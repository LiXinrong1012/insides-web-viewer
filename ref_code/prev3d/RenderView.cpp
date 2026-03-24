#include "RenderView.h"
#include "PreHQWidget.h"

#include <QtGui>
#include "base/ViewFactory.h"
#include "base/TreeItemPropertyManager.h"
#include "pubbase/mimedata.h"

#include "hoopsvisibilitysettingdialog.h"
#include "HoopsMaterialDelegate.h"

#define TREEVIEW_ITEM_TYPE_VISIBILITY	130
#define TREEVIEW_ITEM_TYPE_COLOR		131

using namespace INSIDES;
static QString renderViewName("Render View");

class Render3DTreeItemRegister
{
public:
	Render3DTreeItemRegister();
};

Render3DTreeItemRegister::Render3DTreeItemRegister()
{
	TreeItemPropertyGroup* props=new TreeItemPropertyGroup();
	props->setKeyname(renderViewName);
	props->addProperty(TreeItemProperty(renderViewName+"::Color",TREEVIEW_ITEM_TYPE_COLOR,true,10))
		.addProperty(TreeItemProperty(renderViewName+"::HKey",QVariant::LongLong,false,90))
		.addProperty(TreeItemProperty(renderViewName+"::ShowPath",QVariant::Bool,true,20))
		.addProperty(TreeItemProperty(renderViewName+"::ShowCenter",QVariant::Bool,true,20))
		.addProperty(TreeItemProperty(renderViewName+"::Visibility",TREEVIEW_ITEM_TYPE_VISIBILITY,true,20))
		;

	QAbstractItemDelegate* vDelegate=new VisibilityDelegate(NULL);
	TreeItemPropertyManager::instance()->addItemDelegate(TREEVIEW_ITEM_TYPE_VISIBILITY,vDelegate);

	vDelegate=new HoopsMaterialDelegate(NULL);
	TreeItemPropertyManager::instance()->addItemDelegate(TREEVIEW_ITEM_TYPE_COLOR,vDelegate);

	TreeItemPropertyManager::instance()->addGroup(props);
}

static Render3DTreeItemRegister render3DTreeItemRegister;




QVariant Render3DTreeItemProperties::getData( BaseItem* baseItem,int index )
{
	return _HQWidget->getTreeItemData(baseItem,index);
}

bool Render3DTreeItemProperties::setData( BaseItem* baseItem,int index,const QVariant& data )
{
	return _HQWidget->setTreeItemData(baseItem,index,data);
}

QString Render3DTreeItemProperties::getKeyname() const
{
	return renderViewName;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Pre3dRibbonPage RenderView::_ribbonPage;

RenderView::RenderView(void)
{
	QSplitter* main=new QSplitter(Qt::Horizontal,0);
	PreHQWidget* hoopsView=new PreHQWidget(main);

	_widget=main;
	_actualWidget=hoopsView;
	_treeProperties._HQWidget=hoopsView;

	initActionList();
}


RenderView::~RenderView(void)
{
	delete _widget;
}
QString RenderView::getViewType() const
{
	return renderViewName;
}

QWidget* RenderView::getWidget()
{
	return _widget;
}

QWidget* RenderView::getActualWidget()
{
	return _actualWidget;
}

QString RenderView::getClassTypeName()
{
	return renderViewName;
}

QList<QAction*> RenderView::getActionList()
{
	return _actionList;
}

void RenderView::initActionList()
{
	PreHQWidget* hoopsView=(PreHQWidget*)_actualWidget;
	QWidget* main=_widget;

	// action group
	QAction* ac=hoopsView->getActionOpOrbit();
	_actionList.push_back(ac);

	ac=hoopsView->getActionOpPan();
	_actionList.push_back(ac);
	

	ac=new QAction("ViewAll (&A)",main);
	ac->setIcon(QIcon(":/resources/menu/a011x16x16.png"));
	//ac->setShortcut(QKeySequence("a"));
	connect(ac,SIGNAL(triggered()),hoopsView,SLOT(OnZoomToExtents()));
	_actionList.push_back(ac);

	ac=new QAction("repaint",main);
	ac->setIcon(QIcon(":/resources/menu/a012x16x16.png"));
	connect(ac,SIGNAL(triggered()),hoopsView,SLOT(redraw()));
	_actionList.push_back(ac);


	ac=new QAction("tool",main);
	ac->setIcon(QIcon(":/resources/menu/a005x16x16.png"));
	connect(ac,SIGNAL(triggered()),hoopsView,SLOT(onDisplaySelectMenu()));
	_actionList.push_back(ac);

	ac=new QAction("pick",main);
	ac->setIcon(QIcon(":/resources/menu/a020x16x16.png"));
	connect(ac,SIGNAL(triggered()),hoopsView,SLOT(onDisplayPickMenu()));
	_actionList.push_back(ac);

	ac=new QAction("Legend",main);
	ac->setIcon(QIcon(":/resources/menu/a015x16x16.png"));
	connect(ac,SIGNAL(triggered()),hoopsView,SLOT(onDisplayLegendMenu()));
	_actionList.push_back(ac);
}



ITreeItemPropertyFunc* RenderView::getTreeItemProperties()
{
	return &_treeProperties;
}

void RenderView::updateRibbonPage()
{
	_ribbonPage.update();
}

bool RenderView::saveState( QDataStream& out )
{
//	MimeData mimeData;
//	QDataStream& stream=*mimeData.startWriteCustomData("insviewer/prev3d/widget/1.0");
//	
//	stream<<this->getWidget()->x();
//	stream<<this->getWidget()->y();
//	stream<<this->getWidget()->width();
//	stream<<this->getWidget()->height();
//
////	QDataStream& streamTrackPaths = *mimeData.startWriteCustomData("insviewer/prev3d/grackpaths/1.0");
//	
//
//	mimeData.stopWriteAllCustomData();
//	out<<mimeData;
//	
	PreHQWidget* tmp=(PreHQWidget*)_actualWidget;
	return tmp->saveState(out);
}

bool RenderView::loadState( QDataStream& in,qint64 dataSize )
{
	/*MimeData mimeData;
	in>>mimeData;
	if(mimeData.hasFormat("insviewer/prev3d/widget/1.0"))
	{
		QSharedPointer<QDataStream> stream=mimeData.startReadCustomData("insviewer/prev3d/widget/1.0");
		int width = 0, height = 0,x =0, y = 0;
		(*stream)>>x;
		(*stream)>>y;
		(*stream)>>width;
		(*stream)>>height;
		this->getWidget()->setGeometry(x,y,width,height);
	}
*/
	
	PreHQWidget* tmp=(PreHQWidget*)_actualWidget;
	return tmp->loadState(in);
}

