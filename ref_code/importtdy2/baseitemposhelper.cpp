#include "BaseItemPosHelper.h"
#include <osg/Vec3f>
#include <osg/Matrixf>
#include <osg/Quat>
#include <osg/Matrix>
#include <QPair>
#include <QList>

#include "precore/DataExchangeAPI.h"
#include "precore/ParametersBaseItem.h"
#include "precore/BaseItemHelper.h"
#include "precore/precore_data.h"
#include "precore/IResultItem.h"

using namespace osg;

static void mul2Quaternions  (double* res, /*1*4*/ const double* th1, const double* th2 )
{
	/* multiply th1, and th2, the result is stored in res.
	Added by aslan.zhao@tsinghua.org.cn, @ May 27th, 2010.
	The physical meaning of this operation is rotate th1 first and th2 second.
	Note: this operation is not communicative.	*/

	res[0] = th1[0]*th2[0] - th1[1]*th2[1] - th1[2]*th2[2] - th1[3]*th2[3] ;
	res[1] = th1[0]*th2[1] + th1[1]*th2[0] + th1[2]*th2[3] - th1[3]*th2[2] ;
	res[2] = th1[0]*th2[2] - th1[1]*th2[3] + th1[2]*th2[0] + th1[3]*th2[1] ;
	res[3] = th1[0]*th2[3] + th1[1]*th2[2] - th1[2]*th2[1] + th1[3]*th2[0] ;
}

/// 返回四元数，格式为: w,v1,v2,v3
static void EulerAngleToEulerPara ( double* eulerpara, double* REULER, int first, int second, int third  )
{
	double para[3][4] ;
	double n[3] ;
	double val ;
	int idx[3] = { first, second, third } ;

	for  ( int i = 0; i < 3; i++ )
	{
		para[i][0] = cos(REULER[i]/2) ;
		val = sin(REULER[i]/2) ;

		switch ( idx[i] )
		{
		case 1 :
			n[0] = 1, n[1] = 0, n[2] = 0 ;
			break ;
		case 2:
			n[0] = 0, n[1] = 1, n[2] = 0 ;
			break ;
		case 3:
			n[0] = 0, n[1] = 0, n[2] = 1 ;
			break ;
		default:
			n[0] = 0, n[1] = 0, n[2] = 1 ;
			break ;
		}		

		for ( int j = 0; j < 3; j++ )
			para[i][1+j] = n[j] * val ; 
	}

	double temp1[4] ;
	mul2Quaternions(temp1, para[0], para[1]) ;
	mul2Quaternions(eulerpara, temp1, para[2]) ;
}


bool BaseItemPosHelper::getEuler_Axis( BaseItem* item,const QString& xlabel,
	const QString& ylabel,const QString& zlabel,Matrixf& matrix,TDYParameters* paras )
{
	osg::Vec3f vecX,vecY,vecZ;
	bool hasX=DataExchangeAPI::String2Vec<float>(paras,item->get(xlabel),vecX._v,3);
	bool hasY=DataExchangeAPI::String2Vec<float>(paras,item->get(ylabel),vecY._v,3);
	bool hasZ=DataExchangeAPI::String2Vec<float>(paras,item->get(zlabel),vecZ._v,3);

	if(hasX && hasY){
		vecX.normalize();
		vecY.normalize();
		vecZ=vecX^vecY;
	}
	else if(hasY &&hasZ){
		vecY.normalize();
		vecZ.normalize();
		vecX=vecY^vecZ;
	}
	else if(hasX && hasZ){
		vecX.normalize();
		vecZ.normalize();
		vecY=vecZ^vecX;
	}
	else
		return false;

	matrix.set(vecX.x(),vecX.y(),vecX.z(),0,
		vecY.x(),vecY.y(),vecY.z(),0,
		vecZ.x(),vecZ.y(),vecZ.z(),0,
		0,0,0,1);

	return true;
}

int BaseItemPosHelper::getPosition( BaseItem* item,osg::Vec3f& pos,ParametersBaseItem* parameterItem )
{
	bool hasGlobalPos=DataExchangeAPI::GetPositionFromItem(item,"QG",pos);
	if(hasGlobalPos)
		return 1;

	bool hasRelativePos=DataExchangeAPI::GetPositionFromItem(item,"QR",pos);
	if(hasRelativePos)
		return 2;
	return 0;
}

int BaseItemPosHelper::getInstancePosition( BaseItem* item,osg::Vec3f& pos,ParametersBaseItem* parameterItem )
{
	bool hasGlobalPos=DataExchangeAPI::GetPositionFromItem(item,"CENTER",pos);
	if(hasGlobalPos)
		return 1;
	return 0;
}

