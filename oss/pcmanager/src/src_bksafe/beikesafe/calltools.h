//////////////////////////////////////////////////////////////////////////
//ϵͳ���߼�:��鹤���Ƿ������ذ�װ���������ذ�װ���߻�ִ�й���


#pragma once
//#include "vulfix/BeikeUtils.h"
#include "downloadtoolsdlg.h"
#include <communits/VerifyFileFunc.h>
#include "iefix/RegisterOperate.h"
#include "htmlcallcpp.h"
#include "miniutil/fileversion.h"
#include "atlutil.h"
#include "common/bksafelog.h"

#pragma comment(lib,"Version.lib")

#define REG_INSTALL_KEY_KBIGFILE L"SOFTWARE\\KSafe\\KBigFile"
#define REG_INSTALL_KEY_KMSPEED	 L"SOFTWARE\\KSafe\\KMSpeed"
#define REG_INSTALL_KEY_KPRIVACY L"SOFTWARE\\KSafe\\KPRIVACY"

#define KBIGFILE_INSTALLER_DOWNLOAD_URL			_T("http://dl.ijinshan.com/safe/bigfile.pack")
#define KMSPEED_INSTALLER_DOWNLOAD_URL			_T("http://dl.ijinshan.com/safe/kmspeed.pack")
#define KPRIVACY_INSTALLER_DOWNLOAD_URL			_T("http://dl.ijinshan.com/safe/kprivacy.pack")

#define KBIGFILE_INSTALLER_TEMP_FILE_NAME		_T("\\ksafe_setup_bigfile.exe")
#define KMSPEED_INSTALLER_TEMP_FILE_NAME		_T("\\ksafe_setup_kmspeed.exe")
#define KPRIVACY_INSTALLER_TEMP_FILE_NAME		_T("\\ksafe_setup_kprivacy.exe")

#define KBIGFILE_VERSION_FILE_NAME		_T("kbigfile.exe")
#define KMSPEED_VERSION_FILE_NAME		_T("kmspeed.exe")
#define KPRIVACY_VERSION_FILE_NAME		_T("kprivacy.exe")




class CBKRunoptLog
{
public:
	static CBKRunoptLog* GetRunoptLogPtr()
	{
		static CBKRunoptLog log;
		return &log;
	}

	BKSafeLog::CBKSafeLog GetLogModule()
	{
		return bksafelog;
	}
private:
	BKSafeLog::CBKSafeLog bksafelog;
	CBKRunoptLog()
	{
		bksafelog.SetLogForModule(BKSafeLog::enumBKSafeRunoptLog);
	}
};

interface IBKCallSysTools
{
	virtual void callBackCheck() = 0;
	virtual void  callBackInstall() = 0;
	virtual void  callBackExec() = 0;
};

class BKCallSysTools
{
public:
	BKCallSysTools()
	{
		//check
 		CONNECT_JS_CALL_HANDLER(check, (JSCallbackFunction)&IsNeedDownloadTool, this);
 		//download
 		CONNECT_JS_CALL_HANDLER(install, (JSCallbackFunction)&InstallBKSafeTool, this);
 		//exec
 		CONNECT_JS_CALL_HANDLER(exec, (JSCallbackFunction)&ExecBKSafeTool, this);

		m_ptrCallback = NULL;

		//��Ҫ���˵�URL
		m_arrUrlFilter.RemoveAll();

		m_arrUrlFilter.Add(L"dl.ijinshan.com");
		m_arrUrlFilter.Add(L"download.duba.net");
		m_arrUrlFilter.Add(L"dl.sd.keniu.com");
		m_arrUrlFilter.Add(L"dl.keniu.com");

	}

	~BKCallSysTools()
	{

	}

	CSimpleArray<CString>	m_arrUrlFilter;
	//////////////////////////////////////////////////////////////////////////
	//���ûص�
	IBKCallSysTools	* SetCallbackPtr(IBKCallSysTools* ptr)
	{
		if (NULL == ptr)
			return NULL;

		IBKCallSysTools* p = m_ptrCallback;
		m_ptrCallback = ptr;

		return p;
	}

	//////////////////////////////////////////////////////////////////////////
	//��ȡ�ص�ָ��
	IBKCallSysTools	* GetCallbackPtr()
	{
		return m_ptrCallback;
	}



	//////////////////////////////////////////////////////////////////////////
	//JS �ӿں���

