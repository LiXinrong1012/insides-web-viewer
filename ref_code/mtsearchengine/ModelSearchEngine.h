#pragma once

#include <QString>
#include <QList>

namespace INSIDES
{
	class BaseItem;
}
using namespace INSIDES;

/*!
*	This is a engine for model search.
*	@author	Jerry He
*	@date	2014.7.16
*/

class ModelSearchEngine
{
public:
	ModelSearchEngine(void);
	~ModelSearchEngine(void);

	typedef QList<BaseItem*> BaseItemList;
	BaseItemList compute();

	void setKeyname(const QString& name);
	QString getkeyname()const{return _keyword;}

	void setSearchNameOnly(bool b){_searchNameOnly=b;}
	bool getSearchNameOnly()const{return _searchNameOnly;}

	void setSearchFullName(bool b){_searchFullname=b;}
	bool getSearchFullName()const{return _searchFullname;}

	void setIgnoreFolderItem(bool b){_ignoreFolderItem=b;}
	bool getIgnoreFolderItem()const{return _ignoreFolderItem;}

	void setMatchCase(bool b){_matchCase=b;}
	bool getMatchCase()const{return _matchCase;}

	void setMatchWholeWord(bool b){_matchWholeWord=b;}
	bool getMatchWholeWord()const{return _matchWholeWord;}

	void setUseRegularExpression(bool b){_useRegularExpression=b;}
	bool getUseRegularExpression()const{return _useRegularExpression;}

	void setOutputToMessage(bool b){_outputToMessage=b;}
	bool getOutputToMessage()const{return _outputToMessage;}

	void setOutputDisplayNameOnly(bool b){_outputDisplayNameOnly=b;}
	bool getOutputDisplayNameOnly()const{return _outputDisplayNameOnly;}

private:
	QString _keyword;
	QList<QString> _keywordHistory;

	bool	_searchNameOnly;
	bool	_searchFullname;
	bool	_ignoreFolderItem;
	bool	_matchCase;
	bool	_matchWholeWord;
	bool	_useRegularExpression;

	bool	_outputToMessage;
	bool	_outputDisplayNameOnly;

	bool filter(BaseItem* item);
	void updateItemList(BaseItemList& itemlist);
	void updateItemList(BaseItemList& itemlist,BaseItem* item );
};
