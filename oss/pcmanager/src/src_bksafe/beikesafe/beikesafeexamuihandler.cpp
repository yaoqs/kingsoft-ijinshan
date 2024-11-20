#include "stdafx.h"
#include "beikesafe.h"
#include "beikesafemaindlg.h"
#include "beikesafeexamuihandler.h"
#include <iefix/cinifile.h>
using namespace IniFileOperate;
#include "cbkexamsafe_shareresourcedlg.h"
#include "kws/KwsSetting.h"
#include "bksafeexam_guest.h"
#include <bksafe/bksafeconfig.h>
#include <winmod/wintrustverifier.h>
using namespace WinMod;
#include "iefix/RegisterOperate.h"
#include "miniutil/fileversion.h"
#include "communits/VerifyFileFunc.h"



#define PI 3.1415926535897932384626433832795029L

// #define EXAM_ITEM_COUNT 19


//���ɨ��ĳ�ʼ��ʾ״̬
static CAtlArray<CBeikeSafeExamUIHandler::EXAM_ITEM> g_ExamItem;

// #define EXAM_RESULT_TEXT_COUNT 28
//���ɨ������У��м����ֵ�״̬
static CAtlArray<CBeikeSafeExamUIHandler::EXAM_SCAN_RESULT> g_ExamResultText2;

//���ɨ����������ʾ������
static CAtlArray<CBeikeSafeExamUIHandler::EXAM_SCAN_RESULT> g_ExamResultText;

static CAtlArray<CBeikeSafeExamUIHandler::SAFE_MONITOR_ITEM> g_SafeMonitorItem;

/*
Unknown   = -1,
Safe      = 0,//��ȫ
Info      = 1,//��Ϣ��from msg
RiskInfo  = 2,//�з�����Ϣ from msg
Critical  = 3,//Σ��(���ǹٷ��汾)
Risk_0    = 4,//���գ������ΰ�ȫ������ ui_echofail��
*/
#define MACRO_VALUE_BEGIN

#define URL_COLOR							RGB(77,113,149)			//listview��URLʹ�õ���ɫ
#define TEXT_SAFE_COLOR						RGB(0,128,0)			//listview�а�ȫ���ֵ���ɫ
#define TEXT_OPT_COLOR						RGB(22,113,191)
#define TEXT_DANGER_COLOR					RGB(200,0,0)			//listview��Σ�����ֵ���ɫ
#define TEXT_RISK_O_COLOR					RGB(0xF9,0x93,0x00)		//listview�з������ֵ���ɫ
#define TEXT_DEFAULT_COLOR					RGB(0,0,1)				//listview��Ĭ�����ֵ���ɫ
#define TEXT_COLOR							RGB(0x10,0x10,0x10)
#define TEXT_COLORT_DEFAULT_RESULT			RGB(0x7e,0x7e,0x7e)
#define TEXT_COLOR_OPT						RGB(22,113,191)
#define EXAM_RESULT_SAFE_GROUP_ID			100						//��ȫ��
#define EXAM_RESULT_DANGER_GROUP_ID			200						//Σ����
#define EXAM_RESULT_CANCEL_GROUP_ID			300						//ȡ����
#define EXAM_RESULT_IGNORE_GROUP_ID			400						//������
#define EXAM_RESULT_OPT_GROUP_ID			500						//�Ż���
#define EXAM_OPERATE_CANCEL_IGNORE			1000					//ȡ������
#define EXAM_OPERATE_STARTUP				2000					//����ĳ������
#define EXAM_OPERATE_VIEW					3000					//�鿴����

#define EXAM_PAGE_MAX_LINE					9
#define EXAM_SHOW_COUNT						0
#define MACRO_VALUE_END

#define PRINTF_STR(x,y)						{_sntprintf_s((x), sizeof((x)), TEXT("%s"), (y));}
#define PRINTF_STR2(x,f,y)					{_sntprintf_s((x), sizeof((x)), (f), (y));}
#define PRINTF_INT(x,y)						{_sntprintf_s((x), sizeof((x)), TEXT("%d"), (y));}
#define SAFE_CALL_FUNC(x,y)					{if(NULL != (x)){(x)->(y)}}
#define SAFE_CALL_FUN(x,y)                  if (NULL != (x)){(x)->y;}


CRITICAL_SECTION g_StartExam_cs;

CBeikeSafeExamUIHandler::~CBeikeSafeExamUIHandler()
{
	//DeleteCriticalSection(&g_Exam_cs);
	_ResetMapVector();
	DeleteCriticalSection(&g_StartExam_cs);
	if(NULL != m_hStartExamEvent)
		CloseHandle(m_hStartExamEvent);
	m_hStartExamEvent = NULL;
	_Module.Exam.Stop();
	m_bExamFinished = TRUE;
	m_ExamItemSort.RemoveAll();
	if (0 != m_nStartExamTime)
		_WriteExamLogToIni();

	if (NULL != m_hExamShareDataEvent)
		CloseHandle(m_hExamShareDataEvent);
	m_hExamShareDataEvent = NULL;

	DeleteCriticalSection(&m_LockShareData);
}

#if 0
void CBeikeSafeExamUIHandler::_CheckKwsExamResult()
{
	BKSAFE_EXAM_RESULT_ITEM kwsItem;
	m_bKwsExist = TRUE;//( _IsExistKWS() == 0 );

	//������δ��װ���ܳ���2�Σ��򲻼������
	int nKwsCnt = BKSafeConfig::GetKwsNoUseCnt();
	if(  nKwsCnt > 2 && !m_bKwsExist)
		return;

	BOOL bKwsAllOpen = _IsAllKwsOpen() == 0;
	if( !m_bKwsExist )
		BKSafeConfig::SetKwsNoUseCnt( ++nKwsCnt );

	if( bKwsAllOpen && m_bKwsExist )
	{//��ȫ
		kwsItem.nLevel = 0;
	}
	else
	{//Σ��
		kwsItem.nLevel = 4;
	}
	//_UpdateExamData( BkSafeExamItem::EXAM_KWS_MON, &kwsItem);
	BKSAFE_EXAM_RESULT_ITEM pnms;
	pnms.strDetail = pnms.strItemDetailUrl = pnms.strItemNavigateString = pnms.strItemNoticeText = pnms.strOperationText = L"XXX";
	pnms.nLevel = kwsItem.nLevel;
	_UpdateExamData(BkSafeExamItem::EXAM_KWS_MON, &pnms);
	_ShareExamData(MSG_APP_EXAM_SCORE_CHANGE, BkSafeExamItem::EXAM_KWS_MON, (LPARAM)&pnms);
}

#endif

int CBeikeSafeExamUIHandler::_IsAllKwsOpen()
{
	KwsSetting setting;
	int nErrorCount = 0;
	//��ҳ����
	BOOL bKwsEnable = setting.IsAntiTrojanEnable();
	if( !bKwsEnable )
		nErrorCount++;

	//���㱣��
	BOOL bFishing = setting.IsFishingEnable();
	if( !bFishing )
		nErrorCount++;

	//���ر���
	// 	if (FALSE == setting.IsAutoScanEnable())
	// 		nErrorCount++;

	//	DWORD dwVal;
	//�������汣��
	// 	setting.GetSearchEngine(dwVal);
	// 	BOOL bSearch  = (dwVal > 0);
	// 	if( !bSearch )
	// 		nErrorCount++;

	//��ҳ����
	// 	if (FALSE == setting.IsLockSPEnable())
	// 		nErrorCount++;

	/* �����˲�Ӱ�찲ȫ״̬
	//������
	if (FALSE == setting.IsAnyRuleSubscribed())
	nErrorCount++;
	*/
	return nErrorCount;
}


//�������н���������Ļص�����
LRESULT CBeikeSafeExamUIHandler::OnAppExamScoreChange(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nItem = (int)wParam;
	BKSAFE_EXAM_RESULT_ITEM *pnms = (BKSAFE_EXAM_RESULT_ITEM *)lParam;

	_ShareExamData(uMsg, wParam, lParam);

	if (BkSafeExamItem::Invalid == nItem || NULL == pnms)
	{//�ش�ɨ�������Ϣ��(���������̽���ʱ���ܵ������Ϣ�����û�ȡ��)
		//�������ܼ��״̬�ļ��
		//_CheckKwsExamResult();

		if(FALSE == _Module.Exam.Canceled())//����û�û��ȡ������ǿ�����
			m_mapCancelScanResult.RemoveAll();

		m_bExamFinished = TRUE;
		// ɨ���ˣ�����ɨ��������
		_ShowExamResultData();//  [2/25/2010 zhangbaoliang]
		m_nRealProgress = 100;
		m_pDlg->SetItemIntAttribute(IDC_PROGRESS_EXAM, "value", m_nRealProgress);

		//�ش�������־
		_ReportLog(examtime);
		_ReportLog(examresult, m_strDangerIDs);
		CString strValue;
		m_nMaxScore = m_nMinScore;
		//_UpdateExamScoreImage();
		_UpdateExamResultTitle();
		_WriteExamLogToIni();//write log
		SetEvent(m_hExamShareDataEvent);//֪ͨ���¹����ڴ��е�����
	} else if (BkSafeExamItemExOperate::RemoveItem == nItem)
	{//�޸���ĳ��������Ŀ
		m_lockRemove.Lock();
		if (NULL != lParam)
		{
			if( !IsBadReadPtr( (void*)lParam, sizeof(REMOVE_EXAM_RESULT_ITEM) ) )
			{
				REMOVE_EXAM_RESULT_ITEM RemoveItemInfo = *((REMOVE_EXAM_RESULT_ITEM*)lParam);
				if (m_mapAllDangerItem.FindKey(RemoveItemInfo.uRemoveItem.RemoveItemInfo.dwItemID) >= 0 && 
					TRUE == m_bExamFinished)
				{
					_FixItem(RemoveItemInfo);
				}
			}
		}
		m_lockRemove.Unlock();
	}else if (BkSafeExamItemExOperate::ErrorMsg == nItem)
	{//�ش�������־
		if (1 == lParam)
		{//�������ģ��ʧ��
			m_pDlg->KillTimer(EXAM_TIMER_PROGRESS);
			::MessageBox(m_pDlg->m_hWnd, BkString::Get(IDS_EXAM_1268), NULL, 0);
		}
	}
	else
	{//�ش�ɨ����
		//		m_nFinishedItemCount ++;
		if (nItem < 0 || nItem == 8)
		{
			return 0;
		}

		if( !IsBadReadPtr( (void*)pnms, sizeof(BKSAFE_EXAM_RESULT_ITEM) ) )
		{
			_UpdateExamData(nItem, pnms);
		}

		SetEvent(m_hExamShareDataEvent);//֪ͨ���¹����ڴ��е�����

	}

	return 0;
}

//�������еĻص�����
LRESULT CBeikeSafeExamUIHandler::OnAppExamProgress(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	m_nRealProgress = (DWORD)wParam;

	BKSafe_Exam_ShareData shareData;
	shareData.uMsg = uMsg;
	shareData.cbSize = sizeof(shareData);
	shareData.nItem = -1;
	shareData.u.BKSafe_Exam_Progress.nProgress = m_nRealProgress;
	//m_arrExamShareData.Add(shareData);
	//ɨ�����
	m_arrScanData[uMsg] = shareData;
	SetEvent(m_hExamShareDataEvent);//֪ͨ���¹����ڴ��е�����
	return 0;
}
//�������
LRESULT CBeikeSafeExamUIHandler::OnAppExamOnlyEcho(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam)
{

	return 0;
}

//��ʼ���������̺߳���
void pfnStartExam(void* pParam)
{
	CBeikeSafeExamUIHandler* _pThis = (CBeikeSafeExamUIHandler*)pParam;
	if (NULL == _pThis)
		return;

	//ˢ��ʵʱ������״̬
	//_pThis->UpdatSafemonStateCaption();

	while(WAIT_OBJECT_0 == WaitForSingleObject(_pThis->m_hStartExamEvent, INFINITE))
	{
		EnterCriticalSection(&g_StartExam_cs);
		_pThis->StartExam();
		LeaveCriticalSection(&g_StartExam_cs);
	}

}

//��������
void pfnShareExamData(void* pData)
{
	//return ;//��ʱ���δ˹���


	CBeikeSafeExamUIHandler* _pThis = (CBeikeSafeExamUIHandler*)pData;
	if (NULL == _pThis)
		return;

	//HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_EXAM_RECV);
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, EVENT_EXAM_RECV);
	LPVOID pValue = NULL;
	//static int nCount = 0, nIndex = 0;

	while(TRUE)
	{
		//Sleep(500);

		if (WAIT_OBJECT_0 == WaitForSingleObject(_pThis->m_hExamShareDataEvent, -1))
		{
			//�����ڴ��п�������
			pValue = _pThis->m_ExamPSD.GetData();
			if (NULL != pValue)
			{
				//scan
				POSITION pos = _pThis->m_arrScanData.GetStartPosition();
				int nSize = 0, nIndex = 0, nTotalCount = _pThis->m_arrFixData.GetCount() + _pThis->m_arrScanData.GetCount();
				//size
				memcpy(pValue, &nTotalCount, sizeof(int));
				PBYTE pData = (PBYTE)pValue + sizeof(int);
				while(NULL != pos)
				{
					nSize = nIndex * sizeof(BKSafe_Exam_ShareData);
					BKSafe_Exam_ShareData shareData = _pThis->m_arrScanData.GetNext(pos)->m_value;
					memcpy((pData+nSize), (PBYTE)&shareData, sizeof(BKSafe_Exam_ShareData));
					nIndex++;
				}
				//fix
				pos = _pThis->m_arrFixData.GetStartPosition();
				//nIndex = 0;
				while(NULL != pos)
				{
					nSize = nIndex * sizeof(BKSafe_Exam_ShareData);
					BKSafe_Exam_ShareData shareData = _pThis->m_arrFixData.GetNext(pos)->m_value;
					memcpy((pData+nSize), (PBYTE)&shareData, sizeof(BKSafe_Exam_ShareData));
					nIndex++;
				}

			}
		}

		//::EnterCriticalSection(&_pThis->m_LockShareData);
		/*
		_pThis->m_nShareDataCount = _pThis->m_arrExamShareData.GetCount();
		if (_pThis->m_nShareDataCount <= _pThis->m_nIndexShareData)
		continue;

		_pThis->m_bkSafeLog.WriteLog(L"pfnShareExamData: nCount = %d, nIndex = %d", _pThis->m_nShareDataCount, _pThis->m_nIndexShareData);
		for (_pThis->m_nIndexShareData; _pThis->m_nIndexShareData < _pThis->m_nShareDataCount; _pThis->m_nIndexShareData++)
		{
		if (NULL == hEvent)
		hEvent = CreateEvent(NULL, FALSE, FALSE, EVENT_EXAM_RECV);//OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_EXAM_RECV);
		pValue = _pThis->m_ExamPSD.GetData();
		if (NULL != pValue)
		{
		_pThis->m_bkSafeLog.WriteLog(L"pfnShareExamData: copyData %d", _pThis->m_arrExamShareData[_pThis->m_nIndexShareData].nItem);
		memcpy(pValue, &_pThis->m_arrExamShareData[_pThis->m_nIndexShareData], sizeof(BKSafe_Exam_ShareData));
		SetEvent(_pThis->m_hExamShareDataEvent);

		WaitForSingleObject(hEvent, 1000);
		}
		}
		*/
		//::LeaveCriticalSection(&_pThis->m_LockShareData);
	}

	if (NULL != hEvent)
		CloseHandle(hEvent);

}
void CBeikeSafeExamUIHandler::Init(BOOL bStartExam)
{
	_InitExamItemSort();
	_UpdateExamSetTxt();
	_StartHandShake();//�ֶ�ȥ��һ������
	//	ModifyBwsMonitorState();
	UpdatSafemonStateCaption();
	_CheckDuBa();
	SetTimer(m_pDlg->m_hWnd, TIMER_ID_CHECKINSTALL_DUBA, 5000, NULL);

	m_pDlg->SetItemVisible(IDC_DIV_EXAM_FINISH, FALSE);
	m_pDlg->SetItemVisible(IDC_DIV_EXAM_WORKING, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_LISTVIEW_ID, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_DLG_HISTORY, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_DLG_DIY, FALSE);

	if (0 != _GetExamType())
	{//������ֶ�����Ҫ����UI
		// 		m_pDlg->SetItemVisible(IDC_EXAM_DLG_HISTORY, TRUE);
		m_pDlg->SetItemVisible(IDC_EXAM_DLG_DIY, TRUE);
		_UpdateHistoryInfo();
	}
	else
	{
		//ReportLog(examautostart);
		m_examType = examautostart;
		SetTimer(m_pDlg->m_hWnd, EXAM_TIMER_SHOWLISTVIEW, 50, NULL);
	}

}

void CBeikeSafeExamUIHandler::StartExam(BOOL bExpress)
{
	//	CString strScore;
	m_pDlg->SetItemVisible(IDC_EXAM_IMAG_DIY, FALSE);

	m_bkSafeLog.WriteLog(L"StartExam ...");
	m_dwStartExamTime = ::GetTickCount();
	m_bUserCancelExam = FALSE;
	m_bExamFinished         = FALSE;
	//	m_nFinishedItemCount    = 0;
	m_nShowProgress         = 0;
	m_nStartExamTime			= time(NULL);
	m_nMaxScore = m_nMinScore = m_nMinScore2 = 100;
	//::EnterCriticalSection(&m_LockShareData);
	m_nRealProgress         = m_nDangerCount = m_nFixCount = m_nCancel = 0;
	//::LeaveCriticalSection(&m_LockShareData);
	_UpdateExamScoreImage();

	m_strDangerIDs.Empty();
	//��ʼ�����
	BKSafe_Exam_ShareData examShareData;
	examShareData.cbSize = sizeof(examShareData);
	examShareData.uMsg = MSG_APP_EXAM_SCORE_CHANGE;
	examShareData.nItem = BkSafeExamItem::Invalid;
	examShareData.u.ExamState.nState = 0;
	m_arrScanData[examShareData.nItem] = examShareData;//ɨ���������
	//ˢ�¹����ڴ��е�����
	SetEvent(m_hExamShareDataEvent);


	m_pDlg->SendMessage(MSG_APP_START_EXAM, 0, 0);



	_Module.Exam.Start(bExpress, m_pDlg->m_hWnd, MSG_APP_EXAM_SCORE_CHANGE, MSG_APP_EXAM_PROGRESS);

	m_pDlg->SetTimer(1, 200, NULL);
	m_pDlg->SetTimer(TIMER_ID_EXAMSCORE_ID, 100, NULL);
	m_pDlg->SetTimer(EXAM_TIMER_PROGRESS, 500, NULL);//�ٽ���ʹ�õ�TIMER

}

