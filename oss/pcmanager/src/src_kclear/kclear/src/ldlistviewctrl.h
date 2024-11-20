#pragma once

#include <wtlhelper/whwindow.h>
#include "ListViewCtrlEx.h"
#include "kuiwin/kuiskin.h"
#include "msgdefine.h"

//////////////////////////////////////////////////////////////////////////
//CLDListViewCtrl�����ݴ洢��ʽ
#define URL_COLOR RGB(0, 128, 0)
#define URL_COLOR2 RGB(77,113,149)
#define PRINTF_STR(x,y){_sntprintf_s((x), sizeof((x)), TEXT("%s"), (y));}
#define PRINTF_STR2(x,f,y){_sntprintf_s((x), sizeof((x)), (f), (y));}
#define PRINTF_INT(x,y){_sntprintf_s((x), sizeof((x)), TEXT("%d"), (y));}


#define ZEROMEM(x) ZeroMemory(x, sizeof(x))
#define SAFE_DELETE_PTR(x) if ((NULL != x)){delete (x); x = NULL;}
#define FILL_NOTIFY_MSG_STRUCT(m, w, l, id, s){s.uMsg = m; s.wParam = w; s.lParam = l, s.uCtrlID = id;}

#define LDLISTVIEWCTRL_COLOR_BEGIN
#define LDLISTVIEWCTRL_BK_COLOR RGB(255, 255, 255)
#define LDLISTVIEWCTRL_SEL_COLOR RGB(236, 241, 247)
#define LDLISTVIEWCTRL_LINE_COLOR RGB(211, 211, 211)
#define LDLISTVIEWCTRL_LINE_COLOREX RGB(234,233,225)
#define LDLISTVIEWCTRL_FONT_DEFAULT_COLOR RGB(0, 0, 0)
#define LDLISTVIEWCTRL_SUBITEMFONT_COLOR RGB(0x7e, 0x7e, 0x7e)//RGB(165,165,165)//RGB(153, 153, 153)
#define LDLISTVIEWCTRL_FONT_SEL_COLOR RGB(255, 255, 255)
#define COL_DEFAULT_WHITE_BG	RGB(0xfb,0xfc,0xfd)
#define LDLISTVIEWCTRL_COLOR_END

#define STR_BEGIN
#define STR_SUBITEM_EX_TXT_MARK_BEGIN TEXT("<EX>")
#define STR_SUBITEM_EX_TXT_MARK_END TEXT("</EX>")
#define STR_SUBITEM_TI_TXT_MARK_BEGIN TEXT("<TI>")
#define STR_SUBITEM_TI_TXT_MARK_END TEXT("</TI>")
#define STR_SUBITEM_URL_TXT_MARK_BEGIN TEXT("<URL>")
#define STR_SUBITEM_URL_TXT_MARK_END TEXT("</URL>")
#define STR_END


enum ENUM_SUBITEM_TYPE
{
	SUBITEM_TYPE_TEXT = 0,
	SUBITEM_TYPE_URL,
	SUBITEM_TYPE_IMAGE,//ָ����������һ��ͼƬ
	SUBITEM_TYPE_BUTTON,//ָ����������һ����ť
	SUBITEM_TYPE_WITH_IMAGE,//ָ�������а���һ��ͼƬ
	SUBITEM_TYPE_WITH_IMAGE_EX,
	SUBITEM_TYPE_UNKNOWN
};

enum ENUM_ITEM_TYPE
{
	ITEM_TYPE_NORMAL = 0,
	ITEM_TYPE_TITLE,
	ITEM_TYPE_URL,
	ITEM_TYPE_UNKNOWN
};
//ListView modle
enum ENUM_LISTVIEW_MODEL
{
	MODEL_NORMAL = 0,
	MODEL_TITLE,
	MODEL_UNKNOWN
};
enum ENUM_LISTVIEW_FONT
{
	FONT_NORMAT = 0,
	FONT_BOLD
};

