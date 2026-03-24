#include "parameteranalysisdialog.h"
#include "edcore/project.h"
#include "edcore/document.h"
#include "edcore/solution.h"

#include "edcompile/modelparser.h"
#include "edcompile/tdytypeinfomanager.h"
#include "edcompile/insmodelformator.h"
#include "edcompile/mainitem.h"

#include "ui_parameteranalysisdialog.h"

#include <QCheckBox>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QMouseEvent>
#include <QDoubleSpinBox>
#include <QDir>

using namespace INSEditor::Parse;


///代表一个parameter的一种值的可能
class PItem
{
public:
	PItem(const QString& p,double va)
		:parameter(p)
		,value(va)
	{
	}

	///标识
	QString		 parameter;

	///值
	double		 value;
};

///每个parameter取一个值，组成的一种可能
typedef QList<PItem> PItemGroup;

///存储一行的数据
class PTItem
{
public:
	///标识
	QString parameter;

	///当前
	QString current;

	///开始值
	double begin;

	///结束值
	double stop;

	///步长
	double step;

	///所有可能的值
	QList<double> values;
};

///存储所有行的数据
typedef QList<PTItem> PTItemGroup;

void _getAllItemGroup(const PTItemGroup& group, PItemGroup& currentItemGroup,int index, QList<PItemGroup>& outList )
{
	if (index>=group.size()){
		outList.push_back(currentItemGroup);
		return;
	}

	const PTItem& currentPTItem=group[index];
	foreach(double va,currentPTItem.values)
	{
		currentItemGroup.push_back(PItem(currentPTItem.parameter,va));
		_getAllItemGroup(group,currentItemGroup,index+1,outList);
		currentItemGroup.pop_back();
	}
}

void _getAllItemGroup(const PTItemGroup& group,QList<PItemGroup>& outList)
{
	if(group.size()==0)
		return;
	PItemGroup currentItemGroup;
	_getAllItemGroup(group,currentItemGroup,0,outList);
}

//////////////////////////////////////////////////////////////////////

ParameterAnalysisDialog::ParameterAnalysisDialog(INSEditor::Project* pro,QWidget *parent)
	: QDialog(parent)
	,_project(pro)
{
	ui = new Ui::ParameterAnalysisDialog();
	ui->setupUi(this);

	ui->tableWidget->verticalHeader()->setHidden(true);

	initParameter();

	connect(ui->tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(onItemChanged(QTableWidgetItem*)));
	connect(ui->tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(onItemDoubleClicked(QTableWidgetItem*)));
	connect(ui->cancelBtn,SIGNAL(clicked()),this,SLOT(close()));
	connect(ui->duplicateBtn,SIGNAL(clicked()),this,SLOT(onDuplicateBtnClicked()));
}

ParameterAnalysisDialog::~ParameterAnalysisDialog()
{
	delete ui;
}

void ParameterAnalysisDialog::initParameter()
{
	INSEditor::Parse::ModelParser parser;
	QString fileName = _project->getStartupEntity()->getFullFileName();
	if(fileName.isEmpty())
		return;

	_assmblyItem=parser.parse(fileName);
	INSEditor::Parse::TDYTypeInfoManager typeManager;
	typeManager.loadFromTDYTemplate(qApp->applicationDirPath()+"/settings/ins.xml");
	parser.compileAssemblyItem(_assmblyItem,typeManager.getAllInfos());

	handleLineItem(_assmblyItem);
	ui->tableWidget->resizeColumnToContents(1);
}

void ParameterAnalysisDialog::handleLineItem( INSEditor::Parse::LineItem* item )
{
	if(item->type== ASSEMBLYITEM)
	{
		INSEditor::Parse::AssemblyItem* assItem = (INSEditor::Parse::AssemblyItem*)item;
		QList<INSEditor::Parse::LineItem*>itemList = assItem->getItemList();
		foreach(INSEditor::Parse::LineItem* tmp,itemList)
			handleLineItem(tmp);
	}
	else if(item->type == LINEITEM)
	{
		if(!item->keyname.compare("parameter",Qt::CaseInsensitive))
			addItem(item);
	}
}

