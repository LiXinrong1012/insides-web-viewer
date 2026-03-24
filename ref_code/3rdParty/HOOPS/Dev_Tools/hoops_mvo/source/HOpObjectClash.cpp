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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HOpObjectClash.cpp,v 1.87 2009-10-08 17:38:56 nathan Exp $
//

#include <math.h>
#include <string.h>
#include <stdio.h>

#include "HTools.h"

#include "HBaseModel.h"
#include "HBaseView.h"
#include "HBaseOperator.h"
#include "HEventInfo.h"
#include "HOpObjectClash.h"
#include "HSelectionSet.h"
#include "HSelectionItem.h"
#include "vlist.h"

#include "HUndoManager.h"

class HKeyList: public VList<HC_KEY>
{
};



float big_float[10000];
int big_int[1000];

/////////////////////////////////////////////////////////////////////////////
// HOpObjectClash
//
// Translate items in the selection list in direction of mouse movement
// parallel to camera target plane.
//
// Currently supports translation if item if it is a segment


HOpObjectClash::HOpObjectClash(HBaseView* view, int DoRepeat,int DoCapture) : 
	HOpObjectTranslate(view, DoRepeat, DoCapture)
{
	m_pClashSelection = new HSelectionSet(view, true);
	m_pClashSelection->Init();

	m_TempSegKey = INVALID_KEY;
	m_SelectMode = HOOC_Shell;
	m_IntersectPolylinesVisible = false;

	// disable spriting
	m_save_spriting_mode = GetView()->GetSpritingMode();
	if( m_save_spriting_mode )
		GetView()->SetSpritingMode(false);
}


HOpObjectClash::~HOpObjectClash()
{
	if( m_save_spriting_mode )
		GetView()->SetSpritingMode(m_save_spriting_mode);
	delete m_pClashSelection;
	if(m_TempSegKey != INVALID_KEY)
	{
		HC_Delete_By_Key( m_TempSegKey );
		m_TempSegKey = INVALID_KEY;
	}
}


void HOpObjectClash::GrabSelectionSet()
{
	int i, size;
	HC_KEY object;
	char type[64];
	HSelectionSet *selection;
	HPixelRGBA rgba;
	HPixelRGB rgb;

	selection = GetView()->GetSelection();
	m_pClashSelection->DeSelectAll();
	m_pClashSelection->SetHighlightMode(selection->GetHighlightMode());
	selection->GetSelectionFaceColor(rgba);
	m_pClashSelection->SetSelectionFaceColor(rgba);
	selection->GetSelectionEdgeColor(rgba);
	m_pClashSelection->SetSelectionEdgeColor(rgba);
	selection->GetSelectionMarkerColor(rgba);
	m_pClashSelection->SetSelectionMarkerColor(rgba);
	HC_Open_Segment_By_Key( GetView()->GetSceneKey() );
		m_TempSegKey = HC_KOpen_Segment( "HOpObjectClash_temp" );
			HC_Set_Window( -1, 1, -1, 1 );
			HC_Set_Camera_By_Volume( "stretched", -1, 1, -1, 1 );
			HC_Set_Window_Pattern( "clear" );
			HC_Set_Visibility( "everything = off" );
		HC_Close_Segment();
	HC_Close_Segment();
	SetSelectMode( m_SelectMode );


	//turn off selectability of the selected objects
	size = selection->GetSize();
	for( i = 0; i < size; ++i ) 
	{
		object = selection->GetAt(i);
		HC_Show_Key_Type( object, type );
		if( streq( type, "segment" ) ) 
		{
			HC_Open_Segment_By_Key( object );
				HC_Set_Selectability( "everything = off" );
			HC_Close_Segment();	
		}
		else 
		{
			selection->DeSelect(object, 0, 0, true);
		}
	}
}

void HOpObjectClash::RestoreSelectionSet()
{
	HC_KEY object;
	int i=0;

	//unset the selectability setting that we set during GrabSelectionSet
	while(object = m_KeyList->NthItem(i++))
	{
		HC_Open_Segment_By_Key(object);
			HC_UnSet_Selectability();
		HC_Close_Segment();
	}

	m_pClashSelection->DeSelectAll();
}

