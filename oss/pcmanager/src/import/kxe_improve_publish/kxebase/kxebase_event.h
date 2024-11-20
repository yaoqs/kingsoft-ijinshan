//////////////////////////////////////////////////////////////////////
///		@file		kxebase_event.h
///		@author		luopeng
///		@date		2008-8-29 09:07:58
///	
///		@brief		�¼�������غ����Ķ���
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../kxeevent/ikxeeventnotify.h"
#include "../kxeevent/kxeeventid_def.h"
#include "../DOMUtil/JSONUtil/KJSONDataAccess.h"
#include "../loki/static_check.h"
#include "../loki/TypeManip.h"
#include <string>

/**
 * @defgroup kxebase_event_group KXEngine Architecture Base SDK Event Interface
 * @{
 */


/**
* @brief ���¼�����ϵͳ����һ���¼�
* @param[in] subSystemId Ϊ�����¼�����ϵͳid,�ο�KXE_SUB_SYSTEM_ID
* @param[in] sEventId Ϊ������ϵͳ������¼�id
* @param[in] pszBuffer Ϊ������ϵͳ�������¼�����,��ṹΪJson����
* @param[in] nBufferSize ΪpszBuffer�Ĵ�С
* @remark ����ͬһ����ϵͳ�����͵��¼�,��������˳��,��ͬ����ϵͳ���豣֤
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_post_event(
	KXE_SUB_SYSTEM_ID subSystemId,
	short sEventId,
	const char* pszBuffer, 
	int nBufferSize
	);

/**
* @brief ���¼�����ϵͳע����Ҫ��ע���¼�
* @param[in] subSystemId Ϊ�����¼�����ϵͳid,�ο�KXE_SUB_SYSTEM_ID
* @param[in] sEventId Ϊ������ϵͳ������¼�id
* @param[in] pNotify Ϊ�����¼���Ӧ�Ľӿ�
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_register_event_notify(
	KXE_SUB_SYSTEM_ID subSystemId,
	short sEventId, 
	IKxEEventNotify* pNotify
	);

/**
* @brief ���¼�����ϵͳȡ����Ҫ��ע���¼�
* @param[in] subSystemId Ϊ�����¼�����ϵͳid,�ο�KXE_SUB_SYSTEM_ID
* @param[in] sEventId Ϊ������ϵͳ������¼�id
* @param[in] pNotify Ϊ�����¼���Ӧ�Ľӿ�
* @remark 
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
int __stdcall kxe_base_unregister_event_notify(
	KXE_SUB_SYSTEM_ID subSystemId,
	short sEventId,
	IKxEEventNotify* pNotify
	);

/**
* @brief ���¼�����ϵͳ�����¼��ĺ���ʵ��
* @param[in] subSystemId Ϊ�����¼�����ϵͳid,�ο�KXE_SUB_SYSTEM_ID
* @param[in] sEventId Ϊ������ϵͳ������¼�id
* @param[in] type Ϊ��Ҫ�������¼����ݽṹ
* @remark �˺��������type���ݽṹ���л�ΪJson����
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
template
<
	typename EventType
>
int KxEPostEventT(KXE_SUB_SYSTEM_ID subSystemId, short sEventId, const EventType& type)
{

	KANDOM::KJSONDataAccess dataAccess;
	int nErr = dataAccess.LoadDOMName("root");
	if (nErr == 0)
	{
		nErr = dataAccess.WriteData("event", const_cast<EventType&>(type));
	}

	if (nErr == 0)
	{
		std::string strBuffer;
		nErr = dataAccess.ToCompactString(&strBuffer);
		if (nErr == 0)
		{
			nErr = kxe_base_post_event(subSystemId, sEventId, strBuffer.c_str(), (int)strBuffer.size() + 1);
		}
	}
	return nErr;
}

/**
* @brief ���¼�����ϵͳ�����¼�
* @param[in] _sub_system Ϊ�����¼�����ϵͳid,�ο�KXE_SUB_SYSTEM_ID
* @param[in] _event_id Ϊ������ϵͳ������¼�id
* @param[in] _value Ϊ��Ҫ�������¼����ݽṹ
* @remark �˺꽫����KxEPostEventT,��_valueת��ΪJson�����ݽṹ
* @return 0 �ɹ�, ����ֵΪʧ�ܵĴ����룬
*/
#if _MSC_VER > 1200
#define KXE_POST_EVENT(_sub_system, _event_id, _value) \
	STATIC_CHECK(!(Loki::IsSameType<EventIdToType<_sub_system << 16 | _event_id>::type, void>::value), NotDefinedSubSystemModule);\
	KxEPostEventT(_sub_system, _event_id, _value)
#else
#define KXE_POST_EVENT(_sub_system, _event_id, _value) \
	STATIC_CHECK(!(Loki::IsEqualType<EventIdToType<_sub_system << 16 | _event_id>::type, void>::value), NotDefinedSubSystemModule);\
	KxEPostEventT(_sub_system, _event_id, _value)
#endif

// STATIC_CHECK((Loki::IsSameType<EventIdToType<_sub_system << 16 | _event_id>::type, EventType>::value), NotMatchedSubSystemModuleEvent);

/**
 * @}
 */
