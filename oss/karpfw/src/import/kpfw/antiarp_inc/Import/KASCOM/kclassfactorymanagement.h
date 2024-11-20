///////////////////////////////////////////////////////////////
//
//	Filename: 	KClassFactoryManagement.h
//	Creator:	lichenglin  <lichenglin@kingsoft.net>
//	Date:		2007-8-26   10:55
//	Comment:	�೧������
//
//              �೧���������ڹ���Dll����������ע������೧.
//              ͨ������ע��ķ�ʽΪʹ�ú�:
//                  OBJECT_ENTRY_AUTO( clsid, comImpl )
//
///////////////////////////////////////////////////////////////

#ifndef _KClassFactoryManagement_h_
#define _KClassFactoryManagement_h_
#include <vector>
#include <assert.h>


//.-----------------------------------------------------------------------------
// struct CLASS_FACTORY_ITEM, 
// �����������Class ID �� �����Ӧ���೧
//.-----------------------------------------------------------------------------
struct CLASS_FACTORY_ITEM
{
	CLSID          clsid;
	IClassFactory* pIClassFactory;
};



//.-----------------------------------------------------------------------------
// class KClassFactoryManagement, 
// �೧������
//.-----------------------------------------------------------------------------

class KClassFactoryManagement
{
public:
	/**
	* @brief   �೧��������Dll�д���Ψһʵ��, ͨ��GetInstance()��ȡ��Ψһʵ��
	* @return  �೧��������ַ
	*/
	static KClassFactoryManagement* GetInstance();


	/**
	* @brief   ���೧������ע��һ���೧
	* @param   [in]  rclsid,          ���class ID
	* @param   [in]  pIClassFactory,  �೧�ӿ�
	*/
	void    Add( const CLSID& rclsid, IClassFactory* pIClassFactory );


	/**
	* @brief   ����೧������������ע����೧ 
	*/
	void    Clear();


	/**
	* @brief   ��ȡ�೧�������е��೧����
	*/
	ULONG   GetCount() const;


	/**
	* @brief   ���ö�Ӧ���೧, ��ȡ���
	* @param   [in]   rclsid, Ŀ�������class id, ���ΪCLSID_NULL, ����������೧��ѯ
	* @param   [in]   riid,   ��ѯ�Ľӿ�
	* @param   [out]  ppv,    ���ز�ѯ�Ľӿ�
	* @return  ��׼HRESULT
	* @remark  ��rclsidΪCLSID_NULLʱ, �ú�������������೧���в�ѯ, ����ýӿ��ڸ�Dll
	           ����Ψһ�������ʵ��, ���ѯ�ɹ�; ���û��ʵ�ֻ��ж���������ʵ��, ��
			   ��ѯʧ��. ���ʵ���»���assert��ʾ.
	*/
	HRESULT GetClassObject( REFCLSID rclsid, REFIID riid, LPVOID* ppv );


private:
	KClassFactoryManagement();
	~KClassFactoryManagement();
	IClassFactory* _Find( REFCLSID rclsid );
	std::vector<CLASS_FACTORY_ITEM>  m_vecClassFactory;
};




//.-----------------------------------------------------------------------------
// Implementation of class KClassFactoryManagement, 
//.-----------------------------------------------------------------------------


inline
KClassFactoryManagement* KClassFactoryManagement::GetInstance()
{
	static KClassFactoryManagement _Instance;
	return &_Instance;
}


inline
KClassFactoryManagement::KClassFactoryManagement()
{
}


inline
KClassFactoryManagement::~KClassFactoryManagement()
{
	if( m_vecClassFactory.size() != 0 )
	{
		Clear();
	}
}


inline
void KClassFactoryManagement::Add( const CLSID& rclsid, IClassFactory* pIClassFactory )
{
	assert( pIClassFactory != NULL );


	IClassFactory* pILast = _Find( rclsid );
	if( pILast != NULL )
	{
		assert( false );
		pILast->Release();
	}


	CLASS_FACTORY_ITEM cfItem;
	cfItem.clsid = rclsid;
	cfItem.pIClassFactory = pIClassFactory;

	m_vecClassFactory.push_back( cfItem );
}


inline
void KClassFactoryManagement::Clear()
{
	for( size_t i = 0; i < m_vecClassFactory.size(); i++ )
	{
		m_vecClassFactory[i].pIClassFactory->Release();
	}

	m_vecClassFactory.clear();
}


inline
ULONG KClassFactoryManagement::GetCount() const
{
	return (ULONG)m_vecClassFactory.size();
}


inline
HRESULT KClassFactoryManagement::GetClassObject( REFCLSID rclsid, REFIID riid, LPVOID* ppv )
{
	HRESULT hRet = E_NOINTERFACE;
	*ppv = NULL;

	// ���CLSIDΪ��, ����������೧
	if( rclsid == CLSID_NULL )
	{
		void*   pIRet = NULL;
		HRESULT hr    = E_FAIL;

		for( size_t i = 0; i < m_vecClassFactory.size(); i++ )
		{
			hr = m_vecClassFactory[i].pIClassFactory->CreateInstance( NULL, riid, (void**)&pIRet );
			if( SUCCEEDED( hr ) )
			{
				if( *ppv == NULL )
				{
					hRet = S_OK;
					*ppv = pIRet;
				}
				else
				{
					// ��DLL�д��ڲ�ֻһ���ýӿڵ�ʵ��
					assert( false ); 
					((IUnknown*)pIRet)->Release();
					((IUnknown*)*ppv)->Release();
					*ppv = NULL;
					hRet = E_FAIL;
					break;
				}
			}
		}
	}

	// ���CLSID��Ϊ��, ��ֱ���ҵ���Ӧ���೧���д���
	else
	{
		IClassFactory* pIClassFactory = _Find( rclsid );
		if( pIClassFactory != NULL )
		{
			hRet = pIClassFactory->CreateInstance( NULL, riid, ppv );
		}
	}

	return hRet;
}



inline
IClassFactory* KClassFactoryManagement::_Find( REFCLSID rclsid )
{
	IClassFactory* pIClassFactory = NULL;

	for( size_t i = 0; i < m_vecClassFactory.size(); i++ )
	{
		if( rclsid == m_vecClassFactory[i].clsid )
		{
			pIClassFactory = m_vecClassFactory[i].pIClassFactory;
			break;
		}
	}

	return pIClassFactory;
}



#endif // _KClassFactoryManagement_h_