void HOpObjectClash::UpdateKeyList(void * data)
{
	if((HSelectionSet *)data!=m_pClashSelection)
	{
		//order is important
		RestoreSelectionSet();
		Cleanup();
		Init();
		GrabSelectionSet();
	}
}


HBaseOperator * HOpObjectClash::Clone()
{
	return (HBaseOperator *)new HOpObjectClash(GetView());
}


const char * HOpObjectClash::GetName() { return "HOpObjectClash"; }


int HOpObjectClash::GetScreenVolume( HC_KEY seg, HPoint &min, HPoint &max ) 
{
	int i;
	HPoint	bbx[2], bbox[8];
	float matrix[16];

	// get min/max and enumerate the 8 corner points around seg's bounding cuboid
	HC_Open_Segment_By_Key( seg );
		HC_Compute_Circumcuboid(".", &bbx[0], &bbx[1]);
		HUtility::GenerateCuboidPoints (&bbx[0], &bbx[1], bbox);
		HC_Show_Net_Modelling_Matrix( matrix );
	HC_Close_Segment();

	// get the screen space min/max 
	HC_Open_Segment_By_Key(GetView()->GetSceneKey());
		HC_Open_Segment("dummy");
			HC_Set_Modelling_Matrix (matrix);
			for( i = 0 ; i < 8 ; i++ ) {
				HC_Compute_Coordinates(".", "object", &bbox[i], "local window", &bbox[i]);
				HUtility::ClampPointToWindow(&bbox[i]);
			}
		HC_Close_Segment();
	HC_Close_Segment();
	min = bbox[0];
	max = bbox[0];
	for( i = 1 ; i < 8 ; i++ )
	{
		if (min.x > bbox[i].x) min.x = bbox[i].x;
		if (min.y > bbox[i].y) min.y = bbox[i].y;
		if (min.z > bbox[i].z) min.z = bbox[i].z;
		if (max.x < bbox[i].x) max.x = bbox[i].x;
		if (max.y < bbox[i].y) max.y = bbox[i].y;
		if (max.z < bbox[i].z) max.z = bbox[i].z;
	}
	return HOP_OK;
}


int HOpObjectClash::IntersectPolyline( 
		HC_KEY shell1, 
		float *transformed_points1 )
{
	int point_count1, face_list_length1;
	const int *face_list1;
	int point_count2, face_list_length2;
	const int *face_list2;
	const float *points2;
	int i, polyline_count, polyline_point_count;
	int *polyline_lengths = big_int;
	float *polyline_points = big_float;
	float *ptr;
	HC_KEY shell2;
	float *transformed_points2;
	int offset1, offset2, offset3;
	float modelling_matrix[16];
	int selection_keys_count;
	HC_KEY selection_keys[64];
		
	if( shell1 == INVALID_KEY || transformed_points1 == 0 )
		return 0;
	//assumes that the thing that we are clashing against is on HOOPS' selection stack
	HC_Show_Selection_Element( &shell2, &offset1, &offset2, &offset3 );
	HC_Show_Shell_Size( shell2, &point_count2, 0 );
	if( point_count2 == 0 )
		return 0;
	HC_Show_Geometry_Pointer( shell2, "points", &points2 );
	transformed_points2 = new float[ 3 * point_count2 ];
	HC_Show_Selection_Keys( &selection_keys_count, selection_keys );
	HC_PShow_Net_Modelling_Matrix( selection_keys_count, selection_keys, modelling_matrix );
	HC_Compute_Transformed_Points( 
			point_count2, 
			points2, 
			modelling_matrix, 
			transformed_points2 ); 

	HC_Show_Shell_Size( shell1, &point_count1, &face_list_length1 );
	HC_Show_Geometry_Pointer( shell1, "face list", &face_list1 );
	HC_Show_Shell_Size( shell2, &point_count2, &face_list_length2 );
	HC_Show_Geometry_Pointer( shell2, "face list", &face_list2 );
	HC_Compute_Intersect_Polyline ( 
			point_count1, 
			(const struct ht_point *)transformed_points1, 
			face_list_length1, 
			face_list1,
			point_count2, 
			(const struct ht_point *)transformed_points2, 
			face_list_length2, 
			face_list2,
			&polyline_count,
			polyline_lengths,
			&polyline_point_count,
			(struct ht_point *)polyline_points );
	if( m_IntersectPolylinesVisible ) {
		HC_Open_Segment_By_Key( GetView()->GetIntersectPolylinesKey() );
			ptr = polyline_points;
			for( i = 0 ; i < polyline_count ; i++ ) {
				HC_Insert_Polyline( polyline_lengths[i], ptr );
				ptr += 3*polyline_lengths[i];
			}
		HC_Close_Segment();
	}
	delete [] transformed_points2;
	return polyline_count;

} //end function IntersectPolyline


