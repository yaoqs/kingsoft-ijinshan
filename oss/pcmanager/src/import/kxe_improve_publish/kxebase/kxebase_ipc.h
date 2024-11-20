//////////////////////////////////////////////////////////////////////
///		@file		kxebase_ipc.h
///		@author		luopeng
///		@date		2008-8-29 09:07:58
///	
///		@brief		kxebase��ipc��غ�������
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../kxeipc/ikxerequestdispatch.h"

/**
 * @defgroup kxeipc_sdk_interface_group KXEngine Architecture Base SDK IPC Interface
 * @{
 */

/**
* @brief ��IPC����ע��һ��SP��ص���ָ��
* @param[in] pwszSPName ΪҪע��ص���·��
* @param[in] pDispatch Ϊ��IPC������ܵ�pszSPName·������ʱ�Ļص��ӿ�
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_register_sp_dispatch(
	const wchar_t* pwszSPName,
	IKxERequestDispatch* pDispatch
	);

/**
* @brief ��HTTP������ȡ��һ��uri�ص�
* @param[in] pwszSPName ΪҪע��ص���·��
* @param[in] pDispatch Ϊ��IPC������ܵ�pszSPName·������ʱ�Ļص��ӿ�
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_unregister_sp_dispatch(
	const wchar_t* pwszSPName, 
	IKxERequestDispatch* pDispatch
	);

/**
 * @brief ����ֹͣIPC���񣬵��ҽ����ɹ�����kxe_base_start֮�����
 * @remark HTTP��Ϊ��������ݽ��ܶˣ���ֹͣ�������㴦���ڲ����ݶ����±���
 * @return 0 �ɹ��� ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_stop_ipc();

/**
 * @brief �ָ�IPC���񣬵��ҽ���kxe_bast_stop_http������֮�����ڻָ�IPC�Ĵ���
 * @remark IPC��Ϊ��������ݽ��ܶˣ���ֹͣ�������㴦���ڲ����ݶ����±���
 * @return 0 �ɹ��� ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_resume_ipc();

/**
 * @}
 */
