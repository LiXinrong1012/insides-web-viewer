#include <QtCore/QCoreApplication>
#include "edcore/entity.h"
#include "edcore/project.h"
#include "edcore/document.h"

using namespace INSEditor;


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	Document* doc=Document::instance();
	doc->createNew("D:","app1");

	Document::destruct();
	return a.exec();
}
