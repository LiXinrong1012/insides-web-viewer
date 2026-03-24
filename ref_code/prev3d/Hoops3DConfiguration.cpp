#include "Hoops3DConfiguration.h"

#include "coresps/ShapeManager.h"
#include "coresps/HoopsShapeManager.h"

#include "base/AppConfiguration.h"
#include "base/Console.h"



QDataStream& operator << (QDataStream& fout,const Hoops3DConfiguration& config)
{
	fout <<	config._shellVertexSize;
	fout <<	config._shellEdgeSize;
	fout<<	config._showFEMMarker;
	fout<<	config._showConstraints;
	fout<<	config._showMassCenter;
	fout<<	config._massCenterSize;
	fout<<	config._markerSize;
	fout<<	config._constraintSize;
	fout<<	config._showInitial;
	fout<<	config._windowsTopColor;
	fout<<  config._windowsBottomColor;
	fout<<	config._forceScale;	//绘制力的比例
	fout<<	config._eigenDisplayScale;
	fout<<  config._velocityScale; //绘制速度的比例

	fout<<	config._showFEMNodeID;
	fout<<	config._FEMNodeIDSize;

	fout<<	config._showIMarker;
	fout<<	config._showJMarker;
	return fout;
}
QDataStream& operator >> (QDataStream& fin, Hoops3DConfiguration& config)
{
	fin >>	config._shellVertexSize;
	fin	>>	config._shellEdgeSize;
	fin	>>	config._showFEMMarker;
	fin	>>	config._showConstraints;
	fin	>>	config._showMassCenter;
	fin	>>	config._massCenterSize;
	fin	>>	config._markerSize;
	fin	>>	config._constraintSize;
	fin	>>	config._showInitial;
	fin	>>	config._windowsTopColor;
	fin	>>  config._windowsBottomColor;
	fin	>>	config._forceScale	;//绘制力的比例
	fin	>>	config._eigenDisplayScale;
	fin	>>  config._velocityScale; //绘制速度的比例

	fin	>>	config._showFEMNodeID;
	fin	>>	config._FEMNodeIDSize;

	fin	>>	config._showIMarker;
	fin	>>	config._showJMarker;
	return fin;
}
//////////////////////////////////////////////
///////////////////////////////////////////////

Hoops3DConfiguration::Hoops3DConfiguration(void)
	:_shellVertexSize(1)
	,_shellEdgeSize(3)
	,_showFEMMarker(false)
	,_showConstraints(true)
	,_showMassCenter(false)
	,_massCenterSize(1)
	,_markerSize(1)
	,_showInitial(false)
	,_constraintSize(1)
	,_windowsTopColor(QColor(0,0.501961*255,0.501961*255))
	,_windowsBottomColor(QColor(255,0.984314*255,0.941176*255))
	,_forceScale(1.0)
	,_eigenDisplayScale(1000)
	,_showFEMNodeID(false)
	,_FEMNodeIDSize(1)
	,_velocityScale(1)

	,_showIMarker(true)
	,_showJMarker(true)
{
	Base::AppConfiguration::instance()->getParametersManager()->attach(this);

	initCurrent(true);
	flushSize();
}


Hoops3DConfiguration::~Hoops3DConfiguration(void)
{
	Base::AppConfiguration::instance()->getParametersManager()->disattach(this);
}

Hoops3DConfiguration* Hoops3DConfiguration::instance()
{
	static Hoops3DConfiguration _instance;
	return &_instance;
}

bool Hoops3DConfiguration::parameterChanged( Base::ParametersGroup* parameterManager, 
	const Base::ParameterItem* newParameter,const Base::ParameterItem* oldParameter )
{
	QString fullName=parameterManager->getName()+"::"+newParameter->getKeyword();
	if(_keynameMap.find(fullName)!=_keynameMap.end()){
		initCurrent(false);

		//flushSize();
		return true;
	}

	return false;
}

void Hoops3DConfiguration::initCurrent(bool isInitial)
{
	if(isInitial){
		_keynameMap["Display::Shell vertex size"]="";
		_keynameMap["Display::Shell edge size"]="";
		_keynameMap["Display::Show FEM marker"]="";
		_keynameMap["Display::Show constraint"]="";
		_keynameMap["Display::Show mass center"]="";
		_keynameMap["Display::Mass center size"]="";
		_keynameMap["Display::Marker size"]="";
		_keynameMap["Display::Show initial"]="";
		_keynameMap["Display::Constraint size"]="";
		_keynameMap["Display::Window top color"]="";
		_keynameMap["Display::Window bottom color"]="";
		_keynameMap["Display::Force scale"]="";
		_keynameMap["Display::Velocity scale"]="";
		_keynameMap["Display::Eigen display scale"]="";
		_keynameMap["Display::Show FEM node id"]="";
		_keynameMap["Display::FEM node id size"]="";

	}
	initOneItem<double>("Display","Shell vertex size",QVariant::Double,&_shellVertexSize);
	initOneItem<double>("Display","Shell edge size",QVariant::Double,&_shellEdgeSize);
	initOneItem<bool>("Display","Show FEM marker",QVariant::Bool,&_showFEMMarker);
	initOneItem<bool>("Display","Show constraint",QVariant::Bool,&_showConstraints);
	initOneItem<bool>("Display","Show mass center",QVariant::Bool,&_showMassCenter);
	initOneItem<double>("Display","Mass center size",QVariant::Double,&_massCenterSize);
	initOneItem<double>("Display","Marker size",QVariant::Double,&_markerSize);
	initOneItem<bool>("Display","Show initial",QVariant::Bool,&_showInitial);
	initOneItem<double>("Display","Constraint size",QVariant::Double,&_constraintSize);
	initOneItem<QColor>("Display","Window top color",QVariant::Color,&_windowsTopColor);
	initOneItem<QColor>("Display","Window bottom color",QVariant::Color,&_windowsBottomColor);
	initOneItem<double>("Display","Force scale",QVariant::Double,&_forceScale);
	initOneItem<double>("Display","Velocity scale",QVariant::Double,&_velocityScale);
	initOneItem<double>("Display","Eigen display scale",QVariant::Double,&_eigenDisplayScale);

	/// tmp
	initOneItem<bool>("Display","ShowIMarker",QVariant::Bool,&_showIMarker);
	initOneItem<bool>("Display","ShowJMarker",QVariant::Bool,&_showJMarker);

	initOneItem<double>("Display","FEM node id size",QVariant::Double,&_FEMNodeIDSize);
	initOneItem<bool>("Display","Show FEM node id",QVariant::Bool,&_showFEMNodeID);
}

void Hoops3DConfiguration::flushSize()
{
	HoopsShapeManager::instance()->setGlobalAbsoluteDimension(_constraintSize);
	HoopsShapeManager::instance()->setShapeAbsoluteDimension("Marker",_markerSize);
}

//void Hoops3DConfiguration::setWindowsTopColor( const QColor& color )
//{
//	_windowsTopColor = color;
//	initOneItem<QColor>("Display","Window top color",QVariant::Color,&_windowsTopColor);
//}
//
//void Hoops3DConfiguration::setWindowsBottomColor( const QColor& color )
//{
//	_windowsBottomColor = color;
//	initOneItem<QColor>("Display","Window bottom color",QVariant::Color,&_windowsBottomColor);
//}
