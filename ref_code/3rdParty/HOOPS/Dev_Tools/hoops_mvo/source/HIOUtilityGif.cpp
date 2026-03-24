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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HIOUtilityGif.cpp,v 1.12 2008-08-20 14:35:38 reuben Exp $
//

// The Graphics Interchange Format(c) is the Copyright property of
// CompuServe Incorporated.  GIF(sm) is a Service Mark property of
// CompuServe Incorporated.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "HIOUtilityGif.h"
#include "HDB.h"


class HGifInternal {

public:

	/*
		GifToImage reads a GIF file into a raw HOOPS image
		\param filename The name of the GIF image
		\param imagename The name of the HOOPS image as it will be referenced internally.
		\param format A description of how the image data is packed.  See HC_Insert_Image.
		\param image_key The key to the HOOPS image.  Passed by reference.
		\return A Boolean value indicating success or failure.
	*/
	static bool GifToImage(const wchar_t *filename, HC_KEY *image_key, HC_KEY segment_key,const char *imagename,const char *format);

private:

	static void Show_Error (const char *message);

	static void * start_unpacking_from_file (FILE *fp, bool use_gif_format,int data_bit_size, int max_bits_per_code);
	static bool unpack_from_file (void *u_data,long num_bytes, unsigned char *out_buffer, long *bytes_unpacked);
	static void finish_unpacking_from_file(void	*u_data);

};


HFileInputResult HIOUtilityGif::FileInputToImageKey(const wchar_t * filename, HC_KEY * image_key, HC_KEY segment_key, HInputHandlerOptions * options)
{
	if(!filename) return InputBadFileName;
	if(!image_key || !segment_key) return InputFail;

	const char * image_format = 0;
	const char * image_name = 0;

	SetStartingInput((char*)H_UTF8(filename).encodedText());

	if(options && options->m_pImageFormat) 
		image_format = options->m_pImageFormat;
	else
		image_format = "rgb";

	if(options) 
		image_name = options->m_pImageName;

	bool result = HGifInternal::GifToImage(filename, image_key, segment_key, image_name, image_format);

	SetFinishedInput();

	if(result)
		return InputOK;
	else
		return InputFail;
}




#define	COLORMAP_DEPTH_FLAG	0X07
#define	INTERLACED_FLAG		0x40
#define	COLORMAP_FLAG		0X80

#define MAXIMUM_BLOCK_SIZE	256
#define MAXIMUM_COLORMAP_SIZE	256
#define	MAXIMUM_CODE_LENGTH	12
#define MAXIMUM_LEGAL_CODE	((1 << MAXIMUM_CODE_LENGTH) - 1)
#define NULL_CODE		-1

#define	RGB_MODE		1
#define MAPPED_MODE		2
#define	PACKED_MODE		3

#define	GLOBAL_HEADER_SIZE	13	 
#define LOCAL_HEADER_SIZE	10


#define NULL_CODE		-1
#define	FILE_BUFFER_SIZE	8192

// GIF utility datastructures and methods
typedef  struct list {
	int prefix, 
	suffix;
} LIST;

typedef  struct color {
	unsigned char   red;
	unsigned char   green;
	unsigned char   blue;
} COLOR;

typedef  struct global_header {
	char signature[6];                  /* Should be GIF87a */
	unsigned short  screen_width;       /* Size of saver's screen */
	unsigned short  screen_height;      /* Size of saver's screen */
	unsigned char   flags;              /* Global map, etc. */
	unsigned char   background_color;   /* Should be able to ignore */
	unsigned char   trailer;            /* Should always be 0 */
} GLOBAL_HEADER;

typedef  struct local_header {
	unsigned short  image_left;         /* Where to place the image */
	/* We ignore this. */
	unsigned short  image_top;          /* Where to place the image */
	/* We ignore this. */
	unsigned short  image_width;        /* Size of the image */
	unsigned short  image_height;       /* Size of the image */
	unsigned char   flags;              /* Local map, etc. */
	unsigned char   lzw_code_size;      /* Bits for lzw */
} LOCAL_HEADER;

