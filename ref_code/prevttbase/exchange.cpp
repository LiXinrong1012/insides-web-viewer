//#include "exchange.h"
//#include "prevttbase/sortproxymodel.h"
//
//#include "base/Console.h"
//#include "base/activeviewobject.h"
//
//#include "precore/BaseItem.h"
//#include "precore/precore_data.h"
//#include "precore/FEMPartBaseItem.h"
//#include "precore/IResultItem.h"
//#include "precore/ModelDocument.h"
//#include "precore/FlexResultItem.h"
//#include "precore/DynamicResultItem.h"
//#include "precore/precore_data.h"
//
//#include "prefem/JMesh.h"
//#include "prefem/JMeshGroup.h"
//#include "prefem/prefem_def.h"
//#include "prefem/MeshGlobal.h"
//
//#include <QWeakPointer>
//#include <QStringBuilder>
//using namespace Base;
//
//ExchangeModel::ExchangeModel(SortProxyModel *model)
//	: QAbstractTableModel(model)
//	,_model(model)
//	,_modelType(false)
//{
//}
//
//ExchangeModel::~ExchangeModel()
//{
//
//}
//
//int ExchangeModel::rowCount( const QModelIndex & parent /*= QModelIndex() */ ) const
//{
//	return _model->columnCount();
//}
//
//int ExchangeModel::columnCount( const QModelIndex & parent /*= QModelIndex() */ ) const
//{
//	return _model->rowCount();
//}
//
//QVariant ExchangeModel::data( const QModelIndex & index, int role /*= Qt::DisplayRole */ ) const
//{
//	return _model->data(_model->index(index.column(),index.row()),role);
//}
//
//QVariant ExchangeModel::headerData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */ ) const
//{
//	if (orientation == Qt::Horizontal)
//		return _model->headerData(section,Qt::Vertical,role);
//
//
//	return _model->headerData(section,Qt::Horizontal,role);
//}
