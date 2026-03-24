#include "ImportTDYImp.h"
#include "base/AppConfiguration.h"
#include "base/Console.h"

#include "precore/modeldocument.h"
#include "precore/itemlist.h"
#include "precore/precore_data.h"
#include "precore/UAPI_.h"
#include "precore/BaseItemManager.h"
#include "precore/BaseItemHelper.h"

#include "thusolver/parsefile/Scanner.h"
#include "thusolver/parsefile/Parser.h"
#include "thusolver/parsefile/TemplateFactory.h"
#include "thusolver/parsefile/Assembly.h"

#include "pp_xml/XMLHandler.h"

#include "pretdy/TDYParameters.h"


#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace Base;
using namespace INSIDES;

static void _updateInstanceParameters(INSIDES::BaseItem* instanceItem);

static void _replaceInstanceParameters(INSIDES::BaseItem* item,const QStringList& namelist,const QVector<double>& valuelist)
{
	if(item->getCategory()==TDY_PRE_CATE_PARAMETERS){
		ParametersBaseItem* paraItem=(ParametersBaseItem*)item;
		for(int i=0;i<namelist.size();++i){
			if(paraItem->getParameters()->hasKey(namelist[i])){
				paraItem->getParameters()->addOrReplace(namelist[i],QString("%1").arg(valuelist[i]));
			}
		}
		paraItem->refreshContents();
	}
	else if(item->isInstance()){
		_updateInstanceParameters(item);
	}
	else{
		for(int i=0;i<item->count();++i){
			BaseItem* childItem=item->child(i);
			_replaceInstanceParameters(childItem,namelist,valuelist);
		}
	}

	if(item->getCategory()==TDY_PRE_CATE_FEMPART)
	{
		FEMPartBaseItem* femItem=(FEMPartBaseItem*)item;
		femItem->updateInteralMesh();
	}
}

static void _updateInstanceParameters(BaseItem* instanceItem)
{
	if(!instanceItem->hasKey("PARA_NAME"))
		return;

	// 处理参数
	QString nameList=instanceItem->get("PARA_NAME");
	QString valueList=instanceItem->get("PARA_VALUE");
	QStringList nameVec=nameList.split(",");
	QStringList valueVec=valueList.split(",");
	QVector<double>	doubleValueVec;
	ParametersBaseItem* parentParaItem=BaseItemHelper::getRelatedParameters(instanceItem);
	int n=nameVec.size();
	if(n!=valueVec.size()){
		Console().Error("Unmatched para_name and para_value.");
		return;
	}
	if(n==0)
		return;

	if(!parentParaItem){
		Console().Error("Find parameter failed.");
		for(int i=0;i<n;++i){
			doubleValueVec.push_back(valueVec[i].toDouble());
		}
	}else{
		for(int i=0;i<n;++i){
			doubleValueVec.push_back(parentParaItem->getParameters()->getValue(valueVec[i]));
		}
	}

	int nCount=instanceItem->count();
	for(int i=0;i<nCount;++i)
		_replaceInstanceParameters(instanceItem->child(i),nameVec,doubleValueVec);
}

static void _setRandomColor(BaseItem* item)
{
	AppearanceItem* app=item->getAppearance();
	app->setUseColorAll(true);
	app->setColorAll(app->nextBuildinColor());
}

static void update_name_and_properties(ImportTDYPara* para,BaseItem* baseItem,Parse::Key* key)
{
	Parse::MainItem mainItem=key->mainItem;
	if(mainItem.mainname.empty())
		baseItem->setKeyname(mainItem.mainID.c_str());
	else
		baseItem->setKeyname(mainItem.mainLabel.c_str());

	list<Parse::SubItem*>& subItems=mainItem.sublist;
	for(list<Parse::SubItem*>::iterator b=subItems.begin();
		b!=subItems.end();++b){
			Parse::SubItem* subItem=*b;

			(*baseItem)[subItem->subname.c_str()]=para->importTDYImp->stringlist2QString(subItem->valList);
	}
}

