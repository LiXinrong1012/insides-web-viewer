#pragma once 
#include "Parse_Export_Dll.h"	// for PARSE_EXPORT
#include "Parser.h"
#include <string.h>
#include <stdio.h>
#include <algorithm>

using namespace std ;
using namespace Parse ;

/* 以下这段代码用来定义一个约束库 */
typedef map<string, Template*> map_Template ;

struct PARSE_EXPORT TemplateFactory
{
	static Template* createTemplate( string& s )
	{
		map_Template::iterator it = getMap()->find(s) ;
		if ( it == getMap()->end() )
		{
			Template* pTemp = new Template ;
			string upperkey = s;
			transform(upperkey.begin(), upperkey.end(), upperkey.begin(), toupper);
			getMap()->insert(std::pair<string, Template*>(upperkey, pTemp)) ;
			return pTemp ;
		}
		else
			return (it->second) ;
	}

	static bool find ( string& s )
	{
		map_Template::iterator it = getMap()->find(s) ;
		if ( it == getMap()->end() )
			return false ;
		else
			return true ;
	}

	static map_Template* getMap() 
	{
		if ( !mapTemplate ) mapTemplate = new map_Template ;
		return mapTemplate ;
	}


	static map_Template* mapTemplate ;

public:
	void outputxml() ;
	void importxml(string filename) ;
};

template<typename T>
struct TemplateRegister : public TemplateFactory
{
	TemplateRegister()
	{
		T tmp ;
		tmp.register_template() ;
	}
};

#define REGISTER_DEC_TEMPLATE(classname) \
	static TemplateRegister<classname> reg_TEMPLATE##classname

#define REGISTER_DEF_TEMPLATE(classname) \
	TemplateRegister<classname> classname::reg_TEMPLATE##classname