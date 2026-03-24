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
 * $Id: nmesh.c,v 1.6 2010-10-26 21:29:09 jason Exp $
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hc.h"
#include "hc_standalone.h"

#define UFRAND()	((float) (rand() & 32767) / 32768.0f)
#define streq(a, b)	(strcmp (a, b) == 0)
#define countof(x)	(sizeof (x)/sizeof (x[0]))

typedef struct {
    float x, y, z;
} Point;

typedef struct {
    float xmin, xmax;
    float ymin, ymax;
    float zmin, zmax;
} Box3D;

typedef int	boolean;
#define true	-1
#define false	0

/* hack, sorry */
static int	xcount,
		ycount;
static HC_KEY	mesh_key;

void untile_mesh (
    HC_KEY      mesh_key,
    int         xnodes,
    int		ynodes) {
    boolean     red, start_red;
    int         row, col;

    start_red = false;
    HC_Open_Geometry (mesh_key);
	for (row = 0; row < xnodes-1; row++) {
	    red = start_red;
	    start_red  = !start_red;

	    for (col = 0; col < ynodes-1; col++) {
		HC_Open_Face (-((row + 1) * xnodes + col + 1));
		    HC_UnSet_One_Color ("faces");
		HC_Close_Face ();
		HC_Open_Face (row * xnodes + col);
		    HC_UnSet_One_Color ("faces");
		HC_Close_Face ();
	    }
	}
    HC_Close_Geometry ();
}

void tile_mesh (
    HC_KEY      mesh_key,
    int         xnodes,
    int		ynodes) {
    boolean     red, start_red;
    int         row, col;

    start_red = false;
    HC_Open_Geometry (mesh_key);
	for (row = 0; row < xnodes-1; row++) {
	    red = start_red;
	    start_red  = !start_red;

	    for (col = 0; col < ynodes - 1; col++) {
		if (red) {
		    HC_Open_Face (-((row + 1) * xnodes + col + 1));
			HC_Set_Color ("faces = red");
		    HC_Close_Face ();
		    HC_Open_Face (row * xnodes + col);
			HC_Set_Color ("faces = red");
		    HC_Close_Face ();
		}
		else {
		    HC_Open_Face (-((row + 1) * xnodes + col + 1));
			HC_Set_Color ("faces = black");
		    HC_Close_Face ();
		    HC_Open_Face (row * xnodes + col);
			HC_Set_Color ("faces = black");
		    HC_Close_Face ();
		}
		red = !red;
	    }
	}
    HC_Close_Geometry ();
}

boolean compute_bbox (
    int		count,
    Point	*points,
    Box3D	*bbox) {

    if (count < 0)
	return false;

    bbox->xmin = bbox->xmax = points->x;
    bbox->ymin = bbox->ymax = points->y;
    bbox->zmin = bbox->zmax = points->z;

    if (--count > 0) do {
	points++;

	if (points->x > bbox->xmax) bbox->xmax = points->x;
	if (points->x < bbox->xmin) bbox->xmin = points->x;
	if (points->y > bbox->ymax) bbox->ymax = points->y;
	if (points->y < bbox->ymin) bbox->ymin = points->y;
	if (points->z > bbox->zmax) bbox->zmax = points->z;
	if (points->z < bbox->zmin) bbox->zmin = points->z;

    } while (--count > 0);

    return true;
}

void compute_mesh (
    float	xstart,
    float	xend,
    int		xnodes,
    float	ystart,
    float	yend,
    int		ynodes,
    float	(*funct)(float x, float y),
    Point	*ipl) {
    Point	*pl = ipl;
    float	x, y;
    float	xinc, yinc;

    xinc = (xend - xstart) / (xnodes - 1);
    yinc = (yend - ystart) / (ynodes - 1);
    pl += xnodes * ynodes;

    for (x = xstart; x < xend + xinc/2.0; x += xinc) {
	for (y = ystart; y < yend + yinc/2.0; y += yinc) {
	    --pl;
	    pl->x = x;
	    pl->y = (*funct) (x, y);
	    pl->z = y;
	}
    }
}

