/********************************************************************
* CreatedOn: 2006-9-1   10:20
* FileName: SCOMExportFuncType.h
* CreatedBy: qiuruifeng <qiuruifeng@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/
#ifndef SCOMEXPORTFUNCTYPE_H
#define SCOMEXPORTFUNCTYPE_H
#include "SCOMDef.h"
#include "ISCOMMalloc.h"
#include "../../kxecommon/kxecommon.h"

typedef unsigned long  (__stdcall *pfnKSCoBuildVersionType)(void);

//�������

typedef KSRESULT (__stdcall *pfnKSCoCreateInstanceType)(
									  const KSCLSID& clsid,
									  const KSIID &riid ,
									  void **ppv);
//SCOM���ʼ��

typedef KSRESULT (__stdcall *pfnKSCoInitializeType)(void *pvReserved);

//SCOM�ⷴ��ʼ��,ǿ��ж�����е����

typedef KSRESULT (__stdcall *pfnKSCoUninitializeType)(void);

//ж��ָ�������������Dll

typedef KSRESULT (__stdcall *pfnKSFreeLibType)(const KSCLSID& clsid);

//ж��ָ��·����Dll

typedef KSRESULT (__stdcall *pfnKSFreeLibExType)(const char *pszModulePath);

//ж��û����ʹ�õ�DLL(��ǰʹ�õ������Ϊ0��Dll)
 
typedef KSRESULT (__stdcall *pfnKSFreeUnusedLibType)(void);

//�����Ƿ����ж������Dll,��û���κ��������ʹ��,�򷵻سɹ�

typedef KSRESULT (__stdcall *pfnKSCanUnLoadAllLibNowType)(void);

//ע�����,����һ��ע��DLL���һ���򼸸����
 
typedef KSRESULT (__stdcall *pfnKSRegisterServerType)(const CLASSINFO *ClassInfo,
									int nSize, 
									const char *pszModulePath);

//��ע�����,���Զ�һ������������з�ע��
 
typedef KSRESULT (__stdcall *pfnKSUnRegisterServerType)(const KSCLSID *clsids, int nSize);

//ע�����,����һ��ע��һ��Dll������������

typedef KSRESULT (__stdcall *pfnKSRegisterServerExType)(const char *pszModulePath);

//��ע�����,����һ�η�ע��һ��Dll������������

typedef KSRESULT (__stdcall *pfnKSUnRegisterServerExType)(const char *pszModulePath);

//�ṩͳһ���ڴ����

typedef void* (__stdcall *pfnKSCoTaskMemAllocType)(size_t uSize);

//�ṩͳһ���ڴ���� 

typedef void (__stdcall *pfnKSCoTaskMemFreeType)(void *pv,  size_t uSize);

//��ȡ�ڴ�������ӿ�

typedef KSRESULT (__stdcall *pfnKSCoGetMallocType)(ISCOMMalloc **ppISCOMMalloc);

//��ȡ������ڵ�dll·��
 
typedef KSRESULT (__stdcall *pfnKSCoGetLibraryPathType)(const KSCLSID& clsid, 
									  char* szModulePath, 
									  size_t& uSize
									  );

//�����յ������ļ�

typedef KSRESULT (__stdcall *pfnKSInitConfigDataType)(void);

//����SCOM���dll,ֻ�ܼ��������ļ���û�г��ֵ��ļ�

typedef KSRESULT (__stdcall *pfnKSCoLoadLibraryType)(const char *pszModulePath);

//����װ�������ļ�

typedef KSRESULT (__stdcall *pfnKSReLoadConfigureType)(void);


//�����ID��ȡ������Ѻ�����,uSize���������Ҫ��buffer�Ĵ�С
typedef KSRESULT (__stdcall *pfnKSCoProgIDFromCLSIDType)(const KSCLSID& clsid, 
									   char* pszProgID, 
									   size_t& uSize
									   );

typedef KSRESULT (__stdcall *pfnKSGetPropertyCLSIDType)(DWORD dwProperty, 
														KSCLSID* pCLSIDs, 
														size_t* psizeCLSID
														);
	
typedef KSRESULT (__stdcall *pfnKSSetCLSIDProperty)(const KSCLSID* pCLSID, DWORD dwProperty);

typedef KSRESULT (__stdcall *pfnKSCoCLSIDFromProgIDType)(const char* pszProgID, KSCLSID* pclsid);

typedef KSRESULT (__stdcall *pfnKSFreeLibExWType)(const wchar_t* pszModulePath);

typedef KSRESULT (__stdcall *pfnKSRegisterServerWType)(const CLASSINFO *pClassInfo,
									 int nSize, 
									 const wchar_t *pszModulePath);

typedef KSRESULT (__stdcall *pfnKSRegisterServerExWType)(const wchar_t *pszModulePath);

typedef KSRESULT (__stdcall *pfnKSUnRegisterServerExWType)(const wchar_t *pszModulePath);

typedef KSRESULT (__stdcall *pfnKSCoGetLibraryPathWType)(const KSCLSID& clsid, 
									   wchar_t* szModulePath, 
									   size_t& uSize
									   );

typedef KSRESULT (__stdcall *pfnKSCoProgIDFromCLSIDWType)(const KSCLSID& clsid, 
										wchar_t* pszProgID, 
										size_t& uSize
										);

typedef KSRESULT (__stdcall *pfnKSCoCLSIDFromProgIDWType)(const wchar_t* pszProgID, KSCLSID* pclsid);

typedef KSRESULT (__stdcall *pfnKSCoLoadLibraryWType)(const wchar_t* pszModulePath);

#endif //SCOMEXPORTFUNCTYPE_H