void CBeikeSafeExamUIHandler::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == EXAM_TIMER_SHOWLISTVIEW)
	{//���������ְ׿��
		if (TRUE == IsWindowVisible(m_pDlg->m_hWnd))
		{
			if (0 == m_pDlg->GetTabCurSel(IDC_TAB_MAIN))
			{
				m_pDlg->SetItemVisible(IDC_EXAM_LISTVIEW_ID, TRUE);
				//SetEvent(m_hStartExamEvent);
				StartExam();
			}
			m_pDlg->KillTimer(nIDEvent);
		}
	}
	if (nIDEvent == EXAM_TIMER_PROGRESS)
	{//�ٽ�����ʹ�õ�TIMER����������ൽ10%
		if(m_nShowProgress >= m_nRealProgress && 
			m_nShowProgress <= 10)
		{
			m_nShowProgress++;
			m_pDlg->SetItemIntAttribute(IDC_PROGRESS_EXAM, "value", m_nShowProgress);
			return;
		}else if (m_nShowProgress < m_nRealProgress ||
			10 == m_nShowProgress)
		{
			m_pDlg->KillTimer(EXAM_TIMER_PROGRESS);
		}
	}
	if (nIDEvent == TIMER_ID_CHECKINSTALL_DUBA)
	{
		if (0 == _CheckDuBa())
		{
			m_pDlg->RemoveFromTodoList(BkSafeExamItem::EXAM_CHECK_AV);
		}
	}

	if (nIDEvent == TIMER_ID_EXAMSCORE_ID)
	{//�����
		if (m_nMaxScore >= (m_nMinScore+2) && 
			m_nMaxScore >= 2)
		{
			m_nMaxScore -= 2;
			_UpdateExamScoreImage();
		}
	}

	if (1 != nIDEvent)
	{
		SetMsgHandled(FALSE);
		return;
	}

	static int s_nAni = 0;

	if (m_bExamFinished)
	{//������֮�󣬸���UI��ʾ
		//		m_pDlg->KillTimer(TIMER_ID_EXAM_KWS_PROGRESS);
		m_pDlg->KillTimer(1);

		m_pDlg->SetItemVisible(IDC_DIV_EXAM_WORKING, FALSE);
		m_pDlg->SetItemVisible(IDC_DIV_EXAM_FINISH, TRUE);
		//
		m_pDlg->SetItemVisible(IDC_LBL_EXAM_RESTART, TRUE);

		//RefreshTodoList();
	}
	else
	{//�������и���UI������
		if (m_nShowProgress < m_nRealProgress && FALSE == m_bUserCancelExam)
		{
			m_pDlg->KillTimer(EXAM_TIMER_PROGRESS);

			if (100 == m_nRealProgress)
				m_nShowProgress = 100;
			else
				m_nShowProgress += 1;

			//m_nShowProgress = m_nRealProgress;
			m_pDlg->SetItemIntAttribute(IDC_PROGRESS_EXAM, "value", m_nShowProgress);
		}
		m_pDlg->SetItemIntAttribute(IDC_IMG_EXAM_ANIMATION, "sub", (s_nAni ++) % 5);
	}

	if (100 == m_nShowProgress)
	{
		m_nMaxScore = m_nMinScore;
		_UpdateExamScoreImage();
		m_bExamFinished = TRUE;
	}
}
//�������
void CBeikeSafeExamUIHandler::OnBkLblExamRestart()
{
	_InitArrayForShareData();
	//m_arrExamShareData.RemoveAll();
	//m_nIndexShareData = m_nShareDataCount =0;

	m_examType = reexam;
	_ResetMapVector();

	m_pDlg->SetItemVisible(IDC_EXAM_DLG_HISTORY, FALSE);
	//	m_pDlg->SetItemVisible(IDC_EXAM_DLG_DIY, FALSE);

	StartExam();
	//SetEvent(m_hStartExamEvent);

	m_pDlg->SetItemVisible(IDC_LBL_EXAM_RESTART, FALSE);//������찴ť
}

void CBeikeSafeExamUIHandler::OnBkBtnExamStop()
{
	m_bUserCancelExam = TRUE;
	m_nCancel = 1;
	m_pDlg->SetItemText(IDC_EXAM_CANCEL_580, BkString::Get(IDS_EXAM_1377));
	m_pDlg->KillTimer(EXAM_TIMER_PROGRESS);
	m_pDlg->KillTimer(TIMER_ID_EXAMSCORE_ID);
	//	m_pDlg->KillTimer(1);
	_Module.Exam.Stop();
}


LRESULT CBeikeSafeExamUIHandler::OnAppEchoFinish(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam)
{


	//	_ShowEngStateText();

	return 0;
}


void CBeikeSafeExamUIHandler::RefreshTodoList()
{
}


void CBeikeSafeExamUIHandler::InitCtrl()
{
	if (NULL == m_pDlg)
		return;

	_LoadGlobalData();

	DWORD dwStyle = WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_OWNERDRAWFIXED|LVS_NOCOLUMNHEADER;
	HWND hWnd = m_pDlg->GetViewHWND();
	if (NULL == hWnd)
		return ;
	//IE�޸� ��Ӧ��LISTVIEW
	m_ExamListView.Create(hWnd, NULL, NULL, dwStyle, 0, IDC_EXAM_LISTVIEW_ID, NULL);
	m_ExamListView.SetExpandRectHand(TRUE);

	DWORD dwExStyle = LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT;
	dwExStyle |= m_ExamListView.GetExtendedListViewStyle();
	m_ExamListView.SetExtendedListViewStyle(dwExStyle);
	m_ExamListView.InsertColumn(0, TEXT(""), LVCFMT_LEFT, 40); 
	m_ExamListView.InsertColumn(1, TEXT(""), LVCFMT_LEFT, 340); 
	m_ExamListView.InsertColumn(2, TEXT(""), LVCFMT_LEFT, 120); 
	m_ExamListView.SetItemHeight(27);
	m_ExamListView.SetSplitLines(FALSE);
	m_ExamListView.SetFullRowUpdateCheckBox(TRUE);
	m_ExamListView.SetSelState(FALSE);
	m_ExamListView.SetNotifyHwnd(m_pDlg->m_hWnd);
	m_ExamListView.SetExTxtHand(FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_LISTVIEW_ID, FALSE);
	m_ExamListView.SetBkColor(RGB(0xFF,0xFF,0xFF));
	m_ExamListView.SetTitleCanClickExpand(TRUE);
	m_ExamListView.SetExpandRectHand(TRUE);

	m_pDlg->SetTimer(TIMER_ID_EXAMSCORE_ID, 100, NULL);

	//init shareData  arr
	_InitArrayForShareData();
	//
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pfnShareExamData, this, 0, 0);
	if (NULL != hThread)
		CloseHandle(hThread);
	hThread = NULL;

}

void CBeikeSafeExamUIHandler::_LoadExamData()
{
	m_ExamListView.SetRedraw(FALSE);

	m_ExamListView.DeleteAllItems();
	_ResetMapVector();
	int nCount = g_ExamItem.GetCount();
	LPLDListViewCtrl_Item lpItem = NULL;
	LPLDListViewCtrl_SubItem lpSubItem = NULL;
	m_bKwsExist = TRUE;//( _IsExistKWS() == 0 );

	for (int i = 0; i < nCount; i++)
	{


		lpItem = new LDListViewCtrl_Item;
		if (NULL == lpItem)
			break;
		lpItem->_uGroup = g_ExamItem[i]._dwItemID;
		lpSubItem = new LDListViewCtrl_SubItem();
		if (NULL == lpSubItem)
			break;
		lpItem->PushSubItem(lpSubItem);
		lpSubItem = new LDListViewCtrl_SubItem();
		if (NULL == lpSubItem)
			break;
		_sntprintf_s(lpSubItem->_pszSubItemInfo, sizeof(lpSubItem->_pszSubItemInfo), TEXT("%s"), g_ExamItem[i]._pszItemCaption);
		lpSubItem->_colorExTxt = TEXT_DEFAULT_COLOR;
		lpSubItem->_ImageID = _GetImageID(-3);
		lpSubItem->_OffsetLeft = 5;
		lpSubItem->_enumType = SUBITEM_TYPE_WITH_IMAGE;
		lpItem->PushSubItem(lpSubItem);
		lpSubItem = new LDListViewCtrl_SubItem();
		if (NULL == lpSubItem)
			break;
		_sntprintf_s(lpSubItem->_pszSubItemInfo, sizeof(lpSubItem->_pszSubItemInfo), TEXT("%s"), g_ExamItem[i]._pszInitState);
		lpSubItem->_colorUrlTxt = URL_COLOR;
		lpSubItem->_uSubItem = g_ExamItem[i]._dwItemID;
		lpSubItem->_colorExTxt = TEXT_DEFAULT_COLOR;
		lpItem->PushSubItem(lpSubItem);
		m_ExamListView.InsertItem(i, lpItem);
		BKSAFE_EXAM_RESULT_ITEM item;
		item.nLevel = -1;
		m_mapCancelScanResult.Add(g_ExamItem[i]._dwItemID, item);
	}
	m_ExamListView.SetRedraw(TRUE);
	m_ExamListView.Invalidate();
}

void CBeikeSafeExamUIHandler::_UpdateExamData(int nItem, BKSAFE_EXAM_RESULT_ITEM *pData)
{
	if (NULL == pData || nItem < 0 )
	{
		return;
	}

	CString strError;

	m_bkSafeLog.WriteLog(L"_UpdateExamData, nItem = %d, nLevel = %d", nItem, pData->nLevel);
	m_mapCancelScanResult.Remove(nItem);//ȡ��һ��
	COLORREF excolor=RGB(156,156,156);
	int _nItem = nItem;

	_SetExamMinScore(nItem, pData->nLevel);

	if (BkSafeExamItemLevel::Safe != pData->nLevel)
	{
		if (m_mapAllDangerItem.FindKey(nItem) < 0)
		{
			m_mapAllDangerItem.Add(nItem, *pData);
		}
		else
		{
			m_mapAllDangerItem.SetAt(nItem, *pData);
		}
	}


	if (BkSafeExamItemLevel::Critical == pData->nLevel )
	{//Σ��
		strError.Format(TEXT("%d/"), nItem);
		m_strDangerIDs += strError;
		if (BkSafeExamItem::CriticalPathVirusScan == nItem)
		{
			//			_InitScanLogCtrl(FALSE);
			SYSTEMTIME localTime;
			GetLocalTime(&localTime);
			strError.Format(BkString::Get(IDS_EXAM_1269), localTime.wHour, localTime.wMinute, localTime.wSecond);
			m_pDlg->SetItemText(IDC_EXAM_TEXT_FINDTROJAN_ID, strError);
			m_pDlg->SetItemVisible(IDC_EXAM_DLG_EXAMSCAN_ID, TRUE);
			//			m_logState = trojan;
		}
		if (m_mapDangerScanResult2.FindKey(nItem) < 0)
		{
			++m_nFixCount;
			++m_nDangerCount;
			m_mapDangerScanResult2.Add(nItem, *pData);
			//_CalcExamScore();
		}
		else
		{
			m_mapDangerScanResult2.SetAt(nItem, *pData);

			return;
		}
		excolor = TEXT_DANGER_COLOR;
	}else if(BkSafeExamItemLevel::Optimization == pData->nLevel)
	{
		if (m_mapOptimization.FindKey(nItem) < 0)
		{
			m_mapOptimization.Add(nItem, *pData);
			//_CalcExamScore();
			++m_nDangerCount;
			++m_nFixCount;
		}
		else
		{
			m_mapOptimization.SetAt(nItem, *pData);
			return;
		}
		excolor = TEXT_DANGER_COLOR;//TEXT_RISK_O_COLOR;
	}else if (BkSafeExamItemLevel::Risk_0 == pData->nLevel ||
		BkSafeExamItemLevel::Scan_Error == pData->nLevel)
	{//����
		strError.Format(TEXT("%d|"), nItem);
		m_strDangerIDs += strError;
		if (m_mapRasikScanResult.FindKey(nItem) < 0)
		{
			m_mapRasikScanResult.Add(nItem, *pData);
			//_CalcExamScore();
			++m_nDangerCount;
			++m_nFixCount;
		}
		else
		{
			m_mapRasikScanResult.SetAt(nItem, *pData);
			return;
		}

		excolor = TEXT_DANGER_COLOR;//TEXT_RISK_O_COLOR;
	}
	else
	{//��ȫ
		//		m_mapSafeScanResult.Add(nItem, *pData);
		if (m_mapSafeScanResult.FindKey(nItem) < 0)
		{
			m_mapSafeScanResult.Add(nItem, *pData);
		}
		else
		{
			m_mapSafeScanResult.SetAt(nItem, *pData);return;
		}

		excolor = TEXT_SAFE_COLOR;
	}

	CString strUpdateText(L""), strScanState(L"");

	_GetTextWithItemLevel(_nItem, pData->nLevel, strUpdateText, strScanState);
	if (BkSafeExamItem::SystemLeakScan == _nItem && BkSafeExamItemLevel::Risk_0 == pData->nLevel)
	{
		strUpdateText.Replace(BkString::Get(IDS_EXAM_1270), BkString::Get(IDS_EXAM_1271));
		strScanState.Replace(BkString::Get(IDS_EXAM_1270), BkString::Get(IDS_EXAM_1271));
	}
	_RefreshExamList(_nItem, strUpdateText, strScanState, excolor, URL_COLOR, _GetImageID(pData->nLevel));

}

void CBeikeSafeExamUIHandler::_GetTextWithItemLevel(int nItem, int nLevel, CString& strOperate, CString& strResult, BOOL bResult)
{	
	strResult = strOperate = TEXT("");
	if (nItem < 0)
		return;

	int nCount = g_ExamResultText.GetCount();

	for (int i = 0; i < nCount; i++)
	{
		if (nItem == g_ExamResultText[i]._dwItemID)
		{

			if (BkSafeExamItemLevel::Safe == nLevel)
			{//��ȫ
				if (TRUE == bResult)
				{
					strOperate = g_ExamResultText[i]._strSafeOperate;	
					strResult = g_ExamResultText[i]._strDefaultCaption;
				}
				else
				{
					strOperate = g_ExamResultText[i]._strSafeOperate;
				}
			}else if (BkSafeExamItemLevel::Risk_0 == nLevel ||
				BkSafeExamItemLevel::Optimization == nLevel)
			{//����
				if (TRUE == bResult)
				{
					strOperate = g_ExamResultText[i]._strDangerOperate;
					strResult = g_ExamResultText[i]._strDangerItemCaption;
				}
				else
				{
					strOperate = g_ExamResultText[i]._strDangerDes;
				}

			}else if (BkSafeExamItemLevel::Critical == nLevel)
			{//Σ��
				if (TRUE == bResult)
				{
					strOperate = g_ExamResultText[i]._strDangerOperate;
					strResult = g_ExamResultText[i]._strDangerItemCaption;
				}
				else
				{
					strOperate = g_ExamResultText[i]._strDangerDes;
				}
			}else if (BkSafeExamItemLevel::Scan_Error == nLevel)
			{
				if (TRUE == bResult)
				{
					strOperate = g_ExamResultText[i]._strErrorOperate;
					strResult = g_ExamResultText[i]._strErrorCaption;
				}
				else
				{
					strOperate = g_ExamResultText[i]._strErrorDes;
				}
			}
			else
			{
				strOperate = g_ExamResultText[i]._strCancelOperate;
				strResult = g_ExamResultText[i]._strDefaultCaption;
			}
			break;
		}
	}

}

void CBeikeSafeExamUIHandler::_RefreshExamList(int nItem, CString strUpdate, CString strScanState, COLORREF extxtcolor, COLORREF urlcolor, int nImageID)
{

	int nCount =  m_ExamListView.GetItemCount();

	if (nItem < 0 || FALSE == ::IsWindow(m_ExamListView.m_hWnd))
		return;

	m_ExamListView.SetRedraw(FALSE);
	for (int i = 0; i < nCount; i++)
	{
		if (FALSE == ::IsWindow(m_ExamListView.m_hWnd))
			return;

		LPLDListViewCtrl_Item pDate = (LPLDListViewCtrl_Item)(m_ExamListView.GetItemData(i));
		if (NULL == pDate  || pDate->_enumItemType == ITEM_TYPE_TITLE || pDate->_arrSubItem.GetSize() <= 2)
			continue;
		LPLDListViewCtrl_SubItem pSubItem = NULL;
		pSubItem = pDate->_arrSubItem[2];
		if (NULL == pSubItem)
			continue;
		if (nItem == pSubItem->_uSubItem)
		{
			_sntprintf_s(pSubItem->_pszSubItemInfo, sizeof(pSubItem->_pszSubItemInfo), TEXT("%s"), strUpdate);
			//_sntprintf_s(pDate->_arrSubItem[1]->_pszSubItemInfo, sizeof(pDate->_arrSubItem[1]->_pszSubItemInfo), TEXT("%s"), strScanState);
			pDate->_arrSubItem[1]->_ImageID = nImageID;
			pDate->_arrSubItem[1]->_OffsetLeft = 5;
			pDate->_arrSubItem[1]->_colorExTxt = extxtcolor;
			pSubItem->_colorExTxt = extxtcolor;
			pSubItem->_colorUrlTxt = urlcolor;
			m_ExamListView.MoveTo(i, 0);			
			break;
		}
	}
	CRect rc;
	m_ExamListView.SetRedraw(TRUE);
	m_ExamListView.GetItemRect(0, rc, LVIR_BOUNDS);
	m_ExamListView.InvalidateRect(&rc);

}

int CBeikeSafeExamUIHandler::_GetImageID(int nLevel)
{
	int nRet = -2;
	if (-1 == nLevel)
	{//��ʼɨ��ͼ��
		nRet = 7;
	}else if (BkSafeExamItemLevel::Safe == nLevel)
	{//��ȫ
		nRet = 2;
	}else if (BkSafeExamItemLevel::Risk_0 == nLevel ||
		BkSafeExamItemLevel::Scan_Error == nLevel)
	{//����
		//nRet = 0;
		nRet = 1;
	}else if (BkSafeExamItemLevel::Optimization == nLevel)
	{
		nRet = 3;
	}
	else if (BkSafeExamItemLevel::Critical == nLevel)
	{//Σ��
		nRet = 1;
	}else if (-3 == nLevel)
	{
		nRet = 4;
	}
	else if (-4 == nLevel)
	{//ignore
		nRet = 9;
	}
	else
		nRet = -1;

	return nRet;

}

void CBeikeSafeExamUIHandler::_ShowExamResultData()
{
	m_ExamListView.SetRedraw(FALSE);
	m_ExamListView.DeleteAllItems();
	m_ExamListView.SetRedraw(TRUE);
	int nCount = 0;
	CString strMsg;


	for (int i = 0; i < m_mapRasikScanResult.GetSize(); i++)
		m_mapDangerScanResult2.Add(m_mapRasikScanResult.GetKeyAt(i), m_mapRasikScanResult.GetValueAt(i));

	_SortMap(m_mapDangerScanResult2);//m_mapDangerScanResult

	//Σ����Ŀ
	//nCount = m_mapDangerScanResult.GetSize();
	nCount = m_mapDangerScanResult2.GetSize();
	CString strCaption("");
	if (nCount > 0)
	{//Σ����Ŀ
		strCaption.Format(BkString::Get(IDS_EXAM_1235), nCount);
		_InsertDangerResultData(strCaption, EXAM_RESULT_DANGER_GROUP_ID, m_mapDangerScanResult2);
	}

	//���Ż���Ŀ
	nCount = m_mapOptimization.GetSize();
	if (nCount > 0)
	{
		strCaption.Format(BkString::Get(IDS_EXAM_1407), nCount);
		_InsertOptResultData(strCaption, EXAM_RESULT_OPT_GROUP_ID, m_mapOptimization);

	}

	//��ȫ��Ŀ
	nCount = m_mapSafeScanResult.GetSize();
	if (nCount > 0)
	{
		strCaption.Format(BkString::Get(IDS_EXAM_1236), nCount);
		_InsertSafeResultData(strCaption, EXAM_RESULT_SAFE_GROUP_ID, m_mapSafeScanResult);
	}

	//ȡ����Ŀ
	nCount = m_mapCancelScanResult.GetSize();
	if (nCount > 0)
	{
		strCaption.Format(BkString::Get(IDS_EXAM_1237), nCount);
		_InsertCancelResultData(strCaption, EXAM_RESULT_CANCEL_GROUP_ID, m_mapCancelScanResult);
	}

}

