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
 * $Id: obf_tmp.txt 1.238 2010-11-19 00:48:32 covey Exp $
 */
#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hi_proto.h"
#include "hpserror.h"


static	float	_hoops_SCPHR = 0.0f;		/* _hoops_IH _hoops_GSPHR, _hoops_IHRI _hoops_IS _hoops_SHH _hoops_RSPHR _hoops_PRGI _hoops_IH _hoops_ASPHR */
static	int		_hoops_PSPHR = 0;
static	float	_hoops_HSPHR[] = {0.5f, 0.3f, 0.7f};
static	float	_hoops_ISPHR[] = {1.0f, 0.6f, 0.6f};


#define _hoops_CSPHR		-1


typedef short	_hoops_SSPHR;
#define _hoops_GGHHR			(_hoops_SSPHR)0
#define _hoops_RGHHR			(_hoops_SSPHR)1
#define _hoops_AGHHR			(_hoops_SSPHR)2


#define _hoops_PGHHR 5000
#define _hoops_HGHHR 10

//_hoops_SR _hoops_GSGI _hoops_SGS _hoops_IGHHR _hoops_GH _hoops_ARHAR _hoops_HSP _hoops_ASGA _hoops_RRGPR _hoops_IS _hoops_IRAA _hoops_IRS _hoops_AHCPR _hoops_IIGR _hoops_GHIR 
//_hoops_IH _hoops_APPR _hoops_SCHS (_hoops_PAHH _hoops_PGGA _hoops_IIGR _hoops_IHAH _hoops_CGHHR).  _hoops_CGP _hoops_IIH _hoops_CHR _hoops_HAH _hoops_AHPH
//_hoops_ARHAR _hoops_HSP _hoops_ASGA, _hoops_GA'_hoops_RA _hoops_SGHHR _hoops_IS _hoops_CCIH _hoops_CAPR (_hoops_PPR _hoops_GRHHR _hoops_SGS _hoops_SSIA _hoops_PPPPR'_hoops_RA _hoops_SHH
//_hoops_SIGR _hoops_PGGA _hoops_IIGR _hoops_HHHA _hoops_GPHA _hoops_ASGA)  _hoops_CACH _hoops_AGIR [#10826]
#define _hoops_RRHHR  2048

// "_hoops_ARHHR" = "_hoops_IISR-_hoops_ARCPR-_hoops_CSRHR"

struct _hoops_PRHHR;

struct _hoops_HRHHR {
	_hoops_HRHHR				*next;
	_hoops_PRHHR			*_hoops_IRHHR,
							*_hoops_CRHHR;
	int						vertex1,
							vertex2;
	int						_hoops_SRHHR;
	bool					_hoops_GAHHR;
	bool					_hoops_RAHHR;
	_hoops_SSPHR				_hoops_AAHHR,
							_hoops_PAHHR;
};


struct _hoops_PRHHR {	/* _hoops_SHR _hoops_IRS _hoops_SCPH (_hoops_PRAR, _hoops_PGIPR _hoops_IRS _hoops_PCPI...) */
	_hoops_HRHHR				*_hoops_HAHHR,
							*_hoops_IAHHR,
							*_hoops_CAHHR;
	_hoops_HRHHR				*_hoops_SAHHR;
	int						face;
	/* _hoops_GPHHR _hoops_IH _hoops_PRCA _hoops_ARHAR _hoops_HSP _hoops_ASGA */
	_hoops_PRHHR			*next;
	_hoops_PRHHR			**backlink;
};


struct _hoops_RPHHR {
	_hoops_RPHHR		*_hoops_CGHPR,
							*_hoops_SGHPR,
							*up;
	_hoops_RPHHR		*_hoops_GRHPR;

	int						*_hoops_APHHR,
							*_hoops_PPHHR,
							_hoops_HPHHR,
							_hoops_IPHHR;
	int						_hoops_ISPI,
							_hoops_CSPI;

	One_Face_Attributes		face_attributes; /* (_hoops_CGHI _hoops_GGR _hoops_AGIR _hoops_PISC _hoops_SPCC) */
};

struct _hoops_CPHHR {
	Shell					*_hoops_SPHPR;
	_hoops_HRHHR				**_hoops_SPHHR;
	_hoops_PRHHR			*_hoops_GHHHR;

	int						*_hoops_SRSPR;
	_hoops_RPHHR		*temps;

	int						_hoops_GASPR;
	int						_hoops_RHHHR,
							_hoops_AHHHR;
	int						_hoops_PHHHR;
	int						_hoops_HHHHR;
	int						_hoops_IHHHR;
	int						_hoops_CHHHR;
	int						_hoops_SHHHR;
	bool					_hoops_GIHHR;
	bool					_hoops_RIHHR;
	bool					_hoops_AIHHR;
};


/*
 * _hoops_IPCP _hoops_PIHHR _hoops_IIGR *8 _hoops_HRGR _hoops_PGGA _hoops_RH _hoops_GASR _hoops_SIAS _hoops_SHH _hoops_GAHPR _hoops_APPR _hoops_HSAR _hoops_RH
 * _hoops_HIHHR _hoops_IIGR _hoops_IIHHR+_hoops_CIHHR.
 */
#define _hoops_SIHHR(_hoops_ISPI, _hoops_CSPI)	(((_hoops_ISPI)+(_hoops_CSPI)) ^ ((_hoops_ISPI) * 8))

local _hoops_HRHHR * _hoops_GCHHR (
	_hoops_CPHHR		*info,
	_hoops_PRHHR	*_hoops_RCHHR,
	int				_hoops_ACHHR,
	int				_hoops_PCHHR,
	int				_hoops_SRHHR) {
	_hoops_HRHHR		*edge,
					**_hoops_ASRGR;
	int				_hoops_ISPI,
					_hoops_CSPI;
	bool			_hoops_HCHHR = false;

	if (_hoops_ACHHR < _hoops_PCHHR) {
		_hoops_ISPI = _hoops_ACHHR;
		_hoops_CSPI = _hoops_PCHHR;
	}
	else {
		_hoops_ISPI = _hoops_PCHHR;
		_hoops_CSPI = _hoops_ACHHR;
	}

	_hoops_ASRGR = &info->_hoops_SPHHR [_hoops_SIHHR (_hoops_ISPI, _hoops_CSPI) &
								info->_hoops_AHHHR];

	/*
	 * _hoops_HGI _hoops_PCPH _hoops_ICHHR _hoops_IIHHR < _hoops_CIHHR _hoops_IS _hoops_ACHPR _hoops_GH _hoops_RH _hoops_CCHHR-_hoops_HIGR _hoops_SCHHR
	 * _hoops_RPPR. _hoops_IPCP _hoops_CCHHR _hoops_HIGR _hoops_HRGR _hoops_GSHHR _hoops_HPP _hoops_ISHA->_hoops_RSHHR _hoops_PPR _hoops_PSCR _hoops_ASHHR.
	 * _hoops_PSHHR _hoops_RGR _hoops_HAPR _hoops_IRS _hoops_RSCA _hoops_PISC.
	 */

	while ((edge = *_hoops_ASRGR) != null) {
		if (_hoops_ISPI >= edge->vertex1) {
			while (_hoops_ISPI == edge->vertex1) {
				if (_hoops_CSPI >= edge->vertex2) {
					while (_hoops_CSPI == edge->vertex2) {
						/* _hoops_GGHP _hoops_IRS _hoops_PSSP! */

						if (edge->_hoops_CRHHR != null) {
							info->_hoops_RIHHR = true;
						}
						else if (edge->_hoops_GAHHR	 && edge->vertex1 == _hoops_PCHHR ||
								 !edge->_hoops_GAHHR && edge->vertex1 == _hoops_ACHHR) {
							/*
							 * _hoops_AIAP _hoops_HSHHR _hoops_IS _hoops_SHH _hoops_RH _hoops_HAGA _hoops_IIGR
							 * _hoops_ISHHR _hoops_CSHHR
							 */
							if (edge->_hoops_SRHHR >= _hoops_SRHHR)
								edge->_hoops_CRHHR = _hoops_RCHHR;
							else {
								edge->_hoops_CRHHR = edge->_hoops_IRHHR;
								edge->_hoops_IRHHR = _hoops_RCHHR;
							}

							edge->_hoops_SRHHR += _hoops_SRHHR;
							if (edge->_hoops_SRHHR > info->_hoops_SHHHR)
								info->_hoops_SHHHR = edge->_hoops_SRHHR;

							if (_hoops_HCHHR) {
								info->_hoops_RIHHR = true;
								info->_hoops_GIHHR = true;
							}

							return edge;
						}

						/* _hoops_SR [_hoops_GRS] _hoops_HS _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_RRI _hoops_ISHA _hoops_CCA _hoops_IIHHR & _hoops_CIHHR */
						_hoops_HCHHR = true;

						_hoops_ASRGR = &edge->next;
						if ((edge = *_hoops_ASRGR) == null) break;
						if (_hoops_ISPI != edge->vertex1) break;
					}
					break;
				}

				_hoops_ASRGR = &edge->next;
				if ((edge = *_hoops_ASRGR) == null) break;
			}
			break;
		}

		_hoops_ASRGR = &edge->next;
	}

	info->_hoops_GIHHR |= _hoops_HCHHR;

	ALLOC (edge, _hoops_HRHHR);
	edge->next = *_hoops_ASRGR;
	*_hoops_ASRGR = edge;
	edge->_hoops_IRHHR = _hoops_RCHHR;
	edge->_hoops_CRHHR = null;
	edge->vertex1 = _hoops_ISPI;
	edge->vertex2 = _hoops_CSPI;
	edge->_hoops_SRHHR = _hoops_SRHHR;
	edge->_hoops_GAHHR = (_hoops_ISPI == _hoops_ACHHR);
	edge->_hoops_RAHHR = false;
	edge->_hoops_AAHHR = _hoops_GGHHR;
	edge->_hoops_PAHHR = _hoops_GGHHR;
	++info->_hoops_CHHHR;

	return edge;
}

local void _hoops_CSHPR (_hoops_RPHHR *_hoops_AGPHR, _hoops_RPHHR **_hoops_SSHPR);

local void _hoops_SSHHR (
	_hoops_CPHHR				*info,
	int						count,
	Integer32 const			*v) {
	_hoops_RPHHR		*_hoops_AGPHR;
	Local_Face_Attributes	*_hoops_CPRI = null;
	int						*_hoops_SRSPR = info->_hoops_SRSPR;

	ALLOC (_hoops_AGPHR, _hoops_RPHHR);
	_hoops_AAPHR (_hoops_AGPHR->face_attributes);

	if (info->_hoops_SPHPR != null)
		_hoops_CPRI = &info->_hoops_SPHPR->local_face_attributes;
	if (_hoops_CPRI != null && _hoops_CPRI->flags != null)
		_hoops_PIPHR (_hoops_CPRI, info->_hoops_PHHHR, _hoops_AGPHR->face_attributes);

	_hoops_AGPHR->_hoops_APHHR = info->_hoops_SRSPR;
	_hoops_AGPHR->_hoops_ISPI = v[0];
	_hoops_AGPHR->_hoops_CSPI = v[1];
	for (int i=2; i<count; i++) {
		if ((i & 1) == 0)
			*_hoops_SRSPR++ = v[count - i/2];
		else
			*_hoops_SRSPR++ = v[(i+1)/2];

		*_hoops_SRSPR++ = info->_hoops_PHHHR;
	}
	_hoops_AGPHR->_hoops_HPHHR = (_hoops_SRSPR - _hoops_AGPHR->_hoops_APHHR)/2;

	_hoops_AGPHR->_hoops_PPHHR = null;
	_hoops_AGPHR->_hoops_IPHHR = 0;

	_hoops_CSHPR (_hoops_AGPHR, &info->temps);
}

local void _hoops_GGIHR (
	_hoops_CPHHR				*info,
	Integer32				_hoops_HSPI,
	Integer32				_hoops_ISPI,
	Integer32				_hoops_CSPI) {
	_hoops_RPHHR		*_hoops_AGPHR;
	Local_Face_Attributes	*_hoops_CPRI = null;
	int						*_hoops_SRSPR = info->_hoops_SRSPR;

	ALLOC (_hoops_AGPHR, _hoops_RPHHR);
	_hoops_AAPHR (_hoops_AGPHR->face_attributes);

	if (info->_hoops_SPHPR != null)
		_hoops_CPRI = &info->_hoops_SPHPR->local_face_attributes;
	if (_hoops_CPRI != null && _hoops_CPRI->flags != null)
		_hoops_PIPHR (_hoops_CPRI, info->_hoops_PHHHR, _hoops_AGPHR->face_attributes);

	_hoops_AGPHR->face_attributes.flags |= _hoops_RGIHR;

	_hoops_AGPHR->_hoops_APHHR = info->_hoops_SRSPR;
	_hoops_AGPHR->_hoops_ISPI = _hoops_HSPI;
	_hoops_AGPHR->_hoops_CSPI = _hoops_ISPI;
	*_hoops_SRSPR++ = _hoops_CSPI;
	*_hoops_SRSPR++ = info->_hoops_PHHHR;
	_hoops_AGPHR->_hoops_HPHHR = (_hoops_SRSPR - _hoops_AGPHR->_hoops_APHHR)/2;

	_hoops_AGPHR->_hoops_PPHHR = null;
	_hoops_AGPHR->_hoops_IPHHR = 0;

	_hoops_CSHPR (_hoops_AGPHR, &info->temps);
}


local void _hoops_AGIHR (
	void			*_hoops_PGIHR,
	Integer32		_hoops_HAPH,
	Integer32		_hoops_ISPI,
	Integer32		_hoops_CSPI,
	Integer32		_hoops_SSPI) {
	_hoops_PRHHR	*_hoops_RCHHR;
	_hoops_CPHHR		*info = (_hoops_CPHHR *)_hoops_PGIHR;

	if (_hoops_ISPI == _hoops_CSPI || _hoops_ISPI == _hoops_SSPI || _hoops_CSPI == _hoops_SSPI) {
		if (info->_hoops_SPHPR != null)
			_hoops_GGIHR (info, _hoops_ISPI, _hoops_CSPI, _hoops_SSPI);
		return;
	}

	ALLOC (_hoops_RCHHR, _hoops_PRHHR);
	ZERO_STRUCT (_hoops_RCHHR, _hoops_PRHHR);
	_hoops_RCHHR->face = info->_hoops_PHHHR;

	if (!_hoops_HAPH) {
		_hoops_RCHHR->_hoops_HAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_SSPI, (int)_hoops_ISPI, 1);
		_hoops_RCHHR->_hoops_IAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_ISPI, (int)_hoops_CSPI, 1);
		_hoops_RCHHR->_hoops_CAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_CSPI, (int)_hoops_SSPI, 1);
	}
	else if (!BIT (info->_hoops_IHHHR, 1)) {
		_hoops_RCHHR->_hoops_HAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_ISPI, (int)_hoops_CSPI,
									  info->_hoops_HHHHR - info->_hoops_IHHHR);
		_hoops_RCHHR->_hoops_IAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_CSPI, (int)_hoops_SSPI, 1);
		_hoops_RCHHR->_hoops_CAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_SSPI, (int)_hoops_ISPI, 2);
		++info->_hoops_IHHHR;
	}
	else {
		++info->_hoops_IHHHR;
		_hoops_RCHHR->_hoops_HAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_SSPI, (int)_hoops_ISPI, 1);
		_hoops_RCHHR->_hoops_IAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_ISPI, (int)_hoops_CSPI, 2);
		_hoops_RCHHR->_hoops_CAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_CSPI, (int)_hoops_SSPI,
									  info->_hoops_IHHHR);
	}

	if (info->_hoops_SPHPR != null &&
		info->_hoops_SPHPR->local_face_attributes.normals != null && 
		info->_hoops_AIHHR) {
		_hoops_ARPA *					normals = info->_hoops_SPHPR->local_face_attributes.normals;

		/* _hoops_RPP _hoops_RGR _hoops_GSSR _hoops_HRGR _hoops_ARHAR, _hoops_PRIA _hoops_RH _hoops_SCPH _hoops_IS _hoops_HGIHR _hoops_GH _hoops_SPHR */
		if (normals[_hoops_RCHHR->face].a == 0.0f &&
			normals[_hoops_RCHHR->face].b == 0.0f &&
			normals[_hoops_RCHHR->face].c == 0.0f) {
			if ((_hoops_RCHHR->next = info->_hoops_GHHHR) != null)
				_hoops_RCHHR->next->backlink = &_hoops_RCHHR->next;
			_hoops_RCHHR->backlink = &info->_hoops_GHHHR;
			info->_hoops_GHHHR = _hoops_RCHHR;
		}
	}
}

local void _hoops_IGIHR (
	_hoops_CPHHR		*info,
	Integer32		_hoops_ISPI,
	Integer32		_hoops_CSPI,
	Integer32		_hoops_SSPI,
	Integer32		_hoops_SGHI) {
	_hoops_PRHHR	*_hoops_RCHHR;


	ALLOC (_hoops_RCHHR, _hoops_PRHHR);
	_hoops_RCHHR->face = info->_hoops_PHHHR;

	_hoops_RCHHR->_hoops_HAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_ISPI, (int)_hoops_CSPI, 3);
	_hoops_RCHHR->_hoops_IAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_CSPI, (int)_hoops_SSPI, 2);
	_hoops_RCHHR->_hoops_CAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_SSPI, (int)_hoops_SGHI, 3);
	_hoops_RCHHR->_hoops_SAHHR = _hoops_GCHHR (info, _hoops_RCHHR, (int)_hoops_SGHI, (int)_hoops_ISPI, 2);
}


local float _hoops_CGIHR (
	_hoops_CPHHR const *			info,
	_hoops_HRHHR const *			edge) {
	Point const *				p1 = &info->_hoops_SPHPR->points[edge->vertex1];
	Point const *				p2 = &info->_hoops_SPHPR->points[edge->vertex2];
	Vector						delta;

	delta.x = p2->x - p1->x;
	delta.y = p2->y - p1->y;
	delta.z = p2->z - p1->z;

	return _hoops_SGIHR (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}

local void _hoops_GRIHR (
	Point const *		points,
	int					face_list_length,
	int const *			face_list,
	int const *			face_mapping,
	_hoops_ARPA const *		_hoops_PRHH,
	int const			**_hoops_RRIHR,
	int					limit,
	_hoops_CPHHR			*info) {
	int const			*item;
	int const			*_hoops_CRRHR;
	int const			*global_end;
	_hoops_GIIPR	*_hoops_RIIPR;
	_hoops_ARPA const			*_hoops_HRAHR = null;
	int					_hoops_ARIHR = 1;
	int					i = 0;

	item = *_hoops_RRIHR;
	global_end = face_list + face_list_length;

	_hoops_RIIPR = null;

	info->_hoops_PHHHR = -1;
	do {
		if (face_mapping)
			info->_hoops_PHHHR = face_mapping[i++];
		else
			++info->_hoops_PHHHR;

		if (_hoops_PRHH != null)
			_hoops_HRAHR = &_hoops_PRHH[info->_hoops_PHHHR];

		_hoops_CRRHR = item + 1 + *item;

		/* _hoops_HSGR _hoops_ISGR _hoops_ARAH-_hoops_RSSI */
		while (_hoops_CRRHR != global_end && *_hoops_CRRHR < 0)
			_hoops_CRRHR += 1 - *_hoops_CRRHR;

		info->_hoops_IHHHR = 0;
		info->_hoops_HHHHR = *item - 1;		/* _hoops_RGAR _hoops_IGI _hoops_RPP _hoops_SGCS */

		if (*item == 3 && _hoops_CRRHR-item == 4)
			_hoops_AGIHR ((void *)info, true,
							  item[1], item[2], item[3]);
		else if (*item == 4 && _hoops_CRRHR-item == 5 &&
				 !BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_PRIHR) &&
				 HI_Rank_Polygon (points, item, _hoops_CRRHR) == _hoops_HRIHR)
			_hoops_IGIHR (info,
						  item[1], item[2], item[3], item[4]);
		else if (*item == 6 && _hoops_CRRHR-item == 7 &&
				 BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_IRIHR)) {
			_hoops_AGIHR ((void *)info, false,
							  item[1], item[2], item[6]);
			_hoops_AGIHR ((void *)info, false,
							  item[3], item[4], item[2]);
			_hoops_AGIHR ((void *)info, false,
							  item[5], item[6], item[4]);
			_hoops_AGIHR ((void *)info, false,
							  item[2], item[4], item[6]);
		}
		else if (BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_CRIHR) &&
				 *item > 3 && _hoops_CRRHR-item == *item+1 &&
				 HI_Rank_Polygon (points, item, _hoops_CRRHR) == _hoops_HRIHR)
			_hoops_SSHHR (info, *item, item+1);
