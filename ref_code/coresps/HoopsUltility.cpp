#include "HoopsUltility.h"
#include <osg/Matrixf>
#include "Base/Console.h"

using namespace osg;

HoopsUltility::HoopsUltility(void)
{
}

HoopsUltility::~HoopsUltility(void)
{
}


void HoopsUltility::setModelMatrix_Pos(double x,double y,double z)
{
	Matrixf f;
	f.makeTranslate(x,y,z);
	HC_Set_Modelling_Matrix(f.ptr());
}

void HoopsUltility::setModelMatrix_Pos( const osg::Vec3d& pos )
{
	Matrixf f;
	f.setTrans(pos);
	HC_Set_Modelling_Matrix(f.ptr());
}

void HoopsUltility::setModelMatrix_Scale(value_type x,value_type y,value_type z)
{
	Matrixf f;
	f.makeScale(x,y,z);
	HC_Set_Modelling_Matrix(f.ptr());
	//HC_Append_Modelling_Matrix(f.ptr());
}
//void HoopsUltility::setModelMatrix_Quat(const Quat& quat )
//{
//	Matrixf f;
//	f.makeTranslate(x,y,z);
//	HC_Set_Modelling_Matrix(f.ptr());
//}

void HoopsUltility::setModelMatrix_PosQuat(value_type x,value_type y,value_type z,
	value_type wx,value_type wy,value_type wz,value_type theta)
{
	Matrixf f;
	f.setRotate(Quat(wx,wy,wz,theta));
	//HC_Set_Modelling_Matrix(f.ptr());
	f.setTrans(x,y,z);
	//HC_Append_Modelling_Matrix(f.ptr());
	HC_Set_Modelling_Matrix(f.ptr());
}

void HoopsUltility::setModelMatrix_PosQuat(const osg::Vec3d& pos, const osg::Quat& quat)
{
	Matrixf f;
	f.setRotate(quat);
	//HC_Set_Modelling_Matrix(f.ptr());
	f.setTrans(pos);
	//HC_Append_Modelling_Matrix(f.ptr());
	HC_Set_Modelling_Matrix(f.ptr());
}

void HoopsUltility::setModelMatrix( const osg::Vec3f& pos,osg::Matrixf& quat )
{
	quat.setTrans(pos);
	HC_Set_Modelling_Matrix(quat.ptr());
}

void HoopsUltility::appendModelMatrix( const osg::Vec3f& pos,osg::Matrixf& quat )
{
	quat.setTrans(pos);
	HC_Append_Modelling_Matrix(quat.ptr());
}

void HoopsUltility::appendModelMatrix_Pos( const osg::Vec3d& pos )
{
	Matrixf f;
	f.setTrans(pos);
	HC_Append_Modelling_Matrix(f.ptr());
}

