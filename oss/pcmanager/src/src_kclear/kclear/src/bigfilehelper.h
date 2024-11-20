#pragma once

//////////////////////////////////////////////////////////////////////////

// ����Ϣ
typedef struct tagVolInfo {
    CHAR cVol;
    CString strVolName;
    ULONGLONG qwTotalSize;  // �ܴ�С
    ULONGLONG qwFreeSize;   // ʣ���С
    BOOL bRemovable;
} VolInfo;

// �ļ���Ϣ
typedef struct tagBigFileInfo {
    CString strFilePath;
    CString strExt;
    ULONGLONG qwFileSize;

    bool operator < (const struct tagBigFileInfo& fileInfo) const
    {
        return qwFileSize < fileInfo.qwFileSize;
    }

    bool operator==(const CString& strFilePath) const {
        if (strFilePath.CompareNoCase(this->strFilePath) == 0)
            return true;
        return false;
    }  

    bool Equal(const CString& strFilePath) const
    {
        if (strFilePath.CompareNoCase(this->strFilePath) == 0)
            return true;
        return false;
    }

} BigFileInfo;

typedef enum tagEnumState {
    enumES_Notstart = 0,    // û�п�ʼ
    enumES_Scanning = 1,    // ����ö��
    enumES_Canceled = 2,    // ��ȡ��
    enumES_Finished = 3,    // ����ö�ٽ���
    enumES_Cache = 4,       // �ɵ�����
} EnumState;

//////////////////////////////////////////////////////////////////////////

struct IEnumFileback {
    //virtual void Lock() = 0;
    //virtual void UnLock() = 0;
    virtual void BeginEnum() = 0;
    virtual void EndEnum(BOOL bCanceled) = 0;
    virtual BOOL OnFindFile(const BigFileInfo& strFilePath) = 0;
};

//////////////////////////////////////////////////////////////////////////

namespace bigfilehelper
{
    // ��ʾ�ļ�����
    void ShowFileProperties(LPCTSTR lpFilePath);

    // ��λ�ļ�
    BOOL LocateFile(const CString& strFilePath);

    // ɾ���ļ�
    BOOL Recycle(LPCTSTR pszPath, BOOL bDelete = FALSE);

    BOOL BaiduFileinfo(LPCTSTR pszPath);

    // ���ϵͳ�������̷�(eg. C)
    CHAR GetSystemDrive();

    // ���ϵͳ���̷�(eg. C:\)
    BOOL GetSystemDrive(CString& strDrv);

    // �Զ�������ȵ�Ǩ��Ŀ��Ŀ¼
    BOOL GetAutoDestDirFromSize(CString& strDir);

    // ����ļ���С���ַ���
    void GetFileSizeString(ULONGLONG qwFileSize, CString& strFileSize);

    // ��ö���չ��
    void GetShortExtString(CString& strExt);

    // �ݹ�ö���ļ�
    // in ·����Ҫ\��β
    // out ���ս���Ķ���
    // in �˳��ź�
    BOOL EnumFiles(const CString& strPath, IEnumFileback* piEnumFileback);

    // �����չ��
    void GetFileExt(const CString& strFilePath, CString& strExt);

    // ��ָ����Ŀ¼�����Ƿ����ļ�
    BOOL HasFileInDir(const CString& strPath);

    // ��������·��
    BOOL GetDesktopPath(CString& strPath);

    // ����ҵ��ĵ���·��
    BOOL GetDocumentPath(CString& strPath);

    // ���Chrome������Ŀ¼
    BOOL GetChromeDownloadDirs(std::vector<CString>& vDirs);

    // ���Firefox������Ŀ¼
    BOOL GetFirefoxDownloadDirs(std::vector<CString>& vDirs);

    // ���360�����������Ŀ¼
    BOOL Get360DownloadDirs(std::vector<CString>& vDirs);

    // �������֮��������Ŀ¼
    BOOL GetTheworldDownloadDirs(std::vector<CString>& vDirs);

    // �����Ͱ������Ŀ¼
    BOOL GetMaxmonthDownloadDirs(std::vector<CString>& vDirs);

    // ���FlashGet������Ŀ¼
    BOOL GetFlashGetDownloadDirs(std::vector<CString>& vDirs);

    // ���Ѹ�׵�����Ŀ¼
    BOOL GetXunLeiDownloadDirs(std::vector<CString>& vDirs);

    // ��ñ������ǵ�����Ŀ¼
    BOOL GetBitCometDownloadDirs(std::vector<CString>& vDirs);

    // ���QQ���������Ŀ¼
    BOOL GetQQDownLoadDownloadDirs(std::vector<CString>& vDirs);

    // ������е�����Ŀ¼
    BOOL GetAllDownloadDirs(std::vector<CString>& vDirs);

    // ������й̶��Ϳ��ƶ����̵ľ�
    BOOL GetAllVols(std::vector<VolInfo>& vVols);

    // ѹ����·������·��
    void CompressedPath(CString& strFilePath);

    // ����ļ���ͼ��
    HICON GetIconFromFilePath(const CString& strFilePath);
}

//////////////////////////////////////////////////////////////////////////
