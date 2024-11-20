/********************************************************************
* CreatedOn: 2007-10-12   16:49
* FileName: antiarpioctls.h
* CreatedBy: lidengwang <lidengwang@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL:  $
* Purpose:
*********************************************************************/

#ifndef __ANTIARPIOCTLS_H__
#define __ANTIARPIOCTLS_H__


#define NDIS_DEVICE_ANTIARP        0x8000



//////////////////////////////////////////////////////////////////////////
// ��ȡ����ǽ �汾 
//////////////////////////////////////////////////////////////////////////
#define IOCTL_ANTIARP_GET_VERSION			        \
    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x01, METHOD_BUFFERED, FILE_ANY_ACCESS)

//////////////////////////////////////////////////////////////////////////
// ���÷���ǽ״̬ 
//////////////////////////////////////////////////////////////////////////
#define IOCTL_ANTIARP_SET_STATUS                    \
    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x10, METHOD_BUFFERED, FILE_ANY_ACCESS)

//////////////////////////////////////////////////////////////////////////
// ��ȡ����ǽ״̬ 
//////////////////////////////////////////////////////////////////////////
#define IOCTL_ANTIARP_GET_STATUS                    \
    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x11, METHOD_BUFFERED, FILE_ANY_ACCESS)




//////////////////////////////////////////////////////////////////////////
// ���� ���ýṹ�� ����ǽ״̬   antiarp_config
//////////////////////////////////////////////////////////////////////////
#define IOCTL_ANTIARP_SET_CONFIG                    \
    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x12, METHOD_BUFFERED, FILE_ANY_ACCESS)

//////////////////////////////////////////////////////////////////////////
// ���÷���ǽ ������IP��MAC�б� antiarp_protect_ipmac_list
//////////////////////////////////////////////////////////////////////////
#define IOCTL_ANTIARP_SET_PROCTECT_MACIP_LIST       \
    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x21, METHOD_BUFFERED, FILE_ANY_ACCESS)


//////////////////////////////////////////////////////////////////////////
// ���÷���ǽ ֪ͨ���¼��б� antiarp_config_event
//////////////////////////////////////////////////////////////////////////
#define IOCTL_ANTIARP_SET_CONFIG_EVENT              \
    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x22, METHOD_BUFFERED, FILE_ANY_ACCESS)



//////////////////////////////////////////////////////////////////////////
// ��ȡ���ط��͵�ARP��
//////////////////////////////////////////////////////////////////////////
#define IOCTL_ANTIARP_GET_BLOCK_SEND_ARP_PACKET     \
    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x31, METHOD_BUFFERED, FILE_ANY_ACCESS)


//////////////////////////////////////////////////////////////////////////
// ��ȡ�����յ���ARP��
//////////////////////////////////////////////////////////////////////////
#define IOCTL_ANTIARP_GET_BLOCK_RECEIVE_ARP_PACKET   \
    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x32, METHOD_BUFFERED, FILE_ANY_ACCESS)


//////////////////////////////////////////////////////////////////////////
// ����һ��ARP��
//////////////////////////////////////////////////////////////////////////
#define IOCTL_ANTIARP_SEND_ARP_PACKET   \
    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x41, METHOD_NEITHER, FILE_ANY_ACCESS)



//////////////////////////////////////////////////////////////////////////
// ��ѯһ��MAC��ַ��IP��ַ
//////////////////////////////////////////////////////////////////////////
#define IOCTL_ANTIARP_MAC_TO_IP   \
    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x51, METHOD_BUFFERED, FILE_ANY_ACCESS)


//////////////////////////////////////////////////////////////////////////
// ��ѯһ��IP��ַ��MAC��ַ
//////////////////////////////////////////////////////////////////////////
#define IOCTL_ANTIARP_IP_TO_MAC   \
    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x52, METHOD_BUFFERED, FILE_ANY_ACCESS)

