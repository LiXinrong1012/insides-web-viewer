/*
 * Copyright (c) 2006 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: ogl_shader.c,v 1.9 2010-06-12 00:19:28 jason Exp $
 */

#include "hc.h"
#include "hic.h"
#include <stdio.h>

#define USE_NO_GL
#ifdef USE_NO_GL

int main () {
	HC_Open_Segment ("?picture");
	HC_Insert_Text (0.0, 0.0, 0.0,
		"Program must be compiled without USE_NO_GL ");
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

#ifndef GL_PROGRAM_FORMAT_ASCII_ARB
#  define GL_PROGRAM_FORMAT_ASCII_ARB 0x8875
#endif
#ifndef GL_VERTEX_PROGRAM_ARB
#  define GL_VERTEX_PROGRAM_ARB 0x8620
#endif
#ifndef GL_FRAGMENT_PROGRAM_ARB
#  define GL_FRAGMENT_PROGRAM_ARB 0x8804
#endif
#ifndef GL_PROGRAM_ERROR_POSITION_ARB
#  define GL_PROGRAM_ERROR_POSITION_ARB 0x864B
#endif
#ifndef GL_PROGRAM_ERROR_STRING_ARB
#  define GL_PROGRAM_ERROR_STRING_ARB 0x8874
#endif

/*EXAMPLE OF VERTEX PROGRAM

!!ARBvp1.0
OPTION ARB_position_invariant

PARAM mvp[4] = { state.matrix.mvp };

ATTRIB in_position = vertex.position;
ATTRIB in_color    = vertex.color;

OUTPUT out_position = result.position;
OUTPUT out_color    = result.color;

DP4 out_position.x, mvp[0], in_position;
DP4 out_position.y, mvp[1], in_position;
DP4 out_position.z, mvp[2], in_position;
DP4 out_position.w, mvp[3], in_position;

MOV out_color, in_color; "

END
*/

static HT_Draw_3D_Tristrip_Action driver_draw_3d_tristrip = 0;
static HT_Free_Outer_Window_Action driver_free_outer_window = 0;

static GLuint vertex_program = (GLuint)~0;
static GLuint fragment_program = (GLuint)~0;

#define MAX_VERTEX_PROGRAM_SIZE 8192
static char vertex_program_buffer[MAX_VERTEX_PROGRAM_SIZE];
static const char *vertex_program_string = 0;

#define MAX_FRAGMENT_PROGRAM_SIZE 8192
static char fragment_program_buffer[MAX_FRAGMENT_PROGRAM_SIZE];
static const char *fragment_program_string = 0;

static void my_draw_3d_tristrip(struct ht_net_rendition const * nr, struct ht_tristrip const * pg)
{
	OGLData *ogldata = OGLNRD(nr);

	if (ogldata->supports_ARB_vertex_program && vertex_program_string && vertex_program == ~0) {

		const char *program_string = vertex_program_string;
		size_t program_length = strlen(program_string);
		char formated_error[65535];
		GLint error_location;
		const char *error;
		int i;

		if (program_length < 10) {
			printf("vertex program truncated!!!\n");
		} else {
			ogldata->glGenProgramsARB(1, &vertex_program);
			ogldata->glBindProgramARB(GL_VERTEX_PROGRAM_ARB, vertex_program);
			ogldata->glProgramStringARB(GL_VERTEX_PROGRAM_ARB,
				GL_PROGRAM_FORMAT_ASCII_ARB, program_length, program_string);

			error = (const char*)glGetString(GL_PROGRAM_ERROR_STRING_ARB);
			glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &error_location);
			if (error_location >= 0) {
				sprintf(formated_error, "vertex program error \'%s\' at --> ", error);
				for (i = error_location; i < (int) program_length; i++) {
					if (program_string[i] == '\x0A' || program_string[i] == '\x0D')
						break;
					sprintf(&formated_error[strlen(formated_error)], "%c", program_string[i]);
				}
				printf("%s\n", formated_error);
			}
		}
	}

	if (ogldata->supports_ARB_fragment_program && fragment_program_string && fragment_program == ~0) {

		const char *program_string = fragment_program_string;
		size_t program_length = strlen(program_string);
		char formated_error[65535];
		GLint error_location;
		const char *error;
		int i;

		if (program_length < 10) {
			printf("fragment program truncated!!!\n");
		} else {
			ogldata->glGenProgramsARB(1, &vertex_program);
			ogldata->glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, vertex_program);
			ogldata->glProgramStringARB(GL_FRAGMENT_PROGRAM_ARB,
				GL_PROGRAM_FORMAT_ASCII_ARB, program_length, program_string);

			error = (const char*) glGetString(GL_PROGRAM_ERROR_STRING_ARB);
			glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &error_location);
			if (error_location >= 0) {
				sprintf(formated_error, "fragment program error \'%s\' at --> ", error);
				for (i = error_location; i < (int)program_length; i++) {
					if (program_string[i] == '\x0A' || program_string[i] == '\x0D')
						break;
					sprintf(&formated_error[strlen(formated_error)], "%c", program_string[i]);
				}
				printf("%s\n", formated_error);
			}
		}
	}

	if (vertex_program != ~0) {
		ogldata->glBindProgramARB(GL_VERTEX_PROGRAM_ARB, vertex_program);
		glEnable(GL_VERTEX_PROGRAM_ARB);
	}

	if (fragment_program != ~0) {
		ogldata->glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, fragment_program);
		glEnable(GL_FRAGMENT_PROGRAM_ARB);
	}

	driver_draw_3d_tristrip(nr, pg);

	if (vertex_program != ~0) {
		glDisable(GL_VERTEX_PROGRAM_ARB);
	}

	if (fragment_program != ~0) {
		glDisable(GL_FRAGMENT_PROGRAM_ARB);
	}

}

