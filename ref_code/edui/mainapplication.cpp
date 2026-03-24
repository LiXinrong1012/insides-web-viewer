#include "mainapplication.h"
#include "mainwindow.h"

#include "edcore/console.h"

#include <QTextCodec>
#include <QApplication>
#include <QtnRibbonStyle.h>

MainApplication::MainApplication()
{
}

MainApplication::~MainApplication()
{
}

int MainApplication::run( int argc,char* argv[] )
{
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	QApplication a(argc, argv);
	a.setStyle( new Qtitan::RibbonStyle() );

	a.setApplicationName("INSIDES-Editor");
	a.setOrganizationName("THU-Jerry");
	QApplication::setFont(QFont("Tahoma", 9)); 

	QString logFile=qApp->applicationDirPath()+"/editor_log.txt";
	Base::Console().AttachObserver(new Base::ConsoleObserverFile(logFile.toStdString().c_str()));

	//if(!Base::L::co("main","1.0")){
	//	QMessageBox::message("Info","There's no available license.");
	//	return 0;
	//}

	MainWindow* w=new MainWindow();
	w->show();
	int re= a.exec();
	delete w;
	//Document::destruct();

	//Base::L::ci("main");
	return re;
}
