// HAnalysisModel.h : interface of the HAnalysisModel.cpp class, derived from HBaseModel
// Adds application-specific data and members for each model

#ifndef _HAnalysisModel_H
#define _HAnalysisModel_H

#include "HDB.h"
#include "HBaseModel.h"
#include "HUtility.h"
#include "HUtilityGeometryCreation.h"
#include "HTools.h"

/*!
	Custom HBaseModel object which provides a few tutorial-specific data members
*/
class HAnalysisModel : public HBaseModel
{
public:

	HAnalysisModel();
	virtual ~HAnalysisModel();

	/*! Creates a starting HOOPS/3dGS scene graph containing a colormap and a legend bar */
	void Init();

	// Overrides
	HFileInputResult Read(const char * FileName);
	bool Write(const char * FileName, HBaseView * pHView, int version, int width = 0, int height = 0);
	bool IsSolidModel(){ return m_bSolidModel; };

	int					 m_DataCycles;  //!< number of datacycles for the contour animation
    HShellVertexData	 m_ShellVertexData; //!< pointer to the data structure that will store the color index data


protected:

	// do we have any solid modeler entities
	bool	m_bSolidModel;

};

#endif