//ÿһ�еĽṹ��Ϣ�洢
typedef struct _LDLISTVIEWCTRL_SUBITEM
{
	ENUM_SUBITEM_TYPE _enumType;//ÿһ�е�����
	ULONG _uSubItem;
	WCHAR _pszSubItemInfo[MAX_PATH];
	BOOL _bShowCheckBox;//�Ƿ���ʾCHECKBOX
	BOOL _bCheck;//CHECKBOX��װ�Ƿ���ѡ��״̬
	int _nGroupID;
	CRect _rcExTxt;
	COLORREF _colorExTxt;
	COLORREF _colorUrlTxt;
	COLORREF _colorTxt;
	CSimpleArray<LPCTSTR> _arrUrl;
	CSimpleArray<CRect> _arrUrlRect;
	CSimpleArray<CRect> _arrExTxtRect;
	ENUM_LISTVIEW_FONT _enumFont;
	int _ImageID;
	int _OffsetLeft;
	int nPercent;
	ULONGLONG nSize;
    CString _pszSubItemInfoBackup;
	_LDLISTVIEWCTRL_SUBITEM()
	{
		ZEROMEM(_pszSubItemInfo);
		_enumType = SUBITEM_TYPE_TEXT;
		_bCheck = FALSE;//Ĭ�ϲ�ѡ��
		_bShowCheckBox = FALSE;//Ĭ�ϲ���ʾCHECKBOX
		_nGroupID = -1;
		_rcExTxt = CRect(0, 0, 0, 0);
		_colorExTxt = LDLISTVIEWCTRL_FONT_DEFAULT_COLOR;
		_colorTxt = LDLISTVIEWCTRL_FONT_DEFAULT_COLOR;
		_colorUrlTxt = LDLISTVIEWCTRL_FONT_DEFAULT_COLOR;
		_arrExTxtRect.RemoveAll();
		_arrUrl.RemoveAll();
		_arrUrlRect.RemoveAll();
		_enumFont = FONT_NORMAT;
		_ImageID = -1;
		_OffsetLeft = 0;//���ƫ��
	}
	int PushUrl(LPCTSTR pszUrl)
	{
		_arrUrl.Add(pszUrl);
		return _arrUrl.GetSize();
	}
}LDListViewCtrl_SubItem, *LPLDListViewCtrl_SubItem;
//ÿһ�е���Ϣ�洢�ṹ
typedef struct _LDLISTVIEWCTRL_ITEM
{
	ULONG _uGroup;//����ID
	ULONG _uItemID;//�к�
	BOOL _bShowCheckBox;//�Ƿ���ʾCHECKBOX
	BOOL _bCheck;//CHECKBOX��װ�Ƿ���ѡ��״̬
	WCHAR _pszGroupCaption[MAX_PATH];
	CSimpleArray<LDListViewCtrl_SubItem*> _arrSubItem;
	ENUM_ITEM_TYPE _enumItemType;
	CRect _rcCheckBox;
	BOOL _bExpand;
	LPVOID _pExPtr;
	CRect _rcExpand;
	int _nTxtCheckBox;
	BOOL _bUserExpand;
	DWORD _uResverd[3];
	WCHAR _pszExInfo[MAX_PATH];
	WCHAR _pszExInfo2[MAX_PATH];
	CString _pszSubPath;
	ULONGLONG nSize;
	_LDLISTVIEWCTRL_ITEM()
	{
		_enumItemType = ITEM_TYPE_NORMAL;
		_uItemID = 0;
		_rcCheckBox = CRect(0, 0, 0, 0);
		_arrSubItem.RemoveAll();
		ZEROMEM(_pszGroupCaption);
		_bCheck = FALSE;//Ĭ�ϲ�ѡ��
		_bExpand = TRUE;
		_bShowCheckBox = FALSE;//Ĭ�ϲ���ʾCHECKBOX
		_pExPtr = NULL;
		_rcExpand.IsRectEmpty();
		_bUserExpand = TRUE;
		_nTxtCheckBox = 0;
		_uGroup = -1;
		ZEROMEM(_pszExInfo);
		ZEROMEM(_pszExInfo2);
	}
	~_LDLISTVIEWCTRL_ITEM()
	{
		int count = _arrSubItem.GetSize();
		for (int i = 0; i < count; i++)
		{
			SAFE_DELETE_PTR(_arrSubItem[i]);
		}
		_arrSubItem.RemoveAll();
	}
public:
	int PushSubItem(LDListViewCtrl_SubItem* pSubItem)
	{
		int count = _arrSubItem.GetSize();
		if (NULL == pSubItem)
			return count;
		_arrSubItem.Add(pSubItem);

		return ++count;
	}
}LDListViewCtrl_Item,*LPLDListViewCtrl_Item;

struct LDLISTVIEW_MSG_NOTIFY
{
	UINT uMsg;
	WPARAM wParam;
	LPARAM lParam;
	UINT uCtrlID;
	DWORD dwReserved[6];
};


