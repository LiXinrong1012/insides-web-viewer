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
 * $Id: highligh.c,v 1.4 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdio.h>
#include <string.h>
#define streq(a, b) (strcmp(a, b) == 0)

typedef struct { float   x, y, z;}   Point;

int main () {
   HC_Open_Segment ("?picture");
      HC_Read_Metafile ("robot", ".", "");
      HC_Set_Heuristics ("no hidden surfaces");
      HC_Set_Visibility ("faces = off");
      HC_Set_Selectability ("geometry");
   HC_Close_Segment ();

   HC_Define_Alias ("?highlight",
                    "?picture/quick moves highlight");

   HC_Open_Segment ("?highlight");
      HC_Set_Selectability ("geometry = off");
      HC_Set_Color ("red");
      HC_Set_Line_Weight (5.0);
      HC_Set_Heuristics ("quick moves");
   HC_Close_Segment ();

   HC_Enable_Button_Events ("?Keyboard", "anything");
   HC_Enable_Selection_Events ("?Locater", "?Picture");

   for (;;) {
      char      geometry_type[20], input_type[20];
      Point     pts[100];
      HC_KEY    key;
      int       count, offset1, offset2, offset3;

      HC_Await_Event (input_type);
      if (streq(input_type, "button")) {
	  HC_Exit_Program();
	  return 0;
      }

      HC_Flush_Geometry ("?highlight");
      HC_Show_Selection_Element (&key, &offset1, &offset2, &offset3);
      HC_Show_Key_Type (key, geometry_type);

      if (streq (geometry_type, "circle")) {

         HC_Show_Circle (key, &pts[0], &pts[1], &pts[2]);
         HC_QInsert_Circle ("?highlight", &pts[0], &pts[1], &pts[2]);
      }
      else if (streq (geometry_type, "line")) {

         HC_Show_Line (key, &pts[0].x, &pts[0].y, &pts[0].z,
                            &pts[1].x, &pts[1].y, &pts[1].z);
         HC_QInsert_Line ("?highlight", pts[0].x, pts[0].y, pts[0].z,
                                        pts[1].x, pts[1].y, pts[1].z);
      }
      else if (streq (geometry_type, "marker")) {

         HC_Show_Marker (key, &pts[0].x, &pts[0].y, &pts[0].z);
         HC_QInsert_Marker ("?highlight", pts[0].x, pts[0].y, pts[0].z);
      }
      else if (streq (geometry_type, "polyline")) {

         HC_Show_Polyline (key, &count, pts);
         HC_QInsert_Polyline ("?highlight", count, pts);
      }
      else if (streq (geometry_type, "polygon")) {

         HC_Show_Partial_Polygon (key, offset1, 1, &pts[0]);
         HC_Show_Partial_Polygon (key, offset2, 1, &pts[1]);
         HC_QInsert_Line ("?highlight", pts[0].x, pts[0].y, pts[0].z,
                                        pts[1].x, pts[1].y, pts[1].z);
      }
   }
}
