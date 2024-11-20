#include "stdafx.h"
#include "kscmain.h"
#include "kscmaindlg.h"
#include "uihandler_opt.h"
#include "kuiwin/kuimsgbox.h"
#include <atltime.h>
#include "kuires/kuifontpool.h"
#include "kscbase/kscfilepath.h"
#include <algorithm>

//////////////////////////////////////////////////////////////////////////

typedef BOOL (*pCreateObject)( REFIID , void** );

int GetDrive(SCANPATH* scanpath)  //����·������ȡֻ������������
{
	int nPos = 0;
	CString strDrive = "?:\\";
	DWORD dwDriveList = ::GetLogicalDrives ();
	CString strTmp;
	int nn=0;
	while (dwDriveList)
	{
		if (dwDriveList & 1)
		{	
			strDrive.SetAt (0, 'A' + nPos);
			///�ж����ƶ�����
			{
				int nDiskType = GetDriveType(strDrive);   
				switch(nDiskType)
				{   
				case  DRIVE_NO_ROOT_DIR:
					break;
				case  DRIVE_REMOVABLE: 
					break;
				case  DRIVE_FIXED: 
					{
						scanpath[nn].iType = 0;
						wcscpy(scanpath[nn].szScanFile ,strDrive);
						nn++;
					}
					break;
				case   DRIVE_REMOTE:
					break;   
				case   DRIVE_CDROM:
					break;
				}
			}
		}
		dwDriveList >>= 1;
		nPos++;
	}
	return nn;
}

void dwzh(DWORD dwsize, CString& strText)
{
	DOUBLE dwFileSize = dwsize;
	DOUBLE dFileSize = dwFileSize/1000/1000;
	CString strDanwei = "MB";
	if(dwsize>0) 
	{
		if(dFileSize<1)
		{
			dFileSize = dwFileSize/1000;
			if(dFileSize<1)
			{
				strDanwei = "B";
				strText.Format(_T("%d%s"), dwsize, strDanwei);
			}
			else
			{
				strDanwei = "KB";
				strText.Format(_T("%0.2f%s"), dwFileSize/1000, strDanwei);
			}
		}
		else
		{
			dFileSize = dwFileSize/1000/1000/1000;
			if(dFileSize<1)
			strText.Format(_T("%0.2f%s"), dwFileSize/1000/1000, strDanwei);
			else
			{
				strDanwei = "GB";
				strText.Format(_T("%0.2f%s"), dwFileSize/1000/1000/1000, strDanwei);
			}
		}
	}
	else
	{
		strDanwei = "B";
		strText.Format(_T("%d%s"), dwsize, strDanwei);
	}
}

BOOL WINAPI CUIHandlerOpt::SoftInfoCallBack(void* pThis,SoftInfo softinfo)
{
	CUIHandlerOpt *pDlg = (CUIHandlerOpt*) pThis;
	if (pDlg == NULL)
	{
		return FALSE;
	}
	CString str;
	str.Format(L"%s_%s_%s", softinfo.strClearid, softinfo.strTypeid, softinfo.strmethod);
	////OutputDebugStringW(str);
// 	ClearTreeInfo cleartreeinfo;
// 	cleartreeinfo.nApp = 0;cleartreeinfo.strTypeid = _T("302");cleartreeinfo.nCheck = 1;cleartreeinfo.strClearid = _T("");cleartreeinfo.nSn = 4;cleartreeinfo.strClearName = _T("�����ע�����Ϣ");cleartreeinfo.strExtName = _T("");cleartreeinfo.nFileext = 0;
// 	m_arrClearInfo.Add(cleartreeinfo);

	return TRUE;

}
BOOL WINAPI CUIHandlerOpt::SoftTreeCallBack(void* pThis,ClearTreeInfo treeinfo)
{
	CUIHandlerOpt *pDlg = (CUIHandlerOpt*) pThis;
	if (pDlg == NULL)
	{
		return FALSE;
	}
	
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
BOOL WINAPI CUIHandlerOpt::myScanFileCallBackError(void* pMainError,int iType,LPCTSTR lpcszFileFullPath,DWORD dwFileLowPart,LONG dwFileHighPart)
{	
	CUIHandlerOpt *pDlg = (CUIHandlerOpt*) pMainError;
	if (pDlg == NULL)
	{
		return FALSE;
	}

	if (pDlg->m_bOneScan)
	{
		if ( pDlg->m_OneMap.IsEmpty() || pDlg->m_OneTypeMap.IsEmpty())
		{
			pDlg->StopCleanEx();
			return TRUE;
		}
	}

	CString str;
	str.Format(L"ʧ�ܵ�ע���%d_%s_%d", iType, lpcszFileFullPath, dwFileLowPart);
	////OutputDebugStringW(str);

	if(iType == CLEAN_COMPATE)
	{
		if(pDlg->m_Tree.GetScanState())
		{
			pDlg->m_nCleanNum--;
			if(pDlg->m_nCleanNum == 0)
			{
				pDlg->m_Tree.SetScanState(false);
				pDlg->GetCheckReg(pDlg->m_TreeHenjiMap,&pDlg->m_Tree,true);
				pDlg->m_Tree.Set2ItemState(pDlg->m_Tree.GetRootItem());
				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2,FALSE);

				for (int i=0; i < pDlg->m_arrScanHenji.GetSize(); i++)
				{
					if(pDlg->m_arrScanHenji[i].nType == 4)
					{
						pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2,TRUE);
						pDlg->m_dlg->SetItemStringAttribute(IDC_TXT_CLR_TREETOP2, "pos",  _T("265,10"));
						::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP3, (LPARAM)_T("0"), (WPARAM)_T("�����ļ�������������ɾ����"));
						break;
					} 
				}


				::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_HENJI_CLEAR_fINISH, (LPARAM)0, (WPARAM)0);
				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP, TRUE);
				::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("2"), (WPARAM)_T("�ۼ���������ɣ�������ÿ����кۼ�����"));

			}
		}
		return TRUE;
	}
	pDlg->m_cs.Lock();	

	int nBegin = TREE_BEGIN(iType);

	if (/*!pDlg->m_TreeHenjiMap.IsEmpty()&&*/pDlg->m_TreeHenjiMap.Lookup(nBegin)!=NULL && pDlg->m_Tree.GetScanState())
	{
		CString str;
		str =pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.strItemInfo;

		str = _T("(��������)")+str;
		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_HENJI_TREE_SHOW_HONG, (LPARAM)nBegin, (WPARAM)str.GetBuffer());
		str.ReleaseBuffer();

		str.Format(_T("��������%s"),pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.strItemInfo);
		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("1"), (WPARAM)str.GetBuffer());
		str.ReleaseBuffer();

		pDlg->m_cs.Unlock();	
		return TRUE;
	}	

	int nEnd = TREE_END(iType);
	if (/*!pDlg->m_TreeHenjiMap.IsEmpty()&&*/pDlg->m_TreeHenjiMap.Lookup(nEnd)!=NULL && pDlg->m_Tree.GetScanState())
	{

		bool bTeshuchuli = false;
		pDlg->m_dwAllFileSize = 0;
		DWORD dwteshuszie = 0;
		DWORD dwReg=0;
		DWORD dwFile=0;
		for (int i=0;i<pDlg->m_arrScanHenji.GetSize();i++)
		{
			if(pDlg->m_arrScanHenji[i].hItem != pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem)continue;


			if(pDlg->m_arrScanHenji[i].iType == 6001 || pDlg->m_arrScanHenji[i].iType == 6002 ||pDlg->m_arrScanHenji[i].iType == 1005 ||
				pDlg->m_arrScanHenji[i].iType == 6007 || pDlg->m_arrScanHenji[i].iType == 6008 ||pDlg->m_arrScanHenji[i].iType == 2029 ||
				pDlg->m_arrScanHenji[i].iType == 2030 ||pDlg->m_arrScanHenji[i].iType == 6011 || pDlg->m_arrScanHenji[i].iType == 6012 ||
				pDlg->m_arrScanHenji[i].iType == 6013 ||pDlg->m_arrScanHenji[i].iType == 6014 || pDlg->m_arrScanHenji[i].iType == 6015 ||
				pDlg->m_arrScanHenji[i].iType == 6016)
			{
				bTeshuchuli = true;
				break;
			}

			if(pDlg->m_arrScanHenji[i].nType == 2)pDlg->m_dwAllFileSize += pDlg->m_arrScanHenji[i].dwFileLowPart;
			if(pDlg->m_arrScanHenji[i].nType == 1)dwReg++;
			else if(pDlg->m_arrScanHenji[i].nType == 2)dwFile++;
			else if(pDlg->m_arrScanHenji[i].nType == 3)dwteshuszie++;
		}
		CString strName, strSize;
		pDlg->m_Tree.GetItemText(pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, strName);
		dwzh(pDlg->m_dwAllFileSize, strSize);
		pDlg->WriteLog(dwFile+dwReg+dwteshuszie, pDlg->m_dwAllFileSize);

		if(dwReg>0)
		{
			if(dwteshuszie>0)
			{
				if(dwFile>0)
					strName.Format(L"%s��%d���ļ�������%d�������%d��ע�����%s��", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo,dwFile, dwteshuszie, dwReg, strSize);
				else
					strName.Format(L"%s������%d�������%d��ע���", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo,dwteshuszie, dwReg);
			}
			else
			{
				if(dwFile>0)
					strName.Format(L"%s��%d���ļ���%d��ע�����%s��", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo,dwFile, dwReg, strSize);
				else
					strName.Format(L"%s��%d��ע���", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo,dwFile, dwReg);
			}
		}
		else
		{
			if(dwteshuszie>0)
			{
				if(dwFile>0)
					strName.Format(L"%s��%d���ļ�������%d���������%s��", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo,dwFile, dwteshuszie, strSize);
				else
					strName.Format(L"%s������%d�������", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo,dwteshuszie);
			}
			else
			{
				if(dwFile>0)
					strName.Format(L"%s��%d���ļ�����%s��", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo,dwFile, strSize);
				else
				{
					if (nEnd == 2009)
					{
						strName.Format(L"%s��������ɣ���������Ч��", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);
					}
					else
					{
						strName.Format(L"%s��������ɣ�", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo,dwFile);
					}
				}
			}
		}

		if(bTeshuchuli)
		{
			strName = pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo;
			if(strName.Find(L"��ʱ��Ч")>0)
			{
				strName.Replace(L"��ʱ��Ч", L"�������");
			}
			else
			{
				if (nEnd == 2009)
				{
					strName.Format(L"%s��������ɣ���������Ч��", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);
				}
				else
				{
					strName.Format(L"%s��������ɣ�", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);
				}
			}
		}
		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_HENJI_TREE_SHOW_HEI, (LPARAM)nEnd, (WPARAM)strName.GetBuffer());
		strName.ReleaseBuffer();

		pDlg->m_cs.Unlock();	
		return TRUE;

	}

	if (/*!pDlg->m_TreeHenjiMap.IsEmpty()&&*/pDlg->m_TreeHenjiMap.Lookup(iType)!=NULL && pDlg->m_Tree.GetScanState())
	{
			CString str;
			str =pDlg->m_TreeHenjiMap.Lookup(iType)->m_value.strItemInfo;
			Treety treety;
			treety.hItem = pDlg->m_TreeHenjiMap.Lookup(iType)->m_value.hItem;
			treety.strReg.Format(_T("%s"), lpcszFileFullPath);
			treety.dwFileLowPart = dwFileLowPart;
			treety.strParent = str;
			treety.iType = iType;

			TVINSERTSTRUCT tvInsert;
			tvInsert.hParent = 	pDlg->m_TreeHenjiMap.Lookup(iType)->m_value.hItem;
			tvInsert.hInsertAfter = NULL;
			tvInsert.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
			tvInsert.item.hItem=NULL;
			tvInsert.item.state=INDEXTOSTATEIMAGEMASK(2);
			tvInsert.item.stateMask=TVIS_STATEIMAGEMASK;
			CString strType;
			strType.Format(L"%d", iType);
			tvInsert.item.iImage=pDlg->m_Tree.SelectBit(strType);
			tvInsert.item.iSelectedImage=tvInsert.item.iImage;
			tvInsert.item.cChildren=0;
			tvInsert.item.lParam=0;
			HTREEITEM SubItem;
			str.Format(_T("�ѱ��Ϊɾ������������Ч����%s"), lpcszFileFullPath);
			tvInsert.item.pszText = (TCHAR*)str.GetBuffer();
			SubItem = pDlg->m_Tree.InsertItem(&tvInsert);
			str.ReleaseBuffer();

			if(/*!pDlg->m_RescanCleanmap.IsEmpty()&&*/pDlg->m_RescanCleanmap.Lookup(lpcszFileFullPath)==NULL)
			{
				pDlg->m_RescanCleanmap.SetAt(lpcszFileFullPath, L"�ѱ��Ϊɾ������������Ч����");
			}
			else
			{
				pDlg->m_cs.Unlock();	
				return TRUE;
			}

			treety.hSubItem = SubItem;
			if(str.Find(L"|")>0)
			{
				treety.nType = 3;
			}
			else
			{
				treety.nType = 4;
			}
			pDlg->m_arrScanHenji.Add(treety);

			pDlg->m_Tree.SortChildren(tvInsert.hParent);
			pDlg->m_cs.Unlock();	
			return TRUE;
	}
	else
	{
		try
		{
			if(/*!pDlg->m_RescanCleanmap.IsEmpty()&&*/pDlg->m_RescanCleanmap.Lookup(lpcszFileFullPath)==NULL)
			{
				pDlg->m_RescanCleanmap.SetAt(lpcszFileFullPath, L"�ѱ��Ϊɾ������������Ч����");
			}
		}
		catch (...)
		{
		}
	}
	pDlg->m_cs.Unlock();	
	return TRUE;
}
BOOL WINAPI CUIHandlerOpt::myScanRegCallBackError(void* pMainError,int iType,LPCTSTR lpcszKeyFullPathError,LPCTSTR lpcszValueNameError)
{	
	CUIHandlerOpt *pDlg = (CUIHandlerOpt*) pMainError;
	CString str;
	str.Format(L"ʧ�ܵ��ļ�·��%d_%s_%s", iType, lpcszKeyFullPathError, lpcszValueNameError);
	////OutputDebugStringW(str);

	if (pDlg == NULL)
	{
		return FALSE;
	}
	if (pDlg->m_bOneScan)
	{
		if ( pDlg->m_OneMap.IsEmpty() || pDlg->m_OneTypeMap.IsEmpty())
		{
			pDlg->StopCleanEx();
			return TRUE;
		}
	}
	if(iType == CLEAN_COMPATE)
	{
		if(pDlg->m_Tree.GetScanState())
		{
			pDlg->m_nCleanNum--;
			CString str1231;
			str1231.Format(L"�ۼ�ע������%d", pDlg->m_nCleanNum);
			////OutputDebugStringW(str1231);

			if(pDlg->m_nCleanNum == 0)
			{
				pDlg->m_Tree.SetScanState(false);
				pDlg->GetCheckReg(pDlg->m_TreeHenjiMap,&pDlg->m_Tree,true);
				pDlg->m_Tree.Set2ItemState(pDlg->m_Tree.GetRootItem());

				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2,FALSE);

				for (int i=0; i < pDlg->m_arrScanHenji.GetSize(); i++)
				{
					if(pDlg->m_arrScanHenji[i].nType == 4)
					{
						pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2,TRUE);
						pDlg->m_dlg->SetItemStringAttribute(IDC_TXT_CLR_TREETOP2, "pos",  _T("265,10"));
						::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP3, (LPARAM)_T("0"), (WPARAM)_T("�����ļ�������������ɾ����"));
						break;
					} 
				}

				::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_HENJI_CLEAR_fINISH, (LPARAM)0, (WPARAM)0);
				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP, TRUE);
				::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("2"), (WPARAM)_T("�ۼ���������ɣ�������ÿ����кۼ�����"));
			}

		}
		return TRUE;

	}
	pDlg->m_cs.Lock();	

	int nBegin = TREE_BEGIN(iType);
    if(pDlg->m_TreeHenjiMap.Lookup(nBegin)!=NULL && pDlg->m_Tree.GetScanState())
	{
		CString str;
		str =pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.strItemInfo;

//		pDlg->m_Tree.Expand(pDlg->m_Tree.GetParentItem(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem));
		str = _T("����������")+str;
// 		pDlg->m_Tree.SetItemNow(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem);
// 		pDlg->m_Tree.SetItemText(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem, str);
// 		pDlg->m_Tree.SetTextItemColor(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem, RGB(255,0,0));
		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_HENJI_TREE_SHOW_HONG, (LPARAM)nBegin, (WPARAM)str.GetBuffer());
		str.ReleaseBuffer();

		str.Format(_T("��������%s"),pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.strItemInfo);
		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("1"), (WPARAM)str.GetBuffer());
		str.ReleaseBuffer();

		pDlg->m_cs.Unlock();	

		return TRUE;
	}	
	int nEnd = TREE_END(iType);
	if(pDlg->m_TreeHenjiMap.Lookup(nEnd)!=NULL && pDlg->m_Tree.GetScanState())
	{
		pDlg->m_dwAllFileSize = 0;

		DWORD dwReg=0;
		DWORD dwFile=0;
		for (int i=0;i<pDlg->m_arrScanHenji.GetSize();i++)
		{
			if(pDlg->m_arrScanHenji[i].hItem != pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem)continue;

			if(pDlg->m_arrScanHenji[i].nType == 2)pDlg->m_dwAllFileSize += pDlg->m_arrScanHenji[i].dwFileLowPart;
			if(pDlg->m_arrScanHenji[i].nType == 1)dwReg++;
			else if(pDlg->m_arrScanHenji[i].nType == 2)dwFile++;
		}
		CString strName, strSize;
		pDlg->m_Tree.GetItemText(pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, strName);
		dwzh(pDlg->m_dwAllFileSize, strSize);
		pDlg->WriteLog(dwReg+dwFile, 0);

		if(dwReg>0)
		{
			if(dwFile>0)
			{
				if(pDlg->m_dwAllFileSize>0)
					strName.Format(L"%s��%d���ļ���%d��ע�����%s��", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo,dwFile, dwReg, strSize);
				else
					strName.Format(L"%s��%d���ļ���%d��ע���", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo,dwFile, dwReg);
			}
			else
			{
				strName.Format(L"%s��%d��ע���",pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo,dwReg);
			}
		}
		else
		{
			if(dwFile>0)
				strName.Format(L"%s��%d���ļ�����%s��", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwFile, strSize);
			else
			{
				strName = pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo;
				if(strName.Find(L"��ʱ��Ч")>0)
				{
					strName.Replace(L"��ʱ��Ч", L"�������");
				}
				else
				{
					if (nEnd == 2009)
					{
						strName.Format(L"%s��������ɣ���������Ч��", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);
					}
					else
					{
						strName.Format(L"%s��������ɣ�", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);
					}
				}
					//strName.Format(L"%s��������ɣ�", pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);
			}
		}
// 		pDlg->m_Tree.SetItemText(pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, strName);
// 		pDlg->m_Tree.SetTextItemColor(pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, RGB(0,0,0));
		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_HENJI_TREE_SHOW_HEI, (LPARAM)nEnd, (WPARAM)strName.GetBuffer());
		strName.ReleaseBuffer();
		pDlg->m_Tree.ResetItemState(pDlg->m_Tree.GetRootItem());
		pDlg->m_cs.Unlock();	
		return TRUE;

	}
    if(pDlg->m_TreeHenjiMap.Lookup(iType)!=NULL && pDlg->m_Tree.GetScanState())
	{
		CString str;
		str =pDlg->m_TreeHenjiMap.Lookup(iType)->m_value.strItemInfo;
		Treety treety;
		treety.hItem = pDlg->m_TreeHenjiMap.Lookup(iType)->m_value.hItem;
		treety.strReg.Format(_T("%s"), lpcszKeyFullPathError);
		treety.strValue.Format(_T("%s"), lpcszValueNameError);
		treety.strParent = str;
		treety.iType = iType;

		str.Format(_T("%s\\%s"), lpcszKeyFullPathError, lpcszValueNameError);

		TVINSERTSTRUCT tvInsert;
		tvInsert.hParent = 	pDlg->m_TreeHenjiMap.Lookup(iType)->m_value.hItem;
		tvInsert.hInsertAfter = NULL;
		tvInsert.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
		tvInsert.item.pszText = (TCHAR*)str.GetBuffer();
		tvInsert.item.hItem=NULL;
		tvInsert.item.state=INDEXTOSTATEIMAGEMASK(2);
		tvInsert.item.stateMask=TVIS_STATEIMAGEMASK;
		CString strType;
		strType.Format(L"%d", iType);
		tvInsert.item.iImage=pDlg->m_Tree.SelectBit(strType);
		tvInsert.item.iSelectedImage=tvInsert.item.iImage;
		tvInsert.item.cChildren=0;
		tvInsert.item.lParam=0;
		HTREEITEM SubItem = pDlg->m_Tree.InsertItem(&tvInsert);
		treety.hSubItem = SubItem;
		treety.nType = 1;
		str.ReleaseBuffer();

		pDlg->m_arrScanHenji.Add(treety);

		pDlg->m_cs.Unlock();	
		return TRUE;

	}

	pDlg->m_cs.Unlock();	

	return TRUE;
}

