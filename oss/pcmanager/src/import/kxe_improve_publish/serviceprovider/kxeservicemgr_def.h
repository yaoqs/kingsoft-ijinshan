//////////////////////////////////////////////////////////////////////
///		@file		kxeservicemgr_def.h
///		@author		luopeng
///		@date		2008-10-06 09:07:58
///
///		@brief		�����������ͨ�����ݽṹ����
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../include/kxe_serialize.h"
#include <vector>

/**
 * @defgroup kxeservice_manager_data_struct_group KXEngine Service Manager Data Struct Define
 * @{
 */

/// ֹͣ����ʱ�Ļظ�
typedef struct _KXE_STOP_SERVICE_RSP
{
	DWORD dwProcessId;  ///< �÷���ǰ�Ľ���ID
} KXE_STOP_SERVICE_RSP;

KXE_JSON_DDX_BEGIN(KXE_STOP_SERVICE_RSP)
	KDX_OBJ_NM("ProcessId", dwProcessId);
KXE_JSON_DDX_END()

/// ��ǰ��Ʒ����Ϣ
typedef struct _KXE_PRODUCT_INFO
{
	std::wstring strProductID;                     ///< �ò�Ʒ�Ĳ�Ʒ��־
	std::wstring strParentProductID;               ///< �ò�Ʒ�ĸ���Ʒ��־�������ڣ���Ƕ�����Ʒ
	std::wstring strRecommendProductID;            ///< �Ƽ��ò�Ʒ�Ĳ�Ʒ��־
#if _MSC_VER > 1200
	__int64 nInstallTime;                          ///< �ò�Ʒ��װʱ�䣬����ʱ��Ϊ0���������ȡ��ֵ
#else
	int nInstallTime;                          ///< �ò�Ʒ��װʱ�䣬����ʱ��Ϊ0���������ȡ��ֵ
#endif
	std::wstring strProductPath;                   ///< ��Ʒ��װ��Ŀ¼
	std::wstring strPluginPath;                    ///< PluginĿ¼
	std::wstring strWebDirectoryPath;              ///< ��ҳ·��
	std::vector<KSCLSID> vecChildProduct;          ///< �ò�Ʒ���Ӳ�Ʒ��־
	std::vector<std::wstring> vecComponent;        ///< �ò�Ʒ���е����·��
	std::vector<std::wstring> vecServiceProvider;  ///< �ò�Ʒ���еķ����ṩ��·�������ļ����������vecComponent��
} KXE_PRODUCT_INFO;

KXE_JSON_DDX_BEGIN(KXE_PRODUCT_INFO)
	KDX_OBJ_NM("ProductID", strProductID);
	KDX_OBJ_NM("ParentProductID", strParentProductID);
	KDX_OBJ_NM("RecommendProductID", strRecommendProductID);
	KDX_OBJ_NM("InstallTime", nInstallTime);
	KDX_OBJ_NM("ProductPath", strProductPath);
	KDX_OBJ_NM("PluginPath", strPluginPath);
	KDX_OBJ_NM("WebPath", strWebDirectoryPath);
	KDX_OBJ_NM("ChildProductID", vecChildProduct);
	KDX_OBJ_NM("ComponentArray", vecComponent);
	KDX_OBJ_NM("ServiceProviderArray", vecServiceProvider);
KXE_JSON_DDX_END()

/**
 * @}
 */