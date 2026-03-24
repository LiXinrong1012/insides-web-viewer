#pragma once

#include "base/ParametersManager.h"
#include <QColor>
#include <QMap>

/*!
*	存储跟HOOPS显示有关的全局变量。
*	@author	Jerry He
*	@date	2014.6.17
*/
class Hoops3DConfiguration: public Base::IParametersModificationListener
{
public:
	static Hoops3DConfiguration* instance();

	void flushSize();

	double getShellVertexSize()const{return _shellVertexSize;}
	double getShellEdgeSize()const{return _shellEdgeSize;}
	bool getShowFEMMarker()const{return _showFEMMarker;}
	bool getShowConstraints()const{return _showConstraints;}
	bool getShowMassCenter()const{return _showMassCenter;}
	double getMassCenterSize()const{return _massCenterSize;}
	double getMarkerSize()const{return _markerSize;}
	bool getShowInitial()const{return _showInitial;}
	double getConstraintSize()const{return _constraintSize;}
	double getForceScale()const{return _forceScale;}
	double getEigenDisplayScale()const{return _eigenDisplayScale;}

	bool getShowFEMNodeID()const{return _showFEMNodeID;}
	double getFEMNodeIDSize()const{return _FEMNodeIDSize;}

	double getVelocityScale()const{return _velocityScale;}
	void setVelocityScale(double va){_velocityScale=va;}

	/*QColor getWindowsTopColor()const{return _windowsTopColor;}
	void setWindowsTopColor(const QColor& color);
	QColor getWidowsBottomColor()const{return _windowsBottomColor;}
	void setWindowsBottomColor(const QColor& color);*/

	friend QDataStream& operator << (QDataStream& fout,const Hoops3DConfiguration& config);
	friend QDataStream& operator >> (QDataStream& fin,Hoops3DConfiguration& config);

protected:
	virtual bool parameterChanged(Base::ParametersGroup* parameterManager,
		const Base::ParameterItem* newParameter,const Base::ParameterItem* oldParameter);

	Hoops3DConfiguration(void);
	~Hoops3DConfiguration(void);

	/// 更新值，没有则参加进集合。
	void initCurrent(bool isInitial);

	template<class T> void initOneItem(const QString&groupName,
		const QString& keyName,int varType,T* var);


	QMap<QString,QString>	_keynameMap;

	// attributes
	double	_shellVertexSize;
	double	_shellEdgeSize;
	bool	_showFEMMarker;
	bool	_showConstraints;
	bool	_showMassCenter;
	double	_massCenterSize;
	double	_markerSize;
	double	_constraintSize;
	bool	_showInitial;
	QColor	_windowsTopColor;
	QColor _windowsBottomColor;
	double	_forceScale;	//绘制力的比例
	double	_eigenDisplayScale;
	double  _velocityScale; //绘制速度的比例

	bool	_showFEMNodeID;
	double	_FEMNodeIDSize;

	bool	_showIMarker;
	bool	_showJMarker;

};

QDataStream& operator << (QDataStream& fout,const Hoops3DConfiguration& config);
QDataStream& operator >> (QDataStream& fin,Hoops3DConfiguration& config);

template<class T>
void Hoops3DConfiguration::initOneItem(const QString&groupName,
	const QString& keyName,int varType,T* var)
{
	ParametersManager* parameterManager=AppConfiguration::instance()->getParametersManager();
	const ParameterItem* item=parameterManager->get(keyName,groupName);
	if(item){
		*var=item->getVariant().value<T>();
	}
	else{
		ParameterItem newItem;
		newItem.setKeyword(keyName);
		newItem.setType(varType);
		newItem.setVariant(*var);
		parameterManager->set(newItem,groupName);
	}
}

