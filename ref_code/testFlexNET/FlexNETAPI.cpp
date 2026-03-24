#include "FlexNETAPI.h"
#include "lmclient.h"

#include <QtGui>

#define FEATURE "f1"
VENDORCODE code;
LM_HANDLE *lm_job;
struct flexinit_property_handle *initHandle;
char feature[MAX_FEATURE_LEN * 2] = {'\0'};
int nlic = 1;

static void init(struct flexinit_property_handle **);
static void cleanup(struct flexinit_property_handle *);


bool lc_init()
{
	char * output = NULL;
	struct flexinit_property_handle *initHandle;
	int stat;


	init(&initHandle);

	return true;
}

bool lc_checkout()
{
	if (lc_new_job(0, lc_new_job_arg2, &code, &lm_job))
	{
		lc_perror(lm_job, "lc_new_job failed");
		cleanup(initHandle);
		QMessageBox box;
		box.setText("License check failed. If you have any problems, please contanct Jerry He\
					hejw06@gmail.com");
		box.exec();
		exit(lc_get_errno(lm_job));
		return false;
	}

	strcpy(feature,"main");

	//(void)lc_set_attr(lm_job, LM_A_LICENSE_DEFAULT, (LM_A_VAL_TYPE)LICPATH);
	//lc_set_attr(lm_job,LM_A_LICENSE_DEFAULT,(LM_A_VAL_TYPE)"D:\\mylicense\\uncounted.lic");

	if(lc_checkout(lm_job, feature, "1.0", nlic, LM_CO_NOWAIT, &code, LM_DUP_NONE))
	{
		lc_perror(lm_job, "checkout failed");
		cleanup(initHandle);
		exit (lc_get_errno(lm_job));
		return false;
	}

	return true;
}
bool lc_checkin()
{
	lc_checkin(lm_job, feature, 0);
	lc_free_job(lm_job);
	cleanup(initHandle);
	return true;
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
#endif
}