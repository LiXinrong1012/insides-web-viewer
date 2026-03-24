


#include "hc.h"
#include "hpserror.h"
#include "hp_map.h"
#include "parafile.h"
#include "parafrustdefs.h"
#include "hp_bridge_internal.h"
#include "bulletin.h"
#include "vlist.h"
#include "vhash.h"
#include "utf_utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h> // for tolower function
#include <locale.h>
#include <wchar.h>

#define streq(a,b)      (!strcmp(a,b))

#define HP_MERGE_FACES 2
#define HP_MERGE_BODIES 4
#define HP_CREATE_BODY_SEGMENTS 8
#define HP_CREATE_COLOR_SEGMENTS 16
#define HP_TESSELLATE_ELLIPSES 32
#define HP_RENDER_EDGES 64
#define HP_RENDER_FACES 128
#define HP_UPDATE_MAPPING 256

#define MAX_ERROR_STRING_LENGTH		1024
#define MAX_SEGMENT_NAME_LENGTH		1024
#define MAX_TYPE_NAME_LENGTH		32

bool g_color_segment_mode = true;
bool g_body_segment_mode = true;
bool g_merge_faces_mode = false;
bool g_render_edges_mode = true;
bool g_tessellate_ellipses_mode = false; // not supported yet
bool g_render_faces_mode = true;
bool g_merge_bodies_mode = false;
bool g_no_mapping_mode = false;
bool g_instances_to_bodies = false;

__wchar_t g_schema_path[MAX_SCHEMA_PATH_LENGTH];
unsigned char g_hash_level=0;

PK_TOPOL_render_facet_o_t g_facetOptions;
PK_TOPOL_render_line_o_t g_lineOptions;

// forward declarations
void HP_InitializeRenderOptions ( void );    
//GH99
extern DLLEXPORT void HP_Render_Entities ( unsigned long count, PK_ENTITY_t *entities,
											   PK_TRANSF_t view_transf = NULTAG, 
											   PK_TRANSF_t *topol_transf = 0 );
extern DLLEXPORT void HP_Render_Entity ( PK_ENTITY_t entity, PK_TRANSF_t trans = NULTAG, 
											 PK_TRANSF_t topol_transf = NULTAG );
extern DLLEXPORT void HP_Delete_Entity_Geometry ( unsigned long count, PK_ENTITY_t *entities, 
													  bool PreserveSegments = false );
#ifdef _MSC_VER

extern DLLEXPORT const __wchar_t * HP_Get_Schema_Path ();
extern DLLEXPORT void HP_Set_Schema_Path ( const __wchar_t *schema_path );

#else

extern DLLEXPORT const wchar_t * HP_Get_Schema_Path ();
extern DLLEXPORT void HP_Set_Schema_Path ( const wchar_t *schema_path );

#endif


//this seems to be missing in header 
extern "C" void FreeParasolidFrustrumMemory ( void );

extern "C" PK_ERROR_code_t FRU__delta_init( int action );
extern "C" PK_ERROR_code_t FRU_delta_open_for_write(PK_PMARK_t, PK_DELTA_t *);
extern "C" PK_ERROR_code_t FRU_delta_open_for_read(PK_DELTA_t);
extern "C" PK_ERROR_code_t FRU_delta_write(PK_DELTA_t, unsigned, const char *);
extern "C" PK_ERROR_code_t FRU_delta_read(PK_DELTA_t, unsigned, char *);
extern "C" PK_ERROR_code_t FRU_delta_delete(PK_DELTA_t);
extern "C" PK_ERROR_code_t FRU_delta_close(PK_DELTA_t);

extern "C" void FSTART( int *);
extern "C" void FABORT( int *);
extern "C" void FSTOP( int *);
extern "C" void FMALLO( int *, char **, int *);
extern "C" void FMFREE( int *, char **, int *);
extern "C" void GOSGMT( const int *, const int *, const int *, const int *,
						const double *, const int *, const int *, int *);
extern "C" void GOOPSG( const int *, const int *, const int *, const int *,
						const double *, const int *, const int *, int *);
extern "C" void GOCLSG( const int *, const int *, const int *, const int *,
						const double *, const int *, const int *, int *);
extern "C" void GOPIXL( const int *, const double *, const int *, const int *,
						int *);
extern "C" void GOOPPX( const int *, const double *, const int *, const int *,
						int *);
extern "C" void GOCLPX( const int *, const double *, const int *, const int *,
						int *);
extern "C" void FFOPRD( const int *, const int *, const char *, const int *,
						const int *, int *, int *);
extern "C" void FFOPWR( const int *, const int *, const char *, const int *,
						const char *, const int *, int *, int *);
extern "C" void FFCLOS( const int *, const int *, const int *, int *);
extern "C" void FFREAD( const int *, const int *, const int *, char *, int *,
						int *);
extern "C" void FFWRIT( const int *, const int *, const int *, const char *,
						int *);
extern "C" void FFOPRB( const int *, const int *, const int *, int *, int *,
						int *);
extern "C" void FFSEEK( const int *, const int *, const int *, int *);
extern "C" void FFTELL( const int *, const int *, int *, int *);
extern "C" void FGCRCU( const char *, int *, int *, int *, int *, double *,
						int *, double *, int *);
extern "C" void FGCRSU( const char *, int *, int *, int *, int *, double *,
						int *, double *, int *);
extern "C" void FGEVCU( int *, double *, double *, double *, int *,
						double *, int *);
extern "C" void FGEVSU( int *, double *, double *, double *, double *,
						int *, int *, int *, double *, int *);
extern "C" void FGPRCU( int *, double *, double *, double *, int *, int *);
extern "C" void FGPRSU( int *, double *, double *, double *, int *, int *);

extern "C" int UCOPRD( const int  guise, const int  format, const PK_UCHAR_t name[],
                       const PK_LOGICAL_t skiphd, int *strid);
extern "C" int UCOPWR( const int guise, const int format, const PK_UCHAR_t * name,
					   const char * pd2hdr, int *strid );

extern long HP_Compute_Geometry_Key_Count_internal ( PK_ENTITY_t tagID, unsigned long geomTypes );
extern long HP_Compute_Geometry_Keys_internal ( PK_ENTITY_t tagID, HC_KEY *keys, unsigned long geomTypes, 
												    long count );

 

HP_Map* g_pMap = 0;// the mapping structure between HOOPS and Parasolid
static HP_BulletinBoard* s_pBB; // bulletin board structure to coordinate events between Parasolid and HOOPS

typedef struct point {
    float	x, y, z;
} Point;
typedef struct point Vector; 

typedef struct _ParaFileList
{
	_ParaFileList* next;
	Parafile* pfile;
} ParaFileList;

static ParaFileList* pfiles = 0;



extern DLLEXPORT void* AllocateDynamic( size_t bytes )
{
	void* data = malloc(sizeof(char) * bytes);
//	TRACE( "Dynamic memory (length %d): %p\n", bytes, data );
//	if (recordingDynamicMemory) dynamicMemoryList.AddHead( data );
	return data;
}

extern DLLEXPORT void FreeDynamic( void* data )
{
//	TRACE( "Dynamic memory freed: %p\n", data );
//	if (recordingDynamicMemory)
//	{
//		// this is the slowest bit of the recording process: tracking down the reference & removing it
//		POSITION pos;
//		if ( pos = dynamicMemoryList.Find( data ) ) dynamicMemoryList.RemoveAt( pos );
//	}
	free (data);
}

extern "C" void FreeParaPartitions( void )
{
	ParaFileList* thisElt = 0;
	ParaFileList* lastElt = 0;
	for (thisElt = pfiles; thisElt; thisElt = thisElt->next)
	{
		if (lastElt)
		{
			delete lastElt->pfile;
			delete lastElt;
		}
		lastElt = thisElt;
	}
	if (lastElt)
	{
		delete lastElt->pfile;
		delete lastElt;
		pfiles = 0;
	}
}

extern DLLEXPORT unsigned long HP_Internal_Get_Rendering_Options(void)
{
	unsigned long result = 0; 

	if (!g_no_mapping_mode)
		result |= HP_UPDATE_MAPPING;

	if (g_color_segment_mode)
		result |= HP_CREATE_COLOR_SEGMENTS;

	if (g_body_segment_mode)
		result |= HP_CREATE_BODY_SEGMENTS;

	if (g_tessellate_ellipses_mode)
		result |= HP_TESSELLATE_ELLIPSES;

	if (g_render_edges_mode)
		result |= HP_RENDER_EDGES;

	if (g_render_faces_mode)
		result |= HP_RENDER_FACES;

	if (g_merge_faces_mode)
		result |= HP_MERGE_FACES;

	if (g_merge_bodies_mode)
		result |= HP_MERGE_BODIES;

	return result;
}

extern DLLEXPORT void HP_Internal_Set_Rendering_Options(unsigned long rendering_options)
{
	if (rendering_options & HP_UPDATE_MAPPING)
		g_no_mapping_mode = false;
	else
		g_no_mapping_mode = true;
	
	if (rendering_options & HP_CREATE_COLOR_SEGMENTS)
		g_color_segment_mode = true;
	else
		g_color_segment_mode = false;

	if (rendering_options & HP_CREATE_BODY_SEGMENTS)
		g_body_segment_mode = true;
	else
		g_body_segment_mode = false;

	if (rendering_options & HP_RENDER_EDGES)
		g_render_edges_mode = true;
	else
		g_render_edges_mode = false;

	if (rendering_options & HP_RENDER_FACES)
		g_render_faces_mode = true;
	else
		g_render_faces_mode = false;

	if (rendering_options & HP_TESSELLATE_ELLIPSES)
		g_tessellate_ellipses_mode = true;
	else
		g_tessellate_ellipses_mode = false;

	if (rendering_options & HP_MERGE_FACES)
		g_merge_faces_mode = true;
	else
		g_merge_faces_mode = false;

	if (rendering_options & HP_MERGE_BODIES)
		g_merge_bodies_mode = true;
	else
		g_merge_bodies_mode = false;
}

bool Parse_YesNo_And_Mutate_Options_Using_Bitmask(char* token, unsigned long bitmask, unsigned long* options)
{
	// warning: this function will often mutate argument "token"
	
	char token2[1025];

	if ( 0 == strncmp( token, "no", 2))
	{
		bitmask = ~bitmask;
		*options &= bitmask;
	}
	else if (strstr(token,"=")&&HC_Parse_String(token,"=",-1,token2))
	{

		if (0==strncmp(token2,"off",3))
		{
			bitmask = ~bitmask;
			*options &= bitmask;
		}
		else if (0==strncmp(token2,"on",2))
		{
			*options |= bitmask;
		}
		else if (0==strncmp(token2,"1",1))
		{
			*options |= bitmask;
		}
		else if (0==strncmp(token2,"0",1))
		{
			bitmask = ~bitmask;
			*options &= bitmask;
		}
		else
		{
			/*error*/
			const char * mes = "bad value:";
			const char * mesv[2]; 

			const char * fun = "HP_Set_Rendering_Options";

			mesv[0]=mes;
			mesv[1]=token2;

			HC_Report_Error( 50, 309, 1, 2, mesv, 1, &fun );
			return false;
		}			
	}
	else{
		/*plain option*/
		*options |= bitmask;
	}
	return true;
}

extern DLLEXPORT void HP_Set_Rendering_Options(const char * list)
{
	char token[1025];
	char llist[1025];
	unsigned long options = 0;
	unsigned long bitmask = 0;
	unsigned long i;
	unsigned long token_number = 0;

	options = HP_Internal_Get_Rendering_Options();


		
	/*my canonize chars*/
	for(i=0; i<1024; i++){

		if(!list[i]) break;	
		llist[i] = (char) tolower((int)list[i]);
	}
	llist[i] = 0;


	/*loop through options*/
	while(HC_Parse_String(llist,",",(int)token_number++,token))
	{
		if (strstr(token,"preserve color"))
			bitmask = HP_CREATE_COLOR_SEGMENTS;
		else if (strstr(token,"create body segments"))
			bitmask = HP_CREATE_BODY_SEGMENTS;
		else if (strstr(token,"merge faces"))
			bitmask = HP_MERGE_FACES;
		else if (strstr(token,"merge bodies"))
			bitmask = HP_MERGE_BODIES;
		else if (strstr(token,"edges"))
			bitmask = HP_RENDER_EDGES;
		else if (strstr(token,"faces"))
			bitmask = HP_RENDER_FACES;
		else if (strstr(token,"tessellate ellipses"))
			bitmask = HP_TESSELLATE_ELLIPSES;
		else if (strstr(token,"update mapping"))
			bitmask = HP_UPDATE_MAPPING;
		else
		{
			/*error*/
			const char * mes = "Null option or unknown option";
			
			const char * fun = "HP_Set_Rendering_Options";

			HC_Report_Error( 50, 309, 1, 1, &mes, 1, &fun);
			return;
		}

		if (!Parse_YesNo_And_Mutate_Options_Using_Bitmask(token, bitmask, &options))
			return; // parse error, don't set the options.
	}
	HP_Internal_Set_Rendering_Options(options);
	return;
}

extern DLLEXPORT void HP_Close( void )
{
	FreeParasolidFrustrumMemory();
	PK_SESSION_stop();

	if( g_pMap )
	{
	    delete g_pMap;
	    g_pMap = 0;
	}
}

