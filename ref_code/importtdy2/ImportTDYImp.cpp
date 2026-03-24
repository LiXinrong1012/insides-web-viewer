#include "ImportTDYImp.h"


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

LoadKeyItemFunc ImportTDYImp::getLoadKeyItemFunc( const QString& str )
{
	return _loadKeyItemFuncMap[str];
}

void ImportTDYImp::processItem( ImportTDYPara* para,INSEditor::Parse::LineItem* item)
{
	QString keyName=item->keyname.toUpper();
		
	LoadKeyItemFunc func=para->importTDYImp->getLoadKeyItemFunc(keyName);
		
	if(func)
		func(para,item);
}

void ImportTDYImp::processItemChildren( ImportTDYPara* para,INSEditor::Parse::LineItem* item )
{
	if(item->type!=INSEditor::Parse::ASSEMBLYITEM)
		// to-do: warning
		return;

	INSEditor::Parse::AssemblyItem* assemblyItem=(INSEditor::Parse::AssemblyItem*)item;
	foreach(INSEditor::Parse::LineItem* c,assemblyItem->getItemList())
		processItem(para,c);
}

