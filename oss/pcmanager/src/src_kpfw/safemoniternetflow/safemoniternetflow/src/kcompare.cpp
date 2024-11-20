#include "stdafx.h"
#include "kcompare.h"

// str1��str2 ��Ҫ�����ã���Ϊ�����ı�str1��str2��ֵ
int KCompare::StringNoCase(ATL::CString str1, ATL::CString str2)
{
	str1 = str1.MakeLower();
	str2 = str2.MakeLower();

    int nCmpResult = KPFW_COMPARE_RESULT_ERROR;

    if(str1 == str2)
    {
        nCmpResult = KPFW_COMPARE_RESULT_EQUAL;
    }
    else if(str1 < str2)
    {
        nCmpResult = KPFW_COMPARE_RESULT_LESS;
    }
    else
    {
        nCmpResult = KPFW_COMPARE_RESULT_GREAT;
    }

    return nCmpResult;
}