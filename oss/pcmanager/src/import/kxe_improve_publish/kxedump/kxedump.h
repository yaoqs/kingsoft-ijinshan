//////////////////////////////////////////////////////////////////////
///		@file		kxedump.h
///		@author		luopeng
///		@date		2008-12-13 09:07:58
///
///		@brief		dump���ؽӿ�
//////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @defgroup kxedump_interface_group KXEngine Dump Interface
 * @{
 */

/**
 * @brief ��ʼ������kxedump.dll�����е��쳣�����ӹ�
 * @remark �Ӵ˴�dll�������Ҫע���쳣�������������kxe_base_register_unhandled_exception_filter,
 * kxe_base_unregister_unhandled_exception_filter
 * @see kxe_base_register_unhandled_exception_filter, kxe_base_unregister_unhandled_exception_filter
 * @return 0 �ɹ�������Ϊʧ�ܴ�����
 */
int InitializeDump();


#include "kxedump.inl"
/**
 * @}
 */
