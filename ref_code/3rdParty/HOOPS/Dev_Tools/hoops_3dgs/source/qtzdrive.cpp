/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.64 2010-08-04 01:29:43 evan Exp $
 */

#include "hoops.h"
#include "hd_proto.h"

#if !defined(OSX_SYSTEM) || defined(__x86_64__)

extern "C" bool HC_CDECL HD_Quartz_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "quartz");
}

#else /* _hoops_SR'_hoops_ASAR _hoops_GPP _hoops_GSRRI */

#ifdef AGL_DRIVER /* _hoops_GA'_hoops_RA _hoops_AA _hoops_PA _hoops_HCCPR _hoops_SR'_hoops_ASAR _hoops_GGR _hoops_CRPGS */
#ifndef QUARTZ_DRIVER /* _hoops_SR'_hoops_ASAR _hoops_GGR _hoops_CRPGS _hoops_HIH _hoops_GA'_hoops_RA _hoops_HHGC _hoops_PCHAC _hoops_RHPP */

extern "C" bool HC_CDECL HD_Quartz_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "quartz");
}

#else 

/* _hoops_CASRR _hoops_RH _hoops_PCHAC _hoops_RHPP _hoops_IH _hoops_HPHR _hoops_RPP _hoops_HGRC _hoops_PPR _hoops_RPP 
 * _hoops_SR _hoops_GGHP _hoops_ARI _hoops_HPP _hoops_PPRRR _hoops_IIGR _hoops_RH #_hoops_GCIS _hoops_GGR _hoops_CRPGS */

#define _hoops_IASSC		  1L
#define Quartz_LANDSCAPE		(_hoops_IASSC<<12) /* 4096 */


#define _hoops_ACRSC		 256
#define _hoops_SRPGS (1.0f/(float)_hoops_ACRSC)

#undef _hoops_GAPGS
#if 0
#  define _hoops_GAPGS(x) if (qtzdata->fp != null) \
		fprintf (qtzdata->fp, x);
#else
#  define _hoops_GAPGS(x) _hoops_GRSSH(x)
#endif

/*
 * _hoops_PIH _hoops_SGS _hoops_RHGSR _hoops_AGRR _hoops_RHPP _hoops_HCPH
 */
struct QtzData {
	_hoops_RPSGR 			_hoops_PIGRR; /* _hoops_PPCAR _hoops_CCA _hoops_HGPGA, _hoops_PIHA _hoops_RCPS _hoops_SRS */
	CGContextRef	  context;
	Display_Context const *dc;
	float			  _hoops_HAP;

	/* _hoops_RGHR _hoops_IIPR _hoops_IH _hoops_GSPHR */
	FILE alter			*fp;
	bool			_hoops_ICSSC;

	/* _hoops_AGAH _hoops_IPP _hoops_PRCA */
	_hoops_GARRR		_hoops_RAPGS;
	_hoops_GARRR		lr_incarnation;
	_hoops_GARRR		_hoops_RSHH;

	/* _hoops_HPHS _hoops_SIGR _hoops_GGR _hoops_AGR _hoops_IS _hoops_PSCPR _hoops_IIPH _hoops_HIPH _hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH
	 * _hoops_ARP _hoops_CAPR _hoops_GH _hoops_GAR _hoops_IRS _hoops_HSPH _hoops_ISPH _hoops_PPR _hoops_CISA _hoops_GGR _hoops_RH _hoops_AAPGS _hoops_PAPGS */
	DC_Point 		  *_hoops_HAPGS;
	int 				  _hoops_IAPGS, _hoops_CAPGS;
	int 				  *ptcounts;
	int 				  _hoops_SAPGS, _hoops_GPPGS;
	Driver_Color	  _hoops_RPPGS;
	int 				  _hoops_APPGS;

	WindowRef		  window;

	Driver_Color	  _hoops_AARSR;
};


/*
 * _hoops_CIGR _hoops_IS _hoops_GHPHR _hoops_IRS _hoops_PPPGS _hoops_CRS _hoops_HII _hoops_IRS _hoops_CSPH _hoops_PAR _hoops_SCII
 */
#define QTZD(dc)	((QtzData alter *)(dc)->data) /* _hoops_CSPH->_hoops_AISRH _hoops_HRGR _hoops_HGPGA _hoops_RPP _hoops_GRAA-_hoops_IRAP */
#define QTZD_NR(nr)   (QTZD ((nr)->_hoops_SRA))
#define _hoops_HPPGS (0.5522847498f)  /* _hoops_HII _hoops_IHHRA://_hoops_CHHRA._hoops_IPPGS._hoops_CPPGS._hoops_GCHRR/_hoops_SPPGS/_hoops_PRHC/ */
#ifndef _hoops_IAGHA
#  define _hoops_IAGHA	 (3.14159265358979323846264338327950288)
#endif

/*
 * _hoops_PGAA 
 */
