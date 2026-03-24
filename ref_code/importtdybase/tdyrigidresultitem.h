#pragma once

#include "precore/RigidResultItem.h"

using namespace INSIDES;

///tdy rigid result条目实现
class TDYRigidResultItem :
	public RigidResultItem
{
public:
	TDYRigidResultItem(IResults* parent);
	virtual ~TDYRigidResultItem(void);

	///设置位置
	virtual void setPos(int pos);

	///获得offset
	virtual int getOffset()const{return _offset;} 

	///设置offset
	void setOffset(int o){_offset=o;}

protected:
	int		_offset;
};
