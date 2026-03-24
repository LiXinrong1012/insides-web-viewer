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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HIOUtilityTiff.cpp,v 1.17 2010-02-23 20:13:48 reuben Exp $
//



#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "HTools.h"

#include "HIOUtilityTiff.h"



//THE INTERFACE CODE IS AFTER THIS CLASS

class MVO_API HTiffInternal
{
public:

	static bool ImageToTiff( HC_KEY image_key,const wchar_t *filename);

private:
// TIFF utility datastructures and methods 
	typedef struct {				// Fixed header
	  unsigned short ByteOrder;		// Intel or Motorola byte ordering
	  unsigned short Version;		// TIFF version identifier
	  unsigned long  Offset;		// Offset to first Image File
	} TIFFHEADER;					// Directory (IFD)

	typedef struct {				// A tag entry
	  unsigned short Tag;			// Tag identifier
	  unsigned short DataType;		// Data type of value stored in entry
	  unsigned long Length;			// Number of values in tag entry
	  unsigned long Offset;			// Offset or value of tag
	} TIFFTAGENTRY;

	typedef struct {				// Values read from the tag entries
	  short BitsPerSample;			// 8 for grayscale; 8,8,8 for RGB
	  short Compression;			// Compression flag
	  short SamplesPerPixel;		// 1 for grayscale; 3 for RGB
	  short NumStrips;				// Number of strips in file
	  unsigned long *StripLengths;	// Array of strip lengths
	  unsigned long *StripOffsets;	// Array of strip file offsets
	} TIFFIMAGEINFO;

	int ReadStrips(FILE *fp, TIFFIMAGEINFO *ImInfo,unsigned char  *Im);
	int ReadGrayTIFFImage(FILE *fp, unsigned char  *Im);
	int ReadRGBTIFFImage(FILE *fp, unsigned char  *Im);
	int GetTIFFImageInfo(FILE *fp, int *ImWd, int *ImHt, int *ImType);
	int GetImageInfo(char *Path, int *ImWd, int *ImHt, int *ImType);
	int ReadImage(char *Path, unsigned char  *Im);
	static int WriteTag(FILE *fp, unsigned int Tag, unsigned int DataType, unsigned long Len, unsigned long Offs, int is_offset);
	static int WriteRGBTIFFHeader(FILE *fp, unsigned long ImWd, unsigned long ImHt, unsigned long StripSize);
	int WriteGrayTIFFHeader(FILE *fp, unsigned long ImWd, unsigned long ImHt, unsigned long StripSize);
	static int WriteFxdHdr(FILE *fp);
	void SwapWordOrder(unsigned short *Word);
	void SwapLongOrder(unsigned long *Long);
	int ReadTag(FILE *fp, TIFFTAGENTRY *Entry);
	int ReadWord(FILE *fp, unsigned short *Val);
	int ReadULong(FILE *fp, unsigned long *Val);
	int ReadTags(FILE *fp, TIFFIMAGEINFO *ImInfo);
	int ReadFxdHdr(FILE *fp, unsigned long *FileOffs);

	void fput_word(FILE	*fp, int	n);
	void fput_long(FILE *fp, long n);
	void write_TIFF_tag(FILE *fp, int tag, int type, long length, long offset);
	void image_to_TIFF (HC_KEY image_key, FILE	*fp);

	unsigned char IntelOrdr;

};


HFileOutputResult HIOUtilityTiff::FileOutputFromImageKey(const wchar_t * filename, HC_KEY image_key, HOutputHandlerOptions * options)
{
	if (!filename) return OutputBadFileName;
	if (!image_key) return OutputFail;

	SetStartingOutput();

	bool result = HTiffInternal::ImageToTiff(image_key, filename);

	SetFinishedOutput();

	if(result) 
		return OutputOK;
	else
		return OutputFail;
}


#if 0

HFileOutputResult HIOUtilityTiff::FileOutputByKey(const char * filename, HC_KEY key, ) 
{

	if (!filename) return OutputBadFileName;
	if (key == INVALID_KEY) return OutputFail;
	if (!width || !height) return OutputNotHandled;


	// prepare image for rendering
    HC_Open_Segment ("?driver/null/1");
        HPixelRGB *image = new HPixelRGB[width * height];
        HC_KEY image_key = HC_KInsert_Image (0.0, 0.0, 0.0, "rgb", width, height, image);
    HC_Close_Segment ();

	// prepare data to render
    HC_Open_Segment ("?driver/image/1");

		char buffer[MVO_BUFFER_SIZE];
        sprintf (buffer, "use window id = (image key = %s%p), subscreen = (-1, 1, -1, 1)", H_EXTRA_POINTER_FORMAT, (void*)image_key);
        HC_Set_Driver_Options (buffer);
		HC_Set_Driver_Options ("isolated");
        HC_Include_Segment_By_Key (key);

	HC_Close_Segment ();

    HC_Update_One_Display ("?driver/image/1");

	HFileOutputResult result = FileOutputFromImageKey(filename, image_key);

    HC_Delete_Segment ("?driver/null/1");
    HC_Delete_Segment ("?driver/image/1");

    delete[] image;

	return result;
}

#endif
#if 0

