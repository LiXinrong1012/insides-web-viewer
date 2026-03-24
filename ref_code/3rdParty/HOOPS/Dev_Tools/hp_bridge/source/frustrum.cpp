/*=============================================================================

Code last modified : 12 October 1994 (integrated Vax/Unix example frustrum)
                      9 June    1995 (add NT code for filesystem detection)
		      7 April   1997 (change function prototypes)
		     10 April   1997 (add code for Partition xmt/rcv )
		     11 April   1997 (first attempt to support the Mac)
			 4 November 1997 ParaExplorer specific version
			19 November 1997 Heavy revision for ParaExplorer, i.e. rip out all the unneccesary crap
  
  This Software is proprietary to Electronic Data Systems Corporation.
  Copyright (c) 1997 Electronic Data Systems Corporation.
  This program is an unpublished work fully protected by the United States
  copyright laws and is considered a trade secret belonging to the copyright
  holder. All rights reserved.
  Restricted Rights Legend: Use, Duplication or Disclosure by the Government
  is Subject to Restrictions as Set Forth in Paragraph (c)(1)(ii) of the
  Rights in Technical Data and Computer Software Clause at DFARS 252.227-7013.

EDS assumes no responsibility for the use or reliability of this software;
the example frustrum is provided in order to run the Parasolid Acceptance
Tests and to give application writers access to a simple example of a working
Frustrum which will run on all Parasolid platforms.



//===========================================================================
                 #INCLUDES
=============================================================================*/



#include <frustrum_ifails.h>
#include <frustrum_tokens.h>
#include <parasolid_kernel.h>
#include <math.h>
#include <float.h>

#include "parafrustdefs.h"

#include "hp_map.h"
#include "hp_bridge.h"

#include "hc.h"
#include "utf_utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <wchar.h>

#ifdef _WIN32
#include <windows.h>
#endif


#ifdef _MSC_VER
#pragma warning(disable: 4127 4310 4244 4706 4206 4514 4100 4996 4702)
#endif

/*=============================================================================
                 #DEFINES
=============================================================================*/


/* determines whether information messages are printed */

#define trace_flag 0

#define PS_LONG_NAME  0
#define PS_SHORT_NAME 1

/* extra useful ifails */

#define  FR_not_started       FR_unspecified
#define  FR_internal_error    FR_unspecified


/* other useful definitions */

#define null_strid          (-1)
#define max_namelen         255         /* maximum length of a full pathname */
#define max_header_line (max_namelen+32) /* for long FILE=name in the header */
#define max_open_files      32

#define read_access         1
#define write_access        2
#define read_write_access   3

#define end_of_string_c     '\0'
#define end_of_string_s     "\0"
#define end_of_string_unicode_c     L'\0'
#define end_of_string_unicode_s     L"\0"

#define new_line_c          '\n'
#define new_line_s          "\n"

#define semi_colon_c        ';'
#define semi_colon_s        ";"
#define semi_colon_unicode_c        L';'
#define semi_colon_unicode_s        L";"

#ifdef _WIN32
#define dir_separator_c     '\\'
#define dir_separator_s     "\\"
#define dir_separator_unicode_c     L'\\'
#define dir_separator_unicode_s     L"\\"
#else
#ifdef macintosh
#define dir_separator_c     ':'
#define dir_separator_s     ":"
#else
#define dir_separator_c     '/'
#define dir_separator_s     "/"
#define dir_separator_unicode_c	L'/'
#define dir_separator_unicode_s L"/"
#endif
#endif

/*=============================================================================
                 MACROS
=============================================================================*/

#define trace_print \
    if (!trace_flag) /* skip */; else printf


#define HPK_VECTORS_SAME   1
#define HPK_VECTORS_OPPOSITE 2
#define HPK_VECTORS_OTHER 3

#define HP_PI				3.1415926535897932384626433832795

// MIN and MAX_COLORVALUE_KEY is a reserved range of keys just for color segments.
// they should be defined to be exactly 1,000,000 apart from each other.
// MAX_COLORVALUE_KEY + MIN_COLORVALUE_KEY should be less than the maximum range of 
// a long (range for key values) because of how circles are broken into 2 circular arcs
// and then renumbered.  Range for a long is -2,147,483,648 to 2,147,483,647.
//
// Above, I guess is no more valid. By Default now we insert a circle as one single
// ellipse - Rajesh B (15-Sept-03)
#define MIN_COLORVALUE_KEY 123456789
#define MAX_COLORVALUE_KEY 124456789
/*=============================================================================
                 STRUCTS
=============================================================================*/


/* one structure per open file containing info such as filename and
   the C stream id. the structures are chained together, accessed via
   the "open_files" variable
*/
typedef struct point {
    float	x, y, z;
} Point;

typedef struct file_s *file_p;

typedef struct file_s
{
  file_p next;
  file_p prev;
  int    strid;
  int    guise;
  int    format;
  int    access;
  char   name[max_namelen+1];
  char   key[max_namelen+1];
  FILE  *stream;
} file_t;

static file_p open_files = 0;

/* file stream identifiers and count of open files */
static int stream_id[max_open_files];
static int file_count = 0;

/* frustrum start count (0 not started) */
static int frustrum_started = 0;
/*=============================================================================
                 GLOBAL VARIABLES
=============================================================================*/

/* the following are for writing and checking file headers */

static char g_preamble_1[ max_header_line ] = end_of_string_s;
static char g_preamble_2[ max_header_line ] = end_of_string_s;
static char g_prefix_1[ max_header_line ] = "**PART1;\n";
static char g_prefix_2[ max_header_line ] = "**PART2;\n";
static char g_prefix_3[ max_header_line ] = "**PART3;\n";
static char g_trailer_start[ max_header_line ] = "**END_OF_HEADER";
static char g_trailer[ max_header_line ] = end_of_string_s;
static char g_unknown_value[] = "unknown";

/* machine specific: fopen file open modes. On NT platforms use binary */
/* mode to suppress the writing of carriage returns before line feeds  */

#define g_fopen_mode_read_text   "r"
#define g_fopen_mode_read_binary "rb"
#define g_fopen_mode_write       "wb"
#define g_fopen_mode_append      "wb+"

#ifndef _MSC_VER
#define __wchar_t wchar_t
#endif

#define g_fopen_mode_read_unicode_text   L"r"
#define g_fopen_mode_read_unicode_binary L"rb"
#define g_fopen_mode_write_unicode       L"wb"
#define g_fopen_mode_append_unicode      L"wb+"

/* this buffer used for input-output of file headers and text files */
static char *input_output_buffer = 0;
static size_t   input_output_buflen = 0;

//GH99
static int allocation_chunksize = 10000;				//this should avoid excessive reallocation
static unsigned int allocated_face_points = 0;
static unsigned int allocated_list_elts = 0;
static int segment_level = 0;
static float* face_points = 0;
static float* normals = 0;
static int* face_list = 0;
static int total_face_points = 0;
static int total_face_list_count = 0;
static int current_face_or_line_tag = -1;
static Point* min = 0;/* one corner of bounding box for all geometry */
static Point* max = 0;/* opposite corner of bounding box for all geometry */
static HC_KEY newly_opened_body_segment = 0;
static HC_KEY newly_opened_geom_segment = 0;

extern bool g_color_segment_mode;
extern bool g_body_segment_mode;
extern bool g_merge_faces_mode;
extern bool g_render_edges_mode;
extern bool g_tessellate_ellipses_mode; // not supported yet
extern bool g_render_faces_mode;
extern bool g_merge_bodies_mode;
extern bool g_no_mapping_mode;


extern HP_Map* g_pMap;// the mapping structure between HOOPS and Parasolid


// forward prototypes
static void open_body_segment( void );
static void close_body_segment( void );


/*=============================================================================
                 PROTOS
=============================================================================*/

extern "C" void FreeParaPartitions( void ); // from parafile.cpp

extern "C" DLLEXPORT	void FSTART( int *);
extern "C" DLLEXPORT	void FABORT( int *);
extern "C" DLLEXPORT	void FSTOP( int *);
extern "C" DLLEXPORT	void FMALLO( int *, char **, int *);
extern "C" DLLEXPORT	void FMFREE( int *, char **, int *);
extern "C" DLLEXPORT	void GOSGMT( const int *, const int *, const int *, const int *,
						const double *, const int *, const int *, int *);
extern "C" DLLEXPORT	void GOOPSG( const int *, const int *, const int *, const int *,
						const double *, const int *, const int *, int *);
extern "C" DLLEXPORT	void GOCLSG( const int *, const int *, const int *, const int *,
						const double *, const int *, const int *, int *);
extern "C" DLLEXPORT	void GOPIXL( const int *, const double *, const int *, const int *,
						int *);
extern "C" DLLEXPORT	void GOOPPX( const int *, const double *, const int *, const int *,
						int *);
extern "C" DLLEXPORT	void GOCLPX( const int *, const double *, const int *, const int *,
						int *);
extern "C" DLLEXPORT	void FFOPRD( const int *, const int *, const char *, const int *,
						const int *, int *, int *);
extern "C" DLLEXPORT	void FFOPWR( const int *, const int *, const char *, const int *,
						const char *, const int *, int *, int *);
extern "C" DLLEXPORT	void FFCLOS( const int *, const int *, const int *, int *);
extern "C" DLLEXPORT	void FFREAD( const int *, const int *, const int *, char *, int *,
						int *);
extern "C" DLLEXPORT	void FFWRIT( const int *, const int *, const int *, const char *,
						int *);
extern "C" DLLEXPORT	void FFOPRB( const int *, const int *, const int *, int *, int *,
						int *);
extern "C" DLLEXPORT	void FFSEEK( const int *, const int *, const int *, int *);
extern "C" DLLEXPORT	void FFTELL( const int *, const int *, int *, int *);
extern "C" DLLEXPORT	void FGCRCU( const char *, int *, int *, int *, int *, double *,
						int *, double *, int *);
extern "C" DLLEXPORT	void FGCRSU( const char *, int *, int *, int *, int *, double *,
						int *, double *, int *);
extern "C" DLLEXPORT	void FGEVCU( int *, double *, double *, double *, int *,
						double *, int *);
extern "C" DLLEXPORT	void FGEVSU( int *, double *, double *, double *, double *,
						int *, int *, int *, double *, int *);
extern "C" DLLEXPORT	void FGPRCU( int *, double *, double *, double *, int *, int *);
extern "C" DLLEXPORT	void FGPRSU( int *, double *, double *, double *, int *, int *);

extern "C" DLLEXPORT	int UCOPRD( const int  guise,    const int  format,
                              const PK_UCHAR_t name[],
                              const PK_LOGICAL_t skiphd,
                                    int *strid);
extern "C" DLLEXPORT	int UCOPWR( const int guise, const int format, const PK_UCHAR_t * name,
							   const char * pd2hdr, int *strid );
/* The schema path will be stored in an external global called schemaPath */
extern "C" void extend_schema_filename( char* filename );
/*=============================================================================
                 UTILITY FUNCTIONS
=============================================================================*/



/*
 *	This program reads a HOOPS metafile and searches it
 *	for polygons.  Polygons found are inserted into a
 *	Shell and then the Shell is optimized. The resulting
 *	optimized Shell is written to a new HOOPS metafile.
 *
 *	The program takes two arguments
 *	in-file and out-file
 */

  //it just so happens that point and vector are exactly alike
typedef struct point Vector; 

typedef struct SHELL_INFO_TAG {
   int point_list_len;
   Point *point_list;
   Vector *normal_list;
   int face_list_len;
   int *face_list;
} Shell_Info;

#define MAX_SEGMENT_NAME_LENGTH		1024
#define MAX_TYPE_NAME_LENGTH		32

  //temporary workspace
//char	child[ MAX_SEGMENT_NAME_LENGTH ];

/*******************************\
 * HELPER (recursive)
 * Shell_Search
 * Designed to be called from Segment_Allocate.
 * Finds how much memory necessary for the current and child segments' shells.
 * Fills two structures:
 *   total_info is designed to be big enough for all of the shells put together
 *   max_info should be big enough for the largest shell.
 * Note that only the lengths are valid after this call, not the actual lists.
\*******************************/
void Shell_Search( Shell_Info *total_info, Shell_Info *max_info )
{
   int		local_point_list_len;
   int		local_face_list_len;
   HC_KEY	key;
   int		num_shells = 0;
   char		type[ MAX_TYPE_NAME_LENGTH ];
	HC_KEY	child;


   HC_Begin_Contents_Search (".", "segment");
      while (HC_Find_Contents (type, &child) )
      {
         HC_Open_Segment_By_Key (child);

         Shell_Search( total_info, max_info );
         HC_Close_Segment();
      }
   HC_End_Contents_Search();

   HC_Begin_Contents_Search (".", "shells");
      HC_Show_Contents_Count (&num_shells);
      while (HC_Find_Contents (type, &key)) 
      {
         HC_Show_Shell_Size(key, &local_point_list_len, &local_face_list_len );
           // keep track of the totals
         total_info -> point_list_len += local_point_list_len;
         total_info -> face_list_len  += local_face_list_len;
           // keep track of the maximums
         if( max_info -> point_list_len < local_point_list_len )
            max_info -> point_list_len = local_point_list_len;
         if( max_info -> face_list_len < local_face_list_len )
            max_info -> face_list_len = local_face_list_len;
      }
   HC_End_Contents_Search ();

} // end function Shell_Search


/*******************************\
 * HELPER
 * Segment_Shell_Allocate
 * allocates memory for the current and child segments' shells.
 * Allocates two structures:
 *   total_info is designed to be big enough for all of the shells put together
 *   max_info should be big enough for the largest shell.
 * After the memory is allocated, the length fields are cleared.
 * returns 0 if the memory could not be allocated
\*******************************/
int Segment_Shell_Allocate( Shell_Info *total_info, Shell_Info *max_info )
{
   Shell_Search( total_info, max_info );
   
   max_info -> point_list = (Point *) 
		malloc ( max_info -> point_list_len * sizeof (Point) );
   max_info -> normal_list = (Vector *)
		malloc ( max_info -> point_list_len * sizeof (Vector) );
   max_info -> face_list  = (int *)   
		malloc ( max_info -> face_list_len * sizeof (int) );
   total_info -> point_list = (Point *) 
		malloc ( total_info -> point_list_len * sizeof (Point) );
   total_info -> normal_list = (Vector *)
		malloc ( total_info -> point_list_len * sizeof (Vector) );
   total_info -> face_list  = (int *)   
		malloc ( total_info -> face_list_len * sizeof (int) );

     // clear the lengths of the structures
   max_info -> point_list_len = 0;
   max_info -> face_list_len = 0;
   total_info -> point_list_len = 0;
   total_info -> face_list_len = 0;

     // return 0 if malloc returned 0 for any of the memory requests
   if(  (max_info -> point_list) &&
        (max_info -> face_list) &&
        (total_info -> point_list) &&
        (total_info -> face_list) )
       return 1;
   else
       return 0;

} /* end function Segment_Shell_Allocate */


