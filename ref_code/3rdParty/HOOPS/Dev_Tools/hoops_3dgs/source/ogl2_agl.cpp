/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: ogl2_agl.cpp,v 1.22 2010-12-10 18:55:14 warren Exp $
 */

#ifdef OSX_SYSTEM

#include "hoops.h"
#include "hd_proto.h"

#ifndef OPENGL2_DRIVER

/*
 * STUB DRIVER
 */
extern "C" bool HC_CDECL HD_OpenGL2_Driver (
	Thread_Specific_Data *	thread_data,
	Actor alter *			actor, 
	int						request, 
	void *					request_info) 
{
	UNREFERENCED(request_info);
	return HD_No_Driver (thread_data, actor, request, "opengl2");
}

#else 

#include "stdio.h"

#define DECLARE_OGL_PROTOTYPES
#include "ogl2.cpp"

static EventHandlerRef app_handler_ref = 0;
static EventHandlerUPP app_handlerUPP = 0;

#if 0
#define DEBUG_PRINTS 1
#endif

local void
choose_pixel_format (Display_Context alter * dc)
{
	HOGLData alter *ogldata = OGLD (dc);
	AGLPixelFormat pixel_format;
	GLint attrib[32];
	GLint value;
	GLint accum_buff_size = 0;
	GLint red_accum_size = 0;
	GLint green_accum_size = 0;
	GLint blue_accum_size = 0;
	GLint alpha_accum_size = 0;
	GLint anti_alias_samples = 0;
	int i = 0;
	
	attrib[i++] = AGL_RGBA;
	if (dc->options.double_buffering) attrib[i++] = AGL_DOUBLEBUFFER;
	attrib[i++] = AGL_DEPTH_SIZE;
	attrib[i++] = 16;
	if (dc->options.anti_alias_requested && dc->options.anti_alias_samples != 0) {
		attrib[i++] = AGL_SAMPLE_BUFFERS_ARB;
		attrib[i++] = 1;
		attrib[i++] = AGL_SAMPLES_ARB;
		if (dc->options.anti_alias_samples < 0)
			attrib[i++] = 2;
		else
			attrib[i++] = dc->options.anti_alias_samples;
	}
	
#ifndef AGL_GENERIC_RENDERER_ID
#define AGL_GENERIC_RENDERER_ID 0x00020200
#endif
	/* OSX software contexts can't do pbuffers, so silently ignore the request
	 to force software */
	if (dc->options.debug & Debug_FORCE_SOFTWARE &&
	    ogldata->dc_type != DCT_PBUFFER_IMAGE) {
		attrib[i++] = AGL_RENDERER_ID;
		attrib[i++] = AGL_GENERIC_RENDERER_ID;
	}
	
	if (dc->options.stencil_requested) {
		attrib[i++] = AGL_STENCIL_SIZE;
		attrib[i++] = 1;
	}
	
	attrib[i++] = AGL_ACCUM_RED_SIZE;
	attrib[i++] = 8;
	attrib[i++] = AGL_ACCUM_GREEN_SIZE;
	attrib[i++] = 8;
	attrib[i++] = AGL_ACCUM_BLUE_SIZE;
	attrib[i++] = 8;
	attrib[i++] = AGL_ACCUM_ALPHA_SIZE;
	attrib[i++] = 8;
	
	attrib[i++] = AGL_NONE;
	
	pixel_format = aglChoosePixelFormat(NULL, 0, attrib);
	
	if (!pixel_format) {
		i=0;
		attrib[i++] = AGL_RGBA;
		if (dc->options.double_buffering) attrib[i++] = AGL_DOUBLEBUFFER;
		attrib[i++] = AGL_DEPTH_SIZE;
		attrib[i++] = 16;
		attrib[i++] = AGL_NONE;
		
		pixel_format = aglChoosePixelFormat(NULL, 0, attrib);
	}
	
	if (!pixel_format) {
		i=0;
		attrib[i++] = AGL_RGBA;
		attrib[i++] = AGL_DOUBLEBUFFER;
		attrib[i++] = AGL_DEPTH_SIZE;
		attrib[i++] = 16;
		attrib[i++] = AGL_NONE;
		
		pixel_format = aglChoosePixelFormat(NULL, 0, attrib);
	}
	
	if (!pixel_format) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_SET_ATTRIBUTE, "aglChoosePixelFormat Failed");
		HD_Kill_Driver (dc);
		return;
	}
	
	/*ogldata->curr_AGLContext = aglGetCurrentContext();*/
	
	if (BIT(dc->options.debug, Debug_USE_QGL_CONTEXT)) {
		if (dc->options.use_window_ID2 != 0) {
			ogldata->curr_AGLContext = (AGLContext) dc->options.use_window_ID2;
		}
		else{
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_SET_ATTRIBUTE, "Invalid QGLContext parameter");
			HD_Kill_Driver (dc);
			return;
		}
	}
	else
		ogldata->curr_AGLContext = aglCreateContext(pixel_format, NULL);
	
	
	if (aglDescribePixelFormat(pixel_format, AGL_BACKING_STORE, &value)) {
		if (value) {
			dc->physical.double_buffer_method = Double_Buffer_SWAP;
		}else{
			dc->physical.double_buffer_method = Double_Buffer_COPY;
		}
	}
	
	/* find out the size of the accumulation buffer since we have the pixel format */
	aglDescribePixelFormat(pixel_format, AGL_ACCUM_RED_SIZE, &red_accum_size);
	aglDescribePixelFormat(pixel_format, AGL_ACCUM_GREEN_SIZE, &green_accum_size);
	aglDescribePixelFormat(pixel_format, AGL_ACCUM_BLUE_SIZE, &blue_accum_size);
	aglDescribePixelFormat(pixel_format, AGL_ACCUM_ALPHA_SIZE, &alpha_accum_size);
	accum_buff_size = red_accum_size + green_accum_size + blue_accum_size + alpha_accum_size;
	ogldata->accumulation_bits = accum_buff_size;
	
	aglDescribePixelFormat(pixel_format, AGL_SAMPLES_ARB, &anti_alias_samples);
	ogldata->can_anti_alias = (anti_alias_samples != 0);
	//ogldata->anti_alias_samples = anti_alias_samples;
	
	aglDestroyPixelFormat(pixel_format);
	
	if (!ogldata->curr_AGLContext) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_SET_ATTRIBUTE, "aglCreateContext Failed");
		HD_Kill_Driver (dc);
		return;
	}
	
} /* end function 'choose pixel format' */

/*
 * HELPER
 */
local void
identify_renderer (Display_Context alter * dc) {
	HOGLData alter *ogldata = OGLD (dc);
	char const *test;
	char const *version;

	test = (char const *) glGetString (GL_RENDERER);
	if (test) {
		if (ogldata->card_entry)
			HI_Free_Driver_Config(ogldata->card_entry);
		version = (char const *) glGetString (GL_VERSION);
		if (!version)
			version = "*";

		NAMEFREE(dc->physical.driver_config_id);
		NAMEFREE(dc->physical.driver_config_version);
		HI_Copy_Chars_To_Name(test, &dc->physical.driver_config_id);
		HI_Copy_Chars_To_Name(version, &dc->physical.driver_config_version);
		dc->physical.card_entry = ogldata->card_entry = HI_Lookup_Driver_Config(dc->thread_data, "opengl2", test, version, true, xbit_table);	
	}

	if (!BIT(ogldata->card_entry->flags, HTDF_SOFTWARE)) {
		dc->physical.driver_type = ogl_hardware_string;
		ogldata->is_software = false;
	}else {
		dc->physical.driver_type = ogl_software_string;
		ogldata->is_software = true;
	}	
	ogldata->has_r32f_texture = false;
}


