/**
* @file    bkksupdef.h
* @brief   ...
* @author  bbcallen
* @date    2010-01-20 17:09
*/

#ifndef BKKSUPDEF_H
#define BKKSUPDEF_H

#include "bkavedef.h"
#include "bkengdef.h"

NS_SKYLARK_BEGIN

#define BKMOD_NAME_BKKSUP       L"ksignup.dll"

#define BKKSUP_UPCH_DUBA2011    1   ///< �ɵĲ�����������ַ
#define BKKSUP_UPCH_WANGDUN     2   ///< ���ܵĲ�����������ַ
#define BKKSUP_UPCH_DEFAULT     BKKSUP_UPCH_WANGDUN

// ------------------------------------------------------------
// ������������ʼ����Ϣ

/// ������������ʼ����Ϣ
struct BKKSUP_INIT
{
    UINT32      uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    LPCWSTR     pAVERootDir;            ///< deprectated ����ʹ��
    DWORD       dwUpdateChannel;        ///< ����ͨ��,ȡֵΪ BKKSUP_UPCH_xxx

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKKSUP_INIT* pStruct)
{
    assert(pStruct);
    pStruct->uSize              = sizeof(BKKSUP_INIT);

    pStruct->pAVERootDir        = NULL;
    pStruct->dwUpdateChannel    = BKKSUP_UPCH_DEFAULT;
}




// ------------------------------------------------------------
// ��������������

class IBKEngKsgUpdateCallback;

/// ��������������
struct BKKSUP_UPDATE_PARAM
{
    UINT32                      uSize;              ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    BOOLEAN                     bFastCheckVersion;  ///< [=FALSE]   �����жϰ汾,���TRUE,������ȽϷ���˰汾,���ΪFALSE,��Ա����ļ���������У��
    IBKEngKsgUpdateCallback*    piCallback;         ///< [=NULL]    �����ص�
    UINT32                      uRetryTime;         ///< [=0]       ���Դ���,����Ϊ[0, 3],����3��ȡΪ3

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKKSUP_UPDATE_PARAM* pStruct)
{
    assert(pStruct);
    pStruct->uSize              = sizeof(BKKSUP_UPDATE_PARAM);

    pStruct->bFastCheckVersion  = FALSE;
    pStruct->piCallback         = NULL;
    pStruct->uRetryTime         = 0;
}





// ------------------------------------------------------------
// ������������Ϣ

/// ������������Ϣ
struct BKKSUP_UPDATE_INSTRUCTION
{
    UINT32              uSize;              ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    BOOLEAN             bNeedUpdate;        ///< ��������Ҫ����

    BKAVE_SIGN_VERSION  localSignVersion;   ///< ���ز�����汾
    BKAVE_SIGN_VERSION  remoteSignVersion;  ///< ����˲�����汾,ע��,����˲������ֿ��ܱȱ��ز��������������.

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKKSUP_UPDATE_INSTRUCTION* pStruct)
{
    assert(pStruct);
    pStruct->uSize              = sizeof(BKKSUP_UPDATE_INSTRUCTION);

    pStruct->bNeedUpdate        = FALSE;

    BKENG_INIT(&pStruct->localSignVersion);
    BKENG_INIT(&pStruct->remoteSignVersion);
}




NS_SKYLARK_END

#endif//BKKSUPDEF_H