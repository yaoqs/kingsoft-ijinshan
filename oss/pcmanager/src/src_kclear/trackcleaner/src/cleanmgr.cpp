// CleanMgr.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "CleanManager.h"
#include "CleanProc.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

HINSTANCE g_hInstance;


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	g_hInstance = hModule;
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

CCleanManager			g_cm;
CKClearProc				g_kc;

HRESULT CreateCleanMgrObject( REFIID riid, void** ppvObj )
{
	ATLASSERT(ppvObj);
	
	if ( IsEqualIID(riid, __uuidof(ICleanMgr)) )
	{
		ICleanMgr *p = &g_cm;
		*ppvObj = p;
		return S_OK;
	}
	

	if ( IsEqualIID(riid, __uuidof(IKClearProc)) )
	{	
		//���ûص�ָ��
		g_cm.SetSoftInfoCallBack(g_kc.SoftInfoCallBack,&g_kc);
		//��ȡ��Ϣ
		g_cm.LoadTreetruct(_T(""));

		IKClearProc *p = &g_kc;
		*ppvObj = p;
		return S_OK;
	}
	return E_NOINTERFACE;
}