BOOL WINAPI CUIHandlerOpt::myScanFileCallBack(void* pMain,int iType,LPCTSTR lpcszFileFullPath,DWORD dwFileLowPart,LONG dwFileHighPart)
{	
	CUIHandlerOpt *pDlg = (CUIHandlerOpt*) pMain;

	if (pDlg == NULL)
	{
		return FALSE;
	}
	if (pDlg->m_bOneScan)
	{
		if ( pDlg->m_OneMap.IsEmpty() || pDlg->m_OneTypeMap.IsEmpty())
		{
			pDlg->StopCleanEx();
			return TRUE;
		}
	}

	//if(pDlg->m_bStopScan)
	//{
	//	pDlg->m_cs.Lock();
	//	pDlg->m_dlg->SetItemText(IDC_TXT_CLR_TREETOP, L"");
	//	pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP, FALSE);
	//	CString strBuff;
	//	int nEnd = TREE_END(iType);
	//	if (pDlg->m_TreeHenjiMap.Lookup(nEnd)!=NULL)
	//	{
	//		DWORD dwsize = 0; 
	//		DWORD dwFilesize = 0;
	//		DWORD dwteshuszie = 0;
	//		for (int i=0;i<pDlg->m_arrScanHenji.GetSize();i++)
	//		{
	//			if(pDlg->m_arrScanHenji[i].iType == nEnd)
	//			{
	//				if(pDlg->m_arrScanHenji[i].strReg.Left(3) == L"HKE")continue;

	//				dwFilesize += pDlg->m_arrScanHenji[i].dwFileLowPart;
	//				if(pDlg->m_arrScanHenji[i].nType != 4)
	//				{
	//					CString str;
	//					str.Format(_T("%s"), pDlg->m_arrScanHenji[i].strReg);
	//					TVINSERTSTRUCT tvInsert;
	//					tvInsert.hParent = 	pDlg->m_arrScanHenji[i].hItem;
	//					tvInsert.hInsertAfter = NULL;
	//					tvInsert.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
	//					tvInsert.item.pszText = (TCHAR*)str.GetBuffer();
	//					tvInsert.item.hItem=NULL;
	//					tvInsert.item.state=INDEXTOSTATEIMAGEMASK(2);
	//					tvInsert.item.stateMask=TVIS_STATEIMAGEMASK;
	//					CString strType;
	//					strType.Format(L"%d", nEnd);
	//					tvInsert.item.iImage=pDlg->m_Tree.SelectBit(strType);
	//					tvInsert.item.iSelectedImage=tvInsert.item.iImage;
	//					tvInsert.item.cChildren=0;
	//					tvInsert.item.lParam=0;
	//					HTREEITEM SubItem = pDlg->m_Tree.InsertItem(&tvInsert);
	//					pDlg->m_arrScanHenji[i].hSubItem = SubItem;
	//					str.ReleaseBuffer();
	//					if(str.Find(L"|")>0)
	//					{
	//						pDlg->m_arrScanHenji[i].nType = 3;
	//						dwteshuszie++;
	//					}
	//					else
	//					{
	//						dwsize++;
	//						pDlg->m_arrScanHenji[i].nType = 2;
	//					}
	//				}
	//				else
	//					dwsize ++;
	//			}
	//		}

	//		CString strText;
	//		dwzh(dwFilesize, strText);
	//		pDlg->m_Tree.GetItemText( pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, strBuff);
	//		if(strBuff.Find(L"��ע���")>0)
	//		{
	//			int n = strBuff.Find(L"��");
	//			int n1 = strBuff.Find(L"��ע���");
	//			CString strBuff1 = strBuff;		
	//			if(n>0) 
	//			{
	//				strBuff1.Format(L"%s",strBuff.Mid(n+1, n1-n-1+4));
	//				if(dwteshuszie>0)
	//				{
	//					if(dwsize>0)
	//					{
	//						strBuff.Format(_T("%s��%d���ļ�������%d�������%s����%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize, dwteshuszie, strBuff1,strText);
	//					}
	//					else
	//					{
	//						strBuff.Format(_T("%s������%d�������%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwteshuszie, strBuff1);
	//					}
	//				}
	//				else
	//				{
	//					if(dwsize>0)
	//					{
	//						strBuff.Format(_T("%s��%d���ļ���%s����%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize, strBuff1,strText);
	//					}
	//					else
	//					{
	//						strBuff.Format(_T("%s��%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, strBuff1);
	//					}
	//				}
	//			}
	//		}
	//		else
	//		{
	//			if(dwteshuszie>0)
	//			{
	//				if(dwsize>0)
	//				{
	//					strBuff.Format(_T("%s��%d���ļ�������%d���������%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize, dwteshuszie,strText);
	//				}
	//				else
	//				{
	//					strBuff.Format(_T("%s������%d�������"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwteshuszie);
	//				}
	//			}
	//			else
	//			{
	//				if (dwsize > 0)
	//				{
	//					strBuff.Format(_T("%s��%d���ļ�����%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize, strText);
	//				}
	//				else
	//				{
	//					strBuff.Format(_T("%s���ޣ�"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);
	//				}
	//			}
	//			//			strBuff.Format(_T("%s��%d���ļ�����%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize, strText);
	//		}

	//		if(nEnd == 6001 || nEnd == 6002 || nEnd == 1005 || nEnd == 6007 || nEnd == 2029 || nEnd == 2030 || nEnd == 6008 ||
	//			nEnd == 6011 || nEnd == 6012 || nEnd == 6013 || nEnd == 6014 || nEnd == 6015 ||nEnd == 6016)
	//		{
	//			if(pDlg->m_mapHenjiScanJs.Lookup(nEnd)==NULL && lpcszFileFullPath != NULL && _wcsicmp(lpcszFileFullPath, L"") != 0)
	//			{
	//				CString str;
	//				str =pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo;
	//				Treety treety;
	//				treety.hItem = pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem;
	//				treety.strReg.Format(_T(""));
	//				treety.strValue.Format(_T(""));
	//				treety.strRegValue.Format(L"");
	//				treety.strParent = str;
	//				treety.iType = nEnd;
	//				treety.nType = 2;
	//				treety.hSubItem = treety.hItem;
	//				pDlg->m_arrScanHenji.Add(treety); //����û��ɾ�����⴦��
	//				if (nEnd != 2029)
	//				{
	//					pDlg->m_mapHenjiScanJs.SetAt(nEnd, 0);//���ε�2��ɨ��
	//				}
	//			}
	//			if (nEnd != 2029)
	//			{
	//				strBuff.Format(_T("%s"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);//����������
	//			}
	//		}
	//		if (lpcszFileFullPath != NULL && _wcsicmp(lpcszFileFullPath, L"") != 0)
	//		{
	//			strBuff.Format(_T("%s��%s��"),pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, lpcszFileFullPath);
	//		}
	//		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_HENJI_TREE_SHOW_HEI, (LPARAM)nEnd, (WPARAM)strBuff.GetBuffer());
	//	}
	//	pDlg->m_cs.Unlock();
	//	return TRUE;
	//}

	if(iType == CLEAN_COMPATE)
	{
		if(pDlg->m_bOneScan)
		{
			//if(pDlg->m_bScanBage) return false;
			CString str;
			str.Format(L"%d_%d", pDlg->m_nProgress , pDlg->m_nNewPro);
			////OutputDebugStringW(str);
			//if(pDlg->m_nProgress != pDlg->m_nNewPro) return false;

			////OutputDebugStringW(L"һ������");		
			pDlg->m_bOneScan = 2;
	//		pDlg->m_dlg->SetItemVisible(IDC_DIV_CLR_SCANING, FALSE);

			DWORD dwsize = 0;
			DWORD dwFileNum = 0;
			POSITION posi;
			posi = pDlg->m_OneMap.GetStartPosition();
			while (posi!=NULL)
			{
				OneTy onety = pDlg->m_OneMap.GetValueAt(posi);
				dwsize += onety.dwFilesize;
				dwFileNum += onety.dwFileNum;
				pDlg->m_OneMap.GetNext(posi);
			}

			if(dwFileNum == 0 && dwsize == 0)
			{
				if(pDlg->m_bOneStop)
				{
			//		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_PRG, 2, (LPARAM)L"û����Ҫ�������Ŀ");
				}
				else
				{
			//		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_PRG, 1, (LPARAM)0);
				}

//				pDlg->m_pOneCleanCallBack->OnCleanEntry(0,NULL,0,L"û����Ҫ������",0);
			}
			else
			{
				CString strFilesize, strValue;
				if(dwsize == 0)
				{
					strValue.Format(L"������%d����Ŀ", dwFileNum);
				}
				else
				{
					dwzh(dwsize, strFilesize);
					strValue.Format(L"������%d���ļ������ͷ�%s���̿ռ�", dwFileNum, strFilesize);
				}
				if(pDlg->m_bOneStop)
				{
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_PRG, 2, (LPARAM)strValue.GetBuffer());
					strValue.ReleaseBuffer();
				}
				else
				{
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_PRG, 0, (LPARAM)strValue.GetBuffer());
					strValue.ReleaseBuffer();
				}

//				pDlg->m_pOneCleanCallBack->OnCleanEntry(0, NULL, 0, strValue,0);
			}
			if(pDlg->m_hTimer != (HANDLE)-1)
			{
				TerminateThread(pDlg->m_hTimer, NULL);
				pDlg->m_hTimer = (HANDLE)-1;
			}
            if (pDlg->m_pCleanPrc != NULL)
            {
			    pDlg->m_pCleanPrc->DZ_IsScanClean(FALSE);
            }
            pDlg->StopCleanEx();

			pDlg->WriteLog(dwFileNum, dwsize);
			return TRUE;
		}
		DWORD dwsize = 0;
		if(pDlg->m_bScanBage) return false;

		if(pDlg->m_Tree.GetScanState())
		{
			pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2,FALSE);
			if(pDlg->m_arrScanHenji.GetSize()>0)
			{
				pDlg->m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, TRUE);
				pDlg->m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, TRUE);
				pDlg->m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTN_SCAN, TRUE);
				pDlg->m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, TRUE);
				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP, FALSE);

				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX1, TRUE);
				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX2, TRUE);
				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX3, TRUE);


				dwsize = pDlg->m_arrScanHenji.GetSize();
				DWORD dwRebotsize = 0;
				for (int i=0;i<pDlg->m_arrScanHenji.GetSize();i++)
				{
					if(pDlg->m_arrScanHenji[i].nType == 4)dwRebotsize++;
				}
				if (!pDlg->IsAllNeedRebootDelete())
				{
					CString strText;
					dwzh(pDlg->m_dwAllFileSize, strText);
					CString strbuffText1 = _T("ɨ������ɣ�������");
					CString strbuffText2 = _T("��ʹ�úۼ���");
					CString strbuffText3 = _T("�ļ�����������ɾ����");
					CString strbuffCount;

					strbuffCount.Format(_T("%d"), dwsize);

					int nTextPos =  strbuffCount.GetLength() * 8 + 140-strbuffCount.GetLength();

					CString strTextPos;
					strTextPos.Format(_T("%d,10"), nTextPos);

					pDlg->m_dlg->SetItemStringAttribute(IDC_TXT_CLR_HENJI_SHOW_EX3, "pos", strTextPos);

					strTextPos.Format(_T("%d,10"), nTextPos + 70);

					pDlg->m_dlg->SetItemStringAttribute(IDC_TXT_CLR_TREETOP2, "pos", strTextPos);

					pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);
					pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2, TRUE);

					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("0"),0);
					//pDlg->WriteLog(dwsize, pDlg->m_dwAllFileSize);
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX1, (LPARAM)_T("0"), (WPARAM)strbuffText1.GetBuffer());
					strbuffText1.ReleaseBuffer();
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX3, (LPARAM)_T("0"), (WPARAM)strbuffText2.GetBuffer());
					strbuffText2.ReleaseBuffer();
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX2, (LPARAM)_T("0"), (WPARAM)strbuffCount.GetBuffer());
					strbuffCount.ReleaseBuffer();
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP3, (LPARAM)_T("0"), (WPARAM)strbuffText3.GetBuffer());
					strbuffText3.ReleaseBuffer();
				} 
				else
				{
					CString strText;
					dwzh(pDlg->m_dwAllFileSize, strText);
					CString strbuffText1 = _T("ɨ������ɣ�������");
					CString strbuffText2 = _T("��ʹ�úۼ���������������");
					CString strbuffCount;

					strbuffCount.Format(_T("%d"), dwsize);

					int nTextPos =  strbuffCount.GetLength() * 8 + 140-strbuffCount.GetLength();

					CString strTextPos;
					strTextPos.Format(_T("%d,10"), nTextPos); 

					pDlg->m_dlg->SetItemStringAttribute(IDC_TXT_CLR_HENJI_SHOW_EX3, "pos", strTextPos);

					pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);
					pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2, TRUE);

					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("0"),0);
					//pDlg->WriteLog(dwsize, pDlg->m_dwAllFileSize);
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX1, (LPARAM)_T("0"), (WPARAM)strbuffText1.GetBuffer());
					strbuffText1.ReleaseBuffer();
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX3, (LPARAM)_T("0"), (WPARAM)strbuffText2.GetBuffer());
					strbuffText2.ReleaseBuffer();
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX2, (LPARAM)_T("0"), (WPARAM)strbuffCount.GetBuffer());
					strbuffCount.ReleaseBuffer();
				}

				pDlg->m_dlg->EnableItem(IDC_TXT_CLR_TREEDOWN_DAFU, TRUE);
				if(dwsize == dwRebotsize)
				{
//					pDlg->m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, FALSE);
				}
			}
			else
			{
				pDlg->m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTN_SCAN, TRUE);
				pDlg->m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, TRUE);
				pDlg->m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, TRUE);
				pDlg->m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, TRUE);

				pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);
				pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP, TRUE);
				::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("2"), (WPARAM)_T("ɨ���Ѿ���ɣ�û����Ҫ�������Ŀ��"));
			}

			pDlg->m_dlg->EnableItem(IDC_TXT_CLR_TREEDOWN_DAFU, TRUE);
			::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_HENJI_SCAN_FINISH, (LPARAM)0, (WPARAM)0);
			pDlg->m_Tree.SetScanState(false);
		}
		return TRUE;
	}
	pDlg->m_cs.Lock();
	

	int nBegin = TREE_BEGIN(iType);
	CString strClearid;
	strClearid.Format(L"%d", nBegin);
	if(pDlg->m_bOneScan && pDlg->m_OneTypeMap.Lookup(strClearid)!=NULL)
	{
		OneTy onety = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value;
		if(onety.dwFileNum == 0 && onety.dwFilesize == 0)
		{
			//��һ�ν��� �ӽڵ㿪ʼɨ��
			onety.strClearInfo.Format(L"0B �ļ�������0");
			onety.strState.Format(L"��������...");
		}
		pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value = onety;
		CString strClearName = onety.strClear2name;
//		pDlg->m_pOneCleanCallBack->OnCleanEntry(0,NULL,0,strClearName,0);
		/*::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_TXT, (LPARAM)0, (WPARAM)strClearName.GetBuffer());

		DWORD dwvalue = 100/pDlg->m_nProgress;
		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_VALUE, (LPARAM)dwvalue*pDlg->m_nNewPro+1, (WPARAM)0);
		pDlg->m_wndListCtrl.SetItemCount(pDlg->m_OneMap.GetCount());*/

		CString strItem;
		strItem = onety.strClear2name;
		pDlg->m_pOneCleanCallBack->OnCleanEntry(strItem.GetLength(), strItem, 0, NULL, 1);

		pDlg->m_cs.Unlock();
		return TRUE;
	}
	else if(pDlg->m_bOneScan && nBegin == 4005)
	{
		//int nkey[50] = {0};
		//int n=0;
		//if(pDlg->m_OneTypeMap.Lookup(L"21001")!=NULL){nkey[n]=21001;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21002")!=NULL){nkey[n]=21002;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21003")!=NULL){nkey[n]=21003;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21004")!=NULL){nkey[n]=21004;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21005")!=NULL){nkey[n]=21005;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21006")!=NULL){nkey[n]=21006;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21007")!=NULL){nkey[n]=21007;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21008")!=NULL){nkey[n]=21008;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21009")!=NULL){nkey[n]=21009;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21010")!=NULL){nkey[n]=21010;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21011")!=NULL){nkey[n]=21011;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21012")!=NULL){nkey[n]=21012;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21013")!=NULL){nkey[n]=21013;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21014")!=NULL){nkey[n]=21014;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21015")!=NULL){nkey[n]=21015;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21016")!=NULL){nkey[n]=21016;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21017")!=NULL){nkey[n]=21017;n++;}
		//if(pDlg->m_OneTypeMap.Lookup(L"21018")!=NULL){nkey[n]=21018;n++;}
		//for (int i=0;i<n;i++)
		//{
		//	strClearid.Format(L"%d", nkey[i]);
		//	if(pDlg->m_OneTypeMap.Lookup(strClearid)!=NULL)
		//	{
		//		OneTy onety = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value;
		//		if(onety.dwFileNum == 0 && onety.dwFilesize == 0)
		//		{
		//			//��һ�ν��� �ӽڵ㿪ʼɨ��
		//			onety.strClearInfo.Format(L"0B �ļ�������0");
		//			onety.strState.Format(L"��������...");
		//		}
		//		pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value = onety;
		//		CString strClearName = onety.strClear2name;
		//		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_TXT, (LPARAM)0, (WPARAM)strClearName.GetBuffer());
		//	}
		//}
		//DWORD dwvalue = 100/pDlg->m_nProgress;
		//::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_VALUE, (LPARAM)dwvalue*pDlg->m_nNewPro+1, (WPARAM)0);

		//pDlg->m_wndListCtrl.SetItemCount(pDlg->m_OneMap.GetCount());
		pDlg->m_cs.Unlock();
		return TRUE;
	}
	else if(pDlg->m_TreeHenjiMap.Lookup(nBegin)!=NULL && pDlg->m_Tree.GetScanState())
	{
		CString str123321;
		str123321.Format(L"%d��ʼ", nBegin);

// 		if (pDlg->m_finishScanId.Find(nBegin) == -1)
// 		{
// 			pDlg->m_finishScanId.Add(nBegin);
// 		}
		////OutputDebugStringW(str123321);

		pDlg->m_Tree.Expand(pDlg->m_Tree.GetParentItem(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem));

		pDlg->m_Tree.SelectSetFirstVisible(pDlg->m_TreeHenjiMap[nBegin].hItem);


		CString str;
		str =pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.strItemInfo;

	//	pDlg->m_Tree.Expand(pDlg->m_Tree.GetParentItem(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem));
		//pDlg->m_ScanLajiMap.SetAt(nBegin,str);
		str = _T("������ɨ�裩")+str;
 		pDlg->m_Tree.SetItemNow(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem);
// 		pDlg->m_Tree.SetItemText(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem, str);
// 		pDlg->m_Tree.SetTextItemColor(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem, RGB(255,0,0));
		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_HENJI_TREE_SHOW_HONG, (LPARAM)nBegin, (WPARAM)str.GetBuffer());
		str.ReleaseBuffer();

		str.Format(_T("����ɨ�裺%s"),pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.strItemInfo);
		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP2, (LPARAM)_T("1"), (WPARAM)str.GetBuffer());
		str.ReleaseBuffer();

		pDlg->m_cs.Unlock();
		return TRUE;
	}
	int nEnd = TREE_END(iType);
	strClearid.Format(L"%d", nEnd);
	if(pDlg->m_bOneScan && pDlg->m_OneTypeMap.Lookup(strClearid)!=NULL)
	{
		if(pDlg->m_OneScanFinish.Lookup(strClearid)!=NULL)
		{
			pDlg->m_cs.Unlock();
			return TRUE;
		}
		pDlg->m_OneScanFinish.SetAt(strClearid, L"1");

		DWORD dwJianceNum = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwJianceNum;
		pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwJiancedNum++;
		DWORD dwJiancedNum = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwJiancedNum;
		if(dwJiancedNum == dwJianceNum)
		{
			DWORD dwFilenum = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwFileNum;
			DWORD dwFilesize = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwFilesize;

			if(dwFilesize == 0 && dwFilenum == 0)
			{
				pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strClearInfo.Format(L"û����Ҫ�������Ŀ");	
				if(pDlg->m_bOneStop)
				{
					pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strState = L"δ�������";
				}
				else
				{
					pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strState = L"ɨ�����";
				}	
			}
			else
			{
				if(pDlg->m_bOneStop)
				{
					pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strState = L"δ�������";
				}
				else
				{
					pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strState = L"�������";
				}
			}
		}
		pDlg->m_cs.Unlock();
		return TRUE;
	}
	else if(pDlg->m_bOneScan && nEnd == 4005)
	{
		pDlg->m_cs.Unlock();
		return TRUE;
	}
	else if(pDlg->m_TreeHenjiMap.Lookup(nEnd)!=NULL && (pDlg->m_Tree.GetScanState() || pDlg->m_bStopScan))
	{
		DWORD dwsize = 0; 
		DWORD dwFilesize = 0;
		DWORD dwteshuszie = 0;
	//	pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP, FALSE);
		for (int i=0;i<pDlg->m_arrScanHenji.GetSize();i++)
		{
			if(pDlg->m_arrScanHenji[i].iType == nEnd)
			{
				if(pDlg->m_arrScanHenji[i].strReg.Left(3) == L"HKE")continue;

				dwFilesize += pDlg->m_arrScanHenji[i].dwFileLowPart;
				if(pDlg->m_arrScanHenji[i].nType != 4)
				{
					CString str;
					str.Format(_T("%s"), pDlg->m_arrScanHenji[i].strReg);
					TVINSERTSTRUCT tvInsert;
					tvInsert.hParent = 	pDlg->m_arrScanHenji[i].hItem;
					tvInsert.hInsertAfter = NULL;
					tvInsert.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
					tvInsert.item.pszText = (TCHAR*)str.GetBuffer();
					tvInsert.item.hItem=NULL;
					tvInsert.item.state=INDEXTOSTATEIMAGEMASK(2);
					tvInsert.item.stateMask=TVIS_STATEIMAGEMASK;
					CString strType;
					strType.Format(L"%d", nEnd);
					tvInsert.item.iImage=pDlg->m_Tree.SelectBit(strType);
					tvInsert.item.iSelectedImage=tvInsert.item.iImage;
					tvInsert.item.cChildren=0;
					tvInsert.item.lParam=0;
					HTREEITEM SubItem = pDlg->m_Tree.InsertItem(&tvInsert);
					pDlg->m_arrScanHenji[i].hSubItem = SubItem;
					if(str.Find(L"|")>0)
					{
						pDlg->m_arrScanHenji[i].nType = 3;
						dwteshuszie++;
					}
					else
					{
						dwsize++;
						pDlg->m_arrScanHenji[i].nType = 2;
					}
				}
				else
					dwsize ++;
			}
		}

		CString strText;
		dwzh(dwFilesize, strText);

		CString strBuff;
		pDlg->m_Tree.GetItemText( pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, strBuff);

		////OutputDebugStringW(strBuff+L"����");

		if(strBuff.Find(L"��ע���")>0)
		{
			int n = strBuff.Find(L"��");
			int n1 = strBuff.Find(L"��ע���");
			CString strBuff1 = strBuff;		
			if(n>0) 
			{
				strBuff1.Format(L"%s",strBuff.Mid(n+1, n1-n-1+4));
				if(dwteshuszie>0)
				{
					if(dwsize>0)
					{
						strBuff.Format(_T("%s��%d���ļ�������%d�������%s����%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize, dwteshuszie, strBuff1,strText);
					}
					else
					{
						strBuff.Format(_T("%s������%d�������%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwteshuszie, strBuff1);
					}
				}
				else
				{
					if(dwsize>0)
					{
						strBuff.Format(_T("%s��%d���ļ���%s����%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize, strBuff1,strText);
					}
					else
					{
						strBuff.Format(_T("%s��%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, strBuff1);
					}
				}
			}
		}
		else
		{
			if(dwteshuszie>0)
			{
				if(dwsize>0)
				{
					strBuff.Format(_T("%s��%d���ļ�������%d���������%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize, dwteshuszie,strText);
				}
				else
				{
					strBuff.Format(_T("%s������%d�������"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwteshuszie);
				}
			}
			else
			{
				if (dwsize > 0)
				{
					strBuff.Format(_T("%s��%d���ļ�����%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize, strText);
				}
				else
				{
					strBuff.Format(_T("%s���ޣ�"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);
				}
			}
//			strBuff.Format(_T("%s��%d���ļ�����%s��"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize, strText);
		}

		if(nEnd == 6001 || nEnd == 6002 || nEnd == 1005 || nEnd == 6007 || nEnd == 2029 || nEnd == 2030 || nEnd == 6008 ||
			nEnd == 6011 || nEnd == 6012 || nEnd == 6013 || nEnd == 6014 || nEnd == 6015 ||nEnd == 6016)
		{
			if(pDlg->m_mapHenjiScanJs.Lookup(nEnd)==NULL && lpcszFileFullPath != NULL && _wcsicmp(lpcszFileFullPath, L"") != 0)
			{
				CString str;
				str =pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo;
				Treety treety;
				treety.hItem = pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem;
				treety.strReg.Format(_T(""));
				treety.strValue.Format(_T(""));
				treety.strRegValue.Format(L"");
				treety.strParent = str;
				treety.iType = nEnd;
				treety.nType = 2;
				treety.hSubItem = treety.hItem;
				pDlg->m_arrScanHenji.Add(treety); //����û��ɾ�����⴦��
				if (nEnd != 2029)
				{
					pDlg->m_mapHenjiScanJs.SetAt(nEnd, 0);//���ε�2��ɨ��
				}
			}
			if (nEnd != 2029)
			{
				strBuff.Format(_T("%s"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);//����������
			}
		}
		if (lpcszFileFullPath != NULL && _wcsicmp(lpcszFileFullPath, L"") != 0)
		{
			strBuff.Format(_T("%s��%s��"),pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, lpcszFileFullPath);
		}

// 		pDlg->m_Tree.SetItemText(pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, strBuff);
// 		pDlg->m_Tree.SetTextItemColor(pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, RGB(0,0,0));
		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_HENJI_TREE_SHOW_HEI, (LPARAM)nEnd, (WPARAM)strBuff.GetBuffer());
		strBuff.ReleaseBuffer();
		//		pDlg->m_dwFileSize = 0;
		pDlg->m_cs.Unlock();
		return TRUE;
	}
	
	int nScaning = TREE_SCANING(iType);
    if(pDlg->m_bOneScan)
	{
		if(nScaning == 4005)
		{
			CString str;
			str.Format(L"%s", lpcszFileFullPath);
			str = str.Left(40)+L"..."+str.Right(17);
			//::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_TXT, (LPARAM)0, (WPARAM)str.GetBuffer());

			pDlg->m_cs.Unlock();

			return TRUE;
		}

	}

	strClearid.Format(L"%d", iType);
	if(pDlg->m_bOneScan && pDlg->m_OneTypeMap.Lookup(strClearid)!=NULL)
	{

		if(pDlg->m_RescanCleanmap.Lookup(lpcszFileFullPath)!=NULL)
		{
			pDlg->m_cs.Unlock();
			return TRUE;
		}
		else
		{
			pDlg->m_RescanCleanmap.SetAt(lpcszFileFullPath,L"�ѱ��Ϊɾ������������Ч����");
		}
		{
			DWORD dwFilenum = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwFileNum;
			if(iType == 4001)
			{
				dwFilenum += atol(CW2A(lpcszFileFullPath));
			}
			else
			{
				dwFilenum++;
			}
			DWORD dwFilesize = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwFilesize;
			dwFilesize += dwFileLowPart;
			if(dwFilesize>0)
			{
				CString strFormat;
				dwzh(dwFilesize, strFormat);
				pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strClearInfo.Format(L"%s �ļ�������%d", strFormat, dwFilenum);	
			}
			else
			{
				pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strClearInfo.Format(L"��Ŀ������%d", dwFilenum);	
			}
			pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwFileNum = dwFilenum;
			pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwFilesize = dwFilesize;
			OneTy onety = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value;
			CString strItem;
			strItem = onety.strClear2name;
			pDlg->m_pOneCleanCallBack->OnCleanEntry(strItem.GetLength(), strItem, (int)wcslen(lpcszFileFullPath), lpcszFileFullPath, 1);
		}
		if(iType<20000&&!pDlg->m_bScanBage)
		{
			CString strClearName = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strClear2name;
	//		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_TXT, (LPARAM)0, (WPARAM)strClearName.GetBuffer());
		}

//		pDlg->m_wndListCtrl.SetItemCount(pDlg->m_OneMap.GetCount());
	}
	else if(pDlg->m_TreeHenjiMap.Lookup(iType)!=NULL && pDlg->m_Tree.GetScanState())
	{
		CString str;

		str =pDlg->m_TreeHenjiMap.Lookup(iType)->m_value.strItemInfo;

		////OutputDebugStringW(str+L"123333333333333333333333");
		Treety treety;
		treety.hItem = pDlg->m_TreeHenjiMap.Lookup(iType)->m_value.hItem;
		treety.strReg.Format(_T("%s"), lpcszFileFullPath);
		treety.dwFileLowPart = dwFileLowPart;
		treety.strParent = str;
		treety.iType = iType;
		// 		pDlg->m_dwFileSize += dwFileLowPart;
		pDlg->m_dwAllFileSize +=dwFileLowPart;

		if(pDlg->m_RescanCleanmap.Lookup(lpcszFileFullPath)!=NULL)
		{
			str.Format(_T("%s%s"), pDlg->m_RescanCleanmap.Lookup(lpcszFileFullPath)->m_value, lpcszFileFullPath);
			TVINSERTSTRUCT tvInsert;
			tvInsert.hParent = 	pDlg->m_TreeHenjiMap.Lookup(iType)->m_value.hItem;
			tvInsert.hInsertAfter = NULL;
			tvInsert.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
			tvInsert.item.pszText = (TCHAR*)str.GetBuffer();
			tvInsert.item.hItem=NULL;
			tvInsert.item.state=INDEXTOSTATEIMAGEMASK(2);
			tvInsert.item.stateMask=TVIS_STATEIMAGEMASK;
			CString strType;
			strType.Format(L"%d", iType);
			tvInsert.item.iImage=pDlg->m_Tree.SelectBit(strType);
			tvInsert.item.iSelectedImage=tvInsert.item.iImage;
			tvInsert.item.cChildren=0;
			tvInsert.item.lParam=0;
			HTREEITEM SubItem = pDlg->m_Tree.InsertItem(&tvInsert);
			treety.hSubItem = SubItem;
			treety.nType = 4;
			str.ReleaseBuffer();
// 			pDlg->m_cs.Unlock();
// 			return TRUE;
		}
		pDlg->m_arrScanHenji.Add(treety);
		str = L"����ɨ�裺" ;
		str += lpcszFileFullPath;
		if (str.GetLength() > 110)
		{
			WCHAR strBuff[110] = {0};
			wcsncpy_s(strBuff, str.GetBuffer(110), 109);
			str.ReleaseBuffer();
			str = strBuff;
			str += L"...";
		}
		if (!pDlg->m_bStopScan && pDlg->m_Tree.GetScanState())
		{
			::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP2, (LPARAM)_T("3"), (WPARAM)str.GetBuffer());
			str.ReleaseBuffer();
		}
		else
		{
			pDlg->m_dlg->SetItemText(IDC_TXT_CLR_TREETOP, L"");
			pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP, FALSE);
		}
	}
	pDlg->m_cs.Unlock();

	return TRUE;
}


BOOL WINAPI CUIHandlerOpt::myScanRegCallBack(void* pMain,int iType,LPCTSTR lpcszKeyFullPath,LPCTSTR lpcszValueName,LPCTSTR lpcszValueData)
{
	CUIHandlerOpt *pDlg = (CUIHandlerOpt*) pMain;
	if (pDlg == NULL)
	{
		return FALSE;
	}
	if (pDlg->m_bOneScan)
	{
		if ( pDlg->m_OneMap.IsEmpty() || pDlg->m_OneTypeMap.IsEmpty())
		{
			pDlg->StopCleanEx();
			return TRUE;
		}
	}
	//if(pDlg->m_bStopScan)
	//{
	//	pDlg->m_cs.Lock();
	//	pDlg->m_dlg->SetItemText(IDC_TXT_CLR_TREETOP, L"");
	//	pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP, FALSE);

	//	int nEnd = TREE_END(iType);
	//	if(pDlg->m_TreeHenjiMap.Lookup(nEnd)!=NULL)
	//	{
	//		DWORD dwsize = 0;
	//		for (int i=0;i<pDlg->m_arrScanHenji.GetSize();i++)
	//		{
	//			int n = pDlg->m_arrScanHenji[i].iType;
	//			if(pDlg->m_arrScanHenji[i].iType == nEnd)
	//			{
	//				if(pDlg->m_arrScanHenji[i].strReg.Left(3) != L"HKE")continue;

	//				dwsize++;
	//				CString str;
	//				if (nEnd == 1004)
	//				{
	//					str.Format(_T("%s"), pDlg->m_arrScanHenji[i].strRegValue);
	//				} 
	//				else
	//				{
	//					str.Format(_T("%s"), pDlg->m_arrScanHenji[i].strRegValue);
	//					if(str.GetLength()>0)str.Format(_T("%s\\%s:%s"), pDlg->m_arrScanHenji[i].strReg, pDlg->m_arrScanHenji[i].strValue, pDlg->m_arrScanHenji[i].strRegValue);
	//					else str.Format(_T("%s\\%s"), pDlg->m_arrScanHenji[i].strReg, pDlg->m_arrScanHenji[i].strValue);
	//				}

	//				TVINSERTSTRUCT tvInsert;
	//				tvInsert.hParent = 	pDlg->m_arrScanHenji[i].hItem;
	//				tvInsert.hInsertAfter = NULL;
	//				tvInsert.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
	//				tvInsert.item.pszText = (TCHAR*)str.GetBuffer();
	//				tvInsert.item.hItem=NULL;
	//				tvInsert.item.state=INDEXTOSTATEIMAGEMASK(2);
	//				tvInsert.item.stateMask=TVIS_STATEIMAGEMASK;
	//				CString strType;
	//				strType.Format(L"%d", nEnd);
	//				tvInsert.item.iImage=pDlg->m_Tree.SelectBit(strType);
	//				tvInsert.item.iSelectedImage=tvInsert.item.iImage;
	//				tvInsert.item.cChildren=0;
	//				tvInsert.item.lParam=0;
	//				HTREEITEM SubItem = pDlg->m_Tree.InsertItem(&tvInsert);
	//				pDlg->m_arrScanHenji[i].hSubItem = SubItem;
	//				pDlg->m_arrScanHenji[i].nType = 1;
	//				str.ReleaseBuffer();
	//			}
	//		}

	//		CString strBuff;
	//		pDlg->m_Tree.GetItemText( pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, strBuff);

	//		//OutputDebugStringW(strBuff+L"1111111");
	//		if(strBuff.Find(L"���ļ�")>0 || strBuff.Find(L"��������")>0)
	//		{
	//			int n = strBuff.Find(L"��");
	//			CString strBuff1 = strBuff.Mid(0, strBuff.GetLength() - 1);	
	//			if (dwsize > 0)
	//			{
	//				strBuff.Format(_T("%s��%d��ע���"), strBuff1, dwsize);
	//			}
	//		}
	//		else if(strBuff.Find(L"�������У�����") != -1)
	//		{
	//		}
	//		else
	//		{
	//			if(dwsize > 0)
	//			{
	//				strBuff.Format(_T("%s����%d��ע���"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize);
	//			}
	//			else
	//			{
	//				strBuff.Format(_T("%s���ޣ�"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);
	//			}
	//			if (lpcszKeyFullPath != NULL && _wcsicmp(lpcszKeyFullPath, L"") != 0)
	//			{
	//				strBuff.Format(_T("%s��%s��"),pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, lpcszKeyFullPath);
	//			}
	//		}

	//		if(nEnd == 6001 || nEnd == 6002 || nEnd == 1005 || nEnd == 6007 || nEnd == 2029 || nEnd == 2030 || nEnd == 6008||
	//			nEnd == 6011 || nEnd == 6012 || nEnd == 6013 || nEnd == 6014 || nEnd == 6015 ||nEnd == 6016)
	//		{
	//			if(pDlg->m_mapHenjiScanJs.Lookup(nEnd)==NULL)
	//			{
	//				CString str;
	//				str =pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo;
	//				Treety treety;
	//				treety.hItem = pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem;
	//				treety.strReg.Format(_T(""));
	//				treety.strValue.Format(_T(""));
	//				treety.strRegValue.Format(L"");
	//				treety.strParent = str;
	//				treety.iType = nEnd;
	//				treety.nType = 1;
	//				treety.hSubItem = treety.hItem;
	//				pDlg->m_arrScanHenji.Add(treety); //����û��ɾ�����⴦��
	//				if (nEnd != 2029)
	//				{
	//					pDlg->m_mapHenjiScanJs.SetAt(nEnd, 0);//���ε�2��ɨ��
	//				}
	//			}
	//			strBuff.Format(_T("%s"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);//����������
	//		}
	//		pDlg->m_Tree.SetItemText(pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, strBuff);
	//		pDlg->m_Tree.SetTextItemColor(pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, RGB(0,0,0));
	//	}
	//	pDlg->m_cs.Unlock();
	//	return TRUE;
	//}

//	pDlg->m_Tree.SetScanState(true);
	if(iType == CLEAN_COMPATE)
	{
		if(pDlg->m_bOneScan)
		{
			if(pDlg->m_bOneScan==2)
			{
				//::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_VALUE, (LPARAM)100, (WPARAM)0);
				////OutputDebugStringW(L"һ������");
				pDlg->m_bOneScan = 0;
				pDlg->m_bOneStop = true;
			}
//			pDlg->m_pOneCleanCallBack->OnCleanEntry(0,NULL,0,L"һ�����������",0);
			pDlg->StopCleanEx();
			return TRUE;
		}

		DWORD dwsize = 0;
		if(pDlg->m_Tree.GetScanState())
		{
			pDlg->m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, TRUE);
			pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2,FALSE);
			if(pDlg->m_arrScanHenji.GetSize()>0)
			{
				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX1, TRUE);
				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX2, TRUE);
				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX3, TRUE);

				if (!pDlg->IsAllNeedRebootDelete())
				{
					CString strText;
					dwzh(pDlg->m_dwAllFileSize, strText);
					CString strbuffText1 = _T("ɨ������ɣ�������");
					CString strbuffText2 = _T("��ʹ�úۼ���");
					CString strbuffText3 = _T("�ļ�����������ɾ����");
					CString strbuffCount;

					strbuffCount.Format(_T("%d"), dwsize);

					int nTextPos =  strbuffCount.GetLength() * 8 + 140-strbuffCount.GetLength();

					CString strTextPos;
					strTextPos.Format(_T("%d,10"), nTextPos);

					pDlg->m_dlg->SetItemStringAttribute(IDC_TXT_CLR_HENJI_SHOW_EX3, "pos", strTextPos);

					strTextPos.Format(_T("%d,10"), nTextPos + 70);

					pDlg->m_dlg->SetItemStringAttribute(IDC_TXT_CLR_TREETOP2, "pos", strTextPos);

					pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);
					pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2, TRUE);

					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("0"),0);
					//pDlg->WriteLog(dwsize, pDlg->m_dwAllFileSize);
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX1, (LPARAM)_T("0"), (WPARAM)strbuffText1.GetBuffer());
					strbuffText1.ReleaseBuffer();
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX3, (LPARAM)_T("0"), (WPARAM)strbuffText2.GetBuffer());
					strbuffText2.ReleaseBuffer();
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX2, (LPARAM)_T("0"), (WPARAM)strbuffCount.GetBuffer());
					strbuffCount.ReleaseBuffer();
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP3, (LPARAM)_T("0"), (WPARAM)strbuffText3.GetBuffer());
					strbuffText3.ReleaseBuffer();
				} 
				else
				{
					CString strText;
					dwzh(pDlg->m_dwAllFileSize, strText);
					CString strbuffText1 = _T("ɨ������ɣ�������");
					CString strbuffText2 = _T("��ʹ�úۼ���������������");
					CString strbuffCount;

					strbuffCount.Format(_T("%d"), dwsize);

					int nTextPos =  strbuffCount.GetLength() * 8 + 140-strbuffCount.GetLength();

					CString strTextPos;
					strTextPos.Format(_T("%d,10"), nTextPos); 

					pDlg->m_dlg->SetItemStringAttribute(IDC_TXT_CLR_HENJI_SHOW_EX3, "pos", strTextPos);

					pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);
					pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2, TRUE);

					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("0"),0);
					//pDlg->WriteLog(dwsize, pDlg->m_dwAllFileSize);
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX1, (LPARAM)_T("0"), (WPARAM)strbuffText1.GetBuffer());
					strbuffText1.ReleaseBuffer();
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX3, (LPARAM)_T("0"), (WPARAM)strbuffText2.GetBuffer());
					strbuffText2.ReleaseBuffer();
					::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP_EX2, (LPARAM)_T("0"), (WPARAM)strbuffCount.GetBuffer());
					strbuffCount.ReleaseBuffer();
				}
			}
			else
			{
				pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP, TRUE);
				::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("2"), (WPARAM)_T("ɨ���Ѿ���ɣ�û����Ҫ�������Ŀ��"));
