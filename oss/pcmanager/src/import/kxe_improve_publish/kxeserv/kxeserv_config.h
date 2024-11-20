//////////////////////////////////////////////////////////////////////
///		@file		kxeserv_config.h
///		@author		luopeng
///		@date		2008-10-06 09:07:58
///
///		@brief		
//////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include "../kxeconfig/kxeconfig.h"
#include "../scom/scom/scombase.h"

/**
 * @defgroup kxeservice_manager_config_data_struct_group KXEngine Service Manager Config Data Struct Define
 * @{
 */

/// �����ṩ���б�����
typedef struct _KXE_SERV_SERVICE_PROVIDER_LIST
{
	std::wstring strName;  ///< key
	std::list<KSCLSID> listProviderList; ///< �����ṩ���б�
} KXE_SERV_SERVICE_PROVIDER_LIST;

#if _MSC_VER > 1200
KXE_CFG_DDX_DEFINE(KSCLSID);
#endif

KXE_CFG_DDX_BEGIN(KXE_SERV_SERVICE_PROVIDER_LIST, strName)
	KXE_CFG_DDX_MEMBER("ProviderList", listProviderList)
KXE_CFG_DDX_END()

/// Plugin����
typedef struct _KXE_SERV_PLUGIN_DLL
{
	std::wstring strPluginName; ///< Key & PluginName
	std::wstring strPluginDllPath; ///< Plugin��·��
} KXE_SERV_PLUGIN_DLL;

KXE_CFG_DDX_BEGIN(KXE_SERV_PLUGIN_DLL, strPluginName)
	KXE_CFG_DDX_MEMBER_DEFAULT("Path", strPluginDllPath, L"")
KXE_CFG_DDX_END()

/// Plugin�б�����
typedef struct _KXE_SERV_PLUGIN_DLL_LIST
{
	std::wstring strName;  ///< Key
	std::list<KXE_SERV_PLUGIN_DLL> listPlugin;  ///< Plugin�б�
} KXE_SERV_PLUGIN_DLL_LIST;

KXE_CFG_DDX_BEGIN(KXE_SERV_PLUGIN_DLL_LIST, strName)
	KXE_CFG_DDX_MEMBER("PluginList", listPlugin)
KXE_CFG_DDX_END()


__declspec(selectany) const extern GUID NULL_GUID = 
	{ 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };


/// ��ǰ��Ʒ������
typedef struct _KXE_PRODUCT_CONFIG
{
	std::wstring strProductID;                     ///< �ò�Ʒ�Ĳ�Ʒ��־
	std::wstring strParentProductID;               ///< �ò�Ʒ�ĸ���Ʒ��־�������ڣ���Ƕ�����Ʒ
	std::wstring strRecommendProductID;            ///< �Ƽ��ò�Ʒ�Ĳ�Ʒ��־
	std::wstring strProductPath;                   ///< ��Ʒ��װ��Ŀ¼
	std::wstring strPluginPath;                    ///< PluginPath
	std::wstring strWebDirectoryPath;              ///< WebPath
#if _MSC_VER > 1200
	__int64 nInstallTime;                          ///< ��װʱ��	
#else
	int nInstallTime;                          ///< ��װʱ��	
#endif
	int nInstallPosition;                          ///< ��װ��˳����ʵ����˵�ڼ�����װ
	std::list<KSCLSID> listChildProduct;           ///< �ò�Ʒ���Ӳ�Ʒ��־
	std::list<KSCLSID> listComponent;              ///< �ò�Ʒ���е����
	std::list<KSCLSID> listServiceProvider;        ///< �ò�Ʒ���еķ����ṩ�����
} KXE_PRODUCT_CONFIG;

KXE_CFG_DDX_BEGIN(KXE_PRODUCT_CONFIG, strProductID)
	KXE_CFG_DDX_MEMBER_DEFAULT("ParentProduct", strParentProductID, L"")
	KXE_CFG_DDX_MEMBER_DEFAULT("RecommendProduct", strRecommendProductID, L"")
	KXE_CFG_DDX_MEMBER_DEFAULT("ProductPath", strProductPath, L"")
	KXE_CFG_DDX_MEMBER_DEFAULT("PluginPath", strPluginPath, L"")
	KXE_CFG_DDX_MEMBER_DEFAULT("WebPath", strWebDirectoryPath, L"")
	KXE_CFG_DDX_MEMBER_DEFAULT("InstallTime", nInstallTime, 0)	
	KXE_CFG_DDX_MEMBER_DEFAULT("InstallPosition", nInstallPosition, 0)
	KXE_CFG_DDX_MEMBER("ChildProductList", listChildProduct)
	KXE_CFG_DDX_MEMBER("ComponentList", listComponent)
	KXE_CFG_DDX_MEMBER("ServiceProviderList", listServiceProvider)
