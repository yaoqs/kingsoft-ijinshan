/**
* @file    bkave.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-14 15:41
*/

#ifndef BKAVE_H
#define BKAVE_H

#include <unknwn.h>
#include "skylarkbase.h"
#include "bkavedef.h"

NS_SKYLARK_BEGIN


/// ��ȡɨ��ϸ����Ϣ�Ľӿ�
class IBKAvEngineScanDetail
{
public:

    /**
    * @brief        ����ɨ������е�ϸ����Ϣ
    * @param[in]    ɨ�������·��
    * @param[in]    �Ӷ����ɨ����
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */ 
    virtual HRESULT __stdcall OnScanDetail(
        LPCWSTR                     lpszVirtualPath,
        const BKAVE_ENGINE_RESULT*  pResult) = 0;

    /**
    * @brief        ����ʱ��Ļص�
    * @return       ����E_FAIL����������ᵼ��ɨ���ж�
    */ 
    virtual HRESULT __stdcall OnIdle() = 0;
};











/**
* @brief    �ļ������޸��ļ��Ľ������
*/
class __declspec(uuid("B62CBBBF-D56B-4cfd-9A36-61B0AAC5EF72"))
IBKAveCleanFileObj: public IUnknown
{
public:

    /**
    * @brief        �ر��ļ�
    * @remark       ������Ǳ�Ҫ�����,�������ڶ������ü���Ϊ0��ʱ���Զ��ر�.\n
    *               ���رյ��ļ�,������ ReOpen ���´�.
    */
    virtual HRESULT STDMETHODCALLTYPE Close() = 0;


    /**
    * @brief        ���ö��������ͷ�ʱɾ���ļ�
    * @param[in]    bEnableDeleteOnRelease  �Ƿ�ɾ��
    * @remark       ���ﲻʹ�� FILE_FLAG_DELETE_ON_CLOSE ��־,������Close�ļ���ʱ��,�ļ���Ȼ���Դ���
    */
    virtual HRESULT STDMETHODCALLTYPE DeleteOnRelease(BOOL bEnableDeleteOnRelease) = 0;


    /**
    * @brief        ��ȡ�ļ�������·��
    * @param[out]   pbstrPhysicalPath   �����ļ�������·��(�����ļ���)
    */
    virtual HRESULT STDMETHODCALLTYPE GetPhysicalPath(BSTR* pbstrPhysicalPath) = 0;

};













/// �ļ�����ӿ�
class __declspec(uuid("FD469B0C-4D9D-40f8-AA21-7F3F50E20A7B"))
IBKAvEngine: public IUnknown
{
public:

    /**
    * @brief        ��ʼ���ӿ�
    * @param[in]    pInit           ��ʼ������
    */ 
    virtual HRESULT STDMETHODCALLTYPE Initialize(BKAVE_ENGINE_INIT* pInit = NULL) = 0;

    /**
    * @brief        ����ʼ���ӿ�
    */ 
    virtual HRESULT STDMETHODCALLTYPE Uninitialize() = 0;

    /**
    * @brief        ��ȡ����
    * @param[out]   pSettings       ��������
    */ 
    virtual HRESULT STDMETHODCALLTYPE GetSettings(BKAVE_ENGINE_SETTINGS* pSettings) = 0;

    /**
    * @brief        ��ȡ����
    * @param[in]    pSettings       ������,���ΪNULL,�����ָ�Ĭ������
    */ 
    virtual HRESULT STDMETHODCALLTYPE SetSettings(const BKAVE_ENGINE_SETTINGS* pSettings) = 0;

    /**
    * @brief        ɨ���ļ�
    * @param[in]    lpszFilePath    �ļ�·��
    * @param[in]    pScanParam      ɨ�����
    * @param[out]   pScanResult     �ļ�ɨ����
    * @param[in]    piScanDetail    ��ȡɨ��ϸ�ڵĻص��ӿ�,����ΪNULL
    * @retval       S_OK                                ɨ��ɹ�
    * @retval       S_KSE_BWM_SKIP_TYPE_BY_SETTINGS     �������ù������͵��ļ�
    */ 
    virtual HRESULT STDMETHODCALLTYPE Scan(
        LPCWSTR                 lpszFilePath,
        const BKAVE_SCAN_PARAM* pScanParam,
        BKAVE_ENGINE_RESULT*    pScanResult,
        IBKAvEngineScanDetail*  piScanDetail = NULL) = 0;

    /**
    * @brief        ����ļ�
    * @param[in]    lpszFilePath    �ļ�·��
    * @param[in]    pScanParam      ɨ�����
    * @param[out]   pScanResult     �ļ�ɨ����
    * @param[out]   ppiCleanFileObj ����ļ����޸�����,��ô���ﷵ���޸������ʱ�ļ�
    * @param[in]    piScanDetail    ��ȡɨ��ϸ�ڵĻص��ӿ�,����ΪNULL
    * @retval       S_OK                                ɨ��ɹ�
    * @retval       S_KSE_BWM_SKIP_TYPE_BY_SETTINGS     �������ù������͵��ļ�
    */ 
    virtual HRESULT STDMETHODCALLTYPE Clean(
        LPCWSTR                 lpszFilePath,
        const BKAVE_SCAN_PARAM* pScanParam,
        BKAVE_ENGINE_RESULT*    pScanResult,
        IBKAveCleanFileObj**    ppiCleanFileObj,
        IBKAvEngineScanDetail*  piScanDetail = NULL) = 0;

    /**
    * @brief        ǿ�ƽ�������������ݿ�
    */
    virtual HRESULT STDMETHODCALLTYPE FlushCache() = 0;

    /**
    * @brief        ��ȡ�Ѽ��صĲ�����汾��
    * @param[in]    pSignVersion        ������汾�Ľṹ��
    * @remark       ��Ҫ�������Ѽ���
    */ 
    virtual HRESULT STDMETHODCALLTYPE GetLoadedSignVersion(
        BKAVE_SIGN_VERSION* pSignVersion) = 0;
};