local void 
qtz_set_clip(
		QtzData alter *qtzdata,
		Net_Rendition const  &nr)
{

	_hoops_CGRA const &_hoops_SGRA = nr->_hoops_SAIR;
	_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
	
	/* _hoops_ISPR _hoops_ISIS _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR _hoops_PAH _hoops_RSIH _hoops_RIARR */
        if (qtzdata->_hoops_RAPGS == _hoops_SGRA->_hoops_CPA &&
                ((!_hoops_IHCR->_hoops_HCHH && qtzdata->_hoops_RSHH == _hoops_CCC) ||
                  (_hoops_IHCR->_hoops_HCHH && _hoops_IHCR->_hoops_HCHH->_hoops_CPA == qtzdata->_hoops_RSHH)))
                return;

	qtzdata->_hoops_RAPGS = _hoops_SGRA->_hoops_CPA;
	qtzdata->_hoops_RSHH = _hoops_CCC; /* _hoops_GHCA _hoops_SHH _hoops_HIAP _hoops_SPHR */
	CGContextRef context = qtzdata->context;

	/* _hoops_PHIH _hoops_HCISR _hoops_PIAP _hoops_IS _hoops_RH _hoops_PPRRR _hoops_SCH _hoops_CSAP _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_HGCR _hoops_CRIPR _hoops_RPPS */
	CGContextRestoreGState(context);
	qtzdata->lr_incarnation = _hoops_CCC;
	qtzdata->_hoops_AARSR = _hoops_CAHSR::_hoops_SAHSR;
	CGContextSaveGState(context);

	if (_hoops_IHCR->_hoops_HCHH != null) {
		qtzdata->_hoops_RSHH = _hoops_IHCR->_hoops_HCHH->_hoops_CPA;
		_hoops_ASHH const *_hoops_CRAIR = _hoops_IHCR->_hoops_HCHH->_hoops_PSHH;
		
		do {		

			if (!BIT (_hoops_CRAIR->flags, _hoops_RHIH)) {

				// _hoops_SRPR _hoops_GAPR _hoops_HGPS
			}

			else {

				CGContextBeginPath(context);			
				if (qtzdata->_hoops_PIGRR == _hoops_PPSGR) {
					float l = _hoops_SGRA->_hoops_PHRA.left;
					float r = _hoops_SGRA->_hoops_PHRA.right;
					float b = _hoops_SGRA->_hoops_PHRA.bottom;
					float t = _hoops_SGRA->_hoops_PHRA.top;
	
					/* _hoops_HGASI _hoops_IH _hoops_IRS _hoops_CAGRH _hoops_GGR _hoops_PCHAC _hoops_HICAA: 
				   	_hoops_PGSA 2 _hoops_RISS _hoops_HIPH _hoops_HPGR _hoops_RH _hoops_GRPC _hoops_IIGR _hoops_ISCP _hoops_GCHRR _hoops_PHGSP _hoops_GGR
				   	_hoops_AGR _hoops_IS _hoops_IRCH _hoops_RH _hoops_IASC _hoops_AHCRR _hoops_IIGR _hoops_ISCP _hoops_HSPH _hoops_CRAA */
					CGContextAddRect(context, CGRectMake(l, b, 1, 1));
					CGContextAddRect(context, CGRectMake(r, t, 1, 1));
				}
	
				CGContextMoveToPoint   (context, _hoops_CRAIR->points[0].x, _hoops_CRAIR->points[0].y);
				for (int i = 1 ; i < _hoops_CRAIR->count ; i++)
					CGContextAddLineToPoint (context, _hoops_CRAIR->points[i].x, _hoops_CRAIR->points[i].y);
				CGContextClosePath(context);
			}

		} while ((_hoops_CRAIR = _hoops_CRAIR->next) != null);

		CGContextClip(context);	
	}

	/* _hoops_ARP _hoops_GH _hoops_ACIPR _hoops_CIHH _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_GA'_hoops_RA _hoops_SSHSH _hoops_GRHCP _hoops_ISCP _hoops_ACGP _hoops_CCAC */
	CGContextBeginPath(context);
		CGContextMoveToPoint   (context, _hoops_SGRA->_hoops_PHRA.left, _hoops_SGRA->_hoops_PHRA.bottom);
		CGContextAddLineToPoint(context, _hoops_SGRA->_hoops_PHRA.right+1, _hoops_SGRA->_hoops_PHRA.bottom);
		CGContextAddLineToPoint(context, _hoops_SGRA->_hoops_PHRA.right+1, _hoops_SGRA->_hoops_PHRA.top+1);
		CGContextAddLineToPoint(context, _hoops_SGRA->_hoops_PHRA.left, _hoops_SGRA->_hoops_PHRA.top+1);
	CGContextClosePath(context);
	CGContextClip(context);	

}

#if 0
#define _hoops_SHASH 0.15f

/* _hoops_ACIPR _hoops_HSPH _hoops_IS _hoops_HIPH, _hoops_PSCR _hoops_PGSA _hoops_APGR _hoops_HPGR _hoops_RPIHR _hoops_PPAHP */
local void qtz_flush_patterned_polytriangles (
		Net_Rendition const  &nr)
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	_hoops_CGRA const &_hoops_SGRA = nr->_hoops_SAIR;
	float f, _hoops_IGHCP, l, r, b, t, w, h;
	DC_Point const *points = qtzdata->_hoops_HAPGS;
	int	*_hoops_ICI = qtzdata->ptcounts;
	int count, _hoops_RRC;
	Driver_Color const *color;

	l = _hoops_SGRA->_hoops_PHRA.left;
	r = _hoops_SGRA->_hoops_PHRA.right;
	b = _hoops_SGRA->_hoops_PHRA.bottom;
	t = _hoops_SGRA->_hoops_PHRA.top;
	w = r - l;
	h = t - b;
	CGContextSaveGState(context);
	CGContextBeginPath(context);
		if (qtzdata->_hoops_PIGRR == _hoops_PPSGR) {
			/* _hoops_HGASI _hoops_IH _hoops_IRS _hoops_CAGRH _hoops_GGR _hoops_PCHAC _hoops_HICAA: 
			   _hoops_PGSA 2 _hoops_RISS _hoops_HIPH _hoops_HPGR _hoops_RH _hoops_GRPC _hoops_IIGR _hoops_ISCP _hoops_GCHRR _hoops_PHGSP _hoops_GGR
			   _hoops_AGR _hoops_IS _hoops_IRCH _hoops_RH _hoops_IASC _hoops_AHCRR _hoops_IIGR _hoops_ISCP _hoops_HSPH _hoops_CRAA */
			CGCo ntextMoveToPoint (context, r+2, b);
			CGContextAddLineToPoint(context, r+1, b);
			CGContextAddLineToPoint(context, r+1, b-1);
			CGContextClosePath(context);
			CGContextMoveToPoint   (context, l-1, t+1);
			CGContextAddLineToPoint(context, l, t+1);
			CGContextAddLineToPoint(context, l, t+2);
			CGContextClosePath(context);
		}
		end = _hoops_ICI + qtzdata->_hoops_GPPGS;
		while (_hoops_ICI < end) {
			count = *_hoops_ICI++;
			_hoops_ICHC(count, _hoops_RRC, 3);
			while (count--) {
				CGContextMoveToPoint   (context, points[0].x, points[0].y);
				CGContextAddLineToPoint(context, points[1].x, points[1].y);
				CGContextAddLineToPoint(context, points[2].x, points[2].y);
				CGContextClosePath(context);
				points += _hoops_RRC;
			}
		}
	CGContextClip(context);
	/* _hoops_HA _hoops_PGSA _hoops_RH _hoops_IIPH _hoops_APGR _hoops_HPGR _hoops_RPIHR _hoops_PPAHP */
	_hoops_IGHCP = qtzdata->_hoops_HAP * _hoops_SHASH;
	CGContextBeginPath(context);
	switch (nr->_hoops_IHA->pattern) {
		case 0: /* _hoops_CPCHR _hoops_PPR _hoops_GHPGS */
			_hoops_IGHCP *= 1.41f; 
			for (f = l-h ; f < r ; f +=  _hoops_IGHCP) {
				CGContextMoveToPoint   (context, f, b);
				CGContextAddLineToPoint(context, f+h, t);
			}
			for (f = l ; f-h < r ; f += _hoops_IGHCP) {
				CGContextMoveToPoint   (context, f, b);
				CGContextAddLineToPoint(context, f-h, t);
			} 
			break;

		case 1: /* _hoops_CPCHR _hoops_HAIAH */
			_hoops_IGHCP *= 1.41f;
			for (f = l-h ; f < r ; f += _hoops_IGHCP) {
				CGContextMoveToPoint   (context, f, b);
				CGContextAddLineToPoint(context, f+h, t);
			}
			break;

		case 2: /* _hoops_GHPGS */
			_hoops_IGHCP *= 1.41f;
			for (f = l ; f-h < r ; f += _hoops_IGHCP) {
				CGContextMoveToPoint   (context, f, b);
				CGContextAddLineToPoint(context, f-h, t);
			} 
			break;

		case 3: /* _hoops_IRPHR */
			for (f = l ; f < r ; f += _hoops_IGHCP) {
				CGContextMoveToPoint   (context, f, b);
				CGContextAddLineToPoint(context, f, t);
			} 
			break;

		case 4: /* _hoops_IRGGA & _hoops_IRPHR */
			for (f = b ; f < t ; f += _hoops_IGHCP) {
				CGContextMoveToPoint   (context, l, f);
				CGContextAddLineToPoint(context, r, f);
			} 
			for (f = l ; f < r ; f += _hoops_IGHCP) {
				CGContextMoveToPoint   (context, f, b);
				CGContextAddLineToPoint(context, f, t);
			} 
			break;

		default:
		case 5: /* _hoops_IRGGA */
			for (f = b ; f < t ; f += _hoops_IGHCP) {
				CGContextMoveToPoint   (context, l, f);
				CGContextAddLineToPoint(context, r, f);
			} 
	}
	color = &nr->_hoops_IHA->contrast_color;
	CGContextSetRGBStrokeColor(context, 
		_hoops_SRPGS * color->_hoops_HRIR.r,
		_hoops_SRPGS * color->_hoops_HRIR.g,
		_hoops_SRPGS * color->_hoops_HRIR.b,
		1 
	);
	CGContextStrokePath(context);
	CGContextRestoreGState(context);

	qtzdata->_hoops_CAPGS = 0;
	qtzdata->_hoops_GPPGS = 0;
}


