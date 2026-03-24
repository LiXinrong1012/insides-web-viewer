#include "mdiarea.h"

#include "ribbonwindow.h"
#include "basecodeeditor.h"
#include "viewerwrapper.h"
#include "findresultsmanager.h"
#include "findresultwidget.h"
#include "edparsesingleton.h"

#include "edcore/console.h"
#include "edcore/compileinfomanager.h"
#include "edcore/errormanager.h"
#include "edcore/filemanager.h"
#include "edcore/document.h"
#include "edcore/solution.h"
#include "edcore/project.h"
#include "edcore/entity.h"

#include "edparse/isearchreplacedialog.h"

#include "edcompile/modelparser.h"
#include "edcompile/tdytypeinfomanager.h"

#include "Qsci/qscilexer.h"

#include <QtGui>


/* MdiArea */
MdiArea::MdiArea(QWidget* parent,ViewerWrapper* viewWrapper) 
	: QMdiArea(parent) 
	,_currentActivatedWindow(NULL)
	,_viewerWrapper(viewWrapper)
{
	setTabsClosable(true);

	connect(this,SIGNAL(subWindowActivated ( QMdiSubWindow*)),this,SLOT(onSubWindowActivated(QMdiSubWindow*)));

	_compileTimer=new QTimer(this);
	_compileTimer->setInterval(3000);
	connect(_compileTimer,SIGNAL(timeout()),this,SLOT(onCompileTimer()));

	connect(FileManager::instance(),SIGNAL(requestGotoPosition(const QString&,int,int)),
		this,SLOT(onGotoPosition(const QString&,int,int)));
	
	_compileTimer->start();

	// connect find result window
	FindResultWidget* f=FindResultsManager::instance()->getResultWidget(0);

	if(f)
		connect(f,SIGNAL(resultItemClicked(const FindResultItem&)),this,SLOT(onFindResultItemActivated(const FindResultItem&)));

	f=FindResultsManager::instance()->getResultWidget(1);

	if(f)
		connect(f,SIGNAL(resultItemClicked(const FindResultItem&)),this,SLOT(onFindResultItemActivated(const FindResultItem&)));
}

MdiArea::~MdiArea() 
{
	_compileTimer->stop();
}

void MdiArea::paintEvent(QPaintEvent* paintEvent)
{
	Q_UNUSED(paintEvent);
	QPainter painter(viewport());
	QStyleOption opt;
	opt.init(this);
	if (paintEvent->rect().intersects(opt.rect))
		style()->drawPrimitive((QStyle::PrimitiveElement)CommonStyle::PE_Workspace, &opt, &painter, this);
}

void MdiArea::onWidgetClosing( BaseCodeEditor* w )
{
	QString fileName=w->getFileName();
	w->removeWatchFile(fileName);
	_windows.remove(fileName);
}

void MdiArea::addMyWindow( BaseCodeEditor* w )
{
	QMdiSubWindow* tmp=addSubWindow(w);
	initSubWindowMenu(tmp,w);
	QString fileName = w->getFileName();
	w->addWatchFile(fileName);

	setActiveSubWindow(tmp);
	w->showMaximized();
	connect(w,SIGNAL(widgetClosing(BaseCodeEditor*)),this,SLOT(onWidgetClosing(BaseCodeEditor*)));
	_windows[w->getFileName()]=tmp;
}

QMdiSubWindow* MdiArea::getMyWidget( const QString& fileName )
{
	if(_windows.find(fileName)==_windows.end())
		return NULL;

	return _windows[fileName];
}

QString MdiArea::getCurrentFile( QMdiSubWindow* window )const
{
	if(!window)
		return QString();

	QMapIterator<QString,QMdiSubWindow*> iter(_windows);
	while (iter.hasNext()) {
		iter.next();
		if(iter.value() == window)
			return iter.key();
	}

	return QString();
}