void CBeikeSafeExamUIHandler::_InsertDangerResultData(LPCTSTR pszTitleCaption, int nGroupID, CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM>& mapData)
{
	LPLDListViewCtrl_Item pItemData = NULL;
	LPLDListViewCtrl_SubItem pSubItemData = NULL;
	int nSum = m_ExamListView.GetItemCount();

	CString strResult, strScanState;
	int nCount = mapData.GetSize();
	if (nCount <= 0)
		return;
	int nLevel = mapData.GetValueAt(0).nLevel;

#ifndef NO_GROUP_TITLE
	if (0 != _tcslen(pszTitleCaption))
	{
		_InsertResultDataTitle(nGroupID, pszTitleCaption, BkSafeExamItemLevel::Critical);
	}
#endif

	int nItem = 0, _nInsertAt = -1;
	CString strMsg;
	for (int i = nCount-1; i >= 0; i--)
	{

		BKSAFE_EXAM_RESULT_ITEM exam;
		exam = mapData.GetValueAt(i);
		nItem = mapData.GetKeyAt(i);
		if (_nInsertAt < 0)
			pItemData = _InsertResultData(nGroupID, nItem, exam, TRUE);
		else
			pItemData = _InsertResultData(nGroupID, nItem, exam, TRUE, ++_nInsertAt);


		if (NULL != pItemData)
		{
			pSubItemData = pItemData->_arrSubItem[1];
			if (pSubItemData != NULL)
			{
				if (BkSafeExamItem::SystemLeakScan == nItem &&  
					TRUE == exam.SafeExamItemEx.bInvalid &&
					exam.SafeExamItemEx.u.ExamLeakEx.nHightLeakCount > 0)
				{//©��
					_sntprintf_s(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), BkString::Get(IDS_EXAM_1264), exam.SafeExamItemEx.u.ExamLeakEx.nHightLeakCount);
				}else if (BkSafeExamItem::ConfigSystemMonitor == nItem)
				{//���
					//if (1 == _Module.Exam.GetUnSafeMonitorCount())
					if (TRUE == exam.SafeExamItemEx.bInvalid &&
						1 == exam.SafeExamItemEx.u.BKSafeMonitor.nDisableCount)
					{
						CString strCaption;
						if (0 == _GetSafeMonitorItemCaption(strCaption, exam.SafeExamItemEx.u.BKSafeMonitor.arrDisableID[0]) && 
							FALSE == strCaption.IsEmpty())
						{
							PRINTF_STR(pSubItemData->_pszSubItemInfo, strCaption);
						}
					}
					else
					{
						pSubItemData = pItemData->_arrSubItem[2];
						if (NULL != pSubItemData)
							PRINTF_STR(pSubItemData->_pszSubItemInfo, BkString::Get(IDS_EXAM_1272));
					}
				}else if (TRUE == exam.SafeExamItemEx.bInvalid &&
					exam.SafeExamItemEx.u.ExamKwsResultEx.nDangerCount > 0 &&
					-1 != _IsKwsExam(nItem))
				{//������޸�
					_GetTextWithItemLevel(nItem, nLevel, strResult, strScanState, TRUE);
					_sntprintf_s(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), BkString::Get(IDS_EXAM_1364), strScanState, exam.SafeExamItemEx.u.ExamKwsResultEx.nDangerCount);

				}
			}
		}

		mapData.RemoveAt(i);
	}

}
LRESULT CBeikeSafeExamUIHandler::OnLDListViewClickExTxt(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DWORD dwCtrlID = HIWORD(lParam);
	int nUrlIndex = LOWORD(lParam);
	int nSel , nSubItem;//= int(wParam);
	nSel = LOWORD(wParam);
	nSubItem = HIWORD(wParam);
	if (nSel < 0)
		return -1;

	if (IDC_EXAM_LISTVIEW_ID == dwCtrlID)
	{
		LPLDListViewCtrl_Item pData = (LPLDListViewCtrl_Item)m_ExamListView.GetItemData(nSel);
		if (NULL == pData)
			return -1;
		LPLDListViewCtrl_SubItem pSubItemData = NULL;//pData->_arrSubItem[2];
		if (ITEM_TYPE_TITLE == pData->_enumItemType)
		{//չ������
			//m_ExamListView.ExpandItem(nSel, !pData->_bExpand);
		}
	}
	SetMsgHandled(FALSE);
	return 0;
}

LRESULT CBeikeSafeExamUIHandler::OnLDListViewClickUrl(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nRet = -1;

	DWORD dwCtrlID = HIWORD(lParam);
	int nUrlIndex = LOWORD(lParam);
	int nSel , nSubItem;//= int(wParam);
	nSel = LOWORD(wParam);
	nSubItem = HIWORD(wParam);
	if (nSel < 0)
		return nRet;

	if (IDC_EXAM_LISTVIEW_ID == dwCtrlID)
	{
		LPLDListViewCtrl_Item pData = (LPLDListViewCtrl_Item)m_ExamListView.GetItemData(nSel);
		if (NULL == pData)
			return nRet;
		LPLDListViewCtrl_SubItem pSubItemData = NULL;//pData->_arrSubItem[2];
		if (ITEM_TYPE_TITLE == pData->_enumItemType)
		{//չ������
			m_ExamListView.ExpandItem(nSel, !pData->_bExpand);


		}else if (2 == nSubItem && 0 == pData->_uResverd[0])
		{//�޸�
			pSubItemData = pData->_arrSubItem[2];
			if (NULL == pSubItemData || pSubItemData->_uSubItem < 0)
				return nRet;
			nRet = _ExamFixOperate(pSubItemData->_uSubItem);
		}else if (2 == nSubItem && 0 != pData->_uResverd[0])
		{//����������
			WORD nItem = 0, nType = 0;
			CRect rc;
			m_ExamListView.GetSubItemRect(nSel, nSubItem, LVIR_BOUNDS, &rc);
			pSubItemData = pData->_arrSubItem[2];
			nItem = LOWORD(pData->_uResverd[0]);
			nType = HIWORD(pData->_uResverd[0]);
			if (EXAM_OPERATE_CANCEL_IGNORE == nType)
			{//ȡ������
				TCHAR pszValue[MAX_PATH] = {0};
				if (BkSafeExamItem::EXAM_GUEST_RUN == nItem)
				{
					PRINTF_STR(pszValue, EXAM_GUEST_STR);
				}
				else if (BkSafeExamItem::EXAM_REMOTE_DESKTOP == nItem)
				{
					PRINTF_STR(pszValue, EXAM_REMOTEDESK_STR);
				}else if (BkSafeExamItem::EXAM_CHECK_AV == nItem)
				{
					PRINTF_STR(pszValue, EXAM_DUBA);
				}

				if (0 != _tcslen(pszValue))
					nRet = _Module.Exam.RemoveLocalLibItem(nItem, (void**)&pszValue);
				if (0 == nRet)
				{
					StringCbPrintf(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), BkString::Get(IDS_EXAM_1333));
					m_ExamListView.InvalidateRect(&rc);
				}

			}else if (EXAM_OPERATE_STARTUP == nType)
			{//��������
				UINT_PTR uRet = IDOK;
				DWORD dwBtnType = MB_OKCANCEL|MB_ICONWARNING;
				if (BkSafeExamItem::EXAM_GUEST_RUN == nItem)
					uRet = CBkSafeMsgBox2::ShowMultLine(BkString::Get(IDS_EXAM_1339), NULL, dwBtnType);
				else if (BkSafeExamItem::EXAM_REMOTE_DESKTOP == nItem)
					uRet = CBkSafeMsgBox2::ShowMultLine(BkString::Get(IDS_EXAM_1340), NULL, dwBtnType);

				if (IDOK != uRet)
					return nRet;
				nRet = _Module.Exam.StartupAnUse(nItem);
				if (0 == nRet)
				{
					if (nItem == BkSafeExamItem::EXAM_GUEST_RUN)
					{
						StringCbPrintf(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), BkString::Get(IDS_EXAM_1331));
					}else if (nItem == BkSafeExamItem::EXAM_REMOTE_DESKTOP)
					{
						StringCbPrintf(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), BkString::Get(IDS_EXAM_1332));
					}
					m_ExamListView.InvalidateRect(&rc);
				}
			}else if (EXAM_OPERATE_VIEW == nType)
			{
				if (nItem == BkSafeExamItem::EXAM_HOSTS_FILE)
				{
// 					CBKSafeExam_ShowHostsFileDlg hostsDlg;
// 					hostsDlg.SetDefTabSel(1);
// 					hostsDlg.DoModal();	
				}else if (nItem == BkSafeExamItem::EXAM_SHARE_RESOUCE)
				{
					CBKExamSafe_ShareResourceDlg shareDlg;
					shareDlg.SetDefSel(1);
					shareDlg.DoModal();
				}
			}
			if (0 == nRet)
				pData->_uResverd[0] = 0;
		}
	}
	SetMsgHandled(FALSE);
	return nRet;
}





int CBeikeSafeExamUIHandler::_ExamFixOperate(int nItem)
{
	int nRet = 0;
	if (nItem < 0)
		return -1;

	BKSAFE_EXAM_RESULT_ITEM exam ;
	int Index = -1;
#if 0//����ʹ��
	nItem = 4;
	Index = m_mapSafeScanResult.FindKey(nItem);
	if (Index >= 0)
	{
		exam = m_mapSafeScanResult.GetValueAt(Index);
	}
#else
	Index = m_mapAllDangerItem.FindKey(nItem);
	if (Index >= 0)
	{
		exam = m_mapAllDangerItem.GetValueAt(Index);
	}
	// 	else
	// 	{
	// 		Index = m_mapOptimization.FindKey(nItem);
	// 		if (Index >= 0)
	// 			exam = m_mapOptimization.GetValueAt(Index);
	// 	}
#endif
	//fix log
	CString strMsg;
	strMsg.Format(TEXT("%d"), nItem);
	_ReportLog(examfixitem, strMsg);

	if (Index >= 0)
	{
		if (4 == nItem)
		{//���ٷ��汾
			CWHRoundRectDialog<CBkSimpleDialog> dlg;
			dlg.Load(IDR_BK_GETVER_DLG);
			dlg.DoModal();			
		}
		else if (BkSafeExamItem::EXAM_SHARE_RESOUCE == nItem)
		{
			CBKExamSafe_ShareResourceDlg shareDlg;
			shareDlg.DoModal();
		}
		// 		else if ( BkSafeExamItem::EXAM_KWS_MON == nItem )
		// 		{//������ܱ���
		// 			CInstallStc::GetGlobalPtr()->ReportOpenKWS(_Module.GetProductVersion(), 5);
		// 			CInstallStc::GetGlobalPtr()->ReportOpenKWS(_Module.GetProductVersion(), 5);
		// 			SAFE_CALL_FUN(m_pDlg, Navigate(BKSFNS_MAKE(BKSFNS_PAGE_IEFIX, BKSFNS_PAGE_KWS)));
		// 		}
		else if (BkSafeExamItem::EXAM_GUEST_RUN == nItem)
		{//���GUEST�˺�
			CBKSafeExam_Guest guest(m_pDlg->m_hWnd, MSG_APP_EXAM_SCORE_CHANGE);
			guest.Load(IDR_BK_EXAM_GUEST);
			guest.SetDlgType(BkSafeExamItem::EXAM_GUEST_RUN);
			guest.DoModal();
		}
		else if (BkSafeExamItem::EXAM_REMOTE_DESKTOP == nItem)
		{
			CBKSafeExam_Guest guest(m_pDlg->m_hWnd, MSG_APP_EXAM_SCORE_CHANGE);
			guest.Load(IDR_BK_EXAM_REMOTEDESK);
			guest.SetDlgType(BkSafeExamItem::EXAM_REMOTE_DESKTOP);
			guest.DoModal();

		}else if (BkSafeExamItem::EXAM_CHECK_AV == nItem)
		{
			CBKSafeExam_Duba duba(m_pDlg->m_hWnd, MSG_APP_EXAM_SCORE_CHANGE);
			duba.Load(IDR_BK_EXAM_DUBA);
			duba.SetDlgType(BkSafeExamItem::EXAM_CHECK_AV);
			duba.DoModal();

		}
		else
		{
			_Module.Exam.FixItem(nItem);
			NotityScanEntra( nItem );
			if (BkSafeExamItem::ConfigSystemMonitor == nItem && 
				1 == _Module.Exam.GetUnSafeMonitorCount())
			{
				UpdatSafemonStateCaption();
			}
		}

		nRet = 0;
	}



	return nRet;
}

void CBeikeSafeExamUIHandler::NotityScanEntra( int nItem )
{

}
//����Զ���컹���ֶ���죬���ݲ�ͬ��ѡ������ͬ��UI��ʾ�߼�
void CBeikeSafeExamUIHandler::_UpdateExamSetTxt()
{//0�Զ����1ÿ�����һ��2�ֶ����
	CString strCaption(TEXT("")),
		strLnkCaption(TEXT(""));
	m_pDlg->SetItemVisible(IDC_EXAM_DLG_SETTINGID_1, FALSE);//�ֶ����
	m_pDlg->SetItemVisible(IDC_EXAM_DLG_SETTINGID_2, FALSE);//�Զ����

	BOOL bFlag = FALSE;
	int nValue = BKSafeConfig::GetAutoExam();
	if (0 == nValue)
	{//�Զ����
		bFlag = TRUE;
		strCaption = BkString::Get(IDS_EXAM_1238);
		strLnkCaption = BkString::Get(IDS_EXAM_1243);
	}else if (1 == nValue)
	{//ÿ�����һ��
		bFlag = TRUE;
		strCaption = BkString::Get(IDS_EXAM_1239);
		strLnkCaption = BkString::Get(IDS_EXAM_1242);
	}else if (2 == nValue)
	{//�ֶ����
		m_pDlg->SetItemVisible(IDC_EXAM_DLG_SETTINGID_1, TRUE);//�ֶ����
	}
	if (TRUE == bFlag)
	{
		m_pDlg->SetItemVisible(IDC_EXAM_DLG_SETTINGID_2, TRUE);//�Զ����
		m_pDlg->SetItemText(IDC_EXAM_TXT_SETTING_ID, strCaption);
		m_pDlg->SetItemText(IDC_EXAM_LNK_SETTING_ID, strLnkCaption);
	}

}

void CBeikeSafeExamUIHandler::OnExamSet()
{
	int nValue = BKSafeConfig::GetAutoExam();
	int nSet = 1;
	if (1 == nValue)
		nSet = 2;
	BKSafeConfig::SetAutoExam(nSet);

	if (2 == nSet)
	{
		_ReportLog(noautoexam);
	}

	_UpdateExamSetTxt();
}

void CBeikeSafeExamUIHandler::_WriteExamLogToIni()
{
	CIniFile IniFile(_GetExamLogFilePath());
	SYSTEMTIME timeCur;
	GetLocalTime(&timeCur);
	CString strTime;
	strTime.Format(TEXT("%04d-%02d-%02d"), timeCur.wYear, timeCur.wMonth, timeCur.wDay);
	IniFile.SetStrValue(TEXT("time"),TEXT("last"), strTime);
	if (m_mapAllDangerItem.GetSize() > 0)
		IniFile.SetIntValue(TEXT("level"), TEXT("last"), m_mapAllDangerItem.GetValueAt(0).nLevel);
	else
		IniFile.SetIntValue(TEXT("level"), TEXT("last"), 0);

	IniFile.SetIntValue(L"ExamScore", L"time", m_nStartExamTime);
	IniFile.SetIntValue(L"ExamScore", L"score", m_nMaxScore);
	IniFile.SetIntValue(L"ExamScore", L"fixcount", m_nFixCount);
	IniFile.SetIntValue(L"ExamScore", L"dangercount", m_nDangerCount);
	IniFile.SetIntValue(L"ExamScore", L"cancel", m_nCancel);

}