static void findItemProperties(BaseItem* item, QString keys[],int size,QList<QPair<QString,QString> > & itemAttitudes)
{
	for(int i=0;i<size;++i){
		QString a=item->get(keys[i]);
		if(!a.isEmpty())
			itemAttitudes.push_back(qMakePair(keys[i],a));
	}
}

/// 0:	no information
/// 1:	has information
/// 2:	has axis information
static int getAttitude_Euler(BaseItem* item, osg::Matrixf& matrix,QString attitudes[],int size,ParametersBaseItem* parameterItem)
{
	const TDYParameters* tdyParameters=parameterItem? parameterItem->getParameters():NULL;
	QList<QPair<QString,QString> > itemAttitudes;
	findItemProperties(item,attitudes,size,itemAttitudes);
	if(itemAttitudes.size()==0)
		return 0;
	if(itemAttitudes.size()>1)
		return 2;

	// has global attitude

	// return 0:  成功获得姿态A
	// return 1:  获得姿态错误
	static double eulerpara[4];
	eulerpara[0] = 1 ;	eulerpara[1] = 0 ;
	eulerpara[2] = 0 ;	eulerpara[3] = 0 ;

	QString euler  = itemAttitudes[0].first;
	QString eulerValue=itemAttitudes[0].second;

	int startpos = 0 ;
	if ( euler[0] == 'O' )
		startpos = 1 ;

	if(euler.indexOf("THETA")!=-1)
	{
		DataExchangeAPI::String2Vec(tdyParameters,eulerValue,eulerpara,4);
		Quat quat(eulerpara[1],eulerpara[2],eulerpara[3],eulerpara[0]);
		matrix.setRotate(quat);
		return 1;
	}
	else if (euler.indexOf("PHI") != -1 )
	{
		double phi[3] ;
		DataExchangeAPI::String2Vec(tdyParameters,eulerValue,phi,3);
		Quat quat;
		BaseItemPosHelper::Phi2Quat(phi,quat);
		matrix.setRotate(quat);
		return 1;
	}
	else
	{
		QString orders = euler.mid(startpos+5,3) ;
		int intorders=orders.toInt();

		int order[3] = { 0, 0, 0 };
		for ( int i = 0; i < 3; i++ )
		{
			order[2-i] = intorders%10 ;
			intorders /= 10 ;
		}

		Base::Console().Log("%d %d %d",order[0],order[1],order[2]);
		double values[3] ;
		DataExchangeAPI::String2Vec(tdyParameters,eulerValue,values,3);
		EulerAngleToEulerPara ( eulerpara, values, order[0], order[1], order[2] ) ;
		Quat quat(eulerpara[1],eulerpara[2],eulerpara[3],eulerpara[0]);
		matrix.setRotate(quat);
		return 1;
	}	

	return 0 ;
}

int BaseItemPosHelper::getAttitude( BaseItem* item,osg::Matrixf& matrix,ParametersBaseItem* parameterItem )
{
	TDYParameters* tdyParas=parameterItem? (TDYParameters*)parameterItem->getParameters():NULL;
	static QString globalAttitudes[] = { "THETAG", "PHIG"
		, "EULER321G", "EULER323G", "EULER313G", "EULER312G" 
		, "EULER212G", "EULER213G", "EULER231G", "EULER232G"
		, "EULER123G", "EULER121G", "EULER131G", "EULER132G" } ;
	static QString 	relativeAttitudes[] = { "THETAR", "PHIR"
		, "EULER321R", "EULER323R", "EULER313R", "EULER312R" 
		, "EULER212R", "EULER213R", "EULER231R", "EULER232R"
		, "EULER123R", "EULER121R", "EULER131R", "EULER132R" } ;
	static int attitudesSize=14;


	int findGlobalPosition=getAttitude_Euler(item,matrix,globalAttitudes,attitudesSize,parameterItem);
	if(findGlobalPosition==1)
		return 1;
	if(findGlobalPosition==0){
		int findRelativePosition=getAttitude_Euler(item,matrix,relativeAttitudes,attitudesSize,parameterItem);
		if(findRelativePosition==1)
			return 2;
	}

	if(getEuler_Axis(item,"XR","YR","ZR",matrix,tdyParas))
		return 2;

	if(getEuler_Axis(item,"XG","YG","ZG",matrix,tdyParas))
		return 1;

	return 0;
}

