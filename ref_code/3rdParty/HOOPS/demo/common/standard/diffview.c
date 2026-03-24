/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: diffview.c,v 1.4 2008-02-06 00:22:10 jason Exp $
 */

#ifdef WINDOWS_SYSTEM
#undef WINDOWS_SYSTEM
#endif

#include "hc.h"
#include "hic.h"

float	green[]  = {0.0f, 1.0f, 0.0f};
float	blue[]   = {0.0f, 0.0f, 1.0f};
float	yellow[] = {1.0f, 1.0f, 0.0f};

void change_cone_color (
    HIC_Rendition	const *r,
    HIC_Segment_Info	const *si) {
    HIC_Rendition	const *new_r;
    void		*ptr;

    new_r = HIC_New_Rendition (r);
	ptr = HIC_Show_User_Index (new_r, 13);
	if (ptr != 0)
	    HIC_Set_Face_Color (new_r, ptr);
	HIC_Draw_Segment (new_r, si);
    HIC_Free_Rendition (new_r);
}

int main () {
    HC_Define_Alias ("?cone", "?include library/cone");
    HC_Read_Metafile ("cone", "?cone", "restore state");
    HC_QSet_Color ("?cone", "faces = red");

    HC_Define_Callback_Name ("change cone color", change_cone_color);
    HC_QSet_Callback ("?cone", "draw segment tree = change cone color");

    HC_Open_Segment ("?picture");
	HC_Set_Color ("windows = grayish black");
	HC_Set_Visibility ("no markers");
	HC_Insert_Distant_Light (1.0, 1.0, -1.0);

	HC_Open_Segment ("view1");
	    HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
	    HC_Include_Segment ("?cone");
	    HC_Orbit_Camera (90.0, 0.5);
	    HC_Set_User_Index (13, green);
	HC_Close_Segment ();

	HC_Open_Segment ("view2");
	    HC_Set_Window (0.0, 1.0, 0.0, 1.0);
	    HC_Include_Segment ("?cone");
	    HC_Orbit_Camera (0.0, 0.5);
	HC_Close_Segment ();

	HC_Open_Segment ("view3");
	    HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
	    HC_Include_Segment ("?cone");
	    HC_Orbit_Camera (90.0, 90.0);
	    HC_Set_User_Index (13, blue);
	HC_Close_Segment ();

	HC_Open_Segment ("view4");
	    HC_Set_Window (0.0, 1.0, -1.0, 0.0);
	    HC_Include_Segment ("?cone");
	    HC_Orbit_Camera (45.0, 30.5);
	    HC_Set_User_Index (13, yellow);
	HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Pause ();
    HC_Exit_Program ();
    return 0;
}
