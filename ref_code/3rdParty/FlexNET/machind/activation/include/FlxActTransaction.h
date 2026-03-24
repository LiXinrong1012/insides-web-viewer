/**************************************************************************************************
* NOTICE OF COPYRIGHT AND OWNERSHIP OF SOFTWARE:
*
* Copyright 2009 Flexera Software, Inc. and/or InstallShield Co. Inc.  All Rights Reserved.  
*
* This computer program is the property of Flexera Software, Inc. and InstallShield Co. Inc. of 
* Schaumburg, Illinois, U.S.A.  Any use, copy, publication, distribution, display, modification, 
* or transmission of this computer program in whole or in part in any form or by any means without
* the prior express written permission of Flexera Software, Inc. or InstallShield Co. Inc. is 
* strictly prohibited.
* 
* Except when expressly provided by Flexera Software, Inc. or InstallShield Co. Inc. in writing,
* possession of this computer program shall not be construed to confer any license or rights under 
* any of Flexera Software, Inc.s or InstallShield Co. Inc.s intellectual property rights, whether
* by estoppel, implication, or otherwise.  
* 
* ALL COPIES OF THIS PROGRAM MUST DISPLAY THIS NOTICE OF COPYRIGHT AND OWNERSHIP IN FULL.
**************************************************************************************************/

/*
 * FlxActTransaction.h include file
 *
 * This file declares the objects, functions and other data needed to use the Composite Transaction
 * sub-section of the FNP Activation API, characterised by name prefix "flxActTran".
 *
 * Composite transactions are used to obtain and maintain license rights by exchanging information
 * with a server.
 *
 */

#ifndef FlxActTransaction_h
#define FlxActTransaction_h

#include "FlxActCommon.h"
#include "FlxActError.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
 * API objects. 
 ***************************************************************************************************
 *
 *	FlxActHandle		created by flxActCommonHandleOpen()
 *		|
 *		|-FlxActTransaction
 *			|
 *			|-FlxActTranRequest
 *			|	|
 *			|	|-FlxActTranDictionary
 *			|	|-FlxActTranReqAction
 *			|		|-FlxActTranDictionary
 *			|
 *			|-FlxActTranResponse
 *			| 	|
 *			|	|-FlxActTranDictionary
 *			| 	|-FlxActTranRspAction
 *			|		|-FlxActTranDictionary
 *			|
 *
 * All subordinate objects are automatically destroyed with the FlxActTransaction object.
 *
 * If multiple threads use the same handle the caller is responsible for thread safety, for
 * example by placing a lock around calls that use that handle and superior and subordinate handles.
 */

/***************************************************************************************************
 * API object handles.
 ***************************************************************************************************
 *
 */
	typedef uint32_t	FlxActTransaction;
	typedef uint32_t	FlxActTranRequest;
	typedef uint32_t	FlxActTranResponse;
	typedef uint32_t	FlxActTranReqAction;
	typedef uint32_t	FlxActTranRspAction;
	typedef uint32_t	FlxActTranDictionary;
	typedef uint32_t	FlxActTranServerComms;

/***************************************************************************************************
 * Note on returned pointers. 
 ***************************************************************************************************
 *
 * Many functions return const char* pointers to strings.
 * This removes the need to pass in buffers where the length of the data is unknown.
 * The strings are managed by the API objects and are thread safe; a copy of the string is made
 * and a pointer to the copy is returned.
 * When the transaction object is deleted, all the strings are deleted - invalidating the returned 
 * pointers.
 */

/***************************************************************************************************
 * Result codes. 
 ***************************************************************************************************
 *
 * See also notes under "Error handling" below.
 */

/* 
 * The result code defines the type of error.
 */
typedef uint32_t	FlxActTranResult;

#define	FLX_ACT_TRAN_SUCCESS				0

/* 
 * Errors caused by lack of resources.	
 */ 
#define	FLX_ACT_TRAN_CAT_RESOURCE			(LM_TS_CT_BASE + 100)				/* 51100 */

/* RES: No memory. */
#define	FLX_ACT_TRAN_ERR_NO_MEMORY			(FLX_ACT_TRAN_CAT_RESOURCE + 1)		/* 51101 */

/* 
 * Errors expected only at development time.	
 */ 
#define	FLX_ACT_TRAN_CAT_DEVELOPMENT		(LM_TS_CT_BASE + 200)				/* 51200 */

/* DEV: Invalid handle. */
#define	FLX_ACT_TRAN_ERR_HANDLE				(FLX_ACT_TRAN_CAT_DEVELOPMENT + 1)	/* 51201 */

/* DEV: Invalid Transaction handle. */
#define  FLX_ACT_TRAN_ERR_TRANS_HANDLE      (FLX_ACT_TRAN_CAT_DEVELOPMENT + 2)  /* 51202 */

/* DEV: Invalid Request handle. */
#define  FLX_ACT_TRAN_BAD_REQ_HANDLE        (FLX_ACT_TRAN_CAT_DEVELOPMENT + 3)  /* 51203 */

/* DEV: Bad Comms XML. */
#define  FLX_ACT_TRAN_BAD_COMMS_XML        	(FLX_ACT_TRAN_CAT_DEVELOPMENT + 4)  /* 51204 */

/* DEV: Bad Dictionary XML. */
#define  FLX_ACT_TRAN_BAD_DICT_XML        	(FLX_ACT_TRAN_CAT_DEVELOPMENT + 5)  /* 51205 */

/* DEV: Bad Request XML. */
#define  FLX_ACT_TRAN_BAD_REQ_ACT_XML      	(FLX_ACT_TRAN_CAT_DEVELOPMENT + 6)  /* 51206 */

/* DEV: Unexpected failure; catch-all for errors that can't be better identified. 
        Recommended action is to log the error string (see later). */
#define FLX_ACT_TRAN_UNEXPECTED             (FLX_ACT_TRAN_CAT_DEVELOPMENT + 7)  /* 51207 */

/* DEV: Bad Fulfillment Record XML */
#define  FLX_ACT_TRAN_BAD_FR_XML            (FLX_ACT_TRAN_CAT_DEVELOPMENT + 8)  /* 51208 */



/* 
 * Errors that only occur during response processing.	
 */
#define	FLX_ACT_TRAN_CAT_RSP_PROC			(LM_TS_CT_BASE + 300)				/* 51300 */

