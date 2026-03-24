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
// $Header: /files/homes/master/cvs/hoops_master/hoops_stream/source/HOpcodeShell.cpp,v 1.172 2010-01-21 23:37:54 covey Exp $
//

#include "HStream.h"
#include "HOpcodeShell.h"
#include "HOpcodeHandler.h"
#include "HPolyhedron.h"
#include "BInternal.h"
#define ASSERT(x) 

//enumerate_points
//a small helper function to generate a cuboid given two opposing corners
static void enumerate_points(
    float *p1,
    float *p2,
    float *out)
{
    out[0]  = p1[0];    out[1]  = p1[1];    out[2]  = p1[2];  // 000
    out[3]  = p1[0];    out[4]  = p1[1];    out[5]  = p2[2];  // 001
    out[6]  = p1[0];    out[7]  = p2[1];    out[8]  = p1[2];  // 010
    out[9]  = p1[0];    out[10] = p2[1];    out[11] = p2[2];  // 011
    out[12] = p2[0];    out[13] = p1[1];    out[14] = p1[2];  // 100
    out[15] = p2[0];    out[16] = p1[1];    out[17] = p2[2];  // 101
    out[18] = p2[0];    out[19] = p2[1];    out[20] = p1[2];  // 110
    out[21] = p2[0];    out[22] = p2[1];    out[23] = p2[2];  // 111
} //end function enumerate_points


const int bounding_faces[30] = {
    4,0,4,5,1,  
    4,0,2,6,4,  
    4,0,1,3,2,  
    4,7,6,2,3,  
    4,7,3,1,5,  
    4,7,5,4,6  
};
//const int bounding_tristrips[19] = {
//    18,6,2,4,0,0,1,4,5,6,7,2,3,0,1,1,3,5,7
//};

//public virtual
TK_Status HTK_Shell::Execute (BStreamFileToolkit & tk) alter {
    TK_Status       status = TK_Normal;     // assume success
    int             i;          
    HC_KEY          keysave;

    if (m_opcode != TKE_Shell)
        return tk.Error();

    //insert a placeholder.  
    //If this is firstpass and lodlevel == 0, we'll simply replace the base resolution.
    if (mp_subop & TKSH_FIRSTPASS)
        mp_key = HC_KInsert_Shell(0, null, 0, null); 

    if (mp_subop2 & TKSH2_NULL) {
        if (m_lodlevel != 0) {
            HC_Open_Geometry(mp_key);
                HC_Open_LOD(m_lodlevel);
                    HC_Insert_Shell(0, null, 0, null);
                HC_Close_LOD();
            HC_Close_Geometry();
        }
        set_last_key (tk, mp_key);
        return status;
    }

    if (mp_subop & TKSH_BOUNDING_ONLY) {
		if (tk.GetReadFlags (TK_Ignore_Bounding_LODs)) {
			float points[24];
			//int bounding_tristripslen = sizeof(bounding_tristrips) / sizeof(int);

			//(note that in bounding only mode we can never be refining 
			//a previously given opcode)
			enumerate_points(&mp_bbox[0], &mp_bbox[3], points);
	    
			HC_Open_Geometry(mp_key);
				HC_Open_LOD(m_lodlevel);
					HC_Insert_Shell(8, points, 30, bounding_faces);
					//HC_Insert_Shell_By_Tristrips(8, points, 
					//                bounding_tristripslen, bounding_tristrips, 0, null);
				HC_Close_LOD();
			HC_Close_Geometry();
		}
        set_last_key (tk, mp_key);
    }
    else {
        keysave = mp_key;
        HC_Open_Geometry(mp_key);
            HC_Open_LOD(m_lodlevel);
                if (m_lodlevel != 0)
                    HC_Flush_Contents(".", "geometry");
                if (!(mp_subop2 & TKSH2_COLLECTION)) {
                    if (mp_subop & TKSH_TRISTRIPS)
                        mp_key = HC_KInsert_Shell_By_Tristrips(mp_pointcount, mp_points, 
                                    m_flistlen, m_flist, 0, null);
                    else
                        mp_key = HC_KInsert_Shell(mp_pointcount, mp_points, m_flistlen, m_flist);
                }
                else {
                    for (i = 0 ; i < mp_num_collection_parts ; i++) {
                        mp_collection_parts[i]->Execute(tk);
                    }
                }
            HC_Close_LOD();
        HC_Close_Geometry();

		if (m_lodlevel == 0)
			mp_key = keysave;

        if (mp_subop & TKSH_HAS_OPTIONALS)
            ((HTK_Polyhedron *)this)->HExecute (tk);

        mp_key = keysave;
        set_last_key (tk, mp_key);
    }

    return status;

} // end function HTK_Shell::Execute

#ifndef EPSILON
#  define EPSILON (1e-5f)
#endif
TK_Status HTK_Shell::Usefulness(BStreamFileToolkit & tk, HC_KEY key, int lod, float alter &score) const 
{
#ifndef HSTREAM_READONLY
    float cost, benefit;
    int point_count, face_list_length;
    char tempstr[128];

    UNREFERENCED (tk);

    //should we use HOOPS' usefulness heuritic?
    //char tempstr[512];
    //HC_Show_One_Net_Rendering_Optio("lodo");
    //if (strstr(tempstr, "usefulness heuristic = bounding volume"));

    //make the benefit proportional to length of the bounding volume diagonal
    benefit = ((mp_bbox[3] - mp_bbox[0]) * (mp_bbox[3] - mp_bbox[0])) +
              ((mp_bbox[4] - mp_bbox[1]) * (mp_bbox[4] - mp_bbox[1])) +
              ((mp_bbox[5] - mp_bbox[2]) * (mp_bbox[5] - mp_bbox[2]));
   // benefit = (float) sqrt(benefit);

    //make cost proportional to # of bytes (notice we pass m_lodlevel instead of key)
    HC_Open_Geometry(key);
        HC_Open_LOD(lod);
            HC_Show_LOD_Type(key, lod, tempstr);
            if (streq(tempstr, "shell")) {
                HC_Show_Shell_Size(lod, &point_count, &face_list_length);
                cost = 10.0f + 4.0f * ((point_count * 3) + face_list_length); 
            }
            else {
                int count;
                HC_Begin_Contents_Search(".", "geometry");
                    HC_Show_Contents_Count(&count);
                HC_End_Contents_Search();
                cost = 20.0f * count;
            }
        HC_Close_LOD();
    HC_Close_Geometry();

    if (cost < EPSILON)
        score = 0;
    else
        score = benefit / cost;
    return TK_Normal;
#else
    UNREFERENCED (key);
    UNREFERENCED (lod);
    UNREFERENCED (score);
    return tk.Error (stream_readonly);
#endif
}


TK_Status HTK_Shell::Revisit (BStreamFileToolkit & tk, float priority, int lod) const {
    float score;
    TK_Status status;

    if (!(tk.GetWriteFlags() & TK_Disable_Priority_Heuristic)) {
        if ((status = Usefulness(tk, mp_key, lod, score)) != TK_Normal)
            return status;
        BBaseOpcodeHandler::Revisit (tk, score, lod);
    }
    else  {
        BBaseOpcodeHandler::Revisit (tk, priority, lod);
    }
    return TK_Normal;
}


#define LOD_MIN_VERTEX_COUNT 10
#define LOD_MAX_LEVEL 8


