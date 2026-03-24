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
// $Header: /files/homes/master/cvs/hoops_master/hoops_stream/source/HPolyhedron.cpp,v 1.66 2010-01-21 23:37:54 covey Exp $
//

#include "HStream.h"
#include "HPolyhedron.h"
#include "HOpcodeShell.h"
#include "BInternal.h"
#define ASSERT(x) 


////////////////////////////////////////////////////////////////////////////////
TK_Status HTK_Polyhedron::Execute (BStreamFileToolkit & tk) alter {
    return tk.Error ();
}

TK_Status HTK_Polyhedron::Interpret (BStreamFileToolkit & tk, HC_KEY key, int lod) alter {
    UNREFERENCED(key);
    UNREFERENCED(lod);
    return tk.Error ();
}


TK_Status HTK_Polyhedron::HExecute (BStreamFileToolkit & tk, int mesh_columns) alter {
    HStreamFileToolkit &htk = *(HStreamFileToolkit *)&tk;
    unsigned int handled;
    int row, col, face;
    int i;

    if (mp_pointcount <= 0)
        return TK_Normal;

    if (HasVertexAttributes()) {
        HTK_Named vmsym (TKE_Marker_Symbol);
        handled = 0;

        if (mp_normalcount == mp_pointcount) {
            HC_MSet_Vertex_Normals (mp_key, 0, mp_normalcount, mp_normals);
            handled |= Vertex_Normal;
        }
        if (mp_paramcount == mp_pointcount) {
            HC_MSet_Vertex_Parameters (mp_key, 0, mp_paramcount, mp_paramwidth, mp_params);
            handled |= Vertex_Parameter;
        }
        if (mp_vfcolorcount == mp_pointcount) {
            HC_MSet_Vertex_Colors_By_Value (mp_key, "face", 0, "rgb", mp_vfcolorcount, mp_vfcolors);
            handled |= Vertex_Face_Color;
        }
        else if (mp_vfindexcount == mp_pointcount) {
            HC_MSet_Vertex_Colors_By_FIndex (mp_key, "face", 0, mp_vfindexcount, mp_vfindices);
            handled |= Vertex_Face_Index;
        }
        if (mp_vecolorcount == mp_pointcount) {
            HC_MSet_Vertex_Colors_By_Value (mp_key, "edge", 0, "rgb", mp_vecolorcount, mp_vecolors);
            handled |= Vertex_Edge_Color;
        }
        else if (mp_veindexcount == mp_pointcount) {
            HC_MSet_Vertex_Colors_By_FIndex (mp_key, "edge", 0, mp_veindexcount, mp_veindices);
            handled |= Vertex_Edge_Index;
        }
        if (mp_vmcolorcount == mp_pointcount) {
            HC_MSet_Vertex_Colors_By_Value (mp_key, "marker", 0, "rgb", mp_vmcolorcount, mp_vmcolors);
            handled |= Vertex_Marker_Color;
        }
        else if (mp_vmrgbacount == mp_pointcount) {
            HC_MSet_Vertex_Colors_By_Value (mp_key, "marker", 0, "rgba", mp_vmrgbacount, mp_vmrgbas);
            handled |= Vertex_Marker_Color;
        }
        else if (mp_vmindexcount == mp_pointcount) {
            HC_MSet_Vertex_Colors_By_FIndex (mp_key, "marker", 0, mp_vmindexcount, mp_vmindices);
            handled |= Vertex_Marker_Index;
        }
        HC_Open_Geometry (mp_key);
            for (i = 0; i < mp_pointcount; i++) {
                if ((mp_exists[i] & ~handled) == Vertex_None)
                    continue;
                HC_Open_Vertex (i);
                    if (!(handled & Vertex_Normal) && (mp_exists[i] & Vertex_Normal))
                        HC_Set_Normal (mp_normals[3*i + 0], mp_normals[3*i + 1], mp_normals[3*i + 2]);
                    if (!(handled & Vertex_Parameter) && (mp_exists[i] & Vertex_Parameter))
                        HC_Set_Parameter (mp_paramwidth, &mp_params[mp_paramwidth*i]);
                    if (mp_exists[i] & Vertex_Any_Color) {
                        if (!(handled & Vertex_Face_Color) && (mp_exists[i] & Vertex_Face_Color))
                            HC_Set_Color_By_Value ("face", "rgb", mp_vfcolors[3*i + 0], mp_vfcolors[3*i + 1], mp_vfcolors[3*i + 2]);
                        if (!(handled & Vertex_Edge_Color) && (mp_exists[i] & Vertex_Edge_Color))
                            HC_Set_Color_By_Value ("edge", "rgb", mp_vecolors[3*i + 0], mp_vecolors[3*i + 1], mp_vecolors[3*i + 2]);
                        if (!(handled & Vertex_Marker_Color) && (mp_exists[i] & Vertex_Marker_Color))
                            HC_Set_Color_By_Value ("marker", "rgb", mp_vmcolors[3*i + 0], mp_vmcolors[3*i + 1], mp_vmcolors[3*i + 2]);
                        if (!(handled & Vertex_Face_Index) && (mp_exists[i] & Vertex_Face_Index))
                            HC_Set_Color_By_FIndex ("face", mp_vfindices[i]);
                        if (!(handled & Vertex_Edge_Index) && (mp_exists[i] & Vertex_Edge_Index))
                            HC_Set_Color_By_FIndex ("edge", mp_veindices[i]);
                        if (!(handled & Vertex_Marker_Index) && (mp_exists[i] & Vertex_Marker_Index))
                            HC_Set_Color_By_FIndex ("marker", mp_vmindices[i]);
                        if (!(handled & Vertex_Marker_RGBA) && (mp_exists[i] & Vertex_Marker_RGBA))
                            HC_MSet_Vertex_Colors_By_Value (mp_key, "marker", i, "rgba", 1, &mp_vmrgbas[4*i]);
                    }
                    if (mp_exists[i] & Vertex_Marker_Visibility) {
                        if (mp_vmvisibilities[i] != 0)
                            HC_Set_Visibility("on");
                        else
                            HC_Set_Visibility("off");
                    }
                    if (mp_exists[i] & Vertex_Marker_Symbol) {
						if (mp_vmsymbols[i] != 0x00FF)
							vmsym.SetIndex (mp_vmsymbols[i]);
						else
							vmsym.SetName (mp_vmsymbolstrings[i]);
                        vmsym.Execute (tk);
                    }
                    if (mp_exists[i] & Vertex_Marker_Size)
                        HC_Set_Marker_Size (mp_vmsizes[i]);
                HC_Close_Vertex ();
            }
        HC_Close_Geometry ();
    }

    if (HasFaceAttributes()) {
        HTK_Enumerated	fpat(TKE_Face_Pattern);
		bool			legacy_numbering = true;

		if (htk.GetHoopsVersion() >= 1350) {
			char		legacy_setting[64];

			HC_Show_One_System_Option ("legacy mesh face numbering", legacy_setting);
			if (legacy_setting[1] == 'f')
				legacy_numbering = false;
		}
        handled = 0;

        if (mp_fnormalcount == mp_facecount) {
            HC_MSet_Face_Normals (mp_key, 0, mp_fnormalcount, mp_fnormals);
            handled |= Face_Normal;
        }
        if (mp_fcolorcount > 0 && mp_fcolorcount == mp_facecount && m_opcode != TKE_Mesh) {
            HC_MSet_Face_Colors_By_Value (mp_key, "face", 0, "rgb", mp_fcolorcount, mp_fcolors);
            handled |= Face_Color;
        }
        
		if (mp_findexcount > 0 && mp_findexcount == mp_facecount && m_opcode != TKE_Mesh) {
            HC_MSet_Face_Colors_By_FIndex (mp_key, "face", 0, mp_findexcount, mp_findices);
            handled |= Face_Index; 
        }
        HC_Open_Geometry (mp_key);
            for (i = 0; i < mp_facecount; i++) {

				if (mp_face_exists[i] & ~handled) {

					if (m_opcode == TKE_Mesh && legacy_numbering) {
						// convert between sequential numbering and HOOPS' funky mesh face 
						// numbering scheme if needed
						row = (i/2)/(mesh_columns-1);
						col = (i/2)%(mesh_columns-1);
						face = (row * mesh_columns) + col;
						if (i & 1) {
							face = -(face + mesh_columns + 1);
						}
					}
					else
						face = i;

					HC_Open_Face (face);
						if (!(handled & Face_Color) && (mp_face_exists[i] & Face_Color))
							HC_Set_Color_By_Value ("face", "rgb", mp_fcolors[3*i + 0], mp_fcolors[3*i + 1], mp_fcolors[3*i + 2]);
						if (!(handled & Face_Index) && (mp_face_exists[i] & Face_Index))
							HC_Set_Color_By_FIndex ("face", mp_findices[i]);
						if (mp_face_exists[i] & Face_Pattern) {
							fpat.SetIndex (mp_fpatterns[i]);
							fpat.Execute (tk);
						}
						if (mp_face_exists[i] & Face_Visibility) {
							if (mp_fvisibilities[i])
								HC_Set_Visibility ("on");
							else
								HC_Set_Visibility ("off");
						}
						if (!(handled & Face_Normal) && mp_face_exists[i] & Face_Normal)
							HC_Set_Normal (mp_fnormals[3*i + 0], mp_fnormals[3*i + 1], mp_fnormals[3*i + 2]);
					HC_Close_Face ();
				}
            }
        HC_Close_Geometry ();
    }

    if (mp_fregions != null) {
        HC_MSet_Face_Regions (mp_key, 0, mp_facecount, mp_fregions);
    }

    if (HasEdgeAttributes()) {
        HTK_Named epat (TKE_Edge_Pattern);

        HC_Open_Geometry (mp_key);
            for (i = 0; i < mp_edgecount; i++) {
                if (mp_edge_exists[i] == Edge_None)
                    continue;
                HC_Open_Edge  (mp_edge_enumeration[2*i], mp_edge_enumeration[2*i+1]);
                    if (mp_edge_exists[i] & Edge_Visibility) {
                        if (mp_evisibilities[i] != 0)
                            HC_Set_Visibility("on");
                        else
                            HC_Set_Visibility("off");
                    }
                    if (mp_edge_exists[i] & Edge_Pattern) {
						if (mp_epatterns[i] != 0x00FF)
							epat.SetIndex (mp_epatterns[i]);
						else
							epat.SetName (mp_epatternstrings[i]);
                        epat.Execute (tk);
                    }
                    if (mp_edge_exists[i] & Edge_Color)
                        HC_Set_Color_By_Value ("edge", "rgb", mp_ecolors[3*i + 0], mp_ecolors[3*i + 1], mp_ecolors[3*i + 2]);
                    if (mp_edge_exists[i] & Edge_Index)
                        HC_Set_Color_By_FIndex ("edge", mp_eindices[i]);
                    if (mp_edge_exists[i] & Edge_Normal)
                        HC_Set_Normal (mp_enormals[3*i + 0], mp_enormals[3*i + 1], mp_enormals[3*i + 2]);
                    if (mp_edge_exists[i] & Edge_Weight)
                        HC_Set_Edge_Weight (mp_eweights[i]);
                HC_Close_Edge ();
            }
        HC_Close_Geometry ();
    }

    if (mp_num_collection_parts > 0) {
        // entity-level attributes
        HC_Open_Geometry (mp_key);
            for (i = 0; i < mp_num_collection_parts; i++) {
                mp_collection_parts[i]->Execute (tk);
            }
        HC_Close_Geometry ();
    }

    return TK_Normal;
}


