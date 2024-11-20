/**
* @file    bkdef.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-15 12:55
*/

#ifndef BKDEF_H
#define BKDEF_H

#include <assert.h>
#include <unknwn.h>
#include "skylarkbase.h"

NS_SKYLARK_BEGIN

// ------------------------------------------------------------
// ����Ľӿڰ汾

#define BKENG_VERSION_0001      1                   ///< ��ʼ�汾
#define BKENG_CURRENT_VERSION   BKENG_VERSION_0001  ///< bkeng�ӿڵİ汾,���ӿڷ����ı��ʱ��,�޸Ĵ˺�

#define BKENG_PROTOCOL_VERSION  2                   ///< bkengʹ�õķ����Э���

// ------------------------------------------------------------
// �������
#define BKENG_MATCH_BITS(dst__, bits__)     (((dst__) & (bits__)) == (bits__))


#define BKENG_SET_BITS(dst__, bits__)       do {(dst__) |= (bits__);} while(0)


#define BKENG_UNSET_BITS(dst__, bits__)     do {(dst__) &= ~bits__;} while(0)






// ------------------------------------------------------------
// ģ������

#define BKENG_MODULE_DB         0x00000001          ///< bkdb.mod
#define BKENG_MODULE_CACHE      0x00000002          ///< bkcache.mod
#define BKENG_MODULE_AVE        0x00000004          ///< bkave.mod


// ------------------------------------------------------------
// ɨ������ĺڰ׻�����,ע���� fileengine/ksbwmanager.h ����ͬ��

#define BKENG_BWMTYPE_GENERAL   0x0000FFFF          ///< ͨ��
#define BKENG_BWMTYPE_EXTEND    0x000000FF          ///< Extend, ����NE/LE/MZ/������ͨ�ļ���
#define BKENG_BWMTYPE_PE        0x00000001          ///< Extend2, �����ض���PE�ļ�
#define BKENG_BWMTYPE_SCRIPT    0x00000002          ///< �ű�, ����JS/HTML
#define BKENG_BWMTYPE_PEH       0x00000100          ///< ����ʽ, ����PE�ļ�, ��������Ӱ��, ��Ҫר�ŷ������

// ------------------------------------------------------------
// �ļ�����ɨ��������������
#define BKAVE_SCAN_MASK_SCAN_FILE_IN_ARCHIVE    0x00000001  ///< ɨ��ѹ�����е��ļ�
#define BKAVE_SCAN_MASK_SCAN_FILE_IN_PACK       0x00000002  ///< ɨ���ѿǺ���ļ�
#define BKAVE_SCAN_MASK_SCAN_EXE_ONLY           0x00000004  ///< ��ɨ���ִ���ļ�
#define BKAVE_SCAN_MASK_DEFAULT                 (BKAVE_SCAN_MASK_SCAN_FILE_IN_ARCHIVE | BKAVE_SCAN_MASK_SCAN_FILE_IN_PACK)

#define BKAVE_CLEAN_MASK_AUTO_CLEAN             0x00000001  ///< �Զ����
#define BKAVE_CLEAN_MASK_DELETE_IF_FAIL         0x00000002  ///< ���ʧ�ܵ�ʱ��ɾ���ļ�
#define BKAVE_CLEAN_MASK_NONE                   0x00000000  ///< Ĭ�ϲ��Զ����
#define BKAVE_CLEAN_MASK_DEFAULT                (BKAVE_CLEAN_MASK_AUTO_CLEAN | BKAVE_CLEAN_MASK_DELETE_IF_FAIL)

// ------------------------------------------------------------
// ɨ��������

#define BKENG_SCAN_RESULT_NOT_SCANNED                   0   ///< û�в���
#define BKENG_SCAN_RESULT_SAFE                          1   ///< û�в���
#define BKENG_SCAN_RESULT_FAILED_TO_SCAN                2   ///< ɨ��ʧ��(ͨ����Ϊ�޶�)
#define BKENG_SCAN_RESULT_VIRUS_NEED_DELETE             3   ///< ������Ҫɾ��
#define BKENG_SCAN_RESULT_VIRUS_NEED_DISINFECT          4   ///< ������Ҫ���(��Ⱦ��,ѹ����)
#define BKENG_SCAN_RESULT_VIRUS_NO_OP                   5   ///< ����(�޷����)
#define BKENG_SCAN_RESULT_VIRUS_NEED_DISABLE_AUTORUN    6   ///< ��ֹ������


