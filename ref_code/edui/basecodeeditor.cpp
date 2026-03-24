#include "basecodeeditor.h"
#include <QtCore>
#include <QtGui>
#include <QFileSystemWatcher>

#include "lexerins.h"

#include <Qsci/qscilexercpp.h>
#include <QSci/qsciapis.h>
#include <Qsci/qscilexerpython.h>
#include <QSci/qscilexermatlab.h>
#include <QSci/qscilexerfortran.h>

#include "edcompile/tdytypeinfomanager.h"
#include "edcompile/modelparser.h"

#include "edcore/filemanager.h"
#include "edcore/document.h"

using namespace INSEditor::Parse;

QFont BaseCodeEditor::_textFont=QFont();

BaseCodeEditor::BaseCodeEditor(QWidget *parent)
	: QsciScintilla(parent)
	,_assemblyItem(NULL)
	,_keyWordLine(0)
	,_textChangedTime(0)
	,_isRunning(true)
{
	setWindowIcon(QIcon(":/resources/menu/h000c.png"));
	QFont font;
	font.setFamily(QString::fromUtf8("Arial"));
	setFont(font);

	setPaper(QColor("#fbffcb"));
	setIndentationGuidesBackgroundColor(QColor("#e6e6de"));
	setAutoCompletionThreshold(1);
	setFolding(QsciScintilla::BoxedFoldStyle);;
	setMarginLineNumbers(1,true);
	setAutoCompletionFillupsEnabled(true);
	setAutoCompletionCaseSensitivity(false);
	setAutoCompletionSource(AcsAPIs);
	setAutoIndent(true);
	setCaretWidth(10);
	setCaretLineBackgroundColor(QColor("#e6fff0"));
	setCaretLineVisible(true);
	ensureLineVisible(9999); 
	setUtf8(true);

	QsciLexer* lexer=new LexerINS(this,true);
	setLexer(lexer);
	_apis=new QsciAPIs(lexer);
	updateAPI(_apis);
	_apis->prepare();
	lexer->setAPIs(_apis);

	SendScintilla(SCI_SETMARGINWIDTHN,1,40);
	SendScintilla(SC_CASEINSENSITIVEBEHAVIOUR_IGNORECASE,1);
	SendScintilla(SCI_SETMULTIPLESELECTION,true);

	_saveDocument = new QShortcut(QKeySequence("Ctrl+S"),this);
	connect(_saveDocument, SIGNAL(activated()),this, SLOT(save()));

	setModified(false);
	connect(this,SIGNAL(modificationChanged(bool)),this,SLOT(onModificationChanged()));
	connect(this,SIGNAL(textChanged()),this,SLOT(onTextChanged()));
	connect(this,SIGNAL(cursorPositionChanged(int, int)),this,SLOT(onCursorPositionChanged(int,int)));

	_watcher = new QFileSystemWatcher(this);
	connect(_watcher,SIGNAL(fileChanged ( const QString & )),this,SLOT(onFileChanged(const QString&)));
	createStandardContextMenu();
	this->installEventFilter(this);
	_kList<<"I"<<"J"<<"CM";

	_typeManager.load(qApp->applicationDirPath()+"/settings/ins.xml");

	//初始材质
	initMaterial();
	
	_timer = new QTimer(this);
	connect(_timer,SIGNAL(timeout()),this,SLOT(onTimeouted()));
	_timer->start(5000);
	onTimeouted();
}

BaseCodeEditor::~BaseCodeEditor()
{
	if(_watcher)
		delete _watcher;
	FileManager::instance()->notifyUpdateIcon();
}

int BaseCodeEditor::getCurrentLineNumber()
{
	return SendScintilla(SCI_LINEFROMPOSITION,
		SendScintilla(SCI_GETCURRENTPOS));
}

