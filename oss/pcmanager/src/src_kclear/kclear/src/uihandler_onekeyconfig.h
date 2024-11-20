#pragma once

#include <wtlhelper/whwindow.h>
#include "kuires.h"
#include "image3tabtree.h"
#include <vector>
#include "uihandler_onekey.h"
#include <algorithm>
#include "kscbase/kscsys.h"

class CKscOneKeyConfig
	: public CKuiDialogImpl<CKscOneKeyConfig>
	, public CWHRoundRectFrameHelper<CKscOneKeyConfig>
{
public:
	CKscOneKeyConfig(CKscMainDlg* refDialog, BOOL bSetting)
		: CKuiDialogImpl<CKscOneKeyConfig>("IDR_DLG_FOLDER_BROWSE"),
        m_dlg(refDialog)
	{
        Is_SelALL = FALSE;
		m_bSetting = bSetting;
	}

	~CKscOneKeyConfig(void){}

    std::vector<CString> m_defaultvec;
    std::vector<CString> m_customvec;

protected:
	 CKscMainDlg*        m_dlg;
     CSimpleArray<ClearTreeType>		m_arrClearType;
     CSimpleArray<ClearTreeType>		m_arrClearType2;
     CSimpleArray<ClearTreeInfo>		m_arrClearInfo;
     CAtlMap<CString, TreeInfo>		    m_TreeHenjiMap;
     CWH3StateCheckTreeCtrl10 m_Tree;
     BOOL Is_SelALL;
	 std::wstring m_strMakeSure;
	 BOOL m_bSetting;

     void initTreeContent();
     static BOOL WINAPI SoftTreeCallBack(void* pThis,ClearTreeInfo treeinfo);
     static BOOL WINAPI SoftInfoCallBack(void* pThis,SoftInfo softinfo);
    
public:

	
	void OnBkBtnClose()
	{
		EndDialog(0);
	}

    void SplitString(CString str, WCHAR split, std::vector <CString>& vcResult)
    {
        int iPos = 0; //�ָ��λ��
        int iNums = 0; //�ָ��������
        CString strTemp = str;
        CString strRight;
        //�ȼ������ַ���������

        CString strLeft;
        while (true)
        {
            iPos = strTemp.Find(split);
            if(iPos == -1)
                break;
            //���Ӵ�
            strLeft = strTemp.Left(iPos);
            //���Ӵ�
            strRight = strTemp.Mid(iPos + 1, strTemp.GetLength());
            strTemp = strRight;
            vcResult.push_back(strLeft);
        }
    }

    void OnMakeSure()
    {
		if (this->GetItemCheck(ID_IMG_ONEKEY_CONFIG_SELALL))
		{
			this->SetItemCheck(ID_IMG_ONEKEY_CONFIG_SELALL, TRUE);
// 			COneCleanSetting& setting = COneCleanSetting::Instance();
// 			setting.Set("makesure", L"yes");
		}
		else
		{
			this->SetItemCheck(ID_IMG_ONEKEY_CONFIG_SELALL, FALSE);
// 			COneCleanSetting& setting = COneCleanSetting::Instance();
// 			setting.Set("makesure", L"no");
		}

    }

    BOOL OnInitDialog(HWND wParam, LPARAM lParam)
    {
        m_dlg->SetItemVisible(ID_IMG_ONEKEY_CONFIG_GREENTIP, TRUE);
        m_Tree.Create(this->GetViewHWND(), NULL, NULL, WS_TABSTOP | WS_CHILD | TVS_CHECKBOXES | TVS_HASLINES | TVS_HASBUTTONS | TVS_FULLROWSELECT | TVS_LINESATROOT | TVS_DISABLEDRAGDROP | TVS_SHOWSELALWAYS, 
            0, IDC_TREE_CLR_GAOJI, NULL );
        m_Tree.SetFont(KuiFontPool::GetFont(FALSE, FALSE, FALSE));
		COneCleanSetting& setting = COneCleanSetting::Instance();
		setting.Get("makesure", m_strMakeSure);
		if (m_strMakeSure.compare(L"yes") == 0)
		{
			this->SetItemCheck(ID_IMG_ONEKEY_CONFIG_SELALL, TRUE);
		}
		else
		{
			this->SetItemCheck(ID_IMG_ONEKEY_CONFIG_SELALL, FALSE);
		}
        

        initTreeContent();
		if (m_bSetting)
		{
			this->SetItemText(ID_IMG_ONEKEY_CONFIG_OK, L"ȷ�ϲ���ʼ����");
		}
		else
		{
			this->SetItemText(ID_IMG_ONEKEY_CONFIG_OK, L"��������Χ");
		}

        CString strMoudlePath;
        wchar_t szAppPath[MAX_PATH] = { 0 };


        GetModuleFileNameW(NULL, szAppPath, MAX_PATH);
        PathRemoveFileSpecW(szAppPath);
        strMoudlePath = szAppPath;
        strMoudlePath += L"\\";

        strMoudlePath +=L"data\\icon";
        DWORD dwsize = 0;
        //����ͼ��
        CAtlMap<CString,CString> mapIDvsBitName;
        for (int i=0;i<m_arrClearType.GetSize();i++)
        {
            ClearTreeType treetype = m_arrClearType[i];
            CString strUrl = treetype.strBmpurl;
            int n = strUrl.ReverseFind('/');
            if(n>0)strUrl.Delete(0, n+1);
            else strUrl = L"";
            mapIDvsBitName.SetAt(treetype.strTypeid, strUrl);

            for(int i = 0;i<m_arrClearType2.GetSize();i++)
            {
                ClearTreeType treetype2 = m_arrClearType2[i];
                if(treetype2.nSn = treetype.nSn)
                {
                    CString strUrl = treetype2.strBmpurl;
                    int n = strUrl.ReverseFind('/');
                    if(n>0)strUrl.Delete(0, n+1);
                    else strUrl = L"";
                    mapIDvsBitName.SetAt(treetype2.strTypeid, strUrl);

                    if(treetype2.nSn == 2)
                    {
                        for (int i=0;i<m_arrClearInfo.GetSize();i++)
                        {
                            ClearTreeInfo treeInfo = m_arrClearInfo[i];

                            if(treeInfo.strTypeid == treetype2.strTypeid)
                            {

                                strUrl = treeInfo.strBmpurl;
                                n = strUrl.ReverseFind('/');
                                if(n>0)strUrl.Delete(0, n+1);
                                else strUrl = L"";
                                mapIDvsBitName.SetAt(treeInfo.strClearid, strUrl);
                            }
                        }
                    }

                }

            }    

        }

        m_Tree.Init3State("IDB_CLR_TREE_ICON",strMoudlePath, mapIDvsBitName);
        m_Tree.SetDlghWnd(this->m_hWnd,3);

        for (int i=0;i<m_arrClearType.GetSize();i++)
        {
            ClearTreeType treetype = m_arrClearType[i];


            TVINSERTSTRUCT tvInsert;
            tvInsert.hParent = NULL;
            tvInsert.hInsertAfter = NULL;
            tvInsert.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
            tvInsert.item.pszText = treetype.strTypeName.GetBuffer(treetype.strTypeName.GetLength());;
            tvInsert.item.hItem=NULL;
            tvInsert.item.state=INDEXTOSTATEIMAGEMASK(2);
            tvInsert.item.stateMask=TVIS_STATEIMAGEMASK;
            tvInsert.item.iImage=m_Tree.SelectBit(treetype.strTypeid);
            tvInsert.item.iSelectedImage=tvInsert.item.iImage;
            tvInsert.item.cChildren=0;
            tvInsert.item.lParam=0;
            HTREEITEM hCurrent = m_Tree.InsertItem( &tvInsert );


            for(int i=0;i<m_arrClearType2.GetSize();i++)
            {

                ClearTreeType treetype2 = m_arrClearType2[i];

                if(treetype2.nSn == treetype.nSn)
                {

                    tvInsert.hParent=hCurrent;
                    tvInsert.item.iImage=0;
                    tvInsert.item.pszText=treetype2.strTypeName.GetBuffer(treetype2.strTypeName.GetLength());
                    if(treetype2.nSn == 1 || treetype2.nSn == 3)
                    {
                        if(std::find(m_customvec.begin(),m_customvec.end(),treetype2.strTypeid)!=m_customvec.end())
                        {
                            treetype2.nCheck = 1;
                        }
                        else
                        {
                            treetype2.nCheck = 0;
                        }
                        tvInsert.item.state=INDEXTOSTATEIMAGEMASK(treetype2.nCheck+1);
                    }
                   
                    tvInsert.item.iImage=m_Tree.SelectBit(treetype2.strTypeid);
                    tvInsert.item.iSelectedImage=tvInsert.item.iImage;
                    HTREEITEM hSub2 = m_Tree.InsertItem(&tvInsert);

                    if (treetype2.nSn == 1 || treetype2.nSn == 3)
                    {

                        TreeInfo treeinfo;
                        treeinfo.hItem = hSub2;
                        treeinfo.iCheck = treetype2.nCheck+1;
                        treeinfo.strItemInfo = treetype2.strTypeName;
                        treeinfo.nSn = treetype2.nSn;
                        treeinfo.nType = 0;
                        m_TreeHenjiMap.SetAt(treetype2.strTypeid, treeinfo);

                    }

                    if(treetype.nSn == 2)
                    {
                        for (int i=0;i<m_arrClearInfo.GetSize();i++)
                        {
                            ClearTreeInfo treeInfo = m_arrClearInfo[i];

                            if(treeInfo.strTypeid == treetype2.strTypeid)
                            {

                                tvInsert.hParent=hSub2;
                                tvInsert.item.iImage=0;
                                tvInsert.item.pszText=treeInfo.strClearName.GetBuffer(treeInfo.strClearName.GetLength());

                                if(std::find(m_customvec.begin(),m_customvec.end(),treeInfo.strClearid)!=m_customvec.end())
                                {
                                    treeInfo.nCheck = 1;
                                }
                                else
                                {
                                    treeInfo.nCheck = 0;
                                }

                                tvInsert.item.state=INDEXTOSTATEIMAGEMASK(treeInfo.nCheck+1);//
                                tvInsert.item.iImage=m_Tree.SelectBit(treeInfo.strClearid);
                                tvInsert.item.iSelectedImage=tvInsert.item.iImage;
                                HTREEITEM hSub = m_Tree.InsertItem(&tvInsert);

                                m_Tree._ResetParentState(hSub);

                                TreeInfo treeinfo;
                                treeinfo.hItem = hSub;
                                treeinfo.iCheck = treeInfo.nCheck+1;
                                treeinfo.strItemInfo = treeInfo.strClearName;
                                treeinfo.nSn = treeInfo.nSn;
                                treeinfo.nType = 0;//atoi(CW2A(treeInfo.strTypeid));
                                m_TreeHenjiMap.SetAt(treeInfo.strClearid, treeinfo);

                            }
                        }
                    }
                }
            }
        }

        HTREEITEM hRoot = m_Tree.GetRootItem();
        m_Tree.Expand( hRoot);
        HTREEITEM hCurrent = m_Tree.GetNextItem( hRoot, TVGN_CHILD );
        while ( hCurrent != NULL )
        {
            m_Tree.Expand( hCurrent );
            hCurrent = m_Tree.GetNextItem( hCurrent, TVGN_NEXT );
        }

        m_Tree.Select( hRoot, TVGN_FIRSTVISIBLE );
        m_Tree.ResetItemState(hRoot);
        if(m_Tree.IsAllSelect())
        {
           // this->SetItemCheck(ID_IMG_ONEKEY_CONFIG_SELALL, TRUE);
            Is_SelALL = TRUE;
        }
        else 
        {
           // this->SetItemCheck(ID_IMG_ONEKEY_CONFIG_SELALL, FALSE);
            Is_SelALL = FALSE;
        }

        return TRUE;
    }


    LRESULT OnWmLBtn( UINT uMsg, WPARAM wParam, LPARAM lParam )
    {
        
        if(m_Tree.IsAllSelect())
        {
            //this->SetItemCheck(ID_IMG_ONEKEY_CONFIG_SELALL, TRUE);
        }
        else 
        {
            //this->SetItemCheck(ID_IMG_ONEKEY_CONFIG_SELALL, FALSE);
        }

        if(m_Tree.IsAllNoSelect())
        {
            this->EnableItem(ID_IMG_ONEKEY_CONFIG_OK, FALSE);
        }
        else
        {
            this->EnableItem(ID_IMG_ONEKEY_CONFIG_OK, TRUE);
        }
  
        return TRUE;
    }

    void OnBkBtnSave()
    {
        CString strKeyTmp = _T("");
        POSITION pos;
        pos = m_TreeHenjiMap.GetStartPosition();
        while (pos!=NULL)
        {
            CString key = m_TreeHenjiMap.GetKeyAt(pos);
            TreeInfo treeinfo = m_TreeHenjiMap.GetNextValue(pos);
            if(m_Tree.GetCheckStateEx(treeinfo.hItem))
            {
            
                strKeyTmp += key;
                strKeyTmp += L",";
            }
            
        }

		if (this->GetItemCheck(ID_IMG_ONEKEY_CONFIG_SELALL))
		{
			COneCleanSetting& setting = COneCleanSetting::Instance();
			setting.Set("makesure", L"yes");
		}
		else
		{
			COneCleanSetting& setting = COneCleanSetting::Instance();
			setting.Set("makesure", L"no");
		}

        std::wstring m_strCus(strKeyTmp.GetBuffer());

        COneCleanSetting& setting = COneCleanSetting::Instance();

        setting.Set("custom_entrys", m_strCus);
		if (m_bSetting)
		{
			EndDialog(1);
		}
		else
		{
			EndDialog(0);
		}

    }

    void OnSetRecommand()
    {

        POSITION pos;
        pos = m_TreeHenjiMap.GetStartPosition();
        while (pos!=NULL)
        {
            CString key = m_TreeHenjiMap.GetKeyAt(pos);
            TreeInfo treeinfo = m_TreeHenjiMap.GetNextValue(pos);
            if(std::find(m_defaultvec.begin(),m_defaultvec.end(),key)!=m_defaultvec.end())
            {

                m_TreeHenjiMap[key].iCheck = 2;
                m_Tree.SetState(treeinfo.hItem,2);
                m_Tree._ResetParentState(treeinfo.hItem);
            }
            else
            {
                m_TreeHenjiMap[key].iCheck = 1;
                m_Tree.SetState(treeinfo.hItem,1);
                m_Tree._ResetParentState(treeinfo.hItem);

           
            }

        }
        this->EnableItem(ID_IMG_ONEKEY_CONFIG_OK, TRUE);
      //  this->SetItemCheck(ID_IMG_ONEKEY_CONFIG_SELALL, FALSE);
        Is_SelALL = FALSE;
        
    }




public:
	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
        KUI_NOTIFY_ID_COMMAND(IDC_BTN_SYS_CLOSE, OnBkBtnClose)
        KUI_NOTIFY_ID_COMMAND(ID_IMG_ONEKEY_CONFIG_OK, OnBkBtnSave)
        KUI_NOTIFY_ID_COMMAND(ID_IMG_ONEKEY_CONFIG_CANCEL, OnBkBtnClose)
        KUI_NOTIFY_ID_COMMAND(ID_IMG_ONEKEY_CONFIG_SELALL, OnMakeSure)
        KUI_NOTIFY_ID_COMMAND(ID_IMG_ONEKEY_CONFIG_RECOMMAND, OnSetRecommand)
    KUI_NOTIFY_MAP_END()

		BEGIN_MSG_MAP_EX(CKscOneKeyConfig)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
        MESSAGE_HANDLER_EX(MSG_CLR_CONFIG_TREELUP,OnWmLBtn)
		CHAIN_MSG_MAP(CKuiDialogImpl<CKscOneKeyConfig>)
		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CKscOneKeyConfig>)
		MSG_WM_INITDIALOG(OnInitDialog)
		END_MSG_MAP()
};

