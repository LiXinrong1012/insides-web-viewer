#include "ribbonhoopsvisibilitywidget.h"
#include "ui_ribbonhoopsvisibilitywidget.h"

#include "base/activeviewobject.h"
#include "precore/projectselector.h"
#include "precore/appearance.h"
#include "RenderView.h"
#include "base/view.h"
#include "ViewManager.h"
#include "PreHQWidget.h"

using namespace Base;


RibbonHoopsVisibilityWidget::RibbonHoopsVisibilityWidget(QWidget *parent)
	: QWidget(parent)
	,_disabled(false)
{
	ui = new Ui::RibbonHoopsVisibilityWidget();
	ui->setupUi(this);

	connect(ui->cbFace,SIGNAL(stateChanged(int)),
		this,SLOT(controlChanged()));
	connect(ui->cbLine,SIGNAL(stateChanged(int)),
		this,SLOT(controlChanged()));
	connect(ui->cbEdge,SIGNAL(stateChanged(int)),
		this,SLOT(controlChanged()));
	connect(ui->cbVertex,SIGNAL(stateChanged(int)),
		this,SLOT(controlChanged()));
	connect(ui->cbText,SIGNAL(stateChanged(int)),
		this,SLOT(controlChanged()));

	connect(ui->cbAll,SIGNAL(stateChanged(int)),
		this,SLOT(uiAllChanged()));
	
}

RibbonHoopsVisibilityWidget::~RibbonHoopsVisibilityWidget()
{
	delete ui;
}

static void _control2Value(AppearanceItem* appItem,AppearanceItem::VisibilityItem vItem,
	QCheckBox* uiItem)
{
	if(uiItem->state()==Qt::Checked)
		appItem->setVisibilityType(vItem,AppearanceItem::Visual);
	else if(uiItem->state()==Qt::Unchecked)
		appItem->setVisibilityType(vItem,AppearanceItem::Invisual);
	else
		appItem->setVisibilityType(vItem,AppearanceItem::Undefined);
}

void RibbonHoopsVisibilityWidget::controlChanged()
{
	if(!_disabled)
		updateValue();
}

ViewManager* RibbonHoopsVisibilityWidget::getViewManager()
{
	View* activeView=ActiveViewObject::instance()->activeView();
	if(!activeView || activeView->getViewType()!=RenderView::getClassTypeName())
		return NULL;

	PreHQWidget* w=(PreHQWidget*)activeView->getActualWidget();
	return w->getViewManager().data();
}

PreHQWidget* RibbonHoopsVisibilityWidget::getRenderView()
{
	View* activeView=ActiveViewObject::instance()->activeView();
	if(!activeView || activeView->getViewType()!=RenderView::getClassTypeName())
		return NULL;

	PreHQWidget* w=(PreHQWidget*)activeView->getActualWidget();
	return w;
}

void RibbonHoopsVisibilityWidget::uiAllChanged()
{
	_disabled=true;
	Qt::CheckState a=ui->cbAll->checkState();
	ui->cbFace->setCheckState(a);
	ui->cbLine->setCheckState(a);
	ui->cbEdge->setCheckState(a);
	ui->cbVertex->setCheckState(a);
	ui->cbText->setCheckState(a);

	_disabled=false;
	updateValue();
}

void RibbonHoopsVisibilityWidget::updateValue()
{
	PreHQWidget* renderView=getRenderView();
	ViewManager* viewManager=getViewManager();
	if(!viewManager)
		return;

	const BaseItemSelection& selection=myProjectSelector()->getSelection();
	if(selection.size()==0)
		return;


	for(int i=0;i<selection.size();++i)
	{
		BaseItem* item=selection[i];
		AppearanceItem* appItem=viewManager->getAppearance(item);
		if(appItem){
			_control2Value(appItem,AppearanceItem::Face,ui->cbFace);
			_control2Value(appItem,AppearanceItem::Line,ui->cbLine);
			_control2Value(appItem,AppearanceItem::Edge,ui->cbEdge);
			_control2Value(appItem,AppearanceItem::Vertex,ui->cbVertex);
			_control2Value(appItem,AppearanceItem::Text,ui->cbText);

			viewManager->onVisibilityChanged(appItem);
			viewManager->onApplyMaterial(appItem);
		}
	}

	renderView->GetHoopsView()->Update();
}

