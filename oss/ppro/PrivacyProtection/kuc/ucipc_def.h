/************************************************************************
* @file      : ucipc_def.h
* @author    : WangBin5 <WangBin5.com>
* @date      : 26/11/2009 AM 11:53:11
* @brief     : ͨ�ÿ�ƽ̨��IPC��ʹ�õ�����
*
* $Id: $
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
#include <WinError.h>

#ifndef __COM_IPCTYPE_H__
#define __COM_IPCTYPE_H__

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef VOID
#define VOID void
#endif

#ifndef IN
#define IN 
#endif

#ifndef OUT
#define OUT 
#endif

#ifndef WINAPI
#define WINAPI __stdcall
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef PAGE_READWRITE
#define PAGE_READWRITE 0x04
#endif

#ifndef INFINITE
#define INFINITE 0xFFFFFFFF 
#endif

#ifndef WAIT_TIMEOUT
#define WAIT_TIMEOUT 258L
#endif

#ifndef STATUS_WAIT_0
#define STATUS_WAIT_0 ((DWORD )0x00000000L)
#endif

#ifndef WAIT_OBJECT_0
#define WAIT_OBJECT_0 ((STATUS_WAIT_0 ) + 0 )
#endif

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE ((HANDLE)-1)
#endif

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif

#define IPC_COM_SUCCEED				0x00000000	// �ɹ�
#define IPC_COM_ERROR			    0x00000001	// ʧ��
#define IPC_COM_TIME_OUT			0x00000002	// ��ʱ
#define IPC_COM_WRITEFILE_FAIL		0x00000003	// д���ļ�ʧ��
#define IPC_COM_ERROR_POINT			0x00000004	// ָ�����
#define IPC_COM_ERROR_MEM_ALLOT     0x00000005	// �ڴ�������
#define IPC_COM_ERROR_NO_INIT		0x00000006	// δ��ʼ��
#define IPC_COM_ERROR_DATE_FORMAT	0x00000007	// ���ݸ�ʽ������
#define IPC_COM_ERROR_RECV			0x00000008	// ��������ʧ��
#define IPC_COM_WAIT_SUCCEED		0x00000009	// �ȴ��ɹ�
#define IPC_COM_BUF_TOO_SMALL		0x00000010	// ������̫С
#define IPC_COM_WAIT_FAIL			0x00000011	// �ȴ�ʧ��

//typedef long BOOL;
typedef long LONG;
typedef LONG NTSTATUS, *PNTSTATUS;
//typedef unsigned short WCHAR;
typedef unsigned char BYTE;
typedef unsigned long ULONG;
typedef ULONG DWORD;
typedef long HRESULT;
typedef unsigned char BYTE;
typedef void *PVOID;
typedef PVOID HANDLE;
typedef HANDLE *PHANDLE;
typedef WCHAR *LPWSTR, *PWSTR;
typedef void *LPVOID;
typedef const VOID *LPCVOID;
typedef int INT;



#endif