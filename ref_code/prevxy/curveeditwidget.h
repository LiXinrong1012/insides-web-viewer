#ifndef CURVEEDITWIDGET_H
#define CURVEEDITWIDGET_H

#include <Qsci/qsciscintilla.h>

class QsciAPIs;
namespace Ui {class CurveEditWidget;};

/*!
	@brief   自定义曲线编辑器
	@date    2015.7.2
	@author  Jianjun
*/
class CurveEditWidget : public QsciScintilla
{
//	Q_OBJECT

public:
	CurveEditWidget(QWidget *parent);
	~CurveEditWidget();

private:
	///初始提示
	void initApis();

private:
	///用来存储提示api
	QsciAPIs* _api;
	
};

#endif // CURVEEDITWIDGET_H
