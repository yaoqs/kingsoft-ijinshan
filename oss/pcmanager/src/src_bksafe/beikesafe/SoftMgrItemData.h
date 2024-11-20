#ifndef _SOFTMGR_ITEM_DATA_H_
#define _SOFTMGR_ITEM_DATA_H_
#include <vector>
#include <algorithm>
#include <skylark2/midgenerator.h>

enum SOFT_TYPE
{
	ST_INVALID = -1, ST_IGNORE, ST_FREE, ST_BETA, ST_PAY,
};

enum UPDATE_SOFT_CHECK_TYPE
{
	USCT_INVALID = -1, USCT_ALL, USCT_FREE, USCT_BETA, USCT_PAY
};

// �������
enum SoftAttri : ULONG
{
	SA_None				= (0<<0),
	SA_Beta				= (1<<0),
	SA_Green			= (1<<1),
	SA_Major			= (1<<2),
	SA_New				= (1<<3),
};

class CSoftListItemData
{
public:
	CSoftListItemData()
	{
		m_bIgnore = FALSE;
		m_bDaquan = FALSE;
		m_bChangeIcon = FALSE;
		m_attri = SA_None;
		m_bCancel = FALSE;
		m_bCheck = FALSE;
		m_bCharge = FALSE;
		m_bPlug = FALSE;
		m_bGreen = FALSE;
		m_bSetup = FALSE;
		m_bUpdate = FALSE;
		m_bDownLoad = FALSE;
		m_bDownloading = FALSE;
		m_bContinue = FALSE;
		m_bPause = FALSE;
		m_bLinking = FALSE;
		m_bIcon = FALSE;
		m_bFailed = FALSE;
		m_bLinkFailed = FALSE;
		m_bInstalling = FALSE;
		m_bUninstalling = FALSE;
		m_bWaitInstall = FALSE;
		m_bWaitUninstall = FALSE;
		m_bWaitDownload = FALSE;
		m_bBatchDown = FALSE;
		m_nURLCount = 0;
		m_dwSize = 0;
		m_fMark = 0.0;
		m_llDownloadTime = 0;

		m_nCount = 0;
		m_dwProgress = 0;
		m_dwID = -1;
		m_dwIDUpdate = -1;
		m_pImage = NULL;
		m_dwTime = 0;
		m_fSpeed = 0.0;
		m_dwStartTime = 0;
		m_rcName = CRect(0,0,0,0);
		m_dwFlags = 0;
		m_bUsingForOneKey = FALSE;
	}

#define STR_NEW_DETAIL_URL			L"http://baike.ijinshan.com/ksafe/client/v1_0/%s.html?mid=%s"

	CString GetInfoUrl()
	{
		CString		str;

		if (!m_strSoftID.IsEmpty())
		{
			CString     strMid;
			Skylark::CMidGenerator::Instance().GetMid( strMid );

			str.Format(STR_NEW_DETAIL_URL,m_strSoftID, strMid);
		}

		return str;
	}

public:
	BOOL m_bCheck;				//�Ƿ�ѡ��
	BOOL m_bCharge;				//�Ƿ��շ�
	BOOL m_bPlug;				//�Ƿ��в��
	BOOL m_bGreen;				//�Ƿ���ɫ
	ULONG m_attri;				//�������
	BOOL m_bSetup;				//�Ƿ�װ
	BOOL m_bUpdate;				//�Ƿ�����
	BOOL m_bDownloading;		//�Ƿ���������
	BOOL m_bDownLoad;			//�Ƿ��Ѿ�����
	BOOL m_bContinue;			//�Ƿ����
	BOOL m_bPause;				//�Ƿ���ͣ
	BOOL m_bLinking;			//�������ӷ�����
	BOOL m_bIcon;				//�Ƿ�load��ȷ��icon
	BOOL m_bFailed;				//����ʧ��
	BOOL m_bLinkFailed;			//����ʧ��
	BOOL m_bInstalling;			//���ڰ�װ
	BOOL m_bUninstalling;		//����ж��
	BOOL m_bWaitUninstall;		//�ȴ�ж��
	BOOL m_bWaitInstall;		//���ڰ�װ
	BOOL m_bWaitDownload;		//�ȴ�����
	BOOL m_bBatchDown;			//�Ƿ���������
	BOOL m_bCancel;				//�Ƿ�ȡ��
	BOOL m_bChangeIcon;			//��Ҫ�滻ͼƬ
	BOOL m_bDaquan;				//�Ƿ��Ǵ�ȫ���õİ�װ
	BOOL m_bIgnore;				//�Ƿ���������

	CString m_strPath;			//����Ŀ¼
	CString m_strName;			//�������
	CString m_strDescription;	//�������
	CString m_strPublished;		//����ʱ��
	CString m_strURL;			//����ҳ��ַ
	CString m_strDownURL;		//���ص�ַ
	CString m_strSpeed;			//�����ٶ�
	CString m_strVersion;		//�汾��Ϣ
	CString m_strNewVersion;	//���°汾
	CString m_strOSName;		//�ʺϲ���ϵͳ
	CString m_strIconURL;		//���ͼ�����ص�ַ
	CString m_strFileName;		//�����ļ���
	CString m_strMD5;			//MD5ֵ
	CString m_strType;			//�������
	CString m_strTypeShort;		//�������
	CString m_strTypeID;		//�������ID
	CString m_strSize;			//�����С
	CString m_strSoftID;		//���ID
	CString m_strOrder;			//�ȶ�
	CString m_strMainExe;		//�����������
	float m_fSpeed;				//�����ٶ�
	DWORD m_dwTime;				//�������õ�ʱ��
	DWORD m_dwProgress;			//���ؽ���
	DWORD m_dwStartTime;		//�տ�ʼ����ʱ��
	int m_dwID;					//����ID
	int m_dwIDUpdate;			//ֻ���������б������ID
	int m_nURLCount;			//�������ӵ�URL����
	DWORD m_dwSize;
	float m_fMark;				//����
	LONGLONG m_llDownloadTime;	//��ʼ����ʱ��

	CString m_strCrc;

	CRect m_rcName;				//��¼������ƻ�������
	CRect m_rcDes;				//��¼���������������
	CRect m_rcNewInfo;			//��¼�°湦�ܻ�������
	CRect m_rcFreeback;			//��¼��������
	CRect m_rcTautology;		//��¼��������

	int m_nCount;				//����ͼƬ�Ĵ���

	Gdiplus::Image *m_pImage;	//���ͼ��

	DWORD	m_dwDataID;			// ж����Ϣ�ڵ��������е�ID flz
	DWORD	m_dwFlags;			// �Ƿ��Ƿ�ҳ��

	BOOL	m_bUsingForOneKey;	// �Ƿ�һ��װ����ʹ���У�����������Ĳ���
};


#define		SOFT_INSTALLED			0
#define		SOFT_UNINSTALLED		1
#define		SOFT_UNINSTALLING		2
#define		SOFT_WAITUNINSTALL		3

enum UNIN_STATUS
{
	US_INVALID = -1, US_UNINSTALLED, US_INSTALLING, US_INSTALLED, US_WAIT_UNINSTALL, US_UNINSTALLING,
};

class CUninstallSoftInfo
{
public:
	CUninstallSoftInfo()
	{
		m_rcName = CRect(0, 0, 0, 0);
		m_rcFreq = CRect(0, 0, 0, 0);
		m_rcDeleteIcon = CRect(0, 0, 0, 0);
		m_rcViewDetail = CRect(0, 0, 0, 0);

		m_nSize = -1;
		m_nLastUse = -1;

		m_bShowDeleteIcon = FALSE;
		m_bRudimental = FALSE;
		m_bCleaned = FALSE;
		m_bNoUninstallInfo = FALSE;
		m_bSetup = TRUE;
		m_bCalcSize = FALSE;
		m_dwDataID = -1;
		m_pImage = NULL;
		m_dwUninstalled = 0;
		m_bVisited = FALSE; 
		m_bHide = FALSE;
		m_bWaitUninstall = FALSE;
		m_bUninstalling = FALSE;
		m_bIcon = FALSE;
		m_bCalcSizing = FALSE;
		m_bWaitCalc = FALSE;

		m_bIconLeg = TRUE;
	}

public:

	// ���ж�ػص��з��ص���Ϣ
	CString		key;				// ע������ -- ж��ʱʹ��
	CString		name;				// ����		-- ʹ�ô����Ƶ��� GetUninstallInfo ��ø���ϸ��Ϣ 
	CString		disp_icon;			// ����ͼ��
	CString		loc;				// ����·��
	CString		uni_cmd;			// ж������
	CString		parent;				// ������� -- ж�ظ����ʱ��������ȱ�ж��
	
	// ͨ�� GetUninstallInfo ��õ���Ϣ
	CString		m_strName;			//�������
	CString		m_strDescription;	//�������
	CString		m_strURL;			//����ҳ��ַ
	CString		m_strIconURL;		//���ͼ�����ص�ַ
	CString		m_strSoftID;		//���ID
	CString		m_strTypeName;		// �������
	CString		m_strSize;			//��С
	CString		m_strFreq;			//�ϴ�ʹ�þ�����������
	CString		m_strPath;			//·��

	CRect		m_rcName;
	CRect		m_rcFreq;
	CRect		m_rcDeleteIcon;
	CRect		m_rcViewDetail;

