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
 * $Id: obf_tmp.txt 1.676 2010-12-06 22:05:40 jason Exp $
 */

#ifndef HI_PROTO_DEFINED
#define HI_PROTO_DEFINED

extern "C" {
	typedef void (HC_CDECL * _hoops_RRCIH)
					(void *info, Integer32 _hoops_HAPH,
					 Integer32 _hoops_ISPI, Integer32 _hoops_CSPI, Integer32 _hoops_SSPI);

	typedef void (HC_CDECL * _hoops_ARCIH)
					(void *info, int _hoops_HAPH,
					 Point const *_hoops_ISPI,
					 Point const *_hoops_CSPI,
					 Point const *_hoops_SSPI,
					 int s1,
					 int s2,
					 int _hoops_CAPH,
					 Intersection const *_hoops_GIGCR,
					 Intersection const *_hoops_RIGCR,
					 Intersection const *d3);
	}


GLOBAL_FUNCTION float HI_ACos (float _hoops_PRCIH);
GLOBAL_FUNCTION void HI_Validate_Texture_Fallback_Image ();
GLOBAL_FUNCTION _hoops_RCR * HI_Activate_Texture(_hoops_RCR const * texture, _hoops_CPAIR const * _hoops_CICSR, bool errors, Integer32 _hoops_PSSGA=0);
GLOBAL_FUNCTION float HI_ATan2 (float y, float x);
GLOBAL_FUNCTION void HI_Add_Path_Delimiter (_hoops_HCRPR alter *_hoops_PSHAP, _hoops_HCRPR alter *file);
GLOBAL_FUNCTION void HI_Adjoint_44 (float const *matp, float alter *_hoops_IRIPA);
GLOBAL_FUNCTION void HI_Adjoint_44_Z (float const *matp, float alter *_hoops_CRIPA);
GLOBAL_FUNCTION void HI_Age_Activity (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *root);
GLOBAL_FUNCTION void HI_Age_Seg_Flags (_hoops_CRCP *root);
GLOBAL_FUNCTION bool HI_Analyze_Arc (
		Point const *start,
		Point const *_hoops_GGSSR,
		Point const *end,
		Point alter *center,
		Point alter *_hoops_GGHI,
		Point alter *_hoops_RGHI,
		float alter *_hoops_RAHCR);
GLOBAL_FUNCTION bool HI_Analyze_Font_Data (int data_length,
		 char const *data,
		 char encoding,
		 bool _hoops_HRCIH,
		 int *_hoops_IRCIH,
		 char const **table,
		 char const *name);
GLOBAL_FUNCTION void HI_Append_String (char const *in, char *_hoops_PAGR);
GLOBAL_FUNCTION void HI_Append_String_To_Max (char const *in, int max, char *_hoops_PAGR);
GLOBAL_FUNCTION void HI_Clean_FCD (_hoops_RRHCA *_hoops_ARHCA);
GLOBAL_FUNCTION void HI_Arbitrary_Rotate (Vector const *axis, Point const *_hoops_RPSPA, float _hoops_RAHCR, Point *_hoops_APSPA);
GLOBAL_FUNCTION void HI_Arbitrary_Rotate_SC (Vector const *axis,
		 Point const *_hoops_RPSPA,
		 float _hoops_GGHCR,
		 float _hoops_AGHCR,
		 Point *_hoops_APSPA);
GLOBAL_FUNCTION _hoops_GSPGR HI_Assemble_3D_Polyedges (Polyhedron *_hoops_IPRI,
		 unsigned short _hoops_HGSPR,
		 float _hoops_SHIPR);
GLOBAL_FUNCTION _hoops_GSPGR HI_Assemble_3D_Polymarkers (Polyhedron *_hoops_IPRI,
		 unsigned int _hoops_HGSPR);
GLOBAL_FUNCTION _hoops_GSPGR HI_Assemble_3D_Tristrips (Polyhedron *_hoops_IPRI,
		 unsigned short _hoops_HGSPR,
		 bool _hoops_PCRHR);
GLOBAL_FUNCTION void HI_Assemble_Edge_Normals (Polyhedron *_hoops_IPRI);
GLOBAL_FUNCTION void HI_Assemble_Face_Normals (Polyhedron *_hoops_IPRI);
GLOBAL_FUNCTION void HI_Assemble_Mesh_Vertex_Normals (_hoops_AIHPR *_hoops_PIHPR);
GLOBAL_FUNCTION void HI_Assemble_Shell_Vertex_Normals (Shell *_hoops_SPHPR);
GLOBAL_FUNCTION void HI_Assemble_Vertex_Normals (Polyhedron *_hoops_IPRI);
GLOBAL_FUNCTION void HI_Assemble_Mesh_Tristrips (_hoops_AIHPR *_hoops_PIHPR,
		 unsigned short _hoops_HGSPR,
		 bool _hoops_PCRHR);
GLOBAL_FUNCTION void HI_Assemble_Shell_Tristrips (Shell *_hoops_SPHPR,
		 unsigned short _hoops_HGSPR,
		 bool _hoops_PCRHR);
GLOBAL_FUNCTION void HI_Assemble_Simple_Shell_Tristrips (
		int point_count,
		Point const *points,
		int face_list_length,
		int const *face_list,
		Tristrip **_hoops_SCGIR);
GLOBAL_FUNCTION void HI_Au_Revoir (_hoops_HPAH *thing);
GLOBAL_FUNCTION bool HI_CI_Equal_Strings (char const *a, char const *b);
GLOBAL_FUNCTION bool HI_CI_Equal_Strings_To_Max (char const *a, int max, char const *b);
GLOBAL_FUNCTION bool HI_CI_Wild_Equal_Strings (char const *a, char const *p);
GLOBAL_FUNCTION bool HI_CI_Wild_Equal_Strings_To_Max (char const *a, int max, char const *p);
GLOBAL_FUNCTION void HI_Call_Exit_Handlers (void);
GLOBAL_FUNCTION bool HI_Camera_To_Transform (_hoops_HHRA *_hoops_SPH, double _hoops_CHHCR);
GLOBAL_FUNCTION void HI_Canonize_Chars (char const *string, _hoops_HCRPR *name);
GLOBAL_FUNCTION void HI_Canonize_Chars_Quoted (char const *string, _hoops_HCRPR *name, bool _hoops_CRCIH);
GLOBAL_FUNCTION void HI_Canonize_Kars (unsigned short const *string, KName *name);
GLOBAL_FUNCTION void HI_Canonize_Line_Pattern (char const *string, _hoops_HCRPR *name, Integer32 *_hoops_HHCAP);
GLOBAL_FUNCTION void HI_Chain_Code_Files (void);
GLOBAL_FUNCTION void HI_Check_Wakeups (_hoops_AIGPR * _hoops_RIGC, _hoops_GSPGR now);
GLOBAL_FUNCTION void * HI_Clone_Aligned (void const *in, unsigned int size);
GLOBAL_FUNCTION void * HI_Clone_Anything (void const *in, unsigned int size);
GLOBAL_FUNCTION Bounding * HI_Clone_Bounding (Bounding const *bounding);
GLOBAL_FUNCTION Text_Info * HI_Clone_Text_Info (Text_Info const *text_info);
GLOBAL_FUNCTION Polyhedron * HI_Clone_Polyhedron (_hoops_AIGPR * _hoops_RIGC, Polyhedron *_hoops_IGRSA);
GLOBAL_FUNCTION _hoops_RCR * HI_Clone_Texture (_hoops_RCR const *texture);
GLOBAL_FUNCTION void HI_Close_Complaint (_hoops_AIGPR * _hoops_RIGC, int _hoops_SRCIH);
GLOBAL_FUNCTION bool HI_Close_Directory (void alter *_hoops_PSIHH, _hoops_HCRPR alter *_hoops_GGHGA, _hoops_HCRPR alter *_hoops_RGHGA);
GLOBAL_FUNCTION bool HI_Close_File (void alter *_hoops_CRIPH, _hoops_HCRPR alter *_hoops_GGHGA, _hoops_HCRPR alter *_hoops_RGHGA);
GLOBAL_FUNCTION int HI_Compare_KNames (KName const *a, KName const *b);
GLOBAL_FUNCTION int HI_Compare_Names (_hoops_HCRPR const *a, _hoops_HCRPR const *b);
GLOBAL_FUNCTION int HI_Compare_Strings (char const *a, char const *b);
GLOBAL_FUNCTION int HI_Compare_Strings_To_Max (char const *a, int max, char const *b);
GLOBAL_FUNCTION bool HI_Compute_Three_Point_Circle (
	Point const & start,
	Point const & _hoops_GGSSR,
	Point const & end,
	Point *center,
	float *radius,
	_hoops_ARPA *plane,
	Vector *_hoops_GGHI,
	Vector *_hoops_RGHI);
GLOBAL_FUNCTION bool HI_Compute_Window_Extent (
	_hoops_AIGPR * _hoops_RIGC,
	char const *segname,
	float *_hoops_AGACA,
	float *_hoops_PGACA,
	int *_hoops_HGACA,
	int *_hoops_IGACA,
	int *left,
	int *right,
	int *bottom,
	int *top);
GLOBAL_FUNCTION bool HI_Compute_Window_Extent_By_Pth (
	_hoops_AIGPR *	_hoops_RIGC,
	int count,
	_hoops_CRCP const **_hoops_SISAA,
	float *_hoops_AGACA,
	float *_hoops_PGACA,
	int *_hoops_HGACA,
	int *_hoops_IGACA,
	int *left,
	int *right,
	int *bottom,
	int *top);
GLOBAL_FUNCTION bool HI_Convert_Bounding (Bounding const * _hoops_GACIH, _hoops_RACIH _hoops_PHGIP, Bounding alter * _hoops_AACIH);
GLOBAL_FUNCTION void HI_Convert_Char_To_KName (char const *_hoops_PACIH, KName *_hoops_SIHSA, char encoding);
GLOBAL_FUNCTION int HI_Convert_Keys_To_Path (_hoops_AIGPR * _hoops_RIGC, int in_count, Key const *keys, _hoops_CRCP const ** & _hoops_SISAA);
GLOBAL_FUNCTION void HI_Copy_43 (float const *_hoops_PASPA, float alter *outp);
GLOBAL_FUNCTION void HI_Copy_44 (float const *_hoops_PASPA, float alter *outp);
GLOBAL_FUNCTION _hoops_IHACR * HI_Copy_Callback_List (_hoops_IHACR const *in);
GLOBAL_FUNCTION char * HI_Copy_Chars (char const *in, char *_hoops_PAGR);
GLOBAL_FUNCTION void HI_Copy_Chars_To_Name (char const *_hoops_HACIH, _hoops_HCRPR alter *_hoops_IACIH);
GLOBAL_FUNCTION _hoops_ACSGA * HI_Copy_Colors (_hoops_ACSGA const *_hoops_AIGRA, _hoops_RHAH const * _hoops_SPRAR, _hoops_PIGRA const *	locks=0);
GLOBAL_FUNCTION void HI_Free_Colors (_hoops_ACSGA alter *_hoops_AIGRA);
GLOBAL_FUNCTION _hoops_IGPIR * HI_Copy_Font_Names (_hoops_IGPIR const *in);
GLOBAL_FUNCTION Geometry * HI_Copy_Geometry (_hoops_AIGPR * _hoops_RIGC, Geometry const *_hoops_PPGSA);
GLOBAL_FUNCTION void HI_Copy_KName (KName const *in, KName *_hoops_PAGR);
GLOBAL_FUNCTION void HI_Copy_Matrix (_hoops_HRPA const *in, _hoops_HRPA alter *_hoops_PAGR);
GLOBAL_FUNCTION void HI_Free_Name_List (_hoops_AAPIR * old);
GLOBAL_FUNCTION _hoops_AAPIR * HI_Copy_Name_List (_hoops_AAPIR const *in);
GLOBAL_FUNCTION void HI_Copy_Name (_hoops_HCRPR const *in, _hoops_HCRPR *_hoops_PAGR);
GLOBAL_FUNCTION void HI_Copy_Name_To_Chars (_hoops_HCRPR const *in, char alter *_hoops_PAGR);
GLOBAL_FUNCTION void HI_Copy_Named_Material (Named_Material const *in, Named_Material *_hoops_PAGR);
GLOBAL_FUNCTION Option_Value * HI_Copy_Option_List (Option_Value const *_hoops_GASGH);
GLOBAL_FUNCTION void HI_Copy_String (char const *in, char *_hoops_PAGR);
GLOBAL_FUNCTION void HI_Copy_String_To_Max (char const *in, int max, char *_hoops_PAGR);
GLOBAL_FUNCTION float HI_Cos (float _hoops_RAHCR);
GLOBAL_FUNCTION void HI_Count_Contents (_hoops_AIGPR *	_hoops_RIGC, _hoops_CRCP *_hoops_SRCP, void *info);
GLOBAL_FUNCTION long HI_Count_Transparent_Pixels (int width, char format, void *_hoops_CACIH);
GLOBAL_FUNCTION void HI_Create_Image (Image **_hoops_SACIH,
		 Point const *	where,
		 int width,
		 int height,
		 char format,
		 int row_bytes,
		 int type,
		 unsigned char const *source);
GLOBAL_FUNCTION _hoops_CRCP * HI_Create_One_Segment (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCRPR const *name,
	Subsegment **_hoops_ASRGR,
	Subsegment *_hoops_AIGSA,
	_hoops_CRCP *owner,
	bool _hoops_PPPSA);
GLOBAL_FUNCTION void HI_Open_Segment (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *_hoops_SRCP);
GLOBAL_FUNCTION int HI_Create_Polyglin_Wings (int count, Point *points, bool _hoops_SPGPA, int owner, _hoops_GPCIH ***_hoops_RPCIH);
GLOBAL_FUNCTION _hoops_RGASA * HI_Create_Polygon_Wedge_Tree (int count, Point *points, Point *pivot, bool _hoops_CGASA);
GLOBAL_FUNCTION _hoops_CRCP * HI_Create_Segment (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP * owner,
	char const *name,
	bool _hoops_IIASA);
GLOBAL_FUNCTION void HI_Create_Shell_Edges (Shell *_hoops_SPHPR, bool _hoops_APCIH);
GLOBAL_FUNCTION void HI_Cross_Product (Vector const *a, Vector const *b, Vector alter *c);
GLOBAL_FUNCTION _hoops_HISHA * HI_Current_Event (_hoops_AIGPR * _hoops_RIGC, Type type);
GLOBAL_FUNCTION int HI_Decipher_Action (char const *_hoops_CCAPH);
GLOBAL_FUNCTION bool HI_Decipher_Color_Target (
	_hoops_AIGPR * _hoops_RIGC,
	char const **_hoops_RAARA,
	char const *_hoops_SSRPR,
	bool _hoops_AAARA,
	Color_Object * _hoops_PAARA,
	Color_Object _hoops_GAARA);
