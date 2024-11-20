/**
* @file    bkbak.h
* @brief   ...
* @author  bbcallen
* @date    2010-01-05 21:21
*/

#ifndef BKBAK_H
#define BKBAK_H

#include <unknwn.h>
#include "bkbakdef.h"

NS_SKYLARK_BEGIN





/** 
* @brief    �����ļ���ѯ�ӿ�
*/
class __declspec(uuid("C49884D9-EC30-4916-9B0D-7293FB6CA4D5"))
IBKFileBackupFinder: public IUnknown
{
public:

    /** 
    * @brief        ���ұ���Ŀ¼�ĵ�һ���ļ�
    * @param[out]   pBackupID       ���ر����ļ���ʶ
    * @param[out]   pFindData       �����ΪNULL,�᷵�ر����ļ�ѹ�������Ϣ
    * @param[out]   pbstrOrigPath   ����ԭʼ·��
    */
    virtual BOOL STDMETHODCALLTYPE FindFirstBackupFile(
        BKBAK_BACKUP_ID*            pBackupID,
        BKBAK_BACKUP_SHORT_INFO*    pBackupData     = NULL,
        BSTR*                       pbstrOrigPath = NULL) = 0;

    /** 
    * @brief        ���ұ���Ŀ¼����һ���ļ�
    * @param[out]   pBackupID       ���ر����ļ���ʶ
    * @param[out]   pFindData       �����ΪNULL,�᷵�ر����ļ�ѹ�������Ϣ
    * @param[out]   pbstrOrigPath   ����ԭʼ·��
    */
    virtual BOOL STDMETHODCALLTYPE FindNextBackupFile(
        BKBAK_BACKUP_ID*            pBackupID,
        BKBAK_BACKUP_SHORT_INFO*    pBackupData     = NULL,
        BSTR*                       pbstrOrigPath = NULL) = 0;

    /** 
    * @brief        ���ݱ����ļ���ʶ��ȡ��ϸ
    * @param[in]    byBackupID      �����ļ���ʶ
    * @param[out]   pBackupData     ���ر�����Ϣ
    * @param[out]   pbstrOrigPath   ����ԭʼ·��
    */
    virtual HRESULT STDMETHODCALLTYPE GetBackupInfo(
        const BKBAK_BACKUP_ID*  pBackupID,
        BKBAK_BACKUP_INFO*      pBackupData,
        BSTR*                   pbstrOrigPath) = 0;

    /** 
    * @brief        ���ݱ����ļ���ʶ��ȡ�϶̵���Ϣ
    * @param[in]    byBackupID      �����ļ���ʶ
    * @param[out]   pBackupData     ���ر�����Ϣ
    * @param[out]   pbstrOrigPath   ����ԭʼ·��
    * @remark       �õ��ñ� GetBackupInfo ����
    */
    virtual HRESULT STDMETHODCALLTYPE GetBackupShortInfo(
        const BKBAK_BACKUP_ID*      pBackupID,
        BKBAK_BACKUP_SHORT_INFO*    pBackupData,
        BSTR*                       pbstrOrigPath) = 0;
};



// �ϴ��ӿڵ�ǰ������
class   IBKEngUploader;
class   IBKProgress;
struct  BKENG_UPLOAD_PARAM;