typedef struct decoder_data {
	FILE    *fp;
	bool    failed;
	bool    use_gif_format;
	int     bits_left;
	int     bits_per_code;
	unsigned char   *gif_block_pos;
	unsigned char   *block_pos;
	unsigned char   *block_end;
	unsigned char   *raw_block;
	long    prev_code;
	unsigned int    clear_code;
	unsigned int    EOI_code;
	unsigned int    *prefix;
	unsigned char   *suffix;
	unsigned int    *length;
	unsigned int    highest_defined_code;
	unsigned long   code_mask;
	unsigned long   current_bits;
	long    total_unpacked_bytes;
	int     data_bit_size;
	int     max_bits_per_code;
	int     max_legal_code;
	long    leftover_data_length;
	unsigned char   *leftover_data;
	unsigned char   *leftover_place;
} DECODER_DATA;



void HGifInternal::Show_Error (const char *message) {
	//TODO some thing else here
    //fprintf (stderr, "\n\007%s\n", message);
}




bool HGifInternal::GifToImage(const wchar_t *filename, HC_KEY *image_key, HC_KEY segment_key, const char *imagename, const char *format)
{
	GLOBAL_HEADER	header;
	LOCAL_HEADER	local_header;
	
	unsigned char	*the_image;
	long		image_pos, image_size;
	
	float		float_colormap[MAXIMUM_COLORMAP_SIZE * 3];
	COLOR		colormap[MAXIMUM_COLORMAP_SIZE];
	unsigned char	colors_used[MAXIMUM_COLORMAP_SIZE], colors_remapped[MAXIMUM_COLORMAP_SIZE];
	int		colormap_size, color_count, items_read, color_mode;
	
	int	loop;
	
	unsigned char	raw_block[MAXIMUM_BLOCK_SIZE],
		*raw_pos,
		*parsed_pos,
		*parsed,
		chunk_type;
	FILE		*fp;
	void		*d_data;
	char		image_spec[MVO_SMALL_BUFFER_SIZE];
	
    /* Find out what the target image format is: */
	const char		*char_pos;
    parsed = (unsigned char *) malloc (strlen(format) + 1);
    parsed_pos = parsed;
	for (char_pos = format; *char_pos; char_pos++) {
		if (*char_pos >= 'A' && *char_pos <= 'Z') {
			*parsed_pos++ = (unsigned char)(*char_pos - 'A' + 'a');
		}
		else {
			if (*char_pos != ' ')
				*parsed_pos++ = (unsigned char)*char_pos;
		}
    }
    *parsed_pos = '\0';
    if (strcmp ((const char *)parsed, "rgb") == 0)
		color_mode = RGB_MODE;
    else if (strcmp ((const char *)parsed, "mapped8") == 0)
		color_mode = MAPPED_MODE;
    else if (strcmp ((const char *)parsed, "mapped8,packed") == 0) {
		color_mode = PACKED_MODE;
		for (loop = 0; loop < MVO_SMALL_BUFFER_SIZE; loop++) {
			colors_used[loop] = 0;
			colors_remapped[loop] = 0;
		}
		color_count = 0;
    }
    else {
		Show_Error ("Error: Illegal image format requested.\n");
		free (parsed);
		return 0L;
    }
    free (parsed);
	
    fp = wfopen (filename, L"rb");
    if (!fp) {
		Show_Error ("Error: could not open GIF file for reading.\n");
		return 0L;
    }
	
    items_read = (int) fread (raw_block, GLOBAL_HEADER_SIZE, 1, fp);
    if (items_read != 1) {
		Show_Error ("Error: could not read the GIF file header from.\n");
		fclose (fp);
		return 0L;
    }
	
    strncpy (header.signature, (const char *)raw_block, 6);
    raw_pos = raw_block + 6;
    if (strncmp (header.signature, "GIF", 3) != 0) {
		Show_Error ("Error: Corrupted GIF file (illegal header).\n");
		fclose (fp);
		return 0L;
    }
	
    header.screen_width   = (unsigned short)(*raw_pos++);
    header.screen_width  += (unsigned short)((*raw_pos++) << 8);
	
    header.screen_height  = (unsigned short)(*raw_pos++);
    header.screen_height += (unsigned short)((*raw_pos++) << 8);
	
    header.flags = *raw_pos++;
	
    if (header.flags & COLORMAP_FLAG) {
		colormap_size = 1L << ((header.flags & COLORMAP_DEPTH_FLAG) + 1);
    }
    else {
		colormap_size = 0;
    }
	
    header.background_color = *raw_pos++;
	
    header.trailer = *raw_pos++;
    if (header.trailer != 0) {
		Show_Error ("Error: Not a legal GIF file (bad trailer byte).\n");
		fclose (fp);
		return 0L;
    }
	
    items_read = (int) fread(	colormap, sizeof(COLOR) * colormap_size, 1, fp);
    if (items_read != 1) {
		Show_Error ("Error: Premature EOF reading colormap from GIF.\n");
		fclose (fp);
		return 0L;
    }
	
 	
    items_read = (int) fread ( &chunk_type, sizeof (unsigned char), 1, fp);
    if (items_read != 1) {
		Show_Error ("Error: Premature EOF in GIF file.\n");
		fclose (fp);
		return 0L;
    }
	
    if (chunk_type == ';') {
		Show_Error ("Error: No image present in GIF file.\n");
		fclose (fp);
		return 0L;
    }
    else if (chunk_type != ',') {
		Show_Error ("Error: A non-understood field found in GIF file.\n");
		fclose (fp);
		return 0L;
    }
	
    items_read = (int) fread (raw_block, LOCAL_HEADER_SIZE, 1, fp);
    if (items_read != 1) {
		Show_Error ("Error: Early EOF reading local header in GIF file.\n");
		fclose (fp);
		return 0L;
    }
	
    raw_pos = raw_block;
	
    local_header.image_left  = (unsigned short)(*raw_pos++);
    local_header.image_left += (unsigned short)((*raw_pos++) << 8);
	
    local_header.image_top   = (unsigned short)(*raw_pos++);
    local_header.image_top  += (unsigned short)((*raw_pos++) << 8);
	
    local_header.image_width   = (unsigned short)(*raw_pos++);
    local_header.image_width  += (unsigned short)((*raw_pos++) << 8);
	
    local_header.image_height  = (unsigned short)(*raw_pos++);
    local_header.image_height += (unsigned short)((*raw_pos++) << 8);
	
    image_size = local_header.image_width * local_header.image_height;
    if (color_mode == RGB_MODE) {
		the_image = (unsigned char *)
			malloc (sizeof(unsigned char) * image_size * 3);
    }
    else {
		the_image = (unsigned char *)
			malloc (sizeof(unsigned char) * image_size);
    }
    image_pos = 0;
	
    local_header.flags = *raw_pos++;
	
    if (local_header.flags & COLORMAP_FLAG) {
		colormap_size = 1L << ((header.flags & COLORMAP_DEPTH_FLAG) + 1);
		
		items_read = (int) fread(colormap,
			sizeof(COLOR) * colormap_size, 1, fp);
		if (items_read != 1) {
			Show_Error ("Error: Early EOF reading colormap from GIF file.\n");
			free (the_image);
			fclose (fp);
			return 0L;
		}
    }
	
    local_header.lzw_code_size = *raw_pos++;
	
 	
    d_data = start_unpacking_from_file(fp,1,local_header.lzw_code_size,12);
	
#ifdef USE_SMALL_CHUNKS
    for (loop = 0; loop < image_size; loop += 1) {
		unsigned char *ip;
		
		ip = the_image + loop;
		if (!unpack_from_file(d_data,1,ip,&image_pos)) {
			Show_Error ("Error: Corrupted image data unpacking GIF file.\n");
			free (the_image);
			fclose (fp);
			return 0;
		}
    }
#else
    if (!unpack_from_file (d_data, image_size, the_image, &image_pos)) {
		Show_Error ("Error: Corrupted image data unpacking GIF file.\n");
		free (the_image);
		fclose (fp);
		return 0;
    }
#endif
    finish_unpacking_from_file(d_data);
	image_pos = image_size;
	
 	
    if (image_pos > image_size) {
		Show_Error ("Error: Corrupted image data.\n");
		free (the_image);
		fclose (fp);
		return 0;
    }
    else if (image_pos < image_size) {
		if (color_mode == PACKED_MODE) {
			colors_used[0] = 1;
		}
		for (; image_pos < image_size; image_pos++)
			the_image[image_pos] = 0;
    }
	
    if (color_mode == PACKED_MODE) {
		color_count = 0;
		for (loop = 0; loop < colormap_size; loop++) {
			if (colors_used[loop] != 0) {
				colors_used[color_count] = (unsigned char)loop;
				colors_remapped[loop] = (unsigned char)color_count++;
			}
		}
		for (loop = 0; loop < image_size; loop++) {
			the_image[loop] = colors_remapped[the_image[loop]];
		}
		for (loop = 0; loop < color_count; loop++) {
			colormap[loop] = colormap[colors_used[loop]];
		}
		colormap_size = color_count;
    }
	
	HC_Open_Segment_By_Key(segment_key);

	if (color_mode == MAPPED_MODE || color_mode == PACKED_MODE) {
		for (loop = 0; loop < colormap_size; loop++) {
			float_colormap[loop * 3]     = colormap[loop].red   / 255.0f;
			float_colormap[loop * 3 + 1] = colormap[loop].green / 255.0f;
			float_colormap[loop * 3 + 2] = colormap[loop].blue  / 255.0f;
		}
		HC_Set_Color_Map_By_Value ("RGB",colormap_size,float_colormap);
		if (imagename) {
			sprintf(image_spec, "mapped 8, name = %s", imagename);
		}
		else {
			sprintf(image_spec, "mapped 8");
		}
		*image_key = HC_KInsert_Image (0.0,0.0,0.0, image_spec,
			local_header.image_width, local_header.image_height,
			the_image);
	}
	else {
		/* Color_mode == RGB_MODE */
		for (loop = image_size - 1; loop >= 0; loop--) {
			the_image[loop * 3    ] = colormap[the_image[loop]].red;
			the_image[loop * 3 + 1] = colormap[the_image[loop]].green;
			the_image[loop * 3 + 2] = colormap[the_image[loop]].blue;
		}
		if (imagename) {
			sprintf(image_spec, "rgb, name = %s", imagename);
		}
		else {
			sprintf(image_spec, "rgb");
		}
		*image_key = HC_KInsert_Image (0.0,0.0,0.0, image_spec,
			local_header.image_width, local_header.image_height,
			the_image);
	}

	HC_Close_Segment();
	
    free (the_image);
    fclose (fp);
	return (true);
}


