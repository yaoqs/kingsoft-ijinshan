//////////////////////////////////////////////////////////////////////
///		@file		ikxerequestdispatch.h
///		@author		luopeng
///		@date		2008-8-27 14:07:58
///
///		@brief		IPCת���Ľӿ�
//////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @brief ����IKxERequestDispatch�洢ʱ���ص����ݵĽӿ�
 * @see IKxERequestDispatch
 */
class IKxERequestDispatchReturnBlock
{
public:
	virtual int __stdcall SetBuffer(
		const void* pBuffer, 
		size_t bufSize
		) = 0;

};

typedef enum _ENUM_KXE_COMMUNICATION_TYPE
{
	enum_EKCT_Socket,
	enum_EKCT_Pipe
}ENUM_KXE_COMMUNICATION_TYPE;

/**
 * @brief ���ڿ��Ƶ�ǰIPC���ӵĽӿ�
 */
class IKxERequestControl
{
public:
	/**
	 * @brief ģ�⵱ǰ�ͻ��˽��̵����л���
	 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
	 */
	virtual int __stdcall KxEImpersonateClient() = 0;

	/**
	 * @brief ��ԭ��ǰ���̵Ļ���
	 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
	 */
	virtual int __stdcall KxERevertSelf() = 0;

	/**
	 * @brief ��ȡ��������
	 * @param[out] pEnumType ���ص�ͨ������
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall KxEGetCommunicatieType(
		ENUM_KXE_COMMUNICATION_TYPE* pEnumType
		) = 0;

	/**
	 * @brief ��ȡ��������
	 * @param[out] pdwProcessId Դ����ID
	 * @return 0 �ɹ�������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall KxEGetClientProcessId(
		DWORD* pdwProcessId
		) = 0;
};

/**
* @brief ��IPC����ע��Ŀ¼�����ض���Ľӿ�
* @see IKxERequestDispatchReturnBlock
*/
class IKxERequestDispatch
{
public:
	/**
	* @brief IPC��ȡ��/SP/pszMethod�ϵ�����ʱ,�ͻ�ص����˽ӿ���
	* @param[in] pszMethod Ϊע��ʱ�ض����·����
	* @param[in] pszRequest ������IPC Request
	* @param[in, out] pReturnBlock ���û���������ɺ�,����ʱ�����ݴ洢�Ľṹ
	* @param[in] pControl ���ڵ�ǰ���ӿ��ƵĲ���
	*/
	virtual int __stdcall Dispatch(
		const char* pszMethod, 
		const char* pszRequest, 
		IKxERequestDispatchReturnBlock* pReturnBlock,
		IKxERequestControl* pControl
		) = 0;
};