void handle_size_change(Display_Context alter * dc)
{
	Display_Context alter *dcalter = (Display_Context alter *) dc;
	HOGLData alter *ogldata = OGLD (dcalter);

	ogldata->h3d_actions->set_targets(null);
	H_SAFE_DELETE(ogldata->render_target);
	H_SAFE_DELETE(ogldata->depth_stencil);
	H_SAFE_DELETE(ogldata->dummy_target);
	
	ogldata->render_target = new HOGLRenderTarget(ogldata, ogldata->window_width, ogldata->window_height, 
		H3DTEXUSAGE_RENDERTARGET, H3DFMT_A8R8G8B8, ogldata->antialias_samples);

	ogldata->depth_stencil = new HOGLRenderTarget(ogldata, ogldata->window_width, ogldata->window_height, 
		H3DTEXUSAGE_DEPTHSTENCIL, H3DFMT_D24S8, ogldata->antialias_samples);

	// Set viewport to entire image (so we don't see an invalid viewport in the cache during drawing)
	FORCE_VIEWPORT(ogldata, 0, 0, ogldata->window_width, ogldata->window_height);

	ogldata->h3d_actions->set_targets(ogldata->render_target, ogldata->depth_stencil);
}

local void
unset_ogl (Display_Context const * dc) {
	
	HOGLData alter *ogldata = OGLD (dc);
	
	aglSetCurrentContext(NULL);
	aglSetDrawable(ogldata->curr_AGLContext, NULL);
	//aglSetWindowRef(ogldata->curr_AGLContext, NULL);
	aglDestroyContext(ogldata->curr_AGLContext);
	ogldata->curr_AGLContext = 0;
	
	if (ogldata->prev_AGLContext) {
		aglSetCurrentContext (ogldata->prev_AGLContext);
		ogldata->prev_AGLContext = 0;
	}
	
	if (ogldata->prev_GrafPtr) {
		SetPort (ogldata->prev_GrafPtr);
		ogldata->prev_GrafPtr = 0;
	}	
}


/*
 * ACTION
 */
void finish_picture (Net_Rendition const &  nr,
				bool swap_buffers) 
{
	Display_Context const *dc = nr->display_context;
	HOGLData alter *ogldata = OGLNRD (nr);
	
	glFlush();
	if (dc->thread_data->update_end_time_check != 0)
		glFinish();
	
	if (ogldata->render_target) {
		// For SSAA, filter the blit. For MSAA, specify none to get hardware resolve.
		H3DTEXTUREFILTERTYPE filter = (ogldata->antialias_mode == SUPERSAMPLE_ANTIALIASING) ? 
		H3DTEXF_LINEAR : H3DTEXF_POINT; 
		
		// SIL: OpenGL respects scissor test when blitting, so ensure that this is disabled.
		ENSURE_SCISSOR(ogldata, false);
		
		stretch_rect(ogldata, ogldata->render_target, 0, filter);
	}
	
	if (ogldata->dc_type == DCT_IMAGE) {
		if (!BIT (dc->flags, DCF_outer_window_exists))	// probably shutting down the driver
			return;

		if (!BIT(ogldata->output_image->flags, IF_DL_ONLY))
			HI_Clear_Image_Cache(ogldata->output_image);
		else {
			if (ogldata->output_image->block) {
				FREE_ARRAY(ogldata->output_image->block, ogldata->output_image->width * ogldata->output_image->height * ogldata->output_image->bytes_per_pixel, char);
				ogldata->output_image->block = null;
			}
		}
		
		if (BIT(dc->flags, DCF_outer_window_exists))
			HI_Set_Delayed_Activity (ogldata->output_image->owner, Act_SET_GEOMETRY_REDRAW_WITHIN,
									 ogldata->output_image, Act_SET_GEOMETRY_MODIFIED);
	}
	
	if (/*!CHECK_INTERRUPED(dc) &&*/ BIT(dc->flags, DCF_outer_window_exists)) {
		if (ogldata->dc_type == DCT_IMAGE) {
			RGB24 alter *ptr;
			int w, h;
			w = ogldata->output_image->width;
			h = ogldata->output_image->height;
			if (ogldata->output_image->format == Image_DEPTH_FLOAT32) {
				// This is currently handled in finish_depth_effects
			}
			else {
				if (ogldata->output_image->format == Image_RGB24)
					ptr = (RGB24 alter *)ogldata->output_image->block;
				else
					ALLOC_ARRAY (ptr, w*h, RGB24);
				snapshot (nr, w, h, (unsigned char alter *)ptr);
				if (ptr != ogldata->output_image->block) {
					swizzle_rgb24 (ptr, w, h, 
								   ogldata->output_image->format, 
								   (void alter *)ogldata->output_image->block);
					FREE_ARRAY (ptr, w*h, RGB24);
				}
			}
		}
		
		else if (!BIT(dc->flags, DCF_compile_only)){
			UNREFERENCED(swap_buffers);
			//SwapBuffers (ogldata->hDC);
			aglSwapBuffers(ogldata->curr_AGLContext);
		}
	}
	
	FREE_VB_TEMP(ogldata);
	FREE_IB_TEMP(ogldata);
	
}

/*
 * ACTION
 */
void init_picture (Net_Rendition const &  nr)
{
	Display_Context const *dc = nr->display_context;
	HOGLData alter *ogldata = OGLD (dc);
	
	// Force GPU to consume command buffer and go idle.
	if (dc->thread_data->update_end_time_check == 0)
		flush_device(ogldata);
	
	ogldata->cache->depth_test_reversed = BIT(nr->transform_rendition->flags , TR_REVERSE_DEPTH_TEST);
	FORCE_ZBUFFERING (ogldata, BIT(nr->transform_rendition->flags, TR_Z_BUFFERING));
	
	if (!BIT(dc->flags, DCF_simple_shadow_processing)) {
		if (ogldata->dc_type == DCT_IMAGE) {
			Image alter				*image;
			
			image = (Image alter *)KEY_TO_POINTER (dc->thread_data, dc->options.use_window_ID);
			if (image != ogldata->output_image) {
				/* TODO: check for image size change */
				if (image == null) {
					HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
							  "An invalid key was passed to the OpenGL2 driver with USE_WINDOW_IS_IMAGE set."); 
					return;
				}
				INUTILE (ogldata->output_image);
				ogldata->output_image = image;
				UTILE (ogldata->output_image);
			}
		}
	}
	
	if (!ogldata->has_scene_began) {
		// First choose depth effects, if any.
		choose_depth_effects(ogldata);
		
		// Choose AA mode based on user's request and our constraints.
		AntialiasMode requested_mode = NO_ANTIALIASING;
		int requested_samples = 0;
		if ( ogldata->dc->options.anti_alias_requested ) {
			requested_samples = ogldata->dc->options.anti_alias_samples;
			requested_mode = ogldata->depth_effects.enabled ? SUPERSAMPLE_ANTIALIASING : MULTISAMPLE_ANTIALIASING;
			//if (XBIT_TEST(ogldata->card_entry->xbits, XBIT_BAD_MSAA_SPRITING))
			//requested_mode = SUPERSAMPLE_ANTIALIASING;
		}
		
		// SIL: Rendertargets are now allocated in set_antialias_mode. It must be called in init_picture
		set_antialias_mode(ogldata, requested_mode, requested_samples );
		
		
		// Setup for depth-dependent effects
		if (ogldata->depth_effects.enabled)
			init_depth_effects(ogldata, dc->update_slice);
		
		ogldata->has_scene_began = true;
	}
	
	ENSURE_COLOR_MASK (ogldata, !nr->misc_rendition->mask_color_image);
	ENSURE_CHANNEL_MASK (ogldata, H3DMASK_RGB);	
}


/*forward*/
local void
check_events (HOGLData alter * ogldata);

/*
 * ACTION
 */
void finish_update (Display_Context const * dc) {
	HOGLData alter *ogldata = OGLD (dc);
	if (!BIT(dc->flags, DCF_outer_window_exists))
		return;
	
	if (ogldata->dc_type == DCT_OUR_WINDOW)
		if (!dc->options.disable_all_input &&
			!BIT (dc->options.debug, Debug_NO_WINDOWS_HOOK))
			check_events (ogldata);
	
	aglSetCurrentContext(0);
	
	if (ogldata->prev_AGLContext) {
		aglSetCurrentContext (ogldata->prev_AGLContext);
		ogldata->prev_AGLContext = 0;
	}
	
	if (ogldata->prev_GrafPtr) {
		SetPort (ogldata->prev_GrafPtr);
		ogldata->prev_GrafPtr = 0;
	}

}


