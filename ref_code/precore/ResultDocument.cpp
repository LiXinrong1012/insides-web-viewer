#include "ResultDocument.h"
#include "EasyResults.h"

#include "MyAnimationControler.h"
#include "Base/activeviewobject.h"
#include "Base/Console.h"

#include <QtCore>
#include <QPluginLoader>
#include <QDir>

#include "include/IExchangeResults.h"

#include "pp_xml/XMLHandler.h"
#include "pp_xml/DataStreamReader.h"
#include "pp_xml/DataStreamWriter.h"

#include "ResultExchangeVersion1_0.h"
#include "JResults.h"

using namespace Base;
using namespace pp;


namespace INSIDES
{

ResultDocument::ResultDocument()
	:_results(NULL)
	,_emitMessage(true)
{
	_resultControler=new MyAnimationControler(this);
	ActiveViewObject::instance()->setAnimationControler(_resultControler);
}


ResultDocument::~ResultDocument(void)
{
	delete _results;
	ActiveViewObject::instance()->setAnimationControler(NULL);
	delete _resultControler;
}

IResults* ResultDocument::createDefaultResults()
{
	//EasyResults* results=new EasyResults();
	//TDYResults* results=new TDYResults();
	return NULL;

	notifyResultsLoaded(_results);
	return _results;
}

void ResultDocument::attachListener( IResultListener* x )
{
	int i=_listeners.indexOf(x);
	if(i!=-1)
		return;

	for(ListenerList::Iterator b=_listeners.begin();b!=_listeners.end();++b)
	{
		if((*b)->getPriority()<x->getPriority()){
			_listeners.insert(b,x);
			return;
		}
	}

	_listeners.push_back(x);
}

void ResultDocument::disattachListener( IResultListener* x )
{
	_listeners.removeOne(x);
}



void ResultDocument::notifyListeners()
{
	foreach(IResultListener* l,_listeners){
		l->onResultCurrentFrameChanged();
	}
}

void ResultDocument::clear()
{
	if(_results){
		notifyResultsBeginDeleting();

		delete _results;
		_results=NULL;

		notifyResultsDeleted();
	}
}

IResults* ResultDocument::loadTDYResults()
{
	QDir pluginsDir(qApp->applicationDirPath());

	pluginsDir.cd("plugins");
	QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("importtdyresult.dll"));
	QObject *plugin = pluginLoader.instance();
	if (plugin && qobject_cast<IExchangeResults*>(plugin)) {
		IExchangeResults*  _importTDYResults= qobject_cast<IExchangeResults*>(plugin);
		clear();
		_results=_importTDYResults->createResults();
		if(_results){
			_results->init();

			Base::ActiveViewObject::instance()->setModelStatus(Base::ActiveViewObject::MODEL_STASTUS_DYNAMIC);
			notifyResultsLoaded(_results);
		}
		return _results;
	}
	else
		Base::Console().Error("Load importtdy.dll failed: %s",pluginLoader.errorString().toStdString().c_str());

	return NULL;
}

IResults* ResultDocument::loadTDYEigResults()
{
	QDir pluginsDir(qApp->applicationDirPath());

	pluginsDir.cd("plugins");
	QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("importtdyeigresult.dll"));
	QObject *plugin = pluginLoader.instance();
	if (plugin && qobject_cast<IExchangeResults*>(plugin)) {
		IExchangeResults*  _importTDYResults= qobject_cast<IExchangeResults*>(plugin);
		clear();
		_results=_importTDYResults->createResults();
		if(_results){
			_results->init();

			Base::ActiveViewObject::instance()->setModelStatus(Base::ActiveViewObject::MODEL_STATUS_EIGEN);
			notifyResultsLoaded(_results);
		}
		return _results;
	}
	else
		Base::Console().Error("Load importtdy.dll failed: %s",pluginLoader.errorString().toStdString().c_str());

	return NULL;
}

