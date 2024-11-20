/**
* @file    bkavedef.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-14 15:55
*/

#ifndef BKAVEDEF_H
#define BKAVEDEF_H

#include <assert.h>
#include "skylarkbase.h"
#include "bkdef.h"

NS_SKYLARK_BEGIN

#define BKMOD_NAME_BKAVE        L"ksafeave.dll"

#pragma pack(push)
#pragma pack(4)



// ------------------------------------------------------------
// �ļ�����ȫ�ֳ�ʼ��

/// �ļ�����ȫ�ֳ�ʼ����Ϣ
struct BKAVE_PLATFORM_INIT
{
    UINT32      uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    UINT32      uAveMask;               ///< [=0]       �ļ����������,BKAVE_MASK_xxx

    LPCWSTR     pAVERootDir;            ///< [=NULL]    �������Ŀ¼,���ΪNULL,��Ϊbkave.mod����Ŀ¼

    LPCWSTR     pKSGIni;                ///< [=NULL]    signs.ini       ��·��,���ΪNULL,��Ϊ [root]/signs.ini
    LPCWSTR     pKSGDir;                ///< [=NULL]    *.ksg           ��Ŀ¼,���ΪNULL,��Ϊ [root]/ksg

    LPCWSTR     pKAEIni;                ///< [=NULL]    kaecore.ini     ��·��,���ΪNULL,��Ϊ [root]/kae/kaecore.ini
    LPCWSTR     pKAEDir;                ///< [=NULL]    kaeģ��         ��Ŀ¼,���ΪNULL,��Ϊ [root]/kae

    LPCWSTR     pVNameIni;              ///< [=NULL]    vinfo.ini       ��·��,���ΪNULL,��Ϊ [root]/vinfo.ini
    LPCWSTR     pVNameDir;              ///< [=NULL]    *.vsg           ��Ŀ¼,���ΪNULL,��Ϊ [root]/ksg

    LPCWSTR     pKAECore;               ///< [=NULL]    kaecore.dat     ��·��,���ΪNULL,��Ϊ [KAEDir]/kaecore.dat
    LPCWSTR     pKAEVName;              ///< [=NULL]    kaevname.dat    ��·��,���ΪNULL,��Ϊ [KAEDir]/kaevname.dat
    LPCWSTR     pKArchive;              ///< [=NULL]    karchive.dat    ��·��,���ΪNULL,��Ϊ [KAEDir]/karchive.dat
    LPCWSTR     pKAEUnpak;              ///< [=NULL]    kaeunpak.dat    ��·��,���ΪNULL,��Ϊ [KAEDir]/kaeunpak.dat

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKAVE_PLATFORM_INIT* pStruct)
{
    assert(pStruct);
    pStruct->uSize              = sizeof(BKAVE_PLATFORM_INIT);

    pStruct->uAveMask           = 0;
                                                          
    pStruct->pAVERootDir        = NULL;
                                       
    pStruct->pKSGIni            = NULL;
    pStruct->pKSGDir            = NULL;
                                       
    pStruct->pKAEIni            = NULL;
    pStruct->pKAEDir            = NULL;
                                       
    pStruct->pVNameIni          = NULL;
    pStruct->pVNameDir          = NULL;

    pStruct->pKAECore           = NULL;
    pStruct->pKAEVName          = NULL;
    pStruct->pKArchive          = NULL;
    pStruct->pKAEUnpak          = NULL;
}



// ------------------------------------------------------------
// �ļ������ʼ��

/// �ļ������ʼ����Ϣ
struct BKAVE_ENGINE_INIT
{
    UINT32      uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    IBKFactory* piFactory;              ///< �೧,���ڻ�ȡ����ӿ�,���ΪNULL,�ڲ�����ʹ�û���

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKAVE_ENGINE_INIT* pStruct)
{
    assert(pStruct);
    pStruct->uSize      = sizeof(BKAVE_ENGINE_INIT);

    pStruct->piFactory  = NULL;
}



// ------------------------------------------------------------

/// �ļ���������
struct BKAVE_ENGINE_SETTINGS
{
    UINT32      uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    UINT32      uBWMType;               ///< [=BKENG_BWMTYPE_GENERAL]   �ڰ׻�����

    UINT64      uMaxFileSize;           ///< [=ULONG_MAX]               ɨ���ļ��Ĵ�С����

