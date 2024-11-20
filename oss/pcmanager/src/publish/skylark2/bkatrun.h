/**
* @file    bkatrun.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-27 11:06
*/

#ifndef BKATRUN_H
#define BKATRUN_H

#include "bkatrundef.h"

NS_SKYLARK_BEGIN

/// autorunɨ������Ŀ
class __declspec(uuid("B762E747-D0D5-4c73-8CED-0458E9DB62E0"))
IBKAutorunItem: public IUnknown
{
public:

    /// ��ȡ������ID
    virtual UINT32  STDMETHODCALLTYPE GetAutorunID() = 0;

    /// ��ȡ���������ID
    virtual UINT32  STDMETHODCALLTYPE GetAutorunGroupID() = 0;               

    /// ��ȡ���������Ϣ(��������ʾ)
    virtual LPCWSTR STDMETHODCALLTYPE GetInformation() = 0;



    /// ��ȡ������������ļ���Ŀ
    virtual UINT32  STDMETHODCALLTYPE GetFileCount() = 0;

    /// ��ȡ������������ļ�·��
    virtual LPCWSTR STDMETHODCALLTYPE GetFilePathAt(UINT32 uIndex) = 0;



    /// �ж�ָ���������Ƿ��ܱ��޸�
    virtual BOOL    STDMETHODCALLTYPE CanBeRepaired() = 0;

    /// �޸�ָ��������, ����S_FALSE, ��������Ҫ�޸�
    virtual HRESULT STDMETHODCALLTYPE Repair(BKATRUN_REPAIR_PARAM* pRepairParam) = 0;




    //////////////////////////////////////////////////////////////////////////
    // ���ýӿ�,����δʵ��

    ///// �ж�ָ���������Ƿ��ܱ��޸�
    //virtual BOOL    STDMETHODCALLTYPE CanBeDisabled() = 0;

    ///// �޸�ָ��������
    //virtual HRESULT STDMETHODCALLTYPE Disable(void* pvReserved) = 0;




    ////////////////////////////////////////////////////////////////////////////
    //// ��Ϣ�ӿ�,����δʵ��

    //// �����ǻ�ȡ��չ��Ϣ�Ľӿ�,����δʵ��
    //virtual LPCWSTR     STDMETHODCALLTYPE GetString(    UINT32 uID, LPCWSTR nullValue = L"") = 0;
    //virtual UINT32      STDMETHODCALLTYPE GetUInt(      UINT32 uID, UINT32 nullValue = 0) = 0;
    //virtual UINT64      STDMETHODCALLTYPE GetUInt64(    UINT32 uID, UINT64 nullValue = 0) = 0;
    //virtual UINT32      STDMETHODCALLTYPE GetBlob(      UINT32 uID, BYTE* pBlog, UINT32 nBlogBytes) = 0;
    //virtual UINT32      STDMETHODCALLTYPE GetBlobBytes( UINT32 uID) = 0;
};


/**
* @brief    autorunɨ�����ķ�װ
* @remark   ���Ҫ֧��ɨ��ƻ�����,�����ɨ���߳��г�ʼ��COM
*/
class __declspec(uuid("AC489AB3-530C-408c-9B3F-6CAFE9A3DD0C"))
IBKAutorunScanner: public IUnknown
{
public:

    /**
    * @brief        ��ʼ��ɨ������
    */ 
    virtual HRESULT STDMETHODCALLTYPE StartScan(BKATRUN_SCAN_PARAM* pScanParam) = 0;

    /**
    * @brief        ɨ����һ��������
    */ 
    virtual BOOL    STDMETHODCALLTYPE FindNextItem(IBKAutorunItem** ppiAtrItem) = 0;
};


/**
* @brief    autorunɨ���������ܲ��Բ���
*/
class __declspec(uuid("B77E4A52-DA85-4a5d-9E72-03EAC816E73E"))
IBKAutorunPerformView: public IUnknown
{
public:
    /**
    * @brief        ��ȡ������ɨ����������ܲ���
    * @param        dwPerfID    ���ܲ�����Ŀ,ȡֵΪBKATR_PERF_COUNT__xxx
    */ 
    virtual DWORD   STDMETHODCALLTYPE GetPerfCount(DWORD dwPerfID) = 0;
};


NS_SKYLARK_END



#define  FN_BKAtrunCreateObject "BKAtrunCreateObject"   ///< export BKAtrunCreateObject


/**
* @brief    ����BKAtrun��ģ��
* @param    dwBKEngVer  BKEng�İ汾��,Ĭ��ʹ��BKENG_CURRENT_VERSION,����0��ʾ�����汾���
* @param    riid        Ҫ�����Ķ����iid
* @param    ppvObj      ���ش����Ķ���
*/
EXTERN_C HRESULT WINAPI BKAtrunCreateObject(REFIID riid, void** ppvObj, DWORD dwBKEngVer = BKENG_CURRENT_VERSION);
/// typedef for BKAtrunCreateObject
typedef HRESULT (WINAPI *PFN_BKAtrunCreateObject)(REFIID riid, void** ppvObj, DWORD dwBKEngVer);



#endif//BKATRUN_H