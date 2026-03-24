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
// $Header: /files/homes/master/cvs/hoops_master/hoops_stream/source/HOpcodeHandler.cpp,v 1.439 2010-11-24 00:39:11 covey Exp $
//

#include "HStream.h"
#include "BInternal.h"

#include "HPolyhedron.h"

// NOTE: this table corresponds to enum TKO_Generic_Size_Units
static char const * generic_units_table[] = {
	"oru", "sru", "wru", "points", "pixels", "%", "wsu",
	""								//
};


#ifdef _DEBUG
#ifdef _MSC_VER
#  undef ASSERT
#define ASSERT(x) ((!(x))?__debugbreak():1)
#else
#  include <assert.h>
#  undef ASSERT
#  define ASSERT(x) assert(x)
#endif
#else
#  ifndef DO_NOTHING
#    define DO_NOTHING(x)	do if (0 && (x)) {} while (0)
#  endif
#  undef ASSERT
#  define ASSERT(x) DO_NOTHING(x)
#endif


////////////////////////////////////////

#define READ_INT(x,cp) do {						\
			bool    negative = false;	\
			x = 0;								\
			if (*cp == '-')						\
				{ negative = true;  ++cp; }		\
			while (*cp >= '0' && *cp <= '9') {	\
				x *= 10;						\
				x += (*cp++ - '0');				\
			}									\
			if (negative) x = -x;				\
		} while (0)							   //

////////////////////////////////////////



TK_Status HTK_Open_Segment::Execute (BStreamFileToolkit & tk) alter {
	HStreamFileToolkit &	htk = *(HStreamFileToolkit *)&tk;
	char					name[4096];
	HC_KEY					key;
	char *					cp;

	strcpy (name, GetSegment());

	if (name[0] == '/' && name[1] != '\0' && htk.GetPrependRootSegment())
		sprintf(name, "%s%s", htk.GetPrependRootSegment(), GetSegment()); 

	key = HC_KCreate_Segment (name);

	if (key >= 0) {
		char		scope[32];
		HC_KEY		renumbered = key;

		HC_Open_Segment (name);
			HC_Open_Segment ("..");
				HC_Show_Key_Status (renumbered, scope);
				key = HC_KRenumber_Key (renumbered, -1, "irrelevant");
				HC_Renumber_Key (key, renumbered, scope);
			HC_Close_Segment ();
		HC_Close_Segment ();
	}

	add_segment (htk, key);
	set_last_key (htk, key);

	// try to find names indicating temporaries of unnamed segments
	while ((cp = strrchr (name, '$')) != null) {
		char *          tmp = strchr (cp, '/');

		if (tmp != null)
			*tmp = '\0';  // remove further subsegments

		// aat least one char after $
		tmp = cp + 1;
		if (*tmp == '\0') {
			// nothing after $
			*cp = '\0'; // chop
			continue;   // and retry
		}

		// and all remaining characters should be hex
		while (*tmp) {
			if (*tmp >= '0' && *tmp <= '9' ||
				*tmp >= 'a' && *tmp <= 'f' ||
				*tmp >= 'A' && *tmp <= 'F') { /* ok */ }
			else {
				*cp = '\0';
				cp = null;  // ignore this $
				break;
			}
			tmp++;
		}
		if (cp == null) continue;

		// and the $ should be at the beginning of a segment name
		if (cp == name || cp[-1] == '/') {  // first char, or right after a /
			// looks like the right form
			key = HC_KCreate_Segment (name);
			htk.add_unnamed_segment (key);
		}

		*cp = '\0'; // chop here, retry on parent next
	}

	return TK_Normal;
}

TK_Status HTK_Open_Segment::Interpret (BStreamFileToolkit & tk, HC_KEY key, char const * name) alter {
	UNREFERENCED (key);
#ifndef HSTREAM_READONLY
	UNREFERENCED (tk);

	SetSegment (name);

	return TK_Normal;
#else
	UNREFERENCED (name);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Open_Segment);

////////////////////////////////////////

TK_Status HTK_Close_Segment::Execute (BStreamFileToolkit & tk) alter {
	// NOTE: we don't actually have to close the segment, since we don't
	// keep it open...
	set_last_key (tk, remove_segment (tk));

	return TK_Normal;
}

TK_Status HTK_Close_Segment::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	UNREFERENCED (tk);
	return TK_Normal;       // user may overload, so allow calling through
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Close_Segment);

////////////////////////////////////////

TK_Status HTK_Reopen_Segment::Execute (BStreamFileToolkit & tk) alter {
	TK_Status       status = TK_Normal;
	HC_KEY          key;

	if ((status = tk.IndexToKey (GetIndex(), key)) != TK_Normal)
		return tk.Error();

	add_segment (tk, key);
	set_last_key (tk, key);			 

	return status;
}


TK_Status HTK_Reopen_Segment::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;
	int             index;


	if ((status = tk.KeyToIndex (key, index)) != TK_Normal)
		return tk.Error();

	SetIndex (index);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Reopen_Segment);

////////////////////////////////////////

TK_Status HTK_LOD::Execute (BStreamFileToolkit & tk) alter 
{
	TK_Status status = TK_Normal;     // assume success
	int i, j;
	const char *error_string = null;

	for (i = 1; i <= m_highest_level && status == TK_Normal; i++) {
		HC_Open_LOD(i);
			for (j = 0; j < m_num_primitives[i]; j++) {
				status = m_primitives[i][j]->Execute (tk);
			}
		HC_Close_LOD();
	}
	if (status == TK_Error)
		return tk.Error(error_string);

	return TK_Normal;
}


#define LOD_MAX_LEVEL 8

TK_Status HTK_LOD::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter 
{
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	HStreamFileToolkit &	htk = *(HStreamFileToolkit *)&tk;
	TK_Status				status = TK_Normal;     // assume success
	int						i, j, count;
	HC_KEY					subkey;
	char					type[1024];
	const char *			error_string = null;
    
	m_num_primitives = new int[LOD_MAX_LEVEL];
	m_primitives = new BBaseOpcodeHandler **[LOD_MAX_LEVEL];
	memset(m_num_primitives, 0, LOD_MAX_LEVEL * sizeof(int));
	memset(m_primitives, 0, LOD_MAX_LEVEL * sizeof(BBaseOpcodeHandler **));

	for (i = 1; i < LOD_MAX_LEVEL && status == TK_Normal; i++) {
		HC_Open_LOD(i);
			HC_Begin_Contents_Search(".", "geometry");
				HC_Show_Contents_Count(&count);
				m_num_primitives[i] = count;
				if (count) {
					m_highest_level = i;
					m_primitives[i] = new BBaseOpcodeHandler *[count];
					HC_Reverse_Contents_Search();
					for (j = 0; j < count; j++) {
						if (!HC_Find_Contents(type, &subkey)) {
							error_string = "HOOPS reported an incorrect number of primitives in LOD";
							status = TK_Error;
						}
						if ((status = htk.StringToHandler (type, &m_primitives[i][j])) == TK_Error)
							break;
						// -2 is a special value to indicate we want the base resolution, 
						// suppressing any multipass revisitation
						if ((status = m_primitives[i][j]->Interpret (tk, subkey, -2)) == TK_Error)
				break;
					}
				}
			HC_End_Contents_Search();
		HC_Close_LOD();
	}
	if (status == TK_Error)
		return tk.Error(error_string);

	UNREFERENCED (tk);
	return status;

#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_LOD);

////////////////////////////////////////

TK_Status HTK_Renumber::Execute (BStreamFileToolkit & tk) alter {
	TK_Status		status = TK_Normal;     // assume success
	ID_Key			last_key;

	//following line assumes that there is exactly one key in the toolkit's m_last_keys array.
	//if there isn't, we deserve the error.
	if ((status = tk.GetLastKey(last_key)) != TK_Normal)
		return status;

	switch (Opcode()) {
		case TKE_Renumber_Key_Global:
			HC_Renumber_Key (last_key, GetKey(), "g");
			break;

		case TKE_Renumber_Key_Local:
			HC_Renumber_Key (last_key, GetKey(), "l");
			break;

		case TKE_Priority:
#ifndef TEST_RIG_1
			HC_Set_Priority (last_key, (long)(POINTER_SIZED_INT)GetKey());
#endif
			break;

		default:
			status = tk.Error("unrecognized opcode in HTK_Renumber::Execute");
			break;
	}

	return status;
}

TK_Status HTK_Renumber::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
	return tk.Error();
}

IMPLEMENT_CLONE_OPCODE (HTK_Renumber);

////////////////////////////////////////

TK_Status HTK_Referenced_Segment::Write (BStreamFileToolkit & tk) alter {
#ifndef HSTREAM_READONLY
	HStreamFileToolkit &	htk = *(HStreamFileToolkit *)&tk;
	TK_Status				 status = TK_Normal;

	switch (mh_stage) {
		case 0: {
			// if follow-cross-references, and we haven't seen the segment, send out the segment first...
			if (m_key == -1) {

				// named style

				if (tk.GetTargetVersion() < 1815)
					return TK_Normal;

				if (m_referee != null) {

					if ((status = m_referee->Write (htk)) != TK_Normal)
						return status;

					mh_stage = -1;
					return status;
				}
			}
			else {

				if (m_follow && m_referee == null && !Find_Item (htk, m_key)) {
					Internal_Segment_Processor *	sp = new Internal_Segment_Processor (m_key, m_string);
					// Note: processor starts new root by default, but use current root if it's relative
					if (m_string[0] != '/')
						sp->SetRoot (GetRoot());

					m_referee = sp;
				}

				if (m_referee != null) {

					if ((status = m_referee->Write (htk)) != TK_Normal)
						return status;
				}
			}

			mh_stage++;
		}   nobreak;

		case 1: {
			// did we tag that segment (such as revisiting an included segment)
			if (m_referee != null && htk.m_pending_tags != null && htk.m_pending_tags->m_key == m_key) {
				BBaseOpcodeHandler *        handler = htk.opcode_handler (TKE_Tag);
				Internal_Pending_Tag *      victim = htk.m_pending_tags;
				int                         index;
				char                        buffer[32];

				status = htk.KeyToIndex (m_key, index);
				if (status == TK_NotFound) {    // must be a new item
					index = tk.NextTagIndex();
					tk.AddIndexKeyPair (index, m_key);

					if (tk.GetLogging() && tk.GetLoggingOptions (TK_Logging_Tagging)) {
						sprintf (buffer, "(%d)", index);
						handler->SetLoggingString (buffer);
					}
				}

				if ((status = handler->Write (htk)) != TK_Normal)
					return status;
				handler->Reset();

				// safe to delete the pending tag once it's written
				htk.m_pending_tags = victim->m_next;
				delete victim;
			}
			mh_stage++;
		}   nobreak;

		case 2: {
			// now we can write the reference
			if ((status = TK_Referenced_Segment::Write (htk)) != TK_Normal)
				return status;
			mh_stage = -1;
		}   break;

		default:
			return tk.Error();
	}

	return status;
#else
	return tk.Error (stream_readonly);
#endif
}

TK_Status HTK_Referenced_Segment::Execute (BStreamFileToolkit & tk) alter {
	HC_KEY          key = -1;
	HStreamFileToolkit &	htk = *(HStreamFileToolkit *)&tk;
	char			name[4096];
	char			*use_name = GetSegment();

	if (use_name[0] == '/' && use_name[1] != '\0' && htk.GetPrependRootSegment()) {
		use_name = name;
		sprintf(name, "%s%s", htk.GetPrependRootSegment(), GetSegment()); 
	}

	switch (Opcode()) {
		case TKE_Include_Segment: {
			key = HC_KConditional_Include (use_name, m_condition);
			set_last_key (tk, key);
		}   break;

		case TKE_Style_Segment: {
			key = HC_KConditional_Style (use_name, m_condition);
			set_last_key (tk, key);
		}   break;

		case TKE_Named_Style: {
			key = HC_Named_Style_Segment (use_name);
			set_last_key (tk, key);
		}   break;
	}

	return TK_Normal;
}

static char const * const default_roots[] = {"?Include Library", "?Style Library"};

static TK_Status make_path_relative_segment(HStreamFileToolkit & htk, HC_KEY & m_key, HC_KEY root_key, char * & segname)
{
	char *		segbuf = segname;
	int			length, i;
	int			relative_limit = 64;    // = tk.GetRelativePathLimit();

	if (m_key > -1) {
		char            parent[1024];
		char            scope[32];
		char *          cp;
		HC_KEY          tmpkey = m_key;

		strcpy (parent, segname);
		cp = strrchr (parent, '/');
		if (cp != parent)
			*cp = '\0';
		else
			parent[1] = '\0';

		HC_Open_Segment (parent);
		HC_Show_Key_Status (tmpkey, scope);
		m_key = HC_KRenumber_Key (tmpkey, -1, "irrelevant");
		HC_Renumber_Key (m_key, tmpkey, scope);
		HC_Close_Segment ();
	}

	/* does this rerfer to a segment we don't want processed? */
	if (htk.SegmentIsExcluded (m_key))
		return TK_Abort;

	// see if we can make a relative path
	if (relative_limit > 0) {
		char            curbuf[4096];
		char            root[4096];
		char *          current = curbuf;
		bool            rooted = false;

		HC_Show_Pathname_Expansion (".", current);
		strcat (current, "/");

		HC_Show_Segment (root_key, root);
		strcat (root, "/");

		// to qualify, both segments must be under the "root" segment
		length = (int)strlen (root);
		if (streqn (current, root, length) && streqn (segname, root, length))
			rooted = true;
		else /* if (tk.UseStandardRelativePaths()) */ {
			// or under a "standard" root instead of the current subtree
			for (i=0; i<countof(default_roots); i++) {
				HC_Show_Pathname_Expansion (default_roots[i], root);
				strcat (root, "/");
				length = (int)strlen (root);
				if (streqn (current, root, length) && streqn (segname, root, length)) {
					rooted = true;
					break;
				}
			}
		}

		if (rooted) {
			char *      cp;
			int         levels = 0;

			// done with root, use it to save segname if we later decide we don't want the relative path
			strcpy (root, segname);

			segname += length;
			current += length;

			while ((cp = strchr (current, '/')) != null) {
				length = (int)(POINTER_SIZED_INT)(cp - current + 1);      // include '/' in compare (and subsequent removal if matched)
				if (streqn (segname, current, length)) {
					segname += length;
					current += length;
				}
				else
					break;
			}

			if (*current != '\0') {       // if empty, segname is somewhere *under* current and in proper form
				cp = current;
				// each remaining '/' in current is another level
				while ((cp = strchr (cp, '/')) != null) {
					++levels;
					++cp;   // continue looking after this one
				}
			}

			if (levels > relative_limit) {
				segname = segbuf;
				strcpy (segname, root);     // back to original
			}
			else if (levels > 0) {
				// done with current, use curbuf as temp space to build final value
				curbuf[0] = '\0';
				for (i=0; i<levels; i++) {
					strcat (curbuf, "../");
				}
				strcat (curbuf, segname);

				segname = segbuf;
				strcpy (segname, curbuf);
			}
		}
	}

	// finish processing whatever's left
	length = (int)strlen (segname);
	for (i=0; i<length; ++i)
		if (segname[i] == '@')
			segname[i] = '$';

	return TK_Normal;
}

TK_Status HTK_Referenced_Segment::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	HStreamFileToolkit &	htk = *(HStreamFileToolkit *)&tk;
	char					segbuf[4096];
	char					condition[4096];
	char *					segname = segbuf;

	UNREFERENCED (tk);

	switch (Opcode()) {
		case TKE_Include_Segment: {
			m_key = HC_KShow_Include_Segment (key);
			HC_Show_Conditional_Include (key, segname, condition);
		}   break;

		case TKE_Style_Segment: {
			m_key = HC_KShow_Style_Segment (key);
			HC_Show_Conditional_Style (key, segname, condition);
		}   break;

		case TKE_Named_Style: {
			HC_Show_Named_Style_Segment (key, segname);

			condition[0] = '\0';

			SetSegment (segname);
			SetCondition (condition);

			return TK_Normal;
		}	nobreak;
	}

	if (m_key != -1) {
		TK_Status local_status = make_path_relative_segment(htk, m_key, GetRoot(), segname);

		if (local_status != TK_Normal)
			return local_status;
	}

	SetSegment (segname);
	SetCondition (condition);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

void HTK_Referenced_Segment::Reset () alter {
	mh_stage = 0;
	TK_Referenced_Segment::Reset();
}

IMPLEMENT_CLONE_OPCODE (HTK_Referenced_Segment);

////////////////////////////////////////

TK_Status HTK_Reference::Write (BStreamFileToolkit & tk) alter {
#ifndef HSTREAM_READONLY
	HStreamFileToolkit &	htk = *(HStreamFileToolkit *)&tk;
	TK_Status				status = TK_Normal;

	if (tk.GetTargetVersion() < 1520)
		return TK_Normal;

	switch (mh_stage) {
		case 0: {
#if 0
			// if follow-cross-references, and we haven't seen the segment, send out the segment first...
			if (htk.m_revisit_state == HStreamFileToolkit::Force && m_referee == null) {
				int                         index;

				if (htk.KeyToIndex (m_key, index) == TK_NotFound) {
					char						type[64];

					HC_Show_Key_Type (m_key, type);
					if (streq (type, "segment"))
						m_referee = new Internal_Segment_Processor (m_key, "");
					else {
						unsigned char				opcode;

						if ((status = htk.StringToOpcode (type, &opcode)) == TK_Normal) {
							status = htk.GetOpcodeHandler(opcode)->Clone(tk, &m_referee);

							m_referee->Interpret (tk, m_key);
						}
					}
				}
				else
					return TK_Normal;	// already written during a Force pass, we don't need to rewrite
			}
#endif

			if (m_referee != null && tk.KeyToIndex (m_key, m_index) == TK_NotFound) {
				set_last_key (tk, m_key);   // also make available for tagging
				if ((status = m_referee->Write (htk)) != TK_Normal)
					return status;
			}

			mh_stage++;
		}   nobreak;

		case 1: {
			// did we tag that segment (such as revisiting an included segment)
			if (m_referee != null && htk.m_pending_tags != null && htk.m_pending_tags->m_key == m_key) {
				BBaseOpcodeHandler *        handler = htk.opcode_handler (TKE_Tag);
				Internal_Pending_Tag *      victim = htk.m_pending_tags;
				int                         index;
				char                        buffer[32];

				status = htk.KeyToIndex (m_key, index);
				if (status == TK_NotFound) {    // must be a new item
					index = tk.NextTagIndex();
					tk.AddIndexKeyPair (index, m_key);

					if (tk.GetLogging() && tk.GetLoggingOptions (TK_Logging_Tagging)) {
						sprintf (buffer, "(%d)", index);
						handler->SetLoggingString (buffer);
					}
				}

				if ((status = handler->Write (htk)) != TK_Normal)
					return status;
				handler->Reset();

				// safe to delete the pending tag once it's written
				htk.m_pending_tags = victim->m_next;
				delete victim;

				//m_index = index;

				// done with the referee, will come back to the reference
				tk.set_context_key (mh_owner);
				set_last_key (tk, m_this_key);
				Revisit (tk);

				mh_stage = -1;

				return TK_Normal;
			}
			mh_stage++;
		}   nobreak;

		case 2: {
			// now we can write the reference
			if ((status = TK_Reference::Write (htk)) != TK_Normal)
				return status;
			mh_stage = -1;
		}   break;

		default:
			return tk.Error();
	}

	return status;
#else
	return tk.Error (stream_readonly);
#endif
}

TK_Status HTK_Reference::Execute (BStreamFileToolkit & tk) alter {
	TK_Status		status;
	HC_KEY          key = -1;

	if ((status = tk.IndexToKey (m_index, key)) != TK_Normal)
		return status;

	key = HC_KConditional_Reference_By_Key (key, m_condition);
	set_last_key (tk, key);

	return TK_Normal;
}

TK_Status HTK_Reference::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	HStreamFileToolkit &	htk = *(HStreamFileToolkit *)&tk;
	char					condition[4096];

	m_this_key = key;	// remember in case we need to restore after processing the referenced item

	m_key = HC_KShow_Conditional_Reference (key, condition);

	if (tk.KeyToIndex (m_key, m_index) == TK_NotFound) {
		if (htk.m_revisit_state == HStreamFileToolkit::Force) {	// if Force, ::Write will validate the index
			char						type[64];

			HC_Show_Key_Type (m_key, type);
			if (streq (type, "segment"))
				m_referee = new Internal_Segment_Processor (m_key, "");
			else {
				TK_Status					status;
				unsigned char				opcode;

				if ((status = htk.StringToOpcode (type, &opcode)) == TK_Normal) {
					status = htk.GetOpcodeHandler(opcode)->Clone(tk, &m_referee);

					m_referee->Interpret (tk, m_key);
				}
			}
		}
		else {
			m_index = -1;
			Revisit (tk);
			return TK_Revisit;
		}
	}

	SetCondition (condition);

	if (key == tk.RevisitKey())			// revisiting directly, not in a containing segment
		mh_owner = tk.RevisitOwner();	// so we'll need to generate a reopen/close ourselves

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

bool   HTK_Reference::NeedsContext (BStreamFileToolkit & tk) const {
	UNREFERENCED (tk);

	if (m_referee != null)
		return false;		// will write out the referenced object

	return mh_owner != -1;
}


void HTK_Reference::Reset () alter {
	mh_stage = 0;
	mh_owner = -1;
	TK_Reference::Reset();
}

IMPLEMENT_CLONE (HTK_Reference);

////////////////////////////////////////

HTK_Instance::HTK_Instance (int from_index, int from_variant, int to_index, int to_variant,
						   int options, float const * xform)
	: TK_Instance (from_index, from_variant, to_index, to_variant, options, xform) {
}


TK_Status HTK_Instance::Execute (BStreamFileToolkit & tk) alter {
	TK_Status		status = TK_Normal;
	HC_KEY			oldkey = -1;
	HC_KEY			newkey = -1;
	char			type[32];
	int				pointcount;
	float *			points = null;
	int				faces = 0;
	int				rows = 0, columns = 0;
	bool			is_mesh = false;

	if ((status = tk.IndexToKey (m_from_index, oldkey)) != TK_Normal)
		return tk.Error();

	if (m_to_index != -1) {
		if ((status = tk.IndexToKey (m_to_index, newkey)) != TK_Normal)
			return tk.Error();
	}

	HC_Show_Key_Type (oldkey, type);

	if (streq (type, "mesh")) {
		is_mesh = true;

		HC_Show_Mesh_Size (oldkey, &rows, &columns);

		pointcount = rows * columns;
		points = new float [3*pointcount];
		faces = 2*(rows-1)*(columns-1);

		HC_Show_Mesh (oldkey, &rows, &columns, points);

		HC_Compute_Transformed_Points (rows*columns, points, m_matrix, points);
		newkey = HC_KInsert_Mesh (rows, columns, points);

		// need original points back if transforming normals
		HC_Show_Mesh (oldkey, &rows, &columns, points);
	}
	else if (streq (type, "shell")) {
		int             listlen;
		int             flistlen;
		int *           list = null;
		int *           flist = null;
		int             i;

		if (m_from_variant > 0) {
			HC_Open_Geometry (oldkey);
				HC_Open_LOD (m_from_variant);
		}

		if ((m_options & Instance_By_Tristrip) != 0) {
			HC_Show_Shell_By_Tristrips_Size (oldkey, &pointcount, &listlen, &flistlen);

			points = new float [3*pointcount];
			list = new int [listlen];
			flist = new int [flistlen];

			HC_Show_Shell_By_Tristrips (oldkey, &pointcount, points, &listlen, list, &flistlen, flist);

			faces = 0;
			for (i = 0; i < flistlen; ++i)
				if (faces <= flist[i])
					faces = flist[i] + 1;   // +1 to convert index to pointcount

			HC_Compute_Transformed_Points (pointcount, points, m_matrix, points);

			if (m_to_index != -1) {
				HC_Open_Geometry (newkey);
					HC_Open_LOD (m_to_variant);
						HC_Insert_Shell_By_Tristrips (pointcount, points,  listlen, list, 0, null);
					HC_Close_LOD ();
				HC_Close_Geometry ();
			}
			else
				newkey = HC_KInsert_Shell_By_Tristrips (pointcount, points,  listlen, list, 0, null);

			// need original points back if transforming normals
			HC_Show_Shell_By_Tristrips (oldkey, &pointcount, points, &listlen, list, null, null);

			delete [] flist;
		}
		else {
			HC_Show_Shell_Size (oldkey, &pointcount, &listlen);

			points = new float [3*pointcount];
			list = new int [listlen];

			HC_Show_Shell (oldkey, &pointcount, points, &listlen, list);

			i = 0;
			faces = 0;
			while (i < listlen) {
				int     face_size = list[i];

				if (face_size < 0)
					face_size = -face_size;
				else
					++faces;
				i += face_size + 1;
			}

			HC_Compute_Transformed_Points (pointcount, points, m_matrix, points);

			if (m_to_index != -1) {
				HC_Open_Geometry (newkey);
					HC_Open_LOD (m_to_variant);
						HC_Insert_Shell (pointcount, points, listlen, list);
					HC_Close_LOD ();
				HC_Close_Geometry ();
			}
			else
				newkey = HC_KInsert_Shell (pointcount, points, listlen, list);

			// need original points back if transforming normals
			HC_Show_Shell (oldkey, &pointcount, points, &listlen, list);
		}

		if (m_from_variant > 0) {
				HC_Close_LOD ();
			HC_Close_Geometry ();
		}

		delete [] list;
	}
	else {
		char            buffer[64];

		sprintf (buffer, "instance of unhandled type: %s", type);
		return tk.Error (buffer);
	}

	if (m_from_variant == 0 && m_to_variant == 0) {
		// copy any vertex attributes
		int						exists;
		float					normal[4];  // allow for a plane, not just a vector
		float					parameter[3];
		char					color[80];
		int						i;
		int						normalcount, paramcount, colorcount;

		HC_Open_Geometry (oldkey);
			normalcount = HC_Show_Existence ("vertex normals");
			paramcount = HC_Show_Existence ("vertex parameters");
			colorcount = HC_Show_Existence ("vertex colors");
			if (normalcount || paramcount || colorcount) {
				for (i = 0; i < pointcount; i++) {
					exists = 0;

					HC_Open_Vertex (i);
						if (normalcount == pointcount ||
							(normalcount > 0 && HC_Show_Existence ("normal"))) {
							HC_Show_Normal (&normal[0], &normal[1], &normal[2]);
							normal[3] = -(normal[0]*points[3*i+0] + normal[1]*points[3*i+1] + normal[2]*points[3*i+2]);
							HC_Compute_Transformed_Plane (normal, m_matrix, normal);
							exists |= 1;
						}

						if (colorcount == pointcount ||
							(colorcount > 0 && HC_Show_Existence ("color"))) {
							HC_Show_Color (color);
							exists |= 2;
						}

						if (paramcount == pointcount ||
							(paramcount > 0 && HC_Show_Existence ("parameter"))) {
							int     size;   // always returns 3 for now
							HC_Show_Parameter (&size, parameter); 
							exists |= 4;
						}
					HC_Close_Vertex();

					if (exists != 0) {
						HC_Open_Geometry (newkey);
							HC_Open_Vertex (i);
								if ((exists & 1) != 0)
									HC_Set_Normal (normal[0], normal[1], normal[2]);

								if ((exists & 2) != 0)
									HC_Set_Color (color);

								if ((exists & 4) != 0)
									HC_Set_Parameter (3, parameter);
							HC_Close_Vertex ();
						HC_Close_Geometry ();
					}
				}
			}

			if (HC_Show_Existence ("face normals") != 0 ||
				HC_Show_Existence ("face colors")) {
				for (i = 0; i < faces; i++) {
					int         face_num = i;
					exists = 0;

					// watch for bizarre mesh face numbering...
					if (is_mesh) {
				int     row = (i/2)/(columns-1);
				int     col = (i/2)%(columns-1);

						face_num = (row * columns) + col;
				if (i & 1)
				face_num = -(face_num + columns + 1);
					}

					HC_Open_Face (face_num);
						if (HC_Show_Existence ("normal")) {
							HC_Show_Normal (&normal[0], &normal[1], &normal[2]);
							// need a sample point...
							normal[3] = 0.0f; //-(normal[0]*points[3*i+0] + normal[1]*points[3*i+1] + normal[2]*points[3*i+2]);
							HC_Compute_Transformed_Plane (normal, m_matrix, normal);
							exists |= 1;
						}

						if (HC_Show_Existence ("color")) {
							HC_Show_Color (color);
							exists |= 2;
						}
					HC_Close_Face();

					if (exists != 0) {
						HC_Open_Geometry (newkey);
							HC_Open_Face (face_num);
								if ((exists & 1) != 0)
									HC_Set_Normal (normal[0], normal[1], normal[2]);

								if ((exists & 2) != 0)
									HC_Set_Color (color);
							HC_Close_Face ();
						HC_Close_Geometry ();
					}
				}
			}
		HC_Close_Geometry();
	}

	set_last_key (tk, newkey);

	delete [] points;

	return status;
}

TK_Status HTK_Instance::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	// never called -- instances are always manually created
	UNREFERENCED (key);
	UNREFERENCED (variant);
	return tk.Error();
}

IMPLEMENT_CLONE (HTK_Instance);

////////////////////////////////////////

TK_Status HTK_Delete_Object::Execute (BStreamFileToolkit & tk) alter {
	TK_Status		status = TK_Normal;
	HC_KEY			key;

	if ((status = tk.IndexToKey (GetIndex(), key)) != TK_Normal)
		return tk.Error();

	HC_Delete_By_Key (key);
	// remove dictionary entry?

	return status;
}


TK_Status HTK_Delete_Object::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	// never called -- opcode is for adding changes onto an existing stream
	return tk.Error();
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Delete_Object);

////////////////////////////////////////


TK_Status HTK_Bounding::Execute (BStreamFileToolkit & tk) alter {
	TK_Status		status = TK_Normal;     // assume success
	HC_KEY			key = -1;

	// informational box can be "included" by setting it on a dummy subsegment
	if (Opcode() == TKE_Bounding_Info)
		key = HC_KOpen_Segment ("");

	switch (m_type) {
		case 0:
			HC_Set_Bounding_Cuboid (&m_values[0], &m_values[3]);
			break;

		case 1:
			HC_Set_Bounding_Sphere (&m_values[0], m_values[3]);
			break;

		default:
			status = tk.Error();
			break;
	}

	if (Opcode() == TKE_Bounding_Info) {
		HC_Close_Segment ();
		HC_Delete_By_Key (key);
	}

	return status;
}

TK_Status HTK_Bounding::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY

	switch (Opcode()) {
		case TKE_Bounding: {
			char        type[32];

			HC_Show_Bounding_Info (type);

			if (streqn (type, "type=cuboid", 11)) {
				m_type = 0;
				m_is_valid = HC_Show_Bounding_Cuboid (&m_values[0], &m_values[3]);
			}
			else if (streqn (type, "type=sphere", 11)) {
				m_type = 1;
				m_is_valid = HC_Show_Bounding_Sphere (&m_values[0], &m_values[3]);
			}
			else {
				m_type = -1;
				return tk.Error();
			}
		}   break;

		case TKE_Bounding_Info:
			m_is_valid = HC_Compute_Circumcuboid (".", &m_values[0], &m_values[3]);
			m_type = 0;
			break;

		default:
			return tk.Error();
			break;
	}

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE_OPCODE (HTK_Bounding);

////////////////////////////////////////

TK_Status HTK_Streaming::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);
	HC_Set_Streaming_Mode ("on");
	return TK_Normal;
}

TK_Status HTK_Streaming::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char        setting[8];

	UNREFERENCED (tk);

	HC_Show_Streaming_Mode (setting);
	m_flag = (setting[1] == 'n');

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Streaming);


////////////////////////////////////////

TK_Status HTK_Point::Execute (BStreamFileToolkit & tk) alter {
	TK_Status		status = TK_Normal;     // assume success
	HC_KEY			key = -1;
	float const *	point = GetPoint();

	switch (Opcode()) {
		case TKE_Marker:
			key = HC_KInsert_Marker (point[0], point[1], point[2]);

			set_last_key (tk, key);
			break;

		case TKE_Distant_Light:
			key = HC_KInsert_Distant_Light (point[0], point[1], point[2]);
			if (m_options & TKO_Light_Camera_Relative)
				HC_Set_Geometry_Options(key, "camera relative");

			set_last_key (tk, key);
			break;

		case TKE_Local_Light:
			key = HC_KInsert_Local_Light (point[0], point[1], point[2]);
			if (m_options & TKO_Light_Camera_Relative)
				HC_Set_Geometry_Options(key, "camera relative");

			set_last_key (tk, key);
			break;

		case TKE_Text_Path:
			if (tk.GeometryIsOpen()) {
				HC_KEY					last_key;

				if ((status = tk.GetLastKey(last_key)) != TK_Normal)
					return status;
				HC_Open_Geometry (last_key);
			}

			HC_Set_Text_Path (point[0], point[1], point[2]);

			if (tk.GeometryIsOpen())
				HC_Close_Geometry ();
			break;

		default:
			return tk.Error();
	}

	return status;
}