/*
 * ACTION
 */
void init_update (Display_Context const * dc) 
{
	HOGLData alter *ogldata = OGLD (dc);
	OSStatus err;
	int using_qgl_context = 0;	
	
	if (BIT(dc->options.debug, Debug_USE_QGL_CONTEXT)) {
		using_qgl_context = -1;
	}
	
	if (!BIT(dc->flags, DCF_outer_window_exists))
		return;
	
	if (ogldata->dc_type == DCT_OUR_WINDOW) {
		if (!dc->options.disable_all_input &&
			!BIT (dc->options.debug, Debug_NO_WINDOWS_HOOK))
			check_events (ogldata);
		/* This next line is QUITE necessary to refresh the pointer */
		ogldata = OGLD (dc);
		
		if (!ogldata) 
			return;
	}
	
	ogldata->prev_AGLContext = aglGetCurrentContext();
	
	if (ogldata->dc_type == DCT_PBUFFER_IMAGE) {
		int vs = 0;
		if (!aglSetPBuffer(ogldata->curr_AGLContext, ogldata->pbuffer, 0, 0, vs)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
					  "Unable to set OpenGL pbuffer rendering context in ogl2_agl:init update");
			HD_Kill_Driver (dc);
		}		
	}
	else {
		
		int * override = ogldata->use_clip_override;
		GLint bufferRect[4];
		Rect rect;
		
		if (!ogldata->window || !IsValidWindowPtr(ogldata->window))
			return;
		ogldata->prev_GrafPtr = 0;
		GetPort (&ogldata->prev_GrafPtr);
		
#define OUTER_OVERRIDE_X 0
#define OUTER_OVERRIDE_Y 1
#define OUTER_OVERRIDE_W 2
#define OUTER_OVERRIDE_H 3
#define INNER_OVERRIDE_X 4
#define INNER_OVERRIDE_Y 5
#define INNER_OVERRIDE_W 6
#define INNER_OVERRIDE_H 7
		
		if (ogldata->dc_type == DCT_THEIR_WINDOW && override) {
			
			rect.left	= override[OUTER_OVERRIDE_X] + override[INNER_OVERRIDE_X];
			rect.right	= rect.left + override[INNER_OVERRIDE_W]; 
			
			rect.bottom = override[OUTER_OVERRIDE_Y] + override[OUTER_OVERRIDE_H] - override[INNER_OVERRIDE_Y];
			rect.top	= rect.bottom - override[INNER_OVERRIDE_H];
			
		}else{
			err = GetWindowBounds (ogldata->window, kWindowContentRgn, &rect);
		}
		
		if (	(rect.right-rect.left != ogldata->window_width) || 
			(rect.bottom-rect.top != ogldata->window_height) ||
			(override && (
						  (ogldata->last_clip_override[OUTER_OVERRIDE_X] != override[OUTER_OVERRIDE_X]) ||
						  (ogldata->last_clip_override[OUTER_OVERRIDE_Y] != override[OUTER_OVERRIDE_Y]) ||
						  (ogldata->last_clip_override[OUTER_OVERRIDE_W] != override[OUTER_OVERRIDE_W]) ||
						  (ogldata->last_clip_override[OUTER_OVERRIDE_H] != override[OUTER_OVERRIDE_H]) ||
						  (ogldata->last_clip_override[INNER_OVERRIDE_X] != override[INNER_OVERRIDE_X]) ||
						  (ogldata->last_clip_override[INNER_OVERRIDE_Y] != override[INNER_OVERRIDE_Y]) ||
						  (ogldata->last_clip_override[INNER_OVERRIDE_W] != override[INNER_OVERRIDE_W]) ||
						  (ogldata->last_clip_override[INNER_OVERRIDE_H] != override[INNER_OVERRIDE_H]))) 
			) {
			
			ogldata->window_width = rect.right-rect.left;
			ogldata->window_height = rect.bottom-rect.top;
			
			if (override) {
				int i = 0;
				for (i = 0; i < 8; i++)
					ogldata->last_clip_override[i] = override[i];
			}
			
			ogldata->yfudge = (rect.bottom-rect.top);
			
#if 0
			printf("resized %d %d %d %d %d %d\n",
				   rect.left, rect.top, rect.right, rect.bottom,
				   rect.right-rect.left, rect.bottom-rect.top);
#endif
			
			if (!aglUpdateContext (ogldata->curr_AGLContext)) {
				HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY,
						  "Unable to Update Current OpenGL Rendering Context");
				HD_Kill_Driver (dc);
				return;
			}
			
			HD_Resize_Subscreen (dc, true,
								 0, (rect.right-rect.left)-1, 
								 0, (rect.bottom-rect.top)-1);
			
			if (!using_qgl_context && ogldata->dc_type == DCT_THEIR_WINDOW && override) {
				
				/*left*/
				bufferRect[0] = override[INNER_OVERRIDE_X];
				
				/*bottom*/
				bufferRect[1] = override[INNER_OVERRIDE_Y];
				
				/*width*/
				bufferRect[2] = override[INNER_OVERRIDE_W];
				
				/*height*/
				bufferRect[3] = override[INNER_OVERRIDE_H];
				
#if 0
				printf("AGL_BUFFER_RECT lbwh: %ld %ld %ld %ld\n",		
					   bufferRect[0], bufferRect[1], bufferRect[2], bufferRect[3]);
#endif
				
				aglSetInteger(ogldata->curr_AGLContext, AGL_BUFFER_RECT, bufferRect);
				aglEnable(ogldata->curr_AGLContext, AGL_BUFFER_RECT);
				
				if (BIT (ogldata->dc->options.debug, Debug_OSX_UNDERLAY) && 
					ogldata->dc_type == DCT_THEIR_WINDOW)
				{
					CGContextRef cgx;
					CGRect cgr;
					
					QDBeginCGContext(GetWindowPort(ogldata->window), &cgx);
					cgr.origin.x = 0;
					cgr.origin.y = 0;
					cgr.size.width = rect.right-rect.left;
					cgr.size.height = rect.bottom-rect.top;
					CGContextClearRect(cgx, cgr);
					QDEndCGContext(GetWindowPort(ogldata->window), &cgx);
				} 
			}
		}
		SetPort ((GrafPtr) GetWindowPort (ogldata->window));
	}
	
	ogldata->prev_AGLContext = aglGetCurrentContext();
	if (!aglSetCurrentContext (ogldata->curr_AGLContext)) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY,
				  "Unable to Make Current OpenGL Rendering Context");
		HD_Kill_Driver (dc);
		return;
	}
}

/*****************************************************************************
 *****************************************************************************
							FONT_ACTIONS
 *****************************************************************************
 *****************************************************************************/

struct OGLFontData {
	GLuint list[0xFFFF];
	FMFontFamily family;
	OSX_Style face;
};

/*
 * ACTION
 */
local void
find_all_fonts (Display_Context alter * dc) {
	
	const char * font_names[] = {
		"applFont", "los Angeles", "athens","monaco", "Futura",
		"cairo", "sanFran", "courier","times" ,
		"Geneva","symbol", "helvetica", "systemFont",
	"mobile","toronto", "new York","venice", "london",""}; 
	
	
	Str255 pstr;
	short f;
	int n=0;
	

	return;	
}

/*
 *	* ACTION
 *	 */
local bool measure_char(
	Net_Rendition const & nr,
	Font_Instance const * instance,
	Karacter kar,
	float alter *size_out,
	bool alter *kar_missing,
	void ** per_kar_data) 
{
		
	OGLFontData *fontdata = (OGLFontData *) instance->identifier;
	
	int width;
	
	/*
	 FontInfo info;
	 GetFontInfo(&info);
	 */
	
	TextFont(fontdata->family);
	TextFace(fontdata->face);
	TextSize(instance->vspace);
	
	width = TextWidth((void*)&kar, 0, 2);
	
	/*
	 printf("measure_char %d %d\n",(int)kar, (int)width);
	 */
	
#if 0
	*size_out = 0.0f;
	*kar_missing = true;
	*per_kar_data=(void*)0;
#endif
	
	*size_out = (float)width;
	*kar_missing = false;
	*per_kar_data=(void*)1;
	
	return true;
	
	
}

/*
 * ACTION
 */
local void * 
load_font (Display_Context const * dc,
		   char const * name,
		   Font_Instance alter * instance) {
	
	OGLFontData alter *fontdata;
	Str255 pstr;
	short f;
	
	ALLOC (fontdata, OGLFontData);
	
#if 0
	c2pstrcpy(pstr,name);
	fontdata->family = FMGetFontFamilyFromName(pstr);
#else
	c2pstrcpy(pstr,name);
	GetFNum(pstr, &f);
	fontdata->family = f;
#endif
	
	/*
	 printf("load_font %s \n", name);
	 */
	if (fontdata->family == kInvalidFontFamily) {
		FREE (fontdata, OGLFontData);
		return 0;
	}
	
	/*
	 printf("load_font worked\n");
	 */
	fontdata->face=0;
	
	SET_MEMORY(fontdata->list, sizeof(GLuint)*0xFFFF,0);
	
	return (void *) fontdata;
}


/*
 * ACTION
 */
local void HC_CDECL draw_font (
	Net_Rendition const &	nr,
	Font_Instance const		*instance,
	Point const				*position,
	int							count,
	Karacter const			*kp,
	Vector const				*scale) {

	HD_Draw_Stenciled_Font (nr, instance, position, count, kp, scale);
	
}


/*
 * ACTION
 */
local void
unload_font (Display_Context const * dc, 
			 Font_Instance alter *instance) 
{
	//HOGLData alter *ogldata = OGLD (dc);
	
	OGLFontData const *fontdata = (OGLFontData const *) instance->identifier;
	int i;
	
	/*
	 printf("unload_font\n");
	 */
	if (!fontdata) return;
	
	for (i=0;i<0xFFFF;i++) {
		
		if (fontdata->list[i])
			glDeleteLists (fontdata->list[i], 1);
	}
	
	FREE (fontdata, OGLFontData);
}



/*****************************************************************************
 *****************************************************************************
						Physical Info routines
 *****************************************************************************
 *****************************************************************************/


/*
 * ACTION
 */
void get_current_info (Display_Context alter * dc) {
	HOGLData alter *ogldata = OGLD (dc);
	GDHandle device; 
	
	if (ogldata->device == 0)
		device = ogldata->info_device;
	else
		device = ogldata->device;
	
	if (dc->options.use_window_ID != 0) {
		dc->options.subscreen_moving = true;
		dc->options.subscreen_resizing = true;
		dc->options.subscreen_stretching = true;
		dc->options.subscreen_by_program = false;
	}
#if 0
	if (ogldata->curr_AGLContext) {
		GLint bits[3] = { 0, 0, 0 };
		
		glGetIntegerv (GL_RED_BITS, bits);
		glGetIntegerv (GL_BLUE_BITS, bits + 1);
		glGetIntegerv (GL_GREEN_BITS, bits + 2);
		ogldata->color_planes = bits[0] + bits[1] + bits[2];
	}
#endif
	/* OpenGL always takes 8 bits per rgb */
	dc->current.number_of_colors = 1L << 24;
	dc->current.first_color = 0;
	
	if (ogldata->dc_type == DCT_PBUFFER_IMAGE) {
		dc->current.extent.left = (float) 0;
		dc->current.extent.right = (float) dc->physical.number_of_pixels.x - 1;
		dc->current.extent.bottom = (float) 0;
		dc->current.extent.top = (float) dc->physical.number_of_pixels.y - 1;
	}
	else if (ogldata->window) {
		int *override = ogldata->use_clip_override;
		Rect rect;
		
		if (ogldata->dc_type == DCT_THEIR_WINDOW && override) {
			rect.left	= override[OUTER_OVERRIDE_X] + override[INNER_OVERRIDE_X];
			rect.right	= rect.left + override[INNER_OVERRIDE_W]; 
			rect.bottom = override[OUTER_OVERRIDE_Y] + override[OUTER_OVERRIDE_H] - override[INNER_OVERRIDE_Y];
			rect.top	= rect.bottom - override[INNER_OVERRIDE_H];
		} else {
			GetWindowBounds (ogldata->window, kWindowContentRgn, &rect);
		}
		
		dc->current.extent.left = (float) rect.left;
		dc->current.extent.right = (float) rect.right - 1;
		dc->current.extent.bottom = (float) (ogldata->y_screen_fudge - (rect.bottom - 1));
		dc->current.extent.top = (float) (ogldata->y_screen_fudge - rect.top);
	}
	else{
		GDHandle device; 
		
		if (ogldata->device == 0)
			device = ogldata->info_device;
		else
			device = ogldata->device;
		
		dc->current.extent.left = 0.0f;
		dc->current.extent.right = (float) (*device)->gdRect.right;
		dc->current.extent.bottom = (float) (*device)->gdRect.bottom;
		dc->current.extent.top = 0.0f;
	}
	
}


/*forward*/
local void get_actions (Action_Table alter &);

/*
 * ACTION
 */
void get_physical_info (Display_Context alter * dc) 
{
	HOGLData alter *ogldata = OGLD (dc);
	
	GDHandle device; 	
	
	if (ogldata->device == 0)
		device = ogldata->info_device;
	else
		device = ogldata->device;
	
	dc->physical.flags |= DCPF_load_font_requires_window;
	
	/* We do not do absolute coordinates */
	dc->physical.absolute_coordinates = false;
	
	if (ogldata->dc_type == DCT_IMAGE ||
		ogldata->dc_type == DCT_PBUFFER_IMAGE) {
		
		dc->physical.number_of_pixels.x = ogldata->output_image->width;
		dc->physical.number_of_pixels.y = ogldata->output_image->height;
		dc->physical.size.x = dc->physical.number_of_pixels.x *  (2.54f /72.0f);
		dc->physical.size.y = dc->physical.number_of_pixels.y *  (2.54f /72.0f);
	}
	else {
		short HRes,VRes;
		
		ScreenRes(&HRes, &VRes);
		
		dc->physical.number_of_pixels.x = (*device)->gdRect.right;
		dc->physical.number_of_pixels.y = (*device)->gdRect.bottom;
		dc->physical.size.x = ((*device)->gdRect.right / (float)HRes) * 2.54f;
		dc->physical.size.y = ((*device)->gdRect.bottom / (float)VRes) * 2.54f;
	}
	
	if (dc->options.physical_size.x != -1) {
		dc->physical.size.x = dc->options.physical_size.x;
		dc->physical.size.y = dc->options.physical_size.y;
	}
	
	ogldata->yfudge = ogldata->y_screen_fudge = dc->physical.number_of_pixels.y - 1;
	
	/* put in reasonable numbers here...just in case the test window fails */
	dc->physical.nominal_color_resolution = 256;
	dc->physical.color_system = DIRECT_RGB;
	dc->physical.driver_type = "AOGL";
	dc->physical.driver_version = "$Revision: 1.22 $";
	dc->physical.display_type = "frame buffer";
	dc->physical.locater_type = "mouse";
	
	/* extra capabilities set to false until we see a valid context */
	dc->physical.flags &= ~DCPF_has_gouraud_shading;
	dc->physical.flags &= ~DCPF_has_gouraud_lighting;
	
	dc->physical.flags &= ~DCPF_needs_gamma_correction;
	
	ogldata->can_stencil = false;

	ogldata->caps.max_primitive_count = MAX_INT;
	ogldata->caps.shader_model = SHADER_MODEL_3;
	dc->physical.max_view_dependent_shadow_maps = 4;
	
	/*
	 * WARNING:	 because there is alot of information that we do NOT
	 * know until an OpenGL-visual-equipped window is mapped, we do
	 * an update physical info in setup ogl
	 * This fills in various information (especially about the number
	 * of planes available since it is cut in half when you do double
	 * buffering) that should logically be done here... do an
	 * update_physical_info here but remember that this info may change...
	 */
	if (ogldata->curr_AGLContext)
		update_physical_info (dc);
	
	/* Double Buffering Option is always available in OpenGL */
	dc->physical.double_buffer_method = Double_Buffer_SWAP;
	
	/* extra capabilities */
	dc->physical.flags |= DCPF_has_gouraud_shading;
	dc->physical.flags |= DCPF_has_gouraud_lighting;
	
	dc->physical.hardware_lights = 1; /*this keeps upper level happy*/
	
	if (BIT (dc->options.debug, Debug_NO_OGL_OVERLAY_PLANES))
		dc->physical.flags |= DCPF_cannot_overlay_at_all;
	
	dc->physical.flags |= DCPF_has_locater;
	dc->physical.number_of_locater_buttons = 3;
	
	dc->physical.flags |= DCPF_can_mask_color_image;
	dc->physical.flags |= DCPF_can_reverse_depth_test;
}


