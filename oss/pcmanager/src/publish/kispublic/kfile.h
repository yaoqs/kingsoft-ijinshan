#pragma once
#include "public.h"

NS_BEGIN(KIS)
NS_BEGIN(IO)
NS_BEGIN(KFile)

/*
* @brief								�ж��ļ����ļ����Ƿ���ڡ�
* @param lpFilePath					--- ָ����Ҫ�жϵ��ļ�ȫ·��
* @remark							--- ʹ��GetFileAttributes�������ж��ļ��Ƿ����
*										ʹ�ø÷����ĺô����ڣ����Խ��ļ�ȫ·�����ַ����������ӵ�32767���ַ���
*										ͬʱ�ܹ�֧��"\\?\"��·����ʽ��
* @return 
*							   TRUE --- ����
*							   FALSE--- ������
*/
STDAPIN_(int)  FileExistsA(LPCSTR lpFilePath); 
STDAPIN_(int)  FileExistsW(LPCWSTR lpFilePath); 

/*
* @brief								��ȡ�ļ��Ĵ�С��
* @param lpFilePath					--- ָ���ļ���ȫ·��
* @param uFileSize					--- �ļ��Ĵ�С
* @return 
*							   TRUE --- �ɹ�
*							   FALSE--- ʧ��
*/
STDAPIN_(int)  GetFileSizeA(IN LPCSTR lpStrFilePath, OUT size_t& uFileSize);
STDAPIN_(int)  GetFileSizeW(IN LPCWSTR lpStrFilePath, OUT size_t& uFileSize);

/*
* @brief								ɾ��ָ�����ļ���
* @param lpFilePath					--- ָ������Ҫɾ�����ļ�
* @param bDeleteReboot				--- ����ļ�ɾ��ʧ�ܣ�ָ���Ƿ�����ɾ����Ĭ��Ϊ����ɾ��
* @return 
*							   TRUE --- �ɹ�
*							   FALSE--- ʧ��
*/
STDAPIN_(int)  DeleteFileA(IN LPCSTR lpFilePath, IN BOOL bDeleteReboot = TRUE);
STDAPIN_(int)  DeleteFileW(IN LPCWSTR lpFilePath, IN BOOL bDeleteReboot = TRUE);


/*
* @brief								ɾ���ļ�������������֮��
* @param lpFilePath					--- ָ������Ҫɾ�����ļ�
* @return 
*							   TRUE --- �ɹ�
*							   FALSE--- ʧ��
*/
STDAPIN_(int)  MoveFileRebootA(IN LPCSTR lpFilePath);
STDAPIN_(int)  MoveFileRebootW(IN LPCWSTR lpFilePath);

/*
* @brief								�����ļ�
* @param lpFilePathSrc				--- ָ����Ҫ���������ļ�·��
* @param lpFilePathDes				--- ָ�����������ļ�·��
* @param bFailIfExist				--- ���ʧ�ܾͲ�����
* @return 
*							   TRUE --- �ɹ�
*							   FALSE--- ʧ��
*/
STDAPIN_(int)  CopyFileA(IN LPCSTR lpFilePathSrc, IN LPCSTR lpFilePathDes, IN BOOL bFailIfExist = FALSE);
STDAPIN_(int)  CopyFileW(IN LPCWSTR lpFilePathSrc, IN LPCWSTR lpFilePathDes, IN BOOL bFailIfExist = FALSE);


/*
* @brief								��ȡ�ļ��汾��
* @param lpFilePath					--- ָ����Ҫ��ѯ���ļ��汾�ŵ��ļ�
* @param pdwFileVersionMS			--- ָ���ļ��İ汾�ţ���λ��
* @param pdwFileVersionLS			--- ָ���ļ��İ汾�ţ���λ��
* @return 
*							   TRUE --- �ɹ�
*							   FALSE--- ʧ��
*/
STDAPIN_(int) GetFileVersionDWORDA(IN LPCSTR lpFilePath, IN OUT DWORD *pdwFileVersionMS, IN OUT DWORD *pdwFileVersionLS);
STDAPIN_(int) GetFileVersionDWORDW(IN LPCWSTR lpFilePath, IN OUT DWORD *pdwFileVersionMS, IN OUT DWORD *pdwFileVersionLS);

/*
* @brief								��ȡ�ļ��汾��
* @param lpFilePath					--- ָ����Ҫ��ѯ���ļ��汾�ŵ��ļ�
* @param lpVersion					--- �ļ��İ汾��
* @param nVersionSize				--- ָ���ַ����ĳ��ȣ������صĵ�ǰ�ַ����ĳ���
* @return 
*							   TRUE --- �ɹ�
*							   FALSE--- ʧ��
*/
STDAPIN_(int) GetFileVersionStrA(IN LPCSTR lpFilePath, IN OUT LPSTR lpVersion, IN int& nVersionSize);
STDAPIN_(int) GetFileVersionStrW(IN LPCWSTR lpFilePath, IN OUT LPWSTR lpVersion, IN int& nVersionSize);

NS_END(KFile)
NS_END(IO)
NS_END(KIS)




