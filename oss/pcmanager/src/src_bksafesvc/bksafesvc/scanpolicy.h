#pragma once
#include "scancontext.h"


class CFastScanPolicy 
{
public:
    CFastScanPolicy(){}
    ~CFastScanPolicy(){};
    //����ɨ�� ɨ���ڴ桢������ؼ�Ŀ¼������Ŀ¼
    HRESULT StartScan( CScanContext* pScanContext );
    HRESULT StartScan( CScanContext* pScanContext, CAtlMap<CString, BOOL>& CustomParamMap );
};


class CIeFixScanPolicy
{
public:
    CIeFixScanPolicy(){};
    ~CIeFixScanPolicy(){};
    HRESULT StartScan( CScanContext* pScanContext );
};

//
class COnlyMemoryScanPolicy
{
public:
    COnlyMemoryScanPolicy(){}
    ~COnlyMemoryScanPolicy(){}
    //���ɨ�� ɨ���ڴ桢������
    HRESULT StartScan( CScanContext* pScanContext );
};


//���ɨ��
class CCheckScanPolicy
{
public:
    CCheckScanPolicy(){}
    ~CCheckScanPolicy(){}
    //���ɨ�� ɨ���ڴ桢������
    HRESULT StartScan( CScanContext* pScanContext );
    HRESULT StartScanForCacheMemory( CScanContext* pScanContext );
    HRESULT StartScanForCacheAutoRun( CScanContext* pScanContext );
};



//�Զ���ɨ��
class CCustomScanPolicy
{
public:
    CCustomScanPolicy(){}
    ~CCustomScanPolicy(){};
    //�Զ���ɨ�� ɨ���ڴ桢������ؼ�Ŀ¼������Ŀ¼���Զ���Ŀ¼
    HRESULT StartScan( CScanContext* pScanContext, CAtlMap<CString, BOOL>& CustomDirMap );

};



//ȫ��ɨ�����
class CFullDiskScanPolicy
{
public:
    CFullDiskScanPolicy(){}
    ~CFullDiskScanPolicy(){};
    //ȫ��ɨ�� ɨ���ڴ桢������ؼ�Ŀ¼������Ŀ¼�������̷�
    HRESULT StartScan( CScanContext* pScanContext );

};


class CMoveDiskScanPolicy
{
public:
    CMoveDiskScanPolicy(){}
    ~CMoveDiskScanPolicy(){};
    //ɨ���ڴ� ɨ�������� ɨ���ƶ�����
    HRESULT StartScan( CScanContext* pScanContext );

};



class CRightScanPolicy
{
public:
    CRightScanPolicy(){}
    ~CRightScanPolicy(){};
    //�Ҽ�ɨ�� ɨ���ڴ���û�ָ��Ŀ¼
    HRESULT StartScan( CScanContext* pScanContext, CAtlMap<CString, BOOL>& RightParamMap );

};


class COnlyCustomScanPolicy
{
public:
    HRESULT StartScan( CScanContext* pScanContext, CAtlMap<CString, BOOL>& CustomParamMap );
};


