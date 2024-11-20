#pragma once

//////////////////////////////////////////////////////////////////////////

#include "kscbase/ksclock.h"
#include "kclear/ifcache.h"
#include "bigfilehelper.h"
#include "bigfilelistctrl.h"
#include "vdirctrl.h"
#include "bigfilelistwrapper.h"
#include "kclear/libheader.h"

//////////////////////////////////////////////////////////////////////////

// ��չ����Ϣ
typedef struct tagBigExtInfo {
    CString strExt;
    ULONGLONG qwTotalCount;
    ULONGLONG qwTotalSize;
    UINT nPercent;

    bool operator < (const struct tagBigExtInfo& extInfo) const
    {
        return qwTotalSize < extInfo.qwTotalSize;
    }

} BigExtInfo;

typedef enum tagVirtualDirType {
    enumVDT_Dir = 0,        // �����������
    enumVDT_Volume = 1,     // ��
} VirtualDirType;

typedef enum tagRealDirType {
    enumRDT_Desktop = 0,    // �ҵ�����
    enumRDT_Document = 1,   // �ҵ��ĵ�
    enumRDT_Download = 2,   // ����Ŀ¼
    enumRDT_Other,
} RealDirType;

//////////////////////////////////////////////////////////////////////////

typedef enum tagBigFileTimerId {
    enumBFTI_Animation = 0, // ����
    enumBFTI_ScanPath = 1,
} BigFileTimerId;

//////////////////////////////////////////////////////////////////////////

// ʹ��WM_COMMAND�������ڲ�ID
typedef enum tagBigFileInternalId {
    enumBFII_ScanEnd = 0,   // ɨ�����
    enumBFII_CtrlId = 888,  // ID
} BigFileInternalId;

//////////////////////////////////////////////////////////////////////////

#include "kclearmsg.h"

//////////////////////////////////////////////////////////////////////////
class CBigfileFilter
{
public:
    static CBigfileFilter& Instance();
    BOOL LoadFilter();
    BOOL IsFileInFilter(const CString& strFilepath);
   
private:
    CBigfileFilter();
    ~CBigfileFilter();
   
private:
    std::vector<CString> m_vsysExt;
    std::vector<CString> m_vsysFile;
    std::vector<CString> m_vsysDir;
};


// ����Ŀ¼������
class CVirtualDirManager 
    : public IFCacheQueryback
    , public IEnumFileback
{
public:
    CVirtualDirManager();
    virtual ~CVirtualDirManager();

    void SetDirType(VirtualDirType nType);
    VirtualDirType GetDirType();

    void SetRealDirType(RealDirType nType);
    RealDirType GetRealDirType();

    void SetName(const CString& strName);
    CString GetName();

    void SetVolumeChar(CHAR cVol);
    CHAR GetVolumeChar();
    void UpdateVolumeSizeInfo();

    void SetSysVolume();
    BOOL IsSysVolume();

    void SetRemovable(BOOL bRemovable);

    void GetStatus(CString& strStatus);

    void GetCacheList(std::vector<BigFileInfo>& vCacheList, size_t nLimit, size_t& nMore);
    void CopyTopListToCacheList();

    // ���Top���Ͱ�
    void GetTopExts(std::vector<BigExtInfo>& vTopExts);

    // ���Top100�Ĵ��ļ�
    void GetTop100Files(std::vector<BigFileInfo>& vTopFiles);
    void GetTop100Size(ULONGLONG& qwSize);

    // ���չ����������в�ѯ
    void QueryFilesWithFilter(
        std::vector<BigFileInfo>& vFiles, 
        const CString& strExt, 
        ULONG dwSizeLimit
        );

    void SetNotify(HWND hWnd);
    void OnFileListSize(CRect rcZone);
    HWND InitCtrl(HWND hParent);        // �����ؼ�
    CBigFileListCtrl& GetCtrl();

    void SetSizeFilter(int idx);
    int GetSizeFilter();
    void SetSizeFilterEnable(BOOL fEnable);
    void SetSysFilterEnable(BOOL bEnable);
    BOOL GetSysFilterEnable();
    BOOL GetSizeFilterEnable();
    void SetExtFilter(const CString& strExt);
    void GetExtFilter(CString& strExt);
    void SetListLimit(DWORD dwLimit);

    BOOL FillListCtrl();    // ���ݹ��������������б�
    void CleanBigFileList();

    BOOL LoadCacheASync();
    BOOL LoadCacheSync();      // �����ݿ����Top100����
    static UINT WINAPI LoadCacheThread(LPVOID pParam);
    void GetCacheSummary(CString& strSummary);

    BOOL GetBigFileInfo(size_t idx, BigFileInfo& fileInfo);
    BOOL DeleteBigFile(const CString& strFilePath);

    BOOL StartScan();       // ��ʼɨ��
    BOOL StopScan();        // ֹͣɨ��
    BOOL IsScanning();      // �Ƿ�����ɨ��
    void GetScanningFile(CString& strFilePath, int& nPos); // �������ö�ٵ��ļ�

    BOOL StartFillList();   // ��ʼ���List
    BOOL StopFillList();    // ֹͣ���List
    BOOL IsFilling();       // �Ƿ��������

    CVirtualDirManager& FindParentVirtualDir();

    static UINT WINAPI ScanThread(LPVOID pParam);
    static UINT WINAPI FillThread(LPVOID pParam);

    static BOOL ShowFileProperties(const CString& strFilePath);

    // ʵ�ֲ�ѯ�����callback
    virtual void OnData(
        FCacheQueryType nQueryType,
        LPCWSTR lpFilePath,
        ULONGLONG qwFileSize
        );

    virtual void OnExtData(
        LPCWSTR lpExt,
        ULONGLONG qwSize,
        ULONGLONG qwCount
        );

    virtual void BeginEnum();
    virtual BOOL OnFindFile(const BigFileInfo& fileInfo);
    virtual void EndEnum(BOOL bCanceled);
    EnumState GetEnumState();

    BOOL IsFilterFile(const CString& strFile);

//protected:
    IFCache* GetFCache();
    BOOL GenerateCacheForTopExts();             // ɨ�����ʱ����Top��Ļ���(�ȽϺ�ʱ)
    BOOL GenerateCacheForTop100();              // ɨ�����ʱ����Top500�Ļ���(�ȽϺ�ʱ)
    BOOL GetSummaryInfo();                      // ɨ�����ʱ�����ܴ�С������Ŀ��ͳ��(�ȽϺ�ʱ)
    void GetEnumPaths(std::vector<CString>& vEnumPaths);    // �����Ҫö�ٵ�Ŀ¼

//protected:
    KLock m_lock;
    KLock m_lockStatus;                         // ����ɨ��·��ר��
    std::vector<BigFileInfo> m_vTopFiles;       // ���Top500
    std::vector<BigExtInfo> m_vTopExts;         // ���Top��չ��
    HWND m_hNotifyWnd;                          // ֪ͨ����
    CString m_strName;                          // ��ʾ����
    CHAR m_cVolume;                             // ���ھ�
    VirtualDirType m_nType;                     // ����
    RealDirType m_nDirType;                     // Ŀ¼����(�����dir���͵Ļ�)
    ULONGLONG m_qwTotalSize;                    // �ܴ�С
    ULONGLONG m_qwTotalCount;                   // ����Ŀ
    //BOOL m_bScanning;                         // ����ɨ��
    BOOL m_bFilling;                            // �������
    //HANDLE m_hScanThread;                     // ɨ���߳̾��
    HANDLE m_hFillThread;                       // ����߳̾��
    BOOL m_bStopScanFlag;                       // ֹͣɨ��ı��
    BOOL m_bStopFillFlag;                       // ֹͣ���ı��
    EnumState m_nEnumState;                     // ö��״̬
    ULONGLONG m_qwEnumedSize;                   // �Ѿ�ö���˵Ĵ�С
    CString m_strCurrentFile;                   // ����ö�ٵ��ļ�
    BOOL m_bSysVolume;                          // �Ƿ�Ϊϵͳ��
    BOOL m_bRemovable;                          // �Ƿ�Ϊ�ƶ�Ӳ��

    BOOL m_bSysFilter;                           //�Ƿ�Ϊϵͳ�ļ�

    std::vector<BigFileInfo> m_vCacheFiles;     // �ϴβ�ѯ����Ļ���
    std::vector<CString> m_vDeleteCache;    // ɾ��Cache(����û�����ݿ�����)
    CString m_strCacheExt;                      // �ϴβ�ѯ����չ��
    ULONGLONG m_qwSizeFilter;                   // �ϴβ�ѯ�Ĵ�С����
    BOOL m_bEnableSizeFilter;                   // ��С���ƵĿ���
    CString m_strExtFilter;                     // ��չ����������
    IFCache* m_piFCache;                        // ���ݿ���ʽӿ�
    SYSTEMTIME m_CacheTime;
    BOOL m_bFullCache;

    ULONGLONG m_qwVolTotalSize;                 // ���ھ��ܴ�С
    ULONGLONG m_qwVolFreeSize;                  // ���ھ�ʣ��ռ�

    CBigFileListCtrl m_ctrlFileList;            // FileList�ؼ�(��������Ŀ¼)
    DWORD m_dwFileListLimit;                    // FileList�ؼ�����Ŀ����
};

