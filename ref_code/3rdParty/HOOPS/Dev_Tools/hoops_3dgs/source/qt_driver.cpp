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
 * $Id: obf_tmp.txt 1.41 2010-10-23 01:16:17 trask Exp $
 */



#ifndef QT_DRIVER
#include "hoops.h"
#include "hd_proto.h"

extern "C" bool HC_CDECL
HD_QT_Driver(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED(request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "qt");
}

#else

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QRegion>
#include <QThread>
#include <QLinkedList>
#include <QPrinter>
#include <QPrintDialog>
#include <QPageSetupDialog>
#include <QColor>

#undef FALSE
#undef TRUE
#include "hoops.h"
#include "hd_proto.h"

#define USE_ZLIB
#define NO_DEBUG_SEQUENCE_DRAW
#define NO_DEBUG_SEQUENCE_PUNT
#define NO_DEBUG_SEQUENCE_DOC
#define NO_DEBUG_SEQUENCE_DOC_NAME

//_hoops_HIRGS _hoops_SCHGR _hoops_PPSRR _hoops_SIH
#define DEBUG_USE_SCREEN_RESOLUTION		0x00000001
#define DEBUG_PRINT_DIALOG				0x00000002
#define	_hoops_IIRGS		0x00000004


#include "database.h"
#include "driver.h"

#include "filedata.h"
#include "hic.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "please.h"
#include "searchh.h"
#include "tandt.h"
#include "span.h"
#include "hversion.h"
#include "adt.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <locale.h>
#include <limits.h>



#ifdef USE_ZLIB
# include <Zlib/zlib.h>
#endif

#ifdef _hoops_CIRGS
#		define _hoops_SIRGS(_hoops_RIIPC) {printf ("PDF DRAW: %s:%d   %s\n", __FILE__, __LINE__, _hoops_RIIPC);}
#else
#		define _hoops_SIRGS(_hoops_RIIPC)
#endif

#ifdef _hoops_GCRGS
#		define _hoops_RCRGS(_hoops_RIIPC) {printf ("\tPDF DOC: %s:%d   %s\n", __FILE__, __LINE__, _hoops_RIIPC);}
#else
#		define _hoops_RCRGS(_hoops_RIIPC) 
#endif

#ifdef _hoops_ACRGS
#       define _hoops_PCRGS(_hoops_RIIPC) {printf("\tPDF PUNT: %s:%d   %s\n", __FILE__, __LINE__, _hoops_RIIPC);}
#else
#       define _hoops_PCRGS(_hoops_RIIPC)
#endif

enum {
	_hoops_HCRGS,
	_hoops_ICRGS,
	_hoops_SGSCR,
	_hoops_CCRGS,
	_hoops_SCRGS,
	_hoops_GSRGS,
	_hoops_RSRGS,
	_hoops_HCIPR
};
class DWidget;

struct Qt_Data {
	QApplication*    q_app;
	DWidget*		d_widget;
	int	_hoops_ASRGS, _hoops_PSRGS;
	int _hoops_HAP;
	float _hoops_HSRGS;
	bool			_hoops_ISRGS;
	bool			start_painting;
	bool			stop_painting;
	int paint_flag;
	int				_hoops_CIACC;
	
	bool	_hoops_ASASC;

	/* _hoops_HCISR _hoops_PIAP */
	int _hoops_GASRI;
	int _hoops_RAICC;
	int _hoops_AAICC;
	int _hoops_IRSRI;
	int _hoops_CSRGS;
	int _hoops_SSRGS;
	int _hoops_SAICC;
	int _hoops_GPICC;
	int _hoops_GGAGS;
	int _hoops_RGAGS;
	_hoops_GARRR _hoops_RPICC;
	Integer32 _hoops_APICC;
	Integer32 _hoops_AARSR;
};

#define QTD(dc) ((Qt_Data alter *)(dc->data))

class _hoops_AGAGS: public QPaintEvent{
public:
	int type;
	_hoops_AGAGS(QRegion _hoops_ISIAI);
};

_hoops_AGAGS::_hoops_AGAGS(QRegion _hoops_ISIAI) : QPaintEvent(_hoops_ISIAI) {
	type = _hoops_SGSCR;
}

class DWidget: public QWidget{
public:
	DWidget();
	~DWidget();
	int type;
	
	QPainter* hp;
	QPrinter* _hoops_PGAGS;
	bool _hoops_HGAGS;
	Display_Context alter * dc;

	int polyline_count, _hoops_IGAGS, _hoops_CGAGS, _hoops_SGAGS;
	DC_Point const	*polyline_points, *_hoops_GRAGS, *_hoops_RRAGS, *col_face_points;
	RGBAS32 *colors, color;
	QLinkedList<DC_Point> point_list;

	void _hoops_ARAGS(QPaintEvent* p);
	void draw();
};

DWidget::DWidget() : QWidget() {
	type = _hoops_HCRGS;
	_hoops_HGAGS = false;
	hp = 0;
}

DWidget::~DWidget() {
	destroy(true);
}

void DWidget::draw() {
	Qt_Data alter				*state = QTD (dc);

	if (state->_hoops_ASASC) {
			HD_Standard_Update(dc, 0);
	}
}

void DWidget::_hoops_ARAGS(QPaintEvent *p) {
	Qt_Data alter				*state = QTD (dc);

	if (state->_hoops_ASASC) {
		hp = new QPainter();
		hp->begin(this->_hoops_PGAGS);
			HD_Standard_Update(dc, 0);
		hp->end();
		delete hp;
	}
}






#define _hoops_PRAGS(x) ((x) * state->_hoops_HSRGS)
#define _hoops_HRAGS(x) ((x) / state->_hoops_HSRGS)
/*
 * _hoops_HSCAR _hoops_SGS _hoops_RHGSR _hoops_HCPH _hoops_IS _hoops_SRAC _hoops_SICAR
 */


