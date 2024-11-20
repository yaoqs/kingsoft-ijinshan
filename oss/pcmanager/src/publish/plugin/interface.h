
#pragma once
#include <atlstr.h>

#ifndef VIRTUAL_ENG
#define VIRTUAL_ENG virtual
#endif

#define VERSION_PLUG_INTERFACE_LOW				3
#define VERSION_PLUG_INTERFACE_HIGH				7

//////////////////////////////////////////////////////////////////////////
/// ���ؽ������
#define S_FAILED_CANCEL						0x80000001
#define S_FAILED_LIB_NO_EXIST				0x80000002
#define S_FAILED_LIB_ERROR					0x80000003
#define S_FALIED_LIB_LOCK					0x80000004
#define S_FAILED_ALREADY_RUN				0x80000005
#define S_FAILED_LIB_NO_ITEM				0x80000006
#define S_FAILED_RES_NO_ITEM				0x80000007
#define S_FAILED_RES_MORE_DATA				0x80000008
#define S_FAILED_RES_INVALID_PARAM			0x80000009
#define S_FAILED_REMOVE_RES_RESTART			0x8000000a
#define S_FAILED_INVALID_PARAM				0x8000000b
#define S_FAILED_NO_FIND					0x8000000c
#define S_FAILED_REMOVE_RES_KILLER			0x8000000d
#define S_FAILED_SET_PLUG_TRUST				0x8000000e
//////////////////////////////////////////////////////////////////////////

class IEngineCallback
{
public:

	// ɨ�迪ʼ
	VIRTUAL_ENG HRESULT		ScanStart() = 0;

	// ɨ����ɣ�ֻ���յ�����ص���ʱ��ű�ʾɨ�����
	VIRTUAL_ENG HRESULT		ScanComplete(BOOL bCancel) = 0;

	// ��ʼɨ��ĳ�����
	VIRTUAL_ENG HRESULT		ScanItemStart(DWORD nIndex, DWORD nTotal, LPCTSTR lpName) = 0;

	// ɨ�赽��ĳ���������Χ��Ҫ��ID������ȥquery������Ϣ
	VIRTUAL_ENG HRESULT		FindItemExist(DWORD nItemId) = 0;

	// ɨ��ĳ������Ѿ����
	VIRTUAL_ENG HRESULT		ScanItemComplete(DWORD nItem) = 0;

	// ��ɨ��ʼ
	VIRTUAL_ENG HRESULT		QuickScanStart() = 0;

	// ��ɨ���
	VIRTUAL_ENG HRESULT		QuickScanComplete() = 0;

	// ��ʼ����ĳ�����
	VIRTUAL_ENG HRESULT		RemoveItemStart(DWORD nItemId, DWORD nRate) = 0;

	// ����ĳ���������
	VIRTUAL_ENG HRESULT		RemoveItemEnd(DWORD nItemId, HRESULT hRes ) = 0;

	// ������̽���
	VIRTUAL_ENG	HRESULT		RemoveComplete(BOOL bNeedRestart) = 0;
	
	// ������ʱ����Ҫ����
	VIRTUAL_ENG HRESULT		UnkItemChange(DWORD nItemId) = 0;
	VIRTUAL_ENG HRESULT		LibLoadFailed() = 0;
};

struct PLUG_DAT_INFO
{
	DWORD		nItemId;
	DWORD		nLevel;
	LPCTSTR		lpName;
	LPCTSTR		lpCompany;
	LPCTSTR		lpstrBehavior;
	LPCTSTR		lpstrDesc;
};


