#pragma once

#include "wtypes.h"
#include <Unknwn.h>

struct IEventSender;
class CKisRpcManager;
struct IUpdMgr;

MIDL_INTERFACE("A2351875-2EA5-4F43-1236-01BEC5D2DA23")
IManage:public IUnknown
{
	virtual HRESULT __stdcall Init(IEventSender *piEventSender) = 0;
	virtual HRESULT __stdcall Uninit() = 0;

	virtual HRESULT __stdcall BindRpc(CKisRpcManager *pKisRpcManager) = 0;
	virtual HRESULT __stdcall UnbindRpc() = 0;

	//Return:
	//	S_OK	���Դ������˳�ָ���ļ�
	//	S_FALSE	���Դ�������Ҫ�˳������
	//	E_ABORT	���ܴ�����ֹ�˳������
	//Param:
	//	dwDataType		���µķ�ʽ����index�ļ��ж���
	//	pwsUpdFileList	����ļ�����"|"�ֿ�
	virtual HRESULT __stdcall NotifyUpdate(IN DWORD dwDataType, IN const wchar_t* pwsUpdFileList) = 0;

	//Return:
	//	S_OK	���Դ������˳�ָ�����
	//	S_FALSE	���Դ�������Ҫ�˳������
	//	E_ABORT	���ܴ�����ֹ�˳������
	//Param:
	//	clsUpd		�����������CLSID
	virtual HRESULT __stdcall NotifyUpdate(IN GUID clsUpd) = 0;


	//Return:
	// S_OK �ɹ����¼���ж�ص������ݻ�ģ��
	// E_FAIL ʧ��
	virtual HRESULT __stdcall CompleteUpdate() = 0;
};

MIDL_INTERFACE("6C1027F9-FB80-41AC-9054-567574B7CFE3")
IManageUpdEx:public IUnknown
{
	virtual HRESULT __stdcall SetUpdManagr(IUpdMgr *piUpdManager) = 0;
};