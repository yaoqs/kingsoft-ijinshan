/**
* @file    bootreplacetool.cpp
* @brief   ...
* @author  zhangjun
* @date    2009-10-16 14:00
*/

#include "stdafx.h"
#include "bootreplacetool.h"

#include <atlbase.h>
#include <atlpath.h>
#include <atlfile.h>

#include "encryptfile.h"

#pragma warning(disable: 4996)

using namespace SafeApi;
#pragma comment(lib, "Version.lib")

#define BOOT_CHECK_MAX_ENTRY_LIMIT  65535

//HRESULT CBootReplaceTool::InstallDriver(LPCWSTR lpszDriverPath)
//{
//	// �����������,����֮
//	HRESULT hr = CopyDriverIfNew(lpszDriverPath);
//	if (FAILED(hr))
//		return hr;
//
//
//	// ��ȡϵͳĿ¼
//	WCHAR szSystemDriver[MAX_PATH + 1];
//	UINT  uRet = ::GetSystemDirectory(szSystemDriver, MAX_PATH);
//	if (!uRet)
//		return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//
//	::PathAppend(szSystemDriver, L"Drivers");
//	::PathAppend(szSystemDriver, BC_DriverFileName);
//
//
//
//	// ������·�����мӹ�,�԰����ո��·��������(��MSDN)
//	CPath quotedPathDriver = szSystemDriver;
//	quotedPathDriver.QuoteSpaces();
//
//
//
//	// ��װ����/�޸���������
//	SC_HANDLE hScm = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
//	if (NULL == hScm)
//		return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//
//
//
//	SC_HANDLE hService = ::OpenService(hScm, BC_ServiceName, SC_MANAGER_ALL_ACCESS);
//	if (hService)
//	{
//		BOOL bRet = ::ChangeServiceConfig(
//			hService,
//			SERVICE_KERNEL_DRIVER, 
//			SERVICE_BOOT_START,
//			SERVICE_ERROR_NORMAL,
//			quotedPathDriver.m_strPath,
//			BC_ServiceGroup,
//			NULL,
//			NULL,
//			NULL,
//			NULL,
//			NULL);
//		if (!bRet)
//		{
//			::CloseServiceHandle(hService);
//			::CloseServiceHandle(hScm);
//			return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//		}
//	}
//	else
//	{
//		hService = ::CreateService(
//			hScm,
//			BC_ServiceName,
//			BC_ServiceName,
//			SERVICE_ALL_ACCESS,
//			SERVICE_KERNEL_DRIVER,
//			SERVICE_BOOT_START,
//			SERVICE_ERROR_NORMAL,
//			quotedPathDriver.m_strPath,
//			BC_ServiceGroup,
//			NULL,
//			NULL,
//			NULL,
//			NULL);
//		if (NULL == hService)
//		{
//			::CloseServiceHandle(hScm);
//			return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//		}
//	}
//
//
//
//	::CloseServiceHandle(hService);
//	::CloseServiceHandle(hScm);
//	return S_OK;
//}
//
//HRESULT CBootReplaceTool::UninstallDriver()
//{
//	WCHAR szConfigFile[MAX_PATH + 1];
//	::GetSystemDirectory(szConfigFile, MAX_PATH);
//	::PathAppend(szConfigFile, FileBootCleanConfigFileName);
//	::DeleteFile(szConfigFile);
//
//	::GetSystemDirectory(szConfigFile, MAX_PATH);
//	::PathAppend(szConfigFile, FileBootReplaceConfigFileName);
//	::DeleteFile(szConfigFile);
//
//	::GetSystemDirectory(szConfigFile, MAX_PATH);
//	::PathAppend(szConfigFile, RegBootCleanConfigFileName);
//	::DeleteFile(szConfigFile);
//
//	::GetSystemDirectory(szConfigFile, MAX_PATH);
//	::PathAppend(szConfigFile, DriverApprovedConfigFileName);
//	::DeleteFile(szConfigFile);
//
//	::GetSystemDirectory(szConfigFile, MAX_PATH);
//	::PathAppend(szConfigFile, DriverBlockedConfigFileName);
//	::DeleteFile(szConfigFile);
//
//
//	// ж������
//	SC_HANDLE hScm = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
//	if (NULL == hScm)
//		return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//
//
//	SC_HANDLE hService = ::OpenService(hScm, BC_ServiceName, SC_MANAGER_ALL_ACCESS);
//	if (NULL == hScm)
//	{
//		::CloseServiceHandle(hScm);
//		return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//	}
//
//
//	// ��֧��ֹͣ
//	//SERVICE_STATUS status;
//	//BOOL bStopService = ::ControlService(hService, SERVICE_CONTROL_STOP, &status);
//	//if (!bStopService)
//	//{
//	//    ::CloseServiceHandle(hService);
//	//    ::CloseServiceHandle(hScm);
//	//    return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//	//}
//
//
//	BOOL bDeleteService = ::DeleteService(hService);
//	if (!bDeleteService)
//	{
//		::CloseServiceHandle(hService);
//		::CloseServiceHandle(hScm);
//		return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//	}
//
//
//	WCHAR szDriverFile[MAX_PATH + 1];
//	::GetSystemDirectory(szDriverFile, MAX_PATH);
//	::PathAppend(szDriverFile, L"Drivers");
//	::PathAppend(szDriverFile, BC_DriverFileName);
//	::DeleteFile(szDriverFile);
//
//
//	::CloseServiceHandle(hService);
//	::CloseServiceHandle(hScm);
//	return S_OK;
//}

