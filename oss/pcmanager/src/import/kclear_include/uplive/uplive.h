#pragma once
//#include "uplivedef.h"

// ��׼���»ص��ӿ�
class IStdUpdateCallback
{
public:
    /**
    * @brief    �������͵Ļص�
    * @param    dwUpdType        ��ǰ���ͣ��⻹��bin�����߷ֿ�������
    */
    virtual void STDMETHODCALLTYPE UpdateType( DWORD dwUpdType ) = 0;
    /**
    * @brief    ���µĻص�
    * @param    dwStatus        ��ǰ��״̬
    * @param    lpInformation   �ַ�����Ϣ,���庬��ȡ����dwStatus
    * @param    dwPercentage    ��ɵİٷֱ�,ȡֵ��0��100
    * @retval   TRUE            ��������
    * @retval   FALSE           �ж�����
    */
    virtual BOOL STDMETHODCALLTYPE OnProgress(
        DWORD   dwStatus,
        DWORD   dwPercentage
        ) = 0;

    /**
    * @brief    ���´���Ļص�
    * @param    dwStatus        ��ǰ��״̬
    * @param    hErrCode        ������,���������
    * @param    lpInformation   �ַ�����Ϣ,���庬��ȡ����dwStatus
    */
    virtual void STDMETHODCALLTYPE OnError(
        DWORD   dwStatus,
        HRESULT hErrCode, 
        LPCWSTR lpInformation
        ) = 0;

    /**
    * @brief    �ļ�����ǰ֪ͨ
    * @param    lpszModuleName      ģ����
    * @param    lpszFileName        �ļ���
    * @param    nType               �ļ����ͣ����������������ļ����������ļ����������ļ��ȣ�
    * @param    lpszExtend          ��չ�ַ���
    */
    virtual void STDMETHODCALLTYPE OnFilePreUpdated(
        LPCWSTR lpszModuleName, 
        LPCWSTR lpszFileName,
        int     nType,
        LPCWSTR lpszVersion = NULL,
        LPCWSTR lpszExtend = NULL
        ) = 0;

    /**
    * @brief    ��ʼ�滻�ļ�
    * @param    dwUpdType        ��ǰ���ͣ��⻹��bin�����߷ֿ�������
    * @retval   TRUE            ��������
    * @retval   FALSE           �ж�����
    */
    virtual BOOL STDMETHODCALLTYPE OnBeginUpdateFiles( DWORD dwUpdType ) = 0;

    /**
    * @brief    �ļ��滻֪ͨ
    * @param    lpszModuleName      ģ����
    * @param    lpszFileName        �ļ���
    * @param    nType               �ļ����ͣ����������������ļ����������ļ����������ļ��ȣ�
    * @param    nOperation          �������ͣ����ݡ��滻�������滻�ȣ�
    * @param    dwErrorCode         ��׼LastError�����룬0Ϊ�ɹ�����Ϊʧ��
    */
    virtual void STDMETHODCALLTYPE OnFileReplace(
        LPCWSTR lpszModuleName, 
        LPCWSTR lpszFileName,
        int     nType,
        int     nOperation,
        DWORD   dwErrorCode
        ) = 0;

    /**
    * @brief    �ļ��������֪ͨ
    * @param    lpszModuleName      ģ����
    * @param    lpszFileName        �ļ���
    * @param    nType               �ļ����ͣ����������������ļ����������ļ����������ļ��ȣ�
    */
    virtual void STDMETHODCALLTYPE OnFileUpdated(
        LPCWSTR lpszModuleName, 
        LPCWSTR lpszFileName,
        int     nType
        ) = 0;