static void my_free_outer_window(HT_Display_Context const * dc)
{

	OGLData *ogldata = OGLD(dc);

	if (vertex_program != ~0) {
		ogldata->glDeleteProgramsARB(1, &vertex_program);
		vertex_program = ~0;
	}

	if (fragment_program != ~0) {
		ogldata->glDeleteProgramsARB(1, &fragment_program);
		fragment_program = ~0;
	}

	driver_free_outer_window(dc);
}

static void my_driver_startup(HT_Net_Rendition const * nr)
{
	HT_Display_Context const *dc = (nr)->display_context;
	HT_Action_Table const *actions = &dc->actions;

	driver_draw_3d_tristrip = actions->draw_3d_tristrip;
	driver_free_outer_window = actions->free_outer_window;
	((HT_Action_Table alter *) actions)->draw_3d_tristrip = my_draw_3d_tristrip;
	((HT_Action_Table alter *) actions)->free_outer_window = my_free_outer_window;
}

typedef struct {
	float x, y, z;
} Point;

#define Set(_p,_x,_y,_z) \
	_p.x=_x; _p.y=_y; _p.z=_z;

void InsertBox(Point * max, Point * min)
{

	HC_KEY shell;
	Point points[8];
	int i;
	int face_list[30] = {
		4, 0, 1, 2, 3,
		4, 7, 6, 5, 4,
		4, 1, 5, 6, 2,
		4, 4, 0, 3, 7,
		4, 3, 2, 6, 7,
		4, 4, 5, 1, 0
	};

	const char *vcolor[] = {
		"face=red",
		"face=red",
		"face=red",
		"face=yellow",
		"face=yellow",
		"face=yellow",
		"face=red",
		"face=red"
	};

	Set(points[0], min->x, min->y, min->z);
	Set(points[1], max->x, min->y, min->z);
	Set(points[2], max->x, max->y, min->z);
	Set(points[3], min->x, max->y, min->z);
	Set(points[4], min->x, min->y, max->z);
	Set(points[5], max->x, min->y, max->z);
	Set(points[6], max->x, max->y, max->z);
	Set(points[7], min->x, max->y, max->z);

	shell = HC_KInsert_Shell(8, points, 30, face_list);
	HC_Open_Geometry(shell);

	for (i = 0; i < 8; i++) {
		HC_Open_Vertex(i);
		HC_Set_Color(vcolor[i]);
		HC_Close_Vertex();
	}
	HC_Close_Geometry();
}

