/**
* @file    bkcache.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-16 17:37
*/

#ifndef BKCACHE_H
#define BKCACHE_H

#include <unknwn.h>
#include "skylarkbase.h"
#include "bkdb.h"
#include "bkcachedef.h"

NS_SKYLARK_BEGIN



/**
* @brief    ���� path -> hash
* @remark   nidx(<path>, md5, crc32, timestamp, tag)
*/
class __declspec(uuid("FEB9A481-88A5-4eef-82C9-3B16202F97C5"))
IBKCachePathToHash: public IUnknown
{
public:

    /** 
    * @brief    �򿪱�׼�Ļ���
    * @param    dwStdCache  Ҫ�򿪵Ļ���id,ȡֵΪ
    *           BKCACHE_STD_PATH_TO_HASH
    */
    virtual HRESULT STDMETHODCALLTYPE OpenStandard(DWORD dwStdCache) = 0;


    /** 
    * @brief    ���Զ���Ļ���
    * @param    lpCacheFile �����·��,���ΪNULL,��ȡĬ��λ�õĻ���
    */
    virtual HRESULT STDMETHODCALLTYPE OpenCustom(LPCWSTR lpCacheFile = NULL) = 0;


    /**
    * @brief        �������
    * @param[in]    lpszFilePath    �ļ�·��
    * @param[out]   pRecord          ���ص�cache��Ϣ
    */ 
    virtual HRESULT STDMETHODCALLTYPE Lookup(
        LPCWSTR                 lpszFilePath,
        BKCACHE_PATH_TO_HASH*   pRecord) = 0;


    /**
    * @brief        ���»���
    * @param[in]    lpszFilePath    �ļ�·��
    * @param[in]    pRecord         ���ص�cache��Ϣ
    * @remark       ����¼�¼��ʱ�������,ԭ�м�¼���ᱻ����
    */ 
    virtual HRESULT STDMETHODCALLTYPE Update(
        LPCWSTR                     lpszFilePath,
        const BKCACHE_PATH_TO_HASH* pRecord) = 0;


    /**
    * @brief        ɾ������
    * @param[in]    lpszFilePath    �ļ�·��
    */
    virtual HRESULT STDMETHODCALLTYPE Delete(LPCWSTR lpszFilePath) = 0;


    /**
    * @brief        ɾ�����ڵĻ���(����,��δʵ��)
    */
    virtual HRESULT STDMETHODCALLTYPE DeleteExpired() = 0;


    /**
    * @brief        ���ڴ��м�¼ͬ�������ݿ��ļ�,��ʱ�Ĳ���
    */
    virtual HRESULT STDMETHODCALLTYPE Flush() = 0;




    /// ��ȡ����
    virtual HRESULT STDMETHODCALLTYPE GetSettings(BKCACHE_SETTINGS_PATH_TO_HASH* pSettings) = 0;

    /// �޸�����,���ΪNULL,��ָ�Ĭ������
    virtual HRESULT STDMETHODCALLTYPE SetSettings(const BKCACHE_SETTINGS_PATH_TO_HASH* pSettings) = 0;



    /// ��������
    virtual HRESULT STDMETHODCALLTYPE BeginTransaction(BKDb::EM_TRANSLOCK transLock = BKDb::em_Deferred) = 0;

    /// �ύ����
    virtual HRESULT STDMETHODCALLTYPE CommitTransaction() = 0;

    /// �ع�����
    virtual HRESULT STDMETHODCALLTYPE RollbackTransaction() = 0;

    /// ��鵱ǰ�����Ƿ���������
    virtual BOOL    STDMETHODCALLTYPE IsInTransaction() = 0;

    /// ��ȡ��ǰʱ��
    virtual ULONGLONG STDMETHODCALLTYPE GetCurrentTimeAsTimeStamp() = 0;

};







