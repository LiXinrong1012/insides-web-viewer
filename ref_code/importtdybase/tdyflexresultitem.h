#pragma once

#include "precore/FlexResultItem.h"

namespace INSIDES{
	class IResults;
}
using namespace INSIDES;

/*!
	@brief   TDY柔性体条目继承实现
	@date    2015.7.6
	@author  Jerry
*/
class TDYFlexResultItem :
	public FlexResultItem
{
public:
	TDYFlexResultItem(IResults* parent);
	virtual ~TDYFlexResultItem(void);

	///位置设置
	virtual void setPos(int pos);

	///获得offset
	virtual int getOffset()const{return _offset;}

	///设置offset
	void setOffset(int o){_offset=o;}

protected:
	///用来存储offset变更 
	int		_offset;
};

