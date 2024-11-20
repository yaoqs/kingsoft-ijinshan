/********************************************************************
* CreatedOn: 2005-10-24   11:58
* FileName: SCOMAPI.h
* CreatedBy: qiuruifeng <qiuruifeng@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/
#ifndef SCOMAPI_H
#define SCOMAPI_H

#include "SCOMDef.h"
#include "ISCOMMalloc.h"

//��ȡSCOM��汾
extern "C"
{
	unsigned long  __stdcall KSCoBuildVersion(void);

	//�������
	KSRESULT __stdcall KSCoCreateInstance(const KSCLSID& clsid,
		const KSIID &riid ,
		void **ppv);

	//SCOM���ʼ��
	KSRESULT __stdcall KSCoInitialize(void *pvReserved = NULL);

	//SCOM�ⷴ��ʼ��,ǿ��ж�����е����
	KSRESULT __stdcall KSCoUninitialize(void);

	//ж��ָ�������������Dll
	KSRESULT __stdcall KSFreeLib(const KSCLSID& clsid);

	//ж��ָ��·����Dll
	KSRESULT __stdcall KSFreeLibEx(const char *pszModulePath);

	//ж��û����ʹ�õ�DLL(��ǰʹ�õ������Ϊ0��Dll)
	KSRESULT __stdcall KSFreeUnusedLib(void);

	//�����Ƿ����ж������Dll,��û���κ��������ʹ��,�򷵻سɹ�
	KSRESULT __stdcall KSCanUnLoadAllLibNow(void);

	//ע�����,����һ��ע��DLL���һ���򼸸����
	KSRESULT __stdcall KSRegisterServer(const CLASSINFO *ClassInfo,
		int nSize, 
		const char *pszModulePath);

	//��ע�����,���Զ�һ������������з�ע��
	KSRESULT __stdcall KSUnRegisterServer(const KSCLSID *clsids, int nSize);

	//ע�����,����һ��ע��һ��Dll������������
	KSRESULT __stdcall KSRegisterServerEx(const char *pszModulePath);

	//��ע�����,����һ�η�ע��һ��Dll������������
	KSRESULT __stdcall KSUnRegisterServerEx(const char *pszModulePath);

	//�ṩͳһ���ڴ����
	void* __stdcall KSCoTaskMemAlloc(size_t uSize);

	//�ṩͳһ���ڴ���� 
	void __stdcall KSCoTaskMemFree(void *pv,  size_t uSize);

	//��ȡ�ڴ�������ӿ�
	KSRESULT __stdcall KSCoGetMalloc(ISCOMMalloc **ppISCOMMalloc);

	//��ȡ������ڵ�dll·��
	KSRESULT __stdcall KSCoGetLibraryPath(const KSCLSID& clsid, 
		char* szModulePath, 
		size_t& uSize
		);
	//����ǰĿ¼�µ�SCOM.dll��������ڣ���·��д��ע�����
	KSRESULT __stdcall KSInitConfigData(void);

	//����SCOM���dll,ֻ�ܼ��������ļ���û�г��ֵ��ļ�
	KSRESULT __stdcall KSCoLoadLibrary(const char *pszModulePath);

	//����װ�������ļ�
	KSRESULT __stdcall KSReLoadConfigure(void);

	//�����ID��ȡ������Ѻ�����,uSize���������Ҫ��buffer�Ĵ�С
	KSRESULT __stdcall KSCoProgIDFromCLSID(const KSCLSID& clsid, 
		char* pszProgID, 
		size_t& uSize
		);

	KSRESULT __stdcall KSGetPropertyCLSID(DWORD dwProperty, KSCLSID* pCLSIDs, size_t* psizeCLSID);
	KSRESULT __stdcall KSSetCLSIDProperty(const KSCLSID* pCLSID, DWORD dwProperty);



	//������Ѻ����ƻ�ȡ���id
	KSRESULT __stdcall KSCoCLSIDFromProgID(const char* pszProgID, KSCLSID* pclsid);
	
	//ж��ָ��·����Dll
	KSRESULT __stdcall KSFreeLibExW(const wchar_t* pszModulePath);

	KSRESULT __stdcall KSRegisterServerW(const CLASSINFO *pClassInfo,
		int nSize, 
		const wchar_t *pszModulePath);

	KSRESULT __stdcall KSRegisterServerExW(const wchar_t *pszModulePath);

	//��ע�����,����һ�η�ע��һ��Dll������������
	KSRESULT __stdcall KSUnRegisterServerExW(const wchar_t *pszModulePath);

	KSRESULT __stdcall KSCoGetLibraryPathW(const KSCLSID& clsid, 
		wchar_t* szModulePath, 
		size_t& uSize
		);

	//�����ID��ȡ������Ѻ�����,uSize���������Ҫ��buffer�Ĵ�С
	KSRESULT __stdcall KSCoProgIDFromCLSIDW(const KSCLSID& clsid, 
		wchar_t* pszProgID, 
		size_t& uSize
		);

	KSRESULT __stdcall KSCoCLSIDFromProgIDW(const wchar_t* pszProgID, KSCLSID* pclsid);

	KSRESULT __stdcall KSCoLoadLibraryW(const wchar_t* pszModulePath);


};

#endif //SCOMAPI_H