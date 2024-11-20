//////////////////////////////////////////////////////////////////////////
// Create Author: zhang zexin
// Create Date: 2010-12-16
// Description: 
// Modify Record:
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
// ������
typedef enum tagSlimMethod {
    SLIM_DELETE_FILE = 0,
    SLIM_COMPRESS_FILE = 1,
} SlimMethod;

//////////////////////////////////////////////////////////////////////////
// ϵͳ������ص�(ɨ��,ɾ��,ѹ��)
struct ISystemSlimCallBack
{
    // ɨ��ĳ��������ļ�
    virtual BOOL OnScanItem(
        const wchar_t* szFilePath,
        ULONGLONG qwFileSizeOnDisk,
        BOOL bCompressed
        ) = 0;

    // ����ĳ��������ļ�
    virtual BOOL OnBeginProcessItem(
        const wchar_t* szFilePath
        ) = 0;

    virtual BOOL OnEndProcessItem(
        const wchar_t* szFilePath,
        ULONGLONG qwSavedSize
        ) = 0;

    // ���кͿ����˳�
    virtual BOOL OnIdle(
        ) = 0;
};

//////////////////////////////////////////////////////////////////////////
