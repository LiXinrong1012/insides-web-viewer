#ifndef PP_SPS_SHAPE_MANAGER_H_
#define PP_SPS_SHAPE_MANAGER_H_

#include "coresps/coresps_global2.h"
#include "Base/ShapeDef.h"

using namespace Base;

#ifndef HC_POINTER_SIZED_INT
#if defined(_M_IA64) || defined(_M_AMD64) || defined(WIN64) || defined(_WIN64) || defined(_M_X64)
#   define  HC_POINTER_SIZED_INT    __int64
#else
#   define  HC_POINTER_SIZED_INT    long
#endif
#endif


#ifndef HC_KEY
#   define  HC_KEY      HC_POINTER_SIZED_INT
#endif

class DrawTool;

class ShapeItem
{
public:
	ShapeItem(const string& keyName):_keyName(keyName),_hcKey(-1L),
		_shapeImportFun(NULL),_shapeInsertionFun(NULL),_scale(1.0f),_absoluteDemision(1.0),
		_bUseAbsolute(false),_shapePara(NULL){}
	ShapeItem(const string& keyName,ShapeInsertionFun fun):_keyName(keyName),_hcKey(-1L),
		_shapeImportFun(NULL),_shapeInsertionFun(fun),_scale(1.0f),_absoluteDemision(1.0),
		_bUseAbsolute(false),_shapePara(NULL){}
	~ShapeItem(){}

	string _keyName;
	HC_KEY _hcKey;
	ShapeInsertionFun _shapeInsertionFun;
	ShapeImportFun _shapeImportFun;
	float _scale;
	float _absoluteDemision;
	bool _bUseAbsolute;

	ShapePara* _shapePara;
};


class CORESPS_EXPORT ShapeManager
{
public:
	virtual ~ShapeManager(){}
	/*! insert a shape with its drawing function.*/
	virtual void insertShape(const char* keyName,ShapeInsertionFun fun)=0;

	/*! insert a shape with a complex importing function.*/
	virtual void insertShape(const char* keyName,const ShapePara* para,ShapeImportFun fun)=0;
	
	/*! remove a shape by its keyword.*/
	virtual void removeShape(const char* keyName)=0;

	/*! remove all shapes.*/
	virtual void clear()=0;

	/*! include a shape*/
	virtual bool includeShape(const char* keyName)=0;

	/*! import this shape's drawing code*/
	virtual bool importShape(const char* keyName)=0;

	virtual bool importShape(const ShapeInput* shapeInput)=0;

	/*! set a shape's drawing scale.*/
	virtual bool setShapeScale(const char* keyName,float scale)=0;

	/*! set all shapes' drawing scale.*/
	virtual bool setGlobalScale(float scale)=0;

	virtual void setDrawTool(DrawTool* tool)=0;
	virtual DrawTool* getDrawTool()=0;

	/*!	Reset.*/
	virtual void reset()=0;
	/*! Get the next traversal item. If it's to the end, next()==NULL. */
	virtual ShapeItem* next()=0;

	virtual ShapeItem* getShapeItem(const char* keyName)=0;


	static ShapeManager* instance();
};

CORESPS_EXPORT void register_all_buildin_shapes();

#endif