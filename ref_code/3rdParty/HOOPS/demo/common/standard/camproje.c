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
 * $Id: camproje.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"

void create_label (
   char   *projection) {

   HC_Open_Segment ("");
      HC_Set_Window_Frame ("off");
      HC_Insert_Text (0.0, 0.0, 0.0, projection);
      HC_Set_Window (-0.95, -0.35, -0.5, 0.0);
   HC_Close_Segment ();
}

int main () {
   HC_Define_Alias ("?champagne glass",
                    "?include library/champagne glass");

   HC_Open_Segment ("?champagne glass");
      HC_Read_Metafile ("champagn", ".", "");
      HC_Rotate_Object (-90.0, 0.0, 0.0);
      HC_Set_Visibility ("faces = off");
      HC_Set_Heuristics ("no hidden surfaces");
   HC_Close_Segment ();

   HC_Open_Segment ("?picture");
	HC_Open_Segment ("perspective camera");
	    HC_Set_Window (-0.9, 0.9, 0.3, 0.9);
	    HC_Set_Camera_Projection ("perspective");
	    HC_Include_Segment ("?champagne glass");
	    create_label ("Perspective");
	HC_Close_Segment ();

	HC_Open_Segment ("orthographic camera");
	    HC_Set_Window (-0.9, 0.9, -0.3, 0.3);
	    HC_Set_Camera_Projection ("orthographic");
	    HC_Include_Segment ("?champagne glass");
	    create_label ("Orthographic");
	HC_Close_Segment ();

	HC_Open_Segment ("Stretched camera");
	    HC_Set_Window (-0.9, 0.9, -0.9, -0.3);
	    HC_Set_Camera_Projection ("stretched");
	    HC_Include_Segment ("?champagne glass");
	    create_label ("Stretched");
	HC_Close_Segment ();

        HC_Pause ();
   HC_Close_Segment ();

   HC_Exit_Program ();
   return 0;
}