//				pDlg->m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, FALSE);
			}

			pDlg->m_dlg->EnableItem(IDC_TXT_CLR_TREEDOWN_DAFU, TRUE);
			::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_HENJI_SCAN_FINISH, (LPARAM)0, (WPARAM)0);
			pDlg->m_Tree.SetScanState(false);
		}

		return TRUE;
	}
	pDlg->m_cs.Lock();

	int nBegin = TREE_BEGIN(iType);
	CString strClearid;
	strClearid.Format(L"%d", nBegin);
	if(pDlg->m_bOneScan && pDlg->m_OneTypeMap.Lookup(strClearid)!=NULL)
	{
		OneTy onety = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value;
		if(onety.dwFileNum == 0 && onety.dwFilesize == 0)
		{
			//��һ�ν��� �ӽڵ㿪ʼɨ��
			onety.strClearInfo.Format(L"��Ŀ������%d", onety.dwFileNum);
			onety.strState.Format(L"��������...");
		}
		pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value = onety;
		CString strClearName = onety.strClear2name;

		pDlg->m_pOneCleanCallBack->OnCleanEntry(strClearName.GetLength(), strClearName, 0, NULL, 1);

		pDlg->m_cs.Unlock();
		return TRUE;
	}
	if(pDlg->m_TreeHenjiMap.Lookup(nBegin)!=NULL && pDlg->m_Tree.GetScanState())
	{
		CString str123321;
		str123321.Format(L"%d��ʼ", nBegin);
		//OutputDebugStringW(str123321);

		CString str;
		str =pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.strItemInfo;

// 		if (pDlg->m_finishScanId.Find(nBegin) == -1)
// 		{
// 			pDlg->m_finishScanId.Add(nBegin);
// 		}

		str = _T("������ɨ�裩")+str;
		pDlg->m_Tree.SetItemNow(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem);
		pDlg->m_Tree.SetItemText(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem, str);
		pDlg->m_Tree.SetTextItemColor(pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.hItem, RGB(255,0,0));

		str.Format(_T("����ɨ�裺%s"),pDlg->m_TreeHenjiMap.Lookup(nBegin)->m_value.strItemInfo);
		::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP2, (LPARAM)_T("1"), (WPARAM)str.GetBuffer());
		str.ReleaseBuffer();

		pDlg->m_cs.Unlock();
		return TRUE;
	}
	int nEnd = TREE_END(iType);
	strClearid.Format(L"%d", nEnd);
	if(pDlg->m_bOneScan && pDlg->m_OneTypeMap.Lookup(strClearid)!=NULL)
	{
		if(pDlg->m_OneScanFinish.Lookup(strClearid)!=NULL)
		{
			pDlg->m_cs.Unlock();
			return TRUE;
		}
		pDlg->m_OneScanFinish.SetAt(strClearid, L"1");

		DWORD dwJianceNum = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwJianceNum;
		pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwJiancedNum++;
		DWORD dwJiancedNum = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwJiancedNum;
		if(dwJiancedNum == dwJianceNum)
		{
			DWORD dwFilenum = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwFileNum;
			DWORD dwFilesize = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwFilesize;

			if(dwFilesize == 0 && dwFilenum == 0)
			{
				pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strClearInfo.Format(L"û����Ҫ�������Ŀ");	
				if(pDlg->m_bOneStop)
				{
					pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strState = L"δ�������";
				}
				else
				{
					pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strState = L"ɨ�����";
				}	
			}
			else
			{
				if(pDlg->m_bOneStop)
				{
					pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strState = L"δ�������";
				}
				else
				{
					pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strState = L"�������";
				}
			}
		}
 		CString str123321;
 		str123321.Format(L"%s���", strClearid);

		pDlg->m_cs.Unlock();
		return TRUE;
	}
	else if(pDlg->m_TreeHenjiMap.Lookup(nEnd)!=NULL && (pDlg->m_Tree.GetScanState() || pDlg->m_bStopScan))
	{
	//	pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP, FALSE);
		DWORD dwsize = 0;
		for (int i=0;i<pDlg->m_arrScanHenji.GetSize();i++)
		{
			int n = pDlg->m_arrScanHenji[i].iType;
			if(pDlg->m_arrScanHenji[i].iType == nEnd)
			{
				if(pDlg->m_arrScanHenji[i].strReg.Left(3) != L"HKE")continue;

				dwsize++;
				CString str;
				if (nEnd == 1004)
				{
					str.Format(_T("%s"), pDlg->m_arrScanHenji[i].strRegValue);
				} 
				else
				{
					str.Format(_T("%s"), pDlg->m_arrScanHenji[i].strRegValue);
					if(str.GetLength()>0)str.Format(_T("%s\\%s:%s"), pDlg->m_arrScanHenji[i].strReg, pDlg->m_arrScanHenji[i].strValue, pDlg->m_arrScanHenji[i].strRegValue);
					else str.Format(_T("%s\\%s"), pDlg->m_arrScanHenji[i].strReg, pDlg->m_arrScanHenji[i].strValue);
				}

				TVINSERTSTRUCT tvInsert;
				tvInsert.hParent = 	pDlg->m_arrScanHenji[i].hItem;
				tvInsert.hInsertAfter = NULL;
				tvInsert.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
				tvInsert.item.pszText = (TCHAR*)str.GetBuffer();
				tvInsert.item.hItem=NULL;
				tvInsert.item.state=INDEXTOSTATEIMAGEMASK(2);
				tvInsert.item.stateMask=TVIS_STATEIMAGEMASK;
				CString strType;
				strType.Format(L"%d", nEnd);
				tvInsert.item.iImage=pDlg->m_Tree.SelectBit(strType);
				tvInsert.item.iSelectedImage=tvInsert.item.iImage;
				tvInsert.item.cChildren=0;
				tvInsert.item.lParam=0;
				HTREEITEM SubItem = pDlg->m_Tree.InsertItem(&tvInsert);
				pDlg->m_arrScanHenji[i].hSubItem = SubItem;
				pDlg->m_arrScanHenji[i].nType = 1;
				str.ReleaseBuffer();

                {
                    static int g_nIEVersion = -1;

                    if (g_nIEVersion == -1)
                    {
                        CheckIEVersioin(g_nIEVersion);
                    }
                
                    if (g_nIEVersion <= 6 && g_nIEVersion > 0)
                    {
                        pDlg->m_Tree.SetItemState(SubItem, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK);
                    }
                }
			}
		}

		CString strBuff;
		pDlg->m_Tree.GetItemText( pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, strBuff);

		//OutputDebugStringW(strBuff+L"1111111");
		if(strBuff.Find(L"���ļ�")>0 || strBuff.Find(L"��������")>0)
		{
			int n = strBuff.Find(L"��");
			CString strBuff1 = strBuff.Mid(0, strBuff.GetLength() - 1);	
			if (dwsize > 0)
			{
				strBuff.Format(_T("%s��%d��ע���"), strBuff1, dwsize);
			}
		}
		else if(strBuff.Find(L"�������У�����") != -1)
		{
		}
		else
		{
			if(dwsize > 0)
			{
				strBuff.Format(_T("%s����%d��ע���"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, dwsize);
			}
			else
			{
				strBuff.Format(_T("%s���ޣ�"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);
			}
			if (lpcszKeyFullPath != NULL && _wcsicmp(lpcszKeyFullPath, L"") != 0)
			{
				strBuff.Format(_T("%s��%s��"),pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo, lpcszKeyFullPath);
			}
		}

		if(nEnd == 6001 || nEnd == 6002 || nEnd == 1005 || nEnd == 6007 || nEnd == 2029 || nEnd == 2030 || nEnd == 6008||
			nEnd == 6011 || nEnd == 6012 || nEnd == 6013 || nEnd == 6014 || nEnd == 6015 ||nEnd == 6016)
		{
			if(pDlg->m_mapHenjiScanJs.Lookup(nEnd)==NULL)
			{
				CString str;
				str =pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo;
				Treety treety;
				treety.hItem = pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem;
				treety.strReg.Format(_T(""));
				treety.strValue.Format(_T(""));
				treety.strRegValue.Format(L"");
				treety.strParent = str;
				treety.iType = nEnd;
				treety.nType = 1;
				treety.hSubItem = treety.hItem;
				pDlg->m_arrScanHenji.Add(treety); //����û��ɾ�����⴦��
				if (nEnd != 2029)
				{
					pDlg->m_mapHenjiScanJs.SetAt(nEnd, 0);//���ε�2��ɨ��
				}
			}
			strBuff.Format(_T("%s"), pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.strItemInfo);//����������
		}
		pDlg->m_Tree.SetItemText(pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, strBuff);
		pDlg->m_Tree.SetTextItemColor(pDlg->m_TreeHenjiMap.Lookup(nEnd)->m_value.hItem, RGB(0,0,0));

		pDlg->m_cs.Unlock();
		return TRUE;
	}
	strClearid.Format(L"%d", iType);
	if(pDlg->m_bOneScan && pDlg->m_OneTypeMap.Lookup(strClearid)!=NULL)
	{
		{
			DWORD dwFilenum = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwFileNum;
			dwFilenum++;
			DWORD dwFilesize = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwFilesize;
			if(dwFilesize>0)
			{
				CString strFormat;
				dwzh(dwFilesize, strFormat);
				pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strClearInfo.Format(L"%s �ļ�������%d", strFormat, dwFilenum);	
			}
			else
			{
				pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strClearInfo.Format(L"��Ŀ������%d", dwFilenum);	
			}
			pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.dwFileNum = dwFilenum;
		}

		OneTy onety = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value;
		CString strItem;
		strItem = onety.strClear2name;
		
		/*pDlg->m_pOneCleanCallBack->OnCleanEntry(0,NULL,0,)*/

		CString strOutput;
		strOutput.Format(_T("%s\\%s\\%s"), lpcszKeyFullPath, lpcszValueName, lpcszValueData);
		pDlg->m_pOneCleanCallBack->OnCleanEntry(strItem.GetLength(), strItem, (int)wcslen(strOutput), strOutput, 1);
		if(!pDlg->m_bScanBage)
		{
			CString strClearName = pDlg->m_OneMap.Lookup(pDlg->m_OneTypeMap.Lookup(strClearid)->m_value)->m_value.strClear2name;
			::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_ONE_SCAN_TXT, (LPARAM)0, (WPARAM)strClearName.GetBuffer());
			strClearName.ReleaseBuffer();
		}

		pDlg->m_wndListCtrl.SetItemCount((int)pDlg->m_OneMap.GetCount());
	}
	else if(pDlg->m_TreeHenjiMap.Lookup(iType)!=NULL && pDlg->m_Tree.GetScanState())
	{
		CString str;
		str =pDlg->m_TreeHenjiMap.Lookup(iType)->m_value.strItemInfo;

		//OutputDebugStringW(str+L"123333333333333333333333");

		Treety treety;
		treety.hItem = pDlg->m_TreeHenjiMap.Lookup(iType)->m_value.hItem;
		treety.strReg.Format(_T("%s"), lpcszKeyFullPath);
		treety.strValue.Format(_T("%s"), lpcszValueName);
		treety.strRegValue.Format(L"%s", lpcszValueData);
		treety.strParent = str;
		treety.iType = iType;
		pDlg->m_arrScanHenji.Add(treety);

		CString str1 = L"����ɨ�裺" ;
		str1 += lpcszKeyFullPath;
		str1 += L"\\";
		str1 += lpcszValueName;
		str1 += L"\\";
		str1 += lpcszValueData;
		if (str1.GetLength() > 110)
		{
			WCHAR strBuff[110] = {0};
			wcsncpy_s(strBuff, str1.GetBuffer(110), 109);
			str1.ReleaseBuffer();
			str1 = strBuff;
			str1 += L"...";
		}

		if (!pDlg->m_bStopScan && pDlg->m_Tree.GetScanState())
		{
			::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREETOP2, (LPARAM)_T("1"), (WPARAM)str1.GetBuffer());
			str1.ReleaseBuffer();
		}
		else
		{
			pDlg->m_dlg->SetItemText(IDC_TXT_CLR_TREETOP, L"");
			pDlg->m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP, FALSE);
		}
	}
	else
	{
		CString str;
		str.Format(L"δƥ��%d", iType);
		//OutputDebugStringW(str);
	}
	pDlg->m_cs.Unlock();
	return TRUE;
}