TK_Status HTK_Point::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	float		point[3];
	char		tempstr[256];

	switch (Opcode()) {
		case TKE_Marker:
			HC_Show_Marker (key, &point[0], &point[1], &point[2]);
			break;

		case TKE_Distant_Light:
			HC_Show_Distant_Light (key, &point[0], &point[1], &point[2]);
			break;

		case TKE_Local_Light:
			HC_Show_Local_Light (key, &point[0], &point[1], &point[2]);
			break;

		case TKE_Text_Path:
			HC_Show_Text_Path (&point[0], &point[1], &point[2]);
			break;

		default:
			return tk.Error();
	}

	if (Opcode() == TKE_Local_Light || Opcode() == TKE_Distant_Light) {
		HC_Show_Geometry_Options (key, tempstr);
		if (streq (tempstr, "camera relative"))
			m_options |= TKO_Light_Camera_Relative;
	}

	SetPoint (point);

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}


IMPLEMENT_CLONE_OPCODE (HTK_Point);

////////////////////////////////////////////////////////////////////////////////

TK_Status HTK_Line::Execute (BStreamFileToolkit & tk) alter {
	TK_Status		status = TK_Normal;     // assume success
	HC_KEY			key;
	float const *	points = GetPoints();

	switch (Opcode()) {
		case TKE_Line:
			key = HC_KInsert_Line (points[0], points[1], points[2], points[3], points[4], points[5]);
			set_last_key (tk, key);
			break;

		case TKE_Infinite_Line:
			key = HC_KInsert_Infinite_Line (points[0], points[1], points[2], points[3], points[4], points[5]);
			set_last_key (tk, key);
			break;

		case TKE_Infinite_Ray:
			key = HC_KInsert_Infinite_Ray (points[0], points[1], points[2], points[3], points[4], points[5]);
			set_last_key (tk, key);
			break;

		default:
			return tk.Error();
	}

	return status;
}

TK_Status HTK_Line::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	float           points[6];

	UNREFERENCED (tk);

	switch (Opcode()) {
		case TKE_Line:
			HC_Show_Line (key, &points[0], &points[1], &points[2], &points[3], &points[4], &points[5]);
			break;

		case TKE_Infinite_Line:
			HC_Show_Infinite_Line (key, &points[0], &points[1], &points[2], &points[3], &points[4], &points[5]);
			break;

		case TKE_Infinite_Ray:
			HC_Show_Infinite_Ray (key, &points[0], &points[1], &points[2], &points[3], &points[4], &points[5]);
			break;

		default:
			return tk.Error();
	}

	SetPoints (points);

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}


IMPLEMENT_CLONE_OPCODE (HTK_Line);

////////////////////////////////////////


TK_Status HTK_Polypoint::Execute (BStreamFileToolkit & tk) alter {
	TK_Status		status = TK_Normal;     // assume success
	HC_KEY			key;

	switch (Opcode()) {
		case TKE_Polygon:
			key = HC_KInsert_Polygon (GetCount(), GetPoints());
			set_last_key (tk, key);
			break;

		case TKE_Polyline:
			key = HC_KInsert_Polyline (GetCount(), GetPoints());
			set_last_key (tk, key);
			break;

		default:
			status = tk.Error();
			break;
	}

	return status;
}

TK_Status HTK_Polypoint::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	int				count;

	switch (Opcode()) {
		case TKE_Polygon:
			HC_Show_Polygon_Count (key, &count);
			SetPoints (count);
			HC_Show_Polygon (key, &count, GetPoints());
			break;

		case TKE_Polyline:
			HC_Show_Polyline_Count (key, &count);
			SetPoints (count);
			HC_Show_Polyline (key, &count, GetPoints());
			break;

		default:
			return tk.Error();
			break;
	}

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE_OPCODE (HTK_Polypoint);

////////////////////////////////////////


TK_Status HTK_NURBS_Curve::Execute (BStreamFileToolkit & tk) alter {
	TK_Status		status = TK_Normal;     // assume success
	HC_KEY			key;
	float *			weights = null;
	float *			knots = null;

	if (m_optionals & NC_HAS_WEIGHTS)
		weights = m_weights;
	if (m_optionals & NC_HAS_KNOTS)
		knots = m_knots;

	key = HC_KInsert_NURBS_Curve (m_degree, m_control_point_count, 
								  m_control_points, weights, knots,
								  m_start, m_end);
	set_last_key (tk, key);

	return status;
}

TK_Status HTK_NURBS_Curve::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	int				deg;
	int				weight_count;
	int				knot_count;
	float *			weights = null;
	float *			knots = null;

	m_optionals = 0;

	HC_Show_NURBS_Curve_Size (key, &deg, &m_control_point_count, &weight_count, &knot_count);
	set_curve (deg, m_control_point_count);     // allocate space

	if (tk.GetTargetVersion() < 650) { // older readers only work right if all the fields are set
		weight_count = m_control_point_count;
		knot_count = m_control_point_count + deg + 1;
		m_optionals |= NC_HAS_START | NC_HAS_END;
	}

	if (weight_count > 0) {
		weights = m_weights;
		m_optionals |= NC_HAS_WEIGHTS;
	}
	if (knot_count > 0) {
		ASSERT(knot_count == m_control_point_count + deg + 1);
		m_knot_count_implicit = knot_count;
		knots = m_knots;
		m_optionals |= NC_HAS_KNOTS;
	}

	HC_Show_NURBS_Curve (key, &deg, &m_control_point_count, 
						 m_control_points, weights, knots, &m_start, &m_end);

	if (m_start != 0.0)
		m_optionals |= NC_HAS_START;
	if (m_end != 1.0)
		m_optionals |= NC_HAS_END;

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_NURBS_Curve);

////////////////////////////////////////

TK_Status HTK_NURBS_Surface::execute_trim(BStreamFileToolkit & tk, HT_NURBS_Trim * trim) alter {
	TK_Status		status = TK_Normal;     // assume success

	switch (trim->GetType()) {
		case NS_TRIM_POLY: {
			HC_Trim_NURBS_Surface_By_Poly (trim->GetCount(), trim->GetPoints());
		}   break;

		case NS_TRIM_CURVE: {
			float const *   weights = null;
			float const *   knots = null;

			if ((trim->GetOptions() & NS_TRIM_HAS_WEIGHTS) != 0)
				weights = trim->GetWeights();
			if ((trim->GetOptions() & NS_TRIM_HAS_KNOTS) != 0)
				knots = trim->GetKnots();

			HC_Trim_NURBS_Surface_By_Curve (trim->GetDegree(), trim->GetCount(), trim->GetPoints(),
											weights, knots, 0, 1);
		}   break;

		case NS_TRIM_COLLECTION: {
			HT_NURBS_Trim *ptr = trim->GetList();
			HC_Create_Trim_Collection();
			HC_Open_Trim(0);
			while(ptr != null) {
				execute_trim(tk, ptr); //recurse
				ptr = ptr->GetNext();
			}
			HC_Close_Trim();
		}   break;
	}
	return status;
}


TK_Status HTK_NURBS_Surface::Execute (BStreamFileToolkit & tk) alter {
	TK_Status		status = TK_Normal;     // assume success
	HC_KEY			key;
	float *			weights = null;
	float *			u_knots = null;
	float *			v_knots = null;
	HT_NURBS_Trim *	trim;

	if (m_optionals & NS_HAS_WEIGHTS)
		weights = m_weights;
	if (m_optionals & NS_HAS_KNOTS) {
		u_knots = m_u_knots;
		v_knots = m_v_knots;
	}

	key = HC_KInsert_NURBS_Surface (m_degree[0], m_degree[1], m_size[0], m_size[1], m_control_points,
									weights,  u_knots, v_knots);

	if ((trim = GetTrims()) != null) {
		HC_Open_Geometry (key);
		do {
			execute_trim(tk, trim);
			if (trim->GetOptions() & NS_TRIM_KEEP)
				HC_Set_Trim_Operation (0, "keep");
		} while ((trim = trim->GetNext()) != null);
		HC_Close_Geometry ();
	}

	set_last_key (tk, key);

	return status;
}

TK_Status HTK_NURBS_Surface::interpret_trim (BStreamFileToolkit & tk, int offset) alter {
#ifndef HSTREAM_READONLY
	TK_Status		status = TK_Normal;     // assume success
	int				trimcount, i;
	char			type[32];
	char			operation[32];
	HT_NURBS_Trim *	trim = NewTrim();
	HT_NURBS_Trim *	temp;

	HC_Show_Trim_Type (offset, type);

	if (type[5] == 'p') {   // trim Poly
		int                 count;

		HC_Show_Trim_Poly_Count (offset, &count);
		trim->SetPoly (count);
		HC_Show_Trim_Poly (offset, &count, trim->GetPoints());
	}
	else if (type[6] == 'o') { // trim cOllection
		trim->SetCollection();
		HC_Open_Trim (offset);
			HC_Show_Trim_Count (&trimcount);

			for (i = 0; i < trimcount; i++) {
				interpret_trim(tk, i); //recurse
				temp = m_trims;
				m_trims = m_trims->GetNext();  //pop one off the list
				temp->SetNext(trim->GetList());  //prepend onto trim's internal list
				trim->SetList(temp);
			}
		HC_Close_Trim ();
	}
	else {                  // trim cUrve
		int					count;
		int					degree;
		int					weight_count;
		int					knot_count;
		float *				weights = null;
		float *				knots = null;
		int					options = 0;

		HC_Show_Trim_Curve_Count (offset, &degree, &count, &weight_count, &knot_count);
		trim->SetCurve (degree, count);
		if (weight_count > 0) {
			options |= NS_TRIM_HAS_WEIGHTS;
			weights = trim->GetWeights();
		}
		if (knot_count > 0) {
			options |= NS_TRIM_HAS_KNOTS;
			knots = trim->GetKnots();
		}
		trim->SetOptions (options);
		HC_Show_Trim_Curve (offset, &degree, &count, trim->GetPoints(), weights, knots, null, null);
	}
	HC_Show_Trim_Operation (offset, operation);
	if (operation[0] == 'k')  // "keep", as opposed to "remove"
		trim->SetOptions(trim->GetOptions() | NS_TRIM_KEEP);

	return status;
#else
	UNREFERENCED (offset);
	return tk.Error (stream_readonly);
#endif
}

TK_Status HTK_NURBS_Surface::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	//    TK_Status       status = TK_Normal;     // assume success
	int				u_degree, v_degree;
	int				weight_count;
	int				u_knot_count, v_knot_count;
	float *			weights = null;
	float *			u_knots = null;
	float *			v_knots = null;
	int				trimcount;
	int				i;

	m_optionals = 0;

	HC_Show_NURBS_Surface_Size (key, &u_degree, &v_degree, &m_size[0], &m_size[1],
								&weight_count, &u_knot_count, &v_knot_count);
	SetSurface (u_degree, v_degree, m_size[0], m_size[1], null,  null,  null, null);

	if (weight_count > 0) {
		weights = m_weights;
		m_optionals |= NS_HAS_WEIGHTS;
	}
	if (u_knot_count > 0 || v_knot_count > 0) {
		if (u_knot_count > 0)
			u_knots = m_u_knots;
		if (v_knot_count > 0)
			v_knots = m_v_knots;
		m_optionals |= NC_HAS_KNOTS;
	}

	HC_Show_NURBS_Surface (key, &u_degree, &v_degree, &m_size[0], &m_size[1], m_control_points,
						   weights,  u_knots, v_knots);

	HC_Open_Geometry (key);
		HC_Show_Trim_Count (&trimcount);

		if (trimcount > 0)
			m_optionals |= NS_HAS_TRIMS;

		for (i=0; i<trimcount; ++i) {
			interpret_trim(tk, i);
		}
	HC_Close_Geometry ();

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_NURBS_Surface);

////////////////////////////////////////


TK_Status HTK_Area_Light::Execute (BStreamFileToolkit & tk) alter {
	TK_Status		status = TK_Normal;     // assume success
	HC_KEY			key;
	char const *	options;

	switch (GetOptions()) {
		case 0:		options = "";						break;
		case 1:		options = "bright side=front";		break;
		case 2:		options = "bright side=back";		break;
		case 3:		options = "bright side=both";		break;
		default:	return tk.Error();
	}

	key = HC_KInsert_Area_Light (GetCount(), GetPoints(), options);
	set_last_key (tk, key);

	return status;
}

TK_Status HTK_Area_Light::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char			option_string[32];
	int				count;
	int				option;

	HC_Show_Area_Light_Count (key, &count, option_string);
	SetPoints (count);
	HC_Show_Area_Light (key, &count, GetPoints(), option_string);

	option = 0;
	if (option_string[0] == 'b') {  // bright side=
		switch (option_string[13]) {
			case 'r':	option = 1;		break;		// fRont
			case 'a':	option = 2;		break;		// bAck
			case 'o':	option = 3;		break;		// bOth
			default:	return tk.Error();
		}
	}
	SetOptions (option);

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Area_Light);

////////////////////////////////////////

TK_Status HTK_Spot_Light::Execute (BStreamFileToolkit & tk) alter {
	TK_Status       status = TK_Normal;     // assume success
	HC_KEY          key;
	char            options[256];
	char            tmp[64];
	char            number[32];

	options[0] = '\0';

	if ((GetOptions() & TKO_Spot_Camera_Relative) != 0)
		strcat (options, "camera relative");

	if ((GetOptions() & TKO_Spot_Outer_Mask) != 0) {
		if (options[0])
			strcat (options, ",");

		write_float (number, GetOuter());

		switch (GetOptions() & TKO_Spot_Outer_Mask) {
			case TKO_Spot_Outer_Degrees:    sprintf (tmp, "illumination cone=%s degrees", number);  break;
			case TKO_Spot_Outer_Field:      sprintf (tmp, "illumination cone=%s fru",     number);  break;
			default:                        return tk.Error();
		}
		strcat (options, tmp);
	}

	if ((GetOptions() & TKO_Spot_Inner_Mask) != 0) {
		if (options[0])
			strcat (options, ",");

		write_float (number, GetInner());

		switch (GetOptions() & TKO_Spot_Inner_Mask) {
			case TKO_Spot_Inner_Degrees:    sprintf (tmp, "edge sharpness=%s degrees",    number);  break;
			case TKO_Spot_Inner_Field:      sprintf (tmp, "edge sharpness=%s fru",        number);  break;
			case TKO_Spot_Inner_Percent:    sprintf (tmp, "edge sharpness=%s%%",          number);  break;
			default:                        return tk.Error();
		}
		strcat (options, tmp);
	}

	if ((GetOptions() & TKO_Spot_Concentration) != 0) {
		if (options[0])
			strcat (options, ",");

		write_float (number, GetConcentration());

		sprintf (tmp, "concentration=%s",   number);
		strcat (options, tmp);
	}

	key = HC_KInsert_Spot_Light (GetPosition(), GetTarget(), options);
	set_last_key (tk, key);

	return status;
}

TK_Status HTK_Spot_Light::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            option_string[256];
	char const *    op = option_string;
	int             options;
	float           position[3], target[3];
	float           value;

	HC_Show_Spot_Light (key, position, target, option_string);
	SetPosition (position);
	SetTarget (target);

	options = 0;

	if (streqn (op, "camera", 3)) {
		options |= TKO_Spot_Camera_Relative;
		op += 15;   // strlen ("camera relative");
		if (*op == ',')
			++op;
	}
	if (streqn (op, "illum", 5)) {
		op += 18;   // strlen ("illumination cone=");
		value = read_float (op);
		SetOuter (value);
		while (*op != ' ') {
			if (!*op++)
				return tk.Error();
		}
		++op;
		switch (*op) {
			case 'd':   options |= TKO_Spot_Outer_Degrees;      op += 7; /* strlen ("degrees"); */  break;
			case 'f':   options |= TKO_Spot_Outer_Field;        op += 3; /* strlen ("fru");     */  break;
			default:    return tk.Error();
		}
		if (*op == ',')
			++op;
	}
	if (streqn (op, "edge", 4)) {
		op += 15;   // strlen ("edge sharpness=");
		value = read_float (op);
		SetInner (value);
		while (*op != ' ' && *op != '%') {
			if (!*op++)
				return tk.Error();
		}
		if (*op == ' ')
			++op;
		switch (*op) {
			case 'd':   options |= TKO_Spot_Inner_Degrees;      op += 7; /* strlen ("degrees"); */  break;
			case 'f':   options |= TKO_Spot_Inner_Field;        op += 3; /* strlen ("fru");     */  break;
			case '%':   options |= TKO_Spot_Inner_Percent;      ++op;                               break;
			default:    return tk.Error();
		}
		if (*op == ',')
			++op;
	}
	if (streqn (op, "conc", 4)) {
		op += 14;   // strlen ("concentration=");
		value = read_float (op);
		SetConcentration (value);
		options |= TKO_Spot_Concentration;
	}

	SetOptions (options);

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Spot_Light);

////////////////////////////////////////


TK_Status HTK_Cutting_Plane::Execute (BStreamFileToolkit & tk) alter {
	HC_KEY          key;

	key = HC_KInsert_Cutting_Section (GetCount(), GetPlanes());
	set_last_key (tk, key);

	return TK_Normal;
}

TK_Status HTK_Cutting_Plane::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	int           count;

	UNREFERENCED (tk);

	HC_Show_Cutting_Section_Count (key, &count);
	SetPlanes (count);
	HC_Show_Cutting_Section (key, &count, (void *)GetPlanes());

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Cutting_Plane);

////////////////////////////////////////////////////////////////////////////////


TK_Status HTK_Circle::Execute (BStreamFileToolkit & tk) alter {
	TK_Status       status = TK_Normal;     // assume success
	HC_KEY          key = -1;
	float const *	center;

	switch (Opcode()) {
		case TKE_Circle:
			key = HC_KInsert_Circle (GetStart(), GetMiddle(), GetEnd());
			set_last_key (tk, key);
			break;

		case TKE_Circular_Arc:
			key = HC_KInsert_Circular_Arc (GetStart(), GetMiddle(), GetEnd());
			set_last_key (tk, key);
			break;

		case TKE_Circular_Chord:
			key = HC_KInsert_Circular_Chord (GetStart(), GetMiddle(), GetEnd());
			set_last_key (tk, key);
			break;

		case TKE_Circular_Wedge:
			key = HC_KInsert_Circular_Wedge (GetStart(), GetMiddle(), GetEnd());
			set_last_key (tk, key);
			break;

		default:
			status = tk.Error();
			break;
	}

	if ((center = GetCenter()) != null)
		HC_Set_Circular_Center_By_Key (key, center[0], center[1], center[2]);

	return status;
}

TK_Status HTK_Circle::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;     // assume success
	float           start[3], middle[3], end[3], center[3];

	switch (Opcode()) {
		case TKE_Circle:
			HC_Show_Circle (key, start, middle, end);
			break;

		case TKE_Circular_Arc:
			HC_Show_Circular_Arc (key, start, middle, end);
			break;

		case TKE_Circular_Chord:
			HC_Show_Circular_Chord (key, start, middle, end);
			break;

		case TKE_Circular_Wedge:
			HC_Show_Circular_Wedge (key, start, middle, end);
			break;

		default:
			status = tk.Error();
			break;
	}

	SetPoints (start, middle, end);

	if (HC_Show_Circular_Center (key, &center[0], &center[1], &center[2]))
		SetCenter (center);

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return status;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE_OPCODE (HTK_Circle);

////////////////////////////////////////

TK_Status HTK_Ellipse::Execute (BStreamFileToolkit & tk) alter {
	TK_Status       status = TK_Normal;     // assume success
	HC_KEY          key;
	float const *   limits = GetLimits();

	switch (Opcode()) {
		case TKE_Ellipse:
			key = HC_KInsert_Ellipse (GetCenter(), GetMajor(), GetMinor());
			set_last_key (tk, key);
			break;

		case TKE_Elliptical_Arc:
			key = HC_KInsert_Elliptical_Arc (GetCenter(), GetMajor(), GetMinor(), limits[0], limits[1]);
			set_last_key (tk, key);
			break;

		default:
			status = tk.Error();
			break;
	}

	return status;
}

TK_Status HTK_Ellipse::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;     // assume success
	float           center[3], major[3], minor[3], limits[2];

	switch (Opcode()) {
		case TKE_Ellipse:
			HC_Show_Ellipse (key, center, major, minor);
			limits[0] = 0.0f;
			limits[1] = 1.0f;
			break;

		case TKE_Elliptical_Arc:
			HC_Show_Elliptical_Arc (key, center, major, minor, &limits[0], &limits[1]);
			break;

		default:
			status = tk.Error();
			break;
	}

	SetCenter (center);
	SetMajor (major);
	SetMinor (minor);
	SetLimits (limits[0], limits[1]);

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return status;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE_OPCODE (HTK_Ellipse);

////////////////////////////////////////

TK_Status HTK_Sphere::Execute (BStreamFileToolkit & tk) alter {
	TK_Status       status = TK_Normal;     // assume success
	HC_KEY          key;

	key = HC_KInsert_Sphere (GetCenter(), GetRadius(), GetAxis(), GetOrtho());
	set_last_key (tk, key);

	return status;
}

TK_Status HTK_Sphere::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;     // assume success
	float           center[3], axis[3], ortho[3], radius;

	UNREFERENCED (tk);

	HC_Show_Sphere (key, center, &radius, axis, ortho);

	SetCenter (center);
	SetRadius (radius);
	SetAxis (axis);
	SetOrtho (ortho);

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return status;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Sphere);

////////////////////////////////////////

static char const *cylinder_cappings[] = { "none", "first", "second", "both" };


TK_Status HTK_Cylinder::Execute (BStreamFileToolkit & tk) alter {
	TK_Status       status = TK_Normal;     // assume success
	HC_KEY          key;

	key = HC_KInsert_Cylinder (GetStart(), GetEnd(), GetRadius(), cylinder_cappings[GetCaps()]);
	set_last_key (tk, key);

	return status;
}

TK_Status HTK_Cylinder::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;     // assume success
	float           first[3], second[3], radius;
	char            caps[32];
	int             ii;

	UNREFERENCED (tk);

	HC_Show_Cylinder (key, first, second, &radius, caps);

	SetAxis (first, second);
	SetRadius (radius);
	SetCaps (0);    // make sure something set, though it should choose one...
	for (ii=0; ii<countof(cylinder_cappings); ++ii) {
		if (streq (caps, cylinder_cappings[ii])) {
			SetCaps (ii);
			break;
		}
	}

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return status;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Cylinder);

////

TK_Status HTK_PolyCylinder::Execute (BStreamFileToolkit & tk) alter {
	HStreamFileToolkit &    htk = *(HStreamFileToolkit *)&tk;
	TK_Status       status = TK_Normal;     // assume success
	float const *   normal;

	mp_key = HC_KInsert_PolyCylinder (GetCount(), GetPoints(),  GetRadiusCount(), GetRadii(),
									  cylinder_cappings[GetCaps()]);

	if (htk.GetHoopsVersion() >= 850) {
		if ((normal = GetEndNormal(0)) != null) {
			HC_Open_Geometry (mp_key);
			  HC_Open_Face (0);
				HC_Set_Normal (normal[0], normal[1], normal[2]);
			  HC_Close_Face();
			HC_Close_Geometry();
		}
		if ((normal = GetEndNormal(1)) != null) {
			HC_Open_Geometry (mp_key);
			  HC_Open_Face (1);
				HC_Set_Normal (normal[0], normal[1], normal[2]);
			  HC_Close_Face();
			HC_Close_Geometry();
		}
	}
	if ((status = ((HTK_Polyhedron *)this)->HExecute(tk)) != TK_Normal)
		return status;

	set_last_key (tk, mp_key);

	return status;
}

TK_Status HTK_PolyCylinder::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;     // assume success
	int             count, radius_count;
	char            caps[32];
	int             ii;

	HC_Show_PolyCylinder_Counts (key, &count, &radius_count, caps);

	// reserve space
	SetPoints (count);
	SetRadii (radius_count);

	HC_Show_PolyCylinder (key, &count, GetPoints(), &radius_count, GetRadii(), caps);

	m_flags = 0;
	SetCaps (0);    // make sure something set, though it should choose one...
	for (ii=0; ii<countof(cylinder_cappings); ++ii) {
		if (streq (caps, cylinder_cappings[ii])) {
			SetCaps (ii);
			break;
		}
	}

	HC_Open_Geometry (key);
	  HC_Open_Face (0);
		if (HC_Show_Existence ("normal")) {
			float   normal[3];

			HC_Show_Normal (&normal[0], &normal[1], &normal[2]);
			SetEndNormal (0, normal);
			m_flags |= TKCYL_NORMAL_FIRST;
		}
	  HC_Close_Face();
	  HC_Open_Face (1);
		if (HC_Show_Existence ("normal")) {
			float   normal[3];

			HC_Show_Normal (&normal[0], &normal[1], &normal[2]);
			SetEndNormal (1, normal);
			m_flags |= TKCYL_NORMAL_SECOND;
		}
	  HC_Close_Face();
	HC_Close_Geometry();

	if ((status = ((HTK_Polyhedron *)this)->HInterpret(tk, key)) != TK_NotFound) {
		if (status == TK_Error)
			return status;
		else
			m_flags |= TKCYL_OPTIONALS;
	}

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return status;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_PolyCylinder);

////////////////////////////////////////

TK_Status HTK_Grid::Execute (BStreamFileToolkit & tk) alter {
	TK_Status       status = TK_Normal;     // assume success
	HC_KEY          key;

	key = HC_KInsert_Grid ((m_type & 1) != 0 ? "radial" : "quadrilateral",
						   m_origin, m_ref1, m_ref2, m_counts[0], m_counts[1]);
	set_last_key (tk, key);

	return status;
}

TK_Status HTK_Grid::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            string[32];

	UNREFERENCED (tk);

	HC_Show_Grid (key, string, m_origin, m_ref1, m_ref2, &m_counts[0], &m_counts[1]);
	m_type = 0;
	if (string[0] == 'r')
		m_type |= 1;

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Grid);

////////////////////////////////////////

static char const * encodings[] = {
	"iso latin one",
	"iso latin",
	"jec",
	"euc",
	"16",
	"unicode",
	"unicode32",  // this should be removed
	"utf8",
	"utf16",
	"utf32",
	"wcs",
};

static char const * txtunits[] = {
	"oru", "sru", "wru", "pt", "px", "%", "wsu",
	""
};

TK_Status HTK_Text::Execute (BStreamFileToolkit & tk) alter {
	HStreamFileToolkit &    htk = *(HStreamFileToolkit *)&tk;
	HC_KEY			key;

	switch (Opcode()) {
		case TKE_Text:
			key = HC_KInsert_Text (m_position[0], m_position[1], m_position[2], m_string);
			break;

		case TKE_Text_With_Encoding:
			if (m_encoding == TKO_Enc_Unicode32) {	// trim these to Unicode16 for now
				key = HC_KInsert_Text_With_Encoding (m_position[0], m_position[1], m_position[2],
													 "utf32", (char const *)m_string);
			}
			else
				key = HC_KInsert_Text_With_Encoding (m_position[0], m_position[1], m_position[2],
													 encodings[m_encoding], m_string);
			break;

		default:
			return tk.Error();
	}

	if (htk.GetHoopsVersion() >= 950) {
		if ((m_options & TKO_Text_Option_Region) != 0) {
			char	options[64];

			options[0] = '\0';
			if ((m_region_options & TKO_Text_Region_Window) != 0)
				strcat (options, "window space,");

			if ((m_region_options & TKO_Text_Region_Relative) != 0)
				strcat (options, "relative coordinates,");

			if ((m_region_options & TKO_Text_Region_Adjusted) != 0)
				strcat (options, "adjust direction,");

			if ((m_region_options & TKO_Text_Region_Center) != 0)
				strcat (options, "alignment=center,");
			else if ((m_region_options & TKO_Text_Region_Top) != 0)
				strcat (options, "alignment=top,");

			// more complex when we handle vertical fitting
			if ((m_region_options & TKO_Text_Region_HFit) != 0) {
				unsigned char		hfit = m_region_fit & 0x0F;

				if (hfit == TKO_Text_Region_Fit_None)
					strcat (options, "fitting=none,");
				else if (hfit == TKO_Text_Region_Fit_Spacing)
					strcat (options, "fitting=spacing,");
				//else if (hfit == TKO_Text_Region_Fit_Size)
				//	strcat (options, "fitting=size,");
			}

			if (options[0])
				options[strlen(options)-1] = '\0';

			HC_Open_Geometry (key);
			HC_Set_Text_Region (m_region_count, m_region, options);
			HC_Close_Geometry();
		}
	}

	if (htk.GetHoopsVersion() >= 1250) {
		if ((m_options & TKO_Text_Option_Character_Attributes) != 0) {
			int			i;

			for (i=0; i<m_count; i++) {
				TK_Character_Attribute *	ca = &m_character_attributes[i];
				char						buffer[256], value[32];

				if ((ca->mask & TKO_Character_Name) != 0) {
					sprintf (buffer, "name=(%s)", ca->name);
					HC_MSet_Character_Attributes (key, i, 1, buffer);
				}
				if ((ca->mask & TKO_Character_Size) != 0) {
					write_float (value, ca->size);
					sprintf (buffer, "size=%s %s", value, txtunits[ca->size_units]);
					HC_MSet_Character_Attributes (key, i, 1, buffer);
				}
				if ((ca->mask & TKO_Character_Vertical_Offset) != 0) {
					write_float (value, ca->vertical_offset);
					sprintf (buffer, "vertical offset=%s %s", value, txtunits[ca->vertical_offset_units]);
					HC_MSet_Character_Attributes (key, i, 1, buffer);
				}
				if ((ca->mask & TKO_Character_Horizontal_Offset) != 0) {
					write_float (value, ca->horizontal_offset);
					sprintf (buffer, "horizontal offset=%s %s", value, txtunits[ca->horizontal_offset_units]);
					HC_MSet_Character_Attributes (key, i, 1, buffer);
				}
				if ((ca->mask & TKO_Character_Slant) != 0) {
					write_float (value, ca->slant);
					sprintf (buffer, "slant=%s", value);
					HC_MSet_Character_Attributes (key, i, 1, buffer);
				}
				if ((ca->mask & TKO_Character_Rotation) != 0) {
					write_float (value, ca->rotation);
					sprintf (buffer, "rotation=%s", value);
					if ((ca->mask & TKO_Character_Rotation_Fixed) != 0)
						strcat (buffer, " fixed");
					HC_MSet_Character_Attributes (key, i, 1, buffer);
				}
				if ((ca->mask & TKO_Character_Width_Scale) != 0) {
					write_float (value, ca->width_scale);
					sprintf (buffer, "width scale=%s", value);
					HC_MSet_Character_Attributes (key, i, 1, buffer);
				}
				if ((ca->mask & TKO_Character_Color) != 0) {
					char	v1[32], v2[32], v3[32];

					write_float (v1, ca->color[0]);
					write_float (v2, ca->color[1]);
					write_float (v3, ca->color[2]);
					sprintf (buffer, "color=R=%s G=%s B=%s", v1, v2, v3);
					HC_MSet_Character_Attributes (key, i, 1, buffer);
				}
				if ((ca->mask & TKO_Character_Omitted) != 0) {
					HC_MSet_Character_Attributes (key, i, 1, "omitted");
				}
				if ((ca->mask & TKO_Character_Invisible) != 0) {
					HC_MSet_Character_Attributes (key, i, 1, "invisible");
				}
			}
		}
	}

	set_last_key (tk, key);			 

	return TK_Normal;
}

