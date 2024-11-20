/********************************************************************
	created:	2010/11/17
	created:	17:11:2010   11:21
	author:		Jiang Fengbing
	
	purpose:	��ɽ��ʿARP����ǽ�������ýӿ�
*********************************************************************/
#pragma once

//////////////////////////////////////////////////////////////////////////

#include <unknwn.h>

//////////////////////////////////////////////////////////////////////////

[
    uuid(79865ec3-8708-4835-b20c-758f5eeb25b4)
]
interface IArpFwSetting : IUnknown
{
    /*
     * @brief �ж�ARP����ǽ�Ƿ�װ
     */
    virtual STDMETHODIMP HasInstalled(BOOL* pbInstalled) = 0;

    /*
     * @brief ��װARP����ǽ
     */
    virtual STDMETHODIMP InstallArpFw() = 0;

    /*
     * @brief ж��ARP����ǽ
     */
    virtual STDMETHODIMP UnInstallArpFw() = 0;

    /*
     * @brief ����/�ر�, ARP����ǽ
     */
    virtual STDMETHODIMP EnableArpFw(BOOL bEnable) = 0;

    /*
     * @brief �ж�ARP����ǽ�Ƿ���
     */
    virtual STDMETHODIMP IsArpFwEnable(BOOL* pbEnable) = 0;

    /*
     * @brief ��ʾARP����ǽ������
     */
    virtual STDMETHODIMP ShowSetting(HWND hParent) = 0;

    /*
     * @brief ������һ����־
     */
    virtual STDMETHODIMP GetLastLog(int nLog, wchar_t* pLog) = 0;
};

//////////////////////////////////////////////////////////////////////////
