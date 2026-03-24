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
// $Header: /files/homes/master/cvs/hoops_master/hoops_stream/source/HStreamFileToolkit.cpp,v 1.309 2010-10-22 19:24:17 trask Exp $
//


#include "HStream.h"
#include "HOpcodeShell.h"
#include "HPolyPoly.h"
#include "BInternal.h"


#define ASSERT(x)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


HStreamFileToolkit::HStreamFileToolkit() {
	m_unnamed_segments = null;

#ifndef HSTREAM_READONLY
	m_segment_processor = new Internal_Segment_Processor;

	m_pending_tags = null;
	m_texture_list = null;
	m_non_segment_revisits = false;
	m_revisit_offset = 0;
	m_thumbnail = null;
	m_must_delete = null;

	m_excluded_segments = null;
	m_excluded_count = 0;

	m_prepend_root = 0;

	m_local_attributes = 0;

	m_revisit_state = HStreamFileToolkit::Nothing;

#endif

	SetOpcodeHandler (TKE_Font,					new HTK_Font);
	SetOpcodeHandler (TKE_Texture,				new HTK_Texture);
	SetOpcodeHandler (TKE_Glyph_Definition,		new HTK_Glyph_Definition);
	SetOpcodeHandler (TKE_Named_Style_Def,		new HTK_Named_Style_Def);
	SetOpcodeHandler (TKE_Line_Style,			new HTK_Line_Style);

	SetOpcodeHandler (TKE_Open_Segment,			new HTK_Open_Segment);
	SetOpcodeHandler (TKE_Close_Segment,		new HTK_Close_Segment);
	SetOpcodeHandler (TKE_Reopen_Segment,		new HTK_Reopen_Segment);
	SetOpcodeHandler (TKE_Include_Segment,		new HTK_Referenced_Segment (TKE_Include_Segment));
	SetOpcodeHandler (TKE_Style_Segment,		new HTK_Referenced_Segment (TKE_Style_Segment));
	SetOpcodeHandler (TKE_Named_Style,			new HTK_Referenced_Segment (TKE_Named_Style));
	SetOpcodeHandler (TKE_Repeat_Object,		new HTK_Instance);

	SetOpcodeHandler (TKE_Renumber_Key_Global,	new HTK_Renumber (TKE_Renumber_Key_Global));
	SetOpcodeHandler (TKE_Renumber_Key_Local,	new HTK_Renumber (TKE_Renumber_Key_Local));
	SetOpcodeHandler (TKE_Priority,				new HTK_Renumber (TKE_Priority));
	SetOpcodeHandler (TKE_Bounding,				new HTK_Bounding (TKE_Bounding));
	SetOpcodeHandler (TKE_Bounding_Info,		new HTK_Bounding (TKE_Bounding_Info));

	SetOpcodeHandler (TKE_Delete_Object,		new HTK_Delete_Object);

	SetOpcodeHandler (TKE_Callback,				new HTK_Callback);
	SetOpcodeHandler (TKE_Camera,				new HTK_Camera);
	SetOpcodeHandler (TKE_View,					new HTK_Camera (TKE_View));
	SetOpcodeHandler (TKE_Window,				new HTK_Window);
	SetOpcodeHandler (TKE_Clip_Rectangle,		new HTK_Clip_Rectangle);
	SetOpcodeHandler (TKE_Clip_Region,			new HTK_Clip_Region);
	SetOpcodeHandler (TKE_Visibility,			new HTK_Visibility);
	SetOpcodeHandler (TKE_Selectability,		new HTK_Selectability);
	SetOpcodeHandler (TKE_Color,				new HTK_Color);
	SetOpcodeHandler (TKE_Color_RGB,			new HTK_Color_RGB);
	SetOpcodeHandler (TKE_Color_By_Value,		new HTK_Color_By_Value);
	SetOpcodeHandler (TKE_Color_By_Index,		new HTK_Color_By_Index (TKE_Color_By_Index));
	SetOpcodeHandler (TKE_Color_By_Index_16,	new HTK_Color_By_Index (TKE_Color_By_Index_16));
	SetOpcodeHandler (TKE_Color_By_FIndex,		new HTK_Color_By_FIndex);
	SetOpcodeHandler (TKE_Color_Map,			new HTK_Color_Map);
	SetOpcodeHandler (TKE_Conditional_Action,	new HTK_Conditional_Action);
	SetOpcodeHandler (TKE_Conditions,			new HTK_Conditions);
	SetOpcodeHandler (TKE_Modelling_Matrix,		new HTK_Matrix (TKE_Modelling_Matrix));
	SetOpcodeHandler (TKE_Texture_Matrix,		new HTK_Matrix (TKE_Texture_Matrix));
	SetOpcodeHandler (TKE_Face_Pattern,			new HTK_Enumerated (TKE_Face_Pattern));
	SetOpcodeHandler (TKE_Window_Pattern,		new HTK_Enumerated (TKE_Window_Pattern));
	SetOpcodeHandler (TKE_Marker_Symbol,		new HTK_Named (TKE_Marker_Symbol));
	SetOpcodeHandler (TKE_Text_Alignment,		new HTK_Enumerated (TKE_Text_Alignment));
	SetOpcodeHandler (TKE_Window_Frame,			new HTK_Enumerated (TKE_Window_Frame));
	SetOpcodeHandler (TKE_Handedness,			new HTK_Enumerated (TKE_Handedness));
	SetOpcodeHandler (TKE_Edge_Pattern,			new HTK_Named (TKE_Edge_Pattern));
	SetOpcodeHandler (TKE_Line_Pattern,			new HTK_Named (TKE_Line_Pattern));
	SetOpcodeHandler (TKE_Edge_Weight,			new HTK_Size (TKE_Edge_Weight));
	SetOpcodeHandler (TKE_Line_Weight,			new HTK_Size (TKE_Line_Weight));
	SetOpcodeHandler (TKE_Marker_Size,			new HTK_Size (TKE_Marker_Size));
	SetOpcodeHandler (TKE_Rendering_Options,	new HTK_Rendering_Options);
	SetOpcodeHandler (TKE_Geometry_Options,		new HTK_Geometry_Options);
	SetOpcodeHandler (TKE_Heuristics,			new HTK_Heuristics);
	SetOpcodeHandler (TKE_Text_Font,			new HTK_Text_Font);
	SetOpcodeHandler (TKE_Text_Spacing,			new HTK_Size (TKE_Text_Spacing));
	SetOpcodeHandler (TKE_Text_Path,			new HTK_Point (TKE_Text_Path));
	SetOpcodeHandler (TKE_Unicode_Options,		new HTK_Unicode_Options);
	SetOpcodeHandler (TKE_User_Options,			new HTK_User_Options);
	SetOpcodeHandler (TKE_User_Index,			new HTK_User_Index);
	SetOpcodeHandler (TKE_User_Index_Data,		new HTK_User_Index_Data);
	SetOpcodeHandler (TKE_User_Value,			new HTK_User_Value);
	SetOpcodeHandler (TKE_Streaming_Mode,		new HTK_Streaming);

	SetOpcodeHandler (TKE_Circle,				new HTK_Circle (TKE_Circle));
	SetOpcodeHandler (TKE_Circular_Arc,			new HTK_Circle (TKE_Circular_Arc));
	SetOpcodeHandler (TKE_Circular_Chord,		new HTK_Circle (TKE_Circular_Chord));
	SetOpcodeHandler (TKE_Circular_Wedge,		new HTK_Circle (TKE_Circular_Wedge));
	SetOpcodeHandler (TKE_Sphere,				new HTK_Sphere);
	SetOpcodeHandler (TKE_Cylinder,				new HTK_Cylinder);
	SetOpcodeHandler (TKE_Ellipse,				new HTK_Ellipse (TKE_Ellipse));
	SetOpcodeHandler (TKE_Elliptical_Arc,		new HTK_Ellipse (TKE_Elliptical_Arc));
	SetOpcodeHandler (TKE_Grid,					new HTK_Grid);
	SetOpcodeHandler (TKE_Image,				new HTK_Image);
	SetOpcodeHandler (TKE_Line,					new HTK_Line (TKE_Line));
	SetOpcodeHandler (TKE_Infinite_Line,		new HTK_Line (TKE_Infinite_Line));
	SetOpcodeHandler (TKE_Infinite_Ray,			new HTK_Line (TKE_Infinite_Ray));
	SetOpcodeHandler (TKE_PolyCylinder,			new HTK_PolyCylinder);
	SetOpcodeHandler (TKE_Polyline,				new HTK_Polypoint (TKE_Polyline));
	SetOpcodeHandler (TKE_Polygon,				new HTK_Polypoint (TKE_Polygon));
	SetOpcodeHandler (TKE_PolyPolyline,			new HTK_PolyPolypoint (TKE_PolyPolyline));
	SetOpcodeHandler (TKE_Marker,				new HTK_Point (TKE_Marker));
	SetOpcodeHandler (TKE_Distant_Light,		new HTK_Point (TKE_Distant_Light));
	SetOpcodeHandler (TKE_Local_Light,			new HTK_Point (TKE_Local_Light));
	SetOpcodeHandler (TKE_Spot_Light,			new HTK_Spot_Light);
	SetOpcodeHandler (TKE_Area_Light,			new HTK_Area_Light);
	SetOpcodeHandler (TKE_Shell,				new HTK_Shell);
	SetOpcodeHandler (TKE_Mesh,					new HTK_Mesh);
	SetOpcodeHandler (TKE_NURBS_Curve,			new HTK_NURBS_Curve);
	SetOpcodeHandler (TKE_NURBS_Surface,		new HTK_NURBS_Surface);
	SetOpcodeHandler (TKE_Cutting_Plane,		new HTK_Cutting_Plane);
	SetOpcodeHandler (TKE_Text,					new HTK_Text (TKE_Text));
	SetOpcodeHandler (TKE_Text_With_Encoding,	new HTK_Text (TKE_Text_With_Encoding));
	SetOpcodeHandler (TKE_LOD,					new HTK_LOD);
	SetOpcodeHandler (TKE_Reference,			new HTK_Reference);

	m_hoops_version = 0;
}


////////////////////////////////////////

HStreamFileToolkit::~HStreamFileToolkit() {
#ifndef HSTREAM_READONLY
	delete m_segment_processor;
	delete[] m_prepend_root;
	empty_lists();
#endif
}

void HStreamFileToolkit::empty_lists () alter {
	while (m_unnamed_segments != null) {
		Internal_Segment_List alter *       victim = m_unnamed_segments;
		m_unnamed_segments = victim->m_next;
		delete victim;
	}

#ifndef HSTREAM_READONLY
	while (m_pending_tags != null) {
		Internal_Pending_Tag alter *        victim = m_pending_tags;
		m_pending_tags = victim->m_next;
		delete victim;
	}

	while (m_texture_list != null) {
		Internal_Texture_List alter *       victim = m_texture_list;
		m_texture_list = victim->m_next;
		delete victim;
	}

	delete m_thumbnail;
	m_thumbnail = null;

	delete m_must_delete;
	m_must_delete = null;

	delete [] m_excluded_segments;
	m_excluded_segments = null;
	m_excluded_count = 0;
#endif

	BStreamFileToolkit::empty_lists();
}


void HStreamFileToolkit::Restart () alter {
	empty_lists();

#ifndef HSTREAM_READONLY
	m_local_attributes = 0;

	m_segment_processor->Reset();

	m_revisit_state = HStreamFileToolkit::Nothing;
#endif

	BStreamFileToolkit::Restart();
}

