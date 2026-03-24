
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

#include "kernel_interface.h"
#include "parasolid_kernel.h"
#include "frustrum_tokens.h"
#include "hc.h"
#include "utf_utils.h"
#include "parafile.h"
#include "parafrustdefs.h"
#include "hp_map.h"
#include "hp_bridge_internal.h"
#include "hp_bridge.h"

extern PK_TOPOL_render_facet_o_t g_facetOptions;
extern PK_TOPOL_render_line_o_t g_lineOptions;
extern __wchar_t g_schema_path[MAX_SCHEMA_PATH_LENGTH];

static bool errorFindingSchemaFiles = false;

extern HP_Map* g_pMap; 
  
Parafile::Parafile()
{
}

Parafile::~Parafile()
{
}

bool Parafile::FindSchemaFile( char * schemaDir, char * filename )
{
	return FindSchemaFile((__wchar_t*)H_WCS(schemaDir).encodedText(), (__wchar_t*)H_WCS(filename).encodedText());
}

bool Parafile::FindSchemaFile( __wchar_t * schemaDir, __wchar_t * filename )
{
    FILE *fp;
	__wchar_t file[1024];
	int schemaDirStringLength;

	schemaDirStringLength = (int) wcslen(schemaDir);

	wcscpy(file, schemaDir);

	if (file[schemaDirStringLength-1] != L'/')
	{
		file[schemaDirStringLength] = L'/';
		schemaDirStringLength++;
		file[schemaDirStringLength] = L'\0';
	}


	wcscpy(file+schemaDirStringLength, filename);

	wcscpy(file+schemaDirStringLength+wcslen(filename), L".sch_txt");

	// *FIX, do we have to handle schema files with suffixes other than sch_txt
	// *FIX also, we may have to deal with case-sensitivity under UNIX.

	wcscpy(filename, file);

	fp = wfopen(filename, L"r");
	if (fp)
	{
		fclose(fp);
		return true;
	}
	else
		return false;


}


HC_KEY Parafile::OpenAssembly(PK_ASSEMBLY_t assem, bool tesselate, int level)
{
  	
	int ni;
 				
	PK_INSTANCE_t *instances;
 	PK_ASSEMBLY_ask_instances(assem, &ni, &instances);
	
	if (level > 0) {
		HC_KOpen_Segment("instances"); 
			HC_Set_Visibility("off");
	}

	HC_KEY assembly_key = g_pMap->FindMapping(assem);
	if (assembly_key != 0) {
		g_pMap->DeleteMapping(assembly_key, assem);
	}
	assembly_key = HC_KCreate_Segment(""); 
	g_pMap->AddMapping(assembly_key, assem);
	HC_Open_Segment_By_Key(assembly_key);
	{	
		for ( int j = 0 ; j < ni ; j++ ) {
			PK_ENTITY_t entity;
			PK_TRANSF_t transf;
			
			PK_INSTANCE_sf_t in_sf;
			PK_INSTANCE_ask(instances[j],&in_sf);
			entity = in_sf.part;
			transf = in_sf.transf;
			PK_CLASS_t paraClass;
			PK_ENTITY_ask_class(entity, &paraClass);

			HC_KEY instance_key;
			instance_key = g_pMap->FindMapping(instances[j]);
			if (instance_key != 0) {
				g_pMap->DeleteMapping(instance_key, instances[j]);
			}
			
			PK_TRANSF_sf_t tf;
			PK_TRANSF_ask(transf, &tf);
			float hm[4][4];
			for (int xx=0;xx<4;xx++)
			{
				for (int yy=0;yy<4;yy++)
				{
					hm[xx][yy]=(float)tf.matrix[yy][xx];
				}
			}
			
			if (tesselate)
			{
				PK_ENTITY_ask_class(entity, &paraClass);				
				HC_KEY entity_key = g_pMap->FindMapping(entity);
				if (!entity_key)
				{	
					if (paraClass == PK_CLASS_body)
					{
//						HC_Open_Segment("?include library/instanced entities"); 
						HC_Open_Segment("instances");
							HC_Set_Visibility( "off" );
							HC_Set_Heuristics( "no backplane culls, exclude bounding");
							HC_Open_Segment("");
								HP_Render_Entities(1, &entity);
							HC_Close_Segment(); 
						HC_Close_Segment(); 
						entity_key = g_pMap->FindMapping(entity);
					}
					else
						entity_key = OpenAssembly(entity, tesselate, level + 1);
				}
				if (paraClass == PK_CLASS_body)
					entity_key = HC_KShow_Owner_By_Key(entity_key);

				HC_Open_Segment("model");
					instance_key = HC_KOpen_Segment(""); {
						if ( transf != 0 )
							HC_Set_Modelling_Matrix((float *)hm);
						HC_Include_Segment_By_Key(entity_key);
					} HC_Close_Segment(); 
				HC_Close_Segment();

				g_pMap->AddMapping(instance_key, instances[j]);
			}
		}
	} HC_Close_Segment();

	if (level > 0)
		HC_Close_Segment();
 
	PK_MEMORY_free(instances);
	return assembly_key;				
}

