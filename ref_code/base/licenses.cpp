#include "licenses.h"

#include "pp_flexnet/FlexNETAPI.h"

#include <QDate>

static bool _inited=false;

#define JERRY_REMOVE_LICENSE return checkDate();
//#define JERRY_REMOVE_LICENSE 

bool checkDate()
{
	if(QDate::currentDate()>QDate(2018,11,26)
		&& (1==0))
		return false;
	return true;
}

bool Base::L::init()
{
	JERRY_REMOVE_LICENSE

	if(_inited)
		return true;
	bool re= pp_lc_init();
	_inited=true;
	return re;
}

bool Base::L::co( const char* feature,const char* ver )
{
	JERRY_REMOVE_LICENSE

	if(!_inited)
		init();

	return pp_lc_checkout(feature,ver);
}

bool Base::L::ci( const char*feature )
{
	JERRY_REMOVE_LICENSE

	return pp_lc_checkin(feature);
}

void Base::L::tc()
{
	pp_lc_exit();
}

void Base::L::setlicensefile( const char* licensefile )
{
	pp_lc_set_licensedir(licensefile);
}