////////////////////////////////////////

void HStreamFileToolkit::ActivateContext (ID_Key key) {
	if (key != -1)
		HC_Open_Segment_By_Key (key);
}

void HStreamFileToolkit::DeactivateContext (ID_Key key) {
	if (key != -1)
		HC_Close_Segment ();
}


void HStreamFileToolkit::NewFileContext (ID_Key key) {
	if (key != -1) {
		HC_Open_Segment_By_Key (key);
		HC_Flush_Contents (".", "geometry, subsegments");
	}

	if (GetLogging() && GetLoggingOptions (TK_Logging_Segment_Names)) {
		char path[2048];
		HC_Show_Pathname_Expansion (".", path);
		LogEntry ("File loading into segment: ");
		LogEntry (path);
		LogEntry ("\n");
	}

	if (key != -1)
		HC_Close_Segment ();
}



void HStreamFileToolkit::validate_hoops_version() {
	char    version[32];
	char    *cp = version;

	HC_Show_System_Info ("Hoops version", version);

	m_hoops_version = 0;
	while (*cp) {
		if ('0' <= *cp && *cp <= '9')
			m_hoops_version = 10 * m_hoops_version + (*cp - '0');
		else if (*cp == '-')
			break;
		++cp;
	}
}

void HStreamFileToolkit::add_unnamed_segment (HC_KEY key) alter {
	Internal_Segment_List *         newseg;

	newseg = new Internal_Segment_List (key);
	newseg->m_next = m_unnamed_segments;
	m_unnamed_segments = newseg;
}

void HStreamFileToolkit::read_completed () alter {
	// fixup any unnamed segments we recorded
	while (m_unnamed_segments != null) {
		Internal_Segment_List alter *       victim = m_unnamed_segments;

		HC_Open_Segment_By_Key (victim->m_key);
			HC_Rename_Segment (".", "");
		HC_Close_Segment ();

		m_unnamed_segments = victim->m_next;
		delete victim;
	}
}

////////////////////////////////////////////////////////////////////////////////
// based on the format
static int const thumbnail_bytes_per_pixel[] = {
	3, 4
};

void HStreamFileToolkit::SetThumbnail (BBaseOpcodeHandler * handler) alter {
#ifndef HSTREAM_READONLY
	delete m_thumbnail;
	m_thumbnail = handler;
#else
    UNREFERENCED (handler);
#endif
}

void HStreamFileToolkit::SetThumbnail (int format, int width, int height, unsigned char const * data) alter {
#ifndef HSTREAM_READONLY
	TK_Thumbnail *	    tn = null;

	if (format != 0 && format != 1)
	Error ("invalid thumbnail format");
	else if (width < 1 || width > 256 || height < 1 || height > 256)
	Error ("invalid thumbnail size");
	else {
	tn = new TK_Thumbnail;

	tn->SetFormat (format);
	tn->SetSize (width, height);
	tn->SetBytes (width * height * thumbnail_bytes_per_pixel[format], data);
	}
	SetThumbnail (tn);
#else
    UNREFERENCED (format);
    UNREFERENCED (width);
    UNREFERENCED (height);
    UNREFERENCED (data);
#endif
}

////////////////////////////////////////////////////////////////////////////////
// simple for now, we can do stuff like sort & binary search if these start getting big
void HStreamFileToolkit::AddExcludedSegments (int count, HC_KEY const * keys) alter {
#ifndef HSTREAM_READONLY
	HC_KEY alter *		old_keys = m_excluded_segments;
	
	m_excluded_segments = new HC_KEY [m_excluded_count + count];
	if (old_keys != null) {
		memcpy (m_excluded_segments, old_keys, m_excluded_count*sizeof(HC_KEY));
		delete [] old_keys;
	}
	memcpy (&m_excluded_segments[m_excluded_count], keys, count*sizeof(HC_KEY));
	m_excluded_count += count;
#else
    UNREFERENCED (count);
    UNREFERENCED (keys);
#endif
}

bool HStreamFileToolkit::SegmentIsExcluded (HC_KEY key) const {
#ifndef HSTREAM_READONLY
	int					i;

	for (i=0; i<m_excluded_count; i++) {
		if (key == m_excluded_segments[i])
			return true;
	}
	return false;
#else
    UNREFERENCED (key);
	return true;
#endif
}

void HStreamFileToolkit::ClearExcludedSegments () alter {
#ifndef HSTREAM_READONLY
	delete [] m_excluded_segments;
	m_excluded_segments = null;
	m_excluded_count = 0;
#endif
}

////////////////////////////////////////////////////////////////////////////////

bool	HStreamFileToolkit::MatchPreviousExRef () const {
	wchar_t const *			filename = GetCurrentFile();
	Internal_ExRef_List *	prev = m_previous_exrefs;
	ID_Key					context = GetExternalReferenceContext();

	if (prev != null) do {
		if (!wcscmp (filename, prev->m_ref)) {	// same filename
			char	path[2048];

			HC_Open_Segment_By_Key (context);
				if (prev->m_context != context) {	// to be read into a different segment
					HC_Include_Segment_By_Key (prev->m_context);

					if (GetLogging() && GetLoggingOptions (TK_Logging_Segment_Names)) {
						HC_Open_Segment_By_Key (prev->m_context);
							HC_Show_Pathname_Expansion (".", path);
						HC_Close_Segment();
						LogEntry ("File already available in segment: ");
						LogEntry (path);
						LogEntry ("\n");
						HC_Show_Pathname_Expansion (".", path);
						LogEntry ("Including it into segment: ");
						LogEntry (path);
						LogEntry ("\n");
					}
				}
				else {
					if (GetLogging() && GetLoggingOptions (TK_Logging_Segment_Names)) {
						HC_Show_Pathname_Expansion (".", path);
						LogEntry ("File already loaded into current segment: ");
						LogEntry (path);
						LogEntry ("\n");
					}
				}
			HC_Close_Segment();

			return true;
		}
	} while ((prev = prev->m_next) != null);

	return false;
}
////////////////////////////////////////////////////////////////////////////////


#ifndef HSTREAM_READONLY

static char const * search_strings[] = {
	"styles, named styles",					// these need special handling the first time
	"everything, no styles, no named styles, no geometry, shells, meshes, no hardware resources",  // things we process first time
	"geometry, no shells, no meshes",           // things processed subsequent times
	"geometry"									// forced processing for references
};
static bool const search_reversal[] = {false, true, true, false};
static int const Revisit_Search_Point = 2;
static int const Force_Search_Point = 3;


Internal_Texture_List::Internal_Texture_List (char const * name, char const * image, HC_KEY key)
	: m_next (null), m_name (null), m_image (null), m_image_key (key) {
	m_name = new char [strlen (name)+1];
	strcpy (m_name, name);
	if (image != null) {
		m_image = new char [strlen (image)+1];
		strcpy (m_image, image);
	}
	m_do_write_image = true;
}

Internal_Texture_List::~Internal_Texture_List() {
	delete [] m_name;
	delete [] m_image;
}

////////////////////////////////////////

/* Three quick macros to help with sorting */
#define VAL(x) (-(*(x))->m_priority)  //negative to reverse sorting order
#define MEDIANOF3INDEX(a,b,c) (((a)>(b))?(((b)>(c))?(1):(((a)>(c))?(2):(0))):(((a)>(c))?(0):((b)>(c))?(2):(1)))
#define SWAP_REVISITS(a, b) {Internal_Revisit_Item *tmp = (a); (a) = (b); (b) = tmp;}


/* issorted
 * A quick utility to verify that an array is in fact sorted.  
 * FOR DEBUGGING ONLY
 */
bool HStreamFileToolkit::issorted_revisit (
	Internal_Revisit_Item  **ptr, 
	int                    count) 
{
	until (--count == 0) {
		if (VAL(ptr) > VAL(ptr + 1)) {
			return false;
		}
		else
			++ptr;
	}
	return true;
}


/* qsort_revisit
 * We use QuickSort here, but try to be intelligent about our choice of pivots.
 * We use the median of the start-, mid-, and end-point as our pivot.
 */
void HStreamFileToolkit::qsort_revisit (
	Internal_Revisit_Item **ileft,
	Internal_Revisit_Item **iright,
	int level) 
{
	if (level >= 16)
		return;
	if (iright - ileft == 1) {
		if (VAL(ileft) > VAL(iright))
		   SWAP_REVISITS(*ileft, *iright);
	}
	else if (ileft < iright) {
		Internal_Revisit_Item **left, **right;
		Internal_Revisit_Item **candidates[3];
		float   pivot;
		int     m3i;

		candidates[0] = left = ileft;                       /* left */
		candidates[1] = ileft + ((iright - ileft) / 2);   /* middle */
		candidates[2] = right = iright;                     /* right */

		/* find the best pivot and move it to the far right */
		m3i = MEDIANOF3INDEX(
			VAL(candidates[0]), 
			VAL(candidates[1]),
			VAL(candidates[2]) 
		);
		pivot = VAL(candidates[m3i]);
		SWAP_REVISITS(*candidates[m3i], *right);

		/* should be one higher and one lower */
		/* ASSERT((VAL(candidates[0]) >= pivot) || (VAL(candidates[1]) >= pivot)); */
		/* ASSERT((VAL(candidates[0]) <= pivot) || (VAL(candidates[1]) <= pivot)); */

		for (;;) {
			left--;
			while(VAL(++left) <= pivot) {
				if (left >= right) 
				   goto partition_done;
			}
			SWAP_REVISITS(*left, *right);
			/* ASSERT(VAL(left) < VAL(right)); */

			right++;
			while(VAL(--right) >= pivot) {
				if (left >= right) 
				   goto partition_done;
			}
			SWAP_REVISITS(*left, *right);
			/* ASSERT(VAL(left) < VAL(right)); */
		}
		partition_done:

		qsort_revisit(ileft, left - 1, level+1);
		qsort_revisit(left + 1,  iright, level+1);
#if 0
		// assertion not valid with level limit
		ASSERT(issorted_revisit(ileft, iright - ileft));
#endif
	}

} // end recursive function qsort_revisit

void HStreamFileToolkit::SetPrependRootSegment(const char * segment) {
	delete[] m_prepend_root;
	m_prepend_root=0;

	if (segment) {
		m_prepend_root = new char[strlen(segment)+1];
		strcpy(m_prepend_root, segment);
		if (m_prepend_root[strlen(m_prepend_root)-1] == '/')
			m_prepend_root[strlen(m_prepend_root)-1] = '\0';
	}
}


TK_Status HStreamFileToolkit::sort_revisit() {
	Internal_Revisit_Item *ptr;
	Internal_Revisit_Item **array;
	int i = 0, count = 0;

	if (m_revisit == null)
		return TK_Normal;

	m_non_segment_revisits = false;
	for (ptr = m_revisit; ptr != null; ptr = ptr->m_next) {
		count++;
		if (ptr->m_opcode != TKE_Reopen_Segment)
			m_non_segment_revisits = true;
	}
	array = new Internal_Revisit_Item *[count];
	if (array == null)
		return Error ();
	for (ptr = m_revisit; ptr != null; ptr = ptr->m_next) {
		array[i++] = ptr;
	}
	qsort_revisit(array, array + count - 1);
	for (i = 0; i < count - 1; i++) {
		array[i]->m_next = array[i+1];
	}
	array[count - 1]->m_next = null;
	m_revisit = array[0];
	delete [] array;

	return TK_Normal;
}


