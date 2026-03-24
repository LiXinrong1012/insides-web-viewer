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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HIOUtilityTiff.h,v 1.17 2008-12-16 18:52:50 guido Exp $
//

#ifndef _HIOUTILITYTIFF_H
#define _HIOUTILITYTIFF_H

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include "HTools.h"
#include "HIOManager.h"

/*! The HIOUtilityTiff allows you to export TIFF images.  This class is currently unsupported with 
	the LeadTools Raster Pro Toolkit being the recommended way of importing or exporting raster data.
*/
class MVO_API HIOUtilityTiff: public HOutputHandler
{

public:

	/*!Constructs an HIOUtilityTiff object.*/
	HIOUtilityTiff(){ 
		SetOutputOps(HOutputOpFileOutputFromImageKey);
	};
	virtual ~HIOUtilityTiff() {;};

	/*! \return A character pointer denoting the name of the handler. 
	*/
	const char * GetOutputName() { return "HIOUtilityTiff"; }	

	/*!This method registers the "tiff" and "tif" extensions to this handler as an output handler.*/
	void RegisterOutputHandlerTypes() {
		HIORegisterOutputType("tiff",this);
		HIORegisterOutputType("tif",this);
	};

		/*! \return The string of the type of output this handler creates which are "tiff" and "tif".*/
	const char * GetOutputTypesString() {return "tif;tiff";};

	/*! \return The type of output style which is #HOutputHandlerStyleImage.*/
	HOutputHandlerStyle GetOutputStyle() {return HOutputHandlerStyleImage;};

	/*!
	  This method exports the raster data defined in the HOOPS Image from the given <i>image_key</i> to a TIFF file.
	  
		\param FileName A character pointer denoting the name of the image file to read from.
		\param image_key The pointer to a HOOPS key that will be filled in with a HOOPS image key.
		\param segment_key The HOOPS segment key to create the image_key in i.e. the working segment.
		\param options This parameter is currently not being used.
		\return The #HFileOutputResult result of the operation.
	*/
	HFileOutputResult FileOutputFromImageKey(const __wchar_t * filename, HC_KEY image_key, HOutputHandlerOptions * options);

	HFileOutputResult FileOutputFromImageKey(const unsigned short * filename, HC_KEY image_key, HOutputHandlerOptions * options){
		H_UTF16 utf16;
		utf16.encodedText((utf16_char const*) filename);
		return FileOutputFromImageKey(H_WCS(utf16).encodedText(), image_key, options);
	}

	HFileOutputResult FileOutputFromImageKey(const char * filename, HC_KEY image_key, HOutputHandlerOptions * options){
		return FileOutputFromImageKey(H_WCS(filename).encodedText(), image_key, options);
	}
};


#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif
