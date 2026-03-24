#include "itemcurveview.h"
#include "itemcurvewidget.h"
#include "base/ViewFactory.h"

#include <QAction>
#include "customcurveplot.h"

#include "curvepointstracer.h"


static QString itemCurveViewName("Time Curve View");

ItemCurveView::ItemCurveView()
	: Base::View()
{
	_widget=new ItemCurveWidget();	

	initActionList();
}
QString ItemCurveView::getViewType() const
{
	return itemCurveViewName;
}
ItemCurveView::~ItemCurveView()
{
	delete _widget;
}

QString ItemCurveView::getClassTypeName()
{
	return itemCurveViewName;
}

QWidget* ItemCurveView::getWidget()
{
	return _widget;
}

QList<QAction*> ItemCurveView::getActionList()
{
	return _actionList;
}

void ItemCurveView::initActionList()
{
	ItemCurveWidget* realView=(ItemCurveWidget*)_widget;
	realView->setParentView(this);
	QWidget* main=_widget;

	// action group
	QAction* ac=new QAction("View All",main);
	ac->setIcon(QIcon(":/resources/menu/a011x16x16.png"));
	connect(ac,SIGNAL(triggered()),realView->getPlot(),SLOT(viewAll()));
	_actionList.push_back(ac);

	ac=new QAction("Export",main);
	ac->setIcon(QIcon(":/resources/menu/a029x16x16.png"));
	connect(ac,SIGNAL(triggered()),realView->getPlot(),SLOT(showExchangeDataMenu()));
	_actionList.push_back(ac);
	
	QIcon iconShowHide;
	iconShowHide.addPixmap(QPixmap(":/resources/menu/a030x16x16.png"),QIcon::Normal,QIcon::Off);
	iconShowHide.addPixmap(QPixmap(":/resources/menu/a031x16x16.png"),QIcon::Normal,QIcon::On);
	ac=new QAction("Show/Hide Title",main);
	ac->setToggleAction(true);
	ac->setIcon(iconShowHide);
	connect(ac,SIGNAL(triggered()),realView,SLOT(hideShowTitle()));
	_actionList.push_back(ac);

	ac=new QAction("Settings",main);
	ac->setIcon(QIcon(":/resources/menu/a032x16x16.png"));
	connect(ac,SIGNAL(triggered()),realView,SLOT(showViewSettings()));
	_actionList.push_back(ac);

	ac=new QAction("Curves",main);
	ac->setIcon(QIcon(":/resources/menu/a033x16x16.png"));
	connect(ac,SIGNAL(triggered()),realView,SLOT(showCurveSetting()));
	_actionList.push_back(ac);

	ac=realView->getPlot()->getPointsTracer()->getPointAction();
	ac->setParent(main);
	_actionList.push_back(ac);

	ac=realView->getPlot()->getPointsTracer()->getPointsAction();
	ac->setParent(main);
	_actionList.push_back(ac);

	ac=new QAction("Add custom curve",main);
	ac->setIcon(QIcon(":/resources/menu/a037x16x16.png"));
	connect(ac,SIGNAL(triggered()),realView,SLOT(showAddCustomCurveDialog()));
	_actionList.push_back(ac);

	ac=new QAction(tr("Appearance"),main);
	ac->setIcon(QIcon(":/resources/menu/a015x16x16.png"));
	connect(ac,SIGNAL(triggered()),realView->getPlot(),SLOT(showConfigMenu()));
	_actionList.push_back(ac);
}

bool ItemCurveView::saveState( QDataStream& out )
{
	return ((ItemCurveWidget*)_widget)->saveMyState(out);
}

bool ItemCurveView::loadState( QDataStream& in, qint64 dataSize )
{
	return ((ItemCurveWidget*)_widget)->loadMyState(in, dataSize);
}


