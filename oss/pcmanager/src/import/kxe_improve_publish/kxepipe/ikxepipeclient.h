//////////////////////////////////////////////////////////////////////
///		@file		ikxepipeclient.h
///		@author		luopeng
///		@date		2009-3-17 09:07:58
///
///		@brief		���������װ�Ŀͻ���ʵ��
//////////////////////////////////////////////////////////////////////

#pragma once
#include <Unknwn.h>
#include "../../Publish/kxehttp/ikxerequestdispatch.h"
#include "../kxeipc/kxedispatchmanage.h"
/*
 * @addtogroup kxe_pipe_interface_define
 * @{
 */

/**
 * @brief �����ܵ�����Ŀͻ���
 */
MIDL_INTERFACE("B727E5E4-B953-4de7-96C9-14E289A5F271")
IKxEPipeClient : public IUnknown
{
	/**
	 * @brief ���������ܵ��ͻ���
	 * @param[in] lpszClientPipeName �ͻ��������ܵ����֣��ȴ�����˷�����ʱ����
	 * @param[in] lpszServerPipeName ����������ܵ�����
	 * @param[in] pDispatchManage ���ڻ�ȡ IRequestDispatch ����ָ���Ե����䷽�� Dispatch
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall Start(
		LPCWSTR lpszClientPipeName,
		LPCWSTR lpszServerPipeName,
		KxEDispatchManage *pDispatchManage
		) = 0;

	/**
	 * @brief ֹͣ�����ܵ�
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall Stop() = 0;
};

/**
 * @}
 */