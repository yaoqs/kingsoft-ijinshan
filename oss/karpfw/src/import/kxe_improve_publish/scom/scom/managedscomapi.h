/********************************************************************
* CreatedOn: 2005-10-24   11:58
* FileName: SCOMAPI.h
* CreatedBy: qiuruifeng <qiuruifeng@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/
#ifndef SCOMEXTAPI_H
#define SCOMEXTAPI_H

#include "SCOMDef.h"
#include "SCOMBase.h"
#include "SCOM.h"
#include "ISCOMMalloc.h"
#include "../../kisrpc/rfcdef.h"
#include "kis/kpfw/kpfwsvr/iremotescommgr.h"


/**
	RPC���ú�SCOM���õ��������ڣ�
		RPC���÷��ص���RPC�����ָ�룬���ָ���ʵ�����ڵ������ڲ������ģ����Գ��˸�COM���÷�ʽ��ͬ��AddRef,Release����֮�⣬��ʹ�����Ӧ��delete��ָ�룬����ʹ������ָ���磺auto_ptr<IRpcHello> piHello;
*/
enum SCOM_EX_CREATE_TYPE
{
	SCOM_EX_CREATE_TYPE_RPC = 0,			//ͨ��RPC�ķ�ʽ���е���
	SCOM_EX_CREATE_TYPE_SCOM				//ͨ��������COM�ķ�ʽ���д���������ָ����ã��������ע�᱾������ϵ(��ֱ�ӵ���KSCoCreateInstance��ȣ�ֻ���������Զ����KSCoInitialize�Ķ���)
};

class SCOMAutoInit
{
public:
	SCOMAutoInit():m_bInited(FALSE){};

	~SCOMAutoInit()
	{
		KSCoUninitialize();
	};

	HRESULT init()
	{
		if (!m_bInited)
		{
			HRESULT hRes = E_FAIL;

			hRes = KSCoInitialize(NULL);

			if (SUCCEEDED(hRes))
				m_bInited = TRUE;

			return hRes;
		}
		
		return S_OK;
	}


	BOOL m_bInited;	
};

//Զ�̴��������Զ�������Ҫʵ��IManage�ӿڣ�������ͨ�����ṩ�ߵ�RPC��ʼ��
template<class I>
HRESULT __stdcall KSCoManagedCreateInstance(
	const KSCLSID& clsid,	//��Ҫ�����������ID
	I **ppv,
	const KSCLSID& callerClsid, //�����߱�������ID��������ڷ����ṩ���ڲ���GetCLSID()��õ�ǰ�����������ڽ�������ڵ��ÿ�ֱ�����һ����ֵKSCLSID()
	SCOM_EX_CREATE_TYPE createtype = SCOM_EX_CREATE_TYPE_RPC
	)
{
	
	HRESULT hRes = E_FAIL;

	static PipeEndpoint _endpoint((PTCHAR)KRpcName());
	static RcfClient<IRemoteSCOMMgr> rcSCOMMgr(_endpoint);
	static IRemoteSCOMMgr *piRemoteSCOMMgr = &rcSCOMMgr;
	static BOOL s_bLocalSCOMInited = FALSE;
	static DWORD s_dwCurPID = GetCurrentProcessId();

	if (createtype == SCOM_EX_CREATE_TYPE_RPC)
	{
		hRes = piRemoteSCOMMgr->CreateRemoteInstance(clsid, callerClsid, s_dwCurPID);
		if (SUCCEEDED(hRes))
		{
			RcfClient<I> *pClient = new RcfClient<I>(_endpoint);	

			*ppv = (I*)pClient;

			hRes = S_OK;

			goto Exit0;
		}
	}
	else if (createtype == SCOM_EX_CREATE_TYPE_SCOM)
	{//�����Ҫ�ڽ����ڴ���,��ȷ��SCOM�ѳ�ʼ��

		if (!s_bLocalSCOMInited)
		{
			static SCOMAutoInit scomAI;
			hRes = scomAI.init();

			if (SUCCEEDED(hRes))
				s_bLocalSCOMInited = TRUE;
			else
				goto Exit0;
		}

		//�����ڴ���SCOM���
		hRes = KSCoCreateInstance(clsid, __uuidof(I), (void**)ppv);
	}

Exit0:
	return hRes;
}


//Զ�̴��������Զ�������Ҫʵ��IManage�ӿڣ�������ͨ�����ṩ�ߵ�RPC��ʼ��
template<class I>
HRESULT __stdcall KSCoManagedCreateInstance(
	const KSCLSID& clsid,	//��Ҫ�����������ID
	auto_ptr<I>& rsp,
	const KSCLSID& callerClsid, //�����߱�������ID��������ڷ����ṩ���ڲ���GetCLSID()��õ�ǰ�����������ڽ�������ڵ��ÿ�ֱ�����һ����ֵKSCLSID()
	SCOM_EX_CREATE_TYPE createtype = SCOM_EX_CREATE_TYPE_RPC
	)
{
	HRESULT hResult = E_FAIL;
	I* pi = NULL;

	//��ʱֻ֧��RPC�ĵ��÷�ʽ
	if (createtype != SCOM_EX_CREATE_TYPE_RPC)
		return E_NOTIMPL;

	hResult = KSCoManagedCreateInstance(clsid, &pi, callerClsid, createtype);
	rsp.reset(pi);

	return hResult;
}


#endif //SCOMEXTAPI_H