GLOBAL_FUNCTION Option_Value * HI_Decipher_Color_Type (_hoops_AIGPR * _hoops_RIGC, char const *type, int _hoops_IRIAA);
GLOBAL_FUNCTION Option_Value * HI_Decipher_Color_Channel (_hoops_AIGPR * _hoops_RIGC, char const *type, int _hoops_IRIAA);
GLOBAL_FUNCTION char HI_Decipher_Encoding (_hoops_AIGPR * _hoops_RIGC, char const *encoding);
GLOBAL_FUNCTION bool HI_Decipher_Handedness (char const *_hoops_HIGIH, int alter *which);
GLOBAL_FUNCTION void HI_Decipher_Metafile_Options (_hoops_AIGPR * _hoops_RIGC, char const *listptr, Metafile *_hoops_APHCR);
GLOBAL_FUNCTION bool HI_Decipher_Type_Names (_hoops_AIGPR *	_hoops_RIGC, char const *types, _hoops_RRHCA *_hoops_ARHCA);
GLOBAL_FUNCTION bool HI_Decipher_Unicode_Type_Names (_hoops_AIGPR * _hoops_RIGC, Karacter const * types, _hoops_RRHCA * _hoops_ARHCA);
GLOBAL_FUNCTION void HI_Define_Constant_Options (_hoops_IGRCR const *_hoops_PPCIH,
		 int _hoops_HPCIH,
		 _hoops_GCIIR *_hoops_IPCIH);
GLOBAL_FUNCTION void HI_Define_Default_Colors (_hoops_AIGPR * _hoops_RIGC);
GLOBAL_FUNCTION _hoops_PGIIR * HI_Define_Font (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *name,
	char const *options,
	int data_length,
	char const *data,
	bool _hoops_CPCIH);
GLOBAL_FUNCTION void HI_Define_Internal_Fonts (_hoops_AIGPR * _hoops_RIGC);
GLOBAL_FUNCTION _hoops_PIIIR * HI_Define_Nice_Option (
	_hoops_GCIIR *_hoops_SPHHR,
	long id,
	const _hoops_HCRPR *name,
	int _hoops_RCIIR,
	int _hoops_RHSAA,
	bool _hoops_GHSAA,
	_hoops_GCIIR *_hoops_CIIIR);
GLOBAL_FUNCTION _hoops_RPSAP * HI_Define_Nice_KOption (
	_hoops_GCIIR *_hoops_SPHHR,
	long id,
	const KName *name,
	int _hoops_RCIIR,
	int _hoops_RHSAA,
	bool _hoops_GHSAA,
	_hoops_GCIIR *_hoops_CIIIR);
GLOBAL_FUNCTION void HI_Define_Implicit_Texture(_hoops_AIGPR *	_hoops_RIGC, _hoops_CRCP const *_hoops_SRCP, Image *image, Option_Value *options_list);
GLOBAL_FUNCTION _hoops_RCR * HI_Define_Shadow_Texture(_hoops_AIGPR * _hoops_RIGC, Image *image);
GLOBAL_FUNCTION void HI_Delete_Segment (_hoops_AIGPR *	_hoops_RIGC, _hoops_CRCP *_hoops_SRCP, void *info);
GLOBAL_FUNCTION void HI_Delete_User_Key (_hoops_AIGPR * _hoops_RIGC, _hoops_HPAH * item, Key _hoops_HSICA = -1);
GLOBAL_FUNCTION bool HI_Dequeue_Event (_hoops_AIGPR * _hoops_RIGC);
GLOBAL_FUNCTION char HI_Determine_Image_Format (_hoops_AIGPR * _hoops_RIGC, char const *format, void *_hoops_SPCIH);
GLOBAL_FUNCTION void HI_Disable_Timer_Interrupts (void);
GLOBAL_FUNCTION void HI_Dump_Code (char const *string);
GLOBAL_FUNCTION void HI_Edit_Karacters (_hoops_AIGPR *	_hoops_RIGC, _hoops_GGAGR *source, int key, char _hoops_PRHPH);
GLOBAL_FUNCTION void HI_Edit_Text (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HACC *text,
	int row,
	int column,
	int erase,
	int ndelete,
	int insert,
	unsigned short *_hoops_GHCIH);
GLOBAL_FUNCTION bool HI_Enable_Timer_Interrupts (void);
GLOBAL_FUNCTION int HI_Encoding_Is_Compatible (char from, char to);
GLOBAL_FUNCTION bool HI_Convert_Karacters_Encoding (int count, unsigned short const* in, unsigned short * _hoops_PAGR, char from, char to);
GLOBAL_FUNCTION bool HI_Equal_Strings (char const *a, char const *b);
GLOBAL_FUNCTION bool HI_Equal_Strings_To_Max (char const *a, int max, char const *b);
GLOBAL_FUNCTION void HI_Error_Exit (void);
GLOBAL_FUNCTION bool HI_Evaluate_Color (_hoops_AIGPR *	_hoops_RIGC, _hoops_HCRPR const *_hoops_SRGPH, Named_Material *_hoops_ISHIR, _hoops_CPAIR *_hoops_SAHCA, bool errors);
GLOBAL_FUNCTION float HI_Exponentiate (float _hoops_SHGCR, float _hoops_SCHPH);
GLOBAL_FUNCTION bool HI_Figure_General_Modelling_Mtx (float const *_hoops_CASPA, _hoops_HRPA alter *mat);
GLOBAL_FUNCTION bool HI_Figure_General_Texture_Mtx (float const *_hoops_CASPA, _hoops_HRPA alter *mat);
GLOBAL_FUNCTION bool HI_Figure_Geometry_Bounding (Geometry const * geom, Bounding alter & bounding);
GLOBAL_FUNCTION void HI_Figure_Offaxis_Rotation_Mtx (float x, float y, float z, float _hoops_RAHCR, _hoops_HRPA alter *mat);
GLOBAL_FUNCTION bool HI_Figure_Plane_From_Points (int count, Point const *_hoops_IAIRA, _hoops_ARPA alter *plane);
GLOBAL_FUNCTION void HI_Figure_Rotation_Matrix (float x, float y, float z, _hoops_HRPA alter *mat);
GLOBAL_FUNCTION void HI_Figure_Scale_Matrix (float x, float y, float z, _hoops_HRPA alter *mat);
GLOBAL_FUNCTION void HI_Figure_Segment_Bounding (_hoops_CRCP const * _hoops_SRCP, Bounding alter & bounding, Bounding alter & _hoops_HSRIR);
GLOBAL_FUNCTION void HI_Refresh_Segment_Bounding (_hoops_CRCP alter * _hoops_SRCP);
GLOBAL_FUNCTION void HI_Figure_Translation_Matrix (float x, float y, float z, _hoops_HRPA alter *mat);
GLOBAL_FUNCTION bool HI_Find_Application_Name (_hoops_HCRPR alter *name);
GLOBAL_FUNCTION Attribute * HI_Find_Attribute (_hoops_AIGPR * _hoops_RIGC, _hoops_HPAH const * item, Type type);
GLOBAL_FUNCTION _hoops_GGAGR * HI_Find_Actor (_hoops_AIGPR * _hoops_RIGC, char const *name);
GLOBAL_FUNCTION void HI_Find_Kanji_Char (char const *font, char const *data, unsigned short index, unsigned char const * alter *address);

GLOBAL_FUNCTION Attribute * HI_Find_Local_Attribute (_hoops_AIGPR * _hoops_RIGC, _hoops_SIRIR const * _hoops_ASIIR, Type type);
GLOBAL_FUNCTION Attribute * HI_Find_Net_Attribute (_hoops_AIGPR * _hoops_RIGC, _hoops_HPAH const * item, Type type, int _hoops_CCSPH=0, _hoops_CRACA const * control = null);
GLOBAL_FUNCTION Attribute * HI_Find_Net_Attribute_By_Path (_hoops_AIGPR * _hoops_RIGC, int count, _hoops_CRCP const **_hoops_SISAA, Type type, int _hoops_CCSPH=0, _hoops_CRACA const * control = null);
GLOBAL_FUNCTION Attribute * HI_Find_Attribute_And_Lock (
	_hoops_AIGPR *			_hoops_RIGC,
	_hoops_IPRRA						_hoops_HPGHH,
	int								_hoops_CCSPH=0,
	int								count=0,
	Key const *						keys=null,
	_hoops_HPAH **						target=null,
	_hoops_CRACA const *	control=null);

GLOBAL_FUNCTION bool HI_Find_Our_Open (_hoops_AIGPR *_hoops_RIGC);
GLOBAL_FUNCTION void HI_Find_Polygon_Plane (Polygon alter *polygon);
GLOBAL_FUNCTION unsigned short HI_Find_Raster_Max (unsigned short max, int width, char format, void *_hoops_CACIH);
GLOBAL_FUNCTION void HI_Find_Bounding (_hoops_AIGPR * _hoops_RIGC, _hoops_HPAH const * item, Bounding alter & _hoops_RCHS);
GLOBAL_FUNCTION Window * HI_Find_Scoping_Window (_hoops_CRCP const * _hoops_SRCP);
GLOBAL_FUNCTION void HI_Finish_Code_Generation (void);
GLOBAL_FUNCTION char const * HI_First_Substring_In_String (char const *_hoops_RHCIH, char const *string);
GLOBAL_FUNCTION char const * HI_CI_First_Substring_In_String (char const *_hoops_RHCIH, char const *string);
GLOBAL_FUNCTION void HI_Flush_Geometry (_hoops_AIGPR *	_hoops_RIGC, _hoops_CRCP *_hoops_SRCP, void *info);
GLOBAL_FUNCTION void HI_Really_Flush_Geometry (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *_hoops_SRCP, Integer32 flags);
GLOBAL_FUNCTION void HI_Flush_Driver_Config (char const *driver, char const *id, char const *version);
GLOBAL_FUNCTION bool HI_Names_All_Equal (_hoops_AAPIR *a, _hoops_AAPIR *b);
GLOBAL_FUNCTION bool HI_Font_Names_All_Equal (_hoops_IGPIR *a, _hoops_IGPIR *b);
GLOBAL_FUNCTION void HI_For_Each (_hoops_AIGPR * _hoops_RIGC, char const *spec, bool required, _hoops_CRRHH action, void *param);
GLOBAL_FUNCTION _hoops_GGAGR * HI_Force_Find_Driver (_hoops_AIGPR * _hoops_RIGC, char const *name);
GLOBAL_FUNCTION _hoops_GGAGR * HI_Force_Find_Owner_Actor (_hoops_AIGPR * _hoops_RIGC, char const *segname, _hoops_CRCP **_hoops_PRCPH);
GLOBAL_FUNCTION _hoops_GGAGR * HI_Force_Find_Path_Actor (_hoops_AIGPR * _hoops_RIGC, int count, _hoops_CRCP const ** _hoops_SISAA, _hoops_CRCP **_hoops_PRCPH);
GLOBAL_FUNCTION void HI_Format_Generic_Size_String (_hoops_HCAIR const *size, char alter *list, int _hoops_GGCIR);
GLOBAL_FUNCTION void HI_Free_Bounding (Bounding *bounding);
GLOBAL_FUNCTION void HI_Free_Callback_List (_hoops_IHACR *item);
GLOBAL_FUNCTION void HI_Free_Include_Chain (_hoops_RISAP *_hoops_HACAH);
GLOBAL_FUNCTION void HI_Free_Font_Names (_hoops_IGPIR *_hoops_HGPIR);
GLOBAL_FUNCTION void HI_Free_Kanji_Data (void);
GLOBAL_FUNCTION void HI_Free_Material_Names (Named_Material *mat, int length);
GLOBAL_FUNCTION void HI_Free_Option_List (_hoops_AIGPR * _hoops_RIGC, Option_Value *listptr);
GLOBAL_FUNCTION void HI_Free_Path (_hoops_RSAPR *_hoops_CIPPR);
GLOBAL_FUNCTION void HI_Free_Polyedge_List (Polyedge *_hoops_RSGHR);
GLOBAL_FUNCTION void HI_Free_Polymarker (Polymarker *pm);
GLOBAL_FUNCTION void HI_Free_Polymarker_List (Polymarker *_hoops_RSGHR);
GLOBAL_FUNCTION void HI_Free_Time (void);
GLOBAL_FUNCTION void HI_Free_Tristrip_List (Tristrip *_hoops_RSGHR);
GLOBAL_FUNCTION void HI_Free_Wedge_Tree (_hoops_RGASA *tree);
GLOBAL_FUNCTION void HI_Free_Wings (int count, _hoops_GPCIH **_hoops_RPCIH);
GLOBAL_FUNCTION void HI_Free_Text_Info (Text_Info * text_info);
GLOBAL_FUNCTION void HI_Gather_Modelling (Attribute *_hoops_ASGPR, Attribute **_hoops_PSACR);
GLOBAL_FUNCTION void HI_Generate_Error (
	_hoops_AIGPR *	_hoops_RIGC,
	int category, int specific, int severity,
	int msgc, char const **msgv);
GLOBAL_FUNCTION void HI_Generate_Untrappable_Error (
	_hoops_AIGPR *	_hoops_RIGC,
	int category, int specific, int severity,
	int msgc, char const **msgv);
GLOBAL_FUNCTION void HI_Generic_Delete (_hoops_AIGPR *_hoops_RIGC, _hoops_HPAH *_hoops_CISIR);
GLOBAL_FUNCTION void HI_Flush_Textures (_hoops_AIGPR *_hoops_RIGC, _hoops_CPAIR *_hoops_SAHCA, bool _hoops_AHCIH);
GLOBAL_FUNCTION bool HI_Get_Filename (_hoops_CRCP *_hoops_SRCP, Metafile *_hoops_PHCIH, _hoops_IRIPH *_hoops_GHIPH, _hoops_HCRPR *_hoops_HHCIH);


GLOBAL_FUNCTION void HI_HLS_To_RGB (_hoops_PACHR const *_hoops_HACHR, RGB *rgb);
GLOBAL_FUNCTION void HI_HOOPS_Version (char *data, int _hoops_IHCIH);
GLOBAL_FUNCTION bool HI_Has_Local_Key (_hoops_CRCP const * owner, Key _hoops_HSICA);
GLOBAL_FUNCTION void HI_Ident_44 (float alter *outp);
GLOBAL_FUNCTION void HI_Ident_Matrix (_hoops_HRPA alter *matrix);
GLOBAL_FUNCTION void HI_Default_Camera (_hoops_HHRA * _hoops_SPH, _hoops_HHRA const * _hoops_HIPCR = null);
GLOBAL_FUNCTION void HI_Init_Driver (_hoops_AIGPR *_hoops_RIGC, _hoops_GGAGR *driver, bool _hoops_CHCIH);
GLOBAL_FUNCTION void HI_Attach_Automatic_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP alter * _hoops_SRCP);
GLOBAL_FUNCTION _hoops_GGAGR * HI_Create_Actor(_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP * _hoops_SRCP, Driver_Action action);
GLOBAL_FUNCTION void HI_Init_Internal_Data (void);
GLOBAL_FUNCTION void HI_Init_Time (void);
GLOBAL_FUNCTION void HI_Initialize_Edge_Attributes (Polyhedron *_hoops_IPRI, unsigned short which);
GLOBAL_FUNCTION void HI_Initialize_Face_Attributes (Polyhedron *_hoops_IPRI, unsigned short which);
GLOBAL_FUNCTION void HI_Initialize_Vertex_Attributes (Polyhedron *_hoops_IPRI, unsigned int which, int data);
GLOBAL_FUNCTION Geometry * HI_Insert_Geometry (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *owner,
	Geometry *geometry,
	bool _hoops_SHCIH = false,
	Integer32 _hoops_CPGPR = 0,
	bool _hoops_CCHAH = true);
