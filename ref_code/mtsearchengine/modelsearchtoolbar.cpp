#include "modelsearchtoolbar.h"
#include "ui_modelsearchtoolbar.h"
#include "precore/BaseItem.h"
#include "precore/precore_data.h"
#include "precore/ModelDocument.h"
#include "modeltreesearchoptionswidget.h"


#include "base/Console.h"

#include <QMessageBox>
#include <QKeyEvent>
#include <QSettings>

ModelSearchToolbar::ModelSearchToolbar(QWidget *parent)
	: IModelSearchToolbar(parent)
	/*,_searchNameOnly(false)
	,_ignoreFolderItem(true)
	,_matchCase(false)
	,_matchWholeWord(false)
	,_useRegularExpression(false)
	,_searchType(ALL_TYPES)
	,_outputToMessage(false)
	,_outputDisplayNameOnly(false)*/
{
	ui = new Ui::ModelSearchToolbar();
	ui->setupUi(this);
	ui->toolButton->setIcon(QIcon(":/resources/menu/a011x16x16.png"));
	
	loadKeywordHistory();
	loadSetting();
	_searchWidget = new ModelTreeSearchOptionsWidget(this);

	connect(ui->toolButton,SIGNAL(clicked()),_searchWidget,SLOT(showWidget()));
	connect(ui->comboBox,SIGNAL(active()),this,SLOT(compute()));
}

ModelSearchToolbar::~ModelSearchToolbar()
{
	saveSetting();
	delete ui;
}

void ModelSearchToolbar::keyPressEvent( QKeyEvent *e )
{
	if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		if(!ui->comboBox->currentText().isEmpty())
		{
			setKeyname(ui->comboBox->currentText());
			compute();
		}
	}
}
void ModelSearchToolbar::setKeyname( const QString& name )
{
	_keyword=name;
	if(!_keywordHistory.contains(_keyword,Qt::CaseSensitive) && !_keyword.isEmpty())
	{
		_keywordHistory.push_front(name);
		ui->comboBox->clear();
		ui->comboBox->addItems(_keywordHistory);
		saveKeywordHistory();
	}
}

void ModelSearchToolbar::updateItemList(BaseItemList& itemlist)
{
	BaseItem* rootItem=INSIDES::myDocument()->getActiveItem();

	if(filter(rootItem))
		itemlist.push_back(rootItem);

	int n=rootItem->count();
	for(int i=0;i<n;++i)
		updateItemList(itemlist,rootItem->child(i));
}

void ModelSearchToolbar::updateItemList(BaseItemList& itemlist,BaseItem* item )
{
	if(item->isPartOrAssembly())
		return;

	if(filter(item))
		itemlist.push_back(item);

	int n=item->count();
	for(int i=0;i<n;++i)
		updateItemList(itemlist,item->child(i));
}

void ModelSearchToolbar::compute()
{
	BaseItemList baseItemList; 
	updateItemList(baseItemList);
	_resultItemList = baseItemList;
	emit reqUpdate(baseItemList);
	
}

void ModelSearchToolbar::searchInResult()
{
	BaseItemList tmpItemList;
	updateItemList(tmpItemList);
	BaseItemList tmpList;
	foreach(BaseItem* tmp,tmpItemList)
	{
		if(_resultItemList.contains(tmp))
			tmpList.push_back(tmp);
	}
	_resultItemList = tmpList;
	emit reqUpdate(tmpList);
}

void ModelSearchToolbar::removeFromResut()
{
	BaseItemList tmpItemList;
	updateItemList(tmpItemList);
	foreach(BaseItem* tmp,tmpItemList)
	{
		if(_resultItemList.contains(tmp))
			_resultItemList.removeOne(tmp);
	}
	emit reqUpdate(_resultItemList);
}

void ModelSearchToolbar::joinResult()
{
	BaseItemList tmpItemList;
	updateItemList(tmpItemList);
	foreach(BaseItem* tmp,tmpItemList)
	{
		if(!_resultItemList.contains(tmp))
			_resultItemList.push_back(tmp);
	}
	emit reqUpdate(_resultItemList);
}

