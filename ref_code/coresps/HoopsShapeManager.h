#pragma once

#include "coresps/ShapeManager.h"
#include <vector>
#include <string>
#include <map>
using namespace std;


class CORESPS_EXPORT HoopsShapeManager :
	public ShapeManager
{
public:
	
	static HoopsShapeManager* instance();
	static void destruct();

	virtual void insertShape(const char* keyName,ShapeInsertionFun fun);
	virtual void insertShape(const char* keyName,const ShapePara* para,ShapeImportFun fun);
	virtual void removeShape(const char* keyName);
	virtual void clear();
	virtual bool includeShape(const char* keyName);

	virtual bool setShapeScale(const char* keyName, float scale);
	virtual bool setGlobalScale(float scale);
	virtual bool setShapeAbsoluteDimension(const char* kyeName,float size);
	virtual bool setGlobalAbsoluteDimension(float size);

	virtual bool importShape(const char* keyName);
	virtual bool importShape(const ShapeInput* input);
	virtual void setDrawTool(DrawTool* tool){_drawTool=tool;}
	virtual DrawTool* getDrawTool(){return _drawTool;}

	virtual void reset();
	virtual ShapeItem* next();

	virtual ShapeItem* getShapeItem(const char* keyName);


	/*!
	* Set an existed shape's static parameter.
	* @return Whether this function run succesfully.
	* @Note If this shape is not existed, return false.
	*/
	bool setStaticPara(const char* keyName,int index,ShapePara::ValueType value);
	bool setStaticPara(const char* keyName,int index,const std::string& str);

	void registerBuidinShapes();
protected:
//	typedef map<string,ShapeInsertionFun> String2InsertionMap;
//	typedef map<string,HC_KEY> String2HCKeyMap;
//	String2InsertionMap _insertionMap;
//	String2HCKeyMap _hcKeyMap;
	typedef map<string,ShapeItem*> KeyMap;
	KeyMap _keyMap;
	KeyMap::iterator _current;	//For items traversal.
	float _globalScale;
	string _rootDir;
	DrawTool* _drawTool;
	double _lineWidth;

	static HoopsShapeManager* _instance;
	HoopsShapeManager(void);
	virtual ~HoopsShapeManager(void);

	// functions.
	inline string getFullName(const char* keyName){return (_rootDir+"/")+keyName;}
	void updateShapeScale(const ShapeItem& item);
};