/*
  This is a helper function called by HBaseModel::Write to write a TIFF file. This function may
  alse be called directly, but requires that a HOOPS segment be currently open. 

  \param FileName A character pointer denoting the name of the file to be written
  \param ViewKey Pointer to the HBaseView object using this HBaseModel object.  May be needed to
  get view-dependent information desired for writing out the model information
  \param width An integer denoting the width of the Tiff Image
  \param height An integer denoting the height of the Tiff Image
  \return Success or failure
*/
bool HBaseModel::WriteTiffFile(const char * FileName, HBaseView * pHView, int width, int height) 
{
    HPixelRGB   *image;
    char                                        buffer[MVO_BUFFER_SIZE], hsra_setting[MVO_BUFFER_SIZE], handedness[MVO_BUFFER_SIZE];
    bool                                        result = true;
    HPoint                                      window_color;
    HC_KEY                                      image_key;

    if ((width == 0) || (height == 0))
            return false;

    //determine the correct hsra and window color to use
        HC_Open_Segment_By_Key(pHView->GetViewKey());

            HC_Show_Net_Handedness (handedness);
            HC_Show_One_Net_Rendering_Optio("hidden surface removal algorithm", buffer);

            if (streq(buffer, "hidden line"))
            {
                HC_Show_One_Net_Rendering_Optio("hidden line removal options", buffer);
                sprintf(hsra_setting, "hsra = hidden line, hidden line removal options = (%s)", buffer);
            }
            else
                    sprintf(hsra_setting, "technology = software frame buffer, hsra = szb");
            
            window_color = pHView->GetWindowColor();

        HC_Close_Segment();
        
          
        // prepare image for rendering
    HC_Open_Segment ("?driver/null/1");
        image = new HPixelRGB[width * height];
        image_key = HC_KInsert_Image (0.0, 0.0, 0.0, "rgb", width, height, image);
    HC_Close_Segment ();

        // prepare data to render
    HC_Open_Segment ("?driver/image/1");
        if (pHView->GetHideOverlappedText())
            HImHideOverlappedText::FilterOn();

        sprintf (buffer, "use window id = (image key = %s%p), subscreen = (-1, 1, -1, 1)", H_EXTRA_POINTER_FORMAT, image_key);
        HC_Set_Driver_Options (buffer);

        HC_Set_Color_By_Value("windows", "RGB", window_color.x, window_color.y, window_color.z);
        HC_Set_Rendering_Options("attribute lock = (color = (window))");
        HC_Set_Rendering_Options(hsra_setting);
        HC_Set_Handedness(handedness);

        HC_Include_Segment_By_Key (pHView->GetSceneKey());
    HC_Close_Segment ();

        // render
    HC_Update_Display ();

    // write the image out to a file
    result = HTiffInternal::ImageToTiff(image_key, FileName);

    HC_Delete_Segment ("?driver/null/1");
    HC_Delete_Segment ("?driver/image/1");

    delete[] image;

    return result;
}

#endif



// TIFF's primary data types
#define TIFFBYTE	1     // An 8-bit unsigned integer
#define TIFFASCII	2     // 8-bit byte that stores ASCII codes
#define TIFFSHORT	3     // A 16-bit (2-byte) unsigned integer
#define TIFFLONG	4     // A 32-bit (4-byte) unsigned integer
#define TIFFRATIONAL	5     // Two longs: the first is the numerator
                              // and the second is the denominator
// TIFF tag constants
#define TGNEWSUBFILETYPE            254
#define TGOLDSUBFILETYPE            255
#define TGIMAGEWIDTH                256
#define TGIMAGELENGTH               257
#define TGBITSPERSAMPLE             258
#define TGCOMPRESSION               259

#define TGPHOTOMETRICINTERPRETATION 262
#define TGTHRESHHOLDING             263
#define TGCELLWIDTH                 264
#define TGCELLLENGTH                265
#define TGFILLORDER                 266

#define TGDOCUMENTNAME              269
#define TGIMAGEDESCRIPTION          270
#define TGMAKE                      271
#define TGMODEL                     272
#define TGSTRIPOFFSETS              273
#define TGORIENTATION               274

#define TGSAMPLESPERPIXEL           277
#define TGROWSPERSTRIP              278
#define TGSTRIPBYTECOUNTS           279
#define TGMINSAMPLEVALUE            280
#define TGMAXSAMPLEVALUE            281
#define TGXRESOLUTION               282
#define TGYRESOLUTION               283
#define TGPLANARCONFIGURATION       284
#define TGPAGENAME                  285
#define TGXPOSITION                 286
#define TGYPOSITION                 287
#define TGFREEOFFSETS               288
#define TGFREEBYTECOUNTS            289
#define	TGGRAYUNIT                  290
#define	TGGRAYCURVE                 291

#define TGRESOLUTIONUNIT            296
#define	TGPAGENUMBER                297

#define	TGCOLORRESPONSECURVES       301

#define	TGSOFTWARE                  305
#define	TGDATETIME                  306

#define TGARTIST                    315
#define TGHOSTCOMPUTER              316

#define TGPREDICTOR                 317
#define	TGWHITEPOINT                318
#define	TGPRIMARYCHROMATICITIES     319
#define	TGCOLORMAP                  320

#define INTELBYTES 0x4949           // Intel byte ordering
#define TIFFVERSION 0x002A          // TIFF file version
#define NOCOMPRESSION 1             // Compression not used

// Error flags
#define TIFFFORMATNOTSUPPORTED -2   // TIFF format now supported
#define IMAGEFILETOOBIG -3          // Image is too big
#define OUTOFMEMORY -4              // Out of memory

#define STRIPSIZE 8192              // Size of image strips





#define TIFF_Image_Width		256
#define TIFF_Image_Length		257
#define TIFF_Bits_Per_Sample		258
#define TIFF_Compression		259
#define TIFF_Photometric_Interp		262
#define TIFF_Strip_Offsets		273
#define TIFF_Samples_Per_Pixel		277
#define TIFF_Strip_Byte_Counts		279
#define TIFF_Planar_Configuration	284

#define TIFF_Short			3
#define TIFF_Long			4


/*
	ImageToTiff writes a TIFF file from a raw HOOPS image
	\param image_key The key to the HOOPS image.
	\param filename The name of the TIFF image
	\return A Boolean value indicating success or failure.
*/
bool HTiffInternal::ImageToTiff( HC_KEY image_key,const wchar_t *filename){

	FILE *fp;
	float fjunk;
	int width, height;
	int row,col;
	char format[16];
	HPixelRGB *image_row;
	HPixelRGB *pixel;

	if((fp = wfopen (filename, L"wb")) == 0) 
		return false;

	HC_Show_Image_Size (image_key, &fjunk, &fjunk, &fjunk, format, &width, &height);
	if (strcmp (format, "rgb")) {
		//fprintf (stderr, "Image is not in RGB format.\n");
		return false;
	}

	image_row = new HPixelRGB[width];

	// Write the file's header
	if (!HTiffInternal::WriteRGBTIFFHeader(fp, width, height, width*3)) {
		return false;
	}

	for (row = 0; row < height; ++row) {
		HC_Show_Partial_Image (image_key, 0, row, width, 1, image_row);
		pixel = image_row;
		for (col = 0; col < width; ++col) {
			fputc (pixel->r(), fp);
			fputc (pixel->g(), fp);
			fputc (pixel->b(), fp);
			++pixel;
		}
	}

	fclose(fp);
	
	delete image_row;

	return true;
  
}