TK_Status HTK_Shell::ProcessRevisits(
        BStreamFileToolkit & tk, 
        int lod_in, 
        bool *do_continue)
{
    TK_Status status = TK_Normal;
    char pass;
    int i, coarsest, flags;
    char tempstr[128];

    *do_continue = true;

    pass = (char)Pass(tk);
    flags = tk.GetWriteFlags();

    // -2 is a special value that indicates that we want 
    // the base resolution, only the base resolution, and no revisitation
    // (as of this writing it has so far only been used for segment-level LOD)
    if (lod_in == -2) {
        m_lodlevel = 0;
        return TK_Normal;
    }

    if (pass == 0) {
        // schedule our coarsest representation.  If LODs suppressed, "coarsest" 
        // is automatically 0
        coarsest = 0;
        if (!(flags & TK_Suppress_LOD)) {
            for (i = 0 ; i < LOD_MAX_LEVEL ; i++) {
                HC_Show_LOD_Type(mp_key, i, tempstr);
                if (!streq(tempstr, "invalid"))
                    coarsest = i;
            }
        }
        if ((flags & TK_Suppress_LOD) && 
            (flags & TK_Disable_Priority_Heuristic) &&
            !(flags & TK_Generate_Dictionary)) {
            //with this combination of flags, write the full shell straight into segment tree
            m_lodlevel = (char)coarsest;
        }
        else {
            Revisit(tk, coarsest);
            // output some sort of placeholder -- bbox, empty, or null
            if (!(mp_subop & TKSH_BOUNDING_ONLY)) {
                mp_pointcount = 0;
                m_flistlen = 0;
                if (tk.GetTargetVersion() >= 652) {
                    mp_subop |= TKSH_EXPANDED;
                    mp_subop2 |= TKSH2_NULL;
                }
            }
            m_lodlevel = (char)coarsest;
            *do_continue = false;
        }
    }
    else if (pass == 1) {
        coarsest = lod_in;
        for (i = 0 ; i < coarsest ; i++) {
            HC_Show_LOD_Type(mp_key, i, tempstr);
            if (!streq(tempstr, "invalid")) {
                Revisit(tk, i);
            }
        }
        /* Differences between dictionary and non-dictionary case:
         * Dictionary case:  has one lod_in for all shells starting in second pass sorted 
         *   w.r.t. each other.  After second pass, it's unconstrained free for all mix n' match
         * Non-Dictionary case: unconstrained from the start
         */
        if (flags & TK_Generate_Dictionary) {
            m_lodlevel = (char)coarsest;
        }
        else {
            Revisit(tk, coarsest);
            *do_continue = false;
             /* return TK_Revisit as an indication that nothing at all should be written during 
              * this pass */
            return TK_Revisit;
        }
    }
    else {
        // nothing more needs to be scheduled.  Just fall through and output what was requested.
        m_lodlevel = (char)lod_in;
    }
    return status;
}


/* Interpret
 * public virtual
 * Extracts data from HOOPS into the TK_Shell structure
 * Makes all decisions about what formats to use.
 * Writing decisions are based partly on tk's flags, partly on HOOPS' contents
 */
