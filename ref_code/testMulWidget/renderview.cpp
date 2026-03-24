#include "renderview.h"
#include <QtGui>
#include "tmpwidget.h"

#include "base/ViewFactory.h"

static QString renderViewKeyName("My Render View");
static Base::GeneralProducerRegister<Base::ViewFactory,RenderView,QString> aaa(renderViewKeyName);


RenderView::RenderView(QObject *parent)
	: View(parent)
{
	setViewType(renderViewKeyName);

	m_widget=new TmpWidget();

}

RenderView::~RenderView()
{
	delete m_widget;
}

QWidget* RenderView::getWidget()
{
	return m_widget;
}
