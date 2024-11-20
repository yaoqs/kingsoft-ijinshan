/********************************************************************
* CreatedOn: 2007-10-12   15:45
* FileName: commondef.h
* CreatedBy: lidengwang <lidengwang@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL:  $
* Purpose:
*********************************************************************/


#ifndef __COMMONDEF_H__
#define __COMMONDEF_H__


#define  ANTIARP_DRIVER_VERSION_1      (1)
#define  ANTIARP_DRIVER_VERSION_2      (2)
#define  ANTIARP_DRIVER_VERSION_3      (3)
#define  ANTIARP_DRIVER_VERSION_4      (4)

#define KFW_NIDS_MAJOR_VER		1
#define KFW_NIDS_MINOR_VER		0

#define KNDISFLT_DEVICE_NAME_A       "KNdisFlt"
#define KNDISFLT_NT_DEVICE_NAME_A    "\\Device\\KNdisFlt"
#define KNDISFLT_DOS_DEVICE_NAME_A   "\\DosDevices\\Global\\KNdisFlt"


#define KNDISFLT_DEVICE_NAME         L"KNdisFlt"
#define KNDISFLT_NT_DEVICE_NAME      L"\\Device\\KNdisFlt"
#define KNDISFLT_DOS_DEVICE_NAME     L"\\DosDevices\\Global\\KNdisFlt"


#define max_hostip_count  (10 )
#define max_filter_count  (512)


#pragma pack(push, 1)

typedef struct _mac_ip
{
    unsigned char mac[6];
    unsigned int  ip;

}mac_ip, *p_mac_ip;


//////////////////////////////////////////////////////////////////////////
//
//   ���ýṹ��
//
//////////////////////////////////////////////////////////////////////////
typedef struct _antiarp_config
{

	unsigned short cb;
	unsigned char b_block_in_arp_attack;            // ���ؽ����ⲿARP����
	unsigned char b_block_in_ip_attack;             // ���ؽ����ⲿIP��ͻ����

	unsigned char b_block_out_arp_attack;           // �������ⷢ��ARP����
	unsigned char b_block_out_ip_attack;            // �������ⷢ��IP��ͻ����

	unsigned char b_safe_mode;                      // ��ȫģʽ
	unsigned char b_enable;							// ����

}antiarp_config, *p_antiarp_config;

//////////////////////////////////////////////////////////////////////////
//
//   ������IP��MAC�б�
//
//////////////////////////////////////////////////////////////////////////

typedef struct _protect_addr
{
    mac_ip addr;
    unsigned char bgateway;
}protect_addr, *p_protect_addr;

typedef struct _antiarp_protect_ipmac_list
{
    unsigned int n_list_count;
    protect_addr addr_list[1];

}antiarp_protect_ipmac_list, *p_antiarp_protect_ipmac_list;


//////////////////////////////////////////////////////////////////////////
//
//   ֪ͨ���¼��б�
//
//////////////////////////////////////////////////////////////////////////
typedef struct _antiarp_config_event
{
	HANDLE	m_hCommSemaphore;
	USHORT  m_uMarVer;
	USHORT  m_uMinVer;
}antiarp_config_event, *p_antiarp_config_event;



#pragma pack(pop)


#define status_invalid      (0)
#define status_stop         (1)
#define status_running      (2)
#define status_reset        (3)

#endif
