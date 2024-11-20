//////////////////////////////////////////////////////////////////////
///		@file		kxebase.h
///		@author		luopeng
///		@date		2008-8-29 09:07:58
///	
///		@brief		kxe_base��غ�������
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../kxebase/kxebase_base.h"
#include "../kxebase/kxebase_http.h"
#include "../kxebase/kxebase_event.h"
#include "../kxebase/kxebase_log.h"
#include "../kxebase/kxebase_config.h"
#include "../kxebase/kxebase_job.h"
#include "../kxebase/kxebase_ipc.h"
#include "../kxesystem/kxesystem.h"
#include "../kxebase/log_msg.h"
#include "../kxeconfig/kxeconfig.h"

#ifndef KXE_BASE_FUNCTION_DEFINE

#if (!defined KXE_BASE_LINK_DLL && !defined _USRDLL) || defined KXE_BASE_NOT_LINK_DLL
#include "../kxebase/kxebase_import.inl"
#else
#pragma comment(lib, "kxebase.lib")
#endif

#endif



/**
* @page kxebase KXEngine Architecture Base SDK Interface
* @section kxebase_initialize SDK��ʼ������������
* - @ref kxebase_initialize_group

* @section kxebase_ipc IPC��غ���
* - @ref kxeipc_sdk_interface_group

* @section kxebase_config_function ������ؽӿ�
* - @ref kxebase_config_group
* - @ref kxeconfig_group

* @section kxebase_event_function �¼�������ؽӿ�
* - @ref kxebase_event_group
* - @ref kxeevent_group

* @section kxebase_http_function HTTP��ؽӿ�
* - @ref kxehttp_sdk_interface_group
* - @ref kxehttp_idl_interface_group

* @section kxebase_log_function ������־��غ���
* - @ref kxebase_log_group
* - @ref kxengine_debug_log_interface

* @section kxebase_job_function job������غ���
* - @ref kxebase_thread_group

* @section kxebase_serialize �����������л���غ�
* - @ref kxe_json_serialize_marco_group

* @section kxebase_system ϵͳ��ؼ��ݺ���
* - @ref kxesystem_compatible_interface

* @section kxebase_example_list ʹ��ʾ���б�
* - @ref kxeconfig_example "���ú���ʹ��ʾ��"
* - @ref kxeevent_example "�¼�����ʹ��ʾ��"
* - @ref kxehttp_example "HTTP-RPCʹ��ʾ��"
*/
