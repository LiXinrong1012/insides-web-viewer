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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSUtility.cpp,v 1.21 2008-11-26 21:21:41 guido Exp $
//

// Utility Functions used for the application

#include "stdafx.h"
#include "HSInclude.h"

#include "HTools.h"
#include "HBaseOperator.h"
#include "HBaseView.h"
#include "HSUtility.h"
#include "HUtilityLocaleString.h"
#include "HUtility.h"
#include "HSelectionSet.h"
#include "vlist.h"
#include "vhash.h"
#include "hc.h"

#ifdef PARASOLID
#include "parasolid_kernel.h"
#include "kernel_interface.h"
#include "hp_bridge.h"
#endif // PARASOLID

#include <stdio.h>
#include <math.h>
#include <assert.h>
 
#ifdef ACIS
#ifdef IS_X11
// Required to resolve unresolved symbol in ACIS library libgihusk.sl
// *FIX this is a bug in Acis which should be fixed by release 5.3
#include "Xm/XmP.h"
Widget toplevel=0;
#endif // IS_X11
#endif // ACIS

#ifdef PARASOLID

void TransposePoint(HPoint *point, PK_TRANSF_t trans, bool inverse)
{
	float hm[4][4];
	PK_TRANSF_sf_t tf;
	PK_TRANSF_ask(trans,&tf);

	for (int xx=0;xx<4;xx++)
	{
		for (int yy=0;yy<4;yy++)
		{
			hm[xx][yy]=(float)tf.matrix[yy][xx];
		}
	}
	
	if (inverse)
		HC_Compute_Matrix_Inverse((float *)hm,(float *)hm);

	
 	HC_Compute_Transformed_Points(1,point,(float *)hm,point);
}
void TransposePoint(PK_VECTOR_t *dpoint, PK_TRANSF_t trans, bool inverse)
{	
	HPoint dp;
	dp.x=(float)dpoint->coord[0];
	dp.y=(float)dpoint->coord[1];
	dp.z=(float)dpoint->coord[2];

	TransposePoint(&dp,trans,inverse);
 
	dpoint->coord[0]=(double)dp.x;
	dpoint->coord[1]=(double)dp.y;
	dpoint->coord[2]=(double)dp.z;
}
 
void TransposeInstancedPoint(HPoint *point, bool inverse)
{
	PK_ENTITY_t *entities;
	int numentities;
	HP_Compute_Selected_Entity_List(&entities,&numentities);
	for (int i=0;i<numentities;i++)
	{
		PK_CLASS_t paraClass;
		PK_ERROR_t error = PK_ENTITY_ask_class(entities[i], &paraClass);
		if (paraClass == PK_CLASS_instance)
		{
			
			PK_INSTANCE_sf_t in_sf;
			PK_INSTANCE_ask(entities[i],&in_sf);
 			PK_TRANSF_t transf = in_sf.transf;			
			TransposePoint(point,transf,inverse);
		}
	}
	delete entities;
}

void TransposeInstancedPoint(PK_VECTOR_t *dpoint, bool inverse)
{
	HPoint dp;
	dp.x=(float)dpoint->coord[0];
	dp.y=(float)dpoint->coord[1];
	dp.z=(float)dpoint->coord[2];

	TransposeInstancedPoint(&dp,inverse);
 
	dpoint->coord[0]=(double)dp.x;
	dpoint->coord[1]=(double)dp.y;
	dpoint->coord[2]=(double)dp.z;
}

 
 
int report_ifail(int ifail,int expect)
{
	if ( ifail != expect )
		return 1;
	else
		return 0;
}
// calls the appropriate boolean function based on the target and tools
// and rerenders the resulting bodies
void	parasolid_boolean(PK_boolean_function_t	operation, PK_BODY_t target, 
							  int number_of_tools, PK_BODY_t *tools)
{
	PK_ERROR_code_t		error_code;
	PK_BODY_boolean_o_t options;
	int                 number_of_bodies;
	PK_BODY_t          *bodies;
	PK_PARTITION_t		partition;

	assert(target);
	assert(number_of_tools > 0);

	PK_BODY_boolean_o_m(options);
    options.function = operation;

	// need to ensure that the tools are in the same partition as the target 

	PK_ENTITY_ask_partition(target, &partition);

	for (int i = 0; i < number_of_tools; i++)
		PK_BODY_change_partition(tools[i], partition);

	// perform the boolean operation
	error_code = PK_BODY_boolean(target, number_of_tools, tools, &options, &number_of_bodies, &bodies);

	if ( report_ifail(error_code,0) != 0){
		char	error_message[MVO_BUFFER_SIZE];
		sprintf(error_message, "failed during boolean operation \n  Error Code : %d", error_code);
#ifdef IS_QT

#else
		MessageBox(NULL, H_TEXT(error_message), 0, MB_OK);
#endif
	}

	// render bodies
	HP_Render_Entities(number_of_bodies, bodies);

	if (number_of_bodies > 0)
		PK_MEMORY_free(bodies);
}