/*******************************\
 * HELPER (recursive)
 * Recursive_Merge_Shells
 * This function assumes that the proper amount of memory has 
 *      been allocated (see Segment_Shell_Allocate)
 * Recursive_Merge steps through the child segments, and merges all of the
 *      shells into one.
 * XXX this routine leaves a lot of empty segments in their place.  Ideally,
 *      we would like to step through and delete them.  That will be the 
 *      next step.
\*******************************/
HC_KEY Recursive_Merge_Shells( Shell_Info *total_info, Shell_Info *max_info )
{
	int		local_point_list_len;
	int		local_face_list_len;
	int		polygon_length;
	int		i, j;
	char		type[ MAX_TYPE_NAME_LENGTH ];
	HC_KEY		returned_key = 0;
	HC_KEY		key = 0;
	Vector	*v;
	int		current_point_list_offset, current_face_list_offset;
	HC_KEY	child;

	//recursively find all of the child segments
	HC_Begin_Contents_Search (".","segment");
	while (HC_Find_Contents (type, &child) )
	{
 
		HC_Open_Segment_By_Key (child);
		returned_key = Recursive_Merge_Shells( total_info, max_info );
		HC_Close_Segment();
	}
	HC_End_Contents_Search();

	//after all of the children have been processed, process  current segment
	//  (i.e., a post-order tree traversal)
	HC_Begin_Contents_Search (".", "shells");
	while (HC_Find_Contents (type, &key)) 
	{
		if (!returned_key)
			returned_key = key;
         current_point_list_offset = total_info -> point_list_len;
	     current_face_list_offset  = total_info -> face_list_len;

           //use max_info for the scratch-space buffers, but
           //  write the lengths into local variables, just in case 
           //  we need the max lengths later on.
         HC_Show_Shell(
		key, 
		&(local_point_list_len), 
		max_info -> point_list, 
		&(local_face_list_len), 
		max_info -> face_list 
		);

           //copy the point and face list into the main face list
           //  For each individual shell, the point list originally started 
           //  at zero, but for the main list, it starts at 
           //  current_point_list_offset.  

           // here, we copy the point list
         for( i = 0 ; i < local_point_list_len ; i++ )
         {
            total_info -> point_list[ current_point_list_offset + i].x = 
				max_info -> point_list[i].x;
            total_info -> point_list[ current_point_list_offset + i].y = 
				max_info -> point_list[i].y;
            total_info -> point_list[ current_point_list_offset + i].z = 
				max_info -> point_list[i].z;
         }

           // here, we copy the face list
	 i = 0;
         while(i < local_face_list_len)
         {
              // in this loop:
              // main_face_list[current_face_list_offset]  
              //      is the start of the individual shell
              // main_face_list[current_face_list_offset + i]  
              //      is the start of the polygon inside the shell
              // main_face_list[current_face_list_offset + i + j]
              //      is the the point inside the polygon inside the shell
            
              // the face list is made up of polygon entries.  For each entry,
              //      the length comes first, then a number of data points
              //      equal to the length.
            polygon_length = max_info -> face_list[i];
              // hoops syntax: to subtract a polygon from a shell, use negative
              //      polygon length.  We account for this here with abs. val.
            if( polygon_length < 0 ) polygon_length = -polygon_length;
            total_info -> face_list[ i + current_face_list_offset ] =  
			max_info -> face_list[i];
            for( j = 1 ; j <= polygon_length ; j++ )
                 // remember, the point list was moved, so the face list 
                 // has to be modified as it is copied
               total_info -> face_list[ current_face_list_offset + i + j ] = 
                  max_info -> face_list[ i + j ] + current_point_list_offset;
            i += polygon_length + 1;

         } // end while ( i < local_face_list_len

         HC_Open_Geometry( key );
            for( i = 0 ; i < local_point_list_len ; i++ )
            {
               v = &(total_info -> normal_list[current_point_list_offset+i]);
               HC_Open_Vertex( i );
                  HC_Show_Net_Normal( &(v -> x), &(v -> y), &(v -> z) );
               HC_Close_Vertex();
            }
         HC_Close_Geometry();

           //update the current offsets and prepare to load the next shell.
         total_info -> point_list_len += local_point_list_len;
         total_info -> face_list_len  += local_face_list_len;

      } // end while ( HC_Find_Contents(...) )
   HC_End_Contents_Search ();

   HC_Flush_Contents (".", "shells");
	return returned_key;
} /* end function Recursive_Merge_Shells */


static int
is_extension_present_u(wchar_t* fullname)
{
	wchar_t *extn = wcsrchr( fullname, '.' );
	if (extn != NULL)  {
		wchar_t* extn2 = wcsrchr(extn, '\\');
		if (extn2 == NULL)
			return 1;
		else
			return 0;
	}
	else  {
 		return 0;
	}
}

#if 0
static int
is_extension_present(char* fullname)
{
	char *extn = strrchr( fullname, '.' );
	if (extn != NULL)  {
		char* extn2 = strrchr(extn, '\\');
		if (extn2 == NULL)
			return 1;
		else
			return 0;
	}
	else  {
 		return 0;
	}
}
#endif

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: format_string

History:

  May 1990 - reformatted for example frustrum code

Description:

  Returns a pointer to a lowercase string which declares the file format
  (binary or text). This is for writing into file headers.


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static char* format_string( int format )
    {
    static char ffbnry[] = "binary";
    static char fftext[] = "text";
    switch( format )
      {
      case FFBNRY:
        return ffbnry;
      case FFTEXT:
        return fftext;
      }
    return g_unknown_value;
    }


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: guise_string

History:

  May 1990 - reformatted for example frustrum code

Description:

  Returns a pointer to a lowercase string which declares the file guise
  (that is rollback, snapshot, journal, transmit, schema, licence).
  Romulus files do not have headers; guise FFCXMO is  not valid.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static char* guise_string( int guise )
    {
    static char ffcrol[] = "rollback";
    static char ffcsnp[] = "snapshot";
    static char ffcjnl[] = "journal";
    static char ffcxmt[] = "transmit";
    static char ffcsch[] = "schema";
    static char ffclnc[] = "licence";
    static char ffcxmp[] = "transmit_partition";
    static char ffcxmd[] = "transmit_deltas";
	static char ffcdbg[] = "debug_report";

    switch ( guise )
      {
      case FFCROL: return ffcrol;
      case FFCSNP: return ffcsnp;
      case FFCJNL: return ffcjnl;
      case FFCXMT: return ffcxmt;
      case FFCSCH: return ffcsch;
      case FFCLNC: return ffclnc;
      case FFCXMP: return ffcxmp;
      case FFCXMD: return ffcxmd;
	  case FFCDBG: return ffcdbg;
      }
    return g_unknown_value;
    }


#if 0	//  VC 8 complains about unused local functions
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: nt_short_filesystem

History:

  June  1995 - written

Description:

    machine specific (NT) function to check whether the device implied
    by the root portion of a path  E:\users\me\xx  or \\mc123\share\yy
    or the "currently selected device" implies a short name filesystem.

    ( i.e. should the frustrum use 3 or 7 character file extensions )

    In this implementation, we assume that a FAT (FileAllocationTable)
    filesystem will only support short 8.3 type names. This assumption
    is true for Win32S applications (IX86 only) and pre NT version 3.5
    and where the NT registry option  "Win32FileSystem"
        HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\FileSystem
        has been set explicitly to 1.

    The 'short_filesystem' feature is only relevant if your application
    is ported to IX86 and is required to run under Windows 3.1 / Win32S
    otherwise your application can just use 7 character file extensions

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

#ifdef _WIN32
static int nt_filesystem_type(char* pathname)
                    /* this can be a fully specified file or directory name */
                    /*    (only the first part of the pathname is examined) */
                    /* or it can be blank or null implying "current device" */
    {
    int default_return;
    int res;
    char *root_of_filesystem;
    char root_of_file_system_name[256];
    char filesystemtype[256];
    unsigned long maxnamelength;
    unsigned long filesystemtypelen;
#ifdef _M_IX86
    /* running on an I386 machine where FAT filesystems are more common */
    default_return = PS_SHORT_NAME;
#else
    /* running on AlphaNT/MipsNT where NTFS filesystems are more common */
    default_return = PS_LONG_NAME;
#endif
    res = default_return;
    root_of_filesystem = 0L;
    maxnamelength = (unsigned long) -1;
    filesystemtypelen = (unsigned long) 256;
    if (pathname != 0L && strlen( pathname ) > 0)
      {
      /* examine first few characters in pathname  */
      strcpy( root_of_file_system_name, pathname );
      if ( root_of_file_system_name[0] == dir_separator_c &&
           root_of_file_system_name[1] == dir_separator_c )
        {
        /* look for a UNC name of the form \\<node>\<share>\...         */
        /* constructed filesystem name must must include the trailing   */
        /* backslash after sharename see KnowledgeBase PSS ID Q119219   */
        int i;
        int len;
        int share_found = 0;
        len = (int) (strlen( root_of_file_system_name ));
        for ( i = 2 ; i < len && root_of_filesystem == 0L; i++ )
          {
          if ( root_of_file_system_name[i] == dir_separator_c )
            {
            if ( share_found )
              /* second single backslash marks end of share name  */
              {
              root_of_file_system_name[i + 1] = '\0';
              root_of_filesystem = root_of_file_system_name;
              }
            else
              share_found = 1;
            }
          }
        }
      else
        /* look for a name of form Z:\... or Z:...                      */
        {
        if (root_of_file_system_name[1] == ':')
          {
          /* assume root_of_file_system_name[0] contains drive letter */
          /* (trailing slash makes this a 'root' directory specifier) */
          root_of_file_system_name[2] = dir_separator_c;
          root_of_file_system_name[3] = '\0';
          root_of_filesystem = root_of_file_system_name;
          }
        }
      }

    if (GetVolumeInformation(root_of_filesystem,/* receive: system name     */
                             0L,                /* return : volume name     */
                             (unsigned long) 0,         /*                          */
                             0L,                /* return : no serial num   */
                             &maxnamelength,    /* return : name length     */
                             0L,                /* return : no system flags */
                             filesystemtype,    /* return : file system     */
                             filesystemtypelen) == 1 )
      /* GetVolumeInformation function is implemented in WIN32 and Win32S */
      /* so this function is always available. If the pathname is null or */
      /* it doesn't include any device information, GetVolumeInformation  */
      /* returns whether or not the current device is a FAT file system.  */
      /* (GetVolumeInformation returns zero if the device does not exist) */
      {
      if (strcmp( filesystemtype, "FAT" ) == 0)
        res = PS_LONG_NAME; //PS_SHORT_NAME;
      else if (maxnamelength <= 0)
        /* not sure (return default value)  */
        res = default_return;
      else
        {
        /* use maxnamelength to decide  (12 chars in name "abcdefgh.ijk") */
        if ( maxnamelength <= 12 )
          res = PS_SHORT_NAME;
        else
          res = PS_LONG_NAME;
        }
      }
    return res;
    }
#endif

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: filetype_guise_string

History:

  April 1995 - written
  June  1995 - added nt

Description:

  Returns a pointer to a filetype string for the specified guise.
  Used in the construction of filenames in FFOPRD, FFOPWR etc.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static char* filetype_guise_string( int guise, int filesystem  )
         /* filesystem should be set to PS_LONG_NAME  (most platforms) */
         /* or                          PS_SHORT_NAME  ( _WIN32 only ) */
    {
    /* machine specific: parts of file facetTypes for various guises */

    /* the following are only applicable to NT */
    static char nt_short_ffcsnp[] = ".N";
    static char nt_short_ffcjnl[] = ".J";
    static char nt_short_ffcxmt[] = ".X";
    static char nt_short_ffcsch[] = ".S";
    static char nt_short_ffclnc[] = ".L";
    static char nt_short_ffcxmo[] = ".XMT";
    static char nt_short_ffcxmp[] = ".P";
    static char nt_short_ffcxmd[] = ".D";

    /* the following are only applicable to the Macintosh */
#ifdef macintosh
    static char ffcsnp[] = " snp";
    static char ffcjnl[] = " jnl";
    static char ffcxmt[] = " xmt";
    static char ffcsch[] = " sch";
    static char ffclnc[] = " lnc";
    static char ffcxmo[] = " xmt";
    static char ffcxmp[] = " xmp";
    static char ffcxmd[] = " xmd";
#else
    static char ffcsnp[] = ".snp";
    static char ffcjnl[] = ".jnl";
    static char ffcxmt[] = ".xmt";
    static char ffcsch[] = ".sch";
    static char ffclnc[] = ".lnc";
    static char ffcxmo[] = ".xmt";
    static char ffcxmp[] = ".xmp";
    static char ffcxmd[] = ".xmd";
#endif

    switch( guise )
        {
        case FFCSNP:
            if ( filesystem == PS_SHORT_NAME ) return nt_short_ffcsnp;
            return ffcsnp;
        case FFCJNL:
            if ( filesystem == PS_SHORT_NAME ) return nt_short_ffcjnl;
            return ffcjnl;
        case FFCXMT:
            if ( filesystem == PS_SHORT_NAME ) return nt_short_ffcxmt;
            return ffcxmt;
        case FFCSCH:
            if ( filesystem == PS_SHORT_NAME ) return nt_short_ffcsch;
            return ffcsch;
        case FFCLNC:
            if ( filesystem == PS_SHORT_NAME ) return nt_short_ffclnc;
            return ffclnc;
        case FFCXMO:
            return ffcxmo;
        case FFCXMP:
            if ( filesystem == PS_SHORT_NAME ) return nt_short_ffcxmp;
            return ffcxmp;
        case FFCXMD:
            if ( filesystem == PS_SHORT_NAME ) return nt_short_ffcxmd;
            return ffcxmd;
        }

    return end_of_string_s;
    }

#endif		// VC 8 complains about unused local functions

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: filetype_guise_string_unicode

Description:

  Returns a pointer to a filetype string for the specified guise.
  Used in the construction of filenames in FFOPRD, FFOPWR etc.

  This is a unicode version of filetype_guise_string.
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static wchar_t const * filetype_guise_string_unicode( int guise )
	{
	// Here we are assuming 3 character extensions
    static wchar_t ffcsnp[] = L".N";
    static wchar_t ffcjnl[] = L".J";
    static wchar_t ffcxmt[] = L".X";
    static wchar_t ffcsch[] = L".S";
    static wchar_t ffclnc[] = L".L";
    static wchar_t ffcxmo[] = L".XMT";
    static wchar_t ffcxmp[] = L".P";
    static wchar_t ffcxmd[] = L".D";
	static wchar_t ffcdbg[] = L".XML";

    switch( guise )
        {
        case FFCSNP:
            return ffcsnp;
        case FFCJNL:
            return ffcjnl;
        case FFCXMT:
            return ffcxmt;
        case FFCSCH:
            return ffcsch;
        case FFCLNC:
            return ffclnc;
        case FFCXMO:
            return ffcxmo;
        case FFCXMP:
            return ffcxmp;
        case FFCXMD:
            return ffcxmd;
		case FFCDBG:
			return ffcdbg;
        }

    return end_of_string_unicode_s;
    }

#if 0	//VC 8 complains about unused local functions
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: filetype_format_string

History:

  April 1995 - written
  June  1995 - added nt