    UINT16      uExtractDepth;          ///< [=32]                      [�ݲ�֧��]��ѹ���,ȡֵ��ΧΪ [8, 64],���������ȡ�߽�ֵ
    UINT16      uUnpackDepth;           ///< [=32]                      [�ݲ�֧��]�ѿ����,ȡֵ��ΧΪ [8, 64],���������ȡ�߽�ֵ

    UINT32      uAveScanMask;           ///< [=BKAVE_SCAN_MASK_DEFAULT] ɨ����������,ȡֵΪ BKAVE_SCAN_MASK_xxx
    UINT32      uAveCleanMask;          ///< [=BKAVE_CLEAN_MASK_NONE]   �����������,ȡֵΪ BKAVE_CLEAN_MASK_xxx, ��Ҫ���ʱ,ͨ��ȡ BKAVE_CLEAN_MASK_DEFAULT

    // ------------------------------------------------------------ 

    // ��������
    UINT32      uEnableQueryCacheMask;  ///< [=BKENG_CACHE_MASK_ALL]    ȡֵΪ BKENG_CACHE_MASK_xxx
    UINT32      uEnableWriteCacheMask;  ///< [=BKENG_CACHE_MASK_ALL]    ȡֵΪ BKENG_CACHE_MASK_xxx

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKAVE_ENGINE_SETTINGS* pStruct)
{                                          
    assert(pStruct);    
    pStruct->uSize                  = sizeof(BKAVE_ENGINE_SETTINGS);

    pStruct->uBWMType               = BKENG_BWMTYPE_GENERAL;

    pStruct->uMaxFileSize           = ULONG_MAX;            

    pStruct->uExtractDepth          = 32;                   
    pStruct->uUnpackDepth           = 32;                   

    pStruct->uAveScanMask           = BKAVE_SCAN_MASK_DEFAULT;
    pStruct->uAveCleanMask          = BKAVE_CLEAN_MASK_NONE;

    pStruct->uEnableQueryCacheMask  = BKENG_CACHE_MASK_ALL;
    pStruct->uEnableWriteCacheMask  = BKENG_CACHE_MASK_ALL;
}





// ------------------------------------------------------------

/// �ļ�����ɨ�����
struct BKAVE_SCAN_PARAM
{
    UINT32      uSize;              ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    HRESULT     hrTag;              ///< [=ULONG_MAX]   �����ļ���ǩ�ķ���ֵ, ULONG_MAX ��ʾ��δ�����
    DWORD       dwFileTag;          ///< [=0]           �ļ���ǩ

    BOOLEAN     bValidAveFT;        ///< [=FALSE]       �Ƿ��ṩ�����ave�ļ�����,���� dwFileTag �� uHintAveFT ��ЧʱΪTRUE
    UINT32      uHintAveFT;         ///< [=0]           �ṩ�����ave�ļ�����

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKAVE_SCAN_PARAM* pStruct)
{                                          
    assert(pStruct);    
    pStruct->uSize                  = sizeof(BKAVE_SCAN_PARAM);

    pStruct->hrTag                  = ULONG_MAX;
    pStruct->dwFileTag              = 0;

    pStruct->bValidAveFT            = FALSE;
    pStruct->uHintAveFT             = 0;
}






// ------------------------------------------------------------
// �ļ�����ɨ����

/// �ļ���������
struct BKAVE_ENGINE_RESULT
{
    UINT32      uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    BOOLEAN     bIsVirus;               ///< �Ƿ��ǲ���
    UINT32      uThreatID;              ///< ����ID
    WCHAR       szVirusName[64];        ///< ������
    UINT32      uScanResult;            ///< ɨ����,ȡֵΪBKENG_SCAN_RESULT_xxx
    UINT32      uCleanResult;           ///< ������,ȡֵΪBKENG_CLEAN_RESULT_xxx

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKAVE_ENGINE_RESULT* pStruct)
{  
    assert(pStruct);
    pStruct->uSize          = sizeof(BKAVE_ENGINE_RESULT);

    pStruct->bIsVirus       = FALSE;
    pStruct->uThreatID      = 0;
    pStruct->uScanResult    = BKENG_SCAN_RESULT_SAFE;
    pStruct->uCleanResult   = BKENG_CLEAN_RESULT_NO_OP;
    memset(pStruct->szVirusName, 0, sizeof(pStruct->szVirusName));
}











#pragma pack(pop)
NS_SKYLARK_END

#endif//BKAVEDEF_H