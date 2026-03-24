#include "curveconfigdialog.h"
#include "ui_curveconfigdialog.h"

#include "customxyplot.h"
#include "CustomPlotViewSetting.h"
#include "CurvePlotSettingDialog.h"
#include "CurveSettingDialog.h"

#include "pubbase/mimedata.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QDir>
#include <QUuid>

using namespace INSIDES;

CurveConfigDialog::CurveConfigDialog(QCustomPlot* plot)
	: _customPlot(plot)
{
	ui = new Ui::CurveConfigDialog();
	ui->setupUi(this);

	QString testDir = qApp->applicationDirPath();
	QDir dir;
	dir.setCurrent(testDir);
	dir.mkdir("settings");
	_configDir = testDir + "/settings/";

	initTree();

	connect(ui->treeWidget,SIGNAL(	itemClicked ( QTreeWidgetItem * , int  )),this,SLOT(onItemClicked ( QTreeWidgetItem *, int)));
	connect(ui->treeWidget,SIGNAL(itemDoubleClicked( QTreeWidgetItem *, int )),this,SLOT(onTreeItemDoubleClicked(QTreeWidgetItem*,int)));
	connect(ui->delBtn,SIGNAL(clicked()),this,SLOT(deleteConfig()));
	connect(ui->renameBtn,SIGNAL(clicked()),this,SLOT(renameConfig()));
	connect(ui->upBtn,SIGNAL(clicked()),this,SLOT(upOrDownBtnClicked()));
	connect(ui->downBtn,SIGNAL(clicked()),this,SLOT(upOrDownBtnClicked()));
	connect(ui->exportBtn,SIGNAL(clicked()),this,SLOT(onExportBtnClicked()));
	connect(ui->importBtn,SIGNAL(clicked()),this,SLOT(onImportBtnClicked()));
}

CurveConfigDialog::~CurveConfigDialog()
{
	delete ui;
}

void CurveConfigDialog::saveConfig()
{
	//保存的是用户看到的名
	QString saveName = QInputDialog::getText(this,tr("New Appearance"),tr("Enter appearance name:"));
	if(saveName.isEmpty())
		return;

	if(!isLegal(saveName))
	{
		QMessageBox::warning(this,"Warning","The name is not legal !Please input again.");
		saveConfig();
		return;
	}

	MimeData testMimeData;
	testMimeData.load(_configDir + "prevtc.ini");
	QString id = QUuid::createUuid().toString();

	MimeData mimeData;
	mimeData.load(_configDir +"prevtc.ini");

	//一共有多少种配置
	if(mimeData.hasFormat("insviewer/prevtc/config/id"))
	{
		QSharedPointer<QDataStream> readStream = mimeData.startReadCustomData("insviewer/prevtc/config/id");

		QString idStr;
		*readStream>>idStr;
		if(!idStr.isEmpty())
		{
			QDataStream* writeStream = mimeData.startWriteCustomData("insviewer/prevtc/config/id");
			idStr+=",";
			QString idMap = id + "|" + saveName;
			idStr+=idMap;
			*writeStream<<idStr;
		}
	}
	else
	{
		QDataStream& writeStream = *mimeData.startWriteCustomData("insviewer/prevtc/config/id");
		QString idMap = id + "|" + saveName;
		writeStream<<idMap;
	}

	QDataStream* stream = mimeData.startWriteCustomData(QString("insviewer/prevtc/config/%1").arg(id));

	//保存图
	_customPlot->savePng(_configDir+id+".png",512,512);
	QPixmap p(_configDir+id+".png");
	*stream<<p;
	QFile::remove(_configDir+id+".png");

	CutsomPlotAxisSetting setting;
	Plot2Setting(_customPlot,setting);
	setting.save(*stream);

	mimeData.stopWriteAllCustomData();
	mimeData.save(_configDir + "prevtc.ini");
	
	this->close();
}

