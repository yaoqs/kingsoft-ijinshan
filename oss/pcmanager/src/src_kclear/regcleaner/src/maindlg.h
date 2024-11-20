//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////

#include <map>
#include <vector>
#include <string>
#include "resource.h"

#pragma warning(disable : 4244 4311 4312)
#include "listctrlex.h"
#include "skinprogress.h"
#include "kbitmapbutton.h"
#include "atlbuttenstatc.h"
#include "bitmapstatic.h"
#include "kuimulstatustree.h"
#include "kuitraversabletreectrl.h"
#include "hlhovercr.h"
#pragma warning(default : 4244 4311 4312)
#include "registrydata.h"
#include "ksclock.h"
#include "kscver.h"


//////////////////////////////////////////////////////////////////////////

#define WM_MSG_BASE				(WM_USER + 3888)
#define WM_SCAN_CALLBACK		(WM_MSG_BASE + 1)
#define WM_SCANTYPE_CALLBACK	(WM_MSG_BASE + 2)
#define	WM_SCAN_END				(WM_MSG_BASE + 3)
#define WM_CLEAN_END			(WM_MSG_BASE + 4)
#define WM_CLEANTYPE_CALLBACK	(WM_MSG_BASE + 5)
#define	WM_OWN_TIMER			(WM_MSG_BASE + 6)
#define	WM_OWN_MSGBOX			(WM_MSG_BASE + 7)

//////////////////////////////////////////////////////////////////////////

#define	MAIN_WIDTH					790
#define	MAIN_HEIGHT					425

//////////////////////////////////////////////////////////////////////////


typedef CListCtrlDataEx< CRegistryData::SCAN_RESULT* > CListCtrlExLP;

typedef LRESULT (CALLBACK *LPWNDPROC)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class CMainDlg: public CDialogImpl<CMainDlg>
{
public:
	CMainDlg();
	~CMainDlg();

	enum {IDD = IDD_REGCLEANER};

private:
    enum SC_STATUS{SCS_INVALID, SCS_IDLE, SCS_SCAN, SCS_SCANNED, SCS_CLEAN, SCS_CLEANED};

    CKscVersion			m_AppVerModule;

    SC_STATUS			m_scStatus;			// ��ǰ״̬
    CRegistryData		m_rdScanner;		// ɨ����
    int					m_nRegistryCount;	// ɨ�赽��ע�������

    bool				m_bParentKsafe;		// �������Ƿ�Ϊ��ʿ
    DWORD				m_dwCleanTickCount;	// �ϴ������ʱ��. ��ɨ�����ϴ�����ļ���϶̣�����ɨ�衣

    CImageList											m_imlTreeIcons;
    KUITraversableTreeCtrl<KUIMulStatusTree>			m_tree;
    typedef std::map<CRegistryData::REG_SCAN_TYPE, HTREEITEM>	TREE_ROOT_MAP;
    TREE_ROOT_MAP										m_TreeRootMap;			// ���и�Ԫ�ص��б�
    TREE_ROOT_MAP										m_SelectedRootMap;		// ��ѡ�еĸ�Ԫ�ص��б�
    TREE_ROOT_MAP::iterator								m_iterLastItem;			// ָ���������ĸ�Ԫ�أ�TreeRootMap��iter
    std::map<int,int> m_bSelectMap;
    CString										m_strCacheFile;

    CBitmapStatic		m_bmpTips;
    CImageList			m_imgListTips;
    CBitmapStatic		m_bmpLoading;
    CImageList			m_imgListLoading;
    //CStaticBtn			m_txtDesc;
    tstring				m_strTxtDesc;
    LPWNDPROC			m_lpTxtDescProc;
    bool				m_bTxtDescPaintClr;
    HWND				m_txtDesc;
    CSkinProgress		m_ScanCleanProgress;

    HWND				m_chkSelectAll;		// ȫѡ
    HWND				m_txtSelAll;		
    CHyperLinkHoverCr	m_btnDefault;		// �Ƽ�ѡ��
    KBitmapButton		m_btnStartScan;		// ��ʼɨ�谴ť
    CListCtrlExLP		m_ListCtrl;	

    KBitmapButton		m_btnClean;			// ��������
    KBitmapButton		m_btnStopScan;		// ����ɨ��
    CHyperLinkHoverCr	m_btnHistory;		// �鿴��ʷ

    CRect				m_rcMainClient;		// �����ڵĳߴ�
    CRect				m_rcTopArea;		// ������������ĳߴ�
    CRect				m_rcBtbArea;		// ���水ť���ĳߴ�

    bool				m_bStop;			// ������ֹͣ��ť
    HANDLE				m_hScanThread;		// ɨ���߳̾��
    HANDLE            m_hCleanThread;    //  �����߳̾��
    HANDLE				m_hOwnTimerThread;	// OWN_TIMER�߳�

    KLock				m_lockTips;			// Tips������
    KLock				m_lockTree;			// Tree������

    typedef	std::vector<CRegistryData::SCAN_RESULT*>	VSR;
    typedef std::map<CRegistryData::REG_SCAN_TYPE, VSR>	MTRP;
    MTRP				m_scanResultArray;	// ɨ��ʱ��ʱ����ÿ����������

    bool				m_bSelectedRoot;	
    bool				m_bSelectedChild;
    bool				m_bSelectedUnScaned;
    bool				m_bSelectedCleaned;
    bool				m_bSelectedScanned;
    bool				m_bSelectedUnCleaned;

public:
	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_SCAN_CALLBACK, OnScanCallback);
		MESSAGE_HANDLER(WM_SCANTYPE_CALLBACK, OnScanTypeCallback);
		MESSAGE_HANDLER(WM_CLEANTYPE_CALLBACK, OnCleanTypeCallback);
		MESSAGE_HANDLER(WM_SCAN_END, OnScanEnd);
		MESSAGE_HANDLER(WM_CLEAN_END, OnCleanEnd);
		MESSAGE_HANDLER(WM_KAN_NOTIFY_TREE_CHECKED_CHANGE, OnTreeItemCheckChanged);
		MESSAGE_HANDLER(WM_OWN_TIMER, OnOwnTimer);
		MESSAGE_HANDLER(WM_OWN_MSGBOX, OnOwnMsgBox)

		MSG_WM_SIZE(OnSize)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CTLCOLORSTATIC(OnCtlColorStatic)
		MSG_WM_TIMER(OnScanCleanTimer)

		COMMAND_ID_HANDLER(IDC_BTN_SCAN, OnScanClick)
		COMMAND_ID_HANDLER(IDC_BTN_CLEAN, OnCleanClick)
		COMMAND_ID_HANDLER(IDC_BTN_STOP, OnStopClick)
		COMMAND_ID_HANDLER(IDC_BACKUP, OnBackupClick)
		COMMAND_ID_HANDLER(IDC_DEFAULT, OnSelectDefaultClick)
		COMMAND_ID_HANDLER(IDC_SELECTALL, OnSelectAllClick)
		
		NOTIFY_HANDLER(IDC_LIST, LCN_LEFTCLICK, OnListSelect)
		NOTIFY_HANDLER(IDC_TREE, TVN_GETINFOTIP, OnTreeItemInfoTip)

		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

