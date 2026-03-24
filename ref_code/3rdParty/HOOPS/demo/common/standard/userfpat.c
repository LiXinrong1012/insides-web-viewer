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
 * $Id: userfpat.c,v 1.6 2008-02-06 00:26:12 jason Exp $
 */

#ifdef WINDOWS_SYSTEM
#undef WINDOWS_SYSTEM
#endif

#include "hc.h"
#include "hic.h"

#define _ 0	/* _ provides better visual contrast in the source */

unsigned char honeycomb[] = {
	_,_,_,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,
	_,_,1,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,
	_,_,1,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,
	_,1,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,
	_,1,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,
	1,_,_,_,_,_,_,_,_,_,_,_,1,1,1,1,1,1,
	_,1,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,
	_,1,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,
	_,_,1,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,
	_,_,1,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,
};

unsigned char wave[] = {
	_,_,_,_,1,1,1,_,_,_,
	_,_,_,1,_,_,_,1,_,_,
	_,_,1,_,_,_,_,_,1,_,
	1,1,_,_,_,_,_,_,_,1,
	_,_,_,_,_,_,_,_,_,_,
};

unsigned char dna8by8[] = {
	_,_,_,1,1,_,_,_,
	_,_,1,_,_,1,_,_,
	_,1,_,_,_,_,1,_,
	_,_,1,_,_,1,_,_,
	_,_,_,1,1,_,_,_,
	_,_,1,_,_,1,_,_,
	_,_,1,_,_,1,_,_,
	_,_,1,_,_,1,_,_,
};

unsigned char marsh[] = {
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,1,_,_,1,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,1,_,_,1,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,1,_,_,1,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,1,_,1,_,1,_,_,1,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,_,1,_,1,_,1,_,_,1,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,1,_,1,_,1,_,1,_,1,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,1,_,_,1,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,1,_,_,1,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,1,_,_,1,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,1,_,_,1,_,1,_,1,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,1,_,_,1,_,1,_,1,_,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,1,_,1,_,1,_,1,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,
};

unsigned char washer[] = {
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,_,_,
	_,_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,_,
	_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,
	_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,
	_,_,_,_,1,1,1,1,1,1,1,1,1,_,_,_,_,1,1,1,1,1,1,1,1,1,_,_,_,_,
	_,_,_,_,1,1,1,1,1,1,1,1,_,_,_,_,_,_,1,1,1,1,1,1,1,1,_,_,_,_,
	_,_,_,_,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,_,_,_,_,
	_,_,_,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,_,_,_,
	_,_,_,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,_,_,_,
	_,_,_,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,_,_,_,
	_,_,_,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,_,_,_,
	_,_,_,_,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,_,_,_,_,
	_,_,_,_,1,1,1,1,1,1,1,1,_,_,_,_,_,_,1,1,1,1,1,1,1,1,_,_,_,_,
	_,_,_,_,1,1,1,1,1,1,1,1,1,_,_,_,_,1,1,1,1,1,1,1,1,1,_,_,_,_,
	_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,
	_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,
	_,_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,_,
	_,_,_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,1,1,1,1,1,1,1,1,1,1,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,1,1,1,1,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
};


static	HIC_User_Face_Pattern	const *honeycomb_pat = 0;

void face_with_honeycomb (HIC_Rendition const *r, int count, HIC_DC_Point const*p) {
    if (!honeycomb_pat) {
		honeycomb_pat = HIC_New_User_Face_Pattern (r, 10, 18, honeycomb, 0);
    }

    r = HIC_New_Rendition (r);
	HIC_Set_User_Face_Pattern (r, honeycomb_pat);
	HIC_Draw_DC_Face (r, count, p);
    HIC_Free_Rendition (r);
}

