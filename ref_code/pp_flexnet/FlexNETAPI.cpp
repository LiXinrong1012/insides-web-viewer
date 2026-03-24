#include "FlexNETAPI.h"


#include "FlexNET/machind/lmclient.h"
#include "FlexNET/machind/lm_attr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef PC
#define LICPATH "@localhost"
#else
#define LICPATH "@localhost:license.dat:."
#endif /* PC */

#define FEATURE "f1"
VENDORCODE code;
static LM_HANDLE *lm_job;
static flexinit_property_handle* initHandle;
static char lm_feature[1024];

static void init(struct flexinit_property_handle **);
static void cleanup(struct flexinit_property_handle *);



bool pp_lc_init()
{
	char feature[MAX_FEATURE_LEN * 2] = {'\0'};
	char * output = NULL;

	init(&initHandle);


	if (lc_new_job(0, lc_new_job_arg2, &code, &lm_job))
		return false;

	return true;
}


bool pp_lc_reject()
{
	lc_perror(lm_job, "lc_new_job failed");
	cleanup(initHandle);
	exit(lc_get_errno(lm_job));
}

void pp_lc_set_licensedir( const char* licensedir )
{
	lc_set_attr(lm_job, LM_A_LICENSE_DEFAULT, (LM_A_VAL_TYPE)licensedir);
}

bool pp_lc_checkout(const char* feature,const char* ver)
{
	strcpy_s(lm_feature,feature);

	lc_set_attr(lm_job, LM_A_CHECK_BADDATE, LM_A_VAL_TYPE("1"));
	lc_set_attr(lm_job, LM_A_LICENSE_DEFAULT, (LM_A_VAL_TYPE)LICPATH);
	char lmVersion[20];
	if(!ver)
		strcpy_s(lmVersion,"1.0");
	else
		strcpy_s(lmVersion,ver);
	if(lc_checkout(lm_job, lm_feature, lmVersion, 1, LM_CO_NOWAIT, &code, LM_DUP_NONE))
		return false;

	return true;
}

bool pp_lc_checkin(const char*feature)
{
	strcpy_s(lm_feature,feature);
	lc_checkin(lm_job, lm_feature, 0);
	return true;
}

int pp_lc_exit()
{
	lc_free_job(lm_job);
	cleanup(initHandle);
	exit(lc_get_errno(lm_job));
	return 0;
}


static void init(struct flexinit_property_handle **handle)
{
#ifndef NO_ACTIVATION_SUPPORT
	struct flexinit_property_handle *ourHandle;
	int stat;

	if (stat = lc_flexinit_property_handle_create(&ourHandle))
	{
		fprintf(stderr, "lc_flexinit_property_handle_create() failed: %d\n", stat);
		exit(1);
	}
	if (stat = lc_flexinit_property_handle_set(ourHandle,
			(FLEXINIT_PROPERTY_TYPE)FLEXINIT_PROPERTY_USE_TRUSTED_STORAGE,
			(FLEXINIT_VALUE_TYPE)1))
	{
		fprintf(stderr, "lc_flexinit_property_handle_set failed: %d\n", stat);
	    exit(1);
	}
	if (stat = lc_flexinit(ourHandle))
	{
		fprintf(stderr, "lc_flexinit failed: %d\n", stat);
	    exit(1);
	}
	*handle = ourHandle;
#endif /* NO_ACTIVATION_SUPPORT */
}

static void cleanup(struct flexinit_property_handle *initHandle)
{
#ifndef NO_ACTIVATION_SUPPORT
	int stat;

	if (stat = lc_flexinit_cleanup(initHandle))
	{
		fprintf(stderr, "lc_flexinit_cleanup failed: %d\n", stat);
	}
	if (stat = lc_flexinit_property_handle_free(initHandle))
	{
		fprintf(stderr, "lc_flexinit_property_handle_free failed: %d\n", stat);
	}
#endif /* NO_ACTIVATION_SUPPORT */
}