local int _hoops_CPISR(Line_Rendition const		&_hoops_HC) {
	if ( (_hoops_HC->weight != 1) && BIT(_hoops_HC->style, LCAP_END_MASK)) {
		return -1; /* _hoops_SSCP _hoops_PCCP _hoops_RSGR _hoops_ACPC _hoops_SGS _hoops_HRGR _hoops_HAGH _hoops_HSAR _hoops_RH _hoops_HSPP _hoops_ACPC */
	}
	return 0;
}


local bool
start_device(Display_Context alter * dc)
{
	Qt_Data alter              *state;
	int _hoops_IHHII = 0;

	if (!dc->data) {
		ZALLOC (state, Qt_Data);
		dc->data = (void alter *) state;
		HD_Get_Bit_Patterns (dc, false);


		if (state->q_app = (QApplication*)QCoreApplication::instance ());
		else
			state->q_app = new QApplication(_hoops_IHHII, (char**)0);
		state->d_widget = new DWidget();
		//_hoops_PIAP->_hoops_IRAGS->_hoops_CRAGS(50, 50, 425, 550);
		state->d_widget->dc = dc;
		state->d_widget->hp = new QPainter();
		state->_hoops_CIACC = 0;
		
#ifndef SOLARIS_SYSTEM
		if (BIT(dc->options._hoops_IRARR, _hoops_IIRGS)){
			state->d_widget->_hoops_PGAGS = (QPrinter alter *) (dc->options._hoops_GCHSR);
		}
		else
#endif
		{
			if (BIT(dc->options._hoops_IRARR, DEBUG_USE_SCREEN_RESOLUTION))
				state->d_widget->_hoops_PGAGS = new QPrinter(QPrinter::ScreenResolution);
			else
				state->d_widget->_hoops_PGAGS = new QPrinter(QPrinter::HighResolution);
		}
		
		
		if (BIT(dc->options._hoops_IRARR, DEBUG_PRINT_DIALOG)) {
			QPrintDialog dialog(state->d_widget->_hoops_PGAGS);
			//_hoops_RHRGP._hoops_SRAGS(_hoops_HIRGS::_hoops_GAAGS);
			//_hoops_RHRGP._hoops_RAAGS(_hoops_HIRGS::_hoops_AAAGS);
			if (dialog.exec() == QDialog::Accepted) {
				// _hoops_HCR _hoops_HRGR _hoops_RIRA, _hoops_HIH _hoops_ASAC _hoops_RH _hoops_CRGH _hoops_IH _hoops_SPHR
				// _hoops_PIAP->_hoops_IRAGS->_hoops_CRGH();
			}
			else{
				delete state->d_widget->_hoops_PGAGS;
				//_hoops_HSCI _hoops_RHRGP;
				//_hoops_PIAP->_hoops_IRAGS->_hoops_HAGGR();
				delete state->d_widget;
				return false;
			}
		}
		else{
#ifndef SOLARIS_SYSTEM
			if (BIT(dc->options._hoops_IRARR, _hoops_IIRGS)){
			}
			else
#endif
			{
				state->d_widget->_hoops_PGAGS->setResolution(dc->options._hoops_GHHSR);
				state->d_widget->_hoops_PGAGS->setFullPage(true);
				state->d_widget->_hoops_PGAGS->setPageSize(QPrinter::A4);
			}
		}


		
		
		

		//_hoops_PIAP->_hoops_IRAGS->_hoops_PAAGS();

		//_hoops_HAAGS _hoops_IAAGS(_hoops_PIAP->_hoops_IRAGS->_hoops_GRGAI);
		//_hoops_IAAGS._hoops_CAAGS();
		
		state->_hoops_ASASC = true;
		state->_hoops_ISRGS = false;

		return true;
	}
	state = QTD(dc);

	if (state->_hoops_ASASC)
		return false;
	else 
		return true;
}


local void
stop_device(Display_Context alter * dc)
{
	Qt_Data alter				*state = QTD (dc);

	_hoops_SIRGS("stop_device");

	if (BIT(dc->flags, _hoops_SAISR)) {
		state->d_widget->hp->end();
		state->d_widget->hide();
		state->stop_painting = true;
	}


	//_hoops_PIAP->_hoops_SAAGS->_hoops_RIARR();
	//_hoops_PIAP->_hoops_IRAGS->_hoops_HAGGR();

	delete state->d_widget->hp;
	delete state->d_widget;
	FREE(state, Qt_Data);
	//_hoops_CSPH->_hoops_PIH = _hoops_IRAP;
}


