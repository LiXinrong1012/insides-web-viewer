#ifndef MODELSEARCHTOOLBAR_H
#define MODELSEARCHTOOLBAR_H

#include <QWidget>
#include "imodelsearchtoolbar.h"
namespace Ui {
	class ModelSearchToolbar;
};
namespace INSIDES{
	class BaseItem;
}
class ModelTreeSearchOptionsWidget;
using INSIDES::BaseItem;

enum searchItemType{ALL_TYPES=0,RIGID_BODY,MARKER};
class ModelSearchToolbar : public IModelSearchToolbar
{
	Q_OBJECT

public:
	ModelSearchToolbar(QWidget *parent = 0);
	~ModelSearchToolbar();

	typedef QList<BaseItem*> BaseItemList;
	
	void searchInResult();
	void removeFromResut();
	void joinResult();

	void setKeyname(const QString& name);
	QString getkeyname()const{return _keyword;}

	QStringList& getKeyWordHistory(){return _keywordHistory;}
	void clearKeyWordHistory();

	void setSearchItemType(searchItemType type){_searchType = type;}
	int getSearchItemType(){return _searchType;}

	void setSearchNameOnly(bool b){_searchNameOnly=b;}
	bool getSearchNameOnly()const{return _searchNameOnly;}

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

public slots:
	void compute();

protected:
	void keyPressEvent(QKeyEvent *e);

private:
	Ui::ModelSearchToolbar *ui;
	ModelTreeSearchOptionsWidget* _searchWidget;


	QString _keyword;
	QStringList _keywordHistory;

	searchItemType _searchType;

	bool	_searchNameOnly;
	bool	_ignoreFolderItem;
	bool	_matchCase;
	bool	_matchWholeWord;
	bool	_useRegularExpression;

	bool	_outputToMessage;
	bool	_outputDisplayNameOnly;
	
	BaseItemList	_resultItemList;
private:
	bool filter(BaseItem* item);
	void updateItemList(BaseItemList& itemlist);
	void updateItemList(BaseItemList& itemlist,BaseItem* item );

	void saveKeywordHistory();
	void loadKeywordHistory();
	void saveSetting();
	void loadSetting();
};

#endif // MODELSEARCHTOOLBAR_H
