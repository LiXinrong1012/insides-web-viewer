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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HoopsSegmentTree.cpp,v 1.183 2010-12-07 21:57:31 nathan Exp $
//
// HoopsSegmentTree.cpp: implementation of the HoopsSegmentTree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HBaseView.h"
#include "HBaseModel.h"
#include "TreeGraph.h"
#include "HoopsSegmentTree.h"
#include "HSelectionSet.h"
#include "HSSelectionSet.h"
#include "vlist.h"
#include "vhash.h"
#include "HModelInfo.h"
#include "HUtilityLocaleString.h"
#include "HSelectionItem.h"
#include "CAppSettings.h"

#define SEGMENTITEM 0
#define GEOMETRYITEM 1
#define ATTRIBUTEITEM 2
#define INCLUDEITEM 3
#define STATICMODELITEM 4
#define SEGMENTGROUPITEM 5
#define REFERENCEGROUPITEM 6

class sii_passthru
{
public:
	sii_passthru() : segments(0), references(0) {}
	~sii_passthru() {delete [] segments; delete [] references;}

	HC_KEY * segments;
	HC_KEY * references;
};

inline static void show_bounding_by_key(HC_KEY key, char * text)
{
	char text2[MVO_BUFFER_SIZE];

	char type[MVO_BUFFER_SIZE];

	HC_Show_Key_Type(key, type);

	if(!(streq(type, "segment") || streq(type, "reference")
		|| streq(type, "shell") || streq(type, "mesh") || 
		streq(type, "polycylinder")))
		return;

	const char * prefix = "Bounding %s";

	HC_Show_Bounding_Info_By_Key(key, text2);

	// try referee
	if (streq(text2, "")) {

		while (streq(text2, "") && streq(type, "reference")) {
			int count;
			HC_Show_Reference_Keys_Count (key, &count);
			if (count == 1) {
				key = HC_KShow_Reference_Geometry(key);
				HC_Show_Key_Type(key, type);
				//only consider types that could have a bounding
				if(streq(type, "segment") || streq(type, "reference")
					|| streq(type, "shell") || streq(type, "mesh") || streq(type, "polycylinder"))
					HC_Show_Bounding_Info_By_Key(key, text2);
			}
			else
				break;
		}

		prefix = "Referee Bounding %s";
	}
	
	if(text2[0]!='\0')
	{
		sprintf(text, prefix, text2);
		
		//cuboid
		if(text2[5]=='c')
		{
			HPoint pt1, pt2;

			HC_Show_Bounding_Cuboid_By_Key(key, &pt1, &pt2);
			sprintf(text2, ": { (%f, %f, %f), (%f, %f, %f) }", 
				pt1.x, pt1.y, pt1.z, pt2.x, pt2.y, pt2.z);
			strcat(text, text2);
		}
		//sphere
		else if(text2[5]=='s')
		{
			HPoint pt;
			float radius;

			HC_Show_Bounding_Sphere_By_Key(key, &pt, &radius);
			sprintf(text2, ": { (%f, %f, %f), radius=%f }", 
				pt.x, pt.y, pt.z, radius);
			strcat(text, text2);
		}
	}
}

