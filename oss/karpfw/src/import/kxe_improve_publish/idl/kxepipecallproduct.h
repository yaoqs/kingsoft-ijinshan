//////////////////////////////////////////////////////////////////////
///		@file		kxepipecallproduct.h
///		@author		liangguangcai
///		@date		[2009-4-30, 12:02:30]
///		@brief		�����������ܵ��������˷���SP��������
///		@remark		ע�� USE_KXE_DEBUG_LOG ��Ķ����Ӱ�쵽�Ƿ��¼��־��
///					���ң���������� USE_KXE_DEBUG_LOG��������������
///					kxebase(.lib)
///		@last changed:
///			$by:	    �����<liangguangcai@kingsoft.com>
///			$changed:  �������ڴ����ʧ�ܵĴ����룻����������
//////////////////////////////////////////////////////////////////////

#pragma once

#include <sstream>
#include <cassert>

#include <Windows.h>
#include "../kxeerror/kxeerror.h"
#include "../common/kxe_thread.h"
/*
* [ע]
*	Ĭ������²�����˺꣬���Ĭ������²��������� kxebase(.lib)��
*	��Ҫ��¼ SP �Ĺܵ����ó������־��
*	�����ڳ���Ĺ���Ԥ�������ж������º꣺
*		USE_KXE_DEBUG_LOG
*/
#ifdef USE_KXE_DEBUG_LOG
	#include "../include/kxe.h"
#endif


//------------------------------------------------------------------------------


#define KXEPIPE_WAIT_PIPE_INTERVAL 100	// WaitNamedPipe ʱ���������룩

#define KXEPIPE_MAX_CONNECT_TIMES 5		// ��������ָ���Ĺܵ�����˵�������


//------------------------------------------------------------------------------


class KxEPipeCallProduct
{
public:
	KxEPipeCallProduct() : m_hConnectPipe(NULL)
	{

	}

	~KxEPipeCallProduct()
	{
		// ���ɹ����������ӣ����ʱ�ر�����ܵ�ʵ��
		if (NULL != m_hConnectPipe)
		{
			CloseHandle(m_hConnectPipe);
		}
	}

public:
	/**
	* @brief ��Ŀ�������ܵ����������������������ݲ��ȴ����ݻظ�
	* @param[in] lpszPipeName Ŀ�������ܵ��������˵������ܵ���
	* @param[in] szSPAndMethod Ŀ��ͻ��˵ķ����ṩ�߼�������� /ServiceProvider/Method
	* @param[in] lpszData ����������
	* @param[in] uDataLength ���������ݳ���
	* @param[out] ppReturnData ���ص����ݣ���Ҫ����һ��ָ���ַ�������ReleasePipeBuffer�ͷ�
	* @param[out] puDataLength ���ص����ݳ���
	* @return  0 �ɹ�������Ϊʧ�ܴ�����
	*/
	int __stdcall CallProductPipe(
		LPCWSTR lpszPipeName,
		const char* szSPAndMethod,	// �����Ϊ�գ��ͻ��˻᷵��һ�� ���������� ��Ϣ
		const char* lpszData,			// �����Ϊ�գ��ͻ��˻᷵��һ�� ���������� ��Ϣ
		unsigned int uDataLength,
		void** ppReturnData,
		unsigned int* puDataLength
		)

