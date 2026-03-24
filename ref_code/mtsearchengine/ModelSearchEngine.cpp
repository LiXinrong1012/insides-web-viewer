#include "ModelSearchEngine.h"
#include "precore/modeldocument.h"
#include "precore/precore_data.h"



ModelSearchEngine::ModelSearchEngine(void)
	:
	_searchNameOnly(false)
	,_searchFullname(true)
	,_ignoreFolderItem(true)
	,_matchCase(false)
	,_matchWholeWord(false)
	,_useRegularExpression(false)

	,_outputToMessage(true)
	,_outputDisplayNameOnly(false)
{
}


ModelSearchEngine::~ModelSearchEngine(void)
{
}

void ModelSearchEngine::setKeyname( const QString& name )
{
	_keyword=name;
	if(_keywordHistory.indexOf(name)==-1)
		_keywordHistory.push_back(name);
}

void ModelSearchEngine::updateItemList(BaseItemList& itemlist)
{
	BaseItem* rootItem=myDocument()->getActiveItem();

	if(filter(rootItem))
		itemlist.push_back(rootItem);

	int n=rootItem->count();
	for(int i=0;i<n;++i)
		updateItemList(itemlist,rootItem->child(i));
}

void ModelSearchEngine::updateItemList(BaseItemList& itemlist,BaseItem* item )
{
	if(item->isPartOrAssembly())
		return;

	if(filter(item))
		itemlist.push_back(item);

	int n=item->count();
	for(int i=0;i<n;++i)
		updateItemList(itemlist,item->child(i));
}

QList<BaseItem*> ModelSearchEngine::compute()
{
	BaseItemList baseItemList;
	updateItemList(baseItemList);
	return baseItemList;
}

bool ModelSearchEngine::filter( BaseItem* item )
{
	if(_ignoreFolderItem && item->getCategory()==TDY_PRE_CATE_FOLDER)
		return false;

	if(_keyword.isEmpty())
		return true;

	QString name=item->getFullName();
	if(_matchCase){
		if(name.indexOf(_keyword,0,Qt::CaseSensitive)!=-1)
			return true;
	}
	else{
		if(name.indexOf(_keyword,0,Qt::CaseInsensitive)!=-1)
			return true;
	}

	return false;
}

