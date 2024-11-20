//////////////////////////////////////////////////////////////////////
///		@file		idl_http.h
///		@author		luopeng
///		@date		2008-9-8 09:07:58
///
///		@brief		�����ڼ�����ǰ�� HTTP-RPC ����
///		
//////////////////////////////////////////////////////////////////////

#pragma once
#include "idl_pipe.h"

class KxEHttpClientCommunication : public KxEPipeClientCommunication
{
public:
	/**
	* @brief		
	* @remark		��������HTTP�汾��KxEIPCClientT��
					�������ָ����URL(�� pwszServerPipeName ������Ϊ NULL )
	* @param[in]	: pwszServiceProviderName Ϊ�����ṩ�ߵ�����
	* @param[in]	: pwszServerPipeName Ϊ�÷����ṩ�����ڽ��̵������ܵ���
	*/
	KxEHttpClientCommunication(
		const wchar_t* pwszServiceProviderName,
		const wchar_t* pwszServerPipeName
		) : KxEPipeClientCommunication(pwszServiceProviderName, NULL)
	{
		pwszServerPipeName;
		//just for remove warning
	}
};

/// ���HTTP��һ��SP���÷�װ�汾
template
<
	typename _Interface
>
class KxEHttpClientT : public KxEIPCClientT<_Interface, KxEHttpClientCommunication>
{
public:
	KxEHttpClientT(const wchar_t* pwszServerName = L"127.0.0.1")
		: KxEIPCClientT<_Interface, KxEHttpClientCommunication>(pwszServerName)
	{
	}
};

/**
 * @brief ���ڽ�Interface���䶨�弰HTTP-RPC��ע��ȥת��,������ǰ�����HTTP-RPC�Ĵ���
 * @remark ����ģ�����Interface����Ϊ������Service Provider�ӿ�,Ҳ����ΪSerivce Provider��TYPELIST�ӿ�,������Ϊ:
 *         TYPELIST_2(IKxEScanService, IKxEFileMonService)�����
 */
template
<
	typename Interface,
	int nPort  ///< ָ���ඨ�Ķ˿ںţ����Ϊ0����ʹ��ƽ̨�ķ�ʽ���ӣ������Լ�����һ��http������
>
class KxEHttpServerT : public KxEIPCServerT<Interface>
{
public:
	
};

/**
 * @}
 */