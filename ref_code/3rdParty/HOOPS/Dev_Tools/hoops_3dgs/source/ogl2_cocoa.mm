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
 * $Id: ogl2_cocoa.mm,v 1.3 2010-06-29 00:02:10 evan Exp $
 */

#define id hid
#include "hoops.h"
#include "hd_proto.h"
#undef id

#ifdef OSX_SYSTEM
#ifndef COCOA_OPENGL2_DRIVER

/*
 * STUB DRIVER
 */
extern "C" bool HC_CDECL HD_Cocoa_OpenGL2_Driver (Actor alter * actor, int request, void * request_info) {
	UNREFERENCED(request_info);
	return HD_No_Driver (actor, request, "cocoa_opengl2");
}

#else /* we're on OSX and compiling cocoa opengl2 driver */

#define COCOA_OGL2_DRIVER

#define DECLARE_OGL_PROTOTYPES
#define id hid
#include "ogl2.cpp"
#undef id

#include <AppKit/AppKit.h>
#include <Cocoa/Cocoa.h>
#include <Foundation/Foundation.h>

struct CocoaOGL2Data : public HOGLData
{
	NSOpenGLView *view;		
	NSWindow *window;
	float window_aspect;
	
	NSOpenGLPixelBuffer *pbuffer;
	CGDirectDisplayID display_id;
	
	NSOpenGLContext *curr_NSOpenGLContext;
	NSOpenGLContext *prev_NSOpenGLContext;
};

#define COGLD(dc) ((CocoaOGL2Data alter *)((dc)->data2))
#define COGLNRD(nr) (COGLD((nr)->display_context))

// cococa_common will undefine the two following symbosl when it's done with them
#define VIEW_NAME HOGL2View
#define OGLDATA CocoaOGL2Data
#include "cocoa_common.mm"

local void
choose_pixel_format (Display_Context alter * dc) {
	
} 

/*
 * HELPER
 */
local void
identify_renderer (Display_Context alter * dc) {
	
}


void handle_size_change(Display_Context alter * dc) {
	
}

local void
unset_ogl (Display_Context const * dc) {
	
}

/*
 * ACTION
 */
void finish_picture (Net_Rendition const &  nr,
					 bool swap_buffers) {
	
	Display_Context const *dc = nr->display_context;
	CocoaOGL2Data alter *ogldata = COGLNRD (nr);
	
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
			[ogldata->curr_NSOpenGLContext flushBuffer];
		}
	}
	
	FREE_VB_TEMP(ogldata);
	FREE_IB_TEMP(ogldata);
	
	bless_display_lists (ogldata);
	
}

/*
 * ACTION
 */
void init_picture (Net_Rendition const &  nr) {
	
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
	
	CocoaOGL2Data alter *ogldata = COGLD (dc);
	
	if (!BIT(dc->flags, DCF_outer_window_exists))
		return;
	
	if (ogldata->dc_type == DCT_OUR_WINDOW)
		if (!dc->options.disable_all_input &&
			!BIT (dc->options.debug, Debug_NO_WINDOWS_HOOK))
			check_events (ogldata);
	
	[NSOpenGLContext clearCurrentContext];
	
	if (ogldata->prev_NSOpenGLContext) {
		[ogldata->prev_NSOpenGLContext makeCurrentContext];
	}
	
	ogldata->prev_NSOpenGLContext = 0;		
}


/*
 * ACTION
 */
void init_update (Display_Context const * dc) {
	
	CocoaOGL2Data alter *ogldata = COGLD(dc);
	
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
		ogldata = COGLD (dc);
		
		if (!ogldata) 
			return;
	}
	
	invalidate_cache (ogldata);
	
	if (ogldata->dc_type == DCT_PBUFFER_IMAGE) {	
		
		[ogldata->curr_NSOpenGLContext setPixelBuffer:ogldata->pbuffer
										  cubeMapFace:0
										  mipMapLevel:0
								 currentVirtualScreen:0];
	}
	else {		
		
		if (!ogldata->view)
			return;					
		
		Rect rect = get_window_bounds<CocoaOGL2Data>(dc);		
		
		if ( (rect.right-rect.left != ogldata->window_width) || 
			(rect.bottom-rect.top != ogldata->window_height) ) {
			
			ogldata->window_width = rect.right-rect.left;
			ogldata->window_height = rect.bottom-rect.top;
			
			ogldata->yfudge = (rect.bottom-rect.top);
			
#if 0
			printf("resized %d %d %d %d %d %d\n",
				   rect.left, rect.top, rect.right, rect.bottom,
				   rect.right-rect.left, rect.bottom-rect.top);
#endif						
			
			[ogldata->curr_NSOpenGLContext update];
			
			HD_Resize_Subscreen (dc, true,
								 0, (rect.right-rect.left)-1, 
								 0, (rect.bottom-rect.top)-1);			
			
		}
	}
	
	ogldata->prev_NSOpenGLContext = [NSOpenGLContext currentContext];
	[ogldata->curr_NSOpenGLContext makeCurrentContext];	
	
}

