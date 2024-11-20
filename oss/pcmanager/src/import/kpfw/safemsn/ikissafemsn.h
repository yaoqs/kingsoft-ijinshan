#pragma once

#include "SCOM/SCOM/SCOMDef.h"

#define E_NOFIND_MSN	-2
#define E_NOFIND_DLL	-3

#define KIS_SAFEMSN_EVENT_NAME	L"B827C2AC-0088-4615-8BBD-439AB3ED64CB"
#define SUB_REGISTER_KEY	L"SOFTWARE\\kissafemsn"
#define SAFE_MSN_DLL_PATH	TEXT("SafeMsnPath")
#define ENABLE_SAFE_MSN L"EnableMsn"
#define BOOL_FALSE		L"False"
#define BOOL_TRUE		L"True"



[
	uuid("A121AA2D-8CF5-44a9-BCF2-7AC3A9526387")
]
interface IKisSafeMsn:public IUnknown
{
	virtual STDMETHODIMP SetInstallPath() = 0;

	/**
	*@return E_NOFIND_MSN: û���ҵ�MSN,û��MSN��ע������MSN �� exe�ļ�������
	*@return E_FAIL: �����ļ�ʧ��
	*@return S_OK:��װ�ɹ�
	*/
	virtual STDMETHODIMP Install() = 0;

	/**
	*@return E_NOFIND_MSN: û���ҵ�MSN,û��MSN��ע������MSN �� exe�ļ�������
	*@return E_FAIL: ɾ���ļ�ʧ��
	*@return S_OK:ж�سɹ�
	*/
	virtual STDMETHODIMP UnInstall() = 0;

	/**
	*@return FALSE: MSN����ģ��û�а�װ
	*@return TRUE: MSN����ģ���Ѿ���װ
	*/
	virtual STDMETHODIMP isInstalled() = 0;

	/**
	*@brief  ����MSN����ģ��
	*@remark  key = ENABLE_SAFE_MSN  value = BOOL_FALSE	  �رռ���
	    	  key = ENABLE_SAFE_MSN  value = BOOL_TRUE	  ��������
	*@return ERROR_INVALID_PARAMETER: ��������
	*@return E_FAIL: ����ʧ��
	*@return S_OK: ���óɹ�
	*/
	virtual STDMETHODIMP SetConfig(
		/*[in]*/TCHAR *szKey, 
		/*[in]*/TCHAR *szValue) = 0;

	/**
	*@brief  ��ȡMSN����ģ������
	*@return ERROR_INVALID_PARAMETER: ��������
	*@return E_FAIL: ��ȡʧ��
	*@return S_OK: ��ȡ�ɹ�
	*@remark dwValueLen ��Ϊ�����������СӦ��Ϊ strlen(_value)*sizeof(TCHAR)
	*/
	virtual STDMETHODIMP GetConfig(
		/*[in]*/TCHAR *szKey, 
		/*[out]*/TCHAR *szValue, 
		/*[in,out]*/DWORD &dwValueLen) = 0;		
	
	virtual STDMETHODIMP_(BOOL) IsRunning() = 0;
};

_declspec(selectany) extern const KSCLSID CLSID_KisSafeMsn = { 0x2bd8d816, 0xb04a, 0x44ef, { 0x9f, 0x30, 0xf7, 0x20, 0x63, 0xb6, 0x6c, 0xba }  };