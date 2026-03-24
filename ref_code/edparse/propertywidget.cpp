#include "propertywidget.h"
#include "entitypropertywidget.h"
#include "projectpropertywidget.h"

#include "edcore/entity.h"
#include "edcore/project.h"
#include "edcore/solution.h"

#include "solutionbrowsertreewidget.h"

using namespace INSEditor;


PropertyWidget::PropertyWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	_propertyLayout = new QHBoxLayout;
	_propertyLayout->setContentsMargins(3,3,3,3);
	_propertyLayout->setSpacing(0);
	setLayout(_propertyLayout);

	_entityPropertyWidget=new EntityPropertyWidget(this);
	_projectPropertyWidget=new ProjectPropertyWidget(this);

	_propertyLayout->addWidget(_entityPropertyWidget);
	_propertyLayout->addWidget(_projectPropertyWidget);

	_projectPropertyWidget->hide();
	_entityPropertyWidget->hide();
}

PropertyWidget::~PropertyWidget()
{
}

void PropertyWidget::onItemChanged( void* item, int itemType )
{
	if(!item) { //无有效条目，清除界面
		clearAllView();
		return;
	}

	clearAllView();
	int typeId = itemType;
	switch(typeId)
	{
	case Type_File:
		{
			Entity* entity = (Entity*)item;
			_entityPropertyWidget->setEntity(entity);
			_entityPropertyWidget->show();
			break;
		}
	case Type_Project:
		{
			Project* project = (Project*)item;
			_projectPropertyWidget->setProject(project);
			_projectPropertyWidget->show();
			break;
		}
	default:
		;
	}
}

void PropertyWidget::setEmptyView()
{
	clearAllView();
}

void PropertyWidget::clearAllView()
{
	_entityPropertyWidget->setEntity(NULL);
	_projectPropertyWidget->setProject(NULL);
	_entityPropertyWidget->hide();
	_projectPropertyWidget->hide();
}