void ParameterAnalysisDialog::addItem( INSEditor::Parse::LineItem* item )
{
	foreach (BaseItem* baseItem,item->allItems)
	{
		if(baseItem->type == KEYVALUEITEM)
		{
			KeyValueItem* keyValue = (KeyValueItem*)baseItem;

			int row = ui->tableWidget->rowCount();
			ui->tableWidget->insertRow(row);

			QStringList dList;
			INSEditor::Parse::LineItem* tmp = item->parent;
			while(tmp)
			{
				if(tmp->mainLabel.isEmpty())
					break;

				dList.push_front(tmp->mainLabel);
				tmp = tmp->parent;
			}
			QString tmpStr = dList.join(".") + ".";
			if(!tmpStr.compare("."))
				tmpStr.clear();

			QCheckBox* validBox = new QCheckBox;
			ui->tableWidget->setCellWidget(row,0,validBox);
			connect(validBox,SIGNAL(stateChanged ( int )),this,SLOT(onCheckBoxStateChanged ( int)));

			QLabel* parameterLabel = new QLabel(tmpStr+keyValue->keyname);
			ui->tableWidget->setCellWidget(row,1,parameterLabel);

			if(keyValue->valueList.count()>1)
				continue;

			QLabel* currLabel = new QLabel(keyValue->valueList[0]);
			ui->tableWidget->setCellWidget(row,2,currLabel);

			QTableWidgetItem* beginItem = new QTableWidgetItem;
			beginItem->setData(Qt::DisplayRole,keyValue->valueList[0].toDouble());
			beginItem->setData(Qt::UserRole,quintptr(keyValue));
			ui->tableWidget->setItem(row,3,beginItem);

			QTableWidgetItem* endItem = new QTableWidgetItem;
			endItem->setData(Qt::DisplayRole,keyValue->valueList[0].toDouble());
			ui->tableWidget->setItem(row,4,endItem);

			QTableWidgetItem* speedItem = new QTableWidgetItem;
			speedItem->setData(Qt::DisplayRole,1.0);
			ui->tableWidget->setItem(row,5,speedItem);

			QLabel* countLabel = new QLabel("1");
			ui->tableWidget->setCellWidget(row,6,countLabel);
		}
	}
}

void ParameterAnalysisDialog::onItemChanged( QTableWidgetItem* item )
{
	int row = item->row();
	int col = item->column();

	QLabel* currLabel = (QLabel*)ui->tableWidget->cellWidget(row,2);
	double currNum = currLabel->text().toDouble();

	double beginNum = ui->tableWidget->item(row,3)->data(Qt::DisplayRole).toDouble();
	double endNum = ui->tableWidget->item(row,4)->data(Qt::DisplayRole).toDouble();
	double speedNum = ui->tableWidget->item(row,5)->data(Qt::DisplayRole).toDouble();

	//开始值不可以大于结束值
	if(beginNum > endNum)
	{
		QMessageBox::warning(this,tr("Warning"),tr("The begin number can't greater than end number !"));
		if(col == 3)
			item->setData(Qt::DisplayRole,endNum);
		if(col == 4)
			item->setData(Qt::DisplayRole,beginNum);

		return;
	}

	if((speedNum<=0 ) && col == 5)
	{
		QMessageBox::warning(this,tr("Warning"),tr("The step can't equal to or less than 0"));
		item->setData(Qt::DisplayRole,1.0);
		return ;
	}

	int countNum = ((endNum - beginNum)/speedNum) +1;

	QLabel* countLabel = (QLabel*) ui->tableWidget->cellWidget(row,6);
	countLabel->setText(QString::number(countNum));

	if(countNum>1)
	{
		QCheckBox* vaildBox = (QCheckBox*)ui->tableWidget->cellWidget(row,0);
		vaildBox->setChecked(true);
	}

	int num =1;
	for (int i=0;i<ui->tableWidget->rowCount();i++)
	{
		QLabel* tmpLabel = (QLabel*)ui->tableWidget->cellWidget(i,6);
		int tmp = tmpLabel->text().toInt();
		num = tmp * num;
	}
	
	ui->countValueLabel->setText("<b>"+QString::number(num)+"</b>");
}

