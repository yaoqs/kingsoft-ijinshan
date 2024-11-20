/********************************************************************
* CreatedOn: 2005-8-16   16:40
* FileName: SCOMError.h
* CreatedBy: qiuruifeng <qiuruifeng@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/

#ifndef SCOMERROR_H
#define SCOMERROR_H

#ifdef WIN32
#include <WinError.h>
#else

#define SUCCEEDED(Status) ((long)(Status) >= 0)

#define S_OK					(long)0x00000000L
#define S_FALSE					(long)0x00000001L
#define E_NOTIMPL				(long)0x80000001L
#define E_OUTOFMEMORY			(long)0x80000002L
#define E_INVALIDARG			(long)0x80000003L
#define E_NOINTERFACE			(long)0x80000004L
#define E_POINTER				(long)0x80000005L
#define E_HANDLE				(long)0x80000006L
#define E_ABORT					(long)0x80000007L
#define E_FAIL					(long)0x80000008L
#define CLASS_E_NOAGGREGATION     	(long)0x80040110L
#define CLASS_E_CLASSNOTAVAILABLE 	(long)0x80040111L
#define REGDB_E_CLASSNOTREG			(long)0x80040154L
#define CO_E_DLLNOTFOUND			(long)0x800401F8L
#define NTE_NOT_FOUND				(long)0x80090011L
//#define ERROR_MOD_NOT_FOUND              126L
//#define ERROR_PROC_NOT_FOUND             127L
#endif

#define E_SCOM_MOD_NOT_FOUND		(long)0x82000001L
#define E_SCOM_PROC_NOT_FOUND		(long)0x82000002L
#define E_SCOM_MOD_HAVE_LOADED		(long)0x82000003L
#define E_SCOM_MOD_HAVE_REGISTERED	(long)0x82000004L
#define E_SCOM_COMPONENT_HAVE_REGISTERED	(long)0x82000005L
#define E_SCOM_SIZE_PARAMETER_INVALID		(long)0x82000006L
#define E_SCOM_GET_WORK_DIRECTORY_FAILED	(long)0x82000007L
#define E_SCOM_GET_CONFIG_FILE_FULL_PATH_FAILED	(long)0x82000008L
#define E_SCOM_BUF_LENGTH_NOT_ENOUGH		(long)0x82000009L
#define E_SCOM_COMPONENT_LEAK_ERROR			(long)0x8200000AL
#define E_SCOM_DLL_PATH_NOT_ACCQUIRED_FROM_CONFIGURATION_FILE	(long)0x8200000BL

//�����ļ���ʽ����
//#define E_CONFIGFILEFORMAT_ERROR       (long)0x81000001L

//���������ļ�����
//#define E_CONFIGFILEREAD_ERROR         (long)0x81000002L

//д�������ļ�����
//#define E_CONFIGFILEWRITE_ERROR        (long)0x81000003L

//�Ҳ������
//#define E_SCOM_NOT_FOUND               (long)0x81000004L

//û�ж�λ�ļ�
//#define E_SCOM_NO_LOCATE_FILE          (long)0x81000005L

//û�г�ʼ��
//#define E_SCOM_NOTINIT                 (long)0x81000006L

#endif //SCOMERROR_H