static EventTypeSpec app_events[] = {
{ kEventClassAppleEvent, kEventAppleEvent },
};

static pascal OSStatus our_app_event_handler(EventHandlerCallRef er, EventRef event, void* userData)
{
	OSStatus			result = eventNotHandledErr;
	
	UInt32				iclass = GetEventClass (event);
	UInt32				kind = GetEventKind (event);
	
#if 0
	OGLData *ogldata = (OGLData*)userData;
	WindowRef			window = NULL;
#endif
	
	switch (iclass) {
			
		case kEventClassAppleEvent:
			
			switch (kind) {
				case kEventAppleEvent: 
				{
					OSType aeID, aeClass;
					
					GetEventParameter(event, kEventParamAEEventClass, typeType,
									  NULL, sizeof(aeClass), NULL, &aeClass);
					GetEventParameter(event, kEventParamAEEventID, typeType,
									  NULL, sizeof(aeID), NULL, &aeID);
					if (aeClass == kCoreEventClass) {
						
						switch (aeID) {
							case kAEQuitApplication: 
								
								result = noErr;
								break; 
							default:{
								EventRecord record;
								if (ConvertEventRefToEventRecord(event, &record)) {
									
									if (noErr == AEProcessAppleEvent(&record)) {
										result = noErr;
									}
									
								}else{
									/*
									 printf("failed to ConvertEventRefToEventRecord()");
									 */
								}	
							}
								break;
						}
					}else{
						/*
						 printf("unknown");
						 */
					}
				} 
					break;
					
				default:
					/*
					 printf("default");
					 */
					break;
			}
			break;
			
		default: 
			/*
			 printf("unknown class %c%c%c%c", 
			 (char)(iclass>>24), 
			 (char)((iclass>>16)&255), 
			 (char)((iclass>>8)&255),
			 (char)(iclass&255));
			 */
			break;
	}
	return result;
}

local void
consume_mouse(HOGLData *ogldata, EventRef event)
{
	EventMouseButton button = 0;
	OSX_Point location = {0, 0};
	UInt32 modifiers = 0;
	Rect rect;
	
	UInt32 kind = GetEventKind (event);
	
	GetEventParameter(event, kEventParamMouseButton, typeMouseButton, NULL, sizeof(EventMouseButton), NULL, &button);
	GetEventParameter(event, kEventParamMouseLocation, typeQDPoint, NULL, sizeof(Point), NULL, &location); 
	GetEventParameter(event, kEventParamKeyModifiers, typeUInt32, NULL, sizeof(UInt32), NULL, &modifiers);
	
	GetWindowBounds (ogldata->window, kWindowContentRgn, &rect);
	
	if (!(location.v>rect.top)) return;
	
	if (modifiers & controlKey) {
		button = kEventMouseButtonSecondary;
	}
	
	switch (kind) {
		case kEventMouseDown:
			
			switch (button) {
				case kEventMouseButtonSecondary:
				{
					ogldata->mouse_buttons |= RIGHT_MOUSE;
				}
					break;
				case kEventMouseButtonTertiary:
				{
					ogldata->mouse_buttons |= MIDDLE_MOUSE;
				}
					break;
				case kEventMouseButtonPrimary:
				{
					ogldata->mouse_buttons |= LEFT_MOUSE;
				}
					break;
			}
			
			break;
			
		case kEventMouseUp:
			
			switch (button) {
				case kEventMouseButtonSecondary:
				{
					ogldata->mouse_buttons &= ~RIGHT_MOUSE;
				}
					break;
				case kEventMouseButtonTertiary:
				{
					ogldata->mouse_buttons &= ~MIDDLE_MOUSE;
				}
					break;
				case kEventMouseButtonPrimary:
				{
					ogldata->mouse_buttons &= ~LEFT_MOUSE;
				}
					break;
			}
			
			break;
			
		case kEventMouseDragged:
			break;
		default:
			break;
	}
	
	ogldata->mouse_x = location.h-rect.left-1;
	ogldata->mouse_y = ogldata->yfudge - (location.v-rect.top-1);
	
	HD_Queue_Pixel_Location_Event (ogldata->dc, ogldata->mouse_buttons,
								   ogldata->mouse_x, ogldata->mouse_y);
	
	ogldata->mouse_was_queued = true;
	
}

static void consume_key(HOGLData *ogldata, EventRef event)
{
	UInt32 key_code;
	UInt32 key_mod;
	UInt32 key;
	int status = 0;
	
#define B_SHIFT					0x00000100
#define B_CONTROL				0x00000200 
#define B_NUM_LOCK				0x00000400
#define B_ALT					0x00000800
#define B_CAPS_LOCK				0x00001000
#define B_SCROLL_LOCK			0x00002000
#define B_LEFT_SHIFT			0x00004000
#define B_RIGB_SHIFT			0x00008000
#define B_RIGB_CONTROL			0x00010000
#define B_LEFT_CONTROL			0x00020000
#define B_RIGB_ALT				0x00040000
#define B_LEFT_ALT				0x00080000
	
	GetEventParameter (event, kEventParamKeyCode, typeUInt32, NULL, sizeof(UInt32), NULL, &key_code);
	GetEventParameter (event, kEventParamKeyModifiers, typeUInt32, NULL, sizeof(UInt32), NULL, &key_mod);
	
	if (key_mod & shiftKey) {
		status |= B_SHIFT;
	}
	if (key_mod & controlKey) {
		status |= B_CONTROL;
	}
	if (key_mod & optionKey) {
		status |= B_ALT;
	}
	
	/*TODO
	 if (key_mod &&) status |= B_NUM_LOCK;
	 if (key_mod &&) status |= B_CAPS_LOCK;
	 if (key_mod &&) status |= B_SCROLL_LOCK;
	 */
	
	key = KeyTranslate((void *)GetScriptManagerVariable(smUnicodeScript), 
					   key_mod | key_code, &ogldata->key_state);
	
	switch (key) {
		case kHelpCharCode:			key = MAC_HELP_KEY; break;
		case kEndCharCode:			key = END_KEY; break;
		case kPageUpCharCode:		key = PAGE_UP_KEY; break;
		case kHomeCharCode:			key = HOME_KEY; break;
		case kPageDownCharCode:		key = PAGE_DOWN_KEY; break;
			
		case kBackspaceCharCode:	key = RUBOUT_KEY; break;
			
		case kLeftArrowCharCode:	key = LEFT_ARROW_KEY; break;
		case kRightArrowCharCode:	key = RIGHT_ARROW_KEY; break;
		case kUpArrowCharCode:		key = UP_ARROW_KEY; break;
		case kDownArrowCharCode:	key = DOWN_ARROW_KEY; break;
		default:break;
	}
	
	if ((key_mod & 0x00010000L) && (key >= '0' && key<= '9')) {
		key = FIRST_KEYPAD_KEY + key - '0';
	}
	
	HI_Queue_Keyboard_Event ((Actor alter *)ogldata->dc->actor, key, status);
	
}


