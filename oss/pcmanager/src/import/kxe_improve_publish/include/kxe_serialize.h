//////////////////////////////////////////////////////////////////////
///		@file		kxe_serialize.h
///		@author		luopeng
///		@date		2008-9-23 09:07:58
///	
///		@brief		
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../kxeevent/kxeeventid_def.h"
#include "../kxebase/kxesubsystemid_def.h"
#include "../json/json.h"
#include "../DOMUtil/JSONUtil/KJSONDataAccess.h"
#include "../scom/scom/scomhelper.h"
#include "../loki/static_check.h"
#include <string>

_KAN_DOM_BEGIN

// UUID
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, UUID& value, bool bWrite)
{
	std::wstringstream ws;
	if (bWrite)
	{
		ws << value;
		return KXMLDataExchange(domCur, ws.str(), bWrite);
	}
	else
	{
		std::wstring strValue;
		int nRet = KXMLDataExchange(domCur, strValue, bWrite);
		if (nRet == 0)
		{
			ws.str(strValue);
			ws >> value;
		}
		return nRet;
	}
}

#if _MSC_VER > 1200
template<class _KDOMCursor, class T>
inline long KXMLDataExchange(_KDOMCursor& domCur, T& value, bool bWrite)
{
	STATIC_CHECK(0, TypeNotDefined_KJson);
	return 0;
}
#endif

_KAN_DOM_END

/**
 * @defgroup kxe_json_serialize_marco_group KXEngine Json Serialize Macro
 * @{
 */

/**
* @brief ��ʼ���彫enum���ݽṹ��Json��������֮��������л��뷴���л����м����� 
* @param[in] _enum ��Ҫ�����ö�����͵��м����ݽṹ�ṹ
*/
#define KXE_JSON_DDX_ENUM(_enum) \
	inline std::ostream& operator<<(std::ostream& os, const _enum& enumValue)\
	{\
		return os << (const int&)enumValue;\
	}\
	inline std::istream& operator>>(std::istream& is, _enum& enumValue)\
	{\
		return is >> (int&)enumValue;\
	}\
	KDX_ENUM_DEFINE(_enum)

template
<
	typename T
>
struct KxERequestT1Param
{
	int nCount;
	T param1;
};

template
<
	typename T1,
	typename T2
>
struct KxERequestT2Param
{
	int nCount;
	T1 param1;
	T2 param2;
};

#if _MSC_VER == 1200

#define KXE_JSON_REQUEST_PARAM_1(_class) \
	_KAN_DOM_BEGIN\
	template<typename _KDOMCursor>\
	inline long KXMLDataExchange(_KDOMCursor& _domCur, KxERequestT1Param<_class>& _obj, bool _bWrite)\
	{\
		int _nRetCode = -1;\
		KXE_JSON_DDX_MEMBER("param_count", nCount);\
		KXE_JSON_DDX_MEMBER("param_1", param1);\
		return 0;\
	}\
	_KAN_DOM_END

#define KXE_JSON_REQUEST_PARAM_2(_class1, _class2) \
	_KAN_DOM_BEGIN\
	template<typename _KDOMCursor>\
	inline long KXMLDataExchange(_KDOMCursor& _domCur, KxERequestT2Param<_class1, _class2>& _obj, bool _bWrite)\
	{\
		int _nRetCode = -1;\
		KXE_JSON_DDX_MEMBER("param_count", nCount);\
		KXE_JSON_DDX_MEMBER("param_1", param1);\
		KXE_JSON_DDX_MEMBER("param_2", param2);\
		return 0;\
	}\
	_KAN_DOM_END

#endif

#if _MSC_VER == 1200
#define KXE_JSON_DDX_BEGIN(_class) \
	KXE_JSON_REQUEST_PARAM_1(_class)\
	KDX_BEGIN(_class)
#else
/**
 * @brief ��ʼ���彫���ݽṹ��Json��������֮��������л��뷴���л����м����� 
 * @param[in] _class ��Ҫ������м����ݽṹ
 */
#define KXE_JSON_DDX_BEGIN(_class) KDX_BEGIN(_class)
#endif

/**
 * @brief ���彫���ݽṹ��Json��������֮��������л��뷴���л����м������е����ݳ�Ա 
 * @param[in] _name json�д洢��������
 * @param[in] _member json�д洢������
 */
#define KXE_JSON_DDX_MEMBER(_name, _member) KDX_OBJ_NM(_name, _member);

/**
 * @brief ���彫���ݽṹ��Json����֮��������л��뷴���л����м������е����ݳ�Ա,���û���ҵ�ֵ,����_Default��� 
 * @param[in] _name json�д洢��������
 * @param[in] _member json�д洢������
 * @param[in] _default �ڴ��������û��ָ����ֵʱ,ʹ��_default���
 */
#define KXE_JSON_DDX_MEMBER_DEFAULT(_name, _member, _default) KDX_OBJ_EX(_name, _member, _default);

/**
 * @brief �������彫���ݽṹ������֮��������л��뷴���л����м����� 
 */
#define KXE_JSON_DDX_END() KDX_END()

#include "kxe_serialize_data.h"

#if _MSC_VER == 1200

KXE_JSON_REQUEST_PARAM_1(long);
KXE_JSON_REQUEST_PARAM_1(short);
KXE_JSON_REQUEST_PARAM_1(int);
KXE_JSON_REQUEST_PARAM_1(char);
KXE_JSON_REQUEST_PARAM_1(unsigned long);
KXE_JSON_REQUEST_PARAM_1(unsigned short);
KXE_JSON_REQUEST_PARAM_1(unsigned int);
KXE_JSON_REQUEST_PARAM_1(unsigned char);
KXE_JSON_REQUEST_PARAM_1(std::string);
KXE_JSON_REQUEST_PARAM_1(std::wstring);
KXE_JSON_REQUEST_PARAM_1(UUID);


KXE_JSON_REQUEST_PARAM_2(std::wstring, std::wstring);
KXE_JSON_REQUEST_PARAM_2(unsigned int, std::wstring);
#endif

 /**
  * @}
  */