static BOOL IsOpTrayRunItem(DWORD nRunType, LPCTSTR lpstrName)
{
	if (_tcsicmp(lpstrName,_T("KSafeTray"))==0)
	{
		if (IsHKLMRunType(nRunType))
			return TRUE;
	}
	return FALSE;
}

HRESULT CUIHandlerOpt::GetKSoftDirectory(CString &strDir)
{
    wchar_t szAppPath[MAX_PATH] = { 0 };

    GetModuleFileNameW(NULL, szAppPath, MAX_PATH);
    PathRemoveFileSpecW(szAppPath);
	strDir = szAppPath;
    strDir += L"\\";

	return S_OK;
}

void CUIHandlerOpt::WriteLog(DWORD dwNum, DWORD dwSize)
{
	DWORD dwCount=0,dwFilesize=0;
	if(PathFileExists(m_ScanLogFile))
	{
		TCHAR	szBuffer[MAX_PATH] = {0};
		GetPrivateProfileString( _T("Statistics"), _T("upfilecount"), _T("0"), szBuffer, 100,m_ScanLogFile);
		dwCount = atol(CW2A(szBuffer));
		GetPrivateProfileString( _T("Statistics"), _T("upfilesize"), _T("0"), szBuffer, 100,m_ScanLogFile);
		dwFilesize = atol(CW2A(szBuffer));
		dwNum += dwCount;
		dwSize += dwFilesize;
	}
	CString	strFormat;
	strFormat = CTime::GetCurrentTime().Format( _T( "%Y-%m-%d %H:%M:%S" ) );

//	strFormat.Format(_T("%Y-%M-%d %H:%m:%D"), CTime::GetCurrentTime().GetTime());
	WritePrivateProfileString(_T("Statistics"), _T("uptime"), strFormat, m_ScanLogFile);
	strFormat.Format(_T("%d"), dwNum);
	WritePrivateProfileString( _T("Statistics"), _T("upfilecount"), strFormat, m_ScanLogFile);
	strFormat.Format(_T("%d"), dwSize);
	WritePrivateProfileString( _T("Statistics"), _T("upfilesize"), strFormat, m_ScanLogFile);
}
void CUIHandlerOpt::Init()
{
	m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);
	m_Tree.Create(m_dlg->GetViewHWND(), NULL, NULL, WS_TABSTOP | WS_CHILD | TVS_CHECKBOXES | TVS_HASLINES | TVS_HASBUTTONS | TVS_FULLROWSELECT | TVS_LINESATROOT | TVS_DISABLEDRAGDROP | TVS_SHOWSELALWAYS, 
		0, IDC_TREE_CLR_GAOJI, NULL );
    m_Tree.SetFont(KuiFontPool::GetFont(FALSE, FALSE, FALSE));
    m_Tree.SetItemHeight( 20 );

	m_wndListCtrl.Create( 
		m_dlg->GetViewHWND(), NULL, NULL, 
		WS_CHILD | LVS_REPORT | LVS_OWNERDATA | LVS_SHOWSELALWAYS | LVS_SINGLESEL , 
		0, IDC_LST_CLR_SCAN);
	{
		m_wndListCtrl.InsertColumn(0, _T("������Ŀ"), LVCFMT_LEFT, 230);
		m_wndListCtrl.InsertColumn(1, _T("�ļ���С"), LVCFMT_LEFT, 230);
		m_wndListCtrl.InsertColumn(2, _T("״̬"), LVCFMT_LEFT,157);

        KAppRes& appRes = KAppRes::Instance();
		m_wndListCtrl.SetItemHeight(28);
	}
	
}

void CUIHandlerOpt::InitDelay()
{
	InitDLL();
	if(m_bDllLoadError) 
		return;

	InitHenji();

	RebotUserTree();
	m_cs.Init();
	m_bScanBage = false;
	m_bOneScan = false;
	m_bOneStop = false;
	m_mapHenjiScanJs.RemoveAll();
	m_RescanCleanmap.RemoveAll();

	{
		m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTN,TRUE);
		m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTNRESCAN,FALSE);
		m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTN_CLEAN,TRUE);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, FALSE);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, FALSE);
		m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTN_SCAN, FALSE);
		::SendMessage(m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("3"), (WPARAM)_T("ʹ�úۼ��ᱩ¶������˽�����鶨������"));
	}
}

void CUIHandlerOpt::GetCheckReg(CAtlMap<int, TreeInfo>& TreeMap, CWH3StateCheckTreeCtrl10* Tree,bool bScanFinish)
{
	POSITION pos;
	pos = TreeMap.GetStartPosition();
	while (pos!=NULL)
	{
		int n = TreeMap.GetKeyAt(pos);
		TreeInfo treeinfo = TreeMap.GetNextValue(pos);
		if(Tree->GetCheckState(treeinfo.hItem))
		{
			TreeMap[n].iCheck = 2;
			if(bScanFinish)
			{
 				CString strBuff1, strBuff;
				strBuff = treeinfo.strItemInfo;
 				Tree->GetItemText(treeinfo.hItem, strBuff1);
 				if(!(strBuff1.Find(L"��0")>0 /*|| strBuff1.Find(L"��0")>0*/))continue;
 				if(strBuff.Find(L"��ʱ��Ч")>0)
 				{
 					strBuff.Replace(L"��ʱ��Ч", L"û����Ҫ�������Ŀ");
 				}
 				else
 					strBuff.Format(L"%s��û����Ҫ�������Ŀ��", treeinfo.strItemInfo);
 
 				Tree->SetItemText(treeinfo.hItem, strBuff);
 				Tree->SetState(treeinfo.hItem,2);
			}
		}
		else
		{
			TreeMap[n].iCheck = 1;
		}
	}
}

void CUIHandlerOpt::SetCheckTree(CAtlMap<int, TreeInfo>& TreeMap, CString strTypeid, CWH3StateCheckTreeCtrl10* Tree)
{
	for (int i=0;i<m_arrClearInfo.GetSize();i++)
	{
		if(m_arrClearInfo[i].strTypeid.Left(1)==strTypeid)
		{
			int n = atoi(CW2A(m_arrClearInfo[i].strClearid));
			
			if(TreeMap.Lookup(n)!=NULL)
			{
				Tree->SetState(TreeMap.Lookup(n)->m_value.hItem, m_arrClearInfo[i].nCheck+1);
			}
		}
	}
	Tree->Set2ItemState(Tree->GetRootItem());
}
void CUIHandlerOpt::ResearchReg(CAtlMap<int, TreeInfo>& TreeMap, CWH3StateCheckTreeCtrl10* Tree)
{
 	HTREEITEM		hCurrent = NULL;
	POSITION pos;
	pos = TreeMap.GetStartPosition();
	while (pos!=NULL)
	{
		int n = TreeMap.GetKeyAt(pos);
		TreeInfo treeinfo = TreeMap.GetNextValue(pos);
		Tree->DeleteChild(treeinfo.hItem);
		Tree->SetItemText(treeinfo.hItem,treeinfo.strItemInfo);
	}
}
void CUIHandlerOpt::InitDLL()
{
	HINSTANCE hInstance;
	CString strMoudlePath, strClean, strZClean;
	GetKSoftDirectory(strMoudlePath);
	strClean = strMoudlePath;
	strZClean = strMoudlePath;
	m_ScanLogFile = strMoudlePath + _T("AppData\\kclear_history");
	m_CacheFile = strMoudlePath + _T("cfg\\lastrecord.inf");
	strClean.Append(_T("trackcleaner.dll"));
	hInstance = LoadLibrary(strClean);
	if (hInstance == NULL)
	{
		//OutputDebugStringW(_T("InitDLL::DLL ERROR"));
		m_bDllLoadError = true;
		return;
	}

 	pCreateObject CreateObject;
 	CreateObject = (pCreateObject)GetProcAddress(hInstance, "CreateCleanMgrObject");
 	CreateObject(__uuidof(ICleanMgr), (void**) &m_pCleanMgr);
 
 	CString strClearxml;
 	strClearxml = strMoudlePath;
 	strClearxml.Append(_T("data\\clearsoft.dat"));
 
 	CreateObject = (pCreateObject)GetProcAddress(hInstance, "CreateCleanMgrObject");
 	CreateObject(__uuidof(IKClearProc), (void**) &m_pCleanPrc);
  	if(m_pCleanPrc==NULL)
 	{
		//OutputDebugStringW(_T("GetProcAddress::IKClearProc::Error"));
		m_bDllLoadError = true;
 	}
	else
	{
		m_pCleanPrc->DZ_SetCleanCallBackError(myScanRegCallBackError, myScanFileCallBackError, this);
		m_pCleanPrc->DZ_SetCleanCallBack(myScanRegCallBack,myScanFileCallBack,this);	
		m_bDllLoadError = false;
	}
	//��ʼ����
	m_arrClearType.RemoveAll();
	m_arrClearInfo.RemoveAll();
	ClearTreeType cleartreetype;

	cleartreetype.nSn = 1;
	cleartreetype.strTypeName = _T("Internet Explorer�����ۼ�");
	cleartreetype.strTypeid = _T("101");
	cleartreetype.strBmpurl = _T("//IEpassword.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 2;
	cleartreetype.strTypeName = _T("�������������ۼ�");
	cleartreetype.strTypeid = _T("102");
	cleartreetype.strBmpurl = _T("//FirefoxMac.bmp");
	m_arrClearType.Add(cleartreetype);


	cleartreetype.nSn = 3;
	cleartreetype.strTypeName = _T("�ȸ�����������ۼ�");
	cleartreetype.strTypeid = _T("103");
	cleartreetype.strBmpurl = _T("//googleChrome.bmp");
	m_arrClearType.Add(cleartreetype);


	cleartreetype.nSn = 4;
	cleartreetype.strTypeName = _T("��������������ۼ�");
	cleartreetype.strTypeid = _T("104");
	cleartreetype.strBmpurl = _T("//maxthon.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 5;
	cleartreetype.strTypeName = _T("�ѹ�����������ۼ�");
	cleartreetype.strTypeid = _T("105");
	cleartreetype.strBmpurl = _T("//sogo.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 6;
	cleartreetype.strTypeName = _T("Opera����������ۼ�");
	cleartreetype.strTypeid = _T("106");
	cleartreetype.strBmpurl = _T("//opera_.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 8;
	cleartreetype.strTypeName = _T("����֮������������ۼ�");
	cleartreetype.strTypeid = _T("108");
	cleartreetype.strBmpurl = _T("//windowofworld.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 9;
	cleartreetype.strTypeName = _T("��������������ۼ�");
	cleartreetype.strTypeid = _T("109");
	cleartreetype.strBmpurl = _T("//aboutIE.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 10;
	cleartreetype.strTypeName = _T("����������������ۼ�");
	cleartreetype.strTypeid = _T("112");
	cleartreetype.strBmpurl = _T("//toolbar.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 11;
	cleartreetype.strTypeName = _T("Windowsϵͳ��ʷ�ۼ�");
	cleartreetype.strTypeid = _T("110");
	cleartreetype.strBmpurl = _T("//sys.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 12;
	cleartreetype.strTypeName = _T("Windowsϵͳ�Դ�����ۼ�");
	cleartreetype.strTypeid = _T("111");
	cleartreetype.strBmpurl = _T("//filetype.bmp");
	m_arrClearType.Add(cleartreetype);


	cleartreetype.nSn = 15;
	cleartreetype.strTypeName = _T("�칫���");
	cleartreetype.strTypeid = _T("115");
	cleartreetype.strBmpurl = _T("//office.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 16;
	cleartreetype.strTypeName = _T("ý�岥�����");
	cleartreetype.strTypeid = _T("116");
	cleartreetype.strBmpurl = _T("//kmplayer.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 17;
	cleartreetype.strTypeName = _T("�������");
	cleartreetype.strTypeid = _T("117");
	cleartreetype.strBmpurl = _T("//download.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 18;
	cleartreetype.strTypeName = _T("ѹ����ѹ���");
	cleartreetype.strTypeid = _T("118");
	cleartreetype.strBmpurl = _T("//winrar.bmp");
	m_arrClearType.Add(cleartreetype);

	cleartreetype.nSn = 20;
	cleartreetype.strTypeName = _T("�������");
	cleartreetype.strTypeid = _T("120");
	cleartreetype.strBmpurl = _T("//application.bmp");
	m_arrClearType.Add(cleartreetype);

	ClearTreeInfo cleartreeinfo;
	//typeid=101

////////////////////////////////////////////////////////////
////Internet Explorer
//////////////////////////////////////////////////////////////
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

// 	cleartreeinfo.nApp = 0;
// 	cleartreeinfo.strTypeid = _T("110");
// 	cleartreeinfo.nCheck = 1;
// 	cleartreeinfo.strClearid = _T("2036");
// 	cleartreeinfo.nSn = 21;
// 	cleartreeinfo.strClearName = _T("����ͼ����");
// 	cleartreeinfo.strExtName = _T("");
// 	cleartreeinfo.nFileext = 0;
// 	cleartreeinfo.strBmpurl = _T("//suolvtu.bmp");
// 	m_arrClearInfo.Add(cleartreeinfo);

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

// 	cleartreeinfo.nApp = 0;
// 	cleartreeinfo.strTypeid = _T("112");
// 	cleartreeinfo.nCheck = 1;
// 	cleartreeinfo.strClearid = _T("2035");
// 	cleartreeinfo.nSn = 4;
// 	cleartreeinfo.strClearName = _T("Windows Live������������¼");
// 	cleartreeinfo.strExtName = _T("");
// 	cleartreeinfo.nFileext = 0;
// 	cleartreeinfo.strBmpurl = _T("//Windows_Live.bmp");
// 	m_arrClearInfo.Add(cleartreeinfo);

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
	cleartreeinfo.nSn = 6;
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

// 	cleartreeinfo.nApp = 3;
// 	cleartreeinfo.strTypeid = _T("116");
// 	cleartreeinfo.nCheck = 0;
// 	cleartreeinfo.strClearid = _T("9045");
// 	cleartreeinfo.nSn = 5;
// 	cleartreeinfo.strClearName = _T("���в�����ʷ");
// 	cleartreeinfo.strExtName = _T("");
// 	cleartreeinfo.nFileext = 0;
// 	cleartreeinfo.strBmpurl = _T("//fengxing.bmp");
// 	m_arrClearInfo.Add(cleartreeinfo);

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

// 	cleartreeinfo.nApp = 3;
// 	cleartreeinfo.strTypeid = _T("116");
// 	cleartreeinfo.nCheck = 0;
// 	cleartreeinfo.strClearid = _T("9047");
// 	cleartreeinfo.nSn = 7;
// 	cleartreeinfo.strClearName = _T("�������ֺв�����ʷ��������ʷ");
// 	cleartreeinfo.strExtName = _T("");
// 	cleartreeinfo.nFileext = 0;
// 	cleartreeinfo.strBmpurl = _T("//kuwo.bmp");
// 	m_arrClearInfo.Add(cleartreeinfo);

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
	cleartreeinfo.nCheck = 0;
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
//�����ļ��е���
	if(m_pCleanMgr!=NULL)
	{
		m_pCleanMgr->SetTreeCallBack(SoftTreeCallBack, this);
		//		m_pCleanMgr->SetSoftInfoCallBack(SoftInfoCallBack, this);
		m_pCleanMgr->LoadTreetruct(strClearxml);
	}
}


void CUIHandlerOpt::InitHenji()
{
	m_TreeHenjiMap.RemoveAll();

	CString strMoudlePath;
	GetKSoftDirectory(strMoudlePath);
	strMoudlePath +=L"data\\icon";
	DWORD dwsize = 0;
	//����ͼ��
	CAtlMap<CString,CString> mapIDvsBitName;
	for (int i=0;i<m_arrClearType.GetSize();i++)
	{
		ClearTreeType treetype = m_arrClearType[i];

		if(treetype.strTypeid.Left(1) == "1")
		{
			CString strUrl = treetype.strBmpurl;
			int n = strUrl.ReverseFind('/');
			if(n>0)strUrl.Delete(0, n+1);
			else strUrl = L"";
			mapIDvsBitName.SetAt(treetype.strTypeid, strUrl);

			for (int i=0;i<m_arrClearInfo.GetSize();i++)
			{
				ClearTreeInfo treeInfo = m_arrClearInfo[i];

				if(treeInfo.strTypeid == treetype.strTypeid)
				{
					if(treeInfo.strTypeid == L"105")dwsize++;
					strUrl = treeInfo.strBmpurl;
					n = strUrl.ReverseFind('/');
					if(n>0)strUrl.Delete(0, n+1);
					else strUrl = L"";
					mapIDvsBitName.SetAt(treeInfo.strClearid, strUrl);
				}
			}
		}
	}
	//����
	//m_Tree.LoadHBitmap(strMoudlePath, mapIDvsBitName);
	m_Tree.Init3State("IDB_CLR_TREE_ICON",strMoudlePath, mapIDvsBitName);
	m_Tree.SetDlghWnd(m_dlg->m_hWnd,3);




	for (int i=0;i<m_arrClearType.GetSize();i++)
	{
		ClearTreeType treetype = m_arrClearType[i];
		
		if(treetype.strTypeid == L"105")
		{
			if(dwsize==0)continue;
		}
		if(treetype.strTypeid.Left(1) == "1")
		{ 
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
			treetype.strTypeName.ReleaseBuffer();
			HTREEITEM hCurrent = m_Tree.InsertItem( &tvInsert );
			if (treetype.strTypeid == L"101")
			{
				m_RootTree = hCurrent;
			}

			for (int i=0;i<m_arrClearInfo.GetSize();i++)
			{
				ClearTreeInfo treeInfo = m_arrClearInfo[i];

				if(treeInfo.strTypeid == treetype.strTypeid)
				{
					if(treeInfo.strClearid == "")continue;
					tvInsert.hParent=hCurrent;
					tvInsert.item.iImage=0;
					tvInsert.item.pszText=treeInfo.strClearName.GetBuffer(treeInfo.strClearName.GetLength());
					tvInsert.item.state=INDEXTOSTATEIMAGEMASK(treeInfo.nCheck+1);//
					tvInsert.item.iImage=m_Tree.SelectBit(treeInfo.strClearid);
					tvInsert.item.iSelectedImage=tvInsert.item.iImage;
					HTREEITEM hSub = m_Tree.InsertItem(&tvInsert);
					TreeInfo treeinfo;
					treeinfo.hItem = hSub;
					treeinfo.iCheck = treeInfo.nCheck+1;
					treeinfo.strItemInfo = treeInfo.strClearName;
					treeinfo.nSn = treeInfo.nSn;
					treeinfo.nType = atoi(CW2A(treeInfo.strTypeid));
					int n = atoi(CW2A(treeInfo.strClearid));
					m_TreeHenjiMap.SetAt(n, treeinfo);
					treeInfo.strClearName.ReleaseBuffer();
				}
			}
		}
	}
	HTREEITEM hRoot = m_Tree.GetRootItem();
//	m_Tree.Expand( hRoot);
	HTREEITEM hCurrent = m_Tree.GetNextItem( hRoot, TVGN_CHILD );
	while ( hCurrent != NULL )
	{
		m_Tree.Expand( hCurrent );
		hCurrent = m_Tree.GetNextItem( hCurrent, TVGN_NEXT );
	}
	RebotUserTree();
	m_Tree.Select( hRoot, TVGN_FIRSTVISIBLE );
//	m_Tree.SetScrollPos( SB_HORZ, 0, TRUE );
	m_Tree.ResetItemState(hRoot);
}
BOOL CUIHandlerOpt::_FindRunItem( CKsafeRunInfo* pInfo )
{
	CKsafeRunInfo*	pNewInfo = pInfo;

	SHFILEINFO		hFileInfo = {0};
	if (!pNewInfo->bSystem)
	{
		::SHGetFileInfo(pNewInfo->strExePath,FILE_ATTRIBUTE_NORMAL,&hFileInfo,sizeof(SHFILEINFO),SHGFI_ICON);
	}

	m_runList.InsertItemX(pNewInfo,hFileInfo.hIcon);

	if (pInfo->bUnknown)
	{
		struct RUN_RPT_DATA
		{
			DWORD		nType;
			CString		strname;
			CString		strApp;
		};
		static CSimpleArray<RUN_RPT_DATA>	listReportX;

		BOOL	bFind = FALSE;
		for (int i=0; i<listReportX.GetSize(); i++)
		{
			RUN_RPT_DATA&	item = listReportX[i];

			if (item.nType==pInfo->nType&&
				item.strname.CompareNoCase(pInfo->strName)==0 &&
				item.strApp.CompareNoCase(pInfo->strExePath)==0)
			{
				bFind = TRUE;
			}
		}

		if (!bFind)
		{
			RUN_RPT_DATA	item;
			item.nType		= pInfo->nType;
			item.strname	= pInfo->strName;
			item.strApp		= pInfo->strExePath;
			listReportX.Add(item);
		}
	}

	return TRUE;
}

void CUIHandlerOpt::FirstShow()
{
	m_bFirstShowed = TRUE;
	::PostMessage(m_dlg->m_hWnd,MSG_SYSOPT_RUN_FIRST_IN,NULL,NULL);
}

BOOL CUIHandlerOpt::OnBkRunTypeSelChange( int nTabItemIDOld, int nTabItemIDNew )
{
	if (!IsOpPermit())
		return FALSE;

	m_runList.SetShowType(nTabItemIDNew+1);

	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ALL,FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ENABEL,TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_DISABLE,TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ALL2,FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ENABEL2,TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_DISABLE2,TRUE);

	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_SYSTEM,TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_HIDE_SYSTEM,FALSE);

	m_dlg->SetItemVisible(IDC_DIV_RUNOPT_BTM_RUN_JOB_OP,(nTabItemIDNew+1!=KSRUN_TYPE_SERVICE) );
	m_dlg->SetItemVisible(IDC_LBL_RUNOPT_BTM_SERVICE_OP,(nTabItemIDNew+1==KSRUN_TYPE_SERVICE) );
	

	RefreshTabNumber(nTabItemIDNew);
	SetTopRunDiv(nTabItemIDNew);
	return TRUE;
}

BOOL CUIHandlerOpt::OnClickButton( CKsafeRunInfo* pInfo )
{
	if (!IsOpPermit())
		return FALSE;

	if (pInfo->bEnable && !pInfo->strWarning.IsEmpty())
	{
		CString			str;
		CKuiMsgBox	msgBox;
		str.Format(_T("��Ҫ��ֹ�����ڿ���ʱ����������ܻᵼ���������⣺\r\n%s\r\nȷ��Ҫ��ֹ��\r\n"), pInfo->strWarning);

		msgBox.AddButton(_T("ȷ��"),IDYES);
		msgBox.AddButton(_T("ȡ��"),IDNO);
		if(msgBox.ShowMsg(str, NULL, MB_BK_CUSTOM_BUTTON|MB_ICONWARNING) != IDYES)
			return FALSE;
	}

	if (m_pRunOptEng)
	{
		if (m_pRunOptEng->ControlRun(!pInfo->bEnable, pInfo))
		{
			pInfo->bEnable = !pInfo->bEnable;
		
			if ( pInfo->nType == KSRUN_TYPE_STARTUP && IsOpTrayRunItem(pInfo->nRegType,pInfo->strName) )
			{
// 				CSafeMonitorTrayShell x;
// 				x.SetAllMonitorRun(pInfo->bEnable);
			}
		}
		else
		{
			CKuiMsgBox::Show(_T("����������޸�ʧ�ܣ������Ǳ������������簲ȫ�������ֹ��"),NULL,MB_OK|MB_ICONWARNING);
		}
	}
	int i=m_runList.GetItemIndexByKSInfo(pInfo);

	if (i>=0)
	{
		m_runList.InvalidateRect(NULL);
	}
	RefreshTabNumber();

	return TRUE;
}

void CUIHandlerOpt::OnBkShowEnable()
{
	m_runList.SetSubShowType(SUB_SHOW_TYPE_ENABLE);

	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ALL, TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ENABEL, FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_DISABLE, TRUE);

	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ALL2, TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ENABEL2, FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_DISABLE2, TRUE);

	RefreshTabNumber();
}

void CUIHandlerOpt::OnBkShowDisable()
{
	m_runList.SetSubShowType(SUB_SHOW_TYPE_DISABLE);

	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ALL, TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ENABEL, TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_DISABLE, FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ALL2, TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ENABEL2, TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_DISABLE2, FALSE);

	RefreshTabNumber();
}

void CUIHandlerOpt::OnBkShowAll()
{
	m_runList.SetSubShowType(SUB_SHOW_TYPE_ALL);

	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ALL,FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ENABEL,TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_DISABLE,TRUE);

	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ALL2,FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ENABEL2,TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_DISABLE2,TRUE);

	RefreshTabNumber();
}

void CUIHandlerOpt::OnBkHideSystem()
{
	m_runList.SetShowSystem(FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_SYSTEM,TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_HIDE_SYSTEM,FALSE);
	RefreshTabNumber();
}

void CUIHandlerOpt::OnBkShowSystem()
{
	m_runList.SetShowSystem(TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_SYSTEM,FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_HIDE_SYSTEM,TRUE);
	RefreshTabNumber();
}

void CUIHandlerOpt::OnListReSize( CRect rcWnd )
{
//	m_runList.SetColumnWidth(0,rcWnd.Width()-170);
//	m_runList.SetColumnWidth(1,150);
}
void CUIHandlerOpt::OnOneListReSize( CRect rcWnd )
{
	int iWidth = (rcWnd.Width()-230-230-157)/2;
	m_wndListCtrl.SetColumnWidth(0, 230+iWidth);
	m_wndListCtrl.SetColumnWidth(1, 230+iWidth);
	m_wndListCtrl.SetColumnWidth(2, 157);
}

void CUIHandlerOpt::RefreshItemList()
{
	if (!IsOpPermit())
		return;

	m_runList.ClearAll();
	m_runList.SetLoadShow(TRUE);

	if (m_pRunOptEng!=NULL)
	{
		m_pRunOptEng->EnumRunInfo(0,this);
		m_nState = STATE_RUNOPT_SCAN;
		m_dlg->SetItemVisible(IDC_DIV_RUNOPT_BOTTOM,FALSE);
	}
}

void CUIHandlerOpt::OnBkCancelAll()
{
// 	if (!IsOpPermit())
// 		return;
// 
// 	CString		str;
// 	DWORD		nType = m_dlg->GetTabCurSel(IDC_TAB_RUNOPT_TYPE);
// 	if (nType==0)
// 		str = _T("������");
// 	else if (nType==1)
// 		str = _T("������");
// 	else if (nType==2)
// 		str = _T("�ƻ�������");
// 
// 	CString	strShow;
// 
// 	if ( BKSafeConfig::GetHasRunDelete() )
// 		strShow.Format(_T("����������%s������ȫ������(����ɾ������)��ȷ��Ҫ������"),str);
// 	else
// 		strShow.Format(_T("����������%s������ȫ�����ġ�ȷ��Ҫ������"),str);
// 
// 	if ( CKuiMsgBox::Show(strShow, NULL, MB_YESNO|MB_ICONWARNING) != IDYES)
// 		return;
// 
// 	if (m_pRunOptEng)
// 	{
// 		m_nState = STATE_RUNOPT_CANCEL;
// 		m_pRunOptEng->RestoreRun(m_runList.GetShowType(),this);
// 		m_dlg->SetItemVisible(IDC_DIV_RUNOPT_BOTTOM,FALSE);
// 	}
}

void CUIHandlerOpt::EndScan()
{
	::PostMessage(m_dlg->m_hWnd,MSG_SYSOPT_RUN_SCAN_END,NULL,NULL);
}

void CUIHandlerOpt::RestoreEnd()
{
	::PostMessage(m_dlg->m_hWnd,MSG_SYSOPT_RUN_RESTORE_END,NULL,NULL);
}

LRESULT CUIHandlerOpt::OnWmScanEnd( UINT uMsg, WPARAM wParam, LPARAM lParam )
{

	m_nState = STATE_RUNOPT_NULL;
	m_runList.SetShowDlgState();

	if ( !m_bFirstScanRunEnd )
	{
		CString	strReport;
		for ( int i=0; i < m_runList.GetAllCount(); i++)
		{
			CRunOptListView::_RUN_ITEM_DATA* pdata = m_runList.GetRunDataByIndex(i);
			if (pdata && pdata->pInfo && !pdata->pInfo->bUnknown && !pdata->pInfo->bEnable )
			{
				CString	strX;
				strX.Format(_T("%d_"), pdata->pInfo->nID);
				strReport.Append(strX);

				if ( _tcslen(strReport) > MAX_PATH)
				{
// 					CString	strFormat;
// 					strFormat.Format(_T("http://stat.ijinshan.com/safe/runoptget.htm?ids=%s&ver=%s&pid=%s"),
// 						strReport,_Module.GetProductVersion(),CInstallStc::GetGlobalPtr()->GetPID()
// 						);

					//CStatistics::GetGlobalPtr()->Report(strFormat);
					strReport.Empty();
				}
			}
		}
		if (!strReport.IsEmpty())
		{
// 			CString	strFormat;
// 			strFormat.Format(_T("http://stat.ijinshan.com/safe/runoptget.htm?ids=%s&ver=%s&pid=%s"),
// 				strReport,_Module.GetProductVersion(),CInstallStc::GetGlobalPtr()->GetPID()
// 				);

			//CStatistics::GetGlobalPtr()->Report(strFormat);
			strReport.Empty();
		}

		m_bFirstScanRunEnd = TRUE;
	}

	/*
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ALL,FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ENABEL,TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_DISABLE,TRUE);

	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_SYSTEM,TRUE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_HIDE_SYSTEM,FALSE);

	*/
	m_dlg->SetItemVisible(IDC_DIV_RUNOPT_BOTTOM,TRUE);
	
	RefreshTabNumber();
	return S_OK;
}

LRESULT CUIHandlerOpt::OnWmRestoreEnd( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_dlg->SetItemVisible(IDC_DIV_RUNOPT_BOTTOM,TRUE);
	m_nState = STATE_RUNOPT_NULL;
	RefreshItemList();
	return S_OK;
}

LRESULT CUIHandlerOpt::OnWmFindItem( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	_FindRunItem((CKsafeRunInfo*)wParam);
//	RefreshTabNumber();
	return S_OK;
}

BOOL CUIHandlerOpt::FindRunItem( CKsafeRunInfo* pInfo )
{
	CKsafeRunInfo*	pNew = new CKsafeRunInfo(*pInfo);
	::PostMessage(m_dlg->m_hWnd,MSG_SYSOPT_RUN_SCAN_FIND,(WPARAM)pNew,NULL);
	return TRUE;
}


void CUIHandlerOpt::RefreshTabNumber(DWORD nCurTab)
{
	if (nCurTab==-1)
		nCurTab = m_dlg->GetTabCurSel(IDC_TAB_RUNOPT_TYPE);

	nCurTab++;

	CString	strfomat;
	DWORD	nShowCount = m_runList.GetShowCount();

	strfomat.Format(_T("������(%d/%d)"), 
		m_runList.GetEnableTypeCount(KSRUN_TYPE_STARTUP),
		m_runList.GetDefShowTypeCount(KSRUN_TYPE_STARTUP)
		);
	m_dlg->SetTabTitle(IDC_TAB_RUNOPT_TYPE,0,strfomat);

	strfomat.Format(_T("������(%d/%d)"), 
		m_runList.GetEnableTypeCount(KSRUN_TYPE_SERVICE, m_runList.IsShowSystem()),
		m_runList.GetDefShowTypeCount(KSRUN_TYPE_SERVICE, m_runList.IsShowSystem())
		);
	m_dlg->SetTabTitle(IDC_TAB_RUNOPT_TYPE,1,strfomat);

	strfomat.Format(_T("�ƻ�������(%d/%d)"), 
		m_runList.GetEnableTypeCount(KSRUN_TYPE_TASK),
		m_runList.GetDefShowTypeCount(KSRUN_TYPE_TASK)
		);

	m_dlg->SetTabTitle(IDC_TAB_RUNOPT_TYPE,2,strfomat);
}
BOOL CUIHandlerOpt::OnBkClrTopSelChange( int nTabItemIDOld, int nTabItemIDNew )
{
	m_n3TabType = nTabItemIDNew;
	RefreshCLRState();
	return TRUE;
}
BOOL CUIHandlerOpt::OnBkSysOptSelChange( int nTabItemIDOld, int nTabItemIDNew )
{
// 	if ( nTabItemIDNew == 0 )
// 		CSysOptStc::Instance().ReportTabPageSysOpt(SYSOPT_RPT_RUN, _Module.GetProductVersion() );
// 	else if ( nTabItemIDNew == 1 )
// 		CSysOptStc::Instance().ReportTabPageSysOpt(SYSOPT_RPT_RUB, _Module.GetProductVersion() );
// 	else if (nTabItemIDNew == 2 )
// 		CSysOptStc::Instance().ReportTabPageSysOpt(SYSOPT_RPT_MORE, _Module.GetProductVersion() );

// 	if (nTabItemIDNew>=1 && nTabItemIDNew<=3)
// 	{
// 		if ( CClearModHelper::GetPtr()->IsInstalled() )
// 		{
// 			CClearModHelper::GetPtr()->RunClearType(nTabItemIDNew, m_dlg->GetViewHWND());
// 			return (nTabItemIDOld>=1&&nTabItemIDOld<=3);
// 		}		
// 	}
	if (nTabItemIDNew == 2)
	{
		CString strPath = _Module.GetAppDirPath();
		strPath += _T("netmon.exe");
		ShellExecuteW(NULL, NULL, strPath, NULL, NULL, SW_SHOWNORMAL);
	}

	m_dlg->SetItemVisible(IDC_DIV_SYSOPT_RUN,nTabItemIDNew==0);
	m_dlg->SetItemVisible(IDC_DIV_SYSOPT_MORE,nTabItemIDNew==3);
	m_dlg->SetItemVisible(IDC_DIV_SYSOPT_CLR_HISTORY,FALSE);

	if (nTabItemIDNew==1)
	{
		m_n3TabType = 0;
		RefreshCLRState(nTabItemIDNew);
	}

	return TRUE;
}

LRESULT CUIHandlerOpt::OnWmREGChangeTop( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_dlg->SetItemStringAttribute(IDC_IMG_CLR_REG_TREETOP,"sub",(TCHAR*)wParam);
	m_dlg->SetItemText(IDC_TXT_CLR_REG_TREETOP,(TCHAR*)lParam);
	return S_OK;
}
LRESULT CUIHandlerOpt::OnWmRegScanFinish( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_dlg->SetItemVisible(IDC_DIV_CLR_REG_TREEDOWNBTN,TRUE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_REG_TREEDOWNBTNRESCAN,FALSE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_REG,FALSE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_REG,TRUE);
	m_dlg->SetItemVisible(IDC_IMG_CLR_REG_TREETOP,TRUE);
	if(m_hTimer != (HANDLE)-1)
	{
		TerminateThread(m_hTimer, NULL);
		m_hTimer = (HANDLE)-1;
	}

	m_dlg->EnableItem(IDC_BTN_CLR_LAJI_TREEDOWNBTN_SCAN, TRUE);
	m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, TRUE);

	m_dlg->SetItemVisible(IDC_IMG_CLR_REG_SCAN_TREETOP,FALSE);
	return S_OK;
}
LRESULT CUIHandlerOpt::OnWmHenjiScanFinish( UINT uMsg, WPARAM wParam, LPARAM lParam )
{

	if(m_hTimer != (HANDLE)-1)
	{
		TerminateThread(m_hTimer, NULL);
		m_hTimer = (HANDLE)-1;
	}
	m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTN,TRUE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTNRESCAN,FALSE);
    m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_GAOJI,FALSE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_GAOJI,TRUE);
	m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP,TRUE);
	m_dlg->SetItemVisible(IDC_TXT_CLR_TREEDOWN_DAFU, TRUE);
	m_dlg->EnableItem(IDC_TXT_CLR_TREEDOWN_DAFU, TRUE);
	m_dlg->EnableItem(IDC_CHECK_CLR_HENJI, TRUE);
	m_Tree.SetFocus();
	m_dlg->EnableItem(IDC_BTN_CLR_LAJI_TREEDOWNBTN_SCAN, TRUE);
	m_dlg->EnableItem(IDC_BTN_CLR_REG_TREEDOWNBTN_SCAN, TRUE);

	m_dlg->SetItemVisible(IDC_IMG_CLR_HENJI_SCAN_TREETOP,FALSE);
	return S_OK;
}

