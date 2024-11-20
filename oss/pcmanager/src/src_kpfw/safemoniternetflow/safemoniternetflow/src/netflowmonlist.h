////////////////////////////////////////////////////////////////////////////////
//
//      Comment   : ����������ضԻ�����list�ؼ���������
//
//      Create at : 2010-08-25
//      Create by : �ֽ�
//
//////////////////////////////////////////////////////////////////////////////
// �����б�
#pragma  once
#include "treelistctrlex.h"
#include <vector>
#include "common/netfluxdef.h"
using namespace std;


class KNetFlowMonListItemData;

class KNetFlowMonList
{
private:
    vector<KNetFlowMonListItemData*>		m_ItemsVector;
    CTreeListCtrlEx&					m_listCtrl;

public:
	KNetFlowMonList(CTreeListCtrlEx& listCtrl);
    ~KNetFlowMonList();

    HRESULT UpdateNetFlow(vector<KProcFluxItem>* pFlowInfo, bool& bIsModified);

private:
	KNetFlowMonListItemData* FindMatch(
        vector<KNetFlowMonListItemData*>& items,
        KNetFlowMonListItemData* pItem);

    void Clear();
};