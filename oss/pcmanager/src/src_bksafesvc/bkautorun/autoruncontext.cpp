/**
* @file    autoruncontext.cpp
* @brief   ...
* @author  zhangrui
* @date    2009-04-24  11:37
*/

#include "stdafx.h"
#include "autoruncontext.h"

#include <assert.h>
#include "winmod\winpath.h"
//#include "skylark2\skylarkdbg.h"
#include "skylark2\slfeed.h"
#include "autorunentry.h"
#include "autorunentrytool.h"

using namespace Skylark;
using namespace WinMod;

#define SLPTL_CMD_LINE_SEPARATORS L" ;,\"@"

CAutorunContext::CAutorunContext():
    m_bEnableFeedDebug(FALSE)
{
    Reset();

#ifdef _DEBUG
    //wprintf(L"\n");
#endif
    //m_bDBG__ = LSE_DBG_GET_ENABLE_DBG_LOG();
}

CAutorunContext::~CAutorunContext()
{
}

HRESULT CAutorunContext::Initialize()
{
    m_pathExtList.RemoveAll();

    // ��ȡ��������
    CString strPathExt;
    DWORD dwLen = ::GetEnvironmentVariable(L"PATHEXT", NULL, 0);
    if (dwLen)
    {
        dwLen = ::GetEnvironmentVariable(L"PATHEXT", strPathExt.GetBuffer(dwLen), dwLen);
        if (dwLen)
            strPathExt.ReleaseBuffer();
        else
            strPathExt.ReleaseBuffer(0);
    }


    // ��ȡpathext�б�
    int     nPos = 0;
    CString strItem;
    while (nPos >= 0)
    {
        strItem = strPathExt.Tokenize(L";", nPos);
        if (!strItem.IsEmpty() && L'.' == strItem[0])
        {
            m_pathExtList.Add(strItem);
        }
    }

    // ���.dll��׺
    m_pathExtList.Add(L".dll");




    // ��ȡsearch path�б�
    WCHAR szBuf[MAX_PATH];
    // c:\\windows\\system32
    ::GetSystemDirectory(szBuf, MAX_PATH);
    m_searchPathList.Add(szBuf);
    
    // c:\\windows\\system
    ::GetWindowsDirectory(szBuf, MAX_PATH);
    ::PathAppend(szBuf, L"system");
    m_searchPathList.Add(szBuf);
    
    // c:\\windows
    ::GetWindowsDirectory(szBuf, MAX_PATH);
    m_searchPathList.Add(szBuf);


    // ��ȡ��������
    CString strPath;
    dwLen = ::GetEnvironmentVariable(L"PATH", NULL, 0);
    if (dwLen)
    {
        dwLen = ::GetEnvironmentVariable(L"PATH", strPathExt.GetBuffer(dwLen), dwLen);
        if (dwLen)
            strPathExt.ReleaseBuffer();
        else
            strPathExt.ReleaseBuffer(0);
    }


    // ��ȡpath�б�
    nPos = 0;
    strItem;
    while (nPos >= 0)
    {
        strItem = strPathExt.Tokenize(L";", nPos);
        if (!strItem.IsEmpty() && L'.' == strItem[0])
        {
            m_searchPathList.Add(strItem);
        }
    }




    // to do : ������� HKLM\System\CurrentControlSet\Control\Session Manager\KnownDlls	
    return S_OK;
}

HRESULT CAutorunContext::Uninitialize()
{
    Reset();

    return S_OK;
}

void CAutorunContext::Reset()
{
    while (!m_itemList.IsEmpty())
    {
        CAutorunItem* pItem = m_itemList.GetHead();
        if (pItem)
        {
            delete pItem;
        }

        m_itemList.RemoveHeadNoReturn();
    }

    m_itemPos           = NULL;
    m_dwCurrentEntryID  = SLATR_None;
}

void CAutorunContext::EnableFeedDebug(BOOL bEnable)
{
    m_bEnableFeedDebug = bEnable;
}