TK_Status HStreamFileToolkit::find_textures () {
	Internal_Texture_List *     ptr;
	Internal_Texture_List **    linker;
	char                        name[4096];
	char                        definition[4096];

	HC_Begin_Texture_Search ();
	while (HC_Find_Texture (name)) {
		char *      cp;

		HC_Show_Texture (name, definition);

		cp = definition;
		if (streqn (cp, "source=", 7)) {
			char *		cptr;
			char		quote;

			cp += 7;
			//find the end of the texture name
			quote = 0;
			cptr = cp;
			for (;;) {
				if (*cptr == '"' || *cptr == '`' || *cptr == '\'') {
					if (quote) {
						if (*cptr == quote) {
							if (cptr[1] == quote)
								/* doubling the active quote style acts as an escape
								 * sequence.  (e.g. "travis's texture" can also be expressed
								 * as 'travis''s texture') */
								cptr++;
							else
								quote = 0;
						}
					}
					else
						quote = *cptr;
				}
				else if (*cptr == ',') {
					if (!quote) {
						*cptr = '\0'; //truncate the string
						break;
					}
				} 
				else if (*cptr == '\0')
					break;
				cptr++; 
			}
		}
		else
			cp = null;

		ptr = new Internal_Texture_List (name, cp);
		ptr->m_next = m_texture_list;
		m_texture_list = ptr;
	}
	HC_End_Texture_Search ();

	if (m_texture_list != null) {
		char                    type[32];
		HC_KEY                  key;

		HC_Begin_Contents_Search ("/...", "images");
		while (HC_Find_Contents (type, &key)) {
			float               position[3];
			int                 size[2];
			char                fmt[4096];

			HC_Show_Image_Size (key, &position[0], &position[1], &position[2],
								fmt, &size[0], &size[1]);

			char *          cp = strchr (fmt, ',');

			if (cp != null) {
				cp += strlen (",name=");    // cp now points at actual image name

				Internal_Texture_List *     texture = m_texture_list;
				bool                        image_firsttime = true;

				do {
					if (streq (cp, texture->m_image)) {
						texture->m_do_write_image = image_firsttime;
						texture->m_image_key = key;
						image_firsttime = false;
					}
				} until ((texture = texture->m_next) == null);
			}
		}
		HC_End_Contents_Search ();
	}

	// remove textures that don't have an accessible image
	linker = &m_texture_list;
	while (*linker) {
		if ((*linker)->m_image_key == -1) {
			Internal_Texture_List *     victim = *linker;

			*linker = victim->m_next;
			delete victim;
		}
		else
			linker = &(*linker)->m_next;
	}

	return TK_Normal;
}

#endif  // HSTREAM_READONLY

TK_Status HStreamFileToolkit::tag (int variant) alter {
#ifndef HSTREAM_READONLY
	TK_Status           status = TK_Normal;
	int                 dummy, i;

	if (m_last_keys_used <= 0)
		return Error("attempt to tag something with an unspecified or nonexistent key");
	if (m_last_keys[0] == -1)
		return TK_Normal;

	if (variant != -1) {
		for(i = 0 ; i < m_last_keys_used ; i++) {
			// and now record the file offset to associate with the variant (if any)
			status = KeyToIndex (m_last_keys[i], dummy);  //ignore the value in dummy.  just make sure that we've seen this (or these) keys before
			if (status != TK_NotFound)
				AddVariant (m_last_keys[i], variant, m_position + m_offset);
			//else
			//    return Error("attempt to record variant of an as-yet unknown item");
		}
	}
	if (m_pending_tags == null || m_pending_tags->m_key != m_last_keys[0]) {
		// add "pending tag" if we haven't already
		Internal_Pending_Tag *      tag;

		tag = new Internal_Pending_Tag;
		tag->m_key = m_last_keys[0];
		tag->m_next = m_pending_tags;
		tag->m_variant = variant;
		if (m_last_keys_used > 1) {
			Internal_Key_Array *array = new Internal_Key_Array;
			array->m_count = m_last_keys_used;
			array->m_data = new HC_KEY[ m_last_keys_used ];
			memcpy(array->m_data, m_last_keys, m_last_keys_used * sizeof(HC_KEY));
			tag->m_array = array;
		}
		else
			tag->m_array = null;
		m_pending_tags = tag;
	}
#endif
    UNREFERENCED (variant);
	return TK_Normal;
}


static bool geometry_has_attributes (
	unsigned char		opcode,
	ID_Key				key) {

	switch (opcode) {
		case TKE_Marker:
		case TKE_Polyline: {
			char				options[1024];

			options[0] = '\0';
			HC_Show_Geometry_Options (key, options);
			if (options[0] != '\0')
				return true;
		}	nobreak;

		case TKE_Line:			case TKE_PolyPolyline:
		case TKE_Infinite_Line:	case TKE_Infinite_Ray:
		case TKE_Circular_Arc:	case TKE_Elliptical_Arc:	case TKE_NURBS_Curve:

		case TKE_Polygon:
		case TKE_Circle:		case TKE_Circular_Chord:	case TKE_Circular_Wedge:
		case TKE_Ellipse:
		case TKE_Sphere:		case TKE_Cylinder:		case TKE_NURBS_Surface:
		case TKE_Distant_Light:	case TKE_Local_Light:	case TKE_Spot_Light:	case TKE_Area_Light:
		case TKE_Cutting_Plane:
		case TKE_Image:			case TKE_Grid:
		case TKE_Text:			case TKE_Text_With_Encoding:
		case TKE_PolyCylinder:	// internal handling only of local attributes, not generic ones
		case TKE_Reference: {
			return  HC_Show_Existence_By_Key (key, "attributes, no geometry options") > 0;
		}	nobreak;

		case TKE_Shell:
		case TKE_Mesh:
			// have their own internal handling
			break;

		default:
			// ignore all non-geometry types
			break;
	}

	return false;
}