void CurveConfigDialog::openConfig()
{
	QAction* ac = (QAction*)sender();
	if(!ac)
		return;

	MimeData mimeData;
	mimeData.load(_configDir+"prevtc.ini");

	QString id = ac->data().toString();
	if(id.isEmpty())
		id = ui->treeWidget->currentItem()->data(0,Qt::UserRole).toString();

	QString mimeType = QString("insviewer/prevtc/config/%1").arg(id);
	if(mimeData.hasFormat(mimeType))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData(mimeType);

		//读入图
		QPixmap p;
		*stream>>p;

		CutsomPlotAxisSetting setting;
		setting.load(*stream);

		QCPLayoutElement* pItem =	_customPlot->plotLayout()->elementAt(0);
		QCPPlotTitle* pTitle = dynamic_cast<QCPPlotTitle*>(pItem);
		if(pTitle)
			setting.generalSetting.strChartTitle  = pTitle->text();

		if( _customPlot->xAxis )
			setting.leftAxisSetting.strAxisTitle = _customPlot->xAxis->label();
		if( _customPlot->yAxis )
			setting.bottomAxisSetting.strAxisTitle = _customPlot->yAxis->label();
		if( _customPlot->xAxis2 )
			setting.topAxisSetting.strAxisTitle = _customPlot->xAxis2->label();
		if( _customPlot->yAxis2 )
			setting.rightAxisSetting.strAxisTitle = _customPlot->yAxis2->label();

		Setting2Plot(setting,_customPlot);
	}
	_customPlot->replot();
}

void CurveConfigDialog::initTree()
{
	ui->treeWidget->clear();
	MimeData mimeData;
	mimeData.load(_configDir + "prevtc.ini");
	if(mimeData.hasFormat("insviewer/prevtc/config/id"))
	{
		QSharedPointer<QDataStream> readStream = mimeData.startReadCustomData("insviewer/prevtc/config/id");
		QString idStr;
		*readStream>>idStr;
		QStringList list = idStr.split(",",QString::SkipEmptyParts);

		foreach(QString idMap,list)
		{
			QString displayName,id;
			id = idMap.split("|",QString::SkipEmptyParts)[0];
			displayName = idMap.split("|",QString::SkipEmptyParts)[1];
			QSharedPointer<QDataStream> stream = mimeData.startReadCustomData(QString("insviewer/prevtc/config/%1").arg(id));
			QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
			item->setText(0,displayName);
			item->setData(0,Qt::UserRole,id);
		}
	}
	onItemClicked(ui->treeWidget->topLevelItem(0),0);
	ui->treeWidget->setFocus();
	ui->treeWidget->setItemSelected(ui->treeWidget->topLevelItem(0),true);
}

void CurveConfigDialog::onItemClicked( QTreeWidgetItem * item, int column )
{
	if(!item)
		return;
	QString id = item->data(0,Qt::UserRole).toString();

	MimeData mimeData;
	mimeData.load(_configDir+"prevtc.ini");
	if(mimeData.hasFormat(QString("insviewer/prevtc/config/%1").arg(id)))
	{
		QPixmap p;
		QSharedPointer<QDataStream> stream = mimeData.startReadCustomData(QString("insviewer/prevtc/config/%1").arg(id));
		*stream>>p;

		ui->label->setPixmap(p);
	}
}

void CurveConfigDialog::deleteConfig()
{
	QTreeWidgetItem* curr = ui->treeWidget->currentItem();
	if(!curr)
		return;

	MimeData mimeData;
	mimeData.load(_configDir +"prevtc.ini");
	QString id = curr->data(0,Qt::UserRole).toString();
	
	QSharedPointer<QDataStream> readStream = mimeData.startReadCustomData("insviewer/prevtc/config/id");
	QString idStr;
	*readStream>>idStr;
	QStringList list = idStr.split(",",QString::SkipEmptyParts);

	//删除保存的ID
	foreach(QString s ,list)
	{
		if(s.contains(id))
			list.removeAll(s);
	}
	
	QString str = list.join(",");
	QDataStream* writeStream = mimeData.startWriteCustomData("insviewer/prevtc/config/id");
	if(!str.isEmpty())
		*writeStream<<str;
	else
	{
		mimeData.stopWriteCustomData("insviewer/prevtc/config/id");
		mimeData.removeFormat("insviewer/prevtc/config/id");
	}

	//删除mimedata
	mimeData.removeFormat(QString("insviewer/prevtc/config/%1").arg(id));

	mimeData.stopWriteAllCustomData();
	mimeData.save(_configDir + "prevtc.ini");

	initTree();
	if(ui->treeWidget->topLevelItemCount() == 0 )
		this->close();
}

