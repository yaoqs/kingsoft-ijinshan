/** 
* @file ibkrescan.h
* @brief ��ɨ�ļ��ӿ�
* @author BAO<baoderong@kingsoft.com>
* @date November 05,2010
*/

#ifndef IBKRESCAN_H
#define IBKRESCAN_H

#include "irescancallback.h"

#define BKRS_INSERTFROM_FASTSCAN 0x01			/// �ļ����Կ���ɨ��
#define BKRS_INSERTFROM_FILEMONITOR 0x02		/// �ļ������ļ����
#define BKRS_INSERTFROM_FULLDISKSCAN 0x04		/// �ļ�����ȫ��ɨ��
#define BKRS_INSERTFROM_RSS_KXESCANSP 0x08		/// �ļ����Զ��Բ�ɱsp#define BKRS_INSERTFROM_RSS_USBMONITOR 0x10		/// �ļ����Զ���U�̼��

#define BKRS_INSERTFROM_MASKCODE 0x1F			/// �ļ���Դ����
#define BKRS_INSERTFROM_COUNT 5					/// �ļ���Դ����

/** 
* @interface IBKReScan
* @brief ��ɨ�ļ��ӿ�
*/
interface __declspec(uuid("57F612D4-138D-4bae-A477-B3142E8DDC8D"))
IBKReScan : public IUnknown
{
public:
	/** 
	* @brief ����һ����ɨ�ļ�
	* @details �ļ����ļ���Ϊ�ؼ��֣����һ���ļ�ִ���������ֲ���֮һ
	*	1������ɨ�ļ��б����޴��ļ������ļ��������ݿ����
	*	2�����б����д��ļ�����MD5��ͬ����ִ���κβ������������ļ�
	*	3�����б����д��ļ�����MD5��ͬ���滻ԭ��ͬ���ļ����������ɨ��Ϣ
	*	��ֻ���ļ���Դ��ͬʱ�������ļ���Դ����������Դ
	*
	* @param[in] const wchar_t *pszFileName Ҫ��ӵĻ�ɨ�ļ���
	* @param[in] const BYTE pszMD5[16] ��ɨ�ļ���MD5����NULLʱ�һ��Լ�����MD5
	* @param[in] const wchar_t *pszFileChannel ��ɨ�ļ���ͨ����
	* @param[in] unsigned int uFlag �����ļ���Դ����ȫ�̣���ɨ����أ������԰�λ�򣬼�����궨��
	* @param[in|out] void *pvData ��ʱδ��
	* @return ��׼��HRESULTֵ
	*
	* @attention �˽ӿ�ֻ���ļ����뻺���У������ǿ������ݻ�û�в��뵽���ݿ���
	*/
	virtual HRESULT __stdcall InsertOneFile(
		const wchar_t *pszFileName,
		const BYTE pszMD5[16],
		const wchar_t *pszFileChannel, 
		unsigned int uFlag, 
		void *pvData = NULL) = 0;

	/** 
	* @brief ��ɨ��ʼ������
	*
	* @param[in] IReScanCallback *piReScan ��֪δ֪�ļ����ʱ�Ļص��ӿ�
	* @param[in] const wchar_t *pszChannnelName ��ɨ��ͨ����
	* @param[in] const wchar_t *pszChannnelKey ��ɨ��ͨ��key
	* @param[in|out] void *pvData ��ʱδ��
	* @return ��׼��HRESULTֵ
	*/
	virtual HRESULT __stdcall Initialize(
		IReScanCallback *piReScan, 
		const wchar_t *pszChannnelName,
		const wchar_t *pszChannnelKey) = 0;

	/** 
	* @brief ����ʼ������
	*
	* @param[in|out] void *pvData ��ʱδ��
	* @return ��׼��HRESULTֵ
	*/
	virtual HRESULT __stdcall UnInitialize() = 0;
};

#endif

