/**
* @file    bkcachedef.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-16 17:36
*/

#ifndef BKCACHEDEF_H
#define BKCACHEDEF_H

#include <algorithm>
#include <atltime.h>
#include "skylarkbase.h"
#include "bklevel.h"

NS_SKYLARK_BEGIN

#define BKMOD_NAME_BKCACHE      L"kcache.dll"

#pragma pack(push)
#pragma pack(4)

// ------------------------------------------------------------
// �ļ�����Ľӿڰ汾




// ����ʱ��                                                   ��    ʱ  �� ��
#define BKCACHE_DEFAULT_REMAIN__LONG                CTimeSpan(365,  0,  0,  0).GetTimeSpan()    ///< ������


#define BKCACHE_DEFAULT_REMAIN__BLACK               CTimeSpan(0,    0,  5,  0).GetTimeSpan() 
#define BKCACHE_DEFAULT_REMAIN__UPLOAD              0
#define BKCACHE_DEFAULT_REMAIN__GRAY                CTimeSpan(0,    1,  0,  0).GetTimeSpan()
#define BKCACHE_DEFAULT_REMAIN__TRUST               CTimeSpan(365,  0,  0,  0).GetTimeSpan()

// add by yangjun 2010.11.12 Ϊ������԰׻���ʱ���������
#define BKCACHE_REMAIN_KSWHITE_3DAYS                CTimeSpan(3,  0,  0,  0).GetTimeSpan()
#define BKCACHE_REMAIN_KSWHITE_5DAYS                CTimeSpan(5,  0,  0,  0).GetTimeSpan()
#define BKCACHE_REMAIN_KSWHITE_7DAYS                CTimeSpan(7,  0,  0,  0).GetTimeSpan()
#define BKCACHE_REMAIN_KSWHITE_10DAYS               CTimeSpan(10,  0,  0,  0).GetTimeSpan()
// add end

#define BKCACHE_DEFAULT_REMAIN__PATH_TO_HASH        CTimeSpan(365,  0,  0,  0).GetTimeSpan()

#define BKCACHE_DEFAULT_REMAIN__WIN_TRUST           CTimeSpan(365,  0,  0,  0).GetTimeSpan()
#define BKCACHE_DEFAULT_REMAIN__FILE_TYPE           CTimeSpan(365,  0,  0,  0).GetTimeSpan()

///< δ֪�ļ�������
#define BKCACHE_DEFAULT_REMAIN__UNRECOGNISED_FILE   0

///< ��δ��ɨ����ļ�����1����
#define BKCACHE_DEFAULT_REMAIN__NEVER_BEEN_SCANNED  CTimeSpan(0,    0,  1,  0).GetTimeSpan()






// Ԥ����Ļ���ID
#define BKCACHE_STD_NULL                    0       ///< ���� ��Ч��
#define BKCACHE_STD_PATH_TO_HASH            1       ///< ���� path - hash
#define BKCACHE_STD_HASH_TO_LEVEL           2       ///< ���� hash - level
#define BKCACHE_STD_PATH_TO_WINTRUST        3       ///< ���� path - wintrust
#define BKCACHE_STD_PATH_TO_NONPE           4       ///< ���� path - non-pe
#define BKCACHE_STD_PATH_TO_AVEFT           5       ///< ���� path - ave filetype
#define BKCACHE_STD_PATH_TO_AVEBWM          6       ///< ���� path - ave bwm result

#define BKCACHE_STD_SCAN_LOG                100     ///< ��־ ��ɱ��־
#define BKCACHE_STD_PATH_TO_DELETE_TRACE    101     ///< ��־ ���������־,���Լ���Ƿ����ظ����

#define BKCACHE_STD_EXCLUDE_FILES           200     ///< �ļ��ų�·��




#define BKCACHE_IMPORT_DB_PASSWORD          L"IMPORT-DB"




