/**
* @file    bkeng.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-09 21:42
*/

#ifndef BKENG_H
#define BKENG_H

#include <unknwn.h>
#include "skylarkbase.h"
#include "bkengdef.h"
#include "bklevel.h"

NS_SKYLARK_BEGIN

/**
* @brief ɨ��������ýӿ�
*/
class __declspec(uuid("7F70ECF3-22FB-4c55-B6EC-1C8C0B2EFCDA"))
IBKEngineCallback
{
public:

    /**
    * @brief        ɨ���ļ�ǰ����
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE BeforeScanFile(
        LPCWSTR             lpszFilePath,
        void*               pvFlag) = 0;


    /**
    * @brief        ɨ���ļ������
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pResult         ��ǰ�ļ���ɨ����
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE AfterScanFile(
        LPCWSTR             lpszFilePath,
        const BKENG_RESULT* pResult,
        void*               pvFlag) = 0;


    /**
    * @brief        ����ļ�ǰ���� (�����Զ����ʱ,������ô˻ص�)
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pResult         ��ǰ�ļ���ɨ����
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE BeforeCleanFile(
        LPCWSTR             lpszFilePath,
        const BKENG_RESULT* pResult,
        void*               pvFlag) = 0;


    /**
    * @brief        ����ļ������ (�����Զ����ʱ,������ô˻ص�)
    * @param[in]    lpszFilePath    ԭʼ�ļ�·��
    * @param[in]    pResult         ��ǰ�ļ���������
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */
    virtual HRESULT STDMETHODCALLTYPE AfterCleanFile(
        LPCWSTR             lpszFilePath,
        const BKENG_RESULT* pResult,
        void*               pvFlag) = 0;


    /**
    * @brief        ɨ������з���ϸ�� (�����Ϣ,ѹ�����еĲ�����...)
    * @param[in]    lpszVirtualPath ɨ����������·��
    * @param[in]    pResult         ɨ������ɨ����
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */ 
    virtual HRESULT STDMETHODCALLTYPE OnScanDetail(
        LPCWSTR             lpszVirtualPath,
        const BKENG_RESULT* pResult,
        void*               pvFlag) = 0;


    /**
    * @brief        ����ʱ��Ļص�
    * @param[in]    lpszFilePath    ��ǰ����ɨ����ļ� (�����ǰû������ɨ����ļ�,�������ΪNULL)
    * @param[in]    pvFlag          �ύ�ļ�ʱ����Ļص�����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */ 
    virtual HRESULT STDMETHODCALLTYPE OnIdle() = 0;



    /**
    * @brief        ����ʱ�ص�
    * @param[in]    hrFinishCode    ɨ�践�صĴ�����
    */ 
    virtual HRESULT STDMETHODCALLTYPE OnFinish(
        HRESULT             hrFinishCode) = 0;
};