TK_Status HStreamFileToolkit::GenerateBuffer (char * b, int s, int alter & f, char const * start_segment) alter {
#ifndef HSTREAM_READONLY
	TK_Status           status = TK_Complete;
	bool                create_dictionary = GetWriteFlags(TK_Generate_Dictionary) &&
													!GetWriteFlags(TK_Suppress_LOD);

	if ((status = PrepareBuffer (b, s)) != TK_Normal)
		goto finish;

	switch (m_stage) {
		// Setup
		case 0: {
			// Note: header is not a real type of object, so we create & delete instead of looking up a handler
			if (m_current_object == m_default_object)
				m_current_object = new TK_Header;

			if ((status = m_current_object->Write (*this)) != TK_Normal)
				goto finish;

			delete m_current_object;
			m_current_object = null;

			m_stage++;
		}   nobreak;

		case 1: {
			if (m_current_object == null && m_thumbnail != null) {
				m_current_object = m_thumbnail;

				if ((status = m_current_object->Interpret (*this, -1)) != TK_Normal)
					goto finish;
			}

		if (m_current_object != null) {
			if ((status = m_current_object->Write (*this)) != TK_Normal)
				goto finish;
			m_current_object->Reset();
			m_current_object = null;
		}

			m_stage++;
		}   nobreak;

		case 2: {
			if (m_current_object == null) {
				m_current_object = opcode_handler (TKE_Bounding_Info);

				if ((status = m_current_object->Interpret (*this, -1)) != TK_Normal)
					goto finish;
			}

			if ((status = m_current_object->Write (*this)) != TK_Normal)
				goto finish;

			m_current_object->Reset();
			m_current_object = null;

			m_stage++;
		}   nobreak;

		case 3: {
			if (!GetWriteFlags (TK_Disable_Global_Compression)) {
				if (m_current_object == null) {
					m_current_object = opcode_handler (TKE_Start_Compression);
					m_current_object->Reset();
				}

				if ((status = m_current_object->Write (*this)) != TK_Normal)
					goto finish;

				m_current_object->Reset();
				m_current_object = null;
			}

			m_stage++;
			m_substage = 0; //prepare for the next case
		}   nobreak;

		// Prewalk
		case 4: {
			while(m_substage < m_prewalk_count) {
				if ((status = m_prewalk[m_substage]->Interpret (*this, -1)) != TK_Normal)
					goto finish;
				m_substage++;
			}
			m_stage++;
			m_substage = 0; //prepare for the next case
		}   nobreak;

		case 5: {
			while(m_substage < m_prewalk_count) {
				if ((status = m_prewalk[m_substage]->Write (*this)) != TK_Normal)
					goto finish;
				m_prewalk[m_substage]->Reset();
				m_substage++;
			}
			m_stage++;
		}   nobreak;

		// Contents:
		/// Textures
		case 6: {
			m_save_write_flags = GetWriteFlags ();
			SetWriteFlags (m_save_write_flags & ~TK_Force_Tags);

			find_textures ();

			m_substage = 0;
			if (m_texture_list != null) {
				if (m_current_object == null) {
					set_last_key (-1);

					m_current_object = opcode_handler (TKE_Open_Segment);

					if ((status = m_current_object->Interpret (*this, -1, "?Include Library/texture images")) == TK_Error)
						goto finish;
				}

				if ((status = m_current_object->Write(*this)) != TK_Normal)
					goto finish;

				m_current_object->Reset();
				m_current_object = null;
				m_substage = 1;
			}
			m_stage++;
		}   nobreak;

		case 7: {
			while (1) {
				if (!m_current_object) {
					if (m_texture_list == null) {
						if (m_substage != 0)
							m_current_object = opcode_handler (TKE_Close_Segment);
						m_substage = 0;
						break;
					}

					if (m_texture_list->m_image_key != -1 && m_texture_list->m_do_write_image) {
						m_current_object = opcode_handler (TKE_Image);

						if ((status = m_current_object->Interpret (*this, m_texture_list->m_image_key)) == TK_Error)
							goto finish;

						m_texture_list->m_image_key = -1;   // flag that we can do the texture itself next;
					}
					else {
						m_current_object = opcode_handler (TKE_Texture);

						if ((status = m_current_object->Interpret (*this, -1, m_texture_list->m_name)) == TK_Error)
							goto finish;

						Internal_Texture_List *     victim = m_texture_list;

						m_texture_list = victim->m_next;
						delete victim;
					}
				}

				// [continue to] write the current object
				if (status != TK_Revisit) {
					if ((status = m_current_object->Write(*this)) != TK_Normal)
						goto finish;

					m_current_object->Reset();
					m_current_object = null;
				}
			}

			m_stage++;
		}   nobreak;

		case 8: {
			if (m_current_object != null) {     // only if we did textures
				if ((status = m_current_object->Write(*this)) != TK_Normal)
					goto finish;

				m_current_object->Reset();
				m_current_object = null;
			}

			HC_Begin_Font_Search ("", "defined");
			m_stage++;
		}   nobreak;

		/// Defined Fonts
		case 9: {
			if (GetTargetVersion() >= 650)   // can the intended reader handle fonts?
				while (1) {
					// may need to prepare the next object
					if (!m_current_object) {
						char        font_name[4096];

						if (!HC_Find_Font (font_name))
							break;

						if (!streq (font_name, "enfield") &&    // filter out HOOPS internal defined fonts
							!streq (font_name, "newfield") &&
							!streq (font_name, "brooktondale") &&
							!streq (font_name, "kuma")) {
							m_current_object = opcode_handler (TKE_Font);
							if ((status = m_current_object->Interpret (*this, -1, font_name)) != TK_Normal)
								goto finish;
						}
					}

					if (m_current_object != null) {
						if ((status = m_current_object->Write (*this)) != TK_Normal)
							goto finish;

						m_current_object->Reset();
						m_current_object = null;
					}
				}

			HC_End_Font_Search ();

			SetWriteFlags (m_save_write_flags);

			m_stage++;
		}   nobreak;

		/// Segment tree
		case 10: {
			if (m_current_object == null) {
				char            pathname[1024];
				HC_KEY          segkey;

				if (start_segment != null)
					HC_Show_Pathname_Expansion (start_segment, pathname);
				else
					HC_Show_Pathname_Expansion (".", pathname);

				segkey = HC_KCreate_Segment (pathname);
				if (segkey >= 0) {
					char *          cp;
					HC_KEY          tmpkey = segkey;
					char            scope[32];

					// convert pathname to parent
					cp = strrchr (pathname, '/');
					if (cp != pathname)
						*cp = '\0';
					else
						pathname[1] = '\0';

					HC_Open_Segment (pathname);
						HC_Show_Key_Status (tmpkey, scope);
						segkey = HC_KRenumber_Key (tmpkey, -1, "irrelevant");
						HC_Renumber_Key (segkey, tmpkey, scope);
					HC_Close_Segment ();
				}

				m_current_object = m_segment_processor;

				if (start_segment != null) {
					if ((status = m_current_object->Interpret (*this, segkey, start_segment)) != TK_Normal)
						goto finish;
				}
				else {
					if ((status = m_current_object->Interpret (*this, segkey, -1)) != TK_Normal)
						goto finish;
				}

				m_segment_processor->SetRoot (segkey);
			}

			if ((status = m_current_object->Write (*this)) != TK_Normal)
				goto finish;
			m_stage++;
		}   nobreak;


		case 11: {
			// check for tagged top segment
			HC_KEY          segkey = m_segment_processor->GetRoot();

			// no longer need segment processor
			m_current_object->Reset();
			m_current_object = null;

			if (m_pending_tags != null && m_pending_tags->m_key == segkey && segkey != -1) {
				Internal_Pending_Tag *      victim = m_pending_tags;
				int                         index;
				char                        buffer[32];

				if (victim->m_array != null)
					return Error ("multiple keys on top segment tag");

				m_current_object = opcode_handler (TKE_Tag);

				status = KeyToIndex (segkey, index);
				if (status == TK_NotFound) {    // must be a new item
					index = NextTagIndex();
					AddIndexKeyPair (index, segkey);

					if (GetLogging() && GetLoggingOptions (TK_Logging_Tagging)) {
						sprintf (buffer, "[%d]", index);
						m_current_object->SetLoggingString (buffer);
					}
				}

				// safe to delete the pending tag once it's queued for writing
				m_pending_tags = victim->m_next;
				delete victim;
			}

			m_stage++;
		}   nobreak;


		case 12: {
			// write top segment tag if needed
			if (m_current_object != null) {
				if ((status = m_current_object->Write (*this)) != TK_Normal)
					goto finish;

				m_current_object->Reset();
				m_current_object = null;
			}

			m_revisit_state = HStreamFileToolkit::Nothing;
			m_stage++;
		}   nobreak;


		// Revisits
		case 13: {
			bool			processing = true;

			do {
				switch (m_substage) {
					case 0: {
						// between passes
						if (m_revisit_working == null) {
							if (create_dictionary && m_accumulator.compressed()) {
								m_current_object = opcode_handler (TKE_Stop_Compression);

								if ((status = m_current_object->Write (*this)) != TK_Normal)
									goto finish;

								m_current_object->Reset();
							}
						}
						m_substage++;
					}   nobreak;

					case 1: {
						// prepare working list
						if (m_revisit_working == null && m_revisit_state != HStreamFileToolkit::Force) {
							/* write a pause before starting every new pass. 
							 * (but suppress the first pause if in Priority_Heuristic mode) */
							/*if ((GetWriteFlags() & TK_Disable_Priority_Heuristic) || m_pass != 0)*/ {
								m_current_object = opcode_handler (TKE_Pause);

								if ((status = m_current_object->Write (*this)) != TK_Normal)
									goto finish;

								m_current_object->Reset();
							}
						}

						m_current_object = null;
						if ((status = sort_revisit()) != TK_Normal)
							goto finish;
						m_revisit_working = m_revisit;
						m_revisit = null;
						++m_pass;

						if (m_revisit_working == null) {
							processing = false;
							break;
						}

						m_substage++;
					}   nobreak;

					case 2: {
						// prepare this object
						status = TK_Normal;

						if (m_current_object == null) {
							// make sure this info is available for tagging
							set_context_key (m_revisit_working->m_owner);
							set_last_key (m_revisit_working->m_key);
							mark_position ();
							m_revisit_offset = GeneratedSoFar();

							// construct from top of list
							if (m_revisit_working->m_opcode == TKE_Reopen_Segment) {
								if (m_non_segment_revisits) {
									// save for next time around
									Internal_Revisit_Item *     keeper = m_revisit_working;

									m_revisit_working = keeper->m_next;

									keeper->m_next = m_revisit;
									m_revisit = keeper;


									if (m_revisit_working == null)
										m_substage = 9;	// will recycle to normal/forced choice

									break;	// cycle around and try another
								}

								m_current_object = m_segment_processor;
							}
							else
								m_current_object = opcode_handler (m_revisit_working->m_opcode);

							if (m_revisit_working->m_owner != -1) {
								HC_Open_Segment_By_Key (m_revisit_working->m_owner);
								status = m_current_object->Interpret (*this, m_revisit_working->m_key, m_revisit_working->m_lod);
								HC_Close_Segment();
							}
							else
								status = m_current_object->Interpret (*this, m_revisit_working->m_key, m_revisit_working->m_lod);

							if (status == TK_Error)
								goto finish;
						}

						set_last_key (m_revisit_working->m_key);

						if (status == TK_Revisit)  {
							Internal_Revisit_Item *     victim = m_revisit_working;
							m_revisit_working = m_revisit_working->m_next;
							delete victim;

							m_current_object = null;

							if (m_revisit_working == null)
								m_substage = 9;	// will recycle to normal/forced choice

							break;	// cycle around and try another
						}

						m_substage++;
					}   nobreak;

					case 3: {
						// write this one (start with Compress if appropriate)
						if (!GetWriteFlags (TK_Disable_Global_Compression) && !m_accumulator.compressed())
							if ((status = opcode_handler (TKE_Start_Compression)->Write (*this)) != TK_Normal)
								goto finish;

						opcode_handler (TKE_Start_Compression)->Reset();
						m_substage++;
					}   nobreak;

					case 4: {
						m_revisit_working->m_force_context = m_current_object->NeedsContext(*this);

						if (m_revisit_working->m_force_context) {
							BBaseOpcodeHandler *	reopen_segment = GetOpcodeHandler (TKE_Reopen_Segment);

							if ((status = reopen_segment->Interpret (*this, m_revisit_working->m_owner)) != TK_Normal)
								return status;
							if ((status = reopen_segment->Write(*this)) != TK_Normal)
								goto finish;
							reopen_segment->Reset();
						}
						m_substage++;
					}   nobreak;

					case 5: {
						if (status != TK_Revisit &&
							(m_revisit_state != HStreamFileToolkit::Force ||
							 m_revisit_working->m_opcode == TKE_Reference &&
							 ((HTK_Reference *)m_current_object)->Direct()) &&
							geometry_has_attributes (m_revisit_working->m_opcode, m_revisit_working->m_key)) {
							m_local_attributes = 1;

							if ((status = opcode_handler (TKE_Geometry_Attributes)->Write(*this)) != TK_Normal)
								goto finish;
							opcode_handler (TKE_Geometry_Attributes)->Reset();

							HC_Open_Geometry (m_revisit_working->m_key);
							HC_Begin_Contents_Search (".", "attributes");
						}
						m_substage++;
					}   nobreak;

					case 6: {
						// [continue to] write the current object
						while (m_current_object != null) { // something we want to handle...
							if (status != TK_Revisit) {
								if ((status = m_current_object->Write(*this)) != TK_Normal)
									goto finish;
							}

							if (m_must_delete != null) {
								delete m_must_delete;
								m_must_delete = null;
							}
							else 
								m_current_object->Reset();
							m_current_object = null;

							if (m_local_attributes) {	// noted local attributes earlier
								char			type[1024];
								HC_KEY			item;

								type[0] = '\0';
								if (m_local_attributes == 1) {
									HC_Show_Geometry_Options (m_revisit_working->m_key, type);
									if (type[0] != '\0') {
										m_current_object = opcode_handler (TKE_Geometry_Options);
										if ((status = m_current_object->Interpret (*this, m_revisit_working->m_key)) == TK_Error)
											goto finish;
									}
									m_local_attributes = 2;
								}
								if (m_current_object == null && HC_Find_Contents (type, &item)) {
									unsigned char		op = TKE_Termination;

									if ((status = StringToOpcode (type, &op)) != TK_Normal) {
										#ifdef _DEBUG
											dprintf ("---- no handler for HOOPS type '%s'\n", type);
										#endif
									}

									if (op == TKE_Color)
										m_current_object = m_must_delete = new HTK_Color_Composite;
									else if (op != TKE_Termination)
										m_current_object = opcode_handler (op);

									if (m_current_object != null) {
										if ((status = m_current_object->Interpret (*this, item)) == TK_Error)
											goto finish;
									}
								}
								else {			// done with local attributes, close it down
									HC_End_Contents_Search();
									HC_Close_Geometry();
									m_local_attributes = 0;

									m_current_object = opcode_handler (TKE_Termination);
								}
							}
						}

						m_substage++;
					}   nobreak;

					case 7: {
						if (m_revisit_working->m_force_context) {
							BBaseOpcodeHandler *	close_segment = GetOpcodeHandler (TKE_Close_Segment);

							if ((status = close_segment->Interpret(*this, m_revisit_working->m_owner)) != TK_Normal)
								return status;
							if ((status = close_segment->Write(*this)) != TK_Normal)
								goto finish;
							close_segment->Reset();
						}
						m_substage++;
					}   nobreak;

					case 8: {
						// any details on this object
						m_current_object = opcode_handler (TKE_Stop_Compression);
						if (create_dictionary && m_accumulator.compressed())
							if ((status = m_current_object->Write (*this)) != TK_Normal)
								goto finish;

						m_current_object->Reset();
						m_current_object = null;

						if (m_pending_tags != null &&
							m_pending_tags->m_key == m_revisit_working->m_key) {
							// process a pending tag (for final object offset)
							Internal_Pending_Tag *      victim = m_pending_tags;

							// end position/bounds only useful if we want a dictionary that supports it
							if (create_dictionary && m_dictionary_format > 0) {
								//m_translator.key_variant_offset (victim->m_key, victim->m_variant, start);
								AddVariant (victim->m_key, victim->m_variant,
											m_revisit_offset + m_offset,
											GeneratedSoFar() - m_revisit_offset + m_offset);

								// and see if we can add bounding info
								if ((m_dictionary_options & TK_Dictionary_Bounding_Volumes) != 0) {
									float           bounds[6];
									HC_KEY          current_key = victim->m_key;

									if (current_key == -1)  // top segment
										current_key = HC_KCreate_Segment (".");

									if (HC_Compute_Circumcuboid_By_Key (current_key, &bounds[0], &bounds[3]))
										AddBounds (victim->m_key, bounds);
								}
							}

							m_pending_tags = victim->m_next;
							delete victim;
						}

						if (m_revisit_state == HStreamFileToolkit::Nothing)
							m_revisit_state = HStreamFileToolkit::Working;

						Internal_Revisit_Item *     rvictim = m_revisit_working;
						m_revisit_working = m_revisit_working->m_next;
						delete rvictim;

						if (m_revisit_working != null) {
							// cycle back for next item
							m_substage = 2;
							break;
						}

						m_substage++;
					}   nobreak;


					case 9: {
						// ready for another run on any new (or recycled) revisit items
						if (m_revisit_state == HStreamFileToolkit::Nothing) {
							// only references that couldn't find their items, force them to generate them
							m_current_object = opcode_handler (TKE_Open_Segment);
							if ((status = m_current_object->Interpret (*this, -1, "?Include Library/references")) == TK_Error)
								goto finish;
							if ((status = m_current_object->Write(*this)) != TK_Normal)
								goto finish;
							m_current_object->Reset ();
							m_current_object = null;

							m_revisit_state = HStreamFileToolkit::Force;
						}
						else {
							if (m_revisit_state == HStreamFileToolkit::Force) {
								m_current_object = opcode_handler (TKE_Close_Segment);
								if ((status = m_current_object->Interpret (*this, -1)) == TK_Error)
									goto finish;
								if ((status = m_current_object->Write(*this)) != TK_Normal)
									goto finish;
								m_current_object->Reset ();
								m_current_object = null;
							}
							// whether working or forcing generation, return to base state
							m_revisit_state = HStreamFileToolkit::Nothing;
						}

						m_substage = 0;
					}
				}
			} while (processing);

			m_stage++;
		}   nobreak;

		// Final Pause
		case 14: {
			switch (m_substage) {
				case 0: {
					if (create_dictionary && m_accumulator.compressed()) {
						m_current_object = opcode_handler (TKE_Stop_Compression);

						if ((status = m_current_object->Write (*this)) != TK_Normal)
							goto finish;

						m_current_object->Reset();
					}
					m_substage++;
				}   nobreak;

				case 1: {
					m_current_object = opcode_handler (TKE_Pause);

					if ((status = m_current_object->Write (*this)) != TK_Normal)
						goto finish;

					m_current_object->Reset();
					m_current_object = null;
					m_substage = 0;
				}   break;
			}
			m_stage++;
			m_substage = 0;
		}   nobreak;

		// Postwalk
		case 15: {
			while (m_substage < m_postwalk_count) {
				if ((status = m_postwalk[m_substage]->Interpret (*this, -1)) != TK_Normal)
					goto finish;
				m_substage++;
			}
			m_stage++;
		}   nobreak;

		case 16: {
			if (m_postwalk_count &&
				!GetWriteFlags(TK_Disable_Global_Compression) && 
				!m_accumulator.compressed())  {

				m_current_object = opcode_handler (TKE_Start_Compression);
				if ((status = m_current_object->Write (*this)) != TK_Normal)
					goto finish;
				m_current_object->Reset();
				m_current_object = null;
			}
			m_stage++;
			m_substage = 0; //prepare for the next case
		}   nobreak;

		case 17: {
			while (m_substage < m_postwalk_count) {
				if ((status = m_postwalk[m_substage]->Write (*this)) != TK_Normal)
					goto finish;
				m_postwalk[m_substage]->Reset();
				m_substage++;
			}
			m_stage++;
		}   nobreak;

		// Cleanup
		case 18: {
			if (m_accumulator.compressed()) {
				m_current_object = opcode_handler (TKE_Stop_Compression);

				if ((status = m_current_object->Write (*this)) != TK_Normal)
					goto finish;

				m_current_object->Reset();
				m_current_object = null;
			}

			m_stage++;
		}   nobreak;

		// Dictionary
		case 19: {
			if (create_dictionary) {
				if (m_current_object == null) {
					SetDictionaryOffset (GeneratedSoFar() + m_offset);
							m_current_object = opcode_handler (TKE_Dictionary);
				}

				if ((status = m_current_object->Write (*this)) != TK_Normal)
					goto finish;

				m_current_object->Reset();
				m_current_object = null;

				SetDictionarySize (GeneratedSoFar() - GetDictionaryOffset() + m_offset);
			}
			m_stage++;
		}   nobreak;

		// Done!
		case 20: {
			m_current_object = opcode_handler (TKE_Termination);

			if ((status = m_current_object->Write (*this)) != TK_Normal)
				goto finish;

			status = TK_Complete;

			m_current_object->Reset();
			m_current_object = m_default_object;

			m_stage++;
		}   nobreak;

		// Misc info
		case 21: {
			#ifdef _DEBUG
				if (!GetWriteFlags (TK_Disable_Instancing)) {
					// Good place to gather statistics
					int             num_shells = 0;
					int             instances_generated = 0;
					int             objects_instanced = 0;
					int             max_repeated = 0;
					int             i;

					for (i=0; i<256; i++) {
						Recorded_Instance alter *   instance;

						if ((instance = m_instance_hash[i]) != null) do {
							++num_shells;
							if (instance->m_times_used > 0) {
								instances_generated += instance->m_times_used;
								++objects_instanced;
								if (instance->m_times_used > max_repeated)
									max_repeated = instance->m_times_used;
							}
						} until ((instance = instance->m_next) == null);
					}

					if (max_repeated > 0)
						dprintf ("%d base objects, %d instances from %d objects, up to %d instances per object\n",
								 num_shells, instances_generated, objects_instanced, max_repeated);
					else
						dprintf ("No instances generated\n");
				}
			#endif

			m_stage = -1;
		}   break;

		default:
			status = Error ("GenerateBuffer in unknown state");
	}

  finish:
	if (status == TK_Error) {
		if (m_current_object != null) {
			m_current_object->Reset();
			m_current_object = null;
		}
		if (m_stage == 8) {
			// error while doing fonts, close out the font search
			HC_End_Font_Search ();
		}
	}

	f = CurrentBufferLength();      // send back how much got filled in

	return status;
#else
    UNREFERENCED (b);
    UNREFERENCED (s);
    UNREFERENCED (f);
    UNREFERENCED (start_segment);
	return Error (stream_readonly);
#endif
}


