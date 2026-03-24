#include "appearance.h"


using namespace std;

namespace INSIDES
{

AppearanceItem::VisibilityType AppearanceItem::getVisibilityType( VisibilityItem item )const
{
	return (VisibilityType)(_visibility[item*2+1]?3:0+
		_visibility[item*2]?1:0);
}


void AppearanceItem::setVisibilityType( VisibilityItem item,VisibilityType type )
{
	bool bit2=(type&2)!=0;
	bool bit1=(type&1)!=0;
	_visibility[item*2]=bit1;
	_visibility[item*2+1]=bit2;
}

bool AppearanceItem::isVisibilityUndefined()const
{
	return !_visibility.any();
}

bool AppearanceItem::isVisibilityAll()const
{
	return _visibility.all();
}

const char* AppearanceItem::getVisibilityHoopsKey( VisibilityItem item )
{
	switch(item)
	{
	case Line:
		return "lines";
	case Edge:
		return "edges";
	case Face:
		return "faces";
	case Marker:
		return "markers";
	case Shadow:
		return "shadows";
	case Text:
		return "text";
	case Lighting:
		return "lights";
	case Vertex:
		return "vertices";
	default:
		return "Error";
		
	};
}

void AppearanceItem::setVisibilitAll()
{
	//_visibility.set();
	setVisibilityType(Line,Visual);
	setVisibilityType(Face,Visual);
	setVisibilityType(Lighting,Visual);
}

void AppearanceItem::setVisibilityUndefined()
{
	_visibility.reset();
}

void AppearanceItem::setVisibilityAllHide()
{
	for(int i=0;i<Count;++i)
	{
		setVisibilityType((VisibilityItem)i,Invisual);
	}
}

void AppearanceItem::setColor( ColorItem item,float r,float g,float b )
{
	int ir=r*255;
	int ig=g*255;
	int ib=b*255;
	_colors[item].setRed(ir);
	_colors[item].setGreen(ig);
	_colors[item].setBlue(ib);
}

QColor AppearanceItem::nextBuildinColor()
{
	static float float_colors[] ={
		0, 0.333333f, 1,
			0.706f,0.706f,0.706f,
			0.6235f,0.58f,0.1137f,
			0, 0.666667f, 1,
			0,1,1,   
			0, 1,  0.666667f, 
			0, 1, 0.333333f,
			0,1,0,   
			0.333333f, 1, 0, 
			0.666667f, 1, 0,
			1,1,0,
			1, 0.666667f, 0,  
			1, 0.333333f, 0,
			1,0,0
	};

	static int int_colors[]={
		0,128,255,
		255,0,0,
		0,255,0,

		255,245,224,
		250,206,157,
		73,188,189,

		213,234,218,
		223,166,78,
		139,80,0,

		231,113,8,       
		148,203,231,
		0,147,197,

		243,168,187,
		255,233,169,
		247,185,120,

		238,197,220,
		246,240,204,
		186,212,239,

		188,225,223,
		255,245,224,
		250,206,157
	};

	static int id=0;
	static int size=21;
	int c=id;
	id=(id+1)%size;
	//return QColor(float_colors[c*3]*255,float_colors[c*3+1]*255,float_colors[c*3+2]*255);
	return QColor(int_colors[c*3],int_colors[c*3+1],int_colors[c*3+2]);
}

void AppearanceItem::DeepCopy( AppearanceItem& dst,const AppearanceItem& src )const
{
	dst._visibility=src._visibility;
	dst._colorUsed=src._colorUsed;
	for(int i=0;i<Color_Count;++i)
		dst._colors[i]=src._colors[i];
	dst._hcKey=-1;
	dst._hcSubKeys[0]=-1;
	dst._hcSubKeys[1]=-1;
	dst._hcSubKeys[2]=-1;
	dst._transparency=src._transparency;
	dst._showVelocity=src._showVelocity;
}

void AppearanceItem::setUseColorAll( bool b )
{
	setUseColor(Color_Point,b);
	setUseColor(Color_Face,b);
	setUseColor(Color_Edge,b);
	setUseColor(Color_Line,b);
}

void AppearanceItem::setColorAll( const QColor& color )
{
	setColor(Color_Point,color);
	setColor(Color_Face,color);
	setColor(Color_Edge,color);
	setColor(Color_Line,color);
}

void AppearanceItem::setColorAll( float r,float g,float b )
{
	setColor(Color_Point,r,g,b);
	setColor(Color_Face,r,g,b);
	setColor(Color_Edge,r,g,b);
	setColor(Color_Line,r,g,b);
}

AppearanceItem* AppearanceItem::clone() const
{
	AppearanceItem* item=new AppearanceItem(*this);
	return item;
}

QDataStream& operator<< (QDataStream& out,const AppearanceItem& item)
{
	// 可见性
	AppearanceItem::VBitSet v=item._visibility;
	//v.set();
	quint32 a=v.to_ulong();
	out<<a;

	// 颜色
	out<<(quint32)item._colorUsed.to_ullong();
	out<<item._colors[0];
	out<<item._colors[1];
	out<<item._colors[2];
	out<<item._colors[3];

	return out;
}
QDataStream& operator>> (QDataStream& in,AppearanceItem& item)
{
	quint32 a;
	in>>a;
	item._visibility=AppearanceItem::VBitSet(long(a));

	// 颜色
	in>>a;
	item._colorUsed=AppearanceItem::CBitSet(long(a));
	in>>item._colors[0];
	in>>item._colors[1];
	in>>item._colors[2];
	in>>item._colors[3];

	return in;
}

}	// end namespace INSIDES