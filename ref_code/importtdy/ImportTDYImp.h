#pragma once

#include <QMap>
#include <QString>
#include <list>
#include <map>
#include <vector>
#include "precore/Assembly.h"

using namespace std;

namespace Parse{
	struct Key;
	class Part;
	class Assembly;

	typedef Parse::Assembly TDYAssembly;
}


namespace INSIDES{
	class ModelDocument;
	class BaseItem;
}

class ImportTDYImp;


struct ImportTDYPara
{
	ImportTDYImp*	importTDYImp;
	INSIDES::ModelDocument*	doc;
	INSIDES::Assembly*		currentAssembly;
	INSIDES::BaseItem*		currentPart;
};

typedef bool (*LoadKeyItemFunc)(ImportTDYPara* para,Parse::Key* keyItem);

typedef bool (*LoadPartItemFunc)(ImportTDYPara* para,Parse::Part* partKey);

class ImportTDYImp
{
public:
	ImportTDYImp(void);
	~ImportTDYImp(void);

	typedef QMap<QString,LoadKeyItemFunc> LoadKeyItemFuncMap;
	typedef QMap<QString,LoadPartItemFunc> LoadPartItemFuncMap;

	void registerLoadKey(const QString& str,LoadKeyItemFunc func);
	void registerLoadPart(const QString& str,LoadPartItemFunc func);

	LoadKeyItemFunc getLoadKeyItemFunc(const QString& str);
	LoadPartItemFunc getLoadPartItemFunc(const QString& str);

	bool processKeyListParameters(ImportTDYPara* para,list<Parse::Key*>& keyItemList);
	bool processKeyList(ImportTDYPara* para,list<Parse::Key*>& keylist,bool checkParameters=true);
	bool processPartList(ImportTDYPara* para,map<string,Parse::Part*>* partlist);
	QString stringlist2QString(std::vector<string>& strlist);
private:

	LoadKeyItemFuncMap		_loadKeyItemFuncMap;
	LoadPartItemFuncMap		_loadPartItemFuncMap;
};

void registerImportFuncs(ImportTDYImp* imp);