#ifndef MD5_INC_
#define MD5_INC_

/**
 * @defgroup kxearchitecture_md5_group KXEngine MD5 Function
 * @section kxearchitecture_md5_group_support �ṩ��:������
 * @ref kxearchitecture_md5_example_page
 * @{
 */

//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif


/* Any 32-bit or wider unsigned integer data type will do */
typedef unsigned int MD5_u32plus;

/**
 * @brief ����MD5��������ݽṹ
 */
typedef struct {
	MD5_u32plus lo, hi;
	MD5_u32plus a, b, c, d;
	unsigned char buffer[64];
	MD5_u32plus block[16];
} cli_md5_ctx;

/**
 * @brief ��ʼ��MD5�ļ���ṹ
 * @param[out] ctx ��ʼ���õĽṹ���з���
 */
extern void cli_md5_init(cli_md5_ctx *ctx);

/**
 * @brief ����data���ݽ���MD5�ļ���
 * @param[in] ctx ͨ��cli_md5_init��ʼ��������
 * @param[in] data ��Ҫ����MD5�����buffer
 * @param[in] size ָ����data�ĳ���
 */
extern void cli_md5_update(cli_md5_ctx *ctx, void *data, unsigned long size);

/**
 * @brief ����data���ݽ���MD5�ļ���
 * @param[in] result ��ȡ����õ���MD5�Ľ��,��bufferΪ16�ֽڳ�
 * @param[in] ctx ͨ��cli_md5_init��cli_md5_update���������ݽṹ
 */
extern void cli_md5_final(unsigned char *result, cli_md5_ctx *ctx);

#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////

/**
 * @}
 */

/**
 * @page kxearchitecture_md5_example_page The Example of MD5 Function
 * @section kxearchitecture_md5_example_support �ṩ��:������
 * @section kxearchitecture_md5_example KXEngine MD5 Example
 * @code

 #include "MD5.h"

int PathToNameHash( WCHAR *pwszFilePath,ULONGLONG &ullHash )
{
	ULONG		ulLoopCount;
	ULONG		ulHash1Tmp	=	0;
	ULONG		ulHash2Tmp	=	0;
	ULONG       ulFileNameLength = 0;
	PUCHAR		byPtr = NULL;
	UCHAR		ucTemp = 0;
	int			nStatus = 0;

	if ( pwszFilePath == NULL )
	{
		nStatus = ERROR_INVALID_PARAMETER;
		goto Exit0;
	}

	byPtr = (PUCHAR)pwszFilePath;
	ulFileNameLength = ( ULONG )wcslen( pwszFilePath );
	if( ulFileNameLength >= MAX_PATH )
	{
		return ERROR_INVALID_PARAMETER;
	}
	ulFileNameLength = ulFileNameLength * sizeof( WCHAR );

	for(ulLoopCount = 0; ulLoopCount < ulFileNameLength; ulLoopCount++)
	{
		ucTemp	= g_KAV_LowerToUpperTable[ byPtr[ ulLoopCount ] ];

		ulHash1Tmp = ( ulHash1Tmp * 37 ) + ucTemp;
		ulHash2Tmp = ( ulHash2Tmp * 31 ) + ucTemp;
	}
	ullHash = ulHash1Tmp;
	ullHash = ullHash<<32;
	ullHash += ulHash2Tmp;

Exit0:
	return nStatus;
}

int PathToMD5( WCHAR *wszFilePath,MD5 FileMD5)
{
	if( NULL == FileMD5 )
		return -1; 

	HANDLE hTheFile = NULL;
	int iStatus = 0;
	DWORD nRet = 0;    
	cli_md5_ctx md5ctx;
	BYTE *lpBuffer = NULL;

	hTheFile =
		CreateFile( (LPCWSTR)wszFilePath,
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if( INVALID_HANDLE_VALUE == hTheFile)
	{
		iStatus = GetLastError();
		return iStatus;
	}

	lpBuffer = new BYTE[0x1000];
	if (!lpBuffer)
	{
		iStatus = 2;
		goto Exit0;
	}

	cli_md5_init(&md5ctx);

	for (;;)
	{
		iStatus = ReadFile( hTheFile,
			lpBuffer,
			0x1000,
			&nRet,
			NULL );
		if (!iStatus || !nRet)
			break;

		//
		// Idle for IO & CPU
		// 
		cli_md5_update(&md5ctx, lpBuffer, nRet);
	}

	cli_md5_final(FileMD5, &md5ctx);
	iStatus = 0;
Exit0:
	if( NULL != hTheFile )
		CloseHandle( hTheFile );
	if (lpBuffer)
	{
		delete[] lpBuffer;
		lpBuffer = NULL;
	}
	return iStatus;
}
 * @endcode
 */



#endif  // !MD5_INC_