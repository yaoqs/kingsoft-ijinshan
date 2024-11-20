#include "stdafx.h"
#include "common.h"
#include "scanpolicy.h"
#include "enumtask.h"

//����ɨ�� ɨ���ڴ桢������ؼ�Ŀ¼������Ŀ¼
HRESULT CFastScanPolicy::StartScan( CScanContext* pScanContext )
{
    _ASSERT(pScanContext);
    do 
    {  
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( TRUE );
        pScanContext->SetAddRelationDir( TRUE );

        CAutorunEnumTask AutorunEnum;
        AutorunEnum.EnumScanFile( pScanContext, BKATR_SHOW_ONLY_CAN_REPAIR );
        AutorunEnum.EnumScanFile( pScanContext, BKATR_SHOW_ONLY_CAN_NOT_REPAIR );
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        CMemoryEnumTask MemoryScan;
        MemoryScan.EnumScanFile( pScanContext );
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( FALSE );
        pScanContext->SetAddRelationDir( FALSE );
        //
        CCriticalDirEnumTask CriticalDirEnum;
        CriticalDirEnum.EnumScanFile( pScanContext );
        CAllRootDirEnumTask  AllRootDirEnum( FALSE );
        AllRootDirEnum.EnumScanFile( pScanContext );
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        CCustomDirEnumTask RelationDirEnum;
        RelationDirEnum.EnumScanFileForRelationDir( pScanContext, pScanContext->GetRelationDir() );
    }while( false );

    return S_OK;
}

HRESULT CFastScanPolicy::StartScan( CScanContext* pScanContext, CAtlMap<CString, BOOL>& CustomParamMap )
{
    StartScan( pScanContext );

    do 
    {     
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        CCustomDirEnumTask CustomDirEnum;
        CustomDirEnum.EnumScanFileForCusomDir( pScanContext, CustomParamMap, BkScanStepCriticalDir );
    }while( false );

    return S_OK;
}


HRESULT CIeFixScanPolicy::StartScan( CScanContext* pScanContext )
{
    _ASSERT(pScanContext);
    do 
    {       
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( TRUE );
        pScanContext->SetAddRelationDir( FALSE );
        //
        CMemoryEnumTask MemoryScan;
        MemoryScan.EnumScanFileForIeFixPolicy( pScanContext );
    }while( false );

    return S_OK;
}


HRESULT COnlyMemoryScanPolicy::StartScan( CScanContext* pScanContext )
{
    _ASSERT(pScanContext);
    do 
    {       
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( TRUE );
        pScanContext->SetAddRelationDir( FALSE );
        //
        CMemoryEnumTask MemoryScan;
        MemoryScan.EnumScanFile( pScanContext );
    }while( false );

    return S_OK;
}

//���ɨ��
HRESULT CCheckScanPolicy::StartScan( CScanContext* pScanContext )
{
    _ASSERT(pScanContext);

    do 
    {       
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( TRUE );
        pScanContext->SetAddRelationDir( FALSE );
        //
        CMemoryEnumTask MemoryScan;
        MemoryScan.EnumScanFileForCheckPolicy( pScanContext );
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        CAutorunEnumTask AutorunEnum;
        AutorunEnum.EnumScanFile( pScanContext, 0 );
    }while( false );

    return S_OK;
}

//���ɨ��
HRESULT CCheckScanPolicy::StartScanForCacheMemory( CScanContext* pScanContext )
{
    _ASSERT(pScanContext);

    do 
    {       
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( TRUE );
        pScanContext->SetAddRelationDir( FALSE );
        //
        CMemoryEnumTask MemoryScan;
        MemoryScan.EnumScanFileForCheckPolicy( pScanContext );
    }while( false );

    return S_OK;
}

//���ɨ��
HRESULT CCheckScanPolicy::StartScanForCacheAutoRun( CScanContext* pScanContext )
{
    _ASSERT(pScanContext);

    do 
    {       
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( TRUE );
        pScanContext->SetAddRelationDir( FALSE );

        CAutorunEnumTask AutorunEnum;
        AutorunEnum.EnumScanFile( pScanContext, 0 );
    }while( false );

    return S_OK;
}


//�Զ���ɨ�� ɨ���ڴ桢������ؼ�Ŀ¼������Ŀ¼���Զ���Ŀ¼
HRESULT CCustomScanPolicy::StartScan( CScanContext* pScanContext, CAtlMap<CString, BOOL>& CustomDirMap )
{
    _ASSERT(pScanContext);
    do 
    {  
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( TRUE );
        pScanContext->SetAddRelationDir( FALSE );
        //
        CAutorunEnumTask AutorunEnum;
        AutorunEnum.EnumScanFile( pScanContext, BKATR_SHOW_ONLY_CAN_REPAIR );
        AutorunEnum.EnumScanFile( pScanContext, BKATR_SHOW_ONLY_CAN_NOT_REPAIR );
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        CMemoryEnumTask MemoryScan;
        MemoryScan.EnumScanFile( pScanContext );
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( FALSE );
        pScanContext->SetAddRelationDir( FALSE );
        CCustomDirEnumTask CustomDirEnum;
        CustomDirEnum.EnumScanFileForCusomDir( pScanContext, CustomDirMap, BkScanStepCustomDir  );
    }while( false );

    return S_OK;
}



//ȫ��ɨ�� ɨ���ڴ桢������ؼ�Ŀ¼������Ŀ¼�������̷�
HRESULT CFullDiskScanPolicy::StartScan( CScanContext* pScanContext )
{
    _ASSERT(pScanContext);
    do 
    {  
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( TRUE );
        pScanContext->SetAddRelationDir( TRUE );

        //
        //CMemoryEnumTask MemoryScan;
        //MemoryScan.EnumScanFile( pScanContext );
        //if ( pScanContext->IsExitEnumWork() )
        //{
        //    break;   
        //}

        //CAutorunEnumTask AutorunEnum;
        //AutorunEnum.EnumScanFile( pScanContext );
        //if ( pScanContext->IsExitEnumWork() )
        //{
        //    break;
        //}
        ////
        //pScanContext->SetAddCancelDoublePathForFile( FALSE );
        //pScanContext->SetAddRelationDir( FALSE );
        ////

        //CCriticalDirEnumTask CriticalDirEnum;
        //CriticalDirEnum.EnumScanFile( pScanContext );
        //CAllRootDirEnumTask  AllRootDirEnum( FALSE );
        //AllRootDirEnum.EnumScanFile( pScanContext );
        //if ( pScanContext->IsExitEnumWork() )
        //{
        //    break;
        //}

        //CCustomDirEnumTask RelationDirEnum;
        //RelationDirEnum.EnumScanFileForRelationDir( pScanContext, pScanContext->GetRelationDir() );
        //if ( pScanContext->IsExitEnumWork() )
        //{
        //    break;
        //}

        CAllRootDirEnumTask  AllRootDirRecursionEnum( TRUE );
        AllRootDirRecursionEnum.EnumScanFile( pScanContext );
    }while ( false );

    return S_OK;
}


//ɨ���ڴ� ɨ�������� ɨ���ƶ�����
HRESULT CMoveDiskScanPolicy::StartScan( CScanContext* pScanContext )
{
    _ASSERT(pScanContext);
    do 
    {  
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( TRUE );
        pScanContext->SetAddRelationDir(FALSE);

        //
        CAutorunEnumTask AutorunEnum;
        AutorunEnum.EnumScanFile( pScanContext, BKATR_SHOW_ONLY_CAN_REPAIR );
        AutorunEnum.EnumScanFile( pScanContext, BKATR_SHOW_ONLY_CAN_NOT_REPAIR );
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }

        CMemoryEnumTask MemoryScan;
        MemoryScan.EnumScanFile( pScanContext );
        if ( pScanContext->IsExitEnumWork() )
        {
            break;   
        }

        //
        pScanContext->SetAddCancelDoublePathForFile( FALSE );
        //
        CMoveDisEnumTask MoveDiskEnumTask;
        MoveDiskEnumTask.EnumScanFile( pScanContext );
    }while ( FALSE );

    return S_OK;
}


//�Ҽ�ɨ�� ɨ���ڴ���û�ָ��Ŀ¼
HRESULT CRightScanPolicy::StartScan( CScanContext* pScanContext, CAtlMap<CString, BOOL>& RightParamMap )
{
    _ASSERT(pScanContext);
    do 
    {  
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( TRUE );
        pScanContext->SetAddRelationDir(FALSE);
        //
        CMemoryEnumTask MemoryScan;
        MemoryScan.EnumScanFile( pScanContext );
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        //
        pScanContext->SetAddCancelDoublePathForFile( FALSE );
        //
        CCustomDirEnumTask CustomDirEnum;
        CustomDirEnum.EnumScanFileForCusomDir( pScanContext, RightParamMap, BkScanStepCustomDir );
    }while (false);

    return S_OK;
}


HRESULT COnlyCustomScanPolicy::StartScan( CScanContext* pScanContext, CAtlMap<CString, BOOL>& CustomParamMap )
{
    _ASSERT(pScanContext);
    do 
    {     
        if ( pScanContext->IsExitEnumWork() )
        {
            break;
        }
        CCustomDirEnumTask CustomDirEnum;
        CustomDirEnum.EnumScanFileForCusomDir( pScanContext, CustomParamMap, BkScanStepCustomDir );
    }while( false );

    return S_OK;
}



