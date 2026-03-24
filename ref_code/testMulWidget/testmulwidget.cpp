#include "testmulwidget.h"

#include "base/viewframe.h"
#include "renderview.h"
#include "base/ViewLayoutManager.h"

using namespace Base;

testMulWidget::testMulWidget(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	QAction* myAction=new QAction(this,"Haha");


	RenderView* view=new RenderView();
	Base::ViewLayoutManager *layout=ui.mainWidget->layoutManager();
	layout->AssignView(0,view);
	ui.mainWidget->reload();
	//ui.mainWidget->addTitleBarAction(myAction);
	
	//ViewFrame* frame=new ViewFrame(this);
	//ui.->setCentralWidget(frame);
}
void testMulWidget::onNew()
{
	MultiViewWidget* multiView=ui.mainWidget;
	multiView->destroyAllViews();
	ViewLayoutManager *layout=multiView->layoutManager();
	layout->Reset();
	multiView->reload();

	RenderView* hoopsView=new RenderView();
	layout->AssignView(0,hoopsView);
	multiView->reload();
}

testMulWidget::~testMulWidget()
{

}

void testMulWidget::onSaveState()
{
	QString fileName="D:/layout.txt";
	ui.mainWidget->layoutManager()->SaveAllState(fileName);
}

void testMulWidget::onLoadState()
{
	MultiViewWidget* multiView=ui.mainWidget;
	multiView->destroyAllViews();
	ViewLayoutManager *layout=multiView->layoutManager();
	layout->Reset();
	multiView->reload();

	QString fileName="D:/layout.txt";
	ui.mainWidget->layoutManager()->LoadAllState(fileName);
	multiView->reload();
}


