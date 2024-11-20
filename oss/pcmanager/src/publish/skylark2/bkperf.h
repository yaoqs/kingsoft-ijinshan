/**
* @file    bkperf.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-29 19:59
*/

#ifndef BKPERF_H
#define BKPERF_H

#include <utility>
#include <atlcoll.h>
#include "bkdef.h"

NS_SKYLARK_BEGIN



//////////////////////////////////////////////////////////////////////////
// ���ܲ��Բ���

// ------------------------------------------------------------
// �Ʋ�ɱ�����ܲ��Բ���
#define BKENG_PERF_LOCAL_SCAN                   1       ///< LocalScan(ǰ��ɨ��)
#define BKENG_PERF_REVIEW_SCAN                  2       ///< ReviewScan(����ɨ��)
#define BKENG_PERF_QUERY                        3       ///< Query(������ѯ)
#define BKENG_PERF_REQUERY                      4       ///< Requery(���Ե�������ѯ)

#define BKENG_PERF_NORMALIZE_PATH               10      ///< ���滯�ļ�·��
#define BKENG_PERF_CALC_FILE_TAG                11      ///< �����ļ�tag
#define BKENG_PERF_CREATE_FILE                  12      ///< ���ļ�
#define BKENG_PERF_CHECK_PE                     13      ///< ����Ƿ���PE(���������ļ���ʱ��)
#define BKENG_PERF_HASH_FILE                    14      ///< �����ļ�hash(���������ļ���ʱ��)
#define BKENG_PERF_WINTRUST                     15      ///< �������ǩ��
#define BKENG_PERF_ENCODE                       16      ///< ����Э��
#define BKENG_PERF_DECODE                       17      ///< ����Э��

#define BKENG_PERF_LOOKUP_PATH_TO_NONPE         30      ///< ��ѯ���� path - nonpe
#define BKENG_PERF_LOOKUP_PATH_TO_WINTRUST      31      ///< ��ѯ���� path - wintrust
#define BKENG_PERF_LOOKUP_PATH_TO_HASH          32      ///< ��ѯ���� path - hash
#define BKENG_PERF_LOOKUP_HASH_TO_LEVEL         33      ///< ��ѯ���� hash - level

#define BKENG_PERF_UPDATE_PATH_TO_NONPE         40      ///< ���»��� path - nonpe     
#define BKENG_PERF_UPDATE_PATH_TO_WINTRUST      41      ///< ���»��� path - wintrust
#define BKENG_PERF_UPDATE_PATH_TO_HASH          42      ///< ���»��� path - hash
#define BKENG_PERF_UPDATE_HASH_TO_LEVEL         43      ///< ���»��� hash - level

#define BKENG_PERF_FLUSH_PATH_TO_NONPE          50      ///< FLUSH���� path - nonpe
#define BKENG_PERF_FLUSH_PATH_TO_WINTRUST       51      ///< FLUSH���� path - wintrust
#define BKENG_PERF_FLUSH_PATH_TO_HASH           52      ///< FLUSH���� path - hash
#define BKENG_PERF_FLUSH_HASH_TO_LEVEL          53      ///< FLUSH���� hash - level

// ------------------------------------------------------------
// �ļ���������ܲ��Բ���

#define BKENG_PERF_AVENG_MIN                    100     ///< ...

#define BKENG_PERF_AVENG_GET_TYPE               100     ///< ��ȡ�ļ�����
#define BKENG_PERF_AVENG_SCAN                   101     ///< �ļ�����ɨ��
#define BKENG_PERF_AVENG_CLEAN                  102     ///< �ļ��������
#define BKENG_PERF_AVENG_BWM_SCAN               103     ///< ���úڰ׻�ɨ��
#define BKENG_PERF_AVENG_BWM_CLEAN              104     ///< ���úڰ׻����
#define BKENG_PERF_AVENG_BWM_RESCAN             105     ///< ���úڰ׻�ɨ���������ļ�
#define BKENG_PERF_AVENG_GET_VIRUS_NAME         106     ///< ��ȡ������
#define BKENG_PERF_AVENG_OPEN_SCAN_FILE         107     ///< ��ɨ���ļ�
#define BKENG_PERF_AVENG_CREATE_TEMP_FILE       108     ///< ������ʱ�ļ�
#define BKENG_PERF_AVENG_CALC_FILE_TAG          109     ///< �����ļ�ave tag
#define BKENG_PERF_AVENG_PRE_GET_TYPE           110     ///< ��ȡ�ļ�����(ǰ��)

#define BKENG_PERF_AVENG_ARC_GET_TYPE           120     ///< ��ȡѹ��������
#define BKENG_PERF_AVENG_ARC_EXTRACT            121     ///< ��ѹѹ����
#define BKENG_PERF_AVENG_ARC_EXTRACT_SINGLE     122     ///< ��ѹѹ�����еĵ����ļ�

#define BKENG_PERF_AVENG_UNPACK_GET_TYPE        130     ///< ��ȡ������
#define BKENG_PERF_AVENG_UNPACK_UNPACK          131     ///< �ѿ�

#define BKENG_PERF_LOOKUP_PATH_TO_AVEFT         140     ///< ��ѯ���� path - ave file type
#define BKENG_PERF_LOOKUP_PATH_TO_AVEBWM        141     ///< ��ѯ���� path - ave bwm result

#define BKENG_PERF_UPDATE_PATH_TO_AVEFT         150     ///< ���»��� path - ave file type
#define BKENG_PERF_UPDATE_PATH_TO_AVEBWM        151     ///< ��ѯ���� path - ave bwm result

#define BKENG_PERF_FLUSH_PATH_TO_AVEFT          160     ///< FLUSH���� path - ave file type
#define BKENG_PERF_FLUSH_PATH_TO_AVEBWM         161     ///< ��ѯ���� path - ave bwm result

#define BKENG_PERF_LOCAL_HEURIST                170     ///< ��������ʽ

#define BKENG_PERF_KCLOUD_LOCAL_DETECT_1ST      180     ///< �����Ʊ���,��һ��
#define BKENG_PERF_KCLOUD_LOCAL_DETECT_2ND      181     ///< �����Ʊ���,�ڶ���
#define BKENG_PERF_KCLOUD_NET_DETECT            182     ///< ����������

#define BKENG_PERF_AVENG_MAX                    199     ///< ...

// ------------------------------------------------------------

#define BKENG_PERF_MAX_ITEM                     199     ///< ...

//////////////////////////////////////////////////////////////////////////







// ------------------------------------------------------------
// ���ܲ�������

struct BKENG_PERF_DATA
{
    UINT32      uSize;                  ///< �ṹ���С

    // ------------------------------------------------------------
    // Version[1, ?]

    UINT32      m_uPerfCount;           ///< ���Դ���
    UINT64      m_uPerfTotal;           ///< ������ʱ��
    UINT64      m_uTopPerf[10];         ///< ��ʱ��ߵ�10�β��Ե�ʱ��

    // ------------------------------------------------------------
    // Version[?, ?]
};
/// ��ʼ���ṹ��
inline void BKENG_INIT(BKENG_PERF_DATA* pStruct)
{
    assert(pStruct);
    pStruct->uSize          = sizeof(BKENG_PERF_DATA);   

    pStruct->m_uPerfCount   = 0;
    pStruct->m_uPerfTotal   = 0;
    memset(pStruct->m_uTopPerf, 0, sizeof(pStruct->m_uTopPerf));
}






/**
* @brief    ���ܲ����鿴��
*/
class __declspec(uuid("0B93BC23-BEBC-482b-BDD3-9BC68868AD0E"))
IBKEngPerformanceView: public IUnknown
{
public:

    /**
    * @brief        ��ȡ����
    * @param[in]    dwPerfID    �������ID,ȡֵΪ BKENG_PERF_xxx
    * @param[out]   dwPerfData  ��������
    */
    virtual HRESULT STDMETHODCALLTYPE GetPerformanceData(
        DWORD               dwPerfID,
        BKENG_PERF_DATA*    pPerfData) = 0;

    /**
    * @brief        ��Tickת����ϵͳʱ��
    * @param[in]    uTick       tick��
    * @remark       ��λΪ 100 ns
    */
    virtual ULONGLONG STDMETHODCALLTYPE TickToSystemTime(ULONGLONG uTick) = 0;
};




/**
* @brief    ���ܲ�����ȡ�ӿ�
*/
class __declspec(uuid("33FC2590-C8BE-44c1-9E02-8DED6244C76D"))
IBKEngPerformanceCounter: public IUnknown
{
public:

    /**
    * @brief        ��������
    */
    virtual void STDMETHODCALLTYPE ResetPerf() = 0;

    /**
    * @brief        ��ȡ��ǰ��ʱ
    */
    virtual ULONGLONG STDMETHODCALLTYPE GetTick() = 0;

    /**
    * @brief        �������
    * @param[in]    dwPerfID    �������ID,ȡֵΪ BKENG_PERF_xxx
    * @param[in]    uTickDiff   ��������
    */
    virtual void STDMETHODCALLTYPE AddPerf(DWORD dwPerfID, ULONGLONG uTickDiff) = 0;

    /**
    * @brief        ��Tickת����ϵͳʱ��
    * @param[in]    uTick       tick��
    * @remark       ��λΪ 100 ns
    */
    virtual ULONGLONG STDMETHODCALLTYPE TickToSystemTime(ULONGLONG uTick) = 0;
};




NS_SKYLARK_END

#endif//BKPERF_H