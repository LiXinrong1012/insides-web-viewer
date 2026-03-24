#include "pathpropertydialog.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QMessageBox>
#include <QBrush>

PathPropertyDialog::PathPropertyDialog(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::PathPropertyDialogClass();
	
	ui->setupUi(this);
	resize(750,450);
	ui->pathTableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows);
	this->insertOnePathItem(true,".com.baidu.maker","www.baidu.com",false,20,"#ff00ef",10,50);
	this->insertOnePathItem(true,".com.baidu.makffer","www.baidffu.com",false,10,"#fff0ef",20,30);

	ui->pathTableWidget->setItemSelected(ui->pathTableWidget->item(0,0),true);
	
	connect(ui->removeBtn,SIGNAL(clicked()),this,SLOT(onRemoveBtnClicked()));
	connect(ui->clearAllBtn,SIGNAL(clicked()),this,SLOT(onClearBtnClicked()));
	connect(ui->importBtn,SIGNAL(clicked()),this,SLOT(onImportBtnClicked()));
	connect(ui->exportBtn,SIGNAL(clicked()),this,SLOT(onExportBtnClicked()));

	connect(ui->pathTableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(onItemClicked(QTableWidgetItem*)));
}

PathPropertyDialog::~PathPropertyDialog()
{

}

bool PathPropertyDialog::insertOnePathItem( bool isVisuable,QString maker,QString text,bool arrow,int width,QString color,int delay,int length )
{
	int row = ui->pathTableWidget->rowCount();
	ui->pathTableWidget->insertRow(row);

	QCheckBox *visuableCheckBox = new QCheckBox();
	if (isVisuable == true)
	{
		visuableCheckBox->setChecked(true);
	}
	else
	{
		visuableCheckBox->setChecked(false);
	}

	QCheckBox *arrowCheckBox = new QCheckBox();
	if(arrow == true)
	{
		arrowCheckBox->setChecked(true);
	}
	else
	{
		arrowCheckBox->setChecked(false);
	}

	QSpinBox *widthSpinBox = new QSpinBox();
	widthSpinBox->setValue(width);
	widthSpinBox->setRange(1,20);



	QSpinBox *delaySpinBox = new QSpinBox();
	delaySpinBox->setValue(delay);
	delaySpinBox->setMinimum(0);

	QSpinBox *lengthSpinBox = new QSpinBox();
	lengthSpinBox->setValue(length);
	lengthSpinBox->setMinimum(0);

	ui->pathTableWidget->setCellWidget(row,0,visuableCheckBox);
	ui->pathTableWidget->setItem(row,1,new QTableWidgetItem(maker));
	ui->pathTableWidget->setItem(row,2,new QTableWidgetItem(text));
	ui->pathTableWidget->setCellWidget(row,3,arrowCheckBox);
	ui->pathTableWidget->setCellWidget(row,4,widthSpinBox);

	QTableWidgetItem* item = new QTableWidgetItem();
	item->setBackground(QBrush(QColor(color)));
	ui->pathTableWidget->setItem(row,5,item);


	ui->pathTableWidget->setCellWidget(row,6,delaySpinBox);
	ui->pathTableWidget->setCellWidget(row,7,lengthSpinBox);

	

	return true;
}

//清除线路
void PathPropertyDialog::onClearBtnClicked()
{
	ui->pathTableWidget->clearContents();
}

//remove one
void PathPropertyDialog::onRemoveBtnClicked()
{
	int row = ui->pathTableWidget->currentRow();
	ui->pathTableWidget->removeRow(row);
}

void PathPropertyDialog::onImportBtnClicked()
{
	//
}

void PathPropertyDialog::onExportBtnClicked()
{
	//
}

void PathPropertyDialog::onItemClicked( QTableWidgetItem* item )
{
	int row = item->row();
	int col = item->column();

	if(col == 5)
	{
		QColor color = QColorDialog::getColor();
		if (color.isValid())
		{
			item->setBackground(QBrush(color));
			//设置线的颜色
		}
		
	}
}
