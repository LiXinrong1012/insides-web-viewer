#ifndef EXSECSURF_H
#define EXSECSURF_H

#include "exsecsurf_global.h"

#include "include/IExchangeSectionSurface.h"


/*!
*	THU Dynamics Solver 截面显示转换插件
*
*/
class EXSECSURF_EXPORT ExSecSurf: public QObject, public IExchangeSectionSurface
{
Q_OBJECT
	Q_INTERFACES(IExchangeSectionSurface)

public:
	ExSecSurf();
	virtual ~ExSecSurf();


	virtual QString getKeyname();

	virtual ISectionSurface* createSectionSurface(FlexResultItem* flexResultItem);

private:

};

#endif // EXSECSURF_H
