
#pragma once
//=============================================================================
/**
* @file kexectrlloader.h
* @brief 
* @author qiuruifeng <qiuruifeng@kingsoft.com>
* @date 2010-8-18   1:32
*/
//=============================================================================
#include "kexectrl_def.h"

#define		KSM_SERVICE_MULTI_EXE_LOADER			_T("kexectrl.dll")


class KExeCtrlLoader
{
public:
	KExeCtrlLoader()
	{
		m_hModule					= NULL;
		m_pfnAddExecItemOnServer	= NULL;
		m_pfnRemoveExecItemOnServer	= NULL;
		m_pfnStartOnServer			= NULL;
		m_pfnStopOnServer			= NULL;
		m_pfnNotifyExecItemToServer = NULL;
	}
	~KExeCtrlLoader()
	{
		UnInit();
	}

	int Init(const wchar_t* pszModulePath)
	{
		if (NULL == pszModulePath)
			return -1;

		if( !m_hModule )
		{
			m_hModule = LoadLibraryW(pszModulePath);
			if (NULL == m_hModule)
				return -1;

			m_pfnAddExecItemOnServer	= (pfnAddExecItemOnServerType)::GetProcAddress(m_hModule, "AddExecItemOnServer");
			m_pfnRemoveExecItemOnServer	= (pfnRemoveExecItemOnServerType)::GetProcAddress(m_hModule, "RemoveExecItemOnServer");
			m_pfnStartOnServer			= (pfnStartOnServerType)::GetProcAddress(m_hModule, "StartOnServer");
			m_pfnStopOnServer			= (pfnStopOnServerType)::GetProcAddress(m_hModule, "StopOnServer");
			m_pfnNotifyExecItemToServer	= (pfnNotifyExecItemToServerType)::GetProcAddress(m_hModule, "NotifyExecItemToServer");
		}

		return 0;
	}

	int UnInit(void)
	{
		if (m_hModule)
		{
			FreeLibrary(m_hModule);
			m_hModule					= NULL;
			m_pfnAddExecItemOnServer	= NULL;
			m_pfnRemoveExecItemOnServer	= NULL;
			m_pfnStartOnServer			= NULL;
			m_pfnStopOnServer			= NULL;
			m_pfnNotifyExecItemToServer = NULL;
		}
		return 0;
	}

	/**
	* @brief		���ִ�ж���,һ���յ���Ϣ�ͻ��������õĽ���(����˵���)  
	* @param[in]	ExecItem ִ��exe������,��pszCmdLineΪ�ջ�uItemID���Ѿ����õ��ظ�ʱ��ʧ��
	* @return		0 �ɹ�,	����Ϊʧ�ܴ�����
	*/
	int AddExecItemOnServer(const EXEC_ITEM_INFO* pExecItem)
	{
		return m_pfnAddExecItemOnServer ? m_pfnAddExecItemOnServer(pExecItem) : -1;
	}

	/**
	* @brief		ɾ��ִ�ж���
	* @param[in]	uCtrlID  ִ�ж����Ψһ��ʶ
	* @return		0 �ɹ�,	����Ϊʧ�ܴ�����
	*/
	int RemoveExecItemOnServer(unsigned int uItemID)
	{
		return m_pfnRemoveExecItemOnServer ? m_pfnRemoveExecItemOnServer(uItemID) : -1;
	}

	/**
	* @brief		��ʼ����(����˵���) 
	* @return		0 �ɹ�,	����Ϊʧ�ܴ�����
	*/
	int StartOnServer(void)
	{
		return m_pfnStartOnServer ? m_pfnStartOnServer() : -1;
	}

	/**
	* @brief		ֹͣ����(����˵���) 
	* @return		0 �ɹ�,	����Ϊʧ�ܴ�����
	*/
	int StopOnServer(void)
	{
		return m_pfnStopOnServer ? m_pfnStopOnServer() : -1;
	}

	/**
	* @brief		֪ͨ����˶�ɨ���̨����(�ͻ��˵���) 
	* @return		0 �ɹ�,	����Ϊʧ�ܴ�����
	*/
	int NotifyExecItemToServer(unsigned int uItemID)
	{
		return m_pfnNotifyExecItemToServer ? m_pfnNotifyExecItemToServer(uItemID) : -1;
	}

private:
	HMODULE							m_hModule;
	pfnAddExecItemOnServerType		m_pfnAddExecItemOnServer;
	pfnRemoveExecItemOnServerType	m_pfnRemoveExecItemOnServer;
	pfnStartOnServerType			m_pfnStartOnServer;
	pfnStopOnServerType				m_pfnStopOnServer;
	pfnNotifyExecItemToServerType	m_pfnNotifyExecItemToServer;


};