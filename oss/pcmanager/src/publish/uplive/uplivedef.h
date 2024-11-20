#pragma once
#include "bkxdx/bkxdx.h"
#include "bkxdx/bkxdx_cursor_bkjson.h"    // use bkjson implements
#include "bkxdx/bkxdx_exchange_c.h"       // support c type exchange
#include "bkxdx/bkxdx_exchange_atl.h"     // support ATL class exchange

typedef enum
{
    enumUpdPolicyTypeFast = 0,				//����quick.ini
    enumUpdPolicyTypeSlow = 1,				//����slow.ini
};

// �������ͣ���������bin����
typedef enum
{
    enumUpdTypeLibUpdate = 0,				//������
    enumUpdTypeBinUpdate = 1,				//ģ������
};

// �ļ�����
typedef enum
{
    enumTypeUndefined   = -1,
    enumTypeUpdatePack  = 0,				//�������ļ�
    enumTypeLibFile     = 1,				//ȫ�����ļ��ļ�
    enumTypeLibFileDiff = 2,				//�������ļ�
    enumTypeBinFile     = 3,				//������(ģ��)�ļ�
    enumTypeHotfix      = 4,				//���������޸��ļ�
};

// ����״̬
typedef enum 
{
    enumUpdStatusNone              = 0,    // ռλ��
    enumUpdStatusCheckVersion      = 1,    // ���汾
    enumUpdStatusCheckFileList     = 2,    // �����ļ��б�
    enumUpdStatusDownloadFiles     = 3,    // �����ļ�
    enumUpdStatusUpdateFiles       = 4,    // �����ļ�
    enumUpdStatusUpdateFilesFinished = 5,  // ����ļ�����
    enumUpdStatusCombine           = 6,    // �ϲ��ļ�
    enumUpdStatusAction            = 7,    // ִ����������
    enumUpdStatusNotify            = 8,    // ִ��������֪ͨ
    enumUpdStatusFinished          = 9,    // ��ɸ���
	enumUpdNothing				   = 10,   // ������״̬��û�з�����Ҫ���µ����� [12/24/2010 zhangbaoliang]
};

typedef enum
{
    enumUpdOpBackup                 = 0,
    enumUpdOpReplace                = 1,
    enumUpdOpRebootReplace          = 2,
};

typedef struct _UPD_HINT 
{
    CString strTitle;
    CString strHint;
    CString strDetailUrl;
}UPD_HINT, *PUPD_HINT;

XDX_CLASS_BEGIN(UPD_HINT)
    XDX_MEMBER(strTitle)
    XDX_MEMBER(strHint)
    XDX_MEMBER(strDetailUrl)
XDX_CLASS_END