HRESULT CBootReplaceTool::BootReplaceFile(LPCWSTR lpszDestFilePath, LPCWSTR lpszSrcFilePath)
{
	return BootAddToConfigFile(FileBootReplaceConfigFileName, lpszDestFilePath, lpszSrcFilePath);
}

//HRESULT CBootReplaceTool::CopyDriverIfNew(LPCWSTR lpszNewDriver)
//{
//	WCHAR szOldDriver[MAX_PATH + 1];
//	UINT  uRet = ::GetSystemDirectory(szOldDriver, MAX_PATH);
//	if (!uRet)
//		return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//
//
//	::PathAppend(szOldDriver, L"Drivers");
//	::PathAppend(szOldDriver, BC_DriverFileName);
//
//
//	ULARGE_INTEGER uiOldVersion = GetDllVersion(szOldDriver);
//	ULARGE_INTEGER uiNewVersion = GetDllVersion(lpszNewDriver);
//
//
//	if (uiNewVersion.QuadPart <= uiOldVersion.QuadPart)
//		return S_FALSE; // ����Ҫ����
//
//
//	// �������µİ汾
//	BOOL br = ::CopyFile(lpszNewDriver, szOldDriver, FALSE);
//	if (!br)
//		return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//
//
//	return S_OK;
//}
//
//ULARGE_INTEGER CBootReplaceTool::GetDllVersion(LPCWSTR lpszFilePath)
//{
//	BOOL  bRet              = FALSE;
//	DWORD dwHandle          = 0;
//	DWORD dwFileInfoSize    = 0;
//	VS_FIXEDFILEINFO *pFixFileInfo = NULL;
//	TCHAR *pszFileInfo      = NULL;
//	UINT  uLen              = 0;
//	ULARGE_INTEGER uiVersion;
//	uiVersion.HighPart = 0;
//	uiVersion.LowPart  = 0;
//
//	dwFileInfoSize = ::GetFileVersionInfoSize(lpszFilePath, &dwHandle);
//	if (dwFileInfoSize == 0)
//		goto Exit0;      
//
//	pszFileInfo = new TCHAR[dwFileInfoSize];
//	if (pszFileInfo == NULL)
//		goto Exit0;      
//
//	bRet = ::GetFileVersionInfo(lpszFilePath, dwHandle, dwFileInfoSize, pszFileInfo);
//	if (!bRet)
//		goto Exit0;
//
//	bRet = ::VerQueryValue(pszFileInfo, _T("\\"), (LPVOID *)&pFixFileInfo, &uLen);
//	if (!bRet)
//		goto Exit0;
//
//	if (uLen > 0)
//	{
//		uiVersion.HighPart = pFixFileInfo->dwFileVersionMS;
//		uiVersion.LowPart  = pFixFileInfo->dwFileVersionLS;
//	}
//
//
//Exit0:
//	if (pszFileInfo)
//	{
//		delete pszFileInfo;
//		pszFileInfo = NULL;
//	}
//
//	return uiVersion;
//}
//
//HRESULT CBootReplaceTool::RemoveConfigFile()
//{
//	WCHAR szConfigPath[MAX_PATH + 1];
//	UINT  uRet = ::GetSystemDirectory(szConfigPath, MAX_PATH);
//	if (!uRet)
//		return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//
//
//	::PathAppend(szConfigPath, FileBootReplaceConfigFileName);
//
//
//	BOOL br = ::DeleteFile(szConfigPath);
//	if (!br)
//		return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
//
//
//	return S_OK;
//}

