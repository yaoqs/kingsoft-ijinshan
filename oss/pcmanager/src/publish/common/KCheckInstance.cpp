// kisupinst.cpp

#include "StdAfx.h"
#include "KCheckInstance.h"
#define defKAV_UPLIVE_MUTEX_NAME		_T("{AB8E897A-4E71-4631-825D-9DD1E233C811}_CHECK")
#define defUPLIVE_FILE_MAPPING_NAME		_T("{AE7E329F-D22E-4baf-9563-C0AE499C2BA8}_MAP")

#pragma pack(push, 1)
struct FILE_MAPPING
{
	// ������Ĵ��ھ����
	HWND hWnd;
	// �Ƿ��Ǻ�̨ģʽ��
	BOOL bCurInAutoRunMode;
	// �������ڶ���ʵ��֪ͨ��һ��ʵ����֪ͨ�롣
	int nNotifyCode;
	// ������Ĵ��ھ���ǲ����á�
	BOOL bInvalidInstance;
	// ��������
	HANDLE hInstance;
	// 
	DWORD dwReserve[10];
};
#pragma pack(pop)

typedef FILE_MAPPING * PFILE_MAPPING;

KCheckInstance::KCheckInstance()
	: m_bFirstInstance(TRUE),
	  m_hInstanceMutex(NULL),
	  m_hFileMapping(NULL)
{

}

KCheckInstance::~KCheckInstance()
{

}

KCheckInstance* KCheckInstance::Instance()
{
	static KCheckInstance _Inst;

	return (&_Inst);
}

void KCheckInstance::Release()
{

}

//////////////////////////////////////////////////////////////////////////
//
/*
@ FuncName	: CheckInstance
@ Brief		: ���ʵ����
*/
BOOL KCheckInstance::CheckInstance(OUT BOOL& bIsFirstInstance, IN LPCWSTR lpNamStr, IN LPCWSTR lpFileMapStr)
{
	bIsFirstInstance = TRUE;

	if (lpNamStr != NULL)
		m_hInstanceMutex = ::CreateMutex(NULL, TRUE, lpNamStr);
	else
		m_hInstanceMutex = ::CreateMutex(NULL, TRUE, defKAV_UPLIVE_MUTEX_NAME);

	
	if (m_hInstanceMutex)
	{	
		DWORD dwError = ::WaitForSingleObject(m_hInstanceMutex, 0);
		// ���ȴ���ʱ�ͱ�ʾ�ڶ���ʵ����bug 38535
		if (WAIT_OBJECT_0 != dwError)
		{
			bIsFirstInstance = FALSE;
			::ReleaseMutex(m_hInstanceMutex);
			::CloseHandle(m_hInstanceMutex);
			m_hInstanceMutex = NULL;
		}
	}
	else
		return FALSE;

	PSECURITY_ATTRIBUTES pSA  = NULL;

	// �������ӽ��̼̳иù����ڴ棡��by ZC. 2009-8-26.
	if (pSA)
		pSA->bInheritHandle = FALSE;

	if (lpFileMapStr == NULL)
		m_hFileMapping = ::CreateFileMapping((HANDLE)0xFFFFFFFF, 
											pSA, 
											PAGE_READWRITE, 
											0, 
											sizeof(FILE_MAPPING), 
											defUPLIVE_FILE_MAPPING_NAME);
	else
		m_hFileMapping = ::CreateFileMapping((HANDLE)0xFFFFFFFF, 
											pSA, 
											PAGE_READWRITE, 
											0, 
											sizeof(FILE_MAPPING), 
											lpFileMapStr);

	if (ERROR_ALREADY_EXISTS == ::GetLastError())
	{
		bIsFirstInstance = FALSE;
	}

	if (m_hFileMapping == NULL)
		return FALSE;

	return TRUE;
}

