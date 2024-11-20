#pragma once

#include "bkupdwebfile.h"
#include "bksafe/bksafeconfig.h"
#include "winmod/proxyinfo.h"


class IBkDownloadCallback
{
public:
    // ����FALSE����ֹ����
    virtual BOOL    DownloadProcess( 
        DWORD dwTotalSize, 
        DWORD dwReadSize 
        ) = 0;
};


class CBkUpdDownloader
{
public:
    CBkUpdDownloader(BOOL bConnectionKeepAlive)
        : m_bConnectionKeepAlive(bConnectionKeepAlive)
    {
    }

	void SetUpLiveProxyInfo(BKSAFE_PROXY_INFO::UPLIVE_PROXY_INFO proxyInfo);

	//////////////////////////////////////////////////////////////////////////
	//
	//ʹ��dwProxyType�ö���������
	void UseBKSafeProxyInfo(DWORD dwProxyType = PROXY_TYPE::PROXY_TYPE_ALL);

    HRESULT Download(LPCTSTR lpszUrl, IBkUpdWebFile *piWebFile, IBkDownloadCallback *piCallback = NULL );

protected:
    BOOL m_bConnectionKeepAlive;

private:
	BKSAFE_PROXY_INFO::UPLIVE_PROXY_INFO	m_upliveProxyInfo;
	BOOL				_ProxyInfoValid();

};