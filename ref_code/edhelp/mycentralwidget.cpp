#include "mycentralwidget.h"
#include "HelpViewer.h"

MyCentralWidget* MyCentralWidget::_instance=0;


MyCentralWidget::MyCentralWidget(QObject *parent)
	: QObject(parent)
{
	_instance=this;
}

MyCentralWidget::~MyCentralWidget()
{

}

MyCentralWidget* MyCentralWidget::instance()
{
	return _instance;
}

void MyCentralWidget::setSource( const QUrl& url )
{
	_helpViewer->setSource(url);
}