	//////////////////////////////////////////////////////////////////////////
	//����Ƿ���Ҫ���أ��������0��ʾ��Ҫ���أ�1��ʾ����ֱ�ӵ������У�����ֵΪδ֪����

	static int		IsNeedDownloadTool(DISPPARAMS* params, VARIANT* retval , void* pContext)
	{
		int nRet = -1;

		BKCallSysTools* _pThis = static_cast<BKCallSysTools*>(pContext);
		if (NULL == _pThis)
			return nRet;

		do 
		{

			//���������Ƿ���Ч
			if (params->cArgs < 3)
			{
				CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Check param count error.count = %d", params->cArgs);
				break;
			}

			CString strPath			= params->rgvarg[2],
					strFileName		= params->rgvarg[1],
					strLastVer		= params->rgvarg[0],
					strCurFileVer	= L"";

			CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Check: param -> path = %s, filename = %s, ver = %s", strPath, strFileName, strLastVer);
			//ת���ļ�·��
			_pThis->TranslatePath(strPath);

			//�����Ƿ���Ч
			if (TRUE == strPath.IsEmpty() ||
				TRUE == strFileName.IsEmpty() ||
				TRUE == strLastVer.IsEmpty())
			{
				CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Check param is error.");
				break;
			}
			
			//CWinPath exePath = strPath;
			if ( PathIsDirectory(strPath) )
			{
				strPath.Append(L"\\");
				strPath.Append(strFileName);
			}

			//ָ�����ļ������ڻ����ļ��汾С�����°汾����Ҫ����
			if (FALSE == PathFileExists(strPath))
			{
				CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Check file no exists need download.file = %s", strPath);
				nRet = 0;
				break;
			}

			GetFileVersion(strPath, strCurFileVer);
			//�����ȡ�ļ�ʧ���ˣ������ļ��Ѿ����ƻ����ˣ���ô����������
			if (TRUE == strCurFileVer.IsEmpty())
			{
				CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Check: get current file ver error.file = %s", strPath);
				nRet = 0;
				break;
			}

			//������ذ汾С�����°汾������
			if (TRUE == VersionLess(strCurFileVer, strLastVer))
			{
				CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Check: current file ver less lastver.curver = %s, lastver = %s", strPath, strLastVer);
				nRet = 0;
				break;
			}

			CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Check : need download file.file = %s", strPath);

			//������������������Ҫ����
			nRet = 1;

		} while (FALSE);

		//����ֵ
		if (NULL != retval)
		{
			::VariantInit(retval);
			retval->vt = VT_INT;
			retval->intVal = nRet;
		}

		if (NULL != _pThis->GetCallbackPtr())
			_pThis->GetCallbackPtr()->callBackCheck();

		return nRet;
	}

	//////////////////////////////////////////////////////////////////////////
	//�������°汾
	//����0��ʾ���سɹ��������ʾʧ��
	static int		InstallBKSafeTool(DISPPARAMS* params, VARIANT* retval , void* pContext)
	{
		int nRet = -1;

		do 
		{
			BKCallSysTools* _pThis = static_cast<BKCallSysTools*>(pContext);
			if (NULL == _pThis)
				break;

			//���������������ֱ�ӷ���ʧ��
			if (params->cArgs < 3)
			{
				CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Install: param count error.cont = %d", params->cArgs);
				break;
			}

			//��ȡ����URL
			CString		strURL			= params->rgvarg[2],
						strPath			= params->rgvarg[1],
						strParam		= params->rgvarg[0],
						strTitle		= L"",
						strFileName		= L"";//params->rgvarg[1],

			if ( params->cArgs > 3)
				strTitle = params->rgvarg[3];

			CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Install: param -> url = %s, path = %s, filename = %s, param = %s, title= %s", strURL,
				strPath, strFileName, strParam, strTitle);

			//��ȡ�ļ�·��
			_pThis->TranslatePath(strPath);

			//У������Ŀ¼
		//	CWinPath exePath = strPath;
			if ( FALSE == PathIsDirectory(strPath) ||
				 FALSE  == PathFileExists(strPath))
			{//�������һ��Ŀ¼����Ŀ¼�����ڣ���ֱ��ȥMS����ʱĿ¼
				GetTempPath(MAX_PATH, strPath.GetBuffer(MAX_PATH));
				strPath.ReleaseBuffer(MAX_PATH);
			}

			if (TRUE == strURL.IsEmpty() ||
				TRUE == strPath.IsEmpty() ||
				FALSE == PathIsDirectory (strPath))
			{
				CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Install: param error.");
				break;
			}

			//��֤URL�Ƿ���Ч
 			CUrl url;
 			url.CrackUrl(strURL);
			CString strHost = url.GetHostName();

			int nFind = -1;
			for (int i = 0; i < _pThis->m_arrUrlFilter.GetSize(); i++)
			{
				if (-1 != strHost.Find( _pThis->m_arrUrlFilter[i]) )
				{
					nFind = i;
					break;
				}
			}

			if (-1 == nFind)
			{
				CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Install: param url error");
				break;
			}

			//��ȡ�����ļ���
			int nIndex = strURL.ReverseFind(L'//');
			if (nIndex > 0)
			{
				strFileName = strURL.Mid(nIndex+1);
			}
			else
			{
				strFileName = L"ksafe_tools_tmp.exe";
			}

			CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Install: filename = %s", strFileName);
			//��ʼ���ز�����
			_pThis->DownloadAndInst(strURL, strPath, strFileName, strParam, strTitle);

			nRet = 0;


		} while (FALSE);