GLOBAL_FUNCTION Integer32 HI_Determine_Geometry_Maybes (Geometry const * geometry);
GLOBAL_FUNCTION void HI_Generate_NURBS_Polyline (
	_hoops_PIRGR const *curve,
	_hoops_PARC const *control,
	_hoops_HRPA const *matrix,
	Polyline *p,
	float _hoops_CGHHH);
GLOBAL_FUNCTION void HI_Interpret_Environment (_hoops_AIGPR * _hoops_RIGC, bool _hoops_GICIH);
GLOBAL_FUNCTION int HI_Intersect_Line_Segments_2D (Point *_hoops_GGIAR,
		 Point *p1,
		 Point *_hoops_RICIH,
		 Point *_hoops_AICIH,
		 Point *_hoops_RSPSA);
GLOBAL_FUNCTION Key HI_Insert_Image_By_Row (_hoops_AIGPR * _hoops_RIGC, float x, float y, float z, char const *format, int width, int height, void **_hoops_PICIH);
GLOBAL_FUNCTION char const * HI_Last_Substring_In_String (char const *_hoops_RHCIH, char const *string);
GLOBAL_FUNCTION char const * HI_CI_Last_Substring_In_String (char const *_hoops_RHCIH, char const *string);

GLOBAL_FUNCTION _hoops_SRPPR ** HI_Look_Up_Alias (_hoops_AIGPR * _hoops_RIGC, char const *name, int length);
GLOBAL_FUNCTION _hoops_HCHIR ** HI_Look_Up_Callback_Name (_hoops_AIGPR * _hoops_RIGC, char const *name, int length);
GLOBAL_FUNCTION _hoops_RSHIR ** HI_Look_Up_Color (_hoops_AIGPR *	_hoops_RIGC, char const *name, int length);
GLOBAL_FUNCTION _hoops_PGIIR ** HI_Look_Up_Font (_hoops_AIGPR * _hoops_RIGC, char const *name, int length);
GLOBAL_FUNCTION _hoops_RCR * HI_Look_Up_Texture (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP const *_hoops_SRCP, _hoops_HCRPR const* name);
GLOBAL_FUNCTION void HI_LEA_Pattern_Delete (Polyhedron *_hoops_IPRI, _hoops_HHHIR *pattern);
GLOBAL_FUNCTION _hoops_HHHIR * HI_LEA_Pattern_Init (Polyhedron * _hoops_IPRI, _hoops_HCRPR const * name);
GLOBAL_FUNCTION _hoops_HHHIR * HI_LEA_Pattern_Lookup (Polyhedron const *_hoops_IPRI, unsigned char id);
GLOBAL_FUNCTION void HI_LVA_Symbol_Delete (Polyhedron *_hoops_IPRI, _hoops_RPHIR *symbol);
GLOBAL_FUNCTION _hoops_RPHIR * HI_LVA_Symbol_Init (Polyhedron * _hoops_IPRI, _hoops_HCRPR const * name);
GLOBAL_FUNCTION _hoops_RPHIR * HI_LVA_Symbol_Lookup (Polyhedron const *_hoops_IPRI, unsigned char id);
GLOBAL_FUNCTION void HI_Make_It_Fatal (int category,
		 int specific,
		 int severity,
		 int msgc,
		 char const * const *msgv,
		 int c,
		 char const * const *v);
GLOBAL_FUNCTION void HI_Make_Unique_Filename (_hoops_HCRPR alter *name);
GLOBAL_FUNCTION void HI_Matmul_43_by_43 (float const *leftp, float const *rightp, float alter *resultp);
GLOBAL_FUNCTION void HI_Matmul_44_by_44 (float const *leftp, float const *rightp, float alter *resultp);
GLOBAL_FUNCTION _hoops_IHACR * HI_Merge_Callback_Lists (_hoops_IHACR const * _hoops_RSACR, _hoops_IHACR const * _hoops_ASACR);
GLOBAL_FUNCTION void HI_Merge_Colors (_hoops_SSGI alter *original, _hoops_ACSGA const *	_hoops_AARGA, _hoops_PIGRA const * locks, _hoops_RHAH const *_hoops_SPRAR);

GLOBAL_FUNCTION void HI_More_Cutting_Planes (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *_hoops_SRCP, int count);
GLOBAL_FUNCTION void HI_More_Light (_hoops_AIGPR *	_hoops_RIGC, _hoops_CRCP *_hoops_SRCP, int count);
GLOBAL_FUNCTION void HI_More_Transparencies (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *_hoops_SRCP, int count);
GLOBAL_FUNCTION void HI_More_Shadows (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *_hoops_SRCP, int count);

GLOBAL_FUNCTION void HI_Less_Cutting_Planes (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *_hoops_SRCP, int count);
GLOBAL_FUNCTION void HI_Less_Light (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *_hoops_SRCP, int count);
GLOBAL_FUNCTION void HI_Less_Transparencies (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *_hoops_SRCP, int count);
GLOBAL_FUNCTION void HI_Less_Shadows (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *_hoops_SRCP, int count);

GLOBAL_FUNCTION void HI_Multiply_Matrices (_hoops_HRPA const *left, _hoops_HRPA const *right, _hoops_HRPA alter *result);
GLOBAL_FUNCTION void HI_Normal_Exit (void);
GLOBAL_FUNCTION bool HI_Normalize (Vector alter *_hoops_GIHI);
GLOBAL_FUNCTION bool HI_Normalize_Vectors (int count, Vector alter *_hoops_GIHI);
GLOBAL_FUNCTION bool HI_Normalize_Plane (_hoops_ARPA alter *plane);
GLOBAL_FUNCTION void HI_Not_When_Streamed (_hoops_CRCP *_hoops_SRCP, char const *_hoops_CHCIP);
GLOBAL_FUNCTION _hoops_CRCP * HI_One_Segment_Search (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	bool					required);
GLOBAL_FUNCTION bool HI_Open_Directory (_hoops_HCRPR alter *name,
		 _hoops_HCRPR const *filter,
		 int _hoops_IIIHH,
		 int _hoops_CIIHH,
		 void alter **_hoops_PSIHH,
		 _hoops_HCRPR alter *_hoops_GGHGA,
		 _hoops_HCRPR alter *_hoops_RGHGA);
GLOBAL_FUNCTION bool HI_Open_File (_hoops_HCRPR alter *name,
		 int _hoops_CCHHH,
		 void **_hoops_CRIPH,
		 bool _hoops_SCHHH,
		 _hoops_HCRPR alter *_hoops_GGHGA,
		 _hoops_HCRPR alter *_hoops_RGHGA);
GLOBAL_FUNCTION void HI_Orthogonalize_Matrix (_hoops_HRPA alter *matrix);
GLOBAL_FUNCTION Key HI_Output_Parse (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_HICIH,
	char const *			_hoops_IICIH,
	_hoops_CICIH		action,
	void *					info);
GLOBAL_FUNCTION bool HI_Parse_Color_Map (_hoops_AIGPR * _hoops_RIGC, char const *_hoops_PRHRA, _hoops_RHAH *_hoops_APHCR);
GLOBAL_FUNCTION bool HI_Parse_Color_Map_By_Value (_hoops_AIGPR * _hoops_RIGC, char const *style, int count, RGB const *in, _hoops_RHAH *_hoops_APHCR);

GLOBAL_FUNCTION void HI_Parse_Filename (_hoops_HCRPR alter *name,
		 _hoops_HCRPR alter *_hoops_PSHAP,
		 _hoops_HCRPR alter *file,
		 _hoops_HCRPR alter *_hoops_GPIHH);
GLOBAL_FUNCTION bool HI_Parse_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *_hoops_SICIH,
	_hoops_GCIIR *_hoops_SPHHR,
	Option_Value **_hoops_GCCIH,
	int flags);
GLOBAL_FUNCTION bool HI_Parse_KOptions (
	_hoops_AIGPR *	_hoops_RIGC,
	unsigned short const *_hoops_SICIH,
	_hoops_GCIIR *_hoops_SPHHR,
	Option_Value **_hoops_GCCIH,
	int flags);
GLOBAL_FUNCTION _hoops_RSAPR * HI_Parse_Path (
		_hoops_AIGPR *		_hoops_RIGC,
		char const *_hoops_RCCIH,
		int flags);
GLOBAL_FUNCTION void HI_Pause_Errors (int category,
		 int specific,
		 int severity,
		 int msgc,
		 char const * const * msgv,
		 int c,
		 char const * const * v);
GLOBAL_FUNCTION void HI_Point_On_NURBS_Curve (_hoops_PIRGR const *curve, float u, Point *_hoops_PPHPA);
GLOBAL_FUNCTION void HI_Propagate_Activity (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_SIHIR *_hoops_CISIR,
	Integer32 which);
GLOBAL_FUNCTION void HI_Propagate_Bounding (_hoops_AIGPR *	_hoops_RIGC, _hoops_CRCP *_hoops_SRCP, Bounding const & bounding, _hoops_CRCP const *_hoops_ACCIH);
GLOBAL_FUNCTION void HI_Antiquate_Bounding (_hoops_CRCP *_hoops_SRCP, bool _hoops_PCCIH, bool _hoops_HCCIH=true);
GLOBAL_FUNCTION void HI_Propagate_Maybes (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *_hoops_SRCP, Integer32 what);
GLOBAL_FUNCTION void HI_Propagate_Maybes_Across_Styles (_hoops_CRCP * _hoops_SRCP, Integer32 what);
GLOBAL_FUNCTION void HI_Propagate_Scoped_Activity (_hoops_AIGPR *_hoops_RIGC, _hoops_SIHIR *_hoops_CISIR, Integer32 which, _hoops_PACIR const *scope);


GLOBAL_FUNCTION void HI_RGB_To_HLS (RGB const *rgb, _hoops_PACHR *_hoops_HACHR);
GLOBAL_FUNCTION int HI_Rank_Polygon (Point const *points, int const *face_list, int const *_hoops_ICCIH);
GLOBAL_FUNCTION bool HI_Read_Directory (
	void alter *_hoops_PSIHH,
	_hoops_HCRPR alter *filename,
	_hoops_HCRPR alter *_hoops_GGHGA,
	_hoops_HCRPR alter *_hoops_RGHGA);
GLOBAL_FUNCTION bool HI_Read_File_Buffer (
	void alter *_hoops_CRIPH,
	char alter *buffer,
	int alter *_hoops_GSHHH,
	int _hoops_RSHHH,
	_hoops_HCRPR alter *_hoops_GGHGA,
	_hoops_HCRPR alter *_hoops_RGHGA);
GLOBAL_FUNCTION void HI_Disentangle (_hoops_AIGPR * _hoops_RIGC, _hoops_HPAH *thing);
GLOBAL_FUNCTION void HI_Really_Report_Error (int category, int specific, int severity, int msgc, char **msgv, int c, char **v);
GLOBAL_FUNCTION void HI_Record_Texture_Definition(_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP * _hoops_SRCP, _hoops_RCR *txr);
GLOBAL_FUNCTION void HI_Redraw_Attribute (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *_hoops_SRCP, Type type, Attribute *_hoops_PISCA, Attribute *_hoops_SISCA);
GLOBAL_FUNCTION void HI_Redraw_Downstream (_hoops_AIGPR *	_hoops_RIGC, _hoops_SIHIR *_hoops_CISIR, Integer32 which, _hoops_PACIR const *scope);
GLOBAL_FUNCTION void HI_Redraw_Style (_hoops_AIGPR * _hoops_RIGC, Style *style);
GLOBAL_FUNCTION void HI_Delete_Style_Attributes (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP * _hoops_SRCP, Style *	style);
GLOBAL_FUNCTION Key HI_Rename_Segment (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *_hoops_SRCP,
	_hoops_CRCP *newowner,
	Subsegment **_hoops_ASRGR,
	Subsegment *_hoops_AIGSA,
	_hoops_HCRPR *newname,
	bool _hoops_PIGSA,
	void *info);
GLOBAL_FUNCTION void HI_Report_File_Error (_hoops_IRIPH *_hoops_GHIPH);
GLOBAL_FUNCTION void HI_Report_File_Error_With_Names (_hoops_IRIPH *_hoops_GHIPH, _hoops_HCRPR *_hoops_CCCIH, _hoops_HCRPR *_hoops_SCCIH);
GLOBAL_FUNCTION void HI_Return_Chars (char *_hoops_PAGR, int _hoops_ICHPP, char const *in, int _hoops_GSCIH);
GLOBAL_FUNCTION void HI_Return_Kars (char *_hoops_PAGR, int _hoops_ICHPP, unsigned short const *in, int _hoops_GSCIH, char encoding);
GLOBAL_FUNCTION void HI_Return_Karacters (unsigned short *_hoops_PAGR, int _hoops_ICHPP, unsigned short const *in, int _hoops_GSCIH);
GLOBAL_FUNCTION void HI_Return_Sprintf1 (char *_hoops_ASAPR, int length, char const *spec, void const *item);
GLOBAL_FUNCTION void HI_Scale_And_Translate_Matrix (_hoops_HRPA const *in,
		 float _hoops_GPCH,
		 float _hoops_RPCH,
		 float sz,
		 float tx,
		 float ty,
		 float tz,
		 _hoops_HRPA alter *_hoops_PAGR);
GLOBAL_FUNCTION char const * HI_Scan_Boolean (_hoops_AIGPR * _hoops_RIGC, char const **_hoops_RAARA, char const *_hoops_SSRPR, bool *resultp);
GLOBAL_FUNCTION char const * HI_Scan_Float (_hoops_AIGPR * _hoops_RIGC, char const **_hoops_RAARA, char const *_hoops_SSRPR, float *resultp);
GLOBAL_FUNCTION char const * HI_Scan_Integer (_hoops_AIGPR * _hoops_RIGC, char const **_hoops_RAARA, char const *_hoops_SSRPR, int *resultp);
GLOBAL_FUNCTION char const * HI_Scan_Long (_hoops_AIGPR * _hoops_RIGC, char const **_hoops_RAARA, char const *_hoops_SSRPR, long *resultp);
GLOBAL_FUNCTION char const * HI_Scan_Key (_hoops_AIGPR * _hoops_RIGC, char const **_hoops_RAARA, char const *_hoops_SSRPR, Key *resultp);
GLOBAL_FUNCTION char const * HI_Scan_Ptr (_hoops_AIGPR * _hoops_RIGC, char const **_hoops_RAARA, char const *_hoops_SSRPR, POINTER_SIZED_INT *resultp);
GLOBAL_FUNCTION char const * HI_Scan_Name (_hoops_AIGPR * _hoops_RIGC, char const **_hoops_RAARA, char const *_hoops_SSRPR, _hoops_HCRPR *name);
GLOBAL_FUNCTION char const * HI_Scan_String (_hoops_AIGPR * _hoops_RIGC, char const **_hoops_RAARA, char const *_hoops_SSRPR, _hoops_HCRPR *name);
GLOBAL_FUNCTION char const * HI_Scan_Generic_Size(_hoops_AIGPR * _hoops_RIGC, _hoops_HCAIR *size, char const *options, char const *type);
GLOBAL_FUNCTION void HI_Set_And_Clear_Flags (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP *segment, void *info);
GLOBAL_FUNCTION bool HI_Set_Attribute (_hoops_AIGPR * _hoops_RIGC, _hoops_HPAH *node, Type type, _hoops_RSCIH _hoops_ASCIH, Attribute * _hoops_ASGPR);
GLOBAL_FUNCTION void HI_Set_Default_Attributes (_hoops_AIGPR *	_hoops_RIGC);
GLOBAL_FUNCTION void HI_Set_Delayed_Activity (_hoops_CRCP const * _hoops_GIPIA, Integer32 _hoops_PSCIH,
												Geometry const * geometry, Integer32 _hoops_SSSAP);
