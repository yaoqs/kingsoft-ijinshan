/**
* @file    bkdbdef.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-15 16:48
*/

#ifndef BKDBDEF_H
#define BKDBDEF_H

#include <assert.h>
#include "skylarkbase.h"
#include "bkdef.h"

NS_SKYLARK_BEGIN

#define BKMOD_NAME_BKDB      L"ksafedb.dll"

// ------------------------------------------------------------
// BKDbȫ�ֳ�ʼ��

/// BKDbȫ�ֳ�ʼ����Ϣ
struct BKDB_PLATFORM_INIT
{
    UINT32  uSize;      ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKDB_PLATFORM_INIT* pStruct)
{
    assert(pStruct);
    pStruct->uSize  = sizeof(BKDB_PLATFORM_INIT);      
}

NS_SKYLARK_END

#endif//BKDBDEF_H