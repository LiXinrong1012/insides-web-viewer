#include "testsearchwidget.h"


testSearchWidget::testSearchWidget(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	s = new SearchKeyWidget();

	QPushButton *btn = new QPushButton(this);
	connect(btn,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
}

testSearchWidget::~testSearchWidget()
{

}

void testSearchWidget::onBtnClicked()
{
	s->show();
}
