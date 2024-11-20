////////////////////////////////////////////////////////////////
//
//	Filename: 	dump.h
//	Creator:	yangjun  <yangjun@kingsoft.com>
//	Date:		2009-12-8  23: 07
//	Comment:	�ɴ�����dump.h�������
//
///////////////////////////////////////////////////////////////

#pragma once


#include <windows.h>

typedef DWORD DUMP_CHANNEL;



/**
* @brief	�򿪱���������
* @remark	Ϊ���ݴ������ϰ汾,�������������,������Ʒ���������ʹ��
*/
void __stdcall KxEOpenDumpMonitor();



/**
* @brief	�򿪱���������
* @param	[in] bShowUI��		����ʱ�Ƿ���ʾ�Ի���
* @param	[in] pszUUID		�û�UUID(�ɴ�NULL)
* @return	[in] dwDumpChannel	�ϱ����������˺��ͨ���ű�ʶ,ͨ���˱�ʶ���õ���Ӧ��Dump�ļ�,
								ĿǰΪ��ͬ�Ĳ�Ʒ���䲻ͬ��ͨ���ű�ʶ����,��Ʒ�Լ�����Ϊ��ͬ�Ľ�������ͨ���ű�ʶ�����ڵ�ֵ�����ֲ�ͬ�Ľ���

								����Ʒͨ���ŷ�Χ����,�����Ʒ�����·����ͨ���ŷ�Χ��ʹ��

								[0, 0]		����ͨ��
								[1,99]		��ȫ100
								[100,199]	������
								[200,299]	������
								[300,399]	�ܱ�
								[400,499]	����

								����:��������Ĳ�Ʒ��ʹ�þͿ����������ģ�KxEOpenDumpMonitorEx(true, NULL, 201),dwDumpChannel��ֵ��[200,299]֮�伴��
* @remark	
*/
void __stdcall KxEOpenDumpMonitorEx(bool bShowUI, const wchar_t*pszUUID, DUMP_CHANNEL dwDumpChannel);


/**
* @brief	�򿪱���������
* @param	[in] bShowUI��		����ʱ�Ƿ���ʾ�Ի���
* @param	[in] pszUUID        ����UUID
* @param	[in] dwProductId	��ƷID��Ĭ��Ϊ0
* @return	[in] dwDumpChannel	�ϱ����������˺��ͨ���ű�ʶ,ͨ���˱�ʶ���õ���Ӧ��Dump�ļ�,
								ĿǰΪ��ͬ�Ĳ�Ʒ���䲻ͬ��ͨ���ű�ʶ����,��Ʒ�Լ�����Ϊ��ͬ�Ľ�������ͨ���ű�ʶ�����ڵ�ֵ�����ֲ�ͬ�Ľ���

								����Ʒͨ���ŷ�Χ����,�����Ʒ�����·����ͨ���ŷ�Χ��ʹ��

								[0, 0]		����ͨ��
								[1,99]		��ȫ100
								[100,199]	������
								[200,299]	������
								[300,399]	�ܱ�
								[400,499]	����

								����:��������Ĳ�Ʒ��ʹ�þͿ����������ģ�KxEOpenDumpMonitorEx2(true, null, null, 0x100, 201),dwDumpChannel��ֵ��[200,299]֮�伴��
* @remark	
*/
void __stdcall KxEOpenDumpMonitorEx2(bool bShowUI,
                                     const wchar_t *pszUUID, 
                                     DWORD dwProductId,
                                     DUMP_CHANNEL dwDumpChannel);


int __stdcall KxESetPostServer(
	const char* pszPostServerAddress
	);

/**
* @brief	�����Ƿ���������ģʽ
* @param	[in] bTrialMode		����ģʽ��Ĭ��Ϊ��
* @remark	
*/
void __stdcall KxESetTrialMode(
	bool bTrialMode
	);

void __stdcall KxRegisterUnhandledExceptionFilter(
	LPTOP_LEVEL_EXCEPTION_FILTER
	);

void __stdcall KxUnregisterUnhandledExceptionFilter(
	LPTOP_LEVEL_EXCEPTION_FILTER
	);



typedef void (__stdcall *PFN_KxEOpenDumpMonitor)();
typedef void (__stdcall *PFN_KxEOpenDumpMonitorEx)(bool, const wchar_t*, DWORD);
typedef void (__stdcall *PFN_KxEOpenDumpMonitorEx2)(bool, const wchar_t*, DWORD, DWORD);
typedef void (__stdcall *PFN_KxESetPostServer)(const char*);
typedef void (__stdcall *PFN_KxESetTrialMode)(bool);
typedef void (__stdcall *PFN_KxRegisterUnhandledExceptionFilter)(LPTOP_LEVEL_EXCEPTION_FILTER);
typedef void (__stdcall *PFN_KxUnregisterUnhandledExceptionFilter)(LPTOP_LEVEL_EXCEPTION_FILTER);