TK_Status HTK_Text::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            enc[32];
	int             i, count;
	float			points[4*3];
	char			option_string[64];
	int				region_options = 0;
	int				region_fit = 0;

	UNREFERENCED (tk);

	HC_Show_Text_Length (key, &m_length);
	SetString (m_length);
	HC_Show_Text_With_Encoding (key, &m_position[0], &m_position[1], &m_position[2], enc, GetString());

	m_opcode = TKE_Text;
	if (!streq (enc, "iso latin one")) {
		m_opcode = TKE_Text_With_Encoding;

		for (i = 0; i < countof(encodings); ++i) {
			if (streq (enc, encodings[i])) {
				m_encoding = (unsigned char)i;
				break;
			}
		}
	}

	m_options = 0;
	m_region_options = 0;
	HC_Open_Geometry (key);
		HC_Show_Text_Region (&i, points, option_string);
		if (i != 0) {
			char const *	cp = option_string;

			while (*cp) {
				if (*cp == 'r') {
					region_options |= TKO_Text_Region_Relative;
					cp += 20;	// strlen ("relative coordinates");
				}
				else if (*cp == 'w') {
					region_options |= TKO_Text_Region_Window;
					cp += 12;	// strlen ("window space");
				}
				else if (*cp == 'a') {
					if (cp[1] == 'd') {
						region_options |= TKO_Text_Region_Adjusted;
						cp += 16;	// strlen ("adjust direction");
					}
					else if (cp[1] == 'l') {
						cp += 10;	// strlen ("alignment=");
						if (*cp == 'c') {
							region_options |= TKO_Text_Region_Center;
							cp += 6;	// strlen ("center");
						}
						else if (*cp == 't') {
							region_options |= TKO_Text_Region_Top;
							cp += 3;	// strlen ("top");
						}
						else
							return tk.Error ("unknown text region option");
					}
					else
						return tk.Error ("unknown text region option");
				}
				else if (*cp == 'f') {
					cp += 8;	// strlen ("fitting=");

					if (*cp == 'n') {
						region_options |= TKO_Text_Region_HFit | TKO_Text_Region_VFit;
						region_fit = TKO_Text_Region_Fit_None | (TKO_Text_Region_Fit_None << 4);
						cp += 4;	// strlen ("none");
					}
					else if (*cp == 's') {
						region_options |= TKO_Text_Region_HFit | TKO_Text_Region_VFit;
						if (cp[1] == 'p') {
							region_fit = TKO_Text_Region_Fit_Spacing | (TKO_Text_Region_Fit_Spacing << 4);
							cp += 7;	// strlen ("spacing");
						}
						else if (cp[1] == 'i') {
							region_fit = TKO_Text_Region_Fit_Size | (TKO_Text_Region_Fit_Size << 4);
							cp += 4;	// strlen ("size");
						}
						else
							return tk.Error ("unknown text region fit option");
					}
					// later add specific 'h' & 'v' options
					else
						return tk.Error ("unknown text region fit option");
				}
				else
					return tk.Error ("unknown text region option");

				if (*cp == ',')
					++cp;
			}

			SetTextRegion (i, points, region_options, region_fit);
		}
	HC_Close_Geometry ();

	if (m_character_attributes != null) {
		while (m_count-- > 0) {
			delete m_character_attributes[m_count].name;
		}
		delete [] m_character_attributes;
		m_character_attributes = null;
	}

	HC_Show_Character_Attribute_Count (key, &count);
	if (count > 0) {
		m_options |= TKO_Text_Option_Character_Attributes;
		HC_Show_Text_Count (key, &count);
		m_count = count;

		m_character_attributes = new TK_Character_Attribute [count];
		memset (m_character_attributes, 0, count*sizeof(TK_Character_Attribute));

		while (count-- > 0) {
			TK_Character_Attribute *	ca = &m_character_attributes[count];
			char						answer[256];

			HC_Show_One_Character_Attribute(key, count, "name", answer);
			if (answer[0] != '\0') {
				ca->mask |= TKO_Character_Name;

				ca->name = new char [strlen(answer)+1];
				strcpy (ca->name, answer);
			}

			HC_Show_One_Character_Attribute(key, count, "size", answer);
			if (answer[0] != '\0') {
				char *		ans = answer;

				ca->mask |= TKO_Character_Size;
				ca->size = read_float (ans, &ans);
				++ans; // ' '
				for (i = 0; i < (int)countof(txtunits); ++i) {
					if (streq (ans, txtunits[i])) {
						ca->size_units = (unsigned char)i;
						break;
					}
				}
			}

			HC_Show_One_Character_Attribute(key, count, "vertical offset", answer);
			if (answer[0] != '\0') {
				char *		ans = answer;

				ca->mask |= TKO_Character_Vertical_Offset;
				ca->vertical_offset = read_float (ans, &ans);
				++ans; // ' '
				for (i = 0; i < (int)countof(txtunits); ++i) {
					if (streq (ans, txtunits[i])) {
						ca->vertical_offset_units = (unsigned char)i;
						break;
					}
				}
			}

			HC_Show_One_Character_Attribute(key, count, "horizontal offset", answer);
			if (answer[0] != '\0') {
				char *		ans = answer;

				ca->mask |= TKO_Character_Horizontal_Offset;
				ca->horizontal_offset = read_float (ans, &ans);
				++ans; // ' '
				for (i = 0; i < (int)countof(txtunits); ++i) {
					if (streq (ans, txtunits[i])) {
						ca->horizontal_offset_units = (unsigned char)i;
						break;
					}
				}
			}

			HC_Show_One_Character_Attribute(key, count, "slant", answer);
			if (answer[0] != '\0') {
				ca->mask |= TKO_Character_Slant;
				if (streq (answer, "off"))
					ca->slant = 0.0f;
				else
					ca->slant = read_float (answer);
			}

			HC_Show_One_Character_Attribute(key, count, "rotation", answer);
			if (answer[0] != '\0') {
				ca->mask |= TKO_Character_Rotation;
				if (streq (answer, "off")) {
					ca->mask |= TKO_Character_Rotation_Fixed;
					ca->rotation = 0.0f;
				}
				else {
					char const *	ap = answer;

					ca->rotation = read_float (ap, &ap);
					if (streq (ap, " fixed"))
						ca->mask |= TKO_Character_Rotation_Fixed;
				}
			}

			HC_Show_One_Character_Attribute(key, count, "width scale", answer);
			if (answer[0] != '\0') {
				ca->mask |= TKO_Character_Width_Scale;
				if (streq (answer, "off"))
					ca->width_scale = 1.0f;
				else
					ca->width_scale = read_float (answer);
			}

			HC_Show_One_Character_Attribute(key, count, "color", answer);
			if (answer[0] != '\0') {
				char *		ans = answer;

				ca->mask |= TKO_Character_Color;
				ans += 2;	// "R="
				ca->color[0] = read_float (ans, &ans);
				ans += 3;	// " G="
				ca->color[1] = read_float (ans, &ans);
				ans += 3;	// " B="
				ca->color[2] = read_float (ans, &ans);
			}

			HC_Show_One_Character_Attribute(key, count, "invisible", answer);
			if (streq (answer, "on"))
				ca->mask |= TKO_Character_Invisible;

			HC_Show_One_Character_Attribute(key, count, "omitted", answer);
			if (streq (answer, "on"))
				ca->mask |= TKO_Character_Omitted;
		}
	}

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE_OPCODE (HTK_Text);

////////////////////////////////////////

static char const * formats[] = {
	"mapped 8", "mapped 16", "rgb", "rgba", "bgra", "depth",
	"grayscale", "jpeg", "dxt1", "dxt3", "dxt5", "tga", "png"
};

TK_Status HTK_Image::Execute (BStreamFileToolkit & tk) alter {
	HStreamFileToolkit &    htk = *(HStreamFileToolkit *)&tk;
	HC_KEY          key;
	char            fmt[4096];
	char            variable[512];

	strcpy (fmt, formats[(int)m_format]);

	if (m_name_length > 0) {
		strcat (fmt, ",name=");
		strcat (fmt, m_name);
	}
	if (htk.GetHoopsVersion() >= 1050) {
		if ((m_options & TKO_Image_Explicit_Size) != 0) {

			write_float (variable, m_explicit_size[0]);
			strcat (fmt, ",size=(");
			strcat (fmt, variable);
			strcat (fmt, " ");
			strcat (fmt, generic_units_table[m_explicit_units[0]]);

			write_float (variable, m_explicit_size[1]);
			strcat (fmt, ",");
			strcat (fmt, variable);
			strcat (fmt, " ");
			strcat (fmt, generic_units_table[m_explicit_units[1]]);
			strcat (fmt, ")");
		}
		if ((m_options & TKO_Image_Local_Texture) != 0) {
			strcat (fmt, ",local");
		}
	}
	if (htk.GetHoopsVersion() >= 1850) {
		if (m_options & TKO_Image_Compression_Quality) {
			strcat (fmt, ",compression quality=");
			write_float (variable, m_compression_quality);
			strcat (fmt, variable);
		}
		if (m_options & TKO_Image_Discard) {
			strcat (fmt, ",discard");
		}
	}

	if (m_format == TKO_Image_PNG ||
		m_format == TKO_Image_JPEG ||
		m_format == TKO_Image_DXT1 ||
		m_format == TKO_Image_DXT3 ||
		m_format == TKO_Image_DXT5 ||
		m_format == TKO_Image_TARGA) {
		key = HC_KInsert_Compressed_Image (m_position[0], m_position[1], m_position[2],
								fmt, m_size[0], m_size[1], m_data_size, m_bytes);
	}
	else {
		key = HC_KInsert_Image (m_position[0], m_position[1], m_position[2],
								fmt, m_size[0], m_size[1], m_bytes);
	}
	set_last_key (tk, key);			 

	return TK_Normal;
}

TK_Status HTK_Image::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            fmt[4096];
	char *          cp;
	int             i;

	m_compression = TKO_Compression_None;

	m_explicit_size[0] = -1;
	m_explicit_size[1] = -1;
	m_explicit_units[0] = m_explicit_units[1] = TKO_Generic_Size_Pixels;

	HC_Show_Image_Format (key, fmt);
	if ((cp = strchr (fmt, ',')) != null)
		*cp++ = '\0';

	ASSERT (streq(formats[TKO_Image_TARGA], "tga"));
	for (i = 0; i < countof(formats); ++i) {
		if (streq (fmt, formats[i])) {
			m_format = (unsigned char)i;
			break;
		}
	}
	if (i == countof(formats))
		return tk.Error("unrecognized image format in HTK_Image::Interpret");

	if (m_format == TKO_Image_PNG ||
		m_format == TKO_Image_JPEG ||
		m_format == TKO_Image_TARGA ||
		m_format == TKO_Image_DXT1 ||
		m_format == TKO_Image_DXT3 ||
		m_format == TKO_Image_DXT5 ||
		m_format == TKO_Image_TARGA) 
	{
		HC_Show_Compressed_Image_Size (key, null, &m_size[0], &m_size[1], &m_data_size);

		// allocate space
		SetBytes (m_data_size);
		if (!GetBytes())
			return tk.Error("Failed to allocate memory in TK_Image::Interpret");


		m_explicit_size[0] = (float)m_size[0];
		m_explicit_size[1] = (float)m_size[1];
		m_explicit_units[0] = m_explicit_units[1] = TKO_Generic_Size_Pixels;

		HC_Show_Compressed_Image (key, &m_position[0], &m_position[1], &m_position[2],
					   fmt, &m_size[0], &m_size[1], &m_data_size, GetBytes());

	}
	else {
		HC_Show_Image_Size (key, null, null, null, null, &m_size[0], &m_size[1]);

		// allocate space
		SetBytes (m_size[0] * m_size[1] * TK_Image_Bytes_Per_Pixel[(int)m_format]);
		if (!GetBytes())
			return tk.Error("Failed to allocate memory in TK_Image::Interpret");


		m_explicit_size[0] = (float)m_size[0];
		m_explicit_size[1] = (float)m_size[1];
		m_explicit_units[0] = m_explicit_units[1] = TKO_Generic_Size_Pixels;

		HC_Show_Image (key, &m_position[0], &m_position[1], &m_position[2],
					   fmt, &m_size[0], &m_size[1], GetBytes());
	}

	while (cp != null) {
		char *		start = cp;

		if ((cp = strchr (start, ',')) != null)
			*cp++ = '\0';
		
		switch (*start) {
			case 'c': {
				start += 20;   // strlen ("compression quality=");
				m_compression_quality = read_float (start, &start);
				m_options |= TKO_Image_Compression_Quality;
			}   break;

			case 'd': {		   
				start += 6;   // strlen ("discard");
				m_options |= TKO_Image_Discard;
			}   break;

			case 'n': {
				start += 5;    // strlen ("name=");
				SetName (start);
			}   break;

			case 's': {
				int             ii;

				start += 5;    // strlen ("size=");

				if (*start != '(') {
					m_explicit_size[0] = m_explicit_size[1] = read_float (start, &start);
					while (*start == ' ') ++start;
					if ((cp = strchr (start, ',')) != null)
						*cp++ = '\0';
					for (ii=0; ii<countof(generic_units_table); ++ii) {
						if (streq (start, generic_units_table[ii])) {
							m_explicit_units[0] = m_explicit_units[1] = (unsigned char)ii;
							break;
						}
					}
					if (m_explicit_units[0] == TKO_Generic_Size_Unspecified)
						return tk.Error("can't parse size units");
				}
				else {
					start++;    // '('
					m_explicit_size[0] = read_float (start, &start);
					while (*start == ' ') ++start;
					if ((cp = strchr (start, ',')) == null)
						return tk.Error("can't parse size units");
					*cp++ = '\0';	// overwrite ','
					for (ii=0; ii<countof(generic_units_table); ++ii) {
						if (streq (start, generic_units_table[ii])) {
							m_explicit_units[0] = (unsigned char)ii;
							break;
						}
					}
					if (m_explicit_units[0] == TKO_Generic_Size_Unspecified)
						return tk.Error("can't parse size units");

					start = cp;
					m_explicit_size[1] = read_float (start, &start);
					while (*start == ' ') ++start;
					if ((cp = strchr (start, ')')) == null)
						return tk.Error("can't parse size units");
					*cp++ = '\0';	// overwrite ')'
					for (ii=0; ii<countof(generic_units_table); ++ii) {
						if (streq (start, generic_units_table[ii])) {
							m_explicit_units[1] = (unsigned char)ii;
							break;
						}
					}
					if (m_explicit_units[0] == TKO_Generic_Size_Unspecified)
						return tk.Error("can't parse size units");
					start = cp;
				}

				m_options |= TKO_Image_Explicit_Size;
			}   break;

			default: {
				return tk.Error ("unrecognized image option");
			}   nobreak;
		}
	}

	if (m_name_length > 0) {	// see if it's tied to a local texture
		char	    texture[4096];

		HC_Begin_Local_Texture_Search ();
			while (HC_Find_Texture (texture)) {
				if (streq (m_name, texture)) {
					m_options |= TKO_Image_Local_Texture;
					break;
				}
			}
		HC_End_Texture_Search ();
	}

	if (m_format == TKO_Image_PNG)
		m_compression = TKO_Compression_PNG;
	else if (m_format == TKO_Image_JPEG)
		m_compression = TKO_Compression_JPEG;
	else if (m_format == TKO_Image_TARGA)
		m_compression = TKO_Compression_TARGA;
	else if ((m_format == TKO_Image_DXT1) || (m_format == TKO_Image_DXT3) || (m_format == TKO_Image_DXT5))
		m_compression = TKO_Compression_DXT;
    else if ((m_format == TKO_Image_RGB || m_format == TKO_Image_RGBA || m_format == TKO_Image_BGRA) &&
		m_size[0] > 64 && m_size[1] > 64 &&
		tk.GetJpegQuality() > 0)
		m_compression = TKO_Compression_JPEG;
	else if (m_format == TKO_Image_Mapped)
		m_compression = TKO_Compression_RLE;

	if (HC_Show_Existence_By_Key (key, "referrers"))
		SetNeedsTag (true);

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Image);

////////////////////////////////////////////////////////////////////////////////
// pseudo-object used to hold several color pieces, output only

HTK_Color_Composite::HTK_Color_Composite ()
	: BBaseOpcodeHandler (TKE_Pseudo_Handler) {
	int			i;

	for (i = 0; i < 16; ++i)
		m_parts[i] = null;
}

HTK_Color_Composite::~HTK_Color_Composite () {
	int			i;

	for (i = 0; i < 16; ++i)
		delete m_parts[i];
}

TK_Status HTK_Color_Composite::Write (BStreamFileToolkit & tk) alter {
#ifndef HSTREAM_READONLY
	TK_Status		status = TK_Normal;

	while (m_parts[m_stage] != null) {
		if ((status = m_parts[m_stage]->Write (tk)) != TK_Normal)
			return status;
		adjust_written (tk, -1);    // don't count the subpiece
		++m_stage;
	}
	adjust_written (tk, 1);         // now count the whole set of colors
	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}


TK_Status HTK_Color_Composite::Read (BStreamFileToolkit & tk) alter {
	return tk.Error();
}
TK_Status HTK_Color_Composite::Execute (BStreamFileToolkit & tk) alter {
	return tk.Error();
}

// HTK_Color_Composite::Interpret() currently in parse.cpp

IMPLEMENT_CLONE (HTK_Color_Composite);

////////////////////////////////////////

															   

#define append(t, d) do {	\
	char const *c = d;		\
	while (*c) *t++ = *c++;	\
} while(0)

static char * make_type_string (int mask, char * buffer) {

	char		*tmp=buffer;
	
	if ((mask & TKO_Geo_Geom_Colors) == TKO_Geo_Geom_Colors) {
		append(tmp, "geometry=");
		mask &= ~TKO_Geo_Geom_Colors;
	}

	if ((mask & TKO_Geo_Face) == TKO_Geo_Face) {
		append(tmp, "face=");
		mask &= ~TKO_Geo_Face;
	}
	else
	if ((mask & TKO_Geo_Front) == TKO_Geo_Front) {
		append(tmp, "front=");
		mask &= ~TKO_Geo_Front;
	}
	else
	if ((mask & TKO_Geo_Back) == TKO_Geo_Back) {
		append(tmp, "back=");
		mask &= ~TKO_Geo_Back;
	}

	if ((mask & TKO_Geo_Edge) == TKO_Geo_Edge) {
		append(tmp, "edges=");
		mask &= ~TKO_Geo_Edge;
	}
	
	if ((mask & TKO_Geo_Line) == TKO_Geo_Line) {
		append(tmp, "lines=");
		mask &= ~TKO_Geo_Line;
	}

	if ((mask & (TKO_Geo_Marker|TKO_Geo_Vertex)) == (TKO_Geo_Marker|TKO_Geo_Vertex)) {
		append(tmp, "markers=");
		mask &= ~(TKO_Geo_Marker|TKO_Geo_Vertex);
	}
	else
	if ((mask & TKO_Geo_Marker) == TKO_Geo_Marker) {
		append(tmp, "markers only=");
		mask &= ~TKO_Geo_Marker;
	}
	else
	if ((mask & TKO_Geo_Vertex) == TKO_Geo_Vertex) {
		append(tmp, "vertices=");
		mask &= ~TKO_Geo_Vertex;
	}

	if ((mask & TKO_Geo_Text) == TKO_Geo_Text) {
		append(tmp, "text=");
		mask &= ~TKO_Geo_Text;
	}

	if ((mask & TKO_Geo_Light) == TKO_Geo_Light) {
		append(tmp, "lighting=");
		mask &= ~TKO_Geo_Light;
	}

	if ((mask & TKO_Geo_Window) == TKO_Geo_Window) {
		append(tmp, "windows=");
		mask &= ~TKO_Geo_Window;
	}

	if ((mask & TKO_Geo_Ambient) == TKO_Geo_Ambient) {
		append(tmp, "ambient=");
		mask &= ~TKO_Geo_Ambient;
	}
	else
	if ((mask & TKO_Geo_Ambient_Up) == TKO_Geo_Ambient_Up) {
		append(tmp, "ambient up=");
		mask &= ~TKO_Geo_Ambient_Up;
	}
	else
	if ((mask & TKO_Geo_Ambient_Down) == TKO_Geo_Ambient_Down) {
		append(tmp, "ambient down=");
		mask &= ~TKO_Geo_Ambient_Down;
	}

	if ((mask & TKO_Geo_Face_Contrast) == TKO_Geo_Face_Contrast) {
		append(tmp, "face contrast=");
		mask &= ~TKO_Geo_Face_Contrast;
	}

	if ((mask & TKO_Geo_Window_Contrast) == TKO_Geo_Window_Contrast) {
		append(tmp, "window contrast=");
		mask &= ~TKO_Geo_Window_Contrast;
	}

	if ((mask & TKO_Geo_Simple_Reflection) == TKO_Geo_Simple_Reflection) {
		append(tmp, "simple reflection=");
		mask &= ~TKO_Geo_Simple_Reflection;
	}

	if ((mask & TKO_Geo_Cut_Edge) == TKO_Geo_Cut_Edge) {
		append(tmp, "cut edge=");
		mask &= ~TKO_Geo_Cut_Edge;
	}

	if ((mask & TKO_Geo_Cut_Face) == TKO_Geo_Cut_Face) {
		append(tmp, "cut face=");
		mask &= ~TKO_Geo_Cut_Face;
	}

	if ((mask & TKO_Geo_Edge_Contrast) == TKO_Geo_Edge_Contrast) {
		append(tmp, "edge contrast=");
		mask &= ~TKO_Geo_Edge_Contrast;
	}

	if ((mask & TKO_Geo_Line_Contrast) == TKO_Geo_Line_Contrast) {
		append(tmp, "line contrast=");
		mask &= ~TKO_Geo_Line_Contrast;
	}

	if ((mask & TKO_Geo_Marker_Contrast) == TKO_Geo_Marker_Contrast) {
		append(tmp, "marker contrast=");
		mask &= ~TKO_Geo_Marker_Contrast;
	}

	if ((mask & TKO_Geo_Vertex_Contrast) == TKO_Geo_Vertex_Contrast) {
		append(tmp, "vertex contrast=");
		mask &= ~TKO_Geo_Vertex_Contrast;
	}
	
	if ((mask & TKO_Geo_Text_Contrast) == TKO_Geo_Text_Contrast) {
		append(tmp, "text contrast=");
		mask &= ~TKO_Geo_Text_Contrast;
	}

	return tmp;
}

#define DO_CHANNEL(cbit,cname,data)									\
	if ((m_channels & (1 << cbit)) != 0) {								\
		if (data.m_name && data.m_name[0]) {							\
			if (cname && cname[0]) {									\
				append (tmp, cname);									\
				append (tmp, "=");										\
			}															\
			append(tmp, data.m_name);									\
			append(tmp, ",");											\
		}																\
		else {															\
			if (0) {												\
				char    rr[32], gg[32], bb[32];						\
				if (cname && cname[0]) {							\
					strcat (tmp, cname);							\
					strcat (tmp, "=");								\
				}													\
				write_float (rr, data.m_rgb[0]);					\
				write_float (gg, data.m_rgb[1]);					\
				write_float (bb, data.m_rgb[2]);					\
				sprintf (buffer, "R=%s G=%s B=%s,", rr, gg, bb);	\
				append (tmp, buffer);								\
			}														\
			else if (cname && cname[0])										\
				HC_Set_Explicit_Color(name, cname, data.m_rgb, 0, 0);		\
			else															\
				HC_Set_Explicit_Color(name, "diffuse", data.m_rgb, 0, 0);	\
		}																	\
	}	

TK_Status HTK_Color::Execute (BStreamFileToolkit & tk) alter {
	TK_Status               status = TK_Normal;     // assume success

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	char					buffer[4096];
	char					*tmp;

	tmp = make_type_string(m_mask, buffer);

	if (tmp != buffer && tmp[-1] == '=') {
		*--tmp = '\0';

		char name[4096];

		strcpy(name, buffer);

		append(tmp, "=(");                                           
		DO_CHANNEL (TKO_Channel_Diffuse,		"",				m_diffuse);			// empty string on purpose  
		DO_CHANNEL (TKO_Channel_Specular,		"specular",		m_specular);        
		DO_CHANNEL (TKO_Channel_Mirror,			"mirror",		m_mirror);          
		DO_CHANNEL (TKO_Channel_Transmission,	"transmission",	m_transmission);    
		DO_CHANNEL (TKO_Channel_Emission,		"emission",		m_emission);   
		DO_CHANNEL (TKO_Channel_Environment,	"environment",	m_environment);     
		DO_CHANNEL (TKO_Channel_Bump,			"bump",			m_bump);       
		if ((m_channels & (1 << TKO_Channel_Gloss)) != 0) {                         
			char    ff[32];                                                         
			write_float (ff, m_gloss);
			append(tmp, "gloss=");
			append(tmp, ff);
			append(tmp, ",");                                                
		}                                                                           
		if ((m_channels & (1 << TKO_Channel_Index)) != 0) {                         
			char    ff[32];                                                         
			write_float (ff, m_index);                                              
			append(tmp, "index=");
			append(tmp, ff);
			append(tmp, ","); 
		}                                                                           

		if (tmp[-1] == ',') {
			tmp[-1] = ')';
			*tmp = '\0';
			HC_Set_Color (buffer);
		}
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return status;
}

TK_Status HTK_Color::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
	return tk.Error();    // contents generated as part of HTK_Color_Composite::Interpret()
}

IMPLEMENT_CLONE (HTK_Color);

////////////////////////////////////////

                                                          //

TK_Status HTK_Color_RGB::Execute (BStreamFileToolkit & tk) alter {
	TK_Status               status = TK_Normal;     // assume success

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	char					buffer[4096];
	char					*tmp;

	tmp = make_type_string(m_mask, buffer);

	if (tmp[-1] == '=') {
		tmp[-1] = '\0';
		HC_Set_Color_By_Value (buffer, "RGB", m_rgb[0], m_rgb[1], m_rgb[2]);
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return status;
}

TK_Status HTK_Color_RGB::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
	return tk.Error();    // contents generated as part of HTK_Color_Composite::Interpret()
}

IMPLEMENT_CLONE (HTK_Color_RGB);

////////////////////////////////////////

static char const * color_spaces[] = {"rgb", "hls", "hic", "hsv"};

                                                 
TK_Status HTK_Color_By_Value::Execute (BStreamFileToolkit & tk) alter {
	TK_Status               status = TK_Normal;     // assume success

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}
	
	char					buffer[4096];
	char					*tmp;

	tmp = make_type_string(m_mask, buffer);

	if (tmp[-1] == '=') {
		tmp[-1] = '\0';
		HC_Set_Color_By_Value (buffer, color_spaces[(int)m_space],    
							   m_value[0], m_value[1], m_value[2]);
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return status;
}

TK_Status HTK_Color_By_Value::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
	return tk.Error();    // contents generated as part of HTK_Color_Composite::Interpret()
}

IMPLEMENT_CLONE (HTK_Color_By_Value);

////////////////////////////////////////

           

TK_Status HTK_Color_By_Index::Execute (BStreamFileToolkit & tk) alter {
	TK_Status               status = TK_Normal;     // assume success

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	char					buffer[4096];
	char					*tmp;

	tmp = make_type_string(m_mask, buffer);

	if (tmp[-1] == '=') {
		tmp[-1] = '\0';
		HC_Set_Color_By_Index (buffer, m_index);
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return status;
}

TK_Status HTK_Color_By_Index::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
	return tk.Error();    // contents generated as part of HTK_Color_Composite::Interpret()
}

IMPLEMENT_CLONE_OPCODE (HTK_Color_By_Index);

////////////////////////////////////////



TK_Status HTK_Color_By_FIndex::Execute (BStreamFileToolkit & tk) alter {
	TK_Status               status = TK_Normal;     // assume success

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	char					buffer[4096];
	char					*tmp;

	tmp = make_type_string(m_mask, buffer);

	if (tmp[-1] == '=') {
		tmp[-1] = '\0';
		HC_Set_Color_By_FIndex (buffer, m_index);
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return status;
}

TK_Status HTK_Color_By_FIndex::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
	return tk.Error();    // contents generated as part of HTK_Color_Composite::Interpret()
}

IMPLEMENT_CLONE (HTK_Color_By_FIndex);

////////////////////////////////////////


TK_Status HTK_Color_Map::Execute (BStreamFileToolkit & tk) alter {
	switch (m_format) {
		case TKO_Map_RGB_Values: {
			HC_Set_Color_Map_By_Value ("rgb", m_length, m_values);
		}   break;

		case TKO_Map_String: {
			HC_Set_Color_Map (m_string);
		}   break;

		default:
			return tk.Error();
	};

	return TK_Normal;
}

TK_Status HTK_Color_Map::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            sysop[2048];
	char            style[32];
	int				length;

	HC_Show_Color_Map_Count (&m_length);
	SetValues (m_length);

	HC_Show_One_System_Option ("errors", sysop);
	HC_Define_System_Options ("no errors");

	HC_Show_Color_Map_By_Value (style, &length, GetValues());
	{
		char		newsysop[2048];

		sprintf (newsysop, "errors=(%s)", sysop);
		HC_Define_System_Options (newsysop);
	}

	if (length == m_length) {
		// everything is just diffuse or placeholders, but we can't encode the placeholders
		int		i;
		for (i=0; i<3*length; ++i)
			if (m_values[i] < 0.0f)
				length = 0;		// flag incompatibility and break loop
	}

	if (length != m_length) {
		if (tk.GetTargetVersion() < 1345) {
			// can't make a proper map, just make sure it's not filled with garbage
			memset (&m_values[3*length], 0, (m_length-length)*3*sizeof(float));
		}
		else {
			char            sysop[64];
			char            value[64];


			HC_Show_One_System_Option ("C string length", value);
			if (streq (value, "off"))
				strcpy (sysop, "no C string length");
			else
				sprintf (sysop, "C string Length=%s", value);
			HC_Define_System_Options ("C string Length=16777216");  // big enough?

			m_format = TKO_Map_String;

			HC_Show_Color_Map_Length (&length);
			SetString (length);

			HC_Show_Color_Map (GetString());

			HC_Define_System_Options (sysop);	// restore (here -- override affects unicode handling too!)
		}
	}

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Color_Map);

////////////////////////////////////////////////////////////////////////////////


TK_Status HTK_Callback::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;
		TK_Status				status;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	HC_Set_Callback (GetCallback());

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return TK_Normal;
}

TK_Status HTK_Callback::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            string[4096];

	UNREFERENCED (tk);

	HC_Show_Callback (string);
	SetCallback (string);

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Callback);

////////////////////////////////////////////////////////////////////////////////

#define RENDO_NORMAL(bit,name)							\
	do if ((m_mask[0] & bit) != 0) {					\
		if ((m_value[0] & bit) != 0)					\
			HC_Set_Rendering_Options (name "=on");		\
		else											\
			HC_Set_Rendering_Options (name "=off");		\
	} while (0)										   //

#define RENDO_EXTENDED(bit,name)						\
	do if ((m_mask[1] & bit) != 0) {					\
		if ((m_value[1] & bit) != 0)					\
			HC_Set_Rendering_Options (name "=on");		\
		else											\
			HC_Set_Rendering_Options (name "=off");		\
	} while (0)										   //

#define RENDO_EXTENDED_2(bit,name)						\
	do if ((m_mask[2] & bit) != 0) {					\
		if ((m_value[2] & bit) != 0)					\
			HC_Set_Rendering_Options (name "=on");		\
		else											\
			HC_Set_Rendering_Options (name "=off");		\
	} while (0)										   //

#define RENDO_LIGHTING(gbit, pbit, goochbit, name)			\
	do {													\
		if ((m_mask[1] & goochbit)!=0)						\
			HC_Set_Rendering_Options(name "=gooch");		\
		else if ((m_mask[0] & (gbit|pbit)) != 0) {			\
			if ((m_value[0] & gbit) != 0)					\
				HC_Set_Rendering_Options (name "=gouraud");	\
			else if ((m_value[0] & pbit) != 0)				\
				HC_Set_Rendering_Options (name "=phong");	\
			else											\
				HC_Set_Rendering_Options (name "=off");		\
		}													\
	} while (0)											   //

#define RENDO_VALUE(bit,name,val,fmt)				\
	do if ((m_mask[0] & bit) != 0) {				\
		if ((m_value[0] & bit) != 0) {				\
			char        buff[256];			\
			sprintf (buff, name "=" fmt, val);		\
			HC_Set_Rendering_Options (buff);		\
		}											\
		else										\
			HC_Set_Rendering_Options ("no " name);	\
	} while (0)									   //


#define RENDO_LOCK(bit,name)											\
	do if ((m_lock_mask & bit) != 0) {									\
		if ((m_lock_value & bit) != 0)									\
			HC_Set_Rendering_Options ("attribute lock=" name "=on");	\
		else															\
			HC_Set_Rendering_Options ("attribute lock=" name "=off");	\
	} while (0)														   //

#define RENDO_COLOR_SIMPLE_LOCK(bit,name)									\
	do if ((m_lock_color_mask & bit) != 0) {								\
		if ((m_lock_color_value & bit) != 0)								\
			HC_Set_Rendering_Options ("attribute lock=color=" name "=on");	\
		else																\
			HC_Set_Rendering_Options ("attribute lock=color=" name "=off");	\
	} while (0)															   //

#define RENDO_CHANNEL_LOCK(field,bit,name,chan)										\
	do if ((m_lock_color_##field##_mask & bit) != 0) {								\
		if ((m_lock_color_##field##_value & bit) != 0)								\
			HC_Set_Rendering_Options ("attribute lock=color=" name "=" chan "=on");	\
		else																		\
			HC_Set_Rendering_Options ("attribute lock=color=" name "=" chan "=off");\
	} while (0)																	   //

#define RENDO_COLOR_LOCK(bit,field,name)													\
	do if ((m_lock_color_mask & bit) != 0) {												\
	if ((m_lock_color_value & bit) != 0) {													\
		RENDO_CHANNEL_LOCK (field, TKO_Lock_Channel_Diffuse,		name, "diffuse");		\
		RENDO_CHANNEL_LOCK (field, TKO_Lock_Channel_Specular,		name, "specular");		\
		RENDO_CHANNEL_LOCK (field, TKO_Lock_Channel_Mirror,			name, "mirror");		\
		RENDO_CHANNEL_LOCK (field, TKO_Lock_Channel_Transmission,	name, "transmission");	\
		RENDO_CHANNEL_LOCK (field, TKO_Lock_Channel_Emission,		name, "emission");		\
		RENDO_CHANNEL_LOCK (field, TKO_Lock_Channel_Gloss,			name, "gloss");			\
		RENDO_CHANNEL_LOCK (field, TKO_Lock_Channel_Index,			name, "index");			\
		RENDO_CHANNEL_LOCK (field, TKO_Lock_Channel_Environment,	name, "environment");	\
		RENDO_CHANNEL_LOCK (field, TKO_Lock_Channel_Bump,			name, "bump");			\
		} else																				\
			HC_Set_Rendering_Options ("attribute lock=color=" name "=off");					\
	} while (0)																			   //

#define RENDO_VIS_LOCK(bit,name)													\
	do if ((m_lock_visibility_mask & bit) != 0) {									\
		if ((m_lock_visibility_value & bit) != 0)									\
			HC_Set_Rendering_Options ("attribute lock=visibility=" name "=on");		\
		else																		\
			HC_Set_Rendering_Options ("attribute lock=visibility=" name "=off");	\
	} while (0)																	   //


#define RENDO_FORCED(bit,name)										\
	do if ((m_forced_mask & bit) != 0) {							\
		if ((m_forced_value & bit) != 0)							\
			HC_Set_Rendering_Options ("ignore lock=" name "=on");	\
		else														\
			HC_Set_Rendering_Options ("ignore lock=" name "=off");	\
	} while (0)													   //

#define RENDO_COLOR_SIMPLE_FORCED(bit,name)									\
	do if ((m_forced_color_mask & bit) != 0) {								\
		if ((m_forced_color_value & bit) != 0)								\
			HC_Set_Rendering_Options ("ignore lock=color=" name "=on");		\
		else																\
			HC_Set_Rendering_Options ("ignore lock=color=" name "=off");	\
	} while (0)															   //

#define RENDO_CHANNEL_FORCED(field,bit,name,chan)									\
	do if ((m_forced_color_##field##_mask & bit) != 0) {							\
		if ((m_forced_color_##field##_value & bit) != 0)							\
			HC_Set_Rendering_Options ("ignore lock=color=" name "=" chan "=on");	\
		else																		\
			HC_Set_Rendering_Options ("ignore lock=color=" name "=" chan "=off");	\
	} while (0)																	   //

#define RENDO_COLOR_FORCED(bit,field,name)													\
	do if ((m_forced_color_mask & bit) != 0) {												\
	if ((m_forced_color_value & bit) != 0) {												\
		RENDO_CHANNEL_FORCED (field, TKO_Lock_Channel_Diffuse,		name, "diffuse");		\
		RENDO_CHANNEL_FORCED (field, TKO_Lock_Channel_Specular,		name, "specular");		\
		RENDO_CHANNEL_FORCED (field, TKO_Lock_Channel_Mirror,		name, "mirror");		\
		RENDO_CHANNEL_FORCED (field, TKO_Lock_Channel_Transmission,	name, "transmission");	\
		RENDO_CHANNEL_FORCED (field, TKO_Lock_Channel_Emission,		name, "emission");		\
		RENDO_CHANNEL_FORCED (field, TKO_Lock_Channel_Gloss,		name, "gloss");			\
		RENDO_CHANNEL_FORCED (field, TKO_Lock_Channel_Index,		name, "index");			\
		RENDO_CHANNEL_FORCED (field, TKO_Lock_Channel_Environment,	name, "environment");	\
		RENDO_CHANNEL_FORCED (field, TKO_Lock_Channel_Bump,			name, "bump");			\
		} else																				\
			HC_Set_Rendering_Options ("ignore lock=color=" name "=off");					\
	} while (0)																			   //

#define RENDO_VIS_FORCED(bit,name)												\
	do if ((m_forced_visibility_mask & bit) != 0) {								\
		if ((m_forced_visibility_value & bit) != 0)								\
			HC_Set_Rendering_Options ("ignore lock=visibility=" name "=on");	\
		else																	\
			HC_Set_Rendering_Options ("ignore lock=visibility=" name "=off");	\
	} while (0)																   //


#define RENDO_REFLECTION_VIS(bit,name)												\
	do if ((m_simple_reflection_visibility_mask & bit) != 0) {						\
		if ((m_simple_reflection_visibility_value & bit) != 0)						\
			HC_Set_Rendering_Options ("simple reflection=visibility=" name "=on");	\
		else																		\
			HC_Set_Rendering_Options ("simple reflection=visibility=" name "=off");	\
	} while (0)																	   //

#if 0
static char const * line_patterns[] = {
	"---", "-.-", "- -", "...", "-..", "-...", "-- --", "center", "phantom", "...fine"
};
#endif

TK_Status HTK_Rendering_Options::Execute (BStreamFileToolkit & tk) alter {
	HStreamFileToolkit &    htk = *(HStreamFileToolkit *)&tk;
	TK_Status               status = TK_Normal;     // assume success

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	RENDO_NORMAL (TKO_Interp_Texture_Faces,    "texture interpolation=faces");
	RENDO_NORMAL (TKO_Interp_Texture_Edges,    "texture interpolation=edges");
	RENDO_NORMAL (TKO_Interp_Texture_Markers,  "texture interpolation=markers");

	RENDO_NORMAL (TKO_Interp_Color_Faces,      "color interpolation=faces");
	RENDO_NORMAL (TKO_Interp_Color_Edges,      "color interpolation=edges");
	RENDO_NORMAL (TKO_Interp_Color_Markers,    "color interpolation=markers");

	RENDO_NORMAL (TKO_Interp_Index_Faces,      "color index interpolation=faces");
	RENDO_NORMAL (TKO_Interp_Index_Edges,      "color index interpolation=edges");
	RENDO_EXTENDED (TKO_Interp_Index_Markers,  "color index interpolation=markers");
	if ((m_mask[1] & TKO_Interp_Index_Face_Isolines) != 0)
		HC_Set_Rendering_Options ("color index interpolation=isolines");

	RENDO_LIGHTING (TKO_Interp_Lighting_Faces_Gouraud, TKO_Interp_Lighting_Faces_Phong, 
		TKO_Interp_Lighting_Faces_Gooch, "lighting=faces");
	RENDO_LIGHTING (TKO_Interp_Lighting_Edges_Gouraud, TKO_Interp_Lighting_Edges_Phong, 
		TKO_Interp_Lighting_Edges_Gooch, "lighting=edges");

	if ((m_mask[0] & TKO_Rendo_HSR_Algorithm) != 0) {
		switch (m_hsr & TKO_HSR_Mask) {
			case TKO_HSR_Hardware:      HC_Set_Rendering_Options ("hsr algorithm=hardware z buffer");   break;
			case TKO_HSR_SZB:           HC_Set_Rendering_Options ("hsr algorithm=software z buffer");   break;
			case TKO_HSR_Painters:      HC_Set_Rendering_Options ("hsr algorithm=painters");            break;
			case TKO_HSR_Z_Sort_Only:   HC_Set_Rendering_Options ("hsr algorithm=z-sort only");         break;
			case TKO_HSR_Priority:      HC_Set_Rendering_Options ("hsr algorithm=priority");            break;
			case TKO_HSR_Spider_Web:    HC_Set_Rendering_Options ("hsr algorithm=spider web");          break;
			case TKO_HSR_Hidden_Line:   HC_Set_Rendering_Options ("hsr algorithm=hidden line");         break;
			case TKO_HSR_Fast_Hidden_Line:
									if (htk.GetHoopsVersion() >= 850)
										HC_Set_Rendering_Options ("hsr algorithm=fast hidden line");
									else
										HC_Set_Rendering_Options ("hsr algorithm=hidden line"); // oh well
																										break;
		}
	}
	if ((m_mask[0] & TKO_Rendo_THSR_Algorithm) != 0) {
		switch ((m_hsr & TKO_THSR_Mask) >> 4) {
			case TKO_HSR_Painters:      HC_Set_Rendering_Options ("transparency=hsr algorithm=painters");    break;
			case TKO_HSR_Z_Sort_Only:   HC_Set_Rendering_Options ("transparency=hsr algorithm=z-sort only"); break;
			case TKO_HSR_Depth_Peeling: HC_Set_Rendering_Options ("transparency=hsr algorithm=depth peeling"); break;
			case TKO_HSR_None:          if (htk.GetHoopsVersion() >= 750)
											HC_Set_Rendering_Options ("transparency=hsr algorithm=none");      break;
		}
	}

	if ((m_mask[0] & TKO_Rendo_Technology) != 0) {
		char                buffer[256];

		strcpy (buffer, "technology=(");
		if ((m_tq & TKO_Technology_Standard) != 0)
			strcat (buffer, "standard");
		if ((m_tq & TKO_Technology_Soft_Frame_Buffer) != 0) {
			if (strcmp (buffer, "technology=("))
				strcat (buffer, ",");
			strcat (buffer, "software frame buffer");
		}
		if ((m_tq & TKO_Technology_Radiosity) != 0) {
			if (strcmp (buffer, "technology=("))
				strcat (buffer, ",");
			strcat (buffer, "radiosity");
		}
		if ((m_tq & TKO_Technology_Ray_Trace) != 0) {
			if (strcmp (buffer, "technology=("))
				strcat (buffer, ",");
			strcat (buffer, "ray-trace");
		}
		strcat (buffer, ")");
		HC_Set_Rendering_Options (buffer);
	}

	if ((m_mask[0] & TKO_Rendo_Quantization) != 0) {
		switch (m_tq & TKO_Quantization_Mask) {
			case TKO_Quantization_Threshold:        HC_Set_Rendering_Options ("quantization=threshold");        break;
			case TKO_Quantization_Dither:           HC_Set_Rendering_Options ("quantization=dither");           break;
			case TKO_Quantization_Error_Diffusion:  HC_Set_Rendering_Options ("quantization=error diffusion");  break;
		}
	}

	if (htk.GetHoopsVersion() >= 750) {
		if ((m_mask[1] & TKO_Rendo_Transparency_Style) != 0) {
			switch (m_transparency_options & TKO_Transparency_Style_Mask) {
				case TKO_Transparency_None:         HC_Set_Rendering_Options ("transparency=style=none");       break;
				case TKO_Transparency_Blending:     HC_Set_Rendering_Options ("transparency=style=blending");   break;
				case TKO_Transparency_Screen_Door:  HC_Set_Rendering_Options ("transparency=style=screen door");break;
			}
		}
		if ((m_mask[1] & TKO_Rendo_Transparency_Hardware) != 0) {
			if ((m_value[1] & TKO_Rendo_Transparency_Hardware) != 0)
				HC_Set_Rendering_Options ("transparency=hardware acceleration");
			else
				HC_Set_Rendering_Options ("transparency=no hardware acceleration");
		}
		if ((m_mask[1] & TKO_Rendo_Transparency_Options) != 0) {
			char                buffer[256];

			if ((m_transparency_options & TKO_Transparency_Peeling_Layers) != 0) {
				sprintf (buffer, "transparency=depth peeling options=layers=%d", m_depth_peeling_layers);
				HC_Set_Rendering_Options (buffer);
			}
			if ((m_transparency_options & TKO_Transparency_Peeling_Min_Area) != 0) {
				if (m_depth_peeling_min_area < 0)
					sprintf (buffer, "transparency=depth peeling options=min area=%d pixels", -(int)m_depth_peeling_min_area);
				else
					sprintf (buffer, "transparency=depth peeling options=min area=%f%%", m_depth_peeling_min_area);
				HC_Set_Rendering_Options (buffer);
			}

			if ((m_transparency_options & TKO_Transparency_ZSort_Fast) != 0) {
				HC_Set_Rendering_Options ("transparency=zsort options=fast");
			}
			else if ((m_transparency_options & TKO_Transparency_ZSort_Nice) != 0) {
				HC_Set_Rendering_Options ("transparency=zsort options=nice");
			}
		}
	}

	if (htk.GetHoopsVersion() >= 850) {
		if ((m_mask[1] & TKO_Rendo_Cut_Geometry) != 0) {
			if ((m_cut_geometry & TKO_Cut_Geometry_Level) != 0) {
				switch (m_cut_geometry_level) {
					case TKO_Cut_Geometry_Level_Entity:
									HC_Set_Rendering_Options ("cut geometry=level=entity");         break;
					case TKO_Cut_Geometry_Level_Segment:
									HC_Set_Rendering_Options ("cut geometry=level=segment");        break;
					case TKO_Cut_Geometry_Level_Segment_Tree:
									HC_Set_Rendering_Options ("cut geometry=level=segment tree");   break;
				}
			}
			if ((m_cut_geometry & TKO_Cut_Geometry_Tolerance) != 0) {
				char        buffer[128];
				char        tol[32];

				write_float (tol, fabs(m_cut_geometry_tolerance));
				sprintf (buffer, "cut geometry=tolerance=%s", tol);
				if (m_cut_geometry_tolerance < 0.0f)
					strcat (buffer, "%");
				HC_Set_Rendering_Options (buffer);
			}
			if (htk.GetHoopsVersion() >= 1003) {
				if ((m_cut_geometry & TKO_Cut_Geometry_Match_Color) != 0)
					switch (m_cut_geometry_match) {
						case TKO_Cut_Geometry_Match_Color_Off:
							HC_Set_Rendering_Options ("cut geometry=no match color");       break;
						case TKO_Cut_Geometry_Match_Color_Current:
							HC_Set_Rendering_Options ("cut geometry=match color");          break;
						case TKO_Cut_Geometry_Match_Color_First:
							HC_Set_Rendering_Options ("cut geometry=match color=first");    break;
						case TKO_Cut_Geometry_Match_Color_Last:
							HC_Set_Rendering_Options ("cut geometry=match color=last");     break;
					}
			}
		}

		if ((m_mask[1] & TKO_Rendo_Depth_Range) != 0) {
			char        buffer[128];
			char        tol[32];

			write_float (tol, m_depth_range[0]);
			sprintf (buffer, "depth range=(%s,", tol);
			write_float (tol, m_depth_range[1]);
			strcat (buffer, tol);
			strcat (buffer, ")");
			HC_Set_Rendering_Options (buffer);
		}
	}

	if (htk.GetHoopsVersion() >= 1050) {
		if ((m_mask[1] & TKO_Rendo_Mask_Transform) != 0 && m_mask_transform) {
			char        buffer[256];

			strcpy (buffer, "mask transform=(");
			if (m_mask_transform & TKO_Mask_Camera) {
				strcat (buffer, "camera=(");
				if (m_mask_transform & TKO_Mask_Camera_Rotation)
					strcat (buffer, "rotation,");
				if (m_mask_transform & TKO_Mask_Camera_Scale)
					strcat (buffer, "scale,");
				if (m_mask_transform & TKO_Mask_Camera_Translation)
					strcat (buffer, "translation,");
				if (m_mask_transform & TKO_Mask_Camera_Perspective)
					strcat (buffer, "perspective,");
				buffer[strlen(buffer)-1] = ')';
				strcat (buffer, ",");
			}
			if (m_mask_transform & TKO_Mask_Model) {
				strcat (buffer, "model=(");
				if (m_mask_transform & TKO_Mask_Model_Rotation)
					strcat (buffer, "rotation,");
				if (m_mask_transform & TKO_Mask_Model_Scale)
					strcat (buffer, "scale,");
				if (m_mask_transform & TKO_Mask_Model_Translation)
					strcat (buffer, "translation,");
				buffer[strlen(buffer)-1] = ')';
				strcat (buffer, ",");
			}
			buffer[strlen(buffer)-1] = ')';
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_mask[1] & TKO_Rendo_Image_Scale) != 0) {
			char        buffer[256];
			char        tol[256];

			write_float (tol, m_image_scale[0]);
			sprintf (buffer, "image scale=(%s,", tol);
			write_float (tol, m_image_scale[1]);
			strcat (buffer, tol);
			strcat (buffer, ")");
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_mask[1] & TKO_Rendo_Ambient_Up_Vector) != 0) {
			if (m_value[1] & TKO_Rendo_Ambient_Up_Vector) {
				char        buffer[256];
				char        tol[256];

				write_float (tol, m_ambient_up_vector[0]);
				sprintf (buffer, "ambient up vector=(%s,", tol);
				write_float (tol, m_ambient_up_vector[1]);
				strcat (buffer, tol);
				strcat (buffer, ",");
				write_float (tol, m_ambient_up_vector[2]);
				strcat (buffer, tol);
				strcat (buffer, ")");
				HC_Set_Rendering_Options (buffer);
			}
			else {
				HC_Set_Rendering_Options ("no ambient up vector");
			}
		}

		if ((m_mask[1] & TKO_Rendo_Gooch_Color_Range) != 0) {
			char        buffer[256];
			char        tol[256];

			write_float (tol, m_gooch_color_range[0]);
			sprintf (buffer, "gooch options=(color range=(%s,", tol);
			write_float (tol, m_gooch_color_range[1]);
			strcat (buffer, tol);
			strcat (buffer, "))");
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_mask[1] & TKO_Rendo_Gooch_Diffuse_Weight) != 0) {
			char        buffer[256];
			char        tol[256];

			write_float (tol, m_gooch_diffuse_weight);
			sprintf (buffer, "gooch options=(diffuse weight=%s)", tol);
			HC_Set_Rendering_Options (buffer);
		}
		
		if ((m_mask[1] & TKO_Rendo_Gooch_Color_Map) != 0) {
			char        buffer[1024];

			if (m_gooch_color_map_segment != null) {
				sprintf (buffer, "gooch options=(color map segment=%s)", m_gooch_color_map_segment);
				HC_Set_Rendering_Options (buffer);
			}
			else
				HC_Set_Rendering_Options ("gooch options=no color map segment");
		}

		if ((m_mask[1] & TKO_Rendo_Local_Cutting_Planes) != 0) {
			if ((m_value[1] & TKO_Rendo_Local_Cutting_Planes) != 0)
				HC_Set_Rendering_Options ("local cutting planes");
			else
				HC_Set_Rendering_Options ("no local cutting planes");
		}

		if ((m_mask[1] & TKO_Rendo_Simple_Shadow) != 0 && m_simple_shadow) {
			char        buffer[256];

			strcpy (buffer, "simple shadow=(");
			if (m_simple_shadow & TKO_Simple_Shadow_On)
				strcat (buffer, "on,");
			else if (m_simple_shadow & TKO_Simple_Shadow_Off)
				strcat (buffer, "off,");
			else if (m_simple_shadow & TKO_Simple_Shadow_Auto)
				strcat (buffer, "auto,");
			if (m_simple_shadow & TKO_Simple_Shadow_Plane) {
				char	val[32];

				strcat (buffer, "plane=(");
				write_float (val, m_simple_shadow_plane[0]);
				strcat (buffer, val);
				strcat (buffer, ",");
				write_float (val, m_simple_shadow_plane[1]);
				strcat (buffer, val);
				strcat (buffer, ",");
				write_float (val, m_simple_shadow_plane[2]);
				strcat (buffer, val);
				strcat (buffer, ",");
				write_float (val, m_simple_shadow_plane[3]);
				strcat (buffer, val);
				strcat (buffer, "),");
			}
			if (m_simple_shadow & TKO_Simple_Shadow_Light_Direction) {
				char	val[32];

				strcat (buffer, "light=(");
				write_float (val, m_simple_shadow_light[0]);
				strcat (buffer, val);
				strcat (buffer, ",");
				write_float (val, m_simple_shadow_light[1]);
				strcat (buffer, val);
				strcat (buffer, ",");
				write_float (val, m_simple_shadow_light[2]);
				strcat (buffer, val);
				strcat (buffer, "),");
			}
			if (m_simple_shadow & TKO_Simple_Shadow_Color) {
				char	val[32];

				strcat (buffer, "color='r=");
				write_float (val, m_simple_shadow_color[0]);
				strcat (buffer, val);
				strcat (buffer, " g=");
				write_float (val, m_simple_shadow_color[1]);
				strcat (buffer, val);
				strcat (buffer, " b=");
				write_float (val, m_simple_shadow_color[2]);
				strcat (buffer, val);
				strcat (buffer, "',");
			}
			if (m_simple_shadow & TKO_Simple_Shadow_Opacity) {
				char	val[32];

				strcat (buffer, "opacity=");
				write_float (val, m_simple_shadow_opacity);
				strcat (buffer, val);
				strcat (buffer, ",");
			}
			if (m_simple_shadow & TKO_Simple_Shadow_Blur) {
				char	val[32];

				sprintf (val, "blurring=%d,", m_simple_shadow_blur);
				strcat (buffer, val);
			}
			if (m_simple_shadow & TKO_Simple_Shadow_Resolution) {
				char	val[32];

				sprintf (val, "resolution=%d,", m_simple_shadow_resolution);
				strcat (buffer, val);
			}
			if (m_simple_shadow & TKO_Simple_Shadow_Ignore_Transparency)
				strcat (buffer, "ignore transparency,");
			else if (m_simple_shadow & TKO_Simple_Shadow_Use_Transparency)
				strcat (buffer, "no ignore transparency,");
			buffer[strlen(buffer)-1] = ')';
			HC_Set_Rendering_Options (buffer);
		}
	}

	if (htk.GetHoopsVersion() >= 1504) {
		if ((m_mask[1] & TKO_Rendo_Screen_Range) != 0) {
			char        buffer[128];
			char        tol[32];

			write_float (tol, m_screen_range[0]);
			sprintf (buffer, "screen range=(%s,", tol);
			write_float (tol, m_screen_range[1]);
			strcat (buffer, tol);
			strcat (buffer, ",");
			write_float (tol, m_screen_range[2]);
			strcat (buffer, tol);
			strcat (buffer, ",");
			write_float (tol, m_screen_range[3]);
			strcat (buffer, tol);
			strcat (buffer, ")");
			HC_Set_Rendering_Options (buffer);
		}
	}

	if (htk.GetHoopsVersion() >= 1550) {
		if ((m_mask[1] & TKO_Rendo_Shadow_Map) != 0 && m_shadow_map) {
			char        buffer[256];

			strcpy (buffer, "shadow map=(");
			if (m_shadow_map & TKO_Shadow_Map_On)
				strcat (buffer, "on,");
			else if (m_shadow_map & TKO_Shadow_Map_Off)
				strcat (buffer, "off,");
			if (m_shadow_map & TKO_Shadow_Map_Jitter_On)
				strcat (buffer, "jitter,");
			else if (m_shadow_map & TKO_Shadow_Map_Jitter_Off)
				strcat (buffer, "no jitter,");
			if (m_shadow_map & TKO_Shadow_Map_Resolution) {
				char	val[32];

				sprintf (val, "resolution=%d,", m_shadow_map_resolution);
				strcat (buffer, val);
			}
			if (m_shadow_map & TKO_Shadow_Map_Samples) {
				char	val[32];

				sprintf (val, "samples=%d,", m_shadow_map_samples);
				strcat (buffer, val);
			}
			if (htk.GetHoopsVersion() >= 1650) {
				if (m_shadow_map & TKO_Shadow_Map_View_Depedent_On) {
					strcat (buffer, "view dependent,");
				}
				else if (m_shadow_map & TKO_Shadow_Map_View_Depedent_Off) {
					strcat (buffer, "view independent,");
				}
			}
			buffer[strlen(buffer)-1] = ')';
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_mask[1] & TKO_Rendo_Simple_Reflection) != 0 && m_simple_reflection) {
			char        buffer[4096];
			char	val[32];

			strcpy (buffer, "simple reflection=(");
			if (m_simple_reflection & TKO_Simple_Reflection_On)
				strcat (buffer, "on,");
			else if (m_simple_reflection & TKO_Simple_Reflection_Off)
				strcat (buffer, "off,");
			if (m_simple_reflection & TKO_Simple_Reflection_Plane) {

				strcat (buffer, "plane=(");
				write_float (val, m_simple_reflection_plane[0]);
				strcat (buffer, val);
				strcat (buffer, ",");
				write_float (val, m_simple_reflection_plane[1]);
				strcat (buffer, val);
				strcat (buffer, ",");
				write_float (val, m_simple_reflection_plane[2]);
				strcat (buffer, val);
				strcat (buffer, ",");
				write_float (val, m_simple_reflection_plane[3]);
				strcat (buffer, val);
				strcat (buffer, "),");
			}
			if (m_simple_reflection & TKO_Simple_Reflection_Opacity) {
				strcat (buffer, "opacity=");
				write_float (val, m_simple_reflection_opacity);
				strcat (buffer, val);
				strcat (buffer, ",");
			}
			if (m_simple_reflection & TKO_Simple_Reflection_Blur) {
				if (m_simple_reflection_blur > 0) {
					strcat (buffer, "blur=");
					write_float (val, m_simple_reflection_blur);
					strcat (buffer, val);
				}
				else
					strcat (buffer, "no blur");
				strcat (buffer, ",");
			}
			if (m_simple_reflection & TKO_Simple_Reflection_Attenuation) {
				strcat (buffer, "attenuation=(hither=");
				write_float (val, m_simple_reflection_hither);
				strcat (buffer, val);
				strcat (buffer, ",yon=");
				write_float (val, m_simple_reflection_yon);
				strcat (buffer, val);
				strcat (buffer, "),");
			}
			if (m_simple_reflection & TKO_Simple_Reflection_Fading_On)
				strcat (buffer, "fading,");
			else if (m_simple_reflection & TKO_Simple_Reflection_Fading_Off)
				strcat (buffer, "no fading,");
			buffer[strlen(buffer)-1] = ')';
			HC_Set_Rendering_Options (buffer);

			if ((m_simple_reflection & TKO_Simple_Reflection_Visibility) != 0) {
				RENDO_REFLECTION_VIS (TKO_Geo_Face,				"face");
				RENDO_REFLECTION_VIS (TKO_Geo_Edge,				"edge");
				RENDO_REFLECTION_VIS (TKO_Geo_Line,				"line");
				RENDO_REFLECTION_VIS (TKO_Geo_Marker,			"markers only");
				RENDO_REFLECTION_VIS (TKO_Geo_Vertex_Vis,		"vertices");
				RENDO_REFLECTION_VIS (TKO_Geo_Text,				"text");
				RENDO_REFLECTION_VIS (TKO_Geo_Window,			"window");
				RENDO_REFLECTION_VIS (TKO_Geo_Cutting_Plane,	"cutting plane");
				RENDO_REFLECTION_VIS (TKO_Geo_Image,			"image");
				RENDO_REFLECTION_VIS (TKO_Geo_Light,			"lighting");
				RENDO_REFLECTION_VIS (TKO_Geo_String_Cursor,	"string cursor");
				RENDO_REFLECTION_VIS (TKO_Geo_Cut_Geometry,		"cut geometry");
				RENDO_REFLECTION_VIS (TKO_Geo_Shadow_Visibles,	"shadows");
			}
		}

		if ((m_mask[0] & TKO_Rendo_Display_Lists) != 0) {
			if (m_value[0] & TKO_Rendo_Display_Lists) {
				switch (m_display_list_level) {
					case TKO_Display_List_Level_Entity:
						HC_Set_Rendering_Options ("display lists");					break;
					case TKO_Display_List_Level_Segment:
						HC_Set_Rendering_Options ("display lists=segment");			break;
					case TKO_Display_List_Level_Segment_Tree:
						HC_Set_Rendering_Options ("display lists=segment tree");	break;
				}
			}
			else
				HC_Set_Rendering_Options ("no display lists");
		}
	}
	else
		RENDO_NORMAL (TKO_Rendo_Display_Lists,     "display lists");

	if (htk.GetHoopsVersion() >= 1710) {
		if ((m_mask[1] & TKO_Rendo_Transparency_Depth_Writing) != 0) {
			if ((m_value[1] & TKO_Rendo_Transparency_Depth_Writing) != 0)
				HC_Set_Rendering_Options ("transparency=depth writing");
			else
				HC_Set_Rendering_Options ("transparency=no depth writing");
		}
	}

	RENDO_NORMAL (TKO_Rendo_Local_Viewer,               "local viewer");
	RENDO_NORMAL (TKO_Rendo_Perspective_Correction,     "perspective correction");

	RENDO_NORMAL (TKO_Rendo_LOD,               "lod");

	RENDO_VALUE (TKO_Rendo_Face_Displacement,  "face displacement",    m_face_displacement,    "%d");
	RENDO_VALUE (TKO_Rendo_Debug,              "debug",                m_debug,                "%d");

	if ((m_mask[0] & TKO_Rendo_Fog) != 0) {
		if ((m_value[0] & TKO_Rendo_Fog) == 0)
			HC_Set_Rendering_Options ("no fog");
		else {
			char        buffer[80];
			char        hh[32], yy[32];

			write_float (hh, m_fog_limits[0]);
			write_float (yy, m_fog_limits[1]);
			sprintf (buffer, "fog=(%s,%s)", hh, yy);
			HC_Set_Rendering_Options (buffer);
		}
	}

	if ((m_mask[0] & TKO_Rendo_Attribute_Lock) != 0) {
		if ((m_value[0] & TKO_Rendo_Attribute_Lock) != 0) {
			//RENDO_LOCK (TKO_Lock_Callback,          "callback");
			RENDO_LOCK (TKO_Lock_Camera,            "camera");
			RENDO_LOCK (TKO_Lock_Color_Map,         "color map");
			RENDO_LOCK (TKO_Lock_Driver,            "driver");
			RENDO_LOCK (TKO_Lock_Driver_Options,    "driver options");
			RENDO_LOCK (TKO_Lock_Edge_Pattern,      "edge pattern");
			RENDO_LOCK (TKO_Lock_Edge_Weight,       "edge weight");
			RENDO_LOCK (TKO_Lock_Face_Pattern,      "face pattern");
			RENDO_LOCK (TKO_Lock_Handedness,        "handedness");
			RENDO_LOCK (TKO_Lock_Heuristics,        "heuristics");
			RENDO_LOCK (TKO_Lock_Line_Pattern,      "line pattern");
			RENDO_LOCK (TKO_Lock_Line_Weight,       "line weight");
			RENDO_LOCK (TKO_Lock_Marker_Size,       "marker size");
			RENDO_LOCK (TKO_Lock_Marker_Symbol,     "marker symbol");
			//RENDO_LOCK (TKO_Lock_Metafile,          "metafile");
			RENDO_LOCK (TKO_Lock_Modelling_Matrix,  "modelling matrix");
			RENDO_LOCK (TKO_Lock_Rendering_Options, "rendering options");
			RENDO_LOCK (TKO_Lock_Selectability,     "selectability");
			RENDO_LOCK (TKO_Lock_Styles,            "style");
			RENDO_LOCK (TKO_Lock_Text_Alignment,    "text alignment");
			RENDO_LOCK (TKO_Lock_Text_Font,         "text font");
			RENDO_LOCK (TKO_Lock_Text_Path,         "text path");
			RENDO_LOCK (TKO_Lock_Text_Spacing,      "text spacing");
			RENDO_LOCK (TKO_Lock_User_Options,      "user options");
			RENDO_LOCK (TKO_Lock_User_Value,        "user value");
			RENDO_LOCK (TKO_Lock_Texture_Matrix,    "texture matrix");
			RENDO_LOCK (TKO_Lock_Window,            "window");
			RENDO_LOCK (TKO_Lock_Window_Frame,      "window frame");
			RENDO_LOCK (TKO_Lock_Window_Pattern,    "window pattern");

			if ((m_lock_mask & TKO_Lock_Color) != 0) {
				if ((m_lock_value & TKO_Lock_Color) != 0) {
					RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Light,         "lighting");
					if (htk.GetHoopsVersion() >= 1650) {
						RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Ambient_Up,    "ambient up");
						RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Ambient_Down,  "ambient down");
					}
					else
						RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Ambient_Up,    "ambient");

					if (htk.GetHoopsVersion() >= 1150) {
						if (htk.GetHoopsVersion() >= 1550) {
							RENDO_COLOR_LOCK (TKO_Geo_Simple_Reflection,	simple_reflection,	"simple reflection");
						}
						RENDO_COLOR_LOCK (TKO_Geo_Face,		    face,		"face");
						RENDO_COLOR_LOCK (TKO_Geo_Front,	    face,		"front");
						RENDO_COLOR_LOCK (TKO_Geo_Back,		    back,		"back");
						RENDO_COLOR_LOCK (TKO_Geo_Edge,		    edge,		"edge");
						RENDO_COLOR_LOCK (TKO_Geo_Line,		    line,		"line");
						RENDO_COLOR_LOCK (TKO_Geo_Marker,	    marker,		"markers only");
						RENDO_COLOR_LOCK (TKO_Geo_Vertex,	    vertex,		"vertices");
						RENDO_COLOR_LOCK (TKO_Geo_Text,		    text,		"text");
						RENDO_COLOR_LOCK (TKO_Geo_Window,	    window,		"window");
						RENDO_COLOR_LOCK (TKO_Geo_Face_Contrast,    face_contrast,	"face contrast");
						RENDO_COLOR_LOCK (TKO_Geo_Edge_Contrast,    edge_contrast,	"edge contrast");
						RENDO_COLOR_LOCK (TKO_Geo_Line_Contrast,    line_contrast,	"line contrast");
						RENDO_COLOR_LOCK (TKO_Geo_Text_Contrast,    text_contrast,	"text contrast");
						RENDO_COLOR_LOCK (TKO_Geo_Marker_Contrast,  marker_contrast,	"marker contrast");
						RENDO_COLOR_LOCK (TKO_Geo_Vertex_Contrast,  vertex_contrast,	"vertex contrast");
						RENDO_COLOR_LOCK (TKO_Geo_Window_Contrast,  window_contrast,	"window contrast");
						RENDO_COLOR_LOCK (TKO_Geo_Cut_Face,			cut_face,			"cut face");
						RENDO_COLOR_LOCK (TKO_Geo_Cut_Edge,			cut_edge,			"cut edge");
					}
					else {
						RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Face,             "face");
						RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Edge,             "edge");
						RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Line,             "line");
						if (htk.GetHoopsVersion() >= 750) {
							RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Marker,       "markers only");
							RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Vertex,       "vertices");
						}
						else
							RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Marker,       "markers");
						RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Text,             "text");
						RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Window,           "window");
						RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Face_Contrast,    "face contrast");
						RENDO_COLOR_SIMPLE_LOCK (TKO_Geo_Window_Contrast,  "window contrast");
					}
				}
				else
					HC_Set_Rendering_Options ("attribute lock=no color");
			}

			if ((m_lock_mask & TKO_Lock_Visibility) != 0) {
				if ((m_lock_value & TKO_Lock_Visibility) != 0) {
					RENDO_VIS_LOCK (TKO_Geo_Face,               "face");
					RENDO_VIS_LOCK (TKO_Geo_Edge,               "edge");
					RENDO_VIS_LOCK (TKO_Geo_Line,               "line");
					if (htk.GetHoopsVersion() >= 750) {
						RENDO_VIS_LOCK (TKO_Geo_Marker,         "markers only");
						RENDO_VIS_LOCK (TKO_Geo_Vertex_Vis,     "vertices");
					}
					else
						RENDO_VIS_LOCK (TKO_Geo_Marker,         "markers");
					RENDO_VIS_LOCK (TKO_Geo_Text,               "text");
					RENDO_VIS_LOCK (TKO_Geo_Window,             "window");
					RENDO_VIS_LOCK (TKO_Geo_Cutting_Plane,      "cutting plane");
					RENDO_VIS_LOCK (TKO_Geo_Image,              "image");
					RENDO_VIS_LOCK (TKO_Geo_Light,              "lighting");
					RENDO_VIS_LOCK (TKO_Geo_String_Cursor,      "string cursor");
					RENDO_VIS_LOCK (TKO_Geo_Cut_Geometry,		"cut geometry");
					RENDO_VIS_LOCK (TKO_Geo_Shadow_Visibles,    "shadows");
				}
				else
					HC_Set_Rendering_Options ("attribute lock=no visibility");
			}
		}
		else
			HC_Set_Rendering_Options ("no attribute lock");
	}

	if ((m_mask[2] & TKO_Rendo_Forced_Lock) != 0) {
		if ((m_value[2] & TKO_Rendo_Forced_Lock) != 0) {
			//RENDO_FORCED (TKO_Lock_Callback,          "callback");
			RENDO_FORCED (TKO_Lock_Camera,            "camera");
			RENDO_FORCED (TKO_Lock_Color_Map,         "color map");
			RENDO_FORCED (TKO_Lock_Driver,            "driver");
			RENDO_FORCED (TKO_Lock_Driver_Options,    "driver options");
			RENDO_FORCED (TKO_Lock_Edge_Pattern,      "edge pattern");
			RENDO_FORCED (TKO_Lock_Edge_Weight,       "edge weight");
			RENDO_FORCED (TKO_Lock_Face_Pattern,      "face pattern");
			RENDO_FORCED (TKO_Lock_Handedness,        "handedness");
			RENDO_FORCED (TKO_Lock_Heuristics,        "heuristics");
			RENDO_FORCED (TKO_Lock_Line_Pattern,      "line pattern");
			RENDO_FORCED (TKO_Lock_Line_Weight,       "line weight");
			RENDO_FORCED (TKO_Lock_Marker_Size,       "marker size");
			RENDO_FORCED (TKO_Lock_Marker_Symbol,     "marker symbol");
			//RENDO_FORCED (TKO_Lock_Metafile,          "metafile");
			RENDO_FORCED (TKO_Lock_Modelling_Matrix,  "modelling matrix");
			RENDO_FORCED (TKO_Lock_Rendering_Options, "rendering options");
			RENDO_FORCED (TKO_Lock_Selectability,     "selectability");
			RENDO_FORCED (TKO_Lock_Styles,            "style");
			RENDO_FORCED (TKO_Lock_Text_Alignment,    "text alignment");
			RENDO_FORCED (TKO_Lock_Text_Font,         "text font");
			RENDO_FORCED (TKO_Lock_Text_Path,         "text path");
			RENDO_FORCED (TKO_Lock_Text_Spacing,      "text spacing");
			RENDO_FORCED (TKO_Lock_User_Options,      "user options");
			RENDO_FORCED (TKO_Lock_User_Value,        "user value");
			RENDO_FORCED (TKO_Lock_Texture_Matrix,    "texture matrix");
			RENDO_FORCED (TKO_Lock_Window,            "window");
			RENDO_FORCED (TKO_Lock_Window_Frame,      "window frame");
			RENDO_FORCED (TKO_Lock_Window_Pattern,    "window pattern");

			if ((m_forced_mask & TKO_Lock_Color) != 0) {
				if ((m_forced_value & TKO_Lock_Color) != 0) {
					RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Light,         "lighting");
					if (htk.GetHoopsVersion() >= 1650) {
						RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Ambient_Up,    "ambient up");
						RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Ambient_Down,  "ambient down");
					}
					else
						RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Ambient_Up,    "ambient");

					if (htk.GetHoopsVersion() >= 1150) {
						if (htk.GetHoopsVersion() >= 1550) {
							RENDO_COLOR_FORCED (TKO_Geo_Simple_Reflection,	simple_reflection,	"simple reflection");
						}
						RENDO_COLOR_FORCED (TKO_Geo_Face,		    face,		"face");
						RENDO_COLOR_FORCED (TKO_Geo_Front,			face,		"front");
						RENDO_COLOR_FORCED (TKO_Geo_Back,		    back,		"back");
						RENDO_COLOR_FORCED (TKO_Geo_Edge,		    edge,		"edge");
						RENDO_COLOR_FORCED (TKO_Geo_Line,		    line,		"line");
						RENDO_COLOR_FORCED (TKO_Geo_Marker,			marker,		"markers only");
						RENDO_COLOR_FORCED (TKO_Geo_Vertex,			vertex,		"vertices");
						RENDO_COLOR_FORCED (TKO_Geo_Text,		    text,		"text");
						RENDO_COLOR_FORCED (TKO_Geo_Window,			window,		"window");
						RENDO_COLOR_FORCED (TKO_Geo_Face_Contrast,    	face_contrast,	"face contrast");
						RENDO_COLOR_FORCED (TKO_Geo_Edge_Contrast,    	edge_contrast,	"edge contrast");
						RENDO_COLOR_FORCED (TKO_Geo_Line_Contrast,    	line_contrast,	"line contrast");
						RENDO_COLOR_FORCED (TKO_Geo_Text_Contrast,    	text_contrast,	"text contrast");
						RENDO_COLOR_FORCED (TKO_Geo_Marker_Contrast,  	marker_contrast,	"marker contrast");
						RENDO_COLOR_FORCED (TKO_Geo_Vertex_Contrast,  	vertex_contrast,	"vertex contrast");
						RENDO_COLOR_FORCED (TKO_Geo_Window_Contrast,  	window_contrast,	"window contrast");
						RENDO_COLOR_FORCED (TKO_Geo_Cut_Face,			cut_face,			"cut face");
						RENDO_COLOR_FORCED (TKO_Geo_Cut_Edge,			cut_edge,			"cut edge");
					}
					else {
						RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Face,             "face");
						RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Edge,             "edge");
						RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Line,             "line");
						if (htk.GetHoopsVersion() >= 750) {
							RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Marker,       "markers only");
							RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Vertex,       "vertices");
						}
						else
							RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Marker,       "markers");
						RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Text,             "text");
						RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Window,           "window");
						RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Face_Contrast,    "face contrast");
						RENDO_COLOR_SIMPLE_FORCED (TKO_Geo_Window_Contrast,  "window contrast");
					}
				}
				else
					HC_Set_Rendering_Options ("ignore subsegment locks=no color");
			}

			if ((m_forced_mask & TKO_Lock_Visibility) != 0) {
				if ((m_forced_value & TKO_Lock_Visibility) != 0) {
					RENDO_VIS_FORCED (TKO_Geo_Face,               "face");
					RENDO_VIS_FORCED (TKO_Geo_Edge,               "edge");
					RENDO_VIS_FORCED (TKO_Geo_Line,               "line");
					if (htk.GetHoopsVersion() >= 750) {
						RENDO_VIS_FORCED (TKO_Geo_Marker,         "markers only");
						RENDO_VIS_FORCED (TKO_Geo_Vertex_Vis,     "vertices");
					}
					else
						RENDO_VIS_FORCED (TKO_Geo_Marker,         "markers");
					RENDO_VIS_FORCED (TKO_Geo_Text,               "text");
					RENDO_VIS_FORCED (TKO_Geo_Window,             "window");
					RENDO_VIS_FORCED (TKO_Geo_Cutting_Plane,      "cutting plane");
					RENDO_VIS_FORCED (TKO_Geo_Image,              "image");
					RENDO_VIS_FORCED (TKO_Geo_Light,              "lighting");
					RENDO_VIS_FORCED (TKO_Geo_String_Cursor,      "string cursor");
					RENDO_VIS_FORCED (TKO_Geo_Cut_Geometry,		"cut geometry");
					RENDO_VIS_FORCED (TKO_Geo_Shadow_Visibles,    "shadows");
				}
				else
					HC_Set_Rendering_Options ("ignore subsegment locks=no visibility");
			}
		}
		else
			HC_Set_Rendering_Options ("no ignore subsegment locks");
	}

	RENDO_NORMAL (TKO_Rendo_Stereo,              "stereo");

	RENDO_EXTENDED_2 (TKO_Rendo_Scaled_Displacement, "scaled displacement");

	if ((m_mask[0] & TKO_Rendo_Stereo_Separation) != 0) {
		if ((m_value[0] & TKO_Rendo_Stereo_Separation) != 0) {
			char        buff[64], value[32];

			write_float (value, m_stereo_separation);
			sprintf (buff, "stereo separation = %s", value);
			HC_Set_Rendering_Options (buff);
		}
		else
			HC_Set_Rendering_Options ("no stereo separation");
	}
	if ((m_mask[1] & TKO_Rendo_Stereo_Distance) != 0) {
		if ((m_value[1] & TKO_Rendo_Stereo_Distance) != 0) {
			char        buff[64], value[32];

			write_float (value, m_stereo_distance);
			sprintf (buff, "stereo distance = %s", value);
			HC_Set_Rendering_Options (buff);
		}
		else
			HC_Set_Rendering_Options ("no stereo distance");
	}

	if ((m_mask[0] & TKO_Rendo_Buffer_Options) != 0) {
		if ((m_buffer_options_mask & TKO_Buffer_Size_Limit) != 0) {
			if ((m_buffer_options_value & TKO_Buffer_Size_Limit) != 0) {
				char        buffer[64];

				if (m_buffer_size_limit < 0)
					sprintf (buffer, "sfb options=size limit = %d bytes", -m_buffer_size_limit);
				else
					sprintf (buffer, "sfb options=size limit = %d rasters", m_buffer_size_limit);
				HC_Set_Rendering_Options (buffer);
			}
			else
				HC_Set_Rendering_Options ("sfb options=no size limit");
		}

		if ((m_buffer_options_mask & TKO_Buffer_Retention) != 0) {
			if ((m_buffer_options_value & TKO_Buffer_Retention) != 0)
				HC_Set_Rendering_Options ("sfb options=retention");
			else
				HC_Set_Rendering_Options ("sfb options=no retention");
		}

		if ((m_buffer_options_mask & TKO_Buffer_Color_Depth_Match) != 0)
			HC_Set_Rendering_Options ("sfb options=color depth=match device");
		else if ((m_buffer_options_mask & TKO_Buffer_Color_Depth_Full) != 0)
			HC_Set_Rendering_Options ("sfb options=color depth=full color");
	}


	if ((m_mask[0] & TKO_Rendo_Hidden_Line_Options) != 0) {
		char        buffer[64];

		if ((m_hlr_options & TKO_Hidden_Line_Pattern) != 0) {
			if (m_hlr_line_pattern == -1)
				HC_Set_Rendering_Options ("hlr options=no pattern");
			else {
#if 0
			sprintf (buffer, "hlr options=pattern=%s", line_patterns[m_hlr_line_pattern]);
#else
			sprintf (buffer, "hlr options=pattern=%d", m_hlr_line_pattern);
#endif
			HC_Set_Rendering_Options (buffer);
			}
		}

		if ((m_hlr_options & TKO_Hidden_Line_Dim_Factor) != 0) {
			char        value[32];

			write_float (value, m_hlr_dim_factor);
			sprintf (buffer, "hlr options=dim factor=%s", value);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_hlr_options & TKO_Hidden_Line_Face_Displacement) != 0) {
			char        value[32];

			write_float (value, m_hlr_face_displacement);
			sprintf (buffer, "hlr options=face displacement=%s", value);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_hlr_options & TKO_Hidden_Line_Transparency_Cutoff) != 0) {
			char        value[32];

			write_float (value, m_hlr_transparency_cutoff);
			sprintf (buffer, "hlr options=transparency cutoff=%s", value);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_hlr_options & TKO_Hidden_Line_Visibility_On) != 0)
			HC_Set_Rendering_Options ("hlr options=visibility=on");
		else if ((m_hlr_options & TKO_Hidden_Line_Visibility_Off) != 0)
			HC_Set_Rendering_Options ("hlr options=visibility=off");


		if (htk.GetHoopsVersion() >= 850) {
			if ((m_hlr_options & TKO_Hidden_Line_Render_Faces_On) != 0)
				HC_Set_Rendering_Options ("hlr options=render faces");
			else if ((m_hlr_options & TKO_Hidden_Line_Render_Faces_Off) != 0)
				HC_Set_Rendering_Options ("hlr options=no render faces");
		}
		if (htk.GetHoopsVersion() >= 903) {
			if ((m_hlr_options & TKO_Hidden_Line_Silhouette_Cleanup_On) != 0)
				HC_Set_Rendering_Options ("hlr options=silhouette cleanup");
			else if ((m_hlr_options & TKO_Hidden_Line_Silhouette_Cleanup_Off) != 0)
				HC_Set_Rendering_Options ("hlr options=no silhouette cleanup");
		}
		if (htk.GetHoopsVersion() >= 1150) {
			if ((m_hlr_options & TKO_Hidden_Line_Color) != 0) {
				if (m_hlr_color[0] < 0.0f || m_hlr_color[1] < 0.0f || m_hlr_color[2] < 0.0f)
					HC_Set_Rendering_Options ("hlr options=no color");
				else {
					char	buffer[128], variable[64];

					strcpy (buffer, "hlr options=color=R=");
					write_float (variable, m_hlr_color[0]);
					strcat (buffer, variable);
					strcat (buffer, " G=");
					write_float (variable, m_hlr_color[1]);
					strcat (buffer, variable);
					strcat (buffer, " B=");
					write_float (variable, m_hlr_color[2]);
					strcat (buffer, variable);
					HC_Set_Rendering_Options (buffer);
				}
			}

			if ((m_hlr_options & TKO_Hidden_Line_Weight) != 0) {
				if (m_hlr_weight < 0.0f)
					HC_Set_Rendering_Options ("hlr options=no weight");
				else {
					char	buffer[128], variable[64];

					write_float (variable, m_hlr_weight);
					if (m_hlr_weight_units != 255) {
					strcat (variable, " ");
					strcat (variable, generic_units_table[m_hlr_weight_units]);
					}
					sprintf (buffer, "hlr options=weight=%s", variable);
					HC_Set_Rendering_Options (buffer);
				}
			}

			if ((m_hlr_options & TKO_Hidden_Line_Image_Outline_On) != 0)
				HC_Set_Rendering_Options ("hlr options=image outline");
			else if ((m_hlr_options & TKO_Hidden_Line_Image_Outline_Off) != 0)
				HC_Set_Rendering_Options ("hlr options=no image outline");

			if ((m_hlr_options & TKO_Hidden_Line_HSR_Algorithm) != 0) {
				switch (m_hlr_hsr_algorithm & TKO_HSR_Mask) {
					case TKO_HSR_Hardware:      HC_Set_Rendering_Options ("hlro=rfsa=hardware z buffer");   break;
					case TKO_HSR_SZB:           HC_Set_Rendering_Options ("hlro=rfsa=software z buffer");   break;
					case TKO_HSR_Painters:      HC_Set_Rendering_Options ("hlro=rfsa=painters");            break;
					case TKO_HSR_Z_Sort_Only:   HC_Set_Rendering_Options ("hlro=rfsa=z-sort only");         break;
					case TKO_HSR_None:			HC_Set_Rendering_Options ("hlro=rfsa=none");				break;
				}
			}
		}
	}

	if ((m_mask[0] & TKO_Rendo_NURBS_Curve_Options) != 0) {
		char        buffer[64], number[32];

		if ((m_nurbs_options_mask & TKO_NURBS_Curve_View_Dependent) != 0) {
			if ((m_nurbs_options_value & TKO_NURBS_Curve_View_Dependent) != 0)
				HC_Set_Rendering_Options ("nurbs curve=view dependent");
			else
				HC_Set_Rendering_Options ("nurbs curve=no view dependent");
		}

		if ((m_nurbs_options_mask & TKO_NURBS_Curve_Budget) != 0) {
			sprintf (buffer, "nurbs curve=budget=%d", m_curve_budget);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_nurbs_options_mask & TKO_NURBS_Curve_Continued_Budget) != 0) {
			if ((m_nurbs_options_value & TKO_NURBS_Curve_Continued_Budget) != 0) {
				sprintf (buffer, "nurbs curve=continued budget=%d", m_curve_continued_budget);
				HC_Set_Rendering_Options (buffer);
			}
			else
				HC_Set_Rendering_Options ("nurbs curve=no continued budget");
		}

		if ((m_nurbs_options_mask & TKO_NURBS_Curve_Max_Angle) != 0) {
			write_float (number, m_curve_max_angle);
			sprintf (buffer, "nurbs curve=max angle=%s", number);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_nurbs_options_mask & TKO_NURBS_Curve_Max_Deviation) != 0) {
			write_float (number, m_curve_max_deviation);
			sprintf (buffer, "nurbs curve=max deviation=%s", number);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_nurbs_options_mask & TKO_NURBS_Curve_Max_Length) != 0) {
			write_float (number, m_curve_max_length);
			sprintf (buffer, "nurbs curve=max length=%s", number);
			HC_Set_Rendering_Options (buffer);
		}
	}

	if ((m_mask[0] & TKO_Rendo_NURBS_Surface_Options) != 0) {
		char        buffer[128], number[32];

		if ((m_nurbs_options_mask & TKO_NURBS_Surface_Budget) != 0) {
			sprintf (buffer, "nurbs surface=budget=%d", m_surface_budget);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_nurbs_options_mask & TKO_NURBS_Surface_Trim_Budget) != 0) {
			sprintf (buffer, "nurbs surface=trim budget=%d", m_surface_trim_budget);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_nurbs_options_mask & TKO_NURBS_Surface_Max_Trim_Curve_Deviation) != 0) {
			write_float (number, m_surface_max_trim_curve_deviation);
			sprintf (buffer, "nurbs surface=max trim curve deviation=%s", number);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_nurbs_options_mask & TKO_NURBS_Surface_Max_Facet_Angle) != 0) {
			write_float (number, m_surface_max_facet_angle);
			sprintf (buffer, "nurbs surface=max facet angle=%s", number);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_nurbs_options_mask & TKO_NURBS_Surface_Max_Facet_Deviation) != 0) {
			write_float (number, m_surface_max_facet_deviation);
			sprintf (buffer, "nurbs surface=max facet deviation=%s", number);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_nurbs_options_mask & TKO_NURBS_Surface_Max_Facet_Width) != 0) {
			write_float (number, m_surface_max_facet_width);
			sprintf (buffer, "nurbs surface=max facet width=%s", number);
			HC_Set_Rendering_Options (buffer);
		}
	}

	if ((m_mask[0] & m_value[0] & TKO_Rendo_LOD_Options) != 0) {
		char        buffer[256], value[32];
		int         i;

		if ((m_lod_options_mask & TKO_LOD_Algorithm) != 0) {
			switch (m_lod_algorithm) {
				case TKO_LOD_Algorithm_Fast:
					HC_Set_Rendering_Options ("lod options=algorithm=fast");    break;
				case TKO_LOD_Algorithm_Nice:
					HC_Set_Rendering_Options ("lod options=algorithm=nice");    break;
				default:
					return tk.Error ("unrecognised lod algorithm");             nobreak;
			}
		}

		if ((m_lod_options_mask & (TKO_LOD_Bounding_Current|TKO_LOD_Bounding_Explicit)) != 0) {
			if ((m_lod_options_value & TKO_LOD_Bounding_Current) != 0)
				HC_Set_Rendering_Options ("lod options=bounding=current");
			else if ((m_lod_options_value & TKO_LOD_Bounding_Explicit) != 0) {
				strcpy (buffer, "lod options=bounding=(");
				for (i=0; i<6; ++i) {
					write_float (value, m_bounding[i]);
					strcat (buffer, value);
					strcat (buffer, ",");
				}
				buffer[strlen(buffer)-1] = ')';
				HC_Set_Rendering_Options (buffer);
			}
			else
				HC_Set_Rendering_Options ("lod options=no bounding");
		}

		if ((m_lod_options_mask & TKO_LOD_Calculation_Cutoff) != 0) {
			if ((m_lod_options_value & TKO_LOD_Calculation_Cutoff) != 0) {
				strcpy (buffer, "lod options=calculation usefulness cutoff=(");
				for (i=0; i<m_num_cutoffs; ++i) {
					write_float (value, m_cutoff[i]);
					strcat (buffer, value);
					strcat (buffer, ",");
				}
				buffer[strlen(buffer)-1] = ')';
				HC_Set_Rendering_Options (buffer);
			}
			else
				HC_Set_Rendering_Options ("lod options=no calculation usefulness cutoff");
		}

		if ((m_lod_options_mask & TKO_LOD_Clamp) != 0) {
			if ((m_lod_options_value & TKO_LOD_Clamp) != 0) {
				sprintf (buffer, "lod options=clamp=%d", m_clamp);
				HC_Set_Rendering_Options (buffer);
			}
			else
				HC_Set_Rendering_Options ("lod options=no clamp");
		}

		if ((m_lod_options_mask & TKO_LOD_Collapse_Vertices) != 0) {
			if ((m_lod_options_value & TKO_LOD_Collapse_Vertices) != 0)
				HC_Set_Rendering_Options ("lod options=collapse duplicate vertices");
			else
				HC_Set_Rendering_Options ("lod options=no collapse duplicate vertices");
		}

		if ((m_lod_options_mask & TKO_LOD_Conserve_Memory) != 0) {
			if ((m_lod_options_value & TKO_LOD_Conserve_Memory) != 0)
				HC_Set_Rendering_Options ("lod options=conserve memory");
			else
				HC_Set_Rendering_Options ("lod options=no conserve memory");
		}

		if ((m_lod_options_mask & TKO_LOD_Fallback) != 0) {
			if ((m_lod_options_value & TKO_LOD_Fallback) != 0) {
				switch (m_fallback) {
					case TKO_LOD_Fallback_Bounding:
						HC_Set_Rendering_Options ("lod options=fallback=bounding");             break;
					case TKO_LOD_Fallback_Coarsest:
						HC_Set_Rendering_Options ("lod options=fallback=coarsest");             break;
					case TKO_LOD_Fallback_Coarsest_Bounding:
						HC_Set_Rendering_Options ("lod options=fallback=coarsest bounding");    break;
					case TKO_LOD_Fallback_Coarsest_None:
						HC_Set_Rendering_Options ("lod options=fallback=coarsest none");        break;
					case TKO_LOD_Fallback_Bounding_None:
						HC_Set_Rendering_Options ("lod options=fallback=bounding none");        break;
					default:
						return tk.Error ("unexpected fallback method");                        nobreak;
				}
			}
			else
				HC_Set_Rendering_Options ("lod options=no fallback");
		}

		if ((m_lod_options_mask & TKO_LOD_Max_Degree) != 0) {
			if ((m_lod_options_value & TKO_LOD_Max_Degree) != 0) {
				sprintf (buffer, "lod options=max degree=%d", m_max_degree);
				HC_Set_Rendering_Options (buffer);
			}
			else
				HC_Set_Rendering_Options ("lod options=no max degree");
		}

		if ((m_lod_options_mask & TKO_LOD_Min_Triangle_Count) != 0) {
			sprintf (buffer, "lod options=min triangle count=%d", m_min_triangle_count);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_lod_options_mask & TKO_LOD_Num_Levels) != 0) {
			sprintf (buffer, "lod options=num levels=%d", m_num_levels);
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_lod_options_mask & TKO_LOD_Max_Degree) != 0) {
			if ((m_lod_options_value & TKO_LOD_Max_Degree) != 0)
				HC_Set_Rendering_Options ("lod options=preprocess");
			else
				HC_Set_Rendering_Options ("lod options=no preprocess");
		}

		if ((m_lod_options_mask & TKO_LOD_Ratio) != 0) {
			strcpy (buffer, "lod options=ratio=(");
			for (i=0; i<m_num_ratios; ++i) {
				write_float (value, m_ratio[i]);
				strcat (buffer, value);
				strcat (buffer, ",");
			}
			buffer[strlen(buffer)-1] = ')';
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_lod_options_mask & TKO_LOD_Threshold) != 0) {
			strcpy (buffer, "lod options=threshold=(");
			for (i=0; i<m_num_thresholds; ++i) {
				write_float (value, m_threshold[i]);
				strcat (buffer, value);
				strcat (buffer, ",");
			}
			buffer[strlen(buffer)-1] = '\0';
			switch (m_threshold_type) {
				case TKO_LOD_Threshold_Tris_Per_Pix_Sq: strcat (buffer, " tppix2"); break;
				case TKO_LOD_Threshold_Tris_Per_CM_Sq:  strcat (buffer, " tpcm2");  break;
				case TKO_LOD_Threshold_Percent_Area:    strcat (buffer, " % area"); break;
			}
			strcat (buffer, ")");
			HC_Set_Rendering_Options (buffer);
		}

		if ((m_lod_options_mask & TKO_LOD_Usefulness_Heuristic) != 0) {
			if ((m_lod_options_value & TKO_LOD_Usefulness_Heuristic) != 0) {
				strcpy (buffer, "lod options=usefulness heuristic=");
				if (m_heuristic == TKO_LOD_Heur_Triangle_Size)
					strcat (buffer, "triangle size");
				else {
					if ((m_heuristic & TKO_LOD_Heur_Is_Volume) != 0)
						strcat (buffer, "volume");
					else
						strcat (buffer, "diagonal");

					if ((m_heuristic & TKO_LOD_Heur_Is_Ratio) != 0)
						strcat (buffer, " ratio");

					if ((m_heuristic & TKO_LOD_Heur_Is_Per_Triangle) != 0)
						strcat (buffer, " per triangle");
				}
				HC_Set_Rendering_Options (buffer);
			}
			else
				HC_Set_Rendering_Options ("lod options=no usefulness heuristic");
		}

		if ((m_lod_options_mask & TKO_LOD_Mode_Segment) != 0) {
			if ((m_lod_options_value & TKO_LOD_Mode_Segment) != 0)
				HC_Set_Rendering_Options ("lod options=mode=segment");
			else
				HC_Set_Rendering_Options ("lod options=mode=geometry");
		}
	}

	if ((m_mask[1] & m_value[1] & TKO_Rendo_Tessellation) != 0) {
		char        buffer[256], value[32];
		int         i;

		if ((m_tessellations & TKO_Tessellation_Cylinder) != 0) {
			strcpy (buffer, "tessellation=cylinder=(");
			for (i=0; i<m_num_cylinder; ++i) {
				int	num = m_cylinder[i];

				if (num == 255)	// deal with default unsigned char problem
					num = -1;
				sprintf (value, "%d,", num);
				strcat (buffer, value);
			}
			buffer[strlen(buffer)-1] = ')';
			HC_Set_Rendering_Options (buffer);
		}
		if ((m_tessellations & TKO_Tessellation_Sphere) != 0) {
			strcpy (buffer, "tessellation=sphere=(");
			for (i=0; i<m_num_sphere; ++i) {
				int	num = m_sphere[i];

				if (num == 255)	// deal with default unsigned char problem
					num = -1;
				sprintf (value, "%d,", num);
				strcat (buffer, value);
			}
			buffer[strlen(buffer)-1] = ')';
			HC_Set_Rendering_Options (buffer);
		}
	}

	if ((m_mask[1] & m_value[1] & TKO_Rendo_Geometry_Options) != 0 &&
		htk.GetHoopsVersion() >= 1250) {
		char        buffer[256], value[32];

		if ((m_geometry_options & TKO_Geometry_Options_Dihedral) != 0) {
			strcpy (buffer, "geometry options=hard edge angle=");
			write_float (value, GetHardEdgeAngle());
			strcat (buffer, value);
			HC_Set_Rendering_Options (buffer);
		}
		if ((m_geometry_options & TKO_Geometry_Options_Reverse_PolyCylinder_Radii) != 0)
			HC_Set_Rendering_Options ("geometry options=invert polycylinder=radii");
		else if ((m_geometry_options & TKO_Geometry_Options_No_Reverse_PolyCylinder_Radii) != 0)
			HC_Set_Rendering_Options ("geometry options=invert polycylinder=no radii");
		if ((m_geometry_options & TKO_Geometry_Options_Reverse_PolyCylinder_Colors) != 0)
			HC_Set_Rendering_Options ("geometry options=invert polycylinder=colors");
		else if ((m_geometry_options & TKO_Geometry_Options_No_Reverse_PolyCylinder_Colors) != 0)
			HC_Set_Rendering_Options ("geometry options=invert polycylinder=no colors");
	}

	if ((m_mask[1] & m_value[1] & TKO_Rendo_Image_Tint) != 0 &&
		htk.GetHoopsVersion() >= 1270) {

		char	val[32];
		char	buffer[256];

		strcpy (buffer, "image tint ='r=");
		write_float (val, m_image_tint_color[0]);
		strcat (buffer, val);
		strcat (buffer, " g=");
		write_float (val, m_image_tint_color[1]);
		strcat (buffer, val);
		strcat (buffer, " b=");
		write_float (val, m_image_tint_color[2]);
		strcat (buffer, val);
		strcat (buffer, "'");

		HC_Set_Rendering_Options (buffer);
	}

	if ((m_mask[2] & m_value[2] & TKO_Rendo_Diffuse_Texture_Tint) != 0 &&
		htk.GetHoopsVersion() >= 1270) {

		char	val[32];
		char	buffer[256];

		strcpy (buffer, "diffuse texture tint ='r=");
		write_float (val, m_texture_tint_color[0]);
		strcat (buffer, val);
		strcat (buffer, " g=");
		write_float (val, m_texture_tint_color[1]);
		strcat (buffer, val);
		strcat (buffer, " b=");
		write_float (val, m_texture_tint_color[2]);
		strcat (buffer, val);
		strcat (buffer, "'");

		HC_Set_Rendering_Options (buffer);
	}

	if ((m_mask[1] & TKO_Rendo_Force_Grayscale) != 0 &&
		htk.GetHoopsVersion() >= 1300) {
		if ((m_value[1] & TKO_Rendo_Force_Grayscale) != 0)
			HC_Set_Rendering_Options ("force grayscale");
		else
			HC_Set_Rendering_Options ("no force grayscale");
	}

	if ((m_mask[1] & m_value[1] & TKO_Rendo_Vertex_Displacement) != 0 &&
		htk.GetHoopsVersion() >= 1750) {
			char	buffer[256];
			sprintf (buffer, "vertex displacement = %d", m_vertex_displacement);
			HC_Set_Rendering_Options (buffer);
	}
	if ((m_mask[1] & m_value[1] & TKO_Rendo_General_Displacement) != 0 &&
		htk.GetHoopsVersion() >= 1335) {
			char	buffer[256];
			sprintf (buffer, "general displacement = %d", m_general_displacement);
			HC_Set_Rendering_Options (buffer);
	}

	if ((m_mask[1] & m_value[1] & TKO_Rendo_Join_Cutoff_Angle) != 0 &&
		htk.GetHoopsVersion() >= 1405) {
			char	buffer[256];
			if (htk.GetVersion() < 1820)
				sprintf (buffer, "join cutoff angle = %d", m_join_cutoff_angle);
			else
				sprintf (buffer, "join cutoff angle = line = %d", m_join_cutoff_angle);
			HC_Set_Rendering_Options (buffer);
	}
	if ((m_mask[2] & m_value[2] & TKO_Rendo_Edge_Join_Cutoff_Angle) != 0 &&
		htk.GetHoopsVersion() >= 1850) {
			char	buffer[256];
			sprintf (buffer, "join cutoff angle = edge = %d", m_edge_join_cutoff_angle);
			HC_Set_Rendering_Options (buffer);
	}

	if ((m_mask[1] & TKO_Rendo_Antialias) != 0) {
		if ((m_value[1] & TKO_Rendo_Antialias) != 0) {
			if ((m_antialias & TKO_Antialias_All_On) == TKO_Antialias_All_On)
				HC_Set_Rendering_Options ("anti-alias");
			else if ((m_antialias & TKO_Antialias_All_On) == TKO_Antialias_All_Off)
				HC_Set_Rendering_Options ("no anti-alias");
			else {
				if ((m_antialias & TKO_Antialias_Screen_On) != 0)
					HC_Set_Rendering_Options ("anti-alias=screen");
				else if ((m_antialias & TKO_Antialias_Screen_Off) != 0)
					HC_Set_Rendering_Options ("anti-alias=no screen");

				if ((m_antialias & TKO_Antialias_Lines_On) != 0)
					HC_Set_Rendering_Options ("anti-alias=lines");
				else if ((m_antialias & TKO_Antialias_Lines_Off) != 0)
					HC_Set_Rendering_Options ("anti-alias=no lines");

				if ((m_antialias & TKO_Antialias_Text_On) != 0)
					HC_Set_Rendering_Options ("anti-alias=text");
				else if ((m_antialias & TKO_Antialias_Text_Off) != 0)
					HC_Set_Rendering_Options ("anti-alias=no text");
			}
		}
		else
			HC_Set_Rendering_Options ("no anti-alias");
	}

	if (htk.GetHoopsVersion() >= 1750) {
		if ((m_mask[1] & m_value[1] & TKO_Rendo_Vertex_Decimation) != 0) {
			char	val[32];
			char	buffer[256];

			strcpy (buffer, "vertex decimation = ");
			write_float (val, m_vertex_decimation);
			strcat (buffer, val);

			HC_Set_Rendering_Options (buffer);
		}

		if ((m_hlr_options & TKO_Hidden_Line_Render_Text_On) != 0)
			HC_Set_Rendering_Options ("hlr options=render text");
		else if ((m_hlr_options & TKO_Hidden_Line_Render_Text_Off) != 0)
			HC_Set_Rendering_Options ("hlr options=no render text");
	}


	if ((m_mask[2] & TKO_Rendo_Frame_Buffer_Effects) != 0) {
		if ((m_value[2] & TKO_Rendo_Frame_Buffer_Effects) != 0)
			HC_Set_Rendering_Options ("frame buffer effects");
		else
			HC_Set_Rendering_Options ("no frame buffer effects");
	}


	if ((m_mask[2] & TKO_Rendo_Contour_Options) != 0) {
		char			buffer[256];

		if ((m_contour_options & TKO_Contour_Visibility_Mask) != 0) {
			if ((m_contour_options & (TKO_Contour_Face_Visibility_On|TKO_Contour_Face_Visibility_Off)) != 0) {
				strcpy (buffer, "contour options=visibility=");

				if ((m_contour_options & TKO_Contour_Face_Visibility_On) != 0)
					strcat (buffer, "on");
				else if ((m_contour_options & TKO_Contour_Face_Visibility_Off) != 0)
					strcat (buffer, "off");

				HC_Set_Rendering_Options (buffer);
			}

			if ((m_contour_options & (TKO_Contour_Isoline_Visibility_On|TKO_Contour_Isoline_Visibility_Off)) != 0) {
				strcpy (buffer, "isoline options=visibility=");

				if ((m_contour_options & TKO_Contour_Isoline_Visibility_On) != 0)
					strcat (buffer, "on");
				else if ((m_contour_options & TKO_Contour_Isoline_Visibility_Off) != 0)
					strcat (buffer, "off");

				HC_Set_Rendering_Options (buffer);
			}
		}

		if ((m_contour_options & TKO_Contour_Value_Adjustment) != 0) {
			if (m_contour_value_adjustment == TKO_Contour_Adjustment_None)
				HC_Set_Rendering_Options ("contour options=no value adjustment");
			else if (m_contour_value_adjustment == TKO_Contour_Adjustment_Normalized)
				HC_Set_Rendering_Options ("contour options=value adjustment=normalized");
			else if (m_contour_value_adjustment == TKO_Contour_Adjustment_Explicit) {
				char	val[32];

				strcpy (buffer, "contour options=value adjustment=explicit=(scale=");
				write_float (val, m_contour_value_scale);
				strcat (buffer, val);
				strcat (buffer, ",translate=");
				write_float (val, m_contour_value_translate);
				strcat (buffer, val);
				strcat (buffer, ")");

				HC_Set_Rendering_Options (buffer);
			}
		}
	}

	if ((m_mask[2] & TKO_Rendo_Isoline_Options) != 0) {
		char			buffer[256];
		char			val[32];

		if ((m_isoline_options & TKO_Isoline_Positions) != 0) {
			if (m_isoline_position_type == TKO_Isoline_Positions_Default)
				HC_Set_Rendering_Options ("isoline options=positions=default");
			else if (m_isoline_position_type == TKO_Isoline_Positions_Repeat) {
				strcpy (buffer, "isoline options=positions=repeat=(interval=");
				write_float (val, m_isoline_positions[0]);
				strcat (buffer, val);
				strcat (buffer, ",offset=");
				write_float (val, m_isoline_positions[1]);
				strcat (buffer, val);
				strcat (buffer, ")");

				HC_Set_Rendering_Options (buffer);
			}
			else {
				strcpy (buffer, "isoline options=positions=explicit=(");

				for (int i=0; i<m_isoline_position_count; i++) {
					write_float (val, m_isoline_positions[i]);
					strcat (buffer, val);
					strcat (buffer, ",");
				}
				buffer[strlen(buffer)-1] = ')';

				HC_Set_Rendering_Options (buffer);
			}
		}

		if ((m_isoline_options & TKO_Isoline_Colors) != 0) {
			if (m_isoline_color_count > 0) {
				strcpy (buffer, "isoline options=colors=(");

				for (int i=0; i<m_isoline_color_count; i++) {
					if (m_isoline_colors[3*i+0] == -1.0f)
						strcat (buffer, "*,");
					else if (m_isoline_colors[3*i+0] == -2.0f)
						strcat (buffer, "-,");
					else {
						strcat (buffer, "R=");
						write_float (val, m_isoline_colors[3*i+0]);
						strcat (buffer, val);
						strcat (buffer, " G=");
						write_float (val, m_isoline_colors[3*i+1]);
						strcat (buffer, val);
						strcat (buffer, " B=");
						write_float (val, m_isoline_colors[3*i+2]);
						strcat (buffer, val);
						strcat (buffer, ",");
					}
				}
				buffer[strlen(buffer)-1] = ')';

				HC_Set_Rendering_Options (buffer);
			}
			else
				HC_Set_Rendering_Options ("isoline options=no colors");
		}

		if ((m_isoline_options & TKO_Isoline_Patterns) != 0) {
			if (m_isoline_pattern_count > 0) {
				strcpy (buffer, "isoline options=patterns=(");

				for (int i=0; i<m_isoline_pattern_count; i++) {
					strcat (buffer, m_isoline_patterns[i]);
					strcat (buffer, ",");
				}
				buffer[strlen(buffer)-1] = ')';

				HC_Set_Rendering_Options (buffer);
			}
			else
				HC_Set_Rendering_Options ("isoline options=no patterns");
		}

		if ((m_isoline_options & TKO_Isoline_Weights) != 0) {
			if (m_isoline_weight_count > 0) {
				strcpy (buffer, "isoline options=weights=(");

				for (int i=0; i<m_isoline_weight_count; i++) {
					unsigned char		units = m_isoline_weights_unit[i];

					if (units == 0xFF)
						strcat (buffer, "*,");
					else {
						write_float (val, m_isoline_weights_value[i]);
						strcat (buffer, val);
						if (units != TKO_Generic_Size_Unspecified) {
							strcat (buffer, " ");
							strcat (buffer, generic_units_table[units]);
						}
						strcat (buffer, ",");
					}
				}
				buffer[strlen(buffer)-1] = ')';

				HC_Set_Rendering_Options (buffer);
			}
			else
				HC_Set_Rendering_Options ("isoline options=no weights");
		}

		if ((m_isoline_options & TKO_Isoline_Lighting_On) != 0)
			HC_Set_Rendering_Options ("isoline options=lighting");
		else if ((m_isoline_options & TKO_Isoline_Lighting_Off) != 0)
			HC_Set_Rendering_Options ("isoline options=no lighting");
	}


	if ((m_mask[2] & TKO_Rendo_Diffuse_Color_Tint) != 0) {
		char			buffer[256];
		char			val[32];

		if ((m_tint_options & TKO_Tint_On) != 0)
			HC_Set_Rendering_Options ("diffuse color tint=on");
		else if ((m_tint_options & TKO_Tint_Off) != 0)
			HC_Set_Rendering_Options ("diffuse color tint=off");

		if ((m_tint_options & TKO_Tint_Color) != 0) {
			strcpy (buffer, "diffuse color tint=color=");

			strcat (buffer, "R=");
			write_float (val, m_tint_color[0]);
			strcat (buffer, val);
			strcat (buffer, " G=");
			write_float (val, m_tint_color[1]);
			strcat (buffer, val);
			strcat (buffer, " B=");
			write_float (val, m_tint_color[2]);
			strcat (buffer, val);

			HC_Set_Rendering_Options (buffer);
		}

		if ((m_tint_options & TKO_Tint_Range) != 0) {
			strcpy (buffer, "diffuse color tint=range=(");
			write_float (val, m_tint_range[0]);
			strcat (buffer, val);
			strcat (buffer, ",");
			write_float (val, m_tint_range[1]);
			strcat (buffer, val);
			strcat (buffer, ")");

			HC_Set_Rendering_Options (buffer);
		}

		if ((m_tint_options & TKO_Tint_Effect) != 0) {
			switch (m_tint_effect) {
				case TKO_Tint_Effect_Grayscale: {
					HC_Set_Rendering_Options ("diffuse color tint=effect=grayscale");
				}	break;
				case TKO_Tint_Effect_Modulate: {
					HC_Set_Rendering_Options ("diffuse color tint=effect=modulate");
				}	break;
				case TKO_Tint_Effect_Modulate_Gray: {
					HC_Set_Rendering_Options ("diffuse color tint=effect=modulate grayscale");
				}	break;
				case TKO_Tint_Effect_Tone: {
					HC_Set_Rendering_Options ("diffuse color tint=effect=tone");
				}	break;
			}
		}
	}



	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return status;
}

