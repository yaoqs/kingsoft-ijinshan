//////////////////////////////////////////////////////////////////////
///		@file		kxebase_base.h
///		@author		luopeng
///		@date		2008-8-29 09:07:58
///	
///		@brief		kxebase������������
//////////////////////////////////////////////////////////////////////
#pragma once
#include <WinSock2.h>
#include <windows.h>

/**
 * @defgroup kxebase_initialize_group KXEngine Architecture Base SDK Initialize Interface
 * @{
 */

/**
 * @brief ��ʼ��������,�ú�������Ҳֻ�ܱ�����һ��
 * @remark 
 * @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
 */
int __stdcall kxe_base_init();

/**
 * @brief ��ʼ��������,�ú�������Ҳֻ�ܱ�����һ�Σ���kxe_base_init��������
 * @remark �ú�������ѭ����ʹ�õ�ԭ�������Ӧ���������Ҫ�����������������
 * @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
 */
int __stdcall kxe_base_init_client();

/**
 * @brief ����������,�ú�������Ҳֻ�ܱ�����һ��,���ڲ��ĺ������������������
 * @remark 
 * @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
 */
int __stdcall kxe_base_start();

/**
 * @brief ֹͣ������,�ú�������Ҳֻ�ܱ�����һ��,���ڲ��ĺ��������������ֹͣ
 * @remark 
 * @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
 */
int __stdcall kxe_base_stop();

/**
 * @brief ����ʼ��������,�ú�������Ҳֻ�ܱ�����һ��
 * @remark 
 * @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
 */
int __stdcall kxe_base_fini();

/**
 * @brief ��ȡ��������ص���չSDK
 * @remark 
 * @param[in] pszSystem Ϊ��Ҫ��ȡSDK����ϵͳ������
 * @param[in] pszMethod Ϊ��Ҫ��ȡSDK�ĺ�����
 * @param[out] ppMethodFunction Ϊ�ɹ���ȡ�ĺ���ָ��,�����͵����߱���֪��
 * @return 0 �ɹ�, ����ֵΪʧ�ܵĴ�����
 */
int __stdcall kxe_base_get_system_method(
	const char* pszSystem,
	const char* pszMethod,
	void** ppMethodFunction
	);

/**
 * @brief �������ע���쳣�����ӣ������ڱ���֮ǰ���д�����ϵͳ��ͬ���ǣ�������Է���ֵ
 * @param[in] lpExceptionFilter �����쳣����ĺ���
 * @return 0 �ɹ��� ����Ϊʧ�ܴ�����
 * @remark ��ע��ʧ��ʱ����Ҫ�Լ�����SetUnhandledExceptionFilter���д���
 */
int __stdcall kxe_base_register_unhandled_exception_filter(
	LPTOP_LEVEL_EXCEPTION_FILTER lpExceptionFilter
	);

/**
 * @brief �������ȡˮ�쳣������
 * @param[in] lpExceptionFilter �����쳣����ĺ���
 * @return 0 �ɹ��� ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_unregister_unhandled_exception_filter(
	LPTOP_LEVEL_EXCEPTION_FILTER lpExceptionFilter
	);

/**
 * @brief �ṩ����crash��post��·�����Ƿ���ʾGUI������
 * @param[in] pszPostAddr HTTP����ĵ�ַ
 * @param[in] bShowGUI �Ƿ���ʾ�������棬���û������ϱ���false����ʾֱ���ϱ�
 */
int __stdcall kxe_base_set_crash_post_option(
	const char* pszPostAddr,
	bool bShowGUI
	);

/**
 * @brief ֪ͨ��Ծ��
 * @param[in] uProductId ����Ծ�Ĳ�ƷID
 * @param[in] pwszProductVersion ����Ĳ�Ʒ�汾
 */
int __stdcall kxe_base_notify_activity(
    unsigned int uProductId,
	const wchar_t* pwszProductVersion
	);

/**
 * @brief ��ѹ�ļ�
 * @param[in] pwszSourceFileName ��Ҫ���н�ѹ���ļ�
 * @param[in] pwszTargetDir ��Ҫ��ѹ����Ŀ��Ŀ¼
 */
int __stdcall kxe_base_uncompress_file(
	const wchar_t* pwszSourceFileName,
	const wchar_t* pwszTargetDir
	);

/**
 * @breif ����ָ����Plugin SDK
 * @param[in] pwszPluginDllPath ��Ҫ���ص�plugin sdk
 */
int __stdcall kxe_base_load_plugin(
	const wchar_t* pwszPluginDllPath
	);

/**
 * @breif ����ָ����Plugin SDK
 * @param[in] pwszPluginDllPath ��Ҫ���ص�plugin sdk
 */
int __stdcall kxe_base_unload_plugin(
	const wchar_t* pwszPluginDllPath
	);
/**
 * @}
 */