LRESULT CUIHandlerOpt::OnWmLAJIScanFinish( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_dlg->SetItemVisible(IDC_DIV_CLR_LAJI_TREEDOWNBTN,TRUE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_LAJI_TREEDOWNBTNRESCAN,FALSE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_LAJI,FALSE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_LAJI,TRUE);
	m_dlg->SetItemVisible(IDC_IMG_CLR_LAJI_TREETOP,TRUE);

	if(m_hTimer != (HANDLE)-1)
	{
		TerminateThread(m_hTimer, NULL);
		m_hTimer = (HANDLE)-1;
	}

	m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, TRUE);
	m_dlg->EnableItem(IDC_BTN_CLR_REG_TREEDOWNBTN_SCAN, TRUE);


	m_dlg->SetItemVisible(IDC_IMG_CLR_LAJI_SCAN_TREETOP,FALSE);
	return S_OK;
}

void CUIHandlerOpt::RebotUserTree()
{
	if(PathFileExists(m_CacheFile))
	{
		CAtlMap<CString, CString> TreeRegMap;
		LoadUserCache(TreeRegMap, L"kclear_Exit_checke_reg");
		CAtlMap<CString, CString> TreeLajiMap;
		LoadUserCache(TreeLajiMap, L"kclear_Exit_checke_laji");
		CAtlMap<CString, CString> TreeHenjiMap;
		LoadUserCache(TreeHenjiMap, L"kclear_Exit_checke_henji");

		POSITION pos;

		pos = m_TreeHenjiMap.GetStartPosition();
		while (pos!=NULL)
		{
			int n = m_TreeHenjiMap.GetKeyAt(pos);
			TreeInfo treeinfo = m_TreeHenjiMap.GetNextValue(pos);
			CString strClearid;
			strClearid.Format(L"%d", n);
			if(TreeHenjiMap.Lookup(strClearid)!=NULL)
			{
				m_TreeHenjiMap[n].iCheck = atoi(CW2A(TreeHenjiMap.Lookup(strClearid)->m_value));
				m_Tree.SetState(m_TreeHenjiMap[n].hItem, m_TreeHenjiMap[n].iCheck);
			}
		}
		m_Tree.Set2ItemState(m_Tree.GetRootItem());
	}
	else
	{
		WriteOneCache(m_TreeHenjiMap, &m_Tree, _T("kclear_checke_henji"));
	}
	if(m_Tree.IsAllSelect())
	{
		m_dlg->SetItemCheck(IDC_CHECK_CLR_HENJI, TRUE);
	}
	else
	{
		m_dlg->SetItemCheck(IDC_CHECK_CLR_HENJI, FALSE);
	}
	if(m_Tree.IsAllNoSelect())
	{
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, FALSE);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTNRESCAN, FALSE);
	}
	else
	{
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, TRUE);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTNRESCAN, TRUE);
	}
}

void CUIHandlerOpt::LoadUserCache(CAtlMap<CString, CString>& TreeMap, CString section, bool bOne)
{
		int nCount = 0;
		TCHAR szCount[MAX_PATH] = {L""};
		GetPrivateProfileString(section, L"count", L"0",szCount,sizeof(szCount)/sizeof(TCHAR),m_CacheFile);
		nCount = atoi(CW2A(szCount));
		for (int i=1;i<=nCount;i++)
		{
			CString strinfo, strcheck;
			strinfo.Format(L"iteminfo%d", i);
			strcheck.Format(L"itemcheck%d", i);
			TCHAR chKey[MAX_PATH] = {L""};
			TCHAR chcheck[MAX_PATH] = {L""};
			GetPrivateProfileString(section,strinfo,L"",chKey,sizeof(chKey)/sizeof(TCHAR),m_CacheFile);       
			GetPrivateProfileString(section,strcheck,L"",chcheck,sizeof(chcheck)/sizeof(TCHAR),m_CacheFile);       
			if(wcscmp(chKey, L"")!=0)
			{
				if(bOne)
				{
					CString strFormat;
					if(section == L"kclear_checke_reg")strFormat = L"3";
					else if(section == L"kclear_checke_henji")strFormat = L"1";
					else if(section == L"kclear_checke_laji")strFormat = L"2";
					strFormat += chKey;
					TreeMap.SetAt(strFormat, chcheck);
				}
				else
				{
					TreeMap.SetAt(chKey, chcheck);
				}
			}
		}
}
void CUIHandlerOpt::LoadUserCache(std::deque<CString>& arr, CString section, bool bOne)
{
	int nCount = 0;
	TCHAR szCount[MAX_PATH] = {L""};
	GetPrivateProfileString(section, L"count", L"0",szCount,sizeof(szCount)/sizeof(TCHAR),m_CacheFile);
	nCount = atoi(CW2A(szCount));
	for (int i=1;i<=nCount;i++)
	{
		CString strinfo, strcheck;
		strinfo.Format(L"iteminfo%d", i);
		strcheck.Format(L"itemcheck%d", i);
		TCHAR chKey[MAX_PATH] = {L""};
		TCHAR chcheck[MAX_PATH] = {L""};
		GetPrivateProfileString(section,strinfo,L"",chKey,sizeof(chKey)/sizeof(TCHAR),m_CacheFile);       
		GetPrivateProfileString(section,strcheck,L"",chcheck,sizeof(chcheck)/sizeof(TCHAR),m_CacheFile);       
		if(wcscmp(chKey, L"")!=0)
		{
			if(bOne)
			{
				CString strFormat;
				if(section == L"kclear_checke_reg")strFormat = L"3";
				else if(section == L"kclear_checke_henji")strFormat = L"1";
				else if(section == L"kclear_checke_laji")strFormat = L"2";
				strFormat += chKey;
				arr.push_back(strFormat);
			}
			else
			{
				arr.push_back(chKey);
			}
		}
	}
}

void CUIHandlerOpt::WriteOneCache(CAtlMap<int, TreeInfo>& TreeMap, CWH3StateCheckTreeCtrl10* Tree, CString strSection)
{
	WritePrivateProfileString(strSection, NULL, NULL, m_CacheFile);
	int j= 0;
	POSITION pos;
	pos = TreeMap.GetStartPosition();
	while (pos!=NULL)
	{
		//������µ�check
		int n = TreeMap.GetKeyAt(pos);
		TreeInfo treeinfo = TreeMap.GetNextValue(pos);
		if(Tree->GetCheckState(treeinfo.hItem))
		{
			TreeMap[n].iCheck = 2;
		}
		else
		{
			TreeMap[n].iCheck = 1;
		}
		//�������+sn
		CString strItemInfo;
		strItemInfo.Format(_T("%d"), n);
		//д����
		j++;
		CString strValueInfo,strValueCheck;
		strValueInfo.Format(_T("iteminfo%d"), j);
		strValueCheck.Format(_T("itemcheck%d"), j);
		CString strBuff;
		strBuff.Format(_T("%d"), TreeMap[n].iCheck);
		WritePrivateProfileString(strSection, strValueInfo, strItemInfo, m_CacheFile);
		WritePrivateProfileString(strSection, strValueCheck, strBuff, m_CacheFile);
	}
	CString strBuff;
	strBuff.Format(_T("%d"), j);
	WritePrivateProfileString(strSection, _T("count"), strBuff, m_CacheFile);

}

LRESULT CUIHandlerOpt::OnWmLAJILBtn( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	HTREEITEM hItem = (HTREEITEM)wParam;
	CString str;
	int n = str.Find(L"��");
	if(n>0)
	{
		str = str.Left(n);
	}

	if(m_Tree.IsAllSelect())
	{
		m_dlg->SetItemCheck(IDC_CHECK_CLR_HENJI, TRUE);
	}
	else 
	{
		m_dlg->SetItemCheck(IDC_CHECK_CLR_HENJI, FALSE);
	}
	if(m_Tree.IsAllNoSelect())
	{
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, FALSE);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTNRESCAN, FALSE);
	}
	else
	{
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, TRUE);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTNRESCAN, TRUE);
	}

	return TRUE;
}
void CUIHandlerOpt::OnClrHenjiAllSelect()
{
	//OutputDebugStringW(_T("OnClrHenjiAllSelect::1"));
	if(m_dlg->GetItemCheck(IDC_CHECK_CLR_HENJI))
	{

		m_Tree.SetItemCheck(m_Tree.GetRootItem(), 2);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, TRUE);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTNRESCAN, TRUE);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN_START, TRUE);
	}
	else
	{
		m_Tree.SetItemCheck(m_Tree.GetRootItem(), 1);
	}
}

LRESULT CUIHandlerOpt::OnWmHENJILBtn( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	//OutputDebugStringW(_T("OnWmHENJILBtn::1"));
	HTREEITEM hItem = (HTREEITEM)wParam;
	CString str;
	m_Tree.GetItemText(hItem, str);
	int n = str.Find(L"��");
	if(n>0)
	{
		str = str.Left(n);
	}

	if(m_Tree.IsAllSelect())
	{
		m_dlg->SetItemCheck(IDC_CHECK_CLR_HENJI, TRUE);
	}
	else 
	{
		m_dlg->SetItemCheck(IDC_CHECK_CLR_HENJI, FALSE);
	}
	if(m_Tree.IsAllNoSelect())
	{
	}
	else
	{
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, TRUE);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTNRESCAN, TRUE);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN_START, TRUE);
	}

	return TRUE;
}

LRESULT CUIHandlerOpt::OnWmlajiChangeTop( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_dlg->SetItemStringAttribute(IDC_IMG_CLR_LAJI_TREETOP,"sub",(TCHAR*)wParam);
	m_dlg->SetItemText(IDC_TXT_CLR_LAJI_TREETOP,(TCHAR*)lParam);
	return S_OK;
}
void CUIHandlerOpt::OnBkBtnWaitMore()
{
	::ShellExecute(NULL,_T("open"),_T("http://www.ijinshan.com/safe/optimize_advice.html?fr=client"),NULL,NULL,SW_SHOW);
}

void CUIHandlerOpt::OnBkRunOptTopMore()
{
	::ShellExecute(NULL,_T("open"),_T("http://www.ijinshan.com/safe/optimize_intro.html?fr=client"),NULL,NULL,SW_SHOW);
}

void CUIHandlerOpt::SetTopRunDiv( DWORD nType )
{
	m_dlg->SetItemVisible(IDC_DIV_RUNOPT_TOP_RUN,nType==0);
	m_dlg->SetItemVisible(IDC_DIV_RUNOPT_TOP_SERVICE,nType==1);
	m_dlg->SetItemVisible(IDC_DIV_RUNOPT_TOP_TASK,nType==2);
}

LRESULT CUIHandlerOpt::OnWmFirstIn( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	//CSysOptStc::Instance().ReportTabPageSysOpt(SYSOPT_RPT_RUN, _Module.GetProductVersion());

	InitEng();
	if (m_pRunOptEng==NULL)
	{
		CKuiMsgBox::Show( _T("��ʼ������ʧ�ܣ������°�װ�������"), NULL, MB_OK|MB_ICONWARNING);
		return S_OK;
	}
	m_nState = STATE_RUNOPT_SCAN;
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ALL,FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_ALL2,FALSE);
	m_dlg->EnableItem(IDC_LBL_RUNOPT_SHOW_SYSTEM,FALSE);
	m_runList.SetLoadShow();
	m_pRunOptEng->EnumRunInfo(0,this);

	return S_OK;
}

void CUIHandlerOpt::SecondShow()
{
// 	if ( CTrayRunCommon::GetPtr()->GetChange() )
// 	{
// 		RefreshItemList();
// 	}
}

void CUIHandlerOpt::PostRestoreRunItem( DWORD nType,BOOL bEnable,LPCTSTR lpName )
{
// 	if (IsOpTrayRunItem(nType,lpName))
// 	{
// 		CSafeMonitorTrayShell x;
// 		x.SetAllMonitorRun(bEnable);
// 	}
}

void CUIHandlerOpt::OnBtnAutoOpt()
{
// 	if (!IsOpPermit())
// 		return;
// 
// 	BOOL	bRefresh = FALSE;
// 	if (m_pRunOptEng)
// 	{
// 		CSimpleArray<CKsafeRunInfo*> arrayx;
// 		m_runList.GetCKSRunInfoArray(arrayx);
// 
// 		CRunAutoOptDlg*	pDlg = new CRunAutoOptDlg(m_pRunOptEng,arrayx );
// 		bRefresh = (pDlg->DoModal()==IDOK);
// 		delete pDlg;
// 	}
// 	if (bRefresh)
// 		RefreshItemList();
}

