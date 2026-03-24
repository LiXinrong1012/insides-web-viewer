#ifndef PRETDY_JERRY_PREDOCUMENT_LISTENER_H_
#define PRETDY_JERRY_PREDOCUMENT_LISTENER_H_


namespace INSIDES
{

class BaseItem;

/*!
*	针对模型数据的观察者定义。
*	模型改变时，观察者会调用相应的函数。
*	观察者支持优先级，优先级数值大的观察者会被先调用。
*	@author	Jerry He
*	@date	2014.6.26
*/
class ModelDocumentListener
{
public:
	ModelDocumentListener(int priority):_priority(priority){}
	virtual ~ModelDocumentListener(){}

	int getPriority()const{return _priority;}

protected:
	/// 当节点将要添加时发送
	virtual void doc_BeginItemAdding(BaseItem* item,BaseItem* parent,int pos){}
	/// 当节点添加后发送
	virtual void doc_ItemAdded(BaseItem* item,bool isIncludingChildren){}
	/// 当节点更改后发送
	virtual void doc_ItemModified(BaseItem* item,bool isIncludingChildren){}
	/// 当节点将要删除时发送
	virtual void doc_BeginItemRemoving(BaseItem* item){}
	/// 当节点删除后发送
	virtual void doc_ItemRemoved(BaseItem* parent,BaseItem* item){}
	/// 当模型被重致后发送
	virtual void doc_ModelReseted(BaseItem* rootItem){}
	/// 显示的根节点改变后发送
	virtual void doc_BeginRootItemChanging(BaseItem* currentRoot,BaseItem* newRoot){}
	/// 显示的根节点改变后发送
	virtual void doc_RootItemChanged(BaseItem* currentRoot,BaseItem* oldRoot){}
	/// 参数条目改变时发送
	virtual void doc_ParametersChanged(BaseItem* parametersItem){}
	/// 开始保存文档时发送
	virtual void doc_BeginSavingDocument(){}
	/// 结果保存文档时发送
	virtual void doc_EndSavingDocument(){}


private:
	int _priority;

	friend class ModelDocument;
};

}

#endif