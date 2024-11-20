////////////////////////////////////////////////////////////////
//
//	Filename: 	ksqliteimp.h
//	Creator:	yangjun  <yangjun@kingsoft.com>
//	Date:		2009-7-29  19: 47
//	Comment:	
//
///////////////////////////////////////////////////////////////
#pragma once

#if defined(_USE_SQLITE_DLL)
#include "ksqlite3_import.h"
#else
#include "sqlite3.h"
#pragma comment(lib,"sqlite3.lib")
#endif

#include <string>
#include "kthreadsyn.h"

class IKSqliteResult
{
public:
	virtual size_t GetRowCount() = 0;
	virtual size_t GetColCount() = 0;

	virtual void   Release() = 0;

	virtual __int64			 GetInt64Value(size_t nRow, size_t nCol) = 0;
	virtual unsigned __int64 GetUnsignedInt64Value(size_t nRow, size_t nCol) = 0;
	virtual const char*		 GetStringValue(size_t nRow, size_t nCol) = 0;
};

template<class LOCK_TYPE>
class KSqliteImp
{
public:
	KSqliteImp(void);
	~KSqliteImp(void);

	/**
	* @brief	��ʼ�����ݿ⡡
	* @param	[in]	szDbName ���ݿ�����
	* @param	[in]	szDbKey			���ݿ������
	* @return	0�ɹ�������Ϊʧ��
	*/
	int Init(const char *szDbName,
		/*[in]*/ unsigned int	uWaitTimeout = -1,
		/*[in]*/ const char	*szDbKey = NULL
		);
	
	int Uninit();

	/**
	* @brief	ִ��һ��SQL���
	* @param	[in]	sql		 Ҫִ�е�SQL���
	* @param	[in]	pszError ��������ʱpszErrorָ�������Ϣ���ַ���,��NULL����Դ�����Ϣ
	* @return	0�ɹ�������Ϊʧ��
	* @remark	���*ppszError��Ϊ��,��Ҫ����FreeData���ͷ�*ppszErrorָ����ַ���
	*/
	int Execute(/*[in]*/ const char* sql,/*[in]*/ char **ppszError = NULL);
	
	/**
	* @brief	ִ�в�ѯ���
	* @param	[in]	sql	Ҫɨ���SQL���
	* @param	[out]	ppv	���صĽ������ӿ�
	* @return	0�ɹ�������Ϊʧ��
	* @remark	����ɹ�,�ⲿ����IKSqliteResult��Release���ͷŽӿ�
	*/
	int Query(/*[in]*/ const char* sql,/*[in]*/ IKSqliteResult** ppv);

	/**
	* @brief	��ʼһ������
	* @param	[in]	pszError ��������ʱpszErrorָ�������Ϣ���ַ���,��NULL����Դ�����Ϣ
	* @return	0�ɹ�������Ϊʧ��
	* @remark	���*ppszError��Ϊ��,��Ҫ����FreeData���ͷ�*ppszErrorָ����ַ���
	*			ע�������ʱ�������߳�Ҳ��
	*/
	int BeginTransac(/*[in]*/ char **ppszError = NULL);

	/**
	* @brief	ִ��һ�������е�SQL���
	* @param	[in]	sql		 Ҫִ�е�SQL���
	* @param	[in]	pszError ��������ʱpszErrorָ�������Ϣ���ַ���,��NULL����Դ�����Ϣ
	* @return	0�ɹ�������Ϊʧ��
	* @remark	���*ppszError��Ϊ��,��Ҫ����FreeData���ͷ�*ppszErrorָ����ַ���
				
	*/
	int ExecuteInTransac(/*[in]*/ const char* sql, /*[in]*/ char **ppszError = NULL);

	/**
	* @brief	ִ�в�ѯ���
	* @param	[in]	sql	Ҫɨ���SQL���
	* @param	[out]	ppv	���صĽ������ӿ�
	* @return	0�ɹ�������Ϊʧ��
	* @remark	����ɹ�,�ⲿ����IKSqliteResult��Release���ͷŽӿ�
				ͬʱ��ʼ���������LOCK_TYPEû��ʵ�ֻ��������ܻ᷵�����ݿⱻ�����Ĵ�����Ϣ
	*/
	int QueryInTransac(/*[in]*/ const char* sql,/*[in]*/ IKSqliteResult** ppv);

