
/************************************************************************
* @file      : kxeuc.h
* @author    : WangBin5 <WangBin5.com>
* @date      : 26/11/2009 AM 11:53:11
* @brief     : ͳһͨ�Žӿ�
*
* $Id: $
/************************************************************************/

#include "windows.h"
#include "ucipc.h"

#ifndef _KXE_UC_H_
#define _KXE_UC_H_

#pragma pack (2)
typedef struct _KsafeFileMonStr 
{
    WCHAR sProName[MAX_PATH + 1];  // ����������
    WCHAR sOpenName[MAX_PATH + 1]; // ���򿪵��ļ���
}
KsafeFileMonStr, *PKsafeFileMonStr;
#pragma pack ()

typedef enum
{
	enumKxERuleMgr,
	enumKxELogger,
	enumKxEMisc,
	enumKxEInteractive,
	enumKxETrackSystem,
	enumKxECreateProcess,
		
	enumKxEMaximumSerivceID
};

// ͳһͨ�Żص�ʹ�õ��ڴ������
interface KucIAllocator
{
	virtual LPVOID WINAPI Alloc(
		/* [in] */ ULONG ulSize                     // Ҫ������ڴ��С
		) = 0;
};

// ͳһͨ�Żص���������
typedef DWORD (WINAPI *KucPCALLBACK)(
	/* [in] */ KucIAllocator *piAllocator,             // ��������ʹ�õķ�����
	/* [in] */ PVOID    pvData,                     // ����
	/* [in] */ DWORD    dwDataLength,               // ���ݳ���
	/* [in] */ PVOID    pvParam,                    // �ص����Զ������
	/* [in] */ PVOID    *ppvDataRet,                // ���ص�����, �������Ҫ������ppvDataRet == NULL
	/* [in] */ DWORD    *pdwDataLengthRet           // ���ص����ݳ���, �������Ҫ������pdwDataLengthRet == NULL
        );

int WINAPI KucInit(
	/* [in] */ void* pvNotused /* = NULL */ 
	);

void WINAPI KucUnInit();

int WINAPI KucRegisterCallback(
	/* [in] */ ULONG		ulClientID,              // ͨ�ſͻ���ID
	/* [in] */ KucPCALLBACK	pCallbackRoutine,        // �ص�����ָ��
	/* [in] */ PVOID		pvParam                  // ���ص�����ָ��һ���Զ������
	);

int WINAPI KucUnregisterCallback(
	/* [in] */ ULONG    ulClientID					 // ͨ�ſͻ���ID								   
	);

BOOL WINAPI KucSetVideoDevName(
    /* [in] */ LPCWSTR lpName
    );

#endif