HRESULT CBootReplaceTool::GetDriverPath(WCHAR szSystemDriver[MAX_PATH + 1], LPCWSTR lpszConfigName)
{
	// ��ȡϵͳĿ¼
	UINT  uRet = ::GetSystemDirectory(szSystemDriver, MAX_PATH);
	if (!uRet)
		return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


	::PathAppend(szSystemDriver, lpszConfigName);
	return S_OK;
}

HRESULT CBootReplaceTool::BootFillEntry(FILE_REPLACE_ENTRY& entry, LPCWSTR lpszDestFilePath, LPCWSTR lpszSrcFilePath)
{
	// ����ɾ����
	memset(&entry, 0, sizeof(FILE_REPLACE_ENTRY));
	// �����,��ȥ��unicodeǰ׺
	if (0 == StrCmpNW(lpszSrcFilePath, L"\\\\?\\", 4))
	{
		lpszSrcFilePath += 4;
	}

	if (0 == StrCmpNW(lpszDestFilePath, L"\\\\?\\", 4))
	{
		lpszDestFilePath += 4;
	}

	// ���û��,������ں�·��ǰ׺
	if (0 != StrCmpNW(lpszSrcFilePath, L"\\??\\", 4))
	{
		wcsncpy(entry.wstrFileFrom,     L"\\??\\",    4);
		wcsncpy(entry.wstrFileFrom + 4, lpszSrcFilePath,  _countof(entry.wstrFileFrom) - 4);
	}
	else
	{
		wcsncpy(entry.wstrFileFrom, lpszSrcFilePath, _countof(entry.wstrFileFrom));
	}

	if (0 != StrCmpNW(lpszDestFilePath, L"\\??\\", 4))
	{
		wcsncpy(entry.wstrFileTo,     L"\\??\\",    4);
		wcsncpy(entry.wstrFileTo + 4, lpszDestFilePath,  _countof(entry.wstrFileTo) - 4);
	}
	else
	{
		wcsncpy(entry.wstrFileTo, lpszDestFilePath, _countof(entry.wstrFileTo));
	}

	// ȷ��������
	entry.wstrFileFrom[_countof(entry.wstrFileFrom) - 1] = L'\0';
	CharLower(entry.wstrFileFrom);

	entry.wstrFileTo[_countof(entry.wstrFileTo) - 1] = L'\0';
	CharLower(entry.wstrFileTo);

	// md5û��ʹ��,���ﲻ��дmd5
	return S_OK;
}

HRESULT CBootReplaceTool::BootAddToConfigFile(LPCWSTR lpszConfigName, LPCWSTR lpszDestFilePath, LPCWSTR lpszSrcFilePath)
{
	if (!lpszConfigName || !*lpszConfigName)
		return E_INVALIDARG;

	if (!lpszSrcFilePath || !*lpszSrcFilePath || !lpszDestFilePath || !*lpszDestFilePath)
		return S_FALSE;


	// ��ȡϵͳĿ¼
	WCHAR szSystemDriver[MAX_PATH + 1];
	HRESULT hr = GetDriverPath(szSystemDriver, lpszConfigName);
	if (FAILED(hr))
		return hr;



	// ��ȡ�����ļ�
	CAtlMap<CString, CString> fileList;
	BootLoadConfigFile(lpszConfigName, fileList);


	// �����,��ȥ��unicodeǰ׺
	FILE_REPLACE_ENTRY replaceEntry;
	BootFillEntry(replaceEntry, lpszDestFilePath, lpszSrcFilePath);
	CString t_csDestFile = replaceEntry.wstrFileTo;
	CString t_csSrcFile  = replaceEntry.wstrFileFrom;

	// ����Ƿ���ָ������Ŀ
	if (fileList.Lookup(t_csDestFile))
		return S_FALSE;


	// �����Ŀ
	fileList.SetAt(t_csDestFile, t_csSrcFile);


	// ���������ļ�
	return BootSaveConfigFile(lpszConfigName, fileList);
}