// ------------------------------------------------------------
// path->hash ���������
struct BKCACHE_SETTINGS_PATH_TO_HASH
{
    UINT32  uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    BOOLEAN bAsyncUpdate;           ///< [=TRUE]        �첽����ģʽ, ��Ҫ����Flush�Ż������д�����ݿ�
    UINT64  uExpireTime;            ///< [=ULLONG_MAX]  ����ʱ��, ��λΪ��, Ĭ����������

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKCACHE_SETTINGS_PATH_TO_HASH* pStruct)
{
    assert(pStruct);
    pStruct->uSize          = sizeof(BKCACHE_SETTINGS_PATH_TO_HASH);

    pStruct->bAsyncUpdate   = TRUE;
    pStruct->uExpireTime    = ULLONG_MAX;
}




// ------------------------------------------------------------
// path->hash �����¼
struct BKCACHE_PATH_TO_HASH
{
    UINT32  uSize;                      ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    UINT64  uTimeStamp;                 ///< ��¼д���ʱ���
    BYTE    byMD5[SKYLARK_MD5_BYTES];   ///< md5
    UINT32  uCRC32;                     ///< crc32
    UINT32  uTag;                       ///< �ļ���У����

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKCACHE_PATH_TO_HASH* pStruct)
{
    assert(pStruct);
    pStruct->uSize          = sizeof(BKCACHE_PATH_TO_HASH);

    pStruct->uTimeStamp     = 0;
    memset(pStruct->byMD5, 0, sizeof(pStruct->byMD5));
    pStruct->uCRC32         = 0;
    pStruct->uTag           = 0;
}












// ------------------------------------------------------------
// hash->level ���������
struct BKCACHE_SETTINGS_HASH_TO_LEVEL
{
    UINT32  uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    BOOLEAN bAsyncUpdate;           ///< [=TRUE]        �첽����ģʽ, ��Ҫ����Flush�Ż������д�����ݿ�
    UINT64  vecExpireTime[256];     ///< [=...]         256��level�Ĺ���ʱ��, ��λΪ��

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKCACHE_SETTINGS_HASH_TO_LEVEL* pStruct)
{
    assert(pStruct);
    pStruct->uSize          = sizeof(BKCACHE_SETTINGS_HASH_TO_LEVEL);

    pStruct->bAsyncUpdate   = TRUE;
    memset(pStruct->vecExpireTime, 0, sizeof(pStruct->vecExpireTime));
    assert(SLPTL_LEVEL_GROUP__UPLOAD_MAX   < _countof(pStruct->vecExpireTime));
    assert(SLPTL_LEVEL_GROUP__BLACK_MAX    < _countof(pStruct->vecExpireTime));
    assert(SLPTL_LEVEL_GROUP__GRAY_MAX     < _countof(pStruct->vecExpireTime));
    assert(SLPTL_LEVEL_GROUP__TRUST_MAX    < _countof(pStruct->vecExpireTime));

    // δ֪�ļ�
    std::fill(
        pStruct->vecExpireTime + SLPTL_LEVEL_GROUP__UPLOAD_MIN,
        pStruct->vecExpireTime + SLPTL_LEVEL_GROUP__UPLOAD_MAX + 1,
        BKCACHE_DEFAULT_REMAIN__UPLOAD);

    // ���ļ�
    std::fill(
        pStruct->vecExpireTime + SLPTL_LEVEL_GROUP__BLACK_MIN,
        pStruct->vecExpireTime + SLPTL_LEVEL_GROUP__BLACK_MAX + 1,
        BKCACHE_DEFAULT_REMAIN__BLACK);

    // ���ļ�
    std::fill(
        pStruct->vecExpireTime + SLPTL_LEVEL_GROUP__GRAY_MIN,
        pStruct->vecExpireTime + SLPTL_LEVEL_GROUP__GRAY_MAX + 1,
        BKCACHE_DEFAULT_REMAIN__GRAY);

    // ���ļ�
    std::fill(
        pStruct->vecExpireTime + SLPTL_LEVEL_GROUP__TRUST_MIN,
        pStruct->vecExpireTime + SLPTL_LEVEL_GROUP__TRUST_MAX + 1,
        BKCACHE_DEFAULT_REMAIN__TRUST);

    // �����ٵ���һ�¶��԰׻���ʱ��
    pStruct->vecExpireTime[SLPTL_LEVEL_MARK___DUBA_TRUST_3DAY]   = BKCACHE_REMAIN_KSWHITE_3DAYS;
    pStruct->vecExpireTime[SLPTL_LEVEL_MARK___DUBA_TRUST_5DAY]   = BKCACHE_REMAIN_KSWHITE_5DAYS;
    pStruct->vecExpireTime[SLPTL_LEVEL_MARK___DUBA_TRUST_7DAY]   = BKCACHE_REMAIN_KSWHITE_7DAYS;
    pStruct->vecExpireTime[SLPTL_LEVEL_MARK___DUBA_TRUST_10DAY]  = BKCACHE_REMAIN_KSWHITE_10DAYS;

    // ��Ҫ�ϴ����ļ���������
    pStruct->vecExpireTime[SLPTL_LEVEL_MARK___UNRECOGNISED_FILE]   = BKCACHE_DEFAULT_REMAIN__UNRECOGNISED_FILE;
    pStruct->vecExpireTime[SLPTL_LEVEL_MARK___NEVER_BEEN_SCANNED]  = BKCACHE_DEFAULT_REMAIN__NEVER_BEEN_SCANNED;                         

    // ������������
    pStruct->vecExpireTime[SLPTL_LEVEL_MARK___BLACK_HEURIST_HIGH_RISK]  = 0;
    pStruct->vecExpireTime[SLPTL_LEVEL_MARK___BLACK_HEURIST_LOW_RISK]   = 0;
}


