/**
* @file    slzipinfo.h
* @brief   ...
* @author  zhangrui
* @date    2009-06-04  11:14
*/

#ifndef SLZIPINFO_H
#define SLZIPINFO_H

#include <atlstr.h>
#include "miniutil\bkjson.h"
#include "skylarkbase.h"
#include "bkbak.h"

NS_SKYLARK_BEGIN

/*
{
   "upload" : {
      "file" : "ѹ�����е��ļ���",
      "path" : "�ļ�ԭʼ·��",
      "md5" : "�ļ���md5",
      "crc" : "�ļ���crc32",
      "comment" : "��ע",
   }
}
*/
/// �ϴ���Ϣ���ݶ���
class CUploadZipInfo
{
public:
    /// ...
    void    Clear();

    /// ...
    HRESULT SaveToJson(BkJson::Document& jDoc) const;

    /// ...
    HRESULT LoadFromJson(BkJson::Document& jDoc);

    /// ...
    HRESULT AddToZip(IBKZip* piZip, IBKProgress* piCallback = NULL) const;

    /// ...
    HRESULT ExtractFromZip(IBKUnzip* piUnzip, IBKProgress* piCallback = NULL);

public:
    CString m_strUploadFileName;    ///< �ϴ����ļ���
    CString m_strUploadFilePath;    ///< �ϴ����ļ�ԭʼ·��
    CString m_strComment;           ///< ��ע

    BYTE    m_pbyMd5[SKYLARK_MD5_BYTES];  ///< �ļ���md5
    DWORD   m_dwCRC32;                    ///< �ļ���crc32
};

NS_SKYLARK_END

#endif//SLZIPINFO_H