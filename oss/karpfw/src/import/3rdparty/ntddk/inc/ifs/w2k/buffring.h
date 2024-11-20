/*++ BUILD Version: 0009    // Increment this if a change has global effects
Copyright (c) 1987-1993  Microsoft Corporation

Module Name:

    buffring.h

Abstract:

    This module defines the change buffering state requests related data structures in RDBSS.

Author:

    Balan Sethu Raman (SethuR) 11-Nov-95    Created

Notes:

    The buffering manager implementation consists of two primary data structures
    (1) CHANGE_BUFFERING_STATE_REQUEST and (2) BUFFERING_MANAGER.

    The BUFFERING_MANAGER tracks and initiates actions on all change buffering state
    requests generated by the various mini redirectors as well as the RDBSS.

    There are three lists associated with the buffering manager, i.e., the registration
    list, the dispatcher list and the handler list.

    The registration list contains all the requests initiated for which no processing
    has been done. All DPC level indications merely register the indication in this
    list. The access to this list is protected by a spin lock(RxStrucsupSpinLock).

    The dispatcher list contains all the requests for which the lookup has not been
    completed. This list is organized as a two tier list. The top level is based on
    the NetRootKey. Each entry for a NetRootKey in this list has an associated cluster
    of requests corresponding to the various SrvOpenKey's. This is the reason for
    ghaving two LIST_ENTRY's in the request data structure as well. The
    NetRootListEntry field is used for inter cluster threading and the listEntry
    field is used for intra cluster threading.

    The handler list consists of all the requests for which the lookup has been completed
    and are awaiting processing.

    The dispatcher list and the handler list access is protected by the buffering manager
    mutex.

    The three routines of interest to mini rdr writers are ...

    1) RxIndicateChangeOfBufferingState -- for registering the request.

    2) RxAssociateSrvOpenKey -- for associating a SRV_OPEN instance with the key.


    Note that the key associations are irreverisble and will last the lifetime of the
    associated SRV_OPEN.

    Also note that 0 and 0xffffffff are not valid keys for SRV_OPEN. It has special
    significance for the buffering manager.

--*/

#ifndef __BUFFRING_H__
#define __BUFFRING_H__

#define RX_REQUEST_PREPARED_FOR_HANDLING  (0x10000000)

typedef struct _CHANGE_BUFFERING_STATE_REQUEST_ {
   LIST_ENTRY     ListEntry;

   ULONG          Flags;

   PSRV_CALL      pSrvCall;
   PSRV_OPEN      pSrvOpen;

   PVOID          SrvOpenKey;
   PVOID          pMRxContext;
} CHANGE_BUFFERING_STATE_REQUEST, *PCHANGE_BUFFERING_STATE_REQUEST;

typedef struct _RX_BUFFERING_MANAGER_ {

   BOOLEAN            fDispatcherActive;
   BOOLEAN            fNoWaitHandlerActive;
   BOOLEAN            fLastChanceHandlerActive;
   UCHAR              Pad;

   KSPIN_LOCK         SpinLock;

   // This count is always incremented and never reset. This provides us with
   // a quick mechanism to establish if a buffering state change request has
   // been received for a given srvcall since a point in time.
   LONG               CumulativeNumberOfBufferingChangeRequests;

   LONG               NumberOfUnhandledRequests;
   LONG               NumberOfUndispatchedRequests;
   LONG               NumberOfOutstandingOpens;

   LIST_ENTRY         DispatcherList;
   LIST_ENTRY         HandlerList;
   LIST_ENTRY         LastChanceHandlerList;

   RX_WORK_QUEUE_ITEM DispatcherWorkItem;
   RX_WORK_QUEUE_ITEM HandlerWorkItem;
   RX_WORK_QUEUE_ITEM LastChanceHandlerWorkItem;

   FAST_MUTEX         Mutex;
   LIST_ENTRY         SrvOpenLists[1];
} RX_BUFFERING_MANAGER, *PRX_BUFFERING_MANAGER;

#define RxAcquireBufferingManagerMutex(pBufferingManager)               \
        {                                                               \
           if (!ExTryToAcquireFastMutex(&(pBufferingManager)->Mutex)) {   \
              ExAcquireFastMutex(&(pBufferingManager)->Mutex);            \
           }                                                            \
        }

#define RxReleaseBufferingManagerMutex(pBufferingManager)               \
        ExReleaseFastMutex(&(pBufferingManager)->Mutex)

extern VOID
RxpProcessChangeBufferingStateRequests(
      PSRV_CALL  pSrvCall,
      BOOLEAN    UpdateHandlerState);

extern VOID
RxProcessChangeBufferingStateRequests(
      PSRV_CALL  pSrvCall);

extern VOID
RxProcessFcbChangeBufferingStateRequest(
      PFCB  pFcb);

extern VOID
RxPurgeChangeBufferingStateRequestsForSrvOpen(
      PSRV_OPEN   pSrvOpen);

extern VOID
RxCompleteSrvOpenKeyAssociation(
    IN OUT PSRV_OPEN    pSrvOpen);

extern VOID
RxInitiateSrvOpenKeyAssociation(
   IN OUT PSRV_OPEN pSrvOpen);

extern NTSTATUS
RxInitializeBufferingManager(
   PSRV_CALL pSrvCall);

extern NTSTATUS
RxTearDownBufferingManager(
   PSRV_CALL pSrvCall);

NTSTATUS
RxFlushFcbInSystemCache(
    IN PFCB     Fcb,
    IN BOOLEAN  SynchronizeWithLazyWriter
    );

NTSTATUS
RxPurgeFcbInSystemCache(
    IN PFCB             Fcb,
    IN PLARGE_INTEGER   FileOffset OPTIONAL,
    IN ULONG            Length,
    IN BOOLEAN          UninitializeCacheMaps );


#endif __BUFFRING_H__

