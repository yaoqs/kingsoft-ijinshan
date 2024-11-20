// dummyz@126.com

#pragma once

#include <PshPack4.h>
#include "safemonitor.h"

#define SAFEMONITOR_EVENT_VER				2 // ���event��Ա�ı䣬Ϊ�˱���汾��һ�£���Ҫ�����˰汾

//////////////////////////////////////////////////////////////////////////
// CSafeMonitorEvent
class CSafeMonitorEvent
{
public:
	DWORD	dwMonitorId;
	DWORD	dwCtrl; // ���ƽ��
	DWORD	dwClean; // ������

	SM_FILE_ENGINE	dwFileEngine;	// ���������
	DWORD	dwFileType;		// �ļ�����, ��������ȫ��δ֪
	LPCTSTR	lpFilePath;		// �ļ�·��, ֻ�����ļ�·��
	LPCTSTR	lpVirusName;	// ����ǲ���������Ϊ��������, ����Ϊ�������
	DWORD	dwVirusID;		// ���� ID
	BOOL    bAuto; // �Ƿ��Զ�����
	
public:
	virtual CSafeMonitorEvent* Clone() = 0;
	virtual void Destroy() = 0;

protected:
	void CloneTo(CSafeMonitorEvent* lpDst);
	void OnlyDestroyMember();

public:
	CSafeMonitorEvent() {
		dwMonitorId  = 0;
		dwCtrl       = 0;
		dwClean      = 0;
		dwFileType   = SM_FILE_TYPE_UNKNOWN;
		dwFileEngine = SM_FILE_ENGINE_UNKNOWN;
		lpFilePath   = NULL;
		lpVirusName  = NULL;
		dwVirusID	 = 0;
		bAuto        = FALSE;
	}
};

//////////////////////////////////////////////////////////////////////////
// CProcessMonitorEvent
class CProcessMonitorEvent : public CSafeMonitorEvent
{
public:
	LPCTSTR lpHostPath;		// host ����·��
	LPCTSTR lpCmdLine;		// ������
	LPCTSTR lpCurDir;
	DWORD	dwCmdMode;

public:
	CProcessMonitorEvent() {
		dwMonitorId = SM_ID_PROCESS;
		lpHostPath  = NULL;
		lpCmdLine   = NULL;
		lpCurDir    = NULL;
		dwCmdMode   = 0;
	}

	virtual CSafeMonitorEvent* Clone();
	virtual void Destroy();
};

//////////////////////////////////////////////////////////////////////////
// CRiskMonitorEvent
class CRiskMonitorEvent : public CSafeMonitorEvent
{
public:
	enum {
		SOURCE_READ_REG_DATA  = 0,
		SOURCE_ENUM_REG_VALUE = 1,
		SOURCE_ENUM_REG_KEY   = 2,
		SOURCE_ENUM_REG_DATA  = 3,
		SOURCE_ENUM_FILE      = 4,
		SOURCE_ENUM_WINDRV    = 5,
		SOURCE_ENUM_WINSRV    = 6,
		SOURCE_ENUM_MODULE    = 7, // ö�ٽ���ģ��
		SOURCE_ENUM_PROCESS   = 8
	};

	DWORD	dwLevel;
	DWORD	dwAction;
	DWORD	dwSourceType;
	DWORD	dwPointID;

	LPCTSTR lpCmdLine;
	LPCTSTR lpTitle;
	LPCTSTR	lpInfo;

	LPCTSTR	lpPath;
	LPCTSTR lpValue;
	DWORD	dwDataType;
	LPVOID	lpData;
	DWORD	dwDataSize;

public:
	CRiskMonitorEvent() {
		dwMonitorId  = SM_ID_RISK;
		dwLevel      = 0;
		dwAction     = 0;
		dwSourceType = 0;
		dwPointID    = 0;
		lpCmdLine    = NULL;
		lpInfo       = NULL;
		lpTitle      = NULL;
		lpPath       = NULL;
		lpValue      = NULL;
		dwDataType   = 0;
		lpData       = NULL;
		dwDataSize   = 0;
	}

	virtual CSafeMonitorEvent* Clone();
	virtual void Destroy();
};

/////////////////////////////////////////////////////////////////////////
inline BOOL IsStringDataType(DWORD dwType) {
	return ((dwType == REG_SZ) || (dwType == REG_EXPAND_SZ) || (dwType == REG_MULTI_SZ));
}

enum UDiskMonitorMod{
	UDiskMonitorModInit = 0,
	UDiskMonitorModFastScan = 1,
	UDiskMonitorModHideDirectoryScan,
	UDiskMonitorModDeferedScan,
	UDiskMonitorModLnkFileScan,
};