bool ResultDocument::save( pp::XMLHandler* xmlHandlerx,const QString& baseName )
{
	if(!_results)
		return true;

	XMLHandler& xmlHander=*xmlHandlerx;

	JXMLItem xmlRoot=xmlHander.GetRoot();
	JXMLItem xmlEasyPlot=xmlHander.GetFirstChild(xmlRoot);

	if(!xmlRoot || !xmlEasyPlot)
		return false;

	QSharedPointer<DataStreamWriter> dataWriter=QSharedPointer<DataStreamWriter>(new DataStreamWriter());
	dataWriter->open(baseName+".post");

	// save model
	JXMLItem model=xmlHander.AddChild(xmlEasyPlot,"RESULTS");
	JXMLItem mainModel=xmlHander.AddChild(model,"MAIN");
	// write general information
	int frameCount=_results->getFrameCount();
	xmlHander.SetAttribLong(mainModel,"FRAMECOUNT",frameCount);
	xmlHander.SetAttribLong(mainModel,"RESULTCOUNT",_results->getResultCount());


	ResultExchangeVersion1_0 resultExchangeV1_1;

	int infoId=dataWriter->nextUniqueID();
	dataWriter->startBlock(infoId);
	resultExchangeV1_1.saveGeneralInfo(myResultDocument()->getResults(),dataWriter);
	dataWriter->stopBlock();
	xmlHander.SetAttribLong(mainModel,"GENERALINFO",infoId);


	int dataId=dataWriter->nextUniqueID();
	dataWriter->startBlock(dataId);
	resultExchangeV1_1.save(myResultDocument()->getResults(),dataWriter);
	dataWriter->stopBlock();
	xmlHander.SetAttribLong(mainModel,"DATA",dataId);

	return true;
}

bool ResultDocument::load( pp::XMLHandler* xmlHandler )
{
	clear();

	JXMLItem xmlRoot=xmlHandler->GetRoot();
	JXMLItem xmlEasyPlot=xmlHandler->GetFirstChild(xmlRoot);
	JXMLItem xmlModel=xmlHandler->FindSingleItem(xmlEasyPlot,"RESULTS");
	JXMLItem xmlMainModel=xmlHandler->FindSingleItem(xmlModel,"MAIN");

	QString fileName="a.post";
	QSharedPointer<DataStreamReader> fin(new DataStreamReader());
	fin->addFile(fileName);

	ResultExchangeVersion1_0 resultExchangeV1_1;

	long generalInfoId=xmlHandler->GetAttribLong(xmlMainModel,"GENERALINFO");
	long dataId=xmlHandler->GetAttribLong(xmlMainModel,"DATA");
	DataBlock* generalInfoBlock=fin->findBlock(generalInfoId);
	generalInfoBlock->resetPos();
	JResults* results=(JResults*)resultExchangeV1_1.loadGeneralInfo(generalInfoBlock);
	if(!results)
		return true;

	results->setDataReader(fin);
	DataBlock* dataBlock=fin->findBlock(dataId);
	dataBlock->resetPos();
	resultExchangeV1_1.load(results,dataBlock);

	_results=results;

	Base::ActiveViewObject::instance()->setModelStatus(Base::ActiveViewObject::MODEL_STASTUS_DYNAMIC);
	notifyResultsLoaded(_results);

	return true;
}

void ResultDocument::notifyResultsBeginDeleting()
{
	if(!_emitMessage)
		return;
	foreach(IResultListener* l,_listeners){
		l->res_ResultsBeginDeleting();
	}
}

void ResultDocument::notifyResultsDeleted()
{
	if(!_emitMessage)
		return;
	foreach(IResultListener* l,_listeners){
		l->res_ResultsDeleted();
	}
}

void ResultDocument::notifyResultsLoaded( IResults* results )
{
	if(!_emitMessage)
		return;
	foreach(IResultListener* l,_listeners){
		l->res_ResultsLoaded(results);
	}
}

}