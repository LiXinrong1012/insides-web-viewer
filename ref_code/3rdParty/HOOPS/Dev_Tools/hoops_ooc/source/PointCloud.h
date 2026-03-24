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
 * $Id: PointCloud.h,v 1.4 2010-05-04 22:42:42 chad Exp $
 */

#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#ifdef _MSC_VER
#define OOC_API __declspec (dllexport)
#else
#define OOC_API
#endif

#ifndef alter
#define alter
#endif // alter

#include <stdlib.h>

// enum for different methods of loading an OOC file
enum LoadType {
	LOAD_TYPE_IMMEDIATE,		// no populate callback -- shells loaded directly into segments
	LOAD_TYPE_SYNCHRONOUS,		// uses populate callback -- once triggered => shell is loaded into segment
	LOAD_TYPE_ASYNCHRONOUS		// uses populate callback -- once triggered => shell is queued for loading (default)
};

enum PointCloudStatus {
	PRE_PROCESS_SUCCESS,				// pre-process completed without problem
	PRE_PROCESS_SETUP_FAILURE,			// problem occurred during pre-process setup (directory creation, conflicting files, etc.)
	PRE_PROCESS_FIRST_PASS_FAILURE,		// problem occurred during initial pass (parsing text file for bounding box, binary file generation)
	PRE_PROCESS_SECOND_PASS_FAILURE,	// problem occurred during second pass (spatially sorting all the points)
	PRE_PROCESS_THIRD_PASS_FAILURE,		// problem occurred during third pass (node generation and randomization, index generation)
	PRE_PROCESS_FAILURE,				// some other problem occurred

	LOAD_SUCCESS,						
	LOAD_FAILURE
};

class PointCloudWorld;

class OOC_API PointCloud {
public:
	PointCloud ( wchar_t const * ooc_file_in = 0 );
	PointCloud ( char const * ooc_file_in );
	~PointCloud ();

	// Sets the OOC file which will either be:
	//   -- generated if doing a pre-process
	//	 -- rendered if doing a load
	void SetOOCFile ( wchar_t const * ooc_file_in );
	void SetOOCFile ( char const * ooc_file_in );

	/********************************************************************************/
	/*					Pre-processing functions/settings							*/	
	/********************************************************************************/

	// Generates OOC and node files
	PointCloudStatus PreProcess ();

	// adds point cloud file to list of files processed for OOC generation
	void AddPointCloudFile ( wchar_t const * point_cloud_file_in );
	void AddPointCloudFile ( char const * point_cloud_file_in );

	// sets maximum shell size of node in point cloud
	void SetMaxShellSize ( int max_shell_size_in ); 
	// gets maximum shell size of node in point cloud
	int GetMaxShellSize ();

	// sets maximum amount of memory (in MB) that pre-processing should use (approx.)
	void SetMaxMemoryUsage ( size_t max_memory_usage_in ); 
	// gets maximum amount of memory (in MB) that pre-processing should use (approx.)
	size_t GetMaxMemoryUsage ();

	// sets percentage of overall points to import
	void SetSubSamplePercentage ( double subsample_in ); 
	// gets percentage of overall points to import
	double GetSubSamplePercentage ();

	// sets bounding box outside of which points will be disregarded
	void SetCullingBoundingBox ( float const culling_bbox_in[6] ); 
	// gets bounding box outside of which points will be disregarded
	void GetCullingBoundingBox ( float alter culling_bbox_out[6] );

	// sets flag indicating whether we should overwrite existing files
	void SetOverwriteExistingFiles ( bool overwrite_in );
	// gets flag indicating whether we should overwrite existing files
	bool GetOverwriteExistingFiles ();

	// sets logging file where data about pre-processing should be written (in addition to stdout)
	void SetLoggingFile ( wchar_t const * log_file_name );
	void SetLoggingFile ( char const * log_file_name );

	/********************************************************************************/
	/*						OOC loading functions/settings							*/
	/********************************************************************************/
	
	// Sets up segment tree for reading in OOC point cloud 
	PointCloudStatus Load ();

	// sets the loading type
	void SetLoadType ( LoadType load_type_in );
	// gets the loading type
	LoadType GetLoadType ();

	// sets pointer to data needed for updates (if any)
	void SetExternalUpdateData ( void * update_data_in );
	// gets pointer to data needed for updates (if any)
	void * GetExternalUpdateData ();

	// returns true if a HOOPS update is needed, false otherwise
	bool IsUpdateNeeded ();

private:
	void Initialize ( wchar_t const * ooc_file_in );

	PointCloudWorld *	m_pcw;
	void *				m_update_data;
};

#endif // POINTCLOUD_H

