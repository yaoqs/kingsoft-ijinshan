///////////////////////////////////////////////////////////////
//
//	Filename: 	KwsIPCWarpper.h
//	Creator:	lichenglin  <lichenglin@kingsoft.com>
//	Date:		2009-4-2  11:33
//	Comment:	
//
///////////////////////////////////////////////////////////////


#ifndef _KwsIPCWarpper_old_h_
#define _KwsIPCWarpper_old_h_
#include "KwsSimpleIPCClientOld.h"
#include <atlstr.h>
#include <string>
#include <vector>


namespace kws_old_ipc {

BOOL KwsIsIPCInit();


//////////////////////////////////////////////////////////////////////////
//
// �������
//
//////////////////////////////////////////////////////////////////////////

/**
* @brief   ��ȡ����״̬ (���� �Ƿ��ҡ��Ƿ����ء��Ƿ�Ӧ���˳����Ƿ���Ҫ������)
*/
int KwsQueryTrayStatus( TRAYSTATUS* pnTrayStatus , DWORD *pdwSession);



/**
* @brief   �������̵���״̬ ( ���� or �䰵 )
           Ϊ�����ϴ��� ��ʱû������
*/
int SetTrayStatus( bool bOn );

/**
* @brief   �����Ƿ���ʾ����
*/
int ShowTray( bool bShow );


/**
* @brief   �˳�����
*/
int KwsQuitTray();



//////////////////////////////////////////////////////////////////////////
//
// �������
//
//////////////////////////////////////////////////////////////////////////

/**
* @brief   ��������Ϣ��ӵ���������ݶ�����, 
           ���̻�Ӷ����л�ȡ����������

	nReason ��ʾ�������ݵ�ԭ��Ĭ��-1��ʾû��ԭ��	
*/
int ShowPopo2( int nPopoStyle, const wchar_t* pwszMsg, bool bForceNewPage, int nReason = -1);

/**
* @brief   �ӷ�������ݶ������ȡһ��������Ϣ
           ���pbExists����FALSE, ��ʾ���ݶ���Ϊ��
*/
struct POPOINFO
{
	int  nPopoStyle;
	std::wstring strMsg;
	std::wstring strBtn;
};

int QueryPopoMessage( BOOL* pbExists, POPOINFO* pPopoInfo );



//////////////////////////////////////////////////////////////////////////
//
// ��־���
//
//////////////////////////////////////////////////////////////////////////
/**
* @brief   ��¼��־
*/
int KwsLog( const wchar_t* pwszFile, const wchar_t* pwszMsg );

/**
* @brief   ɾ����־
*/
int KwsDeleteLog( const wchar_t* pwszFile, LOGTYPE lt = TY_ALL);


//////////////////////////////////////////////////////////////////////////
//
// ��������
//
//////////////////////////////////////////////////////////////////////////
int KwsCallAsUser( const wchar_t* pszCmdline );

int KwsCallAsSystem( const wchar_t* pszCmdline );

int KwsCallAsUserOrSystem( const wchar_t* pszCmdline );

int KwsInjectSvc(const wchar_t* pszBp);

int KwsRegNotifyChange();

//////////////////////////////////////////////////////////////////////////
//
// ��ǰ����������
//
//////////////////////////////////////////////////////////////////////////
int KwsSetProgramPath( const wchar_t* pszPath, DWORD dwProcessID );

int KwsGetProgramPath( wchar_t* pszPath, int nSize, DWORD* pdwProcessID);

//////////////////////////////////////////////////////////////////////////
//
// Setting
//
//////////////////////////////////////////////////////////////////////////
int KwsSetProfileStringValue(const wchar_t *pszKey, const wchar_t *pszValue);

int KwsGetProfileStringValue(const wchar_t *pszKey, std::wstring &strValue, const wchar_t *pszDefault);

int KwsSetRegStringValue(const wchar_t *pszKey, const wchar_t *pszSubKey, const wchar_t *pszValue);

int KwsGetRegStringValue(const wchar_t *pszKey, const wchar_t *pszSubKey, std::wstring &strValue, const wchar_t *pszDefault);

int KwsSetRegDWORDValue(const wchar_t *pszKey, const wchar_t *pszSubKey, DWORD dwValue);

int KwsGetRegDWORDValue(const wchar_t *pszKey, const wchar_t *pszSubKey, DWORD &dwValue, DWORD dwDefault);

int KwsDeleteRegValue(const wchar_t *pszKey, const wchar_t *pszSubKey);

int KwsSetCRRegStringValue(const wchar_t *pszKey, const wchar_t *pszSubKey, const wchar_t *pszValue);

//////////////////////////////////////////////////////////////////////////
//
// ������
//
//////////////////////////////////////////////////////////////////////////
int KwsBlackListAdd(int nReason, const wchar_t *pszUrl);

int KwsBlackListDelete(const wchar_t *pszUrl);

int KwsBlackListExport(const wchar_t *pszFilePath, int nADID = -1);

int KwsBlackListImport(const wchar_t *pszFilePath, 
                       const wchar_t *pszItemFlag = L"1",
                       const wchar_t *psziid = L"10");

int KwsBlackListUnSubscribe(const wchar_t *pszItemFlag = L"1",
                            const wchar_t *psziid = L"10");

int KwsBlackListAddEx(int nReason, const wchar_t *pszUrl, std::wstring& strFtUrl,
                      std::wstring& wstrexist, int nADID = 0);

//////////////////////////////////////////////////////////////////////////
//
// ������ҳ
//
//////////////////////////////////////////////////////////////////////////
/**
*  nType ��ʾ������ҳ���ͣ�1��ʾ�û�����ģ�2��ʾ���û�����ģ�	
*/
int KwsSSPAdd(int nType, const wchar_t *pszUrl);

int KwsSSPDelete(const wchar_t *pszUrl);

/**
*  nType ��ʾ������ҳ���ͣ�1��ʾ�û�����ģ�2��ʾ���û�����ģ�0��ʾ��ȡ���У�	
*/
int KwsSSPGet(int nType, std::vector<std::wstring>& vecSsps);

/**
*  ɾ���Զ�ɨ��Ķ�����ҳ
*/
int KwsSSPDeleteAuto();

//////////////////////////////////////////////////////////////////////////
//
// ��ҳ����
//
//////////////////////////////////////////////////////////////////////////
int KwsFRAdd(int nSet, const wchar_t *pszFR);

int KwsFRDelete(const wchar_t *pszFR);

int KwsFRExport(const wchar_t *pszFilePath);

int KwsFRImport(const wchar_t *pszFilePath);

//////////////////////////////////////////////////////////////////////////
/**
* @brief   ��¼��־
*/
int KwsWriteDanUrl( const wchar_t* pwszFile, const wchar_t* pwszMsg );

//////////////////////////////////////////////////////////////////////////

/**
*  ��ȡsp����Ŀ¼
*/
int KwsGetSpDir(char* pszDir, unsigned uLen);

/**
*  ��ȡ���ܰ汾����
*/
int KwsGetKwsType(int* pnType);

}

#endif // _KwsIPCWarpper_h_