typedef BOOL (*pCreateObject)( REFIID , void** );


void CKscOneKeyConfig::initTreeContent()
{
  
    CString strMoudlePath, strClean, strZClean;
    CString	m_ScanLogFile;
    CString m_CacheFile;
    wchar_t szAppPath[MAX_PATH] = { 0 };
    
    //��ʼ����
    m_arrClearType.RemoveAll();
    m_arrClearInfo.RemoveAll();
    ClearTreeType cleartreetype;

    cleartreetype.nSn = 1;
    cleartreetype.strTypeName = _T("ϵͳ����");
    cleartreetype.strTypeid = _T("1");
    cleartreetype.strBmpurl = _T("//laji.bmp");
    m_arrClearType.Add(cleartreetype);

    cleartreetype.nSn = 2;
    cleartreetype.strTypeName = _T("ʹ�úۼ�");
    cleartreetype.strTypeid = _T("2");
    cleartreetype.strBmpurl = _T("//henji.bmp");
    m_arrClearType.Add(cleartreetype);



    ClearTreeType cleartreetype2;

//     cleartreetype2.nSn = 2;
//     cleartreetype2.strTypeName = _T("������ʷ�ۼ�");
//     cleartreetype2.strTypeid = _T("101");
//     cleartreetype2.strBmpurl = _T("//Intenethistory.bmp");
//     m_arrClearType2.Add(cleartreetype2);
// 
//     cleartreetype2.nSn = 2;
//     cleartreetype2.strTypeName = _T("�������ҳ��������");
//     cleartreetype2.strTypeid = _T("103");
//     cleartreetype2.strBmpurl = _T("//password.bmp");
//     m_arrClearType2.Add(cleartreetype2);
// 
//     cleartreetype2.nSn = 2;
//     cleartreetype2.strTypeName = _T("ϵͳ��ʷ��¼");
//     cleartreetype2.strTypeid = _T("104");
//     cleartreetype2.strBmpurl = _T("//syshistory.bmp");
//     m_arrClearType2.Add(cleartreetype2);
// 
//     cleartreetype2.nSn = 2;
//     cleartreetype2.strTypeName = _T("Ӧ�ó�����ʷ��¼");
//     cleartreetype2.strTypeid = _T("105");
//     cleartreetype2.strBmpurl = _T("//application.bmp");
//     m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("Internet Explorer�����ۼ�");
	cleartreetype2.strTypeid = _T("101");
	cleartreetype2.strBmpurl = _T("//IEpassword.bmp");
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("�������������ۼ�");
	cleartreetype2.strTypeid = _T("102");
	cleartreetype2.strBmpurl = _T("//FirefoxMac.bmp");
	m_arrClearType2.Add(cleartreetype2);


	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("�ȸ�����������ۼ�");
	cleartreetype2.strTypeid = _T("103");
	cleartreetype2.strBmpurl = _T("//googleChrome.bmp");
	m_arrClearType2.Add(cleartreetype2);


	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("��������������ۼ�");
	cleartreetype2.strTypeid = _T("104");
	cleartreetype2.strBmpurl = _T("//maxthon.bmp");
	m_arrClearType2.Add(cleartreetype2);


	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("�ѹ�����������ۼ�");
	cleartreetype2.strTypeid = _T("105");
	cleartreetype2.strBmpurl = _T("//sogo.bmp");
	m_arrClearType2.Add(cleartreetype2);


	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("Opera����������ۼ�");
	cleartreetype2.strTypeid = _T("106");
	cleartreetype2.strBmpurl = _T("//opera_.bmp");
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("����֮������������ۼ�");
	cleartreetype2.strTypeid = _T("108");
	cleartreetype2.strBmpurl = _T("//windowofworld.bmp");
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("��������������ۼ�");
	cleartreetype2.strTypeid = _T("109");
	cleartreetype2.strBmpurl = _T("//aboutIE.bmp");
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("����������������ۼ�");
	cleartreetype2.strTypeid = _T("112");
	cleartreetype2.strBmpurl = _T("//toolbar.bmp");
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("Windowsϵͳ��ʷ�ۼ�");
	cleartreetype2.strTypeid = _T("110");
	cleartreetype2.strBmpurl = _T("//sys.bmp");
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("Windowsϵͳ�Դ�����ۼ�");
	cleartreetype2.strTypeid = _T("111");
	cleartreetype2.strBmpurl = _T("//filetype.bmp");
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("�칫���");
	cleartreetype2.strTypeid = _T("115");
	cleartreetype2.strBmpurl = _T("//office.bmp");
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("ý�岥�����");
	cleartreetype2.strTypeid = _T("116");
	cleartreetype2.strBmpurl = _T("//kmplayer.bmp");
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("�������");
	cleartreetype2.strTypeid = _T("117");
	cleartreetype2.strBmpurl = _T("//download.bmp");
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("ѹ����ѹ���");
	cleartreetype2.strTypeid = _T("118");
	cleartreetype2.strBmpurl = _T("//winrar.bmp");
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 2;
	cleartreetype2.strTypeName = _T("�������");
	cleartreetype2.strTypeid = _T("120");
	cleartreetype2.strBmpurl = _T("//application.bmp");
	m_arrClearType2.Add(cleartreetype2);

 
    ClearTreeInfo cleartreeinfo;
    //typeid=101

//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("101");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("1003");
//     cleartreeinfo.nSn = 1;
//     cleartreeinfo.strClearName = _T("IE Cookies");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//cookies.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("101");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("1004");
//     cleartreeinfo.nSn = 2;
//     cleartreeinfo.strClearName = _T("IE��ַ����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//Adressleiste.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("101");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("1005");
//     cleartreeinfo.nSn = 3;
//     cleartreeinfo.strClearName = _T("IE������ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//aboutIE.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("101");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("5002");
//     cleartreeinfo.nSn = 4;
//     cleartreeinfo.strClearName = _T("Firefox�����������ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//FirefoxMac.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("101");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("5001");
//     cleartreeinfo.nSn = 5;
//     cleartreeinfo.strClearName = _T("�ȸ������������ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//googleChrome.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("101");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("5004");
//     cleartreeinfo.nSn = 6;
//     cleartreeinfo.strClearName = _T("��ѶTT�����������ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//tecentTT.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("101");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("5003");
//     cleartreeinfo.nSn = 7;
//     cleartreeinfo.strClearName = _T("���������������ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//maxthon.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("101");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("5005");
//     cleartreeinfo.nSn = 8;
//     cleartreeinfo.strClearName = _T("360�����������ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//360.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("101");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("5006");
//     cleartreeinfo.nSn = 9;
//     cleartreeinfo.strClearName = _T("����֮�������������ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//windowofworld.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("101");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2018");
//     cleartreeinfo.nSn = 10;
//     cleartreeinfo.strClearName = _T("�ȸ蹤����������¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//googlelogo.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("101");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("1001");
//     cleartreeinfo.nSn = 11;
//     cleartreeinfo.strClearName = _T("IE����Ŀ¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//ie.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     //typeid=103
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("103");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("6001");
//     cleartreeinfo.nSn = 1;
//     cleartreeinfo.strClearName = _T("Internet Explorer�Զ�����ı����ݣ���ʱ��Ч��");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//IEform.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("103");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("6002");
//     cleartreeinfo.nSn = 2;
//     cleartreeinfo.strClearName = _T("Internet Explorer�Զ�����������¼����ʱ��Ч��");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//IEpassword.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("103");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("6005");
//     cleartreeinfo.nSn = 3;
//     cleartreeinfo.strClearName = _T("Firefox �Զ�����ı����ݺ�������ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//firefoxform.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("103");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("6006");
//     cleartreeinfo.nSn = 4;
//     cleartreeinfo.strClearName = _T("Firefox �Զ�����������¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//Firefoxpassword.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("103");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("6003");
//     cleartreeinfo.nSn = 5;
//     cleartreeinfo.strClearName = _T("�ȸ� Chrome �Զ�����ı�����");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//googleform.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("103");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("6004");
//     cleartreeinfo.nSn = 6;
//     cleartreeinfo.strClearName = _T("�ȸ� Chrome �Զ�����������¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//googlepassword.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("103");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("6008");
//     cleartreeinfo.nSn = 7;
//     cleartreeinfo.strClearName = _T("����֮������ı����ݺ������¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//windowofworldpassword.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("103");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("6007");
//     cleartreeinfo.nSn = 8;
//     cleartreeinfo.strClearName = _T("360���������ı����ݺ������¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//360password.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
//     
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2001");
//     cleartreeinfo.nSn = 1;
//     cleartreeinfo.strClearName = _T("���жԻ�����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//startmenu.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2002");
//     cleartreeinfo.nSn = 2;
//     cleartreeinfo.strClearName = _T("������еĳ�����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//runhistory.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("2008");
//     cleartreeinfo.nSn =3;
//     cleartreeinfo.strClearName = _T("����򿪵ĳ�����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//newprocess.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2005");
//     cleartreeinfo.nSn = 4;
//     cleartreeinfo.strClearName = _T("���ʹ�õ��ĵ���¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//newdocuments.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2004");
//     cleartreeinfo.nSn = 5;
//     cleartreeinfo.strClearName = _T("����λ�����С��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//position.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
//     
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2014");
//     cleartreeinfo.nSn = 6;
//     cleartreeinfo.strClearName = _T("Windowsϵͳ��־");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//syslog.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 0;
//     cleartreeinfo.strClearid = _T("2009");
//     cleartreeinfo.nSn = 7;
//     cleartreeinfo.strClearName = _T("֪ͨ����ͼ����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//notice.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2007");
//     cleartreeinfo.nSn = 8;
//     cleartreeinfo.strClearName = _T("�ļ���չ����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//extension.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//    
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2031");
//     cleartreeinfo.nSn = 10;
//     cleartreeinfo.strClearName = _T("Windows ������¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//searchfile.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2032");
//     cleartreeinfo.nSn = 11;
//     cleartreeinfo.strClearName = _T("Windows �����ھ�");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//neiborhood.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//    
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2010");
//     cleartreeinfo.nSn = 12;
//     cleartreeinfo.strClearName = _T("����������ӳ����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//reflection-driven.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2011");
//     cleartreeinfo.nSn = 13;
//     cleartreeinfo.strClearName = _T("���Ҽ������ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//serchsys.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2012");
//     cleartreeinfo.nSn = 14;
//     cleartreeinfo.strClearName = _T("�����ļ��˵���ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//searchfile.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2013");
//     cleartreeinfo.nSn = 15;
//     cleartreeinfo.strClearName = _T("���Ҵ�ӡ����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//searchprinter.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2016");
//     cleartreeinfo.nSn = 16;
//     cleartreeinfo.strClearName = _T("ע���༭�����һ�η���λ��");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//regedit.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     //cleartreeinfo.nApp = 0;
//     //cleartreeinfo.strTypeid = _T("104");
//     //cleartreeinfo.nCheck = 0;
//     //cleartreeinfo.strClearid = _T("2017");
//     //cleartreeinfo.nSn = 17;
//     //cleartreeinfo.strClearName = _T("Windows�����ע�����");
//     //cleartreeinfo.strExtName = _T("");
//     //cleartreeinfo.nFileext = 0;
//     //cleartreeinfo.strBmpurl = _T("//browser-regedit.bmp");
//     //m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("104");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("2003");
//     cleartreeinfo.nSn = 18;
//     cleartreeinfo.strClearName = _T("�ļ����뱣����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//openfolder.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9041");
//     cleartreeinfo.nSn = 38;
//     cleartreeinfo.strClearName = _T("PPS ������");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//pps.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9042");
//     cleartreeinfo.nSn = 39;
//     cleartreeinfo.strClearName = _T("PPTV ������");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//PPTV.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9043");
//     cleartreeinfo.nSn = 40;
//     cleartreeinfo.strClearName = _T("QVOD ������");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//Qvod.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9001");
//     cleartreeinfo.nSn = 41;
//     cleartreeinfo.strClearName = _T("Adobe Flash Player��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//adobeflash.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9002");
//     cleartreeinfo.nSn = 42;
//     cleartreeinfo.strClearName = _T("Adobe�Ķ�����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//adobereader.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9003");
//     cleartreeinfo.nSn = 43;
//     cleartreeinfo.strClearName = _T("Windows��ͼ��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//painter.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9004");
//     cleartreeinfo.nSn = 44;
//     cleartreeinfo.strClearName = _T("Windowsд�ְ���ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//writer.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9005");
//     cleartreeinfo.nSn = 45;
//     cleartreeinfo.strClearName = _T("Windowsý�岥������������б�");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//wmp.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
// //     cleartreeinfo.nApp = 0;
// //     cleartreeinfo.strTypeid = _T("105");
// //     cleartreeinfo.nCheck = 1;
// //     cleartreeinfo.strClearid = _T("9006");
// //     cleartreeinfo.nSn = 46;
// //     cleartreeinfo.strClearName = _T("Windows Live Messenger��ʷ��¼");
// //     cleartreeinfo.strExtName = _T("");
// //     cleartreeinfo.nFileext = 0;
// //     cleartreeinfo.strBmpurl = _T("//msn.bmp");
// //     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9007");
//     cleartreeinfo.nSn = 47;
//     cleartreeinfo.strClearName = _T("ACDSee�򿪵�·��");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//acdsee.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9008");
//     cleartreeinfo.nSn = 48;
//     cleartreeinfo.strClearName = _T("����Ӱ��");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//baofeng.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9009");
//     cleartreeinfo.nSn = 49;
//     cleartreeinfo.strClearName = _T("KMPlayer������ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//kmplayer.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9010");
//     cleartreeinfo.nSn = 50;
//     cleartreeinfo.strClearName = _T("�ṷ���ֲ�����ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//kugou.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9011");
//     cleartreeinfo.nSn = 51;
//     cleartreeinfo.strClearName = _T("QQӰ��");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//qqyingyin.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9012");
//     cleartreeinfo.nSn = 52;
//     cleartreeinfo.strClearName = _T("QQLive������ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//qqlive.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9013");
//     cleartreeinfo.nSn = 53;
//     cleartreeinfo.strClearName = _T("RealPlayer/RealOne������");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//realplayer.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9014");
//     cleartreeinfo.nSn = 54;
//     cleartreeinfo.strClearName = _T("Ѹ�׿���������ʷ");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//xunleikk.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9015");
//     cleartreeinfo.nSn = 55;
//     cleartreeinfo.strClearName = _T("Ѹ��������ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//xunlei.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9016");
//     cleartreeinfo.nSn = 56;
//     cleartreeinfo.strClearName = _T("Google �����������¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//googledesktop.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9017");
//     cleartreeinfo.nSn = 57;
//     cleartreeinfo.strClearName = _T("΢�� Office��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//office.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9018");
//     cleartreeinfo.nSn = 58;
//     cleartreeinfo.strClearName = _T("΢�� Word��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//word.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9019");
//     cleartreeinfo.nSn = 59;
//     cleartreeinfo.strClearName = _T("΢�� Excel��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//excel.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9020");
//     cleartreeinfo.nSn = 60;
//     cleartreeinfo.strClearName = _T("΢�� PowerPoint��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//powerpoint.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9021");
//     cleartreeinfo.nSn = 61;
//     cleartreeinfo.strClearName = _T("΢�� Access��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//access.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9022");
//     cleartreeinfo.nSn = 62;
//     cleartreeinfo.strClearName = _T("΢�� FrontPage��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//frontpage.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9023");
//     cleartreeinfo.nSn = 63;
//     cleartreeinfo.strClearName = _T("΢�� SharePoint Designer��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//sharepoint.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//   
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9024");
//     cleartreeinfo.nSn = 64;
//     cleartreeinfo.strClearName = _T("΢�� Publisher��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//publisher.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9025");
//     cleartreeinfo.nSn = 65;
//     cleartreeinfo.strClearName = _T("΢�� Visio��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//visio.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9026");
//     cleartreeinfo.nSn = 66;
//     cleartreeinfo.strClearName = _T("WPS������ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//wpsword.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9027");
//     cleartreeinfo.nSn = 67;
//     cleartreeinfo.strClearName = _T("WPS�����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//wpsexcel.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9028");
//     cleartreeinfo.nSn = 68;
//     cleartreeinfo.strClearName = _T("WPS��ʾ��ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//wpspps.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9029");
//     cleartreeinfo.nSn = 69;
//     cleartreeinfo.strClearName = _T("UltraEdit�༭�����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//ultraedit.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9030");
//     cleartreeinfo.nSn = 70;
//     cleartreeinfo.strClearName = _T("EditPlus�༭�����ʷ��¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//editplus.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9031");
//     cleartreeinfo.nSn = 71;
//     cleartreeinfo.strClearName = _T("WinRAR�ļ��˵��е���ʷ������¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//winrar.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9032");
//     cleartreeinfo.nSn = 72;
//     cleartreeinfo.strClearName = _T("WinZip�ļ��˵��е���ʷ������¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//winzip.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
// 
//     cleartreeinfo.nApp = 0;
//     cleartreeinfo.strTypeid = _T("105");
//     cleartreeinfo.nCheck = 1;
//     cleartreeinfo.strClearid = _T("9033");
//     cleartreeinfo.nSn = 73;
//     cleartreeinfo.strClearName = _T("7ZIP�ļ��˵��е���ʷ������¼");
//     cleartreeinfo.strExtName = _T("");
//     cleartreeinfo.nFileext = 0;
//     cleartreeinfo.strBmpurl = _T("//7zip.bmp");
//     m_arrClearInfo.Add(cleartreeinfo);
		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("101");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("1006");
		cleartreeinfo.nSn = 1;
		cleartreeinfo.strClearName = _T("Internet Explorer ��ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//IEpassword.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("101");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("1004");
		cleartreeinfo.nSn = 2;
		cleartreeinfo.strClearName = _T("Internet Explorer ��ַ����ַ��ʷ");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//IEpassword.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("101");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("1003");
		cleartreeinfo.nSn = 3;
		cleartreeinfo.strClearName = _T("Internet Explorer Cookies��ͬʱ��������/����֮��/��ѶTT/360�������Cookies��");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//IEpassword.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("101");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("1005");
		cleartreeinfo.nSn = 4;
		cleartreeinfo.strClearName = _T("index.dat��¼�������ۼ�");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//IEpassword.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("101");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6001");
		cleartreeinfo.nSn = 5;
		cleartreeinfo.strClearName = _T("Internet Explorer �Զ�����ı���ͬʱ��������/����֮��/��ѶTT/360������ı���");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//IEpassword.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("101");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6002");
		cleartreeinfo.nSn = 6;
		cleartreeinfo.strClearName = _T("Internet Explorer �Զ���������롾ͬʱ��������/����֮��/��ѶTT/360����������롿");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//IEpassword.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		///////////////////////////////////////////////////////////////////////////////////////////
		///��������
		//////////////////////////////////////////////////////////////////////////////////////////
		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("102");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("5002");
		cleartreeinfo.nSn = 1;
		cleartreeinfo.strClearName = _T("Mozilla Firefox ��ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//FirefoxMac.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("102");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6009");
		cleartreeinfo.nSn = 2;
		cleartreeinfo.strClearName = _T("Mozilla Firefox Cookies");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//FirefoxMac.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("102");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6006");
		cleartreeinfo.nSn = 3;
		cleartreeinfo.strClearName = _T("Mozilla Firefox �Զ�����ı���������¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//FirefoxMac.bmp");
		m_arrClearInfo.Add(cleartreeinfo);


		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("102");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6005");
		cleartreeinfo.nSn = 4;
		cleartreeinfo.strClearName = _T("Mozilla Firefox �Զ����������");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//FirefoxMac.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		//////////////////////////////////////////////////////////////////////
		//�ȸ������
		//////////////////////////////////////////////////////////////////////
		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("103");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("5001");
		cleartreeinfo.nSn = 1;
		cleartreeinfo.strClearName = _T("Chrome ��ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//googleChrome.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("103");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6010");
		cleartreeinfo.nSn = 2;
		cleartreeinfo.strClearName = _T("Chrome Cookies");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//googleChrome.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("103");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6004");
		cleartreeinfo.nSn = 5;
		cleartreeinfo.strClearName = _T("Chrome �Զ�����ı�");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//googleChrome.bmp");
		m_arrClearInfo.Add(cleartreeinfo);


		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("103");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6003");
		cleartreeinfo.nSn = 6;
		cleartreeinfo.strClearName = _T("Chrome �Զ����������");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//googleChrome.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		////////////////////////////////////////////////////////////////////////////////////
		//��������������ۼ�
		////////////////////////////////////////////////////////////////////////////////////

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("104");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("5003");
		cleartreeinfo.nSn = 1;
		cleartreeinfo.strClearName = _T("�����������ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//maxthon.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("104");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("1007");
		cleartreeinfo.nSn = 2;
		cleartreeinfo.strClearName = _T("���� Cookies��ͬʱ����IE/����֮��/��ѶTT/360�������Cookies��");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//maxthon.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("104");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6014");
		cleartreeinfo.nSn = 5;
		cleartreeinfo.strClearName = _T("�����Զ�����ı���ͬʱ����IE/����֮��/��ѶTT/360������ı���");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//maxthon.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("104");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6015");
		cleartreeinfo.nSn = 6;
		cleartreeinfo.strClearName = _T("�����Զ���������롾ͬʱ����IE/����֮��/��ѶTT/360����������롿");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//maxthon.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		////////////////////////////////////////////////////////////////////////////////
		//�ѹ�����������ۼ�
		////////////////////////////////////////////////////////////////////////////////
		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("105");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("5008");
		cleartreeinfo.nSn = 6;
		cleartreeinfo.strClearName = _T("�ѹ��������ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//sogo.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("105");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("5009");
		cleartreeinfo.nSn = 7;
		cleartreeinfo.strClearName = _T("�ѹ������Cookies");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//sogo.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("105");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("5010");
		cleartreeinfo.nSn = 8;
		cleartreeinfo.strClearName = _T("�ѹ�������Զ�����ı�");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//sogo.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("105");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("5011");
		cleartreeinfo.nSn = 9;
		cleartreeinfo.strClearName = _T("�ѹ�������Զ����������");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//sogo.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("105");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("5012");
		cleartreeinfo.nSn = 10;
		cleartreeinfo.strClearName = _T("�ѹ����������������ѱ���ı�");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//sogo.bmp");
		m_arrClearInfo.Add(cleartreeinfo);
		////////////////////////////////////////////////////////////////////////////////
		//OPERA�����
		////////////////////////////////////////////////////////////////////////////////

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("106");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("5013");
		cleartreeinfo.nSn = 6;
		cleartreeinfo.strClearName = _T("Opera�������ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//opera_.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("106");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("5014");
		cleartreeinfo.nSn = 7;
		cleartreeinfo.strClearName = _T("Opera�����Cookies");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//opera_.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("106");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("5015");
		cleartreeinfo.nSn = 8;
		cleartreeinfo.strClearName = _T("Opera������Զ����������");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//opera_.bmp");
		m_arrClearInfo.Add(cleartreeinfo);
		////////////////////////////////////////////////////////////////////////////////
		//����֮�������
		////////////////////////////////////////////////////////////////////////////////

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("108");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("5006");
		cleartreeinfo.nSn = 1;
		cleartreeinfo.strClearName = _T("����֮����ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//windowofworld.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("108");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("1008");
		cleartreeinfo.nSn = 2;
		cleartreeinfo.strClearName = _T("����֮��Cookies��ͬʱ����IE/����/��ѶTT/360�������Cookies��");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//windowofworld.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("108");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6013");
		cleartreeinfo.nSn = 5;
		cleartreeinfo.strClearName = _T("����֮���Զ�����ı���ͬʱ����IE/����/��ѶTT/360������ı���");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//windowofworld.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("108");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6012");
		cleartreeinfo.nSn = 6;
		cleartreeinfo.strClearName = _T("����֮���Զ���������롾ͬʱ����IE/����/��ѶTT/360����������롿");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//windowofworld.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		////////////////////////////////////////////////////////////////////////////////
		//���������
		////////////////////////////////////////////////////////////////////////////////

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("109");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("5004");
		cleartreeinfo.nSn = 1;
		cleartreeinfo.strClearName = _T("��ѶTT�������ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//tecentTT.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("109");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6016");
		cleartreeinfo.nSn = 2;
		cleartreeinfo.strClearName = _T("��ѶTT������Զ�����ı������롾ͬʱ����IE/����/����֮��/360������ı������롿");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//tecentTT.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("109");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("5005");
		cleartreeinfo.nSn = 3;
		cleartreeinfo.strClearName = _T("360��ȫ�������ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//360.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("109");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("6007");
		cleartreeinfo.nSn = 4;
		cleartreeinfo.strClearName = _T("360��ȫ������Զ�����ı������롾ͬʱ����IE/����/����֮��/��ѶTT������ı������롿");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//360.bmp");
		m_arrClearInfo.Add(cleartreeinfo);
		//////////////////////////////////////////////////////////////////////////////////
		//Windowsϵͳ��ʷ�ۼ�
		/////////////////////////////////////////////////////////////////////////////////

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2001");
		cleartreeinfo.nSn = 1;
		cleartreeinfo.strClearName = _T("�����С��Ի�����ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//startmenu.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2002");
		cleartreeinfo.nSn = 2;
		cleartreeinfo.strClearName = _T("������г������ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//runhistory.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("2008");
		cleartreeinfo.nSn =3;
		cleartreeinfo.strClearName = _T("�������ʵĳ���Ϳ�ݷ�ʽ��¼����ʼ�˵�������򿪵ĳ����¼Ҳ�ᱻ����������á�");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//newprocess.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2005");
		cleartreeinfo.nSn = 4;
		cleartreeinfo.strClearName = _T("����򿪵��ļ���ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//newdocuments.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("2004");
		cleartreeinfo.nSn = 5;
		cleartreeinfo.strClearName = _T("����λ�����С��ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//position.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("2014");
		cleartreeinfo.nSn = 6;
		cleartreeinfo.strClearName = _T("Windows��־�ļ�");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//syslog.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("2009");
		cleartreeinfo.nSn = 7;
		cleartreeinfo.strClearName = _T("֪ͨ����ͼ����ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//notice.bmp");
		m_arrClearInfo.Add(cleartreeinfo);


		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("2007");
		cleartreeinfo.nSn = 8;
		cleartreeinfo.strClearName = _T("�ļ���չ����ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//extension.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		//cleartreeinfo.nApp = 0;
		//cleartreeinfo.strTypeid = _T("104");
		//cleartreeinfo.nCheck = 0;
		//cleartreeinfo.strClearid = _T("2030");
		//cleartreeinfo.nSn = 9;
		//cleartreeinfo.strClearName = _T("����վ");
		//cleartreeinfo.strExtName = _T("");
		//cleartreeinfo.nFileext = 0;
		//cleartreeinfo.strBmpurl = _T("//recyclebin .bmp");
		//m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2031");
		cleartreeinfo.nSn = 10;
		cleartreeinfo.strClearName = _T("Windows ������¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//searchfile.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2032");
		cleartreeinfo.nSn = 11;
		cleartreeinfo.strClearName = _T("Windows �����ھ�");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//neiborhood.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2010");
		cleartreeinfo.nSn = 12;
		cleartreeinfo.strClearName = _T("����������ӳ����ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//reflection-driven.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2011");
		cleartreeinfo.nSn = 13;
		cleartreeinfo.strClearName = _T("���Ҽ������ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//serchsys.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2012");
		cleartreeinfo.nSn = 14;
		cleartreeinfo.strClearName = _T("�����ļ��˵���ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//searchfile.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2013");
		cleartreeinfo.nSn = 15;
		cleartreeinfo.strClearName = _T("���Ҵ�ӡ����ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//searchprinter.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2016");
		cleartreeinfo.nSn = 16;
		cleartreeinfo.strClearName = _T("ע���༭�����һ�η���λ��");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//regedit.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2003");
		cleartreeinfo.nSn = 18;
		cleartreeinfo.strClearName = _T("�ļ����뱣����ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//openfolder.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2029");
		cleartreeinfo.nSn = 19;
		cleartreeinfo.strClearName = _T("������");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//openfolder.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("2033");
		cleartreeinfo.nSn = 20;
		cleartreeinfo.strClearName = _T("Windows 7 ��ת�б�����������ת�б���ĿҲ�ᱻ����������á�");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//newdocuments.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		/*cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("110");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2036");
		cleartreeinfo.nSn = 21;
		cleartreeinfo.strClearName = _T("����ͼ����");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//suolvtu.bmp");
		m_arrClearInfo.Add(cleartreeinfo);*/

		//////////////////////////////////////////////////////////////////////////////
		//����������������ۼ�
		///////////////////////////////////////////////////////////////////////////////
		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("112");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2018");
		cleartreeinfo.nSn = 1;
		cleartreeinfo.strClearName = _T("�ȸ蹤����������¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//googlelogo.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("112");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2019");
		cleartreeinfo.nSn = 2;
		cleartreeinfo.strClearName = _T("�ٶȹ�����������¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//baidutoolbar.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("112");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("2034");
		cleartreeinfo.nSn = 3;
		cleartreeinfo.strClearName = _T("QQ������������¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//QQtoolbar.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

// 		cleartreeinfo.nApp = 0;
// 		cleartreeinfo.strTypeid = _T("112");
// 		cleartreeinfo.nCheck = 1;
// 		cleartreeinfo.strClearid = _T("2035");
// 		cleartreeinfo.nSn = 4;
// 		cleartreeinfo.strClearName = _T("Windows Live������������¼");
// 		cleartreeinfo.strExtName = _T("");
// 		cleartreeinfo.nFileext = 0;
// 		cleartreeinfo.strBmpurl = _T("//Windows_Live.bmp");
// 		m_arrClearInfo.Add(cleartreeinfo);

		//////////////////////////////////////////////////////////////////////////////
		//�������
		///////////////////////////////////////////////////////////////////////////////
		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("117");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("9037");
		cleartreeinfo.nSn = 1;
		cleartreeinfo.strClearName = _T("Ѹ������");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//xunlei.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("117");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("9038");
		cleartreeinfo.nSn = 3;
		cleartreeinfo.strClearName = _T("FlashGet����");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//Flashget.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("117");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("9039");
		cleartreeinfo.nSn = 4;
		cleartreeinfo.strClearName = _T("BitComet����");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//bitcomet.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("117");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("9051");
		cleartreeinfo.nSn = 5;
		cleartreeinfo.strClearName = _T("Ѹ��7������¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//xunlei7.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("117");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("9044");
		cleartreeinfo.nSn = 41;
		cleartreeinfo.strClearName = _T("QQ ����");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//QQdownload.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		/////////////////////////////////////////////////////////////////////
		///ý�岥�����(116)
		/////////////////////////////////////////////////////////////////////
		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("116");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("9041");
		cleartreeinfo.nSn = 1;
		cleartreeinfo.strClearName = _T("PP Stream������ʷ");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//pps.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("116");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("9042");
		cleartreeinfo.nSn = 2;
		cleartreeinfo.strClearName = _T("PPTV ������");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//PPTV.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 3;
		cleartreeinfo.strTypeid = _T("116");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("9043");
		cleartreeinfo.nSn = 4;
		cleartreeinfo.strClearName = _T("QVOD ������");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//Qvod.bmp");
		m_arrClearInfo.Add(cleartreeinfo);
// 
// 		cleartreeinfo.nApp = 3;
// 		cleartreeinfo.strTypeid = _T("116");
// 		cleartreeinfo.nCheck = 0;
// 		cleartreeinfo.strClearid = _T("9045");
// 		cleartreeinfo.nSn = 5;
// 		cleartreeinfo.strClearName = _T("���в�����ʷ");
// 		cleartreeinfo.strExtName = _T("");
// 		cleartreeinfo.nFileext = 0;
// 		cleartreeinfo.strBmpurl = _T("//fengxing.bmp");
// 		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 3;
		cleartreeinfo.strTypeid = _T("116");
		cleartreeinfo.nCheck = 0;
		cleartreeinfo.strClearid = _T("9046");
		cleartreeinfo.nSn = 6;
		cleartreeinfo.strClearName = _T("����Ӱ��������ʷ");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//sheshou.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

// 		cleartreeinfo.nApp = 3;
// 		cleartreeinfo.strTypeid = _T("116");
// 		cleartreeinfo.nCheck = 0;
// 		cleartreeinfo.strClearid = _T("9047");
// 		cleartreeinfo.nSn = 7;
// 		cleartreeinfo.strClearName = _T("�������ֺв�����ʷ��������ʷ");
// 		cleartreeinfo.strExtName = _T("");
// 		cleartreeinfo.nFileext = 0;
// 		cleartreeinfo.strBmpurl = _T("//kuwo.bmp");
// 		m_arrClearInfo.Add(cleartreeinfo);

		//////////////////////////////////////////////////////////////////////////////
		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("120");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("9048");
		cleartreeinfo.nSn = 10;
		cleartreeinfo.strClearName = _T("���PDF�Ķ�����ʷ��¼");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//fixit.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("120");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("9049");
		cleartreeinfo.nSn = 11;
		cleartreeinfo.strClearName = _T("����������¼��Ϣ");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//aliim.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

		cleartreeinfo.nApp = 0;
		cleartreeinfo.strTypeid = _T("120");
		cleartreeinfo.nCheck = 1;
		cleartreeinfo.strClearid = _T("9050");
		cleartreeinfo.nSn = 12;
		cleartreeinfo.strClearName = _T("Windows Live Messenger");
		cleartreeinfo.strExtName = _T("");
		cleartreeinfo.nFileext = 0;
		cleartreeinfo.strBmpurl = _T("//winlivemsg.bmp");
		m_arrClearInfo.Add(cleartreeinfo);

	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("120");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9002");
	     cleartreeinfo.nSn = 42;
	     cleartreeinfo.strClearName = _T("Adobe�Ķ�����ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//adobereader.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("111");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9003");
	     cleartreeinfo.nSn = 43;
	     cleartreeinfo.strClearName = _T("Windows��ͼ��ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//painter.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("111");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9004");
	     cleartreeinfo.nSn = 44;
	     cleartreeinfo.strClearName = _T("Windowsд�ְ���ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//writer.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("111");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9005");
	     cleartreeinfo.nSn = 45;
	     cleartreeinfo.strClearName = _T("Windowsý�岥������������б�");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//wmp.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("116");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9008");
	     cleartreeinfo.nSn = 48;
	     cleartreeinfo.strClearName = _T("����Ӱ��");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//baofeng.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("116");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9009");
	     cleartreeinfo.nSn = 49;
	     cleartreeinfo.strClearName = _T("KMPlayer������ʷ");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//kmplayer.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("116");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9010");
	     cleartreeinfo.nSn = 50;
	     cleartreeinfo.strClearName = _T("�ṷ���ֲ�����ʷ");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//kugou.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("116");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9011");
	     cleartreeinfo.nSn = 51;
	     cleartreeinfo.strClearName = _T("QQӰ��");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//qqyingyin.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("116");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9012");
	     cleartreeinfo.nSn = 52;
	     cleartreeinfo.strClearName = _T("QQLive������ʷ");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//qqlive.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("116");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9014");
	     cleartreeinfo.nSn = 54;
	     cleartreeinfo.strClearName = _T("Ѹ�׿���������ʷ");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//xunleikk.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("117");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9015");
	     cleartreeinfo.nSn = 55;
	     cleartreeinfo.strClearName = _T("Ѹ��������ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//xunlei.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9017");
	     cleartreeinfo.nSn = 57;
	     cleartreeinfo.strClearName = _T("΢�� Office��ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//office.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9018");
	     cleartreeinfo.nSn = 58;
	     cleartreeinfo.strClearName = _T("΢�� Word��ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//word.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9019");
	     cleartreeinfo.nSn = 59;
	     cleartreeinfo.strClearName = _T("΢�� Excel��ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//excel.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9020");
	     cleartreeinfo.nSn = 60;
	     cleartreeinfo.strClearName = _T("΢�� PowerPoint��ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//powerpoint.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9021");
	     cleartreeinfo.nSn = 61;
	     cleartreeinfo.strClearName = _T("΢�� Access��ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//access.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9022");
	     cleartreeinfo.nSn = 62;
	     cleartreeinfo.strClearName = _T("΢�� FrontPage��ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//frontpage.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9023");
	     cleartreeinfo.nSn = 63;
	     cleartreeinfo.strClearName = _T("΢�� SharePoint Designer��ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//sharepoint.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	   
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9024");
	     cleartreeinfo.nSn = 64;
	     cleartreeinfo.strClearName = _T("΢�� Publisher��ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//publisher.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9025");
	     cleartreeinfo.nSn = 65;
	     cleartreeinfo.strClearName = _T("΢�� Visio��ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//visio.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9026");
	     cleartreeinfo.nSn = 66;
	     cleartreeinfo.strClearName = _T("WPS������ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//wpsword.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9027");
	     cleartreeinfo.nSn = 67;
	     cleartreeinfo.strClearName = _T("WPS�����ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//wpsexcel.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("115");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9028");
	     cleartreeinfo.nSn = 68;
	     cleartreeinfo.strClearName = _T("WPS��ʾ��ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//wpspps.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("120");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9029");
	     cleartreeinfo.nSn = 69;
	     cleartreeinfo.strClearName = _T("UltraEdit�༭�����ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//ultraedit.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("120");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9030");
	     cleartreeinfo.nSn = 70;
	     cleartreeinfo.strClearName = _T("EditPlus�༭�����ʷ��¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//editplus.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("118");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9031");
	     cleartreeinfo.nSn = 71;
	     cleartreeinfo.strClearName = _T("WinRAR�ļ��˵��е���ʷ������¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//winrar.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("118");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9032");
	     cleartreeinfo.nSn = 72;
	     cleartreeinfo.strClearName = _T("WinZip�ļ��˵��е���ʷ������¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//winzip.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);
	 
	     cleartreeinfo.nApp = 0;
	     cleartreeinfo.strTypeid = _T("118");
	     cleartreeinfo.nCheck = 1;
	     cleartreeinfo.strClearid = _T("9033");
	     cleartreeinfo.nSn = 73;
	     cleartreeinfo.strClearName = _T("7ZIP�ļ��˵��е���ʷ������¼");
	     cleartreeinfo.strExtName = _T("");
	     cleartreeinfo.nFileext = 0;
	     cleartreeinfo.strBmpurl = _T("//7zip.bmp");
	     m_arrClearInfo.Add(cleartreeinfo);



    //����
    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("IE(��IE�ں�)�����");
    cleartreetype2.strTypeid = _T("IE_TEMP");
    cleartreetype2.strBmpurl = _T("//ie.bmp");
    cleartreetype2.nCheck = 1;
    m_arrClearType2.Add(cleartreetype2);

    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("�ѹ������(����ģʽ)");
    cleartreetype2.strTypeid = _T("BROWER_SOGO");
    cleartreetype2.strBmpurl = _T("//sogo.bmp");
    cleartreetype2.nCheck = 1;
    m_arrClearType2.Add(cleartreetype2);

    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("����3(����ģʽ)");
    cleartreetype2.strTypeid = _T("BROWER_MATHRON");
    cleartreetype2.strBmpurl = _T("//maxthon.bmp");
    cleartreetype2.nCheck = 1;
    m_arrClearType2.Add(cleartreetype2);

    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("��������(Firefox)");
    cleartreetype2.strTypeid = _T("BROWER_FIREFOX");
    cleartreetype2.strBmpurl = _T("//FirefoxMac.bmp");
    cleartreetype2.nCheck = 1;
    m_arrClearType2.Add(cleartreetype2);

    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("�ȸ������(Chrome)");
    cleartreetype2.strTypeid = _T("BROWER_CHROME");
    cleartreetype2.strBmpurl = _T("//googleChrome.bmp");
    cleartreetype2.nCheck = 1;
    m_arrClearType2.Add(cleartreetype2);

    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("Opera�����");
    cleartreetype2.strTypeid = _T("BROWER_OPERA");
    cleartreetype2.strBmpurl = _T("//opera_.bmp");
    cleartreetype2.nCheck = 1;
    m_arrClearType2.Add(cleartreetype2);

    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("Windows��ʱĿ¼");
    cleartreetype2.strTypeid = _T("WIN_TEMP");
    cleartreetype2.strBmpurl = _T("//sys.bmp");
    cleartreetype2.nCheck = 1;
    m_arrClearType2.Add(cleartreetype2);


	cleartreetype2.nSn = 1;
	cleartreetype2.strTypeName = _T("����վ");
	cleartreetype2.strTypeid = _T("WIN_HUISHOUZHAN");
	cleartreetype2.strBmpurl = _T("//huishouzhan.bmp");
	cleartreetype2.nCheck = 1;
	m_arrClearType2.Add(cleartreetype2);

    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("Windows�Զ����²���");
    cleartreetype2.strTypeid = _T("WIN_UPDATE");
    cleartreetype2.strBmpurl = _T("//update.bmp");
    cleartreetype2.nCheck = 1;
    m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 1;
	cleartreetype2.strTypeName = _T("Windows���󱨸�");
	cleartreetype2.strTypeid = _T("WIN_ERRPORT");
	cleartreetype2.strBmpurl = _T("//errrport.bmp");
	cleartreetype2.nCheck = 1;
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 1;
	cleartreetype2.strTypeName = _T("ϵͳ��־�ļ�");
	cleartreetype2.strTypeid = _T("WIN_LOG");
	cleartreetype2.strBmpurl = _T("//logfile.bmp");
	cleartreetype2.nCheck = 1;
	m_arrClearType2.Add(cleartreetype2);

	cleartreetype2.nSn = 1;
	cleartreetype2.strTypeName = _T("����ͼ����");
	cleartreetype2.strTypeid = _T("WIN_SUOLIETU");
	cleartreetype2.strBmpurl = _T("//suolvtu.bmp");
	cleartreetype2.nCheck = 1;
	m_arrClearType2.Add(cleartreetype2);

    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("Office��װ����");
    cleartreetype2.strTypeid = _T("OFFICE_CACHE");
    cleartreetype2.strBmpurl = _T("//cache.bmp");
    cleartreetype2.nCheck = 1;
    m_arrClearType2.Add(cleartreetype2);

    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("WindowsԤ���ļ�");
    cleartreetype2.strTypeid = _T("WIN_PRE");
    cleartreetype2.strBmpurl = _T("//wread.bmp");
    m_arrClearType2.Add(cleartreetype2);

    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("�����س����ļ�");
    cleartreetype2.strTypeid = _T("WIN_DOWNLOAD");
    cleartreetype2.strBmpurl = _T("//download.bmp");
    m_arrClearType2.Add(cleartreetype2);

    cleartreetype2.nSn = 1;
    cleartreetype2.strTypeName = _T("�û���ʱ�ļ�");
    cleartreetype2.strTypeid = _T("U_TEMP");
    cleartreetype2.strBmpurl = _T("//utemp.bmp");
    cleartreetype2.nCheck = 1;
    m_arrClearType2.Add(cleartreetype2);

    


    //ע���

	if (TRUE)
	{
		cleartreetype.nSn = 3;
		cleartreetype.strTypeName = _T("����ע���");
		cleartreetype.strTypeid = _T("3");
		cleartreetype.strBmpurl = _T("//zhucebiao.bmp");
		m_arrClearType.Add(cleartreetype);

		cleartreetype2.nSn = 3;
		cleartreetype2.strTypeName = _T("�����ڵ�DLL�ļ���¼");
		cleartreetype2.strTypeid = _T("RST_SHAREDDLL");
		cleartreetype2.strBmpurl = _T("//dll.bmp");
		cleartreetype2.nCheck = 1;
		m_arrClearType2.Add(cleartreetype2);

		cleartreetype2.nSn = 3;
		cleartreetype2.strTypeName = _T("�򿪶Ի�����ʷ��¼");
		cleartreetype2.strTypeid = _T("RST_OPENSAVEMRU");
		cleartreetype2.strBmpurl = _T("//openfile.bmp");
		cleartreetype2.nCheck = 1;
		m_arrClearType2.Add(cleartreetype2);

		cleartreetype2.nSn = 3;
		cleartreetype2.strTypeName = _T("�ļ����Ͳ�����¼");
		cleartreetype2.strTypeid = _T("RST_EXTHISTORY");
		cleartreetype2.strBmpurl = _T("//openfile.bmp");
		cleartreetype2.nCheck = 1;
		m_arrClearType2.Add(cleartreetype2);

		cleartreetype2.nSn = 3;
		cleartreetype2.strTypeName = _T("���ڵĿ�ʼ�˵�");
		cleartreetype2.strTypeid = _T("RST_STARTMENU");
		cleartreetype2.strBmpurl = _T("//startmenu.bmp");
		cleartreetype2.nCheck = 1;
		m_arrClearType2.Add(cleartreetype2);

		cleartreetype2.nSn = 3;
		cleartreetype2.strTypeName = _T("ȱʧ��MUI����");
		cleartreetype2.strTypeid = _T("RST_MUICACHE");
		cleartreetype2.strBmpurl = _T("//dlg.bmp");
		m_arrClearType2.Add(cleartreetype2);

		cleartreetype2.nSn = 3;
		cleartreetype2.strTypeName = _T("��Ч�İ����ļ�");
		cleartreetype2.strTypeid = _T("RST_HELP");
		cleartreetype2.strBmpurl = _T("//help.bmp");
		cleartreetype2.nCheck = 1;
		m_arrClearType2.Add(cleartreetype2);

		cleartreetype2.nSn = 3;
		cleartreetype2.strTypeName = _T("��Ч��Ӧ�ó���·��");
		cleartreetype2.strTypeid = _T("RST_APPPATH");
		cleartreetype2.strBmpurl = _T("//application.bmp");
		cleartreetype2.nCheck = 1;
		m_arrClearType2.Add(cleartreetype2);
	}
    

}


BOOL WINAPI CKscOneKeyConfig::SoftInfoCallBack(void* pThis,SoftInfo softinfo)
{
    CUIHandlerOpt *pDlg = (CUIHandlerOpt*) pThis;
    CString str;
    str.Format(L"%s_%s_%s", softinfo.strClearid, softinfo.strTypeid, softinfo.strmethod);

    return TRUE;

}
BOOL WINAPI CKscOneKeyConfig::SoftTreeCallBack(void* pThis,ClearTreeInfo treeinfo)
{
    CKscOneKeyConfig *pDlg = (CKscOneKeyConfig*) pThis;

    CString str;
    str.Format(L"%s_%s_%s", treeinfo.strClearid, treeinfo.strTypeid, treeinfo.strClearName);
    ////OutputDebugStringW(str);
    ClearTreeInfo cleartreeinfo;
    cleartreeinfo.nApp = treeinfo.nApp;
    cleartreeinfo.strTypeid = treeinfo.strTypeid;
    cleartreeinfo.nCheck = treeinfo.nCheck;
    cleartreeinfo.strClearid = treeinfo.strClearid;
    cleartreeinfo.nSn = treeinfo.nSn;
    cleartreeinfo.strClearName = treeinfo.strClearName;
    cleartreeinfo.strExtName = treeinfo.strExtName;
    cleartreeinfo.nFileext = treeinfo.nFileext;
    cleartreeinfo.strBmpurl = treeinfo.strBmpurl;
    cleartreeinfo.strBmpcrc = treeinfo.strBmpcrc;
    pDlg->m_arrClearInfo.Add(cleartreeinfo);

    return TRUE;
}

