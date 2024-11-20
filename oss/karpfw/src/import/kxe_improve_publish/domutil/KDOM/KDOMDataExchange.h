/********************************************************************
* CreatedOn: 2006-12-12   17:44
* FileName:  KDOMDataExchange.h
* CreatedBy: zhangrui <zhangrui@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/

#ifndef __KDOMDataExchange_H_
#define __KDOMDataExchange_H_

#include "KDOMBasic.h"
#include "KDOMMacro.h"
#include "KDOMAutoChild.h"
#include "KDOMAutoArrayElem.h"
#include "KDOMAutoMap.h"

#include <vector>
#include <list>
#include <map>
#include <utility>

#include <ctype.h>

_KAN_DOM_BEGIN

// bool
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, bool& bValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, bValue);
}

// short
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, signed short& sValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, sValue);
}

// unsigned short
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, unsigned short& usValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, usValue);
}

// int
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, signed int& nValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, nValue);
}

// unsigned int
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, unsigned int& unValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, unValue);
}

// long
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, signed long& lValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, lValue);
}

// unsigned long
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, unsigned long& ulValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, ulValue);
}

// __int64
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, __int64& i64Value, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, i64Value);
}

// char
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, char& cValue, bool bWrite)
{
    int nValue = cValue;    // char������Ϊ��ֵ����ת��

    long lRet = domCur.BasicDataExchange(bWrite, nValue);
    if (SUCCEEDED(lRet) && !bWrite)
    {   // ������ʱ,��Ҫ�����ֵ��Χ
        if (nValue > SCHAR_MAX || nValue < SCHAR_MIN)
        {   // ������ֵ��Χ
            domCur.DumpPath();
            return E_KDOM_DATA_OUT_OF_RANGE;
        }
        else
        {
            cValue = nValue;
        }
    }

    return lRet;
}

// signed char
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, signed char& cValue, bool bWrite)
{
    int nValue = cValue;    // char������Ϊ��ֵ����ת��

    long lRet = domCur.BasicDataExchange(bWrite, nValue);
    if (SUCCEEDED(lRet) && !bWrite)
    {   // ������ʱ,��Ҫ�����ֵ��Χ
        if (nValue > SCHAR_MAX || nValue < SCHAR_MIN)
        {   // ������ֵ��Χ
            domCur.DumpPath();
            return E_KDOM_DATA_OUT_OF_RANGE;
        }
        else
        {
            cValue = nValue;
        }
    }

    return lRet;
}

// unsigned char
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, unsigned char& ucValue, bool bWrite)
{
    unsigned int unValue = ucValue; // unsigned char������Ϊ��ֵ����ת��

    long lRet = domCur.BasicDataExchange(bWrite, unValue);
    if (SUCCEEDED(lRet) && !bWrite)
    {   // ������ʱ,��Ҫ�����ֵ��Χ
        if (unValue > UCHAR_MAX)
        {   // ������ֵ��Χ
            domCur.DumpPath();
            return E_KDOM_DATA_OUT_OF_RANGE;
        }
        else
        {
            ucValue = unValue;
        }
    }
    
    return lRet;
}



//////////////////////////////////////////////////////////////////////////
// see MSDN about "/Zc"
#ifdef _NATIVE_WCHAR_T_DEFINED

// wchar_t
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, wchar_t& wcValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, wcValue);
}

#endif



// char*
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, const char* pszValue, bool bWrite)
{
    assert(bWrite);
    if (bWrite)
    {
        return domCur.SetObjValue(pszValue);
    }
    
    return E_KDOM_DATA_TYPE_DO_NOT_SUPPORT_WRITING;
}

// wchar_t*
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, const wchar_t* pwszValue, bool bWrite)
{
    assert(bWrite);
    if (bWrite)
    {
        return domCur.SetObjValue(pwszValue);
    }

    return E_KDOM_DATA_TYPE_DO_NOT_SUPPORT_WRITING;
}








//////////////////////////////////////////////////////////////////////////
// std::xstring
template<class _KDOMCursor, class _CharType, class _Traits, class _Alloc>
inline long KXMLDataExchange(
    _KDOMCursor& domCur,
    std::basic_string<_CharType, _Traits, _Alloc>& strValue,
    bool bWrite
)
{
    return domCur.BasicDataExchange(bWrite, strValue);
}




//////////////////////////////////////////////////////////////////////////
// std::vector
template<class _KDOMCursor, class T, class _Alloc>
inline long KXMLDataExchange(_KDOMCursor& domCur, std::vector<T, _Alloc>& stlVec, bool bWrite)
{
    long lRet;

    //KANDOM::KDOMAutoArrayEx<_KDOMCursor> domArrayIter(&domCur, bWrite);

    if (bWrite)
    {
        // �����д����,��ɾ�������ӽ��
        lRet = domCur.EraseAllChildren();
        if (FAILED(lRet))
        {
            domCur.DumpPath();
            return lRet;
        }

        // ����б�Ϊ��,��ֱ�ӷ���
        if (stlVec.empty())
        {
            return S_OK;
        }
    }
    else
    {   // ����Ƕ�����,��vec��Ҫ�����
        stlVec.clear();
    }

    {
        // ��ÿ��Ԫ�ؽ������ݽ���
        KANDOM::KDOMAutoArrayElemEx<_KDOMCursor> domArrayIter(&domCur, bWrite);

        if (bWrite)
        {
            if (!stlVec.empty())
            {   // ����MoveToNext()�����һ��null����,�������ｫ��һ��Ԫ�ص�д����ǰ
                std::vector<T, _Alloc>::iterator iter = stlVec.begin();

                lRet = domCur.ObjDataExchange(bWrite, *iter);
                if (FAILED(lRet))
                {
                    return lRet;
                }

                ++iter; // ѭ���ӵڶ���Ԫ�ؿ�ʼ
                for (NULL; iter != stlVec.end(); ++iter)
                {
                    // domIterƽ�Ƶ���һ��Ԫ��
                    domArrayIter.MoveToNext();

                    lRet = domCur.ObjDataExchange(bWrite, *iter);
                    if (FAILED(lRet))
                    {
                        return lRet;
                    }
                }
            }
        }
        else
        {
            while (!domArrayIter.End())
            {
                stlVec.push_back(T());
                lRet = domCur.ObjDataExchange(bWrite, stlVec.back());
                if (FAILED(lRet))
                {
                    return lRet;
                }

                // ƽ�Ƶ���һ��Ԫ��
                domArrayIter.MoveToNext();
            }
        }


        // �˳�ʱautoChild�Զ������ϲ�
    }

    return S_OK;
}








//////////////////////////////////////////////////////////////////////////
// std::list
template<class _KDOMCursor, class T, class _Alloc>
inline long KXMLDataExchange(_KDOMCursor& domCur, std::list<T, _Alloc>& stlList, bool bWrite)
{
    long lRet;

    KANDOM::KDOMAutoArrayEx<_KDOMCursor> domArrayIter(&domCur, bWrite);

    if (bWrite)
    {
        // �����д����,��ɾ�������ӽ��
        lRet = domCur.EraseAllChildren();
        if (FAILED(lRet))
        {
            domCur.DumpPath();
            return lRet;
        }

        // ����б�Ϊ��,��ֱ�ӷ���
        if (stlList.empty())
        {
            return S_OK;
        }
    }
    else
    {   // ����Ƕ�����,��vec��Ҫ�����
        stlList.clear();
    }

    {
        // ��ÿ��Ԫ�ؽ������ݽ���
        KANDOM::KDOMAutoArrayElemEx<_KDOMCursor> domArrayIter(&domCur, bWrite);

        if (bWrite)
        {
            if (!stlList.empty())
            {   // ����MoveToNext()�����һ��null����,�������ｫ��һ��Ԫ�ص�д����ǰ
                std::list<T, _Alloc>::iterator iter = stlList.begin();

                lRet = domCur.ObjDataExchange(bWrite, *iter);
                if (FAILED(lRet))
                {
                    return lRet;
                }

                ++iter; // ѭ���ӵڶ���Ԫ�ؿ�ʼ
                for (NULL; iter != stlVec.end(); ++iter)
                {
                    // domIterƽ�Ƶ���һ��Ԫ��
                    domArrayIter.MoveToNext();

                    lRet = domCur.ObjDataExchange(bWrite, *iter);
                    if (FAILED(lRet))
                    {
                        return lRet;
                    }
                }
            }
        }
        else
        {
            while (!domArrayIter.End())
            {
                stlVec.resize(stdVec.size());
                lRet = domCur.ObjDataExchange(bWrite, stlList.back());
                if (FAILED(lRet))
                {
                    return lRet;
                }

                // ƽ�Ƶ���һ��Ԫ��
                domArrayIter.MoveToNext();
            }
        }


        // �˳�ʱautoChild�Զ������ϲ�
    }

    return S_OK;
}





//////////////////////////////////////////////////////////////////////////
// std::map
template<class _KDOMCursor, class K, class T, class PR, class _Alloc>
inline long KXMLDataExchange(_KDOMCursor& domCur, std::map<K, T, PR, _Alloc>& stlMap, bool bWrite)
{
    long lRet;

    if (bWrite)
    {
        // д�����Ὣ��ǰ������ͱ��array
        //// �����д����,��ɾ�������ӽ��
        //lRet = domCur.EraseAllChildren();
        //if (FAILED(lRet))
        //{
        //    domCur.DumpPath();
        //    return lRet;
        //}

        // ����б�Ϊ��,��ֱ�ӷ���
        if (stlMap.empty())
        {
            return S_OK;
        }
    }
    else
    {   // ����Ƕ�����,��map��Ҫ�����
        stlMap.clear();
    }

    {
        // ��ÿ��Ԫ�ؽ������ݽ���
        

        if (bWrite)
        {
            if (!stlMap.empty())
            {
                KANDOM::KDOMAutoMapEx<_KDOMCursor> autoMap(&domCur, bWrite);

                std::map<K, T, PR, _Alloc>::iterator iter = stlMap.begin();
                for (NULL; iter != stlMap.end(); ++iter)
                {
                    lRet = autoMap.SetMapElem(iter->first, iter->second);
                    if (FAILED(lRet))
                    {
                        return lRet;
                    }
                }
            }
        }
        else
        {
            KANDOM::KDOMAutoMapElemEx<_KDOMCursor> autoMapElem(&domCur, bWrite);

            while (!autoMapElem.End())
            {
                std::pair<K, T> value;


                lRet = autoMapElem.GetMapElem(value.first, value.second);
                if (FAILED(lRet))
                {
                    return lRet;
                }

                stlMap.insert(value);

                // ƽ�Ƶ���һ��Ԫ��
                autoMapElem.MoveToNextElem();
            }
        }


        // �˳�ʱautoChild�Զ������ϲ�
    }

    return S_OK;
}






_KAN_DOM_END

#endif//__KDOMDataExchange_H_