#if 1
		else if (*item == 2 && _hoops_CRRHR-item == 3 && info->_hoops_SPHPR != null) {
			_hoops_GGIHR (info, item[1], item[2], item[2]);
		}
#endif
		else
			HI_Triangulate_Face (points, (Vector*)_hoops_HRAHR,
								 item, _hoops_CRRHR,
								 _hoops_AGIHR, (void *)info);

		item = _hoops_CRRHR;
	} _hoops_RGGA (--limit == 0 || item == global_end);

	while (info->_hoops_GHHHR != null && _hoops_ARIHR < 4) {
		while (info->_hoops_GHHHR != null) {
			_hoops_ARPA *						normals = info->_hoops_SPHPR->local_face_attributes.normals;
			_hoops_PRHHR *				_hoops_RCHHR;
			_hoops_PRHHR *				_hoops_SRIHR = null;
			bool						_hoops_GAIHR = false;

			while ((_hoops_RCHHR = info->_hoops_GHHHR) != null) {
				_hoops_HRHHR				*_hoops_RAIHR[3];
				float					lengths[3];
				bool					fixed = false;
				int						j;

				if ((info->_hoops_GHHHR = _hoops_RCHHR->next) != null)
					info->_hoops_GHHHR->backlink = &info->_hoops_GHHHR;

				/* _hoops_GHIS _hoops_RH 3 _hoops_SPPR _hoops_HPP _hoops_HSRAR _hoops_SPCC */
				for (i=0; i<3; ++i) {
					/* _hoops_SCPH _hoops_SPPR _hoops_CHR _hoops_AAIHR _hoops_PII _hoops_PCCP _hoops_CRPR, _hoops_HIS _hoops_SR _hoops_PAH _hoops_PAIHR _hoops_IS _hoops_HAIHR _hoops_RH _hoops_RPHR _hoops_SPR */
					_hoops_RAIHR[i] = (&_hoops_RCHHR->_hoops_HAHHR)[i];
					lengths[i] = _hoops_CGIHR (info, _hoops_RAIHR[i]);

					j = i;
					while (j > 0 && lengths[j] > lengths[j-1]) {
						_hoops_HRHHR *			_hoops_IAIHR = _hoops_RAIHR[j];
						float				_hoops_CAIHR = lengths[j];

						_hoops_RAIHR[j] = _hoops_RAIHR[j-1];
						lengths[j] = lengths[j-1];
						--j;
						_hoops_RAIHR[j] = _hoops_IAIHR;
						lengths[j] = _hoops_CAIHR;
					}
				}

				/* _hoops_RPP _hoops_GII _hoops_SAIHR _hoops_SR'_hoops_ASAR _hoops_GPIHR _hoops_GGR _hoops_HRGR _hoops_HAR _hoops_GACC _hoops_ARHAR, _hoops_IPS _hoops_RGCI _hoops_GSSR */
				for (i=0; i<_hoops_ARIHR; ++i) {
					if (_hoops_RAIHR[i]->_hoops_CRHHR != null) {
						_hoops_PRHHR const *	other;

						if (_hoops_RAIHR[i]->_hoops_IRHHR == _hoops_RCHHR)
							other = _hoops_RAIHR[i]->_hoops_CRHHR;
						else
							other = _hoops_RAIHR[i]->_hoops_IRHHR;

						if (normals[other->face].a != 0.0f ||
							normals[other->face].b != 0.0f ||
							normals[other->face].c != 0.0f) {
							normals[_hoops_RCHHR->face] = normals[other->face];
							_hoops_GAIHR = fixed = true;
							break;
						}
					}
				}

				if (!fixed) {	/* _hoops_GAAP _hoops_HPPR _hoops_GICS _hoops_SPHR */
					if ((_hoops_RCHHR->next = _hoops_SRIHR) != null)
						_hoops_RCHHR->next->backlink = &_hoops_RCHHR->next;
					_hoops_RCHHR->backlink = &_hoops_SRIHR;
					_hoops_SRIHR = _hoops_RCHHR;
				}
			}

			info->_hoops_GHHHR = _hoops_SRIHR;	/* _hoops_ARAS _hoops_AGCR _hoops_GICS _hoops_GGR _hoops_AGIR _hoops_SR _hoops_RPIHR _hoops_IRS _hoops_GSSR _hoops_GPP _hoops_PAII _hoops_APIHR */
			if (!_hoops_GAIHR)	/* _hoops_RPP _hoops_PIRC _hoops_HGAS, _hoops_PSP _hoops_CSSP _hoops_IRCC _hoops_GICS _hoops_HPGR _hoops_RGR _hoops_PAPA */
				break;
		}

		++_hoops_ARIHR;							/* _hoops_CACH _hoops_RPP _hoops_IRCC _hoops_RRI _hoops_SCCPR _hoops_HIPH (_hoops_PPIHR _hoops_SPPR) _hoops_GRS _hoops_HPIHR */
	}

#if 0
	if (info->_hoops_GHHHR != null) {
		HE_WARNING (HEC_FACE, HES_NORMAL, "Unable to resolve all face normals (possibly unconnected degenerate faces)");
		info->_hoops_GHHHR = null;			/* _hoops_IPIHR _hoops_GII _hoops_GGPI _hoops_GGR _hoops_AGIR _hoops_SR _hoops_RCPS _hoops_ISSC */
	}
#endif

	*_hoops_RRIHR = item;
}


#define QS_TYPE				_hoops_HRHHR **				/* _hoops_RH _hoops_GPRR _hoops_IIGR _hoops_CARA _hoops_PAR _hoops_CRPR _hoops_SGS _hoops_ICGI _hoops_HCR _hoops_HSH */
#define QS_VAL(thing,a)		(thing[a]->_hoops_SRHHR)	/* _hoops_HRS _hoops_RH _hoops_PIRA _hoops_IIGR _hoops_PCCP _hoops_IGCI _hoops_CCA _hoops_CIHA _hoops_IRS */
#define QS_COMPARE(i1,i2)	(i1>i2)					/* _hoops_SGH ">" _hoops_IS _hoops_GHIS _hoops_GACPR, "<" _hoops_IS _hoops_GHIS _hoops_CPIHR */
#define QS_SWAP(thing,a,b)	{_hoops_HRHHR *temp; temp=thing[a]; thing[a]=thing[b]; thing[b]=temp;}	/* _hoops_SPIHR _hoops_PGCR _hoops_HSH */
#define QS_COMPARETYPE int
#include "utility/hqsort.h"


#define _hoops_GHIHR 30


local _hoops_HRHHR * _hoops_RHIHR (
	_hoops_CPHHR		*info) {
	_hoops_HRHHR		**table = info->_hoops_SPHHR;
	long			size = info->_hoops_RHHHR;
	_hoops_HRHHR		*edge;

	if (info->_hoops_SHHHR < 2 ||
		info->_hoops_SHHHR == 2 && info->_hoops_CHHHR > 1024) {
		_hoops_HRHHR		head;
		_hoops_HRHHR		*tail = &head;

		/*
		 * _hoops_IPCP _hoops_GHIS _hoops_HRGR _hoops_AHIHR - _hoops_SAHR _hoops_PHIHR
		 */

		head.next = null; /* (_hoops_GGR _hoops_AGIR _hoops_IIH _hoops_CHR _hoops_PIRC _hoops_HPGR _hoops_HCR) */
		do {
			if ((edge = *table) != null) {
				tail->next = edge;
				do tail = edge;
				_hoops_RGGA ((edge = tail->next) == null);
			}
			*table++ = null;
		} _hoops_RGGA (--size == 0);

		return head.next;
	}
	else if (info->_hoops_SHHHR < _hoops_GHIHR) {
		_hoops_HRHHR		**_hoops_ASAPR;
		_hoops_HRHHR		**_hoops_HHIHR;
		_hoops_HRHHR		**be;
		_hoops_HRHHR		*head;

		/*
		 * _hoops_IHIHR _hoops_PPR _hoops_GACC _hoops_GHIS _hoops_HPP _hoops_CSHHR (_hoops_GRP _hoops_CHIHR _hoops_GHIS)
		 * _hoops_SHIHR _hoops_HIGR _hoops_GRS _hoops_HS _hoops_AHPA _hoops_CSHHR _hoops_HPGR _hoops_RH _hoops_HARS
		 */

		ZALLOC_ARRAY_CACHED (_hoops_HHIHR, _hoops_GHIHR, _hoops_HRHHR *);		

		_hoops_ASAPR = _hoops_HHIHR;
		be = _hoops_HHIHR+_hoops_GHIHR;
		{
			_hoops_HRHHR		*next;

			do {
				if ((edge = *table) != null) {
					do {
						next = edge->next;
						edge->next = _hoops_HHIHR[edge->_hoops_SRHHR];
						_hoops_HHIHR[edge->_hoops_SRHHR] = edge;
						edge = next;
					} _hoops_RGGA (edge == null);
				}
				*table++ = null;
			} _hoops_RGGA (--size == 0);
		}

		head = null;
		_hoops_ASAPR = _hoops_HHIHR;
		be = _hoops_HHIHR+_hoops_GHIHR; /* _hoops_SAHR _hoops_IS _hoops_SHH _hoops_ICIC */
		_hoops_RGGA (_hoops_ASAPR == be) if ((edge = *_hoops_ASAPR++) != null) {
			_hoops_HRHHR		*tail = edge;

			_hoops_RGGA (tail->next == null) tail = tail->next;

			tail->next = head;
			head = edge;
		}

		FREE_ARRAY (_hoops_HHIHR, _hoops_GHIHR, _hoops_HRHHR *);

		return head;
	}
	else {
		_hoops_HRHHR		**ptr;
		_hoops_HRHHR		**_hoops_GIIHR;
		_hoops_HRHHR		*_hoops_RIIHR;

		/*
		 * _hoops_IHIHR _hoops_PPR _hoops_GACC _hoops_GHIS _hoops_HPP _hoops_CSHHR (_hoops_GRP _hoops_AIIHR _hoops_GHIS)
		 * _hoops_SHIHR _hoops_HIGR _hoops_GRS _hoops_HS _hoops_AHPA _hoops_CSHHR _hoops_HPGR _hoops_RH _hoops_HARS
		 */

		ALLOC_ARRAY_CACHED (_hoops_GIIHR, info->_hoops_CHHHR, _hoops_HRHHR *);
		ptr = _hoops_GIIHR;

		do {
			if ((edge = *table) != null) {
				do *ptr++ = edge;
				_hoops_RGGA ((edge = edge->next) == null);
			}
			*table++ = null;
		} _hoops_RGGA (--size == 0);

		quick_sort (_hoops_GIIHR, 0, ptr - _hoops_GIIHR - 1);


		{
			_hoops_HRHHR		**head;

			size = info->_hoops_CHHHR;
			head = _hoops_GIIHR;
			ptr = head;

			(*ptr)->next = null;
			_hoops_RGGA (--size == 0) {
				++head;
				(*head)->next = *ptr;
				ptr = head;
			}
		}

		_hoops_RIIHR = *ptr; /* _hoops_PIHA _hoops_SHH _hoops_CPHR _hoops_PIIHR _hoops_IS _hoops_RH _hoops_HSPR _hoops_AAAGR */
		FREE_ARRAY (_hoops_GIIHR, info->_hoops_CHHHR, _hoops_HRHHR *);
		return _hoops_RIIHR;
	}
}


#define _hoops_HIIHR(_hoops_IIIHR, _hoops_CIIHR, _hoops_SIIHR, _hoops_GCIHR)								\
		((_hoops_IIIHR)==null || \
		(_hoops_IIIHR)->local_vertex_attributes._hoops_RCIHR == null ||	\
		 HI_Split_Point_Lookup ((Polyhedron *)_hoops_IIIHR, _hoops_CIIHR->vertex1, _hoops_SIIHR) ==	\
		 HI_Split_Point_Lookup ((Polyhedron *)_hoops_IIIHR, _hoops_CIIHR->vertex1, _hoops_GCIHR) &&	\
		 HI_Split_Point_Lookup ((Polyhedron *)_hoops_IIIHR, _hoops_CIIHR->vertex2, _hoops_SIIHR) ==	\
		 HI_Split_Point_Lookup ((Polyhedron *)_hoops_IIIHR, _hoops_CIIHR->vertex2, _hoops_GCIHR))



#define _hoops_ACIHR true

