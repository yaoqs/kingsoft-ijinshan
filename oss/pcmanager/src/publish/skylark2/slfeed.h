/**
* @file    slfeed.h
* @brief   ...
* @author  zhangrui
* @date    2009-03-02  15:21
*/

#ifndef SLFEED_H
#define SLFEED_H

#include <unknwn.h>
#include "skylarkbase.h"
#include "slfeedschema.h"
#include "slfeedcode.h"
#include "slfeedaudit.h"



inline HRESULT WINAPI SkylarkFeedAudit(DWORD, DWORD, DWORD, DWORD = 1)
{
    return S_FALSE;
}

inline HRESULT WINAPI SkylarkFeedDebugLog(DWORD, DWORD, DWORD, LPCWSTR, DWORD = 1)
{
    return S_FALSE;
}

inline HRESULT WINAPI SkylarkFeedStatistic(DWORD, DWORD, DWORD, DWORD = 1)
{
    return S_FALSE;
}

inline HRESULT WINAPI SkylarkInitializeFeeder(DWORD, DWORD)
{
    return S_FALSE;
}

inline HRESULT WINAPI SkylarkUninitializeFeeder(DWORD = 1000)
{
    return S_FALSE;
}

inline HRESULT WINAPI SkylarkGetMid(LPWSTR, DWORD)
{
    return S_FALSE;
}


inline DWORD WINAPI SkylarkGetProductID()
{
    return SLK_PID_KSAFE;
}

inline DWORD WINAPI SkylarkGetChannelID()
{
    return 0;
}

inline DWORD WINAPI SkylarkGetFeedVer()
{
    return 0;
}

inline HRESULT WINAPI SkylarkRenewFeedVer(DWORD)
{
    return S_FALSE;
}




#define SKYLARK_MID_BUF_SIZE        64      ///< mid��buf����(��ʵ�����ݳ��ȳ�)

#define SLFEED_METHOD_IMMEDIATELY   0       ///< ��������(����)
#define SLFEED_METHOD_ASYNC         1       ///< �첽����(������)
#define SLFEED_METHOD_OFFLINE       2       ///< �ѻ�����(�ӳٷ���)

#if 0

/**
* @brief    ����Ϣ�ռ����������������־
* @param    dwProductID     ��ƷID
* @param    dwChannelID     ͨ��ID,��������
* @param    dwActionID      �ID
* @param    dwFeedMethod    ���ͷ�ʽ,ȡֵΪSLFEED_METHOD_XXX
@verbatim
������ݰ���������
    [�Զ���ȡ] 
    mid         �����汾ʶ���mid
    ip          ������Զ���ȡ
    time        ������Զ���ȡ
    ver         �ͻ��˰汾��

    [������д]
    pid         ��Ʒid
    chid        ͨ����,ʶ���Ʒ�ķַ�;��
    act         �
@endverbatim
*/
EXTERN_C HRESULT WINAPI SkylarkFeedAudit(
    DWORD   dwProductID,
    DWORD   dwChannelID,
    DWORD   dwActionID,
    DWORD   dwFeedMethod = SLFEED_METHOD_ASYNC);
/// typedef for SkylarkFeedAudit
typedef HRESULT (WINAPI *PFN_SkylarkFeedAudit)(
    DWORD   dwProductID,
    DWORD   dwChannelID,
    DWORD   dwActionID,
    DWORD   dwFeedMethod);



/**
* @brief    ����Ϣ�ռ�������������־
* @param    dwSchemaID      ��Ϣ������id,��info���ݿ�Ĺ�����ͳһ����,��slfeedschema.h
* @param    dwInfoCode      ��Ϣ��,��������������ж���,ͨ����Ԥ�����ֵ,��slfeedschema.h
* @param    dwInfoParam     ��Ϣ����,��������������ж���,ͨ�����ױ��ֵ,����GetLastError()�ķ���ֵ
* @param    lpszInfoMessage �ַ�����Ϣ,��������������ж���,ʹ�øò������ܵ��·���������������
* @param    dwFeedMethod    ���ͷ�ʽ,ȡֵΪSLFEED_METHOD_XXX
@verbatim
������־����������
    [�Զ���ȡ] 
    mid         �����汾ʶ���mid
    ip          ������Զ���ȡ
    time        ������Զ���ȡ
    ver         �ͻ��˰汾��

    [������д]
    schema
    code
    param
    message
@endverbatim
*/
EXTERN_C HRESULT WINAPI SkylarkFeedDebugLog(
    DWORD   dwSchemaID,
    DWORD   dwInfoCode,
    DWORD   dwInfoParam,
    LPCWSTR lpszInfoMessage,
    DWORD   dwFeedMethod = SLFEED_METHOD_ASYNC);
/// typedef for SkylarkFeedDebugLog
typedef HRESULT (WINAPI *PFN_SkylarkFeedDebugLog)(
    DWORD   dwSchemaID,
    DWORD   dwInfoCode,
    DWORD   dwInfoParam,
    LPCWSTR lpszInfoMessage,
    DWORD   dwFeedMethod);






/**
* @brief    ����Ϣ�ռ�����������ͳ����־
* @param    dwSchemaID      ��Ϣ������id,��info���ݿ�Ĺ�����ͳһ����,��slfeedschema.h
* @param    dwInfoCode      ��Ϣ��,��������������ж���,ͨ����Ԥ�����ֵ,��slfeedschema.h
* @param    dwInfoParam     ��Ϣ����,��������������ж���,ͨ�����ױ��ֵ,����GetLastError()�ķ���ֵ
* @param    dwFeedMethod    ���ͷ�ʽ,ȡֵΪSLFEED_METHOD_XXX
*/
EXTERN_C HRESULT WINAPI SkylarkFeedStatistic(
    DWORD   dwSchemaID,
    DWORD   dwInfoCode,
    DWORD   dwInfoParam,
    DWORD   dwFeedMethod = SLFEED_METHOD_ASYNC);
