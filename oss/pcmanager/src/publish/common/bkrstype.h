/** 
* @file bkrstype.h
* @brief ��̨��ɨ�Ŀ���ֲ�Ļ����������Ͷ���
* @author BAO<baoderong@kingsoft.com>
* @date October 30,2010
*
* @reference ��ͷ�ļ������ļ��������Ӷ��Ķ���
*/

#ifndef BKRESTYPE_H
#define BKRESTYPE_H

/*****************************************
* ISO C99��׼�������Ͷ���
*****************************************/
// ����������GCC��<stdint.h>�ж���
// stdint.h�ж�����_STDINT_H
#ifndef _STDINT_H
	// 8λ
	typedef signed char          int8_t;
	typedef unsigned char        uint8_t;

	// 16λ
	typedef short int            int16_t;
	typedef unsigned short int   uint16_t;

	// 32λ
	#ifdef _MSC_VER   // _MSC_VER��VCԤ�����
		typedef long                 int32_t;
		/**
		* @attention   DWORD��VC/Windows����unsigned long, ����Ӧ�ü���, ֻ���վ�
		**/
		typedef unsigned long        uint32_t;
	#else
		typedef int                  int32_t;
		typedef unsigned int         uint32_t;
	#endif  // _MSC_VER

	// 64λ
	#ifdef _MSC_VER   // _MSC_VER��VCԤ�����
		/**
		* @attention   VS2005��֧��long long, ��֮ǰ�İ汾��֧��
		**/
		typedef __int64              int64_t;
		typedef unsigned __int64     uint64_t;
	#elif defined(__GNUC__)   // __GNUC__��GCCԤ�����
		/**
		* @attention   sys/types.h������intXX_t, ��û�ж���uintXX_t
		*              ���һ����__WORDSIZE����int64_tΪlong int
		**/
		#ifdef __LP64__   // __LP64__��GCCԤ�����, ��ʱlong��64λ
			#ifndef _SYS_TYPES_H    // sys/types.h�ж�����_SYS_TYPES_H
				typedef long         int64_t;
			#endif
			typedef unsigned long    uint64_t;
		#else
			#ifndef _SYS_TYPES_H    // sys/types.h�ж�����_SYS_TYPES_H
				typedef long long    int64_t;
			#endif
			typedef unsigned long long   uint64_t;
		#endif
	#endif  // _MSC_VER/__GNUC__

	// ��ָ�볤����ͬ����������, ����ָ���������໥ת��
	/**
	* @attention   VS2005��CRT���Ѿ�����intprt_t
	**/
	// _WIN64��VCԤ�����, __LP64__��GCCԤ�����
	#if defined(_WIN64) || defined(__LP64__)   // 64λƽ̨
		#ifndef _INTPTR_T_DEFINED   // VS2005��CRT�ж���intprt_tʱ����˺�
			typedef int64_t              intptr_t;
			#define _INTPTR_T_DEFINED
		#endif
		#ifndef _UINTPTR_T_DEFINED   // VS2005��CRT�ж���uintprt_tʱ����˺�
			typedef uint64_t             uintptr_t;
			#define _UINTPTR_T_DEFINED
		#endif
	#else   // 32λƽ̨
		#ifndef _INTPTR_T_DEFINED   // VS2005��CRT�ж���intprt_tʱ����˺�
			typedef int32_t              intptr_t;
			#define _INTPTR_T_DEFINED
		#endif
		#ifndef _UINTPTR_T_DEFINED   // VS2005��CRT�ж���uintprt_tʱ����˺�
			typedef uint32_t             uintptr_t;
			#define _UINTPTR_T_DEFINED
		#endif
	#endif  // defined(_WIN64) || defined(__LP64__)

#endif  // !_STDINT_H


/*****************************************
* ����Windows�����
*****************************************/
// ����������VC��<windef.h>��<wtype.h>�ж���
// windef.h������_WINDEF_, wtype.h�ж�����__wtypes_h__
#if !(defined(_WINDEF_) || defined(__wtypes_h__))
	#ifndef NULL
		#ifdef __cplusplus
			#define NULL   0
		#else
			#define NULL   ((void *)0)
		#endif
	#endif

	typedef int32_t   BOOL;

	#ifndef FALSE
		#define FALSE   0
	#endif

	#ifndef TRUE
		#define TRUE    1
	#endif

	// ���¶�����ܻ��õ�, ��������ʹ��
	typedef uint8_t     BYTE;
	typedef uint16_t    WORD;
	typedef uint32_t    DWORD;
	typedef uint8_t*    PBYTE;
	typedef uint16_t*   PWORD;
	typedef uint32_t*   PDWORD;

	#ifndef IN
		#define IN
	#endif

	#ifndef OUT
		#define OUT
	#endif

	// IUnknownҪ��AddRef��Release�ķ���ֵ������ULONG, ��LP64��û��Ҫ��64λ��long
	// __LP64__��GCCԤ��������
	#ifdef __LP64__
		typedef unsigned int  ULONG;
	#else
		typedef unsigned long ULONG;
	#endif  // __LP64__
#endif  // !(_WINDEF_ || __wtypes_h__)

// ����������VC��<winnt.h>�ж���
// winnt.h������_WINNT_
#ifndef _WINNT_
	typedef int32_t    HRESULT;

	// ���¶�����ܻ��õ�, ��������ʹ��
	typedef uint16_t   WCHAR;
	typedef void*      HANDLE;
	typedef void*      PVOID;
#endif  // !_WINNT_


/// �ļ����ַ�������, ��Windowsƽ̨����Unicode, ����ƽ̨��ANSI
// _WIN32��_WIN64��VCԤ��������
#if defined(_WIN32) || defined(_WIN64)
	typedef uint16_t KCHAR;
#else
	typedef uint8_t KCHAR;
#endif  // _WIN32 || _WIN64


/// ʹ�ú��ͷ�ʱ��Ҫ���⴦���ָ��
typedef void*      KHANDLE;


/*****************************************
* ��������
*****************************************/

#ifndef ASSERT
	#define ASSERT assert
#endif

#ifndef KAE_MAX
	#define KAE_MAX(a,b)   (((a) > (b)) ? (a) : (b))
#endif

#ifndef KAE_MIN
	#define KAE_MIN(a,b)   (((a) < (b)) ? (a) : (b))
#endif

#endif
