// dummyz@126.com

#pragma once

enum {
	VC_Linker		= 1,
	VB_Linker		= 2,
	Delphi_Linker	= 4,
	Eyuyan_Linker	= 8
};

#include "PEParser.h"
#include <vector>
#include <string>

class CPEiDentifier
{
public:
	CPEiDentifier();
	virtual ~CPEiDentifier();

	BOOL	Load(LPCTSTR lpFilePath);
	void	Unload();

	LPCTSTR Scan(LPCTSTR lpFilePath);
	LPCTSTR	Scan(CPEParser* lpParser);

	// ͨ����ò�����ж�
	static BOOL		IsVCLink(CPEParser* lpParser);
	static BOOL		IsVBLink(CPEParser* lpParser); // �������Ƿ��� vb
	static BOOL		IsDelphiLink(CPEParser* lpParser); // �������Ƿ��� delphi
	static BOOL		IsEyuyanLink(CPEParser* lpParser); // �������Ƿ��� ������
	static BOOL		IsDotNetLink(CPEParser* lpParser);

	static BOOL		IsRiskPacker(CPEParser* lpParser);
	static BOOL		IsNormalPacker(CPEParser* lpParser);

	static BOOL		IsResourcePacked(CPEParser* lpParser);
	static BOOL		IsImportPacked(CPEParser* lpParser);
	static BOOL		IsSectionPacked(CPEParser* lpParser);

	static BOOL		IsResourceBin(CPEParser* lpParser); 
	

	// ��ȡ�ļ����������Ϣ
	static BOOL		GetLinkerInfo(CPEParser* lpParser, BOOL& bNotPacker, DWORD& dwLinker);
	static BOOL		IsAntiVirusCleaned(CPEParser* lpParser); // �Ƿ���ɱ�������������ļ�

protected:
	LPCTSTR	ScanOep(CPEParser* lpParser);
	LPCTSTR ScanNoOep(CPEParser* lpParser);
	
protected:
	struct SIGNATURE
	{
		std::wstring		strName;
		std::vector<WORD>	data;
		PWORD				lpwPointer;
	};

	DWORD					m_dwOepMaxLen;
	DWORD					m_dwNoOepMaxLen;

	std::list<SIGNATURE>	m_OepSignaList;
	std::list<SIGNATURE>	m_NoOepSignaList;
};