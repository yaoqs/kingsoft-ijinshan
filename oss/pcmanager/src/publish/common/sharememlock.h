////////////////////////////////////////////////////////////////////////////////
//      
//      File for url cache manager
//      
//      File      : sharememlock.h
//      Version   : 1.0
//      Comment   : �ṩһ�����ʹ����ڴ����
//      
//      Create at : 2010-2-3
//      Create by : liupeng
//		Motify by : 
//      
///////////////////////////////////////////////////////////////////////////////

#pragma once 

//////////////////////////////////////////////////////////////////////////
// ���������ԣ�
// ����߳̿���ͬʱ��ȡ
// ����д��Ҫ��ʱ���µĶ�ȡ���󱻹���ֱ������д�꣬��д������
// ֻ����һ���߳���д

typedef struct _tagShareMemLock
{
	volatile LONG			m_nLock;
	volatile LONG			m_nReadCnt;
	volatile LONG			m_nWrite;

	volatile DWORD			m_nDbgLockProcessID;
	volatile DWORD			m_nDbgLockThreadID;
	volatile DWORD			m_nDbgLockTime;

	void	InitLock()
	{
		m_nLock = 0;
		m_nReadCnt = 0;
		m_nWrite = 0;
	}

	BOOL	TryLockReadCntLock()
	{
		return (::InterlockedCompareExchange(&m_nLock, 1, 0) == 0);
	}

	BOOL	UnlockReadCntLock()
	{
		m_nLock = 0;
		return TRUE;
	}

	BOOL	TryLockWriteLock()
	{
		return (::InterlockedCompareExchange(&m_nWrite, 1, 0) == 0);
	}

	BOOL	UnlockWriteLock()
	{
		m_nWrite = 0;
		return TRUE;
	}
	
	//////////////////////////////////////////////////////////////////////////
	BOOL	TryLockRead()
	{
		// ������޸�������ô���ȿ����޸�
		if (m_nWrite)
			return FALSE;

		// ����Ѿ����޸��ˣ���ô�ȵȵȣ���֮����жϲ�
		// ׼ȷ�����ǿ����𵽼��ٵ�����
		if (m_nReadCnt < 0)
			return FALSE;

		// ��ʼ����
		if (TryLockReadCntLock())
		{
			if (m_nReadCnt >= 0)
			{
				m_nReadCnt ++;
				UnlockReadCntLock();
				return TRUE;
			}
			else
			{
				UnlockReadCntLock();
				return FALSE;
			}
		}
		return FALSE;
	}

	BOOL	LockRead()
	{
		while (!TryLockRead())
			::Sleep(1);
		return TRUE;
	}

	void	UnLockRead()
	{
		while (!TryLockReadCntLock())
			::Sleep(1);
		m_nReadCnt --;
		UnlockReadCntLock();
	}

	//////////////////////////////////////////////////////////////////////////
	BOOL	TryLockWrite()
	{
		// ��������ڶ�����ô�ٵȵȣ���֮����жϲ�׼ȷ
		// ���ǿ����𵽼�������
		if (m_nReadCnt > 0)
			return FALSE;

		if (TryLockReadCntLock())
		{
			// ȷ��û���˶���Ҳû����д
			if (m_nReadCnt == 0)
			{
				m_nReadCnt = -10000;
				UnlockReadCntLock();
				return TRUE;
			}
			else
			{
				UnlockReadCntLock();
				return FALSE;
			}
		}
		return FALSE;
	}

	BOOL	LockWrite()
	{
		// ��֤û����������д
		while (!TryLockWriteLock())
			::Sleep(1);

		// ��֤������û���ڶ���Ҳû����д
		while (!TryLockWrite())
			::Sleep(1);
		return TRUE;
	}

	void	UnLockWrite()
	{
		while (!TryLockReadCntLock())
			::Sleep(1);
		m_nReadCnt = 0;
		UnlockReadCntLock();

		UnlockWriteLock();
	}
}ShareMemLock;