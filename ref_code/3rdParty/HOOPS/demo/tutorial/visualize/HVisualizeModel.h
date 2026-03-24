// HVisualizeModel.h : interface of the HVisualizeModel.cpp class, derived from HBaseModel
// Adds application-specific data and members for each model

#ifndef _HVisualizeModel_H
#define _HVisualizeModel_H

#include "HDB.h"
#include "HBaseModel.h"
#include "HTools.h"


class HVisualizeModel : public HBaseModel
{
public:

	HVisualizeModel();
	~HVisualizeModel();

	// Overrides
	HFileInputResult Read(const char * FileName);
	bool Write(const char * FileName, HBaseView * pHView, int version, int width = 0, int height = 0);

	void	DeleteAllEntities();

	bool	IsSolidModel(){ return m_bSolidModel; };



protected:


	// do we have any solid modeler entities
	bool	m_bSolidModel;

};

#endif




