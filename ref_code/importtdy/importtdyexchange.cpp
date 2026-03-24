#include "importtdyexchange.h"
#include "Base/Console.h"
#include <QtCore>
#include <QtXml/QDomDocument>
#include <QMessageBox>

#include "base/AppConfiguration.h"
#include "base/Console.h"
#include "base/MultiProgressOperator.h"

#include "precore/modeldocument.h"
#include "precore/itemlist.h"
#include "precore/precore_data.h"
#include "precore/UAPI_.h"

#include "thusolver/parsefile/Scanner.h"
#include "thusolver/parsefile/Parser.h"
#include "thusolver/parsefile/TemplateFactory.h"
#include "thusolver/parsefile/Assembly.h"

#include "pp_xml/XMLHandler.h"

#include "ImportTDYImp.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace Base;
using namespace std;
using namespace pp;
using namespace INSIDES;

Q_EXPORT_PLUGIN2(iexchangefile2, ImportTDYExchange);


template <typename T>
string join(const T& v, const string& delim) {
	ostringstream s;
	for (const auto& i : v) {
		if (&i != &v[0]) {
			s << delim;
		}
		s << i;
	}
	return s.str();
}


void ImportTDYExchange::setFileName( const QString& fileName )
{
	_fileName=fileName;
}

void ImportTDYExchange::setExtraParameters( const QList<QString>& extraPara )
{

}

static void _setCollapseStatus(INSIDES::Assembly* assem)
{
	int n=assem->getInstances()->count();
	for(int i=0;i<n;++i){
		BaseItem* item=assem->getInstances()->child(i);
		if(item->getCategory()==TDY_PRE_CATE_ASSEMBLY)
			_setCollapseStatus(static_cast<PreAssembly*>(item));
	}

	n=assem->getAssemblies()->count();
	for(int i=0;i<n;++i){
		BaseItem* item=assem->getAssemblies()->child(i);
		if(item->getCategory()==TDY_PRE_CATE_ASSEMBLY)
			_setCollapseStatus(static_cast<PreAssembly*>(item));
	}

	assem->getParts()->setCollapsed(true);
	assem->getAssemblies()->setCollapsed(true);
	assem->getConstraints()->setCollapsed(true);
	assem->getLoads()->setCollapsed(true);
	assem->getContacts()->setCollapsed(true);
	assem->getSets()->setCollapsed(true);
	assem->getInstances()->setCollapsed(false);

	n=assem->getInstances()->count();
	for(int i=0;i<n;++i)
		assem->getInstances()->child(i)->setCollapsed(true);

	n=assem->getAssemblies()->count();
	for(int i=0;i<n;++i){
		assem->getAssemblies()->child(i)->setCollapsed(false);
	}
}

static void _setCollapseStatus()
{
	ModelDocument* doc=myDocument();
	PreAssembly* assem=doc->getAssembly();
	_setCollapseStatus(assem);
}

bool ImportTDYExchange::doJob()
{
	Console().Log("ImportTDY, filename = %s",_fileName.toStdString().c_str());

	static bool hasLoadTemplate=false;
	if(!hasLoadTemplate){
		//loadTemplate();
		if(importTemplate())
			hasLoadTemplate=true;
	}
	if(!hasLoadTemplate)
		return false;


	ModelDocument* doc=myDocument();
	doc->setEnableSignal(false);
	doc->createDefault();




	MultiProgressOperator::setProgress(5);

	Console().Log("Finished loading tdy_template.xml");


	QString fileName=AppConfiguration::instance()->workingDirectory()+_fileName;
	QDir::setCurrent(AppConfiguration::instance()->workingDirectory());

	QScopedPointer<Parse::Assembly> parseModel(new Parse::Assembly());

	Parse::Scanner scanner ;
	Parse::Parser parser ;

	TemplateFactory templateFactory ;
	if ( scanner.scan(parseModel.data(), fileName.toStdString().c_str()) != 0 )
	{
		Console().Error(scanner.getErrorMsg().c_str()) ;
		return false ;
	}
	else
	{
		MultiProgressOperator::setProgress(8);
		if ( parser.parse(parseModel.data(), templateFactory.getMap()) != 0 )
		{
			Console().Error(parser.getErrorMsg().c_str()) ;
			return false ;
		}
		MultiProgressOperator::setProgress(10);
	}


	ImportTDYImp imp;
	registerImportFuncs(&imp);
	ImportTDYPara importPara;
	importPara.currentAssembly=myDocument()->getAssembly();
	importPara.doc=myDocument();
	importPara.currentPart=NULL;
	importPara.importTDYImp=&imp;
	processAssembly(parseModel.data(),&importPara);

	QFileInfo info(_fileName);
	QString n=info.fileName();
	
	MultiProgressOperator::setProgress(98);
	myDocument()->getAssembly()->setKeyname(n.replace('.','_'));
	_setCollapseStatus();

	Console().Log("Finished import tdy.");
	MultiProgressOperator::setProgress(100);
	doc->setEnableSignal(true);
	return true;

}