void ParameterAnalysisDialog::onDuplicateBtnClicked()
{
	//将每一行的数据存在里面
	PTItemGroup tItemGroup;
	QStringList changeParamerList;

	for (int i=0;i<ui->tableWidget->rowCount();i++)
	{
		PTItem tItem;
		
		QLabel* parameterLabel = (QLabel*)ui->tableWidget->cellWidget(i,1);
		tItem.parameter = parameterLabel->text();

		QCheckBox* vaildBox = (QCheckBox*)ui->tableWidget->cellWidget(i,0);
		if(vaildBox->isChecked())
			changeParamerList<<tItem.parameter;

		QLabel* currLabel = (QLabel*)ui->tableWidget->cellWidget(i,2);
		tItem.current = currLabel->text();

		double beginNum = ui->tableWidget->item(i,3)->data(Qt::DisplayRole).toDouble();
		tItem.begin = beginNum;

		double stopNum = ui->tableWidget->item(i,4)->data(Qt::DisplayRole).toDouble();
		tItem.stop = stopNum;

		double stepNum = ui->tableWidget->item(i,5)->data(Qt::DisplayRole).toDouble();
		tItem.step = stepNum;

		QLabel* countLabel = (QLabel*) ui->tableWidget->cellWidget(i,6);
		double countNum = countLabel->text().toDouble();		

		if(vaildBox->isChecked())
		{
			for (int j=0;j<countNum;j++)
				tItem.values.push_back(beginNum + j*stepNum);
		}
		else
			tItem.values.push_back(currLabel->text().toDouble());
		
		tItemGroup.push_back(tItem);
	}

	//得到所有可能的情况
	QList<PItemGroup> list;
	_getAllItemGroup(tItemGroup,list);

	if(list.isEmpty())
		return;

	if(changeParamerList.isEmpty())
	{
		QMessageBox::warning(this,"Warning","Select one parameter at least.");
		return ;
	}

	QString prefix = QInputDialog::getText(this,tr("Project Prefix"),tr("Please input project prefix:"));
	QString suffixal = QInputDialog::getText(this,tr("Project Suffix"),tr("Please input project Suffix:"));

	//所有keyValueItem对象 
	QList<INSEditor::Parse::KeyValueItem*> keyValueItemList;

	//存下所有的工程名和更新过的内容
	QStringList projectNameList;
	QStringList contentsList;

	QString solDir = INSEditor::Document::instance()->getSolution()->getSolutionDirectory();
	INSEditor::Parse::INSModelFormator formator;

	for(int i=0;i<ui->tableWidget->rowCount();i++)
	{
		INSEditor::Parse::KeyValueItem* item = (INSEditor::Parse::KeyValueItem*)ui->tableWidget->item(i,3)->data(Qt::UserRole).toULongLong();
		keyValueItemList.push_back(item);
	}
	
	//生成所有新文件名，同时检测是否有不可用的
	foreach(PItemGroup group,list)
	{
		QString tmp ;
		for (int i=0;i<group.count();i++)
		{
			if(!changeParamerList.contains(group[i].parameter,Qt::CaseInsensitive))
				continue;

			double d = group[i].value;
			keyValueItemList[i]->valueList[0] = QString::number(d);

			tmp+=group[i].parameter;
			tmp+="-";
			tmp+=QString::number(group[i].value);
		}
		if(!prefix.isEmpty())
			tmp = prefix+"_"+tmp;
		if(!suffixal.isEmpty())
			tmp = tmp + "_" + suffixal;

		QString newProName = solDir + tmp;

		QDir dir(newProName);
		if(dir.exists())
		{
			QMessageBox::warning(this,tr("Warning"),tr("This project %1 has been exists,so can't build").arg(newProName));
			return;
		}
		else
			projectNameList<<tmp;
		QString str = formator.toString(_assmblyItem);
		contentsList<<str;
	}

	for(int i=0;i<projectNameList.count();i++)
	{
		emit createProject(projectNameList[i],contentsList[i]);

		QDir proDir(_project->getDirectory());
		QStringList list = proDir.entryList(QDir::Files);

		///建立副本的文件夹并拷贝文件
		QString newDir = solDir + projectNameList[i]+"/";

		QStringList projectEntityList;
		for (int i=0;i<_project->getEntities().count();i++)
		{
			QString s = _project->getEntities()[i]->getName();
			projectEntityList.push_back(s);
		}
		for (int i=0;i<list.count();i++)
		{
			QFileInfo info(list[i]);
			QString ext = info.suffix();
			if (!ext.compare("ins") || !ext.compare("tdy") || !ext.compare("inspro") || !ext.compare("insln"))
				continue;
			
			if(projectEntityList.contains(list[i]))
				QFile::copy(_project->getDirectory()+list[i],newDir+list[i]);
		}
	}

	this->close();
}

void ParameterAnalysisDialog::onCheckBoxStateChanged( int state)
{
	int num = 1;

	for (int i=0;i<ui->tableWidget->rowCount();i++)
	{
		QCheckBox* validBox = (QCheckBox*)ui->tableWidget->cellWidget(i,0);
		if(validBox->isChecked())
		{
			QLabel* label = (QLabel*)ui->tableWidget->cellWidget(i,6);
			int tmp = label->text().toInt();
			num = num * tmp;
		}
	}

	ui->countValueLabel->setText(tr("<b>%1</b>").arg(num));
}

void ParameterAnalysisDialog::onItemDoubleClicked( QTableWidgetItem* item )
{
	_clickedRow = item->row();
	_clickedColumn = item->column();
	QDoubleSpinBox* dsBox = new QDoubleSpinBox();
	dsBox->setDecimals(3);
	dsBox->setMaximum(99999999);
	dsBox->setValue(item->data(Qt::DisplayRole).toDouble());
	ui->tableWidget->setCellWidget(_clickedRow,_clickedColumn,dsBox);

	connect(dsBox,SIGNAL(	editingFinished()),this,SLOT(onEditingFinished()));
}

void ParameterAnalysisDialog::onEditingFinished()
{
	QDoubleSpinBox* dsBox = (QDoubleSpinBox*)sender();
	ui->tableWidget->item(_clickedRow,_clickedColumn)->setData(Qt::DisplayRole,dsBox->value());
	dsBox->hide();
}


