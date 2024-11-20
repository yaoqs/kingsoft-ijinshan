//////////////////////////////////////////////////////////////////////
///		@file		kxeevent.h
///		@author		luopeng
///		@date		2008-9-10 09:07:58
///
///		@brief		�¼������ͷ�ļ�����
//////////////////////////////////////////////////////////////////////

#pragma once
#include "ikxeeventnotify.h"
#include "ikxeeventmgr.h"

/**
	@page kxeevent_example KXEngine EventSystem Example

	- @ref kxeevent_example_struct
	- @ref kxeevent_example_post
	- @ref kxeevent_example_notify

	@section kxeevent_example_struct �������ݽṹ

	@code
	#pragma once
	#include <string>
	#include "include/kxe_serialize.h"

	typedef struct _KXE_FILE_MON_STATUS
	{
		BOOL bIsEnable;
	} KXE_FILE_MON_STATUS;

	KXE_JSON_DDX_BEGIN(KXE_FILE_MON_STATUS)
		KXE_JSON_DDX_MEMBER("Enable", bIsEnable);
	KXE_JSON_DDX_END()

	#define KXE_FILE_MON_STATUS_EVENT 1

	KXE_DECLARE_EVENT_ID_TYPE(enum_SubSystem_FileMon, KXE_FILE_MON_STATUS_EVENT, KXE_FILE_MON_STATUS);

	@endcode

	@section kxeevent_example_post �����¼�
	@code
	KXE_FILE_MON_STATUS status;
	status.bIsEnable = m_bIsEnable;
	KXE_POST_EVENT(enum_SubSystem_FileMon, KXE_FILE_MON_STATUS_EVENT, status);		
	@endcode

	@section kxeevent_example_notify ��Ӧ�¼�
	@code
	// ͷ�ļ��еĶ���
	class KxEScanServiceProvider : public IKxEEventNotify
	{
	public:
		KXE_DECLARE_EVENT_NOTIFY();

	int OnFileMonStatusEvent(
		short sSubSystemId, 
		short sEventId,
		const KXE_FILE_MON_STATUS& status, 
		int nErr
		);
	};

	// ʵ���ļ��еĶ���
	KXE_BEGIN_EVENT_NOTIFY(KxEScanServiceProvider)
		KXE_ON_EVENT_PROCESS(enum_SubSystem_FileMon, KXE_FILE_MON_STATUS_EVENT, OnFileMonStatusEvent)
	KXE_END_EVENT_NOTIFY()

	int KxEScanServiceProvider::OnFileMonStatusEvent(short sSubSystemId,
													 short sEventId, 
													 const KXE_FILE_MON_STATUS& status,
													 int nErr)
	{
		std::cout << "The filemon status is " << status.bIsEnable << std::endl;
		return 0;
	}
	int KxEScanServiceProvider::StartService()
	{
		kxe_base_register_event_notify(
			enum_SubSystem_FileMon,
			KXE_FILE_MON_STATUS_EVENT,
			this
			);
		return 0;
	}
	
	@endcode
 */

/**
 @page kxeevent_json_data_struct evnet_json_data_struct

 @section kxeevent_json �¼������Json���ݽṹ
 @code
 root :
 {
	event:
	{
		// any json data
	}
 }

@endcode
*/