static bool PA_ITEM_Parameter(ImportTDYPara* para,Parse::Key* keyItem)
{
	TDYParameters* tdyParas=new TDYParameters();
	Parse::MainItem mainItem=keyItem->mainItem;
	list<Parse::SubItem*>& subItems=mainItem.sublist;
	for(list<Parse::SubItem*>::iterator b=subItems.begin();
		b!=subItems.end();++b){
			Parse::SubItem* subItem=*b;
			tdyParas->add(subItem->subname.c_str(),subItem->valList[0].c_str(),"");
	}

	ParametersBaseItem* paraItem=NULL;
	if(para->currentPart){
		paraItem=new ParametersBaseItem();
		paraItem->setKeyname("parameters");
		PREI_Add_Item(para->currentPart,paraItem);
	}
	else{
		PreAssembly* assembly=para	->currentAssembly;
		paraItem=(ParametersBaseItem*)assembly->getOrCreateParameters();
	}

	paraItem->setTDYParameters(tdyParas);
	paraItem->refreshChildren();

	return true;
}

static bool PA_ITEM_Rigid6(ImportTDYPara* para,Parse::Key* keyItem)
{
	BaseItem* item=para->currentPart;
	Parse::MainItem mainItem=keyItem->mainItem;
	list<Parse::SubItem*>& subItems=mainItem.sublist;
	for(list<Parse::SubItem*>::iterator b=subItems.begin();
		b!=subItems.end();++b){
			Parse::SubItem* subItem=*b;

			(*item)[subItem->subname.c_str()]=para->importTDYImp->stringlist2QString(subItem->valList);
	}
	return true;
}

static bool PA_ITEM_Marker(ImportTDYPara* para,Parse::Key* keyItem)
{
	// ground marker
	if(keyItem->mainItem.hasProperty("GROUND"))
	{
		BaseItem* marker=new BaseItem();
		marker->setCategory(TDY_PRE_CATE_MARKER);

		PreAssembly* preAssem=para->currentAssembly;
		BaseItem* ground=preAssem->getGround();
		PREI_Add_Item(ground,marker);

		update_name_and_properties(para,marker,keyItem);

		return true;
	}
	BaseItem* item=para->currentPart;
	if(item){
		if(item->getCategory()==TDY_PRE_CATE_FEMPART)
		{
			BaseItem* marker=new BaseItem();
			marker->setCategory(TDY_PRE_CATE_MARKER);

			PREI_Add_Item(item,marker);

			update_name_and_properties(para,marker,keyItem);

			return true;
		}

		BaseItem* marker=new BaseItem();
		marker->setCategory(TDY_PRE_CATE_MARKER);

		PREI_Add_Item(item,marker);
			
		update_name_and_properties(para,marker,keyItem);
	}else{
		// marker on ground
		BaseItem* marker=new BaseItem();
		marker->setCategory(TDY_PRE_CATE_MARKER);

		BaseItem* ground=para->doc->findItemWithoutFolder("ground",para->currentAssembly);
		PREI_Add_Item(ground,marker);

		update_name_and_properties(para,marker,keyItem);
	}

	return true;
}