/** 
* @brief    �����ļ��ӿ�
*/
class __declspec(uuid("0D3FFB09-C94F-4d58-8D7D-C50D679F2382"))
IBKFileBackup: public IUnknown
{
public:

    /** 
    * @brief        ���ұ���Ŀ¼�ĵ�һ���ļ�
    * @param[in]    lpszBackupFile  Ҫ���ݵ��ļ�
    * @param[in]    pBackupParam    ���ݲ���
    * @param[out]   pBackupID       �����ΪNULL,�᷵�����ɵı��ݱ�ʾ
    * @param[out]   pBackupInfo     �����ΪNULL,�᷵�����ɵı�����Ϣ
    */
    virtual HRESULT STDMETHODCALLTYPE BackupFile(
        LPCWSTR                     lpszBackupFile,
        const BKBAK_BACKUP_PARAM*   pBackupParam,
        BKBAK_BACKUP_ID*            pBackupID,
        BKBAK_BACKUP_INFO*          pBackupInfo = NULL) = 0;

    /** 
    * @brief        �ָ�ָ�����ļ�
    * @param[in]    pBackupID           Ҫ�ָ����ļ���ʾ
    * @param[in]    bOverwrite          ����ָ���λ�����ļ�,�Ƿ񸲸�֮
    * @param[in]    lpszNewDirectory    �ָ�Ŀ¼,���ΪNULL��ָ���ԭʼĿ¼
    * @param[in]    lpszNewFileName     �ָ��ļ���,���ΪNULL��ָ�Ϊԭʼ�ļ���
    *
    * @retval       E_SKYLARK_RETRIEVE_FAILED_TO_OVERWRITE_DIRECTORY        �޷���ԭ�ļ�(ָ���Ļָ�λ����һ��Ŀ¼)
    * @retval       E_SKYLARK_RETRIEVE_FAILED_TO_OVERWRITE_FILE             �޷���ԭ�ļ�(ָ���Ļָ�λ�ô���һ���ļ�)
    * @retval       E_SKYLARK_RETRIEVE_MISSING_BACKUP_FILE                  �������ݲ�����
    * @retval       E_SKYLARK_RETRIEVE_FAILED_TO_EXTRACT_FILE               ��ѹ�ļ���ʱ��������
    * @retval       E_SKYLARK_RETRIEVE_FAILED_TO_EXTRACT_BACKUP_INFO        ��ȡ�����ļ���Ϣ��ʱ��������
    * @retval       E_SKYLARK_RETRIEVE_FAILED_TO_REPLACE_FILE               �滻�ļ���ʱ��������
    */
    virtual HRESULT STDMETHODCALLTYPE RetrieveFile(
        const BKBAK_BACKUP_ID*  pBackupID,
        BOOL                    bOverwrite,
        LPCWSTR                 lpszNewDirectory = NULL,
        LPCWSTR                 lpszNewFileName  = NULL) = 0;

    /** 
    * @brief        �Ƴ�ָ�����ļ�
    * @param[in]    pBackupID           Ҫ�Ƴ����ļ���ʾ
    */
    virtual HRESULT STDMETHODCALLTYPE RemoveBackupFile(
        const BKBAK_BACKUP_ID*  pBackupID) = 0;

    /** 
    * @brief        �Ƴ����б����ļ�
    */
    virtual HRESULT STDMETHODCALLTYPE RemoveAllBackupFiles() = 0;

    /** 
    * @brief        �Ƴ����ڵı����ļ�
    */
    virtual HRESULT STDMETHODCALLTYPE RemoveExpiredBackupFiles() = 0;

    
    /** 
    * @brief        �ϴ�ָ�����ļ�
    * @param[in]    pBackupID           Ҫ�ָ����ļ���ʾ
    * @param[in]    piUploader          �ϴ����
    * @param[in]    pUploadParam        �ϴ�����,�ᱻ���ݸ�uploader,ֻ��Ҫ��дuUploadChannel��uUploadAct
    * @param[in]    piUploader          �ϴ��ص�                              
    */
    virtual HRESULT STDMETHODCALLTYPE UploadBackupFile(
        const BKBAK_BACKUP_ID*      pBackupID,
        IBKEngUploader*             piUploader,
        const BKENG_UPLOAD_PARAM*   pUploadParam,
        IBKProgress*                piCallback) = 0;
};









