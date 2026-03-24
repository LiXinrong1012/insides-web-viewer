#include "searchkeywidget.h"
#include "ui_searchkeywidget.h"

SearchKeyWidget::SearchKeyWidget(QWidget *parent)
	: ISearchReplaceDialog(parent)
{
	ui = new Ui::SearchKeyWidget();
	ui->setupUi(this);
	this->setWindowTitle("Search Or Replace");
	ui->searchContentComboBox->setFocus();
	ui->findPushBtn->setIcon(QIcon(":/resources/menu/font/f007.png"));
	ui->replacePushBtn->setIcon(QIcon(":/resources/menu/font/f009.png"));

	ui->searchNextPushButton->setShortcut( QKeySequence::InsertParagraphSeparator ); //设置快捷键为键盘的“回车”键
	ui->searchNextPushButton->setShortcut(Qt::Key_Enter); //设置快捷键为enter键
	ui->searchNextPushButton->setShortcut(Qt::Key_Return); //设置快捷键为小键盘上的enter键

	ui->searchLabel1->hide();
	ui->searchLabel2->hide();
	ui->replaceLabel->hide();
	ui->replaceComboBox->hide();
	ui->replaceRangeToolBtn->hide();
	ui->replacePushButton->hide();
	ui->replaceAllPushButton->hide();

	resize(0,0);
	
	_isUse = false;
	
	connect(ui->findPushBtn,SIGNAL(clicked()),this,SLOT(onFindBtnClicked()));
	connect(ui->replacePushBtn,SIGNAL(clicked()),this,SLOT(onReplaceBtnClicked()));

	connect(ui->searchNextPushButton,SIGNAL(clicked()),this,SLOT(onNextPushButtonClicked()));
	connect(ui->searchPreviousPushButton,SIGNAL(clicked()),this,SLOT(onPreviousPushButtonClicked()));
	connect(ui->searchAllPushButton,SIGNAL(clicked()),this,SLOT(onSearchAllPushButtonClicked()));
	connect(ui->searchUseCheckBox,SIGNAL(clicked()),this,SLOT(onSearchUseCheckBoxClicked()));
	connect(ui->searchOpenGroupToolBtn,SIGNAL(clicked()),this,SLOT(onSearchOpenGroupBtnClicked()));
	connect(ui->searchOpenGroupToolBtn2,SIGNAL(clicked()),this,SLOT(onSearchOpenGroupToolBtn2Clicked()));

	connect(ui->replaceAllPushButton,SIGNAL(clicked()),this,SLOT(onReplaceAllPushButtonClicked()));
	connect(ui->replacePushButton,SIGNAL(clicked()),this,SLOT(onReplacePushButtonClicked()));

	controls2Values();
}

SearchKeyWidget::~SearchKeyWidget()
{
}

//searchҳnext click
void SearchKeyWidget::onNextPushButtonClicked()
{
	insertSearchHistory(ui->searchContentComboBox->currentText());
	emit sigFindNext();
}

QString SearchKeyWidget::getSearchContent() const
{
	return ui->searchContentComboBox->currentText();
}

//Previous click
void SearchKeyWidget::onPreviousPushButtonClicked()
{
	emit sigFindPrevious();
}

void SearchKeyWidget::onSearchAllPushButtonClicked()
{
	emit sigFindAll();
}

void SearchKeyWidget::onReplacePushButtonClicked()
{
	emit sigReplace();
}

void SearchKeyWidget::onReplaceAllPushButtonClicked()
{
	emit sigReplaceAll();
}

QString SearchKeyWidget::getReplaceContent()const
{
	return  ui->replaceComboBox->currentText();
}

void SearchKeyWidget::onSearchUseCheckBoxClicked()
{
	if (ui->searchUseCheckBox->isChecked())
	{
		_isUse = true;
		ui->searchUseComboBox->setEnabled(true);
	}
	else
	{
		_isUse = false;
		ui->searchUseComboBox->setEnabled(false);
	}
}

