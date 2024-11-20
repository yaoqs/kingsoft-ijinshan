//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "guidef.h"
#include "maindlg.h"
#include "regbackupdlg.h"
#include "kscver.h"
#include "kuimsgbox.h"
#include "misc/IniEditor.h"
#include "stubbornregs.h"
#include "kscbase/kscsys.h"

//////////////////////////////////////////////////////////////////////////

#define LIST_COLUMN_WIDTH_OFFSET		((4 * 100) + 26)
#define	WND_LEFT_MARGIN					5
#define WND_RIGHT_MARGIN				5
#define WND_TOP_MARGIN					5
#define WND_BOTTOM_MARGIN				10

#define	PROGRESS_MAX_RANGE				100			// ��10sɨ��ʱ�����
#define TIMER_ID_SCAN					0x1001
#define TIMER_ID_CLEAN					0x1002


static CMainDlg*	gs_lpThisDlg = NULL;

//////////////////////////////////////////////////////////////////////////

CMainDlg::CMainDlg() :
	m_bStop(false), m_hScanThread(NULL), m_hCleanThread(NULL), m_scStatus(CMainDlg::SCS_IDLE),
	m_nRegistryCount(0), m_bParentKsafe(false), m_dwCleanTickCount(0),
	m_hOwnTimerThread(NULL), m_lpTxtDescProc(NULL), m_bTxtDescPaintClr(false)
{
	gs_lpThisDlg = this;
	m_AppVerModule.Init(NULL);
	wchar_t szAppPath[MAX_PATH] = { 0 };
	GetModuleFileNameW(NULL, szAppPath, MAX_PATH);
	PathRemoveFileSpecW(szAppPath);
	::PathAppend(szAppPath,L"cfg\\lastrecord.inf");
	m_strCacheFile = szAppPath;
	CStubbornRegs::Instance().Init();
}

//////////////////////////////////////////////////////////////////////////

CMainDlg::~CMainDlg()
{
    if ( m_hScanThread != NULL )
    {
        ::CloseHandle(m_hScanThread);
        m_hScanThread = NULL;
    }
    if(NULL != m_hCleanThread)
    {
        CloseHandle(m_hCleanThread);
        m_hCleanThread = NULL;
    }
	m_AppVerModule.UnInit();

	IniEditor IniEdit;
	IniEdit.SetFile(m_strCacheFile.GetBuffer());

	std::map<int,int>::iterator iter = m_bSelectMap.begin();
	for (; iter!=m_bSelectMap.end(); iter++)
	{
		TCHAR szFlag[32] = {0};
		_itow_s(iter->first,szFlag,32);
		IniEdit.WriteDWORD(L"kclear_checke_reg",szFlag,iter->second);
	}

	CStubbornRegs::Instance().UnInit();
}

//////////////////////////////////////////////////////////////////////////

LRESULT CMainDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	HWND	hwndParent = GetParent();
	
	// �жϸ������Ƿ�Ϊ��ʿ
	if ( ::IsWindow(hwndParent) )
	{
		TCHAR	szClass[40] = {};

		::GetClassName(hwndParent, szClass, 40);
		if ( ::_tcsnicmp(szClass, TEXT("KscTool"), 7) == 0 )
			m_bParentKsafe = true;
	}

	// ��ʼ���ؼ�
	SetMainWndSize();
	InitControl();
	InitListCtrl();
	SetControlPos();

	// �Զ���ʼɨ��
	//StartScan();
	SetScStatus(CMainDlg::SCS_IDLE);

	bHandled = TRUE;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnPaint(HDC hDC)
{
	CPaintDC	PaintDC(m_hWnd);
	CRect		WndRect;
	CRect		TempRect;
	CBrush		FrameBrush;

	GetClientRect(WndRect);
	PaintDC.FillSolidRect(WndRect, DIALOG_BK_COLOR);
}


void CMainDlg::OnSize(UINT wParam, const _WTYPES_NS::CSize& size)
{
	if ( !m_bParentKsafe )
	{
		return;
	}

	switch( wParam )
	{
	case SIZE_MINIMIZED:
		return;
		break;
	default:
		SetMainWndSize();
		SetControlPos();
		break;
	}
}


//////////////////////////////////////////////////////////////////////////

LRESULT CMainDlg::OnListClick(int idCtrl, LPNMHDR pnmh,  BOOL &bHandled)
{
	CListNotify*				pNotify = (CListNotify *)pnmh;
	UINT						unTemp = 0;
	CRegistryData::SCAN_RESULT*	lpResult = NULL;

	if ( pNotify->m_nItem == NULL_ITEM )
		return 0;
	
	unTemp = m_ListCtrl.GetItemFormat(pNotify->m_nItem, 0);
	if ( unTemp & ITEM_FORMAT_FULL_LINE )
	{
		return 0;
	}

	return 0;
}


LRESULT CMainDlg::OnListSelect(int idCtrl, LPNMHDR pnmh,  BOOL &bHandled)
{
	CListNotify*				pNotify = (CListNotify *)pnmh;
	UINT						unTemp = 0;
	CRegistryData::SCAN_RESULT*	lpResult = NULL;

	if ( pNotify->m_nItem == NULL_ITEM )
		return 0;

	// ����Ƿ�ѡ���˵�ѡ��
	unTemp = m_ListCtrl.GetItemFormat(pNotify->m_nItem, 0);
	if ( !(unTemp & ITEM_FORMAT_CHECKBOX) ) {
		return 0;
	}
	
	// �����Ƿ����
	m_ListCtrl.GetItemData(pNotify->m_nItem, lpResult);
	if ( lpResult == NULL )
		return 0;
	
	lpResult->SetToClean( m_ListCtrl.GetItemCheck(pNotify->m_nItem, 0) ? true : false );
	return 0;
}


//////////////////////////////////////////////////////////////////////////

LRESULT CMainDlg::OnCtlColorStatic(HDC hDC, HWND hWnd)
{
	HBRUSH		hbr = NULL;
	CRect		rc;

	::GetClientRect(hWnd, rc);
	hbr = ::CreateSolidBrush(DIALOG_BK_COLOR);
	::FillRect(hDC, rc, hbr);
	::DeleteObject(hbr);

	return (LRESULT)GetStockObject(NULL_BRUSH);
}

//////////////////////////////////////////////////////////////////////////

void CMainDlg::OnClose()
{	
	
	EndDialog(0);
}


void CMainDlg::OnScanCleanTimer(UINT_PTR nIDEvent)
{
	int				nPos = 0;
	int				nStep = 1;
	static int		nTimer = 0;

	if ( nIDEvent != TIMER_ID_CLEAN && nIDEvent != TIMER_ID_SCAN )
		return;

	// ���½�����
	/*nPos = m_ScanCleanProgress.GetPos();
	nStep = m_ScanCleanProgress.GetStep();
	m_ScanCleanProgress.SetPos((nPos >= PROGRESS_MAX_RANGE - 1 - nStep) ? (PROGRESS_MAX_RANGE - 1 - nStep) : nPos + nStep);
	*/

	// ���¶���
	m_bmpLoading.mnIndex = (nTimer++ % 8);
	m_bmpLoading.ShowWindow(SW_SHOW);
	m_bmpLoading.Invalidate(TRUE);

	// ����������
	{
		KAutoLock	lockTips(m_lockTips);
		::SetWindowText(m_txtDesc, m_strTxtDesc.c_str());
	}
}


//////////////////////////////////////////////////////////////////////////

BOOL CMainDlg::SetMainWndSize()
{
	HWND		hwndParent = GetParent();
	CRect		rcParent;
	int			nWidth = 0, nHeight = 0;
	
	// �޸Ĵ��ڳߴ�
	if ( ::IsWindow(hwndParent) )
	{
		::GetClientRect(hwndParent, rcParent);

		if ( m_bParentKsafe )
		{
			nWidth = rcParent.Width();
			nHeight = rcParent.Height();
		}
		else
		{
			nWidth = MAIN_WIDTH;
			nHeight = MAIN_HEIGHT;
		}
	}
	else
	{
		nWidth = MAIN_WIDTH;
		nHeight = MAIN_HEIGHT;
	}
	
	SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOZORDER);
	GetClientRect(m_rcMainClient);

	return TRUE;
}