/// zip��ѹ���ӿ�
class __declspec(uuid("F6188AE6-ED50-4d82-A551-B7F5FFDCD8E3"))
IBKZip: public IUnknown
{
public:
    /**
    * @brief    ����zip�ļ�
    * @param    lpZipFileName   zip�ļ�·��
    * @param    lpszPassword    ѹ������
    * @param    lpszComment     ѹ������ע��(Լ��ΪUTF-8����)
    * @note     ԭ��λ�õ��ļ��ᱻ���
    */
    virtual HRESULT STDMETHODCALLTYPE CreateZipToFile(
        LPCWSTR lpZipFileName,
        LPCSTR  lpszPassword,
        LPCSTR  lpszComment) = 0;

    /**
    * @brief    ����zip�ļ�
    * @param    hFile           zip�ļ����
    * @param    lpszPassword    ѹ������
    * @param    lpszComment     ѹ������ע��(Լ��ΪUTF-8����)
    * @note     ԭ��λ�õ��ļ��ᱻ���
    */
    virtual HRESULT STDMETHODCALLTYPE CreateZipToHandle(
        HANDLE  hFile,
        LPCSTR  lpszPassword,
        LPCSTR  lpszComment) = 0;

    /**
    * @brief    ��zip�����һ���ļ�
    * @param    lpFileName      ����ӵ��ļ�
    * @param    lpDisplayName   �ļ���zip���е���ʾ��
    * @param    piCallback      �ص��ӿ�
    */
    virtual HRESULT STDMETHODCALLTYPE AddFile(
        LPCWSTR         lpFileName,
        LPCWSTR         lpDisplayName,
        IBKProgress*    piCallback = NULL) = 0;

    /**
    * @brief    ��zip�����һ������������
    * @param    pbyData         Ҫ��ӵĶ��������ݻ�����
    * @param    dwBytes         ���ݳ���
    * @param    lpDisplayName   �ļ���zip���е���ʾ��
    * @param    piCallback      �ص��ӿ�
    */
    virtual HRESULT STDMETHODCALLTYPE AddData(
        const BYTE*     pbyData,
        DWORD           dwBytes,
        LPCWSTR         lpDisplayName,
        IBKProgress*    piCallback = NULL) = 0;

    /**
    * @brief    ��zip�����һ���ļ�
    * @param    hFile           ����ӵ��ļ����
    * @param    lpDisplayName   �ļ���zip���е���ʾ��
    * @param    piCallback      �ص��ӿ�
    */
    virtual HRESULT STDMETHODCALLTYPE AddFileHandle(
        HANDLE          hFile,
        LPCWSTR         lpDisplayName,
        IBKProgress*    piCallback = NULL) = 0;
};


