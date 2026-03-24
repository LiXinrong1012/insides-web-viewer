#include "BasicConstant.h"

#include "BasicMathFunc.h"
#include "functionsmanager.h"

void Add_ConsantMap( map<string, double>& mapConst )
{
	mapConst["PI"]		= 3.1415926535897932385 ;
	mapConst["E"]		= 2.7182818284590452354 ;
	mapConst["RTOD"]	= 57.295779513082323 ;
	mapConst["DTOR"]	= 0.017453292519943 ;
	mapConst["SIN45"]	= 0.707106781186548 ;
	mapConst["COS45"]	= 0.707106781186548 ;
}

static FunctionsManager* tmpFunctionManger;

#define JERRY_REGISTER_DEC_FUNC(NAME) \
	{BaseFunction* tmp=new NAME(); \
	tmpFunctionManger->insert(tmp->m_strFuncName,tmp);}


void registerBuildMathFunc( FunctionsManager* functionManager )
{
	tmpFunctionManger=functionManager;

	JERRY_REGISTER_DEC_FUNC(LOGFunction) ;
	JERRY_REGISTER_DEC_FUNC(LOG10Function) ;
	JERRY_REGISTER_DEC_FUNC(EXPFunction) ;
	JERRY_REGISTER_DEC_FUNC(SINFunction) ;
	JERRY_REGISTER_DEC_FUNC(RANDFunction) ;
	JERRY_REGISTER_DEC_FUNC(COSFunction) ;
	JERRY_REGISTER_DEC_FUNC(TANFunction) ;
	JERRY_REGISTER_DEC_FUNC(COTFunction) ;
	JERRY_REGISTER_DEC_FUNC(SINHFunction) ;
	JERRY_REGISTER_DEC_FUNC(COSHFunction) ;
	JERRY_REGISTER_DEC_FUNC(TANHFunction) ;
	JERRY_REGISTER_DEC_FUNC(COTHFunction) ;
	JERRY_REGISTER_DEC_FUNC(SQRTFunction) ;
	JERRY_REGISTER_DEC_FUNC(ASINFunction) ;
	JERRY_REGISTER_DEC_FUNC(ACOSFunction) ;
	JERRY_REGISTER_DEC_FUNC(ATANFunction) ;
	JERRY_REGISTER_DEC_FUNC(ATAN2Function) ;
	JERRY_REGISTER_DEC_FUNC(SIGNFunction) ;
	JERRY_REGISTER_DEC_FUNC(ABSFunction) ;
	JERRY_REGISTER_DEC_FUNC(MAXFunction) ;
	JERRY_REGISTER_DEC_FUNC(MINFunction) ;
	JERRY_REGISTER_DEC_FUNC(MODFunction) ;
	JERRY_REGISTER_DEC_FUNC(ANDFunction) ;
	JERRY_REGISTER_DEC_FUNC(ORFunction) ;
	JERRY_REGISTER_DEC_FUNC(EQFunction) ;
	JERRY_REGISTER_DEC_FUNC(NEFunction) ;
	JERRY_REGISTER_DEC_FUNC(LTFunction) ;
	JERRY_REGISTER_DEC_FUNC(LEFunction) ;
	JERRY_REGISTER_DEC_FUNC(GTFunction) ;
	JERRY_REGISTER_DEC_FUNC(GEFunction) ;
	JERRY_REGISTER_DEC_FUNC(IFFunction) ;




}