		//����ֵ
		if (NULL != retval)
		{
			::VariantInit(retval);
			retval->vt = VT_INT;
			retval->intVal = nRet;
		}

		return nRet;
	}

	//////////////////////////////////////////////////////////////////////////
	//���ñ��س���
	static int		ExecBKSafeTool(DISPPARAMS* params, VARIANT* retval , void* pContext)
	{
		int nRet = -1;

		do 
		{
			BKCallSysTools* _pThis = static_cast<BKCallSysTools*>(pContext);
			if (NULL == _pThis)
				break;

			//���������������ֱ�ӷ���ʧ��
			if (params->cArgs < 3)
			{
				CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"exec: param count error.count = %d", params->cArgs);
				break;
			}

			//��֤�����Ƿ���Ч
			CString		strPath			= params->rgvarg[2],
						strFileName		= params->rgvarg[1],
						strParam		= params->rgvarg[0];

			CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"exec: param -> path = %s, filename=%s, param = %s", strPath, strFileName, strParam);

			//��ȡ������·��
			_pThis->TranslatePath(strPath);

			if (TRUE == strPath.IsEmpty() ||
				TRUE == strFileName.IsEmpty())
			{
				CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"Exec: param error.");
				break;
			}

			//CWinPath exePath = strPath;
			if ( PathIsDirectory(strPath) )
			{
				strPath.Append(L"\\");
				strPath.Append(strFileName);
			}

			if (FALSE == PathFileExists(strPath))
			{
				CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"exec: file no exist. file = %s", strPath);
				break;
			}

			//����
			_pThis->ExecuteTool(strPath, strParam);

		} while (FALSE);

		//����ֵ
		if (NULL != retval)
		{
			::VariantInit(retval);
			retval->vt = VT_INT;
			retval->intVal = nRet;
		}

		return nRet;
	}


	void	TranslatePath( CString &strPath )
	{

		CString		strTmpPath = strPath;
		CAtlArray<CString>	arrPath;
		if (0 != _ParsePath(strPath, arrPath, L"|"))
		{
			if (0 == arrPath[0].CompareNoCase(L"macropath") &&
				2 == arrPath.GetCount())
			{//ͨ����ָ��·��
				strPath = arrPath[1];
				_TranslatePath(strPath);
			}else if (0 == arrPath[0].CompareNoCase(L"regpath") ||
				4 == arrPath.GetCount())
			{//ͨ��ע����ȡ·��
				TCHAR pszPath[MAX_PATH] = {0};
				if (0 == RegisterOperate::CRegisterOperate::GetRegOperatePtr()->GetRegValue(_GetRetKey(arrPath[1]), arrPath[2], arrPath[3], pszPath, sizeof(pszPath)))
					strPath = pszPath;
			}
		}

	}



	

