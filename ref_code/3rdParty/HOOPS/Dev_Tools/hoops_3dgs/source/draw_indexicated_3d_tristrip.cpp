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
 * $Id: obf_tmp.txt 1.241 2011-01-22 06:23:53 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "phdraw.h"
#include "driver.h"
#include "tandt.h"
#include "adt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



enum {
	_hoops_HSRCP,
	_hoops_ISRCP,
	_hoops_CSRCP
};

struct _hoops_ARHGA {
	Point	points[2];
	Vector	normals[2];
	int		_hoops_SSRCP;	// _hoops_RPP _hoops_ISHA _hoops_RCA, _hoops_GIPR _hoops_ARP _hoops_PSHR _hoops_IH _hoops_GSGAR
};

struct _hoops_PRHGA {
	Point *		points;
	Vector *	normals;	// _hoops_RPR _hoops_RGRRR, _hoops_CGHI _hoops_PPRAR _hoops_RPP _hoops_ISHA _hoops_RCA
	int			count;
	int			_hoops_SSRCP;
};

typedef VList<_hoops_ARHGA *> _hoops_IRHGA;
typedef VList<_hoops_PRHGA *> _hoops_CRHGA;
typedef VList<_hoops_IRHGA *> _hoops_GAHGA;

/* _hoops_SPR _hoops_ARP _hoops_IIGR _hoops_CIPH _hoops_IS _hoops_HPPP _hoops_IH _hoops_GRR _hoops_HPPA _hoops_IPPA */
Begin_HOOPS_Namespace
	struct _hoops_GGACP {
		_hoops_IRHGA **			_hoops_PICHR;			/* _hoops_CRPR _hoops_IIGR _hoops_IGGA _hoops_III _hoops_ARH */
		float *					findex;			/* _hoops_CRPR _hoops_IIGR _hoops_PIS _hoops_AIIC _hoops_CIHA _hoops_HSH */
		int						count;			/* _hoops_IGIR _hoops_IIGR _hoops_SIRGR */
	};
End_HOOPS_Namespace;





#define _hoops_RGACP	1024
#define _hoops_AGACP		(3*_hoops_RGACP)
#define _hoops_PGACP		(_hoops_AGACP+3) /* _hoops_ASSS _hoops_IH _hoops_SPR _hoops_RRI _hoops_SCPH _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_GHIPR-_hoops_RH-_hoops_RHC _hoops_HHGP */
#define _hoops_HGACP 4

typedef struct {
	DC_Point					_hoops_HRIGA[_hoops_PGACP];
	RGBAS32						_hoops_HIAI[_hoops_PGACP];
	_hoops_ARPA						_hoops_IHRGA[_hoops_PGACP];
	RGBA						_hoops_IGACP[_hoops_PGACP];
	float						_hoops_IIAI[_hoops_PGACP];
	_hoops_RSSH					_hoops_CGACP[_hoops_PGACP*_hoops_HGACP];
	_hoops_RSSH alter *			_hoops_SHRGA;
	DC_Point alter *			points;
	RGBAS32 alter *				colors;
	_hoops_ARPA alter *				planes;
	_hoops_RSSH alter *			params;
	RGBA alter *				_hoops_HPHSA;
	float alter *				findices;
	int							param_width;
	bool						_hoops_HSHCA;
} _hoops_SGACP;//, _hoops_GRACP;


struct _hoops_RRACP {
	Net_Rendition				nr;
	Tristrip const *			ts;
	_hoops_RHAH const *			_hoops_CSIR;
	DC_Point const *			_hoops_CGCAR;
	_hoops_GRCAR *					_hoops_RRCAR;
	/* _hoops_RCA _hoops_GAR _hoops_RPP _hoops_ARACP (_hoops_IRIC) */
	RGB alter *					_hoops_PRACP;
	RGB alter *					_hoops_HRACP;
	/* _hoops_RCA _hoops_GAR _hoops_RPP _hoops_ARACP (_hoops_GPIC)*/
	RGB alter *					_hoops_IRACP;
	RGB alter *					_hoops_CRACP;
	RGB alter *					_hoops_SRACP;  /* _hoops_PSHA _hoops_GAR _hoops_RPP _hoops_GAACP */
	_hoops_ARPA alter *				planes;
	_hoops_SGACP 					_hoops_IGIC;
	Point const *				_hoops_RAACP;
	float						_hoops_HPRCP;
	bool 						_hoops_CRIR;
	bool 						_hoops_AAACP;
	bool 						_hoops_PAACP;
	bool 						_hoops_APH;
	bool 						_hoops_HAACP;
	bool 						_hoops_IAACP;
	bool 						_hoops_CAACP;
	bool 						_hoops_SAACP;
	unsigned char				_hoops_IRIR;
};







// _hoops_IPCGP _hoops_IGPI, _hoops_RIRRR _hoops_HII _hoops_RPRIP _hoops_RRGR


#define _hoops_PPHGA 0
#define _hoops_HPHGA 1
#define _hoops_IPHGA		2
#define _hoops_CPHGA	3
#define _hoops_SPHGA	4

local bool _hoops_GHHGA (_hoops_IRHGA *_hoops_RHHGA, _hoops_GAHGA *_hoops_AHHGA, float tolerance)
{
	_hoops_IRHGA *		_hoops_HHHGA;
	_hoops_ARHGA			*_hoops_IHHGA, *_hoops_CHHGA, *_hoops_SHHGA, *_hoops_GIHGA, *line;
	float 			_hoops_RIHGA = tolerance;
	float 			_hoops_ARGCR;
	int 			_hoops_PIHGA = -1;
	int 			_hoops_HIHGA, i;
	int 			_hoops_IIHGA = _hoops_PPHGA;

	_hoops_IHHGA = _hoops_RHHGA->PeekFirst();
	_hoops_CHHGA = _hoops_RHHGA->PeekLast();
	_hoops_HIHGA = _hoops_AHHGA->Count();
	_hoops_AHHGA->ResetCursor();

	for (i = 0; i < _hoops_HIHGA; i++) {
		/* _hoops_HGCR _hoops_IRS _hoops_SIHGA */
		_hoops_HHHGA = _hoops_AHHGA->PeekCursor();

		_hoops_SHHGA = _hoops_HHHGA->PeekFirst();
		_hoops_GIHGA = _hoops_HHHGA->PeekLast();

		_hoops_ARGCR = (_hoops_IHHGA->points[0] - _hoops_SHHGA->points[0])._hoops_PPSSR();	/* _hoops_HSPP _hoops_HSPP */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_HPHGA;
		}

		_hoops_ARGCR = (_hoops_CHHGA->points[1] - _hoops_GIHGA->points[1])._hoops_PPSSR();		/* _hoops_RSGR _hoops_RSGR */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_IPHGA;
		}

		_hoops_ARGCR = (_hoops_CHHGA->points[1] - _hoops_SHHGA->points[0])._hoops_PPSSR();	/* _hoops_RSGR _hoops_HSPP */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_CPHGA;
		}

		_hoops_ARGCR = (_hoops_IHHGA->points[0] - _hoops_GIHGA->points[1])._hoops_PPSSR();		/* _hoops_HSPP _hoops_RSGR */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_SPHGA;
		}

		/* _hoops_GCHGA _hoops_IS _hoops_RH _hoops_SPS _hoops_SIHGA */
		_hoops_AHHGA->AdvanceCursor();
	}

	/* _hoops_HCHGA _hoops_RSIH _hoops_RPP _hoops_ISAP _hoops_SIHRR */
	if (_hoops_PIHGA == -1)
		return false;

	/* _hoops_RPP _hoops_IIH _hoops_CHR _hoops_RRI _hoops_HSAR _hoops_SAHR _hoops_IRS _hoops_CIAGR _hoops_III _hoops_SGHC _hoops_GGR _hoops_RH _hoops_III _hoops_HIGR, _hoops_CACH _hoops_RPP
	 * _hoops_SCH _hoops_ICHGA _hoops_ACAS _hoops_IS _hoops_IRS _hoops_PHPA _hoops_GPPS _hoops_HSAR _hoops_RH _hoops_PSSP _hoops_SR _hoops_GSGI.	*/
	if (_hoops_RHHGA->Count() > 3) {
		if ((_hoops_IHHGA->points[0] - _hoops_CHHGA->points[1])._hoops_PPSSR() < _hoops_RIHGA)
			return false;
	}

	/* _hoops_ASAR-_hoops_CCHGA _hoops_RH _hoops_AAH _hoops_SIHRR _hoops_HII _hoops_RH _hoops_SIHGA _hoops_HIGR */
	_hoops_HHHGA = _hoops_AHHGA->NthItem(_hoops_PIHGA);
	/* _hoops_RPP _hoops_IIH _hoops_CHR _hoops_RRI _hoops_HSAR _hoops_SAHR _hoops_IRS _hoops_CIAGR _hoops_III _hoops_SGHC _hoops_GGR _hoops_RH _hoops_SIHGA, _hoops_CACH _hoops_RPP
	 * _hoops_SCH _hoops_ICHGA _hoops_ACAS _hoops_IS _hoops_IRS _hoops_PHPA _hoops_GPPS _hoops_HSAR _hoops_RH _hoops_PSSP _hoops_SR _hoops_GSGI.	*/
	if (_hoops_HHHGA->Count() >= 3) {
		_hoops_SHHGA = _hoops_HHHGA->PeekFirst();
		_hoops_GIHGA = _hoops_HHHGA->PeekLast();
		if ((_hoops_SHHGA->points[0] - _hoops_GIHGA->points[1])._hoops_PPSSR() < _hoops_RIHGA)
			return false; /* _hoops_RH _hoops_SIHGA _hoops_CSAP _hoops_AIAH _hoops_CAHC */
	}


	switch (_hoops_IIHGA) {
		case _hoops_HPHGA: {
			while ((line = _hoops_RHHGA->RemoveFirst()) != null) {
				Swap (line->points[0], line->points[1]);
				Swap (line->normals[0], line->normals[1]);
				_hoops_HHHGA->AddFirst(line);
			}
		}	break;

		case _hoops_IPHGA: {
			_hoops_RHHGA->Reverse();
			while ((line = _hoops_RHHGA->RemoveFirst()) != null) {
				Swap (line->points[0], line->points[1]);
				Swap (line->normals[0], line->normals[1]);
				_hoops_HHHGA->AddLast(line);
			}
		}	break;

		case _hoops_CPHGA: {
			_hoops_RHHGA->Reverse();
			while ((line = _hoops_RHHGA->RemoveFirst()) != null) {
				_hoops_HHHGA->AddFirst(line);
			}
		}	break;

		case _hoops_SPHGA: {
			while ((line = _hoops_RHHGA->RemoveFirst()) != null) {
				_hoops_HHHGA->AddLast(line);
			}
		}	break;

		default: {
			/* _hoops_RGR _hoops_CGH _hoops_IIP _hoops_IHPS -- _hoops_RPP _hoops_ISAP _hoops_RIAGR _hoops_SIHRR, _hoops_SR _hoops_CGH _hoops_HS
			 * _hoops_AIAH _hoops_SCHGA */
			return false;
		}
	}

	delete _hoops_RHHGA;
	return true;
}


local float _hoops_IGSGA[] = {0.001f, 0.01f, 0.1f, 1.0f};