/*****************************************************************************
 *****************************************************************************
 FONT_ACTIONS
 *****************************************************************************
 *****************************************************************************/



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
						void ** per_kar_data) {	
	
	return true;
	
	
}

/*
 * ACTION
 */
local void * 
load_font (Display_Context const * dc,
		   char const * name,
		   Font_Instance alter * instance) {
	
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
			 Font_Instance alter *instance) {
	
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
	
	
	
}


/*forward*/
local void get_actions (Action_Table alter &);

/*
 * ACTION
 */
void get_physical_info (Display_Context alter * dc) {
	
	CocoaOGL2Data alter *ogldata = COGLD(dc);
	
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
		
		dc->physical.number_of_pixels.x = CGDisplayPixelsWide(ogldata->display_id);
		dc->physical.number_of_pixels.y = CGDisplayPixelsHigh(ogldata->display_id);
		
		CGSize size = CGDisplayScreenSize(ogldata->display_id);
		
		dc->physical.size.x = size.width / 10;
		dc->physical.size.y = size.height / 10;		
		
	}
	
	if (dc->options.physical_size.x != -1) {
		dc->physical.size.x = dc->options.physical_size.x;
		dc->physical.size.y = dc->options.physical_size.y;
	}
	
	ogldata->yfudge = ogldata->y_screen_fudge = dc->physical.number_of_pixels.y - 1;
	
	/* put in reasonable numbers here...just in case the test window fails */
	dc->physical.nominal_color_resolution = 256;
	dc->physical.color_system = DIRECT_RGB;
	dc->physical.driver_type = "COCOA_OGL2";
	dc->physical.driver_version = "$Revision: 1.3 $";
	dc->physical.display_type = "frame buffer";
	dc->physical.locater_type = "mouse";
	
	/* extra capabilities set to false until we see a valid context */
	dc->physical.flags &= ~DCPF_has_gouraud_shading;
	dc->physical.flags &= ~DCPF_has_gouraud_lighting;
	
	dc->physical.flags &= ~DCPF_needs_gamma_correction;
	
	ogldata->caps.max_primitive_count = MAX_INT;
	ogldata->caps.shader_model = SHADER_MODEL_3;
	dc->physical.max_view_dependent_shadow_maps = 4;	
	
	ogldata->can_stencil = false;
	
	/*
	 * WARNING:	 because there is alot of information that we do NOT
	 * know until an OpenGL-visual-equipped window is mapped, we do
	 * an update physical info in setup ogl
	 * This fills in various information (especially about the number
	 * of planes available since it is cut in half when you do double
	 * buffering) that should logically be done here... do an
	 * update_physical_info here but remember that this info may change...
	 */
	
	if (ogldata->curr_NSOpenGLContext)	
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

/*
 * ACTION
 */
