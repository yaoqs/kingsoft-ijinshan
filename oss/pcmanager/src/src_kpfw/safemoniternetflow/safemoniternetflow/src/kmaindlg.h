#pragma once
#include "bkres/bkres.h"
//#include "treelistctrlex.h"
#include "kpfw/netfluxdef.h"
#include <vector>
#include "common/KCheckInstance.h"
#include <wtlhelper/whwindow.h>
using namespace std;
#include "bklistbox.h"
#include "common/bksafelog.h"
#include "resource.h"
#include "kprocesslib/interface.h"
#include "netflowmonlistitemdata.h"
#include "netmonitorutility.h"
#include "communits/Locker.h"
#include "kflowstat.h"
#include "kispublic/klocker.h"
#include "kpfw/netstastic.h"
#include <map>
#include "kflowstatlist.h"
#include "kstatlimitdlg.h"


#define ID_TIMER_CHECK_EXIT  1
#define CHECK_EXIT_INTERVAL  500

#define ID_TIMER_UPDATE_NETFlOW_MON		2
#define ID_TIMER_UPDATE_STAT_INFO		3

#define ID_TIMER_REFRESH_FLOATWND_STATUS	4

// ��ʾ��û�ȡһ������, ��������1sһ�Σ�����ĳɸ�СҲû����
#define UPDATE_NETFLOW_MON_INTERVAL		    1000

#define MSG_NETMONITOR_LIMIT	WM_APP+0x100
//class KNetFlowMonList;
#define DEF_PAGE_COUNT			12


