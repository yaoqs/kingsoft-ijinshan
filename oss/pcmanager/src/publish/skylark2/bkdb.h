/**
* @file    bkdb.h
* @brief   ...
* @author  bbcallen
* @date    2009-12-15 16:51
*/

#ifndef BKDB_H
#define BKDB_H

#include <unknwn.h>
#include "bkdbdef.h"

NS_SKYLARK_BEGIN

namespace BKDb
{
    /// ���������ʽ
    enum EM_TRANSLOCK
    {
        em_Deferred     = 1,    ///< �ӳ���, ��������
        em_Immediate    = 2,    ///< ������, �����ݿ�, �������ӿ��Զ����ݿ⵫����д���ݿ�, Ҳ���ܼ�������
        em_Exclusive    = 3,    ///< ������, �����ݿ�, ���������޷��������ݿ�
    };
}

/// ���ݿ��ѯ�����
class __declspec(uuid("288C088E-461A-4212-B6C5-73A69AE5EE24"))
ISQLiteComResultSet3: public IUnknown
{
public:
    /// ��ȡ�е���Ŀ
    virtual int         STDMETHODCALLTYPE GetColumnCount() = 0;

    /// ��ȡ������
    virtual int         STDMETHODCALLTYPE FindColumnIndex(LPCWSTR columnName) = 0;

    /// ��ȡ����
    virtual LPCWSTR     STDMETHODCALLTYPE GetColumnName(int columnIndex) = 0;


    /// ��ȡ������������
    virtual LPCWSTR     STDMETHODCALLTYPE GetDeclaredColumnType(int columnIndex) = 0;

    /// ��ȡ�����͵�ֵ
    virtual int         STDMETHODCALLTYPE GetColumnType(int columnIndex) = 0;




    virtual LPCWSTR     STDMETHODCALLTYPE GetAsString(int columnIndex, LPCWSTR nullValue = L"") = 0;    ///< ��ȡָ���е�ֵ(�ַ���)
    virtual LPCWSTR     STDMETHODCALLTYPE GetAsString(LPCWSTR columnName, LPCWSTR nullValue = L"") = 0; ///< ��ȡָ���е�ֵ(�ַ���)

    virtual int         STDMETHODCALLTYPE GetInt(int columnIndex, int nullValue = 0) = 0;               ///< ��ȡָ���е�ֵ(int)
    virtual int         STDMETHODCALLTYPE GetInt(LPCWSTR columnName, int nullValue = 0) = 0;            ///< ��ȡ�����͵�ֵ(int)

    virtual ULONGLONG   STDMETHODCALLTYPE GetInt64(int columnIndex, ULONGLONG nullValue = 0) = 0;       ///< ��ȡָ���е�ֵ(int64)
    virtual ULONGLONG   STDMETHODCALLTYPE GetInt64(LPCWSTR columnName, ULONGLONG nullValue = 0) = 0;    ///< ��ȡָ���е�ֵ(int64)

    virtual int         STDMETHODCALLTYPE GetBlob(int columnIndex, char* pBlog, int nBlogBytes) = 0;    ///< ��ȡָ���е�ֵ(blob)
    virtual int         STDMETHODCALLTYPE GetBlob(LPCWSTR columnName, char* pBlog, int nBlogBytes) = 0; ///< ��ȡָ���е�ֵ(blob)

    virtual int         STDMETHODCALLTYPE GetBlobBytes(int columnIndex) = 0;                            ///< ��ȡָ���е�blob����(�ֽ���)
    virtual int         STDMETHODCALLTYPE GetBlobBytes(LPCWSTR columnName) = 0;                         ///< ��ȡָ���е�blob����(�ֽ���)

    virtual BOOL        STDMETHODCALLTYPE IsNull(int columnIndex) = 0;      ///< �ж�ָ�����Ƿ�ΪNULL
    virtual BOOL        STDMETHODCALLTYPE IsNull(LPCWSTR columnName) = 0;   ///< �ж�ָ�����Ƿ�ΪNULL




    /// �жϽ������ָ���Ƿ��ѵ�ĩβ(���һ����¼�ĺ�һ��λ��)
    virtual BOOL        STDMETHODCALLTYPE IsEof() = 0;



    /// ȡ���������һ����¼
    virtual BOOL        STDMETHODCALLTYPE NextRow() = 0;
};



