/** 
* @file bkrescanbasedata.h
* @brief �������ݶ���
* @author BAO<baoderong@kingsoft.com>
* @date October 30,2010
*/

#ifndef BKRESCANBASEDATA_H
#define BKRESCANBASEDATA_H

#include "bkrstype.h"

#define MAX_CHANNEL_LENGTH 16		/// ͨ���ŵ���󳤶�
#define MAX_VIRUSNAME_LENGTH 60	/// �Ʋ�ɱ���صĲ�������󳤶ȣ����ص�ΪCP_UTF8�ģ���󳤶�Ϊ60���ַ���ĿǰΪֹ������ȫΪӢ���ַ�

/** 
* @enum BKRS_ScanSatus
* @brief ɨ��������ֵ
*/
typedef enum
{
	enumBKRS_White = 0,		/// �޶�
	enumBKRS_Black,			/// �ж�
	enumBKRS_Unknown,		/// δ֪
	enumBKRS_Scanned,		/// �Ѿ���ȫɨ����ˣ�����δ֪���ļ��������ļ�
	enumBKRS_Dropped		/// �ļ�����������ɾ����
} BKRS_ScanStatus;

/** 
* @enum BKRS_ScanSatus
* @brief ɨ��������ֵ
*/
typedef enum
{
	enumBKRS_Null = -1,

	/// handle���
	enumBKRS_Handled = 0,				/// ��ʾ��֪�ļ��Ѿ��������
	enumBKRS_UserSkipHandled = 1,		/// ��ʾ�û���������ļ�

	/// scan���
	enumBKRS_NeedHandled = 0x100,		/// ��ʾ��δ֪����֪����δ������Ҫ����
}BKRS_HandleStatus;

/** 
* @enum BKRS_HistoryQueryType
* @brief ��ɨ��ʷ�ļ���ѯ����
*/
typedef enum
{
	enumHistoryQuery_All = 0,			/// ��ѯ���е��ļ�
	enumHistoryQuery_White,				/// ��ѯ�׵��ļ�
	enumHistoryQuery_Black,				/// ��ѯ�ڵ��ļ�
	enumHistoryQuery_Scanned,			/// ��ѯ�ֵ��ļ������Ѿ�ɨ������ļ�
	enumHistoryQuery_Dropped,			/// ��ѯ�������ļ�
	enumHistoryQuery_Unknown			/// ��ѯδ֪���ļ�
} BKRS_HistoryQueryType;

/** 
* @enum BKRS_RTScannedQueryType
* @brief ���»�ɨ�����ļ���ѯ����
*/
typedef enum
{
	enumRTScannedQuery_All = 0,			/// ��ѯ�������´�������ļ�
	enumRTScannedQuery_White,				/// ��ѯ�������´�����İ��ļ�
	enumRTScannedQuery_Black,				/// ��ѯ�������´�����ĺ��ļ�
	enumRTScannedQuery_Scanned,			/// ��ѯ�������´�����Ļ��ļ����ļ������Ѿ�ɨ������ļ�
	enumRTScannedQuery_Dropped			/// ��ѯ�������¶����ļ����ļ�
} BKRS_RTScannedQueryType;

typedef enum
{
	enumBKRS_From_FastScan = 0x01,			/// �ļ����Կ���ɨ��
	enumBKRS_From_FileMonitor = 0x02,		/// �ļ������ļ����
	enumBKRS_From_FullDiskScan = 0x04,		/// �ļ�����ȫ��ɨ��
	enumBKRS_From_RSS_KXESCANSP = 0x08,		/// �ļ����Զ��Բ�ɱsp
	enumBKRS_From_RSS_USBMONITOR = 0x10,	/// �ļ����Զ���U�̼��
	enumBKRS_From_ALL = 0x80				/// ������Դ��ʵʱ�����ͻ�ɨģ�鲻Ҫ�ã�
}BKRS_FileFromType;

/** 
* @struct BKRS_QueryFileInfo
* @brief ��ѯ���ص��ļ���Ϣ
*/
typedef struct  
{
	wchar_t pszFileName[MAX_PATH];			/// �ļ���
	BYTE pszMD5[16];						/// �ļ���MD5
	FILETIME stLastScanTime;				/// �ļ����ʱ�䣨UnknownΪ�ϴλ�ɨ��ʱ�䣩
	BKRS_ScanStatus enumFileType;			/// �ļ��ڰ�����
	BKRS_HandleStatus enumHandleStatus;		/// �ļ�����֪����û�б�����
	char szVirusName[MAX_VIRUSNAME_LENGTH];	/// �ļ���Ӧ�Ĳ�����
} BKRS_QueryFileInfo;

#endif
