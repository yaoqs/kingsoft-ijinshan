//////////////////////////////////////////////////////////////////////////
//
//
//
//
//////////////////////////////////////////////////////////////////////////

#include "EnumRegistry.h"


// ʹ�ûص�����������������Ӽ��������Ӽ�

//////////////////////////////////////////////////////////////////////////
// ʹ�ûص�����������������Ӽ��������Ӽ�
bool EnumRegSubKey(HKEY hRootKey, const TCHAR* lpszKeyName, ENUMREGSUBKEYPROC fnProc)
{
	bool		bReturn = false;
	bool		bResult = false;
	HKEY		hKey = NULL;
	LONG		lResult = ERROR_SUCCESS;
	DWORD		dwNumKey = 0;
	DWORD		cbMaxKeyNameLen = 0;
	DWORD		cbKeyName = 0;
	int			i = 0;
	TCHAR*		lpszSubKeyName = NULL;

	// ���ص�����
	if ( fnProc == static_cast<ENUMREGSUBKEYPROC>(NULL) )
	{
		bReturn = true;
		goto Label_Ret;
	}

	// ��Ҫö�ٵ��Ӽ�
	hKey = NULL;
	lResult = ::RegOpenKeyEx(hRootKey, 
		lpszKeyName, 
		0, 
		KEY_QUERY_VALUE | KEY_READ,
		&hKey);
	if (lResult != ERROR_SUCCESS)
	{
		bReturn = false;
		goto Label_Ret;
	}

	// ��ѯ�Ӽ�����Ŀ
	dwNumKey = 0;
	lResult = ::RegQueryInfoKey(hKey,
		NULL, NULL, 
		NULL, 
		&dwNumKey, &cbMaxKeyNameLen, 
		NULL, 
		NULL, NULL, NULL, 
		NULL, 
		NULL);
	if (lResult != ERROR_SUCCESS)
	{
		bReturn = false;
		goto Label_Ret;
	}

	// Ϊ�Ӽ��������ڴ�
	lpszSubKeyName = new TCHAR[cbMaxKeyNameLen + 1];

	// ���������Ӽ�
	bReturn = true;
	for (i = 0; i < (int)dwNumKey; ++i)
	{
		::memset(lpszSubKeyName, 0, cbMaxKeyNameLen + 1);
		cbKeyName = cbMaxKeyNameLen + 1;

		lResult = ::RegEnumKeyEx(hKey, 
			(DWORD)i, 
			lpszSubKeyName, 
			&cbKeyName,
			NULL,
			NULL, 
			NULL, 
			NULL);
		if (lResult != ERROR_SUCCESS)
		{
			bReturn = false;
			break;
		}

		// ���ûص�����������ȡ���Ӽ���
		bResult = (*fnProc)(hKey, lpszSubKeyName);
		if ( !bResult )
		{
			break;
		}

	} // for i


Label_Ret:
	if (hKey != NULL)
		::RegCloseKey(hKey);

	if (lpszSubKeyName != NULL)
		delete [] lpszSubKeyName;

	return bReturn;
}



//////////////////////////////////////////////////////////////////////////
// ����ע���ĳ�Ӽ��µ����м�ֵ 
//////////////////////////////////////////////////////////////////////////