public:
	BOOL HasInstallLatest(LPCTSTR lpszKey, LPCTSTR lpszSubKey, LPCTSTR lpszVerFile, LPCTSTR lpszVersion)
	{
		BOOL bRet = FALSE;
		if (HasInstalled(lpszKey, lpszSubKey, lpszVerFile))
		{
			if (IsLatestVersion(lpszVerFile,lpszVersion) >= 0)
			{
				bRet = TRUE;
				goto Exit0;
			}
		}
Exit0:
		return bRet;
	}

	BOOL HasInstalled(LPCTSTR lpszKey, LPCTSTR lpszSubKey, LPCTSTR lpszVerFile)
	{
		BOOL bRet = FALSE;
		if (lpszKey == NULL || lpszSubKey == NULL || lpszVerFile == NULL)
		{
			bRet = FALSE;
			goto Exit0;
		}
		TCHAR szFilePath[MAX_PATH] = {0};
		ULONG uLen = MAX_PATH;
		LONG lRet = _GetRegStringValue(HKEY_LOCAL_MACHINE, lpszKey, lpszSubKey, szFilePath, uLen);
		if (0 == lRet)		
		{
			::PathAppend(szFilePath, lpszVerFile);
			if (::PathFileExists(szFilePath))
			{
				bRet = TRUE;
				goto Exit0;
			}
			else
			{
				bRet = FALSE;
				goto Exit0;
			}
		}
Exit0:
		return bRet;
	}

	BOOL IsLatestVersion(LPCTSTR lpszFilePath, LPCTSTR lpszLatestVer)
	{
/*
		if ((lpszFilePath == NULL) || (lpszLatestVer == NULL))
			return FALSE;

		LARGE_INTEGER lCurrentVer = {0};
		LARGE_INTEGER lLatestVer = ParseVersion(lpszLatestVer);
		GetFileVersion(lpszFilePath,lCurrentVer);

		return CompareVersion(lCurrentVer,lLatestVer);
*/
		return TRUE;
	}

	void ExecuteTool(LPCTSTR pszFileFullPath, LPCTSTR lpszParam)
	{
		_RunTools(pszFileFullPath, lpszParam);
	}



	int DownloadAndInst(CString strURL, CString strPath, CString strFileName, CString strParam, CString strTitle)
	{
		CString strDownUrl,strSetupFile;

		strSetupFile.Format(L"%s\\%s", strPath, strFileName);

		m_pDownloadDlg = new CToolsDownloadDlg(strURL,strSetupFile, strParam, strTitle);
		if (m_pDownloadDlg)
		{
			return m_pDownloadDlg->DoModal();
		}

		return -1;
	}

private:
	LONG _GetRegStringValue( HKEY hKey, LPCTSTR pszKey, LPCTSTR pszSubKey, LPTSTR pszBuffer, ULONG uLen )
	{
		if( pszKey == NULL || pszSubKey == NULL || pszBuffer == NULL)
			return -1;	
		CRegKey reg;
		LONG lRet = reg.Open( hKey, pszKey, KEY_READ );
		if( lRet != 0 )
			return lRet;
		lRet = reg.QueryStringValue( pszSubKey, pszBuffer, &uLen );
		return lRet;
	}
