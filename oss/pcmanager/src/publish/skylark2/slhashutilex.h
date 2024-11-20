/**
* @file    slhashutilex.h
* @brief   ...
* @author  zhangrui
* @date    2008-12-22  01:31
*/

#ifndef SLHASHUTILEX_H
#define SLHASHUTILEX_H

#include <atlfile.h>
#include "zlibcrc32\crc32.h"
#include "slhashutil.h"

NS_SKYLARK_BEGIN

/// hex������ģ��
template <class T_AtlString>
class CHexUtilExT
{
public:

    typedef typename T_AtlString        StringType; ///< typedef for string type
    typedef typename T_AtlString::XCHAR CharType;   ///< typedef for char type

    /**
    * @brief    �Ӷ���������ת����ʮ���������ֵ��ַ���
    * @param    pbBuf       md5��buffer
    * @param    uCRC32      crc32
    * @param    strHex      ����ת����õ���ʮ���������ֵ��ַ���
    */
    static void HexFromMD5Ex(const BYTE* pbBuf, unsigned int uCRC32, StringType& strHex)
    {
        assert(pbBuf);
        BYTE pbMD5Ex[20];
        memcpy(pbMD5Ex, pbBuf, 16);

        pbMD5Ex[16] = BYTE((uCRC32 >> 24) & 0xFF);
        pbMD5Ex[17] = BYTE((uCRC32 >> 16) & 0xFF);
        pbMD5Ex[18] = BYTE((uCRC32 >>  8) & 0xFF);
        pbMD5Ex[19] = BYTE((uCRC32      ) & 0xFF);

        return CHexUtilT<T_AtlString>::HexFromBuffer(pbMD5Ex, 20, strHex);
    }

    /**
    * @brief    ��ʮ���������ֵ��ַ���ת���ɶ���������
    * @param    pbBuf       ����md5��buffer
    * @param    puCRC32     ����crc32
    * @param    lpHex       Ҫת����ʮ�����������ַ���
    */
    static HRESULT HexToBuffer(BYTE* pbBuf, unsigned int* puCRC32, const CharType* lpHex)
    {
        assert(pbBuf);
        assert(puCRC32);
        assert(lpHex);

        BYTE pbMD5Ex[20];
        HRESULT hr = CHexUtilT<T_AtlString>::HexToBuffer(pbMD5Ex, SKYLARK_MD5EX_BYTES, lpHex);
        if (FAILED(hr))
            return hr;

        memcpy(pbBuf, pbMD5Ex, 16);

        unsigned int uResult = 0;
        uResult  |= pbMD5Ex[16] & 0xFF;
        uResult <<= 8;
        uResult  |= pbMD5Ex[17] & 0xFF;
        uResult <<= 8;
        uResult  |= pbMD5Ex[18] & 0xFF;
        uResult <<= 8;
        uResult  |= pbMD5Ex[19] & 0xFF;

        *puCRC32 = uResult;
        return S_OK;
    }
};



/// md5ex hash ������
class CSLMD5Ex
{
public:

    /// constructor
    CSLMD5Ex(): m_uCRC32(0)
    {
    }


    /// md5ex init
    void Init()
    {
        m_uCRC32 = 0;
        m_md5ctx.Init();
    }


    /**
    * @brief md5ex update
    * @param    pbData  ����������
    * @param    dwLen   ���ݳ���(�ֽ���)
    */
    void Update(const void* pbData, DWORD dwLen)
    {
        m_uCRC32 = CRC32(m_uCRC32, pbData, dwLen);
        m_md5ctx.Update((const BYTE*)pbData, dwLen);
    }


    /**
    * @brief md5ex final
    * @param    md5         ����md5
    * @param    pdwCRC32    ����crc32
    */
    void Final(BYTE md5[20], DWORD* pdwCRC32)
    {
        m_md5ctx.Final(md5);
        *pdwCRC32 = m_uCRC32;
    }


    /**
    * @brief md5ex final
    * @param    pbResult    hashֵ
    */
    void Final(BYTE pbResult[20])
    {
        m_md5ctx.Final(pbResult);

        pbResult[16] = BYTE((m_uCRC32 >> 24) & 0xFF);
        pbResult[17] = BYTE((m_uCRC32 >> 16) & 0xFF);
        pbResult[18] = BYTE((m_uCRC32 >>  8) & 0xFF);
        pbResult[19] = BYTE((m_uCRC32      ) & 0xFF);
    }





    /**
    * @brief ����0�������ݵ�hashֵ
    * @param    pbResult    hashֵ
    */
    static void NullFinal(BYTE pbResult[20])
    {
        memset(pbResult, 0, 20);
        CSLMD5 ctx;
        ctx.Init();
        ctx.Final(pbResult);
    }


protected:
    CSLMD5          m_md5ctx;   ///< md5 context
    unsigned int    m_uCRC32;   ///< crc32 context
};

NS_SKYLARK_END

#endif//SLHASHUTILEX_H