GLOBAL_FUNCTION void HI_Queue_Flush_Derived_Normals (_hoops_GGAGR const *_hoops_GHRI, Polyhedron alter *_hoops_IPRI);
GLOBAL_FUNCTION void HI_Flush_Derived_Normals (_hoops_AIGPR * _hoops_RIGC, Polyhedron alter *_hoops_IPRI);
GLOBAL_FUNCTION void HI_Set_User_Key (_hoops_AIGPR * _hoops_RIGC, _hoops_HPAH * item, int offset, Key key, bool _hoops_HSCIH);
GLOBAL_FUNCTION void HI_Show_Callback (_hoops_GCHIR *callback, char *spec, int _hoops_CSACR, void **_hoops_AIACR);
GLOBAL_FUNCTION void HI_Show_Driver_Options (_hoops_GAPIR *_hoops_PAICA, char *listptr, int _hoops_GGCIR);
GLOBAL_FUNCTION void HI_Show_Encoding_Type (char *string, int length, char encoding);
GLOBAL_FUNCTION bool HI_Show_Environment (char const *which, _hoops_HCRPR alter *result);
GLOBAL_FUNCTION void HI_Show_Heuristics (_hoops_GHAIR const *heuristics, char *listptr, int _hoops_GGCIR);
GLOBAL_FUNCTION void HI_Show_Locater_Action (int _hoops_IHAPH, char *type, int _hoops_SCPRA);
GLOBAL_FUNCTION char * HI_Show_Material (char *_hoops_ASAPR, char const *_hoops_PSAPR, Named_Material const *_hoops_ISHIR, Option_Value const *option, bool _hoops_GIPRA);
GLOBAL_FUNCTION void HI_Show_Rendering_Options (_hoops_RHAIR *_hoops_RCIHP, char *listptr, int _hoops_GGCIR);
GLOBAL_FUNCTION void HI_Show_Selectability (_hoops_ASAIR *_hoops_GSCSP, char *spec, int _hoops_CSACR);
GLOBAL_FUNCTION void HI_Show_Text_Alignment (_hoops_GGPIR *_hoops_CAICA, char *result, int _hoops_RIAGA);
GLOBAL_FUNCTION void HI_Show_Text_Font (_hoops_AGPIR *_hoops_CAICA, char *result, int _hoops_RIAGA);
GLOBAL_FUNCTION bool HI_Show_Texture (	
		_hoops_AIGPR * _hoops_RIGC, 
		_hoops_RCR *texture, 
		char *definition, 
		int _hoops_ISCIH, 
		char *shader_source, 
		int _hoops_CSCIH,
		bool _hoops_SSCIH, 
		const char *opt);
GLOBAL_FUNCTION void HI_Show_Type_Name (int _hoops_GGSIH, char *type, int length);
GLOBAL_FUNCTION void HI_Show_Visibility (_hoops_RSAIR *vis, char *spec, int _hoops_CSACR);
GLOBAL_FUNCTION void HI_SinCos (float _hoops_RAHCR, float *_hoops_GGHCR, float *_hoops_AGHCR);
GLOBAL_FUNCTION void HI_Sleep (_hoops_GSPGR _hoops_SPAPR);
GLOBAL_FUNCTION char alter * HI_Sprintf1 (char alter *_hoops_ASAPR, char const *_hoops_PSAPR, char const *spec, void const *ptr);

GLOBAL_FUNCTION char * HI_Sprintf4 (
	_hoops_AIGPR * _hoops_RIGC,
	char *buf,
	char const *spec,
	int _hoops_CPIPP,
	int _hoops_SPIPP,
	void const *_hoops_AIPPA,
	void const *_hoops_PIPPA);

GLOBAL_FUNCTION float HI_Sqrt (float _hoops_HAGR);
GLOBAL_FUNCTION void HI_Start_Code_Generation (void);
GLOBAL_FUNCTION void HI_Start_Hoops (char const *_hoops_SCPGA);
GLOBAL_FUNCTION void HI_Start_System_Specific (_hoops_AIGPR *_hoops_RIGC);
GLOBAL_FUNCTION void HI_Stop_System_Specific (void);
GLOBAL_FUNCTION int HI_String_Length (char const *start);

GLOBAL_FUNCTION bool HI_Synch_File_Buffer (void alter *_hoops_CRIPH,
		 int alter *_hoops_SHGGR,
		 _hoops_HCRPR alter *_hoops_GGHGA,
		 _hoops_HCRPR alter *_hoops_RGHGA);
GLOBAL_FUNCTION void HI_Table_Insert_Geometry (_hoops_CRCP *_hoops_SRCP, Geometry *geometry);
GLOBAL_FUNCTION void HI_Table_Insert_OO_Geometry (_hoops_CRCP *_hoops_SRCP, Geometry *geometry);
GLOBAL_FUNCTION void HI_Table_Remove_Geometry (Geometry *geometry);
GLOBAL_FUNCTION int HI_Take_A_Poll (_hoops_AIGPR *	_hoops_RIGC, _hoops_GGAGR const *driver, _hoops_GSPGR now, bool _hoops_CCRPH);
GLOBAL_FUNCTION void HI_Polygon_Triangle_Collector (_hoops_RGSIH alter &_hoops_ARGC, Integer32 _hoops_ISPI, Integer32 _hoops_CSPI, Integer32 _hoops_SSPI);
GLOBAL_FUNCTION void HI_Polygon_Merge (_hoops_AIGPR * _hoops_RIGC, _hoops_RGSIH alter *_hoops_ARGC);
GLOBAL_FUNCTION bool HI_Triangulate_Face (Point const *points,
		 Vector const *normal,
		 int const *face_list,
		 int const *_hoops_ICCIH,
		 _hoops_RRCIH triangle_action,
		 void *_hoops_CRHCP);
GLOBAL_FUNCTION bool HI_Triangulate_Face_X (Point const *points,
		 Vector const *normal,
		 int const *face_list,
		 int const *_hoops_ICCIH,
		 _hoops_ARCIH triangle_action,
		 void *_hoops_CRHCP);
GLOBAL_FUNCTION void HI_UnDefine_Colors (_hoops_AIGPR * _hoops_RIGC, char const *string);
GLOBAL_FUNCTION void HI_UnDefine_Texture (_hoops_AIGPR * _hoops_RIGC, _hoops_RCR * texture);
GLOBAL_FUNCTION void HI_Update_Actor_List (_hoops_AIGPR * _hoops_RIGC);
GLOBAL_FUNCTION void HI_Update_Events (_hoops_AIGPR * _hoops_RIGC);
GLOBAL_FUNCTION void HI_Update_Interrupted (_hoops_AIGPR * _hoops_RIGC);
GLOBAL_FUNCTION bool HI_Validate_Face_List (int point_count, int face_list_length, int const *face_list, int *_hoops_AGSIH);
GLOBAL_FUNCTION bool HI_Validate_Glyph (Counted_Pointer<_hoops_GRCAP> alter & glyph);
GLOBAL_FUNCTION bool HI_Validate_Line_Style (_hoops_AIGPR * _hoops_RIGC, Counted_Pointer<_hoops_HPCAP> alter & line_style);
GLOBAL_FUNCTION void HI_Validate_Inverted_Rasters (Image *image);
GLOBAL_FUNCTION void HI_Validate_Matrix_Adjoint (_hoops_HRPA const *matrix);
GLOBAL_FUNCTION void HI_Validate_Matrix_NEG3X3 (_hoops_HRPA alter *matrix);
GLOBAL_FUNCTION void HI_Vertex_Complaint (int offset, Polyhedron *_hoops_IPRI);
GLOBAL_FUNCTION _hoops_GSPGR HI_What_Time (void);
GLOBAL_FUNCTION bool HI_Wild_Equal_Strings (char const *a, char const *p);
GLOBAL_FUNCTION int HI_Wings_Intersect (int _hoops_PGSIH, _hoops_GPCIH **_hoops_HGSIH, int _hoops_IGSIH, _hoops_GPCIH **_hoops_CGSIH);
GLOBAL_FUNCTION bool HI_Would_Be_Include_Loop (_hoops_CRCP *owner, _hoops_CRCP *_hoops_HCPIH);
GLOBAL_FUNCTION bool HI_Write_File_Buffer (void alter *_hoops_CRIPH,
		 char const *buffer,
		 int _hoops_SHGGR,
		 _hoops_HCRPR alter *_hoops_GGHGA,
		 _hoops_HCRPR alter *_hoops_RGHGA);
GLOBAL_FUNCTION bool HI_Compare_Bounding (
		 Bounding const & _hoops_IHHI,
		 Bounding const & _hoops_CHHI);
GLOBAL_FUNCTION bool HI_Face_List_From_Tristrips (_hoops_AIGPR * _hoops_RIGC, Shell *_hoops_SPHPR);
GLOBAL_FUNCTION void HI_Tessellate_NURBS_Surface (
	_hoops_AIGPR * _hoops_RIGC,
	_hoops_APPGR const *_hoops_SSHIH,
	_hoops_AIIAA const *configs);


GLOBAL_FUNCTION void HI_Free_Region_Set (
		UV_Region_Set *set);
GLOBAL_FUNCTION UV_Region_Set * HI_Generate_Convex_Region_Set (
		int count,
		UV_Point const *points);
GLOBAL_FUNCTION UV_Region_Set * HI_Generate_Complex_Region_Set (
		int point_count,
		UV_Point const *points,
		int face_list_length,
		int const * face_list,
		bool _hoops_SGSIH);
GLOBAL_FUNCTION UV_Region_Set * HI_Generate_Polygonal_Region_Set (
		int count,
		UV_Point const *points,
		bool _hoops_SGSIH);
GLOBAL_FUNCTION UV_Region_Set * HI_Generate_Rectangular_Regions (
		float start_u,
		float end_u,
		float _hoops_GRSIH,
		float _hoops_RRSIH,
		int _hoops_ARSIH,
		int _hoops_PRSIH);
GLOBAL_FUNCTION void HI_Subtract_Region_From_Region_Set (
		UV_Region_Set *set,
		UV_Region_Set *_hoops_HRSIH); /* _hoops_RCIC */
GLOBAL_FUNCTION void HI_Convert_Regions_To_Facelist (
		UV_Region_Set const *set,
		int **listptr,
		int *length,
		int *count);

GLOBAL_FUNCTION void HI_Delete_Trim (UV_Trim *node);


GLOBAL_FUNCTION void HI_Not_When_LOD (void);
GLOBAL_FUNCTION void HI_Resort_Tristrips (Polyhedron *_hoops_IPRI, int region);
GLOBAL_FUNCTION void HI_Delete_Shell_Selection_Cache (void *_hoops_CSC);
GLOBAL_FUNCTION void HI_Delete_Intersect_Polyline_Cache (void *_hoops_CSC);
GLOBAL_FUNCTION void *HI_New_Point_Inside_Shell_Cache (void);
GLOBAL_FUNCTION void HI_Delete_Point_Inside_Shell_Cache (void *_hoops_CSC);

GLOBAL_FUNCTION _hoops_AGHIR * HI_Initialize_PCA_Vertex_Attributes (
						PolyCylinder alter * _hoops_HSPIR, unsigned char which);

GLOBAL_FUNCTION void HI_Enumerate_Region_Set_Edges (
		UV_Region_Set const *set,
		int alter *count,
		UV_Edge alter ***_hoops_GRCPR);
GLOBAL_FUNCTION void HI_Split_Region_Set_Edge (
		UV_Region_Set alter *set,
		UV_Edge alter *edge,
		int *count,
		UV_Edge alter ***_hoops_GRCPR);
GLOBAL_FUNCTION void HI_Midpoint_Split_Triangle (
		UV_Region_Set alter *set,
		UV_Region alter *region,
		int alter *_hoops_IRSIH,
		UV_Region alter ***_hoops_CRSIH);
GLOBAL_FUNCTION void HI_Triangulate_Region (
		UV_Region_Set alter *set,
		UV_Region alter *region);
GLOBAL_FUNCTION void HI_Midpoint_Split_One_Triangle (
		UV_Region_Set alter *set,
		UV_Edge alter *edge,
		int *count,
		UV_Edge alter ***_hoops_GRCPR);
GLOBAL_FUNCTION UV_Region_Set * HI_Generate_Triangular_Regions (
		float			start_u,
		float			end_u,
		float			_hoops_GRSIH,
		float			_hoops_RRSIH,
		int				_hoops_ARSIH,
		int				_hoops_PRSIH);
GLOBAL_FUNCTION void HI_Get_UV_Region_Triangle (
		UV_Region_Set alter *set,
		UV_Region alter *region,
		UV_Edge alter **a,
		UV_Edge alter **b,
		UV_Edge alter **c);

GLOBAL_FUNCTION int HI_Compute_Intersect_Polyline (
	_hoops_AIGPR *	_hoops_RIGC,
	int point_count1,
	Point const *points1,
	int face_list_length1,
	int const *face_list1,
	int point_count2,
	Point const *points2,
	int face_list_length2,
	int const *face_list2,
	int alter *polyline_count,
	int alter *polyline_lengths,
	int alter *_hoops_RRPPA,
	Point alter *polyline_points,
	bool _hoops_IRHPA);


GLOBAL_FUNCTION bool HI_Compute_Point_Inside_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	Point const *pt,
	int point_count,
	Point const *points,
	int face_list_length,
	int const *face_list);

GLOBAL_FUNCTION bool HI_Compute_Point_On_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	Point const *pt,
	double tolerance,
	int point_count,
	Point const *points,
	int face_list_length,
	int const *face_list);

GLOBAL_FUNCTION void HI_Compute_Points_Inside_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	int pcount,
	Point const *pt,
	Point const *_hoops_SRSIH,
	int point_count,
	Point const *points,
	int face_list_length,
	int const *face_list,
	char const *options,
	int *result);

GLOBAL_FUNCTION int HI_Compute_Points_On_Shell (
	_hoops_AIGPR * _hoops_RIGC,
	int pcount,
	Point const *pt,
	double tolerance,
	int point_count,
	Point const *points,
	int face_list_length,
	int const *face_list,
	int *result);