// ------------------------------------------------------------
// ����������
#define BKENG_CLEAN_RESULT_NO_OP                        1   ///< δ���

#define BKENG_CLEAN_RESULT_DELETE                       2   ///< ��ɾ��
#define BKENG_CLEAN_RESULT_DISINFECT                    3   ///< �����(�޸�)

#define BKENG_CLEAN_RESULT_FAILED_TO_DELETE             4   ///< ɾ��ʧ��
#define BKENG_CLEAN_RESULT_FAILED_TO_DISINFECT          5   ///< ���ʧ��

#define BKENG_CLEAN_RESULT_DELETE_NEED_REBOOT           6   ///< ɾ����Ҫ����
#define BKENG_CLEAN_RESULT_DISINFECT_NEED_REBOOT        7   ///< �����Ҫ����

#define BKENG_CLEAN_RESULT_NEED_DELETE                  8   ///< ��Ҫɾ��(�ڲ����)
#define BKENG_CLEAN_RESULT_DISINFECT_NEED_REPLACE       9   ///< �������Ҫ�滻(�ڲ����)

#define BKENG_CLEAN_RESULT_DISABLE_AUTORUN              10  ///< ��ֹ������
#define BKENG_CLEAN_RESULT_FAILED_TO_DISABLE_AUTORUN    11  ///< ��ֹ������ʧ��

inline BOOL BKEngCleanNeedReboot(DWORD dwCleanResult)
{
    switch (dwCleanResult)
    {
    case BKENG_CLEAN_RESULT_DELETE_NEED_REBOOT:
    case BKENG_CLEAN_RESULT_DISINFECT_NEED_REBOOT:
        return TRUE;
    }

    return FALSE;
}



// ------------------------------------------------------------
// �ļ���������
#define BKENG_TYPE_MASK_SKIP        0x00000001  ///< [���ɹ���]�������в������ļ�
#define BKENG_TYPE_MASK_EXE         0x00000002  ///< [���ɹ���]��ִ���ļ�
#define BKENG_TYPE_MASK_RTF         0x00000004  ///< RTF�ļ�, ����Office�ļ�
#define BKENG_TYPE_MASK_ARCH        0x00000008  ///< [���ɹ���]ѹ���ļ�
#define BKENG_TYPE_MASK_PIC         0x00000010  ///< ͼ���ļ�
#define BKENG_TYPE_MASK_META        0x00000020  ///< [���ɹ���]�����ļ�
#define BKENG_TYPE_MASK_TEXT        0x00000040  ///< �ı��ļ�
#define BKENG_TYPE_MASK_SHELL       0x00000080  ///< [���ɹ���]�ӿ��ļ�


#define BKENG_TYPE_MASK_NONE        0x00000000  ///< �����ļ�
#define BKENG_TYPE_MASK_ALL         0xFFFFFFFF  ///< �������͵��ļ�

/// ���õĹ����������
#define BKENG_TYPE_MASK_NON_EXE     (BKENG_TYPE_MASK_RTF | BKENG_TYPE_MASK_PIC | BKENG_TYPE_MASK_TEXT)
#define BKENG_TYPE_MASK_DEFAULT     BKENG_TYPE_MASK_NONE



