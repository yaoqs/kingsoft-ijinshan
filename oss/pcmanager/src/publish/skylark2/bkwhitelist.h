/**
* @file    bkwhitelist.h
* @brief   ...
* @author  ����
* @date    2010-7-12 14:42
*/

#ifndef BKWHITELIST_H
#define BKWHITELIST_H

#include <unknwn.h>
/**
* @brief �������ļ�ƥ��ӿ�
*/
class __declspec(uuid("59602084-0E12-4218-96EE-2B49158B8655"))
IBKUserWhiteList
{
public:
	/**
	* @brief        ��ѯ�ļ��Ƿ����
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE Lookup(
		LPCTSTR lpszFileName,
		BOOL& bIsExist
		) = 0;
};

#endif // BKWHITELIST_H