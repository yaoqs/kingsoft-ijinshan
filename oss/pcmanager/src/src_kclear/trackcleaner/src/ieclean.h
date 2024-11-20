#ifndef _IECLEAN_H_
#define _IECLEAN_H_

#include "CleanProc.h"
#include "i_clean.h"

#include "winosver.h"
#include "fileopt.h"
#include "regopt.h"
#include "FileMapWrite.h"
#include <string>
#include "apphistory.h"

/************************************************************************/
//����:����IEʹ�úۼ� 
//
/************************************************************************/

extern ScanFileCallBack g_fnScanFile;
extern ScanRegCallBack  g_fnScanReg;
extern void*			g_pMain;

class CIEClean :IClean
{
public:
	CIEClean();
	virtual ~CIEClean();
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
	//��ʱ�ļ��� 1
	BOOL	ScanIETempFolder();
	BOOL	ScanIETempFolder(LPCTSTR lpFileOrFolderPath);
	BOOL	TempFoldFolder(LPCTSTR lpFileOrPath,LARGE_INTEGER filesize);
	//���ʹ�����ַ 2
	BOOL	ScanVisitHost();
	BOOL	ScanVisitHost(LPCTSTR lpFileOrFolderPath);
	BOOL	VisitHost(LPCTSTR lpFileOrPath,LARGE_INTEGER filesize);
	//IE Cookie 3
	BOOL	ScanIECookie(int nType);
	BOOL	ScanIECookie(LPCTSTR lpszIECookiePath);
	BOOL	IECookie(LPCTSTR lpFileOrPath,LARGE_INTEGER filesize);
	
	BOOL	ScanMaxthon3Cookies();
	//��ַ������ 4
	BOOL	ScanIEAddrBar();
	BOOL	ScanIEAddrBar(LPCTSTR lpszIEAddrBarPath);
	BOOL	IEAddrBar(LPCTSTR lpValueName,LPCTSTR lpValueData);
	//ie����
	//����
	BOOL	ScanIEPass(int nType);
	BOOL	ScanIEPassword(LPCTSTR lpszIEAddrBarPath);
	BOOL	IEPassword(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	//ie��
	//����
	BOOL	ScanIEFrom(int nType);
	BOOL	ScanIEFrom(LPCTSTR lpszIEAddrBarPath);
	BOOL	IEFrom(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	BOOL	IEFrom_Clean();
	//Ie����
	BOOL	CleanIEPassword();
	//Ie��
	BOOL	CleanFrom();
	//����index�ļ�
	BOOL	_CleanIndexDat(); //�����κ�����
	BOOL	CleanIndexDat();
	BOOL	CleanIndex(LPCTSTR lpFileOrPath,LARGE_INTEGER filesize);
	BOOL	ClearLen(LPCTSTR lpFile);
	BOOL	WipeTime(LPCTSTR lpFile);

	//���ie��ʷ��¼
	BOOL    ScanIEHistory();
	BOOL    CleanIEHistory(CString pszUrl);
	std::string deescapeURL(const std::string &URL);
	short int hexChar2dec(char c) ;

	//��������
	BOOL	IsWindowsNT();//�ж�ϵͳ
	BOOL	IsWindows2k();
	BOOL	GetUserSid(PSID* ppSid);
    void	GetSidString(PSID pSid, CString& strSid);
	BOOL	GetOldSD(HKEY hKey, LPCTSTR pszSubKey, BYTE** pSD);
	BOOL	CreateNewSD(PSID pSid, SECURITY_DESCRIPTOR* pSD, PACL* ppDacl);
	BOOL	RegSetPrivilege(HKEY hKey, LPCTSTR pszSubKey, SECURITY_DESCRIPTOR* pSD, BOOL bRecursive);

private:
	CFileOpt				m_fileOpt;
	CRegOpt					m_regOpt;
	TCHAR					m_szLoginName[MAX_PATH];
	BOOL					m_bScan;
	int		                m_nFlags;
	CAppHistory             m_appHistory;
	BOOL                    m_bFlagPass[10000];
	BOOL                    m_bFlagForm[10000];
public:
	static BOOL WINAPI myEnumerateFile(LPCTSTR lpFileOrPath, void* pUserData,LARGE_INTEGER filesize);
	static BOOL WINAPI myEnumerateReg(HKEY rootKey,LPCTSTR lpItemPath,LPCTSTR lpName,DWORD dwValueNameSize,LPBYTE lpValue ,DWORD dwValueSize,DWORD dwType,void* pUserData);

};
	

#endif
