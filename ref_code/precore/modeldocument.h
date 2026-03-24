#pragma once

#include "precore/Assembly.h"
#include "precore/document.h"

#include <QObject>
#include <QScopedPointer>
#include <QUndoStack>
#include <QUndoCommand>

namespace pp{class XMLHandler; class DataStreamWriter;}

class ITreeItemPropertyFunc;

namespace INSIDES
{

class PreDocumentPrivate;

class ModelDocumentListener;


bool PRECORE_EXPORT PP_XML_Open_SaveFile(const QString& fileName,pp::XMLHandler** xmlHandler,pp::DataStreamWriter** dataWriter);
bool PRECORE_EXPORT PP_XML_Close_SaveFile(const QString& fileName,pp::XMLHandler* xmlHandler,pp::DataStreamWriter* dataWriter);

bool PRECORE_EXPORT PP_XML_Open_LoadFile(const QString& fileName,pp::XMLHandler** xmlHandler);
bool PRECORE_EXPORT PP_XML_Close_LoadFile(pp::XMLHandler* xmlHandler);


class PRECORE_EXPORT ModelDocument
{
public:
	ModelDocument();
	~ModelDocument(void);

	Assembly* getAssembly();
	BaseItem* getActiveItem();
	void ModelDocument::setAssembly( Assembly* asembly );

	void pushActiveItem(BaseItem* item);	
	void popActiveItem();

	bool insertChild(BaseItem* parent,BaseItem* item,int pos=-1);
	bool remove(BaseItem* item,bool deleteIt);
	bool modify(BaseItem* src,BaseItem* dst);

	QUndoStack* getUndoStack();
	void pushCommand(QUndoCommand* command);

	bool getUndoable();
	void setUndoable(bool b);

	bool getAutoUpdateView();
	void setAutoUpdateView(bool b);

	void update();
	void reset();

	// data exchange interfaces
	bool save(const QString& fileName);
	bool save(pp::XMLHandler* xmlHandler,pp::DataStreamWriter* dataWriter);
	bool load(const QString& fileName);
	bool load(pp::XMLHandler* xmlHandler);

	void createDefault();		//删除模型内容，并创建默认模型。
	void debug_example1();

	ITreeItemPropertyFunc* getTreeItemProperties();
	//ComTreeModel* getComTreeModel();

	BaseItem* findItem(const QString& absoluteName,Assembly* baseAssembly=NULL);
	BaseItem* findItemWithoutFolder(const QString& name,Assembly* baseAssembly=NULL);

	void setEnableSignal(bool b){_enableSignal=b;}

	void attachListener(ModelDocumentListener* listener);
	void disattachListener(ModelDocumentListener* listener);

protected:

	///// 当文档有更新时
	//void documentChanged();		
	/// 当节点将要添加时发送
	void notifyBeginItemAdding(BaseItem* item,BaseItem* parent,int pos);
	/// 当节点添加后发送
	void notifyItemAdded(BaseItem* item,bool isIncludingChildren);
	/// 当节点更改后发送
	void notifyItemModified(BaseItem* item,bool isIncludingChildren);
	/// 当节点将要删除时发送
	void notifyBeginItemRemoving(BaseItem* item);
	/// 当节点删除后发送
	void notifyItemRemoved(BaseItem* parent,BaseItem* item);
	/// 当模型被重致后发送
	void notifyModelReseted(BaseItem* rootItem);
	/// 显示的根节点改变后发送
	void notifyBeginRootItemChanging(BaseItem* currentRoot,BaseItem* newRoot);
	/// 显示的根节点改变后发送
	void notifyRootItemChanged(BaseItem* currentRoot,BaseItem* oldRoot);
	/// 参数条目改变时发送
	void notifyParametersChanged(BaseItem* parametersItem);
	/// 开始保存文档时发送
	void notifyBeginSavingDocument();
	/// 结果保存文档时发送
	void notifyEndSavingDocument();

public:		//public static functions

protected:
	QScopedPointer<PreDocumentPrivate> _ptr;

	bool		_enableSignal;
	typedef QList<ModelDocumentListener*> ListenerList;
	ListenerList		_listenerList;

	void clearModel();		//删除模型内容
};

inline ModelDocument* myDocument(){return MultiDocuments::instance()->getActiveDocument()->getDocument();}

}