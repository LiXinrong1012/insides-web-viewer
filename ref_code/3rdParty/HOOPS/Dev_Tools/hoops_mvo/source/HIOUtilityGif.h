//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HIOUtilityGif.h,v 1.18 2008-12-16 18:52:50 guido Exp $
//


#ifndef _HIOUTILITYGIF_H
#define _HIOUTILITYGIF_H

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include "HTools.h"
#include "HIOManager.h"

/*! The HIOUtilityGif allows you to read in GIF images.  This class is currently unsupported with 
	the LeadTools Raster Pro Toolkit being the recommended way of importing or exporting raster data.
*/
class MVO_API HIOUtilityGif: public HInputHandler
{

public:
	/*! Constructs an HIOUtilityGif object.*/
	HIOUtilityGif()	{
		SetInputOps(HInputOpFileInputToImageKey);
	};

	virtual ~HIOUtilityGif() {;};

	/*! \return A character pointer denoting the name of the handler. 
	*/	
	const char * GetInputName() { return "HIOUtilityGif"; }


	/*!This method registers the "gif" extension to this handler.*/
	void RegisterInputHandlerTypes() {
		HIORegisterInputType("gif",this);
	};

	/*! \return The string of the type of input this handler creates which is "gif".*/
	const char * GetInputTypesString() {return "gif";};

	/*! \return The type of input style which is HInputHandlerStyleImage.*/
	HInputHandlerStyle GetInputStyle() {return HInputHandlerStyleImage;};

	/*!
	  This method reads the raster data defined in filename into a HOOPS image in the key segment.
	  \param FileName A character pointer denoting the name of the image file to read from.
		\param image_key The pointer to a HOOPS key that will be filled in with a HOOPS image key.
		\param segment_key The HOOPS segment key to create the image_key in i.e. the working segment.
	  \param options The file input options. 
	  \return The #HFileOutputResult result of the operation.

	*/
	HFileInputResult FileInputToImageKey(const __wchar_t * filename, HC_KEY * image_key, HC_KEY segment_key, HInputHandlerOptions * options);

	HFileInputResult FileInputToImageKey(const unsigned short * filename, HC_KEY * image_key, HC_KEY segment_key, HInputHandlerOptions * options){
		H_UTF16 utf16;
		utf16.encodedText((utf16_char const*) filename);
		return FileInputToImageKey(H_WCS(utf16).encodedText(), image_key, segment_key, options);
	}

	HFileInputResult FileInputToImageKey(const char * filename, HC_KEY * image_key, HC_KEY segment_key, HInputHandlerOptions * options){
		return FileInputToImageKey(H_WCS(filename).encodedText(), image_key, segment_key, options);
	}
};


#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif
