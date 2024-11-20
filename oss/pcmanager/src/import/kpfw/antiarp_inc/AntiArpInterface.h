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
#include "pkthdr.h"


typedef BOOL(__stdcall * pfnIsDriverInstalled)();
typedef BOOL(__stdcall * pfnInstallDriver)(BOOL);
typedef BOOL(__stdcall * pfnUninstallDriver)();

#define FUNCNAME_ISDRIVERINSTALLED  _T("IsDriverInstalled")
#define FUNCNAME_INSTALLDRIVER      _T("InstallDriver")
#define FUNCNAME_UNINSTALLDRIVER    _T("UninstallDriver")


class IAntiArpCallback
{
public:
    virtual void __stdcall BlockSendArpPacket(p_block_arp_packet)   = 0;
    virtual void __stdcall BlockSendIpArpPacket(p_block_arp_packet) = 0;

    virtual void __stdcall BlockReceiveArpPacket(p_block_arp_packet)   = 0;
    virtual void __stdcall BlockReceiveIpArpPacket(p_block_arp_packet) = 0;


    virtual void __stdcall StatusChanged(int nStatus ) = 0;
};


extern const GUID CLSID_IANTIARPDEVC;

struct __declspec( uuid( "B6119EFE-365B-4a23-8D83-07776FFA069D" ) )
IAntiArpDevC : public IUnknown
{
    virtual BOOL __stdcall InitDevC() = 0;
    virtual void __stdcall UninitDevC() = 0;

    virtual unsigned int __stdcall GetDriverVersion() = 0;
    virtual unsigned int __stdcall GetDllVersion() = 0;

    virtual int  __stdcall GetStatus() = 0;
    virtual BOOL __stdcall SetStatus( int nStatus) = 0;

    
    virtual BOOL __stdcall SetAntiArpConfig(p_antiarp_config p_config) = 0;
    virtual BOOL __stdcall SetAntiArpProtectList(p_protect_addr plist, int ncount) = 0;
    
    virtual BOOL __stdcall SendArpPacket( PARPPACKET p_arp_packet ) = 0;



    virtual BOOL __stdcall StartSendPacket(DWORD dwSecCount, DWORD dwSec, PARPPACKET p_packet, /* max = 10*/int nCount) = 0;
    virtual void __stdcall StopSendPacket() = 0;


    virtual BOOL __stdcall GetMacInfo( p_mac_ip pmacip, char* szhostname, int nsize) = 0;

    virtual void __stdcall SetCallback(IAntiArpCallback* piCallback) = 0;

    virtual BOOL __stdcall IpToMac(p_mac_ip pmacip, BOOL bTrueIp) = 0;

    virtual BOOL __stdcall IsDriverInstalled() = 0;
};


typedef struct differentMAC 
{
	unsigned int ip;
	unsigned char OldMac[6];
	unsigned char NewMac[6];
}DifferentMac, *PDifferentMac;

class IDifferentMacCallback
{
public:

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
	virtual void __stdcall DifferentNetCard(/*[in, out]*/mac_ip*, 
											/*[out]*/ size_t, 
											/*[in, out]*/mac_ip*,
                                            /*[out]*/ size_t) = 0;

};


extern const GUID CLSID_IARPTABLESAFEGUARD;

struct __declspec(uuid("C3E6C94F-A3ED-4ea6-80AD-1EABF140330D"))
IArpTableSafeguard : public IUnknown
{
	virtual int __stdcall UnInit() = 0;

	virtual void __stdcall InitTable(IDifferentMacCallback* piDiffMacFunc) = 0;

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

};



