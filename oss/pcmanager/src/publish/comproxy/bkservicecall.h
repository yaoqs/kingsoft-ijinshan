/************************************************************************
����Ҫ��
1. ��������bksafesvc.idl
2. �ڹ����������µ�filter������bksafesvc.idl���ɵ�.c�ļ�
3. ȥ��.c�ļ���Ԥ����ѡ��
4. filter����������: parse file : TRUE | SCC file : FASLE
5. �ڰ�����ͷ�ļ�֮ǰ������Ҫ����bksafesvc.idl���ɵ�.h�ļ�
6. ͬʱimport �ļ�����ȥ��.cpp�ļ���Ԥ����ѡ��
    http://192.168.1.234/svn/3rdlib/trunk/publish/miniutil/bkjson.cpp
    http://192.168.1.234/svn/3rdlib/trunk/publish/miniutil/bkjson.h
�Ƽ�idl�������£�
output
   output directory : ./_idl_gen
   header file      : bksafesvc.h
   IID file         : bksafesvc_i.c

Example:
#include "stdafx.h"
#include "_idl_gen/bksafesvc.h"
#include "bkservicecall.h"
************************************************************************/
#include "com_sc_interface.h"
#include "com_sc_xdx.h"

class CBkServiceCall
    : public IBkServiceCall
{
BKCOM_PROXY_DECLARE_MODULE_ID(CBkServiceCall)

BKCOM_PROXY_DECLARE_INIT()

public:
    virtual HRESULT Execute( 
        const CString& strExePath, 
        const CString& strCmdline, 
        BOOL bShow 
        )
    {
        BKCOM_PROXY_METHOD_IMPLEMENT_BEGIN(CBkServiceCall, Execute)
            BKCOM_PROXY_METHOD_XDX_STRUCT(Execute, CBkServiceCall) param;
            param.strExePath = strExePath;
            param.strCmdline = strCmdline;
            param.bShow = bShow;
            cursor.WriteData( param );
            try
            {
                bstrParams = cursor.m_doc.Dump().AllocSysString();
            }
            catch( ... )
            {
                bstrParams = NULL;
            }
        BKCOM_PROXY_METHOD_IMPLEMENT_NO_OUT_END
    }
};