/* RSP: XML header invalid/wrong XML namespace. */
#define FLX_ACT_TRAN_ERR_RSP_XML_HEADER		(FLX_ACT_TRAN_CAT_RSP_PROC + 1)		/* 51301 */

/* RSP: Mandatory XML element missing. */
#define FLX_ACT_TRAN_ERR_RSP_XML_MISSING	(FLX_ACT_TRAN_CAT_RSP_PROC + 2)		/* 51302 */

/* RSP: Not a composite response. */
#define FLX_ACT_TRAN_ERR_RSP_NOT_COMPOSITE	(FLX_ACT_TRAN_CAT_RSP_PROC + 3)		/* 51303 */

/* RSP: Response XML version number not supported. */
#define FLX_ACT_TRAN_ERR_RSP_XML_VERSION	(FLX_ACT_TRAN_CAT_RSP_PROC + 4)		/* 51304 */

/* RSP: XML invalid in some other way. */
#define FLX_ACT_TRAN_ERR_RSP_XML_OTHER		(FLX_ACT_TRAN_CAT_RSP_PROC + 5)		/* 51305 */

/* RSP: First (or only) signature invalid. */
#define FLX_ACT_TRAN_ERR_RSP_SIGNATURE_1	(FLX_ACT_TRAN_CAT_RSP_PROC + 6)		/* 51306 */

/* RSP: No stored request for this response. */
#define FLX_ACT_TRAN_ERR_RSP_NO_REQUEST		(FLX_ACT_TRAN_CAT_RSP_PROC + 7)		/* 51307 */

/* RSP: Request generated on a different machine. */
#define FLX_ACT_TRAN_ERR_RSP_NOT_REQUESTER	(FLX_ACT_TRAN_CAT_RSP_PROC + 8)		/* 51308 */

/* RSP: Second or subsequent signature invalid. */
#define FLX_ACT_TRAN_ERR_RSP_SIGNATURE_2	(FLX_ACT_TRAN_CAT_RSP_PROC +9)		/* 51309 */

/* RSP: Invalid or missing response action attribute. */
#define FLX_ACT_TRAN_ERR_RSP_ACTION_INFO	(FLX_ACT_TRAN_CAT_RSP_PROC +10)		/* 51310 */

/* RSP: One or more response actions failed. */
#define FLX_ACT_TRAN_ERR_RSP_ACTION_FAILED	(FLX_ACT_TRAN_CAT_RSP_PROC +11)		/* 51311 */

/* RSP: Response XML signature version number not supported.*/
#define FLX_ACT_TRAN_ERR_RSP_SIG_VERSION	(FLX_ACT_TRAN_CAT_RSP_PROC +12)     /* 51312 */

/* RSP: Response is not an XML document.*/
#define FLX_ACT_TRAN_ERR_RSP_NOT_XML    	(FLX_ACT_TRAN_CAT_RSP_PROC +13)     /* 51313 */

/* 
 * General errors.	
 */
#define FLX_ACT_TRAN_CAT_GENERAL           (LM_TS_CT_BASE + 400)				/* 51400 */

/* GEN: Trusted storage load failed. */
#define FLX_ACT_TRAN_ERR_TS_LOAD           (FLX_ACT_TRAN_CAT_GENERAL + 1)		/* 51401 */

/* GEN: Trusted storage save failed. */
#define FLX_ACT_TRAN_ERR_TS_SAVE           (FLX_ACT_TRAN_CAT_GENERAL + 2)		/* 51402 */

/* GEN: Failed to initialise comms. */
#define FLX_ACT_TRAN_ERR_COMMS_INIT        (FLX_ACT_TRAN_CAT_GENERAL + 3)       /* 51403 */

/* GEN: Failed to send request. */
#define FLX_ACT_TRAN_ERR_COMMS_SEND        (FLX_ACT_TRAN_CAT_GENERAL + 4)       /* 51404 */

/* GEN: Failed to access attribute */
#define FLX_ACT_TRAN_ERR_ATTR_UNAVAILABLE  (FLX_ACT_TRAN_CAT_GENERAL + 5)       /* 51405 */

/* GEN: Fulfillment Record is disabled */
#define FLX_ACT_TRAN_ERR_FR_DISABLED  	   (FLX_ACT_TRAN_CAT_GENERAL + 6)       /* 51406 */

/* GEN: Fulfillment Record is trusted */
#define FLX_ACT_TRAN_ERR_FR_TRUSTED  	   (FLX_ACT_TRAN_CAT_GENERAL + 7)       /* 51407 */

/* GEN: Fulfillment Record is untrusted */
#define FLX_ACT_TRAN_ERR_FR_UNTRUSTED  	   (FLX_ACT_TRAN_CAT_GENERAL + 8)       /* 51408 */

/*
 * Invalid parameters.
 */
#define FLX_ACT_TRAN_CAT_PARAM				(LM_TS_CT_BASE + 500)				/* 51500 */

/* PARAM: Invalid FulfillmentId. */
#define FLX_ACT_TRAN_ERR_FR_NOT_FOUND		(FLX_ACT_TRAN_CAT_PARAM + 1)		/* 51501 */

/* PARAM: Unknown Dictionary Key. */
#define FLX_ACT_TRAN_ERR_UNKNOWN_DICT_KEY   (FLX_ACT_TRAN_CAT_PARAM + 2)      	/* 51502 */

/* PARAM: Invalid Dictionary Index. */
#define FLX_ACT_TRAN_ERR_INVALID_DICT_INDEX (FLX_ACT_TRAN_CAT_PARAM + 3)      	/* 51503 */

/* PARAM: Bad Pointer Parameter */
#define FLX_ACT_TRAN_ERR_RESULT_PTR         (FLX_ACT_TRAN_CAT_PARAM + 4)        /* 51504 */

/* PARAM: Invalid Action Index */
#define FLX_ACT_TRAN_ERR_INVALID_ACTION_INDEX   (FLX_ACT_TRAN_CAT_PARAM + 5)    /* 51505 */

/* PARAM: Invalid Request index. */
#define FLX_ACT_TRAN_ERR_INVALID_REQUEST_INDEX	(FLX_ACT_TRAN_CAT_PARAM + 6)    /* 51506 */