local void
get_physical_info(Display_Context alter * dc)
{
	Qt_Data alter				*state = QTD (dc);
	dc->_hoops_PGCC.driver_type = "Qt";
	state->d_widget->setGeometry(state->d_widget->_hoops_PGAGS->pageRect());
	//_hoops_PIAP->_hoops_IRAGS->_hoops_CRAGS(0, 0, _hoops_PIAP->_hoops_IRAGS->_hoops_GRGAI->_hoops_IGAA()*_hoops_CSPH->_hoops_AAP._hoops_GPAGS, _hoops_PIAP->_hoops_IRAGS->_hoops_GRGAI->_hoops_APPS()*_hoops_CSPH->_hoops_AAP._hoops_GPAGS);

	if (state->d_widget->_hoops_PGAGS->orientation() == QPrinter::Landscape){
		dc->_hoops_PGCC._hoops_PRPSR.x = state->d_widget->_hoops_PGAGS->pageRect().width();
		dc->_hoops_PGCC._hoops_PRPSR.y = state->d_widget->_hoops_PGAGS->pageRect().height();
	}
	else{
		dc->_hoops_PGCC._hoops_PRPSR.x = state->d_widget->_hoops_PGAGS->pageRect().width();
		dc->_hoops_PGCC._hoops_PRPSR.y = state->d_widget->_hoops_PGAGS->pageRect().height();
	}

	if (dc->options.border && 0) {
		/* _hoops_PSRAR _hoops_CGRIR _hoops_ASCA _hoops_IGIR -- 1/2 _hoops_CPIHH _hoops_HCR _hoops_AARI */
		dc->_hoops_PGCC._hoops_ARISR.x = (int) (dc->options._hoops_GHHSR * 0.5);
		dc->_hoops_PGCC._hoops_ARISR.y = (int) (dc->options._hoops_GHHSR * 0.5);
	}


#ifndef SOLARIS_SYSTEM
	if (BIT(dc->options._hoops_IRARR, _hoops_IIRGS)){
		QSizeF _hoops_RPAGS = state->d_widget->_hoops_PGAGS->paperSize(QPrinter::Millimeter);
		float _hoops_APAGS = 0;
		float _hoops_PPAGS = 0;

        _hoops_APAGS = 0.1 * _hoops_RPAGS.width();
        _hoops_PPAGS = 0.1 * _hoops_RPAGS.height();

		dc->_hoops_PGCC.size.x = _hoops_APAGS;
		dc->_hoops_PGCC.size.y = _hoops_PPAGS;
	}
	else
#endif
	{
		if (dc->options._hoops_SPHSR.x != -1) {	/* _hoops_IPSP _hoops_CARSR _hoops_IGIR */
			dc->_hoops_PGCC.size.x = dc->options._hoops_SPHSR.x;
			dc->_hoops_PGCC.size.y = dc->options._hoops_SPHSR.y;
		}
		else {
			dc->_hoops_PGCC.size.x = 21.59f;
			dc->_hoops_PGCC.size.y = 27.94f;
		}
	}
	
	dc->current._hoops_PRPSR.x = dc->_hoops_PGCC._hoops_PRPSR.x;
	dc->current._hoops_PRPSR.y = dc->_hoops_PGCC._hoops_PRPSR.y;

	dc->current.size.x = dc->_hoops_PGCC.size.x;
	dc->current.size.y = dc->_hoops_PGCC.size.y;


	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	dc->_hoops_PGCC._hoops_PCHSR = 256;
	dc->_hoops_PGCC.flags |= _hoops_CAPGH;
	dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_PSHSR;
	dc->_hoops_PGCC._hoops_ICHSR = "laser printer";

	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;

	dc->_hoops_PGCC.flags &= ~_hoops_HSHSR;
	dc->_hoops_PGCC.flags |= _hoops_ISHSR;
	dc->_hoops_PGCC.flags |= _hoops_GIHSR;
	dc->_hoops_PGCC.flags |= _hoops_IPPGH;
	dc->_hoops_PGCC.flags |= _hoops_CCHSR;


	dc->_hoops_PGCC._hoops_CCPGH = dc->options._hoops_GHHSR/60.0f;
	if(dc->_hoops_PGCC._hoops_CCPGH < 1.0)
		dc->_hoops_PGCC._hoops_CCPGH = 1.0;
	
        /* #11903 _hoops_RGAR _hoops_ARP _hoops_SHIR _hoops_III _hoops_SGCR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_PIP _hoops_IPPSR _hoops_III _hoops_SGCR. */
        if(!dc->options._hoops_HHHSR)
            dc->_hoops_PGCC._hoops_IHHSR = dc->options._hoops_GHHSR/150.0f;
}


local POINTER_SIZED_INT
get_outer_window(Display_Context const * dc)
{
	Qt_Data alter				*state = QTD (dc);

	_hoops_SIRGS("get_outer_window");
	state->_hoops_ASASC = true;

	return (POINTER_SIZED_INT) state->d_widget;
}


local void
free_outer_window(Display_Context const * dc)
{
	Qt_Data alter				*state = QTD (dc);

	_hoops_SIRGS("free_outer_window");


	if (BIT(dc->flags, _hoops_SAISR)) {
		state->d_widget->hide();
		state->_hoops_ASASC = false;
	}
}


local void
init_picture(Net_Rendition const &  nr)
{
	Display_Context const	*dc = nr->_hoops_SRA;
	Qt_Data alter				*state = QTD (dc);
	bool					started_painting = false;

	if(BIT(dc->flags, _hoops_SAISR)){
		if(state->_hoops_CIACC)
			state->d_widget->_hoops_PGAGS->newPage();

		state->_hoops_CIACC++;
		state->d_widget->hp->begin(state->d_widget->_hoops_PGAGS);
	}
}


local void
finish_picture(Net_Rendition const &	nr,
			   bool					swap_buffers)
{
	Display_Context const	*dc = nr->_hoops_SRA;
	Qt_Data alter				*state = QTD (dc);
	bool		ended_painting = false;

	UNREFERENCED (swap_buffers);

	_hoops_SIRGS("finish_picture");


	/* _hoops_RPP (_hoops_IRRC(_hoops_CSPH->_hoops_SGI, _hoops_SASRH)) {
		_hoops_PIAP->_hoops_IRAGS->_hoops_HPAGS->_hoops_RSGR();
		_hoops_PIAP->_hoops_IRAGS->_hoops_IPPR();
		_hoops_PIAP->_hoops_IPAGS = _hoops_IHPR;
	}*/
}