HC_KEY CopyByKey(HC_KEY source_key)
{
	HC_KEY copy_key;

	HC_KEY temp_seg = HC_KOpen_Segment("");

		HC_Move_By_Key(source_key, ".");
		HC_Copy_Segment(".", "new_temp_segment");

		HC_Begin_Contents_Search("new_temp_segment", "everything");
			char type[MVO_BUFFER_SIZE];
			HC_Find_Contents(type, &copy_key);
		HC_End_Contents_Search();



	HC_Close_Segment();

	HC_Move_By_Key(copy_key, ".");
	HC_Move_By_Key(source_key, ".");

	HC_Delete_By_Key(temp_seg);

	return copy_key;
}

//======================================================================
//	Author :Rajesh B			Created : 3/11/2002 2:47:54 PM
//======================================================================
//	Function :		Parasolid2HoopsNurbsSurface
//	Description :	Converts given Parasolid BSurf to HOOPS NURBS
//	Return :		HC_KEY	-	key of HOOPS NURBS Surf
//	Parameters :
//			PK_BSURF_t bsurf	-	input Parasolid surface
//	Note : DO NOT DELETE THIS FUNCTION - IT IS USED FOR QA PURPOSES
//======================================================================
HC_KEY Parasolid2HoopsNurbsSurface( PK_BSURF_t bsurf )
{
	HC_KEY bsurf_key;

	// get the details
	PK_BSURF_sf_t bsurf_sf;
	PK_ERROR_t err = PK_BSURF_ask( bsurf,  &bsurf_sf );

	float* u_knots = new float[bsurf_sf.n_u_vertices + bsurf_sf.u_degree + 1];
	int ku = 0; 
	for( int iuk = 0; iuk < bsurf_sf.n_u_knots; iuk++ )
	{
		for( int ium = 0; ium < bsurf_sf.u_knot_mult[iuk]; ium++ )
			u_knots[ku++] = (float)bsurf_sf.u_knot[iuk];
	}

	float* v_knots = new float[bsurf_sf.n_v_vertices + bsurf_sf.v_degree + 1];
	int kv = 0; 
	for( int ivk = 0; ivk < bsurf_sf.n_v_knots; ivk++ )
	{
		for( int ivm = 0; ivm < bsurf_sf.v_knot_mult[ivk]; ivm++ )
			v_knots[kv++] = (float)bsurf_sf.v_knot[ivk];
	}

	// check if rational
	if( bsurf_sf.is_rational == PK_LOGICAL_true )
	{
		float* ctrl_vtxs = new float[bsurf_sf.n_u_vertices * bsurf_sf.n_v_vertices*3];
		float* wts = new float[bsurf_sf.n_u_vertices * bsurf_sf.n_v_vertices];
		// we need to extract the weights from vertex array
		for( int iv = 0; iv < (bsurf_sf.n_u_vertices)*(bsurf_sf.n_v_vertices); iv++ )
			wts[iv]				= (float)bsurf_sf.vertex[iv*4 + 3];

		// extract the control pts. Parasolid and HOOPS are cross here
		// Parasolid stores in  UxV array and HOOPS likes VxU format
		for( int iu = 0; iu < (bsurf_sf.n_u_vertices); iu++ )
		{
			for( int iv = 0; iv < (bsurf_sf.n_v_vertices); iv++ )
			{
				// we must divide the control points by wts - diff in Parasolid and HOOPS rep. for rational control points
				ctrl_vtxs[(iu*bsurf_sf.n_v_vertices*3) + (iv*3) + 0] = (float)(bsurf_sf.vertex[(iu*bsurf_sf.n_v_vertices*4) + (iv*4) + 0]/bsurf_sf.vertex[(iu*bsurf_sf.n_v_vertices*4) + (iv*4) + 3]);
				ctrl_vtxs[(iu*bsurf_sf.n_v_vertices*3) + (iv*3) + 1] = (float)(bsurf_sf.vertex[(iu*bsurf_sf.n_v_vertices*4) + (iv*4) + 1]/bsurf_sf.vertex[(iu*bsurf_sf.n_v_vertices*4) + (iv*4) + 3]);
				ctrl_vtxs[(iu*bsurf_sf.n_v_vertices*3) + (iv*3) + 2] = (float)(bsurf_sf.vertex[(iu*bsurf_sf.n_v_vertices*4) + (iv*4) + 2]/bsurf_sf.vertex[(iu*bsurf_sf.n_v_vertices*4) + (iv*4) + 3]);
			}
		}

		// insert a NURBS surface
		bsurf_key = HC_KInsert_NURBS_Surface(	bsurf_sf.u_degree, bsurf_sf.v_degree, 
												bsurf_sf.n_u_vertices, bsurf_sf.n_v_vertices,
												ctrl_vtxs, wts, u_knots, v_knots);
		delete[] wts;
		delete[] ctrl_vtxs;
	}
	else
	{

		// extract the control pts. Parasolid and HOOPS are cross here
		// Parasolid stores in  UxV array and HOOPS likes VxU format
		float* ctrl_vtxs = new float[bsurf_sf.n_u_vertices*bsurf_sf.n_v_vertices*3];
		for( int iu = 0; iu < (bsurf_sf.n_u_vertices); iu++ )
		{
			for( int iv = 0; iv < (bsurf_sf.n_v_vertices); iv++ )
			{
				ctrl_vtxs[(iu*bsurf_sf.n_v_vertices*3) + (iv*3) + 0] = (float)bsurf_sf.vertex[(iu*bsurf_sf.n_v_vertices*3) + (iv*3) + 0];
				ctrl_vtxs[(iu*bsurf_sf.n_v_vertices*3) + (iv*3) + 1] = (float)bsurf_sf.vertex[(iu*bsurf_sf.n_v_vertices*3) + (iv*3) + 1];
				ctrl_vtxs[(iu*bsurf_sf.n_v_vertices*3) + (iv*3) + 2] = (float)bsurf_sf.vertex[(iu*bsurf_sf.n_v_vertices*3) + (iv*3) + 2];
			}
		}

		// insert a NURBS surface
		bsurf_key = HC_KInsert_NURBS_Surface(	bsurf_sf.u_degree, bsurf_sf.v_degree, 
												bsurf_sf.n_u_vertices, bsurf_sf.n_v_vertices,
												ctrl_vtxs, 0, u_knots, v_knots);
		delete[] ctrl_vtxs;
	}

	delete[] u_knots;
	delete[] v_knots;

	// free Parasolid memory
	PK_BSURF_sf_free(bsurf_sf);

	return bsurf_key;
}


//======================================================================
//	Author :Rajesh B			Created : 3/11/2002 2:50:54 PM
//======================================================================
//	Function :		InsertTrimData
//	Description :	Given the HOOPS NURBS Surf key and Parasolid trim data
//					inserts appropriate trimming curves in HOOPS
//	Return :void	-	
//	Parameters :
//			HC_KEY bsurf_key	-	HOOPS NURBS surface key
//			PK_SURF_trim_data_t trim_data	-	parasolid trimming data
//			bool use_polyline	-	true indicates use polylines as trimming curves
//									false indicates use NURBS curves as trimming curves
//	Note : DO NOT DELETE THIS FUNCTION - IT IS USED FOR QA PURPOSES
//======================================================================
void InsertTrimData( HC_KEY bsurf_key, PK_SURF_t pk_surf, PK_SURF_trim_data_t trim_data, bool use_polyline)
{
	PK_ERROR_t err;

	// HOOPS has all it's intervals between 0 & 1 and Parasolid allows any values
	// we need to normalize the control points. Stored the max in u and v first
	PK_BSURF_sf_t bsurf_sf;
	err = PK_BSURF_ask( pk_surf,  &bsurf_sf );

	double u_start_param = -1.0;
	double u_end_param = -1.0;
	int ku = 0; 
	for( int iuk = 0; iuk < bsurf_sf.n_u_knots; iuk++ )
	{
		for( int ium = 0; ium < bsurf_sf.u_knot_mult[iuk]; ium++ )
		{
			if( ku == bsurf_sf.u_degree )
				u_start_param = bsurf_sf.u_knot[iuk];
			if( ku == bsurf_sf.n_u_vertices )
				u_end_param = bsurf_sf.u_knot[iuk];
			ku++;
		}
	}

	double v_start_param = -1.0;
	double v_end_param = -1.0;
	int kv = 0; 
	for( int ivk = 0; ivk < bsurf_sf.n_v_knots; ivk++ )
	{
		for( int ivm = 0; ivm < bsurf_sf.v_knot_mult[ivk]; ivm++ )
		{
			if( kv == bsurf_sf.v_degree )
				v_start_param = bsurf_sf.v_knot[ivk];
			if( kv == bsurf_sf.n_v_vertices )
				v_end_param = bsurf_sf.v_knot[ivk];
			kv++;
		}
	}


	err = PK_BSURF_sf_free(bsurf_sf);


	HC_KEY cur_bsurf_key = bsurf_key;
	int prev_trim_set = -1;
	bool is_first_trim_loop = false;
	for( int ic = 0; ic < trim_data.n_spcurves; ic++ )
	{
		int cur_trim_set = trim_data.trim_set[ic];
		// Parasolid: Each trim set represents a connected piece of trimmed surface.
		if( cur_trim_set != prev_trim_set )
		{
			if( cur_trim_set > 0 )
			{
				HC_Close_Geometry();

				// we have a new trim set, must create a copy of this surface
				// remove the earlier trims on the copy and apply this trim set
				cur_bsurf_key = CopyByKey(bsurf_key);
				HC_Open_Geometry(cur_bsurf_key);
					int trims = 0;
					HC_Show_Trim_Count(&trims);
					for(int i_trims = 0; i_trims < trims; i_trims++ )
						HC_Delete_Trim(0);
			}
			else
				HC_Open_Geometry(cur_bsurf_key);

			is_first_trim_loop = true;
		}

		// count then number of sp curves in this trim loop
		int n_loop_curves = 1;
		for( int jc = ic; jc < trim_data.n_spcurves-1; jc++ )
		{
			if( trim_data.trim_loop[jc] != trim_data.trim_loop[jc+1] )
				break;
			else
				n_loop_curves++;
		}

		HC_Create_Trim_Collection();
		HC_Open_Trim( 0 );
			int i_loop_curve = 0;
			while(1)
			{
				if( use_polyline )
					ParasolidSPCurve2HoopsTrimPoly(trim_data.spcurves[ic], trim_data.intervals[ic], 
												 u_start_param, u_end_param, v_start_param, v_end_param);
				else
					ParasolidSPCurve2HoopsNurbsCurve(trim_data.spcurves[ic], u_start_param, u_end_param, 
													 v_start_param, v_end_param, true);

				i_loop_curve++;
				if( i_loop_curve >= n_loop_curves )
					break;
				else
					ic++;
			}
		HC_Close_Trim();

		// 'keep' the outer trimset and 'remove' the rest
		if( is_first_trim_loop )
			HC_Set_Trim_Operation( 0, "keep" );
		else
			HC_Set_Trim_Operation( 0, "remove" );

		is_first_trim_loop = false;
		prev_trim_set = cur_trim_set;
	}

	// close the geometry if already open
	if( prev_trim_set > -1 )
		HC_Close_Geometry();
}


