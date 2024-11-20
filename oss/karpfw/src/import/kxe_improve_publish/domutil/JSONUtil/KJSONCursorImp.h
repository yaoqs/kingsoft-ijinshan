/********************************************************************
* CreatedOn: 2006-12-12   10:47
* FileName:  KJSONCursorImp.h
* CreatedBy: zhangrui <zhangrui@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/

#ifndef __KJSONCursorImp_H_
#define __KJSONCursorImp_H_


#include "KJSONCursor.h"
#include "../KMPCommon/KConv.h"

_KAN_DOM_BEGIN

inline KJSONCursor::KJSONCursor(): m_bInitFlag(false)
{
    //_InitCursor();
}

inline KJSONCursor::~KJSONCursor()
{
}


inline long KJSONCursor::LoadFile(const TKChar* pcszFileName)
{
    assert(pcszFileName);

    _ClearCursor();

    long lRet = m_jsonDoc.LoadFile(pcszFileName);
    if (FAILED(lRet))
    {
        return lRet;
    }

    lRet = _InitCursor();
    if (FAILED(lRet))
    {
        return lRet;
    }

    return S_OK;
}

inline long KJSONCursor::LoadString(const char* pcszInput)
{
    assert(pcszInput);

    _ClearCursor();

    long lRet = m_jsonDoc.LoadJSON(pcszInput);
    if (FAILED(lRet))
    {
        return lRet;
    }

    lRet = _InitCursor();
    if (FAILED(lRet))
    {
        return lRet;
    }

    return S_OK;
}

inline long KJSONCursor::LoadDOMName(const char* pcszName)
{
    assert(pcszName);

    _ClearCursor();

    long lRet = m_jsonDoc.LoadJSONRootName(pcszName);
    if (FAILED(lRet))
    {
        return lRet;
    }

    lRet = _InitCursor();
    if (FAILED(lRet))
    {
        return lRet;
    }

    return S_OK;
}

inline long KJSONCursor::SaveFile(const TKChar* pcszFileName)
{
    assert(m_bInitFlag);
    assert(pcszFileName);
    return m_jsonDoc.SaveFile(pcszFileName);
}

inline long KJSONCursor::ToString(std::string* pstrOutput)
{
    assert(m_bInitFlag);
    assert(pstrOutput);
    return m_jsonDoc.ToJSONString(pstrOutput);
}

inline long KJSONCursor::ToCompactString(std::string* pstrRet)
{
    assert(m_bInitFlag);
    assert(pstrRet);
    return m_jsonDoc.ToCompactJSONString(pstrRet);
}

template<class _KOtherDOMCursor>
inline long KJSONCursor::ToOtherDOM(_KOtherDOMCursor& otherDOMCursor)
{
    assert(m_bInitFlag);

    // �����Ը���
    if ((void*)this == (void*)&otherDOMCursor)
        return S_OK;

    std::string strExchangeValue;
    std::string strObjName;

    long lRet = GetObjName(strObjName);
    if (FAILED(lRet))
    {
        return lRet;
    }

    lRet = otherDOMCursor.LoadDOMName(strObjName.c_str());
    if (FAILED(lRet))
    {
        return lRet;
    }

    PrepareForRead();
    otherDOMCursor.PrepareForWrite();

    return CopyNodeTo(otherDOMCursor);
}



//inline long KJSONCursor::GetLastInternalError()
//{
//    long lRet = m_lLastInternalError;
//
//    m_lLastInternalError = S_OK;
//
//    return lRet;
//}


inline void KJSONCursor::DumpPath()
{
    m_pathDump.clear();

    for (size_t i = 0; i < m_scopeStack.size(); ++i)
    {
        m_pathDump.push_back(m_scopeStack[i].m_strObjName);

        if (m_scopeStack[i].m_hObj.ValuePtr() == NULL)
        {   // �ҵ������λ��,��������һ��������null����
            break;
        }
    }
}

inline void KJSONCursor::PopPathDump(std::vector<std::string>& pathInfo)
{
    pathInfo.swap(m_pathDump);
}













inline long KJSONCursor::PhrasePath(
    const char* pcszPath,
    std::vector<std::string>& pathItemList
)
{
    assert(m_bInitFlag);
    assert(pcszPath);
    return m_jsonDoc.PhrasePath(pcszPath, pathItemList);
}






inline void KJSONCursor::PrepareForRead()
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());

    m_scopeStack[0].m_bWrite = false;
}

inline void KJSONCursor::PrepareForWrite()
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());

    m_scopeStack[0].m_bWrite = true;
}


inline void KJSONCursor::BeginChild(const char* pcszName, bool bWrite)
{
    assert(m_bInitFlag);
    assert(pcszName);
    //assert(!m_scopeStack.empty());

    KJSONLocalScope hNewScope;

    hNewScope.m_bWrite     = bWrite;
    hNewScope.m_strObjName = pcszName;

    if (!m_scopeStack.empty())
    {
        bool bCreateNewChild = bWrite;

        if (m_scopeStack.back().m_hObj.ValuePtr() != NULL)
        {
            hNewScope.m_hObj = m_jsonDoc.OpenChild(
                m_scopeStack.back().m_hObj,
                pcszName,
                bCreateNewChild
            );
        }
    }

    // ���ʧ�ܣ�����Ὣһ���յ�KJSONHandle�Ƶ�ջ��
    m_scopeStack.push_back(hNewScope);
}

inline void KJSONCursor::BeginFirstChild(bool bWrite)
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());
    // д������Ӧ�õ����������
    assert(!bWrite);

    KJSONLocalScope hNewScope;

    hNewScope.m_bWrite = bWrite;

    if (!m_scopeStack.empty())
    {
        if (m_scopeStack.back().m_hObj.ValuePtr() != NULL)
        {   // ��ȡ��Ա�������б�
            m_scopeStack.back().m_hObj.ValueRef().getMemberNames().swap(
                m_scopeStack.back().m_memberNameList
            );

            // ��ȡ��һ����Ա
            m_scopeStack.back().m_nMemberNameIndex = 0;

            if (m_scopeStack.back().m_nMemberNameIndex <
                m_scopeStack.back().m_memberNameList.size())
            {   // ��ȡ��һ����Ա������
                hNewScope.m_strObjName =
                    m_scopeStack.back().m_memberNameList[
                        m_scopeStack.back().m_nMemberNameIndex
                    ];

                // ��ȡ�ó�Ա�Ķ���
                hNewScope.m_hObj = m_jsonDoc.OpenChild(
                    m_scopeStack.back().m_hObj,
                    hNewScope.m_strObjName.c_str(),
                    hNewScope.m_bWrite
                );

                // ������������һ����Ա
                m_scopeStack.back().m_nMemberNameIndex++;
            }
        }
    }

    // ���ʧ�ܣ�����Ὣһ���յ�Handle�Ƶ�ջ��
    m_scopeStack.push_back(hNewScope);
}

inline void KJSONCursor::ToNextBrother()
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());


    KJSONLocalScope hNewScope;

    hNewScope.m_bWrite      = m_scopeStack.back().m_bWrite;
    hNewScope.m_strObjName  = m_scopeStack.back().m_strObjName;
    // д������Ӧ�õ����������
    assert(!hNewScope.m_bWrite);

    // ��ǰһ���ֵܳ�ջ
    m_scopeStack.pop_back();
    assert(!m_scopeStack.empty());

    // ջ����Ϊ��,�����������
    if (!m_scopeStack.empty())
    {
        if (m_scopeStack.back().m_nMemberNameIndex < 
            m_scopeStack.back().m_memberNameList.size())
        {
            // ȡ����һ����Ա������
            hNewScope.m_strObjName = 
                m_scopeStack.back().m_memberNameList[
                    m_scopeStack.back().m_nMemberNameIndex
                ];

            // ��ȡ�ó�Ա�Ķ���
            hNewScope.m_hObj = m_jsonDoc.OpenChild(
                m_scopeStack.back().m_hObj,
                hNewScope.m_strObjName.c_str(),
                hNewScope.m_bWrite
            );

            // ������������һ����Ա
            m_scopeStack.back().m_nMemberNameIndex++;
        }
    }

    // ���ʧ�ܣ�����Ὣһ���յ�Handle�Ƶ�ջ��
    m_scopeStack.push_back(hNewScope);
}


inline bool KJSONCursor::NoMoreBrother()
{
    assert(m_bInitFlag);

    if (m_scopeStack.empty())
    {
        return true;
    }

    bool bWrite = m_scopeStack.back().m_bWrite;

    if (bWrite)
    {   // д����������ĩβ���,������Զ���ᵽ���յ�
        return false;
    }

    return (m_scopeStack.back().m_hObj.ValuePtr() == NULL);
}

inline void KJSONCursor::EndChild()
{
    assert(m_bInitFlag);

    m_scopeStack.pop_back();

    assert(!m_scopeStack.empty());
}

inline bool KJSONCursor::IsNull()
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());

    if (m_scopeStack.empty())
    {
        return false;
    }

    return (m_scopeStack.back().m_hObj.ValuePtr() == NULL);
}

inline bool KJSONCursor::IsLeaf()
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());

    if (m_scopeStack.empty())
    {
        assert(false);
        return false;
    }

    if (m_scopeStack.back().m_hObj.ValuePtr() == NULL)
    {
        assert(false);
        return false;
    }

    if (m_scopeStack.back().m_hObj.ValueRef().isArray() ||
        m_scopeStack.back().m_hObj.ValueRef().isObject())
    {
        return false;
    }

    return true;
}







inline void KJSONCursor::BeginFirstArrayElem(bool bWrite)
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());

    KJSONLocalScope hNewScope;

    hNewScope.m_bWrite     = bWrite;
    //hNewScope.m_strObjName = "";
    hNewScope.m_nIndex     = 0;

    if (!m_scopeStack.empty())
    {
        // �����������
        hNewScope.m_hObj = m_jsonDoc.OpenArrayElement(
            m_scopeStack.back().m_hObj,
            0, 
            hNewScope.m_bWrite
        );
    }

    // ���ʧ�ܣ�����Ὣһ���յ�KJSONHandle�Ƶ�ջ��
    m_scopeStack.push_back(hNewScope);
}

inline void KJSONCursor::ToNextArrayElem()
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());

    KJSONLocalScope hNewScope;

    hNewScope.m_bWrite      = m_scopeStack.back().m_bWrite;
    hNewScope.m_strObjName  = m_scopeStack.back().m_strObjName;
    hNewScope.m_nIndex      = m_scopeStack.back().m_nIndex + 1;

    m_scopeStack.pop_back();
    assert(!m_scopeStack.empty());

    // ��ջ��,Ҳ���Ǹ����������
    if (!m_scopeStack.empty())
    {
        hNewScope.m_hObj = m_jsonDoc.OpenArrayElement(
            m_scopeStack.back().m_hObj,
            hNewScope.m_nIndex, 
            hNewScope.m_bWrite
        );
    }

    // ���ʧ�ܣ�����Ὣһ���յ�Handle�Ƶ�ջ��
    m_scopeStack.push_back(hNewScope);
}

inline bool KJSONCursor::ArrayElemIsEnd()
{
    assert(m_bInitFlag);

    if (m_scopeStack.empty())
    {
        return true;
    }

    bool bWrite = m_scopeStack.back().m_bWrite;

    if (bWrite)
    {   // д����������ĩβ���,������Զ���ᵽ���յ�
        return false;
    }

    //KJSONHandle hNext;

    //// ��ջ��,Ҳ���Ǹ����������
    //if (m_scopeStack.size() >= 2)
    //{

    //    size_t nNewIndex = m_scopeStack.back().m_nIndex + 1;

    //    KJSONHandle hParent = m_scopeStack[m_scopeStack.size() - 2].m_hObj;

    //    hNext = m_jsonDoc.OpenArrayElement(hParent, nNewIndex, false);
    //}

    return (m_scopeStack.back().m_hObj.ValuePtr() == NULL);
}

inline void KJSONCursor::EndArrayElem()
{
    assert(m_bInitFlag);

    m_scopeStack.pop_back();

    assert(!m_scopeStack.empty());
}

//////////////////////////////////////////////////////////////////////////
// BeginArray����д����ʱ,����һ���������
inline void KJSONCursor::BeginArray(bool bWrite)
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());

    KJSONLocalScope hNewScope;

    hNewScope.m_bWrite     = bWrite;
    hNewScope.m_strObjName = "array[]";
    hNewScope.m_nIndex     = 0;

    if (!m_scopeStack.empty())
    {
        if (bWrite)
        {
            // �����д����,����Ҫ��ʼ�������
            m_scopeStack.back().m_hObj.ValueRef() = Json::Value(Json::arrayValue);
        }

        // �����������
        hNewScope.m_hObj = m_scopeStack.back().m_hObj;
    }

    // ���ʧ�ܣ�����Ὣһ���յ�KJSONHandle�Ƶ�ջ��
    m_scopeStack.push_back(hNewScope);
}

inline void KJSONCursor::EndArray()
{
    assert(m_bInitFlag);

    m_scopeStack.pop_back();

    assert(!m_scopeStack.empty());
}

inline bool KJSONCursor::IsArray()
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());

    if (m_scopeStack.back().m_bWrite)
    {   //д����ʱ,����δ������,��������������
        return true;
    }

    KJSONHandle hObj = m_scopeStack.back().m_hObj;
    if (NULL == hObj.ValuePtr())
    {
        return false;
    }

    return hObj.ValueRef().isArray();
}



inline long KJSONCursor::EraseAllChildren()
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());

    long lRet = _VerifyCursor();
    if (FAILED(lRet))
    {
        return lRet;
    }

    return m_jsonDoc.EraseAllChildren(m_scopeStack.back().m_hObj);
}

inline long KJSONCursor::RemoveChildren(const char* pcszName)
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());

    long lRet = _VerifyCursor();
    if (FAILED(lRet))
    {
        return lRet;
    }

    return m_jsonDoc.RemoveChildren(m_scopeStack.back().m_hObj, pcszName);
}

inline long KJSONCursor::GetObjName(std::string& strName)
{
    assert(m_bInitFlag);
    assert(!m_scopeStack.empty());

    long lRet = _VerifyCursor();
    if (FAILED(lRet))
    {
        return lRet;
    }

    strName = m_scopeStack.back().m_strObjName;

    return S_OK;
}









// template<class _KOtherDOMCursor>
// inline long KJSONCursor::CopyNodeTo(_KOtherDOMCursor& otherDOMCursor)
// {
//     assert(m_bInitFlag);
//     assert(!IsNull());
// 
//     long lRet = -1;
// 
//     if (IsNull())
//     {
//         return E_KJSON_CURRENT_NODE_IS_NULL;
//     }
//     else if (IsLeaf())
//     {
//         std::string strValue;
// 
//         // ��ȡֵʧ��,������Ϊ���ֵΪ��,���ﲻ��Ϊ������
//         lRet = GetObjValue(strValue);
//         if (SUCCEEDED(lRet))
//         {
//             lRet = otherDOMCursor.SetObjValue(strValue);
//             if (FAILED(lRet))
//             {
//                 return lRet;
//             }
//         }
// 
//         return S_OK;
//     }
//     else if (IsArray())
//     {
//         // open 'this' for reading
//         KDOMAutoArrayEx<KJSONCursor>     autoArray(this, false);
//         KDOMAutoArrayElemEx<KJSONCursor> autoIter(this, false);
// 
//         if (!autoIter.End())
//         {   // open 'other' for writing
//             KDOMAutoArrayEx<_KOtherDOMCursor>     otherArray(&otherDOMCursor, true);
//             KDOMAutoArrayElemEx<_KOtherDOMCursor> otherIter(&otherDOMCursor, true);
// 
// 
//             lRet = CopyNodeTo(otherDOMCursor);
//             if (FAILED(lRet))
//             {
//                 return lRet;
//             }
//             
// 
//             // �������MoveToNext()�����и�����
//             // д�����MoveToNext()���ܻ����һ��null object
//             // �������������MoveToNext()��˳���������⴦��
//             autoIter.MoveToNext();
//             while (!autoIter.End())
//             {   // open 'other' for writing
//                 otherIter.MoveToNext();
// 
//                 lRet = CopyNodeTo(otherDOMCursor);
//                 if (FAILED(lRet))
//                 {
//                     return lRet;
//                 }
// 
//                 autoIter.MoveToNext();                
//             }
//         }
//     }
//     else
//     {
//         // open 'this' for reading
//         KDOMAutoBrotherEx<KJSONCursor> autoBrother(this, false);
// 
//         while (!autoBrother.NoMoreBrother())
//         {
//             std::string strName;
// 
//             lRet = GetObjName(strName);
//             if (FAILED(lRet))
//             {
//                 return lRet;
//             }
// 
// 
//             {
//                 // open 'other' for writing
//                 KDOMAutoChildEx<_KOtherDOMCursor>
//                 autoOther(strName.c_str(), &otherDOMCursor, true);
// 
//                 lRet = CopyNodeTo(otherDOMCursor);
//                 if (FAILED(lRet))
//                 {
//                     return lRet;
//                 }
//             }
// 
//             autoBrother.MoveToNextBrother();
//         }
//     }
// 
//     return S_OK;
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
// 
// 
// template<class T>
// inline long KJSONCursor::ObjDataExchange(bool bWrite, T& value)
// {
//     assert(m_bInitFlag);
// 
//     return KXMLDataExchange(*this, value, bWrite);
// }
// 
// template<class T>
// inline long KJSONCursor::ObjDataExchange(bool bWrite, T& value, const T& defValue)
// {
//     assert(m_bInitFlag);
// 
//     long lRet = KXMLDataExchange(*this, value, bWrite);
//     if (FAILED(lRet))
//     {
//         value = defValue;
//     }
// 
//     return S_OK;
// }
// 
// template<class T>
// inline long KJSONCursor::BasicDataExchange(bool bWrite, T& value)
// {
//     assert(m_bInitFlag);
// 
//     if (bWrite)
//     {
//         return SetObjValue(value);
//     }
//     else
//     {
//         return GetObjValue(value);
//     }
// }
// 
// template<class T>
// inline long KJSONCursor::BasicDataExchange(bool bWrite, T& value, const T& defValue)
// {
//     assert(m_bInitFlag);
// 
//     if (bWrite)
//     {
//         return SetObjValue(value);
//     }
//     else
//     {
//         return GetObjValue(value, defValue);
//     }
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
// 
// 
// //////////////////////////////////////////////////////////////////////////
// // data operations
// template<class T>
// inline long KJSONCursor::SetObjValue(const T& value)
// {
//     assert(m_bInitFlag);
//     assert(!m_scopeStack.empty());
// 
//     long lRet = _VerifyCursor();
//     if (FAILED(lRet))
//     {
//         DumpPath();
//         return lRet;
//     }
// 
// 
//     lRet = m_jsonDoc.SetValue(m_scopeStack.back().m_hObj, value);
//     if (FAILED(lRet))
//     {
//         DumpPath();
//         return lRet;
//     }
// 
//     return S_OK;
// }
// 
// // ���Ҳ������ʵ�itemʱ,���pDefValue��ΪNULL,�򷵻سɹ�,��valueΪ*pDefValue
// // ���򷵻�ʧ��
// template<class T>
// inline long KJSONCursor::GetObjValue(T& value)
// {
//     assert(m_bInitFlag);
//     assert(!m_scopeStack.empty());
// 
//     long lRet = _VerifyCursor();
//     if (FAILED(lRet))
//     {
//         DumpPath();
//         return lRet;
//     }
// 
//     lRet = m_jsonDoc.GetValue(m_scopeStack.back().m_hObj, value);
//     if (FAILED(lRet))
//     {
//         DumpPath();
//         return lRet;
//     }
// 
//     return S_OK;
// }
// 
// template<class T>
// inline long KJSONCursor::GetObjValue(T& value, const T& defValue)
// {
//     assert(m_bInitFlag);
// 
//     long lRet = GetObjValue(value);
// 
//     if (FAILED(lRet))
//     {
//         value = defValue;
//     }
// 
//     return S_OK;
// }





//////////////////////////////////////////////////////////////////////////
// private implement
inline long KJSONCursor::_InitCursor()
{
    _ClearCursor();

    KJSONHandle hRoot = m_jsonDoc.RootHandle();
    if (NULL == hRoot.ValuePtr())
    {
        return E_KJSON_ROOT_NODE_IS_NULL;
    }

    std::string strRootName;
    long lRet = m_jsonDoc.GetRootName(strRootName);
    if (FAILED(lRet))
    {
        return E_KJSON_FAIL_TO_GET_ROOT_NAME;
    }

    m_scopeStack.push_back(KJSONLocalScope(true, hRoot, strRootName, 0));

    m_bInitFlag = true;

    return S_OK;
}

inline void KJSONCursor::_UninitCursor()
{
    _ClearCursor();

    m_bInitFlag = false;
}

inline void KJSONCursor::_ClearCursor()
{
    m_scopeStack.clear();

    m_bInitFlag = false;
}

inline long KJSONCursor::_VerifyCursor()
{
    if (m_scopeStack.empty())
    {
        return E_KJSON_SCOPE_STACK_IS_EMPTY;
    }

    if (m_scopeStack.back().m_hObj.ValuePtr() == NULL)
    {
        return E_KJSON_CURRENT_NODE_IS_NULL;
    }

    return S_OK;
}



//inline void KJSONCursor::_TraceError(long lRet)
//{
//    m_lLastInternalError = lRet;
//}



_KAN_DOM_END



#endif//__KJSONCursorImp_H_
