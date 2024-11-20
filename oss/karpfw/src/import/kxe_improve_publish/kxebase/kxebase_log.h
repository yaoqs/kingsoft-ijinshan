//////////////////////////////////////////////////////////////////////
///		@file		kxebase_log.h
///		@author		luopeng
///		@date		2008-8-29 09:07:58
///	
///		@brief		kxebase��log��غ�������
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../kxelog/log_priority.h"

/**
 * @defgroup kxebase_log_group KXEngine Architecture Base SDK Log Interface
 * @{
 */

/// ������־��������
typedef void* kxe_log_t;

/**
* @brief ����ָ��������,�������ָ������־����
* @param[in] pszLogObject Ϊָ������־��������
* @param[out] pLog �ɹ�����������־������
* @remark ʹ�������Ҫʹ��kxe_base_close_debug_log�ر�
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_create_debug_log(
	const char* pszLogObject, 
	kxe_log_t* pLog
	);

/**
* @brief ��ָ������־���������־
* @param[in] log Ϊkxe_base_create_debug_log��������־����
* @param[in] nLevel ������־�ļ���
* @param[in] pszMessage ʵ�ʵ���־����
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_debug_log(
	kxe_log_t log, 
	KXE_LOG_LEVEL nLevel, 
	const char* pszMessage
	);

/**
* @brief �ر�ָ������־����
* @param[in] log Ϊkxe_base_create_debug_log��������־����
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_close_debug_log(
	kxe_log_t log
	);

/**
 * @}
 */
