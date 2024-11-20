/**
* @file    bkunknownreport.h
* @brief   ...
* @author  ����
* @date    2010-7-12 14:42
*/

#ifndef BKUNKNOWNREPORT_H
#define BKUNKNOWNREPORT_H

#include <unknwn.h>
/**
* @brief δ֪�ļ��ϴ��ӿ�
*/
class __declspec(uuid("663D4B88-5CD3-4801-BBEA-5E7B4875464A"))
IBKUnknownFileReport
{
public:
	/**
	* @brief        ���δ֪�ļ����ϴ��б�
	* @param[in]    lpszFilePath    ԭʼ�ļ�·��
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE AddUnknownFile(
		LPCWSTR             lpszFilePath
		) = 0;

	/**
	* @brief        ���ļ��ϴ��������
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE Report() = 0;

	/**
	* @brief        �Ƿ�Ϊ�Զ��ϴ��������
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE IsAutoReport(
		BOOL& bIsAutoReport
		) = 0;
};

#endif // BKUNKNOWNREPORT_H
