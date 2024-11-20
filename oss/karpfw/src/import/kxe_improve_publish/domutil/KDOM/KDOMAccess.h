/********************************************************************
* CreatedOn: 2006-12-11   14:50
* FileName:  KDOMAccess.h
* CreatedBy: zhangrui <zhangrui@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/

#ifndef __KDOMAccess_H_
#define __KDOMAccess_H_

#include "../KMPCommon/KConv.h"

#include "KDOMBasic.h"
#include "KDOMAutoPath.h"

_KAN_DOM_BEGIN

template<class _KDOMCursor>
class KDOMAccess
{
public:
    KDOMAccess() : m_bInitFlag(false)
	{
	}

    ~KDOMAccess()
	{

	}

    // ����һ��DOM�ļ�
    long LoadFile(const TKChar* pcszFileName)
	{
		assert(pcszFileName);
		int nRetCode = m_domCursor.LoadFile(pcszFileName);
		
		m_bInitFlag = SUCCEEDED(nRetCode);
		
		return nRetCode;
	}

    // ����һ��DOM�ַ���
    long LoadString(const char* pcszInput)
	{
		assert(pcszInput);
		int nRetCode = m_domCursor.LoadString(pcszInput);
		
		m_bInitFlag = SUCCEEDED(nRetCode);
		
		return nRetCode;
	}

    // ����һ���ַ�����ΪDOM����ĸ��������
    long LoadDOMName(const char* pcszName)
	{
		assert(pcszName);
		int nRetCode = m_domCursor.LoadDOMName(pcszName);
		
		m_bInitFlag = SUCCEEDED(nRetCode);
		
		return nRetCode;
	}

    // ������һ��DOM����
    template<class _KOtherDOMCursor>
    long LoadDOM(KDOMAccess<_KOtherDOMCursor>& otherDomAccess)
	{
		// �����Ը���
		if ((void*)this == (void*)&otherDomAccess)
			return S_OK;
		
		int nRetCode = otherDomAccess.m_domCursor.ToOtherDOM(m_domCursor);
		
		m_bInitFlag = SUCCEEDED(nRetCode);
		
		return nRetCode;
	}

    // ��DOM���󱣴浽�ļ�
    long SaveFile(const TKChar* pcszFileName)
	{
		assert(pcszFileName);
		return m_domCursor.SaveFile(pcszFileName);
	}

    // ���DOM�ַ���(����֤�Ƿ����ʽ)
    long ToString(std::string* pstrOutput)
	{
		assert(m_bInitFlag);
		assert(pstrOutput);
		return m_domCursor.ToString(pstrOutput);
	}

    // ���������ʽ��DOM�ַ���()
    long ToCompactString(std::string* pstrRet)
	{
		assert(m_bInitFlag);
		assert(pstrRet);
		return m_domCursor.ToCompactString(pstrRet);
	}

    // ��ȡ���ݵ�����,ͨ��Ϊ���ݵĸ������
    long GetDataName(std::string* pstrDataName)
	{
		assert(m_bInitFlag);
		assert(pstrDataName);
		
		return m_domCursor.GetObjName(*pstrDataName);
	}

    long PopPathDump(std::vector<std::string>& dumpPath)
	{
		assert(m_bInitFlag);
		
		m_domCursor.PopPathDump(dumpPath);
		
		return 0;
	}

    _KDOMCursor& Cursor()
	{
		return m_domCursor;
	}


    //////////////////////////////////////////////////////////////////////////
    // ���ݴ�ȡ�ӿ�,�����½ӿڵ���ǰ,���뱣֤���ٵ��ù�һ��ĳ��Load����
    // pcszPath����'\'Ϊ�ָ����ŵ�·����ʾ
    // ��ʽΪ"child\grandchild\...\objectname"
    // ע��,·���в���������������,Ҳ����ͨ��LoadDOMName���õ�����
    template<class T>
    long WriteData(const char* pcszPath, T& value)
	{  
		assert(m_bInitFlag);
		assert(pcszPath);

		m_domCursor.PrepareForWrite();
		{
			KDOMAutoPath autoPath(pcszPath, &m_domCursor, true);

			return m_domCursor.ObjDataExchange(true, value);
		}
	}

    template<class T>
    long ReadData(const char* pcszPath, T& value)
	{
		assert(m_bInitFlag);
		assert(pcszPath);
		
		m_domCursor.PrepareForRead();
		
		{
			KDOMAutoPath autoPath(pcszPath, &m_domCursor, false);
			
			return m_domCursor.ObjDataExchange(false, value);
		}
	}

    template<class T>
    long ReadData(const char* pcszPath, T& value, const T& defValue)
	{
		assert(m_bInitFlag);
		assert(pcszPath);
		
		int nRetCode = ReadData(pcszPath, value);
		if (FAILED(nRetCode))
		{
			value = defValue;
		}
		
		return S_OK;
	}


private:
    KDOMAccess(const KDOMAccess&);
    KDOMAccess& operator=(const KDOMAccess&);

    typedef KDOMAutoPathEx<_KDOMCursor>  KDOMAutoPath;

    _KDOMCursor m_domCursor;

    bool m_bInitFlag;

#if _MSC_VER >= 1400
	template<class _KDOMCursor>
		friend class KDOMAccess;
#else
	friend class KDOMAccess<_KDOMCursor>;
#endif

};

_KAN_DOM_END

//#include "KDOMAccessImp.h"

#endif//__KDOMAccess_H_
