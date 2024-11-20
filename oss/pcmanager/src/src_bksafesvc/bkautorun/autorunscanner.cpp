/**
* @file    autorunscanner.cpp
* @brief   ...
* @author  zhangrui
* @date    2009-04-24  15:44
*/

#include "stdafx.h"
#include "autorunscanner.h"

#include "autorunentry.h"
#include "autorunentrytool.h"

using namespace Skylark;

CAutorunScanner::CAutorunScanner()
{
    Reset();
}

CAutorunScanner::~CAutorunScanner()
{
    
}



HRESULT CAutorunScanner::Initialize()
{
    Reset();
    return m_atrContext.Initialize();
}

HRESULT CAutorunScanner::Uninitialize()
{
    Reset();
    return m_atrContext.Uninitialize();
}

void CAutorunScanner::Reset()
{
    m_atrContext.Reset();
    m_dwFindEntryID = SLATR_None;
    m_pCurrentEntry = NULL;
}

void CAutorunScanner::EnableFeedDebug(BOOL bEnable)
{
    m_atrContext.EnableFeedDebug(bEnable);
}


BOOL CAutorunScanner::FindFirstEntryItem(DWORD dwEntryID)
{
    Reset();

    // ö�ٵ�һ��������
    m_dwFindEntryID = dwEntryID;
    m_pCurrentEntry = CAtrEntryTool::FindByEntryID(CAtrEntryTool::GetEntryTable(), m_dwFindEntryID);
    if (!m_pCurrentEntry)
        return FALSE;

    // ö�ٵ�һ��������ĵ�һ��ʵ��
    BOOL bFind = m_atrContext.FindFirstContextItem(m_pCurrentEntry);
    if (bFind)
        return TRUE;

    // ���û���ҵ�,��ö����һ��������
    return FindNextEntryItem();
}

BOOL CAutorunScanner::FindNextEntryItem()
{
    if (!m_pCurrentEntry)
        return FALSE;


    // ö�ٵ�ǰ���������һ��ʵ��
    if (m_atrContext.FindNextContextItem())
        return TRUE;


    // �����ǰ�������Ѿ�ö�����,��ö����һ��ʵ��
    BOOL bFind = FALSE;
    while (!bFind)
    {
        // ö����һ��������
        ++m_pCurrentEntry;
        m_pCurrentEntry = CAtrEntryTool::FindByEntryID(m_pCurrentEntry, m_dwFindEntryID);
        if (!CAtrEntryTool::IsValidEntry(m_pCurrentEntry))
            return FALSE;


        // ö����һ�����������һ��ʵ��
        bFind = m_atrContext.FindFirstContextItem(m_pCurrentEntry);
    }


    return TRUE;
}



HRESULT CAutorunScanner::ExportTo(CAutorunScanner& target)
{
    target.m_dwFindEntryID = m_dwFindEntryID;
    target.m_pCurrentEntry = m_pCurrentEntry;

    return m_atrContext.ExportTo(target.m_atrContext);
}




DWORD CAutorunScanner::GetCurrentEntryID() const
{
    if (m_atrContext.IsEndOfContextItemFind())
        return SLATR_None;

    return m_atrContext.GetCurrentItem()->GetEntryType();
}

DWORD CAutorunScanner::GetCurrentEntryType() const
{
    if (m_atrContext.IsEndOfContextItemFind())
        return SLATR_None;

    return m_atrContext.GetCurrentItem()->GetEntryType();
}

HRESULT CAutorunScanner::CleanCurrentEntry() const
{
	if (m_atrContext.IsEndOfContextItemFind())
		return SLATR_None;

	return m_atrContext.GetCurrentItem()->Clean();
}

LPCWSTR CAutorunScanner::GetInformation() const
{
    if (m_atrContext.IsEndOfContextItemFind())
        return L"";

    return m_atrContext.GetCurrentItem()->GetInformation();
}

DWORD CAutorunScanner::GetFileCount() const
{
    if (m_atrContext.IsEndOfContextItemFind())
        return 0;

    return m_atrContext.GetCurrentItem()->GetFileCount();
}


LPCWSTR CAutorunScanner::GetFilePathAt(DWORD dwIndex) const
{
    if (m_atrContext.IsEndOfContextItemFind())
        return L"";

    return m_atrContext.GetCurrentItem()->GetFileAt(dwIndex);
}


