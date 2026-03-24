/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use. 
 *
 * $Id: obf_tmp.txt 1.436.2.1 2011-01-05 00:35:05 boni Exp $
 */
 
#ifndef HC_PROTO_DEFINED

HC_INTERFACE void HC_CDECL HC_Abort_Program (char const *message);
HC_INTERFACE void HC_CDECL HC_Append_Modelling_Matrix (float const Array[]);
HC_INTERFACE void HC_CDECL HC_Append_Texture_Matrix (float const Array[]);
HC_INTERFACE void HC_CDECL HC_Begin_Alias_Search (void);
HC_INTERFACE void HC_CDECL HC_Begin_Callback_Name_Search (void);
HC_INTERFACE void HC_CDECL HC_Begin_Color_Name_Search (void);
HC_INTERFACE void HC_CDECL HC_Begin_Contents_Search (char const *segment, char const *filter);
HC_INTERFACE void HC_CDECL HC_Begin_Font_Search (char const *display, char const *filter);
HC_INTERFACE void HC_CDECL HC_Begin_Glyph_Search (void);
HC_INTERFACE void HC_CDECL HC_Begin_Line_Style_Search (void);
HC_INTERFACE void HC_CDECL HC_Begin_Open_Segment_Search (void);
HC_INTERFACE void HC_CDECL HC_Begin_Segment_Search (char const *segspec);
HC_INTERFACE void HC_CDECL HC_Begin_Shader_Search (void);
HC_INTERFACE void HC_CDECL HC_Begin_Texture_Search (void);
HC_INTERFACE void HC_CDECL HC_Begin_Local_Texture_Search (void);
HC_INTERFACE void HC_CDECL HC_Bring_To_Front (char const *segment);
HC_INTERFACE void HC_CDECL HC_Bring_To_Front_By_Key (Key key);
HC_INTERFACE void HC_CDECL HC_Close_Edge (void);
HC_INTERFACE void HC_CDECL HC_Close_Face (void);
HC_INTERFACE void HC_CDECL HC_Close_Geometry (void);
HC_INTERFACE void HC_CDECL HC_Close_LOD (void);
HC_INTERFACE void HC_CDECL HC_Close_Region (void);
HC_INTERFACE void HC_CDECL HC_Close_Segment (void);
HC_INTERFACE void HC_CDECL HC_Close_Vertex (void);
HC_INTERFACE bool HC_CDECL HC_Compute_Circumcuboid (char const *segment, Point *min, Point *max);
HC_INTERFACE bool HC_CDECL HC_Compute_Circumcuboid_By_Key (Key key, Point *min, Point *max);
HC_INTERFACE bool HC_CDECL HC_Compute_Circumsphere (char const *segment, Point *center, float *radius);
HC_INTERFACE bool HC_CDECL HC_Compute_Circumsphere_By_Key (Key key, Point *center, float *radius);
HC_INTERFACE bool HC_CDECL HC_Compute_Color (char const *name, char const *out_type, RGB alter *out_value);
HC_INTERFACE bool HC_CDECL HC_Compute_Color_By_Value (char const *in_type, RGB const *in_value, char const *out_type, RGB alter *out_value);
HC_INTERFACE void HC_CDECL HC_Compute_Convex_Hull (int pcount, Point const *points, int *fcount, int face_list[]);
HC_INTERFACE bool HC_CDECL HC_Compute_Coordinates (char const *segment,
		 char const *in_system,
		 Point const *in_position,
		 char const *out_system,
		 Point *out_position);
HC_INTERFACE bool HC_CDECL HC_Compute_Coordinates_By_Path (int count,
		 Key const keys[],
		 char const *in_system,
		 Point const *in_position,
		 char const *out_system,
		 Point *out_position);
HC_INTERFACE void HC_CDECL HC_Compute_Cross_Product (Point const *vector1, Point const *vector2, Point alter *out_vector);
HC_INTERFACE double HC_CDECL HC_Compute_Dot_Product (Point const *vector1, Point const *vector2);
HC_INTERFACE void HC_CDECL HC_Compute_Identity_Matrix (float alter out_matrix[]);
HC_INTERFACE void HC_CDECL HC_Compute_Matrix_Adjoint (float const matrix[], float alter out_matrix[]);
HC_INTERFACE double HC_CDECL HC_Compute_Matrix_Determinant (float const matrix[]);
HC_INTERFACE bool HC_CDECL HC_Compute_Matrix_Inverse (float const matrix[], float alter out_matrix[]);
HC_INTERFACE void HC_CDECL HC_Compute_Matrix_Product (float const matrix1[], float const matrix2[], float alter out_matrix[]);
HC_INTERFACE void HC_CDECL HC_Compute_Minimized_Shell (int in_point_count,
		 Point const *in_points,
		 int in_face_list_length,
		 int const in_face_list[],
		 char const *option_string,
		 int *out_point_count,
		 Point *out_points,
		 int *out_face_list_length,
		 int out_face_list[],
		 int vertex_mapping[],
		 int face_mapping[]);
HC_INTERFACE bool HC_CDECL HC_Compute_Normalized_Matrix (float const matrix[], float alter out_matrix[]);
HC_INTERFACE bool HC_CDECL HC_Compute_Normalized_Vector (Point const *vector, Point alter *out_vector);
HC_INTERFACE void HC_CDECL HC_Compute_Offaxis_Rotation (double x, double y, double z, double theta, float alter out_matrix[]);
HC_INTERFACE void HC_CDECL HC_Compute_Offcenter_Rotation (double alpha, double beta, double theta, double x, double y, double z, float alter out_matrix[]);
HC_INTERFACE void HC_CDECL HC_Compute_Optimized_Shell (int pcount,
	Point const *	points,
	Vector const *	normals,
	int				flist_length,
	int const 		face_list[],
	char const *	options,
	int *			new_pcount,
	Point *			new_points,
	int *			new_flist_length,
	int 			new_face_list[],
	int 			point_mapping_list[],
	int 			face_mapping_list[]);
HC_INTERFACE Key HC_CDECL HC_Compute_Capping_Shell  (
	int				shell_count,
	Key const *		shell_list,
	float const *	plane);

HC_INTERFACE Key HC_CDECL HC_Compute_Boolean_Shell (
	int				target_pcount,
	Point const *	target_points,
	Vector const *	target_normals,
	int				target_flist_length,
	int const 		target_face_list[],
	int				tool_pcount,
	Point const *	tool_points,
	Vector const *	tool_normals,
	int				tool_flist_length,
	int const 		tool_face_list[],
	char const *	options);
HC_INTERFACE bool HC_CDECL HC_Compute_Polygon_Normal (int count, Point const *points, char const *hand, Point alter *out_vector);
HC_INTERFACE bool HC_CDECL HC_Compute_Polygon_Plane (int count, Point const *points, char const *hand, _hoops_ARPA alter *out_plane);
HC_INTERFACE void HC_CDECL HC_Compute_Rotation_Matrix (double alpha, double beta, double theta, float alter out_matrix[]);
HC_INTERFACE void HC_CDECL HC_Compute_Scale_Matrix (double x, double y, double z, float alter out_matrix[]);
HC_INTERFACE int HC_CDECL HC_Compute_Selection (char const *display,
		 char const *start_seg,
		 char const *action,
		 double x,
		 double y);
HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Area (char const *display,
		 char const *start_seg,
		 char const *action,
		 double left,
		 double right,
		 double bottom,
		 double top);
HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Polygon (char const *display,
		 char const *start_seg,
		 char const *action,
		 int pcount,
		 Point const *points);
HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Polylin (char const *display,
		 char const *start_seg,
		 char const *action,
		 int pcount,
		 Point const *points); // _hoops_CGRIH
HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Volume (char const *display,
		 char const *start_seg,
		 char const *action,
		 double left,
		 double right,
		 double bottom,
		 double top,
		 double hither,
		 double yon);
HC_INTERFACE void HC_CDECL HC_Compute_Text16_From_Text (char const *intext, char const *encoding, int *outcount, unsigned short outtext16[]);
HC_INTERFACE void HC_CDECL HC_Compute_Text_Extent (char const *segment, char const *text, float *size, float *ysize);
HC_INTERFACE void HC_CDECL HC_Compute_Text_Extent_By_Key (Key key, float *xfrac, float *yfrac);
HC_INTERFACE void HC_CDECL HC_Compute_Text_Extent_By_Path (int count, Key const keys[], char const *text, float *xfrac, float *yfrac);
HC_INTERFACE void HC_CDECL HC_Compute_Text_Extent_Enc_Path (int count,
		 Key const keys[],
		 char const *encoding,
		 char const *text,
		 float *xfrac,
		 float *yfrac);
HC_INTERFACE void HC_CDECL HC_Compute_Text_Extent_With_Enc (char const *segment,
		 char const *encoding,
		 char const *text,
		 float *xfrac,
		 float *yfrac); // _hoops_SGRIH
HC_INTERFACE void HC_CDECL HC_Compute_Text_From_Text16 (int incount, unsigned short const intext16[], char const *encoding, char *outtext);
HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline (char const *segment,
		 char const *text,
		 int *pcount,
		 Point *points,
		 int *flist_length,
		 int face_list[]);
HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_By_Key (Key key, int *pcount, Point *points, int *flist_length, int face_list[]);
HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_Size (char const *segment, char const *text, int *pcount, int *flist_length);
HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_Size_By (Key key, int *pcount, int *flist_length); // _hoops_GRRIH
HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_Size_Wi (
	char const *	segment,
	char const *	encoding,
	char const *	etext,
	int *			pcount,
	int *			flist_length); // _hoops_RRRIH
HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_With_En (char const *segment,
	char const *	encoding,
	char const *	etext,
	int *			pcount,
	Point *			points,
	int *			flist_length,
	int 			face_list[]); // _hoops_ARRIH
HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_By_Path (
		int						count,
		Key const *				keys,
		char const *			text,
		int *					pcount,
		Point *					points,
		int *					flist_length,
		int 					face_list[]);
HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_Size_Pa (
		int						count,
		Key const 				keys[],
		char const *			text,
		int *					pcount,
		int *					flist_length); // _hoops_PRRIH
HC_INTERFACE bool HC_CDECL HC_Compute_Transform (char const *segment,
		 char const *in_system,
		 char const *out_system,
		 float alter matrix[]);
HC_INTERFACE bool HC_CDECL HC_Compute_Transform_By_Path (int count,
		 Key const keys[],
		 char const *in_system,
		 char const *out_system,
		 float alter matrix[]);
HC_INTERFACE bool HC_CDECL HC_Compute_Transformed_Plane (_hoops_ARPA const *plane, float const matrix[], _hoops_ARPA *out_plane);
HC_INTERFACE bool HC_CDECL HC_Compute_Transformed_Planes (int count, _hoops_ARPA const *planes, float const matrix[], _hoops_ARPA *out_planes);
HC_INTERFACE void HC_CDECL HC_Compute_Transformed_Points (int count, Point const *points, float const matrix[], Point *out_points);
HC_INTERFACE void HC_CDECL HC_Compute_Translation_Matrix (double x, double y, double z, float alter out_matrix[]);
HC_INTERFACE double HC_CDECL HC_Compute_Vector_Length (Point const *vector);
HC_INTERFACE void HC_CDECL HC_Control_Update (char const *segment, char const *options);
HC_INTERFACE void HC_CDECL HC_Control_Update_Area (char const *segment, double left, double right, double bottom, double top, char const *options);
HC_INTERFACE void HC_CDECL HC_Control_Update_Area_By_Key (Key key, double left, double right, double bottom, double top, char const *options);
HC_INTERFACE void HC_CDECL HC_Control_Update_By_Key (Key key, char const *options);
HC_INTERFACE void HC_CDECL HC_Define_Alias (char const *name, char const *expansion);
HC_INTERFACE void HC_CDECL HC_Define_Callback_Name (char const *name, _hoops_IRPCR callback);
HC_INTERFACE void HC_CDECL HC_Define_Color_Name (char const *name, char const *er_name, char const *ish_name, char const *definition);
HC_INTERFACE void HC_CDECL HC_Define_Driver_Config (char const *driver, char const *id, char const *version, char const *config);
HC_INTERFACE void HC_CDECL HC_Define_Error_Handler (_hoops_IRPCR handler);
HC_INTERFACE void HC_CDECL HC_Define_Exit_Handler (_hoops_IRPCR handler);
HC_INTERFACE void HC_CDECL HC_Define_Font (char const *name, char const *options, int data_length, char const *data);
HC_INTERFACE void HC_CDECL HC_Define_Font_By_Reference (char const *name, char const *options, int data_length, char const *data); // _hoops_HRRIH
HC_INTERFACE void HC_CDECL HC_Define_Glyph (char const *name, int data_size, char const *data);
HC_INTERFACE void HC_CDECL HC_Define_Line_Style (char const *name, char const *definition);
HC_INTERFACE void HC_CDECL HC_Define_System_Options (char const *list);
HC_INTERFACE void HC_CDECL HC_Define_Texture (char const *texture_name, char const *definition);
HC_INTERFACE void HC_CDECL HC_Define_Local_Texture (char const *texture_name, char const *definition);
HC_INTERFACE void HC_CDECL HC_Define_Shader (char const *name, char const *options, char const *shader_source);
HC_INTERFACE void HC_CDECL HC_Delete_By_Key (Key key);
HC_INTERFACE void HC_CDECL HC_Delete_Segment (char const *segment);
HC_INTERFACE void HC_CDECL HC_Dolly_Camera (double x, double y, double z);
HC_INTERFACE POINTER_SIZED_INT HC_CDECL HC_Dump_Memory_Profile (char const *which);
HC_INTERFACE void HC_CDECL HC_Edit_Image (Key key, int xoffset, int yoffset, int xcount, int ycount, const void *data);
HC_INTERFACE void HC_CDECL HC_Edit_Image_Options (Key image_key, char const *options);
HC_INTERFACE void HC_CDECL HC_Edit_Mesh (Key key, int row_offset, int column_offset, int row_count, int column_count, Point const *points);
HC_INTERFACE void HC_CDECL HC_Edit_NURBS_Curve (Key key,
		 int control_point_offset,
		 int knot_offset,
		 int control_point_replace_count,
		 int knot_replace_count,
		 Point const *control_points,
		 float const weights[],
		 float const knots[]);