HRESULT CBootReplaceTool::BootRemoveFromConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, CString>& removeList)
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
	CAtlMap<CString, CString> fileList;
	BootLoadConfigFile(lpszConfigName, fileList);


	// ɾ��ָ������Ŀ
	for (POSITION pos = removeList.GetStartPosition(); pos; removeList.GetNext(pos))
	{
		CString t_csDestFile = removeList.GetKeyAt(pos);
		// �����,��ȥ��unicodeǰ׺
		FILE_REPLACE_ENTRY replaceEntry;
		BootFillEntry(replaceEntry, t_csDestFile, t_csDestFile); // note:����Ϊ����srcFile����Ҳ��destFile

		// ɾ��ָ����Ŀ
		fileList.RemoveKey(replaceEntry.wstrFileTo);
	}


	// ���������ļ�
	return BootSaveConfigFile(lpszConfigName, fileList);
}

HRESULT CBootReplaceTool::BootSaveConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, CString>& writeList)
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
	FILE_REPLACE_HEADER fileReplaceHeader;
	memset(&fileReplaceHeader, 0, sizeof(fileReplaceHeader));
	fileReplaceHeader.ulWindowsVersion = ::GetVersion();
	fileReplaceHeader.ulNumber         = (DWORD)writeList.GetCount();

	hr = hCfgFile.Write(&fileReplaceHeader, sizeof(fileReplaceHeader));
	if (FAILED(hr))
	{
		::DeleteFile(strBackup);
		return hr;
	}



	// ����������Ŀ
	POSITION pos = writeList.GetStartPosition();
	for (NULL; pos; writeList.GetNext(pos))
	{
		FILE_REPLACE_ENTRY entry;
		CString t_csDestFile = writeList.GetKeyAt(pos);
		CString t_csSrcFile  = writeList.GetValueAt(pos);
		BootFillEntry(entry, t_csDestFile, t_csSrcFile);

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

HRESULT CBootReplaceTool::BootLoadConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, CString>& fileList)
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




	FILE_REPLACE_HEADER fileReplaceHeader;
	memset(&fileReplaceHeader, 0, sizeof(fileReplaceHeader));



	ULONGLONG uFileSize = 0;
	hr = hCfgFile.GetSize(uFileSize);
	if (FAILED(hr))
		return S_FALSE;


	hr = hCfgFile.Read(&fileReplaceHeader, sizeof(fileReplaceHeader));
	if (FAILED(hr))
		return S_FALSE;


	if (uFileSize < sizeof(FILE_REPLACE_HEADER))
		return S_FALSE;



	// ����ļ���С����Ϣͷ�еĸ����Ƿ��Ǻ�
	// ͬʱ����entry��Ŀ
	ULONGLONG uRealEntryCount = (uFileSize - sizeof(FILE_REPLACE_HEADER)) / sizeof(FILE_REPLACE_HEADER);
	fileReplaceHeader.ulNumber = min(fileReplaceHeader.ulNumber, (DWORD)uRealEntryCount);
	fileReplaceHeader.ulNumber = min(fileReplaceHeader.ulNumber, BOOT_CHECK_MAX_ENTRY_LIMIT);



	for (DWORD i = 0; i < fileReplaceHeader.ulNumber; ++i)
	{
		FILE_REPLACE_ENTRY readEntry;
		CString t_csDestFile, t_csSrcFile;
		hr = hCfgFile.Read(&readEntry, sizeof(readEntry));
		if (FAILED(hr))
			return S_FALSE;

		// ǿ��0������
		readEntry.wstrFileFrom[_countof(readEntry.wstrFileFrom) - 1] = L'\0';
		readEntry.wstrFileTo[_countof(readEntry.wstrFileTo) - 1] = L'\0';

		CharLower(readEntry.wstrFileFrom);
		CharLower(readEntry.wstrFileTo);

		t_csDestFile = readEntry.wstrFileTo;
		t_csSrcFile  = readEntry.wstrFileFrom;
		fileList.SetAt(t_csDestFile, t_csSrcFile);
	}



	return S_OK;
}