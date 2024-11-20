
/************************************************************************
* @file      : ucipc.cpp
* @author    : WangBin5 <WangBin5.com>
* @date      : 26/11/2009 AM 11:53:11
* @brief     : 
*
* $Id: $
/************************************************************************/

#include <WinError.h>
#include "ucipc_tool.h"
#include "ucipc.h"
#include "md5.h"

#define UC_IPC_TIME_OUT				0x3000

//////////////////////////////////////////////////////////////////////////
#define UC_IPC_DRIVER_MARK          0x80000000  // ������������ʱ�ı��λ�����������֪ͨ�����������ʱ��
                                                // �����������Ͳ����Զ���Ǵ�λ

#define UC_IPC_DRIVER_NON			0x0		    // ����֪ͨ�룬�޲���
#define UC_IPC_DRIVER_BUF_SMALL		0x1		    // ����֪ͨ�룬buf̫С���Ѿ���Ӧ�ò����·���
#define UC_IPC_DRIVER_NEED_REPLY	0x2		    // �������͵�������ҪӦ�ò�ظ�
#define UC_IPC_DRIVER_ZERO_LEN   	0x3		    // Ӧ�ò㴫��ȥ�����ݴ�СΪ��
//////////////////////////////////////////////////////////////////////////

UcIpc::UcIpc()
{
	m_hSendEventC1 = NULL;
    m_hRecvEventC1 = NULL;
	m_pSendSAC1 = NULL;
    m_pRecvSAC1 = NULL;
	
	m_hSendEventC2 = NULL;
	m_hRecvEventC2 = NULL;
	m_pSendSAC2 = NULL;
	m_pRecvSAC2 = NULL;
	
	m_hMapFile = NULL;
	m_pMapSA = NULL;

	m_pEndSA = NULL;
	m_hEndEvent = NULL;

	m_pvParam = NULL;
	m_BufSize = 0;
    m_BufSize2 = 0;

	m_pMapFileBuf = NULL;

    m_nIpcAddr = 0xFFFFFFFF;

	m_bInitFlag = FALSE;

    m_bCloseStatus = TRUE;
	m_hWork = NULL;
}

