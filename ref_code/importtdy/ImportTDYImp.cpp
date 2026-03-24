#include "ImportTDYImp.h"

#include "thusolver/parsefile/Scanner.h"
#include "thusolver/parsefile/Parser.h"
#include "thusolver/parsefile/TemplateFactory.h"
#include "thusolver/parsefile/Assembly.h"

#include "base/Console.h"

using namespace Base;

ImportTDYImp::ImportTDYImp(void)
{
}


ImportTDYImp::~ImportTDYImp(void)
{
}

void ImportTDYImp::registerLoadKey( const QString& str,LoadKeyItemFunc func )
{
	_loadKeyItemFuncMap[str]=func;
}

void ImportTDYImp::registerLoadPart( const QString& str,LoadPartItemFunc func )
{
	_loadPartItemFuncMap[str]=func;
}

LoadKeyItemFunc ImportTDYImp::getLoadKeyItemFunc( const QString& str )
{
	return _loadKeyItemFuncMap[str];
}

LoadPartItemFunc ImportTDYImp::getLoadPartItemFunc( const QString& str )
{
	return _loadPartItemFuncMap[str];
}

bool ImportTDYImp::processKeyListParameters(ImportTDYPara* para,list<Parse::Key*>& keyItemList)
{
	for(list<Parse::Key*>::iterator b=keyItemList.begin();b!=keyItemList.end();++b)
	{
		Parse::Key* onekey=*b;
		Parse::MainItem& mainItem=onekey->mainItem;

		string keyName=mainItem.mainname;
		if(keyName=="PARAMETER")
		{
			LoadKeyItemFunc func=para->importTDYImp->getLoadKeyItemFunc(keyName.c_str());
			if(func)
				func(para,onekey);
		}
	}
	return true;
}

bool ImportTDYImp::processKeyList( ImportTDYPara* para,list<Parse::Key*>& keyItemList,bool checkParameters )
{
	for(list<Parse::Key*>::iterator b=keyItemList.begin();b!=keyItemList.end();++b)
	{
		Parse::Key* onekey=*b;
		Parse::MainItem& mainItem=onekey->mainItem;

		string keyName=mainItem.mainname;
		if(checkParameters || keyName!="PARAMETER"){
			LoadKeyItemFunc func=para->importTDYImp->getLoadKeyItemFunc(keyName.c_str());
			if(func)
				func(para,onekey);
		}
	}
	return true;
}

QString ImportTDYImp::stringlist2QString( std::vector<string>& strlist )
{
	QStringList vec;
	for(int i=0;i<strlist.size();++i)
		vec.push_back(strlist[i].c_str());
	return vec.join(",");
}
