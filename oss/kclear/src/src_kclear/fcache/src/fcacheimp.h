// Copyright (c) 2010 Kingsoft Corporation. All rights reserved.
// Copyright (c) 2010 The KSafe Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