bool EnumRegValue(HKEY hRootKey, const TCHAR* lpszKeyName, ENUMREGVALUEPROC fnProc)
{
	bool		bReturn = false;
	bool		bResult = false;
	HKEY		hKey = NULL;
	LONG		lResult = ERROR_SUCCESS;
	DWORD		dwNumValue = 0;
	DWORD		cbValueName = 0;
	DWORD		cbMaxValueNameLen = 0;
	DWORD		cbData = 0;
	DWORD		cbMaxValueDataLen = 0;
	int			i = 0;
	DWORD		dwType  = REG_SZ;
	TCHAR*		lpszValueName = NULL;
	TCHAR*		lpszValueData = NULL;

	// ��鴫��Ļص�����
	if ( fnProc == static_cast<ENUMREGVALUEPROC>(NULL) )
	{
		bReturn = true;
		goto Label_Ret;
	}

	// ��Ҫö�ٵ��Ӽ�
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

	// ��ѯ��ֵ����Ŀ
	dwNumValue = 0;
	lResult = ::RegQueryInfoKey(
		hKey,
		NULL, NULL, 
		NULL, 
		NULL, NULL, 
		NULL, 
		&dwNumValue, &cbMaxValueNameLen, &cbMaxValueDataLen, 
		NULL, 
		NULL);
	if (lResult != ERROR_SUCCESS)
	{
		bReturn = false;
		goto Label_Ret;
	}

	// Ϊ��ֵ���ͼ�ֵ���ݷ����ڴ�
	lpszValueName = new TCHAR[cbMaxValueNameLen + 1];
	lpszValueData = new TCHAR[cbMaxValueDataLen + 1];

	// �������м�ֵ
	bReturn = true;
	for (i = 0; i < (int)dwNumValue; ++i)
	{
		::memset(lpszValueName, 0, cbMaxValueNameLen + 1);
		::memset(lpszValueData, 0, cbMaxValueDataLen + 1);

		cbValueName = cbMaxValueNameLen + 1;
		cbData = cbMaxValueDataLen + 1;

		lResult = ::RegEnumValue(
			hKey, 
			(DWORD)i, 
			lpszValueName, 
			&cbValueName,
			NULL,
			&dwType, 
			(LPBYTE)lpszValueData, 
			&cbData);
		if (lResult != ERROR_SUCCESS)
		{
			bReturn = false;
			break;
		}

		// ���ûص����������ֵ��
		bResult = (*fnProc)(hKey, lpszValueName, lpszValueData, dwType, cbData);
		if ( !bResult )
		{
			break;
		}
	} // for i

Label_Ret:
	if (hKey != NULL)
		::RegCloseKey(hKey);

	if (lpszValueName != NULL)
		delete [] lpszValueName;

	if (lpszValueData != NULL)
		delete [] lpszValueData;

	return bReturn;
}



bool EnumRegSubKey_WithCallBack(HKEY hRootKey, 
                            const TCHAR* lpszKeyName, 
                            ENUMREGSUBKEYPROC_WITHCALLBACK fnProc, 
                            LPVOID param,
                            Wow64Type wow64type
                            )
{
    bool		bReturn = false;
    bool		bResult = false;
    HKEY		hKey = NULL;
    LONG		lResult = ERROR_SUCCESS;
    DWORD		dwNumKey = 0;
    DWORD		cbMaxKeyNameLen = 0;
    DWORD		cbKeyName = 0;
    int			i = 0;
    TCHAR*		lpszSubKeyName = NULL;

    // ���ص�����
    if ( fnProc == static_cast<ENUMREGSUBKEYPROC_WITHCALLBACK>(NULL) )
    {
        bReturn = true;
        goto Label_Ret;
    }

    // ��Ҫö�ٵ��Ӽ�
    hKey = NULL;
    lResult = ::RegOpenKeyEx(hRootKey, 
        lpszKeyName, 
        0, 
        KEY_QUERY_VALUE | KEY_READ | GetRegAccess(wow64type),
        &hKey);
    if (lResult != ERROR_SUCCESS)
    {
        bReturn = false;
        goto Label_Ret;
    }

    // ��ѯ�Ӽ�����Ŀ
    dwNumKey = 0;
    lResult = ::RegQueryInfoKey(hKey,
        NULL, NULL, 
        NULL, 
        &dwNumKey, &cbMaxKeyNameLen, 
        NULL, 
        NULL, NULL, NULL, 
        NULL, 
        NULL);
    if (lResult != ERROR_SUCCESS)
    {
        bReturn = false;
        goto Label_Ret;
    }

    // Ϊ�Ӽ��������ڴ�
    lpszSubKeyName = new TCHAR[cbMaxKeyNameLen + 1];

    // ���������Ӽ�
    bReturn = true;
    for (i = 0; i < (int)dwNumKey; ++i)
    {
        ::memset(lpszSubKeyName, 0, cbMaxKeyNameLen + 1);
        cbKeyName = cbMaxKeyNameLen + 1;

        lResult = ::RegEnumKeyEx(hKey, 
            (DWORD)i, 
            lpszSubKeyName, 
            &cbKeyName,
            NULL,
            NULL, 
            NULL, 
            NULL);
        if (lResult != ERROR_SUCCESS)
        {
            bReturn = false;
            break;
        }

        // ���ûص�����������ȡ���Ӽ���
        bResult = (*fnProc)(hKey, lpszSubKeyName, param, wow64type);
        if ( !bResult )
        {
            break;
        }

    } // for i


Label_Ret:
    if (hKey != NULL)
        ::RegCloseKey(hKey);

    if (lpszSubKeyName != NULL)
        delete [] lpszSubKeyName;

    return bReturn;
}



