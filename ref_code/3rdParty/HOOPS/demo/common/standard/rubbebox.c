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
 * $Id: rubbebox.c,v 1.3 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdio.h>
#include <string.h>
#define  streq(a, b)  (strcmp(a, b) == 0)

typedef struct {   float   x, y, z;}   Point;

void fill_box (
   float    x0,
   float    y0,
   float    x1,
   float    y1) {
   Point    pts[4];

   pts[0].x = x0;   pts[0].y = y0;   pts[0].z = 0.0f;
   pts[1].x = x0;   pts[1].y = y1;   pts[1].z = 0.0f;
   pts[2].x = x1;   pts[2].y = y1;   pts[2].z = 0.0f;
   pts[3].x = x1;   pts[3].y = y0;   pts[3].z = 0.0f;

   HC_Open_Segment ("?picture");
      HC_Insert_Polygon (4, pts);
   HC_Close_Segment ();
}

void rubber_box (
   float       x0,
   float       y0,
   float       x1,
   float       y1) {
   Point       pts[5];

   pts[0].x = x0;   pts[0].y = y0;   pts[0].z = 0.0f;
   pts[1].x = x0;   pts[1].y = y1;   pts[1].z = 0.0f;
   pts[2].x = x1;   pts[2].y = y1;   pts[2].z = 0.0f;
   pts[3].x = x1;   pts[3].y = y0;   pts[3].z = 0.0f;
   pts[4].x = x0;   pts[4].y = y0;   pts[4].z = 0.0f;

   HC_Insert_Polyline (5, pts);
}

int main () {
   HC_Open_Segment ("?picture");
	  HC_Set_Color ("edges = green , lines = red ,face = black");
	  HC_Set_Face_Pattern ("//");
   HC_Close_Segment ();

   HC_Enable_Selection_Events ("?locater", "?picture");
   HC_Enable_Button_Events ("?keyboard", "Q, q");

   HC_Open_Segment ("?picture/rubberband box");
      HC_Set_Heuristics ("quick moves");
      for (;;) {
         char        segment[64], action[4], event_type[64];
         float       x0, y0, x1, y1, junk;
         int         status;

         HC_Await_Event (event_type);

         if (streq (event_type, "selection")) {
            HC_Show_Selection_Source (segment, segment, action, &status);

            if (streq (action, "v")) {
               HC_QSet_Selectability ("?picture", "*^");
               HC_Show_Selection_Position (&junk, &junk, &junk, &x0, &y0, &junk);
            }
            else if (streq (action, "*")) {
               HC_Flush_Geometry (".");
               HC_Show_Selection_Position (&junk, &junk, &junk, &x1, &y1, &junk);
               rubber_box (x0, y0, x1, y1);
            }
            else if (streq (action, "^")) {
               HC_Flush_Geometry (".");
               HC_QSet_Selectability ("?picture", "v");
               HC_Show_Selection_Position (&junk, &junk, &junk, &x1, &y1, &junk);
               fill_box (x0, y0, x1, y1);
            }
         }
         else if (streq (event_type, "button")) break;
      }
   HC_Close_Segment ();      /* ?picture/rubberband_box */

   HC_Disable_Selection_Events ("?locater", "?picture");
   HC_Disable_Button_Events ("?keyboard", "Q, q");

   HC_Exit_Program ();
   return 0;
}