TK_Status HTK_Polyhedron::HInterpret (BStreamFileToolkit & tk, HC_KEY key, int lod, int mesh_columns) alter {
    UNREFERENCED (lod);
#ifndef HSTREAM_READONLY
    HStreamFileToolkit &htk = *(HStreamFileToolkit *)&tk;
    int i;
    int row, col, face;
    //vattribs, fattribs and eattribs are flags to indicate whether show_existence is necessary for given attributes
    unsigned int vattribs = Vertex_None; 
    unsigned int fattribs = Face_None;
    unsigned int eattribs = Edge_None;
    char tempstr[128];
    TK_Status   status = TK_Normal;


    mp_normalcount = 0;
    mp_paramcount  = 0;
    mp_paramwidth = 0;
    mp_vfcolorcount = 0;
    mp_vecolorcount = 0;
    mp_vmcolorcount = 0;
    mp_vmrgbacount = 0;
    mp_vfindexcount = 0;
    mp_veindexcount = 0;
    mp_vmindexcount = 0;
    mp_vmvisibilitycount = 0;
    mp_vmsizecount = 0;
    mp_vmsymbolcount = 0;

    mp_fcolorcount = 0;
    mp_findexcount = 0;
    mp_fnormalcount = 0;
    mp_fpatterncount = 0;
    mp_fvisibilitycount = 0;

    mp_ecolorcount = 0; 
    mp_eindexcount = 0;
    mp_enormalcount = 0;
    mp_epatterncount = 0;
    mp_eweightcount = 0;
    mp_evisibilitycount = 0;

    mp_present = 0;
    mp_face_present = 0;

    HC_Open_Geometry (key);
        if ((mp_normalcount = HC_Show_Existence ("vertex normals")) != 0)
            vattribs |= Vertex_Normal;
        if ((mp_paramcount = HC_Show_Existence ("vertex parameters")) != 0) {
            vattribs |= Vertex_Parameter;
			if (tk.GetTargetVersion() >= 1175) {
				int width = 0;

				for (i = 0 ; width == 0 ; i++) {
					HC_Open_Vertex (i);
					HC_Show_Parameter_Size (&width); 
					HC_Close_Vertex();
				}
				//assumes that all vertices will have the same number of parameters
				mp_paramwidth = (char)width;
			}
			else
				mp_paramwidth = 3;

			if (mp_params == null)
				SetVertexParameters (null, mp_paramwidth);
		}
        /* it's impossible to tell at this level what type of color is set.  We can't distinguish
         * between color-by-index and color-by-value, so just set the mask if any colors are present.
         * We'll figure it out more precisely once the vertex is open. */
        if (HC_Show_Existence ("vertex colors"))
            vattribs |= Vertex_Any_Color;
        if ((mp_vmvisibilitycount = HC_Show_Existence ("vertex visibility")) != 0)
            vattribs |= Vertex_Marker_Visibility;
        if ((mp_vmsizecount = HC_Show_Existence ("vertex size")) != 0)
            vattribs |= Vertex_Marker_Size;
        if ((mp_vmsymbolcount = HC_Show_Existence ("vertex symbol")) != 0)
            vattribs |= Vertex_Marker_Symbol;
            
        if (vattribs != Vertex_None) {
            HTK_Named msym(TKE_Marker_Symbol);

            SetExists();
            if (mp_exists == null)
                return tk.Error ("memory allocation failed for vertex existence flags array");
            for (i = 0; i < mp_pointcount; i++) {
                mp_exists[i] = Vertex_None;

                HC_Open_Vertex (i);
                    if (vattribs & Vertex_Any_Color) {
                        if (HC_Show_Existence ("color")) {
                            char            all[256];
                            char            name[64];

                            HC_Show_Color (all);

                            if (strstr (all, "face=") != null) {
                                HC_Show_One_Color ("face", name);
                                if (name[0] == '#') {
                                    if (mp_vfindices == null)
                                        SetVertexFaceIndices();
                                    mp_vfindices[i] = read_float (&name[1]);
                                    mp_vfindexcount++;
                                    mp_exists[i] |= Vertex_Face_Index;
                                }
                                else {
                                    if (mp_vfcolors == null)
                                        SetVertexFaceColors();
                                    HC_Show_One_Color_By_Value ("face", name,
                                                        &mp_vfcolors[3*i+0], &mp_vfcolors[3*i+1], &mp_vfcolors[3*i+2]); 
                                    //HC_Compute_Color_By_Value (name, &vfcptr[3*i], "rgb", &vfcptr[3*i]);  // already rgb for now
                                    mp_vfcolorcount++;
                                    mp_exists[i] |= Vertex_Face_Color;
                                }
                            }
                            if (strstr (all, "edge=") != null) {
                                HC_Show_One_Color ("edge", name);
                                if (name[0] == '#') {
                                    if (mp_veindices == null)
                                        SetVertexEdgeIndices();
                                    mp_veindices[i] = read_float (&name[1]);
                                    mp_veindexcount++;
                                    mp_exists[i] |= Vertex_Edge_Index;
                                }
                                else {
                                    if (mp_vecolors == null)
                                        SetVertexEdgeColors();
                                    HC_Show_One_Color_By_Value ("edge", name,
                                                        &mp_vecolors[3*i+0], &mp_vecolors[3*i+1], &mp_vecolors[3*i+2]); 
                                    //HC_Compute_Color_By_Value (name, &vecptr[3*i], "rgb", &vecptr[3*i]);  // already rgb for now
                                    mp_vecolorcount++;
                                    mp_exists[i] |= Vertex_Edge_Color;
                                }
                            }
                            if (strstr (all, "marker=") != null || strstr (all, "vertex=") != null) {
                                HC_Show_One_Color ("marker", name);
                                if (name[0] == '#') {
                                    if (mp_vmindices == null)
                                        SetVertexMarkerIndices();
                                    mp_vmindices[i] = read_float (&name[1]);
                                    mp_vmindexcount++;
                                    mp_exists[i] |= Vertex_Marker_Index;
                                }
                                else {
                                    if (mp_vmcolors == null)
                                        SetVertexMarkerColors();
                                    HC_Show_One_Color_By_Value ("marker", name,
                                                        &mp_vmcolors[3*i+0], &mp_vmcolors[3*i+1], &mp_vmcolors[3*i+2]); 
                                    //HC_Compute_Color_By_Value (name, &vmcptr[3*i], "rgb", &vmcptr[3*i]);  // already rgb for now
                                    mp_vmcolorcount++;
                                    mp_exists[i] |= Vertex_Marker_Color;
                                }
                            }
                        }

						if (HC_Show_Existence ("vertex marker rgba")) {
                            if (mp_vmrgbas == null)
                                SetVertexMarkerRGBAs();
							HC_MShow_Vertex_Colors_By_Value (mp_key, "vertex", i, 1, &mp_vmrgbas[4*i]);
							if ((mp_exists[i] & Vertex_Marker_Color) != 0) {
								mp_exists[i] &= ~Vertex_Marker_Color;
								--mp_vmcolorcount;
							}
                            mp_vmrgbacount++;
                            mp_exists[i] |= Vertex_Marker_RGBA;
						}
                    }
                    if (vattribs & Vertex_Normal) {
                        if (mp_normalcount == mp_pointcount || HC_Show_Existence ("normal")) {
                            if (mp_normals == null)
                                SetVertexNormals();
                            HC_Show_Net_Normal (&mp_normals[3*i+0], &mp_normals[3*i+1], &mp_normals[3*i+2]); 
                            mp_exists[i] |= Vertex_Normal;
                        }
                    }
                    if (vattribs & Vertex_Parameter) {
                        if (mp_paramcount == mp_pointcount || HC_Show_Existence ("parameter")) {
							if (tk.GetTargetVersion() >= 1175)
								HC_Show_Parameter (null, &mp_params[mp_paramwidth*i]); 
							else {
								float buffer[256];
								buffer[0] = buffer[1] = buffer[2] = 0;
								HC_Show_Parameter (null, buffer); 
								mp_params[mp_paramwidth*i + 0] = buffer[0];
								mp_params[mp_paramwidth*i + 1] = buffer[1];
								mp_params[mp_paramwidth*i + 2] = buffer[2];
							}
                            mp_exists[i] |= Vertex_Parameter;
                        }
                    }
                    if (vattribs & Vertex_Marker_Visibility) {
                        if (mp_vmvisibilitycount == mp_pointcount || HC_Show_Existence ("visibility")) {
                            if (mp_vmvisibilities == null)
                                SetVertexMarkerVisibilities();
                            HC_Show_Visibility (tempstr); 
                            if (strstr (tempstr, "off") != null)
                                mp_vmvisibilities[i] = false;
                            else
                                mp_vmvisibilities[i] = true;
                            mp_exists[i] |= Vertex_Marker_Visibility;
                        }
                    }
                    if (vattribs & Vertex_Marker_Size) {
                        if (mp_vmsizecount == mp_pointcount || HC_Show_Existence ("vertex size")) {
                            if (mp_vmsizes == null)
                                SetVertexMarkerSizes();
                            HC_Show_Marker_Size  (&mp_vmsizes[i]); 
                            mp_exists[i] |= Vertex_Marker_Size;
                        }
                    }
                    if (vattribs & Vertex_Marker_Symbol) {
                        if (mp_normalcount == mp_pointcount || HC_Show_Existence ("marker symbol")) {
                            if (mp_vmsymbols == null)
                                SetVertexMarkerSymbols();
                            msym.Interpret(tk);
							if (msym.GetName() != null) {
								mp_vmsymbols[i] = (unsigned char)0x00FF;
								if (mp_vmsymbolstrings == null)
									SetVertexMarkerSymbolStrings();
								mp_vmsymbolstrings[i] = new char [strlen (msym.GetName())+1];
								strcpy (mp_vmsymbolstrings[i], msym.GetName());
							}
							else
								mp_vmsymbols[i] = (char)msym.GetIndex();
                            mp_exists[i] |= Vertex_Marker_Symbol;
                        }
                    }
                HC_Close_Vertex();
                mp_present |= mp_exists[i];
            }
        }

        if (HC_Show_Existence ("face colors"))
            fattribs |= Face_Any_Color;
        if ((mp_fnormalcount = HC_Show_Existence ("face normals")) != 0)
            fattribs |= Face_Normal;
        if ((mp_fvisibilitycount = HC_Show_Existence ("face visibility")) != 0)
            fattribs |= Face_Visibility;
        if ((mp_fpatterncount = HC_Show_Existence ("face patterns")) != 0)
            fattribs |= Face_Pattern;
        if (fattribs != Face_None) {
            HTK_Enumerated	fpat (TKE_Face_Pattern);
			bool			legacy_numbering = true;

			if (htk.GetHoopsVersion() >= 1350) {
				char		legacy_setting[64];

				HC_Show_One_System_Option ("legacy mesh face numbering", legacy_setting);
				if (legacy_setting[1] == 'f')
					legacy_numbering = false;
			}

            SetFaceExists();
            if (mp_face_exists == null)
                return tk.Error ("memory allocation failed for face existence flags array");
            for (i = 0; i < mp_facecount; i++) {
                mp_face_exists[i] = Face_None;

                if (m_opcode == TKE_Mesh && legacy_numbering) {
                    // convert between sequential numbering and HOOPS' funky mesh face 
                    // numbering scheme if needed
                    row = (i/2)/(mesh_columns-1);
                    col = (i/2)%(mesh_columns-1);
                    face = (row * mesh_columns) + col;
                    if (i & 1) {
                        face = -(face + mesh_columns + 1);
                    }
                }
                else
                    face = i;

                HC_Open_Face (face);
                    if (fattribs & Face_Any_Color) {
                        if (HC_Show_Existence ("color")) {
                            char            all[256];
                            char            name[64];

                            HC_Show_Color (all);

                            if (strstr (all, "face=") != null) {
                                HC_Show_One_Color ("face", name);
                                // if color by index, name[0] will be '#' -- 
                                // see vertex color handling
                                if (name[0] == '#') {
                                    if (mp_findices == null)
                                        SetFaceIndices();
                                    mp_findices[i] = read_float (&name[1]);
                                    mp_findexcount++;
                                    mp_face_exists[i] |= Face_Index;

                                }
                                else {
                                    if (mp_fcolors == null)
                                        SetFaceColors();
                                    HC_Show_One_Color_By_Value ("face", name,
                                                        &mp_fcolors[3*i+0], &mp_fcolors[3*i+1], &mp_fcolors[3*i+2]); 
                                    mp_fcolorcount++;
                                    mp_face_exists[i] |= Face_Color;
                                }
                            }
                        }
                    }
                    if (fattribs & Face_Normal) {
                        if (mp_fnormalcount == mp_facecount || HC_Show_Existence ("normal")) {
                            if (mp_fnormals == null)
                                SetFaceNormals();
                            HC_Show_Net_Normal (&mp_fnormals[3*i+0], &mp_fnormals[3*i+1], &mp_fnormals[3*i+2]); 
                            mp_face_exists[i] |= Face_Normal;
                        }
                    }
                    if (fattribs & Face_Pattern) {
                        if (mp_fpatterncount == mp_facecount || HC_Show_Existence ("face pattern")) {
                            if (mp_fpatterns == null)
                                SetFacePatterns();
                            fpat.Interpret(tk);
                            mp_fpatterns[i] = (char)fpat.GetIndex();
                            mp_face_exists[i] |= Face_Pattern;
                        }
                    }
                    if (fattribs & Face_Visibility) {
                        if (mp_fvisibilitycount == mp_facecount || HC_Show_Existence ("visibility")) {
                            if (mp_fvisibilities == null)
                                SetFaceVisibilities();
                            HC_Show_Visibility (tempstr);
                            if (strstr (tempstr, "off") != null)
                                mp_fvisibilities[i] = false;
                            else
                                mp_fvisibilities[i] = true;
                            mp_face_exists[i] |= Face_Visibility;
                        }
                    }
                HC_Close_Face();
                mp_face_present |= mp_face_exists[i];
            }
        }

        if (HC_Show_Existence ("edge colors"))
            eattribs |= Edge_Any_Color;
        if ((mp_enormalcount = HC_Show_Existence ("edge normals")) != 0)
            eattribs |= Edge_Normal;
        if ((mp_evisibilitycount = HC_Show_Existence ("edge visibility")) != 0)
            eattribs |= Edge_Visibility;
        if ((mp_epatterncount = HC_Show_Existence ("edge patterns")) != 0)
            eattribs |= Edge_Pattern;
        if ((mp_eweightcount = HC_Show_Existence ("edge weights")) != 0)
            eattribs |= Edge_Weight;
        if (eattribs != Edge_None) {
            HTK_Named	epat (TKE_Edge_Pattern);

            SetEdgeExists();
            if (mp_edge_exists == null)
                return tk.Error ("memory allocation failed for edge existence flags array");
            if (mp_edge_enumeration == null)
                EnumerateEdges();
            for (i = 0; i < mp_edgecount; i++) {
                if (mp_edge_exists[i] & Fake_Edge)
                    continue;
                HC_Open_Edge (mp_edge_enumeration[i*2], mp_edge_enumeration[i*2+1]);
                    if (eattribs & Edge_Any_Color) {
                        if (HC_Show_Existence ("color")) {
                            char            all[256];
                            char            name[64];

                            HC_Show_Color (all);

                            if (strstr (all, "edge=") != null) {
                                HC_Show_One_Color ("edge", name);
                                // if color by index, name[0] will be '#' -- 
                                // see vertex color handling
                                if (name[0] == '#') {
                                    if (mp_eindices == null)
                                        SetEdgeIndices();
                                    mp_eindices[i] = read_float (&name[1]);
                                    mp_eindexcount++;
                                    mp_edge_exists[i] |= Edge_Index;

                                }
                                else {
                                    if (mp_ecolors == null)
                                        SetEdgeColors();
                                    HC_Show_One_Color_By_Value ("edge", name,
                                                        &mp_ecolors[3*i+0], &mp_ecolors[3*i+1], &mp_ecolors[3*i+2]); 
                                    mp_ecolorcount++;
                                    mp_edge_exists[i] |= Edge_Color;
                                }
                            }
                        }
                    }
                    if (eattribs & Edge_Normal) {
                        if (mp_enormalcount == mp_edgecount || HC_Show_Existence ("normal")) {
                            if (mp_enormals == null)
                                SetEdgeNormals();
                            HC_Show_Normal  (&mp_enormals[3*i+0], &mp_enormals[3*i+1], &mp_enormals[3*i+2]); 
                            mp_edge_exists[i] |= Edge_Normal;
                        }
                    }
                    if (eattribs & Edge_Visibility) {
                        if (mp_evisibilitycount == mp_edgecount || HC_Show_Existence ("visibility")) {
                            if (mp_evisibilities == null)
                                SetEdgeVisibilities();
                            HC_Show_Visibility (tempstr);
                            if (strstr (tempstr, "off") != null)
                                mp_evisibilities[i] = false;
                            else
                                mp_evisibilities[i] = true;
                            mp_edge_exists[i] |= Edge_Visibility;
                        }
                    }
                    if (eattribs & Edge_Pattern) {
                        if (mp_epatterncount == mp_edgecount || HC_Show_Existence ("edge pattern")) {
                            if (mp_epatterns == null)
                                SetEdgePatterns();
                            epat.Interpret(tk);
							if (epat.GetName() != null) {
								mp_epatterns[i] = (unsigned char)0x00FF;
								if (mp_epatternstrings == null)
									SetEdgePatternStrings();
								mp_epatternstrings[i] = new char [strlen (epat.GetName())+1];
								strcpy (mp_epatternstrings[i], epat.GetName());
							}
							else
								mp_epatterns[i] = (char)epat.GetIndex();
                            mp_edge_exists[i] |= Edge_Pattern;
                        }
                    }
                    if (eattribs & Edge_Weight) {
                        if (mp_eweightcount == mp_edgecount || HC_Show_Existence ("edge weight")) {
                            if (mp_eweights == null)
                                SetEdgeWeights();
                            HC_Show_Edge_Weight  (&mp_eweights[i]); 
                            mp_edge_exists[i] |= Edge_Weight;
                        }
                    }
                HC_Close_Edge();
                mp_edge_present |= mp_edge_exists[i];
            }
        }

    HC_Close_Geometry();

    if (tk.GetTargetVersion() >= 705 && Opcode() != TKE_PolyCylinder) {
        int         lowest, highest, count;
        char        type[32];
        HC_KEY      subkey;

        HC_Show_Region_Range (key, &lowest, &highest);

        if (lowest != 0 || highest != 0) {
            SetFaceRegions();   // allocate space
            HC_MShow_Face_Regions (key, &lowest, GetFaceRegions());
        }

        HC_Open_Geometry (key);
	    HC_Begin_Contents_Search (".", "attributes");
	        HC_Show_Contents_Count (&count);
            if ((mp_num_collection_parts = count) > 0) {
				mp_collection_parts = new BBaseOpcodeHandler *[count];
				HC_Reverse_Contents_Search();
				for (i = 0; i < count; i++) {
					HC_Find_Contents (type, &subkey);
					if (streq (type, "color"))
						mp_collection_parts[i] = new HTK_Color_Composite;
					else if ((status = htk.StringToHandler (type, &mp_collection_parts[i])) == TK_Error)
						break;
					if ((status = mp_collection_parts[i]->Interpret (tk, subkey)) == TK_Error)
						break;
				}
            }
	    HC_End_Contents_Search();
        HC_Close_Geometry();
    }

    if (status != TK_Normal)
        return status;

    if (mp_normalcount || mp_paramcount ||
		mp_vfindexcount || mp_vfcolorcount || 
		mp_veindexcount || mp_vecolorcount || 
		mp_vmindexcount || mp_vmcolorcount || mp_vmrgbacount || 
        mp_vmvisibilitycount || mp_vmsizecount || mp_vmsymbolcount ||
        mp_fcolorcount || mp_findexcount || mp_fpatterncount || mp_fvisibilitycount || mp_fnormalcount ||
        mp_ecolorcount || mp_eindexcount || mp_epatterncount || mp_evisibilitycount || mp_enormalcount || mp_eweightcount ||
        mp_fregions != null || mp_num_collection_parts > 0)
        return TK_Normal;
    else
        return TK_NotFound;
#else
    UNREFERENCED (key);
    UNREFERENCED (mesh_columns);
    return tk.Error (stream_readonly);
#endif
} // end function TK_Polyhedron::Interpret


