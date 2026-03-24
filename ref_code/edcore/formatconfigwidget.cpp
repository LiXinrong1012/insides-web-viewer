#include "formatconfigwidget.h"
#include "ui_formatconfigwidget.h"

FormatConfigWidget::FormatConfigWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::FormatConfigWidget();
	ui->setupUi(this);
}

FormatConfigWidget::~FormatConfigWidget()
{
	delete ui;
}

int FormatConfigWidget::getIndentationValue()
{
	return ui->IndentationSpinBox->value();
}

void FormatConfigWidget::setIndentationValue( int value )
{
	ui->IndentationSpinBox->setValue(value);
}

int FormatConfigWidget::getLineMaxNumValue()
{
	return ui->lineMaxNumSpinBox->value();
}

void FormatConfigWidget::setLineMaxNumValue( int value )
{
	ui->lineMaxNumSpinBox->setValue(value);
}