class KMainDlg
    : public CBkDialogImpl<KMainDlg>,
	public CWHRoundRectFrameHelper<KMainDlg>
{
public:
	enum enumUpLogType
	{
		enumUnknownProc = 0,
		enumUnknown = -1
	};
public:
    KMainDlg()
        : CBkDialogImpl<KMainDlg>(IDR_BK_NETMONITOR_DIALOG)
		, m_pNetMonitorListBox(NULL)
		, m_hNetMonitorMenu	(NULL)
		, m_hEventGetNetData(NULL)
		, m_nCurShowType(enumQueryTypeEveryDay)
		, m_pNetStatListBox(NULL)
		, m_hEventRptThreadExit(NULL)
		, m_hThreadReport(NULL)
		, m_bRptThreadWorking(FALSE)
    {
		m_FluxSys.nRecvSpeed = 0;
		m_FluxSys.nSendSpeed = 0;
		m_FluxSys.nTotalRecv = 0;
		m_FluxSys.nTotalSend = 0;
		
		m_arrColumWidth.SetCount(10);
		m_arrColumWidth[0] = 250;
		m_arrColumWidth[1] = 70;
		m_arrColumWidth[2] = 70;
		m_arrColumWidth[3] = 70;
		m_arrColumWidth[4] = 100;
		m_arrColumWidth[5] = 85;
		m_arrColumWidth[6] = 90;
		//m_arrColumWidth[7] = 60;
		m_arrColumWidth[7] = 40;
		m_arrColumWidth[8] = 0;
		m_arrColumWidth[9] = 0;

		for (int i = 0; i < 5; i++)
			m_nCurPage[i] = 1;
		

		m_nCurShowStr = 49;

		m_hDefaultIcon	   = NULL;
		//state
		_ResetArray();
		//::InitializeCriticalSection(&m_Lock);
		m_hEventGetNetData = CreateEvent(NULL, FALSE, TRUE, NULL);
		m_mapReported.RemoveAll();
		m_mapNeedReportProc.RemoveAll();

/*		m_nTotalRecvBegin = 0;
		m_nTotalSendBegin = 0;
		m_nTotalAllBegin = 0;
		m_nTimeWatchBegin = 0;
		m_nRecordEveryDays = 0;
		m_nRecordEveryMonth = 0;
		m_nTotalAllBeginForMonth = 0;
*/
		m_pShowStatLock = new KLockerCS();

    }

    ~KMainDlg();

	///////////////////////////////////////////////////////////////////////////////////////
	//����ʹ�ò���

	void			BtnClose(void);
	void			BtnMin(void);
	void			BtnNetMonSwitch(void);
	void            BtnFloatWndSwitch(void);

	BOOL			OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam*/);
	void			OnSize(UINT nType, CSize size);

	void			OnSysCommand(UINT nID, CPoint pt);

	LRESULT			ShowUI(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT			ShowDay(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT			ShowMonth(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	// �������û�����⣬����true���������ʧ�ܷ���false
	BOOL			CheckDriver();

	BOOL			CheckServericeIsOK();

	static BOOL		GetNetMonIsEnabled();

	//���tab
	BOOL			OnBkTabMainSelChange(int nTabItemIDOld, int nTabItemIDNew);


	BOOL			IsFloatWndStartWithTray();
	void			OpenFloatWnd();
private:
	LRESULT			OnTimer(UINT timerId);
	LRESULT			OnDestroy();
	BOOL			_CheckDriverIsFailed();
	BOOL			_CheckForceDisableDriver();
	BOOL			_CheckHasUnCompatibleDriver();
	BOOL			_CheckTdxDriver();
	int				_IsVistaPlatform();
	BOOL			_CheckHasUnCompatibleSofware();
	BOOL			_CheckDriverVersion();

	BOOL			_IsDriverExist(LPCWSTR strDriverServiceName);
	DWORD			_GetServiceStatus(LPCWSTR strServiceName, int nMaxQueryMilliseconds);
	
	CLocker			m_locker;
	//����ʹ�ò���end
	///////////////////////////////////////////////////////////////////////////////////////
	
    
	///////////////////////////////////////////////////////////////////////////////////////
	//������ز���
public:
	BOOL			_DisableDelayScan();

	// 2.0ui [11/29/2010 zhangbaoliang]
	//static CAtlArray<UINT>				m_arrColumState;//�����ж��Ƿ������ʱ��ʹ����Ҫ����0������1������
	//ˢ��LISTBOX��ÿ�е�����
	LRESULT			OnListBoxGetDispInfo(LPNMHDR pnmh);

	//����LISTBOX���иߵ����ֵ
	LRESULT			OnListBoxGetmaxHeight(LPNMHDR pnmh);

	LRESULT			OnListBoxGetItemHeight(LPNMHDR pnmh);

	//LISTBOX�л�ȡ�����Ϣ
	LRESULT			OnBkListBoxClickCtrl(LPNMHDR pnmh);

	//LISTBOX�л�ȡ�Ҽ������Ϣ
	LRESULT			OnBkListBoxRClickCtrl(LPNMHDR pnmh);

	BOOL			OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//��ʼ�Լ�д������Ч�ʺܵ��ݲ�ʹ��
	static			bool SortNetInfo(KProcFluxItem& ItemData1, KProcFluxItem& ItemData2, int nColum, int nState);

	//ʹ��STL������
	static			bool stl_SortNetInfo(KProcFluxItem& ItemData1, KProcFluxItem& ItemData2);

	//��Ӧÿһ�е��������
	static			int  Compare( KProcFluxItem& ItemData1, KProcFluxItem& ItemData2, int nsubIndex = -1);



	//static			bool vetFind_if(KProcFluxItem& findItem);
	//һ�¶��ǵ��������������Ϣ
	//ÿ��Ĭ��Ĭ��״̬ʱ-1,0��ʾ����1��ʾ����
	void			OnClickColumTitle();
	void			OnClickColumLevel();
	void			OnClickColumDownLoadSpeed();
	void			OnClickColumUpLoadSpeed();
	void			OnClickColumNetLimit();
	void			OnClickColumTotalDownload();
	void			OnClickColumTotalUp();
	void			OnClickColumPID();
	// end click colum
	void			OnClickNetSetting();
	void			OnClickNetLockOpen();
	void			OnClickNetLockClose();
	void			OnClickNetLimitText();
	void			OnClickOpenDir();

	//�Ƽ������������
	void			OnStartNetSpeed();

	//��Ӧ�Ĳ����˵�
	LRESULT			OnNetMonitorCommand(UINT uMsg, WPARAM wParam, LPARAM lParam);

	//���������ǵ��������ٴ����ڹر�ʱ����Ϣ������
	LRESULT			OnNetMonitorLimitMsg(UINT uMsg, WPARAM wParam, LPARAM lParam);

	
	//����������
	void			OnClickWindowSetting(void);

	void			OnClickShowList1(void);
	void			OnClickShowList2(void);
	void			OnClickShowList3(void);
	void			OnClickShowList4(void);
	void			OnClickIsShowTip(void);

	void			_ShowListClick(IN int nCurPage);
	void			_ShowListInfo(void);

  	//�����ұߡ�������������ռ�����а�ġ�����ض���
	BOOL			_SetFlowList(IN int nPos, IN const CString& strSrcFilePath, IN const CString& strNeedShowStr, IN const CString& strShowSize);

private:
	static CString _GetNeedShowData(IN ULONGLONG fData);

	// ��������������Ϣ
	void _UpdateNetFlowSummaryWnd();

	//���ö��ٸ��������ڷ�������
	void _SetAccessNetCount(IN int nCount);

	//�����������������ϴ�������������ĵ�λΪB��
	void _SetDownAndUpdateSum(IN ULONGLONG uDownData, IN ULONGLONG uUpdata);

	//���������ٶȣ����뵥λΪB��
	void _SetDownSpeed(IN ULONGLONG uDownSpeed);

	//�����ϴ��ٶȣ����뵥λΪB��
	void _SetUpSpeed(IN ULONGLONG uUpSpeed);

	// ��������
	void _OpenFloatWnd();

	// �ر�������
	void _CloseFloatWnd();

	// ��ȡ�������Ƿ���ʾ
	BOOL			_GetFloatWndDisplayStatus();
	BOOL			_GetIsAutoCloseFloatWndWhenDisableNetmon();
	BOOL			_SaveIsAutoCloseFloatwndWhenDisableNetmon(BOOL isClose);
	BOOL			_GetIsRememberAutoCloseFloatWndWhenDisableNetmon();
	BOOL			_SaveIsRememberAutoCloseFloatWndWhenDisableNetmon(BOOL isRemember);
	CString			_GetFloatWndConfigFilePath();

	void			_SetNetMonSwitchBtn(BOOL isEnabled);
	void			_SetNetMonSwitchHintText(BOOL isEnabled);

	BOOL			_EnableNetMon(BOOL isEnable);
	void			_InitNetMonSwitch();
	void			_InitFloatWndSwitch();
	void			_ShowFloatWnd(BOOL isShow);

	void			_OpenFlux();

	void			_HideOrShowTip(IN BOOL bIsShowTip, IN BOOL bIsNeedAct = TRUE);

private:
	//    WTL::CImageList         m_imagelist;
	// listView�ؼ��е�����
	//    KNetFlowMonList*		m_pNetFlowMonList;

	UINT					m_uTimer;
	KPFWFLUX				m_FluxSys;// ϵͳ������
	vector<KProcFluxItem>	m_processInfoList;// ������̵�������Ϣ
	bool                    m_bFloatWndIsOpen;// ��ǰ������״̬�� true�򿪣�false�ر�
	HANDLE                  m_hEventExit; 
	HANDLE                  m_hEventChangeFlowatWndDisplayStatusText;    
	BOOL                    m_bNetMonEnabled;
	int                     m_nNetFlowListRefreshCountAfterDisable;
	HANDLE					m_hEventRptThreadExit;
	HANDLE					m_hThreadReport;
	BOOL					m_bRptThreadWorking;

	//���޸� 2.0 [12/8/2010 zhangbaoliang]
	CBkNetMonitorListBox*							m_pNetMonitorListBox;
	HMENU											m_hNetMonitorMenu;		
	CAtlArray<UINT>									m_arrColumWidth;

	CAtlMap<DWORD, CNetMonitorCacheData>			m_mapProcNetData;			//��ӦLISTBOX�е�ÿ������
	CAtlMap<DWORD, CNetMonitorCacheData>			m_mapSpeedLimitProcNetData;	//��δʹ��
	CRITICAL_SECTION								m_Lock;						//��ֹ����_RefreshArray������������
	HICON											m_hDefaultIcon;
	CAtlMap<CString, CNetMonitorCacheData>			m_mapNeedReportProc;
	CAtlMap<CString, CNetMonitorCacheData>			m_mapReported;
	int												m_nCurShowStr;
	enumProcessMode									m_enumProcessMode;


	//��Ϊ����ʵ����֮ǰҪ�����ݽ��д�������Ϊ��ͬ��TIMER�е�ȡ���ݺͲ�����������
	//�п����ǳ��ֵ���������ϴε����ݻ�û�д����꣬TIMER����Ҫ��ʼ���ȡ�����ˣ��������������������ڴ�������ݷ��ϱ仯
	//����Ҫ��֤�Ҵ��������ϴε����ݲ���ȡ��ε�����
	HANDLE											m_hEventGetNetData;			
	//CAtlMap<DWORD, PFN>				m_mapMenuFunc;

	void					_ReleaseThread();
	// ������ʾ�б� (LISTBOX)
	void					_InitNetMonitorListBox();

	//�����б�
	void					_ResetArray();

	//������������
	//���������ݽ�������,������ݸ�������һ���б仯�͸����б�����û��ֱ��ǿ��ˢ������
	void					_RefreshListBoxData(vector<KProcFluxItem>& vetNetData);

	//�������Ҫ���򣬸���ÿһ�е�״̬,��������ͼ����ʧ��
	void					_SetColumState(int nColum);	

	//�ѻ�ȡ�������ݻ��浽һ������map��
	//���MAP������ʵ�б��������ÿһ���Ӧһ��
	void					_CreateCacheData(vector<KProcFluxItem>& vetNetData, CAtlMap<DWORD, CNetMonitorCacheData>& mapCacheData);

	//����Ipc֪ͨ����������,���õȲ���
	void					_NetSpeedLimit(CNetMonitorCacheData* pNetData);

	//�������ٹ����ǣ��������������ʾ���ٴ���
	int						_CallNetLimitDialog(CNetMonitorCacheData& NetData);

	//��������ĳ�е�����ʱ����������ӿڰɶ�Ӧ����ʵ�б��е����ݸ��»�������
	//���£���ʱû��ʹ��
	void					_UpdateCacheData(CNetMonitorCacheData& NetData);

	//���½�����
	int						_RefreshProcName(int nLeft, int nRight, KNetFlowMonListItemData ItemData);

	//���½�������
	int						_RefreshProcDes(int nLeft, int nRight, int nHeight, CNetMonitorCacheData NetData);

	//���½����ļ��ȼ�
	int						_RefreshProcLevel(int nLeft, int nRight, KNetFlowMonListItemData ItemData);

	//���½����ϴ��ٶ�
	int						_RefreshProcUpSpeed(int nLeft, int nRight, KNetFlowMonListItemData ItemData);

	//���½��������ٶ�
	int						_RefreshProcDownSpeed(int nLeft, int nRight, KNetFlowMonListItemData ItemData);

	//���½������ٶ�
	int						_RefreshProcLimitSpeed(int nLeft, int nRight, KNetFlowMonListItemData ItemData);

	//���½������ϴ�����
	int						_RefreshProcTotalUp(int nLeft, int nRight, KNetFlowMonListItemData ItemData);

	//���½�����������
	int						_RefreshProcTotalDown(int nLeft, int nRight, KNetFlowMonListItemData ItemData);

	//���½���ID
	int						_RefreshProcID(int nLeft, int nRight, KNetFlowMonListItemData ItemData);

	//���½���ͼ��
	int						_RefreshProcICO(int nLeft, int nRight, KNetFlowMonListItemData ItemData);

	//���½���·��
	int						_RefreshProcPath(int nLeft, int nRight, int nCurSel, KNetFlowMonListItemData ItemData);

	//���½��̲���ͼ��
	int						_RefreshProcSetting(int nLeft, int nRight,KNetFlowMonListItemData ItemData);

	//////////////////////////////////////////////////////////////////////////
	//��ȡ������·��
	CString					_GetAppPath();

	//////////////////////////////////////////////////////////////////////////
	//pid
	//int						_RefreshProcID(int nLeft, int nRight,KNetFlowMonListItemData ItemData);

	//������ز���end
	///////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////
	//����ͳ�Ʋ���

	//���������ʾ֮���
	void			OnClickShowStatDays(void);
	void			OnClickShowStatWeeks(void);
	void			OnClickShowStatMonths(void);
	void			OnClickShowStatDefineSelf(void);

	//��������
	void			OnClickChangeSetting(void);

	//�����ҳ����һҳ����һҳ��βҳ�Ȳ���
	void			OnClickShowFirstPage(void);
	void			OnClickShowBeforePage(void);
	void			OnClickShowNextPage(void);
	void			OnClickShowEndPage(void);

	//��� ���鿴���ࡱ
	void			OnClickShowMore(void);

private:

	//��Ӧlist��Ϣ
	LRESULT			OnStatListGetDispInfo(LPNMHDR pnmh);
	LRESULT			OnStatListGetmaxHeight(LPNMHDR pnmh);
	LRESULT			OnStatListGetItemHeight(LPNMHDR pnmh);
	
	//��ȡ��ʱ�䡱�е�����
	CString			_GetStatListInfoTime( IN CString strTimeMin, IN CString strTimeMax, IN int nMode);
	//��ȡ���ϴ����������е�����
	CString			_GetStatListInfoUpAllFlow(IN LONGLONG lUpAllFlow);
	//��ȡ���������������е�����
	CString			_GetStatListInfoDownAllFlow(IN LONGLONG lDownAllFlow);
	//��ȡ�����������е�����
	CString			_GetStatListInfoAllFlow(IN LONGLONG lAllFlow);
	//��ȡ�����ʱ�䡱�е�����
	CString			_GetStatListMoniterTime(IN long lMoniterTime);

	BOOL			_GetCurLogInfo(IN enumQueryType enumType);
	BOOL			_GetCurLogInfo(IN enumQueryType enumType, IN CString strFrwo, IN CString strTo);
	BOOL			_GetCurLogInfo(OUT LONGLONG& uUpData, OUT LONGLONG& uDownData, OUT LONGLONG& uAllData);

	BOOL			_InitStatList(void);
	void			_ShowStatList(IN int nCode);
	CString			_GetEveryTime(IN long& lMoniterTime, IN long lBeCalcResidue,IN CString strUnit);

	//���ý�����������ʹ��ͳ��
	void			_SetFlowStatInfo(IN CString strAllFlow, IN CString strUpFlow, IN CString strDownFlow);
	void			_ShowPageForList();

	//��ȡ��ǰ����
	void			_GetAndShowProcessInfo(void);

	//����
	static bool		stl_SortPorcessList(KFluxStasticProcItemEx& ItemData1, KFluxStasticProcItemEx& ItemData2);

	void			_ShowRemindInfo(void);
	void			_GetRemindInfo(OUT int& nDay, OUT int& nMonth);
	void			_GetRemindMarkInfo( OUT int& nDayMark, OUT int& nMonthMark );
	void			_GetRemindLastData( OUT int& nDayData, OUT int& nMonthData );

	void			_InitFlowRemindInfo(void);
	int				_GetHadWaitTenMuniters(void);
	//�Ƿ���ʾ�������ͳ�����ѶԻ���
	void			_ShowNetMintorRemindDlg(IN int nIsInit = FALSE);

	void			_ShowDialogRemind(IN int nMode, IN int nSetSize, int nIsInit = FALSE);

	//��ʾ����ͳ�Ƶĵڶ�������
	void			_SetStatFlowShow(void);

	//�����ݿ��ж�ȡ����
	BOOL			_GetAllDataFromDB(IN enumQueryType enumType, IN CString strCurTime, OUT LONGLONG& nRet);

	//
	BOOL			_SetDelayTenMuniter(void);
	BOOL			_HadWaitTenMuniters(void);
	long			_GetFormatTime(int nYear, int nMonth, int nDay);

	void			_ReSetAddData(IN ULONGLONG nTotalRecv, IN ULONGLONG nTotalSend, IN ULONGLONG nTotalAll, IN __int64 nTimeWatch);
	void			_AddNewData(void);
private:
/*
	LONGLONG					m_nTotalRecvBegin;
	LONGLONG					m_nTotalSendBegin;
	LONGLONG					m_nTotalAllBegin;
	__int64						m_nTimeWatchBegin;
	__int64						m_nRecordTimeBegin;
	LONGLONG					m_nRecordEveryDays;
	LONGLONG					m_nRecordEveryMonth;
	LONGLONG					m_nTotalAllBeginForMonth;
*/
	KStatListDlg				m_statListdlg;
//	KNetFluxStasticCacheReader	m_fluxStatRead;
//	KStasticFluxProcessList*	m_pFluxStatRead;
	int							m_nCurShowType;
	int							m_nCurPage[5];

	KFlowStat					m_FlowStatLog;
	CBkNetMonitorListBox*		m_pNetStatListBox;
	struct stLogListInfo 
	{
		CString strMinTime;
		CString strMaxTime;
		LONGLONG lUpFlow;
		LONGLONG lDownFlow;
		LONGLONG lAllFlow;
		LONGLONG lAllTime;
		void Init(void)
		{
			strMinTime = _T("");
			strMaxTime = _T("");
			lUpFlow = 0;
			lDownFlow = 0;
			lAllFlow = 0;
			lAllTime = 0;
		}
	};

	std::vector<stLogListInfo> m_vLogListInfo;
	ILockerMode*			   m_pShowStatLock;
	std::vector<KFluxStasticProcItemEx> m_vFlowStatPList;
	CString						m_strQueryBegin;
	CString						m_strQueryEnd;
	typedef std::pair<CString, KFluxStasticProcItemEx> StatMapPair;
	std::map<CString, KFluxStasticProcItemEx>	m_statMap;

	//����ͳ�Ʋ���end
	///////////////////////////////////////////////////////////////////////////////////////
	
public:
    BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		//��������
		BK_NOTIFY_ID_COMMAND(DEFCLOSEMAINBUTTON, BtnClose)
		BK_NOTIFY_ID_COMMAND(DEF_MIN_BTN, BtnMin)
		BK_NOTIFY_TAB_SELCHANGE(TAB_MAIN, OnBkTabMainSelChange)
		//��������end

		//������ز���
		BK_NOTIFY_ID_COMMAND(DEF_NETFLOW_SWITCH, BtnNetMonSwitch)
		BK_NOTIFY_ID_COMMAND(DEF_FLOATWND_SWITCH, BtnFloatWndSwitch)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_219, OnClickColumTitle)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_220, OnClickColumLevel)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_221, OnClickColumDownLoadSpeed)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_222, OnClickColumUpLoadSpeed)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_223, OnClickColumNetLimit)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_224, OnClickColumTotalDownload)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_225, OnClickColumTotalUp)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_226, OnClickColumPID)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_211, OnClickNetSetting)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_229, OnClickNetLockOpen)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_230, OnClickNetLockClose)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_207, OnClickNetLimitText)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_216, OnClickOpenDir)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_239, OnStartNetSpeed)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_242, OnClickShowList1)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_244, OnClickShowList2)	
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_246, OnClickShowList3)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_249, OnClickIsShowTip)
		BK_NOTIFY_ID_COMMAND(NET_MONITOR_307, OnClickShowList4)
		
	//	BK_NOTIFY_ID_COMMAND(DEV_VIEW_DETAIL, OnClickWindowSetting)
		//������ز���end

		//����ͳ�Ʋ���
		BK_NOTIFY_ID_COMMAND(TAB_SHOW_STAT_DAYS, OnClickShowStatDays)
		BK_NOTIFY_ID_COMMAND(TAB_SHOW_STAT_WEEKS, OnClickShowStatWeeks)	
		BK_NOTIFY_ID_COMMAND(TAB_SHOW_STAT_MONTHS, OnClickShowStatMonths)
		BK_NOTIFY_ID_COMMAND(TAB_SHOW_STAT_DEFINESELF, OnClickShowStatDefineSelf)
		BK_NOTIFY_ID_COMMAND(DEF_NETFLOW_SWITCH2, BtnNetMonSwitch)
		BK_NOTIFY_ID_COMMAND(TAB_SHOW_STAT_CSETTING, OnClickWindowSetting)
		BK_NOTIFY_ID_COMMAND(DEF_SHOW_FIRST, OnClickShowFirstPage)
		BK_NOTIFY_ID_COMMAND(DEF_SHOW_BEFORE, OnClickShowBeforePage)	
		BK_NOTIFY_ID_COMMAND(DEF_SHOW_NEXT, OnClickShowNextPage)
		BK_NOTIFY_ID_COMMAND(DEF_SHOW_ENDP_PAGE, OnClickShowEndPage)
		BK_NOTIFY_ID_COMMAND(DEF_SHOW_MORE, OnClickShowMore)
		//����ͳ�Ʋ���end
    BK_NOTIFY_MAP_END()


    BEGIN_MSG_MAP_EX(KMainDlg)
		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<KMainDlg>)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		//��������
		MSG_WM_SIZE(OnSize)
		CHAIN_MSG_MAP(CBkDialogImpl<KMainDlg>)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_TIMER(OnTimer)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_SYSCOMMAND(OnSysCommand)
		MESSAGE_HANDLER(WM_UPLIVE_SHOW, ShowUI )
		MESSAGE_HANDLER(WM_SHOW_RUN1, ShowDay )
		MESSAGE_HANDLER(WM_SHOW_RUN2, ShowMonth )
		MSG_WM_MOUSEWHEEL(OnMouseWheel)
		MESSAGE_HANDLER_EX(WM_COMMAND,		OnNetMonitorCommand)

		//������ز���
		NOTIFY_HANDLER_EX(NET_MONITOR_201, BKLBM_GET_DISPINFO, OnListBoxGetDispInfo)
		NOTIFY_HANDLER_EX(NET_MONITOR_201, BKLBM_CALC_MAX_HEIGHT, OnListBoxGetmaxHeight)
		NOTIFY_HANDLER_EX(NET_MONITOR_201, BKLBM_CALC_ITEM_HEIGHT, OnListBoxGetItemHeight)
		NOTIFY_HANDLER_EX(NET_MONITOR_201, BKLBM_ITEMCLICK, OnBkListBoxClickCtrl)
		NOTIFY_HANDLER_EX(NET_MONITOR_201, BKRBM_ITEMCLICK, OnBkListBoxRClickCtrl)
		MESSAGE_HANDLER_EX(MSG_NETMONITOR_LIMIT, OnNetMonitorLimitMsg)

		//����ͳ�Ʋ���
		NOTIFY_HANDLER_EX(TAB_SHOW_STAT_WINDOW, BKLBM_GET_DISPINFO, OnStatListGetDispInfo)
		NOTIFY_HANDLER_EX(TAB_SHOW_STAT_WINDOW, BKLBM_CALC_MAX_HEIGHT, OnStatListGetmaxHeight)
		NOTIFY_HANDLER_EX(TAB_SHOW_STAT_WINDOW, BKLBM_CALC_ITEM_HEIGHT, OnStatListGetItemHeight)

		REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()
	
};