static bool PA_ITEM_Graphic(ImportTDYPara* para,Parse::Key* keyItem)
{
	BaseItem* item=(BaseItem*)myBaseItemManager()->create(TDY_PRE_CATE_SHAPE);
	Parse::MainItem mainItem=keyItem->mainItem;
	if(mainItem.mainname.empty())
		item->setKeyname(mainItem.mainID.c_str());
	else
		item->setKeyname(mainItem.mainLabel.c_str());

	PREI_Add_Item(para->currentPart,item);
	vector<string> *strVals;

	if(mainItem.hasProperty("CYLINDER")){
		QString radius=mainItem.subhash["RADIUS"]->valList[0].c_str();
		QString length=mainItem.subhash["HEIGHT"]->valList[0].c_str();
		(*item)["DATAVEC"]=radius+","+length;
		(*item)["SHAPEKEYNAME"]="Cylinder";
	}
	else if(mainItem.hasProperty("BOX"))
	{
		QString length=mainItem.subhash["LENGTH"]->valList[0].c_str();
		QString width=mainItem.subhash["WIDTH"]->valList[0].c_str();
		QString height=mainItem.subhash["HEIGHT"]->valList[0].c_str();
		(*item)["DATAVEC"]=length+","+width+","+height;
		(*item)["SHAPEKEYNAME"]="Box";
	}
	else if(mainItem.hasProperty("SPHERE"))
	{
		QString radius=mainItem.subhash["RADIUS"]->valList[0].c_str();
		(*item)["DATAVEC"]=radius;
		(*item)["SHAPEKEYNAME"]="Sphere";
	}
	else if(mainItem.GetValue("STL",strVals))
	{
		QString stlfileName=(*strVals)[0].c_str();
		(*item)["FILENAME"]=stlfileName;
		item->setCategory(TDY_PRE_CATE_STL);

		bool hasScale=mainItem.GetValue("SCALE",strVals);
		if(hasScale)
			(*item)["SCALE"]=para->importTDYImp->stringlist2QString(*strVals);

	}

	static string checklist[]={"CM","RM"};
	for(int i=0;i<2;++i){
		SubItem* relatedMarker=mainItem.subhash[checklist[i]];
		if(relatedMarker)
			item->set(checklist[i].c_str(),relatedMarker->valList[0].c_str());
	}

	return true;
}
static bool PA_ITEM_Instance(ImportTDYPara* para,Parse::Key* keyItem)
{
	list<Parse::SubItem*>& subItems=keyItem->mainItem.sublist;
	BaseItem* relatedPart=NULL;
	for(list<Parse::SubItem*>::iterator b=subItems.begin();
		b!=subItems.end();++b){
			Parse::SubItem* subItem=*b;
			if(subItem->subname=="PART"|| subItem->subname=="ASSEMBLY"){
				relatedPart=para->doc->findItemWithoutFolder(subItem->valList[0].c_str(),para->currentAssembly);
				break;
			}
	}
	if(relatedPart==0){
		Base::Console().Warning("Wrong instance.");
		return 0;
	}

	BaseItem* item=relatedPart->createInstance();
	Parse::MainItem mainItem=keyItem->mainItem;
	if(mainItem.mainname.empty())
		item->setKeyname(mainItem.mainID.c_str());
	else
		item->setKeyname(mainItem.mainLabel.c_str());
	PREI_Add_Item(para->currentAssembly->getInstances(),item);
	//instance / 1, qubing_1,  part = qubing,  center = "$L1/2",     0, 0
	for(list<Parse::SubItem*>::iterator b=subItems.begin();
		b!=subItems.end();++b){
			Parse::SubItem* subItem=*b;
			if(subItem->subname!="PART"){
				(*item)[subItem->subname.c_str()]=para->importTDYImp->stringlist2QString(subItem->valList);
			}
	}
	_updateInstanceParameters(item);
	return true;
}

static bool PA_ITEM_External(ImportTDYPara* para,Parse::Key* keyItem)
{
	list<Parse::SubItem*>& subItems=keyItem->mainItem.sublist;
	BaseItem* relatedPart=NULL;
	for(list<Parse::SubItem*>::iterator b=subItems.begin();
		b!=subItems.end();++b){
			Parse::SubItem* subItem=*b;
			if(subItem->subname=="INSTANCE"){
				BaseItem* c=para->currentAssembly->getParent();
				while(c){
					if(c->getCategory()==TDY_PRE_CATE_ASSEMBLY)
						break;
					c=c->getParent();
				}
				if(c)
					relatedPart=para->doc->findItemWithoutFolder(subItem->valList[0].c_str(),(INSIDES::Assembly*)c);
				break;
			}
	}
	if(relatedPart==0){
		Base::Console().Warning("Wrong external instance.");
		return 0;
	}

	BaseItem* item=relatedPart->cloneAll();
	Parse::MainItem mainItem=keyItem->mainItem;
	if(mainItem.mainname.empty())
		item->setKeyname(mainItem.mainID.c_str());
	else
		item->setKeyname(mainItem.mainLabel.c_str());
	PREI_Add_Item(para->currentAssembly->getInstances(),item);
	//instance / 1, qubing_1,  part = qubing,  center = "$L1/2",     0, 0
	for(list<Parse::SubItem*>::iterator b=subItems.begin();
		b!=subItems.end();++b){
			Parse::SubItem* subItem=*b;
			if(subItem->subname!="PART"){
				(*item)[subItem->subname.c_str()]=para->importTDYImp->stringlist2QString(subItem->valList);
			}
	}
	//item->updateInstance();
	//_updateInstanceParameters(item);
	return true;
}