void ParasolidSPCurve2HoopsTrimPoly(PK_SPCURVE_t sp_curve, PK_INTERVAL_t pk_intl, 
								  double u_start_param, double u_end_param, 
								  double v_start_param, double v_end_param )
{
	// verify that this is the SPCurve
	PK_CLASS_t curve_class;
	PK_ERROR_t err = PK_ENTITY_ask_class(sp_curve, &curve_class);
	if( curve_class != PK_CLASS_spcurve)
	{
		// this type of curve is not expected as input to this routene
		assert(0);
		return;
	}

	PK_SPCURVE_sf_t spcurve_sf;
	err = PK_SPCURVE_ask( sp_curve,  &spcurve_sf );

	int n_vectors = 0;
	PK_VECTOR_t* vectors;
	double*		 ts;
	err = PK_CURVE_output_vectors(spcurve_sf.curve, pk_intl,
					  PK_LOGICAL_false, 0.0, 0.0, 0.0, 
					  &n_vectors, &vectors, &ts );
	float* uv_pts = new float[n_vectors*2];
	for( int iv = 0; iv < n_vectors; iv++ )
	{
		uv_pts[iv*2 + 0] = (float)( (vectors[iv].coord[0] - u_start_param)/(u_end_param-u_start_param));
		uv_pts[iv*2 + 1] = (float)( (vectors[iv].coord[1] - v_start_param)/(v_end_param-v_start_param));
	}
	HC_Trim_NURBS_Surface_By_Poly( n_vectors, uv_pts );

	if( n_vectors > 1)
		PK_MEMORY_free( vectors );
}

