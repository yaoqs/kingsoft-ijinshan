#ifndef _WINDOWSHISTORY_H_
#define _WINDOWSHISTORY_H_

#include "CleanProc.h"
#include "i_clean.h"

#include "winosver.h"
#include "fileopt.h"
#include "regopt.h"
#include "apphistory.h"
#include "regclean.h"

/************************************************************************/
//����:window��ʷ��¼����
//
/************************************************************************/

extern CRegClean		g_regClean;
extern ScanFileCallBack g_fnScanFile;
extern ScanRegCallBack  g_fnScanReg;
extern ScanFileCallBack g_fnOutScanFile;
extern ScanRegCallBack  g_fnOutScanReg ;

extern void*			g_pMain;

class  CWindowsHistory
{
public:
	CWindowsHistory();
	~CWindowsHistory();
public:
	void	Start()
	{
		m_bScan=TRUE;
		m_fileOpt.UserBreadFlag(FALSE);
		m_regOpt.UserBreadFlag(FALSE);
		m_appHistory.Start();
	
	};
	void	StopScan()
	{ 
		m_bScan=FALSE;
		m_fileOpt.UserBreadFlag(TRUE);
		m_regOpt.UserBreadFlag(TRUE);
		m_appHistory.StopScan();
	};
	//�Ի�����ʷ��¼
	BOOL	ScanRunDlg();
	BOOL	ScanRunDlg(LPCTSTR lpszRunDlgPath);
	BOOL	RunDlg(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	//������еĳ������ʷ��¼
	BOOL	ScanRunHistory();
	BOOL	ScanRunHistory(LPCTSTR lpszRegPath);
	BOOL	RunHistory(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	//������뱣�����ʷ��¼
	BOOL	ScanOpenOrSave();
	BOOL	ScanOpenOrSave(LPCTSTR lpszRegPath);
	BOOL	OpenOrSave(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	//���ڴ�С��¼
	BOOL	ScanWinSize();
	BOOL	ScanWinSize(LPCTSTR lpszWinSizePath);
	BOOL	WinSize(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	//���ʹ���ĵ���¼ (ע���)
	BOOL	ScanRecentDocReg();
	BOOL	ScanRecentDocReg(LPCTSTR lpszRegPath,int iType);
	BOOL	RecentDocReg(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	//���ʹ���ĵ���¼ (�ļ�)
	BOOL	ScanRecentDocFile();
	BOOL	ScanRecentDocFile(LPCTSTR lpszFileOrFolderPath,int iType);
	BOOL	RecentDocFile(LPCTSTR lpFileOrPath,LARGE_INTEGER filesize);
	//�ļ���չ����ʷ��¼
	BOOL	ScanFileExtsHistory();
	BOOL	ScanFileExtsHistory(LPCTSTR lpcszFileExtsHis);
	BOOL	FileExtsHistory(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	//����򿪳�����ʷ��¼USERASSIST
	BOOL	ScanUserAssist();
	BOOL	ScanUserAssist(LPCTSTR lpcszUserAssistPath);
	BOOL	UserAssist(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	//֪ͨ����ͼ����ʷ��¼
	BOOL	ScanTrayNotify();
	BOOL	ScanTrayNotify(LPCTSTR lpcszTrayNotifyPath);
	BOOL	TrayNotify(HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	/************************************************************************/
	// ������Ϊ��ͬ,ͳһ��CommonRegFun �������д���
	/************************************************************************/
	//����������ӳ����ʷ
	BOOL	ScanNetDerive();
	//���Ҽ������ʷ
	BOOL	ScanFindCmp();
	//�ĵ�������ʷ
	BOOL	ScanFindDoc();
	//��ӡ�˿���ʷ
	BOOL	ScanPrtPort();
	//ͨ�ô�����
	BOOL	CommonRegFun(int iType,HKEY hRootKey,LPCTSTR lpSubKey,LPCTSTR lpValueName,LPCTSTR lpValueData);
	/************************************************************************/
	// ������Ϊ��ͬ,ͳһ��CommonFileFun �������д���
	/************************************************************************/
	BOOL	ScanTempFolder();
	BOOL	ScanLogFolder();
	BOOL	ScanRecycled();
	//ɨ���ݷ�ʽ
	BOOL	ScanInvaidDesktopLink();
	BOOL	ScanInvaidDesktopLink(int iType,LPCTSTR lpFileOrPath,CSimpleArray<CString>& vec_fileExts);
	BOOL	ScanInvaidStartLink();
	BOOL	InvalidLink(int iType,LPCTSTR lpFileOrPath,LARGE_INTEGER filesize);	//
	BOOL	_InvalidLink(LPWSTR lpLinkrPath,LPWSTR lpFilePath,int iLen);									//��֤��ݷ�ʽָ�����Ч��	
	BOOL	CommonFileFun(int iType,LPCTSTR lpFileOrPath,LARGE_INTEGER filesize);
	
	//ע���������λ��
	BOOL	ScanRegeditHistory();
	//�����ע�����
	BOOL	ScanRegeditStream();
	
	//google������
	BOOL	ScanGoogleToolBar();
	BOOL	ScanBaiduToolBar();
	BOOL	ScanBaiduToolBar(LPCTSTR lpszRegPath);
	BOOL    ScanQQToolBar();
	BOOL    ScanWindowLiveToolBar();
	//Windows������ʼ�¼
	BOOL	ScanWindowsPrgHistory();
	//�ڴ�ת��
	BOOL	ScanWindowsMemoryDMP();
	
	BOOL	CleanClipBoard();

	BOOL    ScanWindowsSearch();

	BOOL    ScanNethood();

	BOOL    ScanRecycle();

	//win7��ת�б�
	BOOL    ScanWindows7JumpList();
	BOOL    ScanWinSuol();

private:
	CFileOpt				m_fileOpt;
	CRegOpt					m_regOpt;
	BOOL					m_bScan;
	CAppHistory				m_appHistory;
	TCHAR					m_szLoginName[MAX_PATH];
public:
	static BOOL WINAPI myEnumerateFile(LPCTSTR lpFileOrPath, void* pUserData,LARGE_INTEGER filesize);
	static BOOL WINAPI myEnumerateReg(HKEY rootKey,LPCTSTR lpItemPath,LPCTSTR lpName,DWORD dwValueNameSize,LPBYTE lpValue ,DWORD dwValueSize,DWORD dwType,void* pUserData);

};



#endif //_WINDOWSHISTORY_H_