GLOBAL_FUNCTION int HD_Process_Isolines (
	Display_Context *			dc,
	Geometry const *			geometry,
	Bounding const &			bounding,
	Polyedge * *				_hoops_ASRGR,
	float						tolerance) {
	_hoops_GGACP *			_hoops_RGIGA = dc->_hoops_GPACP;
	Polyedge *					pe;
	Point *						pt;
	Vector *					_hoops_GIHI;
	_hoops_IRHGA *					_hoops_HHHGA;
	_hoops_IRHGA *					_hoops_RHHGA;
	_hoops_GAHGA *			_hoops_CAHGA;
	_hoops_CRHGA *				_hoops_GPHGA;
	_hoops_ARHGA *					line;
	_hoops_PRHGA *				polyline;
	int							_hoops_RPACP = 0;
	int							i, j, edge, count, point_count;

	if (_hoops_RGIGA == null)
		return 0;			// _hoops_PHSPR _hoops_IIP _hoops_GSGI _hoops_IRS _hoops_GHRP _hoops_CRHH

	for (int k = 0; k < _hoops_RGIGA->count; k++) {
		if (_hoops_RGIGA->_hoops_PICHR[k] == null)
			continue;

		/* _hoops_CCPP _hoops_HHH _hoops_AH _hoops_CPCI.  _hoops_ASC _hoops_CHR _hoops_HCR _hoops_SRSGA _hoops_GH _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_API, _hoops_HIS _hoops_GASGA _hoops_IIGR
		 * _hoops_GII _hoops_RSIH _hoops_RASGA _hoops_SGS _hoops_AASGA _hoops_SGS _hoops_GGAS. */
		_hoops_CAHGA = POOL_NEW(dc->memory_pool, _hoops_GAHGA)(dc->memory_pool);
		_hoops_GPHGA = POOL_NEW(dc->memory_pool, _hoops_CRHGA)(dc->memory_pool);

		/* _hoops_PASGA _hoops_HII _hoops_III _hoops_IS _hoops_ISII */
		while ((line = _hoops_RGIGA->_hoops_PICHR[k]->RemoveFirst()) != null) {
			_hoops_HHHGA = POOL_NEW(dc->memory_pool, _hoops_IRHGA)(dc->memory_pool);
			_hoops_HHHGA->AddFirst(line);
			_hoops_CAHGA->AddLast(_hoops_HHHGA);
		}
		delete _hoops_RGIGA->_hoops_PICHR[k];
		_hoops_RGIGA->_hoops_PICHR[k] = null;

		bool	_hoops_APACP = (_hoops_CAHGA->Count() < 5000);

		if (_hoops_APACP) {
			// _hoops_GPGR _hoops_HHHH _hoops_HPGR _hoops_HASGA _hoops_HIH _hoops_CASGA _hoops_SASGA _hoops_GPSGA, _hoops_ACPP _hoops_RPSGA
			_hoops_GAHGA *	_hoops_ARGC = POOL_NEW(dc->memory_pool, _hoops_GAHGA)(dc->memory_pool);

			for (i=0; _hoops_CAHGA->Count() > 1 && i < _hoops_GGAPR(_hoops_IGSGA); i++) {
				float			_hoops_IASGA = tolerance * _hoops_IGSGA[i];

				while ((_hoops_RHHGA = _hoops_CAHGA->RemoveFirst()) != null) {
					if (_hoops_GHHGA (_hoops_RHHGA, _hoops_CAHGA, _hoops_IASGA))
						continue;

					_hoops_ARGC->AddFirst(_hoops_RHHGA);
				}
				Swap (_hoops_CAHGA, _hoops_ARGC);
			}

			delete _hoops_ARGC;
		}


		while ((_hoops_RHHGA = _hoops_CAHGA->RemoveFirst()) != null) {
			if (_hoops_APACP) {
				/* _hoops_SR'_hoops_RISP _hoops_PPACP _hoops_RH _hoops_SRS _hoops_SIHGA _hoops_PSAP _hoops_RH _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_HIGR.	 _hoops_HPACP _hoops_SR _hoops_HSPP
				 * _hoops_PHSPR _hoops_SCH, _hoops_HGRRA, _hoops_CACH _hoops_RPP _hoops_SCH _hoops_PAH _hoops_SHH _hoops_RPHGA _hoops_CCA _hoops_GII _hoops_IIGR _hoops_RH _hoops_HIASR. */
				if (_hoops_GHHGA (_hoops_RHHGA, _hoops_CAHGA, tolerance))
					continue;
			}

			/* _hoops_APSGA _hoops_HII _hoops_IRS _hoops_CCHHR _hoops_HIGR _hoops_SCCI _hoops_CRGR _hoops_PCCP _hoops_CRPR.	 _hoops_PS _hoops_PHHR _hoops_HII _hoops_IRS _hoops_PPSGA _hoops_IIGR "_hoops_HPSGA"'_hoops_GRI
			 * _hoops_IS _hoops_IRS _hoops_RSRA "_hoops_IPSGA" */
			if (_hoops_RHHGA->Count() != 0) {
				ZALLOC (polyline, _hoops_PRHGA);
				count = _hoops_RHHGA->Count();
				polyline->count = count + 1;
				ALLOC_ARRAY (polyline->points, polyline->count, Point);
				line = _hoops_RHHGA->PeekFirst();
				if ((polyline->_hoops_SSRCP = line->_hoops_SSRCP) != _hoops_HSRCP)
					ALLOC_ARRAY (polyline->normals, polyline->count, Vector);

				for (i = 0; i < count; i++) {
					line = _hoops_RHHGA->RemoveFirst();
					polyline->points[i] = line->points[0];
					if (polyline->_hoops_SSRCP != _hoops_HSRCP)
						polyline->normals[i] = line->normals[0];
					if (i == count - 1) {
						polyline->points[i+1] = line->points[1];
						if (polyline->_hoops_SSRCP  != _hoops_HSRCP)
							polyline->normals[i+1] = line->normals[1];
					}
					FREE (line, _hoops_ARHGA);
				}

				_hoops_GPHGA->AddFirst(polyline);
			}
			delete _hoops_RHHGA;
			_hoops_RHHGA = null;
		}

		if (_hoops_GPHGA->Count() == 0)
			goto _hoops_HPAGR;


		/* _hoops_PASGA _hoops_HII _hoops_ISII _hoops_IS _hoops_IPCGP _hoops_ACRI */
		_hoops_GPHGA->ResetCursor();
		/* _hoops_GRAS _hoops_PCCP _hoops_AAPA _hoops_ASCR _hoops_GPP _hoops_PPSR _hoops_RPR */
		point_count = 0;
		count = _hoops_GPHGA->Count();
		for (i = 0; i < count; i++) {
			polyline = _hoops_GPHGA->PeekCursor();
			point_count += polyline->count;
			_hoops_GPHGA->AdvanceCursor();
		}

		// _hoops_CAHP _hoops_PCCP _hoops_IPCGP _hoops_ACRI _hoops_RIIA _hoops_IIGR _hoops_GRRRA _hoops_PGRC
		// _hoops_IHHA _hoops_CRPR _hoops_GRS _hoops_SHH '_hoops_RPR' _hoops_RGRRR, _hoops_RII _hoops_SIRGR '_hoops_RSHS' _hoops_RGRRR
		ZALLOC (pe, Polyedge);
		pe->_hoops_PHHA = count;
		ZALLOC_ARRAY (pe->lengths, count, int);
		pe->lengths_allocated = count;
		ZALLOC_ARRAY (pe->_hoops_AIHA, point_count, int);
		pe->_hoops_IPII = point_count;
		pe->_hoops_RAHH |= _hoops_AAHH;
		ALLOC_ARRAY_ALIGNED (pe->points, point_count, Point, 16);
		ZERO_ARRAY (pe->points, point_count, Point);
		pe->point_count = point_count;
		pe->_hoops_RAHH |= _hoops_AIPI;
		pe->total = point_count;
		pe->_hoops_SPHA = point_count - count;
		polyline = _hoops_GPHGA->PeekFirst();
		if (polyline->_hoops_SSRCP == _hoops_CSRCP) {
			ZALLOC_ARRAY (pe->_hoops_ICHA, pe->point_count, Vector);
			pe->_hoops_RAHH |= _hoops_ICGHR;
			_hoops_GIHI = pe->_hoops_ICHA;
		}
		else if (polyline->_hoops_SSRCP == _hoops_ISRCP) {
			ZALLOC_ARRAY (pe->_hoops_SPII, pe->point_count, int);
			pe->_hoops_CPII = pe->point_count;
			ZALLOC_ARRAY (pe->_hoops_RSHA, pe->_hoops_SPHA, Vector);
			pe->_hoops_RAHH |= _hoops_GHII;
			_hoops_GIHI = pe->_hoops_RSHA;
		}
		else
			_hoops_GIHI = null;
		pt = pe->points;
		_hoops_ICAI (pe);

		pe->_hoops_CARI |= _hoops_RCRI;


		pe->_hoops_PPGI.flags = _hoops_IPACP;
		pe->_hoops_PPGI._hoops_CPACP = k;
		pe->_hoops_PPGI.findex = _hoops_RGIGA->findex[k];

		j = 0;
		edge = 0;
		for (i = 0; i < count; i++) {
			polyline = _hoops_GPHGA->RemoveFirst();

			pe->lengths[i] = polyline->count;
			_hoops_AIGA (polyline->points, polyline->count, Point, pt);
			pt += polyline->count;

			if (polyline->_hoops_SSRCP == _hoops_CSRCP) {
				_hoops_AIGA (polyline->normals, polyline->count, Vector, _hoops_GIHI);
				_hoops_GIHI += polyline->count;
			}
			else if (polyline->_hoops_SSRCP == _hoops_ISRCP) {
				_hoops_AIGA (polyline->normals, polyline->count-1, Vector, _hoops_GIHI);
				_hoops_GIHI += polyline->count-1;
			}

			FREE_ARRAY (polyline->points, polyline->count, Point);
			if (polyline->normals != null)
				FREE_ARRAY (polyline->normals, polyline->count, Vector);
			FREE (polyline, _hoops_PRHGA);

			if (pe->_hoops_SPII != null) {
				pe->_hoops_SPII[j++] = 0;
				for (int ii = 0; ii < pe->lengths[i]-1; ii++)
					pe->_hoops_SPII[j++] = edge++;
			}
		}
		for (i = 0; i < point_count; i++)
			pe->_hoops_AIHA[i] = i;


		pe->_hoops_GSCP = (Polyhedron *)geometry;
		pe->bounding = bounding;

		pe->next = *_hoops_ASRGR;
		*_hoops_ASRGR = pe;

		_hoops_RPACP = k + 1;	// _hoops_GPSGR _hoops_HIS _hoops_SGIP

	  _hoops_HPAGR:
		delete _hoops_CAHGA;
		delete _hoops_GPHGA;
	}


	FREE_ARRAY (_hoops_RGIGA->_hoops_PICHR, _hoops_RGIGA->count, _hoops_IRHGA *);
	FREE_ARRAY (_hoops_RGIGA->findex, _hoops_RGIGA->count, float);
	FREE (_hoops_RGIGA, _hoops_GGACP);

	dc->_hoops_GPACP = null;

	return _hoops_RPACP;
}






