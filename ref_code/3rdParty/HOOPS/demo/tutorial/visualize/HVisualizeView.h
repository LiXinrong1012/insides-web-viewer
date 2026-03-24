// HVisualizeView.h : interface of the HVisualizeView class, derived from HBaseView
// Adds application-specific data and members for each view

#ifndef _HVisualizeView_H
#define _HVisualizeView_H

#include "HBaseView.h"
#include "HUtility.h"

class HSelectionSet;


class HVisualizeView : public HBaseView
{

public:

	HVisualizeView(	HBaseModel *model,
							const char * 	alias = 0,	
							const char *	driver_type = 0,
							const char *	instance_name = 0,
							void *			window_handle = 0,
							void *			colormap = 0,
							void *			clip_override = 0);
	~HVisualizeView();

	void	Init();

	/*! Create LOD levels for the shells in the model */
	void	OnBuildLODS();

	/*! Clamp to the original (full-resoluation) shells */
	void	OnLODOriginal();

	/*! Clamp to LOD level 1 */
	void	OnLOD1();

	/*! Clamp to LOD level 2 */
	void	OnLOD2();

	/*! Enable constant framerate logic */
	void	OnEnableFramerate();

	/*! Disable constant framerate logic */
	void	OnDisableFramerate();

};

#endif 