GLOBAL_FUNCTION int HI_Compute_Points_Distance_From_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	int pcount,
	Point const *pt,
	double tolerance,
	int point_count,
	Point const *points,
	int face_list_length,
	int const *face_list,
	const char *options,
	float *result,
	int *_hoops_GASIH
	);
GLOBAL_FUNCTION void HI_Accumulate_Segment_Bounding (
	_hoops_AIGPR * _hoops_RIGC,
	_hoops_CRCP const * _hoops_SRCP,
	Bounding alter & bounding,
	_hoops_HRPA const * matrix,
	Integer32 _hoops_PRCAA,
	Integer32 flags);

GLOBAL_FUNCTION void HI_Reset_Strip_Flags (
		Polyhedron * _hoops_IPRI);

GLOBAL_FUNCTION void HI_Reset_Driver_Config_SS (void);

GLOBAL_FUNCTION void HI_Fake_NURBS_Surface_Configs (
		_hoops_AIIAA alter *configs);
GLOBAL_FUNCTION void HI_Compute_Transformed_Points (
		int count,
		Point const *points,
		float const *matp,
		Point *result);
GLOBAL_FUNCTION void HI_Compute_Transformed_Vectors (
		int count,
		Vector const *_hoops_CIIRR,
		float const *matp,
		Vector *result);
GLOBAL_FUNCTION void HI_Compute_Transformed_Planes (
		int count,
		_hoops_ARPA const *_hoops_CIIRR,
		_hoops_HRPA const *mat,
		_hoops_ARPA *result);
GLOBAL_FUNCTION bool HI_Add_Geometry_Bounding (
		_hoops_AIGPR * _hoops_RIGC,
		Geometry const * geometry,
		_hoops_ISGI const * matrix,
		Integer32 _hoops_RGP,
		_hoops_PIGRA *locks,
		Integer32 flags,
		Bounding alter & bounding);
GLOBAL_FUNCTION bool HI_Accumulate_Bounding_Attributes (
		Attribute * _hoops_ASGPR,
		_hoops_ISGI ** _hoops_PSACR,
		Integer32 * _hoops_RGP,
		_hoops_PIGRA * locks,
		unsigned int alter * conditions,
		_hoops_HGIAA _hoops_RASIH);
GLOBAL_FUNCTION void HI_Compute_Polyhedron_LOD(
		_hoops_AIGPR *	_hoops_RIGC,
		Polyhedron *phon,
		int _hoops_GAIIH,
		int _hoops_AASIH,
		_hoops_RRPHA _hoops_ARPHA,
		float _hoops_PRPHA,
		bool _hoops_HRPHA,
		int _hoops_HISRP,
		int _hoops_RHPHA);

GLOBAL_FUNCTION void HI_Compute_LOD(
		_hoops_AIGPR *	_hoops_RIGC,
		_hoops_RRPHA _hoops_ARPHA,
		float _hoops_PRPHA,
		bool _hoops_HRPHA,
		int pcount, const float *points,
		int _hoops_IRPHA, const int *_hoops_ASPH,
		int *_hoops_CRPHA, float *_hoops_SRPHA,
		int *_hoops_GAPHA, int *_hoops_RAPHA,
		int *vertex_mapping, int *face_mapping);

GLOBAL_FUNCTION bool HI_Query_PNG_Dimensions(int _hoops_PASIH, const void *_hoops_PHGH, int alter *width, int alter *height);
GLOBAL_FUNCTION bool HI_Query_JPEG_Dimensions(int _hoops_PASIH, const void *_hoops_PHGH, int alter *width, int alter *height);
GLOBAL_FUNCTION bool HI_Query_TARGA_Dimensions(int _hoops_PASIH, const void *_hoops_PHGH, int alter *width, int alter *height);
GLOBAL_FUNCTION Image * HI_PNG_Decompress(Image const *);
GLOBAL_FUNCTION Image * HI_JPEG_Decompress(Image const *);
GLOBAL_FUNCTION Image * HI_TARGA_Decompress(Image const *);
GLOBAL_FUNCTION bool HI_PNG_Check_Transparency(Image const *);
GLOBAL_FUNCTION bool HI_TARGA_Check_Transparency(Image const *);
GLOBAL_FUNCTION bool HI_DXT_Check_Transparency(Image const *);

GLOBAL_FUNCTION Image * HI_Create_Spotlight_Image(
		int _hoops_HGII,
		float _hoops_HASIH);

GLOBAL_FUNCTION Image * HI_Create_Indexication_Image(
		Net_Rendition const & nr);

GLOBAL_FUNCTION void HI_Free_Selection_Item(
		_hoops_RPIIR *);
GLOBAL_FUNCTION _hoops_RPIIR *HI_Selection_Item_Heap_Pop(
		_hoops_IPIIR *);

GLOBAL_FUNCTION float const *HI_Get_Sin72_Lookup(void);
GLOBAL_FUNCTION float const *HI_Get_Cos72_Lookup(void);

GLOBAL_FUNCTION bool HI_Parse_Condition (_hoops_AIGPR *	_hoops_RIGC, char const * string, _hoops_CCPCA alter * _hoops_SCPCA);
GLOBAL_FUNCTION void HI_Show_Conditional (_hoops_CCPCA const * _hoops_SCPCA, char alter * list, int _hoops_GGCIR);
GLOBAL_FUNCTION void HI_Copy_Conditional (_hoops_CCPCA const * in, _hoops_CCPCA alter * _hoops_PAGR);
GLOBAL_FUNCTION void HI_Free_Conditional (_hoops_CCPCA alter * _hoops_GHPIR);
GLOBAL_FUNCTION void HI_Show_Conditions (_hoops_SPPIR const * conditions, char * options, int _hoops_HGPCA);

GLOBAL_FUNCTION _hoops_PGRPR * HI_Create_Include (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP * ref,
	_hoops_CRCP * newowner,
	_hoops_CCPCA *condition);

GLOBAL_FUNCTION _hoops_PHIP * HI_Create_Reference (
	_hoops_AIGPR * _hoops_RIGC,
	_hoops_CRCP * ref,
	_hoops_CRCP * newowner,
	_hoops_CCPCA *condition);

GLOBAL_FUNCTION void HI_Transform_Points_43 (
	int								count,
	Point const *			input,
	float const *					transform,
	Point alter *			output);
GLOBAL_FUNCTION void HI_Transform_Points_44 (
	int								count,
	Point const *			input,
	float const *					transform,
	float							_hoops_CHCR,
	Point alter *			output,
	float alter *					ws);

GLOBAL_FUNCTION void HI_Free_Texture_Parameters (_hoops_RRCC * _hoops_HAPAR);
GLOBAL_FUNCTION void HI_Free_Tristrip (Tristrip alter *ts);
GLOBAL_FUNCTION void HI_Free_Polyedge (Polyedge alter *pe);


GLOBAL_FUNCTION _hoops_CPSPP ** HI_Lookup_Error_Control (
	_hoops_CPSPP	 **	_hoops_ASRGR,
	int					category,
	int					specific);

GLOBAL_FUNCTION _hoops_ARARR * HI_Lookup_Driver_Config(
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			driver,
	char const *			id,
	char const *			version,
	bool					_hoops_PHIPP,
	XBits const *			_hoops_HHIPP);


GLOBAL_FUNCTION void HI_Free_Driver_Config(
		_hoops_ARARR *_hoops_GPPHA);

GLOBAL_FUNCTION _hoops_ARARR * HI_Clone_Driver_Config(
		_hoops_ARARR *_hoops_GPPHA);

GLOBAL_FUNCTION void HI_Radix_Sort_8(float *_hoops_IASIH, float *_hoops_CASIH, void** _hoops_SASIH, void** _hoops_GPSIH, Integer32 _hoops_RPSIH, unsigned long elements, bool _hoops_APSIH);
GLOBAL_FUNCTION void HI_Radix_Sort_11(float *_hoops_IASIH, float *_hoops_CASIH, void** _hoops_SASIH, void** _hoops_GPSIH, Integer32 _hoops_RPSIH, unsigned long elements, bool _hoops_APSIH);
GLOBAL_FUNCTION void HI_Sort_Array(unsigned long count, float* priorities, void** array, int _hoops_IRAHH, bool _hoops_APSIH);

GLOBAL_FUNCTION void  HI_Queue_Selection_Event (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *_hoops_PCAPH, char const *_hoops_SASHA, char const *_hoops_RPSHA,
	int status, char const *_hoops_ASGIH, Key _hoops_HSICA,
	int offset1, int offset2, int offset3, double xw, double yw, double _hoops_RCSAP, double xc, double yc,
	double zc, _hoops_AISIA  *_hoops_HHCAP);

GLOBAL_FUNCTION void HI_Show_Color (_hoops_SSGI	*color, char *_hoops_ACPRA, int _hoops_PCPRA);
GLOBAL_FUNCTION Key HI_Copy_Segment (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_CAGSA,
	_hoops_CRCP *				newowner,
	Subsegment **			_hoops_ASRGR,
	Subsegment *			_hoops_AIGSA,
	_hoops_HCRPR *					newname,
	bool					_hoops_PIGSA,
	void *					info);
GLOBAL_FUNCTION Attribute * HI_Clone_Attributes (
	_hoops_AIGPR *	_hoops_RIGC,
	Attribute const *		_hoops_PISCA,
	_hoops_CRCP const *			new_owner,
	bool					_hoops_HISCA,
	void *					_hoops_HASAR);

GLOBAL_FUNCTION void HI_Reverse_Shell_Edges (
	Memory_Pool *				memory_pool,
	Shell const	*				_hoops_SPHPR,
	_hoops_RHHPR alter *	_hoops_AACCP,
	_hoops_RHHPR alter **	_hoops_PACCP);

GLOBAL_FUNCTION void HI_Make_RLE_Stencil(_hoops_RAARP * stencil);
GLOBAL_FUNCTION void HI_Cleanup_Stencil(_hoops_RAARP * stencil, bool _hoops_HRPHP);
GLOBAL_FUNCTION _hoops_RAARP *HI_Clone_Stencil(_hoops_RAARP const* stencil);
GLOBAL_FUNCTION void HI_Init_Stencil_Cache(void);
GLOBAL_FUNCTION void HI_Free_Stencil_Cache(void);
GLOBAL_FUNCTION void HI_Clean_Stencil_Cache (Font_Instance const *instance);
GLOBAL_FUNCTION _hoops_RAARP **HI_Get_Stencil_Cache (
	Font_Instance const *instance,
	int						height,
	int						bolding_level,
	float					_hoops_IPGRP,
	float					rotation,
	float					width_scale,
	bool				antialias);
GLOBAL_FUNCTION _hoops_RAARP * HI_Lookup_Stencil(
	_hoops_RAARP	**_hoops_PPSIH,
	unsigned short		_hoops_SRCSP);
GLOBAL_FUNCTION void HI_Store_Stencil(
	_hoops_RAARP	**_hoops_PPSIH,
	_hoops_RAARP	*stencil);
GLOBAL_FUNCTION int HI_Get_Stencil_Cache_Height (int height, bool _hoops_HPSIH);
GLOBAL_FUNCTION bool HI_Check_Texture_Syntax (char const *_hoops_APARA);

GLOBAL_FUNCTION bool HI_Fast_Lookup_Available (_hoops_CRCP const * owner, bool _hoops_HAASA);
GLOBAL_FUNCTION void HI_Create_Fast_Lookup (_hoops_CRCP alter * owner, bool _hoops_HAASA);
GLOBAL_FUNCTION void HI_Destroy_Fast_Lookups (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP alter * owner);
GLOBAL_FUNCTION _hoops_CRCP * HI_Find_Fast_Lookup_Segment (_hoops_CRCP alter * owner, char const * name);
GLOBAL_FUNCTION void HI_Add_Fast_Lookup_Item (_hoops_CRCP alter * owner, bool _hoops_HAASA, Subsegment * item);
GLOBAL_FUNCTION void HI_Remove_Fast_Lookup_Item (_hoops_CRCP alter * owner, bool _hoops_HAASA, Subsegment * item);
GLOBAL_FUNCTION Subsegment * HI_Find_Fast_Lookup_Predecessor (_hoops_CRCP alter * owner, bool _hoops_HAASA, Subsegment * item, char const * name);
GLOBAL_FUNCTION void HI_Show_Fast_Lookup_Priority_Range (_hoops_CRCP *_hoops_SRCP, long *low, long *high);

GLOBAL_FUNCTION _hoops_HIR * HI_New_Diffuse_Channel(_hoops_RCR alter *texture);
GLOBAL_FUNCTION _hoops_HIR *HI_Copy_Diffuse_Channel_List (_hoops_HIR const *_hoops_PGC);
GLOBAL_FUNCTION void HI_Free_Diffuse_Channel_List (_hoops_HIR alter *_hoops_PGC);
GLOBAL_FUNCTION _hoops_HIR *HI_Mix_Diffuse_Channels (_hoops_HIR const *_hoops_SSSGA, _hoops_HIR const *_hoops_IRRS);
GLOBAL_FUNCTION bool HI_Diffuse_Channels_Match (_hoops_HIR const *_hoops_SSSGA, _hoops_HIR const *_hoops_IRRS, Integer32	_hoops_PSSGA);
GLOBAL_FUNCTION void HI_Median_Cut (
	_hoops_AIGPR *	_hoops_RIGC, 
	int						in_count, 
	Point const *			_hoops_IPSIH, 
	RGB const *				_hoops_ASSPA,
	int						_hoops_PSSPA, 
	Point alter *			out_points, 
	RGB alter *				_hoops_HSSPA,
	int alter *				mapping);

GLOBAL_FUNCTION PolyCylinder * HI_Cylinder_To_PolyCylinder (Cylinder const *cylinder);

GLOBAL_FUNCTION void HI_Adjust_Vertex_Attributes (Shell * _hoops_SPHPR, int offset, int ndelete, int insert);
GLOBAL_FUNCTION void HI_Adjust_Vertex_To_Edge (Shell * _hoops_SPHPR, int offset, int ndelete, int insert);
GLOBAL_FUNCTION void HI_Adjust_Face_Attributes (Shell * _hoops_SPHPR, int offset, int ndelete, int insert);
GLOBAL_FUNCTION void HI_Repair_Shell_Edges (_hoops_AIGPR * _hoops_RIGC, Shell * _hoops_SPHPR);
GLOBAL_FUNCTION void HI_Convert_To_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *options,
	Geometry const *geom,
	Shell alter **_hoops_CPSIH,
	Shell alter **_hoops_SPSIH);
GLOBAL_FUNCTION bool HI_Process_NURBS_Surface_Options (
	Option_Value const *_hoops_GHSIH,
	_hoops_RHAIR alter *_hoops_RCIHP);
GLOBAL_FUNCTION void HI_Set_Priority (_hoops_AIGPR * _hoops_RIGC, _hoops_HPAH *thing, long priority);
GLOBAL_FUNCTION void HI_Bring_To_Front (_hoops_AIGPR * _hoops_RIGC, _hoops_HPAH *thing, int offset=0);
GLOBAL_FUNCTION  void HI_Delete_Specific_Shell_Faces (
	_hoops_AIGPR *	_hoops_RIGC,
	Shell alter *_hoops_SPHPR,
	int	count,
	int const *indices);


