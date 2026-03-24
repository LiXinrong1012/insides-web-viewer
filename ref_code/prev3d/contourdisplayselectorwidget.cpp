#include "contourdisplayselectorwidget.h"

#include "ui_resultselectorwidget.h"

#include "precore/ResultDocument.h"
#include "precore/projectselector.h"
#include "precore/BaseItem.h"
#include "precore/IResultItem.h"


ContourDisplaySelectorWidget::ContourDisplaySelectorWidget(QWidget *parent)
	: TimeCurveResultSelectorWidget(parent)
{

}

ContourDisplaySelectorWidget::~ContourDisplaySelectorWidget()
{

}

void ContourDisplaySelectorWidget::protected_onOK()
{
	IResultItem* resultItem=getCurrentBaseItem();
	int typeId = resultItem->getCategory();
	int secIndex=ui->cbSection->currentIndex();
	int subsecIndex=ui->cbSubSection->currentIndex();
	int subsubsecIndex=ui->cbSubsubSection->currentIndex();
	bool onlyUseCurrent=ui->cbCurrent->isChecked();
	
	int frameCount=myResultDocument()->getResults()->getFrameCount();

	BaseItemSelection list =  myProjectSelector()->getSelection();
	if(list.count() > 1)
	{
		IResults* res=myResultDocument()->getResults();
		foreach(BaseItem* item,list)
		{
			IResults::ResultMap::Iterator f=res->getResults().find(item);
			if(f!=res->getResults().end())
			{
				IResultItem* tmpResultItem = f.value().data();
				if(!tmpResultItem || frameCount <= 0 || secIndex == 0)
					continue;
				if(typeId != tmpResultItem->getCategory())
					continue;

				emit contourItemAdding(tmpResultItem,secIndex,subsecIndex,subsubsecIndex,onlyUseCurrent);
			}
		}
	}
	else
	{
		if(!resultItem || frameCount<=0 || secIndex == 0)
			return;

		emit contourItemAdding(resultItem,secIndex,subsecIndex,subsubsecIndex,onlyUseCurrent);
	}
}