IMPLEMENT_CLONE (HTK_Rendering_Options);

////////////////////////////////////////


#define HEUR_NORMAL(bit,name)							\
	do if ((m_mask & bit) != 0) {						\
		if ((m_value & bit) != 0)                       \
			HC_Set_Heuristics (name "=on");				\
		else											\
			HC_Set_Heuristics (name "=off");			\
	} while (0)										   //

#define HEUR_LIGHTING(gbit, pbit, name)					\
	do if ((m_mask & (gbit|pbit)) != 0) {				\
		if ((m_value & gbit) != 0)						\
			HC_Set_Heuristics (name "=gouraud");		\
		else if ((m_value & pbit) != 0)					\
			HC_Set_Heuristics (name "=phong");			\
		else											\
			HC_Set_Heuristics (name "=off");			\
	} while (0)										   //

#define HEUR_VALUE(bit,name,val,fmt)					\
	do if ((m_mask & bit) != 0) {						\
		if ((m_value & bit) != 0) {						\
			char        buff[256];				\
			sprintf (buff, name "=" fmt, val);			\
			HC_Set_Heuristics (buff);					\
		}												\
		else											\
			HC_Set_Heuristics ("no " name);				\
	} while (0)										   //

static char const *weight_names[] = {
	"world volume",
	"screen extent",
	"distance",	
	"divergence",	
	"density",		
	"priority",	
};

