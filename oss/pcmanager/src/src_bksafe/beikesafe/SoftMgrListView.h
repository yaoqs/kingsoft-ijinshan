#ifndef _SOFT_MGR_LISTVIEW_H_
#define _SOFT_MGR_LISTVIEW_H_

#include "beikecolordef.h"
#include "SoftMgrItemData.h"

enum E_SoftMgrListItemType
{
	SOFTMGR_LISTITEM_TITLE		= 1,
};

#define PAGE_ITEM_MAX_COUNT 50
#define PAGE_ITEM_WIDTH		25
#define PAGE_ITEM2_WIDTH	50
#define PAGE_ITEM_SPACE		4

#define BTN_COLUMN_WIDTH	120
#define TIME_COLUMN_WIDTH	100
#define SIZE_COLUMN_WIDTH	100

class ISoftMgrCallback
{
public:
	virtual void OnViewDetail(DWORD dwIndex) = 0; //�鿴�������
	virtual void OnViewNew(DWORD dwIndex) = 0; //�鿴�������
	virtual void OnDownLoad(DWORD dwIndex) = 0;	//����
	virtual void OnContinue(DWORD dwIndex) = 0;	//����
	virtual void OnPause(DWORD dwindex) = 0;	//��ͣ
	virtual void OnCancel(DWORD dwIndex) = 0;	//ȡ��
	virtual void OnDownLoadIcon(CString strID) = 0;
	virtual void OnFreebackFromList(DWORD dwIndex) = 0;
	virtual void OnTautilogyFromList(DWORD dwIndex) = 0;
	virtual void OnSwitchPage(DWORD dwPage) = 0;
	virtual void OnDaquanSoftMark(DWORD dwIndex) = 0;
};

class CSoftMgrListView : public CWindowImpl<CSoftMgrListView, CListViewCtrl>, 
	public COwnerDraw<CSoftMgrListView>
{
public:
	CSoftMgrListView()
	{
		m_bShowType = FALSE;
		//m_rcCheck = CRect(10, 20, 23, 33);
		//m_rcIcon = CRect(28, 11, 60, 43);
		//m_rcName = CRect(68, 9, 128, 23);
		m_rcCheck = CRect(0,0,0,0);
		m_rcIcon = CRect(10, 11, 42, 43);
		m_rcName = CRect(50, 9, 110, 23);
		m_rcDescription = CRect(50, 33, 110, 45);

		m_rcTautology = CRect(0,0,0,0);
		m_rcFreeback = CRect(0,0,0,0);
		m_rcInstall = CRect(0,0,0,0);
		m_rcWaitDownload = CRect(0,0,0,0);

		m_bDrawItem = FALSE;
		m_bMouseOn = FALSE;
		m_bMouseDown = FALSE;
		m_bMouseOnPause = FALSE;
		m_bMouseOnCancel = FALSE;
		m_bMouseOnName = FALSE;

		m_pHoverTip = 0;
		m_nCurPage = 0;
		m_nItemCount = 0;

		m_fntNameOn.Attach( BkFontPool::GetFont(FALSE,TRUE,FALSE,0));
		m_fntNameNormal.Attach( BkFontPool::GetFont(TRUE, FALSE, FALSE, 0));
		m_fntPlug.Attach( BkFontPool::GetFont(BKF_DEFAULTFONT));
		m_fntDanger.Attach( BkFontPool::GetFont(BKF_BOLDFONT));
		m_fntDefault.Attach( BkFontPool::GetFont(BKF_DEFAULTFONT));

		m_nNameSort = SORT_TYPE_UNKNOW;
		m_nSizeSort = SORT_TYPE_UNKNOW;
		m_nTimeSort = SORT_TYPE_UNKNOW;
	}

	~CSoftMgrListView()
	{
		if(m_hWnd != NULL)
		{
			DeleteAllItems();
		}

		m_fntNameOn.Detach();
		m_fntNameNormal.Detach();
		m_fntPlug.Detach();
		m_fntDanger.Detach();
		m_fntDefault.Detach();
	}
protected:
	enum LASTSTATE
	{
		MOUSE_LASTON_NONE,
		MOUSE_LASTON_STATEBTN,
		MOUSE_LASTON_NAME,
		MOUSE_LASTON_CANCELBTN,
		MOUSE_LASTON_CONTINUEBTN,
		MOUSE_LASTON_SOFTICON,
		MOUSE_LASTON_FREEBACK,
		MOUSE_LASTON_TAUTOLOGY,
		MOUSE_LASTON_DESCRIPTION,
		MOUSE_LASTON_MARK,
		MOUSE_LASTON_NEWINFO,
	};

	enum SortType
	{
		SORT_TYPE_UNKNOW = 0,
		SORT_TYPE_UP,
		SORT_TYPE_DOWN,
	};

public:
	BEGIN_MSG_MAP(CSoftMgrListView)  
		MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST, WM_MOUSELAST, OnToolTipEvent) 
		MSG_WM_LBUTTONDBLCLK(OnLButtonDBClk)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MSG_OCM_CTLCOLORLISTBOX(OnCtlColor)
		MSG_WM_SIZE(OnSize)
		MSG_WM_SETFOCUS(OnSetFocus)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CSoftMgrListView>,1)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()   

	void SetShowType(BOOL bShow = FALSE);
	void OnSetFocus(HWND hWnd);
	HRESULT	OnMouseLeave( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bMsgHandled );
	BOOL OnEraseBkgnd(CDCHandle dc);
	HRESULT	OnMouseWheel( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bMsgHandled );
	void OnLButtonDBClk(UINT uMsg, CPoint ptx);

	LRESULT OnToolTipEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnSize(UINT nType, CSize size);
	void SetLoadShow(BOOL bShow=TRUE);
	void CreateTipCtrl();
	void SetShowDlgState();

	void InitNormal();
	void InitDownLoad();

	LRESULT	OnCtlColor(HDC hDc, HWND hWnd);

	CSoftListItemData*	GetItemDataEx(DWORD dwIndex);

	int SetItemDataEx(DWORD dwIndex, DWORD_PTR dwItemData);

	BOOL GetItemRect(int nItem, LPRECT lpRect, UINT nCode);
	HRESULT	OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bMsgHandled );

	HRESULT	OnLButtonUp( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bMsgHandled );

	void SetClickLinkCallback( ISoftMgrCallback* opCB );

	VOID SetPaintItem(BOOL bDrawItem);

	void MeasureItem(LPMEASUREITEMSTRUCT lpMes);

	HRESULT	OnMouseMove( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bMsgHandled );

	void DrawItem ( LPDRAWITEMSTRUCT lpDrawItemStruct );

	void SetCheckedAllItem(BOOL bChecked);

	void RefreshItem(int nIndex);

	void RefreshProgress(int nIndex);

	void RefreshButton(int nIndex);
	void RefreshRight(int nIndex);
	void RefreshIcon(int nIndex);

	BOOL FindItem(CSoftListItemData *pData);

	void DeleteAllItemsEx(); //����б�ҳɾ������

	void ClearAllItemData(); //ֻ����б���ɾ������
	void DeleteItem(LPDELETEITEMSTRUCT lParam);

	int GetItemCount();
	void AppendPageItem(int nCurPage, int nItemCount);
	void UpdateBtnRect();

	CSimpleArray<CSoftListItemData*>& GetItemArray() 
	{ return m_arrData; }
	BOOL GetSoftType(int nListIndex);
	void UpdateAll();
	int GetListCenterPos(int nListIndex);

