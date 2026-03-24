#pragma once


#include "include/iexchangesectionsurface.h"

namespace INSIDES{
	class FlexResultItem;
}
using namespace INSIDES;

class TDYSectionSurface :
	public ISectionSurface
{
public:
	typedef QList<double>  SectionPointList;

	TDYSectionSurface(FlexResultItem* flexResultItem);
	virtual ~TDYSectionSurface(void);

	virtual void init();
	virtual void update();

	virtual void setD1Points(const QList<double>& points){_section1DPoints=points;}
	virtual void setD1Paras(const QList<double>& params){_section1DParams=params;}

	virtual void setD2Paras(const QList<double>& params){_section2DParams=params;}
	
protected:
	void updateDataSection(FlexResultItem* newFlexResult);

	void initSection1D();
	void initSection2D();

	void generateNode1D(FlexResultItem* pResult, int iStartNodeIdx, 
		const double* pos, const double* phi, const double* F, const double* M);
	void generateNode2D(FlexResultItem* pResult, int iStartNodeIdx, 
		const double* pos, const double* phi, const double* F, const double* M);

	bool check();

private:
	FlexResultItem*		_flexResultItem;
	FlexResultItem*		_newFlexResultItem;
	
	SectionPointList	_section1DPoints;
	SectionPointList	_section1DParams;

	SectionPointList	_section2DParams;		//³õ¶¨£¬0:ºñ¶È

	QMap<int,int>		_beamId2RealStartID;
	QMap<int,int>		_shellId2RealStartID;

	QVector<int>			_elementStartID;
	QVector<int>			_elementType;
	QVector<unsigned long>			_elementNodeList;
};

