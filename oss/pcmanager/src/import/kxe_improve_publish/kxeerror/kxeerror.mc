; // ***** Sample.mc *****

; // This is the header section.

MessageIdTypedef=DWORD


SeverityNames=(
	Success=0x0:STATUS_SEVERITY_SUCCESS
    Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
    Warning=0x2:STATUS_SEVERITY_WARNING
    Error=0x3:STATUS_SEVERITY_ERROR
    )


FacilityNames=(
	KxEBase=0x0:FACILITY_KXEBASE
    KxECfg=0x2:FACILITY_KXECFG
    KxEThread=0x3:FACILITY_KXETHREAD
    KxEEvent=0x4:FACILITY_KXEEVENT
	KxEHttp=0x5:FACILITY_KXEHTTP
	KxEScanApi=0x6:FACILITY_KXESCAN_API
	KxEIdl=0x7:FACILITY_IDL
	KxERegister=0x8:FACILITY_REGISTER
	KxEPassport=0x9:FACILITY_PASSPORT
	KxEServiceMgr=0xa:FACILITY_SERVICEMGR
	KxEIPC=0xb:FACILITY_IPC
	KxEPipe=0xc:FACILITY_PIPE
	
	KxEXmlHttp=0xd:FACILITY_XML_HTTP_REQUEST

	KSE=0xE2:FACILITY_KSE
	KSESqlite=0xE3:FACILITY_KSE_SQLITY
	KSEScanner=0xE4:FACILITY_KSE_SCANNER
	KSEProc=0xE5:FACILITY_KSE_PROC
	KSEFo=0xE6:FACILITY_KSE_FO
	KSEFileEngine=0xE7:FACILITY_KSE_FILEENGINE
	KSEPluginSDK=0xE8:FACILITY_KSE_PLUGIN_SDK
	KSENetDet=0xE9:FACILITY_KSE_NET_DET
	
	KWFS=0xF1:FACILITY_WFS
	KWFDB=0xF2:FACILITY_WFS_FDB
	KWSP=0xF3:FACILITY_WFS_SP
	
	KxEFM=0xA1:FACILITY_FILEMON
	KxEFMSP=0xA2:FACILITY_FILEMON_SP
	KxEFMSDK=0xA3:FACILITY_FILEMON_SDK

    KxESCSP=0xB1:FACILITY_SECURITYCENTER_SP
    KxESRSP=0xA4:FACILITY_SR_SP

        KxEBasicSP=0xA5:FACILITY_BASIC_SP
)


LanguageNames=(English=0x409:MSG00409)
LanguageNames=(Chinese=0x804:MSG00804)

; // The following are message definitions.
;

MessageId=0x1
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_NOT_OPEN
Language=English
The internet has not been open as the function open has not been called sucessfully yet.
.
Language=Chinese
Internet ��δ���򿪣���Ϊ���� open δ���ɹ�����
.

MessageId=0x2
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_NOT_ENOUGH_MEMORY
Language=English
Call new operator return a null pointer.
.
Language=Chinese
���� new ���������ؿ�ָ��
.

MessageId=0x3
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_INCORRECT_RETURN_DATA
Language=English
The return data from the pipe server is incorrect.
.
Language=Chinese
�ӹܵ��������˷��ص����ݲ���ȷ
.

MessageId=0x4
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_INVALID_PARAMETER
Language=English
The parameter is invalid.
.
Language=Chinese
��������
.

MessageId=0x5
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_PIPE_SERVER_NOT_RUNNING
Language=English
The named pipe server is not running right now.
.
Language=Chinese
�����ܵ���������ǰû������
.

MessageId=0x6
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_CREATE_CLIENT_PIPE_INSTANCE_FAILED
Language=English
Create named pipe instance by call API CreateFile failed on the client end.
.
Language=Chinese
�ͻ���ͨ������API CreateFile ���������ܵ�ʧ��
.

MessageId=0x7
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_CREATE_IO_COMPLETION_PORT_FAILED
Language=English
Create IO Completion Port( IOCP ) for the named pipe failed on the client end.
.
Language=Chinese
�ͻ���Ϊ�����ܵ����� IO ��ɶ˿�ʧ��
.

MessageId=0x8
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_CREATE_THREAD_FAILED
Language=English
Create thread for processing I/O request failed.
.
Language=Chinese
�������� I/O ������߳�ʧ��
.

MessageId=0x9
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_NOT_ALL_IO_PROCESSING_THREADS_WERE_NOTIFIED_TO_EXIT
Language=English
Not all of the threads for processing I/O request were notifyed to stop.
.
Language=Chinese
�������д��� I/O ������̶߳���ͨ���˳�
.

MessageId=0xa
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_WAIT_FOR_THREAD_EXIT_FAILED
Language=English
Wait for all the threads for processing I/O request failed.
.
Language=Chinese
�ȴ����д��� I/O ������̵߳���ֹʧ��
.

MessageId=0xb
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_PIPE_WRITE_FILE_FAILED
Language=English
Call the API WriteFile to write pipe failed.
.
Language=Chinese
����API WriteFile ����ܵ�д������ʱʧ��
.

MessageId=0xc
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTP_PIPE_READ_FILE_FAILED
Language=English
Call the API ReadFile to read pipe failed.
.
Language=Chinese
����API ReadFile �Դӹܵ���������ʱʧ��
.

MessageId=0xd
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_PREVIOUS_REQUEST_NOT_COMPLETED
Language=English
Request is denied because previous request has not completed.
.
Language=Chinese
ǰһ�ε�������δ��ɵ��±������󱻾ܾ�
.

MessageId=0xe
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_FAILED_TO_GET_SERVICE_PORT
Language=English
It failed to get service port of the HTTP server.
.
Language=Chinese
��ȡ HTTP �������˿�ʧ��
.

MessageId=0xf
Severity=Error
Facility=KxEXmlHttp
SymbolicName=E_KXMLHTTP_TIME_OUT
Language=English
Operation failed with time out.
.
Language=Chinese
������ʱ��ʧ��
.

; // KxEPipe
MessageId=0x1
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_CREATE_NAMED_PIPE_FAILED
Language=English
Create named pipe failed.
.
Language=Chinese

����CreateNamedPipe���������ܵ�ʧ��
.

MessageId=0x2
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_CREATE_THREAD_FAILED
Language=English
Create thread failed.
.
Language=Chinese

����CreateThread�����߳�ʧ��
.

MessageId=0x3
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_CONNECT_PIPE_FAILED
Language=English
The server end of the named pipe connect the client failed.
.
Language=Chinese

�����ܵ������������ӿͻ���ʧ��
.

MessageId=0x4
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_WAIT_NAMED_PIPE_FAILED
Language=English
The client end of the named pipe connect the server end failed.
.
Language=Chinese

�����ܵ��ͻ������ӷ�������ʧ��
.

MessageId=0x5
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_CREATE_INSTANCE_ON_THE_PIPE_CLIENT_END_FAILED
Language=English
Call CreateFile to create instance on the pipe client end failed.
.
Language=Chinese

����CreateFile�Դ��������ܵ��ͻ���ʧ��
.

MessageId=0x6
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_DISCONNCET_NAMED_PIPE_FAILED
Language=English
The server end of the named pipe disconncet the pipe failed.
.
Language=Chinese

�����ܵ�����˵���DisconncetNamedPipe�Թرչܵ�ʱʧ��
.

MessageId=0x7
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_NAMED_PIPE_NOT_START
Language=English
The named pipe is not started as the user have not call function Start.
.
Language=Chinese

�����ܵ�û����������Ϊ�û�û�е���Start����
.

MessageId=0x8
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_SERVER_WRITE_FILE_FAILED
Language=English
The server end write into the named pipe failed.
.
Language=Chinese

������������ܵ���д������ʧ��
.

MessageId=0x9
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_CLIENT_WRITE_FILE_FAILED
Language=English
The client end write into the named pipe failed.
.
Language=Chinese

�ͻ����������ܵ���д������ʧ��
.

MessageId=0xa
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_SERVER_READ_FILE_FAILED
Language=English
The server end read from the named pipe failed.
.
Language=Chinese

����˴������ܵ��ж�ȡ����ʧ��
.

MessageId=0xb
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_CLIENT_READ_FILE_FAILED
Language=English
The client end read from the named pipe failed.
.
Language=Chinese

�ͻ��˴������ܵ��ж�ȡ����ʧ��
.

MessageId=0xc
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_PRODUCT_ALREADY_REGISTERED
Language=English
The product has been already registered.
.
Language=Chinese

�Ӳ�ƷID�Ѿ�ע��
.

MessageId=0xd
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_INCORRECT_PARAMETER
Language=English
Incorrect parameter(s) passed by caller or delivered in the named pipe.
.
Language=Chinese

�������ṩ�˲���ȷ�Ĳ�������ͨ�������ܵ������������ݲ���ȷ
.

MessageId=0xe
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_THREAD_COMPELLED_TO_STOP
Language=English
Thread is compelled to stop because the user has stopped the pipe.
.
Language=Chinese

�û��ر��˹ܵ������̱߳�����ֹ
.

MessageId=0xf
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_WAIT_FOR_THREAD_EXIT_FAILED
Language=English
Wait for all threads created by the pipe failed.
.
Language=Chinese

�ȴ������߳̽����Ĳ���ʧ��
.

MessageId=0x10
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_BAD_RETURN_DATA
Language=English
Data returned from the server end or the client end is incorrect.
.
Language=Chinese

