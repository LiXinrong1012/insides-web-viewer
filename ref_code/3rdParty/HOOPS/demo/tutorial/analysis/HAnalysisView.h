// HAnalysisView.h : interface of the HAnalysisView class, derived from HBaseView
// Adds application-specific data and members for each view

#ifndef _HAnalysisView_H
#define _HAnalysisView_H

#ifdef WINDOWS_SYSTEM
#include <windows.h>
#define USleep Sleep
#else
#include <unistd.h>
#define USleep usleep
#endif

#include "HBaseView.h"
#include "HUtility.h"

class HSelectionSet;


/*! 
	Custom HBaseView object which provides a few tutorial-specific methods
*/
class HAnalysisView : public HBaseView
{
public:

	HAnalysisView(	HBaseModel *model,
							const char * 	alias = 0,	
							const char *	driver_type = 0,
							const char *	instance_name = 0,
							void *			window_handle = 0,
							void *			colormap = 0,
							void *			clip_override = 0);
	~HAnalysisView();

	void Init();  //!< Initializes the HOOPS/MVO view

	/*! 
		Creates an artificial set of color index values and applies it to the first shell in the selection list
	*/
	void MapData(HC_KEY const key);

	/*! 
		Creates an artificial set of color index values and applies it to the shells in the selection list
	*/
	bool MapSelectionSet();

    /*!
		replaces the shell with a 'quad' interpolated shell. 
		It achives this by calling HUtilityGeometryCreation::GenerateFEAShell
	*/
	void QuadInterpolateData(HC_KEY const key);

    /*!
		Obtains the shells in the seleciton list, and replaces it with a 'quad' interpolated shell. 
	*/
	bool QuadInterpolateSelectionSet();

	/*! 
		The method animates the vertex color information on a shell.  
		It first obtains the shell whose key is stored in HAnalysisModel::m_pShellVertexData  (this data structure 
		was initialized in the call to HAnalysisView::MapData)  It then loops through (3 * HAnalysisModel::m_DataCycles) times, 
		and modifies the shell's vertex colors by cycling through the array denoted by HShellVertexData::m_pFIndexArray pointer.
	*/
	bool AnimateSelectionSet();

	/*! Toggles edge visibility */
	void SetVisibilityEdges(bool on_off);
};

#endif 