BOOL
UcIpc::InitIpc(
	IN ULONG nIpcAddr,
	IN KucPCALLBACK pCallbackRoutine,
	IN PVOID pvParam,
	IN ULONG ulSize,
    IN ULONG ulSize2
	)
{
	BOOL			bRet = FALSE;
	WCHAR			wProtocolType[MAX_PATH] = {0};
	std::wstring	wstTemp;
	DWORD			dwThreadId = 0;

    if (m_bInitFlag) {return TRUE;}

	swprintf(wProtocolType, L"%d", nIpcAddr);

    m_pSendSAC1 = KAVCreateSecurityAttribute();
    m_pRecvSAC1 = KAVCreateSecurityAttribute();

	m_pSendSAC2 = KAVCreateSecurityAttribute();
	m_pRecvSAC2 = KAVCreateSecurityAttribute();

	m_pMapSA = KAVCreateSecurityAttribute();

	m_pEndSA = KAVCreateSecurityAttribute();
    if (!m_pSendSAC1 || !m_pRecvSAC1 ||
		!m_pSendSAC2 || !m_pRecvSAC2 || !m_pMapSA || !m_pEndSA)
    {
        goto _Exit_;
    }

	wstTemp = UC_IPC_UNINIT_EVENT;
	wstTemp += wProtocolType;
    m_hEndEvent = ::CreateEventW(m_pSendSAC1, FALSE, FALSE, wstTemp.c_str());
	if (!m_hEndEvent) {goto _Exit_;}

	// Channel 1
	wstTemp = UC_IPC_EVENT_SEND_C1;
	wstTemp += wProtocolType;
    m_hSendEventC1 = ::CreateEventW(m_pSendSAC1, FALSE, FALSE, wstTemp.c_str());
    if (!m_hSendEventC1)
    {
        m_hSendEventC1 = ::OpenEventW(EVENT_ALL_ACCESS, FALSE, wstTemp.c_str());
        if (!m_hSendEventC1) {goto _Exit_;}
    }
    
    wstTemp = UC_IPC_EVENT_RECV_C1;
	wstTemp += wProtocolType;
    m_hRecvEventC1 = ::CreateEventW(m_pRecvSAC1, FALSE, TRUE, wstTemp.c_str());
    if (!m_hRecvEventC1)
    {
        m_hRecvEventC1 = ::OpenEventW(EVENT_ALL_ACCESS, FALSE, wstTemp.c_str());
        if (!m_hRecvEventC1) {goto _Exit_;}
    }

	SetEvent(m_hRecvEventC1);

	// Channel 2
	wstTemp = UC_IPC_EVENT_SEND_C2;
	wstTemp += wProtocolType;
	m_hSendEventC2 = ::CreateEventW(m_pSendSAC2, FALSE, FALSE, wstTemp.c_str());
	if (!m_hSendEventC2)
	{
		m_hSendEventC2 = ::OpenEventW(EVENT_ALL_ACCESS, FALSE, wstTemp.c_str());
		if (!m_hSendEventC2) {goto _Exit_;}
	}

	wstTemp = UC_IPC_EVENT_RECV_C2;
	wstTemp += wProtocolType;
	m_hRecvEventC2 = ::CreateEventW(m_pRecvSAC2, FALSE, TRUE, wstTemp.c_str());
	if (!m_hRecvEventC2)
	{
		m_hRecvEventC2 = ::OpenEventW(EVENT_ALL_ACCESS, FALSE, wstTemp.c_str());
		if (!m_hRecvEventC2) {goto _Exit_;}
	}

    wstTemp = UC_IPC_FILEMAPNAME_C1;
    wstTemp += wProtocolType;
	m_bInitFlag = InitMap(wstTemp.c_str(), ulSize + ulSize2);
	if (!m_bInitFlag) {goto _Exit_;}

	m_hWork = CreateThread(
		NULL,
		0,
		UcIpc::CommunicationWorker,
		this,
		0,
		&dwThreadId
		);
	if (!m_hWork) {goto _Exit_;}
	
    m_nIpcAddr = nIpcAddr;
	m_BufSize = ulSize;
    m_BufSize2 = ulSize2;
	m_pCallbackRoutine = pCallbackRoutine;
	m_pvParam = pvParam;
	m_bInitFlag = TRUE;
	
_Exit_:
	if (!m_bInitFlag)
	{
		m_bInitFlag = TRUE;
		Uninit();	
	}
	
    return m_bInitFlag;
}

BOOL
UcIpc::InitMap(
	IN LPCWSTR szMapName,
	IN ULONG ulSize
    )
{
    m_hMapFile = ::CreateFileMappingW(
        INVALID_HANDLE_VALUE,               // use paging file
        m_pMapSA,                           // default security 
        PAGE_READWRITE,                     // read/write access
        0,                                  // max. object size 
        ulSize,							// buffer size  
        szMapName);							// name of mapping object
	if (!m_hMapFile)
	{
		m_hMapFile = ::OpenFileMappingW(
			FILE_MAP_ALL_ACCESS,            // read/write access
			TRUE,                           // do not inherit the name
			szMapName);						// name of mapping object
	}
	if (!m_hMapFile) {return FALSE;}
	
    m_pMapFileBuf = (BYTE*) ::MapViewOfFile(
		m_hMapFile,							// handle to map object
        FILE_MAP_ALL_ACCESS,				// read/write permission
        0,                    
        0,                    
        ulSize);
	if (!m_pMapFileBuf) {return FALSE;}
	memset(m_pMapFileBuf, 0x0, ulSize);

	return TRUE;
}

