// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <winnt.h>


#include "kstringex.h"
#include "public.h"

//////////////////////////////////////////////////////////////////////////
//dll �ڲ�ʹ�õķ�����
//�����ַ�����Ҫ����ʱ��Ҫ��������жϣ�
//1���Ƿ�������ַ���ΪNULL�����ΪNULL,�򷵻���ʵ���ַ������ȡ�
//2�����������ַ�����Ϊ�ա����ж�����ĳ����Ƿ����ʵ����ҪС�����ҪС���򽫴�С���ء������ΪFALSE
static int JudgeAndCopy(LPCWSTR lpBufferSrc, LPWSTR lpBufferDes, size_t& nSize)
{
	size_t nCurSize = wcslen(lpBufferSrc);
	if (lpBufferDes == NULL)
	{
		nSize = nCurSize;
		return TRUE;
	}

	if ((int)nSize < nCurSize)
	{
		nSize = nCurSize;
		return FALSE;
	}

	wcscpy_s(lpBufferDes, nSize, lpBufferSrc);
	nSize = nCurSize;

	return TRUE;
}

//�ڲ����÷���
template<class TRet, class T1, class T2>
int CallOutA(void* pFunc, LPSTR lpBuffer, size_t& nSize)
{
	if (ValidPtrRange(pFunc))		return FALSE;

	typedef TRet (* CallOutA)(T1, T2);
	CallOutA pCallOut = (CallOutA)pFunc;

	KWString strBuffer;
	strBuffer.GetBuffer((int)nSize);
	BOOL bRet = pCallOut((LPWSTR)strBuffer.c_str(), nSize);
	strBuffer.ReleaseBuffer();

	if (lpBuffer == NULL)
		return TRUE;

	if ((int)nSize < strBuffer.GetLength())
		return FALSE;

	if (bRet && lpBuffer != NULL)
	{
		KAString strBufferA = strBuffer;
		strcpy_s(lpBuffer, nSize, strBufferA.c_str());
	}

	return bRet;
}



// TODO: reference additional headers your program requires here
