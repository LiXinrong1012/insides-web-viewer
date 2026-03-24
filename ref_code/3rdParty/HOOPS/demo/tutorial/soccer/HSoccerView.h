// HSoccerView.h : interface of the HSoccerView class, derived from HBaseView
// Adds application-specific data and members for each view

#ifndef _HSoccerView_H
#define _HSoccerView_H

#include "HBaseView.h"
#include "HUtility.h"
#include "HSnapGrid.h"

class HSelectionSet;


class HSoccerView : public HBaseView
{

public:

	HSoccerView(	HBaseModel *model,
							const char * 	alias = 0,	
							const char *	driver_type = 0,
							const char *	instance_name = 0,
							void *			window_handle = 0,
							void *			colormap = 0,
							void *			clip_override = 0);
	~HSoccerView();

	void	Init();

	/*! Perform some view-dependent text customization */
	void	ProcessText();

	/*! Delete the selected layers */
	void	DeleteLayers();

	/*! Returns whether there is an HSnapGrid object */
	HSnapGrid * GetSnapGrid() {return (m_pSnapGrid);}

	/*! Gets the state of the snap functionality */
	bool		GetSnap() {return (m_bSnap);}

	/*! Sets the state of the snap functionality */
	void		SetSnap(bool snap) {m_bSnap = snap;}

protected:

	/*! A pointer to an HSnapGrid object */
	HSnapGrid *	m_pSnapGrid;

	/*! Denotes whether snapping should be used or not */
	bool		m_bSnap;
};

#endif 




