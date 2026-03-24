#pragma once
#include "Parse_Export_Dll.h"	// for PARSE_EXPORT
#include <string>
#include <vector>
#include <map>
using namespace std ;

namespace Parse {

	class Key;
	class Part;
	class Assembly;

	struct PARSE_EXPORT Template 
	{
		vector<string> properties ;
		vector<string> subitemnames ;
		string shorthelp ;
		string longhelp ;
	};

	typedef string keyName ;

	class PARSE_EXPORT Parser
	{
	public:
		Parser(){};
		~Parser(void) {};

		int		parse(Assembly* pAssem, map<keyName, Template*>* tempMap=NULL) ;

		string  getErrorMsg() { return m_strError ; } ;

	private:
		int		parse(Part* pPart, map<keyName, Template*>* tempMap=NULL) ;
		int		parse(Key* pKey, map<keyName, Template*>* tempMap=NULL) ;

		char    getNextVal	( string& val, string::size_type& idx, const string strMainItem ) ;
		bool    isDelimiter	( const char c, const bool bDeactive = false ) ;
		bool	isProperty  ( string& val, Template* pTemp ) ;
		bool	isSubItem   ( string& val, Template* pTemp ) ;

		string  m_strError ;
	};
}