/// ���ݿ�Ԥ�������
class __declspec(uuid("2A32BD36-8C49-478e-85D0-00386DB0C81D"))
ISQLiteComStatement3: public IUnknown
{
public:
    /**
    * @brief    ִ��Ԥ�������
    * @param    pnRows  ����Ӱ�������Ŀ
    */ 
    virtual HRESULT     STDMETHODCALLTYPE ExecuteUpdate(int* pnRows = NULL) = 0;

    /// ִ��Ԥ�����ѯ
    virtual HRESULT     STDMETHODCALLTYPE ExecuteQuery(ISQLiteComResultSet3** ppiResultSet) = 0;

    /// ִ��Ԥ���������ѯ(select count(*) from ...)
    virtual int         STDMETHODCALLTYPE ExecuteScalar() = 0;



    virtual HRESULT     STDMETHODCALLTYPE Bind(int paramIndex, LPCWSTR szValue) = 0;        ///< �󶨲���(�ַ���)
    virtual HRESULT     STDMETHODCALLTYPE Bind(int paramIndex, int intValue) = 0;           ///< �󶨲���(int)
    virtual HRESULT     STDMETHODCALLTYPE Bind(int paramIndex, ULONGLONG int64Value) = 0;   ///< �󶨲���(int64)
    /// �󶨲���(ANSI��ANSI���ݵ��ַ���,Լ��ΪUTF-8����)
    virtual HRESULT     STDMETHODCALLTYPE Bind(int paramIndex, LPCSTR szValue) = 0;         
    virtual HRESULT     STDMETHODCALLTYPE BindBlob(int paramIndex, const char* blobValue, int blobLen) = 0; ///< �󶨲���(Blob
    virtual HRESULT     STDMETHODCALLTYPE BindNull(int paramIndex) = 0;                     ///< �󶨲���(NULL)
    virtual HRESULT     STDMETHODCALLTYPE BindZeroBlob(int paramIndex, int blobSize) = 0;   ///< ��ȫ0��blob

    /// ��ȡ��������
    /// ��ȡ��������
    virtual int         STDMETHODCALLTYPE GetParamCount() = 0;

    /// ���ݲ�������ȡ��������,���û���ҵ�,�᷵��-1
    virtual int         STDMETHODCALLTYPE GetParamIndex(LPCWSTR szParam) = 0;

    /// ����Ԥ�������,�Ա��ٴ�ִ��
    virtual void        STDMETHODCALLTYPE Reset() = 0;
};



