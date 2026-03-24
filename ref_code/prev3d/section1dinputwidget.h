#ifndef SECTION1DINPUTWIDGET_H
#define SECTION1DINPUTWIDGET_H

#include <QWidget>
namespace Ui {class Section1DInputWidget;};

class Section1DInputWidget : public QWidget
{
	Q_OBJECT

public:
	Section1DInputWidget(QWidget *parent = 0);
	~Section1DInputWidget();

	QList<double> get1DSectionPoints();
	QList<double> get1DParameters();

	bool onOKClicked();

protected slots:
	void onTypeChanged();

private:
	void setVisual_Circle(bool flag);
	void setVisual_Ellipse(bool flag);
	void setVisual_Rectangle(bool flag);
	void setVisual_Userdefined(bool flag);

	QList<double>	_section1DPoints;
	QList<double>	_section1DParameters;

	Ui::Section1DInputWidget *ui;
};

#endif // SECTION1DINPUTWIDGET_H