void HTiffInternal::fput_word(FILE *fp, int n) 
{
    fputc (n, fp);
    fputc ((n >> 8), fp);
}


void HTiffInternal::fput_long(FILE *fp, long n) 
{ 
    fputc (n, fp);
    fputc ((n >> 8), fp);
    fputc ((n >> 16), fp);
    fputc ((n >> 24), fp);
}


void HTiffInternal::write_TIFF_tag(FILE *fp, int tag, int type, long length, long offset)  
{ 
    fput_word (fp, tag);
    fput_word (fp, type);
    fput_long (fp, length);
    fput_long (fp, offset);
}


/*
 * This file defines a global routine "write_tiff", which
 * should enable you to create a device-independent TIFF
 * file on any platform.
 * To use the routine, create your segment tree as usual.
 * When you have achieved the desired picture, call
 * 	write_tiff (segname, width, height, filename)
 * where
 *	segname   is the name of the segment at which your
 *                picture starts (usually ?picture)
 *      width     is the desired width in square pixels of
 *		  the final image (note that this doesn't
 *                have anything to do with the size of the
 *                window on the screen)
 *	height	  is the desired height in square pixels of
 *                the final image (same note)
 *      filename  is the name of the file to receive the
 *	          TIFF output
 *
 */

void HTiffInternal::image_to_TIFF (HC_KEY image_key, FILE	*fp) 
{
	float		fjunk;
	char		format[16];
	int			width;
	int			height;
	HPixelRGB	*image_row;
	register	HPixelRGB *pixel;
	long		image_ptr, image_pos;
	long		bits_ptr, bits_pos;
    register	int	row;
    register	int	col;    
    

    HC_Show_Image_Size (image_key, &fjunk, &fjunk, &fjunk, format, &width, &height);
    if (strcmp (format, "rgb")) {
	fprintf (stderr, "Image is not in RGB format.\n");
	return;
    }
    image_row = (HPixelRGB *)malloc (sizeof (HPixelRGB) * width);
    
    /*
     * Write TIFF header
     */
    fput_word (fp, 'I'+('I'<<8));	/* use Motorola packing */
    fput_word (fp, 42);		/* version 42		*/
    fput_long (fp, 8L);		/* offset to dict	*/

    /*
     * Write TIFF dict
     */
    fput_word (fp, 9);		/* tag count */
    write_TIFF_tag (fp, 0x00fe, TIFF_Long, 1L, 0L);
    write_TIFF_tag (fp, TIFF_Image_Width, TIFF_Short, 1L, (long)width);
    write_TIFF_tag (fp, TIFF_Image_Length, TIFF_Short, 1L, (long)height);
    write_TIFF_tag (fp, TIFF_Bits_Per_Sample, TIFF_Short, 3L, 0L);
    bits_ptr = ftell (fp) - 4;
    write_TIFF_tag (fp, TIFF_Photometric_Interp, TIFF_Short, 1L, 2L);
    write_TIFF_tag (fp, TIFF_Strip_Offsets, TIFF_Long, 1L, 0L);
    image_ptr = ftell (fp) - 4;
    write_TIFF_tag (fp, TIFF_Samples_Per_Pixel, TIFF_Short, 1L, 3L);
    write_TIFF_tag (fp, TIFF_Strip_Byte_Counts, TIFF_Long, 1L, width * height * 3L);
    write_TIFF_tag (fp, TIFF_Planar_Configuration, TIFF_Short, 1L, 1L);

    /*
     * Write bits per sample
     */
    bits_pos = ftell (fp);
    fseek (fp, bits_ptr, SEEK_SET);
    fput_long (fp, bits_pos);
    fseek (fp, bits_pos, SEEK_SET);
    fput_word (fp, 0x0008);
    fput_word (fp, 0x0008);
    fput_word (fp, 0x0008);
    
    /*
     * Write image
     */
    image_pos = ftell (fp);
    fseek (fp, image_ptr, SEEK_SET);
    fput_long (fp, image_pos);
    fseek (fp, image_pos, SEEK_SET);
    for (row = 0; row < height; ++row) {
	HC_Show_Partial_Image (image_key, 0, row, width, 1, image_row);
	pixel = &image_row[0];
	for (col = 0; col < width; ++col) {
	    fputc (pixel->r(), fp);
	    fputc (pixel->g(), fp);
	    fputc (pixel->b(), fp);
	    ++pixel;
	}
    }
    if ((width * height) & 0x01) fputc (0x00, fp);
    

    free (image_row);
    fclose (fp);
}


//   ReadFxdHdr   
// 
// Reads the 8-byte, fixed position TIFF header. FileOffs is set
// to number that marks the beginning of the IFD (tag entries).
//
int HTiffInternal::ReadFxdHdr(FILE *fp, unsigned long *FileOffs)
{
  TIFFHEADER TIFFHdr;            // Structure to hold the header

  fseek(fp, 0L, SEEK_SET);                  // Go to top of file
  fread(&TIFFHdr, sizeof(TIFFHEADER), 1, fp);     // Read header

  // Set global decoding flag to use correct byte ordering
  IntelOrdr = (TIFFHdr.ByteOrder == INTELBYTES) ? 1 : 0;

  if (!IntelOrdr)                // If not Intel byte ordering,
    SwapWordOrder(&TIFFHdr.Version);       // swap byte order

  if (TIFFHdr.Version != TIFFVERSION)      // Check TIFF version
    return TIFFFORMATNOTSUPPORTED;

  // "Offset" tells where the IFD (tag entries) starts
  *FileOffs = TIFFHdr.Offset;
  if (!IntelOrdr) SwapLongOrder(FileOffs);
  fseek(fp, *FileOffs, SEEK_SET);
  return 1;
}

///////////////////////////  ReadTags   
//
// Copies the information in the tags to the IMAGEINFO structure.
// It assumes that the file pointer is pointing at the number
// of tags in the file.
//
int HTiffInternal::ReadTags(FILE *fp, TIFFIMAGEINFO *ImInfo)
{
  unsigned short i, j;
  unsigned short Val;
  unsigned short NumTags;           // Number of tags in the IFD
  TIFFTAGENTRY Entry;                 // A tag entry
  unsigned long FilePos;          // File position

  ReadWord(fp, &NumTags);
  for (i=0; i<NumTags; i++) {
    ReadTag(fp, &Entry);          // Read one tag entry at a time
    switch(Entry.Tag) {
      case TGBITSPERSAMPLE:       // Bits per sample
        if (Entry.DataType != TIFFSHORT)
          return TIFFFORMATNOTSUPPORTED;
        if (Entry.Length == 1)
          ImInfo->BitsPerSample = (short)Entry.Offset;
        else if (Entry.Length == 3)
          // Note: This really isn't correct. The code should
          // verify that the three actual numbers--at the
          // Entry.Offset location in the file--equal 8. For
          // simplicity, we'll assume that they do.
          ImInfo->BitsPerSample = 8;
        break;
      case TGCOMPRESSION:         // Compression flag
        if (Entry.DataType != TIFFSHORT || Entry.Length != 1)
          return TIFFFORMATNOTSUPPORTED;
        ImInfo->Compression = (short)Entry.Offset;
	break;
      case TGSAMPLESPERPIXEL:     // Samples per pixel
        if (Entry.DataType != TIFFSHORT || Entry.Length != 1)
          return TIFFFORMATNOTSUPPORTED;
        ImInfo->SamplesPerPixel = (short)Entry.Offset;
        break;
      case TGROWSPERSTRIP:
        // This tag isn't used so it can be removed; however,
        // the field is required
        if ((Entry.DataType != TIFFSHORT &&
          Entry.DataType != TIFFLONG) || Entry.Length != 1)
          return TIFFFORMATNOTSUPPORTED;
        break;
      case TGSTRIPOFFSETS:         // Strip file offsets
        if (Entry.DataType != TIFFSHORT &&
          Entry.DataType != TIFFLONG) {
          return TIFFFORMATNOTSUPPORTED;
        }
        ImInfo->NumStrips = (short)Entry.Length; // Number of strips
        // Allocate memory to hold the file pointers that point
        // to where each strip begins in the file
        ImInfo->StripOffsets = (unsigned long *)malloc
          (sizeof(unsigned long)*ImInfo->NumStrips);
        if (ImInfo->StripOffsets == 0) {
          return OUTOFMEMORY;
        }
        if (ImInfo->NumStrips == 1) {
           // Only one strip length, so the value is in the
           //  Offset field
          ImInfo->StripOffsets[0] = Entry.Offset;
        }
        else {  // The strip offsets are stored later in the file
          FilePos = ftell(fp);  // Remember where the file is now
          // Skip ahead to the list of strip offsets
          fseek(fp, Entry.Offset, SEEK_SET);
          // Read the strip offset. It may be stored as either a
          // long or short.
          if (Entry.DataType == TIFFLONG)
            for (j=0; j<ImInfo->NumStrips; j++)
              ReadULong(fp, &ImInfo->StripOffsets[j]);
          else {
            for (j=0; j<ImInfo->NumStrips; j++) {
              ReadWord(fp, &Val);
              ImInfo->StripOffsets[j] = Val;
            }
          }
          // After reading the strip offsets, go back to the
          // last tag read
          fseek(fp, FilePos, SEEK_SET);
        }
        break;
      case TGSTRIPBYTECOUNTS:     // Strip lengths
        if (Entry.DataType != TIFFSHORT &&
          Entry.DataType != TIFFLONG)
          return TIFFFORMATNOTSUPPORTED;
        ImInfo->NumStrips = (short)Entry.Length;
        ImInfo->StripLengths = (unsigned long *)malloc
          (sizeof(unsigned long)*ImInfo->NumStrips);
        if (ImInfo->StripLengths == 0) {
          free(ImInfo->StripOffsets);
          return OUTOFMEMORY;
        }
        // There is only one strip length so value is in Offset
        if (ImInfo->NumStrips == 1)     
          ImInfo->StripLengths[0] = Entry.Offset; 
        else { // The strip offsets are stored later in the file
          FilePos = ftell(fp);   // Remember where the file is
          // Skip ahead to the list of strip bytes. This
          // routine can read long or word strip lengths.
          fseek(fp, Entry.Offset, SEEK_SET);
          if (Entry.DataType == TIFFLONG)
            for (j=0; j<ImInfo->NumStrips; j++)
              ReadULong(fp, &ImInfo->StripLengths[j]);
          else {
            for (j=0; j<ImInfo->NumStrips; j++) {
              ReadWord(fp, &Val);
              ImInfo->StripLengths[j] = Val;
            }
          }
          // After reading the strip lengths, go back to the
          // last tag read
          fseek(fp, FilePos, SEEK_SET);
        }
        break;
      default: break;  // Ignore the other tags
    }
  }
  return 1;
}

//////////////////////////  ReadStrips  
//
// Reads the image's strips in the file. Use an 8K buffer.
// If the strip is bigger than the buffer, do multiple reads.
//
int HTiffInternal::ReadStrips(FILE *fp, TIFFIMAGEINFO *ImInfo, unsigned char  *Im)
{
  unsigned int i, j, k, NumPieces, MaxStripLen=8192;
  unsigned int p;
  unsigned char *Buffer;

  // Allocate memory to hold the buffer
  Buffer = (unsigned char *)malloc(MaxStripLen);
  if (Buffer == 0) return OUTOFMEMORY;

  // There should be a four byte NULL after the tag entries, but
  // we'll skip it and go straight to the image. Read the image
  // strip by strip.
  p = 0;
  for (j=0; (signed int)j<ImInfo->NumStrips; j++) {
    // Go to where the stip begins
    fseek(fp, ImInfo->StripOffsets[j], SEEK_SET);
    // Calculate how many times the 8k buffer must be used used
    // to read the whole strip 
    NumPieces = ImInfo->StripLengths[j] / MaxStripLen;
    for (i=0; i<NumPieces; i++) {
      if (fread(Buffer, 1, MaxStripLen, fp) != MaxStripLen)
        break;
      for (k=0; k<MaxStripLen; k++, p++)
        Im[p] = Buffer[k];   // Copy the strip to the image
    }
    // Read any remaining bytes in the strip
    NumPieces = (unsigned int)
      (ImInfo->StripLengths[j] % MaxStripLen);
    if (NumPieces != 0) {
      if (fread(Buffer, 1, NumPieces, fp) != NumPieces) break;
      for (i=0; i<NumPieces; i++, p++)
        Im[p] = Buffer[i];   // Copy the strip to the image
    }
  }
  free(Buffer);
  return 1;
}