TK_Status HStreamFileToolkit::GenerateOneItemBuffer (char * b, int s, int alter & f, HC_KEY item) alter {
#ifndef HSTREAM_READONLY
	TK_Status           status = TK_Complete;
	int					save_flags = GetWriteFlags();
	char				type[1024];

	SetWriteFlags(save_flags | TK_Disable_Priority_Heuristic);

	if ((status = PrepareBuffer (b, s)) != TK_Normal)
		goto finish;

	switch (m_stage) {
		// Setup
		case 0: {
			if (!GetWriteFlags (TK_Disable_Global_Compression)) {
				if (m_current_object == m_default_object)
					m_current_object = opcode_handler (TKE_Start_Compression);

				if ((status = m_current_object->Write (*this)) != TK_Normal)
					goto finish;

				m_current_object->Reset();
				m_current_object = null;
			}

			m_stage++;
		}   nobreak;

		case 1: {
			if (m_current_object == null) {

				HC_Show_Key_Type (item, type);

				switch (type[0]) {
					case 'c':
						if (streq (type, "circle"))
							m_current_object = opcode_handler (TKE_Circle);
						else if (streq (type, "circular arc"))
							m_current_object = opcode_handler (TKE_Circular_Arc);
						else if (streq (type, "circular chord"))
							m_current_object = opcode_handler (TKE_Circular_Chord);
						else if (streq (type, "circular wedge"))
							m_current_object = opcode_handler (TKE_Circular_Wedge);
						else if (streq (type, "cutting plane"))
							m_current_object = opcode_handler (TKE_Cutting_Plane);
						else if (streq (type, "cutting section"))
							m_current_object = opcode_handler (TKE_Cutting_Plane);
						else if (streq (type, "cylinder"))
							m_current_object = opcode_handler (TKE_Cylinder);
						break;
					case 'e':
						if (streq (type, "ellipse"))
							m_current_object = opcode_handler (TKE_Ellipse);
						else if (streq (type, "elliptical arc"))
							m_current_object = opcode_handler (TKE_Elliptical_Arc);
						break;
					case 'g':
						if (streq (type, "grid"))
							m_current_object = opcode_handler (TKE_Grid);
						break;
					case 'i':
						if (streq (type, "image"))
							m_current_object = opcode_handler (TKE_Image);
						else if (streq (type, "infinite line"))
							m_current_object = opcode_handler (TKE_Infinite_Line);
						else if (streq (type, "infinite ray"))
							m_current_object = opcode_handler (TKE_Infinite_Ray);
						break;
					case 'l':
						if (streq (type, "line"))
							m_current_object = opcode_handler (TKE_Line);
						else {
							if (streq (type, "area light"))
								m_current_object = opcode_handler (TKE_Area_Light);
							else if (streq (type, "distant light"))
								m_current_object = opcode_handler (TKE_Distant_Light);
							else if (streq (type, "local light"))
								m_current_object = opcode_handler (TKE_Local_Light);
							else if (streq (type, "spot light"))
								m_current_object = opcode_handler (TKE_Spot_Light);
						}
						break;
					case 'm':
						if (streq (type, "marker"))
							m_current_object = opcode_handler (TKE_Marker);
						else if (streq (type, "mesh"))
							m_current_object = opcode_handler (TKE_Mesh);
						break;
					case 'n':
						if (streq (type, "nurbs curve"))
							m_current_object = opcode_handler (TKE_NURBS_Curve);
						else if (streq (type, "nurbs surface"))
							m_current_object = opcode_handler (TKE_NURBS_Surface);
						break;
					case 'p':
						if (streq (type, "polygon"))
							m_current_object = opcode_handler (TKE_Polygon);
						else if (streq (type, "polyline"))
							m_current_object = opcode_handler (TKE_Polyline);
						else if (streq (type, "polycylinder"))
							m_current_object = opcode_handler (TKE_PolyCylinder);
						break;
					case 'r':
						if (streq (type, "reference"))
							m_current_object = opcode_handler (TKE_Reference);
					case 's':
						if (streq (type, "shell"))
							m_current_object = opcode_handler (TKE_Shell);
						else if (streq (type, "sphere"))
							m_current_object = opcode_handler (TKE_Sphere);
						break;
					case 't':
						if (streq (type, "text"))
							m_current_object = opcode_handler (TKE_Text);
						break;
				}

				// assuming we are handling it, process it...
				if (m_current_object != null) {
					if ((status = m_current_object->Interpret (*this, item)) == TK_Error)
						goto finish;
				}
			}

			if (m_current_object != null) { // something we want to handle...
				// first get ready if we have any local attributes
				if (geometry_has_attributes (m_current_object->Opcode(), item)) {
					m_local_attributes = 1;

					if ((status = opcode_handler (TKE_Geometry_Attributes)->Write(*this)) != TK_Normal)
						return status;
					opcode_handler (TKE_Geometry_Attributes)->Reset();

					HC_Open_Geometry (item);
					HC_Begin_Contents_Search (".", "attributes");
				}
			}

			m_stage++;
		}   nobreak;

		case 2: {
			// [continue to] write the current object
			while (m_current_object != null) { // something we want to handle...
				if (status != TK_Revisit) {
					if ((status = m_current_object->Write(*this)) != TK_Normal)
						goto finish;
				}

				if (m_must_delete != null) {
					delete m_must_delete;
					m_must_delete = null;
				}
				else 
					m_current_object->Reset();
				m_current_object = null;

				if (m_local_attributes) {	// noted local attributes earlier
					type[0] = '\0';
					if (m_local_attributes == 1) {
						HC_Show_Geometry_Options (item, type);
						if (type[0] != '\0') {
							m_current_object = opcode_handler (TKE_Geometry_Options);
							if ((status = m_current_object->Interpret (*this, item)) == TK_Error)
								goto finish;
						}
						m_local_attributes = 2;
					}
					if (m_current_object == null && HC_Find_Contents (type, &item)) {
						unsigned char		op = TKE_Termination;

						if ((status = StringToOpcode (type, &op)) != TK_Normal) {
							#ifdef _DEBUG
								dprintf ("---- no handler for HOOPS type '%s'\n", type);
							#endif
						}

						if (op == TKE_Color)
							m_current_object = m_must_delete = new HTK_Color_Composite;
						else if (op != TKE_Termination)
							m_current_object = opcode_handler (op);

						if (m_current_object != null) {
							if ((status = m_current_object->Interpret (*this, item)) == TK_Error)
								goto finish;
						}
					}
					else {			// done with local attributes, close it down
						HC_End_Contents_Search();
						HC_Close_Geometry();
						m_local_attributes = 0;

						m_current_object = opcode_handler (TKE_Termination);
					}
				}
			}

			m_stage++;
		}   nobreak;

		// Cleanup
		case 3: {
			if (m_accumulator.compressed()) {
				m_current_object = opcode_handler (TKE_Stop_Compression);

				if ((status = m_current_object->Write (*this)) != TK_Normal)
					goto finish;

				m_current_object->Reset();
				m_current_object = null;
			}

			m_stage++;
		}   nobreak;

		case 4: {
			m_current_object = opcode_handler (TKE_Termination);

			if ((status = m_current_object->Write (*this)) != TK_Normal)
				goto finish;

			status = TK_Complete;

			m_current_object->Reset();
			m_current_object = m_default_object;


			m_stage = -1;
		}   break;

		default:
			status = Error ("GenerateOneItemBuffer in unknown state");
	}

finish:
	if (status == TK_Error) {
		if (m_current_object != null) {
			m_current_object->Reset();
			m_current_object = null;
		}
	}
	f = CurrentBufferLength();      // send back how much got filled in
	SetWriteFlags(save_flags);

	return status;
#else
    UNREFERENCED (b);
    UNREFERENCED (s);
    UNREFERENCED (f);
    UNREFERENCED (item);
	return Error (stream_readonly);
#endif
}