	/**
    * @brief    ���ظ����ļ�֮ǰ֪ͨ
    * @param    lpszDownloadUrl      ����·��
    * @param    lpszFileName         �����ļ�����
    * @param    lpszTargetFileName    Ŀ���ļ�����
	* @param    lpszTargetPath		  Ŀ��·��
	* @param    lpszCRC			      �����ļ�CRC
	* @param    lpszHint			  ������Ϣ
	* @param    lpszVer				  ���ذ汾
	* @param    dwSize				  �ļ���С
	* @param    m_b3rd				  �Ƿ������
	* @param    nType				  ��������
    */
    virtual void STDMETHODCALLTYPE OnPreDownloadUpdated(
		LPCWSTR lpszDownloadUrl,
		LPCWSTR lpszFileName,
		LPCWSTR lpszTargetFileName,
		LPCWSTR lpszTargetPath,
		LPCWSTR lpszCRC,
		LPCWSTR lpszHint,
		LPCWSTR lpszVer,
		DWORD   dwSize,
		BOOL    b3rd,
		int     nType
        ) = 0;
};

class   IUpdatePolicyCallback
{
public:
    //
    //  ��Ϣ�����ļ��������֪ͨ
    //  lpwszConfigPath �����ص���·��
    //  hr              ��� С��0Ϊʧ����
    //
    virtual void MessageConfigUpdate( LPCWSTR lpwszConfigPath, HRESULT hr ) = 0;
    virtual void VirusLibUpdated( ULONGLONG ullVersion, BOOL bSuccessful = FALSE ) = 0;
    virtual void NotifyLibUpdate( LPCWSTR lpwszFileName ) = 0;
};

class   IUpdateDownloadFileCallback
{
public:
    virtual void BeginDownload() = 0;
    virtual void Retry( DWORD dwTimes ) = 0;
    // ����FALSE��ֹ����
    virtual BOOL DownloadProgress(
        DWORD dwTotalSize, 
        DWORD dwReadSize 
        ) = 0;
    virtual void FinishDownload( HRESULT hError ) = 0;
};

class __declspec(uuid("DA8FE310-1A9A-4471-B693-EBCFBC7B103F"))
IUplive : public IUnknown
{
public:
    virtual HRESULT Initialize() = 0;
    virtual HRESULT Uninitialize() = 0;
    virtual void    SetCallback( 
        IStdUpdateCallback* piStd, 
        IUpdatePolicyCallback* piUpdPolicy 
        ) = 0;
    virtual HRESULT Start() = 0;
    virtual void    Stop() = 0;
    virtual void    WaitExit( DWORD dwWaitTime ) = 0;
    virtual HRESULT NotifyUpdateMessage() = 0;
    virtual HRESULT NotifyUpdate( int nType ) = 0;
};

class __declspec(uuid("C9E767AB-DC5D-4c77-8344-2520FB29A306"))
IUpdUtility : public IUnknown
{
public:
    //
    //  lpwszUrl : Ŀ���ļ�URL
    //  lpwszTargetPath : ���·��
    //  bPack : �Ƿ�Ϊzlib��ѹ����
    //  lpwszHashCheck : У��hash����Ϊ������������ļ���hash��˱Ƚϣ�����ͬ�򷵻�ʧ��
    //
    virtual HRESULT DownloadFile( 
        LPCWSTR lpwszUrl, 
        LPCWSTR lpwszTargetPath, 
        BOOL bPack, 
        LPCWSTR lpwszHashCheck = NULL,
        IUpdateDownloadFileCallback* piCallback = NULL
        ) = 0;

    //
    //  lpwszExpression : ���ʽ
    //  TRUE : ��ʾ�ɹ����߷��ϱ��ʽ����
    //  FALSE : ��ʾʧ�ܻ��߲����ϱ��ʽ����
    virtual BOOL DoExpression( LPCWSTR lpwszExpression ) = 0;
};

#define FN_CreateObject			"CreateObject"

//EXTERN_C HRESULT WINAPI CreateObject( REFIID riid, void** ppvObj );
typedef HRESULT (WINAPI *PFN_CreateObject)( REFIID riid, void** ppvObj );