local void
draw_3d_elliptical_arc (
		Net_Rendition const & nr,
		Elliptical_Arc const *arc) 
{
	Qt_Data alter			*state = QTD(nr->_hoops_SRA);
	Line_Rendition const &	_hoops_HC = nr->_hoops_AHP;
	Display_Context const		*dc = nr->_hoops_SRA;
	RGBAS32                      color;
	Circular_Arc const*			_hoops_HGSSR = (Circular_Arc const*)arc;

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_Elliptical_Arc (nr, arc);
		return;
	}


	float		height = state->d_widget->_hoops_PGAGS->pageRect().height() -1;

	state->d_widget->hp->setClipRect(QRectF(nr->_hoops_SAIR->_hoops_SCIH.left,
											state->d_widget->_hoops_PGAGS->pageRect().height() -1 
												- nr->_hoops_SAIR->_hoops_SCIH.top,
											nr->_hoops_SAIR->_hoops_SCIH.right,
											state->d_widget->_hoops_PGAGS->pageRect().height() -1
												-nr->_hoops_SAIR->_hoops_SCIH.bottom));



	_hoops_AAASP(dc, _hoops_HC->color, dc->_hoops_PGCC._hoops_PIHSR, color);

	QPen pen(QColor(color.r, color.g, color.b, color.a));
	if (_hoops_HC->weight == 1)
		pen.setWidth(0); // _hoops_CPAGS _hoops_CSGSR
	else
		pen.setWidthF(_hoops_HC->weight * dc->_hoops_PGCC._hoops_CCPGH);

	switch (_hoops_HC->style & LCAP_MASK) {
			case LCAP_BUTT:		pen.setCapStyle(Qt::FlatCap);  break;
			case LCAP_ROUND:	pen.setCapStyle(Qt::RoundCap); break;
			case LCAP_SQUARE:	pen.setCapStyle(Qt::SquareCap); break;
	}

	switch (_hoops_HC->style & LJOIN_MASK) {
			case LJOIN_MITER:	pen.setJoinStyle(Qt::MiterJoin); break;
			case LJOIN_ROUND:	pen.setJoinStyle(Qt::RoundJoin); break;
			case LJOIN_BEVEL:	pen.setJoinStyle(Qt::BevelJoin); break;
	}
	pen.setMiterLimit(900.0);

	int i;
	int * pattern;
	float _hoops_ICPGH;

	if (BIT(_hoops_HC->line_style->_hoops_GHISR[0].flags, LSF_ABSOLUTE_LENGTH))
		_hoops_ICPGH = 1.0f;
	else
		_hoops_ICPGH = dc->_hoops_PGCC._hoops_ICPGH;

	pattern = _hoops_HC->line_style->_hoops_GHISR[0].pattern;


	QVector<qreal> dashes;
	double value = 0.0;
	for (i = 0; i < _hoops_HC->line_style->_hoops_GHISR[0]._hoops_RHISR; i++) {
		value = (((double)pen.width() / (double)((double)pattern[i])));
		dashes << 1.0 / value ;
	}

	pen.setDashPattern(dashes);
	

	state->d_widget->hp->setPen(pen);

	_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
	DC_Point center, major, minor;
	float w;

	center.x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, arc->center);
	center.y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, arc->center);
	if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
		w = _hoops_PHCP (_hoops_IHCR->matrix->data.elements, arc->center);
		center.x /= w;
		center.y /= w;
	}

	major.x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, arc->major);
	major.y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, arc->major);
	if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
		w = _hoops_PHCP (_hoops_IHCR->matrix->data.elements, arc->major);
		major.x /= w;
		major.y /= w;
	}

	minor.x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, arc->minor);
	minor.y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, arc->minor);
	if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
		w = _hoops_PHCP (_hoops_IHCR->matrix->data.elements, arc->minor);
		minor.x /= w;
		minor.y /= w;
	}

	
	state->d_widget->hp->save();
		float _hoops_PCCHH, _hoops_HCCHH = 0.0;
		_hoops_PCCHH = (sqrt(pow((float)(major.x - center.x), (float)2.0) + pow((float)(major.y - center.y), (float)2.0)));
		_hoops_HCCHH = (sqrt(pow((float)(minor.x - center.x), (float)2.0) + pow((float)(minor.y - center.y), (float)2.0)));
		float x, xp, y, yp = 0.0;
		x = _hoops_PCCHH;
		xp = major.x - center.x;
		y = 0;
		yp = major.y - center.y;
		float theta = acos((y*yp + x*xp)/(x*x + y*y))*(360 / (2 * 3.14159));
		state->d_widget->hp->translate(center.x, height - center.y);
		
		state->d_widget->hp->rotate(-theta);
		state->d_widget->hp->translate(-_hoops_PCCHH, -_hoops_HCCHH);

		float _hoops_SPAGS = _hoops_PCCHH * cos(arc->arc_start);
		float end_point_x = _hoops_PCCHH * cos(arc->_hoops_PHHI);

		float e = sqrt(1.0 - sqrt(pow((float)_hoops_HCCHH, (float)2.0)/pow((float)_hoops_PCCHH, (float)2.0)));
		float focus = e * _hoops_PCCHH;


		float start_angle = acos(_hoops_SPAGS / (-_hoops_PCCHH));
		float _hoops_GHAGS = acos(end_point_x / (-_hoops_PCCHH));


		state->d_widget->hp->drawArc(QRectF(0, 0, 2*_hoops_PCCHH, 2*_hoops_HCCHH), ((int)(start_angle* (360 / (2 * 3.14159)))+180)*16, ((int)((_hoops_GHAGS-start_angle)*(360 / (2 * 3.14159)))+180)*16);
		
	state->d_widget->hp->restore();

}

