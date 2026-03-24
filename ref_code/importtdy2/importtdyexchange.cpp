#include "importtdyexchange.h"

#include <QtCore>
#include <QtXml/QDomDocument>
#include <QMessageBox>

#include "Base/Console.h"
#include "base/AppConfiguration.h"
#include "base/Console.h"
#include "base/MultiProgressOperator.h"

#include "precore/modeldocument.h"
#include "precore/itemlist.h"
#include "precore/precore_data.h"
#include "precore/UAPI_.h"

#include "edcompile/modelparser.h"
#include "edcompile/tdytypeinfomanager.h"

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

class ConsoleCompilingObserver: public INSEditor::Parse::CompileInfoObserver
{
	virtual void error(const INSEditor::Parse::CompileInfoItem& ErrorItem);
};

void ConsoleCompilingObserver::error( const INSEditor::Parse::CompileInfoItem& ErrorItem )
{
	QString mes=QString("%1(%2,%3):%4").arg(ErrorItem.fileName).arg(ErrorItem.rowIndex+1)
		.arg(ErrorItem.columnIndex+1).arg(ErrorItem.errorInfo);

	Console().Error(mes.toStdString().c_str());
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
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
			_setCollapseStatus(static_cast<Assembly*>(item));
	}

	n=assem->getAssemblies()->count();
	for(int i=0;i<n;++i){
		BaseItem* item=assem->getAssemblies()->child(i);
		if(item->getCategory()==TDY_PRE_CATE_ASSEMBLY)
			_setCollapseStatus(static_cast<Assembly*>(item));
	}

	assem->getMarkers()->setCollapsed(true);
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
	for(int i=0;i<n;++i)
		assem->getAssemblies()->child(i)->setCollapsed(false);
}

bool ImportTDYExchange::doJob()
{
	Console().Log("ImportTDY, filename = %s",_fileName.toStdString().c_str());
	QString fileName=AppConfiguration::instance()->workingDirectory()+_fileName;
	QDir::setCurrent(AppConfiguration::instance()->workingDirectory());

	if(!_typeInfoManager.isLoaded())
		_typeInfoManager.load(qApp->applicationDirPath()+"/settings/ins.xml");

	MultiProgressOperator::setProgress(2);

	// 1. Parse the project as a Parse::Assembly
	INSEditor::Parse::ModelParser parser;
	parser.attachErrorObserver(new ConsoleCompilingObserver());

	INSEditor::Parse::AssemblyItem* tmp=parser.parse(fileName);
	QSharedPointer<INSEditor::Parse::AssemblyItem> item=QSharedPointer<INSEditor::Parse::AssemblyItem>(tmp);

	MultiProgressOperator::setProgress(20);
	Console().Log("Finished parsing the file.");

	// 2. Do necessary verification using TDYTypeInfoManager
	parser.compileAssemblyItem(tmp,_typeInfoManager.getAllInfos());

	MultiProgressOperator::setProgress(30);
	Console().Log("Finished compiling the file.");

	// 3. Create new document using Parse::Assembly
	ImportTDYImp imp;
	registerImportFuncs(&imp);
	ImportTDYPara importPara;
	Assembly* newAssembly=new Assembly();
	newAssembly->createDefault();
	importPara.currentAssembly=newAssembly;
	importPara.currentPart=NULL;
	importPara.importTDYImp=&imp;

	imp.processItemChildren(&importPara,tmp);

	MultiProgressOperator::setProgress(90);
	Console().Log("Finished processing the file.");

	_setCollapseStatus(newAssembly);
	newAssembly->setKeyname(_fileName);
	Console().Log("Finished setting collapse status.");

	// 4. Add the new document into the application
	myDocument()->setAssembly(newAssembly);
	MultiProgressOperator::setProgress(100);
	Console().Log("Finished importtdy2.");

	return true;
}

void ImportTDYExchange::clear()
{
}

QString ImportTDYExchange::getKeyname()
{
	return "TDY_IMPORT";
}