void * HGifInternal::start_unpacking_from_file (FILE *fp, bool use_gif_format,int data_bit_size, int		max_bits_per_code) {
    DECODER_DATA	*data;
    int		loop;
	
    data = (DECODER_DATA *) malloc (sizeof(DECODER_DATA));
    if (data == (DECODER_DATA *) 0) {
		return (void *) 0;
    }
	
    data->fp = fp;
    data->failed = false;
    data->use_gif_format = use_gif_format;
    data->data_bit_size = data_bit_size;
    data->max_bits_per_code = max_bits_per_code;
    data->max_legal_code = (1 << max_bits_per_code) - 1;
	
    data->prefix = (unsigned int *)
		malloc(sizeof(unsigned int) * data->max_legal_code + 2+10000);
    if (data->prefix == (unsigned int *) 0) {
		return (void *) 0;
    }
    data->suffix = (unsigned char *)
		malloc(sizeof(unsigned char) * data->max_legal_code + 2+10000);
    if (data->suffix == (unsigned char *) 0) {
		free (data->prefix);
		return (void *) 0;
    }
    data->length = (unsigned int *)
		malloc(sizeof(unsigned int) * data->max_legal_code + 2+10000);
    if (data->length == (unsigned int *) 0) {
		free (data->prefix);
		free (data->suffix);
		return (void *) 0;
    }
    data->raw_block = (unsigned char *)
		malloc(sizeof(unsigned char) * FILE_BUFFER_SIZE);
    if (data->raw_block == (unsigned char *) 0) {
		free (data->prefix);
		free (data->suffix);
		free (data->length);
		return (void *) 0;
    }
    data->leftover_data = (unsigned char *) malloc (data->max_legal_code + 2);
    if (data->leftover_data == (unsigned char *) 0) {
		free (data->prefix);
		free (data->suffix);
		free (data->length);
		free (data->raw_block);
		return (void *) 0;
    }
	
    data->prev_code	= NULL_CODE;
    data->clear_code	= 1 << data_bit_size;
    data->EOI_code	= data->clear_code + 1;
    data->highest_defined_code = data->EOI_code;
    data->bits_per_code = data_bit_size + 1;
    data->code_mask	= (1 << data->bits_per_code) - 1;
    data->current_bits	= 0;
    data->bits_left	= 0;
    data->gif_block_pos	= (unsigned char *) 0;
    data->block_pos	= (unsigned char *) 0;
    data->block_end	= (unsigned char *) 0;
    data->total_unpacked_bytes = 0;
    data->leftover_data_length = 0;
    data->leftover_place = data->leftover_data;
    for (loop = 0; loop < (int)data->clear_code; loop++) {
		data->length[loop] = 0;
    }
	
    return ((void *) data);
}

