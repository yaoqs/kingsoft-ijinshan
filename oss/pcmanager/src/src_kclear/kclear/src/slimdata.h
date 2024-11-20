//////////////////////////////////////////////////////////////////////////
// Creator: Leo Jiang<JiangFengbing@gmail.com>

#ifndef KCLEAR_SLIMDATA_H_
#define KCLEAR_SLIMDATA_H_

//////////////////////////////////////////////////////////////////////////

#include "kscbase/ksclock.h"
#include "slimcallback.h"

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// ������Ŀ����
class SlimItem : public ISystemSlimCallBack
{
public:
    SlimItem();
    explicit SlimItem(const SlimItem& item);
    ~SlimItem();

    int Id() const;
    void SetId(int nId);

    CString Name() const;
    void SetName(const CString& strName);

    CString Description() const;
    void SetDescription(const CString& strDescription);

    CString Warning() const;
    void SetWarning(const CString& strWarning);

    void InsertPath(const CString& strPath, const CStringA& strOsFlag);
    void GetPaths(CAtlArray<CString>& itemPaths) const;

    BOOL IsEnable() const;
    void CheckEnable();

    BOOL UndoEnable() const;
    void SetUndoEnable(BOOL bEnable);

    SlimMethod Method() const;
    void SetMethod(SlimMethod nMethod);

    KLockHandle Lock() const;
    void SetLock(KLockHandle lock);

    BOOL BeginProcess(HWND hNotifyWnd);
    void CancelProcess();

    BOOL Valid() const;
    ULONGLONG SizeOnDisk() const;
    ULONGLONG SizeMaySave() const;
    ULONGLONG SizeSaved() const;

    ISystemSlimCallBack* Callback() const;
    void SetCallback(ISystemSlimCallBack* piCallback);

    void BeginScan(HWND hNotifyWnd);
    void StopScan();

    // ��õ�ǰ���ڴ���Ķ���
    void GetCurrentFile(CString& strFilePath);

    // ɨ��ĳ��������ļ�
    virtual BOOL OnScanItem(
        const wchar_t* szFilePath,
        ULONGLONG qwFileSizeOnDisk,
        BOOL bCompressed
        );

    // ����ĳ��������ļ�
    virtual BOOL OnBeginProcessItem(
        const wchar_t* szFilePath
        );

    virtual BOOL OnEndProcessItem(
        const wchar_t* szFilePath,
        ULONGLONG qwSavedSize
        );

    // ���кͿ����˳�
    virtual BOOL OnIdle(
        );

protected:
    static UINT WINAPI ProcessThreadProc(void* pParam);
    BOOL DeletePaths();
    BOOL CompressPaths();
    static UINT WINAPI ScanThreadProc(void* pParam);
    void ScanPathSync();
    void _FindPath(const CString& strPath);
    void _GetWallpaperFilterPath(CString& strPath);

private:
    int m_nId;
    CString m_strName;
    CString m_strDescription;
    CString m_strWarning;
    CAtlArray<CString> m_itemPaths;
    BOOL m_bEnable;
    SlimMethod m_nMethod;
    HWND m_hNotifyWnd;
    HANDLE m_hWorkThread;
    ISystemSlimCallBack* m_piCallback;
    ULONGLONG m_qwSizeOnDisk;   // ռ�ô��̴�С
    ULONGLONG m_qwSizeMaySave;  // Ԥ�ƿ��Խ�ʡ��С
    ULONGLONG m_qwSizeSaved;    // ʵ�ʽ�ʡ�Ĵ�С
    BOOL m_bStopScanFlag;
    BOOL m_bUndoEnable;
    CString m_strCurrentProcess;
    KLockHandle m_lock;
};

//////////////////////////////////////////////////////////////////////////
// ������������
class SlimData
{
public:
    SlimData();
    ~SlimData();

    BOOL LoadData(HWND hNotifyWnd);
    void ClearData();

    BOOL IsEmpty();
    CString GetName(int nIndex);

    int GetCount();
    int GetValidCount();
    int GetEnalbeCount();
    ULONGLONG GetSizeMaySaved();

    void Scan(int nIndex, HWND hNotifyWnd);

    SlimItem& GetItem(int nIndex);

protected:
    static UINT WINAPI LoadDataThreadProc(void* pParam);
    BOOL LoadDataSync();

private:
    CAtlArray<SlimItem> m_slimItems;
    KLock m_lock;
    KLock m_sharedLock;
    HWND m_hNotifyWnd;
};

//////////////////////////////////////////////////////////////////////////

#endif // KCLEAR_SLIMDATA_H_
