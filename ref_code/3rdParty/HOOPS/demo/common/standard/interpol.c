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
 * $Id: interpol.c,v 1.4 2007-06-20 22:30:03 conor Exp $
 */

#include			"hc.h"
#include            <math.h>
#define PI          3.1415926536f
#define NUM_SIDES   36
#define NUM_VERTEX  (2 * (NUM_SIDES + 1))

typedef struct point{ float  x, y, z;} Point;
float radius[4]   = {0.5f, 1.0f, 0.5f, 0.8f}, yvalue[2] = {0.5f, 0.0f};
float f_values[2] = {-0.499f, 3.499f};
char *labels[4]   = {"0", "1", "2", "3"};

HC_KEY object (void) {
   int      vertex;
   Point    array[NUM_VERTEX];
   float    angle;
   HC_KEY   key;

   for (vertex = 0; vertex < NUM_VERTEX; vertex++) {
      angle = (float) (vertex / 2.0f) / (float) NUM_SIDES * (2.0f * PI);
      array[vertex].x = radius[vertex % 4] * (float)cos (angle);
      array[vertex].y = yvalue[vertex % 2];
      array[vertex].z = radius[vertex % 4] * (float)sin (angle);
   }
   key = HC_KInsert_Mesh (NUM_SIDES + 1, 2, array);

   HC_Open_Geometry (key);
      for (vertex = 0; vertex < NUM_VERTEX; vertex++) {
         HC_Open_Vertex (vertex);
            HC_Set_Color_By_Index ("faces", (vertex % 2) * 3);
         HC_Close_Vertex ();
      }
   HC_Close_Geometry ();
   return key;
}

int main () {
   int   vertex, index;
   Point pts[10];
   HC_KEY key;

   HC_Open_Segment ("?include library/object");
      object ();
      HC_Scale_Object (0.5, 0.5, 0.5);
      HC_Rotate_Object (-15.0, 0.0, 0.0);
   HC_Close_Segment ();

   HC_Open_Segment ("?Picture");
      HC_Insert_Distant_Light (1.0, 1.5, -0.8);
      HC_Set_Color_Map ("darker dandelion, darker thistle, darker sea green, darker periwinkle");
      HC_Set_Camera_Projection ("orthographic");
      HC_Set_Text_Font ("size = .02 sru");
      HC_Set_Rendering_Options ("lighting interpolation");
      HC_Set_Color ("markers = red, faces = blue, text = black");
      HC_Set_Marker_Symbol ("@");
      HC_Set_Marker_Size (0.5);
      HC_Set_Visibility ("edges = off");

      HC_Open_Segment ("explanatory info");
         HC_Set_Text_Alignment ("<");
         HC_Insert_Text (-1.15, 0.90, 0.0, "ci = color interpolation");
         HC_Insert_Text (-1.15, 0.85, 0.0, "cii = color index interpolation");
      HC_Close_Segment ();

      HC_Open_Segment ("color map");
         HC_Set_Visibility ("markers = off");
         HC_Insert_Text (0.96, 0.95, 0.0, "color map");
         pts[0].x = 0.8f; pts[0].y = 0.8f; pts[0].z = 0.0f;
         pts[1].x = 0.8f; pts[1].y = 0.7f; pts[1].z = 0.0f;
         for (index = 2; index < 10; index++) {
            pts[index].x = pts[index - 2].x + 0.08f;
            pts[index].y = pts[index - 2].y;
            pts[index].z = 0.0f;
            if (index & 1)
               HC_Insert_Text ((float)(pts[index - 2].x +
				   ((pts[index].x - pts[index - 2].x) / 2)),
			       0.85, 0.0, labels[(index - 3)/2]);
         }
         key = HC_KInsert_Mesh (5, 2, pts);
         HC_Open_Geometry (key);
            for (index = 0; index < 6; index++) {
              HC_Open_Face (index);
                 HC_Set_Color_By_Index ("faces", index / 2);
              HC_Close_Face ();
            }
         HC_Close_Geometry ();
      HC_Close_Segment ();

      HC_Open_Segment ("view1");
         HC_Include_Segment ("?include library/object");
         HC_Translate_Object (0.0, 0.6, 0.0);
         HC_Set_Rendering_Options ("color interpolation, color index interpolation");
         HC_Insert_Text (0.0, -0.25, 0.0, "blended, thru color map colors");
         HC_Insert_Text (0.0, -0.3, 0.0, "(ci, cii)");
      HC_Close_Segment ();

      HC_Open_Segment ("view2");
         HC_Include_Segment ("?include library/object");
         HC_Translate_Object (-0.75, 0.0, 0.0);
         HC_Set_Rendering_Options ("no color interpolation, color index interpolation");
         HC_Insert_Text (0.15, -0.20, 0.0, "discrete, thru color map colors");
         HC_Insert_Text (0.15, -0.25, 0.0, "(no ci, cii)");
      HC_Close_Segment ();

      HC_Open_Segment ("view3");
         HC_Include_Segment ("?include library/object");
         HC_Translate_Object (0.75, 0.0, 0.0);
         HC_Set_Rendering_Options ("color interpolation, no color index interpolation");
         HC_Insert_Text (0.0, -0.20, 0.0, "blended, only vertex colors");
         HC_Insert_Text (0.0, -0.25, 0.0, "(ci, no cii)");
      HC_Close_Segment ();

      HC_Open_Segment ("view4");
         HC_Include_Segment ("?include library/object");
         HC_Translate_Object (-0.75, -0.7, 0.0);
         HC_Set_Rendering_Options ("no color interpolation, no color index interpolation");
         HC_Insert_Text (0.15, -0.20, 0.0, "ignore vertices, use face color");
         HC_Insert_Text (0.15, -0.25, 0.0, "(no ci, no cii)");
      HC_Close_Segment ();

      HC_Open_Segment ("view5");
         HC_Open_Segment ("");
            HC_Scale_Object (0.5, 0.5, 0.5);
            HC_Rotate_Object (-15.0, 0.0, 0.0);
            HC_Open_Geometry (object());
               for (vertex = 0; vertex < NUM_VERTEX; vertex++) {
                  HC_Open_Vertex (vertex);
                     HC_Set_Color_By_FIndex ("faces", f_values[(vertex % 2)]);
                  HC_Close_Vertex ();
               }
            HC_Close_Geometry ();
         HC_Close_Segment ();
         HC_Translate_Object (0.75, -0.7, 0.0);
         HC_Set_Rendering_Options ("no color interpolation, color index interpolation");
         HC_Insert_Text (0.0, -0.20, 0.0, "control layers by findex");
         HC_Insert_Text (0.0, -0.25, 0.0, "(no ci, cii)");
      HC_Close_Segment ();
   HC_Close_Segment ();		/* ?Picture */

   HC_Pause ();

   HC_Exit_Program ();
   return 0;
}
