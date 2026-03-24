#ifndef INSIDES_EDITOR_LEXERINS_H
#define INSIDES_EDITOR_LEXERINS_H

#include <QObject>

#include <Qsci/qsciglobal.h>
#include <QSci/qscilexercpp.h>
//#include <Qsci/qscilexer.h>


//! \brief The QsciLexerCPP class encapsulates the Scintilla C++
//! lexer.
/*!
	@brief   为程序的提示功能提供支持
	@date    2015.6.19
	@author  Jerry
*/
class LexerINS : public QsciLexerCPP
{
	Q_OBJECT

public:

	LexerINS(QObject *parent = 0, bool caseInsensitiveKeywords = false);

	///自动编译时的分隔符
	QStringList autoCompletionWordSeparators() const;

	///块开始的关键字，未使用
	const char *blockStartKeyword(int *style) const;

	///字符
	const char *wordCharacters() const;

	///默认颜色
	QColor defaultColor(int style) const;

	///默认终止符？
	bool defaultEolFill(int style) const;

	///默认字体
	QFont defaultFont(int style) const;

	///关键字
	const char *keywords(int set) const;

	///默认纸张
	QColor defaultPaper(int style) const;

private:
	Q_DISABLE_COPY(LexerINS);

};

#endif // INSIDES_EDITOR_LEXERINS_H
