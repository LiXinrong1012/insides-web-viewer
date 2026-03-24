#pragma once

#include "base/Legend.h"
#include <QList>

namespace INSIDES{
	class IResultItem;
}

using namespace INSIDES;

class LegendItem;

class DisplayLegendItem
{
public:

	IResultItem*	relatedResultItem;
	LegendItem*		parentLegendItem;
	int				sectionIndex;
	int				subSectionIndex;
	int				subsubSectionIndex;
	bool			isRemoved;

	DisplayLegendItem():isRemoved(false)
	{
	}
};



class LegendItem
{
public:
	LegendItem();
	~LegendItem();

	Base::Legend* getLegend(){return &_legend;}
	int getItemCount()const{return _displayLegend.size();}
	DisplayLegendItem* getItem(int index){return &_displayLegend[index];}
	void addItem(const DisplayLegendItem& item);
	void clearAll();

	void updateBounding();
	void updateOnlyCurrentBounding();

	bool isDirty()const{return _isDirty;}
	void setDirty(bool b);

protected:
	Base::Legend _legend;
	QList<DisplayLegendItem> _displayLegend;
	bool		_isDirty;
};




/*!
*	代表一个云图条Legend集合。
*	@author	Jerry He
*	@date	2014.5.24
*/
class LegendManager
{
public:
	LegendManager(void);
	~LegendManager(void);

	int getLegendCount();
	LegendItem* getLegend(int index);
	void addLegend(LegendItem* item){_legendItems.push_back(item);}
	void clear();

protected:
	QList<LegendItem*>	_legendItems;
	


};

