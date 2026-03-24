#include "ImportTDYImp.h"
#include "base/AppConfiguration.h"
#include "base/Console.h"

#include "precore/modeldocument.h"
#include "precore/itemlist.h"
#include "precore/precore_data.h"
#include "precore/UAPI_.h"
#include "precore/BaseItemManager.h"
#include "precore/BaseItemHelper.h"
#include "precore/DataExchangeAPI.h"

#include "pretdy/TDYParameters.h"

#include "edcompile/mainitem.h"

#include "baseitemposhelper.h"

#include <QDir>

using namespace INSEditor;
using namespace INSIDES;
using namespace Base;

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
		//item->updateInstance();
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

static void updateKeyValues(BaseItem* baseItem,Parse::LineItem* item)
{
	foreach(Parse::KeyValueItem* c,item->keyValues)
		baseItem->set(c->keyname.toUpper(),c->valueList.join(","));

	// 使用RGB赋颜色值
	if(Parse::KeyValueItem* p=item->getKeyvalue("RGB"))
	{
		vector<float> color;
		if(p->valueList.size()>=3 &&
			DataExchangeAPI::PString2FloatVec(baseItem,p->valueList.join(","),color))
		{
			AppearanceItem* apperance = baseItem->getAppearance();
			apperance->setColorAll(color[0]/255,color[1]/255,color[2]/255);
			apperance->setUseColorAll(true);
		}
	}

	//设置材质
	if(Parse::KeyValueItem* p = item->getKeyvalue("MATERIAL"))
		if(!p->valueList.isEmpty())
			baseItem->set("MATERIAL",p->valueList[0]); 
	
	// 使用Transparency赋透明度
	if (Parse::KeyValueItem* p=item->getKeyvalue("TRANSPARENCY"))
	{
		if(p->valueList.size()>0)
		{
			AppearanceItem* apperance = baseItem->getAppearance();
			apperance->setTransparency(p->valueList[0].toFloat());
		}
	}
}

ParametersBaseItem* _getParameterItem(BaseItem* item)
{
	int n=item->count();
	for(int i=0;i<n;++i)
		if(item->child(i)->getCategory()==TDY_PRE_CATE_PARAMETERITEM)
			return (ParametersBaseItem*)item->child(i);
	return NULL;
}

static bool PA_ITEM_Parameter(ImportTDYPara* para,Parse::LineItem* keyItem)
{
	ParametersBaseItem* paraItem=NULL;
	if(para->currentPart){
		paraItem=_getParameterItem(para->currentPart);
		if(!paraItem){
			paraItem=new ParametersBaseItem();
			paraItem->setKeyname("parameters");
			PREI_Add_Item(para->currentPart,paraItem);
		}
	}
	else{
		Assembly* assembly=para	->currentAssembly;
		paraItem=(ParametersBaseItem*)assembly->getOrCreateParameters();
	}

	if(!paraItem)
		return false;
	TDYParameters* tdyParas=paraItem->getParameters();	
	if(tdyParas)
	{
		foreach(Parse::KeyValueItem* keyvalue,keyItem->keyValues)
			tdyParas->add(keyvalue->keyname.toUpper(),keyvalue->valueList.join(",").toUpper(),"");
	}
	else{
		TDYParameters* tdyParas=new TDYParameters();
		foreach(Parse::KeyValueItem* keyvalue,keyItem->keyValues)
			tdyParas->add(keyvalue->keyname.toUpper(),keyvalue->valueList.join(",").toUpper(),"");
		paraItem->setTDYParameters(tdyParas);
	}

	updateKeyValues(paraItem,keyItem);
	paraItem->refreshChildren();

	return true;
}

static bool PA_Item_Assembly(ImportTDYPara* para,Parse::LineItem* key)
{
	Assembly* assembly=(Assembly*)myBaseItemManager()->create(TDY_PRE_CATE_ASSEMBLY);
	assembly->createDefault();
	assembly->setKeyname(key->mainLabel);
	BaseItem* assemParent=para->currentAssembly->getAssemblies();
	PREI_Add_Item(assemParent,assembly);

	Assembly* beforeAssem=para->currentAssembly;
	para->currentAssembly=assembly;
	para->importTDYImp->processItemChildren(para,key);

	para->currentAssembly=beforeAssem;
	return true;
}

static bool PA_PART_RigidPart(ImportTDYPara* para,Parse::LineItem* partKey)
{
	BaseItem* rigidPart=(BaseItem*)myBaseItemManager()->create(TDY_PRE_CATE_RIGIDPART);
	rigidPart->setKeyname(partKey->mainLabel);
	updateKeyValues(rigidPart,partKey);
	BaseItem* parts=para->currentAssembly->getParts();
	PREI_Add_Item(parts,rigidPart);
	para->currentPart=rigidPart;

	para->importTDYImp->processItemChildren(para,partKey);
	para->currentPart=NULL;

	return true;
}