�ӷ���˻�ͻ��˷��ص���������
.

MessageId=0x11
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_SERVICE_PROVIDER_ALREADY_REGISTERED
Language=English
The service provider has been already registered.
.
Language=Chinese

�����ṩ���Ѿ�ע��
.

MessageId=0x12
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_SERVICE_PROVIDER_NOT_REGISTERED
Language=English
Service provider not registered on the subproduct end.
.
Language=Chinese

�Ӳ�Ʒ��û��ע������ṩ��
.

MessageId=0x13
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_PRODUCT_NOT_REGISTERED
Language=English
Product ID has not been registered.
.
Language=Chinese

�Ӳ�ƷID��δע��
.

MessageId=0x14
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_IMPERSONATE_CLIENT_FAILED
Language=English
The server end of the named pipe impersonate the client end failed.
.
Language=Chinese

�����ܵ������ģ��ͻ���ʧ��
.

MessageId=0x15
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_REVERT_TO_SELF_FAILED
Language=English
The server end of the named pipe revert to self failed.
.
Language=Chinese

�����ܵ������ģ��ͻ��˺�ָ�ԭ״̬ʱʧ��
.

MessageId=0x16
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_SP_PROCESS_REQUEST_FAILED
Language=English
The service provider failed to process request.
.
Language=Chinese

�����ṩ�ߴ�������ʧ��
.

MessageId=0x17
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_CREATE_IO_COMPLETION_PORT_FAILED
Language=English
Create I/O completion port or associate an I/O port to a pipe handle failed.
.
Language=Chinese

����I/O��ɶ˿�ʧ�ܣ����߽���ɶ˿���ĳ���ܵ��������ʱʧ��
.

MessageId=0x18
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_CREATE_EVENT_FAILED
Language=English
Create event failed.
.
Language=Chinese

�����¼�����ʧ��
.

MessageId=0x19
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_NOT_ALL_THREADS_ARE_NOTIFIED_TO_STOP
Language=English
Not all of worker threads are notified to stop, this is an fatal error.
.
Language=Chinese

�������еĹ����̶߳���֪ͨ��ֹ������һ����������
.

MessageId=0x1a
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_PIPE_ALREADY_STARTED
Language=English
kxepipe component has been already started.
.
Language=Chinese

kxepipe����Ѿ�����
.

MessageId=0x1b
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_SET_SECURITY_INFO_FAILED
Language=English
Call API SetSecurityInfo failed after the the pipe instance been created.
.
Language=Chinese

���������ܵ�ʵ�������API SetSecurityInfo ʱʧ��
.

MessageId=0x1c
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_GET_SECURITY_DESCRIPTOR_SACL_FAILED
Language=English
Call API GetSecurityDescriptorSacl failed after the the pipe instance been created.
.
Language=Chinese

���������ܵ�ʵ�������API GetSecurityDescriptorSacl ʱʧ��
.

MessageId=0x1d
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_CONVERT_STRING_TO_SECURITY_DESCRIPTOR_FAILED
Language=English
Call API ConvertStringSecurityDescriptorToSecurityDescriptorW failed after the the pipe instance been created.
.
Language=Chinese

���������ܵ�ʵ�������API ConvertStringSecurityDescriptorToSecurityDescriptorW ʱʧ��
.

MessageId=0x1e
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_NOT_ENOUGH_MEMORY
Language=English
Call new operator to allocate memory failed.
.
Language=Chinese

���� new �����������ڴ�ʧ��
.

MessageId=0x1f
Severity=Error
Facility=KxEPipe
SymbolicName=E_KXEPIPE_SP_PIPE_NAME_NOT_FOUND_IN_REGISTRY
Language=English
The specified Service Provider's pipe name was not found in registry.
.
Language=Chinese

��ע�����û���ҵ�ָ�������ṩ�ߵ������ܵ���
.

; // KxEIPC
MessageId=0x1
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_SP_NOT_FOUND
Language=English
The service provider is not fouend.
.
Language=Chinese

�����ṩ��û���ҵ�
.

MessageId=0x2
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_MANAGE_SERVER_ALREADY_INITIALIZED
Language=English
The manage server has been already initialized.
.
Language=Chinese

IPC����������Ѿ���ʼ��
.

MessageId=0x3
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_MANAGE_SERVER_NOT_INITIALIZED
Language=English
The manage server has not been initialized yet.
.
Language=Chinese

IPC�����������δ��ʼ��
.

MessageId=0x4
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_MANAGE_SERVER_ALREADY_STARTED
Language=English
The manage server has been already started.
.
Language=Chinese

IPC����������Ѿ�����
.

MessageId=0x5
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_MANAGE_SERVER_NOT_STARTED
Language=English
The manage server has not been started yet.
.
Language=Chinese

IPC�����������δ����
.

MessageId=0x6
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_MANAGE_CLIENT_ALREADY_INITIALIZED
Language=English
The manage client has been already initialized.
.
Language=Chinese

IPC����ͻ����Ѿ���ʼ��
.

MessageId=0x7
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_MANAGE_CLIENT_NOT_INITIALIZED
Language=English
The manage client has not been initialized yet.
.
Language=Chinese

IPC����ͻ�����δ��ʼ��
.

MessageId=0x8
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_MANAGE_CLIENT_ALREADY_STARTED
Language=English
The manage client has been already started.
.
Language=Chinese

IPC����ͻ����Ѿ�����
.

MessageId=0x9
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_MANAGE_CLIENT_NOT_STARTED
Language=English
The manage client has not been started yet.
.
Language=Chinese

IPC����ͻ�����δ����
.

MessageId=0xa
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_NOT_ALL_SERVICE_PROVIDER_REGISTERED
Language=English
Not all of the service provider of the client reregistered to the server successfully.
.
Language=Chinese

�������еĿͻ��˷����ṩ�߶��ɹ���������ܶ�����ע��
.

MessageId=0xb
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_PIPE_SERVER_DOES_NOT_EXIST
Language=English
The given named pipe server doesn't exist .
.
Language=Chinese

ָ���������ܵ�������������
.

MessageId=0xc
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_NOT_ENOUGH_MEMORY
Language=English
Call the new operator to allocate memory failed.
.
Language=Chinese

���� new �����������ڴ�ʧ��
.

MessageId=0xd
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_CREATE_SP_PIPE_INFO_KEY_FAILED
Language=English
It failed to create the registry key for the specified SP's pipe information.
.
Language=Chinese

��ע����д���ָ��SP�Ĺܵ���Ϣʧ��
.

MessageId=0xe
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_SET_SP_PIPE_NAME_KEY_FAILED
Language=English
It failed to set the specified SP's pipe name key in the registry.
.
Language=Chinese

��ע���������ָ��SP�Ĺܵ�����ֵʧ��
.

MessageId=0xf
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_DELETE_SP_PIPE_INFO_KEY_FAILED
Language=English
It failed to delete the specified SP's pipe information in the registry.
.
Language=Chinese

��ע�����ɾ��ָ��SP�Ĺܵ���Ϣʧ��
.

MessageId=0x10
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_ILLEGAL_URL
Language=English
The request caller's URL is illegal.
.
Language=Chinese

�����ߵ�URL���Ϸ�
.

MessageId=0x11
Severity=Error
Facility=KxEIPC
SymbolicName=E_KXEIPC_READ_INI_FILE_FAILED
Language=English
 It failed to read the .ini filewhich stores legal websites.
.
Language=Chinese

��ȡ����Ϸ����ӵ������ļ�ʧ��
.

; // KxEServiceMgr
MessageId=0x1
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_NOT_INITIALIZED
Language=English
The service manager is not initialized.
.
Language=Chinese

�����������δ��ʼ��
.

MessageId=0x2
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_INITIALIZED
Language=English
The service manager is initialized.
.
Language=Chinese

����������Ѿ���ʼ��
.

MessageId=0x3
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCTMGR_NOT_INITIALIZED
Language=English
The product manager is not initialized.
.
Language=Chinese

��Ʒ��������δ��ʼ��
.

MessageId=0x4
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCTMGR_INITIALIZED
Language=English
The product manager is initialized.
.
Language=Chinese

��Ʒ�������Ѿ���ʼ��
.

MessageId=0x5
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCTMGR_PRODUCT_EXIST
Language=English
The product is exist.
.
Language=Chinese

ָ���Ĳ�Ʒ�Ѿ�����
.

MessageId=0x6
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCTMGR_PRODUCT_NOT_EXIST
Language=English
The product is not exist.
.
Language=Chinese

ָ���Ĳ�Ʒ������
.

MessageId=0x7
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCTMGR_CLSID_DUPLICATE
Language=English
The component's clsid is duplicate
.
Language=Chinese

ָ�������CLSID�Ѿ�����
.

MessageId=0x8
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCTMGR_PATH_INVALID
Language=English
The product's path is invalid
.
Language=Chinese

ָ���Ĳ�ƷĿ¼��Ч
.

MessageId=0x9
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCTMGR_PLUGIN_PATH_INVALID
Language=English
The product's plugin path is invalid
.
Language=Chinese

ָ���Ĳ�ƷpluginĿ¼��Ч
.

MessageId=0xa
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCTMGR_WEB_PATH_INVALID
Language=English
The product's web path is invalid
.
Language=Chinese

ָ���Ĳ�ƷwebĿ¼��Ч
.

