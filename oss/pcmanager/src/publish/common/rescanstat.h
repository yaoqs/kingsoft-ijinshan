#pragma once
#include "utility.h"
#include "rescandb.h"
#include <atltime.h>

#define THIRTY_MIN 36000000000LL

class CRescanResOprate
{
public:
    HRESULT Initialize()
    {
        HRESULT hr = S_OK;

        hr = m_rescanDB.Initialize();

        return hr;
    }

    HRESULT Uninitialize()
    {
        return m_rescanDB.Uninitialize();
    }

    // bShowAll : TRUE ��ʾ���а����Ѿ���ʾ�ģ�����ullTimeDiff
    //            FALSE����ullTimeDiff������ʾ
    // ullTimeDiff : bShowAll FALSEʱ��Ч
    //               0   : ��ʾ����û����ʾ��
    //               !0  : ��ʾ��������ullTimeDiff֮ǰû����ʾ���ļ�
    HRESULT LoadRescanResult( 
        CAtlArray<CRescanResult>& rescanResArray, 
        LONGLONG ullTimeDiff = 0,
        BOOL     bShowAll = TRUE
        )
    {
        ULARGE_INTEGER  ut;

        ut.QuadPart = 0;

        if ( 0 != ullTimeDiff )
        {
            CFileTimeSpan   timdiff;
            CFileTime       timepoint;

            timdiff.SetTimeSpan( ullTimeDiff );
            timepoint = CFileTime::GetCurrentTime() - timdiff;

            ut.LowPart = timepoint.dwLowDateTime;
            ut.HighPart = timepoint.dwHighDateTime;
        }

        return m_rescanDB.GetRescanResult( rescanResArray, ut.QuadPart, bShowAll );
    }

	HRESULT LoadRescanResult2( 
		CAtlArray<CRescanResult>& rescanResArray, 
		LONGLONG ullTimeDiff = 0,
		int nType = REPORT_FILE_STATE_REPORTING | REPORT_FILE_STATE_WAIT_SCAN
		)
	{
        ULARGE_INTEGER  ut;

        ut.QuadPart = 0;

        if ( 0 != ullTimeDiff )
        {
            CFileTimeSpan   timdiff;
            CFileTime       timepoint;

            timdiff.SetTimeSpan( ullTimeDiff );
            timepoint = CFileTime::GetCurrentTime() - timdiff;

            ut.LowPart = timepoint.dwLowDateTime;
            ut.HighPart = timepoint.dwHighDateTime;
        }

		return m_rescanDB.GetRescanResult2( rescanResArray, ut.QuadPart, nType );
	}

    HRESULT ClearRescanResult()
    {
        return m_rescanDB.ClearResult();
    }

    HRESULT UpdateShowState( const CAtlArray<CRescanResult>& resultList )
    {
        return m_rescanDB.UpdateShowState( resultList );
    }

    HRESULT GetTotalCount( int& nCount )
    {
        return m_rescanDB.GetTotalCount( nCount );
    }

    HRESULT GetFirstTimeReportFiles( CAtlArray<CRescanResult>& resultList )
    {
        return m_rescanDB.GetFirstTimeReportFile( resultList );
    }

    BOOL    IsReportintFile()
    {
        return m_rescanDB.IsReportingFile();
    }
private:
    CRescanDB   m_rescanDB;
};