//////////////////////////////////////////////////////////////////////
///		@file		idl_pipe.h
///		@author		�����
///		@date		2009-4-8 30:07:58
///
///		@brief		����pipe���м��װ
///		
//////////////////////////////////////////////////////////////////////

#pragma once
#include "idl_common.h"
#include "idl_util_inl.h"
#include "../kxeerror/kxeerror.h"
#include "../common/kxe_thread.h"
#include "kxepipecallproduct.h"

/**
 * @defgroup kxepipe_idl_interface_group KXEPipe IDL Interface
 * @{
 */

class KxEPipeClientCommunication
{
public:

	/**
	* @brief		ͨ��ע����ѯ SP �ܵ����Ĺ��췽ʽ
	* @remark		�� pwszServerPipeName Ϊ�գ������ע����в�ѯĿ��ܵ���
	* @param[in]	: pwszServiceProviderName Ϊ�����ṩ�ߵ�����
	* @param[in]	: pwszServerPipeName Ϊ�÷����ṩ�����ڽ��̵������ܵ���
	*/
	KxEPipeClientCommunication(
		const wchar_t* pwszServiceProviderName,
		const wchar_t* pwszServerPipeName
		):m_bGetPipeNameFromReg(TRUE)
	{
		if (NULL != pwszServiceProviderName)
		{
			m_wstrServiceProviderName = pwszServiceProviderName;
		}

		if (NULL != pwszServerPipeName)
		{
			m_wstrTargetPipeName		= pwszServerPipeName;
			m_bTargetPipeNameAccquired	= TRUE;
			m_bGetPipeNameFromReg		= FALSE;
		}
		else
		{
			int nRet = idl_util_get_sp_pipe_name_from_registry(
				m_wstrServiceProviderName,
				m_wstrTargetPipeName
				);
			if (0 != nRet)
			{
#ifdef USE_KXE_DEBUG_LOG
				KXE_DEBUG_LOG((LOG_ERROR, "It failed to query the specified SP's pipe name in the registry with error: 0x%8x!", nRet));
#endif
			}
			m_bTargetPipeNameAccquired = (0 == nRet);
		}
	}

	int Navigate(
		const wchar_t* pwszSpAndMethod,
		const char* pszParameter,
		unsigned int uParameterSize,
		kxe::string& strResult
		)
	{
		int nRet				= -1;
		BOOL bIsGetPipeNameNow	= FALSE;//����κ��������д�ע����ȡ�˹ܵ���
		KxEThreadMutexGuard guard(m_Mutex);
		if (!m_bTargetPipeNameAccquired && m_bGetPipeNameFromReg)
		{
			nRet = idl_util_get_sp_pipe_name_from_registry(
				m_wstrServiceProviderName,
				m_wstrTargetPipeName
				);
			if (0 != nRet)
			{
#ifdef USE_KXE_DEBUG_LOG
				KXE_DEBUG_LOG((LOG_ERROR, "It failed to query the specified SP's pipe name in the registry with error: 0x%8x!!", nRet));
#endif
				return E_KXEPIPE_SP_PIPE_NAME_NOT_FOUND_IN_REGISTRY;
			}

			bIsGetPipeNameNow = TRUE;
		}

		nRet = this->CheckIfPipeExist(m_wstrTargetPipeName.c_str());
		if (0 == nRet)
		{
			m_bTargetPipeNameAccquired = TRUE;
		}
		else if (!bIsGetPipeNameNow && m_bGetPipeNameFromReg)
		{
			nRet = idl_util_get_sp_pipe_name_from_registry(
				m_wstrServiceProviderName,
				m_wstrTargetPipeName
				);
			if (0 != nRet)
			{
#ifdef USE_KXE_DEBUG_LOG
				KXE_DEBUG_LOG((LOG_ERROR, "It failed to query the specified SP's pipe name in the registry with error: 0x%8x!!!", nRet));
#endif
				return E_KXEPIPE_SP_PIPE_NAME_NOT_FOUND_IN_REGISTRY;
			}

			nRet = this->CheckIfPipeExist(m_wstrTargetPipeName.c_str());
		}

		if (nRet != 0)
		{
			m_bTargetPipeNameAccquired	= FALSE;
			m_wstrTargetPipeName		= L"";
			return nRet;
		}

		char *pszOutParameter = NULL;
		unsigned int uOutParameterLen = 0;

		nRet = m_callProduct.CallProductPipe(
			m_wstrTargetPipeName.c_str(),
			CW2A(pwszSpAndMethod, CP_UTF8),
			pszParameter,
			uParameterSize,
			(void **)&pszOutParameter,
			&uOutParameterLen
			);
		if (0 != nRet) // ��ʱ�� pszOutParameter ��̬������ڴ潫��CallProductPipe�Զ��ͷţ����Բ�������ʽ����ReleasePipeBuffer
		{
			return nRet;
		}
		else
		{
			strResult = "";	// �Է� strResult �����ҳ��� pszOutParameter
			strResult.insert(0, pszOutParameter, uOutParameterLen);
			m_callProduct.ReleasePipeBuffer(&pszOutParameter);
			return 0;
		}
	}