void CMainDlg::InitControl()
{
	CRect		rc, rcScan;
	int			nVScrollWidth = 0;

	nVScrollWidth = ::GetSystemMetrics(SM_CXVSCROLL);

	// ��ʾͼ��
	m_bmpTips.SubclassWindow(GetDlgItem(IDC_PIC_TIPS));
	m_imgListTips.CreateFromImage(IDB_TIPS, 15, 8, RGB(255, 0, 255), IMAGE_BITMAP, LR_CREATEDIBSECTION);
	m_bmpTips.mpImageList = &m_imgListTips;
	m_bmpTips.mnIndex = 0;
	m_bmpTips.ShowWindow(SW_HIDE);

	// ��̬ͼ��
	m_bmpLoading.SubclassWindow(GetDlgItem(IDC_PIC_LOADING));
	m_imgListLoading.CreateFromImage(IDB_LOADING, 16, 8, RGB(255, 0, 255), IMAGE_BITMAP, LR_CREATEDIBSECTION);
	m_bmpLoading.mpImageList = &m_imgListLoading;
	m_bmpLoading.mnIndex = 0;
	m_bmpLoading.ShowWindow(SW_HIDE);

	// �޸�ɨ���ı���ʾ
	m_txtDesc = GetDlgItem(IDC_TXT_DESC);
	m_lpTxtDescProc = (LPWNDPROC)(LPVOID)(ULONG_PTR)::SetWindowLong(m_txtDesc, GWL_WNDPROC, (LONG)(LONG_PTR)&TxtDescWndProc);
	/*m_txtDesc.SubclassWindow(GetDlgItem(IDC_TXT_DESC));
	m_txtDesc.SetWindowText(L"�뵥��\"����ɨ��\"��ť��ʼɨ�裡");
	m_txtDesc.SetTransparent(TRUE);
	m_txtDesc.SetFontName(TEXT("Microsoft Sans Serif"));
	m_txtDesc.SetTextColor(RGB(0, 0, 0));
	m_txtDesc.ShowWindow(SW_SHOW);*/
	
	// ������
	m_ScanCleanProgress.SubclassWindow(GetDlgItem(IDC_PROGRESS), IDB_PROGRESS);
	m_ScanCleanProgress.ShowWindow(SW_HIDE);
	
	// ȫѡ
	m_chkSelectAll = GetDlgItem(IDC_SELECTALL);
	m_txtSelAll = GetDlgItem(IDC_SELALL_T);

	// �Ƽ�ѡ��
	SET_HYPERCR_LINK(m_btnDefault, IDC_DEFAULT);

	// ��ʷ
	SET_HYPERCR_LINK(m_btnHistory, IDC_BACKUP);

	// ���໯ͼƬ��ť: ��ʼɨ��
	m_btnStartScan.SubclassWindow(GetDlgItem(IDC_BTN_SCAN));
	m_btnStartScan.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
	m_btnStartScan.SetBtnImages(IDB_BTNNORMAL_B, IDB_BTNDOWN_B, IDB_BTNHOVER_B, IDB_BTNDISABLE_B);
	m_btnStartScan.SetImages(0, 1, 2, 3);
	m_btnStartScan.SetCursor((UINT)(ULONG_PTR)IDC_HAND);
	m_btnStartScan.SetTitle(IDS_SCAN);
	m_btnStartScan.SetFont(TEXT("����"), 90);
	
	// ֹͣ
	m_btnStopScan.SubclassWindow(GetDlgItem(IDC_BTN_STOP));
	m_btnStopScan.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
	m_btnStopScan.SetBtnImages(IDB_BTNNORMAL_B, IDB_BTNDOWN_B, IDB_BTNHOVER_B, IDB_BTNDISABLE_B);
	m_btnStopScan.SetImages(0, 1, 2, 3);
	m_btnStopScan.SetCursor((UINT)(ULONG_PTR)IDC_HAND);
	m_btnStopScan.SetTitle(IDS_STOP);
	::ShowWindow(m_btnStopScan, SW_SHOW);
	m_btnStartScan.SetFont(TEXT("����"), 90);

	// ���
	m_btnClean.SubclassWindow(GetDlgItem(IDC_BTN_CLEAN));
	m_btnClean.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
	m_btnClean.SetBtnImages(IDB_BTNNORMAL_B, IDB_BTNDOWN_B, IDB_BTNHOVER_B, IDB_BTNDISABLE_B);
	m_btnClean.SetImages(0, 1, 2, 3);
	m_btnClean.SetCursor((UINT)(ULONG_PTR)IDC_HAND);
	m_btnClean.SetTitle(IDS_CLEAN);
	m_btnStartScan.SetFont(TEXT("����"), 90);
}


//////////////////////////////////////////////////////////////////////////

