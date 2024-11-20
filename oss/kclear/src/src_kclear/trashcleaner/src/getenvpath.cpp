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

// GetEnvPath.cpp: implementation of the CGetEnvPath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "trashcleaner.h"
#include "GetEnvPath.h"
#include "trashpublicfunc.h"
#include "trashdefine.h"
#include "kregfunction.h"
#include "IniEditor.h"
#include "kscbase/kscconv.h"

typedef struct tagCSIDL_NAME
{
    LPCTSTR pszCsidlName;
    int     nFolder;
}CSIDL_NAME, *LPCSIDL_NAME;

#ifdef _UNICODE
#define CSIDL_NAME_ENTRY(ID) \
{ L#ID , ID }
#else
#define CSIDL_NAME_ENTRY(ID) \
{ #ID , ID }
#endif

CSIDL_NAME g_csidlnamelist[] = 
{
    CSIDL_NAME_ENTRY(CSIDL_DESKTOP),
    CSIDL_NAME_ENTRY(CSIDL_INTERNET),
    CSIDL_NAME_ENTRY(CSIDL_PROGRAMS),
    CSIDL_NAME_ENTRY(CSIDL_CONTROLS),
    CSIDL_NAME_ENTRY(CSIDL_PRINTERS),
    CSIDL_NAME_ENTRY(CSIDL_PERSONAL),
    CSIDL_NAME_ENTRY(CSIDL_FAVORITES),
    CSIDL_NAME_ENTRY(CSIDL_STARTUP),
    CSIDL_NAME_ENTRY(CSIDL_RECENT),
    CSIDL_NAME_ENTRY(CSIDL_SENDTO),
    CSIDL_NAME_ENTRY(CSIDL_BITBUCKET),
    CSIDL_NAME_ENTRY(CSIDL_STARTMENU),
    CSIDL_NAME_ENTRY(CSIDL_DESKTOPDIRECTORY),
    CSIDL_NAME_ENTRY(CSIDL_DRIVES),
    CSIDL_NAME_ENTRY(CSIDL_NETWORK),
    CSIDL_NAME_ENTRY(CSIDL_NETHOOD),
    CSIDL_NAME_ENTRY(CSIDL_FONTS),
    CSIDL_NAME_ENTRY(CSIDL_TEMPLATES),
    CSIDL_NAME_ENTRY(CSIDL_COMMON_STARTMENU),
    CSIDL_NAME_ENTRY(CSIDL_COMMON_PROGRAMS),
    CSIDL_NAME_ENTRY(CSIDL_COMMON_STARTUP),
    CSIDL_NAME_ENTRY(CSIDL_COMMON_DESKTOPDIRECTORY),
    CSIDL_NAME_ENTRY(CSIDL_APPDATA),
    CSIDL_NAME_ENTRY(CSIDL_PRINTHOOD),
    CSIDL_NAME_ENTRY(CSIDL_ALTSTARTUP),
    CSIDL_NAME_ENTRY(CSIDL_COMMON_ALTSTARTUP),
    CSIDL_NAME_ENTRY(CSIDL_COMMON_FAVORITES),
    CSIDL_NAME_ENTRY(CSIDL_INTERNET_CACHE),
    CSIDL_NAME_ENTRY(CSIDL_COOKIES),
    CSIDL_NAME_ENTRY(CSIDL_HISTORY),
    CSIDL_NAME_ENTRY(CSIDL_LOCAL_APPDATA),
    CSIDL_NAME_ENTRY(CSIDL_COMMON_APPDATA)
};


CGetEnvPath::CGetEnvPath()
{
    m_hModule = NULL;
    m_pfnGetLongPathName = NULL;

    while (true)
    {
        m_hModule = LoadLibrary(TEXT("Kernel32.dll"));

        if (m_hModule == NULL)
            break;

        m_pfnGetLongPathName = 
            (pfnGetLongPathNameW)GetProcAddress(m_hModule, "GetLongPathNameW");

        break;
    }
}

CGetEnvPath::~CGetEnvPath()
{
    m_pfnGetLongPathName = NULL;

    if (m_hModule != NULL)
        FreeLibrary( m_hModule );
}

CString CGetEnvPath::GetRealPath(LPCTSTR pszEnvPath)
{

    CString strResult;

    if (pszEnvPath == NULL)
    {
        strResult = _T("");
        goto Exit0;
    }
    
    int nFirstPos  = 0; 
    int nSecondPos = 0;
    BOOL bFind = FALSE;

    strResult = pszEnvPath;

    bFind = FindEnvironmentPos(strResult, nFirstPos, nSecondPos);

    if (bFind == TRUE)
    {
        CString strLeft       ;
        CString strRight      ;
        CString strEnvName    ;
        CString strEnvVariable;


        strLeft    = strResult.Left(nFirstPos);
        strRight   = strResult.Mid (nSecondPos + 1);
        strEnvName = strResult.Mid(nFirstPos + 1, nSecondPos - nFirstPos - 1);

        strEnvVariable = GetEnvVariable(strEnvName);
        if (strEnvVariable.GetLength() <= 0)
            strEnvVariable = GetFolderPath( strEnvName );

        if(strEnvVariable.Find(_T(';')) == -1)
            strResult = CombinationPath(strLeft, strEnvVariable, strRight);
        else
        {
            //SplitString()
            std::vector<CString> strvec;
            SplitString(strEnvVariable,_T(';'), strvec);
            strResult = _T("");
            for(std::vector<CString>::iterator it = strvec.begin();it != strvec.end(); it++)
            {
                strResult += CombinationPath(strLeft, (*it), strRight);
                strResult += _T(";");
            }
            
        }

        
        bFind = FindEnvironmentPos(strResult, nFirstPos, nSecondPos);
    }
Exit0:
    return strResult;
}

CString CGetEnvPath::CombinationPath(const CString& strLeft, 
    const CString& strMiddle, 
    const CString& strRight)
{
    CString strResult;
    const int nCount = 3;
    const CString* pStr[nCount] = 
        { &strLeft, &strMiddle, &strRight};

    for (int i = 0; i < nCount; i++)
    {
        const CString& str = *pStr[i];

        if (strResult.GetLength() <= 0)
            strResult += str;
        else
        {
            if (str.GetLength() <= 0)
                continue;

            if (strResult[strResult.GetLength() - 1] == TEXT('\\'))
                strResult.Delete(strResult.GetLength() - 1);

            if (str[0] != TEXT('\\'))
            {
                strResult += TEXT('\\');
            }

            strResult += str;
        }
    }

    return strResult;
}

BOOL CGetEnvPath::FindEnvironmentPos(LPCTSTR pszEnvPath, int& nFirstPos, int& nSecondPos)
{
    BOOL bRet = TRUE;
    if (pszEnvPath == NULL)
    {
        bRet = FALSE;
        goto Exit0;
    }
    
    const TCHAR cSpil = TEXT('%');

    const TCHAR* pFirstPos  = NULL;
    const TCHAR* pSecondPos = NULL;

    pFirstPos = _tcschr(pszEnvPath, cSpil);
    if (pFirstPos == NULL)
    {
        bRet = FALSE;
        goto Exit0;
    }

    pSecondPos = _tcschr(pFirstPos + 1, cSpil);
    if (pSecondPos == NULL)
    {
        bRet = FALSE;
        goto Exit0;
    }

    nFirstPos  = int ( pFirstPos  - pszEnvPath );
    nSecondPos = int ( pSecondPos - pszEnvPath );
Exit0:
    return bRet;
}

CString CGetEnvPath::GetEnvVariable(LPCTSTR pszName)
{
    CString strResult;
	WCHAR wcsTemp[MAX_PATH] = {0}; 
    
    TCHAR szBuffer[MAX_PATH] = { 0 };
    TCHAR szLongPathBuffer[MAX_PATH] = { 0 };

    if ( CString("systemdrive").CompareNoCase(pszName) == 0 )
    {
        //UINT uResult = GetSystemDirectory(szBuffer, MAX_PATH);
        //strResult = GetDrive(_T(""));
        UINT uResult = GetSystemDirectory(szBuffer, MAX_PATH);

        if (uResult > 3 && szBuffer[1] == TEXT(':') && szBuffer[2] == TEXT('\\'))
        {
            szBuffer[2] = TEXT('\0');
            strResult = szBuffer;
            goto Exit0;         
        }
    }
    else if ( CString("program").CompareNoCase(pszName) == 0 )
    {
        //UINT uResult = GetSystemDirectory(szBuffer, MAX_PATH);
        //strResult = GetDrive(_T(""));
        UINT uResult = GetSystemDirectory(szBuffer, MAX_PATH);

        if (uResult > 3 && szBuffer[1] == TEXT(':') && szBuffer[2] == TEXT('\\'))
        {
            szBuffer[3] = TEXT('\0');
            strResult = szBuffer;
            strResult += L"program files";
            goto Exit0;         
        }
    }
    else if ( CString("boot").CompareNoCase(pszName) == 0 )
    {
        //UINT uResult = GetSystemDirectory(szBuffer, MAX_PATH);
        //strResult = GetDrive(_T(""));
        UINT uResult = GetSystemDirectory(szBuffer, MAX_PATH);

        if (uResult > 3 && szBuffer[1] == TEXT(':') && szBuffer[2] == TEXT('\\'))
        {
            szBuffer[3] = TEXT('\0');
            strResult = szBuffer;
            strResult += L"boot";
            goto Exit0;         
        }
    }
    else if ( CString("recovery").CompareNoCase(pszName) == 0 )
    {
        //UINT uResult = GetSystemDirectory(szBuffer, MAX_PATH);
        //strResult = GetDrive(_T(""));
        UINT uResult = GetSystemDirectory(szBuffer, MAX_PATH);

        if (uResult > 3 && szBuffer[1] == TEXT(':') && szBuffer[2] == TEXT('\\'))
        {
            szBuffer[3] = TEXT('\0');
            strResult = szBuffer;
            strResult += L"recovery";
            goto Exit0;         
        }
    }
    else if ( CString("systemroot").CompareNoCase(pszName) == 0 )
    {
       
        UINT uResult = GetSystemDirectory(szBuffer, MAX_PATH);

        if (uResult > 0)
        {
            strResult = szBuffer;
            goto Exit0;         
        }
    }
    else if(CString("windir").CompareNoCase(pszName) == 0)
    {
        UINT uResult = GetWindowsDirectory(szBuffer, MAX_PATH);

        if(szBuffer[wcslen(szBuffer)-1] == _T('\\'))
            szBuffer[wcslen(szBuffer)-1] = _T('\0');

        strResult = szBuffer;
        goto Exit0;
    }
    else if ( CString("systemrecycled").CompareNoCase(pszName) == 0 )
    {
        SYSTEM_VERSION     m_eSysVer;
        KAEGetSystemVersion(&m_eSysVer);
        CString StrSuffix;
        if(m_eSysVer == enumSystem_Win_7)
        {
            StrSuffix = _T("\\$RECYCLE.BIN");
        }
        else
            StrSuffix = _T("\\Recycled");
        strResult = GetDrive(StrSuffix);

        goto Exit0;
    }
	else if ( CString("minidump").CompareNoCase(pszName) == 0 )
	{
		DWORD len = sizeof(szLongPathBuffer);
		GetRegistryValue(HKEY_LOCAL_MACHINE,
			L"SYSTEM\\CurrentControlSet\\Control\\CrashControl",
			L"MinidumpDir",
			NULL,
			(LPBYTE)szLongPathBuffer,
			&len
			);
		if(wcslen(szLongPathBuffer) == 0)
			strResult = L"%minidump%";
		else
		{
			int nFirstPos  = 0; 
			int nSecondPos = 0;
			BOOL bFind = FALSE;
			bFind = FindEnvironmentPos(szLongPathBuffer, nFirstPos, nSecondPos);
			if(bFind)
			{
				CString strLeft       ;
				CString strRight      ;
				CString strEnvName    ;
				CString strEnvVariable;
				
				strResult = szLongPathBuffer;
				strLeft    = strResult.Left(nFirstPos);
				strRight   = strResult.Mid (nSecondPos + 1);
				strEnvName = strResult.Mid(nFirstPos + 1, nSecondPos - nFirstPos - 1);
				TCHAR szTempBuf[MAX_PATH];
				DWORD dwResult = GetEnvironmentVariable(strEnvName.GetBuffer(), szTempBuf, MAX_PATH);
				if (dwResult > 0)
					strEnvVariable = szTempBuf;

				strResult = CombinationPath(strLeft, strEnvVariable, strRight);

			}
			else
				strResult = szLongPathBuffer;

			goto Exit0;

		}
	}
	else if ( CString("memdump").CompareNoCase(pszName) == 0 )
	{
		DWORD len = sizeof(szLongPathBuffer);
		GetRegistryValue(HKEY_LOCAL_MACHINE,
			L"SYSTEM\\CurrentControlSet\\Control\\CrashControl",
			L"DumpFile",
			NULL,
			(LPBYTE)szLongPathBuffer,
			&len
			);
		if(wcslen(szLongPathBuffer) == 0)
			strResult = L"%memdump%";
		else
		{
			int nFirstPos  = 0; 
			int nSecondPos = 0;
			BOOL bFind = FALSE;
			bFind = FindEnvironmentPos(szLongPathBuffer, nFirstPos, nSecondPos);
			if(bFind)
			{
				CString strLeft       ;
				CString strRight      ;
				CString strEnvName    ;
				CString strEnvVariable;

				strResult = szLongPathBuffer;
				strLeft    = strResult.Left(nFirstPos);
				strRight   = strResult.Mid (nSecondPos + 1);
				strEnvName = strResult.Mid(nFirstPos + 1, nSecondPos - nFirstPos - 1);
				TCHAR szTempBuf[MAX_PATH];
				DWORD dwResult = GetEnvironmentVariable(strEnvName.GetBuffer(), szTempBuf, MAX_PATH);
				if (dwResult > 0)
					strEnvVariable = szTempBuf;

				strResult = CombinationPath(strLeft, strEnvVariable, L"");
				strResult += strRight;
			}
			else
				strResult = szLongPathBuffer;
			if (GetFileAttributes(strResult.GetBuffer()) != FILE_ATTRIBUTE_DIRECTORY)
			{
				WCHAR szTempBuffer[MAX_PATH] = {0};
				wcscpy_s(szTempBuffer, MAX_PATH - 1, strResult.GetBuffer());
				::PathRemoveFileSpec(szTempBuffer);
				strResult = szTempBuffer;
			}

			goto Exit0;

		}
	}
	else if (CString("archivefiles").CompareNoCase(pszName) == 0)
	{
		DWORD len = sizeof(szLongPathBuffer);
		GetRegistryValue(HKEY_LOCAL_MACHINE,
			L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VolumeCaches\\Windows Error Reporting Archive Files",
			L"Folder",
			NULL,
			(LPBYTE)szLongPathBuffer,
			&len
			);
		if (wcslen(szLongPathBuffer) == 0)
		{
			strResult = L"%archivefiles%";
		}
		else
		{
			int nFirstPos  = 0; 
			int nSecondPos = 0;
			BOOL bFind = FALSE;
			bFind = FindEnvironmentPos(szLongPathBuffer, nFirstPos, nSecondPos);
			if(bFind)
			{
				CString strLeft       ;
				CString strRight      ;
				CString strEnvName    ;
				CString strEnvVariable;

				strResult = szLongPathBuffer;
				strLeft    = strResult.Left(nFirstPos);
				strRight   = strResult.Mid (nSecondPos + 1);
				strEnvName = strResult.Mid(nFirstPos + 1, nSecondPos - nFirstPos - 1);
				TCHAR szTempBuf[MAX_PATH];
				DWORD dwResult = GetEnvironmentVariable(strEnvName.GetBuffer(), szTempBuf, MAX_PATH);
				if (dwResult > 0)
					strEnvVariable = szTempBuf;

				strResult = CombinationPath(strLeft, strEnvVariable, L"");
				strResult += strRight;
			}
			else
			{
				strResult = szLongPathBuffer;
			}
			goto Exit0;

		}
	}
	else if (CString("queuefiles").CompareNoCase(pszName) == 0)
	{
		DWORD len = sizeof(szLongPathBuffer);
		GetRegistryValue(HKEY_LOCAL_MACHINE,
			L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VolumeCaches\\Windows Error Reporting Queue Files",
			L"Folder",
			NULL,
			(LPBYTE)szLongPathBuffer,
			&len
			);
		if (wcslen(szLongPathBuffer) == 0)
		{
			strResult = L"%queuefiles%";
		}
		else
		{
			int nFirstPos  = 0; 
			int nSecondPos = 0;
			BOOL bFind = FALSE;
			bFind = FindEnvironmentPos(szLongPathBuffer, nFirstPos, nSecondPos);
			if(bFind)
			{
				CString strLeft       ;
				CString strRight      ;
				CString strEnvName    ;
				CString strEnvVariable;

				strResult = szLongPathBuffer;
				strLeft    = strResult.Left(nFirstPos);
				strRight   = strResult.Mid (nSecondPos + 1);
				strEnvName = strResult.Mid(nFirstPos + 1, nSecondPos - nFirstPos - 1);
				TCHAR szTempBuf[MAX_PATH];
				DWORD dwResult = GetEnvironmentVariable(strEnvName.GetBuffer(), szTempBuf, MAX_PATH);
				if (dwResult > 0)
					strEnvVariable = szTempBuf;

				strResult = CombinationPath(strLeft, strEnvVariable, L"");
				strResult += strRight;
			}
			else
			{
				strResult = szLongPathBuffer;
			}
			goto Exit0;

		}
	}
	else if (CString("systemarchivefiles").CompareNoCase(pszName) == 0)
	{
		DWORD len = sizeof(szLongPathBuffer);
		GetRegistryValue(HKEY_LOCAL_MACHINE,
			L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VolumeCaches\\Windows Error Reporting System Archive Files",
			L"Folder",
			NULL,
			(LPBYTE)szLongPathBuffer,
			&len
			);
		if (wcslen(szLongPathBuffer) == 0)
		{
			strResult = L"%systemarchivefiles%";
		}
		else
		{
			int nFirstPos  = 0; 
			int nSecondPos = 0;
			BOOL bFind = FALSE;
			bFind = FindEnvironmentPos(szLongPathBuffer, nFirstPos, nSecondPos);
			if(bFind)
			{
				CString strLeft       ;
				CString strRight      ;
				CString strEnvName    ;
				CString strEnvVariable;

				strResult = szLongPathBuffer;
				strLeft    = strResult.Left(nFirstPos);
				strRight   = strResult.Mid (nSecondPos + 1);
				strEnvName = strResult.Mid(nFirstPos + 1, nSecondPos - nFirstPos - 1);
				TCHAR szTempBuf[MAX_PATH];
				DWORD dwResult = GetEnvironmentVariable(strEnvName.GetBuffer(), szTempBuf, MAX_PATH);
				if (dwResult > 0)
					strEnvVariable = szTempBuf;

				strResult = CombinationPath(strLeft, strEnvVariable, L"");
				strResult += strRight;
			}
			else
			{
				strResult = szLongPathBuffer;
			}
			goto Exit0;

		}
	}
	else if (CString("systemqueuefiles").CompareNoCase(pszName) == 0)
	{
		DWORD len = sizeof(szLongPathBuffer);
		GetRegistryValue(HKEY_LOCAL_MACHINE,
			L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VolumeCaches\\Windows Error Reporting System Queue Files",
			L"Folder",
			NULL,
			(LPBYTE)szLongPathBuffer,
			&len
			);
		if (wcslen(szLongPathBuffer) == 0)
		{
			strResult = L"%systemqueuefiles%";
		}
		else
		{
			int nFirstPos  = 0; 
			int nSecondPos = 0;
			BOOL bFind = FALSE;
			bFind = FindEnvironmentPos(szLongPathBuffer, nFirstPos, nSecondPos);
			if(bFind)
			{
				CString strLeft       ;
				CString strRight      ;
				CString strEnvName    ;
				CString strEnvVariable;

				strResult = szLongPathBuffer;
				strLeft    = strResult.Left(nFirstPos);
				strRight   = strResult.Mid (nSecondPos + 1);
				strEnvName = strResult.Mid(nFirstPos + 1, nSecondPos - nFirstPos - 1);
				TCHAR szTempBuf[MAX_PATH];
				DWORD dwResult = GetEnvironmentVariable(strEnvName.GetBuffer(), szTempBuf, MAX_PATH);
				if (dwResult > 0)
					strEnvVariable = szTempBuf;

				strResult = CombinationPath(strLeft, strEnvVariable, L"");
				strResult += strRight;
			}
			else
			{
				strResult = szLongPathBuffer;
			}
			goto Exit0;

		}
	}
    else if ( CString("tudou").CompareNoCase(pszName) == 0 )
    {
         DWORD len = sizeof(szLongPathBuffer);
         GetRegistryValue(HKEY_LOCAL_MACHINE,
             L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\��������",
             L"UninstallString",
             NULL,
             (LPBYTE)szLongPathBuffer,
             &len
             );
         if(wcslen(szLongPathBuffer) == 0)
            strResult = L"%tudou%";
         else
         {
             ::PathRemoveFileSpec(szLongPathBuffer);
             ::PathAppend(szLongPathBuffer,L"tudouva.ini");
             IniEditor IniEdit;
             IniEdit.SetFile(szLongPathBuffer);
             std::wstring tmpPath = IniEdit.ReadString(L"public",L"savedirectory");
             if(tmpPath.length() == 0)
                 strResult = L"%tudou%";
             else 
                 strResult = tmpPath.c_str();

         }

        goto Exit0;
    }else if ( CString("qvod").CompareNoCase(pszName) == 0 )
    {
        DWORD len = sizeof(szBuffer);
        GetRegistryValue(HKEY_LOCAL_MACHINE,
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\QvodPlayer",
            L"UninstallString",
            NULL,
            (LPBYTE)szLongPathBuffer,
            &len
            );
        if(wcslen(szLongPathBuffer) == 0)
            strResult = L"%qvod%";
        else
        {
            ::PathRemoveFileSpec(szLongPathBuffer);
            ::PathAppend(szLongPathBuffer,L"QvodPlayer.xml");
            TiXmlDocument xmlDoc;
            const TiXmlElement *pXmlQvodPlayer = NULL;
            const TiXmlElement *pXmlGeneral = NULL;
            strResult = L"%qvod%";
            if (!xmlDoc.LoadFile(UnicodeToAnsi(szLongPathBuffer).c_str(), TIXML_ENCODING_UTF8))
                goto Exit0;
            pXmlQvodPlayer = xmlDoc.FirstChildElement("QvodPlayer");
            if (!pXmlQvodPlayer)
                goto Exit0;
            pXmlGeneral = pXmlQvodPlayer->FirstChildElement("General");
            if (pXmlGeneral)
            {
                std::string strTmp(pXmlGeneral->Attribute("Defaultsavepath"));
                if(strTmp.length() == 0)
                    strResult = L"%qvod%";
                else strResult = Utf8ToUnicode(strTmp).c_str();
            }

        }

        goto Exit0;
    }
    else if ( CString("xunleikankan").CompareNoCase(pszName) == 0 )
    {
        DWORD len = sizeof(szBuffer);
        GetRegistryValue(HKEY_LOCAL_MACHINE,
            L"SOFTWARE\\Thunder network\\Xmp",
            L"storepath",
            NULL,
            (LPBYTE)szBuffer,
            &len
            );
        if(wcslen(szBuffer) == 0)
            strResult = L"%xunleikankan%";
        else
        {
            wcscat(szBuffer,L"\\VODCache");
            strResult =szBuffer;
        }

        goto Exit0;
    }
    else if ( CString("youku").CompareNoCase(pszName) == 0 )
    {
        DWORD len = sizeof(szBuffer);
        GetRegistryValue(HKEY_CURRENT_USER,
            L"SOFTWARE\\youku\\iKuAcc",
            L"CachePath",
            NULL,
            (LPBYTE)szBuffer,
            &len
            );
        if(wcslen(szBuffer) == 0)
            strResult = L"%youku%";
        else
        {
            strResult =szBuffer;
            if(strResult.Find(L"\\Desktop")!=-1)
                strResult = L"%youku%";
        }

        goto Exit0;
    }
    else if ( CString("ku6").CompareNoCase(pszName) == 0 )
    {
        DWORD len = sizeof(szLongPathBuffer);
        GetRegistryValue(HKEY_LOCAL_MACHINE,
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Ku6SpeedUpper",
            L"UninstallString",
            NULL,
            (LPBYTE)szLongPathBuffer,
            &len
            );
        if(wcslen(szLongPathBuffer) == 0)
        {
            CString StrSuffix = _T("\\kvideo_cache");;
            strResult = GetDrive(StrSuffix);
        }
        else
        {
            ::PathRemoveFileSpec(szLongPathBuffer);
            ::PathAppend(szLongPathBuffer,L"Ku6SpeedUpper.ini");
            IniEditor IniEdit;
            IniEdit.SetFile(szLongPathBuffer);
            std::wstring tmpPath = IniEdit.ReadString(L"Settings",L"BufPath");
            if(tmpPath.length() > 0)
                strResult = tmpPath.c_str();
            else
            {
                CString StrSuffix = _T("\\kvideo_cache");;
                strResult = GetDrive(StrSuffix);
                
            }
        }
        goto Exit0;
    }
    else if ( CString("ppstream").CompareNoCase(pszName) == 0 )
    {
        CString strTmp = GetFolderPath(L"CSIDL_APPDATA");
        strTmp += L"\\ppstream\\psnetwork.ini";
        if(!::PathFileExists(strTmp.GetBuffer()))
        {
            strTmp = L"";
            GetWindowsDirectory(szLongPathBuffer,MAX_PATH);
            strTmp = szLongPathBuffer;
            strTmp +=  L"\\psnetwork.ini";
        }
        IniEditor IniEdit;
        IniEdit.SetFile(strTmp.GetBuffer());
        std::wstring tmpPath = IniEdit.ReadString(L"vodnet",L"pgfpath");
        if(tmpPath.length()>0)
          ::PathRemoveFileSpec((LPWSTR)tmpPath.c_str());
        else
        {
            tmpPath = IniEdit.ReadString(L"vodnet",L"pgfpath1");
            if(tmpPath.length()>0)
                tmpPath.erase(tmpPath.length()-1);
        }
        strResult = tmpPath.c_str();
        goto Exit0;
    }
    else if ( CString("pptv").CompareNoCase(pszName) == 0 )
    {
        CString strTmp = GetFolderPath(L"CSIDL_COMMON_APPDATA");
        strTmp += L"\\PPLive\\Core\\config.ini";
        IniEditor IniEdit;
        IniEdit.SetFile(strTmp.GetBuffer());
        std::wstring tmpPath = IniEdit.ReadString(L"peer",L"cachepath");
        std::string utf8str = KUTF16_To_ANSI(tmpPath.c_str());
        tmpPath = Utf8ToUnicode(utf8str.c_str());
        if(tmpPath.length() == 0)
            strResult = L"%pptv%";
        else
            strResult = tmpPath.c_str();
        goto Exit0;
    }
    else if ( CString("fengxing").CompareNoCase(pszName) == 0 )
    {
        CString strTmp = GetFolderPath(L"CSIDL_PERSONAL");
        int a = strTmp.ReverseFind(L'\\');
        strTmp = strTmp.Mid(0,strTmp.ReverseFind(L'\\'));
        strTmp += L"\\funshion.ini";
        IniEditor IniEdit;
        IniEdit.SetFile(strTmp.GetBuffer());
        std::wstring tmpPath = IniEdit.ReadString(L"FILE_PATH",L"MEDIA_PATH");
        if(tmpPath.length() == 0)
            strResult = L"%fengxing%";
        else
            strResult = tmpPath.c_str();
        goto Exit0;
    }
    else if ( CString("qqlive").CompareNoCase(pszName) == 0 )
    {
       CString strTmp = GetFolderPath(L"CSIDL_APPDATA");
       strTmp += L"\\Tencent\\QQLive\\user.ini";
       IniEditor IniEdit;
       IniEdit.SetFile(strTmp.GetBuffer());
       std::wstring tmpPath = IniEdit.ReadString(L"Cache",L"Directory");
       if(tmpPath.length()>0)
       {
           tmpPath.erase(tmpPath.length()-1);
           strResult = tmpPath.c_str();
       }
       else strResult = L"%qqlive%";
       
       goto Exit0;
    }
	else if ( CString("firefox").CompareNoCase(pszName) == 0 )
	{
		WCHAR szPath[MAX_PATH] = {0};
		SHGetSpecialFolderPath(NULL, szPath, CSIDL_APPDATA, FALSE);
		std::wstring strPath;
		std::wstring strTemp;
		strPath = szPath;
		HANDLE hFile = INVALID_HANDLE_VALUE;
		if (strPath.rfind(L'\\') != strPath.size())
		{
			strPath += L"\\";
		}
		strPath += L"Mozilla\\Firefox\\profiles.ini";
		IniEditor inif;
		inif.SetFile(strPath.c_str());
		strTemp = inif.ReadString(L"Profile0", L"Path");
		if(strTemp.find(L'//') != -1)
		{
			strTemp.replace(strTemp.find(L'//'), 1, L"\\");
		}

		ZeroMemory(szPath, MAX_PATH);
		SHGetSpecialFolderPath(NULL, szPath, CSIDL_LOCAL_APPDATA, FALSE);
		strPath = szPath;
		if (strPath.rfind(L'\\') != strPath.size())
		{
			strPath += L"\\";
		}
		strPath += L"Mozilla\\Firefox\\";
		strPath += strTemp;
		strPath += L"\\cache";

		strResult = strPath.c_str();
		goto Exit0;
	}
    DWORD dwResult = GetEnvironmentVariable(pszName, szBuffer, MAX_PATH);
    if (dwResult > 0)
    {
        dwResult = 0;

        LPSTR pFileName = NULL;

        if (m_pfnGetLongPathName != NULL) 
            dwResult = m_pfnGetLongPathName(szBuffer, szLongPathBuffer, MAX_PATH);

        strResult = dwResult ? szLongPathBuffer : szBuffer;
    }
Exit0:
   
    return strResult;
}

CString CGetEnvPath::GetFolderPath(LPCTSTR pszName)
{
    CString strResult;
    TCHAR szBuffer[MAX_PATH] = { 0 };

    int nFolder = -1;

    int nCount = sizeof(g_csidlnamelist) / sizeof(g_csidlnamelist[0]);

    for (int i = 0; i < nCount; i++)
    {
        if (_tcscmp( pszName, g_csidlnamelist[i].pszCsidlName) == 0)
        {
            nFolder = g_csidlnamelist[i].nFolder;
            break;
        }
    }

    if (nFolder == -1)
        goto Exit0;
    
    if ( ::SHGetSpecialFolderPath( NULL, szBuffer, nFolder, FALSE) )
        strResult = szBuffer;
Exit0:
    return strResult;
}

CString CGetEnvPath::GetDrive(CString suffix)  //����·������ȡֻ������������
{
    int nPos = 0;
    CString strDrive = "?:";
    DWORD dwDriveList = ::GetLogicalDrives();
    CString strTmp;

    while (dwDriveList)
    {
        if (dwDriveList & 1)
        {	
            strDrive.SetAt (0, 'A' + nPos);
            ///�ж����ƶ�����
            {
                int nDiskType = GetDriveType(strDrive);   
                switch(nDiskType)
                {   
                case  DRIVE_NO_ROOT_DIR:
                    break;
                case  DRIVE_REMOVABLE: 
                    break;
                case  DRIVE_FIXED: 
                    {
                        strTmp += strDrive;
                        strTmp += suffix;
                        if(::PathIsDirectory(strTmp.GetBuffer()))
                            return strTmp;
                        strTmp = _T("");

                    }
                    break;
                case   DRIVE_REMOTE:
                    break;   
                case   DRIVE_CDROM:
                    break;
                }
            }
        }
        dwDriveList >>= 1;
        nPos++;
    }
    return strTmp;
}