/// ���ݿ����Ӷ���
class __declspec(uuid("DAD0CB8C-D2A8-4e1b-8C3D-54AC236172FD"))
ISQLiteComDatabase3: public IUnknown
{
public:

    /**
    * @brief    �Լ��ܷ�ʽ�����ݿ�
    * @param    pszFile         ���ݿ��ļ��ľ���·��
    * @param    pPassword       ����(����������)
    * @param    dwPasswordBytes �����(�ֽ���)
    */ 
    virtual HRESULT     STDMETHODCALLTYPE OpenWithKey(
        LPCWSTR pszFile,
        void*   pPassword,
        DWORD   dwPasswordBytes) = 0;

    /**
    * @brief    ����ͨ��ʽ�����ݿ�
    * @param    pszFile         ���ݿ��ļ��ľ���·��
    */ 
    virtual HRESULT     STDMETHODCALLTYPE Open(LPCWSTR pszFile) = 0;

    /// �ж����ݿ��Ƿ��Ǵ򿪵�״̬
    virtual BOOL        STDMETHODCALLTYPE IsOpen() throw() = 0;

    /// �ر����ݿ�
    virtual void        STDMETHODCALLTYPE Close() throw() = 0;

    /**
    * @brief    ����һ������,������Ƕ��
    * @param    transLock       ���������ʽ
    */ 
    virtual HRESULT     STDMETHODCALLTYPE BeginTransaction(BKDb::EM_TRANSLOCK transLock = BKDb::em_Deferred) = 0;

    /// �ύһ������,������Ƕ��
    virtual HRESULT     STDMETHODCALLTYPE CommitTransaction() = 0;

    /// �ع�һ������,������Ƕ��
    virtual HRESULT     STDMETHODCALLTYPE RollbackTransaction() throw() = 0;

    /// �ж��Ƿ����Զ��ύ״̬
    virtual BOOL        STDMETHODCALLTYPE GetAutoCommit() = 0;




    /**
    * @brief    ����һ�������
    * @param    lpszPointName   ����������������ջ��Ӧ����Ψһ��
    */ 
    virtual HRESULT     STDMETHODCALLTYPE CreateSavePoint(LPCWSTR lpszPointName) = 0;

    /**
    * @brief    �ͷ�(�ύ)һ�������
    * @param    lpszPointName   ����������������ջ��Ӧ����Ψһ��
    */ 
    virtual HRESULT     STDMETHODCALLTYPE ReleaseSavePoint(LPCWSTR lpszPointName) throw() = 0;

    /**
    * @brief    �ع�һ�������
    * @param    lpszPointName   ����������������ջ��Ӧ����Ψһ��
    */ 
    virtual HRESULT     STDMETHODCALLTYPE RollbackToSavePoint(LPCWSTR lpszPointName) = 0;




    /**
    * @brief    ����ͨ��ʽ�����ݿ�
    * @param    szTable     ����
    */ 
    virtual BOOL        STDMETHODCALLTYPE TableExists(LPCWSTR szTable) = 0;


    /**
    * @brief    ����Ԥ�������
    * @param    szSQL           sql���
    * @param    ppiStmt         ���ش�����Ԥ�������ӿ�
    */ 
    virtual HRESULT     STDMETHODCALLTYPE PrepareStatement(LPCWSTR szSQL, ISQLiteComStatement3** ppiStmt) = 0;

    /**
    * @brief    ִ��sql���
    * @param    szSQL           sql���
    * @param    pnRows          ����Ӱ�������Ŀ
    */ 
    virtual HRESULT     STDMETHODCALLTYPE ExecuteUpdate(LPCWSTR szSQL, int* pnRows = NULL) = 0;

    /**
    * @brief    ִ��sql��ѯ
    * @param    szSQL           sql���
    * @param    ppiResultSet    ���ز�ѯ�Ľ����
    */ 
    virtual HRESULT     STDMETHODCALLTYPE ExecuteQuery(LPCWSTR szSQL, ISQLiteComResultSet3** ppiResultSet) = 0;

    /**
    * @brief    ִ�б�����sql��ѯ(select count(*) from ...)
    * @param    szSQL           sql���
    */ 
    virtual int         STDMETHODCALLTYPE ExecuteScalar(LPCWSTR szSQL) = 0;


    /// �������������id
    virtual ULONGLONG   STDMETHODCALLTYPE LastRowId() = 0;

    /// �ж�����ִ�еĲ���
    virtual void        STDMETHODCALLTYPE Interrupt() = 0;

    /// ���ò�ѯ��ʱ��ʱ��
    virtual void        STDMETHODCALLTYPE SetBusyTimeout(int nMillisecs) = 0;

    /// ����sqlite�İ汾
    virtual LPCSTR      STDMETHODCALLTYPE SQLiteVersion() throw() = 0;

    /// ��ȡ������
    virtual int         STDMETHODCALLTYPE GetErrorCode() = 0;

    /// ��ȡ������Ϣ
    virtual LPCWSTR     STDMETHODCALLTYPE GetErrorMsg() = 0;
};

NS_SKYLARK_END

#define FN_BKDbInitialize       "BKDbInitialize"        ///< export BKDbInitialize
#define FN_BKDbUninitialize     "BKDbUninitialize"      ///< export BKDbUninitialize
#define FN_BKDbCreateObject     "BKDbCreateObject"      ///< export BKDbCreateObject


/**
* @brief    ��ʼ��BKDbģ��
* @param    dwFlag  ����,δʹ��
*/
EXTERN_C HRESULT WINAPI BKDbInitialize(Skylark::BKDB_PLATFORM_INIT* pInit);
/// typedef for BKCacheInitialize
typedef HRESULT (WINAPI *PFN_BKDbInitialize)(Skylark::BKDB_PLATFORM_INIT* pInit);



/**
* @brief    ����ʼ��BKDbģ��
* @remark   ���÷���ʼ��ǰ����ȷ����ģ�鵼�������ж��󶼱��ͷ�
*/
EXTERN_C HRESULT WINAPI BKDbUninitialize();
/// typedef for BKCacheUninitialize
typedef HRESULT (WINAPI *PFN_BKDbUninitialize)();



/// class Factory
EXTERN_C HRESULT WINAPI BKDbCreateObject(REFIID riid, void** ppvObj, DWORD dwBKEngVer = BKENG_CURRENT_VERSION);
/// typedef for BKDbCreateObject
typedef HRESULT (WINAPI *PFN_BKDbCreateObject)(REFIID riid, void** ppvObj, DWORD dwBKEngVer);

#endif//BKDB_H