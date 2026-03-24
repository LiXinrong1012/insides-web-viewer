#include "curveeditwidget.h"
#include "lexercurve.h"

#include "precore/modeldocument.h"
#include "precore/ResultDocument.h"

#include <QSci/qsciapis.h>
#include <QApplication>
#include <QSettings>
#include <QEvent>
#include <QKeyEvent>

using namespace INSIDES;
CurveEditWidget::CurveEditWidget(QWidget *parent)
	: QsciScintilla(parent)
{
	QFont font;
	font.setFamily(QString::fromUtf8("Arial"));
	setFont(font);

	setPaper(QColor("#fbffcb"));
	setIndentationGuidesBackgroundColor(QColor("#e6e6de"));
	setAutoCompletionThreshold(1);
	setFolding(QsciScintilla::BoxedFoldStyle);;
	setMarginLineNumbers(1,true);
	setAutoCompletionFillupsEnabled(true);
	setAutoIndent(true);
	setAutoCompletionSource(QsciScintilla::AcsAll);
	setCaretWidth(10);
	setCaretLineBackgroundColor(QColor("#e6fff0"));
	setCaretLineVisible(true);
	ensureLineVisible(9999); 
	setUtf8(true);

	QsciLexer* lexer=new LexerCurve(this);
	_api = new QsciAPIs(lexer);

	initApis();

	lexer->setAPIs(_api);
	this->setLexer(lexer);

	setAutoCompletionCaseSensitivity(false);
	setAutoCompletionFillupsEnabled(true);

	setAutoCompletionSource(QsciScintilla::AcsAll);
}

CurveEditWidget::~CurveEditWidget()
{
}

void CurveEditWidget::initApis()
{
	QString dir = QCoreApplication::applicationDirPath()+"/settings/";
	QSettings settings(dir +"insides-viewer-curve-completion.ini", QSettings::IniFormat);

	settings.beginGroup("COMPLETION");
	static QStringList apis= settings.value("values").toStringList();
	settings.endGroup();

	foreach(QString s,apis)
		_api->add(s);

	ResultDocument* resDoc=myResultDocument();
	IResults* res=resDoc->getResults();
	if(!res)
		return;

	IResults::ResultMap& allRes=res->getResults();
	for(IResults::ResultMap::Iterator b=allRes.begin();b!=allRes.end();++b)
	{
		BaseItem* item=b.key();
		_api->add(item->getFullName());
		QList<BaseItem*> children;
		BaseItem::getChildren(item,children,true);
		for (int i=0;i<children.count();i++)
			_api->add(children[i]->getFullName());
	}
	
	_api->prepare();
}

