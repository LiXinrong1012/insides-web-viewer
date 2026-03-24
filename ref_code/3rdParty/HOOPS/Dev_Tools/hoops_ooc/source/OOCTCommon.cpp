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
 * $Id: OOCTCommon.cpp,v 1.2 2010-10-13 19:25:37 jason Exp $
 */

#define _CRT_SECURE_NO_WARNINGS

#include "hc.h"
#include "hstream.h"

#include "OOCTCommon.h"

#include "vlist.h"

#define HIGH_CUTOFF (0.60f)
#define LOW_CUTOFF (0.40f)

#define BSPX 0x1
#define BSPY 0x2
#define BSPZ 0x4
#define BSP_GARBAGE 0x8 /* unused but reserved */




static void GenerateCuboidPoints(   
	HPoint	*max,
    HPoint	*min,
	HPoint	*points){

    points[0].x = min->x;
    points[0].y = min->y;
    points[0].z = min->z;

    points[1].x = max->x;
    points[1].y = min->y;
    points[1].z = min->z;

    points[2].x = max->x;
    points[2].y = max->y;
    points[2].z = min->z;

    points[3].x = min->x;
    points[3].y = max->y;
    points[3].z = min->z;

    points[4].x = min->x;
    points[4].y = min->y;
    points[4].z = max->z;
    
    points[5].x = max->x;
    points[5].y = min->y;
    points[5].z = max->z;

    points[6].x = max->x;
    points[6].y = max->y;
    points[6].z = max->z;

    points[7].x = min->x;
    points[7].y = max->y;
    points[7].z = max->z;
}



static HC_KEY InsertBox (
    HPoint	*max,
    HPoint	*min){
    HPoint 	points[8];
    int		face_list[30];

	if (!min || !max)
	{
		HPoint p1(-1,-1,-1), p2(1,1,1);
		GenerateCuboidPoints(&p1, &p2, points);
	}
	else
		GenerateCuboidPoints(max, min, points);

    face_list[0] = 4;
    face_list[1] = 0;
    face_list[2] = 1;
    face_list[3] = 2;
    face_list[4] = 3;
    
    face_list[5] = 4;
    face_list[6] = 7;
    face_list[7] = 6;
    face_list[8] = 5;
    face_list[9] = 4;
    
    face_list[10] = 4;
    face_list[11] = 1;
    face_list[12] = 5;
    face_list[13] = 6;
    face_list[14] = 2;
    
    face_list[15] = 4;
    face_list[16] = 4;
    face_list[17] = 0;
    face_list[18] = 3;
    face_list[19] = 7;
    
    face_list[20] = 4;
    face_list[21] = 3;
    face_list[22] = 2;
    face_list[23] = 6;
    face_list[24] = 7;
    
    face_list[25] = 4;
    face_list[26] = 4;
    face_list[27] = 5;
    face_list[28] = 1;
    face_list[29] = 0;

    return HC_KInsert_Shell (8, points, 30, face_list);
}

static int FindContents(HC_KEY &key)
{
    char type[COMMON_BUFFER_SIZE];
    return (HC_Find_Contents(type, &key));

}

static int compare( const void *arg1, const void *arg2 )
{
	OOCT_Instance **o1 = (OOCT_Instance **)arg1;
	OOCT_Instance **o2 = (OOCT_Instance **)arg2;
	if ((*o1)->m_last_id < (*o2)->m_last_id)
		return -1;
	else if ((*o1)->m_last_id > (*o2)->m_last_id)
		return 1;
	else
		return 0;
}
static double ComputeDiameter(HPoint *min, HPoint *max)
{
	HPoint totaldelta = *max - *min;
 	return HC_Compute_Vector_Length(&totaldelta);
}

static bool CalculateBounding(HC_KEY key, HPoint *min, HPoint *max)
{
	
 	char bounding_info[COMMON_BUFFER_SIZE];

	HC_Show_Bounding_Info_By_Key(key, bounding_info);
	
	//figure out whether we have bounding info at all
	if(bounding_info[0]!='\0')
	{
		//get the bounding type and relevant points
		if(strstr(bounding_info, "sphere"))
		{
			float radius;
			HPoint center;

			HC_Show_Bounding_Sphere_By_Key(key, &center, &radius);

			min->x=center.x-radius;
			min->y=center.y-radius;
			min->z=center.z-radius;

			max->x=center.x+radius;
			max->y=center.y+radius;
			max->z=center.z+radius;
		}
		else if(strstr(bounding_info, "cuboid"))
			HC_Show_Bounding_Cuboid_By_Key(key, min, max);

		float matrix[16];
		HC_Open_Segment_By_Key(key);
		if (HC_Show_Existence("modelling matrix"))
		{
			HC_Show_Modelling_Matrix(matrix);
			HC_Compute_Transformed_Points(1,min,matrix,min);
			HC_Compute_Transformed_Points(1,max,matrix,max);
			float t;
			if (max->x < min->x)
			{
				t = min->x;
				min->x = max->x;
				max->x = t;
			}
			if (max->y < min->y)
			{
				t = min->y;
				min->y = max->y;
				max->y = t;
			}
			if (max->z < min->z)
			{
				t = min->z;
				min->z = max->z;
				max->z = t;
			}				
		}
		HC_Close_Segment();

	}
	else
		return false;
	return true;
}

