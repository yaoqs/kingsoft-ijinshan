/**
* @file    bkengdef.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-15 12:17
*/

#ifndef BKENGDEF_H
#define BKENGDEF_H

#include <assert.h>
#include "skylarkbase.h"
#include "bkdef.h"
#include "bklevel.h"

NS_SKYLARK_BEGIN

#define BKMOD_NAME_BKENG        L"ksafeeng.dll"

#pragma pack(push)
#pragma pack(4)



/// ���糬ʱ����
#define SLPTL_NET_MIN_TIMEOUT               1000        ///< ��С�����糬ʱ
#define SLPTL_NET_MAX_QUERY_TIMEOUT         30000       ///< ���Ĳ�ѯ��ʱ#define SLPTL_NET_MAX_ECHO_TIMEOUT          30000       ///< �������ֳ�ʱ#define SLPTL_NET_ECHO_TIMEOUT              20000       ///< �������ֵ����糬ʱ
#define SLPTL_NET_ECHO_TIMEOUT              20000       ///< �������ֵ����糬ʱ
#define SLPTL_NET_QUERY_TIMEOUT             15000       ///< ���β�ѯ�����糬ʱ
#define SLPTL_NET_UPLOAD_TIMEOUT            600000      ///< �����ϴ������糬ʱ



/// skylark ��ѯ�ļ��Ĵ�С����
#define SKYLARK_QUERY_FILE_MAX_SIZE         (20 * 1024 * 1024)

/// skylark �ϴ��ļ��Ĵ�С����
#define SKYLARK_UPLOAD_FILE_MAX_SIZE        (20 * 1024 * 1024)

#define SLPTL_FILETYPE__UNKNOWN     0x00000000  ///< δ֪�ļ�����
#define SLPTL_FILETYPE__NON_PE      0x00000001  ///< ��PE�ļ�
#define SLPTL_FILETYPE__TOO_SMALL   0x00000002  ///< �ļ�̫С
#define SLPTL_FILETYPE__TOO_LARGE   0x00000003  ///< �ļ�̫��

#define SLPTL_FILETYPE__PE          0x00010001  ///< PE�ļ�





// ------------------------------------------------------------
// ��ɱ����ȫ�ֳ�ʼ��

/// ��ɱ����ȫ�ֳ�ʼ����Ϣ
struct BKENG_PLATFORM_INIT
{
    UINT32      uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    BYTE        byDeprecated[12];       ///< ����ʹ�õ��ֶ�

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_PLATFORM_INIT* pStruct)
{
    assert(pStruct);
    pStruct->uSize = sizeof(BKENG_PLATFORM_INIT);

    memset(pStruct->byDeprecated, 0, sizeof(pStruct->byDeprecated));
}






// ------------------------------------------------------------
// ��ɱ�����ʼ��

/// �ļ������ʼ����Ϣ
struct BKENG_ENGINE_INIT
{
    UINT32      uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_ENGINE_INIT* pStruct)
{
    assert(pStruct);
    pStruct->uSize = sizeof(BKENG_ENGINE_INIT);
}






// ------------------------------------------------------------

/// ��ɱ��������
struct BKENG_SETTINGS
{
    UINT32  uSize;                          ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    // ------------------------------------------------------------
    // �ļ������ɨ������

    UINT32  uBWMType;                       ///< [=BKENG_BWMTYPE_GENERAL]       �ڰ׻�����

    UINT64  uMaxFileSize;                   ///< [=ULONG_MAX]                   ɨ���ļ��Ĵ�С����

    UINT16  uExtractDepth;                  ///< [=32]                          [�ݲ�֧��]��ѹ���,ȡֵ��ΧΪ [8, 64],���������ȡ�߽�ֵ
    UINT16  uUnpackDepth;                   ///< [=32]                          �ѿ����,ȡֵ��ΧΪ [8, 64],���������ȡ�߽�ֵ

    UINT32  uAveScanMask;                   ///< [=BKAVE_SCAN_MASK_DEFAULT]     ɨ����������,ȡֵΪ BKAVE_SCAN_MASK_xxx
    UINT32  uAveCleanMask;                  ///< [=BKAVE_CLEAN_MASK_NONE]       �����������,ȡֵΪ BKAVE_CLEAN_MASK_xxx, ��Ҫ���ʱ,ͨ��ȡ BKAVE_CLEAN_MASK_DEFAULT

