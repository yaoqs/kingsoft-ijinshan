#include "stdafx.h"
#include "common.h"
#include "scancontext.h"

BOOL CUnique::IsFilterDir( const CString& DirPath, BOOL& bRecursion )
{
    if ( FALSE == WinMod::CWinPathApi::IsDirectory(DirPath) )
    {
        _ASSERT(0);
        return FALSE;
    }

    return _IsFindDir(DirPath, bRecursion);
}



void CUnique::AddCancelDoubleDir( const CString& ScanDir, BOOL bRecursion )
{
    WinMod::CWinPath DirPath;
    DirPath.m_strPath = ScanDir;
    DirPath.AddBackslash();
  
    if ( FALSE == WinMod::CWinPathApi::IsDirectory(DirPath.m_strPath) )
    {
        _ASSERT(0);
        return;
    }

    BOOL bExit = FALSE;
    POSITION Pos = m_DirPathMap.GetStartPosition();
    if (  NULL == Pos )
    {
        m_DirPathMap.SetAt( DirPath.m_strPath, bRecursion );
        bExit = TRUE;
    }
    else
    {
        //�����ж�
        while ( Pos )
        {
            CAtlMap<CString, BOOL>::CPair* pPair = m_DirPathMap.GetNext( Pos );
            if ( -1 != DirPath.m_strPath.Find(pPair->m_key) && pPair->m_value )
            {
                //1 ��ɨ�����ĳ��Ŀ¼����Ŀ¼������ɨ�����ĳ��Ŀ¼�ǵݹ�ɨ�衣
                //2 ��ɨ�����ĳ��Ŀ¼������ɨ�����Ŀ¼�ǵݹ�ɨ�衣
                //������Ҫɨ���Ŀ¼�Ƿ�ݹ顣�����Ѿ���ɨ�������
                bExit = TRUE;
                break;
            }
        }
    }
    if ( bExit )
    {
        return;
    }

    //�����ж�
    if ( bRecursion )
    {
        //1 ����ɨ�����Ŀ¼����Ŀ¼�������Ѿ�ɨ���Ŀ¼�ĸ�Ŀ¼�����ҵ�ǰĿ¼�ݹ�ɨ�裨Ҫ�����ر�������أ�
        CAtlArray<CString> DelKeyArray;
        POSITION Pos = m_DirPathMap.GetStartPosition();
        while ( Pos )
        {
            CAtlMap<CString, BOOL>::CPair* pPair = m_DirPathMap.GetNext( Pos );
            if ( -1 != pPair->m_key.Find(DirPath.m_strPath) )
            {
                DelKeyArray.Add( pPair->m_key );
            }
        }
        size_t Num = DelKeyArray.GetCount();
        size_t i = 0;
        for(; i<Num; ++i )
        {
            m_DirPathMap.RemoveKey( DelKeyArray[i] );
        }
    }

    //1 ������ɨ�����Ŀ¼����Ŀ¼,�����޹ص�Ŀ¼����������
    //2 ������ɨ�����Ŀ¼����Ŀ¼��������ɨ���Ŀ¼�ĸ�Ŀ¼�����ҵ�ǰĿ¼�ݹ�ɨ�衣��Ҫ�����ر�������أ�֮��������
    //3 ��ɨ�����ĳ��Ŀ¼����Ŀ¼����ɨ�����ĳ��Ŀ¼�������ǵݹ�ɨ�衣��������
    //4 �п���DirPath���Ŀ¼.�Ѿ��ǵݹ�ɨ�����������¸���ֵ�������¸�ֵ��
    m_DirPathMap.SetAt( DirPath.m_strPath, bRecursion );
}



BOOL CUnique::IsFilterFile( const CString& FilePath )
{
    if ( FALSE == WinMod::CWinPathApi::IsFileExisting(FilePath) )
    {
        //�ļ����ڡ����жϲ�������pagefile.sys
        return TRUE;
    }
    BOOL bFilter = FALSE;
    CPath DirPath = FilePath;
    DirPath.RemoveFileSpec();
    BOOL bTemp = FALSE;
    if ( _IsFindFile(FilePath) || _IsFindDir(DirPath.m_strPath, bTemp) )
    {
        //���ύ�����ļ������ļ�����Ŀ¼Ϊ��ɨ�����Ŀ¼��
        bFilter = TRUE;
    }
    return bFilter;
}

void CUnique::AddCancelDoubleFile( const CString& FilePath )
{
    if ( FALSE == WinMod::CWinPathApi::IsFileExisting(FilePath) )
    {
        _ASSERT(0);
        return;
    }
    m_FilePathMap.SetAt( FilePath, 33 );
}

BOOL CUnique::_IsFindFile( const CString& FilePath )
{
    if ( NULL != m_FilePathMap.Lookup(FilePath) )
    {
        return TRUE;
    }
    return FALSE;
}