//======================================================================
//	Author :Rajesh B			Created : 3/11/2002 2:45:18 PM
//======================================================================
//	Function :		ParasolidSPCurve2HoopsNurbsCurve
//	Description :	Converts the given parasolid spcurve to HOOPS NURBS curve
//	Return :		HC_KEY	-	key of the nurbs curve inserted
//	Parameters :
//			PK_SPCURVE_t spcurve	-	input parsolid spcurve tag
//			bool trim	-	true indicates this is a trim curve
//	Note : DO NOT DELETE THIS FUNCTION - IT IS USED FOR QA PURPOSES
// DO NOT PASS ANY OTHER TYPES OF CURVES OTHER THAN BCURVE.
//======================================================================
HC_KEY ParasolidSPCurve2HoopsNurbsCurve( PK_SPCURVE_t spcurve, 
										  double u_start_param, double u_end_param, 
										  double v_start_param, double v_end_param,
										  bool trim)
{
	// verify that this is the SPCurve
	PK_CLASS_t curve_class;
	PK_ERROR_t err = PK_ENTITY_ask_class(spcurve, &curve_class);
	if( curve_class != PK_CLASS_spcurve)
	{
		// this type of curve is not expected as input to this routene
		assert(0);
		return -1;
	}

	PK_SPCURVE_sf_t spcurve_sf;
	err = PK_SPCURVE_ask( spcurve,  &spcurve_sf );

	HC_KEY spcurve_key = -1;
	PK_BCURVE_sf_t bcurve_sf;
	err = PK_BCURVE_ask( spcurve_sf.curve, &bcurve_sf);
	err = PK_ENTITY_ask_class(spcurve_sf.curve, &curve_class);
	if( curve_class != PK_CLASS_bcurve)
	{
		// this type of curve is not handled
		assert(0);
		return -1;
	}

	float* knots = new float[bcurve_sf.n_vertices + bcurve_sf.degree + 1];
	double ps_start_intl = -1.0;
	double ps_end_intl = -1.0;
	int ki = 0;
	for( int ik = 0; ik < bcurve_sf.n_knots; ik++ )
	{
		for( int im = 0; im < bcurve_sf.knot_mult[ik]; im++ )
		{
			knots[ki] = (float)bcurve_sf.knot[ik];
			if( ki == bcurve_sf.degree )
				ps_start_intl = bcurve_sf.knot[ik];
			if( ki == bcurve_sf.n_vertices )
				ps_end_intl = bcurve_sf.knot[ik];
			ki++;
		}
	}

	PK_INTERVAL_t curve_intl;
	PK_CURVE_ask_interval(spcurve_sf.curve, &curve_intl);
	float start_intl = (float)((curve_intl.value[0] - ps_start_intl)/(ps_end_intl - ps_start_intl));
	float end_intl = (float)((curve_intl.value[1] - ps_start_intl)/(ps_end_intl - ps_start_intl));

	float* ctrl_vtxs = new float[bcurve_sf.n_vertices*2];
	float* wts = 0;
	if( bcurve_sf.vertex_dim == 3 && bcurve_sf.is_rational == PK_LOGICAL_true )
	{
		wts = new float[bcurve_sf.n_vertices];
		// we need to extract the weights from vertex array
		for( int iv = 0; iv < bcurve_sf.n_vertices; iv++ )
		{
			wts[iv]					= (float)bcurve_sf.vertex[(iv*3) + 2];
			assert( wts[iv] != 0);
			ctrl_vtxs[(iv*2) + 0]	= (float) ( ((bcurve_sf.vertex[(iv*3) + 0]/wts[iv]) - u_start_param)/(u_end_param - u_start_param) );
			ctrl_vtxs[(iv*2) + 1]	= (float) ( ((bcurve_sf.vertex[(iv*3) + 1]/wts[iv]) - v_start_param)/(v_end_param - v_start_param) );
		}
	}	
	else if( bcurve_sf.vertex_dim == 2 && bcurve_sf.is_rational == PK_LOGICAL_false )
	{
		for( int iv = 0; iv < bcurve_sf.n_vertices; iv++ )
		{
			ctrl_vtxs[(iv*2) + 0]	= (float)( (bcurve_sf.vertex[(iv*2) + 0] - u_start_param)/(u_end_param-u_start_param) );
			ctrl_vtxs[(iv*2) + 1]	= (float)( (bcurve_sf.vertex[(iv*2) + 1] - v_start_param)/(v_end_param-v_start_param) );
		}
	}	
	else
	{
		// we are not expecting this type of curve here, it looks like a bcurve
		assert(0);
	}

	if( trim )
		HC_Trim_NURBS_Surface_By_Curve( bcurve_sf.degree, bcurve_sf.n_vertices,
										ctrl_vtxs, wts, knots, start_intl, end_intl );
	else
		HC_Insert_NURBS_Curve( bcurve_sf.degree, bcurve_sf.n_vertices,
										ctrl_vtxs, wts, knots, start_intl, end_intl);

	if( ctrl_vtxs )
		delete[] ctrl_vtxs;
	if( wts )
		delete[] wts;
	if( knots )
		delete[] knots;

	// free Parasolid memory
	if( bcurve_sf.n_vertices > 1 )
		PK_MEMORY_free(bcurve_sf.vertex);
	if( bcurve_sf.n_knots > 1 )
	{
		PK_MEMORY_free(bcurve_sf.knot);
		PK_MEMORY_free(bcurve_sf.knot_mult);
	}

	return spcurve_key;
}