/* PARAM: Request is read only and cannot be changed. */
#define FLX_ACT_TRAN_ERR_REQUEST_READONLY       (FLX_ACT_TRAN_CAT_PARAM + 7)    /* 51507 */

/*
 * The function id identifies the function that was called.
 */
typedef uint32_t FlxActTranFunctionId;

#define flxActTransaction_ID_BASE							60000
#define	flxActTransactionCreateRequest_ID					(flxActTransaction_ID_BASE + 1)	/* 60001 */
#define	flxActTransactionGetRequest_ID                  	(flxActTransaction_ID_BASE + 2)	/* 60002 */
#define	flxActTransactionDeleteRequest_ID               	(flxActTransaction_ID_BASE + 3) /* 60003 */
#define	flxActTranRequestSave_ID                        	(flxActTransaction_ID_BASE + 4) /* 60004 */
#define	flxActTransactionGetStoredRequestCount_ID       	(flxActTransaction_ID_BASE + 5) /* 60005 */
#define	flxActTransactionLoadStoredRequest_ID           	(flxActTransaction_ID_BASE + 6) /* 60006 */
#define	flxActTransactionDeleteStoredRequest_ID         	(flxActTransaction_ID_BASE + 7)	/* 60007 */
#define	flxActTranRequestGetXML_ID                      	(flxActTransaction_ID_BASE + 8) /* 60008 */
#define	flxActTransactionProcessResponse_ID             	(flxActTransaction_ID_BASE + 9) /* 60009 */
#define	flxActTransactionGetResponse_ID                 	(flxActTransaction_ID_BASE +10) /* 60010 */
#define	flxActTransactionGetResponseReport_ID           	(flxActTransaction_ID_BASE +11) /* 60011 */
#define	flxActTranRequestSetAttribute_ID                	(flxActTransaction_ID_BASE +12) /* 60012 */
#define	flxActTranRequestGetAttribute_ID                	(flxActTransaction_ID_BASE +13) /* 60013 */
#define	flxActTranRequestGetFLEXnetDictionary_ID        	(flxActTransaction_ID_BASE +14) /* 60014 */
#define	flxActTranRequestGetVendorDictionary_ID         	(flxActTransaction_ID_BASE +15) /* 60015 */
#define	flxActTranRequestAddAction_ID                   	(flxActTransaction_ID_BASE +16) /* 60016 */
#define	flxActTranRequestGetActionCount_ID              	(flxActTransaction_ID_BASE +17) /* 60017 */
#define	flxActTranRequestGetAction_ID                   	(flxActTransaction_ID_BASE +18) /* 60018 */
#define	flxActTranReqActionGetType_ID                   	(flxActTransaction_ID_BASE +19) /* 60019 */
#define	flxActTranReqActionSetAttribute_ID              	(flxActTransaction_ID_BASE +20) /* 60020 */
#define	flxActTranReqActionGetFLEXnetDictionary_ID      	(flxActTransaction_ID_BASE +21) /* 60021 */
#define	flxActTranReqActionGetVendorDictionary_ID       	(flxActTransaction_ID_BASE +22) /* 60022 */
#define	flxActTranRequestClearExistingFulfillments_ID   	(flxActTransaction_ID_BASE +23) /* 60023 */
#define	flxActTranRequestAddExistingFulfillment_ID			(flxActTransaction_ID_BASE +24) /* 60024 */
#define	flxActTranRequestSetExistingFulfillmentDetails_ID	(flxActTransaction_ID_BASE +25) /* 60025 */
#define	flxActTranResponseGetFLEXnetDictionary_ID       	(flxActTransaction_ID_BASE +26) /* 60026 */
#define	flxActTranResponseGetVendorDictionary_ID        	(flxActTransaction_ID_BASE +27) /* 60027 */
#define	flxActTranResponseGetActionCount_ID             	(flxActTransaction_ID_BASE +28) /* 60028 */
#define	flxActTranResponseGetAction_ID                  	(flxActTransaction_ID_BASE +29) /* 60029 */
#define	flxActTranRspActionGetType_ID                   	(flxActTransaction_ID_BASE +30) /* 60030 */
#define	flxActTranRspActionGetAttribute_ID              	(flxActTransaction_ID_BASE +31) /* 60031 */
#define	flxActTranRspActionGetFLEXnetDictionary_ID      	(flxActTransaction_ID_BASE +32) /* 60032 */
#define	flxActTranRspActionGetVendorDictionary_ID       	(flxActTransaction_ID_BASE +33)	/* 60033 */
#define	flxActTranDictionaryGetByIndex_ID               	(flxActTransaction_ID_BASE +34)	/* 60034 */
#define	flxActTranDictionaryGetByKey_ID                 	(flxActTransaction_ID_BASE +35) /* 60035 */
#define	flxActTranDictionarySetByKey_ID                 	(flxActTransaction_ID_BASE +36) /* 60036 */
#define	flxActTransactionCreateRecoveryRequest_ID       	(flxActTransaction_ID_BASE +37) /* 60037 */
#define	flxActTranRspActionGetResult_ID						(flxActTransaction_ID_BASE +38) /* 60038 */
#define	flxActTransactionSetCommsAttribute_ID				(flxActTransaction_ID_BASE +39) /* 60039 */
#define	flxActTransactionGetCommsAttribute_ID				(flxActTransaction_ID_BASE +40) /* 60040 */
#define	flxActTransactionSend_ID							(flxActTransaction_ID_BASE +41) /* 60041 */
#define	flxActTranReqActionGetAttribute_ID              	(flxActTransaction_ID_BASE +42) /* 60042 */
#define flxActTranDictionaryGetCount_ID						(flxActTransaction_ID_BASE +43) /* 60043 */
#define flxActTranRequestMatchStored_ID						(flxActTransaction_ID_BASE +44) /* 60044 */
#define flxActTransactionDeleteRequestBySeqNo_ID            (flxActTransaction_ID_BASE +45) /* 60045 */

	
/***************************************************************************************************
 * Creating and destroying the composite transaction object. 
 ***************************************************************************************************
 *
 * Create a composite transaction object for use in all other calls.
 * The FlxActHandle must have been obtained from flxActCommonHandleOpen().
 * A handle for the FlxActTransaction object is returned to *phTransaction.
 * This function will succeed provided that the FlxActHandle is valid and memory is available.
 */