/// typedef for SkylarkFeedStatistic
typedef HRESULT (WINAPI *PFN_SkylarkFeedStatistic)(
    DWORD   dwSchemaID,
    DWORD   dwInfoCode,
    DWORD   dwInfoParam,
    DWORD   dwFeedMethod);






/**
* @brief    ����Ϣ�ռ����������ͱ���
* @param    dwSchemaID      ��Ϣ������id,��info���ݿ�Ĺ�����ͳһ����,��slfeedschema.h
* @param    dwInfoCode      ��Ϣ��,��������������ж���,ͨ����Ԥ�����ֵ,��slfeedschema.h
* @param    dwInfoParam     ��Ϣ����,��������������ж���,ͨ�����ױ��ֵ,����GetLastError()�ķ���ֵ
* @param    lpszInfoMessage �ַ�����Ϣ,�ݶ���󳤶�Ϊ 65535 bytes
* @param    dwFeedMethod    ���ͷ�ʽ,ȡֵΪSLFEED_METHOD_XXX
*/
EXTERN_C HRESULT WINAPI SkylarkFeedReport(
    DWORD   dwSchemaID,
    DWORD   dwInfoCode,
    DWORD   dwInfoParam,
    LPCWSTR lpszInfoMessage,
    DWORD   dwFeedMethod = SLFEED_METHOD_ASYNC);
/// typedef for SkylarkFeedStatistic
typedef HRESULT (WINAPI *PFN_SkylarkFeedReport)(
    DWORD   dwSchemaID,
    DWORD   dwInfoCode,
    DWORD   dwInfoParam,
    LPCWSTR lpszInfoMessage,
    DWORD   dwFeedMethod);







// ����ΪFeeder�Ŀ��ƺ���

/**
* @brief    ����Ϣ�ռ������������첽��־
* @param    bKeepFileIfFailedToSend     ���ΪFALSE,��ô����ʧ�ܺ�,��ɾ������ʧ�ܵ���־
*/
EXTERN_C HRESULT WINAPI SendOfflineFeedReport(BOOL bKeepFileIfFailedToSend);
/// typedef for SendOfflineFeedReport
typedef HRESULT (WINAPI *PFN_SendOfflineFeedReport)(BOOL bKeepFileIfFailedToSend);




/**
* @brief        ��ʼ��ȫ�ֵ�feeder,����δ��������־���ᱻ����
* @param        dwProductID         ��Ʒid
* @param        dwChannelID         ��Ʒͨ��id
* @note         SkylarkInitialize   ����øú���
*/
EXTERN_C HRESULT WINAPI SkylarkInitializeFeeder(DWORD dwProductID, DWORD dwChannelID);
/// typedef for SkylarkInitializeFeeder
typedef HRESULT (WINAPI *PFN_SkylarkInitializeFeeder)();

/**
* @brief        ����ʼ��ȫ�ֵ�feeder,����δ��������־���ᱻ����
* @param[in]    dwMilliSeconds      ��ʱʱ��,��λΪ����
* @note         SkylarkUninitialize ����øú���
*/
EXTERN_C HRESULT WINAPI SkylarkUninitializeFeeder(DWORD dwMilliSeconds = 1000);
/// typedef for SkylarkUninitializeFeeder
typedef HRESULT (WINAPI *PFN_SkylarkUninitializeFeeder)(DWORD dwMilliSeconds);

/**
* @brief        ��ȡmid
* @param[out]   szMid       ����mid
* @param[in]    cchBufLen   mid
* @note         Mid �ַ�������Ϊ40,����buf��������Ϊ41
*/
EXTERN_C HRESULT WINAPI SkylarkGetMid(LPWSTR szMid, DWORD cchBufLen);
/// typedef for SkylarkGetMid
typedef HRESULT (WINAPI *PFN_SkylarkGetMid)(LPWSTR szMid, DWORD cchBufLen);



/**
* @brief        ��ȡ��Ʒid
*/
EXTERN_C DWORD WINAPI SkylarkGetProductID();
/// typedef for SkylarkGetFeedChannel
typedef DWORD (WINAPI *PFN_SkylarkGetProductID)();

/**
* @brief        ��ȡ��Ʒͨ����
*/
EXTERN_C DWORD WINAPI SkylarkGetChannelID();
/// typedef for SkylarkGetFeedChannel
typedef DWORD (WINAPI *PFN_SkylarkGetChannelID)();


/**
* @brief        ��ȡfeed�汾��
*/
EXTERN_C DWORD WINAPI SkylarkGetFeedVer();
/// typedef for SkylarkGetFeedVer
typedef DWORD (WINAPI *PFN_SkylarkGetFeedVer)();

/**
* @brief        ����feed�汾��,ͨ���������������
* @param[in]    dwVersion           �����µ�mid
*/
EXTERN_C HRESULT WINAPI SkylarkRenewFeedVer(DWORD dwVersion);
/// typedef for SkylarkRenewFeedVer
typedef HRESULT (WINAPI *PFN_SkylarkRenewFeedVer)(DWORD dwVersion);



/**
* @brief        ��midΪ����,��ȡhashֵ
* @param[in]    dwMaxHash   hash�����ȡֵ, �ο���ʵ��Ϊ crc32(mid) % (dwMaxHash + 1)
*/
EXTERN_C DWORD WINAPI SkylarkFeedHashCodeByMid(DWORD dwMaxHash);
/// typedef for SkylarkFeedHashCodeByMid
typedef DWORD (WINAPI *PFN_SkylarkFeedHashCodeByMid)(DWORD dwMaxHash);

#endif




#endif//SLFEED_H