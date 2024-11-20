#ifndef _KwsCmptComm_h_
#define _KwsCmptComm_h_

#include <atlstr.h>

typedef enum _E_KWS_KWSTYPE
{
	enum_KKT_Unknown,
	enum_KKT_STD,        /// ������
	enum_KKT_Ksafe,      /// ��ʿ���ɰ�
	enum_KKT_Duba		 /// ���Լ��ɰ�
} E_KWS_KWSTYPE;


__declspec(noinline) E_KWS_KWSTYPE GetKTBySvcProcName();   //��sp�и��ݷ���������ж����ܰ汾

__declspec(noinline) E_KWS_KWSTYPE GetKTByIpc();  // ͨ��ipcͨ�Ų�ѯ���ܰ汾

BOOL IsKwsStdInstalled();  // �Ƿ�װ�˶���������

BOOL IsKwsKsafeInstalled(); // �Ƿ�װ����ʿ������

BOOL IsKwsDubaInstalled(); // �Ƿ�װ�˶��԰�����

BOOL IsKwsStdExist(int* pnType = NULL);  // �����Ƿ��Ѿ�����

int  GetRunningKwsType(E_KWS_KWSTYPE* peType);  // ��ȡ�����е����ܰ汾

BOOL GetCurrentStartupKWSProductName(ATL::CString& strName);

#endif