void colorized_face_with_honeycomb (HIC_Rendition const*r, int count,
				    HIC_DC_Point const*p, HIC_RGBAS32 const*color) {
    if (!honeycomb_pat) {
		honeycomb_pat = HIC_New_User_Face_Pattern (r, 10, 18, honeycomb, 0);
    }

    r = HIC_New_Rendition (r);
	HIC_Set_User_Face_Pattern (r, honeycomb_pat);
	HIC_Draw_DC_Colorized_Face (r, count, p, color);
    HIC_Free_Rendition (r);
}


static HIC_User_Face_Pattern	const *wave_pat = 0;

void face_with_waves (HIC_Rendition const*r, int count, HIC_DC_Point const*p) {
    if (!wave_pat) {
		wave_pat = HIC_New_User_Face_Pattern (r, 5, 10, wave, 0);
    }

    r = HIC_New_Rendition (r);
	HIC_Set_User_Face_Pattern (r, wave_pat);
	HIC_Draw_DC_Face (r, count, p);
    HIC_Free_Rendition (r);
}


static HIC_User_Face_Pattern	const *dna_pat = 0;

void window_with_dna8by8 (HIC_Rendition const*r, HIC_Int_Rectangle const*extent) {
    if (!dna_pat) {
	dna_pat = HIC_New_User_Face_Pattern (r, 8, 8, dna8by8, 0);
    }

    r = HIC_New_Rendition (r);
	HIC_Set_User_Window_Pattern (r, dna_pat);
	HIC_Draw_Window (r, extent);
    HIC_Free_Rendition (r);
}


static HIC_User_Face_Pattern	const *marsh_pat = 0;

void face_with_marsh (HIC_Rendition const*r, int count, HIC_DC_Point const*p) {
    if (!marsh_pat) {
	marsh_pat = HIC_New_User_Face_Pattern (r, 26, 26, marsh, 0);
    }

    r = HIC_New_Rendition (r);
	HIC_Set_User_Face_Pattern (r, marsh_pat);
	HIC_Draw_DC_Face (r, count, p);
    HIC_Free_Rendition (r);
}


static HIC_User_Face_Pattern	const *washer_pos_pat = 0;

void face_as_washers (HIC_Rendition const*r, int count, HIC_DC_Point const*p) {
    if (!washer_pos_pat) {
	washer_pos_pat = HIC_New_User_Face_Pattern (r, 30, 30, washer, 1);
    }

    r = HIC_New_Rendition (r);
	HIC_Set_User_Face_Pattern (r, washer_pos_pat);
	HIC_Draw_DC_Face (r, count, p);
    HIC_Free_Rendition (r);
}


static HIC_User_Face_Pattern	const *washer_neg_pat = 0;

void face_with_washer_holes (HIC_Rendition const*r, int count, HIC_DC_Point const*p) {
    if (!washer_neg_pat) {
	washer_neg_pat = HIC_New_User_Face_Pattern (r, 30, 30, washer, 2);
    }

    r = HIC_New_Rendition (r);
	HIC_Set_User_Face_Pattern (r, washer_neg_pat);
	HIC_Draw_DC_Face (r, count, p);
    HIC_Free_Rendition (r);
}


void free_all_fpatterns() {
    HIC_Free_User_Face_Pattern (honeycomb_pat);
    HIC_Free_User_Face_Pattern (wave_pat);
    HIC_Free_User_Face_Pattern (marsh_pat);
    HIC_Free_User_Face_Pattern (dna_pat);
    HIC_Free_User_Face_Pattern (washer_pos_pat);
    HIC_Free_User_Face_Pattern (washer_neg_pat);
}


