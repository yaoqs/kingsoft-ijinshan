//////////////////////////////////////////////////////////////////////
///		@file		ikxeproductmanageserviceprovider.h
///		@author		luopeng
///		@date		2009-4-18 09:07:58
///
///		@brief		��Ʒ�����SP
//////////////////////////////////////////////////////////////////////

#pragma once

/// ��Ʒ����ķ����ṩ��
class IKxEProductManageServiceProvider
{
public:
	virtual int __stdcall RegisterProductID(
		const std::wstring& strProductID,
		KXE_NULL_PARAEMETER&
		) = 0;

	virtual int __stdcall UnregisterProductID(
		const std::wstring& strProductID,
		KXE_NULL_PARAEMETER&
		) = 0;

	virtual int __stdcall IsProductIDExist(
		const std::wstring& strProductID,
		BOOL& bExist
		) = 0;
};