int BaseItemPosHelper::getInstanceAttitude( BaseItem* item,osg::Matrixf& matrix,ParametersBaseItem* parameterItem )
{
	TDYParameters* tdyParas=parameterItem? (TDYParameters*)parameterItem->getParameters():NULL;

	static QString globalAttitudes[] = { "THETA", "PHI"
		, "EULER321", "EULER323", "EULER313", "EULER312" 
		, "EULER212", "EULER213", "EULER231", "EULER232"
		, "EULER123", "EULER121", "EULER131", "EULER132" } ;
	static int attitudesSize=14;

	int findGlobalPosition=getAttitude_Euler(item,matrix,globalAttitudes,attitudesSize,parameterItem);

	if(findGlobalPosition==1)
		return 1;

	if(getEuler_Axis(item,"XAXIS","YAXIS","ZAXIS",matrix,tdyParas))
		return 1;

	return 0;
}

void BaseItemPosHelper::Phi2Quat(const double* a,Quat& quat )
{
	Vec3d phi(a[0],a[1],a[2]);
	double l=phi.length();
	if(l<1e-5){
		quat=Quat();
		return;
	}
		
	phi.normalize();
	float s=sin(l/2),c=cos(l/2);
	quat.set(phi.x()*s,phi.y()*s,phi.z()*s,c);
}

void BaseItemPosHelper::getInstance( BaseItem* instanceItem,osg::Matrixf& ff,ParametersBaseItem* parameterItem )
{
	Vec3f pos;
	Matrixf matrix;

	int hasPos=BaseItemPosHelper::getInstancePosition(instanceItem,pos,parameterItem);
	int hasAttitude=BaseItemPosHelper::getInstanceAttitude(instanceItem,matrix,parameterItem);

	if(hasPos)
		ff.setTrans(pos);
	
	if(hasAttitude)
		ff.preMult(matrix);
}

void BaseItemPosHelper::updateInstance( BaseItem* instanceItem )
 {
	ParametersBaseItem* parameterItem=BaseItemHelper::getRelatedParameters(instanceItem);
	Matrixf matrix;
	getInstance(instanceItem,matrix,parameterItem);
	instanceItem->setMatrix(&matrix);
}

QString osgMatrix2PosString(osg::Matrixf& matrix)
{
	QString res;
	for(int j=0;j<3;++j)
		res+=QString("%1 ,").arg(matrix(3,j));

	return res;
}

QString osgMatrix2RelativeString(osg::Matrixf& matrix,int xyz)
{
	QString res;
	for(int j=0;j<3;++j)
		res+=QString("%1 ,").arg(matrix(j,xyz));

	return res;
}

void BaseItemPosHelper::updateMarker( BaseItem* markerItem )
{
	ParametersBaseItem* parameterItem=BaseItemHelper::getRelatedParameters(markerItem);
	Matrixf matrix;
	getMarker(markerItem,matrix,parameterItem);
	markerItem->setMatrix(&matrix);
}

void BaseItemPosHelper::getMarker( BaseItem* marker,Matrixf& matrix,ParametersBaseItem* parameterItem)
{
	BaseItem* parent=marker->getParent();
	int cate=parent->getCategory();

	if(cate==TDY_PRE_CATE_RIGIDPART){
		getRigidMarker(marker,matrix,parameterItem);
		return;
	}
	
	getBaseItem(marker,matrix,parameterItem);
}

void BaseItemPosHelper::getBaseItem( BaseItem* item,osg::Matrixf& matrix,ParametersBaseItem* parameterItem )
{
	Vec3f pos;
	Matrixf quat;
	int hasPos=BaseItemPosHelper::getPosition(item,pos,parameterItem);
	int hasAttitude=BaseItemPosHelper::getAttitude(item,quat,parameterItem);

	if(hasPos!=0)
		matrix.preMultTranslate(pos);

	if(hasAttitude!=0)
		matrix=quat*matrix;
}

void BaseItemPosHelper::updateGraphic( BaseItem* graphicsItem ,float scale)
{
	QString hasCM=graphicsItem->get("CM");
	if(hasCM.isEmpty())
		return;

	BaseItem* parent=graphicsItem->getParent();
	BaseItem* cm=parent->child(hasCM);
	if(!cm){
		Base::Console().Warning("Failed to find CM = %s",hasCM.toStdString().c_str());
		return;
	}

	ParametersBaseItem* parameterItem=BaseItemHelper::getRelatedParameters(cm);
	Matrixf matrix;
	BaseItemPosHelper::getMarker(cm,matrix,parameterItem);
	if(scale!=1.0)
		matrix.preMultScale(Vec3f(scale,scale,scale));

	graphicsItem->setMatrix(&matrix);
}

