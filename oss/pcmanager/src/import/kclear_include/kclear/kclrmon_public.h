#ifndef KCLRMON_PUBLIC_H_
#define KCLRMON_PUBLIC_H_

//////////////////////////////////////////////////////////////////////////

#include <unknwn.h>

//////////////////////////////////////////////////////////////////////////
// ���������ػص��ӿ�
[
    uuid(a63507aa-738c-42e1-939a-66384de2ccae)
]
interface IKClearMonitorCallback
{
    // ϵͳ�̳��ֿռ䲻��
    virtual HRESULT STDMETHODCALLTYPE OnSystemDriveLacking(
        ) = 0;
};

//////////////////////////////////////////////////////////////////////////
// ���������ؽӿ�
[
    uuid(3cbcb1d5-5811-433f-8769-4c818dc1e7ff)
]
interface IKClearMonitor : IUnknown
{
    // ��ʼ��
    virtual HRESULT STDMETHODCALLTYPE Initialize(
        IKClearMonitorCallback* piCallback
        ) = 0;

    // ����ʼ��
    virtual HRESULT STDMETHODCALLTYPE UnInitialize(
        ) = 0;

    // ϵͳ���Ƿ�ռ䲻��
    virtual HRESULT STDMETHODCALLTYPE IsSystemDriveLacking(
        /*[IN]*/ int nSysVol,
        /*[OUT]*/ char* szSysVol,
        /*[OUT]*/ BOOL* pbLacking
        ) = 0;

    // ������������
    virtual HRESULT STDMETHODCALLTYPE LaunchKClear(
        /*[IN_OPT]*/ const char* pSubTab
        ) = 0;

    // ��ʼ���
    virtual HRESULT STDMETHODCALLTYPE StartMonitor(
        ) = 0;

    // ֹͣ���
    virtual HRESULT STDMETHODCALLTYPE StopMonitor(
        ) = 0;

    // ���ϵͳ��ʣ��ռ�
    virtual HRESULT STDMETHODCALLTYPE GetSystemDriveFreeSize(
        ULONGLONG* pqwSizeInMB
        ) = 0;
};

//////////////////////////////////////////////////////////////////////////
// ��������������
[
    uuid(ba15b182-a5e2-4064-9f68-31af57cf0362)
]
interface IKClearMonitorSetting : IUnknown
{
    // �Ƿ���������������
    virtual HRESULT STDMETHODCALLTYPE GetEnableMointor(
        BOOL* pbEnable
        ) = 0;

    // �����Ƿ���������������
    virtual HRESULT STDMETHODCALLTYPE SetEnableMointor(
        BOOL bEnable
        ) = 0;

    // ʹ����������������Ƿ���ȴ
    virtual HRESULT STDMETHODCALLTYPE IsNotifyCoolDown(
        BOOL* pbCoolDown
        ) = 0;

    // ��¼�������ʱ��
    virtual HRESULT STDMETHODCALLTYPE RecordLastNotify(
        ) = 0;
};

//////////////////////////////////////////////////////////////////////////

#endif // KCLRMON_PUBLIC_H_
