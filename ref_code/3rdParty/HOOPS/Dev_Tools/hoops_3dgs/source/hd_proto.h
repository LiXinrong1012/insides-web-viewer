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
 * $Id: obf_tmp.txt 1.637 2010-12-10 03:32:35 covey Exp $
 */

#ifndef HD_PROTO_DEFINED


#ifndef _hoops_IPRSP
#include "driver.h"
#endif


extern "C" bool HC_CDECL HD_CGM3_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_DX9_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_HPGL2_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_HPGL_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_Image_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_MSW_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_OpenGL_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter * _hoops_GHRI, int request, void * request_info);
#if 0
extern "C" bool HC_CDECL HD_MGL_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter * _hoops_GHRI, int request, void * request_info);
#endif
extern "C" bool HC_CDECL HD_OpenGL2_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter * _hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_PostScript_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_PDF_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_Printf_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_QT_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_Quartz_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_Whip2D_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_Win32_OpenGL_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter * _hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_Win32_OpenGL2_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter * _hoops_GHRI, int request, void * request_info);
extern "C" bool HC_CDECL HD_X11_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);



GLOBAL_FUNCTION int HD_Acquire_Clip_Points (
	Net_Rendition const & nr,
	Bounding const & bbox,
	int count,
	Point const *_hoops_AICAR,
	DC_Point alter *_hoops_PPHIH,
	float alter *ws,
	unsigned char alter *_hoops_RRCAR);

GLOBAL_FUNCTION void HD_Allow_For_Border (Display_Context alter *dc,
		 int _hoops_HIGRH,
		 int _hoops_IIGRH,
		 int _hoops_CIGRH,
		 int _hoops_SIGRH);
GLOBAL_FUNCTION bool HD_Artcore_Renderer (Net_Rendition const & nr, struct _hoops_HPHIH *_hoops_IPHIH);
GLOBAL_FUNCTION bool HD_Box_Outside_Cutting_Planes (_hoops_HHCR const & _hoops_IHCR,
		 float x,
		 float y,
		 float z,
		 int width,
		 int depth);
GLOBAL_FUNCTION bool HD_Box_Within_Cutting_Planes (_hoops_HHCR const  &_hoops_IHCR,
		 float x,
		 float y,
		 float z,
		 int width,
		 int depth);