int HOpObjectClash::TestEnclosure( 
		HC_KEY shell1, 
		float *transformed_points1 )
{
	int point_count1, face_list_length1;
	const int *face_list1;
	int point_count2, face_list_length2;
	const int *face_list2;
	const float *points2;
	HC_KEY shell2;
	float *transformed_points2 = 0;
	float modelling_matrix[16];
	int selection_keys_count;
	HC_KEY selection_keys[64];
	enum HOOC_Result return_val = HOOC_Unknown;
	char tempstr[128];
		
	if( shell1 == INVALID_KEY || transformed_points1 == 0 )
		goto done;
	//assumes that the thing that we are clashing against is on HOOPS' selection stack
	HC_Show_Selection_Element( &shell2, 0, 0, 0 );
	HC_Show_Shell_Size( shell2, &point_count2, 0 );
	if( point_count2 == 0 )
		goto done;
	HC_Show_Geometry_Pointer( shell2, "points", &points2 );
	transformed_points2 = new float[ 3 * point_count2 ];
	HC_Show_Selection_Keys( &selection_keys_count, selection_keys );
	HC_PShow_Net_Modelling_Matrix( selection_keys_count, selection_keys, modelling_matrix );
	HC_Compute_Transformed_Points( 
			point_count2, 
			points2, 
			modelling_matrix, 
			transformed_points2 ); 
	HC_Show_Shell_Size( shell1, &point_count1, &face_list_length1 );
	HC_Show_Geometry_Pointer( shell1, "face list", &face_list1 );
	HC_Show_Shell_Size( shell2, &point_count2, &face_list_length2 );
	HC_Show_Geometry_Pointer( shell2, "face list", &face_list2 );
	HC_Compute_Shell_Enclosure ( 
			point_count1, 
			(const struct ht_point *)transformed_points1, 
			face_list_length1, 
			face_list1,
			point_count2, 
			(const struct ht_point *)transformed_points2, 
			face_list_length2, 
			face_list2,
			tempstr );
	if( streq( tempstr, "clash" ) )
			return_val = HOOC_Clash;
	else if( streq( tempstr, "in" ) )
		return_val = HOOC_In;
	else if( streq( tempstr, "out" ) )
		return_val = HOOC_Out;
	else
		return_val = HOOC_Unknown;

	done:
	delete [] transformed_points2;
	return return_val;

} //end function TestEnclosure


void HOpObjectClash::ProcessSelectionResults( HC_KEY current_shell_key, float *transformed_points )
{
	HC_KEY	hit_object;
	char	sel_type[MVO_BUFFER_SIZE];
	int result;

	assert(m_pClashSelection);

	do {
		HC_Show_Selection_Original_Key( &hit_object );
		HC_Show_Key_Type( hit_object, sel_type );

		// build up an array of include keys to pass with the selection
		int skey_count;
		char skey_type[MVO_BUFFER_SIZE];
		HC_Show_Selection_Keys_Count(&skey_count);

		HC_KEY *keys		= new HC_KEY[skey_count];
		HC_KEY *incl_keys	= new HC_KEY[skey_count];
		HC_Show_Selection_Keys(&skey_count, keys);

		int i, incl_count = 0;
		for(i = skey_count-1; i >= 0; i--)
		{
			HC_Show_Key_Type(keys[i], skey_type);
			if(strstr(skey_type, "include"))
			{
				incl_keys[incl_count] = keys[i];
				incl_count++;
			}
		}

		if( m_IntersectPolylinesVisible && m_SelectMode == HOOC_Shell && streq( sel_type, "shell" ))
			IntersectPolyline( current_shell_key, transformed_points );

		if( m_pClashSelection->IsSelected( hit_object, incl_count, incl_keys ) )
		{
			delete[] keys;
			delete[] incl_keys;
			continue;
		}

		//Ignore multi-instancing effects for now
		if( m_SelectMode == HOOC_Enclosure ) 
		{
			result = TestEnclosure( current_shell_key, transformed_points );
			if( result == HOOC_In ) 
			{
				/* Change the highlight style to red and restore */
				HPixelRGBA new_hilite_color, saved_hilite_color;
				m_pClashSelection->GetSelectionFaceColor(saved_hilite_color);
				new_hilite_color.Set(255, 0, 0, 0);
				m_pClashSelection->SetSelectionFaceColor(new_hilite_color);
				m_pClashSelection->Select( hit_object, incl_count, incl_keys, false );
				m_pClashSelection->SetSelectionFaceColor(saved_hilite_color);
			}
		}
		else {
				m_pClashSelection->Select( hit_object, incl_count, incl_keys, false );
		}

		delete[] keys;
		delete[] incl_keys;

	} while( HC_Find_Related_Selection() );
}



