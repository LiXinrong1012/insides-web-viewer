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
 * $Id: dialobox.c,v 1.4 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdio.h>
#include <string.h>
#define streq(a, b) (strcmp(a, b) == 0)

typedef struct {
   float   r, g, b;
}  RGB_Color;

void fill_slider (
   char			     *segment,
   float		     value) {
   struct {float x, y, z;}   pts[4];
   char                      readout[64],
                             value_text[12];

   sprintf (readout, "%s readout", segment);
   sprintf (value_text, "%.2f", value);
   HC_Open_Segment (readout);
      HC_Flush_Geometry (".");
      HC_Insert_Text (0.0, 0.0, 0.0, value_text);
   HC_Close_Segment ();

   value = -1.0f + 2.0f * value;
   HC_Open_Segment (segment);
      HC_Flush_Geometry (".");

      if (value != -1.0f)  {
          pts[0].x = -1.0f; pts[0].y = -1.0f;  pts[0].z = 0.0f;
          pts[1].x = -1.0f; pts[1].y = value; pts[1].z = 0.0f;
          pts[2].x =  1.0f; pts[2].y = value; pts[2].z = 0.0f;
          pts[3].x =  1.0f; pts[3].y = -1.0f;  pts[3].z = 0.0f;
          HC_Insert_Polygon (4, pts);
      }
   HC_Close_Segment ();
}

void make_label (
   char   *name,
   float   left,
   float   right,
   float   bottom,
   float   top) {
   char   buf [100];

   sprintf (buf, "%s label", name);
   HC_Open_Segment (buf);
      HC_Set_Window ((double)left,
		     (double)right, 
		     (double)bottom, 
		     (double)top);
      HC_Insert_Text (0.0, 0.0, 0.0, name);
   HC_Close_Segment ();
}

void make_indicator (
   char   *name,
   float   left,
   float   right,
   float   bottom,
   float   top) {

   HC_Open_Segment (name);
      HC_Set_Camera_Projection ("stretched");
      HC_Set_Window (left, right, bottom, top);
      HC_Set_Color (name);
   HC_Close_Segment ();
}

void make_readout (
   char   *name,
   float   left,
   float   right,
   float   bottom,
   float   top) {
   char    buf[100];

   sprintf (buf, "%s readout", name);
   HC_Open_Segment (buf);
      HC_Set_Window ((double)left,
		     (double)right, 
		     (double)bottom, 
		     (double)top);
   HC_Close_Segment ();
}

int main () {
   char  colorname[100];

   HC_Open_Segment ("?picture");
      HC_Open_Segment ("object");
	 strcpy(colorname, "black");  /*  set the initial edge color string  */
	 HC_Set_Color ("black");
         HC_Set_Visibility ("faces = off");
         HC_Set_Heuristics ("no hidden surfaces");
         HC_Set_Camera_By_Volume ("perspective", -1.2, 1.2,
                                                 -1.2, 1.2);
         HC_Rotate_Object (-110.0, 0.0, 0.0);
         HC_Read_Metafile ("champagn", ".", "");
      HC_Close_Segment ();

      HC_Define_Alias ("?color box", "?picture/color box");
      HC_Open_Segment ("?color box");
         HC_Set_Window (-0.8, 0.8, -0.6, 0.6);
         make_label ("R", -0.6f, -0.4f, 0.57f, 0.77f);
         make_label ("G", -0.1f,  0.1f, 0.57f, 0.77f);
         make_label ("B",  0.4f,  0.6f, 0.57f, 0.77f);

         make_indicator ("red", -0.6f, -0.4f, -0.3f, 0.6f);
         make_indicator ("green", -0.1f, 0.1f, -0.3f, 0.6f);
         make_indicator ("blue", 0.4f, 0.6f, -0.3f, 0.6f);

         make_readout ("red", -0.7f, -0.3f, -0.5f, -0.3f);
         make_readout ("green", -0.2f, 0.2f, -0.5f, -0.3f);
         make_readout ("blue", 0.3f, 0.7f, -0.5f, -0.3f);

         HC_Open_Segment ("Apply");
            HC_Set_Window (-0.7, -0.35, -0.9, -0.75);
            HC_Insert_Text (0.0, 0.0, 0.0, "Apply");
         HC_Close_Segment ();

	 HC_Open_Segment ("quit");
	    HC_Set_Window (0.35, 0.7, -0.9, -0.75);
	    HC_Insert_Text (0.0, 0.0, 0.0, "Quit");
	 HC_Close_Segment ();

	 HC_Open_Segment ("resulting color");
	    HC_Set_Window (-0.7, 0.7, 0.75, 0.95);
	 HC_Close_Segment ();

	 HC_QSet_Window_Frame ("* readout", "off");
	 HC_QSet_Window_Frame ("* label", "off");
	 HC_Update_Display ();

	 HC_Open_Segment ("color name");
	    HC_Set_Camera_Projection ("stretched");
	    HC_Set_Text_Alignment ("<");
	    HC_Set_Window (-0.7, 0.7, -0.7, -0.5);
	 HC_Close_Segment ();


	 for (;;) {
	    RGB_Color  rgb;
	    char       event[24];
	    HC_KEY     tkey, ckey;
	    int	       first_button;


	    first_button = 1;

	    HC_Open_Segment ("color name");
		tkey = HC_KInsert_Text (-0.95, 0.0, 0.0, colorname);
		ckey = HC_KInsert_String_Cursor (tkey, 0, (int)strlen(colorname));
	    HC_Close_Segment ();

	    HC_Enable_String_Events ("?keyboard", ckey);
	    HC_Enable_Button_Events ("?keyboard", "anything");
	    HC_Enable_Selection_Events ("?locater", "?picture");

	    do {
		HC_Await_Event (event);

		if (streq (event, "button") && first_button) {
			first_button = 0;
			HC_Edit_Text (tkey, 0, 0, 0, (int) strlen(colorname), "");
			HC_Disable_Button_Events ("?keyboard", "anything");
		}	
	    }  while (!streq (event, "string") && !streq (event, "selection"));

	    if (streq (event, "string")) {
		char      colorspec[100];
		char	  oldcolor_name[100];

		strcpy(oldcolor_name, colorname);

		HC_Show_String (colorname);
		if (!streq (colorname, "") &&  (HC_Compute_Color (colorname, "RGB", &rgb))) {
		      fill_slider ("?color box/red", rgb.r);
		      fill_slider ("?color box/green", rgb.g);
		      fill_slider ("?color box/blue", rgb.b);
		      sprintf (colorspec, "windows = %s", colorname);
		      HC_QSet_Color ("?color box/resulting color", colorspec);
		}
		else
		      strcpy(colorname, oldcolor_name);

	    }
	    else if (streq (event, "selection")) {
		char      segment[100];

		HC_Show_Selection (segment);
		if (streq (segment, "apply")  && colorname[0])
		   HC_QSet_Color ("?picture/object", colorname);
		else if (streq (segment, "quit"))
		   break;
	    }
	    HC_Disable_String_Events ("?keyboard", ckey);
	    HC_Delete_By_Key (tkey);
	    HC_Disable_Selection_Events ("?locater", "?picture");
	 }
      HC_Close_Segment ();
   HC_Close_Segment ();

   HC_Exit_Program ();
   return 0;
}
