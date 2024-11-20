/**
* @file    bkksup.h
* @brief   ...
* @author  bbcallen
* @date    2010-01-22 17:42
*/

#ifndef BKKSUP_H
#define BKKSUP_H

#include "bkksupdef.h"

NS_SKYLARK_BEGIN

class IBKEngKsgUpdateCallback;

/**
* @brief    ���Բ����������ӿ�
*/
class __declspec(uuid("EF9CC682-9035-4697-B271-59BC9565F20B"))
IBKEngKsgUpdate: public IUnknown
{
public:

    /**
    * @brief        ��ʼ������
    * @param[in]    pInit           ��ʼ������
    */
    virtual HRESULT STDMETHODCALLTYPE Initialize(BKKSUP_INIT* pInit) = 0;


    /**
    * @brief        ����ʼ��ɨ������
    */
    virtual HRESULT STDMETHODCALLTYPE Uninitialize() = 0;


    /**
    * @brief        ����Ƿ���Ҫ����
    * @param[in]    pUpdateParam        ��������
    * @param[out]   pUpdateInstruction  ����ָʾ
    */ 
    virtual HRESULT STDMETHODCALLTYPE CheckUpdate(
        const BKKSUP_UPDATE_PARAM* pUpdateParam,
        BKKSUP_UPDATE_INSTRUCTION* pUpdateInstruction) = 0;


    /**
    * @brief        ��ʼ����
    * @param[in]    pUpdateParam        ��������
    * @param[out]   pUpdateInstruction  ����ָʾ
    * @remark       Update ����� CheckUpdate, ���Բ���Ҫ�ȵ��� CheckUpdate
    */ 
    virtual HRESULT STDMETHODCALLTYPE Update(
        const BKKSUP_UPDATE_PARAM* pUpdateParam,
        BKKSUP_UPDATE_INSTRUCTION* pUpdateInstruction) = 0;


    /**
    * @brief        ֪ͨ����ֹͣ
    * @remark       �������Ƿ���������
    */ 
    virtual HRESULT STDMETHODCALLTYPE NotifyStop() = 0;


    /**
    * @brief        ��ȡ���ز�����汾
    * @param[in]    pLocalSignVersion   ���ز�����汾
    */ 
    virtual HRESULT STDMETHODCALLTYPE GetLocalSignVersion(
        BKAVE_SIGN_VERSION* pLocalSignVersion) = 0;
};








/**
* @brief    ���Բ����������ص��ӿ�
*/
class __declspec(uuid("234FC5F4-5815-4f2f-BF58-11DC2ED69C42"))
IBKEngKsgUpdateCallback
{
public:

   /**
    * @brief        �����ļ�ǰ�ص�
    * @param[in]    lpszFileName            ���ص��ļ���
    * @param[in]    dwFileSize              �ļ���С(ѹ��ǰ)
    */ 
    virtual HRESULT STDMETHODCALLTYPE OnPrepareFile(
        LPCWSTR     lpszFileName,
        DWORD       dwFileSize) = 0;

   /**
    * @brief        �����ļ�ʱ�ص�
    * @param[in]    lpszFileName            ���ص��ļ���
    * @param[in]    dwTotalSize             �ļ��ܳ���(ѹ����)
    * @param[in]    dwReceiveSize           �Ѿ����յĴ�С(ѹ����)
    */ 
    virtual HRESULT STDMETHODCALLTYPE OnDownloadFile(
        LPCWSTR     lpszFileName,
        DWORD       dwTotalSize,
        DWORD       dwDownloadedSize) = 0;

    /**
    * @brief        �����ļ�������
    * @param[in]    lpszFileName            ���ص��ļ���
    * @param[in]    dwFileSize              �ļ���С(ѹ��ǰ)
    * @param[in]    hrDownload              ������(����������)
    * @remark       �������ʧ�ܵ�������,��ô�����һ��������ɺ�,�Żᷢ���ûص�
    */ 
    virtual HRESULT STDMETHODCALLTYPE FinishDownloadFile(
        LPCWSTR     lpszFileName,
        DWORD       dwFileSize,
        HRESULT     hrDownload) = 0;

    /**
    * @brief        �滻�ļ�ʱ�ص�
    * @param[in]    lpszFileName            ���ص��ļ���
    * @param[in]    lpszDstPath             ���滻���ļ�λ��
    * @param[in]    hrReplace               ������(����������)
    */ 
    virtual HRESULT STDMETHODCALLTYPE OnReplaceFile(
        LPCWSTR     lpszFileName,
        LPCWSTR     lpszDstPath,
        HRESULT     hrReplace) = 0;
};


NS_SKYLARK_END






#define FN_BKKsupCreateObject			"BKKsupCreateObject"



/**
* @brief    ����ʵ��
* @param    dwBKEngVer  BKEng�İ汾��,Ĭ��ʹ��BKENG_CURRENT_VERSION,����0��ʾ�����汾���
* @param    riid        Ҫ�����Ķ����iid
* @param    ppvObj      ���ش����Ķ���
*/
EXTERN_C HRESULT WINAPI BKKsupCreateObject(REFIID riid, void** ppvObj, DWORD dwBKEngVer = BKENG_CURRENT_VERSION);
/// typedef for BKKsupCreateObject
typedef HRESULT (WINAPI *PFN_BKKsupCreateObject)(REFIID riid, void** ppvObj, DWORD dwBKEngVer);



#endif//BKKSUP_H