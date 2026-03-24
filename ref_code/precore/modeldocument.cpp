#include "modeldocument.h"
#include <stack>
#include <QStringList>
#include <QFileInfo>
#include <QDir>

#include "test.h"

#include "modeldocumentlistener.h"
#include "precore/precore_data.h"
#include "precore/ModelDataXMLExchange.h"

#include "base/Console.h"

#include "pp_xml/xml.h"
#include "pp_xml/DataStreamReader.h"
#include "pp_xml/DataStreamWriter.h"

#include "base/TreeItemPropertyManager.h"

#include "UAPI_.h"

namespace INSIDES
{

class DocumentTreeItemRegister
{
public:
	DocumentTreeItemRegister();
};

DocumentTreeItemRegister::DocumentTreeItemRegister()
{
	TreeItemPropertyGroup* props=new TreeItemPropertyGroup();
	props->setKeyname("Base");
	props->addProperty(TreeItemProperty("Base::id",QVariant::Int,false,20))
		.addProperty(TreeItemProperty("Base::ClassType",QVariant::Int,false,20))
		.addProperty(TreeItemProperty("Base::Category",QVariant::Int,false,20))
		.addProperty(TreeItemProperty("Base::Flags",QVariant::Int,false,20));
	TreeItemPropertyManager::instance()->addGroup(props);
}

static DocumentTreeItemRegister documentTreeRegister;

class DocumentTreeItemProperties:public ITreeItemPropertyFunc
{
public:
	virtual QString getKeyname()const{return "Base";}
	virtual QVariant getData(BaseItem* baseItem,int index);
	virtual bool setData(BaseItem* baseItem,int index,const QVariant& data);
};


QVariant DocumentTreeItemProperties::getData( BaseItem* baseItem,int index )
{
	switch(index){
	case 0:
		return baseItem->getID();
	case 1:
		return baseItem->getClassType();
	case 2:
		return baseItem->getCategory();
	case 3:
		return (qlonglong)baseItem->getFlags();
	}
	return QVariant();
}
bool DocumentTreeItemProperties::setData( BaseItem* baseItem,int index,const QVariant& data )
{
	return false;
}




using namespace pp;


bool PRECORE_EXPORT PP_XML_Open_SaveFile( const QString& fileName,XMLHandler** ppXmlHandler,pp::DataStreamWriter** dataWriter )
{
	// set current directory
	QFileInfo fileInfo(fileName);
	QString baseName=fileInfo.baseName();

	bool re=QDir::setCurrent ( fileInfo.dir().absolutePath() )  ;

	XMLHandler* xmlHandler=new XMLHandler();
	*ppXmlHandler=xmlHandler;
	xmlHandler->Create();

	JXMLItem xmlRoot=xmlHandler->GetRoot();
	JXMLItem xmlEasyPlot=xmlHandler->GetFirstChild(xmlRoot);

	if(!xmlRoot || !xmlEasyPlot)
		return false;

	//VersionInfo ver=version;
	//xmlHander.SetAttribString(xmlEasyPlot,"VERSION",bxVersion2String(ver));
	QString bulkFileName=baseName+".bulk";
	xmlHandler->SetAttribString(xmlEasyPlot,"BULKFILE",bulkFileName);

	QByteArray str=bulkFileName.toLatin1();
	DataStreamWriter* bulkWriter=new DataStreamWriter();
	bulkWriter->open(bulkFileName);
	*dataWriter=bulkWriter;

	return true;
}

bool PRECORE_EXPORT PP_XML_Close_SaveFile(const QString&fileName, XMLHandler* xmlHandler,DataStreamWriter* dataWriter )
{
	bool re=xmlHandler->Save(fileName);
	dataWriter->close();
	delete xmlHandler;
	delete dataWriter;
	return re;
}

bool PRECORE_EXPORT PP_XML_Open_LoadFile( const QString& fileName,pp::XMLHandler** xmlHandler )
{
	// set current directory
	QFileInfo fileInfo(fileName);
	if(!fileInfo.exists())
	{
		Base::Console().Error("File: %s : no such file.",fileName);
		return false;
	}
	bool re=QDir::setCurrent ( fileInfo.dir().absolutePath() )  ;

	*xmlHandler=new XMLHandler();
	(*xmlHandler)->Open(fileName);
	return true;
}

bool PRECORE_EXPORT PP_XML_Close_LoadFile( pp::XMLHandler* xmlHandler )
{
	delete xmlHandler;
	return true;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class PreDocumentPrivate
{
public:
	Assembly*	_assembly;
	
	//Assembly*	_activeAssembly;
	bool		_undoable;
	bool		_autoUpdateView;
	std::stack<BaseItem*> _activeItemQueue;
	// undo 
	QUndoStack*	_undoStack;


	PreDocumentPrivate()
		:_undoable(true)
		,_autoUpdateView(true)
		,_assembly(new Assembly())
	{
		_undoStack=new QUndoStack();
		_activeItemQueue.push(_assembly);
	}

	~PreDocumentPrivate()
	{
		delete _undoStack;
	}
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ModelDocument::ModelDocument()
	:_ptr(new PreDocumentPrivate())
	,_enableSignal(true)
{
}

ModelDocument::~ModelDocument(void)
{
}

Assembly* ModelDocument::getAssembly()
{
	return (_ptr->_assembly);
}

void ModelDocument::setAssembly( Assembly* asembly )
{
	if(_ptr->_assembly)
	{
		delete _ptr->_assembly;
		_ptr->_activeItemQueue.pop();
	}

	_ptr->_assembly=asembly;
	_ptr->_activeItemQueue.push(asembly);
}

BaseItem* ModelDocument::getActiveItem()
{
	return _ptr->_activeItemQueue.top();
}

void ModelDocument::debug_example1()
{
	//my_debug_example(getAssembly());
}

bool ModelDocument::insertChild( BaseItem* parent,BaseItem* item,int pos )
{
	bool re=PREI_Add_Item(parent,item,pos);
	if(re)
		notifyItemAdded(item,true);
	return re;
}

bool ModelDocument::remove( BaseItem* item,bool deleteIt )
{
	notifyBeginItemRemoving(item);
	BaseItem* parent=item->getParent();
	bool re=PREI_Remove_Item(item,false);
	if(re){
		notifyItemRemoved(parent,item);
		if(deleteIt)
			PREI_Delete_Item(item);
	}
	return re;
}

bool ModelDocument::modify( BaseItem* src,BaseItem* dst )
{
	bool re=PREI_Modify_Item(src,dst);
	if(re){
		notifyItemModified(dst,false);
		if(dst->getCategory()==TDY_PRE_CATE_PARAMETERS)
			notifyParametersChanged(dst);
	}
	return re;
}

QUndoStack* ModelDocument::getUndoStack()
{
	return _ptr->_undoStack;
}


void ModelDocument::pushCommand( QUndoCommand* command )
{
	_ptr->_undoStack->push(command);
}

void ModelDocument::update()
{
	notifyModelReseted(getActiveItem());
}

bool ModelDocument::getUndoable()
{
	return _ptr->_undoable;
}

void ModelDocument::setUndoable( bool b )
{
	_ptr->_undoable=b;
}

void ModelDocument::pushActiveItem( BaseItem* item )
{
	BaseItem* curr=getActiveItem();
	if(item==curr)
		return;
	else{
		notifyBeginRootItemChanging(curr,item);
		_ptr->_activeItemQueue.push(item);
		notifyRootItemChanged(item,curr);
	}
}

void ModelDocument::popActiveItem()
{
	int s=_ptr->_activeItemQueue.size();
	if(s<2)
		return;
	else{
		BaseItem* be=_ptr->_activeItemQueue.top();
		_ptr->_activeItemQueue.pop();
		notifyRootItemChanged(_ptr->_activeItemQueue.top(),be);
	}
}



BaseItem* ModelDocument::findItem( const QString& absoluteName,Assembly* baseAssembly )
{
	QStringList vec=absoluteName.split('.',QString::SkipEmptyParts);
	BaseItem* item=baseAssembly?baseAssembly:this->getAssembly();
	for(int i=0;i<vec.size();++i)
	{
		item=item->child(vec[i]);
		if(!item)
			return NULL;
	}
	return item;
}

BaseItem* _findItemWithoutFolder(const QStringList& vec,BaseItem* item,int index)
{
	if(index==vec.size())
		return item;

	int s=item->count();
	for(int i=0;i<s;++i)
	{
		BaseItem* c=item->child(i);
		if((c->getCategory()==TDY_PRE_CATE_FOLDER)
			|| (c->getCategory()==TDY_PRE_CATE_GROUND)){
			BaseItem* a= _findItemWithoutFolder(vec,c,index);
			if(a)
				return a;
			continue;
		}
		if(!c->compareKeyname(vec[index]))
			return _findItemWithoutFolder(vec,c,index+1);
	}
	return NULL;
}





BaseItem* ModelDocument::findItemWithoutFolder( const QString& name,Assembly* baseAssembly )
{
	QStringList vec=name.split('.',QString::SkipEmptyParts);
	BaseItem* item=baseAssembly?baseAssembly:this->getAssembly();
	return _findItemWithoutFolder(vec,item,0);
}


bool ModelDocument::save( const QString& fileName )
{
	notifyBeginSavingDocument();

	XMLHandler* xmlHandler;
	DataStreamWriter* dataWriter;
	if(!PP_XML_Open_SaveFile(fileName,&xmlHandler,&dataWriter)){
		Base::Console().Error("Save model failed.");
		return false;
	}

	JXMLItem xmlRoot=xmlHandler->GetRoot();
	JXMLItem xmlEasyPlot=xmlHandler->GetFirstChild(xmlRoot);

	if(!xmlRoot || !xmlEasyPlot)
		return false;



	// save model
	JXMLItem model=xmlHandler->AddChild(xmlEasyPlot,"MODEL");
	JXMLItem mainModel=xmlHandler->AddChild(model,"MAIN");
	myModelDataXMLExchange()->save(xmlHandler,dataWriter,mainModel);

	
	PP_XML_Close_SaveFile(fileName,xmlHandler,dataWriter);

	notifyEndSavingDocument();
	return true;
}

bool ModelDocument::save( XMLHandler* xmlHandlerx,DataStreamWriter* dataWriter )
{
	notifyBeginSavingDocument();
	XMLHandler& xmlHander=*xmlHandlerx;

	JXMLItem xmlRoot=xmlHander.GetRoot();
	JXMLItem xmlEasyPlot=xmlHander.GetFirstChild(xmlRoot);

	if(!xmlRoot || !xmlEasyPlot)
		return false;


	// save model
	JXMLItem model=xmlHander.AddChild(xmlEasyPlot,"MODEL");
	JXMLItem mainModel=xmlHander.AddChild(model,"MAIN");
	myModelDataXMLExchange()->save(&xmlHander,dataWriter,mainModel);

	notifyEndSavingDocument();
	return true;
}

bool ModelDocument::load( const QString& fileName )
{
	XMLHandler* xmlHandler;
	if(!PP_XML_Open_LoadFile(fileName,&xmlHandler))
		return false;

	load(xmlHandler);

	PP_XML_Close_LoadFile(xmlHandler);
	return true;
}

bool ModelDocument::load( pp::XMLHandler* xmlHandler )
{
	XMLHandler& xmlHander=*xmlHandler;
	JXMLItem xmlRoot=xmlHander.GetRoot();
	JXMLItem xmlEasyPlot=xmlHander.GetFirstChild(xmlRoot);
	JXMLItem xmlModel=xmlHander.FindSingleItem(xmlEasyPlot,"MODEL");
	JXMLItem xmlMainModel=xmlHander.FindSingleItem(xmlModel,"MAIN");

	if(!xmlRoot || !xmlEasyPlot || !xmlModel || !xmlMainModel)
		return false;

	QString bulkFileFile=xmlHander.GetAttribString(xmlEasyPlot,"BULKFILE");
	DataStreamReader bulkReader;
	if(!bulkFileFile.isEmpty())
	{
		QFileInfo bulkFileInfo(bulkFileFile);
		bulkReader.addFile(bulkFileInfo.absoluteFilePath());
	}

	Base::Console().Log("Block size = %d",bulkReader.getBlockCount());

	clearModel();
	ModelDataXMLExchange* modelExchange=myModelDataXMLExchange();
	bool result=modelExchange->load(&xmlHander,&bulkReader,xmlMainModel);
	notifyModelReseted(_ptr->_assembly);
	return result;
}

void ModelDocument::clearModel()
{
	_ptr->_assembly->clearChildren();
	_ptr->_undoStack->clear();
}

void ModelDocument::createDefault()
{
	this->clearModel();
	_ptr->_assembly->createDefault();
	_ptr->_assembly->setKeyname("Model");
	notifyModelReseted(_ptr->_assembly);
}

void ModelDocument::reset()
{
	notifyModelReseted(getActiveItem());
}

ITreeItemPropertyFunc* ModelDocument::getTreeItemProperties()
{
	static DocumentTreeItemProperties treeItemProperties;
	return &treeItemProperties;
}

//ComTreeModel* PreDocument::getComTreeModel()
//{
//	if(!_ptr->_comTreeModel){
//		ComTreeModel* model=new ComTreeModel(0);
//		_ptr->_comTreeModel=model;
//		model->setRootNode(this->getAssembly());
//	}
//	return _ptr->_comTreeModel;	
//}

void ModelDocument::attachListener( ModelDocumentListener* listener )
{
	int i=_listenerList.indexOf(listener);
	if(i!=-1)
		return;

	for(ListenerList::Iterator b=_listenerList.begin();b!=_listenerList.end();++b)
	{
		if((*b)->getPriority()<listener->getPriority()){
			_listenerList.insert(b,listener);
			return;
		}
	}

	_listenerList.push_back(listener);
}

void ModelDocument::disattachListener( ModelDocumentListener* listener )
{
	_listenerList.removeAll(listener);
}

void ModelDocument::notifyBeginItemAdding( BaseItem* item,BaseItem* parent,int pos )
{
	if(!_enableSignal)
		return;
	foreach(ModelDocumentListener* l,_listenerList){
		l->doc_BeginItemAdding(item,parent,pos);
	}
}

void ModelDocument::notifyItemAdded( BaseItem* item,bool isIncludingChildren )
{
	if(!_enableSignal)
		return;
	foreach(ModelDocumentListener* l,_listenerList){
		l->doc_ItemAdded(item,isIncludingChildren);
	}
}

void ModelDocument::notifyItemModified( BaseItem* item,bool isIncludingChildren )
{
	if(!_enableSignal)
		return;
	foreach(ModelDocumentListener* l,_listenerList){
		l->doc_ItemModified(item,isIncludingChildren);
	}
}

void ModelDocument::notifyBeginItemRemoving( BaseItem* item )
{
	if(!_enableSignal)
		return;
	foreach(ModelDocumentListener* l,_listenerList){
		l->doc_BeginItemRemoving(item);
	}
}

void ModelDocument::notifyItemRemoved( BaseItem* parent,BaseItem* item )
{
	if(!_enableSignal)
		return;
	foreach(ModelDocumentListener* l,_listenerList){
		l->doc_ItemRemoved(parent,item);
	}
}

void ModelDocument::notifyModelReseted( BaseItem* rootItem )
{
	if(!_enableSignal)
		return;
	foreach(ModelDocumentListener* l,_listenerList){
		l->doc_ModelReseted(rootItem);
	}
}

void ModelDocument::notifyBeginRootItemChanging( BaseItem* currentRoot,BaseItem* newRoot )
{
	if(!_enableSignal)
		return;
	foreach(ModelDocumentListener* l,_listenerList){
		l->doc_BeginRootItemChanging(currentRoot,newRoot);
	}
}

void ModelDocument::notifyRootItemChanged( BaseItem* currentRoot,BaseItem* oldRoot )
{
	if(!_enableSignal)
		return;
	foreach(ModelDocumentListener* l,_listenerList){
		l->doc_RootItemChanged(currentRoot,oldRoot);
	}
}

void ModelDocument::notifyParametersChanged( BaseItem* parametersItem )
{
	if(!_enableSignal)
		return;
	foreach(ModelDocumentListener* l,_listenerList){
		l->doc_ParametersChanged(parametersItem);
	}
}

void ModelDocument::notifyBeginSavingDocument()
{
	if(!_enableSignal)
		return;
	foreach(ModelDocumentListener* l,_listenerList){
		l->doc_BeginSavingDocument();
	}
}

void ModelDocument::notifyEndSavingDocument()
{
	if(!_enableSignal)
		return;
	foreach(ModelDocumentListener* l,_listenerList){
		l->doc_EndSavingDocument();
	}
}

}