inline static void print_segment_contents_geometry(HModelInfo * ModelInfo, TreeGraph * m_pTreeGraph)
{
	char text[4096];
	int triangle_count = ModelInfo->GetTotalTriangles();
	int vertex_count = ModelInfo->GetTotalVertices();
	int face_count = ModelInfo->GetTotalFaces();
	if (face_count || triangle_count || vertex_count)
	{
		char tmp[MVO_BUFFER_SIZE] = {""};
		strcpy(text, "");

		if (face_count)
		{
			sprintf(tmp,"%d faces",face_count);
			strcat(text, tmp);
		}			
		if (triangle_count)
		{
			if(face_count)
				strcat(text, ", ");
			sprintf(tmp,"%d triangles",triangle_count);
			strcat(text, tmp);
		}
		if (vertex_count)
		{
			if(triangle_count || face_count)
				strcat(text, ", ");
			sprintf(tmp,"%d vertices",vertex_count);
			strcat(text, tmp);
		}
		m_pTreeGraph->AddInfoString(text);
	}

	int shell_count = ModelInfo->GetTotalShell();
	if(shell_count)
	{
		sprintf(text, "%d shells", shell_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int mesh_count = ModelInfo->GetTotalMesh();
	if(mesh_count)
	{
		sprintf(text, "%d meshes", mesh_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int polyline_count = ModelInfo->GetTotalPolyline();
	if (polyline_count)
	{
		sprintf(text,"%d polylines",polyline_count);
		m_pTreeGraph->AddInfoString(text);
	}
	int line_count = ModelInfo->GetTotalLine();
	if (line_count)
	{
		sprintf(text,"%d lines",line_count);
		m_pTreeGraph->AddInfoString(text);
	}
	
	int polygon_count = ModelInfo->GetTotalPolygon();
	if(polygon_count)
	{
		sprintf(text, "%d polygons", polygon_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int circle_count = ModelInfo->GetTotalCircle();
	if(circle_count)
	{
		sprintf(text, "%d circles", circle_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int circular_arc_count = ModelInfo->GetTotalCircularArc();
	if(circular_arc_count)
	{
		sprintf(text, "%d circular arcs", circular_arc_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int circular_chord_count = ModelInfo->GetTotalCircularChord();
	if(circular_chord_count)
	{
		sprintf(text, "%d circular chords", circular_chord_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int circular_wedge_count = ModelInfo->GetTotalCircularWedge();
	if(circular_wedge_count)
	{
		sprintf(text, "%d circular wedges", circular_wedge_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int ellipse_count = ModelInfo->GetTotalEllipse();
	if(ellipse_count)
	{
		sprintf(text, "%d ellipses", ellipse_count);
		m_pTreeGraph->AddInfoString(text);
	}
	
	int elliptical_arc_count = ModelInfo->GetTotalEllipticalArc();
	if(elliptical_arc_count)
	{
		sprintf(text, "%d elliptical arcs", elliptical_arc_count);
		m_pTreeGraph->AddInfoString(text);
	}
	
	int image_count = ModelInfo->GetTotalImage();
	if (image_count)
	{
		sprintf(text,"%d images",image_count);
		m_pTreeGraph->AddInfoString(text);
	}			
	
	int marker_count = ModelInfo->GetTotalMarker();
	if (marker_count)
	{
		sprintf(text,"%d markers", marker_count);
		m_pTreeGraph->AddInfoString(text);
	}
	
	int local_light_count = ModelInfo->GetTotalLocalLight();
	if (local_light_count)
	{
		sprintf(text,"%d local lights",local_light_count);
		m_pTreeGraph->AddInfoString(text);
	}
	
	int distant_light_count = ModelInfo->GetTotalDistantLight();
	if (distant_light_count)
	{
		sprintf(text,"%d distant lights", distant_light_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int spot_light_count = ModelInfo->GetTotalSpotLight();
	if (spot_light_count)
	{
		sprintf(text,"%d spot lights", spot_light_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int cutting_plane_count = ModelInfo->GetTotalCuttingPlane();
	if (cutting_plane_count)
	{
		sprintf(text, "%d cutting planes", cutting_plane_count);
		m_pTreeGraph->AddInfoString(text);
	}
	
	int polycylinder_count = ModelInfo->GetTotalPolyCylinders();
	if(polycylinder_count){
		sprintf(text, "%d polycylinders", polycylinder_count);
		m_pTreeGraph->AddInfoString(text);
	}
	
	int cylinder_count = ModelInfo->GetTotalCylinders();
	if(cylinder_count){
		sprintf(text, "%d cylinders", cylinder_count);
		m_pTreeGraph->AddInfoString(text);
	}
	
	int sphere_count = ModelInfo->GetTotalSpheres();
	if(sphere_count){
		sprintf(text, "%d spheres", sphere_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int nurbs_curve_count = ModelInfo->GetTotalNURBSCurves();
	if(nurbs_curve_count){
		sprintf(text, "%d NURBS curves", nurbs_curve_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int nurbs_surface_count = ModelInfo->GetTotalNURBSSurfaces();
	if(nurbs_surface_count){
		sprintf(text, "%d NURBS surfaces", nurbs_surface_count);
		m_pTreeGraph->AddInfoString(text);
	}
	
	int text_count = ModelInfo->GetTotalText();
	if (text_count)
	{
		sprintf(text,"%d text strings",text_count);
		m_pTreeGraph->AddInfoString(text);
	}	
	
	int infinite_line_count = ModelInfo->GetTotalInfiniteLines();
	if(infinite_line_count){
		sprintf(text, "%d infinite lines", infinite_line_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int infinite_ray_count = ModelInfo->GetTotalInfiniteRays();
	if(infinite_ray_count){
		sprintf(text, "%d infinite rays", infinite_ray_count);
		m_pTreeGraph->AddInfoString(text);
	}

}

inline static void print_segment_contents_non_geometry(HModelInfo * ModelInfo, TreeGraph * m_pTreeGraph)
{
	char text[4096];
#ifdef _DEBUG
	int other_count = ModelInfo->GetTotalOthers();
	if(other_count){
		sprintf(text,"%d unhandled type count (FIXME)", other_count);
		m_pTreeGraph->AddInfoString(text);
	}
#endif
	int subsegment_count = ModelInfo->GetTotalSegments();
	int include_count = ModelInfo->GetTotalIncludes();
	int children_count = subsegment_count + include_count;
	if (children_count)
	{
		sprintf(text,"%d child segments (total)",children_count);
		m_pTreeGraph->AddInfoString(text);
	}
	if (subsegment_count)
	{
		sprintf(text,"%d subsegments",subsegment_count);
		m_pTreeGraph->AddInfoString(text);
	}
	if (include_count)
	{
		sprintf(text,"%d includes",include_count);
		m_pTreeGraph->AddInfoString(text);
	}
	int includer_count = ModelInfo->GetTotalIncluders();
	if (includer_count)
	{
		sprintf(text,"%d includers",includer_count);
		m_pTreeGraph->AddInfoString(text);
	}

	int modelling_matrix_count = ModelInfo->GetTotalMatrices();
	if(modelling_matrix_count)
	{
		if(modelling_matrix_count==1)
			sprintf(text,"1 modelling matrix");
		else
			sprintf(text,"%d modelling matrices", modelling_matrix_count);
		m_pTreeGraph->AddInfoString(text);	
	}

	int reference_count = ModelInfo->GetTotalReferences();
	if(reference_count){
		sprintf(text, "%d references", reference_count);
		m_pTreeGraph->AddInfoString(text);
	}
}

void HoopsSegmentTree::VisualizeBoundings(TreeGraphItem * item, HBaseView * m_pView, bool draw_something)
{
	HC_KEY key=(HC_KEY)item->m_pExtraData;
	HC_KEY incl_path[512];
	int incl_count=0;

	if (item->m_pExtraData2 != 0)
		key=(HC_KEY)item->m_pExtraData2;
	
	if(draw_something && item && item->m_pExtraData && key != INVALID_KEY)
	{
		GetKeyList(item, incl_path, incl_count, true);

		m_pView->VisualizeBounding(true, key, incl_count, incl_path);
	}
	else
	{
		m_pView->VisualizeBounding(false);
	}

}


HoopsSegmentTree::HoopsSegmentTree(HBaseView *view, TreeGraph *graph, HC_KEY startkey)
{
	m_pView = view;
	m_pTreeGraph = graph;
	m_AttributeList = new_vlist(malloc, free);
	m_GeometryList = new_vlist(malloc, free);
	m_DefineList = new_vlist(malloc, free);
	m_ShowInfo = false;
	m_VisualizeBoundings = false;
	m_Selection = view->GetSelection();
	m_GeometryAttributeList_Basic = new_vlist(malloc, free);
	m_GeometryAttributeList_User = new_vlist(malloc, free);
	m_GeometryAttributeList_Text = new_vlist(malloc, free);
	m_GeometryAttributeList_Ref = new_vlist(malloc, free);
	
	// synch with set_attribute.c
	vlist_add_last(m_AttributeList,new HoopsAttributeColor);
	vlist_add_last(m_AttributeList,new HoopsAttributeVisibility);
	vlist_add_last(m_AttributeList,new HoopsAttributeSelectability);
	vlist_add_last(m_AttributeList,new HoopsAttributeCallback);
	vlist_add_last(m_AttributeList,new HoopsAttributeRenderingOptions);
	vlist_add_last(m_AttributeList,new HoopsAttributeUserOptions);
	vlist_add_last(m_AttributeList,new HoopsAttributeUnicodeOptions);
	vlist_add_last(m_AttributeList,new HoopsAttributeUserValue);
	vlist_add_last(m_AttributeList,new HoopsAttributeUserIndex);
	vlist_add_last(m_AttributeList,new HoopsAttributeUserData);
	vlist_add_last(m_AttributeList,new HoopsAttributeCamera);
 	vlist_add_last(m_AttributeList,new HoopsAttributeModellingMatrix);
	vlist_add_last(m_AttributeList,new HoopsAttributeTextureMatrix);
	vlist_add_last(m_AttributeList,new HoopsAttributeHeuristics);
	vlist_add_last(m_AttributeList,new HoopsAttributeTextFont);
	vlist_add_last(m_AttributeList,new HoopsAttributeDriverOptions);
	vlist_add_last(m_AttributeList,new HoopsAttributeSystemOptions);
	vlist_add_last(m_AttributeList,new HoopsAttributeHandedness);
	vlist_add_last(m_AttributeList,new HoopsAttributeWindow);
	vlist_add_last(m_AttributeList,new HoopsAttributeClipRegion);
	vlist_add_last(m_AttributeList,new HoopsAttributeVariableEdgeWeight);
	vlist_add_last(m_AttributeList,new HoopsAttributeEdgeWeight);
	vlist_add_last(m_AttributeList,new HoopsAttributeVariableLineWeight);
	vlist_add_last(m_AttributeList,new HoopsAttributeLineWeight);
	vlist_add_last(m_AttributeList,new HoopsAttributeVariableMarkerSize);
	vlist_add_last(m_AttributeList,new HoopsAttributeMarkerSize);
	vlist_add_last(m_AttributeList,new HoopsAttributeCondition);
	vlist_add_last(m_AttributeList,new HoopsAttributeTextAlignment);
	vlist_add_last(m_AttributeList,new HoopsAttributeWindowPattern);
	vlist_add_last(m_AttributeList,new HoopsAttributeLinePattern);
	vlist_add_last(m_AttributeList,new HoopsAttributeEdgePattern);
	vlist_add_last(m_AttributeList,new HoopsAttributeFacePattern);
	vlist_add_last(m_AttributeList,new HoopsAttributeMarkerSymbol);
	vlist_add_last(m_AttributeList,new HoopsAttributeTextPath);
	vlist_add_last(m_AttributeList,new HoopsAttributeTextSpacing);
	vlist_add_last(m_AttributeList,new HoopsAttributeColorMap);
	vlist_add_last(m_AttributeList,new HoopsAttributeGeometryOptions);
	vlist_add_last(m_AttributeList,new HoopsAttributeConditionalAction);

	vlist_add_last(m_GeometryList,new HoopsGeometryShell);
	vlist_add_last(m_GeometryList,new HoopsGeometryPolyline);
	vlist_add_last(m_GeometryList,new HoopsGeometryMarker);
	vlist_add_last(m_GeometryList,new HoopsGeometryCircle);
	vlist_add_last(m_GeometryList,new HoopsGeometryPolygon);
	vlist_add_last(m_GeometryList,new HoopsGeometryCircularChord);
	vlist_add_last(m_GeometryList,new HoopsGeometryCircularArc);
	vlist_add_last(m_GeometryList,new HoopsGeometryCircularWedge);
	vlist_add_last(m_GeometryList,new HoopsGeometryCuttingPlane);
	vlist_add_last(m_GeometryList,new HoopsGeometryNurbsCurve);
	vlist_add_last(m_GeometryList,new HoopsGeometryNurbsSurface);
	vlist_add_last(m_GeometryList,new HoopsGeometryDistantLight);
	vlist_add_last(m_GeometryList,new HoopsGeometryLocalLight);
	vlist_add_last(m_GeometryList,new HoopsGeometrySpotLight);
	vlist_add_last(m_GeometryList,new HoopsGeometryText);
	vlist_add_last(m_GeometryList,new HoopsGeometryImage);
	vlist_add_last(m_GeometryList,new HoopsGeometryEllipse);
	vlist_add_last(m_GeometryList,new HoopsGeometryEllipticalArc);
	vlist_add_last(m_GeometryList,new HoopsGeometryMesh);
	vlist_add_last(m_GeometryList,new HoopsGeometryCylinder);
	vlist_add_last(m_GeometryList,new HoopsGeometryPolyCylinder);
	vlist_add_last(m_GeometryList,new HoopsGeometryLine);
	vlist_add_last(m_GeometryList,new HoopsGeometrySphere);
	vlist_add_last(m_GeometryList,new HoopsGeometryGrid);
	vlist_add_last(m_GeometryList,new HoopsGeometryInfiniteLine);
	vlist_add_last(m_GeometryList,new HoopsGeometryInfiniteRay);

	vlist_add_last(m_DefineList,new HoopsGeometryLocalTextures);
	vlist_add_last(m_DefineList,new HoopsGeometryGlyph);
	vlist_add_last(m_DefineList,new HoopsGeometryLinePattern);
	vlist_add_last(m_DefineList,new HoopsGeometryFont);
	vlist_add_last(m_DefineList,new HoopsNamedStyleDefinition);
	vlist_add_last(m_DefineList,new HoopsShaderDefinition);

	vlist_add_last(m_GeometryAttributeList_Basic,new HoopsAttributeColor);
	vlist_add_last(m_GeometryAttributeList_Basic,new HoopsAttributeGeometryOptions);
	vlist_add_last(m_GeometryAttributeList_Basic,new HoopsAttributeUserValue);
	vlist_add_last(m_GeometryAttributeList_Basic,new HoopsAttributeUserOptions);
	vlist_add_last(m_GeometryAttributeList_Basic,new HoopsAttributeUserIndex);
	vlist_add_last(m_GeometryAttributeList_Basic,new HoopsAttributeUserData);
	vlist_add_last(m_GeometryAttributeList_Basic,new HoopsAttributeUnicodeOptions);

	vlist_add_last(m_GeometryAttributeList_User,new HoopsAttributeUserValue);
	vlist_add_last(m_GeometryAttributeList_User,new HoopsAttributeUserOptions);
	vlist_add_last(m_GeometryAttributeList_User,new HoopsAttributeUnicodeOptions);
	vlist_add_last(m_GeometryAttributeList_User,new HoopsAttributeUserIndex);
	vlist_add_last(m_GeometryAttributeList_User,new HoopsAttributeUserData);
	vlist_add_last(m_GeometryAttributeList_User,new HoopsAttributeGeometryOptions);

	vlist_add_last(m_GeometryAttributeList_Text,new HoopsAttributeTextAlignment);
	vlist_add_last(m_GeometryAttributeList_Text,new HoopsAttributeTextFont);
	vlist_add_last(m_GeometryAttributeList_Text,new HoopsAttributeTextPath);
	vlist_add_last(m_GeometryAttributeList_Text,new HoopsAttributeTextSpacing);
	vlist_add_last(m_GeometryAttributeList_Text,new HoopsAttributeUserValue);
	vlist_add_last(m_GeometryAttributeList_Text,new HoopsAttributeUserOptions);
	vlist_add_last(m_GeometryAttributeList_Text,new HoopsAttributeUserIndex);
	vlist_add_last(m_GeometryAttributeList_Text,new HoopsAttributeUserData);
	vlist_add_last(m_GeometryAttributeList_Text,new HoopsAttributeUnicodeOptions);

	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeColor);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeUserValue);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeUserOptions);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeUserIndex);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeUserData);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeUnicodeOptions);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeModellingMatrix);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeTextAlignment);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeTextFont);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeTextPath);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeTextSpacing);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeMarkerSymbol);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeMarkerSize);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeLineWeight);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeLinePattern);
	vlist_add_last(m_GeometryAttributeList_Ref,new HoopsAttributeVisibility);

	TreeGraphItem *item = m_pTreeGraph->GetRootItem();
	if (startkey == -1)
		startkey = m_pView->GetModelKey();
	item->SetData("model", (void *)startkey); 
	TreeGraphItem *newitem = AddSegmentItem(startkey, m_pTreeGraph->GetRootItem()); 
	if(CAppSettings::DisableEditing)
		newitem->m_Flags = newitem->m_Flags | READONLY_OBJECT;
	VerifyChildren(newitem);
	//ExpandSegmentItem(newitem,startkey); 	
	//newitem->Expand();
	newitem->m_Type = SEGMENTITEM;
	SetItemImage(newitem, newitem->m_Type);
	m_pCurrentItem=newitem;
}

HoopsSegmentTree::~HoopsSegmentTree()
{
	m_pTreeGraph->Flush();

	START_LIST_ITERATION(HoopsAttribute *, m_AttributeList)
		delete temp;
	END_LIST_ITERATION(m_AttributeList);
	delete_vlist(m_AttributeList);
	START_LIST_ITERATION(HoopsGeometry *, m_GeometryList)
		delete temp;
	END_LIST_ITERATION(m_GeometryList);
	START_LIST_ITERATION(HoopsDefineGeometry *, m_DefineList)
		delete temp;
	END_LIST_ITERATION(m_DefineList);
	delete_vlist(m_DefineList);
	delete_vlist(m_GeometryList);

	START_LIST_ITERATION(HoopsAttribute *, m_GeometryAttributeList_Basic)
		delete temp;
	END_LIST_ITERATION(m_GeometryAttributeList_Basic);
	delete_vlist(m_GeometryAttributeList_Basic);

	START_LIST_ITERATION(HoopsAttribute *, m_GeometryAttributeList_User)
		delete temp;
	END_LIST_ITERATION(m_GeometryAttributeList_User);
	delete_vlist(m_GeometryAttributeList_User);

	START_LIST_ITERATION(HoopsAttribute *, m_GeometryAttributeList_Text)
		delete temp;
	END_LIST_ITERATION(m_GeometryAttributeList_Text);
	delete_vlist(m_GeometryAttributeList_Text);

	START_LIST_ITERATION(HoopsAttribute *, m_GeometryAttributeList_Ref)
		delete temp;
	END_LIST_ITERATION(m_GeometryAttributeList_Ref);
	delete_vlist(m_GeometryAttributeList_Ref);
}




static HC_KEY GetItemKey(TreeGraphItem *item)
{
	TreeGraphItem *startitem = item;
	while (!startitem->m_pExtraData || (HC_KEY)startitem->m_pExtraData == -1)
	{
		startitem = startitem->m_pParentItem;
	}
	return (HC_KEY)startitem->m_pExtraData;
}


void HoopsSegmentTree::OnBeforeTextModified(TreeGraphItem *item, const char *text) 
{
	;
}

bool HoopsSegmentTree::IsAttribute(TreeGraphItem *item)
{
	if (!(item->m_pExtraData && (HC_KEY)item->m_pExtraData != -1) && item->m_pItemText2)
	{
		START_LIST_ITERATION(HoopsAttribute, m_AttributeList)	   
			if (strcmp(item->m_pItemText2, temp->GetName()) == 0)
				return true;	
		END_LIST_ITERATION(m_AttributeList);
	}
	return false;
}

bool HoopsSegmentTree::IsDefine(TreeGraphItem *item)
{
	if (item->m_pParentItem && item->m_pParentItem->m_pParentItem)
		if (strcmp(item->m_pParentItem->m_pParentItem->m_pItemText,"DEFINES") == 0)
			return true;

	return false;

}
bool HoopsSegmentTree::IsGeometry(TreeGraphItem *item)
{
	if (item->m_pParentItem && item->m_pParentItem->m_pParentItem)
		if (strcmp(item->m_pParentItem->m_pParentItem->m_pItemText,"GEOMETRY") == 0)
			return true;

	return false;

}

bool HoopsSegmentTree::IsReference(TreeGraphItem *item)
{
	if((item->m_Flags & GEOMETRY_REFERENCE) || (item->m_Flags & SEGMENT_REFERENCE)
		|| streq(item->m_pItemText,"REFERENCES") )
		return true;
	if (item->m_pParentItem)
		if (streq(item->m_pParentItem->m_pItemText,"REFERENCES") )
			return true;

	return false;

}

bool HoopsSegmentTree::IsGeometry(TreeGraphItem *item, const char *text)
{
	if(strstr(item->m_pItemText, "REFERENCE"))
		return true;
	if (item->m_pParentItem && item->m_pParentItem->m_pParentItem)
		if (strcmp(item->m_pParentItem->m_pParentItem->m_pItemText,"GEOMETRY") == 0)
		{
			if (strcmp(item->m_pParentItem->m_pItemText,text) == 0)
				return true;
		}

		return false;

}

bool HoopsSegmentTree::IsInclude(TreeGraphItem *item)
{
	if(item->m_pParentItem &&
		(streq(item->m_pParentItem->m_pItemText,"INCLUDES") ||
		streq(item->m_pParentItem->m_pItemText,"STYLES") ||
		streq(item->m_pParentItem->m_pItemText,"NAMED STYLES")) )
		return true;

	return false;
}

void HoopsSegmentTree::OnTextModified(TreeGraphItem *item, const char *text2) 
{
	char text[MVO_BIG_BUFFER_SIZE];    
	if (text2)
	{
		char *text3 = (char *)text2;
		int i = (int)strlen(text2)-1;
		while (i>=0 &&  (text2[i] == 13 || text2[i] == 10))
			text3[i--] = 0;

		if (item->m_pExtraData && (HC_KEY)item->m_pExtraData != -1)
		{
			if (IsGeometry(item))
			{
				char type[64];
				HC_Show_Key_Type((HC_KEY)item->m_pExtraData, type);
				START_LIST_ITERATION(HoopsGeometry, m_GeometryList)	   
					if (strcmp(item->m_pParentItem->m_pItemText, temp->GetName()) == 0)
					{
						temp->ModifyGeometry((HC_KEY)item->m_pExtraData,text2);
						break;
					}
					END_LIST_ITERATION(m_GeometryList);

			}
			else
				HUtility::RenameSegment((HC_KEY)item->m_pExtraData, text2);	    
			item->ModifyText(text2);
		}
		else if (IsDefine(item))
		{
			char definename[MVO_BUFFER_SIZE];
			strcpy(text,text2);

			strcpy(definename,item->m_pParentItem->m_pItemText);

			START_LIST_ITERATION(HoopsDefineGeometry, m_DefineList)	   
				if (strcmp(definename, temp->GetName()) == 0)
				{
					char name[4096];
					char res[4096];
					HC_Open_Segment_By_Key(GetItemKey(item));
					temp->GetNameAndDefinition(item->m_pItemText, name, res);
					temp->EditDefine(name,text);
					temp->ShowDefine(name,res);
					HC_Close_Segment();
					item->ModifyText(res);
					//		m_pView->Update();
					break;
				}
			END_LIST_ITERATION(m_DefineList);
		}
		else if (item->m_pItemText2)
		{
			FoldAttributeText(text2, text); 
			START_LIST_ITERATION(HoopsAttribute, m_AttributeList)	   
			if (strcmp(item->m_pItemText2, temp->GetName()) == 0)
			{
				HC_KEY item_key=GetItemKey(item);
				bool is_segment=false;
				char type[MVO_BUFFER_SIZE];
				char final[MVO_BIG_BUFFER_SIZE];

				HC_Show_Key_Type(item_key, type);
				if(streq(type, "segment"))
					is_segment=true;
				else if(streq(type, "style"))
				{
					item_key=HC_KShow_Style_Segment(item_key);
					is_segment=true;
				}

				if(is_segment)
					HC_Open_Segment_By_Key(item_key);
				else
					HC_Open_Geometry(item_key);

				if(temp->Exists()) //HC_Show_Existence(temp->GetName()))
					temp->UnSet();
				temp->Set(text);
				
				if(is_segment)
					HC_Close_Segment();
				else
					HC_Close_Geometry();
				
				ExtendAttributeText(temp->GetName(), text, final);

				item->ModifyText(final);
				m_pView->Update();
				break;
			}
			END_LIST_ITERATION(m_AttributeList);
		}
	}

}

/*
void HoopsSegmentTree::UpdateTreeRecursive(TreeGraphItem *item, HC_KEY key)
{
HC_KEY segkey;
char type[MVO_BUFFER_SIZE];
char segname[MVO_BUFFER_SIZE];
HC_Open_Segment_By_Key(key); 
HC_Begin_Contents_Search(".", "segments");
while (HC_Find_Contents(type, &segkey))
{
HC_Show_Segment(segkey, segname);
HC_Parse_String(segname,"/",-1,segname);
TreeGraphItem *newitem = (TreeGraphItem *)item->AddChildItem(segname,0);
RecursiveFillTree(newitem, segkey);

}
HC_End_Contents_Search();
HC_Close_Segment();
}

*/



TreeGraphItem * HoopsSegmentTree::AddSegmentItem(HC_KEY segkey, TreeGraphItem *parent)
{
	char segname[MVO_BUFFER_SIZE];
	TreeGraphItem * ret;
	HC_Show_Segment(segkey, segname);
	if(strlen(segname)>1)
		HC_Parse_String(segname,"/",-1,segname);
	ret = (TreeGraphItem *)parent->AddChildItem(H_TEXT(segname),(void *)segkey);
	ret->m_Flags = parent->m_Flags & READONLY_OBJECT;

#if 0
	// This is a good way to counter the meaninglessness of a segment names in the browser.
	// Basically we can set a pre-defined user option to be used as display name - Rajesh B (26-Sep-06)
	if(use_user_option_as_label)
	{
		HC_Open_Segment_By_Key(segkey);
		if (HC_Show_Existence("user options"))
		{
			HUserOptions h_user_opts;
			h_user_opts.Show_User_Options();
			if (strstr(h_user_opts.m_data, "_name") != 0)
				HC_Show_One_User_Option("_name", segname);
		}
		HC_Close_Segment();
	}
#endif

	return ret;
}

TreeGraphItem * HoopsSegmentTree::AddGeometryItem(HC_KEY geokey, TreeGraphItem *parent, HoopsGeometry *geomType)
{
	char text[MVO_BUFFER_SIZE];	
	char text2[MVO_BUFFER_SIZE];
	geomType->GetData(geokey, text2);
	sprintf(text, "%X - %s", geokey, text2);
	TreeGraphItem *newitem = (TreeGraphItem *)parent->AddChildItem(H_TEXT(text),(void *)geokey);
	newitem->m_Type = GEOMETRYITEM;
	SetItemImage(newitem, newitem->m_Type);
	if(HC_Show_Existence_By_Key(geokey, "attributes"))
		newitem->SetHasChildren(true);
	return newitem;
}

TreeGraphItem * HoopsSegmentTree::AddStaticModelItem(HC_KEY key, TreeGraphItem *parent)
{
	TreeGraphItem * ret=parent->AddChildItem(_T("STATIC_TREE"),0, false);
	int found=0;
	char type[MVO_BUFFER_SIZE];
	
	ret->m_Flags=STATIC_MODEL | READONLY_OBJECT;

	HC_Open_Segment_By_Key(key);
		HC_Begin_Contents_Search(".", "static model");
			found = HC_Find_Contents (type, &key);
		HC_End_Contents_Search ();
	HC_Close_Segment();

	HC_Open_Segment_By_Key(key);
		key=HC_KCreate_Segment(".");
	HC_Close_Segment();

	memcpy(&(ret->m_pExtraData), &key, sizeof(HC_KEY));
	
	return ret;
}

void HoopsSegmentTree::AddSegmentReference(HC_KEY key, TreeGraphItem *parent)
{
	char segname[MVO_BUFFER_SIZE];
	char info_text[MVO_BUFFER_SIZE];
	char* refname=segname;
	int i=0, min_slash=3;
	HC_KEY seg_key=HC_KShow_Reference_Geometry(key);
	HC_Show_Segment(seg_key, segname);
	while(i<min_slash)
	{		
		if(*refname == '\0')
		{
			//we've gone too far.  
			//start over and don't look as far.
			refname=segname;
			i=0;
			--min_slash;
		}			
		if(*refname == '/')
			++i;		
		++refname;
	}

	bool children_found = false;

	sprintf(info_text, "%s\nKey: %X", refname, key);
	TreeGraphItem *newitem = (TreeGraphItem *)parent->AddChildItem(H_TEXT(info_text),(void *)key);
	newitem->m_Flags=SEGMENT_REFERENCE | (parent->m_Flags & READONLY_OBJECT);
	newitem->m_Type = SEGMENTITEM;
	SetItemImage(newitem, newitem->m_Type);
	
	HC_Open_Geometry(key);
		START_LIST_ITERATION(HoopsAttribute, m_GeometryAttributeList_Ref)	   
			if (temp->Exists())
			{
				children_found = true;
				break;
			}
		END_LIST_ITERATION(m_GeometryAttributeList_Ref);
	HC_Close_Geometry();
	HC_Open_Segment_By_Key(seg_key);
		START_LIST_ITERATION(HoopsGeometry, m_GeometryList)	   
			if (temp->Exists())
			{
				children_found = true;
				break;
			}
		END_LIST_ITERATION(m_GeometryList);
		if (HC_Show_Existence("reference")) 
			children_found = true;
	HC_Close_Segment();	

	if(children_found)
		newitem->SetHasChildren(true);
}

void HoopsSegmentTree::AddDummyGeometry(HC_KEY key, TreeGraphItem *parent, HoopsGeometry *geomType)
{
	char text[MVO_BUFFER_SIZE];

	if(geomType)
	{
		char text2[MVO_BUFFER_SIZE];

		geomType->GetData(key, text2);
		sprintf(text, "%X - %s - %s", key, geomType->GetName(), text2);
	}
	else
	{
		sprintf(text, "%X - Unknown Geometry", key);
	}
	
	TreeGraphItem *newitem = (TreeGraphItem *)parent->AddChildItem(H_TEXT(text),(void *)key);
	newitem->m_Flags=GEOMETRY_REFERENCE | (parent->m_Flags & READONLY_OBJECT);
	newitem->m_Type = GEOMETRYITEM;
	SetItemImage(newitem, newitem->m_Type);
}



void HoopsSegmentTree::AddGeometryReference(HC_KEY key, TreeGraphItem *parent)
{
	bool children_found = false;
	char text[MVO_BUFFER_SIZE];
	int key_count = 0;
	HC_KEY geo_key;
	
	HC_Show_Reference_Keys_Count(key, &key_count);
	if(key_count > 0)
	{
		HC_KEY * ref_keys = new HC_KEY [key_count];
		HC_Show_Reference_Keys(key, &key_count, ref_keys);

		for(int i=0; i<key_count; ++i)
		{
			HoopsGeometry *geomType=0;
			HoopsReference maybe;
			TreeGraphItem *newitem;
			int j;
			char type [MVO_BUFFER_SIZE];
			geo_key=ref_keys[i];

			HC_Show_Key_Type(geo_key, type);
			for(j=0; j<(int)strlen(type); ++j)
				type[j]=toupper(type[j]);

			START_LIST_ITERATION(HoopsGeometry, m_GeometryList)	   
				if(streq(type, temp->GetName()))
				{
					geomType=temp;
					break;
				}
			END_LIST_ITERATION(m_GeometryList);

			if(!geomType && streq(type, "REFERENCE"))
				geomType = &maybe;

			if(geomType)
			{
				char text2[MVO_BUFFER_SIZE];

				geomType->GetData(geo_key, text2);
				sprintf(text, "%X - %s - %s", geo_key, geomType->GetName(), text2);
			}
			else
			{
				sprintf(text, "%X - Unknown Geometry", geo_key);
			}
			
			if(streq(type, "REFERENCE"))
				newitem = (TreeGraphItem *)parent->AddChildItem(H_TEXT(text),(void *)geo_key);
			else
				newitem = (TreeGraphItem *)parent->AddChildItem(H_TEXT(text),(void *)key);
			newitem->m_pExtraData2 = (void*)geo_key;
			newitem->m_Flags=GEOMETRY_REFERENCE | (parent->m_Flags & READONLY_OBJECT);
			newitem->m_Type = GEOMETRYITEM;
			SetItemImage(newitem, newitem->m_Type);

			if (streq(type, "REFERENCE")) {
				HC_Open_Geometry(key);
					START_LIST_ITERATION(HoopsAttribute, m_GeometryAttributeList_Ref)	   
						if (temp->Exists())
						{
							children_found = true;
							break;
						}
					END_LIST_ITERATION(m_GeometryAttributeList_Ref);
				HC_Close_Geometry();	
			}

			if(children_found || (geomType && streq(geomType->GetName(), "REFERENCE")))
				newitem->SetHasChildren(true);
		}
		delete [] ref_keys;
	}
}

void HoopsSegmentTree::AddSegmentGroupItem(int low, int high, TreeGraphItem *parent, void * pt)
{
	char text[MVO_BUFFER_SIZE];

	sprintf(text, "SEGMENTS %d-%d", low, high);
	
	TreeGraphItem *newitem = (TreeGraphItem *)parent->AddChildItem(H_TEXT(text), 0);
	newitem->m_Flags= parent->m_Flags & READONLY_OBJECT;
	newitem->SetHasChildren(true);
	newitem->m_Type = SEGMENTGROUPITEM;
	SetItemImage(newitem, newitem->m_Type, pt);
}

void HoopsSegmentTree::AddReferenceGroupItem(int low, int high, TreeGraphItem *parent, void * pt)
{
	char text[MVO_BUFFER_SIZE];

	sprintf(text, "REFERENCES %d-%d", low, high);
	
	TreeGraphItem *newitem = (TreeGraphItem *)parent->AddChildItem(H_TEXT(text), 0);
	newitem->m_Flags= parent->m_Flags & READONLY_OBJECT;
	newitem->SetHasChildren(true);
	newitem->m_Type = REFERENCEGROUPITEM;
	SetItemImage(newitem, newitem->m_Type, pt);
}

void HoopsSegmentTree::AddIncludeItem(HC_KEY segkey, TreeGraphItem *parent)
{
	char text[MVO_BUFFER_SIZE];
	char text2[MVO_BUFFER_SIZE];
	char type[MVO_BUFFER_SIZE];
	char condition [MVO_BUFFER_SIZE];
	bool has_children = true;
	HC_Open_Segment_By_Key((HC_KEY)parent->m_pParentItem->m_pExtraData);
		HC_Show_Key_Type(segkey, type);
		if(streq(type, "include"))
			HC_Show_Conditional_Include(segkey, text2, condition);	
		if(streq(type, "named style"))
		{
			HC_Show_Named_Style_Segment(segkey, text2);
			condition[0] = '\0';
			has_children = false;
		}
		else
			HC_Show_Conditional_Style(segkey, text2, condition);
	HC_Close_Segment();

	if(condition[0] == '\0')
		sprintf(text, "%X - %s", segkey, text2);
	else
		sprintf(text, "%X - %s (Condition: %s)", segkey, text2, condition);
	TreeGraphItem *newitem = (TreeGraphItem *)parent->AddChildItem(H_TEXT(text),(void *)segkey);
	newitem->SetHasChildren(has_children);
	newitem->m_Flags = parent->m_Flags & READONLY_OBJECT;
	newitem->m_Type = INCLUDEITEM;
	SetItemImage(newitem, newitem->m_Type);
}


bool HoopsSegmentTree::SegmentsExist(TreeGraphItem *item)
{		
	bool found = false;
	char type[MVO_BUFFER_SIZE];
	HC_KEY key;
	HC_Open_Segment_By_Key((HC_KEY)item->m_pExtraData);
	HC_Begin_Contents_Search(".", "segments");
	if (HC_Find_Contents(type, &key))
		found = true;
	HC_End_Contents_Search();
	HC_Close_Segment();
	return found;
}
static HC_KEY ResolveKey(HC_KEY key)
{
	char type[MVO_BUFFER_SIZE];
	HC_Show_Key_Type(key, type);
	if (strcmp(type, "segment") == 0)
		return key;
	else
		return key;
}

bool HoopsSegmentTree::GeometryExists(TreeGraphItem *item)
{
	bool found = false;

	HC_Open_Segment_By_Key(ResolveKey((HC_KEY)item->m_pExtraData));
	START_LIST_ITERATION(HoopsGeometry, m_GeometryList)	   
		if (temp->Exists())
		{
			found = true;
			break;
		}
	END_LIST_ITERATION(m_GeometryList);
	HC_Close_Segment();
	return found;

}
bool HoopsSegmentTree::DefinesExists(TreeGraphItem *item)
{	
	bool found = false;

	HC_Open_Segment_By_Key(ResolveKey((HC_KEY)item->m_pExtraData));
		START_LIST_ITERATION(HoopsGeometry, m_DefineList)	   
			if (temp->Exists())
			{
				found = true;
				break;
			}
		END_LIST_ITERATION(m_DefineList);
	HC_Close_Segment();
	
	return found;
}


bool HoopsSegmentTree::IncludesExist(TreeGraphItem *item)
{
	bool found = false;
	HC_Open_Segment_By_Key(ResolveKey((HC_KEY)item->m_pExtraData));
	if (HC_Show_Existence("includes")) 
		found = true;
	HC_Close_Segment();
	return found;

}

bool HoopsSegmentTree::StylesExist(TreeGraphItem *item)
{
	bool found = false;
	HC_Open_Segment_By_Key(ResolveKey((HC_KEY)item->m_pExtraData));
	if (HC_Show_Existence("styles")) 
		found = true;
	HC_Close_Segment();
	return found;

}

bool HoopsSegmentTree::NamedStylesExist(TreeGraphItem *item)
{
	bool found = false;
	HC_Open_Segment_By_Key(ResolveKey((HC_KEY)item->m_pExtraData));
	if(HC_Show_Existence("named style")) 
		found = true;
	HC_Close_Segment();
	return found;
}

bool HoopsSegmentTree::StaticModelsExist(TreeGraphItem *item)
{
	bool found = false;
	HC_Open_Segment_By_Key(ResolveKey((HC_KEY)item->m_pExtraData));
	if (HC_Show_Existence("static model")) 
		found = true;
	HC_Close_Segment();
	return found;
}

bool HoopsSegmentTree::ReferencesExist(TreeGraphItem *item)
{
	bool found = false;
	HC_Open_Segment_By_Key(ResolveKey((HC_KEY)item->m_pExtraData));
	if (HC_Show_Existence("reference")) 
		found = true;
	HC_Close_Segment();
	return found;
}

bool HoopsSegmentTree::GeometryReferencesExist(TreeGraphItem *item)
{
	bool found = false;
	char type[MVO_BUFFER_SIZE];
	HC_KEY key;

	HC_Open_Segment_By_Key(ResolveKey((HC_KEY)item->m_pExtraData));
	HC_Begin_Contents_Search(".", "reference");
		while(HC_Find_Contents(type, &key))
		{
			key=HC_KShow_Reference_Geometry(key);
			HC_Show_Key_Type(key, type);
			if(!streq(type, "segment"))
			{
				found = true;
				break;
			}
		}
	HC_End_Contents_Search();
	HC_Close_Segment();
	return found;
}


bool HoopsSegmentTree::SegmentReferencesExist(TreeGraphItem *item)
{
	bool found = false;
	char type[MVO_BUFFER_SIZE];
	HC_KEY key;

	HC_Open_Segment_By_Key(ResolveKey((HC_KEY)item->m_pExtraData));
	HC_Begin_Contents_Search(".", "reference");
		while(HC_Find_Contents(type, &key))
		{
			key=HC_KShow_Reference_Geometry(key);
			HC_Show_Key_Type(key, type);
			if(streq(type, "segment"))
			{
				found = true;
				HC_End_Contents_Search();
				HC_Close_Segment();
				return found;
			}
		}
	HC_End_Contents_Search();
	HC_Close_Segment();
	return found;
}


bool HoopsSegmentTree::AttributesExist(TreeGraphItem *item)
{
	bool found = false;
	HC_Open_Segment_By_Key(ResolveKey((HC_KEY)item->m_pExtraData));
	START_LIST_ITERATION(HoopsAttribute, m_AttributeList)	   
		if (temp->Exists())
		{
			found = true;
			break;
		}
	END_LIST_ITERATION(m_AttributeList);
	HC_Close_Segment();
	return found;
}



bool HoopsSegmentTree::AnythingExists(TreeGraphItem *item)
{		
	bool found = false;
	char type[MVO_BUFFER_SIZE];
	HC_KEY key;

	HC_Open_Segment_By_Key((HC_KEY)item->m_pExtraData);
	HC_Begin_Contents_Search(".", "everything, first match");
	if (HC_Find_Contents(type, &key))
		found = true;
	HC_End_Contents_Search();
	HC_Close_Segment();
	return found;
}

void HoopsSegmentTree::VerifyChildren(TreeGraphItem *item)
{
	if (AnythingExists(item))
		item->SetHasChildren(true);
	else
		item->SetHasChildren(false);
	SetItemImage(item, item->m_Type);
}

bool HoopsSegmentTree::HasSelectedChildren(HC_KEY startkey)
{
	bool found = false;

	for (unsigned int i=0;i<m_Selection->GetSize();i++)
	{

		HSmartSelItem *sitem = (HSmartSelItem *)m_Selection->GetSelectionItemAt(i);
		HC_KEY *keys = new HC_KEY[sitem->GetIncludeCount()];
		const HC_KEY *oldkeys = sitem->GetIncludeKeys();
		for (int i=0;i<sitem->GetIncludeCount();i++)
		{
			keys[i] = oldkeys[sitem->GetIncludeCount()-1-i];
		}

		if (HUtility::BuildIncludePath(sitem->GetKey(), keys,sitem->GetIncludeCount(),0,0,startkey))
		{
			delete [] keys;
			found = true;
			break;
		}
		else
		{
			found = false;
			delete [] keys;
		}

	}
	return found;
}



void HoopsSegmentTree::SetItemImage(TreeGraphItem *item, int type, void * pt)
{
	int finalimage = -1;
	
    if (item->m_pExtraData && (type == GEOMETRYITEM || type == SEGMENTITEM) && (HC_KEY)item->m_pExtraData != INVALID_KEY)
	{
		char ctype[64];
		if (!HC_Show_Existence_By_Key((HC_KEY)item->m_pExtraData, "self"))
		{
			OnItemExpanding(item->m_pParentItem, true);
			return;
		}
		HC_Show_Key_Type((HC_KEY)item->m_pExtraData, ctype);
		if (strcmp(ctype, "include") == 0 || strstr(ctype,"style"))
			return;

		if(strcmp(item->m_pItemText, "REFERENCES")==0)
			finalimage = 5;
		else if (item->m_pParentItem && !item->m_pParentItem->m_pExtraData && !strstr(item->m_pParentItem->m_pItemText, "SEGMENTS"))
		{

			if ((HC_KEY)item->m_pExtraData != -1)
			{
				HC_KEY keys[256];
				int keynum;
				GetKeyList(item, keys, keynum);
				if (m_Selection->HSelectionSet::IsSelected((HC_KEY)item->m_pExtraData, keynum, keys))
					finalimage = 6;
				else
					finalimage = 3;
			}
			else
				finalimage = 3;
		}
		else
		{
			HC_KEY keys[256];
			int keynum;
			GetKeyList(item, keys, keynum);
			if (m_Selection->HSelectionSet::IsSelected((HC_KEY)item->m_pExtraData, keynum, keys))
			{
				finalimage = 2;
			}
			else
			{ 
				if(type == GEOMETRYITEM)
				{
					finalimage = 3;
				}
				else 
				{
					if (HasSelectedChildren((HC_KEY)item->m_pExtraData))
						finalimage = 2; 
					else
						finalimage = 1;
				}
			}
		}
	}
	else
	{
		if (type == GEOMETRYITEM)
			finalimage = 3;
		else if (type == ATTRIBUTEITEM)
			finalimage = 4;
		else if (type == STATICMODELITEM)
		{
			if(strcmp(item->m_pItemText, "STATIC_TREE")==0)
				finalimage = 12;
			else
				finalimage = 13;
		}
		else if (type == INCLUDEITEM)
		{
			char type[64];
			if (item->m_pExtraData)
			{
				HC_Open_Segment_By_Key((HC_KEY)item->m_pParentItem->m_pParentItem->m_pExtraData);		    
				HC_Show_Key_Type((HC_KEY)item->m_pExtraData, type);
				if (strcmp(type, "include") == 0)
					finalimage = 5;
				else
					finalimage = 13;
				HC_Close_Segment();
			}
			else
				finalimage = 5;
		}
		else if(type == SEGMENTGROUPITEM)
		{
			int low=0, high=0;
			HC_KEY parent_key = (HC_KEY)item->m_pParentItem->m_pExtraData;
			bool found_selection = false;

			if(m_Selection->GetSize())
			{
				int num = 0, i=0;
				HC_KEY * seg_list = 0;
				sii_passthru * cache = (sii_passthru *)pt;

				sscanf(item->m_pItemText, "SEGMENTS %d-%d", &low, &high);
				low--;

				if(cache && cache->references)
					seg_list = cache->references;
				else
				{
					HC_Open_Segment_By_Key(parent_key);
						HC_Begin_Contents_Search(".", "segments");
							HC_Show_Contents_Count(&num);
							seg_list = new HC_KEY[num];
							while(HC_Find_Contents(0, &seg_list[i++]));
						HC_End_Contents_Search();
					HC_Close_Segment();
					if(cache)
						cache->references = seg_list;
				}

				for(i=low; i<high; ++i)
				{
					if(m_Selection->HSelectionSet::IsSelected(seg_list[i]) || HasSelectedChildren(seg_list[i]))
					{
						found_selection = true;
						break;
					}
				}
			}

			if (found_selection)
				finalimage = 7;
			else
				finalimage = 15;
		}
		else if(type == REFERENCEGROUPITEM)
		{
			int low=0, high=0;
			HC_KEY parent_key = (HC_KEY)item->m_pParentItem->m_pParentItem->m_pParentItem->m_pExtraData;
			bool found_selection = false;

			if(m_Selection->GetSize())
			{
				int num = 0, i=0;
				HC_KEY * ref_list = 0;
				sii_passthru * cache = (sii_passthru *)pt;

				sscanf(item->m_pItemText, "REFERENCES %d-%d", &low, &high);
				low--;

				if(cache && cache->references)
					ref_list = cache->references;
				else
				{
					HC_Open_Segment_By_Key(parent_key);
						HC_Begin_Contents_Search(".", "references");
							HC_Show_Contents_Count(&num);
							ref_list = new HC_KEY[num];
							while(HC_Find_Contents(0, &ref_list[i++]));
						HC_End_Contents_Search();
					HC_Close_Segment();
					if(cache)
						cache->references = ref_list;
				}

				for(i=low; i<high; ++i)
				{
					if(m_Selection->HSelectionSet::IsSelected(ref_list[i]))
					{
						found_selection = true;
						break;
					}
				}
			}

			if (found_selection)
				finalimage = 7;
			else
				finalimage = 15;
		}
	}

	if(item->m_Flags) 
	{
		if(item->m_Flags & STATIC_MODEL)
			finalimage = 12;
		else if(item->m_Flags & SEGMENT_REFERENCE)
			finalimage = 1;
		else if(item->m_Flags & GEOMETRY_REFERENCE)
			finalimage = 3;
	}

	if (finalimage != -1)
		item->SetImage(finalimage);

}    

void HoopsSegmentTree::ExpandByKeyList(HC_KEY *keys, int keynum)
{
	ExpandByKeyListInternal(GetRootItem(), keys, keynum, 0);
}

void HoopsSegmentTree::ExpandByKeyListInternal(TreeGraphItem * startitem, HC_KEY *keys, int keynum, int keypos)
{
	if (!startitem->IsExpanded())
	{
		OnItemExpanding(startitem, true);
		startitem->Expand();
	}

	if (keynum <= keypos)
		return;

	struct vlist_s*	childList = startitem->m_ChildItemList;
	bool is_segment=false;
	char type[64];
	char targettype[64];

	if((startitem->m_pExtraData) && ((HC_KEY)startitem->m_pExtraData != INVALID_KEY))
	{
		HC_Show_Key_Type((HC_KEY)startitem->m_pExtraData, type);
		if(streq(type, "segment"))
		{
			HC_Open_Segment_By_Key((HC_KEY)startitem->m_pExtraData);
			is_segment=true;
		}
		for(int i=keypos; i<keynum-1; ++i)
		{
			if((HC_KEY)startitem->m_pExtraData==keys[i])
			{
				keypos=i+1;
				break;
			}
		}
	}

	HC_Show_Key_Type(HC_KShow_Original_Key(keys[keypos]), targettype);

	TreeGraphItem *temp2;
	START_LIST_ITERATION(TreeGraphItem, childList)
		if (streq(temp->m_pItemText, "INCLUDES") && streq(targettype, "include"))
			ExpandByKeyListInternal(temp, keys, keynum, keypos); 
		else if((streq(temp->m_pItemText, "REFERENCES") || streq(temp->m_pItemText, "SEGMENT_REF"))
			&& streq(targettype, "reference") )
			ExpandByKeyListInternal(temp, keys, keynum, keypos);
		else if(streq(temp->m_pItemText, "GEOMETRY_REF") && streq(targettype, "reference") )
			ExpandByKeyListInternal(temp, keys, keynum, keypos+1);
		else if(strstr(temp->m_pItemText, "SEGMENTS") && streq(targettype, "segment") )
		{
			int low, high, counter = 0;
			HC_KEY search_key, parent_key = (HC_KEY)temp->m_pParentItem->m_pExtraData;
		
			sscanf(temp->m_pItemText, "SEGMENTS %d-%d", &low, &high);
			
			//find which file cabinet to look in.
			HC_Open_Segment_By_Key(parent_key);
				HC_Begin_Contents_Search(".", "segments");
					while(HC_Find_Contents(0, &search_key))
					{
						++counter;
						if(search_key == keys[keypos])
							break;
					}
				HC_End_Contents_Search();
			HC_Close_Segment();

			if(low <= counter && counter <= high)
				ExpandByKeyListInternal(temp, keys, keynum, keypos);
			else
			{
				VLIST_ADVANCE_CURSOR(&childList->cursor);
				continue;
			}
		}
		temp2 = temp;
		if (temp->m_pExtraData)
		{
			HC_Show_Key_Type((HC_KEY)temp->m_pExtraData, type);
			//The "static model" case must come before the "segment" case because 
			//the key type stored on the STATIC_TREE object will be of type "segment."
			if(streq(targettype, "static model") && streq(temp->m_pItemText, "STATIC_TREE"))
			{
				HC_KEY tree_seg_key;
				HC_Open_Segment_By_Key(keys[keypos]);
					tree_seg_key = HC_KCreate_Segment(".");
				HC_Close_Segment();

				if((HC_KEY)temp->m_pExtraData == tree_seg_key)
					ExpandByKeyListInternal(temp, keys, keynum, keypos+1);
			}
			else if (streq(type, "segment") || streq(type, "include"))
			{
				if ((HC_KEY)temp->m_pExtraData == keys[keypos])
					ExpandByKeyListInternal(temp, keys, keynum, keypos+1);
			}
			else if(streq(type, "reference"))
			{
				//gobble up the reference key as well as the segment that it references
				if ((HC_KEY)temp->m_pExtraData == keys[keypos])
					ExpandByKeyListInternal(temp2, keys, keynum, keypos+2);
				else
				{
					HC_KEY this_ref_key = (HC_KEY)temp2->m_pExtraData;
					HC_KEY * ref_keys;
					int ref_count;

					HC_Show_Reference_Keys_Count(this_ref_key, &ref_count);
					if(ref_count > 0)
					{
						ref_keys = new HC_KEY[ref_count];
						HC_Show_Reference_Keys(this_ref_key, 0, ref_keys);
						
						for(int i=0; i<ref_count; ++i)
						{
							if (ref_keys[i] == keys[keypos])
							{			
								OnItemExpanding(temp2, true);
								temp2->Expand();
								break;
							}
						}

						delete [] ref_keys;
					}
				}
			}
		}
		else
		{
			if (streq(temp->m_pItemText, "GEOMETRY"))
			{
				//note that this inner list walk will bash the temp variable
				//references to the temp variable in the outer scope should be referred to temp2
				START_LIST_ITERATION(HoopsGeometry, m_GeometryList )
					char typelower[4096];
					const char *notlower = temp->GetName();
					for (unsigned int j=0;j<strlen(notlower);j++)
						typelower[j] = tolower(notlower[j]);
					typelower[strlen(notlower)] = 0;

					if (streq(targettype, typelower))
					{
						ExpandByKeyListInternal(temp2, keys, keynum, keypos); 				
						break;
					}
				END_LIST_ITERATION(m_GeometryList);

			}
			else
			{
				char typelower[4096];
				const char *notlower = temp2->m_pItemText;
				for (unsigned int j=0;j<strlen(notlower);j++)
					typelower[j] = tolower(notlower[j]);
				typelower[strlen(notlower)] = 0;

				if (streq(targettype, typelower))
				{
					OnItemExpanding(temp2, true);
					temp2->Expand();
					break;
				}
			}

		}			
	END_LIST_ITERATION(childList);

	if(is_segment)
		HC_Close_Segment();

}

static bool ReplaceStringIgnoreSpace(const char *searchtext, const char *comparestring,  const char *replacestring, char *result)
{

	char text[MVO_BUFFER_SIZE];
	char newstring1[MVO_BUFFER_SIZE];
	char newstring2[MVO_BUFFER_SIZE];
	int indexlist1[MVO_BUFFER_SIZE];
	strcpy(text, searchtext);
	int oldindex = 0;
	bool found = false;
	while (1)
	{	

		unsigned int j=0,i;
		for (i=0;i<=strlen(text);i++)
		{
			if (text[i]!=' ')
			{
				newstring1[j] = text[i];
				indexlist1[j] = i;
				j++;
			}

		}

		int k=0;
		for (i=0;i<=strlen(comparestring);i++)
		{
			if (comparestring[i]!=' ')
			{
				newstring2[k] = comparestring[i];
				k++;
			}

		}
		char *res = strstr(newstring1 + oldindex, newstring2);
		if (res)
		{
			found = true;
			oldindex = res - newstring1 + 1;
			int pos1 = res - newstring1;

			memcpy(result, text, indexlist1[pos1]);
			memcpy(result + indexlist1[pos1], replacestring, strlen(replacestring));

			size_t t = (text + strlen(text)) - (text + indexlist1[pos1 + strlen(newstring2)-1]+1);
			memcpy(result + indexlist1[pos1] + strlen(replacestring), text + indexlist1[pos1 + strlen(newstring2) -1] +1, t);
			result[indexlist1[pos1] + strlen(replacestring) + t] = 0;
			strcpy(text, result);

		}
		else
			break;



	}

	return found;

}

#define FIND_RESULT_SUCCESS			1
#define FIND_RESULT_ERROR_PATH_SIZE 0

#define FIND_ATTRIBUTES				1
#define FIND_GEOMETRY				2
#define FIND_SEGMENTS				3
#define FIND_INCLUDES				4
#define FIND_STYLES					5
#define FIND_SEGMENT_REFERENCES		6
#define FIND_GEOMETRY_REFERENCES	7
#define FIND_DEFINITIONS			8
#define FIND_KEYS					9
#define FIND_NAMED_STYLES			10

void HoopsSegmentTree::find_in_blank(int blank, const char *text, TreeGraphItem * startitem, HC_KEY search_key)
{
	char searchstring[MVO_BUFFER_SIZE];
	char replacestring[MVO_BUFFER_SIZE];
	if(startitem==0)
		startitem =  GetRootItem();
	HC_KEY startkey = (HC_KEY)startitem->m_pExtraData;
#define KEY_ARRAY_SIZE 256
	HC_KEY keys[KEY_ARRAY_SIZE];
	struct vlist_s*	foundlist = new_vlist(malloc, free);
	bool key_type=(blank==FIND_GEOMETRY || blank==FIND_SEGMENTS || blank==FIND_INCLUDES 
					|| blank==FIND_STYLES || blank==FIND_SEGMENT_REFERENCES
					|| blank==FIND_GEOMETRY_REFERENCES || blank==FIND_NAMED_STYLES);
	int find_result = FIND_RESULT_SUCCESS;

	if(text)	
	{
		char *res = strstr((char *)text, (const char *)"$$");
		if (res)
		{
			strcpy(searchstring, text);
			searchstring[res - text] = 0;
			strcpy(replacestring, res+2);
		}
		else
		{
			strcpy(replacestring,"");
			strcpy(searchstring,text);
		}
	}
	
	for (unsigned int j=0; j<strlen(searchstring); j++)
		searchstring[j] = tolower(searchstring[j]);
	
	if(blank==FIND_ATTRIBUTES)
		find_result = FindInAttributesInternal(searchstring, replacestring, startkey, keys, KEY_ARRAY_SIZE,0,foundlist);
	else if(blank==FIND_GEOMETRY)
		find_result = FindInGeometryInternal(searchstring, startkey, keys, KEY_ARRAY_SIZE,0, foundlist);
	else if(blank==FIND_SEGMENTS)
		find_result = FindInSegmentsInternal(searchstring, startkey, keys, KEY_ARRAY_SIZE,0, foundlist);
	else if(blank==FIND_INCLUDES)
		find_result = FindInIncludesInternal(searchstring, startkey, keys, KEY_ARRAY_SIZE,0, foundlist);
	else if(blank==FIND_STYLES)
		find_result = FindInStylesInternal(searchstring, startkey, keys, KEY_ARRAY_SIZE,0, foundlist);
	else if(blank==FIND_SEGMENT_REFERENCES)
		find_result = FindInSegmentReferencesInternal(searchstring, startkey, keys, KEY_ARRAY_SIZE,0, foundlist);
	else if(blank==FIND_GEOMETRY_REFERENCES)
		find_result = FindInGeometryReferencesInternal(searchstring, startkey, keys, KEY_ARRAY_SIZE,0, foundlist);
	else if(blank==FIND_DEFINITIONS)
		find_result = FindInDefinitionsInternal(searchstring, startkey, keys, KEY_ARRAY_SIZE,0, foundlist);
	else if(blank==FIND_KEYS)
		find_result = FindInKeysInternal(search_key, startkey, keys, KEY_ARRAY_SIZE,0, foundlist);
	else if(blank==FIND_NAMED_STYLES)
		find_result = FindInNamedStylesInternal(searchstring, startkey, keys, KEY_ARRAY_SIZE,0, foundlist);

	if(find_result == FIND_RESULT_ERROR_PATH_SIZE)
		AfxMessageBox(_T("Maximum search depth reached.  Some search results may be omitted."));
	
	START_LIST_ITERATION(Keylist, foundlist )
		if (key_type && streq(replacestring, "delete"))
			HC_Delete_By_Key(temp->keys[temp->keynum-1]);
		else
			ExpandByKeyListInternal(startitem, temp->keys, temp->keynum, 0);
		//it is necessary to free temp.  it was allocated in FindIn*Internal
		delete temp;
	END_LIST_ITERATION(foundlist);

	delete_vlist(foundlist);
}

int HoopsSegmentTree::FindInAttributesInternal(const char *text, const char *text2, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist)
{
	HC_KEY key;
	char type[64];
	int ret = FIND_RESULT_SUCCESS;
	keys[keypos++] = startkey;
	if(keypos>=keynum)
		return FIND_RESULT_ERROR_PATH_SIZE;

	HC_Open_Segment_By_Key(startkey);
		START_LIST_ITERATION(HoopsAttribute, m_AttributeList )
			static char atext[4096];
			static char segment[4096];
			key=HC_KShow_Original_Key(startkey);
			HC_Show_Segment(key, segment);

			if (temp->Exists())
			{
				static char typelower[32];
				const char *notlower = temp->GetName();
				for (unsigned int j=0; j<strlen(notlower); j++)
					typelower[j] = tolower(notlower[j]);
				typelower[strlen(notlower)] = 0;

				temp->Show(atext);
				if (!streq(text2, "unset") && !streq(text2, ""))
				{
					char res[MVO_BUFFER_SIZE];					
					if (ReplaceStringIgnoreSpace(atext, text, text2, res))
						temp->Set(res);
				}
				if (strstr(atext, text) || strstr(typelower, text))
				{
					if (streq(text2, "unset"))
					{
						temp->UnSet();
					}
					else
					{					
						Keylist *klitem = new Keylist;
						for (int i=0;i<keypos;i++)					
							klitem->keys[i] = keys[i];
						klitem->keys[keypos] = key;
						klitem->keynum = keypos+1;
						vlist_add_last(foundlist, klitem);
					}
				}
			}
		END_LIST_ITERATION(m_AttributeList);

		HC_Begin_Contents_Search(".", "segments, includes");
			while (HC_Find_Contents(type, &key))
			{
				if (streq(type,"include"))
				{
					keys[keypos++] = key;
					if(keypos>=keynum)
					{
						ret = FIND_RESULT_ERROR_PATH_SIZE;
						break;
					}
					key = HC_KShow_Include_Segment(key);
				}

				if(FindInAttributesInternal(text, text2, key, keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
					ret = FIND_RESULT_ERROR_PATH_SIZE;

				if (streq(type,"include"))
					--keypos;
			}
		HC_End_Contents_Search();
	HC_Close_Segment();

	return ret;
}

int HoopsSegmentTree::FindInGeometryInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist)
{
	HC_KEY key;
	char type[64];
	keys[keypos++] = startkey;
	int ret = FIND_RESULT_SUCCESS;
	if(keypos>=keynum)
		return FIND_RESULT_ERROR_PATH_SIZE;

	HC_Open_Segment_By_Key(startkey);
		HC_Begin_Contents_Search(".", "segments, includes, geometry");
			while (HC_Find_Contents(type, &key))
			{
				if (streq(type, "include") || streq(type, "segment"))
				{		
					if (streq(type,"include"))
					{
						keys[keypos++] = key;
						if(keypos>=keynum)
						{
							ret = FIND_RESULT_ERROR_PATH_SIZE;
							break;
						}
						key = HC_KShow_Include_Segment(key);
					}
					if(FindInGeometryInternal(text, key, keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
						ret = FIND_RESULT_ERROR_PATH_SIZE;
					if (streq(type,"include"))
						--keypos;
				}
				
				if (strstr(type, text))
				{			
					Keylist *klitem = new Keylist;
					for (int i=0;i<keypos;i++)					
						klitem->keys[i] = keys[i];
					klitem->keys[keypos] = key;
					klitem->keynum = keypos+1;
					vlist_add_last(foundlist, klitem);							
				}
			}
		HC_End_Contents_Search();
	HC_Close_Segment();

	return ret;
}


void HoopsSegmentTree::FindInAttributes(const char *text, TreeGraphItem * startitem)
{
	find_in_blank(FIND_ATTRIBUTES, text, startitem);
}

void HoopsSegmentTree::FindInGeometry(const char *text, TreeGraphItem * startitem)
{
	find_in_blank(FIND_GEOMETRY, text, startitem);
}

void HoopsSegmentTree::FindInSegments(const char *text, TreeGraphItem * startitem)
{
	find_in_blank(FIND_SEGMENTS, text, startitem);
}

void HoopsSegmentTree::FindInIncludes(const char *text, TreeGraphItem * startitem)
{
	find_in_blank(FIND_INCLUDES, text, startitem);
}

void HoopsSegmentTree::FindInStyles(const char *text, TreeGraphItem * startitem)
{
	find_in_blank(FIND_STYLES, text, startitem);
}

void HoopsSegmentTree::FindInNamedStyles(const char *text, TreeGraphItem * startitem)
{
	find_in_blank(FIND_NAMED_STYLES, text, startitem);
}

void HoopsSegmentTree::FindInSegmentReferences(const char *text, TreeGraphItem * startitem)
{
	find_in_blank(FIND_SEGMENT_REFERENCES, text, startitem);
}

void HoopsSegmentTree::FindInGeometryReferences(const char *text, TreeGraphItem * startitem)
{
	find_in_blank(FIND_GEOMETRY_REFERENCES, text, startitem);
}

void HoopsSegmentTree::FindInKeys(const char *text, TreeGraphItem * startitem)
{
	HC_KEY key = INVALID_KEY;
	sscanf(text, "%X", &key);

	if(key != INVALID_KEY)
		find_in_blank(FIND_KEYS, 0, startitem, key);
}

void HoopsSegmentTree::FindInDefinitions(const char *text, TreeGraphItem * startitem)
{
	find_in_blank(FIND_DEFINITIONS, text, startitem);
}

int HoopsSegmentTree::FindInSegmentsInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist)
{
	HC_KEY key;
	char type[64];  //cannot be static because we may recurse before checking the value.
	int ret = FIND_RESULT_SUCCESS;
	keys[keypos++] = startkey;
	if(keypos>=keynum)
		return FIND_RESULT_ERROR_PATH_SIZE;

	HC_Open_Segment_By_Key(startkey);
		HC_Begin_Contents_Search(".", "segments, includes");
			while (HC_Find_Contents(type, &key))
			{
				if (streq(type,"include"))
				{
					keys[keypos++] = key;
					if(keypos>=keynum)
					{
						ret = FIND_RESULT_ERROR_PATH_SIZE;
						break;
					}
					key = HC_KShow_Include_Segment(key);
				}

				if(FindInSegmentsInternal(text, key, keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
					ret = FIND_RESULT_ERROR_PATH_SIZE;

				if (streq(type,"include"))
					--keypos;
				
				if (streq(type, "segment"))
				{
					static char segname[4096];
					HC_Show_Segment(key, segname);
					HC_Parse_String(segname,"/",-1,segname);
					if (strstr(segname, text))
					{
						Keylist *klitem = new Keylist;
						for (int i=0;i<keypos;i++)					
							klitem->keys[i] = keys[i];
						klitem->keys[keypos] = key;
						klitem->keynum = keypos+1;
						vlist_add_last(foundlist, klitem);
					}
				}
			}
		HC_End_Contents_Search();
	HC_Close_Segment();

	return ret;
}

int HoopsSegmentTree::FindInIncludesInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist)
{
	HC_KEY search_key, seg_key=INVALID_KEY;
	char type[64];
	int ret = FIND_RESULT_SUCCESS;
	keys[keypos++] = startkey;
	if(keypos>=keynum)
		return FIND_RESULT_ERROR_PATH_SIZE;

	HC_Open_Segment_By_Key(startkey);
		HC_Begin_Contents_Search(".", "segments, includes");
			while (HC_Find_Contents(type, &search_key))
			{
				if (streq(type,"include"))
				{
					static char segname[4096];
					keys[keypos++] = search_key;
					if(keypos>=keynum)
					{
						ret = FIND_RESULT_ERROR_PATH_SIZE;
						break;
					}
					seg_key = HC_KShow_Include_Segment(search_key);
					HC_Show_Segment(seg_key, segname);
					if (strstr(segname, text))
					{
						Keylist *klitem = new Keylist;
						for (int i=0;i<keypos;i++)					
							klitem->keys[i] = keys[i];
						klitem->keys[keypos] = search_key;
						klitem->keynum = keypos+1;
						vlist_add_last(foundlist, klitem);
					}

					if(FindInIncludesInternal(text, seg_key, keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
						ret = FIND_RESULT_ERROR_PATH_SIZE;

					--keypos;
				}
				else 
					if(FindInIncludesInternal(text, search_key, keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
						ret = FIND_RESULT_ERROR_PATH_SIZE;
			}
		HC_End_Contents_Search();
	HC_Close_Segment();

	return ret;
}

int HoopsSegmentTree::FindInStylesInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist)
{
	HC_KEY search_key, seg_key;
	char type[64];
	int ret = FIND_RESULT_SUCCESS;
	keys[keypos++] = startkey;
	if(keypos>=keynum)
		return FIND_RESULT_ERROR_PATH_SIZE;

	HC_Open_Segment_By_Key(startkey);
		HC_Begin_Contents_Search(".", "segments, includes, styles");
			while (HC_Find_Contents(type, &search_key))
			{
				if (streq(type, "include") || streq(type, "segment"))
				{		
					HC_KEY key=search_key;
					if (streq(type,"include"))
					{
						keys[keypos++] = search_key;
						if(keypos>=keynum)
						{
							ret = FIND_RESULT_ERROR_PATH_SIZE;
							break;
						}
						key = HC_KShow_Include_Segment(search_key);
					}
					if(FindInStylesInternal(text, key, keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
						ret = FIND_RESULT_ERROR_PATH_SIZE;
					if (streq(type,"include"))
						--keypos;
				}
				else if (streq(type, "style"))
				{
					static char segname[4096];
					seg_key = HC_KShow_Style_Segment(search_key);
					HC_Show_Segment(seg_key, segname);
					if (strstr(segname, text))
					{
						Keylist *klitem = new Keylist;
						for (int i=0;i<keypos;i++)					
							klitem->keys[i] = keys[i];
						klitem->keys[keypos] = search_key;
						klitem->keynum = keypos+1;
						vlist_add_last(foundlist, klitem);
					}
				}
			}
		HC_End_Contents_Search();
	HC_Close_Segment();

	return ret;
}

int HoopsSegmentTree::FindInNamedStylesInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist)
{
	HC_KEY search_key;
	char type[64];
	int ret = FIND_RESULT_SUCCESS;
	keys[keypos++] = startkey;
	if(keypos>=keynum)
		return FIND_RESULT_ERROR_PATH_SIZE;

	HC_Open_Segment_By_Key(startkey);
		HC_Begin_Contents_Search(".", "segments, includes, named styles");
			while(HC_Find_Contents(type, &search_key))
			{
				if (streq(type, "include") || streq(type, "segment"))
				{		
					HC_KEY key=search_key;
					if (streq(type,"include"))
					{
						keys[keypos++] = search_key;
						if(keypos>=keynum)
						{
							ret = FIND_RESULT_ERROR_PATH_SIZE;
							break;
						}
						key = HC_KShow_Include_Segment(search_key);
					}
					if(FindInNamedStylesInternal(text, key, keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
						ret = FIND_RESULT_ERROR_PATH_SIZE;
					if (streq(type,"include"))
						--keypos;
				}
				else if (streq(type, "named style"))
				{
					static char style_name[4096], seg_name[4096];
					HC_Show_Named_Style_Segment(search_key, style_name);
					if(strstr(style_name, text))
					{
						Keylist *klitem = new Keylist;
						for (int i=0;i<keypos;i++)					
							klitem->keys[i] = keys[i];
						klitem->keys[keypos] = search_key;
						klitem->keynum = keypos+1;
						vlist_add_last(foundlist, klitem);
					}
				}
			}
		HC_End_Contents_Search();
	HC_Close_Segment();

	return ret;
}

int HoopsSegmentTree::FindInSegmentReferencesInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist)
{
	HC_KEY search_key, seg_key;
	char type[64];
	int ret = FIND_RESULT_SUCCESS;
	keys[keypos++] = startkey;
	if(keypos>=keynum)
		return FIND_RESULT_ERROR_PATH_SIZE;

	HC_Open_Segment_By_Key(startkey);
		HC_Begin_Contents_Search(".", "segments, includes, reference");
			while (HC_Find_Contents(type, &search_key))
			{
				if (streq(type, "include") || streq(type, "segment"))
				{		
					HC_KEY key=search_key;
					if (streq(type,"include"))
					{
						keys[keypos++] = search_key;
						if(keypos>=keynum)
						{
							ret = FIND_RESULT_ERROR_PATH_SIZE;
							break;
						}
						key = HC_KShow_Include_Segment(search_key);
					}
					if(FindInSegmentReferencesInternal(text, key, keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
						ret = FIND_RESULT_ERROR_PATH_SIZE;
					if (streq(type,"include"))
						--keypos;
				}
				else if (streq(type, "reference"))
				{
					static char segname[4096];
					seg_key = HC_KShow_Reference_Geometry(search_key);
					HC_Show_Key_Type(seg_key, type);
					if(streq(type, "segment"))
					{
						HC_Show_Segment(seg_key, segname);
						if (strstr(segname, text))
						{
							Keylist *klitem = new Keylist;
							for (int i=0;i<keypos;i++)					
								klitem->keys[i] = keys[i];
							klitem->keys[keypos] = search_key;
							klitem->keynum = keypos+1;
							vlist_add_last(foundlist, klitem);
						}
					}
				}
			}
		HC_End_Contents_Search();
	HC_Close_Segment();

	return ret;
}

int HoopsSegmentTree::FindInGeometryReferencesInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist)
{
	HC_KEY search_key, geo_key;
	char type[64];
	int ret = FIND_RESULT_SUCCESS;
	keys[keypos++] = startkey;
	if(keypos>=keynum)
		return FIND_RESULT_ERROR_PATH_SIZE;

	HC_Open_Segment_By_Key(startkey);
		HC_Begin_Contents_Search(".", "segments, includes, reference");
			while (HC_Find_Contents(type, &search_key))
			{
				if (streq(type, "include") || streq(type, "segment"))
				{		
					HC_KEY key=search_key;
					if (streq(type,"include"))
					{
						keys[keypos++] = search_key;
						if(keypos>=keynum)
						{
							ret = FIND_RESULT_ERROR_PATH_SIZE;
							break;
						}
						key = HC_KShow_Include_Segment(search_key);
					}
					if(FindInGeometryReferencesInternal(text, key, keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
						ret = FIND_RESULT_ERROR_PATH_SIZE;
					if (streq(type,"include"))
						--keypos;
				}
				else if (streq(type, "reference"))
				{
					geo_key = HC_KShow_Reference_Geometry(search_key);
					HC_Show_Key_Type(geo_key, type);
					if (strstr(type, text))
					{
						Keylist *klitem = new Keylist;
						for (int i=0;i<keypos;i++)					
							klitem->keys[i] = keys[i];
						klitem->keys[keypos] = search_key;
						klitem->keynum = keypos+1;
						vlist_add_last(foundlist, klitem);							
					}
				}
			}
		HC_End_Contents_Search();
	HC_Close_Segment();
	
	return ret;
}

int HoopsSegmentTree::FindInDefinitionsInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist)
{
	HC_KEY search_key;
	char type[64];
	int ret = FIND_RESULT_SUCCESS;
	keys[keypos++] = startkey;
	if(keypos>=keynum)
		return FIND_RESULT_ERROR_PATH_SIZE;

	HC_Open_Segment_By_Key(startkey);
		HC_Begin_Contents_Search(".", "segments, includes, texture definition, glyph definition, line style definition, named style definition");
			while (HC_Find_Contents(type, &search_key))
			{
				if (streq(type, "include") || streq(type, "segment"))
				{		
					HC_KEY key=search_key;
					if (streq(type,"include"))
					{
						keys[keypos++] = search_key;
						if(keypos>=keynum)
						{
							ret = FIND_RESULT_ERROR_PATH_SIZE;
							break;
						}
						key = HC_KShow_Include_Segment(search_key);
					}
					if(FindInDefinitionsInternal(text, key, keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
						ret = FIND_RESULT_ERROR_PATH_SIZE;
					if (streq(type,"include"))
						--keypos;
				}
				else 
				{
					static char name[4096];
					bool def_found=false;
					HC_Open_Segment_By_Key(search_key);
						if(strstr(type, "texture"))
						{
							HC_Begin_Texture_Search();
								while(HC_Find_Texture(name))
								{
									if(strstr(name, text))
									{
										def_found=true;
										break;
									}
								}
							HC_End_Texture_Search();
						}
						else if(strstr(type, "glyph"))
						{
							HC_Begin_Glyph_Search();
								while(HC_Find_Glyph(name))
								{
									if(strstr(name, text))
									{
										def_found=true;
										break;
									}
								}
							HC_End_Glyph_Search();
						}
						else if(strstr(type, "line style"))
						{
							HC_Begin_Line_Style_Search();
								while(HC_Find_Line_Style(name))
								{
									if(strstr(name, text))
									{
										def_found=true;
										break;
									}
								}
							HC_End_Line_Style_Search();
						}
						if(strstr(type, "named style"))
						{
							HC_Begin_Named_Style_Search();
								while(HC_Find_Named_Style(name))
								{
									if(strstr(name, text))
									{
										def_found=true;
										break;
									}
								}
							HC_End_Named_Style_Search();
						}
					HC_Close_Segment();

					if(def_found)
					{
						Keylist *klitem = new Keylist;
						for (int i=0;i<keypos;i++)
							klitem->keys[i] = keys[i];
						klitem->keys[keypos] = search_key;
						klitem->keynum = keypos+1;
						vlist_add_last(foundlist, klitem);
					}
				}
			}
		HC_End_Contents_Search();
	HC_Close_Segment();

	return ret;
}

int HoopsSegmentTree::FindInKeysInternal(HC_KEY searchkey, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist)
{
	HC_KEY key;
	char type[64];
	keys[keypos++] = startkey;
	int ret = FIND_RESULT_SUCCESS;
	if(keypos>=keynum)
		return FIND_RESULT_ERROR_PATH_SIZE;

	HC_Open_Segment_By_Key(startkey);
		HC_Begin_Contents_Search(".", "everything, static model, no attributes");
			while (HC_Find_Contents(type, &key))
			{
				if (key == searchkey)
				{			
					Keylist *klitem = new Keylist;
					for (int i=0;i<keypos;i++)					
						klitem->keys[i] = keys[i];
					klitem->keys[keypos] = key;
					klitem->keynum = keypos+1;
					vlist_add_last(foundlist, klitem);							
				}

				if (streq(type, "include") || streq(type, "segment") || streq(type, "static model"))
				{		
					if (streq(type,"include"))
					{
						keys[keypos++] = key;
						if(keypos>=keynum)
						{
							ret = FIND_RESULT_ERROR_PATH_SIZE;
							break;
						}
						key = HC_KShow_Include_Segment(key);
						if (key == searchkey)
						{			
							Keylist *klitem = new Keylist;
							for (int i=0;i<keypos;i++)					
								klitem->keys[i] = keys[i];
							klitem->keys[keypos] = key;
							klitem->keynum = keypos+1;
							vlist_add_last(foundlist, klitem);							
						}
					}
					if(FindInKeysInternal(searchkey, key, keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
						ret = FIND_RESULT_ERROR_PATH_SIZE;
					if (streq(type,"include"))
						--keypos;
				}
				else if (streq(type, "reference"))
				{
					HC_KEY * ref_keys;
					int ref_count;

					HC_Show_Reference_Keys_Count(key, &ref_count);
					if(ref_count > 0)
					{
						ref_keys = new HC_KEY[ref_count];
						HC_Show_Reference_Keys(key, 0, ref_keys);
						
						for(int i=0; i<ref_count; ++i)
						{
							if (ref_keys[i] == searchkey)
							{			
								Keylist *klitem = new Keylist;
								for (int j=0; j<keypos; j++)					
									klitem->keys[j] = keys[j];
								klitem->keys[keypos] = key;
								klitem->keys[keypos+1] = ref_keys[i];
								klitem->keynum = keypos+2;
								vlist_add_last(foundlist, klitem);							
							}
							
							HC_Show_Key_Type(ref_keys[i], type);
							if(streq(type, "segment"))
							{
								keys[keypos++] = key;
								if(FindInKeysInternal(searchkey, ref_keys[i], keys, keynum, keypos, foundlist) == FIND_RESULT_ERROR_PATH_SIZE)
									ret = FIND_RESULT_ERROR_PATH_SIZE;
								--keypos;
							}

						}

						delete [] ref_keys;
					}
				}				
			}
		HC_End_Contents_Search();
	HC_Close_Segment();

	return ret;
}


void HoopsSegmentTree::OnItemExpanding(TreeGraphItem *item, bool expand)
{
	if (expand)
	{
		char type[MVO_BUFFER_SIZE];
		if (item->m_pExtraData)
		{
			if(!HC_Show_Existence_By_Key((HC_KEY)item->m_pExtraData, "self"))
				return;

			if (IsInclude(item))
			{		
				HC_Open_Segment_By_Key((HC_KEY)item->m_pParentItem->m_pParentItem->m_pExtraData);		    		    
				HC_Show_Key_Type((HC_KEY)item->m_pExtraData, type);
				HC_Close_Segment();
			}
			else
				HC_Show_Key_Type((HC_KEY)item->m_pExtraData, type);

			if (strcmp(item->m_pItemText, "STATIC_TREE") == 0)
				ExpandStaticModel(item, (HC_KEY)item->m_pExtraData);
			
			else if (strcmp(item->m_pItemText, "REFERENCES") == 0)
				ExpandReferenceItem(item, (HC_KEY)item->m_pParentItem->m_pExtraData);

			else if ((strcmp(type, "segment") == 0) && !(item->m_Flags & ~READONLY_OBJECT))
				ExpandSegmentItem(item, (HC_KEY)item->m_pExtraData);

			else if (strcmp(type, "include") == 0)
				ExpandInclude(item, (HC_KEY)item->m_pExtraData);
			
			else if (strcmp(type, "named style") == 0)
				ExpandNamedStyle(item, (HC_KEY)item->m_pExtraData);

			else if (strcmp(type, "style") == 0)
				ExpandStyle(item, (HC_KEY)item->m_pExtraData);
			
			else if(item->m_Flags)
				ExpandSpecificReference(item, (HC_KEY)item->m_pExtraData);

			else
				ExpandSpecificGeometry(item, (HC_KEY)item->m_pExtraData);
		}			
		else
		{
			START_LIST_ITERATION(HoopsGeometry, m_GeometryList)	   
				if (strcmp(item->m_pItemText, temp->GetName()) == 0)
					ExpandGeometryType(item, (HC_KEY)item->m_pParentItem->m_pParentItem->m_pExtraData, temp);
			END_LIST_ITERATION(m_GeometryList);		
			START_LIST_ITERATION(HoopsGeometry, m_DefineList)	   
				if (strcmp(item->m_pItemText, temp->GetName()) == 0)
					ExpandDefineType(item, (HC_KEY)item->m_pParentItem->m_pParentItem->m_pExtraData, (HoopsDefineGeometry *)temp);
			END_LIST_ITERATION(m_DefineList);		

			if (strcmp(item->m_pItemText, "INCLUDES") == 0)
				ExpandIncludeItem(item, (HC_KEY)item->m_pParentItem->m_pExtraData);
			else if	(strcmp(item->m_pItemText, "STYLES") == 0)
				ExpandStyleItem(item, (HC_KEY)item->m_pParentItem->m_pExtraData);
			else if	(strcmp(item->m_pItemText, "NAMED STYLES") == 0)
				ExpandNamedStyleItem(item, (HC_KEY)item->m_pParentItem->m_pExtraData);
			else if (strcmp(item->m_pItemText, "GEOMETRY") == 0)
				ExpandGeometryItem(item, (HC_KEY)item->m_pParentItem->m_pExtraData);
			else if (strcmp(item->m_pItemText, "DEFINES") == 0)
				ExpandDefinesItem(item, (HC_KEY)item->m_pParentItem->m_pExtraData);
			else if (strcmp(item->m_pParentItem->m_pItemText, "REFERENCES") == 0)
				ExpandReferenceType(item, (HC_KEY)item->m_pParentItem->m_pExtraData);
			else if (strstr(item->m_pItemText, "REFERENCES"))
				ExpandReferenceGroupItem(item, (HC_KEY)item->m_pParentItem->m_pParentItem->m_pExtraData);
			else if (strstr(item->m_pItemText, "SEGMENTS"))
				ExpandSegmentGroupItem(item, (HC_KEY)item->m_pParentItem->m_pExtraData);
		}
		item->m_bExpanded = true;
	}
	else
		item->m_bExpanded = false;

}

typedef VHash<HC_KEY, HC_KEY> VChildHash;

void HoopsSegmentTree::ExpandSegmentItem(TreeGraphItem *item, HC_KEY key)
{

	HC_KEY segkey;
	int num;
	int i;
	char type[MVO_BUFFER_SIZE];
	struct vlist_s*	childList = item->m_ChildItemList;

	START_LIST_ITERATION(TreeGraphItem, childList)
		item->DeleteChildItem(temp);
		vlist_reset_cursor(childList);
	}

	if (StaticModelsExist(item))
	{
		TreeGraphItem *item2 = AddStaticModelItem((HC_KEY)item->m_pExtraData, item);
		item2->m_Type = STATICMODELITEM;
		SetItemImage(item2, item2->m_Type);
		item2->SetHasChildren(true);
	}
	if (GeometryExists(item))
	{
		TreeGraphItem *item2 = item->AddChildItem(_T("GEOMETRY"),0, false);
		item2->m_Type = GEOMETRYITEM;
		SetItemImage(item2, item2->m_Type);
		item2->m_Flags = (item->m_Flags & READONLY_OBJECT);
		item2->SetHasChildren(true);
	}
	if (DefinesExists(item))
	{
		TreeGraphItem *item2 = item->AddChildItem(_T("DEFINES"),0, false);
		item2->m_Type = GEOMETRYITEM;
		SetItemImage(item2, item2->m_Type);
		item2->m_Flags = (item->m_Flags & READONLY_OBJECT);
		item2->SetHasChildren(true);
	}
	if (IncludesExist(item))
	{
		TreeGraphItem *item2 = item->AddChildItem(_T("INCLUDES"),0, false);
		item2->m_Type = INCLUDEITEM;
		SetItemImage(item2, item2->m_Type);
		item2->m_Flags = (item->m_Flags & READONLY_OBJECT);
		item2->SetHasChildren(true);
	}
	if (StylesExist(item))
	{
		TreeGraphItem *item2 = item->AddChildItem(_T("STYLES"),0, false);
		item2->m_Type = INCLUDEITEM;
		SetItemImage(item2, item2->m_Type);
		item2->m_Flags = (item->m_Flags & READONLY_OBJECT);
		item2->SetHasChildren(true);
	}
	if(NamedStylesExist(item))
	{
		TreeGraphItem *item2 = item->AddChildItem(_T("NAMED STYLES"),0, false);
		item2->m_Type = INCLUDEITEM;
		SetItemImage(item2, item2->m_Type);
		item2->m_Flags = (item->m_Flags & READONLY_OBJECT);
		item2->SetHasChildren(true);
	}
	if (ReferencesExist(item))
	{
		TreeGraphItem *item2 = item->AddChildItem(_T("REFERENCES"),0, false);
		item2->m_Type = INCLUDEITEM;
		SetItemImage(item2, item2->m_Type);
		item2->m_pExtraData=item->m_pExtraData;
		item2->m_Flags = (item->m_Flags & READONLY_OBJECT);
		item2->SetHasChildren(true);
	}

	VChildHash * childHash = new VChildHash();

	START_LIST_ITERATION(TreeGraphItem, childList)
		childHash->InsertItem((HC_KEY)temp->m_pExtraData, (HC_KEY)temp->m_pExtraData);
	END_LIST_ITERATION(childList);

	HC_Open_Segment_By_Key(key);
		HC_Begin_Contents_Search(".", "segments");
		HC_Show_Contents_Count(&num);

		if(num<=1000)
		{
			for (i=0;i<num;i++)
			{
				HC_KEY dummy;
				HC_Find_Contents(type, &segkey);
				segkey = HC_KShow_Original_Key(segkey);

				if (childHash->LookupItem(segkey, &dummy) == VHASH_STATUS_FAILED) {
					AddSegmentItem(segkey, item);
				}
			}
		}
		else
		{
			sii_passthru pt;
			for(i=0; i<num; i+=1000)
			{
				int low = i+1, high = (i+1000 < num ? i+1000 : num);
				AddSegmentGroupItem(low, high, item, &pt);
			}
		}
		HC_End_Contents_Search();
	HC_Close_Segment();

	delete childHash;

	START_LIST_ITERATION(TreeGraphItem, childList)
		if (temp->m_pExtraData)
		{
			if (!HC_Show_Existence_By_Key((HC_KEY)temp->m_pExtraData, "self"))
				item->DeleteChildItem(temp);
			else
				VerifyChildren(temp);
		}
	END_LIST_ITERATION(childList);

	ExpandAttributeItem(item, key);
}


bool HoopsSegmentTree::GeometryTypeExists(HC_KEY key,const char *type)
{
	int num;
	char key_type[MVO_BUFFER_SIZE];
	HC_Show_Key_Type(key, key_type);

	if(streq(key_type, "reference"))
		key=HC_KShow_Reference_Geometry(key);

	HC_Open_Segment_By_Key(key);
	HC_Begin_Contents_Search(".", type);
	HC_Show_Contents_Count(&num);
	HC_End_Contents_Search();
	HC_Close_Segment();
	if (num)
		return true;
	else
		return false;
}

bool HoopsSegmentTree::DefineTypeExists(HC_KEY key,HoopsGeometry *type)
{
	int num;
	HC_Open_Segment_By_Key(key);
	num = type->Exists();
	HC_Close_Segment();
	if (num)
		return true;
	else
		return false;
}


bool HoopsSegmentTree::AttributeTypeExists(HC_KEY key,char *type)
{
	/*
	bool found;
	HC_Open_Segment_By_Key(key);
	found = HC_Show_Existence(type);
	HC_Close_Segment();
	*/
	return true;
}


void HoopsSegmentTree::ExpandGeometryItem(TreeGraphItem *item, HC_KEY key)
{

	struct vlist_s*	childList = item->m_ChildItemList;
	bool found[128];
	int i;
	for (i=0;i<128;i++)
		found[i] = false;


	START_LIST_ITERATION(TreeGraphItem, childList)
		vlist_reset_cursor(m_GeometryList);
	i=0;
	while (1) {
		HoopsGeometry *temp2;
		if (!(temp2 = (HoopsGeometry *)vlist_peek_cursor(m_GeometryList)))
			break;

		if (strcmp(temp->m_pItemText, temp2->GetName()) == 0)
		{
			found[i] = true;
			if (!GeometryTypeExists(key, temp2->GetName()))
				item->DeleteChildItem(temp);
		}		
		i++;
		vlist_advance_cursor(m_GeometryList);
	}
	END_LIST_ITERATION(childList);

	char type[MVO_BUFFER_SIZE];
	char filter[MVO_BUFFER_SIZE] = "";

	HC_Show_Key_Type(key, type);
	if(strstr(type, "reference"))
	{
		HC_Show_Reference_Geometry_Filter(key, filter);
		key=HC_KShow_Reference_Geometry(key);		
	}
	
	i=0;
	START_LIST_ITERATION(HoopsGeometry, m_GeometryList)
		if (!found[i])
		{
			if (strstr(filter, "no geometry")) {
				char included_item[MVO_BUFFER_SIZE];
				sprintf(included_item, "%s", temp->GetName());
				for(size_t j=0; j<strlen(included_item); ++j)
					included_item[j]=tolower(included_item[j]);

				if (GeometryTypeExists(key, temp->GetName()) && strstr(filter, included_item))
				{
					TreeGraphItem *item2 = item->AddChildItem(H_TEXT(temp->GetName()),0, false);
					item2->m_Type = GEOMETRYITEM;
					SetItemImage(item2, item2->m_Type);
					item2->SetHasChildren(true);
				}
			}
			else {
				char removed_item[MVO_BUFFER_SIZE];
				sprintf(removed_item, "no %s", temp->GetName());
				for(size_t j=0; j<strlen(removed_item); ++j)
					removed_item[j]=tolower(removed_item[j]);

				if (GeometryTypeExists(key, temp->GetName()) && !strstr(filter, removed_item))
				{
					TreeGraphItem *item2 = item->AddChildItem(H_TEXT(temp->GetName()),0, false);
					item2->m_Type = GEOMETRYITEM;
					SetItemImage(item2, item2->m_Type);
					item2->SetHasChildren(true);
				}
			}
		}
		i++;
		END_LIST_ITERATION(m_GeometryList);
}


void HoopsSegmentTree::ExpandDefinesItem(TreeGraphItem *item, HC_KEY key)
{

	struct vlist_s*	childList = item->m_ChildItemList;
	bool found[128];
	int i;
	for (i=0;i<128;i++)
		found[i] = false;


	START_LIST_ITERATION(TreeGraphItem, childList)
		vlist_reset_cursor(m_DefineList);
	i=0;
	while (1) {
		HoopsGeometry *temp2;
		if (!(temp2 = (HoopsGeometry *)vlist_peek_cursor(m_DefineList)))
			break;

		if (strcmp(temp->m_pItemText, temp2->GetName()) == 0)
		{
			found[i] = true;
			if (!DefineTypeExists(key, temp2))
				item->DeleteChildItem(temp);
		}		
		i++;
		vlist_advance_cursor(m_DefineList);
	}
	END_LIST_ITERATION(childList);

	i=0;
	START_LIST_ITERATION(HoopsGeometry, m_DefineList)
		if (!found[i])
		{
			if (DefineTypeExists(key, temp))
			{
				TreeGraphItem *item2 = item->AddChildItem(H_TEXT(temp->GetName()),0, false);
				item2->m_Type = GEOMETRYITEM;
				SetItemImage(item2, item2->m_Type);
				item2->SetHasChildren(true);
			}
		}
		i++;
	END_LIST_ITERATION(m_DefineList);

}

TreeGraphItem * HoopsSegmentTree::ExpandAttributeType(TreeGraphItem *item, HC_KEY key, const char *type)
{
	char text[MVO_BIG_BUFFER_SIZE] = "-undefined-";
	
	if(key==-1)
		item->Expand();
	else
	{
		bool is_segment=false;
		char key_type[MVO_BUFFER_SIZE];

		HC_Show_Key_Type(key, key_type);
		if(strcmp(key_type, "segment")==0)
			is_segment=true;

		if(is_segment)
			HC_Open_Segment_By_Key(key);
		else
			HC_Open_Geometry(key);

		START_LIST_ITERATION(HoopsAttribute, m_AttributeList)	   
			if (strcmp(type, temp->GetName()) == 0)
			{
				if (temp->Exists())
					temp->Show(text);
				break;
			}
		END_LIST_ITERATION(m_AttributeList);
		
		if(is_segment)
			HC_Close_Segment();
		else
			HC_Close_Geometry();
	}
	if (strcmp(text, "-undefined-") !=0 || key == -1)
	{
		char final[MVO_BIG_BUFFER_SIZE];
		ExtendAttributeText(type, text, final);
		TreeGraphItem *newitem = item->AddChildItem(H_TEXT(final),0, false);
		newitem->ModifyText2(type);
		newitem->m_Flags = item->m_Flags & READONLY_OBJECT;
		newitem->m_Type = ATTRIBUTEITEM;
		SetItemImage(newitem, newitem->m_Type);
		return newitem;

	}

	return 0;
}

void HoopsSegmentTree::ExpandInclude(TreeGraphItem *item, HC_KEY key)
{
	HC_Open_Segment_By_Key((HC_KEY)item->m_pParentItem->m_pParentItem->m_pExtraData);
	HC_KEY newkey;
	newkey = HC_KShow_Include_Segment(key);

	struct vlist_s*	childList = item->m_ChildItemList;
	bool noinclude = true;
	START_LIST_ITERATION(TreeGraphItem, childList)
		if ((HC_KEY)temp->m_pExtraData != newkey)
			item->DeleteChildItem(temp);
		else 
			noinclude = false;
	END_LIST_ITERATION(childList);

	if (noinclude)
	{	
		AddSegmentItem(newkey, item);
		START_LIST_ITERATION(TreeGraphItem, childList)
			VerifyChildren(temp);
		END_LIST_ITERATION(childList);		
	}
	HC_Close_Segment();
}

void HoopsSegmentTree::ExpandStyle(TreeGraphItem *item, HC_KEY key)
{
	HC_Open_Segment_By_Key((HC_KEY)item->m_pParentItem->m_pParentItem->m_pExtraData);
	HC_KEY newkey;
	newkey = HC_KShow_Style_Segment(key);

	struct vlist_s*	childList = item->m_ChildItemList;
	bool noinclude = true;
	START_LIST_ITERATION(TreeGraphItem, childList)
		if ((HC_KEY)temp->m_pExtraData != newkey)
			item->DeleteChildItem(temp);
		else 
			noinclude = false;
	END_LIST_ITERATION(childList);

	if (noinclude)
	{	
		ExpandAttributeItem(item, newkey);
	}
	HC_Close_Segment();
}

void HoopsSegmentTree::ExpandNamedStyle(TreeGraphItem *item, HC_KEY key)
{
#if 0
	char name[MVO_BUFFER_SIZE], style_path[MVO_BUFFER_SIZE];
	HC_KEY newkey, seg_path[1024];

	HC_Open_Segment_By_Key((HC_KEY)item->m_pParentItem->m_pParentItem->m_pExtraData);
		HC_Show_Style_Segment_Named(key, name);
		HC_PShow_Net_Named_Style(name, seg_path, ); 
		newkey = HC_Create_Segment(style_path);

		struct vlist_s*	childList = item->m_ChildItemList;
		START_LIST_ITERATION(TreeGraphItem, childList)
			item->DeleteChildItem(temp);
		END_LIST_ITERATION(childList);

		ExpandAttributeItem(item, newkey);
	HC_Close_Segment();
#endif
}

void HoopsSegmentTree::ExpandStaticModel(TreeGraphItem *item, HC_KEY key)
{
	ExpandSegmentItem(item, key);	
}

void HoopsSegmentTree::ExpandReferenceItem(TreeGraphItem *item, HC_KEY key)
{
	bool geofound=false, segfound=false;
	struct vlist_s*	childList = item->m_ChildItemList;
	
	
	START_LIST_ITERATION(TreeGraphItem, childList)
		if (strcmp(temp->m_pItemText, "GEOMETRY_REF") == 0)
		{
			geofound = true;
			if(!GeometryReferencesExist(item))
			{
				item->DeleteChildItem(temp);
				vlist_reset_cursor(childList);
			}
		}
		else if (strcmp(temp->m_pItemText, "SEGMENT_REF") == 0)
		{
			segfound=true;
			if(!SegmentReferencesExist(item))
			{
				item->DeleteChildItem(temp);
				vlist_reset_cursor(childList);
			}
		}
	END_LIST_ITERATION(childList);

	if (!geofound)
	{
		if (GeometryReferencesExist(item))
		{
			TreeGraphItem *item2 = item->AddChildItem(_T("GEOMETRY_REF"),0, false);
			item2->m_Flags = item->m_Flags & READONLY_OBJECT;
			item2->m_Type = STATICMODELITEM;
			SetItemImage(item2, item2->m_Type);
			item2->SetHasChildren(true);
		}
	}
	if (!segfound)
	{
		if (SegmentReferencesExist(item))
		{
			TreeGraphItem *item2 = item->AddChildItem(_T("SEGMENT_REF"),0, false);
			item2->m_Flags = item->m_Flags & READONLY_OBJECT;
			item2->m_Type = STATICMODELITEM;
			SetItemImage(item2, item2->m_Type);
			item2->SetHasChildren(true);
		}
	}
}

void HoopsSegmentTree::ExpandReferenceType(TreeGraphItem *item, HC_KEY key)
{
	bool expanding_segment = (strcmp(item->m_pItemText, "SEGMENT_REF") == 0);
	char type[MVO_BUFFER_SIZE];
	HC_KEY ref_key;
	struct vlist_s*	childList = item->m_ChildItemList;
	int num;

	START_LIST_ITERATION(TreeGraphItem, childList)
		item->DeleteChildItem(temp);
		vlist_reset_cursor(childList);
	}

	if (!HC_Show_Existence_By_Key((HC_KEY)item->m_pParentItem->m_pExtraData, "self"))
	{
		OnItemExpanding(item->m_pParentItem->m_pParentItem, true);
		return;
	}

	HC_Open_Segment_By_Key(ResolveKey((HC_KEY)(item->m_pParentItem->m_pExtraData)));
	HC_Begin_Contents_Search(".", "reference");
		HC_Show_Contents_Count(&num);

		if(num<=1000)
		{
CREATE_REFS:
			while(HC_Find_Contents(type, &ref_key))
			{
				key=HC_KShow_Reference_Geometry(ref_key);
				HC_Show_Key_Type(key, type);
				if(expanding_segment)
				{
					if(streq(type, "segment"))
						AddSegmentReference(ref_key, item);
				}
				else if (!streq(type, "segment"))
				{	
					HoopsReference refType;
					char text2[MVO_BUFFER_SIZE], text[MVO_BUFFER_SIZE];

					refType.GetData(ref_key, text2);
					sprintf(text, "%X - %s - %s", ref_key, refType.GetName(), text2);
					TreeGraphItem *newitem = (TreeGraphItem *)item->AddChildItem(H_TEXT(text),(void *)ref_key);
					newitem->m_Flags = GEOMETRY_REFERENCE | (item->m_Flags & READONLY_OBJECT);
					newitem->m_Type = GEOMETRYITEM;
					SetItemImage(newitem, newitem->m_Type);
					newitem->SetHasChildren(true);
				}
			}
			HC_End_Contents_Search();
		}
		else
		{
			int seg_cnt=0, geo_cnt=0;
			while(HC_Find_Contents(type, &ref_key))
			{
				key=HC_KShow_Reference_Geometry(ref_key);
				HC_Show_Key_Type(key, type);
				if(streq(type, "segment"))
					++seg_cnt;
				else
					++geo_cnt;
			}
			HC_End_Contents_Search();

			//we spent the first contents search just counting things.
			//we need another one to actually do anything now.
			if((expanding_segment && seg_cnt < 1000) || (!expanding_segment && geo_cnt < 1000))
			{
				HC_Begin_Contents_Search(".", "reference");
				goto CREATE_REFS;
			}
			else
			{
				sii_passthru pt;
				num = (expanding_segment ? seg_cnt : geo_cnt);
				for(int i=0; i<num; i+=1000)
				{
					int low = i+1, high = (i+1000 < num ? i+1000 : num);
					AddReferenceGroupItem(low, high, item, &pt);
				}
			}			
		}
	HC_Close_Segment();
}

void HoopsSegmentTree::ExpandAttributeItem(TreeGraphItem *item, HC_KEY key)
{
	START_LIST_ITERATION(HoopsAttribute, m_AttributeList)	   
		ExpandAttributeType(item, key, temp->GetName());
	END_LIST_ITERATION(m_AttributeList);
}

void HoopsSegmentTree::ExpandGeometryAttributeItem(TreeGraphItem *item, HC_KEY key)
{
	struct vlist_s * AttributeList=0;
	char type[MVO_BUFFER_SIZE];

	HC_Show_Key_Type(key, type);

	if(strstr(type, "shell") || strstr(type, "light") || strstr(type, "mesh"))
		AttributeList=m_GeometryAttributeList_Basic;
	else if(strstr(type, "text"))
		AttributeList=m_GeometryAttributeList_Text;
	else
		AttributeList=m_GeometryAttributeList_User;

	START_LIST_ITERATION(HoopsAttribute, AttributeList)	   
		ExpandAttributeType(item, key, temp->GetName());
	END_LIST_ITERATION(AttributeList);
}



void HoopsSegmentTree::ExpandGeometryType(TreeGraphItem *item, HC_KEY key, HoopsGeometry *geomType)
{
	int num;
	int i;
	char type[MVO_BUFFER_SIZE];
	struct vlist_s*	childList = item->m_ChildItemList;
	HC_KEY *newgeos;
	int newgeoscount = 0;
	bool *foundarray;
	bool was_ref = false;
	HC_KEY seg_key = INVALID_KEY;
	HC_KEY geo_key = INVALID_KEY;


	HC_Show_Key_Type(key, type);
	if(streq(type, "reference")) {
		was_ref = true;
		seg_key=HC_KShow_Reference_Geometry(key);
	}
	else
		seg_key = key;

	HC_Open_Segment_By_Key(seg_key);
		HC_Begin_Contents_Search(".", item->m_pItemText);
			HC_Show_Contents_Count(&num);

			newgeos= new HC_KEY[num];
			foundarray = new bool [vlist_count(childList)];
			memset(foundarray, 0, vlist_count(childList)*sizeof(bool));

			for (i=0; i<num; i++)
			{
				bool found = false;
				HC_Find_Contents(type, &geo_key);
				START_LIST_ITERATION(TreeGraphItem, childList)

					if ((HC_KEY)temp->m_pExtraData == geo_key)
					{
						foundarray[i] = true;
						found = true;
						break;
					}
					END_LIST_ITERATION(childList);
					if (!found)
						newgeos[newgeoscount++] = geo_key;

			}	
			i = 0;
			START_LIST_ITERATION(TreeGraphItem, childList)
				if (!foundarray[i] && temp->m_pExtraData)
					item->DeleteChildItem(temp);
			END_LIST_ITERATION(childList);

			for (i=0;i<newgeoscount;i++) {
				TreeGraphItem * g = AddGeometryItem(newgeos[i], item, geomType);
				if (was_ref) {
					g->m_pExtraData = (void*)key;
					g->m_pExtraData2 = (void*)newgeos[i];
				}
			}

		HC_End_Contents_Search();
	HC_Close_Segment();

	delete [] foundarray;
	delete [] newgeos;	

}
void HoopsSegmentTree::ExpandDefineType(TreeGraphItem *item, HC_KEY key, HoopsDefineGeometry *geomType)
{

	HC_KEY segkey = -1;
	char type[MVO_BUFFER_SIZE];
	struct vlist_s*	childList = item->m_ChildItemList;
	struct vlist_s*	templist = new_vlist(malloc, free);

	START_LIST_ITERATION(TreeGraphItem, childList)
		vlist_add_last(templist, temp);
	END_LIST_ITERATION(childList);


	START_LIST_ITERATION(TreeGraphItem, templist)
		item->DeleteChildItem(temp);
	END_LIST_ITERATION(templist);

	delete_vlist(templist);

	HC_Open_Segment_By_Key(key);
	geomType->StartDefineSearch();

	while (geomType->DoDefineSearch(type))
	{
		char text[MVO_BUFFER_SIZE];	
		sprintf(text, "%s",  type);
		TreeGraphItem *newitem = (TreeGraphItem *)item->AddChildItem(H_TEXT(text),(void *)segkey);
		newitem->m_Type = GEOMETRYITEM;
		SetItemImage(newitem, newitem->m_Type);
	}	
	geomType->EndDefineSearch();
	HC_Close_Segment();
}





void HoopsSegmentTree::ExpandIncludeItem(TreeGraphItem *item, HC_KEY key)
{
	HC_KEY segkey;
	int num;
	int i;
	char type[MVO_BUFFER_SIZE];
	struct vlist_s*	childList = item->m_ChildItemList;

	HC_Open_Segment_By_Key(key);
	HC_Begin_Contents_Search(".", "includes");
	HC_Show_Contents_Count(&num);
	HC_KEY *newsegments = new HC_KEY[num];
	int newsegmentscount = 0;


	bool *foundarray = new bool [vlist_count(childList)];
	for (i=0;i<(int)vlist_count(childList);i++)
		foundarray[i] = 0;

	for (i=0;i<num;i++)
	{
		bool found = false;
		HC_Find_Contents(type, &segkey);
		START_LIST_ITERATION(TreeGraphItem, childList)

			if ((HC_KEY)temp->m_pExtraData == segkey)
			{
				foundarray[i] = true;
				found = true;
				break;
			}
			END_LIST_ITERATION(childList);
			if (!found)
				newsegments[newsegmentscount++] = segkey;

	}	
	HC_End_Contents_Search();
	HC_Close_Segment();
	i = 0;
	START_LIST_ITERATION(TreeGraphItem, childList)
		if (!foundarray[i] && temp->m_pExtraData)
			item->DeleteChildItem(temp);
	END_LIST_ITERATION(childList);

	for (i=0;i<newsegmentscount;i++)
		AddIncludeItem(newsegments[i], item);


	delete [] foundarray;
	delete [] newsegments;	

}

void HoopsSegmentTree::ExpandStyleItem(TreeGraphItem *item, HC_KEY key)
{
	HC_KEY segkey;
	int num;
	int i;
	char type[MVO_BUFFER_SIZE];
	struct vlist_s*	childList = item->m_ChildItemList;

	HC_Open_Segment_By_Key(key);
	HC_Begin_Contents_Search(".", "styles");
	HC_Show_Contents_Count(&num);
	HC_KEY *newsegments = new HC_KEY[num];
	int newsegmentscount = 0;


	bool *foundarray = new bool [vlist_count(childList)];
	for (i=0;i<(int)vlist_count(childList);i++)
		foundarray[i] = 0;

	for (i=0;i<num;i++)
	{
		bool found = false;
		HC_Find_Contents(type, &segkey);
		START_LIST_ITERATION(TreeGraphItem, childList)

			if ((HC_KEY)temp->m_pExtraData == segkey)
			{
				foundarray[i] = true;
				found = true;
				break;
			}
			END_LIST_ITERATION(childList);
			if (!found)
				newsegments[newsegmentscount++] = segkey;

	}	
	HC_End_Contents_Search();
	HC_Close_Segment();
	i = 0;
	START_LIST_ITERATION(TreeGraphItem, childList)
		if (!foundarray[i] && temp->m_pExtraData)
			item->DeleteChildItem(temp);
	END_LIST_ITERATION(childList);

	for (i=0;i<newsegmentscount;i++)
		AddIncludeItem(newsegments[i], item);


	delete [] foundarray;
	delete [] newsegments;	

}

void HoopsSegmentTree::ExpandNamedStyleItem(TreeGraphItem *item, HC_KEY key)
{
	HC_KEY search_key;
	char type[MVO_BUFFER_SIZE];
	struct vlist_s*	childList = item->m_ChildItemList;

	START_LIST_ITERATION(TreeGraphItem, childList)
		item->DeleteChildItem(temp);
		vlist_reset_cursor(childList);
	}

	HC_Open_Segment_By_Key(key);
		HC_Begin_Contents_Search(".", "named style");
			while(HC_Find_Contents(type, &search_key))
				AddIncludeItem(search_key, item);
		HC_End_Contents_Search();
	HC_Close_Segment();
}


void HoopsSegmentTree::ExpandSegmentGroupItem(TreeGraphItem *item, HC_KEY key)
{
	int num=0, i=0, low, high;
	HC_KEY * seg_list;

	HC_Open_Segment_By_Key(key);
		HC_Begin_Contents_Search(".", "segments");
			HC_Show_Contents_Count(&num);
			seg_list = new HC_KEY[num];
			while(HC_Find_Contents(0, &seg_list[i++]));
		HC_End_Contents_Search();
	HC_Close_Segment();

	sscanf(item->m_pItemText, "SEGMENTS %d-%d", &low, &high);
	--low;

	for(i=low; i<high; ++i)
		VerifyChildren(AddSegmentItem(seg_list[i], item));

	delete [] seg_list;
}

void HoopsSegmentTree::ExpandReferenceGroupItem(TreeGraphItem *item, HC_KEY key)
{
	bool expanding_segment = (strcmp(item->m_pParentItem->m_pItemText, "SEGMENT_REF") == 0);
	char type[MVO_BUFFER_SIZE];
	int low, high, num=0, i=0, seg_cnt=0, geo_cnt=0;
	HC_KEY ref_key;
	HC_KEY * ref_list;

	HC_Open_Segment_By_Key(key);
		//count the different reference types
		HC_Begin_Contents_Search(".", "references");
			while(HC_Find_Contents(type, &ref_key))
			{
				key=HC_KShow_Reference_Geometry(ref_key);
				HC_Show_Key_Type(key, type);
				if(streq(type, "segment"))
					++seg_cnt;
				else
					++geo_cnt;
			}
		HC_End_Contents_Search();

		//get a list of the appropriate length
		num = (expanding_segment ? seg_cnt : geo_cnt);
		ref_list = new HC_KEY[num];

		//put the right kind of references in the list
		HC_Begin_Contents_Search(".", "references");
			while(HC_Find_Contents(type, &ref_key))
			{
				key=HC_KShow_Reference_Geometry(ref_key);
				HC_Show_Key_Type(key, type);
				if(expanding_segment && streq(type, "segment"))
					ref_list[i++] = ref_key;
				else if(!expanding_segment && !streq(type, "segment"))
					ref_list[i++] = ref_key;
			}
		HC_End_Contents_Search();			
	HC_Close_Segment();

	sscanf(item->m_pItemText, "REFERENCES %d-%d", &low, &high);
	--low;

	for(i=low; i<high; ++i)
	{
		if(expanding_segment)
			AddSegmentReference(ref_list[i], item);
		else
		{
			HoopsReference refType;
			char text2[MVO_BUFFER_SIZE], text[MVO_BUFFER_SIZE];

			refType.GetData(ref_list[i], text2);
			sprintf(text, "%X - %s - %s", ref_list[i], refType.GetName(), text2);
			TreeGraphItem *newitem = (TreeGraphItem *)item->AddChildItem(H_TEXT(text),(void *)ref_list[i]);
			newitem->m_Flags = GEOMETRY_REFERENCE | (item->m_Flags & READONLY_OBJECT);
			newitem->m_Type = GEOMETRYITEM;
			SetItemImage(newitem, newitem->m_Type);
			newitem->SetHasChildren(true);
		}
	}

	delete [] ref_list;
}

static bool ok_to_select(HC_KEY key, HBaseView * view)
{
	HC_KEY incl_key, root_key, model_key;
	char key_type[MVO_BUFFER_SIZE];

	root_key=HC_KCreate_Segment("/");
	model_key=view->GetModelKey();
	incl_key=HC_KShow_Owner_Original_Key(model_key);

	HC_Show_Key_Type(key, key_type);

	if (streq(key_type, "style") || streq(key_type, "named style") || 
		streq(key_type, "include")|| streq(key_type, "reference"))
		return false;

	if(key==root_key)
		return false;
	else if(key==model_key)
		return true;

	while(key!=root_key)
	{
		key=HC_KShow_Owner_Original_Key(key);

		if(key==incl_key || key==model_key)
			return true;
	}

	return false;
}

void HoopsSegmentTree::OnImageClicked(TreeGraphItem *item) 
{
	HC_KEY key = (HC_KEY)item->m_pExtraData;

	if(item->m_Flags & READONLY_OBJECT)
		return;

	if (item->m_pExtraData && (HC_KEY)item->m_pExtraData != INVALID_KEY &&
		(!item->m_Flags || !(item->m_Flags & STATIC_MODEL | GEOMETRY_REFERENCE | SEGMENT_REFERENCE)))
	{	
		HC_KEY keys[256];
		int keynum;

		GetKeyList(item, keys, keynum);
		HSSelectionSet *selection = (HSSelectionSet *)m_Selection;

#ifdef HOOPS_ONLY
		int sl = selection->GetSelectLevel();
		HViewSelectionLevel lvl  = m_pView->GetViewSelectionLevel();
		selection->SetSelectLevel(ENTITY_TYPE);
		m_pView->SetViewSelectionLevel(HSelectionLevelEntity);
#endif // HOOPS_ONLY

		if(ok_to_select(key, m_pView))
		{
			if (((HSelectionSet *)selection)->IsSelected(key, keynum,keys))
				((HSelectionSet *)selection)->DeSelect(key, keynum, keys, true);	
			else
				((HSelectionSet *)selection)->Select(key, keynum, keys, true);
		}

#ifdef HOOPS_ONLY
		selection->SetSelectLevel(sl);
		m_pView->SetViewSelectionLevel(lvl);
#endif // HOOPS_ONLY

		m_pView->Update();
	}
	SetItemImage(item, item->m_Type);
	ValidateSegmentTree();

}

void HoopsSegmentTree::ValidateSegmentTreeRecursive(TreeGraphItem *item)
{
	sii_passthru pt;

	START_LIST_ITERATION(TreeGraphItem, item->m_ChildItemList)
	if (temp->m_ChildItemList)
	{
		if (temp->m_bExpanded)
			ValidateSegmentTreeRecursive(temp);

		SetItemImage(temp, temp->m_Type, &pt);
	}		
	END_LIST_ITERATION(item->m_ChildItemList);
}






bool HoopsSegmentTree::FindSelectedItemsRecursive(TreeGraphItem *item)
{
	bool expand = false;
	
	START_LIST_ITERATION(TreeGraphItem, item->m_ChildItemList)
		if (temp->m_pExtraData)
		{
			if (m_Selection->IsSelected((HC_KEY)temp->m_pExtraData))
				expand = true;
			bool tempexpand = temp->m_bExpanded;
			if (!temp->m_bExpanded)
			{
				ExpandSegmentItem(temp, (HC_KEY)temp->m_pExtraData);
				temp->Expand();
			}
			if (FindSelectedItemsRecursive(temp))
				expand = true;
			else
			{
				if (!tempexpand)
					temp->UnExpand();
			}

		}
		END_LIST_ITERATION(item->m_ChildItemList);	
		if (expand)
		{
			if (!item->m_bExpanded)	
			{
				ExpandSegmentItem(item, (HC_KEY)item->m_pExtraData);
				item->Expand();
			}
			return true;
		}
		else 
			return false;
}



void HoopsSegmentTree::UndefineAttribute(TreeGraphItem *item)
{

	char type[MVO_BUFFER_SIZE];
	bool is_segment=false;
	HC_KEY key=(HC_KEY)item->m_pParentItem->m_pExtraData;
	
	HC_Show_Key_Type(key, type);
	if(strcmp(type, "segment")==0)
		is_segment=true;

	if(is_segment)
		HC_Open_Segment_By_Key(key);
	else
		HC_Open_Geometry(key);

	START_LIST_ITERATION(HoopsAttribute, m_AttributeList)	   
		if (strcmp(temp->GetName(),item->m_pItemText2) == 0 && temp->Exists())
		{
			temp->UnSet();
			item->m_pParentItem->DeleteChildItem(item);
			break;
		}
		END_LIST_ITERATION(m_AttributeList);
	
	if(is_segment)
		HC_Close_Segment();
	else
		HC_Close_Geometry();
}


void HoopsSegmentTree::ShowNetAttribute(TreeGraphItem *item, char *attname, char *outtext)
{


	HC_Open_Segment_By_Key((HC_KEY)item->m_pExtraData);
	START_LIST_ITERATION(HoopsAttribute, m_AttributeList)	   
		if (strcmp(temp->GetName(),attname) == 0)
		{
			temp->ShowNet(outtext);
			break;
		}
		END_LIST_ITERATION(m_AttributeList);
		HC_Close_Segment();
}



void HoopsSegmentTree::ValidateSegmentTree() 
{
	ValidateSegmentTreeRecursive(m_pTreeGraph->GetRootItem());
}
void HoopsSegmentTree::FindSelectedItems() 
{
	FindSelectedItemsRecursive(m_pTreeGraph->GetRootItem());
}


void HoopsSegmentTree::OnSelectionChanged(TreeGraphItem *item) 
{
	SetCurrentItem(item);

	VisualizeBoundings(item, m_pView, m_VisualizeBoundings);

	if(!m_ShowInfo)
		return;

	if (!IsAttribute(item) && !IsDefine(item) && !IsGeometry(item))
		m_pTreeGraph->ResetInfoContent();

	if (item->m_pExtraData && (HC_KEY)item->m_pExtraData != -1 && !IsGeometry(item) && !IsReference(item) )
	{	
		m_pTreeGraph->ResetInfoContent();

		if (!HC_Show_Existence_By_Key((HC_KEY)item->m_pExtraData, "self"))
		{
			OnItemExpanding(item->m_pParentItem, true);
			return;
		}

		char text[MVO_BUFFER_SIZE];
		HC_Show_Key_Type((HC_KEY)item->m_pExtraData, text);

		if (strcmp(text, "segment") == 0)
		{
			char fullpath[4096];
			long prio;

			HC_Show_Segment((HC_KEY)item->m_pExtraData, fullpath);
			m_pTreeGraph->AddInfoString(fullpath);
			sprintf(fullpath, "Key: %X", (HC_KEY)item->m_pExtraData);
			m_pTreeGraph->AddInfoString(fullpath);

			//fullpath isn't needed anymore so I'll recycle it
			HC_Show_Priority((HC_KEY)item->m_pExtraData, &prio);
			sprintf(fullpath, "Priority: %ld", prio);
			m_pTreeGraph->AddInfoString(fullpath);

			fullpath[0]='\0';
			show_bounding_by_key((HC_KEY)item->m_pExtraData, fullpath);
			if(fullpath[0]!='\0')
				m_pTreeGraph->AddInfoString(fullpath);

			HModelInfo	*ModelInfo;
			ModelInfo = new HModelInfo((HC_KEY)item->m_pExtraData);
			ModelInfo->ComputeModelInfo(); 

			print_segment_contents_non_geometry(ModelInfo, m_pTreeGraph);
			print_segment_contents_geometry(ModelInfo, m_pTreeGraph);

			delete ModelInfo;
		}
	}
	else if(IsGeometry(item) || IsReference(item) )
	{
		HC_KEY key=(HC_KEY)item->m_pExtraData;
		char text[MVO_BUFFER_SIZE];

		if(!key || key==INVALID_KEY)
			return;

		if (!HC_Show_Existence_By_Key((HC_KEY)item->m_pExtraData, "self"))
		{
			OnItemExpanding(item->m_pParentItem, true);
			return;
		}
		
		HC_Show_Key_Type(key, text);

		//trickiness for geometry under references
		if( (item->m_pParentItem && streq(item->m_pParentItem->m_pItemText,"GEOMETRY_REF"))
			|| (item->m_pParentItem && item->m_pParentItem->m_pParentItem 
				&& streq(item->m_pParentItem->m_pParentItem->m_pItemText,"SEGMENT_REF")) )
			m_pTreeGraph->AddInfoString(item->m_pItemText);


		if (streq(text, "shell") || streq(text, "mesh") || streq(text, "polycylinder"))
		{
			text[0]='\0';
			show_bounding_by_key(key, text);
			if(text[0]!='\0')
				m_pTreeGraph->AddInfoString(text);
		}
		else if(streq(text, "reference"))
		{
			HC_KEY ref_key=key;
			HC_KEY source_key;
			char type[4096];
			char filter[4096];

			if (item->m_pExtraData2 != 0)
				source_key=key=(HC_KEY)item->m_pExtraData2;
			else
				source_key=HC_KShow_Reference_Geometry(key);

			HC_Show_Key_Type(source_key, type);

			text[0]='\0';
			show_bounding_by_key(key, text);
			if(text[0]!='\0')
				m_pTreeGraph->AddInfoString(text);

			if(streq(type, "segment"))
			{
				HModelInfo	* ModelInfo;
				ModelInfo = new HModelInfo(source_key);
				ModelInfo->ComputeModelInfo(source_key, false);
				
				print_segment_contents_geometry(ModelInfo, m_pTreeGraph);

				delete ModelInfo;
			}
			else
			{
				HC_KEY geo_parent;
				char parent_name[MVO_BUFFER_SIZE];

				geo_parent=HC_KShow_Owner_Original_Key(source_key);
				HC_Show_Segment(geo_parent, parent_name);
				m_pTreeGraph->AddInfoString(parent_name);
			}

			HC_Show_Reference_Geometry_Filter(ref_key, filter);
			if(streq("geometry",filter))
				m_pTreeGraph->AddInfoString("no filter");
			else
				m_pTreeGraph->AddInfoString(filter);
		}
	}
	else if(item->m_pParentItem && streq(item->m_pParentItem->m_pItemText, "GEOMETRY"))
	{
		HC_KEY container_key=(HC_KEY)item->m_pParentItem->m_pParentItem->m_pExtraData;
		char type[MVO_BUFFER_SIZE];
		int count=0;

		HC_Show_Key_Type(container_key, type);
		if(streq(type, "reference"))
			container_key=HC_KShow_Reference_Geometry(container_key);

		HC_Open_Segment_By_Key(container_key);
			HC_Begin_Contents_Search(".", item->m_pItemText);
				HC_Show_Contents_Count(&count);
			HC_End_Contents_Search();
		HC_Close_Segment();

		sprintf(type, "%d %s of geometry", count, (count==1 ? "piece" : "pieces") );
		m_pTreeGraph->AddInfoString(type);
	}
	else
	{
		if (!IsAttribute(item) && !IsDefine(item))
			m_pTreeGraph->ResetInfoContent();

	}
}

void HoopsSegmentTree::DrawTextInInfoWindow(TreeGraphItem *item, int width)
{
	unsigned int BLENGTH = (float)width/5.5f;
	if (IsAttribute(item) || IsDefine(item) || IsGeometry(item))
	{
		char newt[MVO_BIG_BUFFER_SIZE];
		strncpy(newt, item->m_pItemText, MVO_BIG_BUFFER_SIZE-1);
		newt[MVO_BIG_BUFFER_SIZE-1] = 0;

		char *newtext = newt;
		//    int length = 0;
		m_pTreeGraph->ResetInfoContent();

		bool getout = false;
		while(1)
		{
			char sav = 0;
			if (strlen(newtext)>BLENGTH)
			{
				sav = newtext[BLENGTH-1];
				newtext[BLENGTH-1] = 0;
			}
			else 
				getout = true;
			m_pTreeGraph->AddInfoString(newtext);
			if (getout)
				break;
			else
				newtext[BLENGTH-1] = sav;
			newtext+=BLENGTH-1;
		}
	}
}


void HoopsSegmentTree::ExtendAttributeText(const char *type, char *text, char *final) 
{
	_snprintf_s(final, MVO_BIG_BUFFER_SIZE, _TRUNCATE, "%s <%s>", type, text);
}

void HoopsSegmentTree::FoldAttributeText(const char *text, char *foldedtext) 
{
	const char *res = strstr(text, "<");
	const char *res2 = strstr(text, ">");
	if (!res || !res2)
	{
		res = text;
		strcpy(foldedtext, res);
	}
	else
	{    
		strcpy(foldedtext, res+1);
		if (foldedtext[strlen(foldedtext)-1] == '>')
			foldedtext[strlen(foldedtext)-1] = 0;
	}
}


void HoopsSegmentTree::DeleteSegment(TreeGraphItem *item)
{
	TreeGraphItem * parent = item->m_pParentItem;
	if (m_Selection)
		m_Selection->DeSelectAll();
	
	if(item->m_Flags & READONLY_OBJECT)
		return;

	HC_Delete_By_Key((HC_KEY)item->m_pExtraData);
	parent->DeleteChildItem(item);

	if(strstr(parent->m_pItemText, "SEGMENTS") && !parent->m_pExtraData)
		OnItemExpanding(parent->m_pParentItem, true);
}

void HoopsSegmentTree::EditInPlace(TreeGraphItem *item)
{
	item->EditInPlace();
}

void HoopsSegmentTree::ExpandSpecificGeometry(TreeGraphItem *item, HC_KEY key)
{
	struct vlist_s*	childList = item->m_ChildItemList;
	
	START_LIST_ITERATION(TreeGraphItem, childList)
		item->DeleteChildItem(temp);
		vlist_reset_cursor(childList);
	}   //END_LIST_ITERATION(childList);

	

	ExpandGeometryAttributeItem(item, key);
}

void HoopsSegmentTree::ExpandSpecificReference(TreeGraphItem *item, HC_KEY key)
{
	struct vlist_s*	childList = item->m_ChildItemList;
	
	START_LIST_ITERATION(TreeGraphItem, childList)
		item->DeleteChildItem(temp);
		vlist_reset_cursor(childList);
	} 

	//--------------------------------------------------
	START_LIST_ITERATION(HoopsAttribute, m_GeometryAttributeList_Ref)	   
		ExpandAttributeType(item, key, temp->GetName());
	END_LIST_ITERATION(m_GeometryAttributeList_Ref);

	if(item->m_Flags & GEOMETRY_REFERENCE)
	{
		AddGeometryReference(key, item);
	}
	else if(item->m_Flags & SEGMENT_REFERENCE)
	{
		int num;
		HC_KEY seg_key;
		char filter[MVO_BUFFER_SIZE];
		bool refs_exist = false;

		seg_key=HC_KShow_Reference_Geometry(key);
		HC_Show_Reference_Geometry_Filter(key, filter);
		if(!strstr(filter, "no reference"))
			strcat(filter, ", no reference");

		HC_Open_Segment_By_Key(seg_key);
			HC_Begin_Contents_Search(".", filter);
				HC_Show_Contents_Count(&num);
			HC_End_Contents_Search();
			if(HC_Show_Existence("reference"))
				refs_exist = true;
		HC_Close_Segment();

		if (num)
		{
			TreeGraphItem *item2 = item->AddChildItem(_T("GEOMETRY"),0, true);
			item2->m_Type = GEOMETRYITEM;
			SetItemImage(item2, item2->m_Type);
			item2->m_Flags = (item->m_Flags & READONLY_OBJECT);
			item2->SetHasChildren(true);
		}
		if(refs_exist)
		{
			TreeGraphItem *item2 = item->AddChildItem(_T("REFERENCES"),0, true);
			item2->m_Type = INCLUDEITEM;
			SetItemImage(item2, item2->m_Type);
			item2->m_pExtraData = (void *)seg_key;
			item2->m_Flags = (item->m_Flags & READONLY_OBJECT);
			item2->SetHasChildren(true);
		}

	}
}

void HoopsSegmentTree::GetKeyList(TreeGraphItem *item, HC_KEY *keys, int &keynum, bool verbose)
{
	keynum=0;

	if(verbose)
	{
		//new more complete path
		HC_KEY key=(HC_KEY)item->m_pExtraData;
		HC_KEY key2=(HC_KEY)item->m_pExtraData2;
		TreeGraphItem *current=item;
		char type[MVO_BUFFER_SIZE];

		if (key2) 
			keys[keynum++]=key2;
	
		HC_Show_Key_Type(key, type);

		//walk up the tree to acquire an include path
		if(streq(type, "segment")) {
			keys[keynum++]=key;
		}
		else {
			keys[keynum++]=key;
			keys[keynum++]=HC_KShow_Owner_Original_Key(key);
		}
			
		while((current=current->m_pParentItem) != 0)
		{
			HC_KEY current_key=(HC_KEY)current->m_pExtraData;
			if (current_key && current_key!=INVALID_KEY && current_key != key &&
				HC_Show_Existence_By_Key(current_key, "self"))
			{
				HC_Show_Key_Type(current_key, type);

				if(streq(type, "include") || streq(type, "segment"))
					keys[keynum++]=current_key;
			}
		}
			
		keys[keynum++]=m_pView->GetIncludeLinkKey();
		keys[keynum++]=m_pView->GetViewKey();
		keys[keynum++]=INVALID_KEY;
	}
	else
	{
		//old style
		TreeGraphItem *currentitem = item;
		while (1)
		{
			HC_KEY key = (HC_KEY)currentitem->m_pExtraData;
			if (key && key!=-1)
			{
				char type[64];
				HC_Show_Key_Type(key, type);
				if (strcmp(type, "include") == 0)
					keys[keynum++] = (HC_KEY)currentitem->m_pExtraData;
				if (key == m_pView->GetModelKey() && currentitem->m_pParentItem == 0)
					keys[keynum++] = m_pView->GetIncludeLinkKey();

			}
			currentitem=currentitem->m_pParentItem;
			if (!currentitem)
				break;
		}
		for (int i=0;i<keynum/2;i++)
		{
			HC_KEY temp = keys[i];
			keys[i] = keys[keynum-1-i];
			keys[keynum-1-i] = temp;
		}
	}
}


void HoopsSegmentTree::GetNameAndDefinition(TreeGraphItem *item, char *name, char *definition)
{

	char definename[MVO_BUFFER_SIZE];

	strcpy(definename,item->m_pParentItem->m_pItemText);

	START_LIST_ITERATION(HoopsDefineGeometry, m_DefineList)	   
		if (strcmp(definename, temp->GetName()) == 0)
		{
			temp->GetNameAndDefinition(item->m_pItemText, name, definition);
			break;
		}
	END_LIST_ITERATION(m_DefineList);
}

static void flush_contents_recursive(HC_KEY key, const char *type, bool follow_includes)
{
    HC_KEY includee, inckey;

    HC_Open_Segment_By_Key (key);
        if(follow_includes)
		{
			HC_Begin_Contents_Search ("...", "includes");
			while (HC_Find_Contents (0, &inckey)) {
			    includee = HC_KShow_Include_Segment (inckey);
		        flush_contents_recursive(includee, type, follow_includes);
	        }
			HC_End_Contents_Search ();
		}
        HC_Flush_Contents ("...", type);
    HC_Close_Segment();
} 

void HoopsSegmentTree::FlushSegmentContents(TreeGraphItem *item, const char *type, bool follow_includes)
{
	if (m_Selection)
		m_Selection->DeSelectAll();
	
	if(item->m_Flags & READONLY_OBJECT)
		return;

	flush_contents_recursive((HC_KEY)item->m_pExtraData, type, follow_includes);

	ExpandSegmentItem(item, (HC_KEY)item->m_pExtraData);
	OnSelectionChanged(item);

	m_pView->Update();
}





