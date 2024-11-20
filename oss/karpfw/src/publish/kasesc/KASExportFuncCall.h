///////////////////////////////////////////////////////////////
//
//	Filename: 	KASExportFuncCall.h
//	Creator:	lichenglin  <lichenglin@kingsoft.net>
//	Date:		2007-11-30  10:10
//	Comment:	Ϊ����DLL�еĵ������� �ṩ����ķ���
//
/*
ʹ�÷���:

����xxx.dll����һ��������Add, ���ڼ���ӷ�
����ָ�����Ͷ���: typedef int ( __stdcall* PFNAdd )( int a, int b );
��ʹ�÷�������:

{
	KASExportFuncCall<PFNAdd>  procAdd( TEXT( "xxx.dll" ), "Add" );
	if( procAdd.IsLoad() )
	{
		int nRet = procAdd( 3, 2 );
		assert( nRet == 5 );
	}
}

*/
///////////////////////////////////////////////////////////////

#ifndef _KASExportFuncCall_h_
#define _KASExportFuncCall_h_


///////////////////////////////////////////////////////////////
//
// declaration
//
///////////////////////////////////////////////////////////////

template<class PFN>
class KASExportFuncCall
{
public:
	KASExportFuncCall(void);
	KASExportFuncCall( LPCTSTR pszModuleName, LPCSTR pszProcName );
	~KASExportFuncCall(void);


	BOOL  Load( LPCTSTR pszModuleName, LPCSTR pszProcName );
	void  UnLoad();
	BOOL  IsLoad() const;


	operator PFN () const;

private:
	PFN     m_pfn;
	HMODULE m_hModule;
};






/////////////////////////////////////////////////////////////////
//
// implementation
//
/////////////////////////////////////////////////////////////////

template<class PFN>
KASExportFuncCall<PFN>::KASExportFuncCall(void)
{
	m_pfn     = NULL;
	m_hModule = NULL;
}



template<class PFN>
KASExportFuncCall<PFN>::KASExportFuncCall( LPCTSTR pszModuleName, LPCSTR pszProcName )
{
	m_pfn     = NULL;
	m_hModule = NULL;

	Load( pszModuleName, pszProcName );
}


template<class PFN>
KASExportFuncCall<PFN>::~KASExportFuncCall(void)
{
	UnLoad();
}


template<class PFN>
BOOL KASExportFuncCall<PFN>::Load( LPCTSTR pszModuleName, LPCSTR pszProcName )
{
	BOOL bRet = FALSE;

	if( IsLoad() )
		UnLoad();


	m_hModule = ::LoadLibrary( pszModuleName );
	if( m_hModule == NULL )
		goto Exit0;


	m_pfn = (PFN)::GetProcAddress( m_hModule, pszProcName );
	if( m_pfn == NULL )
		goto Exit0;


	bRet = TRUE;

Exit0:

	if( !bRet )
	{
		UnLoad();
	}

	return bRet;

}


template<class PFN>
void KASExportFuncCall<PFN>::UnLoad()
{
	if( m_hModule != NULL )
	{
		::FreeLibrary( m_hModule );
		m_hModule = NULL;
		m_pfn = NULL;
	}
}


template<class PFN>
BOOL  KASExportFuncCall<PFN>::IsLoad() const
{
	return m_pfn != NULL;
}



template<class PFN>
KASExportFuncCall<PFN>::operator PFN () const
{
	return m_pfn;
}


#endif // _KASExportFuncCall_h_