// ------------------------------------------------------------
// 
#define BKCLOUD_MASK_DISABLE_NETWORK_QUERY      0x00000001  ///< ��ֹ������ѯ
//#define BKCLOUD_MASK_FORCE_HASH_FILE                0x00000002  ///< ǿ�Ƽ����ļ���hash
#define BKCLOUD_MASK_QUERY_BLACK_CACHE          0x00000004  ///< ��ѯ��level����
#define BKCLOUD_MASK_WRITE_CACHE_AFTER_QUERY    0x00000008  ///< �����ܿ���������
#define BKCLOUD_MASK_LOW_RESOURCE_USAGE         0x00000010  ///< ������Դռ��
#define BKCLOUD_MASK_USE_CLOUD_HEURIST          0x00000020  ///< ʹ���ƶ�����
#define BKCLOUD_MASK_FORCE_BOOT_CLEAN           0x00000040  ///< ǿ�����������
#define BKCLOUD_MASK_DEFAULT                    (BKCLOUD_MASK_USE_CLOUD_HEURIST)   ///< Ĭ������

// ------------------------------------------------------------
// ��������
#define BKENG_CACHE_MASK_PATH_TO_HASH       0x00000001  ///< ���� path - hash       (���ûᵼ�����Ǽ���hash)
#define BKENG_CACHE_MASK_HASH_TO_LEVEL      0x00000002  ///< ���� hash - level      (���ûᵼ������������ѯ)
#define BKENG_CACHE_MASK_PATH_TO_WINTRUST   0x00000004  ///< ���� path - wintrust   (���ûᵼ��������֤�ļ�����ǩ����������)
#define BKENG_CACHE_MASK_PATH_TO_NONPE      0x00000008  ///< ���� path - nonpe      (���ûᵼ�����Ǵ��ļ��ж��Ƿ���PE)
#define BKENG_CACHE_MASK_PATH_TO_AVEFT      0x00000010  ///< ���� path - aveft      (���ûᵼ��ave���Ǵ��ļ��ж��ļ�����)
#define BKENG_CACHE_MASK_PATH_TO_AVEBWM     0x00000020  ///< ���� path - avebwm     (���ûᵼ��ave���Ǵ��ļ����кڰ׻�ɨ��)

#define BKENG_CACHE_MASK_NONE               0x00000000
#define BKENG_CACHE_MASK_ALL                0xFFFFFFFF




// ------------------------------------------------------------
// LocalScan (ǰ��ɨ��)
#define BKENG_LOCAL_SCAN_MASK_NONE              0x00000000
#define BKENG_LOCAL_SCAN_MASK_ALL               0xFFFFFFFF


// ------------------------------------------------------------
// ReviewScan (����ɨ��)
#define BKENG_REVIEW_SCAN_MASK_WINTRUST                 0x00000001  ///< ��������ǩ��
#define BKENG_REVIEW_SCAN_MASK_AVENGINE                 0x00000002  ///< ʹ���ļ����渴��
#define BKENG_REVIEW_SCAN_MASK_RESERVED_0               0x00000004  ///< ...
#define BKENG_REVIEW_SCAN_MASK_AVENGINE_SCAN_NON_PE     0x00000008  ///< ʹ���ļ�����ɨ���PE�ļ�
#define BKENG_REVIEW_SCAN_MASK_AVENGINE_SCAN_NON_EXE    0x00000010  ///< ʹ���ļ�����ɨ��ǿ�ִ���ļ�,���� BKENG_REVIEW_SCAN_MASK_AVENGINE_SCAN_NON_PE �����ò���Ч
#define BKENG_REVIEW_SCAN_MASK_USE_LOCAL_HEURIST        0x00000020  ///< ʹ�ñ�������

#define BKENG_REVIEW_SCAN_MASK_NONE                     0x00000000
#define BKENG_REVIEW_SCAN_MASK_ALL                      0xFFFFFFFF
#define BKENG_REVIEW_SCAN_MASK_DEFAULT                  (BKENG_REVIEW_SCAN_MASK_WINTRUST | BKENG_REVIEW_SCAN_MASK_AVENGINE | BKENG_REVIEW_SCAN_MASK_USE_LOCAL_HEURIST)



