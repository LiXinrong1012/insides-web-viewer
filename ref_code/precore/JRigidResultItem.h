#pragma once

#include "precore/rigidresultitem.h"

namespace pp{class DataBlock;}

namespace INSIDES
{

class JRigidResultItem :
	public RigidResultItem
{
public:
	JRigidResultItem(IResults* parent,qint64 startPos);
	virtual ~JRigidResultItem(void);

	virtual void setPos(int index);
	void setDataBlock(pp::DataBlock* dataBlock){_dataBlock=dataBlock;}
	
private:
	qint64		_startPos;
	pp::DataBlock*	_dataBlock;
	
};

}