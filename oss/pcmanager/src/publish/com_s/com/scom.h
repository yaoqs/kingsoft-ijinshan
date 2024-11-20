///////////////////////////////////////////////////////////////
//
//	Filename: 	KISCom.h
//	Creator:	lichenglin  <lichenglin@kingsoft.net>
//	Date:		2007-8-26   15:45
//	Comment:	
/*

        ����ͷ�ļ���������ʵ�ּ򵥵������
		һ����3������Ҫ���ĵĺ�:


		(1) KAS_BEGIN_COM_MAP( CXXX )
				KAS_COM_INTERFACE_ENTRY( IXXX ) �� KAS_COM_INTERFACE_ENTRY_IID( IXXX )
		    KAS_END_COM_MAP()

			����ʵ��IUnknown:
			�������Ҫ���뵽��ʵ�ֽӿڵ�������, ����ʵ��IUnknown��3���麯��,
			��:


			����ӿ���������:
				struct __declspec( uuid( "7CCB588B-6746-47f4-9509-DDF3A4637A63" ) )
				ICompute: public IUnknown
				{
				public:
					virtual int __stdcall Add( int a, int b ) = 0;
					virtual int __stdcall Sub( int a, int b ) = 0;
				};


            ���ʵ��: (ֻ��Ҫʵ����Ҫ�Ľӿ�, �ټ�������, ����ʵ��IUnknown)
				class KCompute : public ICompute
				{
				public:
					virtual int __stdcall Add( int a, int b )
					{
						return a + b;
					}

					virtual int __stdcall Sub( int a, int b )
					{
						return a - b;
					}

					KAS_BEGIN_COM_MAP( KCompute )
						KAS_COM_INTERFACE_ENTRY( ICompute )
					KAS_END_COM_MAP()
				};



		(2) KAS_BEGIN_OBJECT_MAP()
				KAS_OBJECT_ENTRY( IXXX, CXXX )
			KAS_END_OBJECT_MAP()
			
			DllGetClassObject��ʵ��
		    ���ǵļ�COM�淶��ʹ��CLSID, ��ʹ���೧, ֻ��Ҫͨ��һ���ӿ�ID��DLL�д���
			��ʵ��, ���ӿ�ID���䴴����ʵ���Ķ�Ӧ��ϵ��Ҫ�������ָ��:
			��: 
				KAS_BEGIN_OBJECT_MAP()
					KAS_OBJECT_ENTRY( ICompute, KCompute )
				KAS_END_OBJECT_MAP()



		(3) USE_DEFAULT_COM_PROC  �� USE_DEFAULT_COM_PROCEX
		   
			ǰ��ʵ���� DllCanUnloadNow �� DllGetClassObject, 
			����ʵ���� DllCanUnloadNow �� DllGetClassObject �� DllMain
			ʡȥ���ֹ�д��д����.

			��Ҳ���Բ�ʹ����������, �Լ�ʵ����������
		    
			���, ��Ҫ����д.def�ļ�  : )
			    LIBRARY      "xxxmodule"
				EXPORTS
					DllGetClassObject				PRIVATE
					DllCanUnloadNow					PRIVATE


*/
//
///////////////////////////////////////////////////////////////

#ifndef _KASCom_h_
#define _KASCom_h_
#include <Unknwn.h>
#include "dllmodule.h"
#include "getclassobject.h"





#define USE_DEFAULT_COM_PROC  KDllModule _ComDllModule; \
	STDAPI  DllCanUnloadNow(void){  \
		return _ComDllModule.DllCanUnloadNow();}  \
	STDAPI  DllGetClassObject(IN REFCLSID rclsid, IN REFIID riid, OUT LPVOID FAR* ppv){  \
		return _ComDllModule.DllGetClassObject( rclsid, riid, ppv );}


#define USE_DEFAULT_COM_PROCEX    USE_DEFAULT_COM_PROC \
	BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){ \
		if( ul_reason_for_call == DLL_PROCESS_ATTACH ) _ComDllModule.Init( hModule ); \
		return TRUE; }



#endif // _KASCom_h_