local void qtz_append_patterned_polytriangle (
		Net_Rendition const  &nr,
		int	count,
		DC_Point const   *points) 
{
  QtzData alter *qtzdata = QTZD_NR (nr);
	int pcount;

	if (qtzdata->_hoops_IAPGS == 0) {
		qtzdata->_hoops_IAPGS = 4096;
		qtzdata->_hoops_SAPGS = 1024;
		ALLOC_ARRAY(qtzdata->_hoops_HAPGS, qtzdata->_hoops_IAPGS, Point);
		ALLOC_ARRAY(qtzdata->ptcounts, qtzdata->_hoops_SAPGS, int);
	}
	if (qtzdata->_hoops_CAPGS != 0) {
		if (qtzdata->_hoops_APPGS != nr->_hoops_IHA->pattern ||
			qtzdata->_hoops_RPPGS != nr->_hoops_IHA->contrast_color)
			qtz_flush_patterned_polytriangles(nr);
		if (count < 0)
			pcount = -count * 3;
		else
			pcount = count + 2;
		if (qtzdata->_hoops_GPPGS >= qtzdata->_hoops_SAPGS ||
			qtzdata->_hoops_CAPGS + pcount >= _hoops_IAPGS)
			qtz_flush_patterned_polytriangles(nr);
	}
	qtzdata->ptcounts[ qtzdata->_hoops_GPPGS++ ] = count;
	COPY_MEMORY(points,
				 pcount * sizeof(DC_Point),
				 &qtzdata->_hoops_HAPGS[ qtzdata->_hoops_CAPGS ]);
	qtzdata->_hoops_CAPGS += pcount;
}
#endif

/*
 * _hoops_SRAC
 */
local void qtz_draw_window (
		Net_Rendition const	  &nr,
		Int_Rectangle const		*extent) 
	{
	QtzData alter 	  *qtzdata = QTZD_NR (nr);
	CGContextRef		  context = qtzdata->context;
	_hoops_CGRA const &_hoops_SGRA = nr->_hoops_SAIR;
	_hoops_CPAIR		_hoops_CICSR;
	Image const		*image = null;
	_hoops_RCR		  *_hoops_IICSR = null;
	CGColorSpaceRef		_hoops_RHPGS;
	CGImageRef		  _hoops_AHPGS;
	CGDataProviderRef 	providerRef;
	int			  l, b, w, h, bitsPerComponent, _hoops_PHPGS, rowBytes;

	_hoops_GAPGS("qtz_draw_window\n");
	if (_hoops_SGRA->_hoops_SICSR == null) {
		HD_Standard_Draw_Window(nr, extent); /* _hoops_IIS _hoops_CSPH _hoops_ARRGR _hoops_RGHH _hoops_SCH */
		goto _hoops_HPAGR;
	}
	qtz_set_clip(qtzdata, nr);

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

	if (image->format != _hoops_CSGSP &&
		image->format != Image_RGBA32) {
		HD_Standard_Draw_Window(nr, extent); /* _hoops_IIS _hoops_CSPH _hoops_ARRGR _hoops_RGHH _hoops_SCH */
		goto _hoops_HPAGR;
	}


	_hoops_RHPGS = CGColorSpaceCreateDeviceRGB();
	bitsPerComponent = 8;
	_hoops_PHPGS = 32;
	rowBytes = image->row_bytes;
	rowBytes = image->width * 4;

	providerRef = CGDataProviderCreateWithData(
			NULL, 
			image->_hoops_PHGH, 
			rowBytes * image->height, 
			NULL);
	_hoops_AHPGS = CGImageCreate(
			image->width, 
			image->height, 
			bitsPerComponent, 
			_hoops_PHPGS, 
			rowBytes, 
			_hoops_RHPGS, 
			kCGImageAlphaNoneSkipLast, 
			providerRef, 
			NULL /* _hoops_HHPGS */, 
			0 /* _hoops_IHPGS */, 
			kCGRenderingIntentDefault 
	);
	l = extent->left;
	b = extent->bottom;
	w = extent->right - extent->left + 1;
	h = extent->top - extent->bottom + 1;
	CGContextDrawImage (context, CGRectMake(l, b, w, h), _hoops_AHPGS); 
	CFRelease(_hoops_RHPGS);
	CFRelease(providerRef);
	CFRelease(_hoops_AHPGS);

	_hoops_HPAGR:
	if (_hoops_IICSR)
		_hoops_HPRH(_hoops_IICSR);
	}


/*
 * _hoops_PGAA 
 */
local bool 
qtz_set_line_attributes(
		QtzData alter *qtzdata,
		Net_Rendition const  &nr)
{
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	CGContextRef context;
	Driver_Color const *color;
	float weight;
	float *lengths;
	int i, count;
	CGLineJoin _hoops_SAGAI = (CGLineJoin)-1;
	CGLineCap cap = (CGLineCap)-1;

/*
	_hoops_RPP (_hoops_PPPGS->_hoops_CHPGS == _hoops_HGICP->_hoops_HSHR)
		_hoops_ASRC _hoops_IHPR;
*/
	context = qtzdata->context;

	/* _hoops_SR _hoops_GA'_hoops_RA _hoops_RGHH _hoops_GII _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_GGAIA _hoops_III, _hoops_IIGSH _hoops_IGIR _hoops_PSPA
	 * _hoops_PAR _hoops_RPHH _hoops_III _hoops_PAIA */
	if (BIT(_hoops_HC->flags, _hoops_SRPI) || 
		ANYBIT(_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS)) {
		return false;
	}

	if ((weight = _hoops_HC->weight) < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);

	switch (_hoops_HC->style & LCAP_MASK) {
		case LCAP_BUTT:
			cap = kCGLineCapButt;
		break;
		case LCAP_ROUND:
			cap = kCGLineCapRound;
		break;
		case LCAP_SQUARE:
			cap = kCGLineCapSquare;
		break;
	}

	switch (_hoops_HC->style & LJOIN_MASK) {
		case LJOIN_MITER:
			_hoops_SAGAI = kCGLineJoinMiter;
		break;
		case LJOIN_ROUND:
			_hoops_SAGAI = kCGLineJoinRound;
		break;
		case LJOIN_BEVEL:
			_hoops_SAGAI = kCGLineJoinBevel;
		break;
	}

	if (weight > 2 && 
		!BIT(_hoops_HC->line_style->flags, LSF_SOLID) &&
		cap != kCGLineCapButt) {
		return false;
	}
	/* _hoops_HAR _hoops_ICIC _hoops_IS _hoops_ARP _hoops_PIAP _hoops_ARPP _hoops_PAR _hoops_CAH _hoops_RAS _hoops_RGR _hoops_PPSR */
	qtzdata->lr_incarnation = _hoops_HC->_hoops_CPA;

	CGContextSetLineWidth(context, weight);
	CGContextSetLineCap(context, cap);
	CGContextSetLineJoin(context, _hoops_SAGAI);

	if (!BIT(_hoops_HC->line_style->flags, LSF_SOLID)) {
		count = _hoops_HC->line_style->_hoops_GHISR[0]._hoops_RHISR;
		ALLOC_ARRAY (lengths, count, float);
		for (i = 0 ; i < count ; i++)
			lengths[i] = (float) _hoops_HC->line_style->_hoops_GHISR[0].pattern[i];
		CGContextSetLineDash(context, 0, lengths, count);
		FREE_ARRAY (lengths, count, float);
	}
	else {
		CGContextSetLineDash(context, 0, null, 0);
	}

	color = &_hoops_HC->color;
	CGContextSetRGBStrokeColor(context, 
		_hoops_SRPGS * color->_hoops_HRIR.r,
		_hoops_SRPGS * color->_hoops_HRIR.g,
		_hoops_SRPGS * color->_hoops_HRIR.b,
		1 
	);
	return true;

} /* _hoops_RSGR _hoops_API _hoops_SHPGS _hoops_ARP _hoops_III _hoops_AIRC */


/*
 * _hoops_SRAC
 */
local void qtz_draw_dc_polyline (
		Net_Rendition const & nr,
		int	count,
		DC_Point const *points) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef context = qtzdata->context;
	int i;

	_hoops_GAPGS("qtz_draw_dc_polyline\n");
	qtz_set_clip(qtzdata, nr);
	if (!qtz_set_line_attributes(qtzdata, nr)) {
		HD_Std_DC_Polyline(nr, count, points);
		return;
	}

	CGContextBeginPath(context);
	CGContextMoveToPoint   (context, points[0].x + 0.5f, points[0].y + 0.5f);
	for (i = 1 ; i < count ; i++)
		CGContextAddLineToPoint(context, points[i].x + 0.5f, points[i].y + 0.5f);
	CGContextStrokePath(context);
}


/*
 * _hoops_SRAC
 */
local void qtz_draw_dc_elliptical_arc (
		Net_Rendition const  &nr,
		DC_Point const   *center,
		DC_Point const   *radii,
		float 			start,
		float 			end) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef	context = qtzdata->context;
	float w, h, _hoops_SHGCR;

	_hoops_GAPGS("qtz_draw_dc_elliptical_arc\n");
	qtz_set_clip(qtzdata, nr);
	if (!qtz_set_line_attributes(qtzdata, nr)) {
		HD_Std_DC_Elliptical_Arc(nr, center, radii, start, end);
		return;
	}
	w = radii->x;
	h = radii->y;
	_hoops_SHGCR = (w + h) / 2;
	start *= 2.0f * _hoops_IAGHA;
	end *= 2.0f * _hoops_IAGHA,
	CGContextSaveGState(context);
	CGContextScaleCTM(context, w/_hoops_SHGCR, h/_hoops_SHGCR);
	CGContextTranslateCTM(context, center->x*_hoops_SHGCR/w, center->y*_hoops_SHGCR/h);
	CGContextBeginPath(context);
		CGContextAddArc(
			context,
			0, 0,
			_hoops_SHGCR,
			start, end,
			0
		);
	CGContextStrokePath(context);
	CGContextRestoreGState(context);
}


/*
 * _hoops_SRAC
 */
local void qtz_draw_dc_outline_ellipse (
		Net_Rendition const  &nr,
		DC_Point const   *center,
		DC_Point const   *radii) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef	context = qtzdata->context;

	_hoops_GAPGS("qtz_draw_dc_outline_ellipse\n");
	qtz_set_clip(qtzdata, nr);
	if (!qtz_set_line_attributes(qtzdata, nr)) {
		HD_Std_DC_Outline_Ellipse(nr, center, radii);
		return;
	}

	CGContextBeginPath(context);
		CGContextMoveToPoint  (context, center->x + radii->x, center->y);
		CGContextAddCurveToPoint(context, 
				center->x + radii->x, center->y + _hoops_HPPGS*radii->y,
				center->x + _hoops_HPPGS*radii->x, center->y + radii->y,
				center->x, center->y + radii->y );
		CGContextAddCurveToPoint(context, 
				center->x - _hoops_HPPGS*radii->x, center->y + radii->y,
				center->x - radii->x, center->y + _hoops_HPPGS*radii->y,
				center->x - radii->x, center->y  );
		CGContextAddCurveToPoint(context, 
				center->x - radii->x, center->y - _hoops_HPPGS*radii->y,
				center->x - _hoops_HPPGS*radii->x, center->y - radii->y,
				center->x, center->y - radii->y );
		CGContextAddCurveToPoint(context, 
				center->x + _hoops_HPPGS*radii->x, center->y - radii->y,
				center->x + radii->x, center->y - _hoops_HPPGS*radii->y,
				center->x + radii->x, center->y);
	CGContextClosePath(context);
	CGContextStrokePath(context);
}


/*
 * _hoops_SRAC
 */