BOOL CAutorunContext::FindFirstContextItem(const SLATR_ENTRY_DATA* pEntry)
{
    Reset();

    if (!CAtrEntryTool::IsValidEntry(pEntry))
        return FALSE;


    assert(pEntry && pEntry->m_pfnEntryScanHandler);
    m_dwCurrentEntryID = pEntry->m_dwEntryID;


    HRESULT hr = pEntry->m_pfnEntryScanHandler(this, pEntry);
    if (FAILED(hr))
        return FALSE;


    if (m_itemList.IsEmpty())
        return FALSE;


    m_itemPos = m_itemList.GetHeadPosition();
    return TRUE;
}


BOOL CAutorunContext::FindNextContextItem()
{
    if (IsEndOfContextItemFind())
        return FALSE;


    m_itemList.GetNext(m_itemPos);


    if (IsEndOfContextItemFind())
        return FALSE;

    
    return TRUE;
}


BOOL CAutorunContext::IsEndOfContextItemFind() const
{
    if (!m_itemPos || m_itemList.IsEmpty())
        return TRUE;

    return FALSE;
}


HRESULT CAutorunContext::ExportTo(CAutorunContext& target) const
{

    if (m_itemList.IsEmpty())
    {
        target.m_itemList.RemoveAll();
        target.m_itemPos = NULL;
    }
    else
    {
        CAutorunItem* pItem = m_itemList.GetHead();
        CAutorunItem* pNewItem = NULL;
        HRESULT hr = pItem->Clone(&pNewItem);
        if (FAILED(hr))
        {
            delete pNewItem;
            return hr;
        }

        target.m_itemList.AddTail(pItem);
        target.m_itemPos = target.m_itemList.GetHeadPosition();
    }


    target.m_dwCurrentEntryID   = m_dwCurrentEntryID;
    target.m_pathExtList        = m_pathExtList;
    target.m_searchPathList     = m_searchPathList;
    target.m_bEnableFeedDebug   = m_bEnableFeedDebug;
    target.m_bDBG__             = m_bDBG__;


    return S_OK;
}

CAutorunItem* CAutorunContext::GetCurrentItem() const
{
    if (IsEndOfContextItemFind())
        return NULL;

    return m_itemList.GetAt(m_itemPos);
}


BOOL CAutorunContext::FindAllPathInText(LPCWSTR lpszCommandLine, CPathList& pathList, CPathList* pAddionalDirList)
{
    if (!lpszCommandLine || !*lpszCommandLine)
        return FALSE;

    LPCWSTR lpszFind = lpszCommandLine;
    BOOL    bFind = FALSE;
    DWORD   dwCount = 0;
    for (NULL; lpszFind && *lpszFind; ++dwCount)
    {
        if (FindFirstPathInText(lpszFind, pathList, pAddionalDirList))
        {   // ��������ҵ�һ���ļ�
            bFind = TRUE;
        }


        // Ѱ�ҿո�,�������������֮��, �ո�,����,����,�ֺ�
        lpszFind = StrPBrkW(lpszFind, SLPTL_CMD_LINE_SEPARATORS);
        if (lpszFind && *lpszFind)
            ++lpszFind;
    }

    return bFind;
}

