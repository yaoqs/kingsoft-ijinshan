
#ifndef __PUBLICSTRUCT_H__
#define __PUBLICSTRUCT_H__


typedef struct tagFIND_FILE_DATA
{
    LPCTSTR     pszFileNmae;    // �ļ���
    LPCTSTR     pszPathName;    // �ļ�·��
    
    LPCTSTR     pszExtName;     // ��չ��
    ULONGLONG   uFileSize;      // �ļ���С
	int         nCount;
    
}FINDFILEDATA, *LPFINDFILEDATA;

#endif //__PUBLICSTRUCT_H__