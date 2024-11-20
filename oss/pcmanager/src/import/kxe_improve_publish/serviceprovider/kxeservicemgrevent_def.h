//////////////////////////////////////////////////////////////////////
///		@file		kxeservicemgrevent_def.h
///		@author		luopeng
///		@date		2009-3-3 09:07:58
///
///		@brief		������ϵͳ���¼�����
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../include/idl.h"
#include "../include/kxe_serialize.h"

/**
* @defgroup kxeservice_manager_event_define_group KXEngine Base Event Define
* @{
*/

/**
* @brief �����ṩ�������ɹ�����¼����ݽṹ����
*/
typedef struct _KXE_BASE_SERVICE_PROVIDER_STARTUP
{
	KSCLSID clsidSP;
} KXE_BASE_SERVICE_PROVIDER_STARTUP;

KXE_JSON_DDX_BEGIN(KXE_BASE_SERVICE_PROVIDER_STARTUP)
	KXE_JSON_DDX_MEMBER("ServiceProvider", clsidSP);
KXE_JSON_DDX_END()

/**
 * @brief �����ṩ�������ɹ�����¼�ID����,�����¼�����KXE_BASE_SERVICE_PROVIDER_STARTUP
 * @see KXE_FILE_MON_STATUS
 */
#define KXE_SERVICE_PROVIDER_STARTUP_EVENT 1


KXE_DECLARE_EVENT_ID_TYPE(
	enum_SubSystem_Base, 
	KXE_SERVICE_PROVIDER_STARTUP_EVENT, 
	KXE_BASE_SERVICE_PROVIDER_STARTUP
	);

/**
 * @}
 */


