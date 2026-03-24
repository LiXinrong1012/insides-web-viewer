#include "RenderViewTest.h"
#include "PreHQWidget.h"

#include <QtGui>
#include "base/ViewFactory.h"
#include "base/TreeItemPropertyManager.h"

#include "hoopsvisibilitysettingdialog.h"
#include "HoopsMaterialDelegate.h"
#include <QtGui>
#include "prev3dcore/BaseHQWidget.h"
#include "prev3d/SimpleHQWidget.h"

static QString renderViewTestName("RenderViewTest");
//static Base::GeneralProducerRegister<Base::ViewFactory,RenderViewTest,QString> aaa22(renderViewTestName);


RenderViewTest::RenderViewTest(void)
{
	QSplitter* main=new QSplitter(Qt::Horizontal,0);
	BaseHQWidget* hoopsView=new BaseHQWidget(main);
	//SimpleHQWidget* hoopsView=new SimpleHQWidget(main,"haha");

	_widget=main;
	_actualWidget=hoopsView;

}


RenderViewTest::~RenderViewTest(void)
{
	delete _widget;
}
QString RenderViewTest::getViewType() const
{
	return renderViewTestName;
}

QWidget* RenderViewTest::getWidget()
{
	return _widget;
}

QWidget* RenderViewTest::getActualWidget()
{
	return _actualWidget;
}

QString RenderViewTest::getClassTypeName()
{
	return renderViewTestName;
}