//////////////////////////////////////////////////////////////////////////
// ����ע���ĳ�Ӽ��µ����м�ֵ 
//////////////////////////////////////////////////////////////////////////

bool EnumRegValue_WithCallBack(
    HKEY hRootKey, 
    const TCHAR* lpszKeyName, 
    ENUMREGVALUEPROC_WITHCALLBACK fnProc, 
    LPVOID param,
    Wow64Type wow64type
    )
{
    bool		bReturn = false;
    bool		bResult = false;
    HKEY		hKey = NULL;
    LONG		lResult = ERROR_SUCCESS;
    DWORD		dwNumValue = 0;
    DWORD		cbValueName = 0;
    DWORD		cbMaxValueNameLen = 0;
    DWORD		cbData = 0;
    DWORD		cbMaxValueDataLen = 0;
    int			i = 0;
    DWORD		dwType  = REG_SZ;
    TCHAR*		lpszValueName = NULL;
    TCHAR*		lpszValueData = NULL;

    // ��鴫��Ļص�����
    if ( fnProc == static_cast<ENUMREGVALUEPROC_WITHCALLBACK>(NULL) )
    {
        bReturn = true;
        goto Label_Ret;
    }

    // ��Ҫö�ٵ��Ӽ�
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

    // ��ѯ��ֵ����Ŀ
    dwNumValue = 0;
    lResult = ::RegQueryInfoKey(
        hKey,
        NULL, NULL, 
        NULL, 
        NULL, NULL, 
        NULL, 
        &dwNumValue, &cbMaxValueNameLen, &cbMaxValueDataLen, 
        NULL, 
        NULL);
    if (lResult != ERROR_SUCCESS)
    {
        bReturn = false;
        goto Label_Ret;
    }

    // Ϊ��ֵ���ͼ�ֵ���ݷ����ڴ�
    lpszValueName = new TCHAR[cbMaxValueNameLen + 1];
    lpszValueData = new TCHAR[cbMaxValueDataLen + 1];

    // �������м�ֵ
    bReturn = true;
    for (i = 0; i < (int)dwNumValue; ++i)
    {
        ::memset(lpszValueName, 0, cbMaxValueNameLen + 1);
        ::memset(lpszValueData, 0, cbMaxValueDataLen + 1);

        cbValueName = cbMaxValueNameLen + 1;
        cbData = cbMaxValueDataLen + 1;

        lResult = ::RegEnumValue(
            hKey, 
            (DWORD)i, 
            lpszValueName, 
            &cbValueName,
            NULL,
            &dwType, 
            (LPBYTE)lpszValueData, 
            &cbData);
        if (lResult != ERROR_SUCCESS)
        {
            bReturn = false;
            break;
        }

        // ���ûص����������ֵ��
        bResult = (*fnProc)(hKey, lpszValueName, lpszValueData, dwType, cbData, param, wow64type);
        if ( !bResult )
        {
            break;
        }
    } // for i

Label_Ret:
    if (hKey != NULL)
        ::RegCloseKey(hKey);

    if (lpszValueName != NULL)
        delete [] lpszValueName;

    if (lpszValueData != NULL)
        delete [] lpszValueData;

    return bReturn;
}