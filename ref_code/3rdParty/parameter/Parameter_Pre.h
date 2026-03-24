#pragma once

#include "Parameter_Export_DLL.h"
#include <map>
#include <string>
class Parameter;

typedef std::map<std::string, Parameter *> ParameterCollection;

PARAMETER_EXPORT Parameter*    parameter_create();
PARAMETER_EXPORT void  parameter_destory(Parameter* para);
PARAMETER_EXPORT int  parameter_str2para(Parameter* para,const std::string& strFun,ParameterCollection * fmap=NULL);
PARAMETER_EXPORT double  parameter_eval(Parameter* para);
