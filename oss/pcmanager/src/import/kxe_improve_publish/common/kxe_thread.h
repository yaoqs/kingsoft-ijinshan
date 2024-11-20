//////////////////////////////////////////////////////////////////////
///		@file		kxe_thread.h
///		@author		luopeng
///		@date		2008-8-22 10:38:34
///
///		@brief		�߳���صĶ���
//////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @defgroup kxebase_src_thread_group KXEngine Architecture Thread Assistant Interface
 * @{
 */

/// �����Զ���ȡ���ͷ�ͬ�������Guardģ��
template
<
	typename MutexType
>
class KxEMutexGuard
{
public:
	/**
	 * @brief ͨ������ģ�������Acquire�Զ���ȡ����Ȩ
	 */
	KxEMutexGuard(MutexType& mutex) : m_mutex(mutex)
	{
		m_mutex.Acquire();
	}

	/**
	* @brief ͨ������ģ�������Release�Զ����˳�����ʱ�ͷ�����Ȩ
	*/
	~KxEMutexGuard()
	{
		m_mutex.Release();
	}

private:
	MutexType& m_mutex;
};

/**
 * @brief �����߳�ͬ������,ΪCRITICAL_SECTION�ķ�װ
 */
class KxEThreadMutex
{
public:
	KxEThreadMutex()
	{
		InitializeCriticalSection(&m_cs);
	}
	~KxEThreadMutex()
	{
		DeleteCriticalSection(&m_cs);
	}

	/**
	 * @brief ��ȡ�߳�ͬ����������Ȩ,��û��ȡ��,������
	 */
	void Acquire()
	{
		EnterCriticalSection(&m_cs);
	}

	/**
	* @brief �ͷ��߳�ͬ����������Ȩ
	*/
	void Release()
	{
		LeaveCriticalSection(&m_cs);
	}

	/**
	 * @brief ���Ի�ȡ�߳�ͬ����������Ȩ,��û��ȡ��,������false
	 * @return TRUE �ɹ���ȡ
	 * @return FALSE ��ȡʧ��
	 */
#if _WIN32_WINNT >= 0x400
	bool TryAcquire()
	{
		return TryEnterCriticalSection(&m_cs) == TRUE;
	}
#endif

private:
	CRITICAL_SECTION m_cs;
};

/**
 * @brief ���������Զ���ȡ���ͷ��߳�ͬ������KxEThreadMutex������
 */
typedef KxEMutexGuard<KxEThreadMutex> KxEThreadMutexGuard;

/// ������̰߳�ȫ�Ķ���
template
<
	typename T
>
class KxEThreadQueue
{
public:
	KxEThreadQueue()
	{
		m_uMaxThread = 0;
		m_uWaitThreadCount = 0;
		m_uQueueLength = 0;
		m_hCompletionPort = NULL;
	}

	int Open(unsigned int uMaxThread)
	{
		KxEThreadMutexGuard guard(m_mutex);
		if (m_hCompletionPort != NULL)
		{
			return -1;
		}

		m_uMaxThread = uMaxThread;
		m_hCompletionPort = CreateIoCompletionPort(
			INVALID_HANDLE_VALUE,
			NULL,
			0,
			uMaxThread
			);
		if (m_hCompletionPort == NULL)
		{
			return GetLastError();
		}

		return 0;
	}

	int Close()
	{
		KxEThreadMutexGuard guard(m_mutex);
		if (m_hCompletionPort == NULL)
		{
			return -1;
		}

		// ��������
		for (unsigned int i = 0; i < m_uWaitThreadCount; ++i)
		{
			PostQueuedCompletionStatus(
				m_hCompletionPort,
				0,
				0xffffffff,
				NULL
				);
		}

		CloseHandle(m_hCompletionPort);
		m_hCompletionPort = NULL;

		return 0;
	}

	int Enqueue(T* pValue)
	{
		KxEThreadMutexGuard guard(m_mutex);
		if (m_hCompletionPort == NULL)
		{
			return -1;
		}

		BOOL bRet = PostQueuedCompletionStatus(
			m_hCompletionPort,
			0,
			0,
			reinterpret_cast<LPOVERLAPPED>(pValue)
			);
		if (!bRet)
		{
			return GetLastError();
		}

		return 0;
	}

	int Dequeue(
		T** ppValue, 
		unsigned int uMillisecond
		)
	{
		{
			KxEThreadMutexGuard guard(m_mutex);
			if (m_hCompletionPort == NULL)
			{
				return -1;
			}

			++m_uWaitThreadCount;
		}

		DWORD dwSize = 0;
		DWORD dwKey = 0;
		BOOL bRet = GetQueuedCompletionStatus(
			m_hCompletionPort,
			&dwSize,
			&dwKey,
			reinterpret_cast<LPOVERLAPPED*>(ppValue),
			uMillisecond
			);

		{
			KxEThreadMutexGuard guard(m_mutex);
			if (m_hCompletionPort == NULL)
			{
				return -1;
			}

			--m_uWaitThreadCount;
		}

		if (!bRet)
		{
			return GetLastError();
		}

		if (dwKey == 0xFFFFFFFF) // ��־����
		{
			return -1;
		}
		else  // ȡ������ȷ����
		{
			return 0;
		}
	}

private:
	KxEThreadMutex m_mutex;
	unsigned int m_uWaitThreadCount;
	unsigned int m_uMaxThread;
	unsigned int m_uQueueLength;
	HANDLE m_hCompletionPort;
};


/**
 * @}
 */
