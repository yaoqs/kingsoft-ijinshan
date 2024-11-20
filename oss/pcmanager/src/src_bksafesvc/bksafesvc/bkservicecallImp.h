#pragma once
#include "comproxy/com_sc_interface.h"
#include "com_svc_dispatch.h"
#include "comproxy/com_sc_xdx.h"

class CBkServiceCallImp
    : public    CBkComRoot,
      public    IBkServiceCall
{
public:
    CBkServiceCallImp(void);
    ~CBkServiceCallImp(void);
public:
    HRESULT Initialize( DWORD dwProcId, int nVersion );

    HRESULT Uninitialize();

    COM_METHOD_DISPATCH_BEGIN()
        COM_METHOD_DISPATCH_IN_ARG_3_NO_OUT( CBkServiceCall, Execute, strExePath, strCmdline, bShow )
    COM_METHOD_DISPATCH_END
public:
    virtual HRESULT Execute( 
        const CString& strExePath, 
        const CString& strCmdline, 
        BOOL bShow
        );
private:
    // ����TRUE��ʾ������֤ͨ��
    BOOL    VerifyProcess( DWORD dwProcId );
    // ����TRUE��ʾ·����֤ͨ��
    BOOL    VerifyExePath( LPCWSTR lpwszExePath );
    // ����TRUE��ʾǩ����֤ͨ��
    BOOL    VerifyFileSign( LPCWSTR lpwszExePath );
private:
    HANDLE  m_hToken;
};
