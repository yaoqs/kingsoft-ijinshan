/**
* @file    bootchecktool.cpp
* @brief   ...
* @author  zhangrui
* @date    2009-07-31 11:46
*/

#include "stdafx.h"
#include "bootchecktool.h"

#include <atlbase.h>
#include <atlpath.h>
#include <atlfile.h>
#include "encryptfile.h"

#pragma warning(disable: 4996)

using namespace SafeApi;

#define BOOT_CHECK_MAX_ENTRY_LIMIT  65535

HRESULT CBootCheckTool::InstallDriver(LPCWSTR lpszDriverPath)
{
    // �����������,����֮
    HRESULT hr = CopyDriverIfNew(lpszDriverPath);
    if (FAILED(hr))
        return hr;


    // ��ȡϵͳĿ¼
    WCHAR szSystemDriver[MAX_PATH + 1];
    UINT  uRet = ::GetSystemDirectory(szSystemDriver, MAX_PATH);
    if (!uRet)
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;

    ::PathAppend(szSystemDriver, L"Drivers");
    ::PathAppend(szSystemDriver, BC_DriverFileName);



    // ������·�����мӹ�,�԰����ո��·��������(��MSDN)
    CPath quotedPathDriver = szSystemDriver;
    quotedPathDriver.QuoteSpaces();



    // ��װ����/�޸���������
    SC_HANDLE hScm = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (NULL == hScm)
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;



    SC_HANDLE hService = ::OpenService(hScm, BC_ServiceName, SC_MANAGER_ALL_ACCESS);
    if (hService)
    {
        BOOL bRet = ::ChangeServiceConfig(
            hService,
            SERVICE_KERNEL_DRIVER, 
            SERVICE_BOOT_START,
            SERVICE_ERROR_NORMAL,
            quotedPathDriver.m_strPath,
            BC_ServiceGroup,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL);
        if (!bRet)
        {
            ::CloseServiceHandle(hService);
            ::CloseServiceHandle(hScm);
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
        }
    }
    else
    {
        hService = ::CreateService(
            hScm,
            BC_ServiceName,
            BC_ServiceName,
            SERVICE_ALL_ACCESS,
            SERVICE_KERNEL_DRIVER,
            SERVICE_BOOT_START,
            SERVICE_ERROR_NORMAL,
            quotedPathDriver.m_strPath,
            BC_ServiceGroup,
            NULL,
            NULL,
            NULL,
            NULL);
        if (NULL == hService)
        {
            ::CloseServiceHandle(hScm);
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
        }
    }



    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hScm);
    return S_OK;
}

HRESULT CBootCheckTool::UninstallDriver()
{
    WCHAR szConfigFile[MAX_PATH + 1];
    ::GetSystemDirectory(szConfigFile, MAX_PATH);
    ::PathAppend(szConfigFile, FileBootCleanConfigFileName);
    ::DeleteFile(szConfigFile);

    ::GetSystemDirectory(szConfigFile, MAX_PATH);
    ::PathAppend(szConfigFile, FileBootReplaceConfigFileName);
    ::DeleteFile(szConfigFile);

    ::GetSystemDirectory(szConfigFile, MAX_PATH);
    ::PathAppend(szConfigFile, RegBootCleanConfigFileName);
    ::DeleteFile(szConfigFile);

    ::GetSystemDirectory(szConfigFile, MAX_PATH);
    ::PathAppend(szConfigFile, DriverApprovedConfigFileName);
    ::DeleteFile(szConfigFile);

    ::GetSystemDirectory(szConfigFile, MAX_PATH);
    ::PathAppend(szConfigFile, DriverBlockedConfigFileName);
    ::DeleteFile(szConfigFile);


    // ж������
    SC_HANDLE hScm = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (NULL == hScm)
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


    SC_HANDLE hService = ::OpenService(hScm, BC_ServiceName, SC_MANAGER_ALL_ACCESS);
    if (NULL == hScm)
    {
        ::CloseServiceHandle(hScm);
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
    }


    // ��֧��ֹͣ
    //SERVICE_STATUS status;
    //BOOL bStopService = ::ControlService(hService, SERVICE_CONTROL_STOP, &status);
    //if (!bStopService)
    //{
    //    ::CloseServiceHandle(hService);
    //    ::CloseServiceHandle(hScm);
    //    return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
    //}


    BOOL bDeleteService = ::DeleteService(hService);
    if (!bDeleteService)
    {
        ::CloseServiceHandle(hService);
        ::CloseServiceHandle(hScm);
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
    }


    WCHAR szDriverFile[MAX_PATH + 1];
    ::GetSystemDirectory(szDriverFile, MAX_PATH);
    ::PathAppend(szDriverFile, L"Drivers");
    ::PathAppend(szDriverFile, BC_DriverFileName);
    ::DeleteFile(szDriverFile);


    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hScm);
    return S_OK;
}