BOOL CAutorunContext::FindFirstPathInText(LPCWSTR lpszCommandLine, CPathList& pathList, CPathList* pAddionalDirList)
{
    if (!lpszCommandLine || !*lpszCommandLine)
        return FALSE;


    CWinPath path = lpszCommandLine;
    path.m_strPath.Trim();
    CWinPathApi::ExpandEnvironmentStrings(path.m_strPath);
    CWinPathApi::ExpandAsAccessiblePath(path.m_strPath);

    // �����Ƴ�����
    int  nPrevLen = path.m_strPath.GetLength();
    BOOL bIsFileExisting = FALSE;
    while (!bIsFileExisting)
    {
        DWORD dwAttr = ::GetFileAttributes(path.m_strPath);
        bIsFileExisting = (INVALID_FILE_ATTRIBUTES != dwAttr && FILE_ATTRIBUTE_DIRECTORY != dwAttr);
        if (bIsFileExisting)
            break;



        if (path.IsRelative())
        {
            bIsFileExisting = TrySearchPathAndExtension(path, pAddionalDirList);
            if (bIsFileExisting)
                break;
        }
        else
        {
            bIsFileExisting = TrySupplyExtension(path);
            if (bIsFileExisting)
                break;
        }
 


        path.m_strPath.Trim();  // ���������Ŀո�
        for (int i = path.m_strPath.GetLength(); i > 0; --i)
        {
            if (StrChr(SLPTL_CMD_LINE_SEPARATORS, path.m_strPath[i - 1]))
            {
                path.m_strPath.Truncate(i - 1);
                path.m_strPath.TrimRight();
                break;
            }
        }

        // û�ж�����ַ�����ȥ��,��
        if (path.m_strPath.GetLength() >= nPrevLen)
            break;

        nPrevLen = path.m_strPath.GetLength();
    }


    if (bIsFileExisting)
    {
        AddPath(pathList, path);
        return TRUE;
    }


    return FALSE;
}

//BOOL CAutorunContext::FindPathInFileList(LPCWSTR lpszFileList, CPathList& pathList, LPCWSTR lpszDelimiters = L" ,")
//{
//    assert(lpszFileList);
//    assert(lpszDelimiters);
//
//    BOOL     bFind = FALSE;
//    int      nPos  = 0;
//    CString  strFileList = lpszFileList;
//    strFileList.Replace(L';', L' ');     // ���ֺ��滻�ɿո�
//    strFileList.Trim();
//
//    CWinPath pathItem;
//    while (nPos >= 0)
//    {
//        pathItem.m_strPath = strFileList.Tokenize(lpszDelimiters, nPos);
//        if (!pathItem.m_strPath.IsEmpty())
//        {
//            pathItem.m_strPath.Replace(L'\"', L' ');    // �������滻�ɿո�
//            pathItem.m_strPath.Trim();
//            CWinPathApi::ExpandEnvironmentStrings(pathItem.m_strPath);
//            CWinPathApi::ExpandAsAccessiblePath(pathItem.m_strPath);
//
//            if (pathItem.IsRelative())
//            {
//                if (TrySearchPathAndExtension(pathItem))
//                {
//                    AddPath(pathList, pathItem.m_strPath);
//                    bFind = TRUE;
//                }
//            }
//            else
//            {
//                if (TrySupplyExtension(pathItem))
//                {
//                    AddPath(pathList, pathItem.m_strPath);
//                    bFind = TRUE;
//                }
//            }
//        }
//    }
//
//    return bFind;
//}

void CAutorunContext::AddPath(CPathList& pathList, LPCWSTR lpszPath)
{
    if (!lpszPath || !*lpszPath)
        return;


    CString strResolvedPath;

    // ������ݷ�ʽ
    if (CWinPathApi::IsLnkFile(lpszPath))
    {
        HRESULT hr = CWinPathApi::ResolveLnkFile(lpszPath, strResolvedPath);
        if (FAILED(hr))
        {
            strResolvedPath = lpszPath;
        }
    }
    else
    {
        strResolvedPath = lpszPath;
    }


    // �������ظ����ļ�
    for (DWORD i = 0; i < pathList.GetCount(); ++i)
    {
        if (0 == strResolvedPath.CompareNoCase(pathList[0]))
        {
            return;
        }
    }

    pathList.Add(strResolvedPath);
}

LPCWSTR CAutorunContext::SeekNextPossiblePathPos(LPCWSTR lpszExecFile, LPCWSTR lpszCommandLine)
{
    assert(lpszExecFile && !*lpszExecFile);
    if (!lpszExecFile || !*lpszExecFile)
        return NULL;

    assert(lpszCommandLine && !*lpszCommandLine);
    if (!lpszCommandLine || !*lpszCommandLine)
        return NULL;


    lpszExecFile = CWinPathApi::FindFileName(lpszExecFile);
    if (!lpszExecFile)
    {
        return NULL;
    }
    else if (0 == StrCmpIW(lpszExecFile, L"runassrv.exe"))
    {
        return SeekAfterPattern(lpszCommandLine, L"/cmdline:");
    }


    return NULL;
}