////////////////////////////////////////

bool HTK_Polyhedron::match_points (Recorded_Instance const * instance, float const * instance_points) {
#ifndef HSTREAM_READONLY
    float           min, max, epsilon;
    int             i;

    // get range of values to determine reasonable epsilon
    min = max = mp_points[0];
    for (i=1; i<3*mp_pointcount; i++) {
        if (mp_points[i] < min)
            min = mp_points[i];
        else if (mp_points[i] > max)
            max = mp_points[i];
    }

    /* tight epsilon for point comparison */
    epsilon = 1.0e-5f * (max - min);

    // use the points matching the instance's basis to construct a corresponding basis
    int             b0 = 3*instance->m_basis_indices[0];
    int             b1 = 3*instance->m_basis_indices[1];
    int             b2 = 3*instance->m_basis_indices[2];
    int             b3 = 3*instance->m_basis_indices[3];
    float           single[3];

    // the simple matrix which transforms the identity to the basis...
    mp_matrix[0]  = mp_points[b1+0] - mp_points[b0+0];
    mp_matrix[1]  = mp_points[b1+1] - mp_points[b0+1];
    mp_matrix[2]  = mp_points[b1+2] - mp_points[b0+2];
    mp_matrix[3]  = 0.0f;
    mp_matrix[4]  = mp_points[b2+0] - mp_points[b0+0];
    mp_matrix[5]  = mp_points[b2+1] - mp_points[b0+1];
    mp_matrix[6]  = mp_points[b2+2] - mp_points[b0+2];
    mp_matrix[7]  = 0.0f;
    mp_matrix[8]  = mp_points[b3+0] - mp_points[b0+0];
    mp_matrix[9]  = mp_points[b3+1] - mp_points[b0+1];
    mp_matrix[10] = mp_points[b3+2] - mp_points[b0+2];
    mp_matrix[11] = 0.0f;
    mp_matrix[12] = mp_points[b0+0];
    mp_matrix[13] = mp_points[b0+1];
    mp_matrix[14] = mp_points[b0+2];
    mp_matrix[15] = 1.0f;

    // now merge in the inverted basis already stored on the instance
    HC_Compute_Matrix_Product (instance->m_local_basis, mp_matrix, mp_matrix);

    // first, a quick check on a single "arbitrary" point
    HC_Compute_Transformed_Points (1, instance->m_arbitrary_point, mp_matrix, single);
    if (fabs (mp_points[3*instance->m_arbitrary_index+0] - single[0]) > epsilon ||
        fabs (mp_points[3*instance->m_arbitrary_index+1] - single[1]) > epsilon ||
        fabs (mp_points[3*instance->m_arbitrary_index+2] - single[2]) > epsilon)
        return false;

    for (i=0; i<mp_pointcount; i++) {
        HC_Compute_Transformed_Points (1, &instance_points[3*i], mp_matrix, single);
        if (fabs (mp_points[3*i+0] - single[0]) > epsilon ||
            fabs (mp_points[3*i+1] - single[1]) > epsilon ||
            fabs (mp_points[3*i+2] - single[2]) > epsilon)
            break;
    }

    if (i < mp_pointcount)  // broke early?
        return false;

    return true;
#else
    UNREFERENCED (instance);
    UNREFERENCED (instance_points);
    return false;
#endif
}

