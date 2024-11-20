#include "stdafx.h"
#include "common/kcomobject.h"
#include "kclrfactory.h"

//////////////////////////////////////////////////////////////////////////

KClearFactory::KClearFactory()
{
}

KClearFactory::~KClearFactory()
{
}

//////////////////////////////////////////////////////////////////////////

KClearFactory& KClearFactory::Instance()
{
    static KClearFactory singleton;
    return singleton;
}

//////////////////////////////////////////////////////////////////////////

// ������ض���
IKClearMonitor* KClearFactory::CreateMonitor()
{
    IKClearMonitor* pObject = new KComObject<KClearMonitor>();
    pObject->AddRef();
    return pObject;
}

// ����������ö���
IKClearMonitorSetting* KClearFactory::CreateMonitorSetting()
{
    IKClearMonitorSetting* pObject = new KComObject<KClearMonitorSetting>();
    pObject->AddRef();
    return pObject;
}

//////////////////////////////////////////////////////////////////////////
