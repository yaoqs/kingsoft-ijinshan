//////////////////////////////////////////////////////////////////////
///		@file		kxestat.h
///		@author		luopeng
///		@date		2008-9-10 09:07:58
///
///		@brief		��ɱϵͳ��SDK�ṩ
//////////////////////////////////////////////////////////////////////

#pragma once
#include "../include/kxebase_plugin.h"
#include "../include/kxe.h"

/**
 * @defgroup kxestat_subsystem_interface_group KXEngine Activity Statical Subsystem
 * @{
 */

/**
 * @brief ֪ͨ����������ǰ��Ʒ�İ�װ״̬
 * @param[in] pnProductIdArray ��ǰ��װ��Ʒ���б������հ�װʱ�估�����ϵ����
 * @param[in] uIdCount pnProductIdArray������
 * @return 0 �ɹ�������Ϊʧ�ܴ�����
 */
KXEAPI
int __stdcall kxe_stat_notify_product_setup(
	int* pnProductIdArray,
	unsigned int uIdCount
	);

/**
 * @brief ֪ͨ���������������Ծ�ˣ������ϵ�ǰ��װ�����в�Ʒ
 * @param[in] pnProductIdArray ��ǰ��װ��Ʒ���б������հ�װʱ�估�����ϵ����
 * @param[in] uIdCount pnProductIdArray������
 * @return 0 �ɹ�������Ϊʧ�ܴ�����
 */
KXEAPI
int __stdcall kxe_stat_notify_kxengine_activity(
	int* pnProductIdArray,
	unsigned int uIdCount
	);

/**
 * @brief ֪ͨ��������ĳ����Ʒ��Ծ��
 * @param[in] nProductId ��Ծ�Ĳ�ƷID
 * @return 0 �ɹ�������Ϊʧ�ܴ�����
 */
KXEAPI
int __stdcall kxe_stat_notify_product_activity(
	int nProductId
	);

/**
 * @}
 */
