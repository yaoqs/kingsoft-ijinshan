#pragma once
#include <string>
/**
*  ������Ҫʵ�ַ��ʿ���
*/
class KAccessControl
{
public:
	/**
	* @brief   ����Ȩ��
	* @param   hToken Access token handle
	* @param   privilegeName The name of privilege to enable/disable
	* @param   enablePrivilege To enable or disable privilege
	* @return  bool
	* @example:
	*  HANDLE handle = GetCurrentProcess();
	HANDLE hToken = NULL;		
	OpenProcessToken(handle,(TOKEN_ADJUST_PRIVILEGES |TOKEN_QUERY),&hToken);
	SetPrivilege(hToken, SE_RESTORE_NAME, true);
	CloseHandle(hToken);
	CloseHandle(handle);
	*/
	static bool SetPrivilege(
		HANDLE hToken,          
		const std::wstring&  privilegeName, 
		bool enablePrivilege = true  
		);


	/**
	* @brief   ���õ�ǰ���̵�Ȩ��
	* @param   wstring privilegeName
	* @param   bool enablePrivilege
	* @return  bool
	*/
	static bool SetCurrentProcessPrivilege(const std::wstring&  privilegeName, 
		bool enablePrivilege = true );
};