HRESULT CBootCheckTool::BootDeleteFile(LPCWSTR lpszFilePath)
{ 
    return BootAddToConfigFile(FileBootCleanConfigFileName, lpszFilePath);
}

HRESULT CBootCheckTool::BootOccupyFile(LPCWSTR lpszFilePath)
{
    return BootAddToConfigFile(FileBootOccupyConfigFileName, lpszFilePath);
}

HRESULT CBootCheckTool::BootLoadOccupyFile(CAtlMap<CString, DWORD>& fileList)
{
    return BootLoadConfigFile(FileBootOccupyConfigFileName, fileList);
}

HRESULT CBootCheckTool::CopyDriverIfNew(LPCWSTR lpszNewDriver)
{
    WCHAR szOldDriver[MAX_PATH + 1];
    UINT  uRet = ::GetSystemDirectory(szOldDriver, MAX_PATH);
    if (!uRet)
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


    ::PathAppend(szOldDriver, L"Drivers");
    ::PathAppend(szOldDriver, BC_DriverFileName);


    ULARGE_INTEGER uiOldVersion = GetDllVersion(szOldDriver);
    ULARGE_INTEGER uiNewVersion = GetDllVersion(lpszNewDriver);


    if (uiNewVersion.QuadPart <= uiOldVersion.QuadPart)
        return S_FALSE; // ����Ҫ����


    // �������µİ汾
    BOOL br = ::CopyFile(lpszNewDriver, szOldDriver, FALSE);
    if (!br)
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


    return S_OK;
}

ULARGE_INTEGER CBootCheckTool::GetDllVersion(LPCWSTR lpszFilePath)
{
    BOOL  bRet              = FALSE;
    DWORD dwHandle          = 0;
    DWORD dwFileInfoSize    = 0;
    VS_FIXEDFILEINFO *pFixFileInfo = NULL;
    TCHAR *pszFileInfo      = NULL;
    UINT  uLen              = 0;
    ULARGE_INTEGER uiVersion;
    uiVersion.HighPart = 0;
    uiVersion.LowPart  = 0;

    dwFileInfoSize = ::GetFileVersionInfoSize(lpszFilePath, &dwHandle);
    if (dwFileInfoSize == 0)
        goto Exit0;      

    pszFileInfo = new TCHAR[dwFileInfoSize];
    if (pszFileInfo == NULL)
        goto Exit0;      

    bRet = ::GetFileVersionInfo(lpszFilePath, dwHandle, dwFileInfoSize, pszFileInfo);
    if (!bRet)
        goto Exit0;

    bRet = ::VerQueryValue(pszFileInfo, _T("\\"), (LPVOID *)&pFixFileInfo, &uLen);
    if (!bRet)
        goto Exit0;

    if (uLen > 0)
    {
        uiVersion.HighPart = pFixFileInfo->dwFileVersionMS;
        uiVersion.LowPart  = pFixFileInfo->dwFileVersionLS;
    }


Exit0:
    if (pszFileInfo)
    {
        delete pszFileInfo;
        pszFileInfo = NULL;
    }

    return uiVersion;
}

HRESULT CBootCheckTool::RemoveConfigFile()
{
    WCHAR szConfigPath[MAX_PATH + 1];
    UINT  uRet = ::GetSystemDirectory(szConfigPath, MAX_PATH);
    if (!uRet)
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


    ::PathAppend(szConfigPath, FileBootCleanConfigFileName);


    BOOL br = ::DeleteFile(szConfigPath);
    if (!br)
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


    return S_OK;
}

HRESULT CBootCheckTool::GetDriverPath(WCHAR szSystemDriver[MAX_PATH + 1], LPCWSTR lpszConfigName)
{
    // ��ȡϵͳĿ¼
    UINT  uRet = ::GetSystemDirectory(szSystemDriver, MAX_PATH);
    if (!uRet)
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


    ::PathAppend(szSystemDriver, lpszConfigName);
    return S_OK;
}

