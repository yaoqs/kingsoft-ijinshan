#include "stdafx.h"
#include "common.h"
#include "miniutil\bkenvdir.h"
#include "enumtask.h"
#include "scanwork.h"



HRESULT CMemoryEnumTask::EnumScanFileForCheckPolicy( CScanContext* piCallback )
{
    _ASSERT(piCallback);

    //�������������֪�û��ᰲװ���Ǹ�Ŀ¼��ȫ·������֪��������ֻ�ý�������
    static WCHAR * ProcessNames[] =
    {
        L"explorer.exe",
        L"iexplore.exe",
        L"360SE.exe",
        L"Maxthon.exe",
        L"sogouexplorer.exe",
        L"ttraveler.exe",
        L"qq.exe",
        L"svchost.exe",
        L"rundll32.exe",
        NULL
    };

    HRESULT hr = E_FAIL;

    WinMod::CWinProcessEnumerator  ProcessEnum;
    hr = ProcessEnum.EnumAllProcesses();
    if ( FAILED(hr) )
    {
        return E_FAIL;
    }
    BOOL bFindProcess = ProcessEnum.FindFirstProcess();
    for (NULL; bFindProcess; bFindProcess = ProcessEnum.FindNextProcess() )
    {
        if ( piCallback->IsExitEnumWork() )
        {
            break;
        }
        Skylark::CWinPath ProcessName;
        hr = ProcessEnum.GetProcessPath( ProcessName.m_strPath );
        if ( FAILED(hr) )
        {
            continue;
        }
        ProcessName.ExpandNormalizedPathName();

        //�жϽ����Ƿ�Ҫȫö��
        BOOL bEnumAllModule = FALSE;
        LPCWSTR pFileName = WinMod::CWinPathApi::FindFileName(ProcessName.m_strPath);
        if ( NULL == pFileName )
        {
            continue;
        }
        for (int i=0; ProcessNames[i]; ++i )
        {
            if ( 0 == _wcsicmp(ProcessNames[i], pFileName) )
            {
                bEnumAllModule = TRUE;
                break;
            }
        }

        piCallback->RecordCleanInfo( ProcessName.m_strPath, (PVOID)(DWORD_PTR)BkScanStepMemory, (PVOID)(DWORD_PTR)(ProcessEnum.GetProcessID()) );
        piCallback->OperateFile( ProcessName.m_strPath, NULL, 0, (PVOID)(DWORD_PTR)BkScanStepMemory, NULL );
        ProcessName.RemoveFileSpec();
        piCallback->AddRelationDir( ProcessName.m_strPath, BkScanRelationDirStepMemory );

        if ( bEnumAllModule )
        {
            EnumModuleProcess( piCallback, ProcessEnum.GetProcessID() );
        }
    }
    return S_OK;
}


