#include "inslic.h"

#include "pp_flexnet/FlexNETAPI.h"


bool _inited=false;

bool init()
{
	if(_inited)
		return true;
	bool re= pp_lc_init();
	_inited=true;
	return re;
}

bool co( const char* feature,const char* ver )
{
	if(!_inited)
		init();

	return pp_lc_checkout(feature,ver);
}

bool ci( const char*feature )
{
	return pp_lc_checkin(feature);
}

void tc()
{
	pp_lc_exit();
}
