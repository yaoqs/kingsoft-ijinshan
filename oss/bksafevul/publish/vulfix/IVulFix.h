#pragma once
#include "vulfixspecifics.h"
typedef CSimpleArray<int> IntArray;
struct TUpdateItem;
typedef TUpdateItem *LPTUpdateItem;

struct TUpdateItemDetail
{
	TUpdateItemDetail() : nPatchSize(0)
	{
        bCheckCert = TRUE;
	}
	
	CString strWebPage;	// 
	CString strDownurl;	// �������� : ����&Ӣ�� 
	CString strInstallParam;// ��װ����: 
	CString strMD5;		//��������MD5
	int	nPatchSize;			//���İ油�����Ĵ�С
	CString strMirrorurl;	// ������������ : ����&Ӣ�� 
    BOOL    bCheckCert;
};

// ���صȼ� 
// ���صȼ�, 1-5 : rating_map = {'���ڵ�':'-1', ��ѡ':'0', '��':'1', '�е�':'2', '��Ҫ':'3', '����':'4'} 
enum E_WarnLevel	
{
	EWarn_Superseded = -1,
	EWarn_Option = 0,
	EWarn_Low,
	EWarn_Midium,
	EWarn_Important,
	EWarn_Serious,
	EWarn_Fatal,
};

enum E_InstalledResult
{
	EINST_SUCCESS = 0,				// ����ֵ�ܶ� 
	EINST_SUCCESS_CHECKED,			// ��ע��������ҵ�����Ӧ��
	EINST_SUCCESS_CHECK_FAILED,		// ���ܰ�װ�ɹ���, �����ʱ��û�鵽	
	EINST_FAIL,						// ��װʧ�� : ���ݷ���ֵ, ��ȫʧ�� 
	EINST_FAIL_EXECUTE,				// ����ʧ��, �����ļ����������� 
	EINST_FAIL_REQUIRE_REBOOT,		// ��Ҫ���� 
	EINST_FAIL_NOT_APPLICABLE,		// ��ȫʧ�� : ����WIN7 ��exit code 
	EINST_FAIL_HIJACKED,			// ��360 ������
	EINST_FAIL_FILEBUSY,			// User Patcher ��ʱ��, �ļ�æ 
};

struct T_UserPatchInfo
{
	struct PatchFileInfo
	{
		CString strFilenameFrom, strFilenameTo;
	};

	INT nKBID;
	CString strName;
	CString strProductKey, strPatchKey, strPatchValue;
	CSimpleArray<PatchFileInfo> files;

	void AddPatch(LPCTSTR sfrom, LPCTSTR sto)
	{
		PatchFileInfo pi;
		pi.strFilenameFrom = sfrom;
		pi.strFilenameTo = sto;
		files.Add( pi );
	}
};

enum E_VFlags
{
	VFLAG_NULL				= 0,
	VFLAG_SERVICE_PATCH		= 1, 
	VFLAG_IGNORE_INSTALLED	= 2,
};

inline BOOL IsFlagOn( E_VFlags flag, DWORD dwFlags )
{
	return ( ( flag & dwFlags ) == flag );
}

inline void SetFlagOn( E_VFlags flag, DWORD &dwFlags )
{
	dwFlags |= flag;
}

struct TUpdateItem
{
	TUpdateItem() : nID(-1), nWarnLevel(0), isExclusive(0), m_nType(0), dwVFlags(0)
		, bUserPatcher(FALSE), isIgnored(FALSE), isInstalled(FALSE), isExpired(FALSE)
	{
	}
	
	int		nID;			// 
	CString strMsid;			// �����
	CString strName;			// ©������
	int		nWarnLevel;			// E_WarnLevel, -1 ��ʾ����
	CString strPubdate;			// ����ʱ��
	CString strDescription;		// ժҪ

	CString strWebpage;			// ������ַ

	CString strInstallparam;	// ��װ����
	int	isExclusive;			// �Ƿ������װ
	DWORD dwVFlags;				// ������  
	
	TUpdateItemDetail detail;	// ���ص���ϸ��Ϣ

	CString strAffects;			// Ӱ��
	CString strSuggestion;		// ����
	BOOL bUserPatcher;			// �Ƿ�ʹ���Զ���Patcher 	
	CString strCondition;		// �������, ���Ժ���Office ��� 

