//////////////////////////////////////////////////////////////////////
///		@file		kxeeventid_def.h
///		@author		luopeng
///		@date		2008-9-10 09:07:58
///
///		@brief		�¼�����id�����Ͷ�Ӧ��ͷ�ļ�����
//////////////////////////////////////////////////////////////////////

#pragma once
#include "../kxebase/kxesubsystemid_def.h"

/**
 * @addtogroup kxeevent_group
 * @{
 */

template
<
	int nEventId
>
struct EventIdToType
{
	typedef void type;
};

/**
 * @brief ���ڽ�ָ�������ݽṹ���¼�id(_sub_system << 16 | _id)��
 * @see KXE_SUB_SYSTEM_ID
 * @param[in] _sub_system ΪKXE_SUB_SYSTEM_ID�е�ö����
 * @param[in] _id Ϊ������ϵͳ���Ѷ�����¼�id
 * @param[in] _type Ϊ��Ҫ�󶨵��¼�����
 */
#define KXE_DECLARE_EVENT_ID_TYPE(_sub_system, _id, _type) \
	template\
	<>\
	struct EventIdToType<_sub_system << 16 | _id>\
	{\
		typedef _type type;\
	};

/**
 * @}
 */
