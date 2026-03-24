#include "ModelDataXMLExchange.h"
#include "precore/modeldocument.h"
#include "precore/itemlist.h"
#include "precore/precore_data.h"
#include "precore/UAPI_.h"
#include "base/Console.h"
#include "base/ItemProperties.h"

#include "pp_xml/XMLHandler.h"
#include "pp_xml/DataStreamReader.h"
#include "pp_xml/DataStreamWriter.h"
#include "pretdy/TDYParameters.h"
#include "BaseItemFactory.h"

using namespace pp;


namespace INSIDES
{



////////////////////////////////////////////////////////////////////////////////
//  Functions: save base item into file
static bool g_saveIncludeItem(XMLHandler* handler,DataStreamWriter* bulkFile,
	pp::JXMLItem itemNode,BaseItem* item)
{
	handler->SetAttribString(itemNode,"NAME",item->getKeyName());
	handler->SetAttribString(itemNode,"PARENT",item->getParent()->getFullName());
	handler->SetAttribLong(itemNode,"CATEGORY",item->getCategory());
	handler->SetAttribLong(itemNode,"ID",item->getID());
	handler->SetAttribLong(itemNode,"FLAGS",item->getFlags());

	handler->SetAttribLong(itemNode,"HASPROPERTIES",0);
	int bId=bulkFile->nextUniqueID();
	bulkFile->startBlock(bId);
	(*bulkFile->getDataStream())<<*item->getAppearance();
	bulkFile->stopBlock();
	handler->SetAttribLong(itemNode,"APPEARANCE",bId);

	return true;
}

static bool g_saveBaseItem( XMLHandler* handler, DataStreamWriter* bulkFile,
	pp::JXMLItem itemNode,BaseItem* item )
{
	handler->SetAttribString(itemNode,"NAME",item->getKeyName());
	handler->SetAttribString(itemNode,"PARENT",item->getParent()->getFullName());
	handler->SetAttribLong(itemNode,"CATEGORY",item->getCategory());
	handler->SetAttribLong(itemNode,"ID",item->getID());
	handler->SetAttribLong(itemNode,"FLAGS",item->getFlags());

	bool hasProperties=item->getProperties()!=0;
	handler->SetAttribLong(itemNode,"HASPROPERTIES",hasProperties?1:0);
	int bId=bulkFile->nextUniqueID();
	bulkFile->startBlock(bId);
	if(hasProperties)
		(*bulkFile->getDataStream())<<*item->getProperties();
	(*bulkFile->getDataStream())<<*item->getAppearance();
	bulkFile->stopBlock();
	handler->SetAttribLong(itemNode,"APPEARANCE",bId);

	return true;
}

static bool g_saveParametersItem(XMLHandler* handler,DataStreamWriter* bulk,
	pp::JXMLItem itemNode,BaseItem* item)
{
	if(!g_saveBaseItem(handler,bulk,itemNode,item))
		return false;

	ParametersBaseItem* parasItem=(ParametersBaseItem*)item;
	const TDYParameters* paras=parasItem->getParameters();
	if(paras){
		quint32 id=bulk->nextUniqueID();
		bulk->startBlock(id);
		(*bulk->getDataStream())<<*paras;
		bulk->stopBlock();
		handler->SetAttribLong(itemNode,"PARAMETERS",id);
	}
	return true;
}

static bool g_saveFEMBaseItem(XMLHandler* handler,DataStreamWriter* bulk,
	pp::JXMLItem itemNode,BaseItem* item)
{
	if(!g_saveBaseItem(handler,bulk,itemNode,item))
		return false;

	FEMPartBaseItem* femBaseItem=(FEMPartBaseItem*)item;
	JFEMPart* part=femBaseItem->getFEMPart();

	quint32 id=bulk->nextUniqueID();
	bulk->startBlock(id);
	part->m_Mesh.WriteData(bulk->getDataStream());
	bulk->stopBlock();
	handler->SetAttribLong(itemNode,"MESH",id);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//	Functions: load base item from file
static bool g_loadBaseItem(pp::XMLHandler* handler,DataStreamReader*bulkFile,
		JXMLItem itemNode,BaseItem* item)
{
	QString name=handler->GetAttribString(itemNode,"NAME");
	unsigned long flags=(unsigned long)handler->GetAttribLong(itemNode,"FLAGS",0);
	int id=handler->GetAttribLong(itemNode,"ID");
	int hasProperties=handler->GetAttribLong(itemNode,"HASPROPERTIES");
	item->setKeyname(name);
	item->setFlags(flags);
	item->setID(id);

	int bId=handler->GetAttribLong(itemNode,"APPEARANCE");
	if(bId!=0){
		DataBlock *b=bulkFile->findBlock(bId);
		b->fileHandler->device()->seek(b->startPos);
		if(hasProperties){
			Base::ItemProperties* properties=new Base::ItemProperties();
			(*b->fileHandler)>>*(properties);
			item->setProperties(properties);
		}
		(*b->fileHandler)>>*(item->getAppearance());
	}

	//if(item->isInstance())
		//item->updateInstance();

	return true;
}

static bool g_loadIncludeItem(pp::XMLHandler* handler,DataStreamReader*bulkFile,
	JXMLItem itemNode,BaseItem* item)
{
	unsigned long flags=(unsigned long)handler->GetAttribLong(itemNode,"FLAGS",0);
	item->setFlags(flags);

	int bId=handler->GetAttribLong(itemNode,"APPEARANCE");
	if(bId!=0){
		DataBlock *b=bulkFile->findBlock(bId);
		b->fileHandler->device()->seek(b->startPos);
		(*b->fileHandler)>>*(item->getAppearance());
	}

	return true;
}

static bool g_loadParametersItem(pp::XMLHandler* handler,DataStreamReader*bulkFile,
	JXMLItem itemNode,BaseItem* item)
{
	g_loadBaseItem(handler,bulkFile,itemNode,item);
	long parametersDataId=handler->GetAttribLong(itemNode,"PARAMETERS");
	if(parametersDataId!=0){
		DataBlock* block=bulkFile->findBlock(parametersDataId);
		QDataStream* s=block->fileHandler;
		s->device()->seek(block->startPos);
		TDYParameters* paras=new TDYParameters();
		(*s)>>(*paras);
		ParametersBaseItem* paraItem=(ParametersBaseItem*)item;
		paraItem->setTDYParameters(paras);
	}

	return true;
}

static bool g_loadFEMBaseItem(pp::XMLHandler* handler,DataStreamReader*bulkFile,
	JXMLItem itemNode,BaseItem* item)
{
	g_loadBaseItem(handler,bulkFile,itemNode,item);
	long meshID=handler->GetAttribLong(itemNode,"MESH");
	if(meshID!=0){
		DataBlock* block=bulkFile->findBlock(meshID);
		QDataStream* s=block->fileHandler;
		s->device()->seek(block->startPos);
		FEMPartBaseItem* femBaseItem=(FEMPartBaseItem*)item;
		JMesh* mesh=&femBaseItem->getFEMPart()->m_Mesh;
		mesh->LoadData(s);
		JMeshGroup* group=femBaseItem->getFEMPart()->m_Group.createMeshGroup(mesh);
		group->Full(true);
		group->CreateFace();
		group->CreateLine();
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//	ModelDataXMLExchange class implementation
ModelDataXMLExchange::ModelDataXMLExchange(void)
	:_doc(NULL)
{
	initialize();
}


ModelDataXMLExchange::~ModelDataXMLExchange(void)
{
}

void ModelDataXMLExchange::initialize()
{
	_doc=myDocument();
	//_saveEntityFunctionMap[TDY_PRE_ITEMCLASS_BASEITEM]=g_saveBaseItem;
	//_loadEntityFunctionMap[TDY_PRE_ITEMCLASS_BASEITEM]=g_loadBaseItem;

	//_saveEntityFunctionMap[TDY_PRE_ITEMCLASS_MBASEITEM]=g_saveBaseItem;
	//_loadEntityFunctionMap[TDY_PRE_ITEMCLASS_MBASEITEM]=g_loadBaseItem;

	//_loadEntityFunctionMap[TDY_PRE_ITEMCLASS_MBASEITEM]=g_loadBaseItem;
	
	_saveEntityFunctionMap[TDY_PRE_CATE_PARAMETERS]=g_saveParametersItem;
	_loadEntityFunctionMap[TDY_PRE_CATE_PARAMETERS]=g_loadParametersItem;

	_saveEntityFunctionMap[TDY_PRE_CATE_FEMPART]=g_saveFEMBaseItem;
	_loadEntityFunctionMap[TDY_PRE_CATE_FEMPART]=g_loadFEMBaseItem;

}

ModelDataXMLExchange* ModelDataXMLExchange::instance()
{
	static ModelDataXMLExchange* _instance=NULL;
	if(!_instance)
		_instance=new ModelDataXMLExchange();
	return _instance;
}

bool ModelDataXMLExchange::save( XMLHandler* handler, DataStreamWriter* bulkFile,pp::JXMLItem xmlNode )
{
	ModelDocument* doc=myDocument();
	BaseItem* item=doc->getAssembly();
	int n=item->count();

	Save_Load_Global_Status saveStatus;
	saveStatus.xmlHandler=handler;
	saveStatus.dataWriter=bulkFile;

	for(int i=0;i<n;++i)
	{
		saveStatus.parentXMLNode=xmlNode;
		BaseItem* child=item->child(i);
		if(!saveItem(saveStatus,child)){
			Base::Console().Error("Error occurred when trying to save model.");
			return false;
		}
	}
	return true;
}


bool ModelDataXMLExchange::saveItem( Save_Load_Global_Status& saveStatus,BaseItem* item )
{
	XMLHandler* handler=saveStatus.xmlHandler;
	JXMLItem parentXmlNode=saveStatus.parentXMLNode;
	DataStreamWriter* bulkFile=saveStatus.dataWriter;

	JXMLItem currXMLNode=handler->AddChild(parentXmlNode,"ITEM");
	if(item->getIncluded())
	{
		g_saveIncludeItem(handler,bulkFile,currXMLNode,item);
	}
	else{
		// write this item
		SaveEntityMap::iterator f=_saveEntityFunctionMap.find(item->getCategory());

		save_entity_function func=NULL;
		if(f==_saveEntityFunctionMap.end())	//使用最基本模式
			func=g_saveBaseItem;
		else
			func=*f->second;

		bool b=func(handler,bulkFile,currXMLNode,item);
		if(!b){
			return false;
		}
	}

	// write child item
	int n=item->count();
	for(int i=0;i<n;++i){
		saveStatus.parentXMLNode=currXMLNode;
		bool re=saveItem(saveStatus,item->child(i));
		if(!re)
			return false;
	}
	return true;
}

bool ModelDataXMLExchange::load( pp::XMLHandler* handler, DataStreamReader* bulkHandler, pp::JXMLItem parentNode )
{
	bool result=true;
	JXMLItem child=handler->GetFirstChild(parentNode);
	
	Save_Load_Global_Status loadStatus;
	BaseItem* baseItem=myDocument()->getAssembly();
	loadStatus.xmlHandler=handler;
	loadStatus.dataReader=bulkHandler;
	
	while(child)
	{
		loadStatus.parentItem=baseItem;
		if(!loadItem(loadStatus,child)){
			result=false;
			break;
		}
		child=handler->GetNextSibling(child);
	}

	if(result){ // load successfully

		return true;
	}
	else{
		Base::Console().Error("Error occurred when loading file...");
		return false;
	}
}


static bool _get_is_included_from_flags(long flags)
{
	std::bitset<16> tmp((unsigned long long)flags);
	return tmp[1];
}

bool ModelDataXMLExchange::loadItem(Save_Load_Global_Status& loadStatus,
	pp::JXMLItem xmlNode)
{
	// 1. 是否是实例的条目
	// 1. 是：只把需要读的读下来
	// 2. 否：生成条目，根据具体类型具体处理

	XMLHandler* handler=loadStatus.xmlHandler;
	BaseItem* currBaseItem=NULL;
	int flags=handler->GetAttribLong(xmlNode,"FLAGS");
	bool isIncluded=_get_is_included_from_flags(flags);
	if(isIncluded){
		QString name=handler->GetAttribString(xmlNode,"NAME");
		currBaseItem=loadStatus.parentItem->child(name);
		if(!currBaseItem){
			Base::Console().Error("Failed to find item: %s, parent name = %s",
				name.toStdString().c_str(),
				loadStatus.parentItem->getKeyName().toStdString().c_str());
			return true;
		}

		g_loadIncludeItem(loadStatus.xmlHandler,loadStatus.dataReader,
			xmlNode,currBaseItem);
	}
	else{
		currBaseItem=createBaseItem(handler,xmlNode);
		if(!currBaseItem)
			return false;

		LoadEntityMap::iterator f=_loadEntityFunctionMap.find(currBaseItem->getCategory());
		load_entity_function func=NULL;
		if(f==_loadEntityFunctionMap.end())	//使用最基本模式
			func=g_loadBaseItem;
		else
			func=*f->second;

		bool b=func(handler,loadStatus.dataReader,xmlNode,currBaseItem);
		if(!b){
			delete currBaseItem;
			return false;
		}
		// 处理parent
		PREI_Add_Item(loadStatus.parentItem,currBaseItem);
	}


	JXMLItem child=handler->GetFirstChild(xmlNode);
	if(!currBaseItem)
		return true;

	while(child)
	{
		loadStatus.parentXMLNode=xmlNode;
		loadStatus.parentItem=currBaseItem;
		if(!loadItem(loadStatus,child)){
			break;
		}
		child=handler->GetNextSibling(child);
	}
	return true;
}


BaseItem* ModelDataXMLExchange::createBaseItem( pp::XMLHandler* handler,pp::JXMLItem xmlNode )
{


	int category=handler->GetAttribLong(xmlNode,"CATEGORY");
	BaseItem* newItem=NULL;

	newItem=(BaseItem*)BaseItemFactory()->Produce(category);

	if(!newItem){
		Base::Console().Error("Unknown item category: %d",category);
	}
	else{
		newItem->setCategory(category);
	}
	return newItem;
}


}
