//////////////////////////////////////////////////////////////////////
///		@file		ikxeeventnotify.h
///		@author		luopeng
///		@date		2008-8-27 14:07:58
///
///		@brief		jason������C++��������ת������ع��ߺ�������
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../json/json.h"
#include "../DOMUtil/JSONUtil/KJSONDataAccess.h"
#include "kxeevent.h"
#include "kxeeventid_def.h"
#include "../loki/static_check.h"
#include "../loki/TypeManip.h"

/**
 * @defgroup kxeevent_group KXEngine Architecture Event Interface
 * @{
 */

/**
 * @brief ������Ҫ�����¼������ģ�����ʵ�ֵĽӿ�
 */
class IKxEEventNotify
{
public:
	/**
	 * @brief ���ж�Ӧ��sSubSystemId << 16 | sEventId���¼�����ʱ,������ô˺���
	 * @see KXE_SUB_SYSTEM_ID
	 * @param[in] subSystemId Ϊ��ϵͳ��ID����,�μ�KXE_SUB_SYSTEM_ID
	 * @param[in] sEventId Ϊ������ϵͳ������¼�ID��
	 * @param[in] pszJson �¼�����ʱ,���¼�����ת��Ϊ��Json����
	 * @param[in] uSize pszJson�ĳ���,�����ַ���������
	 */
	virtual int __stdcall Notify(
		KXE_SUB_SYSTEM_ID subSystemId, 
		short sEventId, 
		const char* pszJson, 
		unsigned int uSize
		) = 0;
};

template
<
	typename Object,
	typename EventType
>
int KxECallEventProcessFunction(Object* pObject,
								int (Object::*memFunction)(int, const EventType&),
								int nId,
								const char* pszJson,
								int nSize)
{
	EventType eventValue;

	KANDOM::KJSONDataAccess dataAccess;
	int nErr = dataAccess.LoadString(pszJson);
	if (nErr == 0)
	{
		nErr = dataAccess.ReadData("event", eventValue);  // ʧ��?

		if (nErr == 0)
		{
			(pObject->*memFunction)(nId, eventValue);
		}
	}

	return nErr;
}

/**
 * @brief ����Ҫʵ��IKxEEventNotify����ͷ�ļ����÷Ÿú�
 */
#define KXE_DECLARE_EVENT_NOTIFY() \
	int __stdcall Notify(KXE_SUB_SYSTEM_ID sSubSystemId, short sEventId, const char* pszJson, unsigned int nSize);

/**
 * @brief �ú�����ʵ��IKxEEventNotify��Notify����,����pszJsonת��Ϊָ�����������ͺ����
 */
#define KXE_BEGIN_EVENT_NOTIFY(_class)\
		int _class::Notify(KXE_SUB_SYSTEM_ID sSubSystemId, short sEventId, const char* pszJson, unsigned int nSize){\
				switch (sSubSystemId << 16 | sEventId) {

/**
 * @brief ��_sub_system_id << 16 | _id����¼�ת��Ϊ��Ӧ���������ͺ�,���ø�_function
 */
#define KXE_ON_EVENT_PROCESS(_sub_system_id, _id, _function)\
						case _sub_system_id << 16 | _id: \
						{\
							STATIC_CHECK(!(Loki::IsSameType<EventIdToType<_sub_system_id << 16 | _id>::type, void>::value), NotDefinedSubSystemModule);\
							EventIdToType<_sub_system_id << 16 | _id>::type eventValue;\
							KANDOM::KJSONDataAccess dataAccess;\
							int nErr = dataAccess.LoadString(pszJson);\
							if (nErr == 0)\
							{\
								nErr = dataAccess.ReadData("event", eventValue);  \
								if (nErr == 0)\
								{\
									return _function(_sub_system_id, _id, eventValue, 0);\
								}\
							}\
							if (nErr != 0)\
							{\
								_function(_sub_system_id, _id, eventValue, nErr);\
							}\
							return nErr;\
						}\
						break;

/**
 * @brief �ú����ڱ�־ʵ��IKxEEventNotify��Notify��������
 */
#define KXE_END_EVENT_NOTIFY() \
						default:\
								return 0;\
				}\
				return 0;\
		}

/**
 * @}
 */