local int * _hoops_PCIHR (
	Shell						*_hoops_SPHPR,
	_hoops_HRHHR					*_hoops_PPGHR,
	_hoops_PRHHR				*_hoops_RCHHR,
	int							_hoops_ISPI,
	One_Face_Attributes			*_hoops_HCIHR,
	Local_Face_Attributes		*_hoops_ICIHR,
	bool						_hoops_CCIHR,
	int							*_hoops_SCIHR,
	int							*limit) {
	_hoops_HRHHR					*_hoops_GSIHR = _hoops_PPGHR;
	_hoops_HRHHR					*_hoops_RSIHR;
	_hoops_HRHHR					*_hoops_ASIHR;
	int							_hoops_SSPI;
	int							_hoops_CSPI;
	int							*result = _hoops_SCIHR;
	_hoops_PRHHR				*_hoops_PSIHR = null;
	int							_hoops_HSIHR = 0, _hoops_ISIHR = 0;

	if (_hoops_GSIHR->vertex1 == _hoops_ISPI)
		_hoops_CSPI = _hoops_GSIHR->vertex2;
	else
		_hoops_CSPI = _hoops_GSIHR->vertex1;

	_hoops_PCCAR {
		if (_hoops_RCHHR->_hoops_SAHHR != null) {	/* _hoops_CPSA _hoops_IRS _hoops_PCPI */
			_hoops_HRHHR				*_hoops_CSIHR;
			int						_hoops_SGHI;

			/*
			 * _hoops_IPCP _hoops_PCPI _hoops_HRGR _hoops_PAPR _hoops_GAR _hoops_SPCP:
			 *				   _hoops_IHAC
			 *		  _hoops_CIHHR *-----------* _hoops_SSIHR
			 *			 |			 |
			 *			 |			 |
			 *		   _hoops_RAIGR |			 | _hoops_IHRPR
			 *			 |			 |
			 *			 |			 |
			 *		  _hoops_IIHHR *-----------* _hoops_GGCHR
			 *				   _hoops_APCAR
			 *
			 *
			 * _hoops_HPP _hoops_RGCHR _hoops_GIPHR, _hoops_SSS _hoops_RH _hoops_AIGHR _hoops_ISHA (_hoops_AGCHR)
			 * _hoops_GPP _hoops_RGR _hoops_PCPI _hoops_PGAP _hoops_HRGR _hoops_PGCHR _hoops_IIHHR _hoops_PPR _hoops_CIHHR, _hoops_PPR _hoops_PIAAR _hoops_SSIHR _hoops_PPR _hoops_GGCHR.
			 */

			if (_hoops_RCHHR->_hoops_HAHHR == _hoops_GSIHR) {		/* _hoops_SSPC _hoops_HGCHR */
				_hoops_ASIHR = _hoops_RCHHR->_hoops_CAHHR;		/* _hoops_PIHA _hoops_SHH */

				_hoops_RSIHR = _hoops_RCHHR->_hoops_IAHHR;		/* _hoops_SRS _hoops_AHGC */
				_hoops_CSIHR = _hoops_RCHHR->_hoops_SAHHR;

				if (_hoops_RSIHR->vertex1 == _hoops_CSPI)
					_hoops_SSPI = _hoops_RSIHR->vertex2;
				else if (_hoops_RSIHR->vertex2 == _hoops_CSPI)
					_hoops_SSPI = _hoops_RSIHR->vertex1;
				else {
					_hoops_RSIHR = _hoops_RCHHR->_hoops_SAHHR;	/* _hoops_PIHA _hoops_SHH */
					_hoops_CSIHR = _hoops_RCHHR->_hoops_IAHHR;

					if (_hoops_RSIHR->vertex1 == _hoops_CSPI) _hoops_SSPI = _hoops_RSIHR->vertex2;
					else /* _hoops_RPP (_hoops_IGCHR->_hoops_ASHHR == _hoops_CIHHR) */ _hoops_SSPI = _hoops_RSIHR->vertex1;
				}
			}
			else if (_hoops_RCHHR->_hoops_IAHHR == _hoops_GSIHR) {/* _hoops_SSPC _hoops_CGCHR */
				_hoops_ASIHR = _hoops_RCHHR->_hoops_SAHHR;		/* _hoops_PIHA _hoops_SHH */

				_hoops_RSIHR = _hoops_RCHHR->_hoops_CAHHR;		/* _hoops_SRS _hoops_AHGC */
				_hoops_CSIHR = _hoops_RCHHR->_hoops_HAHHR;

				if (_hoops_RSIHR->vertex1 == _hoops_CSPI)
					_hoops_SSPI = _hoops_RSIHR->vertex2;
				else if (_hoops_RSIHR->vertex2 == _hoops_CSPI)
					_hoops_SSPI = _hoops_RSIHR->vertex1;
				else {
					_hoops_RSIHR = _hoops_RCHHR->_hoops_HAHHR;	/* _hoops_PIHA _hoops_SHH */
					_hoops_CSIHR = _hoops_RCHHR->_hoops_CAHHR;

					if (_hoops_RSIHR->vertex1 == _hoops_CSPI) _hoops_SSPI = _hoops_RSIHR->vertex2;
					else /* _hoops_RPP (_hoops_IGCHR->_hoops_ASHHR == _hoops_CIHHR) */ _hoops_SSPI = _hoops_RSIHR->vertex1;
				}
			}
			else if (_hoops_RCHHR->_hoops_CAHHR == _hoops_GSIHR) {/* _hoops_SSPC _hoops_SGCHR */
				_hoops_ASIHR = _hoops_RCHHR->_hoops_HAHHR;		/* _hoops_PIHA _hoops_SHH */

				_hoops_RSIHR = _hoops_RCHHR->_hoops_SAHHR;		/* _hoops_SRS _hoops_AHGC */
				_hoops_CSIHR = _hoops_RCHHR->_hoops_IAHHR;

				if (_hoops_RSIHR->vertex1 == _hoops_CSPI)
					_hoops_SSPI = _hoops_RSIHR->vertex2;
				else if (_hoops_RSIHR->vertex2 == _hoops_CSPI)
					_hoops_SSPI = _hoops_RSIHR->vertex1;
				else {
					_hoops_RSIHR = _hoops_RCHHR->_hoops_IAHHR;	/* _hoops_PIHA _hoops_SHH */
					_hoops_CSIHR = _hoops_RCHHR->_hoops_SAHHR;

					if (_hoops_RSIHR->vertex1 == _hoops_CSPI) _hoops_SSPI = _hoops_RSIHR->vertex2;
					else /* _hoops_RPP (_hoops_IGCHR->_hoops_ASHHR == _hoops_CIHHR) */ _hoops_SSPI = _hoops_RSIHR->vertex1;
				}
			}
			else /* _hoops_RPP (_hoops_SCPH->_hoops_GRCHR == _hoops_RRCHR) */ {	/* _hoops_SSPC _hoops_GRCHR */
				_hoops_ASIHR = _hoops_RCHHR->_hoops_IAHHR;		/* _hoops_PIHA _hoops_SHH */

				_hoops_RSIHR = _hoops_RCHHR->_hoops_HAHHR;		/* _hoops_SRS _hoops_AHGC */
				_hoops_CSIHR = _hoops_RCHHR->_hoops_CAHHR;

				if (_hoops_RSIHR->vertex1 == _hoops_CSPI)
					_hoops_SSPI = _hoops_RSIHR->vertex2;
				else if (_hoops_RSIHR->vertex2 == _hoops_CSPI)
					_hoops_SSPI = _hoops_RSIHR->vertex1;
				else {
					_hoops_RSIHR = _hoops_RCHHR->_hoops_CAHHR;	/* _hoops_PIHA _hoops_SHH */
					_hoops_CSIHR = _hoops_RCHHR->_hoops_HAHHR;

					if (_hoops_RSIHR->vertex1 == _hoops_CSPI) _hoops_SSPI = _hoops_RSIHR->vertex2;
					else /* _hoops_RPP (_hoops_IGCHR->_hoops_ASHHR == _hoops_CIHHR) */ _hoops_SSPI = _hoops_RSIHR->vertex1;
				}
			}

			/* _hoops_ARR _hoops_SSIHR _hoops_ARCHR, _hoops_GGCHR _hoops_HRGR _hoops_PIHGR */
			if (_hoops_ASIHR->vertex1 == _hoops_SSPI) _hoops_SGHI = _hoops_ASIHR->vertex2;
			else /* _hoops_RPP (_hoops_AGCHR->_hoops_ASHHR == _hoops_SSIHR) */ _hoops_SGHI = _hoops_ASIHR->vertex1;

			/* _hoops_GSIH _hoops_RH _hoops_CCAH _hoops_CRHH _hoops_AIRP */
			*result++ = HI_Split_Point_Lookup ((Polyhedron const *)_hoops_SPHPR, _hoops_SGHI, _hoops_RCHHR->face);
			*result++ = _hoops_RCHHR->face;
			*result++ = HI_Split_Point_Lookup ((Polyhedron const *)_hoops_SPHPR, _hoops_SSPI, _hoops_RCHHR->face);
			*result++ = _hoops_RCHHR->face;

			/*
			 * _hoops_ACRAR _hoops_HCR _hoops_RH _hoops_PRCHR _hoops_IS _hoops_RGR _hoops_SCPH (_hoops_HGIPR _hoops_RH _hoops_SCCPR
			 * _hoops_HIPH _hoops_GH _hoops_IS _hoops_RH '1' _hoops_CPPA _hoops_IS _hoops_GRHP _hoops_CAPR _hoops_IHIR) _hoops_PPR _hoops_HRCHR _hoops_IIGR _hoops_SCH.
			 */
			if (_hoops_GSIHR->_hoops_IRHHR == _hoops_RCHHR) _hoops_GSIHR->_hoops_IRHHR = _hoops_GSIHR->_hoops_CRHHR;
			_hoops_GSIHR->_hoops_CRHHR = null;

			if (_hoops_RSIHR->_hoops_IRHHR == _hoops_RCHHR) _hoops_RSIHR->_hoops_IRHHR = _hoops_RSIHR->_hoops_CRHHR;
			_hoops_RSIHR->_hoops_CRHHR = null;

			if (_hoops_ASIHR->_hoops_IRHHR == _hoops_RCHHR) _hoops_ASIHR->_hoops_IRHHR = _hoops_ASIHR->_hoops_CRHHR;
			_hoops_ASIHR->_hoops_CRHHR = null;

			if (_hoops_CSIHR->_hoops_IRHHR == _hoops_RCHHR) _hoops_CSIHR->_hoops_IRHHR = _hoops_CSIHR->_hoops_CRHHR;
			_hoops_CSIHR->_hoops_CRHHR = null;


			/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_RH _hoops_PGHC _hoops_SCPH _hoops_PPR _hoops_ASAC _hoops_PCSA _hoops_RGR _hoops_SPR */
			if (_hoops_PSIHR != null) FREE (_hoops_PSIHR, _hoops_PRHHR);
			_hoops_PSIHR = _hoops_RCHHR;


			/* _hoops_HIAP _hoops_HHH _hoops_SPPR _hoops_GPP _hoops_RH _hoops_SCPH _hoops_GGR _hoops_AGIR _hoops_SR _hoops_RRP _hoops_IS _hoops_AISI _hoops_ISSC */
			if ((result - _hoops_SCIHR) & 2) {	// _hoops_IRCHR _hoops_RGR _hoops_PCPI _hoops_GGR _hoops_IRS _hoops_CRCHR _hoops_SRCHR
				_hoops_RCHHR->_hoops_HAHHR = _hoops_ASIHR;
				_hoops_RCHHR->_hoops_IAHHR = _hoops_RSIHR;
			}
			else {
				_hoops_RCHHR->_hoops_HAHHR = _hoops_RSIHR;
				_hoops_RCHHR->_hoops_IAHHR = _hoops_ASIHR;
			}
			/* _hoops_SGCHR _hoops_CHH _hoops_GACHR _hoops_RH _hoops_CCAH _hoops_GGRAR _hoops_ISHA, _hoops_GRCHR _hoops_CHH _hoops_PHHR _hoops_SGGR */
			_hoops_HSIHR = _hoops_SGHI;
			_hoops_ISIHR = _hoops_CSPI;

			/* _hoops_PH _hoops_IGIAR */
			_hoops_ISPI = _hoops_SGHI;
			_hoops_CSPI = _hoops_SSPI;
			_hoops_GSIHR = _hoops_ASIHR;
		}
		else {							/* _hoops_SCPH */
			/*
			 * _hoops_IPCP _hoops_SCPH _hoops_HRGR _hoops_PAPR _hoops_GAR _hoops_SPCP:
			 *
			 *				   * _hoops_CIHHR
			 *				  / \
			 *				 /	 \
			 *			  _hoops_RAIGR /	  \ _hoops_IHAC
			 *			   /	   \
			 *			  /			\
			 *		  _hoops_IIHHR *-----------* _hoops_SSIHR
			 *				   _hoops_IHRPR
			 *
			 *
			 * _hoops_HPP _hoops_RGCHR _hoops_GIPHR, _hoops_SSS _hoops_RH _hoops_AIGHR _hoops_SPPR (_hoops_IGCHR _hoops_PPR _hoops_AGCHR)
			 * _hoops_GPP _hoops_RGR _hoops_SCPH _hoops_PGAP _hoops_HSSRR _hoops_RGR _hoops_IIHHR _hoops_PPR _hoops_CIHHR.
			 */

			if (_hoops_RCHHR->_hoops_HAHHR == _hoops_GSIHR) {		/* _hoops_SSPC _hoops_HGCHR */
				_hoops_RSIHR = _hoops_RCHHR->_hoops_IAHHR;		/* _hoops_SRS _hoops_AHGC */

				if (_hoops_RSIHR->vertex1 == _hoops_CSPI) {
					_hoops_SSPI = _hoops_RSIHR->vertex2;
					_hoops_ASIHR = _hoops_RCHHR->_hoops_CAHHR;
				}
				else if (_hoops_RSIHR->vertex2 == _hoops_CSPI) {
					_hoops_SSPI = _hoops_RSIHR->vertex1;
					_hoops_ASIHR = _hoops_RCHHR->_hoops_CAHHR;
				}
				else {
					_hoops_RSIHR = _hoops_RCHHR->_hoops_CAHHR;	/* _hoops_PIHA _hoops_SHH */
					_hoops_ASIHR = _hoops_RCHHR->_hoops_IAHHR;
					if (_hoops_RSIHR->vertex1 == _hoops_CSPI) _hoops_SSPI = _hoops_RSIHR->vertex2;
					else /* _hoops_RPP (_hoops_IGCHR->_hoops_ASHHR == _hoops_CIHHR) */ _hoops_SSPI = _hoops_RSIHR->vertex1;
				}
			}
			else if (_hoops_RCHHR->_hoops_IAHHR == _hoops_GSIHR) {/* _hoops_SSPC _hoops_CGCHR */
				_hoops_RSIHR = _hoops_RCHHR->_hoops_HAHHR;		/* _hoops_SRS _hoops_AHGC */

				if (_hoops_RSIHR->vertex1 == _hoops_CSPI) {
					_hoops_SSPI = _hoops_RSIHR->vertex2;
					_hoops_ASIHR = _hoops_RCHHR->_hoops_CAHHR;
				}
				else if (_hoops_RSIHR->vertex2 == _hoops_CSPI) {
					_hoops_SSPI = _hoops_RSIHR->vertex1;
					_hoops_ASIHR = _hoops_RCHHR->_hoops_CAHHR;
				}
				else {
					_hoops_RSIHR = _hoops_RCHHR->_hoops_CAHHR;	/* _hoops_PIHA _hoops_SHH */
					_hoops_ASIHR = _hoops_RCHHR->_hoops_HAHHR;
					if (_hoops_RSIHR->vertex1 == _hoops_CSPI) _hoops_SSPI = _hoops_RSIHR->vertex2;
					else /* _hoops_RPP (_hoops_IGCHR->_hoops_ASHHR == _hoops_CIHHR) */ _hoops_SSPI = _hoops_RSIHR->vertex1;
				}
			}
			else /* _hoops_RPP (_hoops_SCPH->_hoops_SGCHR == _hoops_RRCHR) */ {/* _hoops_SSPC _hoops_SGCHR */
				_hoops_RSIHR = _hoops_RCHHR->_hoops_HAHHR;		/* _hoops_SRS _hoops_AHGC */

				if (_hoops_RSIHR->vertex1 == _hoops_CSPI) {
					_hoops_SSPI = _hoops_RSIHR->vertex2;
					_hoops_ASIHR = _hoops_RCHHR->_hoops_IAHHR;
				}
				else if (_hoops_RSIHR->vertex2 == _hoops_CSPI) {
					_hoops_SSPI = _hoops_RSIHR->vertex1;
					_hoops_ASIHR = _hoops_RCHHR->_hoops_IAHHR;
				}
				else {
					_hoops_RSIHR = _hoops_RCHHR->_hoops_IAHHR;	/* _hoops_PIHA _hoops_SHH */
					_hoops_ASIHR = _hoops_RCHHR->_hoops_HAHHR;
					if (_hoops_RSIHR->vertex1 == _hoops_CSPI) _hoops_SSPI = _hoops_RSIHR->vertex2;
					else /* _hoops_RPP (_hoops_IGCHR->_hoops_ASHHR == _hoops_CIHHR) */ _hoops_SSPI = _hoops_RSIHR->vertex1;
				}
			}

			/* _hoops_GSIH _hoops_RH _hoops_CCAH _hoops_CRHH _hoops_RARP */
			*result++ = HI_Split_Point_Lookup ((Polyhedron const *)_hoops_SPHPR, _hoops_SSPI, _hoops_RCHHR->face);
			*result++ = _hoops_RCHHR->face;

			/*
			 * _hoops_ACRAR _hoops_HCR _hoops_RH _hoops_PRCHR _hoops_IS _hoops_RGR _hoops_SCPH (_hoops_HGIPR _hoops_RH _hoops_SCCPR
			 * _hoops_HIPH _hoops_GH _hoops_IS _hoops_RH '1' _hoops_CPPA _hoops_IS _hoops_GRHP _hoops_CAPR _hoops_IHIR) _hoops_PPR _hoops_HRCHR _hoops_IIGR _hoops_SCH.
			 */
			if (_hoops_GSIHR->_hoops_IRHHR == _hoops_RCHHR) _hoops_GSIHR->_hoops_IRHHR = _hoops_GSIHR->_hoops_CRHHR;
			_hoops_GSIHR->_hoops_CRHHR = null;

			if (_hoops_RSIHR->_hoops_IRHHR == _hoops_RCHHR) _hoops_RSIHR->_hoops_IRHHR = _hoops_RSIHR->_hoops_CRHHR;
			_hoops_RSIHR->_hoops_CRHHR = null;

			if (_hoops_ASIHR->_hoops_IRHHR == _hoops_RCHHR) _hoops_ASIHR->_hoops_IRHHR = _hoops_ASIHR->_hoops_CRHHR;
			_hoops_ASIHR->_hoops_CRHHR = null;


			/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_RH _hoops_PGHC _hoops_SCPH _hoops_PPR _hoops_ASAC _hoops_PCSA _hoops_RGR _hoops_SPR */
			if (_hoops_PSIHR != null) FREE (_hoops_PSIHR, _hoops_PRHHR);
			_hoops_PSIHR = _hoops_RCHHR;

			/* _hoops_PH _hoops_IGIAR */
			_hoops_ISPI = _hoops_CSPI;
			_hoops_CSPI = _hoops_SSPI;
			_hoops_GSIHR = _hoops_RSIHR;
		}


		/* _hoops_PH _hoops_IGIAR _hoops_IS _hoops_RH _hoops_CCAH _hoops_ISHA'_hoops_GRI _hoops_RII _hoops_SCPH, _hoops_RPP _hoops_GII */
		if ((_hoops_RCHHR = _hoops_GSIHR->_hoops_IRHHR) == null) break; /* _hoops_ICCAR _hoops_PRAR */

		/* _hoops_ISPR _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_RGR _hoops_SPS _hoops_SCPH _hoops_SSCP _hoops_PIS _hoops_AIRC */
		if (_hoops_ICIHR != null &&
			!_hoops_IIPHR (_hoops_ICIHR,
												  _hoops_RCHHR->face, *_hoops_HCIHR) ||
			!_hoops_HIIHR (_hoops_SPHPR, _hoops_GSIHR, _hoops_PSIHR->face, _hoops_RCHHR->face))
				break;

		if (limit - result < 4)		// _hoops_GHSGR _hoops_RAPR _hoops_RSIAR _hoops_IS _hoops_HGCR _hoops_HPGR _hoops_CHGC _hoops_HPIH _hoops_PCPI _hoops_RHIR
			break;
	}

	if (_hoops_CCIHR && ((result - _hoops_SCIHR) & 2)) {	// _hoops_RPP (_hoops_GHPP - _hoops_RACHR) _hoops_HRGR _hoops_RRPC _hoops_PCCP _hoops_PISC _hoops_PHI
		result -= 2;
		_hoops_RCHHR = _hoops_PSIHR;

		_hoops_GSIHR = _hoops_RCHHR->_hoops_HAHHR;
		if (_hoops_GSIHR->_hoops_IRHHR == null)
			_hoops_GSIHR->_hoops_IRHHR = _hoops_RCHHR;
		else
			_hoops_GSIHR->_hoops_CRHHR = _hoops_RCHHR;

		_hoops_GSIHR = _hoops_RCHHR->_hoops_IAHHR;
		if (_hoops_GSIHR->_hoops_IRHHR == null)
			_hoops_GSIHR->_hoops_IRHHR = _hoops_RCHHR;
		else
			_hoops_GSIHR->_hoops_CRHHR = _hoops_RCHHR;

		if (_hoops_RCHHR->_hoops_SAHHR == null) {
			_hoops_GSIHR = _hoops_RCHHR->_hoops_CAHHR;
			if (_hoops_GSIHR->_hoops_IRHHR == null)
				_hoops_GSIHR->_hoops_IRHHR = _hoops_RCHHR;
			else
				_hoops_GSIHR->_hoops_CRHHR = _hoops_RCHHR;
		}
		else {
			/* _hoops_AISI _hoops_ISSC *_hoops_HHAA* _hoops_RH _hoops_PCPI _hoops_CCA _hoops_IRS _hoops_CCAH _hoops_GGRAR _hoops_ISHA */

			ALLOC (_hoops_GSIHR, _hoops_HRHHR);
			_hoops_GSIHR->next = _hoops_PPGHR->next;
			_hoops_PPGHR->next = _hoops_GSIHR;
			_hoops_GSIHR->_hoops_IRHHR = _hoops_RCHHR;
			_hoops_GSIHR->_hoops_CRHHR = null;
			_hoops_GSIHR->vertex1 = _hoops_HSIHR;
			_hoops_GSIHR->vertex2 = _hoops_ISIHR;
			_hoops_GSIHR->_hoops_SRHHR = 1;
			_hoops_GSIHR->_hoops_GAHHR = false;
			_hoops_GSIHR->_hoops_RAHHR = false;
			_hoops_GSIHR->_hoops_AAHHR = _hoops_GGHHR;
			_hoops_GSIHR->_hoops_PAHHR = _hoops_GGHHR;

			_hoops_RCHHR->_hoops_CAHHR = _hoops_GSIHR;
			_hoops_RCHHR->_hoops_SAHHR = null;
		}
	}
	else
		if (_hoops_PSIHR != null) FREE (_hoops_PSIHR, _hoops_PRHHR);

	return result;
}


local void _hoops_CSHPR (
	_hoops_RPHHR			*_hoops_AGPHR,
	_hoops_RPHHR			**_hoops_SSHPR) {
	_hoops_RPHHR			*node;

	if (BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_AACHR)) {
		_hoops_PACHR	_hoops_HACHR;

		_hoops_HACHR._hoops_SCPHR = _hoops_SCPHR;	_hoops_SCPHR += 67.0f;
		if (_hoops_SCPHR > 360.0f) _hoops_SCPHR -= 360.0f;
		_hoops_HACHR._hoops_HSPHR = _hoops_HSPHR[_hoops_PSPHR];
		_hoops_HACHR._hoops_ISPHR = _hoops_ISPHR[_hoops_PSPHR];
		_hoops_PSPHR = (_hoops_PSPHR+1) % 3;

		HI_HLS_To_RGB (&_hoops_HACHR, &_hoops_AGPHR->face_attributes.color);

		_hoops_AGPHR->face_attributes.flags &= ~_hoops_IACHR;
		_hoops_AGPHR->face_attributes.flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
	}


	if (_hoops_AGPHR->_hoops_HPHHR > 0)
		_hoops_GGIPR (_hoops_AGPHR->_hoops_APHHR, 2*_hoops_AGPHR->_hoops_HPHHR, int, _hoops_AGPHR->_hoops_APHHR);
	if (_hoops_AGPHR->_hoops_IPHHR > 0)
		_hoops_GGIPR (_hoops_AGPHR->_hoops_PPHHR, 2*_hoops_AGPHR->_hoops_IPHHR, int, _hoops_AGPHR->_hoops_PPHHR);

	/*
	 * _hoops_ASHPR _hoops_RGR _hoops_CCAH _hoops_IRHP-_hoops_CRHH _hoops_HPP _hoops_IGRI _hoops_PIRA
	 * _hoops_CRGR _hoops_IRS _hoops_PSHPR _hoops_HHIS. _hoops_IPCP _hoops_CARA _hoops_HRGR _hoops_IS _hoops_SHH _hoops_SHSS _hoops_IS
	 * _hoops_SSS _hoops_RH _hoops_HSHPR-_hoops_IGRI _hoops_CRHH _hoops_ISHPR
	 * _hoops_SPHR.
	 */

	_hoops_AGPHR->_hoops_CGHPR = null;
	_hoops_AGPHR->_hoops_SGHPR = null;

	if ((node = *_hoops_SSHPR) == null) {		/* _hoops_RH _hoops_SRS _hoops_SPR */
		*_hoops_SSHPR = _hoops_AGPHR;
		_hoops_AGPHR->_hoops_GRHPR = null;
		_hoops_AGPHR->up = null;
		return;
	}

	_hoops_PCCAR {
		if (_hoops_SAGI (_hoops_AGPHR->face_attributes, node->face_attributes,  ~0)) {
			_hoops_AGPHR->up = node->up;
			_hoops_AGPHR->_hoops_GRHPR = node->_hoops_GRHPR;
			node->_hoops_GRHPR = _hoops_AGPHR;
			return;
		}
#ifndef _hoops_PGPHR
		else if (_hoops_HGPHR (_hoops_AGPHR->face_attributes,
										   node->face_attributes)) {
			if (node->_hoops_CGHPR != null)
				node = node->_hoops_CGHPR;
			else {
				/* _hoops_PPSI _hoops_GGSR _hoops_IRS _hoops_CCAH '_hoops_CRGP' _hoops_RIIS */

				/*
				 * _hoops_IPCP _hoops_CCAH _hoops_GIIS _hoops_SHR _hoops_IAGA _hoops_GGSR _hoops_GAR _hoops_RH _hoops_RIIS, _hoops_HRII _hoops_HSAR
				 * _hoops_RH _hoops_RHGS _hoops_GIIS "_hoops_PGIPR" _hoops_HGIPR _hoops_ISHP _hoops_RRGI _hoops_SCH. _hoops_HGI _hoops_IGIPR
				 * _hoops_SGS _hoops_HSP _hoops_IGRI _hoops_PSHPR _hoops_HSH _hoops_PPPPR'_hoops_RA _hoops_CGIPR-_hoops_SGIPR _hoops_SHH
				 * _hoops_GRIPR _hoops_RRIPR.
				 */
				node->_hoops_CGHPR = _hoops_AGPHR;
				_hoops_AGPHR->up = node;
				_hoops_AGPHR->_hoops_GRHPR = null;
				return;
			}
		}
		else {
			if (node->_hoops_SGHPR != null)
				node = node->_hoops_SGHPR;
			else {
				/* _hoops_PPSI _hoops_GGSR _hoops_IRS _hoops_CCAH '_hoops_RRPAR' _hoops_RIIS */

				node->_hoops_SGHPR = _hoops_AGPHR;
				_hoops_AGPHR->up = node;
				_hoops_AGPHR->_hoops_GRHPR = null;
				return;
			}
		}
#endif
	}
}



