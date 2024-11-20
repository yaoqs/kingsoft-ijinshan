///////////////////////////////////////////////////////////////
//
//	Filename: 	KTraversableTreeCtrl.h
//	Creator:	lichenglin  <lichenglin@kingsoft.net>
//	Date:		2007-12-5  19:23
//	Comment:	֧�ֶ����ؼ����е�������.
//              ��ҪTTreeCtrlʵ��GetRootItem��GetNextItem����
//              WTL��MFC�е����ؼ�������֧��
//
///////////////////////////////////////////////////////////////

#ifndef _KTraversableTreeCtrl_h_
#define _KTraversableTreeCtrl_h_


template <class TTreeCtrl>
class KUITraversableTreeCtrl : public TTreeCtrl
{
public:
	HTREEITEM TravGetFirstItem()
	{
		TTreeCtrl* pT = static_cast<TTreeCtrl*>(this);
		return pT->GetRootItem();
	}


	HTREEITEM TravGetNextItem( HTREEITEM hItem )
	{
		TTreeCtrl* pT = static_cast<TTreeCtrl*>(this);

		HTREEITEM hNextItem = NULL;

		//--------------------------------------
		// ������ӽ�� �򷵻ص�һ���ӽ��
		hNextItem = pT->GetNextItem( hItem, TVGN_CHILD );
		if( hNextItem != NULL )
			return hNextItem;

		//--------------------------------------
		// ����, ������ֵܽ��, �򷵻���һ���ֵܽ��
		hNextItem = pT->GetNextItem( hItem, TVGN_NEXT );
		if( hNextItem != NULL )
			return hNextItem;

		//--------------------------------------
		// ����, �������Ƚ�����һ���ֵܽ��.
		while( (hItem = pT->GetNextItem( hItem, TVGN_PARENT )) != NULL )
		{
			hNextItem = pT->GetNextItem( hItem, TVGN_NEXT );
			if( hNextItem != NULL )
				break;
		}

		return hNextItem;
	}
};



#endif // _KTraversableTreeCtrl_h_