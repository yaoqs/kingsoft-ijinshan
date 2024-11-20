#pragma once
#include <iefix/ldlistviewctrl.h>
#include "kws/KTimingCheckSecurityCloudTask.h"
#include "common/bksafelog.h"
#include "communits/ProcessSharedData.h"

extern CRITICAL_SECTION g_StartExam_cs;

class CBeikeSafeMainDlg;


#if 0
class LastTrojanScan
{
public:
	BOOL bScanned;
	DWORD dwScanMode;
	SYSTEMTIME stStartLast;
	SYSTEMTIME stStartFast;
	SYSTEMTIME stStartFull;
	SYSTEMTIME stStartCustom;
	DWORD dwVirusCount;
	DWORD dwRemainVirusCount;
	LastTrojanScan()
	{
		bScanned = FALSE;
	}
	LastTrojanScan(BOOL bScanned, DWORD dwScanMode, SYSTEMTIME stStartLast, 
		SYSTEMTIME stStartFast, SYSTEMTIME stStartFull, 
		SYSTEMTIME stStartCustom, DWORD dwVirusCount, 
		DWORD dwRemainVirusCount)
	{
		this->bScanned = bScanned;
		this->dwScanMode = dwScanMode;
		this->stStartLast = stStartLast;
		this->stStartFast = stStartFast;
		this->stStartFull = stStartFull;
		this->stStartCustom = stStartCustom;
		this->dwVirusCount = dwVirusCount;
		this->dwRemainVirusCount = dwRemainVirusCount;
	}
};
struct UI_CTRL_EX
{
	ULONG uCtrlID;
	ULONG uExParam;
	UI_CTRL_EX()
	{
		uCtrlID = -1;
		uExParam = -1;
	}
};
struct UI_TYPE_STRUCT
{
	ULONG uUIType;//����Ĭ������´��ڷ�Ϊ5�У�1,IE�޸����򴰿� 2��IE�޸����Ӵ��� 3��IE���� 4��IE����򵥴��� 5��IE�޸����Ӵ���
	CSimpleArray<UI_CTRL_EX> arrCtrlParam;//ÿһ�ִ���ģʽ�£����ڵĿؼ�ID
};

#endif