void SearchKeyWidget::onSearchOpenGroupBtnClicked()
{
	if(ui->searchGroupBox2->isHidden())
	{
		ui->searchGroupBox2->show();
		ui->searchOpenGroupToolBtn->setText("-");
		ui->searchLabel1->hide();
	}
	else
	{
		ui->searchGroupBox2->hide();
		ui->searchOpenGroupToolBtn->setText("+");
		ui->searchLabel1->show();
	}
	updateWindow();
}

void SearchKeyWidget::updateWindow()
{
	resize(0,0);
}

void SearchKeyWidget::onSearchOpenGroupToolBtn2Clicked()
{
	if(ui->searchGroupBox3->isHidden())
	{
		ui->searchGroupBox3->show();
		ui->searchOpenGroupToolBtn2->setText("-");
		ui->searchLabel2->hide();
	}
	else
	{
		ui->searchGroupBox3->hide();
		ui->searchOpenGroupToolBtn2->setText("+");
		ui->searchLabel2->show();
	}
	updateWindow();
}

void SearchKeyWidget::setTypeFindOrReplace( bool showFind /*=True*/ )
{
	if (!showFind)
	{
		ui->replaceLabel->show();
		ui->replaceComboBox->show();
		ui->replaceRangeToolBtn->show();
		ui->replacePushButton->show();
		ui->replaceAllPushButton->show();

		ui->searchAllPushButton->hide();
		ui->searchPreviousPushButton->hide();

		ui->replacePushBtn->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(251,254,235, 255), stop:1 rgba(250,240,171, 255));min-width: 75px;min-height: 20px;border-style: outset;border-width: 1px;border-color: rgb(210, 189, 144);");
		ui->findPushBtn->setStyleSheet("border:NULL;min-width: 75px");
	}
	else//find
	{
		ui->replaceLabel->hide();
		ui->replaceComboBox->hide();
		ui->replaceRangeToolBtn->hide();
		ui->replacePushButton->hide();
		ui->replaceAllPushButton->hide();
		
		ui->searchPreviousPushButton->show();
		ui->searchAllPushButton->show();

		ui->findPushBtn->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(251,254,235, 255), stop:1 rgba(250,240,171, 255));min-width: 75px;min-height: 20px;border-style: outset;border-width: 1px;border-color: rgb(210, 189, 144);");
		ui->replacePushBtn->setStyleSheet("border:NULL;min-width: 75px");
	}
	ui->searchContentComboBox->setFocus();
}

void SearchKeyWidget::onFindBtnClicked()
{
	setTypeFindOrReplace(true);
}

void SearchKeyWidget::onReplaceBtnClicked()
{
	setTypeFindOrReplace(false);
}

void SearchKeyWidget::controls2Values()
{
	_isCaseSensitive=ui->searchMatchCaseCheckBox->isChecked();
	_isMatchWholeWords=ui->searchMatchWholeWordsCheckBox->isChecked();
	_isUse = ui->searchUseCheckBox->isChecked();
	if (ui->searchResultRadioButton1->isChecked())
		_isOpenResultOnPage1 = true;
	else
		_isOpenResultOnPage1 = false;

	_isShowOnlyFileName = ui->searchShowFileNameCheckBox->isChecked();
	_isKeepReplacedFileOpen = ui->searchAllOpenCheckBox->isChecked();

	int searchPlace=ui->searchRangeComboBox->currentIndex();
	if(searchPlace==0)
		_searchPlace=SearchInCurrentDocument;
	else if(searchPlace==1)
		_searchPlace=SearchAll;
	else
		_searchPlace=SearchInAllOpenDocuments;
}

void SearchKeyWidget::insertSearchHistory(QString str)
{
	int findRes = ui->searchContentComboBox->findText(str,Qt::MatchCaseSensitive);
	if (findRes == -1)
		ui->searchContentComboBox->addItem(str);
}