FlxActBool flxActTransactionCreate(FlxActHandle			handle,
								   FlxActTransaction*	phTransaction, 
								   FlxActTranResult*	pErr);
/* 
 * Destroy the object returned by flxActTransactionCreate and all its subordinate objects.
 * Invalidates all handles and pointers returned by functions that use the FlxActTransaction 
 * handle and the handles of all attached objects. 
 */
FlxActBool flxActTransactionDestroy(FlxActTransaction hTransaction);

/***************************************************************************************************
 * Error handling. 
 ***************************************************************************************************
 *
 * If a flxActTranXXX function fails it will return FNP_FALSE and set error information:
 *		A FlxActTranResult		defining the error.
 *      A FlxActTranFunctionId	identifying the API function that failed.
 *		An error log string.
 *
 * Error information is held per thread; it is cleared when the next flxActTranXXX function (other 
 * than the error reporting functions in this section) is called.
 */

/* 
 * The result code defines the type of error - see FlxActTranResult.
 */
FlxActTranResult flxActTransactionGetResult(void);

/*
 * The function id identifies the function that was called - see FlxActTranFunctionId.
 */
FlxActTranFunctionId flxActTransactionGetFunctionId(void);

/*
 * Error log string.
 *
 * The log string is a printable diagnostic string that contains the result and function id plus
 * other information (not defined here) about the error that may be useful in support situations.
 * If an unexpected error occurs that may require assistance from FNP support then it should be
 * written to the FNP event file by calling flxActTransactionLogError.
 */
FlxActBool flxActTransactionLogError(void);

/*
 * The string can also be obtained directly (though as it is encoded it can only be interpreted 
 * by FNP support).
 */
const char* flxActTransactionGetLogString(void);

/*
 * For compatibility with older (non-flxActTranXXX) functions, a FlxActError can also be obtained
 * (this is deprecated - use the functions defined above to get result, functionId and log string).
 *		majorErrorNo	The FlxActTranResponseResult.
 *		minorErrorNo	The FlxActTranFunctionId.
 *		sysErrorNo		An item of diagnostic information (not defined here).
 */
FlxActBool flxActTransactionGetError(FlxActError*		pErr);

/*
 * Note that the function flxActCommonGetError() cannot be used for flxActTranXXX functions;
 */ 

/***************************************************************************************************
* Creating a new composite request. 
***************************************************************************************************/
/*
 * This creates a new request object with default attributes and attaches it to the transaction 
 * object, replacing any existing request object and making the current response object null.
 * The reference string supplied with the pReference parameter is used to initialise the 
 * FLX_ACT_TRAN_REQ_REFERENCE attribute. This can be used to identify the request later when 
 * enumerating stored requests, for example "Activate Product A".
 * The request handle is returned as a convenience; it can also be obtained from the transaction 
 * object using flxActTransactionGetRequest.  The handle can be used to set and get request 
 * attributes and actions.
 * The request object is automatically destroyed with the transaction object.
 */
FlxActBool flxActTransactionCreateRequest(FlxActTransaction		hTransaction,
										  const char*			pReference,
										  FlxActTranRequest*	phTranRequest);

/*
 * This returns the request object currently attached to the transaction (the same as that returned 
 * by the most recent call to flxActTransactionCreateRequest, flxActTransactionLoadStoredRequest
 * or flxActTransactionCreateRecoveryRequest. 
 */
FlxActBool flxActTransactionGetRequest(FlxActTransaction	hTransaction,
									   FlxActTranRequest*	phTranRequest);


/* 
 * Request matching:
 * This function checks to see if there is a stored request that matches the current request
 * exactly.  This usually means that the user is regenerating the request for recovery purposes.
 * They could do this by enumerating stored requests and selecting the appropriate one but
 * this function provides the more usable option of simply repeating the request generation with the
 * same actions and attributes.
 * To support this behaviour, call this function immediately before flxActTranRequestSave. If a 
 * match is found use the FLX_ACT_TRAN_REQ_SEQUENCE_NO attribute of hTranRequestMatch to load the
 * matching stored request (see next section).
 * Matching is optional - you can go ahead and save the new request.  Be aware, however, that 
 * you cannot include a return action for a fulfillment record that has already been returned 
 * by a stored request (because the FR was disabled when the earlier request was created).
 */
FlxActBool flxActTranRequestMatchStored(FlxActTranRequest hTranRequest, FlxActTranRequest* hTranRequestMatch);

/* This function saves the request in trusted storage so that it is available when the response 
 * is processed. This makes the request object read-only.
 */
FlxActBool flxActTranRequestSave(FlxActTranRequest	hTranRequest);

/***************************************************************************************************
 * Managing outstanding composite requests. 
 ***************************************************************************************************
 *
 * Composite requests are retained in trusted storage until explicitly deleted.
 * They go through the following life cycle.
 */
typedef uint32_t FlxActTranRequestStatus;

#define FLX_ACT_TRAN_REQ_STATUS_CREATING	 0	/* Created but not yet saved to trusted storage.*/
#define FLX_ACT_TRAN_REQ_STATUS_PENDING		 1	/* Waiting for a response.*/
#define FLX_ACT_TRAN_REQ_STATUS_UNTRUSTED	 2	/* Trusted storage break since request stored.*/
#define FLX_ACT_TRAN_REQ_STATUS_COMPLETE	 3	/* Response processed successfully.*/
#define FLX_ACT_TRAN_REQ_STATUS_RECOVER		 4	/* The response has been processed but there were errors. */

/*
 * You do not need to enumerate stored requests when processing a response as the correct request
 * will be loaded automatically by the transaction object and set as the current request.
 * 
 * Enumeration is provided so that users can be prompted for outstanding responses and for 
 * recovery from error conditions where the requests needs to be re-sent to the server.
 *
 * Enumerate the stored requests by getting the count then loading each in turn by index 
 * (0 to (count-1)).
 * When a request is loaded it becomes the current request for the transaction, replacing any
 * existing request. The request handle is returned as a convenience, it can always be obtained 
 * from the transaction object using flxActTransactionGetRequest.  The request can then be
 * identified from its attributes (flxActTranRequestGetAttribute).
 * If the response has already been processed (status COMPLETE or RECOVER) it will
 * become the current response.  The response handle (from flxActTransactionGetResponse) 
 * can be used to get attributes, for example vendor dictionary entries.
 */
