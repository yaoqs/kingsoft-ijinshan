#pragma once
#include <vector>
#include <string>

class SevenZipModule;
class WcxModule;
struct T_UserPatchInfo;
typedef std::vector<std::string> strings;

enum EPatcherCode
{
	KPATCHER_OK = 0,
	KPATCHER_ERR_GENERAL,		//
	KPATCHER_ERR_DOWNLOADFILE,	// �ӷ������������ݳ���
	KPATCHER_ERR_LOADXML,	// �ӷ������������ݳ���

	KPATCHER_ERR_XMLFILES = 0x10,
	KPATCHER_ERR_EXDLL,			// ����7z, msi.dll ���� 
	KPATCHER_ERR_EXTRACT,		// ������� 
	KPATCHER_ERR_FILEBUSY,		// Ŀ���ļ�æ, �޷����� 
	KPATCHER_ERR_FILENOTMATCH,	// �ļ���ƥ�� 
	KPATCHER_ERR_REPLACE,		// �ļ�������ʱ����� 
};

class IExeUnpack
{
public:
	virtual bool Initialize( LPCTSTR sz7z, LPCTSTR szwcx ) = 0;
	virtual bool Extract(LPCTSTR szfile, LPCTSTR szpath, strings &files) = 0;
	virtual bool IsValid() const = 0;
};

class CExeUnpackPkg : public IExeUnpack
{
public:
	CExeUnpackPkg(){}
	~CExeUnpackPkg(){}
	bool Initialize(LPCTSTR sz7z, LPCTSTR szwcx )
	{
		return true;
	}
	bool IsValid() const;
	bool Extract(LPCTSTR szfile, LPCTSTR szpath, strings &files);
};

class CUserPatcher
{
public:
	CUserPatcher()
	{
		m_objUpk = new CExeUnpackPkg;
	}
	virtual ~CUserPatcher()
	{
		if (m_objUpk)
		{
			delete m_objUpk;
			m_objUpk = NULL;
		}
	}

	bool Initialize( LPCTSTR sz7z, LPCTSTR szwcx );
	int InstallPatch(LPCTSTR szfile, const T_UserPatchInfo &unpkinfo);
	
protected:
	int _Patch(LPCTSTR szfile, const T_UserPatchInfo &unpkinfo, const char *szdirBackup, CString &strLogfile);
	void _FillRegInfo(INT nKBID, LPCTSTR szPatchName, LPCTSTR szProductKey, LPCTSTR szPatchKey, LPCTSTR szPatchValue, LPCTSTR szLogfile);
	void _GetDateString( CString &strDate );

protected:
	IExeUnpack* m_objUpk;
	strings m_files;
};
