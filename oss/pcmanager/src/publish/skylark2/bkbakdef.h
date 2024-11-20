/**
* @file    bkbakdef.h
* @brief   ...
* @author  bbcallen
* @date    2010-01-05 21:21
*/

#ifndef BKBAKDEF_H
#define BKBAKDEF_H

#include "bkdef.h"
#include "bklevel.h"

NS_SKYLARK_BEGIN

#define BKMOD_NAME_BKBAK      L"ksafebak.dll"

#define BKBAK_COMPRESS_DAT_PASSWORD                 "{A56655E0-538D-4381-910D-4D95F2E97CE8}"
#define BKBAK_TEMPFILE_POSTFIX__SLBACKUP            L".kbk"                 ///< �����ļ�ʱ��ѹ���ļ���׺
#define BKBAK_TEMPFILE_INF_EXT                      L".inf"                 ///< �����ļ���ѹ����Ϣ�ļ���׺

#define BKBAK_UPLOAD_PACK_FILE_NAME                 L"pack.slzip"           ///< ѹ�����ڵ������ļ���
#define BKBAK_UPLOAD_PACK_INFO_FILE_NAME            L"pack.info.slzip"      ///< ѹ�����ڵ���Ϣ�ļ���
#define BKBAK_UPLOAD_PACK_INFO_FILE_MAX_SIZE        (1024 * 1024)           ///< ѹ�����ڵ���Ϣ�ļ�����󳤶�

#define BKBAK_BACKUP_FILE_DEFAULT_RESERVE_DAYS      30          ///< Ĭ�ϱ�������
#define BKBAK_BACKUP_FILE_MAX_RESERVE_DAYS          1000        ///< ��ౣ������
#define BKBAK_BACKUP_MAX_FILES                      10000       ///< ��౸��10000���ļ�
#define BKBAK_BACKUP_MIN_FILES                      20          ///< ���ٱ���20���ļ�

#define BKBAK_BACKUP_LEAST_DISK_FREE_BYTES          (1024 * 1024 * 1024)    ///< ������Ӳ��ʣ��ռ�����1g
#define BKBAK_BACKUP_LEAST_DISK_FREE_PERCENT        5                       ///< ������Ӳ��ʣ��ռ�����5%


// ------------------------------------------------------------
// ѹ��������Ϣ

/// ѹ��������Ϣ
struct BKBAK_ZIP_INFO
{
    UINT32      uSize;                      ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    DWORD       dwFileAttributes;           ///< �ļ�����
    FILETIME    ftCreationTime;             ///< �ļ�����ʱ��
    FILETIME    ftLastAccessTime;           ///< �ļ�������ʱ��
    FILETIME    ftLastWriteTime;            ///< �ļ����д��ʱ��
    DWORD       nFileSizeHigh;              ///< �ļ���С�ĸ�32λ
    DWORD       nFileSizeLow;               ///< �ļ���С�ĵ�32λ
    WCHAR       cFileName[MAX_PATH];        ///< �ļ���(�������ļ�·��)

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKBAK_ZIP_INFO* pStruct)
{
    assert(pStruct);
    pStruct->uSize = sizeof(BKBAK_ZIP_INFO);

    pStruct->dwFileAttributes                   = FILE_ATTRIBUTE_NORMAL;
    pStruct->ftCreationTime.dwHighDateTime      = 0;
    pStruct->ftCreationTime.dwLowDateTime       = 0;
    pStruct->ftLastAccessTime.dwHighDateTime    = 0;
    pStruct->ftLastAccessTime.dwLowDateTime     = 0;
    pStruct->ftLastWriteTime.dwHighDateTime     = 0;
    pStruct->ftLastWriteTime.dwLowDateTime      = 0;
    pStruct->nFileSizeHigh                      = 0;
    pStruct->nFileSizeLow                       = 0;
    memset(pStruct->cFileName, 0, sizeof(pStruct->cFileName));
}





// ------------------------------------------------------------
// �ļ����ݲ���

/// �ļ����ݲ���
struct BKBAK_BACKUP_PARAM
{
    UINT        uSize;                          ///< �ṹ���С

    WCHAR       cVirusName[64];                 ///< ������

    UINT32      uSecLevel;                      ///< �ļ��İ�ȫ�ȼ�
    BOOLEAN     bHashed;                        ///< �Ƿ�����Ч��hash
    BYTE        byMD5[SKYLARK_MD5_BYTES];       ///< �ļ���md5,   ���� bHashed ��Ϊ FALSE ʱ,������
    UINT32      uCRC32;                         ///< �ļ���crc32, ���� bHashed ��Ϊ FALSE ʱ,������
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKBAK_BACKUP_PARAM* pStruct)
{
    assert(pStruct);
    pStruct->uSize          = sizeof(BKBAK_BACKUP_PARAM);

    memset(pStruct->cVirusName,         0, sizeof(pStruct->cVirusName));

    pStruct->uSecLevel      = SLPTL_LEVEL_MARK___RESERVED;
    pStruct->bHashed        = FALSE;
    memset(pStruct->byMD5,  0, sizeof(pStruct->byMD5));
    pStruct->uCRC32         = 0;
}




// ------------------------------------------------------------
// �ļ�����ID

/// �ļ�����ID
struct BKBAK_BACKUP_ID
{
    UINT    uSize;
    UINT64  uBackupID;          ///< �����ļ���Ψһ��ʶ;
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKBAK_BACKUP_ID* pStruct)
{
    assert(pStruct);
    pStruct->uSize      = sizeof(BKBAK_BACKUP_ID);

    pStruct->uBackupID  = 0;
}





// ------------------------------------------------------------
// �ļ�������Ϣ

