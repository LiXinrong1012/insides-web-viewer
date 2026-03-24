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
 * $Id: stretcam.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"

typedef struct { float x, y, z; } Point;

float   arrow[] =  {0.1f,  0.2f,  0.0f,  0.6f,  0.2f,  0.0f,
                    0.6f,  0.8f,  0.0f,  0.98f, 0.0f,  0.0f,
                    0.6f, -0.8f,  0.0f,  0.6f, -0.2f,  0.0f,
                    0.1f, -0.2f,  0.0f};
int main () {
   Point       in, out;

   HC_Define_Alias ("?arrow", "?include library/arrow");
   HC_Open_Segment ("?arrow/right");
      HC_Insert_Polygon (7, arrow);
   HC_Close_Segment ();
   HC_Open_Segment ("?arrow/left");
      HC_Insert_Polygon (7, arrow);
      HC_Scale_Object (-1.0, 1.0, 1.0);
   HC_Close_Segment ();

   HC_Open_Segment ("?picture");
      HC_Set_Text_Font ("size = 0.02 sru");
      HC_Set_Camera_Projection ("orthographic");
      HC_Set_Heuristics ("concave polygons");

      HC_Open_Segment ("orthographic camera");
         HC_Set_Window (-0.8, 0.8, 0.4, 0.8);
         HC_Include_Segment ("?arrow");
         HC_Insert_Text (0.0, -0.5, 0.0, "Orthographic");
      HC_Close_Segment ();

      HC_Open_Segment ("orthographic camera with scale");
         HC_Set_Window (-0.8, 0.8, -0.2, 0.2);
         HC_Include_Segment ("?arrow");
         in.x = 1.0f; in.y = 1.0f; in.z = 0.0f;
         if (HC_Compute_Coordinates (".", "local window", &in, "world", &out))
            HC_Scale_Object (out.x, out.y, 1.0);
         HC_Insert_Text (0.0, -0.5, 0.0, "Orthographic with Computed Scale");
      HC_Close_Segment ();

      HC_Open_Segment ("stretched camera");
         HC_Set_Camera_Projection ("stretched");
         HC_Set_Window (-0.8, 0.8, -0.8, -0.4);
         HC_Include_Segment ("?arrow");
         HC_Insert_Text (0.0, -0.5, 0.0, "Stretched");
      HC_Close_Segment ();
   HC_Close_Segment ();

   HC_Pause ();
   HC_Exit_Program ();
   return 0;
}
