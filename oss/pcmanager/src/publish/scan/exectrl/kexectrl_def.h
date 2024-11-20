//=============================================================================
/**
* @file kmultiqs_api.h
* @brief 
* @author qiuruifeng <qiuruifeng@kingsoft.com>
* @date 2010-8-14   16:30
*/
//=============================================================================
#pragma once 

extern "C"
{
	typedef struct _EXEC_ITEM_INFO
	{
		unsigned int	uDataSize;	///< sizeof(_EXEC_ITEM_INFO)
		const wchar_t*	pszCmdLine; ///< ִ�е������в���
		unsigned int	uItemID;	///< ִ�ж����Ψһ��ʶ

	}EXEC_ITEM_INFO;

	/**
	* @brief		���ִ�ж���,һ���յ���Ϣ�ͻ��������õĽ���(����˵���)  
	* @param[in]	ExecItem ִ��exe������,��pszCmdLineΪ�ջ�uItemID���Ѿ����õ��ظ�ʱ��ʧ��
	* @return		0 �ɹ�,	����Ϊʧ�ܴ�����
	*/
	typedef int (__stdcall *pfnAddExecItemOnServerType)(const EXEC_ITEM_INFO* pExecItem);

	/**
	* @brief		ɾ��ִ�ж���
	* @param[in]	uCtrlID  ִ�ж����Ψһ��ʶ
	* @return		0 �ɹ�,	����Ϊʧ�ܴ�����
	*/
	typedef int (__stdcall *pfnRemoveExecItemOnServerType)(unsigned int uItemID);

	/**
	* @brief		��ʼ����(����˵���) 
	* @return		0 �ɹ�,	����Ϊʧ�ܴ�����
	*/
	typedef int (__stdcall *pfnStartOnServerType)(void);

	/**
	* @brief		ֹͣ����(����˵���) 
	* @return		0 �ɹ�,	����Ϊʧ�ܴ�����
	*/
	typedef int (__stdcall *pfnStopOnServerType)(void);
	
	/**
	* @brief		֪ͨ����˶�ɨ���̨����(�ͻ��˵���) 
	* @return		0 �ɹ�,	����Ϊʧ�ܴ�����
	*/
	typedef int (__stdcall *pfnNotifyExecItemToServerType)(unsigned int uItemID);

};