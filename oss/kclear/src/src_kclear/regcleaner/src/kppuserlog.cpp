// Copyright (c) 2010 Kingsoft Corporation. All rights reserved.
// Copyright (c) 2010 The KSafe Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/************************************************************************
* @file      : kppuserlog.h
* @author    : WangBin <WangBin5@kingsoft.com>
* @date      : 6/9/2009 PM 3:32:01
* @brief     : 
*
* $Id: $
/************************************************************************/

#include "stdafx.h"
#include <stdio.h>
#include <strsafe.h>
#include <shlwapi.h>
#include <assert.h>
//#include "def_ksscan.h"
#include "kppuserlog.h"

#pragma comment (lib, "shlwapi.lib")

#define CLEAR_LOG_FILE L"regtube.log"
#define KPP_USER_LOG_TIME_FORMAT L"%04d-%02d-%02d %02d:%02d:%02d "


KppUserLog::KppUserLog() :
	m_bInitFlag(FALSE),
	m_pFile(NULL)
{

}

KppUserLog::~KppUserLog()
{
	if (m_bInitFlag)
	{
		Uninit();
	}

	m_bInitFlag = FALSE;
	m_pFile = NULL;
}

KppUserLog& KppUserLog::UserLogInstance()
{
	static KppUserLog Instance;
    static BOOL bInit = FALSE;
    if (!bInit)
    { 
        WCHAR szLogFileName[MAX_PATH] = {0};
        ::GetModuleFileName(/*HMODULE_THIS,*/NULL, szLogFileName, MAX_PATH -1);
        ::PathRemoveFileSpec(szLogFileName);
        ::PathAppend(szLogFileName, CLEAR_LOG_FILE);
        Instance.Init(szLogFileName);
        bInit = TRUE;
    }

	return Instance; 
}


HRESULT KppUserLog::Init(const WCHAR* wszPathName)
{
    if (!wszPathName)
    {
        return E_FAIL;
    }

    if (!m_bInitFlag)
    {
        m_strPathName = wszPathName;
        InitializeCriticalSection(&m_LogLock);
        m_bInitFlag = TRUE;
    }

	return S_OK;
}

HRESULT KppUserLog::Uninit()
{
	DeleteCriticalSection(&m_LogLock);

	m_bInitFlag = FALSE;
	m_pFile = NULL;

	return S_OK;
}

BOOL KppUserLog::ParseTime(std::wstring& sTime, SYSTEMTIME* pTime)
{
    if (pTime)
    {
        WCHAR szForamt[MAX_PATH] = {0};

        StringCchPrintfW( 
            szForamt,
            64,
            KPP_USER_LOG_TIME_FORMAT,
            pTime->wYear,
            pTime->wMonth,
            pTime->wDay,
            pTime->wHour,
            pTime->wMinute,
            pTime->wSecond
            );

        sTime = szForamt;
    }
    return FALSE;
}


HRESULT KppUserLog::ReadOrgLog(std::vector<std::wstring>& vLogCache)
{
	WCHAR wszTime[TIME_MAX_LEN + 1] = {0};
	std::wstring strLog;
	const WCHAR* Point = NULL;
	HRESULT hrRet = E_FAIL;
	std::vector<std::wstring> vcStrline;
	BYTE* pBuf = NULL;
    FILE* pFile = NULL;
	DWORD dwRealReadSize = 0;

	if (!m_bInitFlag)
	{
		return E_FAIL;
	}

	_LockWork();

	DWORD dwFileSize  = _DoGetFileSizeByFileName(m_strPathName.c_str());
	if (dwFileSize <= 0)
	{
		hrRet = E_FAIL;
		goto _Exit;
	}

	pBuf = new BYTE[dwFileSize + 2];
	if (!pBuf)
	{
		hrRet = E_OUTOFMEMORY;
		goto _Exit;
	}

	::ZeroMemory(pBuf, dwFileSize + 2);

	pFile = ::_wfopen(m_strPathName.c_str(), L"rt,ccs=UNICODE");
	if (!pFile)
	{
		hrRet = E_FAIL;
		goto _Exit;
	}

	dwRealReadSize = (DWORD)::fread(pBuf, sizeof(WCHAR), dwFileSize/2, pFile);
	if (dwRealReadSize == 0)
	{
		hrRet = E_FAIL;
		goto _Exit;
	}

	WCHAR* pszInfo = (WCHAR*)pBuf;

	DWORD dwLineCount = _DoGetLineByBuf(pszInfo, (DWORD)::wcslen(pszInfo), vLogCache);

	hrRet = S_OK;

_Exit:

	if (pBuf)
	{
		delete []pBuf;
		pBuf = NULL;
	}
	if (pFile)
	{
		fclose(pFile);
		pFile = NULL;
	}

	_UnlockWork();
	return hrRet;
}

