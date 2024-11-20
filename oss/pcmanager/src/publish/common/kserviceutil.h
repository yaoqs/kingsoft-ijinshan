//=============================================================================
/**
* @file kserviceutil.h
* @brief 
* @author qiuruifeng <qiuruifeng@kingsoft.com>
* @date 2009-8-6   21:31
*/
//=============================================================================
#pragma once 

enum enumKSERVICE_FIX_ACTION
{
	enumSERVICE_FIX_NONE		= 0,
	enumSERVICE_FIX_START		= 1, 
	enumSERVICE_FIX_INSTALL_AND_START	= 2 
};

/**
 * @brief ������״̬
 * @remark ���ע���HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\�µķ����ֵ��ɾ,��Ȼ�����������,״̬��SERVICE_STOPPED
 * @param[in] pszServiceName ������
 * @param[out] pbServiceExist �����Ƿ����
 * @param[out] pdwStatus ����״̬(SERVICE_STOPPED SERVICE_START_PENDING SERVICE_RUNNING .....)
 * @param[out] pdwError apiִ�еĴ�����
 * @return TRUE�ɹ�,FALSEʧ��
 */
BOOL KCheckServiceStatus(const wchar_t* pszServiceName, 
						 BOOL* pbServiceExist, 
						 DWORD* pdwStatus, 
						 DWORD* pdwError);

/**
* @brief ��������״̬
* @remark ���ע���HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\�µķ����ֵ��ɾ,��������ERROR_PATH_NOT_FOUND,
*			������񱻽��ô�������ERROR_SERVICE_DISABLED
* @param[in] pszServiceName ������
* @param[out] pdwError apiִ�еĴ�����
* @return TRUE�ɹ�,FALSEʧ��
*/
BOOL KStartService(const wchar_t* pszServiceName, DWORD* pdwError);

/**
 * @brief ���ķ�������
 * @remark ���ע���HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\�µķ����ֵ��ɾ,��������ERROR_PATH_NOT_FOUND,
 * @param[in] pszServiceName ������
 * @param[in] pszImagePath	�ļ�·�����Դ�NULL
 * @param[in] pszSvcOrderGroup ���� ���Դ�NULL
 * @param[in] pszDisplayName �����Ѻ����� ���Դ�NULL
 * @param[in] pszDescription ��������  ���Դ�NULL
 * @param[in] dwStartType ��������,���SERVICE_DEMAND_START SERVICE_AUTO_START��SERVICE_NO_CHANGE�ǲ�����
 * @param[out] pdwError apiִ�еĴ�����
 * @return TRUE�ɹ�,FALSEʧ��
 */
BOOL KChangeServiceConfig(const wchar_t* pszServiceName, 
						  const wchar_t* pszImagePath,  
						  const wchar_t* pszSvcOrderGroup, 
						  const wchar_t* pszDisplayName,
						  const wchar_t* pszDescription,
						  DWORD dwStartType,
						  DWORD* pdwError);

/**
 * @brief ��������
 * @remark ���ע���HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\�µķ����ֵ��ɾ,��������ERROR_FILE_NOT_FOUND,
 * @param[in] pszServiceName ������
 * @param[in] pszImagePath �ļ�·��
 * @param[in] pszSvcOrderGroup ����
 * @param[in] pszDisplayName �����Ѻ����� ���Դ�NULL
 * @param[in] pszDescription ��������  ���Դ�NULL
 * @param[in] dwStartType ��������,���SERVICE_DEMAND_START SERVICE_AUTO_START
 * @param[out] pdwError  apiִ�еĴ�����
 * @return TRUE�ɹ�,FALSEʧ��
 */
BOOL KCreateService(const wchar_t* pszServiceName, 
					const wchar_t* pszImagePath,  
					const wchar_t* pszSvcOrderGroup, 
					const wchar_t* pszDisplayName,
					const wchar_t* pszDescription,
					DWORD dwStartType,
					DWORD* pdwError,
					const wchar_t* pDepend = NULL,
					DWORD nServicesType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS);

/**
* @brief		ָֹͣ������
* @remark		
* @param[in]	pszServiceName ������
* @param[out]	pdwError apiִ�еĴ�����
* @return		0 �ɹ�������Ϊ������
**/
BOOL KStopService(const wchar_t* pszServiceName, DWORD* pdwError);

/**
 * @brief ɾ������
 * @remark ���ע���HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\�µķ����ֵ��ɾ,����������ɾ������
 * @param[in] pszServiceName ������
 * @param[out] pdwError apiִ�еĴ�����
 * @return TRUE�ɹ�,FALSEʧ��
 */
BOOL KDeleteService(const wchar_t* pszServiceName, DWORD* pdwError);



/**
 * @brief ������״̬����ͼ�޸�
 * @remark 
 * @param[in] pszServiceName ������
 * @param[in] pszImagePath �ļ�·��
 * @param[in] pszSvcOrderGroup ����
 * @param[in] pszDisplayName ��������
 * @param[out] pnFixAction �޸��Ķ��� 
 * @return TRUE�ɹ�,FALSEʧ��
 */
BOOL CheckAndFixService(const wchar_t* pszServiceName, 
						const wchar_t* pszImagePath,  
						const wchar_t* pszSvcOrderGroup, 
						const wchar_t* pszDisplayName,
						const wchar_t* pszDescription,
						int* pnFixAction,
						DWORD* pdwError);


/**
 * @brief �޸�cryptsvc����
 * @remark 
 * @return 0�ɹ�, ��0ʧ��
 */
int FixCryptService();

BOOL IsNeededReboot(void);