PK_ERROR_code_t Parafile::OpenFileFlat(char *pathName, PK_PARTITION_t file_partition, int* returned_num_parts, PK_PART_t** returned_parts, const PK_PART_receive_o_t *options, bool tesselate)
{
	return OpenFileFlat((__wchar_t *)H_UNICODE_TEXT(pathName), file_partition, returned_num_parts, returned_parts, options, tesselate);
}

PK_ERROR_code_t Parafile::OpenFileFlat(__wchar_t *pathName, PK_PARTITION_t file_partition, int* returned_num_parts, PK_PART_t** returned_parts, const PK_PART_receive_o_t *options, bool tesselate)
{
	PK_PART_t* parts = 0;
	int num_parts = 0;
	
	PK_ERROR_code_t error = 0;
	int i = 0;
	HC_KEY keys[40000];
	long numkeys = 0;
	int max_num_parts = 0;
	PK_PART_t* total_parts = 0;
	int total_parts_index = 0;

	// set default return value
	if (returned_num_parts)
		*returned_num_parts = 0;


	PK_PART_receive_o_t stack_options;

	if (!options)
	{
		options = &stack_options;
		PK_PART_receive_o_m( stack_options );
		stack_options.transmit_format = PK_transmit_format_text_c;
	}

	// create a new partition if a valid one was not given

	if (file_partition == PK_PARTITION_null)
		error = PK_PARTITION_create_empty(&file_partition);
	
	if (error) return error;

	PK_PARTITION_set_current( file_partition);

	PK_PARTITION_t tempPartition;
	tempPartition = PK_PARTITION_null;
	PK_PARTITION_create_empty( &tempPartition );
	PK_PARTITION_set_current( tempPartition);
	error = PK_PART_receive_u((unsigned short const*)H_UTF16(pathName).encodedText(), options, &num_parts, &parts );


	max_num_parts = num_parts;


	for (i=0; i < num_parts; i++)
	{
		PK_CLASS_t partClass;

		PK_ENTITY_ask_class( parts[ i ], &partClass );
		if (partClass == PK_CLASS_assembly)
		{
			PK_ASSEMBLY_t ha, assem;
			int ifail;

			PK_PARTITION_set_current( tempPartition);

			ha = parts[ i ];
			LEVASS( &ha, &assem, &ifail );
			if (ifail == KI_no_errors)
			{
				int getins = TYTOIN, ni, instances, One = 1;
				PK_INSTANCE_t* iarray;
				IDCOEN( &assem, &getins, &instances, &ni, &ifail );

				// ni is the number of instances; increase the size of the returned parts array.
				if (ni > 0)
				{
					max_num_parts += ni - 1; // subtract 1 to account for the already allocated slot for the assembly tag, which will not be returned.
					if (!total_parts)
					{
						int j;
						assert(total_parts_index == i);
						PK_MEMORY_alloc( sizeof( PK_PART_t) * (max_num_parts), (void**)&total_parts );
						for (j = 0; j < total_parts_index; j++)
						{
							total_parts[j] = parts[j];
						}
					}
					else  
					{
						PK_PART_t* temp_parts = 0;
						int j;

						PK_MEMORY_alloc( sizeof( PK_PART_t) * (max_num_parts), (void**)&temp_parts );

						for (j = 0; j < total_parts_index; j++)
						{
							temp_parts[j] = total_parts[j];
						}
												
						PK_MEMORY_free(total_parts);
						total_parts = temp_parts;
						temp_parts = 0;
					}
				}



				PK_MEMORY_alloc( sizeof( PK_INSTANCE_t ) * ni, (void**)&iarray );
				GTTGLI( &instances, &One, &ni, iarray, &ifail );
				DELIST( &instances, &ifail );
				for (int j=0; j<ni; j++)
				{
					PK_BODY_t copy, body;
					PK_TRANSF_t transf;
					int list;
					int nitems;
					int getbody = TYTOBY, gettransf = TYGETF;
					int nrepl;
					PK_GEOM_t* geoms;
					PK_LOGICAL_t* exact;
				
					PK_PARTITION_set_current( tempPartition);
					IDCOEN( iarray + j, &getbody, &list, &nitems, &ifail );
					assert( nitems == 1);
					GTTGLI( &list, &One, &One, &body, &ifail );
					DELIST( &list, &ifail );
					IDCOEN( iarray + j, &gettransf, &list, &nitems, &ifail );
					assert( nitems == 1);
					GTTGLI( &list, &One, &One, &transf, &ifail );
					DELIST( &list, &ifail );

					PK_PARTITION_set_current( file_partition);
					PK_ENTITY_copy( body, &copy );
					PK_BODY_transform( copy, transf, 1.0e-6, &nrepl, &geoms, &exact );
					PK_PARTITION_set_current( tempPartition);
				//	error = PK_TOPOL_render_facet(1, &copy, NULTAG, NULTAG, &g_facetOptions);
				//	error = PK_TOPOL_render_line(1, &copy, NULTAG, NULTAG, &g_lineOptions);
					if (tesselate)
					{
						HP_Render_Entities(1, &copy);
						numkeys = HP_Compute_Geometry_Keys_internal(copy, keys, 0xff, 40000);
						assert(numkeys >= 0);
					}

					
					total_parts[total_parts_index] = copy;
					total_parts_index++;
			

					if (nrepl > 0)
					{
						PK_MEMORY_free( geoms );
						PK_MEMORY_free( exact );
					}
				}
				// we delete everything in the temp partition
				int tn;
				PK_PART_t* tp;
				PK_PARTITION_t tcp;
				PK_SESSION_ask_curr_partition( &tcp );
				PK_PARTITION_ask_assemblies( tcp, &tn, &tp );
				if (tn > 0)
				{
					PK_ENTITY_delete( tn, tp );
					PK_MEMORY_free( tp );
				}
				PK_PARTITION_ask_bodies( tcp, &tn, &tp );
				if (tn > 0)
				{
					PK_ENTITY_delete( tn, tp );
					PK_MEMORY_free( tp );
				}
				PK_MEMORY_free( iarray );
			}
		}
		else
		{
			PK_PARTITION_t curr;
			PK_PARTITION_set_current( file_partition);
			PK_SESSION_ask_curr_partition( &curr );
			PK_BODY_change_partition( parts[ i ], curr );
			if (tesselate)
				HP_Render_Entities(1, &(parts[i]));
			
//			error = PK_TOPOL_render_facet(1, &(parts[i]), NULTAG, NULTAG, &g_facetOptions);
//			error = PK_TOPOL_render_line(1, &(parts[i]), NULTAG, NULTAG, &g_lineOptions);
			if (total_parts)
				total_parts[total_parts_index] = parts[i];
			total_parts_index++; // maintain the proper index in the total_parts array
			// even if it's not yet allocated in case an assembly is encountered later in the
			// parts array which would trigger the allocation of a "total_parts" array.
		}

	}

	if (total_parts)
	{
		// move the "total_parts" array into the "parts" variable (free "parts" first) so that
		// the next bunch of code works unconditionally referring to the "parts" array
		PK_MEMORY_free(parts);
		parts = total_parts;
		total_parts = 0;
	}

	if (returned_parts)
	{
		// user want us to return the array of parts
		*returned_parts = parts;
		assert(returned_num_parts);
		if (returned_num_parts)
			*returned_num_parts = max_num_parts;
	}
	else if (parts)
	{
		PK_MEMORY_free( parts );
		parts = 0;
		num_parts = 0;
	}

	

	if (errorFindingSchemaFiles == true)
		return PK_ERROR_schema_access_error;

	return error;
}