int HOpObjectClash::SelectByScreenVolume( HSmartSelItem * sel_item )
{
	HC_KEY seg = sel_item->GetKey();
	int 	hit_found = 0;
	HPoint	min, max;

	while( IsSpecialKey( seg ) )
		seg = HC_KShow_Owner_By_Key( seg );

	GetScreenVolume( seg, min, max );
	// compute the selection
	HC_Open_Segment_By_Key(GetView()->GetViewKey());
		HC_QSet_Heuristics ("./scene/overwrite", "no related selection limit" );
		HViewSelectionLevel lvl = GetView()->GetViewSelectionLevel();
		GetView()->SetViewSelectionLevel(HSelectionLevelEntity);
		hit_found = HC_Compute_Selection_By_Volume(
					".", 
					"./scene/overwrite", 
					"v", 
					min.x, max.x, min.y, 
					max.y, min.z, max.z );
		GetView()->SetViewSelectionLevel(lvl);
		HC_QUnSet_Heuristics ("./scene/overwrite" );
	HC_Close_Segment();
	if( hit_found )
		ProcessSelectionResults();
	return HOP_OK;
}


int HOpObjectClash::GetWorldVolume( HC_KEY seg, HPoint &min, HPoint &max ) 
{
	int i;
	HPoint	bbx[2], bbox[8];
	float matrix[16];

	// get min/max and enumerate the 8 corner points around seg's bounding cuboid
	HC_Open_Segment_By_Key( seg );
		HC_Compute_Circumcuboid(".", &bbx[0], &bbx[1]);
		HUtility::GenerateCuboidPoints (&bbx[0], &bbx[1], bbox);
		HC_Show_Net_Modelling_Matrix( matrix );
	HC_Close_Segment();

	// get the screen space min/max 
	HC_Open_Segment_By_Key(GetView()->GetSceneKey());
		HC_Open_Segment("dummy");
			HC_Set_Modelling_Matrix (matrix);
			for( i = 0 ; i < 8 ; i++ ) {
				HC_Compute_Coordinates(".", "object", &bbox[i], "world", &bbox[i]);
			}
		HC_Close_Segment();
	HC_Close_Segment();
	min = bbox[0];
	max = bbox[0];
	for( i = 1 ; i < 8 ; i++ )
	{
		if (min.x > bbox[i].x) min.x = bbox[i].x;
		if (min.y > bbox[i].y) min.y = bbox[i].y;
		if (min.z > bbox[i].z) min.z = bbox[i].z;
		if (max.x < bbox[i].x) max.x = bbox[i].x;
		if (max.y < bbox[i].y) max.y = bbox[i].y;
		if (max.z < bbox[i].z) max.z = bbox[i].z;
	}
	return HOP_OK;
}


