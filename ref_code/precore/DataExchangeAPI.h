#pragma once

#include "precore/precore_global.h"
#include <QString>
#include <QStringList>
#include "base/Console.h"
#include <vector>
#include <cmath>
#include "osg/Vec3d"
#include "osg/Matrixf"

#include "pretdy/TDYParameters.h"
#include "precore/BaseItem.h"

using std::min;

namespace osg{
	class Vec3d;
	class Vec3f;
	class Quat;
	class Matrixf;
}
class TDYParameters;

namespace INSIDES
{

class BaseItem;
/*!
*	负责转换数据。
*	@author Jerry He
*	@date 2014.3.7
*/
class PRECORE_EXPORT DataExchangeAPI
{
public:
	// 返回不带Folder的名字
	static QString fullName2TDYName(const QString& name);

	static const TDYParameters* getRelatedParameters(BaseItem* item);

	template<class T>
	static bool String2Vec(const TDYParameters* paras,const QString& str,T* vec,int vecSize);

	static bool PString2Vec3(BaseItem* item,const QString& str,osg::Vec3d& vec3);
	static bool PString2Vec3(BaseItem* item,const QString& str,osg::Vec3f& vec3);
	static bool PString2FloatVec(BaseItem* item,const QString& str, std::vector<float>& vec);


	static bool String2Vec3(const QString& str,osg::Vec3d& vec3){return String2Vec<double>(NULL,str,vec3._v,3);}
	static bool String2Vec3(const QString& str,osg::Vec3f& vec3){return String2Vec<float>(NULL,str,vec3._v,3);}
	static bool String2Vec3(const QString& str,float* vec3){return String2Vec<float>(NULL,str,vec3,3);}
	static bool String2Vec3(const QString& str,double* vec3){return String2Vec<double>(NULL,str,vec3,3);}

	// deprecated
	static bool String2FloatVec(const QString& str, std::vector<float>& vec);


	static bool GetPositionFromItem(BaseItem* item,const QString& vecKey,osg::Vec3d& vec);
	static bool GetPositionFromItem(BaseItem* item,const QString& vecKey,osg::Vec3f& vec);


};


template<class T>
bool DataExchangeAPI::String2Vec(const TDYParameters* paras,const QString& str,T* vec,int vecSize )
{
	QStringList strVec=str.split(",",QString::SkipEmptyParts);
	int count=strVec.size();
	bool result=true;
	if(strVec.size()!=vecSize){
		//Base::Console().Warning("String (%s) is not the size supposed to be.",str.toStdString().c_str());
		count=vecSize>count?count:vecSize;
		result=false;
	}
	if(paras){
		for(int i=0;i<count;++i)
			vec[i]=paras->getValue(strVec[i]);
	}
	else{
		for(int i=0;i<count;++i)
			vec[i]=(T)strVec[i].toDouble();
	}
	return result;
}


}