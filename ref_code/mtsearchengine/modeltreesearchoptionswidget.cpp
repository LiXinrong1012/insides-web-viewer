#include "modeltreesearchoptionswidget.h"
#include "ui_modeltreesearchoptionswidget.h"
#include "modelsearchtoolbar.h"

#include "mtsearchengineimp.h"
#include <QComboBox>
#include <QMessageBox>
#include <QSettings>


ModelTreeSearchOptionsWidget::ModelTreeSearchOptionsWidget(QWidget *parent)
	: QDialog(parent)
	,initing(false)
{
	ui = new Ui::ModelTreeSearchOptionsWidget();
	ui->setupUi(this);

	ui->clearHistorButton->setIcon(QIcon(":/resources/menu/a015x16x16.png"));
	ui->searchInResultButton->setIcon(QIcon(":/resources/menu/a011x16x16.png"));
	ui->removeFromResultButton->setIcon(QIcon(":/resources/menu/a011x16x16.png"));
	ui->joinResultButton->setIcon(QIcon(":/resources/menu/a011x16x16.png"));

	this->setGeometry(400,600,this->geometry().width(),this->geometry().height());


	_searchBar = static_cast<ModelSearchToolbar*>(parent);
	ui->cbInput->setAutoCompletionCaseSensitivity(Qt::CaseSensitive);
	//connect(ui->cbInput,SIGNAL(activated(int)),
	//	this,SLOT(startSearch()));

	connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(startSearch()));
	connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(startSearch()));

	connect(ui->clearHistorButton,SIGNAL(clicked()),this,SLOT(clearHistory()));
	connect(ui->searchInResultButton,SIGNAL(clicked()),this,SLOT(onSearchInResultButtonClicked()));
	connect(ui->removeFromResultButton,SIGNAL(clicked()),this,SLOT(onRemoveFromResultButtonClicked()));
	connect(ui->joinResultButton,SIGNAL(clicked()),this,SLOT(onJoinResultButtonClicked()));

	connect(ui->cbInput,SIGNAL(activated(int)),this,SLOT(onValueChanged()));
	connect(ui->cbTypes,SIGNAL(activated(int)),this,SLOT(onValueChanged()));
	connect(ui->bSearchNameOnly,SIGNAL(stateChanged(int)),this,SLOT(onValueChanged()));
	connect(ui->bIgnoreFolder,SIGNAL(stateChanged(int)),this,SLOT(onValueChanged()));
	connect(ui->bMatchCase,SIGNAL(stateChanged(int)),this,SLOT(onValueChanged()));
	connect(ui->bMatchWholeWord,SIGNAL(stateChanged(int)),this,SLOT(onValueChanged()));
	connect(ui->bUseRegularExpression,SIGNAL(stateChanged(int)),this,SLOT(onValueChanged()));
	connect(ui->bOutputToMessage,SIGNAL(stateChanged(int)),this,SLOT(onValueChanged()));
	connect(ui->bDisplayItemNameOnly,SIGNAL(stateChanged(int)),this,SLOT(onValueChanged()));

	connect(ui->cbRegExp,SIGNAL(activated(int)),this,SLOT(onRegExpActivated()));
	loadGeo();
}

ModelTreeSearchOptionsWidget::~ModelTreeSearchOptionsWidget()
{
	saveGeo();
	delete ui;
}

void ModelTreeSearchOptionsWidget::value2Control()
{
	ui->cbInput->setEditText(_searchBar->getkeyname());
	ui->bSearchNameOnly->setChecked(_searchBar->getSearchNameOnly());
	ui->bIgnoreFolder->setChecked(_searchBar->getIgnoreFolderItem());
	ui->cbTypes->setCurrentIndex(_searchBar->getSearchItemType());
	ui->bMatchCase->setChecked(_searchBar->getMatchCase());
	ui->bMatchWholeWord->setChecked(_searchBar->getMatchWholeWord());
	ui->bUseRegularExpression->setChecked(_searchBar->getUseRegularExpression());
	ui->bOutputToMessage->setChecked(_searchBar->getOutputToMessage());
	ui->bDisplayItemNameOnly->setChecked(_searchBar->getOutputDisplayNameOnly());

	updateInputHistory();
}

void ModelTreeSearchOptionsWidget::control2Value()
{
	_searchBar->setKeyname(ui->cbInput->currentText());
	_searchBar->setSearchItemType((searchItemType)ui->cbTypes->currentIndex());
	_searchBar->setSearchNameOnly(ui->bSearchNameOnly->isChecked());
	_searchBar->setIgnoreFolderItem(ui->bIgnoreFolder->isChecked());
	_searchBar->setMatchCase(ui->bMatchCase->isChecked());
	_searchBar->setMatchWholeWord(ui->bMatchWholeWord->isChecked());
	_searchBar->setUseRegularExpression(ui->bUseRegularExpression->isChecked());
	_searchBar->setOutputToMessage(ui->bOutputToMessage->isChecked());
	_searchBar->setOutputDisplayNameOnly(ui->bDisplayItemNameOnly->isChecked());
}

void ModelTreeSearchOptionsWidget::updateInputHistory()
{
	ui->cbInput->clear();
	ui->cbInput->addItems(_searchBar->getKeyWordHistory());
}

void ModelTreeSearchOptionsWidget::startSearch()
{
	control2Value();
	_searchBar->compute();
}

void ModelTreeSearchOptionsWidget::showWidget()
{
	initing = true;
	value2Control();
	initing = false;
	this->show();
}

void ModelTreeSearchOptionsWidget::onSearchInResultButtonClicked()
{
	control2Value();
	_searchBar->searchInResult();
}

void ModelTreeSearchOptionsWidget::onRemoveFromResultButtonClicked()
{
	control2Value();
	_searchBar->removeFromResut();
}

void ModelTreeSearchOptionsWidget::onJoinResultButtonClicked()
{
	control2Value();
	_searchBar->joinResult();
}

void ModelTreeSearchOptionsWidget::onValueChanged()
{
	if(!initing)
		control2Value();

	if(ui->bUseRegularExpression->isChecked())
		ui->cbRegExp->setEnabled(true);
	else
		ui->cbRegExp->setEnabled(false);
}

void ModelTreeSearchOptionsWidget::saveGeo()
{
	QString dir = QCoreApplication::applicationDirPath()+"/settings/";
	QSettings settings(dir +"insides-viewer.ini", QSettings::IniFormat);

	settings.beginGroup("MODEL_SEARCH_GEO");

	settings.setValue("geometry",this->geometry());

	settings.endGroup();
}

void ModelTreeSearchOptionsWidget::loadGeo()
{
	QString dir = QCoreApplication::applicationDirPath()+"/settings/";
	QSettings settings(dir +"insides-viewer.ini", QSettings::IniFormat);

	settings.beginGroup("MODEL_SEARCH_GEO");

	this->setGeometry(settings.value("geometry",QRect(400,600,280,300)).toRect());

	settings.endGroup();
}

void ModelTreeSearchOptionsWidget::onRegExpActivated()
{
	ui->cbInput->setEditText(ui->cbRegExp->currentText());
}

void ModelTreeSearchOptionsWidget::clearHistory()
{
	QMessageBox msgBox;
	msgBox.setText("Confirmed to remove all search history?");
	msgBox.setIcon(QMessageBox::Warning);

	QPushButton *clearBtn = msgBox.addButton(tr("Clear"), QMessageBox::ActionRole);
	QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

	msgBox.exec();

	if (msgBox.clickedButton() == clearBtn)
	{
		ui->cbInput->clear();
		_searchBar->clearKeyWordHistory();
	}
}
