////////////////////////////////////////////////////////////////////////////////
//      
//      common include File for kpfw
//      
//      File      : netdef.h
//      Version   : 1.0
//      Comment   : �������ڳ��õ�����
//      
//      Create at : 2008-4-7
//      Create by : liupeng
//      
////////////////////////////////////////////////////////////////////////////////

#pragma once 

//////////////////////////////////////////////////////////////////////////
// Ӧ�ó����������
typedef enum emAppRuleType
{
	enumART_Unknown		= 0,							// δ֪����
	enumART_AllowAways	= 1,							// һֱ����
	enumART_AllowOnce	= 2,							// ����һ��
	enumART_AllowThisProcess = 3,						// ���ν�������

	enumART_DenyAways	= 4,							// һֱ��ֹ
	enumART_DenyOnce	= 5,							// ��ֹ����
	enumART_DenyNextProc = 6,							// ��ֹ���´���������

	enumART_Prompt		= 7,							// ����ѯ��
}AppRuleType;
//------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// �����û�ѡ������
typedef enum emUserSelectMode
{
	enumUSM_Mask			= 0xffff0000,				// ����

	enumUSM_Auto		= 1	<< 16,						// ʹ�ÿ�����֤����ж�
	
		enumUSM_Auto_Auto = 0,							// δ֪����
		enumUSM_Allow_Pop	= 2,						// ���ݼ�ס����
		enumUSM_Deny_Pop	= 4,						// ���ݼ�ס��ֹ
		enumUSM_Allow_SafeDign	= 5,					// ��ȫ����

	enumUSM_Allow		= 2 << 16,						// ���Ǳ��޸ģ��������
	enumUSM_Deny		= 3	<< 16,						// ���ǽ�ֹ
	enumUSM_Prompt		= 4 << 16,						// ���ǵ�����ʾ
} UserSelectMode;
//------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// ������֤����
typedef enum emTrustMode
{
	enumTM_Mask			= 0xffff0000,					// ����

	enumTM_Unknown		= 1 << 16,						// ��ǰδ֪����
	enumTM_Safe			= 2 << 16,						// ������֤�Զ�����
	enumTM_Danger		= 3 << 16,						// ���ݼ�ס����
} TrustMode;

// ������֤������
typedef enum emTrustSubMode
{
	enumTSM_DigtSign				= 1,				// ����ǩ��
	enumTSM_Cooperate				= 2,				// �������

	enumTSM_TrustRep				= 3,				// ������֤

	enumTSM_ServerBusy				= 4,				// ������æ
	enumTSM_TrustUnkonwn			= 5,				// ������֤δ֪

	enumTSM_Virus					= 6,				// ����
	enumTSM_Hack					= 7,				// �ڿ����
	enumTSM_Worm					= 8,				// ���
	enumTSM_Infected				= 9,				// ����Ⱦ
	enumTSM_RiskWare				= 10,				// Σ�����
	enumTSM_Other_Virus				= 11,				// ����δ֪����

	enumTSM_TrustFailed				= 12,				// ������֤ʧ��
} TrustSubMode;
//------------------------------------------------------------------------
