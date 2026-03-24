#include "myinsviewer.h"
#include "insviewermanager.h"

#include <QFile>


extern "C" void* createINSViewer()
{
	MyINSViewer* viewer=new MyINSViewer();
	return viewer;
}

MyINSViewer::MyINSViewer()
{

}

MyINSViewer::~MyINSViewer()
{

}

void MyINSViewer::setPara( const INSViewerPara& para )
{
	_viewerPara = para;
}

void MyINSViewer::importModel( const QString& fullName )
{
	//可以收到
	_viewerPara.manager->importedModel();
}

void MyINSViewer::importResult()
{
	_viewerPara.manager->importedResult();
}

void MyINSViewer::importEigen()
{
	_viewerPara.manager->importedEigen();
}

void MyINSViewer::fresh()
{
	_viewerPara.manager->freshed();
}

void MyINSViewer::heightLight()
{
	_viewerPara.manager->heightLight();
}