// object counting

unsigned HLONG HStreamFileToolkit::count_segment_objects (HC_KEY key, char const * start_segment) alter {
	unsigned HLONG       total = 0;
#ifndef HSTREAM_READONLY
	HC_KEY              item_key;
	char                type[32];

	if (key != -1)
		HC_Open_Segment_By_Key (key);
	else if (start_segment != null)
		key = HC_KOpen_Segment (start_segment);

	if (key != -1)
		total += 2;     // Open & Close

	remember_item (key);

	// Attributes & Geometry -- simple count
	total += HC_Show_Existence ("attributes, no driver, no driver options, no styles, geometry");

	// subsegments, includes, styles
	HC_Begin_Contents_Search (".", "segment, include, style");
	HC_Reverse_Contents_Search();
	while (HC_Find_Contents (type, &item_key)) {
		// if key is renumbered, we want to work with internal key
		char            scope[32];
		HC_KEY          renumbered;

		if (item_key >= 0) {
			renumbered = item_key;
			HC_Show_Key_Status (renumbered, scope);
			item_key = HC_KRenumber_Key (renumbered, -1, "irrelevant");
			HC_Renumber_Key (item_key, renumbered, scope);
		}

		if (streq (type, "segment"))
			total += count_segment_objects (item_key);
		else {
			HC_KEY          referee;

			if (streq (type, "include"))
				referee = HC_KShow_Include_Segment (item_key);
			else { /* style */
				referee = HC_KShow_Style_Segment (item_key);
				if (referee == -1)
					continue;
			}

			if (referee >= 0) {
				char        segname[1024];
				char *      cp;

				if (streq (type, "include"))
					HC_Show_Include_Segment (item_key, segname);
				else /* style */
					HC_Show_Style_Segment (item_key, segname);

				cp = strrchr (segname, '/');
				if (cp != segname)
					*cp = '\0';
				else
					segname[1] = '\0';

				HC_Open_Segment (segname);
					renumbered = referee;
					HC_Show_Key_Status (renumbered, scope);
					item_key = HC_KRenumber_Key (renumbered, -1, "irrelevant");
					HC_Renumber_Key (item_key, renumbered, scope);
				HC_Close_Segment ();
			}
			else
				item_key = referee;

			if (!find_item (item_key))
				total += count_segment_objects (item_key);  // the referenced segment if first time

			++total;    // the reference
		}
	}
	HC_End_Contents_Search ();

	// Close counted if needed with Open above


	// extra due to segment revist?
	if (HC_Show_Existence (search_strings[Revisit_Search_Point]))
		total += 2;     // Revisit & Close

	if (key != -1)
		HC_Close_Segment ();        // restore scope

#else
    UNREFERENCED (key);
    UNREFERENCED (start_segment);
#endif
	return total;
}


unsigned POINTER_SIZED_INT HStreamFileToolkit::CountObjects (char const * start_segment) alter {
	unsigned HLONG       total = 0;
#ifndef HSTREAM_READONLY
	// Header: Comment, File_Info, Bounding_Info
	total += 3;

	// Prewalk -- unknown

	// Contents:
	/// Textures
	find_textures ();
	if (m_texture_list != null) {
		// Open & Close dummy segment
		total += 2;
		while (m_texture_list != null) {
			Internal_Texture_List *     victim = m_texture_list;

			if (m_texture_list->m_image_key != -1)
				++total;    // source image
			++total;        // texture itself

			m_texture_list = victim->m_next;
			delete victim;
		}
	}

	/// Defined Fonts
	if (GetTargetVersion() >= 650) { // can the intended reader handle fonts?
		HC_Begin_Font_Search ("", "defined");
			char        font_name[256];

			while (HC_Find_Font (font_name)) {
				if (!streq (font_name, "Enfield") &&    // filter out HOOPS internal defined fonts
					!streq (font_name, "Newfield") &&
					!streq (font_name, "Brooktondale") &&
					!streq (font_name, "Kuma"))
					++total;
			}

		HC_End_Font_Search ();
	}

	/// Segment tree (revisits handled within)
	total += count_segment_objects (-1, start_segment);

	// Postwalk -- unknown

	// Dictionary
	if (GetWriteFlags(TK_Generate_Dictionary) &&
		!GetWriteFlags(TK_Suppress_LOD))
		++total;

	// Termination
	++total;

	// Cleanup
	m_visited_items.clean();

#else
    UNREFERENCED (start_segment);
#endif
	return total;
}



TK_Status HStreamFileToolkit::StringToOpcode (char const *type, unsigned char *opcode_out) {
#ifndef HSTREAM_READONLY
	switch (type[0]) {
		case 'c':
			if (streq (type, "callback"))
				*opcode_out = TKE_Callback;
			else if (streq (type, "camera"))
				*opcode_out = TKE_Camera;
			else if (streq (type, "circle"))
				*opcode_out = TKE_Circle;
			else if (streq (type, "circular arc"))
				*opcode_out = TKE_Circular_Arc;
			else if (streq (type, "circular chord"))
				*opcode_out = TKE_Circular_Chord;
			else if (streq (type, "circular wedge"))
				*opcode_out = TKE_Circular_Wedge;
			else if (streq (type, "clip region"))
				*opcode_out = TKE_Clip_Region;
			else if (streq (type, "color"))
				*opcode_out = TKE_Color;    //will be handled by HTK_Color_Composite
			else if (streq (type, "color map"))
				*opcode_out = TKE_Color_Map;
			else if (streq (type, "conditional action"))
				*opcode_out = TKE_Conditional_Action;
			else if (streq (type, "conditions"))
				*opcode_out = TKE_Conditions;
			else if (streq (type, "cutting plane"))
				*opcode_out = TKE_Cutting_Plane;
			else if (streq (type, "cutting section"))
				*opcode_out = TKE_Cutting_Plane;
			else if (streq (type, "cylinder"))
				*opcode_out = TKE_Cylinder;
			break;
		case 'd':
			if (streq (type, "driver"))
				return TK_Normal;	    // drivers will NOT be handled in output
			else if (streq (type, "driver options"))
				return TK_Normal;	    // drivers options not handled in output
			else if (streq (type, "display list"))
				return TK_Normal;	    // display lists not handled in output (shouldn't even be returned by the search)
			break;
		case 'e':
			if (streq (type, "edge pattern"))
				*opcode_out = TKE_Edge_Pattern;
			else if (streq (type, "edge weight"))
				*opcode_out = TKE_Edge_Weight;
			else if (streq (type, "ellipse"))
				*opcode_out = TKE_Ellipse;
			else if (streq (type, "elliptical arc"))
				*opcode_out = TKE_Elliptical_Arc;
			break;
		case 'f':
			if (streq (type, "face pattern"))
				*opcode_out = TKE_Face_Pattern;
			break;
		case 'g':
			if (streq (type, "grid"))
				*opcode_out = TKE_Grid;
			else if (streq (type, "glyph definitions"))
				*opcode_out = TKE_Glyph_Definition;
			else if (streq (type, "geometry options"))
				*opcode_out = TKE_Geometry_Options;
			break;
		case 'h':
			if (streq (type, "handedness"))
				*opcode_out = TKE_Handedness;
			else if (streq (type, "heuristics"))
				*opcode_out = TKE_Heuristics;
			break;
		case 'i':
			if (streq (type, "image"))
				*opcode_out = TKE_Image;
			else if (streq (type, "include"))
				*opcode_out = TKE_Include_Segment;  //requires special handling by caller
			else if (streq (type, "infinite line"))
				*opcode_out = TKE_Infinite_Line;  
			else if (streq (type, "infinite ray"))
				*opcode_out = TKE_Infinite_Ray;  
			break;
		case 'l':
			if (streq (type, "line"))
				*opcode_out = TKE_Line;             //may be replaced with TKE_PolyPolyline
			else if (streq (type, "line pattern"))
				*opcode_out = TKE_Line_Pattern;
			else if (streq (type, "line pattern definitions"))
				*opcode_out = TKE_Line_Style;
			else if (streq (type, "line weight"))
				*opcode_out = TKE_Line_Weight;
			else if (streq (type, "light"))
				*opcode_out = TKE_Local_Light;      //depending on m_key_type, may be replaced by TKE_Area_Light, TKE_Distant_Light, TKE_Spot_Light
			else if (streq (type, "lods"))
				*opcode_out = TKE_LOD;
			break;
		case 'm':
			if (streq (type, "marker"))
				*opcode_out = TKE_Marker;
			else if (streq (type, "marker size"))
				*opcode_out = TKE_Marker_Size;
			else if (streq (type, "marker symbol"))
				*opcode_out = TKE_Marker_Symbol;
			else if (streq (type, "mesh"))
				*opcode_out = TKE_Mesh;
			else if (streq (type, "metafile"))
				return TK_Normal;		    // HMF options not handled in HSF output
			else if (streq (type, "modelling matrix"))
				*opcode_out = TKE_Modelling_Matrix;
			break;
		case 'n':
			if (streq (type, "nurbs curve"))
				*opcode_out = TKE_NURBS_Curve;
			else if (streq (type, "nurbs surface"))
				*opcode_out = TKE_NURBS_Surface;
			else if (streq (type, "named style"))
				*opcode_out = TKE_Named_Style;
			else if (streq (type, "named style definitions"))
				*opcode_out = TKE_Named_Style_Def;
			break;
		case 'p':
			if (streq (type, "polygon"))
				*opcode_out = TKE_Polygon;
			else if (streq (type, "polyline")) 
				*opcode_out = TKE_Polyline;         //may be replaced with TKE_PolyPolyline
			else if (streq (type, "polycylinder"))
				*opcode_out = TKE_PolyCylinder;

			break;
		case 'r':
			if (streq (type, "rendering options"))
				*opcode_out = TKE_Rendering_Options;
			else if (streq (type, "reference"))
				*opcode_out = TKE_Reference;
			break;
		case 's':
			if (streq (type, "selectability"))
				*opcode_out = TKE_Selectability;
			else if (streq (type, "segment"))
				*opcode_out = TKE_Open_Segment;     //requires special handling by caller
			else if (streq (type, "shell"))
				*opcode_out = TKE_Shell;
			else if (streq (type, "sphere"))
				*opcode_out = TKE_Sphere;
			else if (streq (type, "streaming mode"))
				*opcode_out = TKE_Streaming_Mode;
			else if (streq (type, "style"))
				*opcode_out = TKE_Style_Segment;    //requires special handling by caller
			else if (streq (type, "shaders"))
				*opcode_out = TKE_Texture;			//requires special handling by caller
			break;
		case 't':
			if (streq (type, "text"))
				*opcode_out = TKE_Text;
			else if (streq (type, "text alignment"))
				*opcode_out = TKE_Text_Alignment;
			else if (streq (type, "text font"))
				*opcode_out = TKE_Text_Font;
			else if (streq (type, "text path"))
				*opcode_out = TKE_Text_Path;
			else if (streq (type, "text spacing"))
				*opcode_out = TKE_Text_Spacing;
			else if (streq (type, "texture matrix"))
				*opcode_out = TKE_Texture_Matrix;
			else if (streq (type, "texture definitions"))
				*opcode_out = TKE_Texture;	    //requires special handling by caller
			break;
		case 'u':
			if (streq (type, "user options"))
				*opcode_out = TKE_User_Options;
			else if (streq (type, "user value"))
				*opcode_out = TKE_User_Value;
			break;
		case 'v':
			if (streq (type, "visibility"))
				*opcode_out = TKE_Visibility;
			break;
		case 'w':
			if (streq (type, "window"))
				*opcode_out = TKE_Window;
			else if (streq (type, "window pattern"))
				*opcode_out = TKE_Window_Pattern;
			else if (streq (type, "window frame"))
				*opcode_out = TKE_Window_Frame;
			break;
	}


	return (*opcode_out != 0) ? TK_Normal : TK_NotFound;
#else
    UNREFERENCED (type);
    UNREFERENCED (opcode_out);
	return TK_NotFound;
#endif
}


