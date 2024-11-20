///////////////////////////////////////////////////////////////	
//	
// FileName  :  kapplogadapter.cpp
// Creator   :  yangzhenhui@kingsoft.com
// Date    	 :  2009-12-21  14:17
// Comment   :  
//
///////////////////////////////////////////////////////////////	
#include "StdAfx.h"
#include "kapplogadapter.h"

KAppLogAdapter::KAppLogAdapter(	
	ULONG uAppModuleId, 
	ULONG nRequestProtocol, // PROTO_TYPE
	ULONG nRequestType,		// APP_REQUEST_TYPE
	ULONG uLocalIP,
	USHORT uLocalPort,
	ULONG uRemoteIP,
	USHORT uRemotePort,
	GUID  guidRule,
	ULONG uTrustResult, 
	ULONG uResult,
	ULONG uParentModuleId,
	ULONG uStackModuleId )
{
	m_appLog.m_uAppModuleId = uAppModuleId;
	m_appLog.m_uTrustResult = uTrustResult;		//������֤���
	m_appLog.m_nRequestProtocol = nRequestProtocol; // PROTO_TYPE
	m_appLog.m_nRequestType = nRequestType;		// APP_REQUEST_TYPE
	m_appLog.m_uLocalIP = uLocalIP;			//����IP
	m_appLog.m_uLocalPort = uLocalPort;		//���ض˿�	
	m_appLog.m_uRemoteIP = uRemoteIP;		//Ŀ��IP
	m_appLog.m_uRemotePort = uRemotePort;		//Ŀ��˿�	
	m_appLog.m_guidRule = guidRule;			//ƥ�����GUID
	m_appLog.m_uResult = uResult;			//������
	m_appLog.m_uParentModuleId = uParentModuleId;	//������·��
	m_appLog.m_uStackModuleId = uStackModuleId;	//��ջģ��·��
}

//////////////////////////////////////////////////////////////////////////

KAppLogAdapter::~KAppLogAdapter(void)
{
}

//////////////////////////////////////////////////////////////////////////

BOOL KAppLogAdapter::Do( ILogMgr *logMgr )
{
	BOOL bResult = FALSE;

	do 
	{
		if( logMgr == NULL )
			break;

		logMgr->AddRef();
		logMgr->AddLog( LOG_TYPE_APP, (BYTE*)&m_appLog, sizeof(m_appLog) );

	} while (FALSE);

	if( logMgr != NULL )
		logMgr->Release();

	return TRUE;
}
