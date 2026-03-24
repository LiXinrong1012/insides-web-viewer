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
 * $Id: camcoord.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"

int main () {
   HC_Define_Alias ("?vw", "?include library/volkswagen");
   HC_Open_Segment ("?vw");
      HC_Read_Metafile ("vw", ".", "");
      HC_Orbit_Camera (110.0, 0.0);
      HC_Set_Color ("faces = white");
   HC_Close_Segment ();

   HC_Open_Segment ("?picture");

      HC_Open_Segment ("left window");
         HC_Set_Window (-0.95, 0.5, -0.3, 0.95);
         HC_Include_Segment ("?vw");
      HC_Close_Segment ();

      HC_Open_Segment ("top right window");
         HC_Set_Window (0.5, 0.95, 0.5, 0.95);
         HC_Include_Segment ("?vw");
      HC_Close_Segment ();

      HC_Open_Segment ("middle right window");
         HC_Set_Window (0.5, 0.95, -0.3, 0.5);
         HC_Include_Segment ("?vw");
      HC_Close_Segment ();

      HC_Open_Segment ("wide short window");
         HC_Set_Window (-0.95, 0.95, -0.95, -0.3);
         HC_Include_Segment ("?vw");
      HC_Close_Segment ();

      HC_Pause ();

   HC_Close_Segment ();     /* ?picture */

   HC_Exit_Program ();
   return 0;
}