/**
* @brief ɨ��������ýӿ�
*/
class __declspec(uuid("479D062C-5D89-4694-9818-3BA5BFECEBCB"))
IBKEngine: public IUnknown
{
public:

    /**
    * @brief        ��ʼ��ɨ������
    * @param[in]    pvReserved      ��������
    */
    virtual HRESULT STDMETHODCALLTYPE Initialize(void* pvReserved = NULL) = 0;


    /**
    * @brief        ����ʼ��ɨ������
    * @remark       ���ȷ���� Scan ���غ�ŵ��÷���ʼ��
    */
    virtual HRESULT STDMETHODCALLTYPE Uninitialize() = 0;


    /**
    * @brief        ��ȡɨ������
    * @param[out]   pSettings   ���淵�ص�ɨ������
    */
    virtual HRESULT STDMETHODCALLTYPE GetScanSettings(BKENG_SETTINGS* pSettings) = 0;


    /**
    * @brief        �޸�ɨ������
    * @param[in]    pSettings   ɨ������,���ΪNULL,��Ӧ��Ĭ������
    * @remark       ��ɨ��������޸����ý�����δ�������Ϊ
    */
    virtual HRESULT STDMETHODCALLTYPE SetScanSettings(const BKENG_SETTINGS* pSettings) = 0;



    /**
    * @brief        ��ɨ��״̬��λ,�Ա������һ�ε�ɨ��
    * @remark       ��ͬһ����ʵ��������Scan֮��,��ص���һ��Reset
    */
    virtual HRESULT STDMETHODCALLTYPE Reset() = 0;



    /**
    * @brief        ��һ���ļ���ӵ�ɨ�����
    * @param[in]    pszFileFullName �ļ�������·��
    * @param[in]    pFindData       ö���ļ�ʱ��Ľṹ��,�����ΪNULL,���Լ���ɨ���ٶ�
    * @param[in]    pvFlag          �����߶���İ󶨲���,�ص�ʱԭ������
    * @param[in]    dwHighWaterMark ��ˮλ��,���ȴ�ɨ����ļ����� dwHighWaterMark ʱ,������,ֱ���ļ������� dwHighWaterMark,���Ϊ0,������
    * @remark       �������̫��,�ᵼ�µ�������
    * @retval       S_OK            �ļ����ύ
    * @retval       E_ABORT         �ļ�δ�ύ(��ʱ���ж�)
    */
    virtual HRESULT STDMETHODCALLTYPE AppendFile(
        LPCWSTR                 pszFileFullName,
        const WIN32_FIND_DATAW* pFindData,
        void*                   pvFlag          = NULL,
        DWORD                   dwHighWaterMark = 5000) = 0;



    /**
    * @brief        ��һ��hash��ӵ�ɨ�����
    * @param[in]    pHashScanParam  hashɨ�����
    * @param[in]    pFindData       ö���ļ�ʱ��Ľṹ��,�����ΪNULL,���Լ���ɨ���ٶ�
    * @param[in]    pvFlag          �����߶���İ󶨲���,�ص�ʱԭ������
    * @param[in]    dwHighWaterMark ��ˮλ��,���ȴ�ɨ����ļ����� dwHighWaterMark ʱ,������,ֱ���ļ������� dwHighWaterMark,���Ϊ0,������
    * @remark       �������̫��,�ᵼ�µ�������
    * @retval       S_OK            �ļ����ύ
    * @retval       E_ABORT         �ļ�δ�ύ(��ʱ���ж�)
    */
    virtual HRESULT STDMETHODCALLTYPE AppendHash(
        const BKENG_HASH_SCAN_PARAM*    pHashScanParam,
        void*                           pvFlag          = NULL,
        DWORD                           dwHighWaterMark = 5000) = 0;



    /**
    * @brief        �ύ����
    * @remark       ��ʾ�Ѿ���������ļ����ύ,δ�������߲�ѯ���ļ�����������ѯ
    */
    virtual HRESULT STDMETHODCALLTYPE Commit() = 0;



    /**
    * @brief        ��ʼ�첽ɨ��
    * @param[in]    piCallback      �ص��ӿ�
    * @remark       �õ���Ϊ����������,����ȷ��ɨ���ڼ�,piCallbackʼ����Ч��
    *               ���ǰһ��ɨ��û�н����͵���AsyncScan,�ᵼ��δ�������Ϊ
    */
    virtual HRESULT STDMETHODCALLTYPE AsyncScan(IBKEngineCallback* piCallback) = 0;



    /**
    * @brief        �ж�һ��ɨ������
    * @remark       �õ���Ϊ����������,�ᴥ�� Scan �������� E_ABORT,
    *               ɨ��ȷʵ�˳���,�����piCallback->OnFinish()��
    *               ������洦����ͣ��,�õ��ûᵼ������
    */
    virtual HRESULT STDMETHODCALLTYPE NotifyStop() = 0;



    /**
    * @brief        �ȴ�ɨ����������ж϶��˳�
    * @param[in]    dwWaitTime  �ȴ�ʱ��,��Ϊ0������������ɨ���Ƿ����
    * @return       ����ֵͬ WaitForSingleObject
    */
    virtual DWORD   STDMETHODCALLTYPE WaitForFinish(DWORD dwWaitTime) = 0;



    /**
    * @brief        ��ͣһ��ɨ������
    * @remark       �õ���Ϊȷ��ɨ����ͣ,�ص����ٷ����µĽ��ʱ�ŷ���
    */
    virtual HRESULT STDMETHODCALLTYPE Pause() = 0;



    /**
    * @brief        �ָ�һ��ɨ������
    */
    virtual HRESULT STDMETHODCALLTYPE Resume() = 0;


    //////////////////////////////////////////////////////////////////////////
    // IBKEngine_v4 new interfaces


    /**
    * @brief        ��һ���ļ���ӵ�ɨ�����
    * @param[in]    pszFileFullName �ļ�������·��
    * @param[in]    pScanParam      ɨ�����,����ΪNULL
    * @remark       �������̫��,�ᵼ�µ�������
    * @retval       S_OK            �ļ����ύ
    * @retval       E_ABORT         �ļ�δ�ύ(��ʱ���ж�)
    */
    virtual HRESULT STDMETHODCALLTYPE AppendFileEx(
        LPCWSTR             pszFileFullName,
        BKENG_SCAN_PARAM*   pScanParam) = 0;

    /**
    * @brief        ǿ��ɨ��������ݴ���ļ�
    */
    virtual HRESULT STDMETHODCALLTYPE Flush() = 0;
};








