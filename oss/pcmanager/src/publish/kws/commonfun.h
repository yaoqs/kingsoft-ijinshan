/* -------------------------------------------------------------------------
// �ļ���		:	common/commonfun.h
// ������		:	chenghui
// ����ʱ��		:	2009-4-1 13:47:35
// ��������     :	
//
// $Id: $
// -----------------------------------------------------------------------*/
#ifndef __COMMON_COMMONFUN_H__
#define __COMMON_COMMONFUN_H__

#include <direct.h>
#include <Shlobj.h>
#include <string>
using std::wstring;

// -------------------------------------------------------------------------
void MakeDirEx(LPCSTR szPathDir);
void MakeDirEx(LPCWSTR szPathDir);

// ��ȡAllUser�û�Ŀ¼���
BOOL GetAllUserPath(WCHAR* strPath, size_t nSize);
BOOL GetAllUserPathA(CHAR* strPath, size_t nSize);

// ��ȡAllUser��KWS��Ŀ¼
BOOL GetAllUserKWSPath(WCHAR* strPath, size_t nSize);
BOOL GetAllUserKWSPathA(CHAR* strPath, size_t nSize);

// ��ȡALLUser��KCLT��Ŀ¼
BOOL GetAllUserKISKCLTPathA(CHAR* strPath, size_t nSize);
BOOL GetAllUserKISKCLTPathW(WCHAR* strPath, size_t nSize);

// ��ȡAllUser��KWS��LogĿ¼
BOOL GetAllUserKWSLogPath(WCHAR* strPath, size_t nSize);
namespace KWS
{
BOOL IsFileExist(LPCWSTR strFile);
}
BOOL IsFileExistA(LPCSTR strFile);

BOOL IsDirExist(LPCWSTR strDir);
BOOL IsDirExistA(LPCSTR strDir);

// �Ƿ�װ�˼�����
namespace KWS
{
	BOOL IsKsmExist();
}

// ��ȡ��ǰ��������Ŀ¼
wstring GetModuleDirW();

// ��ȡ��������Ŀ¼
wstring GetQuickLaunchDir();

/// �������ƶ���ʶ�Ƿ���ע�����
bool IsMoveFileExInfoInReg();

//��ȡ�û�UUID,��׼��{00000000-0000-0000-0000-000000000000}��ʽ,�ú����Ỻ����ǰ��ֵ
BOOL    GetKwsUserUUID(wstring& wstrUserUUID);

//��HKEY_CLASSES_ROOT��APPID��CLSID�����½�����,Ĭ��������������
BOOL    RegWriteKwsDefaultBrowserPath(const wstring& wstrKwsDefaultBrowserPath);

// ȡ�õ�ǰϵͳʱ��
std::wstring GetSysDateString();

BOOL	GetProIDByName(LPCTSTR szProName, DWORD & dwPID);

BOOL    RegSetStartPage(PCWCH pcwszUrl, HKEY hKey);

BOOL    CheckLockFlag();

BOOL    SetLockFlag(PCWCH pcwszUrl, BOOL bLocked);
// -------------------------------------------------------------------------
// $Log: $

#endif /* __COMMON_COMMONFUN_H__ */