TK_Status HTK_Shell::Interpret (BStreamFileToolkit & tk, HC_KEY key, int lod) alter {
#ifndef HSTREAM_READONLY
    char pass;
    char tempstr[512];
    int i;
    int flags = tk.GetWriteFlags();
    TK_Status status = TK_Normal;
    int facemap_count = 0, *facemap = null;
    char type[128];
    HC_KEY subkey;
    bool do_continue;

    mp_key = key;
    pass = (char)Pass(tk);
    HC_Compute_Circumcuboid_By_Key(key, &mp_bbox[0], &mp_bbox[3]);
    InitSubop(tk, lod, pass == 0);

    status = ProcessRevisits(tk, lod, &do_continue);
    if (status != TK_Normal)
        return status; //could be a TK_Error or a TK_Revisit (meaning nothing at all should be written during this pass)
    if (!do_continue)
        return TK_Normal;

    if (m_lodlevel < 0)
        return tk.Error("internal error in HTK_Shell::Interpret");

    //if we're spitting out the full resolution version
    if (m_lodlevel == 0) {
        //an early escape if we have no points
        HC_Show_Shell_Size (key, &mp_pointcount, null);
        if (mp_pointcount == 0 && 
            tk.GetTargetVersion() >= 652) {
            mp_subop |= TKSH_EXPANDED;
            mp_subop2 |= TKSH2_NULL;
            return status;
        }

        // set flags in mp_subop specific to lodlevel 0
        if (!(flags & TK_Full_Resolution_Vertices))
            mp_subop |= TKSH_COMPRESSED_POINTS;

        //find out how much to allocate
        if (mp_subop & TKSH_TRISTRIPS) {
            HC_Show_Shell_By_Tristrips_Size (key, &mp_pointcount, 
                            &m_flistlen, &facemap_count);
            //the tristripper tosses degenerate faces, so use special handling for flistlen == 0
            if (m_flistlen == 0) {
                mp_subop &= ~TKSH_TRISTRIPS;
                HC_Show_Shell_Size (key, &mp_pointcount, &m_flistlen);
            }
        }
        else
            HC_Show_Shell_Size (key, &mp_pointcount, &m_flistlen);

        // allocate
        ASSERT(mp_points == null && m_flist == null);
        if (mp_pointcount != 0)
            set_points (mp_pointcount);
        if (m_flistlen != 0)
            set_flist (m_flistlen);

        // grab it from HOOPS
        if (mp_subop & TKSH_TRISTRIPS) {
            facemap = new int[ facemap_count ];
            HC_Show_Shell_By_Tristrips (key, &mp_pointcount, 
                                mp_points, &m_flistlen, m_flist, 
                                &facemap_count, facemap);
            mp_facecount = 0;
            /* if se have a facemap, facecount should reflect the original number of faces,
             * not the new number of faces.  Here we calculate that as the maximum of facemap[i] */
            for (i = 0 ; i < facemap_count ; i ++) {
                if (facemap[i] > mp_facecount)
                    mp_facecount = facemap[i];
            }
            //indices are zero based, so the count is max index + 1
            mp_facecount += 1;
        }
        else {
            HC_Show_Shell (key, &mp_pointcount, mp_points, &m_flistlen, m_flist);
            i = 0;
            mp_facecount = 0;
            while (i < m_flistlen) {
                if (m_flist[i] > 0) {
                    mp_facecount++;
                    i += m_flist[i] + 1;
                }
                else {
                    //a continuation (to define a hole in) the previous face
                    i += -m_flist[i] + 1;
                }
            }
        }
        if ((status = ((HTK_Polyhedron *)this)->HInterpret(tk, key, m_lodlevel)) == TK_Error) 
            return status;
    }
    else {
        //always use compressed points for LODs
        mp_subop |= TKSH_COMPRESSED_POINTS;

        //we should have a valid lod at this level.  output it.
        //we're in trouble if it wasn't a shell at that LOD level
        HC_Show_LOD_Type(key, m_lodlevel, tempstr);
        if (streq(tempstr, "shell")) {  //assumes that shells aren't part of a collection
            HC_Open_Geometry(key);
                HC_Open_LOD(m_lodlevel);
                    HC_Begin_Contents_Search(".", "shells");
                    HC_Find_Contents(type, &subkey);
                    HC_End_Contents_Search();

                    //an early escape if we have no points
                    HC_Show_Shell_Size (subkey, &mp_pointcount, null);
                    if (mp_pointcount == 0 && 
                        tk.GetTargetVersion() >= 652) {
                        mp_subop |= TKSH_EXPANDED;
                        mp_subop2 |= TKSH2_NULL;
                        //don't return yet, because we still need to close lod and geom
                    }
                    else {
                        //now we can grab data from hoops just like the full-res case
                        if (mp_subop & TKSH_TRISTRIPS) {
                            HC_Show_Shell_By_Tristrips_Size (subkey, &mp_pointcount, &m_flistlen, &facemap_count);
                            //the tristripper tosses degenerate faces, so use special handling for flistlen == 0
                            if (m_flistlen == 0) {
                                mp_subop &= ~TKSH_TRISTRIPS;
                                HC_Show_Shell_Size (subkey, &mp_pointcount, &m_flistlen);
                            }
                        }
                        else
                            HC_Show_Shell_Size (subkey, &mp_pointcount, &m_flistlen);

                        if (mp_pointcount != 0)
                            set_points (mp_pointcount);
                        if (m_flistlen != 0)
                            set_flist (m_flistlen);

                        if (mp_subop & TKSH_TRISTRIPS) {
							facemap = new int[ facemap_count ];
                            HC_Show_Shell_By_Tristrips (subkey, &mp_pointcount, 
                                                        mp_points, &m_flistlen, m_flist, 
                                                        &facemap_count, facemap);
							mp_facecount = 0;
							/* find the highest face index
							 * if se have a facemap, facecount should reflect the original number of faces,
							 * not the new number of faces.  Here we calculate that as the maximum of facemap[i] */
							for (i = 0 ; i < facemap_count ; i ++) {
								if (facemap[i] > mp_facecount)
									mp_facecount = facemap[i];
							}
							//indices are zero based, so the count is max index + 1
							mp_facecount += 1;
                        }
                        else {
                            HC_Show_Shell (subkey, &mp_pointcount, mp_points, &m_flistlen, m_flist);
							i = 0;
							while (i < m_flistlen) {
								if (m_flist[i] > 0) {
									mp_facecount++;
									i += m_flist[i] + 1;
								}
								else {
									//a continuation (to define a hole in) the previous face
									i += -m_flist[i] + 1;
								}
							}
                        }
                    }
                HC_Close_LOD();
            HC_Close_Geometry();

            if ((status = ((HTK_Polyhedron *)this)->HInterpret(tk, subkey, m_lodlevel)) == TK_Error) 
                return status;
        }
        else {
            int count;

            if (tk.GetTargetVersion() >= 602) {  // extended format added in 6.02
                HStreamFileToolkit &htk = *(HStreamFileToolkit *)&tk;

                mp_subop |= TKSH_EXPANDED;
                mp_subop2 |= TKSH2_COLLECTION;
                HC_Open_Geometry(key);
                    HC_Open_LOD(m_lodlevel);
                        HC_Begin_Contents_Search(".", "geometry");
                            HC_Show_Contents_Count(&count);
                            mp_num_collection_parts = count;
                            mp_collection_parts = new BBaseOpcodeHandler *[count];
							HC_Reverse_Contents_Search();
                            for (i = 0; i < count; i++) {
                                HC_Find_Contents(type, &subkey);
                                if ((status = htk.StringToHandler (type, &mp_collection_parts[i])) == TK_Error)
                                    break;
                                if ((status = mp_collection_parts[i]->Interpret (tk, subkey, 0)) == TK_Error)
									break;
                            }
                        HC_End_Contents_Search();
                    HC_Close_LOD();
                HC_Close_Geometry();
                return status;
            }
            else {
                //if target version can't handle non-shell lod's, pretend we 
                //just have an empty shell
                mp_pointcount = 0;
                mp_points = null;
                m_flistlen = 0;
                m_flist = null;
            }
        }
    }

    /* Face attributes from HOOPS are with respect to their original faces.
     * We need to remap them according to their order of appearance in the tristrips. */
    if (facemap != null) {
        if (HasFaceAttributes())
            mangle_face_attributes(tk, facemap_count, facemap);
        delete [] facemap;
        facemap = null;
    }

    if (AllowInstancing(tk))
        Find_Instance (tk, mp_pointcount, m_flistlen, mp_present);

    return TK_Normal;
#else
    UNREFERENCED (key);
    UNREFERENCED (lod);
    return tk.Error (stream_readonly);
#endif
} // end function HTK_Shell::interpret