MessageId=0xb
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCTMGR_SP_NOT_COMPONENT
Language=English
The service provider file is not in component file.
.
Language=Chinese

ָ���ķ����ṩ���ļ�����һ��SCOM���
.

MessageId=0xc
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCTMGR_SP_CLSID_NOT_COMPONENT
Language=English
The service provider clsid is not in component clsid.
.
Language=Chinese

ָ���ķ����ṩ��clsid����scom�����
.

MessageId=0xd
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCTMGR_SP_CLSID_DUPLICATE
Language=English
The service provider component's clsid is duplicate
.
Language=Chinese

ָ���ķ����ṩ�����CLSID�Ѿ�����
.

MessageId=0xe
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_ALL_SP_FAIL_IN_PRODUCT
Language=English
The all service providers in a product is failed.
.
Language=Chinese

ָ����Ʒ������SP����ʧ��.
.

MessageId=0xf
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCT_NOT_RUNNING
Language=English
The product is not running.
.
Language=Chinese

ָ���Ĳ�Ʒû����������.
.

MessageId=0x10
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PRODUCT_RUNNING
Language=English
The product is running.
.
Language=Chinese

ָ���Ĳ�Ʒ��������.
.

MessageId=0x11
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_GUID_INVALID
Language=English
The guid is invalid.
.
Language=Chinese

guid����Ч��.
.

MessageId=0x12
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_FILE_PATH_INVALID
Language=English
The file path is invalid.
.
Language=Chinese

�ļ�·������Ч��.
.

MessageId=0x13
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_COMPONENT_NOT_EQUAL
Language=English
The component file in config is not equal in count
.
Language=Chinese

��ȡ��������ļ���Ŀ�������ļ��б�־��Ŀ��һ��
.

MessageId=0x14
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_SP_COMPONENT_NOT_EQUAL
Language=English
The sp component file in config is not equal in count
.
Language=Chinese

��ȡ�������ṩ��������ļ���Ŀ�������ļ��б�־��Ŀ��һ��
.

MessageId=0x15
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_CHILD_PRODUCT_NOT_EQUAL
Language=English
The child product in config is not equal in count
.
Language=Chinese

��ȡ���Ӳ�Ʒ��Ŀ�������ļ��б�־��Ŀ��һ��
.

MessageId=0x16
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_TASK_EXCEED_MAX
Language=English
The task is exceed the max number.
.
Language=Chinese

�����������������ֵ
.

MessageId=0x17
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_TASK_NOT_FOUND
Language=English
The task is not found.
.
Language=Chinese

ָ��������û���ҵ�.
.

MessageId=0x18
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_TASK_CAN_NOT_CLOSE
Language=English
The task can't be closed.
.
Language=Chinese

ָ���������ܱ��ر�
.

MessageId=0x19
Severity=Error
Facility=KxEServiceMgr
SymbolicName=E_KXESERVICEMGR_PROCESS_DETACHED
Language=English
The process is detached.
.
Language=Chinese

ָ���Ľ���detached.
.

; // KxEPassport
MessageId=0x1
Severity=Error
Facility=KxEPassport
SymbolicName=E_KXEPASSPORT_USERNAME_NOT_ASCII
Language=English
The user name is not ascii.
.
Language=Chinese

�û����а�����ascii��.
.

MessageId=0x2
Severity=Error
Facility=KxEPassport
SymbolicName=E_KXEPASSPORT_PPWIZ_IS_RUNNING
Language=English
The Ppwizard is running.
.
Language=Chinese

PPWIZARD����������.
.

MessageId=0x3
Severity=Error
Facility=KxEPassport
SymbolicName=E_KXEPASSPORT_PPWIZ_NOT_UP_TO_SNUFF
Language=English
The scene is not up to snuff.
.
Language=Chinese

�����ϵ���ppwizard������.
.

MessageId=0x4
Severity=Error
Facility=KxEPassport
SymbolicName=E_KXEPASSPORT_SP_NOT_INITIALIZED
Language=English
The Passport service provider has not been initialized.
.
Language=Chinese

Passport SP δ����ʼ��.
.

MessageId=0x5
Severity=Error
Facility=KxEPassport
SymbolicName=E_KXEPASSPORT_NO_PPWIZ_WINDOW_TO_SHOW
Language=English
There is no ppwizard window to show.
.
Language=Chinese

û�п�ǰ�õ�ppwizardҳ��.
.

; // KxERegister
MessageId=0x1
Severity=Error
Facility=KxERegister
SymbolicName=E_KXEREG_FAIL_LOAD_CONFIG
Language=English
It failed to load config file.
.
Language=Chinese

���������ļ�����.
.

MessageId=0x2
Severity=Error
Facility=KxERegister
SymbolicName=E_KXEREG_ZERO_FILE
Language=English
The file list is empty.
.
Language=Chinese

�ļ��б��ǿյ�
.

; // KxEIdl
MessageId=0x1
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_LOAD_FILE
Language=English
It failed to load xml file
.
Language=Chinese

����XML�ļ�����.
.

MessageId=0x2
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_LOAD_TEXT
Language=English
It failed to load xml text.
.
Language=Chinese

����XML���ݳ���.
.

MessageId=0x3
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_LOAD_ROOT
Language=English
It failed to load xml root
.
Language=Chinese

����XML�е�root����.
.

MessageId=0x4
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_SAVE_FILE
Language=English
It failed to save xml file
.
Language=Chinese

����XML�ļ�����.
.

MessageId=0x5
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_GEN_TEXT
Language=English
It failed to gen text in xml.
.
Language=Chinese

����xml����ʱ����.
.

MessageId=0x6
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_PARENT_NODE_IS_NULL
Language=English
The parent node is null in xml.
.
Language=Chinese

��xml�У����ӵ�Ϊnull
.

MessageId=0x7
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_CURRENT_NODE_IS_NULL
Language=English
The current node is null in xml.
.
Language=Chinese

��xml�У���ǰ�ӵ�Ϊnull
.

MessageId=0x8
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_REMOVE_NODE
Language=English
It failed to remove node in xml.
.
Language=Chinese

��xml�У��Ƴ��ӵ�ʧ��.
.

MessageId=0x9
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_GET_NODE_NAME
Language=English
It failed to get node name in xml.
.
Language=Chinese

��xml�У���ȡ��ǰ�ӵ�����ʧ��.
.

MessageId=0xa
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_GET_NODE_TEXT
Language=English
It failed to get node text in xml.
.
Language=Chinese

��xml�У���ȡ��ǰ�ӵ�����ʧ��.
.

MessageId=0xb
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_SET_NODE_TEXT
Language=English
It failed to set node text in xml.
.
Language=Chinese

��xml�У����õ�ǰ�ӵ�����ʧ��.
.

MessageId=0xc
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_VALUE_STREAM_ERROR
Language=English
The stream is error in xml.
.
Language=Chinese

����xmlʱ��stream����
.

MessageId=0xd
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_XMLMANAGER_EXPECTED
Language=English
The xmlmanger is null.
.
Language=Chinese

xmlmanagerû�г�ʼ��.
.

MessageId=0xe
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_SCOPE_STACK_IS_EMPTY
Language=English
The scope stack is empty in xml.
.
Language=Chinese

����xmlʱ��scope stackΪ��.
.

MessageId=0xf
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_INIT_CURSOR
Language=English
It failed to init cursor in xml.
.
Language=Chinese

����xmlʱ����ʼ��cursorʧ��.
.

MessageId=0x10
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_LOAD_DEST_DOM_ROOT
Language=English
It failed to load dest dom's root in xml.
.
Language=Chinese

����xmlʱ������Ŀ��dom's rootʧ��.
.

MessageId=0x11
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_SET_DEST_DOM_VALUE
Language=English
It failed to set dest dom's value in xml.
.
Language=Chinese

����xmlʱ���趨Ŀ��dom's valueʧ��.
.

MessageId=0x12
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_COPY_NODE_TO_DEST_DOM
Language=English
It failed to copy node to dest dom in xml.
.
Language=Chinese

����xmlʱ�����Ƶ�ǰ�ӵ㵽dest domʧ��.
.

MessageId=0x13
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_INVALID_CURSOR_STATE
Language=English
the cursor is in invalid state in xml.
.
Language=Chinese

����xmlʱ��cursor��״̬����ȷ.
.


MessageId=0x20
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_FAIL_TO_LOAD_FILE
Language=English
It failed to load json file
.
Language=Chinese

����json�ļ�����.
.

MessageId=0x21
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_FAIL_TO_LOAD_TEXT
Language=English
It failed to load json text.
.
Language=Chinese

����json���ݳ���.
.

MessageId=0x22
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_FAIL_TO_LOAD_ROOT
Language=English
It failed to load json's root
.
Language=Chinese

����json�е�root����.
.

MessageId=0x23
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_FAIL_TO_SAVE_FILE
Language=English
It failed to save json file
.
Language=Chinese

����json�ļ�����.
.

MessageId=0x24
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_PARENT_NODE_IS_NULL
Language=English
The parent node is null in json.
.
Language=Chinese

��json�У����ӵ�Ϊnull
.

MessageId=0x25
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_CURRENT_NODE_IS_NULL
Language=English
The current node is null in json.
.
Language=Chinese

��json�У���ǰ�ӵ�Ϊnull
.

MessageId=0x26
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_ROOT_NODE_IS_NULL
Language=English
The root node is null in json.
.
Language=Chinese

