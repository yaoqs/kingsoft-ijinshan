//////////////////////////////////////////////////////////////////////////
// FileName:	GetRegistry.cpp
// Author:		Jonathan Xiang
// DateTime:	April 18th, 2008
// Description:
//////////////////////////////////////////////////////////////////////////

#include "GetRegistry.h"



//////////////////////////////////////////////////////////////////////////
// ��ȡע����ֵ������
// Return value:
//	true	: succeeded
//	false	: failed
//////////////////////////////////////////////////////////////////////////

bool GetRegValueType(HKEY hRootKey, const TCHAR* lpszKeyName, const TCHAR* lpszValueName, LPDWORD lpdwType)
{
	bool		bReturn = false;
	HKEY		hKey = NULL;
	LONG		lResult = ERROR_SUCCESS;

	if ( lpdwType == static_cast<DWORD *>(0) )
	{
		bReturn = false;
		goto Label_Ret;
	}

	// ���Ӽ�
	hKey = NULL;
	lResult = ::RegOpenKeyEx(
		hRootKey, 
		lpszKeyName, 
		0, 
		KEY_QUERY_VALUE | KEY_READ,
		&hKey);
	if (lResult != ERROR_SUCCESS)
	{
		bReturn = false;
		goto Label_Ret;
	}

	// ��ѯ��ֵ����
	*lpdwType = REG_SZ;
	lResult = ::RegQueryValueEx(
		hKey,
		lpszValueName,
		NULL,
		lpdwType,
		NULL,
		NULL);
	if (lResult != ERROR_SUCCESS)
	{
		bReturn = false;
		goto Label_Ret;
	}

	bReturn = true;

Label_Ret:
	if (hKey != NULL)
		::RegCloseKey(hKey);

	return bReturn;

}


//////////////////////////////////////////////////////////////////////////
// ��ȡע����ֵ���ݵĳ��ȡ� 
// ����REG_SZ, REG_EXPAND_SZ���ͣ��˳��Ȱ�����β��'\0'; ����REG_MULTI_SZ, �˳��Ȱ������е�'\0'    
// Return value:
//	true	: succeeded
//	false	: failed
//////////////////////////////////////////////////////////////////////////

bool GetRegValueLength(HKEY hRootKey, const TCHAR* lpszKeyName, const TCHAR* lpszValueName, LPDWORD lpcbData)
{
	bool		bReturn = false;
	HKEY		hKey = NULL;
	LONG		lResult = ERROR_SUCCESS;
	
	// ��鴫���ָ���Ƿ���Ч
	if ( lpcbData == static_cast<DWORD *>(0) )
	{
		bReturn = false;
		goto Label_Ret;
	}

	// ���Ӽ�
	hKey = NULL;
	lResult = ::RegOpenKeyEx(
		hRootKey, 
		lpszKeyName, 
		0, 
		KEY_QUERY_VALUE | KEY_READ,
		&hKey);
	if (lResult != ERROR_SUCCESS)
	{
		bReturn = false;
		goto Label_Ret;
	}

	// ��ѯ��ֵ���ݳ��ȡ�����REG_SZ, REG_EXPAND_SZ���ͣ��˳��Ȱ�����β��'\0'; ����REG_MULTI_SZ, �˳��Ȱ������е�'\0'
	*lpcbData = 0;
	lResult = ::RegQueryValueEx(
		hKey,
		lpszValueName,
		NULL,
		NULL,
		NULL,
		lpcbData);
	if (lResult != ERROR_SUCCESS)
	{
		bReturn = false;
		goto Label_Ret;
	}

	bReturn = true;

Label_Ret:
	if (hKey != NULL)
		::RegCloseKey(hKey);

	return bReturn;

}


//////////////////////////////////////////////////////////////////////////
// ��ȡע����ֵ������
// Return value:
//	true	: succeeded
//	false	: failed
//////////////////////////////////////////////////////////////////////////

bool GetRegValueData(HKEY hRootKey, const TCHAR* lpszKeyName, const TCHAR* lpszValueName, LPBYTE lpData, DWORD cbData)
{
	bool		bReturn = false;
	HKEY		hKey = NULL;
	LONG		lResult = ERROR_SUCCESS;
	DWORD		dwType  = REG_SZ;

	if ( lpData == static_cast<BYTE *>(0) )
	{
		bReturn = false;
		goto Label_Ret;
	}

	// ���Ӽ�
	hKey = NULL;
	lResult = ::RegOpenKeyEx(
		hRootKey, 
		lpszKeyName, 
		0, 
		KEY_QUERY_VALUE | KEY_READ,
		&hKey);
	if (lResult != ERROR_SUCCESS)
	{
		bReturn = false;
		goto Label_Ret;
	}

	// ��ѯ��ֵ
	::memset(lpData, 0, cbData);
	lResult = ::RegQueryValueEx(
		hKey,
		lpszValueName,
		NULL,
		&dwType,
		(LPBYTE)lpData,
		&cbData);
	if (lResult != ERROR_SUCCESS)
	{
		bReturn = false;
		goto Label_Ret;
	}

	bReturn = true;

Label_Ret:
	if (hKey != NULL)
		::RegCloseKey(hKey);

	return bReturn;
}


//////////////////////////////////////////////////////////////////////////
// ��ȡע����ֵ���е�����
// Return value:
//	true	: succeeded
//	false	: failed
//////////////////////////////////////////////////////////////////////////

bool GetRegValueAll(HKEY hRootKey, 
                  const TCHAR* lpszKeyName, 
                  const TCHAR* lpszValueName, 
                  LPDWORD lpdwType, 
                  LPBYTE lpData, 
                  LPDWORD lpcbData,
                  Wow64Type wow64type)
{
	bool		bReturn = false;
	HKEY		hKey = NULL;
	LONG		lResult = ERROR_SUCCESS;


	if ( lpData != static_cast<LPBYTE>(0) && lpcbData == static_cast<LPDWORD>(0) )
	{
		bReturn = true;
		goto Label_Ret;
	}

	// ���Ӽ�
	hKey = NULL;
	lResult = ::RegOpenKeyEx(
		hRootKey, 
		lpszKeyName, 
		0, 
		KEY_QUERY_VALUE | KEY_READ | GetRegAccess(wow64type),
		&hKey);
	if (lResult != ERROR_SUCCESS)
	{
		bReturn = false;
		goto Label_Ret;
	}

	// ��ѯ��ֵ
	if ( lpData != static_cast<LPBYTE>(0) )
		::memset(lpData, 0, *lpcbData);

	if ( lpdwType != static_cast<LPDWORD>(0) )
		*lpdwType = REG_SZ;

	lResult = ::RegQueryValueEx(
		hKey,
		lpszValueName,
		NULL,
		lpdwType,
		(LPBYTE)lpData,
		lpcbData);
	if (lResult != ERROR_SUCCESS)
	{
		bReturn = false;
		goto Label_Ret;
	}

	bReturn = true;

Label_Ret:
	if (hKey != NULL)
		::RegCloseKey(hKey);

	return bReturn;
}
