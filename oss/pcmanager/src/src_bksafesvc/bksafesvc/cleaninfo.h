#pragma  once

#include <math.h>
#include <float.h>
#include <algorithm>
#include "skylark2\bkatrun.h"


struct UNTERMINAL_ENTRY
{
    WCHAR * pPath;
    WCHAR * pFileName;
};
class CCleanOperation
{
public:

    static UNTERMINAL_ENTRY UnterminalFileTable[];
public:
    CCleanOperation():m_piAutorunScanner(NULL)
    {
 
    };
    ~CCleanOperation()
    {
        Reset();
    }

    void    Reset()
    {
        _RemoveAllProcessNamePid();
        //autorun
        _RemoveAllModuleAutorunItem();
        if ( NULL != m_piAutorunScanner )
        {
            m_piAutorunScanner->Release();
            m_piAutorunScanner = NULL;
        }
    }
    HRESULT RecordCleanDataForMemory( const CString& FilePath, DWORD Pid );
    HRESULT RecordCleanDataForAutorun( const CString& FilePath, PVOID pParam );
    VOID    OperateMemoryClean( const CString& FilePath );
    VOID    OperateAutoClean( const CString& FilePath );
    
private:
    //�ڴ�ɨ�裬���̴���
    BOOL        _IsOperateForClean( const CString& FilePath );
    VOID        _RemoveAllProcessNamePid();
    BOOL	    _IsProcessMainModule( const CString& StrProcessName, CAtlArray<DWORD>& PidArray );
    VOID        _RemoveProcessNamePid( const CString& StrProcessName );
    //ע���ɨ�裬Autorun����
    VOID        _RemoveAllModuleAutorunItem();
    BOOL        _IsAutorunModule( const CString& StrModule, CAtlArray<Skylark::IBKAutorunItem*>& AutorunItemArray );
    VOID        _RemoveModuleAutorunItem( const CString& StrModule );


private:
    typedef CComAutoCriticalSection                     CObjLock;
    typedef CComCritSecLock<CComAutoCriticalSection>    CObjGuard;
    CObjLock    m_LockForProcess;
    CObjLock    m_LockForAutorun;
    //�ڴ���ģ���
    typedef CAtlArray<DWORD>					CAtlPidArray;
    typedef CAtlMap<CString, CAtlPidArray*>		CAtlProcessNamePidMap;
    CAtlProcessNamePidMap						m_ProcessNamePidMap;
    //Autorunģ���б�
    typedef CAtlArray<Skylark::IBKAutorunItem*>                    CAtlAutorunItemArray;
    typedef CAtlMap<CString, CAtlAutorunItemArray*>                   CAtlModuleNameAutorunItemMap;
    CAtlModuleNameAutorunItemMap                    m_ModuleNameAutorunItemMap;
    Skylark::IBKAutorunScanner*                     m_piAutorunScanner;
};


class CScanStep
{
public:
    CScanStep()
        : m_MemFileNum(0)
        , m_AutoRunFileNum(0)
        , m_CriticalDirFileNum(0)
        , m_AllDiskFileNum(0)
        , m_CustomDirFileNum(0)
        , m_MoveDisFileNum(0)    
    {

    }
    ~CScanStep(){}
public:
    void Reset()
    {
        CObjGuard AutoLock(m_Lock);
        m_MemFileNum        = 0;
        m_AutoRunFileNum        = 0;
        m_CriticalDirFileNum        = 0;
        m_AllDiskFileNum        = 0;
        m_CustomDirFileNum        = 0;
        m_MoveDisFileNum        = 0;
    }
    void IncScanFileNum( int ScanMode, int ScanStep );
    void DecScanFileNum( int ScanMode, int ScanStep );

    HRESULT  QueryScanStep( int ScanMode, CAtlArray<int>& ScanStepArray );

    int GetScanStep( int ScanMode, DWORD ScanFileNum, int SrcScanStep );

    DWORD GetTotalFileNum()
    {
        return (m_MemFileNum + m_AutoRunFileNum + m_CriticalDirFileNum + m_AllDiskFileNum + m_CustomDirFileNum + m_MoveDisFileNum);
    }
private:
    typedef CComAutoCriticalSection                     CObjLock;
    typedef CComCritSecLock<CComAutoCriticalSection>    CObjGuard;
    CObjLock    m_Lock;

    DWORD m_MemFileNum;
    DWORD m_AutoRunFileNum;
    DWORD m_CriticalDirFileNum;
    DWORD m_AllDiskFileNum;
    DWORD m_CustomDirFileNum;
    DWORD m_MoveDisFileNum;
};

class CScanProgress
{
public:
    CScanProgress()
        :m_LastScanFileNum(0)
        ,m_OnePercentFileNum(0)
        ,m_LastPercent(0)
        ,m_bEntry(FALSE)
    {}
    ~CScanProgress(){};

