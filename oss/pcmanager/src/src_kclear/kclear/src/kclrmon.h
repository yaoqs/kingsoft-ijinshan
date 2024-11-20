#ifndef KCLRMON_H_
#define KCLRMON_H_

//////////////////////////////////////////////////////////////////////////

#include "kclear/kclrmon_public.h"
#include "common/kcomobject.h"

//////////////////////////////////////////////////////////////////////////

class KClearMonitor : public IKClearMonitor
{
public:
    KClearMonitor();
    virtual ~KClearMonitor();

    // ��ʼ��
    HRESULT STDMETHODCALLTYPE Initialize(
        IKClearMonitorCallback* piCallback
        );

    // ����ʼ��
    HRESULT STDMETHODCALLTYPE UnInitialize(
        );

    // ϵͳ���Ƿ�ռ䲻��
    HRESULT STDMETHODCALLTYPE IsSystemDriveLacking(
        /*[IN]*/ int nSysVol,
        /*[OUT]*/ char* szSysVol,
        /*[OUT]*/ BOOL* pbLacking
        );

    // ������������
    HRESULT STDMETHODCALLTYPE LaunchKClear(
        /*[IN_OPT]*/ const char* pSubTab
        );

    // ��ʼ���
    HRESULT STDMETHODCALLTYPE StartMonitor(
        );

    // ֹͣ���
    HRESULT STDMETHODCALLTYPE StopMonitor(
        );

    // ���ϵͳ��ʣ��ռ�
    HRESULT STDMETHODCALLTYPE GetSystemDriveFreeSize(
        ULONGLONG* pqwSizeInMB
        );

    KAS_BEGIN_COM_MAP(KClearMonitor)
        KAS_COM_INTERFACE_ENTRY(IKClearMonitor)
    KAS_END_COM_MAP()

protected:
    BOOL IsSystemDriveLacking(BOOL& bLacking);
    static UINT WINAPI TimerThreadProc(void* pParam);
    static ULONGLONG GigaByte(double size);

private:
    HANDLE m_hTimerThread;
    HANDLE m_hExitEvent;
    IKClearMonitorCallback* m_piCallback;
    BOOL m_bVistaOrLater;
    CStringA m_strSysDrive;
    ULONGLONG m_qwSysDriveFreeSizeInMB;
};

//////////////////////////////////////////////////////////////////////////

#endif // KCLRMON_H_