BOOL CUIHandlerOpt::OnDeleteItem( CKsafeRunInfo* pInfo )
{
	CKuiMsgBox	msg;
	CString			strMsg;
	BOOL			bNoNotify = FALSE;//BKSafeConfig::GetNoTipRunDelete();

	strMsg.Format(_T("%s ��ɾ���󣬲��ָܻ���ȷ��ɾ����"), pInfo->strDisplay);
	msg.AddButton(_T("ȷ��"), IDYES);
	msg.AddButton(_T("ȡ��"), IDCANCEL);

	if ( !bNoNotify )
	{
		if ( msg.ShowMsg(strMsg,NULL,MB_YESNO|MB_ICONWARNING,&bNoNotify) != IDYES )
			return FALSE;
		//BKSafeConfig::SetNoTipRunDelete(bNoNotify);
	}

	BOOL bRes = m_pRunOptEng->DeleteRun(pInfo);

	if (bRes)
	{
		if ( pInfo->nType == KSRUN_TYPE_STARTUP && IsOpTrayRunItem(pInfo->nRegType,pInfo->strName) )
		{
// 			CSafeMonitorTrayShell x;
// 			x.SetAllMonitorRun(pInfo->bEnable);
		}
		m_runList.DeleteItemByKSInfo(pInfo);
		m_runList.InvalidateRect(NULL);
		RefreshTabNumber();

		if (m_runList.XBASE_GetItemCount() == 0)
		{
			m_runList.SetShowDlgState();
		}

		//BKSafeConfig::SetHasRunDelete(TRUE);
	}
	else
	{
		CKuiMsgBox::Show(_T("���������ɾ��ʧ�ܣ������Ǳ������������簲ȫ�������ֹ��"),NULL,MB_OK|MB_ICONWARNING);
	}

	return bRes;
}

BOOL CUIHandlerOpt::OnClickLabel( DWORD nIndex, CKsafeRunInfo* pInfo )
{
	if (nIndex==CLICK_INDEX_ENABLE)
		return OnClickButton(pInfo);
	else if (nIndex==CLICK_INDEX_DELETE)
		return OnDeleteItem(pInfo);
	else if (nIndex==CLICK_INDEX_OPEN_FOLDER)
	{
		CString	strFilePath(pInfo->strExePath);
		CString	strParam = _T("/select,\"") + strFilePath + _T("\"");
		::ShellExecute( m_runList.m_hWnd, _T("open"), _T("explorer.exe"), 
			strParam, NULL, SW_SHOW);	
	}
	return FALSE;
}
bool CUIHandlerOpt::IsCheckCache(CString section)
{
	int nCount = 0;
	TCHAR szCount[MAX_PATH] = {L""};
	GetPrivateProfileString(section, L"count", L"0",szCount,sizeof(szCount)/sizeof(TCHAR),m_CacheFile);
	nCount = atoi(CW2A(szCount));
	for (int i=1;i<=nCount;i++)
	{
		CString strinfo, strcheck;
		strcheck.Format(L"itemcheck%d", i);
		TCHAR chcheck[MAX_PATH] = {L""};
		GetPrivateProfileString(section,strcheck,L"",chcheck,sizeof(chcheck)/sizeof(TCHAR),m_CacheFile);       
		strcheck.Format(L"%s", chcheck);
		if(strcheck == "2") return true;
	}
	return false;
}
void CUIHandlerOpt::SetOneState(CAtlMap<CString, CString>& OneMap,std::deque<CString>& arr, CString strTypeid)
{
	for (int i=0;i<m_arrClearInfo.GetSize();i++)
	{
		if(m_arrClearInfo[i].strTypeid.Left(1)==strTypeid)
		{
			if(m_arrClearInfo[i].strClearid.GetLength()==0)continue;
			CString strFormat = strTypeid;
			strFormat += m_arrClearInfo[i].strClearid;

			if(OneMap.Lookup(strFormat)==NULL)
			{
				CString strcheck;
				strcheck.Format(L"%d", m_arrClearInfo[i].nCheck+1);
				OneMap.SetAt(strFormat, strcheck);

				arr.push_back(strFormat);
			}
		}
	}
}

void CUIHandlerOpt::OnOneScan()
{
	
	m_OneScanFinish.RemoveAll();
	CAtlMap<CString, CString> OneMap;
	std::deque<CString> arr;
	LoadUserCache(OneMap,"kclear_checke_reg",true);
	LoadUserCache(OneMap,"kclear_checke_henji",true);
	LoadUserCache(OneMap,"kclear_checke_laji",true);
	LoadUserCache(arr,"kclear_checke_reg",true);
	LoadUserCache(arr,"kclear_checke_henji",true);
	LoadUserCache(arr,"kclear_checke_laji",true);

	//�ж��Ƿ�Ϊ��
	bool bretKong =false;
	if(OneMap.GetCount() == 0)
	{
		bretKong  = true;
	}
 	POSITION posii;int nKong = 0;
 	posii = OneMap.GetStartPosition();
 	while (posii!=NULL)
	{
		CString strCheck = OneMap.GetValueAt(posii);
		if(strCheck == "2") nKong ++;
		OneMap.GetNext(posii);
	}
	if(nKong == 0 || bretKong)
	{
		OneMap.RemoveAll();
		arr.clear();
		//��		
		SetOneState(OneMap, arr, "1");
		SetOneState(OneMap, arr, "2");
		SetOneState(OneMap, arr, "3");
	}

	sort(arr.begin(), arr.end());

	m_OneMap.RemoveAll();
	m_OneTypeMap.RemoveAll();
	int key[100] = {0};
	SCANPATH scanpath[100];
	FILEEXTS fileext[100];
	memset(scanpath, 0, sizeof SCANPATH*100);
	memset(fileext, 0, sizeof FILEEXTS*100);

	int ii=0;
	int k=0;

	int n = 0;
	for (std::deque<CString>::iterator p = arr.begin();p!=arr.end();p++)
// 	POSITION pos;
// 	pos = OneMap.GetStartPosition();
// 	while (pos!=NULL)
	{
		//CString strClearid = OneMap.GetKeyAt(pos);
		CString strClearid = *p;
		CString strCheck = OneMap.Lookup(strClearid)->m_value;
		strClearid.Delete(0, 1);

		if(strCheck == "2") 
		{
			for (int i=0; i<m_arrClearInfo.GetSize();i++)
			{
				if(m_arrClearInfo[i].strClearid == strClearid)
				{
					bool bret = false;
					for (int j=0;j<m_arrClearType.GetSize();j++)
					{
						if(m_arrClearType[j].strTypeid == m_arrClearInfo[i].strTypeid)
						{
							CString str123 = m_arrClearType[j].strTypeid;
							if(m_OneTypeMap.Lookup(strClearid)!=NULL)
							{
								continue;
							}
							m_OneTypeMap.SetAt(strClearid, m_arrClearInfo[i].strTypeid);

							int nn = atoi(CW2A(strClearid));

							if(nn>21000)//����ͨ���
							{
								CString strext = m_arrClearInfo[i].strExtName;
								int j = strext.Find(_T(";"));
								while (j>0)
								{
									fileext[k].iType = nn;
									wcscpy(fileext[k].szFileExts , strext.Left(j));
									k++;

									strext.Delete(0, j+1);
									j = strext.Find(_T(";"));
								}
								scanpath[0].iType = 0;
								wcscpy(scanpath[0].szScanFile , _T("c:\\"));
							}
							else
							{
								CString str123321;
								str123321.Format(L"����%d", nn);
								//OutputDebugStringW(str123321);

								key[ii] = nn;
								ii++;
							}
							if(m_OneMap.Lookup(m_arrClearInfo[i].strTypeid)!=NULL)
							{
								//���������2���ڵ�����
								m_OneMap[m_arrClearInfo[i].strTypeid].dwJianceNum++;
								m_OneMap[m_arrClearInfo[i].strTypeid].strExtName += m_arrClearInfo[i].strExtName;
								bret = true;
								break;
							}
							OneTy onety;
							onety.nItem = n;
							onety.strClearname = m_arrClearType[j].strTypeName;
							onety.strState = L"�ȴ�����...";
							onety.strClearInfo = L"0KB �ļ�������0";
							onety.strExtName = m_arrClearInfo[i].strExtName;
							onety.dwFileNum = 0;
							onety.dwFilesize = 0;
							onety.dwJiancedNum=0;
							onety.dwJianceNum=1;
							onety.strClear2name = m_arrClearInfo[i].strClearName;
							m_OneMap.SetAt(m_arrClearInfo[i].strTypeid, onety);
							n++;
							bret = true;
							break;
						}
					}
					if(bret)break;
				}
			}
		}
	}
	m_wndListCtrl.SetItemCount((int)m_OneMap.GetCount());

	//�б�����
 	POSITION pos;
 	pos = m_OneMap.GetStartPosition();
 	while (pos!=NULL)
	{
		int nItem = m_OneMap.GetValueAt(pos).nItem;
		if(nItem == n-1)
		{
			if(m_OneMap.Lookup(L"202")==NULL)break;
			nItem = m_OneMap.Lookup(L"202")->m_value.nItem;
			m_OneMap.Lookup(L"202")->m_value.nItem = n-1;
			m_OneMap.GetValueAt(pos).nItem = nItem;
			break;			
		}
		m_OneMap.GetNext(pos);
	}


	//��ʾ����
	int yy=0;int nte1=-1,nte2=-1,nte3=-1;
	for (;yy<ii;yy++)
	{
		if(key[yy] == 3014)nte1 = yy;
		if(key[yy] == 3012)nte2 = yy;
		if(key[yy] == 3002)nte3 = yy;
	}
	if(nte1!=-1||nte2!=-1||nte3!=-1)
	{
		if(nte1 != -1)
		{
			if(nte2 != -1)
			{
				if(nte3 != -1)
				{
					key[nte1] = key[ii-3];
					key[nte2] = key[ii-2];
					key[nte3] = key[ii-1];
					key[ii-3] = 3014;
					key[ii-2] = 3012;
					key[ii-1] = 3002;
				}
				else
				{
					key[nte1] = key[ii-2];
					key[nte2] = key[ii-1];
					key[ii-2] = 3014;
					key[ii-1] = 3012;
				}
			}
			else
			{
				if(nte3 != -1)
				{
					key[nte1] = key[ii-2];
					key[nte3] = key[ii-1];
					key[ii-2] = 3014;
					key[ii-1] = 3002;
				}
				else
				{
					key[nte1] = key[ii-1];
					key[ii-1] = 3014;
				}

			}
		}
		else
		{
			if(nte2 != -1)
			{
				if(nte3 != -1)
				{
					key[nte2] = key[ii-2];
					key[nte3] = key[ii-1];
					key[ii-2] = 3012;
					key[ii-1] = 3002;
				}
				else
				{
					key[nte2] = key[ii-1];
					key[ii-1] = 3012;
				}
			}
			else
			{
				if(nte3 != -1)
				{
					key[nte3] = key[ii-1];
					key[ii-1] = 3002;
				}
			}
		}
	}
	try
	{ 

		if(m_pCleanPrc!=NULL)
		{
			if(k>0)m_nProgress = ii+1;
			else m_nProgress = ii;
			if(k>0)
			{
				GARBAINFO m_garbInfo;
				m_garbInfo.iExitsCount = k;
				m_garbInfo.iPathCount = 1;
				m_garbInfo.pFileExts = fileext;
				m_garbInfo.pScanPath = scanpath;
				m_bScanBage = true;
				for (int uui=0;uui<k;uui++)
				{
					CString str;
					str.Format(L"%s", fileext[uui].szFileExts);
					
				}
                if (m_pCleanPrc != NULL)
                {
				    m_pCleanPrc->DZ_IsScanClean(TRUE);
				    m_pCleanPrc->DZ_StartScanBage(&m_garbInfo);
			    }
            }
			if(ii>0)
			{
                if (m_pCleanPrc != NULL)
                {
				    m_pCleanPrc->DZ_IsScanClean(TRUE);
				    m_pCleanPrc->DZ_StartScan(key,ii);
                }
			}
			else
			{
				if(k==0)
				{
					//OutputDebugStringW(_T("ScanlajiProc::ɨ�����"));
					m_dlg->SetItemVisible(IDC_DIV_CLR_LAJI_TREEDOWNBTN,TRUE);
					m_dlg->SetItemVisible(IDC_DIV_CLR_LAJI_TREEDOWNBTNRESCAN,FALSE);
//					m_TreeLaji.SetScanState(false);
				}
			}
		}
	}
	catch (...)
	{
		//OutputDebugStringW(_T("ScanlajiProc::ɨ�����"));
	}
}
unsigned CUIHandlerOpt::ScanOneProc(LPVOID lpVoid)
{
	CUIHandlerOpt *pDlg = (CUIHandlerOpt*)lpVoid;

	pDlg->OnOneScan();
	return TRUE;
}
unsigned CUIHandlerOpt::ScanOnTimer(LPVOID lpVoid)
{
	CUIHandlerOpt *pDlg = (CUIHandlerOpt*)lpVoid;

	while (1)
	{
		Sleep(200);
		static int s_nAni = 0;
		pDlg->m_dlg->SetItemIntAttribute(IDC_IMG_CLR_SCANING, "sub", (s_nAni ++) % 5);
	}
	return TRUE;
}
unsigned CUIHandlerOpt::ScanTreeOnTimer(LPVOID lpVoid)
{
	CUIHandlerOpt *pDlg = (CUIHandlerOpt*)lpVoid;

	while (1)
	{
		Sleep(100);
// 		static int nPos = 0;
// 		switch(pDlg->m_n3TabType)
// 		{
// 		case 1:
// 			{
	/*			pDlg->m_dlg->SetItemIntAttribute(IDC_IMG_CLR_TREETOP2, "sub", (pDlg->m_nPos % 8));
				pDlg->m_nPos++;*/
				::SendMessage(pDlg->m_dlg->m_hWnd, MSG_CLR_TREE_SCANING, (WPARAM)0, (LPARAM)pDlg->m_n3TabType);
// 				pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_HENJI_SCAN_TREETOP, FALSE);
// 				pDlg->m_dlg->SetItemIntAttribute(IDC_IMG_CLR_HENJI_SCAN_TREETOP, "sub", (++nPos)%8);
// 				pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_HENJI_SCAN_TREETOP, TRUE);
// 			}
// 			break;
// 		case 2:
// 			{
// 				::SendMessage(pDlg->m_dlg->m_hWnd, , (WPARAM)0, (LPARAM)pDlg->m_n3TabType)
// 				pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_LAJI_SCAN_TREETOP, FALSE);
// 				pDlg->m_dlg->SetItemIntAttribute(IDC_IMG_CLR_HENJI_SCAN_TREETOP, "sub", (++nPos)%8);
// 				pDlg->m_dlg->SetItemIntAttribute(IDC_IMG_CLR_LAJI_SCAN_TREETOP, "sub", (++nPos)%8);
// 				pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_LAJI_SCAN_TREETOP, TRUE);
// 			}
// 			break;
// 		case 3:
// 			{
// 				::SendMessage(pDlg->m_dlg->m_hWnd, , (WPARAM)0, (LPARAM)pDlg->m_n3TabType)
// 				pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_REG_SCAN_TREETOP, FALSE);
// 				pDlg->m_dlg->SetItemIntAttribute(IDC_IMG_CLR_HENJI_SCAN_TREETOP, "sub", (++nPos)%8);
// 				pDlg->m_dlg->SetItemIntAttribute(IDC_IMG_CLR_LAJI_SCAN_TREETOP, "sub", (++nPos)%8);
// 				pDlg->m_dlg->SetItemIntAttribute(IDC_IMG_CLR_REG_SCAN_TREETOP, "sub", (++nPos)%8);
// 				pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_REG_SCAN_TREETOP, TRUE);
// 			}
// 			break;
// 		}
	}
	return TRUE;
}

LRESULT CUIHandlerOpt::OnWmChangeTop( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if (m_Tree.GetScanState())
	{
		m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP, FALSE);
		m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, TRUE);
	}
	else
	{
		m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP, TRUE);
		m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);
	}
	if (m_bStopScan)
	{
		m_dlg->SetItemText(IDC_TXT_CLR_TREETOP,L"");
		m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);
		m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP, TRUE);
		m_dlg->SetItemIntAttribute(IDC_IMG_CLR_TREETOP, "pos", 1);
	}
	m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP, TRUE);
	m_dlg->SetItemStringAttribute(IDC_IMG_CLR_TREETOP,"sub",(TCHAR*)wParam);
	m_dlg->SetItemText(IDC_TXT_CLR_TREETOP,(TCHAR*)lParam);
	return S_OK;
}

LRESULT CUIHandlerOpt::OnWmChangeTop2( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
//	m_dlg->SetItemIntAttribute(IDC_IMG_CLR_TREETOP2,"sub",(m_nPos % 10));

	if (m_bStopScan)
	{
		m_dlg->SetItemText(IDC_TXT_CLR_TREETOP,L"");
		m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);
		m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP, TRUE);
		m_dlg->SetItemIntAttribute(IDC_IMG_CLR_TREETOP, "pos", 1);
	}
	else
	{
		m_dlg->SetItemText(IDC_TXT_CLR_TREETOP,(TCHAR*)lParam);
	}
	return S_OK;
}

LRESULT CUIHandlerOpt::OnWmChangeTop3( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_dlg->SetItemText(IDC_TXT_CLR_TREETOP2,(TCHAR*)lParam);
	return S_OK;
}

LRESULT CUIHandlerOpt::OnWmChangeTopEx1( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	//	m_dlg->SetItemIntAttribute(IDC_IMG_CLR_TREETOP2,"sub",(m_nPos % 10));
	m_Tree.SelectSetFirstVisible(m_RootTree);
	m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX1,(TCHAR*)lParam);
	return S_OK;
}
LRESULT CUIHandlerOpt::OnWmChangeTopEx2( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	//	m_dlg->SetItemIntAttribute(IDC_IMG_CLR_TREETOP2,"sub",(m_nPos % 10));
//	m_dlg->SetItemColorAttribute(IDC_TXT_CLR_HENJI_SHOW_EX2,NULL, RGB(255, 0, 0));
	m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX2,(TCHAR*)lParam);
	return S_OK;
}

LRESULT CUIHandlerOpt::OnWmChangeTopEx3( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	//	m_dlg->SetItemIntAttribute(IDC_IMG_CLR_TREETOP2,"sub",(m_nPos % 10));

	m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX3,(TCHAR*)lParam);
	return S_OK;
}

void CUIHandlerOpt::OnBkClrDafaul()
{
	//OutputDebugStringW(_T("OnBkClrDafaul::1"));
	SetCheckTree(m_TreeHenjiMap, "1", &m_Tree);
//	WriteOneCache(m_TreeHenjiMap, &m_Tree, _T("kclear_checke_henji"));
	SendMessage(m_dlg->m_hWnd, MSG_CLR_HENJI_TREELUP, 0, 0);

}

void CUIHandlerOpt::OnBkClrOne()
{
	//OutputDebugStringW(_T("OnBkClrOne::1"));
	CKuiMsgBox	msg;
	CString			strMsg;
	msg.AddButton(_T("ȷ��"), IDYES);
	msg.AddButton(_T("ȡ��"), IDCANCEL);
	if(m_Tree.IsAllNoSelect())
	{
		if(IsCheckCache("kclear_checke_laji") || IsCheckCache("kclear_checke_henji"))
		{
			strMsg.Format(_T("\n\n�ѽ���������������ӡ�һ�����������Ƴ���"));
			msg.ShowMsg(strMsg,NULL,MB_OK);
		}
		else
		{
			strMsg.Format(_T("��������������������Ƴ�����һ���������������\n\n��������������������Ƽ�������"));
			msg.ShowMsg(strMsg,NULL,MB_OK|MB_ICONWARNING);

			SetCheckTree(m_TreeHenjiMap, "1", &m_Tree);
			SendMessage(m_dlg->m_hWnd,MSG_CLR_HENJI_TREELUP, 0, 0);

			return ;
		}
	}
	else
	{	
		strMsg.Format(_T("\n\n�ѽ���ǰѡ������롰һ�������У�"));
		msg.ShowMsg(strMsg,NULL,MB_OK);
	}
	WriteOneCache(m_TreeHenjiMap, &m_Tree, _T("kclear_checke_henji"));
}

unsigned CUIHandlerOpt::CleanProc(LPVOID lpVoid)
{
	CUIHandlerOpt *pDlg = (CUIHandlerOpt*)lpVoid;

	int n = (int)pDlg->m_arrClear.GetCount();
	FileInfo *fileinfo = new FileInfo[n+1];
	memset(fileinfo, 0, sizeof FileInfo*n);
	RegInfo *reginfo = new RegInfo[n+1];
	memset(reginfo, 0, sizeof RegInfo*n);

	int k=0;
	int kk=0;
	pDlg->m_nCleanNum = 0;
	if(pDlg->m_pCleanPrc!=NULL)
	{

		for (int i = 0; i < (int)pDlg->m_arrClear.GetCount(); i++)
		{
			if(pDlg->m_arrClear[i].nType == 1)
			{
				reginfo[k].iType = pDlg->m_arrClear[i].iType;
				wcscpy(reginfo[k].szKeyFullPath, pDlg->m_arrClear[i].strReg);
				wcscpy(reginfo[k].szValueName, pDlg->m_arrClear[i].strValue);
				k++;
			}
			else if(pDlg->m_arrClear[i].nType == 2 || pDlg->m_arrClear[i].nType == 3)
			{
				fileinfo[kk].iType = pDlg->m_arrClear[i].iType;
				wcscpy(fileinfo[kk].szFileFullPath, pDlg->m_arrClear[i].strReg);
				kk++;
			}
		}
		if(k>0)pDlg->m_nCleanNum++;
		if(kk>0)pDlg->m_nCleanNum++;
        if (pDlg->m_pCleanPrc != NULL)
        {
            if(k>0){pDlg->m_pCleanPrc->DZ_CleanReg(reginfo, k);}
	        if(kk>0){pDlg->m_pCleanPrc->DZ_CleanFile(fileinfo, kk);}	 
	    }
    }

	delete []reginfo;
	delete []fileinfo;

	return TRUE;
}
unsigned CUIHandlerOpt::ScanProc(LPVOID lpVoid)
{
	CUIHandlerOpt *pDlg = (CUIHandlerOpt*)lpVoid;

	int nArrey = (int)pDlg->m_TreeHenjiMap.GetCount(); 
	int key[100] = {0};
	int i=0;
	pDlg->m_Tree.SetScanState(true);
	std::deque<int> arr;
	pDlg->m_finishScanId.RemoveAll();
	try
	{
		if(pDlg->m_pCleanPrc!=NULL)
		{
			POSITION pos;
			pos = pDlg->m_TreeHenjiMap.GetStartPosition();
			while (pos!=NULL)
			{
				int n = pDlg->m_TreeHenjiMap.GetKeyAt(pos);
				TreeInfo treeinfo = pDlg->m_TreeHenjiMap.GetNextValue(pos);
				if(treeinfo.iCheck == 2)
				{
					CString str;
					str.Format(_T("%d"), n);
					arr.push_back(treeinfo.nType*100+treeinfo.nSn);
				}
				else if (pDlg->m_Tree.GetCheckStateEx(treeinfo.hItem))
				{
					arr.push_back(treeinfo.nType*100+treeinfo.nSn);
				}
			}

			sort(arr.begin(), arr.end());
			for (std::deque<int>::iterator p = arr.begin();p!=arr.end();p++)
			{
				POSITION pos;
				pos = pDlg->m_TreeHenjiMap.GetStartPosition();
				while (pos!=NULL)
				{
					int n = pDlg->m_TreeHenjiMap.GetKeyAt(pos);
					TreeInfo treeinfo = pDlg->m_TreeHenjiMap.GetNextValue(pos);
					if(*p == treeinfo.nType*100+treeinfo.nSn)
					{
						CString str;
						str.Format(_T("����%d,%d, %d, %d, %s"), n, *p, treeinfo.nType, treeinfo.nSn, treeinfo.strItemInfo);
						//OutputDebugStringW(str);

						pDlg->m_finishScanId.Add(n);
						key[i] = n;
						i++;
						break;
					}
				}
			}
			//��ʾ����
			int yy=0;
			for (;yy<i;yy++)
			{
				/*if(key[yy] == 2008)break;*/
			}
			if(yy<i)
			{
				/*key[yy] = key[i-1];
				key[i-1] = 2008;*/
			}


			if(i>0)
            {
                if (pDlg->m_pCleanPrc != NULL)
                    pDlg->m_pCleanPrc->DZ_StartScan(key,i);
            }
            else
			{
				//OutputDebugStringW(_T("ScanREGProc::ɨ�����"));
				pDlg->m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTN,TRUE);
				pDlg->m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTNRESCAN,FALSE);
				pDlg->m_Tree.SetScanState(false);
				pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);
				pDlg->m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP, TRUE);
			}
		}
	}
	catch (...)
	{
		//OutputDebugStringW(_T("ScanProc::ɨ�����"));
	}

// 	pDlg->m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTN,TRUE);
// 	pDlg->m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTNRESCAN,FALSE);
// 	pDlg->m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, TRUE);
	return TRUE;
}

