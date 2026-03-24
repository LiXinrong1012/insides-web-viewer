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
 * $Id: obf_tmp.txt 1.193 2010-12-10 03:32:35 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "phdraw.h"
#include "phedron.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


/* (_hoops_GSCHH _hoops_HRGR _hoops_GGHSA _hoops_HIS _hoops_RSCHH _hoops_PAH _hoops_PAIHR & _hoops_ISPR _hoops_IH _hoops_SCH) */
GLOBAL_FUNCTION bool HD_No_Such_Keyboard (
	Display_Context const *		dc,
	int alter *					button,
	int alter *					status) {
	UNREFERENCED (button);
	UNREFERENCED (status);

	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					   Sprintf_P (null,
				"No keyboard device action routine driver on '%p'",
						  dc->_hoops_AAHSR));
	return false;
}


/* (_hoops_ASCHH _hoops_HRGR _hoops_GGHSA _hoops_HIS _hoops_RSCHH _hoops_PAH _hoops_PAIHR & _hoops_ISPR _hoops_IH _hoops_SCH) */
GLOBAL_FUNCTION bool HD_No_Such_Locater (
	Display_Context const *		dc,
	int alter *					button,
	int alter *					x,
	int alter *					y) {
	UNREFERENCED (button);
	UNREFERENCED (x);
	UNREFERENCED (y);

	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					   Sprintf_P (null,
				"No locater device action routine driver on '%p'",
						  dc->_hoops_AAHSR));
	return false;
}


local void _hoops_AHPGR (
	Display_Context const *		dc,
	char const *				which) {
	UNREFERENCED (dc);

	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					   Sprintf_SP (null,
				"Missing but essential '%s' action routine on '%p'", which,
						  dc->_hoops_AAHSR));
}


local void _hoops_PSCHH (
	Display_Context alter *		dc) {
	UNREFERENCED (dc);
}


local void get_physical_info (
	Display_Context alter *		dc) {
	_hoops_AHPGR (dc, "get_physical_info");
	dc->_hoops_ACPGR->get_physical_info = _hoops_PSCHH;
}


local bool _hoops_HSCHH (
	Display_Context alter *		dc) {
	UNREFERENCED (dc);

	return false;
}


local bool start_device (
	Display_Context alter *		dc) {
	_hoops_AHPGR (dc, "start_device");
	dc->_hoops_ACPGR->start_device = _hoops_HSCHH;
	return false;
}


local void _hoops_ISCHH (
	Display_Context alter *		dc) {
	UNREFERENCED (dc);
}


local void stop_device (
	Display_Context alter *		dc) {
	_hoops_AHPGR (dc, "stop_device");
	dc->_hoops_ACPGR->stop_device = _hoops_ISCHH;
}


local void _hoops_CSCHH (
	Net_Rendition const &		nr,
	int							left,
	int							right,
	int							bottom,
	int							top) {
	UNREFERENCED (nr);
	UNREFERENCED (left);
	UNREFERENCED (right);
	UNREFERENCED (bottom);
	UNREFERENCED (top);
}


local void _hoops_CAAGR (
	Net_Rendition const &		nr,
	int							left,
	int							right,
	int							bottom,
	int							top) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

	UNREFERENCED (left);
	UNREFERENCED (right);
	UNREFERENCED (bottom);
	UNREFERENCED (top);

	_hoops_AHPGR (nr->_hoops_SRA, "clear_z_buffer");
	dc->_hoops_ACPGR->_hoops_CAAGR = _hoops_CSCHH;
}


local POINTER_SIZED_INT _hoops_SSCHH (
	Display_Context const *		dc) {
	UNREFERENCED (dc);

	return 0;
}


local POINTER_SIZED_INT get_outer_window (
	Display_Context const *		dc) {
	_hoops_AHPGR (dc, "get_outer_window");
	((Display_Context alter *)dc)->_hoops_ACPGR->get_outer_window =
												_hoops_SSCHH;
	return 0;
}




