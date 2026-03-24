#ifndef LEXERCURVE_H
#define LEXERCURVE_H

#include <QObject>

#include <Qsci/qsciglobal.h>
#include <QSci/qscilexercpp.h>

/*!
	@brief   语法分析提示
	@date    2015.7.3
	@author  Jianjun
*/
class LexerCurve : public QsciLexerCPP
{
//	Q_OBJECT

public:
	LexerCurve(QObject *parent =0 ,bool caseInsensitiveKeywords = false);
	~LexerCurve();

	///自动编译词语分隔符
	QStringList autoCompletionWordSeparators() const;

	///块开始关键字
	const char *blockStartKeyword(int *style) const;

	///词语特性
	const char *wordCharacters() const;

	///默认颜色
	QColor defaultColor(int style) const;

	///默认结束标志
	bool defaultEolFill(int style) const;

	///默认字体
	QFont defaultFont(int style) const;

	///返回关键字
	const char *keywords(int set) const;

	///默认纸张
	QColor defaultPaper(int style) const;

private:
	Q_DISABLE_COPY(LexerCurve);
	
};

#endif // LEXERCURVE_H
