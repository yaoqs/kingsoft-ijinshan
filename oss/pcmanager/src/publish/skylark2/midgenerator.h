/**
* @file    midgenerator.h
* @brief   ...
* @author  zhangrui
* @date    2009-03-03  15:25
*/

#ifndef MIDGENERATOR_H
#define MIDGENERATOR_H
#pragma comment ( lib, "IPHLPAPI.lib" )

#include <iphlpapi.h>
#include <atlstr.h>
#include <wchar.h>
#include <assert.h>
#include <objbase.h>
#include <atlbase.h>
#include <atlfile.h>
#include "winmod\winpath.h"
#ifdef USE_OPENSSL_H
#include "openssl\md5.h"
#else
#include "md5\md5.h"
#endif
#include "skylark2\skylarkbase.h"

#ifdef USE_OPENSSL_H
#define MD5INIT MD5_Init
#define MD5UPDATE MD5_Update
#define MD5FINAL MD5_Final
#else
#define MD5INIT MD5Init
#define MD5UPDATE MD5Update
#define MD5FINAL MD5Final
#endif

#define SKYLARK_VSN_LENGTH          4
#define SKYLARK_MAC_ID_LENGTH       MAX_ADAPTER_ADDRESS_LENGTH
#define SKYLARK_MID_LENGTH          40
#define SKYLARK_SOFT_ID_LENGTH      32

#define SKYLARK_MID_VER             2


#define SKYLARK_REG_VSN_KEY     L"Interface\\{D524796B-66CC-4952-BF14-17CD454CF138}"
#define SKYLARK_REG_SOFTID_KEY  L"Interface\\{BC40FFCF-BD8B-423d-882A-DEE82FE3315B}"
#define SKYLARK_REG_HARDID_KEY  L"Interface\\{9265A09B-A9C1-44ba-B65B-FEEC1FCA4C05}"



NS_SKYLARK_BEGIN

//////////////////////////////////////////////////////////////////////////
//
//  mid : md5(vsn, mac) + ver + rr + rv + rm
//  ver : 4bytes
//  rr  : 2bytes
//  rv  : 0, vsn = 0
//  rm  : 0, mac = 0
//
//////////////////////////////////////////////////////////////////////////

class CMidGenerator
{
public:

    typedef CComAutoCriticalSection                     CObjLock;
    typedef CComCritSecLock<CComAutoCriticalSection>    CObjGuard;

    CMidGenerator()
    {
        m_szVirtualDescription[ 0 ] = "VMware";
        m_szVirtualDescription[ 1 ] = "Microsoft";
        memset( m_zeroHardIdBuffer, 0, SKYLARK_MAC_ID_LENGTH );
    }

    static  CMidGenerator& Instance()
    {
        static CMidGenerator _ins;
        return _ins;
    }

    void    GetMid(CString& strMid)
    {
        CObjGuard Guard(m_objLock);

        if (m_bGenerated)
        {
            strMid = m_strMid;
            return;
        }



        strMid = L"0000000000000000000000000000000000010000";


        CString strTempMid;
        GenerateMid(strTempMid);
        m_strMid = strTempMid;
        m_bGenerated = TRUE;
        strMid   = m_strMid;

        return;
    }


