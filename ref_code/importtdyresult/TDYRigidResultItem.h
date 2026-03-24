#pragma once

#include "precore/RigidResultItem.h"

using namespace INSIDES;

class TDYRigidResultItem :
	public RigidResultItem
{
public:
	TDYRigidResultItem(IResults* parent);
	virtual ~TDYRigidResultItem(void);

	virtual void setPos(int pos);

	virtual int getOffset()const{return _offset;}
	void setOffset(int o){_offset=o;}

protected:
	int		_offset;
};