	{
		//1.... ��������ȷ��
		if (NULL == lpszPipeName ||NULL == szSPAndMethod ||
			NULL == lpszData || 0 == uDataLength)
		{
			return E_KXEPIPE_INCORRECT_PARAMETER;
		}

		//2.... ���ܵ������ϴ�������ޱ仯�����б仯�����µ�����
		int nRet = 0;
		if (m_wstrServerPipeName != lpszPipeName)
		{
			m_wstrServerPipeName = lpszPipeName;
			m_hConnectPipe = NULL;	// ���½�������
		}

		// ���ܵ��Ƿ����
		nRet = this->CheckIfPipeExist();
		if (0 != nRet)
		{
			return nRet;
		}
		
		if (NULL == m_hConnectPipe)	// ��ֹ�ظ���������
		{
			nRet = ConnectPipeServer();	
			if (0 != nRet)	// ���ʧ�ܣ���m_hConnectPipeһ��ΪNULL
			{
				// ��out�����ÿպ��ٷ���
				*ppReturnData = NULL;
				*puDataLength = 0;
				return nRet;
			}
		}

		//3.... ��ͻ��˷�������
		std::ostringstream os;
		os << szSPAndMethod << "?json=" << lpszData;

		unsigned int uJsonDataLen = (unsigned int)(os.str().size()) * sizeof(char);
		char *pszSendBuffer = new char[sizeof(unsigned int) + uJsonDataLen];
		if (NULL == pszSendBuffer)
		{
			// ��out�����ÿպ��ٷ���
			*ppReturnData = NULL;
			*puDataLength = 0;
			return E_KXEPIPE_NOT_ENOUGH_MEMORY;
		}

		memcpy(
			pszSendBuffer, 
			&uJsonDataLen, 
			sizeof(unsigned int)
			);
		memcpy(
			pszSendBuffer + (sizeof(unsigned int))/sizeof(char),
			os.str().c_str(), 
			uJsonDataLen);
	
		nRet = WritePipeSynchronously(
			pszSendBuffer,
			sizeof(unsigned int)+uJsonDataLen
			);
		if (0 != nRet)
		{
			FreeMemAndClosePipe(
				&pszSendBuffer,
				ppReturnData,
				puDataLength
				);
			return nRet;
		}
	
		/**
		 * ֻҪ WritePipeSynchronously �ɹ������ɹ��ط��ͳ������ݣ�
		 * ����ΪCallProductPipe�ɹ������Խ��ŵȴ��������ݵĵ���
		 */

		//4.... ���տͻ��˵ķ�������

		// �ȶ�ȡ�������ݵĳ���
		nRet = ReadPipeSynchronously(
			(char*)puDataLength,
			sizeof(unsigned int)
			);
		if (0 != nRet)
		{
			// ��out�����ÿգ��ͷŶ�̬����ķ��ͻ��������رչܵ����
			FreeMemAndClosePipe(
				&pszSendBuffer,
				ppReturnData,
				puDataLength
				);
			return nRet;
		}

		if ( 0 == *puDataLength)
		{
			// ��out�����ÿգ��ͷŶ�̬����ķ��ͻ��������رչܵ����
			FreeMemAndClosePipe(
				&pszSendBuffer, 
				ppReturnData, 
				puDataLength
				);
			return E_KXEPIPE_BAD_RETURN_DATA;
		}

		// �ٶ�ȡ��������
		*ppReturnData  = new char[ *puDataLength ];
		if (NULL == *ppReturnData)
		{
			// ��out�����ÿգ��ͷŶ�̬����ķ��ͻ��������رչܵ����
			FreeMemAndClosePipe(
				&pszSendBuffer, 
				ppReturnData, 
				puDataLength
				);
			return E_KXEPIPE_NOT_ENOUGH_MEMORY;
		}

		nRet = ReadPipeSynchronously(
			(char *)(*ppReturnData),
			*puDataLength
			);
		if (0 != nRet)
		{
			delete [] (char*)*ppReturnData;	
			FreeMemAndClosePipe(
				&pszSendBuffer, 
				ppReturnData, 
				puDataLength
				);
			return nRet;
		}

		//5.... CallProductPipe�ɹ����ͷŶ�̬����ķ��ͻ�����
		delete [] pszSendBuffer;
		return 0;
	}