bool ModelSearchToolbar::filter( BaseItem* item )
{
	if(_ignoreFolderItem && item->getCategory()==TDY_PRE_CATE_FOLDER)
		return false;

	if(_searchType == 1)
		if(item->getCategory() != TDY_PRE_CATE_RIGIDPART)
			return false;

	if(_searchType == 2)
		if(item->getCategory() != TDY_PRE_CATE_MARKER)
			return false;

	if(_keyword.isEmpty())
		return true;

	QList<bool> bList;

	QString name;
	if(_searchNameOnly)
		name = item->getKeyName();
	else
		name = item->getFullName();

	if(_useRegularExpression)
	if(name.contains(QRegExp(_keyword)))
	return true;

	if(_matchCase)
	{
		if(name.contains(_keyword,Qt::CaseSensitive))
			bList.push_back(true);
		else
			bList.push_back(false);
	}
	else
	{
		if(name.contains(_keyword,Qt::CaseInsensitive))
			bList.push_back(true);
		else
			bList.push_back(false);
	}

	if(_matchWholeWord)
	{
		if(!name.compare(_keyword,Qt::CaseInsensitive))
			bList.push_back(true);
		else
			bList.push_back(false);
	}

	if(bList.contains(false))
		return false;

	return true;
}

void ModelSearchToolbar::saveKeywordHistory()
{
	QString dir = QCoreApplication::applicationDirPath()+"/settings/";
	QSettings settings(dir +"insides-viewer.ini", QSettings::IniFormat);

	settings.beginGroup("MODEL_SEARCH_HISTORY");
	settings.setValue("key_words", this->_keywordHistory);

	settings.endGroup();
}

void ModelSearchToolbar::loadKeywordHistory()
{
	QString dir = QCoreApplication::applicationDirPath()+"/settings/";
	QSettings settings(dir +"insides-viewer.ini", QSettings::IniFormat);

	settings.beginGroup("MODEL_SEARCH_HISTORY");
	this->_keywordHistory = settings.value("key_words").toStringList();
	ui->comboBox->clear();
	ui->comboBox->addItems(_keywordHistory);

	settings.endGroup();
}

void ModelSearchToolbar::saveSetting()
{
	QString dir = QCoreApplication::applicationDirPath()+"/settings/";
	QSettings settings(dir +"insides-viewer.ini", QSettings::IniFormat);

	settings.beginGroup("MODEL_SEARCH_SETTING");

	settings.setValue("search_type",this->_searchType);
	settings.setValue("search_name_only",this->_searchNameOnly);
	settings.setValue("ignore_folder",this->_ignoreFolderItem);
	settings.setValue("match_case",this->_matchCase);
	settings.setValue("match_whole_word",this->_matchWholeWord);
	settings.setValue("use_regular_expression",this->_useRegularExpression);
	settings.setValue("output_to_message",this->_outputToMessage);
	settings.setValue("output_displayname_only",this->_outputDisplayNameOnly);

	settings.endGroup();
}

void ModelSearchToolbar::loadSetting()
{
	QString dir = QCoreApplication::applicationDirPath()+"/settings/";
	QSettings settings(dir +"insides-viewer.ini", QSettings::IniFormat);

	settings.beginGroup("MODEL_SEARCH_SETTING");

	this->_searchType = (searchItemType)settings.value("search_type",0).toInt();
	this->_searchNameOnly = settings.value("search_name_only",0).toBool();
	this->_ignoreFolderItem = settings.value("ignore_folder",1).toBool();
	this->_matchCase = settings.value("match_case",0).toBool();
	this->_matchWholeWord = settings.value("match_whole_word",0).toBool();
	this->_useRegularExpression = settings.value("use_regular_expression",0).toBool();
	this->_outputToMessage = settings.value("output_to_message",0).toBool();
	this->_outputDisplayNameOnly = settings.value("output_displayname_only",0).toBool();

	settings.endGroup();
}

void ModelSearchToolbar::clearKeyWordHistory()
{
	ui->comboBox->clear();
	_keywordHistory.clear();
	saveKeywordHistory();
}