Description:

  Returns a pointer to a file format (text or binary) filetype string
  for the specified format.
  Used in the construction of filenames in FFOPRD, FFOPWR etc.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static char* filetype_format_string( int format, int filesystem )
    /* filesystem set to PS_LONG_NAME  (most platforms) */
    /* or                PS_SHORT_NAME  ( _WIN32 only ) */
    {
    /* machine specific: parts of file facetTypes for various formats */

    /* the following are only applicable to NT */
    static char nt_short_ffbnry[] = "_B";
    static char nt_short_fftext[] = "_T";

    static char ffbnry[] = "_bin";
    static char fftext[] = "_txt";

    switch ( format )
        {
        case FFBNRY:
            if ( filesystem == PS_SHORT_NAME )return nt_short_ffbnry;
            return ffbnry;
        case FFTEXT:
            if ( filesystem == PS_SHORT_NAME )return nt_short_fftext;
            return fftext;
        }

    return end_of_string_s;
    }

#endif		// VC 8 complains about unused local functions

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: filetype_format_unicode_string

Description:

  Returns a pointer to a file format (text or binary) filetype string
  for the specified format.
  Used in the construction of filenames in FFOPRD, FFOPWR etc.

  This is a unicode version of filetype_format_string.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static wchar_t const * filetype_format_unicode_string( int format )
	// Here we are assuming 3 character extensions
    {
    static wchar_t ffbnry[] = L"_B";
    static wchar_t fftext[] = L"_T";

    switch ( format )
        {
        case FFBNRY:
            return ffbnry;
        case FFTEXT:
            return fftext;
        }

    return end_of_string_unicode_s;
    }

#if 0		// VC 8 complains about unused local functions
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: filekey_string

History:

  May 1990 - reformatted for example frustrum code
  Oct 1994 - safer string copy

Description:

  Returns a pointer to a string which is a copy of the filename
  which was passed to FFOPRD/FFOPWR (before having any directory
  prefix or file extension added to it). This consists of appending
  a null character to the string.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static char* filekey_string( char* keynam, int keylen )
    {
    static char keyword_value[max_namelen+1];

    strncpy(keyword_value, keynam, keylen);
    keyword_value[keylen] = end_of_string_c;

    return keyword_value;
    }


#endif		// VC 8 complains about unused local functions

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: delete_file

History:

  May 1990 - reformatted for example frustrum code
  Oct 1994 - use remove() function on all platforms

Description:

  Deletes the named file.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static void delete_file( char* name, int* ifail )
    {
    if(remove( name ) != 0)
        {
        *ifail = FR_close_fail;
        }
    else
        *ifail = FR_no_errors;
    }

/*=============================================================================
                    FILE HANDLING FUNCTIONS
=============================================================================*/



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: new_open_file

History:

  May 1990 - reformatted for example frustrum code

Description:

  Allocates new structure, adds the file information and
  adds it to the list of open-file structures.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static void new_open_file( FILE* stream, int guise, int format, int access,
			   char* filename, char* keyname, file_p* file_ptr,
			   int* ifail )
    {
    file_p ptr;
    file_p temp = 0;
    int i;

    /* allocate and add file structure into list of open files */
    ptr = (file_p) malloc( sizeof( file_t ));
    if (ptr == 0)
      {
        fclose( stream );
        {
        *ifail = FR_open_fail;
        return;
        }
      }

    if (open_files == 0)
        open_files = ptr;
    else
      {
        for ( temp = open_files; temp->next != 0; temp = temp->next )
            /* skip */;
        temp->next = ptr;
      }

    /* initialise file structure */
    ptr->next = 0;
    if (open_files == ptr)
        ptr->prev = 0;
    else
        ptr->prev = temp;
    for ( i = 0; stream_id[i] != 0; i++ )
        /* skip */;

    stream_id[i] = i + 1;
    ptr->strid = i + 1;
    ptr->guise = guise;
    ptr->format = format;
    ptr->access = access;
    ptr->stream = stream;

    strcpy( ptr->name, filename );
    strcpy( ptr->key, keyname );

    file_count++;

    *file_ptr = ptr;
    *ifail = FR_no_errors;
    }


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: new_open_file_unicode

Description:

  Allocates new structure, adds the file information and
  adds it to the list of open-file structures.
  This is a unicode version of new_open_file.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static void new_open_file_unicode( FILE* stream, int guise, int format, int access,
			   wchar_t* filename, wchar_t* keyname, file_p* file_ptr,
			   int* ifail )
    {
    file_p ptr;
    file_p temp=0;
    int i;

    /* allocate and add file structure into list of open files */
    ptr = (file_p) malloc( sizeof( file_t ));
    if (ptr == NULL)
      {
        fclose( stream );
        {
        *ifail = FR_open_fail;
        return;
        }
      }

    if (open_files == NULL)
        open_files = ptr;
    else
      {
        for ( temp = open_files; temp->next != NULL; temp = temp->next )
            /* skip */;
        temp->next = ptr;
      }

    /* initialise file structure */
    ptr->next = NULL;
    if (open_files == ptr)
        ptr->prev = NULL;
    else
        ptr->prev = temp;
    for ( i = 0; stream_id[i] != 0; i++ )
        /* skip */;

    stream_id[i] = i + 1;
    ptr->strid = i + 1;
    ptr->guise = guise;
    ptr->format = format;
    ptr->access = access;
    ptr->stream = stream;

	// the name and key of the file, as used in the XT header have been set
	// to "unicode filename" to avoid creating an entirely new type for the
	// file. To set these as unicode, the type of ptr will need to be
	// modified to accept this.
    strcpy( ptr->name, "unicode filename" );
    strcpy( ptr->key, "unicode filename" );

    file_count++;

    *file_ptr = ptr;
    *ifail = FR_no_errors;
    }

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: write_to_file

History:

  May 1990 - reformatted for example frustrum code
  Oct 1992 - minimise freeing of transfer buffer