void CMainDlg::InitListCtrl()
{
	CString		sText;
	CRect		rcClient;
	COLORREF	color = RGB(222, 239, 214);

	m_ListCtrl.RegisterClass();
	m_ListCtrl.SubclassWindow(GetDlgItem(IDC_LIST));
	m_ListCtrl.ShowWindow(SW_HIDE);

	if ( m_bParentKsafe )
		color = RGB(185, 219, 255);
	else
		color = RGB(222, 239, 214);
	m_ListCtrl.SetSelectedItemColor(color);

	sText = TEXT("���");
	m_ListCtrl.AddColumn(sText, 160);

	sText = TEXT("ע���λ��");
	m_ListCtrl.AddColumn(sText, 350);

	sText = TEXT("��������");
	m_ListCtrl.AddColumn(sText, 258);

	// TreeView
	WTL::CBitmap	bmIconList;
	bmIconList.LoadBitmap( IDB_LISTITEMS );
	m_imlTreeIcons.Create( 16, 16, ILC_COLOR32 | ILC_MASK, 12, 1 );
	m_imlTreeIcons.Add( bmIconList, RGB( 255, 0, 255 ) );

	m_tree.SubclassWindow( GetDlgItem( IDC_TREE ) );
	m_tree.SetImageList( m_imlTreeIcons, TVSIL_NORMAL );
	m_tree.SetItemHeight( 20 );

	// ���Ԫ��
	HTREEITEM	hTreeItem = NULL;
	for( int i = CRegistryData::RST_BEGIN; i < (int)CRegistryData::RST_END; ++i )
	{
		hTreeItem = m_tree.InsertItem( 
			CRegistryData::GetTitle((CRegistryData::REG_SCAN_TYPE)i), 
			GetTypeIconIndex((CRegistryData::REG_SCAN_TYPE)i), GetTypeIconIndex((CRegistryData::REG_SCAN_TYPE)i),
			NULL, 
			NULL,  
			KUIMulStatusTree::EM_TVIS_CHECK);

		m_tree.SetItemData( hTreeItem, -1 );
		m_TreeRootMap[(CRegistryData::REG_SCAN_TYPE)i] = hTreeItem;
	}

	// ʹ��Ĭ������
	if(::PathFileExists(m_strCacheFile.GetBuffer()))
	{
		IniEditor IniEdit;
		IniEdit.SetFile(m_strCacheFile.GetBuffer());

		TREE_ROOT_MAP::iterator	iter;
		int checkNum = 0;

		for ( iter = m_TreeRootMap.begin(); iter != m_TreeRootMap.end(); ++iter )
		{
			int nSelect = 0;
			TCHAR szFlag[32] = {0};
			_itow_s(iter->first,szFlag,32);
			BOOL bOk = IniEdit.ReadDWORD(L"kclear_checke_reg",szFlag,nSelect);
			if(!bOk)
				goto _exit_;
			if (1==nSelect)
			{
				m_tree.SetCheck(iter->second, KUIMulStatusTree::EM_TVIS_CHECK);
				checkNum ++;
			}
			else
				m_tree.SetCheck(iter->second, KUIMulStatusTree::EM_TVIS_UNCHECK);
		}


		if(checkNum == 10)
		{
			::SendMessage(m_chkSelectAll, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
		}
		else 
			::SendMessage(m_chkSelectAll, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);


	}
	else
	{
	_exit_:
		SelectDefaultItems();
	}
}


void CMainDlg::SetControlPos()
{
	CRect		rc, rcLast;
	int			nVScrollWidth = 0;
	int			nBmpWidth = 72, nBmpHeight = 26;
	int			nLastCtrlLeft = 0;
	const int	nLeftPadding = 10, nRightPadding = 10;

	if ( !::IsWindow(m_bmpTips) )
		return;

	nVScrollWidth = ::GetSystemMetrics(SM_CXVSCROLL);

	// ��ʾͼ��
	m_bmpTips.SetWindowPos(NULL, nLeftPadding, 8, 15, 15, SWP_NOZORDER);
	m_bmpTips.GetWindowRect(rc);
	ScreenToClient(rc);

	// ��̬ͼ��
	m_bmpLoading.SetWindowPos(NULL, nLeftPadding, 8, 16, 16, SWP_NOZORDER);

	rcLast = rc;
	::GetWindowRect(m_txtDesc, rc);
	ScreenToClient(rc);
	::SetWindowPos(m_txtDesc, NULL, nLeftPadding + rcLast.Width() + 5, 10, m_rcMainClient.Width() - 50, rc.Height(), 
		SWP_NOZORDER);
	::GetWindowRect(m_txtDesc, m_rcTopArea);
	ScreenToClient(m_rcTopArea);

	// ������
	m_ScanCleanProgress.GetWindowRect(rc);
	ScreenToClient(rc);
	m_ScanCleanProgress.MoveWindow(m_rcTopArea.left + 100, m_rcTopArea.top, 
		(m_rcMainClient.Width() - 200 > 0) ? (m_rcMainClient.Width() - 200) : 100, 16);

	// ������ͼ
	GetClientRect(rc);
	::SetWindowPos(m_tree, NULL, nLeftPadding, 30, 
		rc.Width() - nLeftPadding - nRightPadding, 
		rc.Height() - 30 - 35,
		SWP_NOZORDER);

	// ȫѡ
	::GetWindowRect(m_chkSelectAll, rc);
	ScreenToClient(rc);
	nLastCtrlLeft = nLeftPadding;
	::SetWindowPos(m_chkSelectAll, NULL, nLastCtrlLeft, 
		m_rcMainClient.bottom - 13 - 9,
		rc.Width(), 13, SWP_NOSIZE | SWP_NOZORDER);
	::GetWindowRect(m_chkSelectAll, rc);
	ScreenToClient(rc);

	::SetWindowPos(m_txtSelAll, NULL, nLeftPadding + rc.Width() + 3, rc.top - 1, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	rc.right += 26;

	// �Ƽ�
	rcLast = rc;
	::GetWindowRect(m_btnDefault, rc);
	ScreenToClient(rc);
	nLastCtrlLeft += rcLast.Width() + 15;
	::SetWindowPos(m_btnDefault, NULL, nLastCtrlLeft, 
		m_rcMainClient.bottom - 10 - rc.Height(),
		rc.Width(), rc.Height(), SWP_NOZORDER);

	// ��ʷ��ť
	rcLast = rc;
	::GetWindowRect(m_btnHistory, rc);
	ScreenToClient(rc);
	nLastCtrlLeft += rcLast.Width() + 10;
	::SetWindowPos(m_btnHistory, NULL,  nLastCtrlLeft, 
		m_rcMainClient.bottom - 10 - rc.Height(), 
		rc.Width(), rc.Height(), SWP_NOZORDER);

	// �������
	m_btnClean.GetWindowRect(m_rcBtbArea);
	ScreenToClient(m_rcBtbArea);
	m_btnClean.GetWindowRect(rc);
	ScreenToClient(rc);
	::SetWindowPos(m_btnClean, NULL, 0, 0, nBmpWidth, nBmpHeight, SWP_NOMOVE | SWP_NOZORDER);

	m_btnClean.GetWindowRect(rc);
	ScreenToClient(rc);
	nLastCtrlLeft =  m_rcMainClient.right - nRightPadding - rc.Width();
	::SetWindowPos(m_btnClean, NULL,  nLastCtrlLeft, 
		m_rcMainClient.bottom - 4 - rc.Height(), 
		0, 0, SWP_NOSIZE | SWP_NOZORDER);

	// ֹͣɨ��
	m_btnStopScan.GetWindowRect(rc);
	ScreenToClient(rc);
	::SetWindowPos(m_btnStopScan, NULL, 0, 0, nBmpWidth, nBmpHeight, SWP_NOMOVE | SWP_NOZORDER);

	m_btnStopScan.GetWindowRect(rc);
	ScreenToClient(rc);
	nLastCtrlLeft -= 10 + rc.Width();
	::SetWindowPos(m_btnStopScan, NULL, nLastCtrlLeft, 
		m_rcMainClient.bottom - 4 - rc.Height(), 
		0, 0, SWP_NOSIZE | SWP_NOZORDER);

	// ��ʼɨ��
	::GetWindowRect(m_btnStartScan, rc);
	ScreenToClient(rc);
	::SetWindowPos(m_btnStartScan, NULL, 0, 0, nBmpWidth, nBmpHeight, SWP_NOMOVE | SWP_NOZORDER);

	::GetWindowRect(m_btnStartScan, rc);
	ScreenToClient(rc);
	//nLastCtrlLeft =  m_rcMainClient.right - nRightPadding - rc.Width();
	//nLastCtrlLeft -= 10 + rc.Width();
	::SetWindowPos(m_btnStartScan, NULL, nLastCtrlLeft, 
		m_rcMainClient.bottom - 4 - rc.Height(), 
		0, 0, SWP_NOSIZE | SWP_NOZORDER);

	

	
}


void CMainDlg::SetScStatus(SC_STATUS status)
{
	if ( status < CMainDlg::SCS_IDLE || status > CMainDlg::SCS_CLEANED )
		return;

	// ���浱ǰ״̬
	m_scStatus = status;

	if ( status == CMainDlg::SCS_IDLE )
	{
		CRect		rc;

		m_bmpTips.mnIndex = 3;
		m_bmpTips.ShowWindow(SW_SHOW);
		m_bmpLoading.ShowWindow(SW_HIDE);

		::SetWindowText(m_txtDesc, TEXT("����ע���ɼӿ�ϵͳ�ٶȣ����鶨������������֮ǰ��ע�����Զ����ݣ��Ա�ָ���"));
		::ShowWindow(m_txtDesc, SW_SHOW);
		::GetWindowRect(m_txtDesc, rc);
		::SetWindowPos(m_txtDesc, NULL, 0, 0, m_rcMainClient.Width() - 50, rc.Height(), SWP_NOZORDER | SWP_NOMOVE);

		m_ScanCleanProgress.ShowWindow(SW_HIDE);
		m_btnClean.ShowWindow(SW_SHOW);
		m_btnHistory.ShowWindow(SW_SHOW);
		m_btnStartScan.ShowWindow(SW_SHOW);
		m_btnStopScan.ShowWindow(SW_HIDE);

		::EnableWindow(m_chkSelectAll, TRUE);
		::EnableWindow(m_txtSelAll, TRUE);
		::EnableWindow(m_btnDefault, TRUE);
		
		m_btnClean.EnableWindow(FALSE);
		m_btnStartScan.EnableWindow(TRUE);

		m_tree.EnableCheck(TRUE);
		return;
	}

	if ( status == CMainDlg::SCS_SCAN )
	{
		CRect	rc;

		m_bmpTips.ShowWindow(SW_HIDE);
		m_bmpLoading.ShowWindow(SW_SHOW);
		
		m_bTxtDescPaintClr = false;
		m_strTxtDesc = TEXT("����ɨ��...");
		::SetWindowText(m_txtDesc, TEXT("����ɨ��..."));
		::ShowWindow(m_txtDesc, SW_SHOW);
		::GetWindowRect(m_txtDesc, rc);
		::SetWindowPos(m_txtDesc, NULL, 0, 0, m_rcMainClient.Width() - 50, rc.Height(), SWP_NOZORDER | SWP_NOMOVE);
		::InvalidateRect(m_txtDesc, NULL, FALSE);
		
		m_ScanCleanProgress.SetRange(0, PROGRESS_MAX_RANGE);
		m_ScanCleanProgress.SetStep(2);
		m_ScanCleanProgress.SetPos(0);
		m_ScanCleanProgress.ShowWindow(SW_HIDE);
		
		//m_hOwnTimerThread = ::CreateThread(NULL, 0, &CMainDlg::OwnTimerThreadProc, this, 0, NULL);
		SetTimer(TIMER_ID_SCAN, 100, NULL);

		//m_btnClean.ShowWindow(SW_HIDE);
		m_btnHistory.ShowWindow(SW_HIDE);
		m_btnStartScan.ShowWindow(SW_HIDE);
		m_btnStopScan.SetTitle(IDS_STOP);
		m_btnStopScan.ShowWindow(SW_SHOW);

		::EnableWindow(m_chkSelectAll, FALSE);
		::EnableWindow(m_txtSelAll, FALSE);
		::EnableWindow(m_btnDefault, FALSE);
		::EnableWindow(m_btnClean, FALSE);

		m_tree.EnableCheck(FALSE);

		return;
	}

	if ( status == CMainDlg::SCS_SCANNED )
	{
		CString		sText;
		CRect		rc;

		// ���ٹ�������ʱ��
		/*if ( m_hOwnTimerThread != NULL )
		{
			::TerminateThread(m_hOwnTimerThread, 0);
			::CloseHandle(m_hOwnTimerThread);
			m_hOwnTimerThread = NULL;
		}*/
		KillTimer(TIMER_ID_SCAN);

		m_ScanCleanProgress.ShowWindow(SW_HIDE);
		m_bmpLoading.ShowWindow(SW_HIDE);

		if ( m_nRegistryCount > 0 )
		{
			m_bmpTips.mnIndex = 0;
			sText.Format(L"ɨ������ɣ�������%d������ע����������������", m_nRegistryCount);
			m_bTxtDescPaintClr = true;

			::EnableWindow(m_btnClean, TRUE);
			::EnableWindow(m_btnStartScan, TRUE);
		}
		else 
		{
			m_bmpTips.mnIndex = 2;
			sText = TEXT("����ָ����ѡ����δ���ֿ������ע����");

			::EnableWindow(m_btnClean, TRUE);
			::EnableWindow(m_btnStartScan, TRUE);
		}

		m_bmpTips.ShowWindow(SW_SHOW);
		
		::SetWindowText(m_txtDesc, sText);
		::ShowWindow(m_txtDesc, SW_SHOW);
		::GetWindowRect(m_txtDesc, rc);
		::SetWindowPos(m_txtDesc, NULL, 0, 0, m_rcMainClient.Width() - 50, rc.Height(), SWP_NOZORDER | SWP_NOMOVE);
		::InvalidateRect(m_txtDesc, NULL, FALSE);

		m_btnClean.ShowWindow(SW_SHOW);
		m_btnHistory.ShowWindow(SW_SHOW);
		m_btnStartScan.SetTitle(IDS_RESCAN);
		m_btnStartScan.ShowWindow(SW_SHOW);
		m_btnStopScan.ShowWindow(SW_HIDE);

		::EnableWindow(m_chkSelectAll, TRUE);
		::EnableWindow(m_txtSelAll, TRUE);
		::EnableWindow(m_btnDefault, TRUE);

		m_tree.EnableCheck(TRUE);
		return;
	}

	if ( status == CMainDlg::SCS_CLEAN )
	{
		CRect		rc;

		m_bmpTips.ShowWindow(SW_HIDE);
		m_bmpLoading.ShowWindow(SW_SHOW);

		m_bTxtDescPaintClr = false;
		m_strTxtDesc = TEXT("��������...");
		::SetWindowText(m_txtDesc, TEXT("��������..."));
		::ShowWindow(m_txtDesc, SW_SHOW);
		::GetWindowRect(m_txtDesc, rc);
		::SetWindowPos(m_txtDesc, NULL, 0, 0, m_rcMainClient.Width() - 50, rc.Height(), SWP_NOZORDER | SWP_NOMOVE);
		::InvalidateRect(m_txtDesc, NULL, FALSE);

		m_ScanCleanProgress.SetRange(0, PROGRESS_MAX_RANGE);
		m_ScanCleanProgress.SetPos(0);
		m_ScanCleanProgress.SetStep(1);
		m_ScanCleanProgress.ShowWindow(SW_HIDE);
		SetTimer(TIMER_ID_CLEAN, 200, NULL);

		//m_btnClean.ShowWindow(SW_HIDE);
		m_btnStartScan.ShowWindow(SW_HIDE);
		m_btnHistory.ShowWindow(SW_HIDE);
		m_btnStopScan.SetTitle(IDS_STOPCLEAN);
		m_btnStopScan.ShowWindow(SW_SHOW);

		::EnableWindow(m_chkSelectAll, FALSE);
		::EnableWindow(m_txtSelAll, FALSE);
		::EnableWindow(m_btnDefault, FALSE);
		::EnableWindow(m_btnClean, FALSE);

		m_tree.EnableCheck(FALSE);

		return;
	}

	if ( status == CMainDlg::SCS_CLEANED )
	{
		CRect		rc;

		// ���ٹ�������ʱ��
		m_ScanCleanProgress.ShowWindow(SW_HIDE);
		KillTimer(TIMER_ID_CLEAN);

		m_bmpTips.mnIndex = 2;
		m_bmpTips.ShowWindow(SW_SHOW);
		m_bmpLoading.ShowWindow(SW_HIDE);
		
		if(m_rdScanner.m_bHaveUndelReg)
			::SetWindowText(m_txtDesc, TEXT("ע�����������ɣ��������ʧ�ܡ�����7��֮���ٴν�������!"));
		else
			::SetWindowText(m_txtDesc, TEXT("ע�����������ɡ�����7��֮���ٴν�������!"));
		::ShowWindow(m_txtDesc, SW_SHOW);
		::GetWindowRect(m_txtDesc, rc);
		::SetWindowPos(m_txtDesc, NULL, 0, 0, m_rcMainClient.Width() - 50, rc.Height(), SWP_NOZORDER | SWP_NOMOVE);
		::InvalidateRect(m_txtDesc, NULL, FALSE);
		
		m_btnClean.ShowWindow(SW_SHOW);
		m_btnHistory.ShowWindow(SW_SHOW);
		m_btnStartScan.ShowWindow(SW_SHOW);
		m_btnStopScan.ShowWindow(SW_HIDE);
		
		::EnableWindow(m_chkSelectAll, TRUE);
		::EnableWindow(m_txtSelAll, TRUE);
		::EnableWindow(m_btnDefault, TRUE);
		::EnableWindow(m_btnClean, TRUE);

		m_tree.EnableCheck(TRUE);
		return;
	}
}


LRESULT CMainDlg::OnScanClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled)
{
	m_bStop = false;
// 	if (IsX64System())
// 	{
// 		::PostMessage(*this, WM_OWN_MSGBOX, (WPARAM)TEXT("ע���������֧��64λ����ϵͳ��"), 
// 			(LPARAM)NULL);
// 		goto Label_Ret;	
// 	}

	CheckTreeSelectStatus();
	if ( !m_bSelectedRoot )
	{
		::PostMessage(*this, WM_OWN_MSGBOX, (WPARAM)TEXT("����δѡ����Ҫɨ�����Ŀ������ѡ��Ȼ�����ɨ�裡"), 
			(LPARAM)NULL);
		goto Label_Ret;	
	}
	StartScan();

Label_Ret:
	bHandled = TRUE;
	return 0;
}


LRESULT CMainDlg::OnStopClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled)
{
	m_bStop = true;
	m_rdScanner.Stop();

	bHandled = TRUE;
	return 0;
}

