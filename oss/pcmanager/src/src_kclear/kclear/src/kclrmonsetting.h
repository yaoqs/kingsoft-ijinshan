#ifndef KCLRMONSETTING_H_
#define KCLRMONSETTING_H_

//////////////////////////////////////////////////////////////////////////

#include "kclear/kclrmon_public.h"
#include "common/kcomobject.h"

//////////////////////////////////////////////////////////////////////////

class KClearMonitorSetting : public IKClearMonitorSetting
{
public:
    KClearMonitorSetting();
    virtual ~KClearMonitorSetting();

    // �Ƿ���������������
    virtual HRESULT STDMETHODCALLTYPE GetEnableMointor(
        BOOL* pbEnable
        );

    // �����Ƿ���������������
    virtual HRESULT STDMETHODCALLTYPE SetEnableMointor(
        BOOL bEnable
        );

    // ʹ����������������Ƿ���ȴ
    virtual HRESULT STDMETHODCALLTYPE IsNotifyCoolDown(
        BOOL* pbCoolDown
        );

    // ��¼�������ʱ��
    virtual HRESULT STDMETHODCALLTYPE RecordLastNotify(
        );

    KAS_BEGIN_COM_MAP(KClearMonitorSetting)
        KAS_COM_INTERFACE_ENTRY(IKClearMonitorSetting)
    KAS_END_COM_MAP()

private:
    CStringA m_strCfgFile;
};

//////////////////////////////////////////////////////////////////////////

#endif // KCLRMONSETTING_H_