local void _hoops_GGSHH (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	unsigned char const *		rasters) {
	UNREFERENCED (nr);
	UNREFERENCED (start);
	UNREFERENCED (end);
	UNREFERENCED (row_bytes);
	UNREFERENCED (rasters);
}


local void _hoops_CCCGA (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	unsigned char const *		rasters) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

	UNREFERENCED (start);
	UNREFERENCED (end);
	UNREFERENCED (row_bytes);
	UNREFERENCED (rasters);

	_hoops_AHPGR (nr->_hoops_SRA, "draw_dc_bit_rasters");
	dc->_hoops_ACPGR->_hoops_CCCGA = _hoops_GGSHH;
}


local void _hoops_RGSHH (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	unsigned char const *		rasters) {
	UNREFERENCED (nr);
	UNREFERENCED (start);
	UNREFERENCED (end);
	UNREFERENCED (row_bytes);
	UNREFERENCED (rasters);
}


local void _hoops_GSCGA (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	unsigned char const *		rasters) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

	UNREFERENCED (start);
	UNREFERENCED (end);
	UNREFERENCED (row_bytes);
	UNREFERENCED (rasters);

	_hoops_AHPGR (nr->_hoops_SRA, "draw_dc_gray8_rasters");
	dc->_hoops_ACPGR->_hoops_GSCGA = _hoops_RGSHH;
}


local void _hoops_AGSHH (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	unsigned char const *		rasters) {
	UNREFERENCED (nr);
	UNREFERENCED (start);
	UNREFERENCED (end);
	UNREFERENCED (row_bytes);
	UNREFERENCED (rasters);
}


local void _hoops_CCCSR (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	unsigned char const *		rasters) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

	UNREFERENCED (start);
	UNREFERENCED (end);
	UNREFERENCED (row_bytes);
	UNREFERENCED (rasters);

	_hoops_AHPGR (nr->_hoops_SRA, "draw_dc_mapped8_rasters");
	dc->_hoops_ACPGR->_hoops_CCCSR = _hoops_AGSHH;
}


local void _hoops_PGSHH (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	unsigned short const *		rasters) {
	UNREFERENCED (nr);
	UNREFERENCED (start);
	UNREFERENCED (end);
	UNREFERENCED (row_bytes);
	UNREFERENCED (rasters);
}


local void _hoops_PSCGA (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	unsigned short const *		rasters) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

	UNREFERENCED (start);
	UNREFERENCED (end);
	UNREFERENCED (row_bytes);
	UNREFERENCED (rasters);

	_hoops_AHPGR (nr->_hoops_SRA, "draw_dc_mapped16_rasters");
	dc->_hoops_ACPGR->_hoops_PSCGA = _hoops_PGSHH;
}


local void _hoops_HGSHH (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	RGBAS32 const *				rasters) {
	UNREFERENCED (nr);
	UNREFERENCED (start);
	UNREFERENCED (end);
	UNREFERENCED (row_bytes);
	UNREFERENCED (rasters);
}


local void draw_dc_rgb32_rasters (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	RGBAS32 const *				rasters) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

	UNREFERENCED (start);
	UNREFERENCED (end);
	UNREFERENCED (row_bytes);
	UNREFERENCED (rasters);

	_hoops_AHPGR (nr->_hoops_SRA, "draw_dc_rgb32_rasters");
	dc->_hoops_ACPGR->draw_dc_rgb32_rasters = _hoops_HGSHH;
}


local void _hoops_IGSHH (
	Display_Context const *		dc,
	unsigned int				r,
	unsigned int				g,
	unsigned int				b,
	int							index) {
	UNREFERENCED (dc);
	UNREFERENCED (r);
	UNREFERENCED (g);
	UNREFERENCED (b);
	UNREFERENCED (index);
}


local void _hoops_SCCSR (
	Display_Context const *		dc,
	unsigned int				r,
	unsigned int				g,
	unsigned int				b,
	int							index) {
	UNREFERENCED (r);
	UNREFERENCED (g);
	UNREFERENCED (b);
	UNREFERENCED (index);

	_hoops_AHPGR (dc, "set_device_color_map");
	((Display_Context alter *)dc)->_hoops_ACPGR->_hoops_SCCSR =
		_hoops_IGSHH;
}



