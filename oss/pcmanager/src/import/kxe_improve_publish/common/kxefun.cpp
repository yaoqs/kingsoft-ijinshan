#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif						

#include "kxefun.h"
#include "serviceprovider/ikxeipcmanageserviceprovider.h"

int KxEGetServicePort(unsigned short* psPort)
{
	KxEPipeClientT<IKxEIPCManageServiceProvider> ipcClient;
	return ipcClient.GetServicePort(L"", *psPort);
}
