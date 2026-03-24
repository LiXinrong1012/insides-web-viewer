#include "expressinputdialog.h"
#include "ui_expressinputdialog.h"
#include <QMenu>
#include <QMessageBox>

ExpressInputDialog::ExpressInputDialog(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::ExpressInputDialog();
	ui->setupUi(this);
	m_nCombolistIndex = 0;

	InitData();
	for(int j =0; j< comboList.at(0).size() ;j++)
	{
		QListWidgetItem *newItem = new QListWidgetItem;
		newItem->setText(comboList.at(0).at(j).keyname);
		ui->listSymbols->insertItem(j, newItem);
	}
}
ExpressInputDialog::ExpressInputDialog(TDYParameterItem item)
	: QDialog()
{
	ui = new Ui::ExpressInputDialog();
	ui->setupUi(this);

	ui->lineName->setText(item.keyname);
	ui->lineDescription->setText(item.description);
	ui->txtExpression->setText(item.strPara);

	InitData();
	
}
ExpressInputDialog::~ExpressInputDialog()
{
	delete ui;
}


TDYParameterItem* ExpressInputDialog::getInputItem()
{
	if(ui->lineName->isModified() || ui->lineDescription->isModified()
		|| ui->txtExpression->isModified())
	{
		QString name = ui->lineName->text();
		QString des = ui->lineDescription->text();
		QString desp = ui->txtExpression->text();
		TDYParameterItem *item = new TDYParameterItem;
		item->keyname = name;
		item->description = des;
		item->strPara = desp;
		return item;	
	}
	return NULL;
}


void ExpressInputDialog::onShowList(int i)
{
	m_nCombolistIndex = i;
	ui->listSymbols->clear();
	if( i < comboList.size())
	{
		for(int j =0; j< comboList.at(i).size() ;j++)
		{
			QListWidgetItem *newItem = new QListWidgetItem;
			newItem->setText(comboList.at(i).at(j).keyname);
			ui->listSymbols->insertItem(j, newItem);
		}
	}
	
}

void ExpressInputDialog::onHelpShow(QListWidgetItem* item)
{
	QString showText("%1%2%3");
	int row = ui->listSymbols->currentRow();
	QString txt = comboList.at(m_nCombolistIndex).at(row).strPara;
	QString ld = ui->lineDescription->text();
	QString text =showText.arg(txt).arg(":").arg(ld);
	ui->labelHelp->setText(text);
}

void ExpressInputDialog::onAddTxtToEnd(QListWidgetItem* item)
{

	ui->txtExpression->insert(item->text());
}

void ExpressInputDialog::InitData()
{
	QList<TDYParameterItem> mathfunList;
	QList<TDYParameterItem> constantsList;
	QList<TDYParameterItem> modelfunList;
	QList<TDYParameterItem> defparaList;

	TDYParameterItem item;
	item.keyname = "e";
	item.strPara = "e";
	item.description = "自然对数";
	constantsList.append(item);

	item.keyname = "PI";
	item.strPara = "PI";
	item.description = "圆周率";
	constantsList.append(item);

	item.keyname = "sin";
	item.strPara = "sin(real)";
	item.description = "正弦函数";
	mathfunList.append(item);

	item.keyname = "cos";
	item.strPara = "cos(real)";
	item.description = "余弦函数";
	mathfunList.append(item);

	item.keyname = "tan";
	item.strPara = "tan(real)";
	item.description = "正切函数";
	mathfunList.append(item);

	item.keyname = "modelfun1";
	item.strPara = "modelfun1(int x)";
	item.description = "模板函数1";
	modelfunList.append(item);

	item.keyname = "modelfun2";
	item.strPara = "modelfun2(double x)";
	item.description = "模板函数2";
	modelfunList.append(item);

	item.keyname = "modelfun3";
	item.strPara = "modelfun3(float x)";
	item.description = "模板函数3";
	modelfunList.append(item);

	item.keyname = "defineparaAA";
	item.strPara = "defineparaAA(string strAA)";
	item.description = "默认参数AA";
	defparaList.append(item);

	item.keyname = "defineparaBB";
	item.strPara = "defineparaBB(string strBB)";
	item.description = "默认参数BB";
	defparaList.append(item);

	item.keyname = "defineparaCC";
	item.strPara = "defineparaCC(string strCC)";
	item.description = "默认参数CC";
	defparaList.append(item);

	comboList.append(mathfunList);
	comboList.append(constantsList);
	comboList.append(modelfunList);
	comboList.append(defparaList);
}
void ExpressInputDialog::onShowMenu()
{

	QMenu *menu = new QMenu();
	QAction *smarkerAction = menu->addAction("select marker");
	QAction *srigidAction = menu->addAction("select rigid");
	QAction *sjointAction = menu->addAction("select joint");

	connect(smarkerAction,SIGNAL(triggered(bool)),this,SLOT(smarkerAct()));
	connect(srigidAction,SIGNAL(triggered(bool)),this,SLOT(srigidAct()));
	connect(sjointAction,SIGNAL(triggered(bool)),this,SLOT(sjointAct()));

	menu->exec(QCursor::pos());
	delete menu;
}

void ExpressInputDialog::smarkerAct()
{
	ui->txtExpression->insert("marker");
}
void ExpressInputDialog::srigidAct()
{
	ui->txtExpression->insert("rigid");
}
void ExpressInputDialog::sjointAct()
{
	ui->txtExpression->insert("joint");
}

void ExpressInputDialog::onOK()
{
	if(ui->lineName->text() == "" || ui->lineDescription->text() == "")
	{
		QMessageBox::warning(this, tr("Warning"),
                                tr("The 'Name' or 'Expression' empty."),
                                QMessageBox::Ok,
                                QMessageBox::Ok);
	}
	else
		this->accept();
}