static bool PA_PART_FEMPart(ImportTDYPara* para,Parse::LineItem* partKey)
{
	FEMPartBaseItem* femPart=(FEMPartBaseItem*)myBaseItemManager()->create(TDY_PRE_CATE_FEMPART);
	femPart->setKeyname(partKey->mainLabel);
	PREI_Add_Item(para->currentAssembly->getParts(),femPart);
	para->currentPart=femPart;

	para->importTDYImp->processItemChildren(para,partKey);

	femPart->updateInteralMesh();

	para->currentPart=NULL;
	return true;
}

static bool PA_ITEM_FNODE6(ImportTDYPara* para,Parse::LineItem* key)
{
	FEMPartBaseItem* femPart=(FEMPartBaseItem*)para->currentPart;
	QVector<SNode>& sNodeList=femPart->getSNodeList();
	SNode newNode;
	newNode.typeName=key->keyname.toUpper();
	QString strId=key->mainID;
	newNode.id=strId.toLong();
	Parse::KeyValueItem* p1=key->getKeyvalue("QG");
	if(!p1)
		p1=key->getKeyvalue("QR");
	if(p1){
		newNode.QG=p1->valueList.join(",");
		sNodeList.push_back(newNode);
	}
	return true;
}

static bool PA_ITEM_TBEAM(ImportTDYPara* para,Parse::LineItem* key)
{
	FEMPartBaseItem* femPart=(FEMPartBaseItem*)para->currentPart;
	QVector<SElement>& sElementList=femPart->getSElementList();
	SElement newElement;
	newElement.typeName=key->keyname.toUpper();
	QString strId=key->mainID;
	newElement.id=strId.toLong();
	Parse::KeyValueItem* p1=key->getKeyvalue("NODE");
	if(p1){
		newElement.nodeList=p1->valueList.join(",");
		sElementList.push_back(newElement);
	}
	return true;
}

static bool PA_ITEM_Rigid6(ImportTDYPara* para,Parse::LineItem* keyItem)
{
	BaseItem* item=para->currentPart;
	updateKeyValues(item,keyItem);
	return true;
}


static bool PA_ITEM_Instance(ImportTDYPara* para,Parse::LineItem* keyItem)
{
	BaseItem* relatedPart=NULL;
	foreach(Parse::KeyValueItem* c,keyItem->keyValues)
	{
		if ( (c->keyname.compare("PART",Qt::CaseInsensitive)==0 )
			||(c->keyname.compare("ASSEMBLY",Qt::CaseInsensitive)==0 ) )
		{
			relatedPart=para->currentAssembly->findItemWithoutFolder(c->valueList[0]);
			break;
		}
	}
	if(relatedPart==0){
		QString tmp=keyItem->toString();
		Base::Console().Warning("Wrong instance. %s",tmp.toStdString().c_str());
		return 0;
	}

	BaseItem* item=relatedPart->createInstance();
	item->setKeyname(keyItem->mainLabel);
	PREI_Add_Item(para->currentAssembly->getInstances(),item);
	//instance / 1, qubing_1,  part = qubing,  center = "$L1/2",     0, 0
	updateKeyValues(item,keyItem);
	_updateInstanceParameters(item);

	if(item->getCategory()==TDY_PRE_CATE_RIGIDPART)
		BaseItemPosHelper::updateInstanceRigid(item);
	else
		BaseItemPosHelper::updateInstance(item);

	return true;
}

static bool PA_ITEM_External(ImportTDYPara* para,Parse::LineItem* keyItem)
{
	Parse::KeyValueItem* p1=keyItem->getKeyvalue("INSTANCE");
	if(!p1)
		return true;

	BaseItem* relatedPart=NULL;
	BaseItem* c=para->currentAssembly->getParent();
	while(c){
		if(c->getCategory()==TDY_PRE_CATE_ASSEMBLY)
			break;
		c=c->getParent();
	}
	if(!c)
		return true;

	relatedPart=para->currentAssembly->findItemWithoutFolder(p1->valueList[0],(INSIDES::Assembly*)c);

	if(!relatedPart){
		Base::Console().Warning("Wrong external instance. File position: (%d, %d)",
			p1->rowIndex+1,p1->columnIndex+1);
		return true;
	}

	BaseItem* item=relatedPart->cloneAll();
	item->setIsExternal(true);
	item->setKeyname(keyItem->mainLabel);

	PREI_Add_Item(para->currentAssembly->getInstances(),item);
	updateKeyValues(item,keyItem);
	return true;
}

