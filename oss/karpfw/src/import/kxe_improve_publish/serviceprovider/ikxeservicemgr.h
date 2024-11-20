//////////////////////////////////////////////////////////////////////
///		@file		ikxeservicemgr.h
///		@author		luopeng
///		@date		2008-10-06 09:07:58
///
///		@brief		����ServiceProvider
//////////////////////////////////////////////////////////////////////

#pragma once
#include "kxeservicemgr_def.h"
#include "../include/idl.h"

/**
 * @defgroup kxeservice_manager_service_provider_interface_group KXEngine Service Manager Service Provider Interface
 * @{
 */

/**
 * @brief �����������SP�ӿ�
 */
class IKxEServiceMgr
{
public:
	/**
	 * @brief ��װ��Ʒ�������
	 * @param[in] productInfo ��װ�Ĳ�Ʒ��Ϣ����
	 * @param[out] strFailedFile �������Ϊ�ļ�����İ�װ���󣬴˱�����Ч
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 * @remark ��A,B����Ʒ��AΪB��Ʒ���Ӳ�Ʒʱ������װ��A����װB��A�ĸ���Ʒ��Ҳ������λ���Ա�־�Ƕ�����װ��
	 */
	virtual int __stdcall InstallProduct(
		const KXE_PRODUCT_INFO& productInfo,
		std::wstring& strFailedFile
		) = 0;

	/**
	 * @brief �ٴΰ�װ��Ʒ������ݣ������Ʒ�Ѿ���װ��Ҳ���ٰ�װһ��
	 * @param[in] productInfo ��װ�Ĳ�Ʒ��Ϣ����
	 * @param[out] strFailedFile �������Ϊ�ļ�����İ�װ���󣬴˱�����Ч
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall ReinstallProduct(
		const KXE_PRODUCT_INFO& productInfo,
		std::wstring& strFailedFile
		) = 0;

	/**
	 * @brief ж�ز�Ʒ�������
	 * @param[in] strProductID ��Ҫж�صĲ�ƷID
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 * @remark ��A,B����Ʒ��AΪB��Ʒ���Ӳ�Ʒʱ��ж��B��Ʒ�󣬽���A��Ʒ�ĸ���Ʒȥ������ɶ�����Ʒ
	 */
	virtual int __stdcall UninstallProduct(
		const std::wstring& strProductID,
		KXE_NULL_PARAEMETER&
		) = 0;

	/**
	 * @brief �жϷ������Ƿ񻹴��ڲ�Ʒ�������������ڣ������ж�ط�����
	 * @param[out] bExistDepend ���ظ����Ƿ���ڲ�Ʒ����������
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall IsExistProductDependFramework(
		const KXE_NULL_PARAEMETER&,
		BOOL& bExistDepend
		) = 0;

	/**
	 * @brief ��ȡָ���Ĳ�Ʒ��Ϣ
	 * @param[in] strProductID ָ���Ĳ�Ʒ��id��־
	 * @param[out] productInfo ����ָ����Ʒ�Ĳ�Ʒ��Ϣ
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall GetProductInfo(
		const std::wstring& strProductID,
		KXE_PRODUCT_INFO& productInfo
		) = 0;

	/**
	 * @brief ��ȡ�������������ܵĲ�Ʒ��Ϣ�б�
	 * @param[out] vecProduct ���ط����ܵ�ǰ���ڵĲ�Ʒ�б�
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall GetProductInfoList(
		const KXE_NULL_PARAEMETER&,
		std::vector<KXE_PRODUCT_INFO>& vecProduct
		) = 0;

	/**
	 * @brief �ж�ָ���Ĳ�Ʒ�Ƿ���ڣ�������һ����Ʒ���������Ʒ��Ҫ��װʱʹ��
	 * @param[in] strProductID ��Ҫ�жϵĲ�ƷKSCLISD��־
	 * @param[out] bExist ���ظ��߸ò�Ʒ�Ƿ����
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall IsProductExist(
		const std::wstring& strProductID,
		BOOL& bExist
		) = 0;

	/**
	 * @brief ʹ�õ�ǰȨ����������
	 * @param[in] strCommandLine ������������
	 * @param[out] dwProcessId ���������Ľ���ID
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall CreateProcessAsClient(
		const std::wstring& strCommandLine, 
		DWORD& dwProcessId
		) = 0;

	/**
	 * @brief ʹ�ù���ԱȨ����������
	 * @param[in] strCommandLine ������������
	 * @param[out] dwProcessId ���������Ľ���ID
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall CreateProcessAsAdmin(
		const std::wstring& strCommandLine, 
		DWORD& dwProcessId
		) = 0;

	/**
	 * @brief ʹ�÷���Ȩ����������
	 * @param[in] strCommandLine ������������
	 * @param[out] dwProcessId ����Ŀ����̵�ID
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall CreateProcessAsServer(
		const std::wstring& strCommandLine, 
		DWORD& dwProcessId
		) = 0;

	/**
	 * @brief ��������
	 * @param[in] strServiceName ������
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall KxEStartService(
		const std::wstring& strServiceName,
		KXE_NULL_PARAEMETER&
		) = 0;

	/**
	 * @brief ��ѯ����ID�Ƿ����
	 * @param[in] dwProcessId ��Ҫ��ѯ�Ľ���ID
	 * @param[out] bExist �����Ƿ����
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall QueryProcessIdExist(
		const DWORD& dwProcessId,
		BOOL& bExist
		) = 0;

	/**
	 * @brief ָ֪ͨ���Ĳ�Ʒ�Ѿ���Ծ
	 * @param[in] uProductId ָ����Ծ�Ĳ�ƷID
	 * @param[out] strProductVersion ��Ծ�Ĳ�Ʒ�汾
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall NotifyProductActivity(
		const unsigned int& uProductId,
		const std::wstring& strProductVersion,
		KXE_NULL_PARAEMETER&
		) = 0;

};

KXE_RCF_BEGIN(IKxEServiceMgr, "KxEServiceMgr")
	KXE_RCF_METHOD(InstallProduct, KXE_PRODUCT_INFO, std::wstring)
	KXE_RCF_METHOD(ReinstallProduct, KXE_PRODUCT_INFO, std::wstring)
	KXE_RCF_METHOD(UninstallProduct, std::wstring, KXE_NULL_PARAEMETER)
	KXE_RCF_METHOD(IsExistProductDependFramework, KXE_NULL_PARAEMETER, BOOL)
	KXE_RCF_METHOD(GetProductInfo, std::wstring, KXE_PRODUCT_INFO)
	KXE_RCF_METHOD(GetProductInfoList, KXE_NULL_PARAEMETER, std::vector<KXE_PRODUCT_INFO>)
	KXE_RCF_METHOD(IsProductExist, std::wstring, BOOL)
	KXE_RCF_METHOD(CreateProcessAsClient, std::wstring, DWORD)
	KXE_RCF_METHOD(CreateProcessAsAdmin, std::wstring, DWORD)
	KXE_RCF_METHOD(CreateProcessAsServer, std::wstring, DWORD)
	KXE_RCF_METHOD(KxEStartService, std::wstring, KXE_NULL_PARAEMETER)
	KXE_RCF_METHOD(QueryProcessIdExist, DWORD, BOOL)
	KXE_RCF_METHOD_2(NotifyProductActivity, unsigned int, std::wstring, KXE_NULL_PARAEMETER)
KXE_RCF_END()

/**
 * @}
 */