int HOpObjectClash::SelectByWorldVolume( HSmartSelItem * sel_item )
{
	HC_KEY	seg = sel_item->GetKey();
	int 	hit_found = 0;
	HPoint	min, max;

	while( IsSpecialKey( seg ) )
		seg = HC_KShow_Owner_By_Key( seg );

	GetWorldVolume( seg, min, max );
	// compute the selection
	HC_Open_Segment_By_Key(GetView()->GetViewKey());
		HC_QSet_Heuristics ("./scene/overwrite", "no related selection limit" );
		HViewSelectionLevel lvl = GetView()->GetViewSelectionLevel();
		GetView()->SetViewSelectionLevel(HSelectionLevelEntity);
		hit_found = HC_Compute_Selection_By_Volume(
					"", 
					"./scene/overwrite", 
					"v", 
					min.x, max.x, min.y, 
					max.y, min.z, max.z );
		GetView()->SetViewSelectionLevel(lvl);
		HC_QUnSet_Heuristics ("./scene/overwrite");
	HC_Close_Segment();
	if( hit_found ) {
		ProcessSelectionResults();
	} 
	return HOP_OK;
}


int HOpObjectClash::SelectByEnclosure( HSmartSelItem * sel_item )
{
	HC_KEY	seg = sel_item->GetKey();
	HC_KEY	key;
	int 	hit_found = 0;
	float	modelling_matrix[16];
	int 	point_count, face_list_length;
	float	*original_points = 0, *transformed_points = 0;
	int 	*face_list = 0;
	float	up[3] = { 0, 1, 0 };
	float	*start;
	HViewSelectionLevel lvl;
	HC_KEY *path = new HC_KEY[sel_item->GetIncludeCount()+2];
	int i;
	char type [MVO_BUFFER_SIZE];
		
	while( IsSpecialKey( seg ) )
		seg = HC_KShow_Owner_By_Key( seg );

	HC_Show_Key_Type(seg, type);
	if(!streq(type, "segment"))
		seg = HC_KShow_Owner_By_Key( seg );

	path[0]=seg;
	for(i=0; i<sel_item->GetIncludeCount(); ++i)
		path[i+1]=sel_item->GetIncludeKeys()[sel_item->GetIncludeCount()-i-1];

	if(path[i]!=GetView()->GetViewKey())
		path[++i]=GetView()->GetViewKey();


	HC_Open_Segment_By_Key( seg );
		HC_Begin_Contents_Search( ".", "shells" );
		while( HC_Find_Contents( 0, &key ) ) {
			HC_Show_Shell_Size( key, &point_count, &face_list_length );
			if( point_count == 0 )
				continue;
			HC_Show_Geometry_Pointer( key, "points", &original_points);
			HC_Show_Geometry_Pointer( key, "face list", &face_list );
			transformed_points = new float[ 3 * point_count ];
			HC_PShow_Net_Modelling_Matrix(i, path, modelling_matrix);
			HC_Compute_Transformed_Points( 
					point_count, 
					original_points, 
					modelling_matrix, 
					transformed_points ); 
			/* XXX for now, just select by the first shell (with real points) 
			 * in the selected segment */
			break;
		}
		HC_End_Contents_Search();
	HC_Close_Segment();
	if( face_list == 0 || original_points == 0 ) {
		//either there were no shells in the segment, or they were all empty 
		goto done;
	}
	start = &transformed_points[0];

	// compute the selection
	HC_Open_Segment_By_Key(GetView()->GetViewKey());
		HC_QSet_Heuristics( "./scene/overwrite", "no related selection limit, no selection sorting" );
		lvl = GetView()->GetViewSelectionLevel();
		GetView()->SetViewSelectionLevel(HSelectionLevelEntity);
		hit_found = HC_Compute_Selection_By_Ray( 
					"v",
					"./scene/overwrite", 
					start,
					up );
		GetView()->SetViewSelectionLevel(lvl);
		HC_QUnSet_Heuristics("./scene/overwrite");
	HC_Close_Segment();
	if( hit_found ) {
		ProcessSelectionResults( key, transformed_points );
	} 
	done:
	delete [] transformed_points;
	delete [] path;
	return HOP_OK;

} //end function SelectByEnclosure