bool CalculateShellBounding(HC_KEY shellkey, HPoint &min, HPoint &max)
{								

	int plen, flen;
 	HC_Show_Shell_Size(shellkey, &plen, &flen);
	if (plen == 0)
		return false;
	HPoint *points = new HPoint[plen];
	HC_Show_Shell(shellkey, &plen, points,&flen,0);

	min = points[0];
	max = points[0];
	for (int i=0;i<plen;i++)
	{
		if (points[i].x < min.x)
			min.x = points[i].x;
		if (points[i].y < min.y)
			min.y = points[i].y;
		if (points[i].z < min.z)
			min.z = points[i].z;
		if (points[i].x > max.x)
			max.x = points[i].x;
		if (points[i].y > max.y)
			max.y = points[i].y;
		if (points[i].z > max.z)
			max.z = points[i].z;
	}
	delete [] points;
	return true;
}



static void FindFileNameWithoutDirectory ( wchar_t const * file_name_in, wchar_t alter * directory_path, wchar_t alter * file_name_with_extension ) {
	if (directory_path == 0 && file_name_with_extension == 0)
		return;

	wchar_t const *file_name = wcsrchr(file_name_in, L'/');

	if (file_name) {
		if (directory_path != 0) {
			wcscpy(directory_path, file_name_in);
			directory_path[file_name - file_name_in] = L'\0';
		}
		if (file_name_with_extension != 0) {
			file_name++;
			wcscpy(file_name_with_extension, file_name);
		}
	}
	else {
		if (directory_path != 0) {
			directory_path[0] = L'\0';
		}
		if (file_name_with_extension != 0) {
			wcscpy(file_name_with_extension, file_name_in);
		}
	}
}




TK_Status TK_OOCT_Shell::Execute(BStreamFileToolkit & tk) 
{
	HPoint minmax[2];
 	TK_Status status = HTK_Shell::Execute(tk);
	if (m_lodlevel == 0)
	{
		if (!(mp_subop2 & TKSH2_NULL))
		{
			if (!CalculateShellBounding(mp_key,minmax[0],minmax[1]))
			{				
				HC_Delete_By_Key(mp_key);
			}
			else
			{
				m_ooct_world->AssociateKey(HC_KShow_Owner_By_Key(mp_key));
				HC_Open_Segment_By_Key(HC_KShow_Owner_By_Key(mp_key));
				CalculateShellBounding(mp_key,minmax[0],minmax[1]);
				InsertBox(&minmax[1], &minmax[0]);
				HC_Delete_By_Key(mp_key);
	// 		HPoint min,max;
	 //		HC_Insert_Shell(2,minmax,0,0);
				HC_Close_Segment();
			}
 		}

	}
	return TK_Normal;
}

TK_Status TK_OOCT_Shell2::Execute(BStreamFileToolkit & tk) 
{
  	TK_Status status = HTK_Shell::Execute(tk);
	HPoint minmax[2];

	if (m_lodlevel == 0)
	{
		if (!(mp_subop2 & TKSH2_NULL))
		{
			if (CalculateShellBounding(mp_key,minmax[0],minmax[1]))
			{				
				m_ooct_world->AssociateKey(HC_KShow_Owner_By_Key(mp_key));
			}
 		}

	}
	return TK_Normal;
}

void OOCT_World::AssociateKey(HC_KEY key)
{	
	IdKeyPair *pair;
	

	int res = vhash_lookup_item(m_KeyToIdKeyPairHash, (void *)key , (void **)&pair);
	if  (res == VHASH_STATUS_SUCCESS)
	{
		pair->m_last_id = m_id;
	}
	else
	{
		pair = new IdKeyPair();
		pair->m_id = m_id;
		pair->m_last_id = m_id;
		pair->m_key = key;
		vhash_insert_item(m_KeyToIdKeyPairHash, (void *)key  , (void *)pair);
		vhash_insert_item(m_IdToIdKeyPairHash, (void *)m_id , (void *)pair);
	}
	m_id++;
}


void OOCT_World::Initialize(const wchar_t *ooct_file_in)
{
	if (m_ooct_file_name)
		delete [] m_ooct_file_name;
	if (m_ooct_file_dir)
		delete [] m_ooct_file_dir;
 	if (m_node_dir_prefix)
		delete [] m_node_dir_prefix;

	size_t ooct_file_in_size = wcslen(ooct_file_in);
	m_ooct_file_dir = new wchar_t [ooct_file_in_size + 1];  
 	m_node_dir_prefix = new wchar_t [ooct_file_in_size + 1];

	m_ooct_file_name = new wchar_t [ooct_file_in_size + 1];
	wcscpy(m_ooct_file_name, ooct_file_in);

	wchar_t *c = m_ooct_file_name;
	while (*c != 0) {
		*c = (*c == L'\\' ? L'/' : *c);
		c++;
	}
 	
	FindFileNameWithoutDirectory(m_ooct_file_name, m_ooct_file_dir, m_node_dir_prefix);

	if ((m_ooct_file_dir_len = wcslen(m_ooct_file_dir)) == 0) {
		swprintf(m_ooct_file_dir, 2, L".");
		m_ooct_file_dir_len = wcslen(m_ooct_file_dir);
	}
	c = m_node_dir_prefix;
	while (*c != 0) {
		*c = (*c == L'.' ? L'_' : *c);
		c++;
	}
	m_node_dir_prefix_len = wcslen(m_node_dir_prefix);

}