class CLDListViewCtrl:
	public CWindowImpl<CLDListViewCtrl, CListViewCtrl>,
	public COwnerDraw<CLDListViewCtrl>
{
public:
	CLDListViewCtrl(void);
	~CLDListViewCtrl(void);
	HWND SetNotifyHwnd(HWND hWnd);
	int DeleteAllItems();
	int DeleteItem(int nItem);
	HWND Create(HWND hWndParent, _U_RECT rect = NULL, LPCTSTR szWindowName = NULL, 
				DWORD dwStyle = 0, DWORD dwExStyle = 0, _U_MENUorID MenuOrID = 0U, 
				LPVOID lpCreateParam = NULL);
	ULONG SetHeaderHeight(ULONG uHeight);
	void ExpandItem(int nItem, BOOL bExpand);//չ��
	int InsertItem(int nItem, LPLDListViewCtrl_Item lpItemData);//��������
	int SetItemHeight(ULONG uHeight = 0);
	BOOL SetBorder(BOOL bBorder, COLORREF color = RGB(0, 200,0));
	BOOL SetFrameLine(BOOL bDot);
	BOOL SetCheckState(int nItem, BOOL bCheck = TRUE);
	BOOL GetCheckState(int nIndex);
	BOOL SetUrlHand(BOOL bHand);
	BOOL SetExTxtHand(BOOL bHand);
	ENUM_LISTVIEW_MODEL SetListViewModel(ENUM_LISTVIEW_MODEL model);
	BOOL SetSplitLines(BOOL bSplitLines);
	BOOL SetFullRowUpdateCheckBox(BOOL bFullRow = FALSE);
	BOOL SetSelState(BOOL bSet = TRUE);
	int PushSubItemImage(DWORD dwImageID);//���������Ŀ��Ҫʹ��IMAGE�Ļ�����Ҫ��ǰ������ָ����Ҫ��IMAGE
	void DrawItem(LPDRAWITEMSTRUCT lpItemStruct);
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	int CompareItem(LPCOMPAREITEMSTRUCT lpComplateItemStruct);
	void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	HBITMAP SetSubItemImage(const std::string& strImageId, int subItemImageWidth);
	int MoveTo(int nOldID, int nNewID);
	COLORREF SetBkColor(COLORREF bkColor);
	BOOL SetCheckBoxHand(BOOL bHand);
	BOOL SetExpandRectHand(BOOL bHand);
	static int CALLBACK SortFuncASC(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) ;
	static int CALLBACK SortFuncASCEx(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) ;
	void LocateFilePath(const std::wstring& strFilePath);
    BOOL GetSubItemRect( int nItem, int nSubItem, int nArea, LPRECT rect );
	void DisableFillFlag();

protected:
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	//HRESULT OnOnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bMsgHandled );
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	LRESULT OnNMClick(LPNMHDR pnmh);
	LRESULT OnNMDClick(LPNMHDR pnmh);
	BOOL OnEraseBkgnd(CDCHandle dc);
	void OnVScroll(UINT nSBCode, UINT nPos, HWND hWnd);
	LRESULT OnMouseWhell(UINT fwKey, short zDela, CPoint pt);
	BOOL OnToolTipText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	LRESULT OnReflectedNotifyRangeHandlerEX(LPNMHDR pnmh);
	LRESULT OnMouseHover(WPARAM wParam, CPoint ptPos);
	LRESULT OnMouseLeave();
	LRESULT OnWmLBtnColunm( UINT uMsg, WPARAM wParam, LPARAM lParam );
	LRESULT OnToolTipEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

	BEGIN_MSG_MAP_EX(CLDListViewCtrl)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		MSG_WM_VSCROLL(OnVScroll)
		MSG_WM_HSCROLL(OnVScroll)
		MSG_WM_MOUSEWHEEL(OnMouseWhell)
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSELEAVE(OnMouseLeave);
		REFLECTED_NOTIFY_CODE_HANDLER_EX(NM_CLICK, OnNMClick)
		REFLECTED_NOTIFY_CODE_HANDLER_EX(NM_DBLCLK, OnNMDClick)
//		REFLECTED_NOTIFY_RANGE_HANDLER_EX(0, 0xffff, OnReflectedNotifyRangeHandlerEX)
		MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST, WM_MOUSELAST, OnToolTipEvent)

		MESSAGE_HANDLER_EX(MSG_CLR_COLUNM_CLICK,OnWmLBtnColunm)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CLDListViewCtrl>,1)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