FlxActBool flxActTransactionGetStoredRequestCount(FlxActTransaction hTransaction,
												  uint32_t*			pCount);

FlxActBool flxActTransactionLoadStoredRequest(FlxActTransaction		hTransaction,
											  uint32_t				index,
											  FlxActTranRequest*	phTranRequest);

/*
 * Note on the use of index and count when enumerating requests.
 * Requests are stored in a vector in request sequence number order; 
 * the lowest numbered has index = 0, the highest has index = (count -1). 
 * When a request is created it is given the next available sequence number, appended to the 
 * vector and the count increased by 1.  Sequence numbers are allocated from a single pool shared 
 * with single action and short code requests so may not be consecutive for composite requests. 
 * When a request is deleted the count is decreased by 1 and higher indexed entries are moved down
 * (their index decreases by 1).
 * So, when using a for loop to enumerate requests you should decrement the count if you 
 * delete a request or increment the index if you don't.
 */


/*
 * Requests with status PENDING should normally be retained until the response is received;
 * if necessary they can be resent to the server using flxActTransactionSend or 
 * flxActTranRequestGetXML.  However, if there is no prospect of a response they should be deleted
 * using flxActTransactionDeleteStoredRequest.
 *
 * Requests with status UNTRUSTED should also be retained until the response is received;
 * after processing the status will become RECOVER. Again, if there is no prospect of a response 
 * they should be deleted.
 *
 * For requests with status RECOVER see flxActTransactionCreateRecoveryRequest.
 *
 * Requests with status COMPLETE should be deleted using flxActTransactionDeleteStoredRequest
 * once any response vendor data has been processed.
 */ 
FlxActBool flxActTranRequestGetStatus(FlxActTranRequest			hTranRequest,
									  FlxActTranRequestStatus*	pStatus);

/* 
 * Deleting stored requests.
 * The current request can be deleted using flxActTransactionDeleteStoredRequest
 * (flxActTransactionLoadStoredRequest makes the request it loads current).
 *
 * The following function can be used to delete any stored request using its sequence number
 * attribute FLX_ACT_TRAN_REQ_SEQUENCE_NO; this is useful in situations where you don't want 
 * to change the current request, for example when deleting the original request after creating 
 * a recovery request.
 */
FlxActBool flxActTransactionDeleteStoredRequestBySeqNo(FlxActTransaction hTransaction, const char* seqNo);

/***************************************************************************************************
 * Recovery.
 ***************************************************************************************************
 *
 * This function is used when response processing has failed and the server needs to know. For
 * example, the server may have granted rights in the response which have not been successfully
 * transferred to the requesting machine (because response processing failed).  Recovery allows
 * the server to reclaim the rights or re-send them in a new response.
 *
 * It should be called when the status of the current request is FLX_ACT_TRAN_REQ_STATUS_RECOVER.
 * It clones the current request and adds recovery information from the processing report of the
 * response.  This new request becomes the current request; it should be checked for a match, saved
 * and sent to the server in the normal way (flxActTransactionSend or flxActTranRequestGetXML).
 */
FlxActBool flxActTransactionCreateRecoveryRequest(FlxActTransaction		hTransaction,
												  FlxActTranRequest*	phTranRequest);

/***************************************************************************************************
 * Setting up the server communications attributes. 
 ***************************************************************************************************
 *
 * These must be set before calling flxActTransactionSend.  
 * You must set the server address attribute FLX_ACT_TRAN_SVR_URI.
 * Other attributes are optional or defaulted.
 */

typedef enum flxActTranServerCommsTypeEnum
{
	FLX_ACT_TRAN_SVR_COMMS_TYPE		= 1,	/* Default "SOAP" (defined below)	*/
	FLX_ACT_TRAN_SVR_URI			= 10,	/* Mandatory						*/
	FLX_ACT_TRAN_SVR_PROXY_HOST		= 21,	/* Optional							*/
	FLX_ACT_TRAN_SVR_PROXY_PORT		= 22,	/* Optional							*/
	FLX_ACT_TRAN_SVR_PROXY_USER		= 23,	/* Optional							*/
	FLX_ACT_TRAN_SVR_PROXY_PASSWORD	= 24,	/* Optional							*/
	FLX_ACT_TRAN_SVR_SSL_CACERT		= 30,	/* Optional							*/
	FLX_ACT_TRAN_SVR_SSL_CAPATH		= 31,	/* Optional							*/
	FLX_ACT_TRAN_SVR_TIMEOUT		= 40,	/* Default 10 secs					*/
	FLX_ACT_TRAN_SVR_POLL_INTERVAL	= 41,	/* Default 1 sec					*/

} FlxActTranServerCommsType;

/* Only SOAP is supported. */
#define FLX_ACT_TRAN_SVR_COMMS_TYPE_SOAP	"SOAP"

/*
 * Set/get attributes.
 */
FlxActBool flxActTransactionSetCommsAttribute(FlxActTransaction			hTransaction,
											  FlxActTranServerCommsType	attributeType,
											  const char*				pAttributeValue);

FlxActBool flxActTransactionGetCommsAttribute(FlxActTransaction			hTransaction,
											  FlxActTranServerCommsType	attributeType,
											  const char**				ppAttributeValue);

/***************************************************************************************************
 * Sending the request to the server. 
 ***************************************************************************************************
 *
 * This function performs the entire transaction by
 * 1. Getting the request XML using flxActTranRequestGetXML().
 * 2. Sending it to the server and obtaining the response.
 * 3. Calling flxActTransactionProcessResponse() - see notes for that function for error handling
 *    and how to proceed next.
 *
 * You must set the server communications attributes first (previous section).
 * The callback function is called with status information as the transaction proceeds; its return
 * value determines whether the transaction should proceed or be canceled (see flxCommsStatusCodes 
 * and flxActCallbackReturn in flxActCommon.h).
 */
typedef uint32_t(*FlxActTranStatusCallback)(const void* pCallerData, 
											uint32_t	statusOld, 
											uint32_t	statusNew);

FlxActBool flxActTransactionSend(FlxActTransaction			hTransaction,
								 FlxActTranStatusCallback 	pfnStatus,
                                 const void* 				pCallerData);

