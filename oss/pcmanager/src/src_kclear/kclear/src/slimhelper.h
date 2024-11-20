#ifndef KCLEAR_SLIMHELPER_H_
#define KCLEAR_SLIMHELPER_H_

//////////////////////////////////////////////////////////////////////////

#include "slimcallback.h"

//////////////////////////////////////////////////////////////////////////

namespace slimhelper
{
    // �������ļ�
    extern const TCHAR g_kSlimFlag[];

    // ��ȡ��ȫ��Ȩ
    BOOL GainSecurityPrivilege1();
    BOOL GainSecurityPrivilege2();

    // �ļ��Ƿ�ѹ��
    BOOL IsCompressed(const CString& strFilePath, BOOL& bCompressed);

    // ѹ�������ļ�
    BOOL CompressFile(const CString& strFilePath,
                      ULONGLONG qwFileSize,
                      DWORD dwFileAttributes,
                      ISystemSlimCallBack* piCallback);

    // ѹ��һ��Ŀ¼
    BOOL CompressDirectory(const CString& strDirectory, 
                           ISystemSlimCallBack* piCallback,
                           int nLevel = 0);

    // ɾ�������ļ�
    BOOL DeleteFile(const CString& strFilePath,
                    ULONGLONG qwFileSize,
                    DWORD dwFileAttributes,
                    ISystemSlimCallBack* piCallback);

    // ɾ��һ��Ŀ¼
    BOOL DeleteDirectory(const CString& strDirectory,
                         ISystemSlimCallBack* piCallback,
                         BOOL bKeepRootDir = TRUE,
                         int nLevel = 0);

    // ɾ��һ��·��������վ
    BOOL RecyclePath(const CString& strFilePath,
                     BOOL bKeepRootDir = TRUE);

    // ɨ�赱���ļ�
    BOOL ScanFile(const CString& strFilePath,
                  ULONGLONG qwFileSize,
                  DWORD dwFileAttributes,
                  ISystemSlimCallBack* piCallback);

    // ɨ��һ��Ŀ¼
    BOOL ScanDirectory(const CString& strDirectory,
                       ISystemSlimCallBack* piCallback);

    // ��ֵת���ַ��͵Ĵ�С
    void GetFileSizeTextString(__int64 fNum, CString& strFileSize);

    // ���ļ���
    BOOL LocateFile(const CString& strFilePath);
};

//////////////////////////////////////////////////////////////////////////

#endif // KCLEAR_SLIMHELPER_H_