/// zip�Ľ�ѹ�ӿ�
class __declspec(uuid("B56C6BE9-3BAE-480d-9794-A2E5553DFBE7"))
IBKUnzip: public IUnknown
{
public:
    /**
    * @brief    ��zip�ļ����ڽ�ѹ
    * @param    lpZipFileName   zip�ļ�·��
    * @param    lpszPassword    ѹ������
    */
    virtual HRESULT STDMETHODCALLTYPE OpenZipFromFile(
        LPCWSTR lpZipFileName,
        LPCSTR  lpszPassword) = 0;

    /**
    * @brief    ��zip�ļ����ڽ�ѹ
    * @param    hFile           zip�ļ����
    * @param    lpszPassword    ѹ������
    */
    virtual HRESULT STDMETHODCALLTYPE OpenZipFromHandle(
        HANDLE  hFile,
        LPCSTR  lpszPassword) = 0;

    /**
    * @brief    ��ȡѹ������ע��
    * @param    lpBuf           ����ע�͵Ļ�����(Լ��ΪUTF-8����)
    * @param    dwLen           �������ĳ���(�ַ���)
    * @param    pdwRealLen      ����ע�͵�ʵ�ʳ���
    */
    virtual HRESULT STDMETHODCALLTYPE GetGlobalComment(
        LPSTR   lpBuf,
        DWORD   dwLen,
        DWORD*  pdwRealLen) = 0;


    /**
    * @brief    ����ѹ�����е��ļ�
    * @param    lpFileNameInZip Ҫ���ҵ��ļ���ѹ�����е�����,���ΪNULL,�򷵻ص�һ���ļ�
    */
    virtual BOOL    STDMETHODCALLTYPE FindFirstFileInZip(LPCWSTR lpFileNameInZip = NULL) = 0;

    /**
    * @brief    ����ѹ��������һ���ļ�
    * @note     ��� FindFirstFileInZip ָ�����ļ���,��ô������������ǰ�ļ�����һ���ļ�
    */
    virtual BOOL    STDMETHODCALLTYPE FindNextFileInZip() = 0;

    /**
    * @brief    ѹ������û�и�����ļ�
    */
    virtual BOOL    STDMETHODCALLTYPE IsEndOfFindInZip() = 0;

    /**
    * @brief    ��ȡѹ�����ڵĵ�ǰ�ļ����ļ���
    * @param    pbstrFileNameInZip  �����ļ���
    */
    virtual HRESULT STDMETHODCALLTYPE GetFileNameInZip(BSTR* pbstrFileNameInZip) = 0;

    /**
    * @brief    ��ȡѹ�����ڵĵ�ǰ�ļ��Ĵ�С(ѹ��ǰ)
    * @param    pullSize    �����ļ���С
    */
    virtual HRESULT STDMETHODCALLTYPE GetFileSize(ULONGLONG* pullSize) = 0;

    /**
    * @brief    ��ѹ�����ڵĵ�ǰ�ļ���ѹ��ָ��λ��
    * @param    lpTargetPath        ��ѹ�ļ������·��,���ΪNULL,��ʹ�õ�ǰĿ¼,�ļ���ʹ��ѹ�����е�����
    * @param    piCallback          �ص��ӿ�
    * @param    bOverwrite          �Ƿ񸲸�ԭ��λ�����е��ļ�
    */
    virtual HRESULT STDMETHODCALLTYPE ExtractToPath(
        LPCWSTR         lpTargetPath        = NULL,
        IBKProgress*    piCallback          = NULL,
        BOOL            bOverwrite          = TRUE) = 0;


    /**
    * @brief    ��ѹ�����ڵĵ�ǰ�ļ���ѹ��ָ��λ��
    * @param    lpTargetDir         ��ѹ�ļ������Ŀ¼,���ΪNULL,��ʹ�õ�ǰĿ¼
    * @param    lpTargetFileName    ��ѹ�ļ�������ļ���,���ΪNULL,��ʹ��ѹ�����е�����
    * @param    piCallback          �ص��ӿ�
    * @param    bOverwrite          �Ƿ񸲸�ԭ��λ�����е��ļ�
    */
    virtual HRESULT STDMETHODCALLTYPE ExtractToDirectory(
        LPCWSTR         lpTargetDir         = NULL,
        LPCWSTR         lpTargetFileName    = NULL,
        IBKProgress*    piCallback          = NULL,
        BOOL            bOverwrite          = TRUE) = 0;

    /**
    * @brief    ��ѹ�����ڵĵ�ǰ�ļ���ѹ��ָ�����
    * @param    hFileHandle         ��ѹ�ļ���������
    * @param    piCallback          �ص��ӿ�
    */
    virtual HRESULT STDMETHODCALLTYPE ExtractToHandle(
        HANDLE          hFileHandle,
        IBKProgress*    piCallback = NULL) = 0;

    /**
    * @brief    ��ѹ�����ڵĵ�ǰ�ļ���ѹ��ָ���ڴ�λ��
    * @param    pBuffer             ��ѹ�ļ��Ļ�����
    * @param    dwBufferSize        ��������С
    * @param    piCallback          �ص��ӿ�
    * @retval   S_OK                �Ѿ���ѹ���
    * @retval   S_FALSE             ���и�������
    */
    virtual HRESULT STDMETHODCALLTYPE ExtractToBuffer(
        BYTE*           pBuffer,
        DWORD           dwBufferSize,
        IBKProgress*    piCallback = NULL) = 0;
};

NS_SKYLARK_END


#define FN_BKBakCreateObject    "BKBakCreateObject"     ///< export BKBakCreateObject


/**
* @brief    ����BKBak��ģ��
* @param    dwBKEngVer      BKEng�İ汾��,Ĭ��ʹ��BKENG_CURRENT_VERSION,����0��ʾ�����汾���
* @param    riid            Ҫ�����Ķ����iid
* @param    ppvObj          ���ش����Ķ���
*/
EXTERN_C HRESULT WINAPI BKBakCreateObject(REFIID riid, void** ppvObj, DWORD dwBKEngVer = BKENG_CURRENT_VERSION);
/// typedef for BKBakCreateObject
typedef HRESULT (WINAPI *PFN_BKBakCreateObject)(REFIID riid, void** ppvObj, DWORD dwBKEngVer);




#endif//BKBAK_H