BOOL 
UcIpc::Uninit(
	VOID
	)
{
	if (!m_bInitFlag)
	{
		return TRUE;
	}

	m_bInitFlag = FALSE;
	
	OutputDebugStringA("Now TerminateThread ucipc!\n");
	
	SetEvent(m_hEndEvent);
	if (m_hWork)
	{
		if (WAIT_OBJECT_0 != ::WaitForSingleObject(m_hWork, 500))
			::TerminateThread(m_hWork, 0);
		::CloseHandle(m_hWork);
		m_hWork = NULL;
	}

	if (m_pSendSAC1)
	{
		KAVFreeSecurityAttribute(m_pSendSAC1);
		m_pSendSAC1 = NULL;
	}
	
	if (m_pRecvSAC1)
	{
		KAVFreeSecurityAttribute(m_pRecvSAC1);
		m_pRecvSAC1 = NULL;
	}
	
	if (m_pSendSAC2)
	{
		KAVFreeSecurityAttribute(m_pSendSAC2);
		m_pSendSAC2 = NULL;
	}
	
	if (m_pRecvSAC2)
	{
		KAVFreeSecurityAttribute(m_pRecvSAC2);
		m_pRecvSAC2 = NULL;
	}
	
	if (m_pMapSA)
	{
		KAVFreeSecurityAttribute(m_pMapSA);
		m_pMapSA = NULL;
	}
	
	//////////////////////////////////////////////////////////////////////////
	
	if (m_hSendEventC1)
	{
		CloseHandle(m_hSendEventC1);
		m_hSendEventC1 = NULL;
	}
	
	if (m_hRecvEventC1)
	{
		CloseHandle(m_hRecvEventC1);
		m_hRecvEventC1 = NULL;
	}
	
	if (m_hSendEventC2)
	{
		CloseHandle(m_hSendEventC2);
		m_hSendEventC2 = NULL;
	}
	
	if (m_hRecvEventC2)
	{
		CloseHandle(m_hRecvEventC2);
		m_hRecvEventC2 = NULL;
	}
	
	if (m_hMapFile)
	{
		CloseHandle(m_hMapFile);
		m_hMapFile = NULL;
	}

	if (m_pMapFileBuf)
    { 
        ::UnmapViewOfFile(m_pMapFileBuf);
        m_pMapFileBuf = NULL;
    }

	if (m_hEndEvent)
	{
		::CloseHandle(m_hEndEvent);
		m_hEndEvent = NULL;
	}

	OutputDebugStringA("end TerminateThread ucipc!\n");

	return TRUE;
}

DWORD 
UcIpc::SendMsg(
    IN BOOL bChannel,
    IN ULONG ulPort,
    IN PBYTE pInBuf1,
    IN ULONG ulInBufLen1,
    IN OPTIONAL PBYTE pInBuf2,
    IN OPTIONAL ULONG ulInBufLen2,
    IN DWORD Timeout
	)