void startFrustrum(int * ifail)
{
//  calling FRU__delta_init here breaks PK_PARTITION_make_pmark on Linux
//	FRU__delta_init( 1 );
	FSTART(ifail);
}

//-----------------------------------------------------------------------
void stopFrustrum(int * ifail)
{
	FSTOP(ifail);
//	FRU__delta_init( 2 );
}


extern DLLEXPORT void HP_Init( const wchar_t* pathToSchemaFiles, PK_LOGICAL_t useBulletinBoard, bool bUnicodeFilenames)
{
	PK_ERROR_code_t		error_code;
	PK_SESSION_start_o_t	start_options;

	
	PK_SESSION_frustrum_t fru;
	PK_MEMORY_frustrum_t memFru;
	PK_DELTA_frustrum_t deltaFru;

	if (g_pMap)
		return; // already initialized
	
	g_schema_path[0] = L'\0'; // initialize the schema path

	if (pathToSchemaFiles)
	{
		wcsncpy(g_schema_path, pathToSchemaFiles, MAX_SCHEMA_PATH_LENGTH - 1);
	}

	g_pMap = new HP_Map();

	HP_InitializeRenderOptions();

	if ( bUnicodeFilenames )
		PK_SESSION_set_unicode( PK_LOGICAL_true);

	PK_SESSION_frustrum_o_m( fru );
	fru.fstart = startFrustrum;
	fru.fabort = FABORT;
	fru.fstop  = stopFrustrum;
	fru.fmallo = FMALLO;
	fru.fmfree = FMFREE;
	fru.gosgmt = GOSGMT;
	fru.goopsg = GOOPSG;
	fru.goclsg = GOCLSG;
	fru.gopixl = GOPIXL;
	fru.gooppx = GOOPPX;
	fru.goclpx = GOCLPX;
	fru.ffoprd = FFOPRD;
	fru.ffopwr = FFOPWR;
	fru.ffclos = FFCLOS;
	fru.ffread = FFREAD;
	fru.ffwrit = FFWRIT;
	fru.ffoprb = FFOPRB;
	fru.ffseek = FFSEEK;
	fru.fftell = FFTELL;
	fru.fgcrcu = FGCRCU;
	fru.fgcrsu = FGCRSU;
	fru.fgevcu = FGEVCU;
	fru.fgevsu = FGEVSU;
	fru.fgprcu = FGPRCU;
	fru.fgprsu = FGPRSU;
	if ( bUnicodeFilenames )
	{
		fru.ucoprd = UCOPRD;  //Unicode open file for read
		fru.ucopwr = UCOPWR;  //Unicode open file for write 
	}

	error_code = PK_SESSION_register_frustrum( &fru );
	assert(error_code == PK_ERROR_no_errors);
	memFru.alloc_fn = AllocateDynamic;
	memFru.free_fn = FreeDynamic;

	deltaFru.open_for_read_fn = FRU_delta_open_for_read;
	deltaFru.open_for_write_fn = FRU_delta_open_for_write;
	deltaFru.close_fn = FRU_delta_close;
	deltaFru.read_fn = FRU_delta_read;
	deltaFru.write_fn = FRU_delta_write;
	deltaFru.delete_fn = FRU_delta_delete;

	error_code = PK_MEMORY_register_callbacks( memFru );
	assert(error_code == PK_ERROR_no_errors);
	error_code = PK_DELTA_register_callbacks( deltaFru );
	assert(error_code == PK_ERROR_no_errors);

	PK_SESSION_start_o_m( start_options );
//	start_options.journal_file = "journal";
	start_options.user_field = 8;
	start_options.o_t_version = 1;
	start_options.reserved = 0;

	error_code = PK_SESSION_start(&start_options);
	if ( error_code!=0){
		return;
	}
	if (useBulletinBoard != PK_LOGICAL_false)
	{
		s_pBB = new HP_BulletinBoard();
		assert(s_pBB);
	}
	else
		s_pBB = 0;
}

extern DLLEXPORT void HP_Init( const char* pathToSchemaFiles, PK_LOGICAL_t useBulletinBoard, bool bUnicodeFilenames)
{
	HP_Init(H_UNICODE_TEXT(pathToSchemaFiles), useBulletinBoard, bUnicodeFilenames);
}

extern DLLEXPORT void HP_Update()
{
	bool result;
	PK_ENTITY_t* created;
	unsigned long num_created;
	PK_ENTITY_t* deleted;
	unsigned long num_deleted;
	PK_ENTITY_t* altered;
	unsigned long num_altered;
	PK_ENTITY_t* transformed;
	unsigned long num_transformed;

	unsigned long i;

	PK_LOGICAL_t is_entity;
	PK_CLASS_t entityClass=0;
	PK_ERROR_t error;
	unsigned long preExisting_options;


	if (s_pBB)
	{

		preExisting_options = HP_Internal_Get_Rendering_Options();

			
		// *FIX we need to deal with the case where user has set merge faces or merge bodies,
		
		// since the Update version of the integration does not currently handle this.

		assert (!((preExisting_options & HP_MERGE_FACES) || (preExisting_options & HP_MERGE_BODIES)));
									
		result = s_pBB->GetChangedEntities(&created, &num_created,
										   &deleted, &num_deleted,
										   &altered, &num_altered,
										   &transformed, &num_transformed);
		assert(result);
		
		if (num_altered)
			HP_Delete_Entity_Geometry(num_altered, altered);

		if (num_deleted)
		{
			HP_Delete_Entity_Geometry(num_deleted, deleted);
			PK_MEMORY_free(deleted);
		}

		for (i = 0; i < num_created; i++)
		{

			assert(created[i] != 0);

			error = PK_ENTITY_is(created[i], &is_entity);
			assert(!error);
			if (is_entity) // this entity has not been deleted
			{
				error = PK_ENTITY_ask_class(created[i], &entityClass);
				assert(!error);
			}
			else
			{
				assert(0); // this created[i] absolutely should be a valid entity
			}
			switch(entityClass)
			{
			case PK_CLASS_body:
				HP_Internal_Set_Rendering_Options(preExisting_options | HP_RENDER_EDGES | HP_RENDER_FACES);
				HP_Render_Entity(created[i]);
				break;
			case PK_CLASS_face:
				HP_Internal_Set_Rendering_Options((preExisting_options & (~HP_RENDER_EDGES)) | HP_RENDER_FACES);
				HP_Render_Entity(created[i]);
				break;
			case PK_CLASS_edge:
				HP_Internal_Set_Rendering_Options((preExisting_options | HP_RENDER_EDGES) & (~HP_RENDER_FACES));
				HP_Render_Entity(created[i]);
				break;
			default:
				// do nothing, not interested in other entity types
				// *FIX assert (0) here, eventually we should get clean arrays back.
				break;
			}
		}
		if (num_created)
			PK_MEMORY_free(created);


		for (i = 0; i < num_altered; i++)
		{

			assert(altered[i] != 0);

			error = PK_ENTITY_is(altered[i], &is_entity);
			assert(!error);
			if (is_entity) // this entity has not been deleted
			{
				error = PK_ENTITY_ask_class(altered[i], &entityClass);
				assert(!error);
			}
			else
			{
				assert(0); // this created[i] absolutely should be a valid entity
			}
			switch(entityClass)
			{
			case PK_CLASS_body:
				HP_Internal_Set_Rendering_Options(preExisting_options | HP_RENDER_EDGES | HP_RENDER_FACES);
				HP_Render_Entity(altered[i]);
				break;
			case PK_CLASS_face:
				HP_Internal_Set_Rendering_Options((preExisting_options & (~HP_RENDER_EDGES)) | HP_RENDER_FACES);
				HP_Render_Entity(altered[i]);
				break;
			case PK_CLASS_edge:
				HP_Internal_Set_Rendering_Options((preExisting_options | HP_RENDER_EDGES) & (~HP_RENDER_FACES));
				HP_Render_Entity(altered[i]);
				break;
			default:
				// do nothing, not interested in other entity types
				// *FIX assert (0) here, eventually we should get clean arrays back.
				break;
			}
		}
		if (num_altered)
			PK_MEMORY_free(altered);

		HP_Internal_Set_Rendering_Options(preExisting_options);
		s_pBB->UpdateBulletins();
	}
}

#ifndef _MSC_VER
#define wcsicmp wcscasecmp
#endif
 
extern PK_ERROR_code_t DLLEXPORT HP_Write_Xmt_File(const __wchar_t *filename, int n_parts, const PK_PART_t *parts, const PK_PART_transmit_o_t *options)
{
	
	int i;
	__wchar_t xtfilename[4096];
	__wchar_t totalfilename[4096];
	__wchar_t const * exten = wcsrchr(filename, L'.');

	if(exten)
		++exten;
	else
		exten = L"";
	
	if (wcsicmp(exten, L"hmf.x_t")==0)
	{
 		wcscpy(xtfilename,filename);
 		 		
		char type[128];
		HC_KEY key;
  				
		__wchar_t hmf_filename[4096];
 		wcscpy(hmf_filename,filename);
		__wchar_t * endpos = wcsrchr(hmf_filename, L'.');
		if (endpos)
			*endpos = 0;
 		wcscat(hmf_filename, L".hmf");

  		wcscpy(totalfilename,filename);

		endpos = wcsrchr(xtfilename, L'.');
		if (endpos)
			*endpos = 0;
 		wcscat(xtfilename, L".x_t2");

 		char owner[128];
		HC_KEY skey = g_pMap->FindMapping(parts[0]);
		HC_Show_Segment(skey, owner);
		
		char *newpos = owner;
		for (i = 0;i < 3;i++)
			newpos=strchr(newpos,'/') + 1;
		if (newpos!=owner)
			*(newpos-1)=0;
		
		
		PK_PARTITION_t curr;
		PK_SESSION_ask_curr_partition( &curr );
		PK_BODY_t *bodies;
		int numbodies;
		PK_PARTITION_ask_bodies(curr,&numbodies,&bodies);		
		
		PK_ATTDEF_sf_t attdef;
		PK_CLASS_t lowner[3] = {PK_CLASS_body,PK_CLASS_face,PK_CLASS_edge};
		PK_ATTRIB_field_t afield = PK_ATTRIB_field_integer_c;
		char def_name[512];
		strcpy(def_name, "TA_hash");
		attdef.name=def_name;
		attdef.attdef_class = PK_ATTDEF_class_01_c;
		attdef.n_owner_types = 3;
		attdef.owner_types = lowner;
		attdef.n_fields = 1;
		attdef.field_types = &afield;
		
		PK_ATTDEF_t att;
		PK_ATTDEF_create(&attdef, &att);
		
		
		for (i = 0;i < numbodies;i++)
		{
			int num_ent;
			PK_ENTITY_t *entities;
			for (int j = 0;j < 3;j++)
			{
				if (j == 0)
				{
					num_ent = 1;
					entities = new PK_ENTITY_t;
					*entities = bodies[i];
				}
				else if (j==1)
					PK_BODY_ask_faces(bodies[i],&num_ent,&entities);
				else if (j==2)
					PK_BODY_ask_edges(bodies[i],&num_ent,&entities);
				
				for (int k = 0;k < num_ent;k++)
				{
					HC_KEY keys[10000];
					int num_keys = g_pMap->FindMapping(entities[k],keys,10000);
					if (num_keys)
					{
						for (int l = 0;l<num_keys;l++)
						{
							if (keys[l] < 0)
								keys[l] = -keys[l];
						}
						
						PK_ATTRIB_t attr;
						PK_ATTRIB_create_empty(entities[k],att,&attr);
						PK_ATTRIB_set_ints(attr, 0, num_keys,(const int *)keys);
					}
				}
				if (j>0)
					PK_MEMORY_free(entities);
				else
					delete entities;
			}
		}
		
		
		HC_Open_Segment(owner);
		
		HC_Begin_Contents_Search("./...","geometry, segment");
		while (HC_Find_Contents(type,&key))
		{
			
			HC_Renumber_Key(key, -key, "global");	
		}
		HC_End_Contents_Search();
		HC_Write_Metafile(".", H_ASCII_TEXT(hmf_filename), "");
	
		
		HC_Begin_Contents_Search("./...", "geometry, segment");
		while (HC_Find_Contents(type,&key))
			HC_Renumber_Key(key, -1, "global");					
		HC_End_Contents_Search();				
		
		HC_Close_Segment();
		
		PK_ERROR_t err=PK_PART_transmit_u(n_parts, parts, (unsigned short const*)H_UTF16(xtfilename).encodedText(), options);


		FILE *t_stream = wfopen(totalfilename, L"wb");
		FILE *s_stream = wfopen(hmf_filename, L"rb");
		fseek(s_stream,0,SEEK_END);
		int size=ftell(s_stream);
		fseek(s_stream,0,SEEK_SET);

		fwrite(&size,sizeof(int),1,t_stream);
		unsigned char buffer[4096];
		for (;;)
		{
			int datain = fread(buffer,1,4096,s_stream);
			fwrite (buffer,1,datain,t_stream);
			if (datain!=4096)
				break;
		}
		fclose (s_stream);
		s_stream = wfopen(xtfilename, L"rb");
		for (;;)
		{
			int datain = fread(buffer,1,4096,s_stream);
			fwrite (buffer,1,datain,t_stream);
			if (datain!=4096)
				break;
		}
		fclose (s_stream);
 		fclose (t_stream);
		wremove (xtfilename);
		wremove (hmf_filename);
		
		for (i=0;i<numbodies;i++)
		{
			int num_ent;
			PK_ENTITY_t *entities;
			for (int j = 0;j < 3;j++)
			{
				if (j==0)
				{
					num_ent = 1;
					entities = new PK_ENTITY_t;
					*entities = bodies[i];
				}
				else if (j==1)
					PK_BODY_ask_faces(bodies[i], &num_ent, &entities);
				else if (j==2)
					PK_BODY_ask_edges(bodies[i], &num_ent, &entities);
				int numdel;
				for (int k=0;k<num_ent;k++)
					PK_ENTITY_delete_attribs(entities[k], att, &numdel);
				
				if (j>0)
					PK_MEMORY_free(entities);
				else
					delete entities;
			}
		}				
		return err;
	}
	else
		return PK_PART_transmit_u(n_parts, parts, (unsigned short const*)H_UTF16(filename).encodedText(), options);
}

