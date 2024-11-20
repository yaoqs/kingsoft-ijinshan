#pragma once

#include "ksaferunstrdefine.h"

#define VERSION_KSAFE_RUNOPT_INTERFACE		6
#define STR_KSAFE_RUN_OPTIMIZE_DAT			_T("\\runopt.dat")


#define KSRUN_TYPE_STARTUP	1
#define KSRUN_TYPE_SERVICE	2
#define KSRUN_TYPE_TASK		3
#define KSRUN_TYPE_ALL		-1

#define KSRUN_TYPE_NONSYSTEM	0x10
#define KSRUN_TYPE_SYSTEM		0x20

#define REG_RUN_TYPE_WINDOW_HKLM		1
#define REG_RUN_TYPE_WINDOW_HKCU		2
#define REG_RUN_TYPE_KSAFE_HKLM			3
#define REG_RUN_TYPE_KSAFE_HKCU			4
#define REG_RUN_TYPE_3XX_HKLM			5
#define REG_RUN_TYPE_3XX_HKCU			6

#define DIR_RUN_TYPE_BEGIN				100
#define DIR_RUN_TYPE_WINDOW_COMM		101
#define DIR_RUN_TYPE_WINDOW_USER		102
#define DIR_RUN_TYPE_KSAFE_COMM			103
#define DIR_RUN_TYPE_KSAFE_USER			104
#define DIR_RUN_TYPE_3XX_COMM			105
#define DIR_RUN_TYPE_3XX_USER			106

inline BOOL IsTypeRunEnable(DWORD nType)
{
	return (nType==REG_RUN_TYPE_WINDOW_HKLM||
		nType==REG_RUN_TYPE_WINDOW_HKCU||
		nType==DIR_RUN_TYPE_WINDOW_COMM||
		nType==DIR_RUN_TYPE_WINDOW_USER);
}

inline BOOL IsTypeRunReg(DWORD nType)
{
	return (nType<DIR_RUN_TYPE_BEGIN);
}

inline BOOL IsTypeRunDir(DWORD nType)
{
	return (nType>DIR_RUN_TYPE_BEGIN);
}

inline BOOL IsHKLMRunType(DWORD nType)
{
	return (nType==REG_RUN_TYPE_WINDOW_HKLM || nType==REG_RUN_TYPE_KSAFE_HKLM);
}

inline BOOL IsSameRunType(DWORD nType, DWORD nTypeX)
{
	if (nTypeX==nType)
		return TRUE;

	if (nType==REG_RUN_TYPE_WINDOW_HKLM && nTypeX==REG_RUN_TYPE_KSAFE_HKLM )
		return TRUE;

	if (nType==REG_RUN_TYPE_WINDOW_HKCU && nTypeX==REG_RUN_TYPE_KSAFE_HKCU )
		return TRUE;

	if (nTypeX==REG_RUN_TYPE_WINDOW_HKLM && nType==REG_RUN_TYPE_KSAFE_HKLM )
		return TRUE;

	if (nTypeX==REG_RUN_TYPE_WINDOW_HKCU && nType==REG_RUN_TYPE_KSAFE_HKCU )
		return TRUE;

	//////////////////////////////////////////////////////////////////////////
	if (nType==DIR_RUN_TYPE_WINDOW_COMM && nTypeX==DIR_RUN_TYPE_KSAFE_COMM )
		return TRUE;

	if (nType==DIR_RUN_TYPE_WINDOW_USER && nTypeX==DIR_RUN_TYPE_KSAFE_USER )
		return TRUE;

	if (nTypeX==DIR_RUN_TYPE_WINDOW_COMM && nType==DIR_RUN_TYPE_KSAFE_COMM )
		return TRUE;

	if (nTypeX==DIR_RUN_TYPE_WINDOW_USER && nType==DIR_RUN_TYPE_KSAFE_USER )
		return TRUE;

	return FALSE;
}


