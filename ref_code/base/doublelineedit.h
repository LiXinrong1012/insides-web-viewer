#ifndef DOUBLELINEEDIT_H
#define DOUBLELINEEDIT_H

#include "base/base_global.h"
#include <QLineEdit>


namespace Base
{

/*!
*	@breif 一个只能输入浮点数的文本框
*
*	@author	Jerry He
*	@date	2014.10.13
*/
class BASE_EXPORT DoubleLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	DoubleLineEdit(QWidget *parent);
	~DoubleLineEdit();

	/// 获取当前值
	double value()const;

	/// 设置当前值
	void setValue(double v);

signals:
	void valueChanged(double v);

	private slots:
		void onTextChanged(const QString& text);
		void onEditingFinished();

};

}


#endif // DOUBLELINEEDIT_H