extern PK_ERROR_code_t DLLEXPORT HP_Write_Xmt_File(const char *filename, int n_parts, const PK_PART_t *parts, const PK_PART_transmit_o_t *options)
{
	return HP_Write_Xmt_File(H_UNICODE_TEXT(filename), n_parts, parts, options);
}


extern PK_ERROR_code_t DLLEXPORT HP_Read_Xmt_File(const __wchar_t *fname, PK_PARTITION_t file_partition, int* num_parts, PK_PART_t** parts, const PK_PART_receive_o_t *options, bool no_tesselation)
{	
  	unsigned int i;
	bool readHMF=false;
	__wchar_t hmf_filename[4096];
	__wchar_t xtfilename[4096];
	__wchar_t const * ext = wcsrchr(fname, L'@');
	if(ext)
		++ext;
	else
		ext = L"";

	wcscpy(xtfilename,fname);
	
	if (wcsicmp(ext, L"hmf.x_t")==0)
	{
		wcscpy(hmf_filename,fname);
		__wchar_t * endpos = wcsrchr(hmf_filename, L'.');
		if (endpos)
			*endpos = 0;
 		wcscat(hmf_filename, L".hmf");
	 	endpos = wcsrchr(xtfilename, L'.');
		if (endpos)
			*endpos = 0;
 		wcscat(xtfilename, L".x_t2");


		FILE *s_stream = wfopen(fname, L"rb");
		FILE *t_stream = wfopen(hmf_filename, L"wb");
	 
		int size;
		fread(&size,sizeof(int),1,s_stream);
		unsigned char buffer[4096];
		for (int i=0;i<size;i+=4096)
		{
			int datain;
			if ( i+4096 >= size)
				datain = size-i;
			else
				datain = 4096;
			fread(buffer,1,datain,s_stream);
			fwrite (buffer,1,datain,t_stream);
			if (datain!=4096)
				break;
		}
		fclose (t_stream);
		t_stream = wfopen(xtfilename, L"wb");
   		for (;;)
		{
 			int datain = fread(buffer,1,4096,s_stream);
			fwrite (buffer,1,datain,t_stream);
			if (datain!=4096)
				break;
		}
		fclose (t_stream);
 		fclose (s_stream);
		readHMF=true;
 	
 		HC_Read_Metafile(H_ASCII_TEXT(hmf_filename), ".", "");	 
		wremove (hmf_filename);
	}


	PK_ERROR_code_t error;
	ParaFileList* newFileElt;

	newFileElt = new ParaFileList;
	newFileElt->next = pfiles;
	newFileElt->pfile = new Parafile();
	pfiles = newFileElt;

	if (s_pBB)  // use of bulletin board is ON
	{
		error = PK_BB_set_status(s_pBB->GetBB(), PK_BB_status_off_c);
		assert(!error);
	}
	if (!g_instances_to_bodies)
		error = pfiles->pfile->OpenFile(xtfilename, file_partition, num_parts, parts, options,no_tesselation);
	else
		error = pfiles->pfile->OpenFileFlat(xtfilename, file_partition, num_parts, parts, options,no_tesselation);

	if( error != PK_ERROR_no_errors )
		return error;

	if (s_pBB)  // use of bulletin board is ON
	{
		PK_ERROR_code_t error;
		error = PK_BB_set_status(s_pBB->GetBB(), PK_BB_status_on_c);
		assert(!error);
	}
	
	if (readHMF)
	{
		wremove (xtfilename);
 			
		PK_PARTITION_t curr;
		PK_SESSION_ask_curr_partition( &curr );
		PK_BODY_t *bodies;
		int numbodies;
		PK_PARTITION_ask_bodies(curr, &numbodies, &bodies);
	 

		PK_ATTDEF_t att;
		PK_ATTDEF_find("TA_hash", &att);
 
// 		delete g_pMap;
//		g_pMap = new HP_Map();

		for (i = 0;i < (unsigned int)numbodies;i++)
		{
			int num_ent;
			PK_ENTITY_t *entities;
			for (int j = 0;j < 3;j++)
			{
				if (j==0)
				{
					num_ent = 1;
					entities = new PK_ENTITY_t;
					*entities = bodies[i];
				}
				else if (j==1)
					PK_BODY_ask_faces(bodies[i], &num_ent, &entities);
				else if (j==2)
					PK_BODY_ask_edges(bodies[i], &num_ent, &entities);
				if (num_ent)
				{
					for (int k = 0;k < num_ent;k++)
					{
						int n_atts;
						PK_ATTRIB_t *at;
						int *bid;
						int numints;
						PK_ENTITY_ask_attribs(entities[k], att, &n_atts, &at);
						if (n_atts)
						{
							PK_ATTRIB_ask_ints(at[0], 0, &numints, &bid);
							if (numints)
							{
								for (int l=0;l < numints;l++)
								{
									HC_KEY hoopskey = HC_KRenumber_Key(bid[l], -1, "global");
									g_pMap->AddMapping(hoopskey, entities[k]);
								}
								PK_MEMORY_free(bid);
							}
							PK_MEMORY_free(at);
							int numdel;
							PK_ENTITY_delete_attribs(entities[k], att, &numdel);
						}
					}
					
					if (j>0)
						PK_MEMORY_free(entities);
					else
						delete entities;
				}
				
			}
		}
						
		
		char type[256];
		HC_KEY key;
		
		HC_Begin_Contents_Search("./...", "geometry, segment");
		while (HC_Find_Contents(type, &key))
		{
			HC_Renumber_Key(key,-1, "global");
		}				
		
		HC_End_Contents_Search();					
	}
		
	return error;
}


extern PK_ERROR_code_t DLLEXPORT HP_Read_Xmt_File(const char *fname, PK_PARTITION_t file_partition, int* num_parts, PK_PART_t** parts, const PK_PART_receive_o_t *options, bool no_tesselation)
{
	return HP_Read_Xmt_File(H_UNICODE_TEXT(fname), file_partition, num_parts, parts, options, no_tesselation);
}
 

#define MAX_FIXED_KEY_ARRAY 1000
extern DLLEXPORT void HP_Delete_Entity_Geometry(unsigned long count, PK_ENTITY_t* entities, bool PreserveSegments)
{
	unsigned long i;
	long j;
	long num_keys = 0;
	long total_num_keys = 0;
	long max_allocated_key_array = MAX_FIXED_KEY_ARRAY;
	HC_KEY fixed_size_key_array[MAX_FIXED_KEY_ARRAY];
	HC_KEY *dynamic_size_key_array = 0;
	HC_KEY *keys = 0;
	keys = fixed_size_key_array;
	char key_type[120];
	PK_CLASS_t para_class;
	PK_ERROR_code_t error_code;
	unsigned long types;

	for ( i = 0 ; i < count ; i++ ) {
		error_code = PK_ENTITY_ask_class(entities[i], &para_class);
		if (para_class == PK_CLASS_assembly) {
			int n_insts;
			PK_INSTANCE_t *insts;
			error_code = PK_ASSEMBLY_ask_instances(entities[i], &n_insts, &insts);
			assert(error_code == PK_ERROR_no_errors);
			int n_entities = n_insts;
			PK_ENTITY_t *sub_entities = new PK_ENTITY_t [n_entities];
			PK_INSTANCE_sf_t inst_sf;
			int j;
			for ( j = 0 ; j < n_entities ; j++ ) {
				error_code = PK_INSTANCE_ask(insts[j], &inst_sf);
				assert(error_code == PK_ERROR_no_errors);
				sub_entities[j] = inst_sf.part;
			}
			HP_Delete_Entity_Geometry(n_entities, sub_entities, PreserveSegments);
			delete [] sub_entities;
			HP_Delete_Entity_Geometry(n_insts, insts, PreserveSegments);
			PK_MEMORY_free(insts);
			types = HP_GEOMETRY_TYPE_assemblies;
		}
		else if (para_class == PK_CLASS_instance)
			types = HP_GEOMETRY_TYPE_instances;
		else
			types = HP_GEOMETRY_TYPE_vertices | HP_GEOMETRY_TYPE_edges | HP_GEOMETRY_TYPE_faces | HP_GEOMETRY_TYPE_bodies;

		num_keys = HP_Compute_Geometry_Keys_internal(entities[i], keys+total_num_keys, types, 
				   max_allocated_key_array - total_num_keys);
		if (num_keys <= 0)
			continue; // cannot delete this entry

		if (num_keys >= max_allocated_key_array - total_num_keys) // the fixed_size array was not big enough
		{
			long reality_check_num_keys = 0;
			num_keys = HP_Compute_Geometry_Key_Count_internal(entities[i], types);

			assert(total_num_keys + num_keys >= max_allocated_key_array);
			if (i == (count - 1))
				max_allocated_key_array = total_num_keys + num_keys + 1;  // add one just to make assert later more capable of finding discrepancies 
																		  // between counts of HP_Compute_Geometry_Keys and HP_Compute_Geometry_Key_Count
			else
				max_allocated_key_array = (total_num_keys + num_keys) * 2;  // avoid excessive re-allocation later

			
			dynamic_size_key_array = (HC_KEY*) realloc(dynamic_size_key_array, max_allocated_key_array * sizeof(HC_KEY));
			if (!dynamic_size_key_array)
			{
				assert(0);
				return;
			}
			// the contents of fixed size array was never copied over if the number of keys exceeded MAX_FIXED_KEY_ARRAY
			if (keys==fixed_size_key_array)
				memcpy(dynamic_size_key_array, keys, sizeof(HC_KEY)*total_num_keys);
			keys = dynamic_size_key_array;
			
			reality_check_num_keys = HP_Compute_Geometry_Keys_internal(entities[i], keys+total_num_keys, types,
									 max_allocated_key_array - total_num_keys);
			assert(reality_check_num_keys == num_keys);
		}
		total_num_keys += num_keys;
	}

	// remove duplicate keys using a hash
	VHash<HC_KEY, int> key_hash;
	int temp;
	vhash_status_t lookup_status;
	for ( j = 0 ; j < total_num_keys ; j++ ) {
		lookup_status = key_hash.LookupItem(keys[j], &temp);
		if (lookup_status == VHASH_STATUS_FAILED) {
			key_hash.InsertItem(keys[j], 1);
		}
	}
	VHash<HC_KEY, int>::PairList *key_list = key_hash.GetPairList();
	VList<HC_KEY> seg_list;

	// to get around annoying HOOPS limitation of not being able to tell
	// whether something has been already deleted when deleting,
	// we will potentially make 2 passes here, first deleting non-segments
	// and then deleting segments.
	VHash<HC_KEY, int>::Pair *cursor;
	key_list->ResetCursor();
	for ( cursor = (VHash<HC_KEY, int>::Pair *)key_list->PeekCursor() ; 
		  NULL != (cursor = (VHash<HC_KEY, int>::Pair *)key_list->PeekCursor()) ; 
		  key_list->AdvanceCursor() ) {
		bool result;

		if (!HC_Show_Existence_By_Key(cursor->Key(), "self")) {
			g_pMap->DeleteMapping(cursor->Key());
			continue;
		}

		HC_Show_Key_Type(cursor->Key(), key_type);
		if (streq(key_type, "segment")) {
			// key is to a segment; delete it last.
			seg_list.AddFirst(cursor->Key());

			HC_KEY key;
			char type[64] = { "" };

			HC_Open_Segment_By_Key(cursor->Key());
			{
				HC_Begin_Contents_Search("...", "shells");
				{
					while (HC_Find_Contents(type, &key))
					{
						HC_Delete_By_Key(key);
					}
				}
				HC_End_Contents_Search();
			}
			HC_Close_Segment();

			continue;
		}

		result = g_pMap->DeleteMapping(cursor->Key());

		if (result)
			HC_Delete_By_Key(cursor->Key());
	}
	delete key_list;

	if (!PreserveSegments) {
		HC_KEY key;
		seg_list.ResetCursor();
		for ( key = seg_list.PeekCursor() ; (key = seg_list.PeekCursor()) ; seg_list.AdvanceCursor() ) {
			// now, delete the segment keys.
			bool result;
			
			result = g_pMap->DeleteMapping(key);
				
			if (result)
				HC_Delete_By_Key(key);
		}
	}
	if (dynamic_size_key_array)
		free(dynamic_size_key_array);
}

