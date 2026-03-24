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
 */

#include "hc.h"
#include <stdio.h>

#define EXTRA_POINTER_FORMAT extra_pointer_format()

const char* extra_pointer_format(void)
{
    char buffer[1024];

    sprintf (buffer, "%p", (void*) buffer);
    if (buffer[0] == '0' && buffer[1] == 'x')
	return "";
    else
	return "0x";
}



int main () {

	HC_KEY image_key;
	HC_KEY image_seg;

	char buffer[4096];


	image_seg = HC_KOpen_Segment("/image");
		image_key = HC_KInsert_Image (0.0, 0.0, 0.0, "rgb", 3000, 3000, 0);
	HC_Close_Segment ();

	HC_Open_Segment ("?driver/opengl/image");
		HC_Insert_Line (-1.0, -1.0, 0.0, 1.0, 1.0, 0.0);
		sprintf (buffer, "isolated, debug = 0x0100000, use window id = %s%p, subscreen = (-1, 1, -1, 1)", EXTRA_POINTER_FORMAT, (void*)image_key);
		HC_Set_Driver_Options (buffer);
		HC_Set_Color("lines=blue , windows=green");
	HC_Close_Segment ();

	HC_Update_One_Display("?driver/opengl/image");
	HC_Delete_Segment("?driver/opengl/image");


	HC_Open_Segment ("?picture");
		HC_Include_Segment_By_Key (image_seg);
		HC_Set_Color("windows=red");
	HC_Close_Segment ();
		
	HC_Pause ();

	HC_Delete_Segment("/image");

	HC_Exit_Program ();

	return 0;
}