local void draw_dc_ellipse (
	Net_Rendition const &	nr,
	DC_Point const			*center,
	DC_Point const			*radii) {
	Qt_Data alter			*state = QTD(nr->_hoops_SRA);
	Line_Rendition const &	_hoops_HC = nr->_hoops_AHP;
	Display_Context const		*dc = nr->_hoops_SRA;
	RGBAS32                      color;

	float		height = state->d_widget->_hoops_PGAGS->pageRect().height() -1;

	state->d_widget->hp->setClipRect(QRectF(0, 0, nr->_hoops_SAIR->extent.right - nr->_hoops_SAIR->extent.left, 
									nr->_hoops_SAIR->extent.top - nr->_hoops_SAIR->extent.bottom - 3));


	_hoops_AAASP(dc, nr->_hoops_IHA->color, dc->_hoops_PGCC._hoops_PIHSR, color);


	QBrush _hoops_RHAGS(QColor(color.r, color.g, color.b, color.a));
	QPen pen(QColor(color.r, color.g, color.b, color.a));
	/*_hoops_RPP (_hoops_HGICP->_hoops_SGCR == 1)
		_hoops_CSGSR._hoops_AHAGS(0); // _hoops_CPAGS _hoops_CSGSR
	_hoops_SHS
		_hoops_CSGSR._hoops_PHAGS(_hoops_HGICP->_hoops_SGCR * _hoops_CSPH->_hoops_CPHSR._hoops_HHAGS);

	_hoops_CICA (_hoops_HGICP->_hoops_IAHA & _hoops_GGCCC) {
			_hoops_AGIR _hoops_IHAGS:		_hoops_CSGSR._hoops_CHAGS(_hoops_HIRGS::_hoops_SHAGS);  _hoops_IHSA;
			_hoops_AGIR _hoops_GIAGS:	_hoops_CSGSR._hoops_CHAGS(_hoops_HIRGS::_hoops_RIAGS); _hoops_IHSA;
			_hoops_AGIR _hoops_AIAGS:	_hoops_CSGSR._hoops_CHAGS(_hoops_HIRGS::_hoops_PIAGS); _hoops_IHSA;
	}

	_hoops_CICA (_hoops_HGICP->_hoops_IAHA & _hoops_HIAGS) {
			_hoops_AGIR _hoops_IIAGS:	_hoops_CSGSR._hoops_CIAGS(_hoops_HIRGS::_hoops_SIAGS); _hoops_IHSA;
			_hoops_AGIR _hoops_GCAGS:	_hoops_CSGSR._hoops_CIAGS(_hoops_HIRGS::_hoops_RCAGS); _hoops_IHSA;
			_hoops_AGIR _hoops_ACAGS:	_hoops_CSGSR._hoops_CIAGS(_hoops_HIRGS::_hoops_PCAGS); _hoops_IHSA;
	}
	_hoops_CSGSR._hoops_HCAGS(900.0);

	
	_hoops_SCSH _hoops_HAS;
	_hoops_SCSH * _hoops_HSGP;
	_hoops_AIIC _hoops_PSHAI;

	_hoops_RPP (_hoops_IRRC(_hoops_HGICP->_hoops_PGRIP->_hoops_HRCPI[0]._hoops_SGI, _hoops_ICAGS))
		_hoops_PSHAI = 1.0f;
	_hoops_SHS
		_hoops_PSHAI = _hoops_CSPH->_hoops_CPHSR._hoops_PSHAI;

	_hoops_HSGP = _hoops_HGICP->_hoops_PGRIP->_hoops_HRCPI[0]._hoops_HSGP;


	
	_hoops_CCAGS<_hoops_SCAGS> _hoops_GSAGS;
	_hoops_GHGPR _hoops_PIRA = 0.0;
	_hoops_IH (_hoops_HAS = 0; _hoops_HAS < _hoops_HGICP->_hoops_PGRIP->_hoops_HRCPI[0]._hoops_RSAGS; _hoops_HAS++) {
		_hoops_PIRA = (((_hoops_GHGPR)_hoops_CSGSR._hoops_IGAA() / (_hoops_GHGPR)((_hoops_GHGPR)_hoops_HSGP[_hoops_HAS])));
		_hoops_GSAGS << 1.0 / _hoops_PIRA ;
	}

	_hoops_CSGSR._hoops_ASAGS(_hoops_GSAGS);
	*/
	

	state->d_widget->hp->setPen(pen);
	state->d_widget->hp->setBrush(_hoops_RHAGS);



	state->d_widget->hp->drawEllipse(QRectF(center->x - radii[0].x, 
											(nr->_hoops_SAIR->extent.top -center->y) - radii[0].y, 
											radii[0].x*2, radii[0].y*2));
}


local void
draw_dc_polydot(Net_Rendition const &	nr,
				int						count,
				DC_Point const *	points)
{
	Qt_Data alter			*state = QTD(nr->_hoops_SRA);
	_hoops_ICP const &	_hoops_CCP = nr->_hoops_GSP;
	Display_Context const		*dc = nr->_hoops_SRA;
	RGBAS32                      color;

	_hoops_AAASP(dc, _hoops_CCP->color, dc->_hoops_PGCC._hoops_PIHSR, color);
	state->d_widget->hp->setPen(QColor(color.r, color.g, color.b, color.a));

	for (int i = 0; i < count; i++) {
		state->d_widget->hp->drawPoint(QPointF(points[i].x, nr->_hoops_SAIR->extent.top - points[i].y));
	}
}

local void
draw_dc_colorized_polydot (
	Net_Rendition const & nr, 
	int						count, 
	DC_Point const		*points,	
	RGBAS32 const		*_hoops_IASGR,
	bool				single) {
	int a = count;
}

#if 0
local void
draw_3d_polymarker (Net_Rendition const &  nr,
					Polymarker const * pm) {
	Qt_Data alter			*state = QTD(nr->_hoops_SRA);

	
}
#endif