extern DLLEXPORT void HP_Show_Rendering_Options(char * list)
{

	if(list){
	
		strcpy(list,"");

		if(g_color_segment_mode){
			strcat(list,"preserve color = on, ");
		}else{
			strcat(list,"preserve color = off, ");
		}
		if(g_body_segment_mode){
			strcat(list,"create body segments = on, ");
		}else{
			strcat(list,"create body segments = off, ");
		}
		if(g_merge_faces_mode){
			strcat(list,"merge faces = on, ");
		}else{
			strcat(list,"merge faces = off, ");
		}
		if(g_merge_bodies_mode){
			strcat(list,"merge bodies = on, ");
		}else{
			strcat(list,"merge bodies = off, ");
		}
		if(g_render_edges_mode){
			strcat(list,"edges = on, ");
		}else{
			strcat(list,"edges = off, ");
		}
		if(g_render_faces_mode){
			strcat(list,"faces = on ");
		}else{
			strcat(list,"faces = off ");
		}
	
		return;
	}else{		
		// error
		const char * mes = "Null list passed...";
		const char * mesv[1]; 
		
		const char * fun = "HP_Show_Rendering_Options";
		const char * funv[1];

		mesv[0]=mes;
		funv[0]=fun;

		HC_Report_Error(50,309,1,1,mesv,1,funv);
	}		
}

extern DLLEXPORT void HP_Show_One_Rendering_Option(const char * type, char * value)
{
	char ltype[1025];
	int i;

	if(type && value){

		
		// my canonize chars
		for(i=0; i<1024; i++){

			if(!type[i]) break;	
			ltype[i] = (char) tolower((int)type[i]);
		}
		ltype[i] = 0;

	
		strcpy(value,"");

		if (strstr(ltype,"preserve color")){
	
			if(g_color_segment_mode){
				strcat(value,"on");
			}else{
				strcat(value,"off");
			}
			return;		
		}
		else
		if (strstr(ltype,"create body segments")){
			
			if(g_body_segment_mode){
				strcat(value,"on");
			}else{
				strcat(value,"off");
			}
			return;
		}
		else
		if (strstr(ltype,"merge faces")){
		
			if(g_merge_faces_mode){
				strcat(value,"on");
			}else{
				strcat(value,"off");
			}
			return;
		} else		
		if (strstr(ltype,"edges")){
		
			if(g_render_edges_mode){
				strcat(value,"on");
			}else{
				strcat(value,"off");
			}
			return;
		} else
		if (strstr(ltype,"faces")){
		
			if(g_render_faces_mode){
				strcat(value,"on");
			}else{
				strcat(value,"off");
			}
			return;
		} else
		if (strstr(ltype,"tessellate ellipses")){
		
			if(g_tessellate_ellipses_mode){
				strcat(value,"on");
			}else{
				strcat(value,"off");
			}
			return;
		} else
		{		
			// error
			const char * mes = "Unknown type in:";
			const char * mesv[2]; 
		
			const char * fun = "HP_Show_One_Rendering_Option";
			const char * funv[1];

			mesv[0]=mes;
			mesv[1]=(char*)type;
			funv[0]=fun;

			HC_Report_Error(50,309,1,2,mesv,1,funv);
			return;
		}	
	}else{		
		// error
		const char * mes = "Null type or value";
		const char * mesv[1]; 
		
		const char * fun = "HP_Show_One_Rendering_Option";
		const char * funv[1];

		mesv[0]=mes;
		funv[0]=fun;

		HC_Report_Error(50,309,1,1,mesv,1,funv);
	}		
}


void initialize_generation_settings(PK_TOPOL_facet_mesh_o_t     *generation_settings)
{
	PK_TOPOL_facet_mesh_o_m( *generation_settings );

	 generation_settings->shape = PK_facet_shape_convex_c ;
	 generation_settings->match = PK_facet_match_topol_c;
	 generation_settings->density = PK_facet_density_no_view_c;
	 generation_settings->cull = PK_facet_cull_none_c;
	 generation_settings->n_loops = 0;
	 generation_settings->loops = 0;
	 generation_settings->max_facet_sides = 100000;
	 generation_settings->is_min_facet_width = PK_LOGICAL_false;
	 generation_settings->min_facet_width =0;
	 generation_settings->is_max_facet_width = PK_LOGICAL_false;
	 generation_settings->max_facet_width = 0;
	 generation_settings->is_curve_chord_tol = PK_LOGICAL_false;
	 generation_settings->curve_chord_tol = 0;
	 generation_settings->is_curve_chord_max = PK_LOGICAL_false;
	 generation_settings->curve_chord_max = 0;
	 generation_settings->is_curve_chord_ang = PK_LOGICAL_true;
	 generation_settings->curve_chord_ang = 0.2; //radians
	 generation_settings->is_surface_plane_tol = PK_LOGICAL_false;
	 generation_settings->surface_plane_tol = 0.0;
	 generation_settings->is_surface_plane_ang = PK_LOGICAL_false;
	 generation_settings->surface_plane_ang = 0.0;
	 generation_settings->is_facet_plane_tol = PK_LOGICAL_false;
	 generation_settings->facet_plane_tol = 0.0;
	 generation_settings->is_facet_plane_ang = PK_LOGICAL_true;
	 generation_settings->facet_plane_ang = 0.01; // radians
	 generation_settings->is_local_density_tol = PK_LOGICAL_false;
	 generation_settings->local_density_tol = 0.0;
	 generation_settings->is_local_density_ang = PK_LOGICAL_false;
	 generation_settings->local_density_ang = 0.0;
}

void initialize_go_options(PK_TOPOL_render_facet_go_o_t		*go_options)
{
	PK_TOPOL_render_facet_go_o_m( *go_options );
	go_options->go_normals = PK_facet_go_normals_yes_c;
	go_options->go_parameters = PK_facet_go_parameters_no_c;
	go_options->go_edges = PK_facet_go_edges_no_c;
	
//GH99
	go_options->go_strips = PK_facet_go_strips_yes_c;
	go_options->go_max_facets_per_strip = 1000;				//is this a good setting?
}

void initialize_line_generation_settings(PK_TOPOL_render_line_o_t  *line_Options)
{

	PK_TOPOL_render_line_o_m( *line_Options );

	// do render parasolid edges.
	line_Options->edge = PK_render_edge_yes_c;

	// don't render silhouette edges as these are view-dependent
	line_Options->silhouette= PK_render_silhouette_no_c;

	// render planar hatches when the entity has planar hatch attribute set
	line_Options->planar = PK_render_planar_attrib_c; 

	// render radial hatches when the entity has radial hatch attribute set
	line_Options->radial = PK_render_radial_attrib_c;

	// render parametric hatches when the entity has parametric hatch attribute set
	line_Options->param = PK_render_param_attrib_c;

	// render unfixed blends as defined by blend attribute (? rw)
	line_Options->unfix = PK_render_unfix_no_c;

// "visibility" can have the values:
//    PK_render_vis_no_c            no visibility evaluated (default)
//    PK_render_vis_hid_c           don't output hidden lines
//    PK_render_vis_inv_c           output hidden lines marked as invisible
//    PK_render_vis_inv_draft_c     output hidden lines and distinguish between
//                                  those hidden by other lines and those
//                                  hidden by faces.
//    PK_render_vis_extended_c      visibility is evaluated.  The information
//                                  output is controlled by the 'invisible',
//                                  'drafting' and 'self_hidden' options of
//                                  the PK_TOPOL_render_line_o_t structure.
	line_Options->visibility = PK_render_vis_no_c;
	line_Options->invisible = PK_render_invisible_no_c;
	line_Options->drafting = PK_render_drafting_no_c;
	line_Options->self_hidden = PK_render_self_hidden_no_c;

	// don't distinguish whether edges are smooth
	line_Options->smooth = PK_render_smooth_no_c;

	// don't indicate whether edges are internal
	line_Options->internal = PK_render_internal_no_c;

	// don't output regional information
	line_Options->region = PK_render_region_no_c;

	line_Options->hierarch = PK_render_hierarch_no_c;

	// output bcurves as polylines
	line_Options->bcurve= PK_render_bcurve_polyline_c;

	// don't skip geometry outside the viewport
	line_Options->viewport = PK_render_viewport_no_c;

	line_Options->is_curve_chord_tol = PK_LOGICAL_true;
	line_Options->curve_chord_tol = 0.000344;

	line_Options->is_curve_chord_max = PK_LOGICAL_false;
	line_Options->curve_chord_max = 0.0;	

	line_Options->is_curve_chord_ang = PK_LOGICAL_true;
	line_Options->curve_chord_ang = .39269908175;


	// have not so far found documentation on any of the following, so just setting to zeroes. rw
	line_Options->planar_spacing = 0.0;
	line_Options->planar_axis.axis.coord[0] = 0.0;
	line_Options->planar_axis.axis.coord[1] = 0.0;
	line_Options->planar_axis.axis.coord[2] = 0.0;
	line_Options->planar_axis.location.coord[0] = 0.0;
	line_Options->planar_axis.location.coord[1] = 0.0;
	line_Options->planar_axis.location.coord[2] = 0.0;
	line_Options->radial_around = 0.0;
	line_Options->radial_along = 0.0;
	line_Options->radial_about = 0.0;
	line_Options->param_u = 0.0;
	line_Options->param_v = 0.0;
	line_Options->unfix_spacing = 0.0;

	// have not so far found documentation on any of the following, so just setting to zeroes. rw
	line_Options->viewport_sf.basis_set.ref_direction.coord[0] = 0.0;
	line_Options->viewport_sf.basis_set.ref_direction.coord[1] = 0.0;
	line_Options->viewport_sf.basis_set.ref_direction.coord[2] = 0.0;
	line_Options->viewport_sf.basis_set.axis.coord[0] = 0.0;
	line_Options->viewport_sf.basis_set.axis.coord[1] = 0.0;
	line_Options->viewport_sf.basis_set.axis.coord[2] = 0.0;
	line_Options->viewport_sf.basis_set.location.coord[0] = 0.0;
	line_Options->viewport_sf.basis_set.location.coord[1] = 0.0;
	line_Options->viewport_sf.basis_set.location.coord[2] = 0.0;
	line_Options->viewport_sf.box.coord[0] = 0.0;
	line_Options->viewport_sf.box.coord[1] = 0.0;
	line_Options->viewport_sf.box.coord[2] = 0.0;
	line_Options->viewport_sf.box.coord[3] = 0.0;
	line_Options->viewport_sf.box.coord[4] = 0.0;
	line_Options->viewport_sf.box.coord[5] = 0.0;

}

void HP_InitializeRenderOptions( void )
{
	initialize_generation_settings(&g_facetOptions.control);
	initialize_go_options(&g_facetOptions.go_option);
	initialize_line_generation_settings(&g_lineOptions);
}



extern DLLEXPORT  void  HP_Compute_Selected_Entity_List(PK_ENTITY_t **entities, int *numentities)
{
	int count;
	*numentities=0;
 	HC_Show_Selection_Keys_Count(&count);
	*entities = new PK_ENTITY_t[count];
	HC_KEY *keys = new HC_KEY[count];
	HC_Show_Selection_Keys(&count, keys);
	for (int i=0;i<count;i++)
	{
		PK_ENTITY_t entity;
		entity = g_pMap->FindMapping(keys[i]);
		if (entity)
		{
			(*entities)[*numentities]=entity;
			(*numentities)++;
		}
	}
	delete keys;
}



 