LRESULT CMainDlg::OnBackupClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled)
{
	CRegBackupDlg regDlg;
	regDlg.DoModal(m_hWnd);
	return 0;
}

LRESULT CMainDlg::OnCleanClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled)
{
	m_bStop = false;

	CheckTreeSelectStatus();
	if ( !m_bSelectedRoot && !m_bSelectedChild )
	{
		// δѡ����
		::PostMessage(*this, WM_OWN_MSGBOX, (WPARAM)TEXT("����δѡ����Ҫ�������Ŀ������ѡ��Ȼ��������"), (LPARAM)NULL);
		goto Label_Ret;
	}
	else if ( m_bSelectedUnScaned && !m_bSelectedScanned && !m_bSelectedUnCleaned )
	{
		// δɨ����+��������
		::PostMessage(*this, WM_OWN_MSGBOX, (WPARAM)TEXT("��ѡ�����Ŀ�д���δɨ�����Ŀ����������ɨ�裬�ٽ�������"), (LPARAM)NULL);
		goto Label_Ret;
	}
	else if ( !m_bSelectedScanned && !m_bSelectedUnCleaned && m_bSelectedCleaned )
	{
		// ֻ����������
		::PostMessage(*this, WM_OWN_MSGBOX, (WPARAM)TEXT("��ѡ�е���Ŀ��ȫ��������ɣ���ѡ��������Ŀ��Ȼ������ɨ�裡"), (LPARAM)NULL);
		goto Label_Ret;
	}
	else if (!m_bSelectedChild)
	{
		::PostMessage(*this, WM_OWN_MSGBOX, (WPARAM)TEXT("����ָ����ѡ����δ���ֿ������ע����"), (LPARAM)NULL);
		goto Label_Ret;
	}


	if ( m_hCleanThread != NULL )
	{
		::CloseHandle(m_hCleanThread);
		m_hCleanThread = NULL;
	}
	
	m_iterLastItem = m_TreeRootMap.end();

	// ��ȡ��ѡ���������Ŀ
	EnumSelectedTreeItem();

	// ����Ϊ�����״̬
	SetScStatus(CMainDlg::SCS_CLEAN);

	// ��������߳�
	m_hCleanThread = ::CreateThread(NULL, 0, &CMainDlg::CleanThreadProc, this, 0, NULL);
	if ( m_hCleanThread == NULL )
	{
		::MessageBox(m_hWnd, TEXT("��ʼ��ʱ�����������������ť���ԡ�"), TEXT("�ڲ�����!"), 
			MB_OK | MB_ICONINFORMATION);

		SetScStatus(CMainDlg::SCS_IDLE);
	}
	else
	{
		m_dwCleanTickCount = ::GetTickCount();
	}

Label_Ret:
	bHandled = TRUE;
	return 0;
}


