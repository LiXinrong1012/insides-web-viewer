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
 * $Id: posthard.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"

#define NUMBER_OF_NODES   24
#define PI                3.141592f
#define R                 0.8f

int main () {
   int     	ii, jj;
   extern       double   sin (), cos();
   float   	delta = (2.0f * PI) / (float)NUMBER_OF_NODES;

   HC_Open_Segment ("?picture");
      for (ii = 0; ii < NUMBER_OF_NODES; ii++) {
         for (jj = ii; jj < NUMBER_OF_NODES; jj++) {

            HC_Insert_Line (
               R * sin (delta * ii), R * cos(delta * ii), 0.0,
               R * sin (delta * jj), R * cos(delta * jj), 0.0);
	 }
      }
      HC_Pause ();
   HC_Close_Segment ();     /* ?Picture */

   HC_Open_Segment ("?driver/postscript/doily.ps");
      HC_Include_Segment ("?picture");
      HC_Update_Display ();
   HC_Close_Segment ();

   HC_Delete_Segment ("?driver/postscript/doily.ps");

   HC_Exit_Program ();
   return 0;
}
