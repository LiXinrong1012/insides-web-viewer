#pragma  once

#include "precore/precore_global.h"
#include "base/data_type_def.h"

#include <bitset>
#include <QDataStream>
#include <QColor>

namespace INSIDES
{

class BaseItem;
typedef quintptr JHC_KEY;
typedef quintptr JKEY;


/*!
*	常规显示属性，并负责关联Data和View
*	@author Jerry He
*	@date 2014.3.6
*/
class PRECORE_EXPORT AppearanceItem
{
public:
	enum VisibilityItem{Line=0,Edge,Face,Marker,Shadow,Text,Lighting,Vertex,Count};
	enum ColorItem{Color_Point=0,Color_Edge,Color_Face,Color_Line,Color_Count};
	enum {VisualAll=0xFFFF};
	enum VisibilityType{Undefined=0,Invisual=1,Visual=3};

	static const char* getVisibilityHoopsKey(VisibilityItem item);

	AppearanceItem()
		:_item(NULL),_hcKey(-1),_visibility(0),
		_colorUsed(0)
		,_transparency(0)
		,_showVelocity(false)
	{
		_hcSubKeys[0]=-1;
		_hcSubKeys[1]=-1;
		_hcSubKeys[2]=-1;
	}

	AppearanceItem(BaseItem* item,JHC_KEY key)
		:_item(item),_hcKey(key),_visibility(0)
		,_colorUsed(0)
		,_transparency(0)
		,_showVelocity(false)
	{
		_hcSubKeys[0]=-1;
		_hcSubKeys[1]=-1;
		_hcSubKeys[2]=-1;
	}

	AppearanceItem(const AppearanceItem& app){
		DeepCopy(*this,app);
	}

	AppearanceItem& operator=(const AppearanceItem& app)
	{
		DeepCopy(*this,app);
		return *this;
	}


	virtual AppearanceItem* clone()const;

	virtual ~AppearanceItem(){}

	BaseItem* getBaseItem(){return _item;}
	void setBaseItem(BaseItem* item){_item=item;}

	JHC_KEY getHCKey(){return _hcKey;}
	void setHCKey(JHC_KEY key){_hcKey=key;}


	// Visiblity
	VisibilityType getVisibilityType(VisibilityItem item)const;
	void setVisibilityType(VisibilityItem item,VisibilityType type);

	bool isVisibilityUndefined()const;
	bool isVisibilityAll()const;

	void setVisibilitAll();
	void setVisibilityUndefined();
	void setVisibilityAllHide();

	JHC_KEY getHCSubKey(int index){return _hcSubKeys[index];}
	void setHCSubKey(int index,JHC_KEY key){_hcSubKeys[index]=key;}

	// Colors
	void setUseColor(ColorItem item,bool b){_colorUsed[item]=b;}
	void setUseColorAll(bool b);
	bool getUseColor(ColorItem item)const{return _colorUsed[item];}
	const QColor& getColor(ColorItem item)const{return _colors[item];}
	void setColor(ColorItem item,const QColor& color){_colors[item]=color;}
	void setColorAll(const QColor& color);
	void setColor(ColorItem item,float r,float g,float b);
	void setColorAll(float r,float g,float b);

	static QColor nextBuildinColor();

	float getTransparency()const{return _transparency;}
	void setTransparency(float f){_transparency=f;}


	friend QDataStream& operator<< (QDataStream& out,const AppearanceItem& item);
	friend QDataStream& operator>> (QDataStream& in,AppearanceItem& item);

	bool	_showVelocity;

protected:
	void DeepCopy(AppearanceItem& dst,const AppearanceItem& src)const;

private:
	BaseItem*	_item;
	JHC_KEY		_hcKey;
	JKEY		_tmpKey1;
	JKEY		_tmpKey2;


	typedef std::bitset<16> VBitSet;
	typedef std::bitset<16> CBitSet;

	VBitSet		_visibility;
	CBitSet		_colorUsed;
	QColor		_colors[Color_Count];
	JHC_KEY		_hcSubKeys[3];		//储存柔性体的shell key或者其它需要储存的key。
	float		_transparency;

};

QDataStream& operator<< (QDataStream& out,const AppearanceItem& item);
QDataStream& operator>> (QDataStream& in,AppearanceItem& item);

} // end namespace INSIDES