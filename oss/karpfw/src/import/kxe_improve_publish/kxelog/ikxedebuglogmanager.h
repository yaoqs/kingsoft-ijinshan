#ifndef _IKXEDEBUGMANAGER_H_
#define _IKXEDEBUGMANAGER_H_
#include <Unknwn.h>
#include "IKxEDebugLog.h"

MIDL_INTERFACE("3D95F16F-E754-49ab-8E70-549D686354A4")
IKxEDebugLogManager : public IUnknown
{
public:
	/**
	* @brief ��ʼ����־������һЩ������Դ
	* @remark
	* @return ��(�ɹ�) or ����(ʧ��)
	*/
	virtual int __stdcall Initialize() = 0;

	/**
	* @brief �ͷŷ��䵽����Դ
	* @remark
	*/
	virtual int __stdcall Uninitialize() = 0;

	/**
	* @brief ����һ����ΪpszLogName��IKxEDebugLog����ppLog
	* @remark
	* @param[in ] pszLogName ������
	* @param[out] ppLog ��̬����IKxEDebugLog������ָ��
	* @return ��(�ɹ�) or ����(ʧ��)
	*/
	virtual int __stdcall CreateDebugLog(
		const char* pszLogName, 
		IKxEDebugLog** ppLog
		) = 0;
};

#endif