/// �ļ�������Ϣ
struct BKBAK_BACKUP_INFO
{
    UINT        uSize;                          ///< �ṹ���С

    FILETIME    ftBackupTime;                   ///< ����ʱ��

    WCHAR       cFileOriginalPath[MAX_PATH];    ///< �ļ���ԭʼ·��(����MAX_PATH�ᱻ�ض�)
    WCHAR       cFileName[MAX_PATH];            ///< �ļ���(����·��)
    WCHAR       cVirusName[64];                 ///< ������

    UINT32      uSecLevel;                      ///< �ļ��İ�ȫ�ȼ�
    BOOLEAN     bHashed;                        ///< �Ƿ�����Ч��hash
    BYTE        byMD5[SKYLARK_MD5_BYTES];       ///< �ļ���md5,   ���� bHashed ��Ϊ FALSE ʱ,������
    UINT32      uCRC32;                         ///< �ļ���crc32, ���� bHashed ��Ϊ FALSE ʱ,������

    DWORD       dwFileAttributes;               ///< �ļ�����
    FILETIME    ftCreationTime;                 ///< �ļ�����ʱ��
    FILETIME    ftLastAccessTime;               ///< �ļ�������ʱ��
    FILETIME    ftLastWriteTime;                ///< �ļ����д��ʱ��
    DWORD       nFileSizeHigh;                  ///< �ļ���С�ĸ�32λ
    DWORD       nFileSizeLow;                   ///< �ļ���С�ĵ�32λ

    DWORD       nCompressedSizeHigh;            ///< ѹ������ļ���С�ĸ�32λ
    DWORD       nCompressedSizeLow;             ///< ѹ������ļ���С�ĵ�32λ
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKBAK_BACKUP_INFO* pStruct)
{
    assert(pStruct);
    pStruct->uSize                              = sizeof(BKBAK_BACKUP_INFO);

    pStruct->ftBackupTime.dwHighDateTime        = 0;
    pStruct->ftBackupTime.dwLowDateTime         = 0;

    memset(pStruct->cFileOriginalPath,  0, sizeof(pStruct->cFileOriginalPath));
    memset(pStruct->cFileName,          0, sizeof(pStruct->cFileName));
    memset(pStruct->cVirusName,         0, sizeof(pStruct->cVirusName));

    pStruct->uSecLevel                          = SLPTL_LEVEL_MARK___RESERVED;
    pStruct->bHashed                            = FALSE;
    memset(pStruct->byMD5, 0, sizeof(pStruct->byMD5));
    pStruct->uCRC32                             = 0;

    pStruct->dwFileAttributes                   = FILE_ATTRIBUTE_NORMAL;
    pStruct->ftCreationTime.dwHighDateTime      = 0;
    pStruct->ftCreationTime.dwLowDateTime       = 0;
    pStruct->ftLastAccessTime.dwHighDateTime    = 0;
    pStruct->ftLastAccessTime.dwLowDateTime     = 0;
    pStruct->ftLastWriteTime.dwHighDateTime     = 0;
    pStruct->ftLastWriteTime.dwLowDateTime      = 0;
    pStruct->nFileSizeHigh                      = 0;
    pStruct->nFileSizeLow                       = 0;

    pStruct->nCompressedSizeHigh                = 0;
    pStruct->nCompressedSizeLow                 = 0;
}







// ------------------------------------------------------------
// �ļ�������Ϣ��Ҫ

/// �ļ�������Ϣ��Ҫ
struct BKBAK_BACKUP_SHORT_INFO
{
    UINT        uSize;                          ///< �ṹ���С

    FILETIME    ftBackupTime;                   ///< ����ʱ��
    WCHAR       cVirusName[64];                 ///< ������

    UINT32      uSecLevel;                      ///< �ļ��İ�ȫ�ȼ�
    BOOLEAN     bHashed;                        ///< �Ƿ�����Ч��hash
    BYTE        byMD5[SKYLARK_MD5_BYTES];       ///< �ļ���md5,   ���� bHashed ��Ϊ FALSE ʱ,������
    UINT32      uCRC32;                         ///< �ļ���crc32, ���� bHashed ��Ϊ FALSE ʱ,������
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKBAK_BACKUP_SHORT_INFO* pStruct)
{
    assert(pStruct);
    pStruct->uSize                              = sizeof(BKBAK_BACKUP_SHORT_INFO);

    pStruct->ftBackupTime.dwHighDateTime        = 0;
    pStruct->ftBackupTime.dwLowDateTime         = 0;

    memset(pStruct->cVirusName,         0, sizeof(pStruct->cVirusName));

    pStruct->uSecLevel                          = SLPTL_LEVEL_MARK___RESERVED;
    pStruct->bHashed                            = FALSE;
    memset(pStruct->byMD5, 0, sizeof(pStruct->byMD5));
    pStruct->uCRC32                             = 0;
}


inline void BKENG_COPY(BKBAK_BACKUP_SHORT_INFO* pTo, const BKBAK_BACKUP_INFO* pFrom)
{
    assert(pTo);
    assert(pFrom);

    pTo->ftBackupTime   = pFrom->ftBackupTime;
    StrCpyNW(pTo->cVirusName, pFrom->cVirusName, _countof(pTo->cVirusName));
    pTo->cVirusName[_countof(pTo->cVirusName) - 1] = L'\0';

    pTo->uSecLevel  = pFrom->uSecLevel;
    pTo->bHashed    = pFrom->bHashed;
    memcpy(pTo->byMD5, pFrom->byMD5, sizeof(pTo->byMD5));
    pTo->uCRC32     = pFrom->uCRC32;
}







NS_SKYLARK_END

#endif//BKBAKDEF_H