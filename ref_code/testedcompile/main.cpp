
#include <QtCore/QCoreApplication>

#include "../edcompile/modelparser.h"
#include "../edcompile/instemplate.h"
#include "../edcompile/tdytypeinfomanager.h"
#include "../edcompile/insmodelformator.h"

using namespace INSEditor::Parse;
using namespace INSEditor;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);


	ModelParser parser;
	parser.addDefaultObserver();

	//AssemblyItem* item=parser.parseFile("C:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/test_parse/crank_slider.tdy");
	//AssemblyItem* item=parser.parse("C:/Users/Jerry/Desktop/TDYPre/databases/solver_sample/thu4/main.tdy");
	AssemblyItem* item=parser.parse("D:/ljp-model/main.tdy");
	//item->print("");

	TDYTypeInfoManager manager;
	manager.loadFromTDYTemplate("D:/solver/tdy_template.xml");
	manager.compileAssemblyItem(item);

	//测试导入导出正确性
	//manager.save("D:/ins.xml");
	//static TDYTypeInfoManager manager2;
	//manager2.load("D:/ins.xml");
	//manager2.save("D:/ins2.xml");
	
	INSModelFormator formator;
	formator.setMaxLineWord(100);
	formator.saveAsFile(item,"D:/a.tdy");
	item->print("");

	return 0;
	//return a.exec();
}
