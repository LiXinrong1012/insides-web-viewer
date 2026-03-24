#pragma once

#include "prev3d/prev3d_global.h"
#include <QString>

namespace INSIDES{
	class BaseItem;
	class ParametersBaseItem;
	class IResultItem; 
}

class TDYParameters;

using namespace INSIDES;

namespace osg
{
	class Vec3f;
	class Matrixf;
	class Quat;
}

/*!
*	This class is used to get item's position and rotation matrix.
*	@author Jerry He
*	@date	2014.4.10
*/
class PREV3D_EXPORT BaseItemPosHelper
{
public:

	static void Phi2Quat(const double* phi,osg::Quat& quat);

	/*!
	*	0:	No position
	*	1:	Set to global position
	*	2:	Set to relative position
	*/
	static int getPosition(BaseItem* item,osg::Vec3f& pos,ParametersBaseItem* parameterItem);

	/// get position at an instance item, return zero if there's no position information
	static int getInstancePosition(BaseItem* item,osg::Vec3f& pos,ParametersBaseItem* parameterItem);

	static int getAttitude(BaseItem* item,osg::Matrixf& quat,ParametersBaseItem* parameterItem);
	static int getInstanceAttitude(BaseItem* item,osg::Matrixf& quat,ParametersBaseItem* parameterItem);

	static bool getEuler_Axis( BaseItem* item,const QString& xlabel, const QString& ylabel,
		const QString& zlabel,osg::Matrixf& matrix,TDYParameters* paras );


	/// 得到基本的变换矩阵，不考虑相对和全局
	static void getBaseItem(BaseItem* item,osg::Matrixf& matrix,ParametersBaseItem* parameterItem);

	/// 得到此条目相关的变换矩阵
	static void getGeneralItem(BaseItem* item,osg::Matrixf& matrix,ParametersBaseItem* parameterItem);
	/// 得到此条目在onOneItem的坐标系中的变换矩阵
	static void getGeneralItemOnOne(BaseItem* item,osg::Matrixf& matrix, BaseItem* onOneItem);


	/// Instance position related
	static void getInstance(BaseItem* instanceItem,osg::Matrixf& matrix,ParametersBaseItem* parameterItem);
	static void getInstanceRigid(BaseItem* rigidItem,osg::Matrixf& matrix,ParametersBaseItem* parameterItem);
	static void updateInstance(BaseItem* instanceItem);
	static void updateInstanceRigid(BaseItem* instanceItem);

	/// Get the matrix under this marker.
	static void getMarker(BaseItem* marker,osg::Matrixf& matrix,ParametersBaseItem* parameterItem);

	static void getRigidMarker(BaseItem* marker,osg::Matrixf& matrix,ParametersBaseItem* parameterItem);

	/// deprecated
	static void getRigidMarker2(BaseItem* marker,osg::Matrixf& matrix,ParametersBaseItem* parameterItem);
	/// Update the marker's position in HOOPS
	static void updateMarker(BaseItem* markerItem);

	/// Update the graphics' position in HOOPS
	static void updateGraphic(BaseItem* graphicsItem,float scale=1.0);








	////////////////////////////////////////////////////////////////////////////////		
	////////////////////////////////////////////////////////////////////////////////		
	// Results related
	static void getResultRigid(IResultItem* item,osg::Matrixf& matrix);
};

