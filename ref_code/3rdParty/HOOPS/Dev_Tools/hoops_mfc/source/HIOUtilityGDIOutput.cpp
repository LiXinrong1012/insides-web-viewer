#ifndef ALT_STDAFX
#include "stdafx.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HIOUtilityGDIOutput.h"
#include "HIOUtilityHOOPS.h"
#include "HBaseView.h"
#include "HBaseOperator.h"
#include "HUtilityLocaleString.h"
#include "HMarkupManager.h"

#include "hic.h"
#include "utf_utils.h"

HFileOutputResult
HIOUtilityGDIOutput::DoClipBoard(const wchar_t * FileName, 
								 HC_KEY key, GDIExportInformation * options)
{
	wchar_t sTemp[128];
	wchar_t const * output;

	HUtility::FindFileNameExtension(FileName, sTemp);
	if (wcseq(sTemp, L"emf")){
		output = FileName;
	} else {
		output = L"clipboard";
	}

	options->m_bUseWindowColor = true;
	options->m_bConserveMemory = false;
	options->m_bUseSubscreen = false;
	
	options->m_Paper_Dpi = options->m_Image_Dpi;
	options->m_Paper_Width = options->m_Window_Width;
	options->m_Paper_Height = options->m_Window_Height;

	HFileOutputResult retval = HUtility::TwoPassPrint(H_FORMAT_TEXT("/driver/msw/%s", H_ASCII_TEXT(output)), options);
	HC_Delete_Segment(H_FORMAT_TEXT("/driver/msw/%s", H_ASCII_TEXT(output)));

	return retval;
}

HFileOutputResult
HIOUtilityGDIOutput::DoPrinter(const wchar_t * FileName, 
							   HC_KEY key, GDIExportInformation * options)
{
	// set the device contexts and driver string depending on whether
	// printing or copy to clipboard

	// only include axis triad if printing
	HC_Open_Segment ("/driver/msw/printer");{

		// first let's do the generic print driver set up
		long debug_flags = 0;
		debug_flags |= DEBUG_PRINTING_MODE;
		debug_flags |= DEBUG_PRINT_NOT_FRAMEBUFFER_MODE;
		debug_flags |= DEBUG_PRINT_NOT_RASTER_REDUCTION;
		debug_flags |= 0x00000020;

		HC_Set_Driver_Options (H_FORMAT_TEXT( "debug = %u,"
						"special events, disable input=all,"
						"subscreen stretching, isolated,"
						"use window ID = %s%p,"
						"use window ID2 = %s%p,"
						"output format = %s%p",
						debug_flags,
						H_EXTRA_POINTER_FORMAT, options->windowID,
						H_EXTRA_POINTER_FORMAT, options->attribDC,
						H_EXTRA_POINTER_FORMAT, (void*)options->deviceContext));
	

		// now we do the rendering options for each driver
		// before we go into this code let's make sure that an update does not occur 
		// on the display by UnSetting the redraw flag
		HC_Control_Update_By_Key(options->m_pHBaseView->GetViewKey(), "unset redraw");

	}HC_Close_Segment();

	HFileOutputResult retval = HUtility::TwoPassPrint("/driver/msw/printer", options);
	HC_Delete_Segment("/driver/msw/printer");

	return retval;
}

/*!
  This is the function which should be used for all GDI Print and Copy to Clipboard work

  \param FileName A character pointer denoting the name of the file to be read in
  \param key This is typically unused 
  \param options You pass in the HBaseView pointer, the camera setting, the device context and the hWnd
	within this structure
  \return result of operation
*/

HFileOutputResult HIOUtilityGDIOutput::FileOutputByKey(const wchar_t *FileName, HC_KEY key, HOutputHandlerOptions * options) 
{
	if(!FileName) return OutputBadFileName;
	if(!key || !options) return OutputFail;
	HFileOutputResult result;

	GDIExportInformation* pinfo = (GDIExportInformation *)options;
	
	if (pinfo->clipBoard)
		result = DoClipBoard(FileName, key, pinfo);
	else result = DoPrinter(FileName, key, pinfo);
	
	return result;
}



