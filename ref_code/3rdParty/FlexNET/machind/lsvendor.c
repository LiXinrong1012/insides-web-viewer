/******************************************************************************

	    Copyright (c) 1988-2009 Flexera Software, Inc. All Rights Reserved.
	This software has been provided pursuant to a License Agreement
	containing restrictions on its use.  This software contains
	valuable trade secrets and proprietary information of
	Flexera Software, Inc. and is protected by law.  It may
	not be copied or distributed in any form or medium, disclosed
	to third parties, reverse engineered or used in any manner not
	provided for in said License Agreement except with the prior
	written authorization from Flexera Software, Inc.

 *****************************************************************************/
/*

 *
 *	Function:  None
 *
 *	Description: Vendor customization data for server.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef PC
#include <shlobj.h>
#endif
#include "lm_code.h"
#include "lmclient.h"
#include "lm_attr.h"

#ifdef PC
typedef int (WINAPI* L_SHCREATEDIRECTORYEX)( HWND hwnd,
    LPCTSTR pszPath,
    const SECURITY_ATTRIBUTES *psa
 );
#endif

#define CURR_FLEX_DIR "FNP\\FLEXlm"
#define PREV_FLEX_DIR "Macrovision\\FLEXlm"
/*
 *	Prototypes for persistent borrow/linger
 */
static void sBorrowInit(char **	ppBuffer, int *	piSize);
static void sBorrowOut(char * szBorrowData,	int	iSize);
static void sBorrowIn(char * szBorrowData, int iSize);
static int sGetBorrowInfo(char *szBorrowFilename, char **	ppBuffer, int *	piSize);

static void sTriggerReplication();

extern LM_HANDLE* lm_job;

/* Vendor encryption routine */

char *(*ls_user_crypt)() = 0;

/* Vendor initialization routines */

/* Initalize any vendor specific attributes by calling lc_set_attr_vendor() 
 * from this routine or lc_set_attr(). Internally this callback is called after the 
 * vendor daemon is initalized but before any license files are read. */
void (*ls_user_init_attributes)() = 0; 
/* the user_init0() callback should be used to setup for common 
 * vendor daemon usage. Internally this callback is called at the start of the 
 * vendor daemon intialization before lm_job is initalized. */
void (*ls_user_init0)() = 0;
void (*ls_user_init1)() = 0;
void (*ls_user_init2)() = 0;
void (*ls_user_init3)() = 0;

/* Checkout, checkin filters, checkin callback */

int (*ls_outfilter)() = 0;
int (*ls_infilter)() = 0;
int (*ls_incallback)() = 0;

/* vendor message, challenge */
char *(*ls_vendor_msg)() = 0;
char *(*ls_vendor_challenge)() = 0;

/* callback for client shutdown p8031 */
void (*ls_user_down) () = 0;

VENDORCODE vendorkeys[] = {		/* Possible keys for vendor daemons */
		{ VENDORCODE_7,
		ENCRYPTION_SEED1^VENDOR_KEY5, ENCRYPTION_SEED2^VENDOR_KEY5,
		  VENDOR_KEY1, VENDOR_KEY2, VENDOR_KEY3, VENDOR_KEY4,
		  FLEXLM_VERSION, FLEXLM_REVISION, FLEXLM_PATCH,
		  LM_BEHAVIOR_CURRENT, {TRL_KEY1, TRL_KEY2}, 0,
		  LM_STRENGTH, LM_SIGN_LEVEL
		},
		    	   };	/* End of vendor codes*/

int keysize = sizeof(vendorkeys)/sizeof(vendorkeys[0]);

int ls_crypt_case_sensitive = 0; /* Is license key case-sensitive? -
					Only used for vendor-supplied
					encryption routines. */
/*
 *      ls_user_lockfile:  We no longer recommend changing this
 *          here, since the text string for the lockfile will
 *          be visible in the binary, and could be therefore
 *          changed.
 */

