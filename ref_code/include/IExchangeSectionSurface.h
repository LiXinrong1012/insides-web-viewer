#pragma once

#include <QString>
#include <QList>
#include <QtCore>


namespace INSIDES{
	class IResults;
	class FlexResultItem;
}
using namespace INSIDES;

/*!
*	代表一个柔性体的截面。
*/
class ISectionSurface
{
public:
	virtual ~ISectionSurface(){}

	virtual void init()=0;
	virtual void update()=0;

	virtual void setD1Points(const QList<double>& points)=0;
	virtual void setD1Paras(const QList<double>& params)=0;
};

class IExchangeSectionSurface
{
public:

	virtual ~IExchangeSectionSurface(void) { }

	virtual QString getKeyname()=0;

	virtual ISectionSurface* createSectionSurface(FlexResultItem* flexResultItem)=0;

};

Q_DECLARE_INTERFACE(IExchangeSectionSurface,
	"com.jerryhe.tdypre.IExchangeSectionSurface/2.0");