LPCWSTR CAutorunContext::SeekAfterPattern(LPCWSTR lpszCommandLine, LPCWSTR lpszPattern)
{    
    assert(lpszCommandLine && !*lpszCommandLine);
    assert(lpszPattern && !*lpszPattern);

    size_t  nPatternLen = wcslen(lpszPattern);
    LPCWSTR lpszFindPos = StrStrIW(lpszCommandLine, lpszPattern);
    if (!lpszFindPos)
        return FALSE;


    if (wcslen(lpszFindPos) <= nPatternLen)
        return FALSE;


    lpszFindPos += nPatternLen;
    return lpszFindPos;
}

BOOL CAutorunContext::TrySearchPathAndExtension(CWinPath& path, CPathList* pAddionalDirList)
{
    assert(path.IsRelative());



    CWinPath absPath;
    // ��鸽�ӵ�Ŀ¼�б�
    if (pAddionalDirList)
    {
        for (size_t i = 0; i < pAddionalDirList->GetCount(); ++i)
        {
            assert(!(*pAddionalDirList)[i].IsEmpty());
            absPath = (LPCWSTR)(*pAddionalDirList)[i];
            absPath.Append(path);

            if (TrySupplyExtension(absPath))
            {
                path = absPath;
                return TRUE;
            }
        }
    }


    // ���Ը���search path ��ȫ·��
    for (size_t i = 0; i < m_searchPathList.GetCount(); ++i)
    {
        assert(!m_searchPathList[i].IsEmpty());
        absPath = (LPCWSTR)m_searchPathList[i];
        absPath.Append(path);

        if (TrySupplyExtension(absPath))
        {
            path = absPath;
            return TRUE;
        }
    }




    return FALSE;
}

BOOL CAutorunContext::TrySupplyExtension(CWinPath& path)
{
    DWORD dwAttr = ::GetFileAttributes(path.m_strPath);
    if (INVALID_FILE_ATTRIBUTES != dwAttr && FILE_ATTRIBUTE_DIRECTORY != dwAttr)
        return TRUE;

    // ���Ը��ݻ������� PATHEXT ��ȫ��չ��
    for (size_t i = 0; i < m_pathExtList.GetCount(); ++i)
    {
        assert(!m_pathExtList[i].IsEmpty());
        assert(L'.' == m_pathExtList[i][0]);
        path.m_strPath.Append(m_pathExtList[i]);

        DWORD dwAttr = ::GetFileAttributes(path.m_strPath);
        if (INVALID_FILE_ATTRIBUTES != dwAttr && FILE_ATTRIBUTE_DIRECTORY != dwAttr)
        {
            path.ExpandFullPathName();
            return TRUE;
        }

        path.RemoveExtension();
    }

    return FALSE;
};





