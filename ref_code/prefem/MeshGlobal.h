#pragma once

#include "prefem/prefem_def.h"

class MeshGlobal
{
public:
	MeshGlobal(void);
	~MeshGlobal(void);

	PP_ELTYPE* getType(){return _elemTypes;}
	PP_ELTYPE* getType(int elemIndex){return &_elemTypes[elemIndex];}


private:
	PP_ELTYPE _elemTypes[MAX_ELEMENT_TYPE];
};

