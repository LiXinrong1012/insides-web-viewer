#pragma once

#include <QMap>
#include <QString>
#include <list>
#include <map>
#include <vector>

#include "precore/Assembly.h"

#include "edcompile/mainitem.h"

using namespace std;

namespace INSIDES{
	class ModelDocument;
	class BaseItem;
}

class ImportTDYImp;


struct ImportTDYPara
{
	ImportTDYImp*			importTDYImp;
	INSIDES::Assembly*		currentAssembly;
	INSIDES::BaseItem*		currentPart;
};

typedef bool (*LoadKeyItemFunc)(ImportTDYPara* para,INSEditor::Parse::LineItem* keyItem);

/*!
	@brief  导入TDY解析类
	@date   2015.7.3
	@author Jerry
*/
class ImportTDYImp
{
public:
	ImportTDYImp(void);
	~ImportTDYImp(void);

	typedef QMap<QString,LoadKeyItemFunc> LoadKeyItemFuncMap;

	///注册加载函数键
	void registerLoadKey(const QString& str,LoadKeyItemFunc func);

	///获得对应str的加载函数
	LoadKeyItemFunc getLoadKeyItemFunc(const QString& str);

	///解析item 
	void processItem( ImportTDYPara* para,INSEditor::Parse::LineItem* item);

	///解析item的子项
	void processItemChildren(ImportTDYPara* para,INSEditor::Parse::LineItem* item);

private:
	
	LoadKeyItemFuncMap		_loadKeyItemFuncMap;
};

///注册导入函数指针
void registerImportFuncs(ImportTDYImp* imp);