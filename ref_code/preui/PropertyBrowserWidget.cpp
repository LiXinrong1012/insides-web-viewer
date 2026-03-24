#include "PropertyBrowserWidget.h"
#include "prosb/qtvariantproperty.h"
#include "prosb/qttreepropertybrowser.h"
#include "prosb/qtgroupboxpropertybrowser.h"
#include "base/ItemProperties.h"
#include <QVBoxLayout>
#include <QtGui>


#include "Base/ExtendMap.h"
#include "precore/TypeDataManager.h"
#include "precore/BaseItem.h"

#include "precore/projectselector.h"

using namespace Base;
using namespace INSIDES;

class PropertyBrowserWidgetPrivate
{
public:
	PropertyBrowserWidgetPrivate(PropertyBrowserWidget* p);

	bool value2Control();

	QtTreePropertyBrowser	*d_treeBrowser;
	PropertyItemClass		*d_pd;
	PropertyBrowserWidget	*d_par;
	QtVariantPropertyManager *variantManager;
	QtVariantEditorFactory	*variantFactory ;

	typedef ExtendMap<QString,QtVariantProperty*> KeyMap;
	KeyMap keyMap;
	

};


PropertyBrowserWidgetPrivate::PropertyBrowserWidgetPrivate(PropertyBrowserWidget* p)
		:d_treeBrowser(new QtTreePropertyBrowser(p)),
		d_pd(NULL),
		d_par(p),
		variantManager(new QtVariantPropertyManager),
		variantFactory(new QtVariantEditorFactory)
{
	QtTreePropertyBrowser* browser=d_treeBrowser;
	browser->setResizeMode(QtTreePropertyBrowser::Interactive);
	browser->setFactoryForManager(variantManager, variantFactory);


	//QtVariantProperty *priority = variantManager->addProperty(QVariant::Int, "Priority");

	//QtVariantProperty* pp1=variantManager->addProperty(QVariant::Bool,"Bool");

	//priority->setToolTip("Task Priority");

	//priority->setAttribute("minimum", 1);
	//priority->setAttribute("maximum", 5);
	//priority->setValue(3);

	//QtVariantProperty *reportType = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(), "Report Type");
	//QStringList types;
	//types << "Bug" << "Suggestion" << "To Do";
	//reportType->setAttribute("enumNames", types);
	//reportType->setValue(1); // current value will be "Suggestion"

	//QtVariantProperty *task1 = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), "Task 1");

	//task1->addSubProperty(priority);
	//task1->addSubProperty(reportType);

	//browser->addProperty(task1);
	//browser->addProperty(pp1);
}
bool PropertyBrowserWidgetPrivate::value2Control()
{
	PropertyItemClass* pPropertyItem=d_pd;
	d_treeBrowser->clear();
	keyMap.clear();

	if(!pPropertyItem)
		return false;

	// init basic properties
	QtVariantProperty* baseGroup=variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
		QObject::tr("Base"));
	d_treeBrowser->addProperty(baseGroup);

	QtVariantProperty* variantKeyname = variantManager->addProperty(QVariant::String, QObject::tr("Keyname"));
	variantKeyname->setValue(pPropertyItem->getFullName());
	QtVariantProperty* variantID = variantManager->addProperty(QVariant::Int, QObject::tr("ID"));
	variantID->setValue(pPropertyItem->getID());
	QtVariantProperty* variantActive = variantManager->addProperty(QVariant::Bool, QObject::tr("Active"));
	variantActive->setValue(pPropertyItem->getActive());
	QtVariantProperty* variantIncluded = variantManager->addProperty(QVariant::Bool, QObject::tr("Included"));
	variantIncluded->setValue(pPropertyItem->getIncluded());

	baseGroup->addSubProperty(variantKeyname);
	baseGroup->addSubProperty(variantID);
	baseGroup->addSubProperty(variantActive);
	baseGroup->addSubProperty(variantIncluded);


	TypeDataManager* typeDataManager=TypeDataManager::instance();
	TypeData* typeData=typeDataManager->getTypeData(pPropertyItem->getCategory());

	if(typeData){
		int groupCount=typeData->groups.size();
		for(int i=0;i<groupCount;++i)
		{
			// update one group
			TypeDataGroup& groupData=typeData->groups[i];
			QtVariantProperty* task=variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),groupData.groupName);
			d_treeBrowser->addProperty(task);
			for(int j=0;j<groupData.items.size();++j)
			{
				// update one single item
				TypeDataSingleItem& singleItem=groupData.items[j];
				if(pPropertyItem->get(singleItem.keyname).isEmpty())
					continue;
				QtVariantProperty* variantProperty = variantManager->addProperty(QVariant::String, singleItem.displayText);
				variantProperty->setStatusTip(singleItem.description);
				variantProperty->setValue(pPropertyItem->get(singleItem.keyname));
				task->addSubProperty(variantProperty);
			}
		}
	}

	// add all properties into the widget

	if(pPropertyItem->getProperties()){
		QtVariantProperty* task=variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),"All Properties");
		d_treeBrowser->addProperty(task);
		const ItemProperties::container_type& allProps=pPropertyItem->getProperties()->getMap();
		for(ItemProperties::container_type::const_iterator b=allProps.constBegin();
			b!=allProps.end();++b)
		{
			// update one single item
			QtVariantProperty* variantProperty = variantManager->addProperty(QVariant::String, b.key());
			variantProperty->setStatusTip(b.value());
			variantProperty->setValue(b.value());
			task->addSubProperty(variantProperty);
		}
	}



