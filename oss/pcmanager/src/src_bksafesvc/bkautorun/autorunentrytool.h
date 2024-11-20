/**
* @file    autorunentrytool.h
* @brief   ...
* @author  zhangrui
* @date    2009-04-26  17:08
*/

#ifndef AUTORUNENTRYTOOL_H
#define AUTORUNENTRYTOOL_H

#include "winmod\winpath.h"
#include "skylark2\skylarkbase.h"
#include "autorunentry.h"



using namespace WinMod;

// entry ��ע���


// entry ��ͷ
#define SLATR_ENTRY_BEGIN(entry_name__)         const SLATR_ENTRY_DATA entry_name__[] = {
// entry ���β
#define SLATR_ENTRY_END()                       {SLATR_None, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0}};

// entry ע���ֵ
#define SLATR_ENTRY_REG(id__, scan_entry__, disable_entry__, fix_entry__, root__, parent__, key__, value__, zero_files)  \
    {id__, scan_entry__, disable_entry__, fix_entry__, root__, parent__, key__, value__, zero_files, 0},

// entry ����Ŀ¼
#define SLATR_ENTRY_SHFOLDER(id__, scan_entry__, csidl__)  \
    {id__, scan_entry__, NULL, NULL, NULL, NULL, NULL, NULL, NULL, csidl__},



#define SLATR_ENTRY_BREAK() \
    {SLATR_None, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0},

#define SLATR_ENTRY(id__, scan_entry__, disable_entry__, fix_entry__)  \
    {id__, scan_entry__, disable_entry__, fix_entry__, NULL, NULL, NULL, NULL, NULL, 0},

//#define SLATR_REGKEY_CURRENT_CONTROL_SET_SERIVCES   L"SYSTEM\\CurrentControlSet\\Services"




class CAtrEntryTool
{
public:


    static BOOL    IsValidEntry(const SLATR_ENTRY_DATA* pEntry);

    static CString GetRegPath(const SLATR_ENTRY_DATA* pEntry);




    static const SLATR_ENTRY_DATA*  GetEntryTable();

    static DWORD                    GetEntryTableCount();

    static const SLATR_ENTRY_DATA*  FindByEntryID(
        const SLATR_ENTRY_DATA*     pFirstEntry,
        DWORD                       dwEntryID);



    static LPCWSTR  GetHKEYRootString(HKEY hRootKey);

    static BOOL     IsDiskInDrive(LPCWSTR lpszRootPath);


    //////////////////////////////////////////////////////////////////////////
    // ����ΪEntry�ı�ɨ�跽ʽ

    // ����ע�����µ�ֵ
    static HRESULT  EnumRegValues(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    // ����һ���Ӽ�,��ɨ���Ӽ���ָ����ֵ
    static HRESULT  EnumSubKeyAndScanRegValue(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    // ���������Ӽ�,��ɨ���Ӽ���ָ����ֵ
    static HRESULT  EnumSubSubKeyAndScanRegValue(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    // EnumSubKeyAndScanRegKeyForCLSID + EnumValueNameForCLSID
    static HRESULT  EnumCLSID(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    // ����һ���Ӽ�,��ɨ���Ӽ��ļ���(CLSID)
    static HRESULT  EnumSubKeyAndScanRegKeyForCLSID(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    // ����һ���Ӽ�,��ɨ���Ӽ��ļ�ֵ(CLSID)
    static HRESULT  EnumSubKeyAndScanRegValueForCLSID(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    // ����ע�����µ�ֵ
    static HRESULT  EnumValueNameForCLSID(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    // ����ע�����µ�ֵ
    static HRESULT  EnumValueForCLSID(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);



    // ɨ��ע�����µ�ָ��ֵ(REG_SZ)
    static HRESULT  ScanRegValue(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    // ɨ��ע�����µ�ָ��ֵ(REG_MULTI_SZ)
    static HRESULT  ScanRegValueAsMultiString(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    // ɨ��ע�����µ�ָ��ֵ(REG_BINARY)
    static HRESULT  ScanRegValueAsBinary(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    // ɨ�� HKLM\SYSTEM\CurrentControlSet\Control\NetworkProvider\Order
    static HRESULT  ScanNetworkProvider(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    //////////////////////////////////////////////////////////////////////////
    // �Է���Ĵ���
    static HRESULT  EnumServices(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);
    static HRESULT  DisableService(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);
    static HRESULT  RemoveService(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    //////////////////////////////////////////////////////////////////////////
    // �Լƻ�����Ĵ���
    static HRESULT  EnumScheduledTasks(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);
    static HRESULT  DoEnumScheduledTasks(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);
    static HRESULT  DoEnumScheduledTasksInVista(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);

    //////////////////////////////////////////////////////////////////////////
    // AutorunInf
    static HRESULT  ScanAutorunInf(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);


    //////////////////////////////////////////////////////////////////////////
    // ������Ŀ¼�Ĵ���
    static HRESULT  ScanShellFolder(IAutorunContext* piContext, const SLATR_ENTRY_DATA* pEntry);
};



#endif//AUTORUNENTRYTOOL_H