IdKeyPair * OOCT_World::GetIdKeyPair(HC_KEY key)
{
	IdKeyPair *pair;

	int res = vhash_lookup_item(m_KeyToIdKeyPairHash, (void *)key , (void **)&pair);
	if  (res == VHASH_STATUS_SUCCESS)
	 return pair;
	else
		return 0;
}

IdKeyPair * OOCT_World::GetIdKeyPairFromId(long id)
{
	IdKeyPair *pair;

	int res = vhash_lookup_item(m_IdToIdKeyPairHash, (void *)id , (void **)&pair);
	if  (res == VHASH_STATUS_SUCCESS)
	 return pair;
	else
		return 0;
}

OOCT_Instance * OOCT_World::GetInstance(long id)
{
	OOCT_Instance *instance;

	int res = vhash_lookup_item(m_IdToInstanceHash, (void *)id , (void **)&instance);
	if  (res == VHASH_STATUS_SUCCESS)
	 return instance;
	else
		return 0;
}


void OOCT_World::QuickFindLastRecursive(HC_KEY key, long &last)
{
	HC_KEY segmentkey;
	HC_Open_Segment_By_Key(key);
	HC_Begin_Contents_Search("...", "segments");
	while (FindContents(segmentkey))
	{
  			IdKeyPair *IdKeyPair = GetIdKeyPair(segmentkey);
			if (IdKeyPair && IdKeyPair->m_last_id > last)
				last = IdKeyPair->m_last_id;
	}
	HC_End_Contents_Search();
	HC_Close_Segment();
}