HC_INTERFACE void HC_CDECL HC_Edit_Polygon (Key key, int offset, int nDelete, int insert, Point const *points);
HC_INTERFACE void HC_CDECL HC_Edit_Polyline (Key key, int offset, int nDelete, int insert, Point const *points);
HC_INTERFACE void HC_CDECL HC_Edit_Shell_Faces (Key key, int offset, int nDelete, int ilist_length, int const insert_list[]);
HC_INTERFACE void HC_CDECL HC_Edit_Shell_Points (Key key, int offset, int nDelete, int insert, Point const *points);
HC_INTERFACE void HC_CDECL HC_Edit_Text (Key key, int row, int column, int erase, int nDelete, char const *new_text);
HC_INTERFACE void HC_CDECL HC_End_Alias_Search (void);
HC_INTERFACE void HC_CDECL HC_End_Callback_Name_Search (void);
HC_INTERFACE void HC_CDECL HC_End_Color_Name_Search (void);
HC_INTERFACE void HC_CDECL HC_End_Contents_Search (void);
HC_INTERFACE void HC_CDECL HC_End_Font_Search (void);
HC_INTERFACE void HC_CDECL HC_End_Open_Segment_Search (void);
HC_INTERFACE void HC_CDECL HC_End_Segment_Search (void);
HC_INTERFACE void HC_CDECL HC_End_Texture_Search (void);
HC_INTERFACE void HC_CDECL HC_End_Shader_Search (void);
HC_INTERFACE void HC_CDECL HC_End_Glyph_Search (void);
HC_INTERFACE void HC_CDECL HC_End_Line_Style_Search (void);
HC_INTERFACE void HC_CDECL HC_Exit_Program (void);
HC_INTERFACE bool HC_CDECL HC_Find_Alias (char * alias);
HC_INTERFACE bool HC_CDECL HC_Find_Callback_Name (char *name);
HC_INTERFACE bool HC_CDECL HC_Find_Color_Name (char *color, char *er_name, char *ish_name);
HC_INTERFACE bool HC_CDECL HC_Find_Contents (char *type, Key *key);
HC_INTERFACE bool HC_CDECL HC_Find_Font (char *name);
HC_INTERFACE bool HC_CDECL HC_Find_Open_Segment (char *segment);
HC_INTERFACE bool HC_CDECL HC_Find_Related_Selection (void);
HC_INTERFACE bool HC_CDECL HC_Find_Segment (char alter *segment);
HC_INTERFACE bool HC_CDECL HC_Find_Texture (char alter *name);
HC_INTERFACE bool HC_CDECL HC_Find_Shader (char alter *sname);
HC_INTERFACE bool HC_CDECL HC_Find_Glyph (char *name);
HC_INTERFACE bool HC_CDECL HC_Find_Line_Style (char *name);
HC_INTERFACE void HC_CDECL HC_Flush_Attributes (char const *segment);
HC_INTERFACE void HC_CDECL HC_Flush_By_Key (Key key);
HC_INTERFACE void HC_CDECL HC_Flush_Contents (char const *segment, char const *filter);
HC_INTERFACE void HC_CDECL HC_Flush_Geometry (char const *segment);
HC_INTERFACE void HC_CDECL HC_Edit_Circle (Key key, Point const *point1, Point const *point2, Point const *point3);
HC_INTERFACE void HC_CDECL HC_Edit_Circle_By_Radius (Key key, Point const *center, double radius, Point const *vector);
HC_INTERFACE void HC_CDECL HC_Edit_Sphere (Key key, Point const *center, double radius, Point const *axis, Point const *ortho);
HC_INTERFACE void HC_CDECL HC_Edit_Circular_Arc (Key key, Point const *point1, Point const *point2, Point const *point3);
HC_INTERFACE void HC_CDECL HC_Edit_Circular_Chord (Key key, Point const *point1, Point const *point2, Point const *point3);
HC_INTERFACE void HC_CDECL HC_Edit_Circular_Wedge (Key key, Point const *point1, Point const *point2, Point const *point3);
HC_INTERFACE void HC_CDECL HC_Edit_Cutting_Plane (Key key, double a, double b, double c, double d);
HC_INTERFACE void HC_CDECL HC_Edit_Ellipse (Key key, Point const *center, Point const *major, Point const *minor);
HC_INTERFACE void HC_CDECL HC_Edit_Elliptical_Arc (
		 Key key, 
		 Point const *center,
		 Point const *major,
		 Point const *minor,
		 double start,
		 double end);
HC_INTERFACE void HC_CDECL HC_Edit_Grid (
		 Key key, 
		 char const *type,
		 Point const *origin,
		 Point const *ref1,
		 Point const *ref2,
		 int count1,
		 int count2);
