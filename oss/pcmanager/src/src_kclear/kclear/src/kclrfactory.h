#ifndef KCLRFACTORY_H_
#define KCLRFACTORY_H_

//////////////////////////////////////////////////////////////////////////

#include "kclrmon.h"
#include "kclrmonsetting.h"

//////////////////////////////////////////////////////////////////////////

class KClearFactory
{
public:
    static KClearFactory& Instance();

    // ������ض���
    IKClearMonitor* CreateMonitor();

    // ����������ö���
    IKClearMonitorSetting* CreateMonitorSetting();

private:
    KClearFactory();
    ~KClearFactory();
};

#endif // KCLRFACTORY_H_
