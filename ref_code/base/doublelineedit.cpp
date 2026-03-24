#include "doublelineedit.h"
#include <QRegExpValidator>

using namespace Base;

DoubleLineEdit::DoubleLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	//QRegExp double_rx10000("10000000|([\\-][0-9]{0,9}[\.][0-9]{1,9})");
	QRegExp double_rx10000("([\\-]{0,1}[0-9]{0,12}[.][0-9]{0,12})"); 
		//"|([0-9]{0,9}[0-9]{1,3})"); 
	setValidator(new QRegExpValidator(double_rx10000, this));

	connect(this,SIGNAL(textChanged(const QString&)),this,SLOT(onTextChanged(const QString&)));
	//connect(this,SIGNAL(editingFinished()),this,SLOT(onEditingFinished()));
	//connect(this,SIGNAL(returnPressed()),this,SLOT(onEditingFinished()));
}

DoubleLineEdit::~DoubleLineEdit()
{

}

void DoubleLineEdit::onTextChanged( const QString& text )
{
	bool ok;
	double d=text.toDouble(&ok);
	if(ok)
		emit valueChanged(d);
}
void Base::DoubleLineEdit::onEditingFinished()
{
	double va=value();
	emit valueChanged(va);
}
double DoubleLineEdit::value()const
{
	bool ok;
	QString t=text();
	double d=t.toDouble(&ok);
	if(ok)
		return d;
	return 0;
}

void Base::DoubleLineEdit::setValue( double v )
{
	double currentValue=value();
	if(currentValue==v)
		return;

	QString str=QString("%1").arg(v);
	setText(str);
}


