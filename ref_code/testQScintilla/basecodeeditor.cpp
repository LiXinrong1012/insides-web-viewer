#include "basecodeeditor.h"
#include <QtCore>
#include <QtGui>

#include <Qsci/qscilexercpp.h>
#include <QSci/qsciapis.h>
#include "lexertdy.h"

BaseCodeEditor::BaseCodeEditor(QWidget *parent)
	: QsciScintilla(parent)
{
//	const QString usersetfont = setter.value("DefaultFontsS").toString();
//	QFont settfont;
//	settfont.fromString(usersetfont);
//	int fromsetting = settfont.pointSize();
//	qDebug() << "### sci usersetfont " << usersetfont;
//	qDebug() << "### sci fromsetting " << fromsetting;
//	fontsize = 12;
//#if defined Q_WS_MAC
//	fontsize = 22;
//#endif
//	numerobase = 0;
//	if (fromsetting > 2) {
//		setFont(settfont);
//	} else {
//		QFont font;
//		font.setFamily(QString::fromUtf8("Arial"));
//		font.setPointSize(fontsize);
//		setFont(font);
//	}

	SendScintilla(SCI_SETCODEPAGE,SC_CP_UTF8);

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
	ensureLineVisible(1); 
	setUtf8(true);
	setWhitespaceVisibility(QsciScintilla::WsVisible);
	caseSensitive();

	//QsciLexerCPP *lexer = new QsciLexerCPP(this);
	QsciLexer* lexer=new LexerTDY(this);
	setLexer(lexer);
	setAutoCompletionCaseSensitivity(false);

	QsciAPIs* apis=new QsciAPIs(lexer);
	apis->add("mymakrer");
	apis->add("myrigid");
	apis->add("myrigid2(int a,int b)hahhaha");
	apis->add("myrigid2(int a,int b,int c)hahhaha");
	apis->prepare();
	lexer->setAPIs(apis);
	setAutoCompletionSource(AcsAPIs);

	//shortcut1 = new QShortcut(QKeySequence("Ctrl+S"),this);
	//model = PAGER_LOADING_FUNCTIONS;
	//connect(shortcut1, SIGNAL(activated()),this, SLOT(SaveCurrentDoc()));
	///////////connect(this, SIGNAL(textChanged()),this, SLOT(UpdateParent()));
	//shortcut7 = new QShortcut(QKeySequence::ZoomOut,this);  /* CTRL- */
	//shortcut8 = new QShortcut(QKeySequence::ZoomIn,this);  /* CTRL+ */
	//connect(shortcut7, SIGNAL(activated()),this, SLOT(Decreasefont()));
	//connect(shortcut8, SIGNAL(activated()),this, SLOT(Increasefont()));
}

BaseCodeEditor::~BaseCodeEditor()
{

}

int BaseCodeEditor::getCurrentLineNumber()
{
	return SendScintilla(SCI_LINEFROMPOSITION,
		SendScintilla(SCI_GETCURRENTPOS));
}

void BaseCodeEditor::onCharAdded( int ch )
{
	if  (ch  ==  '\r'  ||  ch  ==  '\n')  {
		char  linebuf[1000];
	
		
		//int  curLine  =  getCurrentLineNumber();
		//int  lineLength  =  SendScintilla(SCI_LINELENGTH,  curLine);
		////Platform::DebugPrintf("[CR] %d len = %d\n", curLine, lineLength);
		//if  (curLine  >  0  &&  lineLength  <=  2)  {
		//	int  prevLineLength  =  SendScintilla(SCI_LINELENGTH,  curLine  -  1);
		//	if  (prevLineLength  <  sizeof(linebuf))  {
		//		int  buflen  =  sizeof(linebuf);
		//		memcpy(linebuf,  &buflen,  sizeof(buflen));
		//		SendScintilla(EM_GETLINE,  curLine  -  1,
		//			reinterpret_cast<LPARAM>(static_cast<char  *>(linebuf)));
		//		linebuf[prevLineLength]  =  '\0';
		//		for  (int  pos  =  0;  linebuf[pos];  pos++)  {
		//			if  (linebuf[pos]  !=  ' '  &&  linebuf[pos]  !=  '\t')
		//				linebuf[pos]  =  '\0';
		//		}
		//		SendScintilla(EM_REPLACESEL,  0,  reinterpret_cast<LPARAM>(static_cast<char  *>(linebuf)));
		//	}
		}

}

void BaseCodeEditor::testMarker()
{
	int liner=getCurrentLineNumber();
	int markerNumer=SC_MARK_ARROW;
	markerDefine(QImage("D:/Ribbon/res/qtitanlogo32x32.png"),SC_MARK_ARROW);
	SendScintilla(SCI_MARKERADD, liner, markerNumer);
	SendScintilla(SCI_SETINDENTATIONGUIDES,SC_IV_LOOKFORWARD);
}

void BaseCodeEditor::testAnnotation()
{
	clearAnnotations();
	static int lineId=0;
	char myBuffer[1024];
	strcpy(myBuffer,"this is a annotation test.");

	SendScintilla(SCI_ANNOTATIONSETTEXT,lineId++,myBuffer);

}