    // ------------------------------------------------------------
    // �Ʋ�ɱ��ɨ������

    // �Ʋ�ɱ����
    UINT8   uRetryTimes;                    ///< [=0]                           ���Դ���,����Ϊ[0, 3],����3��ȡΪ3
    UINT32  uCloudMask;                     ///< [=BKCLOUD_MASK_DEFAULT]        �Ʋ�ɱ����������

    // ��������
    UINT32  uEnableQueryCacheMask;          ///< [=BKENG_CACHE_MASK_ALL]        ȡֵΪ BKENG_CACHE_MASK_xxx
    UINT32  uEnableWriteCacheMask;          ///< [=BKENG_CACHE_MASK_ALL]        ȡֵΪ BKENG_CACHE_MASK_xxx
    
    // ɨ������
    UINT32  uEnableLocalScanMask;           ///< [=BKENG_LOCAL_SCAN_MASK_ALL]   ȡֵΪ BKENG_LOCAL_SCAN_MASK_xxx
    UINT32  uEnableReviewScanMask;          ///< [=BKENG_REVIEW_SCAN_MASK_ALL]  ȡֵΪ BKENG_REVIEW_SCAN_MASK_xxx

    // ���糬ʱ����
    UINT32  uNetworkTimeout;                ///< [=SLPTL_NET_TIMEOUT]           ���ֵĳ�ʱ����,��λΪ����,��СֵΪ3000����,Ĭ��30000����(30��)
    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_SETTINGS* pStruct)
{
    assert(pStruct);
    pStruct->uSize              = sizeof(BKENG_SETTINGS);


    // �ļ����������
    pStruct->uBWMType           = BKENG_BWMTYPE_GENERAL;    

    pStruct->uMaxFileSize       = ULONG_MAX;                

    pStruct->uExtractDepth      = 32;                       
    pStruct->uUnpackDepth       = 32;         

    pStruct->uAveScanMask       = BKAVE_SCAN_MASK_DEFAULT;
    pStruct->uAveCleanMask      = BKAVE_CLEAN_MASK_NONE;


    // �Ʋ�ɱ��ɨ������
    pStruct->uRetryTimes            = 1;
    pStruct->uCloudMask             = BKCLOUD_MASK_DEFAULT;

    pStruct->uEnableQueryCacheMask  = BKENG_CACHE_MASK_ALL;
    pStruct->uEnableWriteCacheMask  = BKENG_CACHE_MASK_ALL;

    pStruct->uEnableLocalScanMask   = BKENG_LOCAL_SCAN_MASK_ALL;
    pStruct->uEnableReviewScanMask  = BKENG_REVIEW_SCAN_MASK_DEFAULT;

    pStruct->uNetworkTimeout        = SLPTL_NET_QUERY_TIMEOUT;
}




// ------------------------------------------------------------
// ��ɱ����ɨ�����

/// ��ɱ����ɨ�����
struct BKENG_SCAN_PARAM
{
    UINT32                  uSize;              ///< �ṹ���С

    const WIN32_FIND_DATAW* pFindData;          ///< ö���ļ�ʱ��Ľṹ��,�����ΪNULL,���Լ���ɨ���ٶ�
    DWORD                   dwScanMask;         ///< ɨ������,ȡֵΪBKENG_SCAN_MASK_xxx�����
    IUnknown*               piReserved;         ///< ����
    DWORD                   dwScanWeight;       ///< ɨ��Ȩ��,�����������
    void*                   pvFlag;             ///< �����߶���İ󶨲���,�ص�ʱԭ������
    DWORD                   dwHighWaterMark;    ///< ��ˮλ��,���ȴ�ɨ����ļ����� dwHighWaterMark ʱ,������,ֱ���ļ������� dwHighWaterMark,���Ϊ0,������
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_SCAN_PARAM* pStruct)
{  
    assert(pStruct);
    pStruct->uSize              = sizeof(BKENG_SCAN_PARAM);

    pStruct->pFindData          = NULL;
    pStruct->dwScanMask         = BKENG_SCAN_MASK_NONE;
    pStruct->piReserved         = NULL;
    pStruct->dwScanWeight       = 0;
    pStruct->pvFlag             = NULL;
    pStruct->dwHighWaterMark    = 5000;
}