/**
* @brief    �򻯵�ɨ��������ýӿ�,����Ҫʵ�ֻص�
* @remark   �ýӿڲ�ʹ�ûص�,��ȷ�����õļ�,����������ѯ��ʱ���ǳ���
*/
class __declspec(uuid("5112296D-AA01-4dc6-8744-EADABF858D1D"))
IBKEngineLite: public IUnknown
{
public:

    /**
    * @brief        ��ʼ��ɨ������
    * @param[in]    pvReserved      ��������
    */
    virtual HRESULT STDMETHODCALLTYPE Initialize(void* pvReserved = NULL) = 0;


    /**
    * @brief        ����ʼ��ɨ������
    * @remark       ���ȷ���� Scan ���غ�ŵ��÷���ʼ��
    */
    virtual HRESULT STDMETHODCALLTYPE Uninitialize() = 0;


    /**
    * @brief        ��ȡɨ������
    * @param[out]   pSettings   ���淵�ص�ɨ������
    */
    virtual HRESULT STDMETHODCALLTYPE GetScanSettings(BKENG_SETTINGS* pSettings) = 0;


    /**
    * @brief        �޸�ɨ������
    * @param[in]    pSettings   ɨ������,���ΪNULL,��Ӧ��Ĭ������
    * @remark       ��ɨ��������޸����ý�����δ�������Ϊ
    */
    virtual HRESULT STDMETHODCALLTYPE SetScanSettings(const BKENG_SETTINGS* pSettings) = 0;


    /**
    * @brief        ɨ���ļ�
    * @param[in]    lpszFilePath    �ļ�·��
    * @param[in]    dwScanMask      ɨ������,ȡֵΪBKENG_SCAN_MASK_xxx�����
    * @param[out]   pScanResult     �ļ�ɨ����
    * @param[in]    piCallback      �ļ�ɨ����,����ΪNULL(ͨ���������ǰ��ĳЩ����)
    * @param[in]    pvReserved      ��������,δʹ��
    * @remark       �����������ʧ��,��ôpScanResult�е����ݽ�������
    */ 
    virtual HRESULT STDMETHODCALLTYPE Scan(
        LPCWSTR             lpszFilePath,
        DWORD               dwScanMask,
        BKENG_RESULT*       pScanResult,
        IBKEngineCallback*  piCallback = NULL,
        void*               pvReserved = NULL) = 0;


    /**
    * @brief        ɨ��hash
    * @param[in]    pHashScanParam  hashɨ�����
    * @param[out]   pScanResult     �ļ�ɨ����
    * @param[in]    piCallback      �ļ�ɨ����,����ΪNULL(ͨ���������ǰ��ĳЩ����)
    * @param[in]    pvReserved      ��������,δʹ��
    * @remark       �����������ʧ��,��ôpScanResult�е����ݽ�������
    */ 
    virtual HRESULT STDMETHODCALLTYPE ScanHash(
        const BKENG_HASH_SCAN_PARAM*    pHashScanParam,
        BKENG_RESULT*                   pScanResult,
        IBKEngineCallback*              piCallback = NULL,
        void*                           pvReserved = NULL) = 0;


    /**
    * @brief        ����ɨ��������ļ�
    * @param[in]    lpszFilePath    �ļ�·��
    * @param[in]    dwScanMask      ɨ������,ȡֵΪBKENG_SCAN_MASK_xxx�����
    * @param[in]    pScanResult     �ļ��ϴ�ɨ����
    * @param[out]   pCleanResult    �ļ�������
    * @param[in]    piCallback      �ļ�ɨ����,����ΪNULL(ͨ���������ǰ��ĳЩ����)
    * @param[in]    pvReserved      ��������,δʹ��
    * @remark       �����������ʧ��,��ôpScanResult�е����ݽ�������
    */ 
    virtual HRESULT STDMETHODCALLTYPE HintClean(
        LPCWSTR             lpszFilePath,
        DWORD               dwScanMask,
        const BKENG_RESULT* pScanResult,
        BKENG_RESULT*       pCleanResult,
        IBKEngineCallback*  piCallback = NULL,
        void*               pvReserved = NULL) = 0;


    /**
    * @brief        �ж����ڽ��е�ɨ��
    */
    virtual HRESULT STDMETHODCALLTYPE Interrupt() = 0;
};