    void    GenerateMid(CString& strMid)
    {
        // ��ȡsoftid
        BYTE bySoftID[SKYLARK_SOFT_ID_LENGTH];
        //DWORD dwVSN;
        HRESULT hr = E_FAIL;
        //hr = LoadVSNFromReg( dwVSN );
        hr = LoadSoftIdFromReg(bySoftID);
        if ( FAILED( hr ) )
        {
            // ���û�л�ȡ��softid,���½�һ��soft��д��
            //GenerateVSN(dwVSN);
            //SaveVSNToReg(dwVSN);
            //SaveSoftIdToFile(bySoftId);
            
            GenerateSoftId(bySoftID);
            SaveSoftIdToReg(bySoftID);
        }



        // ��ȡhardid
        BYTE byMacId[SKYLARK_MAC_ID_LENGTH];
        BYTE byHintMacId[SKYLARK_MAC_ID_LENGTH];
        memset(byMacId,     0, SKYLARK_MAC_ID_LENGTH);
        memset(byHintMacId, 0, SKYLARK_MAC_ID_LENGTH);

        hr = LoadMacIdFromReg(byHintMacId);

        if (FAILED(hr))
        {   // �޷���ȡ�����hardid
            GenerateMacId(byMacId, NULL);
        }
        else
        {   // ���ݽ����hardidѡ����ʵ�hardid
            GenerateMacId(byMacId, byHintMacId);
        }



        // ����µ�hardid�뽨���hardid��ͬ,�Ҳ�Ϊȫ0,���µ�hardid��Ϊ����hardid��������
        if (0 != memcmp(byMacId, byHintMacId, SKYLARK_MAC_ID_LENGTH) &&
            !IsZeroMacId(byMacId))
        {
            SaveMacIdToReg(byMacId);
        }




        // ����id��Ӳid�ϲ�Ϊmid
        MergeMidWithSoftID(strMid, bySoftID, byMacId);
    }


//protected:


    void    MergeMidWithSoftID(
        CString&    strMid,
        BYTE        bySoftId[ SKYLARK_SOFT_ID_LENGTH ],
        BYTE        byHardId[ SKYLARK_MAC_ID_LENGTH ]
    )
    {
        MD5_CTX ctx;
        BYTE	Buffer[20];

        MD5INIT( &ctx );
        MD5UPDATE( &ctx, bySoftId, SKYLARK_SOFT_ID_LENGTH);
        MD5UPDATE( &ctx, byHardId, SKYLARK_MAC_ID_LENGTH);
        MD5FINAL( Buffer, &ctx );

        HexFromBuffer( Buffer, 16, strMid );

        strMid.AppendFormat(L"%04x", DWORD(SKYLARK_MID_VER));   // mid�汾
        strMid.Append(L"00");                                   // �����ֶ�
        strMid.Append(L"1");
        //strMid.Append( dwVSN == 0 ? L"0" : L"1" );
        strMid.Append( IsZeroMacId( byHardId ) ? L"0" : L"1" );
    }


    void    MergeMid(
        CString&    strMid,
        DWORD       dwVSN,
        BYTE        byHardId[ SKYLARK_MAC_ID_LENGTH ]
        )
    {
        MD5_CTX ctx;
        BYTE	Buffer[20];

        MD5INIT( &ctx );
        MD5UPDATE( &ctx, ( unsigned char* )&dwVSN, SKYLARK_VSN_LENGTH);
        MD5UPDATE( &ctx, byHardId, SKYLARK_MAC_ID_LENGTH);
        MD5FINAL( Buffer, &ctx );

        HexFromBuffer( Buffer, 16, strMid );

        strMid.AppendFormat(L"%04x", DWORD(SKYLARK_MID_VER));   // mid�汾
        strMid.Append(L"00");                                   // �����ֶ�
        strMid.Append( dwVSN == 0 ? L"0" : L"1" );
        strMid.Append( IsZeroMacId( byHardId ) ? L"0" : L"1" );
    }



    HRESULT LoadVSNFromReg( DWORD& dwVSN )
    {
        CRegKey reg;
        LONG    lRet = reg.Open(HKEY_CLASSES_ROOT, SKYLARK_REG_VSN_KEY, KEY_READ);
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;

        lRet = reg.QueryDWORDValue(L"", dwVSN );
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;

        return S_OK;
    }

    HRESULT SaveVSNToReg( DWORD& dwVSN )
    {
        CRegKey reg;
        LONG    lRet = reg.Create(HKEY_CLASSES_ROOT, SKYLARK_REG_VSN_KEY);
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


        lRet = reg.SetDWORDValue( L"", dwVSN );
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;

        return S_OK;
    }

