#include "TypeDataManager.h"
#include "pp_xml/XMLHandler.h"

using namespace pp;

class TypeDataManagerPrivate
{
public:
	typedef std::map<int,TypeData*> TypeDataMap;

	TypeDataMap _dataMap;

	// getters and setters
	TypeData* getTypeData( int typeID );



	void clear();
	bool init(const QString& fileName);
	bool initItem(XMLHandler* handler, JXMLItem typeItem);
};

bool TypeDataManagerPrivate::init(const QString& fileName)
{
	XMLHandler handler;
	bool good=handler.Open(fileName);
	//if(!good)
	//return false;

	JXMLItem xmlRoot=handler.GetRoot();
	JXMLItem xmlConfiguration=handler.GetFirstChild(xmlRoot);
	JXMLItem xmlTypeGroup=handler.GetFirstChild(xmlConfiguration);

	JXMLItem xmlTypeItem=handler.GetFirstChild(xmlTypeGroup);
	while(xmlTypeItem)
	{
		// insert type item
		bool result=initItem(&handler,xmlTypeItem);
		if(!result){
			return false;
		}
		xmlTypeItem=handler.GetNextSibling(xmlTypeItem);
	}
	return true;
}

bool TypeDataManagerPrivate::initItem( XMLHandler* handler, JXMLItem typeItem )
{
	int id=handler->GetAttribLong(typeItem,"ID");
	QString icon=handler->GetAttribString(typeItem,"ICON");
	QString name=handler->GetAttribString(typeItem,"NAME");
	QString TDYName=handler->GetAttribString(typeItem,"TDYKEY");
	QString insIcon=handler->GetAttribString(typeItem,"INSICON");

	TypeData* typeData=new TypeData();
	typeData->typeID=id;
	typeData->icon=icon;
	typeData->insIcon=insIcon;
	typeData->name=name;
	typeData->TDYName=TDYName;
	_dataMap[id]=typeData;

	JXMLItem xmlGroup=handler->GetFirstChild(typeItem);
	while(xmlGroup){
		QString name=handler->GetAttribString(xmlGroup,"NAME");
		TypeDataGroup oneGroup;
		oneGroup.groupName=name;
		
		JXMLItem xmlSingle=handler->GetFirstChild(xmlGroup);
		while(xmlSingle){
			QString keyword=handler->GetAttribString(xmlSingle,"KEYNAME");
			QString text=handler->GetAttribString(xmlSingle,"TEXT");
			QString tip=handler->GetAttribString(xmlSingle,"TIP");
			TypeDataSingleItem singleItem;
			singleItem.keyname=keyword;
			singleItem.displayText=text;
			singleItem.description=tip;
			oneGroup.items.push_back(singleItem);

			xmlSingle=handler->GetNextSibling(xmlSingle);
		}
		typeData->groups.push_back(oneGroup);

		xmlGroup=handler->GetNextSibling(xmlGroup);
	}

	return true;
}

void TypeDataManagerPrivate::clear()
{
	for(TypeDataMap::iterator b=_dataMap.begin();b!=_dataMap.end();++b)
	{
		delete b->second;
	}
	_dataMap.clear();
}

TypeData* TypeDataManagerPrivate::getTypeData( int typeID )
{
	TypeDataMap::iterator f=_dataMap.find(typeID);
	if(f==_dataMap.end())
		return NULL;
	else
		return f->second;
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TypeDataManager* TypeDataManager::_instance=NULL;


TypeDataManager::TypeDataManager(void)
	:_ptr(new TypeDataManagerPrivate())
{
	// only for debug
	//init("D:/model.xml");
	init("settings/configuration.xml");
}


TypeDataManager::~TypeDataManager(void)
{
	clear();
}

TypeDataManager* TypeDataManager::instance()
{
	if(!_instance)
		_instance=new TypeDataManager();
	return _instance;
}


TypeData* TypeDataManager::getTypeData( int typeID )
{
	return _ptr->getTypeData(typeID);
}

void TypeDataManager::clear()
{
	_ptr->clear();
}

bool TypeDataManager::init( const QString& fileName )
{
	return _ptr->init(fileName);
}