inline CString GetFileName(LPCTSTR lpFullPath)
{
	if ( NULL == lpFullPath )
		return L"";

	LPCTSTR lpstr = _tcsrchr(lpFullPath,_T('\\'));

	if (lpstr==NULL)
		return CString(lpFullPath);
	else
		return CString(lpstr+1);
}

//NoAutoDisable
//StopIt

class CKsafeRunInfo
{
public:
	CKsafeRunInfo()
	{	
		nID		= 0;
		bEnable = FALSE;
		nType	= 0;
		nAdvice	= 4;
		bSystem = FALSE;
		bNoDealyShow = FALSE;
		nRegType= 0;
		bUnknown= TRUE;
		bDisabledBy3xx = FALSE;
		bFileIsExist = TRUE;
		bHasIgnored = FALSE;
		bShowRemain = TRUE;
	}
	~CKsafeRunInfo(){}

	BOOL IsAdviseStop()
	{
		return (nAdvice==0);
	}

	BOOL IsDisabledBy3XX()
	{
		return bDisabledBy3xx;
	}

	LPCTSTR GetAdviceStr()
	{
		LPCTSTR	lpstr = _T("���޽���");
		switch (nAdvice)
		{
		case 0:
			lpstr = _T("���Խ�ֹ");
			break;
		case 1:
			lpstr = _T("��������");
			break;
		case 2:
			lpstr = _T("��������");
			break;
		case 3:
			lpstr = _T("��������");
			break;
		case 4:
			lpstr = _T("ά����״");
			break;
		default:
			break;
		}
		if (!bFileIsExist)
			lpstr = _T("����ɾ��");
		return lpstr;
	}

public:
	DWORD		nID;
	DWORD		nType;			
	DWORD		nAdvice;	
	BOOL		bEnable;
	BOOL		bNoDealyShow;	
	BOOL		bUnknown;
	BOOL		bSystem;
	BOOL		bDisabledBy3xx;
	BOOL		bFileIsExist;
	BOOL		bHasIgnored;
	BOOL		bShowRemain;
	DWORD		nRegType;
	DWORD		nJobType;
	CString		strName;			
	CString		strDesc;		
	CString		strPath;		//�������ȫ·��
	CString		strExePath;		//������lnkָ���ļ���ȫ·��
	CString		strValue;		//run���ע���ֵ
	CString		strParam;		
	CString		strDisplay;		//��ʾ������
	CString		strWarning;		//��ֹ�ľ���
};

class IEnumRunCallBack
{
public:
	virtual BOOL FindRunItem(CKsafeRunInfo* pInfo) = 0;
	virtual void BeginScan(DWORD nType) = 0;
	virtual void EndScan() = 0;
	virtual void RestoreEnd() = 0;
	virtual void PostRestoreRunItem(DWORD nType,BOOL bEnable,LPCTSTR lpName) = 0;
};

class IEnumRunCallBackNull : public IEnumRunCallBack
{
	virtual BOOL FindRunItem(CKsafeRunInfo* pInfo)=0;
	virtual void BeginScan(DWORD nType){return;}
	virtual void EndScan(){return;}
	virtual void RestoreEnd(){return;}
	virtual void PostRestoreRunItem(DWORD nType,BOOL bEnable,LPCTSTR lpName){return;}
};

class IRunDatQueryEng
{
public:
	virtual BOOL GetInfoByPathValue(DWORD nType, LPCTSTR lpPath, LPCTSTR lpFullPath, KSRunInfo** ppInfo) = 0;
	virtual VOID DeleteInfo(KSRunInfo* pInfo) = 0;
};

class IRunOptimizeEng
{
public:
	virtual VOID EnumRunInfo(DWORD dwFlags,IEnumRunCallBack* pCallback )=0;
	virtual BOOL ControlRun(BOOL bEnable, CKsafeRunInfo* pInfo) = 0;
	virtual VOID RestoreRun(DWORD nType,IEnumRunCallBack* pCallback) = 0;
	virtual BOOL DeleteRun(CKsafeRunInfo* pInfo) = 0;
	virtual DWORD GetRunCount(DWORD nFlags) = 0;
	virtual VOID EnumRunInfoForExam(DWORD dwFlags,IEnumRunCallBack* pCallback )=0;
};

