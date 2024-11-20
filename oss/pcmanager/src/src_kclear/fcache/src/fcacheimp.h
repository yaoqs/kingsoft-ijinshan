#pragma once

//////////////////////////////////////////////////////////////////////////

#include "kclear/ifcache.h"
#include "3rdparty/sqlite3/sqlite3.h"

//////////////////////////////////////////////////////////////////////////

class CFCacheImpl : public IFCache
{
public:
    CFCacheImpl(char cVol);
    virtual ~CFCacheImpl();

    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject);

    /**
     * @brief ��ʼ��
     */
    virtual BOOL __cdecl Initialize(
        );

    /**
     * @brief ����ʼ��
     */
    virtual BOOL __cdecl UnInitialize(
        );

    /**
     * @brief ��ʼ�������
     */
    virtual BOOL __cdecl BeginAdd(
        );

    /**
     * @brief �����������
     */
    virtual BOOL __cdecl EndAdd(
        );

    /**
     * @brief ȡ���������
     */
    virtual BOOL __cdecl CancelAdd(
        );

    /**
     * @brief ����ļ���Ϣ
     */
    virtual BOOL __cdecl AddFile(
        LPCWSTR lpFilePath,
        ULONGLONG qwFileSize
        );

    /**
     * @brief ɾ���ļ���Ϣ
     */
    virtual BOOL __cdecl DelFile(
        LPCWSTR lpFilePath
        );

    /**
     * @brief ɾ��ĳ��Ŀ¼����������ļ���Ϣ
     */
    virtual BOOL __cdecl DelDir(
        LPCWSTR lpDir
        );

    /**
     * @brief ����ܵĴ�С
     */
    virtual BOOL __cdecl GetTotalInfo(
        ULONGLONG& qwTotalSize,
        ULONGLONG& qwTotalCount
        );

    /**
     * @brief �����ѯ
     */
    virtual BOOL __cdecl Query(
        IFCacheQueryback* piQueryback,
        FCacheQueryType queryType,
        void* pParam1,
        void* pParam2
        );

    /**
     * @brief ���Cache
     */
    virtual BOOL __cdecl Clean(
        );

    /**
     * @brief ����ļ��Ĵ�С
     */
    virtual BOOL __cdecl GetFileSize(
        LPCWSTR lpFilePath,
        ULONGLONG& qwSize
        );

    /**
     * @brief ���Ŀ¼��С
     */
    virtual BOOL __cdecl GetDirInfo(
        LPCWSTR lpDir,
        ULONGLONG& qwSize,
        ULONGLONG& qwCount
        );

    /**
     * @brief �����չ��Top��
     */
    virtual BOOL __cdecl QueryTopExt(
        IFCacheQueryback* piQueryback,
        int nTop
        );

    /**
     * @brief ��¼ɨ���Ƿ�������ɨ��ʱ��
     */
    virtual BOOL __cdecl SetCacheInfo(
        const SYSTEMTIME& scanTime,
        BOOL bFullCache
        );

    /**
     * @brief ���ɨ���Ƿ�������ɨ��ʱ��
     */
    virtual BOOL __cdecl GetCacheInfo(
        SYSTEMTIME& scanTime,
        BOOL& bFullCache
        );

protected:
    BOOL PrepareDbFile(char cVol);

private:
    ULONG m_dwRefCount;
    sqlite3* m_pDbConnect;
    CStringA m_strDbPath;
};

//////////////////////////////////////////////////////////////////////////