/**
* @brief    �ϴ��ӿ�
*/
class __declspec(uuid("38E7A42B-9F47-4774-85E5-20892039B922"))
IBKEngUploader: public IUnknown
{
public:

    /**
    * @brief        ��ʼ��ɨ������
    * @param[in]    pvReserved      ��������
    */
    virtual HRESULT STDMETHODCALLTYPE Initialize(void* pvReserved = NULL) = 0;


    /**
    * @brief        ����ʼ��ɨ������
    */
    virtual HRESULT STDMETHODCALLTYPE Uninitialize() = 0;


    /**
    * @brief        ɨ���ļ�
    * @param[in]    lpszFilePath    �ļ�·��
    * @param[in]    piCallback      �ϴ��ص�
    * @param[in]    pUploadParam    �ϴ�����
    */ 
    virtual HRESULT STDMETHODCALLTYPE Upload(
        LPCWSTR             lpszFilePath,
        IBKProgress*        piCallback,
        BKENG_UPLOAD_PARAM* pUploadParam) = 0;


    /**
    * @brief        �ж�һ��ɨ������
    * @remark       �õ���Ϊ����������,�ᴥ�� Upload ��������ʧ��
    */
    virtual HRESULT STDMETHODCALLTYPE NotifyStop() = 0;
};






/**
* @brief    ����Э��
*/
class __declspec(uuid("9FC31DD2-F1EF-4964-A34A-C52B0F79C488"))
IBKEngineEcho: public IUnknown
{
public:

    /**
    * @brief        ��ʼ�����ֶ���
    * @param[in]    pvReserved      ��������
    */
    virtual HRESULT STDMETHODCALLTYPE Initialize(void* pvReserved = NULL) = 0;


    /**
    * @brief        ����ʼ�����ֶ���
    */
    virtual HRESULT STDMETHODCALLTYPE Uninitialize() = 0;


    /**
    * @brief        ����ļ�
    * @param[in]    lpszFilePath    Ҫ�����ļ�·��
    * @param[in]    pvFlag          �����߶���İ󶨲���
    */ 
    virtual HRESULT STDMETHODCALLTYPE AppendFile(
        LPCWSTR lpszFilePath,
        void*   pvToken) = 0;


    /**
    * @brief        ����ļ�
    * @param[out]   pEchoResult     �������ֽ��
    */ 
    virtual HRESULT STDMETHODCALLTYPE Echo(
        BKENG_ECHO_RESULT*  pEchoResult) = 0;


    /**
    * @brief        ��ȡ�ļ������
    * @param[in]    pvToken         ��ʶҪ��ȡ���ļ����
    * @param[out]   pFileResult     �������ֽ��
    */ 
    virtual HRESULT STDMETHODCALLTYPE GetEchoResult(
        void*           pvToken,
        BKENG_RESULT*   pFileResult) = 0;


    /**
    * @brief        �ж����ڽ��е�ɨ��
    */
    virtual HRESULT STDMETHODCALLTYPE Interrupt() = 0;


    /**
    * @brief        ��ȡ��������
    * @param[out]   pSettings   ���淵�ص���������
    */
    virtual HRESULT STDMETHODCALLTYPE GetEchoSettings(BKENG_ECHO_SETTINGS* pSettings) = 0;


    /**
    * @brief        �޸���������
    * @param[in]    pSettings   ��������,���ΪNULL,��Ӧ��Ĭ������
    * @remark       �����ֹ������޸����ý�����δ�������Ϊ
    */
    virtual HRESULT STDMETHODCALLTYPE SetEchoSettings(const BKENG_ECHO_SETTINGS* pSettings) = 0;
};




