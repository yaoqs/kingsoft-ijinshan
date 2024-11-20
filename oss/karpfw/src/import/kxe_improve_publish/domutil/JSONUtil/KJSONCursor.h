/********************************************************************
* CreatedOn: 2006-12-12   10:47
* FileName:  KJSONCursor.h
* CreatedBy: zhangrui <zhangrui@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/

#ifndef __KJSONCursor_H_
#define __KJSONCursor_H_

#include "KJSONBasic.h"
#include "KJSONDoc.h"

#include "KJSONHandle.h"

_KAN_DOM_BEGIN

//////////////////////////////////////////////////////////////////////////
// �����ļ�����LoadFile��SaveFile��
// ����������ַ�����Ӧ����UTF8����,�����������ַ��Ľӿڻᱻת��ΪUTF8
class KJSONCursor
{
public:
    KJSONCursor();

    ~KJSONCursor();


    long LoadFile(const TKChar* pcszFileName);

    long LoadString(const char* pcszInput);

    long LoadDOMName(const char* pcszName);

    long SaveFile(const TKChar* pcszFileName);

    long ToString(std::string* pstrOutput);

    long ToCompactString(std::string* pstrRet);

    template<class _KOtherDOMCursor>
    long ToOtherDOM(_KOtherDOMCursor& otherDOMCursor);

    //long GetLastInternalError();


    void DumpPath();

    void PopPathDump(std::vector<std::string>& pathInfo);



    long PhrasePath(const char* pcszPath, std::vector<std::string>& pathItemList);

    //////////////////////////////////////////////////////////////////////////
    // ����Ĳ���Ϊ�����ӿ�ʹ��

    //////////////////////////////////////////////////////////////////////////
    // structure operations
    void PrepareForRead();

    void PrepareForWrite();


    void BeginChild(const char* pcszName, bool bWrite);

    void BeginFirstChild(bool bWrite);

    void ToNextBrother();

    bool NoMoreBrother();

    void EndChild();

    bool IsNull();

    bool IsLeaf();



    void BeginFirstArrayElem(bool bWrite);

    void ToNextArrayElem();

    bool ArrayElemIsEnd();

    void EndArrayElem();



    void BeginArray(bool bWrite);

    void EndArray();

    bool IsArray();




    long EraseAllChildren();

    long RemoveChildren(const char* pcszName);

    long GetObjName(std::string& strName);



    template<class _KOtherDOMCursor>
    long CopyNodeTo(_KOtherDOMCursor& otherDOMCursor)
	{
		assert(m_bInitFlag);
		assert(!IsNull());
		
		long lRet = -1;
		
		if (IsNull())
		{
			return E_KJSON_CURRENT_NODE_IS_NULL;
		}
		else if (IsLeaf())
		{
			std::string strValue;
			
			// ��ȡֵʧ��,������Ϊ���ֵΪ��,���ﲻ��Ϊ������
			lRet = GetObjValue(strValue);
			if (SUCCEEDED(lRet))
			{
				lRet = otherDOMCursor.SetObjValue(strValue);
				if (FAILED(lRet))
				{
					return lRet;
				}
			}
			
			return S_OK;
		}
		else if (IsArray())
		{
			// open 'this' for reading
			KDOMAutoArrayEx<KJSONCursor>     autoArray(this, false);
			KDOMAutoArrayElemEx<KJSONCursor> autoIter(this, false);
			
			if (!autoIter.End())
			{   // open 'other' for writing
				KDOMAutoArrayEx<_KOtherDOMCursor>     otherArray(&otherDOMCursor, true);
				KDOMAutoArrayElemEx<_KOtherDOMCursor> otherIter(&otherDOMCursor, true);
				
				
				lRet = CopyNodeTo(otherDOMCursor);
				if (FAILED(lRet))
				{
					return lRet;
				}
				
				
				// �������MoveToNext()�����и�����
				// д�����MoveToNext()���ܻ����һ��null object
				// �������������MoveToNext()��˳���������⴦��
				autoIter.MoveToNext();
				while (!autoIter.End())
				{   // open 'other' for writing
					otherIter.MoveToNext();
					
					lRet = CopyNodeTo(otherDOMCursor);
					if (FAILED(lRet))
					{
						return lRet;
					}
					
					autoIter.MoveToNext();                
				}
			}
		}
		else
		{
			// open 'this' for reading
			KDOMAutoBrotherEx<KJSONCursor> autoBrother(this, false);
			
			while (!autoBrother.NoMoreBrother())
			{
				std::string strName;
				
				lRet = GetObjName(strName);
				if (FAILED(lRet))
				{
					return lRet;
				}
				
				
				{
					// open 'other' for writing
					KDOMAutoChildEx<_KOtherDOMCursor>
						autoOther(strName.c_str(), &otherDOMCursor, true);
					
					lRet = CopyNodeTo(otherDOMCursor);
					if (FAILED(lRet))
					{
						return lRet;
					}
				}
				
				autoBrother.MoveToNextBrother();
			}
		}
		
		return S_OK;
	}



    template<class T>
    long ObjDataExchange(bool bWrite, T& value)
	{
		assert(m_bInitFlag);
		
		return KXMLDataExchange(*this, value, bWrite);
	}

    template<class T>
    long ObjDataExchange(bool bWrite, T& value, const T& defValue)
	{
		assert(m_bInitFlag);
		
		long lRet = KXMLDataExchange(*this, value, bWrite);
		if (FAILED(lRet))
		{
			value = defValue;
		}
		
		return S_OK;
	}

    template<class T>
    long BasicDataExchange(bool bWrite, T& value)
	{
		assert(m_bInitFlag);
		
		if (bWrite)
		{
			return SetObjValue(value);
		}
		else
		{
			return GetObjValue(value);
		}
	}

    template<class T>
    long BasicDataExchange(bool bWrite, T& value, const T& defValue)
	{
		assert(m_bInitFlag);
		
		if (bWrite)
		{
			return SetObjValue(value);
		}
		else
		{
			return GetObjValue(value, defValue);
		}
	}
    


    //////////////////////////////////////////////////////////////////////////
    // data operations
    template<class T>
    long SetObjValue(const T& value)
	{
		assert(m_bInitFlag);
		assert(!m_scopeStack.empty());
		
		long lRet = _VerifyCursor();
		if (FAILED(lRet))
		{
			DumpPath();
			return lRet;
		}
		
		
		lRet = m_jsonDoc.SetValue(m_scopeStack.back().m_hObj, value);
		if (FAILED(lRet))
		{
			DumpPath();
			return lRet;
		}
		
		return S_OK;
	}

    // ���Ҳ������ʵ�itemʱ,���pDefValue��ΪNULL,�򷵻سɹ�,��valueΪ*pDefValue
    // ���򷵻�ʧ��
    template<class T>
    long GetObjValue(T& value)
	{
		assert(m_bInitFlag);
		assert(!m_scopeStack.empty());
		
		long lRet = _VerifyCursor();
		if (FAILED(lRet))
		{
			DumpPath();
			return lRet;
		}
		
		lRet = m_jsonDoc.GetValue(m_scopeStack.back().m_hObj, value);
		if (FAILED(lRet))
		{
			DumpPath();
			return lRet;
		}
		
		return S_OK;
	}

    template<class T>
    long GetObjValue(T& value, const T& defValue)
	{
		assert(m_bInitFlag);
		
		long lRet = GetObjValue(value);
		
		if (FAILED(lRet))
		{
			value = defValue;
		}
		
		return S_OK;
	}


private:
    KJSONCursor(const KJSONCursor&);
    KJSONCursor& operator=(const KJSONCursor&);

    long _InitCursor();
    void _UninitCursor();
    void _ClearCursor();

    long _VerifyCursor();

    //void _TraceError(long lRet);




    //////////////////////////////////////////////////////////////////////////
    // �������ر�ģ�����ȼ��ߣ����������������Σ�յ��÷�
    typedef const void*             K_PCVOID;
    typedef const char*             K_PCCHAR;
    typedef const unsigned char*    K_PCUCHAR;
    typedef const wchar_t*          K_PCWCHAR;

    long GetObjValue(K_PCVOID  value,    K_PCVOID  defStr);
    long GetObjValue(K_PCVOID  value);
    long GetObjValue(K_PCCHAR  value,    K_PCCHAR  defStr);
    long GetObjValue(K_PCCHAR  value);
    long GetObjValue(K_PCUCHAR value,    K_PCUCHAR defStr);
    long GetObjValue(K_PCUCHAR value);
    long GetObjValue(K_PCWCHAR value,    K_PCWCHAR defStr);
    long GetObjValue(K_PCWCHAR value);



    class KJSONLocalScope
    {
    public:
        KJSONLocalScope(): m_bWrite(false), m_hObj(NULL), m_nIndex(0), m_nMemberNameIndex(0)
        {
        }

        KJSONLocalScope(
            bool                bWrite,
            const KJSONHandle&  hObj,
            const std::string&  strObjName,
            size_t              nIndex
        ):
            m_bWrite(bWrite),
            m_hObj(hObj),
            m_strObjName(strObjName),
            m_nIndex(nIndex),
            m_nMemberNameIndex(0)
        {
        }

        KJSONLocalScope(const KJSONLocalScope& rScope):
            m_bWrite(rScope.m_bWrite),
            m_hObj(rScope.m_hObj),
            m_strObjName(rScope.m_strObjName),
            m_nIndex(rScope.m_nIndex),
            m_memberNameList(rScope.m_memberNameList),
            m_nMemberNameIndex(rScope.m_nMemberNameIndex)
        {
        }

        KJSONLocalScope& operator=(const KJSONLocalScope& rScope)
        {
            m_bWrite            = rScope.m_bWrite;
            m_hObj              = rScope.m_hObj;
            m_strObjName        = rScope.m_strObjName;
            m_nIndex            = rScope.m_nIndex;
            m_memberNameList    = rScope.m_memberNameList;
            m_nMemberNameIndex  = rScope.m_nMemberNameIndex;

            return *this;
        }

        bool        m_bWrite;
        KJSONHandle m_hObj;
        std::string m_strObjName;
        size_t      m_nIndex;   // ��������

        std::vector<std::string>    m_memberNameList;
        size_t                      m_nMemberNameIndex; // ������Ա����
    };


    bool m_bInitFlag;

    KJSONDoc m_jsonDoc;

    std::vector<KJSONLocalScope> m_scopeStack;


    //long                        m_lLastInternalError;
    std::vector<std::string>    m_pathDump;
};

_KAN_DOM_END

#include "KJSONCursorImp.h"



#endif//__KJSONCursor_H_