//void BaseItemPosHelper::getRigidMarker( BaseItem* marker,osg::Matrixf& matrix,ParametersBaseItem* parameterItem )
//{
//	//if(marker->getKeyName()=="QIU_M")
//	//{
//	//	int i;
//	//	i++;
//	//}
//	QString hasRM=marker->get("RM");
//	if(!hasRM.isEmpty()){
//		BaseItem* parent=marker->getParent();
//		BaseItem* cm=parent->child(hasRM);
//		if(!cm){
//			Base::Console().Warning("Failed to find RM = %s",hasRM.toStdString().c_str());
//		}
//		else
//			getRigidMarker(cm,matrix,parameterItem);
//	}
//
//	Vec3f pos;
//	Matrixf quat;
//	int hasPos=BaseItemPosHelper::getPosition(marker,pos,parameterItem);
//	int hasAttitude=BaseItemPosHelper::getAttitude(marker,quat,parameterItem);
//
//	if(hasRM.isEmpty() && (hasPos==2 || hasAttitude ==2) ){
//		Matrixf B;
//		getBaseItem(marker->getParent(),B,parameterItem);
//		matrix.preMult(B);
//	}
//
//	if(hasPos!=0)
//		matrix.preMultTranslate(pos);
//
//	if(hasAttitude!=0)
//		matrix.preMult(quat);
//}

void BaseItemPosHelper::getRigidMarker2( BaseItem* marker,osg::Matrixf& matrix,ParametersBaseItem* parameterItem )
{
	QString hasRM=marker->get("RM");
	if(!hasRM.isEmpty()){
		BaseItem* parent=marker->getParent();
		BaseItem* cm=parent->child(hasRM);
		if(!cm)
			Base::Console().Warning("Failed to find RM = %s",hasRM.toStdString().c_str());
		else{
			getRigidMarker2(cm,matrix,parameterItem);
			Vec3f pos;
			Matrixf quat;
			int hasPos=BaseItemPosHelper::getPosition(marker,pos,parameterItem);
			int hasAttitude=BaseItemPosHelper::getAttitude(marker,quat,parameterItem);

			if(hasPos!=0)
				matrix.preMultTranslate(pos);

			if(hasAttitude!=0)
				matrix.preMult(quat);
		}
		return;
	}

	Vec3f pos;
	Matrixf quat;
	int hasPos=BaseItemPosHelper::getPosition(marker,pos,parameterItem);
	int hasAttitude=BaseItemPosHelper::getAttitude(marker,quat,parameterItem);


	// Case 1: 两者都是全局的，进行逆转换到相对坐标系
	if((hasPos==1 && hasAttitude ==1)){
		Matrixf AB;
		if(hasPos!=0)
			AB.preMultTranslate(pos);

		if(hasAttitude!=0)
			AB.preMult(quat);

		Matrixf B;
		getBaseItem(marker->getParent(),B,parameterItem);
		Matrixf BInvert;
		BInvert=Matrixf::inverse(B);
		AB.postMult(BInvert);
		matrix.preMult(AB);
	}
	else if(hasPos==2 && hasAttitude==2 )
	{
		matrix.preMultTranslate(pos);
		matrix.preMult(quat);
	}
	else if(hasPos==1 && hasAttitude==2)
	{
		Matrixf B;
		getBaseItem(marker->getParent(),B,parameterItem);
		Matrixf BInvert;
		BInvert=Matrixf::inverse(B);
		Vec4f vx(pos._v[0],pos._v[1],pos._v[2],1);
		Vec4f g2=BInvert.postMult(vx);

		quat(3,0)=g2._v[0];
		quat(3,1)=g2._v[1];
		quat(3,2)=g2._v[2];
		matrix.preMult(quat);
	}
	else if(hasPos==2 && hasAttitude==1)
	{
		Matrixf r1;
		getAttitude(marker->getParent(),r1,parameterItem);
		Matrixf M1=quat*Matrixf::inverse(r1);
		M1(3,0)=pos._v[0];
		M1(3,1)=pos._v[1];
		M1(3,2)=pos._v[2];
	}
}

void BaseItemPosHelper::getInstanceRigid( BaseItem* rigidItem,osg::Matrixf& ff,ParametersBaseItem*  parameterItem)
{
	Vec3f pos;
	Matrixf matrix;

	int hasPos=BaseItemPosHelper::getInstancePosition(rigidItem,pos,parameterItem);
	int hasAttitude=BaseItemPosHelper::getInstanceAttitude(rigidItem,matrix,parameterItem);

	if(hasPos)
		ff.preMultTranslate(pos);

	if(hasAttitude)
		ff.preMult(matrix);

	getBaseItem(rigidItem,ff,parameterItem);
}