class CBeikeSafeExamUIHandler
	: public CBkNavigator
	, public CBkSafeUIHandlerBase
{
public:
	class EXAM_ITEM
	{
	public:
		EXAM_ITEM(DWORD a, LPCTSTR b, LPCTSTR c)
		{
			_dwItemID       = a;
			_pszItemCaption = b;
			_pszInitState   = c;
		}

		DWORD _dwItemID;
		CString _pszItemCaption;
		CString _pszInitState;
	};
	class EXAM_SCAN_RESULT
	{
	public:
		EXAM_SCAN_RESULT(DWORD a, LPCTSTR b, LPCTSTR c, LPCTSTR d, LPCTSTR e, 
			LPCTSTR f, LPCTSTR g, LPCTSTR h,
			LPCTSTR i = NULL , LPCTSTR j = NULL, LPCTSTR k = NULL)
		{
			_dwItemID					= a;
			_strDefaultCaption			= b == NULL ? L"" : b;	//default
			_strSafeOperate				= c == NULL ? L"" : c;
			_strDangerItemCaption		= d == NULL ? L"" : d;	//danger
			_strDangerDes				= e == NULL ? L"" : e;
			_strDangerOperate			= f == NULL ? L"" : f;
			_strCancelCaption			= g == NULL ? L"" : g;
			_strCancelOperate			= h == NULL ? L"" : h;	//cancel
			_strErrorCaption			= i == NULL ? L"" : i;	//error
			_strErrorOperate			= j == NULL ? L"" : j;
			_strErrorDes				= k == NULL ? L"" : k;

		}

		DWORD   _dwItemID;				//�����ĿID
		CString _strDefaultCaption;		//�����Ŀ����
		CString _strSafeOperate;		//�����Ŀ��ȫ��ʾ�Ĳ���
		CString _strDangerItemCaption;	//Σ����Ŀ��ʾ������
		CString _strDangerOperate;		//�����ĿΣ����ʾ�Ĳ���
		CString _strDangerDes;			//Σ����Ϣ����
		CString _strCancelCaption;		//��챻ȡ������ʾ����
		CString _strCancelOperate;		//ÿ��ȡ��ʱ���Ƽ�����
		CString _strErrorCaption;		//���ʱʧ����ʾ������
		CString _strErrorOperate;		//���ʧ������ʾ�Ĳ���
		CString _strErrorDes;
		//		CString _pszRisk_OOperate;		//�����ĿΣ����ʾ�Ĳ���-->��ʷ����
	};
	// 	enum enumLogState
	// 	{
	// 		scaned = 0,						//û��ɨ���
	// 		days30,							//360û�н��й�ɨ��
	// 		days7,							//7û�н���ɨ��
	// 		trojan,							//����ľ��
	// 		upload,							//���ϴ��ļ���־
	// 		installing,
	// 		kill,
	// 		unknown							//δ֪״̬
	// 	};
	//���ֲ�ͬ��ͳ����Ϣʹ��
	enum enumUpLogType
	{
		installeng = 0,					//��װ��������->0
		scantrojan,						//��ɱľ��->1
		startexam,						//��ʼ���->2
		reexam,							//�������->3
		noautoexam,						//ȡ���Զ����->4
		examtime,						//������->5
		unknownhosts,					//->6
		examresult,						//->7
		examfixitem,					//->8
		examautostart,					//->9
		examechofalied,					//->10
		homepageopt,					//11->��ҳ�Ƽ�����
	};

	class SAFE_MONITOR_ITEM
	{
	public:
		SAFE_MONITOR_ITEM(DWORD a, LPCTSTR b)
		{
			dwItemID    = a;
			strCaption  = b;
		}

		DWORD dwItemID;
		CString strCaption;
	};

public:
	CBeikeSafeExamUIHandler(CBeikeSafeMainDlg *pDialog)
		: m_pDlg(pDialog)
		, m_nShowProgress(0)		//��ǰ��ʾ�Ľ���
		, m_nRealProgress(0)
		, m_bExamFinished(FALSE)	//������
		, m_hStartExamEvent(NULL)	//��ʼ����¼�
		, m_bEcho(TRUE)				//����
		, m_bUpdateLog(FALSE)		
		//		, m_logState(unknown)
		, m_strDangerIDs(TEXT(""))	//ɨ�赽��Σ�����ID���ش���־���úϸ�
		, m_examType(examautostart) //�������
		, m_bKWSEnable(FALSE)
		, m_bKwsExist(FALSE)
		, m_nFixCount(0)
		, m_nDangerCount(0)
		, m_nCancel(0)
		, m_hExamShareDataEvent(NULL)
// 		, m_nShareDataCount(0)
// 		, m_nIndexShareData(0)
	{
		m_bkSafeLog.SetLogForModule(BKSafeLog::enumBKSafeMainDlgLog);
		m_nMaxScore = 100;//Ĭ����100
		m_nMinScore = 100;
		m_nMinScore2 = 100;
		m_nStartExamTime = 0;
		m_ExamItemSort.RemoveAll();
		InitializeCriticalSection(&g_StartExam_cs);
		m_hStartExamEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		_ResetMapVector();
		m_hExamShareDataEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_ExamPSD.Create(NAME_EXAM_SHARE_MEM, SIZE_EXAM_SHARE_MEM);
		::InitializeCriticalSection(&m_LockShareData);
		//m_arrExamShareData.RemoveAll();
		m_arrScanData.RemoveAll();
		m_arrFixData.RemoveAll();
	}

	~CBeikeSafeExamUIHandler();

	BKSafeLog::CBKSafeLog m_bkSafeLog;
	//����������Ļص�����
	void	ModifyMonitorState(int nType);								//ˢ�¼��״̬��Ϣ
	void	UpdatSafemonStateCaption(BOOL bKWSStatusRefresh = TRUE);
	void	UpdateExamSetting();										//���µ�ǰ����״̬
//	void	ModifyBwsMonitorState();									//������������״̬
	void	UpdateDubaState();
	void	Echo();														//��һ�����ֲ���
	CBkNavigator* OnNavigate( CString &strChildName );
	STATE_CLOSE_CHECK    CloseCheck();


	//�ڲ���Ա����
	void	Init(BOOL bStartExam);
	void	InitCtrl();
	void	StartExam(BOOL bExpress = FALSE);
	void	RefreshTodoList();
	HANDLE	m_hStartExamEvent;
	HANDLE									 m_hExamRecvEvent;
	//CAtlArray<BKSafe_Exam_ShareData>		 m_arrExamShareData;
	CRITICAL_SECTION						 m_LockShareData;
	CProcessSharedData						 m_ExamPSD;
	HANDLE									 m_hExamShareDataEvent;
// 	int										 m_nShareDataCount;
// 	int										 m_nIndexShareData;
	CAtlMap<int, BKSafe_Exam_ShareData>    m_arrScanData;
	CAtlMap<int, BKSafe_Exam_ShareData>	 m_arrFixData;


protected:
	void	FullScan();							//����ȫ��ɨ��
	void	OnBkLblExamRestart();				//�������
	void	OnBkBtnExamStop();					//ֹͣɨ��
	void	OnExamSet();						//�ֶ�����������
	void	OnListViewResize(CRect rcSize);		//������������list�Ĵ�С
	void	OnBkStartExam();					//�ֶ�������
	void	OnTimer(UINT_PTR nIDEvent);								
	void	OnBkOperate1();						//���Ͻǵ��Ƽ�����1-5
	void	OnBkOperate2();
	void	OnBkOperate3();
	void	OnBkOperate4();
	void	OnBkOperate5();
	void	OnBkOperate6();
	void	OnBkOperate7();
	void	OnBkOperate8();
	void	OnBkOperate9();
	void	OnBkSetSafemon();					//���Ͻǵ�����ʵʱ����
	void	OnBkSetKwsSafemon();				//���Ͻ����������
	void	NotityScanEntra( int nItem );



	LRESULT OnAppExamScoreChange(UINT uMsg, WPARAM wParam, LPARAM lParam);		//���ģ��ص����
	LRESULT OnAppExamOnlyEcho(UINT uMsg, WPARAM wParam, LPARAM lParam);			
	LRESULT OnAppEchoFinish(UINT uMsg, WPARAM wParam, LPARAM lParam);			//���ֽ���
	LRESULT OnAppExamProgress(UINT uMsg, WPARAM wParam, LPARAM lParam);			//������
	LRESULT OnLDListViewClickUrl(UINT uMsg, WPARAM wParam, LPARAM lParam);		//���������б��е���������
	LRESULT OnLDListViewExpandItem(UINT uMsg, WPARAM wParam, LPARAM lParam);	//�������չ������
	LRESULT OnExamErrorMsg(UINT uMsg, WPARAM wParam, LPARAM lParam);			//���ģ���м�⵽�Ĵ�����Ϣ
	LRESULT	OnFullScanTrojan(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//	LRESULT OnBkExamTabSel(int nTabItemIDOld, int nTabItemIDNew);				//������Ͻǵ��Ƽ����ܰ�ť
	LRESULT OnLDListViewClickExTxt(UINT uMsg, WPARAM wParam, LPARAM lParam);	//���������б��е���������
	LRESULT OnSignal(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);//��ⶾ���������Ƿ����ӳɹ�
	LRESULT OnStartExam(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);

public:
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		BK_NOTIFY_ID_COMMAND(IDC_LBL_EXAM_RESTART,					OnBkLblExamRestart)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_EXAM_STOP,						OnBkBtnExamStop)
		BK_NOTIFY_ID_COMMAND(IDC_EXAM_LNK_SETTING_ID,				OnExamSet)
		BK_NOTIFY_ID_COMMAND(IDC_EXAM_BTN_EXAM,						OnBkStartExam)
		BK_NOTIFY_ID_COMMAND(IDC_EXAM_BTN_CLEAN_OP1_ID,				OnBkOperate1);
	BK_NOTIFY_ID_COMMAND(IDC_EXAM_BTN_CLEAN_OP2_ID,				OnBkOperate2);
	BK_NOTIFY_ID_COMMAND(IDC_EXAM_BTN_CLEAN_OP3_ID,				OnBkOperate3);
	BK_NOTIFY_ID_COMMAND(IDC_EXAM_BTN_CLEAN_OP4_ID,				OnBkOperate4);
	BK_NOTIFY_ID_COMMAND(IDC_EXAM_BTN_CLEAN_OP5_ID,				OnBkOperate5);
	BK_NOTIFY_ID_COMMAND(IDC_EXAM_LNK_OPT_570,					OnBkOperate6);
	BK_NOTIFY_ID_COMMAND(IDC_EXAM_LNK_OPT_571,					OnBkOperate7);
	BK_NOTIFY_ID_COMMAND(IDC_EXAM_LNK_OPT_572,					OnBkOperate8);
	BK_NOTIFY_ID_COMMAND(IDC_EXAM_LNK_OPT_573,					OnBkOperate9);
	BK_NOTIFY_ID_COMMAND(IDC_EXAM_BTN_MODIFY_SAFEMON_ID,		OnBkSetSafemon);
	BK_NOTIFY_REALWND_RESIZED(IDC_EXAM_LISTVIEW_ID,				OnListViewResize)
		BK_NOTIFY_ID_COMMAND(IDC_EXAM_LNK_SETTIMGID_3,				OnExamSet)
		BK_NOTIFY_ID_COMMAND(IDC_EXAM_LNK_TXT_569,					OnBkSetKwsSafemon)
		BK_NOTIFY_ID_COMMAND(IDC_EXAM_LNK_BTN_530,					OnBkLblExamRestart)
		BK_NOTIFY_MAP_END()

		BEGIN_MSG_MAP_EX(CBeikeSafeExamUIHandler)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		MSG_WM_TIMER(OnTimer)
		MESSAGE_HANDLER_EX(MSG_APP_EXAM_SCORE_CHANGE,				OnAppExamScoreChange)
		MESSAGE_HANDLER_EX(MSG_APP_EXAM_ONLY_ECHO,					OnAppExamOnlyEcho)
		MESSAGE_HANDLER_EX(MSG_APP_ECHO_FINISH,						OnAppEchoFinish)
		MESSAGE_HANDLER_EX(MSG_APP_EXAM_PROGRESS,					OnAppExamProgress)
		MESSAGE_HANDLER_EX(MSG_USER_LDLISTVIEWCTRL_LBP_URL,			OnLDListViewClickUrl)
		MESSAGE_HANDLER_EX(MSG_USER_LDLISTVIEWCTRL_EXPAND,			OnLDListViewExpandItem)
		MESSAGE_HANDLER_EX(MSG_APP_EXAM_ERROR,						OnExamErrorMsg)
		MESSAGE_HANDLER_EX(MSG_USER_LDLISTVIEWCTRL_LBP_EXTXT,		OnLDListViewClickExTxt)
		MESSAGE_HANDLER_EX(MSG_APP_FULL_SCAN_TROJAN,				OnFullScanTrojan);
		MESSAGE_HANDLER(MSG_SIGNAL,									OnSignal);
		MESSAGE_HANDLER(MSG_APP_START_EXAM,							OnStartExam)
		END_MSG_MAP()

private:
	CSimpleArray<int>						 m_arrKwsExamItem;		//�������Ҫ�������ܵ���Ŀ
	BOOL									 m_bEcho;				
	BOOL									 m_bUpdateLog;			//�Ƿ���Ҫ�ϴ���־
	BOOL									 m_bUserCancelExam;		//�Ƿ��û��ֶ�ȡ�����
	DWORD									 m_dwStartExamTime;		//��ʼ����ʱ�䣬ͳ����
	CString									 m_strDangerIDs;		//����з���Σ����Ŀ��ID�б�
	enumUpLogType							 m_examType;			//��ǰ�û����������
	BOOL									 m_bKWSEnable;			//�����Ƿ���
	BOOL									 m_bKwsExist;			//�����Ƿ����
	BOOL									 m_bExamFinished;		//���ɨ��������
	int										 m_nShowProgress;		//���ɨ����ʾ����
	int										 m_nRealProgress;		
	CLDListViewCtrl							 m_ExamListView;		//��ʾ�����Ŀ�ͽ����list�б�
	CBeikeSafeMainDlg*						 m_pDlg;				//�����򴰿�ָ��
	KTimingCheckSecurityCloudTask			 m_CheckSecurityCloudTimer; //����Ƿ����Ӷ����ư�ȫ
	KLogic									 m_Logic;
	CSimpleArray<UINT>						 m_ExamItemSort;			//��ʼ���������и���Σ����Ŀ��˳��
	int										 m_nMaxScore;				//�����������ֵ
	int										 m_nMinScore;
	int										 m_nMinScore2;
	int										 m_nDangerCount;		
	int										 m_nCancel;
	int										 m_nFixCount;
	int										 m_nStartExamTime;
	CLocker									 m_lockRemove;


	CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM> m_mapSafeScanResult;	//��찲ȫ��Ŀ
	CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM> m_mapCancelScanResult;	//��챻ȡ������Ŀ
	CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM> m_mapRasikScanResult;	//���߷�����Ŀ
	CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM> m_mapDangerScanResult2;//�����Σ����Ŀ
	CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM> m_mapOptimization;
	CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM> m_mapAllDangerItem;
	CSimpleMap<DWORD, DWORD>				 m_mapItemScoreCoft;	//���ÿ���ϵ��
	CSimpleMap<DWORD, DWORD>				 m_mapExamLevelMinScore;//���ÿ����������ĵ÷���Сֵ

	void		_LoadExamData();														//���������Ŀ����ʾ�б���
	void		_UpdateExamData(int nItem=-1,BKSAFE_EXAM_RESULT_ITEM *pData=NULL);		//�������ɨ����
	void		_GetTextWithItemLevel(int nItem, int nLevel, CString& strOperate,		//���ݲ�ͬ�����Ŀ��Σ�յȼ���ʾ��ͬ����ʾ������Ϣ
		CString& strResult, BOOL bResult = FALSE);
	void		_RefreshExamList(int nItem, CString strUpdate, CString strScanState,	//ˢ��������б�(ɨ������л����)
		COLORREF extxtcolor, COLORREF urlcolor, int nImageID);
	int			_GetImageID(int nLevel);												//����Σ�յȼ���ʾ��ͬ��ͼ��
	void		_ShowExamResultData();								//ɨ�����֮�󣬶�ɨ�������¹���,�����������
	int			_ExamFixOperate(int nItem);												//�޸������ĳ��
	void		_UpdateExamSetTxt();													//�����û�ѡ��ͬ�����������ʾ��ͬ������
	void		_WriteExamLogToIni();													//�����Ϣ��¼��ini�ļ���
	void		_GetExamLogFromIni(CString& strTime, int& dwScore, int& nFixCount, 
		int& nDangerCount, int& nTime, int& nCancel);						//ͨ�������־��ȡ�ϴ������Ϣ
	CString 	_GetExamLogFilePath();													//��ȡ�����־�ļ���·��
	LONG		_CompareFileTime(CString strHistoryTime);								//ʱ��Ƚ�
	void		_UpdateHistoryInfo();													//������־�ļ�������һ�������Ϣ
	void		_StartHandShake();														//����һ�����ֲ���
	COLORREF	_GetTxtColor(int nLevel);												//����Σ�յȼ���Ӫ������ɫ

	int			_FixItem(REMOVE_EXAM_RESULT_ITEM RemoveExamItem);						//�����޸����״̬��Ϣ

	void		_SortMap(CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM>& mapData);			//���б�������򣬸���Σ�յȼ�
//	void		_InsertShowMoreData(int nGroup);										//������ʾ������Ϣ������
	BOOL		_GroupIDExist(int nGroupID);											//���ĳ����Ϣ�Ƿ���ʾ
	void		_ResetMapVector();														//����ɨ�����б�
	void		_InsertSafeResultData(LPCTSTR pszTitleCaption, int nGroupID,			//��ʾ��ȫ�����������
									CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM>& mapData);
	void		_InsertDangerResultData(LPCTSTR pszTitleCaption, int nGroupID,			//Σ��
									CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM>& mapData);
	void		_InsertCancelResultData(LPCTSTR pszTitleCaption, int nGroupID,			//ȡ��
									CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM>& mapData);				
//	BOOL		_IsHaveGroupHideInfo(int nGroupID);										//�Ƿ���������Ϣ
	LPLDListViewCtrl_Item _InsertResultData(int nGroupID, int nItem,					//��list�в�������
		BKSAFE_EXAM_RESULT_ITEM exam, BOOL bReloadCaption, int nInsertAt = -1);
	LPLDListViewCtrl_Item _InsertResultDataTitle(int nGroupID, LPCTSTR pszTitleCaption, //Σ�ջ��߰�ȫ����ı���
		int nLevel, int nImageID = 6, ENUM_LISTVIEW_FONT fontType = FONT_BOLD);

	void		_InsertOptResultData(LPCTSTR pszTitleCaption, int nGroupID,			//��ʾ���Ż������������
									CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM>& mapData);

	int			_GetExamType();															//��⵱ǰ�û����õ�������ͣ�����0��ʾ�������Զ����
	void		_ReportLog(enumUpLogType ReportType, CString strLog = TEXT(""));		//����
	int			_GetSafeMonitorItemCaption(CString& strCaption, int nItemID = -1);						//��ȡδ�����ļ�ص�����
	int			_RetryEcho();															//��������
	int			_IsKwsExam(int nItem);													//����Ƿ���ͨ������ɨ�赽��
// 	void		_CheckKwsExamResult();													//����������ȫ���
 	int			_IsAllKwsOpen();														//�������ȫ�������Ƿ���
	void		_LoadGlobalData();														//���������ʾ�б��е���Ϣ
	void		_UpdateExamResultTitle();												//������ʾ����������Ľ�����Ϣ
	void		_InitExamItemSort();													//��ʼ����촦�������Ŀ����ʵ˳��

	//int			_FileSignerIsValid(LPCTSTR pszFile, CAtlArray<CString>& arrSinger);		//��֤�ļ�ǩ���͸������Ƿ���ͬ�����û��ָ����ֻ��֤��Ч��
	void		_StartProcess(LPCTSTR pszFileFullPath, LPCTSTR pszParam = NULL);		//��������������
	int			_CheckDuBa();															//��ⶾ��
	int			_CheckSoftWareUpdate(int& nUpdateCount);
	void		_SetExamMinScore(int nItemID, int nLevel);
	void		_CalcExamScore();
	void		_UpdateExamScoreImage();
	void		_ParseScore(int nScore, CSimpleArray<int> &arr, CSimpleArray<int>& arr2);
	void		_ParseScoreForUpdateUI(int nScore, CStringA& strSkinNum, 
										CString& strText1, CString& strText2, 
										int& dwImage, int& dwTextColor, int& dwScoreText);
	void		_ParseScoreForUpdateUI(int nScore, int& nLevel, int& nImage, int& nTxtColor);
	void		_ShareExamData(UINT uMsg, WPARAM wParam, LPARAM lParam);
	CString     _ConverColorToStr(COLORREF color);
	void		_UpdateExamResult();
	void		_InitArrayForShareData();
	DWORD		_GetTitleTxtColor(int nLevel);


};