��json�У�root�ӵ�Ϊ��.
.

MessageId=0x27
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_EXPECT_STRING_TYPE
Language=English
It expected the string type in json.
.
Language=Chinese

��json�У���Ҫ�ַ�������.
.

MessageId=0x28
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_VALUE_STREAM_ERROR
Language=English
The stream is error in json.
.
Language=Chinese

����jsonʱ��stream����
.

MessageId=0x29
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_FAIL_TO_GET_NODE_NAME
Language=English
It failed to get node name in json.
.
Language=Chinese

��json�У���ȡ��ǰ�ӵ�����ʧ��.
.

MessageId=0x2a
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_XML_FAIL_TO_GET_ROOT_NAME
Language=English
It failed to get root name in json.
.
Language=Chinese

��json�У���ȡ���ӵ�����ʧ��.
.

MessageId=0x2b
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_FAIL_TO_LOAD_DEST_DOM_ROOT
Language=English
It failed to load dest dom's root in json.
.
Language=Chinese

����jsonʱ������Ŀ��dom's rootʧ��.
.

MessageId=0x2c
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_FAIL_TO_INIT_CURSOR
Language=English
It failed to init cursor in json.
.
Language=Chinese

����jsonʱ����ʼ��cursorʧ��.
.

MessageId=0x2d
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_FAIL_TO_COPY_NODE_TO_DEST_DOM
Language=English
It failed to copy node to dest dom in json.
.
Language=Chinese

����jsonʱ�����Ƶ�ǰ�ӵ㵽dest domʧ��.
.

MessageId=0x2e
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_JSON_SCOPE_STACK_IS_EMPTY
Language=English
The scope stack is empty in json.
.
Language=Chinese

����jsonʱ��scope stackΪ��.
.

MessageId=0x40
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_KDOM_DATA_OUT_OF_RANGE
Language=English
The dom data is out of range.
.
Language=Chinese

dom data�����ݳ����޶�����.
.

MessageId=0x41
Severity=Error
Facility=KxEIdl
SymbolicName=E_KXEIDL_KDOM_DATA_TYPE_DO_NOT_SUPPORT_WRITING
Language=English
The data type is not support to write in dom.
.
Language=Chinese

��dom��ָ�����������Ͳ�֧��д��
.


; // KxEBase

MessageId=0x1
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_PLUGIN_NOT_FOUND
Language=English
It failed to find the plugin.
.
Language=Chinese

û���ҵ���Ӧ�Ĳ��SDK.
.

MessageId=0x2
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_PLUGIN_FUNCTION_NOT_FOUND
Language=English
It failed to find the function in the plugin.
.
Language=Chinese

��ָ����plugin��û���ҵ���Ӧ�ĺ���.
.

MessageId=0x3
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_CFG_NOT_INIT
Language=English
The config componenet wasn't initialied.
.
Language=Chinese

���������û�б���ʼ��.
.

MessageId=0x4
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_EVENT_NOT_INIT
Language=English
The event componenet wasn't initialied.
.
Language=Chinese

�¼������û�б���ʼ��.
.

MessageId=0x5
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_HTTP_NOT_INIT
Language=English
The HTTP componenet wasn't initialied.
.
Language=Chinese

HTTP�����û�б���ʼ��.
.

MessageId=0x6
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_PLUGIN_NOT_INIT
Language=English
The PLUGIN componenet wasn't initialied.
.
Language=Chinese

Plugin�����û�б���ʼ��.
.

MessageId=0x7
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_INVALID_PARAMETER
Language=English
The parameter is invalid.
.
Language=Chinese

������Ч.
.

MessageId=0x8
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_THREAD_NOT_INIT
Language=English
The thread component wasn't initialized.
.
Language=Chinese

�̹߳������û�г�ʼ��.
.

MessageId=0x9
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_NOT_ENOUGH_MEMORY
Language=English
It failed to allocate memory.
.
Language=Chinese

û���㹻���ڴ����.
.

MessageId=0xa
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_SERVICECALL_NOT_INIT
Language=English
The service call component wasn't initialized.
.
Language=Chinese

Service Call���û�г�ʼ��.
.

MessageId=0xb
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_SYSTEM_NOT_SUPPORT
Language=English
It can't support the system.
.
Language=Chinese

��ϵͳ��֧��.
.

MessageId=0xc
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_PLUGIN_PATH_LOADED
Language=English
The plugin path has been loaded.
.
Language=Chinese

ָ����plugin path�Ѿ����ع�.
.

MessageId=0xd
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_PLUGIN_PATH_NOT_LOADED
Language=English
The plugin path doesn't have been loaded.
.
Language=Chinese

ָ����plugin·��û�м���
.

MessageId=0xe
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_ACTIVITY_NOT_INIT
Language=English
The activity stat component is not initialized.
.
Language=Chinese

��Ծ��ͳ�����û�б���ʼ��
.

MessageId=0xf
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_ACTIVITY_INITED
Language=English
The activity stat component is initialized.
.
Language=Chinese

��Ծ��ͳ������Ѿ�����ʼ��
.

MessageId=0x10
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_FUNCTION_NOT_IMPLEMENTED
Language=English
The function is not implemented.
.
Language=Chinese

ָ���ĺ���û��ʵ��
.

MessageId=0x11
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_SERVICE_CAN_NOT_UNINSTALL
Language=English
The service can't be uninstalled.
.
Language=Chinese

���񻹲��ܱ�ж��
.

MessageId=0x12
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_INITED
Language=English
The kxebase is initied.
.
Language=Chinese

kxebase�Ѿ�����ʼ��
.

MessageId=0x13
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_NOT_INITED
Language=English
The kxebase is not initied.
.
Language=Chinese

kxebaseδ����ʼ��.
.

MessageId=0x14
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_SERVICE_CAN_NOT_STOPPED
Language=English
The service can't be stopped.
.
Language=Chinese

���񻹲��ܱ�ֹͣ
.

MessageId=0x15
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_ALL_SP_INITIALIZE_FAILED
Language=English
The service must terminate because none of the SPs was initialized successfully.
.
Language=Chinese

���� SP ��û�г�ʼ���ɹ����·��������ֹ
.

MessageId=0x16
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_ALL_SP_START_FAILED
Language=English
No service provider in the provider list started successfully.
.
Language=Chinese

���� SP ��û�������ɹ����·��������ֹ
.

MessageId=0x17
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_DLL_PATH_NOT_ACCQUIRED_FROM_CONFIGURATION_FILE
Language=English
It failed to accquire kxebase.dll's registry path from the configuration file 'kxecommon.dat'.
.
Language=Chinese

�������ļ� kxecommon.dat �ж�ȡ kxebase.dll ��ע���·��ʧ��
.

MessageId=0x18
Severity=Error
Facility=KxEBase
SymbolicName=E_KXEBASE_START_SERVICE_STOPPED
Language=English
Service auto stop when start service.
.
Language=Chinese

��������ʱ�����Զ���ֹ 
.

; // KxECfg

MessageId=0x1
Severity=Error
Facility=KxECfg
SymbolicName=E_KXECFG_VALUE_NOT_CORRECT
Language=English
The value in registry is not correct.
.
Language=Chinese

ע����е�valueֵ����ȷ
.

MessageId=0x2
Severity=Error
Facility=KxECfg
SymbolicName=E_KXECFG_KXENGINE_CONFIG_PATH_NOT_ACCQUIRED_FROM_CONFIGURATION_FILE
Language=English
It failed to accquire KXENGINE's registry path from the configuration file 'kxecommon.dat'.
.
Language=Chinese

�������ļ� kxecommon.dat �ж�ȡ������������ʼ·��(�� KXENGINE )��ע���·��ʧ��
.

; // KxEThread

MessageId=0x1
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_INVALID_HANDLE
Language=English
The job handle is invalid.
.
Language=Chinese

�����Job�����Ч.
.

MessageId=0x2
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_FINISHED
Language=English
The target job is finished.
.
Language=Chinese

ָ����Job�Ѿ��������.
.

MessageId=0x3
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_READY
Language=English
The target job is ready.
.
Language=Chinese

ָ����Job�Ѿ�׼����.
.

MessageId=0x4
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_RUNNING
Language=English
The job is running.
.
Language=Chinese

ָ����Job��������.
.

MessageId=0x5
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_ERROR
Language=English
The target job is in error state.
.
Language=Chinese

ָ���Job�Ѿ�����,�޷�����.
.

MessageId=0x6
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_WAIT_NUMBER_EXCEED
Language=English
The number of job to wait is exceed 64.
.
Language=Chinese

��Ҫ�ȴ���Job����������64��
.

MessageId=0x7
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_CLOSED
Language=English
The job is closed.
.
Language=Chinese

ָ����Job�Ѿ��ر�.
.

MessageId=0x8
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_NOT_FINISHED
Language=English
The target job is not finished.
.
Language=Chinese

ָ����Job��û���������.
.

MessageId=0x9
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_NOT_READY
Language=English
The target job is not ready.
.
Language=Chinese

ָ����Jobδ׼����.
.

MessageId=0xa
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_NOT_RUNNING
Language=English
The job is not running.
.
Language=Chinese

ָ����Jobû������.
.

MessageId=0xb
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_IN_STOP_CMD
Language=English
The job has recved the stop command.
.
Language=Chinese

�Ѿ���ָ����Job������ֹͣ����
.

MessageId=0xc
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_IN_PAUSE_CMD
Language=English
The job has recved the pause command.
.
Language=Chinese

