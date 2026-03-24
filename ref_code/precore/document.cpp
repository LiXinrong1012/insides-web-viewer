#include "document.h"

#include "base/Console.h"
#include "base/MultiProgressOperator.h"

#include "precore/modeldocument.h"
#include "precore/ResultDocument.h"

#include "pp_xml/XMLHandler.h"
#include "pp_xml/DataStreamReader.h"
#include "pp_xml/DataStreamWriter.h"

#include "projectselector.h"

using namespace pp;
using namespace Base;


namespace INSIDES
{
Document::Document(QObject *parent)
	: QObject(parent)
{
	_preDocument=new ModelDocument();
	_resultDocument=new ResultDocument();
}

Document::~Document()
{
}


bool Document::save( const QString& fileName,bool saveResult )
{
	XMLHandler* xmlHandler;
	DataStreamWriter* dataWriter;
	if(!PP_XML_Open_SaveFile(fileName,&xmlHandler,&dataWriter)){
		Base::Console().Error("Save model failed.");
		return false;
	}

	MultiProgressOperator::startProgress("saving model");
	_preDocument->save(xmlHandler,dataWriter);
	MultiProgressOperator::stopProgress();

	MultiProgressOperator::startProgress("saving result");
	_resultDocument->save(xmlHandler,"a");
	MultiProgressOperator::stopProgress();

	PP_XML_Close_SaveFile(fileName,xmlHandler,dataWriter);

	return true;
}

bool Document::load( const QString& fileName, bool loadResult )
{
	XMLHandler* xmlHandler;
	if(!PP_XML_Open_LoadFile(fileName,&xmlHandler))
		return false;

	_preDocument->load(xmlHandler);
	_resultDocument->load(xmlHandler);

	PP_XML_Close_LoadFile(xmlHandler);

	return false;
}

void Document::onGoInto()
{
	const BaseItemSelection& items=ProjectSelector::instance()->getSelection();
	if(items.size()==0)
		return;
	if(items[0]->isPartOrAssembly())
		//todo: 判断合适的进入方法。2014.2.26
	{
		ModelDocument* doc=this->getDocument();
		doc->pushActiveItem(items[0]);
	}
}

void Document::onGoOut()
{
	ModelDocument* doc=getDocument();
	doc->popActiveItem();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
MultiDocuments* MultiDocuments::_instance=NULL;

MultiDocuments::MultiDocuments()
	:QObject(NULL)
	,_activeDocument(NULL)
{
}

MultiDocuments* MultiDocuments::instance()
{
	if(!_instance){
		_instance=new MultiDocuments();
		Document* document=new Document(_instance);
		_instance->_documents.push_back(document);
		_instance->_activeDocument=document;
	}
		
	return _instance;
}

void MultiDocuments::destruct()
{
	if(_instance)
		delete _instance;
	_instance=NULL;
}

Document* MultiDocuments::getActiveDocument()
{
	return _activeDocument;
}

void MultiDocuments::notifyDisableUIUpdating( bool b )
{
	emit disableUIUpdating(b);
}

}