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
 * $Id: gouhard.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */


/*
 * This file demonstates use of the "hardcopy resolution" driver option
 * to control the resolution of hardcopy output. This HOOPS driver option
 * only applies to drivers that can take action based on this option.
 * Although the hardcopy resolution driver option can be set for any driver,
 * e.g. X11, it is ignored by drivers that lack native primitive support
 * to control resolution. For example, this driver option applies to
 * the CGM and PostScript drivers, but NOT the MSW driver.
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
         HC_Set_Window (-1.0, -0.33, -0.5, 0.5);
         HC_Include_Segment ("?urn");
         HC_Set_Heuristics ("no hidden surfaces");
         HC_Set_Visibility ("faces = off, edges = on");
         HC_Insert_Text (0.0, 1.25, 0.0, "wireframe");
      HC_Close_Segment ();

      HC_Open_Segment ("flat shaded");
         HC_Set_Window (-0.33, 0.33, -0.5, 0.5);
         HC_Include_Segment ("?urn");
	 HC_Insert_Text (0.0, 1.25, 0.0, "flat");
      HC_Close_Segment ();

      HC_Open_Segment ("gouraud shaded");
         HC_Set_Rendering_Options ("hsr algorithm = software z buffer");
         HC_Set_Window (0.33, 1.0, -0.5, 0.5);
         HC_Include_Segment ("?urn");
         HC_Set_Rendering_Options ("lighting interpolation");
         HC_Insert_Text (0.0, 1.25, 0.0, "gouraud");
      HC_Close_Segment ();

      HC_Pause ();
   HC_Close_Segment ();	/* ?picture */

   HC_Open_Segment ("?driver/postscript/gouhard50.ps");
      HC_Set_Driver_Options ("hardcopy resolution = 50");
      HC_Insert_Text (0.0, 0.75, 0.0, "hardcopy resolution = 50");
      HC_Include_Segment ("?picture");
      HC_Update_Display ();
   HC_Close_Segment ();

   HC_Delete_Segment ("?driver/postscript/gouhard50.ps");

   HC_Open_Segment ("?driver/postscript/gouhard150.ps");
      HC_Set_Driver_Options ("hardcopy resolution = 150");
      HC_Insert_Text (0.0, 0.75, 0.0, "hardcopy resolution = 150");
      HC_Include_Segment ("?picture");
      HC_Update_Display ();
   HC_Close_Segment ();

   HC_Delete_Segment ("?driver/postscript/gouhard150.ps");

   HC_Exit_Program ();
   return 0;
}
