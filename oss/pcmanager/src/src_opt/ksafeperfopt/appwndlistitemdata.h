#pragma once
#include "appwndbasedata.h"

class KAppWndListItemData
{
public:
	KAppWndListItemData(){}

	KAppWndListItemData(LPAPP_WND_STATE_ITEM lpWndStateItem)
	{
		m_hWnd = lpWndStateItem->hWnd;
		m_hWndIcon = lpWndStateItem->hIcon;
		m_dwWndState = lpWndStateItem->bHung;
		m_dwPID = lpWndStateItem->dwPID;
		m_hExeIcon = NULL;
		m_dwNotActiveTime = 0;
		m_strWndTitle = lpWndStateItem->szTitle;
	}

	~KAppWndListItemData(){}

	void SetItemExeIcon(HICON hExeIcon)
	{
		m_hExeIcon = hExeIcon;
	}

	void SetItemExePath(const CString& strPath)
	{
		m_strFilePath = strPath;
	}

	void SetItemNotActiveTime(DWORD dwTime)
	{
		m_dwNotActiveTime = dwTime;
		
		if( m_dwWndState == 0 )
		{
			if(m_dwNotActiveTime >= 1800 )
				m_dwWndState = 3;
		}
	}

	void SetItemState(DWORD dwState)
	{
		m_dwWndState = dwState;
	}

	DWORD GetItemPID()
	{
		return m_dwPID;
	}

	HWND GetItemHwnd()
	{
		return m_hWnd;
	}

	CString GetItemExePath()
	{
		return m_strFilePath;
	}

	CString GetItemWndTitle()
	{
		return m_strWndTitle;
	}

	HICON GetItemWndIcon()
	{
		return m_hWndIcon;
	}

	HICON GetItemExeIcon()
	{
		return m_hExeIcon;
	}

	CString GetItemStateStr()
	{
		CString strWndState;
		if (m_dwWndState == 1)//δ��Ӧ
		{
			strWndState	= BkString::Get(STR_WNDSTATE_HUNG);
		}
		else if (m_dwWndState == 0)//�����
		{
			if (m_dwNotActiveTime >= 1800)//30����δʹ��
				strWndState = BkString::Get(STR_30MIN_NOTACTIVE);
			else
				strWndState = BkString::Get(STR_WNDSTATE_NORMAL);
		}
		else if( m_dwWndState == 3 )
		{
			strWndState = BkString::Get(STR_30MIN_NOTACTIVE);
		}

		return strWndState;
	}

	COLORREF GetItemStateColor()
	{
		COLORREF color(RGB(0x00, 0x00, 0x00));
		if (m_dwWndState == 1)
		{
			color = RGB(200, 0, 0);
		}
		else if (m_dwWndState == 0)
		{
			if (m_dwNotActiveTime >= 1800)
				color = RGB(0, 126, 0);
			else
				color = RGB(50, 100, 166);
		}
		else if( m_dwWndState == 3 )
		{
			color = RGB(0, 126, 0);
		}

		return color;
	}

	DWORD SetItemNotActiveTime()
	{
		return m_dwNotActiveTime;
	}
	
	DWORD GetItemState()
	{
		return m_dwWndState;
	}

private:
	HWND		m_hWnd;				// ���ھ��
	CString		m_strWndTitle;		// ���ڱ���
	HICON		m_hWndIcon;			// ����ͼ��
	DWORD		m_dwWndState;		// �Ƿ�δ��Ӧ����:1��δ��Ӧ��0��������2�����ڹرա�3��30����δ��Ӧ��
	DWORD		m_dwPID;			// ��Ӧ���̵�ID
	CString		m_strFilePath;		// ��Ӧ����ȫ·��
	HICON		m_hExeIcon;			// ��Ӧ���̵�ͼ��
	DWORD		m_dwNotActiveTime;	// δ��Ӧ��ʱ��
};