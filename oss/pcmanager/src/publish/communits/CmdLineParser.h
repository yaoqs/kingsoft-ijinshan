// dummyz@126.com

#ifndef _CMDLINE_PARSER_INC_
#define _CMDLINE_PARSER_INC_

#include <list>
#include <atlcoll.h>
#include <ShlObj.h>
#include <ShellAPI.h>

class CCmdLineParser  
{
public:
	enum {
		DEF_CUR_DIR		= 0x0001, // �ڵ�ǰĿ¼����
		DEF_ENV_VAR		= 0x0002, // ��Ĭ�ϵĻ�����������
		DEF_EXT_NAME	= 0x0004, // ʹ��Ĭ�Ͽ�ִ�е���չ��
		NEED_PARAM		= 0x0008,  // ��������
		DEF_FLAG		= DEF_CUR_DIR | DEF_ENV_VAR | DEF_EXT_NAME | NEED_PARAM
	};

public:
	CCmdLineParser(DWORD dwFlag = DEF_FLAG);
	CCmdLineParser(LPCTSTR lpCmdLine /*dwFlag = DEF_CUR_DIR | DEF_ENV_VAR | DEF_EXT_NAME | NEED_PARAM*/);
	virtual ~CCmdLineParser();
	
	BOOL	DoParser(LPCTSTR lpCmdLine, 
		LPCTSTR lpCurDir = NULL, 
		LPCTSTR lpEnvVars = NULL, 
		LPCTSTR lpExtNames = NULL,
		LPCTSTR lpParentPath = NULL
		);

	void	SetFlag(DWORD dwFlag) {
		m_dwFlag = dwFlag;
	}

	LPCTSTR GetCmd() const {
		return (m_szCmd[0] != 0) ? m_szCmd : NULL;
	}

	LPCTSTR GetParam() const {
		return m_lpParam;
	}

private:
	BOOL	ExpandExtNames(LPTSTR lpFilePath, LPCTSTR lpExtNames);
	BOOL	ExpandEnvVars(LPTSTR lpFilePath, LPCTSTR lpEnvVars, LPCTSTR lpExtNames);

	virtual LPTSTR	ExpandMacro(LPCTSTR lpCmdBegin);
	LPTSTR	ExpandMacro2(LPCTSTR lpCmdBegin);
	LPTSTR	ExpandRelative(LPCTSTR lpCmdBegin, LPCTSTR lpCurDir, BOOL bQuotation);
	BOOL	ExpandAbsolute(LPCTSTR lpCmdBegin, LPCTSTR lpExtNames, BOOL bQuotation);

	void	ExpandParam(LPCTSTR lpCmdEnd);

	BOOL	_DoParser(LPCTSTR lpCmdLine, 
		LPCTSTR lpCurDir = NULL, 
		LPCTSTR lpEnvVars = NULL, 
		LPCTSTR lpExtNames = NULL,
		LPCTSTR lpParentPath = NULL
		);

protected:
	TCHAR	m_szCmd[MAX_PATH + 10]; // �༸���ֽڷ�ֹ���

	LPTSTR	m_lpParam;
	DWORD	m_dwFlag;
};

DWORD GetFileListFromCmd(LPCTSTR lpCmd, LPCTSTR lpParam, CAtlArray<CString>& fileArray, LPCTSTR lpCurDir);
inline DWORD GetFileListFromCmd(CCmdLineParser& cmdParser, CAtlArray<CString>& fileArray, LPCTSTR lpCurDir) 
{
	return GetFileListFromCmd(cmdParser.GetCmd(), cmdParser.GetParam(), fileArray, lpCurDir);
}