/*
 * _hoops_RAIGR _hoops_PIP _hoops_HII _hoops_HIRCP. _hoops_IIRCP:
 *
 * _hoops_AHGHR _hoops_IRS _hoops_SCPH, _hoops_CCA _hoops_SAPS _hoops_PSPI _hoops_HPGR _hoops_GRR _hoops_GPHA, _hoops_RGR
 * _hoops_PCPH _hoops_GRS _hoops_GRAS _hoops_RH _hoops_ICRP _hoops_AAIGR _hoops_SPACP.	_hoops_CACPR _hoops_SPACP
 * _hoops_HRGR _hoops_IRS _hoops_SCPH _hoops_CGGR _hoops_SGS _hoops_GHACP _hoops_GRR _hoops_ARAH-_hoops_SCPH _hoops_PAH
 * _hoops_SHH _hoops_HSCH _hoops_CCA _hoops_IRS _hoops_RSRA _hoops_SAPS-_hoops_CIHA.  _hoops_IPCP _hoops_ICRP _hoops_AAIGR
 * _hoops_SPACP _hoops_HRGR _hoops_RH _hoops_SPR _hoops_CCA _hoops_RH _hoops_RHACP _hoops_PHI _hoops_IIGR _hoops_RSSA.
 * _hoops_IPCP _hoops_PCPH _hoops_GRS _hoops_ASRC _hoops_RH _hoops_CGGR _hoops_HIS _hoops_HRCRA, _hoops_PPR _hoops_RGCI _hoops_SPCC.
 * _hoops_GPGP _hoops_PIHRA, _hoops_RH _hoops_PCPH _hoops_GRS _hoops_IHGC _hoops_RH _hoops_RSSP _hoops_IIGR _hoops_RH
 * _hoops_GARRA _hoops_CGGR.	 _hoops_AHACP-_hoops_HIPH _hoops_GIAA _hoops_RH _hoops_CGGR _hoops_GRS _hoops_IIIAR
 * _hoops_RSSP, _hoops_IIGR _hoops_IPGAA, _hoops_HIS _hoops_SCH _hoops_HRGR _hoops_HAHH _hoops_IS _hoops_IHGC _hoops_RGAR _hoops_RH
 * _hoops_RSSP _hoops_IIGR _hoops_RH _hoops_SRS _hoops_ARAH-_hoops_SCPH.
 *
 * _hoops_IPCP _hoops_GIAP _hoops_RHPC, _hoops_CIRCP, _hoops_ICRRP _hoops_RH "_hoops_SIRCP _hoops_PPSR"
 * _hoops_IGIAR _hoops_RH _hoops_GCRCP _hoops_III.  _hoops_HSRR _hoops_PCAI: _hoops_RH _hoops_HPRGR _hoops_IPPHR
 * _hoops_IIGR _hoops_SIRCP _hoops_SIGH _hoops_IRS _hoops_CIRCP _hoops_IIGR 0.5.	_hoops_RCPA _hoops_GIRR _hoops_GH _hoops_CGPR >=0.6,
 * _hoops_PPR _hoops_ISHP _hoops_CGPR <0.6, _hoops_ARP _hoops_RH _hoops_CIRCP _hoops_IS 0.6.	_hoops_RCPA _hoops_ACASA,
 * _hoops_ARP _hoops_RH _hoops_CIRCP _hoops_IS 1.0.
 *
 * _hoops_RAHP _hoops_PCCP _hoops_PGCPR _hoops_PPAP _hoops_GIRRR, _hoops_RH _hoops_SAPS _hoops_PSPI _hoops_IIGR _hoops_RH
 * _hoops_ARGR _hoops_CGGR _hoops_ASRHA _hoops_RCRCP.
 */
#	define		_hoops_ACRCP					1.0f
#	define		_hoops_PCRCP				(1.0f - _hoops_ACRCP)


local RGB *_hoops_PHACP (
	Net_Rendition const &		nr,
	Tristrip const *			ts,
	float						_hoops_HPRCP) {
	_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
	_hoops_AHAH const &				_hoops_PHAH = _hoops_RRA->_hoops_IHRH;
	int							point_count;
	_hoops_ACGHR const *	_hoops_HHACP = ts->_hoops_HCHA;
	RGB alter					*_hoops_IHACP, *vcolors;
	_hoops_RHAH const *			_hoops_CSIR;
	int							i;

	_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

	ALLOC_ARRAY (_hoops_IHACP, ts->point_count, RGB);
	vcolors = _hoops_IHACP;

	if (!ts->_hoops_RPRCP)
		_hoops_HPRCP = 0; /* _hoops_AIAH _hoops_CHACP _hoops_IH _hoops_ASSA _hoops_IIGR _hoops_SHACP */

	point_count = ts->point_count;

	for (i = 0; i < point_count; i++) {
		if (_hoops_CSIR->length == 0) {
			HD_Report_Null_Color_Map ("tristrip", _hoops_CSIR);
			*vcolors = _hoops_GPSR::_hoops_RPSR;
		}
		else
			_hoops_ICRCP (_hoops_CSIR, *_hoops_HHACP * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate + _hoops_HPRCP,
						   *vcolors, ts->_hoops_RPRCP, _hoops_PHAH);

		++_hoops_HHACP;
		++vcolors;
	}
	return _hoops_IHACP;
}

local void _hoops_GIACP (
	Net_Rendition const &		nr,
	Tristrip alter *			ts) {
	_hoops_ARPA alter *				_hoops_RIACP;
	Display_Context *			dc = (Display_Context*)nr->_hoops_SRA;

	if ((_hoops_RIACP = dc->_hoops_AIACP) == null) {
		POOL_ALLOC_ARRAY_ALIGNED (_hoops_RIACP, ts->face_count, _hoops_ARPA, 16, dc->memory_pool);
		dc->_hoops_AIACP = _hoops_RIACP;
		dc->_hoops_PIACP = ts->face_count;

		if (ts == null ||
			ts->_hoops_GSCP == null ||
			(ts->_hoops_GSCP && ts->_hoops_GSCP->type >= _hoops_PRCP) ||
			((Polyhedron*)ts->_hoops_GSCP)->local_face_attributes.normals == null) {
			bool		*done;

			/*
			 * _hoops_CPGP _hoops_HIACP _hoops_HRGR _hoops_IIACP, _hoops_RIP _hoops_RH _hoops_RSSI _hoops_GAR '_hoops_HAR _hoops_CPHR'
			 * _hoops_PPR _hoops_ISPR _hoops_RH _hoops_RIP _hoops_SPHR.
			 */
			POOL_ZALLOC_ARRAY (done, ts->face_count, bool, dc->memory_pool);
			ZERO_ARRAY (_hoops_RIACP, ts->face_count, _hoops_ARPA);


			{
				_hoops_SGCC const &	_hoops_HSGA = nr->transform_rendition->_hoops_IPH;
				int							_hoops_PHHA = ts->_hoops_PHHA;
				int const *					lengths = ts->lengths;
				int const *					vi = ts->_hoops_AIHA;
				int const *					fi = ts->face_indices;
				int							length = 0;
				int							_hoops_HSPI;
				int							_hoops_ISPI;
				int							_hoops_CSPI;
				int							face = -1;
				_hoops_ARPA const *				normals;

				/* (_hoops_RH _hoops_CIACP _hoops_ARI _hoops_IHSH _hoops_GGSR-_hoops_IIGR-_hoops_PRCH, _hoops_HIH _hoops_GRS _hoops_SHH _hoops_IGI _hoops_GPRS) */
				normals = ts->_hoops_PRHH;

				/* _hoops_RCPA _hoops_SICR _hoops_RH _hoops_IRHP _hoops_HSP _hoops_ASGA _hoops_IS _hoops_GHC, _hoops_SR _hoops_RRP _hoops_IRS
				 * _hoops_ISAR _hoops_PPSR _hoops_IH _hoops_GRR. _hoops_PS _hoops_AA _hoops_RGR _hoops_HPP _hoops_SIACP _hoops_RH
				 * _hoops_RCAPR _hoops_CRHH. _hoops_GCACP.
				 */
				while (_hoops_PHHA-- > 0) {
					bool					_hoops_SICPR = false;
					bool					_hoops_ASSRR = false;

					if (BIT (nr->transform_rendition->heuristics, _hoops_SASA))
						_hoops_ASSRR = true;

					length = *lengths++;
					if (length < 0) {
						_hoops_SICPR = true;
						length = -length;
					}
					_hoops_HSPI = *vi++;
					_hoops_ISPI = *vi++;
					if (fi) fi += 2;
					length -= 2;

					while (length-- > 0) {
						_hoops_CSPI = *vi++;
						if (fi)
							face = *fi++;
						else
							face++;

						/* _hoops_RARIR _hoops_GII _hoops_HSP'_hoops_GRI _hoops_IPPA _hoops_HGGC _hoops_PPSPR _hoops_AIPH. */
						if (!done[face]) {
							Vector *		normal;
							Vector			vector;

							if (normals != null)
								normal = (Vector *)&normals[face];
							else {
								Vector		_hoops_RCACP, _hoops_ACACP;

								_hoops_RCACP.x = ts->points[_hoops_ISPI].x - ts->points[_hoops_HSPI].x;
								_hoops_RCACP.y = ts->points[_hoops_ISPI].y - ts->points[_hoops_HSPI].y;
								_hoops_RCACP.z = ts->points[_hoops_ISPI].z - ts->points[_hoops_HSPI].z;

								_hoops_ACACP.x = ts->points[_hoops_CSPI].x - ts->points[_hoops_ISPI].x;
								_hoops_ACACP.y = ts->points[_hoops_CSPI].y - ts->points[_hoops_ISPI].y;
								_hoops_ACACP.z = ts->points[_hoops_CSPI].z - ts->points[_hoops_ISPI].z;

								vector.x = _hoops_RCACP.y * _hoops_ACACP.z  -	 _hoops_RCACP.z * _hoops_ACACP.y;
								vector.y = _hoops_RCACP.z * _hoops_ACACP.x  -	 _hoops_RCACP.x * _hoops_ACACP.z;
								vector.z = _hoops_RCACP.x * _hoops_ACACP.y  -	 _hoops_RCACP.y * _hoops_ACACP.x;

								HI_Normalize (&vector);

								if (_hoops_ASSRR) {
									vector.x = -vector.x;
									vector.y = -vector.y;
									vector.z = -vector.z;
								}
								normal = &vector;
							}

							HD_Compute_One_World_Plane (_hoops_HSGA, normal,
														&ts->points[_hoops_CSPI],
														&_hoops_RIACP[face]);
							done[face] = true;
						}

						if (!_hoops_SICPR) {
							_hoops_HSPI = _hoops_ISPI;
							_hoops_ASSRR = !_hoops_ASSRR;
						}
						_hoops_ISPI = _hoops_CSPI;
					}
				}
			}
			FREE_ARRAY (done, ts->face_count, bool);
		}
		else
			HD_Compute_World_Face_Planes (nr, ((Polyhedron*)ts->_hoops_GSCP), _hoops_RIACP);
	}
}

