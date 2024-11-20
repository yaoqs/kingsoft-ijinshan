// dummyz@126.com

#pragma once

#include "PEParser.h"
#include "PEiDentifier.h"

class CPEJudger
{
public:
	enum RiskLevel
	{
		RiskLevelUnknown = 0,
		RiskLevelLow = 1,
		RiskLevelMid = 2,
		RiskLevelHig = 3
	};

	enum RiskType
	{
		RiskTypeUnknown = 0,
		RiskTypeTrojan = 1,
		RiskTypeVirus = 2
	};

public:
	CPEJudger();
	virtual ~CPEJudger();

	// MAKELONG(RiskType, RiskLevel)
	DWORD			GuessRiskLevel(CPEParser* lpParser, LPTSTR lpName);

private:
	static DWORD	GuessPackerOrVirus(CPEParser* lpParser); // MAKELONG(nScorePacker, nScoreVirus)
#ifdef _PEDISAM_
	static DWORD	GuessVirusByOep(CPEParser* lpParser); // ������� �²��Ƿ���ľ������
#endif

public:
	static BOOL		IsRiskIcon(CPEParser* lpParser); // ͼ�����ļ��У�ͼƬ
	static BOOL		IsSingleIcon(CPEParser* lpParser); // ֻ��һ�� Icon ��Դ

	static BOOL		IsOverlayBindExe(CPEParser* lpParser); // ���������Ƿ����� exe
	static BOOL		IsResourceBindExe(CPEParser* lpParser); // ��Դ�����Ƿ����� exe

	static BOOL		ScanPEStruct(CPEParser* lpParser, ULONG lFilePointer);

public:
	BOOL	__IsSkipFile(CPEParser* lpParser);
};