static pascal OSStatus our_window_handler(EventHandlerCallRef myHandler, EventRef event, void* userData)
{
	OSStatus result = eventNotHandledErr;
	UInt32 iclass = GetEventClass (event);
	UInt32 kind = GetEventKind (event);
	HOGLData *ogldata = (HOGLData*)userData;
	
	Display_Context alter *dc;
	
	if ((dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT) ogldata->window)) != null) {
		
		switch (iclass) {
			case kEventClassMouse:
				consume_mouse(ogldata, event);
				break;
				
			case kEventClassKeyboard:
				
				switch (kind) {
					case kEventRawKeyDown:
						consume_key(ogldata, event);
						result = noErr;
						break;
					default: break;
				}
				break;
			case kEventClassWindow:
				/*
				 printf("kEventClassWindow ");
				 */
				/*
				 GetEventParameter(event, kEventParamDirectObject, typeWindowRef, NULL, sizeof(WindowRef), NULL, &window);
				 */
				switch (kind) {
					case kEventWindowCollapsing:
						/*
						 printf("kEventWindowCollapsing\n");
						 */
						break;
					case kEventWindowActivated: 
						/* called on click activation and initially
						 printf("kEventWindowActivated\n");
						 */
						break;
					case kEventWindowDrawContent:
					{
						/*
						 printf("kEventWindowDrawContent\n");
						 */
						result = noErr;
						HD_Force_Refresh (ogldata->dc);
					}
						break;
					case kEventWindowClose: 
					{
						/* called when window is being closed (close box)
						 printf("kEventWindowClose\n");
						 */
						char event_string[1024];
						
						result = noErr;
						
						if (dc->options.special_events && !dc->options.disable_input) {
							
							HI_Queue_Special_Event (dc->thread_data, "OpenGL:DeleteWindow",
								HI_Build_Special_Event_String(event_string, "OPENGL", dc->actor_segment, 
									(POINTER_SIZED_INT) ogldata->window, -1));
						}
						
						HideWindow(ogldata->window);
						
						HI_Queue_Actor_Shutdown(dc->actor, false);
						dc->options.disable_input = true;
						
					}
						break;
					case kEventWindowShown: 
						/* called on initial show (not on un-minimize)
						 printf("kEventWindowShown\n");
						 */
						result = noErr;
						if (ogldata->window == FrontWindow()) {
							SetUserFocusWindow(ogldata->window);
						}
						
						break;
					case kEventWindowBoundsChanging:
					{
						Rect original_rect, current_rect, previous_rect;
						
						result = noErr;
						
						GetEventParameter(event, kEventParamOriginalBounds, typeQDRectangle, NULL, sizeof(Rect), NULL, &original_rect);
						GetEventParameter(event, kEventParamPreviousBounds, typeQDRectangle, NULL, sizeof(Rect), NULL, &previous_rect);
						GetEventParameter(event, kEventParamCurrentBounds, typeQDRectangle, NULL, sizeof(Rect), NULL, &current_rect);
						
						/*
						 printf("o: %d %d %d %d\n", original_rect.left, original_rect.right, original_rect.bottom, original_rect.top);
						 printf("p: %d %d %d %d\n", previous_rect.left, previous_rect.right, previous_rect.bottom, previous_rect.top);
						 printf("c: %d %d %d %d\n", current_rect.left, current_rect.right, current_rect.bottom, current_rect.top);
						 */
						
						if (!dc->options.subscreen_moving) {
							SetEventParameter(event, kEventParamCurrentBounds, typeQDRectangle, sizeof(Rect), &original_rect);
						}
						
						if (!dc->options.subscreen_stretching) {
							
							Rect ar;
							
							int ow,oh;
							int cw,ch;
							
							int dw,dh;
							int nw,nh;
							int fw,fh;
							
							ow = original_rect.right-original_rect.left;
							oh = original_rect.bottom-original_rect.top;
							
							cw = current_rect.right-current_rect.left;
							ch = current_rect.bottom-current_rect.top;
							
							if (ow == cw && oh == ch) break;
							
							if (abs(ow-cw) > abs(oh-ch)) {
								dw = ow-cw;
								dh = (int)((float)dw*(1.0f/ogldata->window_aspect));  
							}else{
								dh = oh-ch;
								dw = (int)((float)dh*ogldata->window_aspect); 
							}
							
							nw=ow-dw;
							nh=oh-dh;
							
							current_rect.right=current_rect.left+nw;
							current_rect.bottom=current_rect.top+nh;
							
							GetAvailableWindowPositioningBounds(ogldata->info_device, &ar);
							
							/*
							 if (ar.left>current_rect.left) current_rect.left=ar.left;
							 */
							if (current_rect.right>ar.right) current_rect.right=ar.right;
							
							fw=current_rect.right-current_rect.left;
							
							if (fw != nw) {
								nw = fw;
								nh = (int)((float)nw*(1.0f/ogldata->window_aspect));
								current_rect.bottom=current_rect.top+nh;
							}
							
							if (ar.top>current_rect.top) current_rect.top=ar.top;
							if (current_rect.bottom>ar.bottom) current_rect.bottom=ar.bottom;
							
							fh=current_rect.bottom-current_rect.top;
							
							if (fh != nh) {
								dh = fh;
								dw = (int)((float)dh*ogldata->window_aspect); 
								current_rect.right = current_rect.left+dw;
							}
							
							SetEventParameter(event, kEventParamCurrentBounds, typeQDRectangle, sizeof(Rect), &current_rect);
						}
						
					}
						break;
					case kEventWindowBoundsChanged: 
					{
						Rect rect;
						result = noErr;
						ogldata->pending_resize = true;
						
						GetWindowBounds (ogldata->window, kWindowContentRgn, &rect);
						
						if ((rect.right-rect.left != ogldata->window_width) || 
							(rect.bottom-rect.top != ogldata->window_height)) {
							HD_Force_Refresh (ogldata->dc);
						}
					}
						
						break;
					case kEventWindowZoomed: 
						/* called when user clicks on zoom button
						 printf("kEventWindowZoomed\n");
						 */
						break;
				}
				break;
				
			default: 
				/*
				 printf("unknown class\n");
				 */
				break;
		}
		
	}/*FIND DC*/
	
	return result;
}


/*stuff for getting extention pointers*/
static unsigned int ogl_bundle_users = 0;
static CFBundleRef ogl_bundle_ref = 0;

local CFBundleRef LoadSystemFrameWorkBundle(const char *frameworkName)
{
	FSRef folderRef, dstRef;
	CFBundleRef bRef = NULL;
	
	if (FSFindFolder(kSystemDomain, kFrameworksFolderType, false, &folderRef) == noErr) {
		
		HFSUniStr255 hfs;
		CFStringRef cfStr;
		
		/* Convert C string to hfs [unicode] data struct */
		cfStr = CFStringCreateWithCString(CFAllocatorGetDefault(), frameworkName, kCFStringEncodingMacRoman);
		hfs.length = CFStringGetLength(cfStr);
		CFStringGetCharacters(cfStr, CFRangeMake(0,hfs.length), hfs.unicode);
		CFRelease(cfStr);
		
		if (FSMakeFSRefUnicode(&folderRef, hfs.length, hfs.unicode, CFStringGetSystemEncoding(), &dstRef) == noErr) {
			
			CFURLRef urlRef = CFURLCreateFromFSRef(CFAllocatorGetDefault(), &dstRef);
			
			if (urlRef) {
				bRef=CFBundleCreate(CFAllocatorGetDefault(), urlRef);
				CFRelease(urlRef);
			}
		}
	}  
	/* remember to relase this when you are done!! */
	return bRef;	  
}

local void * GetFunctionPointerFromBundle(const char *name, CFBundleRef theBundle)
{
	void *function = 0;
	
	if (theBundle) {
		CFStringRef strRef = CFStringCreateWithCString(CFAllocatorGetDefault(), name, kCFStringEncodingMacRoman);
		function = CFBundleGetFunctionPointerForName(theBundle, strRef);
		CFRelease(strRef);
	}
	return function;
}

