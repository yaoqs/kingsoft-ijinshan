#pragma once
#include "bkxdx/bkxdx.h"
#include "bkxdx/bkxdx_cursor_bkjson.h"    // use bkjson implements
#include "bkxdx/bkxdx_exchange_c.h"       // support c type exchange
#include "bkxdx/bkxdx_exchange_atl.h"     // support ATL class exchange
#include "common_def.h"
#include "comdata_scan_def.h"

typedef struct  _BK_ECHO_RESULT
{
    DWORD   dwEchoStatus;                 //����0��Ϊ���ֳɹ�������������bkengdef.h�У��������ͷ�ļ�
    HRESULT hEchoCode;                    //���ֲ����Ĵ�����,��ѭHRESULT�淶    
    BOOL    bTrustProgram;                //������֤���ļ��Ƿ������
}BK_ECHO_RESULT, *PBK_ECHO_RESULT;

XDX_CLASS_BEGIN(BK_ECHO_RESULT)
    XDX_MEMBER(dwEchoStatus)
    XDX_MEMBER(hEchoCode)
    XDX_MEMBER(bTrustProgram)
XDX_CLASS_END

typedef struct  _BK_PLUGIN_INFO
{
    BOOL    bPlugineLog;
    CString strPath;
    CString strMD5;
}BK_PLUGIN_INFO, *PBK_BLUGIN_INFO;

XDX_CLASS_BEGIN(BK_PLUGIN_INFO)
    XDX_MEMBER(bPlugineLog)
    XDX_MEMBER(strPath)
    XDX_MEMBER(strMD5)
XDX_CLASS_END