//////////////////////  ReadGrayTIFFImage   
//
// Reads a grayscale image from a TIFF file. The Im array
// must be large enough to hold the image. Call GetTIFFImageInfo
// to retrieve the size of the image so that you can allocate
// memory for it.
//
int HTiffInternal::ReadGrayTIFFImage(FILE *fp, unsigned char  *Im)
{
  unsigned long FileOffs;     // Running offset in file
  TIFFIMAGEINFO ImInfo;
  int Err;

  // Read the fixed header
  if ((Err=ReadFxdHdr(fp, &FileOffs)) != 1)
    return Err;

  // Copy the information in the tags to the ImInfo structure
  if ((Err=ReadTags(fp, &ImInfo)) != 1)
    return Err;

  // Check whether you are reading the correct image type
  if (ImInfo.BitsPerSample != 8 ||
      ImInfo.Compression != NOCOMPRESSION ||
      ImInfo.SamplesPerPixel != 1) {
    Err = TIFFFORMATNOTSUPPORTED;
  }
  else
    Err = ReadStrips(fp, &ImInfo, Im);   // Read the strips
  free(ImInfo.StripOffsets);
  free(ImInfo.StripLengths);
  return Err;
}

///////////////////////  ReadRGBTIFFImage 
//
// Reads an RGB image from a TIFF file. Call GetTIFFImageInfo
// first to get the size of the image so that you can allocate
// memory for it.
//
int HTiffInternal::ReadRGBTIFFImage(FILE *fp, unsigned char  *Im)
{
  unsigned long FileOffs;      // Running offset in file
  TIFFIMAGEINFO ImInfo;
  int Err;

  // Read the fixed header
  if ((Err=ReadFxdHdr(fp, &FileOffs)) != 1) 
    return Err;

  if ((Err=ReadTags(fp, &ImInfo)) != 1)  // Read each tag entry
    return Err;

  // Check whether you are reading the correct image type
  if (ImInfo.BitsPerSample != 8 ||
      ImInfo.Compression != NOCOMPRESSION ||
      ImInfo.SamplesPerPixel != 3) {
    Err = TIFFFORMATNOTSUPPORTED;
  }
  else
    Err = ReadStrips(fp, &ImInfo, Im);   // Read the strips
  free(ImInfo.StripOffsets);
  free(ImInfo.StripLengths);
  return Err;
}

//////////////////////  GetTIFFImageInfo   
//
// Reads the TIFF file's header to determine how many pixels are
// in the image. It also sets ImType to 1 if it's a grayscale
// image and 2 if it's an RGB image.
//
int HTiffInternal::GetTIFFImageInfo(FILE *fp, int *ImWd, int *ImHt, int *ImType)
{
  int Err;
  unsigned int i;
  unsigned short NumTags;         // The number of tags in the file
  TIFFTAGENTRY Entry;               // A tag entry
  unsigned long FileOffs;       // File offset

  // Read the fixed header
  if ((Err=ReadFxdHdr(fp, &FileOffs)) != 1)
    return Err;

  *ImWd = -1;   *ImHt = -1;   *ImType = -1;
  fseek(fp, FileOffs, SEEK_SET);
  ReadWord(fp, &NumTags);
  for (i=0; i<NumTags; i++) {
    ReadTag(fp, &Entry);          // Read one tag entry at a time
    switch(Entry.Tag) {
      case TGIMAGELENGTH:                   // Image length tag
        if ((Entry.DataType != TIFFSHORT &&
          Entry.DataType != TIFFLONG) || Entry.Length != 1)
          return TIFFFORMATNOTSUPPORTED;
        *ImHt = (short)Entry.Offset;
        break;
      case TGIMAGEWIDTH:                    // Image width tag
        if ((Entry.DataType != TIFFSHORT &&
          Entry.DataType != TIFFLONG) || Entry.Length != 1)
          return TIFFFORMATNOTSUPPORTED;
        *ImWd = (short)Entry.Offset;
        break;
      case TGPHOTOMETRICINTERPRETATION:     // Image type tag
        if (Entry.DataType != TIFFSHORT || Entry.Length != 1)
          return TIFFFORMATNOTSUPPORTED;
        *ImType = (short)Entry.Offset;
        break;
      default: break;  // Ignore the other tags
    }
  }
  if (*ImWd == -1 || *ImHt == -1 || *ImType == -1)
    // Didn't find all the basic information to read the file
    return TIFFFORMATNOTSUPPORTED;
  return 1;
}

///////////////////////  GetImageInfo   
//
// Retrieves the width, height, and image type of the image in
// a TIFF file. Returns 0 if it can't read the TIFF format.
//
int HTiffInternal::GetImageInfo(char *Path, int *ImWd, int *ImHt, int *ImType)
{
  FILE *fp;

  if ((fp=fopen(Path, "rb")) == 0)
    return 0;

  if (GetTIFFImageInfo(fp, ImWd, ImHt, ImType) != 1) {
    fclose(fp);
    return 0;
  }
  fclose(fp);
  return 1;
}

//////////////////////////  ReadImage   
//
// Primary, high-level routine to read an RGB or grayscale TIFF
// image. Call GetImageInfo first to get the size of the image
// so that you can properly allocate memory for it.
//
int HTiffInternal::ReadImage(char *Path, unsigned char  *Im)
{
  FILE *fp;
  int ImWd, ImHt, ImType, RetVal=1;

  if ((fp=fopen(Path, "rb")) == 0)
    return 0;

  if (GetTIFFImageInfo(fp, &ImWd, &ImHt, &ImType) < 0) {
    fclose(fp);
    return 0;
  }

  if (ImType == 1) {
    // The photometric interpretation field says that
    // this file is potentially a grayscale image
    if (ReadGrayTIFFImage(fp, Im) < 0)
      RetVal = 0;
  }
  else if (ImType == 2) {
    // This file is an RGB image
    if (ReadRGBTIFFImage(fp, Im) <= 0)
      RetVal = 0;
    return RetVal;
  }
  else
    RetVal = 0;;  // Image type not supported
  fclose(fp);
  return RetVal;
}

