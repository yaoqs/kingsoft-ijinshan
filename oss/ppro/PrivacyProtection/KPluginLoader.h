//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KPluginLoader.h
//  Creator     :   YangXD(yxdh)
//  Date        :   2010-4-29 17:30:50
//  Comment     :   Interface for the KPluginLoader class.
//
//////////////////////////////////////////////////////////////////////////////////////
#pragma once


template <class T>
class KPluginLoader
{
public:
	KPluginLoader() : m_pT(NULL), m_hModule(NULL)
	{
	}

	virtual ~KPluginLoader()
	{
		Uninit();
	}

	typedef HRESULT STDAPICALLTYPE GetClassObject(REFCLSID,/* [in ] */ REFIID riid, /* [out, iid_is(riid)] */ LPVOID* ppv);

	bool Init(LPCTSTR pszPluginFile)
	{
		bool bRet = false;
		

		if (NULL == pszPluginFile)
			goto Exit0;

		if (m_hModule)
			goto Exit1;

		m_hModule = ::LoadLibrary(pszPluginFile);
		if (NULL == m_hModule)
			goto Exit0;

		KPluginLoader::GetClassObject* GetClassObjectFn = (KPluginLoader::GetClassObject*)GetProcAddress(m_hModule, "DllGetClassObject");
		if (NULL == GetClassObjectFn)
			goto Exit0;


		CLSID	clsid;
		HRESULT lRetCode = GetClassObjectFn(clsid, __uuidof(T), (void**)&m_pT);
		if (FAILED(lRetCode))
			goto Exit0;


Exit1:
		bRet = true;
		m_strModulePath = pszPluginFile;
Exit0:
		return bRet;
	}

	void Uninit()
	{
		if (!m_hModule)
			return;

		if (m_pT)
		{
			m_pT->Release();
			m_pT = NULL;
		}

		::FreeLibrary(m_hModule);
		m_hModule = NULL;
		m_strModulePath.Empty();
	}

	T* GetPlugin()
	{
		return m_pT;
	}


protected:
	HMODULE		m_hModule;
	T*			m_pT;
	CString		m_strModulePath;
};
