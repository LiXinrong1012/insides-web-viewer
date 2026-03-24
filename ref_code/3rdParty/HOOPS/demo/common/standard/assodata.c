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
 * $Id: assodata.c,v 1.4 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define streq(a, b) (strcmp(a, b) == 0)

int main () {
   int       i;

   HC_Open_Segment ("?picture");
      HC_Set_Driver_Options ("selection proximity = 3");
      HC_Set_Text_Font ("name = (Sans Serif, Typewriter)");
      HC_Set_Text_Font ("size = 0.03 sru");

      HC_Open_Segment ("title");
         HC_Set_Camera_Projection ("stretched");
         HC_Insert_Text (0.0, 0.85, 0.0, "Statistics of Major US Cities");
      HC_Close_Segment ();

      HC_Open_Segment ("us map");
         HC_Read_Metafile ("usa", ".", "");
	 HC_Set_Camera_By_Volume ("stretched", 0.0, 10.0, 0.0, 8.0);
         HC_Set_Selectability ("everything = off, markers = on");
         HC_Set_Marker_Symbol ("@");
         HC_Set_Text_Font ("size = 0.12 sru");

         HC_Open_Segment ("San Francisco");
            HC_Insert_Marker (0.44, 3.8, 0.0);
            HC_Set_User_Options ("population = 731600");
            HC_Set_User_Options ("elevation = 8");
         HC_Close_Segment ();

         HC_Open_Segment ("New York City");
            HC_Insert_Marker (8.95, 4.82, 0.0);
            HC_Set_User_Options ("population = 7352700");
            HC_Set_User_Options ("elevation = 132");
         HC_Close_Segment ();

         HC_Open_Segment ("Denver");
            HC_Insert_Marker (3.27, 3.7, 0.0);
            HC_Set_User_Options ("population = 492200");
            HC_Set_User_Options ("elevation = 5283");
         HC_Close_Segment ();
      HC_Close_Segment ();

      for (i = 0; i < 10; ++i) {
         char    segment[256], full_segment[256];
         char    message[100], value[100];
         float   mx, my, mz, x, y, z;
         HC_KEY  key;
         char    type[100];
         int     offset1, offset2, offset3;

         HC_Get_Selection (segment);
         HC_Show_Selection_Pathname (full_segment);
         HC_Show_Selection_Position (&mx, &my, &mz, &x, &y, &z);
         HC_Show_Selection_Element (&key, &offset1, &offset2, &offset3);
         HC_Show_Key_Type (key, type);

         if (streq (type, "marker")) {
            float   width, height;

            HC_Compute_Text_Extent (".", "T", &width, &height);
            width = width * 7.0f * 2.0f * 1.3f;
            height = height * 2.0f * 2.0f * 1.3f;

            HC_Open_Segment ("popup");
               HC_Flush_Geometry (".");
               if (mx + width > 1)
                  if (my + height > 1)
                     HC_Set_Window (mx - width, mx, my - height, my);
                  else
                     HC_Set_Window (mx - width, mx, my, my + height);
               else
                  if (my + height > 1)
                     HC_Set_Window (mx, mx + width, my - height, my);
                  else
                     HC_Set_Window (mx, mx + width, my, my + height);

               HC_Set_Camera_Projection ("stretched");
               HC_Insert_Text (0.0, 0.5, 0.0, segment);
               HC_QShow_One_User_Option (full_segment, "population", value);
               sprintf (message, "Population: %s", value);

               HC_Insert_Text (0.0, 0.0, 0.0, message);
               HC_QShow_One_User_Option (full_segment, "elevation", value);
               sprintf (message, "Elevation: %s", value);
               HC_Insert_Text (0.0, -0.5, 0.0, message);
            HC_Close_Segment ();
         }
         else if (HC_QShow_Existence ("popup", "self"))
            HC_Delete_Segment ("popup");
      }
   HC_Close_Segment ();

   HC_Exit_Program ();
   return 0;
}
