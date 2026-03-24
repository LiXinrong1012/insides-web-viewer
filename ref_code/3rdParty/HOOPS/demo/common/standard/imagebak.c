
/*---------------------------------------------------------------------*\
 |                                                                     |
 |  Copyright (c) 1986-1991, 1992 by Ithaca Software.                  |
 |  All rights reserved.                                               |
 |  Use of copyright notice does not imply publication or disclosure.  |
 |                                                                     |
 |  THIS SOFTWARE CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION    |
 |  CONSTITUTING VALUABLE TRADE SECRETS OF ITHACA SOFTWARE AND MAY     |
 |  NOT BE (a) DISCLOSED TO THIRD PARTIES, (b) COPIED IN ANY FORM,     |
 |  OR (c) USED FOR ANY PURPOSE EXCEPT AS SPECIFICALLY PERMITTED IN    |
 |  WRITING BY ITHACA SOFTWARE.                                        |
 |                                                                     |
\*---------------------------------------------------------------------*/

/*
 * $Id: imagebak.c,v 1.3 2001-10-03 22:40:00 Jason Exp $
 */

#include "hc.h"
#include <math.h>
#include <stdlib.h>

float tri[] = {-0.5f, -0.866f, 0.0f, -0.5f, 0.866f, 0.0f, 1.0f, 0.0f, 0.1f, 1.7f, 0.4f, 2.0f};
int conn[] = {3, 0, 1, 2, 3, 2, 1, 3};

int main (int argc, char **argv) {
    HC_KEY	key;
    char	dummy[32], *image;
    float	f;
    int		i, ww, hh;

    /* read the image from a metafile */
    HC_Open_Segment ("/tmp/meta");
	HC_Read_Metafile ("fruit", ".", "");
	HC_Begin_Contents_Search (".", "images");
	    HC_Find_Contents (dummy, &key);
	HC_End_Contents_Search ();
	HC_Show_Image_Size (key, &f, &f, &f, dummy, &ww, &hh);
	if (sizeof (int) == 2) {
	    /* probably can't allocate a big chunk, so ask HOOPS to make an
	     * empty image in its database, then fill it in by rasters
	     */
	    HC_KEY	newkey;

	    image = (char *)malloc (ww * 3 * sizeof (char));
	    newkey = HC_QKInsert_Image ("/tmp", 0.0, 0.0, 0.0,
					"rgb, name=fruit, no data",
					ww, hh, image /* ignored */);
	    for (i = 0; i < hh; ++i) {
		HC_Show_Partial_Image (key, 0, i, ww, 1, image);
		HC_Edit_Image (newkey, 0, i, ww, 1, image);
	    }
	    free (image);
	}
	else {
	    image = (char *)malloc (ww * hh * 3 * sizeof (char));
	    HC_Show_Image (key, &f, &f, &f, dummy, &ww, &hh, image);
	    HC_QInsert_Image ("/tmp", 0.0, 0.0, 0.0, "rgb, name=fruit",
			      ww, hh, image);
	    free (image);
	}
	HC_Delete_By_Key (key);
    HC_Close_Segment ();

    /* associated named image with window background */
    HC_Open_Segment ("?Picture");
	HC_Set_Visibility ("no markers, edges");
	key = HC_KInsert_Shell (4, tri, 8, conn);
	HC_Set_Color ("faces=red, window=fruit, edges=gray");
	HC_Pause ();

	for (i = 0; i < 4; i++) {
	    HC_Rotate_Object (0.0, 0.0, 30.0);
	    HC_Update_Display ();
	}
	HC_Pause ();
    HC_Close_Segment ();
    HC_Exit_Program ();
    return 0;
}