//======================================================================
//	Author :Rajesh B			Created : 3/11/2002 2:45:18 PM
//======================================================================
//	Function :		ParasolidBCurve2HoopsNurbsCurve
//	Description :	Converts the given parasolid bcurve to HOOPS NURBS curve
//	Return :		HC_KEY	-	key of the nurbs curve inserted
//	Parameters :
//			PK_BCURVE_t bcurve	-	input parsolid bcurve tag
//			bool trim	-	true indicates this is a trim curve
//	Note : DO NOT DELETE THIS FUNCTION - IT IS USED FOR QA PURPOSES
// DO NOT PASS ANY OTHER TYPES OF CURVES OTHER THAN BCURVE.
//======================================================================
HC_KEY ParasolidBCurve2HoopsNurbsCurve( PK_BCURVE_t bcurve, bool trim)
{
	// verify that this is the BCurve and not SPCurve
	PK_CLASS_t curve_class;
	PK_ERROR_t err = PK_ENTITY_ask_class(bcurve, &curve_class);
	if( curve_class != PK_CLASS_bcurve)
	{
		// this type of curve is not expected as input to this routene
		assert(0);
		return -1;
	}

	HC_KEY bcurve_key = -1;
	PK_BCURVE_sf_t bcurve_sf;
	err = PK_BCURVE_ask( bcurve, &bcurve_sf);

	float* knots = new float[bcurve_sf.n_vertices + bcurve_sf.degree + 1];
	double ps_start_intl = -1.0;
	double ps_end_intl = -1.0;
	int ki = 0;
	for( int ik = 0; ik < bcurve_sf.n_knots; ik++ )
	{
		for( int im = 0; im < bcurve_sf.knot_mult[ik]; im++ )
		{
			knots[ki] = (float)bcurve_sf.knot[ik];
			if( ki == bcurve_sf.degree )
				ps_start_intl = bcurve_sf.knot[ik];
			if( ki == bcurve_sf.n_vertices )
				ps_end_intl = bcurve_sf.knot[ik];
			ki++;
		}
	}

	PK_INTERVAL_t curve_intl;
	PK_CURVE_ask_interval(bcurve, &curve_intl);
	float start_intl = (float)((curve_intl.value[0] - ps_start_intl)/(ps_end_intl - ps_start_intl));
	float end_intl = (float)((curve_intl.value[1] - ps_start_intl)/(ps_end_intl - ps_start_intl));

	float* ctrl_vtxs = new float[bcurve_sf.n_vertices*3];
	float* wts = 0;
	if( bcurve_sf.is_rational == PK_LOGICAL_true )
	{
		wts = new float[bcurve_sf.n_vertices];
		// we need to extract the weights from vertex array
		for( int iv = 0; iv < bcurve_sf.n_vertices; iv++ )
		{
			wts[iv]					= (float)bcurve_sf.vertex[(iv*4) + 3];
			assert( wts[iv] != 0);
			ctrl_vtxs[(iv*3) + 0]	= (float)bcurve_sf.vertex[(iv*4) + 0]/wts[iv];
			ctrl_vtxs[(iv*3) + 1]	= (float)bcurve_sf.vertex[(iv*4) + 1]/wts[iv];
			ctrl_vtxs[(iv*3) + 2]	= (float)bcurve_sf.vertex[(iv*4) + 2]/wts[iv];
		}
	}
	else
	{
		for( int iv = 0; iv < bcurve_sf.n_vertices; iv++ )
		{
			ctrl_vtxs[(iv*3) + 0]	= (float)bcurve_sf.vertex[(iv*3) + 0];
			ctrl_vtxs[(iv*3) + 1]	= (float)bcurve_sf.vertex[(iv*3) + 1];
			ctrl_vtxs[(iv*3) + 2]	= (float)bcurve_sf.vertex[(iv*3) + 2];
		}
	}

	if( trim )
		HC_Trim_NURBS_Surface_By_Curve( bcurve_sf.degree, bcurve_sf.n_vertices,
										ctrl_vtxs, wts, knots, start_intl, end_intl );
	else
		HC_Insert_NURBS_Curve( bcurve_sf.degree, bcurve_sf.n_vertices,
										ctrl_vtxs, wts, knots, start_intl, end_intl);

	if( ctrl_vtxs )	
		delete[] ctrl_vtxs;
	if( wts )	
		delete[] wts;
	if( knots )
		delete[] knots;

	// free Parasolid memory
	if( bcurve_sf.n_vertices > 1 )
		PK_MEMORY_free(bcurve_sf.vertex);
	if( bcurve_sf.n_knots > 1 )
	{
		PK_MEMORY_free(bcurve_sf.knot);
		PK_MEMORY_free(bcurve_sf.knot_mult);
	}

	return bcurve_key;
}

