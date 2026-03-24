#pragma once

#include <map>
#include <string>
class Parameter;

typedef std::map<std::string, Parameter *> ParameterCollection;

Parameter*    parameter_create();
void  parameter_destory(Parameter* para);
int  parameter_str2para(Parameter* para,const std::string& strFun,ParameterCollection * fmap=NULL);
double  parameter_eval(Parameter* para);