int HOpObjectClash::SelectByShell( HSmartSelItem * sel_item )
{
	HC_KEY	seg = sel_item->GetKey();
	int 	hit_found = 0;
	int 	point_count, face_list_length;
	float	*original_points = 0, *transformed_points = 0;
	int 	*face_list = 0;
	HC_KEY	key;
	float	modelling_matrix[16];
	float	start_time, end_time;

	while( IsSpecialKey( seg ) )
		seg = HC_KShow_Owner_By_Key( seg );

	struct vlist_s *keylist;

	HC_Open_Segment_By_Key( seg );
	HUtility::ShowContentsWithPath("shells, references", &keylist, true);
	
	START_LIST_ITERATION(HShowContentsWithPathType, keylist);
		key = temp->patharray[temp->len-1]; 		
	 	HC_Show_Shell_Size( key, &point_count, &face_list_length );
		if( point_count == 0 )
			continue;
		HC_Show_Geometry_Pointer( key, "points", &original_points);
		HC_Show_Geometry_Pointer( key, "face list", &face_list );
		if( face_list == 0 )
			continue;
		transformed_points = new float[ 3 * point_count ];
		HC_PShow_Net_Modelling_Matrix(temp->len-1, temp->patharray, modelling_matrix );
		HC_Compute_Transformed_Points( 
				point_count, 
				original_points, 
				modelling_matrix, 
				transformed_points ); 

		// compute the selection
		HC_Open_Segment_By_Key(GetView()->GetViewKey());
			HC_QSet_Heuristics( "./scene/overwrite", "no related selection limit" );
			HViewSelectionLevel lvl = GetView()->GetViewSelectionLevel();
			GetView()->SetViewSelectionLevel(HSelectionLevelEntity);
			HC_Show_Time( &start_time );
			hit_found = HC_Compute_Selection_By_Shell( 
						"v",
						"./scene/overwrite", 
						point_count, 
						transformed_points, 
						face_list_length, 
						face_list );
			HC_Show_Time( &end_time );
			GetView()->SetViewSelectionLevel(lvl);
			HC_QUnSet_Heuristics("./scene/overwrite");
		HC_Close_Segment();

		if( hit_found ) {
			ProcessSelectionResults( key, transformed_points );
		} 
		delete [] transformed_points;		
		delete [] temp->patharray;
		delete temp;
	END_LIST_ITERATION(keylist);
	HC_Close_Segment();
	delete_vlist(keylist);
	if( face_list == 0 || original_points == 0 ) {
		//either there were no shells in the segment, or they were all empty 
		goto done;
	}

	done:
	return HOP_OK;
}
 

/////////////////////////////////////////////////////////////////////////////
// HOpObjectClash message handlers


void HOpObjectClash::ClashDetect(HEventInfo &event)
{
	int n;
	HC_KEY key;
	char keytype[64];
	float seg_matrix[16], tmatrix[16];
	int size;
	HSmartSelItem *sel_item = 0;
	HSelectionSet * selection=GetView()->GetSelection();

	HC_Open_Segment_By_Key( GetView()->GetCuttingPlaneGeomKey() );
	HC_Flush_Contents( ".", "geometry" );
	HC_Close_Segment();
	if( m_IntersectPolylinesVisible ) {
		HC_Open_Segment_By_Key( GetView()->GetIntersectPolylinesKey() );
			HC_Flush_Contents( ".", "geometry" );
		HC_Close_Segment();
	}

	size = selection->GetSize();
	
	int keycount = 0;
	HC_KEY *keys = new HC_KEY[size];
	float *matrices = new float[size * 16];

	// deselect everything from last time around
	m_pClashSelection->DeSelectAll();
	// calculate and apply modelling matrices to our local selection list
	for (n = 0; n < size; ++n)
	{
		key = selection->GetAt(n);
		HC_Show_Key_Type(key, keytype);
		if ((key != -1) && (streq(keytype, "segment"))) {
			sel_item = (HSmartSelItem *)selection->GetSelectionItemAt(n);
			GetMatrix( event, 
				sel_item->GetFullPathCount (GetView()), 
				(HC_KEY *)sel_item->GetFullPathKeys (GetView()), 
				tmatrix);
			while( IsSpecialKey( key ) )
				key = HC_KShow_Owner_By_Key( key );
			HC_Open_Segment_By_Key(key);
			HC_Set_Rendering_Options ("simple shadow=auto");
			if (GetView()->GetSpritingMode())
				HC_Set_Heuristics("quick moves = spriting");
				if (HC_Show_Existence ("modelling matrix")) {
					HC_Show_Modelling_Matrix (seg_matrix);
					HC_UnSet_Modelling_Matrix ();
					HC_Set_Modelling_Matrix( tmatrix );
					HC_Append_Modelling_Matrix (seg_matrix);
				}
				else {
					memset(seg_matrix,0,16*sizeof(float));
					seg_matrix[0] = seg_matrix[5] = seg_matrix[10] = seg_matrix[15] = 1;
					HC_Set_Modelling_Matrix( tmatrix );
				}
			HC_Close_Segment();

			keys[n] = key;
			memcpy(&matrices[n*16],seg_matrix,16*sizeof(float));
			keycount++;
		}
		switch( m_SelectMode ) {
			case HOOC_Enclosure:
				SelectByEnclosure( sel_item );
				break;
			case HOOC_World:
				SelectByWorldVolume( sel_item );
				break;
			case HOOC_Screen:
				SelectByScreenVolume( sel_item );
				break;
			case HOOC_Shell:
				SelectByShell( sel_item );
				break;
		}	
	}
	m_ptLast = GetNewPoint();
	UpdateMousePos(event);

	//save original matrix, and add to undo manager
	if(!m_bInitialMatrix)
	{
		m_bInitialMatrix = true;
		HUndoItemMatrix *item = new HUndoItemMatrix(GetView(), keycount, keys, matrices);
		GetView()->GetUndoManager()->AddUndoItem(item);
	}

	GetView()->SetGeometryChanged();

	delete[] keys;
	delete[] matrices;
}