void KCheckInstance::ProcessCmdLine(IN LPCTSTR pszCmdline, 
							   OUT BOOL& bIsExitApp, 
							   OUT BOOL& bAutoRun)
{
	bIsExitApp	= FALSE;
	bAutoRun	= FALSE;

/*	if (pszCmdline != NULL)
	{
		if (AnalyzeCmd.InitCmd(pszCmdline))
		{
			// �Ƿ��Զ��˳���������
			AnalyzeCmd.AnalyzeCmd(_T("Quit"), bIsExitApp);
			if (!bIsExitApp)
			{
				// �Ƿ��Զ��˳���������
				AnalyzeCmd.AnalyzeCmd(_T("Exit"), bIsExitApp);				
			}

			AnalyzeCmd.AnalyzeCmd(_T("AutoRun"), bAutoRun);
		} // if 
	}
*/
}

/*
@ FuncName	: ProcessInstance
@ Brief		: �����ʵ����
*/
BOOL KCheckInstance::ProcessInstance(IN BOOL bFirstInstance,
								IN BOOL bIsExitApp,
								IN BOOL bAutoRun,
								IN LPCWSTR lpCmdParam)
{

	if (!bFirstInstance)
	{
		m_bFirstInstance = FALSE;

	//	::MessageBox(NULL, NULL, NULL, NULL);

		LPVOID lpMem = ::MapViewOfFile(m_hFileMapping, 
			FILE_MAP_ALL_ACCESS,
			0, 0, 0);
		if (lpMem != NULL)
		{
			FILE_MAPPING FileMapping = {0};
			memcpy(&FileMapping, lpMem, sizeof(FILE_MAPPING));

			if (bIsExitApp)
			{
			//	::PostMessage(FileMapping.hWnd, WM_UPLIVE_UI_DO_SOMETHING, 1, TRUE);
				//goto Exit0;

				//::PostMessage(FileMapping.hWnd, WM_UPLIVE_UI_DO_SOMETHING, enumDoSomeThing_ExitUpliveApp, TRUE);
			}
			else
			{
				if (FileMapping.bInvalidInstance)
				{
					//�����ھ������Ϊ������ʱ���˳�Uplive��
				} // if FileMapping.bInvalidInstance
				else
				{
					if (TRUE == FileMapping.bCurInAutoRunMode)
					{
						// ���ڶ���ʵ������ʱ������ʾ���ڡ�
						// ��������������̨���е�ʵ�����Ų���ʾ���ڡ�
						if (bAutoRun)
						{
							// Don't show anything on AutoRun mode!
						}
						else
						{
							// �ں�̨����ģʽshow�����档
							if (wcscmp(lpCmdParam, L"") == 0 || lpCmdParam == NULL)
								::PostMessage(FileMapping.hWnd, WM_UPLIVE_SHOW, NULL, NULL);
							else if (wcscmp(lpCmdParam, L"run1") == 0)
								::PostMessage(FileMapping.hWnd, WM_SHOW_RUN1, NULL, NULL);
							else if (wcscmp(lpCmdParam, L"run2") == 0)
								::PostMessage(FileMapping.hWnd, WM_SHOW_RUN2, NULL, NULL);
							else if (_wcsicmp(lpCmdParam, L"-cpu") == 0)
								::PostMessage(FileMapping.hWnd, WM_UPLIVE_SHOW, 1001, NULL);
							else if (_wcsicmp(lpCmdParam, L"-mem") == 0)
								::PostMessage(FileMapping.hWnd, WM_UPLIVE_SHOW, 1002, NULL);
							else if (_wcsicmp(lpCmdParam, L"-ONEKEYSPEEDUP") == 0)
								::PostMessage(FileMapping.hWnd, WM_UPLIVE_SHOW, 1003, NULL);
						}
					}
					else
					{
						if (wcscmp(lpCmdParam, L"") == 0 || lpCmdParam == NULL)
						{
							if (::IsIconic(FileMapping.hWnd))
								::ShowWindow(FileMapping.hWnd, SW_RESTORE);
							::PostMessage(FileMapping.hWnd, WM_UPLIVE_SHOW, NULL, NULL);
						}
						else if (wcscmp(lpCmdParam, L"run1") == 0)
							::PostMessage(FileMapping.hWnd, WM_SHOW_RUN1, NULL, NULL);
						else if (wcscmp(lpCmdParam, L"run2") == 0)
							::PostMessage(FileMapping.hWnd, WM_SHOW_RUN2, NULL, NULL);
						else if (_wcsicmp(lpCmdParam, L"-cpu") == 0)
							::PostMessage(FileMapping.hWnd, WM_UPLIVE_SHOW, 1001, NULL);
						else if (_wcsicmp(lpCmdParam, L"-mem") == 0)
							::PostMessage(FileMapping.hWnd, WM_UPLIVE_SHOW, 1002, NULL);
						else if (_wcsicmp(lpCmdParam, L"-ONEKEYSPEEDUP") == 0)
							::PostMessage(FileMapping.hWnd, WM_UPLIVE_SHOW, 1003, NULL);
					}
				} // if !FileMapping.bInvalidInstance
			}
			::UnmapViewOfFile(lpMem);
		} // lpMem
	} // ERROR_ALREADY_EXISTS
	else
	{
		if (bIsExitApp)
			m_bFirstInstance = FALSE;
		else
			m_bFirstInstance = TRUE;
	}
	
	// �����Ƿ��ǡ���һ��ʵ����.
	return m_bFirstInstance;
}

