#include "propertydockwidget.h"
#include "ui_propertydockwidget.h"

PropertyDockWidget* PropertyDockWidget::_instance=NULL;


PropertyDockWidget::PropertyDockWidget(QWidget *parent)
	: QDockWidget(parent)
{
	ui = new Ui::PropertyDockWidget();
	ui->setupUi(this);

	_instance=this;
}

PropertyDockWidget::~PropertyDockWidget()
{
	delete ui;
}

PropertyWidget* PropertyDockWidget::getPropertyWidget()
{
	return ui->_propertyWidget;
}

PropertyDockWidget* PropertyDockWidget::instance()
{
	return _instance;
}

