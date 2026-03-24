#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Parser.h"
#include "ParseAssembly.h"
#include "MainItem.h"

/*
template <typename T>
	string join(const T& v, const string& delim) {
		ostringstream s;
		int size=v.size();
		for(int ii=0;ii<size;++ii){
			if (&v[ii] != &v[0]) {
				s << delim;
			}
			s << v[ii];
		}
		return s.str();
}

using namespace std ;
namespace Parse {

	int		Parser::parse ( Assembly* pAssem, map<keyName, Template*>* tempMap ) 
	{
		// parse assembly
		for ( map<string, Assembly*>::iterator it = pAssem->mapAssemblys.begin(); it != pAssem->mapAssemblys.end(); it++ )
		{
			if ( parse(it->second, tempMap) != 0 )
				return 1 ;
		}

		// parse part
		for ( map<string, Part*>::iterator it = pAssem->mapParts.begin(); it != pAssem->mapParts.end(); it++ )
		{
			if ( parse(it->second, tempMap) != 0 )
				return 1 ;
		}

		// parse Key
		for ( list<Key*>::iterator it = pAssem->listKeys.begin(); it != pAssem->listKeys.end(); it++ )
		{
			if ( parse(*it, tempMap) != 0 )
				return 1 ;		
		}

		return 0 ;
	}

	int		Parser::parse ( Part* pPart, map<keyName, Template*>* tempMap ) 
	{
		// parse Key
		for ( list<Key*>::iterator it = pPart->listKeys.begin(); it != pPart->listKeys.end(); it++ )
		{
			if ( parse(*it, tempMap) != 0 )
				return 1 ;
		}

		return 0 ;
	}

	int     Parser::parse ( Key* pKey, map<keyName, Template*>* tempMap )
	{
		string strMainItem = pKey->strFull ;

		string::size_type pos = 0, len = strMainItem.length() ;
		MainItem* pmain = NULL ;
		SubItem*  psub  = NULL ;
		string val ;
		char Key, lastkey = ',' ; 
		bool bhaveid = false ;
		Template* pTemplate = NULL ;

		if ( tempMap != NULL )
		{
			map<keyName, Template*>::iterator it = tempMap->find(pKey->strKeyName) ;
			if ( it != tempMap->end() )
				pTemplate = it->second ;
		}
		
		while ( pos <  len )
		{
			Key = getNextVal ( val, pos, strMainItem ) ;
			if ( val == "" ) continue ;

			switch ( Key ) 
			{
			case '/':					// 主项分割符
				pmain = &(pKey->mainItem) ;
				pmain->mainname = val ;
				pmain->iLineNumber = pKey->iLineNum ;
				pmain->filenm = pKey->strFilename ;
				break ;
			case '=':					// 子项分割符
				if ( pmain->subhash.find(val) != pmain->subhash.end() )
				{
					stringstream ss ;	ss.str("") ;
					ss << val << " has been defined at least twice at " << pKey->toLocation() << "." << endl ;

					m_strError = ss.str() ;

					return 1; 
				}

				psub = new SubItem() ;
				if ( pTemplate != NULL && (!isSubItem(val, pTemplate)) )
				{
					string location ;
					pmain->toLocation(location) ;

					string subs = join(pTemplate->subitemnames, ",") ;

					stringstream ss ;	ss.str("") ;
					ss << "unknown subitem " << val << " for " 
					   << pKey->strKeyName << " at " << pKey->toLocation()+ "." << endl ;
					ss << "The optional subitems for " << pKey->strKeyName << " are: " ;
					ss << subs << "." << endl ;

					m_strError = ss.str() ;

					return 1; 
				}
					
				psub->subname = val ;
				pmain->subhash.insert(make_pair(val, psub)) ;
				pmain->sublist.push_back(psub) ;
				break ;
			default:
				if ( isProperty(val, pTemplate) && (lastkey != '=') )			
				{
					// 如果是属性，就直接生成一个子项, 但紧随在等号后面的不是属性
					pmain->properties.insert(make_pair(val, val)) ;
				}
				else
				{
					if ( psub != NULL )		// 子项值
						psub->valList.push_back(val);	
					else if ( !bhaveid )	// 主项 id
					{
						pmain->mainID = val ;
						bhaveid = true ;
					}
					else					// 主项 label
						pmain->mainLabel = val ;
				}

				break ;
			}

			lastkey = Key ;

		}

		if ( pKey->mainItem.mainLabel == "" )
			pKey->mainItem.mainLabel = pKey->strKeyName + "_" + pKey->mainItem.mainID ;

		return 0 ;
	}

	char    Parser::getNextVal ( string& val, string::size_type& idx, const string strMainItem )
	{
		val.clear() ;

		string::size_type pos ;
		char Key ;
		bool bDeactive = false ;			// 代表 主分隔符 是否失效

		for ( pos = idx; pos < strMainItem.length(); pos++ )
		{
			Key  = strMainItem.at(pos) ;	// 遇见 '"', bDeactive 取反
			if ( Key == '\"' ) bDeactive =  !bDeactive ;

			if ( isDelimiter(Key, bDeactive) )	// 如果是 Key 就结束
				break ;
			else
				val.push_back(Key) ;
		}

		idx = pos+1;

		return Key ;
	}

	bool    Parser::isDelimiter ( const char c, const bool bDeactive )
	{
		if ( bDeactive )	return false ;

		bool bKey = false ;
		switch ( c )
		{
		case ',':
		case '=':
		case '/':
		case '\0':
		case '{':
			bKey = true ;
			break ;
		default:
			bKey = false ;
			break ;
		}
		return bKey ;
	}

	bool	Parser::isProperty    ( string& val, Template* pTemp )
	{
		if ( pTemp == NULL )
			return false ;
		else
		{
			string str = val ;

			transform ( val.begin(), val.end(), str.begin(), toupper )  ;

			bool bProperty = false ; 

			vector<string>::iterator it = find ( pTemp->properties.begin(), pTemp->properties.end(), str ) ;
			if ( it !=  pTemp->properties.end() )
				bProperty = true ;

			return bProperty ;
		}
	}

	bool	Parser::isSubItem    ( string& val, Template* pTemp )
	{
		if ( pTemp == NULL )
			return true ;
		else
		{
			if ( pTemp->subitemnames.size() == 0 )
				return true ;
			else
			{
				string str = val ;

				transform ( val.begin(), val.end(), str.begin(), toupper )  ;

				bool bsubitem = false ; 
				vector<string>::iterator it = find ( pTemp->subitemnames.begin(), pTemp->subitemnames.end(), str ) ;
				if ( it !=  pTemp->subitemnames.end() )
					bsubitem = true ;

				return bsubitem ;
			}
		}
	}

}

*/