�Ѿ���ָ����Job��������ͣ����
.

MessageId=0xd
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_JOB_NOT_PAUSE_CMD
Language=English
The job didn't have recved the pause command.
.
Language=Chinese

û����ָ����Job���͹���ͣ����
.

MessageId=0xe
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_MANAGER_INITIALIZED
Language=English
The job manager is initialized.
.
Language=Chinese

�̹߳������Ѿ���ʼ��.
.

MessageId=0xf
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_MANAGER_UNINITIALIZED
Language=English
The job manager is uninitialized.
.
Language=Chinese

�̹߳������Ѿ�����ʼ��.
.

MessageId=0x10
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_MANAGER_STARTED
Language=English
The job manager is started.
.
Language=Chinese

�̹߳������Ѿ�����.
.

MessageId=0x11
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_MANAGER_STOPPED
Language=English
The job manager is stopped.
.
Language=Chinese

�̹߳������Ѿ�ֹͣ.
.

MessageId=0x12
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_THREAD_POOL_INITIALIZED
Language=English
The threadpool is initialized.
.
Language=Chinese

�̳߳��Ѿ���ʼ��.
.

MessageId=0x13
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_THREAD_POOL_UNINITIALIZED
Language=English
The threadpool is uninitialized.
.
Language=Chinese

�̳߳��Ѿ�����ʼ��.
.

MessageId=0x14
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_THREAD_POOL_STARTED
Language=English
The thread pool is started.
.
Language=Chinese

�̳߳��Ѿ�����.
.

MessageId=0x15
Severity=Error
Facility=KxEThread
SymbolicName=E_KXETHREAD_THREAD_POOL_STOPPED
Language=English
The threadpool is stopped.
.
Language=Chinese

�̳߳��Ѿ�ֹͣ.
.

; // KxEEvent
;
MessageId=0x1
Severity=Error
Facility=KxEEvent
SymbolicName=E_KXEEVENT_MANAGER_STOPPED
Language=English
The event manager is not startup.
.
Language=Chinese

�¼�������û������
.

MessageId=0x2
Severity=Error
Facility=KxEEvent
SymbolicName=E_KXEEVENT_MANAGER_STARTED
Language=English
The event manager is started.
.
Language=Chinese

�¼��������Ѿ�����.
.

MessageId=0x3
Severity=Error
Facility=KxEEvent
SymbolicName=E_KXEEVENT_EVENT_SUBSYSTEM_REGISTER_NOT_FOUND
Language=English
It can't found the subsystem id in register.
.
Language=Chinese

û���ҵ�ָ������ϵͳid
.

MessageId=0x4
Severity=Error
Facility=KxEEvent
SymbolicName=E_KXEEVENT_EVENTNOTIFY_STOPPED
Language=English
The event notify manager is stopped.
.
Language=Chinese

�¼�֪ͨ�������Ѿ�ֹͣ.
.

MessageId=0x5
Severity=Error
Facility=KxEEvent
SymbolicName=E_KXEEVENT_EVENTNOTIFY_STARTED
Language=English
The event notify manager is started.
.
Language=Chinese

�¼�֪ͨ�������Ѿ�����.
.

MessageId=0x6
Severity=Error
Facility=KxEEvent
SymbolicName=E_KXEEVENT_EVENT_REGISTER_ID_NOT_FOUND
Language=English
It can't found the register event id.
.
Language=Chinese

û���ҵ�ע���ָ���¼�id.
.

MessageId=0x7
Severity=Error
Facility=KxEEvent
SymbolicName=E_KXEEVENT_EVENT_REGISTER_NOTIFY_NOT_FOUND
Language=English
It can't found the register event notify pointer.
.
Language=Chinese

û���ҵ�ע���ָ���¼���Ӧ�ӿ�.
.

; // KxEHttp

MessageId=0x1
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_PORT_USED
Language=English
The port has been used.
.
Language=Chinese

ָ���˿��Ѿ���ռ��.
.

MessageId=0x2
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_URI_DISPATCH_NOT_FOUND
Language=English
The uri dispatch is not found.
.
Language=Chinese

û���ҵ�ָ����uri��dispatch.
.

MessageId=0x3
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_INITIALIZED
Language=English
The http is initialized.
.
Language=Chinese

http�������Ѿ���ʼ��.
.

MessageId=0x4
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_UNINITIALIZED
Language=English
The http is uninitialized.
.
Language=Chinese

http�������Ѿ�����ʼ��.
.

MessageId=0x5
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_STARTED
Language=English
The http is started.
.
Language=Chinese

http�������Ѿ�����.
.

MessageId=0x6
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_STOPPED
Language=English
The http is stopped.
.
Language=Chinese

http�������Ѿ�ֹͣ.
.

MessageId=0x7
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_REQUEST_NOT_FOUND
Language=English
The http request is not found.
.
Language=Chinese

û���ҵ�ָ����http request.
.

MessageId=0x8
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_SERVICE_METHOD_NOT_FOUND
Language=English
It can't find the service's method.
.
Language=Chinese

û���ҵ���ָ�������ָ������.
.

MessageId=0x9
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_REQUEST_CONTROL_NOT_EXIST
Language=English
The request control is not exist.
.
Language=Chinese

ָ����request control������.
.

MessageId=0xa
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_AUTHORIZED_FAIL
Language=English
It failed to authorize.
.
Language=Chinese

��Ȩʧ��.
.

MessageId=0xb
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_QUERY_STRING_FAIL
Language=English
It failed to get query string in url.
.
Language=Chinese

��url���ѯQUERY_STRINGʧ��.
.

MessageId=0xc
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_REQUEST_METHOD_NOT_SUPPORT
Language=English
The request method is not support.
.
Language=Chinese

��֧��ָ����http����ķ���
.

MessageId=0xd
Severity=Error
Facility=KxEHttp
SymbolicName=E_HTTP_CLIENT_READ_RESPONSE_FAIL
Language=English
It failed on reading http response.
.
Language=Chinese

http client�ڶ�ȡhttp response�ϳ���.
.

MessageId=0xe
Severity=Error
Facility=KxEHttp
SymbolicName=E_HTTP_CLIENT_PARASE_STATUS_FAIL
Language=English
It failed to parase the status line..
.
Language=Chinese

http client�ڽ���status lineʱ����
.

MessageId=0xf
Severity=Error
Facility=KxEHttp
SymbolicName=E_HTTP_CLIENT_PARASE_HEADER_FAIL
Language=English
It failed to parase the response header..
.
Language=Chinese

http client�ڽ���response headerʱ����
.

MessageId=0x10
Severity=Error
Facility=KxEHttp
SymbolicName=E_HTTP_CLIENT_READ_SOCKET_FAIL
Language=English
It failed to read socket.
.
Language=Chinese

http client�ڶ�ȡsocket����ʱ����.
.

MessageId=0x11
Severity=Error
Facility=KxEHttp
SymbolicName=E_HTTP_CLIENT_READ_BODY_FAIL
Language=English
It failed to read body.
.
Language=Chinese

http client�ڻ��body����ʱ����.
.

MessageId=0x12
Severity=Error
Facility=KxEHttp
SymbolicName=E_HTTP_CLIENT_READ_CHUNKEDBODY_FAIL
Language=English
failed to read a 'Transfer-Encoding: chunked' response body
.
Language=Chinese

http client�ڻ��'Transfer-Encoding: chunked' response body����ʱ����.
.

MessageId=0x13
Severity=Error
Facility=KxEHttp
SymbolicName=E_HTTP_CLIENT_NOT_READ_RESPONSE
Language=English
we haven't started reading the response.
.
Language=Chinese

��û�п�ʼ��response.
.

MessageId=0x14
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_EXCEED_POST_DATA_SIZE
Language=English
The post data size is exceed.
.
Language=Chinese

POST�����ݵĴ�С���������ֵ.
.

MessageId=0x15
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_REQUEST_STATUS_NOT_CORRECT
Language=English
The request status may be in dispatching, but recv the data.
.
Language=Chinese

���������ڷ���ȴ�յ����µ�����.
.

MessageId=0x16
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_SECURITY_CODE_NOT_APPENDED
Language=English
The security code not appended in the request data.
.
Language=Chinese

����������û�а�����֤��
.

MessageId=0x17
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_INVALID_SECURITY_CODE
Language=English
The security code in the request data is invalid.
.
Language=Chinese

���������а�������֤����Ч
.

MessageId=0x18
Severity=Error
Facility=KxEHttp
SymbolicName=E_KXEHTTP_REQUEST_GET_METHOD_WITH_DATA
Language=English
The request is get, but with data.
.
Language=Chinese

HTTP��GET����ȴ����������.
.

; // KxEScanApi

; // KxEScanSystem

MessageId=0x1
Severity=Error
Facility=KSE
SymbolicName=E_KSE_OUT_OF_RANGE
Language=English
Out of range.
.
Language=Chinese
Խ��.
.

MessageId=0x2
Severity=Error
Facility=KSE
SymbolicName=E_KSE_INVALID_KSE_HANDLE
Language=English
Invalid handle.
.
Language=Chinese
��Ч���.
.

MessageId=0x3
Severity=Error
Facility=KSE
SymbolicName=E_KSE_DLL_CAN_NOT_BE_UNLOAD_SAFELY
Language=English
The dll can not be unload safely.
.
Language=Chinese
DLL���ܱ���ȫж��.
.