KXE_CFG_DDX_END()

#if _MSC_VER == 1200
inline int kxe_config_write_config(kxe_config_key_t key,
								   const wchar_t* pwszPath,
								   const std::list<KXE_PRODUCT_CONFIG>& listValue)
{
	kxe_config_key_t newKey = NULL;
	
	int nRet = 0;
	if (pwszPath)
	{
		nRet = kxe_base_create_config_key(
			key,
			pwszPath,
			&newKey
			);
		if (nRet != 0)
		{
			return nRet;
		}
		key = newKey;
	}
	
	
	std::list<KXE_PRODUCT_CONFIG>::const_iterator iter = listValue.begin();
	for (; iter != listValue.end(); ++iter)
	{
		nRet = kxe_config_write_config(
			key,
			NULL,
			*iter
			);
		if (nRet != 0)
		{
			break;
		}
	}
	
	if (newKey)
	{
		kxe_config_close_key(newKey);
	}
	
	return nRet;
}

inline int kxe_config_read_config(kxe_config_key_t key,
								  const wchar_t* pwszPath, 
								  std::list<KXE_PRODUCT_CONFIG>& listValue)
{
	kxe_config_key_t newKey = NULL;
	
	int nRet = 0;
	if (pwszPath)
	{
		nRet = kxe_base_create_config_key(
			key,
			pwszPath,
			&newKey
			);
		if (nRet != 0)
		{
			return nRet;
		}
		key = newKey;
	}
	
	
	std::list<std::wstring> listKey;
	nRet = kxe_config_read_key(key, NULL, listKey);
	if (nRet == 0)
	{
		std::list<std::wstring>::iterator iter = listKey.begin();
		
		KXE_PRODUCT_CONFIG value;
		for (; iter != listKey.end(); ++iter)
		{
			KxEConfigSetKeyValue(value, *iter);
			int nRet = kxe_config_read_config(
				key,
				NULL,
				value
				);
			if (nRet != 0)
			{
				break;
			}
			listValue.push_back(value);
		}
	}
	
	if (newKey)
	{
		kxe_config_close_key(newKey);
	}
	
	return nRet;
}

inline int kxe_config_write_config(kxe_config_key_t key,
								   const wchar_t* pwszPath,
								   const std::list<KXE_SERV_PLUGIN_DLL>& listValue)
{
	kxe_config_key_t newKey = NULL;
	
	int nRet = 0;
	if (pwszPath)
	{
		nRet = kxe_base_create_config_key(
			key,
			pwszPath,
			&newKey
			);
		if (nRet != 0)
		{
			return nRet;
		}
		key = newKey;
	}
	
	
	std::list<KXE_SERV_PLUGIN_DLL>::const_iterator iter = listValue.begin();
	for (; iter != listValue.end(); ++iter)
	{
		nRet = kxe_config_write_config(
			key,
			NULL,
			*iter
			);
		if (nRet != 0)
		{
			break;
		}
	}
	
	if (newKey)
	{
		kxe_config_close_key(newKey);
	}
	
	return nRet;
}

inline int kxe_config_read_config(kxe_config_key_t key,
								  const wchar_t* pwszPath, 
								  std::list<KXE_SERV_PLUGIN_DLL>& listValue)
{
	kxe_config_key_t newKey = NULL;
	
	int nRet = 0;
	if (pwszPath)
	{
		nRet = kxe_base_create_config_key(
			key,
			pwszPath,
			&newKey
			);
		if (nRet != 0)
		{
			return nRet;
		}
		key = newKey;
	}
	
	
	std::list<std::wstring> listKey;
	nRet = kxe_config_read_key(key, NULL, listKey);
	if (nRet == 0)
	{
		std::list<std::wstring>::iterator iter = listKey.begin();
		
		KXE_SERV_PLUGIN_DLL value;
		for (; iter != listKey.end(); ++iter)
		{
			KxEConfigSetKeyValue(value, *iter);
			int nRet = kxe_config_read_config(
				key,
				NULL,
				value
				);
			if (nRet != 0)
			{
				break;
			}
			listValue.push_back(value);
		}
	}
	
	if (newKey)
	{
		kxe_config_close_key(newKey);
	}
	
	return nRet;
}
#endif

/// ��Ʒ�б�����
typedef struct _KXE_PRODUCT_CONFIG_LIST
{
	std::wstring strName;  ///< ����
	std::list<KXE_PRODUCT_CONFIG> listProductConfig;  ///< ��Ʒ�б�
} KXE_PRODUCT_CONFIG_LIST;

KXE_CFG_DDX_BEGIN(KXE_PRODUCT_CONFIG_LIST, strName)
	KXE_CFG_DDX_MEMBER("ProductList", listProductConfig)
KXE_CFG_DDX_END()

/**
 * @}
 */