#include "VInteractiveTableView.h"
#include "vinteractivetablewidget.h"

#include "Base/ViewFactory.h"
#include <QSplitter>

#include "prevttbase/resultselectorwidget.h"

static QString interactiveTableViewName("Multiple Interactive Table");

VInteractiveTableView::VInteractiveTableView(QObject* parent)
	:View(parent)
{
	QSplitter* main=new QSplitter(Qt::Horizontal,0);
	VInteractiveTableWidget* actualWidget=new VInteractiveTableWidget(main);
	actualWidget->getSelector()->setParentView(this);

	_widget=main;
	_actualWidget=actualWidget;

	initActionList();
}

QString VInteractiveTableView::getViewType() const
{
	return interactiveTableViewName;
}
QString VInteractiveTableView::getClassTypeName()
{
	return interactiveTableViewName;
}

VInteractiveTableView::~VInteractiveTableView(void)
{
	delete _widget;
}

QWidget* VInteractiveTableView::getWidget()
{
	return _widget;
}

QList<QAction*> VInteractiveTableView::getActionList()
{
	return _actionList;
}

QWidget* VInteractiveTableView::getActualWidget()
{
	return _widget;
}

void VInteractiveTableView::initActionList()
{
	VInteractiveTableWidget* actualView=(VInteractiveTableWidget*)_actualWidget;
	QWidget* main=_widget;

	// action group
	QAction* ac=new QAction("Export",main);
	ac->setIcon(QIcon(":/resources/menu/a029x16x16.png"));
	connect(ac,SIGNAL(triggered()),actualView,SLOT(exportAsTxt()));
	_actionList.push_back(ac);

	ac=new QAction("Export All",main);
	ac->setIcon(QIcon(":/resources/menu/a029x16x16.png"));
	connect(ac,SIGNAL(triggered()),actualView,SLOT(exportAllAsTxt()));
	_actionList.push_back(ac);

	ac=new QAction("Add",main);
	ac->setIcon(QIcon(":/resources/menu/a034x16x16.png"));
	connect(ac,SIGNAL(triggered()),actualView,SLOT(addItems()));
	_actionList.push_back(ac);

	ac=new QAction("Setting",main);
	ac->setIcon(QIcon(":/resources/menu/a034x16x16.png"));
	connect(ac,SIGNAL(triggered()),actualView,SLOT(showSetting()));
	_actionList.push_back(ac);
}

bool VInteractiveTableView::saveState( QDataStream& out )
{
	VInteractiveTableWidget* actualView=(VInteractiveTableWidget*)_actualWidget;
	return actualView->saveMyState(out);
}

bool VInteractiveTableView::loadState( QDataStream& in, qint64 dataSize)
{
	VInteractiveTableWidget* actualView=(VInteractiveTableWidget*)_actualWidget;
	return actualView->loadMyState(in);
}