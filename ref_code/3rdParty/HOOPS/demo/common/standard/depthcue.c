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
 * $Id: depthcue.c,v 1.4 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"
#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} Point;

#define	VECTOR Point
#define PI	3.1415926536

void insert_cylinder (int n) {
    float	theta;
    float	tstep = 180.0f / (float) n;
    double      radians;
    int	i;
    int         pcount = n * 2;
    int         face_list_length = 0;
    Point	point[100];
    int	face_list[100];

    for (theta = 0.0f, i = 0; i < n; i++, theta += tstep) {
	radians =  theta * PI / 180.0;

	point[i + n].x =   point[i].x   = (float)cos (radians);
	point[i + n].y =   point[i].y   = (float)sin (radians);
	point[i + n].z =   -1.0f;
	point[i].z   = 30.0f;

	face_list[face_list_length++] = 4;

	face_list[face_list_length++] = i + n;
	face_list[face_list_length++] = (i + 1) % n + n;
	face_list[face_list_length++] = (i + 1) % n;
	face_list[face_list_length++] = i;
    }
    HC_Insert_Shell (pcount, point, face_list_length, face_list);
}

int main (
    int    argc,
    char   **argv) {
    float  x = 0.0f, y = 0.0f, z = 0.0f;
    float  index = 0.0f;
    HC_KEY fog_key = 0, no_fog_key = 0;

    HC_Open_Segment ("?Include Library");
        HC_Open_Segment ("cylinder");
            insert_cylinder (15);
            HC_Set_Color ("faces = light blue");
            HC_Set_Visibility ("markers = off");
            HC_Zoom_Camera (0.5);
            HC_Rotate_Object (-15.0, 20.0, 0.0);
        HC_Close_Segment ();

        HC_Open_Segment ("lines");
            for (x = -5.0f; x <= 5.0; x++)
		HC_Insert_Line ((double)x, 0.0, 0.0, (double)x, 0.0, 20.0);
            for (z = 0.0f; z <= 20.0; z++)
		HC_Insert_Line (5.0, 0.0, (double)z, -5.0, 0.0, (double)z);
            HC_Zoom_Camera (0.25);
            HC_Rotate_Object (-30.0, 0.0, 0.0);
        HC_Close_Segment ();

        HC_Open_Segment ("markers");
            HC_Set_Marker_Symbol (".");
            for (index = 0.0f; index < 30.0; index += 2.0f) {
		y = (float) index / 10.0f;
		HC_Insert_Marker (-0.50, y, index);
		HC_Insert_Marker (-0.25, y, index);
		HC_Insert_Marker (0.00, y, index);
		HC_Insert_Marker (0.25, y, index);
		HC_Insert_Marker (0.50, y, index);
	    }
        HC_Close_Segment ();

        HC_Open_Segment ("text");
            HC_Set_Text_Font ("name = stroked, transforms = full");
	    HC_Set_Text_Font ("size = 0.075 sru");
            HC_Orbit_Camera (-60.0, 0.0);
            HC_Zoom_Camera (0.5);
            HC_Insert_Text (0.0, 0.0, -0.5, "Atmospheric Attenuation");
            HC_Insert_Text (0.0, -0.5, -0.5, "Depth Cueing");
        HC_Close_Segment ();
    HC_Close_Segment ();

    HC_Open_Segment ("?picture");
        HC_Set_Driver_Options ("no gamma correction");
        HC_Set_Color ("text = red, window = light grey, window contrast = red");
        HC_Update_Display ();

        HC_Open_Segment ("no fog");
            HC_Set_Window (-1.0, 0.0, 0.8, 1.0);
            no_fog_key = HC_KInsert_Text (0.0, 0.0, -0.5, "Regular Text");
            HC_Set_Color ("text = red, window = black, window contrast = red");
        HC_Close_Segment ();
        HC_Open_Segment ("fog");
            HC_Set_Window (0.0, 1.0, 0.8, 1.0);
            fog_key = HC_KInsert_Text (0.0, 0.0, -0.5, "Attenuated Text");
            HC_Set_Color ("text = red, window = black, window contrast = red");
        HC_Close_Segment ();

        HC_Open_Segment ("text");
            HC_Set_Window (-1.0, 0.0, -1.0, 0.8);
            HC_Include_Segment ("?Include Library/text");
        HC_Close_Segment ();
        HC_Open_Segment ("foged text");
            HC_Set_Text_Font ("name = stroked, transforms = full");
            HC_Set_Rendering_Options (
		"atmospheric attenuation = (hither = 3, yon = 7)");
            HC_Set_Window (0.0, 1.0, -1.0, 0.8);
            HC_Include_Segment ("?Include Library/text");
        HC_Close_Segment ();
        HC_Pause ();

        HC_Delete_Segment ("?picture/text");
        HC_Delete_Segment ("?picture/foged text");
        HC_Delete_By_Key (no_fog_key);
        HC_Delete_By_Key (fog_key);
        no_fog_key = HC_QKInsert_Text ("?picture/no fog",
				       0.0, 0.0, -0.5, "Regular Lines");
        fog_key = HC_QKInsert_Text ("?picture/fog",
				    0.0, 0.0, -0.5, "Attenuated Lines");

        HC_Open_Segment ("lines");
            HC_Set_Window (-1.0, 0.0, -1.0, 0.8);
            HC_Include_Segment ("?Include Library/lines");
        HC_Close_Segment ();
        HC_Open_Segment ("foged lines");
            HC_Set_Rendering_Options (
		"atmospheric attenuation = (hither = 10, yon = 15)");
            HC_Set_Window (0.0, 1.0, -1.0, 0.8);
            HC_Include_Segment ("?Include Library/lines");
        HC_Close_Segment ();
        HC_Pause ();

        HC_Delete_Segment ("?picture/lines");
        HC_Delete_Segment ("?picture/foged lines");
        HC_Delete_By_Key (no_fog_key);
        HC_Delete_By_Key (fog_key);
        no_fog_key = HC_QKInsert_Text ("?picture/no fog",
				       0.0, 0.0, -0.5, "Regular Markers");
        fog_key = HC_QKInsert_Text ("?picture/fog",
				    0.0, 0.0, -0.5, "Attenuated Markers");

        HC_Open_Segment ("markers");
            HC_Set_Window (-1.0, 0.0, -1.0, 0.8);
            HC_Include_Segment ("?Include Library/markers");
        HC_Close_Segment ();
        HC_Open_Segment ("foged markers");
            HC_Set_Rendering_Options (
		"atmospheric attenuation = (hither = 4, yon = 20)");
            HC_Set_Window (0.0, 1.0, -1.0, 0.8);
            HC_Include_Segment ("?Include Library/markers");
        HC_Close_Segment ();
        HC_Pause ();

        HC_Delete_Segment ("?picture/markers");
        HC_Delete_Segment ("?picture/foged markers");
        HC_Delete_By_Key (no_fog_key);
        HC_Delete_By_Key (fog_key);
        no_fog_key = HC_QKInsert_Text ("?picture/no fog",
				       0.0, 0.0, -0.5, "Regular Shell");
        fog_key = HC_QKInsert_Text ("?picture/fog",
				    0.0, 0.0, -0.5, "Attenuated Shell");

        HC_Open_Segment ("shell");
            HC_Set_Window (-1.0, 0.0, -1.0, 0.8);
            HC_Set_Color ("window = light grey");
            HC_Include_Segment ("?Include Library/cylinder");
        HC_Close_Segment ();
        HC_Open_Segment ("foged shell");
            HC_Set_Rendering_Options (
		"atmospheric attenuation = (hither = 20, yon = 25)");
            HC_Set_Window (0.0, 1.0, -1.0, 0.8);
            HC_Set_Color ("window = light grey");
            HC_Include_Segment ("?Include Library/cylinder");
        HC_Close_Segment ();
        HC_Pause ();

        HC_Delete_Segment ("?picture/shell");
        HC_Delete_Segment ("?picture/foged shell");
        HC_Delete_By_Key (no_fog_key);
        HC_Delete_By_Key (fog_key);
    HC_Close_Segment ();

    HC_Exit_Program ();
    return 0;
}