bool HTK_Shell::Match_Instance (BStreamFileToolkit const & tk, Recorded_Instance alter * instance) alter {
#ifndef HSTREAM_READONLY
    // generate basis (if needed) and then do precice checks
    int             instance_count;
    float *         instance_points;
    int             instance_flistlen;
    int *           instance_flist;
    int             i;

    if (mp_pointcount == 0)
	return false;

    if (mp_subop & TKSH_TRISTRIPS)
        HC_Show_Shell_By_Tristrips_Size (instance->m_key, &instance_count, &instance_flistlen, null);
    else
        HC_Show_Shell_Size (instance->m_key, &instance_count, &instance_flistlen);

    if (m_flistlen != instance_flistlen ||
	mp_pointcount != instance_count)
	return false;

    instance_points = new float [3*instance_count];
    if (instance_flistlen)
		instance_flist = new int [instance_flistlen];
    else
		instance_flist = null;

    if (mp_subop & TKSH_TRISTRIPS)
        HC_Show_Shell_By_Tristrips (instance->m_key, &instance_count, 
                                    instance_points, &instance_flistlen, instance_flist, null, null);
    else
        HC_Show_Shell (instance->m_key, &instance_count, instance_points, &instance_flistlen, instance_flist);
    
    for (i=0; i<m_flistlen; i++)
        if (instance_flist[i] != m_flist[i])
            break;

    delete [] instance_flist;
    instance_flist = null;

    if (i < instance_flistlen) {
        delete [] instance_points;
        return false;
    }

    if (!instance->basis_valid()) {
        if (!instance->generate_basis (instance_count, instance_points)) {
            delete [] instance_points;
            instance_points = null;
            return false;
        }
    }

    // and now the more complex transformed point comparison
    if (!((HTK_Polyhedron *)this)->match_points (instance, instance_points)) {
        delete [] instance_points;
        instance_points = null;
        return false;
    }

    delete [] instance_points;
    instance_points = null;

    // and now the relatively simple attribute comparison
    if (!((HTK_Polyhedron *)this)->match_attributes (instance))
        return false;

    // got one, so set up to use it instead of writing out the whole thing
    int             index;
    int             our_index = -1;
    int             options = 0;

    if (tk.KeyToIndex (instance->m_key, index) != TK_Normal) {
        tk.Error("internal error: instance matched for shell that cannot be found");
        return false;
    }
	if ((mp_subop & TKSH_FIRSTPASS) == 0) {
       tk.KeyToIndex (mp_key, our_index);
	   if (our_index == -1)					// unusual case, probably a reference forcing a write
		   return false;					// so we have nothing to to instance *into*
	}
    if ((mp_subop & TKSH_TRISTRIPS) != 0)
        options |= Instance_By_Tristrip;
    mp_instance = new TK_Instance (index, instance->m_variant, our_index, m_lodlevel, options, mp_matrix);

    return true;
#else
    UNREFERENCED (tk);
    UNREFERENCED (instance);
    return false;
#endif
} // end function HTK_Shell::Match_Instance



