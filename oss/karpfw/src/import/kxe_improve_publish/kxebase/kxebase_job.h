//////////////////////////////////////////////////////////////////////
///		@file		kxebase_job.h
///		@author		luopeng
///		@date		2008-8-29 09:07:58
///	
///		@brief		job������صĶ���
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../kxethread/ikxetask.h"

/**
 * @defgroup kxebase_thread_group KXEngine Architecture Base SDK Thread Interface
 * @{
 */

/**
 * @brief �ύ��job������
 */
typedef enum _kxe_job_type
{
	enum_kjp_short_job,                   ///< ��ʱ��Ϳ�������ɵ�Job,ʹ���̳߳��е��߳����
	enum_kjp_normal_long_job,             ///< ��ʱ�����������ɵ�Job,�����µ��߳����
	enum_kjp_low_influence_long_job,      ///< ��ʱ������,��Ҫ���Ӱ���û���Job
	enum_kjp_away_keyboard_long_job,      ///< ��ʱ������,���ҽ����û�����ʱ����,��Ҫ����IKxEJobControl.Interuppt���
	enum_kjp_control_cpu_long_job         ///< ���Ƹ��߳�CPUʹ�õ�Job,��Ҫ����kxe_base_set_and_run_control_cpu_job����CPU�������ܿ�ʼ����
} kxe_job_type;

inline bool KxEIsLongJobType(kxe_job_type type)
{
	if (type != enum_kjp_short_job)
	{
		return true;
	}

	return false;
}

/**
 * @brief ����Job��ǰ��״̬
 */
typedef enum _kxe_job_status
{
	enum_kjs_ready,      ///< job�Ѿ�׼����,��������
	enum_kjs_running,    ///< job��������״̬
	enum_kjs_pause_cmd,  ///< ��job������pause����,��job��δ��ͣ
	enum_kjs_paused,     ///< job�Ѿ�������ͣ״̬
	enum_kjs_stop_cmd,   ///< ��job������stop����,��job��δֹͣ
	enum_kjs_finished,   ///< job�Ѿ����
	enum_kjs_error       ///< job���ִ���
} kxe_job_status;


/**
 * @brief ����Job�������
 */
typedef void* kxe_job_t;

/**
 * @brief ����Job��������ָ��������
 * @see kxe_base_close_multi_job, kxe_base_close_job
 * @param[in] type ��������Ҫ���е�����
 * @param[in] pTask �������������
 * @param[in] pParam ������Ĳ���
 * @param[out] pJobHandle �����������õ�JobHandle, ʹ��kxe_base_close_job,
                          kxe_base_close_multi_job�ر�
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_create_job(
	kxe_job_type type, 
	IKxETask* pTask, 
	void* pParam, 
	kxe_job_t* pJobHandle
	);

/**
 * @brief ����Job��������ָ�������񣬴�����ģ�⵱ǰ�̵߳�Token
 * @see kxe_base_close_multi_job, kxe_base_close_job
 * @param[in] type ��������Ҫ���е�����
 * @param[in] pTask �������������
 * @param[in] pParam ������Ĳ���
 * @param[out] pJobHandle �����������õ�JobHandle, ʹ��kxe_base_close_job,
                          kxe_base_close_multi_job�ر�
 * @remark �����ȡTokenʧ�ܣ������ش����룬���������ִ��
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_create_job_as_thread_token(
	kxe_job_type type, 
	IKxETask* pTask, 
	void* pParam, 
	kxe_job_t* pJobHandle
	);

/**
 * @brief �趨enum_kjp_control_cpu_long_job��job��CPUռ����,����ʼ����job.
 *        ������Ϊenum_kjp_control_cpu_long_job���ܵ���
 * @param[in] job ��Ҫ����CPUռ������job
 * @param[in] fCpuPercent �߳��ܹ�����ʹ�õ�CPU�ٷֱ�
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_set_and_run_control_cpu_job(
	kxe_job_t job,
	float fCpuPercent
	);

/**
 * @brief �趨enum_kjp_away_keyboard_long_job��job���û��뿪ָ��ʱ�������
 * @param[in] job ��Ҫ���Ƶ�job
 * @param[in] uSeconds �û��뿪��ʱ��,��λΪ��
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_set_and_run_user_away_job(
	kxe_job_t job,
	unsigned int uSeconds
	);

/**
 * @brief ����job������
 * @see kxe_base_set_and_run_control_cpu_job
 * @see kxe_base_set_and_run_user_away_job
 * @param[in] job ��Ҫ���е�job
 * @remark ��job����Ϊenum_kjp_control_cpu_long_jobʱ,��Ҫʹ��kxe_base_set_and_run_control_cpu_job
          ��job����Ϊenum_kjp_away_keyboard_long_jobʱ,��Ҫʹ��kxe_base_set_and_run_user_away_job
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_run_job(
	kxe_job_t job
	);

/**
 * @brief ָֹͣ����Job
 * @param[in] job ��Ҫֹͣ��Job, ָ����Job��Ҫʹ��IKxETaskControl::IsStop�ж�
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_stop_job(
	kxe_job_t job
	);

/**
 * @brief ��ָͣ����Job
 * @param[in] job ��Ҫ��ͣ��Job
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_pause_job(
	kxe_job_t job
	);

/**
 * @brief �ָ�ָ����Job
 * @param[in] job ��Ҫ�ָ���Job
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_resume_job(
	kxe_job_t job
	);


/**
 * @brief �ȴ�ָ����Job�˳�
 * @param[in] job ��Ҫ�ȴ���Job
 * @param[in] uMilliseconds ��Ҫ�ȴ���ʱ��
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_wait_job(
	kxe_job_t job,
	unsigned int uMilliseconds
	);

/**
* @brief �ȴ�ָ��������Job�˳�
* @param[in] arrayJob ��Ҫֹͣ��Job����
* @param[in] uJobCount ��Ҫֹͣ��job������
* @param[in] bWaitAll �Ƿ�ȴ����е�job�˳���ŷ���
* @param[in] uMilliseconds �ȴ���ʱ��
* @return 0 �ɹ�, ����Ϊʧ�ܴ�����
*/
int __stdcall kxe_base_wait_multi_job(
	kxe_job_t* arrayJob,
	unsigned int uJobCount,
	bool bWaitAll,
	unsigned int uMilliseconds
	);

/**
 * @brief ��ȡ�������˳�ʱ��,���ص�code
 * @param[in] job ��Ҫ��ȡcode��job
 * @param[out] pnExitCode ����job�˳�code
 */
int __stdcall kxe_base_get_job_exit_code(
	kxe_job_t job,
	int* pnExitCode
	);

/**
 * @brief ��ȡ������ǰ��״̬
 * @param[in] job ��Ҫ��ȡ��job
 * @param[out] pStatus �洢��ǰ����״̬
 */
int __stdcall kxe_base_get_job_status(
	kxe_job_t job,
	kxe_job_status* pStatus
	);

/**
 * @brief �ر�ָ����Job
 * @param[in] job ��Ҫ�رյ�Job
 * @remark �����job�������е�ʱ��������йر�
 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
 */
int __stdcall kxe_base_close_job(
	kxe_job_t job
	);

/**
 * @}
 */