//	QtVariantProperty* task1=variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),"Task");
//	d_treeBrowser->addProperty(task1);
//	QtVariantProperty* variantProperty = variantManager->addProperty(QVariant::String, "aaaa");
//	task1->addSubProperty(variantProperty);
	return true;
}






//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
PropertyBrowserWidget::PropertyBrowserWidget(QWidget* parent/* =0 */):QWidget(parent),d_ptr(new PropertyBrowserWidgetPrivate(this))
{
	setupUi();
	d_ptr->value2Control();
	myProjectSelector()->attachSupplier(this);
}

PropertyBrowserWidget::~PropertyBrowserWidget(void)
{
}

void PropertyBrowserWidget::setupUi()
{

	QtTreePropertyBrowser *browser = d_ptr->d_treeBrowser;

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(browser);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	
	/*
	QHBoxLayout *hBoxLayout=new QHBoxLayout;
	QPushButton* applyButton = new QPushButton( tr("Apply"), this);
	QPushButton* cancelButton=new QPushButton(tr("Cancel"),this);
	hBoxLayout->addWidget(applyButton);
	hBoxLayout->addWidget(cancelButton);
	*/

	//layout->addLayout(hBoxLayout);
	setLayout(layout);

	//QObject::connect(applyButton, SIGNAL(clicked()),
	//	this,  SLOT(applyClicked()));

	//QObject::connect(cancelButton, SIGNAL(clicked()),
	//	this,  SLOT(cancelClicked()));

}

void PropertyBrowserWidget::applyClicked()
{
}
void PropertyBrowserWidget::cancelClicked()
{
	updateTree();
}

void PropertyBrowserWidget::setItem(PropertyItemClass *p)
{
	d_ptr->d_pd=p;
	updateTree();
}

PropertyItemClass* PropertyBrowserWidget::getItem()
{
	return d_ptr->d_pd;
}

void PropertyBrowserWidget::updateTree()
{
	d_ptr->value2Control();
}

void PropertyBrowserWidget::updateTree(PropertyItemClass *p)
{
	setItem(p);
	updateTree();
}

void PropertyBrowserWidget::update( const std::vector<PropertyItemClass*>& items )
{
	if(items.size()==0)
		updateTree(NULL);
	else
		updateTree(*items.rbegin());
}

void PropertyBrowserWidget::ss_onSetClicked_projected( BaseItem* item )
{
	setItem(item);
}

void PropertyBrowserWidget::ss_onSetSelection_protected( const BaseItemSelection& selection)
{
	if(selection.size()>0)
		setItem(selection[0]);

}