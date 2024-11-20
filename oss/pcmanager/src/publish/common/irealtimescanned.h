/** 
* @file irealtimescanned.h
* @brief ����ɨ����Ļ�ɨ�ļ���ѯ�ӿ�
* @author BAO<baoderong@kingsoft.com>
* @date November 11,2010
*/

#ifndef IREALTIMESCANNED_H
#define IREALTIMESCANNED_H

#include <Unknwn.h>

#include "bkrescanbasedata.h"

/** 
* @interface IBKRSRTScanned
* @brief ʵʱ�����ļ���ѯ
*/
interface __declspec(uuid("132FABB8-0D2B-495b-B274-1FF524392F7A"))
IBKRSRTScanned : public IUnknown
{
public:
	/** 
	* @brief ��ѯһ���ɨ�ļ�
	* @details Ϊ�˼ӿ��ٶȣ�����uMaxCountΪ0ʱ��ȡ�ļ�¼��δ���ļ���Դ���ǣ���ȡ�ļ�¼Ϊ���ڵ���
	*	��ʱ�ģ����ݿ��ǲ��ϱ仯�ģ������õ�ʱ����¼��
	*
	* @param[in] const BKRS_RTScannedQueryType enumQurerType Ҫ��ѯ���ļ�����
	* @param[in] const BKRS_FileFromType enumFromType ��ѯ���ļ���Դ����
	* @param[in] const uint32_t uMaxCount ��󷵻��ļ�������Ϊ0ʱ��puGetCount�������������������ļ�����
	* @param[in] const uint32_t uWaitSeconds �ȴ����ݿ���ʱ�䣬�������ݿ��Ǳ�����̷��ʵ�
	* @param[out] BKRS_QueryFileInfo *pstQueryResult �����ѯ����ӿ�	
	* @param[out] uint32_t *puGetCount ���ػ�ȡ���ļ���¼��
	* @return ��׼��HRESULTֵ
	*
	* @attention �������ݿ��ǲ��ϵĸ��µģ��������״λ�ȡ��¼�����󣬵ڶ��ν�ռ��ȡ��¼ʱ����ö��Щ
	*	��¼�ռ䣬�Ա��ܻ�ȡ���������������ļ�¼
	*/
	virtual HRESULT __stdcall QueryFiles(
		const BKRS_RTScannedQueryType enumQurerType, 
		const BKRS_FileFromType enumFromType, 
		const uint32_t uMaxCount, 
		const uint32_t uWaitSeconds, 
		BKRS_QueryFileInfo *pstQueryResult, 
		uint32_t *puGetCount) = 0;

	/** 
	* @brief ɾ��ĳЩɨ������ļ�
	* @details �������ݿ��ڲ����ڸ��£������ṩɾ��ĳ�������ļ�������ɾ���˲�Ӧ��ɾ�����ļ�
	*
	* @param[in] const BKRS_QueryFileInfo *pstQueryResult ��Ҫɾ�����ļ���¼
	* @param[in] const uint32_t uFileCount Ҫɾ�����ļ���¼����
	* @param[in] const BKRS_FileFromType enumFromType �ļ���Դ����
	* @param[in] const uint32_t uWaitSeconds �ȴ����ݿ���ʱ�䣬�������ݿ��Ǳ�����̷��ʵ�
	* @return ��׼��HRESULTֵ
	*/
	virtual HRESULT __stdcall RemoveFiles(
		const BKRS_QueryFileInfo *pstQueryResult, 
		const uint32_t uFileCount, 
		const BKRS_FileFromType enumFromType, 
		const uint32_t uWaitSeconds) = 0;	

	/** 
	* @brief ����ĳЩɨ������ļ�״̬
	* @details Ŀǰֻ���´���״̬
	*
	* @param[in] const BKRS_QueryFileInfo *pstQueryResult Ҫ���µ��ļ���¼
	* @param[in] const uint32_t uFileCount Ҫ���µ��ļ���¼����
	* @param[in] const uint32_t uWaitSeconds �ȴ����ݿ���ʱ�䣬�������ݿ��Ǳ�����̷��ʵ�
	* @return ��׼��HRESULTֵ
	*/
	virtual HRESULT __stdcall UpdateFiles(
		const BKRS_QueryFileInfo *pstQueryResult, 
		const uint32_t uFileCount, 
		const uint32_t uWaitSeconds) = 0;

	/** 
	* @brief ���½����ѯ��ʼ������
	*
	* @param ��
	* @return ��׼��HRESULTֵ
	*/
	virtual HRESULT __stdcall Initialize() = 0;

	/** 
	* @brief ���½������ʼ������
	*
	* @param ��
	* @return ��׼��HRESULTֵ
	*/
	virtual HRESULT __stdcall UnInitialize() = 0;
};

#endif

