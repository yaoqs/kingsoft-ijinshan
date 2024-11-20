//////////////////////////////////////////////////////////////////////
///		@file		IKxEMemFeatureOp.h
///		@author		YangBin
///		@date		2009-01-04
///
///		@brief		�ڴ������Ľӿڶ���
//////////////////////////////////////////////////////////////////////
#ifndef _IKXE_MEMORY_RES_OPERATE_H_
#define _IKXE_MEMORY_RES_OPERATE_H_

// �ڴ������ļ�ͷ�ṹ��
typedef struct _KXE_MEM_FEATURE_FILE_HEADER
{
    DWORD dwFileFlag;       //�ļ���ʶ
    SYSTEMTIME timestamp;   //�ļ�����ʱ��
    DWORD dwDataSize;       //���ݴ�С���������ļ�ͷ��
    DWORD dwItemNum;        //�����������
}KXE_MEM_FEATURE_FILE_HEADER, *PKXE_MEM_FEATURE_FILE_HEADER;

typedef struct _KXE_MEM_FEATURE_INDEX
{
    DWORD dwId;             //��ÿ�������Զ����ID��Ψһ��
    DWORD dwSigOffset;      //��Ӧ������������ݿ����ļ��е�ƫ��
}KXE_MEM_FEATURE_INDEX, *PKXE_MEM_FEATURE_INDEX;

//һ���ṹ����һ������
typedef struct _KXE_MEM_FEATURE_SIGNATURE_BLOCK
{
    DWORD dwFeatureSize;           //������С
    DWORD dwFeatureOffset;         //����ƫ��
    DWORD dwVirusNameSize;         //��������С
    DWORD dwVirusNameOffset;       //������ƫ��
    UCHAR data[1];                 //���ݣ������������ֽڣ��󲡶��������ֽڣ�
}KXE_MEM_FEATURE_SIGNATURE_BLOCK, *PKXE_MEM_FEATURE_SIGNATURE_BLOCK;

//һ�������Ӧһ��KXE_MEM_FEATURE_SIGNATURE
typedef struct _KXE_MEM_FEATURE_SIGNATURE
{
    DWORD dwBlockNum;   //��������
    KXE_MEM_FEATURE_SIGNATURE_BLOCK blocks[1];  //���������飬������dwBlockNum����
}KXE_MEM_FEATURE_SIGNATURE, *PKXE_MEM_FEATURE_SIGNATURE;

#define KXE_MEM_FEATURE_GET_INDEX_NUM( _pFileHeader )    (((PKXE_MEM_FEATURE_FILE_HEADER)(_pFileHeader))->dwItemNum)

#define KXE_MEM_FEATURE_GET_FIRST_INDEX( _pFileHeader )  (PKXE_MEM_FEATURE_INDEX)((PCHAR)(_pFileHeader) + sizeof(KXE_MEM_FEATURE_FILE_HEADER))

#define KXE_MEM_FEATURE_GET_SIGNATURE( _pFileHeader, _SigOffest )     (PKXE_MEM_FEATURE_SIGNATURE)((PCHAR)KXE_MEM_FEATURE_GET_FIRST_INDEX( _pFileHeader ) + KXE_MEM_FEATURE_GET_INDEX_NUM( _pFileHeader ) * sizeof(KXE_MEM_FEATURE_INDEX) + (_SigOffest) )

#define KxEGetStructFieldOffSet( type, field ) ( ULONG_PTR )( &( ( type* ) 0 )->field  )

#define KXE_MEM_FEATURE_GET_FEATURE( _pSigBlock )   (PUCHAR)(_pSigBlock) + KxEGetStructFieldOffSet( KXE_MEM_FEATURE_SIGNATURE_BLOCK, data )

#define KXE_MEM_FEATURE_GET_VIRUSNAME( _pSigBlock )   (PWCHAR)((PUCHAR)(_pSigBlock) + KxEGetStructFieldOffSet( KXE_MEM_FEATURE_SIGNATURE_BLOCK, data ) + ((PKXE_MEM_FEATURE_SIGNATURE_BLOCK)(_pSigBlock))->dwVirusNameOffset)

#define KXE_MEM_FEATURE_GET_BLOCK_SIZE( _pSigBlock )  ((PKXE_MEM_FEATURE_SIGNATURE_BLOCK)(_pSigBlock))->dwFeatureSize + ((PKXE_MEM_FEATURE_SIGNATURE_BLOCK)(_pSigBlock))->dwVirusNameSize + KxEGetStructFieldOffSet( KXE_MEM_FEATURE_SIGNATURE_BLOCK, data )

#define MEMORY_FEATURE_FILE_FLAG    'fmgK'    //kingsoft game memory feature