// ------------------------------------------------------------
// hash->level �����¼
struct BKCACHE_HASH_TO_LEVEL
{
    UINT32  uSize;          ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    UINT64  uTimeStamp;     ///< ��¼д���ʱ���
    UINT32  uLevel;         ///< ��ȫ����
    WCHAR   szInfo[64];     ///< ��Ϣ

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKCACHE_HASH_TO_LEVEL* pStruct)
{
    assert(pStruct);
    pStruct->uSize          = sizeof(BKCACHE_HASH_TO_LEVEL);

    pStruct->uTimeStamp     = 0;
    pStruct->uLevel         = SLPTL_LEVEL_MARK___RESERVED;
    memset(pStruct->szInfo, 0, sizeof(pStruct->szInfo));
}

















// ------------------------------------------------------------
// path->hresult ���������
struct BKCACHE_SETTINGS_PATH_TO_HRESULT
{
    UINT32  uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    BOOLEAN bAsyncUpdate;           ///< [=TRUE]        �첽����ģʽ, ��Ҫ����Flush�Ż������д�����ݿ�
    UINT64  uExpireTime;            ///< [=ULLONG_MAX]  ����ʱ��, ��λΪ��, Ĭ����������

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKCACHE_SETTINGS_PATH_TO_HRESULT* pStruct)
{
    assert(pStruct);
    pStruct->uSize          = sizeof(BKCACHE_SETTINGS_PATH_TO_HRESULT);

    pStruct->bAsyncUpdate   = TRUE;
    pStruct->uExpireTime    = ULLONG_MAX;
}


// ------------------------------------------------------------
// hash->hresult �����¼
struct BKCACHE_PATH_TO_HRESULT
{
    UINT32  uSize;          ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    UINT32  hResult;        ///< �������κκ���,Ŀǰʹ�õķ�ʽ����WinTrust����ֵ,PE�ж����
    UINT64  uTimeStamp;     ///< ��¼д���ʱ���
    UINT32  uTag;           ///< �ļ��ı��,

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKCACHE_PATH_TO_HRESULT* pStruct)
{
    assert(pStruct);
    pStruct->uSize          = sizeof(BKCACHE_PATH_TO_HRESULT);

    pStruct->hResult        = 0;
    pStruct->uTimeStamp     = 0;
    pStruct->uTag           = 0;
}






#pragma pack(pop)
NS_SKYLARK_END

#endif//BKCACHEDEF_H