/*++	
	Routine Description:
		
		�������ݡ�
		�����ڴ汻��Ϊ����飬�ֱ�����Channel1��Channel2��
		����ÿ��Channel����pInBuf1��pInBuf2.
		��bChannel==TRUEʱ��������ǰKE_IPC_BUF_MAX_SIZE����

	Arguments:

		pulPort - ��ǰ��ʾ�˿ڡ�Ŀǰ����ÿ��UcIpc��һ���˿ڣ��ʴ��ֶ���֪ͨ������ȡĳЩ��������ı�׼

		pInBuf2 - һ�����buf����ʱ��У�졣��Ϊ��
--*/
{
	NTSTATUS      nStatus		= IPC_COM_ERROR;
	HANDLE        hRecvEvent	= NULL;
	HANDLE        hSendEvent	= NULL;
	PBYTE         pAddr         = NULL;
	KeIpcMsgHead  MsgHead		= {0};
	HANDLE		  ArrEvent[2]	= {0};

    WCHAR DbgStr[200] = {0};

	if ((!pInBuf1 || !m_bInitFlag)) {
		OutputDebugStringA("UcIpc::SendMsg invail !\n");
		goto _Exit_;
	}

	if (bChannel && (ulInBufLen1 + ulInBufLen2
		+ sizeof(KeIpcMsgHead) > m_BufSize) ||
        !bChannel && (ulInBufLen1 + ulInBufLen2
        + sizeof(KeIpcMsgHead) > m_BufSize2) )
	{
        swprintf(DbgStr, L"UcIpc::SendMsg IPC_COM_BUF_TOO_SMALL %x, %x, %x!!\n", ulInBufLen1, m_BufSize2, m_nIpcAddr);
		OutputDebugStringW(DbgStr);
		nStatus = IPC_COM_BUF_TOO_SMALL;
		goto _Exit_;
	}
	
	if (bChannel)
	{
		hRecvEvent = m_hRecvEventC1;
		hSendEvent = m_hSendEventC1;
		pAddr = m_pMapFileBuf;
	}
	else
	{
		hRecvEvent = m_hRecvEventC2;
		hSendEvent = m_hSendEventC2;
		pAddr = m_pMapFileBuf + m_BufSize;
	}

	ArrEvent[0] = hRecvEvent;
	ArrEvent[1] = m_hEndEvent;
	nStatus = WaitForMultipleObjects(2, ArrEvent,
 		FALSE, Timeout);
	if(WAIT_OBJECT_0 != nStatus) {
		//OutputDebugStringA("UcIpc::SendMsg wait fail!\n");
		nStatus = IPC_COM_WAIT_FAIL; goto _Exit_;}

    // һ��channel�еĹ����ڴ��еĽṹ����:
    // +--------------------+
    // |    KeIpcMsgHead    |
    // +--------------------+
    // |    Buf1            |
    // +--------------------+
    // |    Buf2            |
    // +--------------------+
	MsgHead.ulPort = ulPort;
	MsgHead.ulInBufLen1 = ulInBufLen1;
	MsgHead.ulInBufLen2 = ulInBufLen2;
	MDString (pInBuf1, ulInBufLen1, MsgHead.Md5);

	memcpy(pAddr, &MsgHead, sizeof(KeIpcMsgHead));
	memcpy(pAddr + sizeof(KeIpcMsgHead), 
		pInBuf1, ulInBufLen1);
	memcpy(pAddr + sizeof(KeIpcMsgHead) + ulInBufLen1,
		pInBuf2, ulInBufLen2);
	
	nStatus = IPC_COM_SUCCEED;
	//OutputDebugStringA("UcIpc::SendMsg succeed!\n");
	SetEvent(hSendEvent);

_Exit_:
	
	return nStatus;
}

DWORD 
UcIpc::RecvMsg(
    IN CKxEUCAllocator* allocator,
    IN BOOL bChannel,
	IN OUT PULONG pulPort,
    IN OUT PBYTE* ppInBuf1,
    IN OUT PULONG pulInBufLen1,
    IN OUT PBYTE* ppInBuf2,
    IN OUT PULONG pulInBufLen2,
    IN DWORD Timeout
	)