void BaseItemPosHelper::updateInstanceRigid( BaseItem* instanceItem )
{
	ParametersBaseItem* parameterItem=BaseItemHelper::getRelatedParameters(instanceItem);
	Matrixf matrix;
	getInstanceRigid(instanceItem,matrix,parameterItem);
	instanceItem->setMatrix(&matrix);
}

void BaseItemPosHelper::getRigidMarker( BaseItem* marker,osg::Matrixf& matrix,ParametersBaseItem* parameterItem )
{
	QString hasRM=marker->get("RM");
	if(!hasRM.isEmpty()){
		BaseItem* parent=marker->getParent();
		BaseItem* cm=parent->child(hasRM);
		if(!cm)
			Base::Console().Warning("Failed to find RM = %s",hasRM.toStdString().c_str());
		else{
			getRigidMarker(cm,matrix,parameterItem);
			Vec3f pos;
			Matrixf quat;
			int hasPos=BaseItemPosHelper::getPosition(marker,pos,parameterItem);
			int hasAttitude=BaseItemPosHelper::getAttitude(marker,quat,parameterItem);

			if(hasPos!=0)
				matrix.preMultTranslate(pos);

			if(hasAttitude!=0)
				matrix.preMult(quat);
		}
		return;
	}

	// get defined position and attitude
	
	Vec3f posDef;
	Matrixf attitudeDef;
	int hasPos=BaseItemPosHelper::getPosition(marker,posDef,parameterItem);
	int hasAttitude=BaseItemPosHelper::getAttitude(marker,attitudeDef,parameterItem);

	if ( hasPos == 0 || hasAttitude == 0 )
	{
		Base::Console().Warning("Both position and attitude should be defined on markers.");
		return;
	}

	Matrixf MassCenterMatrix ;
	getBaseItem(marker->getParent(),MassCenterMatrix,parameterItem);
    Vec4f relpos(posDef._v[0], posDef._v[1], posDef._v[2], 1.0) ;
	
	if ( hasPos == 1 )
	{
		for ( int i = 0; i < 3; i++ )
			relpos._v[i] -= MassCenterMatrix(3,i) ;
		relpos = MassCenterMatrix.postMult(relpos) ;
	}

	// attitude should be handled at the second step
	if ( hasAttitude == 1 )
	{
		MassCenterMatrix(3,0) = 0 ;	MassCenterMatrix(3,1) = 0 ;	MassCenterMatrix(3,2) = 0 ;
		attitudeDef.postMult(Matrixf::inverse(MassCenterMatrix)) ;
	}

	attitudeDef(3,0) = relpos._v[0] ;
	attitudeDef(3,1) = relpos._v[1] ;
	attitudeDef(3,2) = relpos._v[2] ;
	matrix.preMult(attitudeDef);
}

void BaseItemPosHelper::getGeneralItem( BaseItem* item,osg::Matrixf& matrix,ParametersBaseItem* parameterItem )
{
	if(item->isInstance())
	{
		if(item->getCategory()==TDY_PRE_CATE_RIGIDPART){
			getInstanceRigid(item,matrix,parameterItem);
			return;
		}
		getInstance(item,matrix,parameterItem);
		return;
	}
	if(item->getCategory()==TDY_PRE_CATE_MARKER)
		return getMarker(item,matrix,parameterItem);
}

void BaseItemPosHelper::getGeneralItemOnOne( BaseItem* item,osg::Matrixf& matrix, BaseItem* onOneItem )
{
	QVector<BaseItem*> itemlist;
	BaseItem* tmp=item;
	while(onOneItem!=tmp){
		itemlist.push_back(tmp);
		tmp=tmp->getParent();
	}

	for(int i=itemlist.size()-1;i>=0;--i){
		BaseItem* tmpItem=itemlist[i];
		ParametersBaseItem* parameterItem=BaseItemHelper::getRelatedParameters(tmpItem);
		getGeneralItem(tmpItem,matrix,parameterItem);
	}
}

void BaseItemPosHelper::getResultRigid( IResultItem* item,osg::Matrixf& matrix )
{
	double* a=item->getData(0,0);

	osg::Quat quat;
	BaseItemPosHelper::Phi2Quat(&a[3],quat);
	Vec3d pos(a[0],a[1],a[2]);

	matrix.preMultTranslate(pos);
	matrix.preMultRotate(quat);
}

