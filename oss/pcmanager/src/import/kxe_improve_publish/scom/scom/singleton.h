/********************************************************************
* CreatedOn: 2005-8-16   15:03
* FileName: Singleton.h
* CreatedBy: qiuruifeng <qiuruifeng@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/
#ifndef SINGLETON_H
#define SINGLETON_H
#include "Threads.h"
#include <cassert>

//////////////////////////////////////////////////////////////////////////
//�������ģ�岻�ܱ���̬(��ȫ��)����Ĺ��캯������,��Ϊ�ھ�̬����Ĺ��캯��ִ��ʱ,
//KSComAutoThreadMutex�����ܱ�֤����ʼ����,������ctr���к�(����main������dllmain������),��ľ�̬��Ա�Ѿ���ʼ��
//������������
template<class T>
class SingletonHolder
{
public:
	typedef  T* volatile  _PtrInstanceType;

	static T& Instance();
private:
	SingletonHolder(){};
	SingletonHolder(const SingletonHolder&){};
	SingletonHolder& operator = (const SingletonHolder&){};
	//	~SingletonHolder()
	//	{
	//		m_pInstance = 0;
	//		m_destroyed = true;
	//	};
	static void MakeInstance();
	static void DestroySingleton();
	static void OnDeadReference();

	struct _Lock 
	{
		_Lock()
		{
			m_Lock.Lock();
		}
		~_Lock()
		{
			m_Lock.Unlock();
		}
	};
	friend struct _Lock;

private:
	static KSComAutoThreadMutex m_Lock;
	static _PtrInstanceType m_pInstance;
	static  bool m_destroyed;
};
//////////////////////////////////////////////////////////////////////////
// init data
template<class T>
KSComAutoThreadMutex SingletonHolder<T>::m_Lock;

template<class T>
typename SingletonHolder<T>::_PtrInstanceType
SingletonHolder<T>::m_pInstance = 0;

template<class T>
bool SingletonHolder<T>::m_destroyed = 0;

template<class T>
inline T& SingletonHolder<T>::Instance()
{
	if (!m_pInstance)
	{
		MakeInstance();
	}
	return *m_pInstance;
}
//////////////////////////////////////////////////////////////////////////
//MakeInstance()
template<class T>
inline void SingletonHolder<T>::MakeInstance()
{
	//KSClassLockGuard<T> guard;
	_Lock guard;
	if (!m_pInstance)
	{
		if (m_destroyed)
		{
			OnDeadReference();
		}
		//static T TheInstance;
		//m_pInstance = &TheInstance;
		m_pInstance = new T;
		m_destroyed = false;
		atexit(DestroySingleton);
	}
}
//////////////////////////////////////////////////////////////////////////
//OnDeadReference()
template<class T>
inline void SingletonHolder<T>::OnDeadReference()
{
	throw std::runtime_error("Dead Reference Detected");
}

template<class T>
inline void SingletonHolder<T>::DestroySingleton()
{
	delete m_pInstance;
	m_pInstance = 0;
	m_destroyed = true;
}

//////////////////////////////////////////////////////////////////////////
//�������ģ����Ա���̬(��ȫ��)����Ĺ��캯������,��ΪKSComThreadMutexû�й��캯��,
//��ͨ���ڲ��ı���ж��Ƿ��ʼ��,���û�г�ʼ������г�ʼ��,�������ڵ�һ�ε��õ�ʱ�Ž���
//KSComThreadMutex�ĳ�ʼ��,�����Ǳ���̬(��ȫ��)����Ĺ��캯������ʱ,������߳�ͬʱ����
//Instance()����,�б���ʼ�����εĿ���.
template<class T>
class SingletonHolder_Static
{
public:
	typedef  T* volatile  _PtrInstanceType;

	static T& Instance();
private:
	SingletonHolder_Static(){};
	SingletonHolder_Static(const SingletonHolder_Static&){};
	SingletonHolder_Static& operator = (const SingletonHolder_Static&){};
//	~SingletonHolder()
//	{
//		m_pInstance = 0;
//		m_destroyed = true;
//	};
	static void MakeInstance();
	static void DestroySingleton();
	static void OnDeadReference();

    	struct _Lock 
    	{
        	_Lock()
        	{
            		m_Lock.Lock();
        	}
        	~_Lock()
        	{
            		m_Lock.Unlock();
		}
    	};
    	friend struct _Lock;

private:
    static KSComThreadMutex m_Lock;
	static _PtrInstanceType m_pInstance;
	static  bool m_destroyed;
};
//////////////////////////////////////////////////////////////////////////
// init data
template<class T>
KSComThreadMutex SingletonHolder_Static<T>::m_Lock = {0};

template<class T>
typename SingletonHolder_Static<T>::_PtrInstanceType
SingletonHolder_Static<T>::m_pInstance = 0;

template<class T>
bool SingletonHolder_Static<T>::m_destroyed = 0;

template<class T>
inline T& SingletonHolder_Static<T>::Instance()
{
	if (!m_pInstance)
	{
		MakeInstance();
	}
	return *m_pInstance;
}
//////////////////////////////////////////////////////////////////////////
//MakeInstance()
template<class T>
inline void SingletonHolder_Static<T>::MakeInstance()
{
	//KSClassLockGuard<T> guard;
	_Lock guard;
	if (!m_pInstance)
	{
		if (m_destroyed)
		{
			OnDeadReference();
		}
		//static T TheInstance;
		//m_pInstance = &TheInstance;
		m_pInstance = new T;
		m_destroyed = false;
		atexit(DestroySingleton);
	}
}
//////////////////////////////////////////////////////////////////////////
//OnDeadReference()
template<class T>
inline void SingletonHolder_Static<T>::OnDeadReference()
{
	throw std::runtime_error("Dead Reference Detected");
}

template<class T>
inline void SingletonHolder_Static<T>::DestroySingleton()
{
	delete m_pInstance;
	m_pInstance = 0;
	m_Lock.Term();
	m_destroyed = true;
}

#endif //SINGLETON_H