//======================================================================
//	Author :Rajesh B			Created : 3/29/2002 11:29:11 AM
//======================================================================
//	Function :		PK_BSURF_sf_free
//	Description :	Wish this was implemented in Parasolid to free
//					memory of queries bsurf struct
//	Return :		PK_ERROR_code_t	-	
//	Parameters :
//			PK_BSURF_sf_t bsurf_sf	-	
//	Note :
//======================================================================
PK_ERROR_code_t PK_BSURF_sf_free(PK_BSURF_sf_t bsurf_sf)
{
	if( (bsurf_sf.n_u_vertices + bsurf_sf.n_v_vertices) > 1 )
		PK_MEMORY_free(bsurf_sf.vertex);
	if( bsurf_sf.n_u_knots > 1 )
	{
		PK_MEMORY_free(bsurf_sf.u_knot);
		PK_MEMORY_free(bsurf_sf.u_knot_mult);
	}
	if( bsurf_sf.n_v_knots > 1 )
	{
		PK_MEMORY_free(bsurf_sf.v_knot);
		PK_MEMORY_free(bsurf_sf.v_knot_mult);
	}

	return PK_ERROR_no_errors;
}


#endif // PARASOLID

#ifdef ACIS
//inline void check(outcome& o)
extern void check(outcome& o);
#if 0
{
	int error_number;
	if(!o.ok())
	{
//		__asm int 3;
		char error_string[MVO_BUFFER_SIZE];
		error_number = o.error_number();
		strcpy(error_string, find_err_mess(error_number));
		assert(0);
	}
}
#endif 

