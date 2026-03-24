#include "renderview2.h"
#include "tmpwidget2.h"
#include "Base/ViewFactory.h"

static QString viewKeyName("My Render View2");
static Base::GeneralProducerRegister<Base::ViewFactory,RenderView2,QString> aaa2(viewKeyName);

RenderView2::RenderView2(QObject *parent)
	: View(parent)
{
	setViewType(viewKeyName);
	_widget=new TmpWidget2();
}

RenderView2::~RenderView2()
{
	delete _widget;
}

QWidget* RenderView2::getWidget()
{
	return _widget;
}
