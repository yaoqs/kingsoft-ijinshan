#pragma once
#include "arpcommondef.h"

class ArpConfig
{
public:
	ArpConfig(void);
	~ArpConfig(void);

	BOOL GetArpEnable();
	BOOL SetArpEnable(BOOL bValue);

	BOOL GetArpSafe();
	BOOL SetArpSafe(BOOL bSafe);

	BOOL GetArpSetting(BOOL& bBlockRecvAttack, BOOL& bBlockRecvIPAttack, BOOL& bBlockSendAttack);
	BOOL SetArpSetting(BOOL bBlockRecvAttack, BOOL bBlockRecvIPAttack, BOOL bBlockSendAttack);

	BOOL GetManualGateAddr(mac_ip*& pAddr, INT& nCnt);
	BOOL SetManualGateAddr(mac_ip* pAddr, INT nCnt);

	BOOL GetNotifyGateway(BOOL& bNotify, INT& nTimes );
	BOOL SetNotifyGateway(BOOL bNotify, INT nTimes);

	BOOL GetUseAutoGateAddr();
	BOOL SetUseAutoGateAddr(BOOL bEnable);

	BOOL ClearArpProtectList();

	BOOL Load();
	BOOL Save();

	BOOL m_nVer;

    // �Ƿ�����
	BOOL m_bEnable;

    // ��ȫģʽ
	BOOL m_bSafeMode;

    // ��ֹ���ڵ�ARP����
    BOOL m_bBlockRecvAttack;
    // ��ֹ���ڵ�IP��ͻ
    BOOL m_bBlockRecvIPAttack;
    // ��ֹ�����ARP����
    BOOL m_bBlockSendAttack;

    // ֪ͨ����
	BOOL m_bNotifyGw;
	BOOL m_bAutoGate;
	INT m_nTimes;
	list<mac_ip> m_pMacIpList;
};
