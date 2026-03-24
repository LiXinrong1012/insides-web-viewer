#include "lexerins.h"

#include <qcolor.h>
#include <qfont.h>
#include <qsettings.h>
#include <QApplication>

#include "edcompile/tdytypeinfomanager.h"

// The ctor.
LexerINS::LexerINS(QObject *parent, bool caseInsensitiveKeywords)
	:QsciLexerCPP(parent,caseInsensitiveKeywords)
{
}

// Return the set of character sequences that can separate auto-completion
// words.
QStringList LexerINS::autoCompletionWordSeparators() const
{
	QStringList wl;

	wl <<".";

	return wl;
}

// Return the list of keywords that can start a block.
const char *LexerINS::blockStartKeyword(int *style) const
{
	if (style)
		*style = Keyword;

	return "case catch class default do else finally for if private "
		"protected public struct try union while";
}

// Return the string of characters that comprise a word.
const char *LexerINS::wordCharacters() const
{
	return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_#";
}

// Returns the foreground colour of the text for a style.
QColor LexerINS::defaultColor(int style) const
{
	switch (style)
	{
	case Default:
		return QColor(0x80, 0x80, 0x80);

	case Comment:
	case CommentLine:
		return QColor(0x00, 0x7f, 0x00);

	case CommentDoc:
	case CommentLineDoc:
	case PreProcessorCommentLineDoc:
		return QColor(0x3f, 0x70, 0x3f);

	case Number:
		return QColor(0x00, 0x7f, 0x7f);

	case Keyword:
	case KeywordSet2:
		return QColor(0x00, 0x00, 0x7f);

	case DoubleQuotedString:
	case SingleQuotedString:
	case RawString:
		return QColor(0x7f, 0x00, 0x7f);

	case PreProcessor:
		return QColor(0x7f, 0x7f, 0x00);

	case Operator:
	case UnclosedString:
		return QColor(0x00, 0x00, 0x00);

	case VerbatimString:
	case TripleQuotedVerbatimString:
	case HashQuotedString:
		return QColor(0x00, 0x7f, 0x00);

	case Regex:
		return QColor(0x3f, 0x7f, 0x3f);

	case CommentDocKeyword:
		return QColor(0x30, 0x60, 0xa0);

	case CommentDocKeywordError:
		return QColor(0x80, 0x40, 0x20);

	case PreProcessorComment:
		return QColor(0x65, 0x99, 0x00);

	case InactiveKeywordSet2:
		return QColor(0x65, 0x19, 0x00);

	case InactiveDefault:
	case InactiveUUID:
	case InactiveCommentLineDoc:
	case InactiveCommentDocKeyword:
	case InactiveCommentDocKeywordError:
	case InactivePreProcessorCommentLineDoc:
		return QColor(0xc0, 0xc0, 0xc0);

	case InactiveComment:
	case InactiveCommentLine:
	case InactiveNumber:
	case InactiveVerbatimString:
	case InactiveTripleQuotedVerbatimString:
	case InactiveHashQuotedString:
		return QColor(0x90, 0xb0, 0x90);

	case InactiveCommentDoc:
		return QColor(0xd0, 0xd0, 0xd0);

	case InactiveKeyword:
		return QColor(0x90, 0x90, 0xb0);

	case InactiveDoubleQuotedString:
	case InactiveSingleQuotedString:
	case InactiveRawString:
		return QColor(0xb0, 0x90, 0xb0);

	case InactivePreProcessor:
		return QColor(0xb0, 0xb0, 0x90);

	case InactiveOperator:
	case InactiveIdentifier:
	case InactiveGlobalClass:
		return QColor(0xb0, 0xb0, 0xb0);

	case InactiveUnclosedString:
		return QColor(0x00, 0x00, 0x00);

	case InactiveRegex:
		return QColor(0x7f, 0xaf, 0x7f);

	case InactivePreProcessorComment:
		return QColor(0xa0, 0xc0, 0x90);
	}

	return QsciLexer::defaultColor(style);
}

