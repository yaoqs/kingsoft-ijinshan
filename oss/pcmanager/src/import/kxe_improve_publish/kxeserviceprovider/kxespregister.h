//////////////////////////////////////////////////////////////////////
///		@file		kxespregister.h
///		@author		luopeng
///		@date		2009-1-12 09:07:58
///
///		@brief		�����ṩ����ذ�װ��ж�غ���
//////////////////////////////////////////////////////////////////////

#pragma once
#include <map>
#include <string>
#include <sstream>
#include "../scom/scom/scom.h"
#include "../scom/scom/scomhelper.h"
#include "../scom/scom/singleton.h"
#if _MSC_VER > 1200
#include <atlstr.h>
#else
#include "../common/kxeconv_atl.h"
#endif

#define KXE_ENGINE_SERVICEPROVIDER	_T("SOFTWARE\\Kingsoft\\KISCommon\\KXEngine\\KxEServ\\ProviderList")

/**
 * @defgroup kxe_service_provider_export_group KXEngine Service Provider Export Interface
 * @{
 */

class KxEServiceProviderRegister
{
public:
	int Register(const KSCLSID& clsid, const char* pszProgId)
	{
		m_mapServiceProvider[clsid] = pszProgId;
		return 0;
	}

	int RegisterToRegistry()
	{
		HKEY hKey = NULL;
		LONG lRet = RegCreateKeyEx(
			HKEY_LOCAL_MACHINE,
			KXE_ENGINE_SERVICEPROVIDER,
			0,
			NULL,
			0,
			KEY_CREATE_SUB_KEY,
			NULL,
			&hKey,
			NULL
			);
		if (lRet != ERROR_SUCCESS)
		{
			return lRet;
		}

		std::map<KSCLSID, std::string>::iterator iter = m_mapServiceProvider.begin();
		for (; iter != m_mapServiceProvider.end(); ++iter)
		{
			std::wostringstream os;
			os << iter->first;
			if (os)
			{
				HKEY hChildKey = NULL;
				lRet = RegCreateKeyEx(
					hKey,
					os.str().c_str(),
					0,
					NULL,
					0,
					KEY_SET_VALUE ,
					NULL,
					&hChildKey,
					NULL
					);
				if (lRet != ERROR_SUCCESS)
				{
					break;
				}
				else
				{
					std::wstring strBuffer = CA2W(iter->second.c_str());
					RegSetValueEx(
						hChildKey,
						NULL,
						0,
						REG_SZ,
						(const BYTE*)strBuffer.c_str(),
						(DWORD)strBuffer.size() * sizeof(wchar_t)
						);

					RegCloseKey(hChildKey);
				}
			}
		}

		RegCloseKey(hKey);
		return lRet;
	}

	int UnregisterFromRegistery()
	{
		HKEY hKey = NULL;
		LONG lRet = RegCreateKeyEx(
			HKEY_LOCAL_MACHINE,
			KXE_ENGINE_SERVICEPROVIDER,
			0,
			NULL,
			0,
			KEY_CREATE_SUB_KEY,
			NULL,
			&hKey,
			NULL
			);
		if (lRet != ERROR_SUCCESS)
		{
			return lRet;
		}

		std::map<KSCLSID, std::string>::iterator iter = m_mapServiceProvider.begin();
		for (; iter != m_mapServiceProvider.end(); ++iter)
		{
			std::wostringstream os;
			os << iter->first;
			if (os)
			{
				lRet = RegDeleteKey(
					hKey,
					os.str().c_str()
					);
			}
		}

		RegCloseKey(hKey);
		return lRet;
	}

	int GetCLSIDCount(unsigned int& uCount)
	{
		uCount = (unsigned int)m_mapServiceProvider.size();
		return 0;
	}

	int GetCLSIDInfo(KSCLSID* pClsidBuffer, unsigned int uCount)
	{
		std::map<KSCLSID, std::string>::iterator iter = m_mapServiceProvider.begin();
		for (unsigned int i = 0; iter != m_mapServiceProvider.end() && i < uCount; ++i, ++iter)
		{
			pClsidBuffer[i] = iter->first;
		}

		return 0;
	}

private:
	std::map<KSCLSID, std::string> m_mapServiceProvider;
};

typedef SingletonHolder_Static<KxEServiceProviderRegister> KxEServiceProviderRegisterSinglton;

class KxEServiceProviderRegisterDummy
{
public:
	KxEServiceProviderRegisterDummy(const KSCLSID& clsid, const char* pszProgId)
	{
		KxEServiceProviderRegisterSinglton::Instance().Register(clsid, pszProgId);
	}
};

/// ���Service Provider����ע�ᣬ�Է��㰲װж��
#define KXE_REGISTER_SERVICE_PROVIDER(__class, __progid) \
	static KxEServiceProviderRegisterDummy __LINE__##__class(__class::GetCLSID(), __progid);

