#pragma once
#include "Parse_Export_Dll.h"	// for PARSE_EXPORT
#include "MainItem.h"
#include <string>
#include <list>
#include <map>

using namespace std ;

namespace Parse {

	class Structure ;

	struct PARSE_EXPORT Key
	{
		Key() { master = NULL ; } ;

		// 关键词名，以及所有字符串
		string strKeyName ;			// 关键词
		string strFull ;			// 所有字符

		MainItem mainItem ;

		// 文件中的位置
		string strFilename ;		// 文件名
		int iLineNum ;				// 行号
		string toLocation() ;

		Structure* master ;			// 属于哪个Part或Assembly

		void write(string prestr, ofstream& fout) ;	
	};

	class PARSE_EXPORT Structure 
	{
	public:
		string strType ;
		string strName ;

		list<Key*> listKeys ;
		void addKey ( Key* curkey ) { listKeys.push_back(curkey); } ;

		virtual bool isPart() = NULL ;
		virtual bool isAssembly() = NULL ;

	public:// 文件中的位置
		string strFilename ;		// 文件名
		int iLineNum ;				// 行号

		string toLocation() ;
	};

	class PARSE_EXPORT Part : public Structure 
	{
	public:
		virtual bool isPart() { return true ; } ;
		virtual bool isAssembly() { return false ; } ;

		void write(string prestr, ofstream& fout) ;

		bool bHasParameters() ;
		bool bHas( Key*& pkey, string name ) ;
	};

	class PARSE_EXPORT Assembly : public Structure 
	{
	public:
		Assembly() { strType = "ASSEMBLY" ; } ;

		map<string, Part*>		mapParts ;
		map<string, Assembly*>	mapAssemblys;

		void addPart(Part* curPart) { mapParts[curPart->strName] = curPart; } ;
		void addAssembly(Assembly* curAssem) { mapAssemblys[curAssem->strName] = curAssem; } ;

		virtual bool isPart() { return false ; } ;
		virtual bool isAssembly() { return true ; } ;

		void write(string filenm) ;

	private:
		void write(string prestr, ofstream& fout) ;
	};


	string PARSE_EXPORT KeyLocation(Key* pkey) ;
	string PARSE_EXPORT MainItemLocation(MainItem* pmain) ;
}