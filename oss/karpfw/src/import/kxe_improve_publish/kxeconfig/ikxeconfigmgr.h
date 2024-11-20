//////////////////////////////////////////////////////////////////////
///		@file		ikxeconfigmgr.h
///		@author		luopeng
///		@date		2008-10-07 09:07:58
///	
///		@brief		kxeconfig��ض���
//////////////////////////////////////////////////////////////////////

#pragma once
#include <Unknwn.h>

/**
 * @defgroup kxeconfig_component_interface KXEngine Architecture Config Component Interface
 * @remark  1. �����������ƽ̨���������ʹ��\n
 *          2. ������ڷ���ע���ʱ,����ȫ����WOW64��ע�������,����32λ��ע������ݽ��ж�ȡ,�Ա�֤64λ��ģ�������
 * @{
 */

/**
 * @brief �򿪵ļ�ֵ����
 */
typedef enum _KXE_CONFIG_TYPE
{
	enum_KCT_User,          ///< ��ǰ�û���
	enum_KCT_LoalMachine    ///< ���ػ�����
} KXE_CONFIG_TYPE;

/**
 * @brief ����ǰ�ļ�����
 */
class IKxEConfigKey
{
public:
	/**
	 * @brief �ͷŸü�����Դ,�ü������ر�
	 */
	virtual void __stdcall Release() = 0;

	/**
	 * @brief ɾ����ǰKey��SubKey
	 * @param[in] pwszSubKey ��Ҫɾ�����Ӽ����·��
	 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
	 */
	virtual int __stdcall DeleteKey(
		const wchar_t* pwszSubKey
		) = 0;

	/**
	 * @brief ��ȡ��ǰ�����������·��
	 * @return ���ص�ǰ��������·��
	 */
	virtual const wchar_t* __stdcall GetKeyPath() = 0;

	/**
	 * @brief ��ȡ��ǰ�������������
	 * @return ���ص�ǰ��������
	 */
	virtual KXE_CONFIG_TYPE __stdcall GetKeyType() = 0;

	/**
	 * @brief ö�ٵ�ǰ�����Ӽ�
	 * @param[in] nIndex ö�ٵ�nIndex���Ӽ�
	 * @param[out] ppKey ��ȡ���Ӽ��󷵻�
	 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
	 */
	virtual int __stdcall EnumChildKey(
		int nIndex, 
		IKxEConfigKey** ppKey
		) = 0;

	/**
	 * @brief ��ٵ�ǰ�����Ӽ�����
	 * @param[in] nIndex ö�ٵ�nIndex���Ӽ�
	 * @param[in] pwszBuffer ���ڴ洢�Ӽ���buffer
	 * @param[in] nBufferLength ����ָ��pwszBuffer�Ĵ�С,��λΪwchar_t
	 * @param[out] pnReturnBuffer ��Ҫ��buffer��С, ��λΪwchar_t,�����ַ���������
	 * @return 0 �ɹ�,������Ϊʧ�ܴ�����
	 */
	virtual int __stdcall EnumChildKey(
		int nIndex,
		wchar_t* pwszBuffer,
		int nBufferLength,
		int* pnReturnBuffer
		) = 0;

	/**
	 * @brief ���õ�ǰ���µ�Value����
	 * @param[in] pwszValueName Ҫָ���ĵ�ValueName
	 * @param[in] pwszValue Ҫ�洢������,ֻ�����ַ���
	 * @param[in] nValueLength ���ַ����ĳ���,�����ַ���������, ��λΪwchar_t
	 */
	virtual int __stdcall SetValue(
		const wchar_t* pwszValueName, 
		const wchar_t* pwszValue,
		int nValueLength
		) = 0;

	/**
	 * @brief ��ѯ��ǰ���µ�Value����
	 * @param[in] pwszValueName Ҫָ���ĵ�ValueName
	 * @param[in] pwszValueBuffer ��ȡ�������ݴ洢��buffer
	 * @param[in] nValueLength ���ַ����ĳ���,�����ַ���������, ��λΪwchar_t
	 * @param[out] pnReturnValueLength ��Ҫ���ַ�������,�����ַ���������,��λΪwchar_t
	 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
	 */
	virtual int __stdcall QueryValue(
		const wchar_t* pwszValueName,
		wchar_t* pwszValueBuffer,
		int nValueLength,
		int* pnReturnValueLength
		) = 0;

	/**
	 * @brief ɾ��ָ�����µ�ָ��ValueName
	 * @param[in] pwszValueName Ҫɾ����ValueName
	 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
	 */
	virtual int __stdcall DeleteValue(
		const wchar_t* pwszValueName
		) = 0;
};

/**
 * @brief ���ù�����
 */
MIDL_INTERFACE("83FB006E-CFCB-45be-8E12-80EE44C06A3E")
IKxEConfigMgr : public IUnknown
{
	/**
	 * @brief ��ʼ�����ù�����
	 */
	virtual int __stdcall Initialize() = 0;

	/**
	 * @brief ����ʼ�����ù�����
	 */
	virtual int __stdcall Uninitialize() = 0;

	/**
	 * @brief ������ʼ�����ù�����
	 */
	virtual int __stdcall Start() = 0;

	/**
	 * @brief ֹͣ���ù�����
	 */
	virtual int __stdcall Stop() = 0;

	/**
	 * @brief �������ü�,����ü�����,�����
	 * @param[in] type �򿪵ļ�����
	 * @param[in] pwszPath ��Ҫ�򿪵�·��
	 * @param[out] ppConfigKey ���ڴ洢�򿪵�key
	 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
	 */
	virtual int __stdcall CreateKey(
		KXE_CONFIG_TYPE type,
		const wchar_t* pwszPath,
		IKxEConfigKey** ppConfigKey
		) = 0;

	/**
	 * @brief �����ü�,����ü�������,��ʧ��
	 * @param[in] type �򿪵ļ�����
	 * @param[in] pwszPath ��Ҫ�򿪵�·��
	 * @param[out] ppConfigKey ���ڴ洢�򿪵�key
	 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
	 */
	virtual int __stdcall OpenKey(
		KXE_CONFIG_TYPE type,
		const wchar_t* pwszPath,
		IKxEConfigKey** ppConfigKey
		) = 0;

	/**
	 * @brief ɾ�����ü�
	 * @param[in] type ������
	 * @param[in] pwszPath ��Ҫɾ����·��
	 * @return 0 �ɹ�, ����Ϊʧ�ܴ�����
	 */
	virtual int __stdcall DeleteKey(
		KXE_CONFIG_TYPE type,
		const wchar_t* pwszPath
		) = 0;
};

/**
 * @}
 */