void HGifInternal::finish_unpacking_from_file(void	*u_data) {
	DECODER_DATA	*data;
	
    data = (DECODER_DATA *) u_data;
    free (data->prefix);
    free (data->suffix);
    free (data->length);
    free (data->raw_block);
    free (data->leftover_data);
    free (data);
}

bool HGifInternal::unpack_from_file (void *u_data,long num_bytes, unsigned char	*out_buffer, long		*bytes_unpacked) {
	DECODER_DATA	*data;
	long		unpacked_bytes;
    register	int		bits_left;
    register	int		bits_per_code;
    bool		use_gif_format;
    unsigned char	*gif_block_pos;
	unsigned char	*block_pos;
	unsigned char	*block_end;
	long		items_read;
	unsigned char	*raw_block;
	unsigned long	current_bits;
	unsigned int	this_code;
	unsigned long	code_mask;
    register	long		prev_code;
    register	unsigned int	temp_code;
    register	unsigned int	*prefix;
    register	unsigned char	*suffix;
    register	unsigned int	*length;
	unsigned int	saved_suffix;
	unsigned int	clear_code;
	unsigned int	EOI_code;
    register	unsigned char	*out_buffer_pos;
	unsigned char	*new_buffer_pos;
	unsigned int	highest_defined_code;
	int		max_legal_code;
	unsigned char	*leftover_data;
	
    data = (DECODER_DATA *) u_data;
	
    out_buffer_pos = out_buffer;
    unpacked_bytes = 0;
	
    if (data->failed == true) {
		*bytes_unpacked = 0;
		return false;
    }
	
    /* First use up any decompressed data that was leftover from the previous
    ** call to decompress.
    */
    leftover_data = data->leftover_data;
    if (data->leftover_data_length > 0) {
		register	unsigned char	*leftover_data_pos;
		register	unsigned char	*end_pos;
		
		leftover_data_pos = data->leftover_place;
		if (data->leftover_data_length <= num_bytes) {
			end_pos = leftover_data_pos + data->leftover_data_length;
			unpacked_bytes = data->leftover_data_length;
			data->leftover_data_length = 0;
			data->leftover_place = leftover_data;
		}
		else {
			end_pos = leftover_data_pos + num_bytes;
			data->leftover_data_length -= num_bytes;
			data->leftover_place = end_pos;
			unpacked_bytes = num_bytes;
		}
		
		do {
			*out_buffer_pos++ = *leftover_data_pos++;
		} while (leftover_data_pos < end_pos);
		
		if (unpacked_bytes == num_bytes) {
			leftover_data_pos = leftover_data;
			end_pos = leftover_data + num_bytes + data->leftover_data_length;
			*bytes_unpacked = unpacked_bytes;
			data->total_unpacked_bytes += unpacked_bytes;
			return true;
		}
    } /* if (there was leftover decompressed data) */
	
	
    /* Get rid of the de-referencing so that we go faster in the big loop */
    bits_left		= data->bits_left;
    bits_per_code	= data->bits_per_code;
    use_gif_format	= data->use_gif_format;
    gif_block_pos	= data->gif_block_pos;
    block_pos		= data->block_pos;
    block_end		= data->block_end;
    raw_block		= data->raw_block;
    prev_code		= data->prev_code;
    clear_code		= data->clear_code;
    EOI_code		= data->EOI_code;
    prefix		= data->prefix;
    suffix		= data->suffix;
    length		= data->length;
    highest_defined_code= data->highest_defined_code;
    code_mask		= data->code_mask;
    current_bits	= data->current_bits;
    max_legal_code	= data->max_legal_code;
	
    for (;;) {
	/* Assemble the next code.
	** This may involve reading a new block of data from the file,
	** pulling a few bytes out of the block, shifting bits, and masking
	** out the non-interesting part.
		*/
		while (bits_left < bits_per_code) {
			/* We need to get another byte from the buffer */
			
			/* Check to see if the big buffer is empty.	*/
			if (use_gif_format) {
			/* Check to see if the next byte is a GIF block count.
			** If so, we need to skip over it, and note where the
			** next block count byte will be.
				*/
				if (gif_block_pos == block_pos) {
					/* This byte is the GIF block count */
					/* But make sure we haven't gone off the end of the
					** big buffer.
					*/
					if (block_pos == block_end) {
						/* We went off the end of the bug buffer. */
						/* We need to read in a new big chunk of the
						** file into the big buffer, and re-check the
						** GIF block count then.
						** This happens below.
						*/
					}
					else {
						/* We didn't go off the end of the big buffer */
						
						/* See if this is the end of all GIF blocks */
						if (*block_pos == 0) {
						/* We return "success" in this case, even if we
						** didn't get the expected EOI_code since some
						** GIF files are terminated early, but still have
						** a good image.
							*/
							goto Success;
						}
						gif_block_pos += *block_pos++ + 1;
					} /* else (we didn't go off end of big buffer) */
				} /* if (current position is at a GIF block header) */
				
				/* Now see if our big buffer is empty */
				if (block_pos == block_end) {
					/* The big buffer is empty, get another chunk */
					
					items_read = (int) fread(raw_block, 1,FILE_BUFFER_SIZE, data->fp);
					
					/* Make sure we didn't hit the end of the file */
					if (items_read == 0) {
					/* This is an error condition, since we should
					** hit the EOI_code, not the end of the file
					** to terminate.
						*/
						goto Failed;
					}
					block_pos = raw_block;
					gif_block_pos = gif_block_pos - block_end + raw_block;
					block_end = block_pos + items_read;
					
					/* Now that we have a new big buffer, see if our current
					** position is at a GIF block count.  We checked for this
					** once already, but we need to do it again if we had
					** run out of data.
					*/
					if (gif_block_pos == block_pos) {
						/* This byte is the GIF block count */
						/* See if this is the end of all GIF blocks */
						if (*block_pos == 0) {
						/* We return "success" in this case, even if we
						** didn't get the expected EOI_code since some
						** GIF files are terminated early, but still have
						** a good image.
							*/
							goto Success;
						}
						gif_block_pos += *block_pos++ + 1;
					} /* if (we are at a GIF block count */
				} /* if (the big buffer was empty) */
				
			} /* if (using gif format) */
			else {
				/* Not using GIF format */
				if (block_pos == block_end) {
					/* The big buffer is empty, get another chunk */
					items_read = (int) fread(raw_block, 1, FILE_BUFFER_SIZE,data->fp);
					
					/* Make sure we didn't hit the end of the file */
					if (items_read == 0) {
					/* This is an error condition, since we should
					** hit the EOI_code, not the end of the file
					** to terminate.
						*/
						goto Failed;
					} /* if (we hit the end of the file early) */
					
					block_pos = raw_block;
					block_end = block_pos + items_read;
				} /* if (the big buffer was empty) */
			} /* else (not using GIF format) */
			
			current_bits += *block_pos++ << bits_left;
			bits_left += 8;
		} /* while (bits_left < bits_per_code) */
		
		this_code = current_bits & code_mask;
		current_bits >>= bits_per_code;
		bits_left -= bits_per_code;
		
 		
		if (this_code <= EOI_code) {
			if (this_code < clear_code) {
				unpacked_bytes++;
				if (unpacked_bytes > num_bytes) {
					data->leftover_data_length = 1;
					*leftover_data = (unsigned char)this_code;
					unpacked_bytes = num_bytes;
					saved_suffix = this_code;
					goto Put_in_table;
				}
				*out_buffer_pos++ = (unsigned char) this_code;
				saved_suffix = this_code;
			}
			else if (this_code == clear_code) {
				highest_defined_code = EOI_code;
				bits_per_code = data->data_bit_size + 1;
				code_mask = (1 << bits_per_code) - 1;
				prev_code = NULL_CODE;
				continue;
			}
			else {
				/* this_code must be the EOI_code */
				goto Success;
			}
		} /* if (this_code <= EOI_code) */
		else {
			/* this_code is > than EOI_code */
			
			if (this_code > highest_defined_code) {
				if (this_code > (highest_defined_code + 1) ) {
					goto Failed;
				}
				/* This code is not yet defined in the table,
				** which is *not* an error, it just means that the
				** definition of the code is based on the last character
				** we outputed.  The fact that the code is not defined in
				** the table gives a definition to the code (the definition
				** is based on the last code we got).
				*/
				
				unpacked_bytes += length[prev_code] + 2;
				temp_code = prev_code;
				
				if (unpacked_bytes > num_bytes) {
					unsigned char	*leftover_pos;
					unsigned char	*tail_leftover_pos;
					
					data->leftover_data_length = unpacked_bytes - num_bytes;
					tail_leftover_pos = leftover_data +
						data->leftover_data_length - 1;
					leftover_pos = tail_leftover_pos - 1;
					
 					
					while (leftover_pos >= leftover_data) {
						*leftover_pos-- = suffix[temp_code];
						temp_code	= prefix[temp_code];
					};
					unpacked_bytes = num_bytes;
					
					out_buffer_pos  = out_buffer + num_bytes - 1;
					
					while (temp_code > EOI_code) {
						*out_buffer_pos-- = suffix[temp_code];
						temp_code   = prefix[temp_code];
					}
					*out_buffer_pos = (unsigned char) temp_code;
					*tail_leftover_pos = (unsigned char)temp_code;
					saved_suffix = temp_code;
					goto Put_in_table;
				}
				
				out_buffer_pos += length[prev_code];
				new_buffer_pos  = out_buffer_pos + 1;
			} /* if (this_code > highest_defined_code) */
			else {
				/* this code is in the table */
				unpacked_bytes += length[this_code] + 1;
				temp_code = this_code;
				if (unpacked_bytes > num_bytes) {
					 	unsigned char	*leftover_pos;
					
					data->leftover_data_length = unpacked_bytes - num_bytes;
					leftover_pos =leftover_data + data->leftover_data_length -1;
					do {
						*leftover_pos-- = suffix[temp_code];
						temp_code = prefix[temp_code];
					} while (leftover_pos >= leftover_data);
					unpacked_bytes = num_bytes;
					
					out_buffer_pos  = out_buffer + num_bytes - 1;
					
					while (temp_code > EOI_code) {
						*out_buffer_pos-- = suffix[temp_code];
						temp_code   = prefix[temp_code];
					}
					*out_buffer_pos = (unsigned char) temp_code;
					saved_suffix = temp_code;
					goto Put_in_table;
				}
				out_buffer_pos += length[this_code];
				new_buffer_pos  = out_buffer_pos + 1;
			} /* else, (this code is in the table) */
			
			while (temp_code > EOI_code) {
				*out_buffer_pos-- = suffix[temp_code];
				temp_code   = prefix[temp_code];
			}
			
			*out_buffer_pos = (unsigned char) temp_code;
			if (this_code > highest_defined_code) {
				*new_buffer_pos++ = (unsigned char) temp_code;
			}
			out_buffer_pos = new_buffer_pos;
			saved_suffix = temp_code;
			
	} /* else, (this_code > EOI_code) */
	
Put_in_table:
	if (prev_code != NULL_CODE) {
		highest_defined_code++;
		
		/* The code length is adaptive.  If we have used every possible
		** code for the current code length, then an additional bit is
		** added to the code length.  There is a maximum allowed length.
		*/
		if (highest_defined_code >= code_mask) {
			if (bits_per_code < data->max_bits_per_code) {
				bits_per_code++;
				code_mask = (1 << bits_per_code) - 1;
			}
		}
		
		/* The encoder is *not* required to send a 'clear code'
		** when the table is full.  Instead the encoder can continue
		** to use the codes of the existing table.
		** In the case that the table is filled, we must not
		** add any new strings.
		*/
		if ((int)highest_defined_code <= max_legal_code) {
			prefix[highest_defined_code] = prev_code;
			length[highest_defined_code] = length[prev_code] + 1;
			suffix[highest_defined_code] = (unsigned char)saved_suffix;
		}
	}
	prev_code = this_code;
	if (unpacked_bytes == num_bytes)
		break;
    } /* For loop */
	
Success:
	
	*bytes_unpacked =	unpacked_bytes;
	data->total_unpacked_bytes += unpacked_bytes;
	data->bits_left =	bits_left;
	data->bits_per_code =	bits_per_code;
	data->gif_block_pos =	gif_block_pos;
	data->block_pos =	block_pos;
	data->block_end =	block_end;
	data->prev_code =	prev_code;
	data->highest_defined_code = highest_defined_code;
	data->code_mask =	code_mask;
	data->current_bits =	current_bits;
	return true;
	
Failed:
	*bytes_unpacked = unpacked_bytes;
	data->total_unpacked_bytes += unpacked_bytes;
	data->failed = true;
	return false;
}







