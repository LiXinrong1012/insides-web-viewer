#include "parameterswidget.h"
#include "ui_parameterswidget.h"
#include "expressinputdialog.h"
#include <qdebug.h>
#include <QTableWidgetItem>
#include <QObject>

ParametersWidget::ParametersWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::ParametersWidget();
	ui->setupUi(this);

	ui->tablewidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->btnModify->setDisabled(true);
	ui->btnRemove->setDisabled(true);
	ui->btnUp->setDisabled(true);
	ui->btnDown->setDisabled(true);
	InitData();
	
}

ParametersWidget::~ParametersWidget()
{
	delete ui;
}

void ParametersWidget::InitData()
{
	TDYParameterItem item;
	item.keyname = "11111";
	item.description = "aaaaa";
	item.strPara = "111aaa";
	_itemlist.append(item);

	item.keyname = "22222";
	item.description = "bbbbb";
	item.strPara = "222bb";
	_itemlist.append(item);

	item.keyname = "33333";
	item.description = "ccccc";
	item.strPara = "333ccc";
	_itemlist.append(item);

	
	int size = _itemlist.size();
	//int count = m_TDYPar.count();
	if(!_itemlist.isEmpty())
	//if(count > 0)
	{
		
		for(int i = 0; i < size; i++)
		{
			int rowcount = ui->tablewidget->rowCount();
			ui->tablewidget->insertRow(rowcount);
			modifyRowContent(i);	
		}	 
	}

}

void ParametersWidget::onAdd()
{
	ExpressInputDialog exDlg;
	if ((exDlg.exec() == QDialog::Accepted)) 
	{
		TDYParameterItem *item = exDlg.getInputItem();
		//m_TDYPar.add(item);
		if(item != NULL)
			_itemlist.append(*item);
		int rowcount = ui->tablewidget->rowCount();
		ui->tablewidget->insertRow(rowcount);
		int size = _itemlist.size();
		//int count = m_TDYPar.count();
		if(!_itemlist.isEmpty())
		//if(count > 0)
		{
			for(int i = 0; i < size; i++)
				modifyRowContent(i);	 
		}
    } 
	
}

void ParametersWidget::onRemove()
{
	bool focus = ui->tablewidget->isItemSelected(ui->tablewidget->currentItem());
	if(focus)
	{
		int row1 = ui->tablewidget->currentItem()->row();
		if(row1 >= 0)
		{
			ui->tablewidget->removeRow(row1);
			_itemlist.removeAt(row1);
		}
	}

}
void ParametersWidget::onModify()
{
	bool focus = ui->tablewidget->isItemSelected(ui->tablewidget->currentItem());
	if(focus)
	{
		int row1 = ui->tablewidget->currentItem()->row();
		

		if(row1 >= 0)
		{
			ExpressInputDialog exDlg(_itemlist.at(row1));
			if ((exDlg.exec() == QDialog::Accepted)) 
			{
				TDYParameterItem *item = exDlg.getInputItem();
				if(item != NULL)
				{
					_itemlist.replace(row1,*item);
					modifyRowContent(row1);
				}		
			} 
		}
	}
}
void ParametersWidget::onUp()
{
	bool focus = ui->tablewidget->isItemSelected(ui->tablewidget->currentItem());
	if(focus)
	{
		int row1 = ui->tablewidget->currentItem()->row();
		if(row1 > 0)
		{
			ui->btnUp->setDisabled(false);
			ui->btnDown->setDisabled(false);
			TDYParameterItem item1 = _itemlist.at(row1);
			TDYParameterItem item2 = _itemlist.at(row1-1);
			_itemlist.replace(row1,item2);
			_itemlist.replace(row1-1,item1);
			modifyRowContent(row1);
			modifyRowContent(row1-1);
			ui->tablewidget->selectRow(row1-1);
			int curow = ui->tablewidget->currentItem()->row();
			if(curow == 0)
				ui->btnUp->setDisabled(true);
		}
		else if(0 == row1)
		{
			ui->btnUp->setDisabled(true);
		}
	}
	
}

void ParametersWidget::onDown()
{
    bool focus = ui->tablewidget->isItemSelected(ui->tablewidget->currentItem());
	if(focus)
	{
		int row1 = ui->tablewidget->currentItem()->row();
		int size = ui->tablewidget->rowCount();
		if(row1 < size -1 && row1 >= 0)
		{
			ui->btnDown->setDisabled(false);
			ui->btnUp->setDisabled(false);
			TDYParameterItem item1 = _itemlist.at(row1);
			TDYParameterItem item2 = _itemlist.at(row1+1);
			_itemlist.replace(row1,item2);
			_itemlist.replace(row1+1,item1);
			modifyRowContent(row1);
			modifyRowContent(row1+1);
			ui->tablewidget->selectRow(row1+1);
			int curow = ui->tablewidget->currentItem()->row();
			if(curow == size-1)
				ui->btnDown->setDisabled(true);

		}
		else if(row1 == size-1)
		{
			ui->btnDown->setDisabled(true);
		}
	}
	
}

void ParametersWidget::modifyRowContent(int Row)
{
	TDYParameterItem item;
	for(int j = 0; j < 3; j++)
	{
		item = _itemlist.at(Row);
		QTableWidgetItem *newItem = NULL;
		switch(j)
		{
			case 0:
				newItem =  new QTableWidgetItem(item.keyname);
				break;
			case 1:
				newItem =  new QTableWidgetItem(item.strPara);
				break;
			case 2:
				newItem =  new QTableWidgetItem(item.description);
		}
		ui->tablewidget->setItem(Row, j, newItem);
	}
}

void ParametersWidget::onBtnState(int row,int column)
{
	int size = ui->tablewidget->rowCount();
	if(1 == size)
	{
		ui->btnUp->setDisabled(true);
		ui->btnDown->setDisabled(true);
	}
	else if(0 == row)
	{
		ui->btnUp->setDisabled(true);
		ui->btnDown->setDisabled(false);
	}
	else if(row == size - 1)
	{
		ui->btnDown->setDisabled(true);
		ui->btnUp->setDisabled(false);
	}
	else if(row > 0 && row < size - 1)
	{
		ui->btnUp->setDisabled(false);
		ui->btnDown->setDisabled(false);
	}
	else
	{
		ui->btnModify->setDisabled(true);
		ui->btnRemove->setDisabled(true);
	}
	
		
}

void ParametersWidget::onBtnChangeState()
{
	int row = ui->tablewidget->currentRow();
	int size = ui->tablewidget->rowCount();
	bool focus = ui->tablewidget->isItemSelected(ui->tablewidget->currentItem());
	bool fo = ui->tablewidget->hasFocus();
	
	if(focus)
	{
		ui->btnModify->setDisabled(false);
		ui->btnRemove->setDisabled(false);
	}
	else
	{
		ui->btnModify->setDisabled(true);
		ui->btnRemove->setDisabled(true);
		ui->btnUp->setDisabled(true);
		ui->btnDown->setDisabled(true);
		
	}

}