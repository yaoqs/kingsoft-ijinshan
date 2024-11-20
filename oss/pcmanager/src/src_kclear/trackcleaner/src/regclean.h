#ifndef _REGCLEAN_H_
#define _REGCLEAN_H_

#define  DLL_API

#include "CleanProc.h"
#include "i_clean.h"

#include "winosver.h"
#include "fileopt.h"
#include "regopt.h"
#include "CmdLineParser.h"

/************************************************************************/
//����:��ע����������
//
/************************************************************************/

extern ScanFileCallBack g_fnScanFile;
extern ScanRegCallBack  g_fnScanReg;
extern void*			g_pMain;

class CRegClean:IClean
{
public:
	CRegClean();
	~CRegClean();
public:
	void	Start()
	{	
		m_bScan=TRUE; 
		m_fileOpt.UserBreadFlag(FALSE);
		m_regOpt.UserBreadFlag(FALSE);
	
	};
	void	StopScan()
	{
		m_bScan=FALSE; 
		m_fileOpt.UserBreadFlag(TRUE);
		m_regOpt.UserBreadFlag(TRUE);
	};
	
	//��Чdll
	BOOL ScanInvalidDll();
	BOOL ScanInvalidDll(LPCTSTR lpcszShareDllPath);
	BOOL InvalidDll(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
				//����ֵ��
	static BOOL WINAPI InvalidDll_myEnumerateReg(HKEY rootKey,LPCTSTR lpItemPath,LPCTSTR lpName,DWORD dwValueNameSize,LPBYTE lpValue ,DWORD dwValueSize,DWORD dwType,void* pUserData);
	
	//��Ч�Ҽ��˵�
	BOOL ScanInvalidMenu();
	BOOL ScanInvalidMenu(LPCTSTR lpcszMenuHandler);

	//��Ч��Ӧ�ó���·��
	BOOL ScanInvalidAppPath();
	BOOL ScanInvalidAppPath(LPCTSTR lpcszAppPath);

	//��Ч�ķ���ǽ����
	BOOL ScanIvalidFire();
	BOOL ScanIvalidFire(LPCTSTR lpcszShareDllPath);
	BOOL IvalidFire(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	
	//��Ч��MUI����
	BOOL ScanIvalidMUICache();
	BOOL ScanIvalidMUICache(LPCTSTR lpcszMUIPath);
	BOOL IvalidMUICache(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	
	//��Ч�İ����ĵ�
	BOOL ScanIvalidHelp();
	BOOL ScanIvalidHelp(LPCTSTR lpcszHelpPath);
	BOOL IvalidHelp(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
				//����ֵ����
	static BOOL WINAPI IvalidHelp_myEnumerateReg(HKEY rootKey,LPCTSTR lpItemPath,LPCTSTR lpName,DWORD dwValueNameSize,LPBYTE lpValue ,DWORD dwValueSize,DWORD dwType,void* pUserData);

	//��Ч������
	BOOL		ScanIvalidFont();
	BOOL		ScanIvalidFont(LPCTSTR lpcszFontsPath);
	BOOL		IvalidFont(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	
	//��Ч�İ�װ����
	BOOL		ScanIvalidInstall();
	BOOL		ScanIvalidInstall(LPCTSTR lpcszInstallPath);
	BOOL		ScanIvalidInstall2(LPCTSTR lpcszInstallPath);
	BOOL		IvalidInstall(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	//��Ч�ķ���װ����
	BOOL		ScanInvalidUnInstall();
	BOOL		ScanInvalidUnInstall(LPCTSTR lpcszUnInstallPath);
	//��Ч�Ŀ�ʼ��
	BOOL		ScanInvalidStartMenu();
	BOOL		ScanInvalidStartMenu(LPCTSTR lpcszStartMenu,LPCTSTR lpcszFolderPath);
	
	//��Ч��ACTIVEX��Ϣ
	BOOL		ScanInvelidActiveX();
	BOOL		ScanInvelidActiveX(LPCTSTR strActiveXPath);
	//��Ч������
	BOOL		ScanInvelidRun();
	BOOL		ScanInvelidRun(LPCTSTR lpcszRunPath);
	BOOL		InvelidRun(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);

	//�����ڻ���������·������ת��
	BOOL		ConvetPath(CString& strSourcPat);
	
	//��֤������
	BOOL		ValidDervice(CString& strPath);
	//��Ч���ļ�����
	BOOL		ScanValidFileAss();
	BOOL		ScanValidFileAss(LPCTSTR strFileAssPath);
	//��Ч������Ϣ
	BOOL		ScanInvalidClass();
	BOOL		ScanInvalidClass(LPCTSTR lpcszRegClassPath);

	BOOL		ScanInvalidClass2();
	BOOL		ScanInvalidClass2(LPCTSTR lpcszRegClassPath);
	//������Ϣ
	BOOL		ScanRegRedundancey();
	BOOL		ScanRegRedundancey(LPCTSTR lpcszRegPath);
	static BOOL WINAPI RegRedancey_myEnumerateReg(HKEY rootKey,LPCTSTR lpItemPath,LPCTSTR lpName,DWORD dwValueNameSize,LPBYTE lpValue ,DWORD dwValueSize,DWORD dwType,void* pUserData);
	BOOL		RegRedundancey(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
private:
	CFileOpt				m_fileOpt;
public:
	CRegOpt					m_regOpt;
	BOOL					m_bScan;
public:
	static BOOL WINAPI myEnumerateFile(LPCTSTR lpFileOrPath, void* pUserData,LARGE_INTEGER filesize);
	static BOOL WINAPI myEnumerateReg(HKEY rootKey,LPCTSTR lpItemPath,LPCTSTR lpName,DWORD dwValueNameSize,LPBYTE lpValue ,DWORD dwValueSize,DWORD dwType,void* pUserData);
public:
	
};


#endif