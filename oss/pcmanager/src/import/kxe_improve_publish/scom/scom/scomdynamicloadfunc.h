/********************************************************************
* CreatedOn: 2006-9-5   16:49
* FileName: SCOMDynamicLoadFunc.h
* CreatedBy: qiuruifeng <qiuruifeng@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/
#ifndef SCOMDYNAMICLOADFUNC_H
#define SCOMDYNAMICLOADFUNC_H

#ifndef SCOM_USE_STATIC_LOADING
#include "SCOMAPI.h"
#include "SCOMDynamicLoader.h"
//��ȡSCOM��汾
inline unsigned long  __stdcall KSCoBuildVersion(void)
{
	return GlobalSCOMLoader::Instance().KSCoBuildVersion();
}

//�������
inline KSRESULT __stdcall KSCoCreateInstance(
	const KSCLSID& clsid,
	const KSIID &riid , 
	void **ppv)
{
	return GlobalSCOMLoader::Instance().KSCoCreateInstance(clsid, riid, ppv);
}
//SCOM���ʼ��
inline KSRESULT __stdcall KSCoInitialize(void *pvReserved)
{
	return GlobalSCOMLoader::Instance().KSCoInitialize(pvReserved);
}

//SCOM�ⷴ��ʼ��,ǿ��ж�����е����
inline KSRESULT __stdcall KSCoUninitialize(void)
{
	return GlobalSCOMLoader::Instance().KSCoUninitialize();
}

//�����Ƿ����ж������Dll,��û���κ��������ʹ��,�򷵻سɹ�
inline KSRESULT __stdcall KSCanUnLoadAllLibNow(void)
{
	return GlobalSCOMLoader::Instance().KSCanUnLoadAllLibNow();
}

//ж��ָ�������������Dll
inline KSRESULT __stdcall KSFreeLib(const KSCLSID& clsid)
{
	return GlobalSCOMLoader::Instance().KSFreeLib(clsid);
}

//ж��ָ��·����Dll
inline KSRESULT __stdcall KSFreeLibEx(const char *pszModulePath)
{
	return GlobalSCOMLoader::Instance().KSFreeLibEx(pszModulePath);
}

//ж��û����ʹ�õ�DLL(��ǰʹ�õ������Ϊ0��Dll),�����ػ�û�б�ж�ص�DLL��Ŀ
inline KSRESULT __stdcall KSFreeUnusedLib(void)
{
	return GlobalSCOMLoader::Instance().KSFreeUnusedLib();
}

//ע�����,����һ��ע��DLL���һ���򼸸����
inline KSRESULT __stdcall KSRegisterServer(
	const CLASSINFO *ClassInfo, 
	int nSize, 
	const char *pszModulePath)
{
	return GlobalSCOMLoader::Instance().KSRegisterServer(
		ClassInfo, 
		nSize, 
		pszModulePath);
}

//��ע�����,���Զ�һ������������з�ע��
inline KSRESULT __stdcall KSUnRegisterServer(const KSCLSID *clsids, int nSize)
{
	return GlobalSCOMLoader::Instance().KSUnRegisterServer(clsids, nSize);
}

//ע�����,����һ��ע��һ��Dll������������
inline KSRESULT __stdcall KSRegisterServerEx(const char *pszModulePath)
{
	return GlobalSCOMLoader::Instance().KSRegisterServerEx(pszModulePath);
}

//��ע�����,����һ�η�ע��һ��Dll������������
inline KSRESULT __stdcall KSUnRegisterServerEx(const char *pszModulePath)
{
	return GlobalSCOMLoader::Instance().KSUnRegisterServerEx(pszModulePath);
}

//�ṩͳһ���ڴ����
inline void* __stdcall KSCoTaskMemAlloc(size_t uSize)
{
	return GlobalSCOMLoader::Instance().KSCoTaskMemAlloc(uSize);
}

//�ṩͳһ���ڴ���� 
inline void __stdcall KSCoTaskMemFree(void *pv, size_t uSize)
{
	GlobalSCOMLoader::Instance().KSCoTaskMemFree(pv, uSize);
}

//�����յ������ļ�
inline KSRESULT __stdcall KSInitConfigData(void)
{
	return GlobalSCOMLoader::Instance().KSInitConfigData();
}
//��ȡ�ڴ�������ӿ�
inline KSRESULT __stdcall KSCoGetMalloc(ISCOMMalloc **ppSimpleMalloc)
{
	return GlobalSCOMLoader::Instance().KSCoGetMalloc(ppSimpleMalloc);
}

//��ȡ������ڵ�dll·��
inline KSRESULT __stdcall KSCoGetLibraryPath(const KSCLSID& clsid, char* szModulePath, size_t& uSize)
{
	return GlobalSCOMLoader::Instance().KSCoGetLibraryPath(clsid, szModulePath, uSize);
}

//����SCOM���dll,ֻ�ܼ��������ļ���û�г��ֵ��ļ�
inline KSRESULT __stdcall KSCoLoadLibrary(const char *pszModulePath)
{
	return GlobalSCOMLoader::Instance().KSCoLoadLibrary(pszModulePath);
}

//���¼��������ļ�
inline KSRESULT __stdcall KSReLoadConfigure(void)
{
	return GlobalSCOMLoader::Instance().KSReLoadConfigure();
}

//�����ID��ȡ������Ѻ�����,uSize���������Ҫ��buffer�Ĵ�С
inline KSRESULT __stdcall KSCoProgIDFromCLSID(const KSCLSID& clsid, 
											  char* pszProgID,
											  size_t& uSize)
{
	return GlobalSCOMLoader::Instance().KSCoProgIDFromCLSID(clsid, pszProgID, uSize);
}

inline KSRESULT __stdcall KSGetPropertyCLSID(DWORD dwProperty, KSCLSID* pCLSIDs, size_t* psizeCLSID)
{
	return GlobalSCOMLoader::Instance().KSGetPropertyCLSID(dwProperty, pCLSIDs, psizeCLSID);
}

inline KSRESULT __stdcall KSSetCLSIDProperty(const KSCLSID* pCLSID, DWORD dwProperty)
{
	return GlobalSCOMLoader::Instance().KSSetCLSIDProperty(pCLSID, dwProperty);
}

inline KSRESULT __stdcall KSCoCLSIDFromProgID(const char* pszProgID, KSCLSID* pclsid)
{
	return GlobalSCOMLoader::Instance().KSCoCLSIDFromProgID(pszProgID, pclsid);
}


inline KSRESULT __stdcall KSFreeLibExW(const wchar_t* pszModulePath)
{
	return GlobalSCOMLoader::Instance().KSFreeLibExW(pszModulePath);
}


inline KSRESULT __stdcall KSRegisterServerW(const CLASSINFO *pClassInfo,
									 int nSize, 
									 const wchar_t *pszModulePath)
{
	return GlobalSCOMLoader::Instance().KSRegisterServerW(pClassInfo, nSize, pszModulePath);
}

inline KSRESULT __stdcall KSRegisterServerExW(const wchar_t *pszModulePath)
{
	return GlobalSCOMLoader::Instance().KSRegisterServerExW(pszModulePath);
}

inline KSRESULT __stdcall KSUnRegisterServerExW(const wchar_t *pszModulePath)
{
	return GlobalSCOMLoader::Instance().KSUnRegisterServerExW(pszModulePath);
}

inline KSRESULT __stdcall KSCoGetLibraryPathW(const KSCLSID& clsid, 
									   wchar_t* szModulePath, 
									   size_t& uSize)
{
	return GlobalSCOMLoader::Instance().KSCoGetLibraryPathW(clsid, szModulePath, uSize);
}

inline KSRESULT __stdcall KSCoProgIDFromCLSIDW(const KSCLSID& clsid, 
										wchar_t* pszProgID, 
										size_t& uSize)
{
	return GlobalSCOMLoader::Instance().KSCoProgIDFromCLSIDW(clsid, pszProgID, uSize);
}

inline KSRESULT __stdcall KSCoCLSIDFromProgIDW(const wchar_t* pszProgID, KSCLSID* pclsid)
{
	return GlobalSCOMLoader::Instance().KSCoCLSIDFromProgIDW(pszProgID, pclsid);
}

inline KSRESULT __stdcall KSCoLoadLibraryW(const wchar_t* pszModulePath)
{
	return GlobalSCOMLoader::Instance().KSCoLoadLibraryW(pszModulePath);
}
#endif

#endif //SCOMDYNAMICLOADFUNC_H