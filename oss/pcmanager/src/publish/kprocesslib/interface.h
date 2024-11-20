
#pragma once

// �ӿڰ汾�ţ�ÿ���޸Ľӿ����Ӧ�޸ĸð汾��
#define VERSION_KSAFE_PROCESSLIB_INTERFACE		1
#define STR_KSAFE_PROCESS_LIB_DAT_NAME			    _T("kproclib.dat")
#define STR_KSAFE_PROCESS_LIB_DAT_NAME_PREFIX       L"kproclib"

class KSProcessInfo
{
public:
    int nId;					// ���
    std::wstring strProcessName;     // ������
    std::wstring strDisplayName;     // DisplayName(��δ��)
    std::wstring strDesc;			// ����
    std::wstring strPath;			// ·��
    int     nPathLevel;			// ·��������Ĭ��2��
    std::wstring strCompanyName;     // ��˾����
    std::wstring strSignName;        // ����ǩ��
    std::wstring strSoftId;          // ���Id
    int     nProcessType;       // ��������
    BOOL    bCanClose;          // �ܷ�ر�

    KSProcessInfo()
    {
        nId = 0;
        nPathLevel = 0;
        nProcessType = 0;
        bCanClose = TRUE;
    }
};


enum KProcessType
{
	enum_ProcessType_Unknown = 0,
	enum_ProcessType_SystemCore = 1,
	enum_ProcessType_SystemService = 2,
	enum_ProcessType_SystemProgram = 3,
	enum_ProcessType_KingsoftService = 4,
	enum_ProcessType_KingsoftProgram = 5,
	enum_ProcessType_3rdPartyService = 6,
	enum_ProcessType_3rdPartyProgram = 7,
	enum_ProcessType_End = 8
};

class IProcessLibQuery
{
public:
	virtual BOOL Init(LPCTSTR szLibPath) = 0;
    virtual BOOL GetInfoByPath(LPCTSTR szFullPath, KSProcessInfo** pInfo) = 0;
	virtual void DeleteInfo(KSProcessInfo* pInfo) = 0;
};


typedef IProcessLibQuery* (WINAPI* PFNGetQuery)(DWORD);
typedef VOID (WINAPI* PFNFreeQuery)(IProcessLibQuery* );

#define STR_PROCESS_LIB_DLL_NAME _T("kprocLib.dll")
#define STR_PROCESSLIB_GET_QUERY ("a")
#define STR_PROCESSLIB_FREE_QUERY ("b")


class CProcessLibLoader
{
public:
    CProcessLibLoader(CString strAppPath = L"")
    {
        m_hModDLL	= NULL;
        pfnGetQuery	= NULL;
        pfnFreeQuery = NULL;

        CString strDllPath = strAppPath;

        if (TRUE == strDllPath.IsEmpty())
        {
            strDllPath = STR_PROCESS_LIB_DLL_NAME;
        }
        else
        {
            strDllPath.Append(L"\\");
            strDllPath.Append(STR_PROCESS_LIB_DLL_NAME);
        }

        m_hModDLL	= ::LoadLibrary(strDllPath);

        if ( m_hModDLL != NULL )
        {
            pfnGetQuery  = (PFNGetQuery)::GetProcAddress( m_hModDLL, STR_PROCESSLIB_GET_QUERY);
            pfnFreeQuery = (PFNFreeQuery)::GetProcAddress( m_hModDLL, STR_PROCESSLIB_FREE_QUERY);
        }
    }
    virtual ~CProcessLibLoader()
    {
        if ( m_hModDLL != NULL )
        {
            ::FreeLibrary(m_hModDLL);
            m_hModDLL = NULL;
        }
    }

    static CProcessLibLoader* GetGlobalPtr(CString strAppPath = L"")
    {
        static CProcessLibLoader loader(strAppPath);
        return &loader;
    }

    IProcessLibQuery* GetQuery()
    {
        if ( pfnGetQuery != NULL )
            return pfnGetQuery(VERSION_KSAFE_PROCESSLIB_INTERFACE);

        return NULL;
    }

    VOID FreeQuery(IProcessLibQuery* pQuery)
    {
        if ( pfnFreeQuery != NULL )
            pfnFreeQuery(pQuery);
    }
protected:
    HMODULE				m_hModDLL;

    PFNGetQuery			pfnGetQuery;
    PFNFreeQuery		pfnFreeQuery;
};
