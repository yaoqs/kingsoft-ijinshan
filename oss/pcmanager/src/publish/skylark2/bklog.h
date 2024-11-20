/**
* @file    bklog.h
* @brief   ...
* @author  bbcallen
* @date    2010-01-04 17:54
*/

#ifndef BKLOG_H
#define BKLOG_H

#include "bklogdef.h"
#include "bkcache.h"

NS_SKYLARK_BEGIN

/**
* @brief    ɨ����־д��ӿ�
*/
class __declspec(uuid("D4595D08-B6D1-42f4-816C-91A930720794"))
IBKEngScanLogWriter: public IUnknown
{
public:

    /** 
    * @brief    �򿪱�׼����־
    * @param    dwStdCache  Ҫ�򿪵���־id,ȡֵΪ
    *                       BKCACHE_STD_SCAN_LOG
    */
    virtual HRESULT STDMETHODCALLTYPE OpenStandard(DWORD dwStdCache) = 0;


    /** 
    * @brief    ���Զ��建��
    * @param    lpCacheFile �����·��,���ΪNULL,��ȡĬ��λ�õĻ���
    */
    virtual HRESULT STDMETHODCALLTYPE OpenCustom(LPCWSTR lpCacheFile = NULL) = 0;




    /// д����־
    virtual HRESULT STDMETHODCALLTYPE WriteLog(const BKENG_SCAN_LOG* pLog) = 0;

    /// д����־
    virtual HRESULT STDMETHODCALLTYPE WriteResultAsLog(LPCWSTR lpszFilePath, const BKENG_RESULT* pResult) = 0;


    /// ɾ��������־
    virtual HRESULT STDMETHODCALLTYPE DeleteExpiredLogs() = 0;

    /// ɾ��������־
    virtual HRESULT STDMETHODCALLTYPE DeleteAllLogs() = 0;



    /// ����־���浽�ļ�
    virtual HRESULT STDMETHODCALLTYPE SaveToFile() = 0;
};



/**
* @brief    ��־��ȡ�ӿ�
*/
class __declspec(uuid("F0A73B6F-EA9D-445a-B80E-B30F34E990CE"))
IBKEngScanLogReader: public IUnknown
{
public:


    /** 
    * @brief    �򿪱�׼����־
    * @param    dwStdCache  Ҫ�򿪵���־id,ȡֵΪ
    *                       BKCACHE_STD_SCAN_LOG
    */
    virtual HRESULT STDMETHODCALLTYPE OpenStandard(DWORD dwStdCache) = 0;


    /** 
    * @brief    ���Զ��建��
    * @param    lpCacheFile �����·��,���ΪNULL,��ȡĬ��λ�õĻ���
    */
    virtual HRESULT STDMETHODCALLTYPE OpenCustom(LPCWSTR lpCacheFile = NULL) = 0;



    /**
    * @brief        ��ȡ��־����
    */ 
    virtual DWORD STDMETHODCALLTYPE GetLogCount() = 0;

    /**
    * @brief        ��ȡ��־
    * @param[out]   logArray    �����ȡ����־����, ��Ҫ�ܹ�����dwCount��Ԫ��
    * @param[out]   pdwLogCount ���ض�ȡ����־��Ŀ, ������dwCount
    * @param[in]    dwOffset    ��ȡ��ƫ��(��0��ʼ����)
    * @param[in]    dwCount     Ҫ��ȡ����־�ĸ���
    */ 
    virtual HRESULT STDMETHODCALLTYPE ReadLog(
        BKENG_SCAN_LOG  logArray[],
        DWORD*          pdwLogCount,
        DWORD           dwOffset = 0,
        DWORD           dwCount  = 1) = 0;
};

NS_SKYLARK_END

#endif//BKLOG_H