MessageId=0x100
Severity=Error
Facility=KSE
SymbolicName=E_KSE_TASK_EXIST
Language=English
Task Exit.
.
Language=Chinese
Task Exit.
.

MessageId=0x101
Severity=Error
Facility=KSE
SymbolicName=E_KSE_TASK_IS_ACTIVE
Language=English
The Task is active.
.
Language=Chinese
The Task is active.
.

MessageId=0x102
Severity=Error
Facility=KSE
SymbolicName=E_KSE_UNKNOWN_CREATION_DISPOSITION
Language=English
Unknown creation disposition.
.
Language=Chinese
Unknown creation disposition.
.

MessageId=0x200
Severity=Error
Facility=KSE
SymbolicName=E_KSE_STATUS_OBJ_NOT_FOUND
Language=English
The status object can not be found.
.
Language=Chinese
�Ҳ���״̬����.
.

MessageId=0x201
Severity=Error
Facility=KSE
SymbolicName=E_KSE_STATUS_OBJ_NOT_CREATE
Language=English
The status object can not be created.
.
Language=Chinese
�޷�����״̬����.
.

MessageId=0x202
Severity=Error
Facility=KSE
SymbolicName=E_KSE_UNSUPPORTED_TARGET_TYPE
Language=English
The target type is unsupported.
.
Language=Chinese
��֧�ֵ�Ŀ������.
.

MessageId=0x203
Severity=Error
Facility=KSE
SymbolicName=E_KSE_UNSUPPORTED_OBJ_TYPE
Language=English
The object type is unsupported.
.
Language=Chinese
��֧�ֵĶ�������.
.

MessageId=0x204
Severity=Error
Facility=KSE
SymbolicName=E_KSE_UNABLE_TO_GET_DATA_FROM_STAT
Language=English
Unable to get data from status.
.
Language=Chinese
�޷���״̬������ȡ������.
.

MessageId=0x205
Severity=Error
Facility=KSE
SymbolicName=E_KSE_COPY_INTERRUPTED
Language=English
This copy operation is interrupted.
.
Language=Chinese
���Ʋ������ж�.
.

MessageId=0x301
Severity=Error
Facility=KSE
SymbolicName=E_KSE_DATA_PROPERTY_NOT_FOUND
Language=English
The data property is not found.
.
Language=Chinese
�������Բ�����.
.

MessageId=0x302
Severity=Error
Facility=KSE
SymbolicName=E_KSE_COMPONENT_NOT_INIT
Language=English
The component is not initialized.
.
Language=Chinese
���δ����ʼ��.
.

MessageId=0x303
Severity=Error
Facility=KSE
SymbolicName=E_KSE_EMPTY_VIRTUAL_PATH
Language=English
The virtual path is empty.
.
Language=Chinese
����·��Ϊ��.
.

MessageId=0x401
Severity=Error
Facility=KSE
SymbolicName=E_KSE_TASK_IS_STOPPED
Language=English
The task is stopped.
.
Language=Chinese
The task is stopped.
.

MessageId=0x401
Severity=Success
Facility=KSE
SymbolicName=S_KSE_TASK_IS_STOPPED
Language=English
The task is stopped.
.
Language=Chinese
The task is stopped.
.

MessageId=0x501
Severity=Error
Facility=KSE
SymbolicName=E_KSE_ADDON_SCANNER_CONFLICT
Language=English
The scanner addons are conflict.
.
Language=Chinese
ɨ���������ͻ.
.

MessageId=0x502
Severity=Error
Facility=KSE
SymbolicName=E_KSE_ADDON_PROCESSOR_CONFLICT
Language=English
The processor addons are conflict.
.
Language=Chinese
�����������ͻ
.

MessageId=0x503
Severity=Error
Facility=KSE
SymbolicName=E_KSE_ADDON_SCAN_STATUS_CONFLICT
Language=English
The scan status addons are conflict.
.
Language=Chinese
ɨ��״̬�����ͻ.
.

MessageId=0x504
Severity=Error
Facility=KSE
SymbolicName=E_KSE_SOLUTION_TARGET_CONFLICT
Language=English
The solution target is conflict.
.
Language=Chinese
The solution target is conflict.
.

MessageId=0x505
Severity=Error
Facility=KSE
SymbolicName=E_KSE_SOLUTION_TARGET_IS_TOO_DEEP
Language=English
The solution target is too deep.
.
Language=Chinese
The solution target is too deep.
.

MessageId=0x506
Severity=Error
Facility=KSE
SymbolicName=E_KSE_FAIL_TO_OPEN_SOLUTION_FILE
Language=English
Fail to open solution file.
.
Language=Chinese
Fail to open solution file
.

MessageId=0x601
Severity=Error
Facility=KSE
SymbolicName=E_KSE_CHANNEL_EXIST
Language=English
The channel exist.
.
Language=Chinese
The channel exist.
.

MessageId=0x602
Severity=Error
Facility=KSE
SymbolicName=E_KSE_CHANNEL_DOSE_NOT_EXIST
Language=English
The channel does not exist.
.
Language=Chinese
The channel does not exist.
.

MessageId=0x603
Severity=Error
Facility=KSE
SymbolicName=E_KSE_CHANNEL_IS_DISABLED
Language=English
The channel is disabled.
.
Language=Chinese
The channel is disabled.
.

MessageId=0x701
Severity=Error
Facility=KSE
SymbolicName=E_KSE_ATTACHED_DATA_ITEM_NOT_EXIST
Language=English
The attached data item does not exist.
.
Language=Chinese
�������ݶ��󲻴���.
.

MessageId=0x1
Severity=Error
Facility=KSEScanner
SymbolicName=E_KSE_BAD_TARGET_TYPE
Language=English
The target type is bad.
.
Language=Chinese
�����Ŀ������.
.

MessageId=0x2
Severity=Error
Facility=KSEScanner
SymbolicName=E_KSE_NOT_SUPPORT_TARGET
Language=English
The target is unsupported.
.
Language=Chinese
��֧�ֵ�Ŀ������.
.

MessageId=0x3
Severity=Error
Facility=KSEScanner
SymbolicName=E_KSE_DODISTRIBUTE
Language=English
The DoDistribute function failed.
.
Language=Chinese
DoDistribute����ʧ��.
.

MessageId=0x4
Severity=Error
Facility=KSEScanner
SymbolicName=E_KSE_INVALID_TARGET_ID
Language=English
The target ID is invalid.
.
Language=Chinese
��Ч��Ŀ��IDֵ.
.

MessageId=0x5
Severity=Error
Facility=KSEScanner
SymbolicName=E_KSE_AUTORUN_DLL_FAIL
Language=English
The kaeautorunex.dll error.
.
Language=Chinese
kaeautorunex.dllģ����ش���
.

MessageId=0x6
Severity=Error
Facility=KSEScanner
SymbolicName=E_KSE_NOT_SUPPORTED_EVN_VAR
Language=English
This environment variable is not supported.
.
Language=Chinese
��֧�ֵĻ�������.
.

MessageId=0x7
Severity=Error
Facility=KSEScanner
SymbolicName=E_KSE_NOT_IMPLEMENT_GETEVVBYSELF_FUNC
Language=English
This environment variable used a not implemented GetEVVBySelf function.
.
Language=Chinese
�˻��������õ���һ��û��ʵ�ֵ�ȡֵ����.
.

MessageId=0x1
Severity=Error
Facility=KSEFo
SymbolicName=E_KSE_FILE_NOT_EXIST
Language=English
The file does not exist.
.
Language=Chinese
�ļ�������.
.

MessageId=0x2
Severity=Error
Facility=KSEFo
SymbolicName=E_KSE_CAN_NOT_OPEN_FILE
Language=English
The file can not be opened.
.
Language=Chinese
���ļ�ʧ��.
.

MessageId=0x3
Severity=Error
Facility=KSEFo
SymbolicName=E_KSE_CAN_NOT_DELETE_FILE
Language=English
The file can not be deleted.
.
Language=Chinese
ɾ���ļ�ʧ��.
.

MessageId=0x4
Severity=Error
Facility=KSEFo
SymbolicName=E_KSE_TEMP_FILE_OUT_OF_BUFF_SIZE
Language=English
The temp file buffer size is too small.
.
Language=Chinese
��ʱ�ļ����ڴ滺����������
.

MessageId=0x1
Severity=Error
Facility=KSEFileEngine
SymbolicName=E_KSE_GET_FILE_TYPE
Language=English
GetFileType function failed.
.
Language=Chinese
GetFileType����ʧ��.
.

MessageId=0x2
Severity=Error
Facility=KSEFileEngine
SymbolicName=E_KSE_BWM_SCAN
Language=English
BWM scan failed.
.
Language=Chinese
�ڰ׻�ɨ��ʧ��.
.

MessageId=0x3
Severity=Error
Facility=KSEFileEngine
SymbolicName=E_KSE_BWM_ENDLESS_RESCAN
Language=English
Maybe BWM had a bug, that lead endless rescaning.
.
Language=Chinese
���ܺڰ׻���bug��������ֹ�����ظ�ɨ�������.
.

MessageId=0x4
Severity=Error
Facility=KSEFileEngine
SymbolicName=E_KSE_BWMCALLER_INIT_FAILED
Language=English
KSEBWMCaller Init function failed.
.
Language=Chinese
�ڰ׻�����ģ��ĳ�ʼ����������ʧ��.
.

