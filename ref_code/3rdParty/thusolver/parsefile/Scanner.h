#pragma once
#include "Parse_Export_Dll.h"	// for PARSE_EXPORT
#include <fstream>
#include <list>
#include <string>
using namespace std ;

namespace Parse {

	class Key ;
	class Structure ;
	class Assembly ;

	// Scanner 提供一种“扫描”策略，用于处理将文件中定义的内容转换为 Assembly
	class PARSE_EXPORT Scanner 
	{
	public:
		Scanner();
		~Scanner(void);

		// scan 将 filenm 中定义的内容转换为 mainModel
		int		scan(Assembly* mainModel, string filenm ) ;

		string  getErrorMsg() { return m_strError ; } ;

	private:
		Key*	getNextKey ( Key* curKey, ifstream& fin, int& iCurLineNum, bool& bValid ) ;

		// 成功返回true，失败返回false

		bool	scanAssembly ( ifstream& fin, Key*& curKey, bool&bValid ) ;
		bool	scanInclude ( Key* includeKey ) ;

		string	getStructName ( Key* curKey ) ;

		bool	isPart ( Key* ) ;
		bool	isAssembly ( Key* ) ;

		Structure* curStructure ;
		string strCurFileName ;

		list<string>	 listFileName ;
		list<Structure*> listStruct ; 

		string m_strError ;
	};

	bool isSpace	( char c ) ;    // 判断 char c 是不是空格, tab, 回车, 换行
	bool isMath		( char c ) ;	// 判断 char c 是不是 + - * / (  ) ^
	bool isChar		( char c ) ;	// 判断 char c 是不是 a-z, 或 A-Z 
	int countNumOfChar ( string& str, char c ) ;	// 统计 str 中 char c 的个数
	string  PreDealString		( const string str ) ;	// 将 str 中的字母大写，空格、回车、换行符去掉

}