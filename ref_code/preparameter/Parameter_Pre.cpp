#include "Parameter_Pre.h"
#include "Parameter.h"


Parameter*  parameter_create()
{
	return (new Parameter());
}

void  parameter_destory( Parameter* para )
{
	delete para;
}

int  parameter_str2para( Parameter* para,const std::string& strFun,ParameterCollection * fmap/*=NULL*/ )
{
	return para->strToPara(strFun,fmap);
}

double parameter_eval( Parameter* para )
{
	return para->eval();
}