void CBeikeSafeExamUIHandler::_GetExamLogFromIni(CString& strTime, int& dwScore, int& nFixCount, 
												 int& nDangerCount, int& nTime, int& nCancel)
{
	CIniFile IniFile(_GetExamLogFilePath());
	TCHAR pszValue[MAX_PATH] = {0};
	if(0 != IniFile.GetStrValue(TEXT("time"), TEXT("last"), pszValue, sizeof(pszValue)))
		return;
	strTime = pszValue;

	//IniFile.GetIntValue(TEXT("level"), TEXT("last"), dwValue);
	IniFile.GetIntValue(L"ExamScore", L"time", nTime);
	IniFile.GetIntValue(L"ExamScore", L"score", dwScore);
	IniFile.GetIntValue(L"ExamScore", L"fixcount", nFixCount);
	IniFile.GetIntValue(L"ExamScore", L"dangercount", nDangerCount);
	IniFile.GetIntValue(L"ExamScore", L"cancel", nCancel);

	if (nTime < 0) nTime = 0;
	//if (dwScore < 0) dwScore = 0;
	if (nFixCount < 0) nFixCount = 0;
	if (nDangerCount < 0) nFixCount = 0;
	if (nFixCount > nDangerCount )nFixCount = nDangerCount= 0;
	if (nCancel < 0) nCancel = 0;

}
//��ȡ�����ʷ��¼��Ϣ
CString CBeikeSafeExamUIHandler::_GetExamLogFilePath()
{
	CString strLogPath("");
	CAppPath::Instance().GetLeidianLogPath(strLogPath, TRUE);
	strLogPath += TEXT("\\exam.log");

	return strLogPath;
}
//����ɨ����ʷ��¼������ɨ������Ϣ
void CBeikeSafeExamUIHandler::_UpdateHistoryInfo()
{
	// 	m_pDlg->SetItemAttribute(1000000, "skinlist", "skin0=examscoresafenum,skin1=examscorerisknum,skin2=examscoredangernum");
	// 	m_pDlg->SetItemAttribute(1000000, "sublist", "sub0=1,sub1=2,sub2=-1");

	CString strTime;
	//	int nlevel;
	CString strCpation, strCaptionEx;
	m_pDlg->SetItemVisible(IDC_EXAM_DLG_HISTORY, TRUE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMAG_DIY, TRUE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_603, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_602, FALSE);
	int dwTxtColor = TEXT_SAFE_COLOR;

	int nScore = -1, nTime = 0, nFixCount = 0,  nDangerCount = 0, nImage = 2, nScoreTxt = 0, nCancel = 0;
	_GetExamLogFromIni(strTime, nScore, nFixCount, nDangerCount, nTime, nCancel);

	if (nScore < 0)
	{//��Ч��������Ϊû�н��й����
		nImage = 3;
		m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_602, TRUE);
		m_pDlg->SetItemText(IDC_EXAM_TXT_HISTORY, BkString::Get(IDS_EXAM_1396));//caption
		m_pDlg->SetItemText(IDC_EXAM_TXT_HISTORY_INFO, BkString::Get(IDS_EXAM_1397));//captionEx
	}
	else
	{//�������������
		m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_603, TRUE);
		CTimeSpan span(time(NULL) - nTime);
		int nLastExamTime = 0;
		if (span.GetDays() > 0)
		{//һ��ǰ����
		}
		else
		{
			if (0 != span.GetTotalHours())
			{
				nLastExamTime = span.GetTotalHours();
				strTime = BkString::Get(IDS_EXAM_1401);
			}
			else if (0 != span.GetTotalMinutes())
			{
				strTime = BkString::Get(IDS_EXAM_1402);
				nLastExamTime = span.GetTotalMinutes();
			}
			else if (0 != span.GetTotalSeconds())
			{
				strTime = BkString::Get(IDS_EXAM_1403);
				nLastExamTime = span.GetTotalSeconds();
			}
		}
		CString strTxtColor;
		strTxtColor = L"C80000";
		if (nLastExamTime > 0)
		{
			if (0 != nFixCount)
				strCpation.Format(BkString::Get(IDS_EXAM_1398), strTxtColor, nLastExamTime, strTime, strTxtColor, nDangerCount, strTxtColor, nFixCount);
			else
				strCpation.Format(BkString::Get(IDS_EXAM_1405), strTxtColor, nLastExamTime, strTime, strTxtColor, nDangerCount);
		}
		else
		{
			if (0 != nFixCount)
				strCpation.Format(BkString::Get(IDS_EXAM_1409), strTxtColor, nDangerCount, strTxtColor, nFixCount);
			else
				strCpation.Format(BkString::Get(IDS_EXAM_1410), strTxtColor, nDangerCount);

		}
		m_pDlg->SetRichText(IDC_EXAM_IMG_SCORE_620, strCpation);

		//�ϴ����÷�
		CStringA strScoreNumSkin = "examscoresafenum";		
		m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_605, FALSE);
		m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_611, FALSE);
		m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_616, FALSE);

		//�÷�״̬
		m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_627, FALSE);
		m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_628, FALSE);
		m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_629, FALSE);
		m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_630, FALSE);
		m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_631, FALSE);
		m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_632, FALSE);

		if (0 == nCancel)
		{//û��ȡ�������
			int nLevel = -1;
			_ParseScoreForUpdateUI(nScore, nLevel, nImage, dwTxtColor);
			if (nLevel >= 0)
				m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_627+nLevel, TRUE);

			/*
			_ParseScoreForUpdateUI(nScore, strScoreNumSkin, strCaptionEx, strCpation, nImage, dwTxtColor, nScoreTxt);		

			CSimpleArray<int> n, b;
			n.Add(0);n.Add(0);n.Add(0);
			b = n;
			_ParseScore(nScore, n, b);


			int nIndex = 0;


			DWORD dwID = 0, dwEndID = 0;
			if (0 != b[0])
			{
			nIndex = 0;
			dwID = IDC_EXAM_IMG_SCORE_606;
			// 				dwEndID = IDC_EXAM_IMG_SCORE_608;
			m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_605, TRUE);
			m_pDlg->SetItemIntAttribute(IDC_EXAM_IMG_SCORE_609, "sub", nScoreTxt);
			m_pDlg->SetItemColorAttribute(IDC_EXAM_IMG_SCORE_610, "crtext", dwTxtColor);
			m_pDlg->SetItemText(IDC_EXAM_IMG_SCORE_610, strCaptionEx);
			}else if (0 != b[1])
			{
			nIndex = 1;
			m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_611, TRUE);
			dwID = IDC_EXAM_IMG_SCORE_612;
			//dwEndID = IDC_EXAM_IMG_SCORE_613;
			m_pDlg->SetItemIntAttribute(IDC_EXAM_IMG_SCORE_614, "sub", nScoreTxt);
			m_pDlg->SetItemText(IDC_EXAM_IMG_SCORE_615, strCaptionEx);
			m_pDlg->SetItemColorAttribute(IDC_EXAM_IMG_SCORE_615, "crtext", dwTxtColor);
			}else if (0 != b[2])
			{
			nIndex = 2;
			m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_616, TRUE);
			dwID = IDC_EXAM_IMG_SCORE_617;
			//dwEndID = IDC_EXAM_IMG_SCORE_617;
			m_pDlg->SetItemIntAttribute(IDC_EXAM_IMG_SCORE_618, "sub", nScoreTxt);
			m_pDlg->SetItemText(IDC_EXAM_IMG_SCORE_619, strCaptionEx);
			m_pDlg->SetItemColorAttribute(IDC_EXAM_IMG_SCORE_619, "crtext", dwTxtColor);

			}
			CStringA strTmp, strSkin, strSub;
			int nSkin = 0;
			for (int i = nIndex; i < 3; i++)
			{
			strTmp.Format("skin%d=%s,", nSkin, strScoreNumSkin);
			strSkin += strTmp;
			strTmp.Format("sub%d=%d,", nSkin, n[i]);
			++nSkin;
			strSub += strTmp;
			}

			if (FALSE == strSkin.IsEmpty() &&
			FALSE == strSub.IsEmpty() &&
			0 != dwID)
			{
			m_pDlg->SetItemAttribute(dwID, "skinlist", strSkin);
			m_pDlg->SetItemAttribute(dwID, "sublist", strSub);

			}*/

		}
		else
		{//�ϴ�ȡ�����
			m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_604, FALSE);
			m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_602, TRUE);
			m_pDlg->SetItemText(IDC_EXAM_TXT_HISTORY, BkString::Get(IDS_EXAM_1422));//caption

			if (nDangerCount > 0)
			{
				nImage = 1;
				m_pDlg->SetItemColorAttribute(IDC_EXAM_TXT_HISTORY, "crtext", TEXT_RISK_O_COLOR);	
			}
			else 
				nImage = 3;

		}


	}


	m_pDlg->SetItemColorAttribute(IDC_EXAM_IMG_SCORE_604, "crtext", dwTxtColor);	
	m_pDlg->SetItemIntAttribute(IDC_EXAM_IMAG_DIY, "sub", nImage);//image


}

//�������
void CBeikeSafeExamUIHandler::OnBkStartExam()
{
	//ReportLog(startexam);
	m_examType = startexam;

	m_pDlg->SetItemVisible(IDC_EXAM_DLG_HISTORY, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_DLG_DIY, FALSE);

	m_pDlg->SetItemVisible(IDC_DIV_EXAM_FINISH, FALSE);
	m_pDlg->SetItemVisible(IDC_DIV_EXAM_WORKING, TRUE);
	m_pDlg->SetItemText(IDC_EXAM_CANCEL_580, BkString::Get(IDS_EXAM_1376));
	m_pDlg->SetItemVisible(IDC_EXAM_LISTVIEW_ID, TRUE);

	//SetEvent(m_hStartExamEvent);
	StartExam();
}


LRESULT CBeikeSafeExamUIHandler::OnLDListViewExpandItem(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nRet = -1;

	DWORD dwCtrlID = HIWORD(lParam);
	int nExpand = LOWORD(lParam);
	int nSel = int(wParam);
	if (nSel < 0)
		return nRet;

	if (IDC_EXAM_LISTVIEW_ID == dwCtrlID)
	{
		LPLDListViewCtrl_Item pData = (LPLDListViewCtrl_Item)m_ExamListView.GetItemData(nSel);
		if (NULL == pData || ITEM_TYPE_TITLE != pData->_enumItemType)
			return nRet;
		LPLDListViewCtrl_SubItem pSubItemData = pData->_arrSubItem[0];
		if (NULL == pSubItemData || FALSE == pData->_bUserExpand)
			return nRet;

		if (0 == nExpand)
		{
			pSubItemData->_ImageID = 5;
			//_HideSafeItems(nSel);
			//_HideExamResultItems(pData->_uGroup, nSel);
		}
		else
		{
			pSubItemData->_ImageID = 6;
			//_ExpendExamResultItems(pData->_uGroup, nSel);
			//_ShowSafeItems(nSel);

		}

		CRect rc;
		m_ExamListView.GetItemRect(nSel, &rc, LVIR_BOUNDS);
		m_ExamListView.InvalidateRect(&rc);
	}
	SetMsgHandled(FALSE);
	return nRet;
}



//��һ�����ֲ���
void CBeikeSafeExamUIHandler::_StartHandShake()
{
	m_pDlg->SetItemVisible(IDC_DIV_ECHO_CONNECT_ERROR, FALSE);
	m_pDlg->SetItemVisible(IDC_DIV_ECHO_OK, FALSE);
	m_pDlg->SetItemVisible(IDC_DIV_ECHO_NOFINISH, TRUE);
	//	_Module.Exam.Echo(m_pDlg->m_hWnd, MSG_APP_EXAM_ONLY_ECHO);
	m_CheckSecurityCloudTimer.Startup(m_pDlg->m_hWnd, &m_Logic);
}

COLORREF CBeikeSafeExamUIHandler::_GetTxtColor(int nLevel)
{
	COLORREF excolor=TEXT_COLOR;
	if (BkSafeExamItemLevel::Critical == nLevel)
	{//Σ��
		excolor = TEXT_DANGER_COLOR;
	}else if (BkSafeExamItemLevel::Risk_0 == nLevel ||
		BkSafeExamItemLevel::Scan_Error == nLevel)
	{//����
		excolor = TEXT_DANGER_COLOR;//TEXT_RISK_O_COLOR;
	}else if (BkSafeExamItemLevel::Optimization == nLevel)
	{
		excolor = RGB(66,66,66);
	}
	else if (BkSafeExamItemLevel::Safe == nLevel)
	{//��ȫ
		excolor = TEXT_COLORT_DEFAULT_RESULT;//TEXT_SAFE_COLOR;
	}else if(-1 == nLevel)
	{//cancel
		excolor = TEXT_COLORT_DEFAULT_RESULT;
	}else if (BkSafeExamItemLevel::Unknown == nLevel)
	{
		excolor = 0;
	}

	return excolor;
}

int CBeikeSafeExamUIHandler::_FixItem(REMOVE_EXAM_RESULT_ITEM RemoveExamItem)
{
	int nRet = -1;
	int nItem = RemoveExamItem.uRemoveItem.RemoveItemInfo.dwItemID;
	int nCount = m_ExamListView.GetItemCount();
	int nIndex = m_mapAllDangerItem.FindKey(nItem);
	m_bkSafeLog.WriteLog(L"_FixItem: nCount = %d, nIndex = %d, nItem = %d", nCount, nIndex, nItem);
	if ((nItem <= BkSafeExamItem::Invalid && nItem != BkSafeExamItem::Count) || 
		nIndex < 0 ||
		nCount < 1)
		return nRet;


	int nDangerCount = m_mapAllDangerItem.GetSize();
	if (nDangerCount <= 0)
		return nRet;

	if (BkSafeExamItem::EXAM_KWS_MON == nItem &&
		0 != _IsAllKwsOpen())
		return nRet;

	if (nItem == BkSafeExamItem::ConfigSystemMonitor)
		UpdatSafemonStateCaption();

	if (nItem == BkSafeExamItem::EXAM_TRASH)
	{
		int dwRet = 0;
		BKSafeExamItemEx::BKSafeExamEx ExamItemData;
		if (0 == _Module.Exam.ExamItem(nItem, ExamItemData) && 
			TRUE == ExamItemData.bInvalid &&
			0 != ExamItemData.u.Trash.nSize)
			return nRet;
	}
	int nUpdateCount = 0;
	if (nItem == BkSafeExamItem::EXAM_CHECK_UPDATE)
	{
		_CheckSoftWareUpdate(nUpdateCount);
	}


	m_bkSafeLog.WriteLog(L"_FixItem: StartFix....");
	CString strMsg;
	for (int i = 0; i < nCount ; i++)
	{
		LPLDListViewCtrl_Item pItemData = (LPLDListViewCtrl_Item)(m_ExamListView.GetItemData(i));
		if (NULL == pItemData || pItemData->_arrSubItem.GetSize() < 3)
			continue;
		LPLDListViewCtrl_SubItem pSubItemData = (LPLDListViewCtrl_SubItem)(pItemData->_arrSubItem[2]);

		int nFlag = -1;
		BKSAFE_EXAM_RESULT_ITEM exam;
		exam = m_mapAllDangerItem.GetValueAt(nIndex);

		if (pSubItemData->_uSubItem == nItem &&
			TRUE == exam.SafeExamItemEx.bInvalid &&
			nItem == RemoveExamItem.uRemoveItem.RemoveItemInfo.dwItemID &&
			exam.SafeExamItemEx.u.BKSafeUpdate.nNeedUpdateCount > 0 &&
			BkSafeExamItem::EXAM_CHECK_UPDATE == nItem && 
			nUpdateCount > 0)
		{//�������
			exam.SafeExamItemEx.u.BKSafeUpdate.nNeedUpdateCount = nUpdateCount;
			pSubItemData = (LPLDListViewCtrl_SubItem)(pItemData->_arrSubItem[1]);
			_sntprintf_s(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), BkString::Get(IDS_EXAM_1392), nUpdateCount);
			m_mapAllDangerItem.SetAt(nItem, exam);
			if (0 != nUpdateCount)
			{
				break;
			}
			else
			{
				CString strCaption, strState;
				pSubItemData = (LPLDListViewCtrl_SubItem)(pItemData->_arrSubItem[1]);
				//_GetTextWithItemLevel(nItem, exam.nLevel, strCaption, strState, TRUE);
				_sntprintf_s(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), L"%s", BkString::Get(IDS_EXAM_1430));
				pSubItemData = (LPLDListViewCtrl_SubItem)(pItemData->_arrSubItem[2]);

			}
		}else if (nItem == BkSafeExamItem::SystemLeakScan)
		{
		}else if (nItem == BkSafeExamItem::ConfigSystemMonitor)
		{
		}
		else if (pSubItemData->_uSubItem == nItem &&
			TRUE == exam.SafeExamItemEx.bInvalid &&
			nItem == RemoveExamItem.uRemoveItem.RemoveItemInfo.dwItemID &&
			exam.SafeExamItemEx.u.ExamKwsResultEx.nDangerCount > 0 && 
			-1 != _IsKwsExam(nItem))
		{//����
			int nDanger = exam.SafeExamItemEx.u.ExamKwsResultEx.nDangerCount - RemoveExamItem.uRemoveItem.RemoveItemInfo.dwRemoveDangerCount;
			exam.SafeExamItemEx.u.ExamKwsResultEx.nDangerCount--;
			m_mapAllDangerItem.SetAt(nItem, exam);
			if (nDanger > 0)
			{
				CString strCaption, strState;
				pSubItemData = (LPLDListViewCtrl_SubItem)(pItemData->_arrSubItem[1]);
				_GetTextWithItemLevel(nItem, exam.nLevel, strCaption, strState, TRUE);
				_sntprintf_s(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), BkString::Get(IDS_EXAM_1364), strState, nDanger);
				break;
			}
			else
			{
				CString strCaption, strState;
				pSubItemData = (LPLDListViewCtrl_SubItem)(pItemData->_arrSubItem[1]);
				_GetTextWithItemLevel(nItem, exam.nLevel, strCaption, strState, TRUE);
				_sntprintf_s(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), L"%s", strState);
				pSubItemData = (LPLDListViewCtrl_SubItem)(pItemData->_arrSubItem[2]);
			}
		}

		if (nIndex >= 0)
		{
			m_bkSafeLog.WriteLog(L"_FixItem: _uSubItem = %d, nItem = %d", pSubItemData->_uSubItem, nItem);
			if (pSubItemData->_uSubItem == nItem)
			{
				--m_nFixCount;
				m_mapAllDangerItem.Remove(nItem);
				//m_mapRasikScanResult.Remove(nItem);
				nFlag = 1;
			}
		}

		if (nFlag >= 0)
		{
			nDangerCount--;
			PRINTF_STR(pSubItemData->_pszSubItemInfo, BkString::Get(IDS_EXAM_1273));
			pSubItemData->_colorExTxt = TEXT_COLORT_DEFAULT_RESULT;

			pSubItemData = pItemData->_arrSubItem[1];
			if (NULL != pSubItemData)
			{
				CString strCaption = pSubItemData->_pszSubItemInfo;
				strCaption.Replace(BkString::Get(IDS_EXAM_1260), TEXT(""));
				//_sntprintf_s(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), TEXT("%s"), strCaption);
				PRINTF_STR(pSubItemData->_pszSubItemInfo, strCaption);
				pSubItemData->_colorExTxt = TEXT_COLORT_DEFAULT_RESULT;
				pSubItemData->_ImageID = _GetImageID(BkSafeExamItemLevel::Safe);
			}
			CRect rc;
			m_ExamListView.GetItemRect(i, &rc, LVIR_BOUNDS);
			m_ExamListView.InvalidateRect(&rc);

			if (1 == nFlag)
				break;

			continue;
		}
	}

	_UpdateExamResult();
	_WriteExamLogToIni();//write log

	return nRet;
}
//resize listview
void CBeikeSafeExamUIHandler::OnListViewResize(CRect rcSize)
{
	if (rcSize.IsRectEmpty() || FALSE == ::IsWindow(m_ExamListView.m_hWnd))
		return;
	m_ExamListView.SetColumnWidth(2, 180);
	m_ExamListView.SetColumnWidth(0, 31);
	int nScrollWidth = GetSystemMetrics(SM_CXVSCROLL);
	if (0 == nScrollWidth)
		nScrollWidth = 20;
	m_ExamListView.SetColumnWidth(1, rcSize.Width()-211-nScrollWidth);

}
//�Ƚϸ�����ʱ�򣬺ͱ��ص�ϵͳʱ��ֱ�ӵļ��������Ϊ��λ������
LONG CBeikeSafeExamUIHandler::_CompareFileTime(CString strHistoryTime)
{//2010-03-01
	if (TRUE == strHistoryTime.IsEmpty())
		return 0;
	SYSTEMTIME systemTime;
	ZeroMemory(&systemTime, sizeof(SYSTEMTIME));
	CString tmp;
	tmp = strHistoryTime.Left(4);
	systemTime.wYear = (WORD)(_ttol(tmp));
	systemTime.wMonth = (WORD)(_ttol(strHistoryTime.Mid(5,2)));
	systemTime.wDay = (WORD)(_ttol(strHistoryTime.Right(2)));
	SYSTEMTIME curTime;
	ZeroMemory(&curTime, sizeof(SYSTEMTIME));
	GetLocalTime(&curTime);
	curTime.wHour = 0;
	curTime.wMinute = 0;
	curTime.wSecond = 0;
	curTime.wDayOfWeek = 0;
	curTime.wMilliseconds = 0;
	double dbHistory, dbCur;
	if (FALSE == SystemTimeToVariantTime(&systemTime, &dbHistory))
		return 0;
	if (FALSE == SystemTimeToVariantTime(&curTime, &dbCur))
		return 0;

	return (int)(dbCur-dbHistory);

}
void CBeikeSafeExamUIHandler::_SortMap(CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM>& mapData)
{
	int nCount = 0;
	//����Σ�յ��������򣬸���ɨ����ʾ��˳�����µ���
	CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM> mapTmp;
	nCount = m_ExamItemSort.GetSize();//g_ExamItem.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		DWORD dwID = m_ExamItemSort[i];//g_ExamItem[i]._dwItemID;
		int nIndex = mapData.FindKey(dwID);
		if (nIndex >= 0)
		{
			mapTmp.Add(dwID, mapData.GetValueAt(nIndex));
			mapData.Remove(dwID);
		}
	}
	nCount = g_ExamItem.GetCount();
	for (int i = 0; i < nCount && mapData.GetSize() > 0; i++)
	{
		DWORD dwID = g_ExamItem[i]._dwItemID;
		int nIndex = mapData.FindKey(dwID);
		if (nIndex >= 0)
		{
			mapTmp.Add(dwID, mapData.GetValueAt(nIndex));
		}
	}
	mapData.RemoveAll();
	nCount = mapTmp.GetSize();
	for(int i = nCount - 1 ; i >= 0; i--)
	{
		mapData.Add(mapTmp.GetKeyAt(i), mapTmp.GetValueAt(i));
	}
}


