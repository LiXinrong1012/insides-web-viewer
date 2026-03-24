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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HIOUtilityMagick.cpp,v 1.35 2010-10-13 19:25:23 jason Exp $
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HIOUtilityMagick.h"
#include "HDB.h"
#include "HUtility.h"
#include "HUtilityLocaleString.h"

#ifdef USE_IMAGE_MAGICK

#include <magick/api.h>


void HIOUtilityMagick::RegisterInputHandlerTypes() {
    HIORegisterInputType("jpeg",this);  
    HIORegisterInputType("jpg",this);  
    HIORegisterInputType("bmp",this);  
    HIORegisterInputType("gif",this);  
    HIORegisterInputType("tif",this); 
    HIORegisterInputType("tiff",this);
    HIORegisterInputType("psd",this);
    HIORegisterInputType("pcd",this); 
    HIORegisterInputType("pcx",this); 
    HIORegisterInputType("png",this);   
    HIORegisterInputType("tga",this);   
}

HInputHandlerStyle HIOUtilityMagick::GetInputStyle() {return HInputHandlerStyleImage;};

const char * HIOUtilityMagick::GetInputTypesString() {return "jpeg;jpg;bmp;gif;tif;tiff;psd;pcd;pcx;png;tga";};

void HIOUtilityMagick::RegisterOutputHandlerTypes() {
    HIORegisterOutputType("jpeg",this);
    HIORegisterOutputType("jpg",this); 
    HIORegisterOutputType("bmp",this);  
    HIORegisterOutputType("gif",this);  
    HIORegisterOutputType("tif",this);  
    HIORegisterOutputType("tiff",this); 
    HIORegisterOutputType("psd",this);
    HIORegisterOutputType("pcd",this);
    HIORegisterOutputType("pcx",this); 
    HIORegisterOutputType("png",this); 
    HIORegisterOutputType("tga",this); 
}

HOutputHandlerStyle HIOUtilityMagick::GetOutputStyle() {return HOutputHandlerStyleImage;};

const char * HIOUtilityMagick::GetOutputTypesString() {return "jpeg;jpg;bmp;gif;tif;tiff;psd;pcd;pcx;png;tga";};


class HMagickInternal {

public:

    static bool FileToImage(const wchar_t *filename, 
	    HC_KEY *image_key, HC_KEY segment_key, 
	    const char *imagename, const char *format, bool local,
		HInputHandler * peer);

    static bool ImageToFile( HC_KEY image_key, const wchar_t *filename, HOutputHandler * peer);

};

HIOUtilityMagick::~HIOUtilityMagick() {}

char const * HIOUtilityMagick::GetInputName() {
	return "HIOUtilityMagick";
}

char const * HIOUtilityMagick::GetOutputName() {
	return "HIOUtilityMagick";
}

HFileInputResult HIOUtilityMagick::FileInputToImageKey(const wchar_t * filename, 
    HC_KEY * image_key, HC_KEY segment_key, HInputHandlerOptions * options)
{
	if(!filename) return InputBadFileName;
	if(!image_key || !segment_key) return InputFail;

	SetStartingInput();

	const char * image_format = 0;
	const char * image_name = 0;

	if(options && options->m_pImageFormat) 
		image_format = options->m_pImageFormat;
	else
		image_format = "rgb";

	if(options) 
		image_name = options->m_pImageName;

	bool local = false;

	if (options && options->m_bLocal)
		local=true;

	bool result = HMagickInternal::FileToImage(filename, 
		image_key, segment_key, image_name, image_format, local, this);
	SetFinishedInput();

	if(result)
		return InputOK;
	else
		return InputFail;
}

HFileOutputResult HIOUtilityMagick::FileOutputFromImageKey(const wchar_t * filename, 
	HC_KEY image_key, HOutputHandlerOptions * options)
{
	if (!filename) return OutputBadFileName;
	if (!image_key) return OutputFail;

	SetStartingOutput();

	bool result = HMagickInternal::ImageToFile(image_key, filename, this);

	SetFinishedOutput();

	if(result) 
		return OutputOK;
	else
		return OutputFail;
}


