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
 * $Id: local_texture.c,v 1.3 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void define_texture(
	const char * name, 
	const char * image_options, 
	const char * texture_options, 
	int xs, int ys, 
	unsigned char r,
	unsigned char g,
	unsigned char b,
	unsigned char a)
{
    char o[1024];
    unsigned char * p=0;
    int i, j, ox, os;

    p = (unsigned char*) malloc(xs*ys*4);

    
    for(i=0;i<ys;i++){

	ox=i*xs*4;

	for(j=0;j<xs;j++){

	    os=ox+j*4;

	    if(i%2) {
		p[os+0]=r;
		p[os+1]=g;
		p[os+2]=b;
		p[os+3]=a;
	    }else{
		p[os+0]=0;
		p[os+1]=0;
		p[os+2]=0;
		p[os+3]=255;
	    }
	}
    }

    /*
    sprintf(o,"rgb, texture options = (%s),  name = %s_image", opt, name);
    sprintf(o,"texture options = (%s),rgb,name = %s_image", opt, name);
    sprintf(o,"rgb,name = %s_image , texture options = (%s)", name , opt);
    */

    if(texture_options)
	if(image_options)
	    sprintf(o,"rgba,name = %s, texture options=(%s), %s", 
		    name, texture_options, image_options);
	else
	    sprintf(o,"rgba,name = %s, texture options=(%s)", 
		    name, texture_options);
    else
	if(image_options)
	    sprintf(o,"rgba,name = %s, %s", name, image_options);
	else
	    sprintf(o,"rgba,name = %s", name);

    HC_Set_Visibility("images=off");
    HC_Insert_Image(0.0, 0.0, 0.0, o, xs, ys, (void*)p);

    free(p);
}

static  float   square_mesh[] = {
    -0.8f, -0.8f,  0.0f,
    -0.8f,  0.8f,  0.0f,
    0.8f, -0.8f,  0.0f,
    0.8f,  0.8f,  0.0f
    };

static  float   square_mesh_param[] = {
    0.0f,  0.0f,   0.0f,
    0.0f,  1.0f,   0.0f,
    1.0f,  0.0f,   0.0f,
    1.0f,  1.0f,   0.0f
    };

HC_KEY define_surface()
{
    HC_KEY  mesh_key;
    HC_KEY  seg_key;

    HC_Open_Segment ("hide");
    	HC_Set_Visibility("off");
	seg_key = HC_KOpen_Segment ("geom");
	mesh_key= HC_KInsert_Mesh (2, 2, square_mesh);
	HC_MSet_Vertex_Parameters (mesh_key, 0, 4, 3, square_mesh_param);
	HC_Rotate_Object (25.0, 25.0, 25.0);
	HC_Close_Segment ();
    HC_Close_Segment ();

    return seg_key;
}