//����>=0�������������ڵ���
int CBeikeSafeExamUIHandler::_GroupIDExist(int nGroupID)
{
	int nRet = -1;

	if (nGroupID < 0)
		return nRet;

	int nCount = m_ExamListView.GetItemCount();

	for (int i = 0; i < nCount; i++)
	{
		LPLDListViewCtrl_Item pData = (LPLDListViewCtrl_Item)m_ExamListView.GetItemData(i);
		if (NULL != pData && ITEM_TYPE_TITLE == pData->_enumItemType)
		{
			LPLDListViewCtrl_SubItem pSubItemData = pData->_arrSubItem[0];
			if (NULL != pSubItemData && nGroupID == pSubItemData->_nGroupID)
				return i;
		}
	}


	return nRet;
}


void CBeikeSafeExamUIHandler::_ResetMapVector()
{
	//	m_mapDangerScanResult.RemoveAll();
	m_mapRasikScanResult.RemoveAll();
	m_mapSafeScanResult.RemoveAll();
	m_mapCancelScanResult.RemoveAll();
	//	m_mapAllScanResult.RemoveAll();
	//	m_mapSafeScanResult2.RemoveAll();
	m_mapDangerScanResult2.RemoveAll();
	m_mapOptimization.RemoveAll();
	m_mapAllDangerItem.RemoveAll();
	//	m_arrIgnoreItemID.RemoveAll();
}

LPLDListViewCtrl_Item CBeikeSafeExamUIHandler::_InsertResultDataTitle(int nGroupID, LPCTSTR pszTitleCaption,int nLevel, 
																	  int nImageID/*=6*/, ENUM_LISTVIEW_FONT fontType /*= FONT_BOLD*/)
{
	if (nGroupID < 0)
		return NULL;

	LPLDListViewCtrl_Item pItemData = NULL;
	LPLDListViewCtrl_SubItem pSubItemData = NULL;

	pItemData = new LDListViewCtrl_Item;
	pItemData->_uGroup = nGroupID;
	pItemData->_enumItemType = ITEM_TYPE_TITLE;
	pSubItemData = new LDListViewCtrl_SubItem;
	pSubItemData->_ImageID = nImageID;
	_sntprintf_s(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), TEXT("%s"), pszTitleCaption);
	pSubItemData->_enumFont = fontType;
	pSubItemData->_enumType = SUBITEM_TYPE_WITH_IMAGE;
	pSubItemData->_OffsetLeft = 25;
	pSubItemData->_colorUrlTxt = URL_COLOR;
	pSubItemData->_colorExTxt = _GetTitleTxtColor(nLevel);
	pSubItemData->_bExTxtHand = TRUE;
	pItemData->PushSubItem(pSubItemData);
	m_ExamListView.InsertItem(m_ExamListView.GetItemCount(), pItemData);

	return pItemData;
}

COLORREF CBeikeSafeExamUIHandler::_GetTitleTxtColor(int nLevel)
{
	COLORREF excolor=TEXT_COLOR;
	if (BkSafeExamItemLevel::Critical == nLevel ||
		BkSafeExamItemLevel::Scan_Error == nLevel ||
		BkSafeExamItemLevel::Risk_0 == nLevel)
	{//Σ��
		excolor = TEXT_DANGER_COLOR;
	}else if (BkSafeExamItemLevel::Optimization == nLevel)
	{//����
		excolor = TEXT_COLOR_OPT;
	}
	else if (BkSafeExamItemLevel::Safe == nLevel)
	{//��ȫ
		excolor = TEXT_SAFE_COLOR;
	}else if(-1 == nLevel)
	{//cancel
		excolor = 0;
	}else if (BkSafeExamItemLevel::Unknown == nLevel)
	{
		excolor = 0;
	}

	return excolor;
}

void CBeikeSafeExamUIHandler::_InsertOptResultData(LPCTSTR pszTitleCaption, int nGroupID, CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM>& mapData)
{
	LPLDListViewCtrl_Item pItemData = NULL;
	LPLDListViewCtrl_SubItem pSubItemData = NULL;
	int nSum = m_ExamListView.GetItemCount();

	CString strResult, strScanState;
	int nCount = mapData.GetSize();
	if (nCount <= 0)
		return;
	int nLevel = mapData.GetValueAt(0).nLevel;

#ifndef NO_GROUP_TITLE
	if (0 != _tcslen(pszTitleCaption))
	{
		_InsertResultDataTitle(nGroupID, pszTitleCaption, BkSafeExamItemLevel::Optimization);
		nSum++;
	}
#endif


	int nItem = 0, ShowCount = 0, _nInsertAt = -1;
	for (int i = nCount-1; i >= 0 ; i--)
	{

		BKSAFE_EXAM_RESULT_ITEM exam;
		exam = mapData.GetValueAt(i);
		nItem = mapData.GetKeyAt(i);
		if (_nInsertAt < 0)
			pItemData = _InsertResultData(nGroupID, nItem, exam, TRUE);
		else
			pItemData = _InsertResultData(nGroupID, nItem, exam, TRUE, ++_nInsertAt);

		if (NULL != pItemData)
		{
			pSubItemData = pItemData->_arrSubItem[1];

			if (TRUE == exam.SafeExamItemEx.bInvalid &&
				BkSafeExamItem::EXAM_CHECK_UPDATE == nItem && 
				exam.SafeExamItemEx.u.BKSafeUpdate.nNeedUpdateCount > 0)
			{
				_sntprintf_s(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), BkString::Get(IDS_EXAM_1392), exam.SafeExamItemEx.u.BKSafeUpdate.nNeedUpdateCount);
			}
		}
		mapData.RemoveAt(i);
		++ShowCount;
		++nSum;
	}
}
void CBeikeSafeExamUIHandler::_InsertSafeResultData(LPCTSTR pszTitleCaption, int nGroupID, CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM>& mapData)
{
	LPLDListViewCtrl_Item pItemData = NULL;
	LPLDListViewCtrl_SubItem pSubItemData = NULL;
	int nSum = m_ExamListView.GetItemCount();

	CString strResult, strScanState;
	int nCount = mapData.GetSize();
	if (nCount <= 0)
		return;
	int nLevel = mapData.GetValueAt(0).nLevel;

#ifndef NO_GROUP_TITLE
	if (0 != _tcslen(pszTitleCaption))
	{
		_InsertResultDataTitle(nGroupID, pszTitleCaption, BkSafeExamItemLevel::Safe);
		nSum++;
	}
#endif


	int nItem = 0, ShowCount = 0, _nInsertAt = -1;
	for (int i = nCount-1; i >= 0 ; i--)
	{
		BKSAFE_EXAM_RESULT_ITEM exam;
		exam = mapData.GetValueAt(i);
		nItem = mapData.GetKeyAt(i);
		if (_nInsertAt < 0)
			_InsertResultData(nGroupID, nItem, exam, TRUE);
		else
			_InsertResultData(nGroupID, nItem, exam, TRUE, ++_nInsertAt);
		mapData.RemoveAt(i);
		++ShowCount;
		++nSum;
	}

}

LPLDListViewCtrl_Item CBeikeSafeExamUIHandler::_InsertResultData(int nGroupID, int nItem, BKSAFE_EXAM_RESULT_ITEM exam, 
																 BOOL bReloadCaption, int nInsertAt/* = -1*/)
{
	LPLDListViewCtrl_Item pItemData = NULL;
	LPLDListViewCtrl_SubItem pSubItemData = NULL;
	int _nInsertAt = m_ExamListView.GetItemCount();

	if (nItem < 0)
		return pItemData;

	if ( nInsertAt < 0 )
		_nInsertAt = nInsertAt;

	pSubItemData = new LDListViewCtrl_SubItem;
	pItemData = new LDListViewCtrl_Item;
	CString strOperate, strScanState;
	_GetTextWithItemLevel(nItem, exam.nLevel, strOperate, strScanState, bReloadCaption);

	if (BkSafeExamItem::SystemLeakScan == nItem && BkSafeExamItemLevel::Critical == exam.nLevel)
	{
		strOperate.Replace(BkString::Get(IDS_EXAM_1270), BkString::Get(IDS_EXAM_1271));
		strScanState.Replace(BkString::Get(IDS_EXAM_1270), BkString::Get(IDS_EXAM_1271));
	}
	else if (BkSafeExamItem::EXAM_GUEST_RUN == nItem && BkSafeExamItemLevel::Safe == exam.nLevel)
	{//guest�˻�
		BOOL bHave = FALSE;
		WORD dwFixType = 0;//100��ʾȡ�����ԣ�200��ʾ����
		if (S_OK == _Module.Exam.LocalLibIsHaveItem(BkSafeExamItem::EXAM_GUEST_RUN, bHave) && TRUE == bHave)
		{//����GUEST�����Թ�����ʾȡ������
			dwFixType = EXAM_OPERATE_CANCEL_IGNORE;
			strScanState.Replace(BkString::Get(IDS_EXAM_1056), BkString::Get(IDS_EXAM_1337));
			strOperate.Replace(BkString::Get(IDS_EXAM_1169), BkString::Get(IDS_EXAM_1328));
		}
		else
		{
			dwFixType = EXAM_OPERATE_STARTUP;
			strOperate.Replace(BkString::Get(IDS_EXAM_1169), BkString::Get(IDS_EXAM_1329));
			strScanState.Replace(BkString::Get(IDS_EXAM_1056), BkString::Get(IDS_EXAM_1335));
		}
		pItemData->_uResverd[0] = MAKELONG(nItem, dwFixType);

	}else if (BkSafeExamItem::EXAM_REMOTE_DESKTOP == nItem && BkSafeExamItemLevel::Safe == exam.nLevel)
	{//Զ������
		BOOL bHave = FALSE;
		WORD dwFixType = 0;//100��ʾȡ�����ԣ�200��ʾ����
		if (S_OK == _Module.Exam.LocalLibIsHaveItem(BkSafeExamItem::EXAM_REMOTE_DESKTOP, bHave) && TRUE == bHave)
		{
			dwFixType = EXAM_OPERATE_CANCEL_IGNORE;
			strOperate.Replace(BkString::Get(IDS_EXAM_1172), BkString::Get(IDS_EXAM_1328));
			pItemData->_uResverd[0] = MAKELONG(nItem, EXAM_OPERATE_VIEW);
			strScanState.Replace(BkString::Get(IDS_EXAM_1059), BkString::Get(IDS_EXAM_1338));
		}
		else
		{
			dwFixType = EXAM_OPERATE_STARTUP;
			strOperate.Replace(BkString::Get(IDS_EXAM_1172), BkString::Get(IDS_EXAM_1330));
			strScanState.Replace(BkString::Get(IDS_EXAM_1059), BkString::Get(IDS_EXAM_1336));
			pItemData->_uResverd[0] = MAKELONG(nItem, EXAM_OPERATE_VIEW);
		}
		pItemData->_uResverd[0] = MAKELONG(nItem, dwFixType);
	}else if (BkSafeExamItem::EXAM_HOSTS_FILE == nItem && BkSafeExamItemLevel::Safe == exam.nLevel)
	{//HOST
		BOOL bHave = FALSE;
		_Module.Exam.LocalLibIsHaveItem(BkSafeExamItem::EXAM_HOSTS_FILE, bHave);
		if (TRUE == bHave)
		{
			strOperate.Replace(BkString::Get(IDS_EXAM_1160), BkString::Get(IDS_EXAM_1334));
			pItemData->_uResverd[0] = MAKELONG(nItem, EXAM_OPERATE_VIEW);
		}
	}else if (BkSafeExamItem::EXAM_SHARE_RESOUCE == nItem && BkSafeExamItemLevel::Safe == exam.nLevel)
	{//share resource
		BOOL bHave = FALSE;
		_Module.Exam.LocalLibIsHaveItem(BkSafeExamItem::EXAM_SHARE_RESOUCE, bHave);
		if (TRUE == bHave)
		{
			strOperate.Replace(BkString::Get(IDS_EXAM_1171), BkString::Get(IDS_EXAM_1334));
			pItemData->_uResverd[0] = MAKELONG(nItem, EXAM_OPERATE_VIEW);
		}
	}else if (BkSafeExamItem::EXAM_CHECK_AV == nItem && BkSafeExamItemLevel::Safe == exam.nLevel)
	{
		BOOL bHave = FALSE;
		WORD dwFixType = 0;//100��ʾȡ�����ԣ�200��ʾ����
		if (S_OK == _Module.Exam.LocalLibIsHaveItem(BkSafeExamItem::EXAM_CHECK_AV, bHave) && TRUE == bHave)
		{//����AV�����Թ�����ʾȡ������
			dwFixType = EXAM_OPERATE_CANCEL_IGNORE;
			strScanState.Replace(BkString::Get(IDS_EXAM_1415), BkString::Get(IDS_EXAM_1420));
			strOperate.Replace(BkString::Get(IDS_EXAM_1416), BkString::Get(IDS_EXAM_1421));
		}
		pItemData->_uResverd[0] = MAKELONG(nItem, dwFixType);

	}


	//pItemData->_uResverd[0] = nItem;
	pItemData->PushSubItem(pSubItemData);//ͼ��
	pItemData->_uGroup = nGroupID;
	pSubItemData = new LDListViewCtrl_SubItem;
	_sntprintf_s(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), TEXT("%s"), strScanState);
	pSubItemData->_enumType = SUBITEM_TYPE_WITH_IMAGE;
	pSubItemData->_ImageID = _GetImageID(exam.nLevel);
	pSubItemData->_OffsetLeft = 5;
	pSubItemData->_colorUrlTxt = URL_COLOR;
	pSubItemData->_colorExTxt = _GetTxtColor(exam.nLevel);
	pSubItemData->_nGroupID = nGroupID;
	pSubItemData->_uSubItem = nItem;
	pItemData->PushSubItem(pSubItemData);//״̬
	pSubItemData = new LDListViewCtrl_SubItem;
	_sntprintf_s(pSubItemData->_pszSubItemInfo, sizeof(pSubItemData->_pszSubItemInfo), TEXT("%s"), strOperate);
	pSubItemData->_colorUrlTxt = URL_COLOR;
	pSubItemData->_uSubItem = nItem;
	pItemData->_uGroup = nGroupID;
	pSubItemData->_colorExTxt = _GetTxtColor(exam.nLevel);
	pItemData->PushSubItem(pSubItemData);//���
	if (FALSE == ::IsWindow(m_ExamListView.m_hWnd))
		return pItemData;
	m_ExamListView.InsertItem(_nInsertAt, pItemData);

	return pItemData;
}
void CBeikeSafeExamUIHandler::_InsertCancelResultData(LPCTSTR pszTitleCaption, int nGroupID, CSimpleMap<int, BKSAFE_EXAM_RESULT_ITEM>& mapData)
{
	LPLDListViewCtrl_Item pItemData = NULL;
	LPLDListViewCtrl_SubItem pSubItemData = NULL;
	int nSum = m_ExamListView.GetItemCount();

	CString strResult, strScanState;
	int nCount = mapData.GetSize();
	if (nCount <= 0)
		return;
	int nLevel = mapData.GetValueAt(0).nLevel;
	int ShowCount = 0;

	// 	if (TRUE == _IsHaveGroupHideInfo(EXAM_RESULT_SAFE_GROUP_ID))
	// 		return;

#ifndef NO_GROUP_TITLE
	if (0 != _tcslen(pszTitleCaption))
	{
		_InsertResultDataTitle(nGroupID, pszTitleCaption, BkSafeExamItemLevel::Unknown);
		nSum++;
	}
#endif

	int nItem = 0, _nInsertAt = -1;

	for (int i = nCount-1; i >= 0 ; i--)
	{
		BKSAFE_EXAM_RESULT_ITEM exam;
		exam = mapData.GetValueAt(i);
		nItem = mapData.GetKeyAt(i);
		if (_nInsertAt < 0)
			_InsertResultData(nGroupID, nItem, exam, TRUE);
		else
			_InsertResultData(nGroupID, nItem, exam, TRUE, ++_nInsertAt);

		mapData.RemoveAt(i);
		++ShowCount;
		++nSum;
	}

}

//����������ʱ�򣬼��һ���Ƿ���Ҫ�����������
int CBeikeSafeExamUIHandler::_GetExamType()
{
	int nRet = 0;
	int nValue = -1;
	nValue = BKSafeConfig::GetAutoExam();	
	_UpdateExamSetTxt();
	//   m_bExamRunned = bStartExam && BKSafeConfig::GetAutoExam();
	if (2 == nValue)
	{//�ֶ����
		nRet = -1;
	}
	else if (0 == nValue)
	{//ÿ�δ��������Զ����
		;
	}else if (1 == nValue)
	{//ÿ�����һ��
		CString strTime("");
		int nLevel = -1, nFixCount, nDangerCount, nTime, nCancel;
		_GetExamLogFromIni(strTime, nLevel, nFixCount, nDangerCount, nTime, nCancel);//��ȡ��һ�ε����ʱ��
		if (FALSE == strTime.IsEmpty())
		{//���Ի�ȡ��һ�����ʱ��
			if (_CompareFileTime(strTime) < 1)
			{//һ��ֻ��������
				nRet = -1;
			}
		}
	}

	return nRet;
}
//���µ����ĵ�ǰ������õ�״̬
void CBeikeSafeExamUIHandler::UpdateExamSetting()
{
	if (2 == BKSafeConfig::GetAutoExam())
	{
		_ReportLog(noautoexam);
	}

	_UpdateExamSetTxt();
}


void CBeikeSafeExamUIHandler::FullScan()
{
	_Module.Navigate(TEXT("ui_virscan_full"));
}




LRESULT CBeikeSafeExamUIHandler::OnExamErrorMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (FALSE == ::IsWindow(m_pDlg->m_hWnd))
		return -1;

	if (MSG_APP_EXAM_ERROR == uMsg)
	{
		if (1 == wParam)
		{//�������ģ��ʧ��
			m_pDlg->KillTimer(EXAM_TIMER_PROGRESS);
			::MessageBox(m_pDlg->m_hWnd, BkString::Get(IDS_EXAM_1275), NULL, 0);
		}
	}
	return 0;
}




void CBeikeSafeExamUIHandler::_ReportLog(enumUpLogType ReportType, CString strLog/* = TEXT("")*/)
{
	CString strURL(TEXT(""));
	switch(ReportType)
	{
	case installeng://��װ��������
		{
			//strURL.Format(BkString::Get(IDS_EXAM_1435), 1, CInstallStc::GetGlobalPtr()->GetPID(),_Module.GetProductVersion());
		}
		break;
	case scantrojan://��ɱľ��
		{
		}
		break;
	case startexam://��ʼ���
		{
			//strURL.Format(EXAM_STARTEXAM, 1, CInstallStc::GetGlobalPtr()->GetPID(),_Module.GetProductVersion());
		}
		break;
	case examautostart://�Զ���ʼ���
		{
			//strURL.Format(EXAM_STARTEXAM, 2, CInstallStc::GetGlobalPtr()->GetPID(),_Module.GetProductVersion());
		}
		break;
	case reexam://�������
		{
			//strURL.Format(EXAM_REEXAM, 1, CInstallStc::GetGlobalPtr()->GetPID(),_Module.GetProductVersion());
		}
		break;
	case noautoexam://ȡ���Զ����
		{
		}
		break;
	case  unknownhosts:
		{
			//strURL.Format(BkString::Get(IDS_EXAM_1434), strLog, CInstallStc::GetGlobalPtr()->GetPID(),_Module.GetProductVersion());
		}
		break;
	case examtime:
		{
			DWORD dwTotalTime = ::GetTickCount() - m_dwStartExamTime;

		}
		break;
	case examresult:
		{
			//��쵽��Σ����Ŀ
			if (FALSE == m_strDangerIDs.IsEmpty())
			{
			}
		}
		break;
	case  examfixitem:
		{
		}
		break;
	case examechofalied:
		{
		}
		break;
	case homepageopt:
		{
		}
		break;
	default:
		{
			strURL.Empty();
		}
		break;
	}
}

