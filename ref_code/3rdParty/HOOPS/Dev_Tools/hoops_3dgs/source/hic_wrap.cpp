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
 * $Id: obf_tmp.txt 1.30 2010-11-09 23:36:09 boni Exp $
 */

#define BUILDING_HOOPS_INTERNALS
#include "hic_wrap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#pragma warning (disable: 4996)	// _hoops_HPRGR _hoops_GSGR _hoops_PSCH _hoops_GHSAR _hoops_HGPSA
#endif

extern "C" {
typedef void (*_hoops_SHCCH)(HC_ANY_ARGS);
};
#define HIC_WRAP_FUNCTION(function) (_hoops_SHCCH)(function)

struct HIC_Envelope
{
	void * _hoops_GICCH;
	void * m_data;
};

static void _hoops_RICCH(HC_KEY key, const char * name, const char * _hoops_AICCH,
							_hoops_SHCCH func, HIC_Envelope * _hoops_PICCH)
{
	char _hoops_RCHIR[4096], _hoops_HICCH[4096];
	
	sprintf(_hoops_HICCH, "%s_%p", name, _hoops_PICCH->_hoops_GICCH);
	sprintf(_hoops_RCHIR, "%s=%s", _hoops_AICCH, _hoops_HICCH);

	HC_Open_Segment_By_Key(key);
		HC_Define_Callback_Name(_hoops_HICCH, func);
		HC_Set_Callback_With_Data(_hoops_RCHIR, _hoops_PICCH);
	HC_Close_Segment();
}

static void _hoops_IICCH(HC_KEY key, const char * name, const char * _hoops_AICCH, HIC_Envelope * _hoops_PICCH)
{
	char _hoops_HICCH[4096];

	sprintf(_hoops_HICCH, "%s_%p", name, _hoops_PICCH->_hoops_GICCH);
		
	HC_Open_Segment_By_Key(key);
		HC_UnSet_One_Callback(_hoops_AICCH);
		HC_UnDefine_Callback_Name(_hoops_HICCH);
	HC_Close_Segment();
}

/* _hoops_CICCH _hoops_SICCH */

extern "C" {
	static void _hoops_GCCCH(HIC_Rendition const *nr, HIC_DC_Point const *points)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Line * me=(Draw_DC_Line *)data->_hoops_GICCH;
		me->draw_dc_line(nr, points);
	}
};

class Draw_DC_Line_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Line_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Line_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
};


Draw_DC_Line::Draw_DC_Line(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Line_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc line", 
		HIC_WRAP_FUNCTION(&_hoops_GCCCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Line::~Draw_DC_Line()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc line", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Line::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Line::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_PGSA 3d _hoops_CPAP _hoops_CAPGR  */

extern "C" {

	static void _hoops_HCCCH(HIC_Rendition const *nr,HIC_Geometry const  *geo)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Geometry * me=(Draw_3D_Geometry *)data->_hoops_GICCH;
		me->draw_3d_geometry(nr, geo);
	}

};

class Draw_3D_Geometry_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Geometry_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Geometry_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
};