/*
 * Alternatively you can manage the server communications yourself by using this function to get
 * the request XML; if the request has not already been saved, flxActTranRequestSave() will
 * be called automatically.
 * Send the XML to the server, when the response is received call flxActTransactionProcessResponse()  
 */
FlxActBool flxActTranRequestGetXML(FlxActTranRequest	hTranRequest,
								   const char**			ppRequestXML);


/***************************************************************************************************
 * Processing a response. 
 ***************************************************************************************************
 *
 * This function processes a composite response received from the server.
 *	 1.	The response XML is validated for:
 *		 o	Correct XML header format and namespace.
 *		 o	Root element is <Response>
 *		 o	Mandatory elements are present
 *		 o	Element <ResponseType> has value COMPOSITE.
 *		 o	XML version is correct
 *	 2.	The first signature is validated (if no trusted sections currently exist in trusted storage
 *	    this will be the common signature, otherwise the first or only section signature).
 *	 3.	Requester verification is performed, if specified by the server.  This confirms that the 
 *	    response is being processed on the machine that generated the request. 
 *	 4.	The corresponding request is loaded from trusted storage (if it is not already the current
 *		request); its status must be PENDING.
 *	 5. A response object is created, attached to the transaction object (replacing any existing one)
 *		and stored with the request in trusted storage.
 *	 6.	Any Config actions are performed, creating (or modifying the trusted configuration of) the 
 *	    trusted sections needed to validate other signatures and perform other actions.  
 *	 7.	Any other signatures are validated.
 *	 8.	The remaining actions are performed, in the following order.
 *			Repair
 *			Delete
 *			Create
 *			Modify 
 *			Deny
 *	 9.	If all actions succeed, the changes are committed to trusted storage; otherwise all 
 *	    changes are discarded.  This means that either all actions succeed or none. Config
 *		actions are an exception; any trusted sections that have been created will not be deleted.
 *
 * If all steps are successful the function will return FNP_ACT_TRUE and the current response object
 * will have been set.  As well as details of the actions that have been performed during 
 * processing, the response object contains any vendor defined data sent by the server in the vendor
 * dictionaries; this should be read and actioned now.
 *
 * If the function returns FNP_ACT_FALSE, call flxActTransactionGetResult to get error information.  
 * Depending on the type of error, a response object may still have been created; you can call 
 * flxActTransactionGetResponse to find this out.
 *
 * If the request status is now FLX_ACT_TRAN_REQ_ACTION_RECOVERY a recovery transaction should 
 * be performed - see flxActTransactionCreateRecoveryRequest.
 *
 * Note that successful processing does not guarantee that all the actions requested have been 
 * granted by the server; if not, the server should have included "deny" response actions. You
 * can check for this by enumerating the response actions.
 *
 * All objects created by this function are automatically destroyed with the transaction object.
 */
FlxActBool flxActTransactionProcessResponse(FlxActTransaction	hTransaction,
											const char*			pResponseXml);

/*
 * This returns the response object currently attached to the transaction by the most recent
 * flxActTransactionProcessResponse or flxActTransactionLoadStoredRequest call.
 * It can be used to get response properties such as vendor dictionary entries.
 */
FlxActBool flxActTransactionGetResponse(FlxActTransaction	hTransaction,
									    FlxActTranResponse*	phTranResponse);
/*
 * The response object is stored with the request in trusted storage; when you have finished 
 * with them you must delete them explicitly by calling flxActTransactionDeleteStoredRequest.
 * If this call is not make, for example if there is a crash, the request and response can be
 * loaded in a subsequent session to complete the processing of vendor data. This is
 * why they are not deleted implicitly by flxActTransactionProcessResponse.
 */
FlxActBool flxActTransactionDeleteStoredRequest(FlxActTransaction	hTransaction);

/***************************************************************************************************
 * Request attributes and dictionaries. 
 ***************************************************************************************************
 *
 * These are the request attributes.
 */
typedef enum flxActTranReqAttributeTypeEnum
{
	/* These can be set until the request is saved; they can be got at any time. */
	FLX_ACT_TRAN_REQ_REFERENCE		= 1,

	/* These can be got after the request has been saved; they cannot be set. */
	FLX_ACT_TRAN_REQ_SEQUENCE_NO	= 2,
	FLX_ACT_TRAN_REQ_TIME_GENERATED	= 3,

} FlxActTranReqAttributeType;

/*
 * Set/get attributes.
 */
FlxActBool flxActTranRequestSetAttribute(FlxActTranRequest			hTranRequest,
										 FlxActTranReqAttributeType	attributeType,
										 const char*				pAttributeValue);

FlxActBool flxActTranRequestGetAttribute(FlxActTranRequest			hTranRequest,
										 FlxActTranReqAttributeType	attributeType,
										 const char**				ppAttributeValue);
/*
 * Request FLEXnet dictionary; for items defined by FLEXnet products.
 * Read/write until the request is saved, then read only.
 * An empty dictionary is created when this function is called for the first time;
 * entries are added using flxActTranDictionarySetByKey.
 */
FlxActBool flxActTranRequestGetFLEXnetDictionary(FlxActTranRequest		hTranRequest,
												 FlxActTranDictionary*	phDictionary);
/*
 * Request vendor dictionary; for items defined by the publisher.  
 * Read/write until the request is saved, then read only.
 * An empty dictionary is created when this function is called for the first time;
 * entries are added using flxActTranDictionarySetByKey.
 */
FlxActBool flxActTranRequestGetVendorDictionary(FlxActTranRequest		hTranRequest,
												FlxActTranDictionary*	phDictionary);

/***************************************************************************************************
 * Request actions. 
 ***************************************************************************************************
 *
 * These are the request action types.
 */
typedef enum flxActTranReqActionTypeEnum
{
	FLX_ACT_TRAN_REQ_ACTION_ACTIVATE	= 1,
	FLX_ACT_TRAN_REQ_ACTION_RETURN		= 2,
	FLX_ACT_TRAN_REQ_ACTION_REPAIR		= 3,

} FlxActTranReqActionType;

/*
 * A request may contain zero or more actions. Actions may be added to a request object until it is 
 * saved.  The action object handle returned must be used to set the action properties.
 */
FlxActBool flxActTranRequestAddAction(FlxActTranRequest			hTranRequest,
									  FlxActTranReqActionType	actionType,
									  FlxActTranReqAction*		phAction);
/*
 * Enumerate the actions in a request.
 * Actions are held in a vector in the order they were added; the first has index = 0, the last 
 * has index = (count -1). 
 * The handle returned can be used to set and get the action's attributes.
 */
FlxActBool flxActTranRequestGetActionCount(FlxActTranRequest	hTranRequest,
										   uint32_t*			pCount);

FlxActBool flxActTranRequestGetAction(FlxActTranRequest		hTranRequest,
									  uint32_t				index,	/* 0 to (count - 1) */
									  FlxActTranReqAction*	phTranReqAction);

/***************************************************************************************************
 * Request action attributes and dictionaries. 
 ***************************************************************************************************
 *
 * These are the attributes for individual request actions.
 * Not all attributes are valid for all actions.
 * Attributes cannot be set once the request has been saved.
 */
typedef enum flxActTranReqActAttributeTypeEnum
{
	FLX_ACT_TRAN_REQ_ACT_RIGHTS_ID_TYPE			=  1,	/* Activate; optional, default "0".			*/
	FLX_ACT_TRAN_REQ_ACT_RIGHTS_ID_VALUE		=  2,	/* Activate; mandatory.						*/
	FLX_ACT_TRAN_REQ_ACT_FULFILLMENT_ID			=  3,	/* Activate; optional, default omitted.		*/
														/* Return, repair; mandatory, see note below*/
	FLX_ACT_TRAN_REQ_ACT_REASON					=  4,	/* Activate, return; optional, default "0"	*/
	FLX_ACT_TRAN_REQ_ACT_COUNT					=  5,	/* Activate, return; optional, default "all"*/

	FLX_ACT_TRAN_REQ_ACT_EXPIRATION_TYPE		=  6,	/* Activate; optional, default ""			*/
	FLX_ACT_TRAN_REQ_ACT_EXPIRATION_VALUE		=  7,	/* Activate; optional, default ""			*/

	FLX_ACT_TRAN_REQ_ACT_COUNT_ACTIVATABLE			=  8,	/* Activate, return; optional, default ""   */
	FLX_ACT_TRAN_REQ_ACT_COUNT_ACTIVATABLE_OD		=  9,	/* Activate, return; optional, default ""   */
	FLX_ACT_TRAN_REQ_ACT_COUNT_HYBRID			= 10,	/* Activate, return; optional, default ""   */
	FLX_ACT_TRAN_REQ_ACT_COUNT_HYBRID_OD		= 11,	/* Activate, return; optional, default ""   */
	FLX_ACT_TRAN_REQ_ACT_COUNT_CONCURRENT		= 12,	/* Activate, return; optional, default ""   */
	FLX_ACT_TRAN_REQ_ACT_COUNT_CONCURRENT_OD	= 13,	/* Activate, return; optional, default ""   */
	FLX_ACT_TRAN_REQ_ACT_COUNT_REPAIR			= 14	/* Activate, return; optional, default ""   */

} FlxActTranReqActAttributeType;

/* 
 * Note on the fulfillment id attribute.
 * A fulfillment with that id must exist in trusted storage.
 * For activate and return actions it must be fully trusted.
 * For repair actions it must not be fully trusted.
 * For return actions it must not be disabled; however, this check is deferred until the request is
 * saved to allow the return request to be matched against an existing return request.
 *
 * These checks are repeated when the request is saved, as it is possible that the state of a
 * fulfillment has been changed by another process.
 */

/*
 * Get the request action type.
 */
FlxActBool flxActTranReqActionGetType(FlxActTranReqAction		hTranReqAction,
									  FlxActTranReqActionType*	pActionType);
/*
 * Set/get request action attributes.
 */
FlxActBool flxActTranReqActionSetAttribute(FlxActTranReqAction				hTranReqAction,
										   FlxActTranReqActAttributeType	attributeType,
										   const char*						pAttributeValue);

FlxActBool flxActTranReqActionGetAttribute(FlxActTranReqAction				hTranReqAction,
										   FlxActTranReqActAttributeType	attributeType,
										   const char**						ppAttributeValue);
/*
 * Request action FLEXnet dictionary; for items defined by FLEXnet products for this action.
 * Read/write until the request is saved, then read only.
 * An empty dictionary is created when this function is called for the first time;
 * entries are added using flxActTranDictionarySetByKey.
 */
FlxActBool flxActTranReqActionGetFLEXnetDictionary(FlxActTranReqAction		hTranReqAction,
												   FlxActTranDictionary*	phDictionary);
/*
 * Request action vendor dictionary; for items defined by the publisher for this action.  
 * Read/write until the request is saved, then read only.
 * An empty dictionary is created when this function is called for the first time;
 * entries are added using flxActTranDictionarySetByKey.
 */
FlxActBool flxActTranReqActionGetVendorDictionary(FlxActTranReqAction	hTranReqAction,
												  FlxActTranDictionary*	phDictionary);


/***************************************************************************************************
 * Request - existing fulfillments. 
 ***************************************************************************************************
 * The request can contain details of the fulfillment records that are currently in trusted storage.
 * By default summary details of all fulfillments are included (FulfillmentId, FulfillmentType, 
 * IsTrusted, IsEnabled, TrustedId).  Full details can be sent - this is intended for use in
 * diagnostic or support situations as it may make the request very large.
 */

/*
 * Clear all existing fulfillments from the request.
 */
FlxActBool flxActTranRequestClearExistingFulfillments(FlxActTranRequest hTranRequest);
/*
 * Add a specific fulfillment to the request.
 */
FlxActBool flxActTranRequestAddExistingFulfillment(FlxActTranRequest hTranRequest,
												   const char*		 pFulfillmentId,
												   FlxActBool		 bFullDetails);

/*
 * Add or remove full details of each fulfillment currently in the request.
 */
FlxActBool flxActTranRequestSetExistingFulfillmentDetails(FlxActTranRequest hTranRequest,
														  FlxActBool		bFullDetails);

/***************************************************************************************************
 * Response dictionaries. 
 ***************************************************************************************************
 *
 * FLEXnet dictionary - for items defined by FLEXnet products. Read only.
 */
FlxActBool flxActTranResponseGetFLEXnetDictionary(FlxActTranResponse	hTranResponse,
												  FlxActTranDictionary*	phDictionary);
/*
 * Vendor dictionary - for items defined by the publisher. Read only. 
 */
FlxActBool flxActTranResponseGetVendorDictionary(FlxActTranResponse		hTranResponse,
												 FlxActTranDictionary*	phDictionary);

/***************************************************************************************************
 * Response actions. 
 ***************************************************************************************************
 *
 * These are the response action types.
 */
typedef enum flxActTranRspActionTypeEnum
{
	FLX_ACT_TRAN_RSP_ACTION_CONFIG			= 1,
	FLX_ACT_TRAN_RSP_ACTION_CREATE			= 2,
	FLX_ACT_TRAN_RSP_ACTION_DELETE			= 3,
	FLX_ACT_TRAN_RSP_ACTION_MODIFY			= 4,
	FLX_ACT_TRAN_RSP_ACTION_REPAIR			= 5,
	FLX_ACT_TRAN_RSP_ACTION_ACTIVATE_DENY	= 6,
	FLX_ACT_TRAN_RSP_ACTION_RETURN_DENY		= 7,
	FLX_ACT_TRAN_RSP_ACTION_REPAIR_DENY		= 8,

} FlxActTranRspActionType;

/*
 * Enumerate the actions in a response.
 * Actions are held in a vector in the order they were processed; the first has index = 0, the last
 * has index = (count -1). 
 * The handle returned can be used to obtain the action's type and attributes.
 */
FlxActBool flxActTranResponseGetActionCount(FlxActTranResponse	hTranResponse,
											uint32_t*			pCount);

FlxActBool flxActTranResponseGetAction(FlxActTranResponse	hTranResponse,
									   uint32_t				index,	/* 0 to (count - 1) */
									   FlxActTranRspAction*	phTranRspAction);

/***************************************************************************************************
 * Response action attributes and dictionaries. 
 ***************************************************************************************************
 *
 * These are the attributes for individual response actions.
 * Not all attributes are valid for all actions.
 */
typedef enum flxActTranRspActAttributeTypeEnum
{
	FLX_ACT_TRAN_RSP_ACT_FULFILLMENT_ID		=  1,	/* Create, Delete, Modify, ReturnDeny, RepairDeny */
	FLX_ACT_TRAN_RSP_ACT_TRUSTED_ID			=  2,	/* All but ActivateDeny */
	FLX_ACT_TRAN_RSP_ACT_REASON				=  3,	/* All the Deny actions */
	FLX_ACT_TRAN_RSP_ACT_COMMENT			=  4,	/* All the Deny actions */
	FLX_ACT_TRAN_RSP_ACT_RIGHTS_ID_TYPE		=  5,	/* ActivateDeny */
	FLX_ACT_TRAN_RSP_ACT_RIGHTS_ID_VALUE	=  6,	/* ActivateDeny */

} FlxActTranRspActAttributeType;

/*
 * Get the response action type.
 */
FlxActBool flxActTranRspActionGetType(FlxActTranRspAction		hTranRspAction,
									  FlxActTranRspActionType*	pActionType);
/*
 * Get response action attributes.
 */
FlxActBool flxActTranRspActionGetAttribute(FlxActTranRspAction				hTranRspAction,
										   FlxActTranRspActAttributeType	attributeType,
										   const char**						ppAttributeValue);

/*
 * Response action FLEXnet dictionary; for items defined by FLEXnet products for this action. Read only.
 */
FlxActBool flxActTranRspActionGetFLEXnetDictionary(FlxActTranRspAction		hTranRspAction,
												   FlxActTranDictionary*	phDictionary);
/*
 * Response action vendor dictionary; for items defined by the publisher for this action. Read only. 
 */
FlxActBool flxActTranRspActionGetVendorDictionary(FlxActTranRspAction	hTranRspAction,
												  FlxActTranDictionary*	phDictionary);

/*
 * This returns the result of performing the action during response processing.
 */
typedef uint32_t FlxActTranRspActionResult;

#define	FLX_ACT_TRAN_RSP_ACT_SUCCESS       600 	/* Action performed successfully 
                                                   (processing XXXXX result is FLX_ACT_TRAN_RSP_ERR_NONE). */
#define	FLX_ACT_TRAN_RSP_ACT_WARN_DENY     601 	/* This is a deny action.						*/
#define	FLX_ACT_TRAN_RSP_ACT_ERR_NA        602 	/* Not attempted because of another error.		*/
#define	FLX_ACT_TRAN_RSP_ACT_ERR_SKIP      603 	/* Valid but not performed because of another error.*/
#define	FLX_ACT_TRAN_RSP_ACT_ERR_FR_EXISTS 604	/* Fulfillment record already exists.			*/
#define	FLX_ACT_TRAN_RSP_ACT_ERR_NO_FR	   605	/* Fulfillment record does not exist.			*/
#define	FLX_ACT_TRAN_RSP_ACT_ERR_CONFIG	   606	/* Unable to import trusted config.		  		*/

FlxActBool flxActTranRspActionGetResult(FlxActTranRspAction			hTranRspAction,
										FlxActTranRspActionResult*	pActionResult);

/***************************************************************************************************
 * Dictionary access. 
 ***************************************************************************************************
 *
 * Each dictionary entry has a key and a value.
 * They can be got by key or by index (0 = first, 1 = second, ... , (count-1) = last).
 */
FlxActBool flxActTranDictionaryGetCount(FlxActTranDictionary	hDictionary,
										uint32_t*				pCount);

FlxActBool flxActTranDictionaryGetByIndex(FlxActTranDictionary	hDictionary,
										  uint32_t				index,
										  const char**			ppKey,
										  const char**			ppValue);

FlxActBool flxActTranDictionaryGetByKey(FlxActTranDictionary	hDictionary,
										const char*				pKey,
										const char**			ppValue);
/*
 * They can only be set by key; if an entry with the same key exists its value is overwritten,
 * otherwise a new entry is created at the end of the dictionary.
 */
FlxActBool flxActTranDictionarySetByKey(FlxActTranDictionary	hDictionary,
										const char*				pKey,
										const char*				pValue);

#ifdef __cplusplus
}
#endif

#endif	/* Include guard */