local void qtz_draw_dc_ellipse (
		Net_Rendition const  &nr,
		DC_Point const   *center,
		DC_Point const   *radii) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef	context = qtzdata->context;
	Driver_Color const *color;

	_hoops_GAPGS("qtz_draw_dc_ellipse\n");
	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Ellipse(nr, center, radii);
		return;
	}
	qtz_set_clip(qtzdata, nr);

	color = &nr->_hoops_IHA->color;
	if (qtzdata->_hoops_AARSR != *color) {
		CGContextSetRGBFillColor(context, 
			_hoops_SRPGS * color->_hoops_HRIR.r,
			_hoops_SRPGS * color->_hoops_HRIR.g,
			_hoops_SRPGS * color->_hoops_HRIR.b,
			1);
		qtzdata->_hoops_AARSR = *color;
	}

	CGContextBeginPath(context);
		CGContextMoveToPoint  (context, center->x + radii->x, center->y);
		CGContextAddCurveToPoint(context, 
				center->x + radii->x, center->y + _hoops_HPPGS*radii->y,
				center->x + _hoops_HPPGS*radii->x, center->y + radii->y,
				center->x, center->y + radii->y );
		CGContextAddCurveToPoint(context, 
				center->x - _hoops_HPPGS*radii->x, center->y + radii->y,
				center->x - radii->x, center->y + _hoops_HPPGS*radii->y,
				center->x - radii->x, center->y  );
		CGContextAddCurveToPoint(context, 
				center->x - radii->x, center->y - _hoops_HPPGS*radii->y,
				center->x - _hoops_HPPGS*radii->x, center->y - radii->y,
				center->x, center->y - radii->y );
		CGContextAddCurveToPoint(context, 
				center->x + _hoops_HPPGS*radii->x, center->y - radii->y,
				center->x + radii->x, center->y - _hoops_HPPGS*radii->y,
				center->x + radii->x, center->y);
	CGContextClosePath(context);
	CGContextFillPath(context);
}


/*
 * _hoops_SRAC
 */
local void qtz_draw_dc_face (
		Net_Rendition const  &nr,
		int			count,
		DC_Point const   *points) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef	context = qtzdata->context;
	Driver_Color const *color;
	int i;

	_hoops_GAPGS("qtz_draw_dc_face\n");
	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Face(nr, count, points);
		return;
	}
	qtz_set_clip(qtzdata, nr);

	color = &nr->_hoops_IHA->color;
	if (qtzdata->_hoops_AARSR != *color) {
		CGContextSetRGBFillColor(context, 
			_hoops_SRPGS * color->_hoops_HRIR.r,
			_hoops_SRPGS * color->_hoops_HRIR.g,
			_hoops_SRPGS * color->_hoops_HRIR.b,
			1);
		qtzdata->_hoops_AARSR = *color;
	}

	CGContextBeginPath(context);
		CGContextMoveToPoint   (context, points[0].x, points[0].y);
		for (i = 1 ; i < count ; i++)
			CGContextAddLineToPoint(context, points[i].x, points[i].y);
	CGContextClosePath(context);
	CGContextFillPath(context);
}


/*
 * _hoops_SRAC
 */
local void qtz_draw_dc_colorized_face (
		Net_Rendition const & nr,
		int 		  count,
		DC_Point const	*points,
		RGBAS32 const	*color) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef	context = qtzdata->context;
	int i;

	_hoops_GAPGS("qtz_draw_dc_colorized_face\n");
	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Colorized_Face(nr, count, points, color);
		return;
	}
	qtz_set_clip(qtzdata, nr);

	CGContextSetRGBFillColor(context, 
		_hoops_SRPGS * color->r,
		_hoops_SRPGS * color->g,
		_hoops_SRPGS * color->b,
		1);

	CGContextBeginPath(context);
		CGContextMoveToPoint   (context, points[0].x, points[0].y);
		for (i = 1 ; i < count ; i++)
			CGContextAddLineToPoint(context, points[i].x, points[i].y);
	CGContextClosePath(context);
	CGContextFillPath(context);
}


/*
 * _hoops_SRAC
 */
local void qtz_draw_dc_rectangle (
		Net_Rendition const  &nr,
		int			left,
		int			right,
		int			bottom,
		int			top) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef	context = qtzdata->context;
	Driver_Color const *color;

	_hoops_GAPGS("qtz_draw_dc_rectangle\n");
	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Rectangle (nr, left, right, bottom, top);
		return;
	}
	qtz_set_clip(qtzdata, nr);

	color = &nr->_hoops_IHA->color;
	if (qtzdata->_hoops_AARSR != *color) {
		CGContextSetRGBFillColor(context, 
			_hoops_SRPGS * color->_hoops_HRIR.r,
			_hoops_SRPGS * color->_hoops_HRIR.g,
			_hoops_SRPGS * color->_hoops_HRIR.b,
			1);
		qtzdata->_hoops_AARSR = *color;
	}

	CGContextBeginPath(context);
		CGContextMoveToPoint   (context, left, bottom);
		CGContextAddLineToPoint(context, right, bottom);
		CGContextAddLineToPoint(context, right, top);
		CGContextAddLineToPoint(context, left, top);
	CGContextClosePath(context);
	CGContextFillPath(context);

}


/*
 * _hoops_SRAC
 * _hoops_RPR < 0 _hoops_AGSR _hoops_GIPGS _hoops_HIPH
 * _hoops_RPR > 0 _hoops_AGSR _hoops_RIPGS _hoops_RIHA _hoops_CRHH
 */
local void qtz_draw_dc_polytriangle (
		Net_Rendition const  &nr,
		int	count,
		DC_Point const   *points) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef	context = qtzdata->context;
	Driver_Color const *color;
	int _hoops_RRC;

	_hoops_GAPGS("qtz_draw_dc_triangle\n");
	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Polytriangle(nr, count, points);
		return;
	}
	qtz_set_clip(qtzdata, nr);

	color = &nr->_hoops_IHA->color;
	if (qtzdata->_hoops_AARSR != *color) {
		CGContextSetRGBFillColor(context, 
			_hoops_SRPGS * color->_hoops_HRIR.r,
			_hoops_SRPGS * color->_hoops_HRIR.g,
			_hoops_SRPGS * color->_hoops_HRIR.b,
			1);
		qtzdata->_hoops_AARSR = *color;
	}

	_hoops_ICHC(count, _hoops_RRC, 3);
	while (count-- > 0) {
		CGContextBeginPath(context);
			CGContextMoveToPoint   (context, points[0].x, points[0].y);
			CGContextAddLineToPoint(context, points[1].x, points[1].y);
			CGContextAddLineToPoint(context, points[2].x, points[2].y);
		CGContextClosePath(context);
		CGContextFillPath(context);
		points += _hoops_RRC;
	}
#if 0
	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		qtz_append_patterned_polytriangle(nr, _hoops_CRHC, _hoops_SRHC);
	}
#endif
}



/*
 * _hoops_SRAC
 */
