#pragma once
#include <string>
#include <map>

using namespace std ;

class FunctionsManager;


void Add_ConsantMap( map<string, double>& mapConst ) ;

void registerBuildMathFunc(FunctionsManager* functionManager);
