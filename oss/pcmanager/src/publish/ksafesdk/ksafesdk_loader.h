/**
* @file    ksafesdk_loader.h
* @brief   ...
* @author  bbcallen
* @date    2010-08-06 11:34
*/

#ifndef KSAFESDK_LOADER_H
#define KSAFESDK_LOADER_H

#include <windows.h>
#include <objidl.h>
#include "ksafesdk_def.h"

//////////////////////////////////////////////////////////////////////////////

#ifndef	KSAFESDK_API
#define	KSAFESDK_API __declspec(dllimport)
#endif

typedef KSAFESDK_API HRESULT (__stdcall* PFN_ksafeInitialize)(
    /*[in]*/  PFN_ksafeCallbackW    pCallback);         ///< �ص��ӿ�
typedef KSAFESDK_API HRESULT (__stdcall* PFN_ksafeUninitialize)();
typedef KSAFESDK_API HRESULT (__stdcall* PFN_ksafeScanFileW)(
    /*[in]*/  const wchar_t*        pScanFileName,      ///< Ҫɨ����ļ�·��
    /*[in]*/  unsigned long         dwScanningMode,     ///< ɨ��ģʽ,ȡֵΪ KSAFE_S_M_... �����
    /*[in]*/  unsigned long         dwCleaningMode,     ///< ����,δʹ��
    /*[in]*/  void*                 pUserContext,       ///< �ص�����
    /*[out]*/ KSAFE_RESULT*         pResult);           ///< ɨ����
typedef KSAFESDK_API HRESULT (__stdcall* PFN_ksafeFlushAsyncScan)();

//////////////////////////////////////////////////////////////////////////

extern PFN_ksafeInitialize      ksafeInitialize;
extern PFN_ksafeUninitialize    ksafeUninitialize;
extern PFN_ksafeScanFileW       ksafeScanFileW;
extern PFN_ksafeFlushAsyncScan  ksafeFlushAsyncScan;

//////////////////////////////////////////////////////////////////////////////

HRESULT ksafeLoadW(const wchar_t* pLoadFolder);
HRESULT ksafeUnload();

//////////////////////////////////////////////////////////////////////////////

#endif//KSAFESDK_LOADER_H