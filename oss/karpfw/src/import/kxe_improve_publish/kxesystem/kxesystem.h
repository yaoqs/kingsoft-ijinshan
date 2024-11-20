//////////////////////////////////////////////////////////////////////
///		@file		kxesystem.h
///		@author		luopeng
///		@date		2009-3-3 09:07:58
///
///		@brief		���system��һЩAPI�����Է�װ
///                
//////////////////////////////////////////////////////////////////////

#pragma once
#include <Windows.h>
#include <tchar.h>

/**
 * @defgroup kxesystem_compatible_interface KXEngine System Compatible Interface
 * @{
 */

/**
 * @brief ��ѯ��û���Token
 * @param[in] phToken �洢��ѯ���Ļ�û�Token
 * @return 0 �ɹ��� ����Ϊʧ�ܴ�����
 * @remark phTokean��Ҫʹ��CloseHandle�ر�
 */
int __stdcall kxe_base_system_query_active_user_token(
	HANDLE* phToken
	);

/**
 * @brief ��Ӧ�ó��������Windows�ķ���ǽ
 * @param[in] pwszImageFileName ��Ҫ��ӵĳ���ĺ�·��
 * @param[in] pwszFriendlyName ����
 * @return 0 �ɹ��� ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_system_add_app_windows_firewall(
	const wchar_t* pwszImageFileName,
	const wchar_t* pwszFriendlyName
	);

/**
* @brief ��Ӧ�ó����Windows�ķ���ǽ�Ƴ�
* @param[in] pwszImageFileName ��Ҫ�Ƴ��ĳ���ĺ�·��
* @return 0 �ɹ��� ����Ϊʧ�ܴ�����
*/
inline int __stdcall kxe_base_system_remove_app_windows_firewall(
	const wchar_t* pwszImageFileName
	);

/**
 * @}
 */
