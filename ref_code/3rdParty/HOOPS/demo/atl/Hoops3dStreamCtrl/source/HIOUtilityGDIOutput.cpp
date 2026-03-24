#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HIOUtilityGDIOutput.h"
#include "HBaseView.h"
#include "HBaseOperator.h"
#include "HUtilityLocaleString.h"
#include "HMarkupManager.h"
#include <math.h>
#include <windows.h>
 

#ifndef _UNICODE
#define CtU(x,y)     (strcpy(y, x), y)
#define UtC(x,y)     (strcpy(y, x), y)
#else
#define CtU(x,y)     (mbstowcs(y, x, strlen(x)), y)
#define UtC(x,y)     (wcstombs(y, x, wcslen(x)), y)
#endif



/*!
  This is the function which should be used for all GDI Print and Copy to Clipboard work

  \param FileName A character pointer denoting the name of the file to be read in
  \param key This is typically unused 
  \param options You pass in the HBaseView pointer, the camera setting, the device context and the hWnd
	within this structure
  \return result of operation
*/

HFileOutputResult HIOUtilityGDIOutput::FileOutputByKey(const char *FileName, HC_KEY key, HOutputHandlerOptions * options) 
{
	if(!FileName) 
		return OutputBadFileName;
	if(!key) 
		return OutputFail;
	if (!options)
		return OutputFail;
	
	
	HBaseView* pHView	 = options->m_pHBaseView;
	GDIExportInformation* pinfo = (GDIExportInformation *)options->m_pExtendedData;
	bool rasterOutput	 = pinfo->rasterOutput;
	bool isActivex		 = false;
	bool isAxisTriad	 = false;
	HDC hDC, hAttribDC, hMfDC;
	char sTemp[MVO_BUFFER_SIZE], driver[MVO_SEGMENT_PATHNAME_BUFFER];
	
	// set the device contexts and driver string depending on whether
	// printing or copy to clipboard
	if (pinfo->clipBoard)
	{
		sprintf(driver, "/driver/msw/clipboard");
		
		char ext[MVO_BUFFER_SIZE];
		HUtility::FindFileNameExtension(FileName, ext);
		if (streq(ext, "emf"))
			hMfDC = CreateEnhMetaFile(pinfo->deviceContext, H_TEXT(FileName), NULL, NULL);
		else
			hMfDC = CreateEnhMetaFile(pinfo->deviceContext, NULL, NULL, NULL);

		
		if (isActivex)
			hDC = pinfo->deviceContext;
		else
			hDC = hMfDC;

		hAttribDC = hDC;
	}
	else
	{
		sprintf(driver, "/driver/msw/printer");
		hDC = pinfo->deviceContext;
		hAttribDC = pinfo->attribDC;
	}
	
	// only include axis triad if printing
	if (!(pinfo->clipBoard) && pHView->GetAxisMode() != AxisOff)
		isAxisTriad = true;
	
	
	HC_Open_Segment (driver);

		// first let's do the generic print driver set up
		sprintf (sTemp, "use window ID = %s%p", H_EXTRA_POINTER_FORMAT, pinfo->windowID);
		HC_Set_Driver_Options (sTemp);
	
		long debug_flags = 0;
		if (pinfo->clipBoard)
		{
			// GB: We should be allowed to this but it causes a bug when sfb ctc
			// HC_Set_Window_Frame ("off");
			sprintf (sTemp, "use window ID2 = %s%p", H_EXTRA_POINTER_FORMAT, hDC);
			
			HC_Set_Driver_Options (sTemp);
			
			debug_flags |= DEBUG_CLIPBOARD_MODE;
			debug_flags |= DEBUG_FORCE_FULL_COLOR;
			debug_flags |= 0x00000020;
			if (rasterOutput)
				debug_flags |= DEBUG_SFB_COPY_TO_CLIPBOARD;
			
		}
		else{

			HC_Set_Window_Frame ("off");
			
			sprintf (sTemp, "use window ID2 = %s%p", H_EXTRA_POINTER_FORMAT, pinfo->attribDC);
			HC_Set_Driver_Options (sTemp);
			
#if defined(_M_IA64) || defined(_M_AMD64)
			sprintf (sTemp, "output format = %I64u", hDC);
#else
			sprintf (sTemp, "output format = %u", hDC);
#endif
			HC_Set_Driver_Options (sTemp);
			
			debug_flags |= DEBUG_PRINTING_MODE;
			debug_flags |= DEBUG_PRINT_NOT_FRAMEBUFFER_MODE;
			debug_flags |= DEBUG_PRINT_NOT_RASTER_REDUCTION;
			debug_flags |= 0x00000020;
		}

		sprintf (sTemp, "debug = %u", debug_flags);
		HC_Set_Driver_Options (sTemp);

		sprintf (sTemp, "special events, disable input=all, subscreen stretching, isolated");
		HC_Set_Driver_Options ( sTemp);


		float window_ar;
		HC_Open_Segment_By_Key(pHView->GetViewKey());
			HC_Show_Device_Info(".", "window aspect ratio", sTemp);
			sscanf(sTemp, "%f", &window_ar);
		HC_Close_Segment();
	
	
		// now we do the rendering options for each driver
		// before we go into this code let's make sure that an update does not occur 
		// on the display by UnSetting the redraw flag
		HC_Control_Update_By_Key(pHView->GetViewKey(), "unset redraw");
	
		char imageDriver[MVO_SEGMENT_PATHNAME_BUFFER];
		if (pinfo->clipBoard)
		{
			bool useOpenGLImageGeneration = false;
			HPoint rgbtop, rgbbottom;
			char color[MVO_BUFFER_SIZE];
			
			HRenderMode rndrmode = pHView->GetRenderMode();
			pHView->GetWindowColor(rgbtop, rgbbottom);
			HCLOCALE(sprintf(color, "windows=(r=%f g=%f b=%f), window contrast = (r=%f g=%f b=%f)", rgbtop.x, rgbtop.y, rgbtop.z, rgbbottom.x, rgbbottom.y, rgbbottom.z));
			HC_Set_Window_Pattern("Down");
			HC_Set_Color(color);
			
			if (rndrmode == HRenderHiddenLine || rndrmode == HRenderHiddenLineFast)
			{
				char settings[MVO_BUFFER_SIZE];
				HC_Open_Segment_By_Key(pHView->GetViewKey());
					HC_Show_One_Net_Rendering_Optio("hidden line removal options", sTemp);
				HC_Close_Segment();
				
				sprintf(settings, "hsra=hidden line,hlro=(%s)", sTemp);
				HC_Set_Rendering_Options(settings);
			}
			else if (rndrmode == HRenderWireframe) 
			{
				// transparency forces rasterisation of the scene and so we
				// turn it off here as it has no meaning in wireframe display
				sprintf (sTemp, "hsra=(z-sort only), transparency = (style = off)");
				HC_Set_Rendering_Options (sTemp);
			}
			else 
			{
				DWORD   dwVersion = GetVersion ();
				if (dwVersion < 0x80000000)
					useOpenGLImageGeneration = true;
				
				if (useOpenGLImageGeneration)
				{				
					int width, height;
					HC_Open_Segment_By_Key(pHView->GetViewKey());
						HC_Show_Device_Info(".", "pixels", sTemp);
					HC_Close_Segment();
					sscanf(sTemp,"%d,%d",&width, &height);
					
					HC_Open_Segment ("?driver/null/1");
						HC_KEY image_key = HC_KInsert_Image(0.0, 0.0, 0.0, "rgb, name=background", width, height, NULL);
					HC_Close_Segment ();
					
					long debug = 0l;
					sprintf(imageDriver, "/driver/opengl/image");
					debug |= 0x00100000;
					debug |= DEBUG_FORCE_SOFTWARE;
					
					// prepare data to render
					HC_Open_Segment (imageDriver);

						HC_Set_Color(color);
						HC_Set_Window_Pattern("Down");
						
						sprintf (sTemp, "use window id = %s%p, isolated, debug=%d", H_EXTRA_POINTER_FORMAT, image_key, debug);
						HC_Set_Driver_Options (sTemp);
						HC_Set_Driver_Options ("subscreen=(-1,1,-1,1)");
						
						//need to activate driver for Compute_Coordinate calculations
						HC_Update_One_Display (imageDriver);
						
						HC_Set_Rendering_Options("hsra = hzb");
						HC_Set_Rendering_Options("attribute lock=(color=(windows))");
						HC_Set_Window_Frame("off");
					
						HC_Include_Segment_By_Key (pHView->GetSceneKey());
					
					HC_Close_Segment ();
					
					//create the image
					HC_Update_One_Display (imageDriver);
					
					// put this image in the background
					HC_Set_Color("windows=background");
				}
				else
					HC_Set_Rendering_Options ("technology = software frame buffer, hsra = szb");
			}
		
			if (!useOpenGLImageGeneration)
				HC_Include_Segment_By_Key (pHView->GetSceneKey());
			
		HC_Close_Segment();
				
		HC_Control_Update (driver, "redraw everything");
		HC_Update_One_Display (driver);
		HC_Delete_Segment (driver);
				
		if (!isActivex)
		{
			// put the data on the clipboard
			HENHMETAFILE hEmf = CloseEnhMetaFile(hMfDC);
			if (hEmf == NULL) 
				return OutputFail;
			
			if (OpenClipboard((HWND)pinfo->windowID)) 
			{
				SetClipboardData (CF_ENHMETAFILE, hEmf);
				CloseClipboard();
			}		
			DeleteEnhMetaFile(hEmf);
		}

		if (useOpenGLImageGeneration)
		{		
			if (rasterOutput || isAxisTriad)
			{
				HC_Delete_Segment ("?driver/null/1");
				HC_Delete_Segment (imageDriver);
			}	
		}
	}
	else
	{
		HC_KEY image_key = INVALID_KEY;

		float SubscreenXmin = -1.0f;
		float SubscreenXmax = 1.0f;
		float SubscreenYmin =  -1.0f;
		float SubscreenYmax = 1.0f;
		int page_w_mm = GetDeviceCaps(hAttribDC, HORZSIZE);
		int page_h_mm = GetDeviceCaps(hAttribDC, VERTSIZE);
		float page_ar = (float)page_w_mm/(float)page_h_mm;
		if( window_ar > page_ar )
		{
			SubscreenYmin = -page_ar/window_ar;
			SubscreenYmax = page_ar/window_ar;
		}
		else
		{
			SubscreenXmin = -window_ar/page_ar;
			SubscreenXmax = window_ar/page_ar;
		}

		HCLOCALE(sprintf (sTemp, "subscreen = (%f, %f, %f, %f)",  SubscreenXmin, SubscreenXmax, SubscreenYmin, SubscreenYmax));
		HC_Set_Driver_Options ( sTemp);

		if (rasterOutput || pHView->GetAxisMode() != AxisOff)
		{
			
			// stretch blit image 100 dpi
			float page_w_inches = page_w_mm * 0.03937f;
			float page_h_inches = page_h_mm * 0.03937f;
			int image_dpi=100;
			int iwidth = (int) (page_w_inches*image_dpi*0.5*(SubscreenXmax-SubscreenXmin)) ;
			int iheight =(int)(page_h_inches*image_dpi*0.5*(SubscreenYmax-SubscreenYmin));
				
			// prepare image for rendering
			HC_Open_Segment ("?driver/null/1");
				image_key = HC_KInsert_Image(0.0, 0.0, 0.0, "rgb, name=background", iwidth, iheight, NULL);
			HC_Close_Segment ();
				
				
			bool useOpenGLImageGeneration = true;
			long debug=0L;

			DWORD   dwVersion = GetVersion ();
			if (dwVersion >= 0x80000000)
				useOpenGLImageGeneration = false;
			if (useOpenGLImageGeneration)
			{
				sprintf(imageDriver, "/driver/opengl/image");
				debug |= 0x00100000;
				debug |= DEBUG_FORCE_SOFTWARE;
			}
			else
				sprintf(imageDriver, "?driver/image/1");
				
			// prepare data to render
			HC_Open_Segment (imageDriver);

				HPoint	window_color;
				window_color.Set(1.0,1.0,1.0);
				HC_Set_Color_By_Value("windows", "RGB", window_color.x, window_color.y, window_color.z);

				sprintf (sTemp, "use window id = %s%p, isolated, debug=%d", H_EXTRA_POINTER_FORMAT, image_key, debug);
				HC_Set_Driver_Options (sTemp);
				HC_Set_Driver_Options( "subscreen = (-1,1,-1,1)" );

				HC_Set_Window(SubscreenXmin, SubscreenXmax, SubscreenYmin, SubscreenYmax);
				HC_Set_Window_Frame("off");

				//need to activate driver for Compute_Coordinate calculations
				HC_Update_One_Display (imageDriver);
				
				//lock all the geometry that we want drawn as vectors
				HC_Set_Visibility("lines=off,edges=off,markers=off,text=off");
				
				if (useOpenGLImageGeneration)
					HC_Set_Rendering_Options("hsra = hzb");
				else
					HC_Set_Rendering_Options("hsra = szb");
				
				HC_Set_Rendering_Options("attribute lock=(visibility=(lines,edges,markers,text), color=(windows))");

				// include this code if note background should be visible in printing
 				/*
				HC_Set_User_Index(H_ANNOTATE_SUPPRESS_TEXT_MAGIC, (void *)1);
				HC_Open_Segment_By_Key(pHView->GetMarkupManager()->GetMarkupKey());
				HC_Set_Visibility("text=on");
				HC_Set_Rendering_Options("attribute lock=(visibility=(text))");
				HC_Close_Segment();
				*/
		
				if (rasterOutput)
					HC_Include_Segment_By_Key (pHView->GetSceneKey());
			
			HC_Close_Segment ();
			
			//create the image
			HC_Update_One_Display (imageDriver);
			// include this code if note background should be visible in printing
			/*
			HC_Open_Segment_By_Key(pHView->GetMarkupManager()->GetMarkupKey());
				HC_UnSet_Visibility();
				HC_UnSet_Rendering_Options();
 			HC_Close_Segment();
			HC_Set_User_Index(H_ANNOTATE_SUPPRESS_TEXT_MAGIC, (void *)2);
			*/
			// put this image in the background
			HC_Set_Color("windows=background");

			HC_Set_Rendering_Options("attribute lock=(heuristics),hsra=hidden line,hlro=(visibility=off)");

			char settings[MVO_BUFFER_SIZE];
			HC_Open_Segment_By_Key(pHView->GetSceneKey());
				HC_Show_One_Net_Rendering_Optio("hidden line removal options", sTemp);
			HC_Close_Segment();

			sprintf(settings, "hsra=hidden line,hlro=(%s)", sTemp);
			HC_Set_Rendering_Options(settings);
	}
		
		if( !rasterOutput )//non rasterOutput path
		{
			HRenderMode rndrmode = pHView->GetRenderMode();
			if (rndrmode == HRenderHiddenLine || rndrmode == HRenderHiddenLineFast)
			{
				char settings[MVO_BUFFER_SIZE];
				
				HC_Open_Segment_By_Key(pHView->GetViewKey());
				HC_Show_One_Net_Rendering_Optio("hidden line removal options", sTemp);
				HC_Close_Segment();
				
				sprintf(settings, "hsra=hidden line,hlro=(%s)", sTemp);
				HC_Set_Rendering_Options(settings);
			}
			else if (rndrmode == HRenderWireframe) 
			{
				// transparency forces rasterization of the scene and so we
				// turn it off here as it has no meaning in wireframe display
				sprintf (sTemp, "hsra=(z-sort only), transparency = (style = off)");
				HC_Set_Rendering_Options (sTemp);
			}
			else 
			{	
				// use the standard painters method for HSR removal
				// black makes sure that the edes appear non-rasterised on non-color printers
				sprintf (sTemp, "hsra=painters, debug = %u", DEBUG_NO_PAINTERS_PANELLING);
				HC_Set_Rendering_Options (sTemp);
			}
		}
			
		
		if( rasterOutput || isAxisTriad)
		{
			// we do not want the background on the subwindows to be screwed up
			// create so set the window pattern as blend before we include
			// the scene

			HC_Set_Window_Pattern("blend");

		}

		HC_Include_Segment_By_Key (pHView->GetSceneKey());

	HC_Close_Segment();

	HC_Control_Update (driver, "redraw everything");
	HC_Update_One_Display (driver);
	HC_Delete_Segment (driver);
			
		if (rasterOutput || isAxisTriad)
		{
			if( image_key != INVALID_KEY )
				HC_Delete_By_Key(image_key);
			HC_Delete_Segment ("?driver/null/1");
			HC_Delete_Segment (imageDriver);
		}		
	}
	
	// this final update ensures that 3dGS frees up any 
	// memory that it may have been keeping around
	HC_Update_Display();
	
	return OutputOK;
}