bool HMagickInternal::FileToImage(const wchar_t *filename, 
    HC_KEY *image_key, HC_KEY segment_key, 
    const char *imagename, const char *format, bool local,
	HInputHandler * peer)
{
    ExceptionInfo exception;
    ImageInfo *image_info;
    Image *image;
	bool rc = false;

	*image_key = INVALID_KEY;

    InitializeMagick("."); 

    GetExceptionInfo(&exception);

    image_info=CloneImageInfo((ImageInfo *) NULL);
	strcpy(image_info->filename, H_ASCII_TEXT(filename));

    image=ReadImage(image_info,&exception);
    
	if (exception.severity != UndefinedException){
		CatchException(&exception);
		peer->ReportInputInformation("CatchException(&exception);\n"); 
    }

    if (!image) {
		peer->ReportInputInformation("!image\n"); 
		DestroyImageInfo(image_info);
		DestroyExceptionInfo(&exception);
		DestroyMagick(); 
		return false;
    }

	ImageType it = GetImageType(image, &exception);

	char const * magick_format = 0;
	char const * hoops_format = 0;
	int pixel_size = 0;
	switch(it){
		case PaletteMatteType:
		case GrayscaleMatteType:
		case TrueColorMatteType:
			magick_format = "RGBA";
			hoops_format = "RGBA";
			pixel_size = 4;
			break;

		case GrayscaleType:
			magick_format = "I";
			hoops_format = "grayscale";
			pixel_size = 1;
		break;

		case TrueColorType:
		default:
			if(image->compression == JPEGCompression){
				magick_format = 0;
				hoops_format = "jpeg";
				pixel_size = 0;
			}
			else if(strieq(image->magick, "tga")){
				magick_format = 0;
				hoops_format = "tga";
				pixel_size = 0;
			}
			else{
				magick_format = "RGB";
				hoops_format = "RGB";
				pixel_size = 3;
			}
	}

    unsigned int width = image->magick_columns;
    unsigned int height = image->magick_rows;
    unsigned char * pixels = 0;
	
	if(pixel_size){
		pixels = new unsigned char[width * height * pixel_size];  
		ExportImagePixels(image, 0, 0, width, height, magick_format, CharPixel, pixels, &exception); 
	}

    char image_spec[MVO_BUFFER_SIZE];

    if (imagename)
		sprintf(image_spec, "%s, name = %s", hoops_format, imagename);
    else
		sprintf(image_spec, hoops_format);

	if (local)
		strcat(image_spec, ", local");

	HC_Open_Segment_By_Key(segment_key);{
		if(pixels){
			*image_key = HC_Insert_Image (0.0,0.0,0.0, image_spec, width, height, pixels);
			delete [] pixels;
			if(*image_key != INVALID_KEY)
				rc = true;
		}
		else {
			size_t size = 0;
			unsigned char * jpg = ImageToBlob(image_info, image, &size, &exception);
			if(jpg && size > 0){
				*image_key = HC_Insert_Compressed_Image (0.0, 0.0, 0.0, image_spec, width, height, (int)size, jpg);

				if(*image_key != INVALID_KEY)
					rc = true;
			}
			if(jpg)
				free(jpg);
		}
	}HC_Close_Segment();

	DestroyImage(image);
    DestroyImageInfo(image_info);
    DestroyExceptionInfo(&exception);
    DestroyMagick(); 

    return rc;
}

