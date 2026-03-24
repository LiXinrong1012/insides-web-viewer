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
 * $Id: 3dselect.c,v 1.4 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define	null	(char *) 0
#define ANGLE	(double)15
#define MOVE	(double)0.2

#define RING_0_HEIGHT  -0.6f
#define RING_1_HEIGHT  -0.3f
#define RING_2_HEIGHT   0.0f
#define RING_3_HEIGHT   0.4f
#define RADIUS_0 0.25f
#define RADIUS_1 0.25f
#define RADIUS_2 0.15f
#define RADIUS_3 0.10f
#define NUM_PER_RING   12
#define NUM_RINGS	4

#define COSD(x) cos((x)/(double)180 * 3.14159)
#define SIND(x) sin((x)/(double)180 * 3.14159)


typedef struct {
    float    x, y, z;
} Vector;


void set_attributes (void) {
    HC_Open_Segment ("?picture");
	HC_Set_Color ("markers = red");
	HC_Set_User_Value (0);
	HC_Set_Text_Font ("size = .02 sru");
    HC_Close_Segment ();

    HC_Open_Segment ("?picture/object");
	HC_Set_Visibility ("text = off");
	HC_Set_Selectability ("polylines = on");
	HC_Set_Window_Frame ("off");
    HC_Close_Segment ();

    HC_Create_Segment ("?picture/message");

    HC_Create_Segment ("?picture/object/markers");
}

#define UNREFERENCED(val) val = (double)0;

void rotate_x (
    double	x) {

    HC_QRotate_Object ("?picture/object",
		       x * ANGLE,
		       (double)0,
		       (double)0);
}

void rotate_y (
    double	x) {

    HC_QRotate_Object ("?picture/object",
		       (double)0,
		       x * ANGLE,
		       (double)0);
}

void rotate_z (
    double	x) {

    HC_QRotate_Object ("?picture/object",
		       (double)0,
		       (double)0,
		       x * ANGLE);
}

void move_x (
    double	x) {

    HC_QTranslate_Object ("?picture/object",
			  x * MOVE,
			  (double)0,
			  (double)0);
}

void move_y (
    double	x) {

    HC_QTranslate_Object ("?picture/object",
			  (double)0,
			  x * MOVE,
			  (double)0);
}

void move_z (
    double	x) {

    HC_QTranslate_Object ("?picture/object",
			  (double)0,
			  (double)0,
			  x * (double)2 * MOVE);
}

void reset (
    double	x) {

    UNREFERENCED (x);
    HC_QUnSet_Modelling_Matrix ("?picture/object");
}

void delete_all (
    double	x) {

    UNREFERENCED (x);
    HC_Flush_Segment ("?picture/object/markers");
}

void quit (
    double	x) {

    UNREFERENCED (x);
    HC_Exit_Program ();
}

void message (
    double	x) {

    UNREFERENCED (x);
    HC_Flush_Segment ("?picture/message");
}

void pick_object (
    double	x) {
    HC_KEY	key;
    int		offset1, offset2;
    char	buf[128];
    Vector	point;
    char	type[32];

    UNREFERENCED (x);

    HC_Show_Selection_Item (&key, &offset1, &offset2);
    HC_Show_Key_Type (key, type);

    HC_Open_Segment ("?picture/message");
	HC_Flush_Segment (".");

	if (strcmp (type, "polyline") == 0) {
	    sprintf (buf, "key = %08lX offset = %d offset = %d",
			   key, offset1, offset2);

	    HC_Show_Partial_Polyline (key, offset1, 1, &point);
	    HC_Open_Segment ("?picture/object/markers");
		HC_Insert_Marker (point.x, point.y, point.z);
	    HC_Close_Segment ();
	}
	else
	    sprintf (buf, "No match --- No key returned");

	HC_Insert_Text (0.0, 0.0, 0.0, buf);
    HC_Close_Segment ();
}