private:
	void	OnClose();
	void	OnPaint(HDC hDC);
	void	OnSize(UINT wParam, const _WTYPES_NS::CSize& size);
	void	OnScanCleanTimer(UINT_PTR nIDEvent);

	LRESULT	OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnCtlColorStatic(HDC hDC, HWND hWnd);
	LRESULT	OnScanCallback(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT	OnScanEnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT	OnScanTypeCallback(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT	OnCleanTypeCallback(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT	OnCleanEnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT	OnTreeItemCheckChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT	OnOwnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT	OnOwnMsgBox(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

	LRESULT OnScanClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled);
	LRESULT OnCleanClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled);
	LRESULT	OnStopClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled);
	LRESULT	OnBackupClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled);
	LRESULT	OnSelectAllClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled);
	LRESULT	OnSelectDefaultClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled);

	LRESULT OnListClick(int idCtrl, LPNMHDR pnmh, BOOL &bHandled);
	LRESULT OnListSelect(int idCtrl, LPNMHDR pnmh, BOOL &bHandled);
	LRESULT	OnTreeItemInfoTip(int idCtrl, LPNMHDR pnmh, BOOL &bHandled);

	BOOL	SetMainWndSize();
	void	InitControl();
	void	InitListCtrl();
	int		GetTypeIconIndex(CRegistryData::REG_SCAN_TYPE rstType);

	void	SetControlPos();

	void	SetScStatus(SC_STATUS status);
	HRESULT	StartScan();

	void	CheckTreeSelectStatus();
	void	EnumSelectedTreeItem();
	void	ClearAllTreeItem();
	void	SetScannedTreeItem();
	HRESULT	SetCleanedTreeItem();

	void	SelectDefaultItems();
    bool    CalcChildNum(HTREEITEM hParent, int& nNum);
	bool	CalcSelectedChildNum(HTREEITEM hParent, int& nNum);
    bool    DeleteAllChild(HTREEITEM hParent);
	bool	DeleteSelectedChild(HTREEITEM hParent);

	void	AddTypeScanData(CRegistryData::REG_SCAN_TYPE);

	static DWORD WINAPI	ScanThreadProc(LPVOID lpParameter);
	static DWORD WINAPI	CleanThreadProc(LPVOID lpParameter);
	static DWORD WINAPI	OwnTimerThreadProc(LPVOID lpParameter);

	static bool	ScanCallback(CRegistryData::SCAN_RESULT* result, LPVOID lpParam);
	static bool	ScanTypeCallBack(CRegistryData::REG_SCAN_TYPE rstType, LPVOID lpParam);
	static bool	CleanTypeCallBack(CRegistryData::REG_SCAN_TYPE rstType, LPVOID lpParam);

	static LRESULT CALLBACK TxtDescWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	
};

