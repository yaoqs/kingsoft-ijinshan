/**
* @file    bootchecktool.h
* @brief   ...
* @author  bbcallen
* @date    2009-07-31 11:46
*/

#ifndef BOOTCHECKTOOL_H
#define BOOTCHECKTOOL_H

#include <windows.h>
#include <atlcoll.h>
#include <atlstr.h>
#include "bootcheckstruct.h"
#include "bcdef.h"

NS_SAFEAPI_BEGIN

class CBootCheckTool
{
public:

    // ÿ�����ǰ,���������ǰ���ô˺���ȷ�������Ѱ�װ
    // ���û��ж������Ƿ��Ѱ�װ
    // ��װǰ��������ǩ��,���ж�Ҫ��װ�����İ汾�Ƿ�Ⱦ�������
    HRESULT InstallDriver(LPCWSTR lpszDriverPath);

    HRESULT UninstallDriver();

    HRESULT BootDeleteFile(LPCWSTR lpszFilePath);

    HRESULT BootOccupyFile(LPCWSTR lpszFilePath);


    HRESULT BootLoadOccupyFile(CAtlMap<CString, DWORD>& fileList);


    HRESULT         CopyDriverIfNew(LPCWSTR lpszNewDriver);

    ULARGE_INTEGER  GetDllVersion(LPCWSTR lpszFilePath);

    // ɾ��bootclean�����ļ�
    HRESULT         RemoveConfigFile();


public:

    HRESULT GetDriverPath(WCHAR szSystemDriver[MAX_PATH + 1], LPCWSTR lpszConfigName);

    HRESULT BootFillEntry(FILE_CLEAN_ENTRY& entry, LPCWSTR lpszFilePath);

    HRESULT BootAddToConfigFile(LPCWSTR lpszConfigName, LPCWSTR lpszFilePath);

    HRESULT BootRemoveFromConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, DWORD>& removeList);

    HRESULT BootSaveConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, DWORD>& writeList);

    HRESULT BootLoadConfigFile(LPCWSTR lpszConfigName, CAtlMap<CString, DWORD>& fileList);
};

NS_SAFEAPI_END

#endif//BOOTCHECKTOOL_H