	// RUNTIME 
	int		m_nType;			// ����������, sys, office 
	CString m_strFilePath;		// �����ļ�, ������ڵĻ� 
	
	BOOL isIgnored;			// �Ƿ����
	BOOL isInstalled;		// check result 
	BOOL isExpired;			// 
};

struct TItemFixed
{
	TItemFixed() : nID(0), fromDB(FALSE)
	{}
	TItemFixed(const TItemFixed& v)
		: nID(v.nID),  fromDB(FALSE)
	{
		strName = v.strName;
		strWebPage = v.strWebPage;
		strInstallDate = v.strInstallDate;
	}
	
	INT nID;
	CString strName;
	CString strWebPage;
	CString strInstallDate;
	BOOL fromDB;
};

struct TReplacedUpdate{
	int nKBID, nKBID2;
	CString strPubdate;
};

struct TOptionCondition 
{
	int nWinVer, nWinSP;	
	int nIEVer, nIESP;	

	int nJS;
	int nMediaplayer;	
	int nDX;			
	int nOE;
	int nDataAccess;
	int nFramework;
	int nXML;
	int nMSN;
	
	CString strOffice;			//office �İ汾
	CString m_strCondition;		// ���� 
	CString m_strExpInstalled;	// 
};

enum T_SoftVulActionType
{
	SOFTACTION_NONE,		// �޲���
	SOFTACTION_UPDATE,		// ����������
	SOFTACTION_PATCH,		// ����patch
	SOFTACTION_DISABLECOM,	// ����COM 
};

enum T_SoftComState
{
	COM_NOT_DISABLED,
	COM_PART_DISABLED,
	COM_ALL_DISABLED,
};

union T_VulState
{
	int nstate;
	struct 
	{
		char action;	// T_SoftVulActionType
		bool bMatched;	// clsid �Ƿ���������
		bool bFounded;	// clsid �Ƿ���ע������ҵ�
		char comState;	// T_SoftComState com ״̬
	};
};

struct TVulSoftSubitem
{
	CString  strName;			//����
	CString  strWebpage;		//�������
	CString  strDownpage;		//����ҳ��
	CString  strDownUrl;		//����URL	
	int nAction;				//�������ͱ�ʾ�ǣ��������°汾�������عٷ�����,������COM ����
	int nSize;					//�����С
	
	TOptionCondition conditon;			//
};

struct TVulSoft
{
	int	nID;
	CString strName;			//©������
	CString strPubdate;			//��������
	CString strOrigUrl;			// ©����ԴURL
	CString strAffects;		//����©���汾
	CString	strDescription;			// �������
	CString strDetailDescription;	// ��ϸ����
	CString	strSideaffect;
	int nLevel;				//�ȼ�
	int nDisableCom;		//�Ƿ����COM
	
	CSimpleArray<CString> arrCLSID;			//CLSID�б�  CLSID|VFrom|VTo|
	TVulSoftSubitem matchedItem;				// Detail subitem 
	
	// 
	T_VulState state;
	
	int isIgnored:1;			// �Ƿ����
	int isToFix:1;				// �Ƿ�װ
	int isInstalled:8;			// ��װ�Ƿ�ɹ�: 0 δ��װ, 1 ��װ�ɹ�, -1 ��װʧ�� 
};

typedef TVulSoftSubitem* LPTVulSoftSubitem;
typedef TVulSoft* LPTVulSoft;

enum VulType
{
	VTYPE_IGNORED = -1,		//���Ե� 
	VTYPE_UNKOWN = 0,		
	VTYPE_OFFICE,		
	VTYPE_WINDOWS,		
	VTYPE_SOFTLEAK,		
};

enum TVulFixEventType {
	
	EVulfix_Error,				// ����				
	EVulfix_ScanBegin,			// Scan ��ʼ		0, Num 
	EVulfix_ScanProgress,		// Scan ����		0, nCurrentItem 

	EVulfix_DownloadBegin,		// ���ؿ�ʼ			id  currentnum,	totalnum  
	EVulfix_DownloadProcess,	// ���ؽ���			id, downloadedsize, fullsize
	EVulfix_DownloadEnd,		// ���ؽ���			id, currentnum, down.result
	EVulfix_DownloadError,		// ����ʧ��			id, currentnum, 
	
