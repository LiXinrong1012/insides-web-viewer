#include "testflexnet.h"
#include <QtGui/QApplication>

#include "lmclient.h"
#include "FlexNETAPI.h"

static void init(struct flexinit_property_handle **);
static void cleanup(struct flexinit_property_handle *);


int main(int argc, char *argv[])
{
	char feature[15 * 2] = {'\0'};
	char * output = NULL;
	struct flexinit_property_handle *initHandle;
	int stat;
	int nlic = 1;

	init(&initHandle);

	lc_init();
	QApplication a(argc, argv);

	//lc_checkout();
	lc_checkin();

	testFlexNET w;
	w.show();
	return a.exec();
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