void STDMETHODCALLTYPE CAutorunContext::Append_RegValue_As_Startup(
    const SLATR_ENTRY_DATA* pEntry,
    HKEY                    hKeyRoot,
    LPCWSTR                 lpszRegPath,
    LPCWSTR                 lpszValueName,
    LPCWSTR                 lpszValue)
{
    if (!lpszValue || !*lpszValue)
        return;


    CAutorunItem_RegKey_Run* pItem = new CAutorunItem_RegKey_Run();
    if (!pItem)
        return;



    pItem->m_pEntryData         = pEntry;

    pItem->m_hKeyRoot           = hKeyRoot;
    pItem->m_strRegKeyName      = lpszRegPath;
    pItem->m_strRegValueName    = lpszValueName;
    pItem->m_strRegValue        = lpszValue;

    
    pItem->m_strInformation = CAtrEntryTool::GetHKEYRootString(hKeyRoot);
    if (lpszRegPath)
    {
        pItem->m_strInformation.Append(L"\\");
        pItem->m_strInformation.Append(lpszRegPath);
    }

    if (lpszValueName)
    {
        pItem->m_strInformation.Append(L"\\");
        pItem->m_strInformation.Append(L"[");
        pItem->m_strInformation.Append(lpszValueName);
        pItem->m_strInformation.Append(L"]");
    }
    



    // ��value����������н���
    if (!FindAllPathInText(lpszValue, pItem->m_fileList, NULL))
    {
        if (!pEntry->m_bCanBeZeroFiles)
        {
            ::SetLastError(S_OK);
            FeedInfo(pItem->m_strInformation, lpszValue);
            DWORD dwAttr = ::GetFileAttributes(lpszValue);
            if (INVALID_FILE_ATTRIBUTES  != dwAttr &&
                FILE_ATTRIBUTE_DIRECTORY != dwAttr)
            {
                assert(!"failed to parse existing file");
                FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__FAILED_TO_PARSE_EXISTING_FILE, pEntry->m_dwEntryID, 0, lpszValue);
            }
            else
            {
                DWORD dwError = ::GetLastError();
                FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__APPEND_REGVALUE_AS_STARTUP, pEntry->m_dwEntryID, dwError, lpszValue);
            }
        }
    }
    else if (pItem->m_fileList.IsEmpty())
    {
        NULL;
    }
    else if (pItem->m_fileList.GetCount() == 1)
    {   // ֻ��һ���ļ�,��Ҫ���Ψһ���ļ��ǲ��������ļ���
        CString strFirstFile = pItem->m_fileList[0];
        strFirstFile.MakeLower();
        
        LPCWSTR lpszFileSpec = CWinPathApi::FindFileName(strFirstFile);
        assert(lpszFileSpec);
        if (0 == StrCmpIW(lpszFileSpec, L"rundll32.exe"))
        {
            FeedInfo(pItem->m_strInformation, lpszValue);
            FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__APPEND_REGVALUE_AS_STARTUP, pEntry->m_dwEntryID, S_OK, lpszValue);
        }
    }
    


    m_itemList.AddTail(pItem);
}

void STDMETHODCALLTYPE CAutorunContext::Append_Service(
    const SLATR_ENTRY_DATA* pEntry,
    LPCWSTR                 lpszServiceName,
    DWORD                   dwServiceType,
    DWORD                   dwServiceStart,
    LPCWSTR                 lpszImagePath,
    LPCWSTR                 lpszServiceDll,
    LPCWSTR                 lpszServiceDisplayName,
    LPCWSTR                 lpszServiceDescription)
{
    CAutorunItem_Service* pItem = new CAutorunItem_Service();
    if (!pItem)
        return;




    pItem->m_pEntryData             = pEntry;

    pItem->m_strServiceName         = lpszServiceName;
    pItem->m_dwServiceType          = dwServiceType;
    pItem->m_dwServiceStart         = dwServiceStart;
    pItem->m_strServiceDisplayName  = lpszServiceDisplayName;
    pItem->m_strServiceDescription  = lpszServiceDescription;


    pItem->m_strInformation = L"HKLM\\System\\CurrentControlSet\\Services\\";
    pItem->m_strInformation.Append(lpszServiceName);
    	


    // ��value���������н��н���
    CPathList pathList;
    if (FindAllPathInText(lpszImagePath, pathList, NULL) && !pathList.IsEmpty())
    {
        pItem->m_strImagePath = pathList[0];
    }
    else if (lpszImagePath && *lpszImagePath && ULONG_MAX != dwServiceType)
    {
        ::SetLastError(S_OK);
        FeedInfo(pItem->m_strInformation, lpszImagePath);
        DWORD dwAttr = ::GetFileAttributes(lpszImagePath);
        if (INVALID_FILE_ATTRIBUTES  != dwAttr &&
            FILE_ATTRIBUTE_DIRECTORY != dwAttr)
        {
            assert(!"failed to parse existing file");
            FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__FAILED_TO_PARSE_EXISTING_FILE, pEntry->m_dwEntryID, 0, lpszImagePath);
        }
        else
        {
            DWORD dwError = ::GetLastError();
            FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__APPEND_SERVICE__IMAGE_PATH, pEntry->m_dwEntryID, dwError, lpszImagePath);
        }
    }



    pathList.RemoveAll();
    if (FindAllPathInText(lpszServiceDll, pathList, NULL) && !pathList.IsEmpty())
    {
        pItem->m_strServiceDll = pathList[0];
    }
    else if (lpszServiceDll && *lpszServiceDll && SERVICE_WIN32_SHARE_PROCESS == dwServiceType)
    {   // ������������Ϊ��svchost.exe����ʱ, ������ServiceDLl
        ::SetLastError(S_OK);
        //FeedInfo(pItem->m_strInformation, lpszServiceDll);
        DWORD dwAttr = ::GetFileAttributes(lpszServiceDll);
        if (INVALID_FILE_ATTRIBUTES  != dwAttr &&
            FILE_ATTRIBUTE_DIRECTORY != dwAttr)
        {
            assert(!"failed to parse existing file");
            FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__FAILED_TO_PARSE_EXISTING_FILE, pEntry->m_dwEntryID, 0, lpszServiceDll);
        }
        else
        {
            DWORD dwError = ::GetLastError();
            FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__APPEND_SERVICE__SERVICE_DLL, pEntry->m_dwEntryID, dwError, lpszServiceDll);
        }
    }



    m_itemList.AddTail(pItem);
}

