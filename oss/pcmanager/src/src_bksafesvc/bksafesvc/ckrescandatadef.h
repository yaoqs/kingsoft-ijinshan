/** 
* @file     ckrescandatadef.h
* @author   jiaoyafei
* @date     2010-11-15
* @brief    ��ɨ���ݶ���
*/
  
#ifndef _KRESCAN_DATA_DEF_H__
#define _KRESCAN_DATA_DEF_H__

#include <string>
#include "include/kxe_serialize.h"

//> ��������Ҫ��ɨ���ļ�����Դ
enum EM_BKRS_DATASOURCE
{
    EM_BKRS_DATASOURCE_FASTSCAN     = 0x01,		//> �ļ����Կ���ɨ��
    EM_BKRS_DATASOURCE_FILEMONITOR  = 0x02,		//> �ļ������ļ����
    EM_BKRS_DATASOURCE_FULLDISKSCAN = 0x04		//> �ļ�����ȫ��ɨ�� 
};

KXE_JSON_DDX_ENUM(EM_BKRS_DATASOURCE);


//> ��ӻ�ɨ�ļ����������
typedef struct _S_INFO_OF_INSERTFILE
{
    std::wstring       strFileName;
    std::vector<BYTE>  vecMD5;
    std::wstring       strChannel;
    EM_BKRS_DATASOURCE emSource;
} S_INFO_OF_INSERTFILE;

KXE_JSON_DDX_BEGIN(S_INFO_OF_INSERTFILE)
    KXE_JSON_DDX_MEMBER("FileName",   strFileName)
    KXE_JSON_DDX_MEMBER("MD5",        vecMD5)
    KXE_JSON_DDX_MEMBER("Channel",    strChannel)
    KXE_JSON_DDX_MEMBER("DataSource", emSource)
KXE_JSON_DDX_END()



#endif //> _KRESCAN_DATA_DEF_H__