/*
 * _hoops_PPPA _hoops_RH _hoops_PGGHR, _hoops_CAHA _hoops_GGSR _hoops_RSH _hoops_GSGS _hoops_GC _hoops_HRGR _hoops_SIGR, _hoops_PPR _hoops_ARPR
 * _hoops_RH _hoops_CACHR _hoops_CCGI.
 */
local void _hoops_PRIPR (
	Tristrip				**tristrips,
	_hoops_RPHHR		*temps) {
	_hoops_RPHHR		*_hoops_AGPHR = temps;
	_hoops_RPHHR		*_hoops_PCPHR;
	int						_hoops_SACHR = 0;
	int						_hoops_GPCHR = 0;
	int						_hoops_RPCHR = 0;

	if (temps == null) return;

	do {
		_hoops_RPHHR		*_hoops_HCPHR;
		Tristrip				*ts;

		/* _hoops_SSS _hoops_IRS _hoops_RIIS */
		_hoops_PCCAR {
			if (_hoops_AGPHR->_hoops_CGHPR != null) _hoops_AGPHR = _hoops_AGPHR->_hoops_CGHPR;
			else if (_hoops_AGPHR->_hoops_SGHPR != null) _hoops_AGPHR = _hoops_AGPHR->_hoops_SGHPR;
			else break;
		}

		if ((_hoops_PCPHR = _hoops_AGPHR->up) != null) {
			if (_hoops_PCPHR->_hoops_CGHPR == _hoops_AGPHR)
				_hoops_PCPHR->_hoops_CGHPR = null;
			else if (_hoops_PCPHR->_hoops_SGHPR == _hoops_AGPHR)
				_hoops_PCPHR->_hoops_SGHPR = null;
		}

		_hoops_HCPHR = _hoops_AGPHR;


		ZALLOC (ts, Tristrip);
		_hoops_ICAI (ts);
		ts->next = *tristrips;
		*tristrips = ts;
		ts->face_attributes = _hoops_AGPHR->face_attributes;
		ts->same_colors = _hoops_PAIPR;

		/* _hoops_RPR _hoops_GH _hoops_RH _hoops_PHI _hoops_IIGR _hoops_IIRGR */
		{
			int			_hoops_PHHA = 0;
			int			total = 0;

			do {
				int		_hoops_HAIPR = _hoops_AGPHR->_hoops_HPHHR + _hoops_AGPHR->_hoops_IPHHR + 2;

				if (total > 0 && total + _hoops_HAIPR > 1<<16)
					break;
				total += _hoops_HAIPR;

				++_hoops_PHHA;
			} while ((_hoops_AGPHR = _hoops_AGPHR->_hoops_GRHPR) != null);
			ts->_hoops_PHHA = _hoops_PHHA;
		}
		_hoops_AGPHR = _hoops_HCPHR;

		ALLOC_ARRAY (ts->lengths, ts->_hoops_PHHA, int);
		ts->lengths_allocated = ts->_hoops_PHHA;
		_hoops_SACHR += ts->_hoops_PHHA;

		/* _hoops_HGCR _hoops_RH _hoops_IHHA _hoops_PPR _hoops_APSR _hoops_SPCC */
		{
			int			total = 0;
			int *		_hoops_IAIPR = ts->lengths;

			/*
			 * (1 _hoops_CAIPR _hoops_IH _hoops_GRR _hoops_RCHAR _hoops_GPHA;
			 *	2 _hoops_CAIPR _hoops_IH _hoops_RH _hoops_PGCR _hoops_APHR _hoops_GIHA)
			 */
			do {
				int		_hoops_HAIPR = _hoops_AGPHR->_hoops_HPHHR + _hoops_AGPHR->_hoops_IPHHR + 2;

				if (total > 0 && total + _hoops_HAIPR > 1<<16)
					break;
				total += _hoops_HAIPR;

				*_hoops_IAIPR++ = _hoops_HAIPR;
				if (_hoops_HAIPR > _hoops_RPCHR)
					_hoops_RPCHR = _hoops_HAIPR;
			} while ((_hoops_AGPHR = _hoops_AGPHR->_hoops_GRHPR) != null);
			ts->total = total;
		}
		_hoops_AGPHR = _hoops_HCPHR;

		_hoops_HCPHR = _hoops_AGPHR->up;	// _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_SPCC _hoops_SAIPR

		ALLOC_ARRAY (ts->_hoops_AIHA, ts->total, int);
		ALLOC_ARRAY (ts->face_indices, ts->total, int);
		ts->_hoops_IPII = ts->_hoops_SGAHR = ts->total;

		ts->_hoops_RAHH |= _hoops_AAHH;

		_hoops_GPCHR += ts->total;

		{
			int				total = 0;
			int				*_hoops_RPIPR = ts->_hoops_AIHA;
			int				*_hoops_PAPHR = ts->face_indices;
			int				*in;
			int				*_hoops_PPIPR;
			_hoops_RPHHR	*_hoops_ICPHR;

			/* _hoops_IH _hoops_GRR _hoops_SARGR _hoops_CCA _hoops_RH _hoops_PSHR _hoops_AIRC... */
			do {
				int		_hoops_HAIPR = _hoops_AGPHR->_hoops_HPHHR + _hoops_AGPHR->_hoops_IPHHR + 2;

				if (total > 0 && total + _hoops_HAIPR > 1<<16)
					break;
				total += _hoops_HAIPR;

				int		_hoops_APCHR;
				int		*_hoops_PPCHR;
				int		_hoops_HPCHR;
				int		*_hoops_IPCHR;
				int		vertex1;
				int		vertex2;

				if (!BIT (_hoops_AGPHR->_hoops_IPHHR, 1)) {
					/* _hoops_CPCHR _hoops_HRGR _hoops_CPCHR */
					vertex1 = _hoops_AGPHR->_hoops_ISPI;
					vertex2 = _hoops_AGPHR->_hoops_CSPI;
					_hoops_PPCHR   = _hoops_AGPHR->_hoops_APHHR;
					_hoops_IPCHR  = _hoops_AGPHR->_hoops_PPHHR;
					_hoops_APCHR	 = _hoops_AGPHR->_hoops_HPHHR;
					_hoops_HPCHR = _hoops_AGPHR->_hoops_IPHHR;
				}
				else {
					/* _hoops_SPCHR _hoops_HRGR _hoops_CPCHR */
					vertex1 = _hoops_AGPHR->_hoops_CSPI;
					vertex2 = _hoops_AGPHR->_hoops_ISPI;
					_hoops_PPCHR   = _hoops_AGPHR->_hoops_PPHHR;
					_hoops_IPCHR  = _hoops_AGPHR->_hoops_APHHR;
					_hoops_APCHR	 = _hoops_AGPHR->_hoops_IPHHR;
					_hoops_HPCHR = _hoops_AGPHR->_hoops_HPHHR;
				}

				/*
				 * _hoops_PHAA _hoops_ARAS "_hoops_HPIPR" _hoops_IS _hoops_RH _hoops_CGRS _hoops_ISHA
				 * _hoops_SPIPR: _hoops_GHCHR _hoops_HRGR _hoops_PRGI
				 */

				/*
				 * _hoops_HGI _hoops_RRGR _hoops_HRGR _hoops_GAHPR _hoops_CRGP _hoops_HSAR _hoops_RRH, _hoops_PGGA
				 * _hoops_RH _hoops_CIHHR _hoops_IH _hoops_RH _hoops_SCGR _hoops_SCPH _hoops_HRGR _hoops_PPRRR _hoops_PSAP _hoops_GGR _hoops_RH
				 * _hoops_HPIPR _hoops_GIRA, _hoops_PPR _hoops_GHCA _hoops_HAR _hoops_GGCA _hoops_HPGR _hoops_HCR _hoops_GGR _hoops_RH
				 * _hoops_IRHP _hoops_HIGR (_hoops_GRS _hoops_SHH _hoops_GGR _hoops_RH _hoops_IRHP _hoops_RGSPR _hoops_RIIA) _hoops_RPP _hoops_SR'_hoops_ASAR
				 * _hoops_GHHS _hoops_APAP _hoops_RH _hoops_IRHP'_hoops_GRI _hoops_APHR _hoops_ISHA.
				 */

				/* _hoops_SHR _hoops_HSPP _hoops_CCA 2 _hoops_SPCS _hoops_HSP _hoops_PSPI */
				*_hoops_PAPHR++ = 0;
				*_hoops_PAPHR++ = 0;

				if (_hoops_HPCHR == 0) {
					/* _hoops_PSP _hoops_ISSC _hoops_HIPH - _hoops_SAHR _hoops_HSPP _hoops_RH _hoops_CPCHR _hoops_HIGR */
					*_hoops_RPIPR++ = vertex1;
					*_hoops_RPIPR++ = vertex2;
				}
				else {
					in = _hoops_IPCHR + (_hoops_HPCHR + _hoops_HPCHR);
					_hoops_PPIPR = _hoops_IPCHR + 4; /* _hoops_PHHR _hoops_ISSC _hoops_RGAR _hoops_HIS _hoops_SGIP */

					/* _hoops_RH _hoops_CGHI _hoops_PPSR _hoops_IIGR _hoops_RH _hoops_HIGR _hoops_RHCHR _hoops_ISCP 1_hoops_ICPC _hoops_PPSR */
					*_hoops_RPIPR++ = in[-2];
					*_hoops_RPIPR++ = in[-4];

					_hoops_RGGA (in == _hoops_PPIPR) {
						*_hoops_RPIPR++ = in[-6];		/* _hoops_GPHA 3 */
						*_hoops_PAPHR++ = in[-1];		/* _hoops_HSP _hoops_PHI */
						in -= 2;

						*_hoops_RPIPR++ = in[-6];		/* _hoops_GPHA 3 */
						*_hoops_PAPHR++ = in[-1];		/* _hoops_HSP _hoops_PHI */
						in -= 2;
					}

					*_hoops_RPIPR++ = vertex1;
					*_hoops_PAPHR++ = in[-1];

					*_hoops_RPIPR++ = vertex2;
					*_hoops_PAPHR++ = in[-3];
				}


				/*
				 * _hoops_AGGA _hoops_AA _hoops_RH _hoops_CPCHR _hoops_AHAP - _hoops_GSGS _hoops_GSGS _hoops_GSGS _hoops_RCAC
				 */

				in = _hoops_PPCHR;
				_hoops_PPIPR = _hoops_PPCHR + (_hoops_APCHR + _hoops_APCHR);

				while (in != _hoops_PPIPR) {
					*_hoops_RPIPR++ = *in++;
					*_hoops_PAPHR++ = *in++;
				}

				if (_hoops_AGPHR->face_attributes.region != ts->face_attributes.region)
					ts->face_attributes.region = -1;	/* _hoops_CCPHR */

				_hoops_ICPHR = _hoops_AGPHR->_hoops_GRHPR;

				if (_hoops_AGPHR->_hoops_HPHHR > 0)
					FREE_ARRAY (_hoops_AGPHR->_hoops_APHHR, 2*_hoops_AGPHR->_hoops_HPHHR, int);
				if (_hoops_AGPHR->_hoops_IPHHR > 0)
					FREE_ARRAY (_hoops_AGPHR->_hoops_PPHHR, 2*_hoops_AGPHR->_hoops_IPHHR, int);
				FREE (_hoops_AGPHR, _hoops_RPHHR);
			} while ((_hoops_AGPHR = _hoops_ICPHR) != null);

			if (_hoops_AGPHR != null)	{	// _hoops_HAR _hoops_CPHR _hoops_CCA _hoops_RGR _hoops_SSAI _hoops_GAPR
				_hoops_PCPHR = _hoops_AGPHR;		// _hoops_HIS _hoops_HS _hoops_CRIPR _hoops_HAPR _hoops_APHS _hoops_SCH
				_hoops_AGPHR->up = _hoops_HCPHR;
			}
		}
	} while ((_hoops_AGPHR = _hoops_PCPHR) != null);

	if (BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_AHCHR)) {
		float			_hoops_PHCHR;
		char			_hoops_HHCHR[80], _hoops_IHCHR[80];

		_hoops_PHCHR = (float)_hoops_GPCHR / (float)_hoops_SACHR;

		_hoops_CHCHR (_hoops_HHCHR, "%d strips averaging %f points", _hoops_SACHR, _hoops_PHCHR);
		Sprintf_D  (_hoops_IHCHR, "longest strip is %d points", _hoops_RPCHR);

		_hoops_SHCHR (HEC_DEBUG, HES_DEBUG, _hoops_HHCHR, _hoops_IHCHR);
	}
}


#ifndef DISABLE_ERROR_WARNING_INFO
local void _hoops_GICHR (
	Shell			*_hoops_SPHPR,
	_hoops_CPHHR		*info) {
	_hoops_HRHHR		**table = info->_hoops_SPHHR;
	long			size = info->_hoops_RHHHR;
	_hoops_HRHHR		*edge;
	Key				key = _hoops_SPHPR->key;
	char			_hoops_RICHR[8][120];
	char const		*_hoops_AICHR[10];
	int				_hoops_PICHR = 0;
	int				_hoops_IAIPR = 0;

	_hoops_RICHR[0][0] = '\0';
	do {
		if ((edge = *table++) != null) do {
			while (edge != null && edge->_hoops_CRHHR != null)
				edge = edge->next;

			if (edge != null) {
				_hoops_HRHHR		*test = edge->next;

				while (test != null &&
						test->vertex1 == edge->vertex1 &&
						test->vertex2 == edge->vertex2) {
					if (test->_hoops_CRHHR == null &&
						edge->_hoops_IRHHR->face != test->_hoops_IRHHR->face) {
						char			pair[64];
						int				length;

						HI_Sprintf4 (null, pair, "(%d,%d)",
									 edge->_hoops_IRHHR->face,
									 test->_hoops_IRHHR->face,
									 null, null);
						length = _hoops_SSGR (pair);

						if (_hoops_IAIPR > 0) {
							_hoops_HPRPR (", ", _hoops_RICHR[_hoops_PICHR]);
							_hoops_IAIPR += 2;
						}

						if (_hoops_IAIPR + length > 72) {
							if (_hoops_PICHR == _hoops_GGAPR(_hoops_RICHR)-2) {
								_hoops_HPRPR ("etc...", _hoops_RICHR[_hoops_PICHR]);
								goto done;
							}

							++_hoops_PICHR;
							_hoops_RICHR[_hoops_PICHR][0] = '\0';
							_hoops_IAIPR = 0;
						}

						_hoops_HPRPR (pair, _hoops_RICHR[_hoops_PICHR]);
						_hoops_IAIPR += length;
					}
					test = test->next;
				}

				edge = test;
			}
		} while (edge != null);
	} _hoops_RGGA (--size == 0);

  done:
	if (_hoops_IAIPR > 0)
		++_hoops_PICHR;
	if (_hoops_PICHR > 0) {
		int				i;

		_hoops_SPHPR->polyhedron_flags &= ~_hoops_PGAHR;

		char buf[512];
		_hoops_AICHR[0] = HI_Sprintf4(null,buf,"Shell with key %D has one or more pairs of adjacent",0,0,(void*)&key,null);
		_hoops_AICHR[1] = "	 faces which connect with inconsistent handedness:";
		for (i=0; i<_hoops_PICHR; ++i)
			_hoops_AICHR[i+2] = _hoops_RICHR[i];

		HI_Generate_Error (null, HEC_GEOMETRY_OR_SEGMENT, HES_NON_UNIFORM_HANDEDNESS,
							1, _hoops_PICHR+2, _hoops_AICHR);
	}
}
#endif

