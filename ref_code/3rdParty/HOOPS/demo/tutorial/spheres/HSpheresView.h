// HSpheresView.h : interface of the HSpheresView class, derived from HBaseView
// Adds application-specific data and members for each view

#ifndef _HSpheresView_H
#define _HSpheresView_H

#include "HBaseView.h"
#include "HUtility.h"

class HSelectionSet;


class HSpheresView : public HBaseView
{

public:

	HSpheresView(	HBaseModel *model,
							const char * 	alias = 0,	
							const char *	driver_type = 0,
							const char *	instance_name = 0,
							void *			window_handle = 0,
							void *			colormap = 0,
							void *			clip_override = 0);
	~HSpheresView();

	void	Init();
	void	ChangeMaterial();
	int		OnLButtonDblClk(HEventInfo &event){return HLISTENER_PASS_EVENT;};
};

#endif 