typedef IRunOptimizeEng* (WINAPI *PFNGetRunOptEng)(DWORD);
typedef VOID (WINAPI *PFNFreeRunOptEng)(IRunOptimizeEng* );

typedef IRunDatQueryEng* (WINAPI *PFNGetQueryEng)(DWORD);
typedef VOID (WINAPI *PFNFreeQueryEng)(IRunDatQueryEng* );

typedef VOID (WINAPI *PFNStatitics)();

#define STR_RUNOPT_DLL_NAME _T("krunopt.dll")
#define STR_RUNOPT_GET_ENG	("a")
#define STR_RUNOPT_DEL_ENG	("b")
#define STR_RUNOPT_GET_QENG	("c")
#define STR_RUNOPT_DEL_QENG	("d")

#define STR_RUNOPT_STATITICS ("e")
#define STR_RUNOPT_STATITICS2 ("f")


class CRunOptLoader
{
public:
	CRunOptLoader(CString strAppPath = L"")
	{
		m_hModDLL	= NULL;
		pfnGet		= NULL;
		pfnFree		= NULL;
		pfnGetQEng	= NULL;
		pfnFreeQEng = NULL;

		CString strDllPath = strAppPath;
		if (TRUE == strDllPath.IsEmpty())
		{
			strDllPath = STR_RUNOPT_DLL_NAME;
		}
		else
		{
			strDllPath.Append(L"\\");
			strDllPath.Append(STR_RUNOPT_DLL_NAME);
		}

		m_hModDLL	= ::LoadLibrary(strDllPath);
		if ( m_hModDLL != NULL )
		{
			pfnGet  = (PFNGetRunOptEng)::GetProcAddress( m_hModDLL, STR_RUNOPT_GET_ENG);
			pfnFree = (PFNFreeRunOptEng)::GetProcAddress( m_hModDLL, STR_RUNOPT_DEL_ENG);
			pfnGetQEng  = (PFNGetQueryEng)::GetProcAddress( m_hModDLL, STR_RUNOPT_GET_QENG);
			pfnFreeQEng = (PFNFreeQueryEng)::GetProcAddress( m_hModDLL, STR_RUNOPT_DEL_QENG);
			pfnStatics	= (PFNStatitics)::GetProcAddress(m_hModDLL,STR_RUNOPT_STATITICS2);
		}
	}
	virtual ~CRunOptLoader()
	{
		if ( m_hModDLL != NULL )
		{
			::FreeLibrary(m_hModDLL);
			m_hModDLL = NULL;
		}
	}

	static CRunOptLoader* GetGlobalPtr(CString strAppPath = L"")
	{
		static CRunOptLoader loader(strAppPath);
		return &loader;
	}

	IRunOptimizeEng* GetOptEng()
	{
		if ( pfnGet != NULL )
			return pfnGet(VERSION_KSAFE_RUNOPT_INTERFACE);

		return NULL;	
	}

	VOID FreeOptEng(IRunOptimizeEng* pEng)
	{
		if ( pfnFree != NULL )
			pfnFree(pEng);
	}


	IRunDatQueryEng* GetQueryEng()
	{
		if ( pfnGetQEng != NULL )
			return pfnGetQEng(VERSION_KSAFE_RUNOPT_INTERFACE);

		return NULL;	
	}

	VOID FreeQueryEng(IRunDatQueryEng* pEng)
	{
		if ( pfnFreeQEng != NULL )
			pfnFreeQEng(pEng);
	}

	VOID Statitics()
	{
		if ( pfnStatics != NULL )
			pfnStatics();
	}

protected:
	HMODULE				m_hModDLL;
	PFNGetRunOptEng		pfnGet;
	PFNFreeRunOptEng	pfnFree;

	PFNGetQueryEng		pfnGetQEng;
	PFNFreeQueryEng		pfnFreeQEng;
	PFNStatitics		pfnStatics;
};