#ifndef DISABLE_NON_MANIFOLD_OPTIMIZATION
local void _hoops_HICHR (
	Shell			*_hoops_SPHPR,
	_hoops_CPHHR		*info) {
	_hoops_HRHHR		**table = info->_hoops_SPHHR;
	long			size = info->_hoops_RHHHR;
	_hoops_HRHHR		*edge;
	_hoops_ARPA			*_hoops_PRHH;

	if ((_hoops_PRHH = _hoops_SPHPR->local_face_attributes.normals) == null)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Normals undone.");

	do {
		if ((edge = *table++) != null) do {
			_hoops_HRHHR		*test = edge->next;

			while (test != null &&
					test->vertex1 == edge->vertex1 &&
					test->vertex2 == edge->vertex2) {
				if (edge->_hoops_CRHHR != null || test->_hoops_CRHHR != null) {
					/* _hoops_HPGR _hoops_CHGC 3 _hoops_PAR 4 _hoops_RSSI _hoops_IICHR _hoops_IS _hoops_RGR _hoops_ISHA,
					** _hoops_CACH _hoops_RPP _hoops_CICHR _hoops_RH _hoops_IRPR _hoops_PSAI _hoops_IIGR _hoops_HIPH
					** _hoops_AAAA _hoops_IHHH _hoops_IRS "_hoops_RRI _hoops_SICHR" _hoops_HSP _hoops_GCCHR
					*/
					_hoops_ARPA		*_hoops_RCCHR, *_hoops_ACCHR, *_hoops_PCCHR, *_hoops_HCCHR;
					float			_hoops_ICCHR, _hoops_CCCHR;
					float			_hoops_SCCHR, _hoops_GSCHR;
					_hoops_PRHHR	*_hoops_RCHHR;
					int				_hoops_RSCHR, _hoops_ASCHR;

					/* _hoops_GSSR(_hoops_GRI) _hoops_IH "_hoops_ISHA" _hoops_HSP(_hoops_GRI) _hoops_PPR _hoops_PAII _hoops_PSCHR _hoops_HPAHR */
					_hoops_RCCHR = &_hoops_PRHH[edge->_hoops_IRHHR->face];
					if (edge->_hoops_CRHHR != null) {
						_hoops_ACCHR = &_hoops_PRHH[edge->_hoops_CRHHR->face];
						_hoops_ICCHR = _hoops_RCCHR->a * _hoops_ACCHR->a +
									_hoops_RCCHR->b * _hoops_ACCHR->b +
									 _hoops_RCCHR->c * _hoops_ACCHR->c;
					}
					else {
						_hoops_ACCHR = null;
						_hoops_ICCHR = 0.0f;
					}

					/* _hoops_GSSR(_hoops_GRI) _hoops_IH "_hoops_RPGP" _hoops_HSP(_hoops_GRI) _hoops_PPR _hoops_PAII _hoops_PSCHR _hoops_HPAHR */
					_hoops_PCCHR = &_hoops_PRHH[test->_hoops_IRHHR->face];
					if (test->_hoops_CRHHR != null) {
						_hoops_HCCHR = &_hoops_PRHH[test->_hoops_CRHHR->face];
						_hoops_SCCHR = _hoops_PCCHR->a * _hoops_HCCHR->a +
									_hoops_PCCHR->b * _hoops_HCCHR->b +
									 _hoops_PCCHR->c * _hoops_HCCHR->c;
					}
					else {
						_hoops_HCCHR = null;
						_hoops_SCCHR = 0.0f;
					}

					/* _hoops_RRP _hoops_IS _hoops_CAHA _hoops_HSCHR _hoops_IIGR _hoops_RPGP _hoops_HSHHR
					 * (_hoops_PPR _hoops_PRGPR _hoops_GACC _hoops_ISCHR _hoops_RPP _hoops_GPRI) _hoops_CSCHR _hoops_IS
					 * _hoops_ISHA _hoops_HSHHR
					 */
					/* _hoops_SR _hoops_AHGC _hoops_SGS _hoops_RH _hoops_SRS _hoops_GPHA _hoops_HRGR _hoops_RH _hoops_HSPP _hoops_IIGR
					 * _hoops_ISCP _hoops_SPPR
					 */
					_hoops_RSCHR = _hoops_ASCHR = edge->vertex1;	/* _hoops_AHGC */

					_hoops_RCHHR = edge->_hoops_IRHHR;

					/* _hoops_SPS _hoops_SR _hoops_IHSH _hoops_HPGR _hoops_RH _hoops_HSPR _hoops_ISHA -- _hoops_RPP _hoops_SCH _hoops_HRGR
					 * _hoops_RIHA _hoops_IS _hoops_SGS _hoops_GPHA _hoops_ISCP _hoops_AHGC _hoops_CSAP _hoops_RHPH
					 */
					if (_hoops_RCHHR->_hoops_HAHHR == edge) {
						if (_hoops_RSCHR == _hoops_RCHHR->_hoops_IAHHR->vertex1 ||
							_hoops_RSCHR == _hoops_RCHHR->_hoops_IAHHR->vertex2)
							_hoops_RSCHR = edge->vertex2;
					}
					else if (_hoops_RCHHR->_hoops_IAHHR == edge) {
						if (_hoops_RSCHR == _hoops_RCHHR->_hoops_CAHHR->vertex1 ||
							_hoops_RSCHR == _hoops_RCHHR->_hoops_CAHHR->vertex2)
							_hoops_RSCHR = edge->vertex2;
					}
					else if (_hoops_RCHHR->_hoops_CAHHR == edge) {
						if (_hoops_RCHHR->_hoops_SAHHR != null) {	/* _hoops_PCPI */
							if (_hoops_RSCHR == _hoops_RCHHR->_hoops_SAHHR->vertex1 ||
								_hoops_RSCHR == _hoops_RCHHR->_hoops_SAHHR->vertex2)
								_hoops_RSCHR = edge->vertex2;
						}
						else {							/* _hoops_SCPH */
							if (_hoops_RSCHR == _hoops_RCHHR->_hoops_HAHHR->vertex1 ||
								_hoops_RSCHR == _hoops_RCHHR->_hoops_HAHHR->vertex2)
								_hoops_RSCHR = edge->vertex2;
						}
					}
					else if (_hoops_RCHHR->_hoops_SAHHR == edge) {
						if (_hoops_RSCHR == _hoops_RCHHR->_hoops_HAHHR->vertex1 ||
							_hoops_RSCHR == _hoops_RCHHR->_hoops_HAHHR->vertex2)
							_hoops_RSCHR = edge->vertex2;
					}

					/* _hoops_APHS _hoops_GPP "_hoops_RPGP" */
					_hoops_RCHHR = test->_hoops_IRHHR;

					if (_hoops_RCHHR->_hoops_HAHHR == test) {
						if (_hoops_ASCHR == _hoops_RCHHR->_hoops_IAHHR->vertex1 ||
							_hoops_ASCHR == _hoops_RCHHR->_hoops_IAHHR->vertex2)
							_hoops_ASCHR = test->vertex2;
					}
					else if (_hoops_RCHHR->_hoops_IAHHR == test) {
						if (_hoops_ASCHR == _hoops_RCHHR->_hoops_CAHHR->vertex1 ||
							_hoops_ASCHR == _hoops_RCHHR->_hoops_CAHHR->vertex2)
							_hoops_ASCHR = test->vertex2;
					}
					else if (_hoops_RCHHR->_hoops_CAHHR == test) {
						if (_hoops_RCHHR->_hoops_SAHHR != null) {	/* _hoops_PCPI */
							if (_hoops_ASCHR == _hoops_RCHHR->_hoops_SAHHR->vertex1 ||
								_hoops_ASCHR == _hoops_RCHHR->_hoops_SAHHR->vertex2)
								_hoops_ASCHR = test->vertex2;
						}
						else {							/* _hoops_SCPH */
							if (_hoops_ASCHR == _hoops_RCHHR->_hoops_HAHHR->vertex1 ||
								_hoops_ASCHR == _hoops_RCHHR->_hoops_HAHHR->vertex2)
								_hoops_ASCHR = test->vertex2;
						}
					}
					else if (_hoops_RCHHR->_hoops_SAHHR == test) {
						if (_hoops_ASCHR == _hoops_RCHHR->_hoops_HAHHR->vertex1 ||
							_hoops_ASCHR == _hoops_RCHHR->_hoops_HAHHR->vertex2)
							/* _hoops_SSCHR, _hoops_RII _hoops_PPRRR */
							_hoops_ASCHR = test->vertex2;
					}


					if (_hoops_RSCHR == _hoops_ASCHR) {
						/* _hoops_HSHHR'_hoops_GRI _hoops_GGR _hoops_PSHR _hoops_AGR, _hoops_GAAP _hoops_GGSHR _hoops_RGSHR'_hoops_GRI */
						if (_hoops_HCCHR != null)
							_hoops_CCCHR = _hoops_RCCHR->a * _hoops_HCCHR->a +
										  _hoops_RCCHR->b * _hoops_HCCHR->b +
										   _hoops_RCCHR->c * _hoops_HCCHR->c;
						else
							_hoops_CCCHR = 0.0f;

						if (_hoops_ACCHR != null)
							_hoops_GSCHR = _hoops_PCCHR->a * _hoops_ACCHR->a +
										  _hoops_PCCHR->b * _hoops_ACCHR->b +
										   _hoops_PCCHR->c * _hoops_ACCHR->c;
						else
							_hoops_GSCHR = 0.0f;

						if (_hoops_CCCHR + _hoops_GSCHR > _hoops_ICCHR + _hoops_SCCHR) {
							Swap (edge->_hoops_CRHHR, test->_hoops_CRHHR);

							if ((_hoops_RCHHR = edge->_hoops_CRHHR) != null) {
								if (_hoops_RCHHR->_hoops_HAHHR == test)
									_hoops_RCHHR->_hoops_HAHHR = edge;
								else if (_hoops_RCHHR->_hoops_IAHHR == test)
									_hoops_RCHHR->_hoops_IAHHR = edge;
								else if (_hoops_RCHHR->_hoops_CAHHR == test)
									_hoops_RCHHR->_hoops_CAHHR = edge;
								else if (_hoops_RCHHR->_hoops_SAHHR == test)
									_hoops_RCHHR->_hoops_SAHHR = edge;
							}
							if ((_hoops_RCHHR = test->_hoops_CRHHR) != null) {
								if (_hoops_RCHHR->_hoops_HAHHR == edge)
									_hoops_RCHHR->_hoops_HAHHR = test;
								else if (_hoops_RCHHR->_hoops_IAHHR == edge)
									_hoops_RCHHR->_hoops_IAHHR = test;
								else if (_hoops_RCHHR->_hoops_CAHHR == edge)
									_hoops_RCHHR->_hoops_CAHHR = test;
								else if (_hoops_RCHHR->_hoops_SAHHR == edge)
									_hoops_RCHHR->_hoops_SAHHR = test;
							}
						}
					}
					else if (edge->_hoops_CRHHR != null) {
						/* _hoops_PGCHR, _hoops_GAAP _hoops_GGSHR _hoops_ISHA _hoops_RGSHR _hoops_CCA _hoops_RPGP _hoops_AGSHR */
						_hoops_CCCHR = _hoops_RCCHR->a * _hoops_PCCHR->a +
									  _hoops_RCCHR->b * _hoops_PCCHR->b +
									   _hoops_RCCHR->c * _hoops_PCCHR->c;

						if (_hoops_ACCHR != null && _hoops_HCCHR != null)
							_hoops_GSCHR = _hoops_ACCHR->a * _hoops_HCCHR->a +
										  _hoops_ACCHR->b * _hoops_HCCHR->b +
										   _hoops_ACCHR->c * _hoops_HCCHR->c;
						else
							_hoops_GSCHR = 0.0f;

						if (_hoops_CCCHR + _hoops_GSCHR > _hoops_ICCHR + _hoops_SCCHR) {
							_hoops_SSAGR (test->_hoops_IRHHR);
							_hoops_SSAGR (edge->_hoops_CRHHR);
							Swap (edge->_hoops_CRHHR, test->_hoops_IRHHR);

							_hoops_RCHHR = edge->_hoops_CRHHR;
							if (_hoops_RCHHR->_hoops_HAHHR == test)
								_hoops_RCHHR->_hoops_HAHHR = edge;
							else if (_hoops_RCHHR->_hoops_IAHHR == test)
								_hoops_RCHHR->_hoops_IAHHR = edge;
							else if (_hoops_RCHHR->_hoops_CAHHR == test)
								_hoops_RCHHR->_hoops_CAHHR = edge;
							else if (_hoops_RCHHR->_hoops_SAHHR == test)
								_hoops_RCHHR->_hoops_SAHHR = edge;

							_hoops_RCHHR = test->_hoops_IRHHR;
							if (_hoops_RCHHR->_hoops_HAHHR == edge)
								_hoops_RCHHR->_hoops_HAHHR = test;
							else if (_hoops_RCHHR->_hoops_IAHHR == edge)
								_hoops_RCHHR->_hoops_IAHHR = test;
							else if (_hoops_RCHHR->_hoops_CAHHR == edge)
								_hoops_RCHHR->_hoops_CAHHR = test;
							else if (_hoops_RCHHR->_hoops_SAHHR == edge)
								_hoops_RCHHR->_hoops_SAHHR = test;
						}
					}
					else /* _hoops_RPP (_hoops_RPGP->_hoops_ISCHR != _hoops_IRAP) */ {
						/* _hoops_PGCHR, _hoops_GAAP _hoops_GGSHR _hoops_ISHA _hoops_AGSHR _hoops_CCA _hoops_RPGP _hoops_RGSHR */
						_hoops_CCCHR = 0.0f;

						_hoops_GSCHR = _hoops_PCCHR->a * _hoops_RCCHR->a +
									  _hoops_PCCHR->b * _hoops_RCCHR->b +
									   _hoops_PCCHR->c * _hoops_RCCHR->c;

						if (_hoops_CCCHR + _hoops_GSCHR > _hoops_ICCHR + _hoops_SCCHR) {
							Swap (edge->_hoops_IRHHR, test->_hoops_CRHHR);

							_hoops_RCHHR = edge->_hoops_IRHHR;
							if (_hoops_RCHHR->_hoops_HAHHR == test)
								_hoops_RCHHR->_hoops_HAHHR = edge;
							else if (_hoops_RCHHR->_hoops_IAHHR == test)
								_hoops_RCHHR->_hoops_IAHHR = edge;
							else if (_hoops_RCHHR->_hoops_CAHHR == test)
								_hoops_RCHHR->_hoops_CAHHR = edge;
							else if (_hoops_RCHHR->_hoops_SAHHR == test)
								_hoops_RCHHR->_hoops_SAHHR = edge;

							_hoops_RCHHR = test->_hoops_CRHHR;
							if (_hoops_RCHHR->_hoops_HAHHR == edge)
								_hoops_RCHHR->_hoops_HAHHR = test;
							else if (_hoops_RCHHR->_hoops_IAHHR == edge)
								_hoops_RCHHR->_hoops_IAHHR = test;
							else if (_hoops_RCHHR->_hoops_CAHHR == edge)
								_hoops_RCHHR->_hoops_CAHHR = test;
							else if (_hoops_RCHHR->_hoops_SAHHR == edge)
								_hoops_RCHHR->_hoops_SAHHR = test;
						}
					}
				}
				test = test->next;
			}
		} while ((edge = edge->next) != null);
	} _hoops_RGGA (--size == 0);
}
#endif



