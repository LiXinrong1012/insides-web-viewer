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
 * $Id: rotchar.c,v 1.3 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdio.h>
#include <string.h>


int main () 
{
    char rotation[100];
	int i;

    /* receive input from the keyboard from either window */
    HC_Enable_Button_Events ("?Picture", "anything");

	HC_Open_Segment("?Picture");
		
	HC_Set_Text_Font("name = roman, size = 0.25 sru");
	HC_Insert_Text(0.0,0.0,0.0,"{[$]}");

#if 1 
	for(i=0;i<720;i++){
/*
	for(i=0;i<45;i++){
*/
		sprintf(rotation,"rotation = %d",i);
		HC_Set_Text_Font(rotation);
		HC_Update_Display();
	}
#else

	HC_Set_Text_Font("rotation=89");
	HC_Update_Display();
	HC_Set_Text_Font("rotation=90");
	HC_Update_Display();
	HC_Set_Text_Font("rotation=91");
	HC_Update_Display();
	HC_Set_Text_Font("rotation=120");
	HC_Update_Display();
	HC_Set_Text_Font("rotation=180");
	HC_Update_Display();
	HC_Set_Text_Font("rotation=210");
	HC_Update_Display();
	HC_Set_Text_Font("rotation=240");
	HC_Update_Display();
	HC_Set_Text_Font("rotation=270");
	HC_Update_Display();
	HC_Set_Text_Font("rotation=300");
	HC_Update_Display();
	HC_Set_Text_Font("rotation=330");
	HC_Update_Display();
	HC_Set_Text_Font("rotation=360");
	HC_Update_Display();
#endif

	HC_Close_Segment();

	HC_Pause();

    HC_Exit_Program ();
    return 0;
}