bool start_device (Display_Context alter * dc) {	
	
	CocoaOGL2Data *ogldata;
	ZALLOC (ogldata, CocoaOGL2Data);
	
	/* dc->data may have the quartz driver's data on it */
	//if (!dc->data) 
	//	dc->data = (void alter *) ogldata;
	
	dc->data2 = (void alter *) ogldata;
	ogldata->dc = dc;	
	ogldata->display_id = CGMainDisplayID();
	
	ogldata->ShaderHash = new H3DShaderHASH(ogldata);
	ogldata->at = Action_Table::Create(dc->memory_pool);
	
	if (!dc->options.use_window_ID) {
		
		ogldata->dc_type = DCT_OUR_WINDOW;	
		
	} 
    else if (dc->options.window_id_type == Window_ID_IMAGE_KEY || BIT (dc->options.debug, Debug_USE_WINDOW_IS_IMAGE)) {
        Image alter              *image;
		bool					supported_format;
		
        image = (Image alter *)KEY_TO_POINTER (dc->thread_data, dc->options.use_window_ID);
        if (image == null) {
            HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
					  "An invalid key was passed to the OpenGL2 driver with USE_WINDOW_IS_IMAGE set."); 
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
        ogldata->dc_type = DCT_PBUFFER_IMAGE; 
    }
	else {
		
		ogldata->dc_type = DCT_THEIR_WINDOW;
		
		ogldata->view = (NSOpenGLView*)dc->options.use_window_ID;			
		dc->current.window_ID = (POINTER_SIZED_INT)ogldata->view;		
		
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
void stop_device (Display_Context alter * dc) {
	
}


/*
 * ACTION
 */
bool request_keyboard (Display_Context const * dc,
					   int alter * button, int alter * status) {
	
	return false;
	
}


/*
 * HELPER
 */
local void
check_events (HOGLData alter * ogldata) {
			
}

/*
 * ACTION
 */
bool request_location (Display_Context const * dc,
					   int alter * button,
					   int alter * x, int alter * y) 
{
		
	return false;
}

/*
 * ACTION
 */
POINTER_SIZED_INT get_outer_window (Display_Context const * const_dc) 
{	
	
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	Display_Context alter * dc = (Display_Context alter *) const_dc;
	POINTER_SIZED_INT retval = 0L;
	CocoaOGL2Data alter *ogldata = COGLD(dc);
	
	invalidate_cache (ogldata);	
	
	switch (ogldata->dc_type) {
			
		case DCT_PBUFFER_IMAGE:
			retval = create_pbuffer<CocoaOGL2Data>(dc);		
			break;
			
		case DCT_OUR_WINDOW:
			retval = create_standalone_window<CocoaOGL2Data,HOGL2View>(dc);
			break;
			
		case DCT_THEIR_WINDOW:
			retval = (POINTER_SIZED_INT)ogldata->view;
			break;
			
		case DCT_IMAGE:
		default:
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
					  "internal error: unsupported display context type in ogl2_cocoa:get outer window");
			HD_Kill_Driver (dc);
	}	
	
	choose_pixel_format<CocoaOGL2Data>(dc);	
	
	{
		GLint anti_alias_samples = 0;
		[[ogldata->view pixelFormat] getValues : &anti_alias_samples forAttribute : NSOpenGLPFASamples forVirtualScreen : 0];
		ogldata->can_anti_alias = (anti_alias_samples != 0);	
	}
	
	if (ogldata->dc_type == DCT_PBUFFER_IMAGE) {		
		
		[ogldata->curr_NSOpenGLContext setPixelBuffer:ogldata->pbuffer
										  cubeMapFace:0
										  mipMapLevel:0
								 currentVirtualScreen:0];		
	}	
	else if (ogldata->dc_type == DCT_OUR_WINDOW) {	
		
		ProcessSerialNumber psn = {0, kCurrentProcess};
		TransformProcessType(&psn, kProcessTransformToForegroundApplication);        
        [ogldata->window makeKeyAndOrderFront:NSApp]; // show the window, must happen *after* choose_pixel_format     
        
	}
	else {
		
	}
	
	// very important to make context current before update_physical_info happens in setup_ogl below.
	[ogldata->curr_NSOpenGLContext makeCurrentContext];
	
	init_ogldata(dc);	
	identify_renderer(dc);
	
	ogldata->glewcontext = new GLEWContext();	
	glewInit();
	
	ogldata->double_buffering = dc->options.double_buffering;
	
	/* for now, we haven't mapped over the current pixel format request parameters
	 to a QGLFormat, and setting this accumulation_bits = 16 doesn't work with the
	 default QGLContext */
	if (BIT(dc->options.debug, Debug_USE_QGL_CONTEXT))
		ogldata->accumulation_bits = 0;
	
	setup_ogl((Display_Context alter *) dc);

	
	/* agl driver disables vsync here */
	
	[pool drain];
	
	return retval;		
	
}

/*
 * ACTION
 */
void free_outer_window (Display_Context const * dc)
{
	
}



void retitle_outer_window (
						   Display_Context const	*dc) 
{
	
}

/*
 * ACTION
 */
void resize_outer_window (Display_Context const * dc) 
{
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
extern "C" bool HC_CDECL HD_Cocoa_OpenGL2_Driver (
											Actor alter * actor, 
											int request, 
											void * request_info) 
{
	
	return HD_Connect_Standard_Driver (actor, request, get_actions);
}

#endif 
#endif