local void
draw_dc_polyline(Net_Rendition const    &nr,
				 int						count,
				 DC_Point const			*points) 
{
	Qt_Data alter			*state = QTD(nr->_hoops_SRA);
	Line_Rendition const &	_hoops_HC = nr->_hoops_AHP;
	Display_Context const		*dc = nr->_hoops_SRA;
	RGBAS32                      color;

	if (_hoops_CPISR(_hoops_HC)) {
			_hoops_PCRGS("LSF_COMPLES_ANYBITS LCAP_COMPLES_BITS");
			HD_Std_DC_Polyline (nr, count, points);
			return;
	}

	/*_hoops_PIAP->_hoops_IRAGS->_hoops_HPAGS->_hoops_PSAGS(_hoops_HSAGS(_hoops_SCII->_hoops_AGAIP->_hoops_ISAGS._hoops_RAAP,
											_hoops_PIAP->_hoops_IRAGS->_hoops_GRGAI->_hoops_CSAGS()._hoops_APPS() 
												- _hoops_SCII->_hoops_AGAIP->_hoops_ISAGS._hoops_SCIA - 2,
											_hoops_SCII->_hoops_AGAIP->_hoops_ISAGS._hoops_RPHR -
												_hoops_SCII->_hoops_AGAIP->_hoops_ISAGS._hoops_RAAP,
											_hoops_SCII->_hoops_AGAIP->_hoops_ISAGS._hoops_SCIA
												-_hoops_SCII->_hoops_AGAIP->_hoops_ISAGS._hoops_PRPC -2));*/

	state->d_widget->hp->setClipRect(QRectF(0, 0, nr->_hoops_SAIR->extent.right - nr->_hoops_SAIR->extent.left, 
									nr->_hoops_SAIR->extent.top - nr->_hoops_SAIR->extent.bottom - 3));



	_hoops_AAASP(dc, _hoops_HC->color, dc->_hoops_PGCC._hoops_PIHSR, color);

	QPen pen(QColor(color.r, color.g, color.b, color.a));
	/*_hoops_RPP (_hoops_HGICP->_hoops_SGCR == 1.0f)
		_hoops_CSGSR._hoops_AHAGS(0); // _hoops_CPAGS _hoops_CSGSR (_hoops_GRGR _hoops_IH _hoops_HA)
	_hoops_SHS */
		pen.setWidthF(_hoops_HC->weight * dc->_hoops_PGCC._hoops_CCPGH);

	switch (_hoops_HC->style & LCAP_MASK) {
			case LCAP_BUTT:		pen.setCapStyle(Qt::FlatCap);  break;
			case LCAP_ROUND:	pen.setCapStyle(Qt::RoundCap); break;
			case LCAP_SQUARE:	pen.setCapStyle(Qt::SquareCap); break;
	}

	switch (_hoops_HC->style & LJOIN_MASK) {
			case LJOIN_MITER:	pen.setJoinStyle(Qt::MiterJoin); break;
			case LJOIN_ROUND:	pen.setJoinStyle(Qt::RoundJoin); break;
			case LJOIN_BEVEL:	pen.setJoinStyle(Qt::BevelJoin); break;
	}
	pen.setMiterLimit(900.0);

	int i;
	int * pattern;
	float _hoops_ICPGH;

	if (BIT(_hoops_HC->line_style->_hoops_GHISR[0].flags, LSF_ABSOLUTE_LENGTH))
		_hoops_ICPGH = 1.0f;
	else
		_hoops_ICPGH = dc->_hoops_PGCC._hoops_ICPGH;

	pattern = _hoops_HC->line_style->_hoops_GHISR[0].pattern;


	QVector<qreal> dashes;
	double value = 0.0;
	for (i = 0; i < _hoops_HC->line_style->_hoops_GHISR[0]._hoops_RHISR; i++) {
		value = (((double)pen.width() / (double)((double)pattern[i])));
		dashes << 1.0 / value ;
	}

	pen.setDashPattern(dashes);
	

	state->d_widget->hp->setPen(pen);

	float _hoops_SSAGS = dc->_hoops_PGCC._hoops_PRPSR.x - nr->_hoops_SAIR->extent.right;


	if (count > 0) {
		QPointF *_hoops_GGPGS = new QPointF[count];
		for (int i =0; i < count; i++) {
			if( _hoops_SSAGS > 1)
				_hoops_GGPGS[i].setX(points[i].x - _hoops_SSAGS);
			else
				_hoops_GGPGS[i].setX(points[i].x );
			
			_hoops_GGPGS[i].setY((nr->_hoops_SAIR->extent.top - points[i].y) -1.0 );
		}
		state->d_widget->hp->drawPolyline(_hoops_GGPGS, count);
		delete[] _hoops_GGPGS;
	}
	else{
		int _hoops_RRC, pcount;
		_hoops_ICHC (count, _hoops_RRC, 2);
		pcount = count;
		QPointF *_hoops_GGPGS = new QPointF[count];
		while (pcount-- > 0) {
			_hoops_GGPGS[pcount].setX(points[pcount].x);
			_hoops_GGPGS[pcount].setY(dc->_hoops_PGCC._hoops_PRPSR.y -points[pcount].y);
		}
		state->d_widget->hp->drawPolyline(_hoops_GGPGS, count);
		delete[] _hoops_GGPGS;
	}

}

