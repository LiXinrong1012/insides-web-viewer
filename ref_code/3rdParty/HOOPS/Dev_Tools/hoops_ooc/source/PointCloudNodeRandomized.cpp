/*
 * Copyright (c) 2009 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: PointCloudNodeRandomized.cpp,v 1.7 2009-11-06 02:03:01 chad Exp $
 */

#include "PointCloudNodeRandomized.h"
#include "PointCloudIndex.h"

#include "BStreamFileToolkit.h"

#include "hc.h"

#include <assert.h>

TK_Point_Cloud_Node_Randomized::TK_Point_Cloud_Node_Randomized ( PointCloudIndexNodeData * node_data_in ) {
	m_node_data = node_data_in;
}

TK_Point_Cloud_Node_Randomized::~TK_Point_Cloud_Node_Randomized () {};

TK_Status TK_Point_Cloud_Node_Randomized::Execute ( BStreamFileToolkit & tk ) alter  {
	TK_Status status = TK_Normal;
	unsigned int handled = 0;

	if (mp_pointcount <= 0)
		return tk.Error("Invalid shell");

	HC_KEY shell_key = INVALID_KEY;
	shell_key = HC_KInsert_Shell(mp_pointcount, mp_points, 0, 0);

	if (shell_key == INVALID_KEY)
		return tk.Error("Problem creating shell");

	if (!HasVertexAttributes())
		return TK_Normal;
	
	if (mp_vmcolorcount == mp_pointcount) {
		HC_MSet_Vertex_Colors_By_Value(shell_key, "vertices", 0, "RGB", mp_vmcolorcount, mp_vmcolors);
		handled |= Vertex_Marker_Color;
	}
	if (mp_vmrgbacount == mp_pointcount) {
		HC_MSet_Vertex_Colors_By_Value(shell_key, "vertices", 0, "RGBA", mp_vmrgbacount, mp_vmrgbas);
		handled |= Vertex_Marker_RGBA;
	}
	if (mp_normalcount == mp_pointcount) {
		HC_MSet_Vertex_Normals(shell_key, 0, mp_normalcount, mp_normals);
		handled |= Vertex_Normal;
	}

	HC_Open_Geometry(shell_key);
		for ( int i = 0 ; i < mp_pointcount ; i++ ) {
			if ((mp_exists[i] & ~handled) == Vertex_None)
				continue;

			HC_Open_Vertex(i);
				if (!(handled & Vertex_Marker_Color) && (mp_exists[i] & Vertex_Marker_Color))
					HC_Set_Color_By_Value("vertices", "RGB", mp_vmcolors[3 * i + 0], mp_vmcolors[3 * i + 1], mp_vmcolors[3 * i + 2]);
				if (!(handled & Vertex_Marker_RGBA) && (mp_exists[i] & Vertex_Marker_RGBA))
					HC_MSet_Vertex_Colors_By_Value(shell_key, "vertices", i, "RGBA", 1, &mp_vmrgbas[4 * i]);
				if (!(handled & Vertex_Normal) && (mp_exists[i] & Vertex_Normal))
					HC_Set_Normal(mp_normals[3 * i + 0], mp_normals[3 * i + 1], mp_normals[3 * i + 2]);
			HC_Close_Vertex();
		}
	HC_Close_Geometry();
	
	return status;
}