GLOBAL_FUNCTION void HD_Buffer_DC_Polydot_C08_Z00 (Net_Rendition const & nr, int count, DC_Point const *_hoops_CPHIH);
GLOBAL_FUNCTION void HD_Buffer_DC_Polydot_C08_Z16 (Net_Rendition const & nr, int count, DC_Point const *_hoops_CPHIH);
GLOBAL_FUNCTION void HD_Buffer_DC_Polydot_C24_Z00 (Net_Rendition const & nr, int count, DC_Point const *_hoops_CPHIH);
GLOBAL_FUNCTION void HD_Buffer_DC_Polydot_C24_Z16 (Net_Rendition const & nr, int count, DC_Point const *_hoops_CPHIH);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z00_C (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors,
		 bool single);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z00_G (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z00_U (Net_Rendition const & nr, int count,  DC_Point const *points);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z16_C (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *color,
		 bool single);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z16_G (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z16_U (Net_Rendition const & nr, int count,  DC_Point const *points);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z00_C (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors,
		 bool single);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z00_G (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z00_U (Net_Rendition const & nr, int count,  DC_Point const *points);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z16_C (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors,
		 bool single);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z16_G (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z16_U (Net_Rendition const & nr, int count,  DC_Point const *points);
GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C08_Z00 (Net_Rendition const & nr,
		 DC_Point const *_hoops_HCGCR,
		 DC_Point const *_hoops_ICGCR,
		 int row_bytes,
		 unsigned char const *_hoops_GAAC);
GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C08_Z16 (Net_Rendition const & nr,
		 DC_Point const *_hoops_HCGCR,
		 DC_Point const *_hoops_ICGCR,
		 int row_bytes,
		 unsigned char const *_hoops_GAAC);
GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C24_Z00 (Net_Rendition const & nr,
		 DC_Point const *_hoops_HCGCR,
		 DC_Point const *_hoops_ICGCR,
		 int row_bytes,
		 RGBAS32 const *_hoops_GAAC);
GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C24_Z16 (Net_Rendition const & nr,
		 DC_Point const *_hoops_HCGCR,
		 DC_Point const *_hoops_ICGCR,
		 int row_bytes,
		 RGBAS32 const *_hoops_GAAC);
GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C32_Z00 (Net_Rendition const & nr,
		 DC_Point const *_hoops_HCGCR,
		 DC_Point const *_hoops_ICGCR,
		 int row_bytes,
		 RGBAS32 const *_hoops_GAAC);
GLOBAL_FUNCTION void HD_Buffer_DC_Raster_C32_Z16 (Net_Rendition const & nr,
		 DC_Point const *_hoops_HCGCR,
		 DC_Point const *_hoops_ICGCR,
		 int row_bytes,
		 RGBAS32 const *_hoops_GAAC);
GLOBAL_FUNCTION void HD_Buffer_DC_Rectangle_C08 (Net_Rendition const & nr, int left, int right, int bottom, int top);
GLOBAL_FUNCTION void HD_Buffer_DC_Rectangle_C24 (Net_Rendition const & nr, int left, int right, int bottom, int top);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z00_C (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors,
		 bool single);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z00_G (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z00_U (Net_Rendition const & nr, int count,  DC_Point const *points);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z16_C (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors,
		 bool single);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z16_G (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z16_U (Net_Rendition const & nr, int count,  DC_Point const *points);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z00_C (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors,
		 bool single);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z00_G (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z00_U (Net_Rendition const & nr, int count,  DC_Point const *points);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z16_C (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors,
		 bool single);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z16_G (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z16_U (Net_Rendition const & nr, int count,  DC_Point const *points);
GLOBAL_FUNCTION void HD_Calculate_Outer_Window (Net_Rendition alter & nr);
GLOBAL_FUNCTION bool HD_Calc_Image_Position_And_Size(Net_Rendition const & nr,
		 Image const *image, int *width, int *height, float *_hoops_SPHIH, float *_hoops_GHHIH, float *_hoops_RHHIH);
GLOBAL_FUNCTION void HD_Choose_Font (Net_Rendition const & nr,
		 _hoops_IGPIR const *_hoops_AHHIH,
		 char encoding,
		 bool _hoops_AARHP);
GLOBAL_FUNCTION void HD_Clear_Software_Z_Buffer (Net_Rendition const & nr);
GLOBAL_FUNCTION void  HD_Compute_Hard_Clip (Net_Rendition alter & nr,
		 _hoops_PACIR const *_hoops_HCRRH);
GLOBAL_FUNCTION void HD_Clip_DC_Face (
	Net_Rendition const & nr,
	int count,
	DC_Point const * points,
	RGBAS32 const *color,
	int flags);
GLOBAL_FUNCTION void HD_Clip_DC_Polydot (
	Net_Rendition const & nr,
	int count,
	DC_Point const * points,
	RGBAS32 const *_hoops_PHHIH,
	int flags);
GLOBAL_FUNCTION void HD_Clip_DC_Polyline (
	Net_Rendition const & nr,
	int count,
	DC_Point const * points,
	RGBAS32 const *_hoops_PHHIH,
	RGBA const *rgba_colors,
	_hoops_ARPA const * planes,
	_hoops_RSSH const *_hoops_CCHA,
	int param_width,
	_hoops_SSIC param_flags,
	int flags);
GLOBAL_FUNCTION void HD_Clip_DC_Polytriangle (
	Net_Rendition const & nr,
	int count,
	DC_Point const * points,
	RGBAS32 const *_hoops_PHHIH,
	RGBA const *rgba_colors,
	_hoops_ARPA const * planes,
	_hoops_RSSH const *_hoops_CCHA,
	int param_width,
	_hoops_SSIC param_flags,
	int flags);
GLOBAL_FUNCTION void HD_Clip_DC_Text (
	Net_Rendition const & _hoops_ACRIP,
	DC_Point const * position,
	int count,
	unsigned short const *kstring);
GLOBAL_FUNCTION void HD_Clip_Poly (
		 Int_Rectangle const * _hoops_HHHIH,
		 int _hoops_IAAGA,
		 DC_Point const * in_points,
		 int alter * _hoops_CAAGA,
		 DC_Point alter * out_points,
		 bool close);
GLOBAL_FUNCTION void HD_Compute_One_World_Plane (_hoops_SGCC const &_hoops_HSGA,
		 Vector const *normal,
		 Point const *point,
		 _hoops_ARPA alter *plane);
GLOBAL_FUNCTION void HD_Compute_Screen_Plane_Facings (Net_Rendition const & nr,
		 int count, _hoops_ARPA const *planes, bool _hoops_CRCPH, int alter *directions);
GLOBAL_FUNCTION void HD_Compute_Screen_Plane_Dot_Products (Net_Rendition const & nr,
		 int count, _hoops_ARPA const *planes, bool _hoops_CRCPH, float alter *_hoops_IHHIH);
GLOBAL_FUNCTION void HD_Compute_Screen_Transform (Net_Rendition const & nr,
		 Point alter *scale,
		 Point alter *translate);
GLOBAL_FUNCTION int HD_Compute_Trimmed_Clip_Points (_hoops_HHCR const & _hoops_IHCR,
		 int count,
		 DC_Point const *_hoops_CGCAR, float const *ws, unsigned char alter *_hoops_RRCAR);
GLOBAL_FUNCTION void HD_Compute_World_Edge_Planes (Net_Rendition const & nr,
		 Polyedge const *pe,
		 _hoops_ARPA alter *planes);
GLOBAL_FUNCTION void HD_Compute_World_Face_Planes (Net_Rendition const & nr,
		 Polyhedron const *_hoops_IPRI,
		 _hoops_ARPA alter *planes);
GLOBAL_FUNCTION void HD_Compute_World_Vertex_Planes (Net_Rendition const & nr,
		 int count,
		 Point const *points,
		 Vector const *normals,
		 _hoops_ARPA alter *planes);
GLOBAL_FUNCTION bool HD_Connect_Standard_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void (*_hoops_SRGRH) (_hoops_APARR alter & _hoops_RRCI));
GLOBAL_FUNCTION _hoops_GPPA* HD_Create_Hard_Clip_Cuts(Net_Rendition const & inr, Int_Rectangle const *_hoops_HHHIH, _hoops_HRPA const *mat, int bias);
GLOBAL_FUNCTION int HD_Cut_Hidden_By_Plane (Display_Context const * dc, _hoops_CASS alter *_hoops_GIISA, _hoops_ARPA alter *plane, bool _hoops_RIISA);
GLOBAL_FUNCTION Line_Style HD_Define_Line_Style_Legacy(Net_Rendition const & nr, void * pointer, int _hoops_CHHIH, int _hoops_SHHIH, bool _hoops_GIHIH);
GLOBAL_FUNCTION void HD_Defer_Tree (Net_Rendition const & nr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path, Geometry const * geometry = 0);
GLOBAL_FUNCTION void HD_Defer_Tree_Batch (Net_Rendition const & nr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path, int _hoops_RIHIH, Geometry const * geometry = 0, int _hoops_RRCRP=-1);
GLOBAL_FUNCTION int HD_Determine_Elliptical_Res (Net_Rendition const & nr, _hoops_GHHI const *curve);
GLOBAL_FUNCTION void HD_Determine_Fixed_Colors (Display_Context const *dc, int start, int alter *fixed, int alter *_hoops_CAGCR);
GLOBAL_FUNCTION void HD_Downwind_Camera (Net_Rendition alter & nr, Attribute const *_hoops_ASGPR);
GLOBAL_FUNCTION _hoops_HHA HD_Downwind_Named_Material (Net_Rendition const & nr, _hoops_HHA const & mat, Named_Material const * _hoops_RGHHP);
GLOBAL_FUNCTION int  HD_Downwind_Color (Net_Rendition alter & nr,
		 _hoops_SSGI const *color, _hoops_ACHR _hoops_RCGC, _hoops_PIGRA const * lock);
GLOBAL_FUNCTION void  HD_Downwind_Color_Map (Net_Rendition alter & nr, Attribute const *_hoops_ASGPR);
GLOBAL_FUNCTION void  HD_Downwind_Handedness (Net_Rendition alter & nr, Attribute const *_hoops_ASGPR);
GLOBAL_FUNCTION void  HD_Downwind_Rendition (Net_Rendition alter & nr, Attribute const *_hoops_HPPGR, _hoops_ACHR _hoops_RCGC, bool _hoops_CAGIP);
GLOBAL_FUNCTION int  HD_Downwind_Text_Font (Net_Rendition alter & nr, _hoops_AGPIR const *font);
GLOBAL_FUNCTION void  HD_Downwind_Window (Net_Rendition alter & nr, Attribute const *_hoops_ASGPR);
GLOBAL_FUNCTION void  HD_Downwind_Window_Frame (Net_Rendition alter & nr, Attribute const *_hoops_ASGPR);
GLOBAL_FUNCTION void  HD_Downwind_Modelling_Matrix (
		 Net_Rendition alter & nr,
		 Attribute const *_hoops_ASGPR);
GLOBAL_FUNCTION void  HD_Append_Modelling_Matrix (
		 Net_Rendition alter & nr,
		 _hoops_HRPA const *matrix);
GLOBAL_FUNCTION void HD_Draw_Defined_Font (Net_Rendition const & in_nr,
		 Font_Instance const *specific,
		 Point const *where,
		 int count,
		 unsigned short const *string,
		 Vector const *scale);
GLOBAL_FUNCTION void HD_Draw_Clipped_DC_Image (Net_Rendition const & nr,
		 DC_Point const *start,
		 DC_Point const *end,
		 int hoffset,
		 char format,
		 int row_bytes,
		 void const * const *rasters,
		 int pattern,
		 Driver_Color const *contrast_color,
		 Image const *db_image);
GLOBAL_FUNCTION void HD_Draw_Deferred_Trees (Display_Context alter *dc);

GLOBAL_FUNCTION void HD_Revisit_Overlay (Display_Context alter *dc);
	
GLOBAL_FUNCTION void HD_Draw_Freetype_Font (Net_Rendition const & nr,
		 Font_Instance const *specific,
		 Point const *where,
		 int count,
		 unsigned short const *string,
		 Vector const *scale);
GLOBAL_FUNCTION void HD_Draw_Glyphs (
		 Net_Rendition const &	in_nr,
		 _hoops_GASC const *			glyphs,
		 int					count,
		 DC_Point const *		points,
		 RGBAS32 const *		colors,
		 bool					_hoops_AIPSP,
		 float const *			rotations,
		 float const *			size_fixups);
GLOBAL_FUNCTION _hoops_CASS alter * HD_Draw_Hidden_Item (_hoops_CASS alter *hidden, bool _hoops_CHGCP);
GLOBAL_FUNCTION void HD_Draw_Indexicated_3D_Polyedge (Net_Rendition const & inr, Polyedge const *_hoops_RASGR);
GLOBAL_FUNCTION void HD_Draw_Indexicated_3D_Tristrip (Net_Rendition const & inr, Tristrip const *its);
GLOBAL_FUNCTION void HD_Isoline_From_Tristrip (Net_Rendition const & inr, Tristrip const *its);
GLOBAL_FUNCTION void HD_Assemble_Isolines (
	Net_Rendition const & 			nr,
	Polyhedron const *				_hoops_IPRI,
	unsigned short /* _hoops_AIHIH */	_hoops_PIHIH);
GLOBAL_FUNCTION int HD_Process_Isolines (
	Display_Context * dc,
	Geometry const * geometry,
	Bounding const & bounding,
	Polyedge * * _hoops_ASRGR,
	float tolerance);
GLOBAL_FUNCTION void HD_Draw_Lighted_Face (Net_Rendition const & nr,
		 int count,
		 DC_Point const *_hoops_GHPCP,
		 Geometry const *geometry);
GLOBAL_FUNCTION void HD_Draw_Lighted_Polygon (Net_Rendition const & nr,
		 int count,
		 DC_Point const *_hoops_GHPCP,
		 Geometry const *geometry);
GLOBAL_FUNCTION void HD_Prepare_Overlay_Tree (Net_Rendition alter & nr, _hoops_CRCP const *_hoops_SRCP);
GLOBAL_FUNCTION void HD_Draw_Partial_Erase_Tree (Net_Rendition const & inr, _hoops_CRCP const *start, _hoops_HICS const & path, bool _hoops_HGRHP);
GLOBAL_FUNCTION void HD_Draw_Silhouette_Edges (Net_Rendition const & nr, Polyedge const *_hoops_RASGR);
GLOBAL_FUNCTION void HD_Draw_NonCulled_Edges (Net_Rendition const & nr, Polyedge const *_hoops_RASGR);
GLOBAL_FUNCTION void HD_Prepare_Soft_Z_Buffered_Tree (Net_Rendition alter & nr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path);
GLOBAL_FUNCTION void HD_Draw_Sprites (Display_Context alter *dc, _hoops_HCSIR alter *_hoops_ICSIR, bool _hoops_GAGSP, bool _hoops_RAGSP);
GLOBAL_FUNCTION void HD_Draw_Trimmed_DC_Image (Net_Rendition const & nr,
		 DC_Point const *start,
		 DC_Point const *end,
		 int hoffset,
		 char format,
		 int row_bytes,
		 void const * const *rasters,
		 int pattern,
		 Driver_Color const *contrast_color,
		 Image const *db_image);
GLOBAL_FUNCTION void HD_Elaborate_Selection (Net_Rendition const & nr,
		 Geometry const *item,
		 Key _hoops_HSICA,
		 Key _hoops_CISAP,
		 int offset1,
		 int offset2,
		 int offset3,
		 float _hoops_RCSAP,
		 float _hoops_HCSAP,
		 Integer32 _hoops_PCCAH,
		 _hoops_AISAP * _hoops_ACSAP);
GLOBAL_FUNCTION bool HD_Exit_Update (Display_Context const *dc);
GLOBAL_FUNCTION void HD_Interrupt_Update (Display_Context const *dc, bool _hoops_GPARH, bool _hoops_RPARH);
GLOBAL_FUNCTION void HD_Figure_Light (Net_Rendition const & nr, Geometry const *geometry, RGBA alter *total);
GLOBAL_FUNCTION void HD_Find_One_Font (Display_Context const *dc);
GLOBAL_FUNCTION void HD_Find_Basic_Fonts (Display_Context const *dc);
GLOBAL_FUNCTION void HD_Find_All_Fonts (Display_Context const *dc);
GLOBAL_FUNCTION void HD_Find_Cutting_Planes (Net_Rendition alter & nr, _hoops_CRCP const *_hoops_SRCP);
GLOBAL_FUNCTION Display_Context alter * HD_Find_DC_From_WID (POINTER_SIZED_INT _hoops_RSGRH);
GLOBAL_FUNCTION int HD_Find_Dither_Pattern (Net_Rendition const & nr,
		 RGBAS32 const *target,
		 unsigned short alter *_hoops_ASGRH,
		 int alter *_hoops_AHHIR);
GLOBAL_FUNCTION Font_Instance const * HD_Find_Fill_In_Font (Net_Rendition const & in_nr, Font_Instance const * _hoops_HIHIH, unsigned short _hoops_IIHIH, unsigned short * _hoops_CIHIH);
GLOBAL_FUNCTION void HD_Find_Font_Height (Display_Context const *dc, Font_Instance const *_hoops_SIHIH);
GLOBAL_FUNCTION void HD_Find_Freetype_Fonts (Display_Context const *dc);
GLOBAL_FUNCTION bool HD_Find_One_Freetype_Font (Display_Context const *dc, char const *_hoops_PACSR);
GLOBAL_FUNCTION void HD_Find_Geometry_Screen_Plane (Net_Rendition const & nr,
		 Geometry const *geometry,
		 _hoops_ARPA alter *plane);
GLOBAL_FUNCTION float HD_Find_Geometry_Screen_Plane_C (Net_Rendition const & nr, Geometry const *geometry);
GLOBAL_FUNCTION _hoops_GASC HD_Find_Glyph(_hoops_GHRIP const & _hoops_RRA, const char * _hoops_HSIHH, _hoops_HCRPR const * name, Integer32 key, bool error);
GLOBAL_FUNCTION _hoops_GASC HD_Find_Glyph_Legacy(Net_Rendition const & nr, char symbol);
GLOBAL_FUNCTION char HD_Find_Glyph_Legacy_Symbol(_hoops_GASC const & glyph);
GLOBAL_FUNCTION Line_Style HD_Find_Line_Style(Net_Rendition const & nr, const char * name);
GLOBAL_FUNCTION Line_Style HD_Find_Line_Style_Legacy(Net_Rendition const & nr, char symbol);
GLOBAL_FUNCTION char HD_Find_Line_Style_Legacy_P(Line_Style const & line_style);
GLOBAL_FUNCTION void HD_Find_Lights (Net_Rendition alter & nr, _hoops_CRCP const *_hoops_SRCP);
GLOBAL_FUNCTION void HD_Finish_Priority_Inclusion (Net_Rendition const & nr);
GLOBAL_FUNCTION void HD_Force_Font_Load (Net_Rendition const & nr);
GLOBAL_FUNCTION void HD_Force_Partial_Refresh (Display_Context const *dc, int left, int right, int bottom, int top);
GLOBAL_FUNCTION void HD_Force_Refresh (Display_Context const *dc);
GLOBAL_FUNCTION void HD_Free_Colors (Display_Context alter *dc);
GLOBAL_FUNCTION void HD_Free_Defined_Font_Family (Display_Context alter *dc, _hoops_RCSSP alter *family);
GLOBAL_FUNCTION void HD_Free_Fonts (Display_Context alter *dc);
GLOBAL_FUNCTION void HD_Free_Frame_Buffer_Info (Net_Rendition const & nr, _hoops_HCSIR const *_hoops_ICSIR);
GLOBAL_FUNCTION void HD_Free_Freetype_Globals (_hoops_IGHGP *_hoops_SSGGA);
GLOBAL_FUNCTION void HD_Free_Hidden_List (Display_Context const * dc, _hoops_CASS alter *hidden);
GLOBAL_FUNCTION void HD_Free_Hidden_Payload (Display_Context const * dc, _hoops_SRHSA alter *_hoops_ASHSA);
GLOBAL_FUNCTION void HD_Free_Material_Rendition (_hoops_HHA const *mat);
GLOBAL_FUNCTION void HD_Free_Sprite_List (Display_Context alter *dc, _hoops_HSIIP alter * alter *backlink);
GLOBAL_FUNCTION void HD_Free_Overlay_Segments (_hoops_SCCIP alter * alter *_hoops_ASRGR);
GLOBAL_FUNCTION void HD_Free_Window_Rendition (_hoops_CGRA const *_hoops_SGRA);
GLOBAL_FUNCTION bool HD_Gather_Device_Info (Display_Context const *dc, _hoops_APRHH alter *_hoops_PPRHH);
GLOBAL_FUNCTION bool HD_Gather_Font_Info (Display_Context alter *dc, _hoops_PGHGH alter *_hoops_GCHIH);
GLOBAL_FUNCTION bool HD_Gather_Font_Names (Display_Context const *dc, _hoops_RCHIH alter *_hoops_ACHIH);
GLOBAL_FUNCTION void HD_Gather_Freetype_Text (Net_Rendition const & nr,
		 Font_Instance const *specific,
		 int count,
		 unsigned short const *string,
		 Vector const *scale,
		 char encoding,
		 _hoops_PGHGH *_hoops_GCHIH);
GLOBAL_FUNCTION bool HD_Gather_Screen_Extent (Display_Context alter *dc, _hoops_RISAA alter *_hoops_AISAA);
GLOBAL_FUNCTION bool HD_Gather_Text_Extent (Display_Context alter *dc, _hoops_PGHGH alter *_hoops_GCHIH);
GLOBAL_FUNCTION bool HD_Gather_Text_Outline (Display_Context alter *dc, _hoops_PGHGH alter *_hoops_GCHIH);
GLOBAL_FUNCTION bool HD_Gather_Window_Extent (Display_Context alter *dc, _hoops_RIACA alter *_hoops_AIACA);
GLOBAL_FUNCTION int alter * HD_Generate_DC_Screen_Facings (Net_Rendition const & nr, int count, _hoops_ARPA const * planes, bool _hoops_CRCPH);
GLOBAL_FUNCTION int HD_Generate_Elliptical_Points (Net_Rendition const & nr,
		 _hoops_GHHI const *curve,
		 int _hoops_HGII,
		 Point alter *_hoops_IAIRA);
GLOBAL_FUNCTION void HD_Get_Actions (_hoops_APARR alter & _hoops_RRCI, void (*_hoops_ARSHH) (_hoops_APARR alter & _hoops_RRCI));
GLOBAL_FUNCTION void HD_Get_Bit_Patterns (Display_Context alter *dc, bool _hoops_CIPAR);
GLOBAL_FUNCTION void HD_Get_Bit_Patterns_8 (Display_Context alter *dc, bool _hoops_CIPAR);
GLOBAL_FUNCTION void HD_Get_Colors (Display_Context alter *dc);
GLOBAL_FUNCTION void HD_Get_Current_Info (Display_Context alter *dc);
GLOBAL_FUNCTION void HD_Get_Gamma_Table (Display_Context alter *dc, bool _hoops_GGGIH);
GLOBAL_FUNCTION void HD_Get_Physical_Info (Display_Context alter *dc);
GLOBAL_FUNCTION void HD_HL_DC_Colorized_Polytris (Net_Rendition const & nr, int count,
		 DC_Point const * points,
		 RGBAS32 const * color, bool single);
GLOBAL_FUNCTION void HD_HL_DC_Colorized_Polyline (Net_Rendition const & nr, int count,
		 DC_Point const * points,
		 RGBAS32 const * color, bool single);
GLOBAL_FUNCTION void HD_HL_DC_Colorized_Polymarker (Net_Rendition const & nr, int count,
		 DC_Point const * points,
		 RGBAS32 const * color, bool single, float const * rotations, float const *size_fixups);
GLOBAL_FUNCTION void HD_HL_DC_Gouraud_Polyline (Net_Rendition const & nr, int count,
		 DC_Point const * points,
		 RGBAS32 const * colors);
GLOBAL_FUNCTION void HD_HL_DC_Gouraud_Polytris (Net_Rendition const & nr, int count,
		 DC_Point const * points,
		 RGBAS32 const * colors);
GLOBAL_FUNCTION void HD_HL_3D_Image (Net_Rendition const & nr, Image const * image);
GLOBAL_FUNCTION void HD_HL_DC_Image (Net_Rendition const & nr,
		 DC_Point const * start,
		 DC_Point const * end,
		 int hoffset,
		 char format,
		 int row_bytes,
		 void const * const * rasters,
		 int pattern,
		 Driver_Color const * contrast_color,
		 Image const *db_image);
GLOBAL_FUNCTION void HD_HL_DC_Polymarker (
		 Net_Rendition const & nr,
		 int count,
		 DC_Point const * point,
		 float const * rotations,
		 float const *size_fixups);
GLOBAL_FUNCTION void HD_HL_DC_Polydot(
		 Net_Rendition const & nr, 
		 int count, 
		 DC_Point const * point);
GLOBAL_FUNCTION void HD_HL_DC_Colorized_Polydot(
		 Net_Rendition const & nr, 
		 int count, 
		 DC_Point const * point,
		 RGBAS32 const * _hoops_IASGR,
		 bool	single);
GLOBAL_FUNCTION void HD_HL_DC_Polyline (Net_Rendition const & nr, int count, DC_Point const * points);
GLOBAL_FUNCTION void HD_HL_DC_Polytriangle (Net_Rendition const & nr, int count, DC_Point const * points);
GLOBAL_FUNCTION void HD_HL_DC_Phong_Polyline (Net_Rendition const & nr, int count,
		 DC_Point const * points,
		 RGBA const * colors,
		 _hoops_ARPA const * planes);
GLOBAL_FUNCTION void HD_HL_DC_Textured_Polyline (Net_Rendition const & nr, int count,
		 DC_Point const * points,
		 RGBA const * colors,
		 _hoops_ARPA const * planes,
		 _hoops_RSSH const *_hoops_CCHA,
		 int param_width,
		 _hoops_SSIC alter param_flags);
GLOBAL_FUNCTION void HD_HL_DC_Phong_Polytris (Net_Rendition const & nr, int count,
		 DC_Point const * points,
		 RGBA const * colors,
		 _hoops_ARPA const * planes);
GLOBAL_FUNCTION void HD_HL_DC_Textured_Polytris (Net_Rendition const & nr, int count,
		 DC_Point const * points,
		 RGBA const * colors,
		 _hoops_ARPA const * planes,
		 _hoops_RSSH const *_hoops_CCHA,
		 int param_width,
		 _hoops_SSIC alter param_flags);
GLOBAL_FUNCTION void HD_HL_DC_Text (Net_Rendition const & nr, DC_Point const *where, int count, unsigned short const *kstring);
GLOBAL_FUNCTION void HD_HL_Plain_Text (Net_Rendition const & nr,
		 _hoops_HACC const * _hoops_PCHIH,
		 Point const * point,
		 int count,
		 unsigned short const * _hoops_IHSCP,
		 _hoops_PGCSR const * ki);
GLOBAL_FUNCTION void HD_HL_DC_Text_Rasters (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	RGBAS32 const *				rasters);
GLOBAL_FUNCTION void HD_HL_See_Whats_Hidden (Net_Rendition const & nr);
GLOBAL_FUNCTION void HD_Hide_DC_Colorized_Face (Net_Rendition const & nr,
		 int count,
		 DC_Point const *points,
		 RGBAS32 const *color);
GLOBAL_FUNCTION void HD_Hide_DC_Colorized_Polyline (Net_Rendition const & nr, int count, DC_Point const *_hoops_GHPCP, RGBAS32 const *color, bool single);
GLOBAL_FUNCTION void HD_Hide_DC_Colorized_Polytris (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *color, bool single);
GLOBAL_FUNCTION void HD_Hide_DC_Face (Net_Rendition const & nr, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Hide_DC_Gouraud_Polyline (Net_Rendition const & nr, int count, DC_Point const *_hoops_GHPCP, RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Hide_DC_Gouraud_Polytris (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Hide_DC_Image (Net_Rendition const & nr,
		 DC_Point const *start,
		 DC_Point const *end,
		 int hoffset,
		 char format,
		 int row_bytes,
		 void const * const *rasters,
		 int pattern,
		 Driver_Color const *contrast_color,
		 Image const *db_image);
GLOBAL_FUNCTION void HD_Hide_DC_Polydot (Net_Rendition const & nr, int count, DC_Point const *_hoops_GHPCP);
GLOBAL_FUNCTION void HD_Hide_DC_Colorized_Polydot (Net_Rendition const & nr, int count, DC_Point const *_hoops_GHPCP, RGBAS32 const *color, bool single);
GLOBAL_FUNCTION void HD_Hide_DC_Polygon (Net_Rendition const & nr, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Hide_DC_Polyline (Net_Rendition const & nr, int count, DC_Point const *_hoops_GHPCP);
GLOBAL_FUNCTION void HD_Hide_DC_Polytriangle (Net_Rendition const & nr, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Hide_DC_Phong_Polyline (Net_Rendition const & nr, int count,
		 DC_Point const *_hoops_GHPCP,
		 RGBA const *colors,
		 _hoops_ARPA const *planes);
GLOBAL_FUNCTION void HD_Hide_DC_Phong_Polytris (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBA const *colors,
		 _hoops_ARPA const *planes);
GLOBAL_FUNCTION void HD_Hide_DC_Textured_Polyline (Net_Rendition const & nr, int count,
		 DC_Point const *_hoops_GHPCP,
		 RGBA const *colors,
		 _hoops_ARPA const *planes,
		 _hoops_RSSH const *_hoops_CCHA,
		 int param_width,
		 _hoops_SSIC param_flags);
GLOBAL_FUNCTION void HD_Hide_DC_Textured_Polytris (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBA const *colors,
		 _hoops_ARPA const *planes,
		 _hoops_RSSH const *_hoops_CCHA,
		 int param_width,
		 _hoops_SSIC param_flags);
GLOBAL_FUNCTION void HD_Hide_DC_Stenciled_Quad (Net_Rendition const & nr,
		 DC_Point const *points,
		 _hoops_RAARP const *stencil);
GLOBAL_FUNCTION void HD_Hide_DC_Text (Net_Rendition const & nr, DC_Point const *where, int count, unsigned short const *kstring);
GLOBAL_FUNCTION void HD_Hide_Plain_Text (
		 Net_Rendition const & nr,
		 _hoops_HACC const * _hoops_PCHIH,
		 Point const * position,
		 int count,
		 unsigned short const * _hoops_IHSCP,
		 _hoops_PGCSR const * ki);
GLOBAL_FUNCTION void HD_Image_To_Bit_Rasters (Net_Rendition const & nr,
		 DC_Point const *_hoops_HCGCR,
		 DC_Point const *_hoops_ICGCR,
		 int hoffset,
		 char format,
		 int row_bytes,
		 void const * const *_hoops_HCHIH,
		 int pattern,
		 Driver_Color const *contrast_color,
		 Image const *db_image);
GLOBAL_FUNCTION void HD_Image_To_Gray8_Rasters (Net_Rendition const & nr,
		 DC_Point const *_hoops_HCGCR,
		 DC_Point const *_hoops_ICGCR,
		 int hoffset,
		 char format,
		 int row_bytes,
		 void const * const *_hoops_HCHIH,
		 int pattern,
		 Driver_Color const *contrast_color,
		 Image const *db_image);
GLOBAL_FUNCTION void HD_Image_To_Mapped16_Rasters (Net_Rendition const & nr,
		 DC_Point const *_hoops_HCGCR,
		 DC_Point const *_hoops_ICGCR,
		 int hoffset,
		 char format,
		 int row_bytes,
		 void const * const *_hoops_HCHIH,
		 int pattern,
		 Driver_Color const *contrast_color,
		 Image const *db_image);
GLOBAL_FUNCTION void HD_Image_To_Mapped8_Rasters (Net_Rendition const & nr,
		 DC_Point const *_hoops_HCGCR,
		 DC_Point const *_hoops_ICGCR,
		 int hoffset,
		 char format,
		 int row_bytes,
		 void const * const *_hoops_HCHIH,
		 int pattern,
		 Driver_Color const *contrast_color,
		 Image const *db_image);
GLOBAL_FUNCTION void HD_Image_To_RGB32_Rasters (Net_Rendition const & nr,
		 DC_Point const *_hoops_HCGCR,
		 DC_Point const *_hoops_ICGCR,
		 int hoffset,
		 char format,
		 int row_bytes,
		 void const * const *_hoops_HCHIH,
		 int pattern,
		 Driver_Color const *contrast_color,
		 Image const *db_image);
GLOBAL_FUNCTION _hoops_HCSIR alter * HD_Init_Frame_Buffer_Info (Net_Rendition const & nr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path);
GLOBAL_FUNCTION void HD_Initialize_HL_Data (Display_Context alter *dc);
GLOBAL_FUNCTION void HD_Insert_In_Hidden_Tree (_hoops_CASS alter *item);
GLOBAL_FUNCTION void HD_Kill_Driver (Display_Context const *dc);
GLOBAL_FUNCTION void HD_Linearize_Hidden_Tree (Display_Context const * dc, _hoops_CASS alter *x, int count, int _hoops_ICHIH, _hoops_CASS alter **_hoops_CCHIH, _hoops_CASS alter **_hoops_SCHIH);
GLOBAL_FUNCTION bool HD_Load_Font (Display_Context const *dc, Font_Instance const *_hoops_SIHIH);
GLOBAL_FUNCTION bool HD_Unload_Oldest_Font (Display_Context alter *dc, int _hoops_GSHIH);
GLOBAL_FUNCTION void * HD_Load_Defined_Font (Display_Context const *dc, char const *name, Font_Instance alter *font);
GLOBAL_FUNCTION void HD_Get_Freetype_Font_Bounding (Font_Instance const * instance, _hoops_SASC alter & _hoops_RSHIH);
GLOBAL_FUNCTION void * HD_Load_Freetype_Font (Display_Context const *dc, char const *name, Font_Instance alter *instance);
GLOBAL_FUNCTION bool HD_Mark_Font_As_Aliased (Display_Context const *dc, char const *name, char const *_hoops_ASHIH, long index);
GLOBAL_FUNCTION bool HD_Mark_Font_As_Defined (Display_Context const *dc, char const *name, _hoops_PGIIR const *font);
GLOBAL_FUNCTION bool HD_Mark_Font_As_Freetype (Display_Context const *dc, char const *name);
GLOBAL_FUNCTION bool HD_Mark_Font_As_Generic (Display_Context const *dc, char const *name, int _hoops_SSSGP);
GLOBAL_FUNCTION bool HD_Mark_Font_As_System_Default (Display_Context const *dc, char const *name, float _hoops_ISISR);
GLOBAL_FUNCTION bool HD_Mark_Font_As_Transformable (Display_Context const *dc, char const *name, int _hoops_CAGGH);
GLOBAL_FUNCTION bool HD_Measure_Characters (Net_Rendition const & nr, int count, unsigned short const *_hoops_IHSCP, char const encoding, float *_hoops_GGGS);
GLOBAL_FUNCTION bool HD_Measure_Freetype_Char (Net_Rendition const & nr, Font_Instance const *font, unsigned short _hoops_IPCSR, float alter *_hoops_GGGS, bool alter *_hoops_AHPGR, void ** _hoops_SPCSR);
GLOBAL_FUNCTION bool HD_Measure_Defined_Char (Net_Rendition const & nr, Font_Instance const *font, unsigned short _hoops_IPCSR, float alter *_hoops_GGGS, bool alter *_hoops_PSHIH, void ** _hoops_SPCSR);
GLOBAL_FUNCTION bool HD_Minimum_Update (Display_Context alter *dc);
GLOBAL_FUNCTION float HD_NURBS_Point_Invert (_hoops_PIRGR const *curve, Point const *point);
GLOBAL_FUNCTION bool HD_No_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR const *_hoops_GHRI, int request, char const *_hoops_HSS);
GLOBAL_FUNCTION bool HD_No_Such_Keyboard (Display_Context const *dc, int alter *button, int alter *status);
GLOBAL_FUNCTION bool HD_No_Such_Locater (Display_Context const *dc, int alter *button, int alter *x, int alter *y);
GLOBAL_FUNCTION bool HD_Null_Driver (_hoops_AIGPR *	_hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);

GLOBAL_FUNCTION void HD_Painters_Bias_Z (_hoops_CASS alter *hidden, bool _hoops_AGRCA);
GLOBAL_FUNCTION bool HD_Point_Within_Cutting_Planes (_hoops_HHCR const & _hoops_IHCR, float x, float y, float z);
GLOBAL_FUNCTION bool HD_Point_Within_Cutting_Set (_hoops_IAPA const *_hoops_HRCAR, float x, float y, float z);
GLOBAL_FUNCTION void  HD_Preprocess (Net_Rendition alter & nr);
GLOBAL_FUNCTION void HD_Queue_Pixel_Location_Event (Display_Context const *dc, int status, int _hoops_CHCGR, int _hoops_SHCGR);
GLOBAL_FUNCTION void HD_Rasterize_DC_Spans_C08_U (Net_Rendition const & nr,
		 _hoops_GHISP const & _hoops_RHISP,
		 _hoops_AHISP const *span,
		 int _hoops_PHISP,
		 int bottom);
GLOBAL_FUNCTION void HD_Rasterize_DC_Spans_C24_G (Net_Rendition const & nr,
		 _hoops_GHISP const & _hoops_RHISP,
		 _hoops_AHISP const *span,
		 int _hoops_PHISP,
		 int bottom);
GLOBAL_FUNCTION void HD_Rasterize_DC_Spans_C24_R (Net_Rendition const & nr,
		 _hoops_GHISP const & _hoops_RHISP,
		 _hoops_AHISP const *span,
		 int _hoops_PHISP,
		 int bottom,
		 _hoops_SSIC param_flags);
GLOBAL_FUNCTION void HD_Rasterize_DC_Spans_C24_U (Net_Rendition const & nr,
		 _hoops_GHISP const & _hoops_RHISP,
		 _hoops_AHISP const *span,
		 int _hoops_PHISP,
		 int bottom);
GLOBAL_FUNCTION void HD_Record_Driver_Options (Display_Context alter *dc, Attribute const *_hoops_ASGPR);
GLOBAL_FUNCTION void HD_Record_Font (Display_Context const *dc,
		 char const *_hoops_HSHIH,
		 char const *_hoops_ISHIH,
		 float _hoops_ISISR,
		 float _hoops_IGGGH);
GLOBAL_FUNCTION void HD_Record_Font_With_Encoding (Display_Context const *dc,
		 char const *_hoops_HSHIH,
		 char const *_hoops_ISHIH,
		 char encoding,
		 float _hoops_ISISR,
		 float _hoops_IGGGH);
GLOBAL_FUNCTION Font_Instance const * HD_Record_Scaleable_Instance (
		Display_Context const *dc,
		Font_Instance const	*specific,
		float _hoops_ISISR,
		float _hoops_IGGGH);
GLOBAL_FUNCTION void HD_Redo_Screen (Net_Rendition const & nr, _hoops_HRPA alter *matrix);
GLOBAL_FUNCTION void HD_Remove_Hidden_Followers (_hoops_CASS alter *thing, _hoops_CASS alter *start);
GLOBAL_FUNCTION void HD_Report_Null_Color_Map (char const * _hoops_IPRI, _hoops_RHAH const * _hoops_CSIR);
GLOBAL_FUNCTION void HD_Resize_Subscreen (Display_Context const *_hoops_SAGRH,
		 bool _hoops_PPIPP,
		 int _hoops_GPGRH,
		 int _hoops_RPGRH,
		 int _hoops_APGRH,
		 int _hoops_PPGRH);

GLOBAL_FUNCTION void HD_SP_Hide_DC_Colorized_Line (Net_Rendition const & nr,
		 DC_Point const * points,
		 RGBAS32 const * color);
GLOBAL_FUNCTION void HD_SP_Hide_DC_Colorized_Trian (Net_Rendition const & nr,
		 DC_Point const * points,
		 RGBAS32 const * color);
GLOBAL_FUNCTION void HD_SP_Hide_DC_Gouraud_Line (Net_Rendition const & nr,
		 DC_Point const * points,
		 RGBAS32 const * colors);
GLOBAL_FUNCTION void HD_SP_Hide_DC_Gouraud_Trian (Net_Rendition const & nr,
		 DC_Point const * points,
		 RGBAS32 const * colors);
GLOBAL_FUNCTION void HD_SP_Hide_DC_Image (Net_Rendition const & nr,
		 DC_Point const * start,
		 DC_Point const * end,
		 int hoffset,
		 char format,
		 int row_bytes,
		 void const * const * rasters,
		 int pattern,
		 Driver_Color const * contrast_color,
		 Image const *db_image);
GLOBAL_FUNCTION void HD_SP_Hide_DC_Line (Net_Rendition const & nr, DC_Point const * points);
GLOBAL_FUNCTION void HD_SP_Hide_DC_Marker (Net_Rendition const & nr, DC_Point const * point);
GLOBAL_FUNCTION void HD_SP_Hide_DC_Reshaded_Line (Net_Rendition const & nr,
		 DC_Point const * points,
		 RGB const * colors,
		 _hoops_ARPA const * planes,
		 _hoops_RSSH const *_hoops_CCHA,
		 int param_width,
		 _hoops_SSIC alter param_flags);
GLOBAL_FUNCTION void HD_SP_Hide_DC_Reshaded_Trian (Net_Rendition const & nr,
		 DC_Point const * points,
		 RGB const * colors,
		 _hoops_ARPA const * planes,
		 _hoops_RSSH const *_hoops_CCHA,
		 int param_width,
		 _hoops_SSIC alter param_flags);
GLOBAL_FUNCTION void HD_SP_Hide_DC_Text (Net_Rendition const & nr, DC_Point const * where, int count, unsigned short const * kstring);
GLOBAL_FUNCTION void HD_SP_Hide_DC_Triangle (Net_Rendition const & nr, DC_Point const * points);
GLOBAL_FUNCTION void HD_SP_Hide_Plain_Text (Net_Rendition const & nr,
		 _hoops_HACC const * _hoops_PCHIH,
		 Point const * point,
		 int count,
		 unsigned short const * _hoops_IHSCP,
		 _hoops_PGCSR const * ki);
GLOBAL_FUNCTION void HD_See_Whats_Hidden (Net_Rendition const & nr);
GLOBAL_FUNCTION bool HD_Select_Circle_By_Polyline (Net_Rendition const & nr, DC_Point alter *center, float radius);
GLOBAL_FUNCTION void HD_Select_Dot (Net_Rendition const & nr,
		Geometry const *thing,
		Key _hoops_HSICA,
		Key _hoops_CISAP,
		Integer32 type,
		Point const *_hoops_CSAI);
GLOBAL_FUNCTION void HD_Select_Ellipse (Net_Rendition const & nr, Ellipse const *ellipse, bool _hoops_CSHIH);
GLOBAL_FUNCTION void HD_Select_Elliptical_Arc (Net_Rendition const & nr, Elliptical_Arc const *arc);
GLOBAL_FUNCTION void HD_Select_Grid (Net_Rendition const & nr, Grid const *grid);
GLOBAL_FUNCTION void HD_Select_Image (Net_Rendition const & nr, Image const *image);
GLOBAL_FUNCTION void HD_Select_Inner_Window (Subsegment alter *_hoops_SSGPR, Window_Tree alter *_hoops_SCAAR);
GLOBAL_FUNCTION void HD_Select_Marker (Net_Rendition const & nr, Marker const *marker);
GLOBAL_FUNCTION void HD_Select_Multimarker (Net_Rendition const & nr, _hoops_GRPGR const * _hoops_CPAI);
GLOBAL_FUNCTION void HD_Select_NURBS_Curve (Net_Rendition const & nr, _hoops_PIRGR alter *curve);
GLOBAL_FUNCTION void HD_Select_Cylinder (Net_Rendition const & nr, Cylinder const *cylinder);
GLOBAL_FUNCTION void HD_Select_PolyCylinder (Net_Rendition const & nr, PolyCylinder const *polycylinder);
GLOBAL_FUNCTION void HD_Select_Sphere (Net_Rendition const & nr, Sphere const *sphere);
GLOBAL_FUNCTION void HD_Select_NURBS_Surface (Net_Rendition const & nr, _hoops_APPGR const *_hoops_SSHIH);
GLOBAL_FUNCTION bool HD_Select_Point_By_Polygon (Net_Rendition const & nr, DC_Point alter *center);
GLOBAL_FUNCTION bool HD_Select_Point_List (Net_Rendition const & nr,
		 Geometry const *geometry,
		 int _hoops_ICGPA,
		 Point const *_hoops_IAIRA,
		 bool _hoops_SPGPA,
		 bool _hoops_CSHIH,
		 int alter *offset1,
		 int alter *offset2,
		 float alter *_hoops_HISAP,
		 float alter *_hoops_RCSAP);
GLOBAL_FUNCTION void HD_Select_Polyglin (Net_Rendition const & nr, Geometry const *geometry, bool _hoops_CSHIH);
GLOBAL_FUNCTION void HD_Select_Polyhedron (Net_Rendition const & nr, Polyhedron const *_hoops_IPRI);
GLOBAL_FUNCTION void HD_Select_Text (Net_Rendition const & nr, _hoops_HACC const *text);
GLOBAL_FUNCTION void  HD_Selection_Downwind (Net_Rendition alter & nr, Attribute const *_hoops_HPPGR);
GLOBAL_FUNCTION void HD_Selection_Render (Net_Rendition const & nr, Geometry const *geo, bool single);
GLOBAL_FUNCTION void HD_Selection_Walk_Tree (Net_Rendition const & inr, _hoops_CRCP const *_hoops_SRCP, _hoops_HICS const & path);
GLOBAL_FUNCTION void HD_Set_DC_Cutting_Planes (Net_Rendition const & nr);
GLOBAL_FUNCTION void HD_Set_Z_Buffering_Transform (Net_Rendition const & nr,
		 bool _hoops_GGIIH,
		 bool _hoops_RGIIH,
		 float _hoops_PCHH);
GLOBAL_FUNCTION bool HD_Setup_Frame_Buffer (Net_Rendition const & nr);
GLOBAL_FUNCTION void HD_Setup_Screen_Door (Net_Rendition alter & nr);
GLOBAL_FUNCTION void HD_Span_DC_Colorized_Polyline (Net_Rendition const & nr,
		 int count,
		 DC_Point const *points,
		 RGBAS32 const *_hoops_HICGR,
		 bool single);
GLOBAL_FUNCTION void HD_Span_DC_Colorized_Polytris (Net_Rendition const & nr,
		 int count,
		 DC_Point const *points,
		 RGBAS32 const *_hoops_HICGR,
		 bool single);
GLOBAL_FUNCTION void HD_Span_DC_Gouraud_Polyline (Net_Rendition const & nr, int count, DC_Point const *points, RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Span_DC_Gouraud_Polytris (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Span_DC_Polyline (Net_Rendition const & nr, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Span_DC_Rectangle (Net_Rendition const & nr, int left, int right, int bottom, int top);
GLOBAL_FUNCTION void HD_Span_DC_Phong_Polyline (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBA const *colors,
		 _hoops_ARPA const *planes);
GLOBAL_FUNCTION void HD_Span_DC_Textured_Polyline (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBA const *colors,
		 _hoops_ARPA const *planes,
		 _hoops_RSSH const *_hoops_CCHA,
		 int param_width,
		 _hoops_SSIC param_flags);
GLOBAL_FUNCTION void HD_Span_DC_Phong_Polytris (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBA const *colors,
		 _hoops_ARPA const *planes);
GLOBAL_FUNCTION void HD_Span_DC_Textured_Polytris (Net_Rendition const & nr, int count,
		 DC_Point const *points,
		 RGBA const *colors,
		 _hoops_ARPA const *planes,
		 _hoops_RSSH const *_hoops_CCHA,
		 int param_width,
		 _hoops_SSIC param_flags);
GLOBAL_FUNCTION void HD_Span_DC_Polytriangle (Net_Rendition const & nr, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Standard_Compute_Shading (Net_Rendition const & nr,
		 _hoops_PC const & _hoops_RPPHP,
		 _hoops_HHA const & _hoops_ISHIR,
		 Point const *_hoops_ICAGA,
		 RGB const *color,
		 _hoops_ARPA const *plane,
		 Vector const *_hoops_ASACP,
		 float const * params,
		 int param_width,
		 int param_flags,
		 RGBA alter *result,
		 RGBA alter *_hoops_RPCSP);
GLOBAL_FUNCTION void HD_Activate_Texture_Image(
		Net_Rendition const & nr,
		_hoops_RCR alter *txr,
		unsigned int needed_flags,
		int _hoops_AGIIH, int _hoops_PGIIH,
		int _hoops_HGIIH, int _hoops_IGIIH);
GLOBAL_FUNCTION void HD_Set_Image_Alpha(Image alter *image, unsigned char alpha);
GLOBAL_FUNCTION void HD_Standard_Compute_Texture (Net_Rendition const & nr,
		 _hoops_RCR const *texture,
		 Point const *_hoops_ICAGA,
		 _hoops_ARPA const *plane,
		 float const * params,
		 int param_width,
		 int param_flags,
		 int _hoops_GCI,
		 RGBA alter *_hoops_CGIIH);
GLOBAL_FUNCTION bool HD_Standard_Name_Font(Net_Rendition const & nr, _hoops_IGPIR const *_hoops_RRCSP, _hoops_IGPIR alter *_hoops_ARCSP);
GLOBAL_FUNCTION void HD_Std_3D_Contour (Net_Rendition const & nr, _hoops_PRHIR const *_hoops_CICP);
GLOBAL_FUNCTION void HD_Std_3D_Cylinder (Net_Rendition const & nr, Cylinder const *cylinder);
GLOBAL_FUNCTION void HD_Std_3D_PolyCylinder (Net_Rendition const & nr, PolyCylinder const *polycylinder);
GLOBAL_FUNCTION void HD_Std_3D_Sphere (Net_Rendition const & nr, Sphere const *sphere);
GLOBAL_FUNCTION void HD_Std_3D_Ellipse (Net_Rendition const & nr, Ellipse const *ellipse);
GLOBAL_FUNCTION void HD_Std_3D_Grid (Net_Rendition const & _hoops_SGIIH, Grid const *grid);
GLOBAL_FUNCTION void HD_Std_3D_Image (Net_Rendition const & nr, Image const *image);
GLOBAL_FUNCTION void HD_Std_3D_Light (Net_Rendition const & nr, Light const *light);
GLOBAL_FUNCTION void HD_Std_3D_Marker (Net_Rendition const & nr, Marker const *marker);
GLOBAL_FUNCTION void HD_Std_3D_Multimarker (Net_Rendition const & nr, _hoops_GRPGR const * _hoops_CHPIR);
GLOBAL_FUNCTION void HD_Std_3D_NURBS_Curve (Net_Rendition const & nr, _hoops_PIRGR const *curve);
GLOBAL_FUNCTION void HD_Std_3D_Polyedge (Net_Rendition const & nr, Polyedge const *pe);
GLOBAL_FUNCTION void HD_Std_3D_Polyedge_From_Tristrip (Net_Rendition const & nr, Polyedge const * pe, Tristrip const * ts);
GLOBAL_FUNCTION void HD_Std_3D_Polygon (Net_Rendition const & nr, Polygon const *polygon);
GLOBAL_FUNCTION void HD_Std_3D_Polyhedron (Net_Rendition const & nr, Polyhedron const * _hoops_IPRI);
GLOBAL_FUNCTION void HD_Std_3D_Polyline (Net_Rendition const & nr, Polyline const *pl);
GLOBAL_FUNCTION void HD_Std_3D_Infinite_Line (Net_Rendition const & nr, Polyline const *pl);
GLOBAL_FUNCTION void HD_Std_3D_Polymarker (Net_Rendition const & inr, Polymarker const *pm);
GLOBAL_FUNCTION void HD_Std_3D_Text (Net_Rendition const & inr, _hoops_HACC const *text);
GLOBAL_FUNCTION void HD_Std_3D_Tristrip (Net_Rendition const & nr, Tristrip const *ts);
GLOBAL_FUNCTION void HD_Std_3D_NURBS_Surface (Net_Rendition const & nr, _hoops_APPGR const *surface);
GLOBAL_FUNCTION void HD_Std_DC_Ellipse (Net_Rendition const & nr,
		 DC_Point const *where,
		 DC_Point const *radii);
GLOBAL_FUNCTION void HD_Std_DC_Face (Net_Rendition const & nr, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Std_DC_Image (Net_Rendition const & nr,
		 DC_Point const *start,
		 DC_Point const *end,
		 int hoffset,
		 char format,
		 int row_bytes,
		 void const * const *_hoops_HCHIH,
		 int pattern,
		 Driver_Color const *contrast_color,
		 Image const *db_image);
GLOBAL_FUNCTION void HD_Std_DC_Polydot (Net_Rendition const & nr, int count, DC_Point const *where);
GLOBAL_FUNCTION void HD_Std_DC_Colorized_Polydot (Net_Rendition const & nr, int count, DC_Point const *where, RGBAS32 const *_hoops_HICGR, bool single);
GLOBAL_FUNCTION void HD_Std_DC_Polymarker (
		 Net_Rendition const & nr,
		 int count,
		 DC_Point const *where,
		 float const *rotations,
		 float const *size_fixups);
GLOBAL_FUNCTION void HD_Std_DC_Polygon (Net_Rendition const & nr, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Std_DC_Polyline (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Std_DC_Rectangle (Net_Rendition const & nr, int left, int right, int bottom, int top);
GLOBAL_FUNCTION void HD_Std_DC_Text (Net_Rendition const & _hoops_ACRIP, DC_Point const *position, int count, unsigned short const *kstring);
GLOBAL_FUNCTION void HD_Std_DC_Polytriangle (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Standard_Draw_Inter_Text (Net_Rendition const & nr, Text_Info const *ti);
GLOBAL_FUNCTION void HD_Standard_Draw_Overlay_List (Net_Rendition const & inr);
GLOBAL_FUNCTION void HD_Standard_Draw_Plain_Text (
		 Net_Rendition const & nr,
		 _hoops_HACC const * _hoops_PCHIH,
		 Point const * position,
		 int count,
		 unsigned short const * _hoops_IHSCP,
		 _hoops_PGCSR const * ki);
GLOBAL_FUNCTION void HD_Standard_Draw_Font (Net_Rendition const & nr,
		 Font_Instance const *specific,
		 Point const *where,
		 int count,
		 unsigned short const *string,
		 Vector const *scale);
GLOBAL_FUNCTION void HD_Standard_Draw_Tree (Net_Rendition const & inr, _hoops_CRCP const *_hoops_SRCP, _hoops_HICS const & path);
GLOBAL_FUNCTION void HD_Standard_Draw_Window (Net_Rendition const & nr, Int_Rectangle const *extent);
GLOBAL_FUNCTION void HD_Standard_Draw_Window_Frame (Net_Rendition const & nr,
		 Int_Rectangle const *extent,
		 Int_Rectangle alter *frame,
		 bool calculate_only);
GLOBAL_FUNCTION bool HD_Standard_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter *_hoops_GHRI, int request, void * request_info);
GLOBAL_FUNCTION Geometry const * HD_Standard_Render (Net_Rendition const & nr, Geometry const *geometry,
																unsigned Integer32 mask, bool single);
GLOBAL_FUNCTION Geometry const * HD_Process_Geometry_Reference (Net_Rendition const & nr, _hoops_PHIP const * _hoops_RRA);
GLOBAL_FUNCTION void HD_Standard_Resize_Outer_Window (Display_Context const *_hoops_RIRRH);
GLOBAL_FUNCTION bool HD_Standard_Select (Display_Context alter *dc, Selection_Event alter *_hoops_GPIIR);
GLOBAL_FUNCTION void HD_Standard_UnDraw_Overlay_List (Net_Rendition const & nr);
GLOBAL_FUNCTION bool HD_Standard_Update (Display_Context alter *dc, Activity _hoops_SCISP);
GLOBAL_FUNCTION void HD_Start_Drivers (_hoops_AIGPR *	_hoops_RIGC);
GLOBAL_FUNCTION void HD_Start_Priority_Inclusion (Net_Rendition const & nr, long priority);
GLOBAL_FUNCTION void HD_Std_Create_Frame_Buffer (Net_Rendition const & nr,
		 int width,
		 int height,
		 char format,
		 Image alter * alter *image,
		 void alter * alter *_hoops_PISCP);
GLOBAL_FUNCTION void HD_Std_Destroy_Frame_Buffer (Net_Rendition const & nr, Image alter *image, void alter *_hoops_PISCP);
GLOBAL_FUNCTION void HD_Std_Display_Frame_Buffer (Net_Rendition const & nr,
		 DC_Point const *start,
		 DC_Point const *end,
		 Image const *image,
		 int hoffset,
		 int voffset,
		 void const *_hoops_PISCP);
GLOBAL_FUNCTION void HD_Std_3D_Elliptical_Arc (Net_Rendition const & nr, Elliptical_Arc const *arc);
GLOBAL_FUNCTION void HD_Std_3D_Stenciled_Quad (Net_Rendition const & inr,
		 Point const *points,
		 _hoops_RAARP const *stencil);
GLOBAL_FUNCTION void HD_Std_DC_Colorized_Face (Net_Rendition const & nr,
		 int count,
		 DC_Point const *_hoops_GHPCP,
		 RGBAS32 const *color);

GLOBAL_FUNCTION void HD_Std_DC_Colorized_Polyline (Net_Rendition const & nr,
		 int count,
		 DC_Point const *points,
		 RGBAS32 const *color,
		 bool single);
GLOBAL_FUNCTION void HD_Std_DC_Colorized_Polymarker (Net_Rendition const & nr,
		 int count,
		 DC_Point const *where,
		 RGBAS32 const *color,
		 bool single, float const * rotations,
		 float const *size_fixups);
GLOBAL_FUNCTION void HD_Std_DC_Colorized_Polytris (Net_Rendition const & _hoops_ACRIP,
		 int count,
		 DC_Point const *points,
		 RGBAS32 const *color,
		 bool single);
GLOBAL_FUNCTION void HD_Std_DC_Elliptical_Arc (Net_Rendition const & nr,
		 DC_Point const *center,
		 DC_Point const *radius,
		 float start,
		 float end);
GLOBAL_FUNCTION void HD_Std_DC_Gouraud_Polyline (Net_Rendition const & _hoops_ACRIP,
		 int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Std_DC_Gouraud_Polytris (Net_Rendition const & _hoops_ACRIP,
		 int count,
		 DC_Point const *points,
		 RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Std_DC_Outline_Ellipse (Net_Rendition const & nr,
		 DC_Point const *where,
		 DC_Point const *radii);
GLOBAL_FUNCTION void HD_Std_DC_Phong_Polyline (Net_Rendition const & nr,
		 int count,
		 DC_Point const *points,
		 RGBA const *colors,
		 _hoops_ARPA const *planes);
GLOBAL_FUNCTION void HD_Std_DC_Phong_Polytris (Net_Rendition const & nr,
		 int count,
		 DC_Point const *points,
		 RGBA const *colors,
		 _hoops_ARPA const *planes);
GLOBAL_FUNCTION void HD_Std_DC_Textured_Polyline (Net_Rendition const & nr,
		 int count,
		 DC_Point const *points,
		 RGBA const *colors,
		 _hoops_ARPA const *planes,
		 _hoops_RSSH const *_hoops_CCHA,
		 int param_width,
		 _hoops_SSIC param_flags);
GLOBAL_FUNCTION void HD_Std_DC_Textured_Polytris (Net_Rendition const & nr,
		 int count,
		 DC_Point const *points,
		 RGBA const *colors,
		 _hoops_ARPA const *planes,
		 _hoops_RSSH const *_hoops_CCHA,
		 int param_width,
		 _hoops_SSIC param_flags);
GLOBAL_FUNCTION void HD_Std_DC_Stenciled_Quad (Net_Rendition const & nr,
		 DC_Point const *points,
		 _hoops_RAARP const *stencil);
GLOBAL_FUNCTION void HD_Std_Retitle_Outer_Window (Display_Context const *_hoops_RIRRH);
GLOBAL_FUNCTION int HD_Transform_And_Test_Simple_Sphere (
		Net_Rendition const & nr,
		int count,
		_hoops_CAIS const *_hoops_GRIIH,
		int const *_hoops_ACHS,
		float _hoops_RRIIH,
		float _hoops_ARIIH,
		Test alter *results,
		float alter *_hoops_PRIIH,
		float alter *_hoops_CIHS);
GLOBAL_FUNCTION int HD_Transform_And_Test_Simple_Cuboid (
		Net_Rendition const & nr,
		int count,
		_hoops_SASC const *_hoops_HRIIH,
		float _hoops_RRIIH,
		float _hoops_ARIIH,
		Test alter *results,
		float alter *_hoops_PRIIH,
		float alter *_hoops_CIHS);
GLOBAL_FUNCTION Test HD_Transform_And_Test_Bounding (Net_Rendition const & nr,
		 Bounding const *bounding,
		 _hoops_PACIR const *_hoops_HCSR,
		 Int_Rectangle const *_hoops_ACSR,
		 float _hoops_ARIIH,
		 float *_hoops_IRIIH=null);
GLOBAL_FUNCTION int HD_Transform_And_Test_XYZ_XY (_hoops_HHCR const & _hoops_IHCR,
		 int point_count,
		 Point const *in,
		 float const *_hoops_CCIPA,
		 _hoops_PACIR const *_hoops_GPHH,
		 DC_Point alter *_hoops_PAGR,
		 float alter *ws,
		 unsigned char alter *_hoops_RRCAR);
GLOBAL_FUNCTION int HD_Transform_And_Test_XYZ_XYZ (_hoops_HHCR const & _hoops_IHCR,
		 int point_count,
		 Point const *in,
		 float const *_hoops_CCIPA,
		 _hoops_PACIR const *_hoops_GPHH,
		 DC_Point alter *_hoops_PAGR,
		 float alter *ws,
		 unsigned char alter *_hoops_RRCAR);
GLOBAL_FUNCTION int HD_Transform_And_Test_XYZ_XYZ_W (_hoops_HHCR const & _hoops_IHCR,
		 int point_count,
		 Point const *in,
		 float const *_hoops_CCIPA,
		 _hoops_PACIR const *_hoops_GPHH,
		 DC_Point alter *_hoops_PAGR,
		 float alter *ws,
		 unsigned char alter *_hoops_RRCAR);
GLOBAL_FUNCTION int HD_Transform_And_Test_XYZ_XY_W (_hoops_HHCR const & _hoops_IHCR,
		 int point_count,
		 Point const *in,
		 float const *_hoops_CCIPA,
		 _hoops_PACIR const *_hoops_GPHH,
		 DC_Point alter *_hoops_PAGR,
		 float alter *ws,
		 unsigned char alter *_hoops_RRCAR);
GLOBAL_FUNCTION int HD_Transform_And_Test_XY_XY (_hoops_HHCR const & _hoops_IHCR,
		 int point_count,
		 Point const *in,
		 float const *_hoops_CCIPA,
		 _hoops_PACIR const *_hoops_GPHH,
		 DC_Point alter *_hoops_PAGR,
		 float alter *ws,
		 unsigned char alter *_hoops_RRCAR);
GLOBAL_FUNCTION int HD_Transform_Not_At_All (_hoops_HHCR const & _hoops_IHCR,
		 int point_count,
		 Point const *in,
		 float const *_hoops_CCIPA,
		 _hoops_PACIR const *_hoops_GPHH,
		 DC_Point alter *_hoops_PAGR,
		 float alter *ws,
		 unsigned char alter *_hoops_RRCAR);
GLOBAL_FUNCTION void HD_Undo_Screen (Net_Rendition const & nr, _hoops_HRPA alter *matrix);
GLOBAL_FUNCTION void HD_Unload_All_Fonts (Display_Context alter *dc);
GLOBAL_FUNCTION void HD_Unload_Defined_Font (Display_Context const *dc, Font_Instance alter *instance);
GLOBAL_FUNCTION void HD_Unload_Freetype_Font (Display_Context const *dc, Font_Instance alter *instance);
GLOBAL_FUNCTION void HD_Upwind_Driver_Options (Display_Context alter *dc);
GLOBAL_FUNCTION void HD_Validate_Clip_Half_Planes (_hoops_ASHH *_hoops_CRAIR, bool _hoops_HAGGA = false);
GLOBAL_FUNCTION void HD_Validate_Clipping_Rendition (_hoops_HHCR alter & _hoops_IHCR,
													 _hoops_HSRGA alter & _hoops_CRAIR, _hoops_GPGGA alter & flags);
GLOBAL_FUNCTION void HD_Validate_Clipping_Rendition (_hoops_HHCR alter & _hoops_IHCR,
													 _hoops_HSRGA alter & _hoops_CRAIR);
GLOBAL_FUNCTION void HD_Validate_Object_To_Proj (Net_Rendition const & nr);
GLOBAL_FUNCTION void HD_Validate_Object_To_View (Net_Rendition const & nr);
GLOBAL_FUNCTION void HD_Validate_World_To_Screen (Net_Rendition const & nr);

GLOBAL_FUNCTION float HD_Compute_Generic_Size (
		Net_Rendition const & nr,
		double							value,
		_hoops_GIGRP			_hoops_HHP,
		float							_hoops_HGPAR,
		bool						_hoops_HPIHH,
		bool	alter *				_hoops_IA,
		bool						errors);
GLOBAL_FUNCTION void HD_HL_3D_Polyhedron (
		Net_Rendition const & nr,
		Polyhedron const * _hoops_CRIIH);

GLOBAL_FUNCTION void  HD_Fixup_Attributes (
		Net_Rendition alter & nr,
		_hoops_PIGRA const * lock,
		int flags);

GLOBAL_FUNCTION void HD_Generate_Cut_Geometry (
		Net_Rendition const & 	   nr,
		_hoops_CRCP const *_hoops_SRCP,
		Geometry const *geometry);
GLOBAL_FUNCTION void HD_Process_Cut_Geometry (
		Net_Rendition const & 	   nr,
		_hoops_CRCP const *			_hoops_SRCP,
		_hoops_HICS const & path,
		bool _hoops_HPIGA,
		bool _hoops_SGSGA);
GLOBAL_FUNCTION void HD_Delete_Cut_Geometry_Pieces (
		Display_Context alter *		dc);
GLOBAL_FUNCTION void HD_Shadow_Update (
		Net_Rendition const & nr,
		_hoops_CRCP const * _hoops_SRCP,
		_hoops_HICS const & path);
GLOBAL_FUNCTION void HD_Shadow_Map_Update (
		Net_Rendition const & nr,
		_hoops_CRCP const * _hoops_SRCP,
		_hoops_HICS const & path);
GLOBAL_FUNCTION int HD_Generate_Complete_Points (
		Point const *center,
		Vector const *_hoops_GGHI,
		Vector const *_hoops_RGHI,
		int count,
		bool _hoops_SRIIH,
		Point alter *pl);


GLOBAL_FUNCTION void HD_SZB_DC_Polytriangle (
	Net_Rendition const & 		nr,
	int									count,
	DC_Point const *			points);
GLOBAL_FUNCTION void HD_SZB_DC_Colorized_Polytris (
	Net_Rendition const & 		nr,
	int									count,
	DC_Point const *			points,
	RGBAS32 const *				color,
	bool							single);
GLOBAL_FUNCTION void HD_SZB_DC_Gouraud_Polytris (
	Net_Rendition const & 		nr,
	int									count,
	DC_Point const *			points,
	RGBAS32 const *				colors);
GLOBAL_FUNCTION void HD_SZB_DC_Phong_Polytris (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBA const					*colors,
	_hoops_ARPA const					*planes);
GLOBAL_FUNCTION void HD_SZB_DC_Textured_Polytris (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBA const					*colors,
	_hoops_ARPA const					*planes,
	float const				*params,
	Integer32					param_width,
	Integer32				param_flags);

GLOBAL_FUNCTION void HD_SZB_DC_Polyline (
	Net_Rendition const & 		nr,
	int									count,
	DC_Point const *			points);
GLOBAL_FUNCTION void HD_SZB_DC_Colorized_Polyline (
	Net_Rendition const & 		nr,
	int									count,
	DC_Point const *			points,
	RGBAS32 const *			color,
	bool							single);
GLOBAL_FUNCTION void HD_SZB_DC_Gouraud_Polyline (
	Net_Rendition const & 		nr,
	int									count,
	DC_Point const *			points,
	RGBAS32 const *			colors);

GLOBAL_FUNCTION void HD_SZB_DC_Rectangle (
	Net_Rendition const & 		nr,
	int left, int right, int bottom, int top);

GLOBAL_FUNCTION void HD_SZB_Process_Triangle (
	Net_Rendition const & nr);
GLOBAL_FUNCTION void HD_SZB_Process_Line (
	Net_Rendition const & nr);
GLOBAL_FUNCTION void HD_SZB_Process_Rectangle (
	Net_Rendition const & nr);

GLOBAL_FUNCTION void HD_Compute_Polyhedron_LOD (
	Net_Rendition const & nr,
	Polyhedron *phon,
	int _hoops_GAIIH);




GLOBAL_FUNCTION _hoops_PGSGP * HD_Generate_Octree (
	Net_Rendition const &	nr,
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_HICS const &	path);
GLOBAL_FUNCTION void HD_Delete_Octree (
	_hoops_AIGPR *	_hoops_RIGC,
	Net_Rendition const &	nr,
	_hoops_PGSGP *			node);
GLOBAL_FUNCTION void HD_Send_Queries (
	Net_Rendition const &	nr,
	_hoops_PGSGP *			root);
GLOBAL_FUNCTION void HD_Process_Queries (
	Net_Rendition const &	nr,
	_hoops_PGSGP *			root);

GLOBAL_FUNCTION void  HD_Find_Local_Cutting_Planes (
	Net_Rendition alter & nr, _hoops_CRCP const *_hoops_SRCP);

GLOBAL_FUNCTION void HD_Select_Sphere_Polyhedron (
	Net_Rendition const & nr,  Sphere const *sphere);

GLOBAL_FUNCTION void HD_Vanillify_Actions (
	_hoops_PRGIP _hoops_RCSHR,
	_hoops_APARR alter & _hoops_ACPGR);

GLOBAL_FUNCTION void HD_Free_HL_Data (_hoops_SGSGP alter *data);

GLOBAL_FUNCTION void HD_Unwrap_Polytriangle (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Unwrap_Colorized_Polytriangle (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points, RGBAS32 const *color, bool single);
GLOBAL_FUNCTION void HD_Unwrap_Gouraud_Polytriangle (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points, RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Unwrap_Reshaded_Polytriangle (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points,
		 RGBA const * colors, _hoops_ARPA const * planes,
		 _hoops_RSSH const *_hoops_CCHA, int param_width, _hoops_SSIC alter param_flags);
GLOBAL_FUNCTION void HD_Unwrap_Polyline (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Unwrap_Colorized_Polyline (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points, RGBAS32 const *color, bool single);
GLOBAL_FUNCTION void HD_Unwrap_Gouraud_Polyline (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points, RGBAS32 const *colors);
GLOBAL_FUNCTION void HD_Unwrap_Reshaded_Polyline (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points,
		 RGBA const * colors, _hoops_ARPA const * planes,
		 _hoops_RSSH const *_hoops_CCHA, int param_width, _hoops_SSIC alter param_flags);
GLOBAL_FUNCTION void HD_Unwrap_Polymarker (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points, float const * rotations, float const *size_fixups);
GLOBAL_FUNCTION void HD_Unwrap_Colorized_Polymarker (Net_Rendition const & _hoops_ACRIP, int count, DC_Point const *points, RGBAS32 const *color, bool single, float const * rotations, float const *size_fixups);
GLOBAL_FUNCTION void HD_Compute_Shadow_Resolution (Net_Rendition const & inr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path);
GLOBAL_FUNCTION void HD_Reposition_Shadow (Net_Rendition const & inr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path);
GLOBAL_FUNCTION void HD_Flush_Hidden_Item_Cache (Display_Context alter *dc);
GLOBAL_FUNCTION void HD_Free_Hidden_Item_Cache (Display_Context alter *dc);
GLOBAL_FUNCTION void HD_Clean_Texture_Image_Cache (Net_Rendition const & inr, _hoops_RCR const *txr);
GLOBAL_FUNCTION void HD_Hide_3D_Tristrip(
		Net_Rendition const & nr,
		Net_Rendition const & _hoops_PARHH,
		Tristrip const *ts,
		int flags,
		DC_Point* _hoops_GHPCP);
GLOBAL_FUNCTION void HD_Hide_3D_Polymarker (
	Net_Rendition const & 		inr,
	Polymarker const *			pm,
	int							flags,
	DC_Point *					_hoops_GHPCP) ;

GLOBAL_FUNCTION void HD_Cache_From_Hidden_Tristrip (Hidden_Tristrip alter *_hoops_RAIIH, float _hoops_GCSIP);
GLOBAL_FUNCTION void HD_Free_Hidden_Tristrip (Hidden_Tristrip alter *_hoops_RAIIH);
GLOBAL_FUNCTION void HD_Free_Hidden_Polymarker (_hoops_PGRCP alter * _hoops_AAIIH);
GLOBAL_FUNCTION void HD_Alternate_Hidden_Root (Display_Context alter * dc, int mode);
GLOBAL_FUNCTION void HD_Flush_Octree_Queries (Net_Rendition const & nr, _hoops_CRCP const * _hoops_SRCP);
GLOBAL_FUNCTION _hoops_IAPA alter * HD_Copy_Cutting_Plane_Sets (_hoops_IAPA const *_hoops_AGCPH);
GLOBAL_FUNCTION void HD_Free_Cutting_Plane_Sets (_hoops_IAPA const *_hoops_HRCAR);
GLOBAL_FUNCTION void HD_Validate_Cutting_Plane_Sets (_hoops_SSP const & _hoops_GGH);
GLOBAL_FUNCTION void HD_Validate_Transparent_Cutting_Sets (_hoops_SSP const & _hoops_GGH);
GLOBAL_FUNCTION void* HD_Find_X11_Display(char const * const name);
GLOBAL_FUNCTION void HD_Free_X11_Display(void const * display);
GLOBAL_FUNCTION void HD_Validate_Elliptical_Arc (
		_hoops_GHHI const *curve,
		Elliptical_Arc alter *arc,
		float *_hoops_CSIH);
GLOBAL_FUNCTION void HD_DC_Generate_Elliptical_Bezier (
		Net_Rendition const & nr,
		DC_Point const *center,
		DC_Point const *_hoops_GGHI,
		DC_Point const *_hoops_RGHI,
		float start,
		float end,
		int *count,
		DC_Point *buffer);
GLOBAL_FUNCTION void HD_Generate_Elliptical_Bezier (
		Net_Rendition const	& nr,
		_hoops_GHHI const *curve,
		int *count,
		DC_Point *buffer);

GLOBAL_FUNCTION void HD_Std_Depth_Peeling (Display_Context alter * dc);
GLOBAL_FUNCTION void HD_Draw_Deferred_3D_Geometry (_hoops_PGCIP alter * list, bool _hoops_IGCIP);
GLOBAL_FUNCTION void HD_Free_Deferred_3D_Geometry (_hoops_PGCIP alter * list);
GLOBAL_FUNCTION void HD_Isolate_Tristrip_Data (Display_Context const * dc, Tristrip const * ts);
GLOBAL_FUNCTION void HD_Isolate_Polyedge_Data (Display_Context const * dc, Polyedge const * pe);
GLOBAL_FUNCTION void HD_Isolate_Polymarker_Data (Display_Context const * dc, Polymarker const * pm);

GLOBAL_FUNCTION void HD_Select_DC_Polyline (Net_Rendition const & nr, int count, DC_Point const *points);
GLOBAL_FUNCTION void HD_Select_DC_Polytriangle (Net_Rendition const & nr, int count, DC_Point const *points);


GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Polyline (Net_Rendition const & nr, Polyline const *polyline);
GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Polymarker (Net_Rendition const & nr, Polymarker const *pm);
GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Marker (Net_Rendition const & nr, Marker const *marker);
GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Tristrip (Net_Rendition const & nr, Tristrip const *tristrip);
GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Ellipse (Net_Rendition const & nr, Ellipse const *ellipse);
GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Polygon (Net_Rendition const & nr, Polygon const *polygon);
GLOBAL_FUNCTION void HD_Defer_Peeled_Trans_3D_Polyedge (Net_Rendition const & nr, Polyedge const *polyedge);

GLOBAL_FUNCTION void HD_Defer_Antialiased_3D_Polyline (Net_Rendition const & nr, Polyline const *polyline);
GLOBAL_FUNCTION void HD_Defer_Antialiased_3D_Polygon (Net_Rendition const & nr, Polygon const *polygon);
GLOBAL_FUNCTION void HD_Defer_Antialiased_3D_Polyedge (Net_Rendition const & nr, Polyedge const *polyedge);


GLOBAL_FUNCTION unsigned short HD_Map_Freetype_Char_Index(
	Font_Instance const	*specific,
	unsigned short			_hoops_IPCSR);

GLOBAL_FUNCTION _hoops_RAARP * HD_Make_Freetype_Stencil(
	Net_Rendition const & nr,
	Font_Instance const	*specific,
	unsigned short			_hoops_SRCSP,
	int						bitmap_height,
	int						bolding_level,
	float					xrslant,
	float					xrrotation,
	float					xrwidth_scale,
	bool					antialias);


GLOBAL_FUNCTION unsigned short HD_Standard_Map_Char_Index(
	Font_Instance const	*specific,
	unsigned short	_hoops_IPCSR);

GLOBAL_FUNCTION void HD_Draw_Stenciled_Font (
	Net_Rendition const & nr,
	Font_Instance const	*specific,
	Point const *		where,
	int						count,
	unsigned short const *	string,
	Vector const *		scale);

GLOBAL_FUNCTION void HD_Draw_Dead_Font (
	Net_Rendition const & nr,
	Font_Instance const	*specific,
	Point const *		where,
	int						count,
	unsigned short const *	string,
	Vector const *		scale);

GLOBAL_FUNCTION void HD_Standard_Size_Font(Net_Rendition const & nr, Font_Instance alter *specific);
GLOBAL_FUNCTION bool HD_Standard_Will_Use_Stencil(Net_Rendition const & nr, Font_Instance const *specific);
GLOBAL_FUNCTION bool HD_Freetype_Will_Use_Stencil(Net_Rendition const & nr, Font_Instance const *specific);

GLOBAL_FUNCTION void HD_Search_Null_Clip_Tree (Net_Rendition const & nr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path, Integer32 _hoops_CAHIP, bool _hoops_SAHIP);
GLOBAL_FUNCTION void HD_Reset_Tree_State (Net_Rendition alter & nr);

GLOBAL_FUNCTION Geometry const * HD_Ordered_Render (Net_Rendition const & nr, Geometry const *geometry, unsigned Integer32 mask, bool single);
GLOBAL_FUNCTION void HD_Ordered_Segment (Net_Rendition const & nr, _hoops_CRCP const * _hoops_SRCP);
GLOBAL_FUNCTION void HD_Defer_Ordered (Net_Rendition const & nr, bool _hoops_PPHPP = false);

GLOBAL_FUNCTION void HD_Handle_FBI_Pending_Window (Net_Rendition const & nr);

GLOBAL_FUNCTION void HD_Adjust_WLimit (Net_Rendition alter & nr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path);

GLOBAL_FUNCTION int alter * HD_Get_Screen_Facings (Net_Rendition const & nr, Tristrip const *ts, int face_count);

GLOBAL_FUNCTION void HD_Prepare_Geometry_Transparency (Net_Rendition alter & nr, char const * _hoops_PAIIH);


GLOBAL_FUNCTION unsigned int HD_Type_To_Action_Mask (int type);
GLOBAL_FUNCTION unsigned int HD_Geometry_To_Action_Mask (Geometry const *g);

GLOBAL_FUNCTION RGB HD_Apply_Color_Effects (RGB const & _hoops_SHGCR, _hoops_AHAH const & _hoops_CSPHP);

/* _hoops_IH _hoops_PGHGR _hoops_GGAS */
GLOBAL_FUNCTION void HD_Free_Convex_Clip_Region (_hoops_ASHH const *victim);
GLOBAL_FUNCTION _hoops_ASHH * HD_New_Convex_Clip_Region(Net_Rendition const & nr, int count, DC_Point const *points);

GLOBAL_FUNCTION void HD_Add_Cutting_Plane (Net_Rendition alter & nr, _hoops_ARPA const *plane);
GLOBAL_FUNCTION void HD_Remove_Cutting_Planes(Net_Rendition alter & nr);

GLOBAL_FUNCTION void HD_Draw_Window(Net_Rendition const & nr, Int_Rectangle const *extent);

GLOBAL_FUNCTION void HD_Free_User_Face_Pattern(_hoops_SIHHP const *up);

GLOBAL_FUNCTION void HD_Figure_Driver_Color (Net_Rendition const & nr, RGB const * _hoops_HICGR, Driver_Color * _hoops_CGIIH);

GLOBAL_FUNCTION float HD_Compute_Character_Width(Net_Rendition const & nr, Text_Info alter *ti, int index);

GLOBAL_FUNCTION Point const * HD_Compute_Character_Position(
	Net_Rendition const & nr, Text_Info alter *ti, int index);

GLOBAL_FUNCTION Point const * HD_Compute_Transformed_Text_Position(
	Net_Rendition const & nr, Text_Info alter *ti, Point const * point);

GLOBAL_FUNCTION void HD_Markers_To_Polymarker (Net_Rendition const & inr,  int count, Point * points);



GLOBAL_FUNCTION Driver_Action HD_AIX_Load_Dynamic_Driver (char const *_hoops_HSS);
GLOBAL_FUNCTION void HD_AIX_UnLoad_Dynamic_Driver (Driver_Action _hoops_GHRPR);

GLOBAL_FUNCTION Driver_Action HD_HPUX_Load_Dynamic_Driver (char const *_hoops_HSS);
GLOBAL_FUNCTION void HD_HPUX_UnLoad_Dynamic_Driver (Driver_Action _hoops_GHRPR);

GLOBAL_FUNCTION Driver_Action HD_IRIX_Load_Dynamic_Driver (char const *_hoops_HSS);
GLOBAL_FUNCTION void HD_IRIX_UnLoad_Dynamic_Driver (Driver_Action _hoops_GHRPR);

GLOBAL_FUNCTION Driver_Action HD_Linux_Load_Dynamic_Driver (char const *_hoops_HSS);
GLOBAL_FUNCTION void HD_Linux_UnLoad_Dynamic_Driver (Driver_Action _hoops_GHRPR);

GLOBAL_FUNCTION Driver_Action HD_OSX_Load_Dynamic_Driver (char const *_hoops_HSS);
GLOBAL_FUNCTION void HD_OSX_UnLoad_Dynamic_Driver (Driver_Action _hoops_GHRPR);

GLOBAL_FUNCTION Driver_Action HD_Sun_Load_Dynamic_Driver (char const *_hoops_HSS);
GLOBAL_FUNCTION void HD_Sun_UnLoad_Dynamic_Driver (Driver_Action _hoops_GHRPR);

GLOBAL_FUNCTION void HD_W32_UnLoad_Dynamic_Driver (Driver_Action _hoops_GHRPR);
GLOBAL_FUNCTION Driver_Action HD_Win32_Load_Dynamic_Driver (char const *_hoops_HSS);


GLOBAL_FUNCTION void HD_Purge_Display_Lists(_hoops_GGAGR const * _hoops_GHRI, _hoops_RRPHP _hoops_ARPHP, void *_hoops_HHCAP);
GLOBAL_FUNCTION void HD_Queue_Destroy_List (_hoops_AGCI alter *_hoops_AGAGR, bool _hoops_CGPHP);

GLOBAL_FUNCTION void HD_Process_Deferred_Octrees(Display_Context alter * dc);

GLOBAL_FUNCTION void HD_Clean_DC_Breadcrumbs (Display_Context alter * dc);

GLOBAL_FUNCTION void * HD_Show_User_Index (Net_Rendition const &nr, int index);
GLOBAL_FUNCTION void HD_Merge_User_Indices(_hoops_CIGIP const &_hoops_SIGIP);

GLOBAL_FUNCTION float HD_Compute_Displacement_Scale (Net_Rendition const &nr, float _hoops_HAIIH);


GLOBAL_FUNCTION Net_Rendition HD_New_Local_Edge_Rendition (
	Polyhedron	 alter *			_hoops_IPRI,
	Net_Rendition const & 			_hoops_SGIIH,
	Net_Rendition const & 			_hoops_IAIIH,
	_hoops_IAHPR const *		_hoops_HPHCR);
GLOBAL_FUNCTION  void HD_Replace_Line_Style(Line_Rendition alter & _hoops_HC, Line_Style const & _hoops_CAIIH, bool _hoops_SAIIH = true);

GLOBAL_FUNCTION void HD_Setup_Line_Marker_Xform (
	Net_Rendition const &		inr,
	Polyline const *			pl,
	DC_Point alter *			_hoops_GHPCP,
	Marker const *				_hoops_GPIIH,
	_hoops_HRPA alter *			matrix
);
GLOBAL_FUNCTION void HD_Takedown_Line_Marker_Xform (Net_Rendition const & inr);

GLOBAL_FUNCTION void HD_Update_Log(Display_Context const * dc, const char * message, const char* file, int line);

GLOBAL_FUNCTION void HD_Tint_Driver_Color (Net_Rendition const & nr, Driver_Color alter * _hoops_CPHHP);

GLOBAL_FUNCTION _hoops_GPAIR HD_Find_Named_Style (
	_hoops_RIGIP const &	_hoops_AIGIP,
	const char *					_hoops_HSIHH,
	_hoops_HCRPR const *					_hoops_PACSR,
	Integer32						key,
	bool							error);

GLOBAL_FUNCTION void HD_Patch_Rendition (
	Net_Rendition alter &		nr,
	Net_Rendition const &		_hoops_ACRIP,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_PSPGP alter &		_hoops_PCGPR);


#define HD_PROTO_DEFINED 1
#endif /* _hoops_RPIIH */


