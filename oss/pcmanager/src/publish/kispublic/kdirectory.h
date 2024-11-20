#pragma once
#include "public.h"

NS_BEGIN(KIS)
NS_BEGIN(IO)
NS_BEGIN(KDirectory)

/*
* @brief								����ָ�����ļ�Ŀ¼��
* @param lpFilePath					--- ָ����Ҫ�������ļ��е�ȫ·��
* @remark							--- �ú����ᴴ���ļ���·���µ�����Ŀ¼���������̷���
*										�磺lpStrFilePath == c:\\a\\b\\c\\
*										���ñ���������ᴴ��c:\\a; c:\\a\\b; c:\\a\\b\\c\\ ����Ŀ¼
* @return 
*							   TRUE --- �����ɹ�
*							   FALSE--- ����ʧ��
*/
STDAPIN_(int)  CreateDirA(IN LPCSTR lpStrFilePath);
STDAPIN_(int)  CreateDirW(IN LPCWSTR lpStrFilePath);

/*
* @brief								���������ļ�����ָ�����ļ�Ŀ¼�����Ǵ���֮ǰ�Ὣ�ļ������
* @param lpFilePath					--- ָ����Ҫ�������ļ��е�ȫ·��
* @remark							--- �ú����ᴴ�������ļ�����ָ�����ļ�Ŀ¼�����Ǵ���֮ǰ�Ὣ�ļ������
*										�磺lpFileFullName == c:\\a\\b\\c.exe
*										���ñ���������ᴴ��c:\\a c:\\a\\b��Ŀ¼,������CreateDirAһ��
* @return 
*							   TRUE --- �����ɹ�
*							   FALSE--- ����ʧ��
*/
STDAPIN_(int)  CreateDirCleanFileNameA(IN LPCSTR lpFileFullName);
STDAPIN_(int)  CreateDirCleanFileNameW(IN LPCWSTR lpFileFullName);


/*
* @brief								ɾ���ļ��м���������ļ���
* @param lpFolderPath				--- ָ������Ҫɾ�����ļ���
* @param bDeleteReboot				--- ����ļ���ɾ��ʧ�ܣ�ָ���Ƿ�����ɾ����Ĭ��Ϊ����ɾ��
* @remark							--- ɾ��ָ�����ļ��У�����ļ����ﻹ���ļ��У���ȫ��ɾ����
* @return 
*							   TRUE --- ɾ���ɹ�
*							   FALSE--- ɾ��ʧ��
*/
STDAPIN_(int)  DeleteDirA(IN LPCSTR lpFolderPath, IN BOOL bDeleteReboot = TRUE);
STDAPIN_(int)  DeleteDirW(IN LPCWSTR lpFolderPath, IN BOOL bDeleteReboot = TRUE);


/*
* @brief								�����ļ��С�
* @param lpSrcDir					--- ָ������Ҫ�������ļ���Ŀ¼
* @param lpDstDir					--- ָ���Ŀ��������ļ��е�Ŀ¼
* @param nFailedIfExist				--- ָ������ļ����ڣ��Ƿ����������TRUEΪ����������FALSEΪ����������Ĭ��ΪTRUE
* @return 
*							   TRUE --- ����
*							   FALSE--- ������
*/
STDAPIN_(int)  CopyDirA(IN LPCSTR lpSrcDir, IN LPCSTR lpDstDir, IN int nFailedIfExist = TRUE);
STDAPIN_(int)  CopyDirW(IN LPCWSTR lpSrcDir, IN LPCWSTR lpDstDir, IN int nFailedIfExist = TRUE);


NS_END(KDirectory)

NS_END(IO)
NS_END(KIS)