bool HMagickInternal::ImageToFile( HC_KEY image_key, const wchar_t *filename, HOutputHandler * peer)
{
    char format[MVO_BUFFER_SIZE];   
    unsigned char *pixels=0, *gray=0;
    int width, height;
    float x,y,z;   

    HC_Show_Image_Size(image_key, &x, &y, &z, format, &width, &height);

	char * comma;

	if ((comma = strchr(format, ',')) != 0)
		*comma = '\0';

    // if not the format we like, return
    if(!strieq(format, "grayscale") && !strieq(format, "tga") && !strieq(format, "jpeg") && !strieq(format, "rgb" ) && !strieq(format, "rgba" )) {
		peer->ReportOutputInformation(H_FORMAT_TEXT("Error: Export for %s format not implemented\n", format));
		return false;
    }

	int pixel_size=3;
		
	if (streq(format, "rgba" ))
		pixel_size=4;

    if( width<1 || height < 1) {
		peer->ReportOutputInformation("Error: HOOPS Image too small to export.\n");
		return false;
    }

    pixels = new unsigned char[width*height*pixel_size];
	if(strieq(format, "grayscale")){
    		HC_Show_Geometry_Pointer(image_key, "grayscale rasters", &gray);
		for(int row = 0; row < height; ++row){
			for(int col = 0; col < width; ++col){
				for(int i = 0; i < pixel_size; ++i){
					pixels[pixel_size * (row * width + col) + i] = gray[row * width + col];
				}
			}
		}
	}
	else
    		HC_Show_Partial_Image(image_key, 0, 0, width, height, pixels);

    // make ImageMagick image
    ExceptionInfo exception;
    ImageInfo *image_info=0;
    Image *image=0;
    int write_error = 0;

    InitializeMagick("."); 

    GetExceptionInfo(&exception);

	image=ConstituteImage ( width, height, (pixel_size==3)?"RGB":"RGBA", CharPixel, pixels, &exception ); 

    if (exception.severity != UndefinedException){
		CatchException(&exception);
		peer->ReportOutputInformation("Error: CatchException(&exception);\n"); 
    }

    if (!image) {
		peer->ReportOutputInformation("Error: ConstituteImage failed!\n"); 
		goto CLEANUP_FILE_WRITE;
    }

    image_info=CloneImageInfo((ImageInfo *) NULL);
    strcpy(image->filename, H_ASCII_TEXT(filename));

    write_error = WriteImage(image_info, image);

CLEANUP_FILE_WRITE:

    if(image) 
		DestroyImage(image);
    if(image_info) 
		DestroyImageInfo(image_info);
    DestroyExceptionInfo(&exception);

    DestroyMagick(); 

    if(pixels) delete[] pixels; 

    return true;
}

HFileOutputResult HIOUtilityMagick::FileOutputFromImageKey(const unsigned short * filename, HC_KEY image_key, HOutputHandlerOptions * options){
	H_UTF16 utf16;
	utf16.encodedText((utf16_char const*) filename);
	return FileOutputFromImageKey(H_WCS(utf16).encodedText(), image_key, options);
}

HFileOutputResult HIOUtilityMagick::FileOutputFromImageKey(const char * filename, HC_KEY image_key, HOutputHandlerOptions * options){
	return FileOutputFromImageKey(H_WCS(filename).encodedText(), image_key, options);
}

HFileInputResult HIOUtilityMagick::FileInputToImageKey(const unsigned short * filename, HC_KEY * image_key, HC_KEY segment_key, HInputHandlerOptions * options){
	H_UTF16 utf16;
	utf16.encodedText((utf16_char const*) filename);
	return FileInputToImageKey(H_WCS(utf16).encodedText(), image_key, segment_key, options);
}

HFileInputResult HIOUtilityMagick::FileInputToImageKey(const char * filename, HC_KEY * image_key, HC_KEY segment_key, HInputHandlerOptions * options){
	return FileInputToImageKey(H_WCS(filename).encodedText(), image_key, segment_key, options);
}

HIOUtilityMagick::HIOUtilityMagick() { 
	SetInputOps(HInputOpFileInputToImageKey);
	SetOutputOps(HOutputOpFileOutputFromImageKey);
};

#endif

