#pragma once

#include "coresps/coresps_global.h"
#include <osg/Quat>
#include <QLibrary>
#include <QString>


class CORESPS_EXPORT HoopsUltility
{
public:
	typedef double value_type;
	HoopsUltility(void);
	~HoopsUltility(void);

	static void setModelMatrix_Pos(value_type x,value_type y,value_type z);
	static void setModelMatrix_Pos(const osg::Vec3d& pos);
	static void appendModelMatrix_Pos(const osg::Vec3d& pos);
	static void setModelMatrix_Quat(const osg::Quat& quat );
	static void setModelMatrix_PosQuat(value_type x,value_type y,value_type z,
		value_type wx,value_type wy,value_type wz,value_type theta);

	static void setModelMatrix_PosQuat(const osg::Vec3d& pos, const osg::Quat& quat);
	static void setModelMatrix(const osg::Vec3f& pos,osg::Matrixf& quat);
	static void appendModelMatrix(const osg::Vec3f& pos,osg::Matrixf& quat);
	static void setModelMatrix_Scale(value_type x,value_type y,value_type z);


};