HRESULT CBootCheckTool::BootFillEntry(FILE_CLEAN_ENTRY& entry, LPCWSTR lpszFilePath)
{
    // ����ɾ����
    memset(&entry, 0, sizeof(FILE_CLEAN_ENTRY));
    // �����,��ȥ��unicodeǰ׺
    if (0 == StrCmpNW(lpszFilePath, L"\\\\?\\", 4))
    {
        lpszFilePath += 4;
    }

    // ���û��,������ں�·��ǰ׺
    if (0 != StrCmpNW(lpszFilePath, L"\\??\\", 4))
    {
        wcsncpy(entry.wstrFilePath,     L"\\??\\",    4);
        wcsncpy(entry.wstrFilePath + 4, lpszFilePath,  _countof(entry.wstrFilePath) - 4);
    }
    else
    {
        wcsncpy(entry.wstrFilePath, lpszFilePath, _countof(entry.wstrFilePath));
    }
    // ȷ��������
    entry.wstrFilePath[_countof(entry.wstrFilePath) - 1] = L'\0';
    CharLower(entry.wstrFilePath);


    // md5û��ʹ��,���ﲻ��дmd5
    return S_OK;
}

HRESULT CBootCheckTool::BootAddToConfigFile(LPCWSTR lpszConfigName, LPCWSTR lpszFilePath)
{
    if (!lpszConfigName || !*lpszConfigName)
        return E_INVALIDARG;

    if (!lpszFilePath || !*lpszFilePath)
        return S_FALSE;


    // ��ȡϵͳĿ¼
    WCHAR szSystemDriver[MAX_PATH + 1];
    HRESULT hr = GetDriverPath(szSystemDriver, lpszConfigName);
    if (FAILED(hr))
        return hr;



    // ��ȡ�����ļ�
    CAtlMap<CString, DWORD> fileList;
    BootLoadConfigFile(lpszConfigName, fileList);


    // �����,��ȥ��unicodeǰ׺
    FILE_CLEAN_ENTRY cleanEntry;
    BootFillEntry(cleanEntry, lpszFilePath);


    // ����Ƿ���ָ������Ŀ
    if (fileList.Lookup(cleanEntry.wstrFilePath))
        return S_FALSE;


    // �����Ŀ
    fileList.SetAt(cleanEntry.wstrFilePath, 0);


    // ���������ļ�
    return BootSaveConfigFile(lpszConfigName, fileList);
}

HRESULT CBootCheckTool::BootRemoveFromConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, DWORD>& removeList)
{
    if (!lpszConfigName || !*lpszConfigName)
        return E_INVALIDARG;

    if (removeList.IsEmpty())
        return S_FALSE;

    // ��ȡϵͳĿ¼
    WCHAR szSystemDriver[MAX_PATH + 1];
    HRESULT hr = GetDriverPath(szSystemDriver, lpszConfigName);
    if (FAILED(hr))
        return hr;



    // ��ȡ�����ļ�
    CAtlMap<CString, DWORD> fileList;
    BootLoadConfigFile(lpszConfigName, fileList);


    // ɾ��ָ������Ŀ
    for (POSITION pos = removeList.GetStartPosition(); pos; removeList.GetNext(pos))
    {
        CString strRemoveFile = removeList.GetKeyAt(pos);

        // �����,��ȥ��unicodeǰ׺
        FILE_CLEAN_ENTRY cleanEntry;
        BootFillEntry(cleanEntry, strRemoveFile);

        // ɾ��ָ����Ŀ
        fileList.RemoveKey(cleanEntry.wstrFilePath);
    }


    // ���������ļ�
    return BootSaveConfigFile(lpszConfigName, fileList);
}