int main () {

    HC_KEY  key;
    char show_global_buffer[4096];
    char show_local_buffer[4096];

    HC_Open_Segment ("/");
	HC_Define_Local_Texture("test_local","source=t1");
    HC_Close_Segment(); 
    HC_Define_Texture("test_global","source=t1");

    HC_Open_Segment ("?picture");
    	HC_Set_Text_Font ("size = 0.04 wru");
	HC_Set_Text_Alignment ("*^");
	HC_Set_Color("Text=light blue");

	key = define_surface();

	HC_Open_Segment("scale_transform_1");
	    HC_Scale_Texture (4.0, 4.0, 4.0);
	HC_Close_Segment(); 

	HC_Open_Segment("scale_transform_2");
	    HC_Scale_Texture (2.0, 2.0, 2.0);
	HC_Close_Segment(); 

	HC_Open_Segment("scale_transform_3");
	    HC_Scale_Texture (0.5, 0.5, 0.5);
	HC_Close_Segment(); 

	HC_Open_Segment("scale_transform_4");
	    HC_Scale_Texture (0.25, 0.25, 0.25);
	HC_Close_Segment(); 

	HC_Open_Segment("rotate_transform_1");
	    HC_Rotate_Texture (0.0, 0.0, 0.0);
	HC_Close_Segment(); 

	HC_Open_Segment("rotate_transform_2");
	    HC_Rotate_Texture (0.0, 0.0, 45.0);
	HC_Close_Segment(); 

	HC_Open_Segment("rotate_transform_3");
	    HC_Rotate_Texture (0.0, 0.0, 90.0);
	HC_Close_Segment(); 

	HC_Open_Segment("rotate_transform_4");
	    HC_Rotate_Texture (0.0, 0.0, 135.0);
	HC_Close_Segment(); 

	HC_Open_Segment("translate_transform_1");
	    HC_Translate_Texture (0.0, 0.25, 0.0);
	HC_Close_Segment(); 

	HC_Set_Rendering_Options ("perspective correction");
	HC_Set_Visibility ("markers = off, edges = off");
	HC_Set_Camera_By_Volume ("perspective", -1.2, 1.2, -1.2, 1.2);
	HC_Set_Color("Face=(diffuse = t1, specular = t1)");
	define_texture("t1", 0, 0, 32, 32, 255, 255, 255, 255);

	/*check local and global undefine and show*/
	HC_Open_Segment ("test_locals_textures");
	    HC_Define_Local_Texture("test_not_deleted","source=local_none");
	    HC_Define_Local_Texture("test_deleted","source=local_none");
	    HC_Define_Texture("test_not_deleted","source=global_none");
	    HC_Define_Texture("test_deleted","source=global_none");
	HC_Close_Segment(); 

	HC_Open_Segment ("test_locals_textures");
	    HC_UnDefine_Local_Texture("test_deleted");
	    HC_UnDefine_Texture("test_deleted");
	HC_Close_Segment(); 

	HC_Open_Segment ("test_locals_textures");
	    HC_Show_Local_Texture("test_not_deleted",show_local_buffer);
	    HC_Show_Texture("test_not_deleted",show_global_buffer);
	HC_Close_Segment();

	if(strcmp(show_local_buffer,"source=local_none") ||
	    strcmp(show_global_buffer,"source=global_none")) {
	    printf("Show_Texture or Show_Local_Texture failed\n");
	}

#if 1
	HC_Open_Segment ("one");
	    HC_Set_Window (-1.0, -0.33, 0.0, 1.0);
	    HC_Open_Segment ("1");
		HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = red t1)");
		HC_Insert_Text (0.0, -0.9, -0.5, "32x32 red t1");
	    HC_Close_Segment ();
	    HC_Open_Segment ("2");
		HC_Set_Window (0.0, 1.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = green t1)");
		HC_Insert_Text (0.0, -0.9, -0.5, "32x32 green t1");
	    HC_Close_Segment ();
	    HC_Open_Segment ("3");
		HC_Set_Window (0.0, 1.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = blue t1)");
		HC_Insert_Text (0.0, -0.9, -0.5, "32x32 blue t1");
	    HC_Close_Segment ();
	    HC_Open_Segment ("4");
		HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = cyan t1)");
		HC_Insert_Text (0.0, -0.9, -0.5, "32x32 cyan t1");
	    HC_Close_Segment ();
	HC_Close_Segment ();

	HC_Open_Segment ("two");
	    define_texture("t1", "local", 0, 16, 16, 255, 0, 0, 255);
	    HC_Set_Color("Face=(diffuse = t1)");
	    HC_Set_Window (-0.33, 0.33, 0.0, 1.0);
	    HC_Open_Segment ("1");
		HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Rotate_Texture (0.0, 0.0, 0.0);
		HC_Insert_Text (0.0, -0.9, -0.5, "16x16 null local rotation");
	    HC_Close_Segment ();
	    HC_Open_Segment ("2");
		HC_Set_Window (0.0, 1.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Rotate_Texture (0.0, 0.0, 45.0);
		HC_Insert_Text (0.0, -0.9, -0.5, "16x16 45 local rotation");
	    HC_Close_Segment ();
	    HC_Open_Segment ("3");
		HC_Set_Window (0.0, 1.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Rotate_Texture (0.0, 0.0, 90.0);
		HC_Insert_Text (0.0, -0.9, -0.5, "16x16 90 local rotation");
	    HC_Close_Segment ();
	    HC_Open_Segment ("4");
		HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Rotate_Texture (0.0, 0.0, 135.0);
		HC_Insert_Text (0.0, -0.9, -0.5, "16x16 135 local rotation");
	    HC_Close_Segment ();
	HC_Close_Segment ();

	HC_Open_Segment ("three");
	    HC_Set_Window (0.33, 1.0, 0.0, 1.0);
	    HC_Set_Color("Face=(specular=white)");
	    HC_Define_Local_Texture("t2","source=t1, transform=\"../scale_transform_1\"");
	    HC_Define_Local_Texture("t3","source=t1, transform=\"../scale_transform_2\"");
	    HC_Define_Local_Texture("t4","source=t1, transform=\"../scale_transform_3\"");
	    HC_Define_Local_Texture("t5","source=t1, transform=\"../scale_transform_4\"");
	    HC_Open_Segment ("1");
		HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t2)");
		HC_Insert_Text (0.0, -0.9, -0.5, "32x32 4.0 scale segment");
	    HC_Close_Segment ();
	    HC_Open_Segment ("2");
		HC_Set_Window (0.0, 1.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t3)");
		HC_Insert_Text (0.0, -0.9, -0.5, "32x32 2.0 scale segment");
	    HC_Close_Segment ();
	    HC_Open_Segment ("3");
		HC_Set_Window (0.0, 1.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t4)");
		HC_Insert_Text (0.0, -0.9, -0.5, "32x32 0.5 scale segment");
	    HC_Close_Segment ();
	    HC_Open_Segment ("4");
		HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t5)");
		HC_Insert_Text (0.0, -0.9, -0.5, "32x32 0.25 scale segment");
	    HC_Close_Segment ();
	HC_Close_Segment ();

	HC_Open_Segment ("four");
	    HC_Set_Window (-1.0, -0.33, -1.0, 0.0);
	    HC_Set_Color("Face=(specular=white)");
	    define_texture("t1", "local", 0, 16, 16, 0, 0, 255, 255);
	    HC_Define_Local_Texture("t2","source=t1, transform=\"../rotate_transform_1\"");
	    HC_Define_Local_Texture("t3","source=t1, transform=\"../rotate_transform_2\"");
	    HC_Define_Local_Texture("t4","source=t1, transform=\"../rotate_transform_3\"");
	    HC_Define_Local_Texture("t5","source=t1, transform=\"../rotate_transform_4\"");
	    HC_Open_Segment ("1");
		HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t2)");
		HC_Insert_Text (0.0, -0.9, -0.5, "16x16 null rotation segment");
	    HC_Close_Segment ();
	    HC_Open_Segment ("2");
		HC_Set_Window (0.0, 1.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t3)");
		HC_Insert_Text (0.0, -0.9, -0.5, "16x16 45 rotation segment");
	    HC_Close_Segment ();
	    HC_Open_Segment ("3");
		HC_Set_Window (0.0, 1.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t4)");
		HC_Insert_Text (0.0, -0.9, -0.5, "16x16 90 rotation segment");
	    HC_Close_Segment ();
	    HC_Open_Segment ("4");
		HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t5)");
		HC_Insert_Text (0.0, -0.9, -0.5, "16x16 135 rotation segment");
	    HC_Close_Segment ();
	HC_Close_Segment ();
#endif
	HC_Open_Segment ("five");
	    HC_Set_Window (-0.33, 0.33, -1.0, 0.0);
	    HC_Set_Color("Face=(specular=white)");
	    define_texture("t1", "local", "transform=\"../rotate_transform_2\"", 16, 16, 0, 255, 0, 255);
	    HC_Define_Local_Texture("t2","source=t1, transform=\"../rotate_transform_2\"");
	    HC_Define_Local_Texture("t3","source=t2, transform=\"../scale_transform_2\"");
	    HC_Define_Local_Texture("t4","source=t3");
	    HC_Open_Segment ("1");
		HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t1)");
		HC_Insert_Text (0.0, -0.9, -0.5, "16x16 t1 45 rotate segment");
	    HC_Close_Segment ();
	    HC_Open_Segment ("2");
		HC_Set_Window (0.0, 1.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t2)");
		HC_Insert_Text (0.0, -0.9, -0.5, "t2 = t1 + 45 rotate segment");
	    HC_Close_Segment ();
	    HC_Open_Segment ("3");
		HC_Set_Window (0.0, 1.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t3)");
		HC_Insert_Text (0.0, -0.9, -0.5, "t3 = t2 + 2.0 scale segment");
	    HC_Close_Segment ();
	    HC_Open_Segment ("4");
		HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse = t4)");
		HC_Insert_Text (0.0, -0.9, -0.5, "t4 = t3 + -10 local rotate");
		HC_Rotate_Texture (0.0, 0.0, 10.0);
	    HC_Close_Segment ();
	HC_Close_Segment ();

