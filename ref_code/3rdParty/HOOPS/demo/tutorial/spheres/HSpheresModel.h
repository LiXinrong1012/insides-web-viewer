// HSpheresModel.h : interface of the HSpheresModel.cpp class, derived from HBaseModel
// Adds application-specific data and members for each model

#ifndef _HSpheresModel_H
#define _HSpheresModel_H

#include "HDB.h"
#include "HBaseModel.h"
#include "HTools.h"


class HSpheresModel : public HBaseModel
{
public:

	HSpheresModel();
	~HSpheresModel();

	// Overrides
	HFileInputResult Read(const char * FileName);
	bool Write(const char * FileName, HBaseView * pHView, int version, int width = 0, int height = 0);

	/*! Delete all the entities in the model */
	void	DeleteAllEntities();

	/*! Returns true if this represents a solid modeller model */
	bool	IsSolidModel(){ return m_bSolidModel; };

protected:


	// do we have any solid modeler entities
	bool	m_bSolidModel;

};

#endif