    void Reset()
    {
        m_LastScanFileNum = 0;
        m_OnePercentFileNum = 0;
        m_LastPercent = 0;
        m_bEntry = 0;
    }
    //DWORD GetScanProcess( DWORD CleanFileNum, DWORD TotalFileNum )
    //{
    //     return (CleanFileNum * 100) / TotalFileNum;
    //}
    DWORD GetScanProgress( int ScanMode, DWORD ScanFileNum, DWORD TotalFileNum, DWORD LastProgress, BOOL bEnumFinished)
    {
        DWORD Progress = 0;
        if ( bEnumFinished )
        {
            if ( !m_bEntry )
            {   
                DWORD NoScanFileNum = TotalFileNum - ScanFileNum;
                DWORD NoScanPercent = 100 - LastProgress;
                m_OnePercentFileNum = NoScanFileNum / NoScanPercent;
                m_LastScanFileNum = ScanFileNum;
                m_LastPercent = LastProgress;
                m_bEntry = TRUE;
            }
            if ( (0 <= m_OnePercentFileNum && m_OnePercentFileNum <= 5)
                || (LastProgress > 95) )
            {
                //m_OnePercentFileNum ̫С�ˣ�m_LastPercent + (ScanFileNum-m_LastScanFileNum)/m_OnePercentFileNum; ���ܻᳬ�� 100���磺m_OnePercentFileNum Ϊ 1��
                //m_OnePercentFileNum Ϊ 0���϶�Ҳ���С�
                //LastProgress ���� 95 ʱ��Ҫ����ʵ���ݡ���Ϊ������п���Progress�Ѿ�100�ˣ��������ļ�û��ɨ�棬�����ScanFileNum-m_LastScanFileNum)/m_OnePercentFileNum������ԭ����ɵġ�
                Progress =  (ScanFileNum * 100) / TotalFileNum;
            }
            else
            {
                Progress = m_LastPercent + (ScanFileNum-m_LastScanFileNum)/m_OnePercentFileNum;
            }
        }
        else
        {
            if ( BkScanModeFullScan == ScanMode )
            {
                Progress = (DWORD)(ScanFileNum / 2000);
                if ( Progress > 50 )
                {
                    Progress = 50;
                }
            }
            else if ( BkScanModeCheckScan == ScanMode )
            {
                //���ɨ�����
                //���ɨ������ļ��������������̫������Ĭ��1000.
                //ģ����߰ٷֱ� 90%
                Progress =  (DWORD)(ScanFileNum / 10);
                if ( Progress > 90 )
                {
                    Progress = 90;
                }
            }
            else
            {
                Progress = (DWORD)(ScanFileNum / 150);
                if ( Progress > 80 )
                {
                    Progress = 80;
                }
            }

        }

        return Progress;
    }
private:
    DWORD                       m_LastScanFileNum;
    DWORD                       m_OnePercentFileNum;
    DWORD                       m_LastPercent;
    BOOL                        m_bEntry;
};



class CScanProgress2Hint
{
public:
    CScanProgress2Hint()
    {

    }

    ~CScanProgress2Hint()
    {

    }

    void Reset()
    {
        m_bAlreadyRead  = FALSE;
        m_bAlreadyWrite = FALSE;
        m_dwHintCount   = 0;
    }

    DWORD GetHintCount(LPCWSTR lpszScanMode, DWORD dwMin, DWORD dwMax);
    void  SetHintCount(LPCWSTR lpszScanMode, DWORD dwCount, DWORD dwMin, DWORD dwMax);

    LPCWSTR GetScanIniFile() {return L"ksafesv.scan.ini";}
    LPCWSTR GetScanAppName() {return L"EnumHint";}

    BOOLEAN m_bAlreadyRead;
    BOOLEAN m_bAlreadyWrite;
    DWORD   m_dwHintCount;
};


class CScanProgress2
{
public:
    CScanProgress2();
    ~CScanProgress2();

    void Reset();



    // ���Բ�ֵ
    // xSample �� ySample ������������
    double LinearProgress(
        double xVal,
        double xSamples[],
        double ySamples[],
        size_t nSampleCount,
        double yLowerBound = 0,
        double yUpperBound = DBL_MAX);



    DWORD GetScanProgress( int ScanMode, DWORD ScanFileNum, DWORD TotalFileNum, DWORD LastProgress, BOOL bEnumFinished);


    DWORD GetHintCountForFastScan();
    void  SetHintCountForFastScan(DWORD dwCount);



private:

    BOOL    m_bEnumFinished;                            ///< �Ƿ��Ѿ����ö��
    double  m_dVirtualProgress;                         ///< ��ǰ����ɨ�����

    double  m_dLastVirtualProgress;                     ///< ���һ������ɨ�����
    DWORD   m_dwScanFileCountForLastVirtualProgress;    ///< ���һ������ɨ����ȵĶ�Ӧ�ļ�����

    CScanProgress2Hint  m_hintFastScan;         ///< ����ɨ����ʾ
    CScanProgress2Hint  m_hintFullScan;         ///< ��ȫɨ����
};