local void _hoops_PGSHR (
	Shell						*_hoops_SPHPR,
	_hoops_HRHHR					*_hoops_GRCPR,
	_hoops_CPHHR					*info) {
	_hoops_RPHHR			**temps = &info->temps;
	_hoops_HRHHR					*_hoops_HGSHR;
	_hoops_HRHHR					*_hoops_IGSHR = _hoops_GRCPR;
	_hoops_HRHHR					*_hoops_CGSHR;
	_hoops_HRHHR					*_hoops_SGSHR;
	_hoops_PRHHR				*_hoops_RCHHR;
	_hoops_RPHHR			*_hoops_AGPHR;
	Local_Face_Attributes		*_hoops_CPRI = null;
	int							*limit = info->_hoops_SRSPR + info->_hoops_GASPR;
	_hoops_HRHHR					*tail;

	if (_hoops_SPHPR != null)
		_hoops_CPRI = &_hoops_SPHPR->local_face_attributes;

	tail = _hoops_GRCPR;
	_hoops_RGGA (tail->next == null) tail = tail->next;

	_hoops_PCCAR {
		_hoops_SSAGR (_hoops_IGSHR->next);
		int							*_hoops_SRSPR = info->_hoops_SRSPR;
		/*
		 * _hoops_RAIGR _hoops_CCAH _hoops_APHR _hoops_ISHA. _hoops_HHIGR _hoops_PAH _hoops_SHH _hoops_GRSHR _hoops_PGI _hoops_PPRRR; _hoops_SCH _hoops_PAH
		 * _hoops_HS _hoops_AHHR (_hoops_RPP _hoops_RH _hoops_HISS _hoops_HIPH _hoops_HS _hoops_AIAH _hoops_RPII _hoops_IGI
		 * _hoops_GH), _hoops_SPR, _hoops_PAR _hoops_IRS _hoops_IHIR _hoops_HSPPR _hoops_IIGR _hoops_PGCR _hoops_HISS _hoops_HIPH.
		 */
		if ((_hoops_RCHHR = _hoops_IGSHR->_hoops_IRHHR) == null) {
			/* _hoops_ISAP _hoops_HISS. _hoops_RRSHR. */
			_hoops_CGSHR = _hoops_IGSHR->next;
			FREE (_hoops_IGSHR, _hoops_HRHHR);
			if ((_hoops_IGSHR = _hoops_CGSHR) == null)
				break;
		}
		else {
			/*
			 * _hoops_GCIH _hoops_RICPR _hoops_HPP _hoops_SPAAR _hoops_IRS "_hoops_AGAPR" _hoops_CIGS _hoops_ISHA, _hoops_RPP _hoops_HAR
			 * _hoops_RH _hoops_SCGR.
			 */

			/* ('_hoops_ARSHR' _hoops_HRGR _hoops_IGI _hoops_IS _hoops_IRHC _hoops_RH _hoops_ISHA _hoops_HSPR _hoops_RH
			 *	_hoops_CIGS _hoops_ISHA, _hoops_GGR _hoops_RH _hoops_GIGR _hoops_CSSP _hoops_IIGR _hoops_RH _hoops_SCPH.)
			 */
			if (_hoops_IGSHR->_hoops_CRHHR != null) {
				/* _hoops_AGHI _hoops_HISS _hoops_HIPH - _hoops_IPHR _hoops_SSPP _hoops_HII _hoops_ARI */
				_hoops_HGSHR = _hoops_IGSHR;

				/* _hoops_IPRPR ("_hoops_PRSHR _hoops_ISHA _hoops_CCA _hoops_CSHHR %_hoops_GHGP\_hoops_ACHP", _hoops_HRSHR->_hoops_CSHHR); */

				if (_hoops_RCHHR->_hoops_SAHHR != null) {
					if (_hoops_HGSHR == _hoops_RCHHR->_hoops_HAHHR)
						_hoops_CGSHR = _hoops_RCHHR->_hoops_IAHHR;
					else if (_hoops_HGSHR == _hoops_RCHHR->_hoops_IAHHR)
						_hoops_CGSHR = _hoops_RCHHR->_hoops_CAHHR;
					else if (_hoops_HGSHR == _hoops_RCHHR->_hoops_CAHHR)
						_hoops_CGSHR = _hoops_RCHHR->_hoops_SAHHR;
					else
						_hoops_CGSHR = _hoops_RCHHR->_hoops_HAHHR;

					/* _hoops_GRS _hoops_HAR _hoops_RHHR _hoops_RH "_hoops_IRSHR _hoops_RSRA _hoops_SCPH" _hoops_AGIR _hoops_CAPP */
					_hoops_SGSHR = null;
				}
				else {
					if (_hoops_HGSHR == _hoops_RCHHR->_hoops_HAHHR) {
						_hoops_CGSHR = _hoops_RCHHR->_hoops_IAHHR;
						_hoops_SGSHR = _hoops_RCHHR->_hoops_CAHHR;
					}
					else if (_hoops_HGSHR == _hoops_RCHHR->_hoops_IAHHR) {
						_hoops_CGSHR = _hoops_RCHHR->_hoops_CAHHR;
						_hoops_SGSHR = _hoops_RCHHR->_hoops_HAHHR;
					}
					else {
						_hoops_CGSHR = _hoops_RCHHR->_hoops_HAHHR;
						_hoops_SGSHR = _hoops_RCHHR->_hoops_IAHHR;
					}
				}

				/* (_hoops_PS *_hoops_HHS* _hoops_HPPR _hoops_IS _hoops_SSS _hoops_GIPR _hoops_IIGR _hoops_RH _hoops_CCGI _hoops_SGS _hoops_CRSHR
				 *	_hoops_RGR _hoops_ISHA, _hoops_PPR _hoops_SRSHR _hoops_RH _hoops_CPIS, _hoops_HIH _hoops_SCH'_hoops_GRI _hoops_GASHR
				 *	_hoops_SGS _hoops_SGS _hoops_HGIRR'_hoops_RA _hoops_IGRC _hoops_RASHR _hoops_RH _hoops_AASHR _hoops_SPCC
				 *	_hoops_GSGS _hoops_PAR _hoops_HPGR _hoops_HCR. _hoops_PASHR _hoops_GGR _hoops_HASHR _hoops_ARAR. _hoops_CRSR _hoops_GHCA
				 *	_hoops_SHH _hoops_PPCAR. _hoops_IASHR.)
				 */
			}
			else if (_hoops_IGSHR->next != null && !_hoops_IGSHR->_hoops_RAHHR) {
				/* _hoops_ICAGR _hoops_SCPH _hoops_HISS _hoops_IS _hoops_RGR _hoops_ISHA - _hoops_PSCPR */

				/* _hoops_IPRPR ("_hoops_CASHR _hoops_ISHA _hoops_CCA _hoops_CSHHR %_hoops_GHGP\_hoops_ACHP", _hoops_SASHR->_hoops_CSHHR); */

				_hoops_IGSHR->_hoops_RAHHR = true;
				_hoops_CGSHR = _hoops_IGSHR->next;
				tail->next = _hoops_IGSHR;  _hoops_IGSHR->next = null;  tail = _hoops_IGSHR;
				_hoops_IGSHR = _hoops_CGSHR;

				continue;
			}
			else {
				/* _hoops_ICAGR _hoops_SCPH _hoops_HISS _hoops_IS _hoops_RGR _hoops_ISHA - _hoops_SCH _hoops_GHCA _hoops_SHH
				 * _hoops_GIH _hoops_IS _hoops_HSPP _hoops_HII _hoops_PCCP _hoops_SCCPR _hoops_ISHA _hoops_SGS _hoops_SSCP _hoops_PGCR
				 * _hoops_HIPH (_hoops_RGR _hoops_SPR _hoops_PPR _hoops_HPIH) _hoops_HISS, _hoops_RPP _hoops_IIH
				 * _hoops_HRGR _hoops_GII _hoops_HGPP _hoops_ISHA. _hoops_HGI _hoops_CGRS-_hoops_ISHA _hoops_PPR _hoops_RSRA _hoops_SCPH
				 * _hoops_GRS _hoops_HGCR _hoops_GPSHR _hoops_PSP _hoops_RPSHR _hoops_PGAP _hoops_ISHA _hoops_SR _hoops_HSPP _hoops_HII.
				 */

				if (_hoops_RCHHR->_hoops_SAHHR != null) {
					if (_hoops_RCHHR->_hoops_HAHHR->_hoops_CRHHR != null) {
						_hoops_HGSHR = _hoops_RCHHR->_hoops_HAHHR;
						_hoops_CGSHR = _hoops_RCHHR->_hoops_IAHHR;
					}
					else if (_hoops_RCHHR->_hoops_IAHHR->_hoops_CRHHR != null) {
						_hoops_HGSHR = _hoops_RCHHR->_hoops_IAHHR;
						_hoops_CGSHR = _hoops_RCHHR->_hoops_CAHHR;
					}
					else if (_hoops_RCHHR->_hoops_CAHHR->_hoops_CRHHR != null) {
						_hoops_HGSHR = _hoops_RCHHR->_hoops_CAHHR;
						_hoops_CGSHR = _hoops_RCHHR->_hoops_SAHHR;
					}
					else {
						_hoops_HGSHR = _hoops_RCHHR->_hoops_SAHHR;
						_hoops_CGSHR = _hoops_RCHHR->_hoops_HAHHR;
					}

					/* _hoops_GRS _hoops_HAR _hoops_RHHR _hoops_RH "_hoops_IRSHR _hoops_RSRA _hoops_SCPH" _hoops_AGIR _hoops_CAPP */
					_hoops_SGSHR = null;
				}
				else {
					if (_hoops_RCHHR->_hoops_HAHHR->_hoops_CRHHR != null) {
						_hoops_HGSHR = _hoops_RCHHR->_hoops_HAHHR;
						_hoops_CGSHR = _hoops_RCHHR->_hoops_IAHHR;
						_hoops_SGSHR = _hoops_RCHHR->_hoops_CAHHR;
					}
					else if (_hoops_RCHHR->_hoops_IAHHR->_hoops_CRHHR != null) {
						_hoops_HGSHR = _hoops_RCHHR->_hoops_IAHHR;
						_hoops_CGSHR = _hoops_RCHHR->_hoops_CAHHR;
						_hoops_SGSHR = _hoops_RCHHR->_hoops_HAHHR;
					}
					else {
						_hoops_HGSHR = _hoops_RCHHR->_hoops_CAHHR;
						_hoops_CGSHR = _hoops_RCHHR->_hoops_HAHHR;
						_hoops_SGSHR = _hoops_RCHHR->_hoops_IAHHR;
					}
				}

				/* _hoops_IPRPR ("_hoops_APSHR _hoops_ISHA _hoops_CCA _hoops_CSHHR %_hoops_GHGP\_hoops_ACHP", _hoops_HRSHR->_hoops_CSHHR); */
			}


			/* _hoops_PPSHR _hoops_HISS - _hoops_SSS _hoops_IRS _hoops_IRHP-_hoops_CRHH. */

			ZALLOC (_hoops_AGPHR, _hoops_RPHHR);
			_hoops_AAPHR (_hoops_AGPHR->face_attributes);
			if (_hoops_CPRI != null)
				_hoops_PIPHR (_hoops_CPRI, _hoops_RCHHR->face, _hoops_AGPHR->face_attributes);

			/* _hoops_SR _hoops_HS _hoops_HHRPR _hoops_PCCP _hoops_ISHA _hoops_PPR _hoops_IRS _hoops_SCPH. _hoops_HPSHR _hoops_SGS _hoops_HSPP
			 * _hoops_ISHA, _hoops_IIH _hoops_CHR _hoops_PGCR _hoops_GIHA, _hoops_PGI _hoops_IIGR _hoops_PGAP _hoops_SR _hoops_HHS
			 * _hoops_HSRS _hoops_GAR _hoops_ISCP _hoops_HSPP _hoops_GPHA. _hoops_PHGP _hoops_SR _hoops_HSRS _hoops_RH _hoops_SPR _hoops_SGS
			 * _hoops_IPSHR _hoops_RH _hoops_GIGR _hoops_RSSP _hoops_IIGR _hoops_RH _hoops_SCPH -
			 * _hoops_SGS'_hoops_GRI _hoops_CPHR _hoops_HPP _hoops_CPSHR _hoops_RH _hoops_HSPP _hoops_GPHA _hoops_GAR _hoops_RH _hoops_SPR
			 * _hoops_PGAP *_hoops_GPGH'_hoops_RA* _hoops_GCSP _hoops_GAPA _hoops_SPSHR _hoops_PPR _hoops_ARSHR.
			 */
			if (_hoops_HGSHR->vertex1 == _hoops_CGSHR->vertex1 ||
				_hoops_HGSHR->vertex1 == _hoops_CGSHR->vertex2) {
				_hoops_AGPHR->_hoops_ISPI = _hoops_HGSHR->vertex2;
				_hoops_AGPHR->_hoops_CSPI = _hoops_HGSHR->vertex1;
			}
			else {
				_hoops_AGPHR->_hoops_ISPI = _hoops_HGSHR->vertex1;
				_hoops_AGPHR->_hoops_CSPI = _hoops_HGSHR->vertex2;
			}
			if (_hoops_SPHPR && _hoops_SPHPR->local_vertex_attributes._hoops_RCIHR != null) {
				_hoops_AGPHR->_hoops_ISPI = HI_Split_Point_Lookup ((Polyhedron const *)_hoops_SPHPR, _hoops_AGPHR->_hoops_ISPI, _hoops_RCHHR->face);
				_hoops_AGPHR->_hoops_CSPI = HI_Split_Point_Lookup ((Polyhedron const *)_hoops_SPHPR, _hoops_AGPHR->_hoops_CSPI, _hoops_RCHHR->face);
			}

			_hoops_AGPHR->_hoops_APHHR = _hoops_SRSPR;
			_hoops_SRSPR = _hoops_PCIHR (_hoops_SPHPR,
										   _hoops_HGSHR,
										   _hoops_RCHHR,
										   _hoops_AGPHR->_hoops_ISPI,
										   &_hoops_AGPHR->face_attributes,
										   _hoops_CPRI,
										   !_hoops_ACIHR,
										   _hoops_SRSPR, limit);
			_hoops_AGPHR->_hoops_HPHHR = (_hoops_SRSPR - _hoops_AGPHR->_hoops_APHHR)/2;

			/*
			 * _hoops_PS _hoops_HA _hoops_HS _hoops_IRS _hoops_CRHH _hoops_CPIC _hoops_CPCHR _hoops_HII _hoops_RH _hoops_CIGS
			 * _hoops_ISHA _hoops_PPR _hoops_PGAP _hoops_GHSHR _hoops_RH _hoops_RSSP _hoops_IIGR _hoops_RH _hoops_HSPP
			 * _hoops_SCPH.
			 */


			/*
			 * _hoops_CGP _hoops_SR _hoops_GGHP _hoops_RGAR _hoops_SPR _hoops_RHSHR _hoops_GPP _hoops_RH _hoops_CGHI _hoops_CPCHR _hoops_SPIC,
			 * _hoops_PPR _hoops_IIH'_hoops_GRI _hoops_HPIH _hoops_SCPH _hoops_HISS _hoops_IS _hoops_RH _hoops_HRSHR, _hoops_PSCR
			 * _hoops_SCH'_hoops_GRI _hoops_SSRR _hoops_IS _hoops_SPIC _hoops_CPCHR _hoops_GICS _hoops_HII _hoops_RH
			 * _hoops_RII _hoops_PPAP _hoops_IIGR _hoops_RH _hoops_CRSH _hoops_ISHA _hoops_IS _hoops_IRHI _hoops_RH _hoops_AHSHR _hoops_HIGR _hoops_IRS _hoops_IGRH
			 */
			if (_hoops_AGPHR->_hoops_HPHHR == 1 &&
				_hoops_HGSHR->_hoops_IRHHR != null &&
				(_hoops_CPRI == null ||
				 _hoops_IIPHR (_hoops_CPRI, _hoops_HGSHR->_hoops_IRHHR->face,
													  _hoops_AGPHR->face_attributes) &&
				 _hoops_HIIHR (_hoops_SPHPR, _hoops_HGSHR, _hoops_RCHHR->face, _hoops_HGSHR->_hoops_IRHHR->face))) {
				int		_hoops_PHSHR;

				_hoops_PHSHR = _hoops_SRSPR[-2];
				_hoops_SRSPR[-2] = _hoops_AGPHR->_hoops_CSPI;

				_hoops_SRSPR = _hoops_PCIHR (_hoops_SPHPR,
											   _hoops_HGSHR,
											   _hoops_HGSHR->_hoops_IRHHR,
											   _hoops_AGPHR->_hoops_ISPI,
											   &_hoops_AGPHR->face_attributes,
											   _hoops_CPRI,
											   !_hoops_ACIHR,
											   _hoops_SRSPR, limit);
				_hoops_AGPHR->_hoops_HPHHR = (_hoops_SRSPR - _hoops_AGPHR->_hoops_APHHR)/2;

				/*
				 * _hoops_IRSHR _hoops_RH _hoops_GIGR _hoops_SCPH _hoops_HPP _hoops_HHSHR _hoops_RGCI _hoops_SPPR
				 * _hoops_CPCHR _hoops_PPR _hoops_RH _hoops_GIHA _hoops_CPCHR _hoops_HPP _hoops_PGCR
				 */
				_hoops_CGSHR = _hoops_HGSHR;
				_hoops_HGSHR = _hoops_SGSHR;
				/* _hoops_PSP _hoops_RRP _hoops_IS _hoops_HIAP _hoops_IHSHR */

				_hoops_AGPHR->_hoops_CSPI = _hoops_AGPHR->_hoops_ISPI;
				_hoops_AGPHR->_hoops_ISPI = _hoops_PHSHR;
			}


			/*
			 * _hoops_AGGA _hoops_SPIC _hoops_ISSC _hoops_RH _hoops_RII _hoops_PPRRR, _hoops_APHR _hoops_CCA _hoops_CIHHR, _hoops_PSCR
			 * _hoops_IIHHR, _hoops_PSCR _hoops_RH _hoops_GIAP _hoops_SCPH _hoops_ARI (_hoops_RPP _hoops_IIH _hoops_HRGR _hoops_SPR.)
			 */
			
			if (_hoops_HGSHR->_hoops_IRHHR != null && /* _hoops_PSP _hoops_RRI _hoops_CHSHR */
				(_hoops_CPRI == null ||
				 _hoops_IIPHR (_hoops_CPRI, _hoops_HGSHR->_hoops_IRHHR->face,
													  _hoops_AGPHR->face_attributes) &&
			     (limit - _hoops_SRSPR) >= 4 &&		// _hoops_RSIAR _hoops_IS _hoops_SHH _hoops_GHCAR
				 _hoops_HIIHR (_hoops_SPHPR, _hoops_HGSHR, _hoops_RCHHR->face, _hoops_HGSHR->_hoops_IRHHR->face))) {
				bool _hoops_SHSHR;

				_hoops_SHSHR = BIT (_hoops_AGPHR->_hoops_HPHHR, 1);

				_hoops_AGPHR->_hoops_PPHHR = _hoops_SRSPR;
				_hoops_SRSPR = _hoops_PCIHR (_hoops_SPHPR,
											   _hoops_HGSHR,
											   _hoops_HGSHR->_hoops_IRHHR,
											   _hoops_AGPHR->_hoops_CSPI,
											   &_hoops_AGPHR->face_attributes,
											   _hoops_CPRI,
											   _hoops_SHSHR,
											   _hoops_SRSPR, limit);
				_hoops_AGPHR->_hoops_IPHHR = (_hoops_SRSPR - _hoops_AGPHR->_hoops_PPHHR) / 2;
			}
			else {
				/* _hoops_CPIC _hoops_RH _hoops_RII _hoops_PPRRR _hoops_HRGR _hoops_HAGH, _hoops_RRS _hoops_ARI */
				_hoops_AGPHR->_hoops_PPHHR = null;
				_hoops_AGPHR->_hoops_IPHHR = 0;
			}

			_hoops_CSHPR (_hoops_AGPHR, temps);

			/* _hoops_IPRPR ("_hoops_GISHR (%_hoops_GHGP, %_hoops_GHGP)\_hoops_ACHP", _hoops_RISHR->_hoops_AISHR, _hoops_RISHR->_hoops_PISHR); */
		}
	}
}



typedef struct _hoops_HISHR {
	struct _hoops_HISHR	*next;
	int							vertex;
	_hoops_HRHHR					*_hoops_PPGHR;
	_hoops_PRHHR				*_hoops_IISHR;
	bool					_hoops_CIPAR;
}		_hoops_CISHR;