extern DLLEXPORT PK_ENTITY_t HP_Compute_TagID ( HC_KEY key, PK_CLASS_t paraClass ) {
	PK_ENTITY_t		entity;
	PK_ERROR_code_t error = 0;
	PK_PART_t		part = 0;
	PK_REGION_t		region = 0;
	PK_PARTITION_t	partition = 0;
	PK_BODY_t		body = 0;
	PK_CURVE_t		curve = 0;
	PK_POINT_t		pt = 0;
	PK_SHELL_t		shells[2];
	PK_CLASS_t		entityClass;

	if (HC_Show_Existence_By_Key(key, "self")) {
		assert(g_pMap);
		if (!g_pMap) 
			return 0;
		entity = g_pMap->FindMapping(key);
		if (!entity) {
			if ( paraClass == PK_CLASS_body || paraClass == PK_CLASS_instance ) {
				HC_KEY ancestorSegment;
				// be more forgiving if they are interested in a body pointer; 
				// in case this entity has been rendered in merge_faces mode we need
				// to be a bit tricky about obtaining this info, if and only if 
				// they are looking to get the body associated with a given shell.
				char keytype[120];
				HC_Show_Key_Type(key, keytype);
				if ( (keytype[0] == 's' && keytype[1] == 'h') || paraClass == PK_CLASS_instance ) {
					// look to the parent and grandparent segment of this shell in the hopes of finding
					// a body segment, which will have a mapping to the body entity.
					ancestorSegment = HC_KShow_Owner_By_Key(key);
					entity = g_pMap->FindMapping(ancestorSegment);
					if (!entity) {
						ancestorSegment = HC_KShow_Owner_By_Key(ancestorSegment);
						entity = g_pMap->FindMapping(ancestorSegment);
#ifdef _DEBUG
						if (entity) {
							PK_CLASS_t entityClass;
							error = PK_ENTITY_ask_class(entity, &entityClass);
							assert(!error);
							if (paraClass == PK_CLASS_body)
								assert(entityClass == PK_CLASS_body);
							else
								assert(entityClass == PK_CLASS_instance);

						}
#endif
						return entity; // if entity is 0, that's an appropriate return value here.
					}
				}
				else
					return 0;
			}
			else
				return 0; 
		}
	}
	else
	{
		return 0;
	}
	error = PK_ENTITY_ask_class(entity, &entityClass);
	if (error) 
		return HP_ERROR_unable_to_determine_entity_class;
	switch (entityClass) {
	case PK_CLASS_vertex:
		switch (paraClass) {
		case PK_CLASS_body:
			error = PK_VERTEX_ask_body(entity, &body);
			return body;
		case PK_CLASS_entity:
			return entity;
		case PK_CLASS_partition:
			error = PK_ENTITY_ask_partition(entity, &partition);
			return partition;
		case PK_CLASS_point:
			error = PK_VERTEX_ask_point(entity, &pt);
			return pt;
		case PK_CLASS_vertex: 
			return entity;
		case PK_CLASS_assembly:
		case PK_CLASS_attdef:
		case PK_CLASS_attrib:
		case PK_CLASS_bb:
		case PK_CLASS_bcurve:
		case PK_CLASS_blendsf:
		case PK_CLASS_bsurf:
		case PK_CLASS_circle:
		case PK_CLASS_class:
		case PK_CLASS_cone:
		case PK_CLASS_curve:
		case PK_CLASS_cyl:
		case PK_CLASS_edge:		// a vertex can be associated with multiple edges
		case PK_CLASS_ellipse:
		case PK_CLASS_error:
		case PK_CLASS_face:		// a vertex can be associated with multiple faces
		case PK_CLASS_fcurve:
		case PK_CLASS_fin:
		case PK_CLASS_fsurf:
		case PK_CLASS_geom:
		case PK_CLASS_group:	// a vertex may belong to more than one group
		case PK_CLASS_line:
		case PK_CLASS_loop:
		case PK_CLASS_mark:
		case PK_CLASS_memory:
		case PK_CLASS_offset:
		case PK_CLASS_part:		// TODO: can a vertex can be associated with multiple parts?
		case PK_CLASS_plane:
		case PK_CLASS_pmark:
		case PK_CLASS_region:	// a vertex may belong to more than one region
		case PK_CLASS_session:
		case PK_CLASS_shell:	// a vertex may belong to more than one shell
		case PK_CLASS_spcurve:
		case PK_CLASS_sphere:
		case PK_CLASS_spun:
		case PK_CLASS_surf:
		case PK_CLASS_swept: 
		case PK_CLASS_topol:
		case PK_CLASS_torus:
		case PK_CLASS_transf:
		case PK_CLASS_trcurve: 
		case PK_CLASS_vector:
			return HP_ERROR_non_mappable_entity_class;
		default:
			return HP_ERROR_unknown_entity_class;
		}
		break;
	case PK_CLASS_edge:
		switch (paraClass) {
		case PK_CLASS_body:
			error = PK_EDGE_ask_body(entity, &body);
			return body;
		case PK_CLASS_curve:
			error = PK_EDGE_ask_curve(entity, &curve);
			return curve;
		case PK_CLASS_edge:
		case PK_CLASS_ellipse:
		case PK_CLASS_entity:
			return entity;
		case PK_CLASS_part:
			error = PK_EDGE_ask_curve(entity, &curve);
			error = PK_CURVE_ask_part(curve, &part);
			return part;
		case PK_CLASS_partition:
			error = PK_ENTITY_ask_partition(entity, &partition);
			return partition;	
		case PK_CLASS_assembly:
		case PK_CLASS_attdef:
		case PK_CLASS_attrib:
		case PK_CLASS_bb:
		case PK_CLASS_bcurve:
		case PK_CLASS_blendsf:
		case PK_CLASS_bsurf:
		case PK_CLASS_circle:
		case PK_CLASS_class:
		case PK_CLASS_cone:
		case PK_CLASS_cyl:
		case PK_CLASS_error:
		case PK_CLASS_face:		// an edge can belong to multiple faces
		case PK_CLASS_fcurve:
		case PK_CLASS_fin:
		case PK_CLASS_fsurf:
		case PK_CLASS_geom:
		case PK_CLASS_group:	// an edge may belong to more than one group.
		case PK_CLASS_line:
		case PK_CLASS_loop:
		case PK_CLASS_mark:
		case PK_CLASS_memory:
		case PK_CLASS_offset:
		case PK_CLASS_plane:
		case PK_CLASS_pmark:
		case PK_CLASS_region:	// an edge may belong to more than one region
		case PK_CLASS_session:
		case PK_CLASS_shell:	// an edge may belong to more than one shell
		case PK_CLASS_spcurve:
		case PK_CLASS_sphere:
		case PK_CLASS_spun:
		case PK_CLASS_surf:
		case PK_CLASS_swept: 
		case PK_CLASS_topol:
		case PK_CLASS_torus:
		case PK_CLASS_transf:
		case PK_CLASS_trcurve: 
		case PK_CLASS_vector:
			return HP_ERROR_non_mappable_entity_class;
		default:
			return HP_ERROR_unknown_entity_class;
		}
		break;
	case PK_CLASS_face:
		switch (paraClass) {
		case PK_CLASS_body:
			error = PK_FACE_ask_body(entity, &body);
			return body;
		case PK_CLASS_entity:
		case PK_CLASS_face:
			return entity;
		case PK_CLASS_partition:
			error = PK_ENTITY_ask_partition(entity, &partition);
			return partition;
		case PK_CLASS_region:
			PK_FACE_ask_shells(entity, shells);
			PK_SHELL_ask_region(shells[0], &region);
			return region;
		case PK_CLASS_assembly:
		case PK_CLASS_attdef:
		case PK_CLASS_attrib:
		case PK_CLASS_bb:
		case PK_CLASS_bcurve:
		case PK_CLASS_blendsf:
		case PK_CLASS_bsurf:
		case PK_CLASS_circle:
		case PK_CLASS_class:
		case PK_CLASS_cone:
		case PK_CLASS_curve:
		case PK_CLASS_cyl:
		case PK_CLASS_edge:
		case PK_CLASS_ellipse:
		case PK_CLASS_error:
		case PK_CLASS_fcurve:
		case PK_CLASS_fin:
		case PK_CLASS_fsurf:
		case PK_CLASS_geom:
		case PK_CLASS_group:	// a face may belong to more than one group
		case PK_CLASS_line:
		case PK_CLASS_loop:
		case PK_CLASS_mark:
		case PK_CLASS_memory:
		case PK_CLASS_offset:
		case PK_CLASS_part:		// TODO: can a face belong to more than one part?
		case PK_CLASS_plane:
		case PK_CLASS_pmark:
		case PK_CLASS_point:
		case PK_CLASS_session:
		case PK_CLASS_shell:	// a face may belong to one or two shells
		case PK_CLASS_spcurve:
		case PK_CLASS_sphere:
		case PK_CLASS_spun:
		case PK_CLASS_surf:
		case PK_CLASS_swept: 
		case PK_CLASS_topol:
		case PK_CLASS_torus:
		case PK_CLASS_transf:
		case PK_CLASS_trcurve: 
		case PK_CLASS_vector:
		case PK_CLASS_vertex: 
			return HP_ERROR_non_mappable_entity_class;
		default:
			return HP_ERROR_unknown_entity_class;
		}
		break;
	case PK_CLASS_body:
		switch (paraClass) {
		case PK_CLASS_body:
			return entity;
		default:
			return HP_ERROR_non_mappable_entity_class;
		}
		break;
	case PK_CLASS_instance:
		switch (paraClass) {
		case PK_CLASS_instance:
			return entity;
		default:
			return HP_ERROR_non_mappable_entity_class;
		}
		break;
	default:
		return HP_ERROR_hoops_key_maps_to_invalid_entity_class;

	}
	assert(0);
	return HP_ERROR_not_implemented;
}

extern DLLEXPORT void HP_Show_Tessellation_Options(PK_TOPOL_render_line_o_t *line_Options,
															PK_TOPOL_render_facet_go_o_t *go_options,
															PK_TOPOL_facet_mesh_o_t     *generation_settings)
{
	if (line_Options)
		memcpy(line_Options, &g_lineOptions, sizeof(PK_TOPOL_render_line_o_t));
	if (go_options)
		memcpy(go_options, &g_facetOptions.go_option, sizeof(PK_TOPOL_render_facet_go_o_t));
	if (generation_settings)
		memcpy(generation_settings, &g_facetOptions.control, sizeof(PK_TOPOL_facet_mesh_o_t));
}

extern DLLEXPORT void HP_Set_Tessellation_Options(PK_TOPOL_render_line_o_t *line_Options,
															PK_TOPOL_render_facet_go_o_t *go_options,
															PK_TOPOL_facet_mesh_o_t     *generation_settings)
{
	if (line_Options)
		memcpy(&g_lineOptions, line_Options, sizeof(PK_TOPOL_render_line_o_t));
	if (go_options)
		memcpy(&g_facetOptions.go_option, go_options, sizeof(PK_TOPOL_render_facet_go_o_t));
	if (generation_settings)
		memcpy(&g_facetOptions.control, generation_settings, sizeof(PK_TOPOL_facet_mesh_o_t));
}

