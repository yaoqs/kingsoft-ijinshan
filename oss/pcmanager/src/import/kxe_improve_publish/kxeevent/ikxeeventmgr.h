//////////////////////////////////////////////////////////////////////
///		@file		IKxEEventMgr.h
///		@author		luopeng
///		@date		2008-9-10 09:07:58
///
///		@brief		�¼�����ӿ�
//////////////////////////////////////////////////////////////////////

#pragma once
#include <Unknwn.h>
#include "../kxebase/kxesubsystemid_def.h"

/**
 * @defgroup kxeevent_component_interface KXEngine Architecture Event Component Interface
 * @remark ����������Զ���ʹ��
 * @{
 */

class IKxEEventNotify;

MIDL_INTERFACE("9E9B9EF3-31F5-4b96-82ED-99C9444AD4A3")
IKxEEventMgr : public IUnknown
{
	virtual int __stdcall Start() = 0;

	virtual int __stdcall Stop() = 0;

	virtual int __stdcall RegisterEvent(
		KXE_SUB_SYSTEM_ID subSystemId,
		short sEventId,
		IKxEEventNotify* pNotify
		);

	virtual int __stdcall UnregisterEvent(
		KXE_SUB_SYSTEM_ID subSystemId,
		short sEventId,
		IKxEEventNotify* pNotify
		);

	virtual int __stdcall PostEvent(
		KXE_SUB_SYSTEM_ID subSystemId,
		short sEventId,
		const char* pszBuffer,
		int nBufferSize
		);
};

/**
 * @}
 */