GLOBAL_FUNCTION _hoops_RAARP * HI_W32_make_font_stencil (
	Font_Instance const	*instance,
	unsigned short			_hoops_IPCSR,
	int						_hoops_RHSIH,
	int						bolding_level,
	float					xrslant,
	float					xrrotation,
	float					xrwidth,
	bool				antialias);

GLOBAL_FUNCTION bool HI_W32_measure_char_stenciled(
	 Net_Rendition const & nr,
	 Font_Instance const * instance,
	 Karacter _hoops_IPCSR,
	 float alter *_hoops_GGGS,
	 bool alter *_hoops_CPCSR,
	 void ** _hoops_HPSRH);

GLOBAL_FUNCTION void HI_W32_unload_font_stenciled (
	 Display_Context const * dc,
	 Font_Instance alter * instance);

GLOBAL_FUNCTION void * HI_W32_load_font_stenciled(
	 Display_Context const	*dc,
	 char const							*name,
	 Font_Instance alter		*instance,
	 void *								hDC,
	 _hoops_SGRRR			**_hoops_GRRRR,
	 _hoops_SGRRR			**_hoops_AHSIH);

GLOBAL_FUNCTION void HI_W32_find_all_fonts (
	 Display_Context alter	*dc,
	 _hoops_SGRRR			**_hoops_GRRRR,
	 _hoops_SGRRR			**_hoops_AHSIH);

GLOBAL_FUNCTION bool HI_W32_find_one_font (
	 Display_Context alter	*dc,
	 char const							*_hoops_PACSR,
	 void *								hDC,
	 _hoops_SGRRR			**_hoops_GRRRR,
	 _hoops_SGRRR			**_hoops_AHSIH);

GLOBAL_FUNCTION void HI_W32_find_basic_fonts (
	 Display_Context alter	*dc,
	 void * const						hDC,
	 _hoops_SGRRR			**_hoops_GRRRR,
	 _hoops_SGRRR			**_hoops_AHSIH);

GLOBAL_FUNCTION bool HI_W32_name_font(
	Net_Rendition const &	nr,
	_hoops_IGPIR const			*_hoops_RRCSP,
	_hoops_IGPIR alter			*_hoops_ARCSP);

GLOBAL_FUNCTION _hoops_SGRRR alter *HI_W32_find_font (
	_hoops_SGRRR		*list,
	const char					*name);

GLOBAL_FUNCTION bool HI_Condition_Passed (
	int _hoops_HGHCA, unsigned int const * _hoops_IGHCA, _hoops_CCPCA const * condition);

GLOBAL_FUNCTION int HI_Generate_Elliptical_Points (
	_hoops_GHHI const *curve, int count, Point alter *_hoops_IAIRA);

GLOBAL_FUNCTION int HI_Split_Point_Lookup (Polyhedron const * _hoops_IPRI, int vertex, int face);
GLOBAL_FUNCTION int HI_Split_Point_Original (Polyhedron const * _hoops_IPRI, int vertex);

GLOBAL_FUNCTION void HI_Free_Convex_Clip_Region (_hoops_ASHH alter *_hoops_CRAIR);
GLOBAL_FUNCTION bool HI_Compute_Camera_Min_Max (
		_hoops_HRPA const *_hoops_HSGA,
		_hoops_HHRA const *_hoops_ISPCR,
		_hoops_CRCP const *_hoops_SRCP,
		Bounding const & _hoops_PHSIH,
		float alter *minz_out,
		float alter *_hoops_HHSIH);

GLOBAL_FUNCTION void HI_Ensure_Definition_Set(_hoops_AIGPR *	_hoops_RIGC);

GLOBAL_FUNCTION _hoops_GSPGR HI_Make_Static_Tree (Net_Rendition const & nr, _hoops_CRCP const * root);
GLOBAL_FUNCTION void HI_Clean_Static_Tree(_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP const *_hoops_SRCP);

GLOBAL_FUNCTION bool HI_Push_Display_List (
		_hoops_AIGPR *	_hoops_RIGC, 
		_hoops_GACR alter *	dl,
		float					priority,
		int						_hoops_GPGC);
GLOBAL_FUNCTION void HI_Extract_Display_List (
		_hoops_AIGPR *	_hoops_RIGC, 
		int						index, 
		_hoops_GACR const *	dl);
GLOBAL_FUNCTION void HI_Invalidate_Display_Lists (
		_hoops_AIGPR *	_hoops_RIGC, 
		Geometry alter *		geometry);
GLOBAL_FUNCTION void HI_Invalidate_Segment_Display_Lists(
		_hoops_AIGPR *	_hoops_RIGC, 
		_hoops_CRCP const *			_hoops_SRCP, 
		int						type, 
		Geometry const *		geo, 
		unsigned int			_hoops_GCRC);
GLOBAL_FUNCTION bool HI_Get_Display_List(
		_hoops_GGAGR const *			driver,
		_hoops_GACR alter **	_hoops_ASRGR,
		_hoops_GACR alter **	_hoops_PAGR);
GLOBAL_FUNCTION void HI_Clean_Segment_Display_Lists (
		_hoops_CRCP const *			segment,
		bool					_hoops_CGPHP);
GLOBAL_FUNCTION void HI_Clean_Geometry_Display_Lists (
		Geometry *				geometry,
		bool					_hoops_IRPHP,
		bool					_hoops_CGPHP);
GLOBAL_FUNCTION void HI_Clean_Display_List (
		_hoops_GACR **			_hoops_IHSIH,
		bool					_hoops_HRPHP,
		bool					_hoops_CGPHP);

GLOBAL_FUNCTION bool HI_Named_Materials_Equal (Named_Material const * first, Named_Material const * _hoops_IAGRA);

GLOBAL_FUNCTION void HI_Flush_Color_Material_Lookup(_hoops_ISGPH **_hoops_HIHPP);

GLOBAL_FUNCTION void HI_Record_Recent_Seg_Path (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP const * _hoops_SRCP);
GLOBAL_FUNCTION void HI_Flush_Seg_Path_Lookup(_hoops_AIGPR * _hoops_RIGC);
GLOBAL_FUNCTION void HI_Remove_Seg_Path_Lookup_Item (_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP const * _hoops_SRCP);

GLOBAL_FUNCTION void HI_Clear_Image_Cache (Image alter *image);


GLOBAL_FUNCTION void HI_LOD_Execute(
	int _hoops_CHSIH, const float *_hoops_RHAAA,
	int _hoops_SHSIH, const int *_hoops_ASPH,
	_hoops_SAPHA *_hoops_GISIH,									/* _hoops_RIH _hoops_IHHAH _hoops_IH _hoops_HCR _hoops_SHIR _hoops_HSH */
	int *_hoops_RISIH, float *_hoops_AISIH,
	int *_hoops_PISIH, int *_hoops_RAPHA,
	int *_hoops_PHAS
);

GLOBAL_FUNCTION _hoops_HAPHA *HI_LOD_Chain_Execute_Tristrips(
	int point_count, const float *points,
	const Tristrip *t,
	_hoops_SAPHA *_hoops_GISIH,									/* _hoops_RIH _hoops_IHHAH _hoops_IH _hoops_HCR _hoops_SHIR _hoops_HSH */
	int depth
);

GLOBAL_FUNCTION _hoops_HAPHA *HI_Compute_LOD_Fast(
	int pcount,
	const float *points,
	int _hoops_RHGIR,
	const int *faces,
	float _hoops_PRPHA,
	int depth
);

GLOBAL_FUNCTION _hoops_HAPHA *HI_Compute_LOD_Tristrips_Fast(
	int pcount,
	const float *points,
	const Tristrip *t,
	float _hoops_PRPHA,
	int depth
);

GLOBAL_FUNCTION void HI_Show_Geometry_Options (
	Geometry const *		geo,
	char alter *			list,
	int						_hoops_GGCIR
);

GLOBAL_FUNCTION double HI_Compute_Vector_Length (Vector const *	in);

GLOBAL_FUNCTION void HI_Compute_Offaxis_Rotation (
	double					x,
	double					y,
	double					z,
	double					_hoops_RAHCR,
	float alter				*matp
);

GLOBAL_FUNCTION void HI_Init_Texture_Options();

GLOBAL_FUNCTION void HI_Glyph_Fixup_Polyline (
	Net_Rendition const &		nr,
	int							incount,
	DC_Point const *			_hoops_IRRAA
);

GLOBAL_FUNCTION void HI_Glyph_Fixup_Polygon (
	Net_Rendition const &		inr,
	int							incount,
	DC_Point const *			_hoops_IRRAA
);

GLOBAL_FUNCTION void HI_Glyph_Fixup_Polydot (
	Net_Rendition const &		nr,
	int							incount,
	DC_Point const *			_hoops_IRRAA
);

GLOBAL_FUNCTION void HI_Glyph_Fixup_Ellipse (
	Net_Rendition const &		inr,
	DC_Point const *			center,
	DC_Point const *			_hoops_HISIH
);

GLOBAL_FUNCTION void HI_Glyph_Fixup_Outline_Ellipse (
	Net_Rendition const &		nr,
	DC_Point const *			center,
	DC_Point const *			_hoops_HISIH
);

GLOBAL_FUNCTION void HI_Glyph_Fixup_Polytriangle (
	Net_Rendition const &		inr,
	int							incount,
	DC_Point const *			_hoops_IRRAA
);


GLOBAL_FUNCTION void HI_Compute_Tight_OBB (
	Point const	*_hoops_CSRPA,
	int			_hoops_IISIH,
	Point		*faces
);


GLOBAL_FUNCTION void HI_Compress_User_Options(_hoops_AIGPR * _hoops_RIGC);
GLOBAL_FUNCTION void HI_Free_User_Options_Compressor(void);
GLOBAL_FUNCTION void HI_Decode_User_Option(_hoops_HCRPR const &in, _hoops_HCRPR &_hoops_PAGR);
GLOBAL_FUNCTION void HI_Decode_Unicode_User_Option(KName const &in, KName &_hoops_PAGR);

// _hoops_IS _hoops_ARGAR _hoops_RH _hoops_CISIH _hoops_PSCH _hoops_IH _hoops_SGH _hoops_GGR _hoops_IRS _hoops_SISIH _hoops_RHPP
GLOBAL_FUNCTION _hoops_CPGRR HI_Create_Mutex ();
GLOBAL_FUNCTION void HI_Destroy_Mutex (_hoops_CPGRR _hoops_RASCA);

GLOBAL_FUNCTION void HI_Set_Thread_Name (int id, char const * name, bool _hoops_GCSIH);

GLOBAL_FUNCTION bool HI_Color_Is_Simple (_hoops_SSGI const *color, _hoops_RHAH const * _hoops_CSIR=0);

GLOBAL_FUNCTION void HI_Delete_By_Keys (_hoops_AIGPR * _hoops_RIGC, int count, Key const * keys);

GLOBAL_FUNCTION _hoops_CRCP * HI_Separate_Geometry_Attributes (_hoops_AIGPR * _hoops_RIGC, Geometry alter * g);

GLOBAL_FUNCTION bool HI_Process_Heuristic_Options(_hoops_AIGPR * _hoops_RIGC, char const *list, _hoops_GHAIR alter* _hoops_APHCR, bool _hoops_SCIIH);

GLOBAL_FUNCTION void HI_Delete_Renditions(_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP * _hoops_SRCP,
										  _hoops_PGRPR const * include = 0, Display_Context * dc = 0, bool _hoops_HGRHP = false);

GLOBAL_FUNCTION void HI_Show_Line_Pattern_Explicit (_hoops_AIGPR * _hoops_RIGC, _hoops_PSAIR * _hoops_HSAIR, char * pattern, int _hoops_RCSIH);
GLOBAL_FUNCTION void HI_Show_Edge_Pattern_Explicit (_hoops_AIGPR * _hoops_RIGC, _hoops_ISAIR * _hoops_CSAIR, char * pattern, int _hoops_RCSIH);

GLOBAL_FUNCTION _hoops_HPPIR * HI_Distill_User_Options(_hoops_AIGPR * _hoops_RIGC, _hoops_HPPIR const * user_options, int flags);
GLOBAL_FUNCTION int HI_User_Option_Hash_Key(_hoops_HPPIR const * _hoops_ACSIH);
GLOBAL_FUNCTION bool HI_User_Option_Equal(_hoops_HPPIR const * _hoops_PCSIH, _hoops_HPPIR const * _hoops_HCSIH);

GLOBAL_FUNCTION _hoops_HPAH * HI_Find_Target_And_Lock (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_IPRRA				_hoops_HPPS);

GLOBAL_FUNCTION  _hoops_HPAH * HI_Find_Target_And_Lock (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	_hoops_IPRRA				_hoops_HPPS);

GLOBAL_FUNCTION void HI_Compute_Scale_Matrix (
	double					x,
	double					y,
	double					z,
	float alter				*matp);

GLOBAL_FUNCTION void HI_Compute_Identity_Matrix (
	float alter				*matp);

GLOBAL_FUNCTION void HI_Compute_Matrix_Product (
	float const				*leftp,
	float const				*rightp,
	float alter				*resultp);


GLOBAL_FUNCTION bool HI_Compute_Matrix_Inverse (
	float const				*matp,
	float alter				*invp);

GLOBAL_FUNCTION bool HI_Compute_Normalized_Matrix (
	float const				*matp,
	float alter				*_hoops_CHIPA);

GLOBAL_FUNCTION void HI_Compute_Cross_Product (
	Vector const	*in1,
	Vector const	*in2,
	Vector alter	*_hoops_PAGR);

GLOBAL_FUNCTION void HI_Compute_Rotation_Matrix (
	double					x,
	double					y,
	double					z,
	float alter				*matp);

GLOBAL_FUNCTION void HI_Compute_Translation_Matrix (
	double					x,
	double					y,
	double					z,
	float alter				*matp);

GLOBAL_FUNCTION double HI_Compute_Vector_Angle (
	Vector const	*in1,
	Vector const	*in2);

GLOBAL_FUNCTION double HI_Compute_Dot_Product (
	Vector const	*in1,
	Vector const	*in2);

GLOBAL_FUNCTION void HI_Bring_To_Front_By_Key (
	_hoops_AIGPR * _hoops_RIGC,
	Key key);

GLOBAL_FUNCTION void HI_Begin_Shell_Selection (
	_hoops_AIGPR * _hoops_RIGC);

GLOBAL_FUNCTION void HI_End_Shell_Selection (
	_hoops_AIGPR * _hoops_RIGC);

GLOBAL_FUNCTION double HI_Compute_Matrix_Determinant (
	float const * matp);

GLOBAL_FUNCTION void HI_Relinquish_Memory (void);

GLOBAL_FUNCTION bool HI_Parse_String (
	char const				*string,
	char const				*_hoops_ICSIH,
	int						offset,
	char					*_hoops_CIPPR,
	int						_hoops_CCSIH);

GLOBAL_FUNCTION void HI_UnDefine_Color_Name (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			innames);

