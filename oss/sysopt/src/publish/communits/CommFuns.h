/*
dummyz@126.com
*/
#ifndef _COMMFUNS_INC_
#define _COMMFUNS_INC_

#define ITEMS_COUNT(x) (sizeof (x) / sizeof (x[0]))
#define RETURN_ADDR(first_param) *((PVOID*)&first_param - 1)
#define ONE_MB_BYTES			(1024 * 1024)

inline BOOL IsValidPtrRange(LPCVOID p) // ֻ���ж�ָ��ָ�������Ƿ���Ч
{
	return (p == NULL) || (((ULONG_PTR)p > ONE_MB_BYTES) && ((ULONG_PTR)p < 0x7FFF0000));
}

#define DBG_FMT 0

#if DBG_FMT
void		DebugPrintf(LPCWSTR lpFormat, ...);
void		DebugPrintf(LPCSTR lpFormat, ...);
#else
#define		DebugPrintf(x, ...)
#endif

#define UNFLY_DEBUG_PRINT_LOG 0 // 0,�رյ�����־; 1,����������־
#define UNFLY_LOG_TO_FILE     0 // 0,���������Ϣ; 1,��ӡ���ļ�

#if UNFLY_DEBUG_PRINT_LOG
void UnflyLogA( char *format, ... );
#else
#define UnflyLogA(...) 
#endif

inline BOOL MyIsEmptyString(LPCTSTR lpStr)
{
	return (lpStr == NULL) || (*lpStr == 0);
}

inline BOOL MyIsClsidString(LPCTSTR lpStr)
{
	// ex: {FB3DAD64-A832-46a8-BBD4-4C0C431E09C8}
	const size_t nLen = _tcslen(lpStr);
	return (nLen >= 38) && 
		(lpStr[0] == _T('{')) && (lpStr[37] == _T('}')) &&
		(lpStr[9] == _T('-')) && (lpStr[14] == _T('-')) && (lpStr[19] == _T('-')) &&
		(lpStr[24] == _T('-'));
}

inline LPCTSTR MySkipWhite(LPCTSTR lpStr1)
{
	TCHAR c;
	while ( (c = *lpStr1) != 0 )
	{
		if ( c != _T(' ') && c != _T('\t') )
		{
			break;
		}

		lpStr1++;
	}

	return lpStr1;
}

inline LPCTSTR	MySkipNoWhite(LPCTSTR lpStr1)
{
	TCHAR c;
	while ( (c = *lpStr1) != 0 )
	{
		if ( c == _T(' ') || c == _T('\t') )
		{
			break;
		}

		lpStr1++;
	}

	return lpStr1;
}

inline BOOL MyCheckStringRange(LPCTSTR lpStr, LPVOID lpDataBegin, LPVOID lpDataEnd)
{
	if ( (PVOID)lpStr < lpDataBegin )
	{
		return FALSE;
	}

	while ( *lpStr != 0 )
	{
		if ( (PVOID)lpStr == lpDataEnd )
		{
			return FALSE;
		}

		lpStr++;
	}

	return TRUE;
}


LPCTSTR		MyStrStrI(LPCTSTR lpStr1, LPCTSTR lpStr2);

HKEY		MyOpenRegKey(HKEY hKey, LPCTSTR lpSubKey, BOOL bReadOnly);
void		MyCloseRegKey(HKEY hKey);
BOOL		MyReadRegValue(HKEY hKey, LPCTSTR lpValueName, LPTSTR lpValue, DWORD dwLength);
BOOL		MyReadRegValue(HKEY hKey, LPCTSTR lpValueName, LPDWORD lpdwValue);
BOOL		MyWriteRegValue(HKEY hKey, LPCTSTR lpValueName, LPCTSTR lpValue);
BOOL		MyWriteRegValue(HKEY hKey, LPCTSTR lpValueName, DWORD dwValue);

inline LPCTSTR MyGetExtName(LPCTSTR lpPath) {
	return _tcsrchr(lpPath, _T('.'));
}

inline BOOL MyIsValidFileName(LPCTSTR lpFileName)
{
	TCHAR c;
	while ( (c = *lpFileName) != 0 )
	{
		if ( _tcschr(_T("\\/:*?\"<>|"), c) != NULL )
		{
			return FALSE;
		}
		
		lpFileName++;
	}

	return TRUE;
}

LPCTSTR		MyGetFileDir(LPCTSTR lpPath, LPTSTR lpDir);
LPCTSTR		MyGetFileName(LPCTSTR lpPath);
LPCTSTR		MyAppendFileName(LPTSTR lpPath, LPCTSTR lpFileName);