local void
draw_dc_polytriangle(Net_Rendition const &	nr,
					 int							count,
					 DC_Point const			*points)
{
	Qt_Data alter			*state = QTD(nr->_hoops_SRA);
	_hoops_CIGA const		    &_hoops_SIGA = nr->_hoops_IHA;
	Display_Context const		*dc = nr->_hoops_SRA;
	RGBAS32                      color;

	
	state->d_widget->hp->setClipRect(QRectF(0, 0, nr->_hoops_SAIR->extent.right - nr->_hoops_SAIR->extent.left, 
									nr->_hoops_SAIR->extent.top - nr->_hoops_SAIR->extent.bottom - 3));

	_hoops_AAASP(dc, _hoops_SIGA->color, dc->_hoops_PGCC._hoops_PIHSR, color);

	int height = state->d_widget->_hoops_PGAGS->pageRect().height() -1;

	state->d_widget->type = _hoops_CCRGS;
	state->d_widget->_hoops_IGAGS = count;
	state->d_widget->_hoops_GRAGS = points;
	state->d_widget->color = color;

	QPainter* hp = state->d_widget->hp;
	QPen pen(QColor(color.r, color.g, color.b, color.a)); 
	QBrush _hoops_RHAGS(QColor(color.r, color.g, color.b, color.a));

	if (_hoops_SIGA->pattern != 0) {
		HD_Std_DC_Polytriangle (nr, count, points);
				return;
	}

	hp->setPen(pen);
	hp->setBrush(_hoops_RHAGS);

	int _hoops_RRC;
	_hoops_ICHC (count, _hoops_RRC, 3);

	QPointF *pts = new QPointF[count * 3];
	int tri = 0;
	for (int i = 0; i < count*3; i++) {
		tri = i % 3;
		pts[tri].setX(state->d_widget->_hoops_GRAGS[i].x);
		pts[tri].setY( (nr->_hoops_SAIR->extent.top - state->d_widget->_hoops_GRAGS[i].y) );
		if (i > 0 && tri == 2) //_hoops_SR'_hoops_RISP _hoops_PIISR _hoops_GGR _hoops_RH _hoops_HRSSR _hoops_PPSR, _hoops_HIS _hoops_PGSA _hoops_RH _hoops_SCPH.
			hp->drawPolygon(pts, 3);
	}
	
	delete[] pts;

}

local void
draw_dc_colorized_polytriangle(Net_Rendition const &	nr,
							   int						count,
							   DC_Point const			*points,
							   RGBAS32 const			*colors,
							   bool					_hoops_AIPSP)
{
	Qt_Data alter			*state = QTD(nr->_hoops_SRA);
	state->d_widget->type = _hoops_SCRGS;
	state->d_widget->_hoops_CGAGS = count;
	state->d_widget->_hoops_RRAGS = points;
}

local void draw_dc_colorized_face (	Net_Rendition const & nr,
									int						count,
									DC_Point const		*points,
									RGBAS32	const		*color)
{
	Qt_Data alter			*state = QTD(nr->_hoops_SRA);
	_hoops_CIGA const		    &_hoops_SIGA = nr->_hoops_IHA;
	Display_Context const		*dc = nr->_hoops_SRA;
	RGBAS32                      _hoops_RSISR;


	state->d_widget->hp->setClipRect(QRectF(nr->_hoops_SAIR->_hoops_SCIH.left,
											state->d_widget->_hoops_PGAGS->pageRect().height() -1 
												- nr->_hoops_SAIR->_hoops_SCIH.top,
											nr->_hoops_SAIR->_hoops_SCIH.right,
											state->d_widget->_hoops_PGAGS->pageRect().height() -1
												-nr->_hoops_SAIR->_hoops_SCIH.bottom));


	int height = state->d_widget->_hoops_PGAGS->pageRect().height() -1;


	QPainter* hp = state->d_widget->hp;
	QPen pen(QColor(color->r, color->g, color->b, color->a)); 
	QBrush _hoops_RHAGS(QColor(color->r, color->g, color->b, color->a));

	hp->setPen(pen);
	hp->setBrush(_hoops_RHAGS);

	int _hoops_RRC;

	QPointF *pts = new QPointF[count];
	for (int i = 0; i < count; i++) {
		pts[i].setX(points[i].x);
		pts[i].setY(height - points[i].y);	
	}
	hp->drawPolygon(pts, count);
	
	delete[] pts;

}

local void
draw_dc_gouraud_polytriangle(Net_Rendition const &	nr,
							 int                     _hoops_ISHAR,
							 DC_Point const       *points,
							 RGBAS32 const        *colors)
{
	Qt_Data alter			*state = QTD(nr->_hoops_SRA);
}

	
local void
draw_dc_rgb32_rasters(Net_Rendition const &	nr,
					  DC_Point const         *start,
					  DC_Point const         *end,
					  int                       row_bytes,
					  RGBAS32 const          *_hoops_SACCC)
{
	Qt_Data alter			*state = QTD(nr->_hoops_SRA);
	QRgb pixel;
	int _hoops_RGPGS = (int)(end->x - start->x) +1;
	int raster_height = (int)(end->y - start->y) +1;
	int height = state->d_widget->height();
	QImage image(_hoops_RGPGS, 1, QImage::Format_ARGB32);
	for (int i = 0; i < _hoops_RGPGS; i++) {
		pixel = qRgba(_hoops_SACCC[i].r, _hoops_SACCC[i].g, _hoops_SACCC[i].b, _hoops_SACCC[i].a);
		image.setPixel(i, 0, pixel);
		//_hoops_CSCR._hoops_AGPGS(_hoops_HAS, 1, _hoops_AIR);
	}
	state->d_widget->hp->drawImage(QPointF(start->x , state->d_widget->_hoops_PGAGS->pageRect().height() - 1 - start->y ), image);
}