/// ��ȡ�ڲ�����õĽӿ�
class __declspec(uuid("44D6DC32-B247-4496-8CF8-C611A2D9B3A9"))
IBKEngineInternal: public IUnknown
{
public:

    
    /**
    * @brief        ��ȡ�ڲ�����ӿ�
    * @param[id]    riid    �ӿ�iid
    * @param[out]   ppvObj  ���ؽӿ�ָ��
    */
    virtual HRESULT STDMETHODCALLTYPE QueryInternalComponent(REFIID riid, void** ppvObj) = 0;
};





/// �ļ�������߽ӿ�
class __declspec(uuid("550A1550-366D-42f8-8347-BCB9F382A641"))
IBKEngFileToolkit: public IUnknown
{
public:

    /**
    * @brief        ɾ���ļ�
    * @param[in]    lpszFilePath    �ļ�·��
    * @retval       S_OK                            ɨ��ɹ�
    * @retval       S_BKE_DELETE_FILE_NEED_REBOOT   ��Ҫ����
    */ 
    virtual HRESULT STDMETHODCALLTYPE DeleteFile(LPCWSTR lpszFilePath) = 0;


    /**
    * @brief        �滻�ļ�
    * @param[in]    lpszDstFile     �滻��Ŀ���ļ�
    * @param[in]    lpszSrcFile     �滻��Դ�ļ�
    * @param[in]    bKeepSrcFile    ����Դ�ļ�
    * @retval       S_OK                            ɨ��ɹ�
    * @retval       S_BKE_REPLACE_FILE_NEED_REBOOT  ��Ҫ����
    */ 
    virtual HRESULT STDMETHODCALLTYPE ReplaceFile(
        LPCWSTR lpszDstFile,
        LPCWSTR lpszSrcFile,
        BOOL    bKeepSrcFile = FALSE) = 0;


    /**
    * @brief        ǿ������ɾ���ļ�
    * @param[in]    lpszFilePath    �ļ�·��
    * @retval       S_OK                            ɨ��ɹ�
    * @retval       S_BKE_DELETE_FILE_NEED_REBOOT   ��Ҫ����
    */ 
    virtual HRESULT STDMETHODCALLTYPE ForceBootDeleteFile(LPCWSTR lpszFilePath) = 0;
};





