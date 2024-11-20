/**
* @file    bkquerier.h
* @brief   ...
* @author  ����
* @date    2010-7-12 14:42
*/

#ifndef BKFILEQUERIER_H
#define BKFILEQUERIER_H

#include <unknwn.h>
#include "skylarkbase.h"
#include "bkengdef.h"
#include "bklevel.h"

#define defBK_QUERY_SEC_STATUS_WHITE    (0x01)
#define defBK_QUERY_SEC_STATUS_BLACK    (0x02)
#define defBK_QUERY_SEC_STATUS_GRAY     (0x03)

/// ��ѯ���
struct BKQUERIER_RESULT
{
	UINT32      uSize;              ///< �ṹ���С
	// ------------------------------------------------------------
	// Version[1, ?]

    UINT32      uSecStatus;         ///< �ļ����ԣ��ڡ��ס���
	WCHAR       szVirusName[64];    ///< ���������ڵ������ʹ�á�
	BOOLEAN     bNeedUpload;        ///< �ļ���Ҫ�ϴ�
	HRESULT     hrLastError;        ///< ���һ�β����Ĵ�����
};

/**
* @brief �ƶ˵Ĳ�ѯ�ӿ�
*/
class __declspec(uuid("B1B4171F-3E5C-4a68-98FA-56FDCC4B4028"))
IBKFileQuerier : public IUnknown
{
public:
	/**
	* @brief        ��ʼ���ƶ˼�����
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE Initialize() = 0;


	/**
	* @brief        ����ʼ���ƶ˼�����
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE Uninitialize() = 0;

	/**
	* @brief        ��ֹ���еĵ���
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE Cancel() = 0;

	/**
	* @brief        ��ѯ�ƶ˵õ����
	* @param[in]    lpszFilePath    ԭʼ�ļ�·��
	* @param[out]    result          ��ǰ�ļ��Ĳ�ѯ���
	* @param[in]    plTimeMax       ��ʱֵ
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE Query(
		LPCWSTR             lpszFilePath,
		BKQUERIER_RESULT&   result,
		LONG* plTimeMax
		) = 0;
};




/**
* @brief �ƶ˵Ĳ�ѯ�ӿڻص�
*/
class IBKMultiFileQuerierCallback
{
public:
    virtual HRESULT STDMETHODCALLTYPE OnBKFileQuery(
        LPCWSTR             lpszFilePath,
        BKQUERIER_RESULT&   result,
        void*               pvFlag) = 0;
};

/**
* @brief �ƶ˵Ĳ�ѯ�ӿ�
*/
class __declspec(uuid("3E8AC0CA-DC1D-4e8c-B2C3-CF8092B3598D"))
IBKMultiFileQuerier : public IUnknown
{
public:
	/**
	* @brief        ��ʼ���ƶ˼�����
	* @return       FAILED()Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE Initialize() = 0;


	/**
	* @brief        ����ʼ���ƶ˼�����
	* @return       FAILED()Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE Uninitialize() = 0;

	/**
	* @brief        ��ֹ���еĵ���
	* @return       FAILED()Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE Cancel() = 0;

    /**
	* @brief        ����ɨ��
	*/
	virtual HRESULT STDMETHODCALLTYPE StartScan(IBKMultiFileQuerierCallback* piCallback) = 0;

    /**
	* @brief        �ȴ�ɨ�����
	*/
    virtual HRESULT STDMETHODCALLTYPE AppendFile(
        LPCWSTR lpszFilePath,
        void*   pvFlag = NULL) = 0;

    /**
	* @brief        �ύ���ȴ����淵�����н��
	*/
	virtual DWORD   STDMETHODCALLTYPE WaitForFinish(DWORD dwWaitTime = INFINITE) = 0;

};

#endif // BKFILEQUERIER_H