//////////////////////////  WriteTag   
//
// Writes a single tag to the output file. It assumes that the
// file pointer is already pointing to the location where the
// tag is to be placed.  is_offset indicates whether the value/offset
// field is supposed to store a data value, or if it is an offset to 
// data elsewhere in the file.
//
int HTiffInternal::WriteTag(FILE *fp, unsigned int Tag, unsigned int DataType,
  unsigned long Len, unsigned long Offs, int is_offset)
{

  unsigned short tag, type;
  unsigned long length, long_offset;

  tag = Tag;
  type = DataType;
  length = Len;
  long_offset = Offs;

  fwrite((const void*)&tag, 2, 1, fp);  // Write the tag (2 bytes)
  fwrite((const void*)&type, 2, 1, fp);  // Write the type (2 bytes)
  fwrite((const void*)&length, 4, 1, fp); // Write the length (4 bytes)

  // if the type is short, and the value/offset is supposed to be a value
  // then put the value in the first 2 bytes with zeroes for the last 2 bytes.
  // if the type is long (or anything else), just put the 4 bytes here.
  // if the type is short, and the value/offset is an offset, put the offset
  // in the last two bytes (just write it as a long).
  if(DataType == TIFFSHORT){
    if(is_offset){
      fwrite((const void*)&long_offset, 4, 1, fp);  // Write the offset
	}
	else{
#if MVO_BIGENDIAN
	  long_offset = long_offset << 16;	// shift left 2 bytes, so the value is in the first 2 bytes
#endif
      fwrite((const void*)&long_offset, 4, 1, fp);  // Write the value
	}
  }
  else{
    fwrite((const void*)&long_offset, 4, 1, fp);  // Write the value/offset
  }

  return 1;
}
/////////////////////////  WriteFxdHdr   
//
// Writes the 8-byte fixed header to the top of a file
//
int HTiffInternal::WriteFxdHdr(FILE *fp)
{
  TIFFHEADER TIFFHdr;

 
#if MVO_BIGENDIAN
  TIFFHdr.ByteOrder = 0x4d4d;
#else
  TIFFHdr.ByteOrder = INTELBYTES;
#endif

  TIFFHdr.Version = TIFFVERSION;
  // Start IFD after TIFF header
  TIFFHdr.Offset = sizeof(TIFFHEADER);

  fwrite(&TIFFHdr, sizeof(TIFFHEADER), 1, fp); // Write header
  return 1;
}