struct PLUG_SCAN_RESULT 
{
	DWORD		nItemId;		// �����Ψһ��ʾID
	DWORD		nLevel;			// ����ļ���  ����3��ʾΣ��
	BOOL		bActive;		// �Ƿ��Ծ�����ڲ�ʹ��
	BOOL		bUnknownID;		// �Ƿ���δ֪���
	BOOL		bDelRestart;	// �Ƿ�֮ǰ�Ѿ����������Ҫ������ɾ��
	LPCTSTR		lpName;			// �������
	LPCTSTR		lpCompany;		// �����Ʒ��˾
	LPCTSTR		lpstrType;		// ��������
	LPCTSTR		lpFirstFile;	// ɨ���ĵ�һ���ļ�
	LPCTSTR		lpBehavior;		// �����Ϊ
	LPCTSTR		lpKiller;		// �Ƿ���Ҫרɱ��רɱ�����ص�ַ
	DWORD		nFileSize;		// ɨ�����ļ�����
	LPCTSTR*	pFileBuffer;	// ɨ�����ļ�bufferָ��
	DWORD		nRegSize;		// ɨ����ע������
	LPCTSTR*	pRegBuffer;		// ɨ����ע���bufferָ��

	//�ӿ�Ϊ4��ʱ����ӵ�
	BOOL		bTrust;			// �Ƿ������β��
	LPCTSTR		lpCLSID;		// δ֪�����CLSID
};

typedef struct _LogRemovePlug
{
	DWORD		nItemId;
	LPCTSTR		lpstrName;
	LPCTSTR		lpstrTime;
	PVOID		pBuffer;		// ��������������� CString ��ָ��
}LOG_PLUG_REMOVE, *PLOG_PLUG_REMOVE;

class IDelOpCallback
{
public:
	VIRTUAL_ENG BOOL DeleteFile( LPCTSTR lpFileName ) = 0;
	VIRTUAL_ENG BOOL DeleteFolder( LPCTSTR lpDirName ) = 0;
	VIRTUAL_ENG BOOL DeleteKey(HKEY hRoot, LPCTSTR lpKey ) = 0;
	VIRTUAL_ENG BOOL DeleteKeyValue(HKEY hRoot, LPCTSTR lpKey, LPCTSTR lpValue ) = 0;
};

class IPlugEng
{
public:
	//���ûص�����ɨ��Ĺ����н��п��ƺ�״̬����
	VIRTUAL_ENG HRESULT	SetCallBack(IEngineCallback* callback, LPVOID Param) = 0;

	//�����ʹ��Ĭ�ϵĿ⣬����Ҫ����·��
	VIRTUAL_ENG HRESULT	SetLibPath(LPCTSTR lpLibPath=NULL) = 0;	

	//����ɨ���ȡ������������������������е�Scan��Remove����������ͬʱ���ڣ�ֻ��һ��һ����
	VIRTUAL_ENG HRESULT	QuickScan(BOOL bOnlyDanger=FALSE, BOOL bSyn = FALSE) = 0;

	//��ȫɨ�裬���ÿ����ɨ�裬Ȼ����չɨ��ϵͳ���
	VIRTUAL_ENG HRESULT	ScanAll(BOOL bSyn=FALSE) = 0;

	//����ɨ�裬�ṩһ��ID����
	VIRTUAL_ENG HRESULT	ScanArray(DWORD nNumber, DWORD* pIDBuffer,BOOL bSyn=FALSE) = 0;

	//ֹͣɨ�裬�ڻص��л��յ�ֹͣɨ�����Ϣ
	VIRTUAL_ENG HRESULT	StopScan() = 0;

	//���ݲ��ID����ȡ�������ϸ��Ϣ
	VIRTUAL_ENG HRESULT	GetItemInfo(DWORD nItemId, PVOID itemInfo) = 0;

	//��ȡ�Ѱ�װ����ĸ���, ��һ������Ϊ�ܲ���������ڶ���Ϊ�������ĸ���
	VIRTUAL_ENG HRESULT	GetPluginCount(DWORD & dwPlugNumber, DWORD & dwAdwareNumber) = 0;

	//��ȡɨ�����в����Ϣ����0��ʼһֱ���ö��
	VIRTUAL_ENG HRESULT	GetNextPluginInfo(DWORD & dwPos, PLUG_SCAN_RESULT** info ) = 0;

	//���ɨ�赽����Ļ�������ID����ȡ���ļ���ע������ϸ��Ϣ
	VIRTUAL_ENG HRESULT	GetItemScanResultInfo(DWORD nItemid, PLUG_SCAN_RESULT** pItemInfo) = 0;	// �������Ϣ��ɨ��������ϸ��Ϣ