void OOCT_World::CreateAtomicEntity(IdKeyPair *IdKeyPair, float *matrix, char *color)
{
 	
		OOCT_Instance *instance = GetInstance(IdKeyPair->m_id);		
		HC_Open_Segment("/ooct/ooct_entities");
		HC_KEY key = HC_KOpen_Segment("");
 		if (matrix)
			HC_Set_Modelling_Matrix(matrix);
		if (color)
			HC_Set_Color(color);
		HC_Include_Segment_By_Key(instance->m_key);
		HC_Close_Segment();
		HC_Close_Segment();
		OOCT_Entity *oi = new OOCT_Entity();
		oi->m_key = key;
		oi->m_Instance = instance;
		vlist_add_last(m_AtomicEntityList, oi);
		vhash_insert_item(m_KeyToAtomicEntityHash, (void *)key, (void *)oi);
 		HPoint min,max;
 		CalculateBounding(key, &min, &max);
		oi->m_center.Set((min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f, (min.z + max.z) / 2.0f);
		oi->m_diameter =(float)ComputeDiameter(&min,&max);

}




void OOCT_World::CreateAtomicInstance(IdKeyPair *IdKeyPair, HPoint *min, HPoint *max)
{
	 				 
	OOCT_Instance *oi = new OOCT_Instance();	 
	oi->m_id = IdKeyPair->m_id;
	oi->m_last_id = IdKeyPair->m_last_id;
	QuickFindLastRecursive(IdKeyPair->m_key, oi->m_last_id);
	oi->m_key = IdKeyPair->m_key;
	oi->m_min = *min;
	oi->m_max = *max;

	vlist_add_last(m_AtomicInstancesList, oi);
	m_InstanceCount++;
	IdKeyPair->m_bIsInstance = true;
	vhash_insert_item(m_IdToInstanceHash, (void *)IdKeyPair->m_id, (void *)oi);	
}


void OOCT_World::IdentifySegmentsRecursive(HC_KEY key,int level, bool firstinstance)
{
	int icount;
	char segname[4096];
	char vis[4096];
	
	m_path[level] = key;
	level++;

	IdKeyPair *IdKeyPair = GetIdKeyPair(key);
	if (IdKeyPair && !IdKeyPair->m_bIsInstance)
	{
		HC_Open_Segment_By_Key(key);
		HC_Show_Segment(key, segname);
		HC_Begin_Contents_Search("...", "includes");
		HC_Show_Contents_Count(&icount);
		HC_End_Contents_Search();
	 		
 		if (HC_Show_Existence("visibility"))
		{
			HC_Show_Visibility(vis);
			if (strcmp(vis,"off") == 0)
			{
				HC_Close_Segment();
				return;
			}
		}
 		HC_Close_Segment();


		if (!icount)
		{	

			int scount = 0;
			int segcount;
			HC_Open_Segment_By_Key(key);
 			HC_Begin_Contents_Search("...", "shells");
			HC_Show_Contents_Count(&scount);
			HC_End_Contents_Search();			
			HC_Begin_Contents_Search(".", "segments");
			HC_Show_Contents_Count(&segcount);
			HC_End_Contents_Search();
			HC_Close_Segment();

			if (scount)
			{		
				HPoint min,max;
				if (CalculateBounding(key,&min,&max))
				{
					if (!segcount || ( ComputeDiameter(&min,&max)<m_MaxDiameter/500.0f && 0))			
						CreateAtomicInstance(IdKeyPair,&min, &max);				
				}
			}
			else
				return;
		}
	}
	if (IdKeyPair && IdKeyPair->m_bIsInstance)
	{
		float matrix[16];
		char color[4096];
		bool hasColor = false;
		bool hasMatrix = false;
		HC_KEY path2[256];
		char type[4096];
		for (int j=0;j<level-1;j++)
		{
			HC_Show_Key_Type(m_path[j], type);
			if (strcmp(type, "segment") == 0)
			{
				HC_Open_Segment_By_Key(m_path[j]);
				if (HC_Show_Existence("color"))
					hasColor = false;
				if (HC_Show_Existence("modelling matrix"))
					hasMatrix = true;
				HC_Close_Segment();
			}
			path2[level-j-2] =  m_path[j];
		}
		if (hasMatrix)
			HC_PShow_Net_Modelling_Matrix(level-1, path2, matrix);
		if (hasColor)
			HC_PShow_Net_Color(level-1,path2,color);		
		CreateAtomicEntity(IdKeyPair, hasMatrix ? matrix : 0, hasColor ? color : 0);
		return;
	}
	

	char type[4096];
	HC_KEY childkey;
	HC_Open_Segment_By_Key(key);
	HC_Begin_Contents_Search(".", "segments, includes");
	while (FindContents(childkey))
	{
		HC_Show_Key_Type(childkey, type);
		if (strcmp(type, "segment") == 0)
		{
			HC_Show_Segment(childkey, segname);
			IdentifySegmentsRecursive(childkey, level, firstinstance);
		}
		else
		{				 
			HC_KEY includekey = HC_KShow_Include_Segment(childkey);
			IdentifySegmentsRecursive(includekey, level, false);
		}
	}
	HC_End_Contents_Search();
	HC_Close_Segment();
	
}



void OOCT_World::UpdateLastCountRecursive(HC_KEY key)
{
  	IdKeyPair *pair = GetIdKeyPair(key);
 	if (pair && pair->m_bIsInstance)
	{
		HC_KEY segkey;
		HC_Open_Segment_By_Key(key);
		HC_Begin_Contents_Search("...", "segments");
		while (FindContents(segkey))
		{
			IdKeyPair *pair2 = GetIdKeyPair(segkey);


			if (pair2->m_last_id > pair->m_last_id)
				pair->m_last_id = pair2->m_last_id;
		}
		HC_End_Contents_Search();
		HC_Close_Segment();
		return;
	}
			
	HC_KEY childkey;
	char type[256];
	HC_Open_Segment_By_Key(key);

	HC_Begin_Contents_Search(".", "segments, includes");
	while (FindContents(childkey))
	{
		HC_Show_Key_Type(childkey, type);
		if (strcmp(type, "segment") == 0)
		{
			UpdateLastCountRecursive(childkey);
		}
		else
		{
			HC_KEY includekey = HC_KShow_Include_Segment(childkey);
			UpdateLastCountRecursive(includekey);
		}
	}
	HC_End_Contents_Search();
	HC_Close_Segment();
}

#define BUFFER_SIZE 10000000

void OOCT_World::SerializeInstances()
{	
	for (int i=m_CurrentSerializationPosition;i<m_InstanceCount;i++)
	{
		if (m_InstanceArray[i]->m_last_id<m_id)
		{
			IdKeyPair *pair = GetIdKeyPairFromId(m_InstanceArray[i]->m_id);
			char *buffer = new char[BUFFER_SIZE];
			int written;

			char text[4096];
			HC_Show_Segment(pair->m_key, text);
			HC_Open_Segment_By_Key(pair->m_key);
			m_stream_toolkit_readwrite->Restart();
			m_stream_toolkit_readwrite->SetWriteFlags(TK_Full_Resolution | TK_Disable_Global_Compression);
			TK_Status status = m_stream_toolkit_readwrite->GenerateBuffer(buffer,BUFFER_SIZE,written, 0);
			HC_Close_Segment();
			long fwritten = written;
			fwrite(&fwritten,sizeof(long),1,m_InstanceFileHandle);
			fwritten = (int)fwrite(buffer, 1, written, m_InstanceFileHandle);
  			HC_Show_Segment(pair->m_key, text);

			HC_Open_Segment_By_Key(pair->m_key);
			HC_Flush_Contents("...", "geometry");
			HC_Close_Segment();

			m_InstanceArray[i]->m_FileLocation = m_CurrentFileLocation;
 			m_CurrentFileLocation+=fwritten;
			m_CurrentFileLocation+=sizeof(long);
 			delete [] buffer;
			if (status != TK_Complete)
				status = status;
		
			m_CurrentSerializationPosition = i+1;
		}
		else
			break;
	}
}


void OOCT_World::PreProcess()
{

	m_stream_toolkit = new HStreamFileToolkit;
	m_stream_toolkit->SetOpcodeHandler (TKE_Shell,new TK_OOCT_Shell(this));
	m_stream_toolkit->SetOpcodeHandler (TKE_Line,new TK_OOCT_Line);
	m_stream_toolkit->SetOpcodeHandler (TKE_Polyline,new TK_OOCT_Polypoint(TKE_Polyline));
	m_stream_toolkit->SetOpcodeHandler (TKE_Ellipse,new TK_OOCT_Ellipse(TKE_Ellipse));
	m_stream_toolkit->SetOpcodeHandler (TKE_Elliptical_Arc,new TK_OOCT_Ellipse(TKE_Elliptical_Arc));
	m_stream_toolkit->SetOpcodeHandler (TKE_Text,new TK_OOCT_Text(TKE_Text));
	m_stream_toolkit->SetOpcodeHandler (TKE_Text_With_Encoding,new TK_OOCT_Text(TKE_Text_With_Encoding));
	m_stream_toolkit->SetOpcodeHandler (TKE_Marker,new TK_OOCT_Point(TKE_Marker));
	m_stream_toolkit->SetOpcodeHandler (TKE_Polygon,new TK_OOCT_Polypoint(TKE_Polygon));
	m_stream_toolkit->SetOpcodeHandler  (TKE_Open_Segment,			new TK_OOCT_Open_Segment(this));
	m_stream_toolkit->SetOpcodeHandler  (TKE_Close_Segment,			new TK_OOCT_Close_Segment(this));
 
 	m_id = 0;
 	HC_Open_Segment("/ooct/ooct_model");
	HC_KEY startkey = HC_KOpen_Segment("");
	TK_Status status = HTK_Read_Stream_File (m_ooct_file_name, m_stream_toolkit); 
	HC_Close_Segment();	
	HPoint min,max;

	CalculateBounding(startkey,&min,&max);
 	m_MaxDiameter = ComputeDiameter(&min,&max);

	IdentifySegmentsRecursive(startkey,0, true);
 	UpdateLastCountRecursive(startkey);
		 				
	m_InstanceArray = new OOCT_Instance*[m_InstanceCount];
	int i=0;
	START_LIST_ITERATION(OOCT_Instance,m_AtomicInstancesList);	
		m_InstanceArray[i++] = (OOCT_Instance *)temp;
	END_LIST_ITERATION(m_AtomicInstancesList);

	qsort(m_InstanceArray, m_InstanceCount,sizeof(OOCT_Instance*), compare);

	delete m_stream_toolkit;

	vlist_s *temp_list = new_vlist(malloc,free);
	vhash_to_vlist(m_KeyToIdKeyPairHash, temp_list, malloc);
	START_LIST_ITERATION(vhash_pair_t, temp_list);
	delete (IdKeyPair *)temp->item;
	delete temp;
 	END_LIST_ITERATION(temp_list);

	vhash_flush(m_KeyToIdKeyPairHash);
	vhash_flush(m_IdToIdKeyPairHash);

	HC_Open_Segment("/include library");
	HC_Flush_Contents(".","everything");
	HC_Close_Segment();

	HC_Delete_By_Key(startkey);

	m_stream_toolkit = new HStreamFileToolkit;

	wchar_t  filename[COMMON_BUFFER_SIZE];
	swprintf(filename,COMMON_BUFFER_SIZE,L"%s\\ooct_instances.ooct",m_ooct_file_dir);

 	m_InstanceFileHandle = _wfopen(filename,L"wb");


	m_stream_toolkit->SetOpcodeHandler (TKE_Shell,new TK_OOCT_Shell2(this));
	m_stream_toolkit->SetOpcodeHandler (TKE_Line,new TK_OOCT_Line);
	m_stream_toolkit->SetOpcodeHandler (TKE_Polyline,new TK_OOCT_Polypoint(TKE_Polyline));
	m_stream_toolkit->SetOpcodeHandler (TKE_Ellipse,new TK_OOCT_Ellipse(TKE_Ellipse));
	m_stream_toolkit->SetOpcodeHandler (TKE_Elliptical_Arc,new TK_OOCT_Ellipse(TKE_Elliptical_Arc));
	m_stream_toolkit->SetOpcodeHandler (TKE_Text,new TK_OOCT_Text(TKE_Text));
	m_stream_toolkit->SetOpcodeHandler (TKE_Text_With_Encoding,new TK_OOCT_Text(TKE_Text_With_Encoding));
	m_stream_toolkit->SetOpcodeHandler (TKE_Marker,new TK_OOCT_Point(TKE_Marker));
	m_stream_toolkit->SetOpcodeHandler (TKE_Polygon,new TK_OOCT_Polypoint(TKE_Polygon));
	m_stream_toolkit->SetOpcodeHandler  (TKE_Open_Segment,			new TK_OOCT_Open_Segment2(this));
	m_stream_toolkit->SetOpcodeHandler  (TKE_Close_Segment,			new TK_OOCT_Close_Segment2(this));

 	m_id = 0;
	m_CurrentSerializationPosition = 0;
	m_CurrentFileLocation = 0;
 
	startkey = HC_KOpen_Segment("");
	status = HTK_Read_Stream_File (m_ooct_file_name, m_stream_toolkit); 
	HC_Close_Segment();
 	fclose(m_InstanceFileHandle);

	vhash_flush(m_KeyToIdKeyPairHash);
	vhash_flush(m_IdToIdKeyPairHash);
 	HC_Delete_By_Key(startkey);
	HC_Open_Segment("/include library");
	HC_Flush_Contents(".","everything");
	HC_Close_Segment();

	m_kdtree = new OOCT_KDTree(32, min,max);

	START_LIST_ITERATION(OOCT_Entity,m_AtomicEntityList);		 
	HPoint emin,emax;
 	CalculateBounding(temp->m_key,&emin, &emax);
	m_kdtree->InsertItem(temp,&emin, &emax, true);	 
	END_LIST_ITERATION(m_AtomicEntityList);

	START_LIST_ITERATION(OOCT_Entity,m_AtomicEntityList);		 
	HPoint emin,emax;
	CalculateBounding(temp->m_key,&emin, &emax);
	m_kdtree->InsertItem(temp,&emin, &emax, false);	 
	END_LIST_ITERATION(m_AtomicEntityList);
	m_kdtree->CleanTree();
 	SerializeKDTree();

	HC_Close_Segment();
}

OOCT_World::OOCT_World () {
	m_ooct_file_name = 0;
	m_ooct_file_dir = 0;
	m_ooct_file_dir_len = 0;
	m_node_dir_prefix = 0;
	m_node_dir_prefix_len = 0;
	m_KeyToIdKeyPairHash = new_vhash(10, malloc, free);
	m_IdToIdKeyPairHash = new_vhash(10, malloc, free);
	m_KeyToAtomicEntityHash = new_vhash(10, malloc, free);
	m_AtomicInstancesList = new_vlist(malloc,free);
	m_AtomicEntityList = new_vlist(malloc,free);
 	m_InstanceCount = 0;
 
	m_IdToInstanceHash = new_vhash(10, malloc, free);
	m_KeyToInstanceHash = new_vhash(10, malloc, free);
  	m_stream_toolkit_readwrite = new HStreamFileToolkit;
}


OOCT_KDTree::OOCT_KDTree(int max_depth, HPoint min, HPoint max)
{
	m_min = min;
	m_max = max;
	m_max_depth = max_depth;
	m_root = new OOCT_KDTreeItem(BSPX); 
}


void OOCT_KDTree::CleanTreeRecursive(OOCT_KDTreeItem *subtree)
{
	for (int i=0;i<3;i++)
	{
		if (subtree->kids[i])
		{
			while (1)
			{
				OOCT_KDTreeItem *kid = subtree->kids[i];
				OOCT_KDTreeItem *kidskid = 0;
				int kidcounter = 0;
				if (!kid->kids[3] && kid->m_ItemList->count == 0)
				{
					for (int j=0;j<3;j++)
					{
						if (kid->kids[j])
						{
							kidcounter++;
							kidskid = kid->kids[j];
							if (kidcounter > 1)
								break;
						}
					
					}
					if (kidcounter==1)
					{
						delete kid;
						subtree->kids[i] = kidskid;
						continue;
					}
				}
				break;
			}
		}
	}
	for (int i=0;i<3;i++)
	{
		if (subtree->kids[i])
			CleanTreeRecursive(subtree->kids[i]);
	}
	if (subtree->kids[3])
			CleanTreeRecursive(subtree->kids[3]);
}
				
void OOCT_KDTree::CleanTreeRecursive2(OOCT_KDTreeItem *subtree, OOCT_KDTreeItem *parent, int num)
{
	 
	
		 
	for (int i=0;i<3;i++)
	{
		if (subtree->kids[i])
			CleanTreeRecursive2(subtree->kids[i],subtree,i);
	}
 

	if (subtree->m_ItemList->count == 0 && subtree!=parent)
	{
		int kidcounter = 0;
		for (int j=0;j<3;j++)
		{
			if (subtree->kids[j])
				kidcounter++;
		}
		if (!kidcounter)
		{
			delete subtree;
			parent->kids[num] = 0;
		}
	}

}

void OOCT_World::SerializeKDTreeRecursive(OOCT_KDTreeItem *subtree, int ItemID)
{
	int numberofkids = 0;
 	
	long filelocation = ftell(m_KDTreeFileHandle);
 
	fwrite(&filelocation,sizeof(long),1,m_KDTreeFileMapHandle);
 	fwrite(&ItemID,sizeof(int),1,m_KDTreeFileMapHandle);
	m_NumberOfKDNodes++;

	fwrite(&ItemID,sizeof(int),1,m_KDTreeFileHandle);

	fwrite(&subtree->m_min,sizeof(HPoint),1,m_KDTreeFileHandle);
	fwrite(&subtree->m_max,sizeof(HPoint),1,m_KDTreeFileHandle);
	unsigned char kidinfo = 0;
	if (subtree->kids[0])
	{
		numberofkids++;
		kidinfo |= 1;
	}
	if (subtree->kids[1])
	{
		numberofkids++;
		kidinfo |= 2;
	}
	if (subtree->kids[2])
	{
		numberofkids++;
		kidinfo |= 4;
	}
	if (subtree->kids[3])
	{
		numberofkids++;
		kidinfo |= 8;
	}
	fwrite(&kidinfo,sizeof(unsigned char),1,m_KDTreeFileHandle);
	int count = subtree->m_ItemList->count;
	fwrite(&count,sizeof(int),1,m_KDTreeFileHandle);

	START_LIST_ITERATION(OOCT_Entity,subtree->m_ItemList);	
		unsigned char aexist = 0;
		float matrix[16];
		float  rgb[3];		
		HC_Open_Segment_By_Key(temp->m_key);
		long pos = temp->m_Instance->m_FileLocation;
		fwrite(&pos,sizeof(long),1,m_KDTreeFileHandle);
		if (HC_Show_Existence("modelling matrix"))
		{
			aexist|=1;
			HC_Show_Modelling_Matrix(matrix);
		}
		if (HC_Show_Existence("color"))
		{
		
			char space[32];
			aexist|=2;		
			HC_Show_One_Color_By_Value("faces=diffuse", space, &rgb[0], &rgb[1], &rgb[2]);		
		}
		HC_Close_Segment();
 		fwrite(&temp->m_center,sizeof(HPoint),1,m_KDTreeFileHandle);
 		fwrite(&aexist,sizeof(unsigned char),1,m_KDTreeFileHandle);
		if (aexist & 1)
			fwrite(matrix,sizeof(float),16,m_KDTreeFileHandle);
		if (aexist & 2)
			fwrite(rgb,sizeof(float),3,m_KDTreeFileHandle);

	END_LIST_ITERATION(subtree->m_ItemList);

	int currentcount = m_ItemIDCount;
	m_ItemIDCount+=numberofkids;

	int ckid = 1;

	for (int i=0;i<4;i++)
	{
		if (subtree->kids[i])
		{
			int temp = currentcount + ckid;
			fwrite(&temp,sizeof(int),1,m_KDTreeFileHandle);
 			ckid++;
		}
	}

	ckid = 1;
	for (int i=0;i<4;i++)
	{
		if (subtree->kids[i])
		{
			SerializeKDTreeRecursive(subtree->kids[i],currentcount+ckid);
			ckid++;
		}
	}
 	
}

 







void OOCT_World::SerializeKDTree()
{
	m_ItemIDCount = 0;
	m_NumberOfKDNodes = 0;

	wchar_t  filename[COMMON_BUFFER_SIZE];
	swprintf(filename,COMMON_BUFFER_SIZE,L"%s\\ooct_kdtree.ooct",m_ooct_file_dir);
 	m_KDTreeFileHandle = _wfopen(filename,L"wb");
 	swprintf(filename,COMMON_BUFFER_SIZE,L"%s\\ooct_kdtreeemap.ooct",m_ooct_file_dir);
 	m_KDTreeFileMapHandle = _wfopen(filename,L"wb");
  	fwrite(&m_NumberOfKDNodes,sizeof(int),1,m_KDTreeFileMapHandle);
	SerializeKDTreeRecursive(m_kdtree->m_root,0);
	fseek(m_KDTreeFileMapHandle,0,0);
 	fwrite(&m_NumberOfKDNodes,sizeof(int),1,m_KDTreeFileMapHandle);
	fclose(m_KDTreeFileHandle);
	fclose(m_KDTreeFileMapHandle);
}

OOCT_KDTreeItem::OOCT_KDTreeItem(int partitiontype)
{
	kids[0] = kids[1] = kids[2] = kids[3] =  0;
	m_ItemList = new_vlist(malloc,free);
	m_PartitionType = partitiontype;
 	m_bMinMaxSet = false;
}

void OOCT_KDTreeItem::AppendItem(void *item)
{
	vlist_add_last(m_ItemList, item);
}


void OOCT_KDTree::CleanTree()
{
	CleanTreeRecursive(m_root);
	CleanTreeRecursive2(m_root, m_root,0);
}



void OOCT_KDTree::InsertItem(void *item, HPoint *itemmin, HPoint *itemmax, bool testrun)
{
	int remaining_dimensions = BSPX | BSPY | BSPZ;	
	InsertItemRecursive(m_root, item, m_min,m_max,itemmin, itemmax,0, remaining_dimensions,0, testrun);
}


int get_next_dimension(int current_dimension, int remaining_dimensions) 
{
	do {
		current_dimension = (current_dimension<<1);
		if (current_dimension > BSPZ)
			current_dimension = BSPX;
	} while (!(current_dimension & remaining_dimensions));
	return current_dimension;
}

void OOCT_KDTree::InsertItemRecursive(OOCT_KDTreeItem *subtree, void *item, HPoint min,HPoint max, HPoint *item_min, HPoint *item_max,int max_depth, int remaining_dimensions, int sparseid, bool testrun)
{

	float cutoffs[2];
 	char next_dimension;


	if (testrun)
	{
		if (!subtree->m_bMinMaxSet)
		{
			subtree->m_bMinMaxSet = true;
			subtree->m_min = *item_min;
			subtree->m_max = *item_max;
		}
		else
		{
			if (item_min->x < subtree->m_min.x)
				subtree->m_min.x = item_min->x;
			if (item_min->y < subtree->m_min.y)
				subtree->m_min.y =item_min->y;
			if (item_min->z < subtree->m_min.z)
				subtree->m_min.z = item_min->z;
			if (item_max->x > subtree->m_max.x)
				subtree->m_max.x = item_max->x;
			if (item_max->y > subtree->m_max.y)
				subtree->m_max.y = item_max->y;
			if (item_max->z > subtree->m_max.z)
				subtree->m_max.z = item_max->z;
		}
	}
#if 0
	HC_Open_Segment("/include library/model_1/sparse");
	HC_Set_Visibility("faces = off, edges = on");
		HUtility::InsertBox(&subtree->m_min, &subtree->m_max);
	HC_Close_Segment();		
#endif
	 
	double diam = ComputeDiameter(&subtree->m_min, &subtree->m_max);
	if (max_depth > m_max_depth || (diam < 5800.0f && !testrun)) {
		if (!testrun)
			subtree->AppendItem(item);
		return;
	}
		


	switch (subtree->m_PartitionType) {
		case BSPX: {
			cutoffs[0] = min.x + LOW_CUTOFF * (max.x - min.x);
			cutoffs[1] = min.x + HIGH_CUTOFF * (max.x - min.x);
			if (item_max->x < cutoffs[1]) {
				/* fits on the left */
				if (subtree->kids[ 0 ] == NULL) {
					next_dimension = get_next_dimension(BSPX, remaining_dimensions);
					subtree->kids[ 0 ] = new OOCT_KDTreeItem(next_dimension); 
				}
				max.x = cutoffs[1];
  				InsertItemRecursive(subtree->kids[0], item, min,max, item_min, item_max,max_depth+1,remaining_dimensions, sparseid, testrun);
 			}
			else if (item_min->x > cutoffs[0]) {
				/* fits on the right */
				if (subtree->kids[ 1 ] == NULL) {
					next_dimension = get_next_dimension(BSPX, remaining_dimensions);
					subtree->kids[ 1 ] = new OOCT_KDTreeItem(next_dimension); 
				}
 				min.x = cutoffs[0];
  				InsertItemRecursive(subtree->kids[1], item, min,max, item_min, item_max,max_depth+1,remaining_dimensions, sparseid, testrun);
 			}
			else {
				//		subtree->AppendItem(item);
#if 1
					remaining_dimensions &= ~BSPX;
					if (!remaining_dimensions) {
						/* item_bounds crosses the entire overlap region, as well as the overlap regions
						 * of all other dimensions.	 it belongs at this level */
						if (!testrun)
							subtree->AppendItem(item);
 					}
					else {
						if (subtree->kids[ 2 ] == NULL) {
							next_dimension = get_next_dimension(BSPX, remaining_dimensions);
							subtree->kids[ 2 ] = new OOCT_KDTreeItem(next_dimension); 
						}
		  				InsertItemRecursive(subtree->kids[2], item, min,max, item_min, item_max, max_depth+1,remaining_dimensions, sparseid, testrun);
 					}
#endif
			}
		} break;

		case BSPY: {
			cutoffs[0] =  min.y + LOW_CUTOFF *  (max.y - min.y);
			cutoffs[1] =  min.y + HIGH_CUTOFF *  (max.y - min.y);
			if (item_max->y < cutoffs[1]) {
				/* fits on the left */
				if (subtree->kids[ 0 ] == NULL) {
					next_dimension = get_next_dimension(BSPY, remaining_dimensions);
					subtree->kids[ 0 ] = new OOCT_KDTreeItem(next_dimension); 
				}
				max.y = cutoffs[1];
  				InsertItemRecursive(subtree->kids[0], item, min,max, item_min, item_max,max_depth+1,remaining_dimensions, sparseid, testrun);
 			}
			else if (item_min->y > cutoffs[0]) {
				/* fits on the right */
				if (subtree->kids[ 1 ] == NULL) {
					next_dimension = get_next_dimension(BSPY, remaining_dimensions);
					subtree->kids[ 1 ] = new OOCT_KDTreeItem(next_dimension); 
				}
 				min.y = cutoffs[0];
  				InsertItemRecursive(subtree->kids[1], item, min,max, item_min, item_max,max_depth+1,remaining_dimensions, sparseid, testrun);
 			}
			else {
		//			subtree->AppendItem(item);

#if 1
					remaining_dimensions &= ~BSPY;
					if (!remaining_dimensions) {
						/* item_bounds crosses the entire overlap region, as well as the overlap regions
						 * of all other dimensions.	 it belongs at this level */
						if (!testrun)
							subtree->AppendItem(item);
 					}
					else {
						if (subtree->kids[ 2 ] == NULL) {
							next_dimension = get_next_dimension(BSPY, remaining_dimensions);
							subtree->kids[ 2 ] = new OOCT_KDTreeItem(next_dimension); 
						}
		  				InsertItemRecursive(subtree->kids[2], item, min,max, item_min, item_max, max_depth+1,remaining_dimensions, sparseid, testrun);
 					}
#endif
			}
		} break;
		case BSPZ: {
			cutoffs[0] =  min.z + LOW_CUTOFF *  (max.z - min.z);
			cutoffs[1] =  min.z + HIGH_CUTOFF *  (max.z - min.z);
			if (item_max->z < cutoffs[1]) {
				/* fits on the left */
				if (subtree->kids[ 0 ] == NULL) {
					next_dimension = get_next_dimension(BSPZ, remaining_dimensions);
					subtree->kids[ 0 ] = new OOCT_KDTreeItem(next_dimension); 
				}
				max.z = cutoffs[1];
  				InsertItemRecursive(subtree->kids[0], item, min,max, item_min, item_max,max_depth+1,remaining_dimensions, sparseid, testrun);
 			}
			else if (item_min->z > cutoffs[0]) {
				/* fits on the right */
				if (subtree->kids[ 1 ] == NULL) {
					next_dimension = get_next_dimension(BSPZ, remaining_dimensions);
					subtree->kids[ 1 ] = new OOCT_KDTreeItem(next_dimension); 
				}
 				min.z = cutoffs[0];
  				InsertItemRecursive(subtree->kids[1], item, min,max, item_min, item_max,max_depth+1,remaining_dimensions, sparseid, testrun);
 			}
			else {
	//					subtree->AppendItem(item);
#if 1
					remaining_dimensions &= ~BSPZ;
					if (!remaining_dimensions) {
						/* item_bounds crosses the entire overlap region, as well as the overlap regions
						 * of all other dimensions.	 it belongs at this level */
						if (!testrun)
							subtree->AppendItem(item);
 					}
					else {
						if (subtree->kids[ 2 ] == NULL) {
							next_dimension = get_next_dimension(BSPZ, remaining_dimensions);
							subtree->kids[ 2 ] = new OOCT_KDTreeItem(next_dimension); 
						}
		  				InsertItemRecursive(subtree->kids[2], item, min,max, item_min, item_max, max_depth+1,remaining_dimensions, sparseid, testrun);
 					}
#endif
			}
		} break;


	}
}

