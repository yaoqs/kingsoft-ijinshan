/**
* @file    autoruncontext.h
* @brief   ...
* @author  zhangrui
* @date    2009-04-23  22:05
*/

#ifndef AUTORUNCONTEXT_H
#define AUTORUNCONTEXT_H

#include <atlcoll.h>
#include "winmod\winpath.h"
#include "skylark2\skylarkbase.h"
#include "autorunentry.h"
#include "autorunitem.h"
#include "autorunitem_regkey.h"
#include "autorunitem_service.h"
#include "autorunitem_scheduled_task.h"
#include "autorunitem_startup_folder_file.h"
#include "autorunitem_startup_ini.h"



using namespace WinMod;

class CAutorunEntry;

/// ������ɨ����,������ǰɨ�赽����Ŀ,���ļ��б�
class CAutorunContext: public IAutorunContext
{
public:

    typedef CAtlList<CAutorunItem*>     CItemList;
    typedef Skylark::CCopiableArray<CString>     CPathList;


    CAutorunContext();
    ~CAutorunContext();

    HRESULT Initialize();
    HRESULT Uninitialize();
    void    Reset();

    void    EnableFeedDebug(BOOL bEnable);

    BOOL    FindFirstContextItem(const SLATR_ENTRY_DATA* pEntry);
    BOOL    FindNextContextItem();
    BOOL    IsEndOfContextItemFind() const;

    HRESULT ExportTo(CAutorunContext& target) const;

    CAutorunItem* GetCurrentItem() const;




    //////////////////////////////////////////////////////////////////////////
    // ɨ�踨������, FindXXX �����з��ֵ��ļ��� Append ��ʽ��ӵ� pathList ĩβ

    // ��ͼ���������������е�·��
    BOOL    FindAllPathInText(LPCWSTR lpszCommandLine, CPathList& pathList, CPathList* pAddionalDirList);

    // �����������е�һ��·��, bFirstFind��������
    BOOL    FindFirstPathInText(LPCWSTR lpszCommandLine, CPathList& pathList, CPathList* pAddionalDirList);

    // �����ļ��б��е�ÿ���ļ�
    //BOOL    FindPathInFileList(LPCWSTR lpszFileList, CPathList& pathList, LPCWSTR lpszDelimiters);

    // ����ļ�,�����ǰ,����ļ�·������Ҫ�Ĵ���
    void    AddPath(CPathList& pathList, LPCWSTR lpszPath);

    // ������һ���п�����·������ʼλ��
    LPCWSTR SeekNextPossiblePathPos(LPCWSTR lpszExecFile, LPCWSTR lpszCommandLine);
    LPCWSTR SeekAfterPattern(LPCWSTR lpszCommandLine, LPCWSTR lpszPattern);

    BOOL    TrySearchPathAndExtension(CWinPath& path, CPathList* pAddionalDirList);
    BOOL    TrySupplyExtension(CWinPath& path);



    //////////////////////////////////////////////////////////////////////////
    // ���º����� Entry ��������
    virtual void STDMETHODCALLTYPE Append_RegValue_As_Startup(
        const SLATR_ENTRY_DATA* pEntry,
        HKEY                    hKeyRoot,
        LPCWSTR                 lpszRegPath,
        LPCWSTR                 lpszValueName,
        LPCWSTR                 lpszValue);

    //virtual void STDMETHODCALLTYPE Append_RegValueName_As_Startup(
    //    const SLATR_ENTRY_DATA* pEntry,
    //    HKEY                    hKeyRoot,
    //    LPCWSTR                 lpszRegPath,
    //    LPCWSTR                 lpszValueName);

    virtual void STDMETHODCALLTYPE Append_Service(
        const SLATR_ENTRY_DATA* pEntry,
        LPCWSTR                 lpszServiceName,
        DWORD                   dwServiceType,
        DWORD                   dwServiceStart,
        LPCWSTR                 lpszImagePath,
        LPCWSTR                 lpszServiceDll,
        LPCWSTR                 lpszServiceDisplayName,
        LPCWSTR                 lpszServiceDescription);


    virtual void STDMETHODCALLTYPE Append_Scheduled_Task(
        const SLATR_ENTRY_DATA* pEntry,
        LPCWSTR                 lpszTaskName,
        LPCWSTR                 lpszApplicationName);


    virtual void STDMETHODCALLTYPE Append_Startup_Folder_File(
        const SLATR_ENTRY_DATA* pEntry,
        LPCWSTR                 lpszStartupFolder,
        LPCWSTR                 lpszFilePath);

    virtual void STDMETHODCALLTYPE Append_Startup_Ini_File(
        const SLATR_ENTRY_DATA* pEntry,
        LPCWSTR                 lpszIniFile,
        LPCWSTR                 lpszIniApp,
        LPCWSTR                 lpszIniKey,
        LPCWSTR                 lpszFilePath);


    void FeedInfo(LPCWSTR lpszInformation, LPCWSTR lpszFilePath);

    void FeedDebugValue(DWORD dwFeedCode, DWORD dwEntryID, HRESULT hErrCode, LPCWSTR lpszMessage);

private:


    CItemList   m_itemList;
    POSITION    m_itemPos;

    DWORD       m_dwCurrentEntryID;

    // ����Ĳ�����Resetʱ,���ᱻ��λ
    CPathList   m_pathExtList;
    CPathList   m_searchPathList;
    BOOL        m_bDBG__;
    BOOL        m_bEnableFeedDebug;

    // �Ƿ�����ö��,������ɨ������Ӧ��������ö��
    DWORD       m_dwEnumeratale;
};




#endif//AUTORUNCONTEXT_H