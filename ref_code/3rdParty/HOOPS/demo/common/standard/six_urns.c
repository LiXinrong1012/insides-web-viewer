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
 * $Id: six_urns.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */

/*
 * This file is slightly different from what's printed in the cookbook.
 * It has been updated to correspond to the latest changes to HOOPS.
 */

#include "hc.h"

int main () {
   HC_Define_Alias ("?urn", "?include library/urn");

   HC_Open_Segment ("?urn");
      HC_Read_Metafile ("urn", ".", "");
      HC_Rotate_Object (-25.0, 0.0, 0.0);
      HC_Insert_Distant_Light (1.0, 1.0, -1.0);
   HC_Close_Segment ();

   HC_Open_Segment ("?picture");
      HC_Set_Text_Font ("size = 0.03 wru");
      HC_Set_Text_Alignment ("*^");
      HC_Set_Camera_By_Volume ("perspective", -1.2, 1.2, -1.2, 1.2);
      HC_Set_Color ("faces = copper, lights = white");
      HC_Set_Visibility ("markers = off, edges = off");
      HC_Set_Rendering_Options ("no color interpolation");
      HC_Set_Rendering_Options ("no color index interpolation");
      HC_Set_Rendering_Options ("lighting interpolation = off");

      HC_Open_Segment ("wireframe");
         HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
         HC_Include_Segment ("?urn");
         HC_Set_Heuristics ("no hidden surfaces");
         HC_Set_Visibility ("faces = off, edges = on, lights = off");
         HC_Insert_Text (0.0, 1.25, 0.0, "wireframe");
      HC_Close_Segment ();

      HC_Open_Segment ("index interpolated");
         HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
         HC_Include_Segment ("?urn");
	 HC_Set_Rendering_Options ("color index interpolation");
         HC_Insert_Text (0.0, 1.25, 0.0, "color index interpolated");
      HC_Close_Segment ();

      HC_Open_Segment ("gouraud shaded");
         HC_Set_Window (0.33, 1.0, 0.0, 1.0);
         HC_Include_Segment ("?urn");
         HC_Set_Rendering_Options ("lighting interpolation");
         HC_Insert_Text (0.0, 1.25, 0.0, "gouraud");
      HC_Close_Segment ();

      HC_Open_Segment ("hidden surface and line");
         HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
         HC_Include_Segment ("?urn");
         HC_Set_Visibility ("faces = on, edges = on, lights = off");
         HC_Set_Rendering_Options ("hsra= hidden line, hidden line removal options=(visibility = off, pattern = 4, dim factor = 0.5, face displacement = 0.5)");
         HC_Set_Visibility (" lights = off");
         HC_Insert_Text (0.0, 1.25, 0.0, "true hidden line");
      HC_Close_Segment ();

      HC_Open_Segment ("flat shaded");
         HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
         HC_Include_Segment ("?urn");
	 HC_Insert_Text (0.0, 1.25, 0.0, "flat");
      HC_Close_Segment ();

      HC_Open_Segment ("phong shaded");
         HC_Set_Window (0.33, 1.0, -1.0, 0.0);
         HC_Include_Segment ("?urn");
         HC_Set_Rendering_Options ("lighting interpolation = phong");
         HC_Insert_Text (0.0, 1.25, 0.0, "phong");
      HC_Close_Segment ();

      HC_Pause ();
   HC_Close_Segment (); 	/* ?picture */
   HC_Exit_Program ();
   return 0;
}