char *ls_user_lockfile = (char *)NULL;
int ls_read_wait = 10;		/* How long to wait for solicited reads */
int ls_dump_send_data = 0;	/* Set to non-zero value for debug output */
int ls_normal_hostid = 1;	/* <> 0 -> normal hostid call, 0 -> extended */
int ls_conn_timeout = MASTER_WAIT;  /* How long to wait for a connection */
int ls_enforce_startdate = 1;	/* Enforce start date in features */
int ls_tell_startdate = 1;	/* Tell the user if it is earlier than start
								date */
int ls_minimum_user_timeout = 900; /* Minimum user inactivity timeout (seconds)
					<= 0 -> activity timeout disabled */
int ls_min_lmremove = 120;	/* Minimum amount of time (seconds) that a
				   client must be connected to the daemon before
				   an "lmremove" command will work. */
int ls_use_featset = 0;		/* Use the FEATURESET line from the license
									file */
char *ls_dup_sel = LM_NO_COUNT_DUP_STRING;  /* Duplicate selection criteria
						to emulate count_duplicates for
						pre-v2 clients */
int ls_use_all_feature_lines = 0; /* Use ALL copies of feature lines that are
				     unique if non-zero (ADDITIVE licenses) */
int ls_do_checkroot = 0;	/* Perform check that we are running on the
				   real root of filesystem.  NOTE: this check
				   will fail on diskless systems, but they
				   shouldn't be used as server nodes, anyway */
int ls_show_vendor_def = 0;	/* If non-zero, the vendor daemon will send
				   the vendor-defined checkout data back in
				   lm_userlist() calls */
int ls_allow_borrow = 0;	/* Allow "Borrowing" of licenses by another
				   server */


/* Hostid redirection verification routine */

int (*ls_hostid_redirect_verify)() = 0;
				/* Hostid Redirection verification */

/* Vendor-defined periodic call */

void (*ls_daemon_periodic)() = 0;
				/* Vendor-defined periodic call in daemon */
void (*ls_child_exited)() = 0;
				/* Vendor-defined callback -- called with
				   CLIENT_DATA * argument */

int ls_compare_vendor_on_increment = 0;	/* Compare vendor-defined fields to
					 declare matches for INCREMENT lines? */
int ls_compare_vendor_on_upgrade = 0;	/* Compare vendor-defined fields to
					   declare matches for UPGRADE lines? */
/*
 *	ls_a_behavior_ver can also be set in lm_code.h.
 *	lm_code.h takes priority.  If set there, the value here
 *	will not be used.
 */
char *ls_a_behavior_ver = 0;	/* like LM_A_BEHAVIOR_VER */

int ls_a_check_baddate = 0;		/* like LM_A_CHECK_BADDATE */
int ls_a_lkey_start_date = 0;		/* like LM_A_KEY_START_DATE */
int ls_a_lkey_long = 0;			/* like LM_A_KEY_LONG */
int ls_a_license_case_sensitive = 0;	/* like LM_A_LICENSE_CASE_SENSITIVE */

int ls_hud_hostid_case_sensitive = 0; 	/* Forces hostid checks for hostname,     */
					/* user, or display to be case sensitive. */

void (*ls_a_user_crypt_filter)() = 0;
void (*ls_a_phase2_app)() = 0;
#define TWELVE_HOURS (12 * 60 * 60)
int ls_user_based_reread_delay =
			TWELVE_HOURS;	/* Affects USER_BASED and HOST_BASED:
					 * a reread changes the  INCLUDE
					 * after this many hours.  Default
					 * is 12 hours.  Value is in seconds.
					 * -1 means that the INCLUDE list
					 * for these features cannot be changed
					 * via lmreread.
					 */


/* callback routine for semaphore name change 
 * use lc_set_attr_vendor(  LM_A_USER_LOCK_CALLBACK ) to set this for 
 * a vendor other than the primary vendor*/
char *(*ls_user_lock)() = NULL;         

int ls_borrow_return_early = 0;	/* Set to 1 to allow users to return borrowed licenses early */
/*
 *	Forces vendor daemon to send oldest license if a client's version doesn't match a supported signature
 */
int ls_send_oldest_signature = 0;

/*
 *  Allows access to trusted storage.
 */
int ls_use_trusted_storage = 1;

int ls_allow_physical_ethernetid_only = 0; /* Set to 1 to Authenticate only physical adapter hostid  - */