/**
* @brief    ���� hash -> level
* @remark   nidx(<path>, md5, crc32, timestamp, tag)
*/
class __declspec(uuid("9AF3DB0D-A098-47e1-A1D8-7FF4AD675A48"))
IBKCacheHashToLevel: public IUnknown
{
public:

    /** 
    * @brief    �򿪱�׼�Ļ���
    * @param    dwStdCache  Ҫ�򿪵Ļ���id,ȡֵΪ
    *           BKCACHE_STD_HASH_TO_LEVEL
    */
    virtual HRESULT STDMETHODCALLTYPE OpenStandard(DWORD dwStdCache) = 0;


    /** 
    * @brief    ���Զ��建��
    * @param    lpCacheFile �����·��,���ΪNULL,��ȡĬ��λ�õĻ���
    */
    virtual HRESULT STDMETHODCALLTYPE OpenCustom(LPCWSTR lpCacheFile = NULL) = 0;


    /**
    * @brief        �������
    * @param[in]    byMD5       md5
    * @param[in]    uCRC32      crc32
    * @param[out]   pRecord     ���ص�cache��Ϣ
    */ 
    virtual HRESULT STDMETHODCALLTYPE Lookup(
        const BYTE              byMD5[SKYLARK_MD5_BYTES],
        UINT32                  uCRC32,
        BKCACHE_HASH_TO_LEVEL*  pRecord) = 0;


    /**
    * @brief        ���»���
    * @param[in]    byMD5       md5
    * @param[in]    uCRC32      crc32
    * @param[in]    pRecord     ���ص�cache��Ϣ
    * @remark       ����¼�¼��ʱ�������,ԭ�м�¼���ᱻ����
    */ 
    virtual HRESULT STDMETHODCALLTYPE Update(
        const BYTE                      byMD5[SKYLARK_MD5_BYTES],
        UINT32                          uCRC32,
        const BKCACHE_HASH_TO_LEVEL*    pRecord) = 0;


    /**
    * @brief        ɾ������
    * @param[in]    byMD5       md5
    * @param[in]    uCRC32      crc32
    */
    virtual HRESULT STDMETHODCALLTYPE Delete(const BYTE byMD5[SKYLARK_MD5_BYTES], UINT32 uCRC32) = 0;


    /**
    * @brief        ɾ�����ڵĻ���(����,��δʵ��)
    */
    virtual HRESULT STDMETHODCALLTYPE DeleteExpired() = 0;


    /**
    * @brief        ���ڴ��м�¼ͬ�������ݿ��ļ�,��ʱ�Ĳ���
    */
    virtual HRESULT STDMETHODCALLTYPE Flush() = 0;




    /// ��ȡ����
    virtual HRESULT STDMETHODCALLTYPE GetSettings(BKCACHE_SETTINGS_HASH_TO_LEVEL* pSettings) = 0;

    /// �޸�����,���ΪNULL,��ָ�Ĭ������
    virtual HRESULT STDMETHODCALLTYPE SetSettings(const BKCACHE_SETTINGS_HASH_TO_LEVEL* pSettings) = 0;



    /// ��������
    virtual HRESULT STDMETHODCALLTYPE BeginTransaction(BKDb::EM_TRANSLOCK transLock = BKDb::em_Deferred) = 0;

    /// �ύ����
    virtual HRESULT STDMETHODCALLTYPE CommitTransaction() = 0;

    /// �ع�����
    virtual HRESULT STDMETHODCALLTYPE RollbackTransaction() = 0;

    /// ��鵱ǰ�����Ƿ���������
    virtual BOOL    STDMETHODCALLTYPE IsInTransaction() = 0;

    /// ��ȡ��ǰʱ��
    virtual ULONGLONG STDMETHODCALLTYPE GetCurrentTimeAsTimeStamp() = 0;

};




/**
* @brief    ���� hash -> level
* @remark   nidx(<path>, md5, crc32, timestamp, tag)
*/
class __declspec(uuid("9942D1EC-7B54-4e1c-8F58-5F4F38E95FF6"))
IBKCacheHashToLevel2: public IBKCacheHashToLevel
{
public:
    /** 
    * @brief    ���Զ��建��
    * @param    lpCacheFile     �����·��,���ΪNULL,��ȡĬ��λ�õĻ���
    * @param    pPassword       ��Կ
    * @param    dwPasswordBytes ��Կ����
    * @param    bCreateNewIfFailedToOpen �����ʧ��,�Ƿ��Դ��������ݿ�
    */
    virtual HRESULT STDMETHODCALLTYPE OpenCustom(
        LPCWSTR lpCacheFile,
        void*   pPassword,
        DWORD   dwPasswordBytes,
        BOOL    bCreateNewIfFailedToOpen = TRUE) = 0;
};


