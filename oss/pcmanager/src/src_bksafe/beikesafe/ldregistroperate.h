#pragma once

#include "strsafe.h"

namespace RegisterOperate
{
#define REGPATH_MAX_LEN 512
#define FILEPATH_MAX_LEN 512
#define DEFAULT_BUFFER_MAX_LEN 50




#define ZEROMEM(x) ZeroMemory(x, sizeof(x))
#define SAFE_DELETE_PTR(x) if ((NULL != x)){delete (x); x = NULL;}
#define SAFE_DELETE_ARRAY_PTR(p)	if((p)){delete [](p);(p)=NULL;}
	//�ڲ��Լ�ʹ��
#define STRPRINF_STR(x,y) StringCbPrintf((x), sizeof((x)), TEXT("%s"), (y));
#define STRPRINF_INT(x,y) StringCbPrintf((x), sizeof((x)), TEXT("%d"), (y));
#define STRPRINF(x,y,z) StringCbPrintf((x), sizeof((x)), (y), (z));
#define STRCPY(x,y) StringCbCopy((x), sizeof((x)), (y));

	typedef struct _CLSID_STRUCT
	{
		WORD cbSize;
		WCHAR _pszFullRegPath[REGPATH_MAX_LEN];
		WCHAR _pszCLSID[DEFAULT_BUFFER_MAX_LEN];
		WCHAR _pszFileFullPath[FILEPATH_MAX_LEN];
		WCHAR _pszFileRegPath[REGPATH_MAX_LEN];
		WCHAR _pszDes[DEFAULT_BUFFER_MAX_LEN];
		_CLSID_STRUCT()
		{
			cbSize = sizeof(_CLSID_STRUCT);
			ZEROMEM(_pszCLSID);
			ZEROMEM(_pszFileRegPath);
			ZEROMEM(_pszFileFullPath);
			ZEROMEM(_pszFullRegPath);
			ZEROMEM(_pszDes);
		}
	}CLSID_STRUCT , *LPCLSID_STRUCT;

	class CRegisterOperate
	{
	public:
		~CRegisterOperate(void);
		static CRegisterOperate* GetRegOperatePtr()
		{
			static CRegisterOperate regOp;
			return &regOp;
		}
		//��ȡע���ֵ(�ַ���),����ڵ��û�ȡע���ֵ�ĺ����ǣ�ע����������ַ��ͣ������Ƕ��ֽ��ͣ�����û�е���ר�ŵĶ��ֽں��������Ƿ���
		//��ֵ������Ѷ��ֽ��е�ÿһ����Ϣ�Σ�ƴ�ӵ������ַ����У��м�ʹ�ÿո����ָ�
		int GetRegValue(HKEY hKey, LPCTSTR pszSubPath, LPCTSTR pszName, LPTSTR pszValue, DWORD cbSize);
		//��ȡע���ֵ(��ֵ��)
		int GetRegValue(HKEY hKey, LPCTSTR pszSubPath, LPCTSTR pszName, DWORD& dwValue);
		//��ȡ������ֵ
		int GetBinaryRegValue(HKEY hKey, LPCTSTR pszSubPath, LPCTSTR pszName, LPBYTE pByteValue, DWORD cbSize);
		//���ö�����ֵ
		int SetBinaryRegValue(HKEY hKey, LPCTSTR pszSubPath, LPCTSTR pszName, LPCBYTE pByteValue, DWORD cbSize);
		//��ȡ���ֽ��ַ�ֵ
		int GetRegValue(HKEY hKey, LPCTSTR pszSubPath, LPCTSTR pszName, CAtlArray<CString>& arrString);
		//��ȡע����ֵ���ͣ���Ϊ��Ҫ���ݲ�ͬ�����ͣ����ò�ͬ�Ľӿ�
		DWORD GetRegType(HKEY hKey, LPCTSTR pszSubPath, LPCTSTR pszName);
		//ö���Ӽ�
		int EnumSubKey(HKEY hKey, LPCTSTR pszSubPath, CAtlArray<CString>& arrKey);
		//ö��CLSID(������棬����ö�ٵ�ָ��·���µ�CLSID�Լ�CLSID��Ӧ���ļ���·��)
		int EnumCLSIDAndFile(HKEY hKEY, LPCTSTR pszSubPath, CAtlArray<CLSID_STRUCT>& arrClsid);
		// ����ע����ֵ REG_SZ
		int SetRegValue(HKEY hKey, LPCTSTR pszSubPath, LPCTSTR pszName, LPCTSTR pszValue, DWORD cbSize);
		int SetRegValue2(HKEY hKey, LPCTSTR pszSubPath, LPCTSTR pszName, LPCTSTR pszValue, DWORD cbSize);
		// ����ע����ֵ REG_DWORD
		int SetRegValue(HKEY hKey, LPCTSTR pszSubPath, LPCTSTR pszName, DWORD dwValue);
		//ɾ����ֵ
		int DeleteRegValue(HKEY hKey, LPCTSTR pszSubPath, LPCTSTR pszName);
		//ɾ����
		int DeleteAnKey(HKEY hKey, LPCTSTR pszSubPath);
		//���ע�����Ƿ����
		int KeyIsExist(HKEY hKey, LPCTSTR pszSubPath);
		//ö�ټ�ֵ
		int EnumRegValue(HKEY hKey, LPCTSTR pszSubPath, CAtlArray<CString>& arrRegValue);
		//�����Ӽ�
		int CreateAnKey(HKEY hKey, LPCTSTR pszSubPath, HKEY &hNewKey);
	private:
		CRegisterOperate(void);
		//��ע����
		HKEY _OpenKey(HKEY hKey, LPCTSTR pszSubPath); 
		void _CloseKey(HKEY hKey);
		//��ȡREG_SZע����ֵ
		int _GetValue(HKEY hKey, LPCTSTR pszName, LPTSTR pszValue, DWORD dwType, DWORD cbSize, DWORD cbSize2);
		//��ȡREG_MUL_SZע����ֵ
		int _GetValue_Mul_SZ(HKEY hKey, LPCTSTR pszName, LPTSTR pszValue, DWORD dwType, DWORD cbSize);
		//�������ֽ��ַ���������ÿһ�������ķŵ�arrStr��
		int _ParseMulSzBuf(LPCTSTR pszBuf, CAtlArray<CString>& arrStr);
	};
}


