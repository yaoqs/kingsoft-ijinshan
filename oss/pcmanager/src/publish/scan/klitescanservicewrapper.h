#pragma once
#include "kselitecanservice_def.h"

class ILiteScanService;

class KLiteScanServiceWrapper
{
public:
	KLiteScanServiceWrapper(void);
	~KLiteScanServiceWrapper(void);

	int Initialize();

	int Uninitialize();

	bool IsInitialized();

	/**
	* @brief        ����һ��ɨ��Ự
	* @param[out]   scanHandle    ���صĻỰ���
	* @return		0 �ɹ�,����Ϊʧ�ܴ�����
	* @remark       �̰߳�ȫ����, 
	*/
	virtual int __stdcall CreateScanSession(
		/* [in]  */ const KXE_NULL_PARAEMETER&,     
		/* [out] */ S_KSE_LITESCAN_SESSION& scanHandle
		);

	/**
	* @brief        �ر�һ��ɨ��Ự
	* @param[in]    ScanHandle ͨ��CreateScanSession��ȡ
	* @return		0 �ɹ�,����Ϊʧ�ܴ�����
	* @remark       �̰߳�ȫ����, ���ж��SessionʱΪ��֤�˳�Ч��,Ҫ���ź�NotifyStopScan()��CloseScanSession��˳��
	*/
	virtual int __stdcall CloseScanSession(
		/* [in] */ const S_KSE_LITESCAN_SESSION& ScanHandle,
		/* [out]*/ KXE_NULL_PARAEMETER& nullParm
		);


	/**
	* @brief        ֪ͨɨ��Ựֹͣ
	* @param[in]    ScanHandle ͨ��CreateScanSession��ȡ
	* @return		0 �ɹ�,����Ϊʧ�ܴ�����
	* @remark       �̰߳�ȫ����,���ô˽ӿں�,��Ӧ��ScanHandle��������ɨ�裬����Ҫ����ɨ�裬��Close���ٴ���һ���µġ�
	*/
	virtual int __stdcall NotifyStopScan(
		/* [in] */ const S_KSE_LITESCAN_SESSION& ScanHandle,
		/* [out]*/ KXE_NULL_PARAEMETER& nullParm
		);


	/**
	* @brief         ִ��ɨ��
	* @param [in]    ScanHandle ͨ��CreateScanSession��ȡ
	* @param [in]    ScanTarget ɨ��Ŀ��������Ϣ
	* @param [out]   ScanResults ɨ��Ŀ���Ӧ��ɨ��������ScanTarget�е�vecScanFilesһһ��Ӧ
	* @return		 0 �ɹ�,����Ϊʧ�ܴ�����
	* @remark        �����������߳����ͬһ��ScanHandle������,�����Ҫ���߳�,Ϊÿ���̴߳���һ��ScanHandle
	*/
	virtual int __stdcall ScanFiles(
		/* [in] */ const S_KSE_LITESCAN_SESSION& ScanHandle,
		/* [in] */ const S_KSE_LITESCAN_TARGET_INFO& ScanTarget,
		/* [out]*/ std::vector<S_KSE_LITESCAN_RESULT>& ScanResults
		);


	/**
	* @brief        ��������һ���ļ�,���ٽ�ɨ�����̣�ֱ��ɾ��������
	* @param[in]    ������������Ϣ
	* @param[in]    ����ɹ�ʱ����ؽ����Ϣ(����ֵΪ0ʱ�˽����Ч)
	* @return		0 �ɹ�,����Ϊʧ�ܴ�����
	* @remark       �̰߳�ȫ����
	*/
	virtual int __stdcall ProcessFile(
		/* [in]  */ const S_KSE_PROCESS_FILE_INFO& FileInfo,
		/* [out]*/  S_KSE_PROCESS_FILE_RESULT& ProcessResult
		);

private:
	bool m_bIsInitialized;
;
};