HRESULT KppUserLog::ReadLog(std::map<std::wstring, std::wstring>& mapLine)
{
    HRESULT hr = E_FAIL;
    DWORD dwRealReadSize = 0;
    BYTE* pBuf = NULL;
    FILE* pFile = NULL;

    DWORD dwFileSize  = _DoGetFileSizeByFileName(m_strPathName.c_str());
    if (dwFileSize <= 0)
    {
        hr = E_FAIL;
        goto _Exit;
    }

    pBuf = new BYTE[dwFileSize + 2];
    if (!pBuf)
    {
        hr = E_OUTOFMEMORY;
        goto _Exit;
    }

    ::ZeroMemory(pBuf, dwFileSize + 2);

    pFile = ::_wfopen(m_strPathName.c_str(), L"rt,ccs=UNICODE");
    if (!pFile)
    {
        hr = E_FAIL;
        goto _Exit;
    }

    dwRealReadSize = (DWORD)::fread(pBuf, sizeof(WCHAR), dwFileSize, pFile);
    if (dwRealReadSize != 0)
    {
        WCHAR* pszInfo = (WCHAR*)pBuf;
        _DoGetLineDescByBuf(pszInfo, (DWORD)::wcslen(pszInfo), mapLine);
        hr = S_OK;
    }

_Exit:

    if (pBuf)
    {
        delete []pBuf;
        pBuf = NULL;
    }

    if (pFile)
    {
        fclose(pFile);
        pFile = NULL;
    }

    return S_OK;
}


// Time 字符串中不能有空格
HRESULT KppUserLog::WriteSingleLog(
	/* [in] */const std::wstring& wstLogString
	)
{
	std::wstring strLog;
	HRESULT	hrRet = E_FAIL;
	SYSTEMTIME	sysTime = {0};
    CStringW strTmep;

	if (!m_bInitFlag)
	{
		return E_FAIL;
	}

	_LockWork();

	FILE* pfile = NULL;

	if (::PathFileExists(m_strPathName.c_str()))
	{
		pfile = ::_wfopen(m_strPathName.c_str(), L"at,ccs=UNICODE");
	}
	else
	{
		pfile = ::_wfopen(m_strPathName.c_str(), L"wt,ccs=UNICODE");
	}
	
	if (!pfile)
	{
		hrRet = S_OK;
		goto _Exit;
	}

	GetLocalTime( &sysTime );

    ParseTime(strLog, &sysTime);

    strTmep = wstLogString.c_str();

    strTmep.Replace('\r', ' ');
    strTmep.Replace('\n', ' ');

	strLog += strTmep;
	strLog += '\n';

	::fwrite(strLog.c_str(), sizeof(WCHAR), ::wcslen(strLog.c_str()), pfile);

	hrRet = S_OK;

_Exit:

	if (pfile)
	{
		::fclose(pfile);
		pfile = NULL;
	}

	_UnlockWork();

	return hrRet;
}

HRESULT KppUserLog::ClearLog()
{
    if (::PathFileExists(m_strPathName.c_str()))
    {
        ::DeleteFile(m_strPathName.c_str());
    }
    return S_OK;
}