//////////////////////  WriteRGBTIFFHeader   
//
//  Writes a header for a 24-bit, RGB image
//
int HTiffInternal::WriteRGBTIFFHeader(FILE *fp, unsigned long ImWd,
  unsigned long ImHt, unsigned long StripSize)
{
  unsigned long FileOffs;    // Running offset in file
  unsigned long NextIFD;     // Pointer to next IFD
  unsigned long StartOfStrip;
  unsigned long Numerator = 75L;  // 600 dots per inch
  unsigned long Denominator = 1L;
  short NumTagEntries = 14;    // 14 tag entries for the file
  unsigned long StripsPerImage, i;
  unsigned long LastStripLen;
  unsigned int RowsPerStrip;
  unsigned short Val;
  unsigned long Size;

  RowsPerStrip = (unsigned int)(StripSize / (ImWd * 3));
  if (RowsPerStrip == 0) {   // A strip can't be smaller
    return 0;                // than a row
  }
  Size = ImWd * ImHt * 3L;
  //StripsPerImage = (unsigned int)(Size / StripSize);
  //if (Size % StripSize != 0) StripsPerImage++;
  StripsPerImage = (unsigned long)(Size / StripSize + Size % StripSize);

  WriteFxdHdr(fp);

  FileOffs = sizeof(TIFFHEADER);
  // Build the Image File Directory (IFD) as a list of tag
  // entries. FileOffs is initially set to the location after
  // the tags. This calculation accounts for the 8 byte TIFF
  // header, the 2 bytes that specify the number of tag entries,
  // the tag entries themselves, and a four byte null terminator
  // at the end of the IFD.
  FileOffs += sizeof(short) + sizeof(long) +
             NumTagEntries * sizeof(TIFFTAGENTRY);
  // Write the number of tag entries
  fwrite(&NumTagEntries, sizeof(short), 1, fp);
  // Append the tag entries to the file. These are organized in
  // ascending order.
  WriteTag(fp, TGNEWSUBFILETYPE, TIFFLONG, 1L, 0L, 0);

  WriteTag(fp, TGIMAGEWIDTH, TIFFSHORT, 1L, ImWd, 0);

  WriteTag(fp, TGIMAGELENGTH, TIFFSHORT, 1L, ImHt, 0);

  // The three RGB bytes are saved with 8 bits each
  WriteTag(fp, TGBITSPERSAMPLE, TIFFSHORT, 3L, FileOffs, 1);
  // Update location of next free location in file
  FileOffs += 3L * sizeof(short);

  // A value of 1 signals that no compression is used
  WriteTag(fp, TGCOMPRESSION, TIFFSHORT, 1L, 1L, 0);

  // Pixels are stored as consecutive RGB values
  WriteTag(fp, TGPHOTOMETRICINTERPRETATION, TIFFSHORT, 1L, 2L, 0);

  // Save the file offsets for each image strip later in the
  // file. This assumes that there is more than one strip.
  // If the image fits into one strip, you'll need to change
  // this so that it saves the strip offset in the Offset
  // field of the tag entry structure.
  WriteTag(fp, TGSTRIPOFFSETS, TIFFLONG, StripsPerImage,
                 FileOffs + 4L * sizeof(unsigned long) +
                 StripsPerImage * sizeof(unsigned long), 1);
  WriteTag(fp, TGSAMPLESPERPIXEL, TIFFSHORT, 1L, 3L, 0);

  WriteTag(fp, TGROWSPERSTRIP, TIFFLONG, 1L, RowsPerStrip, 0);

  // Save the image strip lengths later in the file. This
  // assumes that there is more than one strip. If there isn't
  // you'll need to save the strip in the Offset field of the tag.
  WriteTag(fp, TGSTRIPBYTECOUNTS, TIFFLONG, StripsPerImage,
    FileOffs+4L*sizeof(unsigned long), 0);

  WriteTag(fp, TGXRESOLUTION, TIFFRATIONAL, 1L, FileOffs, 1);
  FileOffs += sizeof(unsigned long) * 2L;

  WriteTag(fp, TGYRESOLUTION, TIFFRATIONAL, 1L, FileOffs, 1);
  FileOffs += sizeof(unsigned long) * 2L;

  // The image data is stored as RGBRGBRGB...
  WriteTag(fp, TGPLANARCONFIGURATION, TIFFSHORT, 1L, 1L, 0);

  WriteTag(fp, TGRESOLUTIONUNIT, TIFFSHORT, 1L, 2L, 0);

  NextIFD = 0L;  // There aren't any more tags. Write four zeros.
  fwrite(&NextIFD, sizeof(unsigned long), 1, fp);

  // Write the sizes of the RGB samples that the bits per sample
  // tag was set to point to
  Val = 8;
  fwrite(&Val, sizeof(short), 1, fp);
  fwrite(&Val, sizeof(short), 1, fp);
  fwrite(&Val, sizeof(short), 1, fp);

  // Write the XRESOLUTION value. It's a rational number which
  // consists of two unsigned longs: a numerator and denominator.
  fwrite(&Numerator, sizeof(unsigned long), 1, fp);
  fwrite(&Denominator, sizeof(unsigned long), 1, fp);

  // Now write the YRESOLUTION rational number
  fwrite(&Numerator, sizeof(unsigned long), 1, fp);
  fwrite(&Denominator, sizeof(unsigned long), 1, fp);

  // Next write the sizes of the image strips. The strip lengths
  // are stored as unsigned longs. Handle the last strip as a
  // special case. It may not be as long as the others.
  LastStripLen = (ImWd * ImHt * 3L) -
     (StripSize * ((unsigned long)StripsPerImage-1));
  if (LastStripLen == 0) {
    // If LastStripLen is 0, then StripSize evenly divides
    // into the image, so that all strips will be the same length
    LastStripLen = StripSize;
  }
  // Write lengths of each strip
  for (i=0; i<StripsPerImage-1; i++)
    fwrite(&StripSize, sizeof(unsigned long), 1, fp);
  // Now add in last strip length
  fwrite(&LastStripLen, sizeof(unsigned long), 1, fp);
  // Add in strip lengths from above to the file offset
  FileOffs += sizeof(unsigned long) * StripsPerImage;

  // Calculate where the image strips will start in the file
  StartOfStrip = FileOffs + sizeof(unsigned long) * StripsPerImage;

  // First image strip starts at FileOffs, next strip starts
  // at StartOfStrip+StripSize, and so on
  for (i=0; i<StripsPerImage; i++) {
    fwrite(&StartOfStrip, sizeof(unsigned long), 1, fp);
    StartOfStrip += StripSize;
  }
  return 1;
}

