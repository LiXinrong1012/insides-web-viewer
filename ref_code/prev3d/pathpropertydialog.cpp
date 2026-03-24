#include "pathpropertydialog.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QMessageBox>
#include <QBrush>
#include <QLabel>
#include <QFileDialog>

#include "TrackPaths.h"
#include "ResultViewManager.h"
#include "PreHQWidget.h"
#include "precore/modeldocument.h"
#include "precore/precore_data.h"

PathPropertyDialog::PathPropertyDialog(ResultViewManager* viewManager,QWidget *parent)
	: QDialog(parent)
	,_resultViewManager(viewManager)
{
	ui = new Ui::PathPropertyDialogClass();
	ui->setupUi(this);

	// todo: init data from viewManager to control.

	ui->pathTableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows);
	//this->insertOnePathItem(true,".com.baidu.maker","www.baidu.com",false,20,"#ff00ef",10,50);
	//this->insertOnePathItem(true,".com.baidu.makffer","www.baidffu.com",false,10,"#fff0ef",20,30);
	
	if(_resultViewManager)
	{
		_trackPaths = _resultViewManager->getTrackPaths();
		
		int trackPathCount=_trackPaths->getTrackPathCount();
		for (int i=0;i<trackPathCount;i++)
		{
			TrackPath *path = _trackPaths->getTrackPath(i);
			bool visual = path->getEnabled();
			QString relatedMarker = path->getRelatedMarkerName();
			QString name = path->getName();
			bool arrow = path->getShowArrow();
			int width = path->getLineWidth();
			QColor color = path->getLineColor();
			int delay =path->getDelayFrameCount();
			int length = path->getDisplayFrameCount();
			this->insertOnePathItem(visual,relatedMarker,name,arrow,width,color.name(),delay,length);
		}

		ui->pathTableWidget->setItemSelected(ui->pathTableWidget->item(0,0),true);

		connect(ui->removeBtn,SIGNAL(clicked()),this,SLOT(onRemoveBtnClicked()));
		connect(ui->clearAllBtn,SIGNAL(clicked()),this,SLOT(onClearBtnClicked()));
		connect(ui->importBtn,SIGNAL(clicked()),this,SLOT(onImportBtnClicked()));
		connect(ui->exportBtn,SIGNAL(clicked()),this,SLOT(onExportBtnClicked()));
		connect(ui->closeBtn,SIGNAL(clicked()),this,SLOT(onCloseBtnClicked()));

//		connect(ui->pathTableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(onItemClicked(QTableWidgetItem*)));
	} 
	else
	{
		connect(ui->closeBtn,SIGNAL(clicked()),this,SLOT(close()));
	}
}

PathPropertyDialog::~PathPropertyDialog()
{
	delete ui;
}

bool PathPropertyDialog::insertOnePathItem( bool isVisuable,QString maker,QString text,bool arrow,int width,QString color,int delay,int length )
{
	int row = ui->pathTableWidget->rowCount();
	ui->pathTableWidget->insertRow(row);

	QCheckBox *visuableCheckBox = new QCheckBox();
	if (isVisuable)
		visuableCheckBox->setChecked(true);
	else
		visuableCheckBox->setChecked(false);

	QCheckBox *arrowCheckBox = new QCheckBox();
	if(arrow)
		arrowCheckBox->setChecked(true);
	else
		arrowCheckBox->setChecked(false);

	QSpinBox *widthSpinBox = new QSpinBox();
	widthSpinBox->setValue(width);
	widthSpinBox->setRange(1,20);

	QSpinBox *delaySpinBox = new QSpinBox();
	delaySpinBox->setRange(1,1000000);
	delaySpinBox->setValue(delay);

	QSpinBox *lengthSpinBox = new QSpinBox();
	lengthSpinBox->setRange(1,100000);
	lengthSpinBox->setValue(length);

	ui->pathTableWidget->setCellWidget(row,0,visuableCheckBox);
	ui->pathTableWidget->setItem(row,1,new QTableWidgetItem(maker));
	ui->pathTableWidget->setItem(row,2,new QTableWidgetItem(text));
	ui->pathTableWidget->setCellWidget(row,3,arrowCheckBox);
	ui->pathTableWidget->setCellWidget(row,4,widthSpinBox);
	
	QLabel* label = new QLabel;
	label->setStyleSheet(QString("background-color:%1").arg(color));
	label->installEventFilter(this);
	ui->pathTableWidget->setCellWidget(row,5,label);



	ui->pathTableWidget->setCellWidget(row,6,delaySpinBox);
	ui->pathTableWidget->setCellWidget(row,7,lengthSpinBox);

	return true;
}

//Çå³ýÏßÂ·
void PathPropertyDialog::onClearBtnClicked()
{
	_trackPaths->clearAll();
	ui->pathTableWidget->setRowCount(0);
}

//remove one
void PathPropertyDialog::onRemoveBtnClicked()
{
	int row = ui->pathTableWidget->currentRow();
	ui->pathTableWidget->removeRow(row);
	_trackPaths->removeTrackPath(row);
}

