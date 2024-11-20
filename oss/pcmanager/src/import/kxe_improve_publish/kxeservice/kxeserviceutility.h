//////////////////////////////////////////////////////////////////////
///		@file		kxeserviceutility.h
///		@author		luopeng
///		@date		2008-12-18 09:07:58
///
///		@brief		��������غ������
//////////////////////////////////////////////////////////////////////

#pragma once
#include <Windows.h>

/**
 * @defgroup kxe_service_utility KXEngine Service Utility
 * @{
 */

/**
 * @brief ��װ����
 * @param[in] pszPath ����Ķ������ļ�·��
 * @param[in] pszInternalName ��������������ͣ
 * @param[in] pszServiceName ����������
 * @param[in] pszDescriptiveName ���������
 * @param[in] pSvcGroupOrder ���ص�˳��
 * @return 0 �ɹ��� ����Ϊʧ��
 */
int KxEInstallService(
	TCHAR* pszPath, 
	TCHAR* pszInternalName, 
	TCHAR* pszServiceName,
	TCHAR* pszDescriptiveName,
	TCHAR* pSvcGroupOrder
	);

/**
 * @brief ж�ط���
 * @param[in] pszInternalName ��������������ͣ 
 * @return 0 �ɹ��� ����Ϊʧ��
 */
int KxEUninstallService(
	TCHAR *pszInternalName
	);

/**
 * @brief ��������
 * @param[in] pszInternalName ��������������ͣ 
 * @param[in] bWaitRunning �Ƿ�ȴ�������������ɺ󷵻�
 * @return 0 �ɹ��� ����Ϊʧ��
 */
int KxEStartService(
	TCHAR *pszInternalName,
	bool bWaitRunning
	);

/**
 * @brief ֹͣ����
 * @param[in] pszInternalName ��������������ͣ 
 * @param[in] bWaitStopped �Ƿ�ȴ�������ֹͣ��ɺ󷵻�
 * @return 0 �ɹ��� ����Ϊʧ��
 */
int KxEStopService(
	TCHAR *pszInternalName,
	bool bWaitStopped
	);


/**
* @defgroup kxe_service_utility KXEngine Service Utility
* @{
*/

/**
* @brief ��װ����ʽ����
* @param[in] pszPath ����Ķ������ļ�·��
* @param[in] pszInternalName ��������������ͣ
* @param[in] pszServiceName ����������
* @param[in] pszDescriptiveName ���������
* @param[in] pSvcGroupOrder ���ص�˳��
* @return 0 �ɹ��� ����Ϊʧ��
*/
int KxEInstallServiceInteractive(
					  TCHAR* pszPath, 
					  TCHAR* pszInternalName, 
					  TCHAR* pszServiceName,
					  TCHAR* pszDescriptiveName,
					  TCHAR* pSvcGroupOrder
					  );


#include "kxeserviceutility.inl"

/**
 * @}
 */