void add_button (
    float	left, 
    float	right, 
    float	bottom, 
    float	top,
    char	*title, 
    void	(*action) (double)) {
    char	segname[80];

    sprintf (segname, "?picture/%s", title);

    HC_Open_Segment (segname);
	HC_Set_User_Value ((HC_POINTER_SIZED_INT)action);
	HC_Set_Window ((double)left,
		       (double)right, 
		       (double)bottom, 
		       (double)top);
	HC_Insert_Text (0.0, 0.0, 0.0, title);
    HC_Close_Segment ();
}

void build_menu (void) {
    add_button (-0.95f, 0.95f, -0.45f, -0.35f, "message", message);

    add_button (-1.0f, 1.0f, -0.30f, 1.0f, "object", pick_object);

    add_button (-0.95f, -0.65f, -0.95f, -0.75f, "Rotate X", rotate_x);
    add_button (-0.60f, -0.30f, -0.95f, -0.75f, "Rotate Y", rotate_y);
    add_button (-0.25f, 0.05f, -0.95f, -0.75f, "Rotate Z", rotate_z);

    add_button (-0.95f, -0.65f, -0.70f, -0.50f, "Move X", move_x);
    add_button (-0.60f, -0.30f, -0.70f, -0.50f, "Move Y", move_y);
    add_button (-0.25f, 0.05f, -0.70f, -0.50f, "Move Z", move_z);

    add_button (0.10f,  0.40f, -0.95f, -0.75f, "Delete All", delete_all);
    add_button (0.10f,  0.40f, -0.70f, -0.50f, "Reset", reset);

    add_button (0.45f,  0.75f, -0.95f, -0.75f, "Quit",  quit);
}

void check_user_input (void) {
    char	segname[128];
    char	fullname[128];
    void	(*action) (double);

    /* make Selection processing continue steadily through the Get_Wakeup's */
    HC_Enable_Selection_Events ("?picture", "?locater");

    /* get events */
    for (;;) {
	HC_Get_Selection (segname);
	HC_Show_Selection_Pathname (fullname);
	HC_QShow_User_Value (fullname, (HC_POINTER_SIZED_INT *)&action);

	if (action != 0) {
	    float	x, y, junk;

	    HC_Show_Selection_Location (&x, &y, &junk, &junk, &junk);

	    if (strcmp (segname, "object") == 0) {
		(*action) ((double)x);
	    }
	    else {
		HC_QSet_Color (fullname, "text = red");
		HC_Get_Wakeup (0.05);
		(*action) ((double)x);
		HC_QSet_Color (fullname, "text = black");
	    }
	}
    }
}

void build_object (void) {
    int		i, j;
    float	r[NUM_RINGS];
    float	h[NUM_RINGS];
    Vector	points[NUM_RINGS][NUM_PER_RING];

    r[0] = RADIUS_0;
    r[1] = RADIUS_1;
    r[2] = RADIUS_2;
    r[3] = RADIUS_3;

    h[0] = RING_0_HEIGHT;
    h[1] = RING_1_HEIGHT;
    h[2] = RING_2_HEIGHT;
    h[3] = RING_3_HEIGHT;

    HC_Open_Segment ("?picture/object");
    HC_Set_Heuristics ("no hidden surfaces");
    for (i = 0; i < NUM_RINGS; ++i) {
	HC_Restart_Ink ();
	for (j = 0; j < NUM_PER_RING; ++j) {
	    points[i][j].x = (float)((double)r[i] *
				     COSD ((double)j *
					   (double)(360/NUM_PER_RING)));
	    points[i][j].y = h[i];
	    points[i][j].z = (float)((double)r[i] *
				     SIND ((double)j *
					   (double)(360/NUM_PER_RING)));
	    HC_Insert_Ink (points[i][j].x, points[i][j].y, points[i][j].z);
	}
	HC_Insert_Ink (points[i][0].x, points[i][0].y, points[i][0].z);
    }

    for (j = 0; j < NUM_PER_RING; ++j) {
	HC_Restart_Ink ();
	for (i = 0; i < NUM_RINGS; ++i) {
	    HC_Insert_Ink (points[i][j].x, points[i][j].y, points[i][j].z);
	}
    }

    HC_Close_Segment ();
}

int main () {
    set_attributes ();

    build_menu ();

    build_object ();

    check_user_input ();

    return 0;
}
