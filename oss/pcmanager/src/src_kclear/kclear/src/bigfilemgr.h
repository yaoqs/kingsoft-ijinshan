#pragma once
#include "getinstallpath.h"
#include <Tlhelp32.h>
#include <Shlobj.h>
#include <vector>
#include <string>
using namespace std;
//////////////////////////////////////////////////////////////////////////

class CBigFileSet
{
public:
    // �Ƿ�����ƶ�����Ŀ¼
    virtual BOOL CouldMoveDir()
    {
        return m_fCouldChangeDir;
    }

    // �Ƿ����ɾ������Ŀ¼
    virtual BOOL CouldDelDir()
    {
        return m_fCouldDelDir;
    }

    // �Ƿ�����ƶ������ļ�
    virtual BOOL CouldMoveFile()
    {
        return m_fCouldMoveFile;
    }

    // �Ƿ����ɾ�������ļ�
    virtual BOOL CouldDelFile()
    {
        return m_fCouldDelFile;
    }

    // �ƶ��ļ��е�
    virtual BOOL MoveDirTo(const CString& strNewDir) = 0;

    // �Ƿ�Ϊ��Ҫ�������ļ�
    virtual BOOL IsSkipFile(const CString& strFileName) = 0;

    // ���Tip
    virtual CString GetTip()
    {
        return m_strTip;
    }

protected:
    BOOL m_fCouldChangeDir;
    BOOL m_fCouldDelDir;
    BOOL m_fCouldMoveFile;
    BOOL m_fCouldDelFile;
    CAtlArray<CString> m_bigDirs;
    CString m_strTip;
};

//////////////////////////////////////////////////////////////////////////

class CXxxx : public CBigFileSet
{

};

//////////////////////////////////////////////////////////////////////////

class CBigFileMgr
{
public:
    CBigFileMgr();
    ~CBigFileMgr();

    BOOL Init();
    void UnInit();

    BOOL NeedReboot();

protected:
    BOOL _CreateMovedDir(const CString& strDir);


    BOOL m_fNeedReboot;
};

//////////////////////////////////////////////////////////////////////////
DWORD GetProcessIdFromName(LPCTSTR szProcessName);
WCHAR GetSystemDrive();
// ������ػ�cache·��
DWORD _DoGetFileSizeByFileName(const WCHAR* pFileName);
DWORD _DoGetLineByBuf(WCHAR* const pszBuf, DWORD dwlen, std::vector<std::wstring>& vcStrline);

BOOL _GetFlashGetBigDirs(CAtlList<CString>& dirs);
BOOL _GetXunLeiBigDirs(CAtlList<CString>& dirs);
BOOL _GetBitCometBigDirs(CAtlList<CString>& dirs);
BOOL _GetYouKuBigDirs(CAtlList<CString>& dirs);
BOOL _GetKu6BigDirs(CAtlList<CString>& dirs);
BOOL _GetXunleiKankanBigDirs(CAtlList<CString>& dirs);
BOOL _GetQQMusicBigDirs(CAtlList<CString>& dirs);
BOOL _GetKuwoBigDirs(CAtlList<CString>& dirs);
BOOL _GetKugouBigDirs(CAtlList<CString>& dirs);
BOOL _GetChormeBigDir(CAtlList<CString>& dirs);
BOOL _GetFirefoxBigDir(CAtlList<CString>& dirs);
BOOL _Get360BigDir(CAtlList<CString>& dirs);
BOOL _GetMaxmonthBigDir(CAtlList<CString>& dirs);
BOOL _GetTheworldBigDir(CAtlList<CString>& dirs);
BOOL _GetFlashGetBigDirs(CAtlList<CString>& dirs);
BOOL _GetQQDownLoadBigDirs(CAtlList<CString>& dirs);
BOOL _GetMyDocumentDir(CAtlList<CString>& dirs);
BOOL _GetMyDeskTopDir(CAtlList<CString>& dirs);
BOOL _GetDrive(CAtlList<CString>& dirs);  //��ȡ�������
BOOL _GetDownLoadsDir(CString& dirs);
BOOL _GetMyDocument(CString& dirs);
BOOL _GetMyDeskTop(CString& dirs);


//////////////////////////////////////////////////////////////////////////
// �������ػ�cache·��
BOOL _SetBitCometBigDirs(const CString& strDir);
BOOL _SetXunLeiBigDirs(const CString& strDir);
BOOL _SetYouKuBigDirs(const CString& strDir);
BOOL _SetKu6BigDirs(const CString& strDir);
BOOL _SetXunleiKankanBigDirs(const CString& strDir);
BOOL _SetQQMusicBigDirs(const CString& strDir);
BOOL _SetKuwoBigDirs(const CString& strDir);
BOOL _SetKugouBigDirs(const CString& strDir);
BOOL _SetChormeBigDir(const CString& strDir);
BOOL _SetFirefoxBigDir(const CString& strDir);
BOOL _Set360BigDir(const CString& strDir);
BOOL _SetMaxmonthBigDir(const CString& strDir);
BOOL _SetTheworldBigDir(const CString& strDir);

//////////////////////////////////////////////////////////////////////////
