//////////////////////////////////////////////////////////////////////
///		@file		ikxeserviceprovider.h
///		@author		luopeng
///		@date		2008-9-16 14:07:58
///
///		@brief		Service Provider�Ľӿڶ���
//////////////////////////////////////////////////////////////////////

#pragma once
#include <Unknwn.h>

/**
 * @defgroup kxe_service_provider_interface_group KXEngine Service Provider Interface
 * @{
 */

/**
 * @brief Serivice Provider�����ӿ�
 */
MIDL_INTERFACE("23031722-F263-4074-80FB-5F766AEC49C1")
IKxEServiceProvider : public IUnknown
{
	/**
	 * @brief ��ʼ��Service Provider,�ɷ��������kxeserv����
	 * @return 0 Ϊ�ɹ�, ����Ϊʧ��
	 * @remark �����SDK������Ҫ��ʼ����������ڴ˺����ھ���ɳ�ʼ��������
	 *         ͬʱ�ڴ˺�����������÷ǿ���ڵ�SDK
	 */
	virtual int __stdcall InitializeService() = 0;

	/**
	* @brief ����ʼ��Service Provider,�ɷ��������kxeserv����
	* @return 0 Ϊ�ɹ�, ����Ϊʧ��
	* @remark �ڴ˺����������ٵ��÷ǿ���ڵ�SDK��ͬʱҪ�����Լ��ṩ��SDK��Դ
	*/
	virtual int __stdcall UninitializeService() = 0;
	
	/**
	* @brief ����Service Provider,�ɷ��������kxeserv����
	* @return 0 Ϊ�ɹ�, ����Ϊʧ��
	* @remark �ڴ˺������Ѿ����Ե��÷ǿ���ڵ�SDK,�����ɹ��󣬷������������ⷢ���¼�
	*/
	virtual int __stdcall StartService() = 0;
	
	/**
	* @brief �ر�Service Provider,�ɷ��������kxeserv����
	* @return 0 Ϊ�ɹ�, ����Ϊʧ��
	* @remark �ڴ˺��������ú����еľ��������ٵ��÷ǿ���ڵ�SDK�����⣬
	*         Ҳ�������ڴ˷���ʼ��SDK�������
	*/
	virtual int __stdcall StopService() = 0;	
};

/**
 * @}
 */
