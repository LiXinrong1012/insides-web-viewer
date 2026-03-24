#include "HoopsShapeManager.h"
#include "HoopsDrawTool.h"
#include "base/Console.h"
#include "shapeinputlib.h"
#include "HoopsUltility.h"

using namespace Base;



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
HoopsShapeManager* HoopsShapeManager::_instance=NULL;

bool _checkShapeSize(float s){
	if(s<=0||s>1e8){
		Console().Warning("Shapes' scale is too small or too big.( size = %f )",s);
		return false;
	}
	return true;
}
HoopsShapeManager* HoopsShapeManager::instance()
{
	if(!_instance){
		_instance=new HoopsShapeManager();
		DrawTool* drawTool=new HoopsDrawTool();
		_instance->setDrawTool(drawTool);
	}
	return _instance;
}
void HoopsShapeManager::destruct()
{
	if(_instance){
		DrawTool* drawTool=_instance->getDrawTool();
		if(drawTool){
			delete drawTool;
		}
		delete _instance;
		_instance=NULL;
	}
}
HoopsShapeManager::HoopsShapeManager(void)
:_rootDir("?Include Library/Shape Library")
,_drawTool(NULL)
,_globalScale(1.0f)
,_lineWidth(2.0)
{
	HC_Open_Segment("?Include Library");
	HC_Open_Segment("Shape Library");
	HC_Close_Segment();
	HC_Close_Segment();
}

HoopsShapeManager::~HoopsShapeManager(void)
{
	clear();
}

void HoopsShapeManager::insertShape(const char* keyName,ShapeInsertionFun fun)
{
	ShapeItem* item=new ShapeItem(keyName,fun);

	HC_KEY key=HC_Open_Segment(getFullName(keyName).c_str());
	HC_Set_Line_Weight(_lineWidth);
	//HC_Set_Selectability("everything=off");
	//HC_Define_System_Options("bounding volumes=off");
	fun();
	HC_Close_Segment();

	item->_hcKey=key;
	_keyMap[keyName]=item;
}
void HoopsShapeManager::insertShape(const char* keyName,const ShapePara* para,ShapeImportFun fun)
{
	ShapeItem *item=new ShapeItem(keyName);
	if(para)
		item->_shapePara=new ShapePara(*para);
	item->_shapeImportFun=fun;
	_keyMap[keyName]=item;
}

bool HoopsShapeManager::setStaticPara(const char* keyName,int index,ShapePara::ValueType value)
{
	KeyMap::iterator f=_keyMap.find(keyName);
	if(f==_keyMap.end())
		return false;

	if(index<ShapePara::MAX_VALUE_COUNT&&index>=0){
		ShapePara* para=f->second->_shapePara;
		if(para){
			para->values[index]=value;
			return true;
		}
	}
	return false;
}
bool HoopsShapeManager::setStaticPara(const char* keyName,int index,const std::string& str)
{
	KeyMap::iterator f=_keyMap.find(keyName);
	if(f==_keyMap.end())
		return false;

	if(index<ShapePara::MAX_STRING_COUNT&&index>=0){
		ShapePara* para=f->second->_shapePara;
		if(para){
			para->_str[index]=str;
			return true;
		}
	}
	return false;
}

void HoopsShapeManager::updateShapeScale(const ShapeItem& item)
{
	if(item._hcKey==INVALID_KEY)
		return;

	HC_Open_Segment_By_Key(item._hcKey);
	float size;
	if(item._bUseAbsolute)
		size=item._absoluteDemision;
	else
		size=item._scale*_globalScale;
	HoopsUltility::setModelMatrix_Scale(size,size,size);
	HC_Close_Segment();
}
bool HoopsShapeManager::setShapeScale(const char* keyName, float scale)
{
	if(!_checkShapeSize(scale))
		return false;

	KeyMap::iterator f=_keyMap.find(keyName);
	if(f==_keyMap.end())
		return false;

	ShapeItem* item=f->second;
	item->_scale=scale;
	item->_bUseAbsolute=false;
	updateShapeScale(*item);
	return true;
}

bool HoopsShapeManager::setGlobalScale(float scale)
{
	if(!_checkShapeSize(scale))
		return false;

	if(scale!=_globalScale){
		_globalScale=scale;
		for(KeyMap::iterator b=_keyMap.begin();
			b!=_keyMap.end();++b){
				b->second->_bUseAbsolute=false;
				updateShapeScale(*(b->second));
		}
		return true;
	}
	return false;
}

bool HoopsShapeManager::setShapeAbsoluteDimension(const char* keyName,float size)
{
	if(!_checkShapeSize(size))
		return false;

	KeyMap::iterator f=_keyMap.find(keyName);
	if(f==_keyMap.end())
		return false;

	ShapeItem* item=f->second;
	item->_absoluteDemision=size;
	item->_bUseAbsolute=true;
	updateShapeScale(*item);
	return true;
}
bool HoopsShapeManager::setGlobalAbsoluteDimension(float size)
{
	if(size<=0||size>1e8){
		Console().Error("Shapes' global absolute demision is too small or too big.(size=%f)",size);
		return false;
	}

	for(KeyMap::iterator b=_keyMap.begin();
		b!=_keyMap.end();++b){
			b->second->_bUseAbsolute=true;
			b->second->_absoluteDemision=size;
			updateShapeScale(*(b->second));
	}
	return true;
}

void HoopsShapeManager::removeShape(const char* keyName)
{
	KeyMap::iterator f=_keyMap.find(keyName);
	if(f==_keyMap.end())
		return;
		
	HC_Delete_By_Key(f->second->_hcKey);
	delete f->second;
	_keyMap.erase(f);
}

void HoopsShapeManager::clear()
{
	for(KeyMap::iterator b=_keyMap.begin();
		b!=_keyMap.end();++b){
			HC_Delete_By_Key(b->second->_hcKey);
			delete b->second;
	}
	_keyMap.clear();
}
bool HoopsShapeManager::includeShape(const char* keyName)
{
	KeyMap::iterator f=_keyMap.find(keyName);
	if(f==_keyMap.end())
		return false;

	HC_Include_Segment_By_Key(f->second->_hcKey);
	return true;
}

bool HoopsShapeManager::importShape(const char* keyName)
{
	KeyMap::iterator f=_keyMap.find(keyName);
	if(f==_keyMap.end())
		return false;

	HC_Set_Line_Weight(_lineWidth);
	f->second->_shapeInsertionFun();
	return true;
}

bool HoopsShapeManager::importShape(const ShapeInput* input)
{
	KeyMap::iterator f=_keyMap.find(input->_keyName);
	if(f==_keyMap.end())
		return false;
	
	if(f->second->_shapeImportFun)
		f->second->_shapeImportFun(f->second->_shapePara,input);
	return true;
}


void HoopsShapeManager::reset()
{
	_current=_keyMap.begin();
}
ShapeItem* HoopsShapeManager::next()
{
	if(_current==_keyMap.end())
		return NULL;
	ShapeItem*re= _current->second;
	_current++;
	return re;
}

ShapeItem* HoopsShapeManager::getShapeItem(const char* keyName)
{
	reset();
	ShapeItem* item;
	while(item=next())
	{
		if(item->_keyName==keyName)
			return item;
	}
	return NULL;
}
void HoopsShapeManager::registerBuidinShapes()
{
	importSimpleShapesDef();
	importHoopsShapesDef();


}

