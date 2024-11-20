/**
* @file    bootreplacetool.h
* @brief   ...
* @author  zhangjun
* @date    2009-10-16 14:00
*/

#ifndef BOOTREPLACETOOL_H
#define BOOTREPLACETOOL_H

#include <windows.h>
#include <atlcoll.h>
#include <atlstr.h>
#include "safeapi\bootcheckstruct.h"
#include "safeapi\bcdef.h"

NS_SAFEAPI_BEGIN

class CBootReplaceTool
{
public:

	// ÿ���滻ǰ,�������滻ǰ���ô˺���ȷ�������Ѱ�װ
	// ���û��ж������Ƿ��Ѱ�װ
	// ��װǰ��������ǩ��,���ж�Ҫ��װ�����İ汾�Ƿ�Ⱦ�������
	//HRESULT InstallDriver(LPCWSTR lpszDriverPath);

	//HRESULT UninstallDriver();

	HRESULT BootReplaceFile(LPCWSTR lpszDestFilePath, LPCWSTR lpszSrcFilePath);


	//HRESULT         CopyDriverIfNew(LPCWSTR lpszNewDriver);

	//ULARGE_INTEGER  GetDllVersion(LPCWSTR lpszFilePath);

	// ɾ��bootclean�����ļ�
	//HRESULT         RemoveConfigFile();


public:

	HRESULT GetDriverPath(WCHAR szSystemDriver[MAX_PATH + 1], LPCWSTR lpszConfigName);

	HRESULT BootFillEntry(FILE_REPLACE_ENTRY& entry, LPCWSTR lpszDestFilePath, LPCWSTR lpszSrcFilePath);

	HRESULT BootAddToConfigFile(LPCWSTR lpszConfigName, LPCWSTR lpszDestFilePath, LPCWSTR lpszSrcFilePath);

	// CAtlMap<CString, CString>��Ӧ��ϵ<destFilePath, srcFilePath>,ȷ��destFilePathΪkey
	HRESULT BootRemoveFromConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, CString>& removeList);

	HRESULT BootSaveConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, CString>& writeList);

	HRESULT BootLoadConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, CString>& fileList);
};

NS_SAFEAPI_END

#endif//BOOTREPLACETOOL_H