// ------------------------------------------------------------
// Append Scan Mask �����ļ���ɨ������
#define BKENG_SCAN_MASK_USE_LOCAL_HEURIST               0x00000001  ///< ʹ�ñ�������ʽ
#define BKENG_SCAN_MASK_USE_CLOUD_HEURIST_LOW_RISK      0x00000002  ///< ʹ���ƶ������ĵͷ���
#define BKENG_SCAN_MASK_USE_CLOUD_HEURIST_HIGH_RISK     0x00000004  ///< ʹ���ƶ������ĸ߷���
#define BKENG_SCAN_MASK_FROM_AUTORUNS                   0x00010000  ///< ����������
#define BKENG_SCAN_MASK_HINT_AVP_VIRUS                  0x00020000  ///< ��ʾ���ļ��ǿ��ͱ������ļ�,���ʱ������ɨ��,ֱ�����
#define BKENG_SCAN_MASK_HINT_CURABLE                    0x00040000  ///< ��ʾ���ļ����޸�

#define BKENG_SCAN_MASK_NONE                    0x00000000
#define BKENG_SCAN_MASK_ALL                     0xFFFFFFFF
#define BKENG_SCAN_MASK_DEFAULT                 BKENG_SCAN_MASK_NONE







// ------------------------------------------------------------
// �ļ���������
#define BKAVE_MASK_NO_DAEMON_SIGN           0x00000001  ///< �����ⲻ��פ,����ɨ��ʱ�ż���





/**
* @brief    ���Ȼص�
*/
class IBKProgress
{
public:
    /**
    * @brief        ���Ȼص�
    * @param[in]    dwTotal     ����
    * @param[in]    dwFinished  �����
    */
    virtual HRESULT STDMETHODCALLTYPE OnProgress(
        DWORD   dwTotal,
        DWORD   dwFinished) = 0;
};


/**
* @brief    ��������
*/
class __declspec(uuid("C0C6F1E9-69C5-44ae-B03E-E5E78B3EF79F"))
IBKFactory: public IUnknown
{
public:

    /**
    * @brief        �������ʵ��
    * @param[id]    riid    �ӿ�iid
    * @param[out]   ppvObj  ���ؽӿ�ָ��
    */
    virtual HRESULT STDMETHODCALLTYPE CreateInstance(REFIID riid, void** ppvObj) = 0;
};









// ------------------------------------------------------------
// ������汾�ṹ

/// ������汾�ṹ
struct BKAVE_SIGN_VERSION
{
    // ------------------------------------------------------------
    // Version[1, ?]

    UINT16      uYear;                  ///< ��
    UINT16      uMonth;                 ///< ��
    UINT16      uDay;                   ///< ��
    UINT16      uBuild;                 ///< build��

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKAVE_SIGN_VERSION* pStruct)
{  
    pStruct->uYear      = 0;
    pStruct->uMonth     = 0;
    pStruct->uDay       = 0;
    pStruct->uBuild     = 0;
}







#define BKENG_DETAIL_AVP_BEFORE_SCAN    101     ///< avpɨ�迪ʼ
#define BKENG_DETAIL_AVP_INPROGRESS     102     ///< avpɨ���������
#define BKENG_DETAIL_AVP_SCAN_OBJECT    103     ///< avpɨ�����һ������
#define BKENG_DETAIL_AVP_AFTER_SCAN     104     ///< avpɨ�����

#define BKENG_DETAIL_AFTER_LOCAL_SCAN   201     ///< ���ڵ��ñ���ɨ��



// ------------------------------------------------------------
// ��ɱ�����ɨ��ϸ��

/// ��ɱ����ɨ��ϸ��
struct BKENG_SCAN_DETAIL
{
    UINT32  uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    DWORD   dwDetailType;       ///< ϸ������,ȡֵΪBKENG_DETAIL_xxx
    DWORD   dwUsedScanWeight;   ///< ���ĵ�ɨ��Ȩ��

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_SCAN_DETAIL* pStruct)
{  
    assert(pStruct);
    pStruct->uSize                  = sizeof(BKENG_SCAN_DETAIL);

    pStruct->dwDetailType           = 0;
    pStruct->dwUsedScanWeight       = 0;
}





NS_SKYLARK_END

#endif//BKDEF_H