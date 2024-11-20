#ifndef _CONEW_TASK_H_
#define _CONEW_TASK_H_

namespace conew
{

//
// �������
//
class CTaskMgr;
class IBaseTask
{
public:
	//
	// ���ȼ�
	//
	enum TPriority
	{
		TP_Highest		= 0,
		TP_Above_Normal	= (1<<8),
		TP_Normal		= (1<<16),
		TP_Below_Normal	= (1<<24),
		TP_Lowest		= (1<<30),
		TP_Invalid		= (TP_Lowest + 1),
	};

	//
	// �¼�
	//
	enum TEvent
	{
		TE_Unknown = 0,
		TE_Canceled,
		TE_Removed,
		TE_Completed,
	};

public:
	IBaseTask(LONG type);
	virtual ~IBaseTask() {}

public:
	//
	// ������Ϣ
	//
	void SetId(LONG id);
	LONG GetId() const;

	// ���ͱ������0
	void SetType(LONG type);
	LONG GetType() const;

	void SetPriority(ULONG priority);
	ULONG GetPriority() const;

	//
	// ���ü���
	//
	LONG AddRef();
	LONG Release();

	//
	// �������
	//
	//@Return
	// ����TRUE������������������������
	//
	virtual BOOL TaskProcess(CTaskMgr *pMgr);
	virtual void TaskNotify(CTaskMgr *pMgr, TEvent event);

private:
	IBaseTask(const IBaseTask&);
	IBaseTask& operator=(const IBaseTask&);

protected:
	LONG			m_id;
	LONG			m_type;
	ULONG			m_priority;
	volatile LONG	m_refCnt;	
};


//
// ����������
//
template<class Type>
class CTaskAdapter : public conew::IBaseTask
{
public:
	typedef BOOL (Type::*PFProcess)(conew::CTaskMgr*);
	typedef void (Type::*PFNotify)(conew::CTaskMgr*, TEvent);

public:
	CTaskAdapter(LONG type, Type *pInst, PFProcess pfProcess, PFNotify pfNotify = NULL)
		: IBaseTask(type), _pInst(pInst), _pfProcess(pfProcess), _pfNotify(pfNotify) {}

	virtual BOOL TaskProcess(conew::CTaskMgr *pMgr)
	{
		if(_pInst != NULL && _pfProcess != NULL)
			return (_pInst->*_pfProcess)(pMgr);
		return TRUE;
	}

	virtual void TaskNotify(conew::CTaskMgr *pMgr, TEvent event)
	{
		if(_pInst != NULL && _pfNotify != NULL)
			(_pInst->*_pfNotify)(pMgr, event);
	}

private:
	Type *_pInst;
	PFProcess _pfProcess;
	PFNotify _pfNotify;
};

//
// �������������ֺ���
//
//@Usage
// IBase *pTask = MakeTask(type, this, &ClassName::MemberFunc);
//
template<class Type> inline 
CTaskAdapter<Type>* MakeTask(LONG type, Type *pInst, 
							 BOOL (Type::*pfProcess)(conew::CTaskMgr*), 
							 void (Type::*pfNotify)(conew::CTaskMgr*, conew::IBaseTask::TEvent) = NULL)
{
	return new CTaskAdapter<Type>(type, pInst, pfProcess, pfNotify);
}
//////////////////////////////////////////////////////////////////////////
inline IBaseTask::IBaseTask(LONG type)
{
	m_id		= 0L;
	m_type		= type;
	m_priority	= TP_Normal;
	m_refCnt	= 1L;
}

inline void IBaseTask::SetId(LONG id) 
{ m_id = id; }
inline LONG IBaseTask::GetId() const 
{ return m_id; }

inline void IBaseTask::SetType(LONG type) 
{ m_type = type; }
inline LONG IBaseTask::GetType() const 
{ return m_type; }

inline void IBaseTask::SetPriority(ULONG priority) 
{ m_priority = priority; }
inline ULONG IBaseTask::GetPriority() const 
{ return m_priority; }

inline LONG IBaseTask::AddRef() 
{ return InterlockedIncrement(&m_refCnt); }
inline LONG IBaseTask::Release() 
{ 
	if(InterlockedDecrement(&m_refCnt) <= 0)
	{ 
		delete this; return 0L; 
	}
	else 
	{ 
		return m_refCnt;
	}
}

inline BOOL IBaseTask::TaskProcess(CTaskMgr *pMgr) { return FALSE; }
inline void IBaseTask::TaskNotify(CTaskMgr *pMgr, IBaseTask::TEvent event) {}

}

#endif