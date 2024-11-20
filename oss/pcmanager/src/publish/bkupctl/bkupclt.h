//////////////////////////////////////////////////////////////////////////
//   File Name: bkupclt.h
// Description: Update Module Interface Definition
//     Creator: Zhang Xiaoxuan
//     Version: 2009.6.1 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <Unknwn.h>

#include "bkupclterr.h"

// ����״̬
enum Update_Status {
    BkUpd_Status_None               = 0,    // ռλ��
    BkUpd_Status_Check_Version      = 1,    // ���汾
    BkUpd_Status_Check_FileList     = 2,    // �����ļ��б�
    BkUpd_Status_Download_Files     = 3,    // �����ļ�
    BkUpd_Status_Update_Files       = 4,    // �����ļ�
    BkUpd_Status_Finished           = 5,    // ��ɸ���
};

// ���»ص��ӿ�
class __declspec(uuid("F0790C63-75E1-4e88-A031-A909FCAF7730"))
    IBkUpdateCallback
{
public:
    /**
    * @brief    ���µĻص�
    * @param    dwStatus        ��ǰ��״̬
    * @param    lpInformation   �ַ�����Ϣ,���庬��ȡ����dwStatus
    * @param    dwPercentage    ��ɵİٷֱ�,ȡֵ��0��100,����֤һ���᷵��100
    * @retval   TRUE            ��������
    * @retval   FALSE           �ж�����
    */
    virtual BOOL STDMETHODCALLTYPE OnProgress(
        DWORD   dwStatus,
        DWORD   dwPercentage) = 0;

    /**
    * @brief    ���´���Ļص�
    * @param    dwStatus        ��ǰ��״̬
    * @param    hErrCode        ������,���������
    * @param    lpInformation   �ַ�����Ϣ,���庬��ȡ����dwStatus
    */
    virtual void STDMETHODCALLTYPE OnError(
        DWORD   dwStatus,
        HRESULT hErrCode, 
        LPCWSTR lpInformation) = 0;

    /**
    * @brief    ��ѯģ������Ŀ¼�Ļص�
    * @param    lpszModuleName      ģ����
    * @param    lpszModulePathRet   �ص�����ģ������Ŀ¼
    * @param    dwRetBufferSize     lpszModulePathRetָ���buffer��С��by wchar��
    * @retval   TRUE                ֧�ִ�ģ������
    * @retval   FALSE               ��֧�ִ�ģ������
    */
    virtual BOOL STDMETHODCALLTYPE OnQueryModulePath(
        LPCWSTR lpszModuleName, 
        LPWSTR lpszModulePathRet, 
        DWORD dwRetBufferSize) = 0;

    /**
    * @brief    �ļ�����֪ͨ
    * @param    lpszModuleName      ģ����
    * @param    lpszFileName        �ļ���
    */
    virtual void STDMETHODCALLTYPE OnFileUpdated(
        LPCWSTR lpszModuleName, 
        LPCWSTR lpszFileName) = 0;

    /**
    * @brief    �ļ�����֪ͨ
    * @param    lpszModuleName      ģ����
    * @param    lpszFileName        �ļ���
    * @param    bBackup             TRUE : ����ԭʼ�ļ�, FALSE : �滻��װĿ¼�ļ�
    * @param    dwErrorCode         ��׼LastError������
    */
    virtual void STDMETHODCALLTYPE OnFileReplace(
        LPCWSTR lpszModuleName, 
        LPCWSTR lpszFileName,
        BOOL    bBackup,
        DWORD   dwErrorCode) = 0;
};

// ���½ӿڶ���
class __declspec(uuid("F0790C63-75E1-4e88-A031-A909FCAF7730"))
    IBkUpdater: public IUnknown
{
public:

    virtual HRESULT STDMETHODCALLTYPE CheckVersion(
        LPCWSTR                 lpszVersionUrl,
        LPCWSTR                 lpszAppName,
        LPCWSTR                 lpszSelfFileName,
        IBkUpdateCallback*      piCallback
        ) = 0;

    virtual HRESULT STDMETHODCALLTYPE Update(
        IBkUpdateCallback*      piCallback
        ) = 0;

    // �Ƿ���Ҫ������ǰ����
    virtual BOOL    STDMETHODCALLTYPE NeedRestart() = 0;
};

/// class Factory
EXTERN_C HRESULT BkCreateUpdater(IBkUpdater** ppiObj);

