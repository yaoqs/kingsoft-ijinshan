/**
* @file    bklogdef.h
* @brief   ...
* @author  bbcallen
* @date    2010-01-04 17:56
*/

#ifndef BKLOGDEF_H
#define BKLOGDEF_H

#include "bkcachedef.h"
#include "bkengdef.h"

NS_SKYLARK_BEGIN

// ------------------------------------------------------------
// BKEngine��־

/// BKEngine��־
struct BKENG_SCAN_LOG
{
    UINT32      uSize;              ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    UINT32      uLogID;             ///< ��־����ˮ��,д����־ʱ,�����Զ�����
    FILETIME    ftLogTime;          ///< ��־¼��ʱ��,д����־ʱ,�����Զ�����,ע��������UTCʱ��,��ʾ��ʱ����Ҫת�ɱ���ʱ��

    WCHAR       szPath[MAX_PATH];   ///< �ļ�·��(���� MAX_PATH �ᱻ�ض�)
    WCHAR       szVirusName[64];    ///< ������

    UINT32      uScanResult;        ///< ɨ����,ȡֵΪBKAVE_SCAN_RESULT_xxx
    UINT32      uCleanResult;       ///< ������,ȡֵΪBKAVE_CLEAN_RESULT_xxx

    UINT32      uSecLevel;          ///< �ļ���ȫ�ȼ�,ȡֵΪSLPTL_LEVEL_MARK___xxx

    BOOLEAN     bHashed;            ///< �Ƿ���hash���
    BYTE        byMD5[16];          ///< md5,   ���� bHashed ��Ϊ FALSE ʱ,������
    UINT32      uCRC32;             ///< crc32, ���� bHashed ��Ϊ FALSE ʱ,������

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_SCAN_LOG* pStruct)
{
    assert(pStruct);
    pStruct->uSize  = sizeof(BKENG_SCAN_LOG);

    pStruct->uLogID                     = 0;
    pStruct->ftLogTime.dwHighDateTime   = 0;
    pStruct->ftLogTime.dwLowDateTime    = 0;

    memset(pStruct->szPath,         0, sizeof(pStruct->szPath));
    memset(pStruct->szVirusName,    0, sizeof(pStruct->szVirusName));

    pStruct->uScanResult                = BKENG_SCAN_RESULT_SAFE;
    pStruct->uCleanResult               = BKENG_CLEAN_RESULT_NO_OP;

    pStruct->uSecLevel                  = SLPTL_LEVEL_MARK___RESERVED;

    pStruct->bHashed                    = FALSE;
    memset(pStruct->byMD5,  0, sizeof(pStruct->byMD5));
    pStruct->uCRC32                     = 0;
}

NS_SKYLARK_END

#endif//BKLOGDEF_H