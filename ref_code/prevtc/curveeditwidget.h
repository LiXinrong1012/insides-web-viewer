#ifndef CURVEEDITWIDGET_H
#define CURVEEDITWIDGET_H

#include <Qsci/qsciscintilla.h>

class QsciAPIs;
namespace Ui {class CurveEditWidget;};

/*!
	@brief   曲线编辑界面，继承与SCI文本编辑器
	@date    2015.6.26
	@author  Jianjun
*/
class CurveEditWidget : public QsciScintilla
{
//	Q_OBJECT

public:
	CurveEditWidget(QWidget *parent);
	~CurveEditWidget();

private:
	//初始化提示
	void initApis();

private:
	QsciAPIs* _api;
	
};

#endif // CURVEEDITWIDGET_H