local void _hoops_PCACP (
	Net_Rendition const &		nr,
	Tristrip const *			ts,
	int							face_count) {
	Polyhedron const				*_hoops_IPRI = null;
	Display_Context*				dc = (Display_Context*)nr->_hoops_SRA;

	/* _hoops_CGP _hoops_IIH _hoops_CHR _hoops_PSP _hoops_RSSI, _hoops_PSCR _hoops_IIH _hoops_CHR _hoops_PSP _hoops_GSSIA. */
	if (!face_count) return;

	if (ts->_hoops_GSCP && ts->_hoops_GSCP->type <= _hoops_PRCP)
		_hoops_IPRI = (Polyhedron*)ts->_hoops_GSCP;

	if (dc->_hoops_AIACP != null) {
		/* _hoops_HCACP */
		dc->_hoops_CGHAR =
			HD_Generate_DC_Screen_Facings (nr, face_count,
											  dc->_hoops_AIACP, false);
		dc->_hoops_ICACP = face_count;
	}
	else if (_hoops_IPRI != null &&
			_hoops_IPRI->local_face_attributes.normals != null) {
		/* [_hoops_GCAS] _hoops_CGGGA _hoops_IRS _hoops_CCAH _hoops_RSGA & _hoops_GGRA _hoops_CGH _hoops_SHH _hoops_CCACP
		 * _hoops_HSAR _hoops_SCACP _hoops_RH _hoops_GHC _hoops_IS _hoops_GSSP _hoops_GC (_hoops_PPR _hoops_PSCR _hoops_GAAP
		 * _hoops_CGGGA _hoops_PCCP _hoops_GGRA _hoops_APIC)
		 */
		dc->_hoops_CGHAR = HD_Generate_DC_Screen_Facings (nr, face_count,
						_hoops_IPRI->local_face_attributes.normals, true);
		dc->_hoops_ICACP = face_count;
	}
	else {
		/* _hoops_RRP _hoops_IS _hoops_HGCR _hoops_RH _hoops_GHC _hoops_SRS */
		_hoops_GIACP (nr, (Tristrip alter *)ts);
		dc->_hoops_CGHAR =  HD_Generate_DC_Screen_Facings (nr, face_count,
											  dc->_hoops_AIACP, false);
		dc->_hoops_ICACP = face_count;
	}
}

local void _hoops_GSACP (
	Net_Rendition const &		nr,
	_hoops_HHA const &	_hoops_ISHIR,
	Point const *				_hoops_RSACP,
	RGB const *					color,
	_hoops_ARPA const *				plane,
	Vector const *				_hoops_ASACP,
	RGBA alter *				total,
	RGBA alter *				_hoops_PSACP) {
	_hoops_SGCC const &	_hoops_HSGA = nr->transform_rendition->_hoops_IPH;
	Point						_hoops_HSACP;

	_hoops_HSACP.x = _hoops_HPRA (_hoops_HSGA->data.elements, *_hoops_RSACP);
	_hoops_HSACP.y = _hoops_IPRA (_hoops_HSGA->data.elements, *_hoops_RSACP);
	_hoops_HSACP.z = _hoops_CPRA (_hoops_HSGA->data.elements, *_hoops_RSACP);

	_hoops_ISACP (nr, nr->_hoops_IHA->_hoops_AGP,
						 _hoops_ISHIR, &_hoops_HSACP, color, plane, _hoops_ASACP, null, 0, 0, total, _hoops_PSACP);
}

local void _hoops_CSACP(Net_Rendition const &nr,
					 _hoops_HHA const & mat,
					 bool _hoops_SSACP,
					 Point const * point,
					 RGB const * color,
					 _hoops_ARPA const * plane,
					 Vector const * _hoops_ASACP,
					 RGBA * _hoops_GGPCP,
					 RGBA * _hoops_RGPCP)
{
	if (_hoops_SSACP &&
		ANYBIT (nr->transform_rendition->_hoops_IPH->data._hoops_RAGR, _hoops_CICH))
		_hoops_GSACP (nr, mat, point, color, plane, _hoops_ASACP, _hoops_GGPCP, _hoops_RGPCP);
	else
		_hoops_ISACP (nr,
							 nr->_hoops_IHA->_hoops_AGP,
							 mat, point, color, plane, _hoops_ASACP, null, 0, 0, _hoops_GGPCP, _hoops_RGPCP);
}

/* _hoops_GRAS _hoops_PCPA _hoops_RH _hoops_RCA _hoops_CHH _hoops_SHH _hoops_RPP _hoops_RH _hoops_ISSGR _hoops_AAPR _hoops_HCR _hoops_PGS */
local void _hoops_AGPCP (
	Net_Rendition const &		nr,
	Tristrip const *			ts,
	_hoops_ARPA const *				_hoops_PGPCP,
	bool						_hoops_CAACP,
	RGB alter *					_hoops_HGPCP,
	RGB alter *					_hoops_IGPCP) {
	int							i;
	_hoops_HHA const &	_hoops_ISHIR = nr->_hoops_IHA->_hoops_CHA;
	RGBA						temp, _hoops_CGPCP;

	for (i = 0; i < ts->point_count; i++) {
		_hoops_CSACP (nr, _hoops_ISHIR, _hoops_CAACP,
			&ts->points[i], &_hoops_GPSR::_hoops_IAHHP, &_hoops_PGPCP[i], null, &temp, &_hoops_CGPCP);
		_hoops_HGPCP[i] = temp;
		_hoops_IGPCP[i] = _hoops_CGPCP;
	}
}
local void _hoops_SGPCP (
	Net_Rendition const &		inr,
	Tristrip const *			ts,
	_hoops_ARPA const *				_hoops_AIACP,
	bool						_hoops_CAACP,
	RGB alter *					_hoops_GRPCP,
	RGB alter *					_hoops_RRPCP) {
	Net_Rendition const &		nr = inr;
	_hoops_HHA const &	_hoops_ISHIR = nr->_hoops_IHA->_hoops_CHA;
	RGBA _hoops_PGC, _hoops_SGC;

	for (int i = 0; i < ts->face_count; ++i) {
		_hoops_CSACP (nr,
			_hoops_ISHIR,
			_hoops_CAACP,
			&ts->points[0],
			&_hoops_GPSR::_hoops_IAHHP,
			&_hoops_AIACP[i],
			null,
			&_hoops_PGC,
			&_hoops_SGC);
		_hoops_GRPCP[i] = _hoops_PGC;
		_hoops_RRPCP[i] = _hoops_SGC;
	}
}

local void _hoops_ARPCP (_hoops_SGACP *_hoops_IGIC)
{
	_hoops_IGIC->points = _hoops_IGIC->_hoops_HRIGA;
	_hoops_IGIC->colors = _hoops_IGIC->_hoops_HIAI;
	_hoops_IGIC->planes = _hoops_IGIC->_hoops_IHRGA;
	_hoops_IGIC->params = _hoops_IGIC->_hoops_SHRGA;
	_hoops_IGIC->_hoops_HPHSA = _hoops_IGIC->_hoops_IGACP;
	_hoops_IGIC->findices = _hoops_IGIC->_hoops_IIAI;
}

local void _hoops_PRPCP (_hoops_SGACP *_hoops_IGIC, int param_width)
{
	_hoops_IGIC->param_width = param_width;
	if (param_width > _hoops_HGACP)
		ALLOC_ARRAY (_hoops_IGIC->_hoops_SHRGA, _hoops_PGACP * param_width, _hoops_RSSH);
	else
		_hoops_IGIC->_hoops_SHRGA = _hoops_IGIC->_hoops_CGACP;
	_hoops_IGIC->_hoops_HSHCA = false;
	_hoops_ARPCP(_hoops_IGIC);
}

local void _hoops_HRPCP (_hoops_SGACP *_hoops_IGIC)
{
	if (_hoops_IGIC->param_width > _hoops_HGACP)
		FREE_ARRAY (_hoops_IGIC->_hoops_SHRGA, _hoops_PGACP * _hoops_IGIC->param_width, _hoops_RSSH);
}


local void _hoops_IRPCP (
	Net_Rendition const & nr,
	_hoops_SGACP alter *_hoops_IGIC)
{
	int			count;

	count = _hoops_IGIC->points - _hoops_IGIC->_hoops_HRIGA;
	if (count == 0)
		return;

	if (_hoops_IGIC->planes != _hoops_IGIC->_hoops_IHRGA) {
		RGBA const *		_hoops_HPHSA = null;

		if (_hoops_IGIC->_hoops_HPHSA != _hoops_IGIC->_hoops_IGACP)
			_hoops_HPHSA = _hoops_IGIC->_hoops_IGACP;

		_hoops_CRPCP (nr, -count, _hoops_IGIC->_hoops_HRIGA, _hoops_HPHSA, _hoops_IGIC->_hoops_IHRGA);
	}
	else if (_hoops_IGIC->colors != _hoops_IGIC->_hoops_HIAI) {
		if (_hoops_IGIC->_hoops_HSHCA)
			_hoops_SRPCP (nr, -count, _hoops_IGIC->_hoops_HRIGA, _hoops_IGIC->_hoops_HIAI);
		else
			_hoops_GAPCP (nr, -count, _hoops_IGIC->_hoops_HRIGA, _hoops_IGIC->_hoops_HIAI, false);
	}
	else
		_hoops_RAPCP (nr, -count, _hoops_IGIC->_hoops_HRIGA);
	_hoops_ARPCP (_hoops_IGIC);
}




enum _hoops_AAPCP {
	_hoops_PAPCP = -1,
	_hoops_HAPCP = 0,
	_hoops_IAPCP = 1,
	_hoops_CAPCP = 2
};


/* _hoops_CCRPA 3 _hoops_SCSAA _hoops_RSSA _hoops_HII _hoops_GII _hoops_IIGR _hoops_RH 3 _hoops_SPPR _hoops_IIGR _hoops_IRS _hoops_SCPH _hoops_CRGR
 * _hoops_IRS _hoops_CCAH _hoops_SCPH _hoops_SGS _hoops_SCH _hoops_PSCR _hoops_SAPCP _hoops_GGSR _hoops_CRGR _hoops_RH _hoops_GPPCP */
