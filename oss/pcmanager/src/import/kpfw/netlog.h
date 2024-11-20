////////////////////////////////////////////////////////////////////////////////
//      
//      common include File for kpfw
//      
//      File      : netlog.h
//      Version   : 1.0
//      Comment   : ��������������־��ؽṹ
//      
//      Create at : 2008-7-21
//      Create by : liupeng
//      
////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "netwatch.h"
#include <string>

#define KIS_LOG_CATCNT					10

#define	KPFW_LOG_BUFFER_SIZE			1024*64

//////////////////////////////////////////////////////////////////////////
// ���������־����
enum 
{
	kis_log_kpfw_ip				= 1,				// ip������
	kis_log_kpfw_appvisit		= 2,				// Ӧ�ó����������
	kis_log_kpfw_arp			= 3,				// arp����ǽ������Ϣ
	kis_log_kpfw_apprule		= 4,				// Ӧ�ó�����������־
	kis_log_kpfw_iprule			= 5,				// ip���������־
	kis_log_kpfw_area			= 6,				// �����������־
	kis_log_kpfw_opt			= 7,				// �û����������־
	kis_log_kpfw_debug			= 8,				// debug ��־				
	kis_log_kpfw_update			= 9,				// ������־
	kis_log_kpfw_sheid			= 10,				// ��̬��������
};

// Ӧ�ó������������־��¼
typedef enum enAppLogFlag
{
	enumALF_Unknown				= 0,				// δ֪����

	enumALF_Allow_Appfail		= 1,				// ���ڳ���,�Զ�����
	enumALF_Allow_Popfail		= 2,				// ���ݵ���ʧ��, �Զ������������(�����ǲ���)
	enumALF_Deny_Popfail		= 3,

	enumALF_Port_Deny			= 4,				// Ӧ�ó���˿ڱ���ֹ
	enumALF_Rule_Deny			= 5,				// �Ƿ�����Ϊexe����ֹ��������

	enumALF_Allow_Trust			= 6,				// ��ģ����Ҫ���п�����֤����������ģ��ͨ���˿�����֤,�Զ������������

	enumALF_Allow_Pop			= 7,				// �Ƿ����Զ��ж�Ϊ�����������û���pop��ѡ��������

	enumALF_Pop_Deny			= 8,				// �Ƿ����û���pop��ѡ��deny

	enumALF_Allow_Rule			= 9,				// ����������类����

	enumALF_Allow_Auto			= 10,
}AppLogFlag;

// Ӧ�ó�����򴴽���־��¼
typedef enum enAppRulLogeFlag
{
	enumARLF_Unknown			= 0,				// δ֪����

	enumARLF_Rule_Add			= 1,				// �������

	enumARLF_Rule_Delete		= 2,				// ����ɾ��

	enumARLF_Rule_Update		= 3,				// �����޸�
}AppRuleLogFlag;

// Ӧ�ó����û�������־

typedef enum tagLogUserOptFlag
{
	enumLUO_Open				= 1,				//����
	enumLUO_Close				= 2,				//�ر�
}LogUserOpt;

typedef enum tagLogOptTypeFlag
{
	enumLOT_FireWall			= 1,				//����ǽ
	enumLOT_NetWork				= 2,				//����
}LogOptType;


//���������־

typedef enum tagAreaLogOptFlag
{
	enumAL_SwitchArea			= 1,
	enumAL_ModifyInfo			= 2,
	enumAL_NewArea				= 3,
	enumAL_FindNewArea			= 3,
}AreaLogOpt;

typedef enum tagBehaviorType
{
	enumBT_AccessNet			= 1,
	enumBT_ToBeService			= 2
}BehaviorType;

//////////////////////////////////////////////////////////////////////////
// arp����ǽ��־
typedef enum tagArpAttackType
{
	em_Send_Arp				= 1,			// ��������arp����
	em_Send_IpArp			= 2,			// �������͵�ip��ͻ����
	em_Recieve_Arp			= 3,			// ���յ�arp����
	em_Recieve_IpArp		= 4,			// ���յ���ip��ͻ����
}ArpAttackType;