	// �ɻ�ȡ�����õ���ָ����ͷ�
	VIRTUAL_ENG HRESULT FreeItemScanResInfo(PLUG_SCAN_RESULT* itemInfo) = 0;

	//ɾ����������ͬ���������������ڻص���֪ͨɾ�����
	VIRTUAL_ENG HRESULT	Remove(DWORD nItemId, BOOL bSyn=FALSE) = 0;

	//ɾ��һ������nNumber���������pBuffer����ɾ����ItemId����
	VIRTUAL_ENG	HRESULT Remove(DWORD nNumber, DWORD* pBuffer, BOOL bSyn=FALSE) = 0;

	//���ɨ����
	VIRTUAL_ENG HRESULT	ClearResult() = 0;

	//���ò���Ƿ�ȫ/����/һ��	0Ϊȡ�����Σ�1Ϊ��������
	VIRTUAL_ENG HRESULT	SetPluginSafe(DWORD nItemId, BOOL bTrust) = 0;

	//���Ҫ����Ĳ���Ƿ��в���explorer.exe��
	VIRTUAL_ENG HRESULT GetInjectExplorer(DWORD nSize, DWORD* pBuffer, BOOL & bInject) = 0;

	// ����һ��LOG_PLUG_REMOVE��ָ�����飬������Ҫ�ͷ�
	VIRTUAL_ENG HRESULT GetPlugRemoveLog( DWORD & nOutSize, PLOG_PLUG_REMOVE** ppLogArray) = 0;

	// �ͷ�Log����
	VIRTUAL_ENG HRESULT	FreePlugRemoveLog( DWORD nSize, PLOG_PLUG_REMOVE* pLogArray) = 0;

	// ���������־
	VIRTUAL_ENG HRESULT ClearAllLog() = 0;

	// �������������־
	VIRTUAL_ENG HRESULT SetRebootClean(DWORD nNumber, DWORD* pIDBuffer) = 0;

	// ��ȡ��İ汾��
	VIRTUAL_ENG HRESULT	GetDataBaseVersion(DWORD & nVersion) = 0;

	// �ӿ�Ϊ 4 ��ʱ����ӵ� *************************************
	//��ȫɨ�裬ʹ�ÿ����ɨ�������
	VIRTUAL_ENG HRESULT	ScanAllDanger(BOOL bSyn=FALSE) = 0;

	// �ӿ�Ϊ 5 ��ʱ����ӵ� *************************************
	//�����Ƿ�ʹ����չɨ��
	VIRTUAL_ENG HRESULT SetUseExtend(BOOL bUse=FALSE) = 0;

	// �ӿ�Ϊ 6 ��ʱ����ӵ� *************************************
	// ����ʹ���ⲿ��ɾ���ӿ�
	VIRTUAL_ENG HRESULT SetDelOpCallBack(IDelOpCallback* pOpCallback) = 0;

	// �ӿ�Ϊ7 ��ʱ����ӵ� *************************************
	// ��ȡ�Ѿ����ε��б�
	VIRTUAL_ENG HRESULT GetTrustPlugDetailInfo(PLUG_SCAN_RESULT** pInfo, DWORD* pdwSize) = 0;
	VIRTUAL_ENG HRESULT	SetCLSIDNoTrust(LPCTSTR lpCLSID) = 0;
	VIRTUAL_ENG HRESULT	SetReturnTrustScanRes(BOOL bRet) = 0;
	VIRTUAL_ENG HRESULT	LoadLibrary() = 0;//hub
};
struct PLUG_EXTEND_INFO
{
	CSimpleArray<CStringA>	strCLSIDArray;
	CSimpleArray<CStringA>	strRegArray;
	CSimpleArray<CStringA>	strFileArray;
	CSimpleArray<CStringA>	strDirArray;
};