local void _hoops_RPPCP (
	void *							pass,
	int								fid,
	float							findex, 	// _hoops_SIGRA _hoops_IS _hoops_SGH _hoops_RPP _hoops_HAIR _hoops_GGAR _hoops_HRGR _hoops_IHPPP _hoops_PSAP
	int 							_hoops_HSPI,			// _hoops_PSPI _hoops_IIGR _hoops_RH _hoops_CRIPR _hoops_SCPH'_hoops_GRI _hoops_GRPC
	int 							_hoops_ISPI,
	int 							_hoops_CSPI,
	_hoops_AAPCP 						_hoops_APPCP,			// _hoops_PGAP _hoops_SPPR _hoops_GRR _hoops_IIGR _hoops_RH _hoops_PPPCP _hoops_GRPC _hoops_PGSA _hoops_HII
	_hoops_AAPCP 						_hoops_HPPCP,
	_hoops_AAPCP 						_hoops_IPPCP,
	float							_hoops_CPPCP,			// _hoops_RH _hoops_PRISA _hoops_HSH _hoops_IGIAR _hoops_RH _hoops_CRIPR _hoops_SPPR _hoops_SGS _hoops_RH _hoops_SPPCP
	float							_hoops_HCPSR,			// _hoops_GRPC _hoops_ARHSA */
	float							_hoops_ICPSR) {
	_hoops_RRACP *	data = (_hoops_RRACP *) pass;
	Net_Rendition const & 			nr = data->nr;
	_hoops_GRA const &		_hoops_RRA = nr->_hoops_ARA;
	_hoops_AHAH const &					_hoops_PHAH = _hoops_RRA->_hoops_IHRH;
	Tristrip const *				ts = data->ts;
	_hoops_SGACP alter *					_hoops_IGIC = &data->_hoops_IGIC;
	DC_Point const *				_hoops_GHPCP = data->_hoops_CGCAR;
	_hoops_ARPA const *					planes = data->planes;
	int								i, _hoops_RHPCP = -1, _hoops_AHPCP = -1;
	_hoops_AAPCP							e = _hoops_PAPCP;
	float							t = -1;
	RGB								_hoops_PHPCP;
	RGB								_hoops_HHPCP, _hoops_IHPCP, _hoops_CHPCP;
	RGB const						*_hoops_SHPCP, *_hoops_GIPCP, *color;

	if (data->_hoops_PRACP) {
		_hoops_SHPCP = _hoops_GIPCP = null;  /* _hoops_IS _hoops_SHH _hoops_ACGP _hoops_SPHR */
	}
	else if (data->_hoops_IRACP) {
		_hoops_SHPCP = &data->_hoops_IRACP[fid];
		_hoops_GIPCP = &data->_hoops_CRACP[fid];
	}
	else {
		_hoops_SHPCP = &_hoops_GPSR::_hoops_IAHHP;
		_hoops_GIPCP = null;
	}

	for (i = 0; i < 3; i++) {
		switch (i) {
			case 0:
				e = _hoops_APPCP;
				t = _hoops_CPPCP;
				break;
			case 1:
				e = _hoops_HPPCP;
				t = _hoops_HCPSR;
				break;
			case 2:
				e = _hoops_IPPCP;
				t = _hoops_ICPSR;
				break;
		}
		switch (e) {
			case _hoops_HAPCP:
				_hoops_RHPCP = _hoops_HSPI;
				_hoops_AHPCP = _hoops_ISPI;
				break;
			case _hoops_IAPCP:
				_hoops_RHPCP = _hoops_ISPI;
				_hoops_AHPCP = _hoops_CSPI;
				break;
			case _hoops_CAPCP:
				_hoops_RHPCP = _hoops_CSPI;
				_hoops_AHPCP = _hoops_HSPI;
				t = 1.0f - t;
				break;
			case _hoops_PAPCP: //_hoops_RIPCP
				break;
		}
		if (t < 1) {
			/* _hoops_GGAR */
			float	_hoops_PSRGA = findex;
			_hoops_RSRCP (_hoops_GHPCP[_hoops_RHPCP], _hoops_GHPCP[_hoops_AHPCP], t, _hoops_IGIC->points[0]);
			_hoops_IGIC->points++;
			if (data->_hoops_PAACP) {
				float	_hoops_AIPCP = ts->_hoops_HCHA[_hoops_RHPCP] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate;
				float	f1 = ts->_hoops_HCHA[_hoops_AHPCP] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate;
				_hoops_PSRGA = _hoops_AIPCP + t * (f1 - _hoops_AIPCP);
			}
			_hoops_ICRCP (data->_hoops_CSIR, _hoops_PSRGA, _hoops_CHPCP, data->_hoops_PAACP, _hoops_PHAH);
			color = &_hoops_CHPCP;
			if (data->planes) {
				_hoops_RGRGA (planes[_hoops_RHPCP], planes[_hoops_AHPCP], t, *_hoops_IGIC->planes);
				_hoops_IGIC->planes++;
				*_hoops_IGIC->_hoops_HPHSA = *color;
				_hoops_IGIC->_hoops_HPHSA++;
			}
			if (!_hoops_IGIC->_hoops_HSHCA && i > 0)
				continue; /* _hoops_RGAR _hoops_SPR _hoops_HAIR _hoops_RIR _hoops_SCPH _hoops_RPP _hoops_HAR _hoops_ASISR */
			if (data->_hoops_PRACP) {
				_hoops_PIPCP (data->_hoops_PRACP[_hoops_RHPCP], data->_hoops_PRACP[_hoops_AHPCP], t, _hoops_HHPCP);
				_hoops_PIPCP (data->_hoops_HRACP[_hoops_RHPCP], data->_hoops_HRACP[_hoops_AHPCP], t, _hoops_IHPCP);
				_hoops_SHPCP = &_hoops_HHPCP;
				_hoops_GIPCP = &_hoops_IHPCP;
			}
		}
		else {
			/* _hoops_IPS _hoops_GAR-_hoops_HRGR */
			_hoops_RSAI (&_hoops_GHPCP[_hoops_AHPCP], DC_Point, _hoops_IGIC->points);
			_hoops_IGIC->points++;
			if (data->_hoops_PAACP)
				color = &data->_hoops_SRACP[_hoops_AHPCP];
			else {
				_hoops_ICRCP (data->_hoops_CSIR, findex, _hoops_CHPCP, data->_hoops_PAACP, _hoops_PHAH);
				color = &_hoops_CHPCP;
			}
			if (data->planes) {
				*_hoops_IGIC->planes = planes[_hoops_AHPCP];
				_hoops_IGIC->planes++;
				*_hoops_IGIC->_hoops_HPHSA = *color;
				_hoops_IGIC->_hoops_HPHSA++;
			}
			if (!_hoops_IGIC->_hoops_HSHCA && i > 0)
				continue; /* _hoops_RGAR _hoops_SPR _hoops_HAIR _hoops_RIR _hoops_SCPH _hoops_RPP _hoops_HAR _hoops_ASISR */
			if (data->_hoops_PRACP) {
				_hoops_SHPCP = &data->_hoops_PRACP[_hoops_AHPCP];
				_hoops_GIPCP = &data->_hoops_HRACP[_hoops_AHPCP];
			}
		}

		if (data->_hoops_HAACP) {
		}
		else {
			if (data->_hoops_CRIR) {
				Vector		_hoops_GIHI;
				Point		_hoops_HIPCP;
				_hoops_ARPA		_hoops_IIPCP;
				RGBA		_hoops_CIPCP;

				_hoops_RSRCP (ts->points[_hoops_RHPCP], ts->points[_hoops_AHPCP], t, _hoops_HIPCP);
				if (data->ts->_hoops_ICHA) {
					_hoops_ASRCP (
						data->ts->_hoops_ICHA[_hoops_RHPCP],
						data->ts->_hoops_ICHA[_hoops_AHPCP],
						t,
						_hoops_GIHI);
					HD_Compute_One_World_Plane (nr->transform_rendition->_hoops_IPH,
												&_hoops_GIHI, &data->ts->points[_hoops_RHPCP], &_hoops_IIPCP);
					_hoops_CSACP (nr, nr->_hoops_IHA->_hoops_CHA, data->_hoops_CAACP,
									 &_hoops_HIPCP, color, &_hoops_IIPCP, null, &_hoops_CIPCP, null);
				}
				else {
					_hoops_CSACP (nr, nr->_hoops_IHA->_hoops_CHA, data->_hoops_CAACP,
									 &_hoops_HIPCP, color, null, null, &_hoops_CIPCP, null);
				}
				_hoops_PHPCP.red = _hoops_CIPCP.red;
				_hoops_PHPCP.green = _hoops_CIPCP.green;
				_hoops_PHPCP.blue = _hoops_CIPCP.blue;
			}
			else {
				_hoops_PHPCP.red	= color->red   * _hoops_SHPCP->red;
				_hoops_PHPCP.green = color->green * _hoops_SHPCP->green;
				_hoops_PHPCP.blue	= color->blue  * _hoops_SHPCP->blue;
				if (_hoops_GIPCP) {
					_hoops_PHPCP.red	+= _hoops_GIPCP->red;
					_hoops_PHPCP.green += _hoops_GIPCP->green;
					_hoops_PHPCP.blue	+= _hoops_GIPCP->blue;
					if (_hoops_PHPCP.red > 1)
						_hoops_PHPCP.red = 1;
					if (_hoops_PHPCP.green > 1)
						_hoops_PHPCP.green = 1;
					if (_hoops_PHPCP.blue > 1)
						_hoops_PHPCP.blue = 1;
				}
			}
			_hoops_IGIC->colors[0] = RGBAS32 (_hoops_PHPCP, data->_hoops_IRIR);
			_hoops_SIPCP (nr->_hoops_SRA, _hoops_IGIC->colors[0]);
			_hoops_IGIC->colors++;
		}
	}

	if ((_hoops_IGIC->points - _hoops_IGIC->_hoops_HRIGA) >= _hoops_AGACP) {
		_hoops_IRPCP (nr, _hoops_IGIC);
	}
} /* _hoops_RSGR _hoops_API '_hoops_HPPP _hoops_SPR _hoops_GSAS _hoops_SCPH' */


/* _hoops_CCRPA 2 _hoops_SCSAA _hoops_RSSA _hoops_HII _hoops_GII _hoops_IIGR _hoops_RH 3 _hoops_SPPR _hoops_IIGR _hoops_IRS _hoops_SCPH _hoops_CRGR
 * _hoops_IRS _hoops_III _hoops_SGS _hoops_SCH _hoops_GCPCP _hoops_GGSR _hoops_CRGR _hoops_RH _hoops_IRPR _hoops_HGAGA */
local void _hoops_RCPCP (
	void *							pass,
	int								fid,
	int								index,
	float							findex,
	int 							_hoops_HSPI,
	int 							_hoops_ISPI,
	int 							_hoops_CSPI,
	_hoops_AAPCP 						_hoops_APPCP,
	_hoops_AAPCP 						_hoops_HPPCP,
	float 							_hoops_CPPCP,
	float 							_hoops_HCPSR) {

	//_hoops_RPP ((_hoops_ACPCP < 0.005f || _hoops_ACPCP > 0.995f) && (_hoops_PCPCP < 0.005f || _hoops_PCPCP > 0.995f))
	//	_hoops_ASRC;

	_hoops_RRACP *	data = (_hoops_RRACP *) pass;
	Net_Rendition const &			nr = data->nr;
	Vector const *					_hoops_HCPCP = data->ts->_hoops_ICHA;
	_hoops_ARPA const *					fp = data->ts->_hoops_PRHH;
	Point							points[2];
	Vector							normals[2];

	for (int i = 0; i < 2; i++) {
		int							_hoops_RHPCP = -1, _hoops_AHPCP = -1;
		_hoops_AAPCP						e;
		float						t;

		if (i == 0) {
			e = _hoops_APPCP;		t = _hoops_CPPCP;
		}
		else {
			e = _hoops_HPPCP;		t = _hoops_HCPSR;
		}

		switch (e) {
			case _hoops_HAPCP:
				_hoops_RHPCP = _hoops_HSPI;
				_hoops_AHPCP = _hoops_ISPI;
				break;
			case _hoops_IAPCP:
				_hoops_RHPCP = _hoops_ISPI;
				_hoops_AHPCP = _hoops_CSPI;
				break;
			case _hoops_CAPCP:
				_hoops_RHPCP = _hoops_CSPI;
				_hoops_AHPCP = _hoops_HSPI;
				t = 1.0f - t;
				break;
			case _hoops_PAPCP: //_hoops_PAHA'_hoops_RA _hoops_SHH _hoops_SSRR
				break;
		}

		_hoops_RSRCP (data->_hoops_RAACP[_hoops_RHPCP], data->_hoops_RAACP[_hoops_AHPCP], t, points[i]);
		if (_hoops_HCPCP != null)
			_hoops_ASRCP (_hoops_HCPCP[_hoops_RHPCP], _hoops_HCPCP[_hoops_AHPCP], t, normals[i]);
		else if (fp != null)
			normals[i] = fp[fid];
	}

	if (points[0] != points[1]) {
		_hoops_GGACP *	_hoops_RGIGA = nr->_hoops_SRA->_hoops_GPACP;
		_hoops_ARHGA *			line;

		ALLOC (line, _hoops_ARHGA);
		line->points[0] = points[0];
		line->points[1] = points[1];

		if (_hoops_HCPCP != null) {
			line->_hoops_SSRCP = _hoops_CSRCP;
			line->normals[0] = normals[0];
			line->normals[1] = normals[1];
		}
		else if (fp != null) {
			line->_hoops_SSRCP = _hoops_ISRCP;
			line->normals[0] = normals[0];
			line->normals[1] = normals[1];
		}
		else
			line->_hoops_SSRCP = _hoops_HSRCP;

		if (index >= _hoops_RGIGA->count) {
			int				_hoops_IRCSA = _hoops_RGIGA->count;
			_hoops_IRHGA **	_hoops_ICPCP = _hoops_RGIGA->_hoops_PICHR;
			float *			_hoops_AGRRA = _hoops_RGIGA->findex;

			_hoops_RGIGA->count = index+1;
			ZALLOC_ARRAY (_hoops_RGIGA->_hoops_PICHR, _hoops_RGIGA->count, _hoops_IRHGA *);
			_hoops_AIGA (_hoops_ICPCP, _hoops_IRCSA, _hoops_IRHGA *, _hoops_RGIGA->_hoops_PICHR);
			ZALLOC_ARRAY (_hoops_RGIGA->findex, _hoops_RGIGA->count, float);
			_hoops_AIGA (_hoops_AGRRA, _hoops_IRCSA, float, _hoops_RGIGA->findex);

			FREE_ARRAY (_hoops_ICPCP, _hoops_IRCSA, _hoops_IRHGA *);
			FREE_ARRAY (_hoops_AGRRA, _hoops_IRCSA, float);
		}

		if (_hoops_RGIGA->_hoops_PICHR[index] == null)
			_hoops_RGIGA->_hoops_PICHR[index] = POOL_NEW(data->nr->_hoops_SRA->memory_pool, _hoops_IRHGA)(data->nr->_hoops_SRA->memory_pool);
		_hoops_RGIGA->_hoops_PICHR[index]->AddFirst (line);
		_hoops_RGIGA->findex[index] = findex;
	}
}