float	l[] =  {-1.0f, -0.5f, 0.1f,  0.0f, -0.5f, 0.1f , -0.5f,  0.7f, 0.1f},
	r[] =  { 1.0f,  0.5f, 0.1f,  0.0f,  0.5f, 0.1f ,  0.5f, -0.7f, 0.1f},
	cr[] = { 0.0f, -0.5f, 0.1f, -0.5f,  0.7f, 0.1f ,
	         0.0f,  0.0f, 0.1f,  0.5f, -0.7f, 0.1f},
	cl[] = { 0.0f,  0.0f, 0.1f, -0.5f,  0.7f, 0.1f ,
	         0.0f,  0.5f, 0.1f,  0.5f, -0.7f, 0.1f},
	ol[] = {-1.1f, -0.2f, 0.0f, -1.1f,  0.2f, 0.0f ,
		 0.0f,  0.2f, 0.0f,  0.0f, -0.2f, 0.0f},
	or[] = { 0.0f, -0.2f, 0.0f,  0.0f,  0.2f, 0.0f ,
		 1.1f,  0.2f, 0.0f,  1.1f, -0.2f, 0.0f};

int main () {
    HC_Define_Callback_Name ("honeycomb", face_with_honeycomb);
    HC_Define_Callback_Name ("colorized honeycomb",
			     colorized_face_with_honeycomb);
    HC_Define_Callback_Name ("waves", face_with_waves);
    HC_Define_Callback_Name ("dna8by8", window_with_dna8by8);
    HC_Define_Callback_Name ("marsh", face_with_marsh);
    HC_Define_Callback_Name ("washers", face_as_washers);
    HC_Define_Callback_Name ("holes", face_with_washer_holes);

    HC_Open_Segment ("?Picture");
	HC_Set_Color ("edges = pink");
	HC_Set_Callback ("draw window = dna8by8");

	HC_Open_Segment ("left");
	    HC_Insert_Polygon (3, l);
	    HC_Set_Color ("face = yellow, face contrast = black");
	    HC_Set_Callback ("draw dc face = honeycomb");
	    HC_Set_Callback ("draw dc colorized face = colorized honeycomb");
	HC_Close_Segment ();

	HC_Open_Segment ("right");
	    HC_Insert_Polygon (3, r);
	    HC_Set_Color ("face = dark blue");
	    HC_Set_Callback ("draw dc face = waves");
	HC_Close_Segment ();

	HC_Open_Segment ("center-right");
	    HC_Insert_Polygon (4, cr);
	    HC_Set_Color ("face = red, face contrast = yellow");
	HC_Close_Segment ();

	HC_Open_Segment ("center-left");
	    HC_Insert_Polygon (4, cl);
	    HC_Set_Color ("face = black, face contrast = green");
	    HC_Set_Callback ("draw dc face = marsh");
	HC_Close_Segment ();

	HC_Open_Segment ("over-left");
	    HC_Insert_Polygon (4, ol);
	    HC_Set_Color ("face = gray, face contrast = red");
	    HC_Set_Callback ("draw dc face = washers");
	HC_Close_Segment ();

	HC_Open_Segment ("over-right");
	    HC_Insert_Polygon (4, or);
	    HC_Set_Color ("face = gray, face contrast = red");
	    HC_Set_Callback ("draw dc face = holes");
	HC_Close_Segment ();

	HC_Insert_Text (0.0, 0.9, 0.0, "back: honeycomb, red, marsh, waves");
	HC_Insert_Text (0.0, 0.8, 0.0, "front: washers, holes");
   	HC_Pause ();

	HC_Insert_Text (0.0, 0.7, 0.0, "wide edges");
   	HC_Set_Edge_Weight (3.0);
   	HC_Pause ();

	HC_Flush_Contents (".", "text");
	HC_Insert_Text (0.0, 0.9, 0.0, "back: honeycomb, red, black, blue");
	HC_Insert_Text (0.0, 0.8, 0.0, "front: gray, gray");
	HC_Insert_Text (0.0, 0.7, 0.0, "wide edges");
   	HC_Insert_Distant_Light (-1.0, 1.0, -3.0);
   	HC_Pause ();
    HC_Close_Segment ();

    free_all_fpatterns();
    HC_Exit_Program ();
    return 0;
}
