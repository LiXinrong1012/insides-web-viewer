#pragma once

#include <QString>
#include <QStringList>
#include <QList>
#include <QMap>
using namespace std ;

/*
namespace Parse {

	class Key;
	class Part;
	class Assembly;

	struct Template 
	{
		QStringList properties ;
		QStringList subitemnames ;
		QString		shorthelp ;
		QString		longhelp ;
	};

	typedef QString keyName ;

	class Parser
	{
	public:
		Parser(){};
		~Parser(void) {};

		int		parse(Assembly* pAssem, map<keyName, Template*>* tempMap=NULL) ;

		QString  getErrorMsg() { return m_strError ; } ;

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

*/