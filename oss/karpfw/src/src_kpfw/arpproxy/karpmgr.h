#pragma once
#include "KASAntiArpDevC.h"
#include "arpconfig.h"
#include "txtlog.h"


class KArpInfo:public IAntiArpCallback
{
public:
	KArpInfo();
	~KArpInfo();
	virtual STDMETHODIMP Initialize();
	virtual STDMETHODIMP UnInitialize();

	HRESULT GetHostInfo (KArpHostInfo*);
	HRESULT Ping(ATL::CString);

	// ����arp����ǽ
	HRESULT GetEnable (BOOL*);
	HRESULT SetEnable (BOOL);

	// ʹ���ֶ����õ����ػ����Զ���ȡ����
	HRESULT GetAutoGateWay (BOOL*, vector<mac_ip>*);
	HRESULT SetAutoGateWay (BOOL,  vector<mac_ip>*);
	HRESULT GetMacFromIp   (mac_ip*);

	//arp �߼�����
	HRESULT	GetNotifyGateway(BOOL& bNotifyGw, INT& nTimes);
	HRESULT	SetNotifyGateway(BOOL bNotifyGw, INT nTimes);

	HRESULT	GetAdvSetting(BOOL& bSafeMode, BOOL& bBlockRecvAttack, BOOL& bBlockRecvIPAttack, BOOL& bBlockSendAttack);
	HRESULT	SetAdvSetting(BOOL bSafeMode, BOOL bBlockRecvAttack, BOOL bBlockRecvIPAttack, BOOL bBlockSendAttack);

	HRESULT	Refresh();
	//IP��������
	void __stdcall IpLog( PLOG_IP_RULE pIpRule );
	void __stdcall RasEvent( PRAS_CONNECTION pRasConn )
	{
	}

    void GetLastLog(std::string& strLog);
	BOOL ApplySetting();
	void DelArpCache();
    void ClearProtectList();

private:
	BOOL StartArp();
	void StopArp();
	BOOL UpdateArpConfig();
	void DeleteAllArpEntry();
	BOOL SetAntiArpProtectList();
	BOOL IpToMac(mac_ip* pAddr, long hostip = 0, int nTryCount = 5);

	IAntiArpDevC* GetAntiArpDevC();
	ArpConfig* GetNetConfig();
	KArpHostInfo m_hostInfo;
	IAntiArpDevC* m_arpDevc;
	ArpConfig m_arpConfig;
	CTxtLog m_txtLog;
	ULONG m_uAdapterCount;
	ADAPTER_INFO*	m_pAdaterInfos;
};