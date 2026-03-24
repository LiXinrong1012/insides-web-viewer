// HSampleHModel.h : interface of the HSampleHModel.cpp class, derived from HBaseModel
// Adds application-specific data and members for each model

#ifndef _HSampleHModel_H
#define _HSampleHModel_H

#include "HBaseModel.h"

class HSampleHModel : public HBaseModel
{
private:

public:
	HSampleHModel();
	~HSampleHModel();

	virtual void Init();	
	virtual void Flush();


};

#endif




