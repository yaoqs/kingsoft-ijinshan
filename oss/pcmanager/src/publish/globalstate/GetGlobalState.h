#pragma once

class CGetGlobalState
{
public:
	CGetGlobalState(void);
	~CGetGlobalState(void);

	VOID		InitModule(HMODULE hMod);
public:
	LPCTSTR		GetModulePath();
	LPCTSTR		GetModuleDir();
	LPCTSTR		GetTempDir();
	LPCTSTR		GetWindowsDir();
	LPCTSTR		GetSystem32Dir();
	LPCTSTR		GetProgramDir();
	LPCTSTR		GetCommonAppDataDir();
	LPCTSTR		GetAppDataDir();
	LPCTSTR		GetUserStartupDir();
	LPCTSTR		GetAllStartupDir();

	LPCTSTR		GetUserinitPath();
	LPCTSTR		GetIExplorerPath();
	LPCTSTR		GetExplorerPath();
	LPCTSTR		GetSysExplorerPath();	// system32Ŀ¼��explorer.exe��·��
	LPCTSTR		GetRundll32Path();
	LPCTSTR		GetRegSrvPath();

	LPCTSTR		GetWinlogonPath();
	
	LPCTSTR		GetUserStartMenuProgDir();		// ��ʼ�˵�������Ŀ¼
	LPCTSTR		GetCommonStartMenuProgDir();	

	LPCTSTR		GetUserDesktopDir();	// ����
	LPCTSTR		GetCommonDesktopDir();

	LPCTSTR		GetQuickLanchDir();		// ��������

	LPCTSTR		GetUserStartMenuRootDir();		// �����˵���Ŀ¼
	LPCTSTR		GetCommonStartMenuRootDir();

	LPCTSTR		GetUserStartRunDir();
	LPCTSTR		GetCommonStartRunDir();

	LPCTSTR		GetUserFavoriteDir();
	LPCTSTR		GetCommonFavoriteDir();

	BOOL		IsWindowGENT(){ return TRUE; }		// ��win95��98ϵͳ��NT4���ϵ�ϵͳ
	BOOL		IsWindowNT4(){ return m_dwMajorVer==4; }
	BOOL		IsWindowVista(){return m_dwMajorVer==6;}
	BOOL		IsWindowXp(){return (m_dwMajorVer==5 && m_dwMinVer ==1);}
	BOOL		IsWindow2K(){return (m_dwMajorVer==5 && m_dwMinVer ==0);}
	BOOL		IsWindow5x(){return m_dwMajorVer==5;}	// �ǲ���5.Xϵ�е�
	BOOL		IsWindowGExp(){return (m_dwMajorVer>5)||(m_dwMajorVer==5&&m_dwMinVer>0);}	// �ǲ��Ǵ���XP
	BOOL		IsWindowGE2k(){return m_dwMajorVer>=5;}	// �ǲ��Ǵ���2K
	BOOL		IsWindow7x(){return m_dwMajorVer==7;}	
	BOOL		IsWindow2K3(){return (m_dwMajorVer==5 && m_dwMinVer==2);}
	BOOL		IsWOW64(){return m_bIsWOW64;}

	BOOL		FixPathLastSpec(LPTSTR lpPath);	// �����һλ '\' ȥ��

	VOID		GetLongPath(LPCTSTR lpFile, CString& strLongFile);

protected:
	BOOL	GetIsWOW64();
protected:
	HMODULE		m_hMod;
	DWORD		m_dwMajorVer;
	DWORD		m_dwMinVer;
	BOOL		m_bIsWOW64;
};

CGetGlobalState* GetGlobalState();