local void
draw_window(Net_Rendition const &  nr,
			Int_Rectangle const * extent)
{
	_hoops_CGRA const &_hoops_SGRA = nr->_hoops_SAIR;
	Display_Context const	*dc = nr->_hoops_SRA;
	Qt_Data alter			    *state = QTD (dc);
	Image const			    *image = null;
	_hoops_RCR					*_hoops_IICSR = null;

	_hoops_AIGH *rasters;
	int row, col, i, index;
	unsigned char * data;
	unsigned char ** rows;
	_hoops_CPAIR	_hoops_CICSR;


	if (_hoops_SGRA->_hoops_PGPH != null || _hoops_SGRA->_hoops_SICSR == null) {
		HD_Standard_Draw_Window(nr, extent);
		return;
	}

	if (nr->_hoops_GCCSR->count > 0) {
		_hoops_CICSR.textures = nr->_hoops_GCCSR->textures;
		_hoops_CICSR.keys = nr->_hoops_GCCSR->keys;
		_hoops_CICSR.count = nr->_hoops_GCCSR->count;
	}else{
		_hoops_CICSR.textures = 0;
		_hoops_CICSR.keys = 0;
		_hoops_CICSR.count = 0;
	}
	
	if ((_hoops_IICSR = HI_Activate_Texture((_hoops_RCR alter *)_hoops_SGRA->_hoops_SICSR, &_hoops_CICSR, false))) {
		image = _hoops_IICSR->image;
	}

	if (_hoops_IICSR == null || BIT(_hoops_IICSR->flags, _hoops_AIA)) {
		HD_Standard_Draw_Window(nr, extent);
		return;
	}

	rasters = *(_hoops_AIGH**)image->rasters;


	QImage _hoops_PGPGS(image->width, image->height, QImage::Format_ARGB32);
	QRgb pixel;
	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width ; j++) {
			pixel = qRgba(rasters->r, rasters->g, rasters->b, rasters->a);
			//_hoops_AIR = _hoops_HGPGS(_hoops_PIH[_hoops_HAS*_hoops_CSCR->_hoops_IGAA + _hoops_PPHR + 0], _hoops_PIH[_hoops_HAS*_hoops_CSCR->_hoops_IGAA + _hoops_PPHR + 1], _hoops_PIH[_hoops_HAS*_hoops_CSCR->_hoops_IGAA + _hoops_PPHR + 2], 255);
			_hoops_PGPGS.setPixel(j, i, pixel);
			//_hoops_CSCR._hoops_AGPGS(_hoops_HAS, 1, _hoops_AIR);
			rasters++;
		}
	}
	_hoops_PGPGS = _hoops_PGPGS.scaled(QSize(extent->right - extent->left +1 , extent->top- extent->bottom -1));
	//_hoops_PIAP->_hoops_IRAGS->_hoops_HPAGS->_hoops_IGPGS(_hoops_CGPGS(_hoops_CRRPA->_hoops_RAAP , _hoops_PIAP->_hoops_IRAGS->_hoops_GRGAI->_hoops_CSAGS()._hoops_APPS() - 2 - _hoops_CRRPA->_hoops_SCIA ), _hoops_SGPGS);
	state->d_widget->hp->drawImage(QPointF(0, 0), _hoops_PGPGS);

	


}


local bool  replacement_update (
	Display_Context alter	*dc,
	Activity _hoops_SCISP) {
	Qt_Data alter			*state = QTD(dc);

	state->d_widget->setAttribute(Qt::WA_OutsideWSRange);
	state->d_widget->draw();
	return true;
}

local void
_hoops_RSCSR(_hoops_APARR alter & _hoops_RRCI)
{

	_hoops_SIRGS("get_actions");

	_hoops_RRCI->start_device					= start_device;
	_hoops_RRCI->stop_device						= stop_device;
	_hoops_RRCI->get_physical_info				= get_physical_info;
	_hoops_RRCI->get_outer_window				= get_outer_window;
	_hoops_RRCI->free_outer_window				= free_outer_window;
	_hoops_RRCI->init_picture					= init_picture;
	_hoops_RRCI->finish_picture					= finish_picture;
	_hoops_RRCI->update							= replacement_update; 

	_hoops_RRCI->draw_3d_elliptical_arc          = draw_3d_elliptical_arc;
	_hoops_RRCI->draw_dc_colorized_face	        = draw_dc_colorized_face;
	_hoops_RRCI->draw_dc_colorized_polytriangle	= draw_dc_colorized_polytriangle;
	_hoops_RRCI->draw_dc_colorized_polydot		= draw_dc_colorized_polydot;
	/*_hoops_HPGR->_hoops_GRPGS          = _hoops_GRPGS;*/
	/*_hoops_HPGR->_hoops_RRPGS					= _hoops_RRPGS;*/
	//_hoops_HPGR->_hoops_ARPGS    = _hoops_ARPGS;
	/*_hoops_HPGR->_hoops_PRPGS         = _hoops_PRPGS; */
	_hoops_RRCI->draw_dc_ellipse                 = draw_dc_ellipse; 
	//_hoops_HPGR->_hoops_SRCC					= _hoops_SRCC;
	_hoops_RRCI->draw_dc_polyline				= draw_dc_polyline;
	_hoops_RRCI->draw_dc_polytriangle			= draw_dc_polytriangle;
	/*_hoops_HPGR->_hoops_CIAC				= _hoops_CIAC;*/
	_hoops_RRCI->draw_dc_rgb32_rasters			= draw_dc_rgb32_rasters;
	/*_hoops_HPGR->_hoops_IHRPI					= _hoops_IHRPI;*/
	_hoops_RRCI->draw_window                     = draw_window;

	/*_hoops_HPGR->_hoops_HRPGS					= _hoops_HRPGS;
	_hoops_HPGR->_hoops_CACPC						= _hoops_CACPC;
	_hoops_HPGR->_hoops_SACPC						= _hoops_SACPC;
	_hoops_HPGR->_hoops_HACPC					= _hoops_HACPC; */
}


extern "C" bool HC_CDECL HD_QT_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR);
}


_hoops_HSCSR (_hoops_RSCSR)

#endif /* _hoops_IRPGS */