class ICheckInterface
{
public:
	VIRTUAL_ENG HRESULT	Init() = 0;
	VIRTUAL_ENG HRESULT	GetInfoByCLSID( LPCTSTR lpCLSID, PLUG_DAT_INFO* pPlugInfo ) = 0;
	VIRTUAL_ENG	HRESULT	GetInfoByFilePath( LPCTSTR lpFilePath, PLUG_DAT_INFO* pPlugInfo ) = 0;
	VIRTUAL_ENG HRESULT	GetInfoByRegKey( HKEY hRoot, LPCTSTR lpKey, PLUG_DAT_INFO* pPlugInfo  ) = 0;
	VIRTUAL_ENG HRESULT	GetInfoByRegValue( HKEY hRoot, LPCTSTR lpKey, LPCTSTR lpValue, PLUG_DAT_INFO* pPlugInfo ) = 0;
	VIRTUAL_ENG HRESULT	ForceUnLoadRule() = 0;
	VIRTUAL_ENG HRESULT InitExt() = 0;
	VIRTUAL_ENG HRESULT GetExtendInfo(PLUG_EXTEND_INFO** ppInfo) = 0;
	VIRTUAL_ENG HRESULT FreeExtendInfo(PLUG_EXTEND_INFO* pInfo) = 0;
};


typedef IPlugEng* (WINAPI *PFNGetEngine)(DWORD );
typedef VOID (WINAPI *PFNFreeEngine)(IPlugEng* );

typedef ICheckInterface* (WINAPI *PFNGetCheckEngine)(DWORD);
typedef VOID (WINAPI *PFNFreeCheckEngine)(ICheckInterface* );


#define XX_PLUG_ENGINE_DLL_NAME _T("kplugeng.dll")
#define XX_PLUG_ENG_GET_STR			"f"
#define XX_PLUG_ENG_FREE_STR		"b"
#define XX_PLUG_ENG_REBOOTCLEAN		"c"
#define XX_PLUG_ENG_GET_CHECK_STR	"g"
#define XX_PLUG_ENG_FREE_CHECK_STR	"e"


class CPluginLoader
{
public:
// 	CPluginLoader(void)
// 	{
// 		m_hModDLL	= NULL;
// 		pfnGet		= NULL;
// 		pfnFree		= NULL;
//         pfnGetCheck = NULL;
//         pfnFreeCheck = NULL;
// 
// 		m_hModDLL	= ::LoadLibrary(XX_PLUG_ENGINE_DLL_NAME);
// 		if ( m_hModDLL != NULL )
// 		{
// 			pfnGet  = (PFNGetEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_GET_STR);
// 			pfnFree = (PFNFreeEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_FREE_STR);
// 
// 			pfnGetCheck  = (PFNGetCheckEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_GET_CHECK_STR);
// 			pfnFreeCheck = (PFNFreeCheckEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_FREE_CHECK_STR);
// 		}
// 		LoadEng(XX_PLUG_ENGINE_DLL_NAME);
// 	}

	CPluginLoader(CString strAppPath = L"")
	{
		m_hModDLL	= NULL;
		pfnGet		= NULL;
		pfnFree		= NULL;
		pfnGetCheck = NULL;
		pfnFreeCheck = NULL;
		m_pPlugEng   = NULL;
		CString strDllPath = strAppPath;

		if (TRUE == strAppPath.IsEmpty())
		{
			strDllPath = XX_PLUG_ENGINE_DLL_NAME;
		}
		else
		{
			strDllPath.Append(L"\\");
			strDllPath.Append(XX_PLUG_ENGINE_DLL_NAME);
		}

		LoadEng(strDllPath);
// 		m_hModDLL	= ::LoadLibrary(strAppPath);
// 		if ( m_hModDLL != NULL )
// 		{
// 			pfnGet  = (PFNGetEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_GET_STR);
// 			pfnFree = (PFNFreeEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_FREE_STR);
// 
// 			pfnGetCheck  = (PFNGetCheckEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_GET_CHECK_STR);
// 			pfnFreeCheck = (PFNFreeCheckEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_FREE_CHECK_STR);
// 		}
	}

	~CPluginLoader(void)
	{
		if ( m_hModDLL != NULL )
		{
			::FreeLibrary(m_hModDLL);
			m_hModDLL = NULL;
		}
	}

