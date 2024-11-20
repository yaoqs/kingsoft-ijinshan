#include <Windows.h>
//-----------------------------------------------------------------------------//
//
// c:\windows\system32\userinit.exe, c:\windows\xxx.exe ������buffer, �ֳɶ�Ӧ��
// һ�ζε�buffer, �Զ�����Ϊ�ָ�, ��ȥ�����ź���Ŀո�
//
// plStringCount: ����ʵ���ַ�������
//
// Return:
//			ERROR_SUCCESS
//			ERROR_MORE_DATA
//
#include <winerror.h>
LONG
ParseSpecialBuffer1(
	IN OUT PWCHAR pwszStringBuffer,
	IN OUT PWCHAR aString[],
	IN OUT PLONG plStringCount
	)
{
	LONG lStringLength = 0;
	LONG lCount = 0;
	LONG i = 0;

	lStringLength = (LONG)wcslen(pwszStringBuffer);
	if (0 == lStringLength)
	{
		*plStringCount = 0;
		return ERROR_SUCCESS;
	}

	
	while ((L' ' == pwszStringBuffer[0]) || (L',' == pwszStringBuffer[0]))
	{
		//
		// ȥ���ַ�����ͷ��','��' '
		//
		pwszStringBuffer ++;
	}

	//
	// �ҵ���һ���ַ���
	//
	if (L'\0' != pwszStringBuffer[0])
	{
		aString[lCount] = pwszStringBuffer;
		lCount += 1;
	}
	else
	{
		*plStringCount = 0;
		return ERROR_SUCCESS;
	}
	

	for (i = 0; i < lStringLength; i++)
	{
		PWCHAR pwszTemp = NULL;

		if (L',' == pwszStringBuffer[i])
		{
			pwszStringBuffer[i] = L'\0';
		}
		else
		{
			continue;
		}

		pwszTemp = &pwszStringBuffer[i + 1];

		while ((L' ' == pwszTemp[0]) || (L',' == pwszTemp[0]))
		{
			//
			// ȥ��pwszTemp��ͷ��','��' '
			//
			pwszTemp ++;
		}

		if (L'\0' != pwszTemp[0])
		{
			if (lCount <= *plStringCount)
			{
				aString[lCount] = pwszTemp;
			}
			lCount += 1;
		}
		else
		{
			*plStringCount = lCount;
			return ERROR_SUCCESS;
		}
	}

	if (lCount > *plStringCount)
	{
		*plStringCount = lCount;
		return ERROR_MORE_DATA;
	}
	else
	{
		*plStringCount = lCount;
		return ERROR_SUCCESS;
	}
}
//-----------------------------------------------------------------------------//
LONG
ParseSpecialBuffer2_MultiString(
	IN OUT PVOID pMultiStringBuffer,
	IN LONG lBufferSize,
	IN OUT PWCHAR aString[],
	IN OUT PLONG plStringCount
	)
{
	LONG i;
	LONG lCount = 0;
	PWCHAR pwstrPointer = NULL;

	pwstrPointer = (PWCHAR)pMultiStringBuffer;
	aString[0] = pwstrPointer;
	lCount += 1;

	for (i = 0; i < (lBufferSize / 2); i ++)
	{
		if (pwstrPointer[i] == L'\0')
		{
			aString[lCount] = &pwstrPointer[i + 1];
			if (aString[lCount][0] == L'\0')
			{
				break;
			}
			lCount ++;
		}
	}

	if (lCount > *plStringCount)
	{
		*plStringCount = lCount;
		return ERROR_MORE_DATA;
	}
	else
	{
		*plStringCount = lCount;
		return ERROR_SUCCESS;
	}
}
//-----------------------------------------------------------------------------//
BOOL
IsLetterW (
	WCHAR wch
	)
{
	if (((L'a' <= wch) && (wch <= L'z')) || ((L'A' <= wch) && (wch <= L'Z')))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//-----------------------------------------------------------------------------//
BOOL
IsFullPath (
	PWCHAR pwstrPath
	)
{
	LONG lPathLength = 0;

	//
	// "  c:\aaa.txt" ������Ҳ�У� ȥ��ͷ�ո�
	// 
	while (L' ' == pwstrPath[0])
	{
		pwstrPath++;
	}

	lPathLength = (LONG)wcslen(pwstrPath);

	if (lPathLength < 4)  // c:\a
	{
		return FALSE;
	}

	//
	// %SystemRoot%
	//

	//if ((lPathLength > wcslen(L"%SystemRoot%")) && (0 == wcsncmp(pwstrPath, L"%SystemRoot%", wcslen(L"%SystemRoot%"))))
	//{
	//	return TRUE;
	//}

	if (IsLetterW(pwstrPath[0]) && (L':' == pwstrPath[1]) && (L'\\' == pwstrPath[2]))
	{
		return TRUE;
	}

	//
	//  ��ʱ��������\??\ \\?\ ��֪��user�¶����ļ�����ʽ
	//
	

	return FALSE;
}
//-----------------------------------------------------------------------------//
BOOL
IsFileExist (
	PWCHAR pwstrFilePath
	)
{
	HANDLE hFindHandle = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA FindData = {0};

	hFindHandle = FindFirstFileW(pwstrFilePath, &FindData);
	if (INVALID_HANDLE_VALUE != hFindHandle)
	{
		FindClose(hFindHandle);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//-----------------------------------------------------------------------------//
LONG
MakeFullPath (
	IN  PWCHAR pwstrDest,
	IN  LONG lDestSizeInWCHAR,
	OUT PWCHAR pwstrSource,
	IN  LONG lSourceSizeInWCHAR
	)
{
	//
	// ������Ӧ�ð��ջ��������е�˳��һ��������Ƿ���ڣ�ȡ��һ����ɽկ����������ֱ�Ӽ�systemdirectory
	//
	WCHAR wstrTempDirectory[MAX_PATH] = {0};
	UINT unCount;
	BOOL bFileExist = FALSE;


	//
	// system directory
	//

	memset(pwstrDest, 0, MAX_PATH * sizeof(WCHAR));
	unCount = GetSystemDirectoryW(wstrTempDirectory, MAX_PATH);
	if (unCount > MAX_PATH)
	{
		// @#%@%$#@&%
		return -1;
	}

	if ((LONG)(unCount + wcslen(L"\\") + lSourceSizeInWCHAR) > lDestSizeInWCHAR)
	{
		return -1;
	}

	wcsncpy(pwstrDest, wstrTempDirectory, unCount);
	wcsncat(pwstrDest, L"\\", 1);
	wcsncat(pwstrDest, pwstrSource, lSourceSizeInWCHAR);

	bFileExist = IsFileExist(pwstrDest);
	if (TRUE == bFileExist)
	{
		return ERROR_SUCCESS;
	}


	//
	// windows directory
	//

	memset(pwstrDest, 0, MAX_PATH * sizeof(WCHAR));
	unCount = GetWindowsDirectoryW(wstrTempDirectory, MAX_PATH);
	if (unCount > MAX_PATH)
	{
		// @#%@%$#@&%
		return -1;
	}
	if ((LONG)(unCount + wcslen(L"\\") + lSourceSizeInWCHAR) > lDestSizeInWCHAR)
	{
		return -1;
	}

	wcsncpy(pwstrDest, wstrTempDirectory, unCount);
	wcsncat(pwstrDest, L"\\", 1);
	wcsncat(pwstrDest, pwstrSource, lSourceSizeInWCHAR);

	bFileExist = IsFileExist(pwstrDest);
	if (TRUE == bFileExist)
	{
		return ERROR_SUCCESS;
	}


	//
	// driver directory
	//

	memset(pwstrDest, 0, MAX_PATH * sizeof(WCHAR));
	unCount = GetSystemDirectoryW(wstrTempDirectory, MAX_PATH);
	if (unCount > MAX_PATH)
	{
		// @#%@%$#@&%
		return -1;
	}

	if ((LONG)(unCount + wcslen(L"\\Drivers\\") + lSourceSizeInWCHAR) > lDestSizeInWCHAR)
	{
		return -1;
	}

	wcsncpy(pwstrDest, wstrTempDirectory, unCount);
	wcsncat(pwstrDest, L"\\Drivers\\", 1);
	wcsncat(pwstrDest, pwstrSource, lSourceSizeInWCHAR);

	
	//
	// ��3���ط��������ڵ�ʱ��Ҳ������Ĳ����ڣ�Ҳ���������ˣ� ��㷵��һ��
	//

	return ERROR_SUCCESS;
}
//-----------------------------------------------------------------------------//
int
u_strrcmp (
		   char* str1,
		   char* str2
		   )
{
	size_t i = strlen(str1);
	size_t j = strlen(str2);

	while ((i-- > 0) && (j-- > 0))
	{
		if (str1[i] != str2[j])
		{
			return str1[i] - str2[j];
		}
	}

	return 0;
}
//-----------------------------------------------------------------------------//
int
u_strricmp (
			char* str1,
			char* str2
			)
{
	return u_strrcmp(_strlwr(str1), _strlwr(str2));
}
//-----------------------------------------------------------------------------//
int
u_wcsrcmp (
		   wchar_t* str1,
		   wchar_t* str2
		   )
{
	size_t i = wcslen(str1);
	size_t j = wcslen(str2);

	while ((i-- > 0) && (j-- > 0))
	{
		if (str1[i] != str2[j])
		{
			return str1[i] - str2[j];
		}
	}

	return 0;
}
//-----------------------------------------------------------------------------//
int
u_wcsricmp (
			wchar_t* str1,
			wchar_t* str2
			)
{
	return u_wcsrcmp(_wcslwr(str1), _wcslwr(str2));
}
//-----------------------------------------------------------------------------//
BOOL
MatchPath (
	PWCHAR pwszPath1,
	PWCHAR pwszPath2
	)
{
	if (0 == _wcsicmp(pwszPath1, pwszPath2))
	{
		return TRUE;
	}

	if (0 == u_wcsrcmp(pwszPath1, pwszPath2))
	{
		return TRUE;
	}
	
	return FALSE;
}
//----------------------------------------------------------------------------//