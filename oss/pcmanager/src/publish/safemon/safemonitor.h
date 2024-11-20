/*
dummyz@126.com
2009/12/10
*/
#ifndef _SAFE_MONITOR_INC_
#define _SAFE_MONITOR_INC_ // �����ط�ʹ�ã�����ʹ��#pragma once

/*
1��Σ��ע��������Ϊ���
2��Σ�ս��̴������
3�������Ϊ���
*/

#include <assert.h>

////////////////////////////////////////////////////////////////////////////////////////////////
//									const value defined
////////////////////////////////////////////////////////////////////////////////////////////////

#define BKSAFE_MONITOR_NUMBER		4	// ��������4 ��

// �������ʶ
#define SM_ID_INVAILD				0
#define SM_ID_PROCESS				1 // ���̼��
#define SM_ID_RISK					2 // ���ղ������
#define SM_ID_UDISK					4 // u���Զ���������
#define SM_ID_VIRUS					5
#define SM_ID_LEAK                  6 // ©������
#define SM_ID_RESCAN				SM_ID_VIRUS // ��ɨ
#define SM_ID_KWS					11 //�������������
#define SM_ID_KWS_SAFE_DOWN			12 //���ر�������
#define SM_ID_KWS_URL_MON			13 // url ����ǽ
#define SM_ID_REPORT				14 // �첽�����ύ
#define SM_ID_ARP                   15

// ���������״̬
#define SM_STATUS_INVALID			0
#define SM_STATUS_RUN				1
#define SM_STATUS_STOP				2
#define SM_STATUS_PAUSE				3

// ������֧�ֵĿ���
#define SM_CTRL_TRUST				0x0001			// ����
#define SM_CTRL_BLOCK				0x0002			// ��ֹ
#define SM_CTRL_CLEAN				0x0004			// ��ֹ��ͬʱִ���������
#define SM_CTRL_REMEMBER			0x00010000		// ��ס������������ʾ
#define SM_CTRL_HISTROY				0x00020000		// ����������ʷ
#define SM_CTRL_FAST_SCAN			0x00040000		// ͬʱִ���˿���ɨ��

#define IS_SM_CTRL_TRUST(x)			(((x) & SM_CTRL_TRUST) == SM_CTRL_TRUST)
#define IS_SM_CTRL_BLOCK(x)			(((x) & SM_CTRL_BLOCK) == SM_CTRL_BLOCK)
#define IS_SM_CTRL_CLEAN(x)			(((x) & SM_CTRL_CLEAN) == SM_CTRL_CLEAN)
#define IS_SM_CTRL_REMERBER(x)		(((x) & SM_CTRL_REMEMBER) == SM_CTRL_REMEMBER)
#define IS_SM_CTRL_HISTROY(x)		(((x) & SM_CTRL_HISTROY) == SM_CTRL_HISTROY)
#define IS_SM_CTRL_FAST_SCAN(x)		(((x) & SM_CTRL_FAST_SCAN) == SM_CTRL_FAST_SCAN)

// ��������׽���Ķ���
#define SM_ACTION_NOTING			0
#define SM_ACTION_ADD				1		// �½�
#define SM_ACTION_DELETE			2		// ɾ��
#define SM_ACTION_MODIFY			3		// �޸�

// ������
#define SM_CLEAN_DELETE				1
#define SM_CLEAN_REPAIR				2
#define SM_CLEAN_FAILED				0x00010000
#define SM_CLEAN_SUCCESS			0x00020000
#define SM_CLEAN_REBOOT				0x00030000
#define GET_SM_CLEAN_OPERATOR(x)	((x) & 0xffff)
#define GET_SM_CLEAN_RESULT(x)		((x) & 0xffff0000)

//�ļ�����
enum SM_FILE_TYPE {
	SM_FILE_TYPE_UNKNOWN		= 0x00000000,
	SM_FILE_TYPE_SAFE			= 0x00010000,
	SM_FILE_TYPE_VIRUS			= 0x00020000
};

enum SM_FT_VIRUS  // ������������
{
	SM_FT_VIRUS_TROJAN = 1,
	SM_FT_VIRUS_THREAT,
	SM_FT_VIRUS_MALWARE,
	SM_FT_VIRUS_WORM,
	SM_FT_VIRUS_ADWARE,
	SM_FT_VIRUS_RISK_LOW,// ���ճ���
	SM_FT_VIRUS_RISK_MED,
	SM_FT_VIRUS_RISK_HIG,
};

enum SM_FT_UNKNOWN // δ֪��������
{
	SM_FT_UNKNOWN_NET_ERROR		= 1,
	SM_FT_UNKNOWN_TIMEOUT,
	SM_FT_UNKNOWN_SCAN_ERROR,
	SM_FT_UNKNOWN_SCAN_RESULT_ERROR
};