void STDMETHODCALLTYPE CAutorunContext::Append_Scheduled_Task(
    const SLATR_ENTRY_DATA* pEntry,
    LPCWSTR                 lpszTaskName,
    LPCWSTR                 lpszApplicationName)
{
    CAutorunItem_Scheduled_Task* pItem = new CAutorunItem_Scheduled_Task();
    if (!pItem)
        return;




    pItem->m_pEntryData     = pEntry;
    pItem->m_strInformation = lpszTaskName;

    pItem->m_strTaskName    = lpszTaskName;


    


    // ��value���������н��н���
    CPathList pathList;
    if (FindAllPathInText(lpszApplicationName, pathList, NULL) && !pathList.IsEmpty())
    {
        pItem->m_strApplicationName = pathList[0];
    }
    else
    {
        ::SetLastError(S_OK);
        FeedInfo(pItem->m_strInformation, lpszApplicationName);
        DWORD dwAttr = ::GetFileAttributes(lpszApplicationName);
        if (INVALID_FILE_ATTRIBUTES  != dwAttr &&
            FILE_ATTRIBUTE_DIRECTORY != dwAttr)
        {
            assert(!"failed to parse existing file");
            FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__FAILED_TO_PARSE_EXISTING_FILE, pEntry->m_dwEntryID, 0, lpszApplicationName);
        }
        else
        {
            DWORD dwError = ::GetLastError();
            FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__APPEND_SCHEDULED_TASK_APP, pEntry->m_dwEntryID, dwError, lpszApplicationName);
        }
    }


    m_itemList.AddTail(pItem);
}


void STDMETHODCALLTYPE CAutorunContext::Append_Startup_Folder_File(
    const SLATR_ENTRY_DATA* pEntry,
    LPCWSTR                 lpszStartupFolder,
    LPCWSTR                 lpszFilePath)
{
    CAutorunItem_Startup_Folder_File* pItem = new CAutorunItem_Startup_Folder_File();
    if (!pItem)
        return;




    pItem->m_pEntryData         = pEntry;
    pItem->m_strInformation     = lpszStartupFolder;

    pItem->m_strStartupFolder   = lpszStartupFolder;


    // ��value���������н��н���
    CPathList pathList;
    if (FindAllPathInText(lpszFilePath, pathList, NULL) && !pathList.IsEmpty())
    {
        pItem->m_strFilePath = pathList[0];
    }
    else
    {
        ::SetLastError(S_OK);
        FeedInfo(pItem->m_strInformation, lpszFilePath);
        DWORD dwAttr = ::GetFileAttributes(lpszFilePath);
        if (INVALID_FILE_ATTRIBUTES  != dwAttr &&
            FILE_ATTRIBUTE_DIRECTORY != dwAttr)
        {
            assert(!"failed to parse existing file");
            FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__FAILED_TO_PARSE_EXISTING_FILE, pEntry->m_dwEntryID, 0, lpszFilePath);
        }
        else
        {
            DWORD dwError = ::GetLastError();
            FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__APPEND_STARTUP_FOLDER_FILE, pEntry->m_dwEntryID, dwError, lpszFilePath);
        }
    }


    m_itemList.AddTail(pItem);
}

