#pragma once

/*
* @file    softmgrRubbishListView.h
* @brief   �������--���ع���--������
*/


#include "beikecolordef.h"
#include "SoftMgrItemData.h"

class ISoftMgrRubbishCallback
{
public:
	virtual void OnResume(CString strId) = 0;	//��ԭ
	virtual void OnLbuttonUpNotifyEx(DWORD dwIndex) = 0;
};

class CSoftMgrRubbishListView : public CWindowImpl<CSoftMgrRubbishListView, CListViewCtrl>, 
	public COwnerDraw<CSoftMgrRubbishListView>
{
public:
	CSoftMgrRubbishListView();
	~CSoftMgrRubbishListView();

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
		MOUSE_LASTON_TAUTOLOGY
	};

public:
	BEGIN_MSG_MAP(CSoftMgrRubbishListView)  
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MSG_OCM_CTLCOLORLISTBOX(OnCtlColor)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CSoftMgrRubbishListView>,1)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()   

	CSimpleArray<CSoftListItemData*>& GetItemArray();
	void UpdateAll();

	HRESULT	OnMouseWheel( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bMsgHandled );

	void InitNormal();

	LRESULT	OnCtlColor(HDC hDc, HWND hWnd);

	CSoftListItemData*	GetItemDataEx(DWORD dwIndex);

	int SetItemDataEx(DWORD dwIndex, DWORD_PTR dwItemData);

	BOOL GetItemRect(int nItem, LPRECT lpRect, UINT nCode);

	HRESULT	OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bMsgHandled );

	HRESULT	OnLButtonUp( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bMsgHandled );

	void SetClickLinkCallback( ISoftMgrRubbishCallback* opCB );

	VOID SetPaintItem(BOOL bDrawItem);

	void MeasureItem(LPMEASUREITEMSTRUCT lpMes);

	HRESULT	OnMouseMove( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bMsgHandled );

	void _DrawItem(HDC hDC, LPDRAWITEMSTRUCT lpDrawItemStruct);

	void DrawItem ( LPDRAWITEMSTRUCT lpDrawItemStruct );

	void SetCheckedAllItem(BOOL bChecked);

	void RefreshItemCheckedState(int nIndex);

	void RefreshItem(int nIndex);

	void DeleteAllItemsEx(); //����б�ҳɾ������

	void ClearAllItemData(); //ֻ����б���ɾ������

	void DeleteItem(LPDELETEITEMSTRUCT lParam);

	void ReQueueList(int nIndex);

	int GetItemCount();

private:
	CRect m_rcCheck;			//ѡ���
	CRect m_rcIcon;				//ͼ��
	CRect m_rcName;				//�������
	CRect m_rcDescription;		//�������
	CRect m_rcSize;				//�����С
	CRect m_rcStateBtn;			//״̬��ť
	CRect m_rcState;			//��װ

	BOOL m_bDrawItem;			//�Ƿ�����Ҫ�ػ��Ƶ���
	CBrush	m_hBGBrush;			//����ˢ
	BOOL m_bMouseOn;			//����Ƿ���״̬��ť��
	BOOL m_bMouseDown;			//����Ƿ���
	BOOL m_bMouseOnName;		//����������������

	CFont		m_fntNameOn;	// �����������(��������棩
	CFont		m_fntNameNormal;// ����������壨��������£�
	CFont		m_fntDefault;	// һ������

	CSimpleArray<CSoftListItemData*>	m_arrData;
	ISoftMgrRubbishCallback			*m_linkerCB;

	LASTSTATE					m_enumLastMSState;
	CDC	  m_dcMem;
	CBitmap m_bmpMem;
};