	void LoadEng(CString strDll)
	{
		m_hModDLL	= ::LoadLibrary(strDll);
		if ( m_hModDLL != NULL )
		{
			pfnGet  = (PFNGetEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_GET_STR);
			pfnFree = (PFNFreeEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_FREE_STR);

			pfnGetCheck  = (PFNGetCheckEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_GET_CHECK_STR);
			pfnFreeCheck = (PFNFreeCheckEngine)::GetProcAddress( m_hModDLL, XX_PLUG_ENG_FREE_CHECK_STR);
		}

	}

	IPlugEng* GetPlugEngine()
	{
// 		if ( pfnGet != NULL )
// 			return pfnGet(VERSION_PLUG_INTERFACE_HIGH);
// 
// 		return NULL;
		if (m_pPlugEng == NULL)
		{
			if ( pfnGet != NULL )
				m_pPlugEng = pfnGet(VERSION_PLUG_INTERFACE_HIGH);
		}		
		return m_pPlugEng;
	}
	
	VOID FreePlugEngine(IPlugEng* pEng)
	{
		if ( pfnFree != NULL )
		{
			pfnFree(pEng);
			m_pPlugEng = NULL;
		}
	}

	ICheckInterface* GetCheckInterface()
	{
		if ( pfnGetCheck != NULL )
			return pfnGetCheck(VERSION_PLUG_INTERFACE_HIGH);

		return NULL;
	}
	VOID FreeCheckInterface(ICheckInterface* p)
	{
		if ( pfnFreeCheck )
			pfnFreeCheck(p);
	}

protected:
	HMODULE				m_hModDLL;
	PFNGetEngine		pfnGet;
	PFNFreeEngine		pfnFree;
	PFNFreeCheckEngine	pfnFreeCheck;
	PFNGetCheckEngine	pfnGetCheck;
	IPlugEng*			m_pPlugEng;//hub
};

class CPlugNullCallback : public IEngineCallback
{
public:
	CPlugNullCallback(){}
	~CPlugNullCallback(){}

public:
	virtual HRESULT		ScanStart(){return S_OK;}
	virtual HRESULT		ScanComplete(BOOL bCancel){return S_OK;}
	virtual HRESULT		ScanItemStart(DWORD nIndex, DWORD nTotal, LPCTSTR lpName){return S_OK;}
	virtual HRESULT		FindItemExist(DWORD nItemId){return S_OK;}
	virtual HRESULT		ScanItemComplete(DWORD nItem){return S_OK;}
	virtual HRESULT		UnkItemChange(DWORD nItemId){return S_OK;}

	virtual HRESULT		QuickScanStart(){return S_OK;}
	virtual HRESULT		QuickScanComplete(){return S_OK;}

	virtual HRESULT		RemoveItemStart(DWORD nItemId, DWORD nRate){return S_OK;}
	virtual HRESULT		RemoveItemEnd(DWORD nItemId, HRESULT hRes ){return S_OK;}
	virtual HRESULT		RemoveComplete(BOOL bNeedRestart){return S_OK;}
	virtual HRESULT		LibLoadFailed(){return S_OK;}
};

// inline CPluginLoader* GlobalGetPluginLoader()
// {	
// 	static CPluginLoader loader;
// 	return &loader;
// }

inline CPluginLoader* GlobalGetPluginLoader(CString strAppPath = L"")
{	
	static CPluginLoader loader(strAppPath);
	return &loader;
}

#ifdef __ATLSIMPCOLL_H__
class CDWORDBuffer
{
public:
	CDWORDBuffer(CSimpleArray<DWORD>& arr)
	{
		nSize	= 0;
		pBuffer	= NULL;

		if (arr.GetSize() > 0 )
		{
			pBuffer = new DWORD[arr.GetSize()];
			nSize	= arr.GetSize();
			for ( int i = 0; i < arr.GetSize(); i++)
			{
				pBuffer[i] = arr[i];
			}
		}
	}

	~CDWORDBuffer()
	{
		if ( pBuffer )
		{
			delete pBuffer;
			pBuffer = NULL;
		}
	}

	DWORD*	GetBuffer()
	{
		return pBuffer;
	}
	DWORD GetSize()
	{
		return nSize;
	}

protected:
	DWORD	nSize;
	DWORD*	pBuffer;
};
#endif