#if 1
	HC_Open_Segment ("six");
	    HC_Set_Window (0.33, 1.0, -1.0, 0.0);
	    HC_Set_Color("Face=(diffuse = green)");
	    define_texture("trans", "local", "interpolation filter=no", 16, 16, 255, 0, 0, 128);
	    HC_Define_Local_Texture("decal","source=trans, apply mode=decal");
	    HC_Define_Local_Texture("modulate","source=trans, apply mode=modulate");
	    HC_Define_Local_Texture("decal2","source=decal, interpolation filter=on");
	    HC_Define_Local_Texture("modulate2","source=modulate, interpolation filter=on");
	    HC_Open_Segment ("1");
		HC_Set_Window (-1.0, 0.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=(diffuse=decal)");
		HC_Insert_Text (0.0, -0.9, -0.5, "decal on green interpolation off");
	    HC_Close_Segment ();
	    HC_Open_Segment ("2");
		HC_Set_Window (0.0, 1.0, 0.0, 1.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=modulate");
		HC_Insert_Text (0.0, -0.9, -0.5, "modulate on green interpolation off");
	    HC_Close_Segment ();
	    HC_Open_Segment ("3");
		HC_Set_Window (0.0, 1.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=decal2");
		HC_Insert_Text (0.0, -0.9, -0.5, "decal on green interpolation on");
	    HC_Close_Segment ();
	    HC_Open_Segment ("4");
		HC_Set_Window (-1.0, 0.0, -1.0, 0.0);
		HC_Include_Segment_By_Key(key); 
		HC_Set_Color("Face=modulate2");
		HC_Insert_Text (0.0, -0.9, -0.5, "modulate on green interpolation on");
	    HC_Close_Segment ();

	HC_Close_Segment ();

#endif
#if 1
	HC_Write_Metafile (".", "texture_test.hmf", "save state=texture, follow cross-references");
#endif
    HC_Close_Segment (); 

#if 1
    HC_Write_Metafile ("/", "texture_test_from_root.hmf", "save state=texture, follow cross-references");
#endif

    HC_Pause ();

    {
	HC_KEY segKey, tempKey;
	char pathname[4096];
	char type[80];
	char texture_name[4096];
	int texture_count;
	HC_Open_Segment("/");
	HC_Begin_Contents_Search (".", "attributes");
	while (HC_Find_Contents(type, &tempKey)){
	    if (!strcmp (type, "texture definitions")) {
		HC_Begin_Local_Texture_Search();
		HC_Show_Texture_Count(&texture_count);
		if(texture_count==1)
		    printf("%d texture definition found in segment %s\n", texture_count, "/");
		else
		    printf("%d texture definitions found in segment %s\n", texture_count, "/");
		while ( HC_Find_Texture (texture_name) ){
		    printf("%s\n", texture_name);
		}
		printf("\n");
		HC_End_Texture_Search ();
	    }
	}
	HC_End_Contents_Search();
	HC_Close_Segment();

	HC_Begin_Contents_Search("/...", "segments");
	while (HC_Find_Contents(type, &segKey)) {
	    HC_Open_Segment_By_Key(segKey);
	    HC_Show_Segment (segKey, pathname);
	    HC_Begin_Contents_Search (".", "attributes");
	    while (HC_Find_Contents(type, &tempKey)){
		if (!strcmp (type, "texture definitions")) {
		    HC_Begin_Local_Texture_Search();
		    HC_Show_Texture_Count(&texture_count);
		    if(texture_count==1)
			printf("%d texture definition found in segment %s\n", texture_count, pathname);
		    else
			printf("%d texture definitions found in segment %s\n", texture_count, pathname);
		    while ( HC_Find_Texture (texture_name) ){
			printf("%s\n", texture_name);
		    }
		    printf("\n");
		    HC_End_Texture_Search ();
		}
	    }
	    HC_End_Contents_Search();
	    HC_Close_Segment();
	}
	HC_End_Contents_Search();
    }

    HC_Exit_Program ();
    return 0;
}