MessageId=0x101
Severity=Error
Facility=KSEFileEngine
SymbolicName=E_KSE_EXTRACT_GET_ARC_TYPE
Language=English
GetArcType function failed.
.
Language=Chinese
GetArcType����ʧ��.
.

MessageId=0x102
Severity=Error
Facility=KSEFileEngine
SymbolicName=E_KSE_EXTRACT_DO_EXTRACT
Language=English
DoExtract function failed.
.
Language=Chinese
DoExtract����ʧ��.
.

MessageId=0x103
Severity=Error
Facility=KSEFileEngine
SymbolicName=E_KSE_EXTRACT_HEAD_FAIL
Language=English
Extract head failed.
.
Language=Chinese
��ѹͷ��Ϣʧ��.
.

MessageId=0x104
Severity=Error
Facility=KSEFileEngine
SymbolicName=E_KSE_EXTRACT_DATA_FAIL
Language=English
Extract data failed.
.
Language=Chinese
��ѹ������Ϣʧ��.
.

MessageId=0x201
Severity=Error
Facility=KSEFileEngine
SymbolicName=E_KSE_UNPACK_GET_SHELL_TYPE
Language=English
GetShellType function failed.
.
Language=Chinese
GetShellType����ʧ��.
.

MessageId=0x202
Severity=Error
Facility=KSEFileEngine
SymbolicName=E_KSE_UNPACK_DO_UNPACK
Language=English
DoUnpack function failed.
.
Language=Chinese
DoUnpack����ʧ��.
.

MessageId=0x1
Severity=Error
Facility=KSEPluginSDK
SymbolicName=E_KSE_SDK_BAD_POINTER
Language=English
A bad pointer, like NULL, be passed to function.
.
Language=Chinese
����������һ�������õ�ָ�룬��NULL��
.

MessageId=0x2
Severity=Error
Facility=KSEPluginSDK
SymbolicName=E_KSE_SDK_NOT_INITIALIZE
Language=English
The SDK module has not been initialized.
.
Language=Chinese
SDKģ��û�б���ʼ����
.

MessageId=0x3
Severity=Error
Facility=KSEPluginSDK
SymbolicName=E_KSE_SDK_BAD_PARAMETER
Language=English
The function be passed a bad parameter.
.
Language=Chinese
�����������˴��������
.

MessageId=0x4
Severity=Error
Facility=KSEPluginSDK
SymbolicName=E_KSE_SDK_INVALID_VERSION
Language=English
The version is not invalid.
.
Language=Chinese
�汾����ȷ��
.


MessageId=0x1
Severity=Error
Facility=KSENetDet
SymbolicName=E_KSE_NET_DET_FAILED
Language=English
The net detecting failed.
.
Language=Chinese
������ʧ�ܡ�
.


; //	KWFS=0xF1:FACILITY_WFS

MessageId=0x1
Severity=Error
Facility=KWFS
SymbolicName=E_KW_NEW_OBJECT_FAILED
Language=English
It's failed to new object.
.
Language=Chinese
�������ʧ��
.
	
MessageId=0x2
Severity=Error
Facility=KWFS
SymbolicName=E_KW_FDB_INITIALIZE_ERROR
Language=English
It's failed to initialize fdb.
.
Language=Chinese
��ʼ�����������ݿ�ʧ��
.
	
MessageId=0x3
Severity=Error
Facility=KWFS
SymbolicName=E_KW_FV_INITIALIZE_ERROR
Language=English
It's failed to initialize fv.
.
Language=Chinese
��ʼ���ļ���֤ģ��ʧ��
.
	
MessageId=0x4
Severity=Error
Facility=KWFS
SymbolicName=E_KW_CALL_FM_FAILE
Language=English
It's failed to call FM SDK.
.
Language=Chinese
�����ļ����SDKʧ��
.
	
MessageId=0x5
Severity=Error
Facility=KWFS
SymbolicName=E_KW_CREATE_DBFILE_ERROR
Language=English
It's failed to create DB file.
.
Language=Chinese
����������ݿ��ļ�ʧ��
.
	
MessageId=0x6
Severity=Error
Facility=KWFS
SymbolicName=E_KWFV_START_THREAD_FAILED
Language=English
It's failed to start thread.
.
Language=Chinese
�����߳�ʧ��
.

MessageId=0x7
Severity=Error
Facility=KWFS
SymbolicName=E_KW_NOT_INIT
Language=English
Need initialize first.
.
Language=Chinese
���ȳ�ʼ��
.

MessageId=0x8
Severity=Error
Facility=KWFS
SymbolicName=E_KWFV_VERIFY_FILE_FAILED
Language=English
It's failed to add file to verify.
.
Language=Chinese
��֤�ļ�ʧ��
.

MessageId=0x9
Severity=Error
Facility=KWFS
SymbolicName=E_KW_UNSUCCESS
Language=English
failed,unsuccess
.
Language=Chinese
û�ɹ���ʧ����
.

MessageId=0xa
Severity=Error
Facility=KWFS
SymbolicName=E_KW_NOT_STOP
Language=English
Need stop first
.
Language=Chinese
�����ֹͣ
.

; //	KWFDB=0xF2:FACILITY_WFS_FDB

MessageId=0x1
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_INVALID_PARAMETER
Language=English
The parameter is invalid
.
Language=Chinese
����ı���
.

MessageId=0x2
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_FILE_ALREADY_EXISTS
Language=English
The file already exists.
.
Language=Chinese
�ļ��Ѿ�����
.

MessageId=0x3
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_GET_FILE_INFO
Language=English
It's failed to get file information.
.
Language=Chinese
��ȡ�ļ���Ϣʧ��
.
MessageId=0x4
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_FILE_NOT_FOUND
Language=English
The white file system connot find the file specified.
.
Language=Chinese
�޷�������ҵ�����ļ�
.

MessageId=0x5
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_FILE_TOO_LARGE
Language=English
The file size exceeds the limit allowed and cannot be saved.
.
Language=Chinese
�ļ���С��������
.

MessageId=0x6
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_ADD_FILE_FAILED
Language=English
It's failed to add the file information into file DB.
.
Language=Chinese
����ļ���Ϣʧ��
.

MessageId=0x7
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_FIND_FILE_FAILED
Language=English
It's failed to find the file information in file DB.
.
Language=Chinese
�����ݿ����޷��ҵ����ļ�����Ϣ
.
	
MessageId=0x8
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_DELETE_FILE_FAILED
Language=English
it's failed to delete file information.
.
Language=Chinese
ɾ���ļ���Ϣʧ��
.

MessageId=0x9
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_UPDATE_FILE_FAILED
Language=English
it's failed to update file information.
.
Language=Chinese
�����ļ���Ϣʧ��
.

MessageId=0xa
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_CALL_DB_FAILED
Language=English
It's failed to call DB.
.
Language=Chinese
���ݿ����ʧ��
.

MessageId=0xb
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_DB_NOT_RETURN_DATA
Language=English
The calling of DB is return none data.
.
Language=Chinese
���ݿ����û�з�������
.

MessageId=0xc
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_DB_EMPTY
Language=English
The file information DB is empty.
.
Language=Chinese
���ݿ�Ϊ��
.

MessageId=0xd
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_FILE_INFO_EXPIRE
Language=English
The file information in DB is out of time.
.
Language=Chinese
�ļ���Ϣ�Ѿ�����
.

MessageId=0xe
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFV_OPEN_FILE_FAILED
Language=English
It is failed to open file.
.
Language=Chinese
���ļ�ʧ��
.

MessageId=0xf
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_END_OF_DB
Language=English
It is end of DB
.
Language=Chinese
�Ѿ������ݿ��β.
.

MessageId=0x10
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_FILE_NEED_VERIFY
Language=English
Please verify the file first
.
Language=Chinese
������֤�ļ�
.

MessageId=0x11
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_NEED_START
Language=English
Please start the thread first
.
Language=Chinese
�뿪���߳�
.

MessageId=0x12
Severity=Error
Facility=KWFDB
SymbolicName=E_KWFDB_COMPRESS_FAILED
Language=English
Compress out of bounds
.
Language=Chinese
ѹ����ѹԽ��
.

;//	KWFDB=0xF3:FACILITY_WFS_SP

MessageId=0x1
Severity=Error
Facility=KWSP
SymbolicName=E_KWSP_INITIALIZE_FAILED
Language=English
It's failed to initialize .
.
Language=Chinese
������ϵͳ�����ṩ�߳�ʼ��ʧ��
.

MessageId=0x2
Severity=Error
Facility=KWSP
SymbolicName=E_KWSP_START_FAILED
Language=English
It's failed to start .
.
Language=Chinese
������ϵͳ�����ṩ�߿�ʼ����ʧ��
.


;//KxEFM=0xA1:FACILITY_FILEMON

MessageId=0x1
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_LOADDRIVER_FAILED
Language=English
It's failed to load driver.
.
Language=Chinese
��������ʧ��
.

MessageId=0x2
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_GETSHAREMEM_FAILED
Language=English
It's failed to get share memory.
.
Language=Chinese
��ȡ�����ڴ�ʧ��
.

MessageId=0x3
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_INITSCANENGINE_FAILED
Language=English
It's failed to init scan engine.
.
Language=Chinese
��ʼ������ʧ��
.

MessageId=0x4
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_ERROR_INVALID_PARAMETER
Language=English
Parameter is invlided.
.
Language=Chinese
��������ȷ
.