void CurveConfigDialog::renameConfig()
{
	QTreeWidgetItem* curr = ui->treeWidget->currentItem();
	if(!curr)
		return ;

	QString newName = QInputDialog::getText(this,"","Input New Name :");
	if(newName.isEmpty())
		return;
	if(!isLegal(newName))
	{
		QMessageBox::warning(this,"Warning","The name is not legal !Please input again.");
		renameConfig();
		return;
	}

	QString id = curr->data(0,Qt::UserRole).toString();
	
	MimeData mimeData;
	mimeData.load(_configDir+"prevtc.ini");
	if(mimeData.hasFormat(QString("insviewer/prevtc/config/id")))
	{
		QSharedPointer<QDataStream> stream = mimeData.startReadCustomData(QString("insviewer/prevtc/config/id"));
		QString idStr;
		*stream>>idStr;
		QStringList list = idStr.split(",",QString::SkipEmptyParts);
		for(int i=0;i<list.count();i++)
		{
			if(list[i].contains(id))
			{
				QString id;
				id = list[i].split("|",QString::SkipEmptyParts)[0];
				list[i] = id+"|"+newName;
				QString str = list.join(",");

				QDataStream* writeStream = mimeData.startWriteCustomData("insviewer/prevtc/config/id");
				*writeStream<<str;

				mimeData.stopWriteAllCustomData();
				mimeData.save(_configDir+"prevtc.ini");

				initTree();
				break;
			}
		}
	}
}

void CurveConfigDialog::upOrDownBtnClicked()
{
	QTreeWidgetItem* curr = ui->treeWidget->currentItem();
	if(!curr)
		return;

	QPushButton* btn = (QPushButton*)sender();
	QString id = curr->data(0,Qt::UserRole).toString();
	
	MimeData mimeData;
	mimeData.load(_configDir+"prevtc.ini");
	if(mimeData.hasFormat("insviewer/prevtc/config/id"))
	{
		QSharedPointer<QDataStream> stream = mimeData.startReadCustomData("insviewer/prevtc/config/id");
		QString idStr;
		*stream>>idStr;
		QStringList list = idStr.split(",",QString::SkipEmptyParts);
		for (int i=0;i<list.count();i++)
		{
			if(list[i].contains(id))
			{
				if(btn->text() == "Up")
				{
					if(i == 0)
						return;

					QString tmp = list[i];
					list[i] = list[i-1];
					list[i-1] = tmp;
				}
				else
				{
					if(i== list.count()-1)
						return;

					QString tmp = list[i];
					list[i] = list[i+1];
					list[i+1] = tmp;
				}
				break;
			}
		}

		QDataStream* writeStream = mimeData.startWriteCustomData("insviewer/prevtc/config/id");
		*writeStream<<list.join(",");

		mimeData.stopWriteAllCustomData();
		mimeData.save(_configDir+"prevtc.ini");

		initTree();
	}
}

bool CurveConfigDialog::isLegal( const QString& str )
{
	QStringList testStr;
	testStr<<"\\"
		<<"/"
		<<":"
		<<"*"
		<<"?"
		<<"\""
		<<"<"
		<<">"
		<<"|"
		<<",";
	for(int i=0;i<testStr.count();i++)
	{
		if(str.contains(testStr[i]))
			return false;
	}
	return true;
}

void CurveConfigDialog::onExportBtnClicked()
{
	QString saveName = QFileDialog::getSaveFileName(this,qApp->applicationDirPath(),"*.dat");
	if(saveName.isEmpty())
		return;
	QFileInfo info(saveName);
	QString fileName = info.fileName();
	if(!isLegal(fileName))
	{
		QMessageBox::warning(this,"Warning","The name is not legal !Please input again.");
		onExportBtnClicked();
		return;
	}
	QFile file(saveName);
	if(file.exists())
		file.remove();
	bool b = QFile::copy(_configDir+"prevtc.ini",saveName);
	if(b)
		QMessageBox::information(this,"Finish","Export data to complete!");
	else
		QMessageBox::information(this,"Sorry","Export data to failed!");
}

