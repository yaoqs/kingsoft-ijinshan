#pragma once

#include "SoftMgrItemData.h"


class ISoftMgrUnistallCallbackEx
{
public:
	virtual void OnUninstallEx(int nListId, DWORD dwIndex) = 0;
	virtual void OnViewUninstallDetailEx(int nListId, DWORD dwIndex) = 0;
	virtual void OnDownloadIconFromUninstallEx(int nListId, CString strID) = 0;
	virtual void OnClearShortCutMenu(int nListId, CUninstallSoftInfo *pData) = 0;
	virtual void OnViewRudimentalInfo(int nListId, CUninstallSoftInfo *pData) = 0;
	virtual void OnStartProtection( int nListId, CUninstallSoftInfo *pData ) = 0;
};

class CSoftMgrUninstallListViewEx : public CWindowImpl<CSoftMgrUninstallListViewEx, CListViewCtrl>, 
	public COwnerDraw<CSoftMgrUninstallListViewEx>
{
public:
	CSoftMgrUninstallListViewEx();

	~CSoftMgrUninstallListViewEx();

public:
	enum  //list���
	{
		LIST_STYLE_NORMAL,		//һ��
		LIST_STYLE_DESKTOP,		//����
		LIST_STYLE_STARTMENU	//��ʼ�˵�
	};

protected:
	enum LASTSTATE
	{
		MOUSE_LASTON_NONE,
		MOUSE_LASTON_STATEBTN,
		MOUSE_LASTON_NAME,
		MOUSE_LASTON_SOFTICON,
		MOUSE_LASTON_CLEARICON,
		MOUSE_LASTON_VIEWDETAIL,
	};

public:
	BEGIN_MSG_MAP(CSoftMgrUninstallListViewEx)  
		MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST, WM_MOUSELAST, OnToolTipEvent) 
		MSG_WM_LBUTTONDBLCLK(OnLButtonDBClk)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MSG_WM_SETFOCUS(OnSetFocus)
		MSG_OCM_CTLCOLORLISTBOX(OnCtlColor)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CSoftMgrUninstallListViewEx>,1)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP() 

public:
	void OnSetFocus(HWND hWnd);

	LRESULT OnToolTipEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void CreateTipCtrl();

	HRESULT	OnMouseLeave( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bMsgHandled );

	HRESULT	OnMouseWheel( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bMsgHandled );

	void InitNormal();

	LRESULT	OnCtlColor(HDC hDc, HWND hWnd);

	CUninstallSoftInfo*	GetItemDataEx(DWORD dwIndex);

	int SetItemDataEx(DWORD dwIndex, DWORD_PTR dwItemData);

	BOOL GetItemRect(int nItem, LPRECT lpRect, UINT nCode);

	HRESULT	OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bMsgHandled );

	HRESULT	OnLButtonUp( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bMsgHandled );

	void SetClickLinkCallback( ISoftMgrUnistallCallbackEx* opCB );

	VOID SetPaintItem(BOOL bDrawItem);

	void MeasureItem(LPMEASUREITEMSTRUCT lpMes);

	HRESULT	OnMouseMove( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bMsgHandled );

	void _DrawItem(HDC hDC, LPDRAWITEMSTRUCT lpDrawItemStruct);

	void OnLButtonDBClk(UINT uMsg, CPoint ptx);

	void DrawItem ( LPDRAWITEMSTRUCT lpDrawItemStruct );

	void RefreshItem(int nIndex);

	void RefreshIcon(int nIndex);

	void DeleteAllItemsEx();

	void DeleteItem(LPDELETEITEMSTRUCT lParam);

	int GetItemCount();

	//Must be set after init immediately.
//	BOOL SetShowClearDesktopIcon(BOOL bShow = FALSE);
	void SetListViewID(int nListId);
	void SetListStyle(BOOL bRudimental);//�Ƿ��������
	void SetListType(int nType = LIST_STYLE_NORMAL);

public:
	BOOL		m_bHinting;

private:
	CRect m_rcIcon;				//ͼ��
	CRect m_rcName;				//�������
//	CRect m_rcDescription;		//�������
	CRect m_rcFrequency;		//ʹ��Ƶ��
	CRect m_rcSize;				//�����С
	CRect m_rcStateBtn;			//״̬��ť
	CRect m_rcUninsatll;
	CRect m_rcWaitUninstall;
	CRect m_rcViewDetail;		//�鿴�������
	CRect m_rcDeleteDesktopIcon;//ɾ������ͼ��
	CRect m_rcRudimental;		//����
	CRect m_rcPath;				//·��

	BOOL m_bDrawItem;			//�Ƿ�����Ҫ�ػ��Ƶ���
	BOOL m_bMouseOn;			//����Ƿ���״̬��ť��
	BOOL m_bMouseDown;			//����Ƿ���
	BOOL m_bMouseOnName;		//����������������
	BOOL m_bUninstalling;		//�Ƿ�����ɾ��
//	BOOL m_bShowClearShortCut;	//�Ƿ���ʾɾ������ͼ��

	

	BOOL m_bStyleRudiment;		//�Ƿ�Ϊ��������

	CFont		m_fntNameOn;	// �����������(��������棩
	CFont		m_fntNameNormal;// ����������壨��������£�
	CFont		m_fntPlug;		// �������
	CFont		m_fntDefault;	// һ������
	CFont		m_fntDanger;	// ������ʾ������

	CBrush	m_hBGBrush;			//����ˢ

	int m_nListID;

	CSimpleArray<CUninstallSoftInfo*>	m_arrData;
	ISoftMgrUnistallCallbackEx			*m_linkerCB;
	CToolTipCtrl				 m_wndToolTip;

	DWORD						 m_pHoverTip;
	DWORD						m_pRefresh;
	LASTSTATE					m_enumLastMSState;

	int		m_nListStyle;

	CDC	  m_dcMem;
	CBitmap m_bmpMem;
};