TK_Status HTK_Heuristics::Execute (BStreamFileToolkit & tk) alter {
	HStreamFileToolkit &    htk = *(HStreamFileToolkit *)&tk;
	TK_Status               status = TK_Normal;     // assume success

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	HEUR_NORMAL (TKO_Heuristic_Hidden_Surfaces,         "hidden surfaces");
	HEUR_NORMAL (TKO_Heuristic_Backplane_Cull,          "backplane cull");
	HEUR_NORMAL (TKO_Heuristic_Partial_Erase,           "partial erase");
	HEUR_NORMAL (TKO_Heuristic_Memory_Purge,            "memory purge");
	HEUR_NORMAL (TKO_Heuristic_Clipping,                "clipping");
	HEUR_NORMAL (TKO_Heuristic_Transformations,         "transformations");
	HEUR_NORMAL (TKO_Heuristic_Intersecting_Polygons,   "intersecting polygons");
	HEUR_NORMAL (TKO_Heuristic_Polygon_Crossings,       "polygon crossings");
	HEUR_NORMAL (TKO_Heuristic_Concave_Polygons,        "concave polygons");
	HEUR_NORMAL (TKO_Heuristic_Incremental_Updates,     "incremental updates");

	if ((m_mask & TKO_Heuristic_Polygon_Handedness) != 0) {
		if ((m_value & TKO_Heuristic_Polygon_Handedness) == 0)
			HC_Set_Heuristics ("no polygon handedness");
		else if ((m_extras & TKO_Heur_Extra_Left_Handed_Polys) != 0)
			HC_Set_Heuristics ("polygon handedness=left");
		else
			HC_Set_Heuristics ("polygon handedness=right");
	}

	if ((m_mask & TKO_Heuristic_Quick_Moves) != 0) {
		if ((m_value & TKO_Heuristic_Quick_Moves) == 0)
			HC_Set_Heuristics ("no quick moves");
		else if ((m_extras & TKO_Heur_Extra_Quick_Move_Spriting) != 0)
			HC_Set_Heuristics ("quick moves=spriting");
		else
			HC_Set_Heuristics ("quick moves");
	}

	HEUR_VALUE (TKO_Heuristic_Related_Select_Limit,  "related selection limit",  m_related,  "%d");

	if (m_mask & TKO_Heuristic_Internal_Shell_Limit) {
		if (m_value & TKO_Heuristic_Internal_Shell_Limit) {
			char			tmp[64];

			sprintf (tmp, "internal selection limit=shell=%d", GetInternalShellSelectionLimit());
			HC_Set_Heuristics(tmp);
		}
		else
			HC_Set_Heuristics ("internal selection limit=no shell");
	}
	if (m_mask & TKO_Heuristic_Internal_Polyline_Limit) {
		if (m_value & TKO_Heuristic_Internal_Polyline_Limit) {
			char			tmp[64];

			sprintf (tmp, "internal selection limit=polyline=%d", GetInternalPolylineSelectionLimit());
			HC_Set_Heuristics(tmp);
		}
		else
			HC_Set_Heuristics ("internal selection limit=no polyline");
	}

	if (htk.GetHoopsVersion() >= 660) {
		HEUR_NORMAL (TKO_Heuristic_Selection_Sorting,       "selection sorting");
	}

	if (htk.GetHoopsVersion() >= 750) {
		if (m_mask & TKO_Heuristic_Culling) {
			if (m_value & TKO_Heuristic_Culling) {
				if ((m_culling & TKO_Heur_View_Frustum_Culling) != 0)
					HC_Set_Heuristics ("culling=view frustum");
				else if ((m_culling & TKO_Heur_View_Frustum_Culling_Off) != 0)
					HC_Set_Heuristics ("culling=no view frustum");

				if (htk.GetHoopsVersion() >= 950) {
					if ((m_culling & TKO_Heur_Obscuration_Culling) != 0) {
						if ((GetPixelThreshold() > 0 || (m_culling & TKO_Heur_Obscuration_Use_Octree)) &&
							htk.GetHoopsVersion() >= 1450) {
							char			tmp[64];

							sprintf (tmp, "culling=obscuration=(pixel threshold=%d, %s)", GetPixelThreshold(),
									 (m_culling & TKO_Heur_Obscuration_Use_Octree) ?
									  "use octree" : "no use octree");
							HC_Set_Heuristics(tmp);
						}
						else if (GetPixelThreshold() > 0 && htk.GetHoopsVersion() >= 1150) {
							char			tmp[64];

							sprintf (tmp, "culling=obscuration=pixel threshold=%d", GetPixelThreshold());
							HC_Set_Heuristics(tmp);
						}
						else
							HC_Set_Heuristics ("culling=obscuration");
					}
					else if ((m_culling & TKO_Heur_Obscuration_Culling_Off) != 0)
						HC_Set_Heuristics ("culling=no obscuration");

					if (htk.GetHoopsVersion() >= 1250) {
						if ((m_culling & TKO_Heur_Extent_Culling) != 0) {
							char			tmp[64];

							sprintf (tmp, "culling=maximum extent=%d", GetMaximumExtent());
							HC_Set_Heuristics (tmp);
						}
						else if ((m_culling & TKO_Heur_Extent_Culling_Off) != 0)
							HC_Set_Heuristics ("culling=no maximum extent");

						if ((m_culling & TKO_Heur_Maximum_Extent_Mode) != 0) {
							switch (GetMaximumExtentMode()) {
								case TKO_Heur_Max_Extent_Mode_None:	HC_Set_Heuristics("culling=maximum extent mode=none"); break;
								case TKO_Heur_Max_Extent_Mode_Dot: HC_Set_Heuristics("culling=maximum extent mode=dot"); break;
								case TKO_Heur_Max_Extent_Mode_Bounding: HC_Set_Heuristics("culling=maximum extent mode=bounding"); break;
								case TKO_Heur_Max_Extent_Mode_Defer: HC_Set_Heuristics("culling=maximum extent mode=defer"); break;
							}
						}
					}

					if (htk.GetHoopsVersion() >= 1550) {
						if ((m_culling & TKO_Heur_Vector_Culling) != 0) {
							char			tmp[128];
							char			val[32];
							float const *	vec;

							vec = GetVector();
							sprintf(tmp, "culling=vector=(");
							write_float(val, vec[0]);
							strcat(tmp, val);
							strcat(tmp, ",");
							write_float(val, vec[1]);
							strcat(tmp, val);
							strcat(tmp, ",");
							write_float(val, vec[2]);
							strcat(tmp, val);
							strcat(tmp, ")");

							HC_Set_Heuristics(tmp);
						}
						else if ((m_culling & TKO_Heur_Vector_Culling_Off) != 0)
							HC_Set_Heuristics("culling=no vector");

						if ((m_culling & TKO_Heur_Vector_Tolerance) != 0) {
							char			tmp[64];
							char			val[32];

							sprintf(tmp, "culling=vector tolerance=");
							write_float(val, GetVectorTolerance());
							strcat(tmp, val);
							
							HC_Set_Heuristics(tmp);
						}
						else if ((m_culling & TKO_Heur_Vector_Tolerance_Off) != 0)
							HC_Set_Heuristics("culling=no vector tolerance");
					}

					if (htk.GetHoopsVersion() >= 1750) {
						if ((m_culling & TKO_Heur_Hard_Extent_Culling) != 0) {
							char			tmp[64] = {""};

							sprintf (tmp, "culling=hard extent=%d", GetHardExtent());
							HC_Set_Heuristics (tmp);
						}
						else if ((m_culling & TKO_Heur_Extent_Culling_Off) != 0)
							HC_Set_Heuristics ("culling=no hard extent");

						if ((m_culling & TKO_Heur_Maximum_Extent_Level) != 0) {
							// lazy enumeration of cases...
							switch (GetMaximumExtentLevel()) {
								case TKO_Heur_Max_Extent_Level_None:
									HC_Set_Heuristics("culling=maximum extent level=none");
									break;
								case TKO_Heur_Max_Extent_Level_Segment:
									HC_Set_Heuristics("culling=maximum extent level=segment");
									break;
								case TKO_Heur_Max_Extent_Level_Geometry:
									HC_Set_Heuristics("culling=maximum extent level=geometry");
									break;
								case TKO_Heur_Max_Extent_Level_Primitive:
									HC_Set_Heuristics("culling=maximum extent level=primitive");
									break;
								case TKO_Heur_Max_Extent_Level_Segment|TKO_Heur_Max_Extent_Level_Geometry:
									HC_Set_Heuristics("culling=maximum extent level=(segment,geometry)");
									break;
								case TKO_Heur_Max_Extent_Level_Segment|TKO_Heur_Max_Extent_Level_Primitive:
									HC_Set_Heuristics("culling=maximum extent level=(segment,primitive)");
									break;
								case TKO_Heur_Max_Extent_Level_Geometry|TKO_Heur_Max_Extent_Level_Primitive:
									HC_Set_Heuristics("culling=maximum extent level=(geometry,primitive)");
									break;
								case TKO_Heur_Max_Extent_Level_All:
									HC_Set_Heuristics("culling=maximum extent level=default");
									break;
							}
						}
					}
				}
			}
			else
				HC_Set_Heuristics ("no culling");
		}
	}

	if (htk.GetHoopsVersion() >= 1050) {
		HEUR_NORMAL (TKO_Heuristic_Exclude_Bounding,	"exclude bounding");
	}
	if (htk.GetHoopsVersion() >= 1320) {
		HEUR_NORMAL (TKO_Heuristic_Detail_Selection,	"detail selection");
	}

    if (htk.GetHoopsVersion() >= 1450) {
		if (m_mask & m_value & TKO_Heuristic_Ordered_Unit)
			HC_Set_Heuristics ("ordered drawing=unit");
		else if (m_mask & m_value & TKO_Heuristic_Ordered_Grid)
			HC_Set_Heuristics ("ordered drawing=grid");
		else
		{

	        HEUR_NORMAL (TKO_Heuristic_Ordered_Drawing,		"ordered drawing");

		}

		if (m_mask & TKO_Heuristic_Ordered_Weights) {
			int			i;

			for (i=0; i<TKO_Heur_Order_Count; i++) {
				if (m_ordered_weights_mask & (1 << i)) {
					char		string[80];
					char		variable[16];

					write_float (variable, m_ordered_weights[i]);
					sprintf (string, "ordered weights=%s=%s", weight_names[i], variable);
					HC_Set_Heuristics (string);
				}
			}
		}
    }

	if (htk.GetHoopsVersion() >= 1550) {
		HEUR_NORMAL (TKO_Heuristic_Static,	"static model");

		if ((m_mask & TKO_Heuristic_Selection_Level) != 0) {
			switch (m_selection_level) {
				case TKO_Heur_Selection_Level_Entity:
								HC_Set_Heuristics ("selection level=entity");         break;
				case TKO_Heur_Selection_Level_Segment:
								HC_Set_Heuristics ("selection level=segment");        break;
				case TKO_Heur_Selection_Level_Segment_Tree:
								HC_Set_Heuristics ("selection level=segment tree");   break;
			}
		}
	}

	if (htk.GetHoopsVersion() >= 1750) {
		HEUR_VALUE (TKO_Heuristic_Force_Defer,  "force defer batch",  m_force_defer,  "%d");

		if ((m_mask & TKO_Heuristic_Model_Type) != 0) {
			switch (m_model_type) {
				case TKO_Heur_Model_Type_Default:
								HC_Set_Heuristics ("model type=default");		break;
				case TKO_Heur_Model_Type_LMV:
								HC_Set_Heuristics ("model type=lmv");			break;
			}
		}
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return status;
}

IMPLEMENT_CLONE (HTK_Heuristics);

////////////////////////////////////////

TK_Status HTK_Geometry_Options::Execute (BStreamFileToolkit & tk) alter {
	TK_Status               status = TK_Normal;     // assume success
	HC_KEY					key = -1;

	if ((status = tk.GetLastKey(key)) != TK_Normal)
		return status;

	if ((m_mask & TKO_Geometry_Options_Orientation) != 0) {
		char        buffer[128];
		char        val[32];

		strcpy (buffer, "orientation=(");
		for (int i=0; i<(int)m_orientation_count; i++) {
			write_float (val, m_orientation[i]);
			strcat (buffer, val);
			strcat (buffer, ",");
		}
		buffer[strlen(buffer)-1] = ')';
		HC_Set_Geometry_Options (key, buffer);
	}

	if ((m_mask & TKO_Geometry_Options_Camera_Relative) != 0) {
		if (m_value & TKO_Geometry_Options_Camera_Relative)
			HC_Set_Geometry_Options (key, "camera relative");
		else
			HC_Set_Geometry_Options (key, "no camera relative");
	}

	return status;
}

IMPLEMENT_CLONE (HTK_Geometry_Options);

////////////////////////////////////////


#define DO_VISIBILITY(bit,name)					\
	do if ((m_mask & bit) != 0) {				\
		if ((m_value & bit) != 0)				\
			HC_Set_Visibility (name "=on");		\
		else									\
			HC_Set_Visibility (name "=off");	\
	} while (0)								   //

#ifdef DEBUG
//if you get a compile error at the following line, that means that HTK_Visibility::Execute
//   needs some maintenance to make sure that "all" doesn't get expanded into its components.
static const int force_error_if_all_changes[TKO_Geo_All_Visibles==0x037FFF7F];
#endif

TK_Status HTK_Visibility::Execute (BStreamFileToolkit & tk) alter {
	HStreamFileToolkit &    htk = *(HStreamFileToolkit *)&tk;
	TK_Status               status = TK_Normal;     // assume success
	int                     all, version;

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	version = tk.GetVersion();
	all = TKO_Geo_All_Visibles;

	if (version < 800)
		all &= 0x000FFFFF;
	if (version < 1205)
		all &= 0x002FFFFF;
	if (version < 1305)
		all &= 0x007FFFFF;
	if (version < 1320)
		all &= 0x01FFFFFF;

	if ((m_mask & all) == all &&
		((m_value & all) == all || m_value == 0)) {
		if (m_value == 0)
			HC_Set_Visibility ("off");
		else
			HC_Set_Visibility ("on");
	}

	if ((m_mask & all) == all &&
		((m_value & all) == all || m_value == 0)) {
		if (m_value == 0)
			HC_Set_Visibility ("off");
		else
			HC_Set_Visibility ("on");
	}
	else {
		DO_VISIBILITY (TKO_Geo_Face,                "faces");
		DO_VISIBILITY (TKO_Geo_Edge,                "edges");
		DO_VISIBILITY (TKO_Geo_Line,                "lines");
		if (htk.GetHoopsVersion() >= 750) {
			if (htk.GetVersion() >= 705) {
				DO_VISIBILITY (TKO_Geo_Marker,          "markers only");
				DO_VISIBILITY (TKO_Geo_Vertex_Vis,      "vertices");
			}
			else
				DO_VISIBILITY (TKO_Geo_Marker,          "markers");
		}
		else
			DO_VISIBILITY (TKO_Geo_Marker,          "markers");
		DO_VISIBILITY (TKO_Geo_Text,                "text");
		DO_VISIBILITY (TKO_Geo_Window,              "window");
		DO_VISIBILITY (TKO_Geo_Image,               "images");

		DO_VISIBILITY (TKO_Geo_String_Cursor,       "string cursors");
		DO_VISIBILITY (TKO_Geo_Face_Lighting,       "lighting=faces");
		DO_VISIBILITY (TKO_Geo_Edge_Lighting,       "lighting=edges");
		DO_VISIBILITY (TKO_Geo_Marker_Lighting,     "lighting=markers");
		DO_VISIBILITY (TKO_Geo_Silhouette_Edge,     "edges=interior silhouettes");
		DO_VISIBILITY (TKO_Geo_NonCulled_Edge,      "edges=nonculled");
		DO_VISIBILITY (TKO_Geo_Perimeter_Edge,      "edges=perimeters");
		DO_VISIBILITY (TKO_Geo_Mesh_Quad,           "edges=mesh quads");
		DO_VISIBILITY (TKO_Geo_Hard_Edge,           "edges=hard");
		DO_VISIBILITY (TKO_Geo_Cutting_Plane,       "cutting planes");

		if (htk.GetHoopsVersion() >= 1250)
			DO_VISIBILITY (TKO_Geo_Adjacent_Edge,      "edges=adjacent");

		if (htk.GetHoopsVersion() >= 850) {
			DO_VISIBILITY (TKO_Geo_Cut_Edge,            "cut geometry=edges");
			DO_VISIBILITY (TKO_Geo_Cut_Face,            "cut geometry=faces");
		}
		else
			DO_VISIBILITY (TKO_Geo_Cut_Edge,            "cut edges");

		DO_VISIBILITY (TKO_Geo_Shadow_Emit,         "shadows=emitting");
		DO_VISIBILITY (TKO_Geo_Shadow_Cast,         "shadows=casting");
		DO_VISIBILITY (TKO_Geo_Shadow_Receive,      "shadows=receiving");
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return status;
}

// TK_Visibility::Interpret() currently in parse.cpp

IMPLEMENT_CLONE (HTK_Visibility);

////////////////////////////////////////


#define DO_SELECTABILITY(bit,name)                  \
	do if ((m_mask & bit) != 0) {                   \
		if ((composite & bit) == 0)                 \
			HC_Set_Selectability (name "=off");     \
		else {                                      \
			char        buffer[64];         \
													\
			sprintf (buffer, "%s=", name);          \
			if ((m_down & bit) != 0)                \
				strcat (buffer, "v");               \
			if ((m_up & bit) != 0)                  \
				strcat (buffer, "^");               \
			if ((m_move_down & bit) != 0)           \
				strcat (buffer, "*");               \
			if ((m_move_up & bit) != 0)             \
				strcat (buffer, "O");               \
			if ((m_invisible & bit) != 0)           \
				strcat (buffer, "!");               \
			HC_Set_Selectability (buffer);          \
		}                                           \
	} while (0)                                    //

TK_Status HTK_Selectability::Execute (BStreamFileToolkit & tk) alter {
	HStreamFileToolkit &    htk = *(HStreamFileToolkit *)&tk;
	TK_Status               status = TK_Normal;     // assume success
	int                     composite = m_down | m_up | m_move_down | m_move_up;

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	DO_SELECTABILITY (TKO_Geo_Face,             "faces");
	DO_SELECTABILITY (TKO_Geo_Edge,             "edges");
	DO_SELECTABILITY (TKO_Geo_Line,             "lines");
	if (htk.GetHoopsVersion() >= 750) {
		DO_SELECTABILITY (TKO_Geo_Marker,       "markers only");
		DO_SELECTABILITY (TKO_Geo_Vertex,       "vertices");
	}
	else
		DO_SELECTABILITY (TKO_Geo_Marker,       "markers");
	DO_SELECTABILITY (TKO_Geo_Text,             "text");
	DO_SELECTABILITY (TKO_Geo_Window,           "window");
	DO_SELECTABILITY (TKO_Geo_Image,            "images");

	DO_SELECTABILITY (TKO_Geo_String_Cursor,    "string cursors");
	DO_SELECTABILITY (TKO_Geo_Light,            "lights");

	DO_SELECTABILITY (TKO_Geo_Isoline,			"isolines");

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return status;
}

// TK_Selectability::Interpret() currently in parse.cpp

IMPLEMENT_CLONE (HTK_Selectability);

////////////////////////////////////////

TK_Status HTK_Matrix::Execute (BStreamFileToolkit & tk) alter {
	TK_Status       status = TK_Normal;     // assume success

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	switch (Opcode()) {
		case TKE_Modelling_Matrix:
			HC_Set_Modelling_Matrix (m_matrix);
			break;

		case TKE_Texture_Matrix:
			HC_Set_Texture_Matrix (m_matrix);
			break;

		default:
			status = tk.Error("unknown matrix type");
			break;
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return status;
}

TK_Status HTK_Matrix::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;     // assume success

	switch (Opcode()) {
		case TKE_Modelling_Matrix:
			HC_Show_Modelling_Matrix (m_matrix);
			break;

		case TKE_Texture_Matrix:
			HC_Show_Texture_Matrix (m_matrix);
			break;

		default:
			status = tk.Error("unknown matrix type");
			break;
	}

	return status;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE_OPCODE (HTK_Matrix);

////////////////////////////////////////


TK_Status HTK_Size::Execute (BStreamFileToolkit & tk) alter {
	TK_Status       status = TK_Normal;     // assume success
	char            variable[64];

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	if (m_units != TKO_Generic_Size_Unspecified) {
		write_float (variable, m_value);
		strcat (variable, " ");
		strcat (variable, generic_units_table[m_units]);
	}
	else
		variable[0] = '\0';

	switch (Opcode()) {
		case TKE_Edge_Weight:
			if (m_units == TKO_Generic_Size_Unspecified)
				HC_Set_Edge_Weight (m_value);
			else
				HC_Set_Variable_Edge_Weight (variable);
			break;

		case TKE_Line_Weight:
			if (m_units == TKO_Generic_Size_Unspecified)
				HC_Set_Line_Weight (m_value);
			else
				HC_Set_Variable_Line_Weight (variable);
			break;

		case TKE_Marker_Size:
			if (m_units == TKO_Generic_Size_Unspecified)
				HC_Set_Marker_Size (m_value);
			else
				HC_Set_Variable_Marker_Size (variable);
			break;


		case TKE_Text_Spacing:
			if (tk.GeometryIsOpen()) {
				HC_KEY					last_key;

				if ((status = tk.GetLastKey(last_key)) != TK_Normal)
					return status;
				HC_Open_Geometry (last_key);
			}

			HC_Set_Text_Spacing (m_value);

			if (tk.GeometryIsOpen())
				HC_Close_Geometry ();
			break;

		default:
			status = tk.Error();
			break;
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return status;
}

TK_Status HTK_Size::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;     // assume success
	float           value;
	int             units = TKO_Generic_Size_Unspecified;
	char            variable[64];

	variable[0] = '\0';
	switch (Opcode()) {
		case TKE_Edge_Weight:
			HC_Show_Edge_Weight (&value);
			if (value < 0.0f)
				HC_Show_Variable_Edge_Weight (variable);
			break;

		case TKE_Line_Weight:
			HC_Show_Line_Weight (&value);
			if (value < 0.0f)
				HC_Show_Variable_Line_Weight (variable);
			break;

		case TKE_Marker_Size:
			HC_Show_Marker_Size (&value);
			if (value < 0.0f)
				HC_Show_Variable_Marker_Size (variable);
			break;

		case TKE_Text_Spacing:
			HC_Show_Text_Spacing (&value);
			break;

		default:
			return tk.Error();
	}

	if (value < 0.0f && Opcode() != TKE_Text_Spacing) {
		char const *    cp = variable;
		int             ii;

		value = read_float (cp);

		while (*cp != ' ') {
			if (!*cp++)
				return tk.Error("can't parse size units");
		}
		while (*cp == ' ') ++cp;

		for (ii=0; ii<countof(generic_units_table); ++ii) {
			if (streq (cp, generic_units_table[ii])) {
				units = ii;
				break;
			}
		}

		if (units == TKO_Generic_Size_Unspecified)
			return tk.Error("can't parse size units");
	}

	SetSize (value, units);

	return status;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE_OPCODE (HTK_Size);

////////////////////////////////////////

TK_Status HTK_Conditions::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);

	HC_Set_Conditions (m_string);

	return TK_Normal;
}

TK_Status HTK_Conditions::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char		string[4096];

	UNREFERENCED (tk);

	HC_Show_Conditions (string);
	SetConditions (string);

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Conditions);

////////////////////////////////////////

TK_Status HTK_Conditional_Action::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);
	char				action[256];

	action[0] = '\0';

	switch (m_type) {
		case TKO_Action_Type_Prune_Segment:		strcpy (action, "prune segment");
	}

	if (m_options != 0) {
		strcat (action, "=(");
		if ((m_options & TKO_Action_Option_Segment_Tree) != 0)
			strcat (action, "segment tree,");
		action[strlen(action)-1] = ')';
	}

	HC_Set_Conditional_Action (action, m_string);

	return TK_Normal;
}

TK_Status HTK_Conditional_Action::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
	return tk.Error();    // contents generated as part of HTK_Conditional_Actions::Interpret()
}

IMPLEMENT_CLONE (HTK_Conditional_Action);

////////////////////////////////////////////////////////////////////////////////
// pseudo-object used to hold several color pieces, output only

HTK_Conditional_Actions::HTK_Conditional_Actions ()
	: BBaseOpcodeHandler (TKE_Pseudo_Handler) {
	int			i;

	for (i = 0; i < 16; ++i)
		m_parts[i] = null;
}