TK_Status TK_Point_Cloud_Node_Randomized::Interpret ( BStreamFileToolkit & tk, ID_Key key, int variant ) alter {
	TK_Status status = TK_Normal;
	
	if (m_node_data == 0)
		return status;

	tk.SetWriteFlags(TK_Full_Resolution);

	VArray<PCPoint> *point_list;
	
	m_node_data->GetNodePointList(point_list);
	mp_pointcount = point_list->Count();
	assert(mp_pointcount > 0);
#ifdef POINT_CLOUD_RGBA
	mp_vmrgbacount = mp_pointcount;
#else
	mp_vmcolorcount = mp_pointcount;
#endif // POINT_CLOUD_RGBA
	
#ifdef POINT_CLOUD_VERTEX_NORMALS
	mp_normalcount = mp_pointcount;
#endif // POINT_CLOUD_VERTEX_NORMALS
	
	mp_points = new float [3 * mp_pointcount];
#ifdef POINT_CLOUD_RGBA
	mp_vmrgbas = new float [4 * mp_vmrgbacount];
#else
	mp_vmcolors = new float [3 * mp_vmcolorcount];
#endif // POINT_CLOUD_RGBA

#ifdef POINT_CLOUD_VERTEX_NORMALS
	mp_normals = new float [3 * mp_normalcount];
#endif // POINT_CLOUD_VERTEX_NORMALS
	mp_exists = new unsigned int [mp_pointcount];
	
#ifdef POINT_CLOUD_VERTEX_NORMALS
	if (mp_points == 0 || mp_vmcolors == 0 || mp_normals == 0)
#elif defined(POINT_CLOUD_RGBA)
	if (mp_points == 0 || mp_vmrgbas == 0)
#else
	if (mp_points == 0 || mp_vmcolors == 0)
#endif
		return tk.Error("Problem allocating memory for points and/or vertex colors.");
	
	int i;
	for ( i = 0 ; i < mp_pointcount ; i++ ) {
		mp_exists[i] = 0;
		
		mp_points[3 * i + 0] = point_list->GetData(i).pt.x;
		mp_points[3 * i + 1] = point_list->GetData(i).pt.y;
		mp_points[3 * i + 2] = point_list->GetData(i).pt.z;

		
		if (point_list->GetData(i).vfield & PCPOINT_VALIDITY_RGB) {
#ifdef POINT_CLOUD_RGBA
			mp_vmrgbas[4 * i + 0] = (float)point_list->GetData(i).rgb_color.red / 255.0f;
			mp_vmrgbas[4 * i + 1] = (float)point_list->GetData(i).rgb_color.green / 255.0f;
			mp_vmrgbas[4 * i + 2] = (float)point_list->GetData(i).rgb_color.blue / 255.0f;
			mp_vmrgbas[4 * i + 3] = (point_list->GetData(i).intensity - m_node_data->GetMinIntensity()) / (m_node_data->GetMaxIntensity() - m_node_data->GetMinIntensity());
			mp_exists[i] |= Vertex_Marker_RGBA;
#else
			mp_vmcolors[3 * i + 0] = (float)point_list->GetData(i).rgb_color.red / 255.0f;
			mp_vmcolors[3 * i + 1] = (float)point_list->GetData(i).rgb_color.green / 255.0f;
			mp_vmcolors[3 * i + 2] = (float)point_list->GetData(i).rgb_color.blue / 255.0f;
			mp_exists[i] |= Vertex_Marker_Color;
#endif // POINT_CLOUD_RGBA
		}
		else if (point_list->GetData(i).vfield & PCPOINT_VALIDITY_INTENSITY) {
			float scaled_intensity = (point_list->GetData(i).intensity - m_node_data->GetMinIntensity()) / (m_node_data->GetMaxIntensity() - m_node_data->GetMinIntensity());
			mp_vmcolors[3 * i + 0] = scaled_intensity;
			mp_vmcolors[3 * i + 1] = scaled_intensity;
			mp_vmcolors[3 * i + 2] = scaled_intensity;
			mp_exists[i] |= Vertex_Marker_Color;
		}
		else {
			mp_exists[i] &= ~Vertex_Marker_Color;
			mp_vmcolorcount--;
		}

#ifdef POINT_CLOUD_VERTEX_NORMALS
		mp_normals[3 * i + 0] = point_list->GetData(i).normal.x;
		mp_normals[3 * i + 1] = point_list->GetData(i).normal.y;
		mp_normals[3 * i + 2] = point_list->GetData(i).normal.z;

		if (!(fabs(mp_normals[3 * i + 0] - 0.0) < FEPSILON && fabs(mp_normals[3 * i + 1] - 0.0) < FEPSILON && fabs(mp_normals[3 * i + 2] - 0.0) < FEPSILON))
			mp_exists[i] |= Vertex_Normal;
#endif // POINT_CLOUD_VERTEX_NORMALS
	}

	if (mp_vmcolorcount == 0) {
		delete [] mp_vmcolors;
		mp_vmcolors = 0;
	}
	
	return status;
}
