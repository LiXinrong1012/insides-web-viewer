#pragma once
#include "Parse_Export_Dll.h"	// for PARSE_EXPORT
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std ;

namespace Parse {

	struct PARSE_EXPORT SubItem
	{
		string			subname  ;	// 子项的名字
		vector<string>	valList ;	// 子项的值，可以是多值，所以用了vector存储

		SubItem()  ;
		~SubItem() ;

		SubItem & operator =  (SubItem & source) ;
	};

	struct PARSE_EXPORT MainItem
	{
		MainItem() ;
		MainItem(MainItem&) ;
		~MainItem() ;

		string mainname ;		// 主项的keyword
		string mainID  ;		// 主项的ID
		string mainLabel ;		// 主项的label，也是名字

		string filenm;			// 主项属于的文件名
		int iLineNumber ;	// 主项的第一行在文件中的行号

		map<string, SubItem*>	subhash ;	// 主项还有的子项列表

		map<string, string> properties ;

		list<SubItem*> sublist ;	

		bool GetValue ( string subname, vector<string>*& val, const int num = 1, const bool bcheck = false ) ;

		bool GetValue ( int &num, string subname, vector<string>*& val ) ;

		void toLocation ( string& location ) ;	// 将location赋值为文件名+行号

		bool hasProperty ( string const& s )  ;

		map<string, string>* getProperties() {
			if ( properties.size() == 0 )
				return NULL ;
			else
				return &properties ;
		}

		int  PropertySize()  { return properties.size() ;} ;

		void write ( string prestr, ofstream& fout ) ;

		MainItem & operator =  (MainItem & source) ;

		bool findSubs( list<string> subnames, list<SubItem*>* subs ) ;

		bool confirmSubs( list<string>& subnames ) ;
	};
}