	DWORD		m_dwDataID;				// list ������ID
	LONGLONG	m_nSize;				// ���������ռ�ÿռ�
	int			m_nLastUse;				// ����������ϴ�ʹ��ʱ��

	DWORD		m_dwUninstalled;		// 0 -- δж��  1 -- ��ж��
	BOOL		m_bSetup;
	BOOL		m_bUninstalling;		//����ж��
	BOOL		m_bWaitUninstall;		//�ȴ�ж��
	BOOL		m_bIcon;
	BOOL		m_bCalcSize;
	BOOL		m_bVisited;				// �ݹ����ʱʹ�õı�־
	BOOL		m_bHide;
	BOOL		m_bCalcFreq;			//�Ƿ���Լ���Ƶ��
	BOOL		m_bNoUninstallInfo;		//û��ж����
	BOOL		m_bRudimental;			//������
	BOOL		m_bCleaned;				//�����������ɹ����
	BOOL		m_bShowDeleteIcon;		//�Ƿ���ʾɾ������ͼ��
	BOOL		m_bCalcSizing;			//�Ƿ����ڼ����С
	BOOL		m_bWaitCalc;

	BOOL		m_bIconLeg;				//ͼƬ�Ƿ�Ϸ�

	Gdiplus::Image *m_pImage;
};

class CPowerSweepData
{
public:
	CPowerSweepData()
	{
		bChecked = FALSE;
	}

public:
	CString		name;
	CString		ins_loc;				// ��װĿ¼
	CString		m_strType;				// ��Ŀ���ͣ��ļ���Ŀ¼��ע�����
	CString		m_strPath;				// ·��
	BOOL		bChecked;				// �Ƿ�ѡ�У�Ҫɾ��
};

class CUninstallPowerSweepData
{
public:
	CUninstallPowerSweepData()
	{
		m_nCallType = 0;
		m_nCheckedNum = 0;

	}

	void Clean()
	{
		m_nCallType = 0;
		m_nCheckedNum = 0;

		for ( int i=0; i<m_arrPowerSweepData.GetSize(); i++ )
		{
			CPowerSweepData * p = m_arrPowerSweepData[i];
			if ( p != NULL )
			{
				delete p;
			}
		}

		m_arrPowerSweepData.RemoveAll();
	}

public:

	int								m_nCallType;		// 0 -- ���   1 -- ��ɨ
	CSimpleArray<CPowerSweepData *> m_arrPowerSweepData;
	int								m_nCheckedNum;

};

//-----------------------------------------------------------------------
//���� CSoftListItemData
typedef std::vector<CSoftListItemData*>		t_vecItemData;
typedef t_vecItemData::iterator		t_iterItemData;
typedef std::pair<t_iterItemData, t_iterItemData>	t_pairItemData;

struct CSoftItemData
{
public:
	void AddData(CSoftListItemData* pData)
	{
		m_vecItemData.push_back(pData);
	}

	const t_vecItemData& GetDataList()
	{
		return m_vecItemData;
	}

	enum SortType
	{ 
		SORT_BY_ID = 0x00, 
		SORT_BY_TYPE,
	};

	void SortData(SortType type)
	{
		switch ( type )
		{
		case SORT_BY_ID:
			{
				std::sort(m_vecItemData.begin(), m_vecItemData.end(), _Guid());
			}
			break;
		case SORT_BY_TYPE:
			{
				std::sort(m_vecItemData.begin(), m_vecItemData.end(), _Type());
			}
			break;
		}
	}

	CSoftListItemData* GetDataByID(LPCWSTR lpSoftID)
	{
		if ( lpSoftID == NULL || wcslen(lpSoftID) == 0 )
			return NULL;

		CSoftListItemData _item;
		_item.m_strSoftID = lpSoftID;

		try
		{
			t_pairItemData _pairRet = std::equal_range(m_vecItemData.begin(), m_vecItemData.end(), &_item, _Guid());
			if ( _pairRet.first != _pairRet.second )
				return (*_pairRet.first);
		}
		catch( ... )
		{

		}

		return NULL;
	}

	CSoftItemData()
	{
		m_vecItemData.clear();
	}

	~CSoftItemData()
	{
		m_vecItemData.clear();
	}

	struct _Guid
	{
		bool operator()(CSoftListItemData* _pLeft, CSoftListItemData* _pRight)
		{
			return (_wcsicmp(_pLeft->m_strSoftID, _pRight->m_strSoftID) < 0);
		}
	};

	struct _Type
	{
		bool operator()(CSoftListItemData* _pLeft, CSoftListItemData* _pRight)
		{
			return (_wcsicmp(_pLeft->m_strType, _pRight->m_strType) < 0);
		}
	};
private:
	t_vecItemData	m_vecItemData;
};
#endif