//////////////////////////////////////////////////////////////////////////
// ����һ��IP���˹���
//////////////////////////////////////////////////////////////////////////
#define IOCTL_NDIS_ADD_IP_RULES          CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0012, METHOD_BUFFERED, FILE_ANY_ACCESS)

//////////////////////////////////////////////////////////////////////////
// ɾ��һ��IP���˹���
//////////////////////////////////////////////////////////////////////////
#define IOCTL_NDIS_REMOVE_IP_RULES       CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0013, METHOD_BUFFERED, FILE_ANY_ACCESS)

//////////////////////////////////////////////////////////////////////////
// �������IP���˹���
//////////////////////////////////////////////////////////////////////////
#define IOCTL_NDIS_CLEAR_IP_RULES        CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0014, METHOD_BUFFERED, FILE_ANY_ACCESS)

//////////////////////////////////////////////////////////////////////////
// ���ظ߼�����ģ��
//////////////////////////////////////////////////////////////////////////
#define IOCTL_NDIS_AUTOLOAD_FILTER_MODULES        CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0015, METHOD_BUFFERED, FILE_ANY_ACCESS)

//////////////////////////////////////////////////////////////////////////
// ���ظ߼�����ģ��
//////////////////////////////////////////////////////////////////////////
#define IOCTL_NDIS_CLEAR_FILTER_MODULES        CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0016, METHOD_BUFFERED, FILE_ANY_ACCESS)

//////////////////////////////////////////////////////////////////////////
// ��ȡIP��־
//////////////////////////////////////////////////////////////////////////
#define IOCTL_NDIS_GET_COMMON_EVENT        CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0017, METHOD_BUFFERED, FILE_ANY_ACCESS)

//ö��������Ϣ
#define IOCTL_NDIS_ENUM_ADAPTER        CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0080, METHOD_BUFFERED, FILE_ANY_ACCESS)


//����ARP���ر�־
#define IOCTL_NDIS_SET_BLOCK_FLAG   CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0083, METHOD_BUFFERED, FILE_ANY_ACCESS)

//����NDIS��־�����־
#define IOCTL_NDIS_SET_LOG_FLAG   CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0084, METHOD_BUFFERED, FILE_ANY_ACCESS)

//��������ģ���־	�� ENABLE_FUNCTION
#define IOCTL_NDIS_ENABLE_MODULE_FLAG   CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0085, METHOD_BUFFERED, FILE_ANY_ACCESS)

//����/��������
#define IOCTL_NDIS_ENABLE_NETWORK   CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0086, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_NDIS_DISABLE_NETWORK   CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0087, METHOD_BUFFERED, FILE_ANY_ACCESS)

//���/ɾ���߼������˹���
#define IOCTL_NDIS_ADD_ADV_IP_RULES       CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0088, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_NDIS_REMOVE_ADV_IP_RULES    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0089, METHOD_BUFFERED, FILE_ANY_ACCESS)
//����߼������˹���
#define IOCTL_NDIS_CLEAR_ADV_IP_RULES     CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0090, METHOD_BUFFERED, FILE_ANY_ACCESS)
 
//����ʵʱ֪ͨ���ص�ʱ����
#define IOCTL_NDIS_SET_NOTIFY_TIMER    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0091, METHOD_BUFFERED, FILE_ANY_ACCESS)

//������������б�
#define IOCTL_ANTIARP_CLEAR_PROCTECT_MACIP_LIST    CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0092, METHOD_BUFFERED, FILE_ANY_ACCESS)

//���÷���GUID���Լ���ping
#define IOCTL_NDIS_SET_PASS_GUID  CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0093, METHOD_BUFFERED, FILE_ANY_ACCESS)

//ö�ٲ�������
#define IOCTL_NDIS_ENUM_RAS_CONNECTION  CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0094, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_NDIS_SELECT_GATEWAY_MAC	CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0095, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_NDIS_CLEAN_GATEWAY_MAC	CTL_CODE(NDIS_DEVICE_ANTIARP, 0x0096, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