// ------------------------------------------------------------
// ��ɱ����hashɨ�����

/// ��ɱ����hashɨ�����
struct BKENG_HASH_SCAN_PARAM
{
    UINT32      uSize;              ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    BOOLEAN     bUseHex;            ///< =[FALSE]

    BYTE        byMD5[16];          ///< md5,           ���� bUseHex Ϊ FALSE ʱ��Ч
    UINT32      uCRC32;             ///< crc32,         ���� bUseHex Ϊ FALSE ʱ��Ч

    WCHAR       szHex[64];          ///< hash��hex��ʽ, ���� bUseHex Ϊ TRUE  ʱ��Ч
    
    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_HASH_SCAN_PARAM* pStruct)
{  
    assert(pStruct);
    pStruct->uSize          = sizeof(BKENG_HASH_SCAN_PARAM);

    pStruct->bUseHex        = FALSE;

    memset(pStruct->byMD5, 0, sizeof(pStruct->byMD5));
    pStruct->uCRC32         = 0;

    memset(pStruct->szHex, 0, sizeof(pStruct->szHex));
}




// ------------------------------------------------------------
// ��ɱ����ɨ����

/// ��ɱ��������
struct BKENG_RESULT
{
    UINT32      uSize;              ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    BOOLEAN     bIsVirus;           ///< �Ƿ��ǲ���
    WCHAR       szVirusName[64];    ///< ������
    UINT32      uScanResult;        ///< ɨ����,ȡֵΪBKAVE_SCAN_RESULT_xxx
    UINT32      uCleanResult;       ///< ɨ����,ȡֵΪBKAVE_CLEAN_RESULT_xxx

    UINT32      uSecLevel;          ///< �ļ���ȫ�ȼ�,ȡֵΪSLPTL_LEVEL_MARK___xxx
    BOOLEAN     bNeedUpload;        ///< �ļ���Ҫ�ϴ�

    BOOLEAN     bHashed;            ///< �Ƿ���hash���
    BYTE        byMD5[16];          ///< md5
    UINT32      uCRC32;             ///< crc32

    HRESULT     hrLastError;        ///< ���һ�β����Ĵ�����
    // ------------------------------------------------------------
    // added 2010.07.15

    DWORD       dwUsedScanWeight;   ///< �Ѿ����ĵ�ɨ��Ȩ��
    DWORD       dwTotalScanWeight;  ///< ��ɨ��Ȩ��
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_RESULT* pStruct)
{  
    assert(pStruct);
    pStruct->uSize          = sizeof(BKENG_RESULT);

    pStruct->bIsVirus       = FALSE;
    pStruct->uScanResult    = BKENG_SCAN_RESULT_SAFE;
    pStruct->uCleanResult   = BKENG_CLEAN_RESULT_NO_OP;
    memset(pStruct->szVirusName, 0, sizeof(pStruct->szVirusName));

    pStruct->uSecLevel      = SLPTL_LEVEL_MARK___RESERVED;
    pStruct->bNeedUpload    = FALSE;

    pStruct->bHashed        = FALSE;
    memset(pStruct->byMD5, 0, sizeof(pStruct->byMD5));
    pStruct->uCRC32         = 0;

    pStruct->hrLastError    = S_OK;
    pStruct->dwUsedScanWeight   = 0;    pStruct->dwTotalScanWeight  = 0;}








#define BKENG_UPLOAD_AUTO                  1       ///< �Զ��ϴ�
#define BKENG_UPLOAD_MANUAL                2       ///< �ֶ��ϴ�
#define BKENG_UPLOAD_FORCE                 3       ///< ǿ���ϴ�


// ------------------------------------------------------------
// �ϴ�����

/// �ϴ�����
struct BKENG_UPLOAD_PARAM
{
    UINT32      uSize;              ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    UINT32      uUploadChannel;         ///< [=0]                   �ϴ�ͨ����
    UINT32      uUploadAct;             ///< [=BKENG_UPLOAD_AUTO]   �ϴ���������,ȡֵΪ BKENG_UPLOAD_xxx
    BOOLEAN     bUploadZippedFile;      ///< [=FALSE]               �ϴ��Ѿ�ѹ�������ļ�

    BYTE        byMD5[16];              ///< [=0]                   �ļ�md5,���ҽ��� bUploadZippedFile Ϊ TRUE ʱ, ��ֵ������Ч
    UINT32      uCRC32;                 ///< [=0]                   �ļ�crc,���ҽ��� bUploadZippedFile Ϊ TRUE ʱ, ��ֵ������Ч

    BOOLEAN     bUploadNonPEFile;       ///< [=FALSE]               �ϴ���PE�ļ�

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_UPLOAD_PARAM* pStruct)
{  
    assert(pStruct);
    pStruct->uSize              = sizeof(BKENG_UPLOAD_PARAM);

    pStruct->uUploadChannel     = 0;
    pStruct->uUploadAct         = BKENG_UPLOAD_AUTO;
    pStruct->bUploadZippedFile  = FALSE;

    memset(pStruct->byMD5, 0, sizeof(pStruct->byMD5));
    pStruct->uCRC32             = 0;

    pStruct->bUploadNonPEFile   = FALSE;
}



//////////////////////////////////////////////////////////////////////////
// ����״̬
#define BKENG_ECHO_SUCCESS              0       ///< �ɹ�

#define BKENG_ECHO_UNKNOWN_ERROR        1       ///< δ֪����
#define BKENG_ECHO_LOCAL_ERROR          2       ///< ���ش���
#define BKENG_ECHO_NETWORK_ERROR        3       ///< Զ�̴���
#define BKENG_ECHO_SERVER_ERROR         4       ///< ����˴���
#define BKENG_ECHO_SERVICE_UNAVALIABLE  5       ///< ���񲻿���

#define BKENG_ECHO_UNRECOGNISED_EXE     6       ///< δ֪�Ŀ�ִ���ļ�
#define BKENG_ECHO_BLACK_EXE            7       ///< ��ִ���ļ���ľ��

#define BKENG_ECHO_INTERRUPTED          8       ///< ���ֱ��ж�
#define BKENG_ECHO_LOCAL_COMM_ERROR     10      ///< ���ط���ͨ��ʧ��




// ------------------------------------------------------------

/// ��ɱ��������
struct BKENG_ECHO_SETTINGS
{
    UINT32  uSize;                          ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    UINT8   uRetryTimes;                    ///< [=1]                       ���Դ���,����Ϊ[0, 3],����3��ȡΪ3
    UINT32  uNetworkTimeout;                ///< [=SLPTL_NET_ECHO_TIMEOUT]  ���ֵĳ�ʱ����,��λΪ����,��СֵΪ3000����,Ĭ��30000����(30��)

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_ECHO_SETTINGS* pStruct)
{
    assert(pStruct);
    pStruct->uSize              = sizeof(BKENG_ECHO_SETTINGS);


    // �ļ����������
    pStruct->uRetryTimes        = 3;
    pStruct->uNetworkTimeout    = SLPTL_NET_ECHO_TIMEOUT;
}



// ------------------------------------------------------------
// ������Ϣ
/// ������Ϣ
struct BKENG_ECHO_RESULT
{
    UINT32      uSize;                      ///< �ṹ���С

    UINT32      uEchoStatus;                ///< ����״̬ȡֵ�� BKENG_ECHO_XXX
    HRESULT     hEchoCode;                  ///< ���ֲ����Ĵ�����,��ѭHRESULT�淶

    __time64_t  serverTime;                 ///< ������ʱ��

    // ------------------------------------------------------------
    // added after svn r567

    BOOLEAN     bTrustProgram;              ///< ��������������֤���ļ��Ƿ����
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_ECHO_RESULT* pStruct)
{  
    assert(pStruct);
    pStruct->uSize              = sizeof(BKENG_ECHO_RESULT);

    pStruct->uEchoStatus        = BKENG_ECHO_UNKNOWN_ERROR;
    pStruct->hEchoCode          = E_FAIL;

    pStruct->serverTime         = 0;

    pStruct->bTrustProgram      = FALSE;
}






// ------------------------------------------------------------
// ɱ�������������
struct BKENG_AVE_LOAD
{
    UINT32      uSize;              ///< �ṹ���С
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_AVE_LOAD* pStruct)
{  
    assert(pStruct);
    pStruct->uSize              = sizeof(BKENG_AVE_LOAD);
}






#pragma pack(pop)
NS_SKYLARK_END

#endif//BKENGDEF_H