////////////////////  WriteGrayTIFFHeader   
//
// Writes a TIFF header in preparation for storing a grayscale
// image. StripSize should be at least large enough to hold
// a single image row.
//
int HTiffInternal::WriteGrayTIFFHeader(FILE *fp, unsigned long ImWd,
  unsigned long ImHt, unsigned long StripSize)
{
  unsigned long FileOffs;          // Running offset in file
  unsigned long NextIFD;           // Pointer to next IFD
  unsigned long StartOfStrip;
  unsigned long Numerator = 75L;   // Display at 75 dots
  unsigned long Denominator = 1L;  // per inch
  int NumTagEntries = 14;          // 14 tag entries in file
  unsigned int StripsPerImage, i;
  unsigned long LastStripLen;
  unsigned int RowsPerStrip;
  unsigned long Size;

  RowsPerStrip = (unsigned int)(StripSize / ImWd * 3);
  if (RowsPerStrip == 0) {   // A strip can't be smaller
    return 0;                // than a row
  }
  Size = ImWd * ImHt;
  //StripsPerImage = (unsigned int)(Size / StripSize);
  //if (Size % StripSize != 0) StripsPerImage++;
  StripsPerImage = (unsigned int)(Size / StripSize + Size % StripSize);

  WriteFxdHdr(fp);
  FileOffs = sizeof(TIFFHEADER);

  // Build the Image File Directory (IFD) as a list of tag
  // entries. FileOffs is initially set to the location after
  // the tags. This calculation accounts for the 8 byte TIFF
  // header, the 2 bytes that specify the number of tag entries,
  // the tag entries themselves, and a four byte null terminator
  // at the end of the IFD.
  FileOffs += sizeof(short) + sizeof(long) +
             NumTagEntries * sizeof(TIFFTAGENTRY);

  // Write the number of tag entries
  fwrite(&NumTagEntries, sizeof(short), 1, fp);
  // Append the tag entries to the file
  WriteTag(fp, TGNEWSUBFILETYPE, TIFFLONG, 1L, 0L, 0);

  WriteTag(fp, TGIMAGEWIDTH, TIFFSHORT, 1L, ImWd, 0);

  WriteTag(fp, TGIMAGELENGTH, TIFFSHORT, 1L, ImHt, 0);

  WriteTag(fp, TGBITSPERSAMPLE, TIFFSHORT, 1L, 8L, 0);
  // No compression
  WriteTag(fp, TGCOMPRESSION, TIFFSHORT, 1L, 1L, 0);
  // Set to grayscale format
  WriteTag(fp, TGPHOTOMETRICINTERPRETATION, TIFFSHORT, 1L, 1L, 0);
  // The strip offsets are stored later in the file
  WriteTag(fp, TGSTRIPOFFSETS, TIFFLONG, StripsPerImage,
    FileOffs + 4L * sizeof(unsigned long) +
    StripsPerImage * sizeof(unsigned long), 0);
  // Okay for grayscale and color palette images
  WriteTag(fp, TGSAMPLESPERPIXEL, TIFFSHORT, 1L, 1L, 0);

  WriteTag(fp, TGROWSPERSTRIP, TIFFLONG, 1L, RowsPerStrip, 0);
  // The strip lengths are saved later in the file
  WriteTag(fp, TGSTRIPBYTECOUNTS, TIFFLONG, StripsPerImage,
      FileOffs+4L*sizeof(unsigned long), 0);

  WriteTag(fp, TGXRESOLUTION, TIFFRATIONAL, 1L, FileOffs, 1);
  FileOffs += sizeof(unsigned long) * 2L;

  WriteTag(fp, TGYRESOLUTION, TIFFRATIONAL, 1L, FileOffs, 1);
  FileOffs += sizeof(unsigned long) * 2L;
  // Image data is stored on one contiguous plane
  WriteTag(fp, TGPLANARCONFIGURATION, TIFFSHORT, 1L, 1L, 0);
  // Use inch resolution
  WriteTag(fp, TGRESOLUTIONUNIT, TIFFSHORT, 1L, 2L, 0);

  NextIFD = 0L;  // There aren't any more IFDs
  fwrite(&NextIFD, sizeof(unsigned long), 1, fp);

  // Write out the values that were set aside by using
  // the offsets earlier. Write the XRESOLUTION rational
  // number, which consists of two unsigned longs.
  fwrite(&Numerator, sizeof(unsigned long), 1, fp);
  fwrite(&Denominator, sizeof(unsigned long), 1, fp);

  // Now write the YRESOLUTION rational number
  fwrite(&Numerator, sizeof(unsigned long), 1, fp);
  fwrite(&Denominator, sizeof(unsigned long), 1, fp);

  // Next write the sizes of the image strips. The strip lengths
  // are stored as unsigned longs. Handle the last strip as a
  // special case. It may not be as long as the others.
  LastStripLen = ((unsigned long)ImWd * (unsigned long)ImHt) -
     ((unsigned long)StripSize * (StripsPerImage-1));
  if (LastStripLen == 0) {
    // If LastStripLen is 0, then StripSize divides evenly into
    // the image and all strips will be the same length
    LastStripLen = StripSize;
  }
  // Write the lengths of each strip
  for (i=0; i<StripsPerImage-1; i++)
    fwrite(&StripSize, sizeof(unsigned long), 1, fp);
  fwrite(&LastStripLen, sizeof(unsigned long), 1, fp);
  // Add in strip lengths from above to the file offset
  FileOffs += sizeof(unsigned long) * StripsPerImage;

  // Update FileOffs which points to where the image data starts.
  // The image data will start immediately after a series of
  // strip offsets.
  StartOfStrip = FileOffs + sizeof(unsigned long) * StripsPerImage;

  // First image strip starts at FileOffs, next strip starts
  // at StartOfStrip+StripSize, and so on
  for (i=0; i<StripsPerImage; i++) {
    fwrite(&StartOfStrip, sizeof(unsigned long), 1, fp);
    StartOfStrip += StripSize;
  }
  return 1;
}

////////////////////////  SwapWordOrder   
//
// Swaps the two bytes in an 16-bit word
//
void HTiffInternal::SwapWordOrder(unsigned short *Word)
{
   unsigned char *Byte = (unsigned char *)Word;
   unsigned char Tmp;

   Tmp = Byte[1];
   Byte[1] = Byte[0];    // Move first byte to second
   Byte[0] = Tmp;        // Move second to first byte
}

////////////////////////  SwapLongOrder  
//
// Swaps the bytes in a 32-bit long integer
//
void HTiffInternal::SwapLongOrder(unsigned long *Long)
{
   unsigned char *Byte = (unsigned char *)Long;
   unsigned char Tmp;

   Tmp = Byte[3];
   Byte[3] = Byte[0];    // Move first byte to fourth
   Byte[0] = Tmp;        // Move fourth byte to first
   Tmp = Byte[2];
   Byte[2] = Byte[1];    // Move second byte to third
   Byte[1] = Tmp;        // Move third byte to second
}


//////////////////////////  ReadTag 
//
// Reads a tag entry. Swaps the bytes if the file was written
// using a non-Intel format.
//
int HTiffInternal::ReadTag(FILE *fp, TIFFTAGENTRY *Entry)
{
  size_t t = fread(Entry, sizeof(TIFFTAGENTRY), 1, fp); // Read tag
  if (t == 1) {            // If read operation was successful,
    if (!IntelOrdr) {      // swap the byte ordering if they
      SwapWordOrder(&Entry->Tag);        // were written with
      SwapWordOrder(&Entry->DataType);   // a non-Intel format
      SwapLongOrder(&Entry->Length);
      SwapLongOrder(&Entry->Offset);
      if (Entry->DataType == TIFFSHORT && Entry->Length == 1)
        // Take only the two most significant bytes
        Entry->Offset = Entry->Offset >> 16;
    }
    return 1;
  }
  return 0;
}

/////////////////////////  ReadWord  
//
// Reads a 16-bit word from a file. Swaps the bytes if the file
// was written using a non-Intel format.
//
int HTiffInternal::ReadWord(FILE *fp, unsigned short *Val)
{
  size_t t = fread(Val, sizeof(unsigned short), 1, fp); // Read tag
  if (t == 1) {            // If read operation was successful,
    if (!IntelOrdr)        // swap the byte ordering if the
      SwapWordOrder(Val);  // word was not written with an
    return 1;              // Intel machine
  }
  return 0;
}

//////////////////////////  ReadULong  
//
// Reads a 32-bit long value. Swaps the bytes if the file was
// written using a non-Intel format.
//
int HTiffInternal::ReadULong(FILE *fp, unsigned long *Val)
{
  size_t t = fread(Val, sizeof(unsigned long), 1, fp); // Read tag
  if (t == 1) {            // If read operation was successful,
    if (!IntelOrdr)        // swap the byte ordering if the
      SwapLongOrder(Val);  // word was not written with an
    return 1;              // Intel machine
  }
  return 0;
}



