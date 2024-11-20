#pragma once
#include <string>

class KOpKsafeReg
{
public:

	static std::wstring ReplaceRegStr(IN LPCWSTR lpStr);

	//������ʿ��ע�����
	static BOOL CreateKsafeReg(LPCWSTR lpPath);

	//��ѯksafe����ؼ�ֵ�����ǲ���Ҫ����SOFTWARE\\KSafe
	//�磬Ҫ��SOFTWARE\\KSafe\\Coop �µ�PreOem��ֵ���������µ��ã�
	//std::wstring strValue;   QueryKsafePath(_T("Coop"), _T("PreOem"), strValue);
	static BOOL QueryKsafePath(std::wstring strKey, std::wstring strValueKey, OUT std::wstring& strValue);
	static BOOL QueryKsafePath(std::wstring strKey, std::wstring strValueKey, OUT DWORD& dwValue);
	static BOOL QueryKsafePath(std::wstring strKey, std::wstring strValueKey, OUT std::string& strValue);

private:
	static std::wstring _GetSubKeyStr(void);
};