	/**
	* @brief �ͷ�ͨ�����������ڴ�
	* @param[in] pBuffer ��Ҫ�ͷŵ��ڴ��ַ
	* @return 0 �ɹ�������Ϊʧ�ܴ�����
	*/
	template<typename T>
	int __stdcall ReleasePipeBuffer(
		T** ppBuffer
		)
	{
		delete [] *ppBuffer;
		*ppBuffer = NULL;
		return 0;
	}


private:
	/**
	* @brief		����ָ�����ֵĹܵ��Ƿ����
	* @remark		
	* @return		0 �ɹ�������Ϊ������
	**/
	inline int __stdcall CheckIfPipeExist()
	{
		BOOL bSuccess = FALSE;

		bSuccess = WaitNamedPipe(
			m_wstrServerPipeName.c_str(), 
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

	/**
	* @brief ���������������ܵ�������������
	* @return  0 �ɹ�������Ϊʧ�ܴ�����
	*/
	int __stdcall ConnectPipeServer()
 	{
		int nRet = this->CheckIfPipeExist();
		if (0 != nRet)
		{
			return nRet;
		}
		
		int nCount = 0;
		do 
		{
			m_hConnectPipe = CreateFile(
				m_wstrServerPipeName.c_str(),		// �����ܵ���
				GENERIC_READ | GENERIC_WRITE,	// �ܵ���дģʽ��˫��
				0, 
				(LPSECURITY_ATTRIBUTES)NULL, 
				OPEN_EXISTING, 
				FILE_ATTRIBUTE_NORMAL |
				SECURITY_SQOS_PRESENT |	// ����������ڱ���ϵͳ��ʶ���ģ�¸ÿͻ�
				SECURITY_IMPERSONATION,
				(HANDLE)NULL
				);
			if (INVALID_HANDLE_VALUE != m_hConnectPipe)
			{
				break;	// �ɹ����� nCount һ��С�� KXEPIPE_MAX_CONNECT_TIMES
			}
			else
			{
				++nCount;
				Sleep(50);
			}
		} while (nCount != KXEPIPE_MAX_CONNECT_TIMES);

 		if (nCount == KXEPIPE_MAX_CONNECT_TIMES)
		{
#ifdef USE_KXE_DEBUG_LOG
			KXE_DEBUG_LOG((
				LOG_ERROR,
				"kxepipecallproduct.h: CreateFile failed with error: 0x%8x",
				GetLastError()
				));
#endif
			m_hConnectPipe = NULL;
			return E_KXEPIPE_CREATE_INSTANCE_ON_THE_PIPE_CLIENT_END_FAILED;
		}

		return 0;
	}

	/**
	*@brief �����ͷŷ��ͻ����������÷��ز������رչܵ����
	*@param[in] pszSendBuffer ��Ҫ�ͷŵķ��ͻ�����
	*@param[out] ppReturnData Ϊ��Ҫ�ÿյķ������ݵ�ַ
	*@param[out] puDataLength Ϊ��Ҫ��Ϊ0�ķ������ݳ���
	*@return void
	*/
	inline void FreeMemAndClosePipe(
		char** pszSendBuffer,
		void** ppReturnData,
		unsigned int * puDataLength
		)
	{
		// ��out�����ÿպ��ٷ���
		*ppReturnData = NULL;
		*puDataLength = 0;
		delete [] *pszSendBuffer;  
		CloseHandle(m_hConnectPipe);
		m_hConnectPipe = NULL;
	}
	
	/**
	 * @brief ��ܵ�ͬ����д��ָ����Ŀ������
	 * @param[in] pszSendBuffer ���ͻ�������ַ
	 * @param[in] dwSendDataLength Ҫ���͵����ݳ���
	 * @return  0 �ɹ�������Ϊ������
	 */
	int __stdcall WritePipeSynchronously(
		const char* pszSendBuffer, 
		const DWORD dwSendDataLength
		)
	{
		assert(NULL != m_hConnectPipe);

		DWORD dwBytesWritten = 0;
		DWORD dwTransferOffset = 0;
		BOOL bSuccess = FALSE;
		while (dwSendDataLength != dwTransferOffset)
		{
			dwBytesWritten = 0;
			bSuccess = WriteFile(
				m_hConnectPipe, 
				(LPCVOID)(pszSendBuffer+dwTransferOffset),	// ÿ��ѭ����Ҫ�����ļ�ָ��
				dwSendDataLength - dwTransferOffset,
				&dwBytesWritten,
				NULL	// ͬ����ʽ
				);
			if (!bSuccess)
			{
#ifdef USE_KXE_DEBUG_LOG
				KXE_DEBUG_LOG((
					LOG_ALERT,
					"kxepipecallproduct.h: WritePipeSynchronously failed with error: 0x%8x",
					GetLastError()
					));
#endif
				return E_KXEPIPE_CLIENT_WRITE_FILE_FAILED;
			}
			else
			{
				dwTransferOffset += dwBytesWritten;
			}
		}

		return 0;
	}
	
	/**
	 * @brief �ӹܵ�ͬ���ض�ȡָ����Ŀ������
	 * @param[in, out] pszReceiveBuffer ���ջ�������ַ
	 * @param[in] dwReceiveDataLength Ҫ���յ����ݳ���
	 * @return  0 �ɹ�������Ϊ������
	 */
	int __stdcall ReadPipeSynchronously(
		char* pszReceiveBuffer, 
		const DWORD dwReceiveDataLength
		)
	{
		assert(m_hConnectPipe);

		DWORD dwBytesRead = 0;
		DWORD dwTransferOffset = 0;
		BOOL bSuccess = 0;
		while (dwReceiveDataLength != dwTransferOffset)
		{
			dwBytesRead = 0;
			bSuccess = ReadFile(
				m_hConnectPipe,
				(LPVOID)(pszReceiveBuffer+dwTransferOffset),
				dwReceiveDataLength - dwTransferOffset,
				&dwBytesRead,
				NULL
				);
			if (!bSuccess)
			{
#ifdef USE_KXE_DEBUG_LOG
				KXE_DEBUG_LOG((
					LOG_ALERT,
					"kxepipecallproduct.h: ReadPipeSynchronously failed with error: 0x%8x",
					GetLastError()
					));
#endif
				return E_KXEPIPE_CLIENT_READ_FILE_FAILED;
			}
			else
			{
				dwTransferOffset += dwBytesRead;
			}
		}

		return 0;
	}

private:
	std::wstring m_wstrServerPipeName;
	HANDLE m_hConnectPipe;
};
