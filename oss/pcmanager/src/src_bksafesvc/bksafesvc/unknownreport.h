#pragma once
#include "winmod/winrunnable.h"
#include "skylark2\bkbak_mod.h"
#include "common\runtimelog.h"
#include "reportfiledb.h"
#include "bkengex.h"
#include "setting.h"

#define REPORT_MAX_RETRY_TIMES  3

#define REPORT_MAX_HIGH_LEVEL_SIZE 0x80000
#define REPORT_MAX_MID_LEVEL_SIZE  0x200000

class CUnkownReport
    : public Skylark::IBKProgress
    , public WinMod::AWinRunnable
{
public:
    CUnkownReport(void):
      m_hNotifyStop( NULL ),
      m_spiUploader( NULL ),
      m_bStartReport( FALSE ),
      m_bFast( FALSE ),
      m_bSettingChange( FALSE )
    {
        FILETIME ftCreateTime;
        FILETIME ftExitTime;

        ::GetThreadTimes(
            GetCurrentThread(),
            &ftCreateTime,
            &ftExitTime,
            &m_ftLastKernelTime,
            &m_ftLastUserTime
            );
    }

    virtual ~CUnkownReport(void) {;}

public:
    static CUnkownReport& Instance()
    {
        static CUnkownReport _ins;

        return _ins;
    }

    HRESULT Initialize();
    HRESULT Uninitialize();

    virtual HRESULT STDMETHODCALLTYPE OnProgress(
        DWORD   dwTotal,
        DWORD   dwFinished
        )
    {
        if (!m_hNotifyStop || INVALID_HANDLE_VALUE == m_hNotifyStop)
            return S_OK;

        if (m_bFast)
        {   // ����ģʽ����CPU����
            return S_OK;
        }

        // ������̵�cpuʱ��
        FILETIME ftCreateTime;
        FILETIME ftExitTime;
        FILETIME ftKernelTime;
        FILETIME ftUserTime;

        ::GetThreadTimes(
            GetCurrentThread(),
            &ftCreateTime,
            &ftExitTime,
            &ftKernelTime,
            &ftUserTime
            );

        CFileTimeSpan   ftsKernelDelta  = CFileTime(ftKernelTime)   - CFileTime(m_ftLastKernelTime);
        CFileTimeSpan   ftsUserDelta    = CFileTime(ftUserTime)     - CFileTime(m_ftLastUserTime);

        LONGLONG        nTotalDelta     = ftsKernelDelta.GetTimeSpan() + ftsUserDelta.GetTimeSpan();
        DWORD           dwWaitMs        = 0;

        // cpu����Ϊ1%
        if (nTotalDelta >= CFileTime::Millisecond * static_cast<ULONGLONG>(10))
        {   // ����10����,���ȴ�150����
            dwWaitMs = 150;
        }
        else if (nTotalDelta >= CFileTime::Millisecond)
        {   // ����n����,�ȴ�n * 9����
            dwWaitMs = DWORD(nTotalDelta * 9 / CFileTime::Millisecond);
        }


        // ���ٵȴ�5����
        dwWaitMs = max(dwWaitMs, 5);
        ::WaitForSingleObject(m_hNotifyStop, dwWaitMs);

        ::GetThreadTimes(
            GetCurrentThread(),
            &ftCreateTime,
            &ftExitTime,
            &m_ftLastKernelTime,
            &m_ftLastUserTime
            );

        return S_OK;
    }


    HRESULT AddUnkownFile( CString strUnkownFile, int nTrack )
    {
        CReportFile rfile;

        CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] add unknown file %s", strUnkownFile );

        rfile.m_strFilePath = strUnkownFile.MakeLower();
        rfile.m_nTrack = nTrack;
        rfile.SetCommitTime( CFileTime::GetCurrentTime() );
        {
            CObjGuard guard( m_submitLock );

            // �ֶ��ύ���ļ������ȼ��ϸߣ������ϴ�
            m_submitList.AddHead( rfile );
        }

        ProcessNewFile();

        // active report thread
        m_hNotifyReport.Set();

        return S_OK;
    }

    HRESULT AddUnkownFile( CAtlArray<CReportFile>& reportArray )
    {
        {
            CObjGuard guard( m_submitLock );

            for ( size_t i = 0; i < reportArray.GetCount(); i++ )
            {
                CReportFile rfile;

                CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] add unknown file %s", reportArray[ i ].m_strFilePath );

                rfile.m_strFilePath = reportArray[ i ].m_strFilePath.MakeLower();
                rfile.m_nTrack = reportArray[ i ].m_nTrack;
                rfile.SetCommitTime( CFileTime::GetCurrentTime() );
                {
                    // �ֶ��ύ���ļ������ȼ��ϸߣ������ϴ�
                    m_submitList.AddHead( rfile );
                }
            }
        }

        ProcessNewFile();

        // active report thread
        m_hNotifyReport.Set();

        return S_OK;
    }


    HRESULT AddUploadedUnkownFile( CString strUnkownFile, int nTrack )
    {
		CObjGuard guard( m_submitLock );

		CReportFile rfile;

		WIN32_FILE_ATTRIBUTE_DATA   fdata;

		CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] add uploaded unknown file %s", strUnkownFile );

		rfile.m_strFilePath = strUnkownFile;
		rfile.m_nTrack = nTrack;
		rfile.SetCommitTime( CFileTime::GetCurrentTime() );
		rfile.SetReportTime( CFileTime::GetCurrentTime() );
		rfile.m_nReportState = enumFileReported;

		if ( GetFileAttributesEx( rfile.m_strFilePath, GetFileExInfoStandard, &fdata ) )
		{
			rfile.SetCreateTime( fdata.ftLastWriteTime );
			rfile.m_nFileSize = fdata.nFileSizeLow;
			rfile.m_nRescanState = enumFileNeedRescan;
		}

		// ���Ϊ���ϴ�,�����ɨ����
		m_reportFileDB.AddFileInfo( rfile );

		return S_OK;
    }


    HRESULT AddUploadedUnkownFile( CAtlArray<CReportFile>& reportArray )
    {
		CObjGuard guard( m_submitLock );

		WIN32_FILE_ATTRIBUTE_DATA   fdata;
		for ( size_t i = 0; i < reportArray.GetCount(); i++ )
		{
			CReportFile rfile;

			CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] add unknown file %s", reportArray[ i ].m_strFilePath );

			rfile.m_strFilePath = reportArray[ i ].m_strFilePath.MakeLower();
			rfile.m_nTrack = reportArray[ i ].m_nTrack;
			rfile.SetCommitTime( CFileTime::GetCurrentTime() );
			rfile.SetReportTime( CFileTime::GetCurrentTime() );
			rfile.m_nReportState = enumFileReported;

			if ( GetFileAttributesEx( rfile.m_strFilePath, GetFileExInfoStandard, &fdata ) )
			{
				rfile.SetCreateTime( fdata.ftLastWriteTime );
				rfile.m_nFileSize = fdata.nFileSizeLow;
				rfile.m_nRescanState = enumFileNeedRescan;
			}

			// ���Ϊ���ϴ�,�����ɨ����
			m_reportFileDB.AddFileInfo( rfile );
		}

		return S_OK;
    }


    void NotifyStop()
    {
        if ( m_spiUploader )
        {
            m_spiUploader->NotifyStop();
        }


        if ( m_hNotifyStop )
        {
            m_hNotifyStop.Set();
        }
    }

    void SettingChange()
    {
        CRunTimeLog::WriteLog(WINMOD_LLVL_TRACE, L"[CUnkownReport] notify setting change" );
        m_bSettingChange = TRUE;
    }

    void StartReportUnkownFile()
    {
        //m_bStartReport = TRUE;
    }

