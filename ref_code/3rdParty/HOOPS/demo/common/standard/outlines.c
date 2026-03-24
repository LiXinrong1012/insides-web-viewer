


#include <stdio.h>
#include "hc.h"

typedef struct {
    float x, y, z;
} Point;
#define HT_POINT Point;

#include <stdlib.h>
#include <math.h>


typedef struct Point{
	float x, y, z;
} Pstruct;

#define THE_STRING "abcdefghijklmnopqrstuvwxyz"
#define THE_SRU 0.05f

int main () {

	char font_size[1024];
    int	pcount;
    float *points;
    int	flist_length;
    int	*face_list;
    Pstruct min,max;

    HC_Open_Segment ("?picture");

    	HC_Set_Camera_Projection("orthographic");

	HC_Set_Text_Font ("name = Arial");
	sprintf(font_size,"size = %f sru, width scale = 1.0", THE_SRU);
	HC_Set_Text_Font (font_size);
	HC_Set_Text_Alignment ("**");
	HC_Set_Visibility("markers = off, faces = off");
	HC_Insert_Text (0.0, 0.0, 0.0, THE_STRING);

	HC_Compute_Text_Outline_Size (".", THE_STRING, &pcount, &flist_length);

	if (pcount <= 0)
		HC_Exit_Program ();

	face_list = (int *)malloc (flist_length * sizeof (int));
	points = (float *)malloc (pcount * 3 * sizeof(float));

	HC_Compute_Text_Outline(".", THE_STRING, &pcount, points, &flist_length, face_list);

	HC_Open_Segment ("");
	    HC_Set_Color("red");
	    HC_Insert_Shell (pcount, points,flist_length, face_list);
	    HC_Compute_Circumcuboid(".", &min, &max);
	    HC_Translate_Object(-(max.x+min.x)/2.0,-(max.y)/2.0,0.0);
	    HC_Scale_Object(THE_SRU*2.0,THE_SRU*2.0,0.0);
	HC_Close_Segment ();

	free (face_list);
	free (points); 

    	HC_Pause ();
	HC_Set_Text_Font ("outline");
    	HC_Pause ();
	HC_Set_Text_Font ("no outline");
    	HC_Pause ();

    HC_Close_Segment ();

    HC_Exit_Program ();
    return 0;
}

 
