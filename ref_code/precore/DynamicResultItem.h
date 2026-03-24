#pragma once
#include "precore/RigidResultItem.h"


namespace INSIDES{

class IResults;

class PRECORE_EXPORT DynamicResultItem :
	public RigidResultItem
{
public:
	DynamicResultItem(IResults* parent);
	virtual ~DynamicResultItem(void);

	int getPieceCount()const{return _pieceCount;}
	void setPieceCount(int c){_pieceCount=c;}

protected:
	int _pieceCount;
};

}	// end namespace INSIDES