DWORD		MyGetFileSize(LPCTSTR lpPath);
DWORD		MyGetOsVersion();
HICON		MyGetFileIconHandle(LPCTSTR lpFilePath);
DWORD		MyFindProcess(LPCTSTR lpName);
BOOL		MyGetModulePath(DWORD dwProcessId, LPTSTR lpPath);
ULARGE_INTEGER		MyGetProcessUniqID(HANDLE hProcess = NULL, DWORD dwProcessID = 0); // low=pid, hig=creattime


HRESULT		MyCoCreateInstance(LPCTSTR lpDll, const CLSID& rclsid, const IID& riid, void** ppv);

// 0 �����ڵ�·��
// 1 �ļ�·��
// 2 Ŀ¼·��
int			MyGetPathType(LPCTSTR lpPath);


BOOL		HaveInternetConnection();
BOOL		IsXPLast(); // �жϲ���ϵͳ�Ƿ��� xp �Ժ�İ汾������ xp��
BOOL		IsWin64();
BOOL		IsDownloadFile(LPCTSTR lpPath); // ͨ���ļ���ȫ�����ж��Ƿ������ص��ļ�
BOOL		IsPackerFile(LPCTSTR lpPath); // �Ƿ��Ǽӿǵ��ļ�
BOOL		IsRiskPath(LPCTSTR lpPath);
BOOL		IsPEFile(LPCTSTR lpPath);
BOOL		IsPE(LPVOID lpData, DWORD dwSize);

// ���ؽ������ delete ɾ��
LPWSTR		Ansi2Unicode(LPCSTR lpStr, DWORD nMaxLen = 0);
LPSTR		Unicode2Ansi(LPCWSTR lpStr, DWORD nMaxLen = 0);
LPSTR		ToUTF8Str(LPCSTR lpStr);
LPSTR		ToUTF8Str(LPCWSTR lpStr, DWORD nMaxLen = 0);
LPSTR		UTF8ToAnsi(LPCSTR lpStr);
LPSTR		ToBase64Str(LPCWSTR lpStr);
void		ToBase64Str(LPCWSTR lpStr, CString& strBase64);

BOOL		IsEquHostName(LPCTSTR lpUrl1, LPCTSTR lpUrl2);
CString		MyGetHostName(LPCTSTR lpUrl);

BOOL		IsFullScreen();

template <class T>T MD5ToStr(PBYTE lpMD5, T lpStr)
{
	T lp = lpStr;
	for ( int i = 0; i < 16; i++ )
	{
		BYTE t = lpMD5[i];
		*lp++ = "0123456789abcdef"[t >> 4];
		*lp++ = "0123456789abcdef"[t & 0xf];
	}
	*lp = 0;
	
	return lpStr;
}

template <class T>
BOOL ToHex(T a, int& r)
{
	r = *a;
	if ( r >= 'a' && r <= 'f' ) 
	{
		r = r - 'a' + 10;
	}
	else if ( r >= 'A' && r <= 'F' )
	{
		r = r - 'A' + 10;
	}
	else if ( r >= '0' && r <= '9' )
	{
		r -= '0';
	}
	else
	{
		return FALSE;
	}
	
	return TRUE;
}

template <class T>BOOL StrToMD5(T lpStr, PBYTE lpMD5)
{
	for ( int i = 0; i < 16; i++ )
	{
		int t1, t2;
		
		if ( ToHex(lpStr, t1) && ToHex(lpStr + 1, t2) )
		{
			lpMD5[i] = (t1 << 4) | t2;
			lpStr += 2;
		}
		else
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

// ���� md5
void CalcMD5(PVOID lpBuff, DWORD dwSize, LPBYTE lpMd5);
BOOL CalcFileMD5(LPCTSTR lpFilePath, LPBYTE lpMD5);


class CFunctionTime
{
public:
	CFunctionTime(LPCSTR lpName)
	{
		m_lpFunName = lpName;
		m_dwBeginTime = GetTickCount();
	}

	~CFunctionTime(void)
	{
		DWORD dwTime =  GetTickCount() - m_dwBeginTime;
		DebugPrintf("Function: %s Time: %d ms\n", m_lpFunName, dwTime);
	}

private:
	LPCSTR	m_lpFunName;
	DWORD	m_dwBeginTime;
};

#if DBG_FMT
#define FUNCTION_TIME_PRINT	CFunctionTime __ftpx_tmp(__FUNCTION__);
#define FUNCTION_TIME_PRINT_(x)	CFunctionTime __ftpx_tmp2(__FUNCTION__#x);
#else
#define FUNCTION_TIME_PRINT	
#define FUNCTION_TIME_PRINT_(x)
#endif

#endif /* _COMMFUNS_INC_ */