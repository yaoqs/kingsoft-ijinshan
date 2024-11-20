//////////////////////////////////////////////////////////////////////
///		@file		ikxemodulemanageserviceprovider.h
///		@author		luopeng
///		@date		2009-4-18 09:07:58
///
///		@brief		ģ������SP
//////////////////////////////////////////////////////////////////////

#pragma once

/// ģ�����ķ����ṩ��
class IKxEModuleManageServiceProvider
{
public:
	virtual int __stdcall RegisterModuleID(
		const std::wstring& strModuleID,
		KXE_NULL_PARAEMETER&
		) = 0;

	virtual int __stdcall UnregisterModuleID(
		const std::wstring& strModuleID,
		KXE_NULL_PARAEMETER&
		) = 0;

	virtual int __stdcall IsModuleIDExist(
		const std::wstring& strModuleID,
		BOOL& bExist
		) = 0;
};
