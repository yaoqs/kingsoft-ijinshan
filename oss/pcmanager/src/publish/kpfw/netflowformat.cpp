#include "stdafx.h"
#include "netflowformat.h"

void NetFlowToString( ULONGLONG netFlow, ATL::CString& str )
{
	
	// ULONGLONG ֱ��תfloat��double��Release���Ż�������»����������ʾf
	// �����Լ�ʵ��һ��ת��
	static const wchar_t* szShowUnit[9] = {L"B", L"KB", L"MB", L"GB", L"TB", L"PB", L"EB", L"ZB", L"YB"};
	
	if (0 == netFlow)
	{
		str = L"0KB";
		return;
	}

	int nUnitCur	= 0;
	ULONGLONG numBeforePoint = 0;
	double numAfterPoint = 0;
	
	do
	{
		numBeforePoint = netFlow / 1024;
		numAfterPoint = (netFlow % 1024) / 1024.0;
		netFlow /= 1024;
		nUnitCur ++;
	}while (numBeforePoint > 1024);

	if (nUnitCur < 9)
	{
		WCHAR szRet[20] = {0};
		// ���numAfterPoint ����0.1 ����һλ��������2λС��

		if (numAfterPoint > 0.094)
		{
			// ����10��ʾ���_��С�����һλ������100����2λ����������
			// +0.5f ��Ϊ��ʵ���������롣
			int integerNumAfterPoint = (int)(numAfterPoint*10 + 0.5f);
			if (integerNumAfterPoint >= 10)
			{
				// �������2λС��
				numBeforePoint++;
				integerNumAfterPoint = 0;
			}

			swprintf_s(szRet, 20, L"%I64u.%01d", numBeforePoint, integerNumAfterPoint);
		}
		else
		{
			// ����10��ʾ���_��С�����һλ������100����2λ����������
			// +0.5f ��Ϊ��ʵ���������롣
			int integerNumAfterPoint = (int)(numAfterPoint*100 + 0.5f);
			if (integerNumAfterPoint >= 100)
			{
				// �������3λС��
				numBeforePoint++;
				integerNumAfterPoint = 0;
			}

			swprintf_s(szRet, 20, L"%I64u.%02d", numBeforePoint, integerNumAfterPoint);
		}

		str = szRet;
		str.Append(szShowUnit[nUnitCur]);
	}
}

void NetFlowToString2( ULONGLONG netFlow, ATL::CString& str )
{

	// ULONGLONG ֱ��תfloat��double��Release���Ż�������»����������ʾf
	// �����Լ�ʵ��һ��ת��
	static const wchar_t* szShowUnit[9] = {L"B", L"KB", L"MB", L"GB", L"TB", L"PB", L"EB", L"ZB", L"YB"};

	if (0 == netFlow)
	{
		str = L"0KB";
		return;
	}

	int nUnitCur	= 0;
	ULONGLONG numBeforePoint = 0;
	double numAfterPoint = 0;

	do
	{
		numBeforePoint = netFlow / 1024;
		numAfterPoint = (netFlow % 1024) / 1024.0;
		netFlow /= 1024;
		nUnitCur ++;
	}while (numBeforePoint > 1024);

	if (nUnitCur < 9)
	{
		WCHAR szRet[20] = {0};
		// ���nUnitCur ����2 ����һλ�����򲻱���

		if (nUnitCur > 1)
		{
			// ����10��ʾ���_��С�����һλ������100����2λ����������
			// +0.5f ��Ϊ��ʵ���������롣
			int integerNumAfterPoint = (int)(numAfterPoint*10 + 0.5f);
			if (integerNumAfterPoint >= 10)
			{
				// �������2λС��
				numBeforePoint++;
				integerNumAfterPoint = 0;
			}

			swprintf_s(szRet, 20, L"%I64u.%01d", numBeforePoint, integerNumAfterPoint);
		}
		else
		{
			swprintf_s(szRet, 20, L"%I64u", numBeforePoint);
		}

		str = szRet;
		str.Append(szShowUnit[nUnitCur]);
	}
}