/**
* @class        IKxEMemFeatureOpInFile
* @brief        ������ϵͳ�ڴ������ļ������ӿ�
*
* @details      ����ֱ�Ӳ����ڴ������ļ��Ľӿ�
*/
interface IKxEMemFeatureOpInFile
{
    /**
    * @brief        ��ʼ���ڴ���Դ
    * @param[in]    pwszMemResFileName �ڴ���Դ�ļ���	
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall Initialize( 
        IN PWCHAR pwszMemResFileName
        ) = 0;

    /**
    * @brief        ����ʼ���ڴ���Դ
    * @param[in]    	
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall UnInitialize( ) = 0;

    /**
    * @brief        ���ڴ������ļ�����һ������
    * @param[in]    ulId            ����ID
    *               pszFeature      ��������
    *               ulFeatureSize   ������С
    *               pwszVirusName   ������
    *               ulVirusNameSize ��������С�����ַ����������ֽڣ�
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall InsertFeature( 
        IN ULONG  ulId, 
        IN PUCHAR pszFeature, 
        IN ULONG  ulFeatureSize,
        IN PWCHAR pwszVirusName,
        IN ULONG  ulVirusNameSize
        ) = 0;
    
    /**
    * @brief        ���ڴ������ļ�ɾ��ָ�������ĳ������
    * @param[in]    ulId            ����ID
    *               pszFeature      ��������
    *               ulFeatureSize   ������С
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall DeleteFeature( 
        IN ULONG  ulId, 
        IN PUCHAR pszFeature, 
        IN ULONG  ulFeatureSize 
        ) = 0;

    /**
    * @brief        ���ڴ������ļ�ɾ��ָ���������������
    * @param[in]    ulId    ����ID
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall DeleteFeatures( 
        IN ULONG ulId
        ) = 0;

    /**
    * @brief        ɾ�������ڴ������ļ�
    * @param[in]    ��
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall DeleteAll() = 0;

    /**
    * @brief        �޸�ĳ�����ĳ������
    * @param[in]    ulId               ����ID
    *               pszOldFeature      ����������
    *               ulOldFeatureSize   ��������С
    *               pszNewFeature      ����������
    *               ulNewFeatureSize   ��������С
    *               pwszOldVirusName   �ɲ�����
    *               ulOldVirusNameSize �ɲ�������С
    *               pwszNewVirusName   �²�����
    *               ulNewVirusNameSize �²�������С
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall ModifyFeature( 
        IN ULONG  ulId, 
        IN PUCHAR pszOldFeature, 
        IN ULONG  ulOldFeatureSize, 
        IN PUCHAR pszNewFeature,
        IN ULONG  ulNewFeatureSize,
        IN PWCHAR pwszOldVirusName,
        IN ULONG  ulOldVirusNameSize,
        IN PWCHAR pwszNewVirusName,
        IN ULONG  ulNewVirusNameSize
        ) = 0;

    /**
    * @brief        ���޸�д���ڴ������ļ���
    * @param[in]    ��
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall Flush() = 0;
};

/**
* @class        IKxEMemFeatureReadOp
* @brief        ������ϵͳ���ڴ������ļ������ӿ�
*
* @details      �����ȡ�ڴ������ļ��Ľӿ�
*/
interface IKxEMemFeatureReadOp
{
    /**
    * @brief        ��ʼ��
    * @param[in]    pwszMemResFileName      �ڴ���Դ�ļ���	
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall Initialize( 
        IN PWCHAR pwszMemResFileName
        ) = 0;

    /**
    * @brief        ����ʼ��
    * @param[in]    	
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall UnInitialize( ) = 0;

    /**
    * @brief        ���ݳ���ID�õ���Ӧ�ڴ�����
    * @param[in]    ulId           ����ID
                    ppszBlocks     �ڴ�����buffer
                    pdwBlockNum    �ڴ���������                   
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall GetFeaturesByProcId( 
        IN  ULONG  ulId, 
        OUT PUCHAR *ppszBlocks, 
        OUT PDWORD pdwBlockNum 
        ) = 0;

    /**
    * @brief        �õ��ڴ��ļ��汾
    * @param[out]   pTime   ���صİ汾��Ϣ                   
    * @return       S_OK    �ɹ�
    *               E_FAIL  ʧ��
    */
    virtual HRESULT __stdcall GetMemFileVersion( IN SYSTEMTIME *pTime ) = 0;

    /**
    * @brief        �õ��ڴ���������
    * @param[in]    ��                  
    * @return       != 0    �ɹ�
    *               == 0    ʧ��
    */
    virtual DWORD __stdcall GetMemProcNum() = 0;

    /**
    * @brief        �õ���һ�������������
    * @param[out]   pulProcId   ���صĳ���ID
    *               ppszBlocks  ���صĳ����ڴ�������
    *               pdwBlockNum ���صĳ����ڴ���������
    * @return       TRUE    �ɹ�
    *               FALSE   ʧ��
    */
    virtual BOOL __stdcall GetFirstProc( 
        OUT ULONG  *pulProcId, 
        OUT PUCHAR *ppszBlocks,
        OUT PDWORD pdwBlockNum 
        ) = 0;

    /**
    * @brief        �õ���һ�������������
    * @param[out]   pulProcId   ���صĳ���ID
    *               ppszBlocks  ���صĳ����ڴ�������
    *               pdwBlockNum ���صĳ����ڴ���������
    * @return       TRUE    �ɹ�
    *               FALSE   ʧ�ܣ�����������
    */
    virtual BOOL __stdcall GetNextProc(
        OUT ULONG  *pulProcId, 
        OUT PUCHAR *ppszBlocks,
        OUT PDWORD pdwBlockNum 
        ) = 0;
    
};

#endif