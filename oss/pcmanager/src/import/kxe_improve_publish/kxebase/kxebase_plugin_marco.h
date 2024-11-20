//////////////////////////////////////////////////////////////////////
///		@file		kxebase_plugin_marco.h
///		@author		luopeng
///		@date		2008-8-29 09:07:58
///	
///		@brief		kxe_base��غ�������
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../common/kxe_thread.h"
#include "../loki/TypeManip.h"
#include "../loki/static_check.h"

#if !defined SDK_USER_DIRECT && !defined DEFINE_SYSTEM_SDK

#define KXEAPI typedef

/**
 * @brief ����������ϵͳ��ӵ��õ������ռ���
 * @param[in] system Ϊ�����ռ������
 * @remark KXE_DECLARE_SYSTEM_BEGIN(KxEScanSystem)����Ľ����ΪKxEScanSystem::
 */
#define KXE_DECLARE_SYSTEM_BEGIN(system) \
	namespace system{\
		__declspec(selectany) KxEThreadMutex mutex_##system;\
		inline const char* get_system_name()\
		{\
			return #system;\
		}\
		inline KxEThreadMutex& get_system_mutex()\
		{\
			return mutex_##system;\
		}
/**
 * @brief ����û�в����ĺ���
 * @param[in] function ����ĺ�����
 * @remark ����function�Ѿ�����Ϊ��ָ����ʽKXEAPI int __stdcall function()
*/
#define KXE_DECLARE_SYSTEM_SDK_0(function)\
	typedef int __stdcall type_##function(void);\
	__declspec(selectany) type_##function* g_prototype_##function = NULL;\
	inline int __stdcall function(void)\
	{\
		STATIC_CHECK((Loki::IsSameType<type_##function, ::function>::value), InvalidFunctionDefine);\
		if (g_prototype_##function == NULL)\
		{\
			KxEMutexGuard<KxEThreadMutex> guard(get_system_mutex());\
			int nRet = kxe_base_get_system_method(\
				get_system_name(),\
				#function,\
				(void**)&g_prototype_##function\
				);\
			if (nRet != 0)\
			{\
				return nRet;\
			}\
		}\
		return g_prototype_##function();\
	}


/**
 * @brief ����ֻ��һ�������ĺ���
 * @param[in] function ����ĺ�����
 * @param[in] arg_type_1 �����ĵ�һ������
 * @remark ����function�Ѿ�����Ϊ��ָ����ʽKXEAPI int __stdcall function(arg_typ_1 arg)
*/
#define KXE_DECLARE_SYSTEM_SDK_1(function, arg_type_1)\
	typedef int __stdcall type_##function(arg_type_1);\
	__declspec(selectany) type_##function* g_prototype_##function = NULL;\
	inline int __stdcall function(arg_type_1 arg1)\
	{\
		STATIC_CHECK((Loki::IsSameType<type_##function, ::function>::value), InvalidFunctionDefine);\
		if (g_prototype_##function == NULL)\
		{\
			KxEMutexGuard<KxEThreadMutex> guard(get_system_mutex());\
			int nRet = kxe_base_get_system_method(\
				get_system_name(),\
				#function,\
				(void**)&g_prototype_##function\
				);\
			if (nRet != 0)\
			{\
				return nRet;\
			}\
		}\
		return g_prototype_##function(arg1);\
	}

/**
* @brief ����ֻ�����������ĺ���
* @param[in] function ����ĺ�����
* @param[in] arg_type_1 �����ĵ�һ������
* @param[in] arg_type_2 �����ĵڶ�������
* @remark ����function�Ѿ�����Ϊ��ָ����ʽKXEAPI int __stdcall function(arg_typ_1 arg1, arg_type_2 arg2)
*/
#define KXE_DECLARE_SYSTEM_SDK_2(function, arg_type_1, arg_type_2)\
	typedef int __stdcall type_##function(arg_type_1, arg_type_2);\
	__declspec(selectany) type_##function* g_prototype_##function = NULL;\
	inline int __stdcall function(arg_type_1 arg1, arg_type_2 arg2)\
	{\
		STATIC_CHECK((Loki::IsSameType<type_##function, ::function>::value), InvalidFunctionDefine);\
		if (g_prototype_##function == NULL)\
		{\
			KxEMutexGuard<KxEThreadMutex> guard(get_system_mutex());\
			if (g_prototype_##function == NULL)\
			{\
				int nRet = kxe_base_get_system_method(\
					get_system_name(),\
					#function,\
					(void**)&g_prototype_##function\
					);\
				if (nRet != 0)\
				{\
					return nRet;\
				}\
			}\
		}\
		return g_prototype_##function(arg1, arg2);\
	}

/**
* @brief ����ֻ�����������ĺ���
* @param[in] function ����ĺ�����
* @param[in] arg_type_1 �����ĵ�һ������
* @param[in] arg_type_2 �����ĵڶ�������
* @param[in] arg_type_3 �����ĵ���������
* @remark ����function�Ѿ�����Ϊ��ָ����ʽKXEAPI int __stdcall function(arg_typ_1 arg1, arg_type_2 arg2, arg_type_3 arg3)
*/
#define KXE_DECLARE_SYSTEM_SDK_3(function, arg_type_1, arg_type_2, arg_type_3)\
	typedef int __stdcall type_##function(arg_type_1, arg_type_2, arg_type_3);\
	__declspec(selectany) type_##function* g_prototype_##function = NULL;\
	inline int __stdcall function(arg_type_1 arg1, arg_type_2 arg2, arg_type_3 arg3)\
	{\
		STATIC_CHECK((Loki::IsSameType<type_##function, ::function>::value), InvalidFunctionDefine);\
		if (g_prototype_##function == NULL)\
		{\
			KxEMutexGuard<KxEThreadMutex> guard(get_system_mutex());\
			if (g_prototype_##function == NULL)\
			{\
				int nRet = kxe_base_get_system_method(\
					get_system_name(),\
					#function,\
					(void**)&g_prototype_##function\
					);\
				if (nRet != 0)\
				{\
					return nRet;\
				}\
			}\
		}\
		return g_prototype_##function(arg1, arg2, arg3);\
	}

/**
* @brief ����ֻ���ĸ������ĺ���
* @param[in] function ����ĺ�����
* @param[in] arg_type_1 �����ĵ�һ������
* @param[in] arg_type_2 �����ĵڶ�������
* @param[in] arg_type_3 �����ĵ���������
* @param[in] arg_type_4 �����ĵ��ĸ�����
* @remark ����function�Ѿ�����Ϊ��ָ����ʽ
		KXEAPI int __stdcall function(arg_typ_1 arg1, arg_type_2 arg2, arg_type_3 arg3, arg_typ_4 arg4)
*/
#define KXE_DECLARE_SYSTEM_SDK_4(function, arg_type_1, arg_type_2, arg_type_3, arg_type_4)\
	typedef int __stdcall type_##function(arg_type_1, arg_type_2, arg_type_3, arg_type_4);\
	__declspec(selectany) type_##function* g_prototype_##function = NULL;\
	inline int __stdcall function(arg_type_1 arg1, arg_type_2 arg2, arg_type_3 arg3, arg_type_4 arg4)\
	{\
		STATIC_CHECK((Loki::IsSameType<type_##function, ::function>::value), InvalidFunctionDefine);\
		if (g_prototype_##function == NULL)\
		{\
			KxEMutexGuard<KxEThreadMutex> guard(get_system_mutex());\
			if (g_prototype_##function == NULL)\
			{\
				int nRet = kxe_base_get_system_method(\
					get_system_name(),\
					#function,\
					(void**)&g_prototype_##function\
					);\
				if (nRet != 0)\
				{\
					return nRet;\
				}\
			}\
		}\
		return g_prototype_##function(arg1, arg2, arg3, arg4);\
	}

/**
* @brief ����ֻ����������ĺ���
* @param[in] function ����ĺ�����
* @param[in] arg_type_1 �����ĵ�һ������
* @param[in] arg_type_2 �����ĵڶ�������
* @param[in] arg_type_3 �����ĵ���������
* @param[in] arg_type_4 �����ĵ��ĸ�����
* @param[in] arg_type_5 �����ĵ��ĸ�����
* @remark ����function�Ѿ�����Ϊ��ָ����ʽ
*       KXEAPI int __stdcall function(arg_typ_1 arg1, arg_type_2 arg2, arg_type_3 arg3, arg_typ_4 arg4, arg_typ_5 arg5)
*/
#define KXE_DECLARE_SYSTEM_SDK_5(function, arg_type_1, arg_type_2, arg_type_3, arg_type_4, arg_type_5)\
	typedef int __stdcall type_##function(arg_type_1, arg_type_2, arg_type_3, arg_type_4, arg_type_5);\
	__declspec(selectany) type_##function* g_prototype_##function = NULL;\
	inline int __stdcall function(arg_type_1 arg1, arg_type_2 arg2, arg_type_3 arg3, arg_type_4 arg4, arg_type_5 arg5)\
	{\
		STATIC_CHECK((Loki::IsSameType<type_##function, ::function>::value), InvalidFunctionDefine);\
		if (g_prototype_##function == NULL)\
		{\
			KxEMutexGuard<KxEThreadMutex> guard(get_system_mutex());\
			if (g_prototype_##function == NULL)\
			{\
				int nRet = kxe_base_get_system_method(\
					get_system_name(),\
					#function,\
					(void**)&g_prototype_##function\
					);\
				if (nRet != 0)\
				{\
					return nRet;\
				}\
			}\
		}\
		return g_prototype_##function(arg1, arg2, arg3, arg4, arg5);\
	}
/**
 * @brief ����������ϵͳ��ӵ��õ������ռ���غ�������
 */
#define KXE_DECLARE_SYSTEM_END() }

#elif defined SDK_USER_DIRECT

#define KXEAPI

#define KXE_DECLARE_SYSTEM_BEGIN(system) \
	namespace system{

#define KXE_DECLARE_SYSTEM_SDK_0(function, void)\
	inline int __stdcall function(void)\
	{\
	return ::function();\
	}

#define KXE_DECLARE_SYSTEM_SDK_1(function, arg_type_1)\
	inline int __stdcall function(arg_type_1 arg1)\
	{\
		return ::function(arg1);\
	}

#define KXE_DECLARE_SYSTEM_SDK_2(function, arg_type_1, arg_type_2)\
	inline int __stdcall function(arg_type_1 arg1, arg_type_2 arg2)\
	{\
	return ::function(arg1, arg2);\
	}

#define KXE_DECLARE_SYSTEM_SDK_3(function, arg_type_1, arg_type_2, arg_type_3)\
	inline int __stdcall function(arg_type_1 arg1, arg_type_2 arg2, arg_type_3 arg3)\
	{\
	return ::function(arg1, arg2, arg3);\
	}

#define KXE_DECLARE_SYSTEM_SDK_4(function, arg_type_1, arg_type_2, arg_type_3, arg_type_4)\
	inline int __stdcall function(arg_type_1 arg1, arg_type_2 arg2, arg_type_3 arg3, arg_type_4 arg4)\
	{\
	return ::function(arg1, arg2, arg3, arg4);\
	}

#define KXE_DECLARE_SYSTEM_SDK_5(function, arg_type_1, arg_type_2, arg_type_3, arg_type_4, arg_type_5)\
	inline int __stdcall function(arg_type_1 arg1, arg_type_2 arg2, arg_type_3 arg3, arg_type_4 arg4, arg_type_5 arg5)\
	{\
	return ::function(arg1, arg2, arg3, arg4, arg5);\
	}

#define KXE_DECLARE_SYSTEM_END() }

#else
#define KXEAPI

#define KXE_DECLARE_SYSTEM_BEGIN(system)

#define KXE_DECLARE_SYSTEM_SDK_0(function)

#define KXE_DECLARE_SYSTEM_SDK_1(function, arg_type_1)

#define KXE_DECLARE_SYSTEM_SDK_2(function, arg_type_1, arg_type_2)

#define KXE_DECLARE_SYSTEM_SDK_3(function, arg_type_1, arg_type_2, arg_type_3)

#define KXE_DECLARE_SYSTEM_SDK_4(function, arg_type_1, arg_type_2, arg_type_3, arg_type_4)

#define KXE_DECLARE_SYSTEM_SDK_5(function, arg_type_1, arg_type_2, arg_type_3, arg_type_4, arg_type_5)

#define KXE_DECLARE_SYSTEM_END() 

#endif