static bool PA_ITEM_Marker(ImportTDYPara* para,Parse::LineItem* keyItem)
{
	BaseItem* marker=NULL;
	// ground marker
	if(keyItem->hasProperty("GROUND"))
	{
		marker=(BaseItem*)myBaseItemManager()->create(TDY_PRE_CATE_MARKER);
		
		Assembly* preAssem=para->currentAssembly;
		BaseItem* ground=preAssem->getGround();
		PREI_Add_Item(ground,marker);
	}
	else
	{
		BaseItem* item=para->currentPart;
		if(item){
			marker=(BaseItem*)myBaseItemManager()->create(TDY_PRE_CATE_MARKER);
			PREI_Add_Item(item,marker);
		}
		else
		{
			marker=(BaseItem*)myBaseItemManager()->create(TDY_PRE_CATE_MARKER);
			PREI_Add_Item(para->currentAssembly->getMarkers(),marker);
		}
	}

	if(marker)
	{
		marker->setKeyname(keyItem->mainLabel);
		updateKeyValues(marker,keyItem);
		BaseItemPosHelper::updateMarker(marker);
	}

	return true;
}



static bool PA_ITEM_Graphic(ImportTDYPara* para,Parse::LineItem* keyItem)
{
	BaseItem* item=(BaseItem*)myBaseItemManager()->create(TDY_PRE_CATE_SHAPE);
	item->setKeyname(keyItem->mainLabel);
	PREI_Add_Item(para->currentPart,item);

	Parse::KeyValueItem* tmp=keyItem->getKeyvalue("RADIUS");
	QString radius=tmp?tmp->valueList[0]:QString();
	tmp=keyItem->getKeyvalue("HEIGHT");
	QString height=tmp?tmp->valueList[0]:QString();
	tmp=keyItem->getKeyvalue("LENGTH");
	QString length=tmp?tmp->valueList[0]:QString();
	tmp=keyItem->getKeyvalue("WIDTH");
	QString width=tmp?tmp->valueList[0]:QString();

	if(keyItem->hasProperty("CYLINDER")){
		(*item)["DATAVEC"]=radius+","+height;
		(*item)["SHAPEKEYNAME"]="Cylinder";
	}
	else if(keyItem->hasProperty("BOX"))
	{
		(*item)["DATAVEC"]=length+","+width+","+height;
		(*item)["SHAPEKEYNAME"]="Box";
	}
	else if(keyItem->hasProperty("SPHERE"))
	{
		(*item)["DATAVEC"]=radius;
		(*item)["SHAPEKEYNAME"]="Sphere";
	}
	else if(keyItem->getKeyvalue("FILE") || keyItem->getKeyvalue("STL")) 
	{
		Parse::KeyValueItem* p1=keyItem->getKeyvalue("FILE");
		if(!p1)
			p1 = keyItem->getKeyvalue("STL");
		QString stlfileName=p1->valueList[0];
		QFileInfo fileInfo(stlfileName);
		QString a=fileInfo.absoluteFilePath();
		if(!a.isEmpty())
			(*item)["FILENAME"]=a;
		item->setCategory(TDY_PRE_CATE_STL);
	}
	

	updateKeyValues(item,keyItem);
	QString scale=item->get("SCALE");
	if(!scale.isEmpty()){
		float vScale[1];
		DataExchangeAPI::String2Vec(NULL,scale,vScale,1);
		BaseItemPosHelper::updateGraphic(item,vScale[0]);
	}
	else
		BaseItemPosHelper::updateGraphic(item);
	return true;
}

static bool PA_ITEM_Request(ImportTDYPara* para,Parse::LineItem* key)
{
	BaseItem* baseItem=(BaseItem*)myBaseItemManager()->create(TDY_PRE_CATE_REQUEST);
	baseItem->setKeyname(key->mainLabel);
	PREI_Add_Item(para->currentAssembly->getRequests(),baseItem);
	updateKeyValues(baseItem,key);
	return true;
}

static bool PA_ITEM_Set(ImportTDYPara* para,Parse::LineItem* key)
{
	BaseItem* baseItem=(BaseItem*)myBaseItemManager()->create(TDY_PRE_CATE_SET);
	baseItem->setKeyname(key->mainLabel);
	PREI_Add_Item(para->currentAssembly->getSets(),baseItem);
	updateKeyValues(baseItem,key);
	return true;
}

static bool PA_ITEM_Joint(ImportTDYPara* para,Parse::LineItem* key)
{
	BaseItem* baseItem=(BaseItem*)myBaseItemManager()->create(TDY_PRE_CATE_JOINT);
	baseItem->setKeyname(key->mainLabel);

	if(key->properties.size()){
		Parse::PropertyItem* p1=key->properties[0];
		baseItem->set("JOINTTYPE",p1->name);
	}

	updateKeyValues(baseItem,key);
	PREI_Add_Item(para->currentAssembly->getConstraints(),baseItem);
	return true;
}