void PathPropertyDialog::onImportBtnClicked()
{
	QString openName = QFileDialog::getOpenFileName(".","*.dat",this);
	if(openName.isEmpty())
		return;

	QFile file(openName);
	file.open(QIODevice::ReadOnly);
	QDataStream stream(&file);

	int count=0;
	stream>>count;
	for(int i=ui->pathTableWidget->rowCount();i>=0;i--)
		ui->pathTableWidget->removeRow(i);

	int frameCount=myResultDocument()->getResults()->getFrameCount();
	_resultViewManager->clearTrackPath();

	for (int i=0;i<count;i++)
	{
		QString itemFullName;
		int		nodeNumber=0;
		bool visual=true;
		QString relatedMarker;
		QString name;
		bool arrow= false;
		int width = 1;
		QColor color;
		int delay=0;
		int length = 0;

		stream>>itemFullName
			>>nodeNumber
			>>visual
			>>relatedMarker
			>>name
			>>arrow
			>>width
			>>color
			>>delay
			>>length;

		BaseItem* item = myDocument()->findItem(itemFullName);
		TrackPath* path = NULL;
		if(item->getCategory() == TDY_PRE_CATE_FEMPART)
		{
			_resultViewManager->getPreHQWidget()->setSelectSubNode(nodeNumber);
			path = _resultViewManager->getPreHQWidget()->addNodePath(item);
		}
		if(item->getCategory() == TDY_PRE_CATE_MARKER || item->getCategory() == TDY_PRE_CATE_ASSEMBLY)
			path = _resultViewManager->getPreHQWidget()->addTrackPath(item);

		if(path)
		{
			path->setEnabled(visual);
			path->setRelatedMarkerName(relatedMarker);
			path->setName(name);
			path->setShowArrow(arrow);
			path->setLineWidth(width);
			path->setLineColor(color);
			path->setDelayFrameCount(delay);
			path->setDisplayFrameCount(length);
		}

		this->insertOnePathItem(visual,relatedMarker,name,arrow,width,color.name(),delay,length);
	}
	file.close();
}

void PathPropertyDialog::onExportBtnClicked()
{
	QString saveName = QFileDialog::getSaveFileName(".","*.dat",this);
	if(saveName.isEmpty())
		return;

	QFile file(saveName);
	file.open(QIODevice::WriteOnly);
	QDataStream stream(&file);

	int trackPathCount=_trackPaths->getTrackPathCount();
	stream<<trackPathCount;
	for (int i=0;i<trackPathCount;i++)
	{
		TrackPath *path = _trackPaths->getTrackPath(i);
		QString itemFullName = path->getFullItemName();
		int		nodeNumber = path->getNodeNumber();
		bool visual = path->getEnabled();
		QString relatedMarker = path->getRelatedMarkerName();
		QString name = path->getName();
		bool arrow = path->getShowArrow();
		int width = path->getLineWidth();
		QColor color = path->getLineColor();
		int delay =path->getDelayFrameCount();
		int length = path->getDisplayFrameCount();
		
		stream<<itemFullName
			<<nodeNumber
			<<visual
			<<relatedMarker
			<<name
			<<arrow
			<<width
			<<color
			<<delay
			<<length;
	}
	file.close();
}


void PathPropertyDialog::onCloseBtnClicked()
{
	for (int i=0;i<_trackPaths->getTrackPathCount();i++)
	{
		TrackPath *path = _trackPaths->getTrackPath(i);

		QCheckBox *vBox = (QCheckBox *)ui->pathTableWidget->cellWidget(i,0);
		if (vBox->isChecked())
			path->setEnabled(true);
		else
			path->setEnabled(false);

		path->setRelatedMarkerName(ui->pathTableWidget->item(i,1)->text());

		path->setName(ui->pathTableWidget->item(i,2)->text());

		QCheckBox *aBox = (QCheckBox*)ui->pathTableWidget->cellWidget(i,3);
		if (aBox->isChecked())
			path->setShowArrow(true);
		else
			path->setShowArrow(false);

		QSpinBox *wSpinBox = (QSpinBox *)ui->pathTableWidget->cellWidget(i,4);
		path->setLineWidth(wSpinBox->value());

		QLabel* label = (QLabel*)ui->pathTableWidget->cellWidget(i,5);
		path->setLineColor(label->backgroundColor());

		QSpinBox *dSpinBox = (QSpinBox *)ui->pathTableWidget->cellWidget(i,6);
		path->setDelayFrameCount(dSpinBox->value());

		QSpinBox *lSpinBox = (QSpinBox *)ui->pathTableWidget->cellWidget(i,7);
		path->setDisplayFrameCount(lSpinBox->value());
	}
	this->close();
}

bool PathPropertyDialog::eventFilter( QObject * o, QEvent * e )
{
	if(e->type()== QEvent::MouseButtonDblClick)
	{
		
		QTableWidgetItem* item = ui->pathTableWidget->selectedItems()[0];
		int row = item->row();

		QColor color = QColorDialog::getColor();
		if (color.isValid())
		{
			QLabel* label = (QLabel*)ui->pathTableWidget->cellWidget(row,5);
			label->setStyleSheet(QString("background-color:%1").arg(color.name()));
		}
	}
	return QDialog::eventFilter(o,e);
}
