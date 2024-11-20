// winoptDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include <vector>
#include <map>
using namespace std;

#define WINDOW_UPDATE_TIMEER		1

// CwinoptDlg �Ի���
class CwinoptDlg : public CDialog
{
// ����
public:
	CwinoptDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WINOPT_DIALOG };

	BOOL	AddEnumWindow(HWND hWnd);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void		UpdateListData();
	void		InitListData();
	void		AddListHeader(CHeaderCtrl* pHeader, INT nPos, INT nWidth, LPTSTR strTxt, INT nFormat);
	void		EnumTopLevelWnd();
	int			AddWndInfoToList(HWND hWnd);
	void		OnDestroyWnd(HWND hWnd);
	void		UpdateWndInfo();
	void		RemoveUnVisibleFromList();
	void		LogWndInfo(HWND hWnd);
	BOOL		IsWindowMustList(HWND hWnd, INT* pID = NULL);
	void		ResetList();
	void		SetActiveWnd(HWND hWnd);
	void		DeleteWndFromList(HWND hWnd);

	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

// ʵ��
protected:
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nID);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_winList;
	afx_msg void OnBnClickedCloseSelWin();

private:
	HICON				m_hIcon;
	DWORD				m_nHookMessage;
	map<HWND, int>		m_TopLevelWinList;
	DWORD				m_nUpdateWndTimer;
	BOOL				m_bLoggingWndInfo;

public:
	afx_msg void OnBnClickedLogWndInfo();
	CString m_ActiveWnd;
	CString m_ActiveProcess;
};