Draw_3D_Geometry::Draw_3D_Geometry(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Geometry_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d geometry", 
		HIC_WRAP_FUNCTION(&_hoops_HCCCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Geometry::~Draw_3D_Geometry()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d geometry", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Geometry::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Geometry::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP 3D _hoops_HPSCP _hoops_ISSS  */
extern "C" {                               
static void _hoops_ICCCH(HIC_Rendition const *nr, HIC_Text const *text)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Text * me=(Draw_3D_Text *)data->_hoops_GICCH;

		me->draw_3d_text(nr,text);
	}
};

class Draw_3D_Text_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Text_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Text_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Text::Draw_3D_Text(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Text_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d text", 
		HIC_WRAP_FUNCTION(&_hoops_ICCCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Text::~Draw_3D_Text()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d text", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Text::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Text::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP 3D _hoops_CCCCH _hoops_ISSS  */
extern "C" {                                 
static void _hoops_SCCCH(HIC_Rendition const *nr, HIC_NURBS_Curve const *curve)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Curve * me=(Draw_3D_Curve *)data->_hoops_GICCH;

		me->draw_3d_curve(nr,curve);
	}
};

class Draw_3D_Curve_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Curve_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Curve_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Curve::Draw_3D_Curve(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Curve_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d curve", 
		HIC_WRAP_FUNCTION(&_hoops_SCCCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Curve::~Draw_3D_Curve()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d curve", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Curve::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Curve::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP 3D _hoops_GSCCH _hoops_ISSS  */
extern "C" {                                  
static void _hoops_RSCCH(HIC_Rendition const *nr, HIC_Cylinder const *cylinder)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Cylinder * me=(Draw_3D_Cylinder *)data->_hoops_GICCH;

		me->draw_3d_cylinder(nr,cylinder);
	}
};

class Draw_3D_Cylinder_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Cylinder_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Cylinder_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Cylinder::Draw_3D_Cylinder(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Cylinder_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d cylinder", 
		HIC_WRAP_FUNCTION(&_hoops_RSCCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Cylinder::~Draw_3D_Cylinder()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d cylinder", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Cylinder::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Cylinder::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP 3D _hoops_CSCGR _hoops_ISSS  */
extern "C" {                           
	static void _hoops_ASCCH(HIC_Rendition const *nr, HIC_Ellipse const *ellipse)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Ellipse * me=(Draw_3D_Ellipse *)data->_hoops_GICCH;

		me->draw_3d_ellipse(nr,ellipse);
	}
};

class Draw_3D_Ellipse_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Ellipse_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Ellipse_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	

};


Draw_3D_Ellipse::Draw_3D_Ellipse(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Ellipse_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d ellipse", 
		HIC_WRAP_FUNCTION(&_hoops_ASCCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Ellipse::~Draw_3D_Ellipse()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d ellipse", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Ellipse::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Ellipse::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP 3D _hoops_PSCCH _hoops_ISSS  */
extern "C" {                                  
static void _hoops_HSCCH(HIC_Rendition const *nr, HIC_Elliptical_Arc const *arc)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Elliptical_Arc * me=(Draw_3D_Elliptical_Arc *)data->_hoops_GICCH;

		me->draw_3d_elliptical_arc(nr,arc);
	}
};

class Draw_3D_Elliptical_Arc_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Elliptical_Arc_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Elliptical_Arc_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Elliptical_Arc::Draw_3D_Elliptical_Arc(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Elliptical_Arc_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d elliptical arc", 
		HIC_WRAP_FUNCTION(&_hoops_HSCCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Elliptical_Arc::~Draw_3D_Elliptical_Arc()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d elliptical arc", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Elliptical_Arc::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Elliptical_Arc::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP 3D _hoops_ISCCH _hoops_ISSS  */
extern "C" {                            
static void _hoops_CSCCH(HIC_Rendition const *nr, HIC_Grid const *grid)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Grid * me=(Draw_3D_Grid *)data->_hoops_GICCH;

		me->draw_3d_grid(nr,grid);
	}
};

class Draw_3D_Grid_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Grid_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Grid_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Grid::Draw_3D_Grid(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Grid_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d grid", 
		HIC_WRAP_FUNCTION(&_hoops_CSCCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Grid::~Draw_3D_Grid()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d grid", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Grid::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Grid::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP 3D_hoops_SSCCH _hoops_ISSS  */
extern "C" {                              
static void _hoops_GGSCH(HIC_Rendition const *nr, HIC_Image const *image)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Image * me=(Draw_3D_Image *)data->_hoops_GICCH;

		me->draw_3d_image(nr,image);
	}
};

class Draw_3D_Image_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Image_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Image_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Image::Draw_3D_Image(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Image_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d image", 
		HIC_WRAP_FUNCTION(&_hoops_GGSCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Image::~Draw_3D_Image()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d image", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Image::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Image::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP 3D_hoops_RGSCH _hoops_ISSS  */
extern "C" {                        
static void _hoops_AGSCH(HIC_Rendition const *nr, HIC_Marker const *marker)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Marker * me=(Draw_3D_Marker *)data->_hoops_GICCH;

		me->draw_3d_marker(nr,marker);
	}
};

class Draw_3D_Marker_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Marker_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Marker_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Marker::Draw_3D_Marker(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Marker_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d marker", 
		HIC_WRAP_FUNCTION(&_hoops_AGSCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Marker::~Draw_3D_Marker()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d marker", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Marker::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Marker::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP 3D_hoops_PGSCH _hoops_ISSS  */
extern "C" {                             
static void _hoops_HGSCH(HIC_Rendition const *nr, HIC_Polyhedron const *phon)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Mesh * me=(Draw_3D_Mesh *)data->_hoops_GICCH;

		me->draw_3d_mesh(nr,phon);
	}
};

class Draw_3D_Mesh_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Mesh_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Mesh_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Mesh::Draw_3D_Mesh(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Mesh_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d mesh", 
		HIC_WRAP_FUNCTION(&_hoops_HGSCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Mesh::~Draw_3D_Mesh()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d mesh", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Mesh::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Mesh::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP 3D_hoops_IGSCH _hoops_ISSS  */
extern "C" {                                 
static void _hoops_CGSCH(HIC_Rendition const *nr, HIC_NURBS_Curve const *curve)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Nurbs_Curve * me=(Draw_3D_Nurbs_Curve *)data->_hoops_GICCH;

		me->draw_3d_nurbs_curve(nr,curve);
	}
};

class Draw_3D_Nurbs_Curve_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Nurbs_Curve_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Nurbs_Curve_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Nurbs_Curve::Draw_3D_Nurbs_Curve(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Nurbs_Curve_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d nurbs curve", 
		HIC_WRAP_FUNCTION(&_hoops_CGSCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Nurbs_Curve::~Draw_3D_Nurbs_Curve()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d nurbs curve", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Nurbs_Curve::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Nurbs_Curve::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP 3D_hoops_SGSCH _hoops_ISSS  */
extern "C" {                                      
static void _hoops_GRSCH(HIC_Rendition const *nr, HIC_NURBS_Surface const *surface)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Nurbs_Surface * me=(Draw_3D_Nurbs_Surface *)data->_hoops_GICCH;

		me->draw_3d_nurbs_surface(nr,surface);
	}
};

class Draw_3D_Nurbs_Surface_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Nurbs_Surface_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Nurbs_Surface_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Nurbs_Surface::Draw_3D_Nurbs_Surface(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Nurbs_Surface_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d nurbs surface", 
		HIC_WRAP_FUNCTION(&_hoops_GRSCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Nurbs_Surface::~Draw_3D_Nurbs_Surface()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d nurbs surface", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Nurbs_Surface::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Nurbs_Surface::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP 3D_hoops_RRSCH _hoops_ISSS  */
extern "C" {                           
static void _hoops_ARSCH(HIC_Rendition const *nr, HIC_Polygon const *polygon)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Polygon * me=(Draw_3D_Polygon *)data->_hoops_GICCH;

		me->draw_3d_polygon(nr,polygon);
	}
};

class Draw_3D_Polygon_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Polygon_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Polygon_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Polygon::Draw_3D_Polygon(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Polygon_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polygon", 
		HIC_WRAP_FUNCTION(&_hoops_ARSCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Polygon::~Draw_3D_Polygon()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polygon", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Polygon::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Polygon::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP 3D_hoops_PRSCH _hoops_ISSS  */
extern "C" {                            
static void _hoops_HRSCH(HIC_Rendition const *nr, HIC_Polyline const *polyline)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Polyline * me=(Draw_3D_Polyline *)data->_hoops_GICCH;

		me->draw_3d_polyline(nr,polyline);
	}
};

class Draw_3D_Polyline_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Polyline_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Polyline_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Polyline::Draw_3D_Polyline(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Polyline_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polyline", 
		HIC_WRAP_FUNCTION(&_hoops_HRSCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Polyline::~Draw_3D_Polyline()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polyline", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Polyline::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Polyline::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP 3D_hoops_IRSCH _hoops_ISSS  */
extern "C" {                                  
static void _hoops_CRSCH(HIC_Rendition const *nr, HIC_Polymarker const *pm)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Polymarkers * me=(Draw_3D_Polymarkers *)data->_hoops_GICCH;

		me->draw_3d_polymarker(nr,pm);
	}
};

class Draw_3D_Polymarkers_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Polymarkers_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Polymarkers_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Polymarkers::Draw_3D_Polymarkers(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Polymarkers_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polymarker", 
		HIC_WRAP_FUNCTION(&_hoops_CRSCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Polymarkers::~Draw_3D_Polymarkers()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polymarker", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Polymarkers::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Polymarkers::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP 3D_hoops_SRSCH _hoops_ISSS  */
extern "C" {                                        
static void _hoops_GASCH(HIC_Rendition const *nr, HIC_Polycylinder const *polycylinder)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Polycylinder * me=(Draw_3D_Polycylinder *)data->_hoops_GICCH;

		me->draw_3d_polycylinder(nr,polycylinder);
	}
};

class Draw_3D_Polycylinder_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Polycylinder_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Polycylinder_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Polycylinder::Draw_3D_Polycylinder(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Polycylinder_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polycylinder", 
		HIC_WRAP_FUNCTION(&_hoops_GASCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Polycylinder::~Draw_3D_Polycylinder()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polycylinder", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Polycylinder::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Polycylinder::GetName()
{
	return _impl->_hoops_RCCCH;
}

/* _hoops_CICCH _hoops_GISP 3D_hoops_RASCH _hoops_ISSS  */
extern "C" {                            
static void _hoops_AASCH(HIC_Rendition const *nr, HIC_Polyedge const *pe)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Polyedge * me=(Draw_3D_Polyedge *)data->_hoops_GICCH;

		me->draw_3d_polyedge(nr,pe);
	}
};

class Draw_3D_Polyedge_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Polyedge_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Polyedge_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Polyedge::Draw_3D_Polyedge(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Polyedge_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polyedge", 
		HIC_WRAP_FUNCTION(&_hoops_AASCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Polyedge::~Draw_3D_Polyedge()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polyedge", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Polyedge::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Polyedge::GetName()
{
	return _impl->_hoops_RCCCH;
}

/* _hoops_CICCH _hoops_GISP 3D_hoops_GAISP _hoops_ISSS  */
extern "C" {                                        
static void _hoops_PASCH(HIC_Rendition const *nr, HIC_Polyhedron const *phon)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Polyhedron * me=(Draw_3D_Polyhedron *)data->_hoops_GICCH;

		me->draw_3d_polyhedron(nr,phon);
	}
};

class Draw_3D_Polyhedron_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Polyhedron_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Polyhedron_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Polyhedron::Draw_3D_Polyhedron(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Polyhedron_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polyhedron", 
		HIC_WRAP_FUNCTION(&_hoops_PASCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Polyhedron::~Draw_3D_Polyhedron()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d polyhedron", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Polyhedron::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Polyhedron::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP 3D_hoops_HASCH _hoops_ISSS  */
extern "C" {           
static void _hoops_IASCH(HIC_Rendition const *nr, HIC_Polyhedron const *phon)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Shell * me=(Draw_3D_Shell *)data->_hoops_GICCH;

		me->draw_3d_shell(nr,phon);
	}
};

class Draw_3D_Shell_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Shell_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Shell_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Shell::Draw_3D_Shell(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Shell_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d shell", 
		HIC_WRAP_FUNCTION(&_hoops_IASCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Shell::~Draw_3D_Shell()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d shell", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Shell::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Shell::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP 3D_hoops_CASCH _hoops_ISSS  */

extern "C" {                                            
static void _hoops_SASCH(HIC_Rendition const *nr, HIC_Sphere const *sphere)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Sphere * me=(Draw_3D_Sphere *)data->_hoops_GICCH;

		me->draw_3d_sphere(nr,sphere);
	}
};

class Draw_3D_Sphere_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Sphere_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Sphere_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Sphere::Draw_3D_Sphere(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Sphere_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d sphere", 
		HIC_WRAP_FUNCTION(&_hoops_SASCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Sphere::~Draw_3D_Sphere()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d sphere", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Sphere::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Sphere::GetName()
{
	return _impl->_hoops_RCCCH;
}

/* _hoops_CICCH _hoops_GISP 3D_hoops_GPSCH _hoops_ISSS  */

extern "C" {                                                
static void _hoops_RPSCH(HIC_Rendition const *nr, HIC_NURBS_Surface const *surface)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Surface * me=(Draw_3D_Surface *)data->_hoops_GICCH;

		me->draw_3d_surface(nr,surface);
	}
};

class Draw_3D_Surface_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Surface_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Surface_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Surface::Draw_3D_Surface(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Surface_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d surface", 
		HIC_WRAP_FUNCTION(&_hoops_RPSCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Surface::~Draw_3D_Surface()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d surface", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Surface::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Surface::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP 3D_hoops_APSCH _hoops_ISSS  */

extern "C" {                                   
static void _hoops_PPSCH(HIC_Rendition const *nr, HIC_Tristrip const *tristrip)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Tristrip * me=(Draw_3D_Tristrip *)data->_hoops_GICCH;

		me->draw_3d_tristrip(nr,tristrip);
	}
};

class Draw_3D_Tristrip_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Tristrip_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Tristrip_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Tristrip::Draw_3D_Tristrip(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Tristrip_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d tristrip", 
		HIC_WRAP_FUNCTION(&_hoops_PPSCH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Tristrip::~Draw_3D_Tristrip()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d tristrip", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Tristrip::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Tristrip::GetName()
{
	return _impl->_hoops_RCCCH;
}




/* _hoops_CICCH _hoops_GISP _hoops_HPSCH _hoops_ISSS  */
extern "C" {                                      
static void _hoops_IPSCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points, HIC_RGBAS32 const *color)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Colorized_Face * me=(Draw_DC_Colorized_Face *)data->_hoops_GICCH;

		me->draw_dc_colorized_face(nr,count,points,color);
	}
};

class Draw_DC_Colorized_Face_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Colorized_Face_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Colorized_Face_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Colorized_Face::Draw_DC_Colorized_Face(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Colorized_Face_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized face", 
		HIC_WRAP_FUNCTION(&_hoops_IPSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Colorized_Face::~Draw_DC_Colorized_Face()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized face", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Colorized_Face::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Colorized_Face::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP _hoops_CPSCH _hoops_ISSS  */

extern "C" {                                       
static void _hoops_SPSCH(HIC_Rendition const *nr, HIC_DC_Point const *points, HIC_RGBAS32 const *color)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Colorized_Line * me=(Draw_DC_Colorized_Line *)data->_hoops_GICCH;

		me->draw_dc_colorized_line(nr,points,color);
	}
};

class Draw_DC_Colorized_Line_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Colorized_Line_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Colorized_Line_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Colorized_Line::Draw_DC_Colorized_Line(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Colorized_Line_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized line", 
		HIC_WRAP_FUNCTION(&_hoops_SPSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Colorized_Line::~Draw_DC_Colorized_Line()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized line", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Colorized_Line::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Colorized_Line::GetName()
{
	return _impl->_hoops_RCCCH;
}




/* _hoops_CICCH _hoops_GISP _hoops_GHSCH _hoops_ISSS  */

extern "C" {                                            
static void _hoops_RHSCH(HIC_Rendition const *nr, HIC_DC_Point const *point, HIC_RGBAS32 const *color)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Colorized_Marker * me=(Draw_DC_Colorized_Marker *)data->_hoops_GICCH;

		me->draw_dc_colorized_marker(nr,point,color);
	}
};

class Draw_DC_Colorized_Marker_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Colorized_Marker_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Colorized_Marker_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Colorized_Marker::Draw_DC_Colorized_Marker(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Colorized_Marker_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized marker", 
		HIC_WRAP_FUNCTION(&_hoops_RHSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Colorized_Marker::~Draw_DC_Colorized_Marker()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized marker", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Colorized_Marker::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Colorized_Marker::GetName()
{
	return _impl->_hoops_RCCCH;
}







// 4


/* _hoops_CICCH _hoops_GISP _hoops_AHSCH _hoops_ISSS  */

extern "C" {                                              
static void _hoops_PHSCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points, HIC_RGBAS32 const *color, bool single)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Colorized_Polyline * me=(Draw_DC_Colorized_Polyline *)data->_hoops_GICCH;

		me->draw_dc_colorized_polyline(nr,count,points,color,single);
	}
};

class Draw_DC_Colorized_Polyline_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Colorized_Polyline_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Colorized_Polyline_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Colorized_Polyline::Draw_DC_Colorized_Polyline(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Colorized_Polyline_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized polyline", 
		HIC_WRAP_FUNCTION(&_hoops_PHSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Colorized_Polyline::~Draw_DC_Colorized_Polyline()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized polyline", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Colorized_Polyline::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Colorized_Polyline::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP _hoops_HHSCH _hoops_ISSS  */

extern "C" {                                 
static void _hoops_IHSCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *point, HIC_RGBAS32 const *colors, bool single, float const *rotations, float const *size_fixups)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Colorized_Polymarker * me=(Draw_DC_Colorized_Polymarker *)data->_hoops_GICCH;

		me->draw_dc_colorized_polymarker(nr,count,point,colors,single,rotations,size_fixups);
	}
};

class Draw_DC_Colorized_Polymarker_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Colorized_Polymarker_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Colorized_Polymarker_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Colorized_Polymarker::Draw_DC_Colorized_Polymarker(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Colorized_Polymarker_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized polymarker", 
		HIC_WRAP_FUNCTION(&_hoops_IHSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Colorized_Polymarker::~Draw_DC_Colorized_Polymarker()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized polymarker", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Colorized_Polymarker::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Colorized_Polymarker::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP _hoops_CHSCH _hoops_ISSS  */

extern "C" {                                          
static void _hoops_SHSCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points, HIC_RGBAS32 const *color, bool single)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Colorized_Polytriangle * me=(Draw_DC_Colorized_Polytriangle *)data->_hoops_GICCH;

		me->draw_dc_colorized_polytriangle(nr, count,points,color,single);
	}
};

class Draw_DC_Colorized_Polytriangle_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Colorized_Polytriangle_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Colorized_Polytriangle_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Colorized_Polytriangle::Draw_DC_Colorized_Polytriangle(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Colorized_Polytriangle_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized polytriangle", 
		HIC_WRAP_FUNCTION(&_hoops_SHSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Colorized_Polytriangle::~Draw_DC_Colorized_Polytriangle()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized polytriangle", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Colorized_Polytriangle::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Colorized_Polytriangle::GetName()
{
	return _impl->_hoops_RCCCH;
}




/* _hoops_CICCH _hoops_GISP _hoops_GISCH _hoops_ISSS  */

extern "C" {                                  
static void _hoops_RISCH(HIC_Rendition const *nr, HIC_DC_Point const *points, HIC_RGBAS32 const *color)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Colorized_Triangle * me=(Draw_DC_Colorized_Triangle *)data->_hoops_GICCH;

		me->draw_dc_colorized_triangle(nr,points,color);
	}
};

class Draw_DC_Colorized_Triangle_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Colorized_Triangle_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Colorized_Triangle_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Colorized_Triangle::Draw_DC_Colorized_Triangle(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Colorized_Triangle_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized triangle", 
		HIC_WRAP_FUNCTION(&_hoops_RISCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Colorized_Triangle::~Draw_DC_Colorized_Triangle()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc colorized triangle", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Colorized_Triangle::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Colorized_Triangle::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP _hoops_AISCH _hoops_ISSS  */

extern "C" {                            
static void _hoops_PISCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Face * me=(Draw_DC_Face *)data->_hoops_GICCH;

		me->draw_dc_face(nr, count, points);
	}
};

class Draw_DC_Face_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Face_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Face_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Face::Draw_DC_Face(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Face_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc face", 
		HIC_WRAP_FUNCTION(&_hoops_PISCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Face::~Draw_DC_Face()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc face", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Face::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Face::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP _hoops_HISCH _hoops_ISSS  */

extern "C" {                                   
static void _hoops_IISCH(HIC_Rendition const *nr, HIC_DC_Point const *points, HIC_RGBAS32 const *colors)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Gouraud_Line * me=(Draw_DC_Gouraud_Line *)data->_hoops_GICCH;

		me->draw_dc_gouraud_line(nr,points,colors);
	}
};

class Draw_DC_Gouraud_Line_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Gouraud_Line_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Gouraud_Line_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Gouraud_Line::Draw_DC_Gouraud_Line(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Gouraud_Line_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc gouraud line", 
		HIC_WRAP_FUNCTION(&_hoops_IISCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Gouraud_Line::~Draw_DC_Gouraud_Line()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc gouraud line", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Gouraud_Line::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Gouraud_Line::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP _hoops_CISCH _hoops_ISSS  */

extern "C" {                               
static void _hoops_SISCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points, HIC_RGBAS32 const *colors)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Gouraud_Polyline * me=(Draw_DC_Gouraud_Polyline *)data->_hoops_GICCH;

		me->draw_dc_gouraud_polyline(nr,count,points,colors);
	}
};

class Draw_DC_Gouraud_Polyline_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Gouraud_Polyline_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Gouraud_Polyline_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Gouraud_Polyline::Draw_DC_Gouraud_Polyline(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Gouraud_Polyline_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc gouraud polyline", 
		HIC_WRAP_FUNCTION(&_hoops_SISCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Gouraud_Polyline::~Draw_DC_Gouraud_Polyline()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc gouraud polyline", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Gouraud_Polyline::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Gouraud_Polyline::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP _hoops_GCSCH _hoops_ISSS  */

extern "C" {                                          
	static void _hoops_RCSCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points, HIC_RGBAS32 const *colors)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Gouraud_Polytriangle * me=(Draw_DC_Gouraud_Polytriangle *)data->_hoops_GICCH;

		me->draw_dc_gouraud_polytriangle(nr, count,points,colors);
	}
};

class Draw_DC_Gouraud_Polytriangle_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Gouraud_Polytriangle_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Gouraud_Polytriangle_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
};


Draw_DC_Gouraud_Polytriangle::Draw_DC_Gouraud_Polytriangle(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Gouraud_Polytriangle_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc gouraud polytriangle", 
		HIC_WRAP_FUNCTION(&_hoops_RCSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Gouraud_Polytriangle::~Draw_DC_Gouraud_Polytriangle()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc gouraud polytriangle", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Gouraud_Polytriangle::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Gouraud_Polytriangle::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP _hoops_ACSCH _hoops_ISSS  */

extern "C" {                                          
static void _hoops_PCSCH(HIC_Rendition const *nr, HIC_DC_Point const *points, HIC_RGBAS32 const *colors)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Gouraud_Triangle * me=(Draw_DC_Gouraud_Triangle *)data->_hoops_GICCH;

		me->draw_dc_gouraud_triangle(nr,points,colors);
	}
};

class Draw_DC_Gouraud_Triangle_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Gouraud_Triangle_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Gouraud_Triangle_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Gouraud_Triangle::Draw_DC_Gouraud_Triangle(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Gouraud_Triangle_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc gouraud triangle", 
		HIC_WRAP_FUNCTION(&_hoops_PCSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Gouraud_Triangle::~Draw_DC_Gouraud_Triangle()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc gouraud triangle", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Gouraud_Triangle::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Gouraud_Triangle::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP _hoops_HCSCH  */
extern "C" {                       
static void _hoops_ICSCH(HIC_Rendition const *nr, HIC_DC_Point const *points)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Marker * me=(Draw_DC_Marker *)data->_hoops_GICCH;

		me->draw_dc_marker(nr, points);
	}
};

class Draw_DC_Marker_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Marker_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Marker_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Marker::Draw_DC_Marker(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Marker_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc marker", 
		HIC_WRAP_FUNCTION(&_hoops_ICSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Marker::~Draw_DC_Marker()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc marker", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Marker::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Marker::GetName()
{
	return _impl->_hoops_RCCCH;
}

/* _hoops_CICCH _hoops_GISP _hoops_CCSCH  */
extern "C" {                           
static void _hoops_SCSCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Phong_Polyline * me=(Draw_DC_Phong_Polyline *)data->_hoops_GICCH;

		me->draw_dc_phong_polyline(nr,count,points,colors,planes );
	}
};

class Draw_DC_Phong_Polyline_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Phong_Polyline_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Phong_Polyline_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Phong_Polyline::Draw_DC_Phong_Polyline(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Phong_Polyline_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc phong polyline", 
		HIC_WRAP_FUNCTION(&_hoops_SCSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Phong_Polyline::~Draw_DC_Phong_Polyline()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc phong polyline", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Phong_Polyline::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Phong_Polyline::GetName()
{
	return _impl->_hoops_RCCCH;
}

/* _hoops_CICCH _hoops_GISP _hoops_GSSCH  */
extern "C" {                                 
static void _hoops_RSSCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Phong_Polytriangle * me=(Draw_DC_Phong_Polytriangle *)data->_hoops_GICCH;

		me->draw_dc_phong_polytriangle(nr,count,points,colors,planes );
	}
};

class Draw_DC_Phong_Polytriangle_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Phong_Polytriangle_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Phong_Polytriangle_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Phong_Polytriangle::Draw_DC_Phong_Polytriangle(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Phong_Polytriangle_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc phong polytriangle", 
		HIC_WRAP_FUNCTION(&_hoops_RSSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Phong_Polytriangle::~Draw_DC_Phong_Polytriangle()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc phong polytriangle", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Phong_Polytriangle::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Phong_Polytriangle::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP _hoops_ASSCH  */
extern "C" {                        
	static void _hoops_PSSCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Polyline * me=(Draw_DC_Polyline *)data->_hoops_GICCH;

		me->draw_dc_polyline(nr,count,points);
	}
};

class Draw_DC_Polyline_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Polyline_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Polyline_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
};


Draw_DC_Polyline::Draw_DC_Polyline(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Polyline_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc polyline", 
		HIC_WRAP_FUNCTION(&_hoops_PSSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Polyline::~Draw_DC_Polyline()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc polyline", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Polyline::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Polyline::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP _hoops_HSSCH  */
extern "C" {                       
	static void _hoops_ISSCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *point, float const *rotations, float const *size_fixups)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Polymarker * me=(Draw_DC_Polymarker *)data->_hoops_GICCH;

		me->draw_dc_polymarker(nr,count,point,rotations,size_fixups);
	}
};

class Draw_DC_Polymarker_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Polymarker_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Polymarker_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}

};


Draw_DC_Polymarker::Draw_DC_Polymarker(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Polymarker_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc polymarker", 
		HIC_WRAP_FUNCTION(&_hoops_ISSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Polymarker::~Draw_DC_Polymarker()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc polymarker", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Polymarker::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Polymarker::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP _hoops_CSSCH  */
extern "C" {                                
static void _hoops_SSSCH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Polytriangle * me=(Draw_DC_Polytriangle *)data->_hoops_GICCH;

		me->draw_dc_polytriangle(nr,count,points);
	}
};

class Draw_DC_Polytriangle_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Polytriangle_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Polytriangle_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Polytriangle::Draw_DC_Polytriangle(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Polytriangle_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc polytriangle", 
		HIC_WRAP_FUNCTION(&_hoops_SSSCH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Polytriangle::~Draw_DC_Polytriangle()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc polytriangle", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Polytriangle::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Polytriangle::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP _hoops_GGGSH  */
extern "C" {                                
static void _hoops_RGGSH(HIC_Rendition const *nr, HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes, HIC_Parameter const *params, int param_width, HIC_Integer32 param_flags)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Reshaded_Line * me=(Draw_DC_Reshaded_Line *)data->_hoops_GICCH;

		me->draw_dc_reshaded_line(nr,points,colors,planes,params,param_width,param_flags);
	}
};

class Draw_DC_Reshaded_Line_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Reshaded_Line_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Reshaded_Line_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Reshaded_Line::Draw_DC_Reshaded_Line(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Reshaded_Line_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc reshaded line", 
		HIC_WRAP_FUNCTION(&_hoops_RGGSH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Reshaded_Line::~Draw_DC_Reshaded_Line()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc reshaded line", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Reshaded_Line::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Reshaded_Line::GetName()
{
	return _impl->_hoops_RCCCH;
}




/* _hoops_CICCH _hoops_GISP _hoops_AGGSH  */
extern "C" {                            

};

extern "C" {
static void _hoops_PGGSH(HIC_Rendition const *nr, HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes, HIC_Parameter const *params, int param_width, HIC_Integer32 param_flags)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Reshaded_Triangle * me=(Draw_DC_Reshaded_Triangle *)data->_hoops_GICCH;

		me->draw_dc_reshaded_triangle(nr,points,colors,planes,params,param_width,param_flags);
	}
};

class Draw_DC_Reshaded_Triangle_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Reshaded_Triangle_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Reshaded_Triangle_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Reshaded_Triangle::Draw_DC_Reshaded_Triangle(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Reshaded_Triangle_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc reshaded triangle", 
		HIC_WRAP_FUNCTION(&_hoops_PGGSH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Reshaded_Triangle::~Draw_DC_Reshaded_Triangle()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc reshaded triangle", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Reshaded_Triangle::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Reshaded_Triangle::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP _hoops_HPSCP  */
extern "C" {                 
static void _hoops_HGGSH(HIC_Rendition const *nr, HIC_Text_Info const *ti)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_Text * me=(Draw_Text *)data->_hoops_GICCH;

		me->draw_text(nr, ti);
	}
};

class Draw_Text_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_Text_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_Text_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_Text::Draw_Text(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_Text_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw text", 
		HIC_WRAP_FUNCTION(&_hoops_HGGSH), &(_impl->_hoops_ACCCH));
}

Draw_Text::~Draw_Text()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw text", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_Text::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_Text::GetName()
{
	return _impl->_hoops_RCCCH;
}




/* _hoops_CICCH _hoops_GISP _hoops_IGGSH  */
extern "C" {                        
static void _hoops_CGGSH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes, float const *params, int param_width, HIC_Integer32 param_flags)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Textured_Polyline * me=(Draw_DC_Textured_Polyline *)data->_hoops_GICCH;

		me->draw_dc_textured_polyline(nr,count,points,colors,planes,params,param_width,param_flags);
	}
};

class Draw_DC_Textured_Polyline_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Textured_Polyline_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Textured_Polyline_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Textured_Polyline::Draw_DC_Textured_Polyline(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Textured_Polyline_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc textured polyline", 
		HIC_WRAP_FUNCTION(&_hoops_CGGSH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Textured_Polyline::~Draw_DC_Textured_Polyline()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc textured polyline", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Textured_Polyline::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Textured_Polyline::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_GISP _hoops_SGGSH  */
extern "C" {                                      

	static void _hoops_GRGSH(HIC_Rendition const *nr, int count, HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes, float const *params, int param_width, HIC_Integer32 param_flags)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Textured_Polytriangle * me=(Draw_DC_Textured_Polytriangle *)data->_hoops_GICCH;

		me->draw_dc_textured_polytriangle(nr,count,points,colors,planes,params,param_width,param_flags);
	}
};

class Draw_DC_Textured_Polytriangle_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Textured_Polytriangle_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Textured_Polytriangle_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
};


Draw_DC_Textured_Polytriangle::Draw_DC_Textured_Polytriangle(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Textured_Polytriangle_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc textured polytriangle", 
		HIC_WRAP_FUNCTION(&_hoops_GRGSH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Textured_Polytriangle::~Draw_DC_Textured_Polytriangle()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc textured polytriangle", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Textured_Polytriangle::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Textured_Polytriangle::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP _hoops_RRGSH  */
extern "C" {                                         
static void _hoops_ARGSH(HIC_Rendition const *nr, HIC_DC_Point const *points)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Triangle * me=(Draw_DC_Triangle *)data->_hoops_GICCH;

		me->draw_dc_triangle(nr,points);
	}
};

class Draw_DC_Triangle_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Triangle_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Triangle_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Triangle::Draw_DC_Triangle(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Triangle_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc triangle", 
		HIC_WRAP_FUNCTION(&_hoops_ARGSH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Triangle::~Draw_DC_Triangle()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc triangle", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Triangle::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Triangle::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GISP _hoops_GSRRR  */
extern "C" {                          
static void _hoops_PRGSH(HIC_Rendition const *nr, HIC_Segment_Info const *si)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_Segment * me=(Draw_Segment *)data->_hoops_GICCH;

		me->draw_segment(nr,si);
	}
};

class Draw_Segment_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_Segment_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_Segment_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_Segment::Draw_Segment(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_Segment_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw segment", 
		HIC_WRAP_FUNCTION(&_hoops_PRGSH), &(_impl->_hoops_ACCCH));
}

Draw_Segment::~Draw_Segment()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw segment", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_Segment::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_Segment::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_HRGSH  */
extern "C" {               
static void _hoops_IRGSH(HIC_Rendition const *nr, HIC_Int_Rectangle const *extent)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_Window * me=(Draw_Window *)data->_hoops_GICCH;

		me->draw_window(nr,extent);
	}
};

class Draw_Window_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_Window_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_Window_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_Window::Draw_Window(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_Window_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw window", 
		HIC_WRAP_FUNCTION(&_hoops_IRGSH), &(_impl->_hoops_ACCCH));
}

Draw_Window::~Draw_Window()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw window", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_Window::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_Window::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_CRGSH  */
extern "C" {                                            
static void _hoops_SRGSH(HIC_Rendition const *nr, HIC_Int_Rectangle const *extent, HIC_Int_Rectangle *frame, bool calculate_only)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_Window_Frame * me=(Draw_Window_Frame *)data->_hoops_GICCH;

		me->draw_window_frame(nr,extent,frame,calculate_only);
	}
};

class Draw_Window_Frame_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_Window_Frame_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_Window_Frame_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_Window_Frame::Draw_Window_Frame(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_Window_Frame_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw window frame", 
		HIC_WRAP_FUNCTION(&_hoops_SRGSH), &(_impl->_hoops_ACCCH));
}

Draw_Window_Frame::~Draw_Window_Frame()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw window frame", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_Window_Frame::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_Window_Frame::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GAGSH  */
extern "C" {                                        
static void _hoops_RAGSH(HIC_Rendition const *nr, bool swap_buffers)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Finish_Picture * me=(Finish_Picture *)data->_hoops_GICCH;

		me->finish_picture(nr,swap_buffers);
	}
};

class Finish_Picture_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Finish_Picture_Impl(): _hoops_RCCCH(0) {}

	virtual ~Finish_Picture_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Finish_Picture::Finish_Picture(HC_KEY key, const char * name, void * data)
{
	_impl = new Finish_Picture_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "finish picture", 
		HIC_WRAP_FUNCTION(&_hoops_RAGSH), &(_impl->_hoops_ACCCH));
}

Finish_Picture::~Finish_Picture()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "finish picture", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Finish_Picture::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Finish_Picture::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_AAGSH  */
extern "C" {                                               
static void _hoops_PAGSH(HIC_Rendition const *nr,HIC_Geometry const *geo)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Select_Geometry * me=(Select_Geometry *)data->_hoops_GICCH;

		me->select_geometry(nr,geo);
	}
};

class Select_Geometry_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Select_Geometry_Impl(): _hoops_RCCCH(0) {}

	virtual ~Select_Geometry_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Select_Geometry::Select_Geometry(HC_KEY key, const char * name, void * data)
{
	_impl = new Select_Geometry_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "select geometry", 
		HIC_WRAP_FUNCTION(&_hoops_PAGSH), &(_impl->_hoops_ACCCH));
}

Select_Geometry::~Select_Geometry()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "select geometry", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Select_Geometry::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Select_Geometry::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_HAGSH  */
extern "C" {                                                
static void _hoops_IAGSH(HIC_Rendition const *nr, HIC_Segment_Info const *si)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Select_Segment * me=(Select_Segment *)data->_hoops_GICCH;

		me->select_segment(nr,si);
	}
};

class Select_Segment_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Select_Segment_Impl(): _hoops_RCCCH(0) {}

	virtual ~Select_Segment_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Select_Segment::Select_Segment(HC_KEY key, const char * name, void * data)
{
	_impl = new Select_Segment_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "select segment", 
		HIC_WRAP_FUNCTION(&_hoops_IAGSH), &(_impl->_hoops_ACCCH));
}

Select_Segment::~Select_Segment()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "select segment", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Select_Segment::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Select_Segment::GetName()
{
	return _impl->_hoops_RCCCH;
}



/* _hoops_CICCH _hoops_CAGSH  */
extern "C" {                                                
static void _hoops_SAGSH(HIC_Rendition const *nr, HIC_Geometry *wi)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Select_Window * me=(Select_Window *)data->_hoops_GICCH;

		me->select_window(nr,wi);
	}
};

class Select_Window_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Select_Window_Impl(): _hoops_RCCCH(0) {}

	virtual ~Select_Window_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Select_Window::Select_Window(HC_KEY key, const char * name, void * data)
{
	_impl = new Select_Window_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "select window", 
		HIC_WRAP_FUNCTION(&_hoops_SAGSH), &(_impl->_hoops_ACCCH));
}

Select_Window::~Select_Window()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "select window", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Select_Window::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Select_Window::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GPGSH  */
extern "C" {                                                
static void _hoops_RPGSH(HIC_Rendition const*nr, HIC_Polyedge const*pe)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Isoline * me=(Draw_3D_Isoline *)data->_hoops_GICCH;

		me->draw_3d_isoline(nr,pe);
	}
};

class Draw_3D_Isoline_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Isoline_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Isoline_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Isoline::Draw_3D_Isoline(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Isoline_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d isoline", 
		HIC_WRAP_FUNCTION(&_hoops_RPGSH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Isoline::~Draw_3D_Isoline()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d isoline", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Isoline::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Isoline::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_APGSH  */
extern "C" {                                                
static void _hoops_PPGSH(HIC_Rendition const *nr, int count, HIC_DC_Point const*points )
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		HLR_Hidden_Polyline * me=(HLR_Hidden_Polyline *)data->_hoops_GICCH;

		me->hlr_hidden_polyline(nr,count,points);
	}
};

class HLR_Hidden_Polyline_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	HLR_Hidden_Polyline_Impl(): _hoops_RCCCH(0) {}

	virtual ~HLR_Hidden_Polyline_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


HLR_Hidden_Polyline::HLR_Hidden_Polyline(HC_KEY key, const char * name, void * data)
{
	_impl = new HLR_Hidden_Polyline_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "hlr hidden polylines", 
		HIC_WRAP_FUNCTION(&_hoops_PPGSH), &(_impl->_hoops_ACCCH));
}

HLR_Hidden_Polyline::~HLR_Hidden_Polyline()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "hlr hidden polylines", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * HLR_Hidden_Polyline::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * HLR_Hidden_Polyline::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_HPGSH  */
extern "C" {                                                
static void _hoops_IPGSH(HIC_Rendition const *nr, int count, HIC_DC_Point const*points )
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		HLR_Polyline * me=(HLR_Polyline *)data->_hoops_GICCH;

		me->hlr_polyline(nr,count,points);
	}
};

class HLR_Polyline_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	HLR_Polyline_Impl(): _hoops_RCCCH(0) {}

	virtual ~HLR_Polyline_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


HLR_Polyline::HLR_Polyline(HC_KEY key, const char * name, void * data)
{
	_impl = new HLR_Polyline_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "hlr polyline", 
		HIC_WRAP_FUNCTION(&_hoops_IPGSH), &(_impl->_hoops_ACCCH));
}

HLR_Polyline::~HLR_Polyline()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "hlr polyline", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * HLR_Polyline::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * HLR_Polyline::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_CPGSH  */
extern "C" {                                               
static void _hoops_SPGSH(HIC_Rendition const*nr, HIC_Segment_Info const *si)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_Segment_Tree * me=(Draw_Segment_Tree *)data->_hoops_GICCH;

		me->draw_segment_tree(nr,si);
	}
};

class Draw_Segment_Tree_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_Segment_Tree_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_Segment_Tree_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_Segment_Tree::Draw_Segment_Tree(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_Segment_Tree_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw segment tree", 
		HIC_WRAP_FUNCTION(&_hoops_SPGSH), &(_impl->_hoops_ACCCH));
}

Draw_Segment_Tree::~Draw_Segment_Tree()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw segment tree", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_Segment_Tree::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_Segment_Tree::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_GHGSH  */
extern "C" {                                                

static void _hoops_RHGSH(HIC_Rendition const*nr, HIC_Polyline const *il)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_3D_Infinite_Line * me=(Draw_3D_Infinite_Line *)data->_hoops_GICCH;

		me->draw_3d_infinite_line(nr,il);
	}

};

class Draw_3D_Infinite_Line_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_3D_Infinite_Line_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_3D_Infinite_Line_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_3D_Infinite_Line::Draw_3D_Infinite_Line(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_3D_Infinite_Line_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d infinite line", 
		HIC_WRAP_FUNCTION(&_hoops_RHGSH), &(_impl->_hoops_ACCCH));
}

Draw_3D_Infinite_Line::~Draw_3D_Infinite_Line()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw 3d infinite line", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_3D_Infinite_Line::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_3D_Infinite_Line::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_AHGSH  */
extern "C" {                                                
static void _hoops_PHGSH(HIC_Rendition const * nr, int count, HIC_DC_Point const* p)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Draw_DC_Edge * me=(Draw_DC_Edge *)data->_hoops_GICCH;

		me->draw_dc_edge(nr,count,p);
	}

};

class Draw_DC_Edge_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Draw_DC_Edge_Impl(): _hoops_RCCCH(0) {}

	virtual ~Draw_DC_Edge_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Draw_DC_Edge::Draw_DC_Edge(HC_KEY key, const char * name, void * data)
{
	_impl = new Draw_DC_Edge_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc edge", 
		HIC_WRAP_FUNCTION(&_hoops_PHGSH), &(_impl->_hoops_ACCCH));
}

Draw_DC_Edge::~Draw_DC_Edge()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "draw dc edge", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Draw_DC_Edge::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Draw_DC_Edge::GetName()
{
	return _impl->_hoops_RCCCH;
}


/* _hoops_CICCH _hoops_HHGSH  */
extern "C" {                                                
static void _hoops_IHGSH(HIC_Rendition const *nr, HIC_Driver_Shader_Type driver_type, HIC_Driver_Shader_Geometry_Type geom_type, HIC_Driver_Shader_Geometry_Bits geom_bits, void const *geometry)
	{
		HIC_Envelope * data = (HIC_Envelope*) HIC_Show_Callback_Data(nr);
		Set_Shader * me=(Set_Shader *)data->_hoops_GICCH;

		me->set_shader(nr,driver_type,geom_type,geom_bits,(long)geometry);
	}

};

class Set_Shader_Impl
{
public:
	HC_KEY _hoops_ACC;
	char * _hoops_RCCCH;
	HIC_Envelope  _hoops_ACCCH;

	Set_Shader_Impl(): _hoops_RCCCH(0) {}

	virtual ~Set_Shader_Impl()
	{
		delete [] _hoops_RCCCH;
	}

	void _hoops_PCCCH(const char * name)
	{
		if(_hoops_RCCCH)
			delete [] _hoops_RCCCH;
		_hoops_RCCCH= new char [strlen(name)+1];
		strcpy(_hoops_RCCCH, name);
	}
	
	
};


Set_Shader::Set_Shader(HC_KEY key, const char * name, void * data)
{
	_impl = new Set_Shader_Impl();

	_impl->_hoops_ACC=key;
	_impl->_hoops_PCCCH(name);
	_impl->_hoops_ACCCH._hoops_GICCH=this;
	_impl->_hoops_ACCCH.m_data=data;


	_hoops_RICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "set shader", 
		HIC_WRAP_FUNCTION(&_hoops_IHGSH), &(_impl->_hoops_ACCCH));
}

Set_Shader::~Set_Shader()
{	
	_hoops_IICCH(_impl->_hoops_ACC, _impl->_hoops_RCCCH, "set shader", &(_impl->_hoops_ACCCH));

	delete _impl;
}

void * Set_Shader::GetData()
{
	return _impl->_hoops_ACCCH.m_data;
}

const char * Set_Shader::GetName()
{
	return _impl->_hoops_RCCCH;
}