private:
	void ReleaseBuf();//�ͷ��ڴ�
	void _DrawLine(CDC& memDC, CPoint ptStart, CPoint ptEnd, COLORREF color, DWORD dwPenTyple =PS_SOLID);//h����
	void _DrawBorder(CDC& memDC);//���Ʊ߿�
	void _DrawItemBKColor(CDC& memDC, int nItem, BOOL bSelected = FALSE);//���Ʊ�����ɫ
	void _DrawItemText(CDC& memDC, int nItem, int nSubItem, COLORREF colorText, LPCTSTR pszText = NULL, BOOL bTitle = FALSE);//�����ı�
	void _DrawItemText(CDC& memDC, CRect& rcItem, LPCTSTR pszText, COLORREF colorText = LDLISTVIEWCTRL_FONT_DEFAULT_COLOR, HFONT hFont = KuiFontPool::GetFont(KUIF_DEFAULTFONT), BOOL bTitle = FALSE);//�����ı�����ָ���ľ�������
	void _DrawCheckBox(CDC& memDC, int nItem, BOOL bCheck , CRect &rcCheckBox);//����CHECKBOX
	void _DrawTitle(CDC& memDC, int nItem, LPLDListViewCtrl_Item pItemStruct);//���Ʊ���
	void _DrawText(CDC& memDC, int nItem, LPLDListViewCtrl_Item pItemStruct);//������ͨ�ı�
	BOOL _GetSelected(){return m_bSelState && m_bSelected;};
	void _UpdateCheckBoxState(CPoint pt, LPLDListViewCtrl_Item pItemStruct);//����CHECKBOX��״̬
	void _ExpandItem(int nItem, LPLDListViewCtrl_Item pItemStruct);
	void _Expand(int nGroup, int nCurItem, BOOL bExpand);//չ��
	void _InsertItemData(int nIndex, LPLDListViewCtrl_Item lpItemData);//��������
	void _DrawItemText(CDC& memDC, CRect rcItem, LPLDListViewCtrl_SubItem pSubItem, BOOL bTitle = FALSE);
	int _PointInUrlRect(int nItem, CPoint pt, int& nSubItem);//�жϵ�ǰ����λ���ǲ�����URL�ı�����,������򷵻�>=0�����֣���ʾ��ǰ�����ʵ�ڵڼ�����������
	int _PointInExTxtRect(int nItem, CPoint pt);//�жϵ�ǰ����λ���ǲ����������ı�����,������򷵻�>=0�����֣���ʾ��ǰ�����ʵ�ڵڼ�����������
	void _OnLButtonUpOnAnUrl(int nItem, int nIndexUrl, int nSubItem);//���������һ��URL��ʱ�򣬾ͻ�ִ���������
	void _OnLButtonUpOnAnExTxt(int nItem, int nIndexExTxt);//���������EXTXT��ʱ�򣬾ͻ�ִ���������
	void _OnLButtonUpOnAnButton(int nItem, int nIndexRext);
	LPTSTR _GetAnUrl(int nItem, int nIndexUrl);//��ȡĳ��ָ����URL
	LPLDListViewCtrl_Item _GetItemData(int nItem);
	void _DeleteAnGroupData(int nGroup);//ɾ��ָ�������µ��������ݣ�������TITLE
	int _HitTest(CPoint pt);
	int _DrawImageSubItem(CDC& memDC, int nItem, int nSubItem, LPLDListViewCtrl_SubItem pItemStruct);
	int _DrawButtonSubItem(CDC& memDC, int nItem, int nSubItem, LPLDListViewCtrl_SubItem pItemStruct);
	int _PointInButtonRect(int nItem, CPoint point);
	int _PointInCheckBox(int nItem, CPoint point);
	int _PointInExPandRect(int nItem, CPoint point);
	int _DrawImageSubItem2(CDC& memDC, CRect rc, CRect& ImageRc, LPLDListViewCtrl_SubItem pSubItem);
	int _DrawImageSubItem3(CDC& memDC, int nItem, CRect rc, CRect& ImageRc, LPLDListViewCtrl_SubItem pSubItem,BOOL bCheckbox);

	CSimpleArray<LPLDListViewCtrl_Item> m_arrListViewItem;
	ULONG m_uHeight;
	COLORREF m_colorBorder;
	BOOL m_bDrawBorder;
	BOOL m_bDotFrameLine;
	HBITMAP m_hCheckBitmp;
	BOOL m_bSelected;
	HWND m_hNotifyHwnd;
	CHeaderCtrlEx m_ListViewHeader;
	BOOL m_bUrlHand;
	BOOL m_bExTxtHand;
	ENUM_LISTVIEW_MODEL m_ListViewModel;
	BOOL m_bSplitLines;//�Ƿ���Ʒָ���
	BOOL m_bItemUpdateCheckBox;//�Ƿ��ǵ������ѡ��
	int m_nSelItem;//��ǰѡ�е���
	BOOL m_bSelState;//�Ƿ���ʾѡ��״̬
	DWORD m_dwCtrlID;
//	CSimpleArray<HBITMAP> m_arrImage;
	HBITMAP m_hSubItemImage;
	int m_nSubItemWidth;
	CKuiSkinBase *m_pBtnSkin;
	CSimpleMap<int,CRect> m_mapBtnRect;
	CSimpleMap<int,CRect> m_mapBtnRect2;
	int m_btnState;
//	HICON m_hIconFile;
	CKuiSkinBase *m_pImageSkin;
	CKuiImageSkin *m_pImageSkinEx;
	COLORREF m_bkColor;
	BOOL m_bCheckBoxHand;
	BOOL m_bExpandRectHand;
	BOOL m_bNextFlag;
	CToolTipCtrl m_wndToolTip;

};