void CUIHandlerOpt::OnBkClrScan()
{
	if(m_bOneScan||m_Tree.GetScanState()/*||m_TreeReg.GetScanState()||m_TreeLaji.GetScanState()*/)
	{
// 		CKuiMsgBox	msg;
// 		CString			strMsg;
// 		strMsg.Format(_T("\n���ڽ���ϵͳ�������Ե�..."));
// 		msg.AddButton(_T("ȷ��"), IDYES);
// 		msg.AddButton(_T("ȡ��"), IDCANCEL);
// 
// 		msg.ShowMsg(strMsg,NULL,MB_OK|MB_ICONWARNING);
		return ;
	}
	m_bStopScan = FALSE;
	if (m_Tree.IsAllNoSelect())
	{
		CKuiMsgBox msgbox;
		CString str;
		str.Format(_T("\n����δѡ����Ҫɨ�����Ŀ������ѡ��Ȼ�����ɨ�裡"));

		msgbox.ShowMsg(str,NULL,MB_OK|MB_ICONINFORMATION);
		return ;
	}

	//m_nScanCount++;

	m_hTimer = (HANDLE)_beginthreadex(NULL, 0, ScanTreeOnTimer, this, 0, NULL);
	m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP,FALSE);
// 	m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2,TRUE);
// 	m_dlg->SetItemVisible(IDC_IMG_CLR_HENJI_SCAN_TREETOP, TRUE);
	m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTN_SCAN_START, FALSE);
	m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN_START, FALSE);


	m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTN_CLEAN1, FALSE);
	m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTNRESCAN, TRUE);
	m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTNRESCAN, TRUE);
	//RECT rc={0};
	//m_dlg->GetItemRect(IDC_BTN_CLR_TREEDOWNBTN_SCAN, rc);

	m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTN,FALSE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTNRESCAN,TRUE);
	m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, TRUE);
	m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, FALSE);
	m_dlg->SetItemVisible(IDC_BTN_CLR_TREEDOWNBTN_CLEAN1, TRUE);
	m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN1, FALSE);
	m_dlg->SetItemText(IDC_BTN_CLR_TREEDOWNBTN_SCAN,_T("����ɨ��"));
	m_dlg->EnableItem(IDC_TXT_CLR_TREEDOWN_DAFU, FALSE);
	m_dlg->EnableItem(IDC_CHECK_CLR_HENJI, FALSE);

	m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX1, L"");
	m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX2, L"");
	m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX3, L"");
	m_dlg->SetItemText(IDC_TXT_CLR_TREETOP2, L"");


	m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX1, FALSE);
	m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX2, FALSE);
	m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX3, FALSE);
	m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2,FALSE);


	m_arrScanHenji.RemoveAll();
	m_nScanHenjiiType= 0;
	m_Tree.SetScanState(true);
	GetCheckReg(m_TreeHenjiMap, &m_Tree);

	//ͨ���
	m_dwAllFileSize = 0;


	static bool nFirst= false;
	if(nFirst)ResearchReg(m_TreeHenjiMap, &m_Tree);
	nFirst = true;

	

	m_hScan = (HANDLE)_beginthreadex(NULL, 0, ScanProc, this, 0, NULL);
}
void CUIHandlerOpt::OnBkClrClean()
{
	m_Tree.SetScanState(true);
	GetCheckReg(m_TreeHenjiMap, &m_Tree);

	m_dwAllFileSize = 0;
	m_arrClear.RemoveAll();
	m_amap.RemoveAll();
	for (int i=0;i<m_arrScanHenji.GetSize();i++)
	{
		CString strItem1;
		CString strItem;
		if(m_Tree.GetCheckState(m_arrScanHenji[i].hSubItem))
		{
			if(m_amap.Lookup(m_arrScanHenji[i].hItem)==NULL)
			{
//				m_Tree.Expand(m_arrScanHenji[i].hItem,TVE_COLLAPSE);
				m_amap.SetAt(m_arrScanHenji[i].hItem, m_arrScanHenji[i].strParent);
			}
			TreeClear treeclear;
			treeclear.iType = m_arrScanHenji[i].iType;
			treeclear.strReg= m_arrScanHenji[i].strReg;
			treeclear.strValue=m_arrScanHenji[i].strValue;
			treeclear.nType = m_arrScanHenji[i].nType;
			if (treeclear.nType == 4)
			{
				continue;
			}
			m_arrClear.Add(treeclear);
		} 
	}

	for (int n = 0; n < (int)m_arrClear.GetCount(); n++)
	{
		if (m_arrClear[n].iType == 9038 || 
			m_arrClear[n].iType == 9044 ||
			m_arrClear[n].iType == 9037)
		{
			CKuiMsgBox	msg;
			CString			strMsg;
			strMsg.Format(_T("��������п��ܽ������б����ͣ�������\n\n��ȷ�����������б���"));

			UINT_PTR up = msg.ShowMsg(strMsg,NULL,MB_YESNO|MB_ICONINFORMATION);

			if (up == IDNO)
			{
				m_Tree.SetScanState(false);
				GetCheckReg(m_TreeHenjiMap,&m_Tree,true);
				m_Tree.Set2ItemState(m_Tree.GetRootItem());
				m_Tree.ResetItemState(m_Tree.GetRootItem());
				::SendMessage(m_dlg->m_hWnd, MSG_CLR_HENJI_CLEAR_fINISH, (LPARAM)0, (WPARAM)0);
				return;
			}
			else
				break;
		}
	}

	int nCleanCount = (int)m_arrClear.GetCount();
	if (nCleanCount <= 0)
	{
		if (m_Tree.IsAllNoSelect())
		{
			CKuiMsgBox	msg;
			CString			strMsg;
			msg.AddButton(_T("ȡ��"), IDCANCEL);
			strMsg.Format(_T("\n����δѡ����Ҫ�������Ŀ������ѡ��Ȼ��������"));

			msg.ShowMsg(strMsg,NULL,MB_OK|MB_ICONINFORMATION);
		}
		else if (IsIncludeNoScanItem())
		{
			CKuiMsgBox	msg;
			CString			strMsg;
			strMsg.Format(_T("\n��ѡ�����Ŀ�д���δɨ�����Ŀ����������ɨ�裬�ٽ�������"));

			msg.ShowMsg(strMsg,NULL,MB_OK|MB_ICONINFORMATION);
		}
		else if (IsAllNeedRebootDeleteEx())
		{
			CKuiMsgBox	msg;
			CString			strMsg;
			strMsg.Format(_T("\n ��ѡ��Ŀ��������ɣ��ļ�����������ɾ����"));

			msg.ShowMsg(strMsg,NULL,MB_OK|MB_ICONINFORMATION);
		}
		else
		{
			if (IsNoCleanEmpty())
			{
				goto _exit_;
			}
			CKuiMsgBox	msg;
			CString			strMsg;
			strMsg.Format(_T("\n��ѡ�е���Ŀ��ȫ��������ɣ���ѡ��������Ŀ��Ȼ������ɨ�裡"));

			msg.ShowMsg(strMsg,NULL,MB_OK|MB_ICONINFORMATION);
		}
_exit_:
		for (int i=m_arrScanHenji.GetSize()-1;i>=0;i--)
		{
			if(m_Tree.GetCheckState(m_arrScanHenji[i].hSubItem))
			{

				if(m_arrScanHenji[i].iType == 6001 || m_arrScanHenji[i].iType == 6002 || m_arrScanHenji[i].iType == 1005 ||
					m_arrScanHenji[i].iType == 6007 || m_arrScanHenji[i].iType == 6008 || m_arrScanHenji[i].iType == 2029 ||
					m_arrScanHenji[i].iType == 2030 || m_arrScanHenji[i].iType == 6011 || m_arrScanHenji[i].iType == 6012 ||
					m_arrScanHenji[i].iType == 6013 || m_arrScanHenji[i].iType == 6014 || m_arrScanHenji[i].iType == 6015 ||
					m_arrScanHenji[i].iType == 6016 )
				{continue;}
				m_Tree.SetState(m_arrScanHenji[i].hItem, 2);
				m_Tree.DeleteItem(m_arrScanHenji[i].hSubItem);
				m_arrScanHenji.RemoveAt(i);
			}
		}
///////////////////////////////////////////////////////////////
		m_Tree.SetScanState(false);
		GetCheckReg(m_TreeHenjiMap,&m_Tree,true);
		m_Tree.Set2ItemState(m_Tree.GetRootItem());
		m_Tree.ResetItemState(m_Tree.GetRootItem());
		::SendMessage(m_dlg->m_hWnd, MSG_CLR_HENJI_CLEAR_fINISH, (LPARAM)0, (WPARAM)0);
		return;
	}

	for (int i=m_arrScanHenji.GetSize()-1;i>=0;i--)
	{
		if(m_Tree.GetCheckState(m_arrScanHenji[i].hSubItem))
		{

			if(m_arrScanHenji[i].iType == 6001 || m_arrScanHenji[i].iType == 6002 || m_arrScanHenji[i].iType == 1005 ||
				m_arrScanHenji[i].iType == 6007 || m_arrScanHenji[i].iType == 6008 || m_arrScanHenji[i].iType == 2029 ||
				m_arrScanHenji[i].iType == 2030 || m_arrScanHenji[i].iType == 6011 || m_arrScanHenji[i].iType == 6012 ||
				m_arrScanHenji[i].iType == 6013 || m_arrScanHenji[i].iType == 6014 || m_arrScanHenji[i].iType == 6015 ||
				m_arrScanHenji[i].iType == 6016 )
			{
				continue;
			}
			m_Tree.SetState(m_arrScanHenji[i].hItem, 2);
			m_Tree.SetState(m_arrScanHenji[i].hSubItem,1);
			m_Tree.DeleteItem(m_arrScanHenji[i].hSubItem);
			m_arrScanHenji.RemoveAt(i);
		}
	}
	m_dlg->SetItemVisible(IDC_IMG_CLR_HENJI_SCAN_TREETOP, TRUE);

	m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, FALSE);
	m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, FALSE);
	m_hTimer = (HANDLE)_beginthreadex(NULL, 0, ScanTreeOnTimer, this, 0, NULL);
	m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP,FALSE);
	::SendMessage(m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("2"), (WPARAM)_T("��������ѡ������Ժ�..."));
	m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX1, L"");
	m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX2, L"");
	m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX3, L"");
	m_dlg->SetItemText(IDC_TXT_CLR_TREETOP2, L"");


	m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX1, FALSE);
	m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX2, FALSE);
	m_dlg->SetItemVisible(IDC_TXT_CLR_HENJI_SHOW_EX3, FALSE);
	m_dlg->SetItemVisible(IDC_TXT_CLR_TREETOP2,FALSE);

	m_finishScanId.RemoveAll();


	m_hClean = (HANDLE)_beginthreadex(NULL, 0, CleanProc, this, 0, NULL);

}
void CUIHandlerOpt::OnBkClrReScan()
{
	if(m_Tree.GetScanState())
	{
	
		if (m_hScan != (HANDLE)-1)
		{
			TerminateThread(m_hScan, NULL);
			m_hScan = NULL;
		}

	/*	myScanFileCallBack(this, 0, 0, 0, 0);
		myScanRegCallBack(this, 0, 0, 0, 0);*/
        if (m_pCleanPrc != NULL)
			m_pCleanPrc->DZ_StopScan();

			m_bStopScan = TRUE;
		//m_Tree.SetScanState(false);
		m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX1, L"");
		m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX2, L"");
		m_dlg->SetItemText(IDC_TXT_CLR_HENJI_SHOW_EX3, L"");
		m_dlg->SetItemText(IDC_TXT_CLR_TREETOP2, L"");
		m_dlg->SetItemText(IDC_TXT_CLR_TREETOP, L"");
		m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, FALSE);

		m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTN,TRUE);
		m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTNRESCAN,FALSE);
		m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, TRUE);

		//m_Tree.SetScanState(false);
		//::SendMessage(m_dlg->m_hWnd, MSG_CLR_HENJI_CLEAR_fINISH, (LPARAM)0, (WPARAM)0);
	}

	//ֹͣɨ��

	//::SendMessage(m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("2"), (WPARAM)_T("ɨ���Ѿ���ɣ�û����Ҫ�������Ŀ��"));
}
bool CUIHandlerOpt::IsClr()
{
	CString strTime;
	TCHAR	szBuffer[MAX_PATH] = {0};
	GetPrivateProfileString( _T("Statistics"), _T("uptime"), _T("0"), szBuffer, 100,m_ScanLogFile);

	int nOldyear=0,nOldMonth=0, nOldDay=0, nNewyear=0, nNewMonth=0, nNewDay=0;
	nNewyear= atoi(CW2A((CString)CTime::GetCurrentTime().Format( _T( "%Y" ) )));
	nNewMonth= atoi(CW2A((CString)CTime::GetCurrentTime().Format( _T( "%m" ) )));
	nNewDay= atoi(CW2A((CString)CTime::GetCurrentTime().Format( _T( "%d" ) )));

	strTime.Format(L"%s", szBuffer);
	int n = strTime.Find('-');
	int n1;
	n1 = strTime.Find('-', n+1);
	nOldyear = atoi(CW2A(strTime.Left(n)));
	nOldMonth = atoi(CW2A((CString)strTime.Mid(n+1, n1-n-1)));
	nOldDay = atoi(CW2A((CString)strTime.Right(strTime.GetLength()-n1-1)));

	if(nNewyear>nOldyear)
	{
		return false;
	}
	else if(nNewMonth>nOldMonth)
	{
		if(nNewMonth-nOldMonth>1)
		{
			return false;
		}
		else if(nNewDay>3)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if(nNewDay-nOldDay >4)
	{
		return false;
	}
	else
	{
		return true;
	}

}
void CUIHandlerOpt::RefreshCLRState( int nSel, BOOL bDowning )
{
	
	m_dlg->SetItemVisible(IDC_DIV_CLR_LOADERROR,FALSE);
	if(m_bDllLoadError)
	{
 		m_dlg->SetItemVisible(IDC_DIV_CLR_LOADERROR,TRUE);
// 		CKuiMsgBox	msg;
// 		CString			strMsg;
// 		strMsg.Format(_T("\nKClear.dll����ʧ�ܣ������°�װ"));
// 		msg.AddButton(_T("ȷ��"), IDYES);
// 		msg.AddButton(_T("ȡ��"), IDCANCEL);
// 
// 		msg.ShowMsg(strMsg,NULL,MB_OK|MB_ICONWARNING);
		
		return;
	}
	if (nSel==-1)
		nSel = m_dlg->GetTabCurSel(IDC_TAB_SYSOPT_LEFT);

	m_dlg->SetItemVisible(IDC_DIV_SYSOPT_CLR_HISTORY,TRUE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_NO_DOWN,TRUE);
	switch(m_n3TabType)
	{
	case 0:
		{
			if(m_bOneScan)return;
			m_dlg->SetItemVisible(IDC_DIV_CLR_DOWNING,FALSE);
			m_dlg->SetItemVisible(IDC_DIV_CLR_INSTALLED,FALSE);
			m_dlg->SetItemVisible(IDC_DIV_CLR_SCANING, FALSE);
			m_dlg->SetItemVisible(IDC_DIV_CLR_SCAN_TOP, FALSE);
			m_dlg->SetItemVisible(IDC_DIV_CLR_SCAN_LISTDOWN, FALSE);
			m_dlg->SetItemVisible(IDC_DIV_CLR_SCAN_LST, FALSE);

			static LPCTSTR lpShowText2[] = {
				_T("һ����������Щʲô��"),
				_T("��ɽ��ʿһ�������ܹ��������ϵͳ��Ӧ�ó����������������������ļ�����Ч���"),
				_T("�����ۼ���ע����Ӷ���������������˽��ʹϵͳ���ȶ������������С�")
			} ;
			m_dlg->SetItemText(IDC_TXT_CLR_NO_DOWN_TOP_TIP,lpShowText2[0]);
			m_dlg->SetItemText(IDC_TXT_CLR_NO_DOWN, lpShowText2[1]);
			m_dlg->SetItemText(IDC_TXT_CLR_STATE_DATE, lpShowText2[2]);
// 			TCHAR idBuffer[30];
// 			_itot(nSel-1, idBuffer, 10);

			m_dlg->SetItemVisible(IDC_DIV_CLR_PANL,TRUE);
			m_dlg->SetItemVisible(IDC_DIV_CLR_SCAN,TRUE);

			//m_dlg->SetItemText(IDC_TXT_CLR_STATE,_T("���ĵ����д��ںܶ������ļ�����������������"));
			//m_dlg->SetItemText(IDC_TXT_CLR_STATE_DATE,_T("��������ʱ�䣺2010-5-12 23:04:12"));
			if(!PathFileExists(m_ScanLogFile))
			{
				m_dlg->SetItemStringAttribute(IDC_ICON_CLR_NO_DOWN_TOP_TIP,"sub",L"0");
				m_dlg->SetItemText(IDC_TXT_CLR_STATE_SIZE,_T("���ĵ����д��ںܶ������ļ�����������������"));
				m_dlg->SetItemText(IDC_TXT_CLR_STATE_ALLSIZE,_T("�ۼ�����������δ��������"));
			}
			else
			{
				if(IsClr())
				{
					TCHAR	szBuffer[MAX_PATH] = {0};
					TCHAR	szBuffer1[MAX_PATH] = {0};
					GetPrivateProfileString( _T("Statistics"), _T("uptime"), _T("0"), szBuffer, 100,m_ScanLogFile);
					m_dlg->SetItemStringAttribute(IDC_ICON_CLR_NO_DOWN_TOP_TIP,"sub",L"1");
					CString strTime;
					strTime.Format(L"�ϴ�����ʱ�䣺%s", szBuffer);
					m_dlg->SetItemText(IDC_TXT_CLR_STATE_SIZE,strTime);

					GetPrivateProfileString( _T("Statistics"), _T("upfilecount"), _T("0"), szBuffer, 100,m_ScanLogFile);
					GetPrivateProfileString( _T("Statistics"), _T("upfilesize"), _T("0"), szBuffer1, 100,m_ScanLogFile);
					DWORD dwsize = atol(CW2A(szBuffer1));
					CString strsize;
					dwzh(dwsize, strsize);
					strTime.Format(L"�ۼ���������������%s���ļ������ͷ�%s���̿ռ�", szBuffer, strsize);
					m_dlg->SetItemText(IDC_TXT_CLR_STATE_ALLSIZE,strTime);

				}
				else
				{
					m_dlg->SetItemStringAttribute(IDC_ICON_CLR_NO_DOWN_TOP_TIP,"sub",L"0");
					m_dlg->SetItemText(IDC_TXT_CLR_STATE_SIZE,_T("���ĵ����д��ںܶ������ļ�����������������"));

					TCHAR	szBuffer[MAX_PATH] = {0};
					TCHAR	szBuffer1[MAX_PATH] = {0};
					GetPrivateProfileString( _T("Statistics"), _T("upfilecount"), _T("0"), szBuffer, 100,m_ScanLogFile);
					GetPrivateProfileString( _T("Statistics"), _T("upfilesize"), _T("0"), szBuffer1, 100,m_ScanLogFile);
					DWORD dwsize = atol(CW2A(szBuffer1));
					CString strsize;
					dwzh(dwsize, strsize);
					CString strTime;
					strTime.Format(L"�ۼ���������������%s���ļ������ͷ�%s���̿ռ�", szBuffer, strsize);
					m_dlg->SetItemText(IDC_TXT_CLR_STATE_ALLSIZE,strTime);
				}
			}
			m_dlg->SetItemCheck(IDC_CHK_CLR_SCAN_HENJI,TRUE);
			m_dlg->SetItemCheck(IDC_CHK_CLR_SCAN_LAJI,TRUE);
			m_dlg->SetItemCheck(IDC_CHK_CLR_SCAN_ZHUCEBIAO,TRUE);
		}
		break;
	case 1:
		{
			if(!m_Tree.GetScanState())
			m_dlg->SetItemVisible(IDC_IMG_CLR_HENJI_SCAN_TREETOP, FALSE);

			static bool bHenji = false;

			if(!bHenji)
			{
				m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTN,TRUE);
				m_dlg->SetItemVisible(IDC_DIV_CLR_TREEDOWNBTNRESCAN,FALSE);
				m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, FALSE);
				::SendMessage(m_dlg->m_hWnd, MSG_CLR_TREETOP, (LPARAM)_T("3"), (WPARAM)_T("ʹ�úۼ��ᱩ¶������˽�����鶨������"));
				bHenji = true;
			}
		}
		break;
	default:
		break;
	}
}
void CUIHandlerOpt::OnSetting()
{
	//OutputDebugStringW(_T("ѡ��"));
}
// CBkNavigator* CUIHandlerOpt::OnNavigate( CString &strChildName )
// {
// 	if (0 == strChildName.CompareNoCase(BKSFNS_SYSOPT_CLR_RUBBISH) )
// 	{
// 		m_dlg->SetTabCurSel(IDC_TAB_SYSOPT_LEFT,1);
// 		if ( !CClearModHelper::GetPtr()->IsInstalled() )
// 		{
// 			m_dlg->OnNavigate(CString(BKSFNS_PAGE_SYSTEM_OPTIMIZE));
// 		}
// 		else
// 		{
// 			CInstallStc::GetGlobalPtr()->ReportTabOpen(_Module.GetProductVersion(), CMainDlgStc::GetHomePRunSysOpt() );
// 		}
// 	}
// 	else if (0 == strChildName.CompareNoCase(BKSFNS_SYSOPT_CLR_HENJI))
// 	{
// 		m_dlg->SetTabCurSel(IDC_TAB_SYSOPT_LEFT,2);
// 		if ( !CClearModHelper::GetPtr()->IsInstalled() )
// 		{
// 			m_dlg->OnNavigate(CString(BKSFNS_PAGE_SYSTEM_OPTIMIZE));
// 		}
// 		else
// 		{
// 			CInstallStc::GetGlobalPtr()->ReportTabOpen(_Module.GetProductVersion(), CMainDlgStc::GetHomePRunSysOpt() );
// 		}
// 	}
// 	else if (0 == strChildName.CompareNoCase(BKSFNS_SYSOPT_CLR_REG))
// 	{
// 		m_dlg->SetTabCurSel(IDC_TAB_SYSOPT_LEFT,3);
// 		if ( !CClearModHelper::GetPtr()->IsInstalled() )
// 		{
// 			m_dlg->OnNavigate(CString(BKSFNS_PAGE_SYSTEM_OPTIMIZE));
// 		}
// 		else
// 		{
// 			CInstallStc::GetGlobalPtr()->ReportTabOpen(_Module.GetProductVersion(), CMainDlgStc::GetHomePRunSysOpt() );
// 		}
// 	}
// 	else if (0 == strChildName.CompareNoCase(BKSFNS_SYSOPT_RUN_OPT))
// 	{
// 		m_dlg->SetTabCurSel(IDC_TAB_SYSOPT_LEFT, 0);
// 	}
// 	return NULL;
// }
OneTy CUIHandlerOpt::QueryItem(int iItem)
{
	OneTy onety;
	POSITION pos;
	pos = m_OneMap.GetStartPosition();
	while (pos!=NULL)
	{
		CString strClearid = m_OneMap.GetKeyAt(pos);
		onety = m_OneMap.GetNextValue(pos);
		if(onety.nItem == iItem)
		{
			return onety;
		}
	}
	onety.strClearname =L"";
	return onety;
}
LRESULT CUIHandlerOpt::OnLVNVirusGetDispInfo(LPNMHDR pnmh)
{
	NMLVDISPINFO *pdi = (NMLVDISPINFO*)pnmh;
	OneTy onety= QueryItem(pdi->item.iItem);
	if(onety.strClearname == "")return 0;

	if (pdi->item.mask & LVIF_IMAGE)
	{
		if(onety.strState.Find(L"����")>=0 || onety.strState.Find(L"�ȴ�")>=0)pdi->item.iImage = 4;
		else if(onety.strState.Find(L"�������")>=0 || onety.strState.Find(L"ɨ�����")>=0)pdi->item.iImage = 2;
		else if(onety.strState.Find(L"δ���")>=0)pdi->item.iImage = 1;
	}

	if (pdi->item.mask & LVIF_TEXT)
	{
		CString strItem;
		switch (pdi->item.iSubItem)
		{
		case 0:
			{
				strItem = onety.strClearname;
			}			
			break;
		case 1:
			{
				strItem = onety.strClearInfo;
			}
			break;
		case 2:
			{
				strItem = onety.strState;
			}
			break;
		}
		wcsncpy(pdi->item.pszText, strItem, min(strItem.GetLength() + 1, pdi->item.cchTextMax - 1));
	}
	return 0;
}
void CUIHandlerOpt::OnBkCLROneScan()
{
}
void CUIHandlerOpt::OnBkCLROneReturn()
{
	RefreshCLRState();
}
void CUIHandlerOpt::OnBkCLROneStop()
{
	if (m_hScan != (HANDLE)-1)
	{
		TerminateThread(m_hScan, NULL);
	}
	if(m_bScanBage)
	{
        if (m_pCleanPrc != NULL)
		    m_pCleanPrc->DZ_StopScanBage();
	}
    if (m_pCleanPrc != NULL)
	    m_pCleanPrc->DZ_StopScan();
	m_bOneStop = true;
}
LRESULT CUIHandlerOpt::OnWmOneScanTxt( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_dlg->SetItemText(IDC_TXT_CLR_SCANING,(TCHAR*)lParam);
	return S_OK;
}
LRESULT CUIHandlerOpt::OnWmOneScanValue( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	//int n = (int)wParam;
	//m_dlg->SetItemIntAttribute(IDC_PRO_CLR_SCANING, "value", n);
	StopCleanEx();
	return S_OK;
}

