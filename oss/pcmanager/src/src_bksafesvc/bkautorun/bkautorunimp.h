#ifndef __BKAUTORUNIMP_H__
#define __BKAUTORUNIMP_H__

#include "bkautorun.h"
#include "com_s\com\comobject.h"
class CAutorunScanner;

class CAutorunHandle
	: public IAutorunHandle
{
public:
	CAutorunHandle();          ///< Construcor
	~CAutorunHandle();         ///< Destructor

protected:
	virtual HRESULT WINAPI Create( BOOL bEnableFeedDebug );  ///< ��������ʼ��ɨ����
	virtual void    WINAPI Close();                        ///< �رղ��ͷ�ɨ����


	virtual BOOL    WINAPI FindFirstEntryItem( DWORD dwEntryID );    ///< Ѱ�ҵ�һ��������Ŀ
	virtual BOOL    WINAPI FindNextEntryItem();                                ///< Ѱ����һ��������Ŀ

	virtual HRESULT WINAPI ExportTo( IAutorunHandle& target);       ///< ������ǰ������Ŀ��Ŀ,�Ա�����������

	virtual LPCWSTR WINAPI GetInformation();                       ///< ��ȡ������ʾ����Ϣ

	virtual DWORD   WINAPI GetEntryID();                   ///< [����������] ��ȡ������ID
	virtual DWORD   WINAPI GetEntryType();                 ///< [����������] ��ȡ����������ID
	virtual HRESULT WINAPI CleanEntry();                   ///< [����������] ɾ����ǰ�������Ӧ��value,��������

	virtual DWORD   WINAPI GetFileCount();                 ///< [����������] ��ȡ��������ļ���Ŀ
	virtual LPCWSTR WINAPI GetFilePathAt(DWORD dwIndex);   ///< [����������] ��ȡ��������ļ�·��



	SCOM_BEGIN_COM_MAP(CAutorunHandle)
		SCOM_INTERFACE_ENTRY(IAutorunHandle)
	SCOM_END_COM_MAP()

private:
    BOOL CheckOperateData()
    {
        return (NULL!=m_pScanner) ? TRUE : FALSE;        
    }
    CAutorunScanner*  m_pScanner;
};



#endif //__BKAUTORUNIMP_H__