void CBeikeSafeExamUIHandler::OnBkOperate1()
{
	SAFE_CALL_FUN(m_pDlg, Navigate(BKSFNS_MAKE(BKSFNS_PAGE_IEFIX, BKSFNS_PAGE_PROTECTION)));
	_ReportLog(homepageopt, L"1");
}

void CBeikeSafeExamUIHandler::OnBkOperate2()
{
	SAFE_CALL_FUN(m_pDlg, Navigate(BKSFNS_MAKE(BKSFNS_PAGE_VIRSCAN, BKSFNS_VIRSCAN_SYSFIX)));

	_ReportLog(homepageopt, L"2");
}

void CBeikeSafeExamUIHandler::OnBkOperate3()
{
	_ReportLog(homepageopt, L"3");
}

void CBeikeSafeExamUIHandler::OnBkOperate4()
{//����
	SAFE_CALL_FUN(m_pDlg, Navigate(BKSFNS_MAKE(BKSFNS_PAGE_SYSTEM_CLEAR, BKSFNS_SYSOPT_CLR_HENJI)));
	_ReportLog(homepageopt, L"4");
}

void CBeikeSafeExamUIHandler::OnBkOperate5()
{
}

void CBeikeSafeExamUIHandler::OnBkOperate6()
{//�����Ϸ
	 	SAFE_CALL_FUN(m_pDlg, Navigate(BKSFNS_MAKE(BKSFNS_SOFTMGR, BKSFNS_SOFTMGR_PAGE_HOTGAME)));
	 //	CSysOptStc::Instance().ReportHomePageSysOpt(BKSFNS_SYSOPT_CLR_SHOUSHEN, _Module.GetProductVersion());
	_ReportLog(homepageopt, L"6");
}

void CBeikeSafeExamUIHandler::OnBkOperate7()
{//ע�������
	_ReportLog(homepageopt, L"7");
}

void CBeikeSafeExamUIHandler::OnBkOperate8()
{//��������
	SAFE_CALL_FUN(m_pDlg, Navigate(BKSFNS_MAKE(BKSFNS_PAGE_SYSTEM_OPTIMIZE, BKSFNS_SYSOPT_RUN_OPT)));
	_ReportLog(homepageopt, L"8");
}

void CBeikeSafeExamUIHandler::OnBkOperate9()
{//���ɨ��

	SAFE_CALL_FUN(m_pDlg, Navigate(BKSFNS_MAKE(BKSFNS_PAGE_VIRSCAN, BKSFNS_VIRSCAN_PLUG)));


/*
	CString strPath;
	CAppPath::Instance().GetLeidianAppPath(strPath);
	strPath.Append(L"\\kmspeed.exe");
	//::EnableMenuItem(m_hFloatWndMenu, ID_FLOATWNDMENU_OPEN_NETSPEED, MF_ENABLED);
	if (FALSE == PathFileExists(strPath))
	{//�������л���������ϵͳ���߼�
		SAFE_CALL_FUN(m_pDlg, Navigate(BKSFNS_MAKE(BKSFNS_PAGE_SYSTEM_OPTIMIZE, BKSFNS_SYSOPT_SYSTOOLS)));
	}
	else if (0 == CVerifyFileFunc::GetPtr()->CheckKingSoftFileSigner(strPath))
	{//������ڲ���ǩ���Ϸ�ֱ�ӵ���
		ShellExecute(NULL, _T("open"), strPath, NULL, NULL, SW_SHOW);
	}*/

	_ReportLog(homepageopt, L"9");
}

void CBeikeSafeExamUIHandler::OnBkSetSafemon()
{
	SAFE_CALL_FUN(m_pDlg, Navigate(BKSFNS_MAKE(BKSFNS_PAGE_PROTECTION, BKSFNS_PAGE_PROTECTION_COMMON)));
}

void CBeikeSafeExamUIHandler::UpdatSafemonStateCaption(BOOL bKWSStatusRefresh /* = TRUE */)
{
	LPCTSTR pszCaption[] = {BkString::Get(IDS_EXAM_1288),
		BkString::Get(IDS_EXAM_1289),
		BkString::Get(IDS_EXAM_1290),
		BkString::Get(IDS_EXAM_1291),
		BkString::Get(IDS_EXAM_1292)};
	CSafeMonitorTrayShell safeMonitor;
	CString strCaption(TEXT(""));
	COLORREF dwColorTxt = TEXT_SAFE_COLOR;
	BOOL bAllMonitorOn = TRUE;

	DWORD dwMonitorIDList[] = {
		SM_ID_RISK, 
		SM_ID_PROCESS, 
		SM_ID_UDISK, 
		SM_ID_LEAK
	};

	CSafeMonitorTrayShell MonitorShell;

	for (int i = 0; i < ARRAYSIZE(dwMonitorIDList) && bAllMonitorOn; i ++)
	{
		//�����64λϵͳ��췢��ʱ���̼�ػ�����ҳ���û�п����Ļ�������Ϊû�з���,��ʱ64Ϊϵͳ�²�֧�����������
		if (TRUE == _Module.Exam.IsWin64() &&
			(SM_ID_PROCESS == dwMonitorIDList[i]))
		{
			continue;
		}

		bAllMonitorOn &= MonitorShell.GetMonitorRun(dwMonitorIDList[i]);
	}

	if (FALSE == bAllMonitorOn)
	{
		dwColorTxt = TEXT_DANGER_COLOR;
		strCaption = pszCaption[0];
	}
	else
	{
		strCaption = pszCaption[1];
	}

	if (FALSE == strCaption.IsEmpty())
	{
		SAFE_CALL_FUN(m_pDlg, SetItemText(IDC_EXAM_BTN_CLEAN_GBG_ID, strCaption));
		m_pDlg->SetItemColorAttribute(IDC_EXAM_BTN_CLEAN_GBG_ID, "crtext", dwColorTxt);
	}

}

int CBeikeSafeExamUIHandler::_GetSafeMonitorItemCaption(CString& strCaption, int nItemID)
{
	int nRet = -1;
	strCaption.Empty();
	CSafeMonitorTrayShell safeMonitor;
	int nCount = g_SafeMonitorItem.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		// 		if (TRUE == _Module.Exam.IsWin64())
		// 		{
		// 			if (SM_ID_PROCESS == g_SafeMonitorItem[i].dwItemID)
		// 				continue;
		// 		}

		//if (FALSE == safeMonitor.GetMonitorRun(g_SafeMonitorItem[i].dwItemID))
		if (g_SafeMonitorItem[i].dwItemID == nItemID)
		{
			nRet = 0;
			strCaption = g_SafeMonitorItem[i].strCaption;
			break;
		}
	}

	return nRet;
}

void CBeikeSafeExamUIHandler::ModifyMonitorState(int nType)
{
	UpdatSafemonStateCaption();
}


LRESULT CBeikeSafeExamUIHandler::OnFullScanTrojan(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (MSG_APP_FULL_SCAN_TROJAN == uMsg)
	{
		FullScan();
	}
	return 0;
}


int CBeikeSafeExamUIHandler::_RetryEcho()
{
	//	_SetEngStateVisable(FALSE);
	//	m_pDlg->SetItemVisible(IDC_EXAM_DLG_ENG_INIT_ID, TRUE);
	_StartHandShake();

	return 0;
}

void CBeikeSafeExamUIHandler::Echo()
{
	if (FALSE == m_bEcho)
	{
		_RetryEcho();
	}
}

void CBeikeSafeExamUIHandler::_LoadGlobalData()
{
	//�������ܼ�ص���ĿID
	ExamPubFunc::CExamPubFunc::GetPubFuncPtr()->GetKwsExamItem(m_arrKwsExamItem);

	//���ɨ��ĳ�ʼ��ʾ״̬
	CString strText = BkString::Get(IDS_EXAM_1012);

	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::CriticalPathVirusScan,  								BkString::Get(IDS_EXAM_1013), strText));	// �ؼ�Ŀ¼����ɨ��->1
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::SystemLeakScan,		 								BkString::Get(IDS_EXAM_1014), strText));	// ϵͳ©��ɨ��->2
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::MalwareScan,			 								BkString::Get(IDS_EXAM_1015), strText));	// ������ɨ��->3
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::HandShake,				 								BkString::Get(IDS_EXAM_1016), strText));	// ��֤�ٷ��汾->4
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::ConfigSystemMonitor,	 								BkString::Get(IDS_EXAM_1017), strText));	// ���״̬->7
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_GPEDIT_RUN,		 								BkString::Get(IDS_EXAM_1027), strText));	//���������Ƿ����->27
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_GUEST_RUN,		 								BkString::Get(IDS_EXAM_1028), strText));	//���GUEST�˻��Ƿ����->28
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_HIDE_FOLDER_RUN,	 								BkString::Get(IDS_EXAM_1029), strText));	//��������ļ����Ƿ����->29
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_SHARE_RESOUCE,	 								BkString::Get(IDS_EXAM_1030), strText));	//��⹲����Դ->30
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_REMOTE_DESKTOP,	 								BkString::Get(IDS_EXAM_1031), strText));	//���Զ������->31
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_KWS_MON,			 								BkString::Get(IDS_EXAM_1293), strText));	//������ܱ���->32
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_TRASH,			 								BkString::Get(IDS_EXAM_1303), strText));	//���ϵͳ���Ƿ��������->34
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_DRIVERORDIRECTORYOPEN,							BkString::Get(IDS_EXAM_1323), strText));	//�����̡��ļ��д��Ƿ�����쳣->35
	//���޸����������
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_HOMEPAGE,											BkString::Get(IDS_EXAM_1018), strText));	//����������ҳ�Ƿ񱻶���۸�ָ���쳣��ַ->11
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_DESKTOP_EXCEPTION_ICON,							BkString::Get(IDS_EXAM_1019), strText));	//����Ƿ������å����ƹ���쳣����ͼ��->40
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_IE_LNKFILE_PARAM,									BkString::Get(IDS_EXAM_1020), strText));	//�������ݷ�ʽ�Ƿ񱻶���۸�->12
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_DESKTOP_SYSTEM_EXCEPTION_ICON,    				BkString::Get(IDS_EXAM_1021), strText));	//��ⳣ������ͼ���Ƿ񱻶���۸�->39
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_IE_BROWSE,										BkString::Get(IDS_EXAM_1022), strText));	//���Internetѡ���IE����������Ƿ�����쳣->21
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_IE_DEFAULT_SEARCH_ENG,							BkString::Get(IDS_EXAM_1023), strText));	//��������Ĭ�����������Ƿ�����쳣->16
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_NOTIE_LNK,										BkString::Get(IDS_EXAM_1024), strText));	//����IE������������Ŀ�ݷ�ʽ�Ƿ񱻶���۸�->38
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_FAVORITES_URL,									BkString::Get(IDS_EXAM_1025), strText));	//����ղؼ��Ƿ���ڶ����ƹ����ַ->36
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_HTML_FILE,										BkString::Get(IDS_EXAM_1026), strText));	//���httpЭ�鼰��ҳ�ļ������Ƿ�����->22
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_SYSTEM_EXCEPTION, 								BkString::Get(IDS_EXAM_1341), strText));	//����Ƿ����������ϵͳ�쳣����->37
	//  [10/23/2010 zhangbaoliang]
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_RUNOPT_ONKEY, 									BkString::Get(IDS_EXAM_1382), strText));	//����Ƿ���ڲ���Ҫ����������������->41
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_CHECK_AV, 										BkString::Get(IDS_EXAM_1415), strText));	//����Ƿ���ڲ���Ҫ����������������->41
	g_ExamItem.Add(EXAM_ITEM(BkSafeExamItem::EXAM_CHECK_UPDATE, 									BkString::Get(IDS_EXAM_1387), strText));	//����Ƿ���ڲ���Ҫ����������������->41


	strText = BkString::Get(IDS_EXAM_1116);
	//												ID												strDefCaption				  strSafeOperate				strDangerCaption			  strDangerDes 					strDangerOperate		     strCancelCaption|strCancelOperate strErrorCaption strErrorOperate
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::CriticalPathVirusScan,					BkString::Get(IDS_EXAM_1013), BkString::Get(IDS_EXAM_1145), BkString::Get(IDS_EXAM_1117), BkString::Get(IDS_EXAM_1088), BkString::Get(IDS_EXAM_1173), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::SystemLeakScan,							BkString::Get(IDS_EXAM_1014), BkString::Get(IDS_EXAM_1146), BkString::Get(IDS_EXAM_1118), BkString::Get(IDS_EXAM_1089), BkString::Get(IDS_EXAM_1174), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::MalwareScan,								BkString::Get(IDS_EXAM_1015), BkString::Get(IDS_EXAM_1147), BkString::Get(IDS_EXAM_1119), BkString::Get(IDS_EXAM_1090), BkString::Get(IDS_EXAM_1175), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::HandShake,								BkString::Get(IDS_EXAM_1016), BkString::Get(IDS_EXAM_1148), BkString::Get(IDS_EXAM_1120), BkString::Get(IDS_EXAM_1091), BkString::Get(IDS_EXAM_1176), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::ConfigSystemMonitor,						BkString::Get(IDS_EXAM_1017), BkString::Get(IDS_EXAM_1150), BkString::Get(IDS_EXAM_1122), BkString::Get(IDS_EXAM_1093), BkString::Get(IDS_EXAM_1178), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_GPEDIT_RUN,							BkString::Get(IDS_EXAM_1027), BkString::Get(IDS_EXAM_1168), BkString::Get(IDS_EXAM_1140), BkString::Get(IDS_EXAM_1111), BkString::Get(IDS_EXAM_1196), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_GUEST_RUN,							BkString::Get(IDS_EXAM_1028), BkString::Get(IDS_EXAM_1169), BkString::Get(IDS_EXAM_1141), BkString::Get(IDS_EXAM_1112), BkString::Get(IDS_EXAM_1197), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_HIDE_FOLDER_RUN,						BkString::Get(IDS_EXAM_1029), BkString::Get(IDS_EXAM_1170), BkString::Get(IDS_EXAM_1142), BkString::Get(IDS_EXAM_1113), BkString::Get(IDS_EXAM_1198), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_SHARE_RESOUCE,						BkString::Get(IDS_EXAM_1030), BkString::Get(IDS_EXAM_1171), BkString::Get(IDS_EXAM_1143), BkString::Get(IDS_EXAM_1114), BkString::Get(IDS_EXAM_1199), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_REMOTE_DESKTOP,						BkString::Get(IDS_EXAM_1031), BkString::Get(IDS_EXAM_1172), BkString::Get(IDS_EXAM_1144), BkString::Get(IDS_EXAM_1115), BkString::Get(IDS_EXAM_1200), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_KWS_MON,								BkString::Get(IDS_EXAM_1293), BkString::Get(IDS_EXAM_1298), BkString::Get(IDS_EXAM_1297), BkString::Get(IDS_EXAM_1296), BkString::Get(IDS_EXAM_1299), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_TRASH,								BkString::Get(IDS_EXAM_1303), BkString::Get(IDS_EXAM_1305), BkString::Get(IDS_EXAM_1304), BkString::Get(IDS_EXAM_1307), BkString::Get(IDS_EXAM_1306), NULL, strText, BkString::Get(IDS_EXAM_1321), BkString::Get(IDS_EXAM_1322), BkString::Get(IDS_EXAM_1365)));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_DRIVERORDIRECTORYOPEN,				BkString::Get(IDS_EXAM_1323), BkString::Get(IDS_EXAM_1327), BkString::Get(IDS_EXAM_1324), BkString::Get(IDS_EXAM_1326), BkString::Get(IDS_EXAM_1363), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_HOMEPAGE,							BkString::Get(IDS_EXAM_1018), BkString::Get(IDS_EXAM_1152), BkString::Get(IDS_EXAM_1124), BkString::Get(IDS_EXAM_1095), BkString::Get(IDS_EXAM_1363), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_DESKTOP_EXCEPTION_ICON,				BkString::Get(IDS_EXAM_1019), BkString::Get(IDS_EXAM_1343), BkString::Get(IDS_EXAM_1344), BkString::Get(IDS_EXAM_1345), BkString::Get(IDS_EXAM_1363), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_IE_LNKFILE_PARAM,					BkString::Get(IDS_EXAM_1020), BkString::Get(IDS_EXAM_1153), BkString::Get(IDS_EXAM_1125), BkString::Get(IDS_EXAM_1096), BkString::Get(IDS_EXAM_1363), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_DESKTOP_SYSTEM_EXCEPTION_ICON,		BkString::Get(IDS_EXAM_1021), BkString::Get(IDS_EXAM_1348), BkString::Get(IDS_EXAM_1349), BkString::Get(IDS_EXAM_1350), BkString::Get(IDS_EXAM_1363), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_IE_BROWSE,							BkString::Get(IDS_EXAM_1022), BkString::Get(IDS_EXAM_1162), BkString::Get(IDS_EXAM_1134), BkString::Get(IDS_EXAM_1105), BkString::Get(IDS_EXAM_1363), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_IE_DEFAULT_SEARCH_ENG,				BkString::Get(IDS_EXAM_1023), BkString::Get(IDS_EXAM_1157), BkString::Get(IDS_EXAM_1129), BkString::Get(IDS_EXAM_1100), BkString::Get(IDS_EXAM_1363), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_NOTIE_LNK,							BkString::Get(IDS_EXAM_1024), BkString::Get(IDS_EXAM_1352), BkString::Get(IDS_EXAM_1353), BkString::Get(IDS_EXAM_1354), BkString::Get(IDS_EXAM_1363), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_FAVORITES_URL,						BkString::Get(IDS_EXAM_1025), BkString::Get(IDS_EXAM_1356), BkString::Get(IDS_EXAM_1357), BkString::Get(IDS_EXAM_1358), BkString::Get(IDS_EXAM_1363), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_HTML_FILE,							BkString::Get(IDS_EXAM_1026), BkString::Get(IDS_EXAM_1163), BkString::Get(IDS_EXAM_1135), BkString::Get(IDS_EXAM_1106), BkString::Get(IDS_EXAM_1363), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_SYSTEM_EXCEPTION, 					BkString::Get(IDS_EXAM_1341), BkString::Get(IDS_EXAM_1360), BkString::Get(IDS_EXAM_1361), BkString::Get(IDS_EXAM_1362), BkString::Get(IDS_EXAM_1363), NULL, strText));
	//  [10/23/2010 zhangbaoliang]
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_RUNOPT_ONKEY, 						BkString::Get(IDS_EXAM_1382), BkString::Get(IDS_EXAM_1383), BkString::Get(IDS_EXAM_1423), BkString::Get(IDS_EXAM_1385), BkString::Get(IDS_EXAM_1386), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_CHECK_AV, 						BkString::Get(IDS_EXAM_1415), BkString::Get(IDS_EXAM_1416), BkString::Get(IDS_EXAM_1418), BkString::Get(IDS_EXAM_1429), BkString::Get(IDS_EXAM_1419), NULL, strText));
	g_ExamResultText.Add(EXAM_SCAN_RESULT(BkSafeExamItem::EXAM_CHECK_UPDATE, 						BkString::Get(IDS_EXAM_1387), BkString::Get(IDS_EXAM_1388), BkString::Get(IDS_EXAM_1390), BkString::Get(IDS_EXAM_1390), BkString::Get(IDS_EXAM_1391), NULL, strText));


	g_SafeMonitorItem.Add(SAFE_MONITOR_ITEM(SM_ID_PROCESS,  BkString::Get(IDS_EXAM_1229)));
	g_SafeMonitorItem.Add(SAFE_MONITOR_ITEM(SM_ID_RISK,     BkString::Get(IDS_EXAM_1230)));
	g_SafeMonitorItem.Add(SAFE_MONITOR_ITEM(SM_ID_UDISK,    BkString::Get(IDS_EXAM_1231)));
	g_SafeMonitorItem.Add(SAFE_MONITOR_ITEM(SM_ID_LEAK,     BkString::Get(IDS_EXAM_1232)));

	g_SafeMonitorItem.Add(SAFE_MONITOR_ITEM(SM_ID_KWS,     BkString::Get(IDS_EXAM_1233)));
	g_SafeMonitorItem.Add(SAFE_MONITOR_ITEM(SM_ID_KWS_SAFE_DOWN,     BkString::Get(IDS_EXAM_1412)));
}