BOOL KCheckInstance::CheckFirstInstance(LPCTSTR pszCmdline, IN LPWSTR lpCheckStrName, IN LPCWSTR lpFileMapStr)
{
	int nRetCode = false;
	
	BOOL bFirstInstance = TRUE;

	if (CheckInstance(bFirstInstance, lpCheckStrName, lpFileMapStr))
	{
		// Ԥ�������������С�
		BOOL bIsExitApp = FALSE, bAutoRun = FALSE;
		
		ProcessCmdLine(pszCmdline, bIsExitApp, bAutoRun);

		ProcessInstance(bFirstInstance, bIsExitApp, bAutoRun, pszCmdline);
	}

	// �ǵ�һ��ʵ���͹ر�m_hFileMapping��
	if (FALSE == m_bFirstInstance
		&& m_hFileMapping
		)
	{
		::CloseHandle(m_hFileMapping);
		m_hFileMapping = NULL;
	}

	return m_bFirstInstance;
}

BOOL KCheckInstance::CfgFirstInstance(IN HINSTANCE hInst, 
								 IN HWND hWnd, 
								 IN BOOL bInAutoRun, 
								 IN BOOL bInvalidInst/* = FALSE*/)
{
	int nResult = false;
	
	if (NULL != m_hFileMapping
		&& INVALID_HANDLE_VALUE != m_hFileMapping
		)
	{
		void * lpMem = NULL;

		lpMem = ::MapViewOfFile(m_hFileMapping, FILE_MAP_WRITE, 0, 0, 0);
		if (lpMem)
		{
			FILE_MAPPING _FileMapping = { 0 };

			_FileMapping.hInstance			= hInst;
			_FileMapping.hWnd				= hWnd;
			_FileMapping.bCurInAutoRunMode	= bInAutoRun;
			_FileMapping.bInvalidInstance	= bInvalidInst;

			memcpy(lpMem, (void *)&_FileMapping, sizeof(FILE_MAPPING));
			::UnmapViewOfFile(lpMem);

			nResult = true;
		}
	}
	
	return nResult;
}

BOOL KCheckInstance::IsFirstInstance()
{
	return this->m_bFirstInstance;
}

void KCheckInstance::ClearFirstInstance()
{
	// ���Źرչ����ڴ��뻥������
	if (m_hFileMapping)
	{
		::CloseHandle(m_hFileMapping);
		m_hFileMapping = NULL;
	}

	if (m_hInstanceMutex)
	{
		::ReleaseMutex(m_hInstanceMutex);
		::CloseHandle(m_hInstanceMutex);
		m_hInstanceMutex = NULL;
	}

	if (m_hInstanceMutexSelf)
	{
		::ReleaseMutex(m_hInstanceMutexSelf);
		::CloseHandle(m_hInstanceMutexSelf);
		m_hInstanceMutexSelf = NULL;
	}
}

BOOL KCheckInstance::CheckInstanceSelf( IN LPCTSTR lpInstanceName )
{
	m_hInstanceMutexSelf = ::CreateMutex(NULL, TRUE, lpInstanceName);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;
	
	return TRUE;
}