/// �ļ����������
class __declspec(uuid("4105C1FF-F8E2-4d2c-8801-4332600A5730"))
IBKEngAveController: public IUnknown
{
public:

    /**
    * @brief        ���ڴ氲װ�ļ�����
    * @param[in]    pAveLoad        ���ز���
    * @remark       �´���������ʵ��,����ʹ���ļ�����.
    *               �Ѿ�����������ʵ����Ȼʹ���ϵ�����.
    *               �õ��ò����Զ����ز�����.
    */ 
    virtual HRESULT STDMETHODCALLTYPE LoadAvEngine(BKENG_AVE_LOAD* pAveLoad) = 0;


    /**
    * @brief        ���ڴ�ж���ļ�����
    * @param[in]    pvReserved      ��������
    * @remark       �´������������,����ʹ���ļ�����.
    *               �Ѿ�����������ʵ����Ȼʹ���ϵ�����.
    *               �˳�ʱ,�����߲���Ҫ�ֶ�ж������
    */
    virtual HRESULT STDMETHODCALLTYPE UnloadAvEngine() = 0;


    /**
    * @brief        ���س�פ������,���صĲ�����᳤��פ���ڴ�
    * @param[in]    pvReserved      ��������
    * @remark       �����פ�������Ѿ�����,���ﲻ�����κ�����
    */ 
    virtual HRESULT STDMETHODCALLTYPE LoadDaemonSign() = 0;


    /**
    * @brief        ж�س�פ������
    * @param[in]    pvReserved      ��������
    * @remark       �����פ������û�м���,���ﲻ�����κ�����
    *               �˳�ʱ,�����߲���Ҫ�ֶ�ж�ز�����
    */ 
    virtual HRESULT STDMETHODCALLTYPE UnloadDaemonSign() = 0;


    /**
    * @brief        ֪ͨ��������ʵ�����²�����
    * @param[in]    pvReserved      ��������
    * @remark       ������¼��ز������ʱ��, ����������ɨ��, ������ʹ�õĲ����ⲻ�ᱻ�����滻, ���ǵȵ�ɨ�����ʱ�滻
    */ 
    virtual HRESULT STDMETHODCALLTYPE ReloadSign() = 0;


    /**
    * @brief        ��ȡ�Ѽ��صĳ�פ������汾��
    * @param[in]    pSignVersion        ������汾�Ľṹ��
    * @remark       ��Ҫ�������Ѽ���
    */ 
    virtual HRESULT STDMETHODCALLTYPE GetDaemonSignVersion(
        BKAVE_SIGN_VERSION* pSignVersion) = 0;


    /**
    * @brief        ��ȡ���ز�����汾��
    * @param[in]    lpszSignIniPath     signs.ini��·��,���ΪNULL,���ȫ�����û�ȡ
    * @param[in]    pSignVersion        ������汾�Ľṹ��
    * @remark       ����Ҫ�������Ѽ���
    */ 
    virtual HRESULT STDMETHODCALLTYPE GetLocalSignVersion(
        LPCWSTR             lpszSignIniPath,
        BKAVE_SIGN_VERSION* pSignVersion) = 0;
};






NS_SKYLARK_END




#define FN_BKEngInitialize              "BKEngInitialize"
#define FN_BKEngUninitialize            "BKEngUninitialize"
#define FN_BKEngCreateObject			"BKEngCreateObject"


/**
* @brief    ��ʼ��ɨ��ģ��
*/
EXTERN_C HRESULT WINAPI BKEngInitialize(Skylark::BKENG_PLATFORM_INIT* pInit);
/// typedef for BKEngInitialize
typedef HRESULT (WINAPI *PFN_BKEngInitialize)(Skylark::BKENG_PLATFORM_INIT* pInit);


/**
* @brief    ����ʼ��ɨ��ģ��
*/
EXTERN_C HRESULT WINAPI BKEngUninitialize();
/// typedef for BKEngUninitialize
typedef HRESULT (WINAPI *PFN_BKEngUninitialize)();


/**
* @brief    ����ɨ������ʵ��
* @param    dwBKEngVer  BKEng�İ汾��,Ĭ��ʹ��BKENG_CURRENT_VERSION,����0��ʾ�����汾���
* @param    riid        Ҫ�����Ķ����iid
* @param    ppvObj      ���ش����Ķ���
*/
EXTERN_C HRESULT WINAPI BKEngCreateObject(REFIID riid, void** ppvObj, DWORD dwBKEngVer = BKENG_CURRENT_VERSION);
/// typedef for BKEngCreateObject
typedef HRESULT (WINAPI *PFN_BKEngCreateObject)(REFIID riid, void** ppvObj, DWORD dwBKEngVer);


#endif//BKENG_H