bool HTK_Polyhedron::match_attributes (Recorded_Instance const * instance) {
#ifndef HSTREAM_READONLY
    float               epsilon;
    int                 i;
    bool                matches = true;

    // if ((mp_resent & Vertex_Normal) != 0)
    //    generate adjoint to transform normals

    epsilon = 0.001f;
    HC_Open_Geometry (instance->m_key);
        if (instance->m_variant > 0)
            HC_Open_LOD (instance->m_variant);

        if ((mp_present & ~Vertex_Normal) | mp_face_present | mp_edge_present)
            matches = false;
        if (HC_Show_Existence ("vertex normal") != mp_normalcount)
            matches = false;
        else if (HC_Show_Existence ("face attributes, edge attributes, vertex attributes") != mp_normalcount)
            matches = false;
        else if (mp_present) {
            for (i=0; matches && i<mp_pointcount; i++) {
                HC_Open_Vertex (i);
                    if (HC_Show_Existence ("normal") && (mp_exists[i] & Vertex_Normal) != 0) {
                        float       normal[4];  // allow for a plane, not just a vector

                        HC_Show_Normal (&normal[0], &normal[1], &normal[2]);
                        normal[3] = -(normal[0]*mp_points[3*i+0] + normal[1]*mp_points[3*i+1] + normal[2]*mp_points[3*i+2]);
                        HC_Compute_Transformed_Plane (normal, mp_matrix, normal);

                        if (fabs (normal[0] - mp_normals[3*i+0]) > epsilon ||
                            fabs (normal[1] - mp_normals[3*i+1]) > epsilon ||
                            fabs (normal[2] - mp_normals[3*i+2]) > epsilon)
                            matches = false;
                    }
                    else if ((mp_exists[i] & Vertex_Normal) != 0)
                        matches = false;
                HC_Close_Vertex();
            }
        }

        if (instance->m_variant > 0)
            HC_Close_LOD ();
    HC_Close_Geometry ();

    return matches;
#else
    UNREFERENCED (instance);
    return false;
#endif
}