local void qtz_draw_dc_colorized_polytriangle (
		Net_Rendition const  &nr,
		int	count,
		DC_Point const   *points,
		RGBAS32 const	  *color,
		bool single) 
{
  QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef	context = qtzdata->context;
	int _hoops_RRC;

	_hoops_GAPGS("qtz_draw_dc_colorized_triangle\n");
	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Colorized_Polytris (nr, count, points, color, single);
		return;
	}
	qtz_set_clip(qtzdata, nr);

	_hoops_ICHC(count, _hoops_RRC, 3);
	while (count-- > 0) {
		CGContextSetRGBFillColor(context, 
			_hoops_SRPGS * color->r,
			_hoops_SRPGS * color->g,
			_hoops_SRPGS * color->b,
			1);
	
		CGContextBeginPath(context);
			CGContextMoveToPoint   (context, points[0].x, points[0].y);
			CGContextAddLineToPoint(context, points[1].x, points[1].y);
			CGContextAddLineToPoint(context, points[2].x, points[2].y);
		CGContextClosePath(context);
		CGContextFillPath(context);
		points += _hoops_RRC;
		if (!single)
			color++;
	}
	qtzdata->_hoops_AARSR = _hoops_CAHSR::_hoops_SAHSR;
}


#if 0 /* _hoops_RGR _hoops_CCHRA _hoops_HRGR _hoops_PAHH _hoops_AIPGS */
/*
 * _hoops_SRAC
 */
local void qtz_draw_dc_gouraud_triangle (
		Net_Rendition const  &nr,
		DC_Point const	*points,
		RGBAS32 const	  *colors) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef	context = qtzdata->context;

	_hoops_GAPGS("qtz_draw_dc_gouraud_triangle\n");
	qtz_set_clip(qtzdata, nr);

	/* _hoops_ASIGA _hoops_RGAR _hoops_ARH _hoops_SPR _hoops_IIGR _hoops_RH 3 _hoops_PSHA!!! */
	CGContextSetRGBFillColor(context, 
		_hoops_SRPGS * colors->r,
		_hoops_SRPGS * colors->g,
		_hoops_SRPGS * colors->b,
		1);
	qtzdata->_hoops_AARSR = _hoops_CAHSR::_hoops_SAHSR;
	CGContextBeginPath(context);
		CGContextMoveToPoint   (context, points[0].x, points[0].y);
		CGContextAddLineToPoint(context, points[1].x, points[1].y);
		CGContextAddLineToPoint(context, points[2].x, points[2].y);
	CGContextClosePath(context);
	CGContextFillPath(context);
}
#endif


/*
 * _hoops_SRAC
 */
local void qtz_draw_dc_polydot (
		Net_Rendition const  &nr,
		int	count,
		DC_Point const   *where) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef	context = qtzdata->context;
	Driver_Color const *color;

	_hoops_GAPGS("qtz_draw_dc_dot\n");
	qtz_set_clip(qtzdata, nr);

	color = &nr->_hoops_AHP->color;
	if (qtzdata->_hoops_AARSR != *color) {
		CGContextSetRGBFillColor(context, 
			_hoops_SRPGS * color->_hoops_HRIR.r,
			_hoops_SRPGS * color->_hoops_HRIR.g,
			_hoops_SRPGS * color->_hoops_HRIR.b,
			1);
		qtzdata->_hoops_AARSR = *color;
	}

	while (count-- > 0) {
		CGContextBeginPath(context);
			CGContextMoveToPoint   (context, where->x, where->y);
			CGContextAddLineToPoint(context, where->x+1, where->y);
			CGContextAddLineToPoint(context, where->x+1, where->y+1);
			CGContextAddLineToPoint(context, where->x, where->y+1);
		CGContextClosePath(context);
		CGContextFillPath(context);
		where++;
	}
}


/*
 * _hoops_SRAC
 */
local void qtz_draw_dc_rgb32_rasters (
		Net_Rendition const  &nr,
		DC_Point const 	  *start,
		DC_Point const 	  *end,
		int						row_bytes,
		RGBAS32 const			*rasters) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);
	CGContextRef	context = qtzdata->context;
	RGBAS32	  const *color;
	int i, j, width, height;
	DC_Point where;

	_hoops_GAPGS("qtz_draw_dc_rgb32_rasters\n");
	qtz_set_clip(qtzdata, nr);

	width = (int)end->x - (int)start->x + 1;
	height = (int)end->y - (int)start->y + 1;
	color = rasters;	
	where.x = start->x;
	where.y = start->y;
	for (j = 0 ; j < height ; j++) {
		for (i = 0 ; i < width ; i++) {
			CGContextSetRGBFillColor(context, 
				_hoops_SRPGS * color->r,
				_hoops_SRPGS * color->g,
				_hoops_SRPGS * color->b,
				1);

			CGContextBeginPath(context);
				CGContextMoveToPoint   (context, where.x, where.y);
				CGContextAddLineToPoint(context, where.x+1, where.y);
				CGContextAddLineToPoint(context, where.x+1, where.y+1);
				CGContextAddLineToPoint(context, where.x, where.y+1);
			CGContextClosePath(context);
			CGContextFillPath(context);

			color++;
			where.x += 1;
		}
		where.x = start->x;
		where.y += 1;
	}
	qtzdata->_hoops_AARSR = _hoops_CAHSR::_hoops_SAHSR;	
}


/*
 * _hoops_SRAC
 */
local void qtz_init_update (
		Display_Context const *dc) 
{
	QtzData alter 	*qtzdata = QTZD (dc);

	_hoops_GAPGS("init_update\n");

	if (qtzdata->_hoops_PIGRR == _hoops_PPSGR)
		init_update(dc);	 /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
}


/*
 * _hoops_SRAC
 */
local void qtz_finish_update (
		Display_Context const *dc) 
{
	QtzData alter *qtzdata = QTZD (dc);

	_hoops_GAPGS("finish_update\n");

	if (qtzdata->_hoops_PIGRR == _hoops_PPSGR)
		finish_update(dc);   /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
}


/*
 * _hoops_SRAC
 */
local void qtz_init_picture (
		Net_Rendition const  &nr) 
{
	Display_Context const	  *dc = nr->_hoops_SRA;
	QtzData alter *qtzdata = QTZD_NR (nr);

	if (!BIT(dc->flags, _hoops_SAISR)) return;

	_hoops_GAPGS("qtz_init_picture\n");

	if (qtzdata->_hoops_PIGRR == _hoops_PPSGR)
		init_picture(nr);   /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
}


/*
 * _hoops_SRAC
 */
local void qtz_finish_picture (
		Net_Rendition const  &nr,
		bool		swap_buffers) 
{
	Display_Context const	*dc = nr->_hoops_SRA;
	QtzData alter *qtzdata = QTZD_NR (nr);

	UNREFERENCED (swap_buffers);

	if (!BIT(dc->flags, _hoops_SAISR)) 
		return;

	_hoops_GAPGS("qtz_finish_picture\n");

	if (qtzdata->_hoops_PIGRR == _hoops_PPSGR)
		finish_picture(nr, swap_buffers);   /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
}


