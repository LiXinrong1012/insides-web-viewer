#include <QtCore/QCoreApplication>
#include <QApplication>
#include "viewerlocalserver.h"
#include <QMessageBox>
#include <QLibrary>

#include "insviewer/insviewer.h"

INSViewer* createViewer()
{
	typedef void* (*F1) ();

	QLibrary lib("insviewer.dll");
	lib.load();

	bool bloaded=lib.isLoaded();
	if(bloaded){
		F1 f1=(F1)lib.resolve("createINSViewer");
		if(f1){
			return (INSViewer*)f1();
		}
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ViewerLocalServer server;
	if(!server.listen("myServer")){
		QMessageBox msg;
		msg.setText("faild ........");
		msg.exec();
		return 0;
	}

	INSViewer* viewer=createViewer();
	if(!viewer){
		QMessageBox::critical(0,"Error","Create Solver instance failed.");
		return 0;
	}

	INSViewerPara para;
	para.manager=&server;
	para.fileName="";
	viewer->setPara(para);

	server.setViewer(viewer);

	return a.exec();
}