local void _hoops_CCPCP (
	void *							pass,
	int 							fid,
	int 							_hoops_HSPI,
	int 							_hoops_ISPI,
	int 							_hoops_CSPI) {
	_hoops_RRACP *	data = (_hoops_RRACP *) pass;
	Net_Rendition const &			nr = data->nr;
	_hoops_GRA const &		_hoops_RRA = nr->_hoops_ARA;
	Display_Context *				dc = (Display_Context *)nr->_hoops_SRA;
	Tristrip const *				ts = data->ts;
	float							findex[3], *findices;
	_hoops_GRCAR const *				_hoops_RRCAR = data->_hoops_RRCAR;

	if (data->_hoops_APH &&
		dc->_hoops_CGHAR &&
		!dc->_hoops_CGHAR[fid])
		return;

	if (_hoops_RRCAR[_hoops_HSPI] & _hoops_RRCAR[_hoops_ISPI] & _hoops_RRCAR[_hoops_CSPI] & ~_hoops_RPCAR)
		return; /* _hoops_HCR 3 _hoops_RSSA _hoops_SACH _hoops_SGGR _hoops_IS _hoops_RH _hoops_PSHR _hoops_PPAP (_hoops_HPPA _hoops_GHC _hoops_GA'_hoops_RA _hoops_RPR) */

	if (data->_hoops_SAACP) {
		_hoops_PC const &		_hoops_SCPCP = nr->_hoops_IHA->_hoops_AGP;

		if (_hoops_SCPCP) {
			data->_hoops_CAACP = _hoops_SCPCP->_hoops_ISPHP ||
							BIT (nr->_hoops_IRR->_hoops_PPH, Rendo_LOCAL_VIEWER) ||
							BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH);
			if (data->_hoops_HAACP)
				data->planes = nr->_hoops_SRA->_hoops_PGPCP;
			else {
				if (!data->_hoops_CRIR) {
					if (ts->_hoops_ICHA) {
						ALLOC_ARRAY (data->_hoops_PRACP, ts->point_count, RGB);
						ALLOC_ARRAY (data->_hoops_HRACP, ts->point_count, RGB);
						_hoops_AGPCP (
										nr, ts,
										nr->_hoops_SRA->_hoops_PGPCP,
										data->_hoops_CAACP,
										data->_hoops_PRACP,
										data->_hoops_HRACP);
					}
					if (ts->_hoops_PRHH) {
						ALLOC_ARRAY (data->_hoops_IRACP, ts->face_count, RGB);
						ALLOC_ARRAY (data->_hoops_CRACP, ts->face_count, RGB);
						_hoops_SGPCP (
										nr, ts,
										dc->_hoops_AIACP,
										data->_hoops_CAACP,
										data->_hoops_IRACP,
										data->_hoops_CRACP);
					}
				}
			}
		}
		data->_hoops_SAACP = false;
	}

	findices = ts->_hoops_HCHA;
	findex[0] = findices[_hoops_HSPI] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate + data->_hoops_HPRCP;
	findex[1] = findices[_hoops_ISPI] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate + data->_hoops_HPRCP;
	findex[2] = findices[_hoops_CSPI] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate + data->_hoops_HPRCP;

	if ((int)findex[0] == (int)findex[1] &&
		(int)findex[1] == (int)findex[2]) {
		float		_hoops_CPRCP = (float)(int)(findex[0] + _hoops_PCRCP) + _hoops_ACRCP;

		_hoops_RPPCP (
				pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
				_hoops_HAPCP, _hoops_IAPCP, _hoops_CAPCP,
				1, 1, 0);
	}
	else {
		/* _hoops_GHIS _hoops_HPP _hoops_SIGRA */
		bool _hoops_AGRCA = false;
		int a = 0, b = 1, c = 2;
		int offset[3];
		float _hoops_GSPCP = -1, _hoops_RSPCP = -1, _hoops_ASPCP = -1;
		float _hoops_PSPCP = -1, _hoops_HSPCP = -1, _hoops_ISPCP = -1;
		float _hoops_CPRCP;
		float _hoops_CSPCP, _hoops_SSPCP, _hoops_GGHCP;

		if (findex[a] > findex[b]) {
			Swap (a, b);
			Swap (_hoops_HSPI, _hoops_ISPI);
			_hoops_AGRCA = !_hoops_AGRCA;
		}
		if (findex[b] > findex[c]) {
			Swap (b, c);
			Swap (_hoops_ISPI, _hoops_CSPI);
			_hoops_AGRCA = !_hoops_AGRCA;
		}
		if (findex[a] > findex[b]) {
			Swap (a, b);
			Swap (_hoops_HSPI, _hoops_ISPI);
			_hoops_AGRCA = !_hoops_AGRCA;
		}
		offset[0] = _hoops_HSPI;
		offset[1] = _hoops_ISPI;
		offset[2] = _hoops_CSPI;

		_hoops_CSPCP = findex[b] - findex[a];
		_hoops_SSPCP = findex[c] - findex[a];
		_hoops_GGHCP = findex[c] - findex[b];
		_hoops_CPRCP = (float)(int)(findex[a] + _hoops_PCRCP) + _hoops_ACRCP;
		_hoops_PSPCP = 1.0f;	/* _hoops_GGR _hoops_AGIR _hoops_SR _hoops_IIP _hoops_CPSA _hoops_GRAS _hoops_SPR */
		_hoops_HSPCP = (_hoops_CPRCP - findex[a]) / _hoops_SSPCP;

		/* _hoops_HSPP _hoops_RH _hoops_RIPS _hoops_PSAP _hoops_CCA _hoops_PGI _hoops_IRS _hoops_SCPH _hoops_PAR _hoops_IRS _hoops_PCPI */
		if (_hoops_CPRCP < findex[b]) {
			_hoops_PSPCP = (_hoops_CPRCP - findex[a]) / _hoops_CSPCP;
			_hoops_RPPCP (
					pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
					_hoops_CAPCP, _hoops_HAPCP, _hoops_CAPCP,
					0, _hoops_PSPCP, _hoops_HSPCP);
			_hoops_CPRCP += 1;
			_hoops_GSPCP = _hoops_PSPCP;
			_hoops_RSPCP = _hoops_HSPCP;
		}
		else {
			if (_hoops_GGHCP > 1e-12f)
				_hoops_ISPCP = (_hoops_CPRCP - findex[b]) / _hoops_GGHCP;
			else
				_hoops_ISPCP = 1;
			_hoops_RPPCP (
					pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
					_hoops_CAPCP, _hoops_CAPCP, _hoops_HAPCP,
					0, _hoops_HSPCP, 1);
			_hoops_RPPCP (
					pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
					_hoops_HAPCP, _hoops_IAPCP, _hoops_CAPCP,
					1, _hoops_ISPCP, _hoops_HSPCP);
			_hoops_CPRCP += 1;
			_hoops_ASPCP = _hoops_ISPCP;
			_hoops_RSPCP = _hoops_HSPCP;
		}

		/* _hoops_GCHGA _hoops_RH _hoops_RIPS _hoops_GH _hoops_IS _hoops_RCSR (_hoops_RPP _hoops_HAR _hoops_IIH _hoops_AIAH) */
		while (_hoops_CPRCP < findex[b]) {
			_hoops_PSPCP = (_hoops_CPRCP - findex[a]) / _hoops_CSPCP;
			_hoops_HSPCP = (_hoops_CPRCP - findex[a]) / _hoops_SSPCP;
			_hoops_RPPCP (
					pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
					_hoops_CAPCP, _hoops_HAPCP, _hoops_CAPCP,
					_hoops_RSPCP, _hoops_GSPCP, _hoops_HSPCP);
			_hoops_RPPCP (
					pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
					_hoops_HAPCP, _hoops_HAPCP, _hoops_CAPCP,
					_hoops_GSPCP, _hoops_PSPCP, _hoops_HSPCP);
			_hoops_GSPCP = _hoops_PSPCP;
			_hoops_RSPCP = _hoops_HSPCP;
			_hoops_CPRCP += 1;
		}

		/* _hoops_HGCR _hoops_IHHH _hoops_ISGR _hoops_RCSR (_hoops_PPR _hoops_GCAS _hoops_RPHR _hoops_GH _hoops_IS _hoops_GSGGR) */
		if (_hoops_CPRCP-1 < findex[b]) {
			if (_hoops_GGHCP > 1e-12f)
				_hoops_ISPCP = (_hoops_CPRCP - findex[b]) / _hoops_GGHCP;
			else
				_hoops_ISPCP = 1;
			_hoops_HSPCP = (_hoops_CPRCP - findex[a]) / _hoops_SSPCP;
			if (_hoops_ISPCP > 1)
				_hoops_ISPCP = 1;
			if (_hoops_HSPCP > 1)
				_hoops_HSPCP = 1;
			_hoops_RPPCP (
					pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
					_hoops_CAPCP, _hoops_CAPCP, _hoops_HAPCP,
					_hoops_RSPCP, _hoops_HSPCP, _hoops_PSPCP);
			_hoops_RPPCP (
					pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
					_hoops_HAPCP, _hoops_CAPCP, _hoops_HAPCP,
					_hoops_PSPCP, _hoops_HSPCP, 1);
			_hoops_RPPCP (
					pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
					_hoops_HAPCP, _hoops_CAPCP, _hoops_IAPCP,
					1, _hoops_HSPCP, _hoops_ISPCP);
			_hoops_ASPCP = _hoops_ISPCP;
			_hoops_RSPCP = _hoops_HSPCP;
			_hoops_CPRCP += 1;
		}
		else {
			if (_hoops_GGHCP > 1e-12f)
				_hoops_ASPCP = (_hoops_CPRCP - findex[b] - 1) / _hoops_GGHCP;
			else
				_hoops_ASPCP = 1;
		}

		/* _hoops_GCHGA _hoops_IS _hoops_GSGGR (_hoops_RPP _hoops_HAR _hoops_IIH _hoops_AIAH) */
		while (_hoops_CPRCP-1 < findex[c]) {
			if (_hoops_CPRCP >= findex[c]) {
				/* _hoops_ACPC _hoops_SCH _hoops_PSAP _hoops_CCA _hoops_IRS _hoops_SCPH */
				_hoops_RPPCP (
						pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
						_hoops_IAPCP, _hoops_CAPCP, _hoops_CAPCP,
						_hoops_ASPCP, _hoops_RSPCP, 1);
				break;
			}
			else {
				/* _hoops_GCHGA _hoops_RH _hoops_RIPS _hoops_CCA _hoops_IRS _hoops_PCPI */
				_hoops_ISPCP = (_hoops_CPRCP - findex[b]) / _hoops_GGHCP;
				_hoops_HSPCP = (_hoops_CPRCP - findex[a]) / _hoops_SSPCP;
				_hoops_RPPCP (
						pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
						_hoops_CAPCP, _hoops_IAPCP, _hoops_CAPCP,
						_hoops_RSPCP, _hoops_ASPCP, _hoops_HSPCP);
				_hoops_RPPCP (
						pass, fid, _hoops_CPRCP-1, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
						_hoops_CAPCP, _hoops_IAPCP, _hoops_IAPCP,
						_hoops_HSPCP, _hoops_ASPCP, _hoops_ISPCP);
			}
			_hoops_ASPCP = _hoops_ISPCP;
			_hoops_RSPCP = _hoops_HSPCP;
			_hoops_CPRCP += 1;
		}
	}
}

