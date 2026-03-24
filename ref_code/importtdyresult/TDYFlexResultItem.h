#pragma once

#include "precore/FlexResultItem.h"

namespace INSIDES{
	class IResults;
}
using namespace INSIDES;

class TDYFlexResultItem :
	public FlexResultItem
{
public:
	TDYFlexResultItem(IResults* parent);
	virtual ~TDYFlexResultItem(void);

	virtual void setPos(int pos);

	virtual int getOffset()const{return _offset;}
	void setOffset(int o){_offset=o;}

protected:
	int		_offset;
};

