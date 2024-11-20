#include "stdafx.h"
#include "bkautorunimp.h"
#include "autorunscanner.h"
#include "autorunitem.h"

CAutorunHandle::CAutorunHandle() :         ///< Construcor
m_pScanner(NULL)
{

}


CAutorunHandle::~CAutorunHandle()         ///< Destructor
{
	Close();
}


HRESULT WINAPI CAutorunHandle::Create( BOOL bEnableFeedDebug )  ///< ��������ʼ��ɨ����
{
	Close();
    HRESULT hr = E_FAIL;

    m_pScanner = new CAutorunScanner();
    if ( NULL == m_pScanner )
    {
        return E_OUTOFMEMORY;
    }

    hr = m_pScanner->Initialize();
    if (FAILED(hr))
    {
        delete m_pScanner;
        m_pScanner = NULL;
    }

	return S_OK;
}
void   WINAPI CAutorunHandle::Close()                        ///< �رղ��ͷ�ɨ����
{
    if ( NULL != m_pScanner )
    {
        m_pScanner->Uninitialize();
        delete m_pScanner;
        m_pScanner = NULL;
    }
}


BOOL  WINAPI  CAutorunHandle::FindFirstEntryItem( DWORD dwEntryID )    ///< Ѱ�ҵ�һ��������Ŀ
{
    if ( FALSE == CheckOperateData() )
    {
        return E_FAIL;
    }
	return m_pScanner->FindFirstEntryItem( dwEntryID );
}


BOOL  WINAPI  CAutorunHandle::FindNextEntryItem()                                ///< Ѱ����һ��������Ŀ
{
    if ( FALSE == CheckOperateData() )
    {
        return E_FAIL;
    }
	return m_pScanner->FindNextEntryItem();
}


HRESULT WINAPI CAutorunHandle::ExportTo(IAutorunHandle& target)       ///< ������ǰ������Ŀ��Ŀ,�Ա�����������
{
    return E_FAIL;
}


LPCWSTR WINAPI CAutorunHandle::GetInformation()                       ///< ��ȡ������ʾ����Ϣ
{
    if ( FALSE == CheckOperateData() )
    {
        return L"";
    }
	return m_pScanner->GetInformation();
}


DWORD  WINAPI CAutorunHandle::GetEntryID()                   ///< [����������] ��ȡ������ID
{
    if ( FALSE == CheckOperateData() )
    {
        return E_FAIL;
    }
	return m_pScanner->GetCurrentEntryID();
}


DWORD  WINAPI CAutorunHandle::GetEntryType()                 ///< [����������] ��ȡ����������ID
{
    if ( FALSE == CheckOperateData() )
    {
        return E_FAIL;
    }
	return CAutorunItem::GetEntryTypeByID( GetEntryID() );
}


HRESULT WINAPI CAutorunHandle::CleanEntry()                   ///< [����������] ɾ����ǰ�������Ӧ��value,��������
{
    if ( FALSE == CheckOperateData() )
    {
        return E_FAIL;
    }
	return m_pScanner->CleanCurrentEntry();
}


DWORD WINAPI  CAutorunHandle::GetFileCount()                 ///< [����������] ��ȡ��������ļ���Ŀ
{
    if ( FALSE == CheckOperateData() )
    {
        return E_FAIL;
    }
	 return m_pScanner->GetFileCount();
}


LPCWSTR  WINAPI CAutorunHandle::GetFilePathAt(DWORD dwIndex)   ///< [����������] ��ȡ��������ļ�·��
{
    if ( FALSE == CheckOperateData() )
    {
        return L"";
    }
	return m_pScanner->GetFilePathAt(dwIndex);
}


//////////////
///////////////