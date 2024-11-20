#pragma once
#include <Vulfix/IVulFix.h>

#define _CODE_VULFIX_ 0x88
#define MAKE_LEAK_ERROR( code )		MAKE_HRESULT( 1, _CODE_VULFIX_, code )
#define MAKE_LEAK_STATUS( code )	MAKE_HRESULT( 0, _CODE_VULFIX_, code )

#define KERR_NONE					S_OK
#define KERR_GENERAL				MAKE_LEAK_ERROR( 0x01 )
#define KERR_LANG_NOT_SUPPORTED		MAKE_LEAK_ERROR( 0x02 ) // page not match 
#define KERR_OS_NOT_SUPPORTED		MAKE_LEAK_ERROR( 0x03 )
#define KERR_ADMIN_REQUIRED			MAKE_LEAK_ERROR( 0x04 ) 
#define KERR_LOAD_FILE				MAKE_LEAK_ERROR( 0x05 )
#define KERR_OUT_OF_MEMORY			MAKE_LEAK_ERROR( 0x06 )
#define KERR_WRITE_FILE				MAKE_LEAK_ERROR( 0x07 )
#define KERR_CANCELED				MAKE_LEAK_ERROR( 0x08 )

enum TSysLang{ 
	ESYSLang_Unknown = 0,
	ESYSLang_CN = 2052,
	ESYSLang_EN = 1033
};

enum TRepairDownStat
{
	ERDOWN_SUCCESS					= 1,	//
	ERDOWN_LOCAL_NOT_EXISTS			= 2,	// �ļ��Ѿ�����
	ERDOWN_CANNOT_REACH_OFFICIAL	= 4,	// �޷����ӹ���
	ERDOWN_MULTIDOWN_ERROR			= 8,	// ���߳�����ʧ��
	ERDOWN_MULTIDOWN_ERRORSIGN		= 16,	// ���߳����ص��ļ�sign ���ʧ��
	ERDOWN_ERRORSIGN				= 32,	// �ļ�sign ���ʧ��, ��Ϊ���߳����غ����԰�װ����
	ERDOWN_SINGLEDOWN				= 64,	// ���߳�����
	ERDOWN_MIRROR_USED				= 128,	// ʹ���˾�������
	ERDOWN_IMPORT_LOCAL				= 256,	// ���ص����ļ�
};

typedef CComAutoCriticalSection                     CObjLock;
typedef CComCritSecLock<CComAutoCriticalSection>    CObjGuard;


#define SAFE_DELETE(x) if(x){ delete x; x=NULL; }
#define SAFE_DELETE_ARRAY(x) if(x){delete []x;x=NULL;}

static BOOL __cdecl PROMPTMSG( LPCTSTR xxx, ... )
{
	CString	str;
	va_list arg_ptr; 
	va_start(arg_ptr, xxx); 
	str.FormatV( xxx, arg_ptr );
	va_end( arg_ptr );

	::MessageBox(NULL, str, NULL, MB_OK);
	return TRUE;
}

#ifdef _DEBUG
#define SHOWMSG PROMPTMSG 
#else
#define SHOWMSG ATLTRACE
#endif