////////////////////////////////////////////////////////////////////////////////
//      
//      common include File for kpfw
//      
//      File      : serializetools.h
//      Version   : 1.0
//      Comment   : ����һЩ���õ����л�����
//      
//      Create at : 2008-4-7
//      Create by : liupeng
//      
////////////////////////////////////////////////////////////////////////////////

#pragma once 
#include "kisrpc/rfcdef.h"

//////////////////////////////////////////////////////////////////////////
// atl CString �ַ������л�
namespace TypeSize
{
	inline size_t get_size(ATL::CString & str)
	{
		size_t nSize = sizeof(int);
		if (str.GetLength() > 0)
			nSize += (str.GetLength()+1) * sizeof(TCHAR);
		return nSize;
	}
}

namespace eternity
{
inline Meta::True Serialize(bin_archive &_serializer, ATL::CString & str)
{
	if(_serializer.is_loading())
	{
		INT nBufLen = 0;
		_serializer >> nBufLen;
		if (nBufLen != 0)
		{
			// ���һ��null�ַ�
			nBufLen++;
			LPTSTR pstr= str.GetBuffer(nBufLen);
			_serializer.read(pstr, nBufLen, sizeof(TCHAR));
			str.ReleaseBuffer(-1);
		}
	}
	else
	{
		int nLen = str.GetLength();
		_serializer << nLen;
		if (str.GetLength() > 0)
		{
			_serializer.write(str.GetBuffer(), str.GetLength()+1, sizeof(TCHAR));
		}
	}
	return Meta::True();
}
}