HTK_Conditional_Actions::~HTK_Conditional_Actions () {
	int			i;

	for (i = 0; i < 16; ++i)
		delete m_parts[i];
}

TK_Status HTK_Conditional_Actions::Write (BStreamFileToolkit & tk) alter {
#ifndef HSTREAM_READONLY
	TK_Status		status = TK_Normal;

	while (m_parts[m_stage] != null) {
		if ((status = m_parts[m_stage]->Write (tk)) != TK_Normal)
			return status;
		adjust_written (tk, -1);    // don't count the subpiece
		++m_stage;
	}
	adjust_written (tk, 1);         // now count the whole set of colors
	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}


TK_Status HTK_Conditional_Actions::Read (BStreamFileToolkit & tk) alter {
	return tk.Error();
}
TK_Status HTK_Conditional_Actions::Execute (BStreamFileToolkit & tk) alter {
	return tk.Error();
}

TK_Status HTK_Conditional_Actions::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	int							num_parts = 0;
	char						types[256];
	char						options[256];
	char						condition[1024];
	char *						tp;

	HC_Show_Conditional_Action_Types (types);
	tp = types;
	while (tp != null && *tp != '\0') {
		TK_Status				status;
		status = tk.GetOpcodeHandler(TKE_Conditional_Action)->Clone(tk, &m_parts[num_parts]);
		if (status != TK_Normal)
			return status;
		TK_Conditional_Action *	ca = (TK_Conditional_Action *)m_parts[num_parts++];
		char *					comma = strchr (tp, ',');

		if (comma != null)
			*comma = '\0';

		if (streq (tp, "prune segment"))
			ca->SetAction (TKO_Action_Type_Prune_Segment);

		HC_Show_One_Conditional_Action (tp, options, condition);

		char const *			op = options;
		int						flags = 0;
		while (*op != '\0') {
			if (streqn (op, "segment tree", 12)) {
				flags |= TKO_Action_Option_Segment_Tree;
				op += 12;
			}
			else if (streqn (op, "segment", 7))
				op += 7;

			if (*op == ',')
				++op;
		}
		ca->SetOptions (flags);

		ca->SetCondition (condition);

		if ((tp = comma) != null)
			++tp;
	}

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Conditional_Actions);

////////////////////////////////////////

TK_Status HTK_User_Options::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;
		TK_Status				status;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	HC_Set_User_Options (m_string);

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return TK_Normal;
}

TK_Status HTK_User_Options::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char *          string;
	int				length;
	int             index_count;
	char            sysop[64];
	char            value[64];


	HC_Show_One_System_Option ("C string length", value);
	if (streq (value, "off"))
		strcpy (sysop, "no C string length");
	else
		sprintf (sysop, "C string Length=%s", value);
	HC_Define_System_Options ("C string Length=16777216");  // big enough?

	HC_Show_User_Options_Length (&length);
	string = new char [length+1];
	HC_Show_User_Options (string);
	SetOptions (string);
	delete [] string;


	// these are connected to user_options in Hoops, but generate separate file entries
	m_unicode = tk.GetOpcodeHandler (TKE_Unicode_Options);
	m_unicode->Interpret (tk, key);
	if (((TK_Unicode_Options *)m_unicode)->GetLength() == 0) {
		m_unicode->Reset();
		m_unicode = null;
	}

	HC_Show_User_Index_Count (&index_count);
	if (index_count > 0) {
		m_indices = tk.GetOpcodeHandler (TKE_User_Index);
		m_indices->Interpret (tk, key);
	}

	int data_count = -HC_Show_User_Data_Indices(0, 0);
	if (data_count > 0) {
		m_index_data = tk.GetOpcodeHandler(TKE_User_Index_Data);
		m_index_data->Interpret (tk, key);
	}

	HC_Define_System_Options (sysop);	// restore (here -- override affects unicode handling too!)

	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_User_Options);

////////////////////////////////////////

TK_Status HTK_Unicode_Options::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;
		TK_Status				status;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	HC_Set_Unicode_Options (m_string);

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return TK_Normal;
}

TK_Status HTK_Unicode_Options::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	unsigned short *string;
	int		length;

	UNREFERENCED (tk);

	HC_Show_Unicode_Options_Length (&length);
	string = new unsigned short [length+1];
	HC_Show_Unicode_Options (string);
	SetOptions (string);
	delete [] string;

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Unicode_Options);

////////////////////////////////////////

TK_Status HTK_User_Index::Execute (BStreamFileToolkit & tk) alter {
	int             i;

	UNREFERENCED (tk);

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;
		TK_Status				status;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	for (i = 0; i < m_count; ++i) {
		HC_Set_User_Index (m_indices[i], SL2VP(m_values[i]));
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return TK_Normal;
}

TK_Status HTK_User_Index::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	UNREFERENCED (tk);

	// ugly -- our key/value pairs are int/long, Hoops uses long/pointer, and 64-bit implementations
	// can mismatch int:long and long:pointer in different combinations, so make locals and copy as necessary
	// note that the read/write functions handle the case for truncating values (long) > 4 bytes
	long *		indices;
	void **		values;

	HC_Show_User_Index_Count (&m_count);
	set_indices (m_count);   // allocate space

	if (sizeof(long) != sizeof(int))
		indices = new long  [m_count];
	else
		indices = (long *)m_indices;

	if (sizeof(void *) != sizeof(long))
		values = new void * [m_count];
	else
		values = (void **)m_values;

	HC_Show_User_Indices (&m_count, indices, values);

	if (sizeof(long) != sizeof(int)) {
		for (int i=0; i<m_count; i++)
			m_indices[i] = (long)indices[i];

		delete [] indices;
	}

	if (sizeof(void *) != sizeof(long)) {
		for (int i=0; i<m_count; i++)
			m_values[i] = VP2SL (values[i]);

		delete [] values;
	}

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_User_Index);

////////////////////////////////////////

TK_Status HTK_User_Index_Data::Execute (BStreamFileToolkit & tk) alter {
	int             i;

	UNREFERENCED (tk);

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;
		TK_Status				status;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	for (i = 0; i < m_count; ++i) {
		HC_Set_User_Data (m_indices[i], m_values[i], m_sizes[i]);
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return TK_Normal;
}

TK_Status HTK_User_Index_Data::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	UNREFERENCED (tk);

	int m_count = -HC_Show_User_Data_Indices (0, 0);

	set_indices (m_count);   // allocate space

	if (sizeof(POINTER_SIZED_INT) == sizeof(int))
		HC_Show_User_Data_Indices ((POINTER_SIZED_INT*)m_indices, m_count);
	else {
		POINTER_SIZED_INT * indices = new POINTER_SIZED_INT[m_count];
		HC_Show_User_Data_Indices (indices, m_count);
		for(int i = 0; i < m_count; ++i) {
			m_indices[i] = (int)indices[i];
		}
		delete [] indices;
	}

	for(int i = 0; i < m_count; ++i) {
		m_sizes[i] = -HC_Show_One_User_Data(m_indices[i], 0, 0);
		m_values[i] = new unsigned char[m_sizes[i]];
		HC_Show_One_User_Data(m_indices[i], m_values[i], m_sizes[i]);
	}

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_User_Index_Data);

////////////////////////////////////////


TK_Status HTK_User_Value::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;
		TK_Status				status;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	HC_Set_User_Value (m_value);

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return TK_Normal;
}

TK_Status HTK_User_Value::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	HC_POINTER_SIZED_INT temp;

	UNREFERENCED (tk);

	HC_Show_User_Value (&temp);
	m_value = (long)temp;

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_User_Value);

////////////////////////////////////////


TK_Status HTK_Camera::Execute (BStreamFileToolkit & tk) alter {
	char            projection[64];

	if (Opcode() == TKE_View)
		return TK_Normal;       // HOOPS doesn't handle views by default

	projection[0] = '\0';
	if ((m_projection & TKO_Camera_Oblique_Mask) != 0)
		strcat (projection, "oblique ");
	switch (m_projection & TKO_Camera_Projection_Mask) {
		case TKO_Camera_Orthographic:       strcat (projection, "orthographic");        break;
		case TKO_Camera_Perspective:        strcat (projection, "perspective");         break;
		case TKO_Camera_Stretched:          strcat (projection, "stretched");           break;
		default:                            return tk.Error();
	}
	if ((m_projection & TKO_Camera_Oblique_Mask) != 0) {
		char            values[64];
		char            v1[32], v2[32];

		write_float (v1, m_settings[11]);
		if ((m_projection & TKO_Camera_Oblique_X) != 0) {
			write_float (v2, m_settings[12]);
			sprintf (values, "=(%s,%s)", v1,v2);
		}
		else
			sprintf (values, "=%s", v1);
		strcat (projection, values);
	}

	HC_Set_Camera (&m_settings[0], &m_settings[3], &m_settings[6], m_settings[9], m_settings[10], projection);

	if (m_settings[13] != 0.0f)
		HC_Set_Camera_Near_Limit (m_settings[13]);

	return TK_Normal;
}

TK_Status HTK_Camera::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            projection[64];
	char const *    pp = projection;
	int				limit_set;	// more-or-less bool but as a C return from HOOPS

	// allow interpret to work even if a "view", makes generation of a view from a HOOPS camera fairly simple

	HC_Show_Camera (&m_settings[0], &m_settings[3], &m_settings[6], &m_settings[9], &m_settings[10], projection);
	limit_set = HC_Show_Camera_Near_Limit (&m_settings[13]);

	m_projection = 0;
	if (streqn (pp, "oblique ", 8)) {
		m_projection |= TKO_Camera_Oblique_Y;
		pp += 8;
	}
	switch (*pp) {
		case 'o':   m_projection |= TKO_Camera_Orthographic;        pp += 12;       break;
		case 'p':   m_projection |= TKO_Camera_Perspective;         pp += 11;       break;
		case 's':   m_projection |= TKO_Camera_Stretched;           pp +=  9;       break;
		default:    return tk.Error();
	}
	if ((m_projection & TKO_Camera_Oblique_Mask) != 0) {
		++pp;       // skip '='
		if (*pp == '(') {
			m_projection |= TKO_Camera_Oblique_X;
			++pp;
		}

		m_settings[11] = read_float (pp);

		if ((m_projection & TKO_Camera_Oblique_X) != 0) {
			while (*pp++ != ',') {}
			m_settings[12] = read_float (pp);
			//while (*pp++ != ')') {}
		}
	}

	if (limit_set)
		m_projection |= TKO_Camera_Near_Limit;

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Camera);

////////////////////////////////////////


TK_Status HTK_Window::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);

	HC_Set_Window (m_window[0], m_window[1], m_window[2], m_window[3]);

	return TK_Normal;
}

TK_Status HTK_Window::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	UNREFERENCED (tk);

	HC_Show_Window (&m_window[0], &m_window[1], &m_window[2], &m_window[3]);

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Window);

////////////////////////////////////////


TK_Status HTK_Clip_Region::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);

	char	options[128], *end;

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;
		TK_Status				status;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	end = options;
	options[0] = '\0';

	if (GetOptions() & TKO_Clip_Region_Window_Space) {
		sprintf(end, "window,");
		end += strlen("window,");
	}
	else if (GetOptions() & TKO_Clip_Region_World_Space) {
		sprintf(end, "world,");
		end += strlen("world,");
	}
	if (GetOptions() & TKO_Clip_Region_Clip) {
		sprintf(end, "type=clip,");
		end += strlen("type=clip,");
	}
	else if (GetOptions() & TKO_Clip_Region_Mask) {
		sprintf(end, "type=mask,");
		end += strlen("type=mask,");
	}

	if (end != options)
		*--end = '\0';


	HC_Set_Polygonal_Clip_Region (GetCount(), GetPoints(), options);

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return TK_Normal;
}

TK_Status HTK_Clip_Region::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	int             loops, count;
	char            space[64];

	HC_Show_Clip_Region_Size (&loops, &count, space);

	if (loops > 1)
		return tk.Error ("can only handle simple polygonal clips");

	SetPoints (count);  // allocate space

	HC_Show_Clip_Region (&loops, &count, GetPoints(), space);

	if (strstr (space, "world"))
		SetOptions (GetOptions() | TKO_Clip_Region_World_Space);

	if (strstr (space, "window"))
		SetOptions (GetOptions() | TKO_Clip_Region_Window_Space);

	if (strstr (space, "clip"))
		SetOptions (GetOptions() | TKO_Clip_Region_Clip);

	if (strstr (space, "mask"))
		SetOptions (GetOptions() | TKO_Clip_Region_Mask);

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Clip_Region);

////////////////////////////////////////


TK_Status HTK_Clip_Rectangle::Execute (BStreamFileToolkit & tk) alter {
	float					box[12];

	UNREFERENCED (tk);

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;
		TK_Status				status;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	box[0] = m_rect[0];		box[1]  = m_rect[2];	box[2]  = 0.0f;
	box[3] = m_rect[0];		box[4]  = m_rect[3];	box[5]  = 0.0f;
	box[6] = m_rect[1];		box[7]  = m_rect[3];	box[8]  = 0.0f;
	box[9] = m_rect[1];		box[10] = m_rect[2];	box[11] = 0.0f;

	HC_Set_Polygonal_Clip_Region (4, box,
								  (GetOptions() && TKO_Clip_Region_Window_Space) ? "world space" : "");

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return TK_Normal;
}

IMPLEMENT_CLONE (HTK_Clip_Rectangle);

////////////////////////////////////////


TK_Status HTK_Text_Font::Execute (BStreamFileToolkit & tk) alter {
	HStreamFileToolkit &    htk = *(HStreamFileToolkit *)&tk;
	char                    buffer[4096];
	char                    number[32];

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;
		TK_Status				status;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

	if ((m_mask & m_value & TKO_Font_Names) != 0) {
		sprintf (buffer, "name=(%s)", m_names);
		HC_Set_Text_Font (buffer);
	}
	if ((m_mask & m_value & TKO_Font_Size) != 0) {
		write_float (number, m_size);
		sprintf (buffer, "size=%s %s", number, generic_units_table[m_size_units]);
		HC_Set_Text_Font (buffer);
	}
	if ((m_mask & m_value & TKO_Font_Size_Tolerance) != 0) {
		write_float (number, m_tolerance);
		sprintf (buffer, "size tolerance=%s %s", number, generic_units_table[m_tolerance_units]);
		HC_Set_Text_Font (buffer);
	}
	if ((m_mask & TKO_Font_Transforms) != 0) {
		if ((m_value & TKO_Font_Transforms) == 0)
			HC_Set_Text_Font ("no transforms");
		else if (m_transforms == TKO_Font_Transform_Full)
			HC_Set_Text_Font ("transforms");
		else
			HC_Set_Text_Font ("transforms=character position only");
	}
	if ((m_mask & TKO_Font_Rotation) != 0) {
		if ((m_value & TKO_Font_Rotation) == 0)
			HC_Set_Text_Font ("no rotation");
		else if (m_rotation < 0.0f)
			HC_Set_Text_Font ("rotation=follow path");
		else {
			write_float (number, m_rotation);
			sprintf (buffer, "rotation=%s", number);
			HC_Set_Text_Font (buffer);
		}
	}
	if ((m_mask & TKO_Font_Slant) != 0) {
		if ((m_value & TKO_Font_Slant) == 0)
			HC_Set_Text_Font ("no slant");
		else {
			write_float (number, m_slant);
			sprintf (buffer, "slant=%s", number);
			HC_Set_Text_Font (buffer);
		}
	}
	if ((m_mask & TKO_Font_Width_Scale) != 0) {
		if ((m_value & TKO_Font_Width_Scale) == 0)
			HC_Set_Text_Font ("no width scale");
		else {
			write_float (number, m_width_scale);
			sprintf (buffer, "width scale=%s", number);
			HC_Set_Text_Font (buffer);
		}
	}
	if ((m_mask & m_value & TKO_Font_Extra_Space) != 0) {
		write_float (number, m_extra_space);
		sprintf (buffer, "extra space=%s %s", number, generic_units_table[m_space_units]);
		HC_Set_Text_Font (buffer);
	}
	if ((m_mask & TKO_Font_Line_Spacing) != 0) {
		write_float (number, m_line_spacing);
		sprintf (buffer, "line spacing=%s", number);
		HC_Set_Text_Font (buffer);
	}
	if ((m_mask & m_value & TKO_Font_Greeking_Limit) != 0) {
		if ((m_value & TKO_Font_Greeking_Limit) == 0)
			HC_Set_Text_Font ("no greeking limit");
		else {
			write_float (number, m_greeking_limit);
			sprintf (buffer, "greeking limit=%s %s", number, generic_units_table[m_greeking_units]);
			HC_Set_Text_Font (buffer);
		}
	}


	if (htk.GetHoopsVersion() >= 660) {
		if ((m_mask & TKO_Font_Outline) != 0) {
			if ((m_value & TKO_Font_Outline) == 0)
				HC_Set_Text_Font ("no outline");
			else {
				HC_Set_Text_Font ("outline");
			}
		}
	}
	if (htk.GetHoopsVersion() >= 751) {
		if ((m_mask & TKO_Font_Underline) != 0) {
			if ((m_value & TKO_Font_Underline) == 0)
				HC_Set_Text_Font ("no underline");
			else {
				HC_Set_Text_Font ("underline");
			}
		}
		if ((m_mask & TKO_Font_Strikethrough) != 0) {
			if ((m_value & TKO_Font_Strikethrough) == 0)
				HC_Set_Text_Font ("no strikethrough");
			else {
				HC_Set_Text_Font ("strikethrough");
			}
		}
		if ((m_mask & TKO_Font_Overline) != 0) {
			if ((m_value & TKO_Font_Overline) == 0)
				HC_Set_Text_Font ("no overline");
			else {
				HC_Set_Text_Font ("overline");
			}
		}
	}
	if (htk.GetHoopsVersion() >= 1270) {
		if ((m_mask & TKO_Font_Uniform_Spacing) != 0) {
			if ((m_value & TKO_Font_Uniform_Spacing) == 0)
				HC_Set_Text_Font ("no uniform spacing");
			else {
				HC_Set_Text_Font ("uniform spacing");
			}
		}
		if ((m_mask & TKO_Font_Fill_Edges) != 0) {
			if ((m_value & TKO_Font_Fill_Edges) == 0)
				HC_Set_Text_Font ("no fill edges");
			else {
				HC_Set_Text_Font ("fill edges");
			}
		}

		if ((m_mask & TKO_Font_Bold) != 0) {
			if ((m_value & TKO_Font_Bold) == 0)
				HC_Set_Text_Font ("no bold");
			else {
				HC_Set_Text_Font ("bold");
			}
		}
		if ((m_mask & TKO_Font_Italic) != 0) {
			if ((m_value & TKO_Font_Italic) == 0)
				HC_Set_Text_Font ("no italic");
			else {
				HC_Set_Text_Font ("italic");
			}
		}

		if ((m_mask & TKO_Font_Renderer) != 0) {
			switch (m_renderers[0]) {
				case TKO_Font_Renderer_Undefined:	break;
				case TKO_Font_Renderer_Default:		HC_Set_Text_Font ("renderer=smaller=default");	break;
				case TKO_Font_Renderer_Driver:		HC_Set_Text_Font ("renderer=smaller=driver");	break;
				case TKO_Font_Renderer_Truetype:	HC_Set_Text_Font ("renderer=smaller=truetype");	break;
				case TKO_Font_Renderer_Defined:		HC_Set_Text_Font ("renderer=smaller=defined");	break;
			}
			switch (m_renderers[1]) {
				case TKO_Font_Renderer_Undefined:	break;
				case TKO_Font_Renderer_Default:		HC_Set_Text_Font ("renderer=larger=default");	break;
				case TKO_Font_Renderer_Driver:		HC_Set_Text_Font ("renderer=larger=driver");	break;
				case TKO_Font_Renderer_Truetype:	HC_Set_Text_Font ("renderer=larger=truetype");	break;
				case TKO_Font_Renderer_Defined:		HC_Set_Text_Font ("renderer=larger=defined");	break;
			}
			if (m_renderer_cutoff == 0)
				HC_Set_Text_Font ("renderer=no cutoff");
			else if (m_renderer_cutoff > 0) {
				write_float (number, m_renderer_cutoff);
				sprintf (buffer, "renderer=cutoff=%s %s", number, generic_units_table[m_renderer_cutoff_units]);
				HC_Set_Text_Font (buffer);
			}
		}
	}
	if (htk.GetHoopsVersion() >= 1350) {
		if ((m_mask & TKO_Font_Greeking_Mode) != 0) {
			switch (m_greeking_mode) {
				case TKO_Font_Greeking_Mode_None:		HC_Set_Text_Font ("greeking mode=none");	break;
				case TKO_Font_Greeking_Mode_Lines:		HC_Set_Text_Font ("greeking mode=lines");	break;
				case TKO_Font_Greeking_Mode_Box:		HC_Set_Text_Font ("greeking mode=box");		break;
			}
		}

		if ((m_mask & TKO_Font_Preference) != 0) {
			switch (m_preferences[0]) {
				case TKO_Font_Preference_Undefined:	break;
				case TKO_Font_Preference_Default:	HC_Set_Text_Font ("preference=smaller=default");	break;
				case TKO_Font_Preference_Outline:	HC_Set_Text_Font ("preference=smaller=outline");	break;
				case TKO_Font_Preference_Bitmap:	HC_Set_Text_Font ("preference=smaller=bitmap");		break;
				case TKO_Font_Preference_Exterior:	HC_Set_Text_Font ("preference=smaller=exterior");	break;
			}
			switch (m_preferences[1]) {
				case TKO_Font_Preference_Undefined:	break;
				case TKO_Font_Preference_Default:	HC_Set_Text_Font ("preference=larger=default");	break;
				case TKO_Font_Preference_Outline:	HC_Set_Text_Font ("preference=larger=outline");	break;
				case TKO_Font_Preference_Bitmap:	HC_Set_Text_Font ("preference=larger=bitmap");	break;
				case TKO_Font_Preference_Exterior:	HC_Set_Text_Font ("preference=larger=exterior");break;
			}
			if (m_preference_cutoff == 0)
				HC_Set_Text_Font ("preference=no cutoff");
			else if (m_preference_cutoff > 0) {
				write_float (number, m_preference_cutoff);
				sprintf (buffer, "preference=cutoff=%s %s", number, generic_units_table[m_preference_cutoff_units]);
				HC_Set_Text_Font (buffer);
			}
		}
	}

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

	return TK_Normal;
}

// HTK_Text_Font::Interpret() currently in parse.cpp

IMPLEMENT_CLONE (HTK_Text_Font);

////////////////////////////////////////

TK_Status HTK_Font::Execute (BStreamFileToolkit & tk) alter {
	char            buffer[4096];

	UNREFERENCED (tk);

	sprintf (buffer, "encoding=%s", encodings[m_encoding]);
	if (GetLookup() != null) {
		strcat (buffer, ", lookup=");
		strcat (buffer, GetLookup());
	}
	HC_Define_Font (GetName(), buffer, GetBytesCount(), GetBytes());

	return TK_Normal;
}

TK_Status HTK_Font::Interpret (BStreamFileToolkit & tk, HC_KEY key, char const * name) alter {
	UNREFERENCED (key);
#ifndef HSTREAM_READONLY
	char            options[256];
	int             length;
	char            *op = options;
	int             i;

	UNREFERENCED (tk);

	SetName (name);

	HC_Show_Font_Size (name, options, &length);
	SetBytes (length);
	HC_Show_Font (name, options, &length, GetBytes());

	op += 9;    // strlen ("encoding=");
	for (i = 0; i < countof(encodings); ++i) {
		length = (int)strlen (encodings[i]);
		if (streqn (op, encodings[i], length)) {
			m_encoding = (unsigned char)i;
			op += length;
			break;
		}
	}
	if (*op == ',') {
		op += 9;    // strlen (", lookup=");
		SetLookup (op);
	}

	return TK_Normal;
#else
	UNREFERENCED (name);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Font);

////////////////////////////////////////

HTK_Texture::~HTK_Texture () {
	delete m_referee;
}

TK_Status HTK_Texture::Write (BStreamFileToolkit & tk) alter {
#ifndef HSTREAM_READONLY
	HStreamFileToolkit &htk = *(HStreamFileToolkit *)&tk;
	TK_Status       status = TK_Normal;

	switch (mh_stage) {
		case 0: {
			if (m_transform != null) {
				m_key = HC_KCreate_Segment (m_transform);
				// if follow-cross-references, and we haven't seen the segment, send out the segment first...
				if (/* m_follow &&*/ m_referee == null && !Find_Item (htk, m_key)) {
					m_referee = new Internal_Segment_Processor (m_key, m_transform);
				}

				if (m_referee != null) {
					if ((status = m_referee->Write (htk)) != TK_Normal)
					return status;
				}
			}

			mh_stage++;
		}   nobreak;

		case 1: {
			// did we tag that segment (such as revisiting an included segment)
			if (m_referee != null && htk.m_pending_tags != null && htk.m_pending_tags->m_key == m_key) {
				BBaseOpcodeHandler *        handler = htk.opcode_handler (TKE_Tag);
				Internal_Pending_Tag *      victim = htk.m_pending_tags;
				int                         index;
				char                        buffer[32];

				status = htk.KeyToIndex (m_key, index);
				if (status == TK_NotFound) {    // must be a new item
					index = tk.NextTagIndex();
					tk.AddIndexKeyPair (index, m_key);

					if (tk.GetLogging() && tk.GetLoggingOptions (TK_Logging_Tagging)) {
						sprintf (buffer, "(%d)", index);
						handler->SetLoggingString (buffer);
					}
				}

				if ((status = handler->Write (htk)) != TK_Normal)
					return status;
				handler->Reset();

				// safe to delete the pending tag once it's written
				htk.m_pending_tags = victim->m_next;
				delete victim;
			}
			mh_stage++;
		}   nobreak;

		case 2: {
			// now we can write the texture
			if ((status = TK_Texture::Write (htk)) != TK_Normal)
				return status;
			mh_stage = -1;
		}   break;

		default:
			return tk.Error();
	}

	return status;
#else
	return tk.Error (stream_readonly);
#endif
}

TK_Status HTK_Texture::Execute (BStreamFileToolkit & tk) alter {
	HStreamFileToolkit &    htk = *(HStreamFileToolkit *)&tk;
	char                    definition[8192];
	char                    single[64];
	char const *            which = null;
	HC_KEY		    include_library_images = -2;    // not ERROR_KEY and not a possible key

	if (m_image_length > 0)
		sprintf (definition, "source=%s,", m_image);
	else
		definition[0] = '\0';

	if ((m_flags & TKO_Texture_Param_Source) != 0) {
		which = null;
		switch (m_param_source) {
			case TKO_Texture_Param_Source_U:                    which = "u";                    break;
			case TKO_Texture_Param_Source_UV:                   which = "uv";                   break;
			case TKO_Texture_Param_Source_UVW:                  which = "uvw";                  break;
			case TKO_Texture_Param_Source_Object:               which = "object";               break;
			case TKO_Texture_Param_Source_World:                which = "world";                break;
			case TKO_Texture_Param_Source_Surface_Normal:       which = "surface normal";       break;
			case TKO_Texture_Param_Source_Reflection_Vector:    which = "reflection vector";    break;
			case TKO_Texture_Param_Source_Natural_UV:           which = "natural uv";           break;
			case TKO_Texture_Param_Source_Local_Pixels:         which = "local pixels";         break;
			case TKO_Texture_Param_Source_Outer_Pixels:         which = "outer pixels";         break;
			case TKO_Texture_Param_Source_Local_Window:         which = "local window";         break;
			case TKO_Texture_Param_Source_Outer_Window:         which = "outer window";         break;

			case TKO_Texture_Param_Source_Transmission_Vector:                                  break;
			case TKO_Texture_Param_Source_Sphere_Map:           if (htk.GetHoopsVersion() >= 950)
																	which = "sphere map";       break;
			case TKO_Texture_Param_Source_Cylinder_Map:         if (htk.GetHoopsVersion() >= 950)
																	which = "cylinder map";     break;
			case TKO_Texture_Param_Source_Physical_Reflection_Vector:
								if (htk.GetHoopsVersion() >= 1150)
																	which = "physical reflection"; break;

			default:    return tk.Error ("unknown texture parameter source");             nobreak;
		}

		if (which != null) {
			sprintf (single, "parameterization source=%s,", which);
			strcat (definition, single);
		}
	}
	if ((m_flags & TKO_Texture_Param_Function) != 0) {
		switch (m_param_function) {
			case TKO_Texture_Param_Function_None:               which = "off";                  break;
			case TKO_Texture_Param_Function_Sphere:             which = "sphere";               break;
			case TKO_Texture_Param_Function_Cylinder:           which = "cylinder";             break;
			case TKO_Texture_Param_Function_Box:                which = "box";                  break;

			default:    return tk.Error ("unknown texture parameter function");           nobreak;
		}

		sprintf (single, "parameterization function=%s,", which);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Tiling) != 0) {
		switch (m_tiling & 0x0F) {  // currently only one, not separate for U & V
			case TKO_Texture_Tiling_None:                       // no setting, use clamp
			case TKO_Texture_Tiling_Clamp:                      which = "clamp";                break;
			case TKO_Texture_Tiling_Repeat:                     which = "repeat";               break;
			case TKO_Texture_Tiling_Mirror:                     which = "mirror";               break;
			case TKO_Texture_Tiling_Drop:                       which = "drop";                 break;

			default:    return tk.Error ("unknown texture tiling");                       nobreak;
		}

		sprintf (single, "tiling=%s,", which);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Interpolation) != 0) {
		switch (m_interpolation) {
			case TKO_Texture_Filter_None:                       which = "off";                  break;
			case TKO_Texture_Filter_Trilinear:  // unused, use bilinear
			case TKO_Texture_Filter_Bilinear:                   which = "bilinear";             break;
			case TKO_Texture_Filter_Gaussian:                   which = "gaussian";             break;
			case TKO_Texture_Filter_Stochastic:                 which = "stochastic";           break;

			default:    return tk.Error ("unknown texture interpolation");                nobreak;
		}

		sprintf (single, "interpolation filter=%s,", which);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Decimation) != 0) {
		switch (m_decimation) {
			case TKO_Texture_Filter_None:                       which = "off";                  break;
			case TKO_Texture_Filter_MipMap:                     which = "mipmap";               break;
			case TKO_Texture_Filter_Anisotropic:                which = "anisotropic";          break;

			default:    return tk.Error ("unknown texture decimation");                    nobreak;
		}

		sprintf (single, "decimation filter=%s,", which);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Red_Mapping) != 0) {
		switch (m_red_mapping) {
			case TKO_Texture_Channel_Mapping_Red:               which = "red";                  break;
			case TKO_Texture_Channel_Mapping_Green:             which = "green";                break;
			case TKO_Texture_Channel_Mapping_Blue:              which = "blue";                 break;
			case TKO_Texture_Channel_Mapping_Alpha:             which = "alpha";                break;
			case TKO_Texture_Channel_Mapping_Zero:              which = "zero";                 break;
			case TKO_Texture_Channel_Mapping_One:               which = "one";                  break;
			case TKO_Texture_Channel_Mapping_Luminance:         which = "luminance";            break;
			case TKO_Texture_Channel_Mapping_None:              which = "off";                  break;

			default:    return tk.Error ("unknown texture red channel mapping");          nobreak;
		}

		sprintf (single, "red channel mapping=%s,", which);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Green_Mapping) != 0) {
		switch (m_green_mapping) {
			case TKO_Texture_Channel_Mapping_Red:               which = "red";                  break;
			case TKO_Texture_Channel_Mapping_Green:             which = "green";                break;
			case TKO_Texture_Channel_Mapping_Blue:              which = "blue";                 break;
			case TKO_Texture_Channel_Mapping_Alpha:             which = "alpha";                break;
			case TKO_Texture_Channel_Mapping_Zero:              which = "zero";                 break;
			case TKO_Texture_Channel_Mapping_One:               which = "one";                  break;
			case TKO_Texture_Channel_Mapping_Luminance:         which = "luminance";            break;
			case TKO_Texture_Channel_Mapping_None:              which = "off";                  break;

			default:    return tk.Error ("unknown texture green channel mapping");        nobreak;
		}

		sprintf (single, "green channel mapping=%s,", which);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Blue_Mapping) != 0) {
		switch (m_blue_mapping) {
			case TKO_Texture_Channel_Mapping_Red:               which = "red";                  break;
			case TKO_Texture_Channel_Mapping_Green:             which = "green";                break;
			case TKO_Texture_Channel_Mapping_Blue:              which = "blue";                 break;
			case TKO_Texture_Channel_Mapping_Alpha:             which = "alpha";                break;
			case TKO_Texture_Channel_Mapping_Zero:              which = "zero";                 break;
			case TKO_Texture_Channel_Mapping_One:               which = "one";                  break;
			case TKO_Texture_Channel_Mapping_Luminance:         which = "luminance";            break;
			case TKO_Texture_Channel_Mapping_None:              which = "off";                  break;

			default:    return tk.Error ("unknown texture blue channel mapping");         nobreak;
		}

		sprintf (single, "blue channel mapping=%s,", which);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Alpha_Mapping) != 0) {
		switch (m_alpha_mapping) {
			case TKO_Texture_Channel_Mapping_Red:               which = "red";                  break;
			case TKO_Texture_Channel_Mapping_Green:             which = "green";                break;
			case TKO_Texture_Channel_Mapping_Blue:              which = "blue";                 break;
			case TKO_Texture_Channel_Mapping_Alpha:             which = "alpha";                break;
			case TKO_Texture_Channel_Mapping_Zero:              which = "zero";                 break;
			case TKO_Texture_Channel_Mapping_One:               which = "one";                  break;
			case TKO_Texture_Channel_Mapping_Luminance:         which = "luminance";            break;
			case TKO_Texture_Channel_Mapping_None:              which = "off";                  break;

			default:    return tk.Error ("unknown texture alpha channel mapping");        nobreak;
		}

		sprintf (single, "alpha channel mapping=%s,", which);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Layout) != 0) {
		switch (m_alpha_mapping) {
			case TKO_Texture_Layout_Rectilinear:                which = "rectilinear";          break;
			case TKO_Texture_Layout_Spherical:                  which = "spherical";            break;
			case TKO_Texture_Layout_Hemispherical:              which = "hemispherical";        break;
			case TKO_Texture_Layout_Cubic_Faces:                which = "cubic faces";          break;

			default:    return tk.Error ("unknown texture layout");                       nobreak;
		}

		sprintf (single, "layout=%s,", which);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Transform) != 0) {
		sprintf (single, "transform='%s',", m_transform);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Camera) != 0) {
		sprintf (single, "camera='%s',", m_camera);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Source_Dimensions) != 0) {
		sprintf (single, "source dimensions=(%d,%d,%d),", m_source_dimensions[0], m_source_dimensions[1], m_source_dimensions[2] );
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Value_Scale) != 0) {
		char            v1[32], v2[32];

		write_float (v1, m_value_scale[0]);
		write_float (v2, m_value_scale[1]);
		sprintf (single, "value scale=(%s,%s),", v1, v2);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Caching) != 0)
		strcat (definition, "caching,");
	if ((m_flags & TKO_Texture_DownSample) != 0)
		strcat (definition, "down sample,");
	else if ((m_flags & TKO_Texture_No_DownSample) != 0)
		strcat (definition, "no down sample,");
	else if (tk.GetVersion() < 1155)
		strcat (definition, "no down sample,");

	if ((m_flags & TKO_Texture_Modulate) != 0) {
		if ((m_apply_mode & TKO_Texture_Modulate_Set) != 0)
			strcat (definition, "modulate,");
		else
			strcat (definition, "no modulate,");
	}
	if ((m_flags & TKO_Texture_Decal) != 0) {
		if ((m_apply_mode & TKO_Texture_Decal_Set) != 0)
			strcat (definition, "decal,");
		else
			strcat (definition, "no decal,");
	}
	if ((m_flags & TKO_Texture_Param_Offset) != 0) {
		sprintf (single, "parameter offset=%d,", (int)m_param_offset);
		strcat (definition, single);
	}
	if ((m_flags & TKO_Texture_Transform_Override) != 0)
		strcat (definition, "transform override,");
	if ((m_flags & TKO_Texture_Shader_Multitexture) != 0)
		strcat (definition, "multitexture,");


	if (definition[0])
		definition[strlen(definition)-1] = '\0';    // remove final comma

	if (HC_QShow_Existence ("?Include Library/texture images", "self"))
		include_library_images = HC_KCreate_Segment ("?Include Library/texture images");

	if ((m_flags & TKO_Texture_Shader) != 0) {
		HC_Define_Shader (m_name, definition, m_shader_source);
	}
	else {
		if (tk.CurrentSegment() != include_library_images)
			HC_Define_Local_Texture (m_name, definition);
		else
			HC_Define_Texture (m_name, definition);
	}

	return TK_Normal;
}