inline DWORD GET_SM_FILE_TYPE(DWORD dwFileTyppe)			
{
	return (dwFileTyppe & 0xffff0000);
}

inline DWORD GET_SM_SUB_FILE_TYPE(DWORD dwFileType)
{
	DWORD f = dwFileType & 0xffff;
	return (f <= 0xff) ? f : 0;
}

inline SM_FILE_TYPE MAKE_SM_FILE_TYPE(DWORD dwFileType, DWORD dwSubFileType, DWORD dwSecLevel = 0)
{
	dwSubFileType = dwSubFileType + (dwSecLevel << 8);
	assert(dwSubFileType <= 0xFFFF);

	return (SM_FILE_TYPE)(dwFileType | dwSubFileType);
}

// �ļ�ɨ������
enum SM_FILE_ENGINE
{
	SM_FILE_ENGINE_UNKNOWN									=	0x00000000,
	SM_FILE_ENGINE_VIRUS									=	0x00000001, // ��������
	SM_FILE_ENGINE_LOCAL									=	SM_FILE_ENGINE_VIRUS,
	SM_FILE_ENGINE_CLOUND									=	0x00000002, // �ƶ�����
	SM_FILE_ENGINE_PLUGIN									=	0x00000004, // �������
	SM_FILE_ENGINE_KNOWLEDGELIB								=	0x00000008, // ֪ʶ������
	SM_FILE_ENGINE_HEURISTIC								=	0x00000010, // ����
	SM_FILE_ENGINE_RUNDATA		    						=	0x00000020, // �������
	SM_FILE_ENGINE_VERIFY_SIGN								=	0x00000080, // ǩ��
	SM_FILE_ENGINE_RISK_SIGN								=	0x00000100, // �ڡ��������������հ�װ��

	SM_FILE_ENGINE_ALL										=	0xFFFFFFFF
};

////////////////////////////////////////////////////////////////////////////////////////////////
//									interface define
////////////////////////////////////////////////////////////////////////////////////////////////
#include "SafeMonitorEvent.h"
#include <assert.h>

class ISafeMonitorObserver;
class ISafeMonitorManager;
class CSafeMonitorEvent;

class ISafeMonitorObserver
{
public:
	virtual DWORD __stdcall MonitorEvent(CSafeMonitorEvent* lpEvent) = 0;
};

class ISafeMonitorManager : public ISafeMonitorObserver
{
public:
	virtual HRESULT __stdcall Init() = 0;
	virtual HRESULT __stdcall Uninit() = 0;

	virtual HRESULT __stdcall Startup(ISafeMonitorObserver* lpObserver) = 0;
	virtual HRESULT __stdcall Shutdown() = 0;

	// SM_ID_RISK ֧�� 'default_homepage', 'default_browser'
	virtual HRESULT __stdcall SetProperty(DWORD dwMonitorId, LPCTSTR lpName, LPCTSTR lpValue) = 0;
	virtual HRESULT __stdcall GetProperty(DWORD dwMonitorId, LPCTSTR lpName, LPTSTR& lpValue) = 0;

	// SM_ID_ALL ֧�� 'status', 
	// set 'plugin_lib_updated', 'knowledge_lib_updated', 'riskpoint_lib_updated'
	virtual HRESULT __stdcall SetPropertyInt(DWORD dwMonitorId, LPCTSTR lpName, DWORD dwValue) = 0;
	virtual HRESULT __stdcall GetPropertyInt(DWORD dwMonitorId, LPCTSTR lpName, DWORD& dwValue) = 0;
};

#define SMM_DLL_NAME	_T("ksfmon.dll")
#define SMM_FUN_NAME	"A1"
#define GCPSR_FUN_NAME	"D1"

typedef ISafeMonitorManager* (WINAPI* PFN_GetSafeMonitorManager)();
ISafeMonitorManager* WINAPI GetSafeMonitorManager();


//////////////////////////////////////////////////////////////////////////
// CSafeMonitorLoader

class CSafeMonitorLoader
{
public:
	CSafeMonitorLoader()
	{
		m_pfnGet = NULL;

		m_hModule = LoadLibrary(SMM_DLL_NAME);
		if ( m_hModule != NULL )
		{
			m_pfnGet = (PFN_GetSafeMonitorManager)GetProcAddress(m_hModule, SMM_FUN_NAME);
		}
	}
	
	~CSafeMonitorLoader()
	{
		FreeLibrary(m_hModule);
	}

	operator bool ()
	{
		return (m_hModule != NULL) && (m_pfnGet != NULL);
	}

	ISafeMonitorManager* GetManager()
	{
		assert(m_pfnGet != NULL);
		return (m_pfnGet != NULL) ? m_pfnGet() : NULL;
	}


protected:
	PFN_GetSafeMonitorManager m_pfnGet;
	HMODULE		m_hModule;
};


#endif /* _SAFE_MONITOR_INC_ */ 