void MdiArea::onSubWindowActivated( QMdiSubWindow* window )
{
	if(!window)
		return;

	BaseCodeEditor* tmp=(BaseCodeEditor*)window->widget();

	if(tmp){
		QString fileName=tmp->getFileName();
		QList<INSEditor::Project*> projects = INSEditor::Document::instance()->getSolution()->getAllProjects();
		foreach(INSEditor::Project* pro,projects)
		{
			QList<INSEditor::Entity*> entityList = pro->getEntities();
			foreach(INSEditor::Entity* entity,entityList)
			{
				if(!entity->getFullFileName().compare(fileName,Qt::CaseInsensitive))
				{
					INSEditor::Document::instance()->getSolution()->setMainProject(pro);

					if(INSEditor::Document::instance()->getProperties()->isCreateModelTree)
					{
						INSEditor::Parse::ModelParser parser;
						INSEditor::Parse::AssemblyItem* item=parser.parseFile(tmp->text(),fileName);
						INSEditor::Parse::TDYTypeInfoManager typeManager;
						typeManager.loadFromTDYTemplate(qApp->applicationDirPath()+"/settings/ins.xml");
						parser.compileAssemblyItem(item,typeManager.getAllInfos());

						FileManager::instance()->notifyUpdateModel(item,fileName);
						FileManager::instance()->notifyExpandModelTree();
					}
					return;
				}
			}
		}
	}
}


void MdiArea::onCompileTimer()
{
	////Base::Console().Log("Is compiling file...")	;
	//QList<QMdiSubWindow*> windows=this->subWindowList();
	//foreach(QMdiSubWindow* subWindow,windows){
	//	BaseCodeEditor* editor=(BaseCodeEditor*)subWindow->widget();
	//	if(editor){
	//		if(editor->needCompiling()){
	//			QString text=editor->text();
	//			myProject()->getErrorItemManager()->clear(editor->getFileName());
	//			Parse::FileItem* item=_edparsePlugin->parse(text,editor->getFileName(),true);
	//				
	//			myProject()->getCompileInfoManager()->setItem(editor->getFileName(),item);

	//			editor->setNeedCompiling(false);
	//		}
	//	}
	//}
}

void MdiArea::onGotoPosition( const QString& fullFileName,int rowIndex,int columnIndex )
{
	activateOrOpenFile(fullFileName);
	BaseCodeEditor* editor=(BaseCodeEditor*)activeSubWindow()->widget();
	if(editor)
		editor->setCursorPosition(rowIndex,columnIndex);
}

void MdiArea::activateOrOpenFile( const QString& fileName )
{
	if(fileName.isEmpty())
		return;

	QMdiSubWindow* tmp=getMyWidget(fileName);
	if(tmp){
		setActiveSubWindow(tmp);
		return;
	}

	BaseCodeEditor* newEditor=new BaseCodeEditor(this);
	newEditor->openOrCreateFile(fileName);
	connect(newEditor,SIGNAL(gotoFile(const QString&)),this,SLOT(activateOrOpenFile(const QString&)));
	QApplication::restoreOverrideCursor();

	addMyWindow(newEditor);
}

void MdiArea::createRibbonBar( Qtitan::RibbonPage* page )
{
	_increaseFont=new QAction(tr("Increase Font"),this);
	_increaseFont->setShortcut(QKeySequence::ZoomOut);
	connect(_increaseFont, SIGNAL(activated()),this, SLOT(increaseFont()));

	_decreaseFont=new QAction(tr("Decrease Font"),this);
	_decreaseFont->setShortcut(QKeySequence::ZoomIn);
	connect(_decreaseFont, SIGNAL(activated()),this, SLOT(decreaseFont()));

	createGroupFont(page->addGroup(tr("Font")));
	createGroupEditing(page->addGroup(QIcon(":/resources/menu.font/f007.png"), tr("Editing")));
}
void MdiArea::optionFont()
{
	bool ok = false;
	QFont font = QFontDialog::getFont(&ok, BaseCodeEditor::getTextFont(), this);
	if (ok) 
		BaseCodeEditor::setTextFont(font);
}

void MdiArea::textBold()
{
	QFont font=BaseCodeEditor::getTextFont();
	font.setBold(_actionTextBold->isChecked());
	updateFont(font);
}

