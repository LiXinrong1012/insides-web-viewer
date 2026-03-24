#include "category_register.h"
#include "precore_data.h"
#include "BaseItemFactory.h"
#include "itemlist.h"

using namespace INSIDES;

REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_UNKNOWN,BaseItem);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_BASE,BaseItem);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_FOLDER,BaseItem);

class RigidPartRegister : public Base::AbstractProducer
{  
public: 
	virtual void* Produce(void){
		BaseItem* item=new BaseItem();
		AppearanceItem* appItem=item->getAppearance();
		appItem->setUseColorAll(true);
		appItem->setColorAll(appItem->nextBuildinColor());
		return item;
	} 
	RigidPartRegister(){ BaseItemFactory()->AddProducer(TDY_PRE_CATE_RIGIDPART,this); }
};


class FEMPartRegister : public Base::AbstractProducer
{  
public: 
	virtual void* Produce(void){
		FEMPartBaseItem* item=new FEMPartBaseItem();
		AppearanceItem* appItem=item->getAppearance();
		appItem->setUseColorAll(true);
		appItem->setColorAll(appItem->nextBuildinColor());
		return item;
	} 
	FEMPartRegister(int t){ 
		BaseItemFactory()->AddProducer(t,this); 
	}
};


REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_ASSEMBLY,Assembly);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_LOAD,BaseItem);

class LoadRegister : public Base::AbstractProducer
{  
public: 
	virtual void* Produce(void){
		BaseItem* item=new BaseItem();
		AppearanceItem* appItem=item->getAppearance();
		appItem->setVisibilityType(AppearanceItem::Edge,AppearanceItem::Invisual);
		appItem->setVisibilityType(AppearanceItem::Marker,AppearanceItem::Invisual);
		appItem->setVisibilityType(AppearanceItem::Vertex,AppearanceItem::Invisual);
		appItem->setVisibilityType(AppearanceItem::Face,AppearanceItem::Visual);
		appItem->setVisibilityType(AppearanceItem::Line,AppearanceItem::Visual);
		return item;
	} 
	LoadRegister(){ BaseItemFactory()->AddProducer(TDY_PRE_CATE_LOAD,this); }
};

REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_MARKER,BaseItem);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_GRAPHICS,BaseItem);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_PARAMETERS,ParametersBaseItem);

class STLRegister : public Base::AbstractProducer
{  
public: 
	virtual void* Produce(void){
		BaseItem* item=new BaseItem();
		AppearanceItem* appItem=item->getAppearance();
		appItem->setVisibilityType(AppearanceItem::Edge,AppearanceItem::Invisual);
		appItem->setVisibilityType(AppearanceItem::Marker,AppearanceItem::Invisual);
		appItem->setVisibilityType(AppearanceItem::Vertex,AppearanceItem::Invisual);
		return item;
	} 
	STLRegister(){ BaseItemFactory()->AddProducer(TDY_PRE_CATE_STL,this); }
};

//REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_STL,BaseItem);
//REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_SHAPE,BaseItem);
class ShapeRegister : public Base::AbstractProducer
{  
public: 
	virtual void* Produce(void){
		BaseItem* item=new BaseItem();
		AppearanceItem* appItem=item->getAppearance();
		appItem->setVisibilityType(AppearanceItem::Edge,AppearanceItem::Invisual);
		appItem->setVisibilityType(AppearanceItem::Marker,AppearanceItem::Invisual);
		appItem->setVisibilityType(AppearanceItem::Vertex,AppearanceItem::Invisual);
		return item;
	} 
	ShapeRegister(){ BaseItemFactory()->AddProducer(TDY_PRE_CATE_SHAPE,this); }
};

REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_PARAMETERITEM,BaseItem);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_MOTION,BaseItem);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_JOINT,BaseItem);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_INTPAR,BaseItem);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_GROUND,BaseItem);


class ContactForceRegister : public Base::AbstractProducer
{  
public: 
	virtual void* Produce(void){
		BaseItem* item=new BaseItem();
		AppearanceItem* appItem=item->getAppearance();
		appItem->setVisibilityType(AppearanceItem::Edge,AppearanceItem::Invisual);
		appItem->setVisibilityType(AppearanceItem::Marker,AppearanceItem::Invisual);
		appItem->setVisibilityType(AppearanceItem::Vertex,AppearanceItem::Invisual);
		return item;
	} 
	ContactForceRegister(){ BaseItemFactory()->AddProducer(TDY_PRE_CATE_CONTACT,this); }
};

REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_REQUEST,BaseItem);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_CATE_SET,BaseItem);


REGISTER_BASEITEM_PRODUCER(TDY_PRE_ITEMCLASS_BASEITEM,BaseItem);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_ITEMCLASS_ASSEMBLY,Assembly);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_ITEMCLASS_PARAMETERS,ParametersBaseItem);
REGISTER_BASEITEM_PRODUCER(TDY_PRE_ITEMCLASS_FEMPART,FEMPartBaseItem);


void registerAllCategories()
{
	static STLRegister _stlregister;
	static LoadRegister _loadRegister;
	static ShapeRegister _shapeRegister;
	static ContactForceRegister _contactForceRegister;
	static RigidPartRegister _rigidPartRegister;
	static FEMPartRegister _FEMPartRegister1(TDY_PRE_CATE_FLEXPART);
	static FEMPartRegister _FEMPartRegister2(TDY_PRE_CATE_MNFPART);
	static FEMPartRegister _FEMPartRegister3(TDY_PRE_CATE_FEMPART);
}