//////////////////////////////////////////////////////////////////////////

class CUIHandlerBigFile
{
public:
    CUIHandlerBigFile(CKscMainDlg* refDialog);
    virtual ~CUIHandlerBigFile();

    // for container
    void Init();
	void InitDelay();
    void UnInit();
    void Show();

protected:
    BOOL CreateDirectoryCtrls();
    BOOL CreateFileListCtrl();
    BOOL CreateFilterBox();
    BOOL StartBackgroundScan();

    HMENU InitFileContextMenu();
    HMENU InitExtFilterMenu();
    void OnExtFilterContext();

    BOOL LoadFCache();
    
    BOOL OnStartScan(); // ��ʼɨ��
    BOOL OnStopScan();  // ֹͣɨ��
    BOOL OnReScan();    // ����ɨ��

    // win32�ؼ���ReSize
    void OnDirectoryCtlReSize(CRect rcZone);
    void OnFileListSize(CRect rcZone);
    void OnComboboxReSize(CRect rcZone);

    void OnSizeLimitCheck();    // ��С����CheckBox�Ĺ�ѡ
    void OnSwitchVDir(size_t nItem, size_t nSubItem);
    void OnSysFilterLnk();

    KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
        //MESSAGE_HANDLER(MSG_USER_LDLISTVIEWCTRL_LBP_URL, OnFileListViewClickUrl)
        KUI_NOTIFY_REALWND_RESIZED(ID_CTL_BIGFILE_LISTLEFT, OnDirectoryCtlReSize)
        KUI_NOTIFY_REALWND_RESIZED(ID_CTL_BIGFILE_SIZE_COMBOBOX, OnComboboxReSize)
        KUI_NOTIFY_REALWND_RESIZED(ID_CTL_BIGFILE_LISTRIGHT, OnFileListSize)
        KUI_NOTIFY_ID_COMMAND(ID_BTN_BIGFILE_ENUM_START, OnStartScan)
        KUI_NOTIFY_ID_COMMAND(ID_BTN_BIGFILE_ENUM_STOP, OnStopScan)
        KUI_NOTIFY_ID_COMMAND(ID_CHK_BIGFILE_SIZE_LIMIT, OnSizeLimitCheck)
        KUI_NOTIFY_ID_COMMAND(ID_BTN_BIGFILE_RESCAN, OnReScan)
        KUI_NOTIFY_ID_COMMAND(ID_BTN_BIGFILE_FILTER_MENU1, ShowTopExtMenu)
        KUI_NOTIFY_ID_COMMAND(ID_BTN_BIGFILE_FILTER_MENU2, ShowTopExtMenu)
        KUI_NOTIFY_ID_COMMAND(ID_TXT_BIGFILE_FILTER, ShowTopExtMenu)
        KUI_NOTIFY_ID_COMMAND(ID_CHK_SYSFILE_DISPLAY, OnSysFilterLnk)
    KUI_NOTIFY_MAP_END()

