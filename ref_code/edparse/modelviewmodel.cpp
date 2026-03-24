#include "modelviewmodel.h"

#include "edcompile/mainitem.h"
#include "edcore/compileinfomanager.h"
#include "edcore/filemanager.h"
#include "edcore/entity.h"

#include <QtCore>


using namespace INSEditor::Parse;
using namespace INSEditor;


ModelViewModel::ModelViewModel(QObject *parent)
	: QAbstractItemModel(parent)
	,_rootItem(NULL)
{
	//connect(myProject()->getCompileInfoManager(),SIGNAL(itemUpdated(const QString&,Parse::FileItem*)),
		//this,SLOT(onCompileItemChanged(const QString&,Parse::FileItem*)));
}

ModelViewModel::~ModelViewModel()
{
	delete _rootItem;
}

int ModelViewModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}

QVariant ModelViewModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())  
		return QVariant();  

	if (role != Qt::DisplayRole)
		return QVariant();

	// 显示节点数据值  
	if(role==Qt::DisplayRole)  
	{  
		LineItem *item=static_cast<LineItem*>(index.internalPointer());  
		
		if(item->mainLabel.isEmpty() && index.row() == 0)
			return _entityFullName;
		return item->mainLabel;
	}  

	return QVariant();  
}

Qt::ItemFlags ModelViewModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex ModelViewModel::index(int row, int column, const QModelIndex &parent)const
{
	if(!hasIndex(row,column,parent))  
		return QModelIndex();  

	if(!_rootItem)
		return QModelIndex();

	const AssemblyItem *parentItem;  
	if(!parent.isValid())  
		parentItem=_rootItem;  
	else  
		parentItem=static_cast<AssemblyItem*>(parent.internalPointer());   

	const LineItem *childItem=parentItem->child(row);  
	if(childItem)  
		return createIndex(row,column,(void*)childItem); // 展开树形,为子节点建立索引  
	else  
		return QModelIndex();  
}

QModelIndex ModelViewModel::parent(const QModelIndex &index) const
{
	if(!index.isValid() || !_rootItem)  
		return QModelIndex();  

	AssemblyItem *childItem=static_cast<AssemblyItem*>(index.internalPointer());  
	AssemblyItem *parentItem=childItem->getParent(); 

	// 顶层节点,直接返回空索引  
	if(parentItem==_rootItem)  
		return QModelIndex();  

	// 为父结点建立索引  
	return createIndex(parentItem->row(),0,parentItem); 
}

int ModelViewModel::rowCount(const QModelIndex &parent) const
{
	const AssemblyItem *parentItem;  

	if(!_rootItem)
		return 0;

	if(!parent.isValid())  
		parentItem=_rootItem;  
	else  
		parentItem=static_cast<AssemblyItem*>(parent.internalPointer());  

	if(parentItem->type == ASSEMBLYITEM)
		return parentItem->childCount(); // 返回父结点下子结点数目  
	else
		return 0;
}

void ModelViewModel::setRootItem(AssemblyItem* rt )
{
	_rootItem=rt;
}

void ModelViewModel::onModelItemClicked(const QModelIndex & current)
{
	BaseItem* item=static_cast<BaseItem*>(current.internalPointer());
	if(item){
		//_viewerWrapper->highlight(item->getFullName());

		int lineIndex=item->rowIndex;
		int columnIndex=item->columnIndex;
		FileManager::instance()->notifyGotoPosition(_entityFullName,lineIndex,columnIndex);
	}
}

void ModelViewModel::onCompileItemChanged( const QString& fileName,AssemblyItem* fileItem )
{
	if(fileName.isEmpty())
	{
		setRootItem(NULL);
		_entityFullName=QString();
		return;
	}

	if(!fileName.compare(_entityFullName,Qt::CaseInsensitive)){
		setRootItem(fileItem);
	}
}

void ModelViewModel::onEntityActivated( INSEditor::Parse::AssemblyItem* item ,const QString& fileName)
{
	// 废弃旧的模型数据  
	if(_rootItem)  
	{  
		delete _rootItem;  
		_rootItem=NULL;  
	}
	INSEditor::Parse::AssemblyItem* root = new INSEditor::Parse::AssemblyItem;
	root->keyname = fileName;
	root->mainID = fileName;
	root->mainLabel = fileName;
	root->addChild(item);
	_entityFullName = fileName;
	setRootItem(root);

	// 刷新模型  
	reset();  
}


