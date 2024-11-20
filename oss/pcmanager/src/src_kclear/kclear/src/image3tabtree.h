#pragma  once

#include <wtlhelper/kuifolderbrowsectrl.h>
#include "kscbase/kscres.h"

// ǿ����ɨ��ʹ�õ�tree�� ����������в�ͬ�� ���ӽڵ�ȫѡ��ʱ���ڵ��� checked�� ������mixed
class CWH3StateCheckTreeCtrl10
	: public CWindowImpl<CWH3StateCheckTreeCtrl10, CTreeViewCtrl>
{
public:

	enum {
		CHECK_STATE_NONE      = 0,
		CHECK_STATE_UNCHECKED,
		CHECK_STATE_CHECKED,
		CHECK_STATE_MIXED,
	};

	BOOL GetCheckState(HTREEITEM hItem)
	{
		return CHECK_STATE_CHECKED == (GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12);
	}

	BOOL GetCheckStateEx(HTREEITEM hItem)
	{
		int nRet = -1;
		BOOL bRet = FALSE;
		nRet = GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12;
		if (nRet == CHECK_STATE_MIXED || nRet == CHECK_STATE_CHECKED)
		{
			bRet = TRUE;
		}
		else
		{
			bRet = FALSE;
		}
		return bRet;
	}
	//״̬����
	void SetState(HTREEITEM hItem,UINT nState)
	{
		SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
		GetState(hItem);
	}
	UINT GetState(HTREEITEM hItem)
	{
		UINT nState = 0;
		nState = GetItemState( hItem , TVIS_STATEIMAGEMASK );
		nState = nState>>12;
		return nState;
	}
	void SetRootVisible()
	{
		SelectSetFirstVisible(GetRootItem());
	}
	void TravelSiblingAndParent(HTREEITEM hItem, int nState)
	{
		//���Ҹ��ڵ㣬û�оͽ���
		HTREEITEM hParentItem;
		hParentItem=GetParentItem(hItem);
		if(hParentItem==NULL)
			return;
		if( nState == 2 )
		{//ֻҪ�˽ڵ�Ϊ��ѡ���丸�ڵ�һ���ǰ�ѡ
			SetState(hParentItem,nState);
			TravelSiblingAndParent(hParentItem,nState);
			return;
		}
		HTREEITEM hSibItem;
		hSibItem = GetChildItem(hParentItem);
		while( hSibItem )
		{
			if( nState != GetState(hSibItem) )
			{	//����ֵܽڵ�״̬��һ�������ı丸�ڵ�Ϊ��ѡ
				SetState(hParentItem,2);
				TravelSiblingAndParent(hParentItem,2);
				return;
			}
			hSibItem = GetNextSiblingItem(hSibItem);
		}
		//����ֵܽڵ�״̬һ�������ı丸�ڵ�Ϊ�˽ڵ�״̬
		SetState(hParentItem,nState);
		TravelSiblingAndParent(hParentItem,nState);
	}
	BOOL SetItemCheck(HTREEITEM hItem)
	{
		UINT nState = GetState(hItem);
		switch(nState)
		{
		case 1:
			SetState(hItem,3);
			nState = 3;
			break;
		case 2:
			SetState(hItem,3);
			nState = 3;
			break;
		case 3:
			SetState(hItem,1);
			nState = 1;
			break;
		default:
			break;
		}
		TravelChild(hItem, nState);
		TravelSiblingAndParent(hItem,nState);
		return nState;	
	}
	void SetItemCheck(CString strName,UINT nState)
	{
		HTREEITEM hBrotherItem;
		SetChildCheck(GetRootItem(), strName, nState);

		hBrotherItem=GetNextSiblingItem(GetRootItem());
		while (hBrotherItem)
		{
			SetChildCheck(hBrotherItem, strName, nState);
			hBrotherItem=GetNextSiblingItem(hBrotherItem);
		}

	}
	void SetChildCheck(HTREEITEM hItem,CString strName, UINT nState)
	{
		HTREEITEM hChildItem,hBrotherItem;

		//�����ӽڵ㣬û�оͽ���
		hChildItem=GetChildItem(hItem);
		if(hChildItem!=NULL)
		{
			CString strBuff;
			GetItemText(hChildItem, strBuff);
			int n = strBuff.Find(L"��");
			if(n>0)
			{
				strBuff = strBuff.Left(n);
			}
			if(strBuff == strName)
			//�����ӽڵ��״̬�뵱ǰ�ڵ��״̬һ��
			{
				SetState( hChildItem, nState );
				/*ResetItemState(GetParentItem(hChildItem));*/
				SetState(GetParentItem(hChildItem),Set2Item(GetParentItem(hChildItem)));
			}

			//�ٵݹ鴦���ӽڵ���ӽڵ���ֵܽڵ�
			SetChildCheck(hChildItem, strName, nState);

			//�����ӽڵ���ֵܽڵ�����ӽڵ�
			hBrotherItem=GetNextSiblingItem(hChildItem);
			while (hBrotherItem)
			{
				CString strBuff;
				GetItemText(hBrotherItem, strBuff);
				int n = strBuff.Find(L"��");
				if(n>0)
				{
					strBuff = strBuff.Left(n);
				}
				if(strBuff == strName)
				//�����ӽڵ���ֵܽڵ�״̬�뵱ǰ�ڵ��״̬һ��
				{
					SetState( hBrotherItem, nState );
					//ResetItemState(GetParentItem(hBrotherItem));
					SetState(GetParentItem(hBrotherItem),Set2Item(GetParentItem(hBrotherItem)));
				}
				//�ٵݹ鴦���ӽڵ���ֵܽڵ���ӽڵ���ֵܽڵ�
				SetChildCheck(hBrotherItem, strName, nState);
				hBrotherItem=GetNextSiblingItem(hBrotherItem);
			}
		}
	}
	void SetItemCheck(HTREEITEM hItem, UINT nState)
	{
		HTREEITEM hBrotherItem;
		TravelChild(hItem, nState);
		SetState(hItem, nState);
		hBrotherItem=GetNextSiblingItem(hItem);
		while (hBrotherItem)
		{
			TravelChild(hBrotherItem, nState);
			SetState(hBrotherItem, nState);
			hBrotherItem=GetNextSiblingItem(hBrotherItem);
		}
	}
	void Set2ItemState(HTREEITEM hItem)
	{
		HTREEITEM hBrotherItem;
		SetState(hItem,Set2Item(hItem));
		hBrotherItem=GetNextSiblingItem(hItem);
		while (hBrotherItem)
		{
			SetState(hBrotherItem,Set2Item(hBrotherItem));
			hBrotherItem=GetNextSiblingItem(hBrotherItem);
		}
	}
	BOOL Set2Item(HTREEITEM hItem)
	{
		HTREEITEM hChildItem,hBrotherItem;
		//�����ӽڵ㣬û�оͽ���
		hChildItem=GetChildItem(hItem);
		if(hChildItem!=NULL)
		{
			UINT nState = GetState(hChildItem);
			TravelChild(hChildItem, nState);
			BOOL bState = 0;
			//�����ӽڵ���ֵܽڵ�����ӽڵ�
			hBrotherItem=GetNextSiblingItem(hChildItem);
			while (hBrotherItem)
			{
				UINT nState1;
				//�ٵݹ鴦���ӽڵ���ֵܽڵ���ӽڵ���ֵܽڵ�
				nState1 = GetState(hBrotherItem);
				TravelChild(hBrotherItem, nState1);
				//�ֵܽڵ�״̬��ͬ��ǿ����Ϊ3		
				if(nState1 != nState)bState = 2;
				else 
				{
					if(bState != 2)
					{
						bState = 1;
					}
				}
				hBrotherItem=GetNextSiblingItem(hBrotherItem);
			}
			if(bState ==1)
			{
				//�ֵܽڵ�״̬��ͬ������ǰ�ڵ�״̬
				UINT nParentState = GetState(hChildItem);
				return nParentState;
			}
			else if(bState == 2)
			{
				return 3;
			}
			else
			{
				//���ֵܽڵ㣬����ǰ�ڵ�״̬
				return nState;
			}
		}
		//���ص�ǰ�ڵ�״̬
		return GetState(hItem);
	}
	void ResetItemState(HTREEITEM hItem)
	{
		HTREEITEM hBrotherItem;
		SetState(hItem,ResetItem(hItem));
		hBrotherItem=GetNextSiblingItem(hItem);
		while (hBrotherItem)
		{
			SetState(hBrotherItem,ResetItem(hBrotherItem));
			hBrotherItem=GetNextSiblingItem(hBrotherItem);
		}
	}
	BOOL ResetItem(HTREEITEM hItem)
	{
		HTREEITEM hChildItem,hBrotherItem;
		//�����ӽڵ㣬û�оͽ���
		hChildItem=GetChildItem(hItem);
		if(hChildItem!=NULL)
		{
			UINT nState;
			//�ٵݹ鴦���ӽڵ���ӽڵ�
			nState = ResetItem(hChildItem);
			//���趨��ǰ�ڵ�״̬
			SetState(hChildItem,nState);
			bool bState = false;
			//�����ӽڵ���ֵܽڵ�����ӽڵ�
			hBrotherItem=GetNextSiblingItem(hChildItem);
			while (hBrotherItem)
			{
				UINT nState1;
				//�ٵݹ鴦���ӽڵ���ֵܽڵ���ӽڵ���ֵܽڵ�
				nState1 = ResetItem(hBrotherItem);
				//���趨��ǰ�ڵ�״̬
				SetState(hBrotherItem, nState1);
				//�ֵܽڵ�״̬��ͬ��ǿ����Ϊ2		
				if(nState1 != nState)return 3;
				bState = true;
				hBrotherItem=GetNextSiblingItem(hBrotherItem);
			}
			if(bState)
			{
				//�ֵܽڵ�״̬��ͬ������ǰ�ڵ�״̬
				UINT nParentState = GetState(hChildItem);
				return nParentState;
			}
			else
			{
				//���ֵܽڵ㣬����ǰ�ڵ�״̬
				return nState;
			}
		}
		//���ص�ǰ�ڵ�״̬
		return GetState(hItem);
	}
	void TravelChild(HTREEITEM hItem, int nState)
	{
		HTREEITEM hChildItem,hBrotherItem;

		//�����ӽڵ㣬û�оͽ���
		hChildItem=GetChildItem(hItem);
		if(hChildItem!=NULL)
		{
			//�����ӽڵ��״̬�뵱ǰ�ڵ��״̬һ��
			SetState( hChildItem, nState );
			//�ٵݹ鴦���ӽڵ���ӽڵ���ֵܽڵ�
			TravelChild(hChildItem, nState);

			//�����ӽڵ���ֵܽڵ�����ӽڵ�
			hBrotherItem=GetNextSiblingItem(hChildItem);
			while (hBrotherItem)
			{
				//�����ӽڵ���ֵܽڵ�״̬�뵱ǰ�ڵ��״̬һ��
				SetState( hBrotherItem, nState );
				//�ٵݹ鴦���ӽڵ���ֵܽڵ���ӽڵ���ֵܽڵ�
				TravelChild(hBrotherItem, nState);
				hBrotherItem=GetNextSiblingItem(hBrotherItem);
			}
		}
	}
	bool IsAllSelect()
	{
		HTREEITEM hBrotherItem;

		if(!GetCheckState(GetRootItem()))return false;
		hBrotherItem=GetNextSiblingItem(GetRootItem());
		while (hBrotherItem)
		{
			if(!GetCheckState(hBrotherItem))return false;
			hBrotherItem=GetNextSiblingItem(hBrotherItem);
		}
		return true;
	}
	bool IsAllNoSelect()
	{
		HTREEITEM hBrotherItem;

		if(CHECK_STATE_CHECKED == (GetItemState(GetRootItem(), TVIS_STATEIMAGEMASK) >> 12))return false;
		if(CHECK_STATE_MIXED == (GetItemState(GetRootItem(), TVIS_STATEIMAGEMASK) >> 12))return false;
		hBrotherItem=GetNextSiblingItem(GetRootItem());
		while (hBrotherItem)
		{
			if(CHECK_STATE_CHECKED == (GetItemState(hBrotherItem, TVIS_STATEIMAGEMASK) >> 12))return false;
			if(CHECK_STATE_MIXED == (GetItemState(hBrotherItem, TVIS_STATEIMAGEMASK) >> 12))return false;
			hBrotherItem=GetNextSiblingItem(hBrotherItem);
		}
		return true;
	}
	void DeleteChild(HTREEITEM hItem)
	{
		HTREEITEM hChildItem,hBrotherItem, hBuffItem;

		//�����ӽڵ㣬û�оͽ���
		hChildItem=GetChildItem(hItem);
		if(hChildItem!=NULL)
		{
			//�ٵݹ鴦���ӽڵ���ӽڵ���ֵܽڵ�
			DeleteChild(hChildItem);

			//�����ӽڵ���ֵܽڵ�����ӽڵ�
			hBrotherItem=GetNextSiblingItem(hChildItem);
			while (hBrotherItem)
			{
				//�ٵݹ鴦���ӽڵ���ֵܽڵ���ӽڵ���ֵܽڵ�
				DeleteChild(hBrotherItem);
				hBuffItem = hBrotherItem;
				hBrotherItem=GetNextSiblingItem(hBrotherItem);
				DeleteItem(hBuffItem);
			}
			DeleteItem(hChildItem);
		}
	}

	BOOL HasCheckedItem()
	{
		HTREEITEM hItem = GetChildItem(TVI_ROOT);

		while (NULL != hItem)
		{
			switch (GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12)
			{
			case CHECK_STATE_UNCHECKED:
				break;

			case CHECK_STATE_CHECKED:
			case CHECK_STATE_MIXED:
				return TRUE;

			case CHECK_STATE_NONE:
				hItem = GetChildItem(hItem);
				continue;
			}

			HTREEITEM hNextItem = GetNextSiblingItem(hItem);
			if (NULL == hNextItem)
			{
				HTREEITEM hParentItem = hItem;

				do 
				{
					hParentItem = GetParentItem(hParentItem);
					if (NULL == hParentItem)
						break;

					hNextItem = GetNextSiblingItem(hParentItem);

				} while (NULL == hNextItem);
			}

			hItem = hNextItem;
		}

		return FALSE;
	}



    void Init3State(const std::string& strImageID ,LPCTSTR lpIconPath, CAtlMap<CString,CString>& mapIDvsBitName)
	{
		m_strImageID = strImageID;
		LoadHBitmap(lpIconPath, mapIDvsBitName);
		_Init3State();
	}
	void SetScanState(bool bState)
	{
		m_bScaning = bState;
	}
	void SetDlghWnd(HWND hWnd, BOOL bType)
	{
		m_DlghWnd = hWnd;
		m_bType = bType;
	}
	void SetItemNow(HTREEITEM item)
	{
		m_hCurrentItem = item;
	}
	bool GetScanState()
	{
		return m_bScaning;
	}

	void OnPaint(CDCHandle dc)
	{

		CPaintDC	pdc( m_hWnd );



		DefWindowProc(WM_PAINT, (WPARAM)(void *)pdc, NULL);

// 		HTREEITEM hItem = GetFirstVisibleItem();
// 
// 		int iItemCount = GetVisibleCount() + 1;
// 		while(hItem && iItemCount--)
		{		
// 			if(GetSelectedItem() == hItem)
// 			{
// 				hItem = GetNextVisibleItem(hItem);
// 				continue;
// 			}
			CRect rect;

			// Do not meddle with selected items or drop highlighted items
			UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED;

			if ((GetItemState(m_hCurrentItem, selflag) & selflag) 
				&& ::GetFocus() == m_hWnd)
				;
			else
			{
				// No font specified, so use window font
				HFONT	hOldFont = pdc.SelectFont( GetFont() );

				if ( m_ColorMap.Lookup( m_hCurrentItem ) != NULL )
				{
					pdc.SetTextColor( m_ColorMap[m_hCurrentItem] );
				}
				else
				{
					pdc.SetTextColor( RGB( 0, 0, 0 ) );
				}
				CString sItem;
				GetItemText(m_hCurrentItem, sItem);
				pdc.SetBkMode(TRANSPARENT);
				GetItemRect(m_hCurrentItem, &rect, TRUE);
				rect.left += 2;
				pdc.DrawText(sItem, -1, &rect, DT_VCENTER | DT_LEFT | DT_SINGLELINE );
				
				pdc.SelectFont( hOldFont );
			}
//			hItem = GetNextVisibleItem(m_hCurrentItem);
		}
	}

	void SetTextItemColor( HTREEITEM hItem, COLORREF itemColor )
	{
		m_ColorMap[hItem] = itemColor;
	}

	void LoadHBitmap(LPCTSTR lpIconPath, CAtlMap<CString,CString>& mapIDvsBitName)//ID��·��
	{
        KAppRes& appRes = KAppRes::Instance();

		//Ĭ��ͼ��
		m_img.Create(16,16,ILC_COLOR24,9,0); 
		HBITMAP hBmpCheck	= appRes.GetImage(m_strImageID);
		m_img.Add(hBmpCheck,RGB(0,0,0)); 

		//�Զ���ͼ��
		POSITION posi;
		posi = mapIDvsBitName.GetStartPosition();
		int k=0;
		while (posi!=NULL)
		{
			CString strPath;
			strPath.Format(L"%s\\%s", lpIconPath, mapIDvsBitName.GetValueAt(posi));

			if(PathFileExists(strPath)&&mapIDvsBitName.GetValueAt(posi).GetLength()>0)
			{
				HBITMAP hbitmap;
				hbitmap=(HBITMAP)LoadImage(NULL,strPath,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
				m_img.Add(hbitmap,RGB(0,0,0)); 
				m_HBitmap.SetAt(mapIDvsBitName.GetKeyAt(posi), k);
				k++;
			}
			else
			{
				m_HBitmap.SetAt(mapIDvsBitName.GetKeyAt(posi), 0);
			}
			mapIDvsBitName.GetNext(posi);
		}
	}
	int SelectBit(CString strSoftId)
	{
		if(m_HBitmap.Lookup(strSoftId)!=NULL)
		{
			return m_HBitmap.Lookup(strSoftId)->m_value;
		}
		else
		{
			return 0;
		}
	}
public:

	CWH3StateCheckImageList m_wnd3StateCheckImgList;
	CImageList m_img;
    std::string m_strImageID;
	bool m_bScaning;
	HWND m_DlghWnd;
	HTREEITEM m_hCurrentItem;
	BOOL m_bType;
	CAtlMap<HTREEITEM, COLORREF>	m_ColorMap;
	CAtlMap<CString, int>		m_HBitmap;

	void _Init3State()
	{
        KAppRes& appRes = KAppRes::Instance();

		m_wnd3StateCheckImgList.Create();
		if(!m_strImageID.empty())
		{
			if(m_HBitmap.GetCount()==0)
			{
				m_img.Create(16,16,ILC_COLOR24,9,0); 
				HBITMAP hBmpCheck	= appRes.GetImage(m_strImageID);
				m_img.Add(hBmpCheck,RGB(0,0,0)); 
			}
			SetImageList(m_img, TVSIL_NORMAL);
		}
		SetImageList(m_wnd3StateCheckImgList, TVSIL_STATE);
		m_bScaning = false;
		m_DlghWnd = NULL;
		m_hCurrentItem = NULL;
		m_bType = -1;
	}

	void _CheckSelfAndAllChilds(HTREEITEM hItem, BOOL bCheck)
	{
		SetCheckState(hItem, bCheck);

		HTREEITEM hItemChild = GetChildItem(hItem);
		while (NULL != hItemChild)
		{
			_CheckSelfAndAllChilds(hItemChild, bCheck);

			hItemChild = GetNextSiblingItem(hItemChild);
		}
	}

	void _ResetParentState(HTREEITEM hItem)
	{
		HTREEITEM hItemParent = GetParentItem(hItem);

		if (NULL == hItemParent)
			return;

		UINT uCheck = (GetItemState(hItemParent, TVIS_STATEIMAGEMASK) >> 12);

		if (CHECK_STATE_NONE == uCheck)
			return;

		HTREEITEM hItemParentChild = GetChildItem(hItemParent);

		BOOL bHasCheck = FALSE, bHasUncheck = FALSE;

		while (NULL != hItemParentChild)
		{
			uCheck = (GetItemState(hItemParentChild, TVIS_STATEIMAGEMASK) >> 12);

			bHasCheck |= CHECK_STATE_CHECKED == uCheck || CHECK_STATE_MIXED == uCheck;
			bHasUncheck |= CHECK_STATE_UNCHECKED == uCheck || CHECK_STATE_MIXED == uCheck;

			hItemParentChild = GetNextSiblingItem(hItemParentChild);
		}

		if (bHasCheck)
		{
			if (bHasUncheck)
			{
				uCheck = CHECK_STATE_MIXED;
			}         
			else
			{
				uCheck = CHECK_STATE_CHECKED;
			}

		}
		else
		{
			if (bHasUncheck)
				uCheck = CHECK_STATE_UNCHECKED;
			else
				uCheck = CHECK_STATE_NONE;
		}

		SetItemState(hItemParent, INDEXTOSTATEIMAGEMASK(uCheck), TVIS_STATEIMAGEMASK);

		_ResetParentState(hItemParent);
	}

	void _ToggleItem(HTREEITEM hItem)
	{
		UINT uState = GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12;

		if (CHECK_STATE_NONE == uState)
			return;

		SetRedraw(FALSE);

		BOOL bCheck = !(CHECK_STATE_CHECKED == uState);

		_CheckSelfAndAllChilds(hItem, bCheck);
		_ResetParentState(hItem);

		SetRedraw(TRUE);

		NMHDR nms;
		nms.code = WH3STVN_ITEMCHECKCHANGE;
		nms.hwndFrom = m_hWnd;
		nms.idFrom = GetDlgCtrlID();

		LRESULT lRet = ::SendMessage(GetParent(), WM_NOTIFY, (LPARAM)nms.idFrom, (WPARAM)&nms);
	}

	void OnLButtonDown(UINT nFlags, CPoint point)
	{
		TVHITTESTINFO htinfo;

		ZeroMemory(&htinfo, sizeof(htinfo));

		htinfo.pt = point;

		HitTest(&htinfo);

		if (NULL == htinfo.hItem || TVHT_ONITEMSTATEICON != htinfo.flags)
		{
			SetMsgHandled(FALSE);
			return;
		}
		if(m_bScaning)return;
		_ToggleItem(htinfo.hItem);

	    if(m_DlghWnd)
            ::SendMessage(m_DlghWnd, MSG_CLR_HENJI_TREELUP, (LPARAM)htinfo.hItem, (WPARAM)0);
        if(m_DlghWnd)
            ::SendMessage(m_DlghWnd, MSG_CLR_CONFIG_TREELUP, (LPARAM)htinfo.hItem, (WPARAM)0);
        
	}

	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (VK_SPACE != nChar)
		{
			SetMsgHandled(FALSE);
			return;
		}
		
		HTREEITEM hItem = GetSelectedItem();
		if (NULL == hItem)
		{
			SetMsgHandled(FALSE);
			return;
		}
		if(m_bScaning)return;
		_ToggleItem(hItem);

        if(m_DlghWnd)
            ::SendMessage(m_DlghWnd, MSG_CLR_HENJI_TREELUP, (LPARAM)hItem, (WPARAM)0);
        if(m_DlghWnd)
            ::SendMessage(m_DlghWnd, MSG_CLR_CONFIG_TREELUP, (LPARAM)hItem, (WPARAM)0);
	}

public:

	BEGIN_MSG_MAP_EX(CKuiFolderBrowseCtrl)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONDBLCLK(OnLButtonDown)
		MSG_WM_KEYDOWN(OnKeyDown)
		MSG_WM_PAINT( OnPaint )
	END_MSG_MAP()
};