    BEGIN_MSG_MAP_EX(CUIHandlerBigFile)
        MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
        MSG_WM_TIMER(OnTimer)
        MSG_WM_COMMAND(OnCommand)
        MESSAGE_HANDLER(WM_BIGFILE_SCAN_END, OnScanEnd)
        MESSAGE_HANDLER(WM_BIGFILE_LIST_LINK, OnListLink)
        MESSAGE_HANDLER(WM_BIGFILE_LIST_MORE, OnListMore)
        MESSAGE_HANDLER(WM_BIGFILE_LIST_DBCLICK, OnListDBClick)
        MESSAGE_HANDLER(WM_BIGFILE_LIST_CONTEXT, OnListContext)
        // ���˲˵�
        MSG_WM_INITMENUPOPUP(OnInitMenuPopup)
        MSG_WM_MENUSELECT(OnMenuSelect)
        MSG_WM_DRAWITEM(OnDrawItem)
        MSG_WM_MEASUREITEM(OnMeasureItem)

    END_MSG_MAP()

    // ��Ϣ��Ӧ����
    void OnTimer(UINT_PTR nIDEvent);   // ������ʱ��
    void OnCommand(UINT uNotifyCode, int nID, CWindow wndCtl);
    void OnInitMenuPopup(CMenu menuPopup, UINT nIndex, BOOL bSysMenu);  // ���˲˵�
    void OnMenuSelect(UINT nItemID, UINT nFlags, CMenu menu);
    void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    LRESULT OnFileListViewClickUrl(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); // FileList��Url���
    LRESULT OnScanEnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); 
    LRESULT OnListLink(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); 
    LRESULT OnListMore(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); 
    LRESULT OnListDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); 
    LRESULT OnListContext(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    // ��������
    HICON GetIconFromFileType(LPCTSTR lpExtName);   // ����չ�����ͼ��

    void ShowFilterUI(BOOL bShow = TRUE);    // ��ʾ/���� ���˲˵�&����CheckBox
    void ShowReScanButton(BOOL bShow = TRUE);      // ��ʾ/���� ����ɨ�谴ť
    void ShowScanButton();                          // ��ʾɨ�谴ť(��)
    void ShowScanProgress();                        // ��ʾɨ�����
    void HideScanUI();                              // ����ɨ�����
    void ShowFileList(BOOL bShow = TRUE);           // ��ʾ/���� ��ǰFileList
    BOOL ShowTopExtMenu();                          // ��ʾTop��չ���˵�
    void UpdateHeaderTip();                         // ˢ�¶�����ʾ��
    void UpdateFileListWithExt(int idx);            // �������õĹ�������������ˢ��
    void UpdateFileSizeWithSize(int idx);           // �������õĹ�������������ˢ��

    // ���ܺ���
    BOOL DelBigFile(int idx);
    BOOL DelBigFile(const CString& strFilePath);    // ɾ�����ļ�
    BOOL DoMoveJobs(const CString& strDest, const CString& strSource, ULONGLONG& llSize);
    BOOL DoDelJobs(const CString& strFilePath, BOOL bType);
    static BOOL SaveAutoDestDir(CString& strDir);

    CKscMainDlg* m_dlg; // ����
    CBigFileListWrapper m_listWrapper;  // FileList������
    size_t m_nCurrentVirtualDir;   // ��ǰ�������Ŀ¼
    CVirtualDirCtrl m_ctrlVirtualDirs;
    CVirtualDirManager* m_pCurrentDir;
    CComboBox m_boxSizeLimit;
    HMODULE m_hFCacheModule;
    CString m_strDestDir;   // Ĭ��Ǩ��Ŀ¼
};

//////////////////////////////////////////////////////////////////////////