	EVulfix_InstallBegin,		// ��װ��ʼ			id, currentnum,	totalnum 
	EVulfix_InstallBeginUser,	// �Զ��尲װ��ʼ	
	EVulfix_InstallEnd,			// ��װ����			id, currentnum, install.result 
	EVulfix_InstallError,		// ��װʧ��			id, currentnum 

	EVulfix_Task_Complete,		// ������ȫ��� 
	EVulfix_Task_Error,			// �����д�, ���ܲ������ 

    EVulfix_Download_Check_Error,// ���������Ĳ�������ǩ��У��ʧ��
};

class IVulfixObserver
{
public:
	virtual void OnVulfixEvent(TVulFixEventType evt, int nKbId, DWORD dwParam1, DWORD dwParam2) = 0;
};


// Scan flags 
#define VULSCAN_USE_IUPDATE			1	// Use iupdate for vista, win7
#define VULSCAN_EXPRESS_SCAN		2	// Express Scan, ɨ�赽һ����Σ©�����˳�!! 

class IVulIgnore
{
public:
	virtual ~IVulIgnore() {} 
	virtual HRESULT LoadIgnoreDB() = 0;
	virtual HRESULT SaveIgnoreDB() = 0;					// �������©�����ļ� 
	virtual HRESULT Ignore(int nKBID, BOOL bIgnore) = 0;// ����©��
	virtual HRESULT AutoIgnore(int nKBID, BOOL bIgnored) = 0; // �ṩ�������޸� 
	virtual int IsIgnored(int nKBID) = 0;		// �Ƿ񱻺����� 1:�û����� 2:ϵͳ���� 
};

// ϵͳ & office ©��ɨ�� 
class IVulfix
{
public:
	virtual ~IVulfix() {} 
	
	virtual void SetObserver(IVulfixObserver *pObserver) = 0;

	virtual HRESULT Scan(DWORD dwFlags=0)=0;	// ɨ��
	virtual HRESULT Cancel() = 0;
	
	virtual const CSimpleArray<LPTUpdateItem>& GetResults() = 0;
	virtual const CSimpleArray<LPTVulSoft>& GetSoftVuls() = 0;

	virtual const CSimpleArray<TItemFixed*>& GetFixedVuls() = 0;
	virtual const CSimpleArray<LPTUpdateItem>& GetIgnoredVuls() = 0;
	virtual const CSimpleArray<LPTUpdateItem>& GetInvalidVuls() = 0;
	virtual const CSimpleArray<TReplacedUpdate*>& GetReplacedVuls() = 0;
	
	
	virtual BOOL Ignore(int nKBID, BOOL bIgnore)=0;		// ����©��
	virtual BOOL PersistIgnored()=0;					// �������©�����ļ� 
	
	virtual HRESULT EnableVulCOM(int nId, BOOL bEnable=FALSE) = 0; // ����COM 

	virtual BOOL GetLatestPackgeDate(INT &nYear, INT &nMonth, INT &nDay) = 0;
	virtual BOOL GetLatestInstalledKBDate(FILETIME &latestInstallTime) = 0;
	// Interface for Vista quick scan by date 
	// -1 for db<os.fix	 0 for db==os.fix  1 for db>os.fix, need to repaire
	virtual INT ExpressScanSystem() = 0; 
};


#define VULFLAG_REPAIR_IMPORT_LOCAL				1
#define VULFLAG_REPAIR_DOWNLOAD_IF_FAIL_IMPORT	2
class IRepairVul 
{
public:
	virtual ~IRepairVul() {} 

	virtual HRESULT Reset() = 0;
	virtual HRESULT SetObserver(IVulfixObserver *pObserver) = 0;

	virtual HRESULT AddVul(IVulfix *pVulfix, const IntArray&arrayId) = 0;
	virtual HRESULT AddSoftVul(IVulfix *pSoftVulfix, const IntArray&arrayId) = 0;

	virtual HRESULT Repair(LPCTSTR sDownloadPath, LPCTSTR szImportPath, DWORD dwFlags) = 0;
	virtual HRESULT StopRepair() = 0;
	virtual HRESULT WaitForRepairDone() = 0;
	virtual HRESULT GetItemFilePath(INT nID, BSTR *bstr) = 0;
};

BOOL RequireUsingInterface();