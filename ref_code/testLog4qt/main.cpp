
#include <QtCore/QCoreApplication>
#include <Qt/qsettings.h>

#include "log4qt/log4qt.h"
#include "log4qt/basicconfigurator.h"
#include "log4qt/logger.h"

void setupLog4Qt()
{
	QSettings s;
	// Set logging level for Log4Qt to TRACE
	s.beginGroup("Log4Qt");
	s.setValue("Debug", "TRACE");

	// Configure logging to log to the file C:/myapp.log using the level TRACE
	s.beginGroup("Properties");
	s.setValue("log4j.appender.A1", "org.apache.log4j.FileAppender");
	s.setValue("log4j.appender.A1.file", "C:/myapp.log");
	s.setValue("log4j.appender.A1.layout", "org.apache.log4j.TTCCLayout");
	s.setValue("log4j.appender.A1.layout.DateFormat", "ISO8601");
	s.setValue("log4j.rootLogger", "TRACE, A1");
}
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	Log4Qt::BasicConfigurator::configure();
	Log4Qt::Logger * log = Log4Qt::Logger::rootLogger();
	log->debug("Hello Jerry!");
	log->info("Hello Qt!");
	log->warn("Hello 1+1=2");


	return 0;
	//return a.exec();
}