LRESULT CMainDlg::OnSelectAllClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled)
{
	LRESULT					lCheck = 0;
	HTREEITEM				hTreeItem = NULL;
	TREE_ROOT_MAP::iterator	iter;

	lCheck = ::SendMessage(m_chkSelectAll, BM_GETCHECK, 0, 0);
	m_bSelectMap.clear();

	if ( lCheck == BST_CHECKED )
	{
        ::SendMessage(m_chkSelectAll, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
		// ȫѡ
		for ( iter = m_TreeRootMap.begin(); iter != m_TreeRootMap.end(); ++iter )
		{
			m_tree.SetCheck(iter->second, KUIMulStatusTree::EM_TVIS_CHECK);
			m_bSelectMap[iter->first] = 1;
		}
	}
	else if ( lCheck == BST_UNCHECKED )
	{
		// ȫ��ѡ
        ::SendMessage(m_chkSelectAll, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
		for ( iter = m_TreeRootMap.begin(); iter != m_TreeRootMap.end(); ++iter )
		{
			m_tree.SetCheck(iter->second, KUIMulStatusTree::EM_TVIS_UNCHECK);
			m_bSelectMap[iter->first] = 0;
		}
	}
	else
	{
		// ���û����ѡ�е���״̬������Ϊȫ��ѡ
		::SendMessage(m_chkSelectAll, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
		
		// ȫ��ѡ
		for ( iter = m_TreeRootMap.begin(); iter != m_TreeRootMap.end(); ++iter )
		{
			m_tree.SetCheck(iter->second, KUIMulStatusTree::EM_TVIS_UNCHECK);
		}
	}

	bHandled = FALSE;
	return 0;
}


LRESULT CMainDlg::OnSelectDefaultClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled)
{
	SelectDefaultItems();
	bHandled = TRUE;
	::SendMessage(m_chkSelectAll, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
	return 0;
}


LRESULT CMainDlg::OnScanCallback(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	CRegistryData::SCAN_RESULT*		result = NULL;
	int								nIndex = -1;
	CRegistryData::REG_SCAN_TYPE	rstType;
	tstring							lpTitle, lpProblem;
	CRegistryData::REG_DATA			lpData;
	tstring							strKeyPath;
	LPCTSTR							lpRootKey = TEXT("HKLM");

	bHandled = TRUE;

	// ��ȡɨ�赽������
	result = (CRegistryData::SCAN_RESULT*)lParam;
	if ( result == NULL )
		return 0;

	result->GetInfo(rstType, lpData, lpProblem);
	lpTitle = CRegistryData::GetTitle(rstType);
	lpData.GetKeyFullPath(strKeyPath, true);
	if ( strKeyPath.size() > 1 && strKeyPath[strKeyPath.size() - 1] == TEXT('\\') )
		strKeyPath.erase(strKeyPath.size() - 1);
	
	// ��ӵ�Tree��
	TREE_ROOT_MAP::iterator		iter;
	HTREEITEM					hTreeItem = NULL;

	// �������Ƿ���Ч
	iter = m_TreeRootMap.find(rstType);
	if ( iter == m_TreeRootMap.end() )
		return 0;

	// �����
	hTreeItem = m_tree.InsertItem(strKeyPath.c_str(), 22, 22, 
		iter->second, NULL, KUIMulStatusTree::EM_TVIS_CHECK);
	m_tree.SetItemData(hTreeItem, (DWORD_PTR)(ULONG_PTR)result);

	// ���¼���
	m_nRegistryCount++;

	// �����ı���ʾ
	lpTitle = TEXT("����ɨ�裺");
	lpTitle += strKeyPath;
	if ( lpTitle.size() > 80 )
	{
		lpTitle.erase(40, lpTitle.size() - 83);
		lpTitle.insert(40, TEXT("..."));
	}
	m_strTxtDesc = lpTitle;

	return 0;
}


LRESULT CMainDlg::OnScanTypeCallback(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	tstring						strTitle;
	TREE_ROOT_MAP::iterator		iter;
	int							nNum = 0;
	std::vector<TCHAR>			buffer(30, 0);

	iter = m_SelectedRootMap.find((CRegistryData::REG_SCAN_TYPE)wParam);
	if ( iter == m_SelectedRootMap.end() )
		goto Label_Ret;

	// ɨ�赽��һ���ӽڵ�ʱ���������ɨ���е�״̬�����ָ�ǰһ�ڵ��״̬
	strTitle = CRegistryData::GetTitle(iter->first);
	strTitle += TEXT(" (����ɨ��...)");
	m_tree.SetItemText(iter->second, strTitle.c_str());
	m_tree.SelectItem(iter->second);

	// �л�ͼ��
	m_tree.SetItemImage(iter->second, 23, 23);

	// ����ڵ�
	m_iterLastItem = m_TreeRootMap.find(iter->first);

	if ( --iter != m_SelectedRootMap.end() )
	{
		// ����ϸ���������
		AddTypeScanData(iter->first);

		// ͳ���ϸ���������
		CalcChildNum(iter->second, nNum);
		::_itot_s(nNum, &buffer[0], buffer.size(), 10);

		strTitle = CRegistryData::GetTitle(iter->first);
		strTitle += TEXT(" (��ɨ�赽 ");
		strTitle += &buffer[0];
		strTitle += TEXT(" ��)");
		m_tree.SetItemText(iter->second, strTitle.c_str());
		m_tree.SetItemImage(iter->second, GetTypeIconIndex(iter->first), 
			GetTypeIconIndex(iter->first));
	}

Label_Ret:
	bHandled = TRUE;
	return 0;
}


LRESULT CMainDlg::OnScanEnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	// ����Tree��Ŀ��״̬
	SetScannedTreeItem();
	SetScStatus(CMainDlg::SCS_SCANNED);

	bHandled = TRUE;
	return 0;
}

LRESULT CMainDlg::OnCleanTypeCallback(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	int							nCheck = KUIMulStatusTree::EM_TVIS_CHECK;
	tstring						strTitle;
	TREE_ROOT_MAP::iterator		iter, iterLast;
	int							nChildItem = 0;

	// ����Ƿ�Ϊѡ�е����
	iter = m_SelectedRootMap.find((CRegistryData::REG_SCAN_TYPE)wParam);
	if ( iter == m_SelectedRootMap.end() )
		goto Label_Ret;
	
	// ����������
	strTitle = TEXT("���������");
	strTitle += CRegistryData::GetTitle(iter->first);
	strTitle += TEXT("...");
	m_strTxtDesc = strTitle;

	// ���õ�ǰ�������������״̬
	strTitle = CRegistryData::GetTitle(iter->first);
	strTitle += TEXT(" (�������...)");
	m_tree.SetItemText(iter->second, strTitle.c_str());
	m_tree.SetItemImage(iter->second, 23, 23);
	m_tree.SelectItem(iter->second);
	DeleteSelectedChild(iter->second);

	// ����ǰ��Ԫ��Ϊ��ѡ��״̬������Ϊδѡ��״̬����ѡ�е�Ԫ�ر�ɾ���ˣ�
	m_tree.GetCheck(iter->second, nCheck);
	if ( nCheck == KUIMulStatusTree::EM_TVIS_INDETERMINING )
		m_tree.SetCheck(iter->second, KUIMulStatusTree::EM_TVIS_UNCHECK);

	// ��¼��ǰ���
	iterLast = m_iterLastItem;
	m_iterLastItem = m_TreeRootMap.find(iter->first);

	// �ָ�ǰһ�������������״̬
	if ( iterLast != m_TreeRootMap.end() )
	{
		nChildItem = 0;
		CalcChildNum(iterLast->second, nChildItem);

		strTitle =  CRegistryData::GetTitle(iterLast->first);
		if ( nChildItem <= 0 )
			strTitle += TEXT(" (�����)");
		else
			strTitle += TEXT(" (������Ŀ�����)");
		m_tree.SetItemText(iterLast->second, strTitle.c_str());
		m_tree.SetItemImage(iterLast->second, GetTypeIconIndex(iterLast->first), GetTypeIconIndex(iterLast->first));

		// �����ѡ�е��ӽڵ�
	}

Label_Ret:
	bHandled = TRUE;
	return 0;
}


LRESULT CMainDlg::OnCleanEnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	// ��ձ�ѡ�����������
	SetCleanedTreeItem();

	// ����ؼ�״̬
	SetScStatus(CMainDlg::SCS_CLEANED);

	// ������Ϳؼ�ѡ��״̬�����ð�ť״̬
	CheckTreeSelectStatus();
	
	bHandled = TRUE;
	return 0;
}


LRESULT CMainDlg::OnOwnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	OnScanCleanTimer(TIMER_ID_SCAN);

	bHandled = TRUE;
	return 0;
}


LRESULT CMainDlg::OnOwnMsgBox(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	CKuiMsgBox::Show((LPCTSTR)wParam, (LPCTSTR)lParam, MB_OK | MB_ICONINFORMATION, NULL, *this);
	bHandled = TRUE;
	return 0;
}


// ���û���ѡ��checkboxʱ�����ô˺���
LRESULT CMainDlg::OnTreeItemCheckChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	HTREEITEM					hTreeItem = (HTREEITEM)wParam;
	int							nCheck = (int)lParam;
	CRegistryData::SCAN_RESULT*	lpResult = NULL;

	CheckTreeSelectStatus();

    if(nCheck!=3)
    ::SendMessage(m_chkSelectAll, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
   
	
	// ����Ƿ�Ϊ�ӽڵ��check
	bHandled = TRUE;
	if ( nCheck != KUIMulStatusTree::EM_TVIS_UNCHECK && nCheck != KUIMulStatusTree::EM_TVIS_CHECK )
		return 0;

	// �����Ƿ����
	lpResult = (CRegistryData::SCAN_RESULT*)m_tree.GetItemData(hTreeItem);
	if ( lpResult == NULL || (ULONG_PTR)lpResult == (ULONG_PTR)-1 )
		return 0;

	lpResult->SetToClean( (nCheck == KUIMulStatusTree::EM_TVIS_CHECK) ? true : false );
	return 0;
}


// ��ӦTVN_GETINFOTIPS��Ϣ������ToolTip��ʾ���ı�
LRESULT CMainDlg::OnTreeItemInfoTip(int idCtrl, LPNMHDR pnmh, BOOL &bHandled)
{
	LPNMTVGETINFOTIP				lpGetInfoTip = (LPNMTVGETINFOTIP)pnmh;
	CRegistryData::SCAN_RESULT*		lpResult = NULL;
	HTREEITEM						hTreeItem = NULL;
	tstring							strProblem;

	// ȡ�ڵ����������
	hTreeItem = lpGetInfoTip->hItem;
	lpResult = (CRegistryData::SCAN_RESULT*)(ULONG_PTR)m_tree.GetItemData(hTreeItem);
	if ( lpResult == NULL || (ULONG_PTR)lpResult == (ULONG_PTR)-1 )
		return 0;

	// ������һ����INFOTIPSIZE
	lpResult->GetProblem(strProblem);
	if ( lpGetInfoTip->cchTextMax > 1 && strProblem.size() > 0 )
	{
		::memset(lpGetInfoTip->pszText, 0, lpGetInfoTip->cchTextMax * sizeof(TCHAR));
		::_tcsncpy(lpGetInfoTip->pszText, strProblem.c_str(), lpGetInfoTip->cchTextMax - 1);
	}

	return 0;
}


