#ifndef _IKAV_RECYCLE_H_
#define _IKAV_RECYCLE_H_


#include "unknwn.h"
#include "ikaqfileinfo.h"


// {DD0240C9-F3FB-43c0-B74E-2E3070100AD6}
extern const GUID IID_KAVRECYCLE; 

#define E_FILE_EXISTS             0x04000001
#define E_DISK_FULL               0x84000001
#define E_GENERATE_FILE_FAILED    0x84000002
#define E_DELETE_FILE_FAILED      0x84000003
#define E_GET_FILE_INFO_FAILED    0x84000004
#define E_SET_FILE_ATTRIB_FAILED  0x84000005
#define E_FILE_NOT_FOUND          0x80070006
#define E_INITIALIZE_FAIL         0x84000007


typedef struct _KAVQUARN_SETTING
{
	DWORD	dwQuaranSpaceQuota;			// ����Ŀ¼��С����������Ϊ��λ��
	wchar_t	szQuaranPath[MAX_PATH];		// ����Ŀ¼��·��
} KAVQUARN_SETTING;


/** \class IKAVRecycle
* \brief �����ļ��ӿ�
*/
class IKAVRecycle : public IUnknown
{
public:
	/**	\brief �����ļ�
    * \param   pszQuarnFile	    ָ��Ҫ������ļ���
	* \param   pszVirusName		������
	* \param   nOption		    = 0 �����ɾ��;  = 2 �����ɾ��
	* \return  �ɹ�����S_OK
	*/
	virtual HRESULT STDMETHODCALLTYPE QuarantineFile(
		const wchar_t* pszQuarnFile, 
		const wchar_t* pszVirusName, 
		int nOption) = 0;

	/** \brief �ָ������ļ�
	* \param   pszQuarantFile     �����ļ��� (������ļ���)
	* \param   pszFileName        �ָ��ļ���
	* \return  �ɹ�����S_OK
	*/
	virtual HRESULT STDMETHODCALLTYPE RestoreQuarantineFile(
		const wchar_t* pszQuarantFile, 
		const wchar_t* pszRestoreFile) = 0;

	/** \brief ɾ�������ļ�
	* \param   pszFileName   �����ļ��� (������ļ���)
	* \return  �ɹ�����S_OK
	*/
	virtual HRESULT STDMETHODCALLTYPE DeleteQuarantineFile(
		const wchar_t* pszFileName) = 0;

	/** \brief �õ��Ѹ����ļ���Ϣ
	* \param   ppInfos  ����IKAQFileInfo�ӿ�
	* \return  �ɹ�����S_OK, �������Ŀ¼Ϊ�շ���E_FILE_NOT_FOUND
	*/
	virtual HRESULT STDMETHODCALLTYPE GetQuarantineInfo(
		IKAQFileInfo** ppInfos) = 0;

	/** \brief  ���ⲿ�����ļ���ȡ�������ļ����� 
	* \param    pCount  �����ļ���
	* \return   �ɹ�����S_OK
	*/
	virtual HRESULT STDMETHODCALLTYPE GetQuarantineFileCount(
		unsigned long* pCount) = 0;

	/** \brief δʹ��
	*/
	virtual HRESULT STDMETHODCALLTYPE SetSetting(
		KAVQUARN_SETTING setting) = 0;

	/** \brief δʹ��
	*/
	virtual HRESULT STDMETHODCALLTYPE GetSetting(
		KAVQUARN_SETTING* pSetting) = 0;
};


#endif