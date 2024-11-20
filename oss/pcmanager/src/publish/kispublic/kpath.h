#pragma once
#include "public.h"

NS_BEGIN(KIS)
NS_BEGIN(IO)
NS_BEGIN(KPath)

/*
* @brief								��ȡ��ʿOEM��Ŀ¼��
* @param lpOemPath					--- ���صĽ�ɽ��ʿ��OEM��Ŀ¼���������ΪNULL,��nSize����ʵ����Ҫ�Ĵ�С�����صĽ��������'\\'
* @param nSize						--- ָ�����ĳ��ȣ�����ʵ����Ҫ�ĳ��ȣ��������ʧ�ܣ�nSizeΪʵ����Ҫ�Ĵ�С
* @remark							--- ����ʹ�ã�

std::wstring strValue;
CallFunc<int, LPWSTR, size_t&>(KIS::IO::KPath::GetKafeOemPathW, strValue);
* @return 
*							   TRUE --- �ɹ�
*							   FALSE--- ʧ��
*/
STDAPIN_(int)  GetKafeOemFilePathA(OUT LPSTR lpOemPath, IN OUT size_t& nSize); 
STDAPIN_(int)  GetKafeOemFilePathW(OUT LPWSTR lpOemPath, IN OUT size_t& nSize); 

/*
* @brief								�õ���ǰ���õĽ������ڵ��ļ���·����
* @param lpOemPath					--- ���صĽ�ɽ��ʿ��OEM��Ŀ¼���������ΪNULL,��nSize����ʵ����Ҫ�Ĵ�С�����صĽ��������'\\
* @param nSize						--- ָ�����ĳ��ȣ�����ʵ����Ҫ�ĳ��ȣ��������ʧ�ܣ�nSizeΪʵ����Ҫ�Ĵ�С
* @remark							--- ����ʹ�ã�

std::wstring strValue;
CallFunc<int, LPWSTR, size_t&>(KIS::IO::KPath::GetCurDirectoryW, strValue);
* @return 
*							   TRUE --- �ɹ�
*							   FALSE--- ʧ��
*/
STDAPIN_(int)  GetCurDirectoryA(OUT LPSTR lpPath, IN OUT size_t& nSize); 
STDAPIN_(int)  GetCurDirectoryW(OUT LPWSTR lpPath, IN OUT size_t& nSize); 


/*
* @brief								�õ���ǰ���̵�ȫ·���������ļ�����
* @param lpOemPath					--- ���ص�ǰ���̵�ȫ·�����������ΪNULL,��nSize����ʵ����Ҫ�Ĵ�С
* @param nSize						--- ָ�����ĳ��ȣ�����ʵ����Ҫ�ĳ��ȣ��������ʧ�ܣ�nSizeΪʵ����Ҫ�Ĵ�С
* @remark							--- ����ʹ�ã�

std::wstring strValue;
CallFunc<int, LPWSTR, size_t&>(KIS::IO::KPath::GetCurFullPathW, strValue);
* @return 
*							   TRUE --- �ɹ�
*							   FALSE--- ʧ��
*/
STDAPIN_(int)  GetCurFullPathA(OUT LPSTR lpPath, IN OUT size_t& nSize); 
STDAPIN_(int)  GetCurFullPathW(OUT LPWSTR lpPath, IN OUT size_t& nSize); 


NS_END(KPath)
NS_END(IO)
NS_END(KIS)




