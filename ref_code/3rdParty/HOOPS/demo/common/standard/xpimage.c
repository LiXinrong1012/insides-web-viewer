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
 * $Id: xpimage.c,v 1.3 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"
#include <math.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    HC_KEY	key;
    char	dummy[32];
    float	f;
    int		ii, jj, r2, d2, ww, hh;
    char	*image1, *image2, *ip, *op;

    HC_Open_Segment ("?Picture");
	/* get a normal RGB image from a metafile */
	HC_Insert_Line (-1.0,  1.0, 0.5, 1.0, -1.0, 0.5);
	HC_Insert_Line (-1.0, -1.0, 0.5, 1.0, 1.0, 0.5);
	HC_Read_Metafile ("fruit", ".", "");
	HC_Pause ();

	/* get a local copy of the image so we can interrogate it */
	HC_Begin_Contents_Search (".", "images");
	    HC_Find_Contents (dummy, &key);
	HC_End_Contents_Search ();
	HC_Show_Image_Size (key, &f, &f, &f, dummy, &ww, &hh);
	image1 = (char *)malloc (ww * hh * 3 * sizeof (char));
	HC_Show_Image (key, &f, &f, &f, dummy, &ww, &hh, image1);
	HC_Delete_By_Key (key);

	/* convert the local copy to another copy (with alpha) */
	image2 = (char *)malloc (ww * hh * 4 * sizeof (char));
	if (ww < hh)
	    r2 = (ww / 2) * (ww / 2);
	else
	    r2 = (hh / 2) * (hh / 2);
	ip = image1;
	op = image2;
	for (ii = 0; ii < hh; ii++)
	    for (jj = 0; jj < ww; jj++) {
		/* R G B */
		*op++ = *ip++;
		*op++ = *ip++;
		*op++ = *ip++;

		/* alpha - time to make the donut */
		d2 = (jj - ww / 2) * (jj - ww / 2) +
		     (ii - hh / 2) * (ii - hh / 2);
		*op++ = (char)(d2 > r2 || d2 < 2500 ? 0 : 255);
	    }
	HC_Insert_Image (0.0, 0.0, 0.0, "rgba", ww, hh, image2);
	HC_Pause ();
	free (image1);
	free (image2);
    HC_Close_Segment ();
    HC_Exit_Program ();
    return 0;
}
