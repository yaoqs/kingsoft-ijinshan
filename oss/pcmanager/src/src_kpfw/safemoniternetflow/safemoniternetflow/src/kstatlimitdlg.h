#pragma once
#include "bkres/bkres.h"
#include <wtlhelper/whwindow.h>
#include "bkwin/bklistbox.h"


#define		DEFCANCELMAINBUTTON			102
#define		DEFMORESEETING				108
#define		DEFNETMONITERC				120
#define		DEFSTATINFO					121
#define		DEFCHECKDAY					104
#define		DEFCHECKMONTH				105
#define		DEFINFOTEXT					106

#define		DEFRESULTMORESETTING		10
#define		DEFRESULTNETMOINTERCONTRAL	11
#define		DEFRESULTSTATINFO			12

#define		DEFMODEISDAY				1
#define		DEFMODEISMONTH				2

class KStatListDlg
	: public CBkDialogImpl<KStatListDlg>,
	public CWHRoundRectFrameHelper<KStatListDlg>
{

public:
	KStatListDlg()
		: CBkDialogImpl<KStatListDlg>(IDR_BK_STAT_REMAID)
	{
		m_nMode = 1;
		m_nSetSize = 0;
		m_bIsShowDlg = FALSE;
	}

	~KStatListDlg(){}

private:
	int				m_nMode; //1--��ʾ�� 2--��ʾ��
	int				m_nSetSize; //���õı���ֵ
	BOOL			m_bIsShowDlg;

private:
	void			_SetConfigInfo(IN const CString& strTerm, IN const CString& strName, IN const CString& strValue);
	void			_SetShowInfo(void);

public:

	void			SetConfig(IN int nMode, IN int nSetSize);
	void			SetIsShowDlg(BOOL bIsShowDlg) { m_bIsShowDlg = bIsShowDlg; }
	BOOL			IsShowDlg(void) { return m_bIsShowDlg; }
	void			BtnClose(void);
	BOOL			OnInitDialog(CWindow wndFocus, LPARAM lInitParam);		

	//��ϸ����
	void			OnClickMoreSetting(void);
	//��������
	void			OnClickShowNetMointer(void);
	//��������
	void			OnClickShowStatResult(void);
	//�����
	void			OnClickCheckDay(void);
	//�����
	void			OnClickCheckMonth(void);

	void			OnSysCommand(UINT nID, CPoint pt);
	
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		BK_NOTIFY_ID_COMMAND(DEFCANCELMAINBUTTON, BtnClose)

		BK_NOTIFY_ID_COMMAND(DEFMORESEETING, OnClickMoreSetting)
		BK_NOTIFY_ID_COMMAND(DEFNETMONITERC, OnClickShowNetMointer)
		BK_NOTIFY_ID_COMMAND(DEFSTATINFO, OnClickShowStatResult)
		BK_NOTIFY_ID_COMMAND(DEFCHECKDAY, OnClickCheckDay)
		BK_NOTIFY_ID_COMMAND(DEFCHECKMONTH, OnClickCheckMonth)
	BK_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(KStatListDlg)
		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<KStatListDlg>)
		CHAIN_MSG_MAP(CBkDialogImpl<KStatListDlg>)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_SYSCOMMAND(OnSysCommand)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

};