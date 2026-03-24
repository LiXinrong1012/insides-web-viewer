
#include "hc.h"
#include "hic.h"

#include <stdio.h>



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




static const char *renderer = NULL;
static const char *ogl_extensions = NULL;
#ifdef WGL_DRIVER
static const char *wgl_extensions = NULL;
#endif


static void finish_picture (HIC_Rendition const *nr, bool swap)
{
    FILE *file;

    file = fopen("OPENGL_STRINGS.TXT", "w+");

    renderer = (const char *) glGetString(GL_RENDERER);
    if(renderer)
	fprintf(file,"%s\n",renderer);
    ogl_extensions = (const char *) glGetString(GL_EXTENSIONS);
    if(ogl_extensions) {
	fprintf(file,"opengl extensions:\n");
	fprintf(file,"%s\n",ogl_extensions);
    }

#ifdef WGL_DRIVER
    {
	wglGetExtensionsStringARBProc wglGetExtensionsStringARB;

	wglGetExtensionsStringARB = (wglGetExtensionsStringARBProc) wglGetProcAddress( "wglGetExtensionsStringARB" );
	if( wglGetExtensionsStringARB != null )
	    wgl_extensions = wglGetExtensionsStringARB( ogldata->hDC );

	if( wgl_extensions ) {
	    fprintf(file,"\nwgl extensions:\n");
	    fprintf(file,"%s\n",wgl_extensions);
	}
    }
#endif

    fclose(file);

	HIC_Finish_Picture(nr, swap);
}


int main (int argc, char ** argv) {

	(void)argc;
	(void)argv;

    HC_Define_Callback_Name ("finish picture", 
		    (void (HC_CDECL*)(HC_ANY_ARGS))finish_picture);
#ifdef OSX_SYSTEM
    HC_Open_Segment("?driver/cocoa_opengl/:0+0");
#else
    HC_Open_Segment("?driver/opengl/:0+0");
#endif
	HC_Set_Rendering_Options( "hsra=hzb" );
	HC_Insert_Line( -1,-1,-1, 1,1,1 );


	HC_Define_Callback_Name ("finish_picture", finish_picture);
	HC_Set_Callback ("finish picture = finish_picture");	

    HC_Close_Segment();
    HC_Update_Display();

    if( renderer != NULL && ogl_extensions != NULL ) {
	HC_Open_Segment( "?Picture" );
	    HC_Insert_Text( 0, 0, 0, renderer );
	HC_Close_Segment();
	HC_Pause();
    }

    return 0;
}
	
 