static char *find_next_comma (char *start) 
{
	char *ptr;
	char quote = 0;
	
	ptr = start;
	for (;;) {
		if (*ptr == '"' || *ptr == '\'' || *ptr == '`' || *ptr == '(' || *ptr == ')' ) {
			if (quote) {
				if (*ptr == quote)
					/* tjh: no need to handle escaped quotes here, since after the 2nd instance 
					* the state of "quote" is back where we started */
					quote = 0;
			}
			else
				if (*ptr == '(')
					quote = ')';
				else
					quote = *ptr;
		}
		else if (*ptr == ',') {
			if (!quote)
				return ptr;
		}
		else if (*ptr == '\0')
			return null;
		ptr++;
	}
}


TK_Status HTK_Texture::Interpret (BStreamFileToolkit & tk, HC_KEY key, char const * name) alter {
#ifndef HSTREAM_READONLY
	char        definition[4096];
	char        shader_source[16000];
	char *      def;

	set_name (name);

	if (m_flags & TKO_Texture_Shader) {
		HC_Show_Shader (name, definition, shader_source);
		SetShaderSource (shader_source);
	}
	else {
		if (key)	// global texture
			HC_Show_Texture (name, definition);
		else
			HC_Show_Local_Texture (name, definition);
	}

	def = definition;

	while (*def) {
		bool	set = true;

		if (def[0] == 'n' && def[1] == 'o' && def[2] == ' ') {
			set = false;
			def += 3; // strlen ("no ");
		}

		switch (*def) {
			case 'a': {
				if (def[1] == 'p') {	// apply mode
					def += 11;	// strlen ("apply mode=");
					while (*def != '\0' && *def != ',') def++;
					break;
				}
			}	nobreak;    // drop through for alpha mapping

			case 'r':       // mappings
			case 'g':
			case 'b': {
				char *      mapping = null;

				switch (*def) {
					case 'r': {
						m_flags |= TKO_Texture_Red_Mapping;     mapping = &m_red_mapping;   def += 3;   // strlen ("red");
					}   break;
					case 'g': {
						m_flags |= TKO_Texture_Green_Mapping;   mapping = &m_green_mapping; def += 5;   // strlen ("green");
					}   break;
					case 'b': {
						m_flags |= TKO_Texture_Blue_Mapping;    mapping = &m_blue_mapping;  def += 4;   // strlen ("blue");
					}   break;
					case 'a': {
						m_flags |= TKO_Texture_Alpha_Mapping;   mapping = &m_alpha_mapping; def += 5;   // strlen ("alpha");
					}   break;
				}
				def += 17;  // strlen (" channel mapping=");
				switch (*def) {
					case 'r':   *mapping = TKO_Texture_Channel_Mapping_Red;     def += 3;   // strlen ("red");
								break;
					case 'g':   *mapping = TKO_Texture_Channel_Mapping_Green;   def += 5;   // strlen ("green");
								break;
					case 'b':   *mapping = TKO_Texture_Channel_Mapping_Blue;    def += 4;   // strlen ("blue");
								break;
					case 'a':   *mapping = TKO_Texture_Channel_Mapping_Alpha;   def += 5;   // strlen ("alpha");
								break;
					case 'z':   *mapping = TKO_Texture_Channel_Mapping_Zero;    def += 4;   // strlen ("zero");
								break;
					case 'o':
						if (def[1] == 'f') {
								*mapping = TKO_Texture_Channel_Mapping_None;    def += 3;   // strlen ("off");
								break;
						}
						else {
								*mapping = TKO_Texture_Channel_Mapping_One;     def += 3;   // strlen ("one");
								break;
						}
					case 'l':   *mapping = TKO_Texture_Channel_Mapping_Luminance;def += 9;  // strlen ("luminance");
								break;
					default:    return tk.Error("unknown mapping");
				}
			}   break;

			case 'c': {     // caching, camera
				if (def[2] == 'c') {	// caching
					def += 7;   // strlen ("caching");
					if (*def == '=')
						def += 3;	// strlen ("=on");
					m_flags |= TKO_Texture_Caching;
				}
				else {					// camera
					def += 6;	// strlen ("camera");
					if (set) {
						++def;	// '='
						m_flags |= TKO_Texture_Camera;

						char *	tmp = def;
						do {
							++tmp;
						} while (*tmp!= '\0' && *tmp!=')' && *tmp!=',');

						m_camera_length = (int) (tmp - def);
						m_camera = new char [m_camera_length+1];

						memcpy(m_camera, def, m_camera_length);
						m_camera[m_camera_length] = '\0';
						def = tmp;
					}
				}
			}   break;

			case 'd': {     // decal, decimation, down sample
				if (def[3] == 'a') {	    // decal
					def += 5;		// strlen ("decal");
					m_flags |= TKO_Texture_Decal;
					if (set)
						m_apply_mode |= TKO_Texture_Decal_Set;
					else
						m_apply_mode &= ~TKO_Texture_Decal_Set;
				}
				else if (def[1] == 'e') {   // decimation
					def += 18;		// strlen ("decimation filter=");
					m_flags |= TKO_Texture_Decimation;
					switch (*def) {
						case 'o':   m_decimation = TKO_Texture_Filter_None;         def += 3;   // strlen ("off");
								break;
						case 'm':   m_decimation = TKO_Texture_Filter_MipMap;       def += 6;   // strlen ("mipmap");
								break;
						case 'a':   m_decimation = TKO_Texture_Filter_Anisotropic;  def += 11;  // strlen ("anisotropic");
								break;
						default:    return tk.Error("unknown decimation filter");
					}
				}
				else {			    // down sample
					def += 11;  // strlen ("down sample");
					if (set)
						m_flags |= TKO_Texture_DownSample;
					else
						m_flags |= TKO_Texture_No_DownSample;
				}
			}   break;

			case 'l': {     // layout
				def += 7;   // strlen ("layout=");
				m_flags |= TKO_Texture_Layout;
				switch (*def) {
					case 'c':   m_layout = TKO_Texture_Layout_Cubic_Faces;      def += 11;  // strlen ("cubic faces");
								break;
					case 'h':   m_layout = TKO_Texture_Layout_Hemispherical;    def += 13;  // strlen ("hemispherical");
								break;
					case 'r':   m_layout = TKO_Texture_Layout_Rectilinear;      def += 11;  // strlen ("rectilinear");
								break;
					case 's':   m_layout = TKO_Texture_Layout_Spherical;        def += 9;   // strlen ("spherical");
								break;
					default:    return tk.Error("unknown layout");
				}
			}   break;

			case 'i': {     // interpolation
				def += 21;  // strlen ("interpolation filter=");
				m_flags |= TKO_Texture_Interpolation;
				switch (*def) {
					case 'o':   m_interpolation = TKO_Texture_Filter_None;       def += 3;  // strlen ("off");
								break;
					case 'b':   m_interpolation = TKO_Texture_Filter_Bilinear;   def += 8;  // strlen ("bilinear");
								break;
					case 'g':   m_interpolation = TKO_Texture_Filter_Gaussian;   def += 8;  // strlen ("gaussian");
								break;
					case 's':   m_interpolation = TKO_Texture_Filter_Stochastic; def += 10; // strlen ("stochastic");
								break;
					case 't':   m_interpolation = TKO_Texture_Filter_Trilinear;  def += 9;  // strlen ("trilinear");
								break;
					default:    return tk.Error("unknown interpolation filter");
				}
			}   break;

			case 'm': {     // modulate or multitexture
				if (def[1] == 'o') {
					def += 8;   // strlen ("modulate");
					m_flags |= TKO_Texture_Modulate;
					if (set)
						m_apply_mode |= TKO_Texture_Modulate_Set;
					else
						m_apply_mode &= ~TKO_Texture_Modulate_Set;
				}
				else {
					def += 12;   // strlen ("multitexture")
					m_flags |= TKO_Texture_Shader_Multitexture;
				}
			}   break;

			case 'p': {     // parameterization source, parameterization function, parameter offset
				def += 9;  // strlen ("parameter");
				if (*def == 'i') {
					def += 8;	    // strlen ("ization ");
					if (*def == 's') {      // source
						m_flags |= TKO_Texture_Param_Source;
						def += 7;   // strlen ("source=");
						switch (*def) {
							case 'c':   m_param_source = TKO_Texture_Param_Source_Cylinder_Map;
								def += 12;  // strlen ("cylinder map");
								break;

							case 'l': {
								def += 6;   // strlen ("local ");
								if (def[1] == 'p') {
									m_param_source = TKO_Texture_Param_Source_Local_Pixels;
									def += 6;   // strlen ("pixels");
								}
								else {
									m_param_source = TKO_Texture_Param_Source_Local_Window;
									def += 6;   // strlen ("window");
								}
							}   break;

							case 'n':   m_param_source = TKO_Texture_Param_Source_Natural_UV;
								def += 10;  // strlen ("natural uv");
								break;

							case 'o': {
								if (def[1] == 'b') {
									m_param_source = TKO_Texture_Param_Source_Object;
									def += 6;   // strlen ("object");
								}
								else {
									def += 6;   // strlen ("outer ");
									if (def[1] == 'p') {
										m_param_source = TKO_Texture_Param_Source_Outer_Pixels;
										def += 6;   // strlen ("pixels");
									}
									else {
										m_param_source = TKO_Texture_Param_Source_Outer_Window;
										def += 6;   // strlen ("window");
									}
								}
							}   break;

							case 'p':   m_param_source = TKO_Texture_Param_Source_Physical_Reflection_Vector;
								def += 19;  // strlen ("physical reflection");
								break;
							case 'r':   m_param_source = TKO_Texture_Param_Source_Reflection_Vector;
								def += 17;  // strlen ("reflection vector");
								break;

							case 's': {
								if (def[1] == 'p') {
									m_param_source = TKO_Texture_Param_Source_Sphere_Map;
									def += 10;  // strlen ("sphere map");
								}
								else {
									m_param_source = TKO_Texture_Param_Source_Surface_Normal;
									def += 14;  // strlen ("surface normal");
								}
							}           break;

							case 't':   m_param_source = TKO_Texture_Param_Source_Transmission_Vector;
								def += 19;  // strlen ("transmission vector");
								break;

							case 'u': {
								m_param_source = TKO_Texture_Param_Source_U;
								++def;
								if (*def == 'v') {
									m_param_source = TKO_Texture_Param_Source_UV;
									++def;
								}
								if (*def == 'w') {
									m_param_source = TKO_Texture_Param_Source_UVW;
									++def;
								}
							}   break;

							case 'w':   m_param_source = TKO_Texture_Param_Source_World;
								def += 5;   // strlen ("world");
								break;

							default:    return tk.Error("unknown parameterization source");
						}
					}
					else /* if (*def == 'f') */ {		// function
						m_flags |= TKO_Texture_Param_Function;
						def += 9;	// strlen ("function=");
						switch (*def) {
							case 'b':   m_param_function = TKO_Texture_Param_Function_Box;
								def += 3;   // strlen ("box");
								break;
							case 'c':   m_param_function = TKO_Texture_Param_Function_Cylinder;
								def += 8;   // strlen ("cylinder");
								break;
							case 'o':   m_param_function = TKO_Texture_Param_Function_None;
								def += 3;   // strlen ("off");
								break;
							case 's':   m_param_function = TKO_Texture_Param_Function_Sphere;
								def += 6;   // strlen ("sphere");
								break;

							default:    return tk.Error("unknown parameterization function");
						}
					}
				}
				else {				// offset
					int	    offset;

					m_flags |= TKO_Texture_Param_Offset;
					def += 8;	// strlen (" offset=");
					READ_INT (offset, def);
					m_param_offset = (unsigned char)offset;
				}
			}   break;

			case 's': {     
				if (def[6] == '=') {
					// source=
					char *      comma;

					def += 7;   // strlen ("source=");
					// tjh: a simple strchr won't do here since ',' guarded by quotes needs to be skipped
					comma = find_next_comma (def);
					if (comma != null)
						*comma++ = '\0';

					set_image (def);

					if (comma != null)
						def = comma;
					else
						*def = '\0';
				}
				else {
					// source dimensions=
					def += 18;   // strlen ("source dimensions=");
					m_flags |= TKO_Texture_Source_Dimensions;
					while (*def++ != '(') {}
					m_source_dimensions[0] = (int)read_float(def);
					while (*def++ != ',') {}
					m_source_dimensions[1] = (int)read_float (def);
					while (*def++ != ',') {}
					m_source_dimensions[2] = (int)read_float (def);
					while (*def++ != ')') {}
				}
			}   break;

			case 't': {     // tiling, transform, transform override
				if (def[1] == 'i') {    // tiling
					def += 7;   // strlen ("tiling=");
					m_flags |= TKO_Texture_Tiling;
					switch (*def) {
						case 'c':   m_tiling = TKO_Texture_Tiling_Clamp;    def += 5;   // strlen ("clamp");
									break;
						case 'd':   m_tiling = TKO_Texture_Tiling_Drop;     def += 4;   // strlen ("drop");
									break;
						case 'm':   m_tiling = TKO_Texture_Tiling_Mirror;   def += 6;   // strlen ("mirror");
									break;
						case 'r':   m_tiling = TKO_Texture_Tiling_Repeat;   def += 6;   // strlen ("repeat");
									break;
						default:    return tk.Error("unknown tiling");
					}
					m_tiling |= m_tiling << 4;      // repeat as 2 separate entries in the stream format
				}
				else if (def[9] == ' ' && def[10] == 'o') {	// transform override
					def += 18;	// strlen ("transform override");
					if (set)
						m_flags |= TKO_Texture_Transform_Override;
				}
				else {                  // transform
					char *      comma = null;
					char *      quote = null;

					m_flags |= TKO_Texture_Transform;
					def += 10;  // strlen ("transform=");
					if (*def == '\'') {
						def++;
						quote = strchr (def, '\'');
						if (quote == null)
							return tk.Error ("unmatched ' in texture transform string");
						*quote++ = '\0';
					}
					else {
						comma = strchr (def, ',');
						if (comma != null)
							*comma++ = '\0';
					}

					set_transform (def);

					if (quote != null)
						def = quote;
					else if (comma != null)
						def = comma;
					else
						*def = '\0';
				}
			}   break;

			case 'v': {
				def += 13;  // strlen ("value scale=(");
				m_flags |= TKO_Texture_Value_Scale;
				m_value_scale[0] = read_float (def);
				while (*def++ != ',') {}
				m_value_scale[1] = read_float (def);
				while (*def++ != ')') {}
			}   break;

			default:
				return tk.Error("unknown texture option");
		}

		if (*def == ',')
			++def;
	}

	if ((m_flags & 0xFFFF0000) != 0)
		m_flags |= TKO_Texture_Extended;

	return TK_Normal;
#else
	UNREFERENCED (key);
	UNREFERENCED (name);
	return tk.Error (stream_readonly);
#endif
}

void HTK_Texture::Reset () {
	mh_stage = 0;
	delete m_referee;
	m_referee = null;

	TK_Texture::Reset();
}

IMPLEMENT_CLONE (HTK_Texture);

////////////////////////////////////////////////////////////////////////////////
// pseudo-object used to hold several textures, output only

HTK_Texture_Definitions::HTK_Texture_Definitions (bool is_shader)
	: BBaseOpcodeHandler (TKE_Pseudo_Handler), m_parts (null), m_num_parts (0), m_is_shader(is_shader) {}

HTK_Texture_Definitions::~HTK_Texture_Definitions () {
	int         i;

	for (i = 0; i < m_num_parts; ++i)
		delete m_parts[i];
	delete [] m_parts;
}

TK_Status HTK_Texture_Definitions::Write (BStreamFileToolkit & tk) alter {
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;

	while (m_stage < m_num_parts) {
		if ((status = m_parts[m_stage]->Write (tk)) != TK_Normal)
			return status;
		adjust_written (tk, -1);    // don't count the subpiece
		++m_stage;
	}
	adjust_written (tk, 1);         // now count the whole set of textures
	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}


TK_Status HTK_Texture_Definitions::Interpret(BStreamFileToolkit & tk, ID_Key key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;
	char			name[4096];
	int				size = 0;

	if (m_is_shader) {
		HC_Begin_Shader_Search ();
		while (HC_Find_Shader (name)) {
			HTK_Texture *   texture;

			tk.GetOpcodeHandler(TKE_Texture)->Clone(tk, (BBaseOpcodeHandler **)&texture);

			texture->SetFlags (TKO_Texture_Shader);
			if ((status = texture->Interpret (tk, 0, name)) != TK_Normal)
				return status;

			if (m_num_parts == size) {
				BBaseOpcodeHandler **   old_parts = m_parts;

				m_parts = new BBaseOpcodeHandler * [size += 16];
				memcpy (m_parts, old_parts, m_num_parts*sizeof(BBaseOpcodeHandler *));
				memset (m_parts+m_num_parts, 0, (size-m_num_parts)*sizeof(BBaseOpcodeHandler *));
				delete [] old_parts;
			}
			m_parts[m_num_parts++] = texture;
		}
		HC_End_Shader_Search ();
	}
	else {
		HC_Begin_Local_Texture_Search ();
		while (HC_Find_Texture (name)) {
			HTK_Texture *   texture;

			tk.GetOpcodeHandler(TKE_Texture)->Clone(tk, (BBaseOpcodeHandler **)&texture);

			if ((status = texture->Interpret (tk, 0, name)) != TK_Normal)
				return status;

			if (m_num_parts == size) {
				BBaseOpcodeHandler **   old_parts = m_parts;

				m_parts = new BBaseOpcodeHandler * [size += 16];
				memcpy (m_parts, old_parts, m_num_parts*sizeof(BBaseOpcodeHandler *));
				memset (m_parts+m_num_parts, 0, (size-m_num_parts)*sizeof(BBaseOpcodeHandler *));
				delete [] old_parts;
			}
			m_parts[m_num_parts++] = texture;
		}
		HC_End_Texture_Search ();
	}

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}


TK_Status HTK_Texture_Definitions::Read (BStreamFileToolkit & tk) alter {
	return tk.Error();
}
TK_Status HTK_Texture_Definitions::Execute (BStreamFileToolkit & tk) alter {
	return tk.Error();
}

IMPLEMENT_CLONE (HTK_Texture_Definitions);

////////////////////////////////////////////////////////////////////////////////

TK_Status HTK_Glyph_Definition::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);

	HC_Define_Glyph (GetName(), GetDefinitionSize(), GetDefinition());

	return TK_Normal;
}

TK_Status HTK_Glyph_Definition::Interpret (BStreamFileToolkit & tk, HC_KEY key, char const * name) alter {
	UNREFERENCED (key);
#ifndef HSTREAM_READONLY
	char *      data;
	int		size;

	UNREFERENCED (tk);

	HC_Show_Glyph_Size (name, &size);
	data = new char [size+1];	// Show_Glyph overwrites on byte extra
	HC_Show_Glyph (name, data);

	SetName (name);
	SetDefinition (size, data);

	delete [] data;


	return TK_Normal;
#else
	UNREFERENCED (name);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Glyph_Definition);

////////////////////////////////////////////////////////////////////////////////

TK_Status HTK_Named_Style_Def::Write (BStreamFileToolkit & tk) alter {
#ifndef HSTREAM_READONLY
	HStreamFileToolkit &	htk = *(HStreamFileToolkit *)&tk;
	TK_Status				status = TK_Normal;

	if (tk.GetTargetVersion() < 1815)
		return TK_Normal;

	switch (mh_stage) {
		case 0: {
			// if follow-cross-references, and we haven't seen the segment, send out the segment first...
			if (m_follow && m_referee == null && !Find_Item (htk, m_key)) {
				Internal_Segment_Processor *	sp = new Internal_Segment_Processor (m_key, m_segment);
				// Note: processor starts new root by default, but use current root if it's relative
				if (m_segment[0] != '/')
					sp->SetRoot (GetRoot());

				m_referee = sp;
			}

			if (m_referee != null) {

				if ((status = m_referee->Write (htk)) != TK_Normal)
					return status;
			}
		
			mh_stage++;
		}   nobreak;

		case 1: {
			// did we tag that segment (such as revisiting an included segment)
			if (m_referee != null && htk.m_pending_tags != null && htk.m_pending_tags->m_key == m_key) {
				BBaseOpcodeHandler *        handler = htk.opcode_handler (TKE_Tag);
				Internal_Pending_Tag *      victim = htk.m_pending_tags;
				int                         index;
				char                        buffer[32];

				status = htk.KeyToIndex (m_key, index);
				if (status == TK_NotFound) {    // must be a new item
					index = tk.NextTagIndex();
					tk.AddIndexKeyPair (index, m_key);

					if (tk.GetLogging() && tk.GetLoggingOptions (TK_Logging_Tagging)) {
						sprintf (buffer, "(%d)", index);
						handler->SetLoggingString (buffer);
					}
				}

				if ((status = handler->Write (htk)) != TK_Normal)
					return status;
				handler->Reset();

				// safe to delete the pending tag once it's written
				htk.m_pending_tags = victim->m_next;
				delete victim;
			}
			mh_stage++;
		}   nobreak;

		case 2: {
			// now we can write the reference
			if ((status = TK_Named_Style_Def::Write (htk)) != TK_Normal)
				return status;
			mh_stage = -1;
		}   break;

		default:
			return tk.Error();
	}

	return status;
#else
	return tk.Error (stream_readonly);
#endif
}

TK_Status HTK_Named_Style_Def::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);

	HC_Define_Named_Style(GetName(), GetSegment());

	return TK_Normal;
}

TK_Status HTK_Named_Style_Def::Interpret (BStreamFileToolkit & tk, HC_KEY key, char const * name) alter {
	UNREFERENCED (key);
#ifndef HSTREAM_READONLY

	char		segbuf[4096];
	char *		segname = segbuf;

	HC_Show_Named_Style(name, segname);

	m_key = HC_KCreate_Segment(segname);

	HStreamFileToolkit & htk = (HStreamFileToolkit &)tk;

	TK_Status	status = make_path_relative_segment(htk, m_key, GetRoot(), segname);

	if (status != TK_Normal)
		return status;

	SetName (name);
	SetSegment (segname);

	return TK_Normal;
#else
	UNREFERENCED (name);
	return tk.Error (stream_readonly);
#endif
}

void HTK_Named_Style_Def::Reset () alter {
	mh_stage = 0;
	TK_Named_Style_Def::Reset();
}

IMPLEMENT_CLONE (HTK_Named_Style_Def);

////////////////////////////////////////////////////////////////////////////////

TK_Status HTK_Line_Style::Execute (BStreamFileToolkit & tk) alter {
	UNREFERENCED (tk);

	HC_Define_Line_Style (GetName(), GetDefinition());

	return TK_Normal;
}

TK_Status HTK_Line_Style::Interpret (BStreamFileToolkit & tk, HC_KEY key, char const * name) alter {
	UNREFERENCED (key);
#ifndef HSTREAM_READONLY
	char *      definition;
	int		size;

	UNREFERENCED (tk);

	HC_Show_Line_Style_Size (name, &size);
	definition = new char [size+1];
	HC_Show_Line_Style (name, definition);

	SetName (name);
	SetDefinition (definition);

	delete [] definition;

	return TK_Normal;
#else
	UNREFERENCED (name);
	return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE (HTK_Line_Style);

////////////////////////////////////////////////////////////////////////////////
// pseudo-object used to hold several glyph definitions, output only

HTK_Glyph_Definitions::HTK_Glyph_Definitions ()
	: BBaseOpcodeHandler (TKE_Pseudo_Handler), m_parts (null), m_num_parts (0) {}

HTK_Glyph_Definitions::~HTK_Glyph_Definitions () {
	int         i;

	for (i = 0; i < m_num_parts; ++i)
		delete m_parts[i];
	delete [] m_parts;
}

TK_Status HTK_Glyph_Definitions::Write (BStreamFileToolkit & tk) alter {
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;

	while (m_stage < m_num_parts) {
		if ((status = m_parts[m_stage]->Write (tk)) != TK_Normal)
			return status;
		adjust_written (tk, -1);    // don't count the subpiece
		++m_stage;
	}
	adjust_written (tk, 1);         // now count the whole set of textures
	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}


TK_Status HTK_Glyph_Definitions::Interpret(BStreamFileToolkit & tk, ID_Key key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;
	char			*name = new char[1024*32];
	int				size = 0;

	UNREFERENCED (key);

	HC_Begin_Glyph_Search ();
	while (HC_Find_Glyph (name)) {
		HTK_Glyph_Definition *   gd;

		tk.GetOpcodeHandler(TKE_Glyph_Definition)->Clone(tk, (BBaseOpcodeHandler **)&gd);

		if ((status = gd->Interpret (tk, 0, name)) != TK_Normal) {
			delete [] name;
			return status;
		}

		if (m_num_parts == size) {
			BBaseOpcodeHandler **   old_parts = m_parts;

			m_parts = new BBaseOpcodeHandler * [size += 16];
			memcpy (m_parts, old_parts, m_num_parts*sizeof(BBaseOpcodeHandler *));
			memset (m_parts+m_num_parts, 0, (size-m_num_parts)*sizeof(BBaseOpcodeHandler *));
			delete [] old_parts;
		}
		m_parts[m_num_parts++] = gd;
	}
	HC_End_Glyph_Search ();

	delete [] name;
	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}


TK_Status HTK_Glyph_Definitions::Read (BStreamFileToolkit & tk) alter {
	return tk.Error();
}
TK_Status HTK_Glyph_Definitions::Execute (BStreamFileToolkit & tk) alter {
	return tk.Error();
}

IMPLEMENT_CLONE (HTK_Glyph_Definitions);


////////////////////////////////////////////////////////////////////////////////
// pseudo-object used to hold several glyph definitions, output only

HTK_Named_Style_Defs::HTK_Named_Style_Defs ()
: BBaseOpcodeHandler (TKE_Pseudo_Handler), m_parts (null), m_num_parts (0) {}

HTK_Named_Style_Defs::~HTK_Named_Style_Defs () {
	int         i;

	for (i = 0; i < m_num_parts; ++i)
		delete m_parts[i];
	delete [] m_parts;
}

TK_Status HTK_Named_Style_Defs::Write (BStreamFileToolkit & tk) alter {
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;

	while (m_stage < m_num_parts) {
		if ((status = m_parts[m_stage]->Write (tk)) != TK_Normal)
			return status;
		adjust_written (tk, -1);    // don't count the subpiece
		++m_stage;
	}
	adjust_written (tk, 1);         // now count the whole set of textures
	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}


TK_Status HTK_Named_Style_Defs::Interpret(BStreamFileToolkit & tk, ID_Key key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;
	char			*name = new char[1024*32];
	int				size = 0;

	UNREFERENCED (key);

	HC_Begin_Named_Style_Search ();
	while (HC_Find_Named_Style (name)) {
		HTK_Named_Style_Def *   nsd;

		tk.GetOpcodeHandler(TKE_Named_Style_Def)->Clone(tk, (BBaseOpcodeHandler **)&nsd);
		nsd->SetRoot (GetRoot());

		if ((status = nsd->Interpret (tk, 0, name)) != TK_Normal) {
			delete [] name;
			return status;
		}

		if (m_num_parts == size) {
			BBaseOpcodeHandler **   old_parts = m_parts;

			m_parts = new BBaseOpcodeHandler * [size += 16];
			memcpy (m_parts, old_parts, m_num_parts*sizeof(BBaseOpcodeHandler *));
			memset (m_parts+m_num_parts, 0, (size-m_num_parts)*sizeof(BBaseOpcodeHandler *));
			delete [] old_parts;
		}
		m_parts[m_num_parts++] = nsd;
	}
	HC_End_Named_Style_Search ();

	delete [] name;
	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}


TK_Status HTK_Named_Style_Defs::Read (BStreamFileToolkit & tk) alter {
	return tk.Error();
}
TK_Status HTK_Named_Style_Defs::Execute (BStreamFileToolkit & tk) alter {
	return tk.Error();
}

IMPLEMENT_CLONE (HTK_Named_Style_Defs);

////////////////////////////////////////////////////////////////////////////////
// pseudo-object used to hold several line pattern definitions, output only

HTK_Line_Styles::HTK_Line_Styles ()
	: BBaseOpcodeHandler (TKE_Pseudo_Handler), m_parts (null), m_num_parts (0) {}

HTK_Line_Styles::~HTK_Line_Styles () {
	int         i;

	for (i = 0; i < m_num_parts; ++i)
		delete m_parts[i];
	delete [] m_parts;
}

TK_Status HTK_Line_Styles::Write (BStreamFileToolkit & tk) alter {
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;

	while (m_stage < m_num_parts) {
		if ((status = m_parts[m_stage]->Write (tk)) != TK_Normal)
			return status;
		adjust_written (tk, -1);    // don't count the subpiece
		++m_stage;
	}
	adjust_written (tk, 1);         // now count the whole set of textures
	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}


TK_Status HTK_Line_Styles::Interpret(BStreamFileToolkit & tk, ID_Key key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	TK_Status       status = TK_Normal;
	char	* name = new char[1024*32];
	int		size = 0;

	UNREFERENCED (key);

	HC_Begin_Line_Style_Search ();
	while (HC_Find_Line_Style (name)) {
		HTK_Line_Style *	lpd;

		tk.GetOpcodeHandler(TKE_Line_Style)->Clone(tk, (BBaseOpcodeHandler **)&lpd);

		if ((status = lpd->Interpret (tk, 0, name)) != TK_Normal) {
			delete [] name;
			return status;
		}

		if (m_num_parts == size) {
			BBaseOpcodeHandler **   old_parts = m_parts;

			m_parts = new BBaseOpcodeHandler * [size += 16];
			memcpy (m_parts, old_parts, m_num_parts*sizeof(BBaseOpcodeHandler *));
			memset (m_parts+m_num_parts, 0, (size-m_num_parts)*sizeof(BBaseOpcodeHandler *));
			delete [] old_parts;
		}
		m_parts[m_num_parts++] = lpd;
	}
	HC_End_Line_Style_Search ();

	delete [] name;
	return TK_Normal;
#else
	UNREFERENCED (key);
	return tk.Error (stream_readonly);
#endif
}


TK_Status HTK_Line_Styles::Read (BStreamFileToolkit & tk) alter {
	return tk.Error();
}
TK_Status HTK_Line_Styles::Execute (BStreamFileToolkit & tk) alter {
	return tk.Error();
}

IMPLEMENT_CLONE (HTK_Line_Styles);

////////////////////////////////////////