/**
* @brief    ���� path -> tag
* @remark   nidx(<path>, md5, crc32, timestamp, tag)
*/
class __declspec(uuid("EA7CA7BA-9350-4894-9099-8D5E4B01A79F"))
IBKCachePathToHRESULT: public IUnknown
{
public:

    /** 
    * @brief    �򿪱�׼�Ļ���
    * @param    dwStdCache  Ҫ�򿪵Ļ���id,ȡֵΪ
    *           BKCACHE_STD_PATH_TO_WINTRUST,
    *           BKCACHE_STD_PATH_TO_NONPE,
    *           BKCACHE_STD_PATH_TO_AVEFT,
    *           BKCACHE_STD_PATH_TO_AVEBWM,
    *           BKCACHE_STD_PATH_TO_DELETE_TRACE,
    */
    virtual HRESULT STDMETHODCALLTYPE OpenStandard(DWORD dwStdCache) = 0;


    /** 
    * @brief    �򿪻���
    * @param    lpCacheFile �����·��,���ΪNULL,��ȡĬ��λ�õĻ���
    */
    virtual HRESULT STDMETHODCALLTYPE OpenCustom(LPCWSTR lpCacheFile = NULL) = 0;


    /**
    * @brief        �������
    * @param[in]    lpszFilePath    �ļ�·��
    * @param[out]   pRecord         ���ص�cache��Ϣ
    */ 
    virtual HRESULT STDMETHODCALLTYPE Lookup(
        LPCWSTR                     lpszFilePath,
        BKCACHE_PATH_TO_HRESULT*    pRecord) = 0;


    /**
    * @brief        ���»���
    * @param[in]    lpszFilePath    �ļ�·��
    * @param[in]    pRecord         ���ص�cache��Ϣ
    * @remark       ����¼�¼��ʱ�������,ԭ�м�¼���ᱻ����
    */ 
    virtual HRESULT STDMETHODCALLTYPE Update(
        LPCWSTR                         lpszFilePath,
        const BKCACHE_PATH_TO_HRESULT*  pRecord) = 0;


    /**
    * @brief        ɾ������
    * @param[in]    lpszFilePath    �ļ�·��
    */
    virtual HRESULT STDMETHODCALLTYPE Delete(LPCWSTR lpszFilePath) = 0;


    /**
    * @brief        ɾ�����ڵĻ���(����,��δʵ��)
    */
    virtual HRESULT STDMETHODCALLTYPE DeleteExpired() = 0;


    /**
    * @brief        ���ڴ��м�¼ͬ�������ݿ��ļ�,��ʱ�Ĳ���
    */
    virtual HRESULT STDMETHODCALLTYPE Flush() = 0;




    /// ��ȡ����
    virtual HRESULT STDMETHODCALLTYPE GetSettings(BKCACHE_SETTINGS_PATH_TO_HRESULT* pSettings) = 0;

    /// �޸�����,���ΪNULL,��ָ�Ĭ������
    virtual HRESULT STDMETHODCALLTYPE SetSettings(const BKCACHE_SETTINGS_PATH_TO_HRESULT* pSettings) = 0;



    /// ��������
    virtual HRESULT STDMETHODCALLTYPE BeginTransaction(BKDb::EM_TRANSLOCK transLock = BKDb::em_Deferred) = 0;

    /// �ύ����
    virtual HRESULT STDMETHODCALLTYPE CommitTransaction() = 0;

    /// �ع�����
    virtual HRESULT STDMETHODCALLTYPE RollbackTransaction() = 0;

    /// ��鵱ǰ�����Ƿ���������
    virtual BOOL    STDMETHODCALLTYPE IsInTransaction() = 0;

    /// ��ȡ��ǰʱ��
    virtual ULONGLONG STDMETHODCALLTYPE GetCurrentTimeAsTimeStamp() = 0;

};









