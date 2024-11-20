/********************************************************************
* CreatedOn: 2006-12-11   20:29
* FileName:  KJSONDocImp.h
* CreatedBy: zhangrui <zhangrui@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/

#ifndef __KJSONDocImp_H_
#define __KJSONDocImp_H_


#include "KJSONDoc.h"
#include "../KMPCommon/KConv.h"

#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>


_KAN_DOM_BEGIN


inline KJSONDoc::KJSONDoc(): m_bInitFlag(false)
{
}

inline KJSONDoc::~KJSONDoc()
{
}

//////////////////////////////////////////////////////////////////////////
// i/o operations
inline long KJSONDoc::LoadFile(const TKChar* pcszFileName)
{
    assert(pcszFileName);

    ClearDoc();
    
#if _MSC_VER >= 1400
	AutoFile spFile = NULL;	
	errno_t err = _tfopen_s(&spFile, pcszFileName, KTEXT("rb"));
	if (err != 0)
    {
        return E_KJSON_FAIL_TO_LOAD_FILE;
    }
#else
	AutoFile spFile = _tfopen(pcszFileName, KTEXT("rb"));	
	if (spFile == NULL)
	{
		return E_KJSON_FAIL_TO_LOAD_FILE;
	}
#endif
    


    //
    // ��ȡ�ļ�����
    //
    int nRetCode = fseek(spFile, 0, SEEK_END);
    if (nRetCode != 0)
    {
        return E_KJSON_FAIL_TO_LOAD_FILE;
    }

    long lOffSet = ftell(spFile);
    if (lOffSet <= 0)
    {
        return E_KJSON_FAIL_TO_LOAD_FILE;
    }

    nRetCode = fseek(spFile, 0, SEEK_SET);
    if (nRetCode != 0)
    {
        return E_KJSON_FAIL_TO_LOAD_FILE;
    }


    //
    // ��ȡ�ļ���������
    //
    std::vector<char> vecBuf;
    vecBuf.resize(lOffSet + 1);

    size_t nSize = fread(&vecBuf[0], lOffSet, 1, spFile);
    if (nSize != 1)
    {
        return E_KJSON_FAIL_TO_LOAD_FILE;
    }

    vecBuf.back() = '\0';


    //
    // ����JSON��ʽ�����ļ�����
    //

    bool bRetCode = Json::Reader().parse(
        &vecBuf[0],
        &vecBuf[0] + vecBuf.size(),
        m_superRoot
    );
    if (!bRetCode)
    {
        return E_KJSON_FAIL_TO_LOAD_FILE;
    }

    m_bInitFlag = true;

    return S_OK;
}

inline long KJSONDoc::LoadJSON(const char* pcszJSON)
{
    assert(pcszJSON);

    ClearDoc();

    bool bRetCode = Json::Reader().parse(pcszJSON, m_superRoot);
    if (!bRetCode)
    {
        return E_KJSON_FAIL_TO_LOAD_TEXT;
    }

    m_bInitFlag = true;

    return S_OK;
}

inline long KJSONDoc::LoadJSONRootName(const char* pcszJSONRootName)
{
    assert(pcszJSONRootName);

    ClearDoc();

    m_superRoot = Json::Value(Json::nullValue);

    m_superRoot[pcszJSONRootName] = Json::Value(Json::nullValue);

    m_bInitFlag = true;

    return S_OK;
}

inline long KJSONDoc::SaveFile(const TKChar* pcszFileName)
{
    assert(m_bInitFlag);
    assert(pcszFileName);

#if _MSC_VER >= 1400
	AutoFile spFile = NULL;
	errno_t err = _tfopen_s(&spFile, pcszFileName, KTEXT("wb"));
    if (err != 0)
    {
        return E_KJSON_FAIL_TO_SAVE_FILE;
    }
#else
	AutoFile spFile = _tfopen(pcszFileName, KTEXT("wb"));
    if (spFile == NULL)
    {
        return E_KJSON_FAIL_TO_SAVE_FILE;
    }
#endif

    std::string strJSON = Json::StyledWriter().write(m_superRoot);

    size_t nSize = fwrite(
        strJSON.c_str(),
        max(0, (strJSON.size() - 1)),
        1,
        spFile
    );
    if (nSize != 1)
    {
        return E_KJSON_FAIL_TO_SAVE_FILE;
    }


    return S_OK;
}

inline long KJSONDoc::ToJSONString(std::string* pstrRet)
{
    assert(m_bInitFlag);
    assert(pstrRet);

    *pstrRet = Json::StyledWriter().write(m_superRoot);

    return S_OK;
}

inline long KJSONDoc::ToCompactJSONString(std::string* pstrRet)
{
    assert(m_bInitFlag);
    assert(pstrRet);

    *pstrRet = Json::FastWriter().write(m_superRoot);

    return S_OK;
}

inline void KJSONDoc::ClearDoc()
{
    m_superRoot = Json::Value(Json::nullValue);

    m_bInitFlag = false;
}

















//////////////////////////////////////////////////////////////////////////
// structure operations
inline long KJSONDoc::PhrasePath(
    const char* pcszPath,
    std::vector<std::string>& pathItemList
)
{
    assert(m_bInitFlag);
    assert(pcszPath);
    return KDOMPhrasePath(pcszPath, pathItemList);
}

inline KJSONHandle KJSONDoc::OpenItemPath(const char* pcszPath, bool bCreateIfNotExist)
{
    assert(m_bInitFlag);
    assert(pcszPath);

    std::vector<std::string> pathItemList;

    int nRet = PhrasePath(pcszPath, pathItemList);
    if (nRet < 0)
    {
        return NULL;
    }

    KJSONHandle hParent = RootHandle();
    KJSONHandle hChild;
    for (size_t i = 0; i < pathItemList.size(); ++i)
    {
        hChild = OpenChild(hParent, pathItemList[i].c_str(), bCreateIfNotExist);
        if (!hChild.ValuePtr())
        {
            return NULL;
        }

        hParent = hChild;
    }

    return hChild;
}

inline KJSONHandle KJSONDoc::OpenChild(
    KJSONHandle hParent,
    const char* pcszName,
    bool        bCreateIfNotExist
)
{
    assert(m_bInitFlag);
    assert(pcszName);

    if (!hParent.ValuePtr())
    {
        return NULL;
    }

    // only object or 'null' object can have child
    if (!hParent.ValueRef().isObject())
    {
        return NULL;
    }

    if (!bCreateIfNotExist)
    {   // ���bCreateIfNotExistΪfalse,��ô���뱣֤������null���󱻴�������
        if (!hParent.ValueRef().isMember(pcszName))
        {
            return NULL;
        }
    }

    return &(hParent.ValueRef()[pcszName]);
}
//
//inline KJSONHandle KJSONDoc::OpenArray(KJSONHandle hParent, bool bCreateIfNotExist)
//{
//    assert(m_bInitFlag);
//
//    if (!hParent.ValuePtr())
//    {
//        return NULL;
//    }
//
//    // hParent is array or 'null'
//    if (!hParent.ValueRef().isArray())
//    {
//        return NULL;
//    }
//
//    // û��isNull����,����ֻ���� isArray() && isObject() ����
//    if (hParent.ValueRef().isArray() && hParent.ValueRef().isObject() && bCreateIfNotExist)
//    {   // ����ǿ�����,��Ҫ����һ�����������
//        hParent.ValueRef().resize(0);
//    }
//
//    return hParent;
//}

inline KJSONHandle KJSONDoc::OpenArrayElement(
    KJSONHandle hParent,
    size_t      nIndex,
    bool        bCreateIfNotExist
)
{
    assert(m_bInitFlag);

    if (!hParent.ValuePtr())
    {
        return NULL;
    }

    // hParent is array or 'null'
    if (!hParent.ValueRef().isArray())
    {
        return NULL;
    }

    if (!hParent.ValueRef().isValidIndex(static_cast<Json::Value::UInt>(nIndex)) &&
        !bCreateIfNotExist)
    {
        return NULL;
    }

    return &(hParent.ValueRef()[static_cast<Json::Value::UInt>(nIndex)]);
}

//inline KJSONHandle KJSONDoc::AppendArrayElement(KJSONHandle hParent)
//{
//    if (!hParent.ValuePtr())
//    {
//        return NULL;
//    }
//
//    // hParent is array or 'null'
//    if (!hParent.ValueRef().isArray())
//    {
//        return NULL;
//    }
//
//    return &(hParent.ValueRef().append(Json::Value(Json::nullValue)));
//}

//inline size_t KJSONDoc::GetArraySize(KJSONHandle hParent)
//{
//    if (!hParent.ValuePtr())
//    {
//        return S_OK;
//    }
//
//    // hParent is array or 'null'
//    if (!hParent.ValueRef().isArray())
//    {
//        return S_OK;
//    }
//
//    return hParent.ValueRef().size();
//}


inline long KJSONDoc::EraseAllChildren(KJSONHandle hParent)
{
    assert(m_bInitFlag);

    if (!hParent.ValuePtr())
    {
        return E_KJSON_PARENT_NODE_IS_NULL;
    }

    if (hParent.ValueRef().isArray())
    {
        hParent.ValueRef() = Json::Value(Json::arrayValue);
    }
    else
    {
        hParent.ValueRef() = Json::Value(Json::nullValue);
    }

    return S_OK;
}

inline long KJSONDoc::RemoveChildren(KJSONHandle hParent, const char* pcszName)
{
    assert(m_bInitFlag);

    if (!hParent.ValuePtr())
    {
        return E_KJSON_PARENT_NODE_IS_NULL;
    }

    if (hParent.ValueRef().isObject())
    {
        hParent.ValueRef().removeMember(pcszName);
    }

    return S_OK;
}

inline long KJSONDoc::GetRootName(std::string& strRootName)
{
    assert(m_bInitFlag);

    // m_superRoot�����ҽ����ص�һ���ӽ����Ϊ�߼��ĸ����
    Json::Value::Members members = m_superRoot.getMemberNames();

    if (members.empty())
    {
        return E_KJSON_ROOT_NODE_IS_NULL;
    }

    strRootName = members.front();
    return S_OK;
}

inline KJSONHandle KJSONDoc::RootHandle()
{
    assert(m_bInitFlag);

    // m_superRoot�����ҽ����ص�һ���ӽ����Ϊ�߼��ĸ����
    Json::Value::Members members = m_superRoot.getMemberNames();

    if (members.empty())
    {
        return NULL;
    }

    return &m_superRoot[members.front().c_str()];
}












// 
// 
// //////////////////////////////////////////////////////////////////////////
// // data operations
// template<class T>
// inline long KJSONDoc::SetValue(KJSONHandle hJSONCursor, const T& value)
// {
//     assert(m_bInitFlag);
// 
//     return _SetJSONItem(hJSONCursor, value);
// }
// 
// template<class T>
// inline long KJSONDoc::GetValue(KJSONHandle hJSONCursor, T& value)
// {
//     assert(m_bInitFlag);
// 
//     if (!hJSONCursor.ValueRef().isString())
//     {
//         return E_KJSON_EXPECT_STRING_TYPE;
//     }
// 
// 
//     return _GetJSONItem(hJSONCursor, value);
// }
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// template<class T>
// inline long KJSONDoc::_SetJSONItem(KJSONHandle hJSONCursor, const T& value)
// {
//     assert(m_bInitFlag);
// 
//     std::ostringstream os;
//     os << value;
//     if (os.fail())
//     {
//         return E_KJSON_VALUE_STREAM_ERROR;
//     }
// 
//     hJSONCursor.ValueRef() = os.str();
// 
//     return S_OK;
// }
// 
// template<class T>
// inline long KJSONDoc::_GetJSONItem(KJSONHandle hJSONCursor, T& value)
// {
//     assert(m_bInitFlag);
// 
//     // ��KJSONDoc::GetValue������string������
//     assert(hJSONCursor.ValueRef().isString());
// 
//     std::istringstream is;
//     is.str(hJSONCursor.ValueRef().asString());
//     is >> value;
//     if (is.fail())
//     {
//         return E_KJSON_VALUE_STREAM_ERROR;
//     }
// 
// 
//     return S_OK;
// }
// 
// 
// 
// 
// 
// template <class _Traits, class _Alloc>
// inline long KJSONDoc::_SetJSONItem(
//     KJSONHandle hJSONCursor,
//     const std::basic_string<char, _Traits, _Alloc>& strValue
// )
// {
//     assert(m_bInitFlag);
// 
//     hJSONCursor.ValueRef() = strValue.c_str();
// 
//     return S_OK;
// }
// 
// template <class _Traits, class _Alloc>
// inline long KJSONDoc::_GetJSONItem(
//     KJSONHandle hJSONCursor,
//     std::basic_string<char, _Traits, _Alloc>& strValue
// )
// {
//     assert(m_bInitFlag);
// 
//     // ��KJSONDoc::GetValue������string������
//     assert(hJSONCursor.ValueRef().isString());
// 
//     strValue = hJSONCursor.ValueRef().asCString();
// 
//     return S_OK;
// }
// 
// 
// 
// 
// template <class _Traits, class _Alloc>
// inline long KJSONDoc::_SetJSONItem(
//     KJSONHandle hJSONCursor,
//     const std::basic_string<wchar_t, _Traits, _Alloc>& wstrValue
// )
// {
//     assert(m_bInitFlag);
// 
//     hJSONCursor.ValueRef() = (const char*)KSCE::KU16ToU8(wstrValue.c_str());
// 
//     return S_OK;
// }
// 
// template <class _Traits, class _Alloc>
// inline long KJSONDoc::_GetJSONItem(
//     KJSONHandle hJSONCursor,
//     std::basic_string<wchar_t, _Traits, _Alloc>& wstrValue
// )
// {
//     assert(m_bInitFlag);
// 
//     // ��KJSONDoc::GetValue������string������
//     assert(hJSONCursor.ValueRef().isString());
// 
//     wstrValue = (const wchar_t*)KSCE::KU8ToU16(hJSONCursor.ValueRef().asString().c_str());
// 
//     return S_OK;
// }


inline long KJSONDoc::_SetJSONItem(KJSONHandle hJSONCursor, wchar_t wcValue)
{
	/**
	 * ������δ��뱻�滻��ԭ��
	 * �� vc6 �£����� wchar_t �����ڽ����������ͣ����ǵ�ͬ�� unsigned short,
	 * ��ˣ������л� unsigned short ���͵Ĳ���ʱ������ִ������ģ�庯���汾��
	 *		template<class T>
	 *		long _GetJSONItem(KJSONHandle hJSONCursor, T& value)
	 * ����ִ�е��˺�����������˽����������л���
	 * ���ԣ�ʹ�ú��沿�ֵ��滻���롣�� vc6 �汾�У�
	 * �滻���������л� unsigned short ���͵Ĳ���ʱ������ʽ��ǰ��ģ�庯���汾��
	 * �Ĵ���ʽ��ͬ������ܹ���ȷ�����л���
	 */

    /*assert(m_bInitFlag);

    wchar_t pcszValue[] = {wcValue, L'\0'};

    hJSONCursor.ValueRef() = (const char*)KSCE::KU16ToU8(pcszValue);

    return S_OK;*/

	assert(m_bInitFlag);

	std::ostringstream os;
	os << (unsigned short int)wcValue;	// ע�⣺ǿ��ת���� unsigned short ������Ϊ�˼��� vc6��wchar_t�����ڽ����ͣ�
	if (os.fail())
	{
		return E_KJSON_VALUE_STREAM_ERROR;
	}

	hJSONCursor.ValueRef() = os.str();

	return S_OK;
}

