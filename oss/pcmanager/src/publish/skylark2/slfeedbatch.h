/**
* @file    slfeedbatch.h
* @brief   ...
* @author  zhangrui
* @date    2009-05-22  11:41
*/

#ifndef SLFEEDBATCH_H
#define SLFEEDBATCH_H

#include <wininet.h>
#include <unknwn.h>
#include "skylarkbase.h"
#include "slfeed.h"

NS_SKYLARK_BEGIN

/// �ϴ�feed��־�Ľӿ�
class __declspec(uuid("EC3C9CE5-FD9D-40d2-A8D8-E681C17A6780"))
IFeedBatch: public IUnknown
{
public:

    /// ...
    virtual HRESULT STDMETHODCALLTYPE Post(HINTERNET hInetSession = NULL) = 0;

    /// ...
    virtual HRESULT STDMETHODCALLTYPE PostEx(
        LPCWSTR     lpszMid,
        DWORD       dwProductID,
        DWORD       dwChannelID,
        DWORD       dwFeedVer,
        HINTERNET   hInetSession = NULL) = 0;
};


/// �����ϴ�feed��־�Ľӿ�
class __declspec(uuid("CC86DBC7-35EA-4160-9B4D-3DA546190BD9"))
IFeedDebugLogBatch: public IFeedBatch
{
public:

    /**
    * @brief    ����Ϣ�ռ�������������־
    * @param    dwSchemaID      ��Ϣ������id,��info���ݿ�Ĺ�����ͳһ����,��slfeedschema.h
    * @param    dwInfoCode      ��Ϣ��,��������������ж���,ͨ����Ԥ�����ֵ,��slfeedschema.h
    * @param    dwInfoParam     ��Ϣ����,��������������ж���,ͨ�����ױ��ֵ,����GetLastError()�ķ���ֵ
    * @param    lpszInfoMessage �ַ�����Ϣ,��������������ж���,ʹ�øò������ܵ��·���������������
    * @note     ԭ����,ʹ��������־ʱ,Ӧ�þ����ܷ���ͬ������־,�Ա��������ֱ����
    */
    virtual HRESULT STDMETHODCALLTYPE FeedDebugLog(
        DWORD   dwSchemaID,
        DWORD   dwInfoCode,
        DWORD   dwInfoParam,
        LPCWSTR lpszInfoMessage) = 0;
};

NS_SKYLARK_END


/// class Factory
EXTERN_C HRESULT WINAPI SkylarkCreateFeedDebugLogBatch(Skylark::IFeedDebugLogBatch** ppiObj);
/// typedef SkylarkCreateSecurityProductInfo
typedef HRESULT (WINAPI *PFN_SkylarkCreateFeedDebugLogBatch)(Skylark::IFeedDebugLogBatch** ppiObj);


#endif//SLFEEDBATCH_H