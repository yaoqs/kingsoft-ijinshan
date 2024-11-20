#pragma once
#include "comdata_scan_def.h"

class   IBkScan
{
public:
    virtual HRESULT Scan( int nScanMode, BOOL bBackGround, CAtlArray<CString>& lpParam ) = 0;     // Mode : ɨ�����ͣ�����ɨ�衢�ؼ�Ŀ¼ɨ�衢ȫ��ɨ�衢�Զ���ɨ�裬�Ҽ�ɨ�裩
                                                                                // lpParam�ɹ����ݶ�����������Զ���ɨ��Ŀ¼�ȣ�
    virtual HRESULT Scan2( int nScanMode, BOOL bBackGround, CAtlArray<BK_SCAN_ADDITIONAL_PATH>& lpParam ) = 0;     // Mode : ɨ�����ͣ�����ɨ�衢�ؼ�Ŀ¼ɨ�衢ȫ��ɨ�衢�Զ���ɨ�裬�Ҽ�ɨ�裩
                                                                                // lpParam�ɹ����ݶ���ɨ��Ŀ¼��ͬʱ����ָ����Ŀ¼�Ƿ�ݹ�ɨ��
    virtual HRESULT QuerySteps( int nScanMode, CAtlArray<int>& steps ) = 0;                    // ��ѯɨ�貽����
    virtual HRESULT Pause() = 0;                                                // ��ͣɨ��
    virtual HRESULT Resume() = 0;                                               // �ָ�ɨ��
    virtual HRESULT Stop() = 0;                                                 // ֹͣɨ��
    virtual HRESULT QueryScanInfo( BK_SCAN_INFO& scanInfo ) = 0;                // ��ѯɨ����Ϣ scanInfo : ��ȡ����ɨ����Ϣ
    virtual HRESULT QueryCleanInfo( BK_CLEAN_INFO& cleanInfo ) = 0;             // ��ѯ�����Ϣ cleanInfo: ��ȡ�������Ϣ
    virtual HRESULT QueryFileInfo( int nType, DWORD dwIndex, BK_FILE_INFO& fileInfo ) = 0;  // ��ѯָ�������ļ���Ϣ nType : �ļ����� dwIndex : �ļ����� fileInfo : �ļ���Ϣ
    virtual HRESULT Clean( CAtlArray<DWORD>& fileIndex ) = 0;                   // ���ѡ���ļ� fileIndex : ѡ���ļ�������
    virtual HRESULT QueryLastScanInfo( int nScanMode, BK_SCAN_INFO& scanInfo ) = 0;            // ��ѯ�ϴ�ɨ���� scanInfo : ��ȡ�����ϴ�ɨ����Ϣ
    virtual HRESULT SetScanSetting( BK_SCAN_SETTING& setting ) = 0;             // ����ɨ��ѡ�� settings : Ҫ���õ�ɨ��ѡ��
    virtual HRESULT GetScanSetting( BK_SCAN_SETTING& setting ) = 0;             // ��ȡɨ��ѡ�� settings : ��ȡ����ɨ��ѡ��
    virtual HRESULT ReportFile() = 0;                                           // �ϱ�����ɨ�������δ֪�ļ���
};

class   IBkScanSingleFile
{
public:
    virtual HRESULT ScanFile( CString& strFile, DWORD dwScanMask, DWORD dwScanPolicy, BK_FILE_RESULT& fr ) = 0;       // ɨ��ָ���ļ� strFile : ָ�����ļ�·�� dwScanPolicy : ɨ����� fr : ���ص�ɨ����
    virtual HRESULT CleanFile( CString& strFile, DWORD dwScanMask, DWORD dwScanPolicy, BK_FILE_RESULT& fr ) = 0;      // ���ָ���ļ�
    virtual HRESULT ForceClean( CString& strFile, BK_FORCE_CLEAN_DETAIL& detail, BK_FILE_RESULT& fr ) = 0; // ǿ�����ĳ���ļ�
    //virtual HRESULT SetScanSetting( BK_SCAN_SETTING& setting ) = 0;             // ����ɨ��ѡ�� settings : Ҫ���õ�ɨ��ѡ��
    //virtual HRESULT GetScanSetting( BK_SCAN_SETTING& setting ) = 0;             // ��ȡɨ��ѡ�� settings : ��ȡ����ɨ��ѡ��
};

class   IBkScanMultiFile
{
public:
    virtual HRESULT ScanHash( CAtlArray<CString>& hashArray, DWORD dwScanPolicy, CAtlArray<BK_FILE_RESULT>& frArray ) = 0;
    virtual HRESULT ScanFile( CAtlArray<CString>& fileArray, DWORD dwScanPolicy, CAtlArray<BK_FILE_RESULT>& frArray ) = 0;
};