TK_Status HStreamFileToolkit::StringToHandler (char const *type, BBaseOpcodeHandler **handler) {
#ifndef HSTREAM_READONLY
	unsigned char op = TKE_Termination;

	*handler = null;

	StringToOpcode (type, &op);

	switch (op) {
		case TKE_Open_Segment: 
		case TKE_Include_Segment:
		case TKE_Style_Segment: {
			//these involve special care, so if they are required, we shouldn't be using this function.
			return Error("HStreamFileToolkit found unsupported configuration in HOOPS database");
		} break;

		case TKE_Termination: {
			//skip it.  It's either something we don't know about or something we simply don't want in the file.
		} break;

		default: {
			opcode_handler(op)->Clone(*this, handler);
		} break;
	}
	return TK_Normal;
#else
    UNREFERENCED (type);
    UNREFERENCED (handler);
	return Error (stream_readonly);
#endif
}



////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
#ifndef HSTREAM_READONLY

Internal_Segment_Processor::Internal_Segment_Processor (ID_Key key, char const * name)
	: BBaseOpcodeHandler (TKE_Reopen_Segment)
	, m_name (null)
	, m_key (key)
	, m_top_level (false)
	, m_root (key)  // assume the same till we are told otherwise
	, m_current_object (null)
	, m_must_delete (null)
	, m_item_key (-1)
	, m_saved_count (0)
	, m_saved_keys (null)
	, m_renumbered (-1)
	, m_priority (0)
	, m_start_offset (0)
	, m_searching (false)
	, m_geometry_attributes (false)
	, m_deferred (null)
	, m_search_pass (0) {

	if (name != null) {
		m_name = new char [strlen (name) + 1];
		strcpy (m_name, name);
	}
}

Internal_Segment_Processor::~Internal_Segment_Processor () {
	delete [] m_saved_keys;
	delete m_must_delete;
	delete [] m_name;
}


