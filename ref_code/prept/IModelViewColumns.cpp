#include "IModelViewColumns.h"

#include "base/TreeItemPropertyManager.h"
#include "base/activeviewobject.h"
#include "base/view.h"

#include "precore/modeldocument.h"

#include <QTableView>
#include <QTreeView>

using namespace Base;

using namespace INSIDES;



IModelColumns::IModelColumns(void)
{
}

void IModelColumns::updateColumns()
{
	TreeItemPropertyManager* manager=TreeItemPropertyManager::instance();
	_currTreeItemPropertyList.clear();
	_currentPropertiesIndex.clear();
	_currentPropertiesParents.clear();
	ITreeItemPropertyFunc* name1=myDocument()->getTreeItemProperties();
	View* activeView=ActiveViewObject::instance()->activeView();
	ITreeItemPropertyFunc* name2=activeView?activeView->getTreeItemProperties():NULL;

	QStringList& selected=manager->getSelectedItems();
	TreeItemPropertyGroup* name1Props=manager->getGroup(name1->getKeyname());
	TreeItemPropertyGroup* name2Props=name2?manager->getGroup(name2->getKeyname()):NULL;
	for(int i=0;i<selected.size();++i){
		if(name1Props){
			TreeItemProperty* pros=name1Props->getProperty(selected[i]);
			if(pros){
				_currTreeItemPropertyList.push_back(pros);
				_currentPropertiesParents.push_back(name1);
				_currentPropertiesIndex.push_back(name1Props->indexOf(selected[i]));
				continue;
			}
		}
		if(name2Props){
			TreeItemProperty* pros=name2Props->getProperty(selected[i]);
			if(pros){
				_currTreeItemPropertyList.push_back(pros);
				_currentPropertiesParents.push_back(name2);
				_currentPropertiesIndex.push_back(name2Props->indexOf(selected[i]));
				continue;
			}
		}
	}
}

TreeItemProperty* IModelColumns::getColumnDataType( int columnIndex )
{
	return _currTreeItemPropertyList[columnIndex];
}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
IViewColumns::IViewColumns()
{

}


void IViewColumns::updateHeaderWidth(QTreeView* view,QAbstractItemModel* model,IModelColumns* colModel)
{
	int columnSize=model->columnCount(QModelIndex());
	for(int i=0;i<columnSize-1;++i){
		TreeItemProperty* pro=colModel->getColumnDataType(i);
		view->setColumnWidth(i+1,pro->width);
	}
	view->setColumnWidth(0,TreeItemPropertyManager::instance()->getFirstColumnWidth());
}

void IViewColumns::updateHeaderWidth(QTableView* view,QAbstractItemModel* model,IModelColumns* colModel)
{
	int columnSize=model->columnCount(QModelIndex());
	for(int i=0;i<columnSize-1;++i){
		TreeItemProperty* pro=colModel->getColumnDataType(i);
		view->setColumnWidth(i+1,pro->width);
	}
	view->setColumnWidth(0,TreeItemPropertyManager::instance()->getFirstColumnWidth());
}

void IViewColumns::updateHeaderDelegate(QAbstractItemView* view,QAbstractItemModel* model,IModelColumns* colModel)
{
	// ÉèÖÃ´úÀí
	int columnSize=model->columnCount(QModelIndex());
	for(int i=0;i<columnSize-1;++i){
		TreeItemProperty* pro=colModel->getColumnDataType(i);
		if(pro->editable){
			switch(pro->type){
			default:
				{
					QAbstractItemDelegate* de=TreeItemPropertyManager::instance()->getItemDelegate(pro->type);
					if(de){
						view->setItemDelegateForColumn(i+1,de);
					}
				}
				break;
			}
		}
	}
}

