//////////////////////////////////////////////////////////////////////
///		@file		ikxeauthorizeserviceprovider.h
///		@author		luopeng
///		@date		2008-11-11 09:07:58
///
///		@brief		HTTP��������Ȩ�����ṩ��
//////////////////////////////////////////////////////////////////////

#pragma once
#include "../include/idl.h"

class IKxEAuthorizeServiceProvider
{
public:
	/**
	 * @brief �ͻ��������Ҫ������Ȩ
	 * @param[in] strClientAuthorizeInfo �ͻ��˷�������Ȩ��Ϣ,���ڷ�����ʶ��ͻ���
	 * @param[in] strServerReplyInfo ����˷��ص���Ϣ,���ں������Ӽ��ͻ���ʶ�������
	 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
	 */
	virtual int __stdcall Authorize(
		const std::string& strClientAuthorizeInfo,
		std::string& strServerReplyInfo
		) = 0;
};

KXE_RCF_BEGIN(IKxEAuthorizeServiceProvider, "KxEAuthorizeService")
	KXE_RCF_METHOD(Authorize, std::string, std::string)
KXE_RCF_END()