struct KpfwLogHeader
{
	DWORD		nSize;
	DWORD		nType;
	ULONGLONG	nID;
};

struct KpfwLogContent 
{
	__time64_t		eventTime;
	std::wstring	strInfo;
	std::wstring	strResult;
	INT				nID;
};

//��Ҫ�޸Ľ�����Ա����˳�򣬷���ҲҪ�޸� ToBuffer FromBuffer
struct KpfwLog
{
	int				nID;			// ����ID
	int				nType;			// ��־����
	int				nSize;			// sizeof(int) * 3 + strData.length ���ǹ������ݳ���
	std::string		strData;		// �ַ�������

	void ToBuffer( BYTE* const buffer, int nLen )
	{
		if ( nLen != sizeof( int ) * 3 + strData.length() )
			return;

		if ( buffer )
		{
			memcpy( buffer, &nID, sizeof(int) );
			memcpy( buffer + sizeof(int) * 1,	&nType, sizeof(int) );
			memcpy( buffer + sizeof(int) * 2, &nSize, sizeof(int) );
			memcpy( buffer + sizeof(int) * 3, strData.c_str(), strData.length() );
		}

		return;
	}

	BOOL FromBuffer( BYTE* pBuffer )
	{
		memcpy( &nID,		pBuffer, sizeof(int) );
		memcpy( &nType,		pBuffer + sizeof(int) * 1, sizeof(int) );
		memcpy( &nSize,		pBuffer + sizeof(int) * 2, sizeof(int) );

		if ( !CheckLogType( nType ) )
			return FALSE;
		else
		{
			std::string strTemp( (char*) pBuffer + sizeof(int) * 3, nSize - sizeof(int) * 3 );
			strData = strTemp;
		}
		return TRUE;
	}

	BOOL CheckLogType( int nType )
	{
		BOOL bRetCode = FALSE;
		switch( nType )
		{
		case kis_log_kpfw_ip:
		case kis_log_kpfw_appvisit:
		case kis_log_kpfw_arp:
		case kis_log_kpfw_apprule:
		case kis_log_kpfw_iprule:
		case kis_log_kpfw_area:
		case kis_log_kpfw_opt:
		case kis_log_kpfw_debug:
		case kis_log_kpfw_update:
		case kis_log_kpfw_sheid:
			bRetCode = TRUE;
			break;
		default:
			bRetCode = FALSE;
			break;
		}
		return bRetCode;
	}

};

//////////////////////////////////////////////////////////////////////////
struct ARP_LOG_STASTIC
{
	ULONG					m_nAttackCnt;
	ULONG					m_lastAttackerIp;
};

struct ADVFILTER_LOG_STASTIC
{
	ULONG					m_nAttackCnt;
	GUID					m_lastAttackType;
};

struct DYN_ATTACK_LOG_STASTIC
{
	ULONG					m_nAttackCnt;
	ULONG					m_lastAttackerIp;
};

struct APPRULE_LOG_STASTIC
{
	ULONG					m_nModifyCnt;
	WCHAR					m_lastRulePath[MAX_PATH];
};

struct APPBLOCK_LOG_STASTIC
{
	ULONG					m_nBlockCnt;
	WCHAR					m_lastBlockExePath[MAX_PATH];
	ULONG					m_lastBlockReason;
};

struct NETMON_LOG_STASTIC
{
	ARP_LOG_STASTIC			m_arpLog;
	ADVFILTER_LOG_STASTIC	m_advFltLog;
	DYN_ATTACK_LOG_STASTIC	m_dynAttackLog;
	APPRULE_LOG_STASTIC		m_appRuleLog;
	APPBLOCK_LOG_STASTIC	m_appBlockLog;
};

//////////////////////////////////////////////////////////////////////////
// �Զ�����Ӧ�ó������
struct LOG_CREATE_APP_RULE: KpfwLogHeader
{
	
};

#define KPFW_LOGBUF_64KB	1024 * 64
