#ifndef _IKAQ_FILEINFO_H_
#define _IKAQ_FILEINFO_H_


#include "unknwn.h"

// {7DC323FF-7266-4bca-B157-69D2D4BDE093}
extern const GUID IID_KAQFILEINFO;


#define E_BUFFER_TOO_SMALL    0x84000321


/** \class IKAQFileInfo
* \brief ö���ļ���Ϣ�ӿ�
*/
class IKAQFileInfo : public IUnknown
{
public:
	/** \brief  �����ļ�������ʱ��
	*   \param  index  �ļ����� (��0��������1)
	*   \param  pTime  ���ش��������ļ�ʱ��
	*   \return �ɹ�����S_OK
	*/
	virtual HRESULT STDMETHODCALLTYPE getCreateTime(
		unsigned int index, SYSTEMTIME* pTime) = 0;

	/** \brief  �����ļ���
	*   \param  index         �ļ����� (��0��������1)
	*   \param  pQurantFile   ���ո����ļ���������
	*   \param  ulSizeOfName  ���ջ�������С
	*   \return ������ջ�����С���ļ�������E_BUFFER_TOO_SMALL��
	*           �ɹ�����S_OK
	*/
	virtual HRESULT STDMETHODCALLTYPE getQurantFileName(
		unsigned int index, wchar_t* pQurantFile, unsigned long ulSizeOfName) = 0;

	/** \brief  ���벡����
	*   \param  index        �ļ����� (��0��������1)
	*   \param  pVirusName   ���ղ�����������
	*   \param  ulSizeOfName ���ջ�������С
	*   \return ������ջ�����С���ļ�������E_BUFFER_TOO_SMALL��
	*           �ɹ�����S_OK
	*/
	virtual HRESULT STDMETHODCALLTYPE getVirusName(
		unsigned int index, wchar_t* pVirusName, unsigned long ulSizeOfName) = 0;

	/** \brief  ����ԭʼ�ļ���
	*   \param  index        �ļ����� (��0��������1)
	*   \param  pVirusName   ����ԭʼ�ļ���������
	*   \param  ulSizeOfName ���ջ�������С
	*   \return ������ջ�����С���ļ�������E_BUFFER_TOO_SMALL��
	*           �ɹ�����S_OK
	*/
	virtual HRESULT STDMETHODCALLTYPE getOrignFileName(
		unsigned int index, wchar_t* pFileName, unsigned long ulSizeOfName) = 0;

	/** \brief  �õ������ļ�����
	*   \param  pCount  �����ļ�����
	*   \return �ɹ�����S_OK
	*/
	virtual HRESULT STDMETHODCALLTYPE getQurantFileCount(unsigned long* pCount) = 0;
};


#endif