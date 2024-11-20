#ifndef  _REGOPT_H_
#define  _REGOPT_H_

#include <windows.h>
#include <atlstr.h>
#include <process.h>
#include <atlconv.h>
#include <atlcoll.h>



#define BEGIN		{
#define END			}

#define		ERROR_NOMEMOEY		0xFF0001;	//�ڴ治��
#define		ERROR_NOFAILKEY		0xFF0002;	//��Ч��ֵ
#define		ERROR_NODEF			0xFF0003	//��ЧĬ��ֵ


typedef struct _REGVALUE
{	
	//ֵ��
	CString		strValueName;	
	//����
	DWORD		dwType;
	CString		strValue;

}REGVALUE;

typedef CSimpleArray<REGVALUE> VALUEINFO; 

/************************************************************************/
//����ֵ�����Ƿ�����ݹ�ö��
//HKEY		rootKey			����
//LPCTSTR	lpItemOrKey		ע�����·��
//LPCTSTR	lpName			ֵ��
//LPBYTE	lpValue			ֵ
//DWORD		dwType			ֵ����
//void*		pUserData		�Զ�������
/************************************************************************/
typedef BOOL (WINAPI *EnumerateRegFun) (HKEY rootKey,LPCTSTR lpItemPath,LPCTSTR lpName,DWORD dwValueNameSize,LPBYTE lpValue ,DWORD dwValueSize,DWORD dwType,void* pUserData);

class CRegOpt
{
public:
	CRegOpt(){ s_bUserBreak = FALSE; };
	~CRegOpt(){};
public:
	//ö�����м�ֵ
	void	DoRegEnumeration(HKEY rootKey,LPCTSTR lpItemPath,EnumerateRegFun fnRegFun,void* pUserData=NULL);

	//��õ�ǰ���µ������Ӽ�
	BOOL	DoEnumCurrnetSubKeyEx(HKEY hRootKey,LPCTSTR lpcKey,CSimpleArray<CString>& vec_Key,BOOL bRes=FALSE,BOOL bFullPath =FALSE);
	BOOL	DoEnumCurrnetSubKey(HKEY hRootKey,LPCTSTR lpcKey,CSimpleArray<CString>& vec_Keys);
	BOOL	DoEnumCurrnetSubKey(HKEY hRootKey,LPCTSTR lpcKey,CAtlMap<CString,char>& map_Keys);
	//��õ�ǰ���µ�����ֵ,���bResΪ������еݹ�����ö��
	BOOL	DoEnumCurrnetValue(HKEY hRootKey,LPCTSTR lpcKey,
				CSimpleArray<REGVALUE>& vec_Value,BOOL bRes=FALSE
				);

	BOOL	CrackRegKey(wchar_t* regstring,HKEY& root, wchar_t*& subkey,wchar_t*& value);
	//��ø������Ӽ�
	BOOL	CrackRegKey(CString& strRegPath,HKEY& root,CString& strSubKey);

	//ɾ���Ӽ�
	BOOL	RegDelnode(HKEY hKeyRoot, LPCTSTR lpSubKey);
	//ɾ��ֵ
	BOOL	RegDelValue(HKEY hKeyRoot,LPCTSTR lpSubKey,LPCTSTR lpValue);
	//���Ƿ����
	BOOL	FindKey(HKEY hKeyRoot,LPCTSTR lpSubKey);
	//���ָ������Ĭ��ֵ
	BOOL	GetDefValue(HKEY hKeyRoot,LPCTSTR lpSubKey,CString& ValueName,CString& Value);
	//��ô�����
	DWORD	GetErrorCode();
	//
	BOOL GetHKEYToString(HKEY hRootKey,LPCTSTR lpszSubKey,CString& strRegFullPath);
	
	void	UserBreadFlag(BOOL bUserBreak) { s_bUserBreak = bUserBreak; };
	BOOL	s_bUserBreak;
private:
	BOOL	RegDelnodeRecurse(HKEY hKeyRoot, LPTSTR lpSubKey);
private:
	DWORD	m_iErrCode;
};

#endif	//_REGOPT_H