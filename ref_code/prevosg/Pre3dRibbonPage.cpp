#include "Pre3dRibbonPage.h"

#include "base/activeviewobject.h"
#include "base/view.h"

#include "QtnRibbonBar.h"
#include "QtnRibbonPage.h"
#include "QtnRibbonGroup.h"

//#include "PreHQWidget.h"
#include "RenderView.h"




using namespace Qtitan;
using namespace Base;

Pre3dRibbonPage::Pre3dRibbonPage(void)
	:ribbonPage(0)
{
}


Pre3dRibbonPage::~Pre3dRibbonPage(void)
{
}



Qtitan::RibbonPage* Pre3dRibbonPage::initPage( Qtitan::RibbonBar* ribbonBar )
{
	if (Qtitan::RibbonPage* pageHome = ribbonBar->addPage(QObject::tr("&Render View")))
	{
		pageHome->setContextTitle(QObject::tr("Render View Tools"));
		pageHome->setContextColor(RibbonPage::ContextColorRed);
		ribbonPage=pageHome;
	}
	return ribbonPage;
}


void Pre3dRibbonPage::createGroupView(Qtitan::RibbonGroup& group)
{
	//View* activeView=ActiveViewObject::instance()->activeView();
	//
	//PreHQWidget* hqWidget=(PreHQWidget*)activeView->getActualWidget();

	////Qt::ToolButtonStyle toolButtonType=Qt::ToolButtonTextBesideIcon;
	//Qt::ToolButtonStyle toolButtonType=Qt::ToolButtonTextUnderIcon;
	//
	//

	//QAction* ac;
	//ac=group.addAction(QIcon(":/resources/newmenu/d001b.png"),QObject::tr("XY"),toolButtonType);
	//ac->setToolTip(QObject::tr("Front"));
	//QObject::connect(ac,SIGNAL(triggered()),hqWidget,SLOT(OnFrontView()));

	//ac=group.addAction(QIcon(":/resources/newmenu/d002b.png"),QObject::tr("-XY"),toolButtonType);
	//ac->setToolTip(QObject::tr("Back"));
	//QObject::connect(ac,SIGNAL(triggered()),hqWidget,SLOT(OnBackView()));

	//ac=group.addAction(QIcon(":/resources/newmenu/d003b.png"),QObject::tr("ZY"),toolButtonType);
	//ac->setToolTip(QObject::tr("Right"));
	//QObject::connect(ac,SIGNAL(triggered()),hqWidget,SLOT(OnRightView()));

	//ac=group.addAction(QIcon(":/resources/newmenu/d004b.png"),QObject::tr("-ZY"),toolButtonType);
	//ac->setToolTip(QObject::tr("Left"));
	//QObject::connect(ac,SIGNAL(triggered()),hqWidget,SLOT(OnLeftView()));

	//ac=group.addAction(QIcon(":/resources/newmenu/d005b.png"),QObject::tr("XZ"),toolButtonType);
	//ac->setToolTip(QObject::tr("Top"));
	//QObject::connect(ac,SIGNAL(triggered()),hqWidget,SLOT(OnTopView()));

	//ac=group.addAction(QIcon(":/resources/newmenu/d006b.png"),QObject::tr("-XZ"),toolButtonType);
	//ac->setToolTip(QObject::tr("Bottom"));
	//QObject::connect(ac,SIGNAL(triggered()),hqWidget,SLOT(OnBottomView()));


	//group.addSeparator();

	//ac=group.addAction(QIcon(":/resources/newmenu/d007b.png"),QObject::tr("ISO"),toolButtonType);
	//ac->setToolTip(QObject::tr("ISO"));
	//QObject::connect(ac,SIGNAL(triggered()),hqWidget,SLOT(OnIsometricView()));

	//ac=group.addAction(QIcon(":/prev3d/images/d008a.png"),QObject::tr("+90"),toolButtonType);
	//ac->setToolTip(QObject::tr("Rotate 90 degree"));
	//QObject::connect(ac,SIGNAL(triggered()),hqWidget,SLOT(OnRotate90View()));

	//ac=group.addAction(QIcon(":/prev3d/images/d009a.png"),QObject::tr("-90"),toolButtonType);
	//ac->setToolTip(QObject::tr("Rotate -90 degree"));
	//QObject::connect(ac,SIGNAL(triggered()),hqWidget,SLOT(onRotateMinus90View()));

	//ac=group.addAction(QIcon(":/prev3d/images/d010a.png"),QObject::tr("+30"),toolButtonType);
	//ac->setToolTip(QObject::tr("Rotate +30 degree"));
	//QObject::connect(ac,SIGNAL(triggered()),hqWidget,SLOT(onRotate30View()));

	//ac=group.addAction(QIcon(":/prev3d/images/d011a.png"),QObject::tr("-30"),toolButtonType);
	//ac->setToolTip(QObject::tr("Rotate -30 degree"));
	//QObject::connect(ac,SIGNAL(triggered()),hqWidget,SLOT(onRotateMinus30View()));
}

void Pre3dRibbonPage::update()
{
	if(!ribbonPage || !ActiveViewObject::instance()->activeView())
		return;

	View* activeView=ActiveViewObject::instance()->activeView();
	if(activeView->getViewType()!=RenderView::getClassTypeName())
		return;

	ribbonPage->clearGroups();

	createGroupView(*ribbonPage->addGroup(QObject::tr("View")));
	createGroupVisibility(*ribbonPage->addGroup(QObject::tr("Visibility")));
	createGroupMaterial(*ribbonPage->addGroup(QObject::tr("Material")));

}

void Pre3dRibbonPage::createGroupVisibility( Qtitan::RibbonGroup& page )
{
	/*_visibilityWidget=new RibbonHoopsVisibilityWidget(&page);
	page.addWidget(_visibilityWidget);*/
}

void Pre3dRibbonPage::createGroupMaterial( Qtitan::RibbonGroup& page )
{
	/*_materialWidget=new RibbonHoopsMaterialWidget(&page,&page);*/
	//page.addWidget(_materialWidget);
}