void CurveConfigDialog::onImportBtnClicked()
{
	QString openName = QFileDialog::getOpenFileName(this,qApp->applicationDirPath(),"*.dat");
	if(openName.isEmpty())
		return;

	MimeData mimeData;
	mimeData.load(openName);
	QString importStr;
	if(mimeData.hasFormat("insviewer/prevtc/config/id"))
	{
		QSharedPointer<QDataStream> readStream = mimeData.startReadCustomData("insviewer/prevtc/config/id");
		*readStream>>importStr;
	}
	else
	{
		QMessageBox::information(this,"Sorry","There is no content in the file to import");
		return ;
	}
	QStringList importList = importStr.split(",",QString::SkipEmptyParts);


	MimeData yMimeData;//对原有的操作
	yMimeData.load(_configDir+"prevtc.ini");
	QString idStr;
	if(yMimeData.hasFormat("insviewer/prevtc/config/id"))
	{
		QSharedPointer<QDataStream> readStream = yMimeData.startReadCustomData("insviewer/prevtc/config/id");
		*readStream>>idStr;
	}

	//配置文件中没有保存的数据
	if(idStr.isEmpty())
	{
		QFile::remove(_configDir+"prevtc.ini");
		QFile::rename(openName,_configDir+"prevtc.ini");
		QMessageBox::information(this,"Good","Data import is successful!");
		initTree();
		return;
	}

	//记录用户想要的操作
	//0为取消本次操作,1为替换 ,2为不替换
	int flag = -1;
	foreach(QString s,importList)
	{
		QString id = s.split("|",QString::SkipEmptyParts)[0];
		if(idStr.contains(id))
		{
			//有重复的配置
			QMessageBox msgBox;
			msgBox.setText("How to deal with repeat configuration.\n\n"
				"Choose Replace to replace original.\n\n"
				"Choose Retain to retain original.");
			msgBox.setIcon(QMessageBox::Warning);

			QPushButton *replaceButton = msgBox.addButton(tr("Replace"), QMessageBox::ActionRole);
			QPushButton *retainButton = msgBox.addButton(tr("Retain"), QMessageBox::ActionRole);
			QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

			msgBox.exec();

			if (msgBox.clickedButton() == replaceButton)
				flag = 1;
			else if(msgBox.clickedButton() == retainButton)
				flag = 2;
			else
				flag = 0;
			break;
		}
	}

	if(flag == 0)
		return;

	foreach(QString s,importList)
	{
		QString id = s.split("|",QString::SkipEmptyParts)[0];
		QString name = s.split("|",QString::SkipEmptyParts)[1];
		if(idStr.contains(id))
		{
			//有重复的配置
			if(flag == 2)
				continue;
			
			QStringList idStrList = idStr.split(",",QString::SkipEmptyParts);
			for (int i=0;i<idStrList.count();i++)
			{
				if(idStrList[i].contains(id))
					idStrList.replace(i,s);
			}
			idStr = idStrList.join(",");
			importData(mimeData,yMimeData,id);	
		}
		else
		{
			//没有重复的配置
			idStr+=",";
			idStr+=s;
			importData(mimeData,yMimeData,id);
		}
	}
	QDataStream* writeStream = yMimeData.startWriteCustomData("insviewer/prevtc/config/id");
	*writeStream<<idStr;

	yMimeData.stopWriteAllCustomData();
	yMimeData.save(_configDir+"prevtc.ini");

	QMessageBox::information(this,"Good","Import successfully!");
	initTree();
}

void CurveConfigDialog::importData( MimeData& mimeData,MimeData& yMimeData,const QString& id )
{
	QSharedPointer<QDataStream> importStream = mimeData.startReadCustomData("insviewer/prevtc/config/"+id);

	QPixmap p;
	*importStream>>p;

	CutsomPlotAxisSetting setting;
	setting.load(*importStream);

	QDataStream* writeStream = yMimeData.startWriteCustomData("insviewer/prevtc/config/"+id);

	*writeStream<<p;
	setting.save(*writeStream);
}

void CurveConfigDialog::onTreeItemDoubleClicked( QTreeWidgetItem * item, int column )
{
	if(!item)
		return;

	openConfig();
}

