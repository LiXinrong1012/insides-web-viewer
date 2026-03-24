#include "interactivetableview.h"

#include "interactivetablewidget.h"

#include "Base/ViewFactory.h"

#include "prevttbase/resultselectorwidget.h"

#include <QSplitter>


static QString interactiveTableViewName("Interactive Table");

InteractiveTableView::InteractiveTableView(QObject* parent)
	:View(parent)
{
	QSplitter* main=new QSplitter(Qt::Horizontal,0);
	InteractiveTableWidget* actualWidget=new InteractiveTableWidget(main);
	_tableWidget = actualWidget;
	actualWidget->getSelector()->setParentView(this);
	_widget=main;
	_actualWidget=actualWidget;

	initActionList();
}

QString InteractiveTableView::getViewType() const
{
	return interactiveTableViewName;
}
QString InteractiveTableView::getClassTypeName()
{
	return interactiveTableViewName;
}

InteractiveTableView::~InteractiveTableView(void)
{
	delete _widget;
}

QWidget* InteractiveTableView::getWidget()
{
	return _widget;
}

QList<QAction*> InteractiveTableView::getActionList()
{
	return _actionList;
}

QWidget* InteractiveTableView::getActualWidget()
{
	return _widget;
}

void InteractiveTableView::initActionList()
{
	InteractiveTableWidget* actualView=(InteractiveTableWidget*)_actualWidget;
	QWidget* main=_widget;

	// action group
	QAction* ac=new QAction("Export",main);
	ac->setIcon(QIcon(":/resources/menu/a029x16x16.png"));
	connect(ac,SIGNAL(triggered()),actualView,SLOT(exportAsTxt()));
	_actionList.push_back(ac);

	QIcon iconShowHide;
	iconShowHide.addPixmap(QPixmap(":/resources/menu/a030x16x16.png"),QIcon::Normal,QIcon::Off);
	iconShowHide.addPixmap(QPixmap(":/resources/menu/a031x16x16.png"),QIcon::Normal,QIcon::On);
	ac = new QAction("Show / Hide selector",main);
	ac->setToggleAction(true);
	ac->setIcon(iconShowHide);
	connect(ac,SIGNAL(triggered()),this,SLOT(hideShowSelector()));
	_actionList.push_back(ac);

	ac = _tableWidget->getTransposeAction();
	_actionList.push_back(ac);

	ac = new QAction("Setting",main);
	ac->setIcon(QIcon(":/resources/menu/a029x16x16.png"));
	connect(ac,SIGNAL(triggered()),actualView,SLOT(showSetting()));
	_actionList.push_back(ac);
}

bool InteractiveTableView::saveState( QDataStream& out )
{
	InteractiveTableWidget* actualView=(InteractiveTableWidget*)_actualWidget;
	return actualView->saveMyState(out);
}

bool InteractiveTableView::loadState( QDataStream& in, qint64 dataSize )
{
	InteractiveTableWidget* actualView=(InteractiveTableWidget*)_actualWidget;
	return actualView->loadMyState(in, dataSize);
}

void InteractiveTableView::hideShowSelector()
{
	if (_tableWidget->getSelector()->isHidden())
		_tableWidget->getSelector()->show();
	else
		_tableWidget->getSelector()->hide();
}