/*
 * _hoops_SRAC
 */
local POINTER_SIZED_INT qtz_get_outer_window (
		Display_Context const	  *_hoops_SAGRH) 
{
	Display_Context alter * dc = (Display_Context alter *) _hoops_SAGRH;
	QtzData alter *qtzdata = QTZD (dc);
	POINTER_SIZED_INT retval = 0L;

	_hoops_GAPGS("get_outer_window\n");

	switch (qtzdata->_hoops_PIGRR) {

		case DCT_IMAGE: {
			HE_ERROR (HEC_QUARTZ_DRIVER, HES_CANNOT_CREATE_WINDOW, 
					"Unable to Create a Window");
			return false;
		} break;

		case _hoops_PPSGR: {
			/* _hoops_RGR _hoops_ARAS-_hoops_GHIR _hoops_RPGP _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR _hoops_HS _hoops_PCHAC _hoops_HICAA _hoops_HHPA 
			_hoops_HRGR _hoops_IIAC _hoops_SSRR _hoops_HPP _hoops_RH "_hoops_PIPGS" _hoops_IGRI _hoops_ARP _hoops_GPP _hoops_RH _hoops_HIPGS */
			if (CGGLContextCreate) {
				CGSize size;
				OGLData alter *_hoops_CSRGR = OGLD (dc);
	
				retval = get_outer_window(_hoops_SAGRH); /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
				dc->_hoops_PGCC._hoops_HASHP = 0;
				if (dc->_hoops_PGCC._hoops_HASHP > 0) 
					dc->flags &= ~_hoops_AASHP;
				else 
					dc->flags |= _hoops_AASHP;
				size.width = dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left + 1;
				size.height = dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom + 1;
				qtzdata->context = CGGLContextCreate (
								_hoops_CSRGR->curr_AGLContext,
								size,
								null); 
			}
			else {
				HE_ERROR (HEC_QUARTZ_DRIVER, HES_CANNOT_CREATE_WINDOW, 
						"quartz standalone windows require MacOS 10.3 or later");
				return false;
			}
		} break;

		case _hoops_HPSGR: {
			float scale;
			CGContextRef context = qtzdata->context;

			scale = 72.0f / qtzdata->_hoops_HAP;
			CGContextScaleCTM(context, scale, scale);
			if (dc->options._hoops_ARPSR) {
				CGContextTranslateCTM(
					qtzdata->context, 
					dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left,
					0);
				CGContextRotateCTM(qtzdata->context, _hoops_PCSR(90));
			}
			HD_Resize_Subscreen (dc, true,
								 0, dc->_hoops_PGCC._hoops_PRPSR.x, 
								 0, dc->_hoops_PGCC._hoops_PRPSR.y);

		} break;
	}
	CGContextSaveGState(qtzdata->context);
	return retval;

} /* _hoops_RSGR _hoops_API '_hoops_HGCR _hoops_CRIPR _hoops_RPPS' */


/*
 * _hoops_SRAC
 */
local void qtz_free_outer_window (
		Display_Context const	  *dc) 
{
	QtzData alter *qtzdata = QTZD (dc);

	_hoops_GAPGS("qtz_free_outer_window\n");

	if (qtzdata->_hoops_PIGRR == _hoops_PPSGR || qtzdata->_hoops_PIGRR == DCT_IMAGE) {
	  DisposeWindow (qtzdata->window);
	  qtzdata->window = null;
	}

	if (qtzdata->_hoops_PIGRR == _hoops_PPSGR)
		free_outer_window(dc);   /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
}


/*
 * _hoops_SRAC
 */
local void qtz_resize_outer_window (
		Display_Context const	  *dc) 
{
	QtzData alter 	*qtzdata = QTZD (dc);

	_hoops_GAPGS("qtz_resize_outer_window\n");

	if (qtzdata->_hoops_PIGRR == _hoops_PPSGR)
		_hoops_RSCSP(dc); /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
}


/*
 * _hoops_SRAC
 * _hoops_RPP _hoops_GHGPR _hoops_RHGPR, _hoops_RGR _hoops_PIHA _hoops_SHH _hoops_PIGS _hoops_ARPP _hoops_RH _hoops_GGSHR _hoops_PSCA
 */
local bool qtz_snapshot(
		Net_Rendition const &  nr,
		int width,
		int height,
		unsigned char * data) 
{
	QtzData alter *qtzdata = QTZD_NR (nr);

	_hoops_GAPGS("qtz_snapshot\n");

	if (qtzdata->_hoops_PIGRR == _hoops_PPSGR)
		return snapshot(nr, width, height, data); /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
	else
		/* _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_PCCP _hoops_ICCI _hoops_RPPS, _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RSH _hoops_IS _hoops_GGII */
		return false; 
}




/*
 * _hoops_SRAC
 */
local void qtz_get_physical_info (
		Display_Context alter	*dc) 
{
	QtzData alter 	*qtzdata = QTZD (dc);
	float			width, height;

	_hoops_GAPGS("qtz_get_physical_info\n");

	/* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_SRCIA _hoops_SRS _hoops_PGGA _hoops_SR _hoops_HHGC _hoops_PCHAC-_hoops_SASI _hoops_HPHS
	   _hoops_IS _hoops_IRAA _hoops_RCPPR */
	if (qtzdata->_hoops_PIGRR == _hoops_PPSGR) {
		get_physical_info(dc); /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
		qtzdata->_hoops_HAP = 72.0f;
		dc->_hoops_PGCC.flags &= ~_hoops_ISHSR;
	}
	else {
		qtzdata->_hoops_HAP = dc->options._hoops_GHHSR;
		if (dc->options._hoops_SPHSR.x != -1) {	/* _hoops_IPSP _hoops_CARSR _hoops_IGIR */
			width = dc->options._hoops_SPHSR.x * (float)(1.0 / 2.54);
			height = dc->options._hoops_SPHSR.y * (float)(1.0 / 2.54);
		}
		else {
			width = 8.5f;
			height = 11.0f;
		}
		dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
		dc->_hoops_PGCC.flags |= _hoops_ISHSR;
		if (dc->options._hoops_ARPSR) {
			dc->_hoops_PGCC._hoops_PRPSR.x = (int) (qtzdata->_hoops_HAP * height);
			dc->_hoops_PGCC._hoops_PRPSR.y = (int) (qtzdata->_hoops_HAP * width);
		}
		else {
			dc->_hoops_PGCC._hoops_PRPSR.x = (int) (qtzdata->_hoops_HAP * width);
			dc->_hoops_PGCC._hoops_PRPSR.y = (int) (qtzdata->_hoops_HAP * height);
		}
		dc->_hoops_PGCC.size.x = width * 2.54f;
		dc->_hoops_PGCC.size.y = height * 2.54f;
		dc->current._hoops_PRPSR.x = dc->_hoops_PGCC._hoops_PRPSR.x;
		dc->current._hoops_PRPSR.y = dc->_hoops_PGCC._hoops_PRPSR.y;
		dc->current._hoops_ARISR.x = dc->_hoops_PGCC._hoops_ARISR.x;
		dc->current._hoops_ARISR.y = dc->_hoops_PGCC._hoops_ARISR.y;
		dc->current.size.x = dc->_hoops_PGCC.size.x;
		dc->current.size.y = dc->_hoops_PGCC.size.y;
	}

	dc->_hoops_PGCC.driver_type = "Apple Quartz2D";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.64 $";
	dc->_hoops_PGCC._hoops_ICHSR = "vector";
	dc->_hoops_PGCC.flags &= ~_hoops_GPPGH;
	dc->_hoops_PGCC.flags |= _hoops_GIHSR;
	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	dc->_hoops_PGCC._hoops_PCHSR = _hoops_ACRSC;
	dc->_hoops_PGCC.flags &= ~_hoops_HSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_GPPGH;
	dc->_hoops_PGCC.flags &= ~_hoops_GGISR;
	dc->_hoops_PGCC.flags |= _hoops_SGICP;
	/* _hoops_RIHRR _hoops_III _hoops_SGCR _hoops_IRHAP _hoops_GPP _hoops_IHPCI _hoops_RAAA */
	if (qtzdata->_hoops_HAP > 150) 
		dc->_hoops_PGCC._hoops_IHHSR = (int)((float)qtzdata->_hoops_HAP/150.0f);
	else
		dc->_hoops_PGCC._hoops_IHHSR = 1;
}


