#include "DataExchangeAPI.h"
#include <QtCore>
#include "precore_data.h"
#include "itemlist.h"
#include "precore/modeldocument.h"
#include "precore/BaseItemHelper.h"

using namespace osg;
using namespace std;


namespace INSIDES
{


bool DataExchangeAPI::String2FloatVec( const QString& str, std::vector<float>& vec )
{
	QStringList strVec=str.split(",");
	int n=strVec.size();
	for(int i=0;i<n;++i)
	{
		float x=strVec[i].toFloat();
		vec.push_back(x);
	}
	return true;
}

bool DataExchangeAPI::GetPositionFromItem(BaseItem* item,const QString& vecKey,osg::Vec3d& vec )
{
	const TDYParameters* paras=getRelatedParameters(item);
	return String2Vec<double>(paras,item->get(vecKey),vec._v,3);
}
bool DataExchangeAPI::GetPositionFromItem( BaseItem* item,const QString& vecKey,osg::Vec3f& vec )
{
	const TDYParameters* paras=getRelatedParameters(item);
	return String2Vec<float>(paras,item->get(vecKey),vec._v,3);
}



const TDYParameters* DataExchangeAPI::getRelatedParameters( BaseItem* item )
{
	ParametersBaseItem* pItem=BaseItemHelper::getRelatedParameters(item);
	if(pItem)
		return pItem->getParameters();
	return NULL;
}

bool DataExchangeAPI::PString2Vec3( BaseItem* item,const QString& str,osg::Vec3d& vec3 )
{
	const TDYParameters* paras=getRelatedParameters(item);
	if(!paras)
		return String2Vec3(str,vec3);

	QStringList strVec=str.split(",");
	double x=paras->getValue(strVec[0]);
	double y=paras->getValue(strVec[1]);
	double z=paras->getValue(strVec[2]);
	vec3.set(x,y,z);
	return true;
}

bool DataExchangeAPI::PString2Vec3( BaseItem* item,const QString& str,osg::Vec3f& vec3 )
{
	const TDYParameters* paras=getRelatedParameters(item);
	if(!paras)
		return String2Vec3(str,vec3);

	QStringList strVec=str.split(",");
	double x=paras->getValue(strVec[0]);
	double y=paras->getValue(strVec[1]);
	double z=paras->getValue(strVec[2]);
	vec3.set(x,y,z);
	return true;
}

bool DataExchangeAPI::PString2FloatVec( BaseItem* item,const QString& str, std::vector<float>& vec )
{
	const TDYParameters* paras=getRelatedParameters(item);
	if(!paras)
		return String2FloatVec(str,vec);

	QStringList strVec=str.split(",");
	int n=strVec.size();
	for(int i=0;i<n;++i)
	{
		float x=paras->getValue(strVec[i]);
		vec.push_back(x);
	}
	return true;
}

QString _TDYName(BaseItem* item,const QString& post)
{
	if(item->getParent()==NULL)
		return post;
	if(item->getCategory()==TDY_PRE_CATE_FOLDER)
		return _TDYName(item->getParent(),post);
	if(item->getCategory()==TDY_PRE_CATE_GROUND)
		return post;

	if(post.isEmpty())
		return _TDYName(item->getParent(),item->getKeyName());
	else
		return _TDYName(item->getParent(),item->getKeyName()+"."+post);
}

QString DataExchangeAPI::fullName2TDYName( const QString& name )
{
	ModelDocument* doc=myDocument();
	BaseItem* item=doc->findItem(name);
	if(!item)
		return QString();

	return _TDYName(item,"");

}

}