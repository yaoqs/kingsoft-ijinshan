#ifndef __BKAUTORUN_H__
#define __BKAUTORUN_H__




interface  __declspec(uuid("7FC9D945-223D-4dbb-94BD-E822AFD7B907"))
IAutorunHandle
	: public IUnknown
{
	virtual HRESULT WINAPI Create( BOOL bEnableFeedDebug = FALSE )				= 0;   ///< ��������ʼ��ɨ����
	virtual void    WINAPI Close()												= 0;   ///< �رղ��ͷ�ɨ����


	virtual BOOL    WINAPI FindFirstEntryItem( DWORD dwEntryID = 1 )	= 0;   ///< Ѱ�ҵ�һ��������Ŀ
	virtual BOOL    WINAPI FindNextEntryItem()									= 0;   ///< Ѱ����һ��������Ŀ

	virtual HRESULT WINAPI ExportTo( IAutorunHandle& target)					= 0;   ///< ������ǰ������Ŀ��Ŀ,�Ա�����������

	virtual LPCWSTR WINAPI GetInformation()										= 0;   ///< ��ȡ������ʾ����Ϣ

	virtual DWORD   WINAPI GetEntryID()											= 0;   ///< [����������] ��ȡ������ID                        //
	virtual DWORD   WINAPI GetEntryType()										= 0;   ///< [����������] ��ȡ����������ID                    //
	virtual HRESULT WINAPI CleanEntry()											= 0;   ///< [����������] ɾ����ǰ�������Ӧ��value,��������  //δʵ��
	virtual DWORD   WINAPI GetFileCount()										= 0;   ///< [����������] ��ȡ��������ļ���Ŀ
	virtual LPCWSTR WINAPI GetFilePathAt( DWORD dwIndex )						= 0;   ///< [����������] ��ȡ��������ļ�·��
};


#define FN_BkCreateAutorunHandle            "BkCreateAutorunHandle"
EXTERN_C HRESULT WINAPI BkCreateAutorunHandle( IAutorunHandle **ppiAutorunHandle );
typedef HRESULT (WINAPI *PFN_BkCreateAutorunHandle)( IAutorunHandle **ppiAutorunHandle );



#endif //__BKAUTORUN_H__