static bool PA_ITEM_SpringDamper(ImportTDYPara* para,Parse::LineItem* key)
{
	BaseItem* baseItem=myBaseItemManager()->create(TDY_PRE_CATE_LOAD);
	baseItem->setKeyname(key->mainLabel);

	updateKeyValues(baseItem,key);
	PREI_Add_Item(para->currentAssembly->getLoads(),baseItem);
	return true;
}

static bool PA_ITEM_CONTACT_SPH_SPLINE(ImportTDYPara* para,Parse::LineItem* key)
{
	BaseItem* baseItem=myBaseItemManager()->create(TDY_PRE_CATE_CONTACT);
	baseItem->setKeyname(key->mainLabel);

	updateKeyValues(baseItem,key);
	PREI_Add_Item(para->currentAssembly->getContacts(),baseItem);
	return true;
}

void registerImportFuncs(ImportTDYImp* imp)
{
	imp->registerLoadKey("RIGIDPART",PA_PART_RigidPart);
	imp->registerLoadKey("RIGIDGEARPART",PA_PART_RigidPart);
	imp->registerLoadKey("FEMPART",PA_PART_FEMPart);
	imp->registerLoadKey("VFEMPART",PA_PART_FEMPart);
	imp->registerLoadKey("MNFPART",PA_PART_FEMPart);
	imp->registerLoadKey("MNFGEARPART",PA_PART_FEMPart);
	imp->registerLoadKey("FLEXGEARPART",PA_PART_FEMPart);
	imp->registerLoadKey("ASSEMBLY",PA_Item_Assembly);
	imp->registerLoadKey("EXTERNAL",PA_ITEM_External);

	imp->registerLoadKey("PARAMETER",PA_ITEM_Parameter);
	imp->registerLoadKey("INSTANCE",PA_ITEM_Instance);
	imp->registerLoadKey("RIGID6",PA_ITEM_Rigid6);
	imp->registerLoadKey("RIGIDGEAR6",PA_ITEM_Rigid6);
	imp->registerLoadKey("MARKER",PA_ITEM_Marker);
	imp->registerLoadKey("GRAPHIC",PA_ITEM_Graphic);
	imp->registerLoadKey("REQUEST",PA_ITEM_Request);
	imp->registerLoadKey("SET",PA_ITEM_Set);

	imp->registerLoadKey("JOINT",PA_ITEM_Joint);
	imp->registerLoadKey("JOINT_GEAR",PA_ITEM_Joint);
	// load
	imp->registerLoadKey("SPRINGDAMPER",PA_ITEM_SpringDamper);
	imp->registerLoadKey("SFORCE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("SFORCE_GEAR",PA_ITEM_SpringDamper);
	imp->registerLoadKey("VFORCE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("GFORCE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("VTORQUE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("BUSHING",PA_ITEM_SpringDamper);
	imp->registerLoadKey("BEAMFORCE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("CONTACT_SPH_RCT",PA_ITEM_SpringDamper);
	imp->registerLoadKey("CONTACT_RIGID_RIGID",PA_ITEM_CONTACT_SPH_SPLINE);
	imp->registerLoadKey("CONTACT_G2G_RIGID",PA_ITEM_CONTACT_SPH_SPLINE);
	imp->registerLoadKey("FIELD",PA_ITEM_SpringDamper);
	imp->registerLoadKey("CONTACT_SPH_SPLINE",PA_ITEM_SpringDamper);
	imp->registerLoadKey("CONTACT_FEM_SHAPE",PA_ITEM_CONTACT_SPH_SPLINE);
	imp->registerLoadKey("CONTACT_FEM_SHAPE2",PA_ITEM_CONTACT_SPH_SPLINE);
	imp->registerLoadKey("CONTACT_SET_SHAPE",PA_ITEM_CONTACT_SPH_SPLINE);
	imp->registerLoadKey("CONTACT_FEM_SHAPE_MODI",PA_ITEM_CONTACT_SPH_SPLINE);
	imp->registerLoadKey("JOINT",PA_ITEM_Joint);
	imp->registerLoadKey("SLIDINGJOINT7",PA_ITEM_Joint);
	imp->registerLoadKey("SLIDINGFRICTION7",PA_ITEM_SpringDamper);
	imp->registerLoadKey("THELEN2003MUSCLE",PA_ITEM_SpringDamper);

	imp->registerLoadKey("CONTACT_G2G",PA_ITEM_CONTACT_SPH_SPLINE);
	imp->registerLoadKey("CONTACT_G2G_MNF",PA_ITEM_CONTACT_SPH_SPLINE);
	imp->registerLoadKey("CONTACT_G2G_FLEX",PA_ITEM_CONTACT_SPH_SPLINE);
	

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