    void GenerateVSN( DWORD& dwVSN )
    {
        WCHAR   wszSystemPath[ MAX_PATH + 1 ] = { 0 };
        //WCHAR   wszVolumeName[ MAX_PATH + 1 ] = { 0 };
        DWORD   dwRet = 0;

        dwVSN = 0;

        dwRet = GetSystemDirectory( wszSystemPath, MAX_PATH );
        if ( ( 0 == dwRet ) || ( dwRet < 3 ) )
        {
            return;
        }

        if ( L':' != wszSystemPath[ 1 ] )
        {
            return;
        }

        wszSystemPath[ 3 ] = 0;

        if ( !GetVolumeInformation( 
            wszSystemPath, 
            NULL, 
            0, 
            &dwVSN, 
            NULL, 
            NULL, 
            NULL, 
            0 ) )
        {
            dwVSN = 0;
        }
    }




    HRESULT CMidGenerator::LoadSoftIdFromReg(BYTE bySoftId[SKYLARK_SOFT_ID_LENGTH])
    {
        assert(bySoftId);


        CRegKey reg;
        LONG    lRet = reg.Open(HKEY_CLASSES_ROOT, SKYLARK_REG_SOFTID_KEY, KEY_READ);
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


        ULONG uBytes = SKYLARK_SOFT_ID_LENGTH;
        lRet = reg.QueryBinaryValue(L"", bySoftId, &uBytes);
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


        return S_OK;
    }

    HRESULT CMidGenerator::SaveSoftIdToReg(const BYTE bySoftId[SKYLARK_SOFT_ID_LENGTH])
    {
        assert(bySoftId);


        CRegKey reg;
        LONG    lRet = reg.Create(HKEY_CLASSES_ROOT, SKYLARK_REG_SOFTID_KEY);
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


        lRet = reg.SetBinaryValue(L"", bySoftId, SKYLARK_SOFT_ID_LENGTH);
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


        return S_OK;
    }

    void CMidGenerator::GenerateSoftId(BYTE bySoftId[SKYLARK_SOFT_ID_LENGTH])
    {
        assert(bySoftId);
        assert(SKYLARK_SOFT_ID_LENGTH == (sizeof(GUID) * 2));

        GUID guidGen1;
        GUID guidGen2;
        ::CoCreateGuid(&guidGen1);
        ::CoCreateGuid(&guidGen2);

        memcpy(bySoftId,                &guidGen1, sizeof(GUID));
        memcpy(bySoftId + sizeof(GUID), &guidGen2, sizeof(GUID));
    }






    HRESULT LoadMacIdFromReg(BYTE byMacId[SKYLARK_MAC_ID_LENGTH])
    {
        assert(byMacId);


        CRegKey reg;
        LONG    lRet = reg.Open(HKEY_CLASSES_ROOT, SKYLARK_REG_HARDID_KEY, KEY_READ);
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


        ULONG uBufLen = SKYLARK_MAC_ID_LENGTH;
        lRet = reg.QueryBinaryValue(L"", byMacId, &uBufLen);
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


        return S_OK;
    }

    HRESULT SaveMacIdToReg(const BYTE byMacId[SKYLARK_MAC_ID_LENGTH])
    {
        assert(byMacId);


        CRegKey reg;
        LONG    lRet = reg.Create(HKEY_CLASSES_ROOT, SKYLARK_REG_HARDID_KEY);
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


        lRet = reg.SetBinaryValue(L"", byMacId, SKYLARK_MAC_ID_LENGTH);
        if (lRet != ERROR_SUCCESS)
            return GetLastError() ? AtlHresultFromLastError() : E_FAIL;


        return S_OK;
    }