//64֧�֣��ļ�·�����⡣ 12/29/2010 zhaozhixiong
//1.PROGRAM FILE��Ҫ֧��XP�����ϣ�ֻ���Լ���ע����Ǹ���ȡĿ¼�ĺ��������ض�����û�õ�
//2.SHGetValue���Զ���ע����еĻ�������ת������������ֻ����REGXXXXϵ�к�����ȡ���Լ���ת��
//3.�ر��ļ��ض��������м�ֵ����windows\system32����·��
class CCmdLineParser64 : public  CCmdLineParser
{
	LPTSTR ExpandMacro(LPCTSTR lpCmdBegin)
	{
		size_t nMacroLen, nExpandMacroLen;
		LPTSTR lpCmdBuff = NULL;

		if ( _tcsnicmp(lpCmdBegin, _T("%SystemRoot%"), nMacroLen = sizeof ("%SystemRoot%") - 1) == 0 ||
			_tcsnicmp(lpCmdBegin, _T("%windir%"), nMacroLen = sizeof ("%windir%") - 1) == 0
			)
		{
			HKEY hKey = NULL;
			DWORD dwType = 0;
			nExpandMacroLen = MAX_PATH;

			if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				_T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"),
				NULL, 
				KEY_ALL_ACCESS | KEY_WOW64_64KEY,
				&hKey))
			{
				RegQueryValueEx(hKey, _T("SystemRoot"), NULL, &dwType, (LPBYTE)m_szCmd, (LPDWORD)&nExpandMacroLen);
				nExpandMacroLen = _tcslen(m_szCmd);
				RegCloseKey(hKey);
			}
		}
		else if ( _tcsnicmp(lpCmdBegin, _T("%ProgramFiles%"), nMacroLen = sizeof ("%ProgramFiles%") - 1) == 0 )
		{
			HKEY hKey = NULL;
			DWORD dwType = 0;
			nExpandMacroLen = MAX_PATH;

			if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion"),
				NULL, 
				KEY_ALL_ACCESS | KEY_WOW64_64KEY,
				&hKey))
			{
				RegQueryValueEx(hKey, _T("ProgramFilesDir"), NULL, &dwType, (LPBYTE)m_szCmd, (LPDWORD)&nExpandMacroLen);
				nExpandMacroLen = _tcslen(m_szCmd);
				RegCloseKey(hKey);
			}
		}
		else if ( _tcsnicmp(lpCmdBegin, _T("%CommonProgramFiles%"), nMacroLen = sizeof ("%CommonProgramFiles%") - 1) == 0 )
		{
			HKEY hKey = NULL;
			DWORD dwType = 0;
			nExpandMacroLen = MAX_PATH;

			if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion"),
				NULL, 
				KEY_ALL_ACCESS | KEY_WOW64_64KEY,
				&hKey))
			{
				RegQueryValueEx(hKey, _T("CommonFilesDir"), NULL, &dwType, (LPBYTE)m_szCmd, (LPDWORD)&nExpandMacroLen);
				nExpandMacroLen = _tcslen(m_szCmd);
				RegCloseKey(hKey);
			}
		}
		else if ( _tcsnicmp(lpCmdBegin, _T("%Temp%"), nMacroLen = sizeof ("%Temp%") - 1) == 0 ||
			_tcsnicmp(lpCmdBegin, _T("%Tmp%"), nMacroLen = sizeof ("%Tmp%") - 1) == 0
			)
		{
			nExpandMacroLen = GetTempPath(MAX_PATH, m_szCmd);
		}
		else 
		{
			// ��֧�ֵĺ�·��
			goto _Failed_Exit;
		}

		if ( nExpandMacroLen != 0 )
		{
			size_t dwBuffLen = nExpandMacroLen + _tcslen(lpCmdBegin + nMacroLen) + 2;

			lpCmdBuff = new TCHAR[dwBuffLen];
			if ( lpCmdBuff != NULL )
			{
				_tcscpy(lpCmdBuff, m_szCmd);
				if ( lpCmdBuff[nExpandMacroLen - 1] == _T('\\') )
				{
					nExpandMacroLen--;
				}

				_tcscpy(lpCmdBuff + nExpandMacroLen, lpCmdBegin + nMacroLen);
			}
		}

_Failed_Exit:
		return lpCmdBuff;
	}

};

class CRunoptCmdLineParser : public CCmdLineParser64
{
public:
	CRunoptCmdLineParser(LPCTSTR lpCmdLine) :m_lpCmdLine(lpCmdLine)
	, m_bFileExist(TRUE)
	{
		m_Parser.DoParser(lpCmdLine);
	}
	virtual ~CRunoptCmdLineParser(){}

	LPCTSTR	GetCmd()
	{
		if (m_Parser.GetCmd() == NULL && _tcslen(m_lpCmdLine) > 0)
		{
			m_bFileExist = FALSE;
			int nArgCount = 0;
			LPWSTR* lpParsedCmdLine = ::CommandLineToArgvW(m_lpCmdLine,&nArgCount); 
			if ( lpParsedCmdLine != NULL )
				return lpParsedCmdLine[0];
			else
				return NULL;
		}
		else
			return m_Parser.GetCmd();
	}

	LPCTSTR GetParam()
	{
		return m_Parser.GetParam();
	}

	BOOL IsPEFileExist()
	{
		return m_bFileExist;
	}

protected:
	CCmdLineParser64	m_Parser;
	BOOL			m_bFileExist;
	LPCTSTR			m_lpCmdLine;
};

#endif /* _CMDLINE_PARSER_INC_ */