static bool PA_PART_RigidPart(ImportTDYPara* para,Parse::Part* partKey)
{
	BaseItem* rigidPart=new BaseItem();
	_setRandomColor(rigidPart);

	rigidPart->setCategory(TDY_PRE_CATE_RIGIDPART);
	rigidPart->setKeyname(partKey->strName.c_str());
	BaseItem* parts=para->currentAssembly->getParts();
	PREI_Add_Item(parts,rigidPart);
	para->currentPart=rigidPart;

	bool result=para->importTDYImp->processKeyList(para,partKey->listKeys);
	para->currentPart=NULL;

	return result;
}

static bool PA_PART_FEMPart(ImportTDYPara* para,Parse::Part* partKey)
{
	FEMPartBaseItem* femPart=new FEMPartBaseItem();
	_setRandomColor(femPart);
	femPart->setKeyname(partKey->strName.c_str());
	PREI_Add_Item(para->currentAssembly->getParts(),femPart);
	para->currentPart=femPart;

	bool result=para->importTDYImp->processKeyList(para,partKey->listKeys);

	femPart->updateInteralMesh();

	para->currentPart=NULL;
	return true;
}

static bool PA_ITEM_FNODE6(ImportTDYPara* para,Parse::Key* key)
{
	FEMPartBaseItem* femPart=(FEMPartBaseItem*)para->currentPart;
	QVector<SNode>& sNodeList=femPart->getSNodeList();
	SNode newNode;
	newNode.typeName=key->mainItem.mainname.c_str();
	QString strId=key->mainItem.mainID.c_str();
	newNode.id=strId.toLong();
	newNode.QG=para->importTDYImp->stringlist2QString(key->mainItem.subhash["QG"]->valList);
	sNodeList.push_back(newNode);
	return true;
}
static bool PA_ITEM_TBEAM(ImportTDYPara* para,Parse::Key* key)
{
	FEMPartBaseItem* femPart=(FEMPartBaseItem*)para->currentPart;
	QVector<SElement>& sElementList=femPart->getSElementList();
	SElement newElement;
	newElement.typeName=key->mainItem.mainname.c_str();
	QString strId=key->mainItem.mainID.c_str();
	newElement.id=strId.toLong();
	newElement.nodeList=para->importTDYImp->stringlist2QString(key->mainItem.subhash["NODE"]->valList);
	sElementList.push_back(newElement);
	return true;
}

static bool PA_ITEM_SpringDamper(ImportTDYPara* para,Parse::Key* key)
{
	BaseItem* baseItem=myBaseItemManager()->create(TDY_PRE_CATE_LOAD);

	update_name_and_properties(para,baseItem,key);

	BaseItem* parts=para->currentAssembly->getLoads();
	PREI_Add_Item(parts,baseItem);

	return true;
}
static bool PA_ITEM_CONTACT_SPH_SPLINE(ImportTDYPara* para,Parse::Key* key)
{
	BaseItem* baseItem=(BaseItem*)myBaseItemManager()->create(TDY_PRE_CATE_CONTACT);

	update_name_and_properties(para,baseItem,key);

	BaseItem* parts=para->currentAssembly->getContacts();
	PREI_Add_Item(parts,baseItem);

	return true;
}


static bool PA_ITEM_Joint(ImportTDYPara* para,Parse::Key* key)
{
	BaseItem* baseItem=new BaseItem();

	baseItem->setCategory(TDY_PRE_CATE_JOINT);
	Parse::MainItem mainItem=key->mainItem;
	if(mainItem.mainname.empty())
		baseItem->setKeyname(mainItem.mainID.c_str());
	else
		baseItem->setKeyname(mainItem.mainLabel.c_str());

	if(mainItem.properties.size()>0){
		std::map<string,string>::iterator b=mainItem.properties.begin();
		baseItem->set("JOINTTYPE",b->second.c_str());
	}

	list<Parse::SubItem*>& subItems=mainItem.sublist;
	for(list<Parse::SubItem*>::iterator b=subItems.begin();
		b!=subItems.end();++b){
			Parse::SubItem* subItem=*b;

			(*baseItem)[subItem->subname.c_str()]=para->importTDYImp->stringlist2QString(subItem->valList);
	}

	BaseItem* parts=para->currentAssembly->getConstraints();
	PREI_Add_Item(parts,baseItem);

	return true;
}

