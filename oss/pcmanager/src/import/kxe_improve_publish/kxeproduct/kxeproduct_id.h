//////////////////////////////////////////////////////////////////////
///		@file		kxeproduct_id.h
///		@author		luopeng
///		@date		2009-2-17 14:07:58
///
///		@brief		产品相关ID的定义
//////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @defgroup kxe_product_id_group KXEngine Product ID
 * @{
 */

/**
 * 产品ID直接为16位，分别为高8位，与低8位
 * 0                  7                  15
 * ---------------------------------------
 * |   Product_Type   |  Product_Version |
 * ---------------------------------------
 */

/// 平台产品
#define KXE_PLATFORM_PRODUCT_TYPE          0x00000000
#define KXE_PLATFORM_PRODUCT_TYPE_A        "0x00000000"
#define KXE_PLATFORM_PRODUCT_TYPE_W        L"0x00000000"
#define KXE_PLATFORM_PRODUCT_TYPE_T        _T("0x00000000")

/// 毒霸套装
#define KXE_DUBA_SUIT_PRODUCT_TYPE         0x00010000
#define KXE_DUBA_SUIT_PRODUCT_TYPE_A       "0x00010000"
#define KXE_DUBA_SUIT_PRODUCT_TYPE_W       L"0x00010000"
#define KXE_DUBA_SUIT_PRODUCT_TYPE_T       _T("0x00010000")

/// 清理专家
#define KXE_ANTISPY_PRODUCT_TYPE           0x00020000
#define KXE_ANTISPY_PRODUCT_TYPE_A         "0x00020000"
#define KXE_ANTISPY_PRODUCT_TYPE_W         L"0x00020000"
#define KXE_ANTISPY_PRODUCT_TYPE_T         _T("0x00020000")

/// 在线杀毒
#define KXE_ONLINE_SCAN_PRODUCT_TYPE       0x00030000
#define KXE_ONLINE_SCAN_PRODUCT_TYPE_A     "0x00030000"
#define KXE_ONLINE_SCAN_PRODUCT_TYPE_W     L"0x00030000"
#define KXE_ONLINE_SCAN_PRODUCT_TYPE_T     _T("0x00030000")

/// 手机安全
#define KXE_MOBILE_PHONE_SECURITY_PRODUCT_TYPE     0x00040000
#define KXE_MOBILE_PHONE_SECURITY_PRODUCT_TYPE_A   "0x00040000"
#define KXE_MOBILE_PHONE_SECURITY_PRODUCT_TYPE_W   L"0x00040000"
#define KXE_MOBILE_PHONE_SECURITY_PRODUCT_TYPE_T   _T("0x00040000")

/// 网盾
#define KXE_WEB_SHIELD_PRODUCT_TYPE        0x00050000
#define KXE_WEB_SHIELD_PRODUCT_TYPE_A      "0x00050000"
#define KXE_WEB_SHIELD_PRODUCT_TYPE_W      L"0x00050000"
#define KXE_WEB_SHIELD_PRODUCT_TYPE_T      _T("0x00050000")

/// 浏览器安全助手
#define KXE_BROWSER_ASSIST_PRODUCT_TYPE      0x00060000
#define KXE_BROWSER_ASSIST_PRODUCT_TYPE_A    "0x00060000"
#define KXE_BROWSER_ASSIST_PRODUCT_TYPE_W    L"0x00060000"
#define KXE_BROWSER_ASSIST_PRODUCT_TYPE_T    _T("0x00060000")

/// 金山布卡
#define KXE_BUKA_PRODUCT_TYPE              0x00070000
#define KXE_BUKA_PRODUCT_TYPE_A            "0x00070000"
#define KXE_BUKA_PRODUCT_TYPE_W            L"0x00070000"
#define KXE_BUKA_PRODUCT_TYPE_T            _T("0x00070000")

/// 软件分发平台
#define KXE_SOFTWARE_DISTRIBUTE_PRODUCT_TYPE   0x00080000
#define KXE_SOFTWARE_DISTRIBUTE_PRODUCT_TYPE_A "0x00080000"
#define KXE_SOFTWARE_DISTRIBUTE_PRODUCT_TYPE_W L"0x00080000"
#define KXE_SOFTWARE_DISTRIBUTE_PRODUCT_TYPE_T _T("0x00080000")

/// 金山急救箱
#define KXE_SOFTWARE_JIJIU_PRODUCT_TYPE   0x00090000
#define KXE_SOFTWARE_JIJIU_PRODUCT_TYPE_A "0x00090000"
#define KXE_SOFTWARE_JIJIU_PRODUCT_TYPE_W L"0x00090000"
#define KXE_SOFTWARE_JIJIU_PRODUCT_TYPE_T _T("0x00090000")


/// 新网盾
#define KXE_NEW_WEB_SHIELD_PRODUCT_TYPE      0x00110000
#define KXE_NEW_WEB_SHIELD_PRODUCT_TYPE_A    "0x00110000"
#define KXE_NEW_WEB_SHIELD_PRODUCT_TYPE_W    L"0x00110000"
#define KXE_NEW_WEB_SHIELD_PRODUCT_TYPE_T    _T("0x00110000")

/// 金山网盾3.5
#define KXE_SOFTWARE_JIJIU_WEB_SHIELD_PRODUCT_TYPE  	KXE_NEW_WEB_SHIELD_PRODUCT_TYPE
#define KXE_SOFTWARE_JIJIU_WEB_SHIELD_PRODUCT_TYPE_A 	KXE_NEW_WEB_SHIELD_PRODUCT_TYPE_A
#define KXE_SOFTWARE_JIJIU_WEB_SHIELD_PRODUCT_TYPE_W  	KXE_NEW_WEB_SHIELD_PRODUCT_TYPE_W
#define KXE_SOFTWARE_JIJIU_WEB_SHIELD_PRODUCT_TYPE_T 	KXE_NEW_WEB_SHIELD_PRODUCT_TYPE_T


/// 金山密保
#define KXE_SOFTWARE_PASSWORD_PROTECT_PRODUCT_TYPE   0x000A0000
#define KXE_SOFTWARE_PASSWORD_PROTECT_PRODUCT_TYPE_A "0x000A0000"
#define KXE_SOFTWARE_PASSWORD_PROTECT_PRODUCT_TYPE_W L"0x000A0000"
#define KXE_SOFTWARE_PASSWORD_PROTECT_PRODUCT_TYPE_T _T("0x000A0000")

/// 金山云查杀
#define KXE_SOFTWARE_CLOUD_SCAN_PRODUCT_TYPE   0x000B0000
#define KXE_SOFTWARE_CLOUD_SCAN_PRODUCT_TYPE_A "0x000B0000"
#define KXE_SOFTWARE_CLOUD_SCAN_PRODUCT_TYPE_W L"0x000B0000"
#define KXE_SOFTWARE_CLOUD_SCAN_PRODUCT_TYPE_T _T("0x000B0000")

/// 金山网镖
#define KXE_SOFTWARE_KPFW					   0x000C0000
#define KXE_SOFTWARE_KPFW_A						"0x000C0000"
#define KXE_SOFTWARE_KPFW_W					L"0x000C0000"
#define KXE_SOFTWARE_KPFW_T					_T("0x000C0000")

/// 网银保护
#define KXE_SOFTWARE_BANK_PROTECT_PRODUCT_TYPE      0x000D0000
#define KXE_SOFTWARE_BANK_PROTECT_PRODUCT_TYPE_A    "0x000D0000"
#define KXE_SOFTWARE_BANK_PROTECT_PRODUCT_TYPE_W	L"0x000D0000"
#define KXE_SOFTWARE_BANK_PROTECT_PRODUCT_TYPE_T	_T("0x000D0000")

/// 流量管理
#define KXE_SOFTWARE_FLUX_MANAGEMENT_PRODUCT_TYPE      0x000E0000
#define KXE_SOFTWARE_FLUX_MANAGEMENT_PRODUCT_TYPE_A    "0x000E0000"
#define KXE_SOFTWARE_FLUX_MANAGEMENT_PRODUCT_TYPE_W	   L"0x000E0000"
#define KXE_SOFTWARE_FLUX_MANAGEMENT_PRODUCT_TYPE_T	   _T("0x000E0000")

/// 安全中心
#define KXE_SOFTWARE_SECURITY_CENTER_PRODUCT_TYPE      0x000F0000
#define KXE_SOFTWARE_SECURITY_CENTER_PRODUCT_TYPE_A    "0x000F0000"
#define KXE_SOFTWARE_SECURITY_CENTER_PRODUCT_TYPE_W	   L"0x000F0000"
#define KXE_SOFTWARE_SECURITY_CENTER_PRODUCT_TYPE_T	   _T("0x000F0000")

/// 统一升级
#define KXE_SOFTWARE_UNIUPDATE_PRODUCT_TYPE      0x00100000
#define KXE_SOFTWARE_UNIUPDATE_PRODUCT_TYPE_A    "0x00100000"
#define KXE_SOFTWARE_UNIUPDATE_PRODUCT_TYPE_W	 L"0x00100000"
#define KXE_SOFTWARE_UNIUPDATE_PRODUCT_TYPE_T	 _T("0x00100000")

/// 金山卫士
#define KXE_SOFTWARE_WEISHI_PRODUCT_TYPE      0x00111000
#define KXE_SOFTWARE_WEISHI_PRODUCT_TYPE_A    "0x00111000"
#define KXE_SOFTWARE_WEISHI_PRODUCT_TYPE_W	 L"0x00111000"
#define KXE_SOFTWARE_WEISHI_PRODUCT_TYPE_T	 _T("0x00111000")

/// 可牛急救箱
#define KXE_CONEW_RESCUE_PRODUCT_TYPE      0x00120000
#define KXE_CONEW_RESCUE_PRODUCT_TYPE_A    "0x00120000"
#define KXE_CONEW_RESCUE_PRODUCT_TYPE_W    L"0x00120000"
#define KXE_CONEW_RESCUE_PRODUCT_TYPE_T    _T("0x00120000")

/**
 * @}
 */
