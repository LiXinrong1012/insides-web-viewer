#pragma once

#include <QSharedPointer>
#include <QMap>

#include "precore/ResultDocument.h"


namespace INSIDES{
	class FlexResultItem;
	class FEMPartBaseItem;
	class BaseItem;
}

using namespace INSIDES;

class IExchangeSectionSurface;
class ISectionSurface;

/*!
*	负责跟截面显示相关的所有管理。
*	@author	Jerry He
*	@date	2014.6.9
*/
class SectionSurfaceManager : public IResultListener
{
public:
	SectionSurfaceManager(void);
	~SectionSurfaceManager(void);

	void addSectionSurface(FlexResultItem* flexResultItem,QList<double>& points,QList<double>& paras);

protected:
	void updateData();

	virtual void onResultCurrentFrameChanged();

private:
	typedef QSharedPointer<ISectionSurface> SecSurfPtr;
	typedef QMap<BaseItem*,SecSurfPtr > ItemMap;

	ItemMap	_itemMap;

};

