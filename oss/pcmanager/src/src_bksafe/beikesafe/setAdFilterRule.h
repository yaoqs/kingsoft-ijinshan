#pragma once
//���ù����˹���
#include "kws/commonfun.h"
#include "common/whitelist.h"
#include "kws/setting_hlp.h"
#include "kws/simpleipc/KwsIPCWarpper.h"
#include "kws/simpleipc/KwsIPCWarpperOld.h"
#include "kws/ctrls/rulelistctrl.h"


#define		SBP_FILE_EXT		TEXT("dat")
#define		SBP_FILE_NAME		TEXT("blacklist")
#define		SBP_FULL_NAME		TEXT("blacklist.dat")
#define		SBP_HEAD_ADDR		TEXT("��ַ")
#define		SBP_HEAD_TYPE		TEXT("����")
#define		SBP_DLG_FILTER		TEXT("�����ļ� (*.dat)|*.dat|�����ļ� (*.*)|*.*||")
#define		SBP_CLEAN_TEXT		TEXT("�Ƿ�������еĺ�������������ǡ���\r\n���б����������񡱡�")
#define		SBP_VIRUS_WEB		TEXT("������վ")
#define		SBP_FISHWEB			TEXT("��թ��ַ")
#define		SBP_ADVWEB			TEXT("������")

