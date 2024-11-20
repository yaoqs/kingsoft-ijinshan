///////////////////////////////////////////////////////////////	
//	
// FileName  :  kpfwlogdef.h
// Creator   :  yangzhenhui@kingsoft.com
// Date    	 :  2009-12-23  14:23
// Comment   :  
//
///////////////////////////////////////////////////////////////	
#pragma once
#define MD5_LENGTH 16

#pragma pack(push, 1)

typedef struct tagMODULE_LOG
{
	ULONG m_uModuleId;
	WCHAR m_wsModulePath[MAX_PATH];
	UCHAR m_byMd5[MD5_LENGTH];
}MODULE_LOG, *PMODULE_LOG;


typedef struct tagLANMAN_LOG
{
	ULONG m_uAppModuleId;
	WCHAR m_wsLanmanPath[MAX_PATH];
	ULONG m_uTrustResult;
	ULONG m_uResult;
	ULONG m_uParentModuleId;
	ULONG m_uStackModuleId;
}LANMAN_LOG, *PLANMAN_LOG;


typedef struct tagAPP_LOG
{
	ULONG m_uAppModuleId;		//Ӧ�ó���·��	
	ULONG m_uTrustResult;		//������֤���
	ULONG m_nRequestProtocol; // PROTO_TYPE
	ULONG m_nRequestType;		// APP_REQUEST_TYPE
	ULONG m_uLocalIP;			//����IP
	USHORT m_uLocalPort;		//���ض˿�	
	ULONG m_uRemoteIP;		//Ŀ��IP
	USHORT m_uRemotePort;		//Ŀ��˿�	
	GUID  m_guidRule;			//ƥ�����GUID
	ULONG m_uResult;			//������
	ULONG m_uParentModuleId;	//������·��
	ULONG m_uStackModuleId;	//��ջģ��·��
}APP_LOG,*PAPP_LOG;

typedef struct tagHTTP_LOG
{
	ULONG m_uAppModuleId;		//Ӧ�ó���·��	
	char m_szUrl[MAX_URL_LENGTH+MAX_HOST_LENGTH];
}HTTP_LOG,*PHTTP_LOG;

typedef struct tagPE_LOG
{
	ULONG m_uAppModuleId;		//Ӧ�ó���·��
	WCHAR m_wsModulePath[MAX_PATH];
	char m_szUrl[MAX_URL_LENGTH];
}PE_LOG,*PPE_LOG;

//////////////////////////////////////////////////////////////////////////

typedef struct tagARP_LOG
{
	ULONG uAttackType;
	ULONG nCount;
	PACKET_DIR byDirection;
	ARP_EXTRA_DATA pArpData;
}ARP_LOG,*PARP_LOG;

typedef struct tagIP_LOG
{
	WCHAR ruleName[32];
	LOG_IP_RULE logIpRule;
}IP_LOG, *PIP_LOG;

typedef struct tagANTI_SCAN
{
	ULONG byProtocolType;
	ULONG uLocalIp;
	USHORT uLocalPort;
	ULONG uRemoteIp;
	USHORT uRemotePort;
	ULONG uCount;
}ANTI_SCAN_LOG, *PANTI_SCAN_LOG;

#pragma pack(pop)