/// ����������߰�
class __declspec(uuid("5A1B6478-9636-401d-8C4D-91AD18F92508"))
IBKAveSignToolkit: public IUnknown
{
public:

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



    /**
    * @brief        ���س�פ������,���صĲ�����᳤��פ���ڴ�
    * @remark       ����Ѿ������˲�����,�����ֱ�ӷ���
    */ 
    virtual HRESULT STDMETHODCALLTYPE LoadDaemonSign() = 0;


    /**
    * @brief        ж�س�פ������,���صĲ�����᳤��פ���ڴ�
    * @remark       ����Ѿ������˲�����,�����ֱ�ӷ���
    */ 
    virtual HRESULT STDMETHODCALLTYPE UnloadDaemonSign() = 0;


    /**
    * @brief        ���¼��ز�����,���صĲ�����᳤��פ���ڴ�
    * @remark       ������¼��ز������ʱ��, ����������ɨ��, ������ʹ�õĲ����ⲻ�ᱻ�����滻, ���ǵȵ�ɨ�����ʱ�滻
    */ 
    virtual HRESULT STDMETHODCALLTYPE ReloadSign() = 0;
};



/// ��ȡ�ļ��������ͽӿ�
class __declspec(uuid("BE23349C-611A-48cd-A6F2-4C7CCB7AFEE9"))
IBKAveFileTypeIdentifier : public IUnknown
{
public:


    /**
	* @brief        ��ȡ�ļ��Ļ�������
	* @param[in]    lpszFilePath    Ҫ�����ļ�·��
    * @param[in]    dwFileTag       �ļ���ǩ
    * @param[out]   pdwFileType     �����ļ�����,ȡֵ�� ksfiletype.h
	* @return       ��׼HRESULT����ֵ
	**/
	virtual BOOL    STDMETHODCALLTYPE LookupCachedFileType(
        LPCWSTR lpszFilePath,
        DWORD   dwFileTag,
        DWORD*  pdwFileType) = 0;


    /**
	* @brief        ��ȡ�ļ��Ļ�������
	* @param[in]    lpszFilePath    Ҫ�����ļ�·��
    * @param[in]    dwFileTag       �ļ���ǩ
    * @param[in]    dwFileType      �ļ�����,ȡֵ�� ksfiletype.h
	* @return       ��׼HRESULT����ֵ
	**/
	virtual HRESULT STDMETHODCALLTYPE UpdateFileTypeToCache(
        LPCWSTR lpszFilePath,
        DWORD   dwFileTag,
        DWORD   dwFileType) = 0;


	/**
    * @brief        ��ȡ�ļ�������
    * @param[in]    hFile           Ҫ�����ļ����
    * @param[out]   pdwFileType     �����ļ�����,ȡֵ�� ksfiletype.h
	* @return       ��׼HRESULT����ֵ
	**/
	virtual HRESULT STDMETHODCALLTYPE GetFileType(
        HANDLE  hFile,
        DWORD*  pdwFileType) = 0;


    /**
    * @brief        ǿ�ƽ�������������ݿ�
    */
    virtual HRESULT STDMETHODCALLTYPE FlushFileTypeCache() = 0;


    /**
    * @brief        �ļ������Ƿ���Ҫ��Ave����
    */
    virtual BOOL    STDMETHODCALLTYPE IsFileTypeNeedSkipByAve(DWORD dwFileType) = 0;
};






NS_SKYLARK_END






#define  FN_BKAveInitialize     "BKAveInitialize"       ///< export BKAveInitialize
#define  FN_BKAveUninitialize   "BKAveUninitialize"     ///< export BKAveUninitialize
#define  FN_BKAveCreateObject   "BKAveCreateObject"     ///< export BKAveCreateObject

/**
* @brief    ��ʼ��ɨ��ģ��
* @param    dwFlag  ����,δʹ��
*/
EXTERN_C HRESULT WINAPI BKAveInitialize(Skylark::BKAVE_PLATFORM_INIT* pInit);
/// typedef for BKAveInitialize
typedef HRESULT (WINAPI *PFN_BKAveInitialize)(Skylark::BKAVE_PLATFORM_INIT* pInit);



/**
* @brief    ����ʼ��ɨ��ģ��
* @remark   ���÷���ʼ��ǰ����ȷ����ģ�鵼�������ж��󶼱��ͷ�
*/
EXTERN_C HRESULT WINAPI BKAveUninitialize();
/// typedef for BKAveUninitialize
typedef HRESULT (WINAPI *PFN_BKAveUninitialize)();



/**
* @brief    ����BKAve��ģ��
* @param    dwBKEngVer  BKEng�İ汾��,Ĭ��ʹ��BKENG_CURRENT_VERSION,����0��ʾ�����汾���
* @param    riid        Ҫ�����Ķ����iid
* @param    ppvObj      ���ش����Ķ���
*/
EXTERN_C HRESULT WINAPI BKAveCreateObject(REFIID riid, void** ppvObj, DWORD dwBKEngVer = BKENG_CURRENT_VERSION);
/// typedef for BKAveCreateObject
typedef HRESULT (WINAPI *PFN_BKAveCreateObject)(REFIID riid, void** ppvObj, DWORD dwBKEngVer);



#endif//BKAVE_H