local void _hoops_RGHCP (
	void *							pass,
	int 							fid,
	int 							_hoops_HSPI,
	int 							_hoops_ISPI,
	int 							_hoops_CSPI) {
	_hoops_RRACP *	data = (_hoops_RRACP *) pass;
	Net_Rendition const &			nr = data->nr;
	_hoops_GRA const &		_hoops_RRA = nr->_hoops_ARA;
	Tristrip const *				ts = data->ts;
	float							findex[3], *findices;

	findices = ts->_hoops_HCHA;
	findex[0] = findices[_hoops_HSPI] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate;
	findex[1] = findices[_hoops_ISPI] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate;
	findex[2] = findices[_hoops_CSPI] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate;

	if (findex[0] == findex[1] && findex[1] == findex[2]) {
		// _hoops_PSP _hoops_APGR _hoops_RHIR _hoops_RGR _hoops_SCPH
	}
	else {
		/* _hoops_GHIS _hoops_HPP _hoops_SIGRA */
		int			a = 0, b = 1, c = 2;
		float 		_hoops_AGHCP = -1, _hoops_PGHCP = -1, _hoops_HGHCP = -1;
		float 		_hoops_CSPCP, _hoops_SSPCP, _hoops_GGHCP;
		int			offset[3];
		int			index;
		float		_hoops_IGHCP = 1.0f;
		float 		value = 0.0f;

		if (findex[a] > findex[b]) {
			Swap (a, b);
			Swap (_hoops_HSPI, _hoops_ISPI);
		}
		if (findex[b] > findex[c]) {
			Swap (b, c);
			Swap (_hoops_ISPI, _hoops_CSPI);
		}
		if (findex[a] > findex[b]) {
			Swap (a, b);
			Swap (_hoops_HSPI, _hoops_ISPI);
		}
		offset[0] = _hoops_HSPI;
		offset[1] = _hoops_ISPI;
		offset[2] = _hoops_CSPI;

		_hoops_CSPCP = findex[b] - findex[a];
		_hoops_SSPCP = findex[c] - findex[a];
		_hoops_GGHCP = findex[c] - findex[b];

		if (_hoops_RRA->_hoops_ACP._hoops_RSCRP == _hoops_GSCRP) {
			index = 0;
			value = _hoops_RRA->_hoops_ACP._hoops_SIAIR[index] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate;
		}
		else if (_hoops_RRA->_hoops_ACP._hoops_SIAIR != null) {
			index = 0;
			_hoops_IGHCP = _hoops_RRA->_hoops_ACP._hoops_SIAIR[0];
			value = _hoops_RRA->_hoops_ACP._hoops_SIAIR[1];
		}
		else {	// _hoops_PIHGR _hoops_AGIR, _hoops_PAH _hoops_HPGCA _hoops_IAISR (_hoops_HIH _hoops_RRS _hoops_SPR _hoops_ICHRR _hoops_IH _hoops_RH _hoops_CGHCP _hoops_PPS _hoops_GPP _hoops_RH _hoops_SRS _hoops_CPRC)
			index = (int)findex[a] - 1;
			value = (float)index;
		}

#define _hoops_SGHCP() do {												\
			++index;												\
			if (_hoops_RRA->_hoops_ACP._hoops_RSCRP == _hoops_GSCRP) {	\
				if (index >= _hoops_RRA->_hoops_ACP._hoops_CIAIR)			\
					return;											\
				value = _hoops_RRA->_hoops_ACP._hoops_SIAIR[index] *				\
						_hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate;	\
			}														\
			else {													\
				value += _hoops_IGHCP;										\
			}														\
		} while (0)


		// _hoops_HGCR "_hoops_GGGR"
		while (value < findex[a] - 1.0e-5f)
			_hoops_SGHCP();

		// _hoops_RIPS _hoops_RSGR
		if (Abs (value - findex[a]) < 1.0e-5f && findex[a] == findex[b]) {
			_hoops_RCPCP (
				pass, fid, index, value, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
				_hoops_IAPCP, _hoops_CAPCP,
				0.0f, 0.0f);
			_hoops_SGHCP();
		}
		else	// _hoops_CPHR _hoops_CCA "_hoops_GGGR" _hoops_HIS _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_GHCSA _hoops_GRHCP '_hoops_IRS'
			while (value <= findex[a])
				_hoops_SGHCP();

		// _hoops_GCHGA _hoops_GH _hoops_IS _hoops_RCSR
		while (value < findex[b]) {
			_hoops_AGHCP = (value - findex[a]) / _hoops_CSPCP;
			_hoops_PGHCP = (value - findex[a]) / _hoops_SSPCP;
			_hoops_RCPCP (
					pass, fid, index, value, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
					_hoops_HAPCP, _hoops_CAPCP,
					_hoops_AGHCP, _hoops_PGHCP);
			_hoops_SGHCP();
		}

		// _hoops_GCHGA _hoops_IS _hoops_GSGGR
		while (value < findex[c]) {
			_hoops_HGHCP = (value - findex[b]) / _hoops_GGHCP;
			_hoops_PGHCP = (value - findex[a]) / _hoops_SSPCP;
			_hoops_RCPCP (
					pass, fid, index, value, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
					_hoops_IAPCP, _hoops_CAPCP,
					_hoops_HGHCP, _hoops_PGHCP);
			_hoops_SGHCP();
		}

		// _hoops_ISSC _hoops_RSGR
		if (Abs (value - findex[c]) < 1.0e-5f && findex[b] == findex[c]) {
			_hoops_RCPCP (
				pass, fid, index, value, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI,
				_hoops_HAPCP, _hoops_CAPCP,
				1.0f, 1.0f);
		}
	}
}

/* _hoops_RRHCP _hoops_GRHHR _hoops_HRGR _hoops_IS _hoops_ARHCP _hoops_RGR _hoops_IS _hoops_IRS _hoops_GGHSA _hoops_SRPC _hoops_PRHCP
 * _hoops_SGS _hoops_HRHCP _hoops_PAH _hoops_GACC _hoops_SGH. */
