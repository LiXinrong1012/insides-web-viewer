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
// $Header: /files/homes/master/cvs/hoops_master/hoops_stream/source/HPolyPoly.cpp,v 1.18 2010-12-09 01:33:10 covey Exp $
//

#include "HStream.h"
#include "HOpcodeHandler.h"
#include "HPolyPoly.h"
#include "BInternal.h"

static int zabs (int x) { return x < 0 ? -x : x; }	// simple abs() so we don't need or conflict with other forms

//public virtual
TK_Status HTK_PolyPolypoint::Execute (BStreamFileToolkit & tk) alter 
{
    TK_Status       status = TK_Normal;     // assume success
    int i;
    float *ptr;
    HC_KEY key;
    
    ptr = m_points;
    tk.ClearLastKey();

    m_keys = new HC_KEY[m_primitive_count];

    for (i = 0; i < m_primitive_count; i++) {
        if (m_lengths[i] == 2)
            key = HC_KInsert_Line(ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5]);
        else
            key = HC_KInsert_Polyline(m_lengths[i], ptr);
        tk.AppendLastKey(key);
        m_keys[i] = key;
        ptr += 3 * zabs(m_lengths[i]);
    }
    return status;
}

//public virtual
TK_Status HTK_PolyPolypoint::Interpret (BStreamFileToolkit & tk, HC_KEY owner, int lod) alter {
    UNREFERENCED(owner);
    UNREFERENCED(lod);
#ifndef HSTREAM_READONLY
    char tempstr[128];
    char const *filter = "lines, polylines";
    int i, count, flags;
    float *ptr;
    HC_KEY key;

    m_subop = 0;
    flags = tk.GetWriteFlags();
    if (!(flags & TK_Full_Resolution_Vertices))
        m_subop |= TKPP_COMPRESSED;

    if (flags & TK_Global_Quantization &&
        tk.GetWorldBounding() != null) {
        m_subop |= TKPP_GLOBAL_QUANTIZATION;
    }

    m_point_count = 0;
    m_primitive_count = 0;
    HC_Begin_Contents_Search(".", filter);
    HC_Reverse_Contents_Search();
    while (HC_Find_Contents (tempstr, &key)) {
        if (key >= 0)
            continue;

        if (streq(tempstr, "line"))
            m_point_count += 2;
        else if (streq(tempstr, "polyline")) {
            HC_Show_Polyline_Count (key, &count);
			m_point_count += zabs(count);
        }
        m_primitive_count++;
    }
    HC_End_Contents_Search();

    m_keys = new HC_KEY[m_primitive_count];

    if (m_points_allocated < m_point_count)
        SetPoints(m_point_count);
    if (m_lengths_allocated < m_primitive_count)
        SetLengths(m_primitive_count);

    i = 0;
    ptr = m_points;
    tk.ClearLastKey();
    HC_Begin_Contents_Search(".", filter);
    HC_Reverse_Contents_Search();
    while (HC_Find_Contents (tempstr, &key)) {
        if (key >= 0)
            continue;

        m_keys[i] = key;
        if (streq(tempstr, "line")) {
            HC_Show_Line (key, ptr, ptr+1, ptr+2, ptr+3, ptr+4, ptr+5);
            ptr += 6;
            m_lengths[i] = 2;
        }
        else if (streq(tempstr, "polyline")) {
            HC_Show_Polyline (key, &count, ptr);
            ptr += 3 * zabs(count);
            m_lengths[i] = count;
        }
        i++;
        tk.AppendLastKey(key);
    }
    HC_End_Contents_Search();

    return TK_Normal;
#else
    return tk.Error (stream_readonly);
#endif
}

//public virtual
IMPLEMENT_CLONE_OPCODE (HTK_PolyPolypoint);
