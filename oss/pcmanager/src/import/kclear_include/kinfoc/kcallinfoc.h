#pragma once
#include <wtypes.h>
#include <string>
#include <deque>
using namespace std;

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

enum enumSendMode
{
	enumSendByGet = 1,
	enumSendByPost = 2,
};

typedef BOOL (__stdcall *DllSend)(int);
typedef BOOL (__stdcall *DllAddData)(LPCWSTR, LPCWSTR);
typedef BOOL (__stdcall *DllSetPublic)(LPCWSTR, LPCWSTR);
typedef void (__stdcall *DllCheckAndDelFiles)(int);
typedef BOOL (__stdcall *DllGetUUID)(LPWSTR, DWORD&);


class KCallInfoc
{
public:
	KCallInfoc(void);
	~KCallInfoc(void);

public:
	/*
	* @brief								��ʼ���������ҵ�kinfoc.dll��λ�ò����أ����Ե��ã�Ҳ���Բ����á�
	* @param lpStrFilePath				--- �ļ�·����Ĭ��Ϊȥ�Լ�ȥ����
	* @return 
	*							   TRUE --- �ɹ�
	*							   FALSE--- ʧ��
	*/
	BOOL Init(IN const wchar_t* lpStrFilePath = NULL);

	/*
	* @brief								����ʼ��
	* @return 
	*							   TRUE --- �ɹ�
	*							   FALSE--- ʧ��
	*/
	BOOL Unit();

	/*
	* @brief								��ӹ����ļ���������ļ����ڣ�����滻
	* @param lpStrActionName			--- ����������duba_install(���԰�װ)
	* @param lpStrData					---	��Ҫ��ӵ��ļ��е�����,ÿ����ʹ��'&'����(eg:a=1&b=2&c=3)
	* @param lpStrFilePath				--- ָ����kinfoc���ļ���·����Ĭ��Ϊ��
	* @return 
	*							   TRUE --- ��ӳɹ�
	*							   FALSE--- ���ʧ��
	*/
	BOOL SetPublicFile(IN const wchar_t* lpStrPublicFileName, IN const wchar_t* lpStrPublicData, IN const wchar_t * lpStrFilePath = NULL);
	
	/*
	* @brief								�������
	* @param lpStrActionName			--- ����������duba_install(���԰�װ)
	* @param lpStrData					---	��Ҫ��ӵ��ļ��е�����,ÿ����ʹ��'&'����(eg:a=1&b=2&c=3)
	* @param lpStrFilePath				--- ָ����kinfoc���ļ���·����Ĭ��Ϊ��
	* @return 
	*							   TRUE --- ��ӳɹ�
	*							   FALSE--- ���ʧ��
	*/
	BOOL AddData(IN const wchar_t * lpStrActionName, IN const wchar_t * lpStrData, IN const wchar_t * lpStrFilePath = NULL);

	/*
	* @brief								��������
	* @param enumMode					--- ָ�����͵�ģʽ��Ĭ��Ϊʹ��GET�ķ�ʽ��������
	* @param lpStrFilePath				--- ָ����kinfoc���ļ���·����Ĭ��Ϊ��
	* @return 
	*							   TRUE --- ���ͳɹ�
	*							   FALSE--- ����ʧ��
	*/
	BOOL SendData(IN enumSendMode enumMode = enumSendByGet, IN const wchar_t * lpStrFilePath = NULL );

	/*
	* @brief								ɾ�����е��ļ������ļ����е��ļ�����ĳһ����ʱ
	* @param nNum						--- ���õ��ļ��������ٸ���ʱ��ɾ���ļ�
	* @param lpStrFilePath				--- ָ����kinfoc���ļ���·����Ĭ��Ϊ��
	*/
	void CheckAndDelFiles(IN int nNum, IN const wchar_t * lpStrFilePath = NULL);

	BOOL AddDataEx(IN const wchar_t * lpStrActionName, IN const wchar_t * lpStrData);

private:
	BOOL _GetKInfocPath(OUT std::wstring& strInfocPath);
	BOOL _CheckFileFromReg(OUT std::wstring& strFilePath);
	BOOL _ReadOneRegKey(OUT wchar_t* lpszResult, IN long dwOutMaxSize);

private:
	HMODULE m_hMoudle;
	BOOL m_bIsInit;

private:
	DllSetPublic m_pSendData;
	DllAddData m_pAddData;
	DllSend m_pSend;
	DllCheckAndDelFiles m_pCheckAndDelFiles;
	DllGetUUID m_GetUUID;
};
