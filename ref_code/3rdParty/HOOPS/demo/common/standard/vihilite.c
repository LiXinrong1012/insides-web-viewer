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
 * $Id: vihilite.c,v 1.4 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdlib.h>
#include <math.h>

/*  not needed to compile on Sun systems, on Sun boxes, the header
    files normally used are those for System R5 which are in /usr/include.
    Otherwise, "strings.h" on the Sun boxes can be found in, /usr/ucbinclude
    which is the older Berkley version.
 */
#ifndef SOLARIS_SYSTEM
#    include <string.h>
#endif

#define         TWOPI           6.2857142f
#define         COLORMAP_SIZE   10
#define         STREQ(a, b)      (!strcmp(a, b))

void insert_shaped_cylinder (
   float        r,
   float        height,
   int          n) {
   float	div, phi;
   typedef      struct {float x, y, z;} Point;
   Point       *mesh, *meshptr;
   HC_KEY       key;
   int          index, numrows, numcols;

   numrows = n + 1;
   numcols = 3;
   div = TWOPI / (float)n;

   mesh = (Point *) malloc (numrows * numcols * sizeof(Point));

   HC_Set_Visibility ("markers = off");
   HC_Set_Color ("edges = black");
   HC_Set_Color_Map ("pink, yellow, pine green, peach, blue, orange, cyan, magenta, sea green, purple");

   for (index = 0, meshptr = mesh; index <= n; index++) {
      phi = div * index;
      meshptr->x = r * (float)(cos(phi));		meshptr->y = -height/2.0f;
      meshptr->z = r * (float)(sin(phi));		++meshptr;

      meshptr->x = (r + r/2.0f) * (float)(cos(phi));	meshptr->y = 0.0f;
      meshptr->z = (r + r/2.0f) * (float)(sin(phi));	++meshptr;

      meshptr->x = r * (float)(cos(phi));		meshptr->y =  height/2.0f;
      meshptr->z = r * (float)(sin(phi));		++meshptr;
   }
   key = HC_KInsert_Mesh (numrows, numcols, mesh);
   free (mesh);

   HC_Open_Geometry (key);
      for (index = 0; index < (n*numcols); index++) {
         if ((index % numcols) != (numcols - 1)) {
            HC_Open_Face (index);
               HC_Set_Color_By_Index ("faces", (index / numcols) % COLORMAP_SIZE);
            HC_Close_Face ();
            HC_Open_Face (- (index + (numcols+1)));
               HC_Set_Color_By_Index ("faces", (index / numcols) % COLORMAP_SIZE);
            HC_Close_Face ();
         }
      }
   HC_Close_Geometry ();
}

void build_scene (void) {
   HC_Open_Segment ("?include library/shaped_cylinder");
      insert_shaped_cylinder (0.5f, 2.0f, 10);
   HC_Close_Segment ();
   HC_Define_Alias ("?cylinder", "?include library/shaped_cylinder");

   HC_Open_Segment ("?picture");
      HC_Set_Color ("faces = black, edges = red");
      /*
       * An edge weight of 3.0 causes some drivers (e.g. X11) to draw a few
       * pixels above the edge of the cylinder (driver specific)
       */
      HC_Set_Edge_Weight (3.0);

      HC_Open_Segment ("front view");
         HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
         HC_Set_Camera_By_Volume ("perspective", -2.0, 2.0, -2.0, 2.0);
         HC_Include_Segment ("?cylinder");
      HC_Close_Segment ();

      HC_Open_Segment ("top view");
	 HC_Set_Window (0.0, 1.0, 0.0, 1.0);
         HC_Set_Camera_By_Volume ("perspective", -2.0, 2.0, -2.0, 2.0);
         HC_Orbit_Camera (0.0, 90.0);
         HC_Include_Segment ("?cylinder");
      HC_Close_Segment ();

      HC_Open_Segment ("side view");
	 HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
         HC_Set_Camera_By_Volume ("perspective", -2.0, 2.0, -2.0, 2.0);
         HC_Orbit_Camera (90.0, 0.0);
         HC_Include_Segment ("?cylinder");
      HC_Close_Segment ();

      HC_Open_Segment ("above view");  /* slightly above and slightly right */
         HC_Set_Window (0.0, 1.0, -1.0, 0.0);
         HC_Set_Camera_By_Volume ("perspective", -2.0, 2.0, -2.0, 2.0);
         HC_Orbit_Camera (15.0, 15.0);
	 HC_Include_Segment ("?cylinder");
      HC_Close_Segment ();
}

void input_control (void) {
   char    segment[100];
   char    view_pathname[100];
   char    prev_view[100];
   int     status;
   char    type[10];

   HC_QSet_Selectability ("?picture", "windows = off, geometry = *O");
   HC_QSet_Driver_Options ("?picture", "selection proximity = 1");
   HC_Enable_Button_Events ("?Keyboard", "anything");
   HC_Enable_Selection_Events ("?Locater", "?picture");
   view_pathname[0] = prev_view[0] = '\0';

   for (;;) {
      while (STREQ(view_pathname, prev_view)) {
         HC_Await_Event (type);

         if (STREQ(type, "button")) {
            HC_Close_Segment ();     /* ?picture */
            HC_Exit_Program ();
         }
         HC_Show_Selection_Pathname (segment);
         status = HC_Parse_String (segment, "<", -1, view_pathname);
      }
      HC_QSet_Rendering_Options ("?picture/*", "no attribute lock");
      HC_QSet_Rendering_Options (view_pathname, "attribute lock = color");
      strcpy (prev_view, view_pathname);
   }
}

int main () {
   build_scene ();
   input_control ();
   return 0;
}