local void init_picture (
	Net_Rendition const &		nr) {
	UNREFERENCED (nr);
}


local void finish_picture (
	Net_Rendition const &		nr,
	bool						_hoops_CGSHH) {
	UNREFERENCED (nr);
	UNREFERENCED (_hoops_CGSHH);
}


local void init_update (
	Display_Context const *		dc) {
	UNREFERENCED (dc);
}


local void finish_update (
	Display_Context const *		dc) {
	UNREFERENCED (dc);
}


local void free_outer_window (
	Display_Context const *		dc) {
	UNREFERENCED (dc);
}


local void get_current_info (
	Display_Context alter *		dc) {
	UNREFERENCED (dc);
}


local void _hoops_CACSR (
	Display_Context alter *		dc) {
	UNREFERENCED (dc);
}

local void find_all_fonts (
	Display_Context alter *		dc) {
	UNREFERENCED (dc);
}

local bool _hoops_AACSR (
	Display_Context alter *		dc,
	char const *				name) {
	UNREFERENCED (dc);
	UNREFERENCED (name);
	return false;
}


local void * _hoops_SGSHH (
	Display_Context const *		dc,
	char const *				name,
	Font_Instance alter *		instance) {
	UNREFERENCED (dc);
	UNREFERENCED (name);
	UNREFERENCED (instance);

	return 0;
}


local void * load_font (
	Display_Context const *		dc,
	char const *				name,
	Font_Instance alter *		instance) {
	UNREFERENCED (dc);
	UNREFERENCED (name);
	UNREFERENCED (instance);

	_hoops_AHPGR (dc, "load_font");
	((Display_Context alter *)dc)->_hoops_ACPGR->load_font = _hoops_SGSHH;
	return 0;
}


local bool  _hoops_GRSHH (
	Net_Rendition const &		nr,
	Font_Instance const *		instance,
	Karacter					_hoops_IPCSR,
	float alter *				_hoops_GGGS,
	bool alter *				_hoops_CPCSR,
	void **						_hoops_SPCSR) {
	UNREFERENCED (nr);
	UNREFERENCED (instance);
	UNREFERENCED (_hoops_IPCSR);
	*_hoops_GGGS = 0.0f;
	*_hoops_CPCSR = true;
	UNREFERENCED (_hoops_SPCSR);

	return true;
}

local bool measure_char (
	Net_Rendition const &		nr,
	Font_Instance const *		instance,
	Karacter					_hoops_IPCSR,
	float alter *				_hoops_GGGS,
	bool alter *				_hoops_CPCSR,
	void **						_hoops_SPCSR) {
	UNREFERENCED (instance);
	UNREFERENCED (_hoops_IPCSR);
	*_hoops_GGGS = 0.0f;
	*_hoops_CPCSR = true;
	UNREFERENCED (_hoops_SPCSR);

	_hoops_AHPGR (nr->_hoops_SRA, "measure_char");
	((Display_Context alter *)nr->_hoops_SRA)->_hoops_ACPGR->measure_char = _hoops_GRSHH;
	return true;
}

local void unload_font (
	Display_Context const *		dc,
	Font_Instance alter *		instance) {
	UNREFERENCED (dc);
	UNREFERENCED (instance);
}


local void _hoops_RRSHH (
	Net_Rendition const &		nr,
	_hoops_GHISP const &		_hoops_RHISP,
	_hoops_AHISP const *				span,
	int							_hoops_PHISP,
	int							bottom) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR &&
		dc->_hoops_PGCC._hoops_AAPSR <= 256)
		dc->_hoops_IPCI->_hoops_CICGA = HD_Rasterize_DC_Spans_C08_U;
	else
		dc->_hoops_IPCI->_hoops_CICGA = HD_Rasterize_DC_Spans_C24_U;

	_hoops_HRCGH (nr, _hoops_RHISP, span, _hoops_PHISP, bottom);
}