void BaseCodeEditor::onCharAdded( int ch )
{
	if  (ch  ==  '\r'  ||  ch  ==  '\n')  
	{
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

void BaseCodeEditor::decreaseFont()
{
	QFont font;
	font.setPointSize(30);
	this->lexer()->setFont(font);
	//this->zoomIn();
}

void BaseCodeEditor::increaseFont()
{
	this->zoomOut();
}

void BaseCodeEditor::openOrCreateFile( const QString& fileName )
{
	if(QFile::exists(fileName))
	{
		QFile file(fileName);
		if (!file.open(QFile::ReadOnly)) 
		{
			QMessageBox::warning(this, tr("Application"),
				tr("Cannot read file %1:\n%2.")
				.arg(fileName)
				.arg(file.errorString()));
			return;
		}

		QTextStream in(&file);
		setText(in.readAll());
	}

	setFileName(fileName);
	setWindowTitle(QFileInfo(fileName).fileName());
	setModified(false);

	this->addWatchFile(_fileName);
}

void BaseCodeEditor::save()
{
	if(!this->isModified())
		return;

	this->removeWatchFile(_fileName);
	QFile file(_fileName);
	if (!file.open(QFile::WriteOnly)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot write file %1:\n%2.")
			.arg(_fileName)
			.arg(file.errorString()));
		return;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << this->text();
	file.close();
	QApplication::restoreOverrideCursor();

	setModified(false);
}


void BaseCodeEditor::onModificationChanged()
{
	if(isModified())
		setWindowTitle(QFileInfo(_fileName).fileName()+"*");
	else
		setWindowTitle(QFileInfo(_fileName).fileName());
}

void BaseCodeEditor::closeEvent(QCloseEvent *event)
{
	if(isModified())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle(tr("INSIDES Editor"));
		msgBox.setText(tr("Do you want to save the changes?\n\n")+
			tr("Choose 'Yes' to save the current file.\n")+
			tr("Choose 'No' to  discard the changes.\n")+
			tr("Choose 'Cancel' to stop closing the window")
			);
		msgBox.setIcon(QMessageBox::Warning);

		QPushButton *yesButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
		QPushButton *noButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
		QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

		msgBox.exec();

		if (msgBox.clickedButton() == yesButton)
		{
			save();
			emit widgetClosing(this);
			event->accept();
		}
		else if(msgBox.clickedButton() == noButton)
		{
			emit widgetClosing(this);
			event->accept();
		}
		else
		{
			event->ignore();
			return;
		}
	}
	else
	{
		emit widgetClosing(this);
		event->accept();
	}

	_watcher->removePaths(_watcher->files());
}

int BaseCodeEditor::getLineText(int lineId,QString& str)
{
	static char tmpLine[1024];
	int pos=this->SendScintilla(SCI_GETLINE,lineId,tmpLine);

	str=tmpLine;
	return pos;
}

int BaseCodeEditor::getFileStartPos(int pos)
{
	while(pos>=0){
		char ch = SendScintilla(SCI_GETCHARAT, --pos);
		switch(ch){
		case '\0':
		case '\n':
		case ' ':
		case '\t':
		case '\r':
		case ',':
		case '\\':
		case '/':
			return pos+1;
		}
	}
	return pos;
}

int BaseCodeEditor::getFileEndPos(int pos)
{
	while(true){
		char ch = SendScintilla(SCI_GETCHARAT, ++pos);
		switch(ch){
		case '\0':
		case '\n':
		case ' ':
		case '\t':
		case '\r':
		case ',':
		case '\\':
		case '/':
			return pos;
		}
	}
	return pos;
}

void BaseCodeEditor::contextMenuEvent( QContextMenuEvent *e )
{
	QMenu* menu=createStandardContextMenu();
	menu->setAttribute(Qt::WA_DeleteOnClose,true);
	{
		int pos=SendScintilla(SCI_GETCURRENTPOS);
		int startPos=getFileStartPos(pos);
		int stopPos=getFileEndPos(pos);
		int maxPos = SendScintilla(SCI_GETENDSTYLED);

		int len=stopPos-startPos;
		if(len>0 && len<1024 && stopPos < maxPos){
			static char buff[1024];
			SendScintilla(SCI_GETTEXTRANGE, startPos, stopPos, buff);
			QString fileName = bytesAsText(buff);
			QString ext=fileName.right(4);
			if(!ext.compare(".ins",Qt::CaseInsensitive) || !ext.compare(".tdy",Qt::CaseInsensitive))
				QAction* gotoAction=menu->addAction(tr("Open file")+":"+fileName,this,SLOT(onOpenFile()));

			bool flag=false;
			QString p = isPartEqualBefore(flag);
			if(flag && (!p.compare("PART",Qt::CaseInsensitive) || !p.compare("ASSEMBLY",Qt::CaseInsensitive) || _kList.contains(p,Qt::CaseInsensitive)))
			{
				QString str = getCurrentWords();
				QString fStr = getCurrentWords(true);
				QAction* gotoAction = menu->addAction(QString("Go to %1 Definition").arg(str),this,SLOT(onGotoDefinition()));
				gotoAction->setData(str + ";;" + fStr);
			}
		}
	}
	menu->exec(QCursor::pos());
}

void BaseCodeEditor::onOpenFile()
{
	QAction* ac=(QAction*)sender();
	if(ac){
		QString str=ac->text();
		QStringList vec=str.split(":");
		if(vec.size()>1){
			QString fileName=vec[vec.size()-1];
			QFileInfo info(_fileName);
			FileManager::instance()->notifyOpenFile(info.absolutePath()+"/"+fileName);
		}
	}
}

void BaseCodeEditor::addWatchFile( const QString& fileName )
{
	if(_watcher)
		_watcher->addPath(fileName);
}

void BaseCodeEditor::removeWatchFile( const QString& fileName )
{
	if(_watcher)
		_watcher->removePath(fileName);
}

void BaseCodeEditor::onFileChanged( const QString& fileName)
{
	static bool isShowMessage = false;
	if(isShowMessage)
		return;

	QMessageBox msgBox;
	msgBox.setText(fileName +"\n\n\n\n"
		"This file has been modified outside of the source editor.\n"
		"Do you want to reload it?");
	msgBox.setIcon(QMessageBox::Warning);

	QPushButton *yesButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
	QPushButton *deleteButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);

	isShowMessage = true;
	msgBox.exec();

	if (msgBox.clickedButton() == yesButton)
	{
		QFile file(fileName);
		if(file.exists())
			openOrCreateFile(fileName);
		else
			QMessageBox::information(this,"Sorry","File no longer exists !");
	}
	else
		return;

	isShowMessage = false;
}

