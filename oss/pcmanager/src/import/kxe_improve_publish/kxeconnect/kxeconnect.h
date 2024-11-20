//////////////////////////////////////////////////////////////////////
///		@file		kxeconnect.h
///		@author		luopeng
///		@date		2008-11-12 9:07:58
///
///		@brief		����������ط�װ
//////////////////////////////////////////////////////////////////////

#pragma once
#include <windows.h>

/**
* @defgroup kxeconnect_interface_group KXEngine Architecture Network Interface
* @{
*/

/// ���ڱ�ʾһ�����ӵ����ݽṹ
typedef struct tagMIB_TCPEXROW{
	DWORD dwState;      ///< state of the connection,�μ�MIB_TCP_STATE_*�ĺ궨��
	DWORD dwLocalAddr;  ///< address on local computer
	DWORD dwLocalPort;  ///< port number on local computer
	DWORD dwRemoteAddr; ///< address on remote computer
	DWORD dwRemotePort; ///< port number on remote computer
	DWORD dwProcessId;
} MIB_TCPEXROW, *PMIB_TCPEXROW;

/// �ڻ�ȡ�ܵ�����ʱ���õı��ṹ
typedef struct tagMIB_TCPEXTABLE{
	DWORD dwNumEntries;
	MIB_TCPEXROW table[1];
} MIB_TCPEXTABLE, *PMIB_TCPEXTABLE;

/// �������Ѿ��ر�
#define MIB_TCP_STATE_CLOSED       1

/// �����Ӵ��ڼ���״̬
#define MIB_TCP_STATE_LISTEN       2

/// �������Ѿ�SYN_SENT
#define MIB_TCP_STATE_SYN_SENT     3

/// �������Ѿ�SYN_RCVD
#define MIB_TCP_STATE_SYN_RCVD     4

/// �������Ѿ�����
#define MIB_TCP_STATE_ESTAB        5

/// �������Ѿ�FIN_WAIT1
#define MIB_TCP_STATE_FIN_WAIT1    6

/// �������Ѿ�FIN_WAIT2
#define MIB_TCP_STATE_FIN_WAIT2    7

/// �������Ѿ�CLOSE_WAIT
#define MIB_TCP_STATE_CLOSE_WAIT   8

/// ������CLOSEING
#define MIB_TCP_STATE_CLOSING      9

/// ������LAST_ACK
#define MIB_TCP_STATE_LAST_ACK     10

/// �������Ѿ�TIME_WAIT
#define MIB_TCP_STATE_TIME_WAIT    11

/// �������Ѿ�DELETE_TCB
#define MIB_TCP_STATE_DELETE_TCB   12
/**
 * @brief ��ȡ����ǰ���ӵ����н�����ص���Ϣ
 * @param[out] ppTcpTable ��ȡ������Ϣ,�ɺ����ڲ������ڴ�
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int KxEGetExtendTcpTable(MIB_TCPEXTABLE** ppTcpTable);

/**
 * @brief �ͷŻ�ȡ����table�б�
 * @param[in] pTcpTable ͨ��KxEGetExtendTcpTable��ȡ���б�
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int KxEFreeExtendTcpTable(MIB_TCPEXTABLE* pTcpTable);

#include "kxeconnect.inl"

/**
 * @}
 */
