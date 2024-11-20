#pragma once
#include "comdata_utility_def.h"

class   IBkReScan
{
public:
    virtual HRESULT GetRescanResult( CAtlArray<BK_FILE_RESULT>& result ) = 0;
};

class   IBkUtility
{
public:
    virtual HRESULT ReportFile() = 0;
    virtual HRESULT SettingChange() = 0;
    virtual HRESULT QueryLastScanInfo( DWORD dwScanMode, BK_SCAN_INFO& ScanInfo ) = 0;

    // �Ա�������Ĳ���
    virtual HRESULT EnableAvEngine() = 0;
    virtual HRESULT DisableAvEngine() = 0;

    // �Ա��س�פ�Ĳ�����Ĳ���,
    // ���س�פ��������Ϊ�˱��ⲡ���ⱻ��������,ж�ص��µĵ���
    // ���û�б�Ҫ,ͨ������Ҫ�ӷ��������
    virtual HRESULT LoadDaemonAvSign() = 0;
    virtual HRESULT UnloadDaemonAvSign() = 0;

    // ��������������øú���,ͨ����Tray����
    virtual HRESULT ReloadAvSign() = 0;

    // ���ذ���������
    virtual HRESULT WhiteListUpdate() = 0;
};

class   IBkEcho
{
public:
    virtual HRESULT Echo( CAtlArray<CString>& FileList ) = 0;
    virtual HRESULT GetEchoResult( BK_ECHO_RESULT& result ) = 0;    // S_FALSE : ������; S_OK �����ֳɹ�; ��������ʧ��
    virtual HRESULT Stop() = 0;
};

class   IBkPluginReport
{
public:
    virtual HRESULT PluginReport( CAtlArray<BK_PLUGIN_INFO>& PluginList ) = 0;
};