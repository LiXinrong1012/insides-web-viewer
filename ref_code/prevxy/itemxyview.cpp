#include "itemxyview.h"
#include "itemxywidget.h"
#include "customxyplot.h"
#include "xypointstracer.h"

#include <QAction>

static QString itemCurveViewName("Time Curve View");

ItemXYView::ItemXYView()
	: Base::View()
{
	_widget=new ItemXYWidget();	

	initActionList();
}
QString ItemXYView::getViewType() const
{
	return itemCurveViewName;
}
ItemXYView::~ItemXYView()
{
	delete _widget;
}

QString ItemXYView::getClassTypeName()
{
	return itemCurveViewName;
}

QWidget* ItemXYView::getWidget()
{
	return _widget;
}

QList<QAction*> ItemXYView::getActionList()
{
	return _actionList;
}

void ItemXYView::initActionList()
{
	ItemXYWidget* realView=(ItemXYWidget*)_widget;
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
//	ac->setToggleAction(true);
	
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

	ac = realView->getPlot()->getPointsTracer()->getPointsAction();
	ac->setParent(main);
	_actionList.push_back(ac);

	ac=new QAction(tr("Appearance"),main);
	ac->setIcon(QIcon(":/resources/menu/a015x16x16.png"));
	connect(ac,SIGNAL(triggered()),realView->getPlot(),SLOT(showConfigMenu()));
	_actionList.push_back(ac);
}

bool ItemXYView::saveState( QDataStream& out )
{
	return ((ItemXYWidget*)_widget)->saveMyState(out);
}

bool ItemXYView::loadState( QDataStream& in, qint64 dataSize )
{
	return ((ItemXYWidget*)_widget)->loadMyState(in, dataSize);
}