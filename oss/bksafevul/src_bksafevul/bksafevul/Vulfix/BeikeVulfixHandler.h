#pragma once
#include "BeikeVulfix.h"
#include <wtlhelper/whwindow.h>
#include "BaseViewHandler.h"
#include "BeikeVulfixUtils.h"
#include "ListViewCtrlEx.h"
#include "RichEditCtrlEx.h"
#include "HyperTextCtrl.h"
#include <vulfix/BeikeUtils.h>

class CBeikeVulfixHandler;
class CEmbeddedView;
class CBeikeSafeMainDlg;

#define IDC_RICHVIEW_WIN_VULFIX            3000

struct T_ExportInfo
{
	INT nType, nWarnLevel;
	DWORD dwFlags;
	CString strName, strDesc, strDate;
	CString strPageUrl, strDownloadUrl;
};
typedef std::vector<T_ExportInfo> T_ExportInfoArray;

class CBeikeVulfixHandler : public CBaseViewHandler<CEmbeddedView>
{
public:
	CBeikeVulfixHandler(CEmbeddedView &mainDlg);
	~CBeikeVulfixHandler(void);
	
public:
	BOOL Init(HWND hMainWnd, HWND hWndParent);
	void InitEnv();
	void SetMainDlg(CBeikeSafeMainDlg *pMainDlg);
	BOOL CloseCheck();
	void _SetDisplayState(TScanSoftState st, TRepairSubState subst=REPAIRSTATE_ING, LPCTSTR szMsg=NULL);

protected:
	CBeikeSafeMainDlg *m_MainDlg;
	HWND m_hMainWnd;
	BOOL m_firstInited;
	DWORD m_dwPos;
	CListViewCtrlEx m_wndListCtrlVul, m_wndListCtrlVulFixing;
	BOOL m_bRelateInfoShowing;
	CRichEditCtrlEx m_ctlRichEdit;
	int m_nCurrentRelateInfoItem;
	CHyperTextCtrl m_ctlNaviLink;
	
	bool m_bScanStarted;	// ���Ƿ�����ɨ��xml, ���ǻ��ڵȴ���Ϣ(Win7 & Vista) 
	// scan 
	int m_nScanState, m_nTotalItem, m_nCurrentItem;
	DWORD m_dwScanBeginTime;
	// Repair 
	int m_nRepairTotal, m_nRepairInstalled, m_nRepairDownloaded, m_nRepairProcessed;
	int m_nRepairCurrentRate;
	
	CString m_strLastScanTime;
	T_WindowsInfo m_WinInfo;
	BOOL m_WinInfo64;
	
	// 
	INT m_nNumMust, m_nNumOption, m_nNumSP;
	

	// BK HANDLER
	void OnBkBtnSwitchRelateInfo();
	void OnBkBtnSelectAll();
	void OnBkBtnSelectNone();
	void OnBkBtnSelectAllSuggested();
	void OnBkBtnSelectAllOptional();
	
	void OnBkBtnIgnore();	// ����

	void OnBkBtnScan();
	void OnBkBtnCancelScan();
	
	void OnBkBtnBeginRepair();
	void OnBkBtnCancelRepair();
	void OnBkBtnRunBackground();
	void OnBkBtnReboot();
	
	void OnBkBtnEnableRelateCOM();
	void OnBkBtnDisableRelateCOM();

	void OnBkBtnViewInstalled();
	void OnBkBtnViewIgnored();
	void OnBkBtnViewSupersede();
	void OnBkBtnViewInvalid();	
	
	void OnBkBtnErrorRepair();
	void OnBkBtnVisitVulPurposePage();
	void OnBkBtnExport();
	void OnListReSize(CRect rcWnd);
	void OnDownListReSize(CRect rcWnd);
public:
	// WM HANDLER
	LRESULT OnListBoxVulFixNotify(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnVulFixEventHandle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnListLinkClicked(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnScanStart(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnScanDone(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRepaireDone(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRichEditLink(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnStnClickedNavi(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	int FindListItem( int nID );
	void _ShutdownComputer(BOOL bReboot);
	void _DisplayRelateVulFixInfo( int nItem );
	void _SetScanProgress( int nPos );
	void _SetRepairProgress( int nPos );
	void _UpdateRepairTitle();
	void _EnableRelateCOM( BOOL bEnable );
	void _FillScanResult();
	
	bool _RepairSingle( int arrVulIds, T_VulListItemData* pItemData );
	void _EnableSelectedOpBtn(INT nMust, INT nSP, INT nOption);

	void _NotifyTrayIcon(LPCTSTR szText, INT nTimeOut, BOOL bDelayShow=TRUE);
	void _ViewDetail(INT nSelTab);
	void _UpdateViewDetailBtnsNumber( INT nFixed, INT nIgnored, INT nReplaced, INT nInvalid );
	void _PromptAutoShutdown();
	void _UpdateScanResultTitle( INT nTipIcon, LPCTSTR szTips );
	BOOL _ExportResult( LPCTSTR szFileName, T_ExportInfoArray &arrExportInfo );
	
public:
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN_VULFIX)
		// ϵͳ©�� 
		BK_NOTIFY_ID_COMMAND(IDC_DIV_VULFIX_RESULT_SPLITTER, OnBkBtnSwitchRelateInfo)
		
		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_RESULT_CHECK_ALL, OnBkBtnSelectAll)
		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_RESULT_UNCHECK_ALL, OnBkBtnSelectNone)		
		
		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_RESULT_CHECK_OPTIONAL, OnBkBtnSelectAllOptional)		

		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_RESULT_FIX, OnBkBtnBeginRepair)
		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_RESULT_RESCAN, OnBkBtnScan)
		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_RESULT_IGNORE, OnBkBtnIgnore)		
		