local void * MyAGLGetProcAddress(const char *function_name)
{
	if (!ogl_bundle_ref) {
		return 0;
	}
	
	return GetFunctionPointerFromBundle(function_name, ogl_bundle_ref);
}


/*
 * ACTION
 */
bool start_device (Display_Context alter * dc) 
{
	HOGLData *ogldata;	
	ZALLOC (ogldata, HOGLData);
	
	/* dc->data may have the quartz driver's data on it */
	if (!dc->data) 
		dc->data = (void alter *) ogldata;
	dc->data2 = (void alter *) ogldata;
	ogldata->dc = dc;	
	
	ogldata->ShaderHash = new H3DShaderHASH(ogldata);
	ogldata->at = Action_Table::Create(dc->memory_pool);
	
	if (!dc->options.use_window_ID) {
				
		ogldata->dc_type = DCT_OUR_WINDOW;
		ogldata->info_device = GetMainDevice();			
		
		if (!app_handlerUPP) {
			
			ProcessSerialNumber psn;
			if (GetCurrentProcess(&psn) != noErr) return false;
			SetFrontProcess(&psn);
			
			app_handlerUPP = NewEventHandlerUPP(our_app_event_handler);
			InstallEventHandler(GetApplicationEventTarget(), app_handlerUPP,
								GetEventTypeCount(app_events), app_events, 
								(void*)ogldata, &app_handler_ref); 
			
		}
		
	} 
	
    else if (dc->options.window_id_type == Window_ID_IMAGE_KEY || BIT (dc->options.debug, Debug_USE_WINDOW_IS_IMAGE)) {
        Image alter              *image;
		bool					supported_format;
		
        image = (Image alter *)KEY_TO_POINTER (dc->thread_data, dc->options.use_window_ID);
        if (image == null) {
            HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
					  "An invalid key was passed to the OpenGL driver with USE_WINDOW_IS_IMAGE set."); 
            return false;
        }
		supported_format = (image->format == Image_RGBA32 ||
							image->format == Image_RGBAS32 ||
							image->format == Image_ARGB32 ||
							image->format == Image_RGB24);
        if (!supported_format || image->block == 0) {
            HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
					  "OpenGL output image unsupported format."); 
            return false;
        }
        if (image->height < 1 || image->width < 1) {
            HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
					  "OpenGL output images must be at least 1x1."); 
            return false;
        }
		
        ogldata->output_image = image;
		ogldata->window_width = ogldata->output_image->width;
		ogldata->window_height = ogldata->output_image->height;
        UTILE (ogldata->output_image);
        ogldata->dc_type = DCT_PBUFFER_IMAGE; /* on osx, pbuffer failure is fatal */
    }
	else {
		ogldata->dc_type = DCT_THEIR_WINDOW;
		ogldata->window = (WindowRef) dc->options.use_window_ID;
		((Display_Context alter *) dc)->current.window_ID = (POINTER_SIZED_INT) ogldata->window;
		
		ogldata->use_clip_override = (int*)dc->options.use_clip_override;
		
		if (!dc->options.disable_all_input &&
			!BIT (dc->options.debug, Debug_NO_WINDOWS_HOOK)) {
			
		}
	}
	
	ogl_bundle_users++;
	if (ogl_bundle_users==1) {
		ogl_bundle_ref = LoadSystemFrameWorkBundle("OpenGL.framework");
	}
	
	return true;
}


/*
 * ACTION
 */
void stop_device (Display_Context alter * dc) 
{
	HOGLData alter *ogldata = OGLD (dc);
	
	/* release any Informational DC's we created */
	switch (ogldata->dc_type) {
		case DCT_PBUFFER_IMAGE:
			
			if (ogldata->output_image) {
#if 0	// HOGLData has no output_image_scratch field so this code can't be used
			
				if (ogldata->output_image_scratch) {
					int w = ogldata->output_image->width;
					int h = ogldata->output_image->height;
					FREE_ARRAY(ogldata->output_image_scratch, w*h, RGBAS32);
				}
#endif
				INUTILE (ogldata->output_image); /* currently only relevant to pbuffers */
			}
			break;
			
		case DCT_OUR_WINDOW:
		case DCT_THEIR_WINDOW:
			/* nothing to do */
			break;
	}
	unset_ogl (dc);
	ogldata->dc_type = DCT_UNDEFINED;
	
	if (ogldata->card_entry)
		HI_Free_Driver_Config(ogldata->card_entry);
	
	FREE (ogldata, HOGLData);
	if (dc->data == dc->data2)
		dc->data = null;
	dc->data2 = null;
	
	ogl_bundle_users--;
	
	if (ogl_bundle_users==0) {
		if (ogl_bundle_ref) {
			CFRelease(ogl_bundle_ref);
			ogl_bundle_ref=0;
		}
	}

}


/*
 * ACTION
 */
bool request_keyboard (Display_Context const * dc,
				  int alter * button, int alter * status) 
{
	HOGLData alter *ogldata = OGLD (dc);
	
	if (ogldata != null) {
		check_events (ogldata);
		/* This next line is QUITE necessary to refresh the pointer */
		ogldata = OGLD (dc);
		
		/*
		 * check_events will always have reported any keystrokes
		 * to Hoops via Queue_Keyboard_Event.  Since Hoops doesn't
		 * need to know the "state" of the keyboard, this function
		 * can safely return false.
		 */
	}
	return false;
	
}


/*
 * HELPER
 */
local void
check_events (HOGLData alter * ogldata) 
{
	EventTargetRef target;
	EventRef event;
	
	ogldata->mouse_was_queued = false;
	
	target = GetEventDispatcherTarget();
	
	while (!ReceiveNextEvent(0, 0, kEventDurationNoWait, true, &event)) {
		SendEventToEventTarget(event, target);
		ReleaseEvent(event);
	}
}

/*
 * ACTION
 */
bool request_location (Display_Context const * dc,
				  int alter * button,
				  int alter * x, int alter * y) 
{
	HOGLData alter *ogldata = OGLD (dc);
	
	if (ogldata != null) {
		check_events (ogldata);
		/* This next line is QUITE necessary to refresh the pointer */
		ogldata = OGLD (dc);
		/*
		 * This function must always report a mouse "state",
		 * so if check_events did not report an activity via
		 * Queue_Pixel_Location_Event, we must report one here.
		 * We will just re-report the last mouse state that
		 * we saw.
		 */
		if (ogldata == null || ogldata->mouse_was_queued)
			return false;
		else {
			*button = ogldata->mouse_buttons;
			*x = ogldata->mouse_x;
			*y = ogldata->mouse_y;
			return true;
		}
	}
	
	return false;
}