////////////////////////////////////////////////////////////////////////////////


TK_Status HTK_Mesh::Execute (BStreamFileToolkit & tk) alter {
    TK_Status       status = TK_Normal;     // assume success

    mp_key = HC_KInsert_Mesh (m_rows, m_columns, mp_points);
    if ((status = ((HTK_Polyhedron *)this)->HExecute(tk, m_columns)) != TK_Normal)
            return status;
    set_last_key (tk, mp_key);

    return status;
}


TK_Status HTK_Mesh::Interpret (BStreamFileToolkit & tk, HC_KEY key, int lod) alter {
#ifndef HSTREAM_READONLY
    TK_Status       status = TK_Normal;     // assume success

    HC_Show_Mesh_Size (key, &m_rows, &m_columns);
    SetPoints (m_rows * m_columns);
    HC_Show_Mesh (key, &m_rows, &m_columns, mp_points);

    mp_pointcount = m_rows * m_columns;
    mp_facecount = 2 * (m_rows-1) * (m_columns-1);
    mp_key = key;

    // let the base class have its turn, and decide the flags to use in the subop
    if ((status = ((HTK_Polyhedron *)this)->HInterpret(tk, key, lod, m_columns)) != TK_NotFound) {
        if (status == TK_Error)
            return status;
        else
            mp_subop |= TKSH_HAS_OPTIONALS;
    }

    if ((tk.GetWriteFlags() & TK_Full_Resolution_Vertices) == 0)
        mp_subop |= TKSH_COMPRESSED_POINTS;

    if ((tk.GetWriteFlags() & TK_Disable_Instancing) == 0 && mp_pointcount >= 10 && mp_num_collection_parts == 0)
        Find_Instance (tk, m_rows, m_columns, mp_present);

    return TK_Normal;
#else
    UNREFERENCED (key);
    UNREFERENCED (lod);
    return tk.Error (stream_readonly);
#endif
}