PK_ERROR_code_t Parafile::OpenFile(char *pathName, PK_PARTITION_t file_partition, int* returned_num_parts, PK_PART_t** returned_parts, const PK_PART_receive_o_t *options, bool tesselate)
{
	return OpenFile((__wchar_t *)H_UNICODE_TEXT(pathName), file_partition, returned_num_parts, returned_parts, options, tesselate);
}

PK_ERROR_code_t Parafile::OpenFile(__wchar_t *pathName, PK_PARTITION_t file_partition, int* returned_num_parts, PK_PART_t** returned_parts, const PK_PART_receive_o_t *options, bool tesselate)
{
	PK_PART_t* parts = NULL;
	int num_parts = 0;
	
	PK_ERROR_code_t error = 0;
	int i = 0;
	int max_num_parts = 0;
	PK_PART_t* total_parts = NULL;
	int total_parts_index = 0;

	// set default return value
	if (returned_num_parts)
		*returned_num_parts = 0;


	PK_PART_receive_o_t stack_options;

	if (!options)
	{
		options = &stack_options;
		PK_PART_receive_o_m( stack_options );
		stack_options.transmit_format = PK_transmit_format_text_c;
	}

	// create a new partition if a valid one was not given

	if (file_partition == PK_PARTITION_null)
		error = PK_PARTITION_create_empty(&file_partition);
	
	if (error) return error;

	PK_PARTITION_set_current( file_partition);
 
	error = PK_PART_receive_u((unsigned short const*)H_UTF16(pathName).encodedText(), options, &num_parts, &parts );

	max_num_parts = num_parts;

	for (i=0; i < num_parts; i++)
	{
		PK_CLASS_t partClass;

		PK_ENTITY_ask_class( parts[ i ], &partClass );
		if (partClass == PK_CLASS_assembly)
		{
			PK_PARTITION_set_current( file_partition);
			OpenAssembly(parts[i],tesselate,0);
		}
		else
		{
			PK_PARTITION_t curr;
			PK_PARTITION_set_current( file_partition);
			PK_SESSION_ask_curr_partition( &curr );
			PK_BODY_change_partition( parts[ i ], curr );
			if (tesselate)
				HP_Render_Entities(1, &(parts[i]));
			
 			if (total_parts)
				total_parts[total_parts_index] = parts[i];
			total_parts_index++; // maintain the proper index in the total_parts array
			// even if it's not yet allocated in case an assembly is encountered later in the
			// parts array which would trigger the allocation of a "total_parts" array.
		}
	}

	if (total_parts)
	{
		// move the "total_parts" array into the "parts" variable (free "parts" first) so that
		// the next bunch of code works unconditionally referring to the "parts" array
		PK_MEMORY_free(parts);
		parts = total_parts;
		total_parts = NULL;
	}

	if (returned_parts)
	{
		// user want us to return the array of parts
		*returned_parts = parts;
		assert(returned_num_parts);
		if (returned_num_parts)
			*returned_num_parts = max_num_parts;
	}
	else if (parts)
	{
		PK_MEMORY_free( parts );
		parts = NULL;
		num_parts = 0;
	}

	

	if (errorFindingSchemaFiles == true)
		return PK_ERROR_schema_access_error;

	return error;
}