local void * _hoops_IGHGR(
	Net_Rendition const &		nr,
	long						request,
	void alter *				pointer,
	POINTER_SIZED_INT			_hoops_ISPI,
	POINTER_SIZED_INT			_hoops_CSPI,
	POINTER_SIZED_INT			_hoops_SSPI,
	POINTER_SIZED_INT			_hoops_SGHI,
	float 						f1,
	float 						f2,
	float 						_hoops_CGHGR,
	float 						_hoops_SGHGR) {
	UNREFERENCED(nr); 
	UNREFERENCED(request); 
	UNREFERENCED(pointer); 
	UNREFERENCED(_hoops_ISPI); 
	UNREFERENCED(_hoops_CSPI); 
	UNREFERENCED(_hoops_SSPI); 
	UNREFERENCED(_hoops_SGHI); 
	UNREFERENCED(f1); 
	UNREFERENCED(f2); 
	UNREFERENCED(_hoops_CGHGR); 
	UNREFERENCED(_hoops_SGHGR); 

	return 0;
}


GLOBAL_FUNCTION void HD_Get_Actions (
	_hoops_APARR alter &		_hoops_RRCI,
	void						(*_hoops_ARSHH) (_hoops_APARR alter & _hoops_RRCI)) {

	_hoops_RRCI->id = "driver";
	_hoops_RRCI->mask = _hoops_RAPI;

	_hoops_RRCI->start_device			= start_device;
	_hoops_RRCI->stop_device				= stop_device;
	_hoops_RRCI->get_physical_info		= get_physical_info;
	_hoops_RRCI->get_current_info		= get_current_info;

	_hoops_RRCI->update					= HD_Standard_Update;
	_hoops_RRCI->_hoops_SCCSP				= HD_Standard_Draw_Tree;
	_hoops_RRCI->_hoops_CHCI					= HD_Standard_Render;
	_hoops_RRCI->_hoops_GSCSP					= HD_Standard_Select;

	_hoops_RRCI->init_update				= init_update;
	_hoops_RRCI->finish_update			= finish_update;
	_hoops_RRCI->init_picture			= init_picture;
	_hoops_RRCI->finish_picture			= finish_picture;

	_hoops_RRCI->get_outer_window		= get_outer_window;
	_hoops_RRCI->free_outer_window		= free_outer_window;
	_hoops_RRCI->_hoops_RSCSP		= HD_Standard_Resize_Outer_Window;
	_hoops_RRCI->_hoops_ASCSP	= HD_Std_Retitle_Outer_Window;


	_hoops_RRCI->draw_3d_ellipse			= HD_Std_3D_Ellipse;
	_hoops_RRCI->draw_3d_elliptical_arc	= HD_Std_3D_Elliptical_Arc;
	_hoops_RRCI->draw_3d_grid			= HD_Std_3D_Grid;
	_hoops_RRCI->draw_3d_marker			= HD_Std_3D_Marker;
	_hoops_RRCI->_hoops_RIICP		= HD_Std_3D_Multimarker;
	_hoops_RRCI->draw_3d_polyline		= HD_Std_3D_Polyline;
	_hoops_RRCI->draw_3d_infinite_line   = HD_Std_3D_Infinite_Line;
	_hoops_RRCI->draw_3d_nurbs_curve		= HD_Std_3D_NURBS_Curve;
	_hoops_RRCI->draw_3d_nurbs_surface	= HD_Std_3D_NURBS_Surface;
	_hoops_RRCI->draw_3d_cylinder		= HD_Std_3D_Cylinder;
	_hoops_RRCI->draw_3d_polycylinder	= HD_Std_3D_PolyCylinder;
	_hoops_RRCI->draw_3d_sphere			= HD_Std_3D_Sphere;
	_hoops_RRCI->draw_3d_polygon			= HD_Std_3D_Polygon;
	_hoops_RRCI->_hoops_SHCHP			= HD_Std_3D_Contour;
	_hoops_RRCI->draw_3d_image			= HD_Std_3D_Image;
	_hoops_RRCI->draw_3d_polyhedron		= HD_Std_3D_Polyhedron;
	_hoops_RRCI->draw_3d_text			= HD_Std_3D_Text;
	_hoops_RRCI->_hoops_HRCGA			= HD_Std_3D_Light;
	_hoops_RRCI->_hoops_CRCGA	= HD_Std_3D_Stenciled_Quad;
	_hoops_RRCI->draw_3d_polyedge		= HD_Std_3D_Polyedge;
	_hoops_RRCI->draw_3d_tristrip		= HD_Std_3D_Tristrip;
	_hoops_RRCI->draw_3d_polymarker		= HD_Std_3D_Polymarker;
	_hoops_RRCI->draw_3d_polyedge_from_tristrip = nullroutine;
	_hoops_RRCI->_hoops_PPAS	= HD_Draw_Indexicated_3D_Polyedge;
	_hoops_RRCI->_hoops_ARCI	= HD_Draw_Indexicated_3D_Tristrip;
	_hoops_RRCI->draw_silhouette_polyedge= HD_Draw_Silhouette_Edges;
	_hoops_RRCI->_hoops_PSCSP= HD_Draw_NonCulled_Edges;

	_hoops_RRCI->draw_window				= HD_Standard_Draw_Window;
	_hoops_RRCI->draw_window_frame		= HD_Standard_Draw_Window_Frame;

	_hoops_RRCI->draw_dc_ellipse			= HD_Std_DC_Ellipse;
	_hoops_RRCI->_hoops_SCISR = HD_Std_DC_Outline_Ellipse;
	_hoops_RRCI->_hoops_CCISR	= HD_Std_DC_Elliptical_Arc;

	_hoops_RRCI->draw_dc_face			= HD_Std_DC_Face;
	_hoops_RRCI->draw_dc_colorized_face	= HD_Std_DC_Colorized_Face;

	_hoops_RRCI->_hoops_RPCGA			= HD_Std_DC_Polygon;

	_hoops_RRCI->draw_dc_rectangle		= HD_Std_DC_Rectangle;

	_hoops_RRCI->_hoops_HPCGA			= HD_Std_DC_Image;

	_hoops_RRCI->draw_dc_text			= HD_Std_DC_Text;

	_hoops_RRCI->_hoops_SPCGA	= HD_Std_DC_Stenciled_Quad;

	_hoops_RRCI->draw_dc_polytriangle	   = HD_Std_DC_Polytriangle;
	_hoops_RRCI->draw_dc_colorized_polytriangle = HD_Std_DC_Colorized_Polytris;
	_hoops_RRCI->draw_dc_gouraud_polytriangle   = HD_Std_DC_Gouraud_Polytris;
	_hoops_RRCI->draw_dc_phong_polytriangle	= HD_Std_DC_Phong_Polytris;
	_hoops_RRCI->draw_dc_textured_polytriangle  = HD_Std_DC_Textured_Polytris;

	_hoops_RRCI->draw_dc_polyline		   = HD_Std_DC_Polyline;
	_hoops_RRCI->draw_dc_colorized_polyline = HD_Std_DC_Colorized_Polyline;
	_hoops_RRCI->draw_dc_gouraud_polyline   = HD_Std_DC_Gouraud_Polyline;
	_hoops_RRCI->draw_dc_phong_polyline	= HD_Std_DC_Phong_Polyline;
	_hoops_RRCI->draw_dc_textured_polyline  = HD_Std_DC_Textured_Polyline;

	_hoops_RRCI->draw_dc_polymarker			= HD_Std_DC_Polymarker;
	_hoops_RRCI->draw_dc_colorized_polymarker = HD_Std_DC_Colorized_Polymarker;

	_hoops_RRCI->draw_dc_polydot				= HD_Std_DC_Polydot;
	_hoops_RRCI->draw_dc_colorized_polydot	= HD_Std_DC_Colorized_Polydot;

	_hoops_RRCI->_hoops_CICGA			= _hoops_RRSHH;
	_hoops_RRCI->_hoops_GCCGA = HD_Rasterize_DC_Spans_C24_U;
	_hoops_RRCI->_hoops_ACCGA	= HD_Rasterize_DC_Spans_C24_G;
	_hoops_RRCI->_hoops_HCCGA	= HD_Rasterize_DC_Spans_C24_R;

	_hoops_RRCI->_hoops_CCCGA		= _hoops_CCCGA;
	_hoops_RRCI->_hoops_GSCGA	= _hoops_GSCGA;
	_hoops_RRCI->_hoops_CCCSR = _hoops_CCCSR;
	_hoops_RRCI->_hoops_PSCGA= _hoops_PSCGA;
	_hoops_RRCI->draw_dc_rgb32_rasters	= draw_dc_rgb32_rasters;

	_hoops_RRCI->_hoops_CSCGA			= HD_Standard_Draw_Inter_Text;
	_hoops_RRCI->_hoops_AGCSR			= HD_Standard_Draw_Plain_Text;

	_hoops_RRCI->draw_overlay_list		= HD_Standard_Draw_Overlay_List;
	_hoops_RRCI->_hoops_SCPGR		= HD_Standard_UnDraw_Overlay_List;

	_hoops_RRCI->_hoops_ISCSP		= HD_No_Such_Keyboard;
	_hoops_RRCI->_hoops_HSCSP		= HD_No_Such_Locater;

	_hoops_RRCI->_hoops_SCCSR	= _hoops_SCCSR;

	_hoops_RRCI->_hoops_CACSR		= _hoops_CACSR;
	_hoops_RRCI->find_all_fonts			= find_all_fonts;
	_hoops_RRCI->_hoops_AACSR			= _hoops_AACSR;
	_hoops_RRCI->load_font				= load_font;
	_hoops_RRCI->unload_font				= unload_font;
	_hoops_RRCI->measure_char			= measure_char;
	_hoops_RRCI->_hoops_SRCSR				= HD_Standard_Draw_Font;
	_hoops_RRCI->_hoops_CSCSP				= HD_Standard_Name_Font;
	_hoops_RRCI->map_font_char_index     = HD_Standard_Map_Char_Index;
	_hoops_RRCI->_hoops_SSCSP			    = HD_Standard_Size_Font;
	_hoops_RRCI->_hoops_GGSSP		= HD_Standard_Will_Use_Stencil;
	_hoops_RRCI->_hoops_RGSSP		= nullroutine;

	_hoops_RRCI->_hoops_CAAGR			= _hoops_CAAGR;

	_hoops_RRCI->_hoops_AGSSP			= HD_Standard_Compute_Shading;

	_hoops_RRCI->_hoops_PGSSP			= nullroutine;
	_hoops_RRCI->_hoops_HGSSP		= nullroutine;

	_hoops_RRCI->_hoops_IGSSP		= HD_Std_Create_Frame_Buffer;
	_hoops_RRCI->_hoops_CGSSP	= HD_Std_Display_Frame_Buffer;
	_hoops_RRCI->_hoops_SGSSP	= HD_Std_Destroy_Frame_Buffer;

	_hoops_RRCI->_hoops_SSRGR = nullroutine;

	_hoops_RRCI->_hoops_GRSSP = nullroutine;
	_hoops_RRCI->_hoops_RRSSP = nullroutine;
	_hoops_RRCI->_hoops_CRGIP = nullroutine;


	_hoops_RRCI->create_region = nullroutine;
	_hoops_RRCI->_hoops_HIPGR = nullroutine;
	_hoops_RRCI->_hoops_PIPGR = nullroutine;
	_hoops_RRCI->_hoops_ISPGR = nullroutine;
	_hoops_RRCI->_hoops_CSPGR = nullroutine;
	_hoops_RRCI->_hoops_AGHGR = nullroutine;

	_hoops_RRCI->_hoops_RHH = HD_Std_Depth_Peeling;

	_hoops_RRCI->snapshot = nullroutine;
	_hoops_RRCI->_hoops_IGHGR = _hoops_IGHGR;

	_hoops_RRCI->_hoops_PICS = nullroutine;
	_hoops_RRCI->_hoops_IPSS = nullroutine;
	_hoops_RRCI->_hoops_GHGGR = nullroutine;

	(*_hoops_ARSHH) (_hoops_RRCI);
}




