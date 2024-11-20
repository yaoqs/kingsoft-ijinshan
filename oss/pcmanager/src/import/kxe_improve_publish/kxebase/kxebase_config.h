//////////////////////////////////////////////////////////////////////
///		@file		kxebase_config.h
///		@author		luopeng
///		@date		2008-8-29 09:07:58
///	
///		@brief		���ýӿڹغ�������
//////////////////////////////////////////////////////////////////////
#pragma once

/**
 * @defgroup kxebase_config_group KXEngine Architecture Base SDK Config Interface
 * @{
 */

/// Ԥ�������ü�����--����Ϊ��ǰ���������û�
#define KXE_LOCAL_MACHINE_CONFIG (kxe_config_key_t)0x00000001
/// Ԥ�������ü�����--����Ϊ��ǰ�û�
#define KXE_CURRENT_USER_CONFIG  (kxe_config_key_t)0x00000002

/// ���������
typedef void* kxe_config_key_t;

/**
* @brief ����·��,�������һ��ָ�������ü�
* @param[in] key ����Ҫ�򿪵ľ��Լ�ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_base_create_config_key��kxe_base_open_config_key���������ļ�
* @param[in] pwszPath ���·��,���򿪵�·��Ϊkey��path+pwszPath
* @param[out] pKey �ɹ��򿪺󴫳������ü�
* @remark ���ָ���ļ�����,�����,���򴴽���
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_create_config_key(
	kxe_config_key_t key, 
	const wchar_t* pwszPath, 
	kxe_config_key_t* pKey
	);

/**
* @brief ����·��,��һ��ָ�������ü�
* @param[in] key ����Ҫ�򿪵ľ��Լ�ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_base_create_config_key��kxe_base_open_config_key���������ļ�
* @param[in] pwszPath ���·��,���򿪵�·��Ϊkey��path+pwszPath
* @param[out] pKey �ɹ��򿪺󴫳������ü�
* @remark ���ָ���ļ�����,�����,����ʧ��
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_open_config_key(
	kxe_config_key_t key, 
	const wchar_t* pwszPath, 
	kxe_config_key_t* pKey
	);

/**
* @brief �ر�ָ�������ü�
* @param[in] key ͨ��kxe_base_create_config_key��kxe_base_open_config_key��õļ�ֵ
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_close_config_key(
	kxe_config_key_t key
	);

/**
* @brief ͨ��ָ���ļ��������·��,��ȡvaluename��Ӧ��value
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_base_create_config_key��kxe_base_open_config_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in] pwszValueName ��Ҫ��ȡ��ָ��ValueName
* @param[in, out] pwszValue �������ڴ洢value��ָ��
* @param[in] nValueLength �����pwszBuffer��wchar_t�ĸ���
* @param[out] pnReturnValueLength ����ʵ����Ҫ��buffer��wchat_t�ĸ���,����ĩβ���ַ���������
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
int __stdcall kxe_base_get_config(
	kxe_config_key_t key, 
	const wchar_t* pwszPath, 
	const wchar_t* pwszValueName, 
	wchar_t* pwszValue,
	int nValueLength,
	int* pnReturnValueLength
	);

/**
* @brief ͨ��ָ���ļ��������·��,�趨valuename��Ӧ��value
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_base_create_config_key��kxe_base_open_config_key���������ļ�
* @param[in] pwszPath ���·��,����ȡ��·��Ϊkey��path+pwszPath
* @param[in] pwszValueName ָ��ValueName
* @param[in] pwszValue �����buffer����,ֻ��ʹ���ַ����洢
* @param[in] nValueLength �����pszBuffer�ĳ���,��wchar_t�ĸ�����ʾ
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
int __stdcall kxe_base_set_config(
	kxe_config_key_t key,
	const wchar_t* pwszPath, 
	const wchar_t* pwszValueName, 
	const wchar_t* pwszValue,
	int nValueLength
	);

/**
* @brief ɾ��ָ���ļ�ֵ
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*				 ����ΪKXE_LOCAL_MACHINE_CONFIG,KXE_CURRENT_USER_CONFIG��
*                kxe_base_create_config_key��kxe_base_open_config_key���������ļ�
* @param[in] pwszPath ���·��,���·��Ϊkey��path+pwszPath
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
int __stdcall kxe_base_delete_config_key(
	kxe_config_key_t key,
	const wchar_t* pwszPath
	);

/**
* @brief ö��ָ������Ӽ�
* @param[in] key ����Ҫ��ȡ��ָ����ֵ,
*                kxe_base_create_config_key��kxe_base_open_config_key���������ļ�
* @param[in] uIndex ����Ҫ��ȡ�ĵ�uIndex���Ӽ�
* @param[in, out] pwszBuffer �������ڻ�ȡ�Ӽ�����buffer
* @param[in] nBufferLength �����pwszBuffer��С,��wchar_t���
* @param[out] pnReturnBuffer ������Ҫ��Buffer��С,����ĩβ�ַ���������
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
*/
int __stdcall kxe_base_enum_config_key(
	kxe_config_key_t key,
	unsigned int uIndex,
	wchar_t* pwszBuffer,
	int nBufferLength,
	int* pnReturnBuffer
	);


/**
 * @}
 */