GLOBAL_FUNCTION void HI_Compute_Matrix_Adjoint (
	float const *		matp,
	float alter *		_hoops_IRIPA);

GLOBAL_FUNCTION bool HI_Compute_Transformed_Planes2 (
	int					count,
	_hoops_ARPA const *		in,
	float const *		matp,
	_hoops_ARPA *				_hoops_PAGR);


GLOBAL_FUNCTION void HI_Compute_Optimized_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	int				in_point_count,
	Point const	*	in_points,
	Vector const *	_hoops_ISHRA,
	int				in_face_list_length,
	int const *		in_face_list,
	char const *	option_string,
	int *			out_point_count,
	Point *			out_points,
	int *			out_face_list_length,
	int	*			out_face_list,
	int	*			vertex_mapping,
	int	*			face_mapping);

GLOBAL_FUNCTION _hoops_GGAGR *HI_Find_Owner_Actor (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			segname,
	_hoops_CRCP **				_hoops_PRCPH);


GLOBAL_FUNCTION bool HI_Do_Update (
	_hoops_AIGPR *	_hoops_RIGC,
	double					limit,
	bool					_hoops_SCSIH);

GLOBAL_FUNCTION bool HI_Do_One_Update (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	double					limit);

GLOBAL_FUNCTION void HI_Queue_Actor_Update(
	_hoops_GGAGR const *	_hoops_GHRI,
	bool			_hoops_GSSIH);

GLOBAL_FUNCTION void HI_Queue_Actor_Shutdown(
	_hoops_GGAGR const *	_hoops_GHRI,
	bool			_hoops_GSSIH);

GLOBAL_FUNCTION void HI_Check_Actor_Queue(
	_hoops_GGAGR const *	_hoops_GHRI);

GLOBAL_FUNCTION bool HI_Initialize_Actor (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR * _hoops_GHRI);



GLOBAL_FUNCTION void HI_Close_Segment (
	_hoops_AIGPR *	_hoops_RIGC);

GLOBAL_FUNCTION Key HI_Show_Owner_Key_By_Key (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	bool					_hoops_AARHP,
	bool					_hoops_CISAP);


GLOBAL_FUNCTION bool HI_Compute_Transform_By_Path (
	_hoops_AIGPR *	_hoops_RIGC,
	int						count,
	Key const *				keys,
	char const *			in_system,
	char const *			out_system,
	float alter *			matrix);


GLOBAL_FUNCTION void HI_Show_Shell_Size (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	int *					point_countp,
	int *					face_list_lengthp);

GLOBAL_FUNCTION void HI_Show_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	int *					point_countp,
	Point *					points,
	int *					face_list_lengthp,
	int *					face_list);

GLOBAL_FUNCTION void HI_Show_Clip_Region (
	_hoops_IRAIR				*_hoops_PPGGA,
	int alter				*loops,
	int alter				*lengths,
	Point alter				*points,
	char					*result,
	int						_hoops_RIAGA);

GLOBAL_FUNCTION void HI_Read_Driver_Config_File (void);

GLOBAL_FUNCTION _hoops_AHAGR * HI_Find_Segment_Cache (
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_HICS const &	path,
	bool					_hoops_IIASA = true);
GLOBAL_FUNCTION _hoops_AHAGR * HI_Find_Segment_Cache (
	_hoops_CRCP const *			_hoops_SRCP,
	bool					_hoops_IIASA = true);

GLOBAL_FUNCTION int HI_Record_Lightweight_Key (
	_hoops_HPAH *					item,
	int							offset,
	int							index = -1);
GLOBAL_FUNCTION void HI_Replace_Lightweight_Key (
	int							index,
	_hoops_HPAH *					item,
	int							offset);
GLOBAL_FUNCTION void HI_Remove_Lightweight_Key (
	int							index);

GLOBAL_FUNCTION Key HI_Add_To_Multiline (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	Point const &			a,
	Point const &			b,
	int						index = -1);

GLOBAL_FUNCTION Key HI_Add_To_Multimarker (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	Point const &			a,
	int						index = -1);

GLOBAL_FUNCTION Line * HI_Isolate_Line_From_Multiline (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_SHRIR *				_hoops_GIRIR,
	int						offset);

GLOBAL_FUNCTION Marker * HI_Isolate_Marker_From_Multimarker (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GRPGR *			_hoops_CPAI,
	int						offset);


GLOBAL_FUNCTION bool HI_Find_Alias (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					alias,
	int						length);

GLOBAL_FUNCTION void HI_Show_Alias (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *		alias,
	char *				_hoops_ASAPR,
	int					length);

GLOBAL_FUNCTION bool HI_Find_Color_Name (
	_hoops_AIGPR *	_hoops_RIGC,
	char *			_hoops_ASAPR,
	int				_hoops_HSHPP,
	char *			_hoops_HCHPR,
	int				_hoops_ISHPP,
	char *			_hoops_CSHPP,
	int				_hoops_SSHPP);


GLOBAL_FUNCTION void HI_Show_Color_Name (
	char const *	string,
	char *			_hoops_AAPPR,
	int				len);


GLOBAL_FUNCTION float HI_Cuboid_To_Cuboid_Distance(
	_hoops_SASC const & _hoops_ARCIR,
	_hoops_SASC const & _hoops_PRCIR);


GLOBAL_FUNCTION float HI_Cuboid_To_Cuboid_Max_Distance(
	_hoops_SASC const & _hoops_ARCIR,
	_hoops_SASC const & _hoops_PRCIR);


GLOBAL_FUNCTION float HI_Cuboid_To_Point_Distance(
	_hoops_SASC const & cuboid,
	Point const & point);

GLOBAL_FUNCTION bool HI_Distance_Point_Polygon(
	Point const *	p, 
	Point const *	points, 
	int				_hoops_RHGIR, 
	Point alter *	_hoops_SHHHA, 
	float alter *	dist);

GLOBAL_FUNCTION bool HI_Compute_Point_To_Line_Distance(
	Point const *	point, 
	Point const *	_hoops_RSSIH,  
	Point const *	_hoops_AHPPA, 
	float alter *	_hoops_CGSIR, 
	Point alter *	_hoops_HGII = null);

GLOBAL_FUNCTION void HI_Write_Lock_Database();
GLOBAL_FUNCTION void HI_Read_Lock_Database();
GLOBAL_FUNCTION void HI_Unlock_Database();
GLOBAL_FUNCTION int HI_Check_Lock (Lock hl, char const * file, int line); 



GLOBAL_FUNCTION void HI_Link_Contents (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info);

GLOBAL_FUNCTION void HI_Free_Search_List (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_AGHPR * node);



GLOBAL_FUNCTION _hoops_CRCP * HI_Create_Proxy (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_CRCP const *			_hoops_SRCP);

GLOBAL_FUNCTION _hoops_IPRRA HI_Anything_To_Open_Type(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH const *		item,
	_hoops_CRCP **				_hoops_SRCP = null, 
	Geometry **				geo = null,
	_hoops_SIRIR **			_hoops_ASSIH = null);


GLOBAL_FUNCTION Key HI_Insert_Circle (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end);

GLOBAL_FUNCTION void HI_Edit_Circle (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_PHPIR *				_hoops_HGSSR,
	Point					start,
	Point					_hoops_GGSSR,
	Point					end);

GLOBAL_FUNCTION Key HI_Insert_Circle_By_Radius (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	Point const *			center,
	float					radius,
	Vector const *			normal);

GLOBAL_FUNCTION Key HI_Insert_Circular_Arc (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end);

GLOBAL_FUNCTION void HI_Edit_Circular_Arc (
	_hoops_AIGPR *	_hoops_RIGC,
	Circular_Arc *			c,
	Point					start,
	Point					_hoops_GGSSR,
	Point					end);

GLOBAL_FUNCTION Key HI_Insert_Circular_Chord (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end);

GLOBAL_FUNCTION Key HI_Insert_Circular_Wedge (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end);

GLOBAL_FUNCTION void HI_Edit_Circular_Wedge (
	_hoops_AIGPR *	_hoops_RIGC,
	Circular_Arc *			c, 
	Point					start,
	Point					_hoops_GGSSR,
	Point					end);

GLOBAL_FUNCTION void HI_Edit_NURBS_Curve (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_PIRGR *			curve,
	int						control_point_offset,
	int						knot_offset,
	int						control_point_replace_count,
	int						knot_replace_count,
	Point const *			control_points,
	float const *			weights,
	float const *			knots); 

GLOBAL_FUNCTION Key HI_Insert_NURBS_Curve (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	int						degree,
	int						control_point_count,
	Point const *			control_points, 
	float const *			weights,
	float const *			knots,
	float					start_u,
	float					end_u); 

GLOBAL_FUNCTION void HI_Edit_NURBS_Surface (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_APPGR *			surface,
	int						control_point_offset,
	int						weight_offset,
	int						u_knot_offset,
	int						v_knot_offset,
	int						control_point_replace_count,
	int						weight_replace_count,
	int						u_knot_replace_count,
	int						v_knot_replace_count,
	Point const	*			control_points,
	float const *			weights,
	float const *			u_knots,
	float const *			v_knots);

GLOBAL_FUNCTION Key HI_Insert_NURBS_Surface (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						u_degree,
	int						v_degree,
	int						n_u_vertices,
	int						n_v_vertices,
	Point const *			control_points,
	float const *			weights,
	float const *			u_knots,
	float const *			v_knots);

GLOBAL_FUNCTION void HI_Edit_Cutting_Plane (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HHPIR *			_hoops_IICSA,
	double					a,
	double					b,
	double					c,
	double					d);

GLOBAL_FUNCTION Key HI_Insert_Cutting_Section (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						count,
	_hoops_ARPA const	*			planes);

GLOBAL_FUNCTION void HI_Edit_Cutting_Section (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HHPIR *			_hoops_IICSA,
	int						ioffset,
	int						ndelete,
	int						insert,
	_hoops_ARPA const *			iplanes);

GLOBAL_FUNCTION Key HI_Insert_Cylinder (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			first,
	Point const *			_hoops_IAGRA,
	float					radius,
	char const *			list);

GLOBAL_FUNCTION Key HI_Insert_PolyCylinder (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						point_count,
	Point const *			points,
	int						_hoops_ISPIR,
	float const *			radii,
	char const *			list); 

GLOBAL_FUNCTION void HI_Edit_PolyCylinder (
	_hoops_AIGPR *	_hoops_RIGC,
	PolyCylinder *			_hoops_HSPIR,
	int						point_count,
	Point const *			points,
	int						_hoops_ISPIR,
	float const *			radii,
	char const *			list);

GLOBAL_FUNCTION void HI_Edit_Polygon (
	_hoops_AIGPR *	_hoops_RIGC,
	Polygon *				polygon,
	int						ioffset,
	int						ndelete,
	int						insert,
	Point const *			_hoops_CGICP);

GLOBAL_FUNCTION Key HI_Insert_Polygon (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						count,
	Point const *			points);

GLOBAL_FUNCTION void HI_Edit_Ellipse (
	_hoops_AIGPR *	_hoops_RIGC,
	Ellipse *				e,
	Point					center,
	Point					major,
	Point					minor);

GLOBAL_FUNCTION Key HI_Insert_Ellipse (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			center,
	Point const *			major,
	Point const *			minor);

GLOBAL_FUNCTION void HI_Edit_Elliptical_Arc (
	_hoops_AIGPR *	_hoops_RIGC,
	Elliptical_Arc *		e,
	Point					center,
	Point					major,
	Point					minor,
	double					start,
	double					end);

GLOBAL_FUNCTION Key HI_Insert_Elliptical_Arc (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			center,
	Point const *			major,
	Point const *			minor,
	float					start,
	float					end);

GLOBAL_FUNCTION Key HI_Insert_Grid (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	char const *			type,
	Point const	*			origin,
	Point const	*			ref1,
	Point const	*			ref2,
	int						count1,
	int						count2);

GLOBAL_FUNCTION Key HI_Insert_Image (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					item,
	Point const *				where,
	char const *				format,
	int							width,
	int							height,
	int							size,
	void const *				_hoops_SHGGR,
	bool						_hoops_PSSIH);

GLOBAL_FUNCTION void HI_Edit_Infinite_Line (
	_hoops_AIGPR *	_hoops_RIGC,
	Polyline *				l,
	Point					a,
	Point					b,
	bool					_hoops_HSSIH);

GLOBAL_FUNCTION Key HI_Insert_Infinite_Line (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					item,
	Point const &				a,
	Point const &				b,
	bool						_hoops_HSSIH);

GLOBAL_FUNCTION Key HI_Insert_Distant_Light (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Vector const &			direction);

GLOBAL_FUNCTION void HI_Edit_Light (
	_hoops_AIGPR *	_hoops_RIGC,
	Light *					light,
	Point const *			position,
	Point const *			direction);

GLOBAL_FUNCTION Key HI_Insert_Area_Light (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						count,
	Point const	*			points,
	char const *			list);

GLOBAL_FUNCTION Key HI_Insert_Spot_Light (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_PSSGP *		data);

GLOBAL_FUNCTION void HI_Initialize_Spot_Light_Options(
	_hoops_PSSGP *		data);

GLOBAL_FUNCTION bool HI_Validate_Spot_Light_Options(
	_hoops_PSSGP *		data,
	Point const &			position,
	Point const &			target);

GLOBAL_FUNCTION Key HI_Insert_Local_Light (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const &			position); 

GLOBAL_FUNCTION void HI_Edit_Line (
	_hoops_AIGPR *	_hoops_RIGC,
	Line *					l,
	Point					a,
	Point					b);

GLOBAL_FUNCTION Key HI_Insert_Line (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const &			a,
	Point const &			b);

GLOBAL_FUNCTION void HI_Edit_Marker (
	_hoops_AIGPR *	_hoops_RIGC,
	Marker *				m,
	Point					p);

GLOBAL_FUNCTION Key HI_Insert_Marker (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const &			where);

GLOBAL_FUNCTION void HI_Edit_Mesh (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_AIHPR *					_hoops_PIHPR,
	int						row_offset,
	int						column_offset,
	int						row_count,
	int						column_count,
	Point const *			points);

GLOBAL_FUNCTION Key HI_Insert_Mesh (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						rows,
	int						columns,
	Point const	*			points,
	bool					_hoops_PSSIH);

GLOBAL_FUNCTION void HI_Edit_Polyline (
	_hoops_AIGPR *	_hoops_RIGC,
	Polyline *				polyline,
	int						ioffset,
	int						ndelete,
	int						insert,
	Point const *			_hoops_CGICP);

GLOBAL_FUNCTION Key HI_Insert_Polyline (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						count,
	Point const *			points);

GLOBAL_FUNCTION void HI_Edit_Sphere (
	_hoops_AIGPR *	_hoops_RIGC,
	Sphere *				s,
	Point					center,
	float					radius,
	Vector const *			axis,
	Vector const *			ortho);

GLOBAL_FUNCTION Key HI_Insert_Sphere (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			center,
	float					radius,
	Vector const *			axis,
	Vector const *			ortho);

GLOBAL_FUNCTION Key HI_Insert_Text_With_Encoding (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const &			where,
	_hoops_IHGRP			encoding,
	void const *			string);