local void _hoops_SISHR (
	Shell				*_hoops_SPHPR,
	_hoops_HRHHR				*_hoops_GCSHR) {
	_hoops_CISHR		*_hoops_RCSHR = null,
										**_hoops_ACSHR = &_hoops_RCSHR;
	_hoops_HRHHR				*edge;
	_hoops_CISHR		*_hoops_PCSHR;

	if (_hoops_GCSHR == null) return;

	if (_hoops_SPHPR->local_vertex_attributes.normals == null)
		HI_Initialize_Vertex_Attributes ((Polyhedron *)_hoops_SPHPR, LVA_EXPLICIT_NORMAL,0);

	if (!BIT (_hoops_SPHPR->polyhedron_flags, PHF_FACE_NORMALS_VALID))
		HI_Assemble_Face_Normals ((Polyhedron *)_hoops_SPHPR);

	/* _hoops_HSRR _hoops_GRR _hoops_GPHA _hoops_IIGR _hoops_GRR _hoops_ISHA, _hoops_RPP _hoops_SCH _hoops_SSCP _hoops_HAR _hoops_RPII _hoops_HPSPR _hoops_ARPP _hoops_PPR
	 * _hoops_RPP _hoops_RH _hoops_GSSR _hoops_GPGH'_hoops_RA _hoops_GRGA _hoops_ARP, _hoops_SPIC _hoops_AARI _hoops_RH _hoops_GPHA _hoops_SIIAR
	 * _hoops_RH _hoops_ASGA.
	 */
	_hoops_PCCAR {
		_hoops_HRHHR				*_hoops_PPGHR;
		_hoops_PRHHR			*_hoops_IISHR;
		bool				_hoops_CIPAR;
		int						vertex;

		/* _hoops_RGR '_hoops_HPGP' _hoops_CGH _hoops_HAPR _hoops_GGSR _hoops_ARR _hoops_RIR _hoops_HCSHR _hoops_ICSHR */
		edge = _hoops_GCSHR; /* _hoops_CRGR _hoops_IRS _hoops_GCPR */
		while (!(edge->_hoops_AAHHR == _hoops_GGHHR)) {
			if ((edge = edge->next) == null) {
				_hoops_SPHPR->polyhedron_flags |= PHF_VERTEX_NORMALS_VALID;
				return;
			}
		}
		_hoops_GCSHR = edge; /* _hoops_ISSC _hoops_GGSR */

		/* _hoops_HSPP _hoops_HCHAR _hoops_HPGR _hoops_SCH */
		_hoops_PPGHR = edge;
		_hoops_IISHR = edge->_hoops_IRHHR;
		vertex = edge->vertex1;
		_hoops_CIPAR = false; /* _hoops_CCSHR */

		/* _hoops_HPPP _hoops_HCR _hoops_RH _hoops_RIHA _hoops_SCSHR */
		_hoops_PCCAR {
			Vector		_hoops_ARAHR;
			_hoops_PRHHR	*_hoops_RCHHR;
			bool		_hoops_PCHR;

			_hoops_ARAHR.x = 0.0f;
			_hoops_ARAHR.y = 0.0f;
			_hoops_ARAHR.z = 0.0f;

			/* _hoops_SPIC _hoops_AARI _hoops_RGR _hoops_GPHA _hoops_APHR _hoops_HPGR _hoops_RGR _hoops_ISHA _hoops_PPR _hoops_CPIC _hoops_GIPR _hoops_ASRAR. */

			/* _hoops_IPCP _hoops_SPPR _hoops_GIAA _hoops_IRS _hoops_SCPH _hoops_CHR _hoops_GICPR _hoops_IS _hoops_SHH _hoops_GGR _hoops_AGR _hoops_CCA
			 * _hoops_GPCAR _hoops_IS _hoops_RH _hoops_HSP/_hoops_SCPH _hoops_GSSR; _hoops_RH _hoops_RSSA _hoops_GIAA _hoops_PCCP _hoops_ISHA _hoops_CHR
			 * _hoops_GGR _hoops_PSP _hoops_SAGHR _hoops_AGR.
			 */

			/* _hoops_PS _hoops_HPPP _hoops_SPR _hoops_GPHA _hoops_CCGC, _hoops_PPR _hoops_GSSHR _hoops_HCR _hoops_RH
			 * _hoops_RSSHR _hoops_ASSHR _hoops_GIHA _hoops_CCA _hoops_RH _hoops_IRPR _hoops_PSSHR.
			 * _hoops_IPCP _hoops_HSSHR _hoops_HRGR _hoops_AAIHR _hoops_IS _hoops_SHH _hoops_ISSHR-_hoops_SRS, _hoops_HIS _hoops_RH _hoops_PHI _hoops_IIGR
			 * '_hoops_CSSHR' _hoops_HCCGR _hoops_HRGR _hoops_SSSHR _hoops_IS _hoops_GGGIR _hoops_HPGR _hoops_RGGIR(_hoops_AGGIR(_hoops_PGGIR)).
			 */

#		define QUEUE_ONE(_hoops_HGGIR, _hoops_IGGIR, _hoops_CGGIR, _hoops_SGGIR, _hoops_GRGIR) do {\
			if ((_hoops_HGGIR) == _hoops_GGHHR) {					\
				ALLOC (_hoops_PCSHR, _hoops_CISHR);				\
				*_hoops_ACSHR = _hoops_PCSHR;								\
				_hoops_ACSHR = &_hoops_PCSHR->next;						\
				_hoops_PCSHR->next = null;								\
				_hoops_PCSHR->vertex = _hoops_IGGIR;							\
				_hoops_PCSHR->_hoops_PPGHR = _hoops_CGGIR;						\
				_hoops_PCSHR->_hoops_IISHR = _hoops_SGGIR;				\
				_hoops_PCSHR->_hoops_CIPAR = _hoops_GRGIR;						\
				_hoops_HGGIR = _hoops_AGHHR;							\
			}} while (0)


			edge = _hoops_PPGHR;
			_hoops_RCHHR = _hoops_IISHR;

			if (edge->vertex1 == vertex) {
				if (edge->_hoops_AAHHR == _hoops_RGHHR) goto _hoops_RRGIR;
				edge->_hoops_AAHHR = _hoops_RGHHR;
				QUEUE_ONE (edge->_hoops_PAHHR, edge->vertex2, edge, _hoops_RCHHR, !_hoops_CIPAR);
			}
			else {
				if (edge->_hoops_PAHHR == _hoops_RGHHR) goto _hoops_RRGIR;
				edge->_hoops_PAHHR = _hoops_RGHHR;
				QUEUE_ONE (edge->_hoops_AAHHR, edge->vertex1, edge, _hoops_RCHHR, !_hoops_CIPAR);
			}

			/* _hoops_PH _hoops_ARGIR _hoops_IGIAR _hoops_IH _hoops_RH _hoops_RCHAR _hoops_HAPR */
			if (_hoops_RCHHR == edge->_hoops_IRHHR)
				_hoops_IISHR = edge->_hoops_CRHHR;
			else
				_hoops_IISHR = edge->_hoops_IRHHR;

			_hoops_PCCAR {
				_hoops_ARPA				*_hoops_HRAHR;

				_hoops_HRAHR = &_hoops_SPHPR->local_face_attributes.normals[_hoops_RCHHR->face];

				/* _hoops_SSS _hoops_RH _hoops_RII _hoops_ISHA _hoops_IIGR _hoops_RGR _hoops_SCPH _hoops_PGAP _hoops_PRCHR _hoops_RGR _hoops_GPHA */

				if (edge == _hoops_RCHHR->_hoops_HAHHR) {
					edge = _hoops_RCHHR->_hoops_IAHHR;		/* _hoops_IRHH _hoops_IRS _hoops_AHGC */
					if (edge->vertex1 == vertex || edge->vertex2 == vertex) {
						_hoops_PCHR = false;
					}
					else {
						if (_hoops_RCHHR->_hoops_SAHHR != null)
							edge = _hoops_RCHHR->_hoops_SAHHR;
						else
							edge = _hoops_RCHHR->_hoops_CAHHR;
						_hoops_PCHR = !false; /* _hoops_CACH _hoops_PIP _hoops_GPP == _hoops_PIIA */
					}
				}
				else if (edge == _hoops_RCHHR->_hoops_IAHHR) {
					edge = _hoops_RCHHR->_hoops_CAHHR;		/* _hoops_IRHH _hoops_IRS _hoops_AHGC */
					if (edge->vertex1 == vertex || edge->vertex2 == vertex) {
						_hoops_PCHR = false;
					}
					else {
						edge = _hoops_RCHHR->_hoops_HAHHR;
						_hoops_PCHR = !false; /* _hoops_CACH _hoops_PIP _hoops_GPP == _hoops_PIIA */
					}
				}
				else if (edge == _hoops_RCHHR->_hoops_CAHHR) {
					if (_hoops_RCHHR->_hoops_SAHHR != null)
						edge = _hoops_RCHHR->_hoops_SAHHR;		/* _hoops_IRHH _hoops_IRS _hoops_AHGC */
					else
						edge = _hoops_RCHHR->_hoops_HAHHR;		/* _hoops_IRHH _hoops_IRS _hoops_AHGC */
					if (edge->vertex1 == vertex || edge->vertex2 == vertex) {
						_hoops_PCHR = false;
					}
					else {
						edge = _hoops_RCHHR->_hoops_IAHHR;
						_hoops_PCHR = !false; /* _hoops_CACH _hoops_PIP _hoops_GPP == _hoops_PIIA */
					}
				}
				else {
					edge = _hoops_RCHHR->_hoops_HAHHR;		/* _hoops_IRHH _hoops_IRS _hoops_AHGC */
					if (edge->vertex1 == vertex || edge->vertex2 == vertex) {
						_hoops_PCHR = false;
					}
					else {
						edge = _hoops_RCHHR->_hoops_CAHHR;
						_hoops_PCHR = !false; /* _hoops_CACH _hoops_PIP _hoops_GPP == _hoops_PIIA */
					}
				}

				/* _hoops_RGR == _hoops_HRGR _hoops_PRGIR, _hoops_AHSAR _hoops_SR _hoops_ACPA _hoops_SGS _hoops_HRGIR
				 * _hoops_PPR _hoops_PIIA _hoops_HS _hoops_RPII _hoops_ARP _hoops_ACCP _hoops_IS '!_hoops_RCPP' _hoops_PAR
				 * '_hoops_RCPP' _hoops_PPR _hoops_ISAP _hoops_SHS.
				 *
				 * _hoops_HHIGR'_hoops_GHGP _hoops_SHH _hoops_AGAPR _hoops_RPP _hoops_IHRPR _hoops_RIAGR _hoops_IRS _hoops_IRGIR "_hoops_SICHR _hoops_CRGIR"
				 * _hoops_SIRRR.
				 */
				if (_hoops_PCHR == _hoops_CIPAR) {
					_hoops_ARAHR.x += _hoops_HRAHR->a;
					_hoops_ARAHR.y += _hoops_HRAHR->b;
					_hoops_ARAHR.z += _hoops_HRAHR->c;
				}
				else {
					_hoops_ARAHR.x -= _hoops_HRAHR->a;
					_hoops_ARAHR.y -= _hoops_HRAHR->b;
					_hoops_ARAHR.z -= _hoops_HRAHR->c;
				}

				/* _hoops_RRS _hoops_RPP _hoops_SR _hoops_CGRI _hoops_HCR _hoops_RH _hoops_PPRRR _hoops_AARI */
				if (edge == _hoops_PPGHR) {
					_hoops_IISHR = null;		/* _hoops_RIP _hoops_RH _hoops_SPS _hoops_HAPR _hoops_ISHP */
					break;
				}

				/* _hoops_HPGGR _hoops_PPR _hoops_GSSHR _hoops_RH _hoops_PGCHR _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_ISHA.
				 *
				 * (_hoops_CR _hoops_RGR _hoops_HRGR _hoops_RH *_hoops_SRGIR* _hoops_ISHA _hoops_IIGR _hoops_RGR _hoops_SCPH, '_hoops_PIIA'
				 *	_hoops_ASSP'_hoops_RA _hoops_RRP _hoops_IS _hoops_SHH !'_hoops_GHGP.)
				 */
				if (edge->vertex1 == vertex) {
					edge->_hoops_AAHHR = _hoops_RGHHR;
					QUEUE_ONE (edge->_hoops_PAHHR, edge->vertex2, edge, _hoops_RCHHR, _hoops_CIPAR);
				}
				else {
					edge->_hoops_PAHHR = _hoops_RGHHR;
					QUEUE_ONE (edge->_hoops_AAHHR, edge->vertex1, edge, _hoops_RCHHR, _hoops_CIPAR);
				}

				if (edge->_hoops_CRHHR == _hoops_RCHHR)
					_hoops_RCHHR = edge->_hoops_IRHHR;
				else
					if ((_hoops_RCHHR = edge->_hoops_CRHHR) == null) break;
			}

			/* _hoops_AGGA, _hoops_PHHR _hoops_RH _hoops_RII _hoops_PPRRR _hoops_HII _hoops_RH _hoops_HSPP _hoops_ISHA. _hoops_GAGIR _hoops_GAR _hoops_ARRS, _hoops_AHSAR
			 * _hoops_SGS _hoops_RH _hoops_RAGIR _hoops_IIGR _hoops_RH _hoops_ASGA _hoops_CHR _hoops_AAGIR, _hoops_RH _hoops_PAGIR _hoops_CSSP
			 * _hoops_HRGR _hoops_AAGIR, _hoops_PPR - _hoops_GGR _hoops_HAGIR - _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IS _hoops_RGIC _hoops_AHCA _hoops_IAGIR
			 * _hoops_ISSC _hoops_IS _hoops_RH _hoops_HSPP _hoops_ISHA.
			 */

			edge = _hoops_PPGHR;
			if ((_hoops_RCHHR = _hoops_IISHR) != null) _hoops_PCCAR {
				_hoops_ARPA						*_hoops_HRAHR;

				_hoops_HRAHR = &_hoops_SPHPR->local_face_attributes.normals[_hoops_RCHHR->face];

				/* _hoops_SSS _hoops_RH _hoops_RII _hoops_ISHA _hoops_IIGR _hoops_RGR _hoops_SCPH _hoops_PGAP _hoops_PRCHR _hoops_RGR _hoops_GPHA */

				if (edge == _hoops_RCHHR->_hoops_HAHHR) {
					edge = _hoops_RCHHR->_hoops_IAHHR;
					if (edge->vertex1 == vertex || edge->vertex2 == vertex) {
						_hoops_PCHR = !false;
					}
					else {
						if (_hoops_RCHHR->_hoops_SAHHR != null)
							edge = _hoops_RCHHR->_hoops_SAHHR;
						else
							edge = _hoops_RCHHR->_hoops_CAHHR;
						_hoops_PCHR = false;
					}
				}
				else if (edge == _hoops_RCHHR->_hoops_IAHHR) {
					edge = _hoops_RCHHR->_hoops_CAHHR;
					if (edge->vertex1 == vertex || edge->vertex2 == vertex) {
						_hoops_PCHR = !false;
					}
					else {
						edge = _hoops_RCHHR->_hoops_HAHHR;
						_hoops_PCHR = false;
					}
				}
				else if (edge == _hoops_RCHHR->_hoops_CAHHR) {
					if (_hoops_RCHHR->_hoops_SAHHR != null)
						edge = _hoops_RCHHR->_hoops_SAHHR;
					else
						edge = _hoops_RCHHR->_hoops_HAHHR;
					if (edge->vertex1 == vertex || edge->vertex2 == vertex) {
						_hoops_PCHR = !false;
					}
					else {
						edge = _hoops_RCHHR->_hoops_IAHHR;
						_hoops_PCHR = false;
					}
				}
				else {
					edge = _hoops_RCHHR->_hoops_HAHHR;
					if (edge->vertex1 == vertex || edge->vertex2 == vertex) {
						_hoops_PCHR = !false;
					}
					else {
						edge = _hoops_RCHHR->_hoops_CAHHR;
						_hoops_PCHR = false;
					}
				}

				if (_hoops_PCHR == _hoops_CIPAR) {
					_hoops_ARAHR.x += _hoops_HRAHR->a;
					_hoops_ARAHR.y += _hoops_HRAHR->b;
					_hoops_ARAHR.z += _hoops_HRAHR->c;
				}
				else {
					_hoops_ARAHR.x -= _hoops_HRAHR->a;
					_hoops_ARAHR.y -= _hoops_HRAHR->b;
					_hoops_ARAHR.z -= _hoops_HRAHR->c;
				}

				/* _hoops_HPGGR _hoops_PPR _hoops_GSSHR _hoops_RH _hoops_PGCHR _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_ISHA. */
				if (edge->vertex1 == vertex) {
					edge->_hoops_AAHHR = _hoops_RGHHR;
					QUEUE_ONE (edge->_hoops_PAHHR, edge->vertex2, edge, _hoops_RCHHR, !_hoops_CIPAR);
				}
				else {
					edge->_hoops_PAHHR = _hoops_RGHHR;
					QUEUE_ONE (edge->_hoops_AAHHR, edge->vertex1, edge, _hoops_RCHHR, !_hoops_CIPAR);
				}

				if (edge->_hoops_CRHHR == _hoops_RCHHR)
					_hoops_RCHHR = edge->_hoops_IRHHR;
				else
					if ((_hoops_RCHHR = edge->_hoops_CRHHR) == null) break;
			}

			if (!BIT (_hoops_SPHPR->local_vertex_attributes.flags[vertex],
					  LVA_EXPLICIT_NORMAL)) {
				(void)HI_Normalize (&_hoops_ARAHR);
				_hoops_SPHPR->local_vertex_attributes.normals[vertex].x = _hoops_ARAHR.x;
				_hoops_SPHPR->local_vertex_attributes.normals[vertex].y = _hoops_ARAHR.y;
				_hoops_SPHPR->local_vertex_attributes.normals[vertex].z = _hoops_ARAHR.z;
			}

		  _hoops_RRGIR:;

			if ((_hoops_PCSHR = _hoops_RCSHR) == null) break;

			if ((_hoops_RCSHR = _hoops_PCSHR->next) == null) _hoops_ACSHR = &_hoops_RCSHR;

			_hoops_PPGHR = _hoops_PCSHR->_hoops_PPGHR;
			_hoops_IISHR = _hoops_PCSHR->_hoops_IISHR;
			_hoops_CIPAR = _hoops_PCSHR->_hoops_CIPAR;
			vertex = _hoops_PCSHR->vertex;

			FREE (_hoops_PCSHR, _hoops_CISHR);
		}
	}
} /* _hoops_RSGR _hoops_API _hoops_CAGIR */


GLOBAL_FUNCTION void HI_Assemble_Shell_Vertex_Normals (
	Shell *						_hoops_SPHPR) {
	Local_Face_Attributes *		_hoops_CPRI = &_hoops_SPHPR->local_face_attributes;
	Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_SPHPR->local_vertex_attributes;
	int							vertex, face = -1, _hoops_SAGIR, i;
	int							*face_list, *_hoops_GPGIR;	  
	_hoops_ARPA *						_hoops_HRAHR;
	_hoops_ARPA *						_hoops_RPGIR;
	const int					_hoops_APGIR = _hoops_SPHPR->point_count;

	_hoops_SPHPR->polyhedron_flags |= PHF_VERTEX_NORMALS_VALID;

	if (_hoops_SPRI->explicit_normal_count == _hoops_APGIR)
		return; //_hoops_ISAP _hoops_IS _hoops_AA -- _hoops_HCR _hoops_HHHA

	bool						_hoops_PPGIR = (_hoops_SPRI->explicit_normal_count == 0);

	if (_hoops_SPRI->normals == null)
		HI_Initialize_Vertex_Attributes ((Polyhedron *)_hoops_SPHPR, LVA_EXPLICIT_NORMAL,0);
	
	_hoops_RPGIR = _hoops_CPRI->normals;
	if (!BIT (_hoops_SPHPR->polyhedron_flags, PHF_FACE_NORMALS_VALID))
		HI_Assemble_Face_Normals ((Polyhedron *)_hoops_SPHPR);

	/* _hoops_IH _hoops_GRR _hoops_GPHA
	 *	 _hoops_HSPC _hoops_RH _hoops_GPHA _hoops_GSSR _hoops_IS 0
	 * _hoops_IH _hoops_GRR _hoops_HSP
	 *	 _hoops_GGCR _hoops_RH _hoops_HSP _hoops_GSSR _hoops_IS _hoops_RH _hoops_GPHA _hoops_GSSR
	 * _hoops_IH _hoops_GRR _hoops_GPHA
	 *	 _hoops_HPGIR _hoops_RH _hoops_GPHA _hoops_GSSR
	 */
	for (vertex = 0; vertex < _hoops_APGIR; vertex++) {
		if (_hoops_PPGIR || !BIT (*_hoops_SPRI->_hoops_CHHPR(vertex), LVA_EXPLICIT_NORMAL))
			_hoops_SPRI->normals[vertex] = _hoops_IRGA::_hoops_CRGA;
	}

	if ((face_list = _hoops_SPHPR->face_list) == null) {
		Tristrip const *		ts;

		if ((ts = _hoops_SPHPR->tristrips) != null) do {
			int						_hoops_PHHA = ts->_hoops_PHHA;
			int const *				lengths = ts->lengths;
			int const *				vi = ts->_hoops_AIHA;
			int const *				fi = ts->face_indices;

			while (_hoops_PHHA-- > 0) {
				bool		_hoops_SICPR = false;
				int				length = *lengths++;
				int				p1 = *vi++;
				int				p2 = *vi++;
				int				_hoops_IAPH;

				if (length < 0) {
					length = -length;
					_hoops_SICPR = true;
				}
				length -= 2;

				if (fi) fi += 2;

				while (length-- > 0) {
					_hoops_IAPH = *vi++;
					if (fi)
						face = *fi++;
					else
						face++;

					_hoops_HRAHR = &_hoops_CPRI->normals[face];

					if (_hoops_PPGIR || !BIT (*_hoops_SPRI->_hoops_CHHPR(p1), LVA_EXPLICIT_NORMAL))
						_hoops_SPRI->normals[p1] += *_hoops_HRAHR;
					if (_hoops_PPGIR || !BIT (*_hoops_SPRI->_hoops_CHHPR(p2), LVA_EXPLICIT_NORMAL))
						_hoops_SPRI->normals[p2] += *_hoops_HRAHR;
					if (_hoops_PPGIR || !BIT (*_hoops_SPRI->_hoops_CHHPR(_hoops_IAPH), LVA_EXPLICIT_NORMAL))
						_hoops_SPRI->normals[_hoops_IAPH] += *_hoops_HRAHR;

					if (!_hoops_SICPR)
						p1 = p2;
					p2 = _hoops_IAPH;
				}
			}
		} while ((ts = ts->next) != null);
	}
	else {
		_hoops_GPGIR = face_list + _hoops_SPHPR->face_list_length;

		face = 0;
		while (face_list < _hoops_GPGIR) {
			_hoops_SAGIR = *face_list;

			if (_hoops_SAGIR < 0) {
				_hoops_SAGIR = -_hoops_SAGIR;
				_hoops_HRAHR = &_hoops_CPRI->normals[face - 1];
			}
			else {
				_hoops_HRAHR = &_hoops_CPRI->normals[face];
			}

			/* _hoops_GGR _hoops_RH _hoops_AGIR _hoops_IIGR _hoops_HHHR _hoops_RSSI, _hoops_RGR _hoops_HAPR _hoops_PPPPR'_hoops_RA _hoops_SSSS */
			for (i = 1; i <= _hoops_SAGIR; i++) {
				vertex = *(face_list + i);
				if (_hoops_PPGIR || !BIT (*_hoops_SPRI->_hoops_CHHPR(vertex), LVA_EXPLICIT_NORMAL))
					_hoops_SPRI->normals[vertex] += *_hoops_HRAHR;
			}

			if (*face_list >= 0)
				face++;

			face_list += _hoops_SAGIR + 1;
		}
	}

	if (_hoops_PPGIR) {
		HI_Normalize_Vectors (_hoops_APGIR, _hoops_SPRI->normals);
	}
	else {
		for (vertex = 0; vertex < _hoops_APGIR; vertex++) {
			if (!BIT (*_hoops_SPRI->_hoops_CHHPR(vertex), LVA_EXPLICIT_NORMAL)) {
				HI_Normalize (&_hoops_SPRI->normals[vertex]);
			}
		}
	}

	/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_IRCC _hoops_GAR _hoops_ACIPR _hoops_GAR _hoops_SR _hoops_PAH _hoops_IS _hoops_ASAC _hoops_PPGS, _hoops_PPR _hoops_RH _hoops_RGAR _hoops_SCPC _hoops_SR _hoops_RIAGR
	 * _hoops_HSP _hoops_ASGA _hoops_IS _hoops_RPGH _hoops_CCA _hoops_CSAP _hoops_IS _hoops_CAHP _hoops_AGCR _hoops_GPHA _hoops_ASGA, _hoops_IPGIR _hoops_CIH _hoops_GH _hoops_RH _hoops_PPGS. */ 
	if (_hoops_RPGIR == null ) {
		FREE_ARRAY_ALIGNED (_hoops_CPRI->normals, _hoops_SPHPR->face_count, _hoops_ARPA, 16);
		_hoops_CPRI->normals = null;
		_hoops_SPHPR->polyhedron_flags &= ~PHF_FACE_NORMALS_VALID;
	}
}






local void _hoops_CPGIR (
	int						in_point_count,
	Point const *			in_points,
 	int						in_face_list_length,
	int		 const *		in_face_list,
 	int alter *				mapping) {

	Point min,max, delta, _hoops_SPGIR;
 	int i;
	int _hoops_GHGIR;

	i = 0;
 	
	min = in_points[in_face_list[1]];
	max = in_points[in_face_list[1]];
	while (1) {
		int j;
		int _hoops_RHGIR;
		if (i>=in_face_list_length)
			break;
		_hoops_RHGIR = Abs(in_face_list[i]);
		i++;

  		for (j=0; j<_hoops_RHGIR; j++) {
			if (min.x > in_points[in_face_list[i+j]].x)
				min.x = in_points[in_face_list[i+j]].x;
			if (min.y > in_points[in_face_list[i+j]].y)
				min.y = in_points[in_face_list[i+j]].y;
			if (min.z > in_points[in_face_list[i+j]].z)
				min.z = in_points[in_face_list[i+j]].z;
			if (max.x < in_points[in_face_list[i+j]].x)
				max.x = in_points[in_face_list[i+j]].x;
			if (max.y < in_points[in_face_list[i+j]].y)
				max.y = in_points[in_face_list[i+j]].y;
			if (max.z < in_points[in_face_list[i+j]].z)
				max.z = in_points[in_face_list[i+j]].z;
		}
  		i += _hoops_RHGIR;
	

	}

	delta.x = max.x - min.x;
	delta.y = max.y - min.y;
	delta.z = max.z - min.z;
	_hoops_SPGIR.x = (max.x + min.x)/2.0f;
	_hoops_SPGIR.y = (max.y + min.y) / 2.0f;
	_hoops_SPGIR.z = (max.z + min.z) / 2.0f;
	if (delta.x >= delta.y && delta.x >= delta.z)
		_hoops_GHGIR = 0;
	else if (delta.y >= delta.x  && delta.y >= delta.z)
		_hoops_GHGIR = 1;
	else
		_hoops_GHGIR = 2;
	switch (_hoops_GHGIR) {
		case 0:
			for (i = 0;i<in_point_count;i++) {
 				if (in_points[i].x >= min.x && in_points[i].x <= _hoops_SPGIR.x)
					mapping[i] = 0;
				else
					mapping[i] = 1;
			}
			break;
		case 1:
			for (i = 0;i<in_point_count;i++) {
 				if (in_points[i].y >= min.y && in_points[i].y <= _hoops_SPGIR.y)
					mapping[i] = 0;
				else
					mapping[i] = 1;
			}
			break;
		case 2:
			for (i = 0;i<in_point_count;i++) {
 				if (in_points[i].z >= min.y && in_points[i].z <= _hoops_SPGIR.z)
					mapping[i] = 0;
				else
					mapping[i] = 1;
			}
			break;
	}
}
 

 