class CSetBlackPage 
	: public CBkDialogImpl<CSetBlackPage>
	,public CWHRoundRectFrameHelper<CSetBlackPage>
{
public:
	CSetBlackPage()
		: CBkDialogImpl<CSetBlackPage>(IDR_BK_SAFEKWS_ADRULE_SETTING_DLG)
	{
	}

	~CSetBlackPage(void)
	{
	}

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{				
		return 0;
	}
	BOOL OnInitDialog(HWND wParam, LPARAM lParam)
	{	
		InitCtrls();
		UpdateConfig();
		RefreshTurnOnAntiAdTipState();		
		return TRUE;
	}
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		UninitCtrls();
		return 0;
	}
	void OnBkBtnClose()
	{
		EndDialog(IDCANCEL);
		return;
	}
	void UpdateDelLink()
	{
		if( m_wndEdit.IsWindow() )
		{
			int nCnt = m_wndListView.GetItemCount();
			if (nCnt > 0)
			{
				//���� ����  ���  ȫ��Ϊ��ѡ
				EnableItem( IDC_LINKTEXT_IMPORT, TRUE );
				EnableItem( IDC_LINKTEXT_EXPORT, TRUE );
				EnableItem( IDC_LINKTEXT_CLEAR,	 TRUE );
			}
			else//����������  ����ȫ��Ϊ����ѡ״̬
			{
				EnableItem( IDC_LINKTEXT_IMPORT, TRUE );			
				EnableItem( IDC_LINKTEXT_EXPORT, FALSE );
				EnableItem( IDC_LINKTEXT_CLEAR,	 FALSE );
				EnableItem( IDC_LINKTEXT_DELETE, FALSE );
			}
			int nIndex = m_wndListView.GetSelectedIndex();
			if (nIndex != -1)
			{
				EnableItem( IDC_LINKTEXT_DELETE,  TRUE);
			}
			else
			{
				EnableItem( IDC_LINKTEXT_DELETE,  FALSE);
			}
		}
		
		return;
	}
	void UpdateConfig()
 	{
		std::vector<BLACKLISTITEM> vecList;
		CSettingHlp::Instance().GetBlackList( vecList );
		for ( int i = 0; i < vecList.size(); i++ )
		{
			AddListItem(  vecList[i].wType,  vecList[i].strUrl, i );
		}

		UpdateDelLink();
		SetItemVisible(IDC_TXT_ADFILTER_REBOOT, FALSE);		
		EnableItem( IDC_BTN_ADD_ID, FALSE );
		EnableItem( IDC_LINKTEXT_DELETE,  FALSE);
	}
	void InitCtrls()
	{
		m_wndListView.SetRowHeight( 24 );
		m_rtList = CRect( 13, 77, 13 + 463, 77 + 282);
		m_wndListView.Create( GetViewHWND(), m_rtList, NULL, 
			WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 
			0, IDC_LIST_ADRULE_DLG);
		m_wndListView.HeaderSubclassWindow();
		m_rtList.InflateRect( 1, 1 );
		m_wndListView.SetExtendedListViewStyle( LVS_EX_FULLROWSELECT | m_wndListView.GetExtendedListViewStyle() );

		m_wndListView.InsertColumn(0, L"��ַ",	LVCFMT_LEFT, 340);
		m_wndListView.InsertColumn(1, L"����",		LVCFMT_CENTER, 100);
		m_wndListView.SetNotifyWnd( m_hWnd );

		m_wndEdit.Create( GetViewHWND(), 
			NULL,
			NULL,
			WS_VISIBLE | WS_CHILDWINDOW | ES_AUTOHSCROLL,
			0,
			IDC_EDITBOX_ADRULE_DLG);
		m_wndEdit.SetFont(BkFontPool::GetFont(BKF_DEFAULTFONT));
		return;
	}	
	void UninitCtrls()
	{
		if( m_wndListView.IsWindow() )
			m_wndListView.DestroyWindow();

		if( m_wndEdit.IsWindow() )
			m_wndEdit.DestroyWindow();
	}
	LRESULT OnEditChange(WORD /*wNotifyCode*/, WORD wID, HWND hWndCtl, BOOL& /*bHandled*/)
	{
		if( m_wndEdit.IsWindow() )
		{
			ATL::CString strUrl;
			m_wndEdit.GetWindowText( strUrl );
			if (strUrl.GetLength() > 0)
			{
				EnableItem( IDC_BTN_ADD_ID, TRUE );
			}
			else
			{
				EnableItem( IDC_BTN_ADD_ID, FALSE );
			}
		}

		return TRUE;
	}
	LRESULT OnListViewItemChange( int wParam, LPNMHDR lParam, BOOL& bHandled )
	{
		if( m_wndListView.IsWindow() )
		{
			int nIndex = m_wndListView.GetSelectedIndex();
			if (nIndex != -1)
			{
				EnableItem( IDC_LINKTEXT_DELETE,  TRUE);
			}
			else
			{
				EnableItem( IDC_LINKTEXT_DELETE,  FALSE);
			}
			
		}

		return TRUE;
	}
	//�����ַ
	void ShowRestartText()
	{	
		SetItemVisible(IDC_TXT_ADFILTER_REBOOT, TRUE);
		Invalidate();
		return;
	}
	void OnAddUrl()
	{
		ATL::CString strUrl;
		int nType = UT_ADVWEB;//ֻ�ж����
		m_wndEdit.GetWindowText( strUrl );

		std::wstring szUrl(strUrl);
		std::wstring szFtUrl;

		std::wstring szexist = L"0";
		//�ڷ�����й���
		kws_old_ipc::KwsBlackListAddEx( nType, szUrl.c_str(), szFtUrl, szexist );		
		if( szFtUrl != TEXT(""))
		{
			if (CBkSafeMsgBox2::ShowMultLine( L"���Ƿ�ȷ����������ַ��", L"��ɽ��ʿ",  MB_OKCANCEL|MB_ICONWARNING) == IDOK)
			{
				AddListItem( nType, szFtUrl.c_str(), m_wndListView.GetItemCount() );
				ShowRestartText();
				m_wndEdit.SetWindowText( TEXT("") );
			}
			
		}
 		else if( 0 == szexist.compare(L"1"))
 		{
			//��ַ����
			CBkSafeMsgBox2::ShowMultLine( L"���������ַ�Ѿ����ڣ����������룡", L"��ɽ��ʿ",  MB_OK|MB_ICONWARNING );
 		}
 		else
		{
			//��ַ����  ����������
			CBkSafeMsgBox2::ShowMultLine(L"���������ַ�������������룡",  L"��ɽ��ʿ", MB_OK|MB_ICONWARNING);
		} 			
		UpdateDelLink();
		return;
	}
	void AddListItem( int nType, LPCTSTR pszUrl, int nPos )//����б�
	{
		if ( !m_wndListView.IsWindow() )
			return;

		int j = 0;
		m_wndListView.InsertItem( nPos, TEXT("") );
		m_wndListView.SetItemText( nPos, j++, pszUrl );
		ATL::CString strType;
		GetTypeString( nType, strType );
		m_wndListView.SetItemText( nPos, j++, strType );	
		return;
	}
	void GetTypeString( int nType, ATL::CString &str )//��������
	{
		switch( nType )
		{
		case UT_VIRUSWEB:
			str = SBP_VIRUS_WEB;
			break;
		case UT_FISHWEB:
			str = SBP_FISHWEB;
			break;
		case UT_ADVWEB:
			str = SBP_ADVWEB;
			break;
		default:
			str = SBP_VIRUS_WEB;
		}
		return;
	}
	void ConvertToWtlFileDialogFilter( LPWSTR pwszFilter )
	{
		size_t nCount = wcslen( pwszFilter );
		for( size_t i = 0; i < nCount; i++ )
		{
			if( pwszFilter[i] == '|' )
				pwszFilter[i] = '\0';
		}
		return;
	}
	void OnImport()
	{
		WCHAR szFilter[MAX_PATH] = SBP_DLG_FILTER;
		ConvertToWtlFileDialogFilter(szFilter);
		CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_FILEMUSTEXIST,
			szFilter, 0);
		fileDlg.m_ofn.lStructSize = (::GetVersion() < 0x80000000) ? 88 : 76;	// ����������ʾ�µķ��
		if (IDOK == fileDlg.DoModal())
		{		
			kws_old_ipc::KwsBlackListImport(fileDlg.m_szFileName,  L"0", L"0");
			if( m_wndListView.IsWindow() )
			{
				m_wndListView.DeleteAllItems();
				UpdateConfig();
			}

			ShowRestartText();//��ʾ������			
		}
		UpdateDelLink();
		return;
	}
	void OnExport()
	{
		WCHAR szFilter[MAX_PATH] = SBP_DLG_FILTER;
		ConvertToWtlFileDialogFilter(szFilter);
		CFileDialog fileDlg(FALSE, SBP_FILE_EXT, SBP_FILE_NAME, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,
			szFilter, 0);
		fileDlg.m_ofn.lStructSize = (::GetVersion() < 0x80000000) ? 88 : 76;	// ����������ʾ�µķ��
		if (IDOK == fileDlg.DoModal())
		{		
			kws_old_ipc::KwsBlackListExport(fileDlg.m_szFileName);
		}
		UpdateDelLink();
		return;
	}
	void OnDelete()
	{
		if ( !m_wndListView.IsWindow() )
			return;

		int nIndex = m_wndListView.GetSelectedIndex();
		ATL::CString strUrl;
		if( nIndex != -1 )
		{
			int nRet = 0;
			nRet = CBkSafeMsgBox2::ShowMultLine( L"���Ƿ�ȷ��ɾ��ѡ�е���ַ��", L"��ɽ��ʿ",  MB_OKCANCEL|MB_ICONWARNING );
			if( nRet == IDCANCEL )
				return;
			m_wndListView.GetItemText( nIndex, 0, strUrl );		
			m_wndListView.DeleteItem( nIndex );
			kws_old_ipc::KwsBlackListDelete( strUrl );
			ShowRestartText();
		}
		UpdateDelLink();
		return;
	}
	void OnClear()
	{
		WCHAR szLog[MAX_PATH] = {0};
		BOOL bRet = FALSE;

		ATL::CString strMsg( SBP_CLEAN_TEXT );
		if (CBkSafeMsgBox2::ShowMultLine( strMsg, L"��ɽ��ʿ",  MB_YESNO|MB_ICONWARNING) == IDYES)		
		{
			if( m_wndListView.IsWindow() )
				m_wndListView.DeleteAllItems();

			WCHAR szLog[MAX_PATH] = {0};
			BOOL bRet = FALSE;
			bRet = GetAllUserKWSPath(szLog, MAX_PATH);
			wcscat_s(szLog, MAX_PATH, SBP_FULL_NAME );
			kws_old_ipc::KwsDeleteLog(szLog);

			if( m_wndListView.IsWindow() )
				m_wndListView.DeleteAllItems();

			ShowRestartText();
		}
		UpdateDelLink();
		return;
	}
	void OnAntiAdEnable()
	{
		KwsSetting setting;
		setting.SetAntiAdEnable(TRUE);
		RefreshTurnOnAntiAdTipState();
		return;
	}
	void RefreshTurnOnAntiAdTipState()
	{
		KwsSetting setting;
		if( setting.IsAntiAdEnable() )
		{
			SetItemVisible(IDC_LINKTEXT_ADFILTER_ON, FALSE);
			SetItemVisible(IDC_TXT_ADFILTER_ONOFF,  FALSE);
		}
		else
		{
			SetItemVisible(IDC_LINKTEXT_ADFILTER_ON, TRUE);
			SetItemVisible(IDC_TXT_ADFILTER_ONOFF,  TRUE);
		}
		return;
	}

	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN);	
		BK_NOTIFY_ID_COMMAND(IDC_BTN_SYS_CLOSE,			OnBkBtnClose)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_ADD_ID,			OnAddUrl)//�����ַ
		BK_NOTIFY_ID_COMMAND(IDC_LINKTEXT_IMPORT,		OnImport)//����
		BK_NOTIFY_ID_COMMAND(IDC_LINKTEXT_EXPORT,		OnExport)//����
		BK_NOTIFY_ID_COMMAND(IDC_LINKTEXT_DELETE,		OnDelete)//ɾ��
		BK_NOTIFY_ID_COMMAND(IDC_LINKTEXT_CLEAR,		OnClear)//���	
		BK_NOTIFY_ID_COMMAND(IDC_LINKTEXT_ADFILTER_ON,	OnAntiAdEnable)//���ù����˹���
	BK_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CSetBlackPage)	
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP(CBkDialogImpl<CSetBlackPage>)
		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CSetBlackPage>)
 		MESSAGE_HANDLER(WM_CREATE,				OnCreate)
 		MESSAGE_HANDLER(WM_DESTROY,				OnDestroy)	
		MSG_WM_INITDIALOG(OnInitDialog)
		NOTIFY_HANDLER( IDC_LIST_ADRULE_DLG, LVN_ITEMCHANGED,	OnListViewItemChange)
		COMMAND_HANDLER(IDC_EDITBOX_ADRULE_DLG, EN_CHANGE,		OnEditChange)

		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
private:
	KRuleListCtrl		m_wndListView;
	CRect				m_rtList;
	CEdit				m_wndEdit;
};