/*
 * _hoops_SRAC
 */
local void qtz_get_current_info (
	Display_Context alter	*dc) 
{
	QtzData alter 	*qtzdata = QTZD (dc);

	_hoops_GAPGS("qtz_get_current_info\n");

	if (qtzdata->_hoops_PIGRR == _hoops_PPSGR)
		get_current_info(dc); /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
}


/*
 * _hoops_SRAC
 */
local bool qtz_start_device (
		Display_Context alter *dc) 
{
	QtzData alter *qtzdata;

	ZALLOC (qtzdata, QtzData);
	dc->data = (void alter *) qtzdata;
	qtzdata->dc = dc;
	
	/* _hoops_IH _hoops_GSPHR */
	qtzdata->fp = stdout;
	qtzdata->_hoops_ICSSC = true;
	_hoops_GAPGS("qtz_start_device\n");

	if (dc->options._hoops_GCHSR) {
		qtzdata->_hoops_PIGRR = _hoops_HPSGR;
		qtzdata->context = (CGContextRef) dc->options._hoops_GCHSR;
		HD_Get_Bit_Patterns (dc, true);
	}
	else {
		qtzdata->_hoops_PIGRR = _hoops_PPSGR;
		start_device(dc);  /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
	} 

	return true;
}



/*
 * _hoops_SRAC
 */
local void qtz_stop_device (
		Display_Context alter *dc) 
{
	QtzData alter *qtzdata = QTZD (dc);

	_hoops_GAPGS("stop_device\n");

	if (qtzdata->fp != null && !qtzdata->_hoops_ICSSC)
		fclose (qtzdata->fp);

	if (qtzdata->_hoops_IAPGS != 0) {
		FREE_ARRAY(qtzdata->_hoops_HAPGS, qtzdata->_hoops_IAPGS, Point);
		FREE_ARRAY(qtzdata->ptcounts, qtzdata->_hoops_SAPGS, int);
	}

	FREE (qtzdata, QtzData);
	dc->data = null;

	if (qtzdata->_hoops_PIGRR == _hoops_PPSGR)
		stop_device(dc);	 /* _hoops_AASA _hoops_RHIR _hoops_IS _hoops_ICCI */
}


/*
 * _hoops_SRAC (_hoops_ARSAR _hoops_AIH _hoops_ACSCC)
 */
local void qtz_get_actions (
	_hoops_APARR alter &	_hoops_RRCI) 
{
	/* _hoops_IPRPR ("_hoops_IIPGS\_hoops_ACHP"); */

	/* _hoops_HII _hoops_ICCI */
	_hoops_RRCI->_hoops_HSCSP = _hoops_HSCSP; 
	_hoops_RRCI->_hoops_ISCSP = _hoops_ISCSP; 

	/* _hoops_SISS */
	_hoops_RRCI->start_device			= qtz_start_device;
	_hoops_RRCI->stop_device 			= qtz_stop_device;
	_hoops_RRCI->get_physical_info		= qtz_get_physical_info;
	_hoops_RRCI->get_current_info		= qtz_get_current_info;
	_hoops_RRCI->init_picture			= qtz_init_picture;
	_hoops_RRCI->finish_picture			= qtz_finish_picture;
	_hoops_RRCI->init_update 			= qtz_init_update;
	_hoops_RRCI->finish_update			= qtz_finish_update;

	/* _hoops_RPPS */
	_hoops_RRCI->get_outer_window		= qtz_get_outer_window;
	_hoops_RRCI->_hoops_RSCSP 	= qtz_resize_outer_window;
	_hoops_RRCI->free_outer_window		= qtz_free_outer_window;
	_hoops_RRCI->snapshot				= qtz_snapshot; 

	/* 2D _hoops_ASCA */
	_hoops_RRCI->draw_window 			= qtz_draw_window;
	_hoops_RRCI->draw_dc_ellipse 		= qtz_draw_dc_ellipse;
	_hoops_RRCI->_hoops_CCISR	= qtz_draw_dc_elliptical_arc;
	_hoops_RRCI->_hoops_SCISR = qtz_draw_dc_outline_ellipse;
	_hoops_RRCI->draw_dc_polyline		= qtz_draw_dc_polyline;
	_hoops_RRCI->draw_dc_face			= qtz_draw_dc_face;
	_hoops_RRCI->draw_dc_colorized_face	= qtz_draw_dc_colorized_face;
	_hoops_RRCI->draw_dc_rectangle		= qtz_draw_dc_rectangle;
	_hoops_RRCI->draw_dc_polydot 		= qtz_draw_dc_polydot;
	_hoops_RRCI->draw_dc_polytriangle	= qtz_draw_dc_polytriangle;
	_hoops_RRCI->draw_dc_colorized_polytriangle = qtz_draw_dc_colorized_polytriangle;
	/* _hoops_HPGR->_hoops_CIPGS = _hoops_SIPGS; */

	_hoops_RRCI->draw_dc_rgb32_rasters	= qtz_draw_dc_rgb32_rasters;
}


/*
 * _hoops_IAAAH _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_Quartz_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, qtz_get_actions);
}

#endif /* _hoops_GCPGS */
#endif /* _hoops_ACHAC */
#endif /* _hoops_ARCHH */