/*++	
	Routine Description:
		
		�������ݡ�
		�����ڴ汻��Ϊ����飬�ֱ�����Channel1��Channel2��
		����ÿ��Channel����pInBuf1��pInBuf2.
		��bChannel==TRUEʱ��������ǰKE_IPC_BUF_MAX_SIZE����

	Arguments:

		pInBuf2 - һ�����buf����ʱ��У�졣��Ϊ��
--*/
{
	DWORD         nStatus		= IPC_COM_ERROR;
	HANDLE        hRecvEvent	= NULL;
	HANDLE        hSendEvent	= NULL;
	PBYTE         pAddr         = NULL;
	PBYTE		  pNewOutBuf	= NULL;
	KeIpcMsgHead  MsgHead		= {0};
	HANDLE		  ArrEvent[2]	= {0};
	CHAR		  Md5[UC_IPC_MD5_SIZE] = {0};

	if (!ppInBuf1 || !pulInBufLen1 || !pulPort
		|| !m_bInitFlag) {goto _Exit_;}

	if (bChannel)
	{
		hRecvEvent = m_hRecvEventC1;
		hSendEvent = m_hSendEventC1;
		pAddr = m_pMapFileBuf;
	}
	else
	{
		hRecvEvent = m_hRecvEventC2;
		hSendEvent = m_hSendEventC2;
		pAddr = m_pMapFileBuf + m_BufSize;
	}
	
	ArrEvent[0] = hSendEvent;
	ArrEvent[1] = m_hEndEvent;
 	nStatus = WaitForMultipleObjects(2, ArrEvent,
 		FALSE, Timeout);
 	if(nStatus != WAIT_OBJECT_0) {nStatus = IPC_COM_WAIT_FAIL; goto _Exit_;}

	memcpy(&MsgHead, pAddr, sizeof(KeIpcMsgHead));

    if ( bChannel && (MsgHead.ulInBufLen1 + MsgHead.ulInBufLen2
        + sizeof(KeIpcMsgHead) > m_BufSize) ||
        !bChannel && (MsgHead.ulInBufLen1 + MsgHead.ulInBufLen2
        + sizeof(KeIpcMsgHead) > m_BufSize2) )
	{
        OutputDebugStringA("TOO_SMALL\n");
		nStatus = IPC_COM_BUF_TOO_SMALL; 
		goto _Exit_;
	}

	// ������÷������ܵڶ����������Ͳ���������Ӧ�ռ���
	if (pulInBufLen2 && ppInBuf2)
	{
		pNewOutBuf = (PBYTE)allocator->Alloc ( 
			MsgHead.ulInBufLen1 + MsgHead.ulInBufLen2);
	}
	else
	{
		pNewOutBuf = (PBYTE)allocator->Alloc ( 
			MsgHead.ulInBufLen1);
	}
	if (!pNewOutBuf) {nStatus = IPC_COM_ERROR_MEM_ALLOT; goto _Exit_;}

	memcpy(pNewOutBuf, pAddr + sizeof(KeIpcMsgHead), 
		MsgHead.ulInBufLen1);
	MDString (pNewOutBuf, MsgHead.ulInBufLen1, Md5);
	if (strncmp(MsgHead.Md5, Md5, UC_IPC_MD5_SIZE))
	{
		OutputDebugStringA("Md5 Fail\n");
		nStatus = IPC_COM_ERROR_MEM_ALLOT;
		goto _Exit_;
	}

	*pulPort = MsgHead.ulPort;
	*ppInBuf1 = pNewOutBuf;
	*pulInBufLen1 = MsgHead.ulInBufLen1;

	if (pulInBufLen2 && ppInBuf2)
	{
		memcpy(
			pNewOutBuf + MsgHead.ulInBufLen1, 
			pAddr + sizeof(KeIpcMsgHead) + MsgHead.ulInBufLen1, 
			MsgHead.ulInBufLen2
			);
		*ppInBuf2 = pNewOutBuf + MsgHead.ulInBufLen1;
		*pulInBufLen2 = MsgHead.ulInBufLen2;
	}
	
	nStatus = IPC_COM_SUCCEED;
	SetEvent(hRecvEvent);

_Exit_:
	
	return nStatus;
}

DWORD
UcIpc::CommunicationWorker( 
	LPVOID lpPrarm 
	)