	int GetServerPort(short& sPort)
	{
		sPort;//just for remove warning
		return -1;
	}

private:
	/**
	* @brief		����ָ�����ֵĹܵ��Ƿ����
	* @remark		
	* @return		0 �ɹ�������Ϊ������
	**/
	inline int __stdcall CheckIfPipeExist(LPCWSTR pwszPipeName)
	{
		BOOL bSuccess = FALSE;

		bSuccess = WaitNamedPipe(
			pwszPipeName, 
			NMPWAIT_USE_DEFAULT_WAIT
			);
		if (!bSuccess && ERROR_PIPE_BUSY != GetLastError())
		{
#ifdef USE_KXE_DEBUG_LOG
			KXE_DEBUG_LOG((
				LOG_ERROR,
				"kxepipecallproduct.cpp: WaitNamedPipe failed with error: 0x%8x",
				GetLastError()
				));
#endif
			return E_KXEPIPE_WAIT_NAMED_PIPE_FAILED;
		}

		return 0;
	}

private:
	std::wstring m_wstrServiceProviderName;
	std::wstring m_wstrTargetPipeName;

	BOOL m_bTargetPipeNameAccquired;	/*	��־Ŀ��ܵ����Ƿ��Ѿ���ȡ��	*/
	BOOL m_bGetPipeNameFromReg;
	/**
	 * ��Ϊ����󣬴˶���Ϳ��Ա������������ʹ�õĹܵ�ʵ�������
	 * ������ÿ�ε���CallProductPipeʱ��ȥ����������½���һ������
	 * ��KxEPipeClientCommunication��������ʱ��KxEPipeCallProduct�����������ᱻ���ã�
	 * ��ʱ��ر����������ʹ�õĹܵ�ʵ�����
	 */
	KxEThreadMutex		m_Mutex;
	KxEPipeCallProduct	m_callProduct;	
};

//------------------------------------------------------------------------------

template
<
	typename _Interface
>
class KxEPipeClientT : public KxEIPCClientT<_Interface, KxEPipeClientCommunication>
{
public:

	/**
	* @param[in]	: pwszServerPipeName Ϊ�����Ŀ�������ܵ���
	* @remark		���Ϊ�գ����Զ���ע����в��� _Interface ��Ӧ�� SP ���ڽ��̵Ĺܵ���;
	*				������գ������ pwszServerPipeName ΪĿ��ܵ���
	*/
	KxEPipeClientT(const wchar_t* pwszServerPipeName = NULL)
		: KxEIPCClientT<_Interface, KxEPipeClientCommunication>(pwszServerPipeName)
	{
	}
};

//���sp�Ƿ��Ѿ�����
inline int kxe_check_is_sp_loaded(const wchar_t* pszSPName, BOOL& bIsLoaded)
{
	if (NULL == pszSPName)
		return -1;

	std::wstring strSPName = pszSPName;
	std::wstring strTargetPipeName;

	bIsLoaded = FALSE;
	int nTmpResult = idl_util_get_sp_pipe_name_from_registry(
		strSPName,
		strTargetPipeName
		);
	if (0 == nTmpResult)
	{
		BOOL bSuccess = FALSE;
		bSuccess = WaitNamedPipe(strTargetPipeName.c_str(), 0);
		if (bSuccess || ERROR_PIPE_BUSY == GetLastError())
		{
			bIsLoaded = TRUE;
		}
	}
	return 0;
}

/**
 * @}
 */