enum UDiskMonitorAdvanceSet{
	UDiskMonitorAdvanceSetInit = 0,
	UDiskMonitorAdvanceSetOnlyReport = 1,
};

//////////////////////////////////////////////////////////////////////////
// CUDiskMonitorEvent
class CUDiskMonitorEvent : public CSafeMonitorEvent
{
public:
	LPCTSTR lpInfPath;
	LPCTSTR lpCmdLine;
	DWORD	dwModId;	///> [=UDiskMonitorModInit]	��ģ��ID
	BOOL	bSpecial;	///> [=FALSE]	�����¼�
	DWORD	dwAdvanceSet;

public:
	CUDiskMonitorEvent() {
		dwMonitorId = SM_ID_UDISK;
		lpInfPath   = NULL;
		lpCmdLine   = NULL;
		dwModId		= UDiskMonitorModInit;
		bSpecial	= FALSE;
		dwAdvanceSet = UDiskMonitorAdvanceSetInit;
	}

	virtual CSafeMonitorEvent* Clone();
	virtual void Destroy();
};

//////////////////////////////////////////////////////////////////////////
// CVirusMonitorEvent
class CVirusMonitorEvent : public CSafeMonitorEvent
{
public:
	DWORD		dwInfoType;
	LPCTSTR		lpInfo;
	
	enum enumInfoType
	{
		enumInfoTypeProcessCreated = 1
	};

public:
	CVirusMonitorEvent() 
	{
		dwInfoType = 0;
		lpInfo = NULL;
		dwMonitorId = SM_ID_VIRUS;
	}

	virtual CSafeMonitorEvent* Clone();
	virtual void Destroy();
};

//////////////////////////////////////////////////////////////////////////
// CKwsMonitorEvent
interface IKwsPopObtainer;

class CKwsMonitorEvent : public CSafeMonitorEvent
{
public:
	LPCTSTR		lpURL;
	LPCTSTR		lpInfo;
	LPCTSTR     lpBrowser;
	DWORD		dwBlockType;
	DWORD		dwReason;
	IKwsPopObtainer* lpPopObtainer;

public:
	CKwsMonitorEvent() {
		dwMonitorId = SM_ID_KWS;
		lpURL		= NULL;
		lpInfo		= NULL;
		lpPopObtainer = NULL;
		lpBrowser = NULL;
		dwBlockType	= 0;
		dwReason = 0;
	}

	virtual CSafeMonitorEvent* Clone();
	virtual void Destroy();
};

//////////////////////////////////////////////////////////////////////////
// 
interface IKSafeDownPopInfo;

class CKwsSafeDownEvent: public CSafeMonitorEvent
{
public:
	CKwsSafeDownEvent()
		: m_pPopInfo(NULL)
	{

	}

	CKwsSafeDownEvent(IKSafeDownPopInfo* pPopInfo)
		: m_pPopInfo(pPopInfo)
	{
		dwMonitorId = SM_ID_KWS_SAFE_DOWN;
	}

	virtual CSafeMonitorEvent* Clone();
	virtual void Destroy();

	IKSafeDownPopInfo*		GetInfo(BOOL bSetNull = FALSE)		
	{
		IKSafeDownPopInfo* lpPopInfo = m_pPopInfo;
		if ( bSetNull )
		{
			m_pPopInfo = NULL;
		}

		return lpPopInfo;
	}

private:
	IKSafeDownPopInfo*		m_pPopInfo;
};


//////////////////////////////////////////////////////////////////////////
// CKwsUrlMonitorEvent
interface IKUrlMonPopInfo;

class CKwsUrlMonitorEvent : public CVirusMonitorEvent
{
public:
	CKwsUrlMonitorEvent() 
		: m_pPopInfo(NULL)
	{
	}

	CKwsUrlMonitorEvent(IKUrlMonPopInfo* pPopInfo)
		: m_pPopInfo(pPopInfo)
	{
		dwMonitorId = SM_ID_KWS_URL_MON;
	}

	virtual CSafeMonitorEvent* Clone();
	virtual void Destroy();

	IKUrlMonPopInfo*		GetInfo(BOOL bSetNull = FALSE)		
	{
		IKUrlMonPopInfo* lpPopInfo = m_pPopInfo;
		if ( bSetNull )
		{
			m_pPopInfo = NULL;
		}

		return lpPopInfo;
	}

private:
	IKUrlMonPopInfo*		m_pPopInfo;
};

#include <PopPack.h>
