#pragma once
#include "kbasicsp_def.h"

class KBasicSPWrapperClient
{
public:
	KBasicSPWrapperClient(void);
	~KBasicSPWrapperClient(void);

	/**
	* @brief        ����SP
	* @return		0 �ɹ�, ����Ϊʧ�ܴ����룬�Ѿ����صķ���E_KXEBASIC_SERVICE_PROVIDER_STARTED
	*/
	int __stdcall StartSP(
		/* [in] */ const EM_SP_ID&		SPID,
		/* [out]*/ KXE_NULL_PARAEMETER&
		);

	/**
	* @brief        �ر�SP
	* @return		0 �ɹ�, ����Ϊʧ�ܴ�����
	*/
	int __stdcall StopSP(
		/* [in] */ const EM_SP_ID&		SPID,
		/* [out]*/ KXE_NULL_PARAEMETER&
		);

	/**
	* @brief        ��ѯSP״̬
	* @return		0 �ɹ�, ����Ϊʧ�ܴ�����
	*/
	int __stdcall QuerySPStatus(
		/* [in] */ const EM_SP_ID&		SPID,
		/* [out]*/ EM_SP_STATUS&		Status
		);

	/**
	* @brief ʹ����ͨ�û�Ȩ����������
	* @param[in] parameter �������̵Ĳ���
	* @param[out] dwProcessHandle ���صĽ��̾���������Ƶ�ָ��PID�ڣ����ڲ������л�HANDLE����������д��DWORD
	* @return 0 �ɹ�������Ϊʧ�ܴ�����
	*/
	int __stdcall CreateProcessAsNormalUser(
		const KSAFE_CREATE_PROCESS_PARAMETER& parameter, 
		DWORD& dwProcessHandle
		);

};