// Returns the end-of-line fill for a style.
bool LexerINS::defaultEolFill(int style) const
{
	switch (style)
	{
	case UnclosedString:
	case InactiveUnclosedString:
	case VerbatimString:
	case InactiveVerbatimString:
	case Regex:
	case InactiveRegex:
	case TripleQuotedVerbatimString:
	case InactiveTripleQuotedVerbatimString:
	case HashQuotedString:
	case InactiveHashQuotedString:
		return true;
	}

	return QsciLexer::defaultEolFill(style);
}

// Returns the font of the text for a style.
QFont LexerINS::defaultFont(int style) const
{
	QFont f;

	switch (style)
	{
	case Comment:
	case InactiveComment:
	case CommentLine:
	case InactiveCommentLine:
	case CommentDoc:
	case InactiveCommentDoc:
	case CommentLineDoc:
	case InactiveCommentLineDoc:
	case CommentDocKeyword:
	case InactiveCommentDocKeyword:
	case CommentDocKeywordError:
	case InactiveCommentDocKeywordError:
#if defined(Q_OS_WIN)
		//f = QFont("Comic Sans MS",9);
		f = QFont("Tahoma",9);
#elif defined(Q_OS_MAC)
		f = QFont("Comic Sans MS", 12);
#else
		f = QFont("Bitstream Vera Serif",9);
#endif
		break;

	case Keyword:
	case InactiveKeyword:
	case Operator:
	case InactiveOperator:
		f = QsciLexer::defaultFont(style);
		f.setBold(true);
		break;

	case DoubleQuotedString:
	case InactiveDoubleQuotedString:
	case SingleQuotedString:
	case InactiveSingleQuotedString:
	case UnclosedString:
	case InactiveUnclosedString:
	case VerbatimString:
	case InactiveVerbatimString:
	case Regex:
	case InactiveRegex:
	case TripleQuotedVerbatimString:
	case InactiveTripleQuotedVerbatimString:
	case HashQuotedString:
	case InactiveHashQuotedString:
#if defined(Q_OS_WIN)
		f = QFont("Time New Roman",10);
		//f = QFont("Courier New",10);
#elif defined(Q_OS_MAC)
		f = QFont("Courier", 12);
#else
		f = QFont("Bitstream Vera Sans Mono",9);
#endif
		break;

	default:
		f = QsciLexer::defaultFont(style);
	}

	return f;
}

// Returns the set of keywords.
const char *LexerINS::keywords(int set) const
{
	static INSEditor::Parse::TDYTypeInfoManager infoManager;
	if(!infoManager.isLoaded())
		infoManager.load(qApp->applicationDirPath()+"/settings/ins.xml");

	if (set == 1)
	{
		return infoManager.getAllKeynames();
	}

	if (set == 2)
		return infoManager.getAllProperties();

	if (set == 3)
		return
		"a addindex addtogroup anchor arg attention author b "
		"brief bug c class code date def defgroup deprecated "
		"dontinclude e em endcode endhtmlonly endif "
		"endlatexonly endlink endverbatim enum example "
		"exception f$ f[ f] file fn hideinitializer "
		"htmlinclude htmlonly if image include ingroup "
		"internal invariant interface latexonly li line link "
		"mainpage name namespace nosubgrouping note overload "
		"p page par param post pre ref relates remarks return "
		"retval sa section see showinitializer since skip "
		"skipline struct subsection test throw todo typedef "
		"union until var verbatim verbinclude version warning "
		"weakgroup $ @ \\ & < > # { }";

	return 0;
}

// Returns the background colour of the text for a style.
QColor LexerINS::defaultPaper(int style) const
{
	switch (style)
	{
	case UnclosedString:
	case InactiveUnclosedString:
		return QColor(0xe0,0xc0,0xe0);

	case VerbatimString:
	case InactiveVerbatimString:
	case TripleQuotedVerbatimString:
	case InactiveTripleQuotedVerbatimString:
		return QColor(0xe0,0xff,0xe0);

	case Regex:
	case InactiveRegex:
		return QColor(0xe0,0xf0,0xe0);

	case RawString:
	case InactiveRawString:
		return QColor(0xff,0xf3,0xff);

	case HashQuotedString:
	case InactiveHashQuotedString:
		return QColor(0xe7,0xff,0xd7);
	}

	return QsciLexer::defaultPaper(style);
}