local void _hoops_AHGIR(int point_count, Point const *points, int face_list_length, int const *face_list,
						   int const *face_mapping, 
					  int *_hoops_PHGIR, int **_hoops_HHGIR, 
					  int *_hoops_IHGIR, int **_hoops_CHGIR,
					  int *_hoops_SHGIR,int **_hoops_GIGIR, 
					  int *_hoops_RIGIR, int **_hoops_AIGIR)
{

	int						*_hoops_PIGIR;
	int i;
	int _hoops_HIGIR = 0,_hoops_IIGIR = 0;
 	int	 *_hoops_CIGIR = 0;
	int *_hoops_SIGIR = 0;
 	int	 *_hoops_GCGIR = 0;
	int *_hoops_RCGIR = 0;
	int _hoops_ACGIR = 0,_hoops_PCGIR = 0, _hoops_HCGIR = 0;
 	ALLOC_ARRAY_CACHED(_hoops_PIGIR,point_count, int);
 	_hoops_CPGIR(point_count, points, face_list_length, face_list,_hoops_PIGIR);


 	i = 0;
	while (1) {
		int j;
		int _hoops_RHGIR;
		bool first = false;
		bool _hoops_ICGIR = false;
		
		if (i>=face_list_length)
			break;
		_hoops_RHGIR = face_list[i++];
		if (_hoops_RHGIR < 0) {
			_hoops_RHGIR = -_hoops_RHGIR;
			_hoops_ICGIR = true;
		}
		
		if (!_hoops_ICGIR) {
			for (j=0; j<_hoops_RHGIR; j++) {
				if (_hoops_PIGIR[face_list[i+j]] == 0) {
					first = true;
					break;
				}
			}
			if (first) {
				_hoops_ACGIR++;
 				_hoops_HIGIR+=(_hoops_RHGIR + 1);
			}
			else {
				_hoops_IIGIR+=(_hoops_RHGIR + 1);
				_hoops_PCGIR++;
			}
		}
		i+=_hoops_RHGIR;
			
	}

  
	if (_hoops_HIGIR)
		ALLOC_ARRAY_CACHED(_hoops_CIGIR,_hoops_HIGIR, int);
	if (_hoops_IIGIR)
		ALLOC_ARRAY_CACHED(_hoops_SIGIR,_hoops_IIGIR, int);
	if (_hoops_ACGIR)
		ALLOC_ARRAY_CACHED(_hoops_GCGIR,_hoops_ACGIR, int);
	if (_hoops_PCGIR)
		ALLOC_ARRAY_CACHED(_hoops_RCGIR,_hoops_PCGIR, int);

	i = 0;
	_hoops_HIGIR = 0;
	_hoops_IIGIR = 0;
	_hoops_ACGIR = 0;
	_hoops_PCGIR = 0;
	_hoops_HCGIR = 0;
	while (1) {
		int j;
		int _hoops_RHGIR;
		bool first = false;
		bool _hoops_ICGIR = false;
		
		if (i>=face_list_length)
			break;
		_hoops_RHGIR = face_list[i++];
		if (_hoops_RHGIR < 0) {
			_hoops_RHGIR = -_hoops_RHGIR;
			_hoops_ICGIR = true;
		}
		
		if (!_hoops_ICGIR) {
			for (j=0; j<_hoops_RHGIR; j++) {
				if (_hoops_PIGIR[face_list[i+j]] == 0) {
					first = true;
					break;
				}
			}
			if (first) {
				if (face_mapping)
					_hoops_GCGIR[_hoops_ACGIR++] = face_mapping[_hoops_HCGIR];
				else
					_hoops_GCGIR[_hoops_ACGIR++] = _hoops_HCGIR;
				_hoops_CIGIR[_hoops_HIGIR++] = face_list[i-1];
				for (j=0; j<_hoops_RHGIR; j++) {
					_hoops_CIGIR[_hoops_HIGIR+j] = face_list[i+j];
				}
				_hoops_HIGIR += _hoops_RHGIR;
			}
			else {
				if (face_mapping)
					_hoops_RCGIR[_hoops_PCGIR++] = face_mapping[_hoops_HCGIR];
				else
					_hoops_RCGIR[_hoops_PCGIR++] = _hoops_HCGIR;
				_hoops_SIGIR[_hoops_IIGIR++] = face_list[i-1];
				for (j=0; j<_hoops_RHGIR; j++) {
					_hoops_SIGIR[_hoops_IIGIR+j] = face_list[i+j];
				}
				_hoops_IIGIR += _hoops_RHGIR;
			}	
			_hoops_HCGIR++;
		}
		i += _hoops_RHGIR;
	
		
		
	}

	*_hoops_PHGIR = _hoops_HIGIR;
	*_hoops_SHGIR = _hoops_IIGIR;
	*_hoops_HHGIR = _hoops_CIGIR;
	*_hoops_GIGIR = _hoops_SIGIR;
	*_hoops_CHGIR = _hoops_GCGIR;
	*_hoops_AIGIR = _hoops_RCGIR;
	*_hoops_IHGIR = _hoops_ACGIR;
	*_hoops_RIGIR = _hoops_PCGIR;

	FREE_ARRAY(_hoops_PIGIR,point_count, int);
}


local void _hoops_CCGIR (
	int						point_count,
	Point const				*points,
	int						face_list_length,
	int const				*face_list,
	Shell					*_hoops_SPHPR,
	_hoops_SARHR	_hoops_HGSPR,
	bool					_hoops_PCRHR,
	Tristrip alter			**_hoops_SCGIR) 
{
	_hoops_CPHHR				info;
	_hoops_HRHHR				*_hoops_GRCPR;
	int const				*list;
	int const				*global_end;
	int						limit;
	_hoops_ARPA const				*_hoops_PRHH;
	int						*face_list1[_hoops_HGHHR];
	int						*_hoops_GSGIR[_hoops_HGHHR];
	int						_hoops_RSGIR[_hoops_HGHHR];
 	int						face_list_length1[_hoops_HGHHR];
	int						_hoops_HHAS;
	bool					_hoops_ASGIR = false;
	bool					_hoops_PSGIR = false;

	if (_hoops_PCRHR) {
		Local_Vertex_Attributes *	_hoops_SPRI;

		/*_hoops_AGHR (_hoops_RRCPR != _hoops_IRAP);*/
		_hoops_SPRI = &_hoops_SPHPR->local_vertex_attributes;
		if (_hoops_SPRI->explicit_normal_count == _hoops_SPHPR->point_count + _hoops_SPHPR->_hoops_GCRHR) {
			_hoops_SPHPR->polyhedron_flags |= PHF_VERTEX_NORMALS_VALID;
			_hoops_PCRHR = false;
		}
		if (_hoops_PCRHR && !_hoops_HGSPR) {
			if (!BIT (HOOPS_WORLD->system_flags, _hoops_RGRI)) {
				HI_Assemble_Shell_Vertex_Normals (_hoops_SPHPR);
				_hoops_PCRHR = false;
			}
		}
		if (!_hoops_PCRHR) 
			return;
	}

	face_list1[0] = (int *)face_list;
	face_list_length1[0] = face_list_length;
	_hoops_GSGIR[0] = 0;
	_hoops_HHAS = 0;

	for (int i=0; i<face_list_length; i+=face_list[i]+1) {
		if (face_list[i] < 0) {
			_hoops_PSGIR = true;
			break;
		}
	}
	do {
		if (face_list_length1[_hoops_HHAS]>_hoops_PGHHR && _hoops_HHAS<_hoops_HGHHR-2 && !_hoops_PSGIR)
		{
			_hoops_ASGIR = true;
			_hoops_AHGIR(point_count, points, face_list_length1[_hoops_HHAS], face_list1[_hoops_HHAS], _hoops_GSGIR[_hoops_HHAS],
				&face_list_length1[_hoops_HHAS+1], &face_list1[_hoops_HHAS+1], &_hoops_RSGIR[_hoops_HHAS+1],&_hoops_GSGIR[_hoops_HHAS+1],
				&face_list_length1[_hoops_HHAS+2], &face_list1[_hoops_HHAS+2], &_hoops_RSGIR[_hoops_HHAS+2],&_hoops_GSGIR[_hoops_HHAS+2]);

			if (_hoops_HHAS > 0 && face_list_length1[_hoops_HHAS])
			{
				FREE_ARRAY(face_list1[_hoops_HHAS], face_list_length1[_hoops_HHAS], int);
				FREE_ARRAY(_hoops_GSGIR[_hoops_HHAS], _hoops_RSGIR[_hoops_HHAS], int);
			}

			face_list_length1[_hoops_HHAS] = 0;
			if (face_list_length1[_hoops_HHAS+2] == 0)
			{
				_hoops_HHAS++;
				goto test;
			}
			else if (face_list_length1[_hoops_HHAS+1] == 0)
			{
				_hoops_HHAS+=2;
				goto test;
			}
			else 
				_hoops_HHAS+=2;
		}
		else {
test:
			if (face_list_length1[_hoops_HHAS]) {			
				ZERO_STRUCT (&info, _hoops_CPHHR);
				info._hoops_SPHPR = _hoops_SPHPR; //_hoops_PIP: _hoops_GHCA _hoops_SHH _hoops_IRAP.  _hoops_RGR _hoops_API _hoops_HRGR _hoops_IGI _hoops_IS _hoops_HSGIR _hoops_HCGR, _hoops_HAH
				{
					long  _hoops_ISGIR, _hoops_CSGIR;

					// _hoops_IPCP _hoops_SSSHR _hoops_PHI _hoops_IIGR _hoops_SPPR _hoops_HRGR _hoops_AHCA 3 _hoops_IACH _hoops_RH _hoops_PHI _hoops_IIGR _hoops_RSSA.
					_hoops_ISGIR = point_count * 3L;

					if (_hoops_ISGIR > 1<<16)		// _hoops_HIH _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_HPPR _hoops_IH _hoops_IRS "_hoops_RRHP" _hoops_SSGIR
						_hoops_CSGIR = 1<<16;
					else {
						/* _hoops_CHSC _hoops_GH _hoops_IS _hoops_RH _hoops_SPS _hoops_RIIR _hoops_IIGR 2. */
						_hoops_CSGIR = 16; /* _hoops_ASAC _hoops_IRS _hoops_CIAGR _hoops_RGHS _hoops_HPP _hoops_APHR _hoops_HPGR _hoops_IRS _hoops_GHAR _hoops_CGGPR. */
						while (_hoops_CSGIR < _hoops_ISGIR) _hoops_CSGIR *= 2;
					}
					info._hoops_RHHHR = _hoops_CSGIR;
					info._hoops_AHHHR = _hoops_CSGIR - 1;
				}

				ZALLOC_ARRAY_CACHED (info._hoops_SPHHR, info._hoops_RHHHR, _hoops_HRHHR *);

				/* _hoops_HSP _hoops_HHPH _hoops_GGR _hoops_RH _hoops_GGRIR _hoops_RAIA _hoops_ASGA */
				if (_hoops_SPHPR != null) {
					if (!BIT (_hoops_SPHPR->polyhedron_flags, PHF_FACE_NORMALS_VALID))
						HI_Assemble_Face_Normals ((Polyhedron *)_hoops_SPHPR);
					_hoops_PRHH = _hoops_SPHPR->local_face_attributes.normals;
				}
				else 
					_hoops_PRHH = null;

				/* _hoops_PPSI _hoops_RH _hoops_GSSP _hoops_GIRP */
				limit = _hoops_CSPHR;
				if (_hoops_PCRHR) {
					/* _hoops_PIHA _hoops_HS _hoops_HCR _hoops_RSSI _hoops_HPGR _hoops_ARR */
					limit = -1;		/* (--_hoops_SAIPR==0) _hoops_RPGP _hoops_CGH _hoops_IIP _hoops_RGRIR */
				}

				/* _hoops_IPHR _hoops_GC _hoops_IH _hoops_IRHP _hoops_CPCI: 2 _hoops_AGRIR _hoops_RIR _hoops_SCPH, _hoops_PGRIR < _hoops_HIGR _hoops_SPCC */
				info._hoops_GASPR = 2 * face_list_length1[_hoops_HHAS];
				/* _hoops_HGRIR: _hoops_GRR _hoops_RCCPR _hoops_IGRIR _hoops_PCCP _hoops_CGRIR _hoops_SCPH _hoops_ARRS _hoops_RH _hoops_IHGP _hoops_AHGC */
				list = face_list1[_hoops_HHAS];
				global_end = face_list1[_hoops_HHAS] + face_list_length1[_hoops_HHAS];
				while (list < global_end)
					if (*list++ < 0)
						info._hoops_GASPR += 2;
				// _hoops_PIIC _hoops_SGS'_hoops_GRI _hoops_HGGC _hoops_HAR _hoops_RAPR, _hoops_HIH _hoops_HRII _hoops_HSAR _hoops_IRHH _hoops_RH _hoops_SRHR _hoops_PRGI _hoops_SGRIR,
				// _hoops_SR _hoops_HA _hoops_CHR _hoops_CPIC _hoops_IS _hoops_SAIPR _hoops_RH _hoops_SRHR _hoops_IH _hoops_HCR _hoops_ARAR.
				// _hoops_RH _hoops_CCGI _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_GRRIR, _hoops_HIH _hoops_SAHR _hoops_RRP _hoops_RRRIR _hoops_RIRA _hoops_ARIPR, _hoops_PPR _hoops_SCH _hoops_HACAR
				// _hoops_SISPR _hoops_IS _hoops_CCPP _hoops_IRS _hoops_ARRIR _hoops_CRPR
				if (info._hoops_GASPR > 1<<20)
					info._hoops_GASPR = 1<<20;
					
				ALLOC_ARRAY_CACHED (info._hoops_SRSPR, info._hoops_GASPR, int);
				list = face_list1[_hoops_HHAS];
				info._hoops_SHHHR = 0;
				info._hoops_GIHHR = false;
				info._hoops_RIHHR = false;
				info._hoops_AIHHR = 
					(_hoops_SPHPR != null) && 
					(_hoops_SPHPR->local_face_attributes._hoops_IHAHR < _hoops_RRHHR);
				list = face_list1[_hoops_HHAS];
				_hoops_GRIHR (points, 
									face_list_length1[_hoops_HHAS], face_list1[_hoops_HHAS], _hoops_GSGIR[_hoops_HHAS], 
									_hoops_PRHH, 
									&list, limit, &info);
				
				/* _hoops_GAAP _hoops_ISPR _hoops_IH _hoops_PRRIR _hoops_RSSP _hoops_GGR _hoops_GGRIR */
				if (_hoops_SPHPR != null && info._hoops_GIHHR) {
#ifndef DISABLE_ERROR_WARNING_INFO
					if (_hoops_SPHPR->owner != null &&
						_hoops_SPHPR->owner->type == _hoops_IRCP)
						_hoops_GICHR (_hoops_SPHPR, &info);
#endif
#ifndef DISABLE_NON_MANIFOLD_OPTIMIZATION
					if (info._hoops_RIHHR &&
						!BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_HRRIR))
						_hoops_HICHR (_hoops_SPHPR, &info);
#endif
				}
				
				_hoops_GRCPR = _hoops_RHIHR (&info);
				
				if (_hoops_PCRHR && 
					BIT (HOOPS_WORLD->system_flags, _hoops_RGRI)) {
					/* _hoops_RPP _hoops_SR _hoops_HGGC _hoops_RRP _hoops_ASGA, _hoops_PIHA _hoops_HHGC _hoops_RH _hoops_IRRIR _hoops_SRSGR */
					_hoops_SISHR (_hoops_SPHPR, _hoops_GRCPR);
				}
				
				if (_hoops_GRCPR != null) {
					_hoops_PGSHR (_hoops_SPHPR, _hoops_GRCPR, &info);
					/* _hoops_PIP: _hoops_SCH _hoops_HGGPR _hoops_RH _hoops_SPPR */
					_hoops_GRCPR = null;
				}

				if (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI)) {
					_hoops_PCRHR = false;
				}
				
				/* _hoops_CASI _hoops_GH _hoops_GII _hoops_CRRIR _hoops_CIPH _hoops_PPR _hoops_RH _hoops_SCAH */
				FREE_ARRAY (info._hoops_SPHHR, info._hoops_RHHHR, _hoops_HRHHR *);
				info._hoops_SPHHR = null;

				/* _hoops_HA _hoops_ICIC _hoops_IS _hoops_CASI _hoops_GH _hoops_RH _hoops_GC _hoops_IGI _hoops_HPP _hoops_RH _hoops_PGGHR _hoops_IH _hoops_HIGR _hoops_CASPR */
				FREE_ARRAY (info._hoops_SRSPR, info._hoops_GASPR, int);

				/* _hoops_HA _hoops_IRHH _hoops_RH _hoops_HPHR _hoops_IIRGR */
				if (info.temps != null)
					_hoops_PRIPR (_hoops_SCGIR, info.temps);


				if (_hoops_SPHPR != null &&
					_hoops_HGSPR && 
					face_list_length != 0 &&
					BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_SRRIR) &&
					_hoops_SPHPR->_hoops_IHHPR.flags == null) {
					if (!BIT (_hoops_SPHPR->polyhedron_flags, PHF_SHELL_FACE_LIST_BY_REFERENCE) && 
						_hoops_SPHPR->face_list_length > 0)
						FREE_ARRAY (_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int);

					_hoops_SPHPR->face_list = null;
					_hoops_SPHPR->face_list_length = 0;

					/* _hoops_AGCR _hoops_GACC _hoops_GARIR _hoops_GPP _hoops_RH _hoops_GIGR _hoops_HSP _hoops_PAIGR,
					** _hoops_HIS _hoops_CHR _hoops_PSP _hoops_RPIP _hoops_APIP */

					if (_hoops_SPHPR->_hoops_GRCPR != null) {
						FREE_ARRAY (_hoops_SPHPR->_hoops_GRCPR, _hoops_SPHPR->_hoops_SPHA, _hoops_RHHPR);
						_hoops_SPHPR->_hoops_GRCPR = null;
					}

					if (_hoops_SPHPR->_hoops_HHHPR != null) {
						FREE_ARRAY (_hoops_SPHPR->_hoops_HHHPR, _hoops_SPHPR->point_count + 1, _hoops_RHHPR const *);
						_hoops_SPHPR->_hoops_HHHPR = null;
					}

					if (_hoops_SPHPR->_hoops_SGCPR != null) {
						FREE_ARRAY (_hoops_SPHPR->_hoops_SGCPR, _hoops_SPHPR->_hoops_SPHA, _hoops_CGCPR);
						_hoops_SPHPR->_hoops_SGCPR = null;
					}
				}

				if (_hoops_HHAS > 0) {
					FREE_ARRAY(face_list1[_hoops_HHAS], face_list_length1[_hoops_HHAS], int);
					FREE_ARRAY(_hoops_GSGIR[_hoops_HHAS], _hoops_RSGIR[_hoops_HHAS], int);
				}

			}
			_hoops_HHAS--;
		}
	} while (_hoops_HHAS>=0);

	if (_hoops_ASGIR && _hoops_SPHPR->tristrips) {
		HI_Resort_Tristrips ((Polyhedron alter *)_hoops_SPHPR, -1);
	}
	if (_hoops_PCRHR) {
		HI_Assemble_Shell_Vertex_Normals (_hoops_SPHPR);
	}
}



GLOBAL_FUNCTION void HI_Assemble_Simple_Shell_Tristrips (
	int						point_count,
	Point const				*points,
	int						face_list_length,
	int const				*face_list,
	Tristrip alter			**_hoops_SCGIR) {

	_hoops_CCGIR (point_count, points,
									 face_list_length, face_list,
									 null,
									 (_hoops_SARHR)~0, false,	/* _hoops_RARIR _hoops_HCR, _hoops_PSP _hoops_ASGA */
									 _hoops_SCGIR);
}

GLOBAL_FUNCTION void HI_Assemble_Shell_Tristrips (
	Shell					*_hoops_SPHPR,
	_hoops_SARHR	_hoops_HGSPR,
	bool					_hoops_PCRHR) {

	_hoops_CCGIR (_hoops_SPHPR->point_count, _hoops_SPHPR->points,
									 _hoops_SPHPR->face_list_length, _hoops_SPHPR->face_list,
									 _hoops_SPHPR,
									 _hoops_HGSPR, _hoops_PCRHR,
									 &_hoops_SPHPR->tristrips);
}