HRESULT CMainDlg::StartScan()
{
	// �ͷ�ǰ���ɨ���߳�
	if ( m_hScanThread != NULL )
	{
		::CloseHandle(m_hScanThread);
		m_hScanThread = NULL;
	}

	// ���ǰһ�ε�ɨ����
	ClearAllTreeItem();
	m_iterLastItem = m_TreeRootMap.end();
	{
		KAutoLock		lockTree(m_lockTree);
		m_scanResultArray.clear();
	}

	// ��������
	m_nRegistryCount = 0;

	// ��ȡ��ѡ�����Ŀ�б�
	EnumSelectedTreeItem();

	// ����ɨ��״̬
	SetScStatus(CMainDlg::SCS_SCAN);

	// ����ɨ���߳�
	m_hScanThread = ::CreateThread(NULL, 0, &CMainDlg::ScanThreadProc, this, 0, NULL);
	if ( m_hScanThread == NULL )
	{
		::MessageBox(m_hWnd, TEXT("��ʼ��ɨ��ʱ������������ɨ�谴ť���ԡ�"), TEXT("�ڲ�����!"), 
			MB_OK | MB_ICONINFORMATION);
		
		SetScStatus(CMainDlg::SCS_IDLE);
		return E_FAIL;
	}

	return S_OK;
}


DWORD WINAPI CMainDlg::ScanThreadProc(LPVOID lpParameter)
{
	HRESULT		hr = E_FAIL;
	DWORD		dwTick = 0;
	CMainDlg*	lpThis = static_cast<CMainDlg*>(lpParameter);

	if ( lpThis == NULL )
		return -1;

	// �����ϴ�����ļ��.���̣ܶ�����ɨ�������
	/*dwTick = GetTickCount();
	if ( lpThis->m_dwCleanTickCount <= dwTick && dwTick - lpThis->m_dwCleanTickCount < 60000  )
	{
		::Sleep(3000);
		lpThis->SetScStatus(CMainDlg::SCS_SCANNED);
		return 0;
	}
	else if ( lpThis->m_dwCleanTickCount > dwTick && dwTick < 60000 )
	{
		::Sleep(3000);
		lpThis->SetScStatus(CMainDlg::SCS_SCANNED);
		return 0;
	}*/

	::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);

	// ɨ��
	hr = lpThis->m_rdScanner.Scan(&CMainDlg::ScanTypeCallBack, lpThis, &CMainDlg::ScanCallback, lpThis);
	
	// ɨ�����
	::PostMessage(*lpThis, WM_SCAN_END, 0, 0);
	return 0;
}


DWORD WINAPI CMainDlg::CleanThreadProc(LPVOID lpParameter)
{
	HRESULT		hr = E_FAIL;
	CMainDlg*	lpThis = static_cast<CMainDlg*>(lpParameter);

	if ( lpThis == NULL )
		return -1;

	// ����
	hr = lpThis->m_rdScanner.Clean(&CMainDlg::CleanTypeCallBack, lpThis);

	// �������
	::PostMessage(*lpThis, WM_CLEAN_END, 0, 0);
	return 0;
}


DWORD WINAPI CMainDlg::OwnTimerThreadProc(LPVOID lpParameter)
{
	HRESULT		hr = E_FAIL;
	CMainDlg*	lpThis = static_cast<CMainDlg*>(lpParameter);

	if ( lpThis == NULL )
		return -1;

	while (true)
	{
		::Sleep(300);
		::PostMessage(*lpThis, WM_OWN_TIMER, 0, 0);
	}

	return 0;
}


// ɨ��ص�����
bool CMainDlg::ScanCallback(CRegistryData::SCAN_RESULT* result, LPVOID lpParam)
{
	CMainDlg*		lpThis = static_cast<CMainDlg*>(lpParam);
	CRegistryData::REG_SCAN_TYPE	rstType;
	tstring			lpTitle, lpProblem, strKeyPath;
	CRegistryData::REG_DATA	lpData = {};

	if ( lpThis == NULL || result == NULL )
		return false;

	// ֪ͨ����ɨ�赽����Ŀ
	//::PostMessage(lpThis->m_hWnd, WM_SCAN_CALLBACK, 0, (LPARAM)result);
	//return true;

	// ��ӵ��ڲ��洢�ռ���
	{
		KAutoLock	lockTree(lpThis->m_lockTree);
		lpThis->m_scanResultArray[result->rstType].push_back(result);
	}

	result->GetInfo(rstType, lpData, lpProblem);
	lpTitle = CRegistryData::GetTitle(rstType);
	lpData.GetKeyFullPath(strKeyPath, true);
	if ( strKeyPath.size() > 1 && strKeyPath[strKeyPath.size() - 1] == TEXT('\\') )
		strKeyPath.erase(strKeyPath.size() - 1);

	lpTitle = TEXT("����ɨ�裺");
	lpTitle += strKeyPath;
	if ( lpTitle.size() > 80 )
	{
		lpTitle.erase(40, lpTitle.size() - 83);
		lpTitle.insert(40, TEXT("..."));
	}

	// �����ı���ʾ
	{
		KAutoLock	lockTips(lpThis->m_lockTips);
		lpThis->m_strTxtDesc = lpTitle;
	}

	return true;
}


bool CMainDlg::ScanTypeCallBack(CRegistryData::REG_SCAN_TYPE rstType, LPVOID lpParam)
{
	CMainDlg*				lpThis = static_cast<CMainDlg*>(lpParam);
	TREE_ROOT_MAP::iterator	iter;

	if ( lpThis == NULL )
		return false;

	// �������б��У����������͵�ɨ��
	iter = lpThis->m_SelectedRootMap.find(rstType);
	if ( iter == lpThis->m_SelectedRootMap.end() )
		return false;

	// ��������������
	{
		KAutoLock		lockTree(lpThis->m_lockTree);
		VSR				v;
		MTRP::iterator	iterArray;

		iterArray = lpThis->m_scanResultArray.find(rstType);
		if ( iterArray == lpThis->m_scanResultArray.end() )
			lpThis->m_scanResultArray.insert(std::make_pair(rstType, v));
	}
	
	// ֪ͨ���ڣ������͵�ɨ�迪ʼ��
	::PostMessage(lpThis->m_hWnd, WM_SCANTYPE_CALLBACK, (WPARAM)rstType, 0);
	return true;
}


bool CMainDlg::CleanTypeCallBack(CRegistryData::REG_SCAN_TYPE rstType, LPVOID lpParam)
{
	CMainDlg*		lpThis = static_cast<CMainDlg*>(lpParam);

	if ( lpThis == NULL )
		return true;

	// �������б��У�����
	if ( lpThis->m_SelectedRootMap.find(rstType) == lpThis->m_SelectedRootMap.end() )
		return true;

	// ֪ͨ���ڣ������͵������ʼ��
	::PostMessage(*lpThis, WM_CLEANTYPE_CALLBACK, (WPARAM)rstType, 0);
	return true;
}


void CMainDlg::SetScannedTreeItem()
{
	CMainDlg::TREE_ROOT_MAP::iterator	iter;
	int									nCheck = KUIMulStatusTree::EM_TVIS_UNCHECK;
	tstring								strText;

	// ���ñ�ɨ�����״̬
	for ( iter = m_SelectedRootMap.begin(); iter != m_SelectedRootMap.end(); ++iter )
	{
		// ��������
		m_tree.Expand(iter->second, TVE_COLLAPSE);

		// ��ѡ����δ��ɨ�裨ɨ����ֹ������ʾδɨ��
		if ( m_iterLastItem == m_TreeRootMap.end() || m_iterLastItem->first < iter->first )
		{
			strText =  CRegistryData::GetTitle(iter->first);
			strText += TEXT(" (δɨ��)");
			m_tree.SetItemText(iter->second, strText.c_str());
		}
		// ����ѡ�������������ֻ��0��
		else if ( m_tree.GetChildItem(iter->second) == NULL )
		{
			strText =  CRegistryData::GetTitle(iter->first);
			strText += TEXT(" (��ɨ�赽 0 ��)");
			m_tree.SetItemText(iter->second, strText.c_str());
		}

		// ����ͼ��
		m_tree.SetItemImage(iter->second, GetTypeIconIndex(iter->first), GetTypeIconIndex(iter->first));
	}

	// �ָ����ɨ������ı�
	if ( m_iterLastItem != m_TreeRootMap.end() )
	{
		int					nNum = 0;
		std::vector<TCHAR>	buffer(30, 0);
		tstring				lpTitle;

		AddTypeScanData(m_iterLastItem->first);

		CalcChildNum(m_iterLastItem->second, nNum);
		::_itot_s(nNum, &buffer[0], buffer.size(), 10);

		lpTitle = CRegistryData::GetTitle(m_iterLastItem->first);
		lpTitle += TEXT(" (��ɨ�赽 ");
		lpTitle += &buffer[0];
		lpTitle += TEXT(" ��)");
		m_tree.SetItemText(m_iterLastItem->second, lpTitle.c_str());
	}

	// ѡ�е�һ��
	iter = m_TreeRootMap.begin();
	if ( iter != m_TreeRootMap.end() )
		m_tree.SelectItem(iter->second);
}