local void _hoops_IRHCP (
	Net_Rendition const &		nr,
	Tristrip const *			ts,
	void						(HC_CDECL * triangle_action) (void *info, int fid,
																int _hoops_HSPI, int _hoops_ISPI, int _hoops_CSPI),
	void *						_hoops_CRHCP) {
	_hoops_RRACP *	data = (_hoops_RRACP *) _hoops_CRHCP;
	Display_Context const *		dc = nr->_hoops_SRA;
	int							point_count = ts->point_count;
	int							face_count = ts->face_count;
	int							_hoops_PHHA = ts->_hoops_PHHA;
	int const *					lengths = ts->lengths;
	int const *					_hoops_AIHA = ts->_hoops_AIHA;
	int const *					face_indices = ts->face_indices;
	int							fid = -1;
	int							_hoops_HSPI, _hoops_ISPI, _hoops_CSPI;
	bool						_hoops_CAACP = false;
	bool						_hoops_APH = false;
	bool						_hoops_IAACP, _hoops_HAACP;
	int							_hoops_CRCAR;
	float alter					*ws;
	Bounding					bounding;
	bool						_hoops_SRHCP = dc->_hoops_AIACP != null;
	bool						_hoops_GAHCP = dc->_hoops_CGHAR != null;

	if (ts->_hoops_PHHA == 0)
		return;


	/*_hoops_RPP (_hoops_HSAGA && _hoops_GARI->_hoops_ACHAA < 0)
		_hoops_GARI->_hoops_ACHAA = _hoops_GARI->_hoops_ACHAA;*/

	if (point_count == 0 || face_count == 0) {
		int				index;
		/* _hoops_PPPA _hoops_HIGR _hoops_IS _hoops_CGIC _hoops_RH _hoops_CIAS _hoops_PSHS _hoops_HSH _hoops_IH _hoops_GPHA _hoops_PPR _hoops_HSP _hoops_PSPI. */

		int				length = ts->total;

		while (length-- > 0) {
			if ((index = *_hoops_AIHA++) > point_count)
				point_count = index;

			if (face_indices) {
				if ((index = *face_indices++) > face_count)
					face_count = index;
			}
		}
		_hoops_AIHA = ts->_hoops_AIHA;
		face_indices = ts->face_indices;

		if (face_count == 0 && face_indices == null)
			face_count = ts->total - 2*ts->_hoops_PHHA;

		/* _hoops_AGRP _hoops_CCAH _hoops_HSH _hoops_HII "_hoops_CIAS _hoops_CIHA" _hoops_IS "_hoops_PHI _hoops_IIGR _hoops_PSPI" */
		if (ts->point_count == 0)
			((Tristrip alter *)ts)->point_count = ++point_count;
		if (ts->face_count == 0)
			((Tristrip alter *)ts)->face_count = ++face_count;
	}



	bounding = ts->bounding;
	POOL_ALLOC_ARRAY_ALIGNED (data->_hoops_CGCAR, point_count, DC_Point, 16, dc->memory_pool);
	POOL_ALLOC_ARRAY_ALIGNED (ws, point_count, float, 16, dc->memory_pool);
	POOL_ALLOC_ARRAY (data->_hoops_RRCAR, point_count, _hoops_GRCAR, dc->memory_pool);
	_hoops_CRCAR = HD_Acquire_Clip_Points (nr,
											bounding,
											point_count,
											ts->points,
											(DC_Point *)data->_hoops_CGCAR,
											ws,
											data->_hoops_RRCAR);

	if (_hoops_CRCAR == 0)
		goto _hoops_HPAGR;

	if (dc->_hoops_APHHP == null) {
		_hoops_APH = BIT (nr->transform_rendition->flags, _hoops_IGSP) &&
					ANYBIT (nr->transform_rendition->heuristics,_hoops_RSA);
		_hoops_IAACP = BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GSRC) &&
			   nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR;
		_hoops_HAACP = BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA);

		/* _hoops_RHI _hoops_GCA _hoops_RAHCP */
		if (_hoops_IAACP && nr->_hoops_IHA->_hoops_CHA->texture[_hoops_RIA])
			_hoops_HAACP = true;

		if (ts->_hoops_ICHA != null || _hoops_HAACP ||
			(ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_CCHA || _hoops_IAACP) && !ts->_hoops_PRHH) {
			Display_Context alter *		_hoops_AAHCP = (Display_Context alter *)nr->_hoops_SRA;

			if (_hoops_AAHCP->_hoops_PAHCP < ts->point_count) {
				if (_hoops_AAHCP->_hoops_PGPCP)
					FREE_ARRAY (_hoops_AAHCP->_hoops_PGPCP, _hoops_AAHCP->_hoops_PAHCP, _hoops_ARPA);
				_hoops_AAHCP->_hoops_PAHCP = ts->point_count;
				POOL_ALLOC_ARRAY_CACHED (_hoops_AAHCP->_hoops_PGPCP, _hoops_AAHCP->_hoops_PAHCP, _hoops_ARPA, _hoops_AAHCP->memory_pool);
			}

			if (ts->_hoops_ICHA == null)
				ZERO_ARRAY (dc->_hoops_PGPCP, ts->point_count, _hoops_ARPA);
			else
				HD_Compute_World_Vertex_Planes (nr, ts->point_count,
												ts->points, ts->_hoops_ICHA,
												dc->_hoops_PGPCP);
		}
		else if (ts->_hoops_PRHH) {
			if (dc->_hoops_AIACP == null)
				_hoops_GIACP (nr, (Tristrip alter *)ts);
		}

		if (ts->_hoops_ICHA != null || ts->_hoops_PRHH != null) {
			_hoops_PC const &		_hoops_SCPCP = nr->_hoops_IHA->_hoops_AGP;

			if (_hoops_SCPCP)
				_hoops_CAACP = _hoops_SCPCP->_hoops_ISPHP ||
								BIT (nr->_hoops_IRR->_hoops_PPH, Rendo_LOCAL_VIEWER) ||
								BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH);
		}
	}

	if (_hoops_APH) {
		if (dc->_hoops_CGHAR == null)
			_hoops_PCACP (nr, ts, face_count);
	}

	while (_hoops_PHHA-- > 0) {
		int			length = *lengths++;
		int			_hoops_SICPR = false;
		bool		_hoops_AGRCA = false;

		if (length < 0) {		/* _hoops_HAHCP */
			length = -length;
			_hoops_SICPR = true;
		}

		_hoops_HSPI = *_hoops_AIHA++;
		_hoops_ISPI = *_hoops_AIHA++;
		length -= 2;

		if (face_indices != null)
			face_indices += 2;

		while (length-- > 0) {
			_hoops_CSPI = *_hoops_AIHA++;
			if (face_indices != null)
				fid = *face_indices++;
			else
				fid++;

			if (_hoops_AGRCA)
				(*triangle_action) (_hoops_CRHCP, fid, _hoops_HSPI, _hoops_CSPI, _hoops_ISPI);
			else
				(*triangle_action) (_hoops_CRHCP, fid, _hoops_HSPI, _hoops_ISPI, _hoops_CSPI);

			if (!_hoops_SICPR) {
				_hoops_HSPI = _hoops_ISPI;
				_hoops_AGRCA = !_hoops_AGRCA;
			}
			_hoops_ISPI = _hoops_CSPI;
		}

		/* _hoops_GAPA _hoops_CRPHR _hoops_CGH _hoops_SHH _hoops_IRS _hoops_RIRA _hoops_GHIR _hoops_IS _hoops_ISPR _hoops_SSHGR */
		if (_hoops_GGPGR(nr))
			break; /* _hoops_HRGHP */
	}

  _hoops_HPAGR:
	/*
		_hoops_RPP (_hoops_GARI->_hoops_IAHCP != _hoops_IRAP)
			_hoops_CAHCP (_hoops_GARI->_hoops_IAHCP, _hoops_ACHAA, _hoops_SPGGR, 16);
	}*/
	if (dc->_hoops_AIACP != null && !_hoops_SRHCP) {
		Display_Context alter *		_hoops_AAHCP = (Display_Context alter *)dc;

		FREE_ARRAY_ALIGNED (_hoops_AAHCP->_hoops_AIACP, dc->_hoops_PIACP, _hoops_ARPA, 16);
		_hoops_AAHCP->_hoops_AIACP = null;
		_hoops_AAHCP->_hoops_PIACP = 0;
	}
	if (dc->_hoops_CGHAR != null && !_hoops_GAHCP) {
		Display_Context alter *		_hoops_AAHCP = (Display_Context alter *)dc;

		FREE_ARRAY_ALIGNED (_hoops_AAHCP->_hoops_CGHAR, dc->_hoops_ICACP, int, 16);
		_hoops_AAHCP->_hoops_CGHAR = null;
		_hoops_AAHCP->_hoops_ICACP = 0;
	}

	FREE_ARRAY_ALIGNED (data->_hoops_CGCAR, point_count, DC_Point, 16);
	FREE_ARRAY_ALIGNED (ws, point_count, float, 16);
	FREE_ARRAY (data->_hoops_RRCAR, point_count, _hoops_GRCAR);
} /* _hoops_RSGR _hoops_API '_hoops_SAHCP _hoops_GPHCP _hoops_CRHH' */


GLOBAL_FUNCTION void HD_Draw_Indexicated_3D_Tristrip (
	Net_Rendition const &			nr,
	Tristrip const *				ts) {
	Display_Context alter *			dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_RRACP *	data;

	dc->_hoops_GSGC |= _hoops_SSCI;

#ifndef DISABLE_EXTENDED_TEXTURE
	if (ANYBIT (nr->current, _hoops_GSSHP | _hoops_RSSHP) &&
		!ALLBITS (nr->_hoops_IRR->_hoops_CSA, _hoops_HCSI) &&
		!ts->_hoops_GSSH->_hoops_GSHA) {
		Tristrip alter *	_hoops_IPIAR = (Tristrip alter *)ts;
		_hoops_RCR alter *		txr = HI_Clone_Texture(0);

		txr->_hoops_CGA = _hoops_ASGRP;
		if (ts->_hoops_RPRCP)
			txr->_hoops_PSCC = _hoops_HSGRP;
		else
			txr->_hoops_PSCC = _hoops_HSCC;

		txr->image = HI_Create_Indexication_Image (nr);

		Net_Rendition				_hoops_CRAI = nr.Copy();
		_hoops_CIGA alter &		_hoops_CPIHP = _hoops_CRAI->_hoops_IHA.Modify();
		_hoops_HHA alter &	_hoops_GGHHP = _hoops_CPIHP->_hoops_CHA.Modify();
		_hoops_CPIHP->_hoops_GIA = _hoops_GGHHP;
		HI_Free_Diffuse_Channel_List (_hoops_GGHHP->_hoops_SCA);
		_hoops_GGHHP->_hoops_SCA = HI_New_Diffuse_Channel (txr);
		_hoops_GGHHP->_hoops_ARIR = true;

		if (_hoops_IPIAR->_hoops_GSSH != null && _hoops_ISAI (_hoops_IPIAR->_hoops_GSSH) == 0)
			HI_Free_Texture_Parameters (_hoops_IPIAR->_hoops_GSSH);

		_hoops_RSSH *		_hoops_RPHCP;
		ALLOC_ARRAY_CACHED (_hoops_RPHCP, _hoops_IPIAR->point_count*2, _hoops_RSSH);

		ZALLOC (_hoops_IPIAR->_hoops_GSSH, _hoops_RRCC);
		_hoops_ICAI (_hoops_IPIAR->_hoops_GSSH);
		_hoops_IPIAR->_hoops_GSSH->_hoops_CCHA = _hoops_RPHCP;
		_hoops_IPIAR->_hoops_GSSH->_hoops_SCAI = _hoops_ARCC;
		_hoops_IPIAR->_hoops_GSSH->_hoops_CGAHR = _hoops_IPIAR->point_count;
		_hoops_IPIAR->_hoops_GSSH->_hoops_GSHA = 2;

		_hoops_RSSH *		_hoops_APHCP = _hoops_RPHCP;
		_hoops_RSSH *		_hoops_HRHRA = _hoops_APHCP + _hoops_IPIAR->point_count * 2;
		_hoops_RSSH *		_hoops_PPHPA = _hoops_IPIAR->_hoops_HCHA;
		float			_hoops_PPHCP = 1.0f / nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->length;

		while (_hoops_APHCP < _hoops_HRHRA) {
			*_hoops_APHCP++ = (*_hoops_PPHPA + 0.5f) * _hoops_PPHCP;
			*_hoops_APHCP++ = 0;
			_hoops_PPHPA++;
		}

		_hoops_HPHCP (_hoops_CRAI, _hoops_IPIAR);

		_hoops_HPRH (txr);
		return;
	}
#endif

	ZALLOC (data, _hoops_RRACP);
	data->nr = nr;
	data->ts = ts;
	data->_hoops_AAACP = (ts->_hoops_ICHA != null);
	data->_hoops_PAACP = ts->_hoops_RPRCP;
	_hoops_PRPCP (&data->_hoops_IGIC, ts->_hoops_GSSH->_hoops_GSHA);
	data->_hoops_IGIC._hoops_HSHCA = (data->_hoops_AAACP || data->_hoops_PAACP);
	data->_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;

	if (!data->_hoops_PAACP)
		data->_hoops_HPRCP = 0.5f;
	else
		data->_hoops_SRACP = _hoops_PHACP (nr, ts, data->_hoops_HPRCP);
	data->_hoops_CRIR = BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH);
	data->_hoops_HAACP = BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA);
	data->_hoops_IAACP = BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GSRC) &&
			   nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR;
	data->_hoops_APH = BIT (nr->transform_rendition->flags, _hoops_IGSP);
	data->_hoops_IRIR = (unsigned char)(255.99f * nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR);
	data->_hoops_SAACP = true;
	_hoops_IRHCP (nr, ts, _hoops_CCPCP, data);
	_hoops_IRPCP (nr, &data->_hoops_IGIC);
	_hoops_HRPCP (&data->_hoops_IGIC);
	if (data->_hoops_IRACP)
		FREE_ARRAY (data->_hoops_IRACP, ts->face_count, RGB);
	if (data->_hoops_CRACP)
		FREE_ARRAY (data->_hoops_CRACP, ts->face_count, RGB);
	if (data->_hoops_PRACP)
		FREE_ARRAY (data->_hoops_PRACP, ts->point_count, RGB);
	if (data->_hoops_HRACP)
		FREE_ARRAY (data->_hoops_HRACP, ts->point_count, RGB);
	if (data->_hoops_SRACP)
		FREE_ARRAY (data->_hoops_SRACP, ts->point_count, RGB);
	data->nr.release();
	FREE (data, _hoops_RRACP);
}

GLOBAL_FUNCTION void HD_Isoline_From_Tristrip (
	Net_Rendition const &			nr,
	Tristrip const *				ts) {
	Display_Context alter *			dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_RRACP *	data;

	ZALLOC (data, _hoops_RRACP);
	data->nr = nr;
	data->ts = ts;
	data->_hoops_RAACP = ts->points;
	data->_hoops_APH = false;

	if (dc->_hoops_GPACP == null) {
		int			length = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->length;

		ALLOC (dc->_hoops_GPACP, _hoops_GGACP);
		dc->_hoops_GPACP->count = length;
		ZALLOC_ARRAY (dc->_hoops_GPACP->_hoops_PICHR, length, _hoops_IRHGA *);
		ZALLOC_ARRAY (dc->_hoops_GPACP->findex, length, float);
	}

	_hoops_IRHCP (nr, ts, _hoops_RGHCP, data);
	data->nr.release();
	FREE (data, _hoops_RRACP);
}
