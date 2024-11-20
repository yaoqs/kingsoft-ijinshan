/********************************************************************
* CreatedOn: 2007-10-17   11:01
* FileName: AntiArpInterface.h
* CreatedBy: lidengwang <lidengwang@kingsoft.net> & lvweili
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL:  $
* Purpose:
*********************************************************************/


#pragma once

#include "arpcommondef.h"
#include "../netwatch.h"



extern const __declspec(selectany) GUID CLSID_IArpInstaller = 
{ 0x9f4fa832, 0x9d01, 0x4e47, { 0x84, 0xbc, 0xc9, 0x58, 0x26, 0x77, 0x5e, 0x79 } };

[
	uuid({9F4FA832-9D01-4e47-84BC-C95826775E79})
]
interface IArpInstaller : IUnknown
{
	virtual STDMETHODIMP Install(
		VOID
		) = 0;

	virtual STDMETHODIMP UnInstall(
		VOID
		) = 0;

	virtual STDMETHODIMP SetConfig( 
		DWORD dwEnableFlag, 
		DWORD dwRequestFlag 
		) = 0;

	virtual STDMETHODIMP IsRuning(
		BOOL* bRuning
		) = 0;
};

//////////////////////////////////////////////////////////////////////////

interface IAntiArpCallback
{
	virtual STDMETHODIMP Initialize() = 0;
	virtual STDMETHODIMP UnInitialize() = 0;
	virtual void __stdcall IpLog( PLOG_IP_RULE pIpRule ) = 0;
	virtual void __stdcall RasEvent( PRAS_CONNECTION pRasConn ) = 0;
};

//////////////////////////////////////////////////////////////////////////

extern const __declspec(selectany) GUID CLSID_IANTIARPDEVC = 
{ 0xb6119efe, 0x365b, 0x4a23, { 0x8d, 0x83, 0x7, 0x77, 0x6f, 0xfa, 0x6, 0x9d } };

[
	uuid({B6119EFE-365B-4a23-8D83-07776FFA069D})
]
interface IAntiArpDevC : public IUnknown
{
	virtual STDMETHODIMP_(BOOL) InitDevC() = 0;
	virtual STDMETHODIMP_(VOID) UninitDevC() = 0;

	virtual STDMETHODIMP_(BOOL) GetKfwState( __out ARP_STATE *arpState ) = 0; 
	virtual STDMETHODIMP_(VOID) SetCallback( __in IAntiArpCallback * pCallback ) = 0;
	virtual STDMETHODIMP_(BOOL) SetModuleFlag( __in ULONG uFlag ) = 0; 
	virtual STDMETHODIMP_(BOOL) SetLogFlag( __in ULONG uFlag ) = 0;
	virtual STDMETHODIMP_(BOOL) EnableNetwork( __in BOOL bEnable ) = 0; 

	virtual STDMETHODIMP_(BOOL) SetArpProtectList( p_mac_ip plist, int ncount ) = 0;
	virtual STDMETHODIMP_(BOOL) ClearArpProtectList() = 0;
	virtual STDMETHODIMP_(BOOL) SetArpBlockFlag( ULONG uFlag ) = 0;
	
	virtual STDMETHODIMP_(BOOL) AddIpRules( __in KIP_FILTER_INFO* pIpFilterInfo, ULONG dwFilterCount ) = 0;
	virtual STDMETHODIMP_(BOOL) RemoveIpRule( GUID ruleId ) = 0;
	virtual STDMETHODIMP_(BOOL) RemoveAllIpRules() = 0;

	virtual STDMETHODIMP_(BOOL) AddAdvFilter( __in KPackTemplate *pPackTemplate, ULONG uTemplateLen ) = 0;
	virtual STDMETHODIMP_(BOOL) RemoveAdvFilter( GUID ruleId ) = 0;
	virtual STDMETHODIMP_(BOOL) RemoveAllAdvFilter() = 0;
	
	virtual STDMETHODIMP_(int) GetAdapter( __out ADAPTER_INFO* pAdpaterList, __in int nCount ) = 0;
	virtual STDMETHODIMP_(BOOL) SetNotifyTimer( __in ULONG uTimer ) = 0;
	virtual STDMETHODIMP_(BOOL) SetPassGuid( __in GUID guidPass ) = 0;
	virtual STDMETHODIMP_(int) GetRasConnection( __out PRAS_CONNECTION pRasConnection, __in int nCount ) = 0;

    virtual STDMETHODIMP_(BOOL) SelectGatewayMac() = 0;
    virtual STDMETHODIMP_(BOOL) CleanGatewayMac() = 0;
};


typedef struct differentMAC 
{
	unsigned int ip;
	unsigned char OldMac[6];
	unsigned char NewMac[6];
}DifferentMac, *PDifferentMac;

interface IKAdapter
{
	virtual ULONG  GetHostIp()		PURE;

	virtual BYTE*  GetHostMac()		PURE;

	virtual ULONG  GetGatewayIp()		PURE;

	virtual BYTE*  GetGatewayMac()		PURE;

	virtual BOOL IsWirelessAdapter()		PURE;

	virtual	LPCWSTR GetConnID()				PURE;