/*++	
    Routine Description:
	    ÿ���˿ڽ�����һ�����̣߳�����������������������Ϣͨ��ע��Ļص�����󴫻�ȥ

--*/
{
	CKxEUCAllocator allocator;
	UcIpc*			pUcIpc			= (UcIpc*)lpPrarm;
	PBYTE			pInBuf1			= NULL;
	ULONG			pulInBufLen1	= 0;
	PBYTE			pCheckTime		= NULL;
	ULONG			pulCheckTimeLen = 0;
	PBYTE			pvReplyData		= NULL;
	DWORD			dwDataLengthRet	= 0;
	ULONG			ulPort			= 0;
	NTSTATUS		nStatus			= IPC_COM_ERROR;
	DWORD           dwCallBackRet   = 0;

	if (!pUcIpc) {return 0;}

	while ( pUcIpc->m_bInitFlag )
	{
        // m_pCallbackRoutine���������ڲ��õı��ϰ��δ���÷���dwDataLengthRet��ֵ���±���
        // ���ڴ�ÿ��ѭ�����³�ʼ��һ��.
        pInBuf1			= NULL;
        pulInBufLen1	= 0;
        pCheckTime		= NULL;
        pulCheckTimeLen = 0;
        pvReplyData		= NULL;
        dwDataLengthRet	= 0;
        ulPort			= 0;
        nStatus			= IPC_COM_ERROR;
        dwCallBackRet   = 0;

		nStatus = pUcIpc->RecvMsg(
			&allocator,
			TRUE,
			&ulPort,
			&pInBuf1,
			&pulInBufLen1,
			&pCheckTime,
			&pulCheckTimeLen,
			UC_IPC_TIME_OUT
			);
		if (IPC_COM_SUCCEED != nStatus)
        {
            if (IPC_COM_WAIT_FAIL != nStatus)
            {
                WCHAR wszTime[127 + 1] = {0};
                wsprintfW(wszTime, L"RecvMsg fail!! %x\n", nStatus);
                OutputDebugStringW(wszTime);
            }
            
            continue;
        }

        // ���û��UC_IPC_DRIVER_MARKλ����ʾ���Ǵ�����������
        if (!(ulPort & UC_IPC_DRIVER_MARK)) {continue;}
        ulPort &= ~UC_IPC_DRIVER_MARK;

		if (pUcIpc->m_pCallbackRoutine)
		{
			pUcIpc->m_pCallbackRoutine(
				&allocator,             // ��������ʹ�õķ�����
				pInBuf1,                // ����
				pulInBufLen1,           // ���ݳ���
				pUcIpc->m_pvParam,      // �ص����Զ������
				(PVOID*)&pvReplyData,   // ���ص�����, �������Ҫ������ppvDataRet == NULL
				&dwDataLengthRet);      // ���ص����ݳ���, �������Ҫ������pdwDataLengthRet == NULL);

			if (UC_IPC_DRIVER_NEED_REPLY == ulPort)
			{
                /////////////////////////////////////////////////////////////////////////
                // ������μ������ͷ�Ĵ��뱾��������ͳһͨ�š���ԭ��ͳһͨ�Ŵ��ݵ����ݶ��и�û�õ�
                // ����ͷ��ֻ��������ȥ����
//                 if (dwDataLengthRet <= sizeof(KXE_COMM_PACKET_HEADER))
//                 {
                    // �����������ͷ������㴫�������ݡ�
                    // �����п���UC_IPC_DRIVER_ZERO_LEN��֪
                    nStatus = pUcIpc->SendMsg(
                        FALSE,
                        UC_IPC_DRIVER_ZERO_LEN,
                        (PBYTE)&pvReplyData,     // ���õ�������
                        sizeof(PVOID*),
                        pCheckTime,
                        pulCheckTimeLen,
                        UC_IPC_TIME_OUT
                        );
//                 }
//                 else
//                 {
//                     pvReplyData += sizeof(KXE_COMM_PACKET_HEADER);
//                     dwDataLengthRet -= sizeof(KXE_COMM_PACKET_HEADER);
//                     nStatus = pUcIpc->SendMsg(
//                         FALSE,
//                         0 != dwDataLengthRet ? UC_IPC_DRIVER_NON : UC_IPC_DRIVER_ZERO_LEN,
//                         0 != dwDataLengthRet ? (PBYTE)pvReplyData : (PBYTE)&pvReplyData, // ���Ϊ�㣬��㴫��������
//                         0 != dwDataLengthRet ? dwDataLengthRet : sizeof(PVOID*),
//                         pCheckTime,
//                         pulCheckTimeLen,
//                         UC_IPC_TIME_OUT
//                         );
//                     //OutputDebugStringW(L"SendMsg Over\n\n");
//                 }
			}
		}

		allocator.Clear();
	}

	return 0;
}