void KppUserLog::_LockWork()
{
	EnterCriticalSection(&m_LogLock);
}

void KppUserLog::_UnlockWork()
{
	LeaveCriticalSection(&m_LogLock);
}

DWORD KppUserLog::_DoGetFileSizeByFileName(const WCHAR* pFileName)
{
    if (!pFileName)
    {
        return 0;
    }

    HANDLE hFile = INVALID_HANDLE_VALUE;
    DWORD dwFileSize = 0;

    hFile = ::CreateFile(
        pFileName, 
        GENERIC_READ,
        0, 
        NULL,
        OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL
        );

    if (hFile != INVALID_HANDLE_VALUE)
    {
        dwFileSize = ::GetFileSize(hFile, NULL);
        ::CloseHandle(hFile);
    }

    return dwFileSize;
}

DWORD KppUserLog::_DoGetLineByBuf(
                                  WCHAR* const pszBuf,
                                  DWORD dwlen, 
                                  std::vector<std::wstring>& vcStrline)
{
    if (!pszBuf)
    {
        return 0;
    }

    WCHAR* pszBeginPoint = pszBuf;
    WCHAR* pszCurrentPoint = pszBuf;
    WCHAR* pszTempBuf = NULL;
    DWORD dwlenSize = 0;
    DWORD dwLineCount = 0;

    while (*pszCurrentPoint != 0 && (unsigned)(pszCurrentPoint - pszBuf) <= dwlen)
    {
        if (*pszCurrentPoint == '\n')
        {
            dwlenSize = (DWORD)(pszCurrentPoint - pszBeginPoint);
            pszTempBuf = new WCHAR[dwlenSize + 1];
            if (!pszTempBuf)
            {
                break;
            }
            ::ZeroMemory(pszTempBuf, (dwlenSize + 1)* 2);
            ::memcpy(pszTempBuf, pszBeginPoint, dwlenSize * 2);

            pszBeginPoint = pszCurrentPoint + 1;

            vcStrline.push_back(pszTempBuf);
            dwLineCount++ ;

            delete []pszTempBuf;
            pszTempBuf = NULL;
        }

        pszCurrentPoint ++;
    }

    return dwLineCount;
}

DWORD KppUserLog::_DoGetLineDescByBuf(
                                  WCHAR* const pszBuf, 
                                  DWORD dwlen, 
                                  std::map<std::wstring, std::wstring>& mapStrline)
{
    assert(pszBuf);

    WCHAR* pszBeginPoint = pszBuf;
    WCHAR* pszCurrentPoint = pszBuf;
    WCHAR* pszTempBuf = NULL;

    DWORD dwlenSize = 0;
    DWORD dwLineCount = 0;

    WCHAR* pszTime = NULL;
    WCHAR* pszCom = NULL;

    while (*pszCurrentPoint != 0 && (unsigned)(pszCurrentPoint - pszBuf) <= dwlen)
    {
        if (*pszCurrentPoint == '\n')
        {
            dwlenSize = (DWORD)(pszCurrentPoint - pszBeginPoint);
            pszTempBuf = new WCHAR[dwlenSize + 1];
            if (!pszTempBuf)
            {
                break;
            }

            ::ZeroMemory(pszTempBuf, (dwlenSize + 1) *  2);
            ::memcpy(pszTempBuf, pszBeginPoint, dwlenSize * 2);

            pszBeginPoint = pszCurrentPoint + 1;

            if (::wcslen(pszTempBuf) > 20) //分出时间与内容
            { 
                pszTime = pszTempBuf;
                pszTime[19] = 0;
                pszCom = &pszTempBuf[20];

                mapStrline[pszTime] = pszCom;
            }

            dwLineCount++ ;
            delete []pszTempBuf;
            pszTempBuf = NULL;
        }
        pszCurrentPoint ++;
    }

    return dwLineCount;
}
// -------------------------------------------------------------------------
// $Log: $