local POINTER_SIZED_INT
create_standalone_window(Display_Context * dc)
{
	HOGLData alter *ogldata = OGLD (dc);
	OSStatus status;
	
	EventTypeSpec stand_alone_event_list[] = { 
		{ kEventClassWindow, kEventWindowCollapsing },
		{ kEventClassWindow, kEventWindowCollapsed },
		{ kEventClassWindow, kEventWindowShown },
		{ kEventClassWindow, kEventWindowActivated },
		{ kEventClassWindow, kEventWindowClose },
		{ kEventClassWindow, kEventWindowDrawContent },
		{ kEventClassWindow, kEventWindowBoundsChanging },
		{ kEventClassWindow, kEventWindowBoundsChanged },
		{ kEventClassWindow, kEventWindowZoomed },
		
		{ kEventClassMouse, kEventMouseDown },
		{ kEventClassMouse, kEventMouseUp },
		{ kEventClassMouse, kEventMouseDragged },
		
		{ kEventClassKeyboard, kEventRawKeyDown } };
	
	char title[4096];
	CFStringRef cfstr_title=0;
	WindowAttributes attribs;
	WindowClass window_class;
	Rect rect;
	
	HI_Copy_Name_To_Chars (&dc->options.title, title);
	title[79] = '\0';
	
	attribs = kWindowStandardDocumentAttributes | kWindowStandardHandlerAttribute;
	
	if (!dc->options.subscreen_resizing) {
		attribs &= ~kWindowResizableAttribute;
	}
	
	window_class = kDocumentWindowClass;
	
	rect.left = dc->outer_extent.left;
	rect.right = dc->outer_extent.right;
	rect.top = ogldata->y_screen_fudge - dc->outer_extent.top;
	rect.bottom = ogldata->y_screen_fudge - dc->outer_extent.bottom;
	
	ogldata->window_aspect = (float)(rect.right-rect.left)/(float)(rect.bottom-rect.top);
	
	status = CreateNewWindow(window_class, attribs, &rect, &ogldata->window);
	
	if (status || !ogldata->window) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_CREATE_WINDOW, "Unable to Create a Window");
		HD_Kill_Driver (dc);
	}
	
	cfstr_title = CFStringCreateWithCString (0, title, kCFStringEncodingASCII);
	
	SetWindowTitleWithCFString (ogldata->window, cfstr_title);
	
	ogldata->window_EventHandlerUPP = NewEventHandlerUPP(our_window_handler);
	
	InstallWindowEventHandler(
							  ogldata->window, 
							  ogldata->window_EventHandlerUPP, 
							  GetEventTypeCount (stand_alone_event_list), 
							  stand_alone_event_list, 
							  (void*)ogldata, 
							  &ogldata->event_handler_ref); 
	
	ShowWindow (ogldata->window);
	
	return (POINTER_SIZED_INT)(POINTER_SIZED_INT) ogldata->window;
}

/*
 * ACTION
 */
POINTER_SIZED_INT get_outer_window (Display_Context const * const_dc) 
{	
	Display_Context alter * dc = (Display_Context alter *) const_dc;
	HOGLData alter *ogldata = OGLD (dc);
	POINTER_SIZED_INT retval = 0;	
	
	switch (ogldata->dc_type) {
			
		case DCT_PBUFFER_IMAGE:
		{
			/* return value of 0 from aglCreatePBuffer means failure */
 			if (aglCreatePBuffer (ogldata->output_image->width, 
								  ogldata->output_image->height, 
								  GL_TEXTURE_RECTANGLE_EXT, GL_RGBA, 
								  0, &(ogldata->pbuffer)))
				retval = (POINTER_SIZED_INT)(POINTER_SIZED_INT)ogldata->pbuffer;
		}
			break;
			
		case DCT_OUR_WINDOW:
			retval = create_standalone_window(dc);
			break;
			
		case DCT_THEIR_WINDOW:
			retval = (POINTER_SIZED_INT)(POINTER_SIZED_INT) ogldata->window;
			break;
			
		case DCT_IMAGE:
		default:
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
					  "internal error: unsupported display context type in ogl_agl:get outer window");
			HD_Kill_Driver (dc);
	}	
	
	
	choose_pixel_format(dc);
	
	init_ogldata((Display_Context alter *) dc);
	
	ogldata->prev_GrafPtr = 0;
	if (ogldata->dc_type == DCT_PBUFFER_IMAGE) {
		int vs = 0;
		if (!aglSetPBuffer(ogldata->curr_AGLContext, ogldata->pbuffer, 0, 0, vs)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
					  "Unable to set OpenGL pbuffer rendering context in ogl_agl:get outer window");
			HD_Kill_Driver (dc);
		}
	}
	else {
		if (BIT (ogldata->dc->options.debug, Debug_OSX_UNDERLAY) && 
			ogldata->dc_type == DCT_THEIR_WINDOW) {
			GLint order = -1;
			aglSetInteger(ogldata->curr_AGLContext, AGL_SURFACE_ORDER, &order);
			SetWindowAlpha(ogldata->window, 0.999f);
		}
		
		GetPort (&ogldata->prev_GrafPtr);
		SetPort ((GrafPtr) GetWindowPort (ogldata->window));
		
		if (!aglSetDrawable(ogldata->curr_AGLContext, GetWindowPort(ogldata->window))) {
			//if (!aglSetWindowRef(ogldata->curr_AGLContext, ogldata->window)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
					  "Unable to set drawable");
			HD_Kill_Driver (dc);
		}
		
		if (!aglSetCurrentContext(ogldata->curr_AGLContext)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
					  "Unable to set Current OpenGL Rendering Context");
			HD_Kill_Driver (dc);
		}
	}
	
	ogldata->glewcontext = new GLEWContext();	
	glewInit();
	
	identify_renderer(dc);
	
	ogldata->double_buffering = dc->options.double_buffering;
	
	/* for now, we haven't mapped over the current pixel format request parameters
	 to a QGLFormat, and setting this accumulation_bits = 16 doesn't work with the
	 default QGLContext */
	if (BIT(dc->options.debug, Debug_USE_QGL_CONTEXT))
		ogldata->accumulation_bits = 0;
	
	setup_ogl((Display_Context alter *) dc);
	
	/* disable vertical synch -- should this perhaps be configurable? */
	{
		GLint swap=0;
		aglSetInteger (ogldata->curr_AGLContext, AGL_SWAP_INTERVAL, &swap);
	}	
	
	return retval;	
}

/*
 * ACTION
 */
void free_outer_window (Display_Context const * dc)
{
	HOGLData alter *ogldata = OGLD (dc);
	
	aglSetCurrentContext(ogldata->curr_AGLContext);
	
	/* clean up opengl stuff*/
	invalidate_device_objects((Display_Context *)dc);
	ogldata->Cleanup();

	common_free_outer_window(dc);
	
	aglSetCurrentContext(NULL);
	unset_ogl (dc);
	
	if (ogldata->dc_type == DCT_OUR_WINDOW) {
		DisposeWindow (ogldata->window);
		ogldata->window = null;
		if (ogldata->window_EventHandlerUPP) {
			DisposeEventHandlerUPP(ogldata->window_EventHandlerUPP);
			ogldata->window_EventHandlerUPP = null;
		}
	}
	else if (ogldata->dc_type == DCT_PBUFFER_IMAGE) {
		aglDestroyPBuffer (ogldata->pbuffer);
		ogldata->pbuffer = null;
	}
}



void retitle_outer_window (
						   Display_Context const	*dc) 
{
	// I get a link error if I remove this function. ogl_agl doesn't have it though, so why do I need it here?
}

/*
 * ACTION
 */
void resize_outer_window (Display_Context const * dc) 
{
	HOGLData alter *ogldata = OGLD (dc);
	ogldata->tr_incarnation = INVALID_INCARNATION;
	ogldata->geom_incarnation = INVALID_INCARNATION;
	ogldata->light_incarnation = INVALID_INCARNATION;
	ogldata->cutting_plane_incarnation = INVALID_INCARNATION;
	
	if (ogldata->dc_type == DCT_THEIR_WINDOW) return;
	
	MoveWindow(ogldata->window, dc->outer_extent.left, dc->outer_extent.top, false);
	SizeWindow(ogldata->window, 
			   dc->outer_extent.right - dc->outer_extent.left, 
			   dc->outer_extent.bottom - dc->outer_extent.top, 
			   true);	
}



/*
 * ACTION
 */
local void
get_actions (Action_Table alter & at) {

	get_common_actions (at);

	at->measure_char = measure_char;
	//at->find_one_font = find_one_font;
	//at->find_basic_font = find_basic_font;
	at->find_all_fonts = find_all_fonts;
	at->load_font = load_font;
	at->unload_font = unload_font;
	//at->name_font = name_font;
	//at->make_font_stencil = make_font_stencil;
	//at>will_use_stencil = will_use_stencil;

}/* end function get_actions */


/*
 * REAL DRIVER
 */
extern "C" bool HC_CDECL HD_OpenGL2_Driver (
	Thread_Specific_Data *	thread_data, 
	Actor alter *			actor, 
	int						request, 
	void *					request_info) 
{
	UNREFERENCED(request_info);
	return HD_Connect_Standard_Driver (thread_data, actor, request, get_actions);
}

#endif 
#endif