private:
    virtual DWORD STDMETHODCALLTYPE Run();


    BOOL  PopHeadSubmitFile( CReportFile& rfile );
    BOOL  CheckInReportList( CReportFile& rfile );
    void  ProcessNewFile();
    BOOL  CheckExpired( CReportFile& rfile );
    BOOL  CheckInDB( CReportFile& rfile );
    BOOL  GetReportFile( CReportFile& rfile, CAtlList<CReportFile> **pReportList = NULL );
    BOOL  GetBackupFileAttributes( 
        CString& strId, 
        Skylark::BKBAK_BACKUP_INFO& info, 
        BSTR*   bstrOrgPath = NULL
        );

private:
    typedef CComAutoCriticalSection                     CObjLock;
    typedef CComCritSecLock<CComAutoCriticalSection>    CObjGuard;

    CObjLock                            m_submitLock;
    CObjLock                            m_reportLock;
    ATL::CEvent                         m_hNotifyStop;
    ATL::CEvent                         m_hNotifyReport;

    CAtlList<CReportFile>               m_submitList;
    CAtlList<CReportFile>               m_reportHighList;
    CAtlList<CReportFile>               m_reportMidList;
    CAtlList<CReportFile>               m_reportLowList;

    CComPtr<Skylark::IBKEngUploader>        m_spiUploader;
    CComPtr<Skylark::IBKFileBackup>         m_spiBackup;
    CComPtr<Skylark::IBKFileBackupFinder>   m_spiBakFinder;

    CReportFileDB                       m_reportFileDB;

    LONG                                m_lInit;
private:
    BOOL        m_bStartReport;
    BOOL        m_bFast;
    FILETIME    m_ftLastKernelTime;
    FILETIME    m_ftLastUserTime;
    BOOL        m_bSettingChange;
};


class CUnkownFile
{
public:
    CUnkownFile() : m_bStartReport( FALSE )
    {

    }
public:
    HRESULT AddUnkownFile( CString strUnkownFile, int nTrack )
    {
        BOOL    bAutoReport = FALSE;
        CReportFile rfile;

        CRunTimeLog::WriteLog(WINMOD_LLVL_DEBUG, L"[CUnkownReport] add unknown file %s", strUnkownFile );

        CSvcSetting::Instance().GetAutoReport( bAutoReport );

        if ( !bAutoReport && !m_bStartReport )
        {
            rfile.m_strFilePath = strUnkownFile.MakeLower();
            rfile.m_nTrack = nTrack;

            m_lock.Lock();
            m_unkownArray.Add( rfile );
            m_lock.Unlock();
        }
        else
        {
            CUnkownReport::Instance().AddUploadedUnkownFile( strUnkownFile, nTrack );
        }

        return S_OK;
    }

    HRESULT ReportFile()
    {
        CAtlArray<CReportFile>       tmplist;

        m_bStartReport = TRUE;

        m_lock.Lock();
        tmplist.Copy( m_unkownArray );
        m_lock.Unlock();

        CUnkownReport::Instance().AddUploadedUnkownFile( tmplist );
        return S_OK;
    }
private:
    CAtlArray<CReportFile>   m_unkownArray;
    typedef CComAutoCriticalSection                     CObjLock;
    typedef CComCritSecLock<CComAutoCriticalSection>    CObjGuard;
    CObjLock                m_lock;
    BOOL                    m_bStartReport;
};