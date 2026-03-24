#include "Assembly.h"
#include "precore_data.h"
#include "ParametersBaseItem.h"
#include "pretdy/TDYParameters.h"
#include "UAPI_.h"


namespace INSIDES
{



Assembly::Assembly(const QString& keyName)
	:BaseItem(keyName)
{
	_category=TDY_PRE_CATE_ASSEMBLY;
	_classType=TDY_PRE_ITEMCLASS_ASSEMBLY;
}


Assembly::~Assembly(void)
{
}


BaseItem* Assembly::getParts()
{
	return getOrCreateFolder("Parts");
}

BaseItem* Assembly::getParameters()
{
	if(count()>0 && child(0)->getCategory()==TDY_PRE_CATE_PARAMETERS)
		return child(0);
	return NULL;
}

BaseItem* Assembly::getGround()
{
	return getInstances()->child(0);
}
BaseItem* Assembly::getConstraints()
{
	return getOrCreateFolder("Constraints");
}

BaseItem* Assembly::getLoads()
{
	return getOrCreateFolder("Loads");
}

BaseItem* Assembly::getContacts()
{
	return getOrCreateFolder("Contacts");
}


BaseItem* Assembly::getInstances()
{
	return getOrCreateFolder("Instances");
}

BaseItem* Assembly::getRequests()
{
	return getOrCreateFolder("Requests");
}

BaseItem* Assembly::getSets()
{
	return getOrCreateFolder("Sets");
}

void Assembly::createDefault()
{
	clearChildren();
	initFolders();
}

BaseItem* Assembly::getAssemblies()
{
	return getOrCreateFolder("Assemblies");
}

BaseItem* Assembly::getMarkers()
{
return getOrCreateFolder("Markers");
}

BaseItem* Assembly::getOrCreateParameters()
{
	if(count()>0 && child(0)->getCategory()==TDY_PRE_CATE_PARAMETERS)
		return child(0);
	// insert a parameter first
	BaseItem* item=new ParametersBaseItem();
	item->setID(BaseItem::nextCurrentMaxID());
	PREI_Add_Item(this,item,0);
	return item;
}






void Assembly::initFolders()
{

	//getOrCreateFolder("Parameters");
	getOrCreateFolder("Parts");
	getOrCreateFolder("Assemblies");
	Folder* folder=getOrCreateFolder("Instances");
	BaseItem* ground=new BaseItem("ground");
	ground->setID(BaseItem::nextCurrentMaxID());
	ground->setCategory(TDY_PRE_CATE_GROUND);
	folder->appendChild(ground);
	getOrCreateFolder("Markers");
	getOrCreateFolder("Loads");
	getOrCreateFolder("Constraints");
	getOrCreateFolder("Contacts");
	getOrCreateFolder("Sets");
	getOrCreateFolder("Requests");
	getOrCreateFolder("Output");
	getOrCreateFolder("INTER");

}

Folder* Assembly::getOrCreateFolder( const QString& key )
{
	BaseItem* assemblyItem=this;
	BaseItem* a=assemblyItem->child(key);
	if(!a){
		Folder* folder=new Folder();
		folder->setID(BaseItem::nextCurrentMaxID());
		folder->setKeyname(key);
		folder->setCategory(TDY_PRE_CATE_FOLDER);
		this->appendChild(folder);
		return folder;
	}
	return (Folder*)a;
}


} // end namespace INSIDES