// calls the appropriate boolean function based on the target and tools
// and rerenders the resulting bodies
void	acis_boolean(unsigned long operation, BODY* target, 
							  unsigned long number_of_tools, BODY **tools)
{
	outcome o;
	unsigned long i;

	assert(target);
	assert(tools);
	assert(number_of_tools > 0);

	switch(operation)
	{
	case HA_OPERATION_SUBTRACT:
		for (i = 0; i < number_of_tools; i++)
		{
			o = api_subtract(tools[i], target);
			assert(o.ok());
		}
		break;
	case HA_OPERATION_UNITE:
		for (i = 0; i < number_of_tools; i++)
		{
			o = api_unite(tools[i], target);
			assert(o.ok());
		}
		break;
	case HA_OPERATION_INTERSECT:
		for (i = 0; i < number_of_tools; i++)
		{
			o = api_intersect(tools[i], target);
			assert(o.ok());
		}
		break;
	default:
		assert(0);
		break;
	}
	HA_Render_Entity(target);
}

#endif // ACIS




void QualifiedKey::Select(HBaseView *view)
{
	HSelectionSet *sel = view->GetSelection();
	sel->Select(m_Key, m_IncludeListLength, m_IncludeList);
}
MultiSelectItem::MultiSelectItem(HC_KEY key)
{
	m_Key.SetKey(key);
	m_AssociatedKeyList = new_vlist(malloc, free);
	m_AssociatedSelectItemList = new_vlist(malloc, free);
}
MultiSelectItem::~MultiSelectItem()
{
	START_LIST_ITERATION(QualifiedKey, m_AssociatedKeyList);
 			delete temp;
	END_LIST_ITERATION(m_AssociatedKeyList);
	delete_vlist(m_AssociatedKeyList);
	START_LIST_ITERATION(QualifiedKey, m_AssociatedSelectItemList);
 			delete temp;
	END_LIST_ITERATION(m_AssociatedSelectItemList);
	delete_vlist(m_AssociatedSelectItemList);
}


void MultiSelectItem::AddAssociatedKey(HC_KEY key, int length, HC_KEY *include_list)
{
	QualifiedKey *qk = new QualifiedKey(key, length, include_list);
	vlist_add_last(m_AssociatedKeyList, qk);
}
void MultiSelectItem::AddAssociatedSelectItem(HC_KEY key, int length, HC_KEY *include_list)
{
	QualifiedKey *qk = new QualifiedKey(key, length, include_list);
	vlist_add_last(m_AssociatedSelectItemList, qk);
}
void MultiSelectItem::MultiSelect(MultiSelectManager *mm, HBaseView *view)
{
	START_LIST_ITERATION(QualifiedKey, m_AssociatedKeyList);
 			temp->Select(view);
	END_LIST_ITERATION(m_AssociatedKeyList);
	START_LIST_ITERATION(QualifiedKey, m_AssociatedSelectItemList);
			mm->MultiSelect(temp->GetKey(), view);
 	END_LIST_ITERATION(m_AssociatedSelectItemList);
}



MultiSelectManager::MultiSelectManager()
{
	m_SelectItemHash = new_vhash(10,malloc,free);
	m_SelectItemList = new_vlist(malloc,free);
	m_bHasItems = false;
}
MultiSelectManager::~MultiSelectManager()
{
	START_LIST_ITERATION(MultiSelectItem, m_SelectItemList);
 			delete temp;
	END_LIST_ITERATION(m_SelectItemList);
	delete_vlist(m_SelectItemList);
	delete_vhash(m_SelectItemHash);
	
}



MultiSelectItem * MultiSelectManager::CreateMultiSelectItem(HC_KEY key)
{
	MultiSelectItem *item = new MultiSelectItem(key);
	vhash_insert_item(m_SelectItemHash, (void *)key  , (void *)item);	
	vlist_add_last(m_SelectItemList, item);
	m_bHasItems = true;
	return item;
}
MultiSelectItem * MultiSelectManager::GetMultiSelectItem(HC_KEY key)
{

	MultiSelectItem *item;
	int res = vhash_lookup_item(m_SelectItemHash, (void *)key ,  (void **)&item);
	if (!(res == VHASH_STATUS_SUCCESS))
		return 0;
	return item;
}

HC_KEY  MultiSelectManager::MultiSelect(HC_KEY key, HBaseView *view)
{
	int i;
	if (!m_bHasItems)
		return key;
	HC_KEY oldkey = key;
	for (i=0;i<5;i++)
	{		
		MultiSelectItem *item = GetMultiSelectItem(key);
		if (item)
		{
			item->MultiSelect(this, view);
			break;
		}
		key = HC_KShow_Owner_By_Key(key);
	}
	if (i==5)
		return oldkey;
	else
		return key;

}