/*
 * Virtualization support for vendor daemon.
 * VM_ONLY  - Vendor Daemon can be operated in Virtual machine only
 * PHYSICAL - Vendor Daemon can be operated in Physical machine only
 */
FLEX_VM_TYPE ls_allow_vm = 0;

/* Heartbeat interval between the vendor daemon and lmbind.
   Specify in minutes; 0 means no heartbeat */
unsigned int ls_ba_heartbeat_interval = 30; 
/* The number of connection attempts after discovering a disconnection between
   vendor daemon and lmbind. */
unsigned int ls_ba_heartbeat_retry_count = 3; 
/* The wait period between connection attemps after discovering a 
   disconnection between the vendor daemon and lmbind. 
   Specify in minutes */
unsigned int ls_ba_heartbeat_retry_interval = 5; 
unsigned int ls_allow_tz_override = 0; /* Set to 1 to allow server time zone and time to be overridden */

void (*ls_borrow_out)(char * szBorrowData, int iSize)  = sBorrowOut;
void (*ls_borrow_in)(char * szBorrowData, int iSize) = sBorrowIn;
void (*ls_borrow_init)(char ** pszBorrowBuffer, int * piSize) = sBorrowInit;

/*
	Reserved for future use
*/
void (*ls_3sts_copy)() = NULL;
unsigned int ls_3sts_replicate_wait = 5;

/*
 *	When 1, Disallows the queuing with MAX keyword, when checkout request exceeds MAX value 
 */
int ls_disable_queue_on_max = 0 ; 


/*
 *	Code to determine location of "borrowing" file
 */

#ifdef PC /* WINNT */

/***********************************************************************/
/* @Brief Description:  It creates the borrow cache file folder path
 *
 * @Parameters:  pFlexPath, pBorrowFolder, createFolder
 * 
 * @Retun: void
 ************************************************************************/
static
void
sGetFlexPath(
	char *	pFlexPath,
	char *  pBorrowFolder,
	int 	createFolder)
{
	L_SHGETFOLDERPATHA		GSISHGetFolderPath = NULL;
	HANDLE					hSHFolder = NULL;
	L_SHCREATEDIRECTORYEX	GSISHCreateDir = NULL;
	HANDLE					hShell = NULL;
	char					fullBorrowPath[MAX_PATH] = {'\0'};
	char 					systemPath[MAX_PATH] = {'\0'};
	char 					flexLMDir[MAX_PATH] = {'\0'};
	char *					commonfilebuffer = NULL;
	int						gotValidPath = 0;

	if( !pFlexPath )
	{
		printf("Internal Error: Invalid borrow cache return buffer\n");
		return;
	}

	strncpy(flexLMDir, pBorrowFolder, MAX_PATH - 1);
	flexLMDir[MAX_PATH - 1] = '\0';

	hSHFolder = LoadLibrary("shfolder.dll");
		
	if ( hSHFolder != NULL )
	{	
		DWORD err = 0;
		
		GSISHGetFolderPath = (L_SHGETFOLDERPATHA)
			GetProcAddress(hSHFolder, "SHGetFolderPathA");
		if (GSISHGetFolderPath &&
			(*GSISHGetFolderPath)(NULL, CSIDL_COMMON_APPDATA|CSIDL_FLAG_CREATE, NULL, 0, systemPath) == S_OK)
		{
			if((strlen(systemPath) + strlen(flexLMDir)) < MAX_PATH)
			{
				sprintf(fullBorrowPath,"%s\\%s", systemPath, flexLMDir);
				gotValidPath = 1;
			}
		}
		FreeLibrary(hSHFolder);
		hSHFolder = NULL;
	}
	else 
	{
		commonfilebuffer = getenv("ALLUSERSPROFILE");
		
		if ( commonfilebuffer && ((strlen(commonfilebuffer) + strlen("\\Application Data\\") + strlen(flexLMDir)) < MAX_PATH)) 
		{
			sprintf(fullBorrowPath,"%s\\Application Data\\%s",commonfilebuffer, flexLMDir);
			gotValidPath = 1;
		}
	}

	if( createFolder == 1 ) 
	{
		hShell = LoadLibrary("shell32.dll");
		if(hShell != NULL)
		{
			GSISHCreateDir = (L_SHCREATEDIRECTORYEX)GetProcAddress(hShell, "SHCreateDirectoryExA");
		}
		else
		{
			printf("Internal Error: Loading the library failed\n");
		}
	}

	if( gotValidPath && ( _access(fullBorrowPath, 0 /*existence*/) == -1 ) )
	{
		gotValidPath = 0 ;
		/* Create FNP\Flexlm folder  */
		if( createFolder == 1 ) 
		{
			if(GSISHCreateDir && (*GSISHCreateDir)(NULL, fullBorrowPath, NULL) ==  ERROR_SUCCESS )
			{
				gotValidPath = 1;
			}
		}
	}

	if( !gotValidPath ) 
	{
		/*    Use default     */
		strcpy(fullBorrowPath, DEFAULT_FLEXLM_DIR);
		gotValidPath = 1;
		
		if( createFolder == 1 )
		{
			if(GSISHCreateDir && (*GSISHCreateDir)(NULL, fullBorrowPath, NULL) !=  ERROR_SUCCESS )
			{
				printf("Unable to create a borrow cache directory %s\n",fullBorrowPath);
			}
		}
	}

	if ( hShell )
	{
		FreeLibrary(hShell);
		hShell = NULL;
	}
		
	/*    Copy data over    */
	if ( gotValidPath )
	{
		strcpy(pFlexPath, fullBorrowPath);
	}
}