    // ����ж��hardid��ѡ��,��ô������ѡ��� lpszHintHardId һ���� hardid
    void    GenerateMacId(
        BYTE byMacId[SKYLARK_MAC_ID_LENGTH],
        BYTE byHintMacId[SKYLARK_MAC_ID_LENGTH])
    {
        {
            assert(byMacId);
            memset(byMacId, 0, SKYLARK_MAC_ID_LENGTH);


            IP_ADAPTER_INFO  adapterArray[10];
            ULONG            ulOutBufLen = 10 * sizeof(IP_ADAPTER_INFO);
            ULONG uRet = ::GetAdaptersInfo(adapterArray, &ulOutBufLen);
            if (NO_ERROR != uRet)
            {
                return;
            }



            PIP_ADAPTER_INFO pFirstVirtualAdapter = NULL;   // ��һ����������
            PIP_ADAPTER_INFO pBestAdapter         = NULL;   // ����ʵ�����
            PIP_ADAPTER_INFO pAdapter             = adapterArray;
            for (NULL; pAdapter; pAdapter = pAdapter->Next)
            {
                // ������Ч��������ַ(ȫ0)
                size_t len = min(pAdapter->AddressLength, SKYLARK_MAC_ID_LENGTH);
                if (0 == memcmp(pAdapter->Address, m_zeroHardIdBuffer, len))
                    continue;


                // ����ʾ��Ӳ��idƥ��,����ȡ
                if (byHintMacId && pAdapter->AddressLength)
                {
                    if (0 == memcmp(byHintMacId, pAdapter->Address, pAdapter->AddressLength))
                    {
                        pBestAdapter = pAdapter;
                        break;
                    }
                }




                // ���Թ�����������,��VMWare
                if (MatchVirtualDescription(pAdapter->Description))
                {
                    // ��¼����������λ��,�������ȡ������ʵ����,��ֻ��ȡ���һ����������
                    if (!pFirstVirtualAdapter)
                        pFirstVirtualAdapter = pAdapter;
                    continue;
                }




                // ��������һ�������Ҫ������
                if (!pBestAdapter)
                    pBestAdapter = pAdapter;
            }


            // ���û�к��ʵ�����,��ȡ��һ����������
            if (!pBestAdapter)
                pBestAdapter = pFirstVirtualAdapter;


            // ��Ȼû�п��õ�����,�򷵻�Ĭ��ֵ
            if (!pBestAdapter)
                return;


            memcpy(byMacId, pBestAdapter->Address, pBestAdapter->AddressLength);
        }

    }


//protected:

    BOOL    MatchVirtualDescription(LPCSTR lpDescription)
    {
        if (!lpDescription)
            return FALSE;

        for (int i = 0; i < _countof(m_szVirtualDescription); ++i)
        {
            assert(m_szVirtualDescription[i]);
            if (StrStrIA(lpDescription, m_szVirtualDescription[i]))
                return TRUE;
        }

        return FALSE;
    }

    BOOL    IsZeroMacId(BYTE byHardId[SKYLARK_MAC_ID_LENGTH])
    {
        assert(byHardId);
        return 0 == memcmp(byHardId, m_zeroHardIdBuffer, SKYLARK_MAC_ID_LENGTH);
    }

    void HexFromBuffer(const BYTE* pbBuf, DWORD dwBufLen, CString& strHex)
    {
        assert(pbBuf);
        WCHAR szFormat[] = {L'%', L'0', L'2', L'x', L'\0'};

        strHex.Empty();
        for (DWORD i = 0; i < dwBufLen; ++i)
        {
            strHex.AppendFormat(szFormat, pbBuf[i]);
        }
    }


    CObjLock    m_objLock;                  ///< ������


    BOOL    m_bGenerated;
    CString m_strMid;
    BYTE    m_zeroHardIdBuffer[SKYLARK_MAC_ID_LENGTH];
    LPCSTR  m_szVirtualDescription[ 2 ];
};

NS_SKYLARK_END

#endif//MIDGENERATOR_H