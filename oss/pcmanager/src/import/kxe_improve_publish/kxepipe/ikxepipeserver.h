//////////////////////////////////////////////////////////////////////
///		@file		ikxepipeserver.h
///		@author		luopeng
///		@date		2009-3-17 09:07:58
///
///		@brief		���������װ�ķ�����ʵ��
///		
//////////////////////////////////////////////////////////////////////

#pragma once
#include <Unknwn.h>
#include "../kxeipc/ikxedispatchmanage.h"

/**
 * @defgroup kxe_pipe_interface_define KXEngine Pipe Define in Proudct Manage 
 * @{
 */

/**
 * @brief ��������ķ��������
 */
MIDL_INTERFACE("EC6F568C-0DA2-4539-B474-52A9A20553CE")
IKxEPipeServer : public IUnknown
{
	/**
	* @brief ������lpszPipeName�����Ĺܵ�������¼pCallback�ص����д���
	* @param[in] lpszPipeName ����ʱʹ�õ������ܵ�
	* @param[in] pDispatchManage ���ڹ��� SP �����Ϣ����ָ��
	*/
	virtual int __stdcall Start(
		LPCWSTR lpszPipeName,
		IKxEDispatchManage* pDispatchManage
		) = 0;

	/**
	 * @brief ֹͣ�÷���
	 */
	virtual int __stdcall Stop() = 0;
};

/**
 * @}
 */
