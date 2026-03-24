#include "ParametersBaseItem.h"
#include "pretdy/TDYParameters.h"
#include "precore/precore_data.h"


namespace INSIDES
{


ParametersBaseItem::ParametersBaseItem(void)
	:_parameters(NULL)
{
	_classType=TDY_PRE_ITEMCLASS_PARAMETERS;
	setCategory(TDY_PRE_CATE_PARAMETERS);
	setKeyname("Parameters");
	setCollapsed(true);
}


ParametersBaseItem::~ParametersBaseItem(void)
{
}

void ParametersBaseItem::copyTo( BaseItem* item ) const
{
	if(item==this)
		return;

	if(item->getCategory()!=TDY_PRE_CATE_PARAMETERS)
		return;

	BaseItem::copyTo(item);
	TDYParameters* newParas=NULL;
	if(_parameters){
		newParas=_parameters->clone();
	}

	((ParametersBaseItem*)item)->setTDYParameters(newParas);
}

const TDYParameters* ParametersBaseItem::getParameters() const
{
	return _parameters;
}

TDYParameters* ParametersBaseItem::getParameters()
{
	return _parameters;
}

void ParametersBaseItem::setTDYParameters( TDYParameters* para )
{
	if(para==_parameters)
		return;

	if(_parameters)
		delete _parameters;
	_parameters=para;

	//refreshChildren();
}

void ParametersBaseItem::refreshChildren()
{
	clearChildren();

	if(!_parameters)
		return;
	int n=_parameters->count();
	for(int i=0;i<n;++i)
	{
		const TDYParameterItem* item=_parameters->getAt(i);
		BaseItem* newItem=new BaseItem(item->keyname);
		newItem->setCategory(TDY_PRE_CATE_PARAMETERITEM);
		this->appendChild(newItem);
		newItem->setID(nextCurrentMaxID());
		(*newItem)[item->keyname]=item->strPara;
		double va=_parameters->getValue(item->strPara);
		(*newItem)["value"]=QString("%1").arg(va);
	}
}

void ParametersBaseItem::refreshContents()
{
	if(!_parameters)
		return;
	int n=_parameters->count();
	if(n!=count())
		return;

	for(int i=0;i<n;++i)
	{
		const TDYParameterItem* item=_parameters->getAt(i);
		BaseItem* newItem=child(i);
		(*newItem)[item->keyname]=item->strPara;
	}
}



} // end namespace INSIDES