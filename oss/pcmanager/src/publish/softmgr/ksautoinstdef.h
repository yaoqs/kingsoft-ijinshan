//=================================================================
/**
* @file ksautoinstdef.h
* @brief
* @author zhengyousheng <zhengyousheng@kingsoft.com>
* @data 2010-11-04 12:52
*/
//=================================================================

#pragma once

#include <windows.h>

///< ��װ״̬
typedef enum _EM_KSAI_INSTALL_STATUS
{
	em_Status_Unknown = 0,           ///< δ֪״̬
	em_Status_CheckXmlBufSizeFail,   ///< ���xmlbuffersizeʧ��
	em_Status_ParseXmlBufferFail,    ///< ����xmlbufferʧ��
	em_Status_CreateDesktopFail,     ///< ������������ʧ��
	em_Status_CreateSvrProcFail,     ///< ��������˽���ʧ��
	em_Status_SetupTypError,         ///< ��װ���ʹ���, xml��1��ʾ��Ĭ��װ,2��ʾGUI��װ,����ֵ�Ļ���After�ص��л᷵�ش˴���
	em_Status_StartInstProcFail,     ///< ������װ����ʧ��
	em_Status_Installing,            ///< ���ڰ�װ
	em_Status_UserStop,              ///< ��װ�������û�ֹͣ
	em_Status_EnumWndFail,           ///< ��װ������ö�ٲ���ָ���Ĵ���
	em_Status_Timeout,               ///< ��װ��ʱ
	em_Status_SvrProcExit,           ///< ��װ�����з���˽����˳�
	em_Status_Complete               ///< ��װ���
}EM_KSAI_INSTALL_STATUS;

///< ���������Ϣ
typedef struct _S_KSAI_SOFT_BASE 
{
	DWORD dwSoftID;                ///< ���ID
	_S_KSAI_SOFT_BASE()
	{
		dwSoftID = 0;
	};
}S_KSAI_SOFT_BASE;

///< ��װ���̻ص������Ľ�����Ϣ
typedef struct _S_KSAI_STATUS 
{
	S_KSAI_SOFT_BASE struSoftBase; ///< ���������Ϣ
	DWORD dwCurProgressCount;      ///< ��ǰ��������
	DWORD dwTotalProgressCount;    ///< �ܵĽ�������
	DWORD dwInstallStatus;         ///< ��װ״̬,��EM_KSAI_INSTALL_STATUS

	_S_KSAI_STATUS()
	{
		dwTotalProgressCount = 0;
		dwCurProgressCount   = 0;
		dwInstallStatus      = 0;
	}
}S_KSAI_STATUS;

///< ��װǰ�Ļص�����
typedef struct _S_KSAI_SOFT_INFO
{
	S_KSAI_SOFT_BASE struSoftBase;  ///< ���������Ϣ
}S_KSAI_SOFT_INFO;

///< ��װ��Ļص�����
typedef struct _S_KSAI_INST_RESULT
{
	S_KSAI_STATUS struStatus;       ///< ������Ľ�����Ϣ
}S_KSAI_INST_RESULT;