HRESULT CMainDlg::SetCleanedTreeItem()
{
	tstring				strTitle;
	HTREEITEM			hTreeItem = NULL;
	int					nChildItem = 0;
	CMainDlg::TREE_ROOT_MAP::iterator	iter;
	std::vector<TCHAR>	buffer(100, 0);

	// ���Tree�г�ɨ�赽�����ݣ����������ͽڵ�, �ָ���ʼ�ı�
	for( iter = m_SelectedRootMap.begin(); iter != m_SelectedRootMap.end(); ++iter )
	{
		// ����;ֹͣ��ɨ�������������
		if ( m_bStop && m_iterLastItem != m_TreeRootMap.end() && iter->first > m_iterLastItem->first )
			break;

		// ����δɨ������������
		::memset(&buffer[0], 0, buffer.size() * sizeof(TCHAR));
		m_tree.GetItemText(iter->second, &buffer[0], (int)buffer.size());
		if ( ::_tcsstr(&buffer[0], TEXT("��ɨ�赽")) == NULL )
			continue;

		// ������Ŀ�����
		nChildItem = 0;
		CalcChildNum(iter->second, nChildItem);

		strTitle =  CRegistryData::GetTitle(iter->first);
		if ( nChildItem <= 0 )
			strTitle += TEXT(" (�����)");
		else
			strTitle += TEXT(" (������Ŀ�����)");
		m_tree.SetItemText(iter->second, strTitle.c_str());
		m_tree.SetItemImage(iter->second, GetTypeIconIndex(iter->first), GetTypeIconIndex(iter->first));
	}

	// �ָ����ɨ������ı�
	if ( m_iterLastItem != m_TreeRootMap.end() )
	{
		nChildItem = 0;
		CalcChildNum(m_iterLastItem->second, nChildItem);

		strTitle = CRegistryData::GetTitle(m_iterLastItem->first);
		if ( nChildItem <= 0 )
			strTitle += TEXT(" (�����)");
		else
			strTitle += TEXT(" (������Ŀ�����)");
		m_tree.SetItemText(m_iterLastItem->second, strTitle.c_str());
		m_tree.SetItemImage(m_iterLastItem->second, GetTypeIconIndex(m_iterLastItem->first),
			GetTypeIconIndex(m_iterLastItem->first));
	}

	// ѡ�е�һ��
	iter = m_TreeRootMap.begin();
	if ( iter != m_TreeRootMap.end() )
		m_tree.SelectItem(iter->second);

	return S_OK;
}


void CMainDlg::SelectDefaultItems()
{
	TREE_ROOT_MAP::iterator	iter;
	m_bSelectMap.clear();

	for ( iter = m_TreeRootMap.begin(); iter != m_TreeRootMap.end(); ++iter )
	{
		if (iter->first <= CRegistryData::RST_APPPATH)
		{
			m_tree.SetCheck(iter->second, KUIMulStatusTree::EM_TVIS_CHECK);
			m_bSelectMap[iter->first] = 1;
		}
		else
		{
			m_tree.SetCheck(iter->second, KUIMulStatusTree::EM_TVIS_UNCHECK);
			m_bSelectMap[iter->first] = 0;
		}
	}
}


// ����ڵ���ӽڵ���Ŀ
bool CMainDlg::CalcChildNum(HTREEITEM hParent, int& nNum)
{
    HTREEITEM   hChild = NULL;

    nNum = 0;
    hChild = m_tree.GetChildItem(hParent);
    while ( hChild != NULL )
    {
		++nNum;
        hChild = m_tree.GetNextSiblingItem(hChild);
    }

	return true;
}

// ����ڵ�ı�ѡ�е��ӽڵ���Ŀ
bool CMainDlg::CalcSelectedChildNum(HTREEITEM hParent, int& nNum)
{
	HTREEITEM		hChild = NULL;
	int				nCheck = KUIMulStatusTree::EM_TVIS_UNCHECK;

	nNum = 0;
	hChild = m_tree.GetChildItem(hParent);
	while ( hChild != NULL )
	{
		// ?���Ƿ�ѡ�?
		m_tree.GetCheck(hChild, nCheck);
		if ( nCheck == KUIMulStatusTree::EM_TVIS_CHECK )
			++nNum;

		hChild = m_tree.GetNextSiblingItem(hChild);
	}

	return true;
}


// ɾ���ڵ�������ӽڵ�
bool CMainDlg::DeleteAllChild(HTREEITEM hParent)
{
	bool			bReturn = false;
	HTREEITEM		hChild = NULL;
	HTREEITEM		hItem = NULL;

	bReturn = true;
	hChild = m_tree.GetChildItem(hParent);
	while ( hChild != NULL )
	{
		hItem = hChild;
		hChild = m_tree.GetNextSiblingItem(hChild);
		if ( !m_tree.DeleteItem(hItem) )
		{
			bReturn = false;
			goto Label_Ret;
		}
	}

Label_Ret:
	return bReturn;
}


// ɾ�����б�ѡ�е��ӽڵ�
bool CMainDlg::DeleteSelectedChild(HTREEITEM hParent)
{
	bool			bReturn = false;
	HTREEITEM		hChild = NULL;
	HTREEITEM		hItem = NULL;
	int				nCheck = KUIMulStatusTree::EM_TVIS_UNCHECK;

	bReturn = true;
	hChild = m_tree.GetChildItem(hParent);
	while ( hChild != NULL )
	{
		hItem = hChild;
		hChild = m_tree.GetNextSiblingItem(hChild);
		
		// ����Ƿ�ѡ��
		m_tree.GetCheck(hItem, nCheck);
		if ( nCheck != KUIMulStatusTree::EM_TVIS_CHECK )
			continue;

		// ��ѡ�У�ɾ���ڵ�
		if ( !m_tree.DeleteItem(hItem) )
		{
			bReturn = false;
			goto Label_Ret;
		}
	}

Label_Ret:
	return bReturn;
}


// ��ȡ��ѡ�����Ŀ�����浽�б���
void CMainDlg::EnumSelectedTreeItem()
{
	int			nCheck = KUIMulStatusTree::EM_TVIS_UNCHECK;
	CMainDlg::TREE_ROOT_MAP::iterator	iter;

	m_SelectedRootMap.clear();
	for ( iter = m_TreeRootMap.begin(); iter != m_TreeRootMap.end(); ++iter )
	{
		if ( !m_tree.GetCheck(iter->second, nCheck) )
			continue;

		if ( nCheck != KUIMulStatusTree::EM_TVIS_CHECK && nCheck != KUIMulStatusTree::EM_TVIS_INDETERMINING )
			continue;

		m_SelectedRootMap.insert(std::make_pair(iter->first, iter->second));
	}
}


// ���Tree�е����ݣ����������ͽڵ�, �ָ���ʼ�ı�
void CMainDlg::ClearAllTreeItem()
{
	HTREEITEM		hTreeItem = NULL;
	CMainDlg::TREE_ROOT_MAP::iterator	iter;

	for( iter = m_TreeRootMap.begin(); iter != m_TreeRootMap.end(); ++iter )
	{
		DeleteAllChild(iter->second);
		m_tree.SetItemText(iter->second, CRegistryData::GetTitle(iter->first));
	}

}


