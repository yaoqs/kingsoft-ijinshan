//////////////////////////////////////////////////////////////////////
///		@file		kxeservice.h
///		@author		luopeng
///		@date		2008-9-23 09:07:58
///	
///		@brief		
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../kxeserviceprovider/ikxeserviceprovider.h"
#include "idl.h"
#include "../kxeserviceprovider/service_provider_clsid.h"
#include "../kxeserviceprovider/kxespregister.h"
#include "../kxeevent/ikxeeventnotify.h"

/**
 * @page architecture_service_provider_interface KXEngine Architecture Service Provider Base Interface
 * @section architecture_service_provider_interface_define �ӿ��б�
 * - @ref kxe_service_provider_interface_group
 * @section architecture_service_provider_interface_clsid Ԥ����ķ����ṩ��SCOM��CLSID�б�
 * - @ref kxe_service_provider_clsid_group
 */

/**
 * @page kxeservice_provider_example KXEngine Service Provider Example
 * @section architecture_service_provider_example_header ͷ�ļ�����
 * @code
 * class KxEScanServiceProvider : public IKxEServiceProvider,
							   public IKxEEventNotify,
							   public KxEHttpServerT<IKxEScanService, 0>,
							   public KSComRoot<KxEScanServiceProvider>
{
public:
	KxEScanServiceProvider(void);
	~KxEScanServiceProvider(void);

	KS_DEFINE_GETCLSID(CLSID_KxEScanServiceProvider);

	DECLARE_INDEPENDENT_OBJECT();

	KSCOM_QUERY_BEGIN
		KSCOM_QUERY_ENTRY(IKxEServiceProvider)
	KSCOM_QUERY_END


public: // IKxEServiceProvider
	/// ��ʼ��Service Provider
	virtual int __stdcall InitializeService();
	/// ����ʼ��Service Provider
	virtual int __stdcall UninitializeService();
	/// ����Service Provider
	virtual int __stdcall StartService();
	/// ֹͣService Provider
	virtual int __stdcall StopService();

public:
	virtual int __stdcall StartScanSession(
		const KXE_START_SCAN_PARAEMETER& scanParameter,
		KXE_SCAN_SESSION& scanSession
		);

	virtual int __stdcall QueryScanSession(
		const KXE_SCAN_SESSION& scanSession,
		KXE_SCANNING_FILE& scanningFile
		);

public:
	KXE_DECLARE_EVENT_NOTIFY();

	int OnFileMonStatusEvent(
		short sSubSystemId, 
		short sEventId,
		const KXE_FILE_MON_STATUS& status, 
		int nErr
		);

private:
	HMODULE m_hScanSolution;
	IScanSystem* m_pScanSystem;
};
 * @endcode
 * @section architecture_service_provider_example_src ʵ���ļ�����
 * @code

// ע�����
REGISTER_TO_FACTORY(KxEScanServiceProvider, "KxEScanServiceProvider")

// ע������ṩ���Է��㰲װ
KXE_REGISTER_SERVICE_PROVIDER(KxEScanServiceProvider, "KxEScanServiceProvider")

KXE_REGISTER_COMMAND_PROC(KxEScanServiceProvider, IKxEScanService, StartScanSession);
KXE_REGISTER_COMMAND_PROC(KxEScanServiceProvider, IKxEScanService, QueryScanSession);

KXE_BEGIN_EVENT_NOTIFY(KxEScanServiceProvider)
	KXE_ON_EVENT_PROCESS(enum_SubSystem_FileMon, KXE_FILE_MON_STATUS_EVENT, OnFileMonStatusEvent)
KXE_END_EVENT_NOTIFY()

typedef HRESULT CreateScanSystem(IScanSystem** ppScanSystem);

KxEScanServiceProvider::KxEScanServiceProvider(void)
{
}

KxEScanServiceProvider::~KxEScanServiceProvider(void)
{
}

int KxEScanServiceProvider::InitializeService()
{
	m_hScanSolution = LoadLibrary(_T("ScanSolution.dll"));
	if (m_hScanSolution != NULL)
	{
		CreateScanSystem* pfnScanSystem = (CreateScanSystem*)GetProcAddress(
			m_hScanSolution, 
			"CreateScanSystem"
			);
		if (pfnScanSystem == NULL)
		{
			int nErr = GetLastError();
			FreeLibrary(m_hScanSolution);
			m_hScanSolution = NULL;
			return nErr;
		}

		pfnScanSystem(&m_pScanSystem);
		return 0;
	}
	else
	{
		return GetLastError();
	}
}

int KxEScanServiceProvider::UninitializeService()
{
	if (m_pScanSystem)
	{
		m_pScanSystem->Release();
		m_pScanSystem = NULL;
	}

	if (m_hScanSolution)
	{
		FreeLibrary(m_hScanSolution);
		m_hScanSolution = NULL;
	}

	return 0;
}

int KxEScanServiceProvider::StartService()
{
	m_pScanSystem->Start();

	kxe_base_register_event_notify(
		enum_SubSystem_FileMon,
		KXE_FILE_MON_STATUS_EVENT,
		this
		);


	return RegisterToServer();
}

int KxEScanServiceProvider::StopService()
{
	return UnregisterServer();
}

int KxEScanServiceProvider::StartScanSession(const KXE_START_SCAN_PARAEMETER& scanParameter,
											 KXE_SCAN_SESSION& scanSession)
{
	return m_pScanSystem->StartScanSession(
		scanParameter.strScanPath.c_str(),
		&scanSession.nSession
		);
}

int KxEScanServiceProvider::QueryScanSession(const KXE_SCAN_SESSION& scanSession,
											 KXE_SCANNING_FILE& scanningFile)
{
	TCHAR szBuffer[1024];
	int nRetLen = 0;
	int nRet = m_pScanSystem->QueryScanSession(
		scanSession.nSession,
		szBuffer,
		1024,
		&nRetLen
		);
	if (nRet == 0)
	{
		scanningFile.strScanningFile = szBuffer;
	}
	return nRet;
}

int KxEScanServiceProvider::OnFileMonStatusEvent(short sSubSystemId,
												 short sEventId, 
												 const KXE_FILE_MON_STATUS& status,
												 int nErr)
{
	std::cout << "The filemon status is " << status.bIsEnable << std::endl;
	return 0;
}
 * @endcode

 * @section architecture_service_provider_export_example_src ������������
 * @code
#include "stdafx.h"
#include "../../Publish/scom/scom/scombase.h"
#include "../../Publish/include/kxeservice.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

// ����SCOM�Ľӿ�
DECLARE_DLLEXPORTS();

// ���������ṩ�߽ӿ�
KXE_SERVICE_PROVIDER_REGISTER_EXPORT();

// ������.def�ļ��ڱ��붨��ĵ�������Ϊ
// KSDllCanUnloadNow     			@1  PRIVATE
// KSDllGetClassObject   			@2	PRIVATE
// KSDllGetClassCount    			@3 	PRIVATE
// KSDllGetClassInfo			    @4	PRIVATE
// KxEDllRegisterServiceProvider    @5  PRIVATE
// KxEDllUnregisterServiceProvider  @6  PRIVATE

 * @endcode
 */