MessageId=0x5
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_ERROR_INITIALIZE_FAILED
Language=English
It's failed to initialize.
.
Language=Chinese
�ļ������ϵͳ��ʼ��ʧ��
.

MessageId=0x6
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_ERROR_UNINITIALIZE_FAILED
Language=English
It's failed to uninitialize.
.
Language=Chinese
�ļ������ϵͳ����ʼ��ʧ��
.

MessageId=0x7
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_STARTFILEMON_FAILED
Language=English
It's failed to startfilemon.
.
Language=Chinese
�ļ������ϵͳ����ʧ��
.

MessageId=0x8
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_IS_ALREADY_STOP
Language=English
It's already stop.
.
Language=Chinese
�ļ������ϵͳ�Ѿ��ر�
.

MessageId=0x9
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_IS_NOT_INIT
Language=English
It's not init.
.
Language=Chinese
�ļ������ϵͳû�н��г�ʼ��
.

MessageId=0xa
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_ADDFILTERPROCESSID_ERROR
Language=English
It's failed to add filter processid.
.
Language=Chinese
�ļ������ϵͳ��ӿ��Ž���IDʧ��
.

MessageId=0xb
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_REMOVFILTERPROCESSID_ERROR
Language=English
It's failed to remove filter processid.
.
Language=Chinese
�ļ������ϵͳ�Ƴ����Ž���IDʧ��
.

MessageId=0xc
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_WRITETEMPWHITELIST_ERROR
Language=English
It's failed to write temp whitelist.
.
Language=Chinese
�ļ������ϵͳ����̬������д����ʱ�ļ�ʧ��
.

MessageId=0xd
Severity=Error
Facility=KxEFM
SymbolicName=E_KXEFILEMON_FREEMD5TABLE_ERROR
Language=English
It's failed to free md5table.
.
Language=Chinese
�ļ������ϵͳ�����̬������ʧ��
.

;//KxEFMSP=0xA2:FACILITY_FILEMON_SP

MessageId=0x1
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_INITIALIZESERVICE_FAILED
Language=English
It's failed to initializeservice.
.
Language=Chinese
�ļ����SP��ʼ��ʧ��
.

MessageId=0x2
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_STARTFILEMON_FAILED
Language=English
It's failed to startfilemon.
.
Language=Chinese
�ļ����SP�����ļ����ʧ��
.

MessageId=0x3
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_STOPFILEMON_FAILED
Language=English
It's failed to stopfilemon.
.
Language=Chinese
�ļ����SPֹͣ�ļ����ʧ��
.

MessageId=0x4
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_FILEMONINTERFACE_ISNULL
Language=English
The FileMonInterface is null.
.
Language=Chinese
�ļ����SP��FileMonInterfaceΪ��
.

MessageId=0x5
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_QUERYFILEMON_ERROR
Language=English
It's failed to queryfilemon.
.
Language=Chinese
�ļ����SP��ѯ�ļ����״̬ʧ��
.

MessageId=0x6
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_SETFILEMONSETTING_ERROR
Language=English
It's failed to setfilemon.
.
Language=Chinese
�ļ����SP�����ļ�����Ƿ��������ʧ��
.

MessageId=0x7
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_ADDFILTERPROCESSID_ERROR
Language=English
It's failed to addfilterprocessid.
.
Language=Chinese
�ļ����SP��ӿ��Ž���IDʧ��
.

MessageId=0x8
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_REMOVEFILTERPROCESSID_ERROR
Language=English
It's failed to removefilterprocessid.
.
Language=Chinese
�ļ����SP�Ƴ����Ž���IDʧ��
.

MessageId=0x9
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_QUERYFILEMONSETTING_ERROR
Language=English
It's failed to queryfilemonsetting.
.
Language=Chinese
�ļ����SP��ѯ�Ƿ��������ʧ��
.

MessageId=0xA
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_QUERYFILEMONSCANINFO_ERROR
Language=English
It's failed to QueryFileMonScanInfo.
.
Language=Chinese
�ļ����SP��ѯ�����Ϣʧ��
.
MessageId=0xB
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_NOTIFYENGINEUPDATED_ERROR
Language=English
It's failed to NotifyEngineUpdated
.
Language=Chinese
�ļ����SP:֪ͨ�ļ����Engine(������������ļ�)������Ҫ�ؼ��ذ�����ʱʧ��
.
MessageId=0xC
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_CONFIG_TRUST_PATH_ERROR
Language=English
It's failed to ConfigTrustPath
.
Language=Chinese
�ļ����SP:�����û�����·��ʱʧ��
.
MessageId=0xD
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMONSP_CONFIG_TRUST_FILE_TYPE_ERROR
Language=English
It's failed to ConfigTrustFileType
.
Language=Chinese
�ļ����SP:�����û������ļ����ͣ����ݺ�׺�жϣ�ʱʧ��
.
MessageId=0xE
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMON_SET_WORK_MODE_ERROR
Language=English
It's failed to SetWorkMode
.
Language=Chinese
�ļ����SP:���ü����ϸ����ģʽʱʧ��
.
MessageId=0xF
Severity=Error
Facility=KxEFMSP
SymbolicName=E_KXEFILEMON_SWITCH_WORK_MODE_ERROR
Language=English
It's failed to SwitchWorkMode
.
Language=Chinese
�ļ����SP:�л���ع���ģʽʱʧ��
.
; // KxESCSP

MessageId=0x1
Severity=Error
Facility=KxESCSP
SymbolicName=E_KXE_SCSP_LOAD_XML_FAILED
Language=English
It's failed to load the xml file.
.
Language=Chinese
����xml�ļ�ʧ��
.

MessageId=0x2
Severity=Error
Facility=KxESCSP
SymbolicName=E_KXE_SCSP_BAD_XML_FILE
Language=English
The xml file is bad.
.
Language=Chinese
����xml�ļ�
.

MessageId=0x3
Severity=Error
Facility=KxESCSP
SymbolicName=E_KXE_SCSP_NOT_LOAD_CFG_FILE
Language=English
The config file has not been loaded.
.
Language=Chinese
δ���������ļ�
.

MessageId=0x4
Severity=Error
Facility=KxESCSP
SymbolicName=E_KXE_SCSP_NOT_LOAD_REG_INFO
Language=English
The registered product info has not been loaded.
.
Language=Chinese
δ���ز�Ʒע����Ϣ
.

MessageId=0x5
Severity=Error
Facility=KxESCSP
SymbolicName=E_KXE_SCSP_UNKNOWN_PRODUCT_ID
Language=English
The product id is unknowned.
.
Language=Chinese
δ֪��ƷID
.

MessageId=0x6
Severity=Error
Facility=KxESCSP
SymbolicName=E_KXE_SCSP_UNKNOWN_VIP_FUNC_ID
Language=English
The vip function id is unknowned.
.
Language=Chinese
δ֪VIP����ID
.

MessageId=0x7
Severity=Error
Facility=KxESCSP
SymbolicName=E_KXE_SCSP_INSTALL_PROCESS_EXIST
Language=English
The installing process already exist.
.
Language=Chinese
��װ����������
.

MessageId=0x8
Severity=Error
Facility=KxESCSP
SymbolicName=E_KXE_SCSP_CONFLICT_CFG_FILES
Language=English
The config file of the product is conflict with the config file of the Security Center.
.
Language=Chinese
��Ʒ�������ļ��밲ȫ���ĵ������ļ���ͻ��
.

MessageId=0x9
Severity=Error
Facility=KxESCSP
SymbolicName=E_KXE_SCSP_BAD_PARAMETER
Language=English
The parameter is invalid.
.
Language=Chinese
�Ƿ��ĵ��ò�����
.

MessageId=0xa
Severity=Error
Facility=KxESCSP
SymbolicName=E_KXE_SCSP_CFG_NOT_INSTALLED_PRODUCT
Language=English
The product which be configuring, has not been installed.
.
Language=Chinese
Ҫ���õĲ�Ʒû�а�װ
.


; // KxESRSP

MessageId=0x1
Severity=Error
Facility=KxESRSP
SymbolicName=E_KXESRSP_UUID_CONFLICT
Language=English
The UUID has been used.
.
Language=Chinese
��ʹ�õ�UUID��
.

MessageId=0x2
Severity=Error
Facility=KxESRSP
SymbolicName=E_KXESRSP_NOT_INITED
Language=English
The object has not been inited;
.
Language=Chinese
����δ����ʼ��
.

MessageId=0x3
Severity=Error
Facility=KxESRSP
SymbolicName=E_KXESRSP_INDEX_OUT_OF_RANGE
Language=English
The index is out of range.
.
Language=Chinese
����Խ��
.

MessageId=0x4
Severity=Error
Facility=KxESRSP
SymbolicName=E_KXESRSP_USER_STOP
Language=English
Stop by user.
.
Language=Chinese
�û�Ҫ��ȡ��
.

MessageId=0x5
Severity=Error
Facility=KxESRSP
SymbolicName=E_KXESRSP_SESSION_NUM_MAX_LIMIT
Language=English
The count of sessions has to be the max limit.
.
Language=Chinese
�Ự��Ŀ�ﵽ����
.

MessageId=0x1
Severity=Error
Facility=KxEBasicSP
SymbolicName=E_KXEBASIC_SERVICE_PROVIDER_STARTED
Language=English
The service provider is started.
.
Language=Chinese
ָ����SP�Ѿ�����
.