BOOL CUnique::_IsFindDir( const CString& DirPath, BOOL& bRecursion )
{
    BOOL bRet = FALSE;
    //ƥ����Ŀ¼����,�����ж��Ƿ��ǣ��ݹ���ҵ���Ŀ¼��
    POSITION Pos = m_DirPathMap.GetStartPosition();
    if ( NULL == Pos )
    {
        return FALSE;
    }
    while( Pos )
    {
        CAtlMap<CString, BOOL>::CPair* pPair = m_DirPathMap.GetNext( Pos );

        if ( -1 != DirPath.Find(pPair->m_key) && pPair->m_value )
        {
            //1 ��ɨ�����ĳ��Ŀ¼����Ŀ¼������ɨ�����ĳ��Ŀ¼�ǵݹ�ɨ�衣
            //2 ��ɨ�����ĳ��Ŀ¼������ɨ�����Ŀ¼�ǵݹ�ɨ�衣
            bRecursion = TRUE;
            bRet = TRUE;
            //��¼�����������
            break;
        }
        if ( 0 == DirPath.CompareNoCase(pPair->m_key) && (FALSE == pPair->m_value) )
        {
            //1 ������Ŀ¼����ĳ��ͬĿ¼������û�ݹ�ɨ�����
            bRecursion = FALSE;
            bRet = TRUE;
            //��¼�����������
            break;
        }
    }
    return bRet;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
CAtlMap<CString, RELATETION_DIR_INFO>&    CScanContext::GetRelationDir( )
{
    return m_RelationPathMap;
}

void    CScanContext::RecordCleanInfo( const CString& FilePath, void* pvFlag, PVOID pParam )
{
    DWORD ScanStep = (DWORD)(DWORD_PTR)pvFlag;
    if ( (BkScanStepMemory == ScanStep)
        && (NULL != pParam) )
    {
        m_CleanOperation.RecordCleanDataForMemory( FilePath, (DWORD)(DWORD_PTR)pParam );
    }
    else if ( BkScanStepAutorun == ScanStep )
    {
        //autorun ɨ������ļ�
        m_CleanOperation.RecordCleanDataForAutorun( FilePath, pParam );
    }
}

void    CScanContext::OperateCleanInfo( int Type, const CString& FilePath )
{
    if ( BkScanStepMemory == Type )
    {
        m_CleanOperation.OperateMemoryClean( FilePath );
    }
    else if ( BkScanStepAutorun == Type )
    {
        m_CleanOperation.OperateAutoClean( FilePath );
    }
    else
    {
        _ASSERT(0);
    }
}
 
HRESULT CScanContext::OperateFile(  const CString& FilePath, const WIN32_FIND_DATAW* pFindData, DWORD dwScanMask, void* pvFlag,  PVOID pParam )
{
    //////
    if ( (BkScanModeCheckScan == m_ScanMode) 
        && (BkScanStepAutorun == (INT)(INT_PTR)pvFlag) )
    {
        if ( FALSE == m_OptimizeForCheckScanPolicy.IsNeedOperate( FilePath, pvFlag, pParam ) )
        {
            return S_OK;
        }
    }
    //////

    if ( m_CancelDouble.IsFilterFile(FilePath) )
    {
        return S_OK;
    }

    if (m_HeurDir.IsFileUnderHeuristDir(FilePath))
    {   // �����ϵͳĿ¼,������ʹ���ƶ˸�����
        dwScanMask |= BKENG_SCAN_MASK_USE_CLOUD_HEURIST_HIGH_RISK;
    }

    m_piOpetFileCallback->OperateFile( FilePath, pFindData, dwScanMask, pvFlag, pParam );
    if ( m_bAddPathForFile )
    {
        m_CancelDouble.AddCancelDoubleFile( FilePath );
    }
    return S_OK;
}
BOOL    CScanContext::IsExitEnumWork()
{
    return m_piOpetFileCallback->IsExitEnumWork();
}

//������
void    CScanContext::AddRelationDir( const CString& DirPath, int Step )
{
    if ( FALSE == WinMod::CWinPathApi::IsDirectory(DirPath) )
    {
        _ASSERT(0);
        return;
    }
    if ( m_bRecordRelationDir )
    {
        if ( NULL == m_RelationPathMap.Lookup( DirPath ) )
        {
            RELATETION_DIR_INFO RelationDirInfo;
            RelationDirInfo.bRecursion = FALSE;
            RelationDirInfo.Step       = Step;
            m_RelationPathMap.SetAt( DirPath, RelationDirInfo );
        }
    }
}
BOOL    CScanContext::IsFilterDir( const CString& DirPath, BOOL& bRecursion )
{
    return m_CancelDouble.IsFilterDir( DirPath, bRecursion );
}
void    CScanContext::AddCancelDoubleDir( const CString& ScanDir, BOOL bRecursion )
{
    m_CancelDouble.AddCancelDoubleDir( ScanDir, bRecursion );
}



/////////////////////////////////////////////////////////////////////////////////////
BOOL COptimizeCheckScanPolicy::IsNeedOperate( const CString& FilePath, void*   pvFlag,  PVOID pParam )
{
    BOOL bRet = FALSE;

    const static WCHAR* ppDirName[] =
    {
        //
        L"\\winrar\\",
        L"\\realplayer\\",
        L"\\office11\\",
        L"\\outlook express\\",
        L"\\internet explorer\\",
        L"\\tencent\\",
        L"\\kwmusic\\",
        L"\\stormii\\",
        L"\\thunder\\",
        L"\\sogouinput\\",
        L"\\ttplayer\\",
        L"\\aliwangwang\\",
        //
        NULL
    };

    CString FindData = L"\\program files\\";
    FindData.MakeLower();
    if ( -1 == FilePath.Find(FindData) )
    {
        //û���ҵ���˵�����ǵ����������ɨ���ļ���
        bRet = TRUE;
    }
    else
    {
        //���������
        for ( int i=0; ppDirName[i]; ++i )
        {
            FindData = ppDirName[i];
            FindData.MakeLower();
            if ( -1 != FilePath.Find(FindData) )
            {
                //�Ƚ���Ҫ�ĵ��������Ŀ¼��ɨ���ļ���
                bRet = TRUE;
            }
        }
    }

    return bRet;
}