Description:

  Writes given buffer to open file as either ascii or binary.
  Uses 'fputs' for ascii and 'fwrite' for binary.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static void write_to_file( file_p file_ptr, const char* buffer, int header,
			   size_t buffer_len, int* ifail)
    {
    /* in this example frustrum, the headers of binary and text files are */
    /* output with fputs() and other binary data are output with fwrite() */

    if (header || file_ptr->format == FFTEXT)
        {
        if ( buffer_len == 1 )
            {
            if (fputc( buffer[0], file_ptr->stream ) == EOF)
              {
              *ifail = FR_write_fail;
              }
            else
              {
              *ifail = FR_no_errors;
              }
            }
        else
            {
            unsigned long required;
            unsigned int count;
            /* check whether the global input-output buffer is long enough */
            required = (buffer_len + 1) * sizeof( char );

            if ( input_output_buflen < required )
                {
                if ( input_output_buffer != 0 )
                    free(input_output_buffer);

                input_output_buflen = 0;
                input_output_buffer = (char *) malloc( required );

                if ( input_output_buffer == 0 )
                    {
                    *ifail = FR_unspecified;
                    return;
                    }
                else
                    input_output_buflen = required;
                }


            /* copy the buffer and add a null-terminating character */

            for( count = 0; count < buffer_len; count ++ )
              {
                input_output_buffer[ count ] = buffer[ count ];
              }
            input_output_buffer[buffer_len] = end_of_string_c;

            /* the string will already contain any necessary formatting characters
              (added by the header routines or Parasolid); fputs does not add any
            */

            if (fputs( input_output_buffer, file_ptr->stream ) == EOF)
              {
                *ifail = FR_write_fail;
              }
            else
              {
              *ifail = FR_no_errors;
              }
            }
        }
    else
        {
        /* write to binary file */
        size_t written;
        written = fwrite( buffer, (unsigned) (sizeof(char)),
                          buffer_len, file_ptr->stream );
        if ( written != buffer_len)
          {
            *ifail = FR_write_fail;
          }
        else
          {
            *ifail = FR_no_errors;
          }
        }
    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: read_from_file

History:

  May 1990 - reformatted for example frustrum code
  Oct 1992 - minimise freeing of transfer buffer

Description:

  Read the required amount of data from open file.
  Uses 'fgets' for ascii and 'fread' for binary.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static void read_from_file( file_p file_ptr, char* buffer, int header,
			    int max_buffer_len, int* buffer_len, int* ifail)
    {
    /* in this example frustrum, the headers of binary and text files are */
    /* input with fgets()  and  other binary data are input with fread()  */

    if (header || file_ptr->format == FFTEXT)
        {
        if ( max_buffer_len == 1 )
            {
            int value = fgetc(file_ptr->stream);
            if ( value == EOF )
                {
                *ifail = (feof(file_ptr->stream)?FR_end_of_file:FR_read_fail);
                return;
                }
            else
                {
                buffer[0] = value;
                *buffer_len = 1;
                }
            }
        else
            {
            unsigned long required;

            /* check whether current global input-output buffer long enough */
            required = (max_buffer_len + 1) * sizeof( char );

            if ( input_output_buflen < required )
                {
                if ( input_output_buffer != 0 )
                    free(input_output_buffer);

                input_output_buflen = 0;
                input_output_buffer = (char *) malloc( required );

                if ( input_output_buffer == 0 )
                    {
                    *ifail = FR_unspecified;
                    return;
                    }
                else
                    input_output_buflen = required;
                }

            /* note that the second argument to fgets is the maximim number */
            /* of characters which can ever be written (including the null) */
            /* which is why the second argument to fgets = max_buffer_len+1 */
            if (fgets(input_output_buffer, max_buffer_len+1,
                      file_ptr->stream) == 0)
                {
                *ifail = (feof(file_ptr->stream)?FR_end_of_file:FR_read_fail);

                return;
                }

            /* copy input buffer back to calling function without terminator */
            *buffer_len = (int) strlen(input_output_buffer);
            strncpy(buffer, input_output_buffer, *buffer_len);
            }
        }
    else
        {
        size_t chars = fread( buffer, (unsigned) (sizeof( char )),
                                max_buffer_len, file_ptr->stream );
        if (chars == 0)
          {
          *ifail = ( feof(file_ptr->stream) ? FR_end_of_file : FR_read_fail );

          return;
          }

        *buffer_len = (int) chars;
        }

    *ifail = FR_no_errors;
    }


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: check_valid_unicode_filename

Description:

  Checks that filename is valid, that no spurious characters are there.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static void check_valid_unicode_filename( wchar_t* filename, int* ifail )
    {
    int len;

    /* check that the string is not too long */
    len = wcslen( filename );
    if ( len > max_namelen )
      {
        *ifail = FR_bad_name;
        return;
      }

    *ifail = FR_no_errors;
    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: extend_schema_unicode_filename

Description:

  Add a path variable detailing the location of the schema files. In
  this case the path is hardcoded but could be stored and read from
  the registry. Prepend the path (and a directory separator) to the
  supplied pathname.
  If the resulting pathname would exceed max_namelen characters, the
  supplied pathname is not modified.

  This is a unicode version of extend_schema_filename.
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
static void extend_schema_unicode_filename( __wchar_t* filename )
{
	int namelen = (int)wcslen(filename);
	for ( int i = 0 ; i < namelen ; i++ )
		filename[i] = tolower(filename[i]);

    __wchar_t extended_filename[max_namelen + 1];
  
    __wchar_t const * p_schema_prefix = HP_Get_Schema_Path();
    if ( p_schema_prefix != NULL
    &&  wcslen(p_schema_prefix) + 1 + wcslen(filename) < max_namelen )
    {
        wcscpy( extended_filename, p_schema_prefix );
        wcscat( extended_filename, dir_separator_unicode_s );
        wcscat( extended_filename, filename );
        wcscpy( filename, extended_filename );
		wcscat(filename, L".sch_txt");
    }
}


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: write_header

History:

  May 1990 - reformatted for example frustrum code
  Jan 1995 - max_header_line increased to allow for very long lines when
                 writing   FILE=expanded_P_SCHEMA/name   into the header

Description:

  Writes standard header to file. Most keyword values are written as
  "unknown". This must be changed straight away to produce meaningful
  text - in particular the frustrum name, application name, date and
  type of machine.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static void write_header( file_p file_ptr, const char* pd2hdr, int pd2len,
			  int* ifail)
    {
    char buffer[max_header_line];
    write_to_file( file_ptr, g_preamble_1, 1, strlen(g_preamble_1), ifail );
    if ( *ifail != FR_no_errors ) return;

    write_to_file( file_ptr, g_preamble_2, 1, strlen(g_preamble_2), ifail );
    if ( *ifail != FR_no_errors ) return;

    write_to_file( file_ptr, g_prefix_1, 1, strlen(g_prefix_1), ifail );
    if ( *ifail != FR_no_errors ) return;

    /* machine specific - the frustrum should write the machine name */
    strcpy( buffer, "MC=unknown;\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    /* machine specific - the frustrum should write the machine model number */
    strcpy( buffer, "MC_MODEL=unknown;\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    /* machine specific - the frustrum should write the machine identifier */
    strcpy( buffer, "MC_ID=unknown;\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    /* machine specific - the frustrum should write the operating system name */
    strcpy( buffer, "OS=unknown;\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    /* machine specific - the frustrum should write the operating system versn */
    strcpy( buffer, "OS_RELEASE=unknown;\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    /* machine specific - this should be replaced by your company name */
    strcpy( buffer, "FRU=sdl_parasolid_customer_support;\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    /* machine specific - this should be replaced by your product's name */
    strcpy( buffer, "APPL=parasolid_acceptance_tests;\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    /* machine specific - this should be replaced by your company's location */
    strcpy( buffer, "SITE=unknown;\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    /* machine specific - this should be replaced by runtime user's login id */
    strcpy( buffer, "USER=unknown;\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    strcpy( buffer, "FORMAT=" );
    strcat( buffer, format_string( file_ptr->format ) );
    strcat( buffer, ";\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    strcpy( buffer, "GUISE=" );
    strcat( buffer, guise_string( file_ptr->guise ) );
    strcat( buffer, ";\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    strcpy( buffer, "KEY=" );
    strcat( buffer, file_ptr->key );
    strcat( buffer, ";\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    strcpy( buffer, "FILE=" );
    strcat( buffer, file_ptr->name );
    strcat( buffer, ";\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    /* machine specific - this should be replaced by the runtime date */
    strcpy( buffer, "DATE=unknown;\n" );
    write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
    if ( *ifail != FR_no_errors ) return;

    write_to_file( file_ptr, g_prefix_2, 1, strlen(g_prefix_2), ifail );
    if ( *ifail != FR_no_errors ) return;

    {
    int pd2_count, buffer_count;

    buffer_count = 0;
    for (pd2_count = 0; pd2_count < pd2len; pd2_count++ )
      {
      char c = buffer[buffer_count] = pd2hdr[pd2_count];
      if ( c == ';' )
        {
        buffer[ buffer_count +1 ] = new_line_c;
        buffer[ buffer_count +2 ] = end_of_string_c;
        write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
        if ( *ifail != FR_no_errors ) return;
        buffer_count = 0;
        }
      else
        {
        buffer_count++;
        }
      }
    }
    write_to_file( file_ptr, g_prefix_3, 1, strlen(g_prefix_3), ifail );
    if ( *ifail != FR_no_errors ) return;

    write_to_file( file_ptr, g_trailer, 1, strlen(g_trailer), ifail );
    if ( *ifail != FR_no_errors ) return;

    *ifail = FR_no_errors;
    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: setup_header

History:

  May 1990 - reformatted for example frustrum code

Description:

  Initialise the global variables storing the text for the stardard
  headers written to files.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static void setup_header( void )
    {

    strcpy( g_preamble_1,
              "**" );                           /* two asterisks */
    strcat( g_preamble_1,
              "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );   /* upper case letters */
    strcat( g_preamble_1,
              "abcdefghijklmnopqrstuvwxyz" );   /* lower case letters */
    strcat( g_preamble_1,
              "**************************" );   /* twenty six asterisks */
    strcat( g_preamble_1, new_line_s );


    strcpy( g_preamble_2,
              "**" );                           /* two asterisks */
    strcat( g_preamble_2,
              "PARASOLID" );                    /* PARASOLID (upper case) */
    strcat( g_preamble_2,
              " !" );                           /* space and exclamation */
    strcat( g_preamble_2,
              "\"" );                           /* a double quote char */
    strcat( g_preamble_2,
              "#$%&'()*+,-./:;<=>?@[" );        /* some special chars */
    strcat( g_preamble_2,
              "\\" );                           /* a backslash char */
    strcat( g_preamble_2,
              "]^_`{|}~" );                     /* more special chars */
    strcat( g_preamble_2,
              "0123456789" );                   /* digits */
    strcat( g_preamble_2,
              "**************************" );   /* twenty six asterisks */
    strcat( g_preamble_2, new_line_s );


    strcpy( g_trailer, g_trailer_start );
    strcat( g_trailer,
        "*****************************************************************" );
    strcat( g_trailer, new_line_s );

    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: skip_header

History:

  May 1990 - reformatted for example frustrum code

Description:

  Skip header information when opening a file for read.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

static void skip_header( file_p file_ptr, int* ifail )
    {
    char buffer[max_header_line];
    int chars_read = 0;
    int end_header = 0;
    int first_line = 1;
	const int preamble_len = strlen(g_preamble_1);
	const int trailer_start_len = strlen(g_trailer_start);

    while (!end_header)
        {
        /* read from the file */
        read_from_file( file_ptr, buffer, 1, max_header_line, &chars_read, ifail );
        if ( *ifail != FR_no_errors ) return;
        /***
        ***/

        if (strncmp( buffer, g_trailer_start, trailer_start_len ) == 0)
            {
            /*** this is the end of the header */
            end_header = 1;
            }
        else
        if (first_line			
			/* -1 to skip linebreak character */
        &&  strncmp( buffer, g_preamble_1, preamble_len - 1 ) != 0) 
            {
            /*
            rewind the file to the beginning as the header is not there
            (this must be a Parasolid version 1 or Romulus version 6 file
            */
            rewind( file_ptr->stream );
            end_header = 1;
            }
        else
            {
            /*  line skipped  */
            }

        first_line = 0;
        }
    *ifail = FR_no_errors;
    }



/*=============================================================================
                 EXTERNAL ROUTINES
=============================================================================*/


/* Function: FSTART

History:

  May 1990 - reformatted for example frustrum code

Description:

  Start frustrum; set up file structures if not already done

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern DLLEXPORT void FSTART( int* ifail )
    {
    int i;
    *ifail = FR_unspecified;
//    trace_print(">>> FSTART\n");

    if (frustrum_started == 0)
    {
    for ( i = 0; i < max_open_files; i++ )
      stream_id[i] = 0;

    /* set up the global variables required for writing
    frustrum file headers */
    setup_header();

#ifdef PS_AIX
    /* associate function "danger_catcher" with the condition SIGDANGER */
    signal(SIGDANGER, danger_catcher);
    short_of_memory = 0; /* set the global flag as false */
#endif
    }

    frustrum_started++;

    *ifail = FR_no_errors;
//    trace_print(">>> returning from FSTART with ifail %d\n", *ifail );
    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FSTOP

History:

  May 1990 - reformatted for example frustrum code
  Nov 1992 - reset input_output_bufer to 0 on free

Description:

  Stop frustrum. Does nothing much.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern DLLEXPORT void FSTOP( int* ifail )
    {
    *ifail = FR_unspecified;
//    trace_print(">>> FSTOP\n");

    if (frustrum_started <= 0)
        {
        *ifail = FR_not_started;
//        trace_print(">>> returning from FSTOP with ifail %d\n", *ifail );
        return;
        }

    frustrum_started--;

    if ( input_output_buffer != 0 )
        {
        input_output_buflen = 0;
        free(input_output_buffer);
        input_output_buffer = 0;
        }

    if ( frustrum_started == 0 )
      {
      file_p file_ptr = open_files;

      /* while there are still files open - close them down */
      while (file_ptr != 0)
        {
        fclose( file_ptr->stream );
        if (file_ptr->next == 0)
          {
          /* free the space used in the file pointer */
          free( file_ptr );
          file_ptr = 0;
          }
        else
          {
          file_ptr = file_ptr->next;
          free( file_ptr->prev );
          }
        }

      /* reset variables and return values */
      file_count = 0;
      open_files = 0;
      }

    *ifail = FR_no_errors;
//    trace_print(">>> returning from FSTOP with ifail %d\n", *ifail );
    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FMALLO

History:

  May 1990 - reformatted for example frustrum code

Description:

  Attempts to allocate memory as requested

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern DLLEXPORT void FMALLO( int* nbytes, char** memory, int* ifail)
    {
    *ifail = FR_unspecified;
//    trace_print(">>> FMALLO %d\n", *nbytes);
    if (frustrum_started <= 0)
        {
        *memory = 0;

        *ifail = FR_not_started;
//        trace_print(">>> returning from FMALLO with ifail %d\n", *ifail );
        return;

        }

#ifdef PS_AIX
    if (short_of_memory) /* operating system has warned danger_catcher of it */
        {
        /* when the Frustrum tells Parasolid it has run out of virtual memory,
           Parasolid will perform some housekeeping tasks which will free up
           some space, hence it is approriate to reset the global flag here */
        *memory = 0;
        short_of_memory = 0;
        }
    else if (psdanger(SIGKILL)*PAGESIZE <= *nbytes)
        {
        /* psdanger(SIGKILL) returns the current number of free paging
           space blocks minus the op system paging space kill threshold */
        *memory = 0;
        }
#endif

    *memory = (char *) malloc( *nbytes );

    if (*memory == 0)
        {
        *ifail = FR_memory_full;
//        trace_print(">>> returning from FMALLO with ifail %d\n", *ifail );
        return;
        }

    *ifail = FR_no_errors;
//    trace_print(">>> returning from FMALLO with ifail %d\n", *ifail );
    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FMFREE

History:

  May 1990 - reformatted for example frustrum code

Description:

  Frees memory

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern DLLEXPORT void FMFREE( int* nbytes, char** memory, int* ifail )
    {
    *ifail = FR_unspecified;
//    trace_print(">>> FMFREE\n");
    if (frustrum_started <= 0)
        {
        *ifail = FR_not_started;
//        trace_print(">>> returning from FMFREE with ifail %d\n", *ifail );
        return;
        }

    free( *memory );

    *ifail = FR_no_errors;
//    trace_print(">>> returning from FMFREE with ifail %d\n", *ifail );
    }


void EnsurePointsAllocated(unsigned int numPointsNeeded, unsigned int* allocated_points, float** points)
{
	unsigned long nbytes;
	unsigned int new_allocated_points;
	
	if (numPointsNeeded > *allocated_points)
	{
		new_allocated_points = *allocated_points;

		while(new_allocated_points < numPointsNeeded)
			new_allocated_points += allocation_chunksize;

		nbytes = 3 * new_allocated_points * sizeof (float);
		*points = (float*)realloc(*points, nbytes);
		assert(points);
		normals = (float*)realloc(normals, nbytes);
		assert(normals);

		*allocated_points = new_allocated_points;
	}
}

void EnsureListAllocated(unsigned int numListEltsNeeded)
{
	unsigned long nbytes;
	unsigned int new_allocated_list_elts;
	
	if (numListEltsNeeded > allocated_list_elts)
	{
		new_allocated_list_elts = allocated_list_elts;

		while(new_allocated_list_elts < numListEltsNeeded)
			new_allocated_list_elts += allocation_chunksize;


		nbytes = new_allocated_list_elts * sizeof (float);
		face_list = (int*) realloc(face_list, nbytes);	
		allocated_list_elts = new_allocated_list_elts;
	}
}

extern "C" void FreeParasolidFrustrumMemory ( void )
{
	int  nbytes;
	PK_ERROR_t error;
	if (allocated_face_points)
	{
//		nbytes = 3*sizeof(float)*allocated_points;
//		FMFREE(&nbytes, (char**)&points, &error);
//		assert(nbytes == (3*sizeof(float)*allocated_points));
		free(face_points);
		face_points = 0;

//		nbytes = 3*sizeof(float)*allocated_points;
//		FMFREE(&nbytes, (char**)&normals, &error);
//		assert(nbytes == (3*sizeof(float)*allocated_points));
		free(normals);
		normals = 0;

		allocated_face_points = 0;

//		nbytes = allocated_list_elts * sizeof(float);
//		FMFREE(&nbytes, (char**)&face_list, &error);
//		assert(nbytes == (allocated_list_elts * sizeof(float)));
		free(face_list);
		face_list = 0;

		allocated_list_elts=0;
	}
	if (allocated_face_points)
	{
		free(face_points);
		face_points = 0;
		allocated_face_points = 0;
	}
	if (min)
	{
		/* free space allocated for min and max */
		assert(max);
		nbytes = (int) sizeof(Point);
		FMFREE(&nbytes, (char**)&min, &error);
		assert(nbytes == sizeof(Point));
		min = 0;

		nbytes = (int) sizeof(Point);
		FMFREE(&nbytes, (char**)&max, &error);
		assert(nbytes == sizeof(Point));
		max = 0;
	}
	else
		assert(!max);
	FreeParaPartitions();
}

void AllocMinMax( void )
{
	PK_ERROR_t error;
	int nbytes;
	assert(!min);
	assert(!max);
	nbytes = (int) sizeof(Point);
	FMALLO(&nbytes, (char**)&min, &error);
	assert(nbytes == sizeof(Point));
	FMALLO(&nbytes, (char**)&max, &error);
	assert(nbytes == sizeof(Point));
}


void UpdateMinMax(Point p)
{
	if (!min)
	{
		/* first value, set min and max to be equal to it */
		AllocMinMax();
		min->x = p.x;
		min->y = p.y;
		min->z = p.z;
		max->x = p.x;
		max->y = p.y;
		max->z = p.z;
	}
	else
	{
		if (p.x < min->x)
			min->x = p.x;

		if (p.y < min->y)
			min->y = p.y;

		if (p.z < min->z)
			min->z = p.z;


		if (p.x > max->x)
			max->x = p.x;

		if (p.y > max->y)
			max->y = p.y;

		if (p.z > max->z)
			max->z = p.z;

	}
}


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FFTELL

History:

  May 1990 - reformatted for example frustrum code

Description:

  Indicate position in rollback file.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern DLLEXPORT void FFTELL( const int* guise, const int* strid, int* pos, int* ifail )
    {
    file_p file_ptr;
    *ifail = FR_unspecified;
//    trace_print(">>> FFTELL %d %d\n", *guise, *strid);

    if (frustrum_started <= 0)
        {
        *ifail = FR_not_started;
//        trace_print(">>> returning from FFTELL with ifail %d\n", *ifail );
        return;
        }


    if (*guise != FFCROL)
        {
        *ifail = FR_unspecified;
//        trace_print(">>> returning from FFTELL with ifail %d\n", *ifail );
        return;
        }

    /* check file is open */
    for ( file_ptr = open_files; file_ptr != 0; file_ptr = file_ptr->next )
      {
        if (file_ptr->strid == *strid) break;
      }

    if (file_ptr == 0)
        {
        *ifail = FR_internal_error;
//        trace_print(">>> returning from FFTELL with ifail %d\n", *ifail );
        return;
        }


    /* check file guise */
    if (*guise != file_ptr->guise)
      {
      *ifail = FR_unspecified;
//      trace_print(">>> returning from FFTELL with ifail %d\n", *ifail );
      return;
      }

    /* note file pointer */
    *pos = (int) ftell( file_ptr->stream );

    *ifail = FR_no_errors;
//    trace_print(">>> returning from FFTELL with ifail %d\n", *ifail );
    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FFSEEK

History:

  May 1990 - reformatted for example frustrum code

Description:

  Change position in rollback file.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern DLLEXPORT void FFSEEK( const int* guise, const int* strid, const int* pos,
                    int* ifail )
    {
    file_p file_ptr;
    *ifail = FR_unspecified;
//    trace_print(">>> FFSEEK %d %d\n", *guise, *strid);

    if (frustrum_started <= 0)
      {
      *ifail = FR_not_started;
 //     trace_print(">>> returning from FFSEEK with ifail %d\n", *ifail );
      return;
      }

    if (*guise != FFCROL)
      {
      *ifail = FR_unspecified;
 //     trace_print(">>> returning from FFSEEK with ifail %d\n", *ifail );
      return;
      }

    /* check file is open */
    for ( file_ptr = open_files; file_ptr != 0; file_ptr = file_ptr->next )
      {
      if (file_ptr->strid == *strid) break;
      }

    if (file_ptr == 0)
      {
      *ifail = FR_internal_error;
//      trace_print(">>> returning from FFSEEK with ifail %d\n", *ifail );
      return;
      }


    /* check file guise */
    if (*guise != file_ptr->guise)
      {
      *ifail = FR_unspecified;
 //     trace_print(">>> returning from FFSEEK with ifail %d\n", *ifail );
      return;
      }

    /* reset file pointer */
    if (fseek( file_ptr->stream, (long) (*pos), 0 ) != 0)
      {
      *ifail = FR_unspecified;
 //     trace_print(">>> returning from FFSEEK with ifail %d\n", *ifail );
      return;
      }


    *ifail = FR_no_errors;
//    trace_print(">>> returning from FFSEEK with ifail %d\n", *ifail );
    }

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FFOPRD

History:

  May 1990 - reformatted for example frustrum code

Description:

  Opens a file for read. A file extension is added to show the guise
  and format of the file. If requested, all the line containing the file
  header will be skipped.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

void FFOPRD( const int* guise, const int* format, const char* name, 
		    const int* namlen, const int* skiphd, int* strid,
		    int* ifail )
    {
    __wchar_t   keyname[max_namelen+1];  /* holds key + null char     */
    __wchar_t  filename[max_namelen+1];  /* holds key + extension     */
    FILE *stream;
    file_p file_ptr;

    *ifail = FR_unspecified;
    *strid = null_strid;

    /* check that limit hasnt been reached */
    if (file_count == max_open_files)
      {
      *ifail = FR_open_fail;
      return;
      }

	H_WCS wcs_name(name);
    wcsncpy(  keyname, wcs_name.encodedText(), *namlen );
    keyname[*namlen]  = end_of_string_unicode_c;

    wcsncpy( filename, wcs_name.encodedText(), *namlen );
    filename[*namlen] = end_of_string_unicode_c;

    if ( *guise == FFCSCH )
        {
	        extend_schema_unicode_filename(filename);
        }


    check_valid_unicode_filename( filename, ifail );
    if ( *ifail != FR_no_errors )
      {
      return;
      }

    /* open file for reading */
	if (*format == FFBNRY){
      /* if binary file is opened with "r" instead of "rb" reading will fail */
      /* with end-of-file error, if it reads byte with value equal to CTRL-Z */
        stream = wfopen( filename, g_fopen_mode_read_unicode_binary );
	}
	else{		
        stream = wfopen( filename, g_fopen_mode_read_unicode_text );
	}

    if (stream == 0)
      {
      *ifail = FR_not_found;
      return;
      }

    new_open_file_unicode( stream, *guise, *format, read_access,
                   filename, keyname, &file_ptr, ifail );
    if ( *ifail != FR_no_errors )
      {
      return;
      }


    if (*skiphd == FFSKHD)
      {
      skip_header( file_ptr, ifail );
      if ( *ifail != FR_no_errors )
        {
        return;
        }
      }

    *strid = file_ptr->strid;

    *ifail = FR_no_errors;
    }


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FFOPRB

History:

  May 1990 - reformatted for example frustrum code

Description:

  Opens temporary rollback file for read/write.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern DLLEXPORT void FFOPRB( const int* guise, const int* minsiz, const int* maxsiz,
                    int* actsiz, int* strid, int* ifail )
    {
    char filename[max_namelen+1];
    char  keyname[max_namelen+1];
    FILE *stream;
    file_p file_ptr;
    *ifail = FR_unspecified;
    *strid = null_strid;
//    trace_print(">>> FFOPRB\n");
    if (frustrum_started <= 0)
      {
      *ifail = FR_not_started;
//      trace_print(">>> returning from FFOPRB with ifail %d\n", *ifail );
      return;
      }

    if (file_count == max_open_files)
      {
      *ifail = FR_open_fail;
//      trace_print(">>> returning from FFOPRB with ifail %d\n", *ifail );
      return;
      }

    if (*guise != FFCROL)
      {
      *ifail = FR_unspecified;
//      trace_print(">>> returning from FFOPRB with ifail %d\n", *ifail );
      return;
      }


    strcpy( filename, "rollback.001" );
    strcpy( keyname , "rollback"     );


    /* open file */
    stream = fopen( filename, g_fopen_mode_append );
    if (stream == 0)
      {
      *ifail = FR_open_fail;
//      trace_print(">>> returning from FFOPRB with ifail %d\n", *ifail );
      return;
      }

    new_open_file( stream, *guise, FFBNRY, read_write_access,
                          filename, keyname, &file_ptr, ifail );
    if ( *ifail != FR_no_errors )
      {
//      trace_print(">>> returning from FFOPRB with ifail %d\n", *ifail );
      return;
      }

    *actsiz = *maxsiz;
    *strid = file_ptr->strid;
//    trace_print(">>> strid %d\n", *strid );

    *ifail = FR_no_errors;
//    trace_print(">>> returning from FFOPRB with ifail %d\n", *ifail );
    }


//Writes the standard xml header to the file. 
static void write_xml_header( file_p file_ptr, const char* pd2hdr, int pd2len, int* ifail)
{
	char buffer[max_header_line];
	// <?xml version
	strcpy( buffer, "<?xml version=\"1.0\" ?>" );
	write_to_file( file_ptr, buffer, 1, strlen( buffer ), ifail );
	if ( *ifail != FR_no_errors ) return;
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FFOPWR

History:

  May 1990 - reformatted for example frustrum code

Description:

  Opens file to be written and writes to it the standard file header.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

void FFOPWR( const int* guise, const int* format, const char* name,
		    const int* namlen, const char* pd2hdr, const int *pd2len,
		    int *strid, int *ifail )
    {
    __wchar_t   keyname[max_namelen+1];  /* holds key + null char    */
    __wchar_t  filename[max_namelen+1];  /* holds key + extension    */
    FILE *stream;
    file_p file_ptr;

    *ifail = FR_unspecified;
    *strid = null_strid;

    if (file_count == max_open_files)
      {
      *ifail = FR_open_fail;
      return;
      }

	H_WCS wcs_name(name);
    wcsncpy(  keyname, wcs_name.encodedText(), *namlen );
    keyname[*namlen]  = end_of_string_unicode_c;

    wcsncpy( filename, wcs_name.encodedText(), *namlen );
    filename[*namlen] = end_of_string_unicode_c;

    if ( *guise == FFCSCH )
        {
	        /* add (and decode) a P_SCHEMA prefix to the filename  */
	        extend_schema_unicode_filename(filename); 
        }


    check_valid_unicode_filename( filename, ifail );
    if ( *ifail != FR_no_errors )
      {
      return;
      }

    /* open file for writing */
    stream = wfopen( filename, g_fopen_mode_write_unicode );
    if (stream == 0)
      {
      *ifail = FR_already_exists;
      return;
      }

    new_open_file_unicode( stream, *guise, *format, write_access,
                  filename, keyname, &file_ptr, ifail );
    if ( *ifail != FR_no_errors )
      {
      return;
      }

	if ( *guise == FFCDBG )
		write_xml_header( file_ptr, pd2hdr, *pd2len, ifail );
	else
		write_header( file_ptr, pd2hdr, *pd2len, ifail );    

    if ( *ifail != FR_no_errors )
      {
      return;
      }

    *strid = file_ptr->strid;
    *ifail = FR_no_errors;
    }




/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FFWRIT

History:

  May 1990 - reformatted for example frustrum code

Description:

  Write buffer to open file.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

void FFWRIT( const int* guise, const int* strid, const int* nchars,
		    const char* buffer, int* ifail)
    {
    file_p file_ptr;
    *ifail = FR_unspecified;

    /* find the file info for this stream-id  */
    for ( file_ptr = open_files; file_ptr != 0; file_ptr = file_ptr->next )
      {
      if (file_ptr->strid == *strid) break;
      }

    if (file_ptr == 0)
      {
      *ifail = FR_internal_error;
      return;
      }


    /* check file guise */
    if (*guise != file_ptr->guise)
      {
      *ifail = FR_unspecified;
      return;
      }

    /* check access */
    if (file_ptr->access != write_access &&
        file_ptr->access != read_write_access)
      {
      *ifail = FR_unspecified;
      return;
      }


    write_to_file( file_ptr, buffer, 0, *nchars, ifail );
    if ( *ifail != FR_no_errors )
      {
      return;
      }

	/* If we are writing a journal or debug report file then flush the
		buffer - this to ensure that in the event of crash as much data is preserved
		as possible 
	*/
	if (*guise == FFCJNL || *guise == FFCDBG) 
           fflush( file_ptr->stream );


    *ifail = FR_no_errors;
    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FFREAD

History:

  May 1990 - reformatted for example frustrum code

Description:

  Read buffer from open file.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

void FFREAD( const int* guise, const int* strid, const int* nmax,
		    char* buffer, int* nactual, int* ifail)
    {
    file_p file_ptr;
    int chars_read = 0;
    *ifail = FR_unspecified;
    *nactual = 0;

    /* find the correct file pointer */
    for ( file_ptr = open_files; file_ptr != 0; file_ptr = file_ptr->next )
      {
      if (file_ptr->strid == *strid) break;
      }
    if (file_ptr == 0)
        {
        *ifail = FR_internal_error;
        return;
        }


    /* check file guise */
    if (*guise != file_ptr->guise)
      {
      *ifail = FR_unspecified;
      return;
      }

    /* check access */
    if (file_ptr->access != read_access &&
        file_ptr->access != read_write_access)
      {
      *ifail = FR_unspecified;
      return;
      }

    /* read the information from the file */
    read_from_file( file_ptr, buffer, 0, *nmax, &chars_read, ifail );
    if ( *ifail != FR_no_errors )
      {
      return;
      }


    *nactual = chars_read;
    *ifail = FR_no_errors;
    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FFCLOS

History:

  May 1990 - reformatted for example frustrum code

Description:

  Close specified file. If a rollback file or the action is abort then
  delete the file.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

void FFCLOS( const int* guise, const int* strid, const int* action,
		    int* ifail )
    {
    file_p file_ptr;
    char filename[max_namelen+1];
    int delete_it = 0;
    *ifail = FR_unspecified;

    /* find the file info for this stream-id  */
    for ( file_ptr = open_files; file_ptr != 0; file_ptr = file_ptr->next )
      {
      if (file_ptr->strid == *strid) break;
      }

    if (file_ptr == 0)
      {
      *ifail = FR_close_fail;
      return;
      }


    if ( file_ptr->access == read_write_access ||
         (file_ptr->access == write_access && *action == FFABOR) )
      {
      delete_it = 1;
      strcpy( filename, file_ptr->name );
      }


    /* close file */
    stream_id[file_ptr->strid - 1] = 0;
    if (fclose( file_ptr->stream ) == EOF)
      {
      *ifail = FR_close_fail;
      return;
      }

    if (file_ptr == open_files)
        open_files = open_files->next;
    else
        file_ptr->prev->next = file_ptr->next;

    if (file_ptr->next != 0)
        file_ptr->next->prev = file_ptr->prev;

    free( file_ptr );
    file_count--;

    if (delete_it)
      {
      delete_file( filename, ifail );
      if ( *ifail != FR_no_errors )
        {
        return;
        }
      }

    *ifail = FR_no_errors;
    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: FABORT

History:

  May 1990 - reformatted for example frustrum code
  Oct 1992 - activity moved to FSTOP

Description:

  Aborting a kernel operation. In this implementation, it does nothing

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

void FABORT( int* ifail )
    {
    *ifail = FR_no_errors;
    }


/*=============================================================================
                 GO ROUTINES
=============================================================================*/

/*=============================================================================
                 HELPERS FOR GO ROUTINES
=============================================================================*/


PK_ATTDEF_t GetColorAttributeDefinition( void )
{
	static PK_ATTDEF_t color_attdef = PK_ENTITY_null;

	if(color_attdef == PK_ENTITY_null)
	{
		// ask Parasolid for the tag of the attribute definition
		PK_ATTDEF_find(  "SDL/TYSA_COLOUR", &color_attdef );
		assert(color_attdef != PK_ENTITY_null);
	}
	return color_attdef;
}




/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: GOOPPX

History:

  May 1990 - reformatted for example frustrum code
  Oct 1994 - return CONTIN

Description:

  Open Pixel Data - dummy routine - return code for 'continue, no errors'.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern DLLEXPORT void GOOPPX( const int* nreals, const double* rvals, const int* nints,
                    const int* ivals, int* ifail)
{
//    trace_print(">>> GOOPPX\n" );
    *ifail = CONTIN;
}


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: GOCLPX

History:

  May 1990 - reformatted for example frustrum code
  Oct 1994 - return CONTIN

Description:

  Open Pixel Data - dummy routine - return code for 'continue, no errors'.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern DLLEXPORT void GOCLPX( const int* nreals, const double* rvals, const int* nints,
                    const int* ivals, int* ifail)
{
//    trace_print(">>> GOCLPX\n" );
    *ifail = CONTIN;
}


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: GOPIXL

History:

  May 1990 - reformatted for example frustrum code
  Oct 1994 - return CONTIN

Description:

  Open Pixel Data - dummy routine - return code for 'continue, no errors'.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern DLLEXPORT void GOPIXL( const int* nreals, const double* rvals, const int* nints,
                    const int* ivals, int* ifail)
{
//    trace_print(">>> GOPIXL\n" );
    *ifail = CONTIN;
}

/* note color is passed by value because we may modify this value inside this function */
/* also note that the string colorName must have room for colorNameLength +1 characters */
long MapColorToKey(float *color)
{
	int i;
	char colorName[7];
	long colorvalue;
	int colorNameLength = 6;
	char workspace[30];
	int sigdigits;
	float colorcomponent;

	if (!color) return MAX_COLORVALUE_KEY; /* this is the key for "non-colored" geometry */
	
	/* originally this function mapped color to a string of digits, it's been retrofitted to just return an HC_KEY. */
	
	/* set number of significant digits and set up the format string for generating the string */
	sigdigits = colorNameLength/3;

	for (i = 0; i < 3; i++)
	{
		/* map 1.0f colors to .999999 in name only */
		colorcomponent = color[i];
		if (colorcomponent < 0.0f)
			colorcomponent = 0.0f;
		if (colorcomponent >= .999999f)
			colorcomponent = .999999f;
		sprintf(workspace, "%.6f", colorcomponent);
		assert(workspace[1] == '.');
		assert(workspace[2+6] == '\0');
		/* copy the significant number of digits from just after the decimal in workspace
		   into the string colorName at the appropriate location */
		strncpy(colorName+i*sigdigits, workspace+2, sigdigits);
	}
	colorName[colorNameLength] = '\0'; /* null-terminate the string */
	sscanf(colorName, "%ld", &colorvalue);
	colorvalue += MIN_COLORVALUE_KEY;
	/* colorvalue will always be a key between MIN_COLORVALUE_KEY and 10999999 */
	return colorvalue;
}

/* note color is passed by value because we may modify this value inside this function */
/* also note that the string colorName must have room for colorNameLength +1 characters */
void GenerateColorName(char* colorName, int colorNameLength, float *color)
{
	int i;
	char workspace[30];
	int sigdigits;
	float colorcomponent;

	/* set number of significant digits and set up the format string for generating the string */
	sigdigits = colorNameLength/3;

	assert(sigdigits > 0);
	assert(sigdigits <= 6); /* reasonable precision enforced */
	assert((colorNameLength % 3) == 0); /* assume same number of characters for red, green, blue */


	for (i = 0; i < 3; i++)
	{
		/* map 1.0f colors to .999999 in name only */
		colorcomponent = color[i];
		if (colorcomponent < 0.0f)
			colorcomponent = 0.0f;
		if (colorcomponent >= .999999f)
			colorcomponent = .999999f;
		sprintf(workspace, "%.6f", colorcomponent);
		assert(workspace[1] == '.');
		assert(workspace[2+6] == '\0');
		/* copy the significant number of digits from just after the decimal in workspace
		   into the string colorName at the appropriate location */
		strncpy(colorName+i*sigdigits, workspace+2, sigdigits);
	}
	colorName[colorNameLength] = '\0'; /* null-terminate the string */
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: GOOPSG

History:

  May 1990 - reformatted for example frustrum code
  Oct 1994 - return CONTIN

Description:

  Open Pixel Data - dummy routine - return code for 'continue, no errors'.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/


static void open_body_segment( void )
{
	PK_ERROR_t error;
	PK_BODY_t body;
	HC_KEY key;
	if (g_body_segment_mode && !g_no_mapping_mode)
	{
		PK_CLASS_t paraClass;
		error = PK_ENTITY_ask_class(current_face_or_line_tag, &paraClass);
		if (paraClass == PK_CLASS_face)
			error = PK_FACE_ask_body(current_face_or_line_tag, &body);
		else
			error = PK_EDGE_ask_body(current_face_or_line_tag, &body);

		assert(!error);
		assert(body > 0);
//		if (HC_Show_Existence_By_Key(body, "self"))
		key = g_pMap->FindMapping(body);
		if (key)
		{
			HC_Open_Segment_By_Key(key);
		}
		else
		{
			newly_opened_body_segment = HC_KOpen_Segment("");

			// if it's not a solid body (its a sheet/general body), set no culling
			PK_BODY_type_t body_type;
			error = PK_BODY_ask_type(body, &body_type);
			if( body_type != PK_BODY_type_solid_c )
		 		HC_Set_Heuristics("backplane cull = off");

			assert(newly_opened_body_segment != 0);
		}
	}
}

static void close_body_segment( void )
{
	PK_ERROR_t error;
	PK_BODY_t body;
	if (g_body_segment_mode && !g_no_mapping_mode)
	{
		HC_Close_Segment();
		if (newly_opened_body_segment != 0)
		{
			PK_CLASS_t paraClass;
			error = PK_ENTITY_ask_class(current_face_or_line_tag, &paraClass);
			assert(!error);
			if (paraClass == PK_CLASS_face)
				error = PK_FACE_ask_body(current_face_or_line_tag, &body);
			else
				error = PK_EDGE_ask_body(current_face_or_line_tag, &body);
			assert(!error);
			assert(body > 0);
//			assert(!HC_Show_Existence_By_Key(body, "self"));
//			HC_Renumber_Key(newly_opened_body_segment, body, "global");
			assert(!g_pMap->FindMapping(body));
			g_pMap->AddMapping(newly_opened_body_segment, body);			
			newly_opened_body_segment = 0;
		}
	}
}
static void open_color_segment( void )
{
	if (g_color_segment_mode)
	{
		float color[3];
		long color_code;
		PK_ATTDEF_t color_attdef;
		PK_ATTRIB_t attrib;
		PK_ERROR_t error;
		int i;
		char colorstring[100]; // really only need about 10, but this won't hurt
		float* paraColor = 0;  /* paraColor stays 0 if no color is set in Parasolid */
		color_attdef = GetColorAttributeDefinition();

		error = PK_ENTITY_ask_first_attrib( current_face_or_line_tag, color_attdef, &attrib );
		assert(!error);
		if(attrib == PK_ENTITY_null)
		{
			PK_FACE_t *faces;
			int n_faces;
			PK_CLASS_t PKclass;

			error = PK_ENTITY_ask_class( current_face_or_line_tag, &PKclass );
			assert(!error);
			if (PKclass == PK_CLASS_edge)
			{
				error = PK_EDGE_ask_faces( current_face_or_line_tag, &n_faces, &faces );
				for(i = 0; i < n_faces; i++)
				{
					/* this edge might border 2 differently-colored faces.
					   we'll take the first color info we find and use that.
					   (this is the same behavior as the PSOLID OGL viewer) */
					error = PK_ENTITY_ask_first_attrib( faces[i], color_attdef, &attrib );
					if(attrib != PK_ENTITY_null)
						break;
				}
				if (n_faces)
					free(faces);
			}
		}
		if (attrib != PK_ENTITY_null) 
		{
			int nDoubles;
			double* data;
			PK_ATTRIB_ask_doubles( attrib, 0, &nDoubles, &data );
			if (nDoubles)
			{
				assert( nDoubles == 3 );
				color[0] = (float)data[0];
				color[1] = (float)data[1];
				color[2] = (float)data[2];
				paraColor = color;
				PK_MEMORY_free( data );
			}
		}
		color_code = MapColorToKey(paraColor);
		assert(color_code >= MIN_COLORVALUE_KEY);
		assert(color_code <= MAX_COLORVALUE_KEY);
		sprintf(colorstring, "%ld", color_code);
 
		HC_Open_Segment(colorstring);
		if (paraColor) /* only set color if it's set in parasolid */
			HC_Set_Color_By_Value("lines, faces, edges", "RGB", color[0], color[1], color[2]);
	}
}

static void close_color_segment( void )
{
	if (g_color_segment_mode)
	{
		HC_Close_Segment();
	}
}


static void open_geom_segments( void )
{

	HC_KEY key = g_pMap->FindMapping(current_face_or_line_tag);
	if (key)
	{

		char key_type[128];
		HC_Show_Key_Type(key, key_type);
		if ((key_type[0] == 's') && (key_type[1] == 'e'))
		{
			newly_opened_geom_segment = key;
			HC_Open_Segment_By_Key(key);
			return;
		}
	}
	open_body_segment();
	open_color_segment();
}

static void close_geom_segments( void )
{
	if (newly_opened_geom_segment)
	{
		HC_Close_Segment();
		newly_opened_geom_segment = 0;
	}
	else
	{
		close_color_segment();
		close_body_segment();
	}
}

static void build_shell( void )
{
    int		new_pcount;
    int		new_flist_length;
    int		*new_face_list;
    int		*point_mapping_list;
    int		*face_mapping_list;
    Point	*new_points;
	int		i;
	HC_KEY	key;

	open_geom_segments();
 
	/* malloc arrays for the returned Shell -
       sizes cannot be bigger than unoptimized_shell sizes */
    new_points = (Point *) malloc (total_face_points *
				   sizeof (Point));
    new_face_list =  (int *) malloc (total_face_list_count *
				     sizeof (int));
    point_mapping_list = (int *) malloc (total_face_points *
					 sizeof (int));
    face_mapping_list = (int *) malloc (total_face_list_count *
					sizeof (int));
//		point_mapping_list = 0;
//		face_mapping_list = 0;

    HC_Compute_Optimized_Shell (total_face_points, face_points, 0,
				total_face_list_count, face_list,
				"tolerance = 0% fru",
				&new_pcount, new_points,
				&new_flist_length, new_face_list,
				point_mapping_list, face_mapping_list);
 
    key = HC_KInsert_Shell (new_pcount, new_points,
		     new_flist_length, new_face_list);

	HC_Open_Geometry(key);
	for (i = 0; i < total_face_points; i++)
	{
		if (point_mapping_list[i] != -1)
		{
			HC_Open_Vertex(point_mapping_list[i]);
			HC_Set_Normal(normals[i*3],normals[i*3+1],normals[i*3+2]);
			HC_Close_Vertex();
		}
	}
	HC_Close_Geometry();
//	assert((current_face_or_line_tag < MIN_COLORVALUE_KEY) || (current_face_or_line_tag >= MAX_COLORVALUE_KEY)); /* face tag must not overlap with our color tags */
//	assert(HC_Show_Existence_By_Key(current_face_or_line_tag, "self") == 0);
//	HC_Renumber_Key(key, current_face_or_line_tag, "global");

	if (!g_no_mapping_mode)
	{
		assert(!g_pMap->FindMapping(current_face_or_line_tag));
		g_pMap->AddMapping(key, current_face_or_line_tag);
	}

	PK_ERROR_code_t error_code;
	int n_vertices;
	PK_VERTEX_t *vertices;

	error_code = PK_FACE_ask_vertices(current_face_or_line_tag, &n_vertices, &vertices);
	if (!error_code) {
		PK_POINT_t pt;
		PK_POINT_sf_t pt_sf;

		for ( i = 0 ; i < n_vertices ; i++ ) {
			if (!g_pMap->FindMapping(vertices[i])) {
				error_code = PK_VERTEX_ask_point(vertices[i], &pt);
				assert(!error_code);
				error_code = PK_POINT_ask(pt, &pt_sf);
				assert(!error_code);
				key = HC_KInsert_Marker(pt_sf.position.coord[0], pt_sf.position.coord[1], 
										pt_sf.position.coord[2]);
				g_pMap->AddMapping(key, vertices[i]);
			}
		}
	}
	else {
		assert(0);
	}
	PK_MEMORY_free(vertices);

	free(new_points);
	free(new_face_list);
	free(point_mapping_list);
	free(face_mapping_list);
	
	close_geom_segments();
}

static void build_line()
{
	HC_KEY key;

	open_geom_segments();

	assert (total_face_points > 1);
	if (total_face_points == 2)
		key = HC_KInsert_Line (face_points[0],face_points[1],face_points[2],face_points[3],face_points[4],face_points[5]);
	else
	    key = HC_KInsert_Polyline (total_face_points, face_points);
//	assert((current_face_or_line_tag < MIN_COLORVALUE_KEY) || (current_face_or_line_tag >= MAX_COLORVALUE_KEY)); /* face tag must not overlap with our color tags */
//
//	assert(HC_Show_Existence_By_Key(current_face_or_line_tag, "self") == 0);
//	HC_Renumber_Key(key, current_face_or_line_tag, "global");

	if (!g_no_mapping_mode)
	{

//GH99	
	//	assert(!g_pMap->FindMapping(current_face_or_line_tag));
		g_pMap->AddMapping(key, current_face_or_line_tag);
	}
 
	close_geom_segments();
}

extern DLLEXPORT void GOOPSG( const int* segtyp,
										 const int* ntags,
										 const int* tags,
										 const int* ngeom,
										 const double* geom,
										 const int* nlntp,
										 const int* lntp,
										 int* ifail)
{
	segment_level++;

    *ifail = CONTIN;

}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: GOCLSG

History:

  May 1990 - reformatted for example frustrum code
  Oct 1994 - return CONTIN

Description:

  Open Pixel Data - dummy routine - return code for 'continue, no errors'.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern DLLEXPORT void GOCLSG( const int* segtyp, const int* ntags, const int* tags,
                    const int* ngeom, const double* geom, const int* nlntp,
                    const int* lntp, int* ifail)
{
//    trace_print(">>> GOCLSG\n" );
//	printf("Closing segment\n");
	static int collapsed_already = 0;
	segment_level--;
	*ifail = CONTIN;

	if ((total_face_points > 0) && (*segtyp == SGTPFA))
	{
		build_shell();
		total_face_points = 0;
		total_face_list_count = 0;
		collapsed_already = 0;
	}

	*ifail = CONTIN;
}

static void get_center_from_center(float* center, const double* givenCenter)
{
	center[0] = (float)givenCenter[0];
	center[1] = (float)givenCenter[1];
	center[2] = (float)givenCenter[2];
}
static void get_axis_endpoint_from_axis_origin_and_direction_and_length(float* endpoint,
																 const double* origin,
																 const double* direction,
																 double length)
{
	endpoint[0] = (float) (direction[0] * length + origin[0]);
	endpoint[1] = (float) (direction[1] * length + origin[1]);
	endpoint[2] = (float) (direction[2] * length + origin[2]);
}

/* normalize double precision vector in place */
static void normalize_vector(double* vector)
{
	double length;
	length = sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
	vector[0]/=length;
	vector[1]/=length;
	vector[2]/=length;
}

/* reverse double precision vector in place */
static void reverse_vector(double* vector)
{
	vector[0] = - vector[0];
	vector[1] = - vector[1];
	vector[2] = - vector[2];
}

static void verify_normalized(const double* vector)
{
	double length;
	length = vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2];
	if ((length > 1.01) || (length < .99))
		assert(0);
}

static double dot_product(const double* vector1, const double* vector2)
{
	return vector1[0]*vector2[0]+vector1[1]*vector2[1]+vector1[2]*vector2[2];
}

static void cross_product( const double* x, const double* y, double* z )
{
	z[ 0 ] = x[1]*y[2] - x[2]*y[1];
	z[ 1 ] = x[2]*y[0] - x[0]*y[2];
	z[ 2 ] = x[0]*y[1] - x[1]*y[0];
}

static bool are_vectors_within_tolerance( const double* vector1, const double* vector2, const double tolerance )
{
	double middle[3];
	middle[0] = vector1[0] - vector2[0];
	middle[1] = vector1[1] - vector2[1];
	middle[2] = vector1[2] - vector2[2];
	if (   (middle[0] <= tolerance) && (middle[0] >= -tolerance) 
		&& (middle[1] <= tolerance) && (middle[1] >= -tolerance) 
		&& (middle[2] <= tolerance) && (middle[2] >= -tolerance)) 
		return true;
	else
		return false;
}

static unsigned int compare_vectors( const double* vector1, const double* vector2 )
{
	double diff[3];
	diff[0] = vector2[0] - vector1[0];
	diff[1] = vector2[1] - vector1[1];
	diff[2] = vector2[2] - vector1[2];
	if (((diff[0] < .01) && (diff[0] > -.01))
		&& ((diff[1] < .01) && (diff[1] > -.01))
		&& ((diff[2] < .01) && (diff[2] > -.01)))
		return HPK_VECTORS_SAME;
	diff[0] = vector2[0] + vector1[0];
	diff[1] = vector2[1] + vector1[1];
	diff[2] = vector2[2] + vector1[2];
	if (((diff[0] < .01) && (diff[0] > -.01))
		&& ((diff[1] < .01) && (diff[1] > -.01))
		&& ((diff[2] < .01) && (diff[2] > -.01)))
		return HPK_VECTORS_OPPOSITE;
	return HPK_VECTORS_OTHER;
}

static float get_parametric_angle_from_axis_origin_and_directions_and_coordinate(
											const double* center,
											const double* major_direction,
											const double* minor_direction,
											const double* coordinate,
											const double* radii)
{
	/* one way to get this angle is to determine the angle between the major axis and the 
	   point on the ellipse which is given by the value coordinate (we are to find the parametric
	   angle of this coordinate, i.e. if this start or end point coincides with the major axis
	   then the return value will be zero.  In HOOPS this angle is parametrized between zero and
	   one  instead of zero to 2*pi so if the start or end point given by "coordinate" coincides
	   with the minor axis then the return value should be .25 */
	/* determining this angle information fully (to determine the correct quadrant, etc, will be
	   assisted by also determining the angle between the _minor_ axis and the "coordinate." */

	double coord_direction[3];
	double dot;
	double majorangle = 0.0;
	double minorangle = 0.0;
    double adjusted;
	double halfpi = HP_PI/2.0;
	double twopi = HP_PI*2.0;
	double pi = HP_PI;

	/* make coord_dirction equal coordinate minus center */
	coord_direction[0] = coordinate[0] - center[0];
	coord_direction[1] = coordinate[1] - center[1];
	coord_direction[2] = coordinate[2] - center[2];

	/* assuming major and minor directions are already normalized */
	verify_normalized(major_direction);
	verify_normalized(minor_direction);
	normalize_vector(coord_direction);

	/* get dot product, let's do this in double precision rather than use HOOPS routines */
	dot = dot_product(major_direction, coord_direction);
	
	/* the acos function doesn't deal well with values outside of range -1, 1 */
	if (dot < -1.01)
		assert(0);
	else if (dot <= -1.0)
		majorangle = pi;
	else if (dot > 1.01)
		assert(0);
	else if (dot >= 1.0)
		majorangle = 0.0;
	else
		majorangle = acos(dot);
	/* acos returns a value between zero and pi */

	dot = dot_product(minor_direction, coord_direction);
	
	if (dot < -1.01)
		assert(0);
	else if (dot <= -1.0)
		minorangle = pi;
	else if (dot > 1.01)
		assert(0);
	else if (dot >= 1.0)
		minorangle = 0.0;
	else
		minorangle = acos(dot);


	if (majorangle < halfpi)
	{
		// This angle is world angle, but we need the angle on to the
		// circum-scribing the ellipse. Apply the correction - Rajesh B 31-Jan-2000
		double tan_major = tan(majorangle);
			// testing for NAN
		if( (tan_major != tan_major)  || (fabs(tan_major) > 1000) )	// this is tan of 90 or 270 deg or near to those within 0.5 deg
			adjusted = majorangle;
		else
			adjusted = atan (tan(majorangle) * radii[0]/radii[1]);

		if (minorangle >= halfpi)
		{
			/* we are in quadrant 4 */
			return (float)((twopi - adjusted)/twopi);
		}
		else
		{
			/* we are in quadrant 1 */			
			return (float)((adjusted/twopi) );
		}
	}
	else
	{
		// This angle is world angle, but we need the angle on to the
		// circum-scribing the ellipse. Apply the correction - Rajesh B 31-Jan-2000
		double tan_major = tan(majorangle);
		if( (tan_major != tan_major) || (fabs(tan_major) > 1000) )	// this is tan of 90 or 270 deg or near to those within 0.5 deg
			adjusted = majorangle;
		else
            adjusted = pi + atan (tan(majorangle) * radii[0]/radii[1]);

		/* majorangle >= halfpi */
		if (minorangle >= halfpi)
		{
			/* we are in quadrant 3 */
			return (float)((twopi - adjusted)/twopi);
		}
		else
		{
			/* we are in quadrant 2 */
			return (float)(adjusted/twopi);
		}
	}
}



void build_nurbs(float *vertices, float *knots, float *weights, int num_vertices, int num_knots)
{
	HC_KEY key;

	open_geom_segments();

  	int degree = num_knots - num_vertices - 1;
 	key = HC_KInsert_NURBS_Curve(degree, num_vertices, vertices,weights,knots,0.0, 1.0);
 	if (!g_no_mapping_mode)
	{
 		g_pMap->AddMapping(key, current_face_or_line_tag);
	}
 	close_geom_segments();
}



void build_ellipse(const double* geom)
{
	HC_KEY key;
	float center[3], major[3], minor[3];

	open_geom_segments();
 	get_center_from_center(center, geom);
	get_axis_endpoint_from_axis_origin_and_direction_and_length(major, geom, &geom[3], geom[9]);
	get_axis_endpoint_from_axis_origin_and_direction_and_length(minor, geom, &geom[6], geom[10]);


	// Inserting two elliptical arcs instead of one complete ellipse. 
	// This avoids the polygon filling of ellipses which we dont want
	// for edges and polygons - Rajesh B 31-Jan-2001
	//	key = HC_KInsert_Ellipse(center, major, minor);
	key = HC_KInsert_Elliptical_Arc(center, major, minor, 0.0f, 0.5f);
	if (!g_no_mapping_mode)
		g_pMap->AddMapping(key, current_face_or_line_tag);

	key = HC_KInsert_Elliptical_Arc(center, major, minor, 0.5f, 1.0f);
	if (!g_no_mapping_mode)
		g_pMap->AddMapping(key, current_face_or_line_tag);

//	assert((current_face_or_line_tag < MIN_COLORVALUE_KEY) || (current_face_or_line_tag >= MAX_COLORVALUE_KEY)); /* face tag must not overlap with our color tags */
//
//	assert(HC_Show_Existence_By_Key(current_face_or_line_tag, "self") == 0);
//	HC_Renumber_Key(key, current_face_or_line_tag, "global");
	close_geom_segments();
}
void build_partial_ellipse(const double* geom)
{
	float center[3], major[3], minor[3];
	float start, end, adjustedstart;
	HC_KEY key;
	get_center_from_center(center, geom);
	get_axis_endpoint_from_axis_origin_and_direction_and_length(major, geom, &geom[3], geom[9]);
	get_axis_endpoint_from_axis_origin_and_direction_and_length(minor, geom, &geom[6], geom[10]);
	start = get_parametric_angle_from_axis_origin_and_directions_and_coordinate(geom, &geom[3], &geom[6], &geom[11], &geom[9]);
	if (start == 1.0f)
		start = 0.0f;
	end = get_parametric_angle_from_axis_origin_and_directions_and_coordinate(geom, &geom[3], &geom[6], &geom[14], &geom[9]);
	if (end == 0.0f && start != 0.0f)
		end = 1.0f;
	if (start > end)
	{
		adjustedstart = start - 1.0f;
		assert(adjustedstart < end);
	}
	else
		adjustedstart = start;

	open_geom_segments();
	if (start > end)
	{
		// this elliptical arc crosses the major axis, which HOOPS does not permit.
		// unfortunately in this case we need to split the arc into 2 pieces.
		key = HC_KInsert_Elliptical_Arc(center, major, minor, start, 1.0f);
		if (!g_no_mapping_mode)
		{

//GH99
//			assert(!g_pMap->FindMapping(current_face_or_line_tag));
		g_pMap->AddMapping(key, current_face_or_line_tag);
		}

		key = HC_KInsert_Elliptical_Arc(center, major, minor, 0.0f, end);

		// We are mapping 2 HOOPS primitives to this entity; add a large constant value to the second entity.
		// we'll have more comments on this where the keys are used.
//GH99
//			assert(g_pMap->FindMapping(current_face_or_line_tag));
		if (!g_no_mapping_mode)
			g_pMap->AddMapping(key, current_face_or_line_tag);
		
	}
	else
	{
		assert(start <= end);
		key = HC_KInsert_Elliptical_Arc(center, major, minor, start, end);
//GH99
//			assert(!g_pMap->FindMapping(current_face_or_line_tag));
		if (!g_no_mapping_mode)
			g_pMap->AddMapping(key, current_face_or_line_tag);
	}
	close_geom_segments();
}

void build_circle(const double* geom)
{
	float point1[3], point2[3];
	double majAxis[ 3 ];
	double minAxis[ 3 ];
	int i;
	HC_KEY key;

	PK_VECTOR1_t vec, vec2, vec3;
	vec2.coord[0]=0.0;			//VC 8 complains about possible uninitialized variable use
	for (i=0; i<3; i++) 
	{
		vec.coord[ i ] = geom[ 3 + i ];
		vec2.coord[ i ] = 0.0;
	}
	normalize_vector( vec.coord );  // PK_VECTOR_perpendicular is very fussy about this.
	PK_VECTOR_perpendicular( vec, vec2, &vec3 );
	for (i=0; i<3; i++) majAxis[ i ] = vec3.coord[ i ];

	cross_product( &geom[3], majAxis, minAxis );// cross the circle axis with the "major axis" to get the "minor axis"

	open_geom_segments();

	get_axis_endpoint_from_axis_origin_and_direction_and_length(point1, geom, majAxis, geom[6]);
	get_axis_endpoint_from_axis_origin_and_direction_and_length(point2, geom, minAxis, geom[6]);

#ifdef HPBRIDGE_OLD_INSERT_CIRCLE_AS_TWO_ARCS
	// Here we insert circle as two arcs. This is because nobody thought that a circle could be 
	// inserted as a single ellipse (major=minor) instead. If you still liked it though... (Rajesh B 15-Sept-03)
	float point3[3], point4[3];

	reverse_vector(majAxis); // reversing the major axis will get us a third point on the circle
	get_axis_endpoint_from_axis_origin_and_direction_and_length(point3, geom, majAxis, geom[6]);
	reverse_vector(minAxis);  // reversing the minor axis will get us a fourth point on the circle
	get_axis_endpoint_from_axis_origin_and_direction_and_length(point4, geom, minAxis, geom[6]);
	
	// we cannot just insert a circle since a HOOPS circle is a FILLED entity.
	//	HC_Insert_Circle(point1, point2, point3);
	key = HC_KInsert_Circular_Arc(point1, point2, point3);
//	assert((current_face_or_line_tag < MIN_COLORVALUE_KEY) || (current_face_or_line_tag >= MAX_COLORVALUE_KEY)); /* face tag must not overlap with our color tags */
//
//	assert(HC_Show_Existence_By_Key(current_face_or_line_tag, "self") == 0);
//	HC_Renumber_Key(key, current_face_or_line_tag, "global");
//GH99
//	assert(!g_pMap->FindMapping(current_face_or_line_tag));
	if (!g_no_mapping_mode && key!=-1)
	{
/*		
		if (g_pMap->FindMapping(current_face_or_line_tag))
		{
			// *WARNING potential performance degradation as we erase
			// and re-render this geometry.  This is a likely sign that the
			// user is doing something wrong here.
			// *FIX we need to think about some way to generate errors and
			// warnings from within this integration.
			HP_Delete_Entity_Geometry(1, &current_face_or_line_tag);
		}
		*/
		g_pMap->AddMapping(key, current_face_or_line_tag);
	}
	key = HC_KInsert_Circular_Arc(point3, point4, point1);
	assert(current_face_or_line_tag < MIN_COLORVALUE_KEY); /* face tag must not overlap with our color tags */

	// We are mapping 2 HOOPS primitives to this entity; add a large constant value to the second entity.
	// we'll have more comments on this where the keys are used.
//	assert(HC_Show_Existence_By_Key(current_face_or_line_tag + MAX_COLORVALUE_KEY, "self") == 0);
//	HC_Renumber_Key(key, current_face_or_line_tag + MAX_COLORVALUE_KEY, "global");
	if (!g_no_mapping_mode && key!=-1)
	{
		assert(g_pMap->FindMapping(current_face_or_line_tag));
		g_pMap->AddMapping(key, current_face_or_line_tag);
	}
#else
	// Circles are no more inserted as two arcs, but instead as an elliptical arc (from 0 to 1 and 
	// major=minor) (Rajesh B 15-Sept-03)
	float center[3];
 	get_center_from_center(center, geom);
	key = HC_KInsert_Elliptical_Arc(center, point1, point2, 0.0f, 1.0f);
	if (!g_no_mapping_mode && key!=-1)
	{
		assert(!g_pMap->FindMapping(current_face_or_line_tag));
		g_pMap->AddMapping(key, current_face_or_line_tag);
	}
#endif //HPBRIDGE_OLD_INSERT_CIRCLE_AS_TWO_ARCS


	close_geom_segments();
}

void build_partial_circle(const double* geom)
{
	float point1[3], point2[3], point3[3];
	double middle[3];
	double majAxis[ 3 ];
	double minAxis[ 3 ];
	double triangleNormal[ 3 ];
	unsigned int result;
	double zeroVector[ 3 ];
	HC_KEY key;

	zeroVector[0] = 0.0;
	zeroVector[1] = 0.0;
	zeroVector[2] = 0.0;

/* given start & end of the circle, we then need to determine whether the angle between these
   points on the circle is greater or less than 180 degrees.  The circle is drawn clockwise 
   from start to end as viewed from along the given circle axis.

   Once we know that, then it is not difficult to come up with a third point on the circular
   arc, which we need to generate for HOOPS.  Simply find the midpoint of the line segment
   between the start & end points of the circle, build a line segment from the center of 
   the circle to that point, and then extend that line segment out so that its length is 
   equal to the radius of the circle.

*/
	/* assert that the axis vector is normalized; we depend on this later */
	verify_normalized(&geom[3]);

	point1[0] = (float) geom[7];
	point1[1] = (float) geom[8];
	point1[2] = (float) geom[9];
	
	/* let's call the vector from the origin toward the start point the "major axis" */
	majAxis[0] = geom[7] - geom[0];
	majAxis[1] = geom[8] - geom[1];
	majAxis[2] = geom[9] - geom[2];
	normalize_vector(majAxis);
	
	point3[0] = (float) geom[10];
	point3[1] = (float) geom[11];
	point3[2] = (float) geom[12];

	/* let's call the vector from the origin toward the end point the "minor axis" */
	minAxis[0] = geom[10] - geom[0];
	minAxis[1] = geom[11] - geom[1];
	minAxis[2] = geom[12] - geom[2];
	normalize_vector(minAxis);

	/* set middle to be the midpoint of the line segment between the start and end points */
	middle[0] = (geom[7] + geom[10]) / 2.0; 
	middle[1] = (geom[8] + geom[11]) / 2.0; 
	middle[2] = (geom[9] + geom[12]) / 2.0; 
	
	/* subtract the circle origin from middle, which will make it a vector from the center to that point */
	middle[0] = middle[0] - geom[0];
	middle[1] = middle[1] - geom[1];
	middle[2] = middle[2] - geom[2];

	/* If the middle vector's longest component is less than .4% (I've also tried .01 and .001, 
	 *  both of which seem to work fine) of the radius long, we have a precision problem */
	if (are_vectors_within_tolerance(middle, zeroVector, .004 * geom[6]))
	{
		/* we have an exact semicircle, need to handle this case separately because
		   we can't accurately normalize a near-zero length vector */
	    /* take the cross-product of the circle axis with the "major axis" to yield a vector
		   pointing towards a 90 degree rotation clockwise from the "major axis".*/
		/* need to reverse the major axis vector to achieve this result */
		reverse_vector(majAxis);
		cross_product(majAxis, &geom[3], middle); 

	}
	else
	{
	/* determine whether the radial angle between the start and end points is greater than
	   or less than 180 degrees */
	/* the method we will use to do that will be to generate a normal from the triangle 
	   formed by the center of the circle and the start and end points.  This normal will either
	   be the same as or opposite to the circle normal.  If the normal is the same, then 
	   the angle will be > 180 degrees, and we will reverse the "middle" normal to come up 
	   with the vector pointing towards the point in the middle of the arc.
	   */
	/* need to reverse the major axis vector to achieve this result */

		reverse_vector(majAxis);
		cross_product(majAxis, minAxis, triangleNormal);
		normalize_vector(triangleNormal);
		result = compare_vectors(triangleNormal, &geom[3]);
		if (result == HPK_VECTORS_SAME)
		{
			reverse_vector(middle);
		}
		else if (result == HPK_VECTORS_OPPOSITE)
		{
			/* don't need to do anything */
		}
		else
		{
			/* the design of this algorithm isn't working */
			assert(0);
		}
	}

	/* normalize that vector so its length will be 1.0 */
	normalize_vector(middle);

	/* multiply the vector by the radius so it will now reach the perimeter of the circle. */

	middle[0] *= geom[6];
	middle[1] *= geom[6];
	middle[2] *= geom[6];

	point2[0] = (float) (geom[0] + middle[0]);
	point2[1] = (float) (geom[1] + middle[1]);
	point2[2] = (float) (geom[2] + middle[2]);

	open_geom_segments();
	key = HC_KInsert_Circular_Arc(point1, point2, point3);
//		assert((current_face_or_line_tag < MIN_COLORVALUE_KEY) || (current_face_or_line_tag >= MAX_COLORVALUE_KEY)); /* face tag must not overlap with our color tags */
//
//		assert(HC_Show_Existence_By_Key(current_face_or_line_tag, "self") == 0);
//		HC_Renumber_Key(key, current_face_or_line_tag, "global");
//GH99
//		assert(!g_pMap->FindMapping(current_face_or_line_tag));
		if (key!=-1)
		{
			if (!g_no_mapping_mode)
				g_pMap->AddMapping(key, current_face_or_line_tag);
		}
	close_geom_segments();
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: GOSGMT

History:

  May 1990 - reformatted for example frustrum code
  Oct 1994 - return CONTIN

Description:

  Open Pixel Data - dummy routine - return code for 'continue, no errors'.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
extern DLLEXPORT void GOSGMT( const int* segtyp, const int* ntags, const int* tags,
                    const int* ngeom, const double* geom, const int* nlntp,
                    const int* lntp, int* ifail)
{
	int i;
	int numpoints;
    *ifail = CONTIN;
    switch( *segtyp )
    {        
	case SGTPSI:							//GH99 Silhouette edges and normal edges are handled the same
	case SGTPED:
		current_face_or_line_tag = tags[0];
		//printf("Edge\n");
		switch(lntp[1])
		{
		case L3TPRN:
		{
			//printf("rational nurbs curve\n");

 				int vertex_num = lntp[9];
				int knot_num = lntp[10];

				float *vertices = new float[vertex_num*3];
				float *knots = new float[knot_num];
				float *weights = new float[vertex_num];
				int n = 0;
				for (i=0;i<vertex_num*4;i+=4)
				{
					vertices[n++] = (float)geom[i];
					vertices[n++] = (float)geom[i + 1];
					vertices[n++] = (float)geom[i + 2];
					weights[i/4] = (float)geom[i + 3];
				}
				for (i=0;i<knot_num;i++)
					knots[i]=(float)geom[i+4*vertex_num];
				build_nurbs(vertices,knots, weights, vertex_num, knot_num);
				delete [] vertices;
				delete [] knots;
				delete [] weights;
				total_face_points = 0;
			}	 
			break;
		case L3TPNC:
			{
			//printf("non rational nurbs curve\n");

 				int vertex_num = lntp[9];
				int knot_num = lntp[10];

				float *vertices = new float[vertex_num*3];
				float *knots = new float[knot_num];
				for (i=0;i<vertex_num*3;i++)
					vertices[i] = (float)geom[i];
				for (i=0;i<knot_num;i++)
					knots[i] = (float)geom[i+3*vertex_num];
				build_nurbs(vertices,knots, 0, vertex_num, knot_num);
				delete [] vertices;
				delete [] knots;
				total_face_points = 0;
			}
			break;
		case L3TPCC:
			//printf("Complete circle\n");
			assert(*ngeom == 7);
			build_circle(geom);
			break;
		case L3TPEL:
			//printf("Partial ellipse\n");
			assert(*ngeom == 17);
			build_partial_ellipse(geom);
			break;
		case L3TPCE:
			//printf("Complete ellipse\n");
			build_ellipse(geom);
			assert(*ngeom == 11);
			break;
		case L3TPPY:
			//printf("Polyline\n");

			total_face_points = *ngeom; // ngeom is number of vertices exactly, so don't cut in half.

			EnsurePointsAllocated(*ngeom, &allocated_face_points, &face_points);

			for (i = 0; i < (*ngeom)*3; i++)
				face_points[i] = (float) geom[i];

			build_line();
			total_face_points = 0;

			break;

		case L3TPSL:
			//printf("Straight line\n");

			assert(*ngeom == 9);
			total_face_points = 2;
			assert(total_face_points == 2);

			EnsurePointsAllocated(total_face_points, &allocated_face_points, &face_points);

			for (i = 0; i < total_face_points*3; i++)
				face_points[i] = (float) geom[i];

			build_line();
			total_face_points = 0;

			break;
		case L3TPCI:
			//printf("Partial circle\n");
			assert(*ngeom == 13);
			build_partial_circle(geom);
			break;
		case ERNOGO:
			//printf("Unspecified error\n");
			break;
		case ERRUBB:
			//printf("Rubber entity (no geometry attached)\n");
			break;
		case ERSANG:
			//printf("Surface angular tolerance too small\n");
			break;
		case ERSDIS:
			//printf("Surface distance tolerance too small\n");
			break;
		case ERCANG:
			//printf("Curve angular tolerance too small\n");
			break;
		case ERCDIS:
			//printf("Curve distance tolerance too small\n");
			break;
		case ERCLEN:
			//printf("Chord length tolerance too small\n");
			break;
		case ERFWID:
			//printf("Facet width tolerance too small\n");
			break;
		default:
			//printf("unexpected geometry type %d", lntp[0]);
			break;

		}
		break;  
    case SGTPPH:
		//printf("Planar hatch-line\n");
		break;
	case SGTPRH:
		//printf("Radial hatch-line\n");
		break;

	case SGTPRU:
	//	printf("Rib line\n");
		break;
	case SGTPBB:
	//	printf("Blend-boundary line\n");
		break;
	case SGTPPL:
	//	printf("Parametric hatch-line\n");
		break;
    case SGTPFT:
		if (tags[0] != current_face_or_line_tag)
		{
//			if (total_face_points > 0)
//				build_shell();
//			total_face_points = 0; 
//			total_face_list_count = 0;
			current_face_or_line_tag = tags[0];
		}
		switch(lntp[1])
		{
		case L3TPFV:

		//	printf("facet has no normals, error\n");
			break;
		case L3TPPY:
			// if there is a shell being built, finish up now, it's time for a polyline.
//			if (total_face_points > 0)
//			{
//				build_shell();
//				total_face_points = 0; 
//				total_face_list_count = 0;
//			}
			total_face_points = *ngeom; // ngeom is number of vertices exactly, so don't cut in half.

			EnsurePointsAllocated(*ngeom, &allocated_face_points, &face_points);

			for (i = 0; i < total_face_points*3; i++)
				face_points[i] = (float) geom[i];

			build_line();
			total_face_points = 0;

			break;

		case L3TPFN:
			if (tags[0] != current_face_or_line_tag)
			{
				// we've encountered a new face tag, build the old face into a shell 
				// and start a new one
//				if (total_face_points > 0)
//				{
//					build_shell();
//				}
				//float points[3 * MAX_POINTS];
				//float normals[3 * MAX_POINTS];
				//int face_list[MAX_POINTS + 1];
//				total_face_points = 0; 
//				total_face_list_count = 0;
				current_face_or_line_tag = tags[0];
			}

			numpoints = (*ngeom)/2; // ngeom is number of vertices PLUS normals, so cut in half.

			EnsurePointsAllocated(numpoints + total_face_points, &allocated_face_points, &face_points);
			EnsureListAllocated(total_face_list_count + numpoints + 1);

			for (i = 0; i < numpoints*3; i++)
			{
				face_points[total_face_points*3 + i] = (float) geom[i];
				normals[total_face_points*3 + i] = (float) geom[(*ngeom/2)*3 + i];
			}

			face_list[total_face_list_count] = numpoints; // number of vertices in this polygon 
			for (i = 1; i <= numpoints; i++)
			{
				face_list[total_face_list_count + i] = total_face_points + i-1;
			}
			total_face_points += numpoints;
			total_face_list_count = total_face_list_count + numpoints + 1;
				
				
			break;

		default:
			//printf("UNEXPECTED geometry type in output-face\n");
			break;
		}

		break;

	case SGTPER:
		//printf("Error segment\n");
		break;
	case SGTPGC:
		//printf("Geometry:  Curve\n");
		break;
	case SGTPGS:
		//printf("Geometry:  Surface\n");
		break;
	case SGTPGB:
		//printf("Gemetry:   Surface boundary\n");
		break;

    case SGTPMF:
		//printf("Mangled Facet\n");
		break;
	case SGTPVT:
		//printf("Visibility Segment\n");
		break;
	case SGTPTS:
		//printf("Facet strip\n");
		switch(lntp[1])
		{
		case L3TPTN:
			//GH99
			//printf("Processing facet strip.\n");

 
			if (tags[0] != current_face_or_line_tag)
				current_face_or_line_tag = tags[0];
 
			numpoints = (*ngeom)/2; // ngeom is number of vertices PLUS normals, so cut in half.

			EnsurePointsAllocated(numpoints + total_face_points, &allocated_face_points, &face_points);
			EnsureListAllocated(total_face_list_count + 4 * ( numpoints - 2 ));		//every face consists of 4 entries in the list

			for (i = 0; i < numpoints*3; i++)
			{
				face_points[total_face_points*3 + i] = (float) geom[i];
				normals[total_face_points*3 + i] = (float) geom[(*ngeom/2)*3 + i];
			}

			for (i=0;i<numpoints-2;i++)
			{
				face_list[total_face_list_count+i*4] = 3; // number of vertices in this polygon 

				//every second triangle is reversed			
				if (i%2)
				{
					face_list[total_face_list_count + i * 4 + 1] = total_face_points + i + 2;
					face_list[total_face_list_count + i * 4 + 2] = total_face_points + i + 1;
					face_list[total_face_list_count + i * 4 + 3] = total_face_points + i;
				}
				else
				{	
					face_list[total_face_list_count + i * 4 + 1] = total_face_points + i;
					face_list[total_face_list_count + i * 4 + 2] = total_face_points + i + 1;
					face_list[total_face_list_count + i * 4 + 3] = total_face_points + i + 2;				
				}
 
			}
 			total_face_points += numpoints;
			total_face_list_count = total_face_list_count + 4 * (numpoints - 2);				
			break;
		default:
			//printf("UNEXPECTED geometry type in output-facet-strip\n");
			break;
		}
		
		break;


	case SGTPVP:
		//printf("Parametrised Visiblity Segment\n");
		break;

	default:
		//printf("Unsupported segment type: %d\n", *segtyp);
		break;
	}
}                   



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: UCOPWR ( registered as UCOPWR )

Description:

Opens unicode file to be written and writes to it the standard file header.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/


extern	int UCOPWR( const int guise, const int format, const PK_UCHAR_t * name,
		const char * pd2hdr, int *strid )
    {
	int namelen;
	int pd2len;

	H_UTF16 name_utf16;
	name_utf16.encodedText<PK_UCHAR_t>(name);
	H_WCS name_wcs(name_utf16);

	wchar_t   keyname[max_namelen+1];  /* holds key + null char    */
    wchar_t  filename[max_namelen+1];  /* holds key + extension    */

    FILE *stream;
    file_p file_ptr;

	int ifail;
    ifail = FR_unspecified;
    *strid = null_strid;


	namelen = name_wcs.length();
	pd2len = strlen(pd2hdr);

    if (file_count == max_open_files)
      {
      ifail = FR_open_fail;
      return ifail;
      }

    wcsncpy(  keyname, name_wcs.encodedText(), namelen );
    keyname[namelen]  = end_of_string_c;

    wcsncpy( filename, name_wcs.encodedText(), namelen );
    filename[namelen] = end_of_string_c;

    if ( guise == FFCSCH )
        {
        /* add (and decode) a prefix to the filename   */
        extend_schema_unicode_filename(filename);
        }

    {
	int dd = is_extension_present_u( filename);
	if( dd == 0 )  
	{
		/* add the file extension */
		wchar_t const * gui  = filetype_guise_string_unicode( guise );
		wcscat( filename, gui );
		if( guise != FFCXMO && guise != FFCDBG )
		  {
		  wchar_t const * fmt = filetype_format_unicode_string( format );
		  wcscat( filename, fmt );
		  }
		}
	}

    check_valid_unicode_filename( filename, &ifail );
    if ( ifail != FR_no_errors )
      {
      return ifail;
      }

    /* open file for writing */
    //stream = fopen( filename, g_fopen_mode_write );
    stream = wfopen( filename, g_fopen_mode_write_unicode );

	if (stream == 0 ) 
      {
		ifail = FR_open_fail;
      return ifail;
      }

    new_open_file_unicode( stream, guise, format, write_access,
                  filename, keyname, &file_ptr, &ifail );
    if ( ifail != FR_no_errors )
      {
      return ifail;
      }

    if ( guise == FFCDBG )
		write_xml_header( file_ptr, pd2hdr, pd2len, &ifail );
	else
		write_header( file_ptr, pd2hdr, pd2len, &ifail );

    if ( ifail != FR_no_errors )
      {
      return ifail;
      }

    *strid = file_ptr->strid;
    ifail = FR_no_errors;

	return ifail;
    }



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Function: OpenReadUnicodeFrustrumFile ( registered as UCOPRD )

Description:

  Opens a file for read. A file extension is added to show the guise
  and format of the file. If requested, all the line containing the file
  header will be skipped.

  This is a unicode version of OpenReadFrustrumFile

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

extern int UCOPRD( const int guise, const int format, const PK_UCHAR_t * name, const PK_LOGICAL_t skiphd, int* strid)
    {
	int namelen;

	H_UTF16 name_utf16;
	name_utf16.encodedText<PK_UCHAR_t>(name);
	H_WCS name_wcs(name_utf16);

	wchar_t   keyname[max_namelen+1];  /* holds key + null char    */
    wchar_t  filename[max_namelen+1];  /* holds key + extension    */

    FILE *stream;
    file_p file_ptr;

    int ifail = FR_unspecified;
    *strid = null_strid;
	namelen = name_wcs.length();

    /* check that limit hasnt been reached */
    if (file_count == max_open_files)
      {
      ifail = FR_open_fail;
      return ifail;
      }

    wcsncpy(  keyname, name_wcs.encodedText(), namelen );
    keyname[namelen]  = end_of_string_unicode_c;

    wcsncpy( filename, name_wcs.encodedText(), namelen );
    filename[namelen] = end_of_string_unicode_c;

    if ( guise == FFCSCH )
        {
			// add (and decode) a prefix to the filename 
			extend_schema_unicode_filename(filename);
        }

    {
		
	int dd = is_extension_present_u( filename);	

	// before we go appending an extension, see if the file exists without one
	FILE *test_stream = wfopen( filename, g_fopen_mode_read_unicode_binary );
	if ( test_stream )
	{
		dd = 1;
		fclose(test_stream);
	}

	if( dd == 0){ // there is no extension *and* no file exists with the extension-less name so append the default extension
		wchar_t const * gui  = filetype_guise_string_unicode( guise);
		wcscat( filename, gui );
		if( guise != FFCXMO )
		  {
		  wchar_t const * fmt = filetype_format_unicode_string( format );
		  wcscat( filename, fmt );
		  }
		}
	}


    check_valid_unicode_filename( filename, &ifail );
    if ( ifail != FR_no_errors )
      {
      return ifail;
      }

    /* open file for reading */
    if (format == FFBNRY)
      /* if binary file is opened with "r" instead of "rb" reading will fail */
      /* with end-of-file error, if it reads byte with value equal to CTRL-Z */
	    stream = wfopen( filename, g_fopen_mode_read_unicode_binary );
    else
		stream = wfopen( filename, g_fopen_mode_read_unicode_text );

    if (stream == 0)
      {
      ifail = FR_not_found;
      return ifail;
      }

    new_open_file_unicode( stream, guise, format, read_access,
                  filename, keyname, &file_ptr, &ifail );

    if ( ifail != FR_no_errors )
      {
      return ifail;
      }


    if (skiphd == FFSKHD)
      {
      skip_header( file_ptr, &ifail );
      if ( ifail != FR_no_errors )
        {
        return ifail;
        }
      }

    *strid = file_ptr->strid;

    ifail = FR_no_errors;

	return ifail;
}