LRESULT CUIHandlerOpt::OnWmOneScanPrg( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	CString strFormat;
	int n = (int)wParam;
	switch(n)
	{
	case 0://ɨ�����
		{
			strFormat.Format(L"������������%s", (TCHAR*)lParam);
			m_dlg->SetItemStringAttribute(IDC_IMG_CLR_SCAN_TOP,"sub",L"1");
			m_dlg->SetItemText(IDC_TXT_CLR_SCAN_INFO1,L"��ϲ�����ѳɹ������ϵͳ����");
			m_dlg->SetItemText(IDC_TXT_CLR_SCAN_INFO2,strFormat);
		}
		break;
	case 1://��������
		{
			m_dlg->SetItemStringAttribute(IDC_IMG_CLR_SCAN_TOP,"sub",L"1");
			m_dlg->SetItemText(IDC_TXT_CLR_SCAN_INFO1,L"���ĵ���״�����ã������������");
			m_dlg->SetItemText(IDC_TXT_CLR_SCAN_INFO2,L"������������û����Ҫ�������Ŀ");
		}
		break;
	case 2://δ���
		{
			strFormat.Format(L"������������%s", (TCHAR*)lParam);
			m_dlg->SetItemStringAttribute(IDC_IMG_CLR_SCAN_TOP,"sub",L"0");
			m_dlg->SetItemText(IDC_TXT_CLR_SCAN_INFO1,L"��������û����ɣ�����������������");
			m_dlg->SetItemText(IDC_TXT_CLR_SCAN_INFO2,strFormat);
		}
		break;
	}
	m_dlg->SetItemVisible(IDC_DIV_CLR_SCAN_TOP, TRUE);
	m_dlg->SetItemVisible(IDC_DIV_CLR_SCAN_LISTDOWN, TRUE);

	
	return S_OK;
}

LRESULT CUIHandlerOpt::OnWmRegClearFinish( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_dlg->EnableItem(IDC_BTN_CLR_REG_TREEDOWNBTN_SCAN, TRUE);
	m_dlg->EnableItem(IDC_BTN_CLR_REG_TREEDOWNBTN_CLEAN, FALSE);

	m_dlg->SetItemVisible(IDC_IMG_CLR_REG_TREETOP,TRUE);
	if(m_hTimer != (HANDLE)-1)
	{
		TerminateThread(m_hTimer, NULL);
		m_hTimer = (HANDLE)-1;
	}

	m_dlg->SetItemVisible(IDC_IMG_CLR_REG_SCAN_TREETOP,FALSE);

	return TRUE;
}
LRESULT CUIHandlerOpt::OnWmHenjiClearFinish( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_SCAN, TRUE);
	m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, TRUE);
//	m_dlg->EnableItem(IDC_BTN_CLR_TREEDOWNBTN_CLEAN, FALSE);
	m_Tree.SelectSetFirstVisible(m_RootTree);

	m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP,TRUE);
	if(m_hTimer != (HANDLE)-1)
	{
		TerminateThread(m_hTimer, NULL);
		m_hTimer = (HANDLE)-1;
	}

	m_dlg->SetItemVisible(IDC_IMG_CLR_HENJI_SCAN_TREETOP,FALSE);

	return TRUE;
}
LRESULT CUIHandlerOpt::OnWmTreeScaning( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	static int nPos = 0;

    m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP2, TRUE);
    m_dlg->SetItemVisible(IDC_IMG_CLR_TREETOP, FALSE);
    m_dlg->SetItemVisible(IDC_IMG_CLR_HENJI_SCAN_TREETOP, FALSE);

	m_dlg->SetItemIntAttribute(IDC_IMG_CLR_TREETOP2, "sub", (++nPos)%8);

	//int n = (LPARAM)lParam;
	//switch(n)
	//{
	//case 1:
	//	//m_dlg->SetItemVisible(IDC_IMG_CLR_HENJI_SCAN_TREETOP, TRUE);
	//	m_dlg->SetItemIntAttribute(IDC_IMG_CLR_TREETOP2, "sub", (++nPos)%8);
	//	break;
	//case 2:
	//	//m_dlg->SetItemVisible(IDC_IMG_CLR_LAJI_SCAN_TREETOP, TRUE);
	//	m_dlg->SetItemIntAttribute(IDC_IMG_CLR_TREETOP2, "sub", (++nPos)%8);
	//	break;
	//case 3:
	//	//m_dlg->SetItemVisible(IDC_IMG_CLR_REG_SCAN_TREETOP, TRUE);
	//	m_dlg->SetItemIntAttribute(IDC_IMG_CLR_REG_SCAN_TREETOP, "sub", (++nPos)%8);
	//	break;
	//}
	return TRUE;
}

LRESULT CUIHandlerOpt::OnWmHenjiTreeHei( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	CString strInfo = (TCHAR*)lParam;
	int n = (int)wParam;

	m_Tree.SetItemNow(m_TreeHenjiMap.Lookup(n)->m_value.hItem);
	m_Tree.SetItemText(m_TreeHenjiMap.Lookup(n)->m_value.hItem, strInfo);
	m_Tree.SetTextItemColor(m_TreeHenjiMap.Lookup(n)->m_value.hItem, RGB(0,0,0));

	return TRUE;
}

LRESULT CUIHandlerOpt::OnBkClrScanForKIS( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	OnBkClrScan();

	return TRUE;
}
LRESULT CUIHandlerOpt::OnWmHenjiTreeHong( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	CString strInfo = (TCHAR*)lParam;
	int n = (int)wParam;

	m_Tree.SetItemNow(m_TreeHenjiMap.Lookup(n)->m_value.hItem);
	m_Tree.SetItemText(m_TreeHenjiMap.Lookup(n)->m_value.hItem, strInfo);
	m_Tree.SetTextItemColor(m_TreeHenjiMap.Lookup(n)->m_value.hItem, RGB(255,0,0));

	return TRUE;
}

LRESULT CUIHandlerOpt::OnWmLajiClearFinish( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_dlg->EnableItem(IDC_BTN_CLR_LAJI_TREEDOWNBTN_SCAN, TRUE);
	m_dlg->EnableItem(IDC_BTN_CLR_LAJI_TREEDOWNBTN_CLEAN, FALSE);

	m_dlg->SetItemVisible(IDC_IMG_CLR_LAJI_TREETOP,TRUE);
	if(m_hTimer != (HANDLE)-1)
	{
		TerminateThread(m_hTimer, NULL);
		m_hTimer = (HANDLE)-1;
	}

	m_dlg->SetItemVisible(IDC_IMG_CLR_LAJI_SCAN_TREETOP,FALSE);

	return TRUE;
}
void CUIHandlerOpt::OnBkClrShowDafaul()
{
	bool bret = false;
	if(PathFileExists(m_CacheFile))
	{
		CAtlMap<CString, CString> TreeHenjiMap;
		LoadUserCache(TreeHenjiMap, L"kclear_checke_henji");
		int n = (int)TreeHenjiMap.GetCount();
		if(n>0)bret = true;
		POSITION pos;
		pos = m_TreeHenjiMap.GetStartPosition();
		while (pos!=NULL)
		{
			int n = m_TreeHenjiMap.GetKeyAt(pos);
			TreeInfo treeinfo = m_TreeHenjiMap.GetNextValue(pos);
			CString strClearid;
			strClearid.Format(L"%d", n);
			if(TreeHenjiMap.Lookup(strClearid)!=NULL)
			{
				m_TreeHenjiMap[n].iCheck = atoi(CW2A(TreeHenjiMap.Lookup(strClearid)->m_value));
				m_Tree.SetState(m_TreeHenjiMap[n].hItem, m_TreeHenjiMap[n].iCheck);
			}
		}
		m_Tree.Set2ItemState(m_Tree.GetRootItem());
	}
	if(!bret)
	{
		CKuiMsgBox	msg;
		CString			strMsg;
		strMsg.Format(_T("\n����δ�����ҵķ��������ǽ��ѡ��Ƽ���������Ϊ�ҵķ�����"));
		msg.AddButton(_T("ȷ��"), IDYES);
		msg.AddButton(_T("ȡ��"), IDCANCEL);

		if(msg.ShowMsg(strMsg,NULL,MB_YESNO|MB_ICONWARNING) == IDYES)
		{
			SetCheckTree(m_TreeHenjiMap, "1", &m_Tree);
			WriteOneCache(m_TreeHenjiMap, &m_Tree, _T("kclear_checke_henji"));
		}
	}
}


int CUIHandlerOpt::GetScrollMaxSize(TreeInfo& treeinfo)
{
	int nMaxSize = 0;
	if (treeinfo.nType == 101)
	{
		nMaxSize = 11;
		goto _exit_;
	}
	else if (treeinfo.nType == 103)
	{
		nMaxSize = 12;
		goto _exit_;
	}
	else if (treeinfo.nType == 104)
	{
		nMaxSize = 19;
		goto _exit_;
	}
	else if (treeinfo.nType == 105)
	{
		nMaxSize = 42;
		goto _exit_;
	}
_exit_:

	return nMaxSize;
}

int CUIHandlerOpt::GetScrollCurrentPos(TreeInfo& treeinfo)
{
	int nCurrentPos = 0;
	if (treeinfo.nType == 101)
	{
		nCurrentPos = treeinfo.nSn;
		goto _exit_;
	}
	else if (treeinfo.nType == 103)
	{
		nCurrentPos = 12/* + treeinfo.nSn*/;
		goto _exit_;
	}
	else if (treeinfo.nType == 104)
	{
		nCurrentPos = 12 + treeinfo.nSn;
		goto _exit_;
	}
	else if (treeinfo.nType == 105)
	{
		nCurrentPos = 12 + 20 + treeinfo.nSn;
		goto _exit_;
	}
_exit_:
	return (nCurrentPos) ;
}

BOOL CUIHandlerOpt::IsEableCleanBtn()
{
	BOOL bRet = FALSE;

	int nIndex = 0;
	for (int i=0; i < m_arrScanHenji.GetSize(); i++)
	{
		if(m_Tree.GetCheckState(m_arrScanHenji[i].hSubItem) 
			&& m_arrScanHenji[i].nType != 4
			)
		{
			bRet = TRUE;
			goto _exit_;
		} 
	}

_exit_:
	return bRet;
}

BOOL CUIHandlerOpt::IsIncludeNoScanItem()
{
	BOOL bRet = FALSE;

	POSITION pos;
	pos = m_TreeHenjiMap.GetStartPosition();
	while (pos!=NULL)
	{
		int n = m_TreeHenjiMap.GetKeyAt(pos);
		TreeInfo treeinfo = m_TreeHenjiMap.GetNextValue(pos);
		if (treeinfo.iCheck == 2 || 
			m_Tree.GetCheckStateEx(treeinfo.hItem))
		{
			if (m_finishScanId.Find(n) == -1 && m_finishScanId.GetSize() > 0)
			{
				if (!m_pCleanPrc->DZ_GetNoinstallApp(n))
				{
					bRet = TRUE;
					goto _exit_;
				}
			}
		}
	}

_exit_:
	return bRet;
}

BOOL CUIHandlerOpt::IsAllNeedRebootDelete()
{
	BOOL bRet = FALSE;

	for (int i = 0; i < m_arrScanHenji.GetSize(); i++)
	{
		if (m_arrScanHenji[i].nType != 4 )
		{
			bRet = TRUE;
			goto _exit_;
		}
	}
_exit_:
	return bRet;
}

BOOL CUIHandlerOpt::IsAllNeedRebootDeleteEx()
{
	BOOL bRet = FALSE;
	int nTotalCount = 0;

	int nCount = 0;

	POSITION pos;
	pos = m_TreeHenjiMap.GetStartPosition();
	while (pos!=NULL)
	{
		int n = m_TreeHenjiMap.GetKeyAt(pos);
		TreeInfo treeinfo = m_TreeHenjiMap.GetNextValue(pos);
		if (treeinfo.iCheck == 2 || 
			m_Tree.GetCheckStateEx(treeinfo.hItem))
		{
			nCount = m_arrScanHenji.GetSize();
			for (int i = 0; i < m_arrScanHenji.GetSize(); i++)
			{

				if (m_arrScanHenji[i].hItem == treeinfo.hItem)
				{
					if (m_arrScanHenji[i].nType != 4)
					{
						bRet = FALSE;
						goto _exit_;
					}
					else
					{
						nTotalCount++;
					}
				}
			}
			
		}
	}

	if (nTotalCount > 0)
	{
		bRet = TRUE;
	}

_exit_:
	return bRet;
}
BOOL CUIHandlerOpt::IsNoCleanEmpty()
{
	BOOL bRet = FALSE;
	int nTotalCount = 0;

	int nCount = 0;

	POSITION pos;
	pos = m_TreeHenjiMap.GetStartPosition();
	while (pos!=NULL)
	{
		int n = m_TreeHenjiMap.GetKeyAt(pos);
		TreeInfo treeinfo = m_TreeHenjiMap.GetNextValue(pos);
		if (m_Tree.GetCheckState(treeinfo.hItem))
		{
			CString strText;
			m_Tree.GetItemText(treeinfo.hItem, strText);
			//if (strText.Find(_T("�������")) != -1 || strText.Find(_T("û����Ҫ�������Ŀ")) == -1 )
			//{
			//	bRet = FALSE;
			//	goto _exit_;
			//}
			if (strText.Find(_T("��0")) != -1 && strText.Find(_T("��0")) != -1)
			{
				bRet = TRUE;
				goto _exit_;
			}

			if (strText.Find(_T("��0��")) != -1)
			{
				bRet = TRUE;
				goto _exit_;
			}
		}
	}

_exit_:
	return bRet;		
}
//
//BOOL CUIHandlerOpt::InitOne()
//{
//	CString strOneId;
//
//	strOneId = _T("9042");
//	m_dOneScanId.push_back(strOneId);
//
//	strOneId = _T("9043");
//	m_dOneScanId.push_back(strOneId);
//
//	strOneId = _T("1003");
//	m_dOneScanId.push_back(strOneId);
//	return TRUE;
//}
//
//BOOL CUIHandlerOpt::OnOneScanEx()
//{
//	BOOL bRet = FALSE;
//	InitOne();
//	int nScanId[100] = {0};
//	int nIndex = 0;
//	std::deque<CString>::iterator it;
//	for (it = m_dOneScanId.begin(); it != m_dOneScanId.end(); it++)
//	{
//		int nn = atoi(CW2A(*it));
//		nScanId[nIndex] = nn;
//		nIndex++;
//	}
//
//	int nSize = m_dOneScanId.size();
//
//	if (m_pCleanPrc != NULL)
//	{
//		m_pCleanPrc->DZ_IsScanClean(TRUE);
//		m_pCleanPrc->DZ_StartScan(nScanId, nSize);
//	}
//
//	return bRet;
//}

void CUIHandlerOpt::SetCallback(ICleanCallback* piCallback)
{
	bool bRet = false;
	if (piCallback == NULL)
	{
		goto _exit_;
	}
	m_pOneCleanCallBack = piCallback;
_exit_:
	return;
}
bool CUIHandlerOpt::StartClean(int nTask, const char* szTask)
{
	bool bRet = false;
	int nIndex = 0;
	std::deque<int>::iterator it;
	if (m_pOneCleanCallBack == NULL)
	{
		goto _exit_;
	}
	m_pOneCleanCallBack->OnBegin();
//	m_OneScanId.clear();
	m_OneKeyId.RemoveAll();

//�����������
	ParaseOneScan(szTask, /*m_OneScanId, */nTask);

	//for (it = m_OneScanId.begin(); it != m_OneScanId.end(); it++)
	//{
	//	if (*it > 1000 )
	//	{
	//		nIndex++;
	//	}
	//}
	nIndex = m_OneKeyId.GetSize();

	if (nIndex == 0)
	{
		m_pOneCleanCallBack->OnEnd();
		goto _exit_;
	}
	m_bOneScan = TRUE;
    if (m_pCleanPrc == NULL)
    {
        m_pOneCleanCallBack->OnEnd();
        goto _exit_;
    }
	m_hScanEx = (HANDLE)_beginthreadex(NULL, 0, OneScanProce, this, 0, NULL);

_exit_:
	return bRet;
}
bool CUIHandlerOpt::StopClean()
{
	if (m_hScanEx != (HANDLE)-1)
	{
		TerminateThread(m_hScanEx, NULL);
		m_hScanEx = (HANDLE) -1;
	}

    if (m_pCleanPrc != NULL)
	    m_pCleanPrc->DZ_StopScan();
	
    m_bOneScan = FALSE;
	m_bOneStop = TRUE;
    if (m_pOneCleanCallBack != NULL)
    {
	    m_pOneCleanCallBack->OnCancel();
	    m_pOneCleanCallBack->OnEnd();
    }
	return false;
}

bool CUIHandlerOpt::StopCleanEx()
{
	if (m_hScanEx != (HANDLE)-1)
	{
		TerminateThread(m_hScanEx, NULL);
		m_hScanEx = (HANDLE) -1;
	}
    if (m_pCleanPrc != NULL)
	    m_pCleanPrc->DZ_StopScan();
	
    m_bOneScan = FALSE;
	m_bOneStop = TRUE;
	
    if (m_pOneCleanCallBack != NULL)
        m_pOneCleanCallBack->OnEnd();
	
    return false;
}

unsigned CUIHandlerOpt::OneScanProce(LPVOID lpVoid)
{	
	CUIHandlerOpt* pDlg = (CUIHandlerOpt*)lpVoid;

	int nScanId[1000] = {0};
	int nIndex = 0;
	
	//std::deque<int>::iterator it;
	//for (it = pDlg->m_OneScanId.begin(); it != pDlg->m_OneScanId.end(); it++)
	//{
	//	if (*it > 1000 )
	//	{
	//		nScanId[nIndex] = *it;
	//		nIndex++;
	//	}
	//}
	for (int i = 0; i< pDlg->m_OneKeyId.GetSize(); i++)
	{
		nScanId[i] = pDlg->m_OneKeyId[i];
		nIndex++;
	}

	if (pDlg->m_pCleanPrc != NULL)
	{
		pDlg->m_pCleanPrc->DZ_IsScanClean(TRUE);
		pDlg->m_pCleanPrc->DZ_StartScan(nScanId, nIndex);
	}

	return TRUE;
}

BOOL CUIHandlerOpt::ParaseOneScan(const char* szTask/*, std::deque<int>&vnOneScan*/, const int nTask)
{
	BOOL bRet = FALSE;
	int nIndex = 0;
	int nScanId = 0;
	char szScanId[5] = {0};
	int i = 0;
	int n = 0;
	int j = 0;
	int nId = 0;
	char szTemp[5] = {0};
	CString strOneId;
	std::deque<CString> arr;
	if (sizeof(szTask) <= 0)
	{
		bRet = FALSE;
		goto _exit_;
	}
	m_OneMap.RemoveAll();
	m_OneTypeMap.RemoveAll();

	for (i = 0; i < nTask; i++)
	{
		if (szTask[i] == ',')
		{
			strncpy(szTemp, szTask + j, 4);
			strOneId = szTemp;
			arr.push_back(strOneId);
			j = i + 1;
		}
	}

	strncpy(szTemp, szTask + j, 4);
	strOneId = szTemp;
	arr.push_back(strOneId);
	
	j = 0;
	i = 0;

	for (std::deque<CString>::iterator p = arr.begin();p!=arr.end();p++)
	{
		CString strClearid = *p;
		for (int i=0; i<m_arrClearInfo.GetSize();i++)
		{
			if (m_arrClearInfo[i].strClearid == strClearid)
			{
				for (int j = 0; j < m_arrClearType.GetSize(); j++)
				{
					if (m_arrClearInfo[i].strTypeid == m_arrClearType[j].strTypeid)
					{

						CString str123 = m_arrClearType[j].strTypeid;
						if(m_OneTypeMap.Lookup(strClearid)!=NULL)
						{
							continue;
						}
						m_OneTypeMap.SetAt(strClearid, m_arrClearInfo[i].strTypeid);


						if(m_OneMap.Lookup(m_arrClearInfo[i].strTypeid)!=NULL)
						{
							//���������2���ڵ�����
							m_OneMap[m_arrClearInfo[i].strTypeid].dwJianceNum++;
							m_OneMap[m_arrClearInfo[i].strTypeid].strExtName += m_arrClearInfo[i].strExtName;
							bRet = TRUE;
							break;
						}
						OneTy onety;
						onety.nItem = n;
						onety.strClearname = m_arrClearType[j].strTypeName;
						onety.strState = L"�ȴ�����...";
						onety.strClearInfo = L"0KB �ļ�������0";
						onety.strExtName = m_arrClearInfo[i].strExtName;
						onety.dwFileNum = 0;
						onety.dwFilesize = 0;
						onety.dwJiancedNum=0;
						onety.dwJianceNum=1;
						onety.strClear2name = m_arrClearInfo[i].strClearName;
						m_OneMap.SetAt(m_arrClearInfo[i].strTypeid, onety);
						n++;
						bRet = TRUE;
						break;
					}
				}
				if (bRet)
				{
					break;
				}
			}
		}
	}

	for (i = 0; i < nTask; i++)
	{
		if (szTask[i] == ',')
		{
			strncpy(szTemp, szTask + j, 4);
            nId = atoi(szTemp);
			if (nId > 0)
			{
				//vnOneScan.push_back(nId);
				m_OneKeyId.Add(nId);
			}
			j = i + 1;
		}
	}
	strncpy(szTemp, szTask + j, 4);
	nId = atoi(szTemp);
	if (nId > 0)
	{
		//vnOneScan.push_back(nId);
		m_OneKeyId.Add(nId);
	}
_exit_:
	return bRet;
}

void CUIHandlerOpt::Release()
{
	return;
}

//////////////////////////////////////////////////////////////////////////

BOOL CUIHandlerOpt::CheckIEVersioin(int& ieVersion)
{
    BOOL bRet = FALSE;
    DWORD infoSize = 0;
    CString strName;
    TCHAR szPath[MAX_PATH] = {0};
    TCHAR *szInfo = NULL;
    TCHAR   szSubBlock[256];
    TCHAR *lpBuffer = NULL;
    UINT   dwBytes; 

    struct   LANGANDCODEPAGE   { 
        WORD   wLanguage; 
        WORD   wCodePage; 
    }   *lpTranslate; 

    //   Read   the   list   of   languages   and   code   pages. 
    UINT   cbTranslate; 

    SHGetSpecialFolderPath(NULL, szPath, CSIDL_WINDOWS, FALSE);
    PathAppend(szPath, L"System32\\ieframe.dll");

    infoSize = GetFileVersionInfoSize(szPath, NULL);   

    if (infoSize == 0)        
        goto Clear0;

    szInfo = new TCHAR[infoSize + 2];

    if (!GetFileVersionInfo(szPath, NULL, infoSize, szInfo))
    {
        goto Clear0;
    }   

    ::VerQueryValue(   szInfo,   L"\\VarFileInfo\\Translation", 
        (LPVOID*)&lpTranslate,   &cbTranslate   ); 

    _snwprintf(   szSubBlock,   256,   L"\\StringFileInfo\\%04x%04x\\ProductVersion", 
        lpTranslate[0].wLanguage,   lpTranslate[0].wCodePage   ); 
    if(   ::VerQueryValue(   szInfo,   szSubBlock,   (   LPVOID*   )&lpBuffer,   &dwBytes   )   ) 
    { 
        if (lpBuffer)
        {
            ieVersion = lpBuffer[0] - 48;
        }
        else
        {
            ieVersion = 0;
        }
    } 

    bRet = TRUE;
Clear0:
    if (szInfo)
    {
        delete[] szInfo;
        szInfo = NULL;
    }
    if (ieVersion <= 0)
    {
        // ע���
        CRegKey key;
        TCHAR szVersion[128];
        ULONG uLen = 128;

        key.Create(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Internet Explorer"));
        key.QueryStringValue(L"Version", szVersion, &uLen);

        ieVersion = szVersion[0] - 48;

        key.Close();
    }

    if (ieVersion <= 0 || ieVersion >= 10)
    {
        ieVersion = 0;
        bRet = FALSE;
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////////