void BaseCodeEditor::updatePartPrompt( const QString& type )
{
	QStringList list ;
	if(!type.compare("ASSEMBLY",Qt::CaseInsensitive))
		list<<"ASSEMBLY";
	else
		list<<"FEMPART"<<"RIGIDPART";
	_apis->clear();

	//得到当前光标处的条目
	LineItem* item = getAssItemByKeyword(getKeyWords(),getCurrentLineNumber());
	if(!item)
		return;

	QList<LineItem*> tmpList = item->getParent()->getItemList();
	foreach(LineItem* tmp,tmpList)
	{
		if(tmp->type == ASSEMBLYITEM && list.contains(tmp->keyname,Qt::CaseInsensitive))
			_apis->add(tmp->mainLabel);
	}
	_apis->prepare();
}

void BaseCodeEditor::onCursorPositionChanged( int line,int index )
{
	QString s = getCurrentWords();
	bool b = false;//是否有dq这个关键字
	QString dq = isPartEqualBefore(b).toUpper();
	if((!dq.compare("ASSEMBLY",Qt::CaseInsensitive) || !dq.compare("PART",Qt::CaseInsensitive))&& b)
	{
		updatePartPrompt(dq);
		return;
	}
	else if(b && !dq.isEmpty())
	{
		updateSomePos();
		if(_inYin)
			updateInYinWords();
		else if(_kList.contains(dq))
		{
			if(_keyValues.contains(s))
			{
				_apis->clear();

				foreach(QString sTmp,_keyValues[s])
					_apis->add(sTmp);

				_apis->prepare();

				return;
			}
			else
			{
				//填加同级下可引用的
				_apis->clear();
				LineItem* lineItem = getAssItemByKeyword(getKeyWords(),getCurrentLineNumber());
				if(!lineItem)
					return;

				QList<LineItem*> tmpList = lineItem->getParent()->getItemList();

				foreach(QString tmp,_keyValues.keys())
				{
					foreach(LineItem* item,tmpList)
					{
						if(!item->mainLabel.compare(tmp,Qt::CaseInsensitive) && !item->keyname.compare("INSTANCE",Qt::CaseInsensitive))
							_apis->add(tmp);
					}
				}

				_apis->prepare();
			}
		}
		else if(_cuLine == _keyWordLine)
		{
			_apis->clear();
			_apis->prepare();
		}
	}

	if(_isRunning)
		_textChangedTime = 0;
	else
	{
		_isRunning = true;
		_timer->start(5000);
	}

	updatePrompt();
	if(INSEditor::Document::instance()->getProperties()->isAutoShowHelp)
	{
		QString word =getCurrentWords();
		QString keyWord = getKeyWords();

		int line = getCurrentLineNumber();

		if(_proMap.keys().contains(word.toUpper()) && !word.isEmpty())
		{
			keyWord = word;
			SendScintilla(SCI_ANNOTATIONCLEARALL);
			showHelp(keyWord,word,line);
		}
		else if(_proMap[keyWord.toUpper()].contains(word,Qt::CaseInsensitive))
		{
			SendScintilla(SCI_ANNOTATIONCLEARALL);
			showHelp(keyWord,word,line);
		}
	}
	else
		SendScintilla(SCI_ANNOTATIONCLEARALL);
}

void BaseCodeEditor::onTextChanged()
{
	_needCompiling=true;
}

void BaseCodeEditor::updateAPI(QsciAPIs* apis)
{
	TDYTypeInfoManager manager;
	QString fileName = qApp->applicationDirPath() + "/settings/ins.xml";
	manager.load(fileName);
	_tdyInfoList = manager.getAllInfos();
	for(QMap<QString,TDYTypeInfoPtr>::Iterator it = _tdyInfoList.begin();it != _tdyInfoList.end();it++)
	{
		QString keyName = it.key();
		QSharedPointer<TDYTypeInfo> ptr = it.value();

		QList<QString> propertyList = ptr->propertyList;

		QList<TDYTypeKeyValuePtr> keyValueList = ptr->keyvalueList;

		apis->add(keyName);
		_allKeyNames.push_back(keyName);

		QStringList tmpProList;

		foreach(QString property,propertyList)
		{
			//			apis->add(keyName + "." + property);
			if(!property.isEmpty())
				tmpProList.push_back(property);
		}

		foreach(TDYTypeKeyValuePtr tmp,keyValueList)
		{
			//			apis->add(keyName + "." + tmp->keyName);
			if(!tmp->keyName.isEmpty())
				tmpProList.push_back(tmp->keyName);
		}
		tmpProList.sort();
		if(!keyName.isEmpty())
			_proMap[keyName] = tmpProList;
	}
}

void BaseCodeEditor::updatePrompt()
{
	QString keyWord = getKeyWords();

	updateSomePos();
	getKeyWords();

	if(_comPos>_numletPos && _comPos >_kuoPos)//先找到逗号
		updatePromptWords(keyWord);

	else if(_comPos ==-1 && _kuoPos==-1 && _numletPos==-1)
		updatePromptWords();
	else if(_inYin)
		updateInYinWords();
	else if((_kuoPos>_numletPos && _kuoPos >_comPos) ||(_numletPos > _comPos && _cuLine > _keyWordLine && _cuLine > _comLine) )
		updatePromptWords();
}

void BaseCodeEditor::updateInYinWords()
{
	_apis->clear();
	_apis->add("PARAMETER");
	_apis->prepare();
}

void BaseCodeEditor::updatePromptWords()
{
	_apis->clear();
	foreach(QString s,_allKeyNames)
		_apis->add(s);
	_apis->prepare();
}

void BaseCodeEditor::updatePromptWords( QString keyWord )
{
	QStringList tmpList = _proMap[keyWord.toUpper()];
	_apis->clear();

	foreach(QString s,tmpList)
		_apis->add(keyWord + "." + s);

	_apis->prepare();
}

bool BaseCodeEditor::eventFilter( QObject * object, QEvent * event )
{
	if(event->type() == QEvent::KeyPress)
	{
		QKeyEvent* e = static_cast<QKeyEvent*>(event);
		_currentKey = e->key();
	}
	if(event->type() == QEvent::KeyRelease)
	{
		QKeyEvent* e = static_cast<QKeyEvent*>(event);
		_currentKey = e->key();
		if(e->key() == Qt::Key_F1)
			showHelp();

		else if(e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
			onPressEnter();
		else if(e->key() == Qt::Key_P && (e->modifiers() & Qt::ControlModifier))
			onPressCtrlP();
		else if(e->key() == Qt::Key_Escape)
			SendScintilla(SCI_ANNOTATIONCLEARALL);
		else if(e->key() == Qt::Key_Equal)
			onPressEqual();
		else if(e->key() == Qt::Key_Comma)
			building();
	}
	return QsciScintilla::eventFilter(object,event);
}

QString BaseCodeEditor::getKeyWords()
{
	QString lineText;
	int cuLine = getCurrentLineNumber();
	getLineText(cuLine,lineText);

	while(cuLine > 0)
	{
		int p=0;
		bool flag = false;
		QString tmpStr;
		while(p<lineText.count())
		{
			if(lineText[p].isLetterOrNumber() || lineText[p] == '_')
			{
				flag = true;
				tmpStr += lineText[p];
			}
			else if(flag)
			{
				if(_proMap.contains(tmpStr.toUpper()))
				{
					_keyWordLine = cuLine;
					return tmpStr;
				}
			}
			p++;
		}
		cuLine--;

		getLineText(cuLine,lineText);
	}
	return QString();
}

QString BaseCodeEditor::isPartEqualBefore(bool& exist)
{
	QString keyWord;
	bool begin = false;
	bool flag = false;
	int pos=SendScintilla(SCI_GETCURRENTPOS);
	QString kw = getKeyWords().toUpper();

	while(pos >= 0)
	{
		QChar ch = SendScintilla(SCI_GETCHARAT, --pos);
		if(ch == ',' || ch == '{' || ch == '}')
		{
			if(!keyWord.isEmpty() && flag)
			{
				if(_proMap[kw].contains(keyWord,Qt::CaseInsensitive))
					exist = true;
				else 
					exist = false;

				return keyWord;
			}
			else 
				return QString();
		}

		if(ch == '=')
			flag = true;

		if(flag)
		{
			if(ch.isLetterOrNumber() || ch == '_')
			{
				keyWord = ch + keyWord;
				begin = true;
			}
			else if(begin)
				break;
		}
	}

	if(_proMap[kw].contains(keyWord,Qt::CaseInsensitive))
		exist = true;

	return keyWord;
}

QString BaseCodeEditor::getCurrentWords(bool isFullName)
{
	int pos = SendScintilla(SCI_GETCURRENTPOS);
	int maxPos = SendScintilla(SCI_GETENDSTYLED);
	QString tmpWord;
	QChar ch = SendScintilla(SCI_GETCHARAT,pos);

	bool flag = false;
	QList<QChar> chList;
	if(isFullName)
		chList<<'_'<<'.';
	else
		chList<<'_';

	while(pos >=0)
	{
		QChar tmp = SendScintilla(SCI_GETCHARAT,--pos);
		if(tmp.isLetterOrNumber() || chList.contains(tmp))
			flag = true;
		else if(flag)
			break;
	}

	while(pos < maxPos)
	{
		QChar tmp = SendScintilla(SCI_GETCHARAT,++pos);
		if(tmp.isLetterOrNumber() || chList.contains(tmp))
			tmpWord += tmp;
		else
			break;
	}

	return tmpWord;
}

void BaseCodeEditor::updatePartApi(INSEditor::Parse::LineItem* assItem,QString prefix)
{
	INSEditor::Parse::AssemblyItem* tmpAssItem = static_cast<INSEditor::Parse::AssemblyItem*>(assItem);

	QList<LineItem*> baseItemList = tmpAssItem->getItemList();
	foreach(LineItem* tmp,baseItemList)
	{
		if(tmp->type == LINEITEM)
			_apis->add(prefix+"."+tmp->mainLabel);
		else if(tmp->type == ASSEMBLYITEM)
		{
			_apis->add(prefix+"."+tmp->mainLabel);
			updatePartApi(tmp,prefix + "." + tmp->mainLabel);
		}
	}
}

void BaseCodeEditor::updatePromptWordsWithPart()
{
	QString k = getKeyWords();
	if(!_proMap[k].contains("part",Qt::CaseInsensitive) || !_assemblyItem)
		return;

	_apis->clear();
	QList<LineItem*> baseItemList = _assemblyItem->getItemList();
	foreach(LineItem* tmp,baseItemList)
	{
		if(tmp->type == ASSEMBLYITEM)
		{
			_apis->add(tmp->mainLabel);
			updatePartApi(tmp,tmp->mainLabel);
		}
	}

	_apis->prepare();
}

void BaseCodeEditor::onTimeouted()
{
	_textChangedTime += 1;//如果十秒之内内容未做改变，则不再刷新模型数据节约资源，当再次编辑时启动
	if(_textChangedTime == 5)
	{
		_isRunning = false;
		_timer->stop();
		building();
	}
}

void BaseCodeEditor::tidyAssItem( INSEditor::Parse::AssemblyItem* assItem )
{
	QList<LineItem*> itemList = assItem->getItemList();
	foreach(LineItem* tmp,itemList)
	{
		if(tmp->type == ASSEMBLYITEM)
			tidyAssItem(static_cast<INSEditor::Parse::AssemblyItem*>(tmp));
		else if(!tmp->keyname.compare("INSTANCE",Qt::CaseInsensitive))
			setKeyValues(tmp);
	}
}

void BaseCodeEditor::setKeyValues( INSEditor::Parse::LineItem* key )
{
	QString k = key->mainLabel;
	QString part;//引用的是谁？
	QString assembly;
	QList<KeyValueItem*> kvList = key->keyValues;
	foreach(KeyValueItem* tmp,kvList)
	{
		if(!tmp->keyname.compare("PART",Qt::CaseInsensitive) && tmp->valueList.count()>0)
		{
			part = tmp->valueList[0];
			break;
		}
		if(!tmp->keyname.compare("ASSEMBLY",Qt::CaseInsensitive)&& tmp->valueList.count() > 0)
		{
			assembly = tmp->valueList[0];
			break;
		}
	}
	_partRefItem = NULL;
	QStringList types;
	if(!part.isEmpty())
	{
		types<<"FEMPART"<<"RIGIDPART";
		getPartAssItem(part,_assemblyItem,types);
	}
	else if(!assembly.isEmpty())
	{
		types<<"ASSEMBLY";
		getPartAssItem(assembly,_assemblyItem,types);
	}
	else 
		return;

	if(!_partRefItem)
		return;

	QStringList list;
	updatePartStrList(_partRefItem,key->mainLabel,list);
	_keyValues[key->mainLabel] = list;
}

void BaseCodeEditor::updatePartStrList( INSEditor::Parse::AssemblyItem* assItem,QString key ,QStringList& list )
{
	QList<LineItem*> itemList = assItem->getItemList();
	foreach(LineItem* tmp , itemList)
	{
		if(tmp->type == ASSEMBLYITEM)
		{
			QString ml = tmp->mainLabel;
			QString instanceMainLabel;
			bool isPart;
			if(!tmp->keyname.compare("ASSEMBLY"))
				isPart = false;
			else
				isPart = true;

			foreach(LineItem* item,itemList)
			{
				if(item->keyname.compare("INSTANCE",Qt::CaseInsensitive))
					continue;

				foreach(KeyValueItem* kvItem,item->keyValues)
				{
					if(kvItem->valueList.isEmpty())
						continue;

					if(!isPart)
					{
						if(!kvItem->keyname.compare("ASSEMBLY",Qt::CaseInsensitive) && !kvItem->valueList[0].compare(ml,Qt::CaseInsensitive))
						{
							instanceMainLabel = item->mainLabel;
							break;
						}
					}
					else
					{
						if(!kvItem->keyname.compare("PART",Qt::CaseInsensitive) && !kvItem->valueList[0].compare(ml,Qt::CaseInsensitive))
						{
							instanceMainLabel = item->mainLabel;
							break;
						}
					}
				}
				if(!instanceMainLabel.isEmpty())
					break;
			}
			if(!instanceMainLabel.isEmpty())
				updatePartStrList(static_cast<AssemblyItem*>(tmp),key+"."+instanceMainLabel,list);
			else 
				updatePartStrList(static_cast<AssemblyItem*>(tmp),key,list);
		}
		else 
			list.push_back(key+"."+tmp->mainLabel);//非 assItem 比如 amrker 可以直接加入
	}
}

void BaseCodeEditor::getPartAssItem(const QString& mainLabel,INSEditor::Parse::AssemblyItem* assItem,const QStringList& types)
{
	if(!assItem->mainLabel.compare(mainLabel,Qt::CaseInsensitive) && types.contains(assItem->keyname,Qt::CaseInsensitive))
	{
		_partRefItem = assItem;
		return;
	}

	QList<LineItem*> lItemList = assItem->getItemList();
	foreach(LineItem* tmp,lItemList)
	{
		if(!tmp->mainLabel.compare(mainLabel,Qt::CaseInsensitive) && types.contains(assItem->keyname,Qt::CaseInsensitive))
		{
			_partRefItem = static_cast<AssemblyItem*>(tmp);
			return;
		}
		else if(tmp->type == ASSEMBLYITEM)
			getPartAssItem(mainLabel,static_cast<AssemblyItem*>(tmp),types);
	}
}

void BaseCodeEditor::showHelp()
{
	SendScintilla(SCI_ANNOTATIONCLEARALL);
	int line = getCurrentLineNumber();
	QString word =getCurrentWords();
	QString keyWord = getKeyWords();
	showHelp(keyWord,word,line);
}

void BaseCodeEditor::showHelp( QString keyWord,QString word,int line )
{
	if(!word.isEmpty())
	{
		if(!word.compare(keyWord,Qt::CaseInsensitive))
		{
			QMap<QString,INSEditor::Parse::TDYTypeInfoPtr>::Iterator it = _tdyInfoList.find(word.toUpper());
			QString tmp = word;
			if(it->value->helpString.isEmpty())
				word = tr("The keyword %1 has no associated help ").arg(tmp);
			else
				word = it->value->helpString;
		}
		else
		{ //下级关键字的帮助
			if(_proMap[keyWord].contains(word))
			{
				QMap<QString,INSEditor::Parse::TDYTypeInfoPtr>::Iterator it = _tdyInfoList.find(keyWord.toUpper());
				foreach(TDYTypeKeyValuePtr keyValue,it->value->keyvalueList)
				{
					if(!word.compare(keyValue->keyName))
					{
						if(keyValue->helpString.isEmpty())
							word = tr("The keyword %1 has no associated help ").arg(word);
						else
							word = keyValue->helpString;
						break;
					}
				}
			}
			else
				word = tr("The keyword %1 is nonexistence").arg(word);
		}

		QByteArray ba = word.toUtf8();//toLatin1 不支持中文
		const char* lParam = strdup(ba.data()); 

		SendScintilla(SCI_ANNOTATIONSETTEXT,line,lParam);
		SendScintilla(SCI_ANNOTATIONSETVISIBLE,ANNOTATION_BOXED);
	}
}

void BaseCodeEditor::updateSomePos()
{
	_comLine=-1;_cuLine=-1;_numletPos=-1;_numletLine=-1;_comPos=-1;_kuoPos=-1;_yinPos=-1;_dengPos=-1;
	_inYin=false;

	_cuLine = getCurrentLineNumber();
	getKeyWords();
	int pos = SendScintilla(SCI_GETCURRENTPOS);
	while(pos >= 0)
	{
		QChar ch = SendScintilla(SCI_GETCHARAT, --pos);
		if(ch == ',')
		{
			_comLine = SendScintilla(SCI_LINEFROMPOSITION,pos);
			break;
		}
	}

	int tmpPos = SendScintilla(SCI_GETCURRENTPOS) ;
	QChar ch = SendScintilla(SCI_GETCHARAT, tmpPos);

	if((ch == 10 || ch == 13) && (_currentKey == Qt::Key_Enter || _currentKey == Qt::Key_Return))
		_cuLine++;

	while(tmpPos >= 0)
	{
		ch = SendScintilla(SCI_GETCHARAT, tmpPos--);
		if(ch.isLetterOrNumber() || ch == '_')
		{
			if(_numletPos==-1)
				_numletPos=tmpPos;
			if(_numletLine == -1)
				_numletLine = SendScintilla(SCI_LINEFROMPOSITION,tmpPos);
		}
		else if(ch == ',')
		{
			if(_comPos==-1)
				_comPos=tmpPos;
		}
		else if(ch == '}' || ch=='{')
		{
			if(_kuoPos==-1)
				_kuoPos=tmpPos;
		}
		else if(ch == '=')
		{
			if(_dengPos == -1)
				_dengPos = tmpPos;
		}
		else if(ch == '"')
		{
			if(_inYin)
				_inYin = false;
			else
				_inYin = true;

			if(_yinPos == -1)
				_yinPos = tmpPos;
		}
	}
}

LineItem* BaseCodeEditor::getAssItemByKeyword(const QString& keyword,int line)
{
	if(!_assemblyItem)
		return NULL;
	QList<LineItem*> itemList = _assemblyItem->getItemList();
	QList<LineItem*> tmpList;

	foreach(LineItem* tmp,itemList)
	{
		if(!tmp->keyname.compare(keyword,Qt::CaseInsensitive))
			tmpList.push_back(tmp);
		else if(tmp->type == ASSEMBLYITEM)
			getAssItemByKeyword(static_cast<AssemblyItem*>(tmp),keyword,tmpList);
	}
	LineItem* result = NULL;
	foreach(LineItem* tmp,tmpList)
	{
		if(tmp->rowIndex <= line && !result)
			result = tmp;

		if(tmp->rowIndex <=line && tmp->rowIndex > result->rowIndex)
			result = tmp;
	}
	return result;
}

void BaseCodeEditor::getAssItemByKeyword(INSEditor::Parse::AssemblyItem* item,const QString& keyword,QList<INSEditor::Parse::LineItem*>& list)
{
	QList<LineItem*> itemList = item->getItemList();

	foreach(LineItem* tmp,itemList)
	{
		if(!tmp->keyname.compare(keyword,Qt::CaseInsensitive))
			list.push_back(tmp);

		if(tmp->type == ASSEMBLYITEM)
			getAssItemByKeyword(static_cast<AssemblyItem*>(tmp),keyword,list);
	}
}

void BaseCodeEditor::onPressEnter()
{
	updateSomePos();
	getKeyWords();

	if(_cuLine >= _comLine + 2)
	{
		if(_comPos > _numletPos)
		{
			QString kw = getKeyWords();
			updatePromptWords(kw);
		}
		else if(_numletPos > _comPos)
			updatePromptWords();
	}
}

void BaseCodeEditor::onPressCtrlP()
{
	updateSomePos();
	QString kw = getKeyWords();
	if(_comPos > _numletPos)
	{
		_apis->clear();
		QString tmp = _proMap[kw.toUpper()].join("-");

		tmp = tmp.trimmed();
		QByteArray ba = tmp.toUtf8();//toLatin1 不支持中文
		const char* lParam = strdup(ba.data()); 

		SendScintilla(SCI_AUTOCSETSEPARATOR,'-');
		SendScintilla(SCI_AUTOCSHOW,lParam);
	}
	else if((_kuoPos>_numletPos && _kuoPos >_comPos) ||(_numletPos > _comPos && _cuLine > _numletLine))
	{
		_apis->clear();
		QString tmp;
		foreach(QString tStr,_proMap.keys())
			if(!tStr.isEmpty())
				tmp += tStr + "-";

		tmp = tmp.trimmed();
		if(!tmp.isEmpty())
			tmp.remove(tmp.size()-1,1);
		QByteArray ba = tmp.toUtf8();//toLatin1 不支持中文
		const char* lParam = strdup(ba.data()); 
		SendScintilla(SCI_AUTOCSETSEPARATOR,'-');
		SendScintilla(SCI_AUTOCSHOW,lParam);
	}
}

void BaseCodeEditor::onPressEqual()
{
	bool flag = false;
	QString p = isPartEqualBefore(flag);
	QStringList assStr,partStr;

	LineItem* lineItem = getAssItemByKeyword(getKeyWords(),getCurrentLineNumber());
	if(!lineItem)
		return;
	_apis->clear();
	QList<LineItem*> tmpList = lineItem->getParent()->getItemList();

	QString kname = getKeyWords();
	if(!kname.compare("MARKER",Qt::CaseInsensitive))
	{
		foreach(LineItem* item , tmpList)
		{
			if(!item->keyname.compare("INSTANCE",Qt::CaseInsensitive) && item->rowIndex < lineItem->rowIndex)
				partStr<<item->mainLabel;
		}
	}
	else
	{
		foreach(LineItem* item , tmpList)
		{
			if(item->type == ASSEMBLYITEM && item->rowIndex < lineItem->rowIndex)
			{
				if(!item->keyname.compare("ASSEMBLY",Qt::CaseInsensitive))
					assStr<<item->mainLabel;
				else
					partStr<<item->mainLabel;
			}
		}
	}

	if(flag)
	{
		QString tmp;
		if(!p.compare("PART",Qt::CaseInsensitive))
			tmp = partStr.join("-").trimmed();
		else if(!p.compare("ASSEMBLY",Qt::CaseInsensitive))
			tmp = assStr.join("-").trimmed();
		else if(!p.compare("MATERIAL",Qt::CaseInsensitive)) 
		{
			/*tmp = "paint.medium_rough_plaster_wall-misc.glass-fabric.leather-fabric.car_interior_plush-metal.brushed_metal-"
				"fabric.car_seat_fabric-stone.orange_granite-metal.brass-stone.salmon_granite-paint.smooth_plaster_wall-"
				"stone.green_granite-metal.brushed_metal_discs-metal.chrome-metal.painted_cast_metal-paint.metallic_paint-wood.floorboards_bamboo-misc.concrete-metal.plain_metal-"
				"metal.cast_aluminum-stone.spectrolite_granite-wood.car_panel_walnut-wood.construction_pine-fabric.car_seat_fabric_diamonds-"
				"paint.car_paint-metal.copper-wood.floorboards_oak-wood.oak";*/
			tmp = _materialStr;
		}
		else if(_kList.contains(p,Qt::CaseInsensitive))
		{
			foreach(QString tmpS,_keyValues.keys())
			{
				foreach(LineItem* item,tmpList)
				{
					if(!item->mainLabel.compare(tmpS,Qt::CaseInsensitive) && !item->keyname.compare("INSTANCE",Qt::CaseInsensitive) && item->rowIndex <lineItem->rowIndex)
						tmp += tmpS + "-";
				}
			}
			tmp.trimmed();
			if(!tmp.isEmpty())
				tmp.remove(tmp.size()-1,1);
		}

		if(tmp.isEmpty())
			return;

		QByteArray ba = tmp.toUtf8();//toLatin1 不支持中文
		const char* lParam = strdup(ba.data()); 
		SendScintilla(SCI_AUTOCSETSEPARATOR,'-');
		SendScintilla(SCI_AUTOCSHOW,lParam);
	}
}

void BaseCodeEditor::onGotoDefinition()
{
	QAction* ac = static_cast<QAction*>(sender());
	QString mainLabel,fMainLabel;
	QString tmpStr = ac->data().toString();
	if(tmpStr.split(";;")[0] == tmpStr.split(";;")[1])
		mainLabel = tmpStr.split(";;")[0];
	else
	{
		mainLabel = tmpStr.split(";;")[0];
		fMainLabel = tmpStr.split(";;")[1];
	}

	if(mainLabel.isEmpty())
		return;

	LineItem* item = getAssItemByKeyword(getKeyWords(),getCurrentLineNumber());
	if(!item)
		return;
	QList<LineItem*>list = item->getParent()->getItemList();
	if(fMainLabel.isEmpty())
	{
		foreach(LineItem* tmp,list)
		{
			if(tmp->type == ASSEMBLYITEM && !tmp->mainLabel.compare(mainLabel,Qt::CaseInsensitive))
			{
				SendScintilla(SCI_GOTOLINE,tmp->rowIndex);
				break;
			}
		}
	}
	else
	{
		QStringList strList;//按这个查找
		foreach(QString str , fMainLabel.split("."))
		{
			strList.push_back(str);
			if(!mainLabel.compare(str,Qt::CaseInsensitive))
				break;
		}

		LineItem* resultItem=item->getParent();

		for (int i=0;i<strList.count();i++)
			resultItem = getGotoItem(strList,i,resultItem);

		if(resultItem != item && resultItem)
			SendScintilla(SCI_GOTOLINE,resultItem->rowIndex);
	}
}

LineItem* BaseCodeEditor::getGotoItem( QStringList list,int pos,LineItem* item )
{
	QString str = list[pos];
	QList<LineItem*> itemList = static_cast<AssemblyItem*>(item)->getItemList();
	foreach(LineItem* tmp,itemList)
	{
		if(!tmp->mainLabel.compare(str))
		{
			if(pos == list.count() -1)
				return tmp;
			else
			{
				QString assMainLabel;
				foreach(KeyValueItem* kvItem,tmp->keyValues)
				{
					if((!kvItem->keyname.compare("PART",Qt::CaseInsensitive) || !kvItem->keyname.compare("ASSEMBLY",Qt::CaseInsensitive)) && !kvItem->valueList.isEmpty())
					{
						assMainLabel = kvItem->valueList[0];
						break;
					}
				}
				foreach(LineItem* assTmp,itemList)
				{
					if(assTmp->type == ASSEMBLYITEM && !assTmp->mainLabel.compare(assMainLabel))
						return assTmp;
				}
			}
		}
	}
	return NULL;
}

void BaseCodeEditor::building()
{
	delete _assemblyItem;
	_assemblyItem = NULL;
	_assemblyItem=_parser.parseFile(this->text(),this->getFileName(),true);
	if(!_assemblyItem)
		return;

	_parser.compileAssemblyItem(_assemblyItem,this->getFileName(),_typeManager.getAllInfos());
	tidyAssItem(_assemblyItem);
}

void BaseCodeEditor::initMaterial()
{
	QString materialRoot = qApp->applicationDirPath()+"/material/";
	QDir materialDir(materialRoot);
	if(!materialDir.exists())
		return;

	QStringList list = materialDir.entryList(QDir::AllDirs|QDir::NoDotAndDotDot);
	if(list.isEmpty())
		return;

	foreach(QString folder,list)
	{
		QString tmpStr = materialRoot + folder;
		QDir tmpDir(tmpStr);
		QStringList tmpStrList = tmpDir.entryList(QDir::Files|QDir::NoDotAndDotDot);
		foreach(QString file,tmpStrList)
		{
			QString str = "\"" + folder + "/" + file + "\"";
			if(_materialStr.isEmpty())
				_materialStr += str;
			else
				_materialStr += "-" + str;
		}
	}
}