inline long KJSONDoc::_GetJSONItem(KJSONHandle hJSONCursor, wchar_t& wcValue)
{
    assert(m_bInitFlag);

    // ��KJSONDoc::GetValue������string������
    assert(hJSONCursor.ValueRef().isString());

	/**
	 * ������δ��뱻�滻��ԭ��
	 * �� vc6 �£����� wchar_t �����ڽ����������ͣ����ǵ�ͬ�� unsigned short,
	 * ��ˣ������л� unsigned short ���͵Ĳ���ʱ������ִ������ģ�庯���汾��
	 *		template<class T>
	 *		long _GetJSONItem(KJSONHandle hJSONCursor, T& value)
	 * ����ִ�е��˺�����������˽����������л���
	 * ���ԣ�ʹ�ú��沿�ֵ��滻���롣�� vc6 �汾�У�
	 * �滻���������л� unsigned short ���͵Ĳ���ʱ������ʽ��ǰ��ģ�庯���汾��
	 * �Ĵ���ʽ��ͬ������ܹ���ȷ�����л���
	 */

    /*KSCE::KU8ToU16 conv(hJSONCursor.ValueRef().asString().c_str());

    if (conv.CharCount() < 2)
    {
        return E_KJSON_VALUE_STREAM_ERROR;
    }

    wcValue = conv[0];*/

	std::istringstream is;
	unsigned short int uTemp = 0;
	is.str(hJSONCursor.ValueRef().asString());
	is >> uTemp;	// ע�⣺ǿ��ת���� unsigned short ������Ϊ�˼��� vc6��wchar_t�����ڽ����ͣ�
	if (is.fail())
	{
		return E_KJSON_VALUE_STREAM_ERROR;
	}

	wcValue = (wchar_t)uTemp;
    return S_OK;
}


inline long KJSONDoc::_SetJSONItem(KJSONHandle hJSONCursor, const wchar_t* pwszValue)
{
    assert(m_bInitFlag);

    assert(pwszValue);

    hJSONCursor.ValueRef() = (const char*)KSCE::KU16ToU8(pwszValue);

    return S_OK;
}

_KAN_DOM_END


#endif//__KJSONDocImp_H_