// ���tree����Ŀ��ѡ����������ø����ڿؼ���״̬(ɨ�衢�����ȫѡ)
void CMainDlg::CheckTreeSelectStatus()
{
	bool					bRootAllSelected = true;
	int						nSelectRootElem = 0;
	int						nSelectedChildElem = 0, nTotalSelectedChildElem = 0;
	int						nCheck = KUIMulStatusTree::EM_TVIS_UNCHECK;
	std::vector<TCHAR>		buffer(100,0);
	CMainDlg::TREE_ROOT_MAP::iterator	iter;

	// ��ʼ��״̬
	m_bSelectedRoot = false;
	m_bSelectedChild = false;
	m_bSelectedUnScaned = false;
	m_bSelectedScanned = false;
	m_bSelectedCleaned = false;
	m_bSelectedUnCleaned = false;

	nTotalSelectedChildElem = 0;
	m_bSelectMap.clear();
	int nIndex = 0;
	for ( iter = m_TreeRootMap.begin(); iter != m_TreeRootMap.end(); ++iter)
	{
		// ����Ԫ�ص�ѡ��״̬
		if ( !m_tree.GetCheck(iter->second, nCheck) )
		{
			
			continue;
		}
		if ( nCheck == KUIMulStatusTree::EM_TVIS_CHECK || nCheck == KUIMulStatusTree::EM_TVIS_INDETERMINING )
		{
			++nSelectRootElem;
			m_bSelectMap[iter->first] = 1;

			nSelectedChildElem = 0;
			CalcSelectedChildNum(iter->second, nSelectedChildElem);
			nTotalSelectedChildElem += nSelectedChildElem;

			// ����ı�
			::memset(&buffer[0], 0, buffer.size() * sizeof(TCHAR));
			m_tree.GetItemText(iter->second, &buffer[0], (int)buffer.size());
			if ( ::_tcsstr(&buffer[0], TEXT("��ɨ�赽")) != NULL )
			{
				m_bSelectedScanned = true;
				m_bSelectedUnCleaned = true;
			}
			else if ( ::_tcsstr(&buffer[0], TEXT("����")) != NULL )
			{
				if ( nSelectedChildElem <= 0 )
					m_bSelectedCleaned = true;
				else
					m_bSelectedUnCleaned = true;
			}
			else if ( ::_tcsstr(&buffer[0], TEXT("δɨ��")) != NULL )
			{
				m_bSelectedUnScaned = true;
			}
			else if ( ::_tcsstr(&buffer[0], TEXT("(")) == NULL )
			{
				m_bSelectedUnScaned = true;
			}
		}

		if(nCheck == KUIMulStatusTree::EM_TVIS_UNCHECK)
			m_bSelectMap[iter->first] = 0;

		if ( nCheck == KUIMulStatusTree::EM_TVIS_INDETERMINING )
			bRootAllSelected = false;
	}

	// ȫѡ
    nCheck = (int)::SendMessage(m_chkSelectAll, BM_GETCHECK, 0, 0);
	if ( nSelectRootElem == m_TreeRootMap.size() && bRootAllSelected )
	{
		::SendMessage(m_chkSelectAll, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
	}
	else if ( nSelectRootElem == 0 )
	{
		::SendMessage(m_chkSelectAll, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
	}
   

	// ɨ��
	if ( m_scStatus == CMainDlg::SCS_IDLE || m_scStatus == CMainDlg::SCS_SCANNED || m_scStatus == CMainDlg::SCS_CLEANED )
	{	
		if ( nSelectRootElem == 0 )
		{
			m_bSelectedRoot = false;
			//m_btnStartScan.EnableWindow(FALSE);
		}
		else
		{
			m_bSelectedRoot = true;
			m_btnStartScan.EnableWindow(TRUE);
		}
	}
	
	// ���
	if ( m_scStatus == CMainDlg::SCS_SCANNED || m_scStatus == CMainDlg::SCS_CLEANED )
	{
		if ( nTotalSelectedChildElem == 0 )
		{
			m_bSelectedChild = false;
			//m_btnClean.EnableWindow(FALSE);
		}
		else
		{
			m_bSelectedChild = true;
			m_btnClean.EnableWindow(TRUE);
		}
	}
}


int CMainDlg::GetTypeIconIndex(CRegistryData::REG_SCAN_TYPE rstType)
{
	int		nIndex = 0;

	switch (rstType)
	{
	case CRegistryData::RST_UNINSTALL:
		nIndex = 12;
		break;
	case CRegistryData::RST_SHAREDDLL:
		nIndex = 14;
		break;
	case CRegistryData::RST_OPENSAVEMRU:
		nIndex = 20;
		break;
	case CRegistryData::RST_FILEASSOC:
		nIndex = 18;
		break;
	case CRegistryData::RST_COM:
		nIndex = 16;
		break;
	case CRegistryData::RST_EXTHISTORY:
		nIndex = 20;
		break;
	case CRegistryData::RST_STARTMENU:
		nIndex = 21;
		break;
	case CRegistryData::RST_MUICACHE:
		nIndex = 17;
		break;
	case CRegistryData::RST_HELP:
		nIndex = 13;
		break;
	case CRegistryData::RST_APPPATH:
		nIndex = 19;
		break;
	default:
		nIndex = 6;
		break;
	}

	return nIndex;
}


void CMainDlg::AddTypeScanData(CRegistryData::REG_SCAN_TYPE rstType)
{
	CRegistryData::SCAN_RESULT*		result = NULL;
	int								nIndex = -1;
	tstring							lpTitle, lpProblem;
	CRegistryData::REG_DATA			lpData;
	tstring							strKeyPath;
	LPCTSTR							lpRootKey = TEXT("HKLM");
	TREE_ROOT_MAP::iterator			iterTree;
	HTREEITEM						hTreeItem = NULL;
	MTRP::iterator					iterMap;
	VSR::iterator					iterArray;
	KAutoLock						lockTree(m_lockTree);

	// �������Ƿ���Ч
	iterTree = m_TreeRootMap.find(rstType);
	if ( iterTree == m_TreeRootMap.end() )
		return;

	iterMap = m_scanResultArray.find(rstType);
	if ( iterMap == m_scanResultArray.end() )
		return;

	for ( iterArray = iterMap->second.begin(); iterArray != iterMap->second.end(); ++iterArray )
	{
		// ��ȡɨ�赽������
		result = (CRegistryData::SCAN_RESULT*)*iterArray;
		if ( result == NULL )
			return;

		result->GetInfo(rstType, lpData, lpProblem);
		lpTitle = CRegistryData::GetTitle(rstType);
		lpData.GetKeyFullPath(strKeyPath, true);
		if ( strKeyPath.size() > 1 && strKeyPath[strKeyPath.size() - 1] == TEXT('\\') )
			strKeyPath.erase(strKeyPath.size() - 1);

		// ��ӵ�Tree��
		hTreeItem = m_tree.InsertItem(strKeyPath.c_str(), 22, 22, 
			iterTree->second, NULL, KUIMulStatusTree::EM_TVIS_CHECK);
		m_tree.SetItemData(hTreeItem, (DWORD_PTR)(ULONG_PTR)result);
	}

	// ���¼���
	m_nRegistryCount += (int)iterMap->second.size();
	iterMap->second.clear();

	return;
}


LRESULT CALLBACK CMainDlg::TxtDescWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc = NULL;
	HDC			hdcMem = NULL;
	HBITMAP		hbmp = NULL;
	CRect		rc;
	tstring		strText;
	int			nX = 0;
	CFont		fontText;
	CString		sText;
	HBRUSH		hbr = NULL;
	TEXTMETRIC	tm = {};
	SIZE		sz = {};

	// ������PAINT��Ϣ
	if ( uMsg != WM_PAINT )
		return (*gs_lpThisDlg->m_lpTxtDescProc)(hwnd, uMsg, wParam, lParam);

	::GetClientRect(hwnd, rc);
	hdc = ::GetDC(hwnd);
	hdcMem = ::CreateCompatibleDC(hdc);
	hbmp = ::CreateCompatibleBitmap(hdc, rc.Width(), rc.Height());
	::SelectObject(hdcMem, hbmp);

	hbr = ::CreateSolidBrush(DIALOG_BK_COLOR);
	::FillRect(hdcMem, rc, hbr);
	::DeleteObject(hbr);

	fontText.CreatePointFont(90, TEXT("MS Shell Dlg"));
	::SelectObject(hdcMem, fontText);
	::GetTextMetrics(hdcMem, &tm);

	::SetBkMode(hdcMem, TRANSPARENT);
	::SetBkColor(hdcMem, DIALOG_BK_COLOR);

	// �����ı�
	if ( !gs_lpThisDlg->m_bTxtDescPaintClr )
	{
		std::vector<TCHAR>		buf(500, 0);

		::GetWindowText(hwnd, &buf[0], (int)buf.size());
		::SetTextColor(hdcMem, RGB(0,0,0));
		::TextOut(hdcMem, 0, 0, &buf[0], (int)::_tcslen(&buf[0]));
	}
	else
	{
		nX = 0;
		strText = TEXT("ɨ������ɣ�������  ");
		::SetTextColor(hdcMem, RGB(0,0,0));
		::TextOut(hdcMem, nX, 0, strText.c_str(), (int)strText.size());
		
		if ( GetTextExtentPoint32(hdcMem, strText.c_str(), (int)strText.size(), &sz) )
			nX += sz.cx - tm.tmOverhang;
		else
			nX += (int)(strText.size() * 12);
		sText.Format(TEXT("%d"), gs_lpThisDlg->m_nRegistryCount);
		strText = sText;
		::SetTextColor(hdcMem, RGB(255,0,0));
		::TextOut(hdcMem, nX, 0, strText.c_str(), (int)strText.size());

		if ( GetTextExtentPoint32(hdcMem, strText.c_str(), (int)strText.size(), &sz) )
			nX += sz.cx - tm.tmOverhang;
		else
			nX += (int)strText.size() * 8;
		strText = TEXT("  ������ע����������������");
		::SetTextColor(hdcMem, RGB(0,0,0));
		::TextOut(hdcMem, nX, 0, strText.c_str(), (int)strText.size());
	}

	// ���Ƶ�
	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(), hdcMem, 0, 0, SRCCOPY);

	::DeleteObject(hbmp);
	::DeleteDC(hdcMem);
	::ReleaseDC(hwnd, hdc);
	::ValidateRect(hwnd, NULL);

	return 0;
}
