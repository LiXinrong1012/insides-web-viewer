#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <QWidget>
#include <qlist.h>
#include "pretdy/TDYParameters.h"
namespace Ui {class ParametersWidget;};

class ParametersWidget : public QWidget
{
	Q_OBJECT

public:
	ParametersWidget(QWidget *parent = 0);
	~ParametersWidget();
public:
	QList<TDYParameterItem> _itemlist;
	TDYParameters m_TDYPar;
	void modifyRowContent(int Row);
	void InitData();

private slots:
		void onAdd();
		void onRemove();
		void onModify();
		void onUp();
		void onDown();
		void onBtnState(int,int);
		void onBtnChangeState();


private:
	Ui::ParametersWidget *ui;
};

#endif // PARAMETERSWIDGET_H