HRESULT CMemoryEnumTask::EnumScanFileForIeFixPolicy( CScanContext* piCallback )
{
    _ASSERT(piCallback);

    static UNTERMINAL_ENTRY EnummAllProcessModule[] =
    {
        {L"%ProgramFiles%\\Internet Explorer",             L"iexplore.exe"},
        {L"\\SystemRoot\\",                                L"explorer.exe"},
        {NULL,  NULL}
    };

    HRESULT hr = E_FAIL;

    WinMod::CWinProcessEnumerator  ProcessEnum;
    hr = ProcessEnum.EnumAllProcesses();
    if ( FAILED(hr) )
    {
        return E_FAIL;
    }
    BOOL bFindProcess = ProcessEnum.FindFirstProcess();
    for (NULL; bFindProcess; bFindProcess = ProcessEnum.FindNextProcess() )
    {
        if ( piCallback->IsExitEnumWork() )
        {
            break;
        }
        Skylark::CWinPath ProcessName;
        hr = ProcessEnum.GetProcessPath( ProcessName.m_strPath );
        if ( FAILED(hr) )
        {
            continue;
        }
        ProcessName.ExpandNormalizedPathName();

        //�жϽ����Ƿ�Ҫȫö��
        BOOL bEnumAllModule = FALSE;
        LPCWSTR pFileName = WinMod::CWinPathApi::FindFileName(ProcessName.m_strPath);
        if ( NULL == pFileName )
        {
            continue;
        }
        for (int i=0; EnummAllProcessModule[i].pFileName; ++i )
        {
            if ( 0 == _wcsicmp(EnummAllProcessModule[i].pFileName, pFileName) )
            {
                Skylark::CWinPath FilePath = EnummAllProcessModule[i].pPath;
                FilePath.Append( EnummAllProcessModule[i].pFileName );
                FilePath.ExpandNormalizedPathName();
                if ( 0 == ProcessName.m_strPath.CompareNoCase(FilePath.m_strPath) )
                {
                    bEnumAllModule = TRUE;
                    break;
                }
            }
        }

        piCallback->RecordCleanInfo( ProcessName.m_strPath, (PVOID)(DWORD_PTR)BkScanStepMemory, (PVOID)(DWORD_PTR)(ProcessEnum.GetProcessID()) );
        piCallback->OperateFile( ProcessName.m_strPath, NULL, 0, (PVOID)(DWORD_PTR)BkScanStepMemory, NULL );
        ProcessName.RemoveFileSpec();
        piCallback->AddRelationDir( ProcessName.m_strPath, BkScanRelationDirStepMemory );

        if ( bEnumAllModule )
        {
            EnumModuleProcess( piCallback, ProcessEnum.GetProcessID() );
        }
    }
    return S_OK;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT CMemoryEnumTask::EnumModuleProcess( CScanContext* piCallback, DWORD Pid )
{
    HRESULT hr = E_FAIL;

    WinMod::CWinModuleEnumerator ModuleEnum;
    hr = ModuleEnum.EnumAllModules( Pid );
    if ( FAILED(hr) )
    {
        return hr;
    }
    BOOL bFindModule = ModuleEnum.FindFirstModule();
    for (NULL; bFindModule; bFindModule = ModuleEnum.FindNextModule() )
    {
        if ( piCallback->IsExitEnumWork() )
        {
            break;
        }
        Skylark::CWinPath ModulePath;
        hr = ModuleEnum.GetModulePath( ModulePath.m_strPath );
        if ( FAILED(hr) )
        {
            continue;
        }

        ModulePath.ExpandNormalizedPathName();
        piCallback->OperateFile( ModulePath.m_strPath, NULL, 0, (PVOID)(DWORD_PTR)BkScanStepMemory, NULL );
        ModulePath.RemoveFileSpec();
        piCallback->AddRelationDir( ModulePath.m_strPath, BkScanRelationDirStepMemory );
    }
    return S_OK;
}

HRESULT CMemoryEnumTask::EnumScanFile( CScanContext* piCallback )
{
    _ASSERT(piCallback);


    HRESULT hr = E_FAIL;

    WinMod::CWinProcessEnumerator  ProcessEnum;
    hr = ProcessEnum.EnumAllProcesses();
    if ( FAILED(hr) )
    {
        return E_FAIL;
    }
    BOOL bFindProcess = ProcessEnum.FindFirstProcess();
    for (NULL; bFindProcess; bFindProcess = ProcessEnum.FindNextProcess() )
    {
        if ( piCallback->IsExitEnumWork() )
        {
            break;
        }
        Skylark::CWinPath ProcessName;
        hr = ProcessEnum.GetProcessPath( ProcessName.m_strPath );
        if ( FAILED(hr) )
        {
            continue;
        }

        ProcessName.ExpandNormalizedPathName();
        piCallback->RecordCleanInfo( ProcessName.m_strPath, (PVOID)(DWORD_PTR)BkScanStepMemory, (PVOID)(DWORD_PTR)(ProcessEnum.GetProcessID()) );
        piCallback->OperateFile( ProcessName.m_strPath, NULL, 0, (PVOID)(DWORD_PTR)BkScanStepMemory, NULL );
        ProcessName.RemoveFileSpec();
        piCallback->AddRelationDir( ProcessName.m_strPath, BkScanRelationDirStepMemory );
        EnumModuleProcess( piCallback, ProcessEnum.GetProcessID() );
    }
    return S_OK;
}






HRESULT CEnumDirTask::EnumFileDepth( CScanContext* piCallback, const CString& DirPath )
{
    WinMod::CWinPath NormalizePath = DirPath;
    NormalizePath.AddBackslash();

    if ( IsFilterScanDir(NormalizePath.m_strPath) )
    {
        return S_OK;
    }
    BOOL bRecursion = FALSE;
    if ( piCallback->IsFilterDir(NormalizePath.m_strPath, bRecursion) )
    {
        if ( bRecursion )
        {
            return FALSE;
        }
    }


    WinMod::CWinFileFindDepthFirst hFileFind;
    hFileFind.SetFilter(&piCallback->m_JunctionFilter);
    BOOL bFind = hFileFind.FindFirstFile(NormalizePath.m_strPath);
    while ( bFind )
    {
        if ( piCallback->IsExitEnumWork() )
        {
            //�˳�ɨ��
            break;
        }

        Skylark::CWinPath strFullPath = hFileFind.GetFullPath();
        strFullPath.ExpandNormalizedPathName();
        if ( WinMod::CWinPathApi::IsDirectory(strFullPath) )
        {
            BOOL bRecursionFilter = TRUE;

            strFullPath.AddBackslash();
            if ( IsFilterScanDir(strFullPath.m_strPath) )
            {
                bFind = hFileFind.FindNextFileSkipCurrentTree();
                continue;
            }
            else if ( piCallback->m_JunctionFilter.NeedSkipDirTree(strFullPath.m_strPath, hFileFind.GetFindDataBuffer() ) )
            {
                bFind = hFileFind.FindNextFileSkipCurrentTree();
                continue;
            }
            else if ( piCallback->IsFilterDir(strFullPath.m_strPath, bRecursionFilter) )
            {
                if ( bRecursionFilter )
                {
                    bFind = hFileFind.FindNextFileSkipCurrentTree();
                    continue;
                }
            }
        }
        else
        {
            OperateFile( piCallback, strFullPath.m_strPath, hFileFind.GetFindDataBuffer(), 0, NULL );
        }


        bFind = hFileFind.FindNextFile();
    }
    return S_OK;
}

HRESULT CEnumDirTask::EnumFileCurrentDir( CScanContext* piCallback, const CString& DirPath )
{
    WinMod::CWinFileFind  hFileFind;
    BOOL bFind = hFileFind.FindFirstFile( DirPath + L"*.*" );
    for (; bFind; bFind = hFileFind.FindNextFile() )
    {
        if ( piCallback->IsExitEnumWork() )
        {
            //�˳�ɨ��
            break;
        }

        Skylark::CWinPath strFullPath = DirPath;
        strFullPath.Append( hFileFind.GetFileName() );
        if ( WinMod::CWinPathApi::IsDirectory(strFullPath) )
        {
            continue;
        }
        strFullPath.m_strPath.MakeLower();
        OperateFile( piCallback, strFullPath.m_strPath, hFileFind.GetFindDataBuffer(), 0, NULL );
    }

    return S_OK;
}

HRESULT CEnumDirTask::EnumScanFileForDir( CScanContext* piCallback, const CString& DirPath, BOOL bRecursion )
{
    Skylark::CWinPath NormalizePath = DirPath;
    NormalizePath.AddBackslash();


    if ( FALSE == WinMod::CWinPathApi::IsDirectory(NormalizePath.m_strPath) )
    {
        OperateFile( piCallback, NormalizePath.m_strPath, NULL, 0, NULL );
        return S_OK;
    }
    if ( IsFilterScanDir(NormalizePath.m_strPath) )
    {
        //������������ɨ�衣
        return S_OK;
    }
    BOOL  bRecursionFilter = FALSE;
    BOOL bFilter = piCallback->IsFilterDir( NormalizePath.m_strPath, bRecursionFilter );
    if ( bFilter && bRecursionFilter )
    {
        return S_OK;
    }


    if (  bFilter )
    {
        if ( (FALSE == bRecursionFilter) && bRecursion )
        {
            //Ŀ¼�ǵݹ�ɨ���������Ҫ�ݹ�ɨ��
            WinMod::CWinFileFind  hFileFind;
            BOOL bFind = hFileFind.FindFirstFile( NormalizePath.m_strPath + L"\\*.*" );
            for (; bFind; bFind = hFileFind.FindNextFile() )
            {
                if ( piCallback->IsExitEnumWork() )
                {
                    //�˳�ɨ��
                    break;
                }
                Skylark::CWinPath strFullPath = NormalizePath.m_strPath;
                strFullPath.Append( hFileFind.GetFileName() );
                strFullPath.ExpandNormalizedPathName();
                if ( WinMod::CWinPathApi::IsDirectory(strFullPath.m_strPath) )
                {
                    EnumFileDepth( piCallback, strFullPath.m_strPath );
                }
            }
        }
    }
    else
    {
        if ( bRecursion )
        {
            //Ŀ¼û��ɨ������ݹ�ɨ��
            EnumFileDepth( piCallback, NormalizePath.m_strPath );
        }
        else
        {
            //Ŀ¼û��ɨ������ǵݹ�ɨ��
            EnumFileCurrentDir( piCallback, NormalizePath.m_strPath );
        }
    }

    return S_OK;
}

BOOL CEnumDirTask::IsFilterScanDir(  const CString& StrDirPath )
{
    //��Ŀ¼�µģ�leidianrecycleĿ¼��·���ֽ������ᳬ��30���ַ�
    if ( StrDirPath.GetLength() < 30 )
    {
        Skylark::CWinPath LeiDianRecycle;
        WCHAR TmpRecycle[] = 
            L"C:\\"
            RECYCLE_DIR
            L"\\";
        for ( int i = 0; i<24; ++i, ++TmpRecycle[0] )
        {
            LeiDianRecycle.m_strPath = TmpRecycle;
            LeiDianRecycle.ExpandNormalizedPathName();
            if ( 0 == LeiDianRecycle.m_strPath.CompareNoCase(StrDirPath) )
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}


HRESULT CCriticalDirEnumTask::EnumScanFile( CScanContext* piCallback )
{
    InitCriticalDirInfo();

    POSITION Pos = m_CriticalDirMap.GetStartPosition();
    if ( NULL == Pos )
    {
        return S_OK;
    }
    while ( Pos )
    {
        CAtlMap<CString, BOOL>::CPair* pPair = m_CriticalDirMap.GetNext( Pos );
        if ( WinMod::CWinPathApi::IsDirectory(pPair->m_key) )
        {
            EnumScanFileForDir( piCallback, pPair->m_key, pPair->m_value );
            piCallback->AddCancelDoubleDir( pPair->m_key, pPair->m_value );
            if ( piCallback->IsExitEnumWork() )
            {
                break;
            }
        }
    }
    return S_OK;
}

BOOL CCriticalDirEnumTask::IsFilterScanDir(  const CString& StrDirPath )
{
    CString TmpDirPath = StrDirPath;
    TmpDirPath.MakeLower();
    if ( NULL != m_FilterDirList.Find(TmpDirPath) )
    {
        return TRUE;
    }
    return CEnumDirTask::IsFilterScanDir(StrDirPath);
}





HRESULT CCriticalDirEnumTask::InitCriticalDirInfo()
{
    struct SUBDIR_SCAN_ENTRY
    {
        WCHAR* pSubDir;
        BOOL   bRecursion;
    };

    DWORD Result = 0;

    Skylark::CWinPath NormalizePath;
    //system
    CString SystemCriticalDir;
    Result = ::GetSystemDirectory( SystemCriticalDir.GetBuffer(MAX_PATH+1), MAX_PATH );
    SystemCriticalDir.ReleaseBuffer( (0==Result)?(0):(-1) );
    if ( 0 != Result )
    {
        NormalizePath.m_strPath = SystemCriticalDir;
        NormalizePath.ExpandNormalizedPathName();
        m_CriticalDirMap.SetAt( NormalizePath.m_strPath, FALSE );
        // system ���ݹ�ɨ�裬��˾Ͳ���Ҫ���˸��ļ�����
        //system filter
        //if ( WinMod::CWinOSVer::IsVistaOrLater() )
        //{ 
        //    NormalizePath.m_strPath = SystemCriticalDir;
        //    NormalizePath.Append( L"DriverStore" );
        //    NormalizePath.ExpandNormalizedPathName();
        //    m_FilterDirList.AddTail( NormalizePath.m_strPath );
        //}
        NormalizePath.Append( L"dllcache" );
        m_CriticalDirMap.SetAt( NormalizePath.m_strPath, TRUE );
    }


    CString WindowsDir;
    Result = ::GetWindowsDirectory( WindowsDir.GetBuffer(MAX_PATH+1), MAX_PATH );
    WindowsDir.ReleaseBuffer( (0==Result)?(0):(-1) );
    if ( 0 != Result )
    {
        NormalizePath.m_strPath = WindowsDir;
        NormalizePath.ExpandNormalizedPathName();
        m_CriticalDirMap.SetAt( NormalizePath.m_strPath, FALSE );

        SUBDIR_SCAN_ENTRY ScanTable[] =
        {
            //{L"fonts",                      TRUE},
            //{L"tasks",                      TRUE},
            {L"Downloaded Program Files",   TRUE},
            //{L"microsoft",                  TRUE},
            {L"temp",                       TRUE},
            {L"system",                     TRUE},
            {NULL,                          FALSE}
        };

        int i = 0;
        for(; ScanTable[i].pSubDir; ++i )
        {
            NormalizePath.m_strPath = WindowsDir;
            NormalizePath.Append( ScanTable[i].pSubDir );
            NormalizePath.ExpandNormalizedPathName();
            m_CriticalDirMap.SetAt( NormalizePath.m_strPath, ScanTable[i].bRecursion );
        }

        //c disk temp
        NormalizePath.m_strPath = WindowsDir;
        NormalizePath.RemoveFileSpec();
        NormalizePath.Append( L"temp" );
        NormalizePath.ExpandNormalizedPathName();
        m_CriticalDirMap.SetAt( NormalizePath.m_strPath, FALSE );
    }


    BkEnvDir EnvDir;
    EnvDir.Init();
    //user temp
    CAtlArray<CString> SystemTempDirArray;
    BOOL    bSuccess = FALSE;
    if ( WinMod::CWinOSVer::IsVistaOrLater() )
    {
        bSuccess = EnvDir.Get(CSIDL_LOCAL_APPDATA, SystemTempDirArray);
    }
    else
    {
        bSuccess = EnvDir.Get(CSIDL_PROFILE, SystemTempDirArray);
    }
    if ( bSuccess )
    {
        size_t Num = SystemTempDirArray.GetCount();
        size_t i = 0;
        for (; i < Num; ++i )
        {
            NormalizePath.m_strPath = SystemTempDirArray[i];
            NormalizePath.Append(L"Temp");
            NormalizePath.RemoveBackslash();
            NormalizePath.ExpandNormalizedPathName();
            m_CriticalDirMap.SetAt( NormalizePath.m_strPath, FALSE );
        }
    }


    //internet cash, ie���治ɨ
    //CAtlArray<CString> InternetCachDirArray;
    //if ( EnvDir.Get(CSIDL_INTERNET_CACHE, InternetCachDirArray) )
    //{
    //    size_t Num = InternetCachDirArray.GetCount();
    //    size_t i = 0;
    //    for (; i < Num; ++i )
    //    {
    //        NormalizePath.m_strPath = InternetCachDirArray[i];
    //        NormalizePath.ExpandNormalizedPathName();
    //        m_CriticalDirMap.SetAt( NormalizePath.m_strPath, FALSE );
    //    }
    //}

    CAtlArray<CString> DesktopDirArray;
    if ( EnvDir.Get(CSIDL_DESKTOPDIRECTORY, DesktopDirArray) )
    {
        size_t Num = DesktopDirArray.GetCount();
        size_t i = 0;
        for (; i < Num; ++i )
        {
            NormalizePath.m_strPath = DesktopDirArray[i];
            NormalizePath.ExpandNormalizedPathName();
            m_CriticalDirMap.SetAt( NormalizePath.m_strPath, FALSE );
        }
    }

    CAtlArray<CString> CommDesktop;
    if ( EnvDir.Get( CSIDL_COMMON_DESKTOPDIRECTORY, CommDesktop ) )
    {
        size_t Num = CommDesktop.GetCount();
        size_t i = 0;
        for (; i < Num; ++i )
        {
            NormalizePath.m_strPath = CommDesktop[ i ];
            NormalizePath.RemoveBackslash();
            NormalizePath.ExpandNormalizedPathName();
            m_CriticalDirMap.SetAt( NormalizePath.m_strPath, FALSE );
        }
    }

    CAtlArray<CString> AppData;
    if ( EnvDir.Get( CSIDL_APPDATA, AppData ) )
    {
        size_t Num = AppData.GetCount();
        size_t i = 0;
        for (; i < Num; ++i )
        {
            NormalizePath.m_strPath = AppData[ i ];
            NormalizePath.RemoveBackslash();
            NormalizePath.ExpandNormalizedPathName();
            m_CriticalDirMap.SetAt( NormalizePath.m_strPath, FALSE );
        }
    }

    CString ProgrameFileDir;
    BOOL bRet = ::SHGetSpecialFolderPath( NULL, ProgrameFileDir.GetBuffer(MAX_PATH + 1), CSIDL_PROGRAM_FILES, FALSE );
    ProgrameFileDir.ReleaseBuffer( (FALSE==bRet)?(0):(-1) );
    if ( bRet )
    {
        NormalizePath.m_strPath = ProgrameFileDir;
        NormalizePath.ExpandNormalizedPathName();
        m_CriticalDirMap.SetAt( NormalizePath.m_strPath, FALSE );
        SUBDIR_SCAN_ENTRY ScanTable[] =
        {
            {L"common files",               FALSE},
            {L"common files\\microsoft",    FALSE},
            {L"common files\\system",       FALSE},
            {L"Internet Explorer",          FALSE},
            //{L"Windows Live\\Messenger",    FALSE},
            {NULL,                          FALSE}
        };
        int i = 0;
        for(; ScanTable[i].pSubDir; ++i )
        {
            NormalizePath.m_strPath = ProgrameFileDir;
            NormalizePath.Append( ScanTable[i].pSubDir );
            NormalizePath.ExpandNormalizedPathName();
            m_CriticalDirMap.SetAt( NormalizePath.m_strPath, ScanTable[i].bRecursion );
        }
    }



    //qq ��װĿ¼ ���ݹ�
    CString RetQQInstallPath;
    if (  COther::GetQQInstallDir(RetQQInstallPath) )
    {
        NormalizePath.m_strPath = RetQQInstallPath;
        NormalizePath.Append( L"bin" );
        if ( !NormalizePath.IsExisting() )
        {
            NormalizePath.RemoveFileSpec();
        }
        NormalizePath.ExpandNormalizedPathName();
        m_CriticalDirMap.SetAt( NormalizePath.m_strPath, FALSE );
    }

    //msn ����Ŀ¼ ���ݹ�
    CAtlArray<CString> RetMsnReceivePathArray;
    if ( COther::GetMsnReceiveDir(RetMsnReceivePathArray) )
    {
        size_t Num = RetMsnReceivePathArray.GetCount();
        size_t i = 0;
        for (; i<Num; ++i )
        {
            NormalizePath.m_strPath = RetMsnReceivePathArray[i];
            NormalizePath.ExpandNormalizedPathName();
            m_CriticalDirMap.SetAt( NormalizePath.m_strPath, FALSE );
        }
    }



    return S_OK;
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////





HRESULT CCustomDirEnumTask::EnumScanFileForCusomDir( CScanContext* piCallback, CAtlMap<CString, BOOL>& DirParam, int ScanStep )
{
    m_ScanStep = ScanStep;
    POSITION Pos = DirParam.GetStartPosition();
    if ( NULL == Pos )
    {
        return E_FAIL;
    }
    while( Pos )
    {
        CAtlMap<CString, BOOL>::CPair* pPair = DirParam.GetNext( Pos );
        if ( WinMod::CWinPathApi::IsDirectory(pPair->m_key) )
        {
            EnumScanFileForDir( piCallback, pPair->m_key, pPair->m_value );
            piCallback->AddCancelDoubleDir( pPair->m_key, pPair->m_value );
        }
        else if ( WinMod::CWinPathApi::IsFileExisting(pPair->m_key) )
        {
            OperateFile( piCallback, pPair->m_key, NULL, 0, NULL );
        }
        else
        {
            _ASSERT(0);//��ɨ�赽ӳ��������������ʱ����ִ�е����
        }
        if ( piCallback->IsExitEnumWork() )
        {
            break;
        }
    }
    return S_OK;
}

HRESULT CCustomDirEnumTask::EnumScanFileForRelationDir( CScanContext* piCallback, CAtlMap<CString, RELATETION_DIR_INFO>& RelationDirMap )
{
    POSITION Pos = RelationDirMap.GetStartPosition();
    if ( NULL == Pos )
    {
        return E_FAIL;
    }
    while( Pos )
    {
        CAtlMap<CString, RELATETION_DIR_INFO>::CPair* pPair = RelationDirMap.GetNext( Pos );
        if ( WinMod::CWinPathApi::IsDirectory(pPair->m_key) )
        {
            m_ScanStep = pPair->m_value.Step;
            EnumScanFileForDir( piCallback, pPair->m_key, pPair->m_value.bRecursion );
            piCallback->AddCancelDoubleDir( pPair->m_key, pPair->m_value.bRecursion );
        }
        else if ( WinMod::CWinPathApi::IsFileExisting(pPair->m_key) )
        {
            m_ScanStep = pPair->m_value.Step;
            OperateFile( piCallback, pPair->m_key, NULL, 0, NULL );
        }
        else
        {
            _ASSERT(0);
        }
        if ( piCallback->IsExitEnumWork() )
        {
            break;
        }
    }
    return S_OK;
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

HRESULT CAllRootDirEnumTask::EnumScanFile( CScanContext* piCallback )
{
    DWORD dwCount = 0;
    WCHAR szRootPath[] = L"C:\\";
    for ( int i = 0; i < 24; ++i, ++szRootPath[0] )
    {
        UINT uDriveType = ::GetDriveType( szRootPath );
        if ( (DRIVE_CDROM == uDriveType)
            || (DRIVE_UNKNOWN == uDriveType)
            || (DRIVE_NO_ROOT_DIR == uDriveType) )
        {
            continue;
        }

        BOOL bAccessible = FALSE;
        UINT OldErrorMode = SetErrorMode( SEM_NOOPENFILEERRORBOX | SEM_FAILCRITICALERRORS );
        if ( CDiskCheck::IsDriveDeviceAccessible(szRootPath[0]) )
        {
            bAccessible = TRUE;
        }
        SetErrorMode( OldErrorMode );
        if ( FALSE == bAccessible )
        {
            //���ܷ��ʣ�����
            continue;
        }   

        Skylark::CWinPath RootPath;
        RootPath.m_strPath = szRootPath;
        RootPath.ExpandNormalizedPathName();
        EnumScanFileForDir( piCallback, RootPath.m_strPath, m_bRecursion );
        piCallback->AddCancelDoubleDir( RootPath.m_strPath, m_bRecursion );
        if ( piCallback->IsExitEnumWork() )
        {
            break;
        }
    }

    return S_OK;
}



HRESULT CAllRootDirEnumTask::OperateFile( CScanContext* piCallback, const CString& FilePath, const WIN32_FIND_DATAW* pFindData, DWORD dwScanMask, PVOID pParam )
{
    if ( m_bRecursion )
    {
        piCallback->OperateFile( FilePath, pFindData, 0, (PVOID)BkScanStepAllDisk, pParam );
    }
    else
    {
        piCallback->OperateFile( FilePath, pFindData, 0, (PVOID)BkScanStepCriticalDir, pParam );
    }
    return S_OK;
}


HRESULT CMoveDisEnumTask::EnumScanFile( CScanContext* piCallback )
{
    DWORD dwCount = 0;
    WCHAR szRootPath[] = L"C:\\";
    for ( int i = 0; i < 24; ++i, ++szRootPath[0] )
    {
        UINT uDriveType = ::GetDriveType( szRootPath );
        if ( DRIVE_REMOVABLE != uDriveType )
        {
            //�����ƶ����̣�������
            continue;
        }

        BOOL bAccessible = FALSE;
        UINT OldErrorMode = SetErrorMode( SEM_NOOPENFILEERRORBOX | SEM_FAILCRITICALERRORS );
        if ( CDiskCheck::IsDriveDeviceAccessible(szRootPath[0]) )
        {
            bAccessible = TRUE;
        }
        SetErrorMode( OldErrorMode );
        if ( FALSE == bAccessible )
        {
            //���ܷ��ʣ�����
            continue;
        }   

        Skylark::CWinPath RootPath;
        RootPath.m_strPath = szRootPath;
        RootPath.RemoveBackslash();
        RootPath.ExpandNormalizedPathName();
        EnumScanFileForDir( piCallback, RootPath.m_strPath, TRUE );
        piCallback->AddCancelDoubleDir( RootPath.m_strPath, TRUE );
        if ( piCallback->IsExitEnumWork() )
        {
            break;
        }
    }

    return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
HRESULT CAutorunEnumTask::EnumScanFile( CScanContext* piCallback, DWORD dwEnumParam )
{
    ::CoInitialize(NULL);

    HRESULT hr = E_FAIL;

    Skylark::IBKAutorunScanner*     piAutorunScanner = NULL;
    do 
    {
        hr = CAutorunProxy::Instance().BkCreateAutorunHandle( __uuidof(Skylark::IBKAutorunScanner), (void**)&piAutorunScanner );
        if ( FAILED(hr) )
        {
            break;
        }

        //
        Skylark::BKATRUN_SCAN_PARAM ScanParam;
        Skylark::BKENG_INIT(&ScanParam);
        ScanParam.uResverd[0] = dwEnumParam;
        hr = piAutorunScanner->StartScan(&ScanParam);
        if (FAILED(hr))
            return hr;


        switch ( piCallback->GetScanMode() )
        {
        case BkScanModeCheckScan:
        case BkScanModeCacheAutorun:
            {
                ScanParam.uPolicy = Skylark::enumScanPolicyLite;
                break;
            }
        default:
            {
                ScanParam.uPolicy = Skylark::enumScanPolicyFull;
            }
        }
        hr = piAutorunScanner->StartScan( &ScanParam );
        if ( FAILED(hr) )
        {
            break;
        }

        piCallback->RecordCleanInfo( L"IBKAutorunScanner", (PVOID)BkScanStepAutorun, piAutorunScanner );
        Skylark::IBKAutorunItem* piBKAutorunItem = NULL;
        while ( piAutorunScanner->FindNextItem(&piBKAutorunItem) )
        {
            DWORD dwFileCount = piBKAutorunItem->GetFileCount();
            for ( DWORD dwFileIndex = 0; dwFileIndex < dwFileCount; ++dwFileIndex )
            {
                if ( piCallback->IsExitEnumWork() )
                {
                    break;
                }
                Skylark::CWinPath FilePath = piBKAutorunItem->GetFilePathAt( dwFileIndex );
                FilePath.ExpandNormalizedPathName();
                if ( FALSE == FilePath.m_strPath.IsEmpty() )
                {
                    DWORD dwScanMask = 0;
                    if (piBKAutorunItem->CanBeRepaired())
                    {
                        LPCWSTR lpszExtension = CWinPathApi::FindExtension(FilePath.m_strPath);
                        if (lpszExtension && 0 != StrCmpIW(lpszExtension, L".sys"))
                        {   // .sys�ļ���ʹ������ʽ
                            dwScanMask = BKENG_SCAN_MASK_FROM_AUTORUNS |
                                BKENG_SCAN_MASK_USE_LOCAL_HEURIST |
                                BKENG_SCAN_MASK_USE_CLOUD_HEURIST_HIGH_RISK |
                                BKENG_SCAN_MASK_USE_CLOUD_HEURIST_LOW_RISK;
                        }
                    }

                    piCallback->RecordCleanInfo( FilePath.m_strPath, (PVOID)BkScanStepAutorun, piBKAutorunItem );
                    piCallback->OperateFile( FilePath.m_strPath, NULL, dwScanMask, (PVOID)BkScanStepAutorun, NULL );
                    FilePath.RemoveFileSpec();

                    DWORD dwAtrID = piBKAutorunItem->GetAutorunID();
                    switch (dwAtrID)
                    {
                    case SLATR_HKCR_Shell_MuiCache:
                    case SLATR_HKCU_ShellNoRoam_MuiCache:
                        // ���������Ͳ�ɨ������Ŀ¼
                        break;
                    default:
                        piCallback->AddRelationDir( FilePath.m_strPath, BkScanRelationDirStepAutorun );
                    }
                }
            }
            if ( piBKAutorunItem )
            {
                piBKAutorunItem->Release();
                piBKAutorunItem = NULL;
            }
            if ( piCallback->IsExitEnumWork() )
            {
                break;
            }
        }
    } while ( false );

    if ( piAutorunScanner )
    {
        piAutorunScanner->Release();
        piAutorunScanner = NULL;
    }

    ::CoUninitialize();
    return hr;
}


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