TK_Status Internal_Segment_Processor::Interpret (BStreamFileToolkit & tk, ID_Key key, int variant) alter {
#ifndef HSTREAM_READONLY
	char			segname[4096];
	char *			slash;

	// use the key passed in
	m_key = key;
	m_top_level = (key == -1 || variant == -1);	// variant -1 for start segment first time, key -1 on revisits

	// determine the name if appropriate
	if (tk.pass() == 0 && !m_top_level) {
		HC_Show_Segment (m_key, segname);
		if ((slash = strrchr (segname, '/')) != null) {
			++slash;
			memmove (segname, slash, strlen(slash)+1);		// name only
		}
		if (segname[0] == '@') {		// unnamed segment
			HC_Open_Segment_By_Key (m_key);
				if (HC_QShow_Existence ("...", "includers, stylers"))
					segname[0] = '$';
				else
					segname[0] = '\0';
			HC_Close_Segment ();
		}

		delete [] m_name;
		m_name = new char [strlen (segname) + 1];
		strcpy (m_name, segname);
	}

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

TK_Status Internal_Segment_Processor::Interpret (BStreamFileToolkit & tk, ID_Key key, char const * special) alter {
#ifndef HSTREAM_READONLY
	char			segname[1024];
	int				i, length;

	if (special == null)
		return Interpret (tk, key);

	if (!HC_QShow_Existence (special, "self")) {
		sprintf (segname, "Segment '%s' can not be found", special);
		return tk.Error (segname);
	}

	strcpy (segname, special);

	// this variant currently should always get a valid key
	m_key = key;
	m_top_level = false;

	// now maybe adjust the name
	if (segname[0] == '@')
		segname[0] = '\0';

	length = (int)strlen (segname);
	for (i=0; i<length; ++i)
		if (segname[i] == '@')
			segname[i] = '$';

	delete [] m_name;
	m_name = new char [strlen (segname) + 1];
	strcpy (m_name, segname);

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}


void Internal_Segment_Processor::Reset () alter {
	if (m_searching) {
		HC_End_Contents_Search();
		m_searching = false;
	}

	m_key = -1;
	m_top_level = false;
	m_root = -1;
	m_item_key = -1;
	m_renumbered = -1;
	m_priority = 0;
	m_start_offset = 0;
	m_search_pass = 0;

	m_saved_count = 0;
	delete [] m_saved_keys;
	m_saved_keys = null;

	m_use_polypolylines = false;
	m_polylines_already_handled = false;

	if (m_current_object)
		m_current_object->Reset();
	m_current_object = null;
	m_deferred = null;

	delete [] m_name;
	m_name = null;

	delete m_must_delete;
	m_must_delete = null;

	BBaseOpcodeHandler::Reset();
}


void Internal_Segment_Processor::save_keys (HStreamFileToolkit & tk) alter {
	delete [] m_saved_keys;
	m_saved_keys = null;

	if ((m_saved_count = tk.m_last_keys_used) > 1) {
		m_saved_keys = new HC_KEY [m_saved_count];
		memcpy (m_saved_keys, tk.m_last_keys, m_saved_count * sizeof(HC_KEY));
	}
}

void Internal_Segment_Processor::restore_keys (HStreamFileToolkit & tk) alter {
	int         i;

	tk.set_last_key (m_item_key);

	if (m_saved_count > 1) {
	tk.ClearLastKey();
	for (i = 0; i < m_saved_count; i++)
		tk.AppendLastKey (m_saved_keys[i]);
	}
}


TK_Status Internal_Segment_Processor::Clone (BStreamFileToolkit & tk, BBaseOpcodeHandler **newhandler) const {
	*newhandler = new Internal_Segment_Processor();
	if (*newhandler != null)
		return TK_Normal;
	else
		return tk.Error();
}

TK_Status Internal_Segment_Processor::Read (BStreamFileToolkit & btk) {
	return btk.Error();
}

TK_Status Internal_Segment_Processor::Write (BStreamFileToolkit & btk) {
#ifndef HSTREAM_READONLY
	HStreamFileToolkit &tk = *(HStreamFileToolkit *)&btk;
	TK_Status           status = TK_Normal;
	char                type[256];
	int                 count;

	tk.set_context_key (m_key);

	if (!m_top_level && (tk.pass() != 0 || m_name != null)) {
		HC_Open_Segment_By_Key (m_key);     // make sure we're in correct scope
	}
	if (m_geometry_attributes)
		HC_Open_Geometry (m_item_key);

	switch (m_stage) {
		case 0: {
			Remember_Item (tk, m_key);

			if (tk.pass() == 0 || tk.m_revisit_state == HStreamFileToolkit::Force) {
				if (m_name != null) {
					// but first, get an open generated
					m_current_object = tk.opcode_handler (TKE_Open_Segment);

					tk.set_last_key (m_key);   // also make available for tagging
					tk.mark_position ();                    // and store offset for tagging

					if ((status = m_current_object->Interpret (tk, m_key, m_name)) != TK_Normal)
						goto cleanup;
				}
			}
			else {
				// but first, get a reopen generated if needed
				if (!m_top_level) {
					m_current_object = tk.opcode_handler (TKE_Reopen_Segment);

					tk.set_last_key (m_key);   // also make available for tagging
					tk.mark_position ();                    // and store offset for tagging

					if ((status = m_current_object->Interpret (tk, m_key)) != TK_Normal)
						goto cleanup;
				}
				m_search_pass = Revisit_Search_Point;

				if (!(tk.m_write_flags & TK_Disable_Compound_Primitives) &&
							(tk.GetTargetVersion() >= 702)) {
					//we should really be going by the number of points, but the number of primitives is quicker to compute
					
					bool has_line_user_options = false;
					HC_Begin_Contents_Search(".", "lines, polylines");
						HC_Show_Contents_Count(&count);

						char				linetype[32];
						HC_KEY				key;

						while (!has_line_user_options && HC_Find_Contents(linetype, &key)) {
							unsigned char	lineop = TKE_Termination;

							if ((status = tk.StringToOpcode (linetype, &lineop)) == TK_Normal)
								has_line_user_options = geometry_has_attributes (lineop, key);
							else	// dunno, give up
								has_line_user_options = true;
						}
					HC_End_Contents_Search();

					if (count > 5 && !has_line_user_options)
						m_use_polypolylines = true;
				}
			}
			if (tk.m_revisit_state == HStreamFileToolkit::Force)
				m_search_pass = Force_Search_Point;

			HC_Begin_Contents_Search (".",  search_strings[m_search_pass]);
			if (search_reversal[m_search_pass])
				HC_Reverse_Contents_Search();
			++m_search_pass;
			m_searching = true;

			m_item_key = -1;
			m_stage++;
		}   nobreak;

		case 1: {
			while (1) {
				status = TK_Normal;         // assume success
				tk.set_context_key (m_key); // make sure context current

				// may need to make an object
				if (!m_current_object) {
					unsigned char			op = TKE_Termination;

					type[0] = '\0';
					if (!HC_Find_Contents (type, &m_item_key)) {
						if (m_geometry_attributes) {
							HC_End_Contents_Search ();
							HC_Close_Geometry ();
							m_geometry_attributes = false;
							m_item_key = -1;
							op = TKE_Geometry_Attributes;		// flag to request a Termination
						}
						else if (m_search_pass < Revisit_Search_Point) {
							HC_End_Contents_Search ();
							HC_Begin_Contents_Search (".",  search_strings[m_search_pass]);
							if (search_reversal[m_search_pass])
								HC_Reverse_Contents_Search();
							++m_search_pass;

							if (!HC_Find_Contents (type, &m_item_key))
								break;
						}
						else
							break;
					}

					// if key is renumbered, we want to work with internal key
					if (m_item_key > -1) {
						char            scope[32];

						m_renumbered = m_item_key;
						HC_Show_Key_Status (m_renumbered, scope);
						m_renumbered_scope = (unsigned char)
							 ((scope[0] == 'g') ? TKE_Renumber_Key_Global : TKE_Renumber_Key_Local);
						m_item_key = HC_KRenumber_Key (m_renumbered, -1, "irrelevant");
						HC_Renumber_Key (m_item_key, m_renumbered, scope);
					}

					tk.set_last_key (m_item_key);			// also make available for tagging
					if (!m_geometry_attributes)
						tk.mark_position ();				// and store offset for tagging

					if ((status = tk.StringToOpcode (type, &op)) != TK_Normal) {
						#ifdef _DEBUG
							dprintf ("---- no handler for HOOPS type '%s'\n", type);
						#endif
					}
					switch (op) {
						case 0: {
							// was not found
							continue;
						}	nobreak;

						case TKE_Geometry_Attributes: {
							// really trying to shut down local geometry attributes
							m_current_object = tk.opcode_handler (TKE_Termination);
						}	break;                        

						case TKE_Open_Segment: {
							if (tk.SegmentIsExcluded (m_item_key) ||	// one we don't want,
								Find_Item (tk, m_item_key))			// or one we've already done?
								continue;

							// recursive -- can't use predefined handler
							Internal_Segment_Processor *    sp = new Internal_Segment_Processor;

							sp->SetRoot (GetRoot());  // subsegment has same root as we do
							m_current_object = m_must_delete = sp;

							HC_Show_Priority (m_item_key, &m_priority);
						}	break;                        

						case TKE_Include_Segment: {
							HC_Show_Priority (m_item_key, &m_priority);
						}	nobreak;
						case TKE_Style_Segment: {
							// recursive -- can't use predefined handler
							HTK_Referenced_Segment *    ref;

							tk.opcode_handler(op)->Clone(tk, (BBaseOpcodeHandler **)&ref);
							ref->SetRoot (GetRoot());
							m_current_object = m_must_delete = ref;
						}	break;

						case TKE_Color: {
							// not a normal object (maybe we should reserve one...)
							// It can't be overloaded, so it is safe to do a new (as opposed to clone)
							m_current_object = m_must_delete = new HTK_Color_Composite;
						}	break;

						case TKE_Conditional_Action: {
							// at segment level, there may be multiple actions
							// so select a handler than can collect them
							m_current_object = m_must_delete = new HTK_Conditional_Actions;
						}	break;

						case TKE_Texture: {
							// at segment level 'Texture' really means local 'texture definitions'
							// We use a special handler which can in turn use the appropriate Texture handler
							bool is_shader = streq (type, "shaders");
							m_current_object = m_must_delete = new HTK_Texture_Definitions(is_shader);

						}	break;

						case TKE_Glyph_Definition: {
							// need a pseudo-handler which can deal with multiple definitions
							m_current_object = m_must_delete = new HTK_Glyph_Definitions;
						}	break;

						case TKE_Named_Style_Def: {
							// need a pseudo-handler which can deal with multiple definitions
							m_current_object = m_must_delete = new HTK_Named_Style_Defs;
							((HTK_Named_Style_Defs*)m_current_object)->SetRoot (GetRoot());
						}	break;

						case TKE_Line_Style: {
							// need a pseudo-handler which can deal with multiple definitions
							m_current_object = m_must_delete = new HTK_Line_Styles;
						}	break;

						case TKE_Polyline:
						case TKE_Line: {
							//only have polypolylines handle the non-renumbered stuff
							if (m_use_polypolylines && m_renumbered == -1) {
								if (!m_polylines_already_handled) {
									m_current_object = tk.opcode_handler (TKE_PolyPolyline);
									m_polylines_already_handled = true;
								}
								else
									continue;
							}
							else {
								m_current_object = tk.opcode_handler (op);
							}
						}	break;

						case TKE_Local_Light: {
							HC_Show_Key_Type (m_item_key, type);
							if (streq (type, "area light"))
								op = TKE_Area_Light;
							else if (streq (type, "distant light"))
								op = TKE_Distant_Light;
							else if (streq (type, "local light"))
								op = TKE_Local_Light;
							else if (streq (type, "spot light"))
								op = TKE_Spot_Light;

							m_current_object = tk.opcode_handler (op);
						}	break;

						case TKE_Infinite_Line: {
							HC_Show_Key_Type (m_item_key, type);
							if (streq (type, "infinite line"))
								op = TKE_Infinite_Line;
							else if (streq (type, "infinite ray"))
								op = TKE_Infinite_Ray;

							m_current_object = tk.opcode_handler (op);
						}	break;


						default: {
							m_current_object = tk.opcode_handler (op);
						} break;
					}
					if (tk.GetTargetVersion() < 1330)
						m_priority = 0;

					// assuming we are handling it, process it...
					if (m_current_object != null) {
						if (m_current_object->Opcode() != TKE_Termination) {
							if ((status = m_current_object->Interpret (tk, m_item_key)) == TK_Error)
								goto cleanup;
						}

						// local geometry attributes
						if (status != TK_Revisit && tk.GetTargetVersion() >= 1210 &&
							geometry_has_attributes (op, m_item_key)) {
							m_deferred = m_current_object;
							m_current_object = tk.opcode_handler (TKE_Geometry_Attributes);
						}
					}

					save_keys (tk);
				}

				// [continue to] write the current object
				if (m_current_object != null) { // something we want to handle...
					restore_keys (tk);          // make sure in case Write gets repeated

					if (status == TK_Abort) {}	// Interpret said we don't want it
					else if (status == TK_Revisit) {
						m_renumbered = -1;		// we didn't write it out, so we can't renumber it yet
					}
					else {
						if ((status = m_current_object->Write(tk)) != TK_Normal)
							goto cleanup;
					}


					// special objects get deleted, most can just get reused
					if (m_must_delete != null) {
						delete m_must_delete;
						m_must_delete = null;
					}
					else
						m_current_object->Reset();
					m_current_object = null;

					if (m_deferred != null) {
						// geometry with attributes, write & prepare next attribute search
						m_current_object = m_deferred;
						m_deferred = null;

						if (m_geometry_attributes == 0) {	// first time here we check for geometry_options
							HC_Show_Geometry_Options (m_item_key, type);
							if (type[0] != '\0') {
								m_deferred = tk.opcode_handler (TKE_Geometry_Options);
								if ((status = m_deferred->Interpret (tk, m_item_key)) == TK_Error)
									goto cleanup;
							}
						}
						m_geometry_attributes = true;

						if (m_deferred == null) {
							HC_Open_Geometry (m_item_key);
							HC_Begin_Contents_Search (".", "attributes");
						}
					}
					// check for tagged item
					else if (tk.m_pending_tags != null && tk.m_pending_tags->m_key == m_item_key && m_item_key != -1) {
						// Note: changes to tagging here need to be mimicked in HTK_Referenced_Segment::Write()
						Internal_Pending_Tag *      victim = tk.m_pending_tags;
						int                         index;
						char                        buffer[32];
						bool                        logging = tk.GetLogging() &&
																		  tk.GetLoggingOptions (TK_Logging_Tagging);

						m_current_object = tk.opcode_handler (TKE_Tag);

						//if m_array is null, we are dealing with one index to one tag, otherwise one tag can map
						//to any arbitrarily large number of indices.
						if (victim->m_array == null) {
							status = tk.KeyToIndex (m_item_key, index);

							if (status == TK_NotFound) {        // must be a new item
								index = tk.NextTagIndex();
								tk.AddIndexKeyPair (index, m_item_key);

								if (logging) {
									sprintf (buffer, "[%d]", index);
									m_current_object->SetLoggingString (buffer);
								}
							}
						}
						else {
							int i;
							HC_KEY key;

							if (logging) {
								m_current_object->SetLoggingString (10*victim->m_array->m_count);
								m_current_object->GetLoggingString()[0] = '\0';
							}

							for (i = 0; i < victim->m_array->m_count; i++) {
								key = victim->m_array->m_data[i];
								status = tk.KeyToIndex (key, index);

								if (status == TK_NotFound) {    // must be a new item
									index = tk.NextTagIndex();
									tk.AddIndexKeyPair (index, key);

									if (logging) {
										sprintf (buffer, "[%d]", index);
										strcat (m_current_object->GetLoggingString(), buffer);
										if (i%10 == 9)
											strcat (m_current_object->GetLoggingString(), "\n\t\t\t\t");
									}
								}
							}
						}

						// safe to delete the pending tag once it's queued for writing
						tk.m_pending_tags = victim->m_next;
						delete victim;
					}
					// check for priority
					else if (m_priority != 0) {
						m_current_object = m_must_delete = new TK_Renumber (TKE_Priority, m_priority);
						m_priority = 0;
					}
					// check for renumber
					else if (m_renumbered > -1) {
						m_current_object = m_must_delete = new TK_Renumber (m_renumbered_scope, m_renumbered);
						m_renumbered = -1;
					}
				}
			}

			HC_End_Contents_Search ();
			m_searching = false;

			m_stage++;
		}   nobreak;

		case 2: {
			if (!m_top_level && (tk.pass() != 0 || m_name != null)) {
				m_current_object = tk.opcode_handler (TKE_Close_Segment);

				tk.set_last_key (m_key);                // also make available for tagging
				tk.mark_position ();                    // and store offset for tagging

				if ((status = m_current_object->Interpret(tk, m_key)) != TK_Normal)
					goto cleanup;

				if ((status = m_current_object->Write(tk)) != TK_Normal)
					goto cleanup;

				m_current_object->Reset();
				m_current_object = null;
			}

			m_stage++;
		}   nobreak;

		case 3: {
			// if we have other stuff, revisit/tag/record
			tk.set_last_key (m_top_level ? -1 : m_key);
			if (tk.pass() == 0) {
				if (HC_Show_Existence (search_strings[Revisit_Search_Point])) {
					Revisit (tk);
					Tag (tk);
				}
			}
			else {
				tk.set_position (m_start_offset);
				Tag (tk, 0);
			}

			m_stage = -1;
		}   break;

		default:
			status = tk.Error();
	}

  cleanup:
	if (status == TK_Error) {
		if (m_current_object != null) {
			m_current_object->Reset();
			m_current_object = null;
		}
		if (m_searching) {
			// error while processing contents, close out the contents search
			HC_End_Contents_Search ();
			m_searching = false;
		}
	}

	if (m_geometry_attributes)
		HC_Close_Geometry();
	if (!m_top_level && (tk.pass() != 0 || m_name != null))
		HC_Close_Segment ();        // restore scope

	return status;
#else
	return btk.Error (stream_readonly);
#endif
}


#endif