float xfreq, yfreq;

float sin_cos (
    float	x,
    float	y) {

    return ((0.25f + 0.5f * (float)sin(x * 1.5f + 1.0f)) *
	    (float)sin (xfreq * x) *
	    (float)cos (yfreq * y));
}

#define LIGHT1	1
#define LIGHT2	2
#define LIGHT3	3
#define THING	4
#define CAMERA	5
static int move_what = CAMERA;

boolean handle_event (
    char		*event_type) {
    char		key[64];
    static boolean	tiled = false;
    static boolean	cull = true;


    if (strcmp (event_type, "none") == 0) {
	HC_Exit_Program ();
    }

	
    if (streq (event_type, "button")) {
	HC_Show_Button (key);

	if (streq (key, "x") || streq (key, "q")) {
	    return true;
	}
	else if (streq (key, "t")) {
#	    define	NUM_STEPS	18
            int         count = NUM_STEPS;
            float       end, start;

            HC_Show_Time (&start);
            do {
                HC_QRotate_Object ("?mesh", 0.0, 360.0 / NUM_STEPS, 0.0);
                HC_Update_Display ();
            }
            while (--count > 0);
            HC_Show_Time (&end);

	    printf ("\n%6.2f updates per second\n", NUM_STEPS / (end - start));

	}
	else if (streq (key, "T")) {
	    if ((tiled = !tiled) != 0)
		tile_mesh (mesh_key, xcount, ycount);
	    else
		untile_mesh (mesh_key, xcount, ycount);
	}
	else if (streq (key, "c")) {
	    char	current[64];

	    HC_QShow_One_Net_Rendering_Opti ("?mesh",
				"color interpolation", current);

	    if (streq (current, "off")) {
		HC_QSet_Rendering_Options ("?mesh",
					   "color interpolation = (faces = on)");
		printf ("color interpolation on\n");
	    }
	    else {
		HC_QSet_Rendering_Options ("?mesh",
					   "color interpolation = off");
		printf ("color interpolation off\n");
	    }
	}
	else if (streq (key, "f")) {
	    char	current[64];

	    HC_QShow_One_Net_Rendering_Opti ("?mesh",
					     "color index interpolation",
					     current);

	    if (streq (current, "off")) {
		HC_QSet_Rendering_Options ("?mesh",
					   "color index interpolation = (faces = on)");
		printf ("color index interpolation on\n");
	    }
	    else {
		HC_QSet_Rendering_Options ("?mesh",
					"color index interpolation = off");
		printf ("color index interpolation off\n");
	    }
	}
	else if (streq (key, "h")) {
	    char	type[64],
			current[64];

	    HC_QShow_One_Net_Heuristic ("?picture", "hidden surfaces", current);

	    printf ("\nCurrently hidden surfaces = \"%s\"\n", current);
	    printf ("Type:\n");
	    printf ("    h ---- \"hidden surface removal algorithm = hardware\"\n");
	    printf ("    s ---- \"hidden surface removal algorithm = software\"\n");
	    printf ("    z ---- \"hidden surface removal algorithm = z-sort only\"\n");
	    printf ("    b ---- \"hidden surface removal algorithm = software z buffer\"\n");
	    printf ("    o ---- \"hidden surfaces = off\"\n");
	    printf ("Any Key -- No Change\n");

	    HC_Get_Button (type);

	    if (streq (type, "h")) {
		HC_QSet_Heuristics ("?picture", "hidden surfaces");
		HC_QSet_Rendering_Options ("?picture",
					   "hsr algorithm = hardware Z buffer");
		printf ("hidden surfaces = on\n");
	    }
	    else if (streq (type, "s")) {
		HC_QSet_Heuristics ("?picture", "hidden surfaces");
		HC_QSet_Rendering_Options ("?picture",
					   "hsr algorithm = painters");
		printf ("hidden surfaces = software\n");
	    }
	    else if (streq (type, "z")) {
		HC_QSet_Heuristics ("?picture", "hidden surfaces");
		HC_QSet_Rendering_Options ("?picture",
					   "hsr algorithm = z sort only");
		printf ("hidden surfaces = z-sort only\n");
	    }
	    else if (streq (type, "b")) {
		HC_QSet_Heuristics ("?picture", "hidden surfaces");
		HC_QSet_Rendering_Options ("?picture",
					   "hsr algorithm = software z buffer");
		printf ("hidden surfaces = software z buffer\n");
	    }
	    else if (streq (type, "o")) {
		HC_QSet_Heuristics ("?picture", "no hidden surfaces");
		printf ("hidden surfaces = off\n");
	    }
	    else
		printf ("No Change Selected");
	}
	else if (streq (key, "Q")) {
	    char	type[64],
			current[64];

	    HC_QShow_One_Net_Rendering_Opti ("?mesh", "quantization", current);

	    printf ("\nCurrently quantization = \"%s\"\n", current);
	    printf ("Type:\n");
	    printf ("    t ---- \"quantization = threshhold\"\n");
	    printf ("    d ---- \"quantization = dithering\"\n");
	    printf ("    e ---- \"quantization = error diffusion\"\n");
	    printf ("Any Key -- No Change\n");

	    HC_Get_Button (type);

	    if (streq (type, "t")) {
		HC_QSet_Rendering_Options ("?mesh", "quantization = threshold");
		printf ("quantization = threshold\n");
	    }
	    else if (streq (type, "d")) {
		HC_QSet_Rendering_Options ("?mesh", "quantization = dithering");
		printf ("quantization = dithering\n");
	    }
	    else if (streq (type, "e")) {
		HC_QSet_Rendering_Options ("?mesh",
					   "quantization = error diffusion");
		printf ("quantization = error diffusion\n");
	    }
	    else
		printf ("No Change Selected");
	}
	else if (streq (key, "v")) {
	    char	answer[16];
	    char        type[16];

	    printf ("Type:\n");
	    printf ("    f ---- \"toggle faces\"\n");
	    printf ("    e ---- \"toggle edges\"\n");
	    printf ("    m ---- \"toggle markers\"\n");
	    printf ("Any Key -- No Change\n");

	    HC_Get_Button (type);

	    if (streq (type, "f")) {
		HC_QShow_One_Net_Visibility ("?mesh", "faces", answer);

		if (streq (answer, "off")) {
		    HC_QSet_Visibility ("?mesh", "faces = on");
		    printf ("faces visible\n");
		}
		else {
		    HC_QSet_Visibility ("?mesh", "faces = off");
		    printf ("faces invisible\n");
		}
	    }
	    else if (streq (type, "e")) {
		HC_QShow_One_Net_Visibility ("?mesh", "edges", answer);

		if (streq (answer, "off")) {
		    HC_QSet_Visibility ("?mesh", "edges = on");
		    printf ("edges visible\n");
		}
		else {
		    HC_QSet_Visibility ("?mesh", "edges = off");
		    printf ("edges invisible\n");
		}
	    }
	    else if (streq (type, "m")) {
		HC_QShow_One_Net_Visibility ("?mesh", "markers", answer);

		if (streq (answer, "off")) {
		    HC_QSet_Visibility ("?mesh", "markers = on");
		    printf ("markers visible\n");
		}
		else {
		    HC_QSet_Visibility ("?mesh", "markers = off");
		    printf ("markers invisible\n");
		}
	    }
	    else
		printf ("No Change Selected\n");
	}
	else if (streq (key, "n")) {
	    char	answer[16];

	    HC_QShow_One_Net_Visibility ("?normals", "lines", answer);

	    if (streq (answer, "off")) {
		HC_QSet_Visibility ("?normals", "lines = on");
		printf ("normals visible\n");
	    }
	    else {
		HC_QSet_Visibility ("?normals", "lines = off");
		printf ("normals invisible\n");
	    }
	}
	else if (streq (key, "b")) {
	    if ((cull = !cull) != 0) {
		HC_QSet_Heuristics ("?picture", "backplane cull = on");
		printf ("culling on\n");
	    }
	    else {
		HC_QSet_Heuristics ("?picture", "backplane cull = off");
		printf ("culling off\n");
	    }
	    HC_Update_Display ();
	}
	else if (streq (key, "p")) {
	    static boolean	perspective = true;

	    if ((perspective = !perspective) != 0) {
		HC_QSet_Camera_Projection ("?picture", "perspective");
		printf ("perspective camera\n");
	    }
	    else {
		HC_QSet_Camera_Projection ("?picture", "ortho");
		printf ("ortho camera\n");
	    }
	}
	else if (streq (key, "P")) {
	    char	type[64];

	    printf ("Type:\n");
	    printf ("    l ---- left\n");
	    printf ("    r ---- right\n");
	    printf ("Any Key -- off\n");

	    HC_Get_Button (type);

	    if (streq (type, "l")) {
		HC_QSet_Heuristics ("?picture", "polygon handedness = left");
		printf ("polygon handedness left\n");
	    }
	    else if (streq (type, "r")) {
		HC_QSet_Heuristics ("?picture", "polygon handedness = right");
		printf ("polygon handedness right\n");
	    }
	    else {
		HC_QSet_Heuristics ("?picture", "no polygon handedness");
		printf ("polygon handedness off\n");
	    }
	}
	else if (streq (key, "l")) {
	    char	type[4],
			current[64];

	    HC_QShow_One_Net_Rendering_Opti ("?mesh",
					     "lighting interpolation",
					     current);

	    printf ("\nCurrent lighting interpolation is \"%s\"\n", current);
	    printf ("Type:\n");
	    printf ("    n ---- No Lighting Interpolation\n");
	    printf ("    g ---- Gouraud Interpolated LI\n");
	    printf ("    p ---- Phong Interpolated LI\n");
	    printf ("Any Key -- No Change\n");

	    HC_Get_Button (type);

	    if (streq (type, "g"))
		HC_QSet_Rendering_Options ("?mesh", "lighting = (faces = gouraud)");
	    else if (streq (type, "p"))
		HC_QSet_Rendering_Options ("?mesh", "lighting = (faces = phong)");
	    else if (streq (type, "n"))
		HC_QSet_Rendering_Options ("?mesh", "lighting = off");
	    else
		printf ("No change selected\n");

	    HC_QShow_One_Net_Rendering_Opti ("?mesh",
					     "lighting interpolation",
					     current);

	    printf ("Lighting interpolation is now \"%s\"\n\n", current);

	}
        else if (streq (key, "g")) {
            char        vis[4];

            HC_QShow_One_Net_Visibility ("?mesh", "edges", vis);
            if (streq ("off", vis))
                HC_QSet_Visibility ("?mesh", "edges = mesh quads only");
            else
                HC_QSet_Visibility ("?mesh", "edges = off");
        }
        else if (streq (key, "F")) {
            char        vis[4];

            HC_QShow_One_Net_Visibility ("?mesh", "faces", vis);
            if (streq ("off", vis))
                HC_QSet_Visibility ("?mesh", "faces = on");
            else
                HC_QSet_Visibility ("?mesh", "faces = off");
        }
        else if (streq (key, "1")) {
            char        vis[4];

            HC_QShow_One_Net_Visibility ("?picture/light1", "lights", vis);
            if (streq ("on", vis))
                HC_QSet_Visibility ("?picture/light1", "lights = off");
            else
                HC_QSet_Visibility ("?picture/light1", "lights = on");
        }
        else if (streq (key, "2")) {
            char        vis[4];

            HC_QShow_One_Net_Visibility ("?picture/light2", "lights", vis);
            if (streq ("on", vis))
                HC_QSet_Visibility ("?picture/light2", "lights = off");
            else
                HC_QSet_Visibility ("?picture/light2", "lights = on");
        }
        else if (streq (key, "3")) {
            char        vis[4];

            HC_QShow_One_Net_Visibility ("?picture/light3", "lights", vis);
            if (streq ("on", vis))
                HC_QSet_Visibility ("?picture/light3", "lights = off");
            else
                HC_QSet_Visibility ("?picture/light3", "lights = on");
        }
	else if (streq (key, "+")) {
	    char	disp[64];
	    int		new_disp;

	    HC_QShow_One_Net_Rendering_Opti ("?picture",
					     "face displacement",
					     disp);
	    new_disp = atoi(disp) + 1;
	    printf ("New face displacement = %d\n", new_disp);
	    sprintf (disp, "face displacement = %d", new_disp);
	    HC_QSet_Rendering_Options ("?picture", disp);
	}
	else if (streq (key, "-")) {
	    char	disp[64];
	    int		new_disp;

	    HC_QShow_One_Net_Rendering_Opti ("?picture",
					     "face displacement",
					     disp);
	    new_disp = atoi(disp) - 1;
	    printf ("New face displacement = %d\n", new_disp);
	    sprintf (disp, "face displacement = %d", new_disp);
	    HC_QSet_Rendering_Options ("?picture", disp);
	}
	else if (streq (key, "r")) {
	    printf ("Reading Metafile\n");
	    HC_Flush_Segment ("?picture");
		HC_Read_Metafile ("z", "?picture", "");
	}
	else if (streq (key, "w")) {
	    printf ("Writing Metafile\n");
		HC_Write_Metafile ("?picture", "z", "");
	}
	else if (streq (key, "G")) {
	    char	val[64];

            HC_QShow_One_Net_Driver_Option ("?picture",
					    "gamma correction",
					    val);
            if (streq ("on", val)) {
		printf ("turning gamma correction off\n");
                HC_QSet_Driver_Options ("?picture", "no gamma correction");
	    }
            else {
		printf ("turning gamma correction on\n");
                HC_QSet_Driver_Options ("?picture", "gamma correction");
	    }
	}
	else if (streq (key, "d")) {
	    char	val[64];

            HC_QShow_One_Net_Driver_Option ("?picture",
					    "double-buffering",
					    val);
            if (streq ("on", val)) {
		printf ("turning double buffering off\n");
                HC_QSet_Driver_Options ("?picture", "no double-buffering");
	    }
            else {
		printf ("turning double buffering on\n");
                HC_QSet_Driver_Options ("?picture", "double-buffering");
	    }
	}
	else if (streq (key, "s")) {
	    char	val[64];

            HC_QShow_One_Net_Driver_Option ("?picture", "light scaling", val);

            if (streq ("off", val))
                HC_QSet_Driver_Options ("?picture", "light scaling = 0.9");
            else {
                HC_QSet_Driver_Options ("?picture", "no light scaling");
	    }
	}
	else if (streq (key, "i")) {
	    HC_QZoom_Camera ("?picture", 1.5);
	}
	else if (streq (key, "o")) {
	    HC_QZoom_Camera ("?picture", 0.75);
	}
	else if (streq (key, "z")) {
	    static boolean	flat = false;
	    if ((flat = !flat) != 0)
		HC_QScale_Object ("?mesh", 1.0, 0.0, 1.0);
	    else
		HC_QUnSet_Modelling_Matrix ("?mesh");
	}
	else if (streq (key, "m")) {
	    char	type[64];

	    printf ("enter object to move (1, 2, 3, t, o, c)\n");
	    HC_Get_Button (type);

	    if (streq (type, "1")) {
		move_what = LIGHT1;
		printf ("moving light 1\n");
	    }
	    else if (streq (type, "2")) {
		move_what = LIGHT2;
		printf ("moving light 2\n");
	    }
	    else if (streq (type, "3")) {
		move_what = LIGHT3;
		printf ("moving light 3\n");
	    }
	    else if (streq (type, "t")) {
		move_what = THING;
		printf ("moving thing\n");
	    }
	    else if (streq (type, "o")) {
		move_what = THING;
		printf ("moving thing\n");
	    }
	    else if (streq (type, "c")) {
		move_what = CAMERA;
		printf ("moving camera\n");
	    }
	}
	else if (streq (key, "left arrow")) {
	    switch (move_what) {
		case LIGHT1:
		    HC_QRotate_Object ("?light1", 0.0, -5.0, 0.0);
		    break;
		case LIGHT2:
		    HC_QRotate_Object ("?light2", 0.0, -5.0, 0.0);
		    break;
		case LIGHT3:
		    HC_QRotate_Object ("?light3", 0.0, -5.0, 0.0);
		    break;
		case THING:
		    HC_QRotate_Object ("?mesh", 0.0, -5.0, 0.0);
		    break;
		case CAMERA:
		    HC_QOrbit_Camera ("?picture", -5.0, 0.0);
		    break;
	    }
	}
	else if (streq (key, "right arrow")) {
	    switch (move_what) {
		case LIGHT1:
		    HC_QRotate_Object ("?light1", 0.0, 5.0, 0.0);
		    break;
		case LIGHT2:
		    HC_QRotate_Object ("?light2", 0.0, 5.0, 0.0);
		    break;
		case LIGHT3:
		    HC_QRotate_Object ("?light3", 0.0, 5.0, 0.0);
		    break;
		case THING:
		    HC_QRotate_Object ("?mesh", 0.0, 5.0, 0.0);
		    break;
		case CAMERA:
		    HC_QOrbit_Camera ("?picture", 5.0, 0.0);
		    break;
		}
	}
	else if (streq (key, "up arrow")) {
	    switch (move_what) {
		case LIGHT1:
		    HC_QRotate_Object ("?light1", 5.0, 0.0, 0.0);
		    break;
		case LIGHT2:
		    HC_QRotate_Object ("?light2", 5.0, 0.0, 0.0);
		    break;
		case LIGHT3:
		    HC_QRotate_Object ("?light3", 5.0, 0.0, 0.0);
		    break;
		case THING:
		    HC_QRotate_Object ("?mesh", 5.0, 0.0, 0.0);
		    break;
		case CAMERA:
		    HC_QOrbit_Camera ("?picture", 0.0, 5.0);
		    break;
		}
	}
	else if (streq (key, "down arrow")) {
	    switch (move_what) {
		case LIGHT1:
		    HC_QRotate_Object ("?light1", -5.0, 0.0, 0.0);
		    break;
		case LIGHT2:
		    HC_QRotate_Object ("?light2", -5.0, 0.0, 0.0);
		    break;
		case LIGHT3:
		    HC_QRotate_Object ("?light3", -5.0, 0.0, 0.0);
		    break;
		case THING:
		    HC_QRotate_Object ("?mesh", -5.0, 0.0, 0.0);
		    break;
		case CAMERA:
		    HC_QOrbit_Camera ("?picture", 0.0, -5.0);
		    break;
		}
	}
	else {
	    printf ("I don't know that key yet. Here's what I do know:\n");
	    printf ("File\tx -- exit program\n");
	    printf ("\tq -- exit program\n");
	    printf ("\tr -- read metafile z.hmf\n");
	    printf ("\tw -- write metafile z.hmf\n");
	    printf ("\tt -- time %d step rotation\n", NUM_STEPS);
	    printf ("\nGeom\tb -- toggle backplane cull\n");
	    printf ("\tP -- specify polygon handedness\n");
	    printf ("\tF -- toggle grid face visibility\n");
	    printf ("\tg -- toggle grid edge visibility\n");
	    printf ("\tv -- toggle marker visibility\n");
	    printf ("\tn -- toggle normals visibility\n");
	    printf ("\tT -- Tile mesh (alternate face colors - may need to hit f to see)\n");
	    printf ("\tz -- flatten z values\n");
	    printf ("\nLights\tl -- specify lighting model\n");
	    printf ("\ts -- toggle light scaling (0.9 or off)\n");
	    printf ("\t1 -- toggle light 1\n");
	    printf ("\t2 -- toggle light 2\n");
	    printf ("\t3 -- toggle light 3\n");
	    printf ("\nRender\tp -- perspective or orthographic\n");
	    printf ("\th -- specify hidden surface algorithm\n");
	    printf ("\tc -- toggle color interpolation\n");
	    printf ("\tf -- toggle color index interpolation\n");
	    printf ("\tQ -- specify quantization algorithm\n");
	    printf ("\td -- toggle double-buffering\n");
	    printf ("\tG -- toggle gamma correction\n");
	    printf ("\nMove\tm -- specify object associated with future move commands\n");
	    printf ("\ti -- zoom in\n");
	    printf ("\to -- zoom out\n");
	    printf ("\tleft arrow\n");
	    printf ("\tright arrow\n");
	    printf ("\tup arrow\n");
	    printf ("\tdown arrow\n");
	}
	return false;
    }
    else if (streq (event_type, "selection")) {
	HC_KEY	key;
	int	off1, off2, off3;
	char	type[128];
	char	string[128];
	float	xw, yw, x, y, z;

	HC_Show_Selection_Element (&key, &off1, &off2, &off3);
	HC_Show_Key_Type (key, type);
	HC_Show_Selection_Location (&xw, &yw, &x, &y, &z);

	HC_Open_Segment ("?mesh/labels");
	    sprintf (string, "%d", off3);
	    HC_Insert_Marker (x, y, z);
	HC_Close_Segment ();

	if (streq (type, "mesh")) {
	    HC_Open_Geometry (key);
		HC_Open_Face (off3);
		    HC_Set_Color ("faces = white");
		HC_Close_Face ();
	    HC_Close_Geometry ();
	}

	printf ("A \"%s\" was selected, key = %p, offsets [%d, %d, %d]",
		type, (void*)key, off1, off2, off3);
	printf (", at [%f, %f] [%f, %f, %f]\n", xw, yw, x, y, z);
	return false;
    }
    else
	return false;
}

