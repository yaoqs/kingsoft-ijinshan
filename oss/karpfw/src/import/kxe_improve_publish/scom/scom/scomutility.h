/********************************************************************
* CreatedOn: 2005-9-5   18:03
* FileName: SCOMUtility.h
* CreatedBy: qiuruifeng <qiuruifeng@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/

#ifndef SCOMUTILITY_H
#define SCOMUTILITY_H

#include "SCOMAPI.h"
#include "KSIUnknown.h"

//����->���ķ���ֵ����,������AddRef��Release����,ʹ���Ϊ˽��,���ܱ�������
template <class T>
class _NoAddRefReleaseOnKSCOMPtr : public T
{
private:
    virtual unsigned long __stdcall AddRef(void) = 0;
    virtual unsigned long __stdcall Release(void) = 0;
};

template <class T>
class KSCOMPtr
{
public:
    typedef T _PtrClass;

    KSCOMPtr() 
    {
        m_pInterface = NULL;
    }
    KSCOMPtr(int nNull) 
    {
        KS_ASSERT(nNull == 0);
        (void)nNull;
        m_pInterface = NULL;
    }
    KSCOMPtr(T* lp) 
    {
        m_pInterface = lp;
        if (m_pInterface)
            m_pInterface->AddRef();
    }
	KSCOMPtr(const KSCOMPtr &copy)
	{
		m_pInterface = copy.m_pInterface;
		if(m_pInterface)
			m_pInterface->AddRef();
	}

	KSCOMPtr& operator = (const KSCOMPtr &copy)
	{
		if (m_pInterface != copy.m_pInterface)
		{
			Release();
			m_pInterface = copy.m_pInterface;
			if (m_pInterface)
				m_pInterface->AddRef();
		}
		return *this;
	}

    ~KSCOMPtr() 
    {
        if (m_pInterface)
            m_pInterface->Release();
    }

    //�ͷŽӿ�ָ��
    void Release() 
    {
        T* pTemp = m_pInterface;
        if (pTemp)
        {
            m_pInterface = NULL;
            pTemp->Release();
        }
    }

    operator T*() const 
    {
        return m_pInterface;
    }

    T& operator*() const 
    {
        KS_ASSERT(m_pInterface != NULL);
        return *m_pInterface;
    }

	//vs2005��stl�������й������ʱ��Ҫ����ȡַ��,
	//�������Ͳ�һ�½���������ָ���޷��������й���,����ȥ����ȡַ���ŵ�����
	//�ɶ�����ڴ�ṹ����������ָ��ĵ�ַ���ڲ�ԭ��ָ��ĵ�ֵַһ��
	//������Ҫȡ�ڲ�ԭ��ָ��ĵ�ַʱҲ���԰�����ָ��ĵ�ַǿת�õ�.
	//��Ϊ����ȡַ���Ź��ܵİ�ȫ�滻,�ṩһ��ȡַ����
	T** Address()
	{
	   KS_ASSERT(m_pInterface == NULL);
	   return &m_pInterface;
	}
    //ʹ�ø÷���ǰҪȷ��ָ��Ϊ��
    //T** operator&() 
    //{
    //   KS_ASSERT(m_pInterface == NULL);
    //    return &m_pInterface;
    //}

	
    //����->��,����ֵ����ԭʼָ��,ǿ�Ʋ��ܹ�ʹ��->AddRef()��->Release()
    //����Ϊ�˱�������->Release()�����������������νӿ�ָ��
    _NoAddRefReleaseOnKSCOMPtr<T>* operator->() const 
    {
        KS_ASSERT(m_pInterface != NULL);
        return (_NoAddRefReleaseOnKSCOMPtr<T>*)m_pInterface;
    }

    bool operator!() const 
    {
        return (m_pInterface == NULL);
    }

    bool operator<(T* pT) const 
    {
        return (m_pInterface < pT);
    }

    bool operator==(T* pT) const 
    {
        return (m_pInterface == pT);
    }

    //��ͬ���͵Ľӿ�ָ�븳ֵ����ǰָ��
    T* operator=(T* pT)
    {
        if (m_pInterface != pT)
        {
            Release();
            m_pInterface = pT;
            if (m_pInterface)
                m_pInterface->AddRef();
        }
        return m_pInterface;
    }

    //���������͵Ľӿ�ָ�븳ֵ����ǰָ��,
    //��ʹ�� operator= �ķ�����Ϊ�˿��Ի�ȡ�������Լ�
    //������Ϊ���Ǽ�⸳ֵ�Ƿ�ʧ�ܶ������Ĵ���
    KSRESULT Assign(IUnknown *lp)
    {
        Release();
        if (lp != NULL)
        {
             return  lp->QueryInterface(KS_IIDOF(T), (void**)&m_pInterface);              
        }
        else
        {
           return  S_OK;
        }
    }

    //�ж������ӿ�ָ���Ƿ�����ͬһ������
    bool IsEqualObject(IUnknown* pOther) 
    {
        if (m_pInterface == NULL && pOther == NULL)
            return true;

        if (m_pInterface == NULL || pOther == NULL)
            return false;

        KSCOMPtr<KSIUnknown> punk1;
        KSCOMPtr<KSIUnknown> punk2;
        m_pInterface->QueryInterface(KS_IIDOF(IUnknown), (void**)&punk1);
        pOther->QueryInterface(KS_IIDOF(IUnknown), (void**)&punk2);
        return punk1 == punk2;
    }

    //��ԭʼ�ӿ�ָ���ȡ����Ȩ,���������ü���
    void Attach(T* p2) 
    {
        if (m_pInterface)
            m_pInterface->Release();
        m_pInterface = p2;
    }

    //������ָ�������Ȩ����һ��ԭʼ�Ľӿ�ָ��ʱʹ��,���������ü���
    T* Detach() 
    {
        T* pt = m_pInterface;
        m_pInterface = NULL;
        return pt;
    }

	void Swap(KSCOMPtr& other)
	{
		 T* pt = m_pInterface;
		 m_pInterface = other.m_pInterface;
		 other.m_pInterface = pt;
	}

    //����һ�ݾ���AddRef�Ľӿ�ָ��Ŀ���
    KSRESULT CopyTo(T** ppT) const
    {
        KS_ASSERT(ppT != NULL);
        if (ppT == NULL)
            return E_POINTER;
        *ppT = m_pInterface;
        if (m_pInterface)
            m_pInterface->AddRef();
        return S_OK;
    }

    //���Ͱ�ȫ��QueryInterface
    template <class Q>
        KSRESULT QueryInterface(Q** pp) const 
    {
        KS_ASSERT(pp != NULL);
        return m_pInterface->QueryInterface(KS_IIDOF(Q), (void**)pp);
    }
    //���Ͱ�ȫ��KSCoCreateInstance
    KSRESULT KSCoCreateInstance(const KSCLSID& clsid)
    {
        KS_ASSERT(m_pInterface == NULL);
        return ::KSCoCreateInstance(clsid, KS_IIDOF(T), (void**)&m_pInterface);
    }
private:
    T* m_pInterface;
};

#endif //SCOMUTILITY_H