	virtual	LPCWSTR	GetGateName()			PURE;

	virtual	ULONG	GetIndex()			PURE;

	virtual	BOOL	IsAdapterConnected()			PURE;
};

interface IKAdapterColl
{
	virtual INT		GetAdapterCnt()		PURE;

	virtual IKAdapter* GetAdapter(INT i)		PURE;
};

interface IDifferentMacCallback
{

// -------------------------------------------------------------------------
// ����		: __stdcall differentMac
// ����		: ��������ı仯
// ����ֵ	: virtual void 
// ����		: PDifferentMac
// ��ע		: 
// -------------------------------------------------------------------------
	virtual void __stdcall differentMac( PDifferentMac ) = 0;

// -------------------------------------------------------------------------
// ����		: __stdcall DifferentNetCard
// ����		: ������������صı仯
// ����ֵ	: virtual void 
// ����		: /*[in��out]*/mac_ip*
// ����		: /*[out]*/ size_t
// ����		: /*[in��out]*/unsigned int
// ��ע		: 
// -------------------------------------------------------------------------
	virtual void __stdcall DifferentNetCard(IKAdapterColl* pAdapterColl) = 0;

};


extern const GUID CLSID_IARPTABLESAFEGUARD;
interface IAntiArpDevC;

struct __declspec(uuid("C3E6C94F-A3ED-4ea6-80AD-1EABF140330D"))
IArpTableSafeguard : public IUnknown
{
	virtual int __stdcall UnInit() = 0;

	virtual void __stdcall InitTable(IDifferentMacCallback* piDiffMacFunc, IAntiArpDevC* pArpDriver) = 0;

	virtual BOOL __stdcall UpdateAdapterInfo() = 0;

	virtual IKAdapterColl* __stdcall GetAdapterColl() = 0;

	virtual void __stdcall Lock() = 0;

	virtual void __stdcall Unlock() = 0;

	virtual int __stdcall InitTableFromSys(IDifferentMacCallback* piDiffMacFunc) = 0;

// -------------------------------------------------------------------------
// ����		: __stdcall Get_IPMAC_Info
// ����		: 
// ����ֵ	: virtual int 
// ����		: /*[in, out]*/_mac_ip* LocalArray ����������Ϣ
// ����		: /*[in��out]*/int* nArrSize ����������Ŀ
// ����		: /*[in��out]*/_mac_ip* Gateway ����
// ��ע		: ������������˻��棬����SendARP()
// -------------------------------------------------------------------------
	virtual int __stdcall Get_IPMAC_Info(/*[in, out]*/_mac_ip* pLocalArray, 
										 /*[in, out]*/ int* nLocalArraySize, 
										 /*[in, out]*/_mac_ip* pGateway,
                                         /*[in, out]*/ int* nGatewaySize) = 0;

// -------------------------------------------------------------------------
// ����		: __stdcall ModifyState
// ����		: ��̬��
// ����ֵ	: virtual int 
// ����		: /*[in]*/_mac_ip* IpMacItem 
// ����		: DWORD dwType 
// ��ע		: // dwType: Static == 4; Dynamic == 3; Invalid == 2; Other == 1
// -------------------------------------------------------------------------
	virtual int __stdcall ModifyState(/*[in]*/_mac_ip* IpMacItem, DWORD dwType) = 0;
	
	virtual int __stdcall AddItem(/*[in]*/_mac_ip* IpMacItem) = 0;

	virtual int __stdcall JudgeIp(/*[in]*/_mac_ip* IpMacItem) = 0;

// -------------------------------------------------------------------------
// ����		: __stdcall DeleteARPBuff
// ����		: ��ջ���
// ����ֵ	: virtual int 
// ��ע		: ��FlushIpNetTable()��û��DeleteIpNetEntry()
// -------------------------------------------------------------------------
	virtual int __stdcall DeleteARPBuff() = 0;

	virtual int __stdcall StartLookTableThread(size_t nFrequence) = 0;

	virtual int __stdcall EndLookTableTread() = 0;

// -------------------------------------------------------------------------
// ����		: __stdcall StartLookNetCardThread
// ����		: �����̣߳�������������صı仯
// ����ֵ	: virtual int 
// ����		: size_t nFrequence
// ��ע		: ����б仯�����ûص�DifferentNetCard()
// -------------------------------------------------------------------------
	virtual int __stdcall StartLookNetCardThread(size_t nFrequence) = 0;

	virtual int __stdcall EndLookNetCardTread() = 0;

	virtual int __stdcall FromIpToMac(unsigned int unGatewayIp, unsigned int unLocalIp, unsigned char* szMac) = 0;

};


extern const __declspec(selectany) GUID CLSID_IKARPSP = 
{ 0xe39515be, 0x65fa, 0x4df2, { 0xb1, 0x88, 0x1d, 0xe5, 0x7e, 0x2c, 0xd5, 0xfa } };

[
	uuid({E39515BE-65FA-4df2-B188-1DE57E2CD5FA})
]
interface IKArpSp : public IUnknown
{
	virtual STDMETHODIMP_(int) 	Start()			PURE;
	virtual STDMETHODIMP_(int) 	Stop()			PURE;
};