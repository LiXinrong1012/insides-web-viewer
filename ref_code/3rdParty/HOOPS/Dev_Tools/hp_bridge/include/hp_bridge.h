#ifndef __HP_BRIDGE_H_
#define __HP_BRIDGE_H_

#include "hc.h"
#include "parafrustdefs.h"

#define HP_ERROR_key_out_of_range					-1
#define HP_ERROR_non_circle_key_out_of_range		-2
#define HP_ERROR_key_does_not_exist					-3
#define HP_ERROR_unable_to_determine_entity_class	-4
#define HP_ERROR_non_mappable_entity_class			-5
#define HP_ERROR_unknown_entity_class				-6
#define HP_ERROR_not_implemented					-7
#define HP_ERROR_hoops_key_maps_to_invalid_entity_class -8
#define HP_ERROR_incorrect_face_tag_mapping			-9

#ifndef _MSC_VER
#define __wchar_t wchar_t
#endif

extern void HP_Init(const char* pathToSchemaFiles, PK_LOGICAL_t useBulletinBoard, bool bUnicodeFilenames=true);

extern void HP_Update(void);
extern void HP_Close(void);

extern PK_ERROR_code_t HP_Read_Xmt_File(const char* filename, PK_PARTITION_t file_partition, int* num_parts, PK_PART_t** parts, const PK_PART_receive_o_t* options, bool tesselate=true);
extern PK_ERROR_code_t HP_Write_Xmt_File(const char* filename, int num_parts, const PK_PART_t* parts, const PK_PART_transmit_o_t* options);

#ifdef _MSC_VER

extern void HP_Init(const __wchar_t* pathToSchemaFiles, PK_LOGICAL_t useBulletinBoard, bool bUnicodeFilenames=true);
extern PK_ERROR_code_t HP_Read_Xmt_File(const __wchar_t * filename, PK_PARTITION_t file_partition, int* num_parts, PK_PART_t** parts, const PK_PART_receive_o_t* options, bool tesselate=true);
extern PK_ERROR_code_t HP_Write_Xmt_File(const __wchar_t * filename, int num_parts, const PK_PART_t* parts, const PK_PART_transmit_o_t* options);

#else

extern void HP_Init(const wchar_t* pathToSchemaFiles, PK_LOGICAL_t useBulletinBoard, bool bUnicodeFilenames=true);
extern PK_ERROR_code_t HP_Read_Xmt_File(const wchar_t * filename, PK_PARTITION_t file_partition, int* num_parts, PK_PART_t** parts, const PK_PART_receive_o_t* options, bool tesselate=true);
extern PK_ERROR_code_t HP_Write_Xmt_File(const wchar_t * filename, int num_parts, const PK_PART_t* parts, const PK_PART_transmit_o_t* options);

#endif

extern void HP_Delete_Entity_Geometry(unsigned long count, PK_ENTITY_t* entities, bool PreserveSegments=false);

//GH99
extern void HP_Render_Entities(unsigned long count, PK_ENTITY_t* entities, PK_TRANSF_t view_transf=NULTAG, PK_TRANSF_t* topol_transf=0);

extern void HP_Render_Entity(PK_ENTITY_t entity, PK_TRANSF_t trans=NULTAG, PK_TRANSF_t topol_transf=NULTAG);

/*!
  Updates the given entity by re-tessellating it. The HOOPS segment hierarchy will be retained.
  This api requires following conditions to succeed
  1. entity to be updated should be of PK_BODY_t class
  2. entity should have already been rendered first by calling HP_Render_Entity api
  3. 'create body segments' rendering option should be on
  \param entity The entity to be updated (should be of PK_BODY_t type)
  \param trans	View transformation (default is NULTAG)
  \param topol_transf Entity transformation (default is NULTAG)
  \return bool true if succeeds
*/
extern bool HP_Update_Entity(PK_ENTITY_t entity, PK_TRANSF_t view_trans=NULTAG, PK_TRANSF_t topol_transf=NULTAG);

extern void HP_Show_Tessellation_Options(PK_TOPOL_render_line_o_t* line_Options, PK_TOPOL_render_facet_go_o_t* go_options, PK_TOPOL_facet_mesh_o_t* generation_settings);

extern void HP_Set_Tessellation_Options(PK_TOPOL_render_line_o_t* line_Options, PK_TOPOL_render_facet_go_o_t* go_options, PK_TOPOL_facet_mesh_o_t* generation_settings);

extern long HP_Compute_Geometry_Keys(PK_ENTITY_t tagID, long max_count, HC_KEY* keys, const char* list);

extern long HP_Compute_Geometry_Key_Count(PK_ENTITY_t tagID, char* list);
extern PK_ENTITY_t HP_Compute_TagID(HC_KEY key, PK_CLASS_t paraClass);
extern void HP_Set_Rendering_Options(const char* list);
extern void HP_Show_Rendering_Options(char* list);
extern void HP_Show_One_Rendering_Option(const char* type, char* value);
extern int HP_CheckConsistency(void);
extern const __wchar_t * HP_Get_Schema_Path(void);
extern void HP_Set_Schema_Path(const char* schema_path);
extern unsigned char HP_Get_Hash_Level(void);
extern void HP_Set_Hash_Level(unsigned char level);
extern void HP_Set_Instances_To_Bodies(bool flatten);
extern bool HP_Get_Instances_To_Bodies(void);
extern int HP_Check_Consistency(void);
extern bool HP_Associate_Key_To_Entity(PK_ENTITY_t entity, HC_KEY key);
extern void HP_Compute_Selected_Entity_List(PK_ENTITY_t** entities, int* numentities);

#endif
