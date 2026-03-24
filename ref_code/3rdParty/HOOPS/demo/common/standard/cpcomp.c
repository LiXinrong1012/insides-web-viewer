#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WINDOWS_SYSTEM
#undef WINDOWS_SYSTEM
#endif

#include "hc.h"
#include "hic.h"

#ifdef WINDOWS_SYSTEM 
#define extra_pointer_format "0x"
#else
#define extra_pointer_format ""
#endif


typedef struct pline {
    int         count;
    HIC_Point    *points;
    struct      pline   *next;
} CP_Polyline;


typedef struct cp_line_data {
    CP_Polyline         *pLhead;
    CP_Polyline         *pLtail;
    long                count;
} CP_Linedata;




/* pointer to the structure that will store the lines */

static CP_Linedata *pD;  



/* initialization of the above data structure; to be called each time that */
/* the cutting plane intersection polylines are recomputed                 */

void Init_CP_Line_Data () {
    pD = (CP_Linedata *)malloc(sizeof(CP_Linedata));
    pD->pLhead = 0;
    pD->pLtail = 0;
    pD->count = 0;
}



/* the 'draw_3d_polyline' callback that will store up the HOOPS cutting plane */
/* intersection polylines                                                     */

void store_cp_polyline (HIC_Rendition const *nr, HIC_Polyline const *poly) {
    CP_Polyline                 *pL;

    pL = (CP_Polyline *)malloc(sizeof(CP_Polyline));
    pL->count = HIC_Show_Polyline_Count(poly);
    pL->points = (HIC_Point *)malloc(sizeof(HIC_Point)*pL->count);
    memcpy( pL->points, HIC_Show_Polyline_Points(poly), sizeof(HIC_Point) * pL->count);
                

    pL->next = 0;

    if (pD->pLtail != 0)
        pD->pLtail->next = pL;

    pD->pLtail = pL;

    if (pD->pLhead == 0)
        pD->pLhead = pL;

    pD->count++;
}



/* this routine inserts the stored up cutting plane polylines into a single segment */
/* which has cutting planes turned off                                             */

void Insert_CP_Polylines()
{
    CP_Polyline     *pL;

    HC_Open_Segment("?Picture/cp_geom");
     
       HC_Set_Visibility("cutting planes = off");

       for (pL = pD->pLhead; pL != 0; pL = pL->next) {
            /* HC_Insert_Polyline(pL->count, pL->points);*/
			HC_Insert_Polygon(pL->count, pL->points);  /* we'll use a polygon for this demo */
       }

    
    HC_Close_Segment();

}



/* after inserting the lines into the HOOPS segment tree, we free them up */

void Free_CP_Polylines()
{
    CP_Polyline  *pL;
    CP_Polyline  *pLprev;

    if (pD->pLhead != 0) {
        pLprev = pD->pLhead;

        for (pL = pD->pLhead->next; pL != 0; pL = pL->next) {
                free (pLprev->points);
                free (pLprev);
                pLprev = pL;
        }
                
        free (pLprev->points);
        free (pLprev);
    }

        free (pD);
}



/* this is a preprocess step that tells HOOPS to compute the cutting plane   */
/* insersection polylines.  It uses an update to the image_driver to perform */
/* the calculations                                                          */

void Compute_CP_Lines()
{
    HC_KEY image_key;
    char buf[256];
    unsigned char   *data;

    data =  (unsigned char *)malloc (sizeof(unsigned char)*30000);

	Init_CP_Line_Data();

    HC_Open_Segment("/null");
            image_key = HC_KInsert_Image(0.0, 0.0, 0.0, "rgb", 100, 100, data);
    HC_Close_Segment();

    HC_Open_Segment("/driver/image/cp_image");
	  /* set the debug bit that tells HOOPS to calculate the cp intersections */
      sprintf(buf, "use window id = %s%p, debug = 1", extra_pointer_format, (void *)image_key);
      HC_Set_Driver_Options(buf);   
	  
	  /* use szb for fast rendering to the image */
      HC_Set_Rendering_Options ("hsra = szb");  
	  
      HC_Include_Segment("?Picture");  /* include your scene into the image driver segment */
    HC_Close_Segment();

	/* Update the scene; HOOPS will render to the image specified above and draw the cp    */
	/* intersection polylines which are intercepted by the IM callback                     */
    HC_Update_Display();              

	/* shut down the image driver */
    HC_Delete_Segment("/driver/image/cp_image"); 
    
    /* don't forget to unset the callback before the first screen update */
    HC_QUnSet_One_Callback("/driver", "draw 3d polyline");

    Insert_CP_Polylines();    /* insert the lines into the HOOPS tree */
    Free_CP_Polylines();      /* free up our stored list of polylines */

    free (data);

}




/* perform the cutting plane intersection calculation as a preprocess step */

int main()
{
	HC_Open_Segment("?Picture");
	  HC_Set_Rendering_Options("hsra = szb");   /* if a 3D driver is active, use hardware z-buffer !!! */

	  HC_Set_Color("windows = black, text = white, lines = red, faces = blue, edges = green");
	  HC_Insert_Distant_Light(0.0, 1.0, -1.0);

	  HC_Open_Segment ("text");
        HC_Set_Window( -1.0, 1.0, -1.0, -0.75 );
        HC_Insert_Text (0.0, 0.0, 0.0, "click to see intersection polygons");
      HC_Close_Segment ();
	  

	  HC_Open_Segment("object");

		  /* read in the file (or include the appropriate segment hierarchy)  */
		  /* that has the cutting planes in it                                */
		  HC_Read_Metafile("msphere.hmf", ".", "");
		  HC_Scale_Object(.1, .1 , .1);
		  HC_Rotate_Object(-130.0, 20.0, 20.0);

		  /* turn off lines so that the only lines intercepted by the draw_3d_polyline callback */
		  /* are the cutting plane intersection lines */
		  HC_Set_Visibility("markers = off");

	  HC_Close_Segment();

	HC_Close_Segment();

    /* this first update gives us a picture of the cutting-planed scene *without* the cp lines*/
	HC_Pause(); 


	/* define and set the draw_3d_polyline callback prior to the image_driver update */
    HC_Define_Callback_Name ("store-polyline", (void (HC_CDECL*)(HC_ANY_ARGS)) store_cp_polyline);
    HC_QSet_Callback ("/driver", "draw 3d polyline = store-polyline");

	/* have HOOPS compute the cp lines, and insert them into the HOOPS tree */
    Compute_CP_Lines(); 
	
	HC_Flush_Geometry( "?picture/text" );
    HC_QInsert_Text( "?picture/text", 0.0, 0.0, 0.0, "click to see intersection polylines in HLR mode");
    HC_Pause();

    /* turn on edges and HLR algorithm */
    HC_QSet_Visibility("?Picture", "faces = on, edges = on");
	HC_QSet_Rendering_Options("?Picture", "hsra = hidden line, hlro = (visibility = off)");
	HC_Flush_Geometry( "?picture/text" );
	/* need to force an update for the first HLR rendering due to a bug      */
	/* without this forced update, we don't see the HLR scene until a resize */
	HC_Control_Update("?Picture", "redraw everything");
	HC_Pause();

	return 1;
}
