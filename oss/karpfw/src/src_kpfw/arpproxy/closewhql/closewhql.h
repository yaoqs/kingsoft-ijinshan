
#ifndef CCLOSEWHQL_H_08_07_03
#define CCLOSEWHQL_H_08_07_03

//�� vista ����Ҫ�� ����ԱȨ�޲�������ʹ��

typedef struct tagEnumReturn
{
	TCHAR * tszName;
	BOOL   bRetCode;
}EnumReturn;

class CCloseWHQL
{

public:

	CCloseWHQL();
	~CCloseWHQL();

	//�ⲿֻ�����������������
	BOOL StartCloseThread();
	void EndCloseThread();

	void SetDlgName(LPTSTR lpDlgName);
	static DWORD WINAPI _CloseThread( LPVOID lpParameter );

protected:

	HANDLE m_hThread;

};

#endif //CCLOSEWHQL_H_08_07_03