GLOBAL_FUNCTION Key HI_Insert_Shell (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						point_count,
	Point const *			points,
	int						face_list_length,
	int const *				face_list,
	bool					_hoops_ISSIH);

GLOBAL_FUNCTION void HI_Edit_Shell_Points (
	_hoops_AIGPR *	_hoops_RIGC,
	Shell *					_hoops_SPHPR,
	int						ioffset,
	int						ndelete,
	int						insert,
	Point const *			points);

GLOBAL_FUNCTION void HI_Edit_Shell_Faces (
	_hoops_AIGPR *	_hoops_RIGC,
	Shell *					_hoops_SPHPR,
	int						ioffset,
	int						ndelete,
	int						_hoops_CSSIH,
	int	const *				insert_list);

GLOBAL_FUNCTION Key HI_Insert_Shell_By_Tristrips (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						point_count,
	Point const	*			points,
	int						_hoops_PGRIH,
	int const *				_hoops_ARRI,
	int						_hoops_HGRIH,
	int const *				_hoops_IGRIH);



GLOBAL_FUNCTION bool HI_Set_Color(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_SSGI *					color); 

GLOBAL_FUNCTION bool HI_Set_Color(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR,
	_hoops_SSGI *					color);

GLOBAL_FUNCTION bool HI_Set_Vertex_Symbol(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_SSAIR	*		_hoops_SSSIH);

GLOBAL_FUNCTION bool HI_Set_Marker_Symbol(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_SSAIR	*		_hoops_SSSIH);

GLOBAL_FUNCTION bool HI_Set_Marker_Size(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_AHPIR *		_hoops_GGGCH);

GLOBAL_FUNCTION bool HI_Set_Line_Pattern(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	_hoops_PSAIR *	_hoops_HSAIR);

GLOBAL_FUNCTION bool HI_Set_Edge_Pattern (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ISAIR *	_hoops_CSAIR);

GLOBAL_FUNCTION bool HI_Set_Edge_Pattern (
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_ISAIR *	_hoops_CSAIR);

GLOBAL_FUNCTION void HI_Set_Bounding(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	Bounding *				bounding);

GLOBAL_FUNCTION bool HI_Set_Callback(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	_hoops_GCHIR *				callback);

GLOBAL_FUNCTION bool HI_Set_Camera (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	_hoops_HHRA *				_hoops_SPH);

GLOBAL_FUNCTION void HI_Set_Camera_Near_Limit (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					limit);

GLOBAL_FUNCTION void HI_UnSet_Camera_Near_Limit (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item);

GLOBAL_FUNCTION void HI_Set_Camera_By_Volume (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	char const *			proj,
	float					xmin,
	float					xmax,
	float					ymin,
	float					ymax);

GLOBAL_FUNCTION void HI_Set_Camera_Field (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					width,
	float					height);

GLOBAL_FUNCTION void HI_Set_Camera_Position (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	Point const *			point);

GLOBAL_FUNCTION void HI_Set_Camera_Projection (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	char const *			proj);

GLOBAL_FUNCTION void HI_Set_Camera_Target (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	Point const *			target);

GLOBAL_FUNCTION void HI_Set_Camera_Up_Vector (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	Vector const *			up_vector);

GLOBAL_FUNCTION void HI_Zoom_Camera (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					_hoops_APCH);

GLOBAL_FUNCTION void HI_Roll_Camera (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					_hoops_RAHCR);

GLOBAL_FUNCTION void HI_Pan_Camera (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					_hoops_PAHCR,
	float					_hoops_HAHCR);

GLOBAL_FUNCTION void HI_Orbit_Camera (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	float					_hoops_PAHCR,
	float					_hoops_HAHCR);

GLOBAL_FUNCTION bool HI_Set_Polygonal_Clip_Region (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	_hoops_IRAIR *			_hoops_PPGGA);

GLOBAL_FUNCTION bool HI_Set_Color_Map (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RHAH *				_hoops_CSIR); 

GLOBAL_FUNCTION bool HI_Set_Conditions (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_SPPIR *			conditions); 

GLOBAL_FUNCTION void HI_Unset_Color(
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR);

GLOBAL_FUNCTION void HI_UnSet_Edge_Pattern(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset);

GLOBAL_FUNCTION void HI_UnSet_Vertex_Symbol(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset);


GLOBAL_FUNCTION bool HI_Set_Line_Weight(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				target, 
	_hoops_AHPIR *		_hoops_GGGCH);

GLOBAL_FUNCTION bool HI_Set_Edge_Weight (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_AHPIR *		_hoops_GGGCH);

GLOBAL_FUNCTION bool HI_Set_Edge_Weight(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_AHPIR *		_hoops_GGGCH);

GLOBAL_FUNCTION void HI_UnSet_Edge_Weight(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset);

GLOBAL_FUNCTION void HI_UnSet_Vertex_Size(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset);

GLOBAL_FUNCTION bool HI_Set_Text_Spacing (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_AHPIR *		_hoops_GGGCH);

GLOBAL_FUNCTION bool HI_Set_Face_Pattern(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR,
	_hoops_GGPIR	*		_hoops_RGGCH);

GLOBAL_FUNCTION bool HI_Set_Face_Pattern (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GGPIR	*		_hoops_RGGCH);

GLOBAL_FUNCTION void HI_UnSet_Face_Pattern(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR);

GLOBAL_FUNCTION bool HI_Set_Window_Pattern (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GGPIR	*		_hoops_RGGCH);


GLOBAL_FUNCTION bool HI_Set_Glyph_Defs(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	_hoops_AAAIR *			glyph_defs);

GLOBAL_FUNCTION void HI_UnSet_Defined_Glyph(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	_hoops_HCRPR const &			_hoops_CRPCR);

GLOBAL_FUNCTION bool HI_Set_Line_Style_Defs(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	_hoops_APAIR *		line_style);

GLOBAL_FUNCTION void HI_UnSet_Defined_Line_Style(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	_hoops_HCRPR const &			_hoops_CRPCR);


GLOBAL_FUNCTION bool HI_Set_Text_Font (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	_hoops_AGPIR *				_hoops_CAICA);

GLOBAL_FUNCTION bool HI_Set_Text_Alignment (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	_hoops_GGPIR	*		_hoops_RGGCH);

GLOBAL_FUNCTION void HI_Set_Text_Region (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HACC *					text,
	int						count,
	Point const *			points,
	int						options,
	int						_hoops_AGGCH = 0);

GLOBAL_FUNCTION char * HI_Show_Text_Region_Options (
	_hoops_AIHIR const *		region,
	char alter *			_hoops_PGGCH);


GLOBAL_FUNCTION bool HI_Set_Driver_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	_hoops_GAPIR *		_hoops_PAICA);


GLOBAL_FUNCTION bool HI_Set_Handedness (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ARAIR *			_hoops_HRACA);

GLOBAL_FUNCTION bool HI_Set_Heuristics (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GHAIR *			heuristics); 

GLOBAL_FUNCTION bool HI_Set_Modelling_Matrix(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ISGI *		modelling_matrix);

GLOBAL_FUNCTION bool HI_Append_Modelling_Matrix(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ISGI *		modelling_matrix);


GLOBAL_FUNCTION bool HI_Set_Rendering_Options(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RHAIR *		_hoops_RSHCA);

GLOBAL_FUNCTION bool HI_Set_Selectability(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ASAIR *			_hoops_AAICA); 

GLOBAL_FUNCTION bool HI_Set_Streaming_Mode(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RRAIR *		_hoops_SSGCR);

GLOBAL_FUNCTION bool HI_Set_Text_Path (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RGPIR *				_hoops_HGGCH);

GLOBAL_FUNCTION bool HI_Set_Texture_Matrix (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GAAIR *		_hoops_APGH);

GLOBAL_FUNCTION bool HI_Append_Texture_Matrix (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GAAIR *		_hoops_APGH);

GLOBAL_FUNCTION bool HI_Set_Visibility (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RSAIR *			_hoops_APHCR);

GLOBAL_FUNCTION bool HI_Set_Visibility(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR,
	_hoops_RSAIR *			_hoops_APHCR);

GLOBAL_FUNCTION void HI_UnSet_Visibility(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR);

GLOBAL_FUNCTION bool HI_Set_Window (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Window *				window);

GLOBAL_FUNCTION bool HI_Set_Window_Frame (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GSAIR *			_hoops_IGGCH);

GLOBAL_FUNCTION bool HI_Set_User_Value (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RHPIR *			_hoops_CGGCH);

GLOBAL_FUNCTION bool HI_Set_User_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_HPPIR *			user_options);

GLOBAL_FUNCTION bool HI_Define_Named_Style (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_IAAIR *		_hoops_SGGCH);

GLOBAL_FUNCTION void HI_Undefine_Named_Style(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_CRCP const *			_hoops_SRCP, 
	_hoops_HCRPR const &			_hoops_CRPCR); 





GLOBAL_FUNCTION void HI_UnSet_Attribute (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						type);


GLOBAL_FUNCTION void HI_Free_User_Option (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPPIR *			user_options);

GLOBAL_FUNCTION void HI_Free_Condition(_hoops_SPPIR * _hoops_GHPIR);

GLOBAL_FUNCTION _hoops_PCACA * HI_Copy_Conditional_Actions(_hoops_PCACA * _hoops_ACPGR);
GLOBAL_FUNCTION void HI_Free_Conditional_Actions(_hoops_PCACA * action);

GLOBAL_FUNCTION bool HI_Check_Geometry_Attribute_Type(
	_hoops_AIGPR *	_hoops_RIGC,
	Geometry const *		geo,
	Type					type);

GLOBAL_FUNCTION bool HI_Is_Segment_Open(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	bool					_hoops_AARHP);


GLOBAL_FUNCTION bool HI_Bounding_Is_Excluded (Attribute const *_hoops_ASGPR);

GLOBAL_FUNCTION bool HI_Show_One_User_Option_By_Key(_hoops_AIGPR * _hoops_RIGC, Key key, char const * uoname, char * options);
GLOBAL_FUNCTION bool HI_PShow_One_Net_User_Option(_hoops_AIGPR * _hoops_RIGC, int count, Key const * keys, char const * uoname, char * options);

GLOBAL_FUNCTION void HI_Show_One_User_Data_By_Key(_hoops_AIGPR * _hoops_RIGC, Key key, POINTER_SIZED_INT index, void *data, long data_length, long * data_length_out);
GLOBAL_FUNCTION void HI_PShow_One_Net_User_Data(_hoops_AIGPR * _hoops_RIGC, int count, Key const * keys, POINTER_SIZED_INT index, void *data, long data_length, long * data_length_out);

GLOBAL_FUNCTION void HI_Queue_Keyboard_Event (_hoops_GGAGR *source, int button, int status);
GLOBAL_FUNCTION void HI_Queue_Keyboard_Event_W_Enc (_hoops_GGAGR *source, int button, int status, char encoding);
GLOBAL_FUNCTION void HI_Queue_Location_Event (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR *source, float x, float y, int status, int action);
GLOBAL_FUNCTION void HI_Queue_Wakeup_Event (_hoops_AIGPR * _hoops_RIGC, _hoops_HRIIR * _hoops_CHIIR);
GLOBAL_FUNCTION void HI_Queue_Wakeup_Event (_hoops_AIGPR * _hoops_RIGC, float _hoops_PHSAP); 
GLOBAL_FUNCTION void HI_Queue_Special_Event (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			type,
	char const *			value);

GLOBAL_FUNCTION void HI_Queue_Related_Selection (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			pathname,
	Key						_hoops_HSICA,
	int						offset1,
	int						offset2,
	int						offset3,
	double					xw,
	double					yw,
	double					_hoops_RCSAP,
	double					xc,
	double					yc,
	double					zc); 

GLOBAL_FUNCTION void HI_Await_Event (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					type,
	int						_hoops_SCPRA);

GLOBAL_FUNCTION char alter * HI_Build_Special_Event_String (
	char alter *string,
	char const *brand,
	_hoops_CRCP const *_hoops_GHRI,
	POINTER_SIZED_INT window,
	int _hoops_SHHPH);

GLOBAL_FUNCTION void HI_Generate_Polyline_Bezier (
	int count,
	Point const *points,
	Point alter *buffer);

GLOBAL_FUNCTION int HI_Check_For_Events (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR const * _hoops_GHRI);

GLOBAL_FUNCTION void HI_Enable_Location_Events (
	_hoops_AIGPR *	_hoops_RIGC,	
	char const *			_hoops_SHAPH,
	char const *			_hoops_GIAPH,
	_hoops_APSHA			_hoops_IHAPH);

GLOBAL_FUNCTION void HI_Enable_Button_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_IRPPH,
	char const *			_hoops_CRPPH);

GLOBAL_FUNCTION void HI_Disable_Button_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_IRPPH,
	char const *			_hoops_CRPPH);

GLOBAL_FUNCTION void HI_Disable_Location_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_SHAPH,
	char const *			_hoops_GIAPH,
	_hoops_APSHA			_hoops_IHAPH);

GLOBAL_FUNCTION void HI_Disable_Selection_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_SHAPH,
	char const *			_hoops_GIAPH);

GLOBAL_FUNCTION void HI_Enable_Selection_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_SHAPH,
	char const *			_hoops_GIAPH);

GLOBAL_FUNCTION void HC_CDECL HI_Enable_Wakeup_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	float					_hoops_PHSAP);

GLOBAL_FUNCTION bool HI_Disable_Wakeup_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	float					_hoops_PHSAP);

GLOBAL_FUNCTION void HI_Define_Error_Handler (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GHSAP	_hoops_APRPR); 

GLOBAL_FUNCTION void HI_UnDefine_Error_Handler (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GHSAP	_hoops_APRPR);

GLOBAL_FUNCTION void HI_Requeue_Event (_hoops_AIGPR * _hoops_RIGC);

GLOBAL_FUNCTION void HI_Exit_Program ();

GLOBAL_FUNCTION void HI_Show_One_Conditional_Action (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_SPPIR const *			conditions,
	char const *				action_type,
	char *						options,
	char *						condition);

GLOBAL_FUNCTION void HI_System_Memory_Purge();

/* _hoops_GRGCH-_hoops_IPPAR _hoops_IPPRA _hoops_PSCH */
GLOBAL_FUNCTION bool HI_Unset_Text_Font (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	_hoops_AGPIR *				_hoops_CAICA);

GLOBAL_FUNCTION bool HI_Unset_Color(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_SSGI *					color);

GLOBAL_FUNCTION bool HI_Unset_Driver_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	_hoops_GAPIR *		_hoops_PAICA);

GLOBAL_FUNCTION bool HI_Unset_Selectability(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ASAIR *			_hoops_AAICA); 

GLOBAL_FUNCTION bool HI_Unset_Visibility (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RSAIR *			_hoops_APHCR);

GLOBAL_FUNCTION bool HI_Unset_Rendering_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RHAIR *		_hoops_RCIHP);

GLOBAL_FUNCTION bool HI_Unset_Heuristics (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GHAIR *			heuristics);


/*******************************/

#endif /* _hoops_RRGCH */