protected:
	void _DrawSoftItem(HDC hDC, LPDRAWITEMSTRUCT lpDrawItemStruct);
	void _DrawPageItem(HDC hDC, LPDRAWITEMSTRUCT lpDrawItemStruct);

	void _MouseMoveSoftItem(CSoftListItemData* pData, POINT pts, CRect rcItem);
	void _MouseMovePageItem(CSoftListItemData* pData, POINT pts, CRect rcItem);
	void _LButtonDownSoftItem(CSoftListItemData* pData, POINT pts, CRect rcItem, BOOL &bMsgHandled );
	void _LButtonDownPageItem(CSoftListItemData* pData, POINT pts, CRect rcItem, BOOL &bMsgHandled );
	void _LButtonUpSoftItem(CSoftListItemData* pData, POINT pts, CRect rcItem, int nIndex);
	void _LButtonUpPageItem(CSoftListItemData* pData, POINT pts, CRect rcItem, int nIndex);

public:
	SortType	m_nNameSort;
	SortType	m_nSizeSort;
	SortType	m_nTimeSort;

	BOOL m_bShowType;			//�Ƿ�������ǰ��ʾ����
	CRect m_rcCheck;			//ѡ���
	CRect m_rcIcon;				//ͼ��
	CRect m_rcName;				//�������
	CRect m_rcDescription;		//�������
	CRect m_rcSize;				//�����С
	CRect m_rcStar;				//��������
	CRect m_rcMark;				//����
	CRect m_rcStateBtn;			//״̬��ť
	CRect m_rcCancel;			//ȡ����ť
	CRect m_rcContinue;			//������ť
	CRect m_rcState;			//״̬���������ٶ�
	CRect m_rcPlug;				//���
	CRect m_rcCharge;			//�շ�
	CRect m_rcProgress;			//���ؽ�����
	CRect m_rcValue;			//����ֵ
	CRect m_rcLink;				//�������ӷ�����
	CRect m_rcFreeback;			//����
	CRect m_rcTautology;		//����
	CRect m_rcInstall;			//��װ
	CRect m_rcWaitInstall;		//�ȴ���װ
	CRect m_rcWaitDownload;		//�ȴ�����
	CRect m_rcUseOnKey;			//���ڱ�����װ��ʹ��ʱ���ΰ�ť,��ʾ���ڰ�װ

	BOOL m_bDrawItem;			//�Ƿ�����Ҫ�ػ��Ƶ���
	CBrush	m_hBGBrush;			//����ˢ
	BOOL m_bMouseOn;			//����Ƿ���״̬��ť��
	BOOL m_bMouseDown;			//����Ƿ���
	BOOL m_bMouseOnPause;		//�������ͣ��ť��
	BOOL m_bMouseOnCancel;		//�����ȡ����ť��
	BOOL m_bMouseOnName;		//����������������
	BOOL m_bMouseOnFreeback;
	BOOL m_bMouseOnTautology;

	CFont		m_fntNameOn;	// �����������(��������棩
	CFont		m_fntNameNormal;// ����������壨��������£�
	CFont		m_fntPlug;		// �������
	CFont		m_fntDefault;	// һ������
	CFont		m_fntDanger;	// ������ʾ������

	CSimpleArray<CSoftListItemData*>	m_arrData;
	ISoftMgrCallback			*m_linkerCB;
	CToolTipCtrl				 m_wndToolTip;
	CBkDialogView				 m_dlgMsg;

	DWORD						 m_pHoverTip;
	DWORD						m_pRefresh;
	LASTSTATE					m_enumLastMSState;

	CDC	  m_dcMem;
	CBitmap m_bmpMem;

	CSoftListItemData m_pDataPageItem;
	int m_nCurPage;
	int m_nItemCount;
	BOOL m_bPageBtnEnableEx[14];
	CRect m_rcPageBtnEx[14];
	int m_nPageBtnEx[14];
};

#endif