		// ɨ���� 
		BK_NOTIFY_ID_COMMAND(IDC_BTN_VULFIX_SCAN_CANCEL, OnBkBtnCancelScan)
		
		// ©���޸�
		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_REPAIR_TOP_CANCEL, OnBkBtnCancelRepair)
		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_REPAIR_TOP_BACKRUN, OnBkBtnRunBackground)

		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_REPAIR_TOP_REBOOT, OnBkBtnReboot)
		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_REPAIR_TOP_RESCAN, OnBkBtnScan)

		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_REPAIR_TOP_REBOOT2, OnBkBtnReboot)
		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_REPAIR_TOP_RESCAN2, OnBkBtnScan)
				
		BK_NOTIFY_ID_COMMAND(IDC_DIV_VULFIX_REPAIR_BTM_DONE_PART, OnBkBtnReboot)
		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_REPAIR_TOP_RESCAN3, OnBkBtnScan)
		BK_NOTIFY_ID_COMMAND(1052, OnBkBtnScan)	// �޸�, ��������ʧ��, ��ֱ����ʾ����ɨ��


		BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_ERROR_REPAIR, OnBkBtnErrorRepair)
		BK_NOTIFY_ID_COMMAND(1034, OnBkBtnVisitVulPurposePage)
		BK_NOTIFY_ID_COMMAND(2001, OnBkBtnExport)
		
		

		BK_NOTIFY_REALWND_RESIZED(IDC_LST_VULFIX_RESULT_LIST, OnListReSize)
		BK_NOTIFY_REALWND_RESIZED(IDC_LST_VULFIX_FIXING_LIST, OnDownListReSize)
		
		// �鿴�Ѻ���/�Ѱ�װ
		//BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_SHOW_IGNORED_DLG, OnBkBtnViewIgnored)	
		//BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_SHOW_INSTALLED_DLG, OnBkBtnViewInstalled)	
		//BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_SHOW_SUPERSEDED_DLG, OnBkBtnViewSupersede)
		//BK_NOTIFY_ID_COMMAND(IDC_LBL_VULFIX_SHOW_INVALID_DLG, OnBkBtnViewInvalid)
	BK_NOTIFY_MAP_END()
	
	BEGIN_MSG_MAP_EX(CBeikeVulfixHandler)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN_VULFIX)
		
		MESSAGE_HANDLER(WMH_SCAN_START, OnScanStart)
		MESSAGE_HANDLER(WMH_SCAN_DONE, OnScanDone)
		MESSAGE_HANDLER(WMH_REPAIR_DONE, OnRepaireDone)	
		MESSAGE_HANDLER(WMH_SCAN_SOFT_DONE, OnScanDone)
		MESSAGE_RANGE_HANDLER(WMH_VULFIX_BASE, WMH_VULFIX_BASE+EVulfix_Task_Error, OnVulFixEventHandle)
		MESSAGE_HANDLER(WMH_LISTEX_LINK, OnListLinkClicked)

		NOTIFY_ID_HANDLER(IDC_LST_VULFIX_RESULT_LIST, OnListBoxVulFixNotify)
		NOTIFY_HANDLER(IDC_TXT_VULFIX_VUL_DESCRIPTION, EN_LINK, OnRichEditLink)
		COMMAND_HANDLER(1016, STN_CLICKED, OnStnClickedNavi)
		//MSG_WM_CHAR(OnChar)
	END_MSG_MAP()
};

class CEmbeddedView : public CBkDialogViewImpl<CEmbeddedView>, 	public CIconAnimate<CEmbeddedView>
{
public:
	CBeikeVulfixHandler m_viewSoftVul;

	CEmbeddedView() : m_viewSoftVul(*this)
	{
	}

	void Init(HWND hMainWnd)
	{
		m_viewSoftVul.Init(hMainWnd, m_hWnd);
	}

public:
	BEGIN_MSG_MAP_EX(CEmbeddedView)
		//MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP(CBkDialogViewImpl<CEmbeddedView>)
		MSG_WM_TIMER(OnTimer)

		CHAIN_MSG_MAP_MEMBER(m_viewSoftVul)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
};


