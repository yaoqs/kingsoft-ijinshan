/********************************************************************
* CreatedOn: 2005-8-16   15:40
* FileName: SCOMBase.h
* CreatedBy: qiuruifeng <qiuruifeng@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/

#ifndef SCOMBASE_H
#define SCOMBASE_H

#include "SCOMDef.h"
#include "Singleton.h"
#include "SCOMFactory.h"
#include "SCOMAPI.h"


//�������,����ָ�����ü���������,Ĭ����ʹ���̰߳�ȫ�ļ�����,�������̰߳�ȫ���������ʹ��unsign long��
//���ü�������ֵ��0,���Ҫ�Զ������ü�������ʹ�ô������Ĺ��캯��
template
<
	class T,
	class RefCounterType = KSRefCnt
>
class KSComRoot : public IUnknown
{
public:
	typedef typename T _ComType;

	KSComRoot():m_RefCnt(0L)
	{
	}

	KSComRoot(unsigned long lRefCnt):m_RefCnt(lRefCnt)
	{
	}
	~KSComRoot()
	{        
	}
protected:
	RefCounterType m_RefCnt;
};


//������new��delete���������,�������ʱ ��ʹ��SCOM���ڴ����
template 
<
    class T,
	class RefCounterType = KSRefCnt
>
class KSComRoot2 : public KSComRoot<T, RefCounterType>
{
public:
 //   typedef typename T _ComType;
	KSComRoot2(unsigned long lRefCnt):KSComRoot<T, RefCounterType>(lRefCnt)
	{
	}
	static void* operator new(unsigned int uSize)
	{
		return KSCoTaskMemAlloc(uSize);
	}

	static void operator delete(void* p, unsigned int uSize)
	{
		KSCoTaskMemFree(p, uSize);
	}
	virtual ~KSComRoot2()
	{        
	}
};

#define  IMPLEMENT_INDEPENDENT_CREATOR()  \
static KSRESULT __stdcall CreateInstance(const KSIID &riid, void **ppv) \
{                                         \
	KS_ASSERT(ppv != NULL);               \
	_ComType *p = NULL;                   \
	p = new _ComType();                   \
	KSRESULT hRes;                        \
	hRes = p->QueryInterface(riid, ppv);  \
	if (hRes != S_OK)                     \
	{                                     \
		delete p;                         \
	}                                     \
	return hRes;\
}

#ifdef _DEBUG

#define IMPLEMENT_INDEPENDENT_ADDREF() \
unsigned long __stdcall AddRef()    \
{                                   \
	KS_ASSERT(long(m_RefCnt) >= 0); \
	long lRefCnt = ++m_RefCnt;      \
	if (1 == lRefCnt)				\
	{								\
		GlobalFactory::Instance().Lock();\
		GlobalFactory::Instance().AddComponentCount(KS_CLSIDOF(_ComType));\
	}								\
	return lRefCnt;					\
}

#define IMPLEMENT_INDEPENDENT_RELEASE()  \
unsigned long __stdcall Release()        \
{                                        \
	KS_ASSERT(long(m_RefCnt) > 0);       \
	long lRefCnt = --m_RefCnt;           \
	if (lRefCnt == 0)                    \
	{                                    \
		GlobalFactory::Instance().ReleaseComponentCount(KS_CLSIDOF(_ComType));\
		delete this;                     \
		GlobalFactory::Instance().UnLock();\
	}				\
	return lRefCnt;	\
}

#else

#define IMPLEMENT_INDEPENDENT_ADDREF() \
unsigned long __stdcall AddRef()    \
{                                   \
	KS_ASSERT(long(m_RefCnt) >= 0); \
	long lRefCnt = ++m_RefCnt;      \
	if (1 == lRefCnt)				\
	{								\
		GlobalFactory::Instance().Lock();\
	}								\
	return lRefCnt;					\
}

#define IMPLEMENT_INDEPENDENT_RELEASE()  \
unsigned long __stdcall Release()        \
{                                        \
	KS_ASSERT(long(m_RefCnt) > 0);       \
	long lRefCnt = --m_RefCnt;           \
	if (lRefCnt == 0)                    \
	{                                    \
		delete this;                     \
		GlobalFactory::Instance().UnLock(); \
	}				\
	return lRefCnt;	\
}

#endif

#define DECLARE_INDEPENDENT_OBJECT() public: \
    IMPLEMENT_INDEPENDENT_ADDREF()           \
    IMPLEMENT_INDEPENDENT_RELEASE()          \
    IMPLEMENT_INDEPENDENT_CREATOR()



#define IMPLEMENT_SINGLETON_CREATOR()           \
static KSRESULT __stdcall CreateInstance(const KSIID &riid, void **ppv)\
{                                               \
	KS_ASSERT(ppv != NULL);                     \
	_ComType *p = NULL;                         \
	p = &SingletonHolder<_ComType>::Instance(); \
	KSRESULT hRes;                              \
	hRes = p->QueryInterface(riid, ppv);        \
	return hRes;\
}

#ifdef _DEBUG

#define IMPLEMENT_SINGLETON_ADDREF() \
unsigned long __stdcall AddRef()    \
{                                   \
	KS_ASSERT(long(m_RefCnt) >= 0); \
	long lRefCnt = ++m_RefCnt;      \
	if (1 == lRefCnt)				\
	{								\
		GlobalFactory::Instance().Lock();\
		GlobalFactory::Instance().AddComponentCount(KS_CLSIDOF(_ComType));\
	}								\
	return lRefCnt;              \
}

#define IMPLEMENT_SINGLETON_RELEASE() \
unsigned long __stdcall Release()     \
{                                     \
	KS_ASSERT(long(m_RefCnt) > 0);    \
	long lRefCnt = --m_RefCnt;        \
	if (0 == lRefCnt)                 \
	{                                 \
		GlobalFactory::Instance().ReleaseComponentCount(KS_CLSIDOF(_ComType));\
		GlobalFactory::Instance().UnLock(); \
	}             \
	return lRefCnt;\
}

#else

#define IMPLEMENT_SINGLETON_ADDREF() \
	unsigned long __stdcall AddRef()    \
{                                   \
	KS_ASSERT(long(m_RefCnt) >= 0); \
	long lRefCnt = ++m_RefCnt;      \
	if (1 == lRefCnt)				\
	{								\
		GlobalFactory::Instance().Lock();\
	}								\
	return lRefCnt;              \
}

#define IMPLEMENT_SINGLETON_RELEASE() \
unsigned long __stdcall Release()     \
{                                     \
	KS_ASSERT(long(m_RefCnt) > 0);    \
	long lRefCnt = --m_RefCnt;        \
	if (lRefCnt == 0)                 \
	{                                 \
		GlobalFactory::Instance().UnLock();\
	}				\
	return lRefCnt;	\
}
#endif

#define DECLARE_SINGLETON_OBJECT()  public:  \
    IMPLEMENT_SINGLETON_RELEASE()            \
    IMPLEMENT_SINGLETON_ADDREF()             \
    IMPLEMENT_SINGLETON_CREATOR()

//////////////////////////////////////////////////////////////////////////
//QueryInterfaceʵ�ֺ�,һ��QueryInterfaceʵ�ֿ�������
//KSCOM_QUERY_BEGIN;
//KSCOM_QUERY_ENTRY(IFaceSample);
//KSCOM_QUERY_END;
#define KSCOM_QUERY_BEGIN  public:          \
KSRESULT __stdcall QueryInterface(const KSIID &riid, void **ppv)\
{                                           \
    KSRESULT res = S_OK;                    \
    if (riid == KS_IIDOF(IUnknown)){      \
    *ppv = reinterpret_cast<IUnknown*>(this);


#define KSCOM_QUERY_ENTRY(_interface)       \
    }                                       \
    else if(riid == KS_IIDOF(_interface)){  \
    *ppv = static_cast<_interface*>(this); 
    

#define KSCOM_QUERY_ENTRY2(_interface, _derived)  \
    }                                             \
    else if(riid == KS_IIDOF(_interface)){        \
    *ppv = static_cast<_interface*>(static_cast<_derived*>(this));


#define KSCOM_QUERY_END   \
    }                     \
    else                  \
    {                     \
    *ppv = NULL;          \
    return E_NOINTERFACE; \
    }                     \
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();\
    return res;           \
}

//////////////////////////////////////////////////////////////////////////
//ָ���ӿ�iid��QueryInterfaceʵ�ֺ�,һ��QueryInterfaceʵ�ֿ�������
//KSCOM_QUERY_BEGIN_WITH_IID(IID_IUnknown);
//KSCOM_QUERY_BEGIN_WITH_IID(IID_IFaceSample, IFaceSample);
//KSCOM_QUERY_END;
#define KSCOM_QUERY_BEGIN_WITH_IID(_iunk_iid)  public:\
KSRESULT __stdcall QueryInterface(const KSIID &riid, void **ppv)\
{                                           \
    KSRESULT res = S_OK;                    \
    if (riid == iunk_iid){                  \
    *ppv = reinterpret_cast<IUnknown*>(this);


#define KSCOM_QUERY_ENTRY_WITH_IID(_iface_iid, _interface)\
     }                             \
    else if(riid == _iface_iid){   \
    *ppv = static_cast<_interface*>(this); 


#define KSCOM_QUERY_ENTRY2_WITH_IID(_iface_iid, _interface, _derived)\
    }                              \
	else if(riid == _iface_iid){   \
	*ppv = static_cast<_interface*>(static_cast<_derived*>(this));

//////////////////////////////////////////////////////////////////////////
#define KSCOM_SIMPLE_ADDREF_IMPL_WITH_REF_COUNT(_m_refcnt)		\
ULONG STDMETHODCALLTYPE AddRef(void)							\
{																\
	return ++_m_refcnt;											\
}																

#define KSCOM_SIMPLE_RELEASE_IMPL_WITH_REF_COUNT(_m_refcnt)		\
ULONG STDMETHODCALLTYPE Release(void)							\
{																\
	assert(long(_m_refcnt) > 0);								\
	long lRefCnt = --_m_refcnt;									\
	if (0 == _m_refcnt)											\
	{															\
		delete this;											\
	}															\
	return lRefCnt;												\
}

#define KSCOM_DECLARE_REF_COUNT(_m_refcnt, _ref_init_count)		\
private:														\
	KSRefCnt_WithArgument<_ref_init_count> _m_refcnt;

#define KSCOM_SIMPLE_ADDREF_RELEASE_IMPL(_m_refcnt, _ref_init_count)\
public:															\
KSCOM_SIMPLE_ADDREF_IMPL_WITH_REF_COUNT(_m_refcnt)				\
KSCOM_SIMPLE_RELEASE_IMPL_WITH_REF_COUNT(_m_refcnt)				\
KSCOM_DECLARE_REF_COUNT(_m_refcnt, _ref_init_count)

//ʵ��AddRef()������Release()�����ĺ�,���ü���Ĭ��Ϊ0
#define KSCOM_SIMPLE_ADDREF_RELEASE_DEFAULT_IMPL_0()			\
KSCOM_SIMPLE_ADDREF_RELEASE_IMPL(m_RefCnt, 0)

//ʵ��AddRef()������Release()�����ĺ�,���ü���Ĭ��Ϊ1
#define KSCOM_SIMPLE_ADDREF_RELEASE_DEFAULT_IMPL_1()			\
KSCOM_SIMPLE_ADDREF_RELEASE_IMPL(m_RefCnt, 1)

#endif //SCOMBASE_H