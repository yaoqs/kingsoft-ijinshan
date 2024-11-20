/** 
* @file irescancallback.h
* @brief ��֪�ļ��ڰ�ʱ���ļ��ص��ӿ��ඨ��
* @author BAO<baoderong@kingsoft.com>
* @date November 10,2010
*/

#ifndef IRESCANCALLBACK_H
#define IRESCANCALLBACK_H

/** 
* @interface IReScanCallback
* @brief ɨ������ļ��ص��ӿ�
*/
interface __declspec(uuid("269D58B4-3B39-405f-8439-C5A3178ABF73"))
 IReScanCallback : public IUnknown
{
public:

	/** 
	* @brief ��һ����֪�ڰ׵��ļ����ص�����
	*
	* @param[in] const wchar_t *pszFileName ��ɨ�ļ���
	* @param[in] BYTE pszMD5[16] ��ɨ�ļ���MD5
	* @param[in[ const wchar_t *pszChannel ��ɨ�ļ���ͨ����
	* @param[in] unsigned int uFlag �����ļ���Դ����ȫ�̣���ɨ����أ������԰�λ��
	* @param[in] const unsigned int uFileType �ļ����ͣ�0Ϊ�ף�1Ϊ�ڣ�3Ϊ�֣�4Ϊ����
	* @return ��׼��HRESULTֵ
	*/
	virtual HRESULT __stdcall NotifyFileResult(
		const wchar_t *pszFileName,
		const BYTE pszMD5[16], 
		const wchar_t *pszChannel,
		unsigned int uFlag, 
		unsigned int uFileType) = 0;
};

#endif
