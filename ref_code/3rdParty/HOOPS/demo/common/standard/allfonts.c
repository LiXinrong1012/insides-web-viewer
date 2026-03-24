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
 * $Id: allfonts.c,v 1.7 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



#define LOAD_ON_USE

void move_up (
    char	*name,
    float	delta,
    float	*currp,
    float	limit) {

    if (*currp + delta > limit)
	delta = limit - *currp;
    if (delta > 0.001) {
	HC_QTranslate_Object (name, 0.0, (double)-delta, 0.0);
	*currp += delta;
    }
}

void move_down (
    char	*name,
    float	delta,
    float	*currp,
    float	limit) {

    if (*currp - delta < limit)
	delta = *currp - limit;
    if (delta > 0.001) {
	HC_QTranslate_Object (name, 0.0, (double)delta, 0.0);
	*currp -= delta;
    }
}

int main () {
    char	font_name[256], dummy[256], value[256];
    int		count, loop, max_legal;
    float	dmyf, yinc, ypos;
    float	min_generic_ypos,
		min_defined_ypos,
		min_family_ypos,
		min_specific_ypos;
    float	curr_generic_ypos,
		curr_defined_ypos,
		curr_family_ypos,
		curr_specific_ypos;

    HC_Define_System_Options ("no message limit");
    HC_Open_Segment ("?picture");
      HC_Set_Camera_By_Volume ("stretched", -1.0, 1.0, -1.0, 1.0);
      HC_Set_Text_Font ("size = 0.025 sru, size tolerance = 50%");
      HC_Update_Display ();

      HC_Open_Segment ("instructions");
	HC_Set_Window (-1.0, 1.0, 0.9, 1.0);
	HC_Set_Color ("windows = black, text = white");
	HC_Set_Text_Font ("name = (system default, sans serif, roman, courier, stroked)");
	HC_Insert_Text (0.0, 0.0, 0.0,
			"Click on Font-Name for more info, use arrows to scroll, type 'q' when done.");
      HC_Close_Segment ();

      HC_Open_Segment ("generic fonts");
	HC_Set_Window (-1.0, -0.2, 0.4, 0.8);
	HC_Begin_Font_Search ("?Picture", "Generic");
	  HC_Show_Font_Count (&count);
	  curr_generic_ypos = ypos = 0.95f;
	  while (HC_Find_Font (font_name)) {
	      sprintf (dummy, "\"%s\"", font_name);
	      HC_Open_Segment (dummy);
		sprintf (dummy, "name = \"%s\"", font_name);
		HC_Set_Text_Font (dummy);
		HC_Insert_Text (0.0, (double)ypos, 0.0, font_name);
		HC_Compute_Text_Extent (".", font_name, &dmyf, &yinc);
		if ((1.2 * yinc) < 0.04)
		    ypos -= 0.04f;
		else
		    ypos -= 1.2f * yinc;
	      HC_Close_Segment ();
	  }
	HC_End_Font_Search ();
	min_generic_ypos = ypos;
      HC_Close_Segment ();
      HC_Open_Segment ("generic title bar");
	HC_Set_Window (-1.0, -0.2, 0.8, 0.9);
	HC_Set_Color ("windows = grayish white, text = red");
	sprintf (dummy, "%d Generic Fonts", count);
	HC_Insert_Text (0.0, 0.0, 0.0, dummy);
      HC_Close_Segment ();

      HC_Open_Segment ("defined fonts");
	HC_Set_Window (-1.0, -0.2, -1.0, -0.4);
	HC_Begin_Font_Search ("?Picture", "Defined");
	  HC_Show_Font_Count (&count);
	  curr_defined_ypos = ypos = 0.95f;
	  while (HC_Find_Font (font_name)) {
	      sprintf (dummy, "\"%s\"", font_name);
	      HC_Open_Segment (dummy);
		sprintf (dummy, "name = \"%s\"", font_name);
		HC_Set_Text_Font (dummy);
		HC_Insert_Text (0.0, (double)ypos, 0.0, font_name);
		HC_Compute_Text_Extent (".", font_name, &dmyf, &yinc);
		if ((1.2 * yinc) < 0.04)
		    ypos -= 0.04f;
		else
		    ypos -= 1.2f * yinc;
	      HC_Close_Segment ();
	  }
	HC_End_Font_Search ();
	min_defined_ypos = ypos;
      HC_Close_Segment ();
      HC_Open_Segment ("defined title bar");
	HC_Set_Window (-1.0, -0.2, -0.4, -0.3);
	HC_Set_Color ("windows = grayish white, text = purple");
	sprintf (dummy, "%d Defined Fonts", count);
	HC_Insert_Text (0.0, 0.0, 0.0, dummy);
      HC_Close_Segment ();

      HC_Open_Segment ("family fonts");
	HC_Set_Window (-1.0, -0.2, -0.3, 0.3);
	HC_Begin_Font_Search ("?Picture", "Families");
	  HC_Show_Font_Count (&count);
	  curr_family_ypos = ypos = 0.95f;
	  while (HC_Find_Font (font_name)) {
	      sprintf (dummy, "\"%s\"", font_name);
	      HC_Open_Segment (dummy);
		sprintf (dummy, "name = \"%s\"", font_name);
#ifdef LOAD_ON_USE
		HC_Set_Text_Font ("name = roman");
#else
		HC_Set_Text_Font (dummy);
#endif
		HC_Insert_Text (0.0, (double)ypos, 0.0, font_name);
		HC_Compute_Text_Extent (".", font_name, &dmyf, &yinc);
		if ((1.2 * yinc) < 0.04)
		    ypos -= 0.04f;
		else
		    ypos -= 1.2f * yinc;
	      HC_Close_Segment ();
	  }
	HC_End_Font_Search ();
	min_family_ypos = ypos;
      HC_Close_Segment ();
      HC_Open_Segment ("families title bar");
	HC_Set_Window (-1.0, -0.2, 0.3, 0.4);
	HC_Set_Color ("windows = grayish white, text = blue");
	sprintf (dummy, "%d Family-named Fonts", count);
	HC_Insert_Text (0.0, 0.0, 0.0, dummy);
      HC_Close_Segment ();

      HC_Open_Segment ("specific fonts");
	HC_Set_Window (-0.2, 1.0, -1.0, 0.8);
	HC_Begin_Font_Search ("?Picture", "specific");
	  HC_Show_Font_Count (&count);
	  curr_specific_ypos = ypos = 0.95f;
	  while (HC_Find_Font (font_name)) {
#ifndef LOAD_ON_USE
	      char		size[200];

	      HC_Show_Font_Info ("?Picture", font_name, "sizes", size);
	      if (size[0] == '(')
		  count--;
	      else {
#endif
		  sprintf (dummy, "\"%s\"", font_name);
		  HC_Open_Segment (dummy);
#ifdef LOAD_ON_USE
		    HC_Set_Text_Font ("name = roman");
#else
		    if (size[0] != '\0')
			sprintf (dummy, "name = \"%s\", size = %s pt",
					font_name, size);
		    else
			sprintf (dummy, "name = \"%s\"", font_name);
		    HC_Set_Text_Font (dummy);
#endif
		    HC_Insert_Text (0.0, (double)ypos, 0.0, font_name);
		    HC_Compute_Text_Extent (".", font_name, &dmyf, &yinc);
		    if (1.2 * yinc < 0.04)
			ypos -= 0.04f;
		    else
			ypos -= 1.2f * yinc;
		  HC_Close_Segment ();
#ifndef LOAD_ON_USE
	      }
#endif
	  }
	HC_End_Font_Search ();
	min_specific_ypos = ypos;
      HC_Close_Segment ();
      HC_Open_Segment ("specific title bar");
	HC_Set_Window (-0.2, 1.0, 0.8, 0.9);
	HC_Set_Color ("windows = grayish white, text = dark green");
	sprintf (dummy, "%d Specific Fonts Reported", count);
	HC_Insert_Text (0.0, 0.0, 0.0, dummy);
      HC_Close_Segment ();

      HC_QSet_Camera_By_Volume ("*fonts", "stretched", -0.05, 1.0, 0.0, 1.0);
      HC_QSet_Text_Font ("*fonts", "size = 0.03 sru, size tolerance = 100%");
      HC_QSet_Text_Alignment ("*fonts", "<^");
      HC_QSet_Selectability ("*fonts", "text = on, windows=off");

      HC_QSet_Camera_By_Volume ("*bar", "stretched", -0.05, 1.0, -1.0, 1.0);
      HC_QSet_Text_Font ("*bar", "name = (sans serif, roman, system default)");
      HC_QSet_Text_Alignment ("*bar", "<*");
    HC_Close_Segment ();

    HC_Enable_Button_Events ("?Keyboard", "anything");
    HC_Enable_Selection_Events ("?Locater", "?Picture");
    for (;;) {
	char	event[80];

	HC_Await_Event (event);

	/* When the driver goes to haven, we bail out */
	if (strcmp (event, "none") == 0) {
	    HC_Exit_Program ();
	}
	if (strcmp (event, "button") == 0) {
	    HC_Show_Button (dummy);

	    if (strcmp (dummy, "q") == 0  ||  strcmp (dummy, "Q") == 0)
		break;

	    else if (strcmp (dummy, "left arrow") == 0)
		HC_QTranslate_Object ("?Picture/* fonts", -0.3, 0.0, 0.0);
	    else if (strcmp (dummy, "right arrow") == 0)
		HC_QTranslate_Object ("?Picture/* fonts", 0.3, 0.0, 0.0);

	    else if (strcmp (dummy, "up arrow") == 0) {
		move_up ("?Picture/generic fonts", 0.6f,
			 &curr_generic_ypos, 0.95f);
		move_up ("?Picture/defined fonts", 0.6f,
			 &curr_defined_ypos, 0.95f);
		move_up ("?Picture/family fonts", 0.6f,
			 &curr_family_ypos, 0.95f);
		move_up ("?Picture/specific fonts", 0.6f,
			 &curr_specific_ypos, 0.95f);
	    }
	    else if (strcmp (dummy, "down arrow") == 0) {
		move_down ("?Picture/generic fonts", 0.6f,
			   &curr_generic_ypos, min_generic_ypos + 0.5f);
		move_down ("?Picture/defined fonts", 0.6f,
			   &curr_defined_ypos, min_defined_ypos + 0.5f);
		move_down ("?Picture/family fonts", 0.6f,
			   &curr_family_ypos, min_family_ypos + 0.5f);
		move_down ("?Picture/specific fonts", 0.6f,
			   &curr_specific_ypos, min_specific_ypos + 0.5f);
	    }
	}
	else {
	    char	sizes[12000], *pos, the_size[40];

	    /* Find the name of the font that was selected.	*/
	    HC_Show_Selection_Pathname (dummy);
	    HC_Show_Selection (font_name);
	    /* name may come back with extra quotes around it */
	    if (font_name[0] == '`' ||
		font_name[0] == '\'' ||
		font_name[0] == '"') {
		strcpy (font_name, &font_name[1]);
		font_name[strlen (font_name)-1] = '\0';
	    }

	    /* Hide the font lists, and display info on selected font.	*/
	    HC_Open_Segment ("?Picture/font info");
		HC_Set_Window (-1.0, 1.0, -1.0, 1.0);
		HC_Set_Color ("windows = black, text = white");
		HC_Set_Camera_By_Volume ("s", -1.0, 1.0, 0.0, 1.0);
		HC_Set_Text_Alignment ("v<");

		/* Display a sample of all the available sizes.		  */
		/* If this is a stroked font, then show a basic set of sizes. */
		/* If there is only one size, then skip this section, since  */
		/* a sample of the font will be shown in the next stage.  */
		HC_Show_Font_Info ("?Picture", font_name, "sizes", sizes);

		the_size[0] = '\0';
		if (sizes[0] == '(') {
		    strcpy (sizes, &sizes[1]);
		    sizes[strlen (sizes) - 1] = '\0';
		}

		if (!strlen(sizes)) /* Any size available */
		    strcpy (sizes, "4., 6., 8., 9., 10., 12., 14., 16., 18., 20., 24., 32.");

		if (HC_Parse_String (sizes, ", ", 1, the_size)) {
		    /* A list of sizes is available */

		    ypos = 0.05f;
		    for (loop = 0;
			 HC_Parse_String (sizes, ", ", loop, the_size);
			 loop++) {

			HC_Open_Segment ("");
			    sprintf (dummy, "name = \"%s\", size = %s pt", font_name, the_size);
			    HC_Set_Text_Font (dummy);
			    sprintf (dummy, "%s pt: The Quick Brown Fox jumps over the lazy dog. 1234567890", the_size);
			    HC_Insert_Text (-0.95, (double)ypos, 0.0, dummy);
			    HC_Compute_Text_Extent (".", dummy, &dmyf, &yinc);
			    ypos += 1.5f * yinc;
			HC_Close_Segment ();
		    }
		    HC_Get_Selection (dummy);
		}
	    HC_Close_Segment ();
	    HC_Create_Segment ("?Picture/font info/dummy");
	    HC_Delete_Segment ("?Picture/font info/*");

	    HC_Open_Segment ("?Picture/font info");
		HC_Set_Color ("windows = black, text = yellow");
		HC_Set_Text_Alignment ("<*");

		HC_Set_Text_Font ("name = (sans serif, roman, stroked), size = 0.02 wru, size tolerance = 50%");
		sprintf (dummy, "Name:          %s", font_name);
		HC_Insert_Text (-0.98, 0.95, 0.0, dummy);

		HC_Show_Font_Info ("?Picture", font_name, "exists", value);
		sprintf (dummy, "Exists:        %s", value);
		HC_Insert_Text (0.4, 0.95, 0.0, dummy);

		/* HC_Show_Font_Info ("?Picture", font_name, "sizes", sizes); */
		sprintf (dummy, "Sizes:         %s", sizes);
		HC_Insert_Text (-0.98, 0.90, 0.0, dummy);

		HC_Show_Font_Info ("?Picture", font_name, "outlineable", value);
		sprintf (dummy, "Outlineable: %s", value);
		HC_Insert_Text (0.4, 0.90, 0.0, dummy);

		HC_Show_Font_Info ("?Picture", font_name, "scaleable", value);
		sprintf (dummy, "Scaleable:     %s", value);
		HC_Insert_Text (-0.98, 0.85, 0.0, dummy);

		HC_Show_Font_Info ("?Picture", font_name, "proportional", value);
		sprintf (dummy, "Proportional:  %s", value);
		HC_Insert_Text (0.4, 0.85, 0.0, dummy);

		HC_Show_Font_Info ("?Picture", font_name, "scaleable", value);
		sprintf (dummy, "Rotatable:     %s", value);
		HC_Insert_Text (-0.98, 0.80, 0.0, dummy);

		HC_Show_Font_Info ("?Picture", font_name, "width scaleable", value);
		sprintf (dummy, "Width Scaleable:  %s", value);
		HC_Insert_Text (0.4, 0.80, 0.0, dummy);

		HC_Show_Font_Info ("?Picture", font_name, "points to sru", value);
		sprintf (dummy, "Points to SRU: %s", value);
		HC_Insert_Text (-0.98, 0.75, 0.0, dummy);

		HC_Show_Font_Info ("?Picture", font_name, "generic name", value);
		sprintf (dummy, "Generic name:  %s", value);
		HC_Insert_Text (0.4, 0.75, 0.0, dummy);

		HC_Show_Font_Info ("?Picture", font_name, "max character", value);
		max_legal = atoi (value);
		sprintf (dummy, "Max Character: %s", value);
		HC_Insert_Text (-0.98, 0.7, 0.0, dummy);

		HC_Show_Font_Info ("?Picture", font_name, "encoding", value);
		sprintf (dummy, "Encoding: %s", value);
		HC_Insert_Text (0.4, 0.7, 0.0, dummy);

		HC_Insert_Text (-0.98, 0.65, 0.0, "Sample:");

		HC_Open_Segment ("");
		  HC_Set_Color ("text = white");
		  if (HC_Parse_String (sizes, ", ", -1, the_size))
		       sprintf (dummy, "name = \"%s\", size = %s pt", font_name, the_size);
		  else
		       sprintf (dummy, "name = \"%s\", size = 14 pt, size tolerance = 100%%", font_name);
		  HC_Set_Text_Font (dummy);

		  dummy[0] = (char)max_legal;
		  dummy[1] = '\0';
		  HC_Insert_Text (-0.3, 0.7, 0.0, dummy);

		  HC_Open_Segment ("");
		    HC_Set_Window (-1.0, 1.0, -1.0, 0.25);

		    HC_Insert_Text (-0.95, 0.92, 0.0,
"The Quick Brown Fox jumps over the lazy dog.  1234567890 !@#$^&* ()_-= + {}[]");
		    HC_Compute_Text_Extent (".", "The lazy", &dmyf, &yinc);
		    ypos = 0.92f - 1.15f * yinc;

		    HC_Show_Font_Info ("?Picture", font_name, "encoding", value);

		    if (strcmp (value, "euc") == 0 || strcmp (value, "jec") == 0)
			HC_Insert_Text_With_Encoding (-0.9, (double)ypos, 0.0, "EUC",
			    "\310\364\363\310\306\360\302\316\270\370\273\312");
			else if (strcmp (value, "unicode") == 0) {

			    unsigned short uni[1024];
				unsigned short * pos;

				HC_Open_Segment ("");
				HC_Set_Text_Font ("size = 20 pt");

				for (pos = uni, loop = 0; loop <= 1024; loop++) {
				    
					if (loop)
					    *pos++ = (unsigned short)loop;
					else
					    *pos++ = (unsigned short)' ';

					if (!((loop+1) % 128) || loop == max_legal) {

					    *pos = (unsigned short)'\0';
					    HC_Insert_Text_With_Encoding (-0.9, (double)ypos, 0.0, "unicode",(char *)uni);
					    HC_Compute_Text_Extent (".", dummy, &dmyf, &yinc);
					    ypos -= yinc;
					    pos = uni;
					}
				}
				HC_Close_Segment();
			}else
			for (pos = dummy, loop = 0; loop <= max_legal; loop++) {
			    if (loop)
				*pos++ = (char)loop;
			    else
				*pos++ = ' ';

			    if (!((loop+1) % 32) || loop == max_legal) {
				*pos = '\0';
				HC_Insert_Text (-0.9, (double)ypos, 0.0, dummy);
				HC_Compute_Text_Extent (".", dummy, &dmyf, &yinc);
				ypos -= yinc;
				pos = dummy;
			    }
			}

		    for (;;) {
			HC_Await_Event (event);
			if (strcmp (event, "none") == 0) {
	    		    HC_Exit_Program ();
			}
			if (strcmp (event, "selection") == 0) 
			    break;

			HC_Show_Button (dummy);
			if (strcmp (dummy, "left arrow") == 0)
			    HC_Translate_Object (0.2, 0.0, 0.0);
			else if (strcmp (dummy, "right arrow") == 0)
			    HC_Translate_Object (-0.2, 0.0, 0.0);
			else if (strcmp (dummy, "up arrow") == 0)
			    HC_Translate_Object (0.0, -0.2, 0.0);
			else if (strcmp (dummy, "down arrow") == 0)
			    HC_Translate_Object (0.0, 0.2, 0.0);
		    }

		  HC_Close_Segment ();
		HC_Close_Segment ();
	    HC_Close_Segment ();
	    HC_Delete_Segment ("?Picture/font info");
	}
    }
    HC_Disable_Button_Events ("?Keyboard", "anything");
    HC_Disable_Selection_Events ("?Locater", "?Picture");
    HC_Delete_Segment ("?picture");

    HC_Exit_Program ();
    return 0;
}