/// ��Service Provider�İ�װ��ж�غ������������ṩ����װж�س������
#define KXE_SERVICE_PROVIDER_REGISTER_EXPORT() \
	extern "C"\
	int __stdcall KxEDllRegisterServiceProvider() \
	{\
		return KxEServiceProviderRegisterSinglton::Instance().RegisterToRegistry();\
	}\
	extern "C"\
	int __stdcall KxEDllUnregisterServiceProvider() \
	{\
		return KxEServiceProviderRegisterSinglton::Instance().UnregisterFromRegistery();\
	}\
	extern "C"\
	int __stdcall KxEDllGetSPCLSIDCount(unsigned int* punCount) \
	{\
		return KxEServiceProviderRegisterSinglton::Instance().GetCLSIDCount(*punCount);\
	}\
	extern "C"\
	int __stdcall KxEDllGetSPCLSIDInfo(KSCLSID* pClsidBuffer, unsigned int uCount)\
	{\
		return KxEServiceProviderRegisterSinglton::Instance().GetCLSIDInfo(pClsidBuffer, uCount);\
	}

/**
 * @brief ��ָ��·���ķ����ṩ�߽��а�װ
 * @param[in] pwszServiceProviderPath �����ṩ�ߵ�·��
 * @return 0 �ɹ��� ����Ϊʧ��
 */
inline int KxEInstallServiceProvider(const wchar_t* pwszServiceProviderPath)
{
	HMODULE hDll = LoadLibrary(pwszServiceProviderPath);
	if (hDll == NULL)
	{
		return GetLastError();
	}

	typedef int __stdcall KxEDllRegisterServiceProvider();
	KxEDllRegisterServiceProvider* pfnKxEDllRegisterServiceProvider = 
		(KxEDllRegisterServiceProvider*)GetProcAddress(hDll, "KxEDllRegisterServiceProvider");

	int nRet = 0;
	if (pfnKxEDllRegisterServiceProvider == NULL)
	{
		nRet = GetLastError();
	}
	else
	{
		nRet = pfnKxEDllRegisterServiceProvider();
	}
	FreeLibrary(hDll);
	return nRet;
}

/**
 * @brief ��ָ��·���ķ����ṩ�߽���ж��
 * @param[in] pwszServiceProviderPath �����ṩ�ߵ�·��
 * @return 0 �ɹ��� ����Ϊʧ��
 */
inline int KxEUninstallServiceProvider(const wchar_t* pwszServiceProviderPath)
{
	HMODULE hDll = LoadLibrary(pwszServiceProviderPath);
	if (hDll == NULL)
	{
		return GetLastError();
	}

	typedef int __stdcall KxEDllUnregisterServiceProvider();
	KxEDllUnregisterServiceProvider* pfnKxEDllUnregisterServiceProvider = 
		(KxEDllUnregisterServiceProvider*)GetProcAddress(hDll, "KxEDllUnregisterServiceProvider");

	int nRet = 0;
	if (pfnKxEDllUnregisterServiceProvider == NULL)
	{
		nRet = GetLastError();
	}
	else
	{
		nRet = pfnKxEDllUnregisterServiceProvider();
	}
	FreeLibrary(hDll);
	return nRet;
}

inline int KxEGetServiceProviderCLSIDCount(const wchar_t* pwszServiceProviderPath,
										   unsigned int& uCount)
{
	HMODULE hDll = LoadLibrary(pwszServiceProviderPath);
	if (hDll == NULL)
	{
		return GetLastError();
	}

	typedef int __stdcall KxEDllGetSPCLSIDCount(unsigned int* punCount);
	KxEDllGetSPCLSIDCount* pfnKxEDllGetSPCLSIDCount = 
		(KxEDllGetSPCLSIDCount*)GetProcAddress(hDll, "KxEDllGetSPCLSIDCount");

	int nRet = 0;
	if (pfnKxEDllGetSPCLSIDCount == NULL)
	{
		nRet = GetLastError();
	}
	else
	{
		nRet = pfnKxEDllGetSPCLSIDCount(&uCount);
	}
	FreeLibrary(hDll);
	return nRet;
}

inline int KxEGetServiceProviderCLSIDInfo(const wchar_t* pwszServiceProviderPath,
										  KSCLSID* pClisdBuffer, 
										  unsigned int uCount)
{
	HMODULE hDll = LoadLibrary(pwszServiceProviderPath);
	if (hDll == NULL)
	{
		return GetLastError();
	}

	typedef int __stdcall KxEDllGetSPCLSIDInfo(KSCLSID* pClsidBuffer, unsigned int uCount);
	KxEDllGetSPCLSIDInfo* pfnKxEDllGetSPCLSIDInfo = 
		(KxEDllGetSPCLSIDInfo*)GetProcAddress(hDll, "KxEDllGetSPCLSIDInfo");

	int nRet = 0;
	if (pfnKxEDllGetSPCLSIDInfo == NULL)
	{
		nRet = GetLastError();
	}
	else
	{
		nRet = pfnKxEDllGetSPCLSIDInfo(pClisdBuffer, uCount);
	}
	FreeLibrary(hDll);
	return nRet;
}

/**
 * @}
 */