static bool PA_ITEM_Request(ImportTDYPara* para,Parse::Key* key)
{
	BaseItem* baseItem=new BaseItem();

	baseItem->setCategory(TDY_PRE_CATE_REQUEST);
	Parse::MainItem mainItem=key->mainItem;
	if(mainItem.mainname.empty())
		baseItem->setKeyname(mainItem.mainID.c_str());
	else
		baseItem->setKeyname(mainItem.mainLabel.c_str());

	BaseItem* parts=para->currentAssembly->getRequests();
	PREI_Add_Item(parts,baseItem);
	return true;
}


static bool PA_ITEM_Set(ImportTDYPara* para,Parse::Key* key)
{
	BaseItem* baseItem=new BaseItem();
	baseItem->setCategory(TDY_PRE_CATE_SET);

	update_name_and_properties(para,baseItem,key);
	PREI_Add_Item(para->currentAssembly->getSets(),baseItem);
	return true;
}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void registerImportFuncs(ImportTDYImp* imp)
{
	imp->registerLoadPart("RIGIDPART",PA_PART_RigidPart);
	imp->registerLoadPart("FEMPART",PA_PART_FEMPart);
	imp->registerLoadPart("VFEMPART",PA_PART_FEMPart);
	imp->registerLoadPart("MNFPART",PA_PART_FEMPart);


	imp->registerLoadKey("PARAMETER",PA_ITEM_Parameter);
	imp->registerLoadKey("RIGID6",PA_ITEM_Rigid6);
	imp->registerLoadKey("MARKER",PA_ITEM_Marker);
	imp->registerLoadKey("INSTANCE",PA_ITEM_Instance);
	imp->registerLoadKey("EXTERNAL",PA_ITEM_External);
	imp->registerLoadKey("GRAPHIC",PA_ITEM_Graphic);
	imp->registerLoadKey("REQUEST",PA_ITEM_Request);
	imp->registerLoadKey("SET",PA_ITEM_Set);

	// load
	imp->registerLoadKey("SPRINGDAMPER",PA_ITEM_SpringDamper);
	imp->registerLoadKey("SFORCE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("VFORCE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("GFORCE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("VTORQUE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("BUSHING",PA_ITEM_SpringDamper);
	imp->registerLoadKey("BEAMFORCE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("CONTACT_SPH_RCT",PA_ITEM_SpringDamper);
	imp->registerLoadKey("CONTACT_RIGID_RIGID",PA_ITEM_CONTACT_SPH_SPLINE);
	imp->registerLoadKey("FIELD",PA_ITEM_SpringDamper);
	imp->registerLoadKey("CONTACT_SPH_SPLINE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("CONTACT_FEM_SHAPE",PA_ITEM_CONTACT_SPH_SPLINE);
	//imp->registerLoadKey("CONTACT_SPH_SPLINE",PA_ITEM_CONTACT_SPH_SPLINE);
	imp->registerLoadKey("JOINT",PA_ITEM_Joint);
	

	imp->registerLoadKey("FNODE6",PA_ITEM_FNODE6);
	imp->registerLoadKey("FQUATNODE",PA_ITEM_FNODE6);
	imp->registerLoadKey("FNODE7",PA_ITEM_FNODE6);
	imp->registerLoadKey("FNODE8",PA_ITEM_FNODE6);
	imp->registerLoadKey("FNODE9",PA_ITEM_FNODE6);
	imp->registerLoadKey("FNODE10",PA_ITEM_FNODE6);
	imp->registerLoadKey("FNODE11",PA_ITEM_FNODE6);
	imp->registerLoadKey("FNODE12",PA_ITEM_FNODE6);

	imp->registerLoadKey("FNODE3",PA_ITEM_FNODE6);
	imp->registerLoadKey("VFNODE3",PA_ITEM_FNODE6);
	imp->registerLoadKey("VFNODE6",PA_ITEM_FNODE6);


	imp->registerLoadKey("TBEAM",PA_ITEM_TBEAM);
	imp->registerLoadKey("EBEAM",PA_ITEM_TBEAM);
	imp->registerLoadKey("QUAD",PA_ITEM_TBEAM);
	imp->registerLoadKey("SHELL",PA_ITEM_TBEAM);
	imp->registerLoadKey("PLATE",PA_ITEM_TBEAM);

	imp->registerLoadKey("CABLE",PA_ITEM_TBEAM);
	imp->registerLoadKey("VCABLE",PA_ITEM_TBEAM);
	imp->registerLoadKey("VBEAM",PA_ITEM_TBEAM);


}