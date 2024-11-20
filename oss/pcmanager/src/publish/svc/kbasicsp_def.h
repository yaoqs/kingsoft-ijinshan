///////////////////////////////////////////////////////////////////////////////
///		@file		KBasicSP_def.h
///		@author		yxdh
///		@date		2009-7-10 10:27:58
///		@brief		
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "include/kxe_serialize.h"


/**
* @brief ��������ṩ��ID
*/
typedef enum _EM_SP_ID
{
	enum_QuickScan_SP = 0,				///< ����ɨ������ṩ��
	enum_DiskScan_SP	,				///< ȫ��ɨ������ṩ��
    enum_ARP_SP
} EM_SP_ID;

KXE_JSON_DDX_ENUM(EM_SP_ID)


/**
* @brief SP��״̬
*/
typedef enum _EM_SP_STATUS
{
    em_SP_Unknown       = -2,
    em_SP_Not_Ready     = -1,
	em_SP_Ready         = 0,			///< SP����
	em_SP_Downloading   = 1				///< ��������...
} EM_SP_STATUS;

KXE_JSON_DDX_ENUM(EM_SP_STATUS);


/**
 * �������̵Ĳ���
 */
typedef struct _KSAFE_CREATE_PROCESS_PARAMETER
{
	DWORD        dwSourcePID;      /// �����ߵĽ���ID�����ڸ���
	std::wstring strCommandLine;   /// ���õ�������
	DWORD        dwCreateFlags;    /// �������̵Ĳ�����ʼ�ջ����CREATE_UNICODE_ENVIRONMENT
	BOOL         bDisalbeX64Redirection;  // �Ƿ����X64���ļ��ض���
} KSAFE_CREATE_PROCESS_PARAMETER;

KXE_JSON_DDX_BEGIN(KSAFE_CREATE_PROCESS_PARAMETER)
    KXE_JSON_DDX_MEMBER("SourcePID", dwSourcePID)
	KXE_JSON_DDX_MEMBER("CommandLine", strCommandLine)
	KXE_JSON_DDX_MEMBER("CreateFlags", dwCreateFlags)
	KXE_JSON_DDX_MEMBER("DisalbeX64Redirection", bDisalbeX64Redirection)
KXE_JSON_DDX_END()