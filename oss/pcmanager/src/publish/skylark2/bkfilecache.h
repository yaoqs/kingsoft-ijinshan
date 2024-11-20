/**
* @file    bkfilecache.h
* @brief   ...
* @author  ����
* @date    2010-7-12 14:42
*/

#ifndef BKFILECACHE_H
#define BKFILECACHE_H

#include <unknwn.h>
#include "skylarkbase.h"
#include "bkengdef.h"
#include "bklevel.h"

/**
* @brief �ļ�Cache����ӿ�
*/
class __declspec(uuid("18E73B75-01C8-408c-AC81-A935113E6DBA"))
IBKFileCache : public IUnknown
{
public:
	/**
	* @brief        ��ʼ���ļ�Cache����
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE Initialize() = 0;


	/**
	* @brief        ����ʼ���ļ�Cache����
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE Uninitialize() = 0;

	/**
	* @brief        ����ѯ���ļ�������и���
	* @param[in]    lpszFilePath    ԭʼ�ļ�·��
	* @param[in]    dwFileLevel     �ļ��ļ�����Խ�ɽ�Ʋ�ɱ���ֵĲ�����ʹ��SLPTL_LEVEL_MARK___BLACK_AUTO(50)
	* @param[in]    lpszVirusName   ������
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE UpdateCloudPEFile(
		LPCWSTR             lpszFilePath,
		DWORD               dwFileLevel,
		LPCWSTR             lpszVirusName
		) = 0;

	/**
	* @brief        ��������������ݿ�
	* @return       ��0Ϊʧ��
	*/
	virtual HRESULT STDMETHODCALLTYPE FlushToDB() = 0;
};


#endif // BKFILECACHE_H