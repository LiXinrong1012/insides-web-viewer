#include "mainapplication.h"

#include <QApplication>

#include "main_ui.h"
#include <QtGui/QApplication>
#include <QTextCodec>
#include <QtCore>
#include <QtGui>

#include "base/AppConfiguration.h"
#include "base/licenses.h"

#include "hoops_init.h"

#include "precore/document.h"

#include "localserver.h"
#include <QtnRibbonStyle.h>


using namespace Base;


/// 根据main函数中启动程序文件设置启动目录。 Jerry 2013.4.9.
void _setStartupDirFomrExecutable(const QString& executable)
{
	QFileInfo dir(executable);
	QString str=dir.absoluteDir().absolutePath();
	QDir::setCurrent(str);	//by Jerry He, 2014.8.19
	if((str[str.size()-1]!='/')&&
		(str[str.size()-1]!='\\'))
		AppConfiguration::instance()->setStartupDirectory(str+"/");
	else
		AppConfiguration::instance()->setStartupDirectory(str);
}

MainApplication::MainApplication()
{

}

MainApplication::~MainApplication()
{

}

int MainApplication::run( int argc,char* argv[] )
{
	_setStartupDirFomrExecutable(argv[0]);

	QString logFile=AppConfiguration::instance()->startupDirectory()+"viewer_log.txt";
	ConsoleObserverFile* file=new ConsoleObserverFile(logFile.toStdString().c_str());
	Base::Console().AttachObserver(file);


	Console().Log("Start run...");

	if(!Base::L::init()
		&& (0==1))
		return 0;



	Console().Log("Initialized license system.");

	init_HOOPS();

	Console().Log("Initialized HOOPS system.");

	QApplication::setColorSpec( QApplication::ManyColor );

	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	//m_pHDB->SetDriverType("dx9");//HQWidget::ChooseDriver());
	//m_pHDB->SetDriverType(choose_DefaultDriver());
	m_pHDB->SetDriverType("opengl");//HQWidget::ChooseDriver());

	QApplication a(argc, argv);
	a.setStyle( new Qtitan::RibbonStyle() );

	//QString licenseFile=qApp->applicationDirPath()+"/license/license.lic";
	//QMessageBox::about(NULL,licenseFile,licenseFile);
	//Base::L::setlicensefile(licenseFile.toStdString().c_str());


	QString inputModelName;
	QString serverName;
	QStringList arguments=qApp->arguments();
	Console().Log("Argc: %s",arguments.join(" ").toStdString().c_str());
	// 处理本地连接
	int i=1;
	while(i<argc)
	{
		QString a=arguments[i];
		if(a.compare("-N",Qt::CaseInsensitive)==0){
			serverName=arguments[i+1];
			i=i+2;
			continue;
		}
		inputModelName=a;
		i=i+1;
	}

	if(inputModelName.size()!=0 && inputModelName[0]=='\"')
		inputModelName=inputModelName.mid(1,inputModelName.size()-2);

	//a.setApplicationName("QtitanRibbon Office Sample");
	//a.setOrganizationName("Developer Machines");

	if(!Base::L::co("insviewer","2.0")
		&& (0==1)){
		QMessageBox::message("Info","There's no available license.");
		return 0;
	}

	main_ui* w=NULL;
	if(QFile::exists(inputModelName)){
		Console().Log("Read model file: %s",inputModelName.toStdString().c_str());
		w=new main_ui(NULL,NULL,inputModelName,serverName);
	}
	if(!w)
		w=new main_ui(NULL,NULL,QString(),serverName);

	w->show();
	int re= a.exec();
	delete w;
	INSIDES::MultiDocuments::destruct();
	destroy_HOOPS();
	Base::L::ci("main");
	//Base::L::tc();
	return re;

}