void STDMETHODCALLTYPE CAutorunContext::Append_Startup_Ini_File(
    const SLATR_ENTRY_DATA* pEntry,
    LPCWSTR                 lpszIniFile,
    LPCWSTR                 lpszIniApp,
    LPCWSTR                 lpszIniKey,
    LPCWSTR                 lpszFilePath)
{
    CAutorunItem_Startup_Ini* pItem = new CAutorunItem_Startup_Ini();
    if (!pItem)
        return;




    pItem->m_pEntryData         = pEntry;
    pItem->m_strStartupIniFile  = lpszIniFile;
    pItem->m_strIniApp          = lpszIniApp;
    pItem->m_strIniKey          = lpszIniKey;


    // ������inf����Ŀ¼����
    CWinPath path = lpszIniFile;
    path.RemoveFileSpec();

    CPathList addionalDirList;
    addionalDirList.Add(path.m_strPath);

    // ��value���������н��н���
    if (FindAllPathInText(lpszFilePath, pItem->m_fileList, &addionalDirList) && !pItem->m_fileList.IsEmpty())
    {
        NULL;
    }
    else
    {
        ::SetLastError(S_OK);
        FeedInfo(pItem->m_strInformation, lpszFilePath);
        DWORD dwAttr = ::GetFileAttributes(lpszFilePath);
        if (INVALID_FILE_ATTRIBUTES  != dwAttr &&
            FILE_ATTRIBUTE_DIRECTORY != dwAttr)
        {
            assert(!"failed to parse existing file");
            FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__FAILED_TO_PARSE_EXISTING_FILE, pEntry->m_dwEntryID, 0, lpszFilePath);
        }
        else
        {
            DWORD dwError = ::GetLastError();
            FeedDebugValue(SLK_FEEDCODE_SLAUTORUN__APPEND_STARTUP_FOLDER_FILE, pEntry->m_dwEntryID, dwError, lpszFilePath);
        }
    }


    m_itemList.AddTail(pItem);
}


void CAutorunContext::FeedInfo(LPCWSTR lpszInformation, LPCWSTR lpszFilePath)
{
    UNREFERENCED_PARAMETER(lpszInformation);
    UNREFERENCED_PARAMETER(lpszFilePath);


#ifdef  _DEBUG
#ifndef _ATL_MIN_CRT

    //wprintf(L" <!!!> %s\n", lpszInformation);
    //wprintf(L"   <!!!> %s\n", lpszFilePath);

#endif
#endif
}


void CAutorunContext::FeedDebugValue(DWORD dwFeedCode, DWORD dwEntryID, HRESULT hErrCode, LPCWSTR lpszMessage)
{
    UNREFERENCED_PARAMETER(dwFeedCode);
    UNREFERENCED_PARAMETER(dwEntryID);
    UNREFERENCED_PARAMETER(hErrCode);
    UNREFERENCED_PARAMETER(lpszMessage);

    if (!lpszMessage || !*lpszMessage)
        return;


    if (!m_bEnableFeedDebug)
        return;


    CString strMsg;
    strMsg.Format(L"[%lx]%s", dwEntryID, lpszMessage);
    SkylarkFeedDebugLog(SLK_SCHEMA_AUTORUN, dwFeedCode, hErrCode, strMsg);
}