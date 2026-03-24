#pragma once

#include "pp_xml/XMLHandler.h"

#include <map>
namespace pp{
class XMLHandler;
class DataStreamReader;
class DataStreamWriter;
}

namespace INSIDES
{

class BaseItem;
class ModelDocument;

struct Save_Load_Global_Status 
{
	pp::XMLHandler*	xmlHandler;
	pp::DataStreamWriter*	dataWriter;
	pp::DataStreamReader*	dataReader;
	BaseItem*	parentItem;
	pp::JXMLItem	parentXMLNode;
};

class ModelDataXMLExchange
{
public:
	static ModelDataXMLExchange* instance();

	bool load(pp::XMLHandler* handler, pp::DataStreamReader* bulkHandler, pp::JXMLItem parentNode);
	bool save(pp::XMLHandler* handler, pp::DataStreamWriter* bulkHandler,pp::JXMLItem xmlNode);

private:
	ModelDataXMLExchange(void);
	~ModelDataXMLExchange(void);

	void initialize();
	bool saveItem(Save_Load_Global_Status& saveStatus,BaseItem* item); 

	bool loadItem(Save_Load_Global_Status& loadStatus,pp::JXMLItem xmlNode); 
	BaseItem* createBaseItem(pp::XMLHandler* handler,pp::JXMLItem xmlNode);


	typedef bool (*load_entity_function)(pp::XMLHandler* handler,pp::DataStreamReader* bulkFile,
		pp::JXMLItem xmlNode,BaseItem* item);
	typedef bool (*save_entity_function)(pp::XMLHandler* handler,pp::DataStreamWriter* bulkFile,
		pp::JXMLItem xmlNode,BaseItem* item);

	typedef std::map<int,load_entity_function> LoadEntityMap;
	typedef std::map<int,save_entity_function> SaveEntityMap;

	LoadEntityMap _loadEntityFunctionMap;
	SaveEntityMap _saveEntityFunctionMap;
	ModelDocument*	_doc;
};

inline ModelDataXMLExchange* myModelDataXMLExchange(){return ModelDataXMLExchange::instance();}

}