	/**
	* @brief	�ύһ������
	* @param	[in]	pszError ��������ʱpszErrorָ�������Ϣ���ַ���,��NULL����Դ�����Ϣ
	* @return	0�ɹ�������Ϊʧ��
	* @remark	���*ppszError��Ϊ��,��Ҫ����FreeData���ͷ�*ppszErrorָ����ַ���
	*			ͬʱ��ʼ���������LOCK_TYPEû��ʵ�ֻ��������ܻ᷵�����ݿⱻ�����Ĵ�����Ϣ
	*/
	int CommitTransac(/*[in]*/ char **ppszError = NULL);

	/**
	* @brief	�ع�һ������
	* @param	[in]	pszError ��������ʱpszErrorָ�������Ϣ���ַ���,��NULL����Դ�����Ϣ
	* @return	0�ɹ�������Ϊʧ��
	* @remark	���*ppszError��Ϊ��,��Ҫ����FreeData���ͷ�*ppszErrorָ����ַ���
	*			ͬʱ��ʼ���������LOCK_TYPEû��ʵ�ֻ��������ܻ᷵�����ݿⱻ�����Ĵ�����Ϣ
	*/
	int RollbackTransac(/*[in]*/ char **ppszError = NULL);

	/**
	* @brief	��ʽ��һ��Sql���
	* @param	[in]	sql Ҫ��ʽ����Sql��ʽ���������
	* @return	���ظ�ʽ�����Sql���
	* @remark	���ص�Sql���Ҫʹ��FreeData���ͷ�
				ͬʱ��ʼ���������LOCK_TYPEû��ʵ�ֻ��������ܻ᷵�����ݿⱻ�����Ĵ�����Ϣ
	*/
	const char* EscapeSqlString(/*[in]*/ const char* sql,...);

	/**
	* @brief	��ʽ��һ��Sql���
	* @param	[in]	sql		Ҫ��ʽ����Sql��ʽ���������
	* @param	[in]	arglist	Ҫ��ʽ����Sql���Ĳ���
	* @return	���ظ�ʽ�����Sql���
	* @remark	���ص�Sql���Ҫʹ��FreeData���ͷ�
	*/
	const char* VEscapeSqlString(/*[in]*/ const char *sql,/*[in]*/ va_list arglist);

	/**
	* @brief	�ͷ��ڲ����ص��ڴ�
	* @param	[in] pData Ҫ�ͷŵ��ڴ�
	* @remark	���Դ�NULL
	*/
	void FreeData(/*[in]*/ const void *pData);

	/**
	* @brief	�ж�����ִ�еĲ���
	* @remark	���ڶ��߳�ʱִ��˳��Ĳ�ȷ����
	*/
	void NotifyInterrupt();

	/**
	* @brief	�ָ��жϵ�״̬
	* @remark	���ڶ��߳�ʱִ��˳��Ĳ�ȷ����,������ʽ������жϵ�״̬,�����ڷ���ʼ��ʱ����һ���߳��е��ô˺���
	*/
	void NotifyResume();

private:
	template<class T>
	friend int sqliteBusyCallback(void *ptr,int count);

	bool IsBusyTimeOut(int nCount);

	bool TryBeginTransac();

	const char *errorCodeAsString(int nErrCode);

	void GetDbMutexName(std::wstring & strMutexName, const char* pszDbFileName);



protected:
	sqlite3*		m_db;
	bool			m_bIsInterrupt;
	LOCK_TYPE		m_lockMutex;
	KSYNEvent		m_waitEvent;
	unsigned int	m_uWaitTimeOut;
};

class KFakedMutex
{
public:
	int Init(const TCHAR* pszName = NULL, LPSECURITY_ATTRIBUTES psa = NULL)
	{return 0;}

	int UnInit()
	{return 0;}

	bool TryLock()
	{return true;}

	int UnLock()
	{return true;}
};

class _KSYNMutex: public KSYNMutex
{
public:
	int Init(const TCHAR* pszName = NULL, LPSECURITY_ATTRIBUTES psa = NULL)
	{
		return 0;
	}
};

typedef KSqliteImp<KFakedMutex>		KSqliteDbNoSyn;			///	����Ҫͬ����SQLITE��������,�����ݿⱻ�������̻��߳�ռ��ʱ����SQLITE_BUSY
typedef KSqliteImp<_KSYNMutex>		KSqliteDbThreadSyn;		///	������Ҫ�߳�ͬ����SQLITE��������
typedef KSqliteImp<KSYNKernelMutex>	KSqliteDbProcessSyn;	///	���̻���̶߳�ʵ��ͬ����SQLITE��������

#include "ksqliteimp_inl.h"