int CBeikeSafeExamUIHandler::_IsKwsExam(int nItem)
{
	return m_arrKwsExamItem.Find(nItem);
}

#if 0
void CBeikeSafeExamUIHandler::ModifyBwsMonitorState()
{
	CString strCaption = L"";
	DWORD dwColorTxt = TEXT_SAFE_COLOR; 
	BOOL bKwsIsExist = 0;//( _IsExistKWS() == 0 );

	//������δ��װ���ܳ���2�Σ��򲻼������
	BOOL bKwsAllOpen = _IsAllKwsOpen() == 0;
	if( bKwsAllOpen && bKwsIsExist )
	{//��ȫ
		strCaption = BkString::Get(IDS_EXAM_1368);
	}
	else
	{//Σ��
		dwColorTxt = TEXT_DANGER_COLOR;
		strCaption = BkString::Get(IDS_EXAM_1367);
	}

	if (FALSE == strCaption.IsEmpty())
	{
		SAFE_CALL_FUN(m_pDlg, SetItemText(IDC_EXAM_LNK_TXT_568, strCaption));
		m_pDlg->SetItemColorAttribute(IDC_EXAM_LNK_TXT_568, "crtext", dwColorTxt);
	}

}
#endif

void CBeikeSafeExamUIHandler::OnBkSetKwsSafemon()
{
	SAFE_CALL_FUN(m_pDlg, Navigate(BKSFNS_MAKE(BKSFNS_PAGE_IEFIX, BKSFNS_PAGE_KWS)));
}

void CBeikeSafeExamUIHandler::_UpdateExamResultTitle()
{
#if 0
	m_nMaxScore = 80;
#endif

	m_pDlg->SetItemVisible(IDC_DIV_EXAM_WORKING, FALSE);
	m_pDlg->SetItemVisible(IDC_DIV_EXAM_FINISH, TRUE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMAG_DIY, TRUE);
	//m_pDlg->SetItemText(IDC_EXAM_TEXT_526, BkString::Get(IDS_EXAM_1414));
	int nLevel = -1, dwTxtColor = TEXT_SAFE_COLOR, dwImage = 0, dwScoreText = 0;;
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_621, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_622, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_623, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_624, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_625, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_626, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_TEXT_526, FALSE);
	_ParseScoreForUpdateUI(m_nMinScore, nLevel, dwImage, dwTxtColor);


	CString strCaption = L"",
		strDes	   = BkString::Get(IDS_EXAM_1371),
		strtmp = L"";

	if (0 != m_nFixCount)
	{
		strtmp.Format(L"%d", m_nFixCount);
		strDes.Format(BkString::Get(IDS_EXAM_1395), L"8C0000", strtmp);
		strDes += BkString::Get(IDS_EXAM_1423+nLevel);

	}

	if (TRUE == _Module.Exam.Canceled() )
	{//����û��Ѿ�ȡ��
		m_pDlg->SetItemVisible(IDC_EXAM_TEXT_526, TRUE);
		if (0 == m_nDangerCount)
			strDes.Format(BkString::Get(IDS_EXAM_1406), L"6D6D6D", BkString::Get(IDS_EXAM_1375));
		else
			strDes.Format(BkString::Get(IDS_EXAM_1411), L"8C0000", strtmp);

		m_pDlg->SetItemText(IDC_EXAM_TEXT_526, BkString::Get(IDS_EXAM_1413));
		m_pDlg->SetItemAttribute(IDC_EXAM_TEXT_526, "class", "examtitle");
		dwTxtColor = TEXT_RISK_O_COLOR;
	}
	else
	{
		if (nLevel >= 0)
		{
			m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_621+nLevel, TRUE);
		}

		m_pDlg->SetItemAttribute(IDC_EXAM_TEXT_526, "class", "examscoretitle");
	}

	if (FALSE == strCaption.IsEmpty())
	{
		m_pDlg->SetItemIntAttribute(IDC_EXAM_IMAG_DIY, "sub", dwImage);//image
		m_pDlg->SetRichText(IDC_EXAM_TEXT_524, strDes);
	}


	m_pDlg->SetItemColorAttribute(IDC_EXAM_TEXT_526, "crtext", dwTxtColor);
	m_pDlg->SetRichText(IDC_EXAM_TEXT_524, strDes);




	/*
	m_pDlg->SetItemVisible(IDC_DIV_EXAM_WORKING, FALSE);
	m_pDlg->SetItemVisible(IDC_DIV_EXAM_FINISH, TRUE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMAG_DIY, TRUE);
	m_pDlg->SetItemText(IDC_EXAM_TEXT_526, BkString::Get(IDS_EXAM_1414));
	CString strCaption = L"",
	strDes	   = BkString::Get(IDS_EXAM_1371),
	strColor = L"",
	strtmp = L"";
	int   dwTxtColor = TEXT_SAFE_COLOR, dwImage = 0, dwScoreText = 0;



	CStringA strSkin;
	_ParseScoreForUpdateUI(m_nMaxScore, strSkin, strCaption, strDes, dwImage, dwTxtColor, dwScoreText);

	if (0 != m_nDangerCount)
	{
	strtmp.Format(L"%d", m_nDangerCount);
	strDes.Format(BkString::Get(IDS_EXAM_1395), L"8C0000", strtmp);
	}


	m_pDlg->SetItemAttribute(IDC_EXAM_TEXT_526, "class", "examscoretitle");
	m_pDlg->SetItemColorAttribute(IDC_EXAM_TEXT_526, "crtext", dwTxtColor);

	if (TRUE == _Module.Exam.Canceled() )
	{//����û��Ѿ�ȡ��
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_592, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_593, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_594, FALSE);

	if (0 == m_nDangerCount)
	strDes.Format(BkString::Get(IDS_EXAM_1406), L"6D6D6D", BkString::Get(IDS_EXAM_1375));
	else
	strDes.Format(BkString::Get(IDS_EXAM_1411), L"8C0000", strtmp);

	m_pDlg->SetItemText(IDC_EXAM_TEXT_526, BkString::Get(IDS_EXAM_1413));
	m_pDlg->SetItemAttribute(IDC_EXAM_TEXT_526, "class", "examtitle");
	m_pDlg->SetItemColorAttribute(IDC_EXAM_TEXT_526, "crtext", TEXT_RISK_O_COLOR);
	}

	if (FALSE == strCaption.IsEmpty())
	{
	m_pDlg->SetItemIntAttribute(IDC_EXAM_IMAG_DIY, "sub", dwImage);//image
	m_pDlg->SetRichText(IDC_EXAM_TEXT_524, strDes);
	m_pDlg->SetItemText(IDC_EXAM_IMG_SCORE_591, strCaption);
	m_pDlg->SetItemText(IDC_EXAM_IMG_SCORE_598, strCaption);
	m_pDlg->SetItemText(IDC_EXAM_IMG_SCORE_601, strCaption);
	m_pDlg->SetItemColorAttribute(IDC_EXAM_IMG_SCORE_591, "crtext", dwTxtColor);
	m_pDlg->SetItemColorAttribute(IDC_EXAM_IMG_SCORE_598, "crtext", dwTxtColor);
	m_pDlg->SetItemColorAttribute(IDC_EXAM_IMG_SCORE_601, "crtext", dwTxtColor);
	}
	*/
	m_pDlg->SetItemIntAttribute(IDC_EXAM_IMAG_DIY, "sub", dwImage);//image

}




LRESULT CBeikeSafeExamUIHandler::OnSignal(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	if (lParam)
	{//0->��������
		//m_pDlg->SetItemVisible(IDC_DIV_ECHO_NOFINISH, TRUE);
	}
	else if (wParam)
	{//2->���ӳɹ�
		//m_pDlg->SetItemVisible(IDC_DIV_ECHO_CONNECT_ERROR, FALSE);
		m_pDlg->SetItemVisible(IDC_DIV_ECHO_OK, TRUE);
		m_pDlg->SetItemVisible(IDC_DIV_ECHO_NOFINISH, FALSE);
		m_pDlg->SetItemVisible(IDC_DIV_ECHO_CONNECT_ERROR, FALSE);
		m_bEcho = TRUE;
		m_pDlg->SendMessage(MSG_APP_ECHO_FINISH, BkSafeExamItemLevel::Safe, TRUE );
	}
	else
	{//1->����ʧ��
		//m_pDlg->SetItemVisible(IDC_DIV_ECHO_OK, FALSE);
		m_pDlg->SetItemVisible(IDC_DIV_ECHO_CONNECT_ERROR, TRUE);
		m_pDlg->SetItemVisible(IDC_DIV_ECHO_NOFINISH, FALSE);
		m_pDlg->SetItemVisible(IDC_DIV_ECHO_OK, FALSE);
		_ReportLog(examechofalied);
		m_pDlg->SendMessage(MSG_APP_ECHO_FINISH, BkSafeExamItemLevel::RiskInfo, FALSE);
		m_bEcho = FALSE;
	}

	return 0;
}

void CBeikeSafeExamUIHandler::_InitExamItemSort()
{
	/*
	�ؼ�Ŀ¼����ɨ��->1
	ϵͳ©��ɨ��->2
	������ɨ��->3
	�ٷ��汾->4
	���״̬->7
	������ܱ���->32

	����������ҳ�Ƿ񱻶���۸�ָ���쳣��ַ->11
	����Ƿ������å����ƹ���쳣����ͼ��->40
	��ⳣ������ͼ���Ƿ񱻶���۸�->39
	�������ݷ�ʽ�Ƿ񱻶���۸�->12
	����IE������������Ŀ�ݷ�ʽ�Ƿ񱻶���۸�->38
	����ղؼ��Ƿ���ڶ����ƹ����ַ->36

	���GUEST�˻��Ƿ����->28
	���Զ������->31

	���������Ƿ����->27
	��������ļ����Ƿ����->29
	��⹲����Դ->30
	���ϵͳ���Ƿ��������->34
	�����̡��ļ��д��Ƿ�����쳣->35

	���Internetѡ���IE����������Ƿ�����쳣->21
	��������Ĭ�����������Ƿ�����쳣->16
	���httpЭ�鼰��ҳ�ļ������Ƿ�����->22
	����Ƿ����������ϵͳ�쳣����->37
	*/
	m_ExamItemSort.RemoveAll();
	m_ExamItemSort.Add(1);
	m_ExamItemSort.Add(2);
	m_ExamItemSort.Add(3);
	m_ExamItemSort.Add(4);
	m_ExamItemSort.Add(7);
	m_ExamItemSort.Add(32);

	m_ExamItemSort.Add(11);
	m_ExamItemSort.Add(40);
	m_ExamItemSort.Add(39);
	m_ExamItemSort.Add(12);
	m_ExamItemSort.Add(38);
	m_ExamItemSort.Add(36);

	m_ExamItemSort.Add(28);
	m_ExamItemSort.Add(31);
	m_ExamItemSort.Add(27);
	m_ExamItemSort.Add(29);
	m_ExamItemSort.Add(30);
	m_ExamItemSort.Add(34);
	m_ExamItemSort.Add(35);
	m_ExamItemSort.Add(BkSafeExamItem::EXAM_CHECK_AV);
	m_ExamItemSort.Add(BkSafeExamItem::EXAM_CHECK_UPDATE);

	m_ExamItemSort.Add(21);
	m_ExamItemSort.Add(16);
	m_ExamItemSort.Add(22);
	m_ExamItemSort.Add(37);

	//���ÿ���ϵ��
	m_mapItemScoreCoft.RemoveAll();
	m_mapItemScoreCoft.Add(1, 5);	//ľ��ɨ��
	m_mapItemScoreCoft.Add(2, 4);	//ϵͳ©��
	m_mapItemScoreCoft.Add(3, 4);	//������ɨ��->3
	m_mapItemScoreCoft.Add(4, 3);	//�ٷ��汾
	m_mapItemScoreCoft.Add(7, 3);	//����Ƿ��ѿ�����ɽ��ʿȫ������
	m_mapItemScoreCoft.Add(32, 2);	//���������ȫ�����Ƿ���ȫ������

	m_mapItemScoreCoft.Add(11, 3);	//����������ҳ�Ƿ񱻶���۸�ָ���쳣��ַ
	m_mapItemScoreCoft.Add(40, 3);	//����Ƿ������å����ƹ���쳣����ͼ��
	m_mapItemScoreCoft.Add(39, 3);	//��ⳣ������ͼ���Ƿ񱻶���۸�
	m_mapItemScoreCoft.Add(12, 3);	//�������ݷ�ʽ�Ƿ񱻶���۸�
	m_mapItemScoreCoft.Add(38, 2);	//����IE������������Ŀ�ݷ�ʽ�Ƿ񱻶���۸�
	m_mapItemScoreCoft.Add(36, 2);	//����ղؼ��Ƿ���ڶ����ƹ����ַ

	m_mapItemScoreCoft.Add(28, 2);	//����Ƿ� Guest �˻�������
	m_mapItemScoreCoft.Add(31, 2);	//����Ƿ��ֹԶ��������������
	m_mapItemScoreCoft.Add(27, 2);	//����Ƿ�����Ա�����
	m_mapItemScoreCoft.Add(29, 2);	//����Ƿ�����鿴�����ļ�/�ļ���
	m_mapItemScoreCoft.Add(30, 2);	//����Ƿ���ϵͳ������Դ
	m_mapItemScoreCoft.Add(34, 5);	//���ϵͳ�Ƿ��������
	m_mapItemScoreCoft.Add(35, 2);	//�����̡��ļ��д��Ƿ�����쳣

	m_mapItemScoreCoft.Add(21, 2);	//���Internetѡ���IE����������Ƿ�����쳣
	m_mapItemScoreCoft.Add(16, 2);	//��������Ĭ�����������Ƿ�����쳣
	m_mapItemScoreCoft.Add(22, 2);	//���httpЭ�鼰��ҳ�ļ������Ƿ�����
	m_mapItemScoreCoft.Add(37, 2);	//����Ƿ����������ϵͳ�쳣����
	m_mapItemScoreCoft.Add(41, 1);	//����Ƿ���ڲ���Ҫ����������������
	m_mapItemScoreCoft.Add(BkSafeExamItem::EXAM_CHECK_AV, 2);	//����Ƿ���ڲ���Ҫ����������������

	//�������
	m_mapExamLevelMinScore.Add(0, 5);//ľ��
	m_mapExamLevelMinScore.Add(30, 5);
	m_mapExamLevelMinScore.Add(60, 30);
	m_mapExamLevelMinScore.Add(90, 60);
	m_mapExamLevelMinScore.Add(99, 90);
}

/*
int CBeikeSafeExamUIHandler::_FileSignerIsValid(LPCTSTR pszFile, CAtlArray<CString>& arrSinger)
{
int nRet = -1;
CWinTrustVerifier verifile;
CWinTrustSignerInfoChain SingerInfo;
verifile.TryLoadDll();
DWORD dwWinTrust = 0, nCount = arrSinger.GetCount();
HRESULT hr = S_OK;
dwWinTrust = verifile.VerifyFile(pszFile, &SingerInfo);

if (dwWinTrust <= 0x0000FFFF)
hr = AtlHresultFromWin32(dwWinTrust);
else
hr = dwWinTrust;

if ( SUCCEEDED( hr ) )
{
if ( !SingerInfo.m_chain.IsEmpty() )
{
for ( int i = 0; i < nCount; i++)
{
if (0 == SingerInfo.m_chain.GetHead().m_strIsserName.Compare(arrSinger[i]))
{//�����֤���幫˾��ǩ�����ڸ�����ǩ���б��������һ��ƥ���Ͼ���ɹ���
nRet = 0;
break;
}
}

//�������֤���幫˾��ǩ�����ߵ���һ���Ѿ����ǳɹ���
if (0 == nCount)
nRet = 0;
}
}

return nRet;
}*/


void CBeikeSafeExamUIHandler::_StartProcess(LPCTSTR pszFileFullPath, LPCTSTR pszParam /*= NULL*/)
{
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;

	CString strCmd;
	if (NULL == pszParam)
	{
		strCmd.Format( TEXT("\"%s\""), pszFileFullPath);
	}
	else
	{
		strCmd.Format( TEXT("\"%s\" %s"), pszFileFullPath, pszParam );
	}

	if (::CreateProcess(  NULL, (LPTSTR)(LPCTSTR)strCmd, NULL, NULL,
		FALSE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}

int CBeikeSafeExamUIHandler::_CheckDuBa()
{
	int nRet = -1;
	KCallDuba duba;
	static BOOL bFlag = FALSE;
	if ( bFlag == duba.IsDubaExist() )
		return nRet;

	bFlag = duba.IsDubaExist();

	// ����Ҫ���¶���״̬�� [1/18/2011 zhangbaoliang]
/*
	if ( TRUE == bFlag )
	{
		nRet = 0;
		m_pDlg->SetItemText(IDC_EXAM_TXT_581, BkString::Get(IDS_EXAM_1380));
		m_pDlg->SetItemText(IDC_EXAM_TXT_582, BkString::Get(IDS_EXAM_1381));
	}
	else
	{
		m_pDlg->SetItemText(IDC_EXAM_TXT_581, BkString::Get(IDS_EXAM_1378));
		m_pDlg->SetItemText(IDC_EXAM_TXT_582, BkString::Get(IDS_EXAM_1379));
	}*/

	return nRet;
}
void CBeikeSafeExamUIHandler::UpdateDubaState()
{
	_CheckDuBa();
}

LRESULT CBeikeSafeExamUIHandler::OnStartExam(UINT , WPARAM wParam, LPARAM lParam, BOOL& )
{
	UpdatSafemonStateCaption();
	_UpdateExamSetTxt();//���������������
	_LoadExamData();

	m_pDlg->SetItemIntAttribute(IDC_PROGRESS_EXAM, "value", 0);
	m_pDlg->SetItemVisible(IDC_DIV_EXAM_WORKING, TRUE);
	m_pDlg->SetItemText(IDC_EXAM_CANCEL_580, BkString::Get(IDS_EXAM_1376));
	m_pDlg->SetItemVisible(IDC_DIV_EXAM_FINISH, FALSE);
	//history
	m_pDlg->SetItemVisible(IDC_EXAM_DLG_HISTORY, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_LISTVIEW_ID, TRUE);

	return 0;
}

int CBeikeSafeExamUIHandler::_CheckSoftWareUpdate(int& nUpdateCount)
{
	int nRet = -1;

	nUpdateCount = 0;

	DWORD dwUpdateTime = 0;
	BKSafeConfig::GetSoftUpdateCount2(nUpdateCount, dwUpdateTime);

	CTimeSpan span((DWORD)_time32(NULL)-dwUpdateTime);

	m_bkSafeLog.WriteLog(L"logtime: %s", span.Format(L"%D, hours: %H, mins: %M, secs: %S"));


	m_bkSafeLog.WriteLog(L"ui BksafeExam: CheckSoftWareUpdate count = %d, nTime = %d, nDays = %d", nUpdateCount, dwUpdateTime, span.GetDays());

	if (span.GetDays() > 3)
		return nRet;

	if ( span.GetDays() <= 3 &&
		nUpdateCount > 0)
	{
		nRet = 0;
	}

	return nRet;
}

void  CBeikeSafeExamUIHandler::_SetExamMinScore(int nItemID, int nLevel)
{
	int nMinScore = 100;
	if (nLevel == BkSafeExamItemLevel::Critical)
	{
		if (BkSafeExamItem::CriticalPathVirusScan == nItemID)
		{//ɨ�赽ľ��ֱ�Ӹ�0��
			nMinScore = 0;
		}else if (BkSafeExamItem::SystemLeakScan == nItemID ||
			BkSafeExamItem::MalwareScan == nItemID)
		{//ɨ�赽©�����߲����5-30
			nMinScore = 30;
		}else
		{
			nMinScore = 60;
		}
	}
	else if (nLevel == BkSafeExamItemLevel::Risk_0)
	{
		//nMinScore = 60;
		if (
			// 			BkSafeExamItem::ConfigSystemMonitor == nItemID ||
			// 			BkSafeExamItem::EXAM_KWS_MON == nItemID ||
			BkSafeExamItem::HandShake == nItemID ||
			BkSafeExamItem::EXAM_HOMEPAGE == nItemID ||
			BkSafeExamItem::EXAM_DESKTOP_EXCEPTION_ICON == nItemID)
		{
			nMinScore = 60;
		}
		else
		{
			nMinScore = 90;
		}
	}else if (nLevel == BkSafeExamItemLevel::Optimization)
	{
		nMinScore = 99;
	}

	if (nMinScore < m_nMinScore2)
		m_nMinScore2 = nMinScore;
	if (m_nMinScore2 < 0)
		m_nMinScore2 = 0;
	if (m_nMinScore2 < m_nMinScore)
		m_nMinScore = m_nMinScore2;

	m_bkSafeLog.WriteLog(L"_SetExamMinScore: m_nMinScore = %d, nMinScore = %d", m_nMinScore, nMinScore);
}

void CBeikeSafeExamUIHandler::_CalcExamScore()
{

	int nIndex = m_mapExamLevelMinScore.FindKey(m_nMinScore2);
	if (nIndex >= 0)
	{
		int nValue = m_mapExamLevelMinScore.GetValueAt(nIndex);
		BKSAFE_EXAM_RESULT_ITEM exam;
		int nItemCount = 0, nItem = 0, nLevelValue = 0;
		//Σ��
		for (int i = 0; i < m_mapAllDangerItem.GetSize(); i++)
		{
			nItemCount = 1;
			nItem = m_mapAllDangerItem.GetKeyAt(i);
			nIndex = m_mapItemScoreCoft.FindKey(nItem);;
			if (nIndex < 0)
				continue;
			exam = m_mapAllDangerItem.GetValueAt(i);
			if (TRUE == exam.SafeExamItemEx.bInvalid)
			{
				if (BkSafeExamItem::SystemLeakScan == nItem)
					nItemCount = exam.SafeExamItemEx.u.ExamLeakEx.nHightLeakCount;
				else
					nItemCount = exam.SafeExamItemEx.u.ExamKwsResultEx.nDangerCount;
				m_bkSafeLog.WriteLog(L"m_mapAllDangerItem nItemCount = %d", nItemCount);
				if (nItemCount < 1)
					nItemCount = 1;
			}
			nLevelValue += m_mapItemScoreCoft.GetValueAt(nIndex) * nItemCount;
		}



		double db1 = (double)nLevelValue/10;
		int nNnum1 = (m_nMinScore2-nValue);
		double db2 = atan(db1);
		db1 = db2*2/PI;
		int nScore = nValue + nNnum1*(1 - db1) + 0.5;
		if (m_nMinScore > nScore)
		{
			m_nMinScore = nScore;
		}
		if (m_nMinScore < 0)
			m_nMinScore = 0;
		m_bkSafeLog.WriteLog(L"_CalcExamScore:minScore = %d, m_nMaxScore = %d, nLevelValue = %d,", m_nMinScore, m_nMaxScore, nLevelValue);
	}
}

void CBeikeSafeExamUIHandler::_UpdateExamScoreImage()
{
#if 0
	m_nMaxScore = 4;
#endif

	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_592, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_593, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_594, FALSE);

	/*

	CStringA strScoreNumSkin = "examscoresafenum";
	CString strText1, strText2;
	int nScoreTxt = 0,  nScoreNum = 0, nImage = 0, nColor = 0;

	_ParseScoreForUpdateUI(m_nMaxScore, strScoreNumSkin, strText1, strText2, nImage, nColor, nScoreTxt);


	CSimpleArray<int> n, b;
	n.Add(0);n.Add(0);n.Add(0);
	b = n;
	_ParseScore(m_nMaxScore, n, b);

	int nIndex = 0;
	if (FALSE == m_bExamFinished)
	{
	CStringA strSkin;
	strSkin.Format("skin0=%s,skin1=%s,skin2=%s", strScoreNumSkin, strScoreNumSkin, strScoreNumSkin);
	m_pDlg->SetItemAttribute(IDC_EXAM_IMG_SCORE_583, "skinlist", strSkin);
	strSkin.Format("sub0=%d,sub1=%d,sub2=%d", b[0] == 0 ? -1:n[0], b[1] == 0 ? -1:n[1], b[2] == 0 ? -1:n[2]);
	m_pDlg->SetItemAttribute(IDC_EXAM_IMG_SCORE_583, "sublist", strSkin);
	m_pDlg->SetItemIntAttribute(IDC_EXAM_IMG_SCORE_584, "sub", nScoreTxt);
	return;
	}
	else if (FALSE == _Module.Exam.Canceled())
	{//û��ȡ�����
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_592, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_593, FALSE);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_594, FALSE);
	CStringA strSkin, strSub;
	DWORD dwID = 0, dwEndID = 0;
	if (0 != b[0])
	{
	nIndex = 0;
	dwID = IDC_EXAM_IMG_SCORE_587;

	m_pDlg->SetItemIntAttribute(IDC_EXAM_IMG_SCORE_597, "sub", nScoreTxt);
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_592, TRUE);
	}else if (0 != b[1])
	{
	nIndex = 1;
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_593, TRUE);
	dwID = IDC_EXAM_IMG_SCORE_595;
	m_pDlg->SetItemIntAttribute(IDC_EXAM_IMG_SCORE_597, "sub", nScoreTxt);
	}else if (0 != b[2])
	{
	nIndex = 2;
	m_pDlg->SetItemVisible(IDC_EXAM_IMG_SCORE_594, TRUE);
	dwID = IDC_EXAM_IMG_SCORE_599;
	m_pDlg->SetItemIntAttribute(IDC_EXAM_IMG_SCORE_600, "sub", nScoreTxt);
	}

	CStringA strTmp;
	int nSkin = 0;
	for (int i = nIndex; i < 3; i++)
	{
	strTmp.Format("skin%d=%s,", nSkin, strScoreNumSkin);
	strSkin += strTmp;
	strTmp.Format("sub%d=%d,", nSkin, n[i]);
	++nSkin;
	strSub += strTmp;
	}

	if (FALSE == strSkin.IsEmpty() &&
	FALSE == strSub.IsEmpty() &&
	0 != dwID)
	{
	m_pDlg->SetItemAttribute(dwID, "skinlist", strSkin);
	m_pDlg->SetItemAttribute(dwID, "sublist", strSub);

	}
	}

	m_pDlg->SetItemIntAttribute(IDC_EXAM_IMG_SCORE_590, "sub", nScoreTxt);
	m_pDlg->SetItemIntAttribute(IDC_EXAM_IMG_SCORE_586, "sub", nScoreTxt);
	*/

}

void CBeikeSafeExamUIHandler::_ParseScore(int nScore, CSimpleArray<int> &arr, CSimpleArray<int>& arr2)
{
	if (nScore >= 100)
	{
		arr[0] = 1;
		arr2[0] = arr2[1] = arr2[2] = 1;
	}else if (nScore >= 10)
	{
		arr[1] = nScore / 10;
		arr[2] = nScore % 10;
		arr2[1] = arr2[2] = 1;
	}
	else if (nScore >= 0 && nScore < 10)
	{
		arr[2] = nScore;
		arr2[2] = 1;
	}
}

void CBeikeSafeExamUIHandler::_ParseScoreForUpdateUI(int nScore, CStringA& strSkinNum, 
													 CString& strText1, CString& strText2, 
													 int& dwImage, int& dwTextColor, int& dwScoreText)
{

	//���ĵ��Էǳ���������������֣�
	if ( nScore >= 100)
	{//���ĵ��Էǳ���������������֣�
		strSkinNum = "examscoresafenum";
		//strText1.Format(BkString::Get(IDS_EXAM_1369), BkString::Get(IDS_EXAM_1370));
		strText1 = BkString::Get(IDS_EXAM_1370);
		dwTextColor = TEXT_SAFE_COLOR;
		dwImage = 0;
		dwScoreText = 0;
	}else if (nScore >= 60)
	{
		strText1 = BkString::Get(IDS_EXAM_1393);
		//dwTextColor = TEXT_RISK_O_COLOR;
		if (0 == m_nDangerCount)
		{
			strText2.Format(BkString::Get(IDS_EXAM_1395), L"6D6D6D", BkString::Get(IDS_EXAM_1371));
		}		
		strSkinNum = "examscoreoptnum";
		// 		strText1 = BkString::Get(IDS_EXAM_1370);
		dwTextColor = TEXT_OPT_COLOR;
		dwImage = 5;
		dwScoreText = 3;
	}else if (nScore >= 30)
	{//���ĵ��Կ��Խ�һ���Ż����̣���
		// 		strText1 = BkString::Get(IDS_EXAM_1393);
		// 		dwTextColor = TEXT_RISK_O_COLOR;
		// 		if (0 == m_nDangerCount)
		// 		{
		// 			strText2.Format(BkString::Get(IDS_EXAM_1395), L"6D6D6D", BkString::Get(IDS_EXAM_1371));
		// 		}		
		// 		strSkinNum = "examscoresafenum";
		// 		dwImage = 0;
		// 		dwScoreText = 0;

		strText1 = BkString::Get(IDS_EXAM_1372);
		dwTextColor = TEXT_RISK_O_COLOR;
		dwImage = 1;
		dwScoreText = 1;
		strSkinNum = "examscorerisknum";
	}else if (nScore >= 5)
	{//���ĵ��Դ������صİ�ȫ���⣡
		//strText1.Format(BkString::Get(IDS_EXAM_1369), BkString::Get(IDS_EXAM_1372));
		strText1 = BkString::Get(IDS_EXAM_1394);
		dwTextColor = TEXT_DANGER_COLOR;
		dwImage = 2;
		dwScoreText = 2;
		strSkinNum = "examscoredangernum";
	}else if (nScore >= 0 && nScore < 5)
	{//���ĵ��Դ������صİ�ȫ��в�����죩
		//strText1.Format(BkString::Get(IDS_EXAM_1369), BkString::Get(IDS_EXAM_1394));
		strText1 = BkString::Get(IDS_EXAM_1394);
		dwTextColor = TEXT_DANGER_COLOR;
		dwImage = 2;
		dwScoreText = 2;
		strSkinNum = "examscoredangernum";
	}

	if (TRUE == _Module.Exam.Canceled())
		dwImage = 1;
}

CString CBeikeSafeExamUIHandler::_ConverColorToStr(COLORREF color)
{
	CString strColor = L"C80000";
	strColor.Format(L"%02x%02x%02x", GetRValue(color), GetGValue(color), GetBValue(color));

	return strColor;
}

void CBeikeSafeExamUIHandler::_ShareExamData(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//	return ;//��ʱ���δ˹���
		
	// 	int nSize = sizeof(BKSafe_Exam_ShareData);
	//	nSize *= 52;

	if (MSG_APP_EXAM_SCORE_CHANGE == uMsg)
	{
		BKSafe_Exam_ShareData examShareData;
		examShareData.cbSize = sizeof(examShareData);
		examShareData.uMsg = uMsg;
		examShareData.nItem = (int)wParam;
		m_bkSafeLog.WriteLog(L"_ShareExamData: %d", examShareData.nItem);

		if (BkSafeExamItem::Invalid == examShareData.nItem)
		{//�ش�ɨ�������Ϣ��(���������̽���ʱ���ܵ������Ϣ�����û�ȡ��)
			//m_arrExamShareData.Add(examShareData);
			examShareData.u.ExamState.nState = -1;
			if (_Module.Exam.Canceled())
				examShareData.u.ExamState.nState = 1;
			else
				examShareData.u.ExamState.nState = 2;
			m_arrScanData[examShareData.nItem] = examShareData;//ɨ���������
		} else if (BkSafeExamItemExOperate::RemoveItem == examShareData.nItem && (int)lParam >= 0)
		{//�޸���ĳ��������Ŀ
			EnterCriticalSection(&m_LockShareData);
			REMOVE_EXAM_RESULT_ITEM* RemoveItemInfo = (REMOVE_EXAM_RESULT_ITEM*)lParam;
			if (NULL != RemoveItemInfo)
			{
				if( !IsBadReadPtr( (void*)RemoveItemInfo, sizeof(REMOVE_EXAM_RESULT_ITEM) ) )
				{
					examShareData.u.BKSafe_Exam_Remove_Item.RemoveItemData = *RemoveItemInfo;
					m_arrFixData[RemoveItemInfo->uRemoveItem.RemoveItemInfo.dwItemID] = examShareData;//�޸�����
				}
				//m_arrExamShareData.Add(examShareData);
			}
			::LeaveCriticalSection(&m_LockShareData);

		}else if (BkSafeExamItemExOperate::ErrorMsg == examShareData.nItem)
		{//�ش�������־
		}
		else
		{//�ش�ɨ����

			BKSAFE_EXAM_RESULT_ITEM* pItem = (BKSAFE_EXAM_RESULT_ITEM *)lParam;
			m_bkSafeLog.WriteLog(L"_ShareExamData: %d, pValue = %x", examShareData.nItem, pItem);

			if (NULL != pItem)
			{
				if( !IsBadReadPtr( (void*)lParam, sizeof(BKSAFE_EXAM_RESULT_ITEM) ) )
				{
					examShareData.u.BKSafe_Exam_Scan_Item = *pItem;
					m_arrScanData[examShareData.nItem] = examShareData;//ɨ������
				}
			}
			//m_arrExamShareData.Add(examShareData);
		}
	}

	//	LeaveCriticalSection(&m_LockShareData);
}

void CBeikeSafeExamUIHandler::_ParseScoreForUpdateUI(int nScore, int& nLevel, int& nImage, int& nTxtColor)
{
	// 	nImage = 0;
	// 	nTxtColor = TEXT_SAFE_COLOR;
	//���ĵ��Էǳ���������������֣�
	if ( nScore >= 100)
	{//���ĵ��Էǳ���������������֣�
		nImage = 0;
		nLevel = 0;
	}else if (nScore > 90)
	{//�Ż�
		nLevel = 1;
		nImage = 5;
		nTxtColor = TEXT_OPT_COLOR;
	}
	else if (nScore > 60)
	{//����
		nLevel = 2;
		nImage = 1;
		nTxtColor = TEXT_RISK_O_COLOR;
	}else if (nScore > 30)
	{//Σ��
		nLevel = 3;
		nImage = 2;
		nTxtColor = TEXT_DANGER_COLOR;
	}else if (nScore > 5)
	{//��Σ
		nLevel = 4;
		nImage = 2;
		nTxtColor = TEXT_DANGER_COLOR;
	}else if (nScore >= 0 && nScore <= 5)
	{//ľ��
		nLevel = 5;
		nImage = 2;
		nTxtColor = TEXT_DANGER_COLOR;
	}

}

void CBeikeSafeExamUIHandler::_UpdateExamResult()
{
	m_nMaxScore = m_nMinScore2 = m_nMinScore = 100;
	for(int i = 0; i < m_mapAllDangerItem.GetSize(); i++)
	{
		BKSAFE_EXAM_RESULT_ITEM exam = m_mapAllDangerItem.GetValueAt(i);
		//��ȡ���µĵ÷�����
		_SetExamMinScore(m_mapAllDangerItem.GetKeyAt(i), exam.nLevel);
	}
	//��������µ���ϸ�÷�
	//_CalcExamScore();
	m_nMaxScore = m_nMinScore;

	//���½����ʾ
	_UpdateExamResultTitle();
}


CBkNavigator* CBeikeSafeExamUIHandler::OnNavigate( CString &strChildName )
{
	if (0 == strChildName.CompareNoCase(BKSFNS_FRCE_STARTEXAM))
	{
		OnBkLblExamRestart();
	}else if (0 == strChildName.CompareNoCase(BKSFNS_STOPEXAM))
	{
		OnBkBtnExamStop();
	}
	return NULL;
}

void CBeikeSafeExamUIHandler::_InitArrayForShareData()
{
	m_arrFixData.RemoveAll();
	m_arrScanData.RemoveAll();
	BKSafe_Exam_ShareData examShareData;
	examShareData.cbSize = sizeof(examShareData);
	examShareData.uMsg = -1;
	examShareData.nItem = -1;
	for ( int i = 0; i < g_ExamItem.GetCount(); i++)
	{
		m_arrScanData[g_ExamItem[i]._dwItemID] = examShareData;
		m_arrFixData[g_ExamItem[i]._dwItemID] = examShareData;
	}
	m_arrScanData[BkSafeExamItem::Invalid] = examShareData;
	m_arrScanData[MSG_APP_EXAM_PROGRESS] = examShareData;

	//ˢ�¹����ڴ��е�����
	SetEvent(m_hExamShareDataEvent);
}


STATE_CLOSE_CHECK CBeikeSafeExamUIHandler::CloseCheck()
{
	if (FALSE == m_bExamFinished && 
		m_ExamListView.GetItemCount() > 0)
	{
		m_nCancel = TRUE;
		_WriteExamLogToIni();//write log
	}
	
	if (FALSE == m_bExamFinished && m_ExamListView.GetItemCount() > 0)
	{
		BKSafe_Exam_ShareData examShareData;
		examShareData.cbSize = sizeof(examShareData);
		examShareData.uMsg = MSG_APP_EXAM_SCORE_CHANGE;
		examShareData.nItem = BkSafeExamItem::Invalid;
		examShareData.u.ExamState.nState = 1;
		m_arrScanData[examShareData.nItem] = examShareData;//ɨ���������
		//ˢ�¹����ڴ��е�����
		SetEvent(m_hExamShareDataEvent);

	}
	return CLOSE_CHECK_CONTINUE;
}