private:
	CToolsDownloadDlg* m_pDownloadDlg;


	void _RunTools(LPCTSTR pszFileFullPath, LPCTSTR pszParam)
	{
		if (NULL == pszFileFullPath || NULL == pszParam)
			return;


	//	TCHAR szFilePath[MAX_PATH] = {0};
		ULONG uLen = MAX_PATH;
		BOOL bIsKingsoftSigner = FALSE;
		bIsKingsoftSigner = CVerifyFileFunc::GetPtr()->CheckKingSoftFileSigner(pszFileFullPath) == 0;

		CBKRunoptLog::GetRunoptLogPtr()->GetLogModule().WriteLog(L"EXEC: kingsoft signer is %d, file = %s, param = %s", bIsKingsoftSigner, pszFileFullPath, pszParam);;
		if (::PathFileExists(pszFileFullPath) && bIsKingsoftSigner)
		{
			ShellExecute(NULL, _T("open"), pszFileFullPath, pszParam, NULL, SW_SHOW);
/*
			STARTUPINFO si = {sizeof(STARTUPINFO)};
			PROCESS_INFORMATION pi;
			int nProgress = 1;
			DWORD dwRet = 0;

			CString strCmdLine;

			strCmdLine.Format(L"%s %s", pszFileFullPath, pszParam);
			BOOL bRet = ::CreateProcess(NULL, (LPTSTR)(LPCTSTR)strCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
			if (!bRet)
				return ;

			::CloseHandle(pi.hThread);
			::WaitForSingleObject(pi.hProcess,INFINITE);
			::GetExitCodeProcess(pi.hProcess, &dwRet);
			::CloseHandle(pi.hProcess);
*/

			return ;
		}

	}

	void	_TranslatePath( CString &strPath )
	{
		int     i = -1;
		HRESULT hr;
		LPCWSTR lpwszPath = NULL;
		CString strPrefix;
		CPath path;
		CString strPredef;

		if ( strPath.GetLength() < 3 ) // %*%����Ϊ3�ˡ�
		{
			return;
		}

		path.m_strPath = strPath;

		lpwszPath = ( LPCWSTR )strPath;
		if ( L'%' != lpwszPath[ 0 ] )
		{
			return;
		}

		i = strPath.Find( L'%', 1 );
		if ( -1 == i )
		{
			return;
		}

		strPrefix = strPath.Mid( 1, i - 1 );

		if ( 0 == strPrefix.CompareNoCase( L"ksafepath" ) )
		{
			hr = CAppPath::Instance().GetLeidianAppPath( path.m_strPath );
			if ( FAILED( hr ) )
			{
				return;
			}
		}
		else if ( 0 == strPrefix.CompareNoCase( L"ksafedata" ) )
		{
			hr = CAppPath::Instance().GetLeidianDataPath( path.m_strPath );
			if ( FAILED( hr ) )
			{
				return;
			}
		}
		else if ( 0 == strPrefix.CompareNoCase( L"ksafeconfig" ) )
		{
			hr = CAppPath::Instance().GetLeidianCfgPath( path.m_strPath );
			if ( FAILED( hr ) )
			{
				return;
			}
		}
		else if ( 0 == strPrefix.CompareNoCase( L"ksafeupdate" ) )
		{
			hr = CAppPath::Instance().GetLeidianLogPath( path.m_strPath );
			if ( FAILED( hr ) )
			{
				return;
			}

			path.Append( L"update" );
		}
		else if ( 0 == strPrefix.CompareNoCase( L"ksafeviruslib" ) )
		{
			hr = CAppPath::Instance().GetLeidianAvsPath( path.m_strPath );
			if ( FAILED( hr ) )
			{
				return;
			}

			path.Append( L"ksg" );
		}
		else if ( 0 == strPrefix.CompareNoCase( L"system32" ) )
		{
			TCHAR   wszBuffer[ MAX_PATH + 1 ] = { 0 };
			DWORD   dwBytes = MAX_PATH;

			wszBuffer[ dwBytes ] = 0;

			dwBytes = GetSystemDirectory( wszBuffer, dwBytes );
			if ( 0 == dwBytes )
			{
				hr = HRESULT_FROM_WIN32( GetLastError() );
				return;
			}

			path.m_strPath = wszBuffer;
		}
		else if ( 0 == strPrefix.CompareNoCase( L"program files" ) )
		{
			TCHAR   wszBuffer[ MAX_PATH + 1 ] = { 0 };
			DWORD   dwBytes = MAX_PATH;

			wszBuffer[ dwBytes ] = 0;

			if ( SHGetSpecialFolderPath( NULL, wszBuffer, CSIDL_PROGRAM_FILES, FALSE  ) )
			{
				path.m_strPath = wszBuffer;
			}
			else
			{
				hr = HRESULT_FROM_WIN32( GetLastError() );
				return;
			}
		}
		else
		{
			return;
		}

		if ( i < ( strPath.GetLength() - 1 ) )
		{
			path.Append( strPath.Mid( i + 1 ) );
		}

		strPath = path.m_strPath;
	}

	HKEY	_GetRetKey(CString strRoot)
	{
		HKEY hkey = NULL;
		if ( strRoot.CompareNoCase( L"HKCU" ) == 0 )
		{
			hkey = HKEY_CURRENT_USER;
		}
		else if ( strRoot.CompareNoCase( L"HKLM" ) == 0 )
		{
			hkey = HKEY_LOCAL_MACHINE;
		}
		else if ( strRoot.CompareNoCase( L"HKCR" ) == 0 )
		{
			hkey = HKEY_CLASSES_ROOT;
		}

		return hkey;

	}

	int		_ParsePath(CString strPath, CAtlArray<CString>& arrPath, LPCTSTR pszToken)
	{
		int nRet = -1;

		CString strValue = strPath;
		strValue += pszToken;
		int nIndex = strPath.Find(pszToken);
		while (-1 != nIndex)
		{
			arrPath.Add(strValue.Left(nIndex));
			strValue = strValue.Mid(nIndex+1);

			nIndex = strValue.Find(pszToken);
		}

		nRet = arrPath.GetCount();

		return nRet;
	}

	private:
		IBKCallSysTools*		m_ptrCallback;
		
};