void ImportTDYExchange::clear()
{
}



void ImportTDYExchange::loadTemplate()
{
	QString solverDir=AppConfiguration::instance()->getSolverDirectory();
	QString templateName=solverDir+"tdy_template.xml";
	//templateName="tdy_template.xml";
	TemplateFactory factory;
	char fileName[1024];
	strcpy(fileName,templateName.toStdString().c_str());
	factory.importxml(fileName);
}

static vector<string> QStringList2VectorList(const QString str)
{
	QStringList vec=str.split(",",QString::SkipEmptyParts);
	vector<string> re;
	foreach(const QString& a,vec){
		re.push_back(a.trimmed().toStdString());
	}
	return re;
}
bool ImportTDYExchange::importTemplate()
{
	// 1. 工程目录中找
	// 2. 求解器设置目录中找
	// 3. 后处理启动目录中找
	bool foundFile=false;
	QString templateName;
	QDir tmpDir;
	QString tdyTemplateFileName("tdy_template.xml");

	QStringList dirList;
	dirList<<AppConfiguration::instance()->workingDirectory()
		<<AppConfiguration::instance()->getSolverDirectory()
		<<AppConfiguration::instance()->startupDirectory();
	foreach(QString strDir,dirList){
		if(!strDir.isEmpty()){
			tmpDir.setPath(strDir);
			if(tmpDir.exists(tdyTemplateFileName)){
				templateName=tmpDir.absoluteFilePath(tdyTemplateFileName);
				foundFile=true;
				break;
			}
		}
	}

	if(!foundFile){
		Console().Error("Failed to find tdy_template.xml");
		return false;
	}

	Console().Log("Is importing template file: %s",templateName.toStdString().c_str());

	QDomDocument doc;
	QFile file(templateName);
	if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
		return false;
	
	doc.setContent(file.readAll());

	QDomElement rootElement = doc.firstChildElement();
	QDomElement currElement = rootElement.firstChildElement();
	while(!currElement.isNull())
	{
		QString keyname=currElement.attribute("KEYWORD");
		QString props=currElement.attribute("PROPERTIES");
		QString subitemName=currElement.attribute("SUBITEMNAMES");
		QString shortHelp=currElement.attribute("SHORTHELP");
		QString longhelp=currElement.attribute("LONGHELP");

		Template* t=new Template();
		t->properties=QStringList2VectorList(props);
		t->subitemnames=QStringList2VectorList(subitemName);
		t->shorthelp=shortHelp.toStdString();
		t->longhelp=longhelp.toStdString();

		map_Template* temp_map=TemplateFactory::getMap();
		(*temp_map)[keyname.toStdString()]=t;

		currElement=currElement.nextSiblingElement();
	}
	return true;
}



bool ImportTDYExchange::processAssembly( Parse::Assembly* parseModel, ImportTDYPara* ImpPara)
{
	ImpPara->importTDYImp->processKeyListParameters(ImpPara,parseModel->listKeys);


	map<string,Parse::Part*>& partlist=parseModel->mapParts;
	for(map<string,Parse::Part*>::iterator b=partlist.begin();
		b!=partlist.end();++b)
	{
		Parse::Part* onePart=b->second;
		string partKeyName=onePart->strType;
		LoadPartItemFunc func=ImpPara->importTDYImp->getLoadPartItemFunc(partKeyName.c_str());
		if(func)
			func(ImpPara,onePart);
	}

	map<string,Parse::Assembly*>& assemblyList=parseModel->mapAssemblys;
	for(map<string,Parse::Assembly*>::iterator b=assemblyList.begin();
		b!=assemblyList.end();++b)
	{
		Parse::Assembly* oneAssembly=b->second;
		string partKeyName=oneAssembly->strType;
		Console().Log("Assembly Key name = %s",partKeyName.c_str());

		PreAssembly* assembly=new PreAssembly();
		assembly->createDefault();
		assembly->setKeyname(oneAssembly->strName.c_str());
		BaseItem* assemParent=ImpPara->currentAssembly->getAssemblies();
		PREI_Add_Item(assemParent,assembly);

		PreAssembly* beforeAssem=ImpPara->currentAssembly;
		ImpPara->currentAssembly=assembly;
		processAssembly(oneAssembly,ImpPara);

		ImpPara->currentAssembly=beforeAssem;
	}


	return ImpPara->importTDYImp->processKeyList(ImpPara,parseModel->listKeys,false);

}

QString ImportTDYExchange::getKeyname()
{
	return "TDY_IMPORT";
}



