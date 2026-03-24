
#include <stdio.h>
#include <malloc.h>
#include "hc.h"

#define WIDTH 128
#define HEIGHT 128
#define INVALID_KEY ((HC_KEY)-1)
#define countof(x) (int)(sizeof(x)/sizeof(x[0]))

const char *create_image() 
{
	static const char *name = "checker_image";
	unsigned char *image, *ptr;
	char tempstr[128];
	int i, j, black;

	image = (unsigned char *) malloc ( 3 * WIDTH * HEIGHT * sizeof( unsigned char ));
	ptr = image;
	/* create a checkerboard pattern */
	for( j = 0 ; j < HEIGHT ; j++ ) {
		for( i = 0 ; i < WIDTH ; i++ ) {
			black = ((i / 16) & 0x1) ^ ((j / 16) & 0x1);
			if( black )
				ptr[0] = ptr[1] = ptr[2] = 0;
			else
				ptr[0] = ptr[1] = ptr[2] = 255;
			ptr += 3;
		}
	}
	sprintf( tempstr, "rgb, name=%s", name );
	HC_Insert_Image( 0, 0, 0, tempstr, WIDTH, HEIGHT, image );
	free( image );
	return name;
}


HC_KEY create_shell()
{
	int i;
	HC_KEY key = INVALID_KEY;

	float points[8][3] = {
		{    0,    0, 0 },
		{    0,    1, 0 },
		{    1,    1, 0 },
		{    1,    0, 0 },
		{ 0.2f, 0.2f, 0 },
		{ 0.2f, 0.8f, 0 },
		{ 0.8f, 0.8f, 0 },
		{ 0.8f, 0.2f, 0 }
	};
	int faces[] = { 4, 0, 1, 2, 3, -4, 4, 5, 6, 7 };

	key = HC_KInsert_Shell( countof(points), points, countof(faces), faces );
	HC_Open_Geometry( key );
		for( i = 0 ; i < countof(points) ; i++ ) {
			HC_Open_Vertex(i);
				HC_Set_Parameter( 3, points[i] );
			HC_Close_Vertex();
		}
	HC_Close_Geometry();
	return key;
}

int main()
{
	const char *texname = "my texture checkerboard";
	const char *image_name;
	char texdef[128], face_color[128];

	HC_Open_Segment( "/tmp" );
		image_name = create_image();
		sprintf( texdef, "source = %s", image_name );
		HC_Define_Texture( texname, texdef );
	HC_Close_Segment();
	HC_Open_Segment( "?Picture" );
		sprintf( face_color, "faces = %s", texname );
		HC_Set_Color( face_color );
		create_shell();
	HC_Close_Segment();
	HC_Pause();
	return 0;
}

