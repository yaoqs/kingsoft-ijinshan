////////////////////////////////////////////////////////////////////////////////
//      
//      common include File for kpfw
//      
//      File      : errorcode.h
//      Version   : 1.0
//      Comment   : �������ڷ�����ֳ������
//      
//      Create at : 2008-4-7
//      Create by : liupeng
//      
////////////////////////////////////////////////////////////////////////////////

#pragma once 

//////////////////////////////////////////////////////////////////////////
// ��������ʽ����windows ���������ݣ�
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |  Class    |         Code      |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//		Class - is the facility's function class
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//

// ���ڷ���
#define FACILITY_KPFW					0x701

#define ERROR_CODE_BUILDER(level, facility, cls, c)		\
		(( ((int)(level) & 0xf) << 28 ) | ( ((int)facility & 0xfff) << 16 ) | ( ((int)cls & 0x3f) << 10 ) | ( (int)c & 0x3ff ))

#define ERROR_CODE(facility, cls, c)	ERROR_CODE_BUILDER( 0xC, facility, cls, c)

#define WARING_CODE(facility, cls, c)	ERROR_CODE_BUILDER( 0x8, facility, cls, c )

#define KPFW_ERROR(cls, c)				ERROR_CODE( FACILITY_KPFW, cls, c )

#define KPFW_WARNING(cls, c)			WARING_CODE( FACILITY_KPFW, cls, c )

// ���ڴ�������
#define KPFW_ECLASS_IPRULE				0x01
#define KPFW_ECLASS_APPRULE				0x02
#define KPFW_ECLASS_ARP					0x03
#define KPFW_ECLASS_LOG					0x04
#define KPFW_ECLASS_DRIVER				0x05
#define KPFW_ECLASS_AREA				0x06
#define KPFW_ECLASS_BADURL				0x07

//////////////////////////////////////////////////////////////////////////
// ��������

//////////////////////////////////////////////////////////////////////////
// ip������ش���:

// ip�����ļ���ʧ��
#define E_IP_FILE_OPEN_FAILED			KPFW_ERROR( KPFW_ECLASS_IPRULE, 0x1)

// ip�����ļ����ƻ�
#define E_IP_FILE_DAMAGED				KPFW_ERROR( KPFW_ECLASS_IPRULE, 0x2)

// Ĭ��ip�����ļ���ʧ��
#define E_DEFAULT_IP_FILE_OPEN_FAILED	KPFW_ERROR( KPFW_ECLASS_IPRULE, 0x3)

// ip�����ļ�����ʧ��
#define E_IP_FILE_SAVE_FAILED			KPFW_ERROR( KPFW_ECLASS_IPRULE, 0x4)

// ����ʶ��� ip�����ļ���ʽ
#define E_IP_FILE_UNKNOWN_FMT			KPFW_ERROR( KPFW_ECLASS_IPRULE, 0x5)

// ��ʶ���ļ���ʽ
#define E_BADURL_FILE_UNKNOWN_FMT			KPFW_ERROR( KPFW_ECLASS_BADURL, 0x6)

//////////////////////////////////////////////////////////////////////////
// ������ش���:

// ������ʼ��ʧ��
#define E_DIRVER_INIT_FAILED			KPFW_ERROR( KPFW_ECLASS_DRIVER, 0x1)

// ������������
#define E_DIRVER_PROXY_NOTEXIST			KPFW_ERROR( KPFW_ECLASS_DRIVER, 0x2)

//////////////////////////////////////////////////////////////////////////
// Ӧ�ó��������ش���:

// Ӧ�ó�������ļ���ʧ��
#define E_APP_FILE_OPEN_FAILED			KPFW_ERROR( KPFW_ECLASS_APPRULE, 0x1)

// Ӧ�ó�������ļ����ƻ�
#define E_APP_FILE_DAMAGED				KPFW_ERROR( KPFW_ECLASS_APPRULE, 0x2)

// ����ʶ���Ӧ�ó�������ļ�
#define E_APP_FILE_UNKNOWN_FMT			KPFW_ERROR( KPFW_ECLASS_APPRULE, 0x3)

// Ӧ�ó�������ļ�����ʧ��
#define E_APP_FILE_SAVE_FAILED			KPFW_ERROR( KPFW_ECLASS_APPRULE, 0x4)
// 

//////////////////////////////////////////////////////////////////////////
// ����������

// ��������ļ���ʧ��
#define E_AREA_FILE_OPEN_FAILED			KPFW_ERROR( KPFW_ECLASS_AREA, 0x1)

// ��������ļ����ƻ�
#define E_AREA_FILE_DAMAGED				KPFW_ERROR( KPFW_ECLASS_AREA, 0x2)

// ��������ļ�����ʧ��
#define E_AREA_FILE_SAVE_FAILED			KPFW_ERROR( KPFW_ECLASS_AREA, 0x4)

// ����ʶ��� ��������ļ���ʽ
#define E_AREA_FILE_UNKNOWN_FMT			KPFW_ERROR( KPFW_ECLASS_AREA, 0x5)
