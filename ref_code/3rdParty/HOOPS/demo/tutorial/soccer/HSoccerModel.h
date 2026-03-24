// HSoccerModel.h : interface of the HSoccerModel.cpp class, derived from HBaseModel
// Adds application-specific data and members for each model

#ifndef _HSoccerModel_H
#define _HSoccerModel_H

#include "HDB.h"
#include "HBaseModel.h"
#include "HTools.h"
#include "HUtilityGeometryCreation.h"


class HSoccerModel : public HBaseModel
{
public:

	HSoccerModel();
	~HSoccerModel();

	void Init();

	/*! utility function that inserts a polygon into the specified segment */
	static void		InsertFilledRectangle (const char * seg, float x0, float y0, float x1, float y1);

	// Overrides
	HFileInputResult Read(const char * FileName);
	bool Write(const char * FileName, HBaseView * pHView, int version, int width = 0, int height = 0);

	/*! Delete all of the HOOPS/3dGS scene-graph associated with this HSoccerModel object */
	void	DeleteAllEntities();

	/*! Returns whether the scene-graph contains geometry representing a solid model */
	bool	IsSolidModel(){ return m_bSolidModel; };

	/*! Returns a pointer to the list of layers associated with the model */
	struct vlist_s * GetLayerList(){return m_pLayers; };

protected:

	/*! keys of the segments that represent the layers in the scene-graph */
	struct vlist_s	*m_pLayers;	

	/*! we have any solid modeler entities */
	bool	m_bSolidModel;

};

#endif




