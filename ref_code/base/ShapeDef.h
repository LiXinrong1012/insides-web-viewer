#ifndef POWER_PLOT_BASE_SHAPE_DEF_H_
#define  POWER_PLOT_BASE_SHAPE_DEF_H_


/**
*	This file is used to build the basic classes and structures that 
*	are needed to create a framework of Shapes.
*	/author	Jerry He (hejw06@gmail.com)
*	/date	Oct, 2011
*/

#include <vector>
#include <string>
using namespace std;

namespace Base
{
	const float Invalid_Float_Value=-1e10;

	struct ShapePara
	{
		typedef float ValueType;

		/// 最大可以设置3个字符串属性值
		/// 最大可以设置10个float型属性值
		enum Size{MAX_STRING_COUNT=3,MAX_VALUE_COUNT=10};

		///	float型属性值
		ValueType	values[MAX_VALUE_COUNT];
		/// 针对这些float型属性值的描述
		string		discription[MAX_VALUE_COUNT];

		/// 字符串型属性值
		string _str[MAX_STRING_COUNT];

		ShapePara(){
			for(int i=0;i<MAX_VALUE_COUNT;++i){
				discription[i]="brief discription";
				values[i]=Invalid_Float_Value;
			}
		}
	};

	/**
	*	Shape input parameters.
	*/
	struct ShapeInput
	{
		string _keyName;
		typedef float ValueType;
		typedef vector<ValueType> DataVec;

		DataVec _paras;

		ShapeInput(){};
		ShapeInput(const char* keyName):_keyName(keyName){};
		ShapeInput(const string& keyName):_keyName(keyName){};
		ShapeInput(const char* keyName,const DataVec& vec):_keyName(keyName),_paras(vec){}
		ShapeInput(const string& keyName,const DataVec& vec):_keyName(keyName),_paras(vec){}
		bool isNull(){return _keyName.empty();}
	};


	typedef void (*ShapeInsertionFun)(void);
	typedef void (*ShapeImportFun)(const ShapePara* para,const ShapeInput* input);
}


#endif