bool HTK_Mesh::Match_Instance (BStreamFileToolkit const & tk, Recorded_Instance alter * instance) alter {
#ifndef HSTREAM_READONLY
    // generate basis for the instance (if needed) and then do precice checks
    int             instance_count;
    float *         instance_points;
    int             rows, columns;

    HC_Show_Mesh_Size (instance->m_key, &rows, &columns);

    instance_count = rows * columns;
    instance_points = new float [3*instance_count];

    HC_Show_Mesh (instance->m_key, &rows, &columns, instance_points);

    if (!instance->basis_valid()) {
        if (!instance->generate_basis (instance_count, instance_points)) {
            delete [] instance_points;
            return false;
        }
    }

    // first the more complex transformed point comparison
    if (!((HTK_Polyhedron *)this)->match_points (instance, instance_points)) {
        delete [] instance_points;
        return false;
    }

    delete [] instance_points;

    // and now the relatively simple attribute comparison
    if (!((HTK_Polyhedron *)this)->match_attributes (instance))
        return false;

    // got one, so set up to use it instead of writing out the whole thing
    int             index;

    if (tk.KeyToIndex (instance->m_key, index) != TK_Normal) {
        tk.Error();
        return false;
    }
    mp_instance = new TK_Instance (index, instance->m_variant, -1, 0, 0, mp_matrix);

    return true;
#else
    UNREFERENCED (tk);
    UNREFERENCED (instance);
    return false;
#endif
}

IMPLEMENT_CLONE (HTK_Mesh);
