/**
* @file    autorunscanner.h
* @brief   ...
* @author  zhangrui
* @date    2009-04-24  15:44
*/

#ifndef AUTORUNSCANNER_H
#define AUTORUNSCANNER_H

#include "skylark2\skylarkbase.h"
#include "autoruncontext.h"



class CAutorunScanner//: public CAutorunContext
{
public:

    CAutorunScanner();
    ~CAutorunScanner();


    HRESULT Initialize();
    HRESULT Uninitialize();
    void    Reset();

    void    EnableFeedDebug(BOOL bEnable);

    BOOL    FindFirstEntryItem(DWORD dwEntryID);
    BOOL    FindNextEntryItem();
    BOOL    IsEndOfEntryItemFind() const;

    HRESULT ExportTo(CAutorunScanner& target);



    DWORD   GetCurrentEntryID() const;
    DWORD   GetCurrentEntryType() const;

	HRESULT CleanCurrentEntry() const;


    LPCWSTR GetInformation() const;
    DWORD   GetFileCount() const;
    LPCWSTR GetFilePathAt(DWORD dwIndex) const;



protected:


    DWORD                   m_dwFindEntryID;    ///< Ҫ���ҵ�������id
    CAutorunContext         m_atrContext;       ///< ������Ŀö�ٵľ��


    const SLATR_ENTRY_DATA* m_pCurrentEntry;    ///< ��ǰɨ�赽��������
};



#endif//AUTORUNSCANNER_H