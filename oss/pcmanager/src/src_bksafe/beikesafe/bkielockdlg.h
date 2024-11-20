#pragma once


#include <wtlhelper/whwindow.h>
#include "beikesafe.h"
#include <plugin/interface.h>
#include <common/utility.h>
#include "beikecolordef.h"
#include "beikesafemsgbox.h"
#include <miniutil/bkprocprivilege.h>
#include "common/KwsSettingOld.h"

class CIeLockDlg
	: public CBkDialogImpl<CIeLockDlg>
	, public CWHRoundRectFrameHelper<CIeLockDlg>
{
public:
	CIeLockDlg(BOOL b, int n)
		: CBkDialogImpl<CIeLockDlg>(IDR_BK_IELOCK_DLG)
	{
		m_pComBoBox = NULL;
		m_bReboot = b;
		m_nCnt = n;
	}
	~CIeLockDlg(void)
	{

	}
public:
	int _ReBoot()
	{
		CBkProcPrivilege privilege;

		if (!privilege.EnableShutdown())
			return -1;

		if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCEIFHUNG, 
			SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
			SHTDN_REASON_MINOR_HOTFIX |
			SHTDN_REASON_FLAG_PLANNED)) 
			return 0;

		return -1;
	}
	void OnBkClose()
	{
		EndDialog(0);
	}
	void OnReboot()
	{
		//��������
		if (GetItemCheck(IDC_IEFIX_TEXT_LNK_SELECTALL))//ѡ����
		{
			ATL::CString strWebName;
			ATL::CString strWebUrl;
			CSafeMonitorTrayShell trayShell;

			if( m_pComBoBox )
			{
				strWebUrl = m_pComBoBox->GetInputWebUrl();
				strWebName = m_pComBoBox->GetInputWebName();
				ATL::CString strTrimed = strWebUrl.Trim();

				if ( strTrimed.GetLength() == 0 )
				{
					strWebUrl = TEXT("about:blank");
					strWebName = CSettingHlp::Instance().UrlToName((LPCTSTR)strWebUrl);
				}
			}

			kws_old_ipc::KwsSetting setting;

			trayShell.SetDefaultHomepage(strWebUrl);
			setting.SetStartPage( strWebUrl );
			setting.SetLockSPEnable( TRUE );
			strWebName = CSettingHlp::Instance().UrlToName((LPCTSTR)strWebUrl);

			CSettingHlp::Instance().RegSetStartPage(strWebUrl, HKEY_CURRENT_USER);
			CSettingHlp::Instance().RegSetStartPage(strWebUrl, HKEY_LOCAL_MACHINE);

			if( m_pComBoBox )
			{
				strWebName = CSettingHlp::Instance().UrlToName( strWebUrl );
				strWebUrl = CSettingHlp::Instance().NameToUrl( strWebName );
				m_pComBoBox->AddString( strWebUrl, strWebName );
			}
		}		
		_ReBoot();
		EndDialog(1);
	}
	void OnRebootLater()
	{
		//�Ժ�����		
		if (GetItemCheck(IDC_IEFIX_TEXT_LNK_SELECTALL))//ѡ����
		{
			ATL::CString strWebName;
			ATL::CString strWebUrl;
			CSafeMonitorTrayShell trayShell;

			if( m_pComBoBox )
			{
				strWebUrl = m_pComBoBox->GetInputWebUrl();
				strWebName = m_pComBoBox->GetInputWebName();
				ATL::CString strTrimed = strWebUrl.Trim();

				if ( strTrimed.GetLength() == 0 )
				{
					strWebUrl = TEXT("about:blank");
					strWebName = CSettingHlp::Instance().UrlToName((LPCTSTR)strWebUrl);
				}
			}

			kws_old_ipc::KwsSetting setting;

			trayShell.SetDefaultHomepage(strWebUrl);
			setting.SetStartPage( strWebUrl );
			setting.SetLockSPEnable( TRUE );
			strWebName = CSettingHlp::Instance().UrlToName((LPCTSTR)strWebUrl);

			CSettingHlp::Instance().RegSetStartPage(strWebUrl, HKEY_CURRENT_USER);
			CSettingHlp::Instance().RegSetStartPage(strWebUrl, HKEY_LOCAL_MACHINE);

			if( m_pComBoBox )
			{
				strWebName = CSettingHlp::Instance().UrlToName( strWebUrl );
				strWebUrl = CSettingHlp::Instance().NameToUrl( strWebName );
				m_pComBoBox->AddString( strWebUrl, strWebName );
			}
		}
		
		EndDialog(0);
	}


	BOOL OnInitDialog(HWND wParam, LPARAM lParam)
	{	
		if( !m_pComBoBox )
		{
			m_pComBoBox = new KComboBox;
			CSettingHlp::Instance().CreateComBoBox(GetViewHWND() , m_pComBoBox, IDC_KWS_COMBOBOX_CTRL );
		}
		ATL::CString strX;
		strX.Format(_T("�Ѿ��ɹ��޸� %d ���쳣"), m_nCnt);
		this->SetItemVisible(IDC_KWS_COMBOBOX_CTRL, TRUE);
		this->SetItemCheck(IDC_IEFIX_TEXT_LNK_SELECTALL,TRUE);
		this->SetItemText(IDC_TXT_TEXT_DANER_NUM, strX);

		if (m_bReboot)
		{
			this->SetItemVisible(IDC_TXT_BTM_SURE, FALSE);
			this->SetItemVisible(IDC_TXT_TEXT_LOCK, FALSE);
			this->SetItemVisible(IDC_TXT_BTM_REBOOT, TRUE);
			this->SetItemVisible(IDC_TXT_BTM_REBOOT_LATER, TRUE);
			this->SetItemVisible(IDC_TXT_TEXT_REBOOT, TRUE);
		}
		else
		{			
			this->SetItemVisible(IDC_TXT_BTM_REBOOT, FALSE);
			this->SetItemVisible(IDC_TXT_BTM_REBOOT_LATER, FALSE);
			this->SetItemVisible(IDC_TXT_TEXT_REBOOT, FALSE);
			this->SetItemVisible(IDC_TXT_TEXT_LOCK, TRUE);
			this->SetItemVisible(IDC_TXT_BTM_SURE, TRUE);
		}
		return TRUE;
	}

protected:
	KComboBox*			m_pComBoBox;
	BOOL				m_bReboot;//�Ƿ���Ҫ����
	int					m_nCnt;//�쳣����Ŀ
public:
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		BK_NOTIFY_ID_COMMAND(IDC_TXT_BTM_REBOOT_LATER, OnRebootLater)//�Ժ�����
		BK_NOTIFY_ID_COMMAND(IDC_TXT_BTM_CLOSE, OnBkClose)//�رհ�ť
		BK_NOTIFY_ID_COMMAND(IDC_TXT_BTM_REBOOT, OnReboot)//��������
		BK_NOTIFY_ID_COMMAND(IDC_TXT_BTM_SURE, OnRebootLater)//ȷ��		
		BK_NOTIFY_MAP_END()

		BEGIN_MSG_MAP_EX(CIeLockDlg)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP(CBkDialogImpl<CIeLockDlg>)
		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CIeLockDlg>)
		MSG_WM_INITDIALOG(OnInitDialog)
		END_MSG_MAP()
};
