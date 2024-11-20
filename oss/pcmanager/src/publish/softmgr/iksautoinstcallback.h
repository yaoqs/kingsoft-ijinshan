//=================================================================
/**
* @file iksautoinstcallback.h
* @brief
* @author zhengyousheng <zhengyousheng@kingsoft.com>
* @data 2010-11-06 11:22
*/
//=================================================================

#pragma once

#include "ksautoinstdef.h"

class IKSAutoInstCallBack
{
public:

	/**
	* @brief ĳһ�����װǰ�����ݻص�
	* @param[in] pstruSoftInfo ���������Ϣ������Ϣ
	* @return 0 �ɹ�������Ϊʧ�ܴ�����
	*/
	virtual HRESULT BeforeInstall(const S_KSAI_SOFT_INFO* pstruSoftInfo) = 0;

	/**
	* @brief ĳһ����������ݻص�
	* @param[in] pstruStatus ���������Ϣ���������
	* @return 0 �ɹ�������Ϊʧ�ܴ�����
	*/
	virtual HRESULT OnProgress(const S_KSAI_STATUS* pstruStatus) = 0;

	/**
	* @brief ĳһ�����װ������ݻص�
	* @param[in] pstruInstResult ���������Ϣ�������Ϣ�밲װ���
	* @return 0 �ɹ�������Ϊʧ�ܴ�����
	*/
	virtual HRESULT AfterInstall(const S_KSAI_INST_RESULT* pstruInstResult) = 0;
};