HC_INTERFACE void HC_CDECL HC_Edit_Line (Key key, double xa, double ya, double za, double xb, double yb, double zb);
HC_INTERFACE void HC_CDECL HC_Edit_Infinite_Line (Key key, double xa, double ya, double za, double xb, double yb, double zb);
HC_INTERFACE void HC_CDECL HC_Edit_Infinite_Ray (Key key, double xa, double ya, double za, double xb, double yb, double zb);
HC_INTERFACE void HC_CDECL HC_Edit_Marker (Key key, double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Edit_Cylinder (Key key, Point const *p1, Point const *p2, double radius, char const *cap);
HC_INTERFACE void HC_CDECL HC_Edit_PolyCylinder (Key key, int p_count, Point const *pts, int r_count, float const radii[], char const *capping);

HC_INTERFACE Key HC_CDECL HC_Copy_Geometry (Key key, char const *segment);
HC_INTERFACE Key HC_CDECL HC_Copy_Segment (char const *old, char const *nNew);
HC_INTERFACE Key HC_CDECL HC_Create_Segment (char const *segment);
HC_INTERFACE Key HC_CDECL HC_Include_Segment (char const *include);
HC_INTERFACE Key HC_CDECL HC_Include_Segment_By_Key (Key seg_key);
HC_INTERFACE Key HC_CDECL HC_Insert_Area_Light (int count, Point const *points, char const *listptr);
HC_INTERFACE Key HC_CDECL HC_Insert_Circle (Point const *point1, Point const *point2, Point const *point3);
HC_INTERFACE Key HC_CDECL HC_Insert_Circular_Arc (Point const *point1, Point const *point2, Point const *point3);
HC_INTERFACE Key HC_CDECL HC_Insert_Circular_Chord (Point const *point1, Point const *point2, Point const *point3);
HC_INTERFACE Key HC_CDECL HC_Insert_Circular_Wedge (Point const *point1, Point const *point2, Point const *point3);
HC_INTERFACE Key HC_CDECL HC_Insert_Cutting_Plane (double a, double b, double c, double d);
HC_INTERFACE Key HC_CDECL HC_Insert_Cylinder (Point const *center_point1, Point const *center_point2, double radius, char const *cap);
HC_INTERFACE Key HC_CDECL HC_Insert_Sphere (Point const *center, double radius, Point const *axis, Point const *ortho);
HC_INTERFACE Key HC_CDECL HC_Insert_Circle_By_Radius (Point const *center, double radius, Point const *normal);
HC_INTERFACE Key HC_CDECL HC_Insert_Distant_Light (double di, double dj, double dk);
HC_INTERFACE Key HC_CDECL HC_Insert_Ellipse (Point const *center, Point const *major, Point const *minor);
HC_INTERFACE Key HC_CDECL HC_Insert_Elliptical_Arc (
		Point const *center,
		Point const *major,
		Point const *minor,
		double start,
		double end);
HC_INTERFACE Key HC_CDECL HC_Insert_Grid (
		char const *type,
		Point const *origin,
		Point const *ref1,
		Point const *ref2,
		int count1,
		int count2);
HC_INTERFACE Key HC_CDECL HC_Insert_Image (double x, double y, double z, char const *format, int width, int height, const void *data);
HC_INTERFACE Key HC_CDECL HC_Insert_Compressed_Image (double x, double y, double z, char const *format, int width, int height, int size, void const *data);
HC_INTERFACE Key HC_CDECL HC_Insert_Image_By_Ref (double x, double y, double z, char const *format, int width, int height, const void *data);
HC_INTERFACE Key HC_CDECL HC_Insert_Ink (double x, double y, double z);
HC_INTERFACE Key HC_CDECL HC_Insert_Line (double xa, double ya, double za, double xb, double yb, double zb);
HC_INTERFACE Key HC_CDECL HC_Insert_Infinite_Line (double xa, double ya, double za, double xb, double yb, double zb);
HC_INTERFACE Key HC_CDECL HC_Insert_Infinite_Ray (double xa, double ya, double za, double xb, double yb, double zb);
HC_INTERFACE Key HC_CDECL HC_Insert_Local_Light (double x, double y, double z);
HC_INTERFACE Key HC_CDECL HC_Insert_Marker (double x, double y, double z);
HC_INTERFACE Key HC_CDECL HC_Insert_Mesh (int rows, int columns, Point const *points);
HC_INTERFACE Key HC_CDECL HC_Insert_Mesh_By_Ref (int rows, int columns, Point const *points);
HC_INTERFACE Key HC_CDECL HC_Insert_NURBS_Curve (int degree,
		 int control_point_count,
		 Point const * control_points,
		 float const * weights,
		 float const * knots,
		 double start_u,
		 double end_u);
HC_INTERFACE Key HC_CDECL HC_Insert_Polygon (int count, Point const *points);
HC_INTERFACE Key HC_CDECL HC_Insert_Polyline (int count, Point const *points);
HC_INTERFACE Key HC_CDECL HC_Insert_Shell (int pcount, Point const *points, int flist_length, int const face_list[]);
HC_INTERFACE Key HC_CDECL HC_Insert_Shell_By_Ref (int pcount, Point const *points, int flist_length, int const face_list[]);
HC_INTERFACE Key HC_CDECL HC_Insert_Shell_By_Tristrips (
	int				pcount,
	Point const *	points,
	int				tristrips_length,
	int const 		tristrips[],
	int				face_indices_length,
	int const 		face_indices[]);
HC_INTERFACE Key HC_CDECL HC_Insert_Spot_Light (Point const *position, Point const *target, char const *list);
HC_INTERFACE Key HC_CDECL HC_Insert_String_Cursor (Key text_key, int row, int column);
HC_INTERFACE Key HC_CDECL HC_Insert_Text (double x, double y, double z, char const *text);
HC_INTERFACE Key HC_CDECL HC_Insert_Text_With_Encoding (double x, double y, double z, char const *encoding, void const *text);
HC_INTERFACE Key HC_CDECL HC_Open_Segment (char const *segment);
HC_INTERFACE Key HC_CDECL HC_Renumber_Key (Key old_key, Key new_key, char const *scope);
HC_INTERFACE Key HC_CDECL HC_Show_Include_Segment (Key key, char *pathname);
HC_INTERFACE Key HC_CDECL HC_Show_Owner_Original_Key (Key key);
HC_INTERFACE Key HC_CDECL HC_Style_Segment (char const *style);
HC_INTERFACE Key HC_CDECL HC_Style_Segment_By_Key (Key seg_key);
HC_INTERFACE void HC_CDECL HC_MSet_Character_Attributes (Key key, int offset, int count, char const *options);
HC_INTERFACE void HC_CDECL HC_MUnSet_Character_Attributes (Key key, int offset, int count, char const *options);
HC_INTERFACE void HC_CDECL HC_MSet_Face_Normals (Key key, int offset, int count, Vector const *normals);
HC_INTERFACE void HC_CDECL HC_MSet_Face_Colors_By_FIndex (Key key, char const *type, int offset, int count, float const findices[]);
HC_INTERFACE void HC_CDECL HC_MSet_Face_Colors_By_Value (
	Key				key,
	char const *	type,
	int				offset,
	char const *	color_space,
	int				count,
	RGB const 	values[]);
HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Colors_By_FIndex (Key key, char const *types, int offset, int count, float const findices[]);
HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Colors_By_Value (
	Key				key,
	char const *	types,
	int				offset,
	char const *	color_space,
	int				count,
	RGB const 		values[]);
HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Colors_By_Value4 (
	Key				key,
	char const *	geometry,
	int				offset,
	char const *	color_space,
	int				count,
	RGBA const 	values[]);
HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Normals (Key key, int offset, int count, Vector const *normals);
HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Parameters (Key key, int offset, int pcount, int number, float const parameters[]);
HC_INTERFACE void HC_CDECL HC_Modify_Color_Map (int offset, char const *colors);
HC_INTERFACE void HC_CDECL HC_Modify_Color_Map_By_Value (int offset, char const *color_space, int count, RGB const values[]);
HC_INTERFACE void HC_CDECL HC_Move_By_Key (Key key, char const *new_owner);
HC_INTERFACE void HC_CDECL HC_Move_Distant_Light (Key key, double di, double dj, double dk);
HC_INTERFACE void HC_CDECL HC_Move_Image (Key key, double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Move_Light_Position (Key key, double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Move_Light_Target (Key key, double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Move_Segment (char const *old, char const *nNew);
HC_INTERFACE void HC_CDECL HC_Move_String_Cursor (Key key, int row, int column);
HC_INTERFACE void HC_CDECL HC_Move_Text (Key key, double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Open_Edge (int offset1, int offset2);
HC_INTERFACE void HC_CDECL HC_Open_Face (int id);
HC_INTERFACE void HC_CDECL HC_Open_Geometry (Key key);
HC_INTERFACE void HC_CDECL HC_Open_LOD (int level);
HC_INTERFACE void HC_CDECL HC_Open_Region (int region);
HC_INTERFACE void HC_CDECL HC_Open_Segment_By_Key (Key key);
HC_INTERFACE void HC_CDECL HC_Open_Vertex (int offset);
HC_INTERFACE void HC_CDECL HC_Orbit_Camera (double theta, double phi);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Callback (int key_count, Key const path_keys[], char *callbacks);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera (int key_count,
		 Key const path_keys[],
		 Point *position,
		 Point *target,
		 Vector *up,
		 float *width,
		 float *height,
		 char *projection);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_By_Volume (int count,
		 Key const keys[],
		 char *proj,
		 float *xmin,
		 float *xmax,
		 float *ymin,
		 float *ymax);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_Field (int key_count, Key const path_keys[], float *width, float *height);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_Position (int key_count, Key const path_keys[], float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_Projection (int key_count, Key const path_keys[], char *projection);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_Target (int key_count, Key const path_keys[], float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Camera_Up_Vector (int key_count, Key const path_keys[], float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Color (int count, Key const keys[], char *color_spec);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Color_Map (int key_count, Key const path_keys[], char *colors);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Color_Map_By_Value (int key_count, Key const path_keys[], char *color_space, int alter *count, RGB alter values[]);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Color_Map_Count (int key_count, Key const path_keys[], int *count);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Driver_Options (int key_count, Key const path_keys[], char *list);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Edge_Pattern (int key_count, Key const path_keys[], char *pattern);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Edge_Weight (int key_count, Key const path_keys[], float *weight);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Face_Pattern (int key_count, Key const path_keys[], char *pattern);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Handedness (int key_count, Key const path_keys[], char *value);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Heuristics (int key_count, Key const path_keys[], char *list);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Line_Pattern (int key_count, Key const path_keys[], char *pattern);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Line_Weight (int key_count, Key const path_keys[], float *weight);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Marker_Size (int key_count, Key const path_keys[], float *size);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Marker_Symbol (int key_count, Key const path_keys[], char *symbol);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Modelling_Matrix (int key_count, Key const path_keys[], float alter matrix[]);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Rendering_Options (int key_count, Key const path_keys[], char *list);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Selectability (int key_count, Key const path_keys[], char *list);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Text_Alignment (int key_count, Key const path_keys[], char *locater);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Text_Font (int key_count, Key const path_keys[], char *options);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Text_Path (int key_count, Key const path_keys[], float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Text_Spacing (int key_count, Key const path_keys[], float *spacing);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Texture_Matrix (int key_count, Key const path_keys[], float alter matrix[]);
HC_INTERFACE void HC_CDECL HC_PShow_Net_User_Index_Count (int key_count, Key const keys[], int *count);
HC_INTERFACE void HC_CDECL HC_PShow_Net_User_Indices (int key_count, Key const path_keys[], int *count, long *indices, void **values);
HC_INTERFACE void HC_CDECL HC_PShow_Net_User_Options (int key_count, Key const path_keys[], char *list);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Unicode_Options (int key_count, Key const path_keys[], unsigned short *options);
HC_INTERFACE void HC_CDECL HC_PShow_Net_User_Opt_Length (int key_count, Key const path_keys[], int *length); // _hoops_IRRIH
HC_INTERFACE void HC_CDECL HC_PShow_Net_Unicode_Opt_Length (int key_count, Key const path_keys[], int *length); // _hoops_CRRIH
HC_INTERFACE void HC_CDECL HC_PShow_Net_User_Value (int key_count, Key const path_keys[], POINTER_SIZED_INT *data);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Visibility (int key_count, Key const path_keys[], char *list);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Window (int key_count, Key const path_keys[], float *left, float *right, float *bottom, float *top);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Window_Frame (int key_count, Key const path_keys[], char *flag);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Window_Pattern (int key_count, Key const path_keys[], char *pattern);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Callback (int count, Key const keys[], char const *callback_point, char *callback_name);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Callback_WD (int count, Key const keys[], char const *callback_point, char *callback, void **data); // _hoops_SRRIH
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Color (int count, Key const keys[], char const *type, char *color);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Color_By_Index (int count, Key const keys[], char const *type, int *index);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Color_By_Value (
	int				count,
	Key const 		keys[],
	char const *	type,
	char *			color_space,
	float *			a,
	float *			b,
	float *			c);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Color_Map (int count, Key const keys[], int offset, char *color);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Color_Map_By_V (
	int				count,
	Key const 		keys[],
	int				offset,
	char *			color_space,
	float *			x,
	float *			y,
	float *			z); // _hoops_GARIH
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Driver_Option (int count, Key const keys[], char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Heuristic (int count, Key const keys[], char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Rendering_Opti (int count, Key const keys[], char const *type, char *value); // _hoops_RARIH
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Selectability (int count, Key const keys[], char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Text_Font (int count, Key const keys[], char const *type, char *value);
HC_INTERFACE bool HC_CDECL HC_PShow_One_Net_User_Index (int count, Key const keys[], long index, void **value);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_User_Option (int count, Key const keys[], char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Unicode_Opt (int key_count, Key const keys[], unsigned short const *requested_option, unsigned short *options); // _hoops_AARIH
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Visibility (int count, Key const keys[], char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_Pan_Camera (double theta, double phi);
HC_INTERFACE bool HC_CDECL HC_Parse_String (char const *string, char const *delimiter, int offset, char *token);
HC_INTERFACE void HC_CDECL HC_Pause (void);
HC_INTERFACE void HC_CDECL HC_Print_Version (void);

HC_INTERFACE int HC_CDECL HC_QShow_Existence (char const *segment, char const *filter);
HC_INTERFACE int HC_CDECL HC_Show_Existence (char const *filter);
HC_INTERFACE int HC_CDECL HC_Show_Existence_By_Key (Key key, char const *filter);

HC_INTERFACE int HC_CDECL HC_QShow_Existence_Unicode (char const *segment, unsigned short const *filter);
HC_INTERFACE int HC_CDECL HC_Show_Existence_Unicode (unsigned short const *filter);
HC_INTERFACE int HC_CDECL HC_Show_Existence_Unicode_By_K (Key key, unsigned short const *filter); // _hoops_PARIH

HC_INTERFACE void HC_CDECL HC_Read_Metafile (char const *file, char const *segment, char const *options);
HC_INTERFACE void HC_CDECL HC_Record_Instance_Handle (void const *handle);
HC_INTERFACE void HC_CDECL HC_Record_Profile_Source (char const *section, char const *filename);
HC_INTERFACE void HC_CDECL HC_Relinquish_Memory (void);
HC_INTERFACE void HC_CDECL HC_Rename_Segment (char const *old, char const *nNew);
HC_INTERFACE void HC_CDECL HC_Report_Error (int category,
		 int specific,
		 int severity,
		 int msgc,
		 char const * const *msgv,
		 int stack_c,
		 char const * const *stack_v);
HC_INTERFACE void HC_CDECL HC_Reset_System (void);
HC_INTERFACE void HC_CDECL HC_Restart_Ink (void);
HC_INTERFACE void HC_CDECL HC_Roll_Camera (double theta);
HC_INTERFACE void HC_CDECL HC_Rotate_Object (double theta, double phi, double psi);
HC_INTERFACE void HC_CDECL HC_Rotate_Object_Offaxis (double x, double y, double z, double theta);
HC_INTERFACE void HC_CDECL HC_Rotate_Texture (double theta, double phi, double psi);
HC_INTERFACE void HC_CDECL HC_Rotate_Texture_Offaxis (double x, double y, double z, double theta);
HC_INTERFACE void HC_CDECL HC_Scale_Object (double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Scale_Texture (double u, double v, double w);
HC_INTERFACE void HC_CDECL HC_Scroll_Text (Key key, int left_scroll, int up_scroll);
HC_INTERFACE void HC_CDECL HC_Set_Bounding_Cuboid (Point const *min, Point const *max);
HC_INTERFACE void HC_CDECL HC_Set_Bounding_Sphere (Point const *center, double radius);
HC_INTERFACE void HC_CDECL HC_Set_Callback (char const *callbacks);
HC_INTERFACE void HC_CDECL HC_Set_Callback_With_Data (char const *callback, void const *data);
HC_INTERFACE void HC_CDECL HC_Set_Camera (Point const *position,
		 Point const *target,
		 Vector const *up,
		 double width,
		 double height,
		 char const *projection);
HC_INTERFACE void HC_CDECL HC_Set_Camera_By_Volume (char const *projection, double xmin, double xmax, double ymin, double ymax);
HC_INTERFACE void HC_CDECL HC_Set_Camera_Field (double width, double height);
HC_INTERFACE void HC_CDECL HC_Set_Camera_Position (double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Set_Camera_Projection (char const *type);
HC_INTERFACE void HC_CDECL HC_Set_Camera_Target (double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Set_Camera_Up_Vector (double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Set_Color (char const *color_spec);
HC_INTERFACE void HC_CDECL HC_Set_Explicit_Color (
	char const *type, 
	char const *channel, 
	Point const *rgb, 
	char const *texture, 
	char const *options);
HC_INTERFACE void HC_CDECL HC_Set_Color_By_FIndex (char const *types, double findex);
HC_INTERFACE void HC_CDECL HC_Set_Color_By_Index (char const *types, int index);
HC_INTERFACE void HC_CDECL HC_Set_Color_By_Value (char const *types, char const *color_space, double a, double b, double c);
HC_INTERFACE void HC_CDECL HC_Set_Color_Map (char const *colors);
HC_INTERFACE void HC_CDECL HC_Set_Color_Map_By_Value (char const *color_space, int count, RGB const values[]);
HC_INTERFACE void HC_CDECL HC_Set_Driver_Options (char const *list);
HC_INTERFACE void HC_CDECL HC_Set_Edge_Pattern (char const *pattern);
HC_INTERFACE void HC_CDECL HC_Set_Edge_Pattern_Explicit (char const *pattern);
HC_INTERFACE void HC_CDECL HC_Set_Edge_Weight (double weight);
HC_INTERFACE void HC_CDECL HC_Set_Face_Pattern (char const *pattern);
HC_INTERFACE void HC_CDECL HC_Set_Handedness (char const *value);
HC_INTERFACE void HC_CDECL HC_Set_Heuristics (char const *list);
HC_INTERFACE void HC_CDECL HC_Set_Line_Pattern (char const *pattern);
HC_INTERFACE void HC_CDECL HC_Set_Line_Pattern_Explicit (char const *pattern);
HC_INTERFACE void HC_CDECL HC_Set_Line_Weight (double weight);
HC_INTERFACE void HC_CDECL HC_Set_Marker_Size (double weight);
HC_INTERFACE void HC_CDECL HC_Set_Marker_Symbol (char const *symbol);
HC_INTERFACE void HC_CDECL HC_Set_Modelling_Matrix (float const matrix[]);
HC_INTERFACE void HC_CDECL HC_Set_Normal (double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Set_Parameter (int number, float const parameters[]);
HC_INTERFACE void HC_CDECL HC_Set_Priority (Key key, long priority);
HC_INTERFACE void HC_CDECL HC_Set_Rendering_Options (char const *list);
HC_INTERFACE void HC_CDECL HC_Set_Selectability (char const *list);
HC_INTERFACE void HC_CDECL HC_Set_Streaming_Mode (char const *flag);
HC_INTERFACE void HC_CDECL HC_Set_Text_Alignment (char const *locater);
HC_INTERFACE void HC_CDECL HC_Set_Text_Font (char const *list);
HC_INTERFACE void HC_CDECL HC_Set_Text_Path (double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Set_Text_Size (double ivalue);
HC_INTERFACE void HC_CDECL HC_Set_Text_Spacing (double spacing);
HC_INTERFACE void HC_CDECL HC_Set_Texture_Matrix (float const matrix[]);
HC_INTERFACE void HC_CDECL HC_Set_User_Index (long index, void const *data);
HC_INTERFACE void HC_CDECL HC_Set_User_Options (char const *list);
HC_INTERFACE void HC_CDECL HC_Set_Unicode_Options (unsigned short const *options);
HC_INTERFACE void HC_CDECL HC_Set_User_Value (POINTER_SIZED_INT data);
HC_INTERFACE void HC_CDECL HC_Set_Visibility (char const *list);
HC_INTERFACE void HC_CDECL HC_Set_Window (double left, double right, double bottom, double top);
HC_INTERFACE void HC_CDECL HC_Set_Window_Frame (char const *flag);
HC_INTERFACE void HC_CDECL HC_Set_Window_Pattern (char const *pattern);
HC_INTERFACE void HC_CDECL HC_Show_Alias (char const *alias, char *expansion);
HC_INTERFACE void HC_CDECL HC_Show_Alias_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_Area_Light (Key key, int *ucount, Point *upoints, char *listptr);
HC_INTERFACE void HC_CDECL HC_Show_Area_Light_Count (Key key, int *count, char *listptr);
HC_INTERFACE bool HC_CDECL HC_Show_Bounding_Cuboid (Point *min, Point *max);
HC_INTERFACE bool HC_CDECL HC_Show_Bounding_Cuboid_By_Key (Key key, Point *min, Point *max);
HC_INTERFACE void HC_CDECL HC_Show_Bounding_Info (char *list);
HC_INTERFACE void HC_CDECL HC_Show_Bounding_Info_By_Key (Key key, char *list);
HC_INTERFACE bool HC_CDECL HC_Show_Bounding_Sphere (Point *center, float *radius);
HC_INTERFACE bool HC_CDECL HC_Show_Bounding_Sphere_By_Key (Key key, Point *center, float *radius);
HC_INTERFACE void HC_CDECL HC_Show_Button (char *button );
HC_INTERFACE void HC_CDECL HC_Show_Button_Source (char *keyboard, char *button, int *status);
HC_INTERFACE void HC_CDECL HC_Show_Callback (char *callbacks);
HC_INTERFACE void HC_CDECL HC_Show_Callback_Name (char const *name, _hoops_IRPCR *callback);
HC_INTERFACE void HC_CDECL HC_Show_Callback_Name_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_Camera (Point *position,
		 Point *	target,
		 Vector *	up,
		 float *	width,
		 float *	height,
		 char *		projection);
HC_INTERFACE void HC_CDECL HC_Show_Camera_By_Volume (char *projection, float *xmin, float *xmax, float *ymin, float *ymax);
HC_INTERFACE void HC_CDECL HC_Show_Camera_Field (float *width, float *height);
HC_INTERFACE void HC_CDECL HC_Show_Camera_Position (float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_Show_Camera_Projection (char *projection);
HC_INTERFACE void HC_CDECL HC_Show_Camera_Target (float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_Show_Camera_Up_Vector (float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_Show_Circle (Key key, Point *point1, Point *point2, Point *point3);
HC_INTERFACE void HC_CDECL HC_Show_Circular_Arc (Key key, Point *point1, Point *point2, Point *point3);
HC_INTERFACE void HC_CDECL HC_Show_Circular_Chord (Key key, Point *point1, Point *point2, Point *point3);
HC_INTERFACE void HC_CDECL HC_Show_Circular_Wedge (Key key, Point *point1, Point *point2, Point *point3);
HC_INTERFACE void HC_CDECL HC_Show_Color (char *color_spec);
HC_INTERFACE void HC_CDECL HC_Show_Color_By_Index (char *type, int *index);
HC_INTERFACE void HC_CDECL HC_Show_Color_By_Value (char *type, char *color_space, float *a, float *b, float *c);
HC_INTERFACE void HC_CDECL HC_Show_Color_Map (char *colors);
HC_INTERFACE void HC_CDECL HC_Show_Color_Map_By_Value (char *color_space, int *count, RGB values[]);
HC_INTERFACE void HC_CDECL HC_Show_Color_Map_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_Color_Name (char const *color, char *definition);
HC_INTERFACE void HC_CDECL HC_Show_Color_Name_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_Explicit_Color (
	char const *type,
	char const *channel,
	float alter *rgb,
	char alter *texture,
	char alter *options);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Explicit_Color (
	int keycount,
	Key const path_keys[],
	char const *type,
	char const *channel,
	float alter *rgb,
	char alter *texture,
	char alter *options);
HC_INTERFACE void HC_CDECL HC_Show_Contents_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_Cutting_Plane (Key key, float *a, float *b, float *c, float *d);
HC_INTERFACE void HC_CDECL HC_Show_Cylinder (Key key, Point *point1, Point *point2, float *radius, char *cap);
HC_INTERFACE void HC_CDECL HC_Show_Circle_By_Radius (Key key, Point *center, float *radius, Vector *normal);
HC_INTERFACE void HC_CDECL HC_Show_Sphere (Key key, Point *center, float *radius, Point *axis, Point *ortho);
HC_INTERFACE void HC_CDECL HC_Show_Device_Info (char const *driver, char const *item, char *data);
HC_INTERFACE void HC_CDECL HC_Show_Device_Info_By_Key (Key key, char const *item, char *data);
HC_INTERFACE void HC_CDECL HC_Show_Distant_Light (Key key, float *di, float *dj, float *dk);
HC_INTERFACE void HC_CDECL HC_Show_Driver_Options (char *list);
HC_INTERFACE void HC_CDECL HC_Show_Edge_Pattern (char *pattern);
HC_INTERFACE void HC_CDECL HC_Show_Edge_Pattern_Explicit (char *pattern);
HC_INTERFACE void HC_CDECL HC_Show_Edge_Weight (float *weight);
HC_INTERFACE void HC_CDECL HC_Show_Ellipse (Key key, Point *center, Point *major, Point *minor);
HC_INTERFACE void HC_CDECL HC_Show_Elliptical_Arc (Key key,
		 Point *center,
		 Point *major,
		 Point *minor,
		 float *start,
		 float *end);
HC_INTERFACE bool HC_CDECL HC_Show_Environment (char const *variable, char *value);
HC_INTERFACE void HC_CDECL HC_Show_Face_Pattern (char *pattern);
HC_INTERFACE void HC_CDECL HC_Show_Font (char const *name, char *options, int *data_length, char alter *data);
HC_INTERFACE void HC_CDECL HC_Show_Font_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_Font_Info (char const *driver, char const *name, char const *item, char alter *data);
HC_INTERFACE void HC_CDECL HC_Show_Font_Size (char const *name, char *options, int *data_length);
HC_INTERFACE void HC_CDECL HC_Show_Grid (Key key,
		 char *type,
		 Point *origin,
		 Point *ref1,
		 Point *ref2,
		 int *count1,
		 int *count2);
HC_INTERFACE void HC_CDECL HC_Show_Handedness (char *value);
HC_INTERFACE void HC_CDECL HC_Show_Heuristics (char *list);
HC_INTERFACE void HC_CDECL HC_Show_Image (Key key, float *x, float *y, float *z, char *format, int *width, int *height, void *data);
HC_INTERFACE void HC_CDECL HC_Show_Image_Size (Key key, float *x, float *y, float *z, char *format, int *width, int *height);
HC_INTERFACE void HC_CDECL HC_Show_Compressed_Image (Key key, float *x, float *y, float *z, char *format, int *width, int *height, int *size, void *data);
HC_INTERFACE void HC_CDECL HC_Show_Compressed_Image_Size (Key key, char *format, int *width, int *height, int *size);
HC_INTERFACE void HC_CDECL HC_Show_Image_Format (Key key, char *format);
HC_INTERFACE void HC_CDECL HC_Show_Image_Name (Key key, char *name);
HC_INTERFACE void HC_CDECL HC_Show_Glyph (char const *name, char *data);
HC_INTERFACE void HC_CDECL HC_Show_Glyph_Size (char const *name, int *data_size);
HC_INTERFACE void HC_CDECL HC_Show_Line_Style (char const *style, char *definition);
HC_INTERFACE void HC_CDECL HC_Show_Line_Style_Size (char const *style, int *size);
HC_INTERFACE void HC_CDECL HC_Show_Line_Pattern (char *pattern);
HC_INTERFACE void HC_CDECL HC_Show_Line_Pattern_Explicit (char *pattern);
HC_INTERFACE void HC_CDECL HC_Show_Key_Status (Key key, char *status);
HC_INTERFACE void HC_CDECL HC_Show_Key_Type (Key key, char *type);
HC_INTERFACE void HC_CDECL HC_Show_LOD_Type (Key key, int level, char *type);
HC_INTERFACE void HC_CDECL HC_Show_Line (Key key, float *xa, float *ya, float *za, float *xb, float *yb, float *zb);
HC_INTERFACE void HC_CDECL HC_Show_Infinite_Line (Key key, float *xa, float *ya, float *za, float *xb, float *yb, float *zb);
HC_INTERFACE void HC_CDECL HC_Show_Infinite_Ray (Key key, float *xa, float *ya, float *za, float *xb, float *yb, float *zb);
HC_INTERFACE void HC_CDECL HC_Show_Line_Weight (float *weight);
HC_INTERFACE void HC_CDECL HC_Show_Local_Light (Key key, float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_Show_Location (float *x, float *y);
HC_INTERFACE void HC_CDECL HC_Show_Location_Source (char *locater, char *display, char *action, int *status);
HC_INTERFACE void HC_CDECL HC_Show_Marker (Key key, float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_Show_Marker_Size (float *size);
HC_INTERFACE void HC_CDECL HC_Show_Marker_Symbol (char *symbol);
HC_INTERFACE void HC_CDECL HC_Show_Memory_Usage (long *allocated, long *in_use);
HC_INTERFACE void HC_CDECL HC_Show_Mesh (Key key, int *rows, int *columns, Point *points);
HC_INTERFACE void HC_CDECL HC_Show_Mesh_Size (Key key, int *rows, int *columns);
HC_INTERFACE void HC_CDECL HC_Show_Modelling_Matrix (float alter matrix[]);
HC_INTERFACE void HC_CDECL HC_Show_NURBS_Curve (Key key,
		 int *degree,
		 int *cp_count,
		 Point *points,
		 float *weights,
		 float *knots,
		 float *start_u,
		 float *end_u);
HC_INTERFACE void HC_CDECL HC_Show_NURBS_Curve_Size (Key key, int *degree, int *cp_count, int *weight_count, int *knot_count);
HC_INTERFACE void HC_CDECL HC_Show_Normal (float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_Show_One_Callback (char const *callback_point, char *callback_name);
HC_INTERFACE void HC_CDECL HC_Show_One_Callback_With_Data (char const *callback_point, char *callback, void **data);
HC_INTERFACE void HC_CDECL HC_Show_One_Color (char const *type, char *color);
HC_INTERFACE void HC_CDECL HC_Show_One_Color_By_Index (char const *type, int *index);
HC_INTERFACE void HC_CDECL HC_Show_One_Color_By_Value (char const *type, char *color_space, float *a, float *b, float *c);
HC_INTERFACE void HC_CDECL HC_Show_One_Color_Map (int offset, char *color);
HC_INTERFACE void HC_CDECL HC_Show_One_Color_Map_By_Value (int offset, char *color_space, float *a, float *b, float *c);
HC_INTERFACE void HC_CDECL HC_Show_One_Driver_Option (char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_Show_One_Heuristic (char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_Show_One_Rendering_Option (char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_Show_One_Selectability (char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_Show_One_System_Option (char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_Show_One_Text_Font (char const *type, char *value);
HC_INTERFACE bool HC_CDECL HC_Show_One_User_Index (long index, void **value);
HC_INTERFACE void HC_CDECL HC_Show_One_User_Option (char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_Show_One_Unicode_Option (unsigned short const *requestedOption, unsigned short *options);
HC_INTERFACE void HC_CDECL HC_Show_One_Visibility (char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_Show_Open_Segment_Count (int *count);
HC_INTERFACE Key HC_CDECL HC_Show_Owner (char const *segment, char *owner);
HC_INTERFACE Key HC_CDECL HC_Show_Owner_By_Key (Key key, char *owner);
HC_INTERFACE void HC_CDECL HC_Show_Parameter (int *size, float list[]);
HC_INTERFACE void HC_CDECL HC_Show_Parameter_Size (int *size);
HC_INTERFACE void HC_CDECL HC_Show_Partial_Image (Key key, int xpos, int ypos, int xlen, int ylen, void *data);
HC_INTERFACE void HC_CDECL HC_Show_Partial_Mesh (Key key,
		 int row_offset,
		 int col_offset,
		 int row_count,
		 int col_count,
		 Point *points);
HC_INTERFACE void HC_CDECL HC_Show_Partial_Polygon (Key key, int offset, int request, Point *points);
HC_INTERFACE void HC_CDECL HC_Show_Partial_Polyline (Key key, int offset, int request, Point *points);
HC_INTERFACE void HC_CDECL HC_Show_Partial_Shell (Key key,
		 int voffset,
		 int vcount,
		 Point *points,
		 int foffset,
		 int fcount,
		 int *face_list_length,
		 int face_list[]);
HC_INTERFACE void HC_CDECL HC_Show_Partial_Shell_Size (Key key, int foffset, int fcount, int *flist_length);
HC_INTERFACE void HC_CDECL HC_Show_Pathname_Expansion (char const *pathname, char *expansion);
HC_INTERFACE void HC_CDECL HC_Show_Polygon (Key key, int *count, Point *points);
HC_INTERFACE void HC_CDECL HC_Show_Polygon_Count (Key key, int *count);
HC_INTERFACE void HC_CDECL HC_Show_Polyline (Key key, int *count, Point *points);
HC_INTERFACE void HC_CDECL HC_Show_Polyline_Count (Key key, int *count);
HC_INTERFACE void HC_CDECL HC_Show_Priority (Key key, long *priority);
HC_INTERFACE void HC_CDECL HC_Show_Rendering_Options (char *list);
HC_INTERFACE void HC_CDECL HC_Show_Segment (Key key, char *pathname);
HC_INTERFACE void HC_CDECL HC_Show_Segment_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_Selectability (char *list);
HC_INTERFACE void HC_CDECL HC_Show_Selection (char *segment);
HC_INTERFACE void HC_CDECL HC_Show_Selection_Element (Key *key, int *offset1, int *offset2, int *offset3);
HC_INTERFACE void HC_CDECL HC_Show_Selection_Source_Elem (int *vertex, int *edge, int *face, Point *hit_location); // _hoops_HARIH
HC_INTERFACE void HC_CDECL HC_Show_Selection_Original_Key (Key *key);
HC_INTERFACE void HC_CDECL HC_Show_Selection_Elements (Key *key, int *count, int vertex1[], int vertex2[], int faces[]);
HC_INTERFACE void HC_CDECL HC_Show_Selection_Elements_Coun (Key *key, int *count); // _hoops_IARIH
HC_INTERFACE void HC_CDECL HC_Show_Selection_Item (Key *key, int *offset1, int *offset2);
HC_INTERFACE void HC_CDECL HC_Show_Selection_Keys (int *count, Key keys[]);
HC_INTERFACE void HC_CDECL HC_Show_Selection_Original_Keys (int *count, Key keys[]);
HC_INTERFACE void HC_CDECL HC_Show_Selection_Keys_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_Selection_Location (float *xw, float *yw, float *xc, float *yc, float *zc);
HC_INTERFACE void HC_CDECL HC_Show_Selection_Pathname (char *segment);
HC_INTERFACE void HC_CDECL HC_Show_Selection_Position (float *window_x, float *window_y, float *window_z, float *camera_x, float *camera_y, float *camera_z);
HC_INTERFACE void HC_CDECL HC_Show_Selection_Source (char *locater, char *picture, char *action, int *status);
HC_INTERFACE void HC_CDECL HC_Show_Shell (Key key, int *pcount, Point *points, int *flist_length, int face_list[]);
HC_INTERFACE void HC_CDECL HC_Show_Shell_By_Tristrips (Key key,
		 int *pcount,
		 Point *points,
		 int *tristrips_length,
		 int tristrips[],
		 int *face_indices_length,
		 int face_indices[]);
HC_INTERFACE void HC_CDECL HC_Show_Shell_By_Tristrips_Size (Key key, int *pcount, int *tristrips_length, int *face_indices_length);
HC_INTERFACE void HC_CDECL HC_Show_Shell_Size (Key key, int *pcount, int *flist_lengthp);
HC_INTERFACE void HC_CDECL HC_Show_Shell_Face_Count (Key key, int *face_count);
HC_INTERFACE void HC_CDECL HC_Show_Shell_Tristrip_Count (Key key, int *tristrip_count);
HC_INTERFACE void HC_CDECL HC_Show_Spot_Light (Key key, Point *position, Point *target, char *list);
HC_INTERFACE void HC_CDECL HC_Show_Streaming_Mode (char alter *flag);
HC_INTERFACE void HC_CDECL HC_Show_String (char *text);
HC_INTERFACE void HC_CDECL HC_Show_String_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_String_Cursor (Key key, Key *text_key, int *row, int *col);
HC_INTERFACE void HC_CDECL HC_Show_String_Length (int *length);
HC_INTERFACE void HC_CDECL HC_Show_String_Source (char *keyboard, Key *cursor_key);
HC_INTERFACE void HC_CDECL HC_Show_String_With_Encoding (char *encoding, void *text);
HC_INTERFACE Key HC_CDECL HC_Show_Style_Segment (Key key, char *pathname);
HC_INTERFACE void HC_CDECL HC_Show_System_Info (char const *type, char *value);
HC_INTERFACE void HC_CDECL HC_Show_System_Options (char *list);
HC_INTERFACE void HC_CDECL HC_Show_Text (Key key, float *x, float *y, float *z, char *text);
HC_INTERFACE void HC_CDECL HC_Show_Text_Alignment (char *locater);
HC_INTERFACE void HC_CDECL HC_Show_Text_Count (Key key, int *count);
HC_INTERFACE void HC_CDECL HC_Show_Text_Encoding (Key key, char *encoding);
HC_INTERFACE void HC_CDECL HC_Show_Text_Font (char *options);
HC_INTERFACE void HC_CDECL HC_Show_Text_Length (Key key, int *length);
HC_INTERFACE void HC_CDECL HC_Show_Text_Path (float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_Show_Text_Size (float *value);
HC_INTERFACE void HC_CDECL HC_Show_Text_Spacing (float *spacing);
HC_INTERFACE void HC_CDECL HC_Show_Text_With_Encoding (Key key, float *x, float *y, float *z, char *encoding, void *text);
HC_INTERFACE void HC_CDECL HC_Show_Texture (char const *texture, char *definition);
HC_INTERFACE void HC_CDECL HC_Show_Shader (char const *name, char *definition, char *shader_source);
HC_INTERFACE void HC_CDECL HC_Show_Local_Texture (char const *texture_name, char *definition);
HC_INTERFACE void HC_CDECL HC_Show_Texture_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_Glyph_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_Line_Style_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_Texture_Matrix (float alter *matrix);
HC_INTERFACE void HC_CDECL HC_Show_Time (float *time);
HC_INTERFACE void HC_CDECL HC_Show_User_Index_Count (int *count);
HC_INTERFACE void HC_CDECL HC_Show_User_Indices (int *count, long *indices, void **values);
HC_INTERFACE void HC_CDECL HC_Show_User_Options (char *list);
HC_INTERFACE void HC_CDECL HC_Show_Unicode_Options (unsigned short *options);
HC_INTERFACE void HC_CDECL HC_Show_User_Options_Length (int *length);
HC_INTERFACE void HC_CDECL HC_Show_Unicode_Options_Length (int *length);
HC_INTERFACE void HC_CDECL HC_Show_User_Value (POINTER_SIZED_INT *data);
HC_INTERFACE void HC_CDECL HC_Show_Visibility (char *list);
HC_INTERFACE void HC_CDECL HC_Show_Wakeup (float *time);
HC_INTERFACE void HC_CDECL HC_Show_Window (float *left, float *right, float *bottom, float *top);
HC_INTERFACE void HC_CDECL HC_Show_Window_Frame (char *flag);
HC_INTERFACE void HC_CDECL HC_Show_Window_Pattern (char *pattern);
HC_INTERFACE void HC_CDECL HC_Translate_Object (double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Translate_Texture (double u, double v, double w);
HC_INTERFACE void HC_CDECL HC_UnDefine_Alias (char const *iname);
HC_INTERFACE void HC_CDECL HC_UnDefine_Callback_Name (char const *iname);
HC_INTERFACE void HC_CDECL HC_UnDefine_Color_Name (char const *innames);
HC_INTERFACE void HC_CDECL HC_UnDefine_Error_Handler (_hoops_IRPCR iroutine);
HC_INTERFACE void HC_CDECL HC_UnDefine_Exit_Handler (_hoops_IRPCR iroutine);
HC_INTERFACE void HC_CDECL HC_UnDefine_Font (char const *name);
HC_INTERFACE void HC_CDECL HC_UnDefine_Glyph (char const *name);
HC_INTERFACE void HC_CDECL HC_UnDefine_Line_Style (char const *name);
HC_INTERFACE void HC_CDECL HC_UnDefine_Texture (char const *iname);
HC_INTERFACE void HC_CDECL HC_UnDefine_Local_Texture (char const *iname);
HC_INTERFACE void HC_CDECL HC_UnDefine_Shader (char const *iname);
HC_INTERFACE void HC_CDECL HC_UnSet_Bounding_Volume (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Callback (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Camera (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Color (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Color_Map (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Driver_Options (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Edge_Pattern (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Edge_Weight (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Face_Pattern (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Handedness (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Heuristics (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Line_Pattern (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Line_Weight (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Marker_Size (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Marker_Symbol (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Modelling_Matrix (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Normal (void);
HC_INTERFACE void HC_CDECL HC_UnSet_One_Callback (char const *which);
HC_INTERFACE void HC_CDECL HC_UnSet_One_Color (char const *which);
HC_INTERFACE void HC_CDECL HC_UnSet_One_Driver_Option (char const *which);
HC_INTERFACE void HC_CDECL HC_UnSet_One_Heuristic (char const *which);
HC_INTERFACE void HC_CDECL HC_UnSet_One_Rendering_Option (char const *which);
HC_INTERFACE void HC_CDECL HC_UnSet_One_Selectability (char const *which);
HC_INTERFACE void HC_CDECL HC_UnSet_One_Text_Font (char const *which);
HC_INTERFACE void HC_CDECL HC_UnSet_One_User_Index (long index);
HC_INTERFACE void HC_CDECL HC_UnSet_One_User_Option (char const *which);
HC_INTERFACE void HC_CDECL HC_UnSet_One_Unicode_Option (unsigned short const *which);
HC_INTERFACE void HC_CDECL HC_UnSet_One_Visibility (char const *which);
HC_INTERFACE void HC_CDECL HC_UnSet_Parameter (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Rendering_Options (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Selectability (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Streaming_Mode (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Text_Alignment (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Text_Font (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Text_Path (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Text_Spacing (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Texture_Matrix (void);
HC_INTERFACE void HC_CDECL HC_UnSet_User_Options (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Unicode_Options (void);
HC_INTERFACE void HC_CDECL HC_UnSet_User_Value (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Visibility (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Window (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Window_Frame (void);
HC_INTERFACE void HC_CDECL HC_UnSet_Window_Pattern (void);
HC_INTERFACE bool HC_CDECL HC_Update_Display (void);
HC_INTERFACE bool HC_CDECL HC_Update_Display_Timed (double limit);
HC_INTERFACE bool HC_CDECL HC_Update_One_Display (char const *name);
HC_INTERFACE bool HC_CDECL HC_Update_One_Display_Timed (char const *name, double limit);
HC_INTERFACE void HC_CDECL HC_Write_Metafile (char const *segname, char const *file, char const *options);
HC_INTERFACE void HC_CDECL HC_Zoom_Camera (double izoom);
HC_INTERFACE void HC_CDECL HC_Show_Geometry_Pointer (Key key, const char * s, void * p);
HC_INTERFACE void HC_CDECL HC_Show_Geometry_Options (Key key, char *options);
HC_INTERFACE void HC_CDECL HC_Set_Geometry_Options (Key key, const char *options); // _hoops_CARIH
HC_INTERFACE Key HC_CDECL HC_Insert_NURBS_Surface (
		 int u_degree,
		 int v_degree,
		 int n_u_vertices,
		 int n_v_vertices,
		 Point const *control_points, 
		 float const weights[],
		 float const u_knots[],
		 float const v_knots[]);
HC_INTERFACE void HC_CDECL HC_Show_NURBS_Surface_Size (
		 Key key, 
		 int alter *u_degree,
		 int alter *v_degree,
		 int alter *n_u_vertices,
		 int alter *n_v_vertices,
		 int alter *weights_count,
		 int alter *u_knots_count,
		 int alter *v_knots_count);
HC_INTERFACE void HC_CDECL HC_Show_NURBS_Surface (
		 Key key,
		 int *u_degree,
		 int *v_degree,
		 int *n_u_vertices,
		 int *n_v_vertices,
		 Point alter *control_points, 
		 float alter weights[],
		 float alter u_knots[],
		 float alter v_knots[]);
HC_INTERFACE void HC_CDECL HC_Trim_NURBS_Surface_By_Poly (
		 int count,
		 float const points[]);
HC_INTERFACE void HC_CDECL HC_Trim_NURBS_Surface_By_Curve (
		 int			degree,
		 int			control_point_count,
		 float const 	control_points[], 
		 float const 	weights[],
		 float const 	knots[],
		 double start_u,
		 double end_u);
HC_INTERFACE void HC_CDECL HC_Edit_NURBS_Surface (
		 Key key,
		 int control_point_offset,
		 int weight_offset,
		 int u_knot_offset,
		 int v_knot_offset,
		 int control_point_replace_count,
		 int weight_replace_count,
		 int u_knot_replace_count,
		 int v_knot_replace_count,
		 Point const *control_points,
		 float const weights[],
		 float const u_knots[],
		 float const v_knots[]);
HC_INTERFACE void HC_CDECL HC_Edit_NURBS_Surface_Points (
		 Key key,
		 int control_point_offset,
		 int control_point_replace_count,
		 Point const *control_points);
HC_INTERFACE void HC_CDECL HC_Edit_NURBS_Surface_Weights (
		 Key key,
		 int weight_offset,
		 int weight_replace_count,
		 float const control_points[]);
HC_INTERFACE void HC_CDECL HC_Edit_NURBS_Surface_Knots (
		 Key key,
		 int u_knot_offset,
		 int v_knot_offset,
		 int u_knot_replace_count,
		 int v_knot_replace_count,
		 float const u_knots[],
		 float const v_knots[]);
HC_INTERFACE void HC_CDECL HC_Show_Trim_Count (
		int						*count);
HC_INTERFACE void HC_CDECL HC_Show_Trim_Type (
		int						offset,
		char					*type);
HC_INTERFACE void HC_CDECL HC_Show_Trim_Poly (
		int						offset,	   
		int						*count,
		float					uvpoints[]);
HC_INTERFACE void HC_CDECL HC_Show_Trim_Poly_Count (
		int						offset,	   
		int						*count);
HC_INTERFACE void HC_CDECL HC_Show_Trim_Curve (
		int						offset,	   
		int						*degree,
		int						*control_point_count,
		float					control_points[],
		float					weights[],
		float					knots[],
		float					*start_u,
		float					*end_u);
HC_INTERFACE void HC_CDECL HC_Show_Trim_Curve_Count (
		int						offset,	   
		int						*degree,
		int						*control_point_count,
		int						*weight_count,
		int						*knot_count);
HC_INTERFACE void HC_CDECL HC_Delete_Trim (
		int						offset);
HC_INTERFACE void HC_CDECL HC_Open_Trim (
		int						offset);
HC_INTERFACE void HC_CDECL HC_Close_Trim (void);
HC_INTERFACE void HC_CDECL HC_Set_Trim_Operation (
		int						index,
		char const				*operation);
HC_INTERFACE void HC_CDECL HC_Show_Trim_Operation (
		int						index,
		char					*operation);
HC_INTERFACE void HC_CDECL HC_Create_Trim_Collection (void);
HC_INTERFACE void HC_CDECL HC_Set_Variable_Line_Weight (
		char const *			options);
HC_INTERFACE void HC_CDECL HC_Set_Variable_Edge_Weight (
		char const *			options);
HC_INTERFACE void HC_CDECL HC_Set_Variable_Marker_Size (
		char const				*options);
HC_INTERFACE void HC_CDECL HC_Show_Variable_Edge_Weight (
		char alter				*listptr);
HC_INTERFACE void HC_CDECL HC_Show_Variable_Line_Weight (
		char alter				*listptr);
HC_INTERFACE void HC_CDECL HC_Show_Variable_Marker_Size (
		char alter				*listptr);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Var_Edge_Weight (
		int					count,
		Key const			keys[],
		char alter			* weight); // _hoops_SARIH

HC_INTERFACE void HC_CDECL HC_PShow_Net_Var_Line_Weight (
		int						count,
		Key const			keys[],
		char alter				* weight); // _hoops_GPRIH

HC_INTERFACE void HC_CDECL HC_PShow_Net_Var_Marker_Size (
		int						count,
		Key const			keys[],
		char alter				* size); // _hoops_RPRIH

HC_INTERFACE void HC_CDECL HC_MShow_Character_Attributes(
		Key	key, 
		int		offset, 
		int		count, 
		char	*result);
HC_INTERFACE void HC_CDECL HC_Show_Character_Attribute_Cou(
		Key	key,  
		int		*count); // _hoops_APRIH
HC_INTERFACE void HC_CDECL HC_Show_One_Character_Attribute(
		Key	key, 
		int		offset, 
		char	const *which, 
		char	*result);
HC_INTERFACE void HC_CDECL HC_Set_Faces (
		int				first,
		int				count);
HC_INTERFACE void HC_CDECL HC_Set_Region (
		int				region);
HC_INTERFACE void HC_CDECL HC_MSet_Region_Faces (
		Key			key,
		int				region,
		int				first,
		int				count);
HC_INTERFACE void HC_CDECL HC_MSet_Face_Regions (
		Key			key,
		int				first,
		int				count,
		int const		in_regions[]);
HC_INTERFACE void HC_CDECL HC_Show_Faces (
		int alter *		count,
		int alter 		faces[]);
HC_INTERFACE void HC_CDECL HC_Show_Faces_Count (
		int alter *		count);
HC_INTERFACE void HC_CDECL HC_Show_Region (
		int alter 		region[]);
HC_INTERFACE void HC_CDECL HC_MShow_Region_Faces (
		Key			key,
		int				region,
		int alter		*count,
		int alter		faces[]);
HC_INTERFACE void HC_CDECL HC_MShow_Region_Faces_Count (
		Key			key,
		int				region,
		int alter		*count);
HC_INTERFACE void HC_CDECL HC_MShow_Face_Regions (
		Key			key,
		int alter		*count,
		int alter		regions[]);
HC_INTERFACE void HC_CDECL HC_MShow_Face_Regions_Count (
		Key			key,
		int alter		*count);
HC_INTERFACE void HC_CDECL HC_MShow_Partial_Face_Regions (
		Key			key,
		int				first,
		int				count,
		int alter		regions[]);
HC_INTERFACE void HC_CDECL HC_Show_Region_Range (
		Key			key,
		int alter *		lowest,
		int alter *		highest);
HC_INTERFACE Key HC_CDECL HC_Insert_PolyCylinder (int pcount, Point const *pts, int rcount, float const rads[], char const *listptr);
HC_INTERFACE void HC_CDECL HC_Show_PolyCylinder (Key key, int *pcount, Point *pts, int *rcount, float rads[], char *listptr);
HC_INTERFACE void HC_CDECL HC_Show_PolyCylinder_Counts (Key key, int *pcount, int *rcount, char *listptr);
HC_INTERFACE Key HC_CDECL HC_Insert_Shell_From_Region (Key key, int region, char const *options);
HC_INTERFACE Key HC_CDECL HC_Insert_Unicode_Text (
	double x,
	double y,
	double z,
	unsigned short const text[]);
HC_INTERFACE void HC_CDECL HC_Show_Unicode_Text (
	Key key, 
	float *x, 
	float *y, 
	float *z, 
	unsigned short text[]);
HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Shell ( 
		char const *action, 
		char const *start_seg, 
		int point_count, 
		Point const *points, 
		int face_list_length, 
		int const face_list[] );
HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Sh_W_Op ( 
		char const *action, 
		char const *start_seg, 
		int point_count, 
		Point const *points, 
		int face_list_length, 
		int const face_list[],
		char const *options); // _hoops_PPRIH
HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Swept_S ( 
		char const *action, 
		char const *start_seg, 
		Key			shellkey,
		int			sweepcount,
		float		const matrices[],		
		char const *options); // _hoops_HPRIH
HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Swept_2 ( 
		char const *action, 
		char const *start_seg, 
		Key			shellkey,
		int			sweepcount,
		float		const matrices[],		
		char const *options,
		float		bounding_box[]
		); // _hoops_IPRIH
HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Key ( 
		char const *action, 
		char const *start_seg, 
		Key key, float const *mat);
HC_INTERFACE Key HC_CDECL HC_Compute_Swept_Shell(
	Key				shellkey,					
	Point const		*direction_in,
	Key				*front_key,					
	Key				*back_key,		
	Key				*side_key,					
	char const			*options);  
HC_INTERFACE void HC_CDECL HC_Compute_Swept_Shell_Along_P (
	Key				shellkey,
	int				numsweeps,
	float const 	matrices[],
	char const *	options); // _hoops_CPRIH
HC_INTERFACE float HC_CDECL HC_Compute_Selection_Dist_By_Sh ( 
	char const *	action, 
	char const *	start_seg, 
	int				point_count, 
	Point const *	points, 
	int				face_list_length, 
	int const 		face_list[] ,
	const char *	options); // _hoops_SPRIH
HC_INTERFACE void HC_CDECL HC_Begin_Shell_Selection (void);
HC_INTERFACE void HC_CDECL HC_End_Shell_Selection (void);
HC_INTERFACE int HC_CDECL HC_Compute_Intersect_Polyline (
		int point_count1, 
		Point const *points1, 
		int face_list_length1, 
		int const face_list1[],
		int point_count2, 
		Point const *points2, 
		int face_list_length2, 
		int const face_list2[],
		int *polyline_count, 
		int polyline_lengths[], 
		int *polyline_points_count, 
		Point *polyline_points );
HC_INTERFACE int HC_CDECL HC_Show_Intersect_Polyline_Size (
		int point_count1, 
		Point const *points1, 
		int face_list_length1, 
		int const face_list1[],
		int point_count2, 
		Point const *points2, 
		int face_list_length2, 
		int const face_list2[],
		int *polyline_count, 
		int *polyline_points_count );
HC_INTERFACE bool HC_CDECL HC_Compute_Point_Inside_Shell (
		Point const *pt,
		int point_count1,
		Point const *points1,
		int face_list_length1,
		int const face_list1[]);
HC_INTERFACE bool HC_CDECL HC_Compute_Point_On_Shell (
		Point const *pt,
		double tolerance,
		int point_count1,
		Point const *points1,
		int face_list_length1,
		int const face_list1[]);
HC_INTERFACE int HC_CDECL HC_Compute_Points_On_Shell (
		int test_pcount,
		Point const *test_pt,
 		double tolerance,
		int point_count1,
		Point const *points1,
		int face_list_length1,
		int const face_list1[],
		int results[]);
HC_INTERFACE int HC_CDECL HC_Compute_Points_Distance_F_Sh (
		int test_pcount,
		Point const *test_pt,
 		double tolerance,
		int point_count1,
		Point const *points1,
		int face_list_length1,
		int const face_list1[],
		const char *options,
		float *results); // _hoops_GHRIH
HC_INTERFACE int HC_CDECL HC_Compute_Points_Distance_F_S2 (
		int test_pcount,
		Point const *test_pt,
 		double tolerance,
		int point_count1,
		Point const *points1,
		int face_list_length1,
		int const face_list1[],
		const char *options,
		float *results,
		int *face_results); // _hoops_RHRIH
HC_INTERFACE void HC_CDECL HC_Compute_Points_Inside_Shell (
	int test_pcount,
	Point const *test_pt,
	Point const *test_vec,
	int point_count1,
	Point const *points1,
	int face_list_length1,
	int const face_list1[],
	char const *options,
	int *results);
HC_INTERFACE void HC_CDECL HC_Compute_Shell_Enclosure (
		int point_count1,
		Point const *points1,
		int face_list_length1,
		int const face_list1[],
		int point_count2,
		Point const *points2,
		int face_list_length2,
		int const face_list2[],
		char alter *result);
HC_INTERFACE int HC_CDECL HC_Compute_Selection_By_Ray ( 
		char const *action, 
		char const *start_seg, 
		Point const *start,
		Point const *direction );
HC_INTERFACE bool HC_CDECL HC_Filter_Circumcuboid (char const *segname, char const *filter, Point *min, Point *max);
HC_INTERFACE bool HC_CDECL HC_Filter_Circumcuboid_By_Key (Key key, char const *filter, Point *min, Point *max);
HC_INTERFACE bool HC_CDECL HC_Filter_Circumsphere (char const *segname, char const *filter, Point *center, float *radius);
HC_INTERFACE bool HC_CDECL HC_Filter_Circumsphere_By_Key (Key key, char const *filter, Point *center, float *radius);
HC_INTERFACE void HC_CDECL HC_Set_Polygonal_Clip_Region (
 int count, Point const * points, char const * options);
HC_INTERFACE void HC_CDECL HC_Show_Clip_Region (
 int alter *loops, int alter *lengths, Point alter *points, char *spec);
HC_INTERFACE void HC_CDECL HC_Show_Clip_Region_Size (
 int alter *loops, int alter *total, char *spec);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Clip_Region (
 int count, Key const keys[], int alter *loops, int alter *lengths, Point alter *points, char *spec);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Clip_Region_Size (
 int count, Key const keys[], int alter *loops, int alter *total, char *spec);
HC_INTERFACE void HC_CDECL HC_UnSet_Clip_Region (void);
HC_INTERFACE void HC_CDECL HC_Regenerate_LOD (char const *s1, char const *s2);
HC_INTERFACE void HC_CDECL HC_Regenerate_LOD_By_Key (Key key, char const *s2);
HC_INTERFACE void HC_CDECL HC_Set_Text_Region (int count, Point const *points, char const *options);
HC_INTERFACE void HC_CDECL HC_Show_Text_Region (int alter *count, Point alter *points, char alter *options);
HC_INTERFACE void HC_CDECL HC_Show_Text_Region_Count (int alter *count);
HC_INTERFACE void HC_CDECL HC_UnSet_Text_Region (void);
HC_INTERFACE void HC_CDECL HC_Compute_Screen_Extent (
		char const *segname, char const *filter, float *left, float *right, float *bottom, float *top);
HC_INTERFACE void HC_CDECL HC_Compute_Screen_Extent_By_Pat (
		int count, Key const keys[], char const *filter, float *left, float *right, float *bottom, float *top); // _hoops_AHRIH
HC_INTERFACE void HC_CDECL HC_Compute_Screen_Extent_By_Key (
		Key key, char const *filter, float *left, float *right, float *bottom, float *top);
HC_INTERFACE void HC_CDECL HC_Set_Camera_Near_Limit (double ilimit);
HC_INTERFACE bool HC_CDECL HC_Show_Camera_Near_Limit (float *limit);
HC_INTERFACE bool HC_CDECL HC_PShow_Net_Camera_Near_Limit (int count, Key const keys[], float *limit);
HC_INTERFACE void HC_CDECL HC_UnSet_Camera_Near_Limit (void);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_User_Opt_Len (int count, Key const keys[], char const * which, int *length); // _hoops_PHRIH
HC_INTERFACE void HC_CDECL HC_Show_One_User_Option_Length (char const *uoname, int *length);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Uni_Opt_Len (int count, Key const keys[], unsigned short const * which, int * length); // _hoops_HHRIH
HC_INTERFACE void HC_CDECL HC_Show_One_Uni_Option_Length (unsigned short const *uoname, int *length); // _hoops_IHRIH
HC_INTERFACE Key HC_CDECL HC_Show_Original_Key (Key key);
HC_INTERFACE Key HC_CDECL HC_Show_Renumbered_Key (Key key, char *status);
HC_INTERFACE double HC_CDECL HC_Compute_Vector_Angle (Point const *in1, Point const *in2);
HC_INTERFACE void HC_CDECL HC_Set_Conditions (char const *options);
HC_INTERFACE void HC_CDECL HC_UnSet_Conditions (void);
HC_INTERFACE void HC_CDECL HC_UnSet_One_Condition (char const *which);
HC_INTERFACE void HC_CDECL HC_Set_Conditional_Action (char const * options,char const * condition);
HC_INTERFACE void HC_CDECL HC_Show_Cond_Action_Types (char * action_types); // _hoops_CHRIH
HC_INTERFACE void HC_CDECL HC_Show_One_Conditional_Action (char const * action_type, char * options, char * condition);
HC_INTERFACE void HC_CDECL HC_UnSet_Conditional_Actions (void);
HC_INTERFACE void HC_CDECL HC_UnSet_One_Conditional_Action (char const *which);
HC_INTERFACE Key HC_CDECL HC_Conditional_Style (char const *name, char const *condition);
HC_INTERFACE Key HC_CDECL HC_Conditional_Style_By_Key (Key key, char const *condition);
HC_INTERFACE Key HC_CDECL HC_Conditional_Include (char const *name, char const *condition);
HC_INTERFACE Key HC_CDECL HC_Conditional_Include_By_Key (Key key, char const *condition);
HC_INTERFACE void HC_CDECL HC_Show_Conditions (char *options);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Conditions (int count, Key const keys[], char *options);
HC_INTERFACE void HC_CDECL HC_Show_Conditions_Length (int *length);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Conditions_Length (int count, Key const keys[], int *length);
HC_INTERFACE void HC_CDECL HC_Show_One_Condition (char const *cname, char *options);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Condition (int count, Key const keys[], char const * conditions, char * options);
HC_INTERFACE void HC_CDECL HC_Show_Conditional_Include (Key key, char *includee, char *condition);
HC_INTERFACE void HC_CDECL HC_Show_Conditional_Style (Key key, char *pathname, char *condition);
HC_INTERFACE Key HC_CDECL HC_Copy_Segment_With_Mapping (char const *oldname, char const *newname, int count, Key const old_keys[], Key alter new_keys[]);
HC_INTERFACE void HC_CDECL HC_Reverse_Contents_Search (void);
HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Colors_By_Value (Key key, char const *type, int offset, int count, RGB alter rgb[]);
HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Colors_By_FInd (Key key, char const *type, int offset, int count, float alter findices[]); // _hoops_SHRIH
HC_INTERFACE void HC_CDECL HC_MShow_Face_Colors_By_Value (Key key, int offset, int count, RGB alter rgb[]);
HC_INTERFACE void HC_CDECL HC_MShow_Face_Colors_By_FIndex (Key key, int offset, int count, float alter findices[]);
HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Normals (Key key, int offset, int count, Vector alter *normals);
HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Parameters (Key key, int offset, int count, int	alter *number_parameters, float alter user_parameters[]);
HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Parameter_Size (Key key, int *number_parameters);
HC_INTERFACE void HC_CDECL HC_Set_Circular_Center (double x, double y, double z);
HC_INTERFACE void HC_CDECL HC_Set_Circular_Center_By_Key (Key key, double x, double y, double z);
HC_INTERFACE bool HC_CDECL HC_Show_Circular_Center (Key key, float * x, float * y, float * z);
HC_INTERFACE void HC_CDECL HC_MShow_Net_Vertex_Normals (Key key, int offset, int count, Vector alter * normals);
HC_INTERFACE bool HC_CDECL HC_Show_Error (char * severity, int * category, int * specific);
HC_INTERFACE void HC_CDECL HC_MSet_Vertex_Visibilities (Key key, int offset, int count, char const visibilities[]);
HC_INTERFACE void HC_CDECL HC_MUnSet_Vertex_Visibilities (Key key, int offset, int count);
HC_INTERFACE void HC_CDECL HC_MShow_Vertex_Visibilities (Key key, int offset, int count, char alter visibilities[]);
HC_INTERFACE void HC_CDECL HC_MSet_Face_Visibilities (Key key, int offset, int count, char const visibilities[]);
HC_INTERFACE void HC_CDECL HC_MUnSet_Face_Visibilities (Key key, int offset, int count);
HC_INTERFACE void HC_CDECL HC_MShow_Face_Visibilities (Key key, int offset, int count, char alter visibilities[]);
HC_INTERFACE void HC_CDECL HC_MSet_Specific_Vertex_Vis (Key key, int count, int const indices[], char const visibilities[]); // _hoops_GIRIH
HC_INTERFACE void HC_CDECL HC_MUnSet_Specific_Vertex_Vis (Key key, int count, int const  indices[]); // _hoops_RIRIH
HC_INTERFACE void HC_CDECL HC_MShow_Specific_Vertex_Vis (Key key, int count, int const  indices[], char alter visibilities[]); // _hoops_AIRIH
HC_INTERFACE void HC_CDECL HC_MSet_Specific_Face_Vis (Key key, int count, int const indices[], char const visibilities[]); // _hoops_PIRIH,_hoops_HIRIH
HC_INTERFACE void HC_CDECL HC_MUnSet_Specific_Face_Vis (Key key, int count, int const indices[]); // _hoops_IIRIH,_hoops_CIRIH
HC_INTERFACE void HC_CDECL HC_MShow_Specific_Face_Vis (Key key, int count, int const indices[], char alter visibilities[]); // _hoops_SIRIH,_hoops_GCRIH
HC_INTERFACE void HC_CDECL HC_MUnSet_Face_Colors (Key key, int offset, int count);
HC_INTERFACE void HC_CDECL HC_MUnSet_Vertex_Colors (Key key, int offset, int count);
HC_INTERFACE Key HC_CDECL HC_Insert_Cutting_Section (int count, _hoops_ARPA const *planes);
HC_INTERFACE void HC_CDECL HC_Show_Cutting_Section (Key key, int *count, _hoops_ARPA alter *planes);
HC_INTERFACE void HC_CDECL HC_Show_Cutting_Section_Count (Key key, int *count);
HC_INTERFACE void HC_CDECL HC_Edit_Cutting_Section (Key key, int ioffset, int ndelete, int insert, _hoops_ARPA const * iplanes);
HC_INTERFACE void HC_CDECL HC_Compute_Triangulation(Point const *points, int flist_length, int const face_list[], int *tlist_length, int triangle_list[]);
HC_INTERFACE void HC_CDECL HC_Compute_Triangulation_Size(Point const *points, int flist_length, int const face_list[], int *tlist_length);
HC_INTERFACE void HC_CDECL HC_Compute_Polyline_From_Curve(Key key, char const *options, int *pcount, Point *points);
HC_INTERFACE void HC_CDECL HC_Compute_Pline_From_Crv_Size(Key key, char const *options, int *pcount); // _hoops_RCRIH
HC_INTERFACE void HC_CDECL HC_Optimize_Segment_Tree (char const * segname, char const * option_string);
HC_INTERFACE void HC_CDECL HC_Optimize_Segment_Tree_By_Key (Key segkey, char const * option_string);
HC_INTERFACE void HC_CDECL HC_Show_Optimized_Mapping (char const * segname, char const * direction,
													Key in_owner, Key in_key, int in_region,
													Key * out_owner, Key * out_key, int * out_region);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Texture(int count, Key const keys[],char const * txr, char *output, Key * out_image);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Texture(int count, Key const keys[], char const * txr, char const * opt, char *output);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Shader(int count, Key const keys[],char const * name, char *output, char *shader_source);
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Shader_Option(int count, Key const keys[], char const * name, char const * opt, char *output);
HC_INTERFACE void HC_CDECL HC_Show_Priority_Range (Key key, long *low, long *high);
HC_INTERFACE void HC_CDECL HC_Delete_Specific_Shell_Points (Key key, int count, int const  indices[]);
HC_INTERFACE void HC_CDECL HC_Delete_Specific_Shell_Faces (Key key, int count, int const  indices[]);
HC_INTERFACE void HC_CDECL HC_MSet_Spec_Vert_Col_By_FIndex (
	Key key, char const *geometry, int count, int const  indices[], float const findices[]); // _hoops_ACRIH
HC_INTERFACE void HC_CDECL HC_MSet_Spec_Vert_Col_By_Value (
	Key key, char const *geometry, int count, int const  indices[], char const *color_space, RGB const values[]); // _hoops_PCRIH
HC_INTERFACE void HC_CDECL HC_MSet_Spec_Face_Col_By_FIndex (
	Key key, int count, int const  indices[], float const findices[]); // _hoops_HCRIH
HC_INTERFACE void HC_CDECL HC_MSet_Spec_Face_Col_By_Value (
	Key key, int count, int const  indices[], char const *color_space, RGB const values[]); // _hoops_ICRIH
HC_INTERFACE void HC_CDECL HC_MShow_Spec_Vert_Col_By_FInd (
	Key key, char const *geometry, int count, int const  indices[], float alter findices[]); // _hoops_CCRIH
HC_INTERFACE void HC_CDECL HC_MShow_Spec_Vert_Col_By_Value (
	Key key, char const *geometry, int count, int const  indices[], RGB alter rgb[]); // _hoops_SCRIH
HC_INTERFACE void HC_CDECL HC_MShow_Spec_Face_Col_By_FInd (
	Key key, int count, int const  indices[], float alter findices[]); // _hoops_GSRIH
HC_INTERFACE void HC_CDECL HC_MShow_Spec_Face_Col_By_Value (
	Key key, int count, int const  indices[], RGB alter rgb[]); // _hoops_RSRIH
HC_INTERFACE void HC_CDECL HC_MUnSet_Spec_Vertex_Colors (Key key, int count, int const  indices[]); // _hoops_ASRIH
HC_INTERFACE void HC_CDECL HC_MUnSet_Spec_Face_Colors (Key key, int count, int const  indices[]); // _hoops_PSRIH
HC_INTERFACE Key HC_CDECL HC_Generate_Shell_From_Geometry(Key geom, char const *options);
HC_INTERFACE Key HC_CDECL HC_Generate_Poly_From_Geometry(Key geom, char const *options); // _hoops_HSRIH
HC_INTERFACE void HC_CDECL HC_Compute_Face_Neighborhood_Si (
	Key key, 
	int index, 
	int alter *count); // _hoops_ISRIH
HC_INTERFACE void HC_CDECL HC_Compute_Face_Neighborhood (
	Key key, 
	int index, 
	int alter *count, 
	int alter neighbors[]);
HC_INTERFACE void HC_CDECL HC_Show_Net_Normal (float *x, float *y, float *z);
HC_INTERFACE void HC_CDECL HC_Rollback_Ink(int count);
HC_INTERFACE Key HC_CDECL HC_Reference_Geometry (char const *name);
HC_INTERFACE Key HC_CDECL HC_Reference_Geometry_By_Key (Key key);
HC_INTERFACE Key HC_CDECL HC_Conditional_Reference (char const *name, char const *condition);
HC_INTERFACE Key HC_CDECL HC_Conditional_Reference_By_Key (Key key, char const *condition); 
HC_INTERFACE Key HC_CDECL HC_Show_Reference_Geometry (Key key);
HC_INTERFACE Key HC_CDECL HC_Show_Conditional_Reference (Key key, char *condition);
HC_INTERFACE void HC_CDECL HC_Show_Reference_Geometry_Filt (Key key, char *filter); // _hoops_CSRIH
HC_INTERFACE void HC_CDECL HC_Begin_Open_Item_Search (void) ;
HC_INTERFACE bool HC_CDECL HC_Find_Open_Item (Key	*key, char *type, int *offset1, int	*offset2);
HC_INTERFACE void HC_CDECL HC_Show_Open_Item_Count (int	*count);
HC_INTERFACE void HC_CDECL HC_End_Open_Item_Search (void);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Color_Map_Length (int count, Key const keys[], int *value);
HC_INTERFACE void HC_CDECL HC_Show_Color_Map_Length (int *value);
HC_INTERFACE void HC_CDECL HC_Move_Key_By_Key (Key key, Key newowner); // _hoops_SSRIH
HC_INTERFACE void HC_CDECL HC_Set_User_Data (POINTER_SIZED_INT index, void const *data, long data_length);
HC_INTERFACE long HC_CDECL HC_Show_One_User_Data (POINTER_SIZED_INT index, void *data, long data_length);
HC_INTERFACE long HC_CDECL HC_Show_User_Data_Indices (POINTER_SIZED_INT data_indices[], long data_indices_count);
HC_INTERFACE void HC_CDECL HC_UnSet_One_User_Data (POINTER_SIZED_INT index);
HC_INTERFACE long HC_CDECL HC_PShow_One_Net_User_Data (
	int					count,
	Key const *			keys,	
	POINTER_SIZED_INT index, 
	void *data, 
	long data_length);
HC_INTERFACE int HC_CDECL HC_MShow_Vertex_Colors_With_Ex (Key key, char const *	geometry, int offset, int count, char *	result_type, float * index_colors, RGB alter * rgb_colors, RGBA alter * rgba_colors); // _hoops_GGAIH
HC_INTERFACE void HC_CDECL HC_MUnSet_Vertex_Normals (Key key, int offset, int count);
HC_INTERFACE void HC_CDECL HC_MUnSet_Face_Normals (Key key, int offset, int count);
HC_INTERFACE void HC_CDECL HC_MUnSet_Vertex_Parameters (Key key, int offset, int count);
HC_INTERFACE void HC_CDECL HC_MSet_Specific_Vertex_Normals (Key key, int count, int const  indices[], Vector const *normals);
HC_INTERFACE void HC_CDECL HC_MUnSet_Specific_Vert_Normals (Key key, int count, int const  indices[]); // _hoops_RGAIH
HC_INTERFACE void HC_CDECL HC_MShow_Specific_Vert_Normals (Key key, int count, int const  indices[], Vector alter * normals); // _hoops_AGAIH
HC_INTERFACE void HC_CDECL HC_MSet_Specific_Face_Normals (Key key, int count, int const  indices[], Vector const * normals);
HC_INTERFACE void HC_CDECL HC_MUnSet_Specific_Face_Normals (Key key, int count, int const  indices[]);
HC_INTERFACE void HC_CDECL HC_MShow_Specific_Face_Normals (Key key, int count, int const  indices[], Vector alter * normals);
HC_INTERFACE void HC_CDECL HC_MSet_Spec_Vertex_Parameters (Key key, int count, int const  indices[], int number_parameters, float const user_parameters[]); // _hoops_PGAIH
HC_INTERFACE void HC_CDECL HC_MShow_Spec_Vertex_Parameters (Key key, int count, int const  indices[], int alter * number_parameters, float alter user_parameters[]);
HC_INTERFACE void HC_CDECL HC_MUnSet_Spec_Vert_Parameters (Key key, int count, int const  indices[]); // _hoops_HGAIH
HC_INTERFACE void HC_CDECL HC_MUnSet_Vertex_Colors2 (Key key, char const * type, int offset, int count);
HC_INTERFACE void HC_CDECL HC_MUnSet_Spec_Vertex_Colors2 (Key key, char const * type, int count, int const  indices[]); // _hoops_IGAIH
HC_INTERFACE int HC_CDECL HC_MShow_Spec_Vert_Colors_W_Ex (Key key, char const *	geometry, int count, int const vertices[], char * result_type, float index_colors[], RGB alter rgb_colors[], RGBA alter rgba_colors[]); // _hoops_CGAIH
HC_INTERFACE int HC_CDECL HC_MShow_Face_Colors_With_Ex (Key key, char const * geometry, int offset, int count, char * result_type, float index_colors[], RGB alter rgb_colors[]); // _hoops_SGAIH
HC_INTERFACE int HC_CDECL HC_MShow_Spec_Face_Colors_W_Ex (Key key, char const *	geometry, int count, int const * faces, char * result_type, float index_colors[], RGB alter rgb_colors[]); // _hoops_GRAIH
HC_INTERFACE int HC_CDECL HC_MShow_Vertex_Parameters_W_Ex (Key key, int offset, int count, char alter * existence, int alter * param_width, float alter user_parameters[]); // _hoops_RRAIH
HC_INTERFACE int HC_CDECL HC_MShow_Spec_Vertex_Params_W_E (Key key, int count, int const specific_vertices[], char alter * existence, int alter * param_width, float alter user_parameters[]); // _hoops_ARAIH
HC_INTERFACE int HC_CDECL HC_MShow_Vertex_Vis_W_Ex (Key key, int offset, int count, char alter * existence, char alter visibilities[]); // _hoops_PRAIH
HC_INTERFACE int HC_CDECL HC_MShow_Spec_Vertex_Vis_W_Ex (Key key, int count, int const  indices[], char alter * existence, char alter visibilities[]); // _hoops_HRAIH
HC_INTERFACE int HC_CDECL HC_MShow_Face_Vis_W_Ex (Key key, int offset, int count, char alter * existence, char alter * visibilities); // _hoops_IRAIH
HC_INTERFACE int HC_CDECL HC_MShow_Spec_Face_Vis_W_Ex (Key key, int count, int const  indices[], char alter * existence, char alter visibilities[]); // _hoops_CRAIH
HC_INTERFACE int HC_CDECL HC_MShow_Vertex_Normals_W_Ex (Key key, int offset, int count, char alter * existence, Vector alter * normals); // _hoops_SRAIH
HC_INTERFACE int HC_CDECL HC_MShow_Spec_Vert_Normals_W_Ex (Key key, int count, int const  indices[], char alter * existence, Vector alter *normals); // _hoops_GAAIH
HC_INTERFACE int HC_CDECL HC_MShow_Face_Normals_W_Ex (Key key, int offset, int count, char alter * existence, Vector alter * normals); // _hoops_RAAIH
HC_INTERFACE int HC_CDECL HC_MShow_Spec_Face_Normals_W_Ex (Key key, int count, int const  indices[], char alter * existence, Vector alter * normals); // _hoops_AAAIH
HC_INTERFACE Key HC_CDECL HC_Include_Segment_Key_By_Key (Key key, Key includer_key);
HC_INTERFACE Key HC_CDECL HC_Conditional_Include_Key_By_Ke (Key key, char const *condition, Key includer_key); // _hoops_PAAIH
HC_INTERFACE void HC_CDECL HC_Define_Named_Style (char const * style_name, char const * style_segment_name);
HC_INTERFACE void HC_CDECL HC_UnDefine_Named_Style (char const * style_name); 
HC_INTERFACE Key HC_CDECL HC_Show_Named_Style (char const * style_name, char *style_segment_name);
HC_INTERFACE void HC_CDECL HC_Begin_Named_Style_Search (void);
HC_INTERFACE bool HC_CDECL HC_Find_Named_Style (char * style_name);
HC_INTERFACE void HC_CDECL HC_Show_Named_Style_Count (int * count);
HC_INTERFACE void HC_CDECL HC_End_Named_Style_Search (void); 
HC_INTERFACE Key HC_CDECL HC_PShow_Net_Named_Style (
	int				count,
	Key const *		keys,
	char const *	style_name,
	char *			style_segment_name); 
HC_INTERFACE Key HC_CDECL HC_Named_Style_Segment (char const * style_name);
HC_INTERFACE void HC_CDECL HC_Show_Named_Style_Segment (Key style_key, char * style_name);
HC_INTERFACE Key HC_CDECL HC_Open_Segment_Key_By_Key (Key parent_segment, char const *child_segment_name);
HC_INTERFACE Key HC_CDECL HC_Style_Segment_Key_By_Key (Key target_segment, Key style_segment);
HC_INTERFACE Key HC_CDECL HC_Named_Style_Segment_By_Key (Key target_segment, char const * style_name);
HC_INTERFACE Key HC_CDECL HC_Create_Segment_Key_By_Key (Key parent_segment, char const * child_segment_name);
HC_INTERFACE void HC_CDECL HC_Set_Default_Line_Styles();
HC_INTERFACE void HC_CDECL HC_Set_Default_Line_Styles_By_K(Key target_segment); // _hoops_HAAIH
HC_INTERFACE void HC_CDECL HC_Set_Default_Glyphs();
HC_INTERFACE void HC_CDECL HC_Set_Default_Glyphs_By_Key(Key target_segment);
HC_INTERFACE Key HC_CDECL HC_Reference_Geometry_Key_By_Ke (Key target_segment, Key reference_key); // _hoops_IAAIH
HC_INTERFACE void HC_CDECL HC_PShow_Net_Line_Style (
	int						count,
	Key const *				keys,
	char const *			name,
	char *					definition);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Line_Style_Size (
	int						count,
	Key const *				keys,
	char const *			name,
	int *					size);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Glyph (
	int						count,
	Key const *				keys,
	char const *			name,
	char *					definition);
HC_INTERFACE void HC_CDECL HC_PShow_Net_Glyph_Size (
	int						count,
	Key const *				keys,
	char const *			name,
	int *					size);
HC_INTERFACE void HC_CDECL HC_Generate_Error (
	int						level,
	int						category,
	int						specific,
	char const *			buf1,
	char const *			buf2,
	char const *			buf3); 
HC_INTERFACE void HC_CDECL HC_Commit_Proxy (
	Key						key,
	const char *			options);
	
HC_INTERFACE Key HC_CDECL HC_Create_Proxy (
	Key						key);
	
HC_INTERFACE void HC_CDECL HC_Begin_Error_Handler_Search ();
HC_INTERFACE void HC_CDECL HC_Begin_Exit_Handler_Search (); 
HC_INTERFACE void HC_CDECL HC_End_Error_Handler_Search ();
HC_INTERFACE void HC_CDECL HC_End_Exit_Handler_Search ();
HC_INTERFACE bool HC_CDECL HC_Find_Error_Handler (_hoops_IRPCR * address);
HC_INTERFACE bool HC_CDECL HC_Find_Exit_Handler (_hoops_IRPCR * address);
HC_INTERFACE void HC_CDECL HC_Show_Error_Handler_Count (int alter *	count);
HC_INTERFACE void HC_CDECL HC_Show_Exit_Handler_Count (int alter * count);
HC_INTERFACE Key HC_CDECL HC_Compute_Subshell ( 
	Key			source,
	int			keep_fcount, 
	const int 	keep_faces[],
	int			keep_pcount, 
	const int   keep_pts1[], 
	const int   keep_pts2[],
	int 		face_map[], 
	int 		pts_map[]);
	
HC_INTERFACE void HC_CDECL HC_MSet_Specific_Edge_Vis (
	Key				key,
	int				count,
	int const 		indices1[],
	int const 		indices2[],
	char const  	visibilities[]); // _hoops_CAAIH
	
HC_INTERFACE void HC_CDECL HC_MShow_Face_Normals (
	Key				key,
	int				offset,
	int				count,
	Vector alter *	normals);
	
HC_INTERFACE void HC_CDECL HC_MShow_Net_Face_Normals (
	Key				key,
	int				offset,
	int				count,
	Vector alter *	normals);
	
HC_INTERFACE void HC_CDECL HC_MShow_Specific_Edge_Vis (
	Key				key,
	int				count,
	int const 		indices1[],
	int const 		indices2[],
	char alter 		visibilities[]); // _hoops_SAAIH
	
HC_INTERFACE void HC_CDECL HC_MUnSet_Specific_Edge_Vis (
	Key				key,
	int				count,
	int const 		indices1[],
	int const 		indices2[]); // _hoops_GPAIH
	
HC_INTERFACE void HC_CDECL HC_Show_Font_Info_By_Path (
	int				count,
	Key const 		keys[],
	char const *	font,
	char const *	item,
	char *			data);

HC_INTERFACE void HC_CDECL HC_Show_Reference_Keys (
	Key				key,
	int alter *		count,
	Key alter  		keys[]);

HC_INTERFACE void HC_CDECL HC_Show_Reference_Keys_Count (
	Key				key,
	int alter *		count); 


HC_INTERFACE void HC_CDECL HC_PShow_Net_Line_Pattern_Exp (
	int						count,
	Key const *				keys,
	char *					pattern);	// _hoops_RPAIH
HC_INTERFACE void HC_CDECL HC_PShow_Net_Edge_Pattern_Exp (
	int						count,
	Key const *				keys,
	char *					pattern);	// _hoops_APAIH


#define HC_PROTO_DEFINED 1
#endif /* _hoops_PPAIH */