/**
* @brief    ·���б�
* @remark   plidx(<path>, flag, timestamp)
*/
class __declspec(uuid("58AF1B9D-8DDD-4f2c-83BA-337CEDD44605"))
IBKCachePathList: public IUnknown
{
public:

    /** 
    * @brief    �򿪱�׼�Ļ���
    * @param    dwStdCache  Ҫ�򿪵Ļ���id,ȡֵΪ
    *           BKCACHE_STD_EXCLUDE_FILES
    */
    virtual HRESULT STDMETHODCALLTYPE OpenStandard(DWORD dwStdCache) = 0;


    /** 
    * @brief    ���Զ���Ļ���
    * @param    lpCacheFile �����·��,���ΪNULL,��ȡĬ��λ�õĻ���
    */
    virtual HRESULT STDMETHODCALLTYPE OpenCustom(LPCWSTR lpCacheFile = NULL) = 0;


    /** 
    * @brief    ���ҵ�һ����¼
    */
    virtual BOOL    STDMETHODCALLTYPE FindFirstItem() = 0;


    /** 
    * @brief    ������һ����¼
    */
    virtual BOOL    STDMETHODCALLTYPE FindNextItem() = 0;



    /** 
    * @brief    ��ȡ��ǰ��¼��·��
    */
    virtual LPCWSTR STDMETHODCALLTYPE Get_FilePath() = 0;

    /** 
    * @brief    ���ҵ�ǰ��¼�ı�־λ
    */
    virtual DWORD   STDMETHODCALLTYPE Get_Flag() = 0;

    /** 
    * @brief    ���ҵ�ǰ��¼��ʱ���
    */
    virtual ULONGLONG STDMETHODCALLTYPE Get_TimeStamp() = 0;



    /**
    * @brief        ��Ӽ�¼
    * @param[in]    lpszFilePath    �ļ�·��
    */
    virtual HRESULT STDMETHODCALLTYPE Add(
        LPCWSTR     lpszFilePath,
        DWORD       dwFlag = 0,
        ULONGLONG   uTimeStamp = 0) = 0;


    /**
    * @brief        ɾ����¼
    * @param[in]    lpszFilePath    �ļ�·��
    */
    virtual HRESULT STDMETHODCALLTYPE Delete(LPCWSTR lpszFilePath) = 0;




    /// ��������
    virtual HRESULT STDMETHODCALLTYPE BeginTransaction(BKDb::EM_TRANSLOCK transLock = BKDb::em_Deferred) = 0;

    /// �ύ����
    virtual HRESULT STDMETHODCALLTYPE CommitTransaction() = 0;

    /// �ع�����
    virtual HRESULT STDMETHODCALLTYPE RollbackTransaction() = 0;

    /// ��ȡ��ǰʱ��
    virtual ULONGLONG STDMETHODCALLTYPE GetCurrentTimeAsTimeStamp() = 0;
};












NS_SKYLARK_END




#define FN_BKCacheInitialize    "BKCacheInitialize"     ///< export BKCacheInitialize
#define FN_BKCacheCreateObject  "BKCacheCreateObject"   ///< export BKCacheCreateObject


/// ��ʼ��bkcacheģ��,���Զ�ε���
EXTERN_C HRESULT WINAPI BKCacheInitialize();
/// typedef for BKCacheCreateObject
typedef HRESULT (WINAPI *PFN_BKCacheInitialize)();


/**
* @brief    ����BKCache��ģ��
* @param    dwBKEngVer      BKEng�İ汾��,Ĭ��ʹ��BKENG_CURRENT_VERSION,����0��ʾ�����汾���
* @param    riid            Ҫ�����Ķ����iid
* @param    ppvObj          ���ش����Ķ���
*/
EXTERN_C HRESULT WINAPI BKCacheCreateObject(REFIID riid, void** ppvObj, DWORD dwBKEngVer = BKENG_CURRENT_VERSION);
/// typedef for BKCacheCreateObject
typedef HRESULT (WINAPI *PFN_BKCacheCreateObject)(REFIID riid, void** ppvObj, DWORD dwBKEngVer);



#endif//BKCACHE_H