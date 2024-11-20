//////////////////////////////////////////////////////////////////////
///		@file		kxebase_http.h
///		@author		luopeng
///		@date		2008-8-29 09:07:58
///	
///		@brief		kxebase��http��غ�������
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../kxeipc/ikxerequestdispatch.h"

/**
 * @defgroup kxehttp_sdk_interface_group KXEngine Architecture Base SDK HTTP Interface
 * @{
 */

/**
* @brief ��HTTP������ע��һ��uri�ص�
* @param[in] pszUri ΪҪע��ص���·��
* @param[in] pDispatch Ϊ��HTTP������ܵ�pszUri·������ʱ�Ļص��ӿ�
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_register_uri_dispatch(
	const char* pszUri, 
	IKxERequestDispatch* pDispatch
	);

/**
* @brief ��HTTP������ȡ��һ��uri�ص�
* @param[in] pszUri ΪҪע��ص���·��
* @param[in] pDispatch Ϊ��HTTP������ܵ�pszUri·������ʱ�Ļص��ӿ�
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_unregister_uri_dispatch(
	const char* pszUri, 
	IKxERequestDispatch* pDispatch
	);

/**
 * @brief ����ֹͣHTTP���񣬵��ҽ����ɹ�����kxe_base_start֮�����
 * @remark HTTP��Ϊ��������ݽ��ܶˣ���ֹͣ�������㴦���ڲ����ݶ����±���
 * @return 0 �ɹ��� ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_stop_http();

/**
 * @brief �ָ�HTTP���񣬵��ҽ���kxe_bast_stop_http������֮�����ڻָ�HTTP�Ĵ���
 * @remark HTTP��Ϊ��������ݽ��ܶˣ���ֹͣ�������㴦���ڲ����ݶ����±���
 * @return 0 �ɹ��� ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_resume_http();


/**
 * @brief ����web·���ı���
 * @param[in] pszName ����������alias\\pszName\\other_name�ϣ����ڸ�ֵһ��ʹ��ProductID
 * @param[in] pszDirectory ����ָ���Ŀ¼��ת�����ΪpszDirectory\\other_name
 * @remark ����Ŀ¼�д���kxewebʱ������һ��Ŀ¼��Ϊ.dat��չ����zipѹ����������ת����\n
 * ���Ϊd:\\kingsoft\\kxeweb\\kavweb\\index.htm��������ת��Ϊ\n
 * d:\\kingsoft\\kxeweb\\kavweb.dat�е�index.htm�ļ�
 * @return 0 �ɹ�������Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_register_web_path(const char* pszName,
										 const char* pszDirectory);

/**
 * @brief ȡˮweb·���ı���
 * @param[in] pszName ����������alias\\pszName\\other_name��
 * @return 0 �ɹ�������Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_unregister_web_path(const char* pszName);
/**
 * @}
 */