int main(int argc, char **argv)
{

	Point p1, p2;
	Point center;
	float radius;
	const char *a_hmf_file = 0;
	int i;

	for (i = 1; i < argc; i++) {

		if (argv[i][0] == '-' && argv[i][1] == 'v') {

			FILE *program_file = NULL;
			if (argv[i][2] != '\0')
				program_file = fopen(&argv[i][2], "rb");
			else if (++i < argc)
				program_file = fopen(&argv[i][0], "rb");
			if (program_file) {
				size_t l = fread(vertex_program_buffer, sizeof(char),
					MAX_VERTEX_PROGRAM_SIZE, program_file);
				vertex_program_buffer[l] = '\0';
				vertex_program_string = vertex_program_buffer;
				fclose(program_file);
			} else {
				if(i < argc)
					printf("Unable open vertex program: %s\n", &argv[i][2]);
				else
					printf("Missing vertex program after -v\n");
			}
		} else if (argv[i][0] == '-' && argv[i][1] == 'f') {

			FILE *program_file = NULL;
			if (argv[i][2] != '\0')
				program_file = fopen(&argv[i][2], "rb");
			else if (++i < argc)
				program_file = fopen(&argv[i][0], "rb");
			if (program_file) {
				size_t l = fread(fragment_program_buffer, sizeof(char),
					MAX_FRAGMENT_PROGRAM_SIZE, program_file);
				fragment_program_buffer[l] = '\0';
				fragment_program_string = fragment_program_buffer;
			} else {
				if(i < argc)
					printf("Unable open fragment program: %s\n", &argv[i][2]);
				else
					printf("Missing fragment program after -f\n");
			}
		} else if (argv[i][0] == '-' && argv[i][1] == 'h') {
			if (argv[i][2] != '\0')
				a_hmf_file = &argv[i][2];
			else if (++i < argc)
				a_hmf_file = &argv[i][0];
		} else {
			fprintf(stderr, "Unable known option string: %s\n", argv[i]);
			fprintf(stderr, "%s -v<vertex program> -f<fragment program> -h<hmf file>\n", argv[0]);
		}

	}

	HC_Define_Callback_Name("my driver startup", (void (HC_CDECL *) (HC_ANY_ARGS))
		my_driver_startup);

	HC_Delete_Segment("?picture");

	HC_Open_Segment("?driver/opengl/:0+0");
	HC_Set_Rendering_Options("hsra = hzb");
	HC_Set_Visibility("markers = off, edges = on");
	HC_Set_Color("faces = red, edges = black, lights = white");
	HC_Set_Rendering_Options("lighting interpolation");
	HC_Set_Callback("driver startup = my driver startup");

	HC_Open_Segment("thing");
	if (!a_hmf_file) {
		Set(p1, -0.5f, -0.5f, -0.5f);
		Set(p2, 0.5f, 0.5f, 0.5f);
		InsertBox(&p1, &p2);
	} else {
		char cmd[8192];
		sprintf(cmd, "'%s'", a_hmf_file);
		HC_Read_Metafile(cmd, ".", "");
	}

	HC_Show_Bounding_Sphere(&center, &radius);
	HC_Set_Camera_Target(center.x, center.y, center.z);
	HC_Set_Camera_Position(3 * radius, 3 * radius, 3 * radius);
	HC_Insert_Distant_Light(3 * radius, 3 * radius, 2 * radius);

	HC_Close_Segment();

	HC_Close_Segment();

	HC_Pause();

	return 0;
}

#endif