long HP_Compute_Geometry_Key_Count_internal ( PK_ENTITY_t tagID, unsigned long geomTypes ) {
	HC_KEY			temp_keys[1000];
	PK_CLASS_t		paraClass;
	PK_ERROR_code_t error = 0;
	PK_VERTEX_t		*vertices = NULL;
	PK_EDGE_t		*edges = NULL;
	PK_FACE_t		*faces = NULL;
	PK_PART_t		*parts = NULL;
	PK_ENTITY_t		*entities = NULL;
	PK_GROUP_t		*groups = NULL;
	PK_BODY_t		*bodies = NULL;
	PK_ASSEMBLY_t	*assemblies = NULL;
	PK_SHELL_t		*shells = NULL;
	int				num_entities = 0;
	long			num_keys = 0;
	long			temp_key_count = 0;
	int				i = 0;

	error = PK_ENTITY_ask_class(tagID, &paraClass);
	
	if (error) {
		//	ALTERED 5/12/99 rlw return HP_ERROR_unable_to_determine_entity_class;

		
		// modify behavior so that delete_entity_geometry can work
		// even after geometry has been deleted from Parasolid.
		// The maximum number of keys that should be mapped to a particular
		// tagID is 2, or the same as the max number of keys mapped to a
		// particular Parasolid edge.  So, we'll proceed by just returning
		// those 0 or 1 or 2 keys mapped to this particular tagID regardless
		// of its (now unknowable) class and hope things work out for the best.
		// in the case of HP_Delete_Entity_Geometry, it should work fine for edges
		// and faces, as well as bodies provided body_segment_mode is on.
		// if the last proviso is not true, then this fn will return nothing
		// and HP_Delete_Entity_Geometry will delete nothing for that
		// particular body.

		paraClass = PK_CLASS_edge;
		geomTypes = HP_GEOMETRY_TYPE_edges;
	}

	switch (paraClass) {
	case PK_CLASS_assembly:
		error = PK_ASSEMBLY_ask_parts(tagID, &num_entities, &parts);
		for ( i = 0 ; i < num_entities ; i++ ) {
			temp_key_count = HP_Compute_Geometry_Key_Count_internal(parts[i], geomTypes);
			if (temp_key_count < 0)
				return temp_key_count;  // return error code
			num_keys += temp_key_count;
		}
		if (parts) {
			PK_MEMORY_free(parts);
			parts = NULL;
		}
		return num_keys;
	case PK_CLASS_attdef:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_attrib:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_bb:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_blendsf:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_body:
		if (geomTypes & HP_GEOMETRY_TYPE_vertices) {
			error = PK_BODY_ask_vertices(tagID, &num_entities, &vertices);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Key_Count_internal(vertices[i], geomTypes);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (vertices) {
				PK_MEMORY_free(vertices);
				vertices = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_edges) {
			// must actually get the geometry here to check for circles
			error = PK_BODY_ask_edges(tagID, &num_entities, &edges);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Key_Count_internal(edges[i], geomTypes);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (edges) {
				PK_MEMORY_free(edges);
				edges = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_faces) {
			// passing null as last arg simply returns count; no allocation is performed
			error = PK_BODY_ask_faces(tagID, &num_entities, &faces);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Key_Count_internal(faces[i], geomTypes);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (faces) {
				PK_MEMORY_free(faces);
				faces = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_bodies) {
   			temp_key_count = g_pMap->FindMapping(tagID, temp_keys, 499);
			if (temp_key_count < 0)
				return temp_key_count;  // return error code
			num_keys += temp_key_count;			 
		}
		return num_keys;
	case PK_CLASS_bsurf:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_class:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_cone:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_bcurve:
	case PK_CLASS_circle:
	case PK_CLASS_curve:
	case PK_CLASS_ellipse:
	case PK_CLASS_fcurve:
	case PK_CLASS_icurve:
	case PK_CLASS_line:
	case PK_CLASS_spcurve:
	case PK_CLASS_trcurve: 
		if (geomTypes & HP_GEOMETRY_TYPE_edges) {
			error = PK_CURVE_ask_edges(tagID, &num_entities, &edges);
			for (i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Key_Count_internal(edges[i], geomTypes);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (edges) {
				PK_MEMORY_free(edges);
				edges = NULL;
			}
		}
		return num_keys;
	case PK_CLASS_cyl:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_edge:
		if (geomTypes & HP_GEOMETRY_TYPE_vertices) {
			num_entities = 2;
			PK_VERTEX_t vertices[2];
			error = PK_EDGE_ask_vertices(tagID, vertices);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Key_Count_internal(vertices[i], geomTypes);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_edges) {
			temp_key_count = g_pMap->FindMapping(tagID, temp_keys, 499);
			if (temp_key_count < 0)
				return temp_key_count;  // return error code
			num_keys += temp_key_count;
		}
		return num_keys;
	case PK_CLASS_entity:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_error:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_face:
		if (geomTypes & HP_GEOMETRY_TYPE_vertices) {
			error = PK_FACE_ask_vertices(tagID, &num_entities, &vertices);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Key_Count_internal(vertices[i], geomTypes);
				if (temp_key_count < 0)
					return temp_key_count; // return error code
				num_keys += temp_key_count;
			}
			if (vertices) {
				PK_MEMORY_free(vertices);
				vertices = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_edges) {
			// must actually get the geometry here to check for circles
			error = PK_FACE_ask_edges(tagID, &num_entities, &edges);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Key_Count_internal(edges[i], geomTypes);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (edges) {
				PK_MEMORY_free(edges);
				edges = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_faces) {
			temp_key_count = g_pMap->FindMapping(tagID, temp_keys, 1000);
			if (temp_key_count < 0)
				return temp_key_count;  // return error code
			num_keys += temp_key_count;
		}
		return num_keys;
	case PK_CLASS_fin:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_fsurf:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_geom:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_group: 
		error = PK_GROUP_ask_entities(tagID, &num_entities, &entities);
		for ( i = 0 ; i < num_entities ; i++ ) {
			temp_key_count = HP_Compute_Geometry_Key_Count_internal(entities[i], geomTypes);
			// this group may contain non-mappable entities.  HP_Compute_Geometry_Key_Count_internal
			// will return negative values as counts (error codes) in that case.  We don't want
			// to screw up the entity count by adding a negative value to the count,
			// nor throw an error in this case.  So just check
			// the value here.
			if (temp_key_count > 0)
				num_keys += temp_key_count;
			else {
				if ( (temp_key_count == HP_ERROR_non_mappable_entity_class) ||
					 (temp_key_count == HP_ERROR_unknown_entity_class)) {
					// ignore this
				}
				else {
					// other errors shouldn't happen
					assert(0);
					return temp_key_count; // which contains error code 
				}
			}
		}
		if (entities) {
			PK_MEMORY_free(entities);
			entities = NULL;
		}
		return num_keys;
	case PK_CLASS_loop:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_mark:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_memory:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_offset:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_part:
		error = PK_PART_ask_groups(tagID, &num_entities, &groups);
		for ( i = 0 ; i < num_entities ; i++ ) {
			temp_key_count = HP_Compute_Geometry_Key_Count_internal(groups[i], geomTypes);
			if (temp_key_count < 0)
				return temp_key_count;  // return error code
			num_keys += temp_key_count;
		}
		if (groups) {
			PK_MEMORY_free(groups);
			groups = NULL;
		}
		return num_keys;
	case PK_CLASS_partition:
		if (geomTypes & HP_GEOMETRY_TYPE_assemblies) {
			error = PK_PARTITION_ask_assemblies(tagID, &num_entities, &assemblies);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Key_Count_internal(assemblies[i], geomTypes);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (assemblies) {
				PK_MEMORY_free(assemblies);
				assemblies = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_bodies) {
			error = PK_PARTITION_ask_bodies(tagID, &num_entities, &bodies);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Key_Count_internal(bodies[i], geomTypes);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (bodies) {
				PK_MEMORY_free(bodies);
				bodies = NULL;
			}
		}
		return num_keys;
	case PK_CLASS_plane:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_pmark:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_point:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_region:
		if (geomTypes & HP_GEOMETRY_TYPE_faces) {
			error = PK_REGION_ask_shells(tagID, &num_entities, &shells);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Key_Count_internal(shells[i], geomTypes);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (shells) {
				PK_MEMORY_free(shells);
				shells = NULL;
			}
		}
		return num_keys;
	case PK_CLASS_session:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_shell:
		if (geomTypes & HP_GEOMETRY_TYPE_faces) {
			error = PK_SHELL_ask_oriented_faces(tagID, &num_entities, &faces, 0);
			
			// each face can appear in the list up to twice; we need to eliminate the counts for the repeats.
			temp_key_count = num_entities;
			for ( i = 0 ; i < num_entities ; i++ ) {
				int j;
				for ( j = i + 1 ; j < num_entities ; j++ ) {
					if (faces[i] == faces[j]) {
						temp_key_count--;
						break; // repeats only happen once; stop looking for repeats of faces[i].
					}
				}
				if (j != num_entities) {
					// no match was found, DO get the key corresponding to this face
					temp_key_count = HP_Compute_Geometry_Key_Count_internal(faces[i], geomTypes);
					if (temp_key_count < 0)
						return temp_key_count;  // return error code
					num_keys += temp_key_count;
				}
			}
			if (faces) {
				PK_MEMORY_free(faces);
				faces = NULL;
			}
			num_keys = temp_key_count;
		}
		if (geomTypes & HP_GEOMETRY_TYPE_edges) {
			error = PK_SHELL_ask_wireframe_edges(tagID, &num_entities, &edges);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Key_Count_internal(edges[i], geomTypes);			
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (edges) {
				PK_MEMORY_free(edges);
				edges = NULL;
			}
		}
		return num_keys;
	case PK_CLASS_sphere:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_spun:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_surf:
		return HP_ERROR_not_implemented;
	case PK_CLASS_swept: 
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_topol:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_torus:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_transf:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_vector:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_vertex: 
		if (geomTypes & HP_GEOMETRY_TYPE_vertices) {
			temp_key_count = g_pMap->FindMapping(tagID, temp_keys, 1000);
			if (temp_key_count < 0)
				return temp_key_count;  // return error code
			num_keys += temp_key_count;
		}
		return num_keys;
	default:
		return HP_ERROR_unknown_entity_class;

	}
	assert(0);
	return HP_ERROR_unknown_entity_class;

}

extern DLLEXPORT long HP_Compute_Geometry_Key_Count ( PK_ENTITY_t tagID, char *list ) {
	char token[1025];
	char token2[1025];
	char llist[1025];
	int i;
	unsigned long geomTypes = 0, geomSwitch;

	// convert chars to lower case
	for ( i = 0 ; i < 1024 ; i++ ) {
		if (!list[i]) 
			break;	
		llist[i] = (char)tolower((int)list[i]);
	}
	llist[i] = 0;


	// loop through options
	i = 0;
	while (1) {
		// we are done if no more tokens are available
		if (!HC_Parse_String(llist, ",", i, token)) 
			return HP_Compute_Geometry_Key_Count_internal(tagID, geomTypes);

		i++;

		geomSwitch = 0;
		if (strstr(token, "vertices"))
			geomSwitch = HP_GEOMETRY_TYPE_vertices;
		else if (strstr(token, "edges"))
			geomSwitch = HP_GEOMETRY_TYPE_edges;
		else if (strstr(token, "faces"))
			geomSwitch = HP_GEOMETRY_TYPE_faces;
		else if (strstr(token, "bodies"))
			geomSwitch = HP_GEOMETRY_TYPE_bodies;
		else if (strstr(token, "instances"))
			geomSwitch = HP_GEOMETRY_TYPE_instances;
		else if (strstr(token, "assemblies"))
			geomSwitch = HP_GEOMETRY_TYPE_assemblies;

		if (geomSwitch) {
			if (0 == strncmp(token, "no", 2)) {
				continue;		
			}
			else if ( strstr(token, "=") && HC_Parse_String(token, "=", -1, token2) ) {
				if (0 == strncmp(token2, "off", 3)) {
					continue;			
				}
				else if (0 == strncmp(token2, "on", 2)) {
					geomTypes |= geomSwitch;
					continue;
				}
				else if (0 == strncmp(token2, "1", 1)) {
					geomTypes |= geomSwitch;
					continue;
				}
				else if (0 == strncmp(token2, "0", 1)) {
					continue;
				}

				// bad value error
				const char *mes = "bad value:";
				const char *mesv[2]; 

				const char *fun = "HP_Compute_Geometry_Keys";
				const char *funv[1];

				mesv[0] = mes;
				mesv[1] = token2;
				funv[0] = fun;

				HC_Report_Error(HEC_SYNTAX, HES_PARSE_STRING, 1, 2, mesv, 1, funv);

				return HP_ERROR_unknown_entity_class;
			}
			else {
				// plain option
				geomTypes |= geomSwitch;
			}
			continue;
		}

		break;
	}

	// error
	const char *mes = "Null type or unknown type";
	const char *mesv[1]; 

	const char *fun = "HP_Compute_Geometry_Keys";
	const char *funv[1];

	mesv[0] = mes;
	funv[0] = fun;

	HC_Report_Error(HEC_SYNTAX, HES_PARSE_STRING, 1, 2, mesv, 1, funv);

	return HP_ERROR_unknown_entity_class;
}

extern DLLEXPORT long HP_Compute_Geometry_Keys ( PK_ENTITY_t tagID, long max_count, HC_KEY *keys, 
													 const char *list ) {
	char token[1025];
	char token2[1025];
	char llist[1025];
	int i;
	unsigned long geomTypes = 0, geomSwitch;

	// convert chars to lower case
	for ( i = 0 ; i < 1024 ; i++ ) {
		if (!list[i]) 
			break;	
		llist[i] = (char)tolower((int)list[i]);
	}
	llist[i] = 0;


	// loop through options
	i = 0;
	while (1) {
		// we are done if no more tokens are available
		if (!HC_Parse_String(llist, ",", i, token)) 
			return HP_Compute_Geometry_Keys_internal(tagID, keys, geomTypes, max_count);

		i++;

		geomSwitch = 0;
		if (strstr(token, "vertices"))
			geomSwitch = HP_GEOMETRY_TYPE_vertices;
		else if (strstr(token, "edges"))
			geomSwitch = HP_GEOMETRY_TYPE_edges;
		else if (strstr(token, "faces"))
			geomSwitch = HP_GEOMETRY_TYPE_faces;
		else if (strstr(token, "bodies"))
			geomSwitch = HP_GEOMETRY_TYPE_bodies;
		else if (strstr(token, "instances"))
			geomSwitch = HP_GEOMETRY_TYPE_instances;
		else if (strstr(token, "assemblies"))
			geomSwitch = HP_GEOMETRY_TYPE_assemblies;

		if (geomSwitch) {
			if (0 == strncmp(token, "no", 2)) {
				continue;		
			}
			else if ( strstr(token, "=") && HC_Parse_String(token, "=", -1, token2) ) {
				if (0 == strncmp(token2, "off", 3)) {
					continue;			
				}
				else if (0 == strncmp(token2, "on", 2)) {
					geomTypes |= geomSwitch;
					continue;
				}
				else if (0 == strncmp(token2, "1", 1)) {
					geomTypes |= geomSwitch;
					continue;
				}
				else if (0 == strncmp(token2, "0", 1)) {
					continue;
				}
					
				// bad value error
				const char *mes = "bad value:";
				const char *mesv[2]; 
	
				const char *fun = "HP_Compute_Geometry_Keys";
				const char *funv[1];

				mesv[0] = mes;
				mesv[1] = token2;
				funv[0] = fun;

				HC_Report_Error(HEC_SYNTAX, HES_PARSE_STRING, 1, 2, mesv, 1, funv);
			
				return HP_ERROR_unknown_entity_class;
			}
			else {
				// plain option
				geomTypes |= geomSwitch;
			}
			continue;
		}
			
		break;
	}
	
	// error
	const char *mes = "Null type or unknown type";
	const char *mesv[1]; 
	
	const char *fun = "HP_Compute_Geometry_Keys";
	const char *funv[1];

	mesv[0] = mes;
	funv[0] = fun;

	HC_Report_Error(HEC_SYNTAX, HES_PARSE_STRING, 1, 2, mesv, 1, funv);

	return HP_ERROR_unknown_entity_class;
}

static void merge_body_faces_in_currently_open_segment(PK_BODY_t* bodies_to_merge, unsigned long num_bodies)
{
	int shell_point_list_len = 0;
	int shell_face_list_len = 0;
	int max_shell_point_list_len = 0;
	int max_shell_face_list_len = 0;
	int total_point_list_len = 0;
	int total_face_list_len = 0;
	int optimized_point_list_len = 0;
	int optimized_face_list_len = 0;
	int total_point_list_offset = 0;
	int total_face_list_offset = 0;
	int i = 0;

	char type[ MAX_TYPE_NAME_LENGTH ];
	HC_KEY key = 0;
	PK_FACE_t face_pointer = 0;
	bool result = false;


	// search for shells.  if the shell belongs to the body being merged, increment the size of the 
	// working arrays.
	HC_Begin_Contents_Search (".", "shells");
	while (HC_Find_Contents (type, &key)) 
	{
		unsigned long i;
		PK_BODY_t face_parent_body;
		face_parent_body = HP_Compute_TagID(key, PK_CLASS_body);
		for (i = 0; i < num_bodies; i++)
		{
			if (face_parent_body == bodies_to_merge[i])
			{
				HC_Show_Shell_Size(key, &shell_point_list_len, &shell_face_list_len );
				total_point_list_len += shell_point_list_len;
				total_face_list_len += shell_face_list_len;
				if (max_shell_point_list_len < shell_point_list_len)
					max_shell_point_list_len = shell_point_list_len;
				if (max_shell_face_list_len < shell_face_list_len)
					max_shell_face_list_len = shell_face_list_len;
				break; // found the body in the array; no need to search more
			}
		}
	}
	HC_End_Contents_Search();
	// search for shells.  if the shell belongs to the body being merged, build the 
	// working arrays.
	if (total_point_list_len && total_face_list_len)
	{
		Point *shell_point_list;
		int *shell_face_list;

		Point *total_point_list;
		Vector *total_normal_list;
		int *total_face_list;

		Point *optimized_point_list;
		int *optimized_face_list;

		
		int *point_mapping_list = 0;
		int *face_mapping_list = 0;
		
		shell_point_list = (Point*) malloc (max_shell_point_list_len * sizeof(Point));
		shell_face_list = (int*) malloc (max_shell_face_list_len * sizeof(int));

		total_point_list = (Point*) malloc (total_point_list_len * sizeof(Point));
		total_normal_list = (Vector*) malloc (total_point_list_len * sizeof(Vector));
		total_face_list = (int*) malloc (total_face_list_len * sizeof(int));

		optimized_point_list = (Point*) malloc (total_point_list_len * sizeof(Point));
		optimized_face_list = (int*) malloc (total_face_list_len * sizeof(int));

	    point_mapping_list = (int *) malloc (total_point_list_len * sizeof (int));

		face_mapping_list = (int *) malloc (total_face_list_len * sizeof (int));

		assert(shell_point_list);
		assert(shell_face_list);

		assert(total_point_list);
		assert(total_normal_list);
		assert(total_face_list);

		assert(optimized_point_list);
		assert(optimized_face_list);

		HC_Begin_Contents_Search (".", "shells");
		while (HC_Find_Contents (type, &key)) 
		{
			int i;
			unsigned long j;
			PK_BODY_t face_parent_body;
			face_parent_body = HP_Compute_TagID(key, PK_CLASS_body);
			for (j = 0; j < num_bodies; j++)
			{
				if (face_parent_body == bodies_to_merge[j])
				{
					// the shell we've found belongs to the body we're merging,
					// absorb it.
					HC_Show_Shell(key, &shell_point_list_len, shell_point_list, &shell_face_list_len, shell_face_list );
					HC_Open_Geometry( key );  // we'll be querying normals soon
					for (i = 0; i < shell_point_list_len; i++)
					{
						total_point_list[total_point_list_offset + i].x = shell_point_list[i].x;
						total_point_list[total_point_list_offset + i].y = shell_point_list[i].y;
						total_point_list[total_point_list_offset + i].z = shell_point_list[i].z;
						HC_Open_Vertex( i );
						HC_Show_Net_Normal( &total_normal_list[total_point_list_offset + i].x,
											&total_normal_list[total_point_list_offset + i].y,
											&total_normal_list[total_point_list_offset + i].z);
						HC_Close_Vertex();
					}
					HC_Close_Geometry();

					for (i = 0; i < shell_face_list_len; )
					{
						int j;
						assert(shell_face_list[i] > 0); // if negative, means subtract this poly from shell.
						// this integration should never result in us seeing that case.

						total_face_list[total_face_list_offset + i] = shell_face_list[i];
						for (j = 1; j <= shell_face_list[i]; j++)
						{
							total_face_list[total_face_list_offset + i + j] = shell_face_list[i+j] + total_point_list_offset;
						}
						i += 1 + shell_face_list[i];
					}

					total_face_list_offset += shell_face_list_len;
					total_point_list_offset += shell_point_list_len;

					// find out the pointer of the FACE entity of the shell we're deleting.
					// when we map the created shell to an entity, we will map it to 
					// the BODY entity
					face_pointer = HP_Compute_TagID(key, PK_CLASS_face);
					// now, delete the found shell and de-map it
					// from this point forward, there will be no mappings between the 
					// HOOPS shells and the Parasolid entities.
					result = g_pMap->DeleteMapping(key);
//GH2000
//					assert(result);
					HC_Delete_By_Key(key);
				}
			}
		}
		HC_End_Contents_Search();

		// list is assembled, now put it together into a single optimized shell.
		HC_Compute_Optimized_Shell(total_point_list_len, total_point_list,
                              (float *)total_normal_list,
                              total_face_list_len, total_face_list,
                              "tolerance = 0% fru, normal tolerance = 1degrees",
                              &optimized_point_list_len,optimized_point_list,
                              &optimized_face_list_len, optimized_face_list,
                              point_mapping_list, face_mapping_list );

		key = HC_KInsert_Shell (optimized_point_list_len, 
								optimized_point_list,
								optimized_face_list_len, 
								optimized_face_list );

		// set the normals
		HC_Open_Geometry(key);
		for( i = 0 ; i < total_point_list_len ; i++ )
		{
			if( point_mapping_list[i] >= 0 )
			{
				HC_Open_Vertex( point_mapping_list[i] );
					HC_Set_Normal( total_normal_list[i].x,
									total_normal_list[i].y,
									total_normal_list[i].z );
				HC_Close_Vertex();
			}
		}
		HC_Close_Geometry();

		
//GH2000		
//		assert(face_pointer != 0);


		if (shell_point_list)
			free(shell_point_list);
		if (shell_face_list)
			free(shell_face_list);

		if (total_point_list)
			free(total_point_list);
		if (total_normal_list)
			free(total_normal_list);
		if (total_face_list)
			free(total_face_list);

		if (optimized_point_list)
			free(optimized_point_list);
		if (optimized_face_list)
			free(optimized_face_list);

		if (point_mapping_list)
			free(point_mapping_list);
		if (face_mapping_list)
			free(face_mapping_list);
	}
	
}

static void merge_body_faces(PK_BODY_t* bodies_to_merge, unsigned long num_bodies)
{
	int result;
	char type[ MAX_TYPE_NAME_LENGTH ];
	bool openSegmentMerged;

	if (g_body_segment_mode)
	{
		assert(num_bodies == 1);
		if (num_bodies != 1)
			return;
		HC_KEY key = 0;
		HP_Compute_Geometry_Keys_internal(bodies_to_merge[0], &key, HP_GEOMETRY_TYPE_bodies, 1);
//GH2000					
		if (!key)
			return;
		assert(key);
		HC_Open_Segment_By_Key(key);
	}
	// find all of the child segments
	if (g_color_segment_mode)
	{
		HC_KEY child;
		HC_Begin_Contents_Search (".","segment");
		result = HC_Find_Contents (type, &child);
		assert(result); // there should be at least one child segment when in color_segment_mode
		HC_Open_Segment_By_Key (child);
	}

	openSegmentMerged = false;
	while (openSegmentMerged == false)
	{
		merge_body_faces_in_currently_open_segment(bodies_to_merge, num_bodies);
		openSegmentMerged = true;
		if (g_color_segment_mode)
		{
			int result;
			HC_KEY child;

			HC_Close_Segment();  // close previously opened color segment

			result = HC_Find_Contents (type, &child);  // find next color segment
			if (result)
			{
				HC_Open_Segment_By_Key (child);  // open next color segment
				openSegmentMerged = false;   // set loop flag true so we'll continue merging
			}
		}
	}

	if (g_color_segment_mode)
	{
		HC_End_Contents_Search();
	}

	if (g_body_segment_mode)
	{
		HC_Close_Segment();
	}
}

extern DLLEXPORT void HP_Internal_Open_Assembly(PK_ASSEMBLY_t assembly, bool tesselate, int level)
{
	Parafile parafile;
	parafile.OpenAssembly(assembly,tesselate,level);
}

extern DLLEXPORT void HP_Internal_Merge_Body_Faces(PK_BODY_t* bodies_to_merge, unsigned long num_Bodies)
{
	merge_body_faces(bodies_to_merge,num_Bodies);
}

extern DLLEXPORT void HP_Render_Entity ( PK_ENTITY_t entity, PK_TRANSF_t view_transf, PK_TRANSF_t topol_transf ) {
	// if the user is rendering an object which already exists in the HOOPS tree,
	// we should automatically delete it here for them so they don't have to.

	// *FIX need to handle case where user renders an individual face,
	// but they have merge_bodies mode ON.  Probably should forbid this (report error here)
	// *TODO determine method of error reporting
 
 	PK_ERROR_code_t error = 0;
	PK_CLASS_t paraClass;

	if (!entity) 
		return;

	error = PK_ENTITY_ask_class(entity, &paraClass);
	if (error) {
		assert(0);
		return;
	}
	
	if (paraClass == PK_CLASS_assembly) {
		Parafile pfile;
		pfile.OpenAssembly(entity, true, 0);
	}
	else {
		if (g_render_faces_mode && view_transf == NULTAG)
			error = PK_TOPOL_render_facet(1, &entity, &topol_transf, view_transf, &g_facetOptions);

		if (error) {
			assert(0);
			return;
		}
		// render the lines (PK_Edges)  Each Parsolid PK_Edge will be mapped
		// to a HOOPS line, polyline, arc, ellipse, circular arc, or elliptical arc
		if (g_render_edges_mode)
			error = PK_TOPOL_render_line(1, &entity, &topol_transf, view_transf, &g_lineOptions);

		if (error) {
			assert(0);
			return;
		}

		
		if (g_merge_faces_mode && !g_merge_bodies_mode) {
			PK_CLASS_t paraClass;

			error = PK_ENTITY_ask_class(entity, &paraClass);

			if (paraClass == PK_CLASS_body)
				merge_body_faces(&entity, 1);
		}
	}
}

extern DLLEXPORT void HP_Render_Entities ( unsigned long count, PK_ENTITY_t * entities, PK_TRANSF_t view_transf, PK_TRANSF_t *topol_transf ) {
	// if the user is rendering an object which already exists in the HOOPS tree,
	// we should automatically delete it here for them so they don't have to.

	// *FIX need to handle case where user renders an individual face,
	// but they have merge_bodies mode ON.  Probably should forbid this (report error here)
	// *TODO determine method of error reporting

	unsigned long i;
 
	if (!count) 
		return;
 
	PK_BODY_t *bodies;
	unsigned long num_bodies = 0;
	bodies = new PK_BODY_t [count];
	if (!bodies)
		return;
	for ( i = 0 ; i < count ; i++ ) {
		HP_Render_Entity(entities[i], view_transf, (topol_transf ? topol_transf[i] : NULTAG));
		
		// we only merge faces in the non hidden line case	
		if (!view_transf) {
			PK_ERROR_code_t error = 0;
			PK_CLASS_t paraClass;
			error = PK_ENTITY_ask_class(entities[i], &paraClass);
			if (error) {
				assert(0);
				return;
			}
			
			if (paraClass == PK_CLASS_body) {
				if (g_merge_bodies_mode)
					bodies[num_bodies++] = entities[i];
			}
		}
	}
	
	if (num_bodies > 0)
		merge_body_faces(bodies, num_bodies);
			
	delete [] bodies;
}           

extern DLLEXPORT bool HP_Update_Entity(PK_ENTITY_t entity,PK_TRANSF_t view_trans=NULTAG, PK_TRANSF_t topol_transf=NULTAG)
{
	// This api right now only works for bodies and 'create body segments' is on
	HC_KEY body_key;
	int count = HP_Compute_Geometry_Keys(entity, 1, &body_key, "bodies");
	bool no_segment = false;
	if( count == 1 )
	{
		char key_type[4096];
		HC_Show_Key_Type(body_key, key_type);
		if (!strstr(key_type, "segment"))
			no_segment = true;
	}
	else
		no_segment = true;

	if( no_segment )
	{
		const char * mes = "Could not determine segment corresponding to given entity."
						   " Please ensure entity is 'body' type and 'create body segments' option is on";
		const char * mesv[1]; 
		const char * fun = "HP_Update_Entity";
		const char * funv[1];
		mesv[0]=mes;
		funv[0]=fun;

		HC_Report_Error(50,309,2,1,mesv,1,funv);
		return false;
	}

	HP_Delete_Entity_Geometry(1, &entity, true);

	HC_Open_Segment_By_Key(body_key);
		HP_Render_Entity(entity, view_trans, topol_transf);
	HC_Close_Segment();

	return true;
}


extern long HP_Compute_Geometry_Keys_internal ( PK_ENTITY_t tagID, HC_KEY *keys, unsigned long geomTypes, 
												    long count ) {
	PK_CLASS_t		paraClass;
	PK_ERROR_code_t error = 0;
	PK_EDGE_t		*edges = NULL;
	PK_VERTEX_t		*vertices = NULL;
	PK_FACE_t		*faces = NULL;
	PK_ENTITY_t		*entities = NULL;
	PK_GROUP_t		*groups = NULL;
	PK_BODY_t		*bodies = NULL;
	PK_ASSEMBLY_t	*assemblies = NULL;
	PK_SHELL_t		*shells = NULL;
	int				num_entities = 0;
	long			num_keys = 0;
	long			temp_key_count = 0;
	int				i = 0;

	if (count <= 0)	//<0 can actually happen (as far as I understand the code) if the maximum size
		return 0;	//of the key array is reached (realloc is necessary)
					// don't overshoot given array
 	
	error = PK_ENTITY_ask_class(tagID, &paraClass);
	
	if (error) {

		//	ALTERED 5/12/99 rlw return HP_ERROR_unable_to_determine_entity_class;

		
		// modify behavior so that delete_entity_geometry can work
		// even after geometry has been deleted from Parasolid.
		// The maximum number of keys that should be mapped to a particular
		// tagID is 2, or the same as the max number of keys mapped to a
		// particular Parasolid edge.  So, we'll proceed by just returning
		// those 0 or 1 or 2 keys mapped to this particular tagID regardless
		// of its (now unknowable) class and hope things work out for the best.
		// in the case of HP_Delete_Entity_Geometry, it should work fine for edges
		// and faces, as well as bodies provided body_segment_mode is on.
		// if the last proviso is not true, then this fn will return nothing
		// and HP_Delete_Entity_Geometry will delete nothing for that
		// particular body.

		paraClass = PK_CLASS_edge;
		geomTypes = HP_GEOMETRY_TYPE_edges;
	}

	switch (paraClass) {
	case PK_CLASS_instance:
	case PK_CLASS_assembly:
		if (geomTypes & HP_GEOMETRY_TYPE_assemblies || geomTypes & HP_GEOMETRY_TYPE_instances)
			num_keys = g_pMap->FindMapping(tagID, keys, count);
		return num_keys;
	case PK_CLASS_attdef:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_attrib:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_bb:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_blendsf:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_body:
		if (geomTypes & HP_GEOMETRY_TYPE_vertices) {
			error = PK_BODY_ask_vertices(tagID, &num_entities, &vertices);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Keys_internal(vertices[i], &keys[num_keys], geomTypes, count-num_keys);
				if (temp_key_count < 0)
					return temp_key_count; // return error code
				num_keys += temp_key_count;
			}
			if (vertices) {
				PK_MEMORY_free(vertices);
				vertices = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_edges) {
			// must actually get the geometry here to check for circles
			error = PK_BODY_ask_edges(tagID, &num_entities, &edges);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Keys_internal(edges[i], &keys[num_keys], geomTypes, count-num_keys);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (edges) {
				PK_MEMORY_free(edges);
				edges = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_faces) {
			// passing null as last arg simply returns count; no allocation is performed
			error = PK_BODY_ask_faces(tagID, &num_entities, &faces);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Keys_internal(faces[i], &keys[num_keys], geomTypes, count-num_keys);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (faces) {
				PK_MEMORY_free(faces);
				faces = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_bodies) {
			temp_key_count = g_pMap->FindMapping(tagID, &keys[num_keys], count-num_keys);
			if (temp_key_count < 0)
				return temp_key_count;  // return error code
			num_keys += temp_key_count;			 
		}
		return num_keys;
	case PK_CLASS_bsurf:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_class:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_cone:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_bcurve:
	case PK_CLASS_circle:
	case PK_CLASS_curve:
	case PK_CLASS_ellipse:
	case PK_CLASS_fcurve:
	case PK_CLASS_icurve:
	case PK_CLASS_line:
	case PK_CLASS_spcurve:
	case PK_CLASS_trcurve: 
		if (geomTypes & HP_GEOMETRY_TYPE_edges) {
			error = PK_CURVE_ask_edges(tagID, &num_entities, &edges);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Keys_internal(edges[i], &keys[num_keys], geomTypes, count-num_keys);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (edges) {
				PK_MEMORY_free(edges);
				edges = NULL;
			}
		}
		return num_keys;
	case PK_CLASS_cyl:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_edge:
		if (geomTypes & HP_GEOMETRY_TYPE_vertices) {
			num_entities = 2;
			PK_VERTEX_t vertices[2];
			error = PK_EDGE_ask_vertices(tagID, vertices);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Keys_internal(vertices[i], &keys[num_keys], geomTypes, count-num_keys);
				if (temp_key_count < 0)
					return temp_key_count; // return error code
				num_keys += temp_key_count;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_edges) {
			temp_key_count = g_pMap->FindMapping(tagID, &keys[num_keys], count-num_keys);
			if (temp_key_count < 0)
				return temp_key_count;  // return error code
			num_keys += temp_key_count;
		}
		return num_keys;
	case PK_CLASS_entity:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_error:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_face:
		if (geomTypes & HP_GEOMETRY_TYPE_vertices) {
			error = PK_FACE_ask_vertices(tagID, &num_entities, &vertices);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Keys_internal(vertices[i], &keys[num_keys], geomTypes, count-num_keys);
				if (temp_key_count < 0)
					return temp_key_count; // return error code
				num_keys += temp_key_count;
			}
			if (vertices) {
				PK_MEMORY_free(vertices);
				vertices = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_edges) {
			// must actually get the geometry here to check for circles
			error = PK_FACE_ask_edges(tagID, &num_entities, &edges);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Keys_internal(edges[i], &keys[num_keys], geomTypes, count-num_keys);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (edges) {
				PK_MEMORY_free(edges);
				edges = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_faces) {
			temp_key_count = g_pMap->FindMapping(tagID, &keys[num_keys], count-num_keys);
			if (temp_key_count < 0)
				return temp_key_count;  // return error code
			num_keys += temp_key_count;
		}
		return num_keys;
	case PK_CLASS_fin:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_fsurf:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_geom:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_group: 
		error = PK_GROUP_ask_entities(tagID, &num_entities, &entities);
		for ( i = 0 ; i < num_entities ; i++ ) {
			temp_key_count = HP_Compute_Geometry_Keys_internal(entities[i], &keys[num_keys], geomTypes, count-num_keys);
			// this group may contain non-mappable entities.  HP_Compute_Geometry_Key_Count_internal
			// will return negative values as counts (error codes) in that case.  We don't want
			// to screw up the entity count by adding a negative value to the count,
			// nor throw an error in this case.  So just check
			// the value here.
			if (temp_key_count > 0)
				num_keys += temp_key_count;
			else
			{
				if ( (temp_key_count == HP_ERROR_non_mappable_entity_class) ||
					 (temp_key_count == HP_ERROR_unknown_entity_class) ) {
					// ignore this
				}
				else {
					// other errors shouldn't happen
					assert(0);
					return temp_key_count; // which contains error code 
				}
			}
		}
		if (entities) {
			PK_MEMORY_free(entities);
			entities = NULL;
		}
		return num_keys;
	case PK_CLASS_loop:
		return HP_ERROR_non_mappable_entity_class;	
	case PK_CLASS_mark:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_memory:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_offset:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_part:
		error = PK_PART_ask_groups(tagID, &num_entities, &groups);
		for ( i = 0 ; i < num_entities ; i++ ) {
			temp_key_count = HP_Compute_Geometry_Keys_internal(groups[i], &keys[num_keys], geomTypes, count-num_keys);
			if (temp_key_count < 0)
				return temp_key_count;  // return error code
			num_keys += temp_key_count;
		}
		if (groups) {
			PK_MEMORY_free(groups);
			groups = NULL;
		}
		return num_keys;
	case PK_CLASS_partition:
		if (geomTypes & HP_GEOMETRY_TYPE_assemblies) {
			error = PK_PARTITION_ask_assemblies(tagID, &num_entities, &assemblies);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Keys_internal(assemblies[i], &keys[num_keys], geomTypes, count-num_keys);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (assemblies) {
				PK_MEMORY_free(assemblies);
				assemblies = NULL;
			}
		}
		if (geomTypes & HP_GEOMETRY_TYPE_bodies) {
			error = PK_PARTITION_ask_bodies(tagID, &num_entities, &bodies);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Keys_internal(bodies[i], &keys[num_keys], geomTypes, count-num_keys);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (bodies) {
				PK_MEMORY_free(bodies);
				bodies = NULL;
			}
		}
		return num_keys;
	case PK_CLASS_plane:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_pmark:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_point:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_region:
		if (geomTypes & HP_GEOMETRY_TYPE_faces) {
			error = PK_REGION_ask_shells(tagID, &num_entities, &shells);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Keys_internal(shells[i], &keys[num_keys], geomTypes, count-num_keys);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (shells) {
				PK_MEMORY_free(shells);
				shells = NULL;
			}
		}
		return num_keys;
	case PK_CLASS_session:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_shell:
		if (geomTypes & HP_GEOMETRY_TYPE_faces) {
			error = PK_SHELL_ask_oriented_faces(tagID, &num_entities, &faces, 0);
			
			// each face can appear in the list up to twice; we need to eliminate the counts for the repeats.
			temp_key_count = num_entities;
			for ( i = 0 ; i < num_entities ; i++ ) {
				int j;
				for ( j = i + 1 ; j < num_entities ; j++ ) {
					if (faces[i] == faces[j]) {
						temp_key_count--;
						break; // repeats only happen once; stop looking for repeats of faces[i].
					}
				}
				if (j != num_entities) {
					// no match was found, DO get the key corresponding to this face
					if (count - num_keys > 0) {
						temp_key_count = HP_Compute_Geometry_Keys_internal(faces[i], &keys[num_keys], geomTypes, count-num_keys);
						if (temp_key_count < 0)
							return temp_key_count;  // return error code
						num_keys += temp_key_count;
					}
				}
			}
			if (faces) {
				PK_MEMORY_free(faces);
				faces = NULL;
			}
			num_keys = temp_key_count;
		}
		if (geomTypes & HP_GEOMETRY_TYPE_edges) {
			error = PK_SHELL_ask_wireframe_edges(tagID, &num_entities, &edges);
			for ( i = 0 ; i < num_entities ; i++ ) {
				temp_key_count = HP_Compute_Geometry_Keys_internal(edges[i], &keys[num_keys], geomTypes, count-num_keys);
				if (temp_key_count < 0)
					return temp_key_count;  // return error code
				num_keys += temp_key_count;
			}
			if (edges) {
				PK_MEMORY_free(edges);
				edges = NULL;
			}
		}
		return num_keys;
	case PK_CLASS_sphere:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_spun:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_surf:
		return HP_ERROR_not_implemented;
	case PK_CLASS_swept: 
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_topol:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_torus:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_transf:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_vector:
		return HP_ERROR_non_mappable_entity_class;
	case PK_CLASS_vertex: 
		if (geomTypes & HP_GEOMETRY_TYPE_vertices) {
			temp_key_count = g_pMap->FindMapping(tagID, &keys[num_keys], count-num_keys);
			if (temp_key_count < 0)
				return temp_key_count;  // return error code
			num_keys += temp_key_count;
		}
		return num_keys;
	default:
		return HP_ERROR_unknown_entity_class;

	}
	assert(0);
	return HP_ERROR_unknown_entity_class;

}

extern DLLEXPORT const __wchar_t * HP_Get_Schema_Path()
{
	return (g_schema_path);
}

extern DLLEXPORT void HP_Set_Schema_Path(const __wchar_t *schema_path)
{
	g_schema_path[0] = L'\0'; // initialize the schema path

	if (schema_path)
	{
		wcsncpy(g_schema_path, schema_path, MAX_SCHEMA_PATH_LENGTH - 1);
	}
}

extern DLLEXPORT void HP_Set_Schema_Path(const char *schema_path)
{
	HP_Set_Schema_Path(H_UNICODE_TEXT(schema_path));
}

extern DLLEXPORT unsigned char  HP_Get_Hash_Level() 
{
	return (g_hash_level);
}

extern DLLEXPORT void HP_Set_Hash_Level(unsigned char level) 
{
	g_hash_level=level;
}

extern DLLEXPORT bool HP_Get_Instances_To_Bodies() 
{
	return (g_instances_to_bodies);
}

extern DLLEXPORT void HP_Set_Instances_To_Bodies(bool flatten) 
{
	g_instances_to_bodies =flatten;
}

 
extern DLLEXPORT int HP_Check_Consistency() 
{
	return(g_pMap->CheckConsistency());
}

extern DLLEXPORT bool HP_Associate_Key_To_Entity(PK_ENTITY_t entity, HC_KEY key) 
{
	PK_LOGICAL_t is_entity;
	PK_ERROR_t error = PK_ENTITY_is(entity, &is_entity);
	(void)error; //for warning
	assert(!error);
	if (is_entity) // this entity has not been deleted
	{
		HC_KEY keys[10000];
		int count = g_pMap->FindMapping(entity,keys,10000);
		bool mapping_exists = false;
		for (int i=0;i < count; i++)
		{
			if (keys[i] == key)
			{
				mapping_exists = true;
				break;
			}
		}
		if (!mapping_exists)
		{
			g_pMap->AddMapping(key, entity);
			return true;
		}
	}
	return false;
}
