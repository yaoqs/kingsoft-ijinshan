/**
* @file    avpheurdir.cpp
* @brief   ...
* @author  bbcallen
* @date    2010-07-13 19:40
*/

#include "stdafx.h"
#include "avpheurdir.h"

#include <shlobj.h>
#include "winmod\winpath.h"

NS_SKYLARK_USING

HRESULT CAvpHeurDir::LoadHeuristDir()
{
    WCHAR szPath[MAX_PATH + 1];

    //////////////////////////////////////////////////////////////////////////
    // %windir%\system32
    ::GetSystemDirectory(szPath, MAX_PATH);
    szPath[_countof(szPath) - 1] = L'\0';
    AddHeurDir(szPath, FALSE);

    // %windir%\system32\dllcache
    ::PathAppend(szPath, L"dllcache");
    AddHeurDir(szPath, FALSE);



    //////////////////////////////////////////////////////////////////////////
    // %windir%
    ::GetWindowsDirectory(szPath, MAX_PATH);
    szPath[_countof(szPath) - 1] = L'\0';
    AddHeurDir(szPath, FALSE);

    // %windir%\system
    ::PathAppend(szPath, L"system");
    AddHeurDir(szPath, FALSE);



    //////////////////////////////////////////////////////////////////////////
    // ��Ŀ¼
    ::GetWindowsDirectory(szPath, MAX_PATH);
    szPath[_countof(szPath) - 1] = L'\0';
    ::PathRemoveFileSpec(szPath);
    AddHeurDir(szPath, FALSE);



    //////////////////////////////////////////////////////////////////////////
    // %ProgramFiles%
    ::SHGetSpecialFolderPath(NULL, szPath, CSIDL_PROGRAM_FILES, FALSE);
    szPath[_countof(szPath) - 1] = L'\0';
    AddHeurDir(szPath, FALSE);

    // %ProgramFiles%\Common Files
    ::SHGetSpecialFolderPath(NULL, szPath, CSIDL_PROGRAM_FILES_COMMON, FALSE);
    szPath[_countof(szPath) - 1] = L'\0';
    AddHeurDir(szPath, FALSE);



    //////////////////////////////////////////////////////////////////////////
    // %AppData%
    ::SHGetSpecialFolderPath(NULL, szPath, CSIDL_APPDATA, FALSE);
    szPath[_countof(szPath) - 1] = L'\0';
    AddHeurDir(szPath, FALSE);


    return S_OK;
}

BOOL CAvpHeurDir::IsFileUnderHeuristDir(LPCWSTR lpszFile)
{
    assert(lpszFile && *lpszFile);
    if (!lpszFile || !*lpszFile)
        return TRUE;


    CWinPath PathFile = lpszFile;
    PathFile.m_strPath.MakeLower();
    PathFile.RemoveFileSpec();
    PathFile.AddBackslash();
    if (m_HeurDirMap.Lookup(PathFile))
        return TRUE;


    // ���ﲻ��Ҫ��Ŀ¼��������
    return FALSE;
}

HRESULT CAvpHeurDir::AddHeurDir(LPCWSTR lpszDirectory, BOOL bNormailized)
{
    assert(lpszDirectory && *lpszDirectory);
    if (!lpszDirectory || !*lpszDirectory)
        return E_INVALIDARG;

    assert(lpszDirectory && *lpszDirectory);
    if (!lpszDirectory || !*lpszDirectory)
        return S_FALSE;


    WinMod::CWinPath pathDir = lpszDirectory;
    if (!bNormailized)
    {
        pathDir.ExpandNormalizedPathName();
    }
    pathDir.AddBackslash();
    pathDir.m_strPath.MakeLower();
    m_HeurDirMap.SetAt(pathDir, 0);
    return S_OK;
}