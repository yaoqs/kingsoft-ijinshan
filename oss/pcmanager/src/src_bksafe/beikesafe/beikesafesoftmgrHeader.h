#pragma once


#include <bkres/bkres.h>
#include "bkwin/bklistbox.h"
#include <runoptimize/interface.h>
//#include "bksoftmgruninstall.h"
#include "SoftMgrListView.h"
#include "SoftMgrItemData.h"
#include "softmgrqueryedit.h"
#include "softmgrdetail.h"
#include "TypeListBox.h"
#include <softmgr\ISoftManager.h>
#include "softmgr\ISoftChecker.h"
#include <softmgr\IDTManager.h>
#include <libdownload\libDownload.h>
#include <softmgr\URLEncode.h>
#include <softmgr\ISoftChecker.h>
#include "softmgr\ISoftUninstall.h"
#include "softmgr\ISoftDesktop.h"
#include "softmgr\KSoftMgrUpdateInfo.h"
#include "softmgrDownListView.h"
#include "SoftMgrUpdateRollWnd.h"
#include "SoftMgrUniExpandListView.h"
#include "bkmsgdefine.h"
#include "beikesafesoftmgrnecess.h"
#include "kws/ctrls/kcombobox.h"
#include "kws/setting_hlp.h"
#include "SoftInstProxy.h"
#include <softmgr/ISoftInstall.h>
#include "LockHelper.h"
#include "bksafeuihandlerbase.h"

#include <iostream>
#include <fstream>

#include <map>
#include <vector>
#include "Wildcard.h"

typedef BOOL (*pCreateObject)( REFIID , void** );

#define IDC_UNINSTALL_LISTVIEW	11111
#define XX_MSG_DLG_WIDTH	300
#define XX_MSG_DLG_HEIGHT	100

//
// �ֻ��ر�����
//
#define PHONE_NESS_SWITCH	1

#if PHONE_NESS_SWITCH
#		define	TAB_INDEX_TUIJIAN		0
#		define	TAB_INDEX_BIBEI			1
#		define	TAB_INDEX_DAQUAN		2
#		define	TAB_INDEX_UPDATE		3
#		define	TAB_INDEX_UNINSTALL		4
#		define	TAB_INDEX_PHONE			5
#		define	TAB_INDEX_GAME			6
#else
#		define	TAB_INDEX_TUIJIAN		-1
#		define	TAB_INDEX_BIBEI			0
#		define	TAB_INDEX_DAQUAN		1
#		define	TAB_INDEX_UPDATE		2
#		define	TAB_INDEX_UNINSTALL		3
#		define	TAB_INDEX_GAME			4
#		define	TAB_INDEX_PHONE			-1
#endif

#if PHONE_NESS_SWITCH
class CWebBrowserExternal : public CWHHtmlContainerWindow
{
public:
	HRESULT SetExternalDispatch(IDispatch* pDisp) 
	{ return m_wndIE.SetExternalDispatch(pDisp); }
};
#endif

//
// �������б���ֹ�ظ���ʾ������
//
class CSoftUpdatedList
{
public:
	void Startup(const CString &kSafePath);
	// ������������
	void Add(int softId);
	// �ж��Ƿ��Ѿ�����
	BOOL InList(int softId);
	void Cleanup();

private:
	struct SoftInfo
	{
		int _id;
		__time32_t _time;

		SoftInfo() {_id = 0; _time = 0;}
		SoftInfo(int id, __time32_t time) {_id = id; _time = time;}
	};

private:
	CString _filePath;
	CComCriticalSection _csList;
	CAtlArray<SoftInfo> _softInfoList;
};

//���ع�������ṹ��
struct threadParam
{
	void *pDlg;
	void *pData;
	int flag;	//0������1��ͣ��2ȡ��, 3ɾ��
};

struct softInfo 
{
	int nState; //״̬��1��ͣ, 2ȡ��
	int nProgress;
};

//��װ���е�Ԫ��
struct installParam 
{
	CString strPath;
	CSoftListItemData *pData;
};


//��¼ж��·��
typedef std::map<CString, int>	t_mapUnInitPath;
typedef t_mapUnInitPath::iterator	t_iterUnInitPath;


class CBeikeSafeMainDlg;
class CBeikeSoftMgrPowerSweepDlg;
class CBkSafeSoftMgrUnstDlg;

enum UniType
{
	UNI_TYPE_UNKNOW = 0,
	UNI_TYPE_ALL,
	UNI_TYPE_START,
	UNI_TYPE_QUICK,
	UNI_TYPE_DESKTOP,
	UNI_TYPE_PROCESS,
	UNI_TYPE_TRAY,
};
enum SoftActionFrom
{
	ACT_SOFT_FROM_DAQUAN = 0,
	ACT_SOFT_FROM_NECESS,
	ACT_SOFT_FROM_UPDATE,
};

class CBeikeSafeSoftmgrUIHandler
	:public ISoftMgrCallback,
	public ILstSoftUniExpandCallback,
	public ISoftMgrUpdateCallback,
	public IClickCallback,
	public IEditCallBack,
	public IHttpAsyncObserver,
	public CBkNavigator,
	public ksm::ISoftUnincallNotify,
	public ksm::ISoftInfoQueryNotify,
	public IKSAutoInstCallBack2,
	public CBkSafeUIHandlerBase
#if PHONE_NESS_SWITCH
	,public IDispatch
#endif
{
public:
	friend class CBeikeSafeSoftmgrNecessHandler;

public:
	CBeikeSafeSoftmgrUIHandler(CBeikeSafeMainDlg *pDialog)
		: m_pDlg(pDialog)
		, m_necessUIHandler(pDialog,this)
	{
		m_bInitInterface = FALSE;
		m_bCachExist = FALSE;
		m_bViewUninstall = FALSE;
		m_bLoadFail = FALSE;
		m_bInitData = FALSE;
		m_bViewDetail = FALSE;
		m_bInit = FALSE;
		m_bQuery = FALSE;
		m_bQueryUni = FALSE;
		m_nTab = 0;
		m_nDown = -1;
		m_nIndexUpdate = 0;
		m_hWndListUpdate = NULL;
		m_hDownIcon = (HANDLE)-1;
		m_hInitData = (HANDLE)-1;
		m_hDownload = (HANDLE)-1;
		m_strCurType = BkString::Get(IDS_SOFTMGR_8018);
		m_nCurType = 0;
		m_nCurTypeUni = 0;
		m_pSoftMgr = NULL;
		m_pSoftChecker = NULL;
		m_pUninstall = NULL;
		m_nCountUpdateIgnore = 0;
		m_bInitUpdate = FALSE;
		m_nSoftIdByCmd = 0;

		m_bInitInfoQuery = FALSE;
		m_pInfoQuery = NULL;

		m_bShowDownloaded	= FALSE;
		m_bViewAll			= FALSE;
		m_bCleaned			= FALSE;
		m_bViewDestTop = FALSE;

		m_bStartMonitor = FALSE;
		m_hUpdSoftInfoThread = NULL;
		m_hCheckInstallThread = NULL;
		m_hCheckUpdateThread = NULL;

		m_hSignLoadFinish = NULL;

		m_nUniBtnId = 0;

		m_bInitInstProxy = FALSE;

		m_pPowerSweepDlg = NULL;
		m_pImge = NULL;
		m_hInstall = (HANDLE)-1;
		m_font.Attach(BkFontPool::GetFont(BKF_DEFAULTFONT));

		m_arrCheckUpdate.RemoveAll();

		m_pSelSoftUniData = NULL;
		m_pSoftRubbishSweep = NULL;
		m_bInitUni = FALSE;
		m_dlgSoftMgrUninstall = NULL;
		m_nUniType = UNI_TYPE_ALL;
		m_bUniRefresh = TRUE;
		m_nUniLastClickHeaderIndex = -1;
		m_nDaquanLastClickHeaderIndex = -1;
		m_pDTManagerOneKey = NULL;

		CreateObject = NULL;
#if PHONE_NESS_SWITCH
		m_phoneLoaded = FALSE;
		m_recommendLoaded = FALSE;
		m_pPhoneDTMgr = NULL;
#endif
	}

	~CBeikeSafeSoftmgrUIHandler();

public:
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	LRESULT OnRefreshNetPage(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	CString GetSoftLibraryVersion();//�õ������İ汾��Ϣ
	CString GetUninstLibVersion();
	HRESULT GetKSafeDirectory(CString &strDir);//�õ���װĿ¼
	HRESULT GetKSoftDirectory(CString &strDir);//�õ�Ŀ¼
	HRESULT GetKSoftDataDir(CString &strDir);//�õ�dataĿ¼
	HRESULT GetKSoftIconDir(CString &strDir);//�õ�iconĿ¼
	void SetDownloadDetail();			//��ʾ��������
	void OnListReSize(CRect rcWnd);		// ���������ڴ�С�ı��Ҳ�listbox��С
	void InitDownloadDir();
	void Uninit();
	BOOL IsRecommend(CSoftListItemData *pData);
	void OnEditMouseWheelMsg(WPARAM wParam, LPARAM lParam);

	STATE_CLOSE_CHECK	CloseCheck();


	VOID _RefershItemBySoftIDMainThread(CString strSoftID);
	VOID _RefershItemBySoftIDWorkerThread(CString strSoftID);
	LRESULT OnRefershItemBySoftID(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnRefershRubbishInfo(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnRefershUniAllSoftFinish(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnSoftmgrUEDataCompleted(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnSoftmgrFreshTotal(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnSoftmgrUESortByName(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnSoftmgrRefreshUniType(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnSoftmgrUEShowUniDataPage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnSoftmgrUEHideHeaderArrow(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnCheckSoftCanInstall(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnNotifySoftInstall(UINT uMsg, WPARAM wParam, LPARAM lParam);


	void OnViewDetail(DWORD dwIndex);	//�鿴����	
	void OnViewNew(DWORD dwIndex);	//�鿴�������	
	void OnDownLoad(DWORD dwIndex);		//��ʼ���ز���
	void _downLoadSoft(CSoftListItemData* pSoftData, SoftActionFrom nFrom = ACT_SOFT_FROM_DAQUAN, BOOL bUpdate = FALSE);
	void OnCancel(DWORD dwIndex);		//����ȡ������
	void _CancelDownLoad(CSoftListItemData* pSoftData, SoftActionFrom nFrom = ACT_SOFT_FROM_DAQUAN);
	void OnContinue(DWORD dwIndex);		//���ؼ�������
	void _ContinueDownLoad(CSoftListItemData* pData, SoftActionFrom nFrom = ACT_SOFT_FROM_DAQUAN);
	void OnPause(DWORD dwIndex);		//������ͣ����
	void _PauseDownLoad(CSoftListItemData* pData, SoftActionFrom nFrom = ACT_SOFT_FROM_DAQUAN);
	void OnDownLoadIcon(CString strID);	//����ICON
	
	void OnFreebackFromList(DWORD dwIndex);//����
	void _FreebackFromList(CSoftListItemData* pData,SoftActionFrom nFrom = ACT_SOFT_FROM_DAQUAN);
	void OnTautilogyFromList(DWORD dwIndex);//����
	void _TautilogyFromList(CSoftListItemData* pData,SoftActionFrom nFrom = ACT_SOFT_FROM_DAQUAN);
	void OnSwitchPage(DWORD dwPage);
	void OnDaquanSoftMark(DWORD dwIndex);
	void OnBiBeiSoftMark(CSoftListItemData* pData);
	void OnViewNewInfo(CSoftListItemData* pData);

	void OnUpdateViewDetail(DWORD dwIndex, HWND hWndList); //�鿴�������
	void OnUpdateViewNew(DWORD dwIndex, HWND hWndList); //�鿴�������
	void OnUpdateDownLoad(DWORD dwIndex, HWND hWndList);	//����
	void OnBtnClick( DWORD dwIndex, int nType );
	void OnUpdateContinue(DWORD dwIndex, HWND hWndList);	//����
	void OnUpdatePause(DWORD dwindex, HWND hWndList);	//��ͣ
	void OnUpdateCancel(DWORD dwIndex, HWND hWndList);	//ȡ��
	void OnUpdateDownLoadIcon(CString strID);
	void OnUpdateFreebackFromList(DWORD dwIndex, HWND hWndList);
	void OnUpdateTautilogyFromList(DWORD dwIndex, HWND hWndList);
	void OnUpdateSoftMark(DWORD dwIndex, HWND hWndList);
	void OnUpdateIgnore(DWORD dwIndex, HWND hWndList);

	void OnUniExpandDownLoadIcon(CString strID);
	BOOL OnClickSoftUniExpand(DWORD nIndex, SOFT_UNI_INFO* pInfo);

	void OnClick( int nListId, CTypeListItemData * pData);//������list

	void OnEditEnterMsg(DWORD nEditId);	//��ѯ����ص�

	BOOL OnHttpAsyncEvent( IDownload* pDownload, ProcessState state, LPARAM lParam ); //����ICON�ص��ӿ�

	// ж�أ���������¼�
	virtual void __stdcall SoftDataEvent(ksm::UninstEvent event, ksm::ISoftDataEnum *pEnum);
	// ж�أ����ж���¼�
	virtual void __stdcall SoftDataSweepEvent(ksm::UninstEvent event, ksm::ISoftDataSweep *pSweep);
	// ж�أ���ݷ�ʽ�����¼�
	virtual void __stdcall SoftLinkEvent(ksm::UninstEvent event, ksm::SoftItemAttri type, ksm::ISoftLinkEnum *pData);
	// ж�أ��������¼�
	virtual void __stdcall SoftRubbishEvent(ksm::UninstEvent event, ksm::ISoftRubbishEnum *pEnum);
	// ж�أ���������ɨ�¼�
	virtual void __stdcall SoftRubbishSweepEvent(ksm::UninstEvent event, ksm::ISoftRubbishSweep *pSweep);

	virtual void __stdcall SoftQueryNotify(ksm::ISoftInfoEnum *pEnum, void *pParams);

	BOOL OnTabSoftMgrSelChange(int nTabItemIDOld, int nTabItemIDNew);//�л�����tab

	LRESULT OnSoftmgrRefreshBottom(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateSoftCount(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam);
	//���ؼ��������Ϣ����ʾ�������Ƕ��̲߳���������ͨ����Ϣ��ʵ�֣���ӳ���ˢ�����⣩
	LRESULT OnSoftmgrInitFinish(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam);
	LRESULT OnOnSoftmgrRefreshLoadTip(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam);
	LRESULT OnSetCheckListNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLoadUpdateCache(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLoadUpdateReal(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUpdateUniType(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnChangeUninstallEdit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnChangeDaquanEdit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnUniComboBoxSelect(WORD wNotifyCode, WORD wID, HWND hWndCtl);

	void OnUpdateCheckAll();		//����ҳ�Ƿ�ȫѡ
	void OnUpdateBtnIgnore();	
	void OnUpdateDetailBack();
	void OnUpdateSelectSoft();
	void OnUpdateFromeDetail();

	void DeleteFileAfterTime();
	void OnBackFromQuery();
	void OnBack();
	void OnSetting();					//����
	void OnRefresh();					//ˢ��
	void OnQuerySoft();					//��ѯ���
	void OnClearDaquanQeuryEdit();
	void OnClearUninstallQeuryEdit();
	void OnDownloadMgr();				//���ع���
//	void OnBatchDownSoft();				//���ع�ѡ���	
	void OnShowNoPlugSoft();				//ѡ���������
	void OnShowFreeSoft();		//ֻ��ʾ����޲�����
	void OnDownLoadFromeDetail();		//������ҳ��������
	void OnTransferFromQuery();			//û�в�ѯ�������ʱ����ת����
	void OnTransferUninstall();			//û�в�ѯ����Ҫж�ص������ת����

	void OnQueryUninstall();					//��ѯж��

	BOOL InsertSoftInfo(CSoftListItemData *pData, BOOL bPlugCheck, BOOL bFreeCheck, BOOL& bQueryMark);
	void GetSoftStateFromCach(CString strFilePath); //�ӻ����ж�ȡ�������Ϣ
	void GetUpdateStateFromCache(CString strFilePath);	//�ӻ����ж�ȡ������Ϣ
	void UpdateCach();	//���»����ļ�
	void SaveUpdatePointOutInfo();
	void SaveDownloadSoftInfo(CString strSoftInfo);
	void SaveSoftInfoLog(CString strFilePath, CSimpleArray<CString>& arr);
	void LoadSoftInfoLog(CString strFilePath, CSimpleArray<CString>& arr);
	void SaveUpdateIgnoreList();
	void LoadUpdateIgnoreList();
	void ShowLoadInstallInfoTip();	//���������Ϣ��ʾ
	void OnTimer(UINT_PTR nIDEvent);	//��ʱ����ʱˢ�µײ�������Ϣ
	void OnSize(UINT nType, CSize size);

	void OnUninstallQueryBack(BOOL bClearEditText = FALSE);
	void OnUninstallDetailBack();
	void OnUninstallOpenDir();
	void OnDetailUninstall();

	void OnBackFromInsQuery();

	void OnBtnUniAll();
	void OnBtnUniDesk();
	void OnBtnUniStartMenu();
	void OnBtnUniQuickLan();
	void OnBtnUniProcess();
	void OnBtnUniTray();

	void SortUninstallInfoBySpace( BOOL bIncrease );
	void SortUninstallInfoByTime( BOOL bIncrease );

	CString GetCurrentSystemVersion();	//�жϵ�ǰϵͳ�İ汾
	BOOL SelDir(CString& strPath);

	//��ʼ��
	void Init();		

	void InitSwitch();			// �л�TAB��ʱ���init�Ĳ���
	void InitSlow();			// �����Ƚ������߳�
	void InitLeftTypeList();
	void InitRightSoftList();
	void InitUninstallSoftList();
	BOOL InitInterface();
	void InitLinks();

	IDTManager*	GetDTManagerForOneKey();

	void	GetUninstallDataFromMap( CUninstallSoftInfo * pData, void * mp );
	void	LoadUninstallImage( CUninstallSoftInfo * pData );

	void ShowLoadingTip();
	void HideLoadingTip();
	void RollTheTip();
	void ShowUniDataPage();

	void GetSoftInfoByCondition();

	//��ȡ�������
	void ShowItemsBySoftType(CString strSoftType);

	CSoftListItemData* GetDataBySoftID(CString strID);
	BOOL IsDataFilterByCheck(CSoftListItemData* pData, BOOL bFree, BOOL bPlug);
	BOOL ShowDataToList(CAtlList<CSoftListItemData*>& arr, BOOL bShowTypeInfo = FALSE);
	
	void LoadNecessData();	// ��sqlite�����ȡ���е�װ���ر������Ϣ
	void LoadAllSoftData();//��sqlite�����ȡ���е������Ϣ

	void ConvertMapToSoftItemData(CSoftListItemData* pData, CAtlMap<CString,CString>& soft);

	void ClickDaquanType(CString strNewType);
	int GetDaquanType(CString strType);
	void OnClickDaquanType(UINT uCmdId); 
	void OnClickXiezaiType(UINT uCmdId); 
	CString GetTypeUI(CString strTypeData);
	CString GetTypeData(CString strTypeUI);
	void LoadUniType(CSimpleArray<CString>& soft);
	void OnSubmitSoft(); //���ɽ��ʿ�ύ���
	void OnFreeBack(); //����
	void GetConfig();	//����ж��������Ҫ��INI�ļ�
	void CheckDownloadState(); //����������ӵ�״̬

	void OnReStart();	//������ʿ
	void OnIgnoreReStartTip();	// ���ò�����������������Ҫ������ʿ���ر�tip
	void OnCloseReStartTip();   // �ر�����������Ҫ������ʿ��tip

	void ShowPicSoftMgr();	//�ڼ�����Ϣ��ʱ��չʾͼƬ
	void OnBtnSwitchWatch(); //���ؼ��
	void OnLnkCurrentBack();

	void OnBtnResidualClear(); //�������������
	void OnBtnRubbishClear();
	void OnBtnSystemSlim();

	void OnBtnSmrDaquanSortByName(); 
	void OnBtnSmrDaquanSortBySize(); 
	void OnBtnSmrDaquanSortByTime(); 

	void OnBtnSmrUniSortByName(); 
	void OnBtnSmrUniSortBySize(); 
	void OnBtnSmrUniSortByTime(); 

	void OnSetIEMainhome();
	void OnSetDesktopLink();
	void UpdateDesktopIcon(int nNum);

	//��д����
	void GetDownloadCachInfo();
	void SetDownloadCachInfo();

	void FreshTotal();		// ˢ���Ѱ�װ�ļ������� �Լ�ϵͳ�̿��ÿռ�
	void ShowUninstallInfoBar(BOOL bShow);
	void OnBtnSearchBack();	
	void OnUninstallBack(BOOL bClearEditText = FALSE);	
	void RefreshUniPage();
	void GetTheShowPic(int nIndex);     //���������Ϣ��ʱ����������ʾͼƬ

	void ShowQueryAndRefreshBtn( BOOL bShow ); //�Ƿ���ʾ����ť

	void CheckSoftInstallState(const CSimpleArray<CString>& strSoftIDS);

	static void _CheckSoftInstallStateProc(LPVOID lpParam);

	static void DownloadInfoCallBack(int64 cur,int64 all,int64 speed,DWORD time,void* para);

	static unsigned __stdcall ThreadInitDataProc(LPVOID lpVoid);//��ʼ�������̺߳���
	static unsigned __stdcall ThreadProc(LPVOID lpVoid);//���ز����̺߳���
	static unsigned __stdcall InstallProc(LPVOID lpVoid);//��װ�̺߳���
	static unsigned __stdcall ThreadIconProc(LPVOID lpVoid);//����ICON�̺߳���
	static unsigned __stdcall ThreadIniProc(LPVOID lpVoid);//����INI�ļ�
	static unsigned __stdcall ThreadDownloadProc(LPVOID lpVoid);//��������̺߳���
	static unsigned __stdcall ThreadCheckInstallProc(LPVOID lpVoid); //��������װ
	static unsigned __stdcall ThreadUpdateSoftInfoProc(LPVOID lpVoid); //�������������Ϣ
	static unsigned __stdcall ThreadCheckUpateProc(LPVOID lpVoid);	//����������

	virtual HRESULT OnInstSoftComplete(HRESULT hr);

	virtual HRESULT BeforeInstall(const S_KSAI_SOFT_INFO* pstruSoftInfo);
	virtual HRESULT OnProgress(const S_KSAI_STATUS* pstruStatus);
	virtual HRESULT AfterInstall(const S_KSAI_INST_RESULT* pstruInstResult);

public:
	// ���ļ����ڵ�ʱ����а�װ
	BOOL	_InstallSoftExistFile(CSoftListItemData* pData);
	BOOL	CheckSoftCanInstall(CSoftListItemData* pData, BOOL bFromDownOK);		// ��������ϵ�ʱ���Ƿ���Խ��а�װ

	//
	// �ش����ж�ط�����Ϣ
	//

	// �õ���汾
	CString GetLibVersion(LPCWSTR pLibPath);

	BOOL IsNeedUpdate(CSoftListItemData* pData);
	BOOL IsSearchInfo(SOFT_UNI_INFO * pInfo, CWildcard &wildcard);

	CBkNavigator* OnNavigate(CString &strChildName);

	void OnKeyDownReturn(MSG* pMsg);
	VOID QuerySoftMark(LPCTSTR lpstrSoftID);
	void AddToNewInst(LPCTSTR pszSoftId );

protected:
	BOOL _IsChildCtrlMessage(MSG* pMsg, HWND hParent);
	//
	// ֪ͨ�������������������仯
	//
	void NotifySoftUpdateCount(int cnt);

	void _UpdateSoftInfo();
	void _CheckSoftInstall();
	void _LoadPinYinLib();
	void _CheckSoftUpdate();
	void _ChangeArrayToList(CSimpleArray<CSoftListItemData*>& arrIn, CAtlList<CSoftListItemData*>& arrOut);
	void _SortArrayByOrder(CSimpleArray<CSoftListItemData*>& arrIn, CAtlList<CSoftListItemData*>& arrOut);
	void _SortArrayByLastUpdate(CSimpleArray<CSoftListItemData*>& arrIn, CAtlList<CSoftListItemData*>& arrOut);
	void _MoveMaijorFirst(CAtlList<CSoftListItemData*>& arrOut);
	SOFT_UNI_INFO * UniAddOrUpdateItemToList(ksm::SoftData& sd);
	CString GetSoftType(LONG nType);

	void _QuerySoftMark(LPCTSTR lpstrSoftID);
	void _LoadUpdate();

	void _ReloadTypeUni(BOOL bChangeType = TRUE);
	void _ReloadListUni();
	BOOL IsTestSoftPhone( CString& strUrl );

	void DoBibeiCmd(LPCTSTR lpstrCmd);
	void DoDaquanCmd(LPCTSTR lpstrCmd);
	void OnQuerySoftByID(LPCTSTR lpstrSoftId);

public:
	BOOL			m_bInitInterface;	//��־�Ƿ��Ѿ���ʼ������softmgr.dll, ��������, ����softmgr.dat, rank.dat
	BOOL			m_bInit;			// ��־�Ƿ��Ѿ���ʼ��
	BOOL			m_bViewDetail;		//��ʶ�Ƿ����ڲ鿴����
	BOOL			m_bViewUninstall;	//�鿴ж������
	BOOL			m_bInitData;		//�Ƿ��Ѿ���������
	CString			m_strBibeiCmd;		//��������ת
	CString			m_strDaquanCmd;		//��������ת
	BOOL			m_bLoadFail;		//��������ʧ��
	BOOL			m_bCachExist;		//�����ļ��Ƿ����

	BOOL			m_bStartMonitor;	//����Ƿ��Ѿ�����

	BOOL			m_bCleaned;			
	int				m_nUniBtnId;

	CString			m_strErrorHtml;
	CString			m_strAllSoftKeyWord;
	CString			m_strUninstKeyWord;

	CBeikeSafeMainDlg *m_pDlg;			//������ָ��
	Gdiplus::Image *m_pImge;			//ȱʡͼƬ	

	Gdiplus::Image *m_pImageDir;
	Gdiplus::Image *m_pImageFile;
	Gdiplus::Image *m_pImageReg;

	CDetailSoftMgrDlg m_IconDlg;		//��ʾ���ͼ��
	CDetailSoftMgrDlg m_IconUninstallSoft;	//ж������������ʾ���ͼ��
	CDetailSoftMgrDlg m_IconUpdateSoft;		//��������������ʾ���ͼ��

	CBeikeSoftMgrPowerSweepDlg * m_pPowerSweepDlg;

public:
	CSoftMgrQueryEdit				m_editUninstall;	//ж�ز�ѯ�ؼ�
	CSoftMgrQueryEdit				m_edit;				//��ȫ��ѯ�ؼ�
	CSoftMgrListView				m_list;				//�Ҳ���ʾ�����Ϣlistbix
	int								m_nDaquanLastClickHeaderIndex;
	CTypeListBox					m_SoftTypeList;		//����������listbox

	CTypeListBox					m_TypeUni;		
	CSoftMgrUniExpandListView		m_UniExpandSoftList;
	CComboBox						m_comBoBoxUni;
	int								m_nUniLastClickHeaderIndex;
	UniType							m_nUniType;
	BOOL							m_bUniRefresh;
	ksm::ISoftRubbishSweep*			m_pSoftRubbishSweep;	//����ϵͳ�����Ŀ��ƽӿڣ���ʱ�ԣ�

	CSoftUpdatedList				m_softUpdatedList;
	CSoftMgrUpdateRollWnd			m_UpdateSoftList;
	CWHHtmlContainerWindow			m_IEGame;			// ������Ϸ
	CWHHtmlContainerWindow			m_IEDetail;			//����ҳ��IE�ؼ�
	CWHHtmlContainerWindow			m_IEUninstallDetail;	// ж������ҳ��
	CWHHtmlContainerWindow			m_IEUpdateDetail;		// ��������ҳ��
	CFont m_font;					//����list����
	CString m_strCurType;				//��ǰѡ����������
    int m_nCurType;
	CAtlMap<CString,void*>			m_arrTask;		//���ع���
	CAtlMap<void*, CString>			m_arrTaskMap;	//���ع���
	CAtlMap<CString, CString>		m_arrTypeMap; //��typeID��TypeName��ӳ��

	CAtlMap<CString, softInfo*>		m_arrCachInfo;	//���ػ�����Ϣ

	CURLEncode url_encode;				
	BOOL	m_bQuery;					//�Ƿ��@ʾ���������
	BOOL	m_bQueryUni;				//�Ƿ��@ʾ���������
	int 	m_nDown;					//��ǰ�鿴��������
	CString	m_strDetailSoftID;			//��ǰ�鿴��������ID
	int		m_nIndexUpdate;				//����ҳ���鿴�����������
	CString	m_strUpdateDetailSoftID;	//����ҳ���鿴�������ID
	HWND	m_hWndListUpdate;			//����ҳ���鿴��������������ڵ��б�ؼ�
	HANDLE	m_hInstall;					//��װ������
	HANDLE  m_hDownIcon;				//����ICON�߳̾��
	HANDLE  m_hInitData;				//��ʼ���߳̾��
	HANDLE  m_hDownload;				//�����߳̾��
	int  m_nTab;						//��ǰtab
	CComCriticalSection		m_cs;		//�ٽ���
	CComCriticalSection		m_csUpdCacheLock; //����������
	CComCriticalSection		m_csUpdCheckLock; //���������	
	CLock					m_lockIconDown;		// ����ͼ����

	BOOL	m_bViewAll;					// ���ڲ鿴ȫ�����
	BOOL	m_bViewDestTop;				

	CAtlList<CSoftListItemData *>		m_arrDownIconData;		//��Ҫ����ICON�����
	CAtlMap<CString, CSoftListItemData*> m_arrDataMap;			//����ӳ��
	CSimpleArray<CSoftListItemData*>	m_arrData;              // �����ȫ�����������Ϣ
	CSimpleArray<CSoftListItemData*>	m_arrDataSub;           // �����ȫ�е�ǰ���������Ϣ
	CSimpleArray<CSoftListItemData*>	m_arrDataNew;           // �����ȫ�����¸��·��������Ϣ�����ɹ����е����������ڴ�������ܣ�by ������,2011-1-8)

	BOOL								m_bInitUni;
	CString								m_strCurTypeUni;	
	int									m_nCurTypeUni;
	CSimpleArray<SOFT_UNI_INFO*>		m_arrSoftUniDataSub;	//��ǰж�����
	CSimpleArray<SOFT_UNI_INFO*>		m_arrSoftUniData;		//���п�ж�����
	SOFT_UNI_INFO*						m_pSelSoftUniData;		//��ǰѡ�е�ж����Ϣ��ָ��
	CAtlMap<CString, SOFT_UNI_INFO*>	m_arrSoftUniDataMap;	//ж��������б�key������ӳ��
	CSimpleArray<SOFT_RUB_INFO*>		m_arrRubData;			//ϵͳ������Ŀ�б�

	CSimpleArray<CString>				m_arrNewDown;			//��¼�����أ��Ǹ��£������°�װ��
	CAtlList<installParam *>			m_arrInstall;			//���غ���Ҫ��װ�����---��װ��ַ,����
	CAtlList<CSoftListItemData *>		m_arrDownload;			//���غ���Ҫ��װ�����---��װ��ַ,����
	CSimpleArray<CSoftListItemData*>	m_arrCachSetup;			//�����м�¼���Ѱ�װ�������Ϣ
	CSimpleArray<CSoftListItemData*>	m_arrCheckSetup;		//�������Ѱ�װ�����
	CSimpleArray<CSoftListItemData*>	m_arrUpdCache;			//��������		
	CAtlList<CSoftListItemData*>		m_listUpdTemp;			//��������̵߳��������
	CSimpleArray<CSoftListItemData*>	m_arrCheckUpdate;		//�����ֿ������������
	BOOL								m_bInitUpdate;
	int									m_nCountUpdateIgnore;	
	CSimpleArray<CString>				m_arrIgnore;			//���Ը���ID
	int									m_nSoftIdByCmd;			//�����й���Ҫ�����������ID;

	BOOL								m_bShowDownloaded;		// ��־�Ƿ�򿪡��鿴���顱ʱ�����������ء�
	CSoftItemData						m_ItemData;		//�ӿ��ѯ�ٶ�

	//�����ؽӿ�
	HINSTANCE				hInstance;
	pCreateObject			CreateObject;

	ISoftManager*			m_pSoftMgr;			
	ISoftCheckerEx*			m_pSoftChecker;
	IDTManager*				m_pDTManager;
	IDTManager*				m_pDTManagerOneKey;		// һ��װ����

	IDownload *				m_pDownload;
	ksm::ISoftUninstall2*	m_pUninstall;

	BOOL					m_bInitInfoQuery;
	ksm::ISoftInfoQuery*	m_pInfoQuery;

	CBkDialogView			m_dlgTip;
	CBkDialogView			m_SoftListTip;

	CBkSafeSoftMgrUnstDlg*	m_dlgSoftMgrUninstall;	// ���ж�ضԻ���

	CBeikeSafeSoftmgrNecessHandler	m_necessUIHandler;
	ksm::CSoftInstProxy				m_softInstEng;
	BOOL							m_bInitInstProxy;

#if PHONE_NESS_SWITCH
	//
	// �ֻ��ر�
	//
private:
	enum PhoneDownState
	{
		PDS_NONE	= 0,
		PDS_INIT,
		PDS_DOWNING,
		PDS_DONE,
		PDS_PAUSED,
		PDS_ERROR_MD5,
		PDS_ERROR,
	};

	typedef struct PhoneSoft
	{
		void*		idDown;		// ���ر�ʶ
		PhoneDownState
					state;		// ����״̬
		ULONG		speed;		// �ٶ�
		ULONG		recved;		// �������ֽ���
	} *PPhoneSoft;

	typedef CAtlMap<void*, LONG> Dt2IdMap;
	typedef CAtlMap<LONG, PhoneSoft> Id2PhoneSoftMap;

	typedef Dt2IdMap::CPair* Dt2IdIter;
	typedef Id2PhoneSoftMap::CPair* Id2PhoneSoftIter;

	typedef CComCritSecLock<CComCriticalSection> CriticalSectionScoped;

private:
	BOOL				m_phoneLoaded;
	BOOL				m_recommendLoaded;
	IDTManager			*m_pPhoneDTMgr;
	CWebBrowserExternal	m_IESoftRecommend;
	CWebBrowserExternal	m_IEPhoneNess;
	CComCriticalSection	m_csPhoneNess;
	Dt2IdMap			m_dt2Id;
	Id2PhoneSoftMap		m_id2PhoneSoft;

public:
	// ��ȡ���ؽӿڣ����ڱ�Ҫʱ�Ŵ������ع������
	IDTManager* GetDTMgrForPhone();
	static void PhoneSoftDownInfoCallback(__int64 cur,__int64 all,__int64 speed,DWORD time,void* para);
	static void PhoneSoftDownCallback(DTManager_Stat st,void* tk,void* para);
	void PhoneSoftDownProcess(DTManager_Stat st, void *tk);
	// Js�ӿ�
	HRESULT PhoneSoftExists(DISPID, DISPPARAMS*, VARIANT*);
	HRESULT PhoneStartDown(DISPID, DISPPARAMS*, VARIANT*);
	HRESULT PhonePauseDown(DISPID, DISPPARAMS*, VARIANT*);
	HRESULT PhoneResumeDown(DISPID, DISPPARAMS*, VARIANT*);
	HRESULT PhoneStopDown(DISPID, DISPPARAMS*, VARIANT*);
	HRESULT PhoneGetDownState(DISPID, DISPPARAMS*, VARIANT*);
	HRESULT PhoneOpenDownedSoft(DISPID, DISPPARAMS*, VARIANT*);

	HRESULT PhoneNavigatePage(DISPID, DISPPARAMS*, VARIANT*);
	HRESULT ReportInfo(DISPID, DISPPARAMS*, VARIANT*);

private:
	// window.externalʵ�ֽӿ�
	STDMETHOD(QueryInterface)(REFIID riid, void **ppvObject);
	STDMETHOD_(ULONG, AddRef)() { return 1; }
	STDMETHOD_(ULONG, Release)() { return 1; }

	STDMETHOD(GetTypeInfoCount)(UINT *pctinfo) { return E_NOTIMPL; }
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo) { return E_NOTIMPL; }
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
#endif

public:
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		BK_NOTIFY_REALWND_RESIZED(IDC_LIST_SOFTMGR, OnListReSize)
		BK_NOTIFY_ID_COMMAND(IDC_UPDATE_CHECKBOX_ALL, OnUpdateCheckAll)
		BK_NOTIFY_ID_COMMAND(IDC_UPDATE_IGNORE_TEXT, OnUpdateBtnIgnore)
		BK_NOTIFY_ID_COMMAND(IDC_UPDATE_VIEW_IGNORE, OnUpdateBtnIgnore)
		BK_NOTIFY_ID_COMMAND(IDC_UPDATE_BACK_DETAIL, OnUpdateDetailBack)
		BK_NOTIFY_ID_COMMAND(IDC_UPDATE_SELECT_SOFT, OnUpdateSelectSoft )
		BK_NOTIFY_ID_COMMAND(IDC_UPDATE_BTN_DETAIL, OnUpdateFromeDetail)
		BK_NOTIFY_ID_COMMAND(IDC_DOWNLOADMGR_SOFTMGR, OnDownloadMgr)
		BK_NOTIFY_ID_COMMAND(IDC_CHECKBOX_DAQUAN_NOPLUGSOFT, OnShowNoPlugSoft)
		BK_NOTIFY_ID_COMMAND(IDC_CHECKBOX_DAQUAN_FREESOFT, OnShowFreeSoft)
		BK_NOTIFY_ID_COMMAND(IDC_SETTING_SOFTMGR, OnSetting)
		BK_NOTIFY_ID_COMMAND(IDC_REFRESH_SOFTMGR, OnRefresh)
		BK_NOTIFY_ID_COMMAND(IDC_QUERY_SOFTMGR, OnQuerySoft)
		BK_NOTIFY_ID_COMMAND(IDC_SOFT_BTN2_QUERY, OnQuerySoft)
		BK_NOTIFY_ID_COMMAND(IDC_SOFT_DAQUAN_BTN_QEURY_EDIT, OnClearDaquanQeuryEdit)
		BK_NOTIFY_ID_COMMAND(IDC_SOFT_UNISTALL_BTN_QEURY_EDIT, OnClearUninstallQeuryEdit)

		BK_NOTIFY_ID_COMMAND(IDS_BACK_DETAIL_SOFTMGR, OnBack)
		BK_NOTIFY_ID_COMMAND(IDC_BACK_QUERY_SOFTMGR, OnBackFromQuery)
		BK_NOTIFY_ID_COMMAND(IDC_BACK_QUERY_SOFTMGR_ICO, OnBackFromQuery)
		BK_NOTIFY_ID_COMMAND(IDC_BACK_QUERY_UNI_SOFTMGR, OnBtnSearchBack)
		BK_NOTIFY_ID_COMMAND(IDC_BACK_QUERY_UNI_SOFTMGR_ICO, OnBtnSearchBack)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_SEARCH_GOBACK, OnBackFromInsQuery)
		BK_NOTIFY_ID_COMMAND(IDC_LNK_GOBACK, OnUninstallDetailBack)
		BK_NOTIFY_ID_COMMAND(IDC_LNK_CUR_PAGE, OnLnkCurrentBack)
		BK_NOTIFY_ID_COMMAND( IDC_LINK_UNINSTALL_OPENDIR, OnUninstallOpenDir )
		BK_NOTIFY_ID_COMMAND(IDC_DOWN_BTN_DETAIL_SOFTMGR, OnDownLoadFromeDetail)
		BK_NOTIFY_ID_COMMAND(IDC_FREEBACK_SOFTMGR, OnFreeBack)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_UNINSTALL_DO, OnDetailUninstall)
		BK_NOTIFY_ID_COMMAND(IDS_LINK_TIP2_SOFTMGR, OnTransferFromQuery)
		BK_NOTIFY_ID_COMMAND(IDC_TXT_SEARCH_CON3, OnTransferUninstall)
		BK_NOTIFY_ID_COMMAND(IDS_LINK_SUBMIT_SOFTMGR, OnSubmitSoft)
		BK_NOTIFY_ID_COMMAND( IDC_BTN_UNI_ALL, OnBtnUniAll )
		BK_NOTIFY_ID_COMMAND( IDC_BTN_UNI_DESK, OnBtnUniDesk )
		BK_NOTIFY_ID_COMMAND( IDC_BTN_UNI_STARTMENU, OnBtnUniStartMenu )
		BK_NOTIFY_ID_COMMAND( IDC_BTN_UNI_QUICKLAN, OnBtnUniQuickLan )
		BK_NOTIFY_ID_COMMAND( IDC_BTN_UNI_PROCESS, OnBtnUniProcess )
		BK_NOTIFY_ID_COMMAND( IDC_BTN_UNI_TRAY, OnBtnUniTray )
		BK_NOTIFY_ID_COMMAND( IDC_LNK_WATCH_LASTUSE, OnBtnSwitchWatch)
		BK_NOTIFY_ID_COMMAND( IDC_DLG_RESIDUAL_CLEAR, OnBtnResidualClear)
		BK_NOTIFY_ID_COMMAND( IDC_LINK_RUBBISH_CLEAR, OnBtnRubbishClear)
		BK_NOTIFY_ID_COMMAND( IDC_LINK_SYSTEM_SLIM, OnBtnSystemSlim)

		BK_NOTIFY_ID_COMMAND(IDC_SOFT_DAQUAN_LEFT_RESTART,OnReStart)
		BK_NOTIFY_ID_COMMAND(IDC_SOFT_DAQUAN_LEFT_IGNORE_VER_TIP,OnIgnoreReStartTip)
		BK_NOTIFY_ID_COMMAND(IDC_SOFT_DAQUAN_LEFT_CLOSE_VER_TIP,OnCloseReStartTip)
		BK_NOTIFY_ID_COMMAND(IDC_SOFT_UPDATE_LEFT_RESTART,OnReStart)
		BK_NOTIFY_ID_COMMAND(IDC_SOFT_UPDATE_LEFT_IGNORE_VER_TIP,OnIgnoreReStartTip)
		BK_NOTIFY_ID_COMMAND(IDC_SOFT_UPDATE_LEFT_CLOSE_VER_TIP,OnCloseReStartTip)

		BK_NOTIFY_ID_COMMAND_EX(IDC_SOFTMGR_DAQUAN_TYPE_FIRST, IDC_SOFTMGR_DAQUAN_TYPE_LAST, OnClickDaquanType)
		BK_NOTIFY_ID_COMMAND_EX(IDC_SOFTMGR_XIEZAI_TYPE_FIRST, IDC_SOFTMGR_XIEZAI_TYPE_LAST, OnClickXiezaiType)

		BK_NOTIFY_ID_COMMAND( IDC_SMR_DAQUAN_HEADER_NAME, OnBtnSmrDaquanSortByName)
		BK_NOTIFY_ID_COMMAND( IDC_SMR_DAQUAN_HEADER_SIZE, OnBtnSmrDaquanSortBySize)
		BK_NOTIFY_ID_COMMAND( IDC_SMR_DAQUAN_HEADER_TIME, OnBtnSmrDaquanSortByTime)
		BK_NOTIFY_ID_COMMAND( IDC_SMR_UNI_HEADER_NAME, OnBtnSmrUniSortByName)
		BK_NOTIFY_ID_COMMAND( IDC_SMR_UNI_HEADER_SIZE, OnBtnSmrUniSortBySize)
		BK_NOTIFY_ID_COMMAND( IDC_SMR_UNI_HEADER_TIME, OnBtnSmrUniSortByTime)
		BK_NOTIFY_ID_COMMAND(IDC_SET_IE_MAINHOME_SOFTMGR, OnSetIEMainhome)
		BK_NOTIFY_ID_COMMAND(IDC_SET_DESKTOP_LINK_SOFTMGR, OnSetDesktopLink)
		BK_NOTIFY_ID_COMMAND( IDC_UNINSTALL_QUERYBACK_LNK, OnUninstallDetailBack )
		BK_NOTIFY_TAB_SELCHANGE(IDC_TAB_SOFTMGR, OnTabSoftMgrSelChange)

		BK_NOTIFY_ID_COMMAND(IDC_SOFT_UNISTALL_BTN2_QEURY_EDIT, OnQueryUninstall)

		BK_NOTIFY_MAP_END()

		BEGIN_MSG_MAP_EX(CBeikeSafeSoftmgrUIHandler)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP_MEMBER(m_necessUIHandler)
		COMMAND_HANDLER(IDC_SOFT_UNISTALL_EDT_QEURY_EDIT, EN_CHANGE, OnChangeUninstallEdit)
		COMMAND_HANDLER(IDC_EDIT_SOFTMGR, EN_CHANGE, OnChangeDaquanEdit)
		COMMAND_HANDLER_EX(IDS_CLASS_COMBO_UNI_SOFTMGR, CBN_SELCHANGE, OnUniComboBoxSelect)
		MSG_WM_TIMER(OnTimer)
		MSG_WM_SIZE(OnSize)
		MSG_WM_MOUSEWHEEL(OnMouseWheel)

		MESSAGE_HANDLER(WM_NET_ERROR_REFRESH, OnRefreshNetPage)

		MESSAGE_HANDLER_EX(WM_BOTTOM_REFRESH, OnSoftmgrRefreshBottom)
		MESSAGE_HANDLER_EX(WM_LOADTIP_REFRESH, OnOnSoftmgrRefreshLoadTip)
		MESSAGE_HANDLER_EX(WM_SOFT_INIT_FINISH, OnSoftmgrInitFinish)
		MESSAGE_HANDLER(WM_USER_SET_CHECK_LIST, OnSetCheckListNotify)
		MESSAGE_HANDLER(MSG_APP_LOAD_UPDATE_CACHE, OnLoadUpdateCache)
		MESSAGE_HANDLER(MSG_APP_LOAD_UPDATE_REAL, OnLoadUpdateReal)
		MESSAGE_HANDLER(MSG_APP_UPDATE_UNI_TYPE, OnUpdateUniType)
		MESSAGE_HANDLER_EX(WM_UPDATE_SOFT_COUNT, OnUpdateSoftCount)
		MESSAGE_HANDLER_EX(WM_SOFT_REFRESH_ITEM, OnRefershItemBySoftID)
		MESSAGE_HANDLER_EX(WM_SOFT_REFRESH_CANLIU,OnRefershRubbishInfo)
		MESSAGE_HANDLER_EX(WM_SOFT_UNI_ALL_REFRESH_FINISH,OnRefershUniAllSoftFinish)
		MESSAGE_HANDLER_EX(WM_SOFT_UE_DATA_COMPLETED,OnSoftmgrUEDataCompleted)
		MESSAGE_HANDLER_EX(WM_SOFT_UE_HIDE_HEADER_ARROW,OnSoftmgrUEHideHeaderArrow)
		MESSAGE_HANDLER_EX(WM_SOFT_FRESH_TOTAL,OnSoftmgrFreshTotal)
		MESSAGE_HANDLER_EX(WM_SOFT_UE_SORT_BY_NAME,OnSoftmgrUESortByName)
		MESSAGE_HANDLER_EX(WM_SOFT_REFRESH_UNI_TYPE,OnSoftmgrRefreshUniType)
		MESSAGE_HANDLER_EX(WM_SOFT_UE_SHOW_UNIDATAPAGE,OnSoftmgrUEShowUniDataPage)
		MESSAGE_HANDLER_EX(WM_SOFT_INSTALL_CHECK,OnCheckSoftCanInstall)
		MESSAGE_HANDLER_EX(WM_SOFT_INSTALL_NOTIFY,OnNotifySoftInstall)
		END_MSG_MAP()

private:
	HANDLE	m_hUpdSoftInfoThread;		//��ȡ�����Ϣ���߳̾��
	HANDLE	m_hCheckInstallThread;		//��������װ���߳̾��
	HANDLE	m_hCheckUpdateThread;		//�������������߳̾��

	HANDLE	m_hSignLoadFinish;		//�����������
};
