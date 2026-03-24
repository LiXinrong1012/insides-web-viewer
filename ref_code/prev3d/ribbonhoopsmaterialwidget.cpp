#include "ribbonhoopsmaterialwidget.h"

#include "QTitanRibbon/include/QtnRibbonBar.h"
#include "QTitanRibbon/include/QtnRibbonPage.h"
#include "QTitanRibbon/include/QtnRibbonGroup.h"
#include "QTitanRibbon/include/QtnOfficePopupColorButton.h"

#include "precore/projectselector.h"
#include "precore/appearance.h"
#include "precore/BaseItem.h"

#include "ribbonhoopsvisibilitywidget.h"
#include "base/view.h"
#include "ViewManager.h"
#include "PreHQWidget.h"

#include <QtGui>

using namespace Base;


RibbonHoopsMaterialWidget::RibbonHoopsMaterialWidget( QObject *parent, Qtitan::RibbonGroup* group )
	: QObject(parent)
{
	cbFace=new QAction("Face",group);
	cbFace->setCheckable(true);
	cbFace->setChecked(true);
	cbFace->setIcon(QIcon(":/resources/newmenu/d024a.png"));
	group->addAction(cbFace);

	cbLine=new QAction("Line",group);
	cbLine->setCheckable(true);
	cbLine->setChecked(true);
	cbLine->setIcon(QIcon(":/resources/newmenu/d025a.png"));
	group->addAction(cbLine);

	cbVertex=new QAction("Vertex",group);
	cbVertex->setCheckable(true);
	cbVertex->setChecked(true);
	cbVertex->setIcon(QIcon(":/resources/newmenu/d028a.png"));
	group->addAction(cbVertex);

	cbText=new QAction("Text",group);
	cbText->setCheckable(true);
	cbText->setChecked(true);
	cbText->setIcon(QIcon(":/resources/newmenu/d027a.png"));
	group->addAction(cbText);

	QMenu* splitPopup=new QMenu(group);
	connect(splitPopup->addAction(tr("Unset all")),SIGNAL(triggered()),this,SLOT(onUnsetAll()));
	
	QAction* ac=group->addAction(QIcon(":/resources/newmenu/h002a.png"),tr("Unset"),Qt::ToolButtonIconOnly,splitPopup);
	connect(ac,SIGNAL(triggered()),this,SLOT(onUnset()));

	btnColor=new Qtitan::PopupColorButton(group);
	QAction* actionColor=group->addWidget(QIcon(":/prev3d/images/d001a.png"),tr("Color"),
		btnColor);
	connect(btnColor,SIGNAL(colorChanged(const QColor&)),this,SLOT(onColor(const QColor&)));
	connect(actionColor,SIGNAL(triggered()),this,SLOT(setColor()));

	group->addSeparator();

	group->addWidget(new QLabel(tr("Transparency"),group));
	QSpinBox* spinBox=new QSpinBox(group);
	spinBox->setValue(0);
	spinBox->setSuffix(tr("%"));
	spinBox->setRange(0,100);
	spinBox->setMinimumWidth(50);
	spinBox->setMaximumWidth(50);
	group->addWidget(QIcon(":/prev3d/images/d001a.png"),tr("Value"),true,spinBox);

	sliderTransparency=new QSlider(Qt::Horizontal,group);
	sliderTransparency->setRange(0,100);
	sliderTransparency->setMaximumWidth(90);
	sliderTransparency->setMinimumWidth(90);
	group->addWidget(sliderTransparency);
	connect(sliderTransparency,SIGNAL(valueChanged(int)),this,SLOT(onTransparencyChanged()));
	connect(sliderTransparency,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
	connect(spinBox,SIGNAL(valueChanged(int)),sliderTransparency,SLOT(setValue(int)));
}

RibbonHoopsMaterialWidget::~RibbonHoopsMaterialWidget()
{
}

void RibbonHoopsMaterialWidget::onUnset()
{
	PreHQWidget* renderView=RibbonHoopsVisibilityWidget::getRenderView();
	ViewManager* viewManager=RibbonHoopsVisibilityWidget::getViewManager();
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
			if(cbVertex->isChecked())
				appItem->setUseColor(AppearanceItem::Color_Point,false);
			if(cbLine->isChecked()){
				appItem->setUseColor(AppearanceItem::Color_Edge,false);
				appItem->setUseColor(AppearanceItem::Color_Line,false);
			}
			if(cbFace->isChecked())
				appItem->setUseColor(AppearanceItem::Color_Face,false);

			viewManager->onVisibilityChanged(appItem);
			viewManager->onApplyMaterial(appItem);
		}
	}

	renderView->GetHoopsView()->Update();
}

void RibbonHoopsMaterialWidget::onUnsetAll()
{
	PreHQWidget* renderView=RibbonHoopsVisibilityWidget::getRenderView();
	ViewManager* viewManager=RibbonHoopsVisibilityWidget::getViewManager();
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
			appItem->setUseColorAll(false);
			viewManager->onVisibilityChanged(appItem);
			viewManager->onApplyMaterial(appItem);
		}
	}

	renderView->GetHoopsView()->Update();
}

void RibbonHoopsMaterialWidget::onTransparencyChanged()
{
	PreHQWidget* renderView=RibbonHoopsVisibilityWidget::getRenderView();
	ViewManager* viewManager=RibbonHoopsVisibilityWidget::getViewManager();
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
			appItem->setTransparency(sliderTransparency->value()/100.0);
			viewManager->onVisibilityChanged(appItem);
			viewManager->onApplyMaterial(appItem);
		}
	}

	renderView->GetHoopsView()->Update();
}

static void _setOneColor(QAction* checkBox,
	AppearanceItem* appItem,AppearanceItem::ColorItem t,const QColor& color)
{
	if(checkBox->isChecked()){
		appItem->setUseColor(t,true);
		appItem->setColor(t,color);
	}
}

void RibbonHoopsMaterialWidget::onColor( const QColor& color )
{
	if(!color.isValid())
		return;

	PreHQWidget* renderView=RibbonHoopsVisibilityWidget::getRenderView();
	ViewManager* viewManager=RibbonHoopsVisibilityWidget::getViewManager();
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
			_setOneColor(cbFace,appItem,AppearanceItem::Color_Face,color);
			_setOneColor(cbLine,appItem,AppearanceItem::Color_Edge,color);
			_setOneColor(cbLine,appItem,AppearanceItem::Color_Line,color);
			_setOneColor(cbVertex,appItem,AppearanceItem::Color_Point,color);
			
			viewManager->onVisibilityChanged(appItem);
			viewManager->onApplyMaterial(appItem);
		}
	}

	renderView->GetHoopsView()->Update();

	btnColor->setColor(color);
}

void RibbonHoopsMaterialWidget::setColor()
{
	onColor(btnColor->color());
}