void MdiArea::textItalic()
{
	QFont font=BaseCodeEditor::getTextFont();
	font.setItalic(_actionTextItalic->isChecked());
	updateFont(font);
}

void MdiArea::textFamily(const QString &f)
{
	QFont font=BaseCodeEditor::getTextFont();
	font.setFamily(f);
	updateFont(font);
}

void MdiArea::textSize(const QString &p)
{
	qreal pointSize = p.toFloat();
	if (p.toFloat() > 0) 
	{
		QFont font=BaseCodeEditor::getTextFont();
		font.setPointSizeF(pointSize);
		updateFont(font);
	}
}

void MdiArea::createGroupFont( Qtitan::RibbonGroup* group )
{
	Qtitan::RibbonGroup* groupFont=group;
	//if(Qtitan::RibbonGroup* groupFont = page->addGroup(QIcon(":/res/smallfontgrow.png"), tr("Font"))) 
	groupFont->setOptionButtonVisible();
	QAction* act = groupFont->optionButtonAction();
	act->setText(tr("F&ont"));
	act->setIcon(QIcon(":/resources/menu/font/f001.png"));
	act->setToolTip(tr("Show the Font dialog box"));
	act->setStatusTip(tr("Show the Font dialog box"));
	connect(act, SIGNAL(triggered()), this, SLOT(optionFont()));

	groupFont->setControlsGrouping();
	groupFont->setControlsCentering();

	_comboFont = new QFontComboBox();
	_comboFont->setMaximumWidth(130);
	groupFont->addWidget(_comboFont);
	connect(_comboFont, SIGNAL(activated(QString)), this, SLOT(textFamily(QString)));

	_comboSize = new QComboBox();
	_comboSize->setMaximumWidth(45);
	_comboSize->setObjectName("m_comboSize");
	groupFont->addWidget(_comboSize);
	_comboSize->setEditable(true);

	QFontDatabase db;
	foreach(int size, db.standardSizes())
		_comboSize->addItem(QString::number(size));

	connect(_comboSize, SIGNAL(activated(QString)), this, SLOT(textSize(QString)));
	_comboSize->setCurrentIndex(_comboSize->findText(QString::number(QApplication::font().pointSize())));

	groupFont->addSeparator();
	QAction* _actionGrowFont=groupFont->addAction(QIcon(":/resources/menu/font/f003.png"), tr("Grow Font"), Qt::ToolButtonIconOnly);
	connect(_actionGrowFont,SIGNAL(triggered()),this,SLOT(increaseFont()));

	QAction* _actionShrinkFont=groupFont->addAction(QIcon(":/resources/menu/font/f004.png"), tr("Shrink Font"), Qt::ToolButtonIconOnly);
	connect(_actionShrinkFont,SIGNAL(triggered()),this,SLOT(decreaseFont()));

	groupFont->addSeparator();
	groupFont->addAction(QIcon(":/resources/menu/font/f002.png"), tr("&Clear Formatting"), Qt::ToolButtonIconOnly);
	groupFont->addSeparator();

	_actionTextBold = groupFont->addAction(QIcon(":/resources/menu/font/f005.png"), tr("&Bold"), Qt::ToolButtonIconOnly);
	_actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
	_actionTextBold->setPriority(QAction::LowPriority);
	QFont bold;
	bold.setBold(true);
	_actionTextBold->setFont(bold);
	connect(_actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
	_actionTextBold->setCheckable(true);

	_actionTextItalic = groupFont->addAction(QIcon(":/resources/menu/font/f006.png"), 
		tr("&Italic"), Qt::ToolButtonIconOnly);
	_actionTextItalic->setPriority(QAction::LowPriority);
	_actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
	QFont italic;
	italic.setItalic(true);
	_actionTextItalic->setFont(italic);
	connect(_actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
	_actionTextItalic->setCheckable(true);
}

void MdiArea::decreaseFont()
{
	QFont font=BaseCodeEditor::getTextFont();
	font.setPointSize(font.pointSize()-1);
	updateFont(font);
}

void MdiArea::increaseFont()
{
	QFont font=BaseCodeEditor::getTextFont();
	font.setPointSize(font.pointSize()+1);
	updateFont(font);
}

void MdiArea::updateFont( const QFont& font )
{
	QList<QMdiSubWindow*> windows=this->subWindowList();
	foreach(QMdiSubWindow* w,windows){
		BaseCodeEditor* editor=(BaseCodeEditor*)w->widget();
		editor->lexer()->setFont(font);
	}
	BaseCodeEditor::setTextFont(font);
}

void MdiArea::createGroupEditing(Qtitan::RibbonGroup* groupEditing)
{
	QAction* actionFind = new QAction(QIcon(":/resources/menu/font/f007.png"), tr("Find"), this);
	actionFind->setShortcut(Qt::CTRL + Qt::Key_F);
	actionFind->setStatusTip(tr("Find the specified text"));
	connect(actionFind,SIGNAL(triggered()),this,SLOT(openFindDialog()));

	QAction* actionGoto = new QAction(QIcon(":/resources/menu/font/f008.png"), tr("Go To"), this);
	actionGoto->setStatusTip(tr("Navigate to a specific page, line, numer, footnote, comment, or other object"));
	actionGoto->setEnabled(false);

	QMenu* findMenu = new QMenu(this);
	findMenu->addAction(actionFind);
	findMenu->addAction(actionGoto);
	groupEditing->addAction(actionFind, Qt::ToolButtonTextBesideIcon, findMenu);

	QAction* actionReplace = groupEditing->addAction(QIcon(":/resources/menu/font/f009.png"), tr("Replace"), 
		Qt::ToolButtonTextBesideIcon);
	actionReplace->setShortcut(Qt::CTRL + Qt::Key_H);
	actionReplace->setStatusTip(tr("Replace specific text with different text"));
	connect(actionReplace,SIGNAL(triggered()),this,SLOT(openReplaceDialog()));

	QMenu* selectMenu = groupEditing->addMenu(QIcon(":/resources/menu/font/f010.png"), tr("Select"));

	QAction* m_actionSelectAll = new QAction(tr("Select All"), this);
	m_actionSelectAll->setShortcut(Qt::CTRL + Qt::Key_A);
	m_actionSelectAll->setStatusTip(tr("Select the entire document"));
	selectMenu->addAction(m_actionSelectAll);
	connect(m_actionSelectAll, SIGNAL(triggered()), this, SLOT(selectAll()));

	QAction* pActionSelectObjects = new QAction(tr("Select Objects"), this);
	pActionSelectObjects->setEnabled(false);
	selectMenu->addAction(pActionSelectObjects);

	QAction* pActionSelectMultipleObjects = new QAction(tr("Select Multiple Objects"), this);
	pActionSelectMultipleObjects->setEnabled(false);
	selectMenu->addAction(pActionSelectMultipleObjects);
}

void MdiArea::openFindDialog()
{
	EDParseSingleton::instance()->getPlugin()->getSearchReplaceDialog()->setTypeFindOrReplace(true);
	EDParseSingleton::instance()->getPlugin()->getSearchReplaceDialog()->show();
}
void MdiArea::openReplaceDialog()
{
	EDParseSingleton::instance()->getPlugin()->getSearchReplaceDialog()->setTypeFindOrReplace(false);
	EDParseSingleton::instance()->getPlugin()->getSearchReplaceDialog()->show();
}
void MdiArea::onFindNext()
{
	QMdiSubWindow* subWindow=this->activeSubWindow();
	if(subWindow && (BaseCodeEditor*)subWindow->widget())
	{
		BaseCodeEditor* editor=(BaseCodeEditor*)subWindow->widget();
		ISearchReplaceDialog* dialog=EDParseSingleton::instance()->getPlugin()->getSearchReplaceDialog();
		editor->findFirst(dialog->getSearchContent(),
			dialog->isUseSearch(),
			dialog->isCaseSensitiveSearch(),
			dialog->isCaseWholeWordsSearch(),
			false);
	}	
}

void MdiArea::onFindPrevious()
{
}

void MdiArea::onReplaceNext()
{
	QMdiSubWindow* subWindow=this->activeSubWindow();
	if(subWindow && (BaseCodeEditor*)subWindow->widget())
	{
		BaseCodeEditor* editor=(BaseCodeEditor*)subWindow->widget();
		ISearchReplaceDialog* dialog=EDParseSingleton::instance()->getPlugin()->getSearchReplaceDialog();
		editor->replace(dialog->getReplaceContent());
		editor->findFirst(dialog->getSearchContent(),
			dialog->isUseSearch(),
			dialog->isCaseSensitiveSearch(),
			dialog->isCaseWholeWordsSearch(),
			false);
	}	
}

void MdiArea::onReplaceAll()
{
	QMdiSubWindow* subWindow=this->activeSubWindow();
	if(subWindow && (BaseCodeEditor*)subWindow->widget())
	{
		BaseCodeEditor* editor=(BaseCodeEditor*)subWindow->widget();
		onGotoPosition(editor->getFileName(),0,0);
		while(true)
		{
			ISearchReplaceDialog* dialog=EDParseSingleton::instance()->getPlugin()->getSearchReplaceDialog();
			editor->replace(dialog->getReplaceContent());
			bool flag = editor->findFirst(dialog->getSearchContent(),
				dialog->isUseSearch(),
				dialog->isCaseSensitiveSearch(),
				dialog->isCaseWholeWordsSearch(),
				false);
			if(!flag)
				break;
		}
	}
}

void MdiArea::setEDParsePlugin( EDParsePlugin* p )
{
	_edparsePlugin=p;
	ISearchReplaceDialog* dialog=p->getSearchReplaceDialog();
	connect(dialog,SIGNAL(sigFindNext()),this,SLOT(onFindNext()));
	connect(dialog,SIGNAL(sigFindPrevious()),this,SLOT(onFindPrevious()));
	connect(dialog,SIGNAL(sigFindAll()),this,SLOT(onFindAll()));
	connect(dialog,SIGNAL(sigReplace()),this,SLOT(onReplaceNext()));
	connect(dialog,SIGNAL(sigReplaceAll()),this,SLOT(onReplaceAll()));
}

void MdiArea::onFindAll()
{
	ISearchReplaceDialog* dialog=EDParseSingleton::instance()->getPlugin()->getSearchReplaceDialog();

	QDockWidget* d1=FindResultsManager::instance()->getResultDock(dialog->isOpenResultOnPage1Search()?0:1);
	d1->raise();
	FindResultWidget* w=FindResultsManager::instance()->getResultWidget(dialog->isOpenResultOnPage1Search()?0:1);

	w->addFirst(dialog->getSearchContent());

	QList<QMdiSubWindow*> subWindows;
	if(dialog->getSearchPlace()==ISearchReplaceDialog::SearchInCurrentDocument){
		if(activeSubWindow())
			subWindows.push_back(activeSubWindow());
	}
	else{
		if(dialog->getSearchPlace()==ISearchReplaceDialog::SearchAll){
			// open all document
			openAllDocuments();
		}

		subWindows=this->subWindowList();
	}

	int fileCount=0;
	foreach(QMdiSubWindow* window,subWindows)
		findInWindow(window)?fileCount++:0;

	w->addEnd(fileCount,subWindows.size());
	w->scrollToBottom();
	d1->show();
}

bool MdiArea::findInWindow(QMdiSubWindow* subWindow)
{
	bool found=false;
	if(subWindow && (BaseCodeEditor*)subWindow->widget())
	{
		ISearchReplaceDialog* dialog=EDParseSingleton::instance()->getPlugin()->getSearchReplaceDialog();
		FindResultWidget* w=FindResultsManager::instance()->getResultWidget(dialog->isOpenResultOnPage1Search()?0:1);
		BaseCodeEditor* editor=(BaseCodeEditor*)subWindow->widget();
		editor->setCursorPosition(0,0);
		bool result=editor->findFirst(dialog->getSearchContent(),
			dialog->isUseSearch(),
			dialog->isCaseSensitiveSearch(),
			dialog->isCaseWholeWordsSearch(),
			false);
		while(result){
			FindResultItem item;
			editor->getSelection(&item.lineFrom,&item.indexFrom,&item.lineTo,&item.indexTo);
			item.fileName=editor->getFileName();
			item.text=editor->text(item.lineFrom).trimmed();
			w->addResultItem(item);
			found=true;

			result=editor->findNext();
		}
	}	
	return found;
}

void MdiArea::onFindResultItemActivated( const FindResultItem& resultItem )
{
	QMdiSubWindow* subWindow= getMyWidget(resultItem.fileName);
	if(subWindow){
		setActiveSubWindow(subWindow);
		BaseCodeEditor* editor=(BaseCodeEditor*)subWindow->widget();
		editor->setSelection(resultItem.lineFrom,resultItem.indexFrom,resultItem.lineTo,resultItem.indexTo);
	}
}

void MdiArea::openAllDocuments()
{
	//INSProject* project=INSProject::instance();
	//QList<INSEntity*> allEntities=project->getAllEntities();

	//foreach(INSEntity* entity,allEntities)
	//{
	//	if(entity->getType()==INS_FILE  && 
	//		(!entity->getFileExt().compare("INS",Qt::CaseInsensitive) ||
	//		!entity->getFileExt().compare("TDY",Qt::CaseInsensitive)))
	//	{
	//		this->activateOrOpenFile(entity->getFullFileName());
	//	}
	//}
}

void MdiArea::initSubWindowMenu( QMdiSubWindow* tmp,BaseCodeEditor* w )
{
	QMenu* menu = tmp->systemMenu();
	menu->clear();
	QFileInfo info(w->getFileName());

	QAction* ac = menu->addAction("Save "+ info.fileName());
	ac->setShortcut(tr("Ctrl+S"));
	ac->setIcon(QIcon(":/resources/menu/a007-16.png"));
	connect(ac,SIGNAL(triggered()),FileManager::instance(),SLOT(onSaveFile()));

	ac = menu->addAction("Close");
	ac->setShortcut(tr("Ctrl+F4"));
	connect(ac,SIGNAL(triggered()),this,SLOT(closeCurr()));

	ac = menu->addAction("Close All But This");
	connect(ac,SIGNAL(triggered()),this,SLOT(closeAllButThis()));

	menu->addSeparator();

	ac = menu->addAction("Copy Full Path");
	connect(ac,SIGNAL(triggered()),this,SLOT(copyFullPath()));

	ac = menu->addAction("Open Containing Folder");
	connect(ac,SIGNAL(triggered()),this,SLOT(openContainingFolder()));
}

void MdiArea::closeCurr()
{
	this->currentSubWindow()->close();
}

void MdiArea::closeAllButThis()
{
	QList<QMdiSubWindow*> list = this->subWindowList();
	QMdiSubWindow* curr = this->currentSubWindow();
	foreach(QMdiSubWindow* tmp,list)
		if(tmp != curr)
			tmp->close();
}

void MdiArea::copyFullPath()
{
	if(!this->currentSubWindow())
		return ;

	BaseCodeEditor* editor=static_cast<BaseCodeEditor*>(this->activeSubWindow()->widget());
	if(!editor)
		return ;

	QString tmp = editor->getFileName();
	tmp.replace("/","\\");
	QApplication::clipboard()->setText(tmp);
}

void MdiArea::openContainingFolder()
{
	if(!this->currentSubWindow())
		return ;
	BaseCodeEditor* editor=static_cast<BaseCodeEditor*>(this->activeSubWindow()->widget());
	if(!editor)
		return ;

	QString fullName=editor->getFileName();

	QProcess *process = new QProcess;
	QStringList strList;
	fullName.replace("/","\\");
	strList<<"/select," << "/select," + fullName;
	process->start("Explorer", strList);
}

QStringList MdiArea::getOpenFiles() const
{
	QStringList strList;
	QList<QMdiSubWindow*> list = this->subWindowList();
	foreach(QMdiSubWindow* sub, list)
	{
		BaseCodeEditor* editor = static_cast<BaseCodeEditor*>(sub->widget());
		if(editor)
			strList<< editor->getFileName();
	}

	return strList;
}