int HOpObjectClash::OnLButtonDownAndMove(HEventInfo &event)
{
	if (!OperatorStarted()) 
		return HBaseOperator::OnLButtonDownAndMove(event);
	ClashDetect(event);
	GetView()->Update();
	return (HOP_OK);
}


// Mouse has come down
int HOpObjectClash::OnLButtonDown(HEventInfo &event)
{
	SetOperatorStarted(true);
	HOpObjectTranslate::OnLButtonDown(event);

	GrabSelectionSet();
	HC_Begin_Shell_Selection();
	ClashDetect(event);
	GetView()->ForceUpdate();

	return(HOP_OK);
}


// Mouse has come up 
int HOpObjectClash::OnLButtonUp(HEventInfo &event)
{
	HC_End_Shell_Selection();
	if( m_IntersectPolylinesVisible ) {
		HC_Open_Segment_By_Key( GetView()->GetIntersectPolylinesKey() );
			HC_Flush_Contents( ".", "geometry" );
		HC_Close_Segment();
	}
	RestoreSelectionSet();
	HOpObjectTranslate::OnLButtonUp(event);

	SetOperatorStarted(false);

	return(HOP_READY);
}


void HOpObjectClash::SetSelectMode( int mode )
{
	const char *text;

	switch( mode ) {
		case HOOC_Screen:
			text = "select mode = screen";
			break;
		case HOOC_Shell:
			text = "select mode = shell";
			break;
		case HOOC_World:
			text = "select mode = world";
			break;
		default:
			/* huh? this shouldn't happen */
			return; 
	}
	HC_Open_Segment_By_Key( m_TempSegKey );
		HC_Open_Segment( "select mode" );
			HC_Flush_Contents( ".", "text" );
			HC_Insert_Text( 0, -0.9, 0, text );
		HC_Close_Segment();
	HC_Close_Segment();
	m_SelectMode = mode;
}

int HOpObjectClash::OnKeyDown(HEventInfo &event)
{
	char the_char = event.GetChar();

	switch(the_char) {
		case 'd': /* for "driver" */
			m_SelectMode = HOOC_Screen;
			break;

		case 'e': /* for "enclosure" */
			m_SelectMode = HOOC_Enclosure;
			break;

		case 'p':
			m_IntersectPolylinesVisible = !m_IntersectPolylinesVisible;
			break;

		case 's':
			m_SelectMode = HOOC_Shell;
			break;

		case 'w':
			m_SelectMode = HOOC_World;
			break;

		default:
			return HBaseOperator::OnKeyDown(event);
	}
	return (HOP_OK);
}