HRESULT CBootCheckTool::BootSaveConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, DWORD>& writeList)
{
    if (!lpszConfigName || !*lpszConfigName)
        return E_INVALIDARG;


    // ��ȡϵͳĿ¼
    WCHAR szSystemDriver[MAX_PATH + 1];
    HRESULT hr = GetDriverPath(szSystemDriver, lpszConfigName);
    if (FAILED(hr))
        return hr;


    CString strBackup = szSystemDriver;
    strBackup.Append(L".write");


    // �������ļ�
    CEncryptFile hCfgFile;
    hr = hCfgFile.Create(
        strBackup,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_DELETE,      // do not share file
        OPEN_ALWAYS);
    if (FAILED(hr))
        return hr;


    hr = hCfgFile.SetSize(0);
    if (FAILED(hr))
    {
        ::DeleteFile(strBackup);
        return hr;
    }


    // �����ļ�ͷ
    FILE_CLEAN_HEADER fileCleanHeader;
    memset(&fileCleanHeader, 0, sizeof(fileCleanHeader));
    fileCleanHeader.ulWindowsVersion = ::GetVersion();
    fileCleanHeader.ulNumber         = (DWORD)writeList.GetCount();
    hr = hCfgFile.Write(&fileCleanHeader, sizeof(fileCleanHeader));
    if (FAILED(hr))
    {
        ::DeleteFile(strBackup);
        return hr;
    }



    // ����������Ŀ
    POSITION pos = writeList.GetStartPosition();
    for (NULL; pos; writeList.GetNext(pos))
    {
        CString strKey = writeList.GetKeyAt(pos);

        FILE_CLEAN_ENTRY entry;
        memset(&entry, 0, sizeof(entry));

        wcsncpy(entry.wstrFilePath, strKey, _countof(entry.wstrFilePath));
        entry.wstrFilePath[_countof(entry.wstrFilePath) - 1] = L'\0';

        hr = hCfgFile.Write(&entry, sizeof(entry));
        if (FAILED(hr))
        {
            ::DeleteFile(strBackup);
            return hr;
        }
    }



    hCfgFile.Close();
    ::DeleteFile(szSystemDriver);
    BOOL bRet = ::MoveFile(strBackup, szSystemDriver);
    if (!bRet)
    {
        ::DeleteFile(strBackup);
        return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
    }


    return S_OK;
}

HRESULT CBootCheckTool::BootLoadConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, DWORD>& fileList)
{
    if (!lpszConfigName || !*lpszConfigName)
        return E_INVALIDARG;

    fileList.RemoveAll();


    // ��ȡϵͳĿ¼
    WCHAR szSystemDriver[MAX_PATH + 1];
    HRESULT hr = GetDriverPath(szSystemDriver, lpszConfigName);
    if (FAILED(hr))
        return hr;


    if (INVALID_FILE_ATTRIBUTES == ::GetFileAttributes(szSystemDriver))
        return S_FALSE;



    CString strBackup = szSystemDriver;
    strBackup.Append(L".read");


    // ����һ���������ڶ�ȡ
    ::CopyFile(szSystemDriver, strBackup, FALSE);




    // ��ȡ�����ļ�,�˳�ʱ�Զ�ɾ��
    CEncryptFile hCfgFile;
    hr = hCfgFile.Create(
        strBackup,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_DELETE,      // do not share file
        OPEN_EXISTING,
        FILE_FLAG_DELETE_ON_CLOSE);
    if (FAILED(hr))
        return S_FALSE;




    FILE_CLEAN_HEADER fileCleanHeader;
    memset(&fileCleanHeader, 0, sizeof(fileCleanHeader));



    ULONGLONG uFileSize = 0;
    hr = hCfgFile.GetSize(uFileSize);
    if (FAILED(hr))
        return S_FALSE;


    hr = hCfgFile.Read(&fileCleanHeader, sizeof(fileCleanHeader));
    if (FAILED(hr))
        return S_FALSE;


    if (uFileSize < sizeof(FILE_CLEAN_HEADER))
        return S_FALSE;



    // ����ļ���С����Ϣͷ�еĸ����Ƿ��Ǻ�
    // ͬʱ����entry��Ŀ
    ULONGLONG uRealEntryCount = (uFileSize - sizeof(FILE_CLEAN_HEADER)) / sizeof(FILE_CLEAN_ENTRY);
    fileCleanHeader.ulNumber = min(fileCleanHeader.ulNumber, (DWORD)uRealEntryCount);
    fileCleanHeader.ulNumber = min(fileCleanHeader.ulNumber, BOOT_CHECK_MAX_ENTRY_LIMIT);



    for (DWORD i = 0; i < fileCleanHeader.ulNumber; ++i)
    {
        FILE_CLEAN_ENTRY readEntry;
        hr = hCfgFile.Read(&readEntry, sizeof(readEntry));
        if (FAILED(hr))
            return S_FALSE;

        // ǿ��0������
        readEntry.wstrFilePath[_countof(readEntry.wstrFilePath) - 1] = L'\0';

        CString strFilePath = readEntry.wstrFilePath;
        strFilePath.MakeLower();
        fileList.SetAt(strFilePath, 0);
    }



    return S_OK;
}