#define NSCALE 0.075

void add_normals (
    HC_KEY	mesh_key,
    int		vcount,
    Point	*points) {
    int		vertex;
    float	x, y, z;

    HC_Open_Segment ("?mesh/normals");
	HC_Set_Visibility ("everything = off");
	HC_Set_Color ("lines = red");
	HC_Open_Geometry (mesh_key);
	    for (vertex = 0; vertex < vcount; vertex++) {
		HC_Open_Vertex (vertex);
		HC_Show_Net_Normal (&x, &y, &z);
		HC_Close_Vertex ();

		HC_QInsert_Line ("?mesh/normals",
				 points->x, points->y, points->z,
				 points->x - NSCALE * x,
				 points->y - NSCALE * y,
				 points->z - NSCALE * z);
		points++;
	    }
	HC_Close_Geometry ();
    HC_Close_Segment ();
}

int main (
    int		argc,
    char	**argv) {
    Point	*points;
    char	event[128];
    int		vcount;
    Box3D	bbox;

    if (argc < 2) {
	xcount = ycount = 30;
    }
    else if (argc == 2) {
	xcount = ycount = atoi (argv[1]);
    }
    else {
	xcount = atoi (argv[1]);
	ycount = atoi (argv[2]);
    }
    vcount = xcount*ycount;
    points = (Point *)malloc (vcount * sizeof (Point));

    if (argc < 4) {
	xfreq = yfreq = (float)5;
    }
    else if (argc == 4) {
	xfreq = yfreq = (float)atoi (argv[3]);
    }
    else {
	xfreq = (float)atoi (argv[3]);
	yfreq = (float)atoi (argv[4]);
    }

    HC_Open_Segment ("?picture");
	HC_Define_System_Options ("no bounding volumes");
	HC_Set_Visibility ("edges = off, faces = on");
	HC_Set_Selectability ("geometry = on, windows = off");
	HC_Set_Marker_Symbol (".");
	HC_Set_Color ("text = white, windows = gray, window contrast = red");
	HC_Set_Color ("faces = cerulean, edges = black, markers = white");

        HC_Open_Segment ("light1");
            HC_Insert_Distant_Light (0.0, 1.0, 0.0);
            HC_Set_Visibility ("lights = off");
        HC_Close_Segment ();
	HC_Define_Alias ("?light1", "?picture/light1");

        HC_Open_Segment ("light2");
            HC_Insert_Distant_Light (1.0, 1.0, -1.0);
            HC_Set_Visibility ("lights = on");
        HC_Close_Segment ();
	HC_Define_Alias ("?light2", "?picture/light2");

        HC_Open_Segment ("light3");
            HC_Insert_Distant_Light (-1.0, 1.0, -1.0);
            HC_Set_Color ("lights = blue");
            HC_Set_Visibility ("lights = off");
        HC_Close_Segment ();
	HC_Define_Alias ("?light3", "?picture/light3");

	HC_Open_Segment ("mesh");
	    HC_Define_Alias ("?mesh", "?picture/mesh");
	    compute_mesh (-1.0f, 1.0f, xcount, -1.0f, 1.0f,
			  ycount, sin_cos, points);
	    compute_bbox (vcount, points, &bbox);
	    mesh_key = HC_KInsert_Mesh (xcount, ycount, points);
	    HC_Set_Rendering_Options ("color interpolation = off");
	    HC_Set_Rendering_Options ("color index interpolation = off");
	    HC_Set_Rendering_Options ("color index interpolation = (faces = on)");

	    add_normals (mesh_key, vcount, points);
	    HC_Define_Alias ("?normals", "?mesh/normals");

	    {
		float	*findices, *fiptr;
		Point	*vptr = &points[0];
		float	cscale;
		int	row, col;
		int	fcyc;
		int	ccount;

		/* put in a rainbow map */
		HC_Set_Color_Map ("red, green, blue");
		ccount = 3;

		/* compute and set FIndices */
		findices = (float *)malloc (vcount*sizeof (float));

		fcyc = 1;
		row = 0;
		fiptr = findices;
		cscale = (float) (fcyc * (ccount + 1)) / (bbox.ymax - bbox.ymin);
		do {
		    col = 0;
		    do {
			*fiptr++= (vptr->y - bbox.ymin) * cscale;
			vptr++;
		    }
		    while (++col < ycount);
		}
		while (++row < xcount);

		HC_MSet_Vertex_Colors_By_FIndex (mesh_key, "faces, edges",
						 0, vcount, findices);
		HC_Set_Visibility ("markers = off");
		free (findices);
	    }

	    HC_Open_Segment ("labels");
		HC_Set_Text_Font ("size = 0.007 sru");
	    HC_Close_Segment ();
	HC_Close_Segment ();

	HC_Enable_Button_Events ("?keyboard", "anything");
	HC_Enable_Selection_Events ("?locater", "?picture");
	do {
	    HC_Await_Event (event);
	} while (!handle_event (event));
    HC_Close_Segment ();
    HC_Exit_Program ();
    return 0;
}