TK_Status HTK_Shell::LabelFakeEdges()
{
    TK_Status status = TK_Normal;
    int *non_tristrips_face_list, *tristrips_save, *enumeration_save;
    int *non_tristrips_enumeration, *ptr;
    int i, face_list_length, edgecount_save, flistlen_save;        

    if (mp_edge_exists == null)
        return TK_Error;
    if (!(mp_subop & TKSH_TRISTRIPS))
        return status;
    HC_Show_Geometry_Pointer(mp_key, "face list", &non_tristrips_face_list);
    if (!non_tristrips_face_list) 
        return status;
    HC_Show_Shell_Size(mp_key, NULL, &face_list_length);
    if (face_list_length == mp_facecount * 4)
        return status;

    enumeration_save = mp_edge_enumeration;
    edgecount_save = mp_edgecount;
    mp_subop &= ~TKSH_TRISTRIPS;
    tristrips_save = m_flist;
    m_flist = non_tristrips_face_list;
    flistlen_save = m_flistlen;
    m_flistlen = face_list_length;
    status = EnumerateEdges();
    m_flist = tristrips_save;
    mp_subop |= TKSH_TRISTRIPS;
    non_tristrips_enumeration = mp_edge_enumeration;
    mp_edge_enumeration = enumeration_save;
    mp_edgecount = edgecount_save;
    m_flistlen = flistlen_save;
    if (status == TK_Normal) {
        ptr = non_tristrips_enumeration;
        for (i = 0 ; i < mp_edgecount ; i++) {
            if (ptr[0] == mp_edge_enumeration[i*2] &&
                ptr[1] == mp_edge_enumeration[i*2+1])
                ptr += 2;
            else {
                mp_edge_exists[i] |= Fake_Edge;
            }
        }
    }
    delete [] non_tristrips_enumeration;
    return status;
}

IMPLEMENT_CLONE (HTK_Shell);
