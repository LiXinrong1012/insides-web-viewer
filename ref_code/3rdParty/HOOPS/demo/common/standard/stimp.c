 
#include "hc.h"
#include "hic.h"

/* needs HIC update */
#define USE_NO_GL
#ifdef USE_NO_GL

/* OGL not present */

int main () {
    HC_Open_Segment ("?picture");
    HC_Insert_Text (0.0, 0.0, 0.0,
            "Program must be compiled without -DUSE_NO_GL");
    HC_Close_Segment ();
    HC_Pause ();
    HC_Exit_Program ();
    return 0;
}

#else



#ifdef OSX_SYSTEM

# undef OS_INLINE
# define OS_INLINE static __inline__ /* workaround for a problem in agl headers */
# include <AGL/agl.h>
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <Carbon/Carbon.h>

#else

#ifdef WINDOWS_SYSTEM
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
# include <windows.h>
#endif

# include <GL/gl.h>
# include <GL/glu.h>

#endif







typedef struct {
	float x,y,z;
	} Point;

#define Set(_p,_x,_y,_z) \
	_p.x=_x; _p.y=_y; _p.z=_z;

static int write_renderer = 0;
 
void InsertBox (Point *max, Point *min){

    Point 	points[8];
    int		face_list[30] = {4,0,1,2,3,
							 4,7,6,5,4,
							 4,1,5,6,2,
							 4,4,0,3,7,
							 4,3,2,6,7,
							 4,4,5,1,0};

	Set(points[0], min->x, min->y, min->z);
	Set(points[1], max->x, min->y, min->z);
	Set(points[2], max->x, max->y, min->z);
	Set(points[3], min->x, max->y, min->z);
	Set(points[4], min->x, min->y, max->z);
 	Set(points[5], max->x, min->y, max->z);
 	Set(points[6], max->x, max->y, max->z);
 	Set(points[7], min->x, max->y, max->z);
 
	HC_Insert_Shell (8, points, 30, face_list);
   
    return;
}

GLubyte halftone[] = {
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA, 
        0xAA, 0xAA, 0xAA, 0xAA,  0xAA, 0xAA, 0xAA, 0xAA};


static void
my_set_material (OGLData  * ogldata,
				 HT_Net_Rendition const * nr,
				 HT_Material_Rendition const * matr,
				 HT_RGB const *use_color,
				 HT_RGB const *use_specular_color)
{

	OGL_DEFAULT_SET_MATERIAL(ogldata,nr,matr,use_color, use_specular_color);

	if (HIC_Show_User_Index(nr,10)) {

		glPolygonStipple(halftone);
 		glEnable (GL_POLYGON_STIPPLE);
		ogldata->cache.face_pattern = INVALID_CACHE;
		ogldata->geom_incarnation = INVALID_CACHE;

	} 

	if(write_renderer) {

		FILE * file;
		const char * renderer;

		file = fopen("OPENGL_RENDERER.TXT", "w+");


		renderer = (const char *) glGetString(GL_RENDERER);
		
		if(renderer)
			fprintf(file,"%s",renderer);

		fclose(file);

		write_renderer = 0;
	}

	return;
}


static void
my_set_3d_xform (
	OGLData  * ogldata,
	HT_Net_Rendition const * nr)
{
	glDisable (GL_POLYGON_STIPPLE);
	OGL_DEFAULT_SET_3D_XFORM(ogldata, nr);
}

static void
my_set_dc_xform (
	OGLData  * ogldata,
	HT_Net_Rendition const * nr)
{
	glDisable (GL_POLYGON_STIPPLE);
	OGL_DEFAULT_SET_DC_XFORM(ogldata, nr);
}



static void my_driver_startup (
	      HT_Net_Rendition const * nr)
{
	OGLData  *ogldata = OGLNRD (nr);     

 	ogldata->actions.set_material = my_set_material;
 	ogldata->actions.set_dc_xform = my_set_dc_xform;
 	ogldata->actions.set_3d_xform = my_set_3d_xform;

}


int main (int argc, char ** argv) {

	Point p1,p2;

	if(argc >= 2) 
		if(argv[1][0] == '-' && argv[1][1] == 'w')
			write_renderer = 1;

 	HC_Define_Callback_Name ("my driver startup", 
			(void (HC_CDECL*)(HC_ANY_ARGS))my_driver_startup);

	HC_Delete_Segment("?picture");
 
	HC_Open_Segment("?driver/opengl/:0+0");
		HC_Set_Visibility ("markers = off, edges = on");
		HC_Set_Rendering_Options("hsra = hzb, no technology");
		HC_Set_Color ("faces = red, edges = black, lights = white");
		HC_Set_Rendering_Options ("lighting interpolation");
		HC_Insert_Distant_Light(1,1,-1);
		HC_Set_Camera_Position(0,0,4);
		HC_Set_Camera_Target(0,0,0);
		HC_Set_Callback ("driver startup = my driver startup");

		HC_Open_Segment("box1"); 
			Set(p1,-0.5f,-0.5f,-0.5f);
			Set(p2,0.0f,0.0f,0.0f);
			HC_Set_User_Index(10,(void *)0);
			InsertBox(&p1,&p2);
		HC_Close_Segment();

		HC_Open_Segment("box2"); 
			Set(p1,0.0f,0.0f,0.0f);
			Set(p2,0.5f,0.5f,0.5f);
			HC_Set_User_Index(10,(void *)1);
			InsertBox(&p1,&p2);
		HC_Close_Segment();

	HC_Close_Segment();

	HC_Pause();

	return 0;
}
	
#endif
