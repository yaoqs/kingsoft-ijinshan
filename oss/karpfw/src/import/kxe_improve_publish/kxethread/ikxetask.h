//////////////////////////////////////////////////////////////////////
///		@file		ikxetask.h
///		@author		luopeng
///		@date		2008-9-22 14:07:58
///
///		@brief		Task�ӿڼ�JobControl�Ķ���
//////////////////////////////////////////////////////////////////////

#pragma once

/**
* @addtogroup kxebase_thread_group
* @ref kxebase_thread_example
* @{
*/

/**
* @brief IKxETaskControl���ƽӿ�,��Job������Ϊenum_kjp_away_keyboard_long_job��enum_kjp_control_cpu_long_job��Ҫ���ô˽ӿ�
*/
class IKxETaskControl
{
public:
	/**
	 * @brief �������ʵ���ߵ��ô˽ӿ���ʵ��������ж�,������ָ������ʱ,�ٷ��ظ�������
	 * @return E_KXETHREAD_JOB_IN_STOP_CMD �����ⲿ������kxe_base_stop_cmd,��Ҫֹͣ������
	 */
	virtual int __stdcall Interruppt() = 0;

	/**
	 * @brief �������ʵ���ߵ��ô˽ӿ���ʵ���жϸ������Ƿ���Ҫֹͣ,�����ⲿ������kxe_base_stop_cmd
	 */
	virtual bool __stdcall IsStop() = 0;
};

/**
* @brief ָ�����������нӿ�
*/
class IKxETask
{
public:
	/**
	* @brief �������ʵ�����к���
	* @see kxe_base_get_job_exit_code
	* @see kxe_job_type
	* @param[in] pParam ΪJob�Ķ����߹涨����,���ύ������ṩ������
	* @param[in] pControl ��pControl��Чʱ,��Ҫ��ѭ���е������Ӻ���Interuppt��IsStop�ж��˳�,���ҽ�����Run�����е���.
	* @remark ��IKxETaskControlָ����Чʱ,Taskʵ������Ҫ��ʱ���ô˽ӿڵ�Interruppt,��ʵ��CPU,�û��뿪����ͣ�Ĵ���
	* @return ���ص�ֵͨ��kxe_base_get_job_exit_code�ܹ��õ�
	*/
	virtual int __stdcall RunTask(
		void* pParam, 
		IKxETaskControl* pControl
		) = 0;
};

/**
* @}
*/

/**
 * @page kxebase_thread_example KXEngine Thread Example
 * @section kxebase_thread_example_define_task ���������ʵ��
 * @code
class KxETask : public IKxETask
{
public:
	virtual int __stdcall StopTask()
	{
		m_bStop = true;
		return 0;
	}

	virtual int __stdcall RunTask(
		void* pParam, 
		IKxETaskControl* pControl
		)
	{
		while (!pControl->IsStop())
		{
			Sleep(100);
		
			// do something

			pControl->Interruppt();
		}
		return -1;
	}
};
 * @endcode
 @section kxebase_thread_example_startup_job �����񴴽�ΪJob�����в���
 @code
	kxe_job_t job;

	KxETask* pTask = new KxETask;
	kxe_base_create_job(
		enum_kjp_low_influence_long_job,
		pTask,
		NULL,
		&job
		);

	kxe_base_run_job(job);

	kxe_base_wait_job(job, 20000);

	kxe_base_stop_job(job);

	kxe_base_wait_job(job, INFINITE);

	int nExitCode = 0;
	kxe_base_get_job_exit_code(job, &nExitCode);

	kxe_base_close_job(job);

	delete pTask;

 @endcode
 */