#else /* !PC WINNT */

/***********************************************************************/
/* @Brief Description: Checks the borrow cache file folder Path in case of non-windows
 *
 * @Parameters: pFlexPath, pBorrowFolder, createFolder
 *				createFolder is not used
 * 
 * @Return:  void
 ************************************************************************/
static
void
sGetFlexPath(
	char *	pFlexPath,
	char *  pBorrowFolder,
	int 	createFolder)
{
	strcpy(pFlexPath, "/var/tmp");
}
#endif /* WINNT */

static
void
sBorrowOut(
	char *	szBorrowData,
	int		iSize)
{
	FILE *	fp = NULL;
	char	buffer[MAX_PATH] = {'\0'};
	char	szBorrowFilename[MAX_PATH] = {'\0'};

	sGetFlexPath(buffer, CURR_FLEX_DIR, 1);
	sprintf(szBorrowFilename, "%s%s%sborrow", buffer,
		DIRECTORY_SEPARATOR, VENDOR_NAME);
	/*
	 *	Open file and position at EOF
	 */
	fp = fopen(szBorrowFilename, "ab");
	if(fp)
	{
		/*
		 *	Write entry
		 */
		(void)fwrite(szBorrowData, iSize, 1, fp);
		(void)fclose(fp);
	}
	return;
}

static
void
sBorrowIn(
	char *	szBorrowData,
	int		iSize)
{
	FILE *	fp = NULL;
	char	entry[4096] = {'\0'};
	char *	pPosition = NULL;
	char *	pBuffer = NULL;
	char *	pCurr = NULL;
	int		length = 0;
	long	filesize = 0;
	long	remaining = 0;
	char	buffer[MAX_PATH] = {'\0'};
	char	szBorrowFilename[MAX_PATH] = {'\0'};

	sGetFlexPath(buffer, CURR_FLEX_DIR, 1);
	sprintf(szBorrowFilename, "%s%s%sborrow", buffer,
		DIRECTORY_SEPARATOR, VENDOR_NAME);

	/*
	 *	Open borrow file
	 */
	fp = fopen(szBorrowFilename, "rb");
	if(fp)
	{
		/*
		 *	Allocate buffer to hold contents of new file
		 */
		(void)fseek(fp, 0, SEEK_END);
		remaining = filesize = ftell(fp);
		if(filesize > 0)
		{
			pBuffer = (char *)malloc(sizeof(char) * filesize);
			if(!pBuffer)
			{
				(void)fclose(fp);
				return;
			}
			(void)fseek(fp, 0, SEEK_SET);
			/*
			 *	Read entire contents of file into memory
			 */
			(void)fread(pBuffer, filesize, 1, fp);	/* overrun checked */
			(void)fclose(fp);
			fp = NULL;
			pCurr = pBuffer;
		}
		else
		{
			/*
			 *	File has no data
			 */
			(void)fclose(fp);
			return;
		}

		while(remaining)
		{
			/*
			 *	Read length of entry
			 */
			memset(entry, 0, sizeof(entry));
			memcpy((void *)&length, pCurr, sizeof(length));
			if(length > remaining)
			{
				if(pBuffer)
				{
					free(pBuffer);
					pBuffer = NULL;
				}
				return;
			}
			memcpy(entry, pCurr, length);
			remaining -= length;
			pPosition = pCurr;
			pCurr += length;

			/*
			 *	Compare with borrow/linger coming back in
			 */
			if(length == iSize &&
				memcmp(entry, szBorrowData, length) == 0)
			{
				/*
				 *	Found it
				 */
				if(remaining)
				{
					/*
					 *	Append the remaining portion of the file, starting
					 *	at the location for this current entry
					 */
					memcpy(pPosition, pCurr, remaining);
				}

				/*
				 *	Update what the new file size will be
				 */
				filesize -= length;

				/*
				 *	Delete original file
				 */
				(void)remove(szBorrowFilename);

				/*
				 *	Create new file with updated info
				 */
				fp = fopen(szBorrowFilename, "ab");
				if(fp)
				{
					(void)fwrite(pBuffer, filesize, 1, fp);
					(void)fclose(fp);
					fp = NULL;
					break;
				}
			}
		}
		/*
		 *	Cleanup
		 */
		if(pBuffer)
			free(pBuffer);
		if(fp)
			(void)fclose(fp);
	}
	return;
}

static
void
sBorrowInit(
	char **	ppBuffer,
	int *	piSize)
{
	char	buffer[MAX_PATH] = {'\0'};
	char	szBorrowFilename[MAX_PATH] = {'\0'};

	sGetFlexPath(buffer, CURR_FLEX_DIR, 1); /* Check whether the FNP folder exists, if it exists then don't create, otherwise create it */
	sprintf(szBorrowFilename, "%s%s%sborrow", buffer,
		DIRECTORY_SEPARATOR, VENDOR_NAME);
	if(sGetBorrowInfo(szBorrowFilename, ppBuffer, piSize ))	/* Read from FNP folder path if the borrow cache file exist */
	{
#ifdef PC 
		/* Check whether Macrovision folder exists,
		 * if it exists then read borrow cache from there,
		 * otherwise read from c:\flexlm folder  
		 */
		buffer[0]='\0';
		sGetFlexPath(buffer, PREV_FLEX_DIR, 0);
		sprintf(szBorrowFilename, "%s%s%sborrow", buffer,
			DIRECTORY_SEPARATOR, VENDOR_NAME);
		sGetBorrowInfo(szBorrowFilename, ppBuffer, piSize);
#endif
	}	
}

/***********************************************************************/
/* @Brief Description: Returns the status whether the borrow cache file is read or not
 *
 * @Parameters: szBorrowFilename , ppBuffer and piSize
 * 
 * @Return: The status 0-success, -1 on failure 
 ************************************************************************/
static
int 
sGetBorrowInfo(
	char *szBorrowFilename, 
	char **	ppBuffer,
	int *	piSize)
{
	FILE *	fp = NULL;
	long	filesize = 0;

	if(szBorrowFilename)
	{
		fp = fopen(szBorrowFilename, "rb");
		
		if(fp)
		{
			(void)fseek(fp, 0, SEEK_END);
			filesize = ftell(fp);
			(void)fseek(fp, 0, SEEK_SET);
			*ppBuffer = (char *)malloc(sizeof(char) * filesize);
			if(*ppBuffer)
			{
				(void)fread(*ppBuffer, filesize, 1, fp);	/* overrun checked */
				*piSize = filesize;
			}
			else
			{
				*piSize = 0;
			}
			
			(void)fclose(fp);
			remove(szBorrowFilename);
			return 0;
		}
	}
	return -1;
}
