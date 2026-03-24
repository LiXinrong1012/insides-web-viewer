/*
 * Copyright (c) 2006 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.565.2.2 2011-01-24 20:07:14 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "patterns.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"


#define	_hoops_SIIHC

/* _hoops_SIGP: _hoops_RHAR
	_hoops_GCIHC (_hoops_HASC)
	_hoops_AACC _hoops_CPAP, _hoops_IRGH _hoops_HPPA _hoops_GHC, _hoops_SGHS
	_hoops_IGRI _hoops_CRGIR _hoops_GPP _hoops_SIRAR _hoops_AAP
*/

#define	_hoops_RCIHC			128
#define	_hoops_ACIHC			512
#define _hoops_PCIHC				1024*32
#define _hoops_HCIHC	1024*32
#define _hoops_ICIHC		256
#define _hoops_CCIHC			1024
#define _hoops_SCIHC				3333


#define _hoops_GSIHC 0.25f


#define	_hoops_RSIHC			0x00000001
#define	_hoops_ASIHC			0x00000002
#define	_hoops_PSIHC					0x00000004
#define	_hoops_HSIHC		0x00000008
#define	_hoops_ISIHC				0x00000010
#define	_hoops_CSIHC			0x00000020
#define	_hoops_SSIHC			0x00000040
#define	_hoops_GGCHC			0x00000080
#define	_hoops_RGCHC			0x00000100
#define _hoops_AGCHC			0x00000200
#define _hoops_PGCHC	0x00000400
#define	_hoops_HGCHC			0x00000800
#define	_hoops_IGCHC			0x00001000
#define _hoops_CGCHC			0x00002000
#define _hoops_SGCHC				0x00004000
#define _hoops_GRCHC			0x00008000
#define	_hoops_RRCHC			0x00010000
#define	_hoops_ARCHC						0x00020000


// _hoops_SGCRP _hoops_SGI
#define _hoops_PRCHC				0x10000000
#define _hoops_HRCHC				0x20000000
#define	_hoops_IRCHC		0x40000000


/* _hoops_HHASH _hoops_HII _hoops_GII _hoops_CRCHC _hoops_CSSC */
#define	_hoops_SRCHC				 0		/* 0 _hoops_IHRI _hoops_GAR _hoops_SR _hoops_CGH _hoops_IIP _hoops_SGH _hoops_AIHHH _hoops_IS _hoops_GACHC */
#define	_hoops_RACHC			-1
#define	_hoops_AACHC			-2


/* _hoops_CAGH _hoops_SGGR _hoops_HII _hoops_GII _hoops_HCAGR _hoops_IGI _hoops_SIH */
#define	_hoops_PACHC						_hoops_HCIGP(4)
#define	_hoops_HACHC				_hoops_HCIGP(5)
#define	_hoops_IACHC					_hoops_HCIGP(6)
#define	_hoops_CACHC					_hoops_HCIGP(7)
#define	_hoops_SACHC				_hoops_HCIGP(8)

/* _hoops_GCIS */
#define	_hoops_GPCHC		_hoops_HCIGP(3)





typedef VHash<_hoops_CRCP const *, int> _hoops_CSGHP;
typedef VHash<_hoops_CRCP const *, float> _hoops_RPCHC;
typedef VHash<Subsegment const *, int> _hoops_APCHC;
typedef VHash<Geometry const *, int> _hoops_PPCHC;
typedef VHash<_hoops_PGRPR *, int> _hoops_HPCHC;
typedef VHash<_hoops_PGRPR *, float> _hoops_IPCHC;

/* _hoops_HHASH _hoops_HII _hoops_GII _hoops_IGRI _hoops_GPRR */
#define	_hoops_CPCHC				_hoops_GHAGP

struct _hoops_SPCHC {
	Key			_hoops_GHCHC;
	Key			_hoops_CISAP;

	int			_hoops_RHCHC;
};

struct _hoops_AHCHC : public Attribute {
	int			_hoops_PHCHC;
	_hoops_SPCHC *	_hoops_GPICA;
};


// _hoops_RAS _hoops_SR _hoops_RGHH _hoops_CHAPA _hoops_SR _hoops_HCAGR _hoops_HHGC _hoops_IS _hoops_CACH _hoops_RPP _hoops_RH _hoops_HHRPA _hoops_CAGH _hoops_PAH _hoops_SHH _hoops_RSRAR.
// _hoops_HGRRA, _hoops_RIRP-_hoops_PAGIR _hoops_HHCHC _hoops_RH _hoops_PIAP _hoops_IIGR _hoops_RH _hoops_SCGR _hoops_CAGH, _hoops_HIS _hoops_GRHP _hoops_IHGC _hoops_IH _hoops_HHHA _hoops_IHCHC
struct _hoops_CHCHC {
	_hoops_CHCHC *	next;
	_hoops_CRCP const *		segment;
	_hoops_CRCP *			node;
	int					_hoops_PIHRC;
};


class _hoops_SHCHC : public CMO_Pooled {
public:
	_hoops_CRCP *				s;
	float					t;
};


struct _hoops_GICHC {
	int					_hoops_RICHC;
	Subsegment const *	_hoops_AICHC;
};

struct _hoops_PICHC;

struct _hoops_HICHC {
	_hoops_CRCP *			_hoops_SRCP;
	_hoops_PICHC *		_hoops_ASCIA;
	_hoops_GICHC		_hoops_IICHC;
};


#define _hoops_CICHC		3

#define _hoops_SICHC	(1<<(3*_hoops_CICHC))

#define _hoops_GCCHC	3

struct _hoops_PICHC {
	_hoops_HICHC *	_hoops_HGASH[_hoops_SICHC];
	Point					_hoops_RCCHC[_hoops_CICHC+1];
	_hoops_SASC			cuboid;
};

class _hoops_ACCHC : public CMO_Pooled {
public:
	_hoops_PICHC *		_hoops_ASCIA;
	_hoops_GICHC		_hoops_IICHC;
};

typedef VHash<_hoops_CRCP const *, _hoops_ACCHC *> _hoops_PCCHC;
typedef VList<_hoops_SHCHC *> _hoops_HCCHC;

struct _hoops_ICCHC {
	_hoops_AIGPR *	_hoops_RIGC;
	Memory_Pool *			memory_pool;

	_hoops_PCCHC *		_hoops_CCCHC;

	_hoops_AAPHP *		_hoops_GGRHH;

	int		flags;

	int		id;

	// _hoops_IPSP _hoops_CHIA _hoops_SCCHC _hoops_CPCP, _hoops_RPP _hoops_GII
	int		_hoops_GSCHC[64];
	int		_hoops_RSCHC;

	int		_hoops_ASCHC;
	int		_hoops_PSCHC;
	int		_hoops_HSCHC;

	int		_hoops_ISCHC;
	int		_hoops_CSCHC;

	int		_hoops_SSCHC;
	int		_hoops_GGSHC;

	char	_hoops_RGSHC[4096];
};

typedef struct _hoops_AGSHC {
	struct _hoops_AGSHC *		next;
	Attribute const *			_hoops_ASGPR;
}	_hoops_PGSHC;


local const _hoops_IGRCR _hoops_HGSHC[] = {
	{_hoops_SRCHC,		_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},

	{_hoops_RACHC,	_hoops_GRRCR ("spatial"),		_hoops_RRRCR, 0, false},

	{HK_COLOR,				_hoops_GRRCR ("color"),				_hoops_RRRCR, 0, false},
	{HK_RENDERING_OPTIONS,	_hoops_GRRCR ("rendering option"),	_hoops_RRRCR, 0, false},
	{HK_MODELLING_MATRIX,	_hoops_GRRCR ("modelling matrix"),	_hoops_RRRCR, 0, false},
	{HK_SELECTABILITY,		_hoops_GRRCR ("selectability"),		_hoops_RRRCR, 0, false},
	{HK_VISIBILITY,			_hoops_GRRCR ("visibility"),		_hoops_RRRCR, 0, false},
	{HK_HEURISTICS,			_hoops_GRRCR ("heuristic"),			_hoops_RRRCR, 0, false},
	{HK_USER_OPTIONS,		_hoops_GRRCR ("user option"),		_hoops_RRRCR, 0, false},

	{HK_COLOR,				_hoops_GRRCR ("colors"),			_hoops_RRRCR, 0, false},
	{HK_RENDERING_OPTIONS,	_hoops_GRRCR ("rendering options"),	_hoops_RRRCR, 0, false},
	{HK_MODELLING_MATRIX,	_hoops_GRRCR ("modelling matrices"),_hoops_RRRCR, 0, false},
	{HK_SELECTABILITY,		_hoops_GRRCR ("selectabilities"),	_hoops_RRRCR, 0, false},
	{HK_VISIBILITY,			_hoops_GRRCR ("visibilities"),		_hoops_RRRCR, 0, false},
	{HK_HEURISTICS,			_hoops_GRRCR ("heuristics"),		_hoops_RRRCR, 0, false},
	{HK_USER_OPTIONS,		_hoops_GRRCR ("user options"),		_hoops_RRRCR, 0, false},

#if 0
	{HK_EDGE_PATTERN,		_hoops_GRRCR ("edge pattern"),		_hoops_RRRCR, 0, false},
	{HK_EDGE_WEIGHT,		_hoops_GRRCR ("edge weight"),		_hoops_RRRCR, 0, false},
	{HK_FACE_PATTERN,		_hoops_GRRCR ("face pattern"),		_hoops_RRRCR, 0, false},
	{HK_LINE_PATTERN,		_hoops_GRRCR ("line pattern"),		_hoops_RRRCR, 0, false},
	{HK_LINE_WEIGHT,		_hoops_GRRCR ("line weight"),		_hoops_RRRCR, 0, false},
	{HK_MARKER_SIZE,		_hoops_GRRCR ("marker size"),		_hoops_RRRCR, 0, false},
	{HK_MARKER_SYMBOL,		_hoops_GRRCR ("marker symbol"),		_hoops_RRRCR, 0, false},
	{HK_TEXT_ALIGNMENT,		_hoops_GRRCR ("text alignment"),	_hoops_RRRCR, 0, false},
	{HK_TEXT_FONT,			_hoops_GRRCR ("text font"),			_hoops_RRRCR, 0, false},
	{HK_TEXT_PATH,			_hoops_GRRCR ("text path"),			_hoops_RRRCR, 0, false},
	{HK_TEXT_SPACING,		_hoops_GRRCR ("text spacing"),		_hoops_RRRCR, 0, false},
	{HK_USER_VALUE,			_hoops_GRRCR ("user value"),		_hoops_RRRCR, 0, false},
	{HK_TEXTURE_MATRIX,		_hoops_GRRCR ("texture matrix"),	_hoops_RRRCR, 0, false},

	{HK_CAMERA,				_hoops_GRRCR ("camera"),			_hoops_RRRCR, 0, false},
	{HK_HANDEDNESS,			_hoops_GRRCR ("handedness"),		_hoops_RRRCR, 0, false},
	{HK_CLIP_REGION,		_hoops_GRRCR ("clip region"),		_hoops_RRRCR, 0, false},
#endif
};

local const _hoops_HPAGA _hoops_IGSHC = {
	_hoops_GGAPR (_hoops_HGSHC),	_hoops_HGSHC,
};

local const _hoops_IGRCR _hoops_CGSHC[] = {
	{0,									_hoops_GRRCR ("off"),						_hoops_RRRCR, 0, false},
	{0,									_hoops_GRRCR ("false"),						_hoops_RRRCR, 0, false},
	{0,									_hoops_GRRCR ("no"),						_hoops_RRRCR, 0, false},
	{_hoops_HGCHC,		_hoops_GRRCR ("on"),						_hoops_RRRCR, 0, false},
	{_hoops_HGCHC,		_hoops_GRRCR ("true"),						_hoops_RRRCR, 0, false},
	{_hoops_HGCHC,		_hoops_GRRCR ("yes"),						_hoops_RRRCR, 0, false},
	{_hoops_RRCHC,			_hoops_GRRCR ("merge"),						_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_SGSHC = {
	_hoops_GGAPR (_hoops_CGSHC),	_hoops_CGSHC,
};

local const _hoops_IGRCR _hoops_GRSHC[] = {
	{_hoops_RSIHC,			_hoops_GRRCR ("expand includes"),			_hoops_RRRCR, 0, true},
	{_hoops_RGCHC,			_hoops_GRRCR ("process includes"),			_hoops_RRRCR, 0, true},
	{_hoops_ASIHC,		_hoops_GRRCR ("collapse matrices"),			_hoops_RRRCR, 0, true},
	{_hoops_PSIHC,				_hoops_GRRCR ("reorganize"),				_hoops_GHAGA, -99, true,
																				&_hoops_IGSHC},
	{_hoops_ISIHC,				_hoops_GRRCR ("merge shells"),				_hoops_RRRCR, 0, true},
	{_hoops_AGCHC,			_hoops_GRRCR ("instance shells"),			_hoops_RRRCR, 0, true},
	{_hoops_PGCHC,	_hoops_GRRCR ("remove duplicate shells"),	_hoops_RRRCR, 0, true},
	{_hoops_CSIHC,			_hoops_GRRCR ("generate mapping"),			_hoops_RRRCR, 0, true},

	{_hoops_GGCHC,		_hoops_GRRCR ("discard user data"),			_hoops_RRRCR, 0, true},
	{_hoops_HGCHC,		_hoops_GRRCR ("preserve user data"),		_hoops_GHAGA, -1, true,
																				&_hoops_SGSHC},
	{_hoops_HGCHC,		_hoops_GRRCR ("preserve user options"),		_hoops_GHAGA, -1, true,
																				&_hoops_SGSHC},

	{_hoops_IGCHC,		_hoops_GRRCR ("discard invisible"),			_hoops_RRRCR, 0, true},

	{_hoops_GRCHC,		_hoops_GRRCR ("extract geometry attributes"),	_hoops_RRRCR, 0, true},
#if 0
	{_hoops_HSIHC,	_hoops_GRRCR ("unnecessary attributes"),	_hoops_RRRCR, 0, true},
#endif
};


#define	_hoops_RRSHC(_hoops_RSPGP, item)									\
			do if ((item)->key > _hoops_SHSSR) {					\
				HI_Delete_User_Key (_hoops_RSPGP, (_hoops_HPAH *)item);	\
				(item)->key = _hoops_AIRIR (item);			\
			} while (0)


local void _hoops_ARSHC (
	Geometry *			geometry) {
	_hoops_AHCHC *		id = (_hoops_AHCHC *)geometry->_hoops_IPPGR;

	if (id != null && id->type == _hoops_CPCHC)	/* _hoops_AIAH _hoops_GGHP _hoops_SPR */
		return;

	ZALLOC (id, _hoops_AHCHC);
	id->type = _hoops_CPCHC;
	id->owner = (_hoops_CRCP *)geometry;
	id->_hoops_HIHI = 1;
	if ((id->next = geometry->_hoops_IPPGR) != null)
		id->next->backlink = &id->next;
	geometry->_hoops_IPPGR = (Attribute *)id;
	id->backlink = &geometry->_hoops_IPPGR;
	ALLOC_ARRAY (id->_hoops_GPICA, 1, _hoops_SPCHC);
	id->_hoops_GPICA[0]._hoops_GHCHC = geometry->owner->key;
	id->_hoops_GPICA[0]._hoops_CISAP = geometry->key;
	id->_hoops_GPICA[0]._hoops_RHCHC = 0;
	id->_hoops_PHCHC = 1;
}

local void _hoops_RAGSA (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP const *		_hoops_SRCP,
	_hoops_CRCP *			_hoops_SRCII,
	_hoops_CRCP *			newowner) {

	/* _hoops_PSSP _hoops_GGCH _hoops_HGRH _hoops_GGR _hoops_PRSHC */
	if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR)) {
		if (_hoops_SRCP->_hoops_AAGSA() > 0) {
			if (_hoops_SRCII)
				HI_Less_Light (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCII, _hoops_SRCP->_hoops_AAGSA());
			HI_More_Light (_hoops_ARCAR->_hoops_RIGC, newowner, _hoops_SRCP->_hoops_AAGSA());
		}

		if (_hoops_SRCP->_hoops_PAGSA() > 0) {
			if (_hoops_SRCII)
				HI_Less_Cutting_Planes (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCII, _hoops_SRCP->_hoops_PAGSA());
			HI_More_Cutting_Planes (_hoops_ARCAR->_hoops_RIGC, newowner, _hoops_SRCP->_hoops_PAGSA());
		}

		if (_hoops_SRCP->_hoops_SHGSA() > 0) {
			if (_hoops_SRCII)
				HI_Less_Shadows (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCII, _hoops_SRCP->_hoops_SHGSA());
			HI_More_Shadows (_hoops_ARCAR->_hoops_RIGC, newowner, _hoops_SRCP->_hoops_SHGSA());
		}

		if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA)) {
			if (_hoops_SRCP->_hoops_IGCCA > 0) {
				if  (_hoops_SRCII)
					HI_Less_Transparencies (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCII, _hoops_SRCP->_hoops_IGCCA);
				HI_More_Transparencies (_hoops_ARCAR->_hoops_RIGC, newowner, _hoops_SRCP->_hoops_IGCCA);
			}
		}
	}
}


local int _hoops_HRSHC (
	Subsegment *		_hoops_IRSHC,
	Subsegment *		_hoops_CRSHC) {
	_hoops_CRCP const *		_hoops_SRSHC = _hoops_SSIGP (_hoops_IRSHC);
	_hoops_CRCP const *		_hoops_GASHC = _hoops_SSIGP (_hoops_CRSHC);

	if (BIT (_hoops_SRSHC->_hoops_RCGC, _hoops_AHASA) != BIT (_hoops_GASHC->_hoops_RCGC, _hoops_AHASA)) {
		if (BIT (_hoops_SRSHC->_hoops_RCGC, _hoops_AHASA))
			return -1;
		else
			return 1;
	}

	if (_hoops_IRSHC->priority != _hoops_CRSHC->priority) {
		if (_hoops_IRSHC->priority < _hoops_CRSHC->priority)
			return -1;
		else
			return 1;
	}

	if (_hoops_IRSHC->type != _hoops_CRSHC->type) {
		/* _hoops_RH _hoops_SPS _hoops_III _hoops_IGIPR _hoops_SGS _hoops_IHASA < _hoops_ISASA,
		   _hoops_PPR _hoops_SGS _hoops_SGS _hoops_HRGR _hoops_RH _hoops_AGR _hoops_SR _hoops_HHGC _hoops_IS _hoops_HS _hoops_RH _hoops_IIPR _hoops_SHH _hoops_GGR */
		if (_hoops_IRSHC->type < _hoops_CRSHC->type)
			return -1;
		else
			return 1;
	}

	if (_hoops_IRSHC->type == _hoops_IRCP) {
		_hoops_CRCP const *		_hoops_RASHC = (_hoops_CRCP const *)_hoops_IRSHC;
		_hoops_CRCP const *		_hoops_AASHC = (_hoops_CRCP const *)_hoops_CRSHC;

		if (_hoops_RASHC->name.length == 0) {
			if (_hoops_AASHC->name.length == 0)
				return 0;
			else
				return -1;
		}
		else if (_hoops_AASHC->name.length == 0)
			return 1;
		else
			return _hoops_GPASA (_hoops_RASHC->name.text, _hoops_AASHC->name.text);
	}

	return 0;
}


local char const * _hoops_PASHC (char alter * _hoops_RPPA) {
	char const *		string = _hoops_RPPA;

	while (*_hoops_RPPA != '\0') {
		if ('A' <= *_hoops_RPPA && *_hoops_RPPA <= 'Z')
			*_hoops_RPPA += 'a' - 'A';
		++_hoops_RPPA;
	}

	return string;
}


local _hoops_CRCP * _hoops_HASHC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				root,
	const char *			name = null,
	_hoops_RCCCA			_hoops_IASHC = 0,
	_hoops_RCCCA			_hoops_CASHC = 0,
	Subsegment **			_hoops_ASRGR = null)
{
	if (_hoops_ASRGR == null)
		_hoops_ASRGR = &root->_hoops_RGRPR;

	_hoops_CRCP	*	_hoops_SRCP = HI_Create_One_Segment (_hoops_ARCAR->_hoops_RIGC, null, _hoops_ASRGR, null, root, false);

	if (_hoops_ARCAR && BIT(_hoops_ARCAR->flags, _hoops_PRCHC))
		_hoops_SRCP->_hoops_RRHH |= _hoops_HIRIR;

	_hoops_SRCP->_hoops_RRHH |= _hoops_IASHC;
	_hoops_SRCP->_hoops_RRHH &= ~_hoops_CASHC;

	if (name == null)
		name = "";

	char	_hoops_SASHC[4096];
	_hoops_PASHC(_hoops_CAIGI(_hoops_ARCAR->_hoops_RIGC, _hoops_SASHC, "%s -- %d", name, _hoops_ARCAR->id++));
	HI_Copy_Chars_To_Name (_hoops_SASHC, &_hoops_SRCP->name);

#if 0
	if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 169")) {
		_hoops_SRCP=_hoops_SRCP;
	}
#endif

	return _hoops_SRCP;
}


#define _hoops_RCCAH(_hoops_AIPPA,_hoops_PIPPA) (_hoops_HRSHC(_hoops_AIPPA,_hoops_PIPPA)>0)
#define _hoops_ACCAH(_hoops_AIPPA,_hoops_PIPPA)	(_hoops_HRSHC(_hoops_AIPPA,_hoops_PIPPA)==0)
#define QS_TYPE					Subsegment **
#define QS_VAL(thing,a)			(thing[a]->priority)
#define QS_PIVOT_VAL(thing,a)	(thing[a])
#define QS_COMPLEX_COMPARE(thing,a,b) _hoops_RCCAH(thing[a],thing[b])
#define QS_SWAP(thing,a,b)		{Subsegment * tmp = thing[a]; thing[a] = thing[b]; thing[b] = tmp;}
#define QS_EQUAL(thing,a,b)		_hoops_ACCAH(thing[a],thing[b])
#include "utility/hqsort.h"

local void _hoops_GPSHC (
	_hoops_CRCP alter *		_hoops_SRCP,
	int					count) {
	Subsegment *		ptr;
	Subsegment **		_hoops_RPSHC;

	if (count < 2)
		return;

	ALLOC_ARRAY_CACHED (_hoops_RPSHC, count, Subsegment *);
	ptr = _hoops_SRCP->_hoops_RGRPR;
	for (int i = 0; i < count; i++) {
		_hoops_RPSHC[i] = ptr;
		ptr = ptr->next;
	}
	quick_sort(_hoops_RPSHC, 0, count-1);
	_hoops_SRCP->_hoops_RGRPR = _hoops_RPSHC[0];
	_hoops_RPSHC[0]->backlink = &_hoops_SRCP->_hoops_RGRPR;
	for (int i = 1; i < count; i++) {
		_hoops_RPSHC[i-1]->next = _hoops_RPSHC[i];
		_hoops_RPSHC[i]->backlink = &_hoops_RPSHC[i-1]->next;
	}
	_hoops_RPSHC[count-1]->next = null;
	FREE_ARRAY (_hoops_RPSHC, count, Subsegment *);
}


local _hoops_CRCP * _hoops_APSHC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_ISGI *		_hoops_PSACR) {
	_hoops_CRCP *				_hoops_PPSHC;
	_hoops_ISGI *		matrix;

	_hoops_PPSHC = _hoops_HASHC (_hoops_ARCAR, _hoops_SRCP, "capsule");

	if (_hoops_PSACR != null) {
		ZALLOC (matrix, _hoops_ISGI);
		matrix->type = HK_MODELLING_MATRIX;
		matrix->_hoops_HIHI = 1;
		HI_Copy_Matrix (&_hoops_PSACR->matrix, &matrix->matrix);

		_hoops_PPSHC->_hoops_IPPGR = (Attribute *)matrix;
		matrix->backlink = &_hoops_PPSHC->_hoops_IPPGR;
		matrix->owner = _hoops_PPSHC;

		if (BIT (matrix->matrix._hoops_RAGR, _hoops_RRICR))
			_hoops_PPSHC->_hoops_RRHH |= _hoops_RSPCR;
	}

	return _hoops_PPSHC;
}

local void _hoops_HPSHC (
	_hoops_ICCHC *		_hoops_ARCAR,
	Geometry const *		geometry,
	_hoops_CRCP *				_hoops_SRCP,
	int						_hoops_SSPCR,
	int						mask = ~0) {

	if (geometry->type == _hoops_ICIP) {
		if (BIT (mask, _hoops_AGPGR(_hoops_ICIP)))
			HI_More_Light (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCP, _hoops_SSPCR);
	}
	else if (geometry->type == _hoops_HGPGR) {
		if (BIT (mask, _hoops_AGPGR(_hoops_HGPGR)))
			HI_More_Cutting_Planes (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCP, _hoops_SSPCR);
	}
	else if (geometry->type == _hoops_AHIP) {
		_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)geometry;

		if (_hoops_RRA->_hoops_RGPGR &
			(_hoops_AGPGR(_hoops_ICIP)|_hoops_AGPGR(_hoops_HGPGR))) {

			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				if ((geometry = ((_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0])->geometry) != null) do {
					_hoops_HPSHC (_hoops_ARCAR, geometry, _hoops_SRCP, _hoops_SSPCR, _hoops_RRA->_hoops_RGPGR);
				} while ((geometry = geometry->next) != null);
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
					_hoops_HPSHC (_hoops_ARCAR, (Geometry const *)_hoops_RRA->_hoops_IHIP[i], _hoops_SRCP, _hoops_SSPCR, _hoops_RRA->_hoops_RGPGR);
				}
			}
		}
	}
}


local void _hoops_IPSHC (
	Geometry const *		geometry,
	_hoops_CRCP alter *			_hoops_SRCP) {

	switch (geometry->type) {
		case _hoops_AHIP: {
			_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)geometry;

			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP const *			_hoops_IGRPR = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

				if (ANYBIT (_hoops_RRA->_hoops_RGPGR, _hoops_AGPGR(_hoops_SCIP)|_hoops_AGPGR(_hoops_GSIP)|_hoops_AGPGR(_hoops_AHIP)) ||
					BIT (_hoops_IGRPR->_hoops_PHSI, _hoops_HHSI)) {
					_hoops_SRCP->_hoops_PHSI |= _hoops_HHSI;
					_hoops_SRCP->_hoops_RCGC |= _hoops_IGRPR->_hoops_RCGC & (_hoops_IRHGP|_hoops_ASPCR|_hoops_ASRRA);
				}
			}
			else {
				for (int i = 0; i < _hoops_RRA->_hoops_HHIP; i++) {
					_hoops_IPSHC ((Geometry const *)_hoops_RRA->_hoops_IHIP[i], _hoops_SRCP);
					if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_HHSI))
						break;
				}
			}
		}	break;

		case _hoops_SCIP:
		case _hoops_GSIP: {
			Polyhedron const *			phon = (Polyhedron const *)geometry;

			if (phon->local_face_attributes._hoops_CPIAA > 0 ||
				phon->_hoops_IHHPR._hoops_CPIAA > 0 ||
				phon->local_vertex_attributes._hoops_CPIAA > 0)
				_hoops_SRCP->_hoops_PHSI |= _hoops_HHSI;
		}	_hoops_HHHI;

		default: {
			_hoops_SRCP->_hoops_RCGC |= geometry->owner->_hoops_RCGC & (_hoops_IRHGP|_hoops_ASPCR|_hoops_ASRRA);
		}	break;
	}
}


local void _hoops_GRAPA (
	_hoops_ICCHC *		_hoops_ARCAR,
	Geometry alter *		geometry,
	_hoops_CRCP alter *			_hoops_SRCP,
	bool					_hoops_CPSHC) {

	if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
		_hoops_CRCP alter *			_hoops_RRAPA = geometry->owner;
		_hoops_CRCP alter *			_hoops_ARAPA = _hoops_SRCP->owner;

		if (BIT(_hoops_ARCAR->flags, _hoops_CSIHC))
			_hoops_ARSHC (geometry);

		_hoops_RRSHC (_hoops_ARCAR->_hoops_RIGC, geometry);

		_hoops_HPSHC (_hoops_ARCAR, geometry, _hoops_RRAPA, -1);
		if (_hoops_RRAPA->_hoops_GACP != null)
			HI_Table_Remove_Geometry (geometry);
		_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,geometry);

		if (_hoops_CPSHC)
			_hoops_SRCP->owner = (_hoops_CRCP *)HOOPS_WORLD;

		HI_Insert_Geometry (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, geometry, !BIT (geometry->_hoops_RRHH, _hoops_RSPCR), 0, false);

		_hoops_SRCP->owner = _hoops_ARAPA;
		_hoops_HPSHC (_hoops_ARCAR, geometry, _hoops_SRCP, 1);
	}
	else {
		_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,geometry);

		geometry->owner = _hoops_SRCP;

		if ((geometry->next = _hoops_SRCP->geometry) != null)
			geometry->next->backlink = &geometry->next;

		geometry->backlink = &_hoops_SRCP->geometry;
		_hoops_SRCP->geometry = geometry;
	}
	_hoops_IPSHC (geometry, _hoops_SRCP);
}

local void _hoops_SPSHC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_PHGSA,
	_hoops_CRCP *			_hoops_HHGSA) {
	UNREFERENCED(_hoops_ARCAR);
	ASSERT(BIT(_hoops_ARCAR->flags, _hoops_PRCHC));
	ASSERT(_hoops_PHGSA->geometry != null);

	Geometry *	g = _hoops_PHGSA->geometry;

	while (1) {
		g->owner = _hoops_HHGSA;
		if (g->next == null)
			break;
		g = g->next;
	}

	if (_hoops_HHGSA->geometry) {
		g->next = _hoops_HHGSA->geometry;
		g->next->backlink = &g->next;
	}

	g = _hoops_PHGSA->geometry;

	g->backlink = &_hoops_HHGSA->geometry;
	_hoops_HHGSA->geometry = g;
	_hoops_PHGSA->geometry = null;

	_hoops_HHGSA->_hoops_RCGC |= _hoops_PHGSA->_hoops_RCGC;
	if (BIT (_hoops_PHGSA->_hoops_PHSI, _hoops_HHSI))
		_hoops_HHGSA->_hoops_PHSI |= _hoops_HHSI;
}


local void _hoops_GHSHC (
	_hoops_ICCHC *		_hoops_ARCAR,
	Geometry alter *		geometry,
	_hoops_CRCP alter *			_hoops_SRCP,
	bool					_hoops_CPSHC) {

	if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
		_hoops_CRCP alter *			_hoops_ARAPA = _hoops_SRCP->owner;

		if (_hoops_CPSHC)
			_hoops_SRCP->owner = (_hoops_CRCP *)HOOPS_WORLD;

		HI_Insert_Geometry (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, geometry, !BIT (geometry->_hoops_RRHH, _hoops_RSPCR), 0, false);

		_hoops_SRCP->owner = _hoops_ARAPA;
		_hoops_HPSHC (_hoops_ARCAR, geometry, _hoops_SRCP, 1);
	}
	else {
		geometry->owner = _hoops_SRCP;

		if ((geometry->next = _hoops_SRCP->geometry) != null)
			geometry->next->backlink = &geometry->next;

		geometry->backlink = &_hoops_SRCP->geometry;
		_hoops_SRCP->geometry = geometry;
	}
	_hoops_IPSHC (geometry, _hoops_SRCP);
}

local _hoops_CRCP * _hoops_RHSHC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_PPSHC,
	_hoops_HPAH *				thing,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_ISGI *		_hoops_PSACR) {

	if (_hoops_PPSHC == null)
		_hoops_PPSHC = _hoops_APSHC (_hoops_ARCAR, _hoops_SRCP, _hoops_PSACR);

	if (thing->type >= _hoops_AHRIR && thing->type <= _hoops_PHRIR)
		_hoops_GRAPA (_hoops_ARCAR, (Geometry *)thing, _hoops_PPSHC, true);
	else {
		Subsegment *		_hoops_GIPIA = (Subsegment *)thing;
		_hoops_CRCP *			_hoops_PPIPP = _hoops_SSIGP (_hoops_GIPIA);


		if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC))
			_hoops_RRSHC (_hoops_ARCAR->_hoops_RIGC, _hoops_GIPIA);
		_hoops_RAGSA (_hoops_ARCAR, _hoops_PPIPP, _hoops_GIPIA->owner, _hoops_PPSHC);

		_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_GIPIA);
		if ((_hoops_GIPIA->next = _hoops_PPSHC->_hoops_RGRPR) != null)
			_hoops_GIPIA->next->backlink = &_hoops_GIPIA->next;
		_hoops_PPSHC->_hoops_RGRPR = _hoops_GIPIA;
		_hoops_GIPIA->backlink = &_hoops_PPSHC->_hoops_RGRPR;
		_hoops_GIPIA->owner = _hoops_PPSHC;
		HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, _hoops_PPSHC, _hoops_PPIPP->_hoops_RCGC);
	}

	return _hoops_PPSHC;
}

local void _hoops_AHSHC (
	int							count,
	_hoops_ARPA alter *				plane,
	_hoops_ISGI const *	_hoops_PSACR) {
	_hoops_RPRA const *			_hoops_CRIPA;

	/* "_hoops_IRSIR _hoops_HIHP _hoops_GAR _hoops_GPRRH . _hoops_HAICR" - _hoops_RPRRH & _hoops_APRRH */
	/* _hoops_RH _hoops_IAPGR-_hoops_GGSR _hoops_AIRP _hoops_CHR _hoops_HSSPR _hoops_IS _hoops_SHH _hoops_AHHR _hoops_GGR _hoops_IRS _hoops_IRISR 4x3 */

	if (_hoops_PSACR->matrix._hoops_APRA == null)
		HI_Validate_Matrix_Adjoint (&_hoops_PSACR->matrix);

	_hoops_CRIPA = (_hoops_RPRA const *)_hoops_PSACR->matrix._hoops_APRA->data.elements;

	while (count-- > 0) {
		_hoops_ARPA		input = *plane;

		plane->a =	_hoops_CRIPA[0][0] * input.a +
					_hoops_CRIPA[0][1] * input.b +
					_hoops_CRIPA[0][2] * input.c /* +
					_hoops_PPRRH[0][3] * _hoops_CIIA._hoops_GHGP */;

		plane->b =	_hoops_CRIPA[1][0] * input.a +
					_hoops_CRIPA[1][1] * input.b +
					_hoops_CRIPA[1][2] * input.c /* +
					_hoops_PPRRH[1][3] * _hoops_CIIA._hoops_GHGP */;

		plane->c =	_hoops_CRIPA[2][0] * input.a +
					_hoops_CRIPA[2][1] * input.b +
					_hoops_CRIPA[2][2] * input.c /* +
					_hoops_PPRRH[2][3] * _hoops_CIIA._hoops_GHGP */;

		plane->d =	_hoops_CRIPA[3][0] * input.a +
					_hoops_CRIPA[3][1] * input.b +
					_hoops_CRIPA[3][2] * input.c +
					_hoops_CRIPA[3][3] * input.d;

		(void)HI_Normalize_Plane (plane);

		plane++;
	}
}

local void _hoops_PHSHC (
	_hoops_GACR *	dl) {

	if (dl  != null) do {
		dl->_hoops_GSAI = (_hoops_GHGI)0xffffffff;
	} while ((dl = dl->next) != null);
}

local void _hoops_HHSHC (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP) {
	Geometry *				geometry;
	Subsegment *			_hoops_GIPIA;

	HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, _hoops_SRCP, -1, null, 0);

	if ((geometry = _hoops_SRCP->geometry) != null) do {
		switch (geometry->type) {
			case _hoops_GSIP:
			case _hoops_SCIP: {
				Polyhedron *	_hoops_HPGPR = (Polyhedron *)geometry;
				Tristrip *	ts;
				Polyedge *	pe;
				Polymarker *	pm;

				if ((ts = _hoops_HPGPR->tristrips) != null) do {
					_hoops_PHSHC (ts->_hoops_GAHA);
				} while ((ts = ts->next) != null);
				if ((pe = _hoops_HPGPR->_hoops_SHGPR) != null) do {
					_hoops_PHSHC (pe->_hoops_GAHA);
				} while ((pe = pe->next) != null);
				if ((pm = _hoops_HPGPR->_hoops_GIGPR) != null) do {
					_hoops_PHSHC (pm->_hoops_GAHA);
				} while ((pm = pm->next) != null);
				if ((pe = _hoops_HPGPR->_hoops_CHGPR) != null) do {
					_hoops_PHSHC (pe->_hoops_GAHA);
				} while ((pe = pe->next) != null);
			}	break;

			case _hoops_CSIP: {
				PolyCylinder *		_hoops_HSPIR = (PolyCylinder *)geometry;

				_hoops_PHSHC (_hoops_HSPIR->_hoops_SGHIR);
				_hoops_PHSHC (_hoops_HSPIR->_hoops_GRHIR);
			}	break;

			case _hoops_HGCP: {
				_hoops_PHSHC (((Image *)geometry)->_hoops_GAHA);
			}	break;
		}
	} while ((geometry = geometry->next) != null);

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_HHSHC (_hoops_RIGC, _hoops_SSIGP (_hoops_GIPIA));
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}

local _hoops_CRCP * _hoops_IHSHC (
	_hoops_ICCHC *		_hoops_ARCAR,
	Geometry *				geometry,
	_hoops_ISGI *		_hoops_PSACR,
	bool					_hoops_CHSHC,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_CRCP *				_hoops_PPSHC) {
	Geometry *				next;
	float const *			mat = &_hoops_PSACR->matrix.elements[0][0];
#if 0
	bool					_hoops_SHSHC;

	_hoops_SHSHC = _hoops_SRSPA (_hoops_PSACR->matrix.elements) < 0.0f;
#endif

	do {
		next = geometry->next;

		switch (geometry->type) {
			case _hoops_SGCP: {
				bool			transform = true;	/* _hoops_ICRP _hoops_PPCAR _hoops_AGIR */

				if (_hoops_SRCP != null) {
					if (_hoops_PSACR->matrix._hoops_CPH == 0.0f ||
						BIT (geometry->_hoops_RRHH, _hoops_SHHI)) {
						_hoops_PPSHC = _hoops_RHSHC (_hoops_ARCAR, _hoops_PPSHC, (_hoops_HPAH *)geometry, _hoops_SRCP, _hoops_PSACR);
						transform = false;
					}
				}
				else if (BIT (geometry->_hoops_RRHH, _hoops_SHHI)) {	/* _hoops_GCGRA */
					_hoops_AIHI *		_hoops_SIIGP = (_hoops_AIHI *)geometry;
					_hoops_PHPIR *			_hoops_HGSSR;

					ALLOC (_hoops_HGSSR, _hoops_PHPIR);
					ZERO_STRUCT (_hoops_HGSSR, _hoops_PHPIR);

					_hoops_HGSSR->center.x = _hoops_SIIGP->center.x;
					_hoops_HGSSR->center.y = _hoops_SIIGP->center.y;
					_hoops_HGSSR->center.z = 0.0f;

					_hoops_HGSSR->radius = _hoops_SIIGP->radius;

					_hoops_HGSSR->start.x = _hoops_SIIGP->center.x + _hoops_SIIGP->radius;
					_hoops_HGSSR->start.y = _hoops_SIIGP->center.y;
					_hoops_HGSSR->start.z = 0.0f;

					_hoops_HGSSR->_hoops_GGSSR.x = _hoops_SIIGP->center.x;
					_hoops_HGSSR->_hoops_GGSSR.y = _hoops_SIIGP->center.y + _hoops_SIIGP->radius;
					_hoops_HGSSR->_hoops_GGSSR.z = 0.0f;

					_hoops_HGSSR->end.x = _hoops_SIIGP->center.x - _hoops_SIIGP->radius;
					_hoops_HGSSR->end.y = _hoops_SIIGP->center.y;
					_hoops_HGSSR->end.z = 0.0f;

					_hoops_HGSSR->_hoops_GGHI.x = _hoops_SIIGP->radius;
					_hoops_HGSSR->_hoops_GGHI.y = 0.0f;
					_hoops_HGSSR->_hoops_GGHI.z = 0.0f;

					_hoops_HGSSR->_hoops_RGHI.x = 0.0f;
					_hoops_HGSSR->_hoops_RGHI.y = _hoops_SIIGP->radius;
					_hoops_HGSSR->_hoops_RGHI.z = 0.0f;

					_hoops_HGSSR->plane.a = 0.0f;
					_hoops_HGSSR->plane.b = 0.0f;
					_hoops_HGSSR->plane.c = -1.0f;
					_hoops_HGSSR->plane.d = 0.0f;

					_hoops_HGSSR->type = _hoops_SGCP;
					_hoops_HGSSR->owner = _hoops_SIIGP->owner;

					geometry = (Geometry *)_hoops_HGSSR;
					if ((geometry->next = _hoops_SIIGP->next) != null)
						geometry->next->backlink = &geometry->next;
					geometry->backlink = _hoops_SIIGP->backlink;
					*geometry->backlink = geometry;

					_hoops_SIIGP->backlink = &_hoops_SIIGP->next;
					_hoops_SIIGP->next = null;
					_hoops_HPRH (_hoops_SIIGP);
				}

				if (transform) {
					_hoops_PHPIR *			_hoops_HGSSR = (_hoops_PHPIR *)geometry;
					Point			_hoops_CSPIR[2];

					_hoops_CSPIR[0].x = _hoops_HGSSR->center.x + _hoops_HGSSR->_hoops_GGHI.x;
					_hoops_CSPIR[0].y = _hoops_HGSSR->center.y + _hoops_HGSSR->_hoops_GGHI.y;
					_hoops_CSPIR[0].z = _hoops_HGSSR->center.z + _hoops_HGSSR->_hoops_GGHI.z;
					_hoops_CSPIR[1].x = _hoops_HGSSR->center.x + _hoops_HGSSR->_hoops_RGHI.x;
					_hoops_CSPIR[1].y = _hoops_HGSSR->center.y + _hoops_HGSSR->_hoops_RGHI.y;
					_hoops_CSPIR[1].z = _hoops_HGSSR->center.z + _hoops_HGSSR->_hoops_RGHI.z;

					HI_Transform_Points_43 (1, &_hoops_HGSSR->center, mat, &_hoops_HGSSR->center);
					_hoops_AHSHC (1, &_hoops_HGSSR->plane, _hoops_PSACR);
					HI_Transform_Points_43 (2, _hoops_CSPIR, mat, _hoops_CSPIR);

					_hoops_HGSSR->_hoops_GGHI.x = _hoops_CSPIR[0].x - _hoops_HGSSR->center.x;
					_hoops_HGSSR->_hoops_GGHI.y = _hoops_CSPIR[0].y - _hoops_HGSSR->center.y;
					_hoops_HGSSR->_hoops_GGHI.z = _hoops_CSPIR[0].z - _hoops_HGSSR->center.z;
					_hoops_HGSSR->_hoops_RGHI.x = _hoops_CSPIR[1].x - _hoops_HGSSR->center.x;
					_hoops_HGSSR->_hoops_RGHI.y = _hoops_CSPIR[1].y - _hoops_HGSSR->center.y;
					_hoops_HGSSR->_hoops_RGHI.z = _hoops_CSPIR[1].z - _hoops_HGSSR->center.z;

					HI_Transform_Points_43 (1, &_hoops_HGSSR->start,  mat, &_hoops_HGSSR->start);
					HI_Transform_Points_43 (1, &_hoops_HGSSR->_hoops_GGSSR, mat, &_hoops_HGSSR->_hoops_GGSSR);
					HI_Transform_Points_43 (1, &_hoops_HGSSR->end,    mat, &_hoops_HGSSR->end);
				}
			}	break;

			case _hoops_RIIP:
			case _hoops_GRCP:
			case _hoops_RRCP: {
				bool			transform = true;	/* _hoops_ICRP _hoops_PPCAR _hoops_AGIR */

				if (_hoops_SRCP != null) {
					if (_hoops_PSACR->matrix._hoops_CPH == 0.0f ||
						BIT (geometry->_hoops_RRHH, _hoops_SHHI)) {
						_hoops_PPSHC = _hoops_RHSHC (_hoops_ARCAR, _hoops_PPSHC, (_hoops_HPAH *)geometry, _hoops_SRCP, _hoops_PSACR);
						transform = false;
					}
				}
				else if (BIT (geometry->_hoops_RRHH, _hoops_SHHI)) {	/* _hoops_GCGRA */
					Circular_Arc_Lite *	_hoops_IHAPH = (Circular_Arc_Lite *)geometry;
					Circular_Arc *		arc;
					float					_hoops_GGHCR, _hoops_AGHCR;

					ALLOC (arc, Circular_Arc);
					ZERO_STRUCT (arc, Circular_Arc);

					arc->center.x = _hoops_IHAPH->center.x;
					arc->center.y = _hoops_IHAPH->center.y;
					arc->center.z = 0.0f;

					arc->radius = _hoops_IHAPH->radius;
					arc->arc_start = _hoops_IHAPH->arc_start;
					arc->_hoops_PHHI = _hoops_IHAPH->_hoops_PHHI;

					_hoops_RICH (_hoops_IHAPH->arc_start * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					arc->start.x = _hoops_IHAPH->center.x + _hoops_AGHCR * _hoops_IHAPH->radius;
					arc->start.y = _hoops_IHAPH->center.y + _hoops_GGHCR * _hoops_IHAPH->radius;
					arc->start.z = 0.0f;

					_hoops_RICH (0.5f * (_hoops_IHAPH->arc_start + _hoops_IHAPH->_hoops_PHHI) * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					arc->_hoops_GGSSR.x = _hoops_IHAPH->center.x + _hoops_AGHCR * _hoops_IHAPH->radius;
					arc->_hoops_GGSSR.y = _hoops_IHAPH->center.y + _hoops_GGHCR * _hoops_IHAPH->radius;
					arc->_hoops_GGSSR.z = 0.0f;

					_hoops_RICH (_hoops_IHAPH->_hoops_PHHI * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					arc->end.x = _hoops_IHAPH->center.x + _hoops_AGHCR * _hoops_IHAPH->radius;
					arc->end.y = _hoops_IHAPH->center.y + _hoops_GGHCR * _hoops_IHAPH->radius;
					arc->end.z = 0.0f;

					arc->_hoops_GGHI.x = arc->start.x - arc->center.x;
					arc->_hoops_GGHI.y = arc->start.y - arc->center.y;
					arc->_hoops_GGHI.z = 0.0f;

					arc->_hoops_RGHI.x = -arc->_hoops_GGHI.y;
					arc->_hoops_RGHI.y =  arc->_hoops_GGHI.x;
					arc->_hoops_RGHI.z = 0.0f;

					arc->plane.a = 0.0f;
					arc->plane.b = 0.0f;
					arc->plane.c = -1.0f;
					arc->plane.d = 0.0f;

					arc->type = _hoops_IHAPH->type;
					arc->owner = _hoops_IHAPH->owner;

					geometry = (Geometry *)arc;
					if ((geometry->next = _hoops_IHAPH->next) != null)
						geometry->next->backlink = &geometry->next;
					geometry->backlink = _hoops_IHAPH->backlink;
					*geometry->backlink = geometry;

					_hoops_IHAPH->backlink = &_hoops_IHAPH->next;
					_hoops_IHAPH->next = null;
					_hoops_HPRH (_hoops_IHAPH);
				}

				if (transform) {
					if (BIT (geometry->_hoops_RRHH, _hoops_RGGGA)) {
						_hoops_SSSSR *	_hoops_GISHC = (_hoops_SSSSR *)geometry;

						HI_Transform_Points_43 (3, _hoops_GISHC->points, mat, _hoops_GISHC->points);
					}
					else {
						Circular_Arc *	arc = (Circular_Arc *)geometry;
						Point			_hoops_CSPIR[2];

						_hoops_CSPIR[0].x = arc->center.x + arc->_hoops_GGHI.x;
						_hoops_CSPIR[0].y = arc->center.y + arc->_hoops_GGHI.y;
						_hoops_CSPIR[0].z = arc->center.z + arc->_hoops_GGHI.z;
						_hoops_CSPIR[1].x = arc->center.x + arc->_hoops_RGHI.x;
						_hoops_CSPIR[1].y = arc->center.y + arc->_hoops_RGHI.y;
						_hoops_CSPIR[1].z = arc->center.z + arc->_hoops_RGHI.z;

						HI_Transform_Points_43 (1, &arc->center, mat, &arc->center);
						_hoops_AHSHC (1, &arc->plane, _hoops_PSACR);
						HI_Transform_Points_43 (2, _hoops_CSPIR, mat, _hoops_CSPIR);

						arc->_hoops_GGHI.x = _hoops_CSPIR[0].x - arc->center.x;
						arc->_hoops_GGHI.y = _hoops_CSPIR[0].y - arc->center.y;
						arc->_hoops_GGHI.z = _hoops_CSPIR[0].z - arc->center.z;
						arc->_hoops_RGHI.x = _hoops_CSPIR[1].x - arc->center.x;
						arc->_hoops_RGHI.y = _hoops_CSPIR[1].y - arc->center.y;
						arc->_hoops_RGHI.z = _hoops_CSPIR[1].z - arc->center.z;

						HI_Transform_Points_43 (1, &arc->start,  mat, &arc->start);
						HI_Transform_Points_43 (1, &arc->_hoops_GGSSR, mat, &arc->_hoops_GGSSR);
						HI_Transform_Points_43 (1, &arc->end,    mat, &arc->end);
					}
				}
			}	break;


			case _hoops_HGPGR: {
				_hoops_HHPIR *			_hoops_ARRGA = (_hoops_HHPIR *)geometry;

				_hoops_AHSHC (_hoops_ARRGA->count, _hoops_ARRGA->planes, _hoops_PSACR);
			}	break;


			case _hoops_ASIP: {
				if (_hoops_PSACR->matrix._hoops_CPH == 0.0f) {
					_hoops_PPSHC = _hoops_RHSHC (_hoops_ARCAR, _hoops_PPSHC, (_hoops_HPAH *)geometry, _hoops_SRCP, _hoops_PSACR);
				}
				else {
					Cylinder *			cylinder = (Cylinder *)geometry;

					HI_Transform_Points_43 (2, cylinder->axis, mat, cylinder->axis);
					cylinder->radius *= _hoops_PSACR->matrix._hoops_CPH;
				}
			}	break;


			case _hoops_CSIP: {
				if (_hoops_PSACR->matrix._hoops_CPH == 0.0f) {
					_hoops_PPSHC = _hoops_RHSHC (_hoops_ARCAR, _hoops_PPSHC, (_hoops_HPAH *)geometry, _hoops_SRCP, _hoops_PSACR);
				}
				else {
					PolyCylinder *		_hoops_HSPIR = (PolyCylinder *)geometry;
					int					i;

					HI_Transform_Points_43 (_hoops_HSPIR->point_count, _hoops_HSPIR->points, mat, _hoops_HSPIR->points);
					HI_Compute_Transformed_Vectors (2, _hoops_HSPIR->_hoops_ACCSA, mat, _hoops_HSPIR->_hoops_ACCSA);
					HI_Normalize_Vectors (2, _hoops_HSPIR->_hoops_ACCSA);
					for (i=0; i<_hoops_HSPIR->_hoops_ISPIR; i++)
						_hoops_HSPIR->radii[i] *= _hoops_PSACR->matrix._hoops_CPH;
					_hoops_HSPIR->_hoops_PCCSA *= _hoops_PSACR->matrix._hoops_CPH;

					_hoops_HSPIR->bounding = _hoops_HSPIR->bounding._hoops_SCIS (mat);
				}
			}	break;


			case _hoops_HSIP: {
				if (_hoops_PSACR->matrix._hoops_CPH == 0.0f) {
					_hoops_PPSHC = _hoops_RHSHC (_hoops_ARCAR, _hoops_PPSHC, (_hoops_HPAH *)geometry, _hoops_SRCP, _hoops_PSACR);
				}
				else {
					Sphere *			sphere = (Sphere *)geometry;

					HI_Transform_Points_43 (1, &sphere->data.center, mat, &sphere->data.center);
					if (sphere->_hoops_CSPIR != null)
						HI_Compute_Transformed_Vectors (2, sphere->_hoops_CSPIR, mat, sphere->_hoops_CSPIR);
					sphere->data.radius *= _hoops_PSACR->matrix._hoops_CPH;
				}
			}	break;


			case _hoops_CGCP: {
				Ellipse *				ellipse = (Ellipse *)geometry;
				Point					_hoops_CSPIR[2];

				_hoops_CSPIR[0].x = ellipse->center.x + ellipse->_hoops_GGHI.x;
				_hoops_CSPIR[0].y = ellipse->center.y + ellipse->_hoops_GGHI.y;
				_hoops_CSPIR[0].z = ellipse->center.z + ellipse->_hoops_GGHI.z;
				_hoops_CSPIR[1].x = ellipse->center.x + ellipse->_hoops_RGHI.x;
				_hoops_CSPIR[1].y = ellipse->center.y + ellipse->_hoops_RGHI.y;
				_hoops_CSPIR[1].z = ellipse->center.z + ellipse->_hoops_RGHI.z;

				HI_Transform_Points_43 (1, &ellipse->center, mat, &ellipse->center);
				_hoops_AHSHC (1, &ellipse->plane, _hoops_PSACR);
				HI_Transform_Points_43 (2, _hoops_CSPIR, mat, _hoops_CSPIR);

				ellipse->_hoops_GGHI.x = _hoops_CSPIR[0].x - ellipse->center.x;
				ellipse->_hoops_GGHI.y = _hoops_CSPIR[0].y - ellipse->center.y;
				ellipse->_hoops_GGHI.z = _hoops_CSPIR[0].z - ellipse->center.z;
				ellipse->_hoops_RGHI.x = _hoops_CSPIR[1].x - ellipse->center.x;
				ellipse->_hoops_RGHI.y = _hoops_CSPIR[1].y - ellipse->center.y;
				ellipse->_hoops_RGHI.z = _hoops_CSPIR[1].z - ellipse->center.z;

				HI_Transform_Points_43 (1, &ellipse->major, mat, &ellipse->major);
				HI_Transform_Points_43 (1, &ellipse->minor, mat, &ellipse->minor);
			}	break;

			case _hoops_GIIP: {
				Elliptical_Arc *		arc = (Elliptical_Arc *)geometry;
				Point					_hoops_CSPIR[2];

				_hoops_CSPIR[0].x = arc->center.x + arc->_hoops_GGHI.x;
				_hoops_CSPIR[0].y = arc->center.y + arc->_hoops_GGHI.y;
				_hoops_CSPIR[0].z = arc->center.z + arc->_hoops_GGHI.z;
				_hoops_CSPIR[1].x = arc->center.x + arc->_hoops_RGHI.x;
				_hoops_CSPIR[1].y = arc->center.y + arc->_hoops_RGHI.y;
				_hoops_CSPIR[1].z = arc->center.z + arc->_hoops_RGHI.z;

				HI_Transform_Points_43 (1, &arc->center, mat, &arc->center);
				_hoops_AHSHC (1, &arc->plane, _hoops_PSACR);
				HI_Transform_Points_43 (2, _hoops_CSPIR, mat, _hoops_CSPIR);

				arc->_hoops_GGHI.x = _hoops_CSPIR[0].x - arc->center.x;
				arc->_hoops_GGHI.y = _hoops_CSPIR[0].y - arc->center.y;
				arc->_hoops_GGHI.z = _hoops_CSPIR[0].z - arc->center.z;
				arc->_hoops_RGHI.x = _hoops_CSPIR[1].x - arc->center.x;
				arc->_hoops_RGHI.y = _hoops_CSPIR[1].y - arc->center.y;
				arc->_hoops_RGHI.z = _hoops_CSPIR[1].z - arc->center.z;

				HI_Transform_Points_43 (1, &arc->major, mat, &arc->major);
				HI_Transform_Points_43 (1, &arc->minor, mat, &arc->minor);
			}	break;


			case _hoops_GGCP: {
				Grid *					grid = (Grid *)geometry;
				Point					_hoops_CSPIR[2];

				_hoops_CSPIR[0].x = grid->origin.x + grid->_hoops_GGHI.x;
				_hoops_CSPIR[0].y = grid->origin.y + grid->_hoops_GGHI.y;
				_hoops_CSPIR[0].z = grid->origin.z + grid->_hoops_GGHI.z;
				_hoops_CSPIR[1].x = grid->origin.x + grid->_hoops_RGHI.x;
				_hoops_CSPIR[1].y = grid->origin.y + grid->_hoops_RGHI.y;
				_hoops_CSPIR[1].z = grid->origin.z + grid->_hoops_RGHI.z;

				HI_Transform_Points_43 (1, &grid->origin, mat, &grid->origin);
				HI_Transform_Points_43 (1, &grid->ref1, mat, &grid->ref1);
				HI_Transform_Points_43 (1, &grid->ref2, mat, &grid->ref2);
				_hoops_AHSHC (1, &grid->plane, _hoops_PSACR);
				HI_Transform_Points_43 (2, _hoops_CSPIR, mat, _hoops_CSPIR);

				grid->_hoops_GGHI.x = _hoops_CSPIR[0].x - grid->origin.x;
				grid->_hoops_GGHI.y = _hoops_CSPIR[0].y - grid->origin.y;
				grid->_hoops_GGHI.z = _hoops_CSPIR[0].z - grid->origin.z;
				grid->_hoops_RGHI.x = _hoops_CSPIR[1].x - grid->origin.x;
				grid->_hoops_RGHI.y = _hoops_CSPIR[1].y - grid->origin.y;
				grid->_hoops_RGHI.z = _hoops_CSPIR[1].z - grid->origin.z;
			}	break;


			case _hoops_HGCP: {
				Image *				image = (Image *)geometry;

				HI_Transform_Points_43 (1, &image->_hoops_CSAI, mat, &image->_hoops_CSAI);
			}	break;


			case _hoops_ICIP: {
				Light *				light = (Light *)geometry;

				if (!BIT (light->flags, _hoops_RISGP)) switch (light->_hoops_PRR) {
					case _hoops_H: {
						_hoops_HIPIR alter *	dl = (_hoops_HIPIR alter *)light;

						HI_Compute_Transformed_Vectors (1, &dl->direction, mat,
														&dl->direction);
						HI_Compute_Transformed_Vectors (1, (Vector *)&dl->original, mat,
														(Vector *)&dl->original);
					}	break;
					case _hoops_C: {
						_hoops_AIPIR alter *		pl = (_hoops_AIPIR alter *)light;

						HI_Transform_Points_43 (1, &pl->position, mat, &pl->position);
					}	break;
					case _hoops_I: {
						_hoops_PIPIR alter *		sl = (_hoops_PIPIR alter *)light;

						HI_Transform_Points_43 (1, &sl->position, mat, &sl->position);
						HI_Transform_Points_43 (1, &sl->target, mat, &sl->target);
					}	break;
					case _hoops_S: {
						_hoops_SHPIR alter *		al = (_hoops_SHPIR alter *)light;

						HI_Transform_Points_43 (al->count, al->points, mat, al->points);
					}	break;
				}
			}	break;


			case _hoops_PCIP: {
				Marker *			marker = (Marker *)geometry;

				HI_Transform_Points_43 (1, &marker->_hoops_CSAI, mat, &marker->_hoops_CSAI);
			}	break;

			case _hoops_PIRS: {
				_hoops_GRPGR *	_hoops_CPAI = (_hoops_GRPGR *)geometry;

				HI_Transform_Points_43 (_hoops_CPAI->count, _hoops_CPAI->points, mat, _hoops_CPAI->points);
			}	break;


			case _hoops_GSIP:
			case _hoops_SCIP: {
				Polyhedron *		_hoops_HPGPR = (Polyhedron *)geometry;
				bool				transform = true;

				if (_hoops_PSACR->matrix._hoops_CPH == 0.0f &&
					_hoops_SRCP != null && _hoops_HPGPR->_hoops_HGAIR != null) {
					int				level;

					/* _hoops_HSPAR _hoops_IH _hoops_GRAA-_hoops_GRRRI _hoops_PRCCA _hoops_IGPC, _hoops_RPP _hoops_GII _hoops_SR _hoops_PIHA _hoops_RISHC _hoops_RH _hoops_SHSC _hoops_AHAP */
					for (level = 0; level < _hoops_IGAIR; level++) {
						Geometry const *		_hoops_CSGCR;

						if ((_hoops_CSGCR = _hoops_HPGPR->_hoops_HGAIR->data[level]) != null) do {
							switch (_hoops_CSGCR->type) {
								case _hoops_SGCP:
								case _hoops_RIIP:
								case _hoops_GRCP:
								case _hoops_RRCP:
								case _hoops_ASIP:
								case _hoops_CSIP:
								case _hoops_HSIP: {
									transform = false;
								}	break;
							}

							if (!transform)
								break;
						} while ((_hoops_CSGCR = _hoops_CSGCR->next) != null);

						if (!transform)
							break;
					}
				}


				if (transform) {
					int		point_count = _hoops_HPGPR->point_count + _hoops_HPGPR->_hoops_GCRHR;

					HI_Transform_Points_43 (point_count, _hoops_HPGPR->points, mat, _hoops_HPGPR->points);

					_hoops_HPGPR->bounding = Bounding::Create(point_count, _hoops_HPGPR->points);

					if (_hoops_HPGPR->local_vertex_attributes.normals != null) {
						Vector *		normals = _hoops_HPGPR->local_vertex_attributes.normals;

						HI_Compute_Transformed_Vectors (point_count, normals, mat, normals);
						HI_Normalize_Vectors (point_count, normals);
					}
					if (_hoops_HPGPR->_hoops_IHHPR.normals != null) {
						Vector *		normals = _hoops_HPGPR->_hoops_IHHPR.normals;

						HI_Compute_Transformed_Vectors (_hoops_HPGPR->_hoops_SPHA, normals, mat, normals);
						HI_Normalize_Vectors (_hoops_HPGPR->_hoops_SPHA, normals);
					}
					if (_hoops_HPGPR->local_face_attributes.normals != null) {
						_hoops_ARPA *		planes = _hoops_HPGPR->local_face_attributes.normals;

						_hoops_AHSHC (_hoops_HPGPR->face_count, planes, _hoops_PSACR);
					}

					if (_hoops_HPGPR->_hoops_HGAIR != null) {
						int				level;

						for (level = 0; level < _hoops_IGAIR; level++) {
							if (_hoops_HPGPR->_hoops_HGAIR->data[level] != null) {
								Geometry const *		_hoops_CSGCR;

								int flags = _hoops_ARCAR->flags;
								_hoops_ARCAR->flags &= ~_hoops_CSIHC;
								_hoops_IHSHC (_hoops_ARCAR, _hoops_HPGPR->_hoops_HGAIR->data[level], _hoops_PSACR, _hoops_CHSHC,
													  null, null);
								_hoops_ARCAR->flags = flags;

								_hoops_CSGCR = _hoops_HPGPR->_hoops_HGAIR->data[level];
								do {
									HI_Add_Geometry_Bounding (_hoops_ARCAR->_hoops_RIGC, _hoops_CSGCR, null, ~0, null, _hoops_CRIAA, _hoops_HPGPR->bounding);
								} while ((_hoops_CSGCR = _hoops_CSGCR->next) != null);
							}
						}
					}
				}
				else
					_hoops_PPSHC = _hoops_RHSHC (_hoops_ARCAR, _hoops_PPSHC, (_hoops_HPAH *)geometry, _hoops_SRCP, _hoops_PSACR);
			}  break;


			case _hoops_RCIP: {
				Polygon *	polygon = (Polygon *)geometry;

				HI_Transform_Points_43 (polygon->count, polygon->points, mat, polygon->points);
				_hoops_AHSHC (1, &polygon->plane, _hoops_PSACR);
			}	break;


			case _hoops_PIIP: {
				Line *		line = (Line *)geometry;

				HI_Transform_Points_43 (2, line->points, mat, line->points);
			}	break;

			case _hoops_HIIP:
			case _hoops_IIIP: {
				Polyline *	polyline = (Polyline *)geometry;

				HI_Transform_Points_43 (Abs(polyline->count), polyline->points, mat, polyline->points);
			}	break;


			case _hoops_CHIP: {
#ifndef _hoops_CCPIR
				_hoops_PIRGR *	curve = (_hoops_PIRGR *)geometry;

				HI_Transform_Points_43 (curve->control_point_count, curve->control_points,
											mat, curve->control_points);
				if (curve->polyline.points != null)
					HI_Transform_Points_43 (curve->polyline.count, curve->polyline.points,
												mat, curve->polyline.points);
#endif
			}	break;



			case _hoops_PRCP: {
#ifndef _hoops_GSPIR
				_hoops_APPGR *	surface = (_hoops_APPGR *)geometry;

				HI_Transform_Points_43 (surface->n_u_vertices * surface->n_v_vertices, surface->control_points,
											mat, surface->control_points);
				if (surface->_hoops_IPRI != null) {
					HI_Au_Revoir ((_hoops_HPAH *)surface->_hoops_IPRI);
					surface->_hoops_IPRI = null;
				}
#endif
			}	break;

			case _hoops_AGCP: {
				if (_hoops_CHSHC &&
					ANYBIT (_hoops_PSACR->matrix._hoops_RAGR, _hoops_GRICR|_hoops_CHCP))
					_hoops_PPSHC = _hoops_RHSHC (_hoops_ARCAR, _hoops_PPSHC, (_hoops_HPAH *)geometry, _hoops_SRCP, _hoops_PSACR);
				else {
					_hoops_HACC *		text = (_hoops_HACC *)geometry;

					HI_Transform_Points_43 (1, &text->_hoops_CSAI, mat, &text->_hoops_CSAI);
				}
			}	break;


			case _hoops_AHIP: {
				Attribute *				_hoops_HPHCR = geometry->_hoops_IPPGR;
				_hoops_HRPA *			_hoops_AISHC = &_hoops_PSACR->matrix;
				_hoops_HRPA				_hoops_PISHC;

				while (_hoops_HPHCR != null && _hoops_HPHCR->type < HK_MODELLING_MATRIX)
					_hoops_HPHCR = _hoops_HPHCR->next;

				if (_hoops_HPHCR != null && _hoops_HPHCR->type == HK_MODELLING_MATRIX) {
					_hoops_AISHC = &_hoops_PISHC;
					ZERO_STRUCT (_hoops_AISHC, _hoops_HRPA);
					HI_Multiply_Matrices (&((_hoops_ISGI *)_hoops_HPHCR)->matrix, &_hoops_PSACR->matrix, _hoops_AISHC);
				}

				_hoops_ISGI *	modelling_matrix;
				ZALLOC (modelling_matrix, _hoops_ISGI);

				modelling_matrix->matrix = *_hoops_AISHC;

				if (!HI_Set_Modelling_Matrix (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)geometry, modelling_matrix))
					FREE (modelling_matrix, _hoops_ISGI);
			}	break;


			case _hoops_GHPGR: {
				return _hoops_PPSHC;
			}	_hoops_HHHI;

			case HK_STRING_CURSOR:
			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Unknown/unexpected geometry type");
				return _hoops_PPSHC;
			}	_hoops_HHHI;
		}

		if (geometry->owner == _hoops_SRCP && BIT (_hoops_PSACR->matrix._hoops_RAGR, _hoops_RRICR))
			geometry->_hoops_RRHH |= _hoops_RSPCR;
	} while ((geometry = next) != null);

	return _hoops_PPSHC;
}


local float _hoops_SRSPA (_hoops_RPRA const *m) {
	return (
		m[0][0] * (m[1][1]*m[2][2] - m[2][1]*m[1][2]) -
		m[1][0] * (m[0][1]*m[2][2] - m[2][1]*m[0][2]) +
		m[2][0] * (m[0][1]*m[1][2] - m[1][1]*m[0][2])
	);
}

#define	_hoops_HISHC	_hoops_PICAR	/* _hoops_GII _hoops_PIRA _hoops_HHASH _hoops_HII _hoops_SIH _hoops_GGR _hoops_IISHC */

local bool _hoops_CISHC(_hoops_CRCP const * _hoops_SRCP)
{
	bool _hoops_CISHC = false;

	if (BIT(_hoops_SRCP->_hoops_RRHH, _hoops_IRPGI))
		_hoops_CISHC = true;
	else {
		Geometry const * g = _hoops_SRCP->geometry;
		while (g != null) {
			if (BIT(g->_hoops_RRHH, _hoops_IRPGI)) {
				_hoops_CISHC = true;
				break;
			}
			g = g->next;
		}
	}

	return _hoops_CISHC;
}

local void _hoops_SISHC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_ISGI *		_hoops_PSACR,
	int						_hoops_GCSHC,
	bool					_hoops_CHSHC)
{
	_hoops_ISGI *		matrix = _hoops_PSACR;

	Attribute const *		_hoops_IHPIA = null;
	_hoops_GHAIR alter *		_hoops_RCSHC = null;
	_hoops_CRCP *				_hoops_PPSHC = null;
	Subsegment *			_hoops_GIPIA;
	Subsegment *			next;
	bool					_hoops_SAPA = false;

	Attribute const *	_hoops_ASGPR;
	if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) do {
		if (_hoops_ASGPR->type > _hoops_IAAA (HK_MODELLING_MATRIX, HK_HEURISTICS, HK_TEXT_FONT))
			break;

		if (_hoops_ASGPR->type == HK_MODELLING_MATRIX) {
			_hoops_IHPIA = _hoops_ASGPR;

			if (_hoops_PSACR == null) {
				matrix = (_hoops_ISGI *)_hoops_ASGPR;
				_hoops_PRRH (matrix);
			}
			else {
				ZALLOC (matrix, _hoops_ISGI);
				matrix->type = HK_MODELLING_MATRIX;
				matrix->_hoops_HIHI = 1;
				HI_Multiply_Matrices (&((_hoops_ISGI const *)_hoops_ASGPR)->matrix, &_hoops_PSACR->matrix, &matrix->matrix);
			}

			if (_hoops_SRSPA ((_hoops_RPRA const *)((_hoops_ISGI *)_hoops_IHPIA)->matrix.elements) < 0.0f) {
				_hoops_GCSHC ^= _hoops_HISHC;
				_hoops_SAPA = true;

				if (ANYBIT (_hoops_GCSHC, _hoops_RSA))
					_hoops_GCSHC ^= _hoops_RSA;

				if (_hoops_RCSHC != null) {
					if (ANYBIT (_hoops_RCSHC->value, _hoops_RSA))
						_hoops_RCSHC->value ^= _hoops_RSA;
				}
			}
		}
		else if (_hoops_ASGPR->type == HK_HEURISTICS) {
			_hoops_RCSHC = (_hoops_GHAIR alter *)_hoops_ASGPR;

			if (ANYBIT (_hoops_RCSHC->value, _hoops_RSA)) {
				if (BIT (_hoops_GCSHC, _hoops_HISHC))
					_hoops_RCSHC->value ^= _hoops_RSA;

				_hoops_GCSHC &= ~_hoops_RSA;
				_hoops_GCSHC |= _hoops_RCSHC->value & _hoops_RSA;
			}
		}
		else if (_hoops_ASGPR->type == HK_TEXT_FONT) {
			_hoops_AGPIR const *		_hoops_PGPIR = (_hoops_AGPIR const *)_hoops_ASGPR;

			// _hoops_RRP _hoops_IS _hoops_ACPA _hoops_RGR _hoops_IH _hoops_CHAPA _hoops_PRGI _hoops_RPP _hoops_PSP _hoops_RSGA _hoops_GAPR
			if (BIT (_hoops_PGPIR->_hoops_HAICA, _hoops_PPPAP))
				_hoops_CHSHC = (_hoops_PGPIR->transform != FT_NONE);
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	if (matrix != null && _hoops_CISHC(_hoops_SRCP)) {
		// _hoops_PAH'_hoops_RA _hoops_ARHSA _hoops_RH _hoops_CPAP, _hoops_HIS _hoops_PRIA _hoops_RH _hoops_GCHRR _hoops_RSGA (_hoops_RPP _hoops_HAR _hoops_SAHR _hoops_RH _hoops_IRGH _hoops_SPR)
		if (matrix != (_hoops_ISGI const *)_hoops_IHPIA) {
			_hoops_ISGI *	modelling_matrix;
			ZALLOC (modelling_matrix, _hoops_ISGI);

			modelling_matrix->matrix = matrix->matrix;

			if (!HI_Set_Modelling_Matrix (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, modelling_matrix))
				FREE (modelling_matrix, _hoops_ISGI);
		}
		// _hoops_PPR _hoops_ARP _hoops_GH _hoops_IRS _hoops_CASI _hoops_PIAP _hoops_IH _hoops_CHAPA
		if (matrix != _hoops_PSACR)
			_hoops_HPRH (matrix);
		matrix = null;
		_hoops_IHPIA = null;
		_hoops_SAPA = false;
	}

	if (_hoops_SAPA && ANYBIT (_hoops_GCSHC, _hoops_RSA) &&
		(_hoops_RCSHC == null || !ANYBIT (_hoops_RCSHC->mask, _hoops_RSA))) {
		/* _hoops_RRP _hoops_IS _hoops_HGCR _hoops_RH _hoops_IRPR _hoops_RGSR _hoops_GPP _hoops_RGR _hoops_CAGH */
		if (_hoops_RCSHC == null) {
			Attribute **		_hoops_ASRGR = &_hoops_SRCP->_hoops_IPPGR;

			ZALLOC (_hoops_RCSHC, _hoops_GHAIR);
			_hoops_RCSHC->type = HK_HEURISTICS;
			_hoops_RCSHC->_hoops_HIHI = 1;
			_hoops_RCSHC->owner = _hoops_SRCP;
			_hoops_RCSHC->_hoops_CPGPR = _hoops_HCHPA;
			_hoops_RCSHC->mask = _hoops_RSA;
			_hoops_RCSHC->value = _hoops_GCSHC & _hoops_RSA;

			while (*_hoops_ASRGR != null) {
				if ((*_hoops_ASRGR)->type >= HK_HEURISTICS)
					break;
				_hoops_ASRGR = &(*_hoops_ASRGR)->next;
			}

			if ((_hoops_RCSHC->next = *_hoops_ASRGR) != null)
				(*_hoops_ASRGR)->backlink = &_hoops_RCSHC->next;
			_hoops_RCSHC->backlink = _hoops_ASRGR;
			*_hoops_ASRGR = (Attribute *)_hoops_RCSHC;
		}

		_hoops_RCSHC->mask |= _hoops_RSA;
		_hoops_RCSHC->value |= _hoops_GCSHC & _hoops_RSA;
	}


/* _hoops_RPP _hoops_HPPA _hoops_GHC, _hoops_PGAP _hoops_SIAS _hoops_SHH _hoops_IRGH, _hoops_AA _hoops_SR _hoops_SAHR _hoops_ARP _hoops_RH _hoops_RSGA _hoops_ARI & _hoops_IIRRC? */
	/* _hoops_ACSHC _hoops_RPP _hoops_RH _hoops_HCSP _hoops_HRGR _hoops_ARP _hoops_ARI,
		_hoops_HIH _hoops_IS _hoops_ISPR _hoops_GGR _hoops_RHAR, _hoops_SR _hoops_PAH _hoops_AA _hoops_PCCP _hoops_RGCHR _hoops_GIPHR _hoops_RHIR _hoops_PCSHC (_hoops_PHRSA
		_hoops_RHIR _hoops_RPCII & _hoops_HCSHC (& _hoops_PAII _hoops_PCIAA)) _hoops_IS _hoops_CACH _hoops_RPP "_hoops_IRGH _hoops_HPPA _hoops_GHC" _hoops_HRGR _hoops_ARP _hoops_RPGHH.

		_hoops_PS _hoops_HHS _hoops_GACC _hoops_HPCAR _hoops_ISAP _hoops_SIPP _hoops_RH _hoops_SAAP _hoops_HHIS _hoops_PPR _hoops_HPPP _hoops_IIHA _hoops_GPP _hoops_IHGP _hoops_ICSHC
		(_hoops_GGCR "_hoops_CCSHC" _hoops_RIP _hoops_IS _hoops_PAGIR) _hoops_PPR _hoops_ASSS _hoops_IRS "_hoops_RHRIR" _hoops_CCH _hoops_PGAP _hoops_RHAP _hoops_RH _hoops_IPAC
	*/
#if 0
	if (local _hoops_SCSHC planes &&
		(_hoops_GSSHC || _hoops_RSSHC && _hoops_ASSHC (_hoops_SRCP))) {	/* _hoops_PAR _hoops_HISI... */

		/* _hoops_RPP _hoops_SR _hoops_HS _hoops_IRS _hoops_RSGA _hoops_PPR _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_GAGPR _hoops_RH _hoops_IRGH _hoops_SPR */
		if (matrix != null && matrix != (_hoops_ISGI *)_hoops_IHPIA) {
			HI_Set_Attribute (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP,  HK_MODELLING_MATRIX,
									  _hoops_HGCII, (void *)&matrix->matrix);
		}
		return;
	}
	else
#endif
	{
		/* _hoops_RPP _hoops_SR _hoops_HS _hoops_IRS _hoops_RSGA, _hoops_HIISR _hoops_CCA _hoops_SASI _hoops_AIRC _hoops_PPR _hoops_CIPAA _hoops_IRGH _hoops_CPAP */
		if (matrix != null) {
			if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) {
				float		scale;

				if (matrix->matrix._hoops_CPH != 0.0f)
					scale = matrix->matrix._hoops_CPH;
				else {
					float		temp;

					scale = HI_Compute_Vector_Length ((Vector const *)&matrix->matrix.elements[0][0]);
					temp = HI_Compute_Vector_Length ((Vector const *)&matrix->matrix.elements[1][0]);
					if (temp > scale)
						scale = temp;
					temp = HI_Compute_Vector_Length ((Vector const *)&matrix->matrix.elements[2][0]);
					if (temp > scale)
						scale = temp;
				}

				do switch (_hoops_ASGPR->type) {
					case HK_TEXT_FONT: {
						_hoops_AGPIR alter *		_hoops_PGPIR = (_hoops_AGPIR alter *)_hoops_ASGPR;

						if (!_hoops_CHSHC) {
							if (BIT (_hoops_PGPIR->_hoops_HAICA, _hoops_RPPAP) &&
								(_hoops_PGPIR->_hoops_GHGRP == GSU_ORU || _hoops_PGPIR->_hoops_GHGRP == _hoops_SPSC))
								_hoops_PGPIR->size *= scale;
							if (BIT (_hoops_PGPIR->_hoops_HAICA, _hoops_APPAP) &&
								(_hoops_PGPIR->_hoops_SSPAP == GSU_ORU || _hoops_PGPIR->_hoops_SSPAP == _hoops_SPSC))
								_hoops_PGPIR->_hoops_ACPAP *= scale;
							if (BIT (_hoops_PGPIR->_hoops_HAICA, _hoops_CPPAP) &&
								(_hoops_PGPIR->_hoops_GGHAP == GSU_ORU || _hoops_PGPIR->_hoops_GGHAP == _hoops_SPSC))
								_hoops_PGPIR->_hoops_PCPAP *= scale;
							if (BIT (_hoops_PGPIR->_hoops_HAICA, _hoops_GHPAP) &&
								(_hoops_PGPIR->_hoops_RGHAP == GSU_ORU || _hoops_PGPIR->_hoops_RGHAP == _hoops_SPSC))
								_hoops_PGPIR->_hoops_HCPAP *= scale;
						}
					}	break;

					case HK_LINE_WEIGHT:
					case HK_EDGE_WEIGHT:
					case HK_MARKER_SIZE:
					case HK_TEXT_SPACING: {
						_hoops_AHPIR alter *	item = (_hoops_AHPIR alter *)_hoops_ASGPR;

						if (item->data._hoops_HHP == GSU_ORU || item->data._hoops_HHP == _hoops_SPSC)
							item->data.value *= scale;
					}	break;
				} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
			}

			if (_hoops_SRCP->geometry != null)
				_hoops_PPSHC = _hoops_IHSHC (_hoops_ARCAR, _hoops_SRCP->geometry, matrix, _hoops_CHSHC, _hoops_SRCP, _hoops_PPSHC);
		}


		/* _hoops_PPR _hoops_GHHA */
		if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
			next = _hoops_GIPIA->next;

			if (_hoops_GIPIA == (Subsegment *)_hoops_PPSHC) {
				/* _hoops_IIS'_hoops_GRI _hoops_HAR _hoops_SHH _hoops_RHRH... */
			}
			else if (_hoops_GIPIA->type != _hoops_IRCP) {
				if (matrix != null)
					_hoops_PPSHC = _hoops_RHSHC (_hoops_ARCAR, _hoops_PPSHC, (_hoops_HPAH *)_hoops_GIPIA, _hoops_SRCP, matrix);
			}
			else {
				_hoops_CRCP * _hoops_SIIS = (_hoops_CRCP *)_hoops_GIPIA;

				if (_hoops_SIIS->_hoops_SGRPR() != null || _hoops_CISHC(_hoops_SIIS)) {
					if (matrix != null)
						_hoops_PPSHC = _hoops_RHSHC (_hoops_ARCAR, _hoops_PPSHC, (_hoops_HPAH *)_hoops_SIIS, _hoops_SRCP, matrix);
					_hoops_SISHC (_hoops_ARCAR, _hoops_SIIS, null, _hoops_GCSHC, _hoops_CHSHC);
				}
				else
					_hoops_SISHC (_hoops_ARCAR, _hoops_SIIS, matrix, _hoops_GCSHC, _hoops_CHSHC);
			}
		} while ((_hoops_GIPIA = next) != null);
	}

	/* _hoops_GGAS */
	if (matrix != null && matrix != _hoops_PSACR)
		_hoops_HPRH (matrix);

	if (_hoops_IHPIA != null) {
		_hoops_HPAH alter *		victim = (_hoops_HPAH *)_hoops_IHPIA;

		_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,victim);
		HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, victim);
		_hoops_HPRH (victim);
	}
}

local void _hoops_PSSHC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *		_hoops_SRCP,
	bool			_hoops_HSSHC) {
	Attribute *		_hoops_ASGPR;
	Attribute *		next;
	Geometry *		geometry;
	Subsegment *	_hoops_GIPIA;

	if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) do {
		next = _hoops_ASGPR->next;

		if (_hoops_ASGPR->type == HK_USER_OPTIONS || _hoops_ASGPR->type == HK_USER_VALUE) {
			if (_hoops_HSSHC) {
				if (_hoops_ASGPR->type == HK_USER_OPTIONS) {
					_hoops_HPPIR const * _hoops_IPPIR = (_hoops_HPPIR const *)_hoops_ASGPR;
					if (_hoops_IPPIR->_hoops_IGGSA)
						HI_Distill_User_Options(_hoops_ARCAR->_hoops_RIGC, _hoops_IPPIR, _hoops_ACIAP|_hoops_PCIAP);
				}
			}
			else {
				_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_ASGPR);
				_hoops_HPRH (_hoops_ASGPR);
			}
		}
	} while ((_hoops_ASGPR = next) != null);

	if ((geometry = _hoops_SRCP->geometry) != null) do {
		if ((_hoops_ASGPR = geometry->_hoops_IPPGR) != null) do {
			next = _hoops_ASGPR->next;

			if (_hoops_ASGPR->type == HK_USER_OPTIONS || _hoops_ASGPR->type == HK_USER_VALUE) {
				if (_hoops_HSSHC) {
					if (_hoops_ASGPR->type == HK_USER_OPTIONS) {
						_hoops_HPPIR const * _hoops_IPPIR = (_hoops_HPPIR const *)_hoops_ASGPR;
						if (_hoops_IPPIR->_hoops_IGGSA)
							HI_Distill_User_Options(_hoops_ARCAR->_hoops_RIGC, _hoops_IPPIR, _hoops_ACIAP|_hoops_PCIAP);
					}
				}
				else {
					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_ASGPR);
					_hoops_HPRH (_hoops_ASGPR);
				}
			}
		} while ((_hoops_ASGPR = next) != null);
	} while ((geometry = geometry->next) != null);

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP)
			_hoops_PSSHC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA, _hoops_HSSHC);
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}

local void _hoops_ISSHC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP) {
	Subsegment *		_hoops_GIPIA;

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		Subsegment *	next = _hoops_GIPIA->next;
		/* _hoops_PAH'_hoops_RA _hoops_IGIRR _hoops_IRCH _hoops_RAGPR _hoops_CRRPR _hoops_SIHH _hoops_RRI _hoops_ICSHC */
		if (_hoops_GIPIA->type == _hoops_AGRPR) {
			_hoops_PGRPR *		include = (_hoops_PGRPR alter *)_hoops_GIPIA;
			_hoops_CRCP *		ref = _hoops_PGRCA(include->_hoops_IGRPR);

			if (include->condition.count == 0 &&
				!BIT (ref->_hoops_PHSI, _hoops_GISIR)) {
				_hoops_HCRPR					_hoops_CSSHC;
				_hoops_IISCA	_hoops_SSSHC;

				ZERO_STRUCT (&_hoops_SSSHC, _hoops_IISCA);
				_hoops_SSSHC._hoops_IIGSA = true;

				/* _hoops_IRHH _hoops_IPS _hoops_GGGIC _hoops_IS _hoops_SRCH _hoops_GGHS _hoops_SPIH */
				_hoops_RSAI (&ref->name, _hoops_HCRPR, &_hoops_CSSHC);
				ZERO_STRUCT (&ref->name, _hoops_HCRPR);

				Key			new_key = HI_Copy_Segment (_hoops_ARCAR->_hoops_RIGC, ref, _hoops_SRCP, &_hoops_GIPIA->next, _hoops_GIPIA,
														null, false, &_hoops_SSSHC);
				if (new_key != _hoops_SHSSR) {
					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC, include);
					HI_Delete_User_Key (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)include);
					HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)include);
					include->_hoops_RRHH |= _hoops_HGAGR;
					_hoops_HPRH (include);

					_hoops_ISSHC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_RCSSR (_hoops_ARCAR->_hoops_RIGC, new_key));
				}
				_hoops_RSAI (&_hoops_CSSHC, _hoops_HCRPR, &ref->name);
				if (ref->priority != 0) {
					_hoops_GIPIA->priority = ref->priority;
					_hoops_SRCP->_hoops_PHSI |= _hoops_GGPSA | _hoops_CCHGP;
				}
			}
		}
		else if (_hoops_GIPIA->type == _hoops_IRCP)
			_hoops_ISSHC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA);

		_hoops_GIPIA = next;
	} while (_hoops_GIPIA != null);
}

local void _hoops_RGGIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP) {
	Subsegment *		_hoops_GIPIA;
	Geometry *			geo;
	Geometry *			_hoops_AGGIC;

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP)
			_hoops_RGGIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA);
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	// _hoops_CPAP _hoops_RAS _hoops_CHAPA, _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GIHHH _hoops_GHIR _hoops_IPAC _hoops_GII _hoops_RPGCA _hoops_GRSSA _hoops_CHAPA...
	if ((geo = _hoops_SRCP->geometry) != null) do {
		_hoops_AGGIC = geo->next;

		Key				_hoops_PGGIC = geo->key;
		_hoops_CRCP *		_hoops_SAGSA = HI_Separate_Geometry_Attributes (_hoops_ARCAR->_hoops_RIGC, geo);

		if (BIT (_hoops_ARCAR->flags, _hoops_CSIHC)) {
			_hoops_AHCHC *		id;

			ZALLOC (id, _hoops_AHCHC);
			id->type = _hoops_CPCHC;
			id->owner = (_hoops_CRCP *)_hoops_SRCP;
			id->_hoops_HIHI = 1;
			if ((id->next = _hoops_SAGSA->_hoops_IPPGR) != null)
				id->next->backlink = &id->next;
			_hoops_SAGSA->_hoops_IPPGR = (Attribute *)id;
			id->backlink = &_hoops_SAGSA->_hoops_IPPGR;

			ALLOC_ARRAY (id->_hoops_GPICA, 1, _hoops_SPCHC);
			id->_hoops_PHCHC = 1;
			id->_hoops_GPICA[0]._hoops_GHCHC = _hoops_SRCP->key;
			id->_hoops_GPICA[0]._hoops_CISAP = _hoops_PGGIC;
			id->_hoops_GPICA[0]._hoops_RHCHC = 0;
		}
	} while ((geo = _hoops_AGGIC) != null);
}

enum _hoops_HGGIC { _hoops_IGGIC, _hoops_CGGIC, _hoops_SGGIC };

local _hoops_HGGIC	_hoops_GRGIC[3] = { _hoops_CGGIC, _hoops_IGGIC, _hoops_SGGIC };

local _hoops_HGGIC	_hoops_RRGIC[3][3] = {	{ 	_hoops_IGGIC,		_hoops_IGGIC,		_hoops_IGGIC		},
									{ 	_hoops_IGGIC,		_hoops_CGGIC,		_hoops_SGGIC	},
									{ 	_hoops_IGGIC,		_hoops_SGGIC,	_hoops_SGGIC	} };

local _hoops_HGGIC	_hoops_ARGIC[3][3] = {	{ 	_hoops_IGGIC,		_hoops_CGGIC,		_hoops_SGGIC	},
									{ 	_hoops_CGGIC,		_hoops_CGGIC,		_hoops_CGGIC			},
									{ 	_hoops_SGGIC,	_hoops_CGGIC,		_hoops_SGGIC	} };

local _hoops_HGGIC	_hoops_PRGIC[3][3] = {	{ 	_hoops_CGGIC,		_hoops_IGGIC,		_hoops_SGGIC	},
									{ 	_hoops_IGGIC,		_hoops_CGGIC,		_hoops_SGGIC	},
									{ 	_hoops_SGGIC,	_hoops_SGGIC,	_hoops_SGGIC	} };

local _hoops_HGGIC	_hoops_HRGIC[3][3] = {	{ 	_hoops_IGGIC,		_hoops_CGGIC,		_hoops_SGGIC	},
									{ 	_hoops_CGGIC,		_hoops_IGGIC,		_hoops_SGGIC	},
									{ 	_hoops_SGGIC,	_hoops_SGGIC,	_hoops_SGGIC	} };



local _hoops_HGGIC _hoops_IRGIC (
	_hoops_CCPCA const &		_hoops_SCPCA,
	_hoops_SPPIR const *		_hoops_CRGIC) {

	if (_hoops_SCPCA.count == 0)
		return _hoops_CGGIC;

	if (_hoops_CRGIC == null)
		return _hoops_SGGIC;

	_hoops_HGGIC				_hoops_CGHCA[32];		// _hoops_SRGIC _hoops_HSH
	int						a = 0;

	for (int i = 0; i < _hoops_SCPCA.count; ++i) {
		int				code = _hoops_SCPCA._hoops_ASACA[i];

		switch (code) {
			case _hoops_IHPCA: {
				_hoops_CGHCA[a-1] = _hoops_GRGIC[_hoops_CGHCA[a-1]];
			}	break;
			case _hoops_HIPCA: {
				--a;
				_hoops_CGHCA[a-1] = _hoops_RRGIC[_hoops_CGHCA[a-1]][_hoops_CGHCA[a]];
			}	break;
			case _hoops_ISACA: {
				--a;
				_hoops_CGHCA[a-1] = _hoops_ARGIC[_hoops_CGHCA[a-1]][_hoops_CGHCA[a]];
			}	break;
			case _hoops_RIPCA:
			case _hoops_SIPCA: {
				--a;
				_hoops_CGHCA[a-1] = _hoops_HRGIC[_hoops_CGHCA[a-1]][_hoops_CGHCA[a]];
			}	break;
			case _hoops_AIPCA: {
				--a;
				_hoops_CGHCA[a-1] = _hoops_PRGIC[_hoops_CGHCA[a-1]][_hoops_CGHCA[a]];
			}	break;

			default: {
				int				index = code / 32;
				int				offset = code % 32;

				if (index >= _hoops_CRGIC->count)
					_hoops_CGHCA[a++] = _hoops_SGGIC;
				else if (!BIT (_hoops_CRGIC->_hoops_SGCAA[index] >> offset, 1))
					_hoops_CGHCA[a++] = _hoops_SGGIC;
				else 
					_hoops_CGHCA[a++] = (_hoops_HGGIC)((_hoops_CRGIC->values[index] >> offset) & 1);
			}	break;
		}
	}

	ASSERT (a == 1);

	return _hoops_CGHCA[0];
}

local bool _hoops_GAGIC (
	_hoops_CCPCA const &		_hoops_SCPCA,
	_hoops_SPPIR const *		_hoops_CRGIC) {

	return _hoops_IRGIC (_hoops_SCPCA, _hoops_CRGIC) != _hoops_SGGIC;
}


local bool _hoops_RAGIC (
	_hoops_CRCP const *			node,
	_hoops_SPPIR const *		_hoops_AAGIC) {
	Attribute const *		_hoops_ASGPR;
	Subsegment const *		_hoops_GIPIA;

	if ((_hoops_ASGPR = node->_hoops_IPPGR) != null) do {
		if (_hoops_ASGPR->type == HK_STYLE) {
			Style const *	style = (Style const *)_hoops_ASGPR;

			for (int i = 0; i < style->condition.count; ++i) {
				int				code = style->condition._hoops_ASACA[i];

				if (code >= 0) {
					int				index = code / 32;
					int				offset = code % 32;

					if (index < _hoops_AAGIC->count) {
						if (BIT (_hoops_AAGIC->_hoops_SGCAA[index] >> offset, 1))
							return true;
					}
				}
			}
		}
		else
			break;
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	if ((_hoops_GIPIA = node->_hoops_RGRPR) != null) do {
		_hoops_CRCP const *		_hoops_SRCP;

		if (_hoops_GIPIA->type == _hoops_AGRPR) {
			_hoops_PGRPR const *		include = (_hoops_PGRPR const *)_hoops_GIPIA;

			for (int i = 0; i < include->condition.count; ++i) {
				int				code = include->condition._hoops_ASACA[i];

				if (code >= 0) {
					int				index = code / 32;
					int				offset = code % 32;

					if (index < _hoops_AAGIC->count) {
						if (BIT (_hoops_AAGIC->_hoops_SGCAA[index] >> offset, 1))
							return true;
					}
				}
			}

			_hoops_SRCP = include->_hoops_IGRPR;
		}
		else
			_hoops_SRCP = (_hoops_CRCP const *)_hoops_GIPIA;

		if (_hoops_RAGIC (_hoops_SRCP, _hoops_AAGIC))
			return true;
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	return false;
}


#define _hoops_PAGIC				0x00
#define _hoops_HAGIC				0x01
#define _hoops_IAGIC				0x02
#define _hoops_CAGIC			0x04
#define _hoops_SAGIC			0x08
#define _hoops_GPGIC			0x10
#define _hoops_RPGIC				0x20
#define _hoops_APGIC			0x40

local int _hoops_PPGIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP const *		_hoops_SRCP,
	_hoops_SPPIR const *	_hoops_CRGIC = null,
	Attribute const *	_hoops_ASGPR = null) {

	int		state = _hoops_PAGIC;
	bool	_hoops_HPGIC = false;
	bool	_hoops_IPGIC = false;

	if (_hoops_ASGPR == null)
		_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;

	if (_hoops_ASGPR != null) do {
		switch (_hoops_ASGPR->type) {
			case _hoops_CPPIR: {
				_hoops_SPPIR const *	conditions = (_hoops_SPPIR const *)_hoops_ASGPR;
				if (conditions->_hoops_ACPGR != null)
					state |= _hoops_IAGIC;
			}	break;

			case HK_STYLE: {
				Style const *		style = (Style const *)_hoops_ASGPR;

				if (!_hoops_GAGIC (style->condition, _hoops_CRGIC))
					state |= _hoops_HAGIC | _hoops_SAGIC | _hoops_APGIC;
				else if (style->_hoops_IGRPR == null)
					state |= _hoops_HAGIC | _hoops_SAGIC;
				else if (style->_hoops_IGRPR->_hoops_IPPGR && _hoops_IRGIC (style->condition, _hoops_CRGIC) == _hoops_CGGIC)
					state |= _hoops_PPGIC (_hoops_ARCAR, _hoops_SRCP, _hoops_CRGIC, style->_hoops_IGRPR->_hoops_IPPGR);
			}	break;

			case HK_VISIBILITY: {
				_hoops_RSAIR const *	vis = (_hoops_RSAIR const *)_hoops_ASGPR;
				_hoops_ACHR			flags = vis->mask & vis->value | ~vis->mask;
				_hoops_ACHR			_hoops_CPGIC = _hoops_SRCP->_hoops_RCGC & _hoops_IRHGP;

				if (BIT(_hoops_CPGIC, T_EDGES))
					_hoops_CPGIC |= T_ANY_EDGE;

				if (!ANYBIT(flags, _hoops_CPGIC))
					_hoops_HPGIC = true;
			}	break;

			case HK_CAMERA:
			case HK_CLIP_REGION: {
				state |= _hoops_HAGIC;
			}	break;

			case HK_WINDOW:
			case HK_DRIVER: {
				state |= _hoops_IAGIC;
			}	break;

			case HK_RENDERING_OPTIONS: {
				_hoops_RHAIR const *		_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_ASGPR;

				if (_hoops_AHAIR->_hoops_PGICA != _hoops_GCAAP)
					state |= _hoops_HAGIC;
				else if (_hoops_AHAIR->_hoops_HHAIR != null) {
					if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_ARICA) &&
						BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_RSSRP) &&
						_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.level == _hoops_GGGAP) {
						state |= _hoops_HAGIC;
					}
					else if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_PGGAP))
						state |= _hoops_HAGIC;
				}

				if (_hoops_AHAIR->locks != null) {
					/* _hoops_CCGR _hoops_SR _hoops_PAH _hoops_RARHR _hoops_GIH */
					_hoops_HHAGP	_hoops_SPGIC = _hoops_AHAIR->locks->normal.mask._hoops_IPPGR & _hoops_AHAIR->locks->normal.value._hoops_IPPGR;
					_hoops_ACHR		_hoops_GHGIC = _hoops_AHAIR->locks->normal.mask._hoops_RGP & _hoops_AHAIR->locks->normal.value._hoops_RGP;

					if (_hoops_SPGIC != 0)
						state |= _hoops_HAGIC | _hoops_RPGIC;

					if (BIT(_hoops_SPGIC, _hoops_GGCAA(HK_VISIBILITY)) &&
						!ANYBIT(~_hoops_GHGIC, _hoops_SRCP->_hoops_RCGC&_hoops_IRHGP))
						_hoops_IPGIC = true;
				}
			}	break;

			case HK_HEURISTICS: {
				_hoops_GHAIR const *		_hoops_GIGC = (_hoops_GHAIR const *)_hoops_ASGPR;

				if (ANYBIT (_hoops_GIGC->mask & _hoops_GIGC->value, _hoops_HPIRP) ||
					BIT (_hoops_GIGC->mask, _hoops_GPIRP))
					state |= _hoops_IAGIC;
			}	break;

			case HK_USER_OPTIONS:
			case HK_USER_VALUE: {
				if (BIT(_hoops_ARCAR->flags, _hoops_HGCHC))
					state |= _hoops_CAGIC;
			}	break;

			case HK_CALLBACK: {
				_hoops_GCHIR const *		_hoops_RCHIR = (_hoops_GCHIR const *)_hoops_ASGPR;
				_hoops_IHACR const *	_hoops_RCACR;

				if ((_hoops_RCACR = _hoops_RCHIR->_hoops_ACHIR) != null) do {
					switch (_hoops_RCACR->type) {
						case _hoops_APACR:
						case _hoops_SSRCR:
						case _hoops_CSRCR:
						case _hoops_HPACR: {
							state |= _hoops_IAGIC;
						}	break;
					}
				} while ((_hoops_RCACR = _hoops_RCACR->next) != null);
			}	break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	if (_hoops_HPGIC) {
		state |= _hoops_IAGIC|_hoops_GPGIC;
	}

	return state;
}

local int _hoops_RHGIC (
	Geometry const *		g,
	int						_hoops_RGPGR = ~0,
	int *					_hoops_AHGIC = 0,
	int *					_hoops_PHGIC = 0,
	bool					single = false) {
	int 					point_count = 0;
	int 					_hoops_HHGIC = 0;
	int 					_hoops_IHGIC = 0;

	while (g != null) {
		Type				type = g->type;

		if (!BIT (_hoops_RGPGR, _hoops_AGPGR(type))) {
			_hoops_IHGIC++;
			_hoops_PGPGR (g, g->type);
			if (single || g == null)
				goto _hoops_PRSPR;
		}
		else switch (type) {
			case _hoops_SCIP: {
				do {
					Shell *			_hoops_SPHPR = (Shell *)g;

					point_count += _hoops_SPHPR->point_count;
					_hoops_HHGIC++;
					if (single)
						goto _hoops_PRSPR;
				} while (((g = g->next) != null) && g->type == type);
			} break;

			case _hoops_GSIP: {
				do {
					_hoops_AIHPR *			_hoops_PIHPR = (_hoops_AIHPR *)g;

					point_count += _hoops_PIHPR->point_count;
					_hoops_HHGIC++;
					if (single)
						goto _hoops_PRSPR;
				} while (((g = g->next) != null) && g->type == type);
			} break;

			case _hoops_CSIP: {
				do {
					PolyCylinder *	_hoops_HARIR = (PolyCylinder *)g;

					point_count += _hoops_HARIR->point_count;
					_hoops_HHGIC++;
					if (single)
						goto _hoops_PRSPR;
				} while (((g = g->next) != null) && g->type == type);
			} break;

			case _hoops_AHIP: {
				do {
					_hoops_PHIP *	_hoops_RRA = (_hoops_PHIP *)g;

					if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
						_hoops_CRCP *		_hoops_SRCP = (_hoops_CRCP *)_hoops_RRA->_hoops_IHIP[0];
						int 			_hoops_CHGIC = 0;
						int 			_hoops_SHGIC = 0;

						point_count += _hoops_RHGIC (_hoops_SRCP->geometry, _hoops_RGPGR & _hoops_RRA->_hoops_RGPGR,
															&_hoops_CHGIC, &_hoops_SHGIC, false);

						_hoops_HHGIC += _hoops_CHGIC;
						_hoops_IHGIC += _hoops_SHGIC;
					}
					else {
						for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
							Geometry *		geo = (Geometry *)_hoops_RRA->_hoops_IHIP[i];
							int				_hoops_CHGIC = 0;
							int 			_hoops_SHGIC = 0;

							point_count += _hoops_RHGIC (geo, _hoops_RGPGR & _hoops_RRA->_hoops_RGPGR,
																&_hoops_CHGIC, &_hoops_SHGIC, true);

							_hoops_HHGIC += _hoops_CHGIC;
							_hoops_IHGIC += _hoops_SHGIC;
						}
					}
					if (single)
						goto _hoops_PRSPR;
				} while ((g = g->next) != null && g->type == type);
			} break;

			default: {
				do {
					_hoops_HHGIC++;
					if (single)
						goto _hoops_PRSPR;
				} while ((g = g->next) != null && g->type == type);
			} break;
		}
	}

_hoops_PRSPR:
	if (_hoops_AHGIC)
		*_hoops_AHGIC = _hoops_HHGIC;

	if (_hoops_PHGIC)
		*_hoops_PHGIC = _hoops_IHGIC;

	return point_count;
}


local int _hoops_GIGIC (
	_hoops_CRCP const *		_hoops_SRCP) {
	int					point_count = 0;

	if (_hoops_SRCP->type == _hoops_AGRPR) {
		_hoops_PGRPR *	include = (_hoops_PGRPR *)_hoops_SRCP;

		_hoops_SRCP = (_hoops_CRCP const *) (include->_hoops_IGRPR);
	}

	point_count += _hoops_RHGIC(_hoops_SRCP->geometry);

	Subsegment *		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;

	while (_hoops_GIPIA != null) {
 		point_count += _hoops_GIGIC((_hoops_CRCP *)_hoops_GIPIA);
		_hoops_GIPIA = _hoops_GIPIA->next;
	}

	return point_count;
}

local int _hoops_SAGGC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP const *		_hoops_SRCP,
	_hoops_SPPIR const *	_hoops_CRGIC = null) {
	int					result = _hoops_PPGIC (_hoops_ARCAR, _hoops_SRCP, _hoops_CRGIC);

	if (!BIT (result, _hoops_IAGIC)) {
		Xref const *	_hoops_HRCIR;
		int 			_hoops_IPPPI = 0;
		int 			_hoops_RIGIC = 0;

		if ((_hoops_HRCIR = _hoops_SRCP->_hoops_SGRPR()) != null) do {
			_hoops_SSAGR(_hoops_HRCIR->_hoops_GRRPR);
			if (_hoops_HRCIR->type == _hoops_AGRPR) {
				_hoops_IPPPI++;
				if (_hoops_IPPPI == 2) {
					_hoops_RIGIC = _hoops_GIGIC (_hoops_SRCP);
					if (_hoops_RIGIC < _hoops_ARCAR->_hoops_CSCHC)
						goto _hoops_PRSPR;
				}
			}
		} while ((_hoops_HRCIR = _hoops_HRCIR->_hoops_GRRPR) != null);

		if (_hoops_IPPPI > 1 &&
			_hoops_RIGIC*_hoops_IPPPI > _hoops_ARCAR->_hoops_ISCHC)
			result |= _hoops_IAGIC;
	}

_hoops_PRSPR:
 	return result;
}



local bool _hoops_AIGIC (
	Attribute *			_hoops_PIGIC,
	Attribute *			_hoops_GPCPA) {
	int					_hoops_HIGIC = 0;
	int					_hoops_IIGIC = 0;

	/* _hoops_HPCAR _hoops_RH _hoops_HRGI _hoops_RPP _hoops_SR _hoops_PIIC _hoops_HS _hoops_IRS _hoops_IAHA */
	if (_hoops_PIGIC != null && _hoops_PIGIC->type == HK_STYLE)
		return true;
	if (_hoops_GPCPA != null && _hoops_GPCPA->type == HK_STYLE)
		return true;

	/* _hoops_IRHH _hoops_PIP _hoops_IIGR _hoops_GII _hoops_SGHS */
	if (_hoops_PIGIC != null && _hoops_PIGIC->type == HK_RENDERING_OPTIONS) {
		_hoops_RHAIR const *		_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_PIGIC;
		if (_hoops_AHAIR->locks != null)
			_hoops_HIGIC |= _hoops_AHAIR->locks->normal.mask._hoops_IPPGR;
	}
	if (_hoops_GPCPA != null && _hoops_GPCPA->type == HK_RENDERING_OPTIONS) {
		_hoops_RHAIR const *		_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_GPCPA;
		if (_hoops_AHAIR->locks != null)
			_hoops_IIGIC |= _hoops_AHAIR->locks->normal.mask._hoops_IPPGR;
	}

	while (1) {
		/* _hoops_GCHGA _hoops_CPCI _hoops_IS _hoops_IRS _hoops_PIS _hoops_IGRI */
		while (_hoops_PIGIC != null && (_hoops_GPCPA == null || _hoops_PIGIC->type < _hoops_GPCPA->type)) {
			if (BIT (_hoops_IIGIC, 1UL << _hoops_PIGIC->type))
				return true;					/* _hoops_IGRI _hoops_ARI _hoops_SPIH _hoops_CCA _hoops_AAHS _hoops_CAPP */
			_hoops_PIGIC = _hoops_PIGIC->next;
		}
		while (_hoops_GPCPA != null && (_hoops_PIGIC == null || _hoops_GPCPA->type < _hoops_PIGIC->type)) {
			if (BIT (_hoops_HIGIC, 1UL << _hoops_GPCPA->type))
				return true;					/* _hoops_IGRI _hoops_ARI _hoops_SPIH _hoops_CCA _hoops_AAHS _hoops_ARRS */
			_hoops_GPCPA = _hoops_GPCPA->next;
		}

		/* _hoops_RPP _hoops_GIPR _hoops_CPCI _hoops_CPHR, _hoops_SR'_hoops_ASAR _hoops_RIRA */
		if (_hoops_PIGIC == null && _hoops_GPCPA == null)
			return false;
		/* _hoops_RPP _hoops_PGI _hoops_HIGR _hoops_RHPA _hoops_SR'_hoops_ASAR _hoops_CPHR, _hoops_HCCPR _hoops_RH _hoops_PIS _hoops_SGHS _hoops_GHCA _hoops_HAHA _hoops_RH _hoops_RII _hoops_HIGR */
		if (_hoops_PIGIC == null && _hoops_HIGIC == 0 ||
			_hoops_GPCPA == null && _hoops_IIGIC == 0)
			return false;

		/* _hoops_ISPR _hoops_IH _hoops_PPPSR _hoops_RAGS */
		if (_hoops_PIGIC != null && _hoops_GPCPA != null && _hoops_PIGIC->type == _hoops_GPCPA->type)
			return true;
	}

	return false;
}

local bool _hoops_CIGIC (
	Attribute *		_hoops_ASGPR) {

	if (_hoops_ASGPR != null) do {
		if (_hoops_ASGPR->type > _hoops_IAAA (HK_VISIBILITY, _hoops_IAAA (HK_WINDOW_PATTERN, HK_WINDOW_FRAME)))
			break;
		switch (_hoops_ASGPR->type) {
			case HK_VISIBILITY: {
				if (BIT (((_hoops_RSAIR const *)_hoops_ASGPR)->mask, T_WINDOWS))
					return true;
			}	break;

			case HK_WINDOW_PATTERN:
			case HK_WINDOW_FRAME:
				return true;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	return false;
}

local bool _hoops_SIGIC (
	_hoops_CRCP *		_hoops_SRCP) {
	Xref *			_hoops_AHICA;

	if ((_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR()) != null) do {
		if (_hoops_AHICA->type == HK_STYLE)
			return true;
	} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

	return false;
}

local _hoops_GHAIR * _hoops_GCGIC(
	_hoops_ICCHC *	_hoops_ARCAR,
	Attribute const *	_hoops_HPHCR)
{
	UNREFERENCED(_hoops_ARCAR);

	_hoops_GHAIR * h = null;

	while (_hoops_HPHCR != null) {
		if (_hoops_HPHCR->type > HK_HEURISTICS)
			break;

		if (_hoops_HPHCR->type == HK_HEURISTICS) {
			h = (_hoops_GHAIR *)_hoops_HPHCR;
			break;
		}

		_hoops_HPHCR = _hoops_HPHCR->next;
	}

	return h;
}

local _hoops_GHAIR * _hoops_RCGIC(
	_hoops_ICCHC *	_hoops_ARCAR,
	Attribute const *	_hoops_HPHCR)
{
	UNREFERENCED(_hoops_ARCAR);

	_hoops_GHAIR * h = _hoops_GCGIC(_hoops_ARCAR, _hoops_HPHCR);

	if (h != null &&
		BIT(h->mask, _hoops_APIRP) &&
		!ANYBIT(h->mask, ~(_hoops_APIRP|_hoops_CCIAA)))
		return h;

	return null;
}

local _hoops_SSGI * _hoops_ACGIC(
	_hoops_ICCHC *	_hoops_ARCAR,
	Attribute const *	_hoops_HPHCR)
{
	UNREFERENCED(_hoops_ARCAR);

	_hoops_SSGI * c = null;

	while (_hoops_HPHCR != null) {
		if (_hoops_HPHCR->type > HK_COLOR)
			break;

		if (_hoops_HPHCR->type == HK_COLOR) {
			c = (_hoops_SSGI *)_hoops_HPHCR;
			break;
		}

		_hoops_HPHCR = _hoops_HPHCR->next;
	}

	return c;
}

local void _hoops_PCGIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP,
	bool				_hoops_CPSHC,
	bool				_hoops_HCGIC)
{

	Subsegment *		_hoops_GIPIA;

#if 0
	if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 638087")) {
		_hoops_ARCAR=_hoops_ARCAR;
	}
#endif

	if (_hoops_SRCP->_hoops_RGRPR == null)
		return;

	if (!BIT(_hoops_SRCP->_hoops_PHSI, _hoops_GIPSA) &&
		!BIT(_hoops_PPGIC (_hoops_ARCAR, _hoops_SRCP), _hoops_RPGIC)) {
_hoops_ICGIC:
		bool 	_hoops_CCGIC = false;
		bool 	_hoops_SCGIC = false;
		bool 	_hoops_GSGIC = false;
		int 	_hoops_RSGIC = 0;
		int 	_hoops_ASGIC = 0;
		int 	_hoops_IPPPI = 0;

		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;
		while (_hoops_GIPIA != null) {
			if (_hoops_GIPIA->type == _hoops_IRCP) {
				_hoops_CRCP *		_hoops_SIIS = (_hoops_CRCP *)_hoops_GIPIA;

				++_hoops_ASGIC;

				if (_hoops_GIPIA->priority != 0)
					_hoops_SCGIC = true;

				if (_hoops_SIIS->_hoops_IPPGR != null)
					++_hoops_RSGIC;

				if (_hoops_SIIS->geometry != null)
					_hoops_GSGIC = true;
			}
			else
				_hoops_IPPPI++;

			_hoops_GIPIA = _hoops_GIPIA->next;
		}

		if (_hoops_ASGIC > 1 &&
			_hoops_RSGIC == _hoops_ASGIC &&
			!_hoops_SCGIC) //??? _hoops_HPIPR
			goto _hoops_PRSPR;

		//_hoops_PSGIC * _hoops_HSGIC = _hoops_ISGIC(_hoops_SAHHH, _hoops_PHHIP->_hoops_AIRC);

		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;
		while (_hoops_GIPIA != null) {
			if (_hoops_GIPIA->type != _hoops_IRCP) {
				_hoops_GIPIA = _hoops_GIPIA->next;
				continue;
			}

			Subsegment *	_hoops_CSGIC = _hoops_GIPIA->next;
			_hoops_CRCP *		_hoops_SIIS = (_hoops_CRCP *)_hoops_GIPIA;

			//_hoops_PSGIC * _hoops_SSGIC = _hoops_ISGIC(_hoops_SAHHH, _hoops_PHHIP->_hoops_AIRC);

			if (//!_hoops_IRRC (_hoops_GGRIC->_hoops_CPGC, _hoops_RGRIC) &&

				//_hoops_SSGIC == _hoops_IRAP &&

				(_hoops_SIIS->priority == 0 || _hoops_ASGIC == 1 || _hoops_SRCP->priority == 0) &&

				(!BIT (_hoops_SRCP->_hoops_RRHH, _hoops_CACHC) ||
				 !ANYBIT (_hoops_SIIS->_hoops_PHSI, _hoops_GGPSA|_hoops_CCHGP)) &&

				(!ANYBIT (_hoops_SIIS->_hoops_RRHH, _hoops_PACHC|_hoops_HACHC) ||
					(ANYBIT (_hoops_SRCP->_hoops_RRHH, _hoops_PACHC|_hoops_HACHC) &&
					 _hoops_ASGIC == 1 && _hoops_IPPPI == 0 &&
					 _hoops_SRCP->geometry == null &&
					 (_hoops_SRCP->_hoops_IPPGR == null ||
					  !_hoops_AIGIC (_hoops_SRCP->_hoops_IPPGR, _hoops_SIIS->_hoops_IPPGR)))) &&

				_hoops_SIIS->_hoops_SGRPR() == null &&
				!BIT(_hoops_SIIS->_hoops_RRHH, _hoops_IRPGI) &&

				(!BIT(_hoops_SRCP->_hoops_RRHH, _hoops_IRPGI) || _hoops_SIIS->geometry == null) &&

				!BIT (_hoops_SIIS->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR|_hoops_GIPSA|_hoops_PACAA) &&

				(
					_hoops_SIIS->_hoops_IPPGR == null ||
					_hoops_ASGIC == 1 &&
					_hoops_SRCP->geometry == null &&
					_hoops_IPPPI == 0 &&
					!_hoops_PPGIC (_hoops_ARCAR, _hoops_SIIS) &&
					!_hoops_AIGIC (_hoops_SRCP->_hoops_IPPGR, _hoops_SIIS->_hoops_IPPGR) &&
					(!BIT (_hoops_SRCP->_hoops_RRHH, _hoops_CACHC) && !_hoops_SIGIC(_hoops_SRCP) || _hoops_SIIS->_hoops_IPPGR == null) &&
					(!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) || !_hoops_CIGIC (_hoops_SIIS->_hoops_IPPGR))
				)
				) {
				Attribute **	_hoops_ASRGR = &_hoops_SRCP->_hoops_IPPGR;
				bool			_hoops_AGRIC = false;

				while (_hoops_SIIS->_hoops_IPPGR != null) {
					Attribute *	_hoops_ASGPR = _hoops_SIIS->_hoops_IPPGR;

					_hoops_SIIS->_hoops_IPPGR = _hoops_ASGPR->next;	/* _hoops_GA'_hoops_RA _hoops_RGIC _hoops_AHCA _hoops_GII _hoops_IPSIR, _hoops_GRS _hoops_CCIH _hoops_CGPR _hoops_SGS _hoops_SPR _hoops_IHCI */

					if (_hoops_ASGPR->type == HK_MODELLING_MATRIX)
						_hoops_AGRIC = true;

					while (*_hoops_ASRGR != null && _hoops_ASGPR->type >= (*_hoops_ASRGR)->type)
						_hoops_ASRGR = &(*_hoops_ASRGR)->next;

					if ((_hoops_ASGPR->next = *_hoops_ASRGR) != null)
						_hoops_ASGPR->next->backlink = &_hoops_ASGPR->next;
					*_hoops_ASRGR = _hoops_ASGPR;
					_hoops_ASGPR->backlink = _hoops_ASRGR;
					_hoops_ASRGR = &_hoops_ASGPR->next;

					_hoops_ASGPR->owner = _hoops_SRCP;
					if (_hoops_ASGPR->type == _hoops_IPAIR) {
						_hoops_CPAIR *		_hoops_SPAIR = (_hoops_CPAIR *)_hoops_ASGPR;
						int					i;

						for (i=0; i<_hoops_SPAIR->count; i++) {
							if (_hoops_SPAIR->textures[i]->owner == (_hoops_HPAH *)_hoops_SIIS)
								_hoops_SPAIR->textures[i]->owner = (_hoops_HPAH *)_hoops_SRCP;
						}
					}
				}

				if (_hoops_AGRIC &&
					(!BIT(_hoops_ARCAR->flags, _hoops_PRCHC) ||
					 !_hoops_CPSHC)) {

					_hoops_SRCP->bounding = _hoops_SIIS->bounding;
					_hoops_SIIS->bounding = null;

					_hoops_SRCP->_hoops_HSRIR = _hoops_SIIS->_hoops_HSRIR;
					_hoops_SIIS->_hoops_HSRIR = null;
				}

				if (_hoops_SIIS->geometry) {
					if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
						while (_hoops_SIIS->geometry != null)
							_hoops_GRAPA (_hoops_ARCAR, _hoops_SIIS->geometry, _hoops_SRCP, _hoops_CPSHC);
					}
					else {
						_hoops_SPSHC(_hoops_ARCAR, _hoops_SIIS, _hoops_SRCP);
						_hoops_SRCP->_hoops_RCGC |= _hoops_SIIS->_hoops_RCGC;
					}
				}

				if (_hoops_SRCP->priority == 0 && _hoops_SIIS->priority != 0) {
					_hoops_SRCP->priority = _hoops_SIIS->priority;
					_hoops_SRCP->owner->_hoops_PHSI |= _hoops_GGPSA | _hoops_CCHGP;
				}

				_hoops_SRCP->_hoops_PHSI |= _hoops_SIIS->_hoops_PHSI & (_hoops_GGPSA | _hoops_CCHGP);

				while ((_hoops_GIPIA = _hoops_SIIS->_hoops_RGRPR) != null) {
					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_GIPIA);
					_hoops_GIPIA->next = _hoops_SRCP->_hoops_RGRPR;
					_hoops_GIPIA->next->backlink = &_hoops_GIPIA->next;
					_hoops_GIPIA->backlink = &_hoops_SRCP->_hoops_RGRPR;
					_hoops_SRCP->_hoops_RGRPR = _hoops_GIPIA;
					_hoops_GIPIA->owner = _hoops_SRCP;
					_hoops_CCGIC = true;
				}

				_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_SIIS);
				HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_SIIS);
				_hoops_HPRH (_hoops_SIIS);
			}

			_hoops_GIPIA = _hoops_CSGIC;
		}

		if (_hoops_CCGIC)
			goto _hoops_ICGIC;
	}

_hoops_PRSPR:
	_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;
	if (_hoops_GIPIA != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP &&
			(_hoops_HCGIC || !BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_PACHC)))
			_hoops_PCGIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA, _hoops_CPSHC, _hoops_HCGIC);
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}


local void _hoops_PGRIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP) {
	Subsegment *		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;

	if (_hoops_GIPIA != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP) {
			_hoops_GIPIA->_hoops_RRHH &= ~(_hoops_IACHC);
			_hoops_PGRIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA);
		}
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}


GLOBAL_FUNCTION bool HI_Color_Is_Simple (
	_hoops_SSGI const *		color,
	_hoops_RHAH const *	_hoops_CSIR) {

	if (ANYBIT (color->_hoops_GHA,
		Color_WINDOW|Color_WINDOW_CONTRAST|Color_CUT_GEOMETRY|
		_hoops_IRARA|Color_LIGHTING|_hoops_SGARA))
		return false;

	if (BIT (color->_hoops_GHA, Color_FRONT) != BIT (color->_hoops_GHA, Color_BACK))
		return false;

	_hoops_ACSGA *		list = color->colors;
	int					_hoops_HGRIC = 0;

	while (list) {
		if (list->type == _hoops_SHGRA) {
			if (_hoops_CSIR == null)
				return false;

			// _hoops_ASIGA _hoops_IPRPI
			ASSERT (0);

			return false;
		}
		else if (list->type == _hoops_GIGRA) {
			return false;
		}
		_hoops_HGRIC |= list->_hoops_GHA;
		list = list->next;
	}
	if (_hoops_HGRIC != color->_hoops_GHA)
		return false;

	return true;
}





local void _hoops_IGRIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				node,
	Attribute const *		_hoops_PIGIC,
	Attribute const *		_hoops_GPCPA,
	_hoops_PIGRA *		locks = null,
	_hoops_SPPIR const *		_hoops_CRGIC = null) {
	Attribute **			_hoops_ASRGR = &node->_hoops_IPPGR;
	bool					_hoops_CGRIC = false;
	_hoops_CRCP const *			_hoops_RPSHC[3];
	_hoops_CRCP const *			_hoops_SGRIC[2];
	int						type;
	int						count=0;
	_hoops_PIGRA			_hoops_GRRIC;

	if (locks == null) {
		locks = &_hoops_GRRIC;
		ZERO_STRUCT(locks, _hoops_PIGRA);
	}

	_hoops_CRACA control;
	ZERO_STRUCT (&control, _hoops_CRACA);
	control.locks = locks;
	if (_hoops_CRGIC != null)
		control.conditions = _hoops_CRGIC->values;

	_hoops_RPSHC[count++] = null;	/* _hoops_IASI _hoops_AAHRP */
	if (_hoops_PIGIC != null)
		_hoops_RPSHC[count++] = _hoops_PIGIC->owner;
	if (_hoops_GPCPA != null)
		_hoops_RPSHC[count++] = _hoops_GPCPA->owner;

	if (_hoops_PIGIC != null && _hoops_PIGIC->type == HK_STYLE ||
		_hoops_GPCPA != null && _hoops_GPCPA->type == HK_STYLE)
		_hoops_CGRIC = true;

	if (_hoops_GPCPA != null) {
		_hoops_SGRIC[0] = null;
		_hoops_SGRIC[1] = _hoops_GPCPA->owner;
	}

	// _hoops_ASIGA _hoops_RPP (_hoops_IAHA->_hoops_HPAC._hoops_RPR > 0)

	/* _hoops_HAPR _hoops_RHAP _hoops_HAR _hoops_GCIS _hoops_PCIAA _hoops_PAR _hoops_RRRIC */
	for (type = _hoops_RAAGP; type < _hoops_CRCCA; type++) {
		Attribute *		_hoops_ASGPR = null;

		if (_hoops_CGRIC) {
			if (type != HK_USER_VALUE)
				_hoops_ASGPR = HI_Find_Net_Attribute_By_Path (_hoops_ARCAR->_hoops_RIGC, count, (_hoops_CRCP const **)_hoops_RPSHC, type, _hoops_PSCAP, &control);
		}
		else {
			while (_hoops_PIGIC != null && _hoops_PIGIC->type < type)
				_hoops_PIGIC = _hoops_PIGIC->next;
			while (_hoops_GPCPA != null && _hoops_GPCPA->type < type)
				_hoops_GPCPA = _hoops_GPCPA->next;

			if (_hoops_PIGIC != null && _hoops_PIGIC->type == type &&		/* _hoops_RRP _hoops_IS _hoops_HASC */
				_hoops_GPCPA != null && _hoops_GPCPA->type == type) {
				if (type != HK_USER_VALUE)
					_hoops_ASGPR = HI_Find_Net_Attribute_By_Path (_hoops_ARCAR->_hoops_RIGC, count, (_hoops_CRCP const **)_hoops_RPSHC, type, _hoops_PSCAP, &control);
			}
			else if (_hoops_PIGIC != null && _hoops_PIGIC->type == type) {
				_hoops_ASGPR = (Attribute *)_hoops_PIGIC;
				_hoops_PRRH (_hoops_ASGPR);
			}
			else if (_hoops_GPCPA != null && _hoops_GPCPA->type == type) {
				_hoops_ASGPR = HI_Find_Net_Attribute_By_Path (_hoops_ARCAR->_hoops_RIGC, 2, (_hoops_CRCP const **)_hoops_SGRIC, type, _hoops_PSCAP, &control);
			}
		}

		if (_hoops_ASGPR != null) {
			if (_hoops_ASGPR->_hoops_HIHI > 1) {		/* _hoops_CGRPR _hoops_IS _hoops_CPHP, _hoops_IRHH _hoops_IRS _hoops_IPS */
				_hoops_HPRH (_hoops_ASGPR);	/* _hoops_GRAA-_hoops_AHHR */
				_hoops_ASGPR = HI_Clone_Attributes (_hoops_ARCAR->_hoops_RIGC, _hoops_ASGPR, node, false, null);
			}

			switch (_hoops_ASGPR->type) {
				case _hoops_CPPIR: {
					_hoops_SPPIR *	_hoops_GHPIR = (_hoops_SPPIR*)_hoops_ASGPR;

					if (BIT(_hoops_ARCAR->flags, _hoops_PRCHC) &&
						!BIT(node->_hoops_RCGC, _hoops_CPHGP) ||
						_hoops_GHPIR->count == 0 &&
						_hoops_GHPIR->_hoops_ACPGR == null) {
						ASSERT(_hoops_GHPIR->_hoops_ACPGR == null);
						_hoops_HPRH (_hoops_ASGPR);
						_hoops_ASGPR = null;
					}
				}	break;

				case HK_USER_OPTIONS: {
					bool	_hoops_SGII = BIT(_hoops_ARCAR->flags, _hoops_HGCHC);

					/* _hoops_RGAR _hoops_GRHP _hoops_ARRIC _hoops_HSH _hoops_IH _hoops_ASGC */
					if (!_hoops_SGII &&
						(BIT(_hoops_ARCAR->flags, _hoops_IRCHC) ||
						 BIT(_hoops_ARCAR->flags, _hoops_PRCHC) && BIT(node->_hoops_RCGC, _hoops_AHHGP))) {
						_hoops_HPPIR *	_hoops_IPPIR = (_hoops_HPPIR*)_hoops_ASGPR;

						if (_hoops_IPPIR->_hoops_IGGSA && _hoops_IPPIR->_hoops_IGGSA->Count() > 0) {
							int count = _hoops_IPPIR->_hoops_IGGSA->Count();

							_hoops_CGGSA::UniqueCursor *	uc = _hoops_IPPIR->_hoops_IGGSA->GetUniqueCursor();
							while (count--) {
								_hoops_HPPIR const *			_hoops_HGSGP = uc->Peek();
								ASSERT(_hoops_HGSGP->_hoops_IGGSA == null);

								if (_hoops_HGSGP->_hoops_AGGSA && _hoops_HGSGP->_hoops_AGGSA->Count() > 0 ||
									_hoops_HGSGP->_hoops_IGGSA && _hoops_HGSGP->_hoops_IGGSA->Count() > 0) {
									_hoops_SGII = true;
									if (_hoops_HGSGP->option_list) {
										HI_Free_Option_List (_hoops_ARCAR->_hoops_RIGC, _hoops_HGSGP->option_list);
										_hoops_PGRCA(_hoops_HGSGP)->option_list = null;
									}
									if (_hoops_HGSGP->_hoops_APICA) {
										HI_Free_Option_List (_hoops_ARCAR->_hoops_RIGC, _hoops_HGSGP->_hoops_APICA);
										_hoops_PGRCA(_hoops_HGSGP)->_hoops_APICA = null;
									}
									//_hoops_RPP (_hoops_PRRIC->_hoops_HRRIC) { _hoops_SIGP
									//	_hoops_PRRIC->_hoops_HRRIC->_hoops_IRRIC(_hoops_CRRIC);
									//	_hoops_HSCI _hoops_PRRIC->_hoops_HRRIC;
									//}
									uc->Advance();
								}
								else {
									uc->RemoveAt();
									_hoops_HPRH(_hoops_HGSGP);
								}
							}
							delete uc;
						}
					}

					if (!_hoops_SGII) {
						/* _hoops_HGIRR'_hoops_RA _hoops_HS _hoops_PA _hoops_RAAP _hoops_HPGR _hoops_HCR */
						_hoops_HPRH (_hoops_ASGPR);
						_hoops_ASGPR = null;
					}
				}	break;

				case HK_MODELLING_MATRIX: {
					if (((_hoops_ISGI const *)_hoops_ASGPR)->matrix._hoops_RAGR == _hoops_SGICR) {
						/* _hoops_PSP _hoops_RRP _hoops_IS _hoops_GRHP & _hoops_HPPP _hoops_PCCP _hoops_SRGH _hoops_RSGA */
						_hoops_HPRH (_hoops_ASGPR);
						_hoops_ASGPR = null;
					}
				}	break;

				case HK_SELECTABILITY: {
					if (BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
						/* _hoops_PSP _hoops_RRP _hoops_IS _hoops_GRHP & _hoops_HPPP _hoops_GHSHA _hoops_IPPAR */
						_hoops_HPRH (_hoops_ASGPR);
						_hoops_ASGPR = null;
					}
				}	break;

				case HK_RENDERING_OPTIONS: {
					_hoops_RHAIR const *		_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_ASGPR;

					if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_HRRAP))
						HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, node, _hoops_ASPCR);

					if (_hoops_AHAIR->_hoops_HHAIR != null) {
						if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_PGGAP))
							node->_hoops_PHSI |= _hoops_PACAA;

						if (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR.text != null &&
							(_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR.text[0] == '.' ||
							 _hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR.text[0] == '^')) {

							_hoops_HCRPR		name;
							_hoops_CRCP *	_hoops_SRCP;
							char		pathname[4096];

							HI_Canonize_Chars_Quoted (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR.text, &name, false);
							HI_Open_Segment(_hoops_ARCAR->_hoops_RIGC, _hoops_GPCPA->owner);
								_hoops_SRCP = HI_One_Segment_Search(_hoops_ARCAR->_hoops_RIGC, name.text, false);
							HI_Close_Segment(_hoops_ARCAR->_hoops_RIGC);
							_hoops_RGAIR(name);

							if (_hoops_SRCP != null) {
								_hoops_RAIGI (_hoops_ARCAR->_hoops_RIGC, pathname, "%p", (void *)_hoops_SRCP);
								_hoops_RGAIR(_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR);
								HI_Copy_Chars_To_Name(pathname, &_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR);
							}
						}
					}
				}	break;

				case HK_WINDOW_PATTERN: {
					_hoops_CHCAP const *	_hoops_SRRIC = (_hoops_CHCAP const *)_hoops_ASGPR;

					if (_hoops_SRRIC->value == FP_WINDOW_TRANSPARENT ||
						_hoops_SRRIC->value == FP_WINDOW_TRANS_NO_ZCLEAR)
						node->_hoops_PHSI |= _hoops_RCHGP;
				}	break;

				case HK_WINDOW: {
					node->_hoops_PHSI |= _hoops_SHSIR;
					HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, node->owner, T_WINDOWS);
				}	break;

				case HK_CAMERA: {
					HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, node, _hoops_PSPCR);
				}	break;

				case HK_VISIBILITY: {
					_hoops_RSAIR const *	vis = (_hoops_RSAIR const *)_hoops_ASGPR;
					_hoops_ACHR			_hoops_RCGC = 0;

					if (ANYBIT (vis->value, _hoops_AAHGP) ||
						(ANYBIT (vis->value, T_CUT_GEOMETRY) &&
						 ANYBIT (vis->_hoops_PRIGA.value, T_FACES|T_LINES)))
						_hoops_RCGC |= _hoops_APHGP;

					if (BIT (vis->value, T_WINDOWS))
						_hoops_RCGC |= _hoops_HPHGP;

					if (!ALLBITS (node->_hoops_RCGC, _hoops_RCGC))
						HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, node, _hoops_RCGC);
				}	break;
			}

			if (_hoops_ASGPR != null) {
				_hoops_ASGPR->_hoops_CPGPR |= _hoops_CASIR;
				_hoops_ASGPR->owner = node;			/* _hoops_IRHH _hoops_RCRR */
				if ((_hoops_ASGPR->next = *_hoops_ASRGR) != null)
					_hoops_ASGPR->next->backlink = &_hoops_ASGPR->next;
				_hoops_ASGPR->backlink = _hoops_ASRGR;
				*_hoops_ASRGR = _hoops_ASGPR;
				_hoops_ASRGR = &_hoops_ASGPR->next;
			}
		}
	}
}



local void _hoops_GARIC(_hoops_ICCHC * _hoops_ARCAR, _hoops_CRCP * _hoops_SRCP, bool _hoops_RARIC);

local void _hoops_AARIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP,
	Attribute *			_hoops_PARIC,
	_hoops_CRCP *			root) {
	Subsegment *		_hoops_GIPIA;
	Subsegment *		_hoops_HARIC;
	bool				_hoops_IARIC = false;
	_hoops_CHCHC *	_hoops_CARIC = null;

top:
	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {
		Attribute *	_hoops_ASGPR;

		if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) do {
			if (_hoops_ASGPR->type == _hoops_GRAIR) {
				_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_ASGPR);
				HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_ASGPR);
				_hoops_HPRH (_hoops_ASGPR);
				break;
			}
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

		_hoops_SRCP->_hoops_PHSI &= ~_hoops_PRSIR;
		_hoops_IARIC = true;
	}

	if (_hoops_SRCP == root)
		_hoops_SRCP->_hoops_RRHH |= _hoops_PACHC; /* _hoops_RCSAR '_hoops_SRRPR' _hoops_GRS _hoops_SHH _hoops_SARIC */
	else {
		bool			_hoops_GPRIC = false;

		/* _hoops_PAH'_hoops_RA _hoops_ASRS _hoops_CIPH _hoops_PII _hoops_HGHIP _hoops_CRGR _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_HIRA.
		   _hoops_RPP _hoops_PRCHR, _hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_HASC _hoops_GGR _hoops_GCIAA _hoops_AIRC _hoops_CR _hoops_SGS _hoops_CHH _hoops_GPGSA _hoops_GH
			_hoops_SGH _hoops_GAR _hoops_IRS _hoops_IAHA _hoops_PAR _hoops_GGCR _hoops_RPRIC _hoops_AIRC _hoops_IH _hoops_PCCP _hoops_PPCPI, _hoops_HIS _hoops_SHSP _hoops_SCH
			_hoops_ARI _hoops_CAS _hoops_SCH _hoops_GRS _hoops_CAPGP _hoops_GGR _hoops_RH _hoops_GSSR _hoops_CRAA _hoops_HAH.  _hoops_PS _hoops_PAH, _hoops_HGRRA, _hoops_HPPR _hoops_IS
			_hoops_SGGC _hoops_GIAA _hoops_RGR _hoops_CAGH
		*/
		if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR|_hoops_GIPSA|_hoops_PACAA|_hoops_GGPSA) ||
			_hoops_SRCP->priority != 0 || _hoops_SRCP->_hoops_SGRPR() != null || BIT(_hoops_SRCP->_hoops_RRHH, _hoops_IRPGI)) {
			_hoops_GPRIC = true;
		}
		else {
			int		_hoops_PIHRC = _hoops_SAGGC (_hoops_ARCAR, _hoops_SRCP);
			_hoops_GPRIC = ANYBIT(_hoops_PIHRC, ~(_hoops_IAGIC|_hoops_APGIC));
		}

		if (_hoops_GPRIC) {
			/* _hoops_GACC _hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_HASC _hoops_GGR _hoops_GCIAA _hoops_AIRC _hoops_CR _hoops_SGS _hoops_CHH _hoops_GPGSA _hoops_GH
				_hoops_SGH _hoops_GAR _hoops_IRS _hoops_IAHA _hoops_PAR _hoops_GGCR _hoops_RPRIC _hoops_AIRC _hoops_IH _hoops_PCCP _hoops_PPCPI, _hoops_HIS _hoops_SHSP _hoops_SCH
				_hoops_ARI _hoops_CAS _hoops_SCH _hoops_GRS _hoops_CAPGP _hoops_GGR _hoops_RH _hoops_GSSR _hoops_CRAA _hoops_HAH.  _hoops_PS _hoops_PAH, _hoops_HGRRA, _hoops_HPPR _hoops_IS
				_hoops_SGGC _hoops_GIAA _hoops_RGR _hoops_CAGH
			*/
			_hoops_GARIC (_hoops_ARCAR, _hoops_SRCP, true);
			goto _hoops_APRIC;
		}

		if (_hoops_SRCP->owner != root) {
			_hoops_CRCP *		_hoops_SRCII = _hoops_SRCP->owner;
			_hoops_CRCP *		newowner = root;

			if (_hoops_SRCP->_hoops_IPPGR != null) {
				_hoops_CRCP					_hoops_PPRIC;
				/* _hoops_PPSI _hoops_RHGS _hoops_IRGH _hoops_AIRC _hoops_GPP _hoops_IRS _hoops_SPCS _hoops_IH _hoops_RH _hoops_AAHRP */
				_hoops_PPRIC.type = _hoops_IRCP;
				_hoops_PPRIC._hoops_IPPGR = _hoops_SRCP->_hoops_IPPGR;
				_hoops_PPRIC._hoops_IPPGR->backlink = &_hoops_PPRIC._hoops_IPPGR;
				_hoops_PPRIC._hoops_IPPGR->owner = &_hoops_PPRIC;

				_hoops_SRCP->_hoops_IPPGR = null;

				_hoops_IGRIC (_hoops_ARCAR, _hoops_SRCP, _hoops_PARIC, _hoops_PPRIC._hoops_IPPGR);

				/* _hoops_CASI _hoops_GGSR _hoops_RH _hoops_RHGS _hoops_IRGH _hoops_AIRC */
				while (_hoops_PPRIC._hoops_IPPGR != null) {
					Attribute *		_hoops_ASGPR = _hoops_PPRIC._hoops_IPPGR;
					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_ASGPR);
					HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_ASGPR);
					_hoops_HPRH (_hoops_ASGPR);
				}
			}
			else if (_hoops_PARIC != null)
				_hoops_IGRIC (_hoops_ARCAR, _hoops_SRCP, _hoops_PARIC, null);

/* _hoops_CGH _hoops_HASC _hoops_CCA _hoops_PCCP _hoops_APRS _hoops_CAGH _hoops_RPP _hoops_AIRC _hoops_RH _hoops_PSHR? */

			/* _hoops_IHIS _hoops_CRGR _hoops_SCIA */
			_hoops_RRSHC (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCP);
			_hoops_RGAIR (_hoops_SRCP->name);
			_hoops_RAGSA (_hoops_ARCAR, _hoops_SRCP, _hoops_SRCII, newowner);

			_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_SRCP);

			_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_SRCP, root);

			_hoops_SRCP->owner = root;
		}
	}

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_HARIC = _hoops_GIPIA->next;

		if (_hoops_GIPIA->type == _hoops_IRCP) {
			if (_hoops_IARIC || _hoops_GIPIA->next == null) {
				if (!_hoops_IARIC) {
					_hoops_CHCHC *	_hoops_CCGIC;

					POOL_ZALLOC (_hoops_CCGIC, _hoops_CHCHC, _hoops_ARCAR->memory_pool);
					_hoops_CCGIC->segment = _hoops_SRCP;
					_hoops_CCGIC->next = _hoops_CARIC;
					_hoops_CARIC = _hoops_CCGIC;
				}

				_hoops_PARIC = _hoops_SRCP->_hoops_IPPGR;
				_hoops_SRCP = (_hoops_CRCP *)_hoops_GIPIA;
				goto top;
			}
			else
				_hoops_AARIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA, _hoops_SRCP->_hoops_IPPGR, root);
		}
	} while ((_hoops_GIPIA = _hoops_HARIC) != null);

  _hoops_APRIC:;
	do {
		if (_hoops_SRCP != root && _hoops_SRCP->geometry == null && _hoops_SRCP->_hoops_RGRPR == null) {
			int						_hoops_RHICA = 0;
			Xref *					_hoops_AHICA;

			if ((_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR()) != null) do {
				if (_hoops_AHICA->type == HK_STYLE)
					++_hoops_RHICA;
			} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

			if (BIT(_hoops_ARCAR->flags, _hoops_HGCHC) && _hoops_SRCP->_hoops_IPPGR != null) {
				Attribute const *	_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR;

				do {
					if (_hoops_HPHCR->type == HK_USER_OPTIONS || _hoops_HPHCR->type == HK_USER_VALUE) {
						++_hoops_RHICA;
						break;
					}
				} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
			}

			if (_hoops_SRCP->_hoops_IPPGR == null || _hoops_RHICA == 0) {
				_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_SRCP);
				HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP);
				_hoops_HPRH (_hoops_SRCP);
			}
		}

		if (_hoops_CARIC != null) {
			_hoops_CHCHC *		_hoops_CCGIC = _hoops_CARIC;

			_hoops_SRCP = (_hoops_CRCP alter *)_hoops_CCGIC->segment;

			_hoops_CARIC = _hoops_CCGIC->next;
			FREE (_hoops_CCGIC, _hoops_CHCHC);
		}
		else
			_hoops_SRCP = null;
	} while (_hoops_SRCP != null);
}

local void _hoops_HPRIC (
	_hoops_CRCP *		root) {
	Subsegment *	_hoops_GIPIA;
	Geometry *		geometry;

	root->_hoops_RCGC &= ~(_hoops_AAHGP & _hoops_IRHGP);

	Bounding		_hoops_IPRIC;
	Type			_hoops_CPRIC = -1;
	bool			_hoops_SPRIC = HI_Bounding_Is_Excluded(root->_hoops_IPPGR);

	if ((geometry = root->geometry) != null) do {
		Bounding	_hoops_SCIIA;

		if (!_hoops_SPRIC && HI_Figure_Geometry_Bounding (geometry, _hoops_SCIIA))
			_hoops_IPRIC.Merge (_hoops_SCIIA);

		if (geometry->type != _hoops_CPRIC) {
			if (geometry->type != _hoops_AHIP)
				_hoops_CPRIC = geometry->type;

			root->_hoops_RCGC |= HI_Determine_Geometry_Maybes (geometry);
		}

		geometry = geometry->next;
	} while (geometry != null);

	root->_hoops_HSRIR = _hoops_IPRIC;
	root->bounding = null;

	if ((_hoops_GIPIA = root->_hoops_RGRPR) != null) do {
		_hoops_CRCP *	_hoops_SRCP = null;

		if (_hoops_GIPIA->type == _hoops_IRCP) {
			_hoops_SRCP = (_hoops_CRCP *)_hoops_GIPIA;
			_hoops_HPRIC (_hoops_SRCP);
		}
		else {
			_hoops_PGRPR *	include = (_hoops_PGRPR *)_hoops_GIPIA;
			_hoops_SRCP = (_hoops_CRCP alter *)include->_hoops_IGRPR;
		}

		ASSERT(_hoops_SRCP != null);

		root->_hoops_RCGC |= _hoops_SRCP->_hoops_RCGC;

		if (!_hoops_SPRIC && !_hoops_SRCP->bounding._hoops_HICAR()) {
			Bounding _hoops_SHCPH = _hoops_SRCP->bounding;
			Attribute *	_hoops_PSACR = null;

			HI_Gather_Modelling (_hoops_SRCP->_hoops_IPPGR, &_hoops_PSACR);

			if (_hoops_PSACR != null) {
				_hoops_SHCPH = _hoops_SHCPH._hoops_SCIS (&((_hoops_ISGI *)_hoops_PSACR)->matrix.elements[0][0]);
				_hoops_HPRH (_hoops_PSACR);
			}

			root->bounding.Merge(_hoops_SHCPH);
		}
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	if (!_hoops_SPRIC)
		root->bounding.Merge(root->_hoops_HSRIR);

	_hoops_GIPIA = root->_hoops_RGRPR;

	// _hoops_GHRIC _hoops_GII _hoops_GIGR _hoops_SPSHI _hoops_SGS _hoops_RRP _hoops_IS _hoops_SHH _hoops_RHRIC _hoops_ARPP _hoops_RH _hoops_RHAR _hoops_SPSHI
	if (_hoops_GIPIA != null && _hoops_GIPIA->priority < 0 && _hoops_GIPIA != root->_hoops_RGRPR) {
		Subsegment *	_hoops_HHIHR = _hoops_GIPIA;
		while (_hoops_HHIHR->next != null && _hoops_HHIHR->next->priority < 0)
			_hoops_HHIHR = _hoops_HHIHR->next;
		// _hoops_IHIS _hoops_HIGR _hoops_HII '_hoops_SGHC' _hoops_RHIR '_hoops_SPSHI' _hoops_IS _hoops_RIPS _hoops_IIGR _hoops_SRRPR->_hoops_CHAPA
		if ((*_hoops_GIPIA->backlink = _hoops_HHIHR->next) != null)
			_hoops_HHIHR->next->backlink = _hoops_GIPIA->backlink;

		_hoops_HHIHR->next = root->_hoops_RGRPR;
		_hoops_HHIHR->next->backlink = &_hoops_HHIHR->next;
		_hoops_GIPIA->backlink = &root->_hoops_RGRPR;
		root->_hoops_RGRPR = _hoops_GIPIA;
	}
}



local bool _hoops_AHRIC (
	_hoops_SSGI const *		_hoops_PHRIC,
	_hoops_SSGI const *		_hoops_HHRIC) {
	_hoops_ACSGA const *	first = _hoops_PHRIC->colors;

	if (_hoops_PHRIC->_hoops_GHA != _hoops_HHRIC->_hoops_GHA)
		return false;

	do {
		_hoops_ACSGA const *	_hoops_IAGRA = _hoops_HHRIC->colors;

		do if (first->_hoops_GHA == _hoops_IAGRA->_hoops_GHA) {
			if (first->type != _hoops_IAGRA->type)
				return false;

			switch (first->type) {
				case _hoops_SHGRA: {
					_hoops_PCSGA const *		_hoops_IHRIC= (_hoops_PCSGA const *)first;
					_hoops_PCSGA const *		_hoops_CHRIC = (_hoops_PCSGA const *)_hoops_IAGRA;

					if (_hoops_IHRIC->value != _hoops_CHRIC->value)
						return false;
				}	break;

				case _hoops_PPCA: {
					_hoops_APCA const *		_hoops_CAGRA = (_hoops_APCA const *)first;
					_hoops_APCA const *		_hoops_SAGRA = (_hoops_APCA const *)_hoops_IAGRA;

					if (_hoops_CAGRA->rgb.red != _hoops_SAGRA->rgb.red ||
						_hoops_CAGRA->rgb.green != _hoops_SAGRA->rgb.green ||
						_hoops_CAGRA->rgb.blue != _hoops_SAGRA->rgb.blue)
						return false;
				}	break;

				case _hoops_GIGRA: {
					_hoops_HCSGA const *		_hoops_SHRIC = (_hoops_HCSGA const *)first;
					_hoops_HCSGA const *		_hoops_GIRIC = (_hoops_HCSGA const *)_hoops_IAGRA;

					if (!HI_Named_Materials_Equal (&_hoops_SHRIC->_hoops_ISHIR, &_hoops_GIRIC->_hoops_ISHIR))
						return false;
				}	break;
			}
			break;	/* _hoops_RGR _hoops_SPR _hoops_CSAP _hoops_IHRI, _hoops_SAS _hoops_CCA _hoops_CRIPR _hoops_HAPR */
		} while ((_hoops_IAGRA = _hoops_IAGRA->next) != null);

		if (_hoops_IAGRA == null)	/* _hoops_RPP _hoops_PSP _hoops_HIGR _hoops_RARP _hoops_SPASR _hoops_RH _hoops_AGSAR */
			return false;
   } while ((first = first->next) != null);

   return true;
}

local bool _hoops_RIRIC (
	_hoops_RHAIR const *	a,
	_hoops_RHAIR const *	b) {

	// _hoops_IIAP _hoops_RAICR _hoops_ARPP _hoops_RGR _hoops_HRGR _hoops_PIGS

	if (a->_hoops_RRRAP != 0) {
		if (BIT (a->_hoops_RRRAP, _hoops_PRRAP)) {
			if (a->_hoops_IRARR != b->_hoops_IRARR)
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_CRRAP)) {
			if (a->_hoops_CHIH != b->_hoops_CHIH)
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_IPRAP)) {
			if (a->_hoops_IGAAP != b->_hoops_IGAAP)
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_SARAP)) {
			if (a->_hoops_SHIH != b->_hoops_SHIH)
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_GPRAP)) {
			if (a->_hoops_GSAAP != b->_hoops_GSAAP)
				return false;
			if (a->_hoops_RSAAP != b->_hoops_RSAAP)
				return false;
		}
		if (a->_hoops_HHAIR != null) {
			if (b->_hoops_HHAIR == null)
				return false;

			if (BIT (a->_hoops_RRRAP, _hoops_IARAP)) {
				if (a->_hoops_HHAIR->_hoops_ACSRP != b->_hoops_HHAIR->_hoops_ACSRP)
					return false;
			}
			if (BIT (a->_hoops_RRRAP, _hoops_RPRAP)) {
				if (a->_hoops_HHAIR->_hoops_PCSRP != b->_hoops_HHAIR->_hoops_PCSRP)
					return false;
			}
			if (BIT (a->_hoops_RRRAP, _hoops_PPRAP)) {
				if (a->_hoops_HHAIR->_hoops_HRGA != b->_hoops_HHAIR->_hoops_HRGA)
					return false;
			}
			if (BIT (a->_hoops_RRRAP, _hoops_HPH)) {
				if (a->_hoops_HHAIR->_hoops_CRIR.hither != b->_hoops_HHAIR->_hoops_CRIR.hither || a->_hoops_HHAIR->_hoops_CRIR.yon != b->_hoops_HHAIR->_hoops_CRIR.yon)
					return false;
			}
			if (BIT (a->_hoops_RSIAA, _hoops_ARICA)) {
				if (a->_hoops_HHAIR->_hoops_PRIGA.mask != b->_hoops_HHAIR->_hoops_PRIGA.mask ||
					a->_hoops_HHAIR->_hoops_PRIGA.value != b->_hoops_HHAIR->_hoops_PRIGA.value)
					return false;

				if (BIT (a->_hoops_HHAIR->_hoops_PRIGA.value, _hoops_RSSRP)) {
					if (a->_hoops_HHAIR->_hoops_PRIGA.level != b->_hoops_HHAIR->_hoops_PRIGA.level)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_PRIGA.value, _hoops_PSSRP)) {
					if (a->_hoops_HHAIR->_hoops_PRIGA.tolerance != b->_hoops_HHAIR->_hoops_PRIGA.tolerance)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_PRIGA.value, _hoops_HSSRP)) {
					if (a->_hoops_HHAIR->_hoops_PRIGA._hoops_SRIGA != b->_hoops_HHAIR->_hoops_PRIGA._hoops_SRIGA)
						return false;
				}
			}
			if (BIT (a->_hoops_RSIAA, _hoops_RRICA)) {
				if (a->_hoops_HHAIR->_hoops_GHSS.mask != b->_hoops_HHAIR->_hoops_GHSS.mask ||
					a->_hoops_HHAIR->_hoops_GHSS.value != b->_hoops_HHAIR->_hoops_GHSS.value)
					return false;

				if (BIT (a->_hoops_HHAIR->_hoops_GHSS.value, _hoops_IGGAP)) {
					if (a->_hoops_HHAIR->_hoops_GHSS.plane != b->_hoops_HHAIR->_hoops_GHSS.plane)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_GHSS.value, _hoops_CGGAP)) {
					if (a->_hoops_HHAIR->_hoops_GHSS.light != b->_hoops_HHAIR->_hoops_GHSS.light)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_GHSS.value, _hoops_SGGAP)) {
					if (a->_hoops_HHAIR->_hoops_GHSS.color.rgb != b->_hoops_HHAIR->_hoops_GHSS.color.rgb)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_GHSS.value, _hoops_GRGAP)) {
					if (a->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR != b->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_GHSS.value, _hoops_RRGAP)) {
					if (a->_hoops_HHAIR->_hoops_GHSS._hoops_HAP != b->_hoops_HHAIR->_hoops_GHSS._hoops_HAP)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_GHSS.value, _hoops_ARGAP)) {
					if (a->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR != b->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR)
						return false;
				}
			}
			if (BIT (a->_hoops_RSIAA, _hoops_CSGAP)) {
				if (a->_hoops_HHAIR->_hoops_HRR.mask != b->_hoops_HHAIR->_hoops_HRR.mask ||
					a->_hoops_HHAIR->_hoops_HRR.value != b->_hoops_HHAIR->_hoops_HRR.value)
					return false;

				if (BIT (a->_hoops_HHAIR->_hoops_HRR.value, _hoops_PAGAP)) {
					if (a->_hoops_HHAIR->_hoops_HRR._hoops_HAP != b->_hoops_HHAIR->_hoops_HRR._hoops_HAP)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_HRR.value, _hoops_HAGAP)) {
					if (a->_hoops_HHAIR->_hoops_HRR._hoops_CAP != b->_hoops_HHAIR->_hoops_HRR._hoops_CAP)
						return false;
				}
			}
			if (BIT (a->_hoops_RSIAA, _hoops_SSGAP)) {
				if (a->_hoops_HHAIR->_hoops_RHGGR.mask != b->_hoops_HHAIR->_hoops_RHGGR.mask ||
					a->_hoops_HHAIR->_hoops_RHGGR.value != b->_hoops_HHAIR->_hoops_RHGGR.value)
					return false;

				if (BIT (a->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_GPGAP)) {
					if (a->_hoops_HHAIR->_hoops_RHGGR.plane != b->_hoops_HHAIR->_hoops_RHGGR.plane)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_RPGAP)) {
					if (a->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR != b->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_HPGAP)) {
					if (a->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR != b->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_PPGAP)) {
					if (a->_hoops_HHAIR->_hoops_RHGGR.hither != b->_hoops_HHAIR->_hoops_RHGGR.hither ||
						a->_hoops_HHAIR->_hoops_RHGGR.yon != b->_hoops_HHAIR->_hoops_RHGGR.yon)
						return false;
				}
				if (BIT (a->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_IPGAP)) {
					if (a->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask != b->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask ||
						a->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value != b->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value)
						return false;
				}
				if (BIT (a->_hoops_RSIAA, _hoops_GGRAP)) {
					if (a->_hoops_HHAIR->_hoops_IHAIR.mask != b->_hoops_HHAIR->_hoops_IHAIR.mask ||
						a->_hoops_HHAIR->_hoops_IHAIR.value != b->_hoops_HHAIR->_hoops_IHAIR.value)
						return false;

					if (BIT (a->_hoops_HHAIR->_hoops_IHAIR.value, _hoops_SCSRP)) {
						if (a->_hoops_HHAIR->_hoops_IHAIR._hoops_GRCR != b->_hoops_HHAIR->_hoops_IHAIR._hoops_GRCR)
							return false;
					}
					if (BIT (a->_hoops_HHAIR->_hoops_IHAIR.value, _hoops_ICSRP)) {
						if (a->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[0] != b->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[0] ||
							a->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[1] != b->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[1])
							return false;
					}
					if (BIT (a->_hoops_HHAIR->_hoops_IHAIR.value, _hoops_GSSRP)) {
						if (a->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR.length !=
							b->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR.length ||
							!_hoops_RAHSR (a->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR,
							b->_hoops_HHAIR->_hoops_IHAIR._hoops_GIAIR))
							return false;
					}
				}
			}
		}
		else if (b->_hoops_HHAIR != null)
			return false;

		if (BIT (a->_hoops_RRRAP, _hoops_PARAP)) {
			if (a->_hoops_SIRAP != b->_hoops_SIRAP)
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_HRRAP)) {
			if (a->_hoops_HHAAP[0] != b->_hoops_HHAAP[0] || a->_hoops_HHAAP[1] != b->_hoops_HHAAP[1])
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_APRAP)) {
			if (a->_hoops_HCIH.left != b->_hoops_HCIH.left || a->_hoops_HCIH.right != b->_hoops_HCIH.right ||
				a->_hoops_HCIH.bottom != b->_hoops_HCIH.bottom || a->_hoops_HCIH.top != b->_hoops_HCIH.top)
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_GARAP)) {
			if (a->_hoops_IHAAP[0] != b->_hoops_IHAAP[0] || a->_hoops_IHAAP[1] != b->_hoops_IHAAP[1])
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_RARAP)) {
			if (a->_hoops_CHAAP != b->_hoops_CHAAP)
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_CPRAP)) {
			if (a->_hoops_HRA != b->_hoops_HRA)
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_SRRAP)) {
			if (a->_hoops_SRI != b->_hoops_SRI)
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_CARAP)) {
			if (a->_hoops_RCRAP != b->_hoops_RCRAP)
				return false;
		}
		if (BIT (a->_hoops_RRRAP, _hoops_IRRAP)) {
			if (a->_hoops_PSAAP != b->_hoops_PSAAP)
				return false;
		}
	}

	if (a->_hoops_RSIAA != 0) {
		if (a->_hoops_PRSI != null) {
			if (b->_hoops_PRSI == null)
				return false;

			if (BIT (a->_hoops_RSIAA, _hoops_SGICA)) {
				if (a->_hoops_PRSI->mask != b->_hoops_PRSI->mask ||
					a->_hoops_PRSI->value != b->_hoops_PRSI->value)
					return false;

				if (BIT (a->_hoops_PRSI->value, _hoops_ISCRP)) {
					for (int i = 0; i < _hoops_IGAIR; i++)
						if (a->_hoops_PRSI->_hoops_PRPHA[i] != b->_hoops_PRSI->_hoops_PRPHA[i])
							return false;
				}
				if (BIT (a->_hoops_PRSI->value, _hoops_IASRP)) {
					for (int i = 0; i < _hoops_IGAIR; i++)
						if (a->_hoops_PRSI->_hoops_AISRP[i] != b->_hoops_PRSI->_hoops_AISRP[i])
							return false;
				}
				if (BIT (a->_hoops_PRSI->value, _hoops_IRSRP)) {
					for (int i = 0; i < _hoops_IGAIR; i++)
						if (a->_hoops_PRSI->_hoops_GHRGR[i] != b->_hoops_PRSI->_hoops_GHRGR[i])
							return false;
				}
				if (BIT (a->_hoops_PRSI->value, _hoops_GRSRP)) {
					if (a->_hoops_PRSI->_hoops_SRHHR != b->_hoops_PRSI->_hoops_SRHHR)
						return false;
				}
				if (BIT (a->_hoops_PRSI->value, _hoops_CSCRP)) {
					if (a->_hoops_PRSI->_hoops_HISRP != b->_hoops_PRSI->_hoops_HISRP)
						return false;
				}
				if (BIT (a->_hoops_PRSI->value, _hoops_HASRP)) {
					if (a->_hoops_PRSI->_hoops_IISRP != b->_hoops_PRSI->_hoops_IISRP)
						return false;
				}
				if (BIT (a->_hoops_PRSI->value, _hoops_SSCRP)) {
					if (a->_hoops_PRSI->_hoops_IRSH != b->_hoops_PRSI->_hoops_IRSH)
						return false;
				}
				if (BIT (a->_hoops_PRSI->value, _hoops_GGSRP)) {
					if (a->_hoops_PRSI->_hoops_RHPHA != b->_hoops_PRSI->_hoops_RHPHA)
						return false;
				}
				if (BIT (a->_hoops_PRSI->value, _hoops_IGSRP)) {
					if (a->_hoops_PRSI->_hoops_ARPHA != b->_hoops_PRSI->_hoops_ARPHA)
						return false;
				}
				if (ANYBIT (a->_hoops_PRSI->value, _hoops_HRSRP)) {
					if (BIT (a->_hoops_PRSI->value, _hoops_PRSRP))
						if (a->_hoops_PRSI->bounding->cuboid.min != b->_hoops_PRSI->bounding->cuboid.min ||
							a->_hoops_PRSI->bounding->cuboid.max != b->_hoops_PRSI->bounding->cuboid.max)
							return false;
				}
				if (BIT (a->_hoops_PRSI->value, _hoops_PASRP)) {
					if (a->_hoops_PRSI->_hoops_RCSRP != b->_hoops_PRSI->_hoops_RCSRP)
						return false;
				}
			}
		}
		else if (b->_hoops_PRSI != null)
				return false;

		if (a->locks != null) {
			if (b->locks == null)
				return false;

			if (BIT (a->_hoops_RSIAA, _hoops_GSIAA)) {
				if (!EQUAL_MEMORY (&a->locks->normal, sizeof(_hoops_CACRP), &b->locks->normal))
					return false;
			}
			if (BIT (a->_hoops_RSIAA, _hoops_RGRAP)) {
				if (!EQUAL_MEMORY (&a->locks->_hoops_SACRP, sizeof(_hoops_CACRP), &b->locks->_hoops_SACRP))
					return false;
			}
		}
		else if (b->locks != null)
			return false;

		if (BIT (a->_hoops_RSIAA, _hoops_GGICA)) {
			if (a->_hoops_RGICA.mask != b->_hoops_RGICA.mask ||
				a->_hoops_RGICA.value != b->_hoops_RGICA.value)
				return false;

			if (BIT (a->_hoops_RGICA.value, _hoops_HPAAP)) {
				if (a->_hoops_RGICA._hoops_SPAAP != b->_hoops_RGICA._hoops_SPAAP)
					return false;
			}
			if (BIT (a->_hoops_RGICA.value, _hoops_CPAAP)) {
				if (a->_hoops_RGICA._hoops_GHAAP != b->_hoops_RGICA._hoops_GHAAP)
					return false;
			}
		}

		if (a->_hoops_AIAIR != null) {
			if (b->_hoops_AIAIR == null)
				return false;

			if (BIT (a->_hoops_RSIAA, _hoops_IGICA)) {
				if (a->_hoops_AIAIR->mask != b->_hoops_AIAIR->mask ||
					a->_hoops_AIAIR->value != b->_hoops_AIAIR->value)
					return false;

				if (BIT (a->_hoops_AIAIR->value, _hoops_RPCRP)) {
					if (!_hoops_RAHSR (a->_hoops_AIAIR->_hoops_PIAIR, b->_hoops_AIAIR->_hoops_PIAIR))
						return false;
				}
				if (BIT (a->_hoops_AIAIR->value, _hoops_GHCRP)) {
					if (a->_hoops_AIAIR->weight.value != b->_hoops_AIAIR->weight.value ||
						a->_hoops_AIAIR->weight._hoops_HHP != b->_hoops_AIAIR->weight._hoops_HHP)
						return false;
				}
				if (BIT (a->_hoops_AIAIR->value, _hoops_SPCRP)) {
					if (a->_hoops_AIAIR->color != b->_hoops_AIAIR->color)
						return false;
				}
				if (BIT (a->_hoops_AIAIR->value, _hoops_APCRP)) {
					if (a->_hoops_AIAIR->_hoops_IHCRP != b->_hoops_AIAIR->_hoops_IHCRP)
						return false;
				}
				if (BIT (a->_hoops_AIAIR->value, _hoops_PPCRP)) {
					if (a->_hoops_AIAIR->_hoops_CHIH != b->_hoops_AIAIR->_hoops_CHIH)
						return false;
				}
				if (BIT (a->_hoops_AIAIR->value, _hoops_PHCRP)) {
					if (a->_hoops_AIAIR->_hoops_CHCRP != b->_hoops_AIAIR->_hoops_CHCRP)
						return false;
				}
				if (BIT (a->_hoops_AIAIR->value, _hoops_AHCRP)) {
					if (a->_hoops_AIAIR->_hoops_SRI != b->_hoops_AIAIR->_hoops_SRI)
						return false;
				}
			}
		}
		else if (b->_hoops_AIAIR != null)
			return false;


		if (a->_hoops_IIAIR != null) {
			if (b->_hoops_IIAIR == null)
				return false;

			if (ANYBIT (a->_hoops_RSIAA, _hoops_AGRAP | _hoops_PRICA)) {
				if (a->_hoops_IIAIR->mask != b->_hoops_IIAIR->mask ||
					a->_hoops_IIAIR->value != b->_hoops_IIAIR->value)
					return false;


				if (BIT (a->_hoops_IIAIR->value, _hoops_AICRP)) {
					if (a->_hoops_IIAIR->_hoops_CCCRP != b->_hoops_IIAIR->_hoops_CCCRP)
						return false;

					if (a->_hoops_IIAIR->_hoops_CCCRP == _hoops_ICCRP) {
						if (a->_hoops_IIAIR->scale != b->_hoops_IIAIR->scale ||
							a->_hoops_IIAIR->translate != b->_hoops_IIAIR->translate)
							return false;
					}
				}


				if (BIT (a->_hoops_IIAIR->value, _hoops_IICRP) && a->_hoops_IIAIR->_hoops_SIAIR != null) {
					if (a->_hoops_IIAIR->_hoops_CIAIR != b->_hoops_IIAIR->_hoops_CIAIR)
						return false;
					for (int i=0; i<a->_hoops_IIAIR->_hoops_CIAIR; i++)
						if (a->_hoops_IIAIR->_hoops_SIAIR[i] != b->_hoops_IIAIR->_hoops_SIAIR[i])
							return false;
				}
				if (BIT (a->_hoops_IIAIR->value, _hoops_CICRP)) {
					if (a->_hoops_IIAIR->_hoops_GCAIR != b->_hoops_IIAIR->_hoops_GCAIR)
						return false;
					for (int i=0; i<a->_hoops_IIAIR->_hoops_GCAIR; i++)
						if (a->_hoops_IIAIR->colors[i] != b->_hoops_IIAIR->colors[i])
							return false;
				}
				if (BIT (a->_hoops_IIAIR->value, _hoops_SICRP)) {
					if (a->_hoops_IIAIR->_hoops_RCAIR != b->_hoops_IIAIR->_hoops_RCAIR)
						return false;
					for (int i=0; i<a->_hoops_IIAIR->_hoops_RCAIR; i++)
						if (!_hoops_RAHSR (a->_hoops_IIAIR->_hoops_ACAIR[i],
										  b->_hoops_IIAIR->_hoops_ACAIR[i]))
							return false;
				}
				if (BIT (a->_hoops_IIAIR->value, _hoops_GCCRP)) {
					if (a->_hoops_IIAIR->weight_count != b->_hoops_IIAIR->weight_count)
						return false;
					for (int i=0; i<a->_hoops_IIAIR->weight_count; i++)
						if (a->_hoops_IIAIR->weights[i].value != b->_hoops_IIAIR->weights[i].value ||
							a->_hoops_IIAIR->weights[i]._hoops_HHP != b->_hoops_IIAIR->weights[i]._hoops_HHP)
							return false;
				}
			}
		}
		else if (b->_hoops_IIAIR != null)
			return false;

		if (BIT (a->_hoops_RSIAA, _hoops_PGRAP)) {
			if (a->_hoops_SHAAP != b->_hoops_SHAAP)
				return false;

			if (BIT (a->_hoops_SHAAP, _hoops_AIGRP)) {
				if (a->_hoops_IHRH.translate != b->_hoops_IHRH.translate ||
					a->_hoops_IHRH.scale != b->_hoops_IHRH.scale)
					return false;
			}
			if (BIT (a->_hoops_SHAAP, _hoops_PIGRP)) {
				if (a->_hoops_IHRH.color != b->_hoops_IHRH.color)
					return false;
			}
			if (BIT (a->_hoops_SHAAP, _hoops_HIGRP)) {
				if (a->_hoops_IHRH._hoops_ACGRP != b->_hoops_IHRH._hoops_ACGRP)
					return false;
			}
		}

		if (a->geometry != null) {
			if (b->geometry == null)
				return false;

			if (BIT (a->_hoops_RSIAA, _hoops_IRICA)) {
				if (a->geometry->_hoops_APPI.mask != b->geometry->_hoops_APPI.mask ||
					a->geometry->_hoops_APPI.value != b->geometry->_hoops_APPI.value)
					return false;

				if (BIT (a->geometry->_hoops_APPI.value, _hoops_CHGAP)) {
					if (a->geometry->_hoops_APPI._hoops_PPPI != b->geometry->_hoops_APPI._hoops_PPPI)
						return false;
				}
				if (BIT (a->geometry->_hoops_APPI.value, _hoops_SHGAP)) {
					if (a->geometry->_hoops_APPI._hoops_HPPI != b->geometry->_hoops_APPI._hoops_HPPI)
						return false;
				}
				if (BIT (a->geometry->_hoops_APPI.value, _hoops_GIGAP)) {
					if (a->geometry->_hoops_APPI._hoops_IPPI != b->geometry->_hoops_APPI._hoops_IPPI)
						return false;
				}
				if (BIT (a->geometry->_hoops_APPI.value, _hoops_RIGAP)) {
					if (a->geometry->_hoops_APPI._hoops_CPPI != b->geometry->_hoops_APPI._hoops_CPPI)
						return false;
				}
				if (BIT (a->geometry->_hoops_APPI.value, _hoops_AIGAP)) {
					if (a->geometry->_hoops_APPI._hoops_SPPI != b->geometry->_hoops_APPI._hoops_SPPI)
						return false;
				}
			}
			if (BIT (a->_hoops_RSIAA, _hoops_CRICA)) {
				if (a->geometry->_hoops_PSRIR.mask != b->geometry->_hoops_PSRIR.mask ||
					a->geometry->_hoops_PSRIR.value != b->geometry->_hoops_PSRIR.value)
					return false;

				if (BIT (a->geometry->_hoops_PSRIR.value, _hoops_PIGAP)) {
					if (a->geometry->_hoops_PSRIR.configs._hoops_GGIRP !=
						b->geometry->_hoops_PSRIR.configs._hoops_GGIRP)
						return false;
				}
				if (BIT (a->geometry->_hoops_PSRIR.value, _hoops_IIGAP)) {
					if (a->geometry->_hoops_PSRIR.configs._hoops_CSHRP !=
						b->geometry->_hoops_PSRIR.configs._hoops_CSHRP)
						return false;
				}
				if (BIT (a->geometry->_hoops_PSRIR.value, _hoops_CIGAP)) {
					if (a->geometry->_hoops_PSRIR.configs._hoops_RGIRP !=
						b->geometry->_hoops_PSRIR.configs._hoops_RGIRP)
						return false;
				}
				if (BIT (a->geometry->_hoops_PSRIR.value, _hoops_SIGAP)) {
					if (a->geometry->_hoops_PSRIR.configs._hoops_AGIRP !=
						b->geometry->_hoops_PSRIR.configs._hoops_AGIRP)
						return false;
				}
				if (BIT (a->geometry->_hoops_PSRIR.value, _hoops_GCGAP)) {
					if (a->geometry->_hoops_PSRIR.configs._hoops_PGIRP !=
						b->geometry->_hoops_PSRIR.configs._hoops_PGIRP)
						return false;
				}
				if (BIT (a->geometry->_hoops_PSRIR.value, _hoops_RCGAP)) {
					if (a->geometry->_hoops_PSRIR.configs._hoops_SSHRP !=
						b->geometry->_hoops_PSRIR.configs._hoops_SSHRP)
						return false;
				}
			}
			if (BIT (a->_hoops_RSIAA, _hoops_SRICA)) {
				if (a->geometry->_hoops_GAICA.mask != b->geometry->_hoops_GAICA.mask)
					return false;

				if (BIT (a->geometry->_hoops_GAICA.mask, _hoops_ACGAP)) {
					for (int i = 0; i < _hoops_IGAIR; i++)
						if (a->geometry->_hoops_GAICA.cylinder[i] != b->geometry->_hoops_GAICA.cylinder[i])
							return false;
				}
				if (BIT (a->geometry->_hoops_GAICA.mask, _hoops_PCGAP)) {
					for (int i = 0; i < _hoops_IGAIR; i++)
						if (a->geometry->_hoops_GAICA.sphere[i] != b->geometry->_hoops_GAICA.sphere[i])
							return false;
				}
			}
			if (BIT (a->_hoops_RSIAA, _hoops_HRICA)) {
				if (a->geometry->mask != b->geometry->mask ||
					a->geometry->value != b->geometry->value)
					return false;

				if (BIT (a->geometry->value, _hoops_GHGAP)) {
					if (a->geometry->_hoops_GCIPR != b->geometry->_hoops_GCIPR)
						return false;
				}
			}
		}
		else if (b->geometry != null)
			return false;


		if (BIT (a->_hoops_RSIAA, _hoops_AGICA)) {
			if (a->_hoops_PGICA != b->_hoops_PGICA)
				return false;
		}

		if (BIT (a->_hoops_RSIAA, _hoops_CSHCA)) {
			if (a->_hoops_SSHCA.mask != b->_hoops_SSHCA.mask ||
				a->_hoops_SSHCA.value != b->_hoops_SSHCA.value)
				return false;

			if (BIT (a->_hoops_SSHCA.value, _hoops_RAAAP)) {
				if (a->_hoops_SSHCA.style != b->_hoops_SSHCA.style)
					return false;
			}
			if (BIT (a->_hoops_SSHCA.value, _hoops_AAAAP)) {
				if (a->_hoops_SSHCA._hoops_SRI != b->_hoops_SSHCA._hoops_SRI)
					return false;
			}
			if (BIT (a->_hoops_SSHCA.value, _hoops_HAAAP)) {
				if (a->_hoops_SSHCA._hoops_RPAAP != b->_hoops_SSHCA._hoops_RPAAP)
					return false;
			}
			if (BIT (a->_hoops_SSHCA.value, _hoops_IAAAP)) {
				if (a->_hoops_SSHCA._hoops_APAAP != b->_hoops_SSHCA._hoops_APAAP)
					return false;
			}
		}
		if (BIT (a->_hoops_RSIAA, _hoops_ISGAP)) {
			if (a->_hoops_CHP.mask != b->_hoops_CHP.mask ||
				a->_hoops_CHP.value != b->_hoops_CHP.value)
				return false;
		}
	}

	return true;
}

local bool _hoops_AIRIC (
	_hoops_GHAIR const *	a,
	_hoops_GHAIR const *	b) {

	// _hoops_IIAP _hoops_RAICR _hoops_ARPP _hoops_RGR _hoops_HRGR _hoops_PIGS

	if (BIT (a->value, _hoops_RAIRP)) {
		if (a->_hoops_APH.mask != b->_hoops_APH.mask ||
			a->_hoops_APH.value != b->_hoops_APH.value)
			return false;

		if (BIT (a->_hoops_APH.value, _hoops_SPIRP)) {
			if (a->_hoops_APH._hoops_ACIRP != b->_hoops_APH._hoops_ACIRP ||
				a->_hoops_APH._hoops_PCIRP != b->_hoops_APH._hoops_PCIRP)
				return false;
		}
		if (BIT (a->_hoops_APH.value, Heur_Culling_EXTENT)) {
			if (a->_hoops_APH._hoops_GRGC != b->_hoops_APH._hoops_GRGC)
				return false;
		}
		if (BIT (a->_hoops_APH.value, _hoops_RIHS)) {
			if (a->_hoops_APH._hoops_GCHS != b->_hoops_APH._hoops_GCHS)
				return false;
		}
		if (BIT (a->_hoops_APH.value, _hoops_AHIRP)) {
			if (a->_hoops_APH._hoops_CIIRP != b->_hoops_APH._hoops_CIIRP)
				return false;
		}
		if (BIT (a->_hoops_APH.value, _hoops_RHIRP)) {
			if (a->_hoops_APH._hoops_PCHS != b->_hoops_APH._hoops_PCHS)
				return false;
		}
		if (BIT (a->_hoops_APH.value, _hoops_HHIRP)) {
			if (a->_hoops_APH._hoops_SHHS != b->_hoops_APH._hoops_SHHS)
				return false;
		}
		if (BIT (a->_hoops_APH.value, _hoops_GHIRP)) {
			if (a->_hoops_APH.vector != b->_hoops_APH.vector)
				return false;
		}
		if (BIT (a->_hoops_APH.value, _hoops_PHIRP)) {
			if (a->_hoops_APH._hoops_IIIRP != b->_hoops_APH._hoops_IIIRP)
				return false;
		}
	}

	if (BIT (a->value, _hoops_PPIRP)) {
		if (a->_hoops_IRCRP != b->_hoops_IRCRP)
			return false;
	}
	if (BIT (a->value, _hoops_RPIRP)) {
		if (a->_hoops_GRCRP != b->_hoops_GRCRP)
			return false;
	}
	if (BIT (a->value, _hoops_SICIA)) {
		if (a->_hoops_GCCIA != b->_hoops_GCCIA)
			return false;
	}
	if (BIT (a->value, _hoops_SRIRP)) {
		if (a->_hoops_CCIRP.mask != b->_hoops_CCIRP.mask ||
			a->_hoops_CCIRP.value != b->_hoops_CCIRP.value)
			return false;

		if (BIT (a->_hoops_CCIRP.value, _hoops_HCIRP)) {
			if (a->_hoops_CCIRP._hoops_SPHPR != b->_hoops_CCIRP._hoops_SPHPR)
				return false;
		}
		if (BIT (a->_hoops_CCIRP.value, _hoops_ICIRP)) {
			if (a->_hoops_CCIRP.polyline != b->_hoops_CCIRP.polyline)
				return false;
		}
	}
	if (BIT (a->value, _hoops_CAIRP)) {
		if (a->_hoops_CSIRP != b->_hoops_CSIRP)
			return false;

		for (int i=0; i< _hoops_ISIRP; i++) {
			if (BIT (a->_hoops_CSIRP, 1<<i)) {
				if (a->_hoops_SSIRP[i] != b->_hoops_SSIRP[i])
					return false;
			}
		}
	}
	if (BIT (a->value, _hoops_APIRP)) {
		if (a->_hoops_RRCRP != b->_hoops_RRCRP ||
			a->_hoops_ARCRP != b->_hoops_ARCRP)
			return false;
	}

	return true;
}

INLINE int _hoops_PIRIC(_hoops_SPPIR alter * c)
{
	int key = c->count + 1;

	int n = 0;

	while (n < c->count) {
		key += c->_hoops_SGCAA[n];
		key += c->values[n];
		n++;
	}

	_hoops_PCACA * a = c->_hoops_ACPGR;

	while (a != null) {
		key += a->type;
		key += a->flags<<16;
		key += a->condition.count;

		n = 0;

		while (n < a->condition.count) {
			key += a->condition._hoops_ASACA[n];
			n++;
		}

		a = a->next;
	}

	return key;
}

local bool _hoops_HIRIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	Attribute const *	_hoops_IIRIC,
	Attribute const *	_hoops_CIRIC) {
	char				_hoops_SIRIC[4096];
	char				_hoops_GCRIC[4096];

	/* _hoops_PSSP _hoops_RPP _hoops_GIPR _hoops_GRAA-_hoops_PHIPR */
	if (_hoops_IIRIC == null && _hoops_CIRIC == null)
		return true;

	/* _hoops_GRAA-_hoops_PSSP _hoops_RPP _hoops_PGI _hoops_HRGR _hoops_RCRIC */
	if (_hoops_IIRIC == null || _hoops_CIRIC == null)
		return false;

	/* _hoops_PAR _hoops_RPP _hoops_CSSC _hoops_GA'_hoops_RA _hoops_ISPCA */
	if (_hoops_IIRIC->type != _hoops_CIRIC->type)
		return false;

	/* _hoops_CICAR */
	switch (_hoops_IIRIC->type) {
		case HK_COLOR: {
			if (!_hoops_AHRIC ((_hoops_SSGI *)_hoops_IIRIC, (_hoops_SSGI *)_hoops_CIRIC))
				return false;
		}	break;

		case HK_LINE_WEIGHT:
		case HK_EDGE_WEIGHT:
		case HK_MARKER_SIZE:
		case HK_TEXT_SPACING: {
			_hoops_AHPIR const *		_hoops_ACRIC = (_hoops_AHPIR const *)_hoops_IIRIC;
			_hoops_AHPIR const *		_hoops_PCRIC = (_hoops_AHPIR const *)_hoops_CIRIC;

			if (_hoops_ACRIC->data.value != _hoops_PCRIC->data.value ||
				_hoops_ACRIC->data._hoops_HHP != _hoops_PCRIC->data._hoops_HHP)
				return false;
		}	break;

		case HK_FACE_PATTERN:
		case HK_WINDOW_PATTERN:
		case HK_TEXT_ALIGNMENT: {
			_hoops_GGPIR const *		_hoops_HCRIC = (_hoops_GGPIR const *)_hoops_IIRIC;
			_hoops_GGPIR const *		_hoops_ICRIC = (_hoops_GGPIR const *)_hoops_CIRIC;

			if (_hoops_HCRIC->value != _hoops_ICRIC->value ||
				_hoops_HCRIC->_hoops_HHCAP != _hoops_ICRIC->_hoops_HHCAP)
				return false;
		}	break;

		case HK_LINE_PATTERN: {
			_hoops_PSAIR const *		_hoops_CCRIC = (_hoops_PSAIR const *)_hoops_IIRIC;
			_hoops_PSAIR const *		_hoops_SCRIC = (_hoops_PSAIR const *)_hoops_CIRIC;

			if (_hoops_CCRIC->value != _hoops_SCRIC->value ||
				_hoops_CCRIC->mask != _hoops_SCRIC->mask ||
				_hoops_CCRIC->_hoops_ASCAP != _hoops_SCRIC->_hoops_ASCAP ||
				_hoops_CCRIC->_hoops_RSCAP != _hoops_SCRIC->_hoops_RSCAP ||
				_hoops_CCRIC->_hoops_GSCAP != _hoops_SCRIC->_hoops_GSCAP ||
				_hoops_CCRIC->_hoops_SCCAP != _hoops_SCRIC->_hoops_SCCAP)
				return false;

			if (!_hoops_RAHSR (_hoops_CCRIC->line_style, _hoops_SCRIC->line_style) ||
				!_hoops_RAHSR (_hoops_CCRIC->start_glyph, _hoops_SCRIC->start_glyph) ||
				!_hoops_RAHSR (_hoops_CCRIC->middle_glyph, _hoops_SCRIC->middle_glyph) ||
				!_hoops_RAHSR (_hoops_CCRIC->end_glyph, _hoops_SCRIC->end_glyph))
				return false;
		}	break;

		case HK_EDGE_PATTERN: {
			_hoops_ISAIR const *		_hoops_GSRIC = (_hoops_ISAIR const *)_hoops_IIRIC;
			_hoops_ISAIR const *		_hoops_RSRIC = (_hoops_ISAIR const *)_hoops_CIRIC;

			if (_hoops_GSRIC->value != _hoops_RSRIC->value ||
				_hoops_GSRIC->mask != _hoops_RSRIC->mask ||
				_hoops_GSRIC->_hoops_SCCAP != _hoops_RSRIC->_hoops_SCCAP)
				return false;

			if (!_hoops_RAHSR (_hoops_GSRIC->line_style, _hoops_RSRIC->line_style))
				return false;
		}	break;

		case HK_MARKER_SYMBOL: {
			_hoops_SSAIR const *		_hoops_ASRIC = (_hoops_SSAIR const *)_hoops_IIRIC;
			_hoops_SSAIR const *		_hoops_PSRIC = (_hoops_SSAIR const *)_hoops_CIRIC;

			if (!_hoops_RAHSR (_hoops_ASRIC->name, _hoops_PSRIC->name) ||
				_hoops_ASRIC->_hoops_HHCAP != _hoops_PSRIC->_hoops_HHCAP)
				return false;
		}	break;

		case HK_WINDOW_FRAME: {
			_hoops_GSAIR const *		_hoops_HSRIC = (_hoops_GSAIR const *)_hoops_IIRIC;
			_hoops_GSAIR const *		_hoops_ISRIC = (_hoops_GSAIR const *)_hoops_CIRIC;

			if (_hoops_HSRIC->flags != _hoops_ISRIC->flags)
				return false;
		}	break;

		case HK_HANDEDNESS: {
			_hoops_ARAIR const *		_hoops_CSRIC = (_hoops_ARAIR const *)_hoops_IIRIC;
			_hoops_ARAIR const *		_hoops_SSRIC = (_hoops_ARAIR const *)_hoops_CIRIC;

			if (_hoops_CSRIC->which != _hoops_SSRIC->which)
				return false;
		}	break;

		case HK_TEXT_PATH: {
			_hoops_RGPIR const *		_hoops_GGAIC = (_hoops_RGPIR const *)_hoops_IIRIC;
			_hoops_RGPIR const *		_hoops_RGAIC = (_hoops_RGPIR const *)_hoops_CIRIC;

			if (_hoops_GGAIC->value != _hoops_RGAIC->value)
				return false;
		}	break;

		case HK_USER_VALUE: {
			_hoops_RHPIR const *		_hoops_AGAIC = (_hoops_RHPIR const *)_hoops_IIRIC;
			_hoops_RHPIR const *		_hoops_PGAIC = (_hoops_RHPIR const *)_hoops_CIRIC;

			if (BIT(_hoops_ARCAR->flags, _hoops_HGCHC))
				return false;

			if (_hoops_AGAIC->data != _hoops_PGAIC->data)
				return false;
		}	break;

		case HK_SELECTABILITY: {
			_hoops_ASAIR const *		_hoops_HGAIC = (_hoops_ASAIR const *)_hoops_IIRIC;
			_hoops_ASAIR const *		_hoops_IGAIC = (_hoops_ASAIR const *)_hoops_CIRIC;

			if (_hoops_HGAIC->mask != _hoops_IGAIC->mask ||
				_hoops_HGAIC->up != _hoops_IGAIC->up ||
				_hoops_HGAIC->down != _hoops_IGAIC->down ||
				_hoops_HGAIC->_hoops_RHARP != _hoops_IGAIC->_hoops_RHARP ||
				_hoops_HGAIC->_hoops_AHARP != _hoops_IGAIC->_hoops_AHARP ||
				_hoops_HGAIC->_hoops_PHARP != _hoops_IGAIC->_hoops_PHARP ||
				_hoops_HGAIC->_hoops_HHARP != _hoops_IGAIC->_hoops_HHARP)
				return false;
		}	break;

		case HK_VISIBILITY: {
			_hoops_RSAIR const *		_hoops_CGAIC = (_hoops_RSAIR const *)_hoops_IIRIC;
			_hoops_RSAIR const *		_hoops_SGAIC = (_hoops_RSAIR const *)_hoops_CIRIC;

			if (_hoops_CGAIC->mask != _hoops_SGAIC->mask ||
				_hoops_CGAIC->value != _hoops_SGAIC->value)
				return false;
			if (BIT (_hoops_CGAIC->value, T_CUT_GEOMETRY) &&
				_hoops_CGAIC->_hoops_PRIGA.mask != _hoops_SGAIC->_hoops_PRIGA.mask ||
				_hoops_CGAIC->_hoops_PRIGA.value != _hoops_SGAIC->_hoops_PRIGA.value)
				return false;
			if (BIT (_hoops_CGAIC->value, T_ANY_SHADOW) &&
				_hoops_CGAIC->_hoops_SPSS.mask != _hoops_SGAIC->_hoops_SPSS.mask ||
				_hoops_CGAIC->_hoops_SPSS.value != _hoops_SGAIC->_hoops_SPSS.value)
				return false;
		}	break;

		case HK_MODELLING_MATRIX:
		case HK_TEXTURE_MATRIX: {
			_hoops_ISGI const *		_hoops_GRAIC = (_hoops_ISGI const *)_hoops_IIRIC;
			_hoops_ISGI const *		_hoops_RRAIC = (_hoops_ISGI const *)_hoops_CIRIC;

			if (_hoops_GRAIC->matrix._hoops_RAGR != _hoops_RRAIC->matrix._hoops_RAGR)
				return false;

			if (!EQUAL_MEMORY (_hoops_GRAIC->matrix.elements, 16 * sizeof(float), _hoops_RRAIC->matrix.elements))
				return false;
		}	break;

		case HK_CLIP_REGION: {
			_hoops_IRAIR const *		_hoops_ARAIC = (_hoops_IRAIR const *)_hoops_IIRIC;
			_hoops_IRAIR const *		_hoops_PRAIC = (_hoops_IRAIR const *)_hoops_CIRIC;

			if (_hoops_ARAIC->flags != _hoops_PRAIC->flags ||
				_hoops_ARAIC->count != _hoops_PRAIC->count)
				return false;
			if (!EQUAL_MEMORY (_hoops_ARAIC->points,
							   _hoops_ARAIC->count * sizeof(Point),
							   _hoops_PRAIC->points))
				return false;
		}	break;

		case HK_STYLE: {
			Style const *		_hoops_HGAIC = (Style const *)_hoops_IIRIC;
			Style const *		_hoops_IGAIC = (Style const *)_hoops_CIRIC;

			if (_hoops_HGAIC->_hoops_IGRPR != _hoops_IGAIC->_hoops_IGRPR ||
				_hoops_HGAIC->condition.count != _hoops_IGAIC->condition.count)
				return false;
			if (!_hoops_RAHSR (_hoops_HGAIC->_hoops_SGAIR, _hoops_IGAIC->_hoops_SGAIR))
				return false;
			if (!EQUAL_MEMORY (_hoops_HGAIC->condition._hoops_ASACA,
							   _hoops_HGAIC->condition.count * sizeof(int),
							   _hoops_IGAIC->condition._hoops_ASACA))
				return false;
		}	break;

		case _hoops_CPPIR: {
			_hoops_SPPIR alter *		_hoops_HRAIC = (_hoops_SPPIR alter *)_hoops_IIRIC;
			_hoops_SPPIR alter *		_hoops_IRAIC = (_hoops_SPPIR alter *)_hoops_CIRIC;

			if (_hoops_HRAIC->count != _hoops_IRAIC->count)
				return false;

			if ((_hoops_HRAIC->_hoops_ACPGR != null) != (_hoops_IRAIC->_hoops_ACPGR != null))
				return false;

			if (_hoops_HRAIC->_hoops_PRGCA == 0)
				_hoops_HRAIC->_hoops_PRGCA = _hoops_PIRIC(_hoops_HRAIC);

			if (_hoops_IRAIC->_hoops_PRGCA == 0)
				_hoops_IRAIC->_hoops_PRGCA = _hoops_PIRIC(_hoops_IRAIC);

			if (_hoops_HRAIC->_hoops_PRGCA != _hoops_IRAIC->_hoops_PRGCA)
				return false;

			if (_hoops_HRAIC->count > 0 &&
				(!EQUAL_MEMORY (_hoops_HRAIC->_hoops_SGCAA, _hoops_HRAIC->count * sizeof(unsigned int), _hoops_IRAIC->_hoops_SGCAA) ||
				 !EQUAL_MEMORY (_hoops_HRAIC->values, _hoops_HRAIC->count * sizeof(unsigned int), _hoops_IRAIC->values)))
				return false;

			if (_hoops_HRAIC->_hoops_ACPGR != null) {
				// _hoops_ISPR _hoops_IH _hoops_HSGS _hoops_CSSC _hoops_GGR _hoops_CRAIC
				_hoops_PCACA * a1 = _hoops_IRAIC->_hoops_ACPGR;

				while (a1 != null) {
					_hoops_PCACA * a2 = _hoops_HRAIC->_hoops_ACPGR;

					while (a2 != null) {
						if (a1->type == a2->type)
							break;

						a2 = a2->next;
					}

					if (a2 == null)
						return false;

					a1 = a1->next;
				}

				// _hoops_CICAR _hoops_ISPR
				a1 = _hoops_HRAIC->_hoops_ACPGR;

				while (a1 != null) {
					_hoops_PCACA * a2 = _hoops_IRAIC->_hoops_ACPGR;

					while (a2 != null) {
						if (a1->type == a2->type) {
							if (a1->flags != a2->flags)
								return false;

							if (a1->condition.count != a2->condition.count ||
								!EQUAL_MEMORY (a1->condition._hoops_ASACA, a1->condition.count * sizeof(unsigned int), a2->condition._hoops_ASACA))
								return false;

							break;
						}

						a2 = a2->next;
					}

					if (a2 == null)
						return false;

					a1 = a1->next;
				}
			}
		}	break;

		/* _hoops_PAH _hoops_SAHR _hoops_RRI-_hoops_PAR-_hoops_CRGP "_hoops_CRGH" _hoops_AGCR _hoops_PPR _hoops_PCR _hoops_RH [_hoops_GCAS _hoops_CSACI] _hoops_RHIPP */
		case HK_COLOR_MAP: {
			_hoops_RHAH const *		_hoops_SRAIC = (_hoops_RHAH const *)_hoops_IIRIC;
			_hoops_RHAH const *		_hoops_GAAIC = (_hoops_RHAH const *)_hoops_CIRIC;

			int				i;

			if (_hoops_SRAIC->length != _hoops_GAAIC->length)
				return false;

			for (i=0; i<_hoops_SRAIC->length; i++) {
				int				length;
				char *			_hoops_ASAPR;

				_hoops_ASAPR = HI_Show_Material (_hoops_SIRIC, &_hoops_SIRIC[_hoops_GGAPR(_hoops_SIRIC)],
										&_hoops_SRAIC->_hoops_HAA[i], null, false);
				length = _hoops_ASAPR - _hoops_SIRIC;
				_hoops_ASAPR = HI_Show_Material (_hoops_GCRIC, &_hoops_GCRIC[_hoops_GGAPR(_hoops_GCRIC)],
										&_hoops_GAAIC->_hoops_HAA[i], null, false);
				if (_hoops_ASAPR - _hoops_GCRIC != length)
					return false;
				if (!_hoops_GPPSA (_hoops_SIRIC, length, _hoops_GCRIC))
					return false;
			}
		}	break;

		case HK_HEURISTICS: {
			_hoops_GHAIR const *		_hoops_CSRIC = (_hoops_GHAIR const *)_hoops_IIRIC;
			_hoops_GHAIR const *		_hoops_SSRIC = (_hoops_GHAIR const *)_hoops_CIRIC;

			if (_hoops_CSRIC->mask != _hoops_SSRIC->mask ||
				_hoops_CSRIC->value != _hoops_SSRIC->value)
				return false;

			if (!_hoops_AIRIC (_hoops_CSRIC, _hoops_SSRIC))
				return false;
		}	break;

		case HK_RENDERING_OPTIONS: {
			_hoops_RHAIR const *		_hoops_RAAIC = (_hoops_RHAIR const *)_hoops_IIRIC;
			_hoops_RHAIR const *		_hoops_AAAIC = (_hoops_RHAIR const *)_hoops_CIRIC;

			if (_hoops_RAAIC->_hoops_SCIAA != _hoops_AAAIC->_hoops_SCIAA ||
				_hoops_RAAIC->_hoops_RSIAA != _hoops_AAAIC->_hoops_RSIAA ||
				_hoops_RAAIC->_hoops_PSHCA != _hoops_AAAIC->_hoops_PSHCA ||
				_hoops_RAAIC->_hoops_RRRAP != _hoops_AAAIC->_hoops_RRRAP ||
				_hoops_RAAIC->_hoops_ISHCA != _hoops_AAAIC->_hoops_ISHCA ||
				_hoops_RAAIC->_hoops_GHRAP != _hoops_AAAIC->_hoops_GHRAP)
				return false;

			if (!_hoops_RIRIC (_hoops_RAAIC, _hoops_AAAIC))
				return false;
			}	break;

		case HK_TEXT_FONT: {
			HI_Show_Text_Font ((_hoops_AGPIR *)_hoops_IIRIC, _hoops_SIRIC, -1);
			HI_Show_Text_Font ((_hoops_AGPIR *)_hoops_CIRIC, _hoops_GCRIC, -1);

			if (!_hoops_AGGR (_hoops_SIRIC, _hoops_GCRIC))
				return false;
		}	break;

		/* _hoops_RGHPA & _hoops_PPPHR, _hoops_HIH _hoops_RH _hoops_PIS _hoops_HRGR _hoops_SIGR _hoops_IS _hoops_PHHR _hoops_CCA _hoops_HAIR _hoops_APIC... */
		case _hoops_IPAIR: {
			_hoops_CPAIR const *	_hoops_PAAIC = (_hoops_CPAIR *)_hoops_IIRIC;
			_hoops_CPAIR const *	_hoops_HAAIC = (_hoops_CPAIR *)_hoops_CIRIC;
			int						i, j;

			if (_hoops_PAAIC->count != _hoops_HAAIC->count)
				return false;

			for (i=0; i<_hoops_PAAIC->count; i++) {
				for (j=0; j<_hoops_HAAIC->count; j++) {
					if (_hoops_PAAIC->keys[i] == _hoops_HAAIC->keys[j] &&
						_hoops_RAHSR (_hoops_PAAIC->textures[i]->name, _hoops_HAAIC->textures[j]->name)) {
						/* _hoops_RPPCR _hoops_PSSP, _hoops_CACH _hoops_RPP _hoops_SSIA _hoops_CPSA _hoops_CHR _hoops_RCGRA */
						if (_hoops_PAAIC->textures[i]->_hoops_RSR != null && _hoops_HAAIC->textures[i]->_hoops_RSR == null ||
							_hoops_PAAIC->textures[i]->_hoops_RSR == null && _hoops_HAAIC->textures[i]->_hoops_RSR != null)
							return false;

						if (_hoops_PAAIC->textures[i]->_hoops_RSR == null) {
							HI_Show_Texture (_hoops_ARCAR->_hoops_RIGC, _hoops_PAAIC->textures[i], _hoops_SIRIC, -1, null, 0, true, 0);
							HI_Show_Texture (_hoops_ARCAR->_hoops_RIGC, _hoops_HAAIC->textures[j], _hoops_GCRIC, -1, null, 0, true, 0);

							if (_hoops_AGGR (_hoops_SIRIC, _hoops_GCRIC))
								break;
						}
						else {
							if (_hoops_PAAIC->textures[i]->_hoops_RSR->id == _hoops_HAAIC->textures[j]->_hoops_RSR->id)
								break;
						}
					}
				}
				if (j == _hoops_HAAIC->count)	/* _hoops_PSP _hoops_PSSP */
					return false;
			}
		}	break;

		/* _hoops_CRICR, _hoops_PHRI _hoops_HAR _hoops_IAAIC _hoops_CAAIC */
		case _hoops_RPAIR: {
			_hoops_APAIR const *	_hoops_PAAIC = (_hoops_APAIR *)_hoops_IIRIC;
			_hoops_APAIR const *	_hoops_HAAIC = (_hoops_APAIR *)_hoops_CIRIC;
			int						i, j;

			if (_hoops_PAAIC->count != _hoops_HAAIC->count)
				return false;

			for (i=0; i<_hoops_PAAIC->count; i++) {
				for (j=0; j<_hoops_HAAIC->count; j++) {
					if (_hoops_PAAIC->keys[i] == _hoops_HAAIC->keys[j] &&
						_hoops_RAHSR (_hoops_PAAIC->_hoops_HPAIR[i]->name, _hoops_HAAIC->_hoops_HPAIR[j]->name)) {
						/* _hoops_RPPCR _hoops_PSSP, _hoops_CACH _hoops_RPP _hoops_SSIA _hoops_CPSA _hoops_CHR _hoops_RCGRA */
						if (_hoops_RAHSR (_hoops_PAAIC->_hoops_HPAIR[i]->definition, _hoops_HAAIC->_hoops_HPAIR[j]->definition))
							break;
					}
				}
				if (j == _hoops_HAAIC->count)	/* _hoops_PSP _hoops_PSSP */
					return false;
			}
		}	break;
		case _hoops_RAAIR: {
			_hoops_AAAIR const *	_hoops_PAAIC = (_hoops_AAAIR *)_hoops_IIRIC;
			_hoops_AAAIR const *	_hoops_HAAIC = (_hoops_AAAIR *)_hoops_CIRIC;
			int						i, j;

			if (_hoops_PAAIC->count != _hoops_HAAIC->count)
				return false;

			for (i=0; i<_hoops_PAAIC->count; i++) {
				for (j=0; j<_hoops_HAAIC->count; j++) {
					if (_hoops_PAAIC->keys[i] == _hoops_HAAIC->keys[j] &&
						_hoops_RAHSR (_hoops_PAAIC->glyphs[i]->name, _hoops_HAAIC->glyphs[j]->name)) {
						/* _hoops_RPPCR _hoops_PSSP, _hoops_CACH _hoops_RPP _hoops_SSIA _hoops_CPSA _hoops_CHR _hoops_RCGRA */
						if (_hoops_PAAIC->glyphs[i]->length == _hoops_HAAIC->glyphs[i]->length &&
							EQUAL_MEMORY (_hoops_PAAIC->glyphs[i]->data, _hoops_PAAIC->glyphs[i]->length,
										  _hoops_HAAIC->glyphs[j]->data))
							break;
					}
				}
				if (j == _hoops_HAAIC->count)	/* _hoops_PSP _hoops_PSSP */
					return false;
			}
		}	break;

		/* _hoops_GSISI _hoops_RGHPA _hoops_CPCI... */
		case HK_CALLBACK: {
			_hoops_GCHIR const *			_hoops_SAAIC = (_hoops_GCHIR const *)_hoops_IIRIC;
			_hoops_GCHIR const *			_hoops_GPAIC = (_hoops_GCHIR const *)_hoops_CIRIC;
			_hoops_IHACR const *		_hoops_RPAIC;
			_hoops_IHACR const *		_hoops_APAIC;
			int							_hoops_PPAIC, _hoops_HPAIC;

			/* _hoops_ISPR _hoops_IHHA _hoops_IIGR _hoops_CPCI */
			_hoops_PPAIC = _hoops_HPAIC = 0;
			if ((_hoops_RPAIC = _hoops_SAAIC->_hoops_ACHIR) != null) do
				++_hoops_PPAIC;
			while ((_hoops_RPAIC = _hoops_RPAIC->next) != null);
			if ((_hoops_APAIC = _hoops_GPAIC->_hoops_ACHIR) != null) do
				++_hoops_HPAIC;
			while ((_hoops_APAIC = _hoops_APAIC->next) != null);
			if (_hoops_PPAIC != _hoops_HPAIC)
				return false;

			/* _hoops_CICAR _hoops_PPS _hoops_IIGR _hoops_CPCI */
			if ((_hoops_RPAIC = _hoops_SAAIC->_hoops_ACHIR) != null) do {
				if ((_hoops_APAIC = _hoops_GPAIC->_hoops_ACHIR) != null) do {
					if (_hoops_RPAIC->type == _hoops_APAIC->type &&
						_hoops_RPAIC->_hoops_AIACR == _hoops_APAIC->_hoops_AIACR &&
						_hoops_RAHSR(_hoops_RPAIC->name->name, _hoops_APAIC->name->name))
						break;
				} while ((_hoops_APAIC = _hoops_APAIC->next) != null);

				if (_hoops_APAIC == null)	/* _hoops_PSP _hoops_PSSP */
					return false;
			} while ((_hoops_RPAIC = _hoops_RPAIC->next) != null);
		}	break;

		case HK_USER_OPTIONS: {
			if (BIT(_hoops_ARCAR->flags, _hoops_HGCHC) &&
				!BIT(_hoops_ARCAR->flags, _hoops_RRCHC))
				return false;

			_hoops_HPPIR alter * _hoops_IPAIC = (_hoops_HPPIR alter *)_hoops_IIRIC;
			_hoops_HPPIR alter * _hoops_CPAIC = (_hoops_HPPIR alter *)_hoops_CIRIC;

			if (_hoops_IPAIC->_hoops_PRGCA == 0)
				_hoops_IPAIC->_hoops_PRGCA = HI_User_Option_Hash_Key(_hoops_IPAIC);

			if (_hoops_CPAIC->_hoops_PRGCA == 0)
				_hoops_CPAIC->_hoops_PRGCA = HI_User_Option_Hash_Key(_hoops_CPAIC);

			if (_hoops_IPAIC->_hoops_PRGCA != _hoops_CPAIC->_hoops_PRGCA ||
				!HI_User_Option_Equal (_hoops_IPAIC, _hoops_CPAIC))
				return false;
		}	break;

		/* _hoops_SHR _hoops_GRAA-_hoops_SPASR */
		case HK_DRIVER:
		case HK_DRIVER_OPTIONS:
		case HK_CAMERA:
		case HK_WINDOW:
		default:
			return  false;
	}

	/* _hoops_HCR _hoops_IHRI */

	return true;
}


#define _hoops_SPAIC	256

#define _hoops_GHAIC(_hoops_RHAIC) (int)((37.0f * (_hoops_RHAIC).red) + (86.0f * (_hoops_RHAIC).green) + (144.0f * (_hoops_RHAIC).blue))

local int _hoops_SCSGA (
	_hoops_RCR const *		texture) {
	_hoops_AAPIR const *	nl;
	int					value;

	if (texture == null)
		return 0;

	value = texture->flags;

	if ((nl = texture->_hoops_PAPIR) != null) do {
		value += nl->key;
		nl = nl->next;
	} while (nl != null);

	return value;
}

local int _hoops_AHAIC (
	_hoops_SSGI const *		color) {
	_hoops_ACSGA const *	list = color->colors;
	int					value;

	value = color->_hoops_GHA;
	do {
		switch (list->type) {
			case _hoops_SHGRA: {
				_hoops_PCSGA const *		findex = (_hoops_PCSGA const *)list;

				value += (int)findex->value;
			}	break;

			case _hoops_PPCA: {
				_hoops_APCA const *		normal = (_hoops_APCA const *)list;

				value += _hoops_GHAIC (normal->rgb);
			}	break;

			case _hoops_GIGRA: {
				_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;
				Named_Material const *		mat = &_hoops_ICSGA->_hoops_ISHIR;
				_hoops_ARGRA			_hoops_PRGRA = mat->_hoops_PRGRA;
				_hoops_HIR const *	_hoops_GSSGA = mat->_hoops_SCA;

				value += mat->_hoops_PRGRA;
				value += mat->_hoops_HRGRA;

				while (_hoops_GSSGA != null) {
					value += _hoops_SCSGA (_hoops_GSSGA->texture);
					value += (int)(_hoops_GSSGA->_hoops_HGA * _hoops_GSSGA->_hoops_IRIR);
					value += _hoops_GSSGA->flags;

					_hoops_GSSGA = _hoops_GSSGA->next;
				}

				value += _hoops_GHAIC (mat->_hoops_CSHR);

				for (int i=0; i<_hoops_CRGRA; i++)
					if (BIT (_hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i]))
						value += _hoops_GHAIC (mat->color[i]);

				for (int i=0; i<_hoops_GAGRA; i++)
					if (BIT (_hoops_PRGRA, HOOPS_READ_ONLY._hoops_APGRA[i]))
						value += _hoops_SCSGA (mat->texture[i]);

				if (BIT (_hoops_PRGRA, M_TRANSMISSION))
					value += (int)(64.0f * mat->_hoops_IRIR);

				if (BIT (_hoops_PRGRA, _hoops_RAGRA))
					value += (int)(32.0f * mat->gloss);

				if (BIT (_hoops_PRGRA, _hoops_AAGRA))
					value += (int)(128.0f * mat->_hoops_PAGRA);
			}	break;
		}
	} while ((list = list->next) != null);

	return value & (_hoops_SPAIC-1);
}

local int _hoops_PHAIC (
	_hoops_ISGI const *		matrix) {

	int value = matrix->matrix._hoops_RAGR;
	for (int i=0; i<4; i++) {
		for (int j=0; j<3; j++) {
			int const *	v = (int const *)&matrix->matrix.elements[i][j];

			value += (*v & 0x0000FFFF) ^ (*v >> 16);
		}
	}

	return value & (_hoops_SPAIC-1);
}


local int _hoops_HHAIC(Attribute const * _hoops_HPHCR)
{
	int key = _hoops_HPHCR->type * _hoops_CRCCA + 1;

	switch (_hoops_HPHCR->type) {
		case HK_COLOR: {
			_hoops_SSGI const * color = (_hoops_SSGI const*)_hoops_HPHCR;
			key += _hoops_AHAIC (color);
		}	break;

		case HK_LINE_WEIGHT:
		case HK_EDGE_WEIGHT:
		case HK_MARKER_SIZE:
		case HK_TEXT_SPACING: {
			_hoops_AHPIR const * _hoops_GGGCH = (_hoops_AHPIR const *)_hoops_HPHCR;
			key += _hoops_GGGCH->data.value + _hoops_GGGCH->data._hoops_HHP;
		}	break;

		case HK_FACE_PATTERN:
		case HK_WINDOW_PATTERN:
		case HK_TEXT_ALIGNMENT: {
			_hoops_GGPIR const * _hoops_RGGCH = (_hoops_GGPIR const *)_hoops_HPHCR;
			key += _hoops_RGGCH->value + _hoops_RGGCH->_hoops_HHCAP;
		}	break;

		case HK_LINE_PATTERN: {
			_hoops_PSAIR const * _hoops_HSAIR = (_hoops_PSAIR const *)_hoops_HPHCR;
			key += _hoops_HSAIR->value +
					_hoops_HSAIR->mask +
					_hoops_HSAIR->_hoops_ASCAP +
					_hoops_HSAIR->_hoops_RSCAP +
					_hoops_HSAIR->_hoops_GSCAP +
					_hoops_HSAIR->_hoops_SCCAP;
		}	break;

		case HK_EDGE_PATTERN: {
			_hoops_ISAIR const * _hoops_CSAIR = (_hoops_ISAIR const *)_hoops_HPHCR;
			key += _hoops_CSAIR->value +
					_hoops_CSAIR->mask +
					_hoops_CSAIR->_hoops_SCCAP;
		}	break;

		case HK_MARKER_SYMBOL: {
			_hoops_SSAIR const *	_hoops_IHAIC = (_hoops_SSAIR const *)_hoops_HPHCR;
			key += _hoops_IHAIC->key;
		}	break;

		case HK_WINDOW_FRAME: {
			_hoops_GSAIR const * _hoops_CHAIC = (_hoops_GSAIR const *)_hoops_HPHCR;
			key += _hoops_CHAIC->flags;
		}	break;

		case HK_HANDEDNESS: {
			_hoops_ARAIR const * h = (_hoops_ARAIR const *)_hoops_HPHCR;
			key += h->which;
		}	break;

		case HK_TEXT_PATH: {
			_hoops_RGPIR const * _hoops_HAPAR = (_hoops_RGPIR const *)_hoops_HPHCR;
			key += (int)(_hoops_HAPAR->value.x+_hoops_HAPAR->value.y+_hoops_HAPAR->value.z);
		}	break;

		case HK_USER_VALUE: {
			_hoops_RHPIR const * _hoops_ARHC = (_hoops_RHPIR const *)_hoops_HPHCR;
			key |= _hoops_ARHC->data;
		}	break;

		case HK_SELECTABILITY: {
			_hoops_ASAIR const * s = (_hoops_ASAIR const *)_hoops_HPHCR;
			key += s->mask +
					s->up +
					s->down +
					s->_hoops_RHARP +
					s->_hoops_AHARP +
					s->_hoops_PHARP +
					s->_hoops_HHARP;
		}	break;

		case HK_VISIBILITY: {
			_hoops_RSAIR const * v = (_hoops_RSAIR const *)_hoops_HPHCR;
			key += v->mask+
					v->value;
#if 0
			if (BIT (_hoops_CGAIC->value, T_CUT_GEOMETRY) &&
				_hoops_CGAIC->_hoops_PRIGA.mask != _hoops_SGAIC->_hoops_PRIGA.mask ||
				_hoops_CGAIC->_hoops_PRIGA.value != _hoops_SGAIC->_hoops_PRIGA.value)
				return false;
			if (BIT (_hoops_CGAIC->value, T_ANY_SHADOW) &&
				_hoops_CGAIC->_hoops_SPSS.mask != _hoops_SGAIC->_hoops_SPSS.mask ||
				_hoops_CGAIC->_hoops_SPSS.value != _hoops_SGAIC->_hoops_SPSS.value)
				return false;
#endif
		}	break;

		case HK_MODELLING_MATRIX:
		case HK_TEXTURE_MATRIX: {
			_hoops_ISGI const * m = (_hoops_ISGI const *)_hoops_HPHCR;
			key += _hoops_PHAIC (m);
		}	break;

		case HK_CLIP_REGION: {
			_hoops_IRAIR const * _hoops_CRAIR = (_hoops_IRAIR const *)_hoops_HPHCR;
			key += _hoops_CRAIR->flags + _hoops_CRAIR->count;
			// _hoops_ASIGA
		}	break;

		case HK_STYLE: {
			Style const * s = (Style const *)_hoops_HPHCR;
			key |= s->condition.count;
			if (s->_hoops_IGRPR != null)
				key |= s->_hoops_IGRPR->key;
		}	break;

		case _hoops_CPPIR: {
			_hoops_SPPIR alter * c = (_hoops_SPPIR alter *)_hoops_HPHCR;

			if (c->_hoops_PRGCA == 0)
				c->_hoops_PRGCA = _hoops_PIRIC(c);

			if (c->_hoops_ACPGR != null) {
				_hoops_PCACA * action = c->_hoops_ACPGR;

				while (action != null) {
					key += action->flags;
					key += action->type;
					action = action->next;
				}
			}

			key += c->_hoops_PRGCA;
		}	break;

		/* _hoops_PAH _hoops_SAHR _hoops_RRI-_hoops_PAR-_hoops_CRGP "_hoops_CRGH" _hoops_AGCR _hoops_PPR _hoops_PCR _hoops_RH [_hoops_GCAS _hoops_CSACI] _hoops_RHIPP */
		case HK_COLOR_MAP: {
			_hoops_RHAH const * _hoops_SRAIR = (_hoops_RHAH const *)_hoops_HPHCR;
			key += _hoops_SRAIR->length;
		}	break;

		case HK_HEURISTICS: {
			_hoops_GHAIR const * h = (_hoops_GHAIR const *)_hoops_HPHCR;
			key += h->mask + h->value;
		}	break;

		case HK_RENDERING_OPTIONS: {
			_hoops_RHAIR const * _hoops_RGGHH = (_hoops_RHAIR const *)_hoops_HPHCR;
			key += _hoops_RGGHH->_hoops_SCIAA +
					_hoops_RGGHH->_hoops_RSIAA +
					_hoops_RGGHH->_hoops_PSHCA +
					_hoops_RGGHH->_hoops_RRRAP +
					_hoops_RGGHH->_hoops_ISHCA +
					_hoops_RGGHH->_hoops_GHRAP;

			if (BIT (_hoops_RGGHH->_hoops_RRRAP, _hoops_HRRAP))
				key += *((int*)&_hoops_RGGHH->_hoops_HHAAP[0]) + *((int*)&_hoops_RGGHH->_hoops_HHAAP[1]);
		}	break;

		case HK_TEXT_FONT: {
			_hoops_AGPIR const * _hoops_PGPIR = (_hoops_AGPIR const *)_hoops_HPHCR;
			key += _hoops_PGPIR->_hoops_HAICA +
					_hoops_PGPIR->_hoops_CPGRP +
					_hoops_PGPIR->transform +
					_hoops_PGPIR->_hoops_GHGRP;
		}	break;

		/* _hoops_RGHPA & _hoops_PPPHR, _hoops_HIH _hoops_RH _hoops_PIS _hoops_HRGR _hoops_SIGR _hoops_IS _hoops_PHHR _hoops_CCA _hoops_HAIR _hoops_APIC... */
		case _hoops_IPAIR: {
			_hoops_CPAIR const * _hoops_SAHCA = (_hoops_CPAIR *)_hoops_HPHCR;
			key += _hoops_SAHCA->count;
		}	break;

		/* _hoops_CRICR, _hoops_PHRI _hoops_HAR _hoops_IAAIC _hoops_CAAIC */
		case _hoops_RPAIR: {
			_hoops_APAIR const *	_hoops_SAHCA = (_hoops_APAIR *)_hoops_HPHCR;
			key += _hoops_SAHCA->count;
		}	break;
		case _hoops_RAAIR: {
			_hoops_AAAIR const * _hoops_SAHCA = (_hoops_AAAIR *)_hoops_HPHCR;
			key += _hoops_SAHCA->count;
		}	break;

		/* _hoops_GSISI _hoops_RGHPA _hoops_CPCI... */
		case HK_CALLBACK: {
			_hoops_GCHIR const * _hoops_RCHIR = (_hoops_GCHIR const *)_hoops_HPHCR;
			_hoops_IHACR const * _hoops_RCACR;
			if ((_hoops_RCACR = _hoops_RCHIR->_hoops_ACHIR) != null) do {
				key++;
			} while ((_hoops_RCACR = _hoops_RCACR->next) != null);
		}	break;

		case HK_USER_OPTIONS: {
			_hoops_HPPIR alter * _hoops_IPPIR = (_hoops_HPPIR alter *)_hoops_HPHCR;

			if (_hoops_IPPIR->_hoops_PRGCA == 0)
				_hoops_IPPIR->_hoops_PRGCA = HI_User_Option_Hash_Key(_hoops_IPPIR);

			key |= _hoops_IPPIR->_hoops_PRGCA;
		}	break;

		/* _hoops_SHR _hoops_GRAA-_hoops_SPASR */
		case HK_DRIVER:
		case HK_DRIVER_OPTIONS:
		case HK_CAMERA:
		case HK_WINDOW:
		default: {
			//_hoops_ASIGA
		}	break;
	}

	return key;
}

local bool _hoops_SHAIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP const *		_hoops_GIAIC,
	_hoops_CRCP const *		_hoops_RIAIC) {

	Attribute const *	_hoops_IIRIC = _hoops_GIAIC->_hoops_IPPGR;
	Attribute const *	_hoops_CIRIC = _hoops_RIAIC->_hoops_IPPGR;

	_hoops_SSAGR(_hoops_IIRIC);
	_hoops_SSAGR(_hoops_CIRIC);

	Attribute const *	_hoops_AIAIC[_hoops_CRCCA+1];
	Attribute const *	_hoops_PIAIC[_hoops_CRCCA+1];

	int	_hoops_PPAIC = 0;
	int	_hoops_HPAIC = 0;

	int _hoops_HIAIC = 1;
	int _hoops_IIAIC = 1;

	while (_hoops_IIRIC != null) {
		_hoops_SSAGR(_hoops_IIRIC->next);
		_hoops_AIAIC[_hoops_PPAIC++] = _hoops_IIRIC;
		_hoops_HIAIC += _hoops_HHAIC(_hoops_IIRIC);
		_hoops_IIRIC = _hoops_IIRIC->next;
	}

	while (_hoops_CIRIC != null) {
		_hoops_SSAGR(_hoops_CIRIC->next);
		_hoops_PIAIC[_hoops_HPAIC++] = _hoops_CIRIC;
		_hoops_IIAIC += _hoops_HHAIC(_hoops_CIRIC);
		_hoops_CIRIC = _hoops_CIRIC->next;
	}

	if (_hoops_HIAIC != _hoops_IIAIC)
		return false;

	if (_hoops_PPAIC != _hoops_HPAIC)
		return false;

	/* _hoops_CICAR _hoops_PPS */
	while (_hoops_PPAIC-- > 0) {
		/* _hoops_PAR _hoops_RPP _hoops_CSSC _hoops_GA'_hoops_RA _hoops_ISPCA */
		if (_hoops_AIAIC[_hoops_PPAIC]->type != _hoops_PIAIC[_hoops_PPAIC]->type)
			return false;

		if (!_hoops_HIRIC (_hoops_ARCAR, _hoops_AIAIC[_hoops_PPAIC], _hoops_PIAIC[_hoops_PPAIC]))
			return false;
	}

	return true;
}

local bool _hoops_CIAIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP const *		container,
	_hoops_CRCP const *		_hoops_IIRHA,
	int					type) {
	Attribute const *	_hoops_IIRIC;
	Attribute const *	_hoops_CIRIC;

	if ((_hoops_IIRIC = container->_hoops_IPPGR) != null) do {
		if (_hoops_IIRIC->type >= type) {
			if (_hoops_IIRIC->type > type)
				_hoops_IIRIC = null;
			break;
		}
	} while ((_hoops_IIRIC = _hoops_IIRIC->next) != null);

	if ((_hoops_CIRIC = _hoops_IIRHA->_hoops_IPPGR) != null) do {
		if (_hoops_CIRIC->type >= type) {
			if (_hoops_CIRIC->type > type)
				_hoops_CIRIC = null;
			break;
		}
	} while ((_hoops_CIRIC = _hoops_CIRIC->next) != null);

	if (_hoops_IIRIC == null && _hoops_CIRIC == null) {}
	else if (_hoops_IIRIC == null || _hoops_CIRIC == null)
		return false;
	else if (!_hoops_HIRIC (_hoops_ARCAR, _hoops_IIRIC, _hoops_CIRIC))
		return false;

	/* _hoops_HCR _hoops_IHRI */

	return true;
}

local Attribute * _hoops_SIAIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP const *		_hoops_SRCP,
	int					type) {
	Attribute *			_hoops_HPHCR;

	if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) do {
		if (_hoops_HPHCR->type >= type) {
			if (_hoops_HPHCR->type == type) {
				_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_HPHCR);
				return _hoops_HPHCR;
			}
			break;
		}
	} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

	return null;
}


#define _hoops_GCAIC	_hoops_CRCCA


local void _hoops_RCAIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP const *		_hoops_SRCP,
	_hoops_PGSHC **	_hoops_ACAIC,
	int *				_hoops_ICI) {
	Attribute const *	_hoops_HPHCR;
	Subsegment const *	_hoops_GIPIA;

	if (/* !_hoops_IRRC (_hoops_PHHIP->_hoops_CPGC, _hoops_PCAIC) && */
		(_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) do {
		int						type = (int)_hoops_HPHCR->type;
		_hoops_PGSHC **		_hoops_ASRGR = &_hoops_ACAIC[type];
		_hoops_PGSHC *		ref;

		if (_hoops_ICI[type] < _hoops_SCIHC) {
			if (_hoops_HPHCR->type == HK_COLOR) {
				_hoops_PGSHC **	_hoops_HCAIC = (_hoops_PGSHC **)_hoops_ACAIC[HK_COLOR];
				int					_hoops_ICAIC;

				_hoops_ICAIC = _hoops_AHAIC ((_hoops_SSGI const *)_hoops_HPHCR);
				_hoops_ASRGR = &_hoops_HCAIC[_hoops_ICAIC];
			}
			if (_hoops_HPHCR->type == HK_MODELLING_MATRIX) {
				_hoops_PGSHC **	_hoops_CCAIC = (_hoops_PGSHC **)_hoops_ACAIC[HK_MODELLING_MATRIX];
				int					_hoops_ICAIC;

				_hoops_ICAIC = _hoops_PHAIC ((_hoops_ISGI const *)_hoops_HPHCR);
				_hoops_ASRGR = &_hoops_CCAIC[_hoops_ICAIC];
			}

			if ((ref = *_hoops_ASRGR) != null) do {
				if (_hoops_HIRIC (_hoops_ARCAR, _hoops_HPHCR, ref->_hoops_ASGPR))
					break;
			} while ((ref = ref->next) != null);

			if (ref == null) {
				POOL_ALLOC (ref, _hoops_PGSHC, _hoops_ARCAR->memory_pool);
				ref->_hoops_ASGPR = _hoops_HPHCR;
				ref->next = *_hoops_ASRGR;
				*_hoops_ASRGR = ref;

				++_hoops_ICI[type];
			}
		}
	} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP)
			_hoops_RCAIC (_hoops_ARCAR, _hoops_SSIGP (_hoops_GIPIA), _hoops_ACAIC, _hoops_ICI);
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}

local void _hoops_SCAIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP const *		_hoops_SRCP,
	int *				_hoops_GSAIC,
	int *				_hoops_RSAIC) {
	_hoops_PGSHC *	_hoops_ACAIC[_hoops_GCAIC];
	int					_hoops_ICI[_hoops_GCAIC];
	int					_hoops_ARPPH;
	Subsegment const *	_hoops_GIPIA;
	int					count = 0;
	_hoops_PGSHC *	_hoops_HCAIC[_hoops_SPAIC];
	_hoops_PGSHC *	_hoops_CCAIC[_hoops_SPAIC];

	ZERO_ARRAY (_hoops_ACAIC, _hoops_GCAIC, _hoops_PGSHC *);
	ZERO_ARRAY (_hoops_ICI, _hoops_GCAIC, int);
	/* _hoops_SGH _hoops_IRS _hoops_SHSC _hoops_SCAH _hoops_GASR _hoops_IH _hoops_PSHA & _hoops_HCIA _hoops_RIIA _hoops_IIGR _hoops_IRS _hoops_IHGP _hoops_HIGR */
	ZERO_ARRAY (_hoops_HCAIC, _hoops_SPAIC, _hoops_PGSHC *);
	_hoops_ACAIC[HK_COLOR] = (_hoops_PGSHC *)_hoops_HCAIC;
	ZERO_ARRAY (_hoops_CCAIC, _hoops_SPAIC, _hoops_PGSHC *);
	_hoops_ACAIC[HK_MODELLING_MATRIX] = (_hoops_PGSHC *)_hoops_CCAIC;

	/* _hoops_GA'_hoops_RA _hoops_RPR _hoops_AIRC _hoops_GPP _hoops_RH _hoops_SRRPR _hoops_CAGH */
	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP &&
			!BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_PACHC))
			_hoops_RCAIC (_hoops_ARCAR, _hoops_SSIGP (_hoops_GIPIA), _hoops_ACAIC, _hoops_ICI);
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	/* _hoops_PSP _hoops_RPIP _hoops_RRP _hoops_CGRPR _hoops_AIRC */
	/* _hoops_HIH _hoops_AIRP _hoops_IH _hoops_ASAIC & _hoops_PSAIC)_hoops_HSAIC _hoops_CHR _hoops_PAII _hoops_HAII _hoops_PIRRR, _hoops_CASI & _hoops_RAIPR _hoops_SRS */
	for (int i=0; i<_hoops_SPAIC; i++) {
		_hoops_PGSHC *		ref;

		while ((ref = _hoops_HCAIC[i]) != null) {
			_hoops_HCAIC[i] = ref->next;
			FREE (ref, _hoops_PGSHC);
		}
		while ((ref = _hoops_CCAIC[i]) != null) {
			_hoops_CCAIC[i] = ref->next;
			FREE (ref, _hoops_PGSHC);
		}
	}
	_hoops_ACAIC[HK_COLOR] = null;
	_hoops_ACAIC[HK_MODELLING_MATRIX] = null;
	/* _hoops_HA _hoops_RH _hoops_SHISR _hoops_ARIPR */
	for (int i=0; i<_hoops_GCAIC; i++) {
		_hoops_PGSHC *		ref;

		while ((ref = _hoops_ACAIC[i]) != null) {
			_hoops_ACAIC[i] = ref->next;
			FREE (ref, _hoops_PGSHC);
		}
	}

	/* _hoops_CGSI _hoops_SGS _hoops_IIP _hoops_HASC */
	_hoops_ICI[(int)HK_WINDOW] = 0;

	/* _hoops_CGSI _hoops_SGS _hoops_CHR _hoops_PPPHR _hoops_PPR _hoops_CGH _hoops_SHH _hoops_CPHR _hoops_GGR _hoops_GAR _hoops_CIAGR _hoops_CPAAR (_hoops_SHCAR, _hoops_GAR _hoops_RSIH) _hoops_GAR _hoops_SSRR */
	if (_hoops_ICI[(int)HK_HEURISTICS] > 0) {
		_hoops_GSAIC[count++] = HK_HEURISTICS;
		_hoops_ICI[(int)HK_HEURISTICS] = 0;
	}
	if (_hoops_ICI[(int)_hoops_CPPIR] > 0) {
		_hoops_GSAIC[count++] = _hoops_CPPIR;
		_hoops_ICI[(int)_hoops_CPPIR] = 0;
	}
	if (_hoops_ICI[(int)HK_CLIP_REGION] > 0) {
		_hoops_GSAIC[count++] = HK_CLIP_REGION;
		_hoops_ICI[(int)HK_CLIP_REGION] = 0;
	}
	if (_hoops_ICI[(int)_hoops_IPAIR] > 0) {
		_hoops_GSAIC[count++] = _hoops_IPAIR;
		_hoops_ICI[(int)_hoops_IPAIR] = 0;
	}
	if (_hoops_ICI[(int)_hoops_RPAIR] > 0) {
		_hoops_GSAIC[count++] = _hoops_RPAIR;
		_hoops_ICI[(int)_hoops_RPAIR] = 0;
	}
	if (_hoops_ICI[(int)_hoops_RAAIR] > 0) {
		_hoops_GSAIC[count++] = _hoops_RAAIR;
		_hoops_ICI[(int)_hoops_RAAIR] = 0;
	}
	if (_hoops_ICI[(int)HK_COLOR_MAP] > 0) {
		_hoops_GSAIC[count++] = HK_COLOR_MAP;
		_hoops_ICI[(int)HK_COLOR_MAP] = 0;
	}
	if (_hoops_ICI[(int)HK_HANDEDNESS] > 0) {
		_hoops_GSAIC[count++] = HK_HANDEDNESS;
		_hoops_ICI[(int)HK_HANDEDNESS] = 0;
	}

	/* _hoops_RISA _hoops_RAPR _hoops_IS _hoops_SGH _hoops_GHSHA _hoops_GHIS */
	_hoops_PCCAR {
		_hoops_ARPPH = -1;
		for (int i=0; i<_hoops_GCAIC; i++) {
			if (_hoops_ICI[i] != 0) {
				if (_hoops_ARPPH < 0 || _hoops_ICI[i] < _hoops_ICI[_hoops_ARPPH])
					_hoops_ARPPH = i;
			}
		}

		if (_hoops_ARPPH < 0)
			break;

		if (_hoops_ICI[_hoops_ARPPH] == _hoops_ARCAR->_hoops_GGSHC)
			break;

		_hoops_GSAIC[count++] = _hoops_ARPPH;

		_hoops_ICI[_hoops_ARPPH] = 0;
	}

	*_hoops_RSAIC = count;
}









local int _hoops_ISAIC (
	_hoops_PHIP *	_hoops_RRA) {
	int						types = 0;

	if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
		_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];
		Geometry const *	g = _hoops_SRCP->geometry;

		while (g != null) {
			if (_hoops_RRA->_hoops_RGPGR & _hoops_AGPGR(g->type)) {
				types |= _hoops_AGPGR(g->type);

				if (g->type == _hoops_AHIP) {
					_hoops_PHIP *	_hoops_CSAIC = (_hoops_PHIP *)g;

					if (_hoops_CSAIC->_hoops_RGPGR == ~0)
						types |= _hoops_ISAIC(_hoops_CSAIC);
					else
						types |= _hoops_CSAIC->_hoops_RGPGR;

					g = g->next;
				}
				else
					_hoops_PGPGR (g, g->type);
			}
			else
				_hoops_PGPGR (g, g->type);
		}
	}
	else {
		for (int ii=0; ii<_hoops_RRA->_hoops_HHIP; ii++) {
			Geometry const *	g = (Geometry const *)_hoops_RRA->_hoops_IHIP[ii];

			if (_hoops_RRA->_hoops_RGPGR & _hoops_AGPGR(g->type)) {
				types |= _hoops_AGPGR(g->type);

				if (g->type == _hoops_AHIP) {
					_hoops_PHIP *	_hoops_CSAIC = (_hoops_PHIP *)g;

					if (_hoops_CSAIC->_hoops_RGPGR == ~0)
						types |= _hoops_ISAIC(_hoops_CSAIC);
					else
						types |= _hoops_CSAIC->_hoops_RGPGR;
				}
			}
		}
	}

	return types;
}

local _hoops_PHIP * _hoops_SSAIC(
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			owner,
	int					_hoops_RGPGR)
{
	ASSERT(BIT(_hoops_ARCAR->flags, _hoops_PRCHC));
	UNREFERENCED(_hoops_ARCAR);

	_hoops_PHIP * _hoops_RRA;
	ZALLOC (_hoops_RRA, _hoops_PHIP);
	_hoops_RRA->type = _hoops_AHIP;
	_hoops_RRA->_hoops_RRHH = _hoops_IIHIR;
	_hoops_RRA->_hoops_HIHI = 1;
	_hoops_RRA->owner = owner;
	_hoops_RRA->key = _hoops_AIRIR (_hoops_RRA);
	_hoops_RRA->_hoops_CPGPR |= _hoops_CASIR;
	_hoops_RRA->_hoops_RGPGR = _hoops_RGPGR;

	return _hoops_RRA;
}

local void _hoops_GGPIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				node,
	_hoops_PHIP *	_hoops_RGPIC)
{
	_hoops_CRCP *	owner = _hoops_HASHC (_hoops_ARCAR, node->owner, "unroll reference");
	if (_hoops_RGPIC->_hoops_IPPGR != null || node->_hoops_IPPGR != null)
		_hoops_IGRIC (_hoops_ARCAR, owner, node->_hoops_IPPGR, _hoops_RGPIC->_hoops_IPPGR);

	_hoops_GRGGI *	gl = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_GRGGI) (_hoops_ARCAR->memory_pool);

	_hoops_CRCP const *	_hoops_AGPIC;

	if (_hoops_RGPIC->_hoops_IHIP[0]->type == _hoops_IRCP) {
		_hoops_AGPIC = (_hoops_CRCP const *)_hoops_RGPIC->_hoops_IHIP[0];
		ASSERT(!BIT(_hoops_AGPIC->_hoops_RRHH, _hoops_HIRIR));

		_hoops_CRCP const *	_hoops_SRCP = (_hoops_CRCP const *)_hoops_RGPIC->_hoops_IHIP[0];
		Geometry *		g = _hoops_SRCP->geometry;

		while (g != null) {
			if (_hoops_RGPIC->_hoops_RGPGR & _hoops_AGPGR(g->type)) {
				if (g->type == _hoops_AHIP) {
					_hoops_GGPIC (_hoops_ARCAR, owner, (_hoops_PHIP *)g);
				}
				else
					gl->AddFirst(g);

				g = g->next;
			}
			else
				_hoops_PGPGR (g, g->type);
		}
	}
	else {
		_hoops_AGPIC = (_hoops_CRCP const *)_hoops_RGPIC->_hoops_IHIP[0]->owner;
		ASSERT(!BIT(_hoops_AGPIC->_hoops_RRHH, _hoops_HIRIR));

		for (int i=0; i<_hoops_RGPIC->_hoops_HHIP; i++) {
			Geometry *	g = (Geometry *)_hoops_RGPIC->_hoops_IHIP[i];
			if (_hoops_RGPIC->_hoops_RGPGR & _hoops_AGPGR(g->type)) {
				if (g->type == _hoops_AHIP)
					_hoops_GGPIC (_hoops_ARCAR, owner, (_hoops_PHIP *)g);
				else
					gl->AddFirst(g);
			}
		}
	}

	int _hoops_PGPIC = gl->Count();

	if (_hoops_PGPIC > 0) {
		// _hoops_SIGP: _hoops_IRHH _hoops_RGHP _hoops_SRRPR _hoops_RPP _hoops_RAGPR
		Geometry **	_hoops_ASRGR = &owner->geometry;

		_hoops_PHIP *	_hoops_RRA = _hoops_SSAIC(_hoops_ARCAR, node, ~0);

		// _hoops_SIGP: _hoops_IPS _hoops_HPAC

		_hoops_RRA->backlink = _hoops_ASRGR;
		if ((_hoops_RRA->next = *_hoops_ASRGR) != null)
			_hoops_RRA->next->backlink = &_hoops_RRA->next;
		*_hoops_ASRGR = _hoops_RRA;

		_hoops_RRA->_hoops_HHIP = _hoops_PGPIC;
		ALLOC_ARRAY (_hoops_RRA->_hoops_IHIP, _hoops_RRA->_hoops_HHIP, _hoops_SIHIR const *);

		for (int i=0; i<_hoops_PGPIC; i++) {
			Geometry * g = gl->RemoveFirst();
			_hoops_RRA->_hoops_IHIP[i] = (_hoops_SIHIR const *)g;
			_hoops_PRRH (g);
		}

		_hoops_RRA->_hoops_RGPGR = _hoops_ISAIC(_hoops_RRA);
		ASSERT(!BIT(_hoops_RRA->_hoops_RGPGR, _hoops_AGPGR(_hoops_AHIP)));
	}

	delete gl;
}


local _hoops_PHIP * _hoops_HGPIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_PHIP *	_hoops_RRA) {
	_hoops_CRCP *				node = _hoops_RRA->owner;
	Geometry *				geo = node->geometry;

	ASSERT(BIT(node->_hoops_RRHH, _hoops_HIRIR));

	while (geo) {
		ASSERT (geo->type == _hoops_AHIP);

		_hoops_RRA = (_hoops_PHIP *)geo;

		if (BIT(_hoops_RRA->_hoops_RGPGR, _hoops_AGPGR(_hoops_AHIP))) {
			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				Geometry *			g = ((_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0])->geometry;

				while (g) {
					if (g->type == _hoops_AHIP) {
						_hoops_GGPIC (_hoops_ARCAR, _hoops_RRA->owner, (_hoops_PHIP *)g);

						g = g->next;
					}
					else
						_hoops_PGPGR(g, g->type);
				}
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
					Geometry *		g = (Geometry *)_hoops_RRA->_hoops_IHIP[i];

					if (g->type == _hoops_AHIP)
						_hoops_GGPIC (_hoops_ARCAR, _hoops_RRA->owner, (_hoops_PHIP *)g);
				}
			}

			_hoops_RRA->_hoops_RGPGR = ~0 & ~_hoops_AGPGR(_hoops_AHIP);
			_hoops_RRA->_hoops_RGPGR = _hoops_ISAIC(_hoops_RRA);

			geo = _hoops_RRA->next;

			if (_hoops_RRA->_hoops_RGPGR == 0) {
				ASSERT(BIT(_hoops_RRA->owner->_hoops_RRHH, _hoops_HIRIR));
				_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_RRA);
				_hoops_HPRH(_hoops_RRA);
				_hoops_RRA = null;
			}
		}
		else
			geo = geo->next;
	}

	return _hoops_RRA;
}


local void _hoops_IGPIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				node,
	_hoops_CRCP const *			_hoops_SRCP)
{
	UNREFERENCED(_hoops_ARCAR);

	ASSERT(BIT(_hoops_ARCAR->flags, _hoops_PRCHC));
	ASSERT(!BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HIRIR));
	ASSERT(_hoops_SRCP->geometry != null);

#if 0
	if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "_0788b4d0")) {
		_hoops_ARCAR=_hoops_ARCAR;
	}
#endif

	_hoops_PHIP *	_hoops_RRA = _hoops_SSAIC(_hoops_ARCAR, node, ~0);

	ALLOC_ARRAY (_hoops_RRA->_hoops_IHIP, 1, _hoops_SIHIR const *);
	_hoops_RRA->_hoops_HHIP = 1;
	_hoops_RRA->_hoops_IHIP[0] = (_hoops_SIHIR const *)_hoops_SRCP;
	_hoops_PRRH (_hoops_SRCP);

	_hoops_RRA->_hoops_RGPGR = _hoops_ISAIC(_hoops_RRA);

	node->geometry = (Geometry *)_hoops_RRA;
	_hoops_RRA->backlink = &node->geometry;

	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_HHSI))
		node->_hoops_PHSI |= _hoops_HHSI;

	if (BIT(_hoops_RRA->_hoops_RGPGR, _hoops_AGPGR(_hoops_AHIP)))
		_hoops_RRA = _hoops_HGPIC (_hoops_ARCAR, _hoops_RRA);

	ASSERT(_hoops_RRA == null || _hoops_RRA->_hoops_RGPGR != 0);

	node->_hoops_RCGC |= _hoops_SRCP->_hoops_RCGC & (_hoops_IRHGP|_hoops_ASPCR|_hoops_ASRRA);
	node->owner->_hoops_RCGC |= node->_hoops_RCGC;
}


local void _hoops_CGPIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP,
	bool					_hoops_HCGIC) {

	ASSERT(BIT(_hoops_ARCAR->flags, _hoops_PRCHC));
	ASSERT(BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HIRIR));

	Geometry *				g;

#if 0
	if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 109177")) {
		_hoops_ARCAR=_hoops_ARCAR;
	}
#endif

	if ((g = _hoops_SRCP->geometry) != null) {
		_hoops_RPAPA **	_hoops_SGPIC = null;

		int		_hoops_GRPIC[] = {
					/* _hoops_GRRI-_hoops_SHSS _hoops_PPR _hoops_RRPIC */
					_hoops_AGPGR(_hoops_SCIP) | _hoops_AGPGR(_hoops_GSIP) | _hoops_AGPGR(_hoops_PRCP) | _hoops_AGPGR(_hoops_RCIP) |
						_hoops_AGPGR(_hoops_ASIP) | _hoops_AGPGR(_hoops_CSIP) | _hoops_AGPGR(_hoops_HSIP),

					/* _hoops_GRRI-_hoops_SHSS */
					_hoops_AGPGR(_hoops_PIIP) | _hoops_AGPGR(_hoops_HIIP) | _hoops_AGPGR(_hoops_IIIP),

					~0 // _hoops_HIASR _hoops_HIGR _hoops_PIHA _hoops_SHH _hoops_CGHI
				};

		int		_hoops_ARPIC = _hoops_GGAPR(_hoops_GRPIC);

		POOL_ZALLOC_ARRAY(_hoops_SGPIC, _hoops_ARPIC, _hoops_RPAPA *, _hoops_ARCAR->memory_pool);

		do {
			ASSERT(g->type == _hoops_AHIP);

			_hoops_PHIP *	_hoops_RRA = (_hoops_PHIP *)g;

			for (int i=0; i<_hoops_ARPIC; i++) {
				if (ANYBIT(_hoops_RRA->_hoops_RGPGR, _hoops_GRPIC[i])) {
					if (_hoops_SGPIC[i] == null)
						_hoops_SGPIC[i] = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_RPAPA)(_hoops_ARCAR->memory_pool);
					_hoops_SGPIC[i]->AddFirst(_hoops_RRA);
					break;
				}
			}
		} while ((g = g->next) != null);


		for (int i=0; i<_hoops_ARPIC; i++) {
            if (_hoops_SGPIC[i] != null) {
				_hoops_RHRHH (_hoops_ARCAR->_hoops_RIGC, _hoops_ARCAR->_hoops_RGSHC, "defer group %d", i);
				_hoops_CRCP *	_hoops_PRPIC = _hoops_HASHC(_hoops_ARCAR, _hoops_SRCP, _hoops_ARCAR->_hoops_RGSHC, _hoops_SACHC);

				// _hoops_ASIGA _hoops_CGH _hoops_SHH _hoops_SHSS _hoops_IS _hoops_RGRR _hoops_SGHGP _hoops_HPP _hoops_GPRR _hoops_IGGHA
				HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, _hoops_PRPIC, _hoops_SRCP->_hoops_RCGC);

				if (i > 0) {
					_hoops_GHAIR *	heuristics;
					ZALLOC (heuristics, _hoops_GHAIR);
					heuristics->mask |= _hoops_APIRP;
					heuristics->value |= _hoops_APIRP;
					heuristics->_hoops_RRCRP = i*1000;

					if (!HI_Set_Heuristics (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_PRPIC, heuristics)) {
						ASSERT(0); // _hoops_CGH _hoops_HAR _hoops_IHPS
						FREE (heuristics, _hoops_GHAIR);
					}
				}


				_hoops_PHIP *	_hoops_RRA;

				while ((_hoops_RRA = _hoops_SGPIC[i]->RemoveFirst()) != null) {
					int					_hoops_HRPIC = 0;

					_hoops_RHGIC(_hoops_RRA, ~_hoops_GRPIC[i], &_hoops_HRPIC, null, true);

					if (_hoops_HRPIC > 0) {
						_hoops_CRCP const *		_hoops_AGPIC;

						if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP)
							_hoops_AGPIC = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];
						else
							_hoops_AGPIC = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0]->owner;

						_hoops_PHIP *	_hoops_APIS = _hoops_SSAIC(_hoops_ARCAR, _hoops_RRA->owner, ~_hoops_GRPIC[i]&_hoops_RRA->_hoops_RGPGR);

						// _hoops_HSRPA _hoops_RAS _hoops_IRPIC
						if (_hoops_RRA->next)
							_hoops_RRA->next->backlink = &_hoops_APIS->next;
						_hoops_APIS->next = _hoops_RRA->next;
						_hoops_RRA->next = _hoops_APIS;
						_hoops_APIS->backlink = &_hoops_RRA->next;

						if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
							ALLOC_ARRAY (_hoops_APIS->_hoops_IHIP, 1, _hoops_SIHIR const *);
							_hoops_APIS->_hoops_HHIP = 1;
							_hoops_APIS->_hoops_IHIP[0] = (_hoops_SIHIR const *)_hoops_AGPIC;
							_hoops_PRRH (_hoops_AGPIC);
						}
						else {
							_hoops_APIS->_hoops_HHIP = _hoops_HRPIC;
							ALLOC_ARRAY (_hoops_APIS->_hoops_IHIP, _hoops_HRPIC, _hoops_SIHIR const *);

							_hoops_SIHIR const **_hoops_CRPIC;
							ALLOC_ARRAY (_hoops_CRPIC, _hoops_RRA->_hoops_HHIP-_hoops_HRPIC, _hoops_SIHIR const *);

							int _hoops_SRPIC = 0;
							int _hoops_GAPIC = 0;

							for (int ii=0; ii<_hoops_RRA->_hoops_HHIP; ii++) {
								int	type = _hoops_AGPGR(_hoops_RRA->_hoops_IHIP[ii]->type) & _hoops_RRA->_hoops_RGPGR;
								ASSERT(type != 0);

								if (BIT(type, _hoops_GRPIC[i]))
									_hoops_CRPIC[_hoops_GAPIC++]=_hoops_RRA->_hoops_IHIP[ii];
								else {
									_hoops_APIS->_hoops_IHIP[_hoops_SRPIC++]=_hoops_RRA->_hoops_IHIP[ii];
								}
							}

							FREE_ARRAY (_hoops_RRA->_hoops_IHIP, _hoops_RRA->_hoops_HHIP, _hoops_SIHIR const *);
							_hoops_RRA->_hoops_IHIP = _hoops_CRPIC;
							_hoops_RRA->_hoops_HHIP -= _hoops_HRPIC;
						}

						// _hoops_HGIHR _hoops_RHGS _hoops_PAGGR _hoops_GGCR _hoops_SCH _hoops_IS _hoops_IGGHA _hoops_HIGR _hoops_IH _hoops_PCPA _hoops_IGICR
						_hoops_RRA->_hoops_RGPGR &= ~_hoops_APIS->_hoops_RGPGR;

						for (int j=i+1; j<_hoops_ARPIC; j++) {
							if (ANYBIT(_hoops_APIS->_hoops_RGPGR, _hoops_GRPIC[j])) {
								if (_hoops_SGPIC[j] == null)
									_hoops_SGPIC[j] = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_RPAPA)(_hoops_ARCAR->memory_pool);
								_hoops_SGPIC[j]->AddFirst(_hoops_APIS);
								break;
							}
						}

#ifdef HOOPS_DEBUG_BUILD
						int		count = 0;
						_hoops_RHGIC(_hoops_APIS, ~0, &count);
						ASSERT(count > 0);
#endif
					}

#ifdef HOOPS_DEBUG_BUILD
					int		count = 0;
					_hoops_RHGIC(_hoops_RRA, ~0, &count);
					ASSERT(count > 0);
#endif
					_hoops_GRAPA (_hoops_ARCAR, _hoops_RRA, _hoops_PRPIC, true);
				}

				ASSERT(_hoops_PRPIC->geometry != null);

				delete _hoops_SGPIC[i];
			}
		}

		FREE_ARRAY(_hoops_SGPIC, _hoops_ARPIC, _hoops_RPAPA *);
	}

	Subsegment *	_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;

	if (_hoops_GIPIA != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP) {
			if (BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_SACHC))
				_hoops_GIPIA->_hoops_RRHH &= ~_hoops_SACHC;
			else if (_hoops_HCGIC || !BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_PACHC))
				_hoops_CGPIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA, _hoops_HCGIC);
		}
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}


struct _hoops_RAPIC {
	_hoops_RAPIC *		next;
	_hoops_CRCP *				s;
	_hoops_PGRPR *				i;
	_hoops_PHIP *	r;
	Geometry *				g;
	float					t;
	int						_hoops_IGCPA;
};

typedef VHash<_hoops_PHIP *, _hoops_GRGGI *> _hoops_AAPIC;
typedef VHash<_hoops_CRCP *, _hoops_GRGGI *> _hoops_PAPIC;
typedef VHash<_hoops_CRCP *, _hoops_RPAPA *> _hoops_HAPIC;

local _hoops_RAPIC * _hoops_IAPIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	Bounding const &		bounding,
	_hoops_CRCP *				segment,
	_hoops_PGRPR *				include,
	_hoops_PHIP *	_hoops_CSAGR,
	Geometry *				geometry,
	_hoops_RAPIC **		_hoops_ASRGR) {

	if (!bounding._hoops_HICAR()) {
		//_hoops_AIIC	_hoops_RA = _hoops_IASC._hoops_IGGRR();
		//_hoops_RA *= _hoops_IASC._hoops_CAPIC();

		float	t = bounding._hoops_SGCIR();
		Vector	d = bounding->cuboid.max - bounding->cuboid.min;

		if (d.x > d.y) {
			t *= d.x;
			if (d.y > d.z)
				t *= d.y;
			else
				t *= d.z;
		}
		else {
			t *= d.y;
			if (d.x > d.z)
				t *= d.x;
			else
				t *= d.z;
		}

		// _hoops_HPPR _hoops_IS _hoops_HGCR _hoops_HICHH _hoops_PPR _hoops_SSGRH _hoops_GHC _hoops_IS _hoops_SHH _hoops_GCRHA
		// _hoops_CHAA _hoops_GGR _hoops_SAPIC _hoops_IIGR _hoops_GPIC _hoops_APSAR
		int		c = 0;

		if (d.x == 0.0f)
			c++;
		if (d.y == 0.0f)
			c++;
		if (d.z == 0.0f)
			c++;

		if (c == 1)
			t *= 2;


		_hoops_RAPIC *	x;

		POOL_ZALLOC(x, _hoops_RAPIC, _hoops_ARCAR->memory_pool);

		x->next = *_hoops_ASRGR;
		x->i = include;
		x->g = geometry;
		x->s = segment;
		x->r = _hoops_CSAGR;
		x->t = t;

		*_hoops_ASRGR = x;
		return x;
	}

	return null;
}

local void _hoops_GPPIC(
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				segment,
	_hoops_PHIP *	_hoops_CSAGR,
	Geometry *				g,
	int						_hoops_RGPGR,
	_hoops_RAPIC **		_hoops_ASRGR,
	bool					single) {

	int _hoops_RPPIC = _hoops_AGPGR(_hoops_RCIP)|_hoops_AGPGR(_hoops_GSIP)|_hoops_AGPGR(_hoops_SCIP)|_hoops_AGPGR(_hoops_CSIP)|_hoops_AGPGR(_hoops_AHIP);

	while (g != null) {
		Type	type = g->type;

		if (!BIT (_hoops_RGPGR, _hoops_AGPGR(type))) {
			_hoops_PGPGR (g, g->type);
			if (single || g == null)
				goto _hoops_PRSPR;
		}
		else switch (type) {
			case _hoops_RCIP: {
				do {
					Bounding	_hoops_SCIIA;
					HI_Figure_Geometry_Bounding (g, _hoops_SCIIA);

					if (!_hoops_SCIIA._hoops_HICAR())
						_hoops_IAPIC(_hoops_ARCAR, _hoops_SCIIA, segment, null, _hoops_CSAGR, g, _hoops_ASRGR);

					if (single)
						goto _hoops_PRSPR;
				} while (((g = g->next) != null) && g->type == type);
			} break;

			case _hoops_GSIP:
			case _hoops_SCIP: {
				do {
					Polyhedron *	phon = (Polyhedron *)g;

					if (phon->bounding._hoops_HICAR()) {
						_hoops_RAPIC *	x;

						POOL_ZALLOC(x, _hoops_RAPIC, _hoops_ARCAR->memory_pool);

						x->next = *_hoops_ASRGR;
						x->g = g;
						x->s = segment;
						x->r = _hoops_CSAGR;
						x->t = -1.0f;

						*_hoops_ASRGR = x;
					}
					else
						_hoops_IAPIC(_hoops_ARCAR, phon->bounding, segment, null,
														_hoops_CSAGR, g, _hoops_ASRGR);

					if (single)
						goto _hoops_PRSPR;
				} while (((g = g->next) != null) && g->type == type);
			} break;

			case _hoops_CSIP: {
				do {
					PolyCylinder *	_hoops_HARIR = (PolyCylinder *)g;

					if (_hoops_HARIR->bounding._hoops_HICAR()) {
						_hoops_RAPIC *	x;

						POOL_ZALLOC(x, _hoops_RAPIC, _hoops_ARCAR->memory_pool);

						x->next = *_hoops_ASRGR;
						x->g = g;
						x->s = segment;
						x->r = _hoops_CSAGR;
						x->t = -1.0f;

						*_hoops_ASRGR = x;
					}
					else
						_hoops_IAPIC(_hoops_ARCAR, _hoops_HARIR->bounding, segment, null,
														_hoops_CSAGR, g, _hoops_ASRGR);

					if (single)
						goto _hoops_PRSPR;
				} while (((g = g->next) != null) && g->type == type);
			} break;

			case _hoops_AHIP: {
				do {
					_hoops_PHIP *	_hoops_RRA = (_hoops_PHIP *)g;

					if (ANYBIT(_hoops_RPPIC, _hoops_RRA->_hoops_RGPGR&_hoops_RGPGR)) {
						if (BIT(_hoops_RRA->owner->_hoops_RRHH, _hoops_HIRIR)) {
							if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
								_hoops_CRCP *		_hoops_SRCP = (_hoops_CRCP *)_hoops_RRA->_hoops_IHIP[0];

								_hoops_GPPIC(_hoops_ARCAR, segment, _hoops_RRA, _hoops_SRCP->geometry, _hoops_RGPGR & _hoops_RRA->_hoops_RGPGR, _hoops_ASRGR, false);
							}
							else {
								for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
									Geometry *		geo = (Geometry *)_hoops_RRA->_hoops_IHIP[i];

									_hoops_GPPIC(_hoops_ARCAR, segment, _hoops_RRA, geo, _hoops_RGPGR & _hoops_RRA->_hoops_RGPGR, _hoops_ASRGR, true);
								}
							}
						}
						else {
							_hoops_IAPIC(_hoops_ARCAR, _hoops_RRA->bounding, segment, null,
								_hoops_CSAGR, g, _hoops_ASRGR);
						}
					}

					if (single)
						goto _hoops_PRSPR;
				} while (((g = g->next) != null) && g->type == type);
			} break;

			default: {
				do {
					if (single)
						goto _hoops_PRSPR;
				} while (((g = g->next) != null) && g->type == type);
			} break;
		}
	}
_hoops_PRSPR:;
}



local void _hoops_APPIC(
	_hoops_ICCHC *		_hoops_ARCAR,
	Geometry *				g,
	_hoops_CRCP *				_hoops_SRCP,
	const char *			name,
	_hoops_SSGI *					color) {
	_hoops_CRCP *				_hoops_HHGSA = _hoops_HASHC(_hoops_ARCAR, _hoops_SRCP, name, _hoops_SACHC|_hoops_IACHC);

	if (color) {
		if (!HI_Set_Color(_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_HHGSA, color)) {
			ASSERT(0); // _hoops_RGR _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_CCHCP
			HI_Free_Colors (color->colors);
			FREE (color, _hoops_SSGI);
		}
	}
	else
		_hoops_HHGSA->_hoops_RRHH |= _hoops_PACHC;

	_hoops_PHIP *	_hoops_RRA = _hoops_SSAIC(_hoops_ARCAR, _hoops_HHGSA, _hoops_AGPGR(g->type));

	_hoops_RRA->_hoops_HHIP = 1;
	ALLOC_ARRAY (_hoops_RRA->_hoops_IHIP, 1, _hoops_SIHIR const *);
	_hoops_RRA->_hoops_IHIP[0] = (_hoops_SIHIR const *)g;
	_hoops_PRRH (g);

	_hoops_GHSHC (_hoops_ARCAR, _hoops_RRA, _hoops_HHGSA, true);
}


local void _hoops_PPPIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	Geometry *				g,
	_hoops_CRCP *				_hoops_SRCP) {
	_hoops_CRCP *				_hoops_HHGSA = _hoops_HASHC(_hoops_ARCAR, _hoops_SRCP, "", _hoops_SACHC);

	if (g->_hoops_IPPGR != null) {
		_hoops_HHGSA->_hoops_IPPGR = HI_Clone_Attributes(_hoops_ARCAR->_hoops_RIGC, g->_hoops_IPPGR, _hoops_HHGSA, true, null);
		_hoops_HHGSA->_hoops_IPPGR->backlink = &_hoops_HHGSA->_hoops_IPPGR;
	}

	Attribute *		_hoops_ASGPR = _hoops_HHGSA->_hoops_IPPGR;

	while (_hoops_ASGPR) {
		Attribute *	next = _hoops_ASGPR->next;

		if (_hoops_ASGPR->type == HK_MODELLING_MATRIX) {
			_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_ASGPR);
			_hoops_HPRH (_hoops_ASGPR);
		}

		_hoops_ASGPR = next;
	}

	_hoops_PHIP *	_hoops_RRA = _hoops_SSAIC(_hoops_ARCAR, _hoops_HHGSA, _hoops_AGPGR(g->type));

	_hoops_RRA->_hoops_HHIP = 1;
	ALLOC_ARRAY (_hoops_RRA->_hoops_IHIP, 1, _hoops_SIHIR const *);
	_hoops_RRA->_hoops_IHIP[0] = (_hoops_SIHIR const *)g;
	_hoops_PRRH (g);

	_hoops_GHSHC (_hoops_ARCAR, _hoops_RRA, _hoops_HHGSA, true);
}

local bool _hoops_HPPIC(Attribute * _hoops_IPPGR)
{

	while (_hoops_IPPGR != null) {
		if (_hoops_IPPGR->type != HK_USER_OPTIONS &&
			_hoops_IPPGR->type != HK_USER_VALUE)
			return true;

		_hoops_IPPGR = _hoops_IPPGR->next;
	}

	return false;
}

local void _hoops_IPPIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP,
	bool				_hoops_HCGIC) {
	Geometry *			geo;
	Geometry *			_hoops_CPPIC;

	ASSERT(BIT(_hoops_ARCAR->flags, _hoops_PRCHC));
	ASSERT(BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HIRIR));

	if ((geo = _hoops_SRCP->geometry) != null) do {
		_hoops_CPPIC = geo->next;

		if (geo->type == _hoops_AHIP) {
			_hoops_PPCHC *		_hoops_RCRC = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_PPCHC)(_hoops_ARCAR->memory_pool);
			_hoops_PHIP *	_hoops_RRA = (_hoops_PHIP *)geo;

			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP *	_hoops_AGPIC = (_hoops_CRCP *)_hoops_RRA->_hoops_IHIP[0];
				Geometry *	g = _hoops_AGPIC->geometry;
				int			_hoops_SPPIC = 0;

				while (g != null) {
					Type	type = g->type;

					if (!BIT (_hoops_AGPGR(type), _hoops_RRA->_hoops_RGPGR)) {
						_hoops_PGPGR (g, g->type);
					}
					else {
						do {
							_hoops_SPPIC++;

							if (g->_hoops_IPPGR != null &&
								g->type != _hoops_AHIP &&
								_hoops_HPPIC(g->_hoops_IPPGR)) {

								_hoops_PPPIC(_hoops_ARCAR, g, _hoops_SRCP);
								_hoops_RCRC->InsertItem(g, 1);
							}
							else switch (g->type) {
								case _hoops_GSIP:
								case _hoops_SCIP: {
									Polyhedron *	phon = (Polyhedron *)g;
									Local_Face_Attributes *	_hoops_CPRI = &phon->local_face_attributes;

									if (phon->face_count > 0) {
										if (_hoops_CPRI->_hoops_PSRRA == phon->face_count) {
											_hoops_ACGHR index = _hoops_CPRI->findices[0];

											int ii;

											for (ii=1; ii<phon->face_count; ii++) {
												if (index != _hoops_CPRI->findices[ii])
													break;
											}

											if (ii == phon->face_count) {
												_hoops_SSGI * _hoops_APRRA;
												ZALLOC (_hoops_APRRA, _hoops_SSGI);

												_hoops_PCSGA * findex;
												ZALLOC (findex, _hoops_PCSGA);

												findex->value = index;
												findex->type = _hoops_SHGRA;
												_hoops_APRRA->_hoops_GHA = _hoops_APRRA->_hoops_CCCIR = findex->_hoops_GHA = Color_FACE;
												_hoops_APRRA->colors = findex;
												_hoops_APRRA->_hoops_RRHH |= _hoops_SACHC;

												_hoops_APPIC(_hoops_ARCAR, g, _hoops_SRCP, "shell color", _hoops_APRRA);
											}
											else
												_hoops_APPIC(_hoops_ARCAR, g, _hoops_SRCP, "isolated color", null);

											_hoops_RCRC->InsertItem(g, 1);
										}
										else if (_hoops_CPRI->_hoops_HSRRA == phon->face_count) {
											RGB	c = _hoops_CPRI->colors[0];
											int ii;

											for (ii=1; ii<phon->face_count; ii++) {
												if (c != _hoops_CPRI->colors[ii])
													break;
											}

											if (ii == phon->face_count) {
												_hoops_SSGI * _hoops_APRRA;
												ZALLOC (_hoops_APRRA, _hoops_SSGI);

												_hoops_HCSGA *	_hoops_ICSGA;
												ZALLOC (_hoops_ICSGA, _hoops_HCSGA);

												_hoops_ICSGA->_hoops_ISHIR._hoops_CSHR = c;
												_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA = M_DIFFUSE;
												_hoops_ICSGA->type = _hoops_GIGRA;
												_hoops_APRRA->_hoops_GHA = _hoops_APRRA->_hoops_CCCIR = _hoops_ICSGA->_hoops_GHA = Color_FACE;
												_hoops_APRRA->colors = _hoops_ICSGA;
												_hoops_APRRA->_hoops_RRHH |= _hoops_SACHC;

												_hoops_APPIC(_hoops_ARCAR, g, _hoops_SRCP, "shell color", _hoops_APRRA);
												_hoops_RCRC->InsertItem(g, 1);
											}
										}
									}
								}	break;

								default:	break;
							}
						} while ((g = g->next) != null && g->type == type);
					}
				}


				int _hoops_GHPIC = _hoops_RCRC->Count();

				if (_hoops_GHPIC > 0) {
					if (_hoops_GHPIC == _hoops_SPPIC) {
						ASSERT(!_hoops_RRA->_hoops_IPPGR);
						ASSERT(_hoops_SRCP->_hoops_GACP == null);

						_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_RRA);
						_hoops_HPRH(_hoops_RRA);
					}
					else {
						// _hoops_CICA _hoops_IS _hoops_GSIPR-_hoops_PAGGR _hoops_IH _hoops_HHRPA _hoops_CIPH
						_hoops_SIHIR const **	_hoops_IHIP;
						int					_hoops_RHPIC	= _hoops_SPPIC - _hoops_GHPIC;
						int					n = 0;

						ALLOC_ARRAY (_hoops_IHIP, _hoops_RHPIC, _hoops_SIHIR const *);

						Geometry *	g = _hoops_AGPIC->geometry;

						while (g != null) {
							Type	type = g->type;

							if (!BIT (_hoops_AGPGR(type), _hoops_RRA->_hoops_RGPGR)) {
								_hoops_PGPGR (g, g->type);
							}
							else do {
								if (!_hoops_RCRC->LookupItem(g)) {
									_hoops_IHIP[n++] = (_hoops_SIHIR const *) g;
									_hoops_PRRH (g);
								}
							} while (((g = g->next) != null) && g->type == type);
						}

						ASSERT(n == _hoops_RHPIC);

						_hoops_HPRH (_hoops_AGPIC);
						FREE_ARRAY (_hoops_RRA->_hoops_IHIP, _hoops_RRA->_hoops_HHIP, _hoops_SIHIR const *);

						_hoops_RRA->_hoops_IHIP = _hoops_IHIP;
						_hoops_RRA->_hoops_HHIP = _hoops_RHPIC;
					}
				}
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
					Geometry *	g = (Geometry*)_hoops_RRA->_hoops_IHIP[i];

					if (BIT(_hoops_AGPGR(g->type), _hoops_RRA->_hoops_RGPGR)) {
						if (g->_hoops_IPPGR != null &&
							g->type != _hoops_AHIP) {

							_hoops_PPPIC(_hoops_ARCAR, g, _hoops_SRCP);
							_hoops_RCRC->InsertItem(g, 1);
						}
						else switch (g->type) {
							case _hoops_GSIP:
							case _hoops_SCIP: {
								Polyhedron *	phon = (Polyhedron *)g;
								Local_Face_Attributes *	_hoops_CPRI = &phon->local_face_attributes;

								if (phon->face_count > 0) {
									if (_hoops_CPRI->_hoops_PSRRA == phon->face_count) {
										_hoops_ACGHR index = _hoops_CPRI->findices[0];
										int ii;

										for (ii=1; ii<phon->face_count; ii++) {
											if (index != _hoops_CPRI->findices[ii])
												break;
										}

										if (ii == phon->face_count) {
											_hoops_SSGI * _hoops_APRRA;
											ZALLOC (_hoops_APRRA, _hoops_SSGI);

											_hoops_PCSGA * findex;
											ZALLOC (findex, _hoops_PCSGA);

											findex->value = index;
											findex->type = _hoops_SHGRA;
											_hoops_APRRA->_hoops_GHA = _hoops_APRRA->_hoops_CCCIR = findex->_hoops_GHA = Color_FACE;
											_hoops_APRRA->colors = findex;
											_hoops_APRRA->_hoops_RRHH |= _hoops_SACHC;

											_hoops_APPIC(_hoops_ARCAR, g, _hoops_SRCP, "shell color", _hoops_APRRA);
										}
										else
											_hoops_APPIC(_hoops_ARCAR, g, _hoops_SRCP, "isolated color", null);

										_hoops_RCRC->InsertItem(g, 1);
									}
									else if (_hoops_CPRI->_hoops_HSRRA == phon->face_count) {
										RGB	c = _hoops_CPRI->colors[0];
										int ii;

										for (ii=1; ii<phon->face_count; ii++) {
											if (c != _hoops_CPRI->colors[ii])
												break;
										}

										if (ii == phon->face_count) {
											_hoops_SSGI * _hoops_APRRA;
											ZALLOC (_hoops_APRRA, _hoops_SSGI);

											_hoops_HCSGA *	_hoops_ICSGA;
											ZALLOC (_hoops_ICSGA, _hoops_HCSGA);

											_hoops_ICSGA->_hoops_ISHIR._hoops_CSHR = c;
											_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA = M_DIFFUSE;
											_hoops_ICSGA->type = _hoops_GIGRA;
											_hoops_APRRA->_hoops_GHA = _hoops_APRRA->_hoops_CCCIR = _hoops_ICSGA->_hoops_GHA = Color_FACE;
											_hoops_APRRA->colors = _hoops_ICSGA;
											_hoops_APRRA->_hoops_RRHH |= _hoops_SACHC;

											_hoops_APPIC(_hoops_ARCAR, g, _hoops_SRCP, "shell color", _hoops_APRRA);
											_hoops_RCRC->InsertItem(g, 1);
										}
									}
								}
							}	break;

							default:	break;
						}
					}
				}

				// _hoops_HHGP _hoops_GH
				int _hoops_GHPIC = _hoops_RCRC->Count();

				if (_hoops_GHPIC > 0) {
					if (_hoops_GHPIC == _hoops_RRA->_hoops_HHIP) {
						ASSERT(!_hoops_RRA->_hoops_IPPGR);
						ASSERT(_hoops_SRCP->_hoops_GACP == null);

						_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_RRA);
						_hoops_HPRH(_hoops_RRA);
					}
					else {
						_hoops_SIHIR const **	_hoops_IHIP;
						int					_hoops_RHPIC	= _hoops_RRA->_hoops_HHIP - _hoops_GHPIC;
						int					n=0;

						ALLOC_ARRAY (_hoops_IHIP, _hoops_RHPIC, _hoops_SIHIR const *);

						for (int ii=0; ii<_hoops_RRA->_hoops_HHIP; ii++) {
							if (_hoops_RCRC->LookupItem((Geometry*)_hoops_RRA->_hoops_IHIP[ii]))
								_hoops_HPRH (_hoops_RRA->_hoops_IHIP[ii]);
							else
								_hoops_IHIP[n++] = _hoops_RRA->_hoops_IHIP[ii];
						}

						FREE_ARRAY (_hoops_RRA->_hoops_IHIP, _hoops_RRA->_hoops_HHIP, _hoops_SIHIR const *);

						_hoops_RRA->_hoops_IHIP = _hoops_IHIP;
						_hoops_RRA->_hoops_HHIP = _hoops_RHPIC;
					}
				}
			}

			delete _hoops_RCRC;
		}
		else
			ASSERT(0); // _hoops_PGPI _hoops_CRPGI _hoops_RGAR
	} while ((geo = _hoops_CPPIC) != null);


	Subsegment *	_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;

	if (_hoops_GIPIA != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP) {
			if (BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_SACHC))
				_hoops_GIPIA->_hoops_RRHH &= ~_hoops_SACHC;
			else if (_hoops_HCGIC || !BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_PACHC))
				_hoops_IPPIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA, _hoops_HCGIC);
		}
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}

local void _hoops_AHPIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_RAPIC **		_hoops_ASRGR,
	_hoops_CSGHP *		_hoops_PHPIC,
	_hoops_RPCHC *	_hoops_HHPIC) {
	ASSERT(BIT(_hoops_ARCAR->flags, _hoops_PRCHC));

#if 0
	if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 4519")) {
		_hoops_ARCAR=_hoops_ARCAR;
	}
	if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "sub0 -- 0")) {
		_hoops_ARCAR=_hoops_ARCAR;
	}
#endif

#define _hoops_IHPIC		5
#define _hoops_CHPIC		111
#define _hoops_SHPIC			3111
#define _hoops_GIPIC	3333

	if (_hoops_ASRGR) {
		if (!BIT (_hoops_SRCP->_hoops_RRHH, _hoops_CACHC)) {
			_hoops_GHAIR * h = _hoops_RCGIC(_hoops_ARCAR, _hoops_SRCP->_hoops_IPPGR);

			// _hoops_SIGPA _hoops_GPRR _hoops_PPR _hoops_IGRI _hoops_PISI _hoops_ARAH-_hoops_HHIS
			if (h != null && h->_hoops_RRCRP >= _hoops_CHPIC)
				return;

			if (_hoops_PHPIC != null)
				_hoops_PHPIC->ReplaceItem(_hoops_SRCP, _hoops_CHPIC);

			if (_hoops_SRCP->geometry)
				_hoops_GPPIC(_hoops_ARCAR, _hoops_SRCP, null, _hoops_SRCP->geometry, ~0, _hoops_ASRGR, false);
		}

		Subsegment *		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;

		if (_hoops_GIPIA != null) do {
			if (_hoops_GIPIA->type == _hoops_IRCP)
				_hoops_AHPIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA, _hoops_ASRGR, _hoops_PHPIC, _hoops_HHPIC);
			else if (_hoops_GIPIA->type == _hoops_AGRPR) {
				_hoops_PGRPR *	include = (_hoops_PGRPR *)_hoops_GIPIA;

				if (!BIT(include->_hoops_RRHH, _hoops_GPCHC)) {
					_hoops_CRCP *	s = (_hoops_CRCP alter *)include->_hoops_IGRPR;

					float		_hoops_RIPIC;

					if (!_hoops_HHPIC->LookupItem(s, &_hoops_RIPIC)) {
						_hoops_RIPIC = -MAX_FLOAT;

						Bounding	_hoops_CCIIA = s->bounding;

						if (!_hoops_CCIIA._hoops_HICAR()) {
							_hoops_RAPIC *	_hoops_AIPIC = null;

							_hoops_AHPIC (_hoops_ARCAR, s, &_hoops_AIPIC, null, _hoops_HHPIC);

							while (_hoops_AIPIC != null) {
								_hoops_RAPIC *	next = _hoops_AIPIC->next;

								if (_hoops_AIPIC->t > _hoops_RIPIC)
									_hoops_RIPIC = _hoops_AIPIC->t;

								FREE(_hoops_AIPIC, _hoops_RAPIC);

								_hoops_AIPIC = next;
							}
						}

						_hoops_HHPIC->InsertItem(s, _hoops_RIPIC);
					}

					if (_hoops_RIPIC != -MAX_FLOAT) {
						_hoops_RAPIC * _hoops_PIPIC;

						POOL_ZALLOC(_hoops_PIPIC, _hoops_RAPIC, _hoops_ARCAR->memory_pool);

						_hoops_PIPIC->next = *_hoops_ASRGR;
						_hoops_PIPIC->i = include;
						_hoops_PIPIC->s = _hoops_SRCP;
						_hoops_PIPIC->t = _hoops_RIPIC;

						*_hoops_ASRGR = _hoops_PIPIC;
					}
				}
				else {
					_hoops_RAPIC * _hoops_PIPIC;

					POOL_ZALLOC(_hoops_PIPIC, _hoops_RAPIC, _hoops_ARCAR->memory_pool);

					_hoops_PIPIC->next = *_hoops_ASRGR;
					_hoops_PIPIC->i = include;
					_hoops_PIPIC->s = _hoops_SRCP;
					_hoops_PIPIC->t = -1.0;

					*_hoops_ASRGR = _hoops_PIPIC;
				}
			}
		} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

		return;
	}

	_hoops_CSGHP *		_hoops_HIPIC = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_CSGHP)(_hoops_ARCAR->memory_pool);
	_hoops_RPCHC *	_hoops_IIPIC = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_RPCHC)(_hoops_ARCAR->memory_pool);
	_hoops_RPCHC *	_hoops_GGCRP = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_RPCHC)(_hoops_ARCAR->memory_pool);
	_hoops_RAPIC *		list = null;

	_hoops_AHPIC (_hoops_ARCAR, _hoops_SRCP, &list, _hoops_HIPIC, _hoops_IIPIC);

	float _hoops_CIPIC = MAX_FLOAT;
	float _hoops_SIPIC = -MAX_FLOAT;

	_hoops_RAPIC *	_hoops_GCPIC = null;
	_hoops_RAPIC *	x;
	_hoops_RAPIC **	_hoops_RCPIC;
	int 				c = 0;
	int 				_hoops_IPPPI = 0;

	x = list;
	_hoops_RCPIC = &list;
	while (x != null) {
		_hoops_RAPIC *	_hoops_ACPIC = x->next;

		if (x->t == -1.0f) {
			*_hoops_RCPIC = _hoops_ACPIC;

			if (x->i == null) {
				x->next = _hoops_GCPIC;
				_hoops_GCPIC = x;
			}
			else {
				ASSERT(x->s);
				_hoops_CRCP * _hoops_HPAPI = _hoops_HASHC(_hoops_ARCAR, x->s, "invisible");
				_hoops_HIPIC->ReplaceItem(_hoops_HPAPI, _hoops_GIPIC);

				Subsegment * _hoops_GIPIA = (Subsegment *)x->i;
				_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_GIPIA);

				_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_GIPIA, _hoops_HPAPI);

				_hoops_GIPIA->owner = _hoops_HPAPI;

				FREE(x, _hoops_RAPIC);
			}
		}
		else {
			c++;

			if (x->t > _hoops_SIPIC)
				_hoops_SIPIC = x->t;

			if (x->t < _hoops_CIPIC)
				_hoops_CIPIC = x->t;

			if (x->i)
				_hoops_IPPPI++;

			_hoops_RCPIC = &x->next;
		}

		x = _hoops_ACPIC;
	}

	typedef VHash<_hoops_PHIP *, _hoops_RAPIC *> _hoops_PCPIC;
	_hoops_PCPIC * 	_hoops_HCPIC = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_PCPIC)(_hoops_ARCAR->memory_pool);

#define _hoops_ICPIC 1000

	if (c > 0) {
		float 					_hoops_CCPIC = (_hoops_SIPIC - _hoops_CIPIC);
		float 					_hoops_SCPIC = _hoops_CCPIC / (float)_hoops_ICPIC;
		_hoops_RAPIC **		h;
		int *					n;

		POOL_ZALLOC_ARRAY_CACHED(h, _hoops_ICPIC, _hoops_RAPIC *, _hoops_ARCAR->memory_pool);
		POOL_ZALLOC_ARRAY_CACHED(n, _hoops_ICPIC, int, _hoops_ARCAR->memory_pool);

		x = list;
		while (x != null) {
			_hoops_RAPIC *	_hoops_ACPIC = x->next;
			float				t = x->t - _hoops_CIPIC;
			int					i = _hoops_ICPIC - 1 -(int)(t / _hoops_SCPIC);

			if (i < 0)
				i = 0;
			else if (i > _hoops_ICPIC - 1)
				i = _hoops_ICPIC - 1;

			n[i]++;
			x->next = h[i];
			h[i] = x;

			x = _hoops_ACPIC;
		}

		int		limits[_hoops_IHPIC-1];
		int		used = 0;
		int		_hoops_IGCPA = 0;
		bool	_hoops_GSPIC = true;

		for (int i=0; i<_hoops_IHPIC-1; i++)
			limits[i] = (c>>(_hoops_IHPIC-i))+1;

		for (int i=0; i<_hoops_ICPIC; i++) {
			if (h[i] != null) {
				x = h[i];
				h[i] = null;

				used += n[i];

				while (_hoops_IGCPA < _hoops_IHPIC-1 && used > limits[_hoops_IGCPA])
					_hoops_IGCPA++;

				if (_hoops_GSPIC == true) {
					// _hoops_RPP _hoops_CPS _hoops_HRGR _hoops_RH _hoops_PSHR _hoops_IGIR _hoops_SAHR _hoops_SGH _hoops_IGGHA _hoops_AHHR
					if (_hoops_IGCPA == _hoops_IHPIC-1)
						_hoops_IGCPA = 0;
					_hoops_GSPIC = false;
				}

				while (x != null) {
					_hoops_RAPIC *	_hoops_RSPIC = x->next;
					_hoops_RAPIC *	item;

					if (x->i != null) {
						ASSERT(x->r == null);
						ASSERT(x->g == null);

#define _hoops_ASPIC 3.0
						ASSERT(x->s);
						_hoops_CRCP * _hoops_HPAPI = _hoops_HASHC(_hoops_ARCAR, x->s, "include");
						_hoops_HIPIC->InsertItem(_hoops_HPAPI, _hoops_IGCPA);
						_hoops_GGCRP->InsertItem(_hoops_HPAPI, _hoops_ASPIC);

						Subsegment * _hoops_GIPIA = (Subsegment *)x->i;
						_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_GIPIA);

						_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_GIPIA, _hoops_HPAPI);

						_hoops_GIPIA->owner = _hoops_HPAPI;

						FREE(x, _hoops_RAPIC);
					}
					else {
						ASSERT(x->r != null);
						ASSERT(x->g != null);

						_hoops_HCPIC->LookupItem(x->r, &item);

						if (item != null) {
							x->next = item->next;
							item->next = x;
						}
						else {
							x->next = null;
							_hoops_HCPIC->InsertItem(x->r, x);
						}

						x->_hoops_IGCPA = _hoops_IGCPA;
					}

					x = _hoops_RSPIC;
				}
			}
		}

		FREE_ARRAY(h, _hoops_ICPIC, _hoops_RAPIC *);
		FREE_ARRAY(n, _hoops_ICPIC, int);
	}

	x = _hoops_GCPIC;
	while (x != null) {
		_hoops_RAPIC * _hoops_RSPIC = x->next;
		_hoops_RAPIC * item;

		ASSERT(x->r != null);
		ASSERT(x->g != null);
		ASSERT(x->i == null);

		_hoops_HCPIC->LookupItem(x->r, &item);

		if (item != null) {
			x->next = item->next;
			item->next = x;
		}
		else {
			x->next = null;
			_hoops_HCPIC->InsertItem(x->r, x);
		}

		x->_hoops_IGCPA = -1;

		x = _hoops_RSPIC;
	}

	if (_hoops_HCPIC->Count() > 0) {
		_hoops_PCPIC::PairList *	pl = _hoops_HCPIC->GetPairList();
		_hoops_PCPIC::Pair *		p;

		while ((p = pl->RemoveFirst()) != null) {
			_hoops_PHIP *	_hoops_PSPIC = p->Key();

			x = p->Item();
			delete p;

			_hoops_CRCP *	_hoops_PHGSA = _hoops_PSPIC->owner;

			_hoops_HIPIC->ReplaceItem(_hoops_PHGSA,0);

			if (_hoops_PSPIC->_hoops_IHIP[0]->type != _hoops_IRCP &&
				_hoops_PSPIC->_hoops_HHIP == 1) {

				ASSERT(x->next == null);

				if (x->_hoops_IGCPA == 0) {
					; // _hoops_AA _hoops_ISAP
				}
				else if (x->_hoops_IGCPA != -1) {
					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_PSPIC);
					_hoops_CRCP *	_hoops_HHGSA = _hoops_HASHC(_hoops_ARCAR, _hoops_PHGSA, _hoops_PHGSA->name.text);
					_hoops_HIPIC->InsertItem(_hoops_HHGSA, x->_hoops_IGCPA);
					_hoops_PSPIC->owner = _hoops_HHGSA;
					_hoops_GHSHC (_hoops_ARCAR, _hoops_PSPIC, _hoops_HHGSA, true);
				}
				else {
					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_PSPIC);
					_hoops_HPRH(_hoops_PSPIC);
				}

				FREE(x, _hoops_RAPIC);
				continue;
			}

			int	gl_count = 0;

			_hoops_GRGGI *	gl[_hoops_IHPIC];
			ZERO_ARRAY(gl, _hoops_IHPIC, _hoops_GRGGI *);
			_hoops_PPCHC *	_hoops_HSPIC = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_PPCHC)(_hoops_ARCAR->memory_pool);

			if (_hoops_PSPIC->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP *	_hoops_AGPIC = (_hoops_CRCP *)_hoops_PSPIC->_hoops_IHIP[0];
				Geometry *	g = _hoops_AGPIC->geometry;

				while (g != null) {
					Type	type = g->type;

					if (!BIT (_hoops_PSPIC->_hoops_RGPGR, _hoops_AGPGR(type))) {
						_hoops_PGPGR (g, g->type);
					}
					else {
						_hoops_HSPIC->InsertItem(g, 1);
						g = g->next;
					}
				}
			}
			else {
				for (int i=0; i<_hoops_PSPIC->_hoops_HHIP; i++)
					_hoops_HSPIC->InsertItem((Geometry *)_hoops_PSPIC->_hoops_IHIP[i], 1);
			}

			while (x != null) {
				_hoops_RAPIC *	_hoops_RSPIC = x->next;

				ASSERT(x->g != null);
				ASSERT(x->i == null);
				ASSERT(x->r == _hoops_PSPIC);

				_hoops_HSPIC->RemoveItem(x->g);

				if (x->_hoops_IGCPA != -1) {
					if (gl[x->_hoops_IGCPA] == null) {
						gl[x->_hoops_IGCPA] = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_GRGGI)(_hoops_ARCAR->memory_pool);
						gl_count++;
					}

					gl[x->_hoops_IGCPA]->AddFirst(x->g);
				}

				FREE(x, _hoops_RAPIC);
				x = _hoops_RSPIC;
			}

			for (int _hoops_IGCPA=0; _hoops_IGCPA<_hoops_IHPIC; _hoops_IGCPA++) {
				if (gl[_hoops_IGCPA]) {
					_hoops_CRCP *	_hoops_HHGSA = _hoops_HASHC(_hoops_ARCAR, _hoops_PHGSA, _hoops_PHGSA->name.text);

					_hoops_HIPIC->InsertItem(_hoops_HHGSA, _hoops_IGCPA);

					_hoops_PHIP *	_hoops_RRA = _hoops_SSAIC(_hoops_ARCAR, _hoops_HHGSA, ~0);

					int _hoops_PGPIC = gl[_hoops_IGCPA]->Count();
					_hoops_RRA->_hoops_HHIP = _hoops_PGPIC;
					ALLOC_ARRAY (_hoops_RRA->_hoops_IHIP, _hoops_RRA->_hoops_HHIP, _hoops_SIHIR const *);

					for (int i=0; i<_hoops_PGPIC; i++) {
						Geometry * g = gl[_hoops_IGCPA]->RemoveFirst();
						_hoops_RRA->_hoops_IHIP[i] = (_hoops_SIHIR const *)g;
						_hoops_PRRH (g);
					}

					_hoops_RRA->_hoops_RGPGR = _hoops_ISAIC(_hoops_RRA);

					_hoops_GHSHC (_hoops_ARCAR, _hoops_RRA, _hoops_HHGSA, true);

					delete gl[_hoops_IGCPA];
				}
			}

			if (_hoops_HSPIC->Count() > 0) {
				_hoops_CRCP *	_hoops_HHGSA = _hoops_HASHC(_hoops_ARCAR, _hoops_PHGSA, _hoops_PHGSA->name.text);

				_hoops_HIPIC->InsertItem(_hoops_HHGSA, _hoops_CHPIC);

				_hoops_PHIP *	_hoops_RRA = _hoops_SSAIC(_hoops_ARCAR, _hoops_HHGSA, _hoops_PSPIC->_hoops_RGPGR);

				_hoops_PPCHC::PairList *	pl = _hoops_HSPIC->GetPairList();
				_hoops_PPCHC::Pair *		p;

				_hoops_RRA->_hoops_HHIP = _hoops_HSPIC->Count();
				ALLOC_ARRAY (_hoops_RRA->_hoops_IHIP, _hoops_RRA->_hoops_HHIP, _hoops_SIHIR const *);

				int n = 0;

				while ((p = pl->RemoveFirst()) != null) {
					Geometry const * g = p->Key();
					delete p;

					_hoops_RRA->_hoops_IHIP[n++] = (_hoops_SIHIR const *)g;
					_hoops_PRRH (g);
				}

				delete pl;

				_hoops_RRA->_hoops_RGPGR = _hoops_ISAIC(_hoops_RRA);

				_hoops_GHSHC (_hoops_ARCAR, _hoops_RRA, _hoops_HHGSA, true);
			}

			delete _hoops_HSPIC;

			_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_PSPIC);
			_hoops_HPRH(_hoops_PSPIC);
		}

		delete pl;
	}

	delete _hoops_HCPIC;

	if (_hoops_HIPIC->Count() > 0) {
		_hoops_CSGHP::PairList *	pl = _hoops_HIPIC->GetPairList();
		_hoops_CSGHP::Pair *		p;

		while ((p = pl->RemoveFirst()) != null) {
			_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)p->Key();
			int			defer = p->Item();

			delete p;

			// _hoops_GAAP _hoops_CPS _hoops_CSAP _hoops_ISPIC
			if (_hoops_SRCP->geometry == null) {
				if (_hoops_SRCP->_hoops_RGRPR == null &&
					!BIT (_hoops_SRCP->_hoops_RRHH, _hoops_CACHC) &&
					!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GIPSA)) {

					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_SRCP);
					_hoops_HPRH (_hoops_SRCP);
					continue;
				}
			}

			if (defer == _hoops_CHPIC &&
				_hoops_SRCP->geometry == null)
				continue;

			if (defer > 0) {
				/* _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SIHGA */
				_hoops_RHRHH (_hoops_ARCAR->_hoops_RIGC, _hoops_ARCAR->_hoops_RGSHC, "size group %d", defer);

				_hoops_CRCP *	_hoops_CSPIC = _hoops_HASHC(_hoops_ARCAR, _hoops_SRCP->owner, _hoops_ARCAR->_hoops_RGSHC);

				_hoops_GHAIR *	heuristics;
				ZALLOC (heuristics, _hoops_GHAIR);
				heuristics->mask |= _hoops_APIRP;
				heuristics->value |= _hoops_APIRP;
				heuristics->_hoops_RRCRP = defer;

				if (defer == _hoops_GIPIC) {
					heuristics->mask |= _hoops_CCIAA;
					heuristics->value |= _hoops_CCIAA;
				}

				float bias;
				if (_hoops_GGCRP->LookupItem(_hoops_SRCP, &bias))
					heuristics->_hoops_ARCRP = bias;

				if (!HI_Set_Heuristics (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_CSPIC, heuristics)) {
					ASSERT(0); // _hoops_CGH _hoops_HAR _hoops_IHPS
					FREE (heuristics, _hoops_GHAIR);
				}


				_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCP);
				_hoops_SRCP->owner = _hoops_CSPIC;
				_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, (Subsegment*)_hoops_SRCP, _hoops_CSPIC);

				HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, _hoops_CSPIC, _hoops_SRCP->_hoops_RCGC);
			}
		}

		delete pl;
	}

	delete _hoops_IIPIC;
	delete _hoops_HIPIC;
	delete _hoops_GGCRP;
}


local void _hoops_SSPIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP) {
	Subsegment *		_hoops_GIPIA;
	Subsegment *		_hoops_HARIC;

	ASSERT(BIT(_hoops_ARCAR->flags, _hoops_PRCHC));
	ASSERT(BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HIRIR));

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_HARIC = _hoops_GIPIA->next;
		if (_hoops_GIPIA->type == _hoops_IRCP)
			_hoops_SSPIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA);
	} while ((_hoops_GIPIA = _hoops_HARIC) != null);


	if (_hoops_SRCP != null &&
		_hoops_SRCP->geometry != null) {

		Geometry const * g = _hoops_SRCP->geometry;

		// _hoops_SICR _hoops_GGHIC _hoops_PHHIP _hoops_CRPGI _hoops_IS _hoops_PGPI _hoops_CRPGI
		do {
			if (g->type == _hoops_AHIP) {
				_hoops_PHIP *	_hoops_RRA = (_hoops_PHIP *)g;

				if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
					_hoops_CRCP *			_hoops_RIHHH = (_hoops_CRCP *)_hoops_RRA->_hoops_IHIP[0];
					int					count = 0;

					_hoops_RHGIC(_hoops_RIHHH->geometry, _hoops_RRA->_hoops_RGPGR, &count);
					if (count == 1) {
						Geometry *		x = (Geometry *)_hoops_RIHHH->geometry;

						while (!BIT (_hoops_RRA->_hoops_RGPGR, _hoops_AGPGR(x->type)))
							x = x->next;

						// _hoops_CICA _hoops_IS _hoops_PGPI _hoops_HAR _hoops_PHHIP
						_hoops_HPRH(_hoops_RRA->_hoops_IHIP[0]);
						_hoops_RRA->_hoops_IHIP[0] = (_hoops_SIHIR *)x;
						_hoops_PRRH (x);

						_hoops_RRA->_hoops_RGPGR = _hoops_AGPGR(x->type);
						if (x->type == _hoops_AHIP)
							_hoops_RRA->_hoops_RGPGR |= ((_hoops_PHIP*) x)->_hoops_RGPGR;
					}
				}
			}
			else
				ASSERT(0);
		} while ((g = g->next) != null);

		// _hoops_APSGA _hoops_PGPI _hoops_CRPGI _hoops_HII _hoops_SASI _hoops_SGHC
		_hoops_HAPIC *	_hoops_RGHIC = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_HAPIC)(_hoops_ARCAR->memory_pool);
		g = _hoops_SRCP->geometry;

		while (g != null) {
			if (g->type == _hoops_AHIP &&
				g->_hoops_IPPGR == null) {
				_hoops_PHIP alter * _hoops_RRA = (_hoops_PHIP alter *)g;

				if (_hoops_RRA->_hoops_IHIP[0]->type != _hoops_IRCP) {
					_hoops_RPAPA *_hoops_CPGIP = _hoops_RGHIC->Lookup(_hoops_RRA->_hoops_IHIP[0]->owner);

					if (_hoops_CPGIP == null) {
						_hoops_CPGIP = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_RPAPA)(_hoops_ARCAR->memory_pool);
						_hoops_RGHIC->InsertItem(_hoops_RRA->_hoops_IHIP[0]->owner, _hoops_CPGIP);
					}
					_hoops_CPGIP->AddFirst(_hoops_RRA);
				}
			}

			g = g->next;
		}

		if (_hoops_RGHIC->Count() > 0) {
			_hoops_HAPIC::PairList *	_hoops_AGHIC = _hoops_RGHIC->GetPairList();
			_hoops_HAPIC::Pair *		_hoops_PGHIC;

			while ((_hoops_PGHIC = _hoops_AGHIC->RemoveFirst()) != null) {
				_hoops_RPAPA *	_hoops_APAPA = _hoops_PGHIC->Item();

				delete _hoops_PGHIC;

				if (_hoops_APAPA->Count() > 1) {
					_hoops_GRGGI alter *		_hoops_HGHIC = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_GRGGI)(_hoops_ARCAR->memory_pool);
					_hoops_PHIP alter *	_hoops_RRA;

					while ((_hoops_RRA = _hoops_APAPA->RemoveFirst()) != null) {
						for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
							if (BIT(_hoops_AGPGR(_hoops_RRA->_hoops_IHIP[i]->type), _hoops_RRA->_hoops_RGPGR)) {
								if (!_hoops_HGHIC->ItemExists((Geometry*)_hoops_RRA->_hoops_IHIP[i]))
									_hoops_HGHIC->AddFirst((Geometry*)_hoops_RRA->_hoops_IHIP[i]);
							}
						}

						ASSERT(!_hoops_RRA->_hoops_IPPGR);

						_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC, _hoops_RRA);
						_hoops_HPRH(_hoops_RRA);
					}

					if (_hoops_HGHIC->Count() > 0) {
						_hoops_PHIP *	_hoops_RRA = _hoops_SSAIC(_hoops_ARCAR, _hoops_SRCP, ~0);

						int _hoops_PGPIC = _hoops_HGHIC->Count();
						_hoops_RRA->_hoops_HHIP = _hoops_PGPIC;
						ALLOC_ARRAY (_hoops_RRA->_hoops_IHIP, _hoops_RRA->_hoops_HHIP, _hoops_SIHIR const *);

						for (int i=0; i<_hoops_PGPIC; i++) {
							Geometry * g = _hoops_HGHIC->RemoveFirst();
							_hoops_RRA->_hoops_IHIP[i] = (_hoops_SIHIR const *)g;
							_hoops_PRRH (g);
						}

						_hoops_RRA->_hoops_RGPGR = _hoops_ISAIC(_hoops_RRA);

						_hoops_GHSHC (_hoops_ARCAR, _hoops_RRA, _hoops_SRCP, true);
					}
					delete _hoops_HGHIC;
				}
				delete _hoops_APAPA;
			}
			delete _hoops_AGHIC;
		}
		delete _hoops_RGHIC;
	}


	if (_hoops_SRCP != null &&
		_hoops_SRCP->_hoops_RGRPR == null &&
		_hoops_SRCP->_hoops_IPPGR != null &&
		_hoops_SRCP->geometry != null) {

		if (_hoops_SRCP->geometry->next == null || _hoops_SRCP->geometry->next->next == null) {
			Attribute *		_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;
			_hoops_PIGRA	locks;
			ZERO_STRUCT(&locks, _hoops_PIGRA);

			if (_hoops_ASGPR != null) do {
				if (_hoops_ASGPR->type > HK_RENDERING_OPTIONS)
					break;
				if (_hoops_ASGPR->type == HK_RENDERING_OPTIONS) {
					_hoops_RHAIR const	*	_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_ASGPR;
					if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA))
						_hoops_RSAI (&_hoops_AHAIR->locks->normal.value, _hoops_PIGRA, &locks);
					break;
				}
			} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

			_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;

			Attribute *		next = null;

			do {
				next = _hoops_ASGPR->next;

				if (!BIT(locks._hoops_IPPGR, _hoops_GGCAA(_hoops_ASGPR->type)) &&
					!BIT(_hoops_ASGPR->_hoops_RRHH, _hoops_SACHC) &&
					(_hoops_ASGPR->type == HK_MODELLING_MATRIX ||
					 _hoops_ASGPR->type == HK_USER_OPTIONS ||
					 _hoops_ASGPR->type == HK_USER_VALUE ||
					 _hoops_ASGPR->type == HK_COLOR && HI_Color_Is_Simple((_hoops_SSGI *)_hoops_ASGPR))) {

					if (_hoops_ASGPR->type == HK_MODELLING_MATRIX &&
						!_hoops_SRCP->bounding._hoops_HICAR()) {
						_hoops_ISGI const *	_hoops_CPAI = (_hoops_ISGI const *)_hoops_ASGPR;

						_hoops_SRCP->bounding = _hoops_SRCP->bounding._hoops_SCIS (&_hoops_CPAI->matrix.elements[0][0]);
						_hoops_SRCP->_hoops_HSRIR = _hoops_SRCP->bounding;
					}

					Geometry *		g = _hoops_SRCP->geometry;

					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_ASGPR);

					Attribute *		a = _hoops_ASGPR;

					do {
						Attribute **	_hoops_ASRGR = &g->_hoops_IPPGR;

						while (*_hoops_ASRGR != null && (*_hoops_ASRGR)->type < _hoops_ASGPR->type)
							_hoops_ASRGR = &(*_hoops_ASRGR)->next;

						if (*_hoops_ASRGR == null || (*_hoops_ASRGR)->type > _hoops_ASGPR->type) {
							if (a == null)
								a = HI_Clone_Attributes (_hoops_ARCAR->_hoops_RIGC, _hoops_ASGPR, (_hoops_CRCP const *)g, false, null);

							if ((a->next = *_hoops_ASRGR) != null)
								a->next->backlink = &a->next;
							a->backlink = _hoops_ASRGR;
							*_hoops_ASRGR = a;
							a->owner = (_hoops_CRCP *)g;

							_hoops_ASRGR = &a->next;

							a = null;
						}
						else switch (a->type) {	// _hoops_HASC
							case HK_COLOR: {
								_hoops_SSGI const *		_hoops_IGHIC = (_hoops_SSGI const *)a;
								_hoops_SSGI alter *		_hoops_CGHIC = (_hoops_SSGI alter *)*_hoops_ASRGR;
								// _hoops_RHPH _hoops_AGR _hoops_IH _hoops_SGHIC, _hoops_HIS _hoops_GRHIC _hoops_IRS _hoops_IGRH
								_hoops_ACSGA *		_hoops_RRHIC = _hoops_CGHIC->colors;

								_hoops_CGHIC->colors = HI_Copy_Colors (_hoops_IGHIC->colors, null);
								HI_Merge_Colors (_hoops_CGHIC, _hoops_RRHIC, null, null);
								HI_Free_Colors (_hoops_RRHIC);
							}	break;

							case HK_MODELLING_MATRIX: {
								_hoops_ISGI const *		_hoops_ARHIC = (_hoops_ISGI const *)a;
								_hoops_ISGI alter *		_hoops_PRHIC = (_hoops_ISGI alter *)*_hoops_ASRGR;

								HI_Multiply_Matrices (&_hoops_PRHIC->matrix, &_hoops_ARHIC->matrix, &_hoops_PRHIC->matrix);
							}	break;

							case HK_USER_OPTIONS: {
								// _hoops_SIGP
							}	break;

							case HK_USER_VALUE: {
								// _hoops_ISAP _hoops_ARI, _hoops_SAHR _hoops_GRHP _hoops_RH _hoops_IRGH _hoops_PIRA
							}	break;
						}

						if (_hoops_ASGPR->type == HK_MODELLING_MATRIX)
							((_hoops_PHIP alter *)g)->bounding = null;
					} while ((g = g->next) != null);

					if (a != null)
						_hoops_HPRH (a);
				}
			} while ((_hoops_ASGPR = next) != null);
		}

		if (_hoops_SRCP->_hoops_IPPGR == null &&
			!ANYBIT (_hoops_SRCP->_hoops_RRHH, _hoops_PACHC | _hoops_HACHC)) {

			if (_hoops_SRCP->geometry != null) {
				if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
					while (_hoops_SRCP->geometry != null)
						_hoops_GRAPA (_hoops_ARCAR, _hoops_SRCP->geometry, _hoops_SRCP->owner, false);
				}
				else
					_hoops_SPSHC(_hoops_ARCAR, _hoops_SRCP, _hoops_SRCP->owner);
			}

			_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_SRCP);
			HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP);
			_hoops_HPRH (_hoops_SRCP);

			_hoops_SRCP = null;
		}
	}

	if (_hoops_SRCP != null &&
		_hoops_SRCP->geometry != null) {

		// _hoops_IRHH _hoops_IRS _hoops_CRCC _hoops_CAGH _hoops_IH _hoops_IRGH _hoops_CRPGI
		ASSERT(_hoops_SRCP->geometry != null);
		if (_hoops_SRCP->_hoops_RGRPR != null) {
			_hoops_CRCP * _hoops_HRHIC = _hoops_HASHC(_hoops_ARCAR, _hoops_SRCP, "refs", _hoops_HACHC);

			if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
				while (_hoops_SRCP->geometry != null)
					_hoops_GRAPA (_hoops_ARCAR, _hoops_SRCP->geometry, _hoops_HRHIC, true);
			}
			else
				_hoops_SPSHC(_hoops_ARCAR, _hoops_SRCP, _hoops_HRHIC);
		}
	}
}

local float _hoops_IRHIC(
	_hoops_ICCHC *	_hoops_ARCAR,
	Geometry *			geometry)
{
	int			_hoops_CRHIC = 0;
	int			_hoops_SRHIC = 0;
	int			point_count = 0;

	if (geometry != null) do {
		int		_hoops_HSPIR = 0;
		int		c = 0;

		_hoops_CRHIC++;

		if (geometry->type == _hoops_AHIP) {
			_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)geometry;

			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP *				_hoops_SRCP = (_hoops_CRCP *)_hoops_RRA->_hoops_IHIP[0];

				_hoops_HSPIR = _hoops_RHGIC(_hoops_SRCP->geometry, _hoops_RRA->_hoops_RGPGR, &c);
				// _hoops_ASIGA _hoops_CGH _hoops_HAR _hoops_IHPS _hoops_HIH _hoops_RHAP
				//_hoops_AGHR(_hoops_GSGGR > 0);
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
					Geometry const *	g = (Geometry const *)_hoops_RRA->_hoops_IHIP[i];
					if (BIT(_hoops_AGPGR(g->type), _hoops_RRA->_hoops_RGPGR)) {
						if (g->type == _hoops_SCIP || g->type == _hoops_GSIP) {
							Polyhedron const *	_hoops_HPGPR = (Polyhedron const *)g;
							_hoops_HSPIR += _hoops_HPGPR->point_count;
						}
						else if (g->type == _hoops_CSIP) {
							PolyCylinder const *	_hoops_HSPIR = (PolyCylinder const *)g;
							_hoops_HSPIR += _hoops_HSPIR->point_count;
						}
						c++;
					}
				}
			}

#define _hoops_GAHIC 8

			if (_hoops_HSPIR > 0 && c > 1) {
				int		_hoops_RAHIC = (int)((float)_hoops_HSPIR/(float)c);

				if (_hoops_RAHIC > _hoops_GAHIC)
					_hoops_SRHIC += c;
				else {
					int count = (int)((float)c/(float)(_hoops_GAHIC-_hoops_RAHIC));
					_hoops_SRHIC += count;
				}
			}
			else
				_hoops_SRHIC++;
		}
		else {
			if (geometry->type == _hoops_SCIP ||geometry->type == _hoops_GSIP) {
				Polyhedron const *	_hoops_HPGPR = (Polyhedron const *)geometry;
				_hoops_HSPIR += _hoops_HPGPR->point_count;
			}
			else if (geometry->type == _hoops_CSIP) {
				PolyCylinder const *	_hoops_HSPIR = (PolyCylinder const *)geometry;
				_hoops_HSPIR += _hoops_HSPIR->point_count;
			}
			++_hoops_SRHIC;
		}

		point_count += _hoops_HSPIR;
	} while ((geometry = geometry->next) != null);

	int _hoops_ASCHC = _hoops_ARCAR->_hoops_ASCHC;

	float t = 0;

	if (_hoops_CRHIC > 1 &&
		(_hoops_SRHIC > _hoops_ASCHC ||
		point_count > _hoops_ARCAR->_hoops_HSCHC)) {
		t = (float)_hoops_SRHIC/(float)_hoops_ASCHC;
		t += (float)point_count/(float)_hoops_ARCAR->_hoops_HSCHC;
	}

	return t;
}




local void _hoops_AAHIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP,
	_hoops_CRCP *			tree=null)
{
	Subsegment *		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;
	int					_hoops_ASGIC = 0;
	int					_hoops_IPPPI = 0;

	if (!tree || _hoops_SRCP->_hoops_IPPGR != null ||
		ANYBIT(_hoops_SRCP->_hoops_RRHH, _hoops_PACHC|_hoops_CACHC))
		tree = _hoops_SRCP;

	if (_hoops_GIPIA != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP) {
			_hoops_AAHIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA, tree);
			_hoops_ASGIC++;
		}
		else
			_hoops_IPPPI++;
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	if (BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HACHC)) {
		if (_hoops_SRCP->geometry == null && _hoops_IPPPI == 0)
			_hoops_SRCP->_hoops_RRHH &= ~_hoops_HACHC;
		else if (_hoops_SRCP->owner != tree) {
			_hoops_CIGPR(_hoops_ARCAR->_hoops_RIGC, _hoops_SRCP);
			_hoops_SRCP->owner = tree;
			_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, (Subsegment*)_hoops_SRCP, tree);
		}
	}
}


local int _hoops_PAHIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP) {

	Subsegment *		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;
	int					_hoops_HAHIC = 0;

	if (_hoops_GIPIA != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP) {
			_hoops_HAHIC += _hoops_PAHIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA);

			if (BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_HACHC) && !BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_PACHC))
				_hoops_HAHIC++;
		}
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	if (BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HACHC) && !BIT(_hoops_SRCP->_hoops_RRHH, _hoops_PACHC)) {
		if (_hoops_GIPIA && _hoops_GIPIA->next == null && _hoops_GIPIA->type == _hoops_IRCP) {
			_hoops_SRCP->_hoops_RRHH &= ~_hoops_HACHC;
		}
		else if (_hoops_SRCP->geometry == null &&
				 (_hoops_HAHIC > 0 || BIT(_hoops_SRCP->owner->_hoops_RRHH, _hoops_HACHC))) {
			_hoops_SRCP->_hoops_RRHH &= ~_hoops_HACHC;
			_hoops_HAHIC = 0;
		}
	}

	return _hoops_HAHIC;
}



#define _hoops_PRIS		0x1
#define _hoops_HRIS		0x2
#define _hoops_IRIS		0x4


struct _hoops_IAHIC {
	_hoops_IAHIC *	next;
	_hoops_HPAH *		item;
	_hoops_SASC	cuboid;
};

local bool _hoops_CAHIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_IAHIC **			items,
	_hoops_CRCP *				root,
	_hoops_SASC const *	_hoops_RCCHC,
	int						_hoops_SAHIC,
	bool					_hoops_GPHIC) {

	_hoops_CRCP *				_hoops_RPHIC = null;
	_hoops_CRCP **				_hoops_APHIC;
	bool					_hoops_IHRPA = false;
	bool					_hoops_PPHIC = false;

	ASSERT(_hoops_RCCHC != null || _hoops_GPHIC);

#if 0
	if (root->name.text && strstr(root->name.text, "-- 57774")) {
		_hoops_IHRPA=_hoops_IHRPA;
	}
#endif

	POOL_ZALLOC_ARRAY_CACHED (_hoops_APHIC, _hoops_SAHIC, _hoops_CRCP *, _hoops_ARCAR->memory_pool);

	_hoops_IAHIC *	item = *items;

	*items = null;

	while (item != null) {
		_hoops_IAHIC *	_hoops_HPHIC = item->next;
		_hoops_CRCP *		_hoops_GIHPR = null;

		if (_hoops_RCCHC) {
			for (int i = 0; i < 2; i++) {
				if (_hoops_RCCHC[i]._hoops_HPCIR(item->cuboid)) {
					if (_hoops_APHIC[i] == null)
						_hoops_APHIC[i] = _hoops_HASHC(_hoops_ARCAR, root, "split", _hoops_IACHC | _hoops_HACHC);

					_hoops_GIHPR = _hoops_APHIC[i];

					_hoops_IHRPA = true;
					break;
				}
			}
		}

		// _hoops_IHIS _hoops_IS _hoops_IPHIC _hoops_RPP _hoops_SCH _hoops_SARS'_hoops_RA _hoops_SIHRR
		if (_hoops_GIHPR == null && _hoops_GPHIC) {
			if (_hoops_RPHIC == null)
				_hoops_RPHIC = _hoops_HASHC(_hoops_ARCAR, root, "split span", _hoops_IACHC|_hoops_SACHC| _hoops_HACHC);
			_hoops_GIHPR = _hoops_RPHIC;
		}

		if (_hoops_GIHPR) {
			switch (item->item->type) {
				case _hoops_AGRPR:
				case _hoops_IRCP: {
					Subsegment *	_hoops_GIPIA = (Subsegment *)item->item;
					_hoops_CRCP *		_hoops_CPHIC = _hoops_SSIGP (_hoops_GIPIA);

					if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
						_hoops_RRSHC (_hoops_ARCAR->_hoops_RIGC, _hoops_GIPIA);
						_hoops_RAGSA (_hoops_ARCAR, _hoops_CPHIC, _hoops_GIPIA->owner, _hoops_GIHPR);
					}

					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_GIPIA);

					_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_GIPIA, _hoops_GIHPR);

					_hoops_GIPIA->owner = _hoops_GIHPR;

					if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
						Bounding bounding = Bounding::Create(item->cuboid);
						HI_Propagate_Bounding (_hoops_ARCAR->_hoops_RIGC, _hoops_GIHPR, bounding, null);
						HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, _hoops_GIHPR, _hoops_CPHIC->_hoops_RCGC);
					}
				}	break;

				// _hoops_CPAP
				default: {
					Geometry *g = (Geometry *)item->item;
					_hoops_GRAPA (_hoops_ARCAR, g, _hoops_GIHPR, false);
					if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC))
						_hoops_GIHPR->_hoops_RCGC |= HI_Determine_Geometry_Maybes (g);
					_hoops_PPHIC = true;
				}	break;
			}

			FREE(item, _hoops_IAHIC);
		}
		else {
			item->next = *items;
			 *items = item;
		}

		item = _hoops_HPHIC;
	}

	if (_hoops_SRCP->geometry != null &&
		_hoops_SRCP->_hoops_RGRPR == null &&
		_hoops_GPHIC) {

		if (_hoops_RPHIC == null)
			_hoops_RPHIC = _hoops_HASHC(_hoops_ARCAR, root, "split span", _hoops_IACHC|_hoops_SACHC| _hoops_HACHC);

		if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
			while (_hoops_SRCP->geometry != null)
				_hoops_GRAPA (_hoops_ARCAR, _hoops_SRCP->geometry, _hoops_RPHIC, false);
		}
		else
			_hoops_SPSHC(_hoops_ARCAR, _hoops_SRCP, _hoops_RPHIC);

		_hoops_PPHIC = true;
	}

	if (BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
		if (_hoops_RPHIC != null)
			_hoops_HPRIC (_hoops_RPHIC);

		for (int i = 0; i < 2; i++) {
			if (_hoops_APHIC[i] != null)
				_hoops_HPRIC (_hoops_APHIC[i]);
		}
	}

	FREE_ARRAY (_hoops_APHIC, _hoops_SAHIC, _hoops_CRCP *);

	return _hoops_PPHIC;
} /* _hoops_RSGR _hoops_API '_hoops_SIAPA _hoops_CAGH */


#define _hoops_SPHIC			0x01
#define _hoops_GHHIC	0x02
#define _hoops_RHHIC	0x04
#define _hoops_AHHIC	0x08


local float _hoops_PHHIC(
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP,
	int					flags)
{
	Subsegment *		_hoops_SIIS = _hoops_SRCP->_hoops_RGRPR;

	int					_hoops_HHHIC = 0;
	int					_hoops_IPPPI = 0;
	float				t = 0.0f;

	if (ANYBIT(flags, _hoops_SPHIC|_hoops_RHHIC|_hoops_AHHIC)) {
		if (_hoops_SIIS != null) do {
			if (_hoops_SIIS->type == _hoops_AGRPR)
				_hoops_IPPPI++;
			else
				_hoops_HHHIC++;

			if (ANYBIT(flags, _hoops_SPHIC|_hoops_RHHIC)) {
				_hoops_CRCP *	_hoops_GIPIA = _hoops_SSIGP (_hoops_SIIS);

				t += _hoops_PHHIC(_hoops_ARCAR, _hoops_GIPIA, flags&~_hoops_GHHIC);

				if (t > 1.0f)
					break;
			}
		} while ((_hoops_SIIS = _hoops_SIIS->next) != null);

		if (BIT(flags, _hoops_SPHIC)) {
			int _hoops_PSCHC = _hoops_IAAA((int)((float)_hoops_ARCAR->_hoops_PSCHC*_hoops_SRCP->bounding._hoops_SGCIR()), 8);
			t += (float)(_hoops_HHHIC+_hoops_IPPPI) / (float)_hoops_PSCHC;
		}
	}

#define _hoops_IHHIC 16
	if (BIT(flags, _hoops_AHHIC) &&
		_hoops_IPPPI > _hoops_IHHIC)
		t += 1.0f;

	if (t < 1.0f && _hoops_SRCP->geometry != null &&
		ANYBIT(flags, _hoops_GHHIC|_hoops_RHHIC))
		t += _hoops_IRHIC(_hoops_ARCAR, _hoops_SRCP->geometry);

	return t;
}


local void _hoops_CHHIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			root,
	int					level,
	int					flags)
{
	if (level > 32)
		return;

#if 0
	if (root->name.text && strstr(root->name.text, "-- 25728")) {
		level=level;
	}
	if (root->name.text && strstr(root->name.text, "-- 11123")) {
		level=level;
	}
#endif

	float t = _hoops_PHHIC(_hoops_ARCAR, root, flags);

	if (t > 1.0f) {
		Subsegment *	_hoops_SISAA = root->_hoops_RGRPR;
		root->_hoops_RGRPR = null;
		if (_hoops_SISAA)
			_hoops_SISAA->backlink = &_hoops_SISAA;

		_hoops_IAHIC *		items = null;
		Geometry *			geometry = root->geometry;
		Bounding			bounding = Bounding::Create();;

		if (geometry != null) {
			while (geometry != null) {
				Geometry *	_hoops_CCGPR = geometry->next;
				Bounding	_hoops_RCHS;

				if (geometry->type == _hoops_GSIP || geometry->type == _hoops_SCIP) {
					Polyhedron const *	_hoops_HARIR = (Polyhedron const *)geometry;
					_hoops_RCHS = _hoops_HARIR->bounding;
				}
				else if (geometry->type == _hoops_CSIP) {
					PolyCylinder const *	_hoops_HARIR = (PolyCylinder const *)geometry;
					_hoops_RCHS = _hoops_HARIR->bounding;
				}
				else if (geometry->type == _hoops_AHIP) {
					_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)geometry;
					_hoops_RCHS = _hoops_RRA->bounding;
					if (_hoops_RCHS._hoops_HICAR())
						HI_Figure_Geometry_Bounding (geometry, _hoops_RCHS);
				}
				else
					HI_Figure_Geometry_Bounding (geometry, _hoops_RCHS);

				if (!_hoops_RCHS._hoops_HICAR() &&
					 _hoops_RCHS._hoops_PGCIR() > 0.0f) {

					if (geometry->_hoops_IPPGR != null) {
						Attribute *		_hoops_PSACR = null;
						HI_Gather_Modelling (geometry->_hoops_IPPGR, &_hoops_PSACR);
						if (_hoops_PSACR != null) {
							_hoops_RCHS = _hoops_RCHS._hoops_SCIS (&((_hoops_ISGI *)_hoops_PSACR)->matrix.elements[0][0]);
							_hoops_HPRH (_hoops_PSACR);
						}
					}

					_hoops_IAHIC *	item;

					POOL_ZALLOC(item, _hoops_IAHIC, _hoops_ARCAR->memory_pool);
					item->next = items;
					items = item;

					item->item = (_hoops_HPAH *)geometry;
					item->cuboid = _hoops_RCHS->cuboid;

					bounding.Merge(_hoops_RCHS);
				}

				geometry = _hoops_CCGPR;
			}
		}

		Subsegment *	next;

		if ((next = _hoops_SISAA) != null) do {
			_hoops_CRCP const *		_hoops_CPHIC = _hoops_SSIGP (next);

			if (!_hoops_CPHIC->bounding._hoops_HICAR()) {
				Bounding	_hoops_RCHS = _hoops_CPHIC->bounding;

				Vector		d = _hoops_RCHS->cuboid.max - _hoops_RCHS->cuboid.min;

				if (d.x != d.y || d.x != d.z) {
					Attribute *			mat = null;

					HI_Gather_Modelling (_hoops_CPHIC->_hoops_IPPGR, &mat);

					if (mat != null) {
						_hoops_RCHS = _hoops_RCHS._hoops_SCIS (&((_hoops_ISGI *)mat)->matrix.elements[0][0]);
						_hoops_HPRH (mat);
					}

					_hoops_IAHIC *		item;

					POOL_ZALLOC(item, _hoops_IAHIC, _hoops_ARCAR->memory_pool);
					item->next = items;
					items = item;

					item->item = (_hoops_HPAH *)next;
					item->cuboid = _hoops_RCHS->cuboid;

					bounding->Merge (_hoops_RCHS);
				}
			}
		} while ((next = next->next) != null);

		if (!bounding._hoops_HICAR()) {
			bool _hoops_SHHIC = false;
			int _hoops_SAIS = 0;

			level++;

			while (items && !ALLBITS (_hoops_SAIS, _hoops_PRIS|_hoops_HRIS|_hoops_IRIS)) {
				_hoops_SASC const & cuboid = bounding->cuboid;

				int _hoops_HAIS = 0;
				float _hoops_RPIS = 0.0f;
				float _hoops_PPIS = 0.0f;

				if (!BIT (_hoops_SAIS, _hoops_PRIS)) {
					_hoops_RPIS = cuboid.max.x - cuboid.min.x;
					if (_hoops_RPIS > 0.0f) {
						_hoops_HAIS = _hoops_PRIS;
						_hoops_PPIS = _hoops_RPIS;
					}
					else
						_hoops_SAIS |= _hoops_PRIS;
				}

				if (!BIT (_hoops_SAIS, _hoops_HRIS)) {
					_hoops_RPIS = cuboid.max.y - cuboid.min.y;
					if (_hoops_RPIS > _hoops_PPIS) {
						_hoops_PPIS = _hoops_RPIS;
						_hoops_HAIS = _hoops_HRIS;
					}
					else if (_hoops_RPIS == 0.0f)
						_hoops_SAIS |= _hoops_HRIS;
				}

				if (!BIT (_hoops_SAIS, _hoops_IRIS)) {
					_hoops_RPIS = cuboid.max.z - cuboid.min.z;
					if (_hoops_RPIS > _hoops_PPIS) {
						_hoops_PPIS = _hoops_RPIS;
						_hoops_HAIS = _hoops_IRIS;
					}
					else if (_hoops_RPIS == 0.0f)
						_hoops_SAIS |= _hoops_IRIS;
				}

				if (_hoops_PPIS > 0.0f) {
					float _hoops_GIHIC = 0.0f;

					switch (_hoops_HAIS) {
						case _hoops_PRIS: {
							_hoops_RPIS = cuboid.max.x - cuboid.min.x;
							_hoops_GIHIC = (cuboid.max.x + cuboid.min.x) * 0.5f;
						} break;
						case _hoops_HRIS: {
							_hoops_RPIS = cuboid.max.y - cuboid.min.y;
							_hoops_GIHIC = (cuboid.max.y + cuboid.min.y) * 0.5f;
						} break;
						case _hoops_IRIS: {
							_hoops_RPIS = cuboid.max.z - cuboid.min.z;
							_hoops_GIHIC = (cuboid.max.z + cuboid.min.z) * 0.5f;
						} break;
					}

					_hoops_SASC	_hoops_RCCHC[2];

					for (int i = 0; i < 2; i++) {
						/* _hoops_HSPP _hoops_CCA _hoops_RH _hoops_SHSC _hoops_IPIS, _hoops_PSCR _hoops_SR _hoops_RIHIC _hoops_SAHR _hoops_SPR _hoops_SPIS */
						_hoops_RCCHC[i] = cuboid;

#define	_hoops_RRIS				0.15f
						switch (_hoops_HAIS) {
							case _hoops_PRIS: {
								if (i == 0)
									_hoops_RCCHC[i].max.x = _hoops_GIHIC + _hoops_RRIS * _hoops_RPIS;
								else
									_hoops_RCCHC[i].min.x = _hoops_GIHIC - _hoops_RRIS * _hoops_RPIS;
							}	break;

							case _hoops_HRIS: {
								if (i == 0)
									_hoops_RCCHC[i].max.y = _hoops_GIHIC + _hoops_RRIS * _hoops_RPIS;
								else
									_hoops_RCCHC[i].min.y = _hoops_GIHIC - _hoops_RRIS * _hoops_RPIS;
							}	break;

							case _hoops_IRIS: {
								if (i == 0)
									_hoops_RCCHC[i].max.z = _hoops_GIHIC + _hoops_RRIS * _hoops_RPIS;
								else
									_hoops_RCCHC[i].min.z = _hoops_GIHIC - _hoops_RRIS * _hoops_RPIS;
							}	break;
						}
					}

					if (_hoops_CAHIC (_hoops_ARCAR, root, &items, root, _hoops_RCCHC, 2, false))
						_hoops_SHHIC = true;

					_hoops_SAIS |= _hoops_HAIS;
				}
				else
					ASSERT(ALLBITS (_hoops_SAIS, _hoops_PRIS|_hoops_HRIS|_hoops_IRIS));
			}

			if (items != null &&
				_hoops_CAHIC (_hoops_ARCAR, root, &items, root, null, 2, true))
				_hoops_SHHIC = true;

			ASSERT(items == null);

			if (_hoops_SHHIC) {
				// _hoops_HHGSI _hoops_IASC
				root->_hoops_HSRIR = null;
				if (root->geometry != null) {
					Bounding	_hoops_IPRIC;
					if ((geometry = root->geometry) != null) do {
						Bounding	_hoops_SCIIA;
						if (HI_Figure_Geometry_Bounding (geometry, _hoops_SCIIA))
							_hoops_IPRIC.Merge (_hoops_SCIIA);
						geometry = geometry->next;
					} while (geometry != null);
					root->_hoops_HSRIR = _hoops_IPRIC;
				}
			}
		}

		if (items != null) {
			_hoops_IAHIC *	item = items;
			while (item != null) {
				_hoops_IAHIC *	_hoops_ISSRH = item->next;
				FREE(item, _hoops_IAHIC);
				item = _hoops_ISSRH;
			}
		}

		if (_hoops_SISAA != null) {
			if (root->_hoops_RGRPR == null) {
				root->_hoops_RGRPR = _hoops_SISAA;
				_hoops_SISAA->backlink = &root->_hoops_RGRPR;
			}
			else {
				Subsegment *	tail = root->_hoops_RGRPR;
				while (tail->next != null)
					tail = tail->next;

				/* _hoops_CSSCI _hoops_SGHC _hoops_HIGR */
				tail->next = _hoops_SISAA;
				_hoops_SISAA->backlink = &tail->next;
			}
		}
	}

	Subsegment *	_hoops_HHIHR = root->_hoops_RGRPR;

	// _hoops_GHHA _hoops_IGIAR _hoops_HCR _hoops_RH _hoops_ARAH-_hoops_SPSHI
	if (_hoops_HHIHR != null) do {
		if (!BIT(_hoops_HHIHR->_hoops_RRHH, _hoops_SACHC)) {
			if (_hoops_HHIHR->type == _hoops_IRCP) {
				_hoops_CRCP *		_hoops_SRCP = (_hoops_CRCP*)_hoops_HHIHR;
				_hoops_GHAIR *	h = null;

				//_hoops_RPP (_hoops_AIHIC) // _hoops_SIGPA _hoops_GPRR _hoops_PPR _hoops_IGRI _hoops_PISI _hoops_ARAH-_hoops_HHIS
					h = _hoops_RCGIC(_hoops_ARCAR, _hoops_SRCP->_hoops_IPPGR);

				if ((h == null || h->_hoops_RRCRP < _hoops_CHPIC) &&
					_hoops_SRCP->_hoops_RGRPR != null || _hoops_SRCP->geometry != null)
					_hoops_CHHIC (_hoops_ARCAR, _hoops_SRCP, level, flags);
			}
			else if (BIT(_hoops_ARCAR->flags, _hoops_RGCHC)) {
				_hoops_CRCP *	_hoops_SRCP = _hoops_SSIGP (_hoops_HHIHR);
				if (_hoops_ARCAR->_hoops_GGRHH->LookupItem(_hoops_SRCP) != VHASH_STATUS_SUCCESS) {
					_hoops_ARCAR->_hoops_GGRHH->InsertItem(_hoops_SRCP);
					_hoops_CHHIC (_hoops_ARCAR, _hoops_SRCP, 1, flags);
				}
			}

			_hoops_HHIHR->_hoops_RRHH &= ~_hoops_SACHC;
		}
	} while ((_hoops_HHIHR = _hoops_HHIHR->next) != null);
}

typedef VHash<Integer32, _hoops_IIPSA *> _hoops_PIHIC;

#define _hoops_HIHIC			_hoops_GSHGP

local void _hoops_IIHIC(_hoops_ICCHC * _hoops_ARCAR, _hoops_CRCP * _hoops_SRCP);

local void _hoops_CIHIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			root,
	int					level,
	_hoops_GICHC *		_hoops_IICHC,
	bool				_hoops_HCGIC) {

	if (level++ > 32)
		return;

	Subsegment *	_hoops_SIIS = root->_hoops_RGRPR;

	if (_hoops_SIIS == null)
		return;

	_hoops_SSAGR(_hoops_SIIS);

	Subsegment *	_hoops_SIHIC = null;
	Subsegment *	_hoops_GCHIC = null;
	Subsegment *	_hoops_RCHIC = null;

	Subsegment *	next;

	int 			_hoops_ACHIC = 0;
	int				_hoops_PCHIC = 0;


	_hoops_PIHIC * _hoops_HCHIC = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_PIHIC)(_hoops_ARCAR->memory_pool);

	if (_hoops_SIIS != null) do {
		next = _hoops_SIIS->next;
		_hoops_SSAGR(next);

		if (_hoops_IICHC && _hoops_IICHC->_hoops_AICHC == _hoops_SIIS)
			break;

		_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_SIIS);

		_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_SIIS;

#if 0
		if (_hoops_SRCP->type == _hoops_IRCP) {
			if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 17682")) {
				_hoops_ARCAR=_hoops_ARCAR;
			}
			if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 17693")) {
				_hoops_ARCAR=_hoops_ARCAR;
			}
		}
#endif


		if (_hoops_SIIS->type == _hoops_IRCP &&
			!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_HIHIC|_hoops_SHSIR|_hoops_GISIR|_hoops_GIPSA|_hoops_PACAA) &&
			!BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HACHC) &&
			_hoops_SIIS->priority == 0 &&
			_hoops_SRCP->_hoops_SGRPR() == null &&
			!BIT(_hoops_SRCP->_hoops_RRHH, _hoops_IRPGI)) {

			_hoops_ACHIC++;

			Attribute * _hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR;
			int key = 1;

			while (_hoops_HPHCR != null) {
				_hoops_SSAGR(_hoops_HPHCR->next);
				key += _hoops_HHAIC(_hoops_HPHCR);
				_hoops_HPHCR = _hoops_HPHCR->next;
			}

			_hoops_IIPSA * sl;

			_hoops_HCHIC->LookupItem(key, &sl);

			if (sl == null) {
				sl = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_IIPSA)(_hoops_ARCAR->memory_pool);
				_hoops_HCHIC->InsertItem(key, sl);
			}

			sl->AddFirst(_hoops_SRCP);

			if ((_hoops_SIIS->next = _hoops_RCHIC) != null)
				_hoops_RCHIC->backlink = &_hoops_SIIS->next;
			_hoops_RCHIC = _hoops_SIIS;
		}
		else {
			_hoops_PCHIC++;

			if ((_hoops_SIIS->next = _hoops_SIHIC) != null)
				_hoops_SIHIC->backlink = &_hoops_SIIS->next;
			_hoops_SIHIC = _hoops_SIIS;
			if (_hoops_GCHIC == null)
				_hoops_GCHIC = _hoops_SIIS;
		}
	} while ((_hoops_SIIS = next) != null);

	if (_hoops_SIHIC) {
		if (_hoops_IICHC) {
			if (_hoops_IICHC->_hoops_AICHC) {
				if ((_hoops_GCHIC->next = root->_hoops_RGRPR) != null)
					root->_hoops_RGRPR->backlink = &_hoops_GCHIC->next;
				_hoops_SIHIC->backlink = &root->_hoops_RGRPR;
				root->_hoops_RGRPR = _hoops_SIHIC;
			}
			else {
				root->_hoops_RGRPR = _hoops_SIHIC;
				_hoops_SIHIC->backlink = &root->_hoops_RGRPR;
			}

			_hoops_IICHC->_hoops_AICHC = root->_hoops_RGRPR;
		}
		else if (_hoops_SIHIC) {
			root->_hoops_RGRPR = _hoops_SIHIC;
			_hoops_SIHIC->backlink = &root->_hoops_RGRPR;
		}
	}

	if (_hoops_RCHIC) {
		int	_hoops_ICHIC = 0;
		int	_hoops_CCHIC = 0;
		_hoops_APCHC * _hoops_SCHIC = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_APCHC)(_hoops_ARCAR->memory_pool);

		/* _hoops_CGH _hoops_SHH _hoops_SHSS _hoops_IS _hoops_HASC "_hoops_SGHC" _hoops_PGAP _hoops_HS _hoops_PIS _hoops_AIRC */
		while (_hoops_RCHIC != null) {
			_hoops_CRCP *			_hoops_SRCP = (_hoops_CRCP *)_hoops_RCHIC;
			Subsegment *		_hoops_GIPIA = null;

			// _hoops_GA'_hoops_RA _hoops_HPPR _hoops_IS _hoops_GSHIC _hoops_APRS _hoops_RSHIC
			if (_hoops_SCHIC->LookupItem(_hoops_RCHIC) == VHASH_STATUS_FAILED) {
				Attribute *			_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR;
				int key = 1;

				while (_hoops_HPHCR != null) {
					_hoops_SSAGR(_hoops_HPHCR->next);
					key += _hoops_HHAIC(_hoops_HPHCR);
					_hoops_HPHCR = _hoops_HPHCR->next;
				}

				_hoops_IIPSA * sl;
				_hoops_HCHIC->LookupItem(key, &sl);
				ASSERT(sl);

				sl->ResetCursor();

				_hoops_PCCAR {
					_hoops_CRCP * _hoops_GIAIC;

					while (1) {
						_hoops_GIAIC = sl->PeekCursor();
						if (_hoops_GIAIC != _hoops_SRCP)
							break;
						sl->AdvanceCursor();
					}

					if (!_hoops_GIAIC) {
						_hoops_GIPIA = null;
						/* _hoops_PSP _hoops_RRI _hoops_IS _hoops_ISPR, _hoops_PSP _hoops_PSSP */
						_hoops_ICHIC++;
						break;
					}

#if 0
					if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 17682")) {
						_hoops_ARCAR=_hoops_ARCAR;
					}
					if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 17693")) {
						_hoops_ARCAR=_hoops_ARCAR;
					}
					if (_hoops_GIAIC->name.text && strstr(_hoops_GIAIC->name.text, "-- 17682")) {
						_hoops_ARCAR=_hoops_ARCAR;
					}
					if (_hoops_GIAIC->name.text && strstr(_hoops_GIAIC->name.text, "-- 17693")) {
						_hoops_ARCAR=_hoops_ARCAR;
					}
#endif

					if (_hoops_SHAIC (_hoops_ARCAR, _hoops_GIAIC, _hoops_SRCP)) {
						_hoops_GIPIA = (Subsegment*)_hoops_GIAIC;
						sl->Remove(_hoops_SRCP);
						/* _hoops_GGHP _hoops_SPR */
						_hoops_CCHIC++;
						break;
					}

					sl->AdvanceCursor();
				}
			}

			next = _hoops_RCHIC->next;

			if (_hoops_GIPIA != null) {
#if 0
				if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 2209")) {
					_hoops_ARCAR=_hoops_ARCAR;
				}
				if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 2387")) {
					_hoops_ARCAR=_hoops_ARCAR;
				}
#endif

				_hoops_SCHIC->ReplaceItem(_hoops_GIPIA, 1);

				_hoops_GIPIA->_hoops_RRHH |= _hoops_SRCP->_hoops_RRHH&(_hoops_PACHC|_hoops_IACHC);

				if (BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_PACHC))
					_hoops_GIPIA->_hoops_RRHH |= _hoops_SACHC;

				if (_hoops_SRCP->geometry) {
					/* _hoops_IHIS _hoops_GRR _hoops_CPAP _hoops_IGCI _hoops_CRGR _hoops_RH _hoops_APRS _hoops_CAGH '_hoops_HHASA' */
					if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
						while (_hoops_SRCP->geometry != null)
							_hoops_GRAPA (_hoops_ARCAR, _hoops_SRCP->geometry, (_hoops_CRCP *)_hoops_GIPIA, true);
					}
					else
						_hoops_SPSHC(_hoops_ARCAR, _hoops_SRCP, (_hoops_CRCP *)_hoops_GIPIA);
				}

				/* _hoops_IHIS _hoops_GII _hoops_CHAPA _hoops_HII _hoops_PHHIP _hoops_CRGR '_hoops_HHASA' _hoops_GACC */
				Subsegment *	_hoops_SIIS;
				_hoops_CRCP *		_hoops_CPHIC = (_hoops_CRCP *)_hoops_GIPIA;

				while ((_hoops_SIIS = _hoops_SRCP->_hoops_RGRPR) != null) {
					_hoops_CRCP *	_hoops_ASHIC = _hoops_SSIGP(_hoops_SIIS);

					if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC))
						_hoops_RAGSA (_hoops_ARCAR, _hoops_ASHIC, _hoops_SRCP, (_hoops_CRCP *)_hoops_GIPIA);

					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_SIIS);
					if ((_hoops_SIIS->next = _hoops_CPHIC->_hoops_RGRPR) != null)
						_hoops_SIIS->next->backlink = &_hoops_SIIS->next;
					_hoops_SIIS->backlink = &_hoops_CPHIC->_hoops_RGRPR;
					_hoops_CPHIC->_hoops_RGRPR = _hoops_SIIS;
					_hoops_SIIS->owner = (_hoops_CRCP *)_hoops_GIPIA;
				}

				HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, (_hoops_CRCP *)_hoops_GIPIA, _hoops_SRCP->_hoops_RCGC);
				/* _hoops_APRI '_hoops_PHHIP' */
				HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP);

				_hoops_HPRH (_hoops_SRCP);
			}
			else {	/* _hoops_PSP _hoops_PIGGP _hoops_CAGH, _hoops_CSSCI _hoops_RRGI _hoops_SRRPR */
				if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC))
					_hoops_RRSHC (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCP);

				_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_RCHIC, root);

				_hoops_RCHIC->owner = root;
			}

			_hoops_RCHIC = next;

			if (_hoops_ICHIC-_hoops_CCHIC > _hoops_ARCAR->_hoops_SSCHC) {
				// _hoops_RCRP _hoops_GH
				while (_hoops_RCHIC != null) {
					next = _hoops_RCHIC->next;
					_hoops_SSAGR(next);

					if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC))
						_hoops_RRSHC (_hoops_ARCAR->_hoops_RIGC, (_hoops_CRCP*)_hoops_RCHIC);

					_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_RCHIC, root);

					_hoops_RCHIC->owner = root;

					_hoops_RCHIC = next;
				}
				break;
			}
		}

		delete _hoops_SCHIC;
	}

	if (_hoops_IICHC) {
		// _hoops_AA _hoops_RGAR _hoops_CCAH _hoops_PSHIC
		_hoops_IICHC->_hoops_AICHC = root->_hoops_RGRPR;
		_hoops_IICHC->_hoops_RICHC = 0;
	}

	if (_hoops_HCHIC) {
		if (_hoops_HCHIC->Count() > 0)
			_hoops_HCHIC->DeleteItems();
		delete _hoops_HCHIC;
	}

	// _hoops_GHHA _hoops_IGIAR _hoops_HIGR _hoops_IIGR _hoops_GIGR _hoops_ARAH-_hoops_SPSHI
	if ((_hoops_SIIS = root->_hoops_RGRPR) != null) do {
		_hoops_CRCP *		_hoops_SRCP;

		if (!_hoops_HCGIC && _hoops_SIIS == _hoops_SIHIC &&
			!BIT(_hoops_ARCAR->flags, _hoops_RGCHC))
			break;

		if (_hoops_SIIS->type == _hoops_IRCP) {
			_hoops_SRCP = (_hoops_CRCP *)_hoops_SIIS;

#if 0
			if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 8853")) {
				_hoops_ARCAR=_hoops_ARCAR;
			}
#endif

			if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_HIHIC|_hoops_SHSIR|_hoops_GISIR|_hoops_GIPSA)) {
				if (_hoops_HCGIC && _hoops_SRCP->_hoops_RGRPR != null &&
					BIT(_hoops_SRCP->_hoops_RRHH, _hoops_SACHC)) {

					_hoops_PGRIC(_hoops_ARCAR, _hoops_SRCP);

					if (BIT(_hoops_ARCAR->flags, _hoops_PRCHC))
						_hoops_IIHIC(_hoops_ARCAR, _hoops_SRCP);
					else
						_hoops_GARIC(_hoops_ARCAR, _hoops_SRCP, false);
				}

				if (_hoops_HCGIC && _hoops_SRCP->_hoops_RGRPR != null)
					_hoops_CIHIC (_hoops_ARCAR, _hoops_SRCP, level, null, _hoops_HCGIC);
			}

			_hoops_SRCP->_hoops_RRHH &= ~_hoops_SACHC;
		}
		else if (BIT(_hoops_ARCAR->flags, _hoops_RGCHC)) {
			_hoops_SRCP = _hoops_SSIGP (_hoops_SIIS);

			if (_hoops_ARCAR->_hoops_GGRHH->LookupItem(_hoops_SRCP) != VHASH_STATUS_SUCCESS) {
				_hoops_ARCAR->_hoops_GGRHH->InsertItem(_hoops_SRCP);
				_hoops_CIHIC (_hoops_ARCAR, _hoops_SRCP, 1, null, _hoops_HCGIC);
			}
		}
	} while ((_hoops_SIIS = _hoops_SIIS->next) != null);
}

local bool _hoops_HSHIC (
	_hoops_CRCP const *		_hoops_SRCP,
	int					type) {
	Attribute *			_hoops_HPHCR;

	if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) do {
		if (_hoops_HPHCR->type >= type) {
			if (_hoops_HPHCR->type == type)
				return true;
			break;
		}
	} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

	return false;
}

local void _hoops_ISHIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			root,
	int					level,
	int					_hoops_RCCRR,
	bool				_hoops_HCGIC) {

	if (level++ > 32)
		return;

	Subsegment *	_hoops_HHIHR = root->_hoops_RGRPR;

	if (_hoops_HHIHR == null)
		return;

	Subsegment *	_hoops_SISAA = null;
	Subsegment *	tail = null;
	Subsegment *	next;

	if (_hoops_HHIHR != null) do {
		next = _hoops_HHIHR->next;

		if (_hoops_HHIHR->type == _hoops_IRCP &&
			!ANYBIT (_hoops_HHIHR->_hoops_RRHH, _hoops_PACHC|_hoops_IACHC|_hoops_HACHC) &&
			_hoops_HSHIC((_hoops_CRCP const *)_hoops_HHIHR, _hoops_RCCRR)) {
			_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_HHIHR);
			if (_hoops_SISAA == null)
				_hoops_SISAA = tail = _hoops_HHIHR;
			else {
				tail->next = _hoops_HHIHR;
				_hoops_HHIHR->backlink = &tail->next;
				tail = _hoops_HHIHR;
			}
		}
	} while ((_hoops_HHIHR = next) != null);

	_hoops_HHIHR = root->_hoops_RGRPR;

	if (_hoops_SISAA != null) {
		/* _hoops_PAHH _hoops_HAR _hoops_SIGR, _hoops_HIH _hoops_ICIC */
		_hoops_SISAA->backlink = &_hoops_SISAA;

		/* _hoops_IRS _hoops_SASI _hoops_IGRI */
		_hoops_PGSHC **		_hoops_SPHHR = null;

		/* _hoops_RPP _hoops_ASAIC _hoops_RAIA _hoops_IRS _hoops_SCAH _hoops_GASR */
		if (_hoops_RCCRR == HK_COLOR || _hoops_RCCRR == HK_MODELLING_MATRIX)
			POOL_ZALLOC_ARRAY_CACHED (_hoops_SPHHR, _hoops_SPAIC, _hoops_PGSHC *, _hoops_ARCAR->memory_pool);

		while (_hoops_SISAA != null) {
			_hoops_CRCP *			_hoops_SRCP = (_hoops_CRCP *)_hoops_SISAA;
			Subsegment *		_hoops_CSHIC = root->_hoops_RGRPR;
			Attribute *			_hoops_SSHIC = null;
			int					_hoops_HPPSH = 0;
			bool				_hoops_GGIIC = true;
			int					_hoops_ICAIC = 0;

			next = _hoops_SISAA->next;

			if (_hoops_RCCRR == HK_COLOR || _hoops_RCCRR == HK_MODELLING_MATRIX) {
				/* _hoops_CACH _hoops_RPP _hoops_SR _hoops_HS _hoops_IRS _hoops_HAIR/_hoops_RSGA _hoops_GPP _hoops_PHHIP, _hoops_IAII _hoops_IHAGH _hoops_GIPHR _hoops_CGH _hoops_AA _hoops_IHRI */
				Attribute const *	_hoops_RGIIC;

				if ((_hoops_RGIIC = _hoops_SRCP->_hoops_IPPGR) != null) do {
					if (_hoops_RGIIC->type >= _hoops_RCCRR) {
						if (_hoops_RGIIC->type > _hoops_RCCRR)
							_hoops_RGIIC = null;
						break;
					}
				} while ((_hoops_RGIIC = _hoops_RGIIC->next) != null);

				if (_hoops_RGIIC != null) {
					_hoops_PGSHC *		ref;

					_hoops_CSHIC = null;	/* _hoops_HCCPR _hoops_SR _hoops_HGCR _hoops_IRS _hoops_PSSP */

					if (_hoops_RCCRR == HK_COLOR)
						_hoops_ICAIC = _hoops_AHAIC ((_hoops_SSGI const *)_hoops_RGIIC);
					else
						_hoops_ICAIC = _hoops_PHAIC ((_hoops_ISGI const *)_hoops_RGIIC);

					if ((ref = _hoops_SPHHR[_hoops_ICAIC]) != null) do {
						if (_hoops_HIRIC (_hoops_ARCAR, ref->_hoops_ASGPR, _hoops_RGIIC)) {
							_hoops_CSHIC = (Subsegment *)ref->_hoops_ASGPR->owner;
							break;
						}
					} while ((ref = ref->next) != null);

					if (_hoops_CSHIC == null) {
						/* _hoops_PCACR _hoops_CAHP _hoops_RH _hoops_HPSH _hoops_RPR _hoops_GAR _hoops_RPP _hoops_SR _hoops_RIAGR _hoops_IGI _hoops_RH _hoops_SHISR _hoops_GIPHR _hoops_CAPP */
						_hoops_CSHIC = root->_hoops_RGRPR;
						while (_hoops_CSHIC != _hoops_HHIHR) {
							_hoops_CSHIC = _hoops_CSHIC->next;
							++_hoops_HPPSH;
						}
						_hoops_CSHIC = null;
					}

					_hoops_GGIIC = false;
				}
			}

			if (_hoops_GGIIC) _hoops_PCCAR {
				/* _hoops_RPP (_hoops_AGIIC == _hoops_IRAP) _hoops_RIHH; */
				if (_hoops_CSHIC == _hoops_HHIHR) {
					_hoops_CSHIC = null;	/* _hoops_PSP _hoops_RRI _hoops_IS _hoops_ISPR, _hoops_PSP _hoops_PSSP */
					break;
				}
				if (!BIT(_hoops_CSHIC->_hoops_RRHH, _hoops_PACHC) &&
					_hoops_CSHIC->type == _hoops_IRCP &&
					_hoops_CIAIC (_hoops_ARCAR, (_hoops_CRCP const *)_hoops_CSHIC, _hoops_SRCP, _hoops_RCCRR))
					break;					/* _hoops_GGHP _hoops_SPR */

				_hoops_CSHIC = _hoops_CSHIC->next;
				++_hoops_HPPSH;
			}

			/* _hoops_RH _hoops_CAGH _hoops_GRS _hoops_PSP _hoops_RPIP _hoops_HS _hoops_GII _hoops_HHHA _hoops_IGRI _hoops_IH _hoops_RGR _hoops_GPRR */
			_hoops_SSHIC = _hoops_SIAIC (_hoops_ARCAR, _hoops_SRCP, _hoops_RCCRR);

			if (_hoops_CSHIC == null) {
				/* _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SIHGA */
				_hoops_PHRHH (_hoops_ARCAR->_hoops_RIGC, _hoops_ARCAR->_hoops_RGSHC, "internal container %d-%d", _hoops_RCCRR, _hoops_HPPSH);
				_hoops_CRCP *	_hoops_HHGSA = _hoops_HASHC(_hoops_ARCAR, root, _hoops_ARCAR->_hoops_RGSHC, _hoops_IACHC);
				_hoops_CSHIC = (Subsegment *)_hoops_HHGSA;
#if 0
				if (_hoops_HHGSA->name.text && strstr(_hoops_HHGSA->name.text, "-- 276782")) {
					_hoops_ARCAR=_hoops_ARCAR;
				}
#endif
				/* _hoops_GRHP _hoops_RH _hoops_IGRI(_hoops_GRI) (_hoops_RPP _hoops_GII) _hoops_HII _hoops_RH _hoops_CAGH */
				if ((_hoops_HHGSA->_hoops_IPPGR = _hoops_SSHIC) != null) {
					_hoops_SSHIC->backlink = &_hoops_HHGSA->_hoops_IPPGR;
					do {
						_hoops_SSHIC->owner = _hoops_HHGSA;
						if (_hoops_SSHIC->type == _hoops_IPAIR) {
							_hoops_CPAIR *		_hoops_SPAIR = (_hoops_CPAIR *)_hoops_SSHIC;
							int			i;

							for (i=0; i<_hoops_SPAIR->count; i++) {
								if (_hoops_SPAIR->textures[i]->owner == (_hoops_HPAH *)_hoops_SRCP)
									_hoops_SPAIR->textures[i]->owner = (_hoops_HPAH *)_hoops_HHGSA;
							}
						}
						else if (_hoops_SSHIC->type == HK_COLOR ||
								 _hoops_SSHIC->type == HK_MODELLING_MATRIX) {
							_hoops_PGSHC *		ref;

							POOL_ALLOC (ref, _hoops_PGSHC, _hoops_ARCAR->memory_pool);
							ref->_hoops_ASGPR = _hoops_SSHIC;
							ref->next = _hoops_SPHHR[_hoops_ICAIC];
							_hoops_SPHHR[_hoops_ICAIC] = ref;
						}
					} while ((_hoops_SSHIC = _hoops_SSHIC->next) != null);
				}
			}
			else {
				/* _hoops_APRI _hoops_RH _hoops_SSRS _hoops_IGRI(_hoops_GRI) */
				while (_hoops_SSHIC != null) {
					Attribute *		victim = _hoops_SSHIC;

					_hoops_SSHIC = _hoops_SSHIC->next;
					_hoops_HPRH (victim);
				}
			}

			if (_hoops_SRCP->_hoops_RGRPR != null)
				_hoops_CSHIC->_hoops_RRHH |= _hoops_SACHC;

			if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
				_hoops_RRSHC (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCP);
				_hoops_RAGSA (_hoops_ARCAR, _hoops_SRCP, _hoops_SRCP->owner, (_hoops_CRCP *)_hoops_CSHIC);
			}

			_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_SISAA, (_hoops_CRCP alter *)_hoops_CSHIC);

			_hoops_SISAA->owner = (_hoops_CRCP *)_hoops_CSHIC;

			if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC)) {
				if (_hoops_SRCP->bounding != null)
					HI_Propagate_Bounding (_hoops_ARCAR->_hoops_RIGC, (_hoops_CRCP *)_hoops_CSHIC, _hoops_SRCP->bounding, _hoops_SRCP);
			}

			HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, (_hoops_CRCP *)_hoops_CSHIC, _hoops_SRCP->_hoops_RCGC);

			_hoops_SISAA = next;
		}

		if (_hoops_SPHHR != null) {
			for (int i=0; i<_hoops_SPAIC; i++) {
				_hoops_PGSHC *		ref;

				while ((ref = _hoops_SPHHR[i]) != null) {
					_hoops_SPHHR[i] = ref->next;
					FREE (ref, _hoops_PGSHC);
				}
			}
			FREE_ARRAY (_hoops_SPHHR, _hoops_SPAIC, _hoops_PGSHC *);
		}

		// _hoops_IHIS _hoops_CCAH _hoops_SPSHI _hoops_IS _hoops_SIHGA _hoops_HIGR _hoops_RPP _hoops_SSIA _hoops_HS _hoops_PGIIC
		_hoops_SISAA = root->_hoops_RGRPR;
		if (_hoops_SISAA != null) do {
			next = _hoops_SISAA->next;

			if (BIT(_hoops_SISAA->_hoops_RRHH, _hoops_SACHC)) {
				_hoops_SISAA->_hoops_RRHH &= ~_hoops_SACHC;

				_hoops_PCGIC (_hoops_ARCAR, (_hoops_CRCP*)_hoops_SISAA, true, false);

				if (_hoops_HHIHR == null) {
					if (next != null) {
						_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_SISAA);
						_hoops_HHIHR=next;
						while (_hoops_HHIHR->next != null)
							_hoops_HHIHR = _hoops_HHIHR->next;
						_hoops_HHIHR->next = _hoops_SISAA;
						_hoops_SISAA->backlink = &_hoops_HHIHR->next;
					}
				}
				else if (next != _hoops_HHIHR) {
					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_SISAA);
					_hoops_SISAA->backlink = _hoops_HHIHR->backlink;
					*_hoops_SISAA->backlink = _hoops_SISAA;
					if ((_hoops_SISAA->next = _hoops_HHIHR) != null)
						_hoops_HHIHR->backlink = &_hoops_SISAA->next;
				}
				else
					next = null;	// _hoops_RRS _hoops_HII _hoops_CPIC _hoops_CRGR _hoops_PGHC _hoops_SPSHI
				_hoops_HHIHR = _hoops_SISAA;
			}
		} while ((_hoops_SISAA = next) != null && _hoops_SISAA != _hoops_HHIHR);
	}

	_hoops_SISAA = root->_hoops_RGRPR;

	// _hoops_GHHA _hoops_IGIAR _hoops_HIGR _hoops_IIGR _hoops_GIGR _hoops_ARAH-_hoops_SPSHI _hoops_IPSH _hoops_CCAH _hoops_SPSHI
	if (_hoops_HHIHR != null) do {
		if (_hoops_HHIHR->type == _hoops_IRCP) {
			_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_HHIHR;
			if (_hoops_SRCP->_hoops_RGRPR != null &&
				(_hoops_HCGIC ||
				 !BIT(_hoops_SRCP->_hoops_RRHH, _hoops_PACHC))) {

				_hoops_ISHIC (_hoops_ARCAR, _hoops_SRCP, level, _hoops_RCCRR, _hoops_HCGIC);
			}
		}
		else if (BIT(_hoops_ARCAR->flags, _hoops_RGCHC)) {
			_hoops_CRCP *	_hoops_SRCP = _hoops_SSIGP (_hoops_HHIHR);

			if (_hoops_ARCAR->_hoops_GGRHH->LookupItem(_hoops_SRCP) != VHASH_STATUS_SUCCESS) {
				_hoops_ARCAR->_hoops_GGRHH->InsertItem(_hoops_SRCP);
				_hoops_ISHIC (_hoops_ARCAR, _hoops_SRCP, 1, _hoops_RCCRR, _hoops_HCGIC);
			}
		}
		ASSERT (_hoops_HHIHR->next != _hoops_HHIHR);  //_hoops_RPP _hoops_RGR _hoops_HGIIC, _hoops_SR'_hoops_ASAR _hoops_GGR _hoops_PCCP _hoops_PGGS _hoops_HAPR
	} while ((_hoops_HHIHR = _hoops_HHIHR->next) != null);
}



local void _hoops_IGIIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP,
	Bounding const &	bounding) {

	UNREFERENCED(bounding);

#if 0
if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 48065")) {
	_hoops_SRCP=_hoops_SRCP;
}
#endif

	bool	_hoops_CGIIC = !BIT(_hoops_ARCAR->flags, _hoops_PRCHC);

	_hoops_SRCP->_hoops_RRHH &= ~(_hoops_PACHC | _hoops_IACHC | _hoops_HACHC | _hoops_CACHC | _hoops_SACHC);

	if (!BIT(_hoops_ARCAR->flags, _hoops_PRCHC) &&
		_hoops_SRCP->_hoops_GACP == null && _hoops_SRCP->geometry != null) {
		Geometry *		geometry = _hoops_SRCP->geometry;

		_hoops_SRCP->_hoops_GACP = NEW(_hoops_AAIGP)();

		do {
			Type		type = geometry->type;
			int			_hoops_CPIGP = _hoops_IIAGR(geometry->type);

			_hoops_SRCP->_hoops_GACP->set (_hoops_CPIGP, geometry);

			do geometry = geometry->next;
			while (geometry != null && geometry->type == type &&
					!BIT (geometry->_hoops_RRHH, _hoops_PASIR));
		} while (geometry != null && !BIT (geometry->_hoops_RRHH, _hoops_PASIR));
		_hoops_SRCP->_hoops_GACP->set (_hoops_RACP, geometry);
	}

	Attribute * _hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR;
	while (_hoops_HPHCR) {
		_hoops_HPHCR->_hoops_RRHH &= ~_hoops_SACHC;

		switch (_hoops_HPHCR->type) {
			case _hoops_CPPIR: {
				_hoops_SPPIR alter *		c = (_hoops_SPPIR alter *)_hoops_HPHCR;
				c->_hoops_PRGCA = 0;
			} break;

			case HK_USER_OPTIONS: {
				_hoops_HPPIR alter *	_hoops_IPPIR = (_hoops_HPPIR alter *)_hoops_HPHCR;

				if (!BIT(_hoops_ARCAR->flags, _hoops_HGCHC)) {
					if (_hoops_IPPIR->_hoops_IGGSA && _hoops_IPPIR->_hoops_IGGSA->Count() > 1)
						HI_Distill_User_Options(_hoops_ARCAR->_hoops_RIGC, _hoops_IPPIR, _hoops_ACIAP|_hoops_PCIAP);
				}

				_hoops_IPPIR->_hoops_PRGCA = 0;
			} break;

			default:break;
		}

		_hoops_HPHCR = _hoops_HPHCR->next;
	}

	Subsegment *		_hoops_GIPIA;
	int					_hoops_ASGIC = 0;

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) {
		_hoops_RAPIC * list = null;

		do {
			if (_hoops_GIPIA->type == _hoops_IRCP) {
				_hoops_CRCP *	_hoops_SIIS = (_hoops_CRCP *)_hoops_GIPIA;

				_hoops_IGIIC (_hoops_ARCAR, _hoops_SIIS, _hoops_SIIS->bounding);

				_hoops_IAPIC (_hoops_ARCAR, _hoops_SIIS->bounding, _hoops_SIIS, null, null, null, &list);
			}
			else {
				_hoops_PGRPR *	include = (_hoops_PGRPR *)_hoops_GIPIA;
				include->_hoops_RRHH &= ~_hoops_GPCHC;
			}

			_hoops_ASGIC++;
		} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);


		if (list != null) {
			float 	_hoops_CIPIC = MAX_FLOAT;
			float 	_hoops_SIPIC = -MAX_FLOAT;

			_hoops_RAPIC *x = list;

			while (x != null) {
				_hoops_RAPIC * _hoops_ACPIC = x->next;

				if (x->t == -1.0f) {
				}
				else {
					if (x->t > _hoops_SIPIC)
						_hoops_SIPIC = x->t;

					if (x->t < _hoops_CIPIC)
						_hoops_CIPIC = x->t;
				}

				x = _hoops_ACPIC;
			}

#define _hoops_SGIIC 100
			float	_hoops_CCPIC = (_hoops_SIPIC - _hoops_CIPIC);

			if (_hoops_CCPIC > 0.0f) {
			    float	_hoops_SCPIC = _hoops_CCPIC / (float)_hoops_SGIIC;

			    x = list;
			    while (x != null) {
				    _hoops_RAPIC * _hoops_ACPIC = x->next;
				    int i;

				    if (x->t == -1.0f) {
					    i = _hoops_SGIIC - 1;
				    }
				    else {
					    i = _hoops_SGIIC - 1 -(int)((x->t - _hoops_CIPIC) / _hoops_SCPIC);

					    if (i < 0)
						    i = 0;
					    else if (i > _hoops_SGIIC - 1)
						    i = _hoops_SGIIC - 1;
				    }

				    char	_hoops_RAPPH[8];

				    if (i < 10)
					    _hoops_RHRHH (_hoops_ARCAR->_hoops_RIGC, _hoops_RAPPH, "0%d", i);
				    else
					    _hoops_RHRHH (_hoops_ARCAR->_hoops_RIGC, _hoops_RAPPH, "%d", i);

				    _hoops_CRCP *	_hoops_SIIS = x->s;

				    if (_hoops_SIIS->name.length > 0) {
					    _hoops_GPIGI (_hoops_ARCAR->_hoops_RIGC, _hoops_ARCAR->_hoops_RGSHC, "%s-%n", _hoops_RAPPH, &_hoops_SIIS->name);
					    _hoops_RGAIR (_hoops_SIIS->name);
				    }
				    else {
					    char		unnamed[32];
					    _hoops_PASHC (_hoops_SRIGI (_hoops_ARCAR->_hoops_RIGC, unnamed, "-unnamed--#%X", _hoops_SIIS->key));
					    _hoops_IAIGI (_hoops_ARCAR->_hoops_RIGC, _hoops_ARCAR->_hoops_RGSHC, "%s-%s", _hoops_RAPPH, unnamed);
				    }
				    HI_Copy_Chars_To_Name (_hoops_ARCAR->_hoops_RGSHC, &_hoops_SIIS->name);
				    _hoops_CGIIC = true;

				    FREE(x, _hoops_RAPIC);
				    x = _hoops_ACPIC;
			    }
		    }
			else {
				x = list;
				while (x != null) {
					_hoops_RAPIC * _hoops_ACPIC = x->next;
					FREE(x, _hoops_RAPIC);
					x = _hoops_ACPIC;
				}
			}
		}
	}


	if (_hoops_CGIIC && _hoops_ASGIC > 1)
		_hoops_GPSHC (_hoops_SRCP, _hoops_ASGIC);
}

local void _hoops_GRIIC (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP) 
{
	// _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGRIR _hoops_HHSIR _hoops_GAR _hoops_SR _hoops_CHR _hoops_GIAA _hoops_IRS _hoops_IHSIR
	HI_Destroy_Fast_Lookups (_hoops_RIGC, _hoops_SRCP);

	Subsegment *	_hoops_GIPIA;
	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP)
			_hoops_GRIIC (_hoops_RIGC, (_hoops_CRCP *)_hoops_GIPIA);
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}


enum _hoops_RRIIC {
	// _hoops_HISAR _hoops_RAPSR _hoops_HPAP _hoops_IH _hoops_HH _hoops_RHPC _hoops_IGAA
	_hoops_ARIIC		= 0x00000100,
	_hoops_PRIIC		= 0x00000200,
	_hoops_HRIIC		= 0x00000400,
	_hoops_IRIIC			= 0x00000800,
	_hoops_CRIIC		= 0x00001000,
	_hoops_SRIIC		= 0x00002000,
	_hoops_GAIIC		= 0x00004000,
	_hoops_RAIIC			= 0x00008000,
	_hoops_AAIIC		= 0x00010000,
	_hoops_PAIIC		= 0x00020000,
	_hoops_HAIIC		= 0x00040000,
	_hoops_IAIIC		= 0x00080000,

	_hoops_CAIIC		= 0x00100000,
	_hoops_SAIIC		= 0x00200000,
	_hoops_GPIIC			= 0x00400000,
	_hoops_RPIIC			= 0x00800000,
	_hoops_APIIC		= 0x01000000,

	_hoops_PPIIC		= 0x02000000,
	_hoops_HPIIC		= 0x04000000,
	_hoops_IPIIC			= 0x10080000,
	_hoops_CPIIC			= 0x20000000,
	_hoops_SPIIC		= 0x40000000,
	_hoops_GHIIC		= 0x80000000
};

int _hoops_RHIIC (
	Shell const *		_hoops_SPHPR) {

	if (_hoops_SPHPR->_hoops_IPPGR != null && _hoops_SPHPR->_hoops_IPPGR->type != _hoops_CPCHC)
		return -1;					// _hoops_PAH _hoops_HAR _hoops_HASC

	Local_Vertex_Attributes const *	_hoops_SPRI = &_hoops_SPHPR->local_vertex_attributes;
	_hoops_RPGHR const *	lea = &_hoops_SPHPR->_hoops_IHHPR;
	Local_Face_Attributes const *	_hoops_CPRI = &_hoops_SPHPR->local_face_attributes;

	if (_hoops_SPRI->param_width > 128)
		return -1;					// _hoops_HAR _hoops_PRGI _hoops_GISI _hoops_HPPR

	if (_hoops_CPRI->regions != null)		// _hoops_GA'_hoops_RA _hoops_GCGH _hoops_HPHRA _hoops_APRS _hoops_PGHH
		return -1;

	// _hoops_PA _hoops_SHS _hoops_CGH _hoops_SHH _hoops_IHRI, _hoops_SAHR _hoops_RIP _hoops_SCH (_hoops_IAGCI _hoops_RRGPR _hoops_SCH _hoops_GGSR _hoops_GGR _hoops_RH _hoops_HISAR _hoops_RAPSR)
	int								result = _hoops_SPRI->param_width;

	if (_hoops_SPRI->_hoops_CPIAA > 0)
		result |= _hoops_ARIIC;
	if (_hoops_SPRI->_hoops_SIIPR > 0)
		result |= _hoops_PRIIC;
	if (_hoops_SPRI->_hoops_AHIIC > 0)
		result |= _hoops_HRIIC;
	if (_hoops_SPRI->_hoops_SCHHC > 0)
		result |= _hoops_IRIIC;
	if (_hoops_SPRI->_hoops_RSAPA > 0)
		result |= _hoops_CRIIC;
	if (_hoops_SPRI->_hoops_ICRRA > 0)
		result |= _hoops_SRIIC;
	if (_hoops_SPRI->_hoops_PCRRA > 0)
		result |= _hoops_GAIIC;
	if (_hoops_SPRI->_hoops_HIRRA > 0)
		result |= _hoops_RAIIC;
	if (_hoops_SPRI->_hoops_SCHPR > 0)
		result |= _hoops_AAIIC;
	if (_hoops_SPRI->_hoops_CCHPR > 0)
		result |= _hoops_PAIIC;
	if (_hoops_SPRI->_hoops_RCRHR > 0)
		result |= _hoops_HAIIC;
	if (_hoops_SPRI->_hoops_SIRHR > 0)
		result |= _hoops_IAIIC;

	if (lea->_hoops_CPIAA > 0)
		result |= _hoops_PPIIC;
	if (lea->_hoops_SIIPR > 0)
		result |= _hoops_HPIIC;
	if (lea->_hoops_HSRRA > 0)
		result |= _hoops_IPIIC;
	if (lea->_hoops_PSRRA > 0)
		result |= _hoops_CPIIC;
	if (lea->_hoops_SRAPA > 0)
		result |= _hoops_SPIIC;
	if (lea->_hoops_CCHHC > 0)
		result |= _hoops_GHIIC;

	if (_hoops_CPRI->_hoops_CPIAA > 0)
		result |= _hoops_CAIIC;
	if (_hoops_SPRI->_hoops_SIIPR > 0)
		result |= _hoops_SAIIC;
	if (_hoops_CPRI->_hoops_HSRRA > 0)
		result |= _hoops_GPIIC;
	if (_hoops_CPRI->_hoops_PSRRA > 0)
		result |= _hoops_RPIIC;
	if (_hoops_CPRI->_hoops_SRAPA > 0)
		result |= _hoops_APIIC;

	return result;
}

typedef VHash<int, Shell *> _hoops_PHIIC;

local void _hoops_HHIIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP) {

	if (_hoops_SRCP->geometry != null)  {
		Geometry *	geometry = _hoops_SRCP->geometry;
		Geometry *	_hoops_CCGPR;

		_hoops_PHIIC *	_hoops_IAPHA = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_PHIIC)(_hoops_ARCAR->memory_pool);

		do {
			_hoops_CCGPR = geometry->next;

			if (geometry->type == _hoops_SCIP) {
				Shell *		_hoops_SPHPR = (Shell *)geometry;

				if (_hoops_SPHPR->point_count == 0) {	// _hoops_SAHR _hoops_APRI _hoops_SCH _hoops_HA
					if (geometry->owner->_hoops_GACP != null)
						HI_Table_Remove_Geometry (geometry);
					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,geometry);
					HI_Delete_User_Key (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)geometry);
					_hoops_HPRH (geometry);
					continue;
				}

				int		_hoops_IHIIC = _hoops_RHIIC (_hoops_SPHPR);

				if (_hoops_IHIIC != -1) {		// "_hoops_CHIIC" _hoops_SCHS _hoops_GRS _hoops_SHH _hoops_RAAP _hoops_GGR _hoops_HGHC
					if (geometry->owner->_hoops_GACP != null)
						HI_Table_Remove_Geometry (geometry);
					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,geometry);

					Shell *	_hoops_HRSSA = _hoops_IAPHA->Lookup (_hoops_IHIIC);

					if (_hoops_HRSSA != null) {
						_hoops_SPHPR->next = _hoops_HRSSA->next;
						_hoops_HRSSA->next = _hoops_SPHPR;
					}
					else
						_hoops_IAPHA->InsertItem (_hoops_IHIIC, _hoops_SPHPR);
				}
			}
		} while ((geometry = _hoops_CCGPR) != null);


		_hoops_PHIIC::PairList *		pl = _hoops_IAPHA->GetPairList();
		_hoops_PHIIC::Pair *			p;

		while ((p = pl->RemoveFirst()) != null) {
			Shell *					_hoops_SHIIC = p->Item();
			Key						key = _hoops_AIRIR (_hoops_SHIIC);
			Geometry *				remaining = _hoops_SHIIC->next;

			delete p;

			// _hoops_SRS (_hoops_PAR _hoops_RGAR) _hoops_SAGGR _hoops_GIIIC _hoops_IS _hoops_CAGH
			HI_Insert_Geometry (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, _hoops_SHIIC, !BIT (_hoops_SHIIC->_hoops_RRHH, _hoops_RSPCR), 0, false);

			if (remaining != null) {	// _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_IIGR _hoops_RGR _hoops_GPRR, _hoops_RPR _hoops_CAPR _hoops_GH _hoops_PPR _hoops_HASC _hoops_CRGR _hoops_SRS
				Local_Vertex_Attributes *	_hoops_RIIIC = &_hoops_SHIIC->local_vertex_attributes;
				_hoops_RPGHR *		_hoops_AIIIC = &_hoops_SHIIC->_hoops_IHHPR;
				Local_Face_Attributes *		_hoops_PIIIC = &_hoops_SHIIC->local_face_attributes;
				int							_hoops_HIIIC = 1;
				Shell *						_hoops_SPHPR = (Shell *)remaining;
				int							_hoops_AAAHA = 0;
				int							_hoops_IIIIC = 0;
				int							_hoops_CIIIC = 0;
				int							_hoops_SIIIC = 0;

				if (_hoops_SHIIC->face_list == null && _hoops_SHIIC->tristrips != null)
					HI_Face_List_From_Tristrips (_hoops_ARCAR->_hoops_RIGC, _hoops_SHIIC);
				if (_hoops_SHIIC->_hoops_SPHA < 0)
					HI_Create_Shell_Edges (_hoops_SHIIC, false);

				do {
					if (_hoops_SPHPR->face_list == null && _hoops_SPHPR->tristrips != null)
						HI_Face_List_From_Tristrips (_hoops_ARCAR->_hoops_RIGC, _hoops_SPHPR);
					if (_hoops_SPHPR->_hoops_SPHA < 0)
						HI_Create_Shell_Edges (_hoops_SPHPR, false);

					++_hoops_HIIIC;
					_hoops_AAAHA += _hoops_SPHPR->point_count;
					_hoops_IIIIC += _hoops_SPHPR->_hoops_SPHA;
					_hoops_CIIIC += _hoops_SPHPR->face_count;
					_hoops_SIIIC += _hoops_SPHPR->face_list_length;
				} while ((_hoops_SPHPR = (Shell *)_hoops_SPHPR->next) != null);

				int				_hoops_ICIAR = _hoops_SHIIC->point_count;
				int				_hoops_GCIIC = _hoops_SHIIC->_hoops_SPHA;
				int				_hoops_GHHAR = _hoops_SHIIC->face_count;
				Point *			pt = null;
				int *			_hoops_PSRGA = null;

				/* _hoops_SRS, _hoops_ASGGR _hoops_RH _hoops_SRS _hoops_RRCPR _hoops_GAR _hoops_IRS _hoops_CCAH _hoops_RGGAR _hoops_IH _hoops_HCR _hoops_RH _hoops_PIH */
				Point *			_hoops_HRRGA = _hoops_SHIIC->points;
				int *			_hoops_RCIIC = _hoops_SHIIC->face_list;

				ALLOC_ARRAY_ALIGNED (_hoops_SHIIC->points, _hoops_SHIIC->point_count + _hoops_AAAHA, Point, 16);
				_hoops_AIGA (_hoops_HRRGA, _hoops_SHIIC->point_count, Point, _hoops_SHIIC->points);
				FREE_ARRAY_ALIGNED (_hoops_HRRGA, _hoops_SHIIC->point_count, Point, 16);
				pt = _hoops_SHIIC->points + _hoops_SHIIC->point_count;

				if (_hoops_RIIIC->normals != null && _hoops_RIIIC->explicit_normal_count == 0) {
					FREE_ARRAY (_hoops_RIIIC->normals, _hoops_SHIIC->point_count, Vector);
					_hoops_RIIIC->normals = null;
				}
				if (BIT(_hoops_SHIIC->polyhedron_flags, _hoops_CGRHR) ||
					ANYBIT (*_hoops_RIIIC->_hoops_CHHPR(), ~0))
					HI_Adjust_Vertex_Attributes (_hoops_SHIIC, _hoops_SHIIC->point_count, 0, _hoops_AAAHA);
				_hoops_SHIIC->polyhedron_flags &= ~PHF_VERTEX_NORMALS_VALID;

				if (_hoops_SHIIC->_hoops_HHHPR != null)
					HI_Adjust_Vertex_To_Edge (_hoops_SHIIC, _hoops_SHIIC->point_count, 0, _hoops_AAAHA);
				_hoops_SHIIC->point_count += _hoops_AAAHA;


				if (_hoops_PIIIC->normals != null &&
					_hoops_PIIIC->explicit_normal_count == 0) {
						FREE_ARRAY_ALIGNED (_hoops_PIIIC->normals, _hoops_SHIIC->face_count, _hoops_ARPA, 16);
						_hoops_PIIIC->normals = null;
				}
				if (BIT(_hoops_SHIIC->polyhedron_flags, _hoops_APRHR) ||
					ANYBIT (*_hoops_PIIIC->_hoops_CHHPR(), ~0))
					HI_Adjust_Face_Attributes (_hoops_SHIIC, _hoops_SHIIC->face_count, 0, _hoops_CIIIC);
				_hoops_SHIIC->polyhedron_flags &= ~PHF_FACE_NORMALS_VALID;

				_hoops_SHIIC->face_count += _hoops_CIIIC;


				if (_hoops_SHIIC->face_list_length + _hoops_SIIIC != 0) {
					ALLOC_ARRAY (_hoops_SHIIC->face_list, _hoops_SHIIC->face_list_length + _hoops_SIIIC, int);
					if (_hoops_SHIIC->face_list_length != 0) {
						_hoops_AIGA (_hoops_RCIIC, _hoops_SHIIC->face_list_length, int, _hoops_SHIIC->face_list);
						FREE_ARRAY (_hoops_RCIIC, _hoops_SHIIC->face_list_length, int);
					}
					_hoops_PSRGA = _hoops_SHIIC->face_list + _hoops_SHIIC->face_list_length;
					_hoops_SHIIC->face_list_length += _hoops_SIIIC;
				}


				if (_hoops_SHIIC->tristrips) {
					Tristrip *			ts;

					if ((ts = _hoops_SHIIC->tristrips) != null) do {
						_hoops_GACR *		dl;

						while ((dl = ts->_hoops_GAHA) != null) {
							ts->_hoops_GAHA = dl->next;
							_hoops_HPRH(dl);
						}
					} while ((ts = ts->next) != null);
					HI_Free_Tristrip_List (_hoops_SHIIC->tristrips);
				}
				_hoops_SHIIC->tristrips = null;
				_hoops_SHIIC->_hoops_ACRHR = 0;

				if (_hoops_SHIIC->_hoops_SHGPR) {
					Polyedge *			pe;

					if ((pe = _hoops_SHIIC->_hoops_SHGPR) != null) do {
						_hoops_GACR *		dl;

						while ((dl = pe->_hoops_GAHA) != null) {
							pe->_hoops_GAHA = dl->next;
							_hoops_HPRH(dl);
						}
					} while ((pe = pe->next) != null);
					HI_Free_Polyedge_List (_hoops_SHIIC->_hoops_SHGPR);
				}
				_hoops_SHIIC->_hoops_SHGPR = null;
				_hoops_SHIIC->_hoops_RSHPR = 0;

				if (_hoops_SHIIC->_hoops_GIGPR) {
					Polymarker *			pm;

					if ((pm = _hoops_SHIIC->_hoops_GIGPR) != null) do {
						_hoops_GACR *		dl;

						while ((dl = pm->_hoops_GAHA) != null) {
							pm->_hoops_GAHA = dl->next;
							_hoops_HPRH(dl);
						}
					} while ((pm = pm->next) != null);
					HI_Free_Polymarker_List (_hoops_SHIIC->_hoops_GIGPR);
				}
				_hoops_SHIIC->_hoops_GIGPR = null;
				_hoops_SHIIC->_hoops_AGRHR = 0;

				if (_hoops_SHIIC->_hoops_CHGPR) {
					Polyedge *			pe;

					if ((pe = _hoops_SHIIC->_hoops_CHGPR) != null) do {
						_hoops_GACR *		dl;

						while ((dl = pe->_hoops_GAHA) != null) {
							pe->_hoops_GAHA = dl->next;
							_hoops_HPRH(dl);
						}
					} while ((pe = pe->next) != null);
					HI_Free_Polyedge_List (_hoops_SHIIC->_hoops_SHGPR);
				}
				_hoops_SHIIC->_hoops_CHGPR = null;


				/* _hoops_SIGP: _hoops_GAAP _hoops_PAH _hoops_SHH _hoops_AHGSP _hoops_PPR _hoops_HASC _hoops_PRCCA _hoops_PIH */
				if (_hoops_SHIIC->_hoops_HGAIR != null) {
					HI_Au_Revoir ((_hoops_HPAH *)_hoops_SHIIC->_hoops_HGAIR);
					_hoops_SHIIC->_hoops_HGAIR = null;
				}


				// _hoops_SIA _hoops_PIH
				_hoops_AHCHC *	_hoops_ACIIC = null;

				if (BIT(_hoops_ARCAR->flags, _hoops_CSIHC)) {
					if (_hoops_SHIIC->_hoops_IPPGR != null &&
						_hoops_SHIIC->_hoops_IPPGR->type == _hoops_CPCHC)
						_hoops_ACIIC = (_hoops_AHCHC *)_hoops_SHIIC->_hoops_IPPGR;

					if (_hoops_ACIIC == null) {
						ALLOC (_hoops_ACIIC, _hoops_AHCHC);
						ZERO_STRUCT (_hoops_ACIIC, _hoops_AHCHC);
						_hoops_ACIIC->type = _hoops_CPCHC;
						_hoops_ACIIC->owner = (_hoops_CRCP *)_hoops_SHIIC;
						_hoops_ACIIC->_hoops_HIHI = 1;
						if ((_hoops_ACIIC->next = _hoops_SHIIC->_hoops_IPPGR) != null)
							_hoops_ACIIC->next->backlink = &_hoops_ACIIC->next;
						_hoops_SHIIC->_hoops_IPPGR = (Attribute *)_hoops_ACIIC;
						_hoops_ACIIC->backlink = &_hoops_SHIIC->_hoops_IPPGR;

						ALLOC_ARRAY (_hoops_ACIIC->_hoops_GPICA, _hoops_HIIIC, _hoops_SPCHC);
						_hoops_ACIIC->_hoops_PHCHC = 1;
						_hoops_ACIIC->_hoops_GPICA[0]._hoops_GHCHC = _hoops_SHIIC->owner->key;
						_hoops_ACIIC->_hoops_GPICA[0]._hoops_CISAP = _hoops_SHIIC->key;
						_hoops_ACIIC->_hoops_GPICA[0]._hoops_RHCHC = 0;
					}
					else {
						_hoops_SPCHC *		_hoops_PCIIC = _hoops_ACIIC->_hoops_GPICA;

						ALLOC_ARRAY (_hoops_ACIIC->_hoops_GPICA, _hoops_HIIIC, _hoops_SPCHC);
						_hoops_RSAI (_hoops_PCIIC, _hoops_SPCHC, _hoops_ACIIC->_hoops_GPICA);
						FREE_ARRAY (_hoops_PCIIC, 1, _hoops_SPCHC);
					}
				}

				// _hoops_HAIR _hoops_SIRGR _hoops_GHCA _hoops_SHH _hoops_GCSP; _hoops_IS _hoops_IISPR _hoops_RH _hoops_HGRH, _hoops_IHSA _hoops_GII _hoops_ACPAA _hoops_ARI, _hoops_ISPR _hoops_IH _hoops_HASC _hoops_SPHR
				if (ANYBIT(*_hoops_RIIIC->_hoops_CHHPR(0), _hoops_ARSII)) {
					if (_hoops_RIIIC->_hoops_PAHIR != null) {
						if (_hoops_RIIIC->_hoops_PAHIR == _hoops_RIIIC->ecolors)
							_hoops_APRGA (_hoops_RIIIC->ecolors, _hoops_SHIIC->point_count, RGB, _hoops_RIIIC->_hoops_PAHIR);
						else if (_hoops_RIIIC->_hoops_PAHIR == _hoops_RIIIC->fcolors)
							_hoops_APRGA (_hoops_RIIIC->fcolors, _hoops_SHIIC->point_count, RGB, _hoops_RIIIC->_hoops_PAHIR);
					}
					if (_hoops_RIIIC->ecolors != null && _hoops_RIIIC->ecolors == _hoops_RIIIC->fcolors)
						_hoops_APRGA (_hoops_RIIIC->fcolors, _hoops_SHIIC->point_count, RGB, _hoops_RIIIC->ecolors);
				}
				if (ANYBIT(*_hoops_RIIIC->_hoops_CHHPR(0), _hoops_GGSII)) {
					if (_hoops_RIIIC->_hoops_HAHIR != null) {
						if (_hoops_RIIIC->_hoops_HAHIR == _hoops_RIIIC->_hoops_HGHIR)
							_hoops_APRGA (_hoops_RIIIC->_hoops_HGHIR, _hoops_SHIIC->point_count, _hoops_ACGHR, _hoops_RIIIC->_hoops_HAHIR);
						else if (_hoops_RIIIC->_hoops_HAHIR == _hoops_RIIIC->_hoops_IGHIR)
							_hoops_APRGA (_hoops_RIIIC->_hoops_IGHIR, _hoops_SHIIC->point_count, _hoops_ACGHR, _hoops_RIIIC->_hoops_HAHIR);
					}
					if (_hoops_RIIIC->_hoops_HGHIR != null && _hoops_RIIIC->_hoops_HGHIR == _hoops_RIIIC->_hoops_IGHIR)
						_hoops_APRGA (_hoops_RIIIC->_hoops_IGHIR, _hoops_SHIIC->point_count, _hoops_ACGHR, _hoops_RIIIC->_hoops_HGHIR);
				}


				/* _hoops_HA _hoops_HASC _hoops_RH _hoops_HHRPA _hoops_SCHS _hoops_CRGR _hoops_RH _hoops_GC _hoops_HCIIC _hoops_GGR _hoops_RH _hoops_SRS _hoops_SPR */
				_hoops_HIIIC = 1;

				_hoops_SPHPR = (Shell *)remaining;
				do {
					_hoops_CCGPR = _hoops_SPHPR->next;

					unsigned char	_hoops_ICIIC[256];	// _hoops_IH _hoops_SIA _hoops_RPHGA _hoops_RRPR _hoops_PAR _hoops_HSGP _hoops_HSH
					int const *		_hoops_PCHI;

					/* _hoops_ACRAA _hoops_PIH, _hoops_APHR _hoops_CCA _hoops_RSSA & _hoops_SCAPA */
					_hoops_AIGA (_hoops_SPHPR->points, _hoops_SPHPR->point_count, Point, pt);
					pt += _hoops_SPHPR->point_count;

					if (_hoops_SPHPR->face_list_length != 0) {
						_hoops_AIGA (_hoops_SPHPR->face_list, _hoops_SPHPR->face_list_length, int, _hoops_PSRGA);
						_hoops_PCHI = _hoops_PSRGA + _hoops_SPHPR->face_list_length;
						while (_hoops_PSRGA != _hoops_PCHI) {
							int		count = *_hoops_PSRGA++;

							if (count < 0) count = -count;
							while (count-- > 0)
								*_hoops_PSRGA++ += _hoops_ICIAR;
						}
					}

					// _hoops_ARP _hoops_CCAH _hoops_ISPH
					if (_hoops_SPHPR->face_count > 0) {
						PUSHNAME(_hoops_ARCAR->_hoops_RIGC);
						HC_MSet_Region_Faces (key, _hoops_HIIIC, _hoops_GHHAR, _hoops_SPHPR->face_count);
						POPNAME(_hoops_ARCAR->_hoops_RIGC);
					}

					Local_Vertex_Attributes *	_hoops_CCIIC = &_hoops_SPHPR->local_vertex_attributes;
					_hoops_RPGHR *		_hoops_SCIIC = &_hoops_SPHPR->_hoops_IHHPR;
					Local_Face_Attributes *		_hoops_GSIIC = &_hoops_SPHPR->local_face_attributes;

					// _hoops_ASGA
					if (_hoops_CCIIC->explicit_normal_count > 0) {
						if (_hoops_RIIIC->normals == null)
							HI_Initialize_Vertex_Attributes (_hoops_SHIIC, LVA_EXPLICIT_NORMAL, 0);
						_hoops_AIGA (_hoops_CCIIC->normals, _hoops_SPHPR->point_count, Vector, &_hoops_RIIIC->normals[_hoops_ICIAR]);
						for (int i=0; i<_hoops_SPHPR->point_count; i++)
							*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= *_hoops_CCIIC->_hoops_CHHPR(i) & LVA_EXPLICIT_NORMAL;
						_hoops_RIIIC->explicit_normal_count += _hoops_CCIIC->explicit_normal_count;
					}
					if (_hoops_SCIIC->explicit_normal_count > 0) {
						if (_hoops_AIIIC->normals == null)
							HI_Initialize_Edge_Attributes (_hoops_SHIIC, _hoops_CRAHR);
						_hoops_AIGA (_hoops_SCIIC->normals, _hoops_SPHPR->_hoops_SPHA, Vector, &_hoops_AIIIC->normals[_hoops_GCIIC]);
						for (int i=0; i<_hoops_SPHPR->_hoops_SPHA; i++)
							*_hoops_AIIIC->_hoops_CHHPR(_hoops_GCIIC+i) |= *_hoops_SCIIC->_hoops_CHHPR(i) & LFA_EXPLICIT_NORMAL;
						_hoops_AIIIC->explicit_normal_count += _hoops_SCIIC->explicit_normal_count;
					}
					if (_hoops_GSIIC->explicit_normal_count > 0) {
						if (_hoops_PIIIC->normals == null)
							HI_Initialize_Face_Attributes (_hoops_SHIIC, LFA_EXPLICIT_NORMAL);
						_hoops_AIGA (_hoops_GSIIC->normals, _hoops_SPHPR->face_count, _hoops_ARPA, &_hoops_PIIIC->normals[_hoops_GHHAR]);
						for (int i=0; i<_hoops_SPHPR->face_count; i++)
							*_hoops_PIIIC->_hoops_CHHPR(_hoops_GHHAR+i) |= *_hoops_GSIIC->_hoops_CHHPR(i) & LFA_EXPLICIT_NORMAL;
						_hoops_PIIIC->explicit_normal_count += _hoops_GSIIC->explicit_normal_count;
					}

					// _hoops_PPR _hoops_RII _hoops_AIRC...
					// _hoops_GIHA
					if (_hoops_CCIIC->_hoops_CPIAA > 0 || _hoops_CCIIC->_hoops_SIIPR > 0) {
						for (int i=0; i<_hoops_SPHPR->point_count; i++)
							*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= *_hoops_CCIIC->_hoops_CHHPR(i) & _hoops_CIICA;

						_hoops_RIIIC->_hoops_CPIAA += _hoops_CCIIC->_hoops_CPIAA;
						_hoops_RIIIC->_hoops_SIIPR += _hoops_CCIIC->_hoops_SIIPR;
					}

					if (_hoops_CCIIC->_hoops_HIRRA > 0) {
						_hoops_AIGA (_hoops_CCIIC->_hoops_IAHIR, _hoops_SPHPR->point_count, RGBAS32, &_hoops_RIIIC->_hoops_IAHIR[_hoops_ICIAR]);
						for (int i=0; i<_hoops_SPHPR->point_count; i++)
							*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= *_hoops_CCIIC->_hoops_CHHPR(i) & _hoops_CCRRA;
						_hoops_RIIIC->_hoops_HIRRA += _hoops_CCIIC->_hoops_HIRRA;
					}

					if (_hoops_CCIIC->_hoops_ICRRA > 0) {
						_hoops_AIGA (_hoops_CCIIC->_hoops_PAHIR, _hoops_SPHPR->point_count, RGB, &_hoops_RIIIC->_hoops_PAHIR[_hoops_ICIAR]);
						for (int i=0; i<_hoops_SPHPR->point_count; i++)
							*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= *_hoops_CCIIC->_hoops_CHHPR(i) & _hoops_HCRRA;
						_hoops_RIIIC->_hoops_ICRRA += _hoops_CCIIC->_hoops_ICRRA;
					}
					if (_hoops_CCIIC->_hoops_SCHPR > 0) {
						_hoops_AIGA (_hoops_CCIIC->ecolors, _hoops_SPHPR->point_count, RGB, &_hoops_RIIIC->ecolors[_hoops_ICIAR]);
						for (int i=0; i<_hoops_SPHPR->point_count; i++)
							*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= *_hoops_CCIIC->_hoops_CHHPR(i) & _hoops_PPHPR;
						_hoops_RIIIC->_hoops_SCHPR += _hoops_CCIIC->_hoops_SCHPR;
					}
					if (_hoops_CCIIC->_hoops_RCRHR > 0) {
						_hoops_AIGA (_hoops_CCIIC->fcolors, _hoops_SPHPR->point_count, RGB, &_hoops_RIIIC->fcolors[_hoops_ICIAR]);
						for (int i=0; i<_hoops_SPHPR->point_count; i++)
							*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= *_hoops_CCIIC->_hoops_CHHPR(i) & _hoops_AARHR;
						_hoops_RIIIC->_hoops_RCRHR += _hoops_CCIIC->_hoops_RCRHR;
					}

					if (_hoops_CCIIC->_hoops_PCRRA > 0) {
						_hoops_AIGA (_hoops_CCIIC->_hoops_HAHIR, _hoops_SPHPR->point_count, _hoops_ACGHR, &_hoops_RIIIC->_hoops_HAHIR[_hoops_ICIAR]);
						for (int i=0; i<_hoops_SPHPR->point_count; i++)
							*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= *_hoops_CCIIC->_hoops_CHHPR(i) & _hoops_SIRRA;
						_hoops_RIIIC->_hoops_PCRRA += _hoops_CCIIC->_hoops_PCRRA;
					}
					if (_hoops_CCIIC->_hoops_CCHPR > 0) {
						_hoops_AIGA (_hoops_CCIIC->_hoops_HGHIR, _hoops_SPHPR->point_count, _hoops_ACGHR, &_hoops_RIIIC->_hoops_HGHIR[_hoops_ICIAR]);
						for (int i=0; i<_hoops_SPHPR->point_count; i++)
							*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= *_hoops_CCIIC->_hoops_CHHPR(i) & _hoops_RPHPR;
						_hoops_RIIIC->_hoops_CCHPR += _hoops_CCIIC->_hoops_CCHPR;
					}
					if (_hoops_CCIIC->_hoops_SIRHR > 0) {
						_hoops_AIGA (_hoops_CCIIC->_hoops_IGHIR, _hoops_SPHPR->point_count, _hoops_ACGHR, &_hoops_RIIIC->_hoops_IGHIR[_hoops_ICIAR]);
						for (int i=0; i<_hoops_SPHPR->point_count; i++)
							*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= *_hoops_CCIIC->_hoops_CHHPR(i) & _hoops_HARHR;
						_hoops_RIIIC->_hoops_SIRHR += _hoops_CCIIC->_hoops_SIRHR;
					}

					if (_hoops_CCIIC->_hoops_RSAPA > 0) {
						int							width = _hoops_RIIIC->param_width;

						_hoops_AIGA (_hoops_CCIIC->params, _hoops_SPHPR->point_count * width, float,
									&_hoops_RIIIC->params[_hoops_ICIAR * width]);
						for (int i=0; i<_hoops_SPHPR->point_count; i++)
							*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= *_hoops_CCIIC->_hoops_CHHPR(i) & _hoops_ASAPA;
						_hoops_RIIIC->_hoops_RSAPA += _hoops_CCIIC->_hoops_RSAPA;
					}

					if (_hoops_CCIIC->_hoops_SCHHC > 0) {
						_hoops_AIGA (_hoops_CCIIC->_hoops_CAHIR, _hoops_SPHPR->point_count, float, &_hoops_RIIIC->_hoops_CAHIR[_hoops_ICIAR]);
						for (int i=0; i<_hoops_SPHPR->point_count; i++)
							*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= *_hoops_CCIIC->_hoops_CHHPR(i) & _hoops_GCICA;
						_hoops_RIIIC->_hoops_SCHHC += _hoops_CCIIC->_hoops_SCHHC;
					}

					if (_hoops_CCIIC->_hoops_AHIIC > 0) {
						_hoops_RPHIR const *		sl = _hoops_CCIIC->_hoops_GPHIR;
						do {
							_hoops_RPHIR const *	_hoops_RSIIC = HI_LVA_Symbol_Init (_hoops_SHIIC, &sl->name);

							if (_hoops_RSIIC != null)
								_hoops_ICIIC[(int)sl->id] = _hoops_RSIIC->id;
							else
								_hoops_ICIIC[(int)sl->id] = 0;	// _hoops_PGSAH...
						} while ((sl = sl->next) != null);

						for (int i=0; i<_hoops_SPHPR->point_count; i++) {
							if (BIT(*_hoops_CCIIC->_hoops_CHHPR(i), _hoops_SIICA)) {
								_hoops_RIIIC->_hoops_SAHIR[_hoops_ICIAR+i] = _hoops_ICIIC[(int)_hoops_CCIIC->_hoops_SAHIR[i]];
								*_hoops_RIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= _hoops_SIICA;
							}
						}
						_hoops_RIIIC->_hoops_AHIIC += _hoops_CCIIC->_hoops_AHIIC;
					}

					// _hoops_SPPR
					if (_hoops_SCIIC->_hoops_CPIAA > 0 || _hoops_SCIIC->_hoops_SIIPR > 0) {
						for (int i=0; i<_hoops_SPHPR->_hoops_SPHA; i++)
							*_hoops_AIIIC->_hoops_CHHPR(_hoops_GCIIC+i) |= *_hoops_SCIIC->_hoops_CHHPR(i) & _hoops_ICICA;
						_hoops_AIIIC->_hoops_CPIAA += _hoops_SCIIC->_hoops_CPIAA;
						_hoops_AIIIC->_hoops_SIIPR += _hoops_SCIIC->_hoops_SIIPR;
					}

					if (_hoops_SCIIC->_hoops_HSRRA > 0) {
						_hoops_AIGA (_hoops_SCIIC->colors, _hoops_SPHPR->_hoops_SPHA, RGB, &_hoops_AIIIC->colors[_hoops_GCIIC]);
						for (int i=0; i<_hoops_SPHPR->_hoops_SPHA; i++)
							*_hoops_AIIIC->_hoops_CHHPR(_hoops_GCIIC+i) |= *_hoops_SCIIC->_hoops_CHHPR(i) & _hoops_SSRRA;
						_hoops_AIIIC->_hoops_HSRRA += _hoops_SCIIC->_hoops_HSRRA;
					}
					if (_hoops_SCIIC->_hoops_PSRRA > 0) {
						_hoops_AIGA (_hoops_SCIIC->findices, _hoops_SPHPR->_hoops_SPHA, _hoops_ACGHR, &_hoops_AIIIC->findices[_hoops_GCIIC]);
						for (int i=0; i<_hoops_SPHPR->_hoops_SPHA; i++)
							*_hoops_AIIIC->_hoops_CHHPR(_hoops_GCIIC+i) |= *_hoops_SCIIC->_hoops_CHHPR(i) & _hoops_RPGI;
						_hoops_AIIIC->_hoops_PSRRA += _hoops_SCIIC->_hoops_PSRRA;
					}

					if (_hoops_SCIIC->_hoops_CCHHC > 0) {
						_hoops_AIGA (_hoops_SCIIC->weights, _hoops_SPHPR->_hoops_SPHA, float, &_hoops_AIIIC->weights[_hoops_GCIIC]);
						for (int i=0; i<_hoops_SPHPR->_hoops_SPHA; i++)
							*_hoops_AIIIC->_hoops_CHHPR(_hoops_GCIIC+i) |= *_hoops_SCIIC->_hoops_CHHPR(i) & _hoops_SCICA;
						_hoops_AIIIC->_hoops_CCHHC += _hoops_SCIIC->_hoops_CCHHC;
					}

					if (_hoops_SCIIC->_hoops_SRAPA > 0) {
						_hoops_HHHIR const *		pl = _hoops_SCIIC->_hoops_PHHIR;
						do {
							_hoops_HHHIR const *	_hoops_CASCA = HI_LEA_Pattern_Init (_hoops_SHIIC, &pl->name);

							if (_hoops_CASCA != null)
								_hoops_ICIIC[(int)pl->id] = _hoops_CASCA->id;
							else
								_hoops_ICIIC[(int)pl->id] = 0;	// _hoops_PGSAH...
						} while ((pl = pl->next) != null);

						for (int i=0; i<_hoops_SPHPR->_hoops_SPHA; i++) {
							if (BIT(*_hoops_CCIIC->_hoops_CHHPR(i), _hoops_GPGI)) {
								_hoops_AIIIC->_hoops_AHHIR[_hoops_GCIIC+i] = _hoops_ICIIC[(int)_hoops_SCIIC->_hoops_AHHIR[i]];
								*_hoops_AIIIC->_hoops_CHHPR(_hoops_ICIAR+i) |= _hoops_GPGI;
							}
						}
					}

					// _hoops_RSSI
					if (_hoops_GSIIC->_hoops_CPIAA > 0 || _hoops_GSIIC->_hoops_SIIPR > 0) {
						for (int i=0; i<_hoops_SPHPR->face_count; i++)
							*_hoops_PIIIC->_hoops_CHHPR(_hoops_GHHAR+i) |= *_hoops_GSIIC->_hoops_CHHPR(i) & _hoops_HRAPA;
						_hoops_PIIIC->_hoops_CPIAA += _hoops_GSIIC->_hoops_CPIAA;
						_hoops_PIIIC->_hoops_SIIPR += _hoops_GSIIC->_hoops_SIIPR;
					}

					if (_hoops_GSIIC->_hoops_HSRRA > 0) {
						_hoops_AIGA (_hoops_GSIIC->colors, _hoops_SPHPR->face_count, RGB, &_hoops_PIIIC->colors[_hoops_GHHAR]);
						for (int i=0; i<_hoops_SPHPR->face_count; i++)
							*_hoops_PIIIC->_hoops_CHHPR(_hoops_GHHAR+i) |= *_hoops_GSIIC->_hoops_CHHPR(i) & LFA_EXPLICIT_COLOR_BY_VALUE;
						_hoops_PIIIC->_hoops_HSRRA += _hoops_GSIIC->_hoops_HSRRA;
					}
					if (_hoops_GSIIC->_hoops_PSRRA > 0) {
						_hoops_AIGA (_hoops_GSIIC->findices, _hoops_SPHPR->face_count, _hoops_ACGHR, &_hoops_PIIIC->findices[_hoops_GHHAR]);
						for (int i=0; i<_hoops_SPHPR->face_count; i++)
							*_hoops_PIIIC->_hoops_CHHPR(_hoops_GHHAR+i) |= *_hoops_GSIIC->_hoops_CHHPR(i) & LFA_EXPLICIT_COLOR_BY_FINDEX;
						_hoops_PIIIC->_hoops_PSRRA += _hoops_GSIIC->_hoops_PSRRA;
					}

					if (_hoops_GSIIC->_hoops_SRAPA > 0) {
						_hoops_AIGA (_hoops_GSIIC->_hoops_AHHIR, _hoops_SPHPR->face_count, unsigned char, &_hoops_PIIIC->_hoops_AHHIR[_hoops_GHHAR]);
						for (int i=0; i<_hoops_SPHPR->face_count; i++)
							*_hoops_PIIIC->_hoops_CHHPR(_hoops_GHHAR+i) |= *_hoops_GSIIC->_hoops_CHHPR(i) & _hoops_HAGI;
						_hoops_PIIIC->_hoops_SRAPA += _hoops_GSIIC->_hoops_SRAPA;
					}


					_hoops_ICIAR += _hoops_SPHPR->point_count;
					_hoops_GCIIC += _hoops_SPHPR->_hoops_SPHA;
					_hoops_GHHAR += _hoops_SPHPR->face_count;
					_hoops_HIIIC++;

					/* _hoops_PPR _hoops_SIA _hoops_RPP _hoops_PIASR */
					if (BIT(_hoops_ARCAR->flags, _hoops_CSIHC)) {
						_hoops_AHCHC *	id = null;

						if (_hoops_SPHPR->_hoops_IPPGR != null &&
							_hoops_SPHPR->_hoops_IPPGR->type == _hoops_CPCHC)
							id = (_hoops_AHCHC *)_hoops_SPHPR->_hoops_IPPGR;

						if (id == null) {
							_hoops_ACIIC->_hoops_GPICA[_hoops_ACIIC->_hoops_PHCHC]._hoops_GHCHC = _hoops_SPHPR->owner->key;
							_hoops_ACIIC->_hoops_GPICA[_hoops_ACIIC->_hoops_PHCHC]._hoops_CISAP = _hoops_SPHPR->key;
						}
						else {
							_hoops_ACIIC->_hoops_GPICA[_hoops_ACIIC->_hoops_PHCHC]._hoops_GHCHC = id->_hoops_GPICA[0]._hoops_GHCHC;
							_hoops_ACIIC->_hoops_GPICA[_hoops_ACIIC->_hoops_PHCHC]._hoops_CISAP = id->_hoops_GPICA[0]._hoops_CISAP;

							_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,id);
							FREE_ARRAY (id->_hoops_GPICA, id->_hoops_PHCHC, _hoops_SPCHC);
							FREE (id, _hoops_AHCHC);
						}
						_hoops_ACIIC->_hoops_GPICA[_hoops_ACIIC->_hoops_PHCHC]._hoops_RHCHC = _hoops_ACIIC->_hoops_PHCHC++;
					}

					/* _hoops_HCR _hoops_CPHR _hoops_CCA _hoops_RGR _hoops_RRCPR */
					HI_Delete_User_Key (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_SPHPR);
					_hoops_HPRH (_hoops_SPHPR);
				} while ((_hoops_SPHPR = (Shell *)_hoops_CCGPR) != null);

				// _hoops_HACH _hoops_RHCHH _hoops_IIGR _hoops_GHPP
				HI_Repair_Shell_Edges (_hoops_ARCAR->_hoops_RIGC, _hoops_SHIIC);

				_hoops_SHIIC->bounding = Bounding::Create(_hoops_SHIIC->point_count, _hoops_SHIIC->points);

				// _hoops_PPR _hoops_CACH _hoops_RPP _hoops_SR _hoops_PAH _hoops_HSSRR _hoops_HAIR _hoops_SIRGR _hoops_HA _hoops_GPIA _hoops_HCPC _hoops_ISHA
				if (_hoops_RIIIC->_hoops_PAHIR != null && _hoops_RIIIC->ecolors != null) {
					bool		_hoops_APACP = true;

					for (int i=0; _hoops_APACP && i<_hoops_SHIIC->point_count;  ++i) {
						Local_Vertex_Flags		flags = *_hoops_RIIIC->_hoops_CHHPR(i);

						if (ALLBITS (flags, _hoops_HCRRA | _hoops_PPHPR)) {
							if (_hoops_RIIIC->_hoops_PAHIR[i] != _hoops_RIIIC->ecolors[i])
								_hoops_APACP = false;
						}
						else if (ANYBIT (flags, _hoops_HCRRA | _hoops_PPHPR))
							_hoops_APACP = false;		// _hoops_HAR _hoops_GIPR (_hoops_PGHC _hoops_RPGP), _hoops_HIS _hoops_PAH'_hoops_RA _hoops_PSSP
					}

					if (_hoops_APACP) {
						FREE_ARRAY (_hoops_RIIIC->ecolors, _hoops_SHIIC->point_count, RGB);
						_hoops_RIIIC->ecolors = _hoops_RIIIC->_hoops_PAHIR;
					}
				}
				// _hoops_GPIA _hoops_HCPC _hoops_HSP
				if (_hoops_RIIIC->_hoops_PAHIR != null && _hoops_RIIIC->fcolors != null) {
					bool		_hoops_APACP = true;

					for (int i=0; _hoops_APACP && i<_hoops_SHIIC->point_count;  ++i) {
						Local_Vertex_Flags		flags = *_hoops_RIIIC->_hoops_CHHPR(i);

						if (ALLBITS (flags, _hoops_HCRRA | _hoops_AARHR)) {
							if (_hoops_RIIIC->_hoops_PAHIR[i] != _hoops_RIIIC->fcolors[i])
								_hoops_APACP = false;
						}
						else if (ANYBIT (flags, _hoops_HCRRA | _hoops_AARHR))
							_hoops_APACP = false;		// _hoops_HAR _hoops_GIPR (_hoops_PGHC _hoops_RPGP), _hoops_HIS _hoops_PAH'_hoops_RA _hoops_PSSP
					}

					if (_hoops_APACP) {
						FREE_ARRAY (_hoops_RIIIC->fcolors, _hoops_SHIIC->point_count, RGB);
						_hoops_RIIIC->fcolors = _hoops_RIIIC->_hoops_PAHIR;
					}
				}
				// _hoops_ISHA _hoops_HCPC _hoops_HSP (_hoops_RPP _hoops_HAR _hoops_AIAH _hoops_GIPR _hoops_RPHGA _hoops_IS _hoops_GPIA)
				if (_hoops_RIIIC->ecolors != null && _hoops_RIIIC->fcolors != null && _hoops_RIIIC->ecolors != _hoops_RIIIC->fcolors) {
					bool		_hoops_APACP = true;

					for (int i=0; _hoops_APACP && i<_hoops_SHIIC->point_count;  ++i) {
						Local_Vertex_Flags		flags = *_hoops_RIIIC->_hoops_CHHPR(i);

						if (ALLBITS (flags, _hoops_PPHPR | _hoops_AARHR)) {
							if (_hoops_RIIIC->ecolors[i] != _hoops_RIIIC->fcolors[i])
								_hoops_APACP = false;
						}
						else if (ANYBIT (flags, _hoops_PPHPR | _hoops_AARHR))
							_hoops_APACP = false;		// _hoops_HAR _hoops_GIPR (_hoops_PGHC _hoops_RPGP), _hoops_HIS _hoops_PAH'_hoops_RA _hoops_PSSP
					}

					if (_hoops_APACP) {
						FREE_ARRAY (_hoops_RIIIC->fcolors, _hoops_SHIIC->point_count, RGB);
						_hoops_RIIIC->fcolors = _hoops_RIIIC->ecolors;
					}
				}
				// _hoops_APHS _hoops_IH _hoops_CIHA _hoops_SIRGR
				// _hoops_GPIA _hoops_HCPC _hoops_ISHA
				if (_hoops_RIIIC->_hoops_HAHIR != null && _hoops_RIIIC->_hoops_HGHIR != null) {
					bool		_hoops_APACP = true;

					for (int i=0; _hoops_APACP && i<_hoops_SHIIC->point_count;  ++i) {
						Local_Vertex_Flags		flags = *_hoops_RIIIC->_hoops_CHHPR(i);

						if (ALLBITS (flags, _hoops_SIRRA | _hoops_RPHPR)) {
							if (_hoops_RIIIC->_hoops_HAHIR[i] != _hoops_RIIIC->_hoops_HGHIR[i])
								_hoops_APACP = false;
						}
						else if (ANYBIT (flags, _hoops_SIRRA | _hoops_RPHPR))
							_hoops_APACP = false;		// _hoops_HAR _hoops_GIPR (_hoops_PGHC _hoops_RPGP), _hoops_HIS _hoops_PAH'_hoops_RA _hoops_PSSP
					}

					if (_hoops_APACP) {
						FREE_ARRAY (_hoops_RIIIC->_hoops_HGHIR, _hoops_SHIIC->point_count, _hoops_ACGHR);
						_hoops_RIIIC->_hoops_HGHIR = _hoops_RIIIC->_hoops_HAHIR;
					}
				}
				// _hoops_GPIA _hoops_HCPC _hoops_HSP
				if (_hoops_RIIIC->_hoops_HAHIR != null && _hoops_RIIIC->_hoops_IGHIR != null) {
					bool		_hoops_APACP = true;

					for (int i=0; _hoops_APACP && i<_hoops_SHIIC->point_count;  ++i) {
						Local_Vertex_Flags		flags = *_hoops_RIIIC->_hoops_CHHPR(i);

						if (ALLBITS (flags, _hoops_SIRRA | _hoops_HARHR)) {
							if (_hoops_RIIIC->_hoops_HAHIR[i] != _hoops_RIIIC->_hoops_IGHIR[i])
								_hoops_APACP = false;
						}
						else if (ANYBIT (flags, _hoops_SIRRA | _hoops_HARHR))
							_hoops_APACP = false;		// _hoops_HAR _hoops_GIPR (_hoops_PGHC _hoops_RPGP), _hoops_HIS _hoops_PAH'_hoops_RA _hoops_PSSP
					}

					if (_hoops_APACP) {
						FREE_ARRAY (_hoops_RIIIC->_hoops_IGHIR, _hoops_SHIIC->point_count, _hoops_ACGHR);
						_hoops_RIIIC->_hoops_IGHIR = _hoops_RIIIC->_hoops_HAHIR;
					}
				}
				// _hoops_ISHA _hoops_HCPC _hoops_HSP (_hoops_RPP _hoops_HAR _hoops_AIAH _hoops_GIPR _hoops_RPHGA _hoops_IS _hoops_GPIA)
				if (_hoops_RIIIC->_hoops_HGHIR != null && _hoops_RIIIC->_hoops_IGHIR != null && _hoops_RIIIC->_hoops_HGHIR != _hoops_RIIIC->_hoops_IGHIR) {
					bool		_hoops_APACP = true;

					for (int i=0; _hoops_APACP && i<_hoops_SHIIC->point_count;  ++i) {
						Local_Vertex_Flags		flags = *_hoops_RIIIC->_hoops_CHHPR(i);

						if (ALLBITS (flags, _hoops_RPHPR | _hoops_HARHR)) {
							if (_hoops_RIIIC->_hoops_HGHIR[i] != _hoops_RIIIC->_hoops_IGHIR[i])
								_hoops_APACP = false;
						}
						else if (ANYBIT (flags, _hoops_RPHPR | _hoops_HARHR))
							_hoops_APACP = false;		// _hoops_HAR _hoops_GIPR (_hoops_PGHC _hoops_RPGP), _hoops_HIS _hoops_PAH'_hoops_RA _hoops_PSSP
					}

					if (_hoops_APACP) {
						FREE_ARRAY (_hoops_RIIIC->_hoops_IGHIR, _hoops_SHIIC->point_count, _hoops_ACGHR);
						_hoops_RIIIC->_hoops_IGHIR = _hoops_RIIIC->_hoops_HGHIR;
					}
				}
			}
		}

		delete pl;
		delete _hoops_IAPHA;
	}

	if (_hoops_SRCP->_hoops_RGRPR != null)  {
		Subsegment *		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;

		do if (_hoops_GIPIA->type == _hoops_IRCP)
			_hoops_HHIIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA);
		while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
	}
}

#define	_hoops_ASIIC(_hoops_PSIIC, _hoops_HSIIC) \
		(int)(((_hoops_PSIIC >> 24) ^ (_hoops_PSIIC >> 16) ^ (_hoops_PSIIC >> 8) ^ _hoops_PSIIC ^ (_hoops_HSIIC >> 8) ^ _hoops_HSIIC) & \
			  (_hoops_RAPGI-1))


local void _hoops_ISIIC (
	_hoops_ICCHC *			_hoops_ARCAR,
	_hoops_CRCP *					_hoops_SRCP,
	_hoops_IAPGI *	table) {
	Geometry *					geometry;
	Subsegment *				_hoops_GIPIA;

	if (_hoops_SRCP->_hoops_IPPGR != null && _hoops_SRCP->_hoops_IPPGR->type == _hoops_CPCHC) {
		_hoops_AHCHC *		id = (_hoops_AHCHC *)_hoops_SRCP->_hoops_IPPGR;

		for (int i=0; i<id->_hoops_PHCHC; i++) {
			_hoops_AAPGI *		_hoops_SPRAR;
			int						_hoops_GCAH;

			ALLOC (_hoops_SPRAR, _hoops_AAPGI);
			_hoops_SPRAR->original.owner = id->_hoops_GPICA[i]._hoops_GHCHC;
			_hoops_SPRAR->original.key = id->_hoops_GPICA[i]._hoops_CISAP;
			_hoops_SPRAR->original.region = 0;
			_hoops_SPRAR->_hoops_HAPGI.owner = -1;
			_hoops_SPRAR->_hoops_HAPGI.key = _hoops_SRCP->key;
			_hoops_SPRAR->_hoops_HAPGI.region = id->_hoops_GPICA[i]._hoops_RHCHC;

			_hoops_GCAH = _hoops_ASIIC (_hoops_SPRAR->original.key, _hoops_SPRAR->original.region);
			_hoops_SPRAR->forward = table->forward[_hoops_GCAH];
			table->forward[_hoops_GCAH] = _hoops_SPRAR;
			_hoops_GCAH = _hoops_ASIIC (_hoops_SPRAR->_hoops_HAPGI.key, _hoops_SPRAR->_hoops_HAPGI.region);
			_hoops_SPRAR->_hoops_PAPGI = table->_hoops_PAPGI[_hoops_GCAH];
			table->_hoops_PAPGI[_hoops_GCAH] = _hoops_SPRAR;
		}

		_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,id);
		FREE_ARRAY (id->_hoops_GPICA, id->_hoops_PHCHC, _hoops_SPCHC);
		FREE (id, _hoops_AHCHC);
	}

	if ((geometry = _hoops_SRCP->geometry) != null) do {
		if (geometry->_hoops_IPPGR != null && geometry->_hoops_IPPGR->type == _hoops_CPCHC) {
			_hoops_AHCHC *		id = (_hoops_AHCHC *)geometry->_hoops_IPPGR;

			for (int i=0; i<id->_hoops_PHCHC; i++) {
				_hoops_AAPGI *		_hoops_SPRAR;
				int						_hoops_GCAH;

				ALLOC (_hoops_SPRAR, _hoops_AAPGI);
				_hoops_SPRAR->original.owner = id->_hoops_GPICA[i]._hoops_GHCHC;
				_hoops_SPRAR->original.key = id->_hoops_GPICA[i]._hoops_CISAP;
				_hoops_SPRAR->original.region = 0;
				_hoops_SPRAR->_hoops_HAPGI.owner = _hoops_SRCP->key;
				_hoops_SPRAR->_hoops_HAPGI.key = geometry->key;
				_hoops_SPRAR->_hoops_HAPGI.region = id->_hoops_GPICA[i]._hoops_RHCHC;

				_hoops_GCAH = _hoops_ASIIC (_hoops_SPRAR->original.key, _hoops_SPRAR->original.region);
				_hoops_SPRAR->forward = table->forward[_hoops_GCAH];
				table->forward[_hoops_GCAH] = _hoops_SPRAR;
				_hoops_GCAH = _hoops_ASIIC (_hoops_SPRAR->_hoops_HAPGI.key, _hoops_SPRAR->_hoops_HAPGI.region);
				_hoops_SPRAR->_hoops_PAPGI = table->_hoops_PAPGI[_hoops_GCAH];
				table->_hoops_PAPGI[_hoops_GCAH] = _hoops_SPRAR;
			}

			_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,id);
			FREE_ARRAY (id->_hoops_GPICA, id->_hoops_PHCHC, _hoops_SPCHC);
			FREE (id, _hoops_AHCHC);
		}
	} while ((geometry = geometry->next) != null);

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP)
			_hoops_ISIIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA, table);
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}

local void _hoops_CSIIC (
	_hoops_ICCHC *			_hoops_ARCAR,
	_hoops_CRCP *					root) {
	_hoops_IAPGI *	table;

	UNREFERENCED(_hoops_ARCAR);

	if ((table = HOOPS_WORLD->_hoops_IIHGI) != null) do {
		if (table->segment == root) {
			/* _hoops_CASI _hoops_GGSR _hoops_RHGS _hoops_PIH _hoops_HII _hoops_RGR _hoops_CAGH'_hoops_GRI _hoops_GASR */
			for (int i=0; i<_hoops_RAPGI; i++) {
				while (table->forward[i] != null) {
					_hoops_AAPGI *		_hoops_SPRAR = table->forward[i];

					table->forward[i] = _hoops_SPRAR->forward;
					FREE (_hoops_SPRAR, _hoops_AAPGI);
				}
			}
			ZERO_ARRAY (table->forward, _hoops_RAPGI, _hoops_AAPGI *);
			ZERO_ARRAY (table->_hoops_PAPGI, _hoops_RAPGI, _hoops_AAPGI *);
		}
	} while ((table = table->next) != null);

	if (table == null) {
		/* _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_GASR */
		ALLOC (table, _hoops_IAPGI);
		ZERO_STRUCT (table, _hoops_IAPGI);
		table->next = HOOPS_WORLD->_hoops_IIHGI;
		table->segment = root;
		HOOPS_WORLD->_hoops_IIHGI = table;
	}

	_hoops_ISIIC (_hoops_ARCAR, root, table);
}

local bool _hoops_SSIIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP,
	bool					_hoops_HCGIC) {
	bool					_hoops_GGCIC = false;
	Subsegment *			_hoops_GIPIA;
	Subsegment *			_hoops_HARIC;

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_HARIC = _hoops_GIPIA->next;

		if (_hoops_GIPIA->type == _hoops_IRCP &&
			(_hoops_HCGIC || !ANYBIT(_hoops_GIPIA->_hoops_RRHH, _hoops_PACHC|_hoops_CACHC))) {
			if (_hoops_SSIIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA, _hoops_HCGIC))
				_hoops_GGCIC = true;
		}
	} while ((_hoops_GIPIA = _hoops_HARIC) != null);

	if (!BIT(_hoops_SRCP->_hoops_RRHH, _hoops_CACHC) &&
		_hoops_SRCP->geometry == null &&
		_hoops_SRCP->_hoops_RGRPR == null &&
		(!ANYBIT(_hoops_SRCP->_hoops_RRHH, _hoops_PACHC|_hoops_HACHC) ||
		 (ANYBIT(_hoops_SRCP->_hoops_RRHH, _hoops_PACHC|_hoops_HACHC) && _hoops_HCGIC &&
		  !ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR|_hoops_GIPSA))) &&
		_hoops_PPGIC (_hoops_ARCAR, _hoops_SRCP) != _hoops_CAGIC) {
		int						_hoops_RHICA = 0;
		Xref *					_hoops_AHICA;

		if ((_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR()) != null) do {
			if (_hoops_AHICA->type == HK_STYLE)
				++_hoops_RHICA;
		} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

		if (_hoops_SRCP->_hoops_IPPGR == null || _hoops_RHICA == 0) {
			_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_SRCP);
			HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP);
			_hoops_HPRH (_hoops_SRCP);
			_hoops_GGCIC = true;
		}
	}
	return _hoops_GGCIC;
}

struct _hoops_RGCIC {
	_hoops_RGCIC *		next;
	Vector							_hoops_ICIIC;
	float *							_hoops_CGRRC;
};

struct _hoops_AGCIC {
    _hoops_AGCIC *		next;

    Key						key;
    int                 	_hoops_PGCIC;
    int                 	values[3];

    float               	_hoops_HGCIC[16];      /* _hoops_RSGA _hoops_HII _hoops_ISCP _hoops_HARGR _hoops_IS _hoops_SRGH */
    int                 	_hoops_IGCIC[4];
    Point               	_hoops_CGCIC;
    int                 	_hoops_SGCIC;
    bool	            	_hoops_SCCSA;
	bool					_hoops_GRCIC;
	bool					_hoops_RRCIC;
	bool					_hoops_ARCIC;

	Shell *					_hoops_SPHPR;

	float					matrix[16];
	float					_hoops_PRCIC[16];

	_hoops_ISGI *		_hoops_HRCIC;
	_hoops_RGCIC *	_hoops_IRCIC;


   /* _hoops_CICC _hoops_CRCIC (_hoops_SRPC) _hoops_RCIC { _hoops_ASRC _hoops_CRCIC; }
    _hoops_CICC _hoops_SRCIC (_hoops_SCSH _hoops_RPR, _hoops_AIIC _hoops_RCIC * _hoops_RSSA) _hoops_RAPC;*/
};

local int _hoops_GACIC (int _hoops_RSS, int _hoops_ASS, int _hoops_IPCCP) {
    int     tmp;

    tmp = _hoops_RSS ^ _hoops_ASS ^ _hoops_IPCCP;
    return tmp & 0x000000FF;
}

local float _hoops_RPSSR (Point const * points, int const * indices) {
    Point const &   _hoops_GGIAR = points[indices[0]];
    Point const &   p1 = points[indices[1]];
    Point const &   p2 = points[indices[2]];
    Point const &   _hoops_IAPH = points[indices[3]];
    Vector			_hoops_HSPI = p1 - _hoops_GGIAR, _hoops_ISPI = p2 - _hoops_GGIAR, _hoops_CSPI = _hoops_IAPH - _hoops_GGIAR;

    return _hoops_HSPI.x * (_hoops_ISPI.y*_hoops_CSPI.z - _hoops_ISPI.z*_hoops_CSPI.y) -
           _hoops_HSPI.y * (_hoops_ISPI.x*_hoops_CSPI.z - _hoops_ISPI.z*_hoops_CSPI.x) +
           _hoops_HSPI.z * (_hoops_ISPI.x*_hoops_CSPI.y - _hoops_ISPI.y*_hoops_CSPI.x);
}

local float _hoops_RACIC (int count, Point const * points, int * _hoops_CSPIR) {
    int         limit, save, i;
    int         _hoops_HGGHA = 0, _hoops_RCRGI = 53 % count;
    float       _hoops_ACCAA, _hoops_APPPC = 0;

    if (count < 4)
		return 0;

    for (i = 0; i < 4; i++)
        _hoops_CSPIR[i] = i * count / 4;

    if (count > 8)
        limit = 8;
    else
        limit = count;

    /* _hoops_GAAP _hoops_GGCR _hoops_RRGR _hoops_IS _hoops_SRPA _hoops_HARGR _hoops_GGR _hoops_AGIR _hoops_RSSA _hoops_IHPS _hoops_IS _hoops_SHH _hoops_IRPAA */
    _hoops_ACCAA = (float)fabs (_hoops_RPSSR (points, _hoops_CSPIR));

    for (i = 0; i < limit; i++) {
        save = _hoops_CSPIR[_hoops_HGGHA];
        _hoops_CSPIR[_hoops_HGGHA] = _hoops_RCRGI;
        _hoops_APPPC = (float)fabs (_hoops_RPSSR (points, _hoops_CSPIR));
        if (_hoops_APPPC < _hoops_ACCAA)
            _hoops_CSPIR[_hoops_HGGHA] = save;  /* _hoops_HSHPC _hoops_ISSC _hoops_IS _hoops_PCPA _hoops_SR _hoops_RIAGR */
        else
            _hoops_ACCAA = _hoops_APPPC;
        _hoops_HGGHA = (_hoops_HGGHA+1) % 4;
        _hoops_RCRGI = (_hoops_RCRGI * 13 + 1023) % count;
    }

    return _hoops_ACCAA;
}

local bool _hoops_AACIC (
    float const             *a,
    float alter             *_hoops_CRPA) {
    float                   tmp[16];
	float					_hoops_HHIPA, _hoops_IHIPA;

    float       _hoops_AAIPA = a[ 4]*a[ 9] - a[ 5]*a[ 8],
                _hoops_PAIPA = a[ 4]*a[10] - a[ 6]*a[ 8],
                _hoops_HAIPA = a[ 4]*a[11] - a[ 7]*a[ 8],
                _hoops_IAIPA = a[ 4]*a[13] - a[ 5]*a[12],
                _hoops_CAIPA = a[ 4]*a[14] - a[ 6]*a[12],
                _hoops_SAIPA = a[ 4]*a[15] - a[ 7]*a[12],
                _hoops_GPIPA = a[ 5]*a[10] - a[ 6]*a[ 9],
                _hoops_RPIPA = a[ 5]*a[11] - a[ 7]*a[ 9],
                _hoops_APIPA = a[ 5]*a[14] - a[ 6]*a[13],
                _hoops_PPIPA = a[ 5]*a[15] - a[ 7]*a[13],
                _hoops_HPIPA = a[ 6]*a[11] - a[ 7]*a[10],
                _hoops_IPIPA = a[ 6]*a[15] - a[ 7]*a[14],
                _hoops_CPIPA = a[ 8]*a[13] - a[ 9]*a[12],
                _hoops_SPIPA = a[ 8]*a[14] - a[10]*a[12],
                _hoops_GHIPA = a[ 8]*a[15] - a[11]*a[12],
                _hoops_RHIPA = a[ 9]*a[14] - a[10]*a[13],
                _hoops_AHIPA = a[ 9]*a[15] - a[11]*a[13],
                _hoops_PHIPA = a[10]*a[15] - a[11]*a[14];
    float       _hoops_GGIAR, p1, p2, _hoops_IAPH;

    tmp[ 0] = a[5]*_hoops_PHIPA - a[6]*_hoops_AHIPA + a[7]*_hoops_RHIPA;
    tmp[ 1] = a[2]*_hoops_AHIPA - a[3]*_hoops_RHIPA - a[1]*_hoops_PHIPA;
    tmp[ 2] = a[1]*_hoops_IPIPA - a[2]*_hoops_PPIPA + a[3]*_hoops_APIPA;
    tmp[ 3] = a[2]*_hoops_RPIPA - a[3]*_hoops_GPIPA - a[1]*_hoops_HPIPA;
    tmp[ 4] = a[6]*_hoops_GHIPA - a[7]*_hoops_SPIPA - a[4]*_hoops_PHIPA;
    tmp[ 5] = a[0]*_hoops_PHIPA - a[2]*_hoops_GHIPA + a[3]*_hoops_SPIPA;
    tmp[ 6] = a[2]*_hoops_SAIPA - a[3]*_hoops_CAIPA - a[0]*_hoops_IPIPA;
    tmp[ 7] = a[0]*_hoops_HPIPA - a[2]*_hoops_HAIPA + a[3]*_hoops_PAIPA;
    tmp[ 8] = a[4]*_hoops_AHIPA - a[5]*_hoops_GHIPA + a[7]*_hoops_CPIPA;
    tmp[ 9] = a[1]*_hoops_GHIPA - a[3]*_hoops_CPIPA - a[0]*_hoops_AHIPA;
    tmp[10] = a[0]*_hoops_PPIPA - a[1]*_hoops_SAIPA + a[3]*_hoops_IAIPA;
    tmp[11] = a[1]*_hoops_HAIPA - a[3]*_hoops_AAIPA - a[0]*_hoops_RPIPA;
    tmp[12] = a[5]*_hoops_SPIPA - a[6]*_hoops_CPIPA - a[4]*_hoops_RHIPA;
    tmp[13] = a[0]*_hoops_RHIPA - a[1]*_hoops_SPIPA + a[2]*_hoops_CPIPA;
    tmp[14] = a[1]*_hoops_CAIPA - a[2]*_hoops_IAIPA - a[0]*_hoops_APIPA;
    tmp[15] = a[0]*_hoops_GPIPA - a[1]*_hoops_PAIPA + a[2]*_hoops_AAIPA;

    _hoops_GGIAR =  tmp[ 0];
    p1 = -tmp[ 4];
    p2 =  tmp[ 8];
    _hoops_IAPH = -tmp[12];

    _hoops_HHIPA = a[0]*_hoops_GGIAR - a[1]*p1 + a[2]*p2 - a[3]*_hoops_IAPH;

    if (_hoops_HHIPA == 0.0f)
        return false;

    _hoops_IHIPA = 1.0f / _hoops_HHIPA;

    _hoops_CRPA[ 0] = tmp[ 0] * _hoops_IHIPA;
    _hoops_CRPA[ 1] = tmp[ 1] * _hoops_IHIPA;
    _hoops_CRPA[ 2] = tmp[ 2] * _hoops_IHIPA;
    _hoops_CRPA[ 3] = tmp[ 3] * _hoops_IHIPA;
    _hoops_CRPA[ 4] = tmp[ 4] * _hoops_IHIPA;
    _hoops_CRPA[ 5] = tmp[ 5] * _hoops_IHIPA;
    _hoops_CRPA[ 6] = tmp[ 6] * _hoops_IHIPA;
    _hoops_CRPA[ 7] = tmp[ 7] * _hoops_IHIPA;
    _hoops_CRPA[ 8] = tmp[ 8] * _hoops_IHIPA;
    _hoops_CRPA[ 9] = tmp[ 9] * _hoops_IHIPA;
    _hoops_CRPA[10] = tmp[10] * _hoops_IHIPA;
    _hoops_CRPA[11] = tmp[11] * _hoops_IHIPA;
    _hoops_CRPA[12] = tmp[12] * _hoops_IHIPA;
    _hoops_CRPA[13] = tmp[13] * _hoops_IHIPA;
    _hoops_CRPA[14] = tmp[14] * _hoops_IHIPA;
    _hoops_CRPA[15] = tmp[15] * _hoops_IHIPA;

    return  true;
}

bool _hoops_PACIC (_hoops_AGCIC* instance, int count, Point const * points) {
    if (instance->_hoops_SCCSA)
        return true;

    if (count > 0) {
        Point           min, max;
		float			_hoops_GSAHR;
        int             i;

        /* _hoops_HGCR _hoops_CCIR _hoops_IIGR _hoops_HSH _hoops_IS _hoops_CGIC _hoops_GHAR _hoops_CGHCP */
        min = max = points[0];
        for (i=1; i<count; i++) {
			if (points[i].x < min.x)
				min.x = points[i].x;
			else if (points[i].x > max.x)
				max.x = points[i].x;

			if (points[i].y < min.y)
				min.y = points[i].y;
			else if (points[i].y > max.y)
				max.y = points[i].y;

			if (points[i].z < min.z)
				min.z = points[i].z;
			else if (points[i].z > max.z)
				max.z = points[i].z;
        }
        /* _hoops_HACIC _hoops_CGHCP _hoops_IH _hoops_HARGR _hoops_AHCHI */
		_hoops_GSAHR = max.x - min.x;
		if (_hoops_GSAHR < max.y - min.y)
			_hoops_GSAHR = max.y - min.y;
		if (_hoops_GSAHR < max.z - min.z)
			_hoops_GSAHR = max.z - min.z;
		_hoops_GSAHR *= 1.0e-4f;
        _hoops_GSAHR *= _hoops_GSAHR * _hoops_GSAHR;   /* _hoops_AHCHI _hoops_SHRRR _hoops_AISRA _hoops_IACIC _hoops_RH _hoops_CACIC */

        /* _hoops_PAH _hoops_SR _hoops_SSS _hoops_IRS _hoops_HARGR _hoops_PARGI _hoops_RH _hoops_RSSA
        // _hoops_GIGHR: _hoops_RGR _hoops_GCA "_hoops_CISAR" -- _hoops_GRS _hoops_RRP _hoops_IS _hoops_SRPA _hoops_IS _hoops_HIISR _hoops_CCA _hoops_GPIC _hoops_CGSI _hoops_PII _hoops_AAPI */
        if (_hoops_RACIC (count, points, instance->_hoops_IGCIC) >= _hoops_GSAHR) {
            int             _hoops_SACIC = instance->_hoops_IGCIC[0];
            int             _hoops_IHHI = instance->_hoops_IGCIC[1];
            int             _hoops_CHHI = instance->_hoops_IGCIC[2];
            int             _hoops_GPCIC = instance->_hoops_IGCIC[3];

            /* _hoops_GHPHR _hoops_RH _hoops_RSGA _hoops_PGAP _hoops_HRGR _hoops_RH _hoops_HIHP _hoops_HII _hoops_RH _hoops_HARGR _hoops_IS _hoops_SRGH
            // _hoops_HIS _hoops_SRS _hoops_RH _hoops_IHGP _hoops_RSGA _hoops_PGAP _hoops_AHGGR _hoops_RH _hoops_SRGH _hoops_IS _hoops_RH _hoops_HARGR... */
            instance->matrix[ 0] = points[_hoops_IHHI].x - points[_hoops_SACIC].x;
            instance->matrix[ 1] = points[_hoops_IHHI].y - points[_hoops_SACIC].y;
            instance->matrix[ 2] = points[_hoops_IHHI].z - points[_hoops_SACIC].z;
            instance->matrix[ 3] = 0.0f;
            instance->matrix[ 4] = points[_hoops_CHHI].x - points[_hoops_SACIC].x;
            instance->matrix[ 5] = points[_hoops_CHHI].y - points[_hoops_SACIC].y;
            instance->matrix[ 6] = points[_hoops_CHHI].z - points[_hoops_SACIC].z;
            instance->matrix[ 7] = 0.0f;
            instance->matrix[ 8] = points[_hoops_GPCIC].x - points[_hoops_SACIC].x;
            instance->matrix[ 9] = points[_hoops_GPCIC].y - points[_hoops_SACIC].y;
            instance->matrix[10] = points[_hoops_GPCIC].z - points[_hoops_SACIC].z;
            instance->matrix[11] = 0.0f;
            instance->matrix[12] = points[_hoops_SACIC].x;
            instance->matrix[13] = points[_hoops_SACIC].y;
            instance->matrix[14] = points[_hoops_SACIC].z;
            instance->matrix[15] = 1.0f;

            /* _hoops_SR _hoops_CGH _hoops_SHR _hoops_SHH _hoops_SHSS _hoops_IS _hoops_ISSP _hoops_CR _hoops_SR _hoops_AISP _hoops_IRS _hoops_HPHR _hoops_HARGR _hoops_ARP, _hoops_HIH _hoops_ISPR _hoops_APIC */
            if (_hoops_AACIC (instance->matrix, instance->_hoops_HGCIC)) {
                /* _hoops_GRHP _hoops_SPR _hoops_IHH _hoops_PPSR _hoops_AARI _hoops_IH _hoops_IRS _hoops_HHCI _hoops_HIHP & _hoops_RPGP _hoops_ARPP _hoops_SR _hoops_AA _hoops_HCR _hoops_RSSA */
                i = count - 1;
                do if (i != instance->_hoops_IGCIC[0] &&
                       i != instance->_hoops_IGCIC[1] &&
                       i != instance->_hoops_IGCIC[2] &&
                       i != instance->_hoops_IGCIC[3])
                     break;
                while (--i > 0);

                instance->_hoops_CGCIC = points[i];
                instance->_hoops_SGCIC = i;

                instance->_hoops_SCCSA = true;
            }
        }
    }

    return instance->_hoops_SCCSA;
}

bool _hoops_RPCIC (
	_hoops_AGCIC alter *	_hoops_APCIC,
	_hoops_AGCIC alter *	_hoops_PPCIC,
	Point const *				_hoops_HPCIC,
	bool						_hoops_IPCIC) {
	float alter *				matrix = _hoops_APCIC->matrix;
	Point const *				points = _hoops_APCIC->_hoops_SPHPR->points;
	int							_hoops_CPCIC = _hoops_APCIC->_hoops_SPHPR->point_count;
    Point           			min, max;
	float						_hoops_GSAHR;
    int             			i;
	int             			_hoops_SACIC, _hoops_IHHI, _hoops_CHHI, _hoops_GPCIC;
	Point           			single;

    /* _hoops_HGCR _hoops_CCIR _hoops_IIGR _hoops_HSH _hoops_IS _hoops_CGIC _hoops_GHAR _hoops_CGHCP */
    min = max = points[0];
    for (i=1; i<_hoops_CPCIC; i++) {
        if (points[i].x < min.x)
            min.x = points[i].x;
        else if (points[i].x > max.x)
            max.x = points[i].x;

        if (points[i].y < min.y)
            min.y = points[i].y;
        else if (points[i].y > max.y)
            max.y = points[i].y;

        if (points[i].z < min.z)
            min.z = points[i].z;
        else if (points[i].z > max.z)
            max.z = points[i].z;
    }

    /* _hoops_HASGA _hoops_CGHCP _hoops_IH _hoops_PPSR _hoops_PPS */
    _hoops_GSAHR = max.x - min.x;
    if (_hoops_GSAHR < max.y - min.y)
		_hoops_GSAHR = max.y - min.y;
    if (_hoops_GSAHR < max.z - min.z)
		_hoops_GSAHR = max.z - min.z;
    _hoops_GSAHR *= 1.0e-3f;

    /* _hoops_SGH _hoops_RH _hoops_RSSA _hoops_PIS _hoops_RH _hoops_HAGAR'_hoops_GRI _hoops_HARGR _hoops_IS [_hoops_ASAR]_hoops_GHPHR _hoops_IRS _hoops_RSHCR _hoops_HARGR */
	_hoops_SACIC = _hoops_PPCIC->_hoops_IGCIC[0];
	_hoops_IHHI = _hoops_PPCIC->_hoops_IGCIC[1];
	_hoops_CHHI = _hoops_PPCIC->_hoops_IGCIC[2];
	_hoops_GPCIC = _hoops_PPCIC->_hoops_IGCIC[3];


    /* _hoops_RH _hoops_IHGP _hoops_RSGA _hoops_PGAP _hoops_AHGGR _hoops_RH _hoops_SRGH _hoops_IS _hoops_RH _hoops_HARGR... */
    matrix[0]  = points[_hoops_IHHI].x - points[_hoops_SACIC].x;
    matrix[1]  = points[_hoops_IHHI].y - points[_hoops_SACIC].y;
    matrix[2]  = points[_hoops_IHHI].z - points[_hoops_SACIC].z;
    matrix[3]  = 0.0f;
    matrix[4]  = points[_hoops_CHHI].x - points[_hoops_SACIC].x;
    matrix[5]  = points[_hoops_CHHI].y - points[_hoops_SACIC].y;
    matrix[6]  = points[_hoops_CHHI].z - points[_hoops_SACIC].z;
    matrix[7]  = 0.0f;
    matrix[8]  = points[_hoops_GPCIC].x - points[_hoops_SACIC].x;
    matrix[9]  = points[_hoops_GPCIC].y - points[_hoops_SACIC].y;
    matrix[10] = points[_hoops_GPCIC].z - points[_hoops_SACIC].z;
    matrix[11] = 0.0f;
    matrix[12] = points[_hoops_SACIC].x;
    matrix[13] = points[_hoops_SACIC].y;
    matrix[14] = points[_hoops_SACIC].z;
    matrix[15] = 1.0f;

	/*_hoops_SPCIC(_hoops_GHCIC->_hoops_RHCIC, _hoops_GHCIC->_hoops_AHCIC);*/

    /* _hoops_HA _hoops_HASC _hoops_GGR _hoops_RH _hoops_GGICR _hoops_HARGR _hoops_AIAH _hoops_GCSS _hoops_GPP _hoops_RH _hoops_HAGAR */
    HI_Compute_Matrix_Product (_hoops_PPCIC->_hoops_HGCIC, matrix, matrix);

    /* _hoops_SRS, _hoops_IRS _hoops_HHCI _hoops_ISPR _hoops_GPP _hoops_IRS _hoops_RSRA "_hoops_SCSAA" _hoops_PPSR */
    HI_Compute_Transformed_Points (1, &_hoops_PPCIC->_hoops_CGCIC, matrix, &single);
    if (fabs (points[_hoops_PPCIC->_hoops_SGCIC].x - single.x) > _hoops_GSAHR ||
        fabs (points[_hoops_PPCIC->_hoops_SGCIC].y - single.y) > _hoops_GSAHR ||
        fabs (points[_hoops_PPCIC->_hoops_SGCIC].z - single.z) > _hoops_GSAHR)
        return false;

    for (i=0; i<_hoops_CPCIC; i++) {
        HI_Compute_Transformed_Points (1, &_hoops_HPCIC[i], matrix, &single);
        if (fabs (points[i].x - single.x) > _hoops_GSAHR ||
            fabs (points[i].y - single.y) > _hoops_GSAHR ||
            fabs (points[i].z - single.z) > _hoops_GSAHR)
            break;
    }

    if (i < _hoops_CPCIC)  /* _hoops_PRRHA _hoops_RSIH? */
        return false;

	if (_hoops_IPCIC) {
		_hoops_RGCIC *		_hoops_PHCIC = _hoops_PPCIC->_hoops_IRCIC;
		while (_hoops_PHCIC != null) {
			if (Abs(matrix[0] - _hoops_PHCIC->_hoops_CGRRC[0]) <= _hoops_GSAHR &&
				Abs(matrix[1] - _hoops_PHCIC->_hoops_CGRRC[1]) <= _hoops_GSAHR &&
				Abs(matrix[2] - _hoops_PHCIC->_hoops_CGRRC[2]) <= _hoops_GSAHR &&
				Abs(matrix[3] - _hoops_PHCIC->_hoops_CGRRC[3]) <= _hoops_GSAHR &&
				Abs(matrix[4] - _hoops_PHCIC->_hoops_CGRRC[4]) <= _hoops_GSAHR &&
				Abs(matrix[5] - _hoops_PHCIC->_hoops_CGRRC[5]) <= _hoops_GSAHR &&
				Abs(matrix[6] - _hoops_PHCIC->_hoops_CGRRC[6]) <= _hoops_GSAHR &&
				Abs(matrix[7] - _hoops_PHCIC->_hoops_CGRRC[7]) <= _hoops_GSAHR &&
				Abs(matrix[8] - _hoops_PHCIC->_hoops_CGRRC[8]) <= _hoops_GSAHR &&
				Abs(matrix[9] - _hoops_PHCIC->_hoops_CGRRC[9]) <= _hoops_GSAHR &&
				Abs(matrix[10] - _hoops_PHCIC->_hoops_CGRRC[10]) <= _hoops_GSAHR &&
				Abs(matrix[11] - _hoops_PHCIC->_hoops_CGRRC[11]) <= _hoops_GSAHR &&
				Abs(matrix[12] - _hoops_PHCIC->_hoops_CGRRC[12]) <= _hoops_GSAHR &&
				Abs(matrix[13] - _hoops_PHCIC->_hoops_CGRRC[13]) <= _hoops_GSAHR &&
				Abs(matrix[14] - _hoops_PHCIC->_hoops_CGRRC[14]) <= _hoops_GSAHR &&
				Abs(matrix[15] - _hoops_PHCIC->_hoops_CGRRC[15]) <= _hoops_GSAHR) {
				_hoops_APCIC->_hoops_GRCIC = true;
				return true;
			}
			_hoops_PHCIC = _hoops_PHCIC->next;
		}
	}

	/*	_hoops_HPGHR _hoops_RGR _hoops_PPSR, _hoops_SR'_hoops_ASAR _hoops_RRRIR _hoops_RCRR _hoops_SGS _hoops_RGR _hoops_AHCAH _hoops_AHAP _hoops_HHCIC _hoops_IS _hoops_HS
		_hoops_IRS _hoops_CGRPR _hoops_IIAC.  _hoops_PHGP _hoops_SR _hoops_RRP _hoops_IS _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_RH _hoops_HCHIA _hoops_SR'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_PPSI
		_hoops_GPP _hoops_RGR _hoops_CGRPR */
	_hoops_RGCIC *		_hoops_IHCIC;

	ZALLOC(_hoops_IHCIC, _hoops_RGCIC);
	ALLOC_ARRAY(_hoops_IHCIC->_hoops_CGRRC, 16, float);
	_hoops_AIGA(matrix, 16, float, _hoops_IHCIC->_hoops_CGRRC);

	_hoops_IHCIC->next = _hoops_PPCIC->_hoops_IRCIC;
	_hoops_PPCIC->_hoops_IRCIC = _hoops_IHCIC;

    return true;
}

/* _hoops_CACH _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_IRS _hoops_HCHIA (_hoops_GRAPR _hoops_ICSA/_hoops_SAAA) _hoops_GAPA
   _hoops_RH _hoops_PGCR _hoops_SPGIA */
bool _hoops_CHCIC (
	_hoops_AGCIC alter *	_hoops_APCIC,
	_hoops_AGCIC alter *	_hoops_PPCIC,
	bool						_hoops_IPCIC) {
	float alter *				matrix = _hoops_APCIC->matrix;
	Point const *				_hoops_SHCIC = _hoops_APCIC->_hoops_SPHPR->points;
	Point const *				_hoops_GICIC = _hoops_PPCIC->_hoops_SPHPR->points;
	int							_hoops_CPCIC = _hoops_APCIC->_hoops_SPHPR->point_count;
	Vector						vector, _hoops_RICIC;
	int							i;
	Point *						_hoops_AICIC, *_hoops_PICIC;
	Point						_hoops_GSAHR, min, max;
	float						_hoops_HICIC[16];
	bool _hoops_IICIC = false;
	bool _hoops_CICIC = false;

	_hoops_HICIC[0]  = 1.0f;
    _hoops_HICIC[1]  = 0.0f;
    _hoops_HICIC[2]  = 0.0f;
    _hoops_HICIC[3]  = 0.0f;

    _hoops_HICIC[4]  = 0.0f;
    _hoops_HICIC[5]  = 1.0f;
    _hoops_HICIC[6]  = 0.0f;
    _hoops_HICIC[7]  = 0.0f;

    _hoops_HICIC[8]  = 0.0f;
    _hoops_HICIC[9]  = 0.0f;
    _hoops_HICIC[10] = 1.0f;
    _hoops_HICIC[11] = 0.0f;

    _hoops_HICIC[12] = 0.0f;
    _hoops_HICIC[13] = 0.0f;
    _hoops_HICIC[14] = 0.0f;
    _hoops_HICIC[15] = 1.0f;

	if (_hoops_APCIC->_hoops_HRCIC != null &&
		BIT(_hoops_APCIC->_hoops_HRCIC->matrix._hoops_RAGR , _hoops_GRICR))
		return false;

	if (_hoops_APCIC->_hoops_HRCIC != null &&
		BIT(_hoops_APCIC->_hoops_HRCIC->matrix._hoops_RAGR, _hoops_PRICR)) {
		ALLOC_ARRAY(_hoops_AICIC, _hoops_APCIC->_hoops_SPHPR->point_count, Point);
		_hoops_IICIC = true;
		_hoops_HICIC[12] = _hoops_APCIC->_hoops_HRCIC->matrix.elements[3][0];
		_hoops_HICIC[13] = _hoops_APCIC->_hoops_HRCIC->matrix.elements[3][1];
		_hoops_HICIC[14] = _hoops_APCIC->_hoops_HRCIC->matrix.elements[3][2];
		HI_Compute_Transformed_Points(_hoops_APCIC->_hoops_SPHPR->point_count, _hoops_SHCIC, _hoops_HICIC, _hoops_AICIC);
	}
	else {
		/* _hoops_SAHR _hoops_PPSR _hoops_IS _hoops_RH _hoops_GIGR _hoops_RSSA _hoops_RIIA _hoops_IIGR _hoops_SICIC _hoops_HPP _hoops_SRGH _hoops_RSGA */
		_hoops_AICIC = (Point *)_hoops_SHCIC;
	}

	if (_hoops_PPCIC->_hoops_HRCIC != null &&
		BIT(_hoops_PPCIC->_hoops_HRCIC->matrix._hoops_RAGR , _hoops_PRICR)) {
		ALLOC_ARRAY(_hoops_PICIC, _hoops_PPCIC->_hoops_SPHPR->point_count, Point);
		_hoops_CICIC = true;
		_hoops_HICIC[12] = _hoops_PPCIC->_hoops_HRCIC->matrix.elements[3][0];
		_hoops_HICIC[13] = _hoops_PPCIC->_hoops_HRCIC->matrix.elements[3][1];
		_hoops_HICIC[14] = _hoops_PPCIC->_hoops_HRCIC->matrix.elements[3][2];
		HI_Compute_Transformed_Points(_hoops_PPCIC->_hoops_SPHPR->point_count, _hoops_GICIC, _hoops_HICIC, _hoops_PICIC);
	}
	else {
		_hoops_PICIC = (Point *)_hoops_GICIC;
	}

	vector.x = _hoops_SHCIC[0].x - _hoops_GICIC[0].x;
	vector.y = _hoops_SHCIC[0].y - _hoops_GICIC[0].y;
	vector.z = _hoops_SHCIC[0].z - _hoops_GICIC[0].z;

	_hoops_RICIC.x = _hoops_AICIC[0].x - _hoops_PICIC[0].x;
	_hoops_RICIC.y = _hoops_AICIC[0].y - _hoops_PICIC[0].y;
	_hoops_RICIC.z = _hoops_AICIC[0].z - _hoops_PICIC[0].z;

	max.x = min.x = _hoops_AICIC[0].x;
	max.y = min.y = _hoops_AICIC[0].y;
	max.z = min.z = _hoops_AICIC[0].z;
	_hoops_GSAHR.x = 0; _hoops_GSAHR.y = 0; _hoops_GSAHR.z = 0;

	for (i=1; i<_hoops_CPCIC; ++i) {
		if (_hoops_AICIC[i].x < min.x)
			min.x = _hoops_AICIC[i].x;
		else if (_hoops_AICIC[i].x > max.x)
			max.x = _hoops_AICIC[i].x;
		if (_hoops_AICIC[i].y < min.y)
			min.y = _hoops_AICIC[i].y;
		else if (_hoops_AICIC[i].y > max.y)
			max.y = _hoops_AICIC[i].y;
		if (_hoops_AICIC[i].z < min.z)
			min.z = _hoops_AICIC[i].z;
		else if (_hoops_AICIC[i].z > max.z)
			max.z = _hoops_AICIC[i].z;
	}

    /* _hoops_HASGA _hoops_CGHCP _hoops_IH _hoops_PPSR _hoops_PPS */
    _hoops_GSAHR.x = 1.0e-2f * (max.x - min.x);
    _hoops_GSAHR.y = 1.0e-2f * (max.y - min.y);
    _hoops_GSAHR.z = 1.0e-2f * (max.z - min.z);


	/*	_hoops_SRS _hoops_ISPR _hoops_SGS _hoops_IIH _hoops_HRGR _hoops_IRS _hoops_HCHIA _hoops_GAPA _hoops_RH _hoops_PGCR _hoops_SCHS.
		_hoops_SR _hoops_GRS _hoops_ISPR _hoops_SPHR _hoops_IS _hoops_CACH _hoops_RPP _hoops_RH _hoops_GCCIC _hoops_IHIS _hoops_CAPR _hoops_IS _hoops_RH
		_hoops_PSHR _hoops_GISR (_hoops_GGR _hoops_PGAP _hoops_AGIR _hoops_SR _hoops_GHCA _hoops_HHGC _hoops_IS _hoops_HSCI _hoops_ASPSR _hoops_SCHS/_hoops_CRPGI. */
	for (i=1; i<_hoops_CPCIC; ++i) {
		if (Abs((_hoops_SHCIC[i].x - _hoops_GICIC[i].x) - vector.x) > _hoops_GSAHR.x ||
			Abs((_hoops_SHCIC[i].y - _hoops_GICIC[i].y) - vector.y) > _hoops_GSAHR.y ||
			Abs((_hoops_SHCIC[i].z - _hoops_GICIC[i].z) - vector.z) > _hoops_GSAHR.z) {
			if (_hoops_IICIC)
				FREE_ARRAY(_hoops_AICIC, _hoops_APCIC->_hoops_SPHPR->point_count, Point);
			if (_hoops_CICIC)
				FREE_ARRAY(_hoops_PICIC, _hoops_PPCIC->_hoops_SPHPR->point_count, Point);
			return false;
		}
	}

	/*	_hoops_HA _hoops_IHSH _hoops_HPGR _hoops_RH _hoops_CHIAR _hoops_RSSA, _hoops_PPR _hoops_CACH _hoops_RPP _hoops_CGSI _hoops_CHR _hoops_GHHS _hoops_CHIAR
		_hoops_CRGR _hoops_RH _hoops_PSHR _hoops_AHC. */
	for (i=1; i<_hoops_CPCIC; ++i) {
		if (Abs((_hoops_AICIC[i].x - _hoops_PICIC[i].x)) > _hoops_GSAHR.x ||
			Abs((_hoops_AICIC[i].y - _hoops_PICIC[i].y)) > _hoops_GSAHR.y ||
			Abs((_hoops_AICIC[i].z - _hoops_PICIC[i].z)) > _hoops_GSAHR.z) {
			_hoops_APCIC->_hoops_GRCIC = false;
			if (_hoops_IPCIC) {
				if (_hoops_IICIC) {
					FREE_ARRAY(_hoops_AICIC, _hoops_APCIC->_hoops_SPHPR->point_count, Point);
				}
				if (_hoops_CICIC) {
					FREE_ARRAY(_hoops_PICIC, _hoops_PPCIC->_hoops_SPHPR->point_count, Point);
				}
				return false;
			}
			break;
		}
	}

	if (i < _hoops_CPCIC) {
		/* _hoops_SR _hoops_SCHGA _hoops_GGSR _hoops_IIGR _hoops_SGS _hoops_HAPR _hoops_RSIH, _hoops_CAGAR _hoops_SGS _hoops_AGCR _hoops_PGCR _hoops_CGSI _hoops_CHR _hoops_HAR
			_hoops_GISI _hoops_SHH _hoops_RCCIC _hoops_CRGR _hoops_RH _hoops_PSHR _hoops_GISR, _hoops_PHGP _hoops_SR _hoops_CGH _hoops_PHHR _hoops_IAISR _hoops_PPR _hoops_CGRPR
			_hoops_CAPR _hoops_PII _hoops_GSSR */
	}
	else if (_hoops_IPCIC && i == _hoops_CPCIC) {
		/* _hoops_SR _hoops_IIAC _hoops_SCH _hoops_RHIR _hoops_SGS _hoops_SHSC _hoops_HAPR, _hoops_CAGAR _hoops_SGS _hoops_AGCR _hoops_PGCR _hoops_CGSI _hoops_CHR
			_hoops_CPIC _hoops_IS _hoops_RSGR _hoops_GH _hoops_GGR _hoops_RH _hoops_PSHR _hoops_GISR.  _hoops_PHGP _hoops_IIS'_hoops_GRI _hoops_HPGGR _hoops_RGR _hoops_AHCAH, _hoops_ACCIC
			_hoops_SGS _hoops_SCH _hoops_SPASR _hoops_HPIH _hoops_APRS _hoops_HAGAR.  _hoops_HGI _hoops_PPRRR _hoops_SR _hoops_PAH _hoops_HSCI _hoops_RH _hoops_RRCPR,
			_hoops_PPR _hoops_HAR _hoops_GGCR _hoops_IRS _hoops_CGRPR */
		/*	_hoops_SR _hoops_PAH _hoops_ASRC _hoops_IHPR _hoops_ARI, _hoops_PSCR _hoops_GGR _hoops_RH _hoops_AGIR _hoops_CAS _hoops_SR _hoops_RGHH _hoops_IRS _hoops_PSSP, _hoops_SR _hoops_GRS _hoops_ISPR
			_hoops_IH _hoops_RH _hoops_GRH _hoops_AGIR _hoops_SGS _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_PSSP _hoops_IIGR _hoops_IRS _hoops_RRHSA _hoops_HPSPR _hoops_CPAP, _hoops_PPR _hoops_RIIA
			_hoops_IIGR _hoops_CPRAA _hoops_IRS _hoops_CGRPR, _hoops_SR _hoops_GRS _hoops_HSCI _hoops_RH _hoops_AHCAH _hoops_RRCPR */
		_hoops_APCIC->_hoops_GRCIC = true;
		if (_hoops_IICIC)
			FREE_ARRAY(_hoops_AICIC, _hoops_APCIC->_hoops_SPHPR->point_count, Point);
		if (_hoops_CICIC)
			FREE_ARRAY(_hoops_PICIC, _hoops_PPCIC->_hoops_SPHPR->point_count, Point);
		return true;
	}

	/*	_hoops_AGGA _hoops_SR _hoops_RRP _hoops_IS _hoops_ISPR _hoops_HCR _hoops_IIGR _hoops_RH _hoops_PRCHR _hoops_SR'_hoops_RISP _hoops_IIAC _hoops_IIGR _hoops_RH _hoops_APRS _hoops_HAGAR.
		_hoops_PS _hoops_GHCA _hoops_RHCA _hoops_SR _hoops_HHGC _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CGRPR _hoops_IIGR _hoops_SCH _hoops_GRP _hoops_ISCP _hoops_AAGA, _hoops_HIH _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_AIAH
		_hoops_RPII _hoops_PSHS _hoops_PPR _hoops_RCCIC _hoops_CRGR _hoops_RH _hoops_PSHR _hoops_GISR, _hoops_SR _hoops_RRP _hoops_IS _hoops_ISPR _hoops_AGAP _hoops_PRCHR _hoops_HAH. */
	if (_hoops_IPCIC) {
		_hoops_RGCIC *		_hoops_PCCIC = _hoops_PPCIC->_hoops_IRCIC;
		while (_hoops_PCCIC != null) {
			if (Abs(vector.x - _hoops_PCCIC->_hoops_ICIIC.x) <= _hoops_GSAHR.x &&
				Abs(vector.y - _hoops_PCCIC->_hoops_ICIIC.y) <= _hoops_GSAHR.y &&
				Abs(vector.z - _hoops_PCCIC->_hoops_ICIIC.z) <= _hoops_GSAHR.z) {
				_hoops_APCIC->_hoops_GRCIC = true;
				if (_hoops_IICIC)
					FREE_ARRAY(_hoops_AICIC, _hoops_APCIC->_hoops_SPHPR->point_count, Point);
				if (_hoops_CICIC)
					FREE_ARRAY(_hoops_PICIC, _hoops_PPCIC->_hoops_SPHPR->point_count, Point);
				return true;
			}
			_hoops_PCCIC = _hoops_PCCIC->next;
		}
	}


	/*	_hoops_HPGHR _hoops_RGR _hoops_PPSR, _hoops_SR'_hoops_ASAR _hoops_RRRIR _hoops_RCRR _hoops_SGS _hoops_RGR _hoops_AHCAH _hoops_AHAP _hoops_HHCIC _hoops_IS _hoops_HS
		_hoops_IRS _hoops_CGRPR _hoops_IIAC.  _hoops_PHGP _hoops_SR _hoops_RRP _hoops_IS _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_RH _hoops_HCHIA _hoops_SR'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_PPSI
		_hoops_GPP _hoops_RGR _hoops_CGRPR */
	/* _hoops_PS _hoops_RGAR _hoops_HHGC _hoops_IS _hoops_PRIA _hoops_RGR _hoops_HCHIA _hoops_GGR _hoops_ISCP _hoops_HIGR _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_HCCIC _hoops_HGIPR _hoops_CPHP */
	if (Abs(vector.x) > _hoops_GSAHR.x || Abs(vector.y) > _hoops_GSAHR.y || Abs(vector.z) > _hoops_GSAHR.z) {
		_hoops_RGCIC *		_hoops_IHCIC;

		ZALLOC(_hoops_IHCIC, _hoops_RGCIC);
		_hoops_IHCIC->_hoops_ICIIC = vector;

		_hoops_IHCIC->next = _hoops_PPCIC->_hoops_IRCIC;
		_hoops_PPCIC->_hoops_IRCIC = _hoops_IHCIC;
	}

	matrix[0]  = 1.0f;
    matrix[1]  = 0.0f;
    matrix[2]  = 0.0f;
    matrix[3]  = 0.0f;

    matrix[4]  = 0.0f;
    matrix[5]  = 1.0f;
    matrix[6]  = 0.0f;
    matrix[7]  = 0.0f;

    matrix[8]  = 0.0f;
    matrix[9]  = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;

    matrix[12] = vector.x;
    matrix[13] = vector.y;
    matrix[14] = vector.z;
    matrix[15] = 1.0f;

	if (_hoops_IICIC)
		FREE_ARRAY(_hoops_AICIC, _hoops_APCIC->_hoops_SPHPR->point_count, Point);
	if (_hoops_CICIC)
		FREE_ARRAY(_hoops_PICIC, _hoops_PPCIC->_hoops_SPHPR->point_count, Point);

	return true;
}


bool _hoops_ICCIC (
	_hoops_AGCIC alter *	_hoops_APCIC,
	_hoops_AGCIC const *	_hoops_PPCIC,
	bool						_hoops_IPCIC) {
    /* _hoops_CAHP _hoops_HARGR (_hoops_RPP _hoops_SIGR) _hoops_PPR _hoops_PSCR _hoops_AA _hoops_CCCIC _hoops_HCGC */
    int             i;

	if (_hoops_IPCIC) {
	    if (_hoops_APCIC->_hoops_SPHPR->point_count == 0)
			return false;

	    if (_hoops_APCIC->_hoops_SPHPR->point_count != _hoops_PPCIC->_hoops_SPHPR->point_count ||
			_hoops_APCIC->_hoops_SPHPR->face_list_length != _hoops_PPCIC->_hoops_SPHPR->face_list_length)
			return false;

	    for (i=0; i<_hoops_APCIC->_hoops_SPHPR->face_list_length; i++)
	        if (_hoops_APCIC->_hoops_SPHPR->face_list[i] != _hoops_PPCIC->_hoops_SPHPR->face_list[i])
	            return false;

		return _hoops_CHCIC (_hoops_APCIC, (_hoops_AGCIC *)_hoops_PPCIC, _hoops_IPCIC);
	}
	else {
	    for (i=0; i<_hoops_APCIC->_hoops_SPHPR->face_list_length; i++)
	        if (_hoops_APCIC->_hoops_SPHPR->face_list[i] != _hoops_PPCIC->_hoops_SPHPR->face_list[i])
	            return false;

		if (!_hoops_APCIC->_hoops_RRCIC) {
	        if (!_hoops_PACIC (_hoops_APCIC, _hoops_APCIC->_hoops_SPHPR->point_count, _hoops_APCIC->_hoops_SPHPR->points)) {
	            return false;
	        }
	    }
		/* _hoops_IRHH _hoops_RCRR _hoops_RH _hoops_APRS _hoops_HAGAR _hoops_SSCP _hoops_IRS _hoops_HARGR _hoops_HAH! */
		if (!_hoops_PPCIC->_hoops_RRCIC) {
	        if (!_hoops_PACIC ((_hoops_AGCIC *)_hoops_PPCIC, _hoops_PPCIC->_hoops_SPHPR->point_count, _hoops_PPCIC->_hoops_SPHPR->points)) {
	            return false;
	        }
	    }

	    /* _hoops_PPR _hoops_HA _hoops_RH _hoops_RRI _hoops_SIRAR _hoops_CHIAR _hoops_PPSR _hoops_PPS */
	    if (!_hoops_RPCIC (_hoops_APCIC, (_hoops_AGCIC *)_hoops_PPCIC, _hoops_PPCIC->_hoops_SPHPR->points, _hoops_IPCIC)) {
	        return false;
	    }

	    return true;
	}
}

local int _hoops_SCCIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_AGCIC **	_hoops_GSCIC,
	_hoops_ISGI*		_hoops_RSCIC,
	bool					_hoops_IPCIC) {
	int						shell_count = 0, _hoops_ASCIC = 0;
	Attribute*				_hoops_ASGPR = 0;
	_hoops_ISGI*		_hoops_IHPIA = _hoops_RSCIC;

	/* _hoops_ISPR _hoops_IH _hoops_HCIA */
	if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) do {
		if (_hoops_ASGPR->type == HK_MODELLING_MATRIX) {
			if (_hoops_RSCIC == null) {
				_hoops_IHPIA = (_hoops_ISGI *)_hoops_ASGPR;
				_hoops_PRRH (_hoops_IHPIA);
			}
			else {
				ZALLOC (_hoops_IHPIA, _hoops_ISGI);
				_hoops_IHPIA->type = HK_MODELLING_MATRIX;
				_hoops_IHPIA->_hoops_HIHI = 1;
				HI_Multiply_Matrices (&((_hoops_ISGI *)_hoops_ASGPR)->matrix,
									  &_hoops_RSCIC->matrix,
									  &_hoops_IHPIA->matrix);
			}
			break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	if (_hoops_SRCP->geometry != null)  {
		Geometry *		geometry = _hoops_SRCP->geometry;
		int				_hoops_HIIIC = 0;
		Geometry *		_hoops_CCGPR = null;

		/* _hoops_CGIC _hoops_RSH _hoops_GSGS _hoops_SR _hoops_GRS _hoops_GGCR _hoops_CRGR _hoops_SRS _hoops_RRCPR, _hoops_RPP _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_IHGP _hoops_RRCPR */
		do {
			_hoops_CCGPR = geometry->next;

			if (geometry->type == _hoops_SCIP) {
				Shell *					_hoops_SPHPR = (Shell *)geometry;
				_hoops_AGCIC *		instance;
				_hoops_AGCIC *		_hoops_PPCIC;
				int						index = 0;

				/*	_hoops_PGIPR _hoops_RH _hoops_RRCPR _hoops_SSCP _hoops_PSP _hoops_HSP _hoops_HIGR.  _hoops_RGR _hoops_AGIR _hoops_IRHS _hoops_IS _hoops_SHH _hoops_GIR _hoops_RRAR
					_hoops_HIH _hoops_IH _hoops_HA _hoops_SAHR _hoops_HSGR _hoops_AGAP _hoops_SCHS */
				if (_hoops_SPHPR->face_list_length == 0)
					continue;

				/*	_hoops_IH _hoops_RISA _hoops_SCHS _hoops_SR _hoops_GA'_hoops_RA _hoops_PHGC _hoops_HII _hoops_PSSC _hoops_PGGA _hoops_IIGR _hoops_RH _hoops_ACCGI
					_hoops_HII _hoops_RH _hoops_CPAP _hoops_CGRPR _hoops_PPR _hoops_RSGA.  _hoops_HSHCR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_IRCC _hoops_IS _hoops_HGCR _hoops_IASH
					_hoops_IIGR _hoops_SSRS _hoops_SCHS, _hoops_PSCR _hoops_PHHR _hoops_IAISR _hoops_PPR _hoops_HSCI!*/
				if (_hoops_SPHPR->point_count <= 32 && !_hoops_IPCIC)
					continue;

				index = _hoops_GACIC (_hoops_SPHPR->point_count, _hoops_SPHPR->face_list_length, _hoops_SPHPR->face_list[_hoops_SPHPR->face_list_length-1]);


				_hoops_HIIIC++;

				if ((_hoops_PPCIC = _hoops_GSCIC[index]) != null) do {
					if (_hoops_SPHPR == _hoops_PPCIC->_hoops_SPHPR)
						break;
				} while ((_hoops_PPCIC = _hoops_PPCIC->next) != null);
				if (_hoops_PPCIC != null)
					continue;


				ZALLOC (instance, _hoops_AGCIC);
				instance->values[0] = _hoops_SPHPR->point_count;
				instance->values[1] = _hoops_SPHPR->face_list_length;
				instance->key = _hoops_AIRIR (_hoops_SPHPR);
				instance->_hoops_SPHPR = _hoops_SPHPR;
				instance->_hoops_HRCIC = _hoops_IHPIA;
				instance->_hoops_ARCIC = false;


				if ((_hoops_PPCIC = _hoops_GSCIC[index]) != null) {
					do {
						if (instance->values[0] == _hoops_PPCIC->_hoops_SPHPR->point_count &&
							instance->values[1] == _hoops_PPCIC->_hoops_SPHPR->face_list_length) {
							if (_hoops_ICCIC(instance, _hoops_PPCIC, _hoops_IPCIC)) {
								/* _hoops_IRHH _hoops_IRS _hoops_CPAP _hoops_CGRPR _hoops_PPR _hoops_HSCI _hoops_RH _hoops_RRCPR */
								if (_hoops_IPCIC && instance->_hoops_GRCIC) {
									HI_Generic_Delete (_hoops_ARCAR->_hoops_RIGC,(_hoops_HPAH *)_hoops_SPHPR);
								}
								else {
									_hoops_ASCIC++;

									_hoops_PHIP * _hoops_RRA = HI_Create_Reference (_hoops_ARCAR->_hoops_RIGC, (_hoops_CRCP *)_hoops_PPCIC->_hoops_SPHPR, _hoops_SRCP, null);

									_hoops_ISGI *	modelling_matrix;
									ZALLOC (modelling_matrix, _hoops_ISGI);

									HI_Figure_General_Modelling_Mtx (instance->matrix, &modelling_matrix->matrix);

									if (!HI_Set_Modelling_Matrix (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_RRA, modelling_matrix))
										FREE (modelling_matrix, _hoops_ISGI);

									HI_Generic_Delete (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_SPHPR);
								}

                                while (instance->_hoops_IRCIC != null) {
									_hoops_RGCIC *		victim = instance->_hoops_IRCIC;

									instance->_hoops_IRCIC = victim->next;

                                    if (victim->_hoops_CGRRC)
                                        FREE_ARRAY (victim->_hoops_CGRRC, 16, float);
                                    FREE (victim, _hoops_RGCIC);
                                }
								FREE (instance, _hoops_AGCIC);
								instance = null;
								break;
							}
						}
					} while ((_hoops_PPCIC = _hoops_PPCIC->next) != null);
				}
				if (_hoops_PPCIC == null) {
					instance->next = _hoops_GSCIC[index];
					_hoops_GSCIC[index] = instance;
				}
			}
		} while ((geometry = _hoops_CCGPR) != null);

		shell_count += _hoops_HIIIC;
	}

	if (_hoops_SRCP->_hoops_RGRPR != null)  {
		Subsegment *		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;

		do {
			if (_hoops_GIPIA->type == _hoops_IRCP)
				shell_count += _hoops_SCCIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA, _hoops_GSCIC,
												_hoops_IHPIA, _hoops_IPCIC);
			else if (_hoops_GIPIA->type == _hoops_AGRPR) {
				_hoops_PGRPR *	include = (_hoops_PGRPR *)_hoops_GIPIA;

				if (include->_hoops_IGRPR->type == _hoops_IRCP)
					shell_count += _hoops_SCCIC (_hoops_ARCAR, (_hoops_CRCP *)include->_hoops_IGRPR, _hoops_GSCIC,
													_hoops_IHPIA, _hoops_IPCIC);
			}
		} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
	}

	if (_hoops_IHPIA != _hoops_RSCIC)
		_hoops_HPRH (_hoops_IHPIA);

	return shell_count;
}


local void _hoops_GARIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP,
	bool					_hoops_RARIC) {
	int						_hoops_PSCIC[64];
	int *					_hoops_GSCHC = _hoops_PSCIC;
	int						_hoops_RSCHC = 0;

	if (_hoops_RARIC) {
		/* (_hoops_IRHH _hoops_SPR "_hoops_SIHGA" _hoops_IIAAR _hoops_HCR _hoops_IGGA _hoops_SGHC) */
		_hoops_AARIC (_hoops_ARCAR, _hoops_SRCP, null, _hoops_SRCP);

		if (BIT (_hoops_ARCAR->flags, _hoops_ASIHC))
			_hoops_SISHC (_hoops_ARCAR, _hoops_SRCP, null, 0, true);
	}

	if (_hoops_ARCAR->_hoops_RSCHC != 0) {
		_hoops_GSCHC = _hoops_ARCAR->_hoops_GSCHC;
		_hoops_RSCHC = _hoops_ARCAR->_hoops_RSCHC;
	}
	else {
		_hoops_SCAIC (_hoops_ARCAR, _hoops_SRCP, _hoops_GSCHC, &_hoops_RSCHC);

		_hoops_GSCHC[_hoops_RSCHC++] = _hoops_AACHC;

		if (BIT(_hoops_ARCAR->flags, _hoops_SGCHC))
			_hoops_GSCHC[_hoops_RSCHC++] = _hoops_RACHC;
	}

	HOOPS_WORLD->_hoops_AGHGI = 1;//_hoops_IHPR;

	_hoops_HPRIC (_hoops_SRCP);

	/* _hoops_SPS, _hoops_GACHC _hoops_GII _hoops_SPSHI, _hoops_HAGC _hoops_CCAH _hoops_SPSHI _hoops_GAR _hoops_SIGR _hoops_HPGR _hoops_GRR _hoops_HHSPR */
	for (int _hoops_HSCIC=0; _hoops_HSCIC<_hoops_RSCHC; _hoops_HSCIC++) {
		ASSERT(_hoops_ARCAR->_hoops_GGRHH->Count() == 0);

		switch (_hoops_GSCHC[_hoops_HSCIC]) {
			case _hoops_RACHC:
				if (_hoops_RARIC) {
					_hoops_CHHIC (_hoops_ARCAR, _hoops_SRCP, 1, _hoops_SPHIC|_hoops_GHHIC);
					_hoops_PAHIC (_hoops_ARCAR, _hoops_SRCP);
				}
				break;
			case _hoops_AACHC:
				_hoops_CIHIC (_hoops_ARCAR, _hoops_SRCP, 1, null, false);
				break;
			default:
				_hoops_ISHIC (_hoops_ARCAR, _hoops_SRCP, 1, _hoops_GSCHC[_hoops_HSCIC], false);
				break;
		}

		_hoops_ARCAR->_hoops_GGRHH->Flush();

		_hoops_PCGIC (_hoops_ARCAR, _hoops_SRCP, true, false);
	}

	HOOPS_WORLD->_hoops_AGHGI = 0;//_hoops_RCPP;

	_hoops_HPRIC (_hoops_SRCP);
}


local void _hoops_ISCIC (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	char const *			option_string) {
	Option_Value *			option_list;
	Option_Value *			option;
	bool					_hoops_IPCIC = false;

	_hoops_HIACR (_hoops_PIRGI, _hoops_GRSHC);

	if (!HI_Parse_Options (_hoops_RIGC, option_string, _hoops_CIACR (_hoops_PIRGI), &option_list, _hoops_SIACR))
		return;

	_hoops_ICCHC	_hoops_ARCAR;
	ZERO_STRUCT (&_hoops_ARCAR, _hoops_ICCHC);
	_hoops_ARCAR._hoops_RIGC = _hoops_RIGC;
	//_hoops_SAHHH._hoops_CSCIC = _hoops_SSCIC(_hoops_GGSIC); _hoops_CPHR _hoops_RAS _hoops_CGHI _hoops_ASRC
	_hoops_ARCAR._hoops_PSCHC = _hoops_RCIHC;
	_hoops_ARCAR._hoops_ASCHC = _hoops_ACIHC;
	_hoops_ARCAR._hoops_HSCHC = _hoops_PCIHC;
	_hoops_ARCAR._hoops_ISCHC = _hoops_HCIHC;
	_hoops_ARCAR._hoops_CSCHC = _hoops_ICIHC;
	_hoops_ARCAR._hoops_SSCHC = _hoops_CCIHC;
	_hoops_ARCAR._hoops_GGSHC = _hoops_SCIHC;
	//_hoops_SAHHH._hoops_RGSIC = _hoops_RAPCI(_hoops_AGSIC)(_hoops_PGSIC); _hoops_CPHR _hoops_RAS _hoops_CGHI _hoops_ASRC

	if ((option = option_list) != null) do {
		int				_hoops_ARPPH = option->type->id;

		if (option->_hoops_GCACR)
			_hoops_ARCAR.flags &= ~_hoops_ARPPH;
		else {
			_hoops_ARCAR.flags |= _hoops_ARPPH;

			if (_hoops_ARPPH == _hoops_PSIHC) {
				Option_Value *	_hoops_AHSAA = option->value.option_list;

				if (_hoops_AHSAA != null) do {
					if (_hoops_AHSAA->type->id == _hoops_SRCHC) {
						_hoops_ARCAR.flags &= ~_hoops_ARPPH;

						if (_hoops_AHSAA != option->value.option_list || _hoops_AHSAA->next != null)
							HE_WARNING (HEC_SYNTAX, HES_PARSE_STRING,
										"'reorganize=off' specified, all other 'reorganize' options ignored");
					}
					else {
						if (_hoops_AHSAA->type->id == HK_COLOR) {
							_hoops_ARCAR._hoops_GSCHC[_hoops_ARCAR._hoops_RSCHC++] = _hoops_IPAIR;
							_hoops_ARCAR._hoops_GSCHC[_hoops_ARCAR._hoops_RSCHC++] = HK_COLOR_MAP;
						}

						_hoops_ARCAR._hoops_GSCHC[_hoops_ARCAR._hoops_RSCHC++] = (int)_hoops_AHSAA->type->id;

						if (_hoops_AHSAA->type->id == HK_COLOR)
							_hoops_ARCAR._hoops_GSCHC[_hoops_ARCAR._hoops_RSCHC++] = _hoops_AACHC;
					}
				} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
			}
			else if (_hoops_ARPPH == _hoops_HGCHC) {
				Option_Value *	_hoops_AHSAA = option->value.option_list;

				if (_hoops_AHSAA != null) do {
					switch (_hoops_AHSAA->type->id) {
						case 0:								// _hoops_HHHA _hoops_PSAP
							_hoops_ARCAR.flags &= ~_hoops_HGCHC;
							break;

						case _hoops_HGCHC:	// _hoops_HHHA _hoops_GPP (_hoops_AIAH _hoops_ARP)
							break;

						case _hoops_RRCHC:		// _hoops_HASC _hoops_HGRC
							_hoops_ARCAR.flags |= _hoops_RRCHC;
							break;
					}
				} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
			}
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);

	if (_hoops_ARCAR.flags == 0)
		return;		/* _hoops_ISAP _hoops_HGRC? */

	if (BIT (_hoops_ARCAR.flags, _hoops_HGCHC))
		_hoops_ARCAR.flags &= ~_hoops_GGCHC;

	// _hoops_HAR _hoops_HHPA
	//_hoops_SAHHH._hoops_SGI |= _hoops_HGSIC|_hoops_IGSIC|_hoops_CGSIC;

	_hoops_ARCAR.memory_pool = HI_Create_Memory_Pool(MPF_NONE);
	_hoops_ARCAR._hoops_GGRHH = POOL_NEW(_hoops_ARCAR.memory_pool, _hoops_AAPHP)(_hoops_ARCAR.memory_pool, _hoops_PAPHP);
	_hoops_RPPPR();

	/* _hoops_ISPR _hoops_IH _hoops_SGSIC _hoops_AAIP _hoops_SRS? */
	if (BIT (_hoops_ARCAR.flags, _hoops_PSIHC)) {
		/* _hoops_RHSGH _hoops_CRRPR *_hoops_CRGR* _hoops_RGR _hoops_HHIS (_hoops_HAR _hoops_RPCPR _hoops_SCIA) _hoops_PGI _hoops_PAH _hoops_HAR _hoops_SHH _hoops_CPHR,
			_hoops_PAR _hoops_HGAP _hoops_RH _hoops_PGPAA _hoops_SGHC _hoops_SHH _hoops_ARP _hoops_IIRAA _hoops_PPR _hoops_ICACR _hoops_PPSAR _hoops_ISSC _hoops_CRGR
			_hoops_RH _hoops_HACH _hoops_GHPP

			_hoops_PSHR _hoops_ARPC _hoops_CCA:
				_hoops_RCAR _hoops_RSSA
				_hoops_HPPA _hoops_GHC (_hoops_GHCA _hoops_SHH _hoops_IRGH)
				_hoops_PGSA _hoops_CAGH [_hoops_HHIS] _hoops_ASGC

			_hoops_IPPAR _hoops_ARPC _hoops_CCA _hoops_HH _hoops_APRIP -- _hoops_RH "_hoops_CGRIR" _hoops_CSPGI _hoops_GHCA _hoops_GARIR _hoops_GPP _hoops_APRIP
			_hoops_PHPA _hoops_GGR _hoops_RH _hoops_HHIS _hoops_PGAP _hoops_PAH'_hoops_RA _hoops_GHRHA; _hoops_GRSIC _hoops_GIIS _hoops_IRHS >1 _hoops_CAGH _hoops_PAPA
			_hoops_IS _hoops_HCAAA _hoops_RH _hoops_PHPA _hoops_APRIP
		*/
	}


	if (BIT (_hoops_ARCAR.flags, _hoops_RSIHC)) {
		_hoops_ISSHC (&_hoops_ARCAR, _hoops_SRCP);
	}

	if (BIT (_hoops_ARCAR.flags, _hoops_GRCHC) && !BIT(_hoops_ARCAR.flags, _hoops_CSIHC)) {
		_hoops_RGGIC (&_hoops_ARCAR, _hoops_SRCP);
	}

	_hoops_GRIIC (_hoops_RIGC, _hoops_SRCP);

	HI_Delete_Renditions (_hoops_RIGC, _hoops_SRCP);

	if (BIT (_hoops_ARCAR.flags, _hoops_HSIHC)) {
		/* _hoops_HASIR _hoops_AIRC _hoops_PGAP _hoops_HS _hoops_ISAP _hoops_IS _hoops_HAHA (_hoops_SHCAR _hoops_RRSIC _hoops_RPP _hoops_RGAR _hoops_SCHS _hoops_GPRI) */
		/* _hoops_PAH'_hoops_RA _hoops_AA _hoops_RGR _hoops_RPP _hoops_CRRPR _hoops_SGAGA _hoops_CAPP (_hoops_PAR _hoops_RRP _hoops_IS _hoops_ARSIC _hoops_CRGR _hoops_RH _hoops_CRRPR?) */
	}

	/* _hoops_HASIR _hoops_AH _hoops_PIH (_hoops_AIRI _hoops_CPCI _hoops_IH _hoops_HA) */
	/* _hoops_SIGP: _hoops_GAAP   _hoops_AACC _hoops_CPAP, _hoops_RGCH, _hoops_GCSS _hoops_HGIIP, _hoops_HCHSR _hoops_PSCA */
	if (ANYBIT (_hoops_ARCAR.flags, _hoops_ASIHC|_hoops_PSIHC|_hoops_ISIHC)) {
		_hoops_HHSHC (_hoops_RIGC, _hoops_SRCP);
	}


	if (BIT (_hoops_ARCAR.flags, _hoops_GGCHC)) {
		/* _hoops_SPIC _hoops_HHIS _hoops_HGAPA _hoops_IPSP _hoops_AAP & _hoops_HSH _hoops_HII _hoops_SGHC & _hoops_CPAP */
		_hoops_PSSHC (&_hoops_ARCAR, _hoops_SRCP, false);
	}


	if (BIT (_hoops_ARCAR.flags, _hoops_PSIHC)) {
		_hoops_GARIC(&_hoops_ARCAR, _hoops_SRCP, true);

		if (!BIT (_hoops_ARCAR.flags, _hoops_GGCHC)) {
			/* _hoops_SPIC _hoops_HHIS _hoops_PRSIC _hoops_IPSP _hoops_AAP */
			_hoops_PSSHC (&_hoops_ARCAR, _hoops_SRCP, true);
		}

		ASSERT(_hoops_ARCAR._hoops_GGRHH->Count() == 0);
		_hoops_CIHIC (&_hoops_ARCAR, _hoops_SRCP, 1, null, true);
		_hoops_ARCAR._hoops_GGRHH->Flush();
		_hoops_PCGIC (&_hoops_ARCAR, _hoops_SRCP, true, false);

		/* _hoops_HSHPC _hoops_SPSHI _hoops_IS _hoops_SGHC, _hoops_GHRHA _hoops_PICAA (_hoops_PSP _hoops_AIRC, _hoops_PSP _hoops_CPAP) _hoops_SGHC */
		_hoops_IGIIC (&_hoops_ARCAR, _hoops_SRCP, _hoops_SRCP->bounding);
	}
	else if (BIT (_hoops_ARCAR.flags, _hoops_ASIHC)) {
		/* _hoops_SPIC _hoops_HHIS _hoops_RCRS _hoops_HCIA _hoops_PPR _hoops_HPHRA _hoops_CRGR _hoops_PPSR _hoops_PIH */
		_hoops_SISHC (&_hoops_ARCAR, _hoops_SRCP, null, 0, true);
		/* _hoops_HGIHR _hoops_GH _hoops_RH _hoops_IASC _hoops_RGCRA _hoops_HA */
		_hoops_HPRIC (_hoops_SRCP);
	}


	if (BIT (_hoops_ARCAR.flags, _hoops_HSIHC)) {
		/* _hoops_HASIR _hoops_AIRC _hoops_PGAP _hoops_CHR _hoops_RH _hoops_PSHR _hoops_GAR _hoops_RH _hoops_PCIRA _hoops_CAGH (_hoops_RPP _hoops_IRS _hoops_CAGH _hoops_HRGR _hoops_PGPAA,
			_hoops_PSCR _hoops_RGAR _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_GACC _hoops_PSHR _hoops_GAR _hoops_HCR _hoops_HCSHC -- _hoops_RPP _hoops_SR _hoops_PAH _hoops_CGIC _hoops_SGS...) */
	}

	if (BIT (_hoops_ARCAR.flags, _hoops_ISIHC)) {
		/* _hoops_IHSH _hoops_IH _hoops_HACH _hoops_SGHC _hoops_CCA _hoops_GPGR _hoops_SCHS _hoops_SGS _hoops_PAH _hoops_SHH _hoops_RPHGA */
		/* _hoops_RPP _hoops_IRS _hoops_HACH _hoops_RRCPR _hoops_HRGR _hoops_RH _hoops_RGAR _hoops_CPAP _hoops_GGR _hoops_IRS _hoops_CAGH _hoops_PPR _hoops_IIH _hoops_CHR _hoops_PSP _hoops_AIRC _hoops_HIHPA
			_hoops_HAIR _hoops_PPR _hoops_PRRIC, _hoops_AGAP _hoops_AIRC _hoops_HHS _hoops_SHH _hoops_RIPPR _hoops_CRGR _hoops_RH _hoops_RRCPR _hoops_PPR _hoops_RH _hoops_RRCPR
			_hoops_ACAS _hoops_RIPPR _hoops_CRGR _hoops_RH _hoops_PCIRA _hoops_CAGH
		*/
		_hoops_HHIIC (&_hoops_ARCAR, _hoops_SRCP);
	}

	if (BIT (_hoops_ARCAR.flags, _hoops_PGCHC)) {
		_hoops_IPCIC = true;
	}

	if (BIT (_hoops_ARCAR.flags, _hoops_AGCHC) || _hoops_IPCIC) {
		/* _hoops_HAGAR _hoops_GII _hoops_SSRS _hoops_SCHS */
		_hoops_AGCIC *             _hoops_GSCIC[256];

		ZERO_ARRAY(_hoops_GSCIC, 256, _hoops_AGCIC*);

		int		rotations = _hoops_SCCIC (&_hoops_ARCAR, _hoops_SRCP, _hoops_GSCIC, null, _hoops_IPCIC);
		UNREFERENCED(rotations);

		for (int i = 0; i < 256; i++) {
			_hoops_AGCIC *			instance = _hoops_GSCIC[i];

			while (instance != null) {
				_hoops_AGCIC *		next = instance->next;

                while (instance->_hoops_IRCIC != null) {
					_hoops_RGCIC *		victim = instance->_hoops_IRCIC;

					instance->_hoops_IRCIC = victim->next;

                    if (victim->_hoops_CGRRC)
                        FREE_ARRAY (victim->_hoops_CGRRC, 16, float);
                    FREE (victim, _hoops_RGCIC);
                }
				FREE (instance, _hoops_AGCIC);
				instance = next;
			}
		}
	}

	/* _hoops_HACH _hoops_PHARA _hoops_RIH _hoops_IH (_hoops_APGP) _hoops_RHPA _hoops_SGHC */
	_hoops_SRCP->_hoops_RRHH |= _hoops_CACHC;	// _hoops_HIH _hoops_AGSAH _hoops_ACSRR _hoops_CPPPR _hoops_IIGSH _hoops_AGIR
	_hoops_SSIIC (&_hoops_ARCAR, _hoops_SRCP, true);
	_hoops_SRCP->_hoops_RRHH &= ~_hoops_CACHC;


	if (BIT(_hoops_ARCAR.flags, _hoops_CSIHC)) {
		if (BIT (_hoops_ARCAR.flags, _hoops_GRCHC)) {
			_hoops_RGGIC (&_hoops_ARCAR, _hoops_SRCP);
		}
		/* _hoops_CAHP _hoops_HACH _hoops_SIA _hoops_GASR & _hoops_CASI _hoops_GGSR _hoops_RRSRR */
		_hoops_CSIIC (&_hoops_ARCAR, _hoops_SRCP);
	}

	_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_PCPGP |
							 _hoops_CSCCA |
							 _hoops_PISSR |
							 _hoops_RPSIR |
							 _hoops_SSCCA);

	_hoops_IRRPR();

	delete _hoops_ARCAR._hoops_GGRHH;

#ifdef VALIDATE_MEMORY
	size_t allocated = 0;
	HI_Relinquish_Memory_On_Pool (_hoops_ARCAR.memory_pool);
	HI_Memory_On_Pool(_hoops_ARCAR.memory_pool, &allocated);
	if (allocated > 0) {
		HE_WARNING (HEC_HOOPS_SYSTEM, HES_MEMORY_USAGE, "Memory leak detected in optimize tree memory pool.");
		HI_Dump_Allocation_Metadata (_hoops_ARCAR.memory_pool, "optimize tree memory pool");
	}
#endif

	HI_Destroy_Memory_Pool(_hoops_ARCAR.memory_pool);
}

HC_INTERFACE void HC_CDECL HC_Optimize_Segment_Tree (
	char const *		segname,
	char const *		option_string)
{
	_hoops_PAPPR context("Optimize_Segment_Tree");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Optimize_Segment_Tree (%S, %S);\n",
								  segname, option_string));
	);

	_hoops_RPPPR();
	_hoops_CRCP *	_hoops_SRCP;
	if ((_hoops_SRCP = HI_One_Segment_Search (context, segname, true)) != null) {
		_hoops_ISCIC (context, _hoops_SRCP, option_string);
	}
	_hoops_IRRPR();
}

HC_INTERFACE void HC_CDECL HC_Optimize_Segment_Tree_By_Key (
	Key					segkey,
	char const *		option_string)
{
	_hoops_PAPPR context("Optimize_Segment_Tree_By_Key");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Optimize_Segment_Tree_By_Key (LOOKUP (%D), ", segkey));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", option_string));
	);

	_hoops_RPPPR();
	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (context, segkey);

	if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP || BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");
	}
	else
		_hoops_ISCIC (context, _hoops_SRCP, option_string);

	_hoops_IRRPR();
}


HC_INTERFACE void HC_CDECL HC_Show_Optimized_Mapping (
	char const *				segname,
	char const *				direction,
	Key							in_owner,
	Key							in_key,
	int							in_region,
	Key *						out_owner,
	Key *						out_key,
	int *						out_region)
{
	_hoops_PAPPR context("Show_Optimized_Mapping");

	*out_owner = in_owner;
	*out_key = in_key;
	*out_region = in_region;

	_hoops_CSPPR();
	_hoops_CRCP *	_hoops_SRCP;
	if ((_hoops_SRCP = HI_One_Segment_Search (context, segname, true)) != null) {
		_hoops_IAPGI *	table;
		_hoops_HCRPR						_hoops_HRSIC;
		bool						_hoops_AGRCA;

		HI_Canonize_Chars (direction, &_hoops_HRSIC);
		_hoops_AGRCA = (_hoops_HRSIC.length > 0 && _hoops_HRSIC.text[0] == 'b');
		_hoops_RGAIR (_hoops_HRSIC);

		if ((table = HOOPS_WORLD->_hoops_IIHGI) != null) do {
			if (table->segment == _hoops_SRCP) {
				int						_hoops_GCAH = _hoops_ASIIC (in_key, in_region);
				_hoops_AAPGI *	_hoops_SPRAR;

				if (!_hoops_AGRCA) {
					if ((_hoops_SPRAR = table->forward[_hoops_GCAH]) != null) do {
						if ((_hoops_SPRAR->original.owner == in_owner || in_owner == _hoops_SHSSR) &&
							_hoops_SPRAR->original.key == in_key &&
							_hoops_SPRAR->original.region == in_region) {
							*out_owner = _hoops_SPRAR->_hoops_HAPGI.owner;
							*out_key = _hoops_SPRAR->_hoops_HAPGI.key;
							*out_region = _hoops_SPRAR->_hoops_HAPGI.region;
							break;
						}
					} while ((_hoops_SPRAR = _hoops_SPRAR->forward) != null);
				}
				else {
					if ((_hoops_SPRAR = table->_hoops_PAPGI[_hoops_GCAH]) != null) do {
						if ((_hoops_SPRAR->_hoops_HAPGI.owner == in_owner || in_owner == _hoops_SHSSR) &&
							_hoops_SPRAR->_hoops_HAPGI.key == in_key &&
							_hoops_SPRAR->_hoops_HAPGI.region == in_region) {
							*out_owner = _hoops_SPRAR->original.owner;
							*out_key = _hoops_SPRAR->original.key;
							*out_region = _hoops_SPRAR->original.region;
							break;
						}
					} while ((_hoops_SPRAR = _hoops_SPRAR->_hoops_PAPGI) != null);
				}
				break;
			}
		} while ((table = table->next) != null);
	}
	_hoops_IRRPR();
}


/**************************************************************************************************/

#ifdef _hoops_SIIHC
local bool _hoops_IRSIC (
	_hoops_CRCP const *			_hoops_SRCP) {
	Subsegment const *		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;

	if (_hoops_GIPIA == null || _hoops_GIPIA->next == null)
		goto _hoops_CRSIC;

	if (_hoops_GIPIA->next == null) {
		if (_hoops_GIPIA->priority == 0 ||
			(_hoops_GIPIA->type == _hoops_AGRPR && BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_HPAPA)))
			goto _hoops_CRSIC;

		return false;
	}

	do {
		if (BIT (_hoops_GIPIA->_hoops_RRHH, _hoops_PASIR) ||
			_hoops_GIPIA->priority != 0 &&
			(_hoops_GIPIA->type == _hoops_IRCP || !BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_HPAPA)))
			return true;
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

_hoops_CRSIC:
	((_hoops_CRCP *)_hoops_SRCP)->_hoops_PHSI &= ~(_hoops_GGPSA | _hoops_CCHGP);

	return false;
}
#endif



local _hoops_PICHC * _hoops_SRSIC(_hoops_ICCHC * _hoops_ARCAR, _hoops_SASC * cuboid, bool _hoops_GASIC)
{
	_hoops_PICHC *	_hoops_ASCIA;
	POOL_ZALLOC_CACHED(_hoops_ASCIA, _hoops_PICHC, _hoops_ARCAR->memory_pool);

	_hoops_ASCIA->cuboid = *cuboid;

	if (_hoops_GASIC) {
		float _hoops_RASIC = _hoops_IAAA(cuboid->max.x - cuboid->min.x, cuboid->max.y - cuboid->min.y, cuboid->max.z - cuboid->min.z) * 0.5f;
		Vector _hoops_AASIC(_hoops_RASIC,_hoops_RASIC,_hoops_RASIC);
		Point _hoops_RICIR = _hoops_AICIR(_hoops_ASCIA->cuboid.min, _hoops_ASCIA->cuboid.max);
		_hoops_ASCIA->cuboid.Merge(_hoops_RICIR+_hoops_AASIC);
		_hoops_ASCIA->cuboid.Merge(_hoops_RICIR-_hoops_AASIC);
	}

	Vector _hoops_IGHCP = _hoops_ASCIA->cuboid._hoops_RSAIA() / _hoops_CICHC;

	for (int i=0; i<_hoops_CICHC+1; i++) {
		_hoops_ASCIA->_hoops_RCCHC[i] = _hoops_ASCIA->cuboid.min + _hoops_IGHCP * (float)i;
	}

	return _hoops_ASCIA;
}

local _hoops_ACCHC * _hoops_PASIC(
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SCAAR)
{
	_hoops_ACCHC *	_hoops_CCCHC;
	_hoops_ARCAR->_hoops_CCCHC->LookupItem(_hoops_SCAAR, &_hoops_CCCHC);
	if (_hoops_CCCHC == null) {
		_hoops_CCCHC = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_ACCHC)();
		_hoops_ARCAR->_hoops_CCCHC->InsertItem(_hoops_SCAAR, _hoops_CCCHC);
		if (BIT(_hoops_ARCAR->flags, _hoops_ARCHC)) {
			if (!_hoops_SCAAR->bounding._hoops_HICAR())
				_hoops_CCCHC->_hoops_ASCIA = _hoops_SRSIC(_hoops_ARCAR, &_hoops_SCAAR->bounding->cuboid, true);
		}
	}
	return _hoops_CCCHC;
}


local _hoops_HICHC * _hoops_HASIC(
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_PICHC *		_hoops_ASCIA,
	_hoops_CRCP const *		_hoops_SRCP,
	_hoops_CRCP *			_hoops_SCAAR,
	int					level=0,
	int *				_hoops_IASIC=null,
	bool				_hoops_CASIC=false)
{
	_hoops_SASC		cuboid;
	int					_hoops_RCHA = 0;
	_hoops_SASC		_hoops_SASIC;

	int					_hoops_GPSIC[_hoops_GCCHC+1];

	if (_hoops_IASIC == null) {
		ZERO_ARRAY(_hoops_GPSIC, _hoops_GCCHC+1, int);
		_hoops_IASIC = _hoops_GPSIC;
	}

	if (_hoops_SRCP->bounding._hoops_HICAR()) {
		_hoops_RCHA = _hoops_SICHC-1;
	}
	else {
		cuboid = _hoops_SRCP->bounding->cuboid;

		for (int i=0; i<_hoops_CICHC; i++) {
			if (cuboid.max.x >= _hoops_ASCIA->_hoops_RCCHC[i].x &&
				cuboid.min.x <= _hoops_ASCIA->_hoops_RCCHC[i+1].x) {
				_hoops_RCHA |= 1<<(i+_hoops_CICHC*0);
				_hoops_SASIC.min.x = _hoops_AHIA(_hoops_SASIC.min.x, _hoops_ASCIA->_hoops_RCCHC[i].x);
				_hoops_SASIC.max.x = _hoops_IAAA(_hoops_SASIC.max.x, _hoops_ASCIA->_hoops_RCCHC[i+1].x);
			}

			if (cuboid.max.y >= _hoops_ASCIA->_hoops_RCCHC[i].y &&
				cuboid.min.y <= _hoops_ASCIA->_hoops_RCCHC[i+1].y) {
				_hoops_RCHA |= 1<<(i+_hoops_CICHC*1);
				_hoops_SASIC.min.y = _hoops_AHIA(_hoops_SASIC.min.y, _hoops_ASCIA->_hoops_RCCHC[i].y);
				_hoops_SASIC.max.y = _hoops_IAAA(_hoops_SASIC.max.y, _hoops_ASCIA->_hoops_RCCHC[i+1].y);
			}

			if (cuboid.max.z >= _hoops_ASCIA->_hoops_RCCHC[i].z &&
				cuboid.min.z <= _hoops_ASCIA->_hoops_RCCHC[i+1].z) {
				_hoops_RCHA |= 1<<(i+_hoops_CICHC*2);
				_hoops_SASIC.min.z = _hoops_AHIA(_hoops_SASIC.min.z, _hoops_ASCIA->_hoops_RCCHC[i].z);
				_hoops_SASIC.max.z = _hoops_IAAA(_hoops_SASIC.max.z, _hoops_ASCIA->_hoops_RCCHC[i+1].z);
			}
		}

		if (_hoops_RCHA == 0)
			_hoops_RCHA = _hoops_SICHC-1;

		//_hoops_AGHR(_hoops_SIH>>(_hoops_RPSIC*0) & (1<<_hoops_RPSIC)-1); //_hoops_SISR
		//_hoops_AGHR(_hoops_SIH>>(_hoops_RPSIC*1) & (1<<_hoops_RPSIC)-1); //_hoops_HAPC
		//_hoops_AGHR(_hoops_SIH>>(_hoops_RPSIC*2) & (1<<_hoops_RPSIC)-1); //_hoops_SSH
	}

	_hoops_IASIC[level] = _hoops_RCHA;

	_hoops_HICHC * _hoops_APSIC = _hoops_ASCIA->_hoops_HGASH[_hoops_RCHA];

	if (_hoops_APSIC == null) {
		POOL_ZALLOC(_hoops_APSIC, _hoops_HICHC, _hoops_ARCAR->memory_pool);
		_hoops_ASCIA->_hoops_HGASH[_hoops_RCHA] = _hoops_APSIC;

		local const	char	_hoops_PPSIC[] = "0123456789abcdef";

		int n = 0;

		_hoops_ARCAR->_hoops_RGSHC[n++] = 'm';
		_hoops_ARCAR->_hoops_RGSHC[n++] = 's';
		_hoops_ARCAR->_hoops_RGSHC[n++] = 'n';
		_hoops_ARCAR->_hoops_RGSHC[n++] = ' ';

		for (int i=0; i<=level; i++) {
			POINTER_SIZED_INT _hoops_HPSIC = _hoops_IASIC[i];
			bool first = false;
			for (int j=1; j<=sizeof(POINTER_SIZED_INT); j++) {
				int shift = (sizeof(POINTER_SIZED_INT)-j)*8;
				int index = _hoops_HPSIC>>shift;

				if (first || (index&0xF0) != 0) {
					first = true;
					_hoops_ARCAR->_hoops_RGSHC[n++] = _hoops_PPSIC[(index&0xF0) >> 4];
				}

				if (first || (index&0x0F) != 0 || j == sizeof(POINTER_SIZED_INT)) {
					first = true;
					_hoops_ARCAR->_hoops_RGSHC[n++] = _hoops_PPSIC[index&0x0F];
				}
			}
			_hoops_ARCAR->_hoops_RGSHC[n++] = ':';
		}
		_hoops_ARCAR->_hoops_RGSHC[--n] = '\0';

		_hoops_APSIC->_hoops_SRCP = _hoops_HASHC(_hoops_ARCAR, _hoops_SCAAR, _hoops_ARCAR->_hoops_RGSHC, _hoops_HACHC);
	}
	else if (_hoops_RCHA != _hoops_SICHC-1 &&
			 level < _hoops_GCCHC &&
			 _hoops_APSIC->_hoops_IICHC._hoops_RICHC > 0) {

		if (_hoops_APSIC->_hoops_ASCIA == null) {
			_hoops_APSIC->_hoops_ASCIA = _hoops_SRSIC(_hoops_ARCAR, &_hoops_SASIC, false);

			Subsegment *	_hoops_SIIS = _hoops_APSIC->_hoops_SRCP->_hoops_RGRPR;

			_hoops_APSIC->_hoops_SRCP->_hoops_RGRPR = null;
			_hoops_APSIC->_hoops_IICHC._hoops_RICHC = 0;

			while (_hoops_SIIS != null) {
				Subsegment * next = _hoops_SIIS->next;
				_hoops_HICHC * _hoops_IPSIC = _hoops_HASIC(_hoops_ARCAR, _hoops_APSIC->_hoops_ASCIA, (_hoops_CRCP const *)_hoops_SIIS, _hoops_APSIC->_hoops_SRCP, level+1, _hoops_IASIC, _hoops_CASIC);
				_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_SIIS, _hoops_IPSIC->_hoops_SRCP);
				_hoops_SIIS->owner = _hoops_IPSIC->_hoops_SRCP;
				_hoops_IPSIC->_hoops_IICHC._hoops_RICHC++;
				if (_hoops_CASIC) {
					_hoops_IPSIC->_hoops_SRCP->_hoops_RCGC |= ((_hoops_CRCP*)_hoops_SIIS)->_hoops_RCGC;
					if (_hoops_IPSIC->_hoops_SRCP->bounding == null)
						_hoops_IPSIC->_hoops_SRCP->bounding = ((_hoops_CRCP*)_hoops_SIIS)->bounding;
					else
						_hoops_IPSIC->_hoops_SRCP->bounding->Merge(((_hoops_CRCP*)_hoops_SIIS)->bounding);
				}
				_hoops_SIIS = next;
			}
		}
	}

	if (_hoops_APSIC->_hoops_ASCIA != null)
		_hoops_APSIC = _hoops_HASIC(_hoops_ARCAR, _hoops_APSIC->_hoops_ASCIA, _hoops_SRCP, _hoops_APSIC->_hoops_SRCP, level+1, _hoops_IASIC, _hoops_CASIC);

	return _hoops_APSIC;
}


local void _hoops_CPSIC(_hoops_ICCHC * _hoops_ARCAR, _hoops_CRCP * _hoops_SRCP, _hoops_CRCP const * root,
							 _hoops_PIGRA * locks=0, _hoops_SPPIR * conditions=0);

/* _hoops_CRICR _hoops_IS _hoops_SPSIC, _hoops_HIH _hoops_CRHPR _hoops_IRS _hoops_IPS */
local int _hoops_GHSIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			tree,
	_hoops_CRCP *			_hoops_HRSSA,
	_hoops_CRCP const *		_hoops_SRCP,
	Attribute const *	_hoops_PARIC,
	_hoops_CRCP const *		root,
	bool				direct,
	_hoops_PIGRA *	locks,
	_hoops_SPPIR *		conditions)
{
	_hoops_CRCP *			node = tree;
	bool				_hoops_IARIC = false;
	int					_hoops_PIHRC;
	_hoops_CHCHC *	_hoops_CARIC = null;
	Attribute const *	_hoops_RHSIC = _hoops_PARIC;
	_hoops_ACCHC *		_hoops_CCCHC;

	if (conditions != null)
		_hoops_PRRH (conditions);

top:
	_hoops_PIHRC = 0;

	ASSERT(BIT(_hoops_ARCAR->flags, _hoops_PRCHC));
	ASSERT(!BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HIRIR));

	if (_hoops_SRCP == root) {
		/* _hoops_RCSAR '_hoops_SRRPR' _hoops_GRS _hoops_SHH _hoops_SARIC */
		tree->_hoops_RRHH |= _hoops_PACHC;

		if (_hoops_SRCP->geometry != null) {
			_hoops_CCCHC = _hoops_PASIC(_hoops_ARCAR, tree);

			_hoops_CRCP *	_hoops_AHSIC = node;

			if (!BIT (_hoops_PIHRC, _hoops_GPGIC) &&
				_hoops_CCCHC->_hoops_ASCIA != null) {

				_hoops_HICHC * _hoops_APSIC = _hoops_HASIC(_hoops_ARCAR, _hoops_CCCHC->_hoops_ASCIA, tree, node);
				_hoops_AHSIC = _hoops_APSIC->_hoops_SRCP;
			}

			_hoops_CRCP * _hoops_PHSIC = _hoops_HASHC(_hoops_ARCAR, _hoops_AHSIC, "root geometry");
			node->_hoops_RCGC |= _hoops_SRCP->_hoops_RCGC & (_hoops_AHHGP|_hoops_CPHGP);
			_hoops_IGPIC (_hoops_ARCAR, _hoops_PHSIC, _hoops_SRCP);
			// _hoops_ASIGA _hoops_SPRHA _hoops_PHSSI
		}

		// _hoops_ASIGA _hoops_SGHS
		_hoops_PIHRC |= _hoops_HAGIC | _hoops_SAGIC;
	}
	else {
		bool			_hoops_GPRIC = false;
		_hoops_CRCP *		_hoops_SCAAR = tree;

		_hoops_PIHRC |= _hoops_SAGGC (_hoops_ARCAR, _hoops_SRCP, conditions);

		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR))
			_hoops_IARIC = true;

		/* _hoops_PAH'_hoops_RA _hoops_ASRS _hoops_CIPH _hoops_PII _hoops_ARAH-_hoops_SPHGR _hoops_CRGR _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_HIRA.
		   _hoops_RPP _hoops_PRCHR, _hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_HASC _hoops_GGR _hoops_GCIAA _hoops_AIRC _hoops_CR _hoops_SGS _hoops_CHH _hoops_GPGSA _hoops_GH
			_hoops_SGH _hoops_GAR _hoops_IRS _hoops_IAHA _hoops_PAR _hoops_GGCR _hoops_RPRIC _hoops_AIRC _hoops_IH _hoops_PCCP _hoops_PPCPI, _hoops_HIS _hoops_SHSP _hoops_SCH
			_hoops_ARI _hoops_CAS _hoops_SCH _hoops_GRS _hoops_CAPGP _hoops_GGR _hoops_RH _hoops_GSSR _hoops_CRAA _hoops_HAH.  _hoops_PS _hoops_PAH, _hoops_HGRRA, _hoops_HPPR _hoops_IS
			_hoops_SGGC _hoops_GIAA _hoops_RGR _hoops_CAGH
		*/
		if (BIT(_hoops_PIHRC, _hoops_IAGIC))
			_hoops_GPRIC = false;
		else {
			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PACAA))
				_hoops_GPRIC = true;
#ifdef _hoops_SIIHC
			else if (_hoops_SRCP->priority != 0 ||
				BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GGPSA) && _hoops_IRSIC(_hoops_SRCP))
				_hoops_GPRIC = true;
#endif
			else
				_hoops_GPRIC = ANYBIT(_hoops_PIHRC, ~(_hoops_IAGIC|_hoops_APGIC));

			if (_hoops_GPRIC && _hoops_PARIC)
				_hoops_SCAAR = _hoops_HRSSA;
		}

		_hoops_CCCHC = _hoops_PASIC(_hoops_ARCAR, _hoops_SCAAR);

		_hoops_GICHC *	_hoops_IICHC = &_hoops_CCCHC->_hoops_IICHC;
		_hoops_CRCP *		_hoops_AHSIC = _hoops_SCAAR;

		if (!BIT (_hoops_PIHRC, _hoops_GPGIC) &&
			_hoops_CCCHC->_hoops_ASCIA != null) {

			_hoops_HICHC * _hoops_APSIC = _hoops_HASIC(_hoops_ARCAR, _hoops_CCCHC->_hoops_ASCIA, _hoops_SRCP, _hoops_SCAAR);
			_hoops_AHSIC = _hoops_APSIC->_hoops_SRCP;
			_hoops_IICHC = &_hoops_APSIC->_hoops_IICHC;
		}

		_hoops_IICHC->_hoops_RICHC++;

#define _hoops_HHSIC	10000
		if (_hoops_IICHC->_hoops_RICHC > _hoops_HHSIC) {
			bool _hoops_IHSIC = false;
			if (_hoops_PARIC) {
				_hoops_IHSIC = BIT(_hoops_PARIC->owner->_hoops_PHSI, _hoops_HIHIC);
				_hoops_PARIC->owner->_hoops_PHSI |= _hoops_HIHIC;
			}
			_hoops_CIHIC (_hoops_ARCAR, _hoops_AHSIC, 1, _hoops_IICHC, false);
			if (_hoops_PARIC) {
				if (!_hoops_IHSIC)
					_hoops_PARIC->owner->_hoops_PHSI &= ~_hoops_HIHIC;
			}
		}


		if (_hoops_GPRIC) {
			if (_hoops_SRCP->name.length > 0)
				_hoops_PIRHH (_hoops_ARCAR->_hoops_RIGC, _hoops_ARCAR->_hoops_RGSHC, "%n -- root", &_hoops_SRCP->name);
			else
				_hoops_AAHR("unnamed -- root", _hoops_ARCAR->_hoops_RGSHC);
		}
		else if (BIT (_hoops_PIHRC, _hoops_IAGIC)) {
			if (_hoops_SRCP->name.length > 0)
				_hoops_PIRHH (_hoops_ARCAR->_hoops_RIGC, _hoops_ARCAR->_hoops_RGSHC, "%n -- include", &_hoops_SRCP->name);
			else
				_hoops_AAHR("unnamed -- include", _hoops_ARCAR->_hoops_RGSHC);
		}
		else {
			if (_hoops_SRCP->name.length > 0)
				_hoops_PIRHH (_hoops_ARCAR->_hoops_RIGC, _hoops_ARCAR->_hoops_RGSHC, "%n", &_hoops_SRCP->name);
			else
				_hoops_AAHR("unnamed", _hoops_ARCAR->_hoops_RGSHC);
		}

		node = _hoops_HASHC(_hoops_ARCAR, _hoops_AHSIC, _hoops_ARCAR->_hoops_RGSHC);
		node->_hoops_RCGC |= _hoops_SRCP->_hoops_RCGC & (_hoops_AHHGP|_hoops_CPHGP);

		if (BIT(_hoops_ARCAR->flags, _hoops_ARCHC))
			node->bounding = _hoops_SRCP->bounding;

#ifdef _hoops_SIIHC
		if (_hoops_SRCP->priority != 0) {
			node->priority = _hoops_SRCP->priority;
			_hoops_AHSIC->_hoops_PHSI |= _hoops_GGPSA | _hoops_CCHGP;
		}
#endif

		if (_hoops_GPRIC) {
			node->_hoops_RRHH |= _hoops_IACHC;

			_hoops_PIGRA	_hoops_PCGS;
			_hoops_PIGRA	_hoops_RGCAA;

			_hoops_RSAI (locks, _hoops_PIGRA, &_hoops_PCGS);
			_hoops_RSAI (locks, _hoops_PIGRA, &_hoops_RGCAA);

			Attribute *		_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;

			if (_hoops_ASGPR != null) do {
				if (_hoops_ASGPR->type > HK_RENDERING_OPTIONS)
					break;
				if (_hoops_ASGPR->type == HK_RENDERING_OPTIONS) {
					_hoops_RHAIR const	*	_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_ASGPR;

					if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA)) {
						_hoops_PIGRA	_hoops_CIIAA;

						/* _hoops_PA _hoops_HSGRA _hoops_HRGR _hoops_HCAGR _hoops_ASIAA _hoops_HCIAA */
						_hoops_RSAI (&_hoops_AHAIR->locks->normal.mask, _hoops_PIGRA, &_hoops_CIIAA);
						if (0 /* _hoops_PCIRA _hoops_AAHS _hoops_PSIAA _hoops_RPSI _hoops_AAHS */)
							_hoops_HSIAA (&_hoops_CIIAA, &_hoops_PCGS, sizeof (_hoops_PIGRA));

						/* _hoops_HASC _hoops_CCAH _hoops_AAHS _hoops_HRP */
						_hoops_HSIAA (&_hoops_PCGS, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
						_hoops_ISIAA (&_hoops_PCGS, &_hoops_AHAIR->locks->normal.value, sizeof (_hoops_PIGRA));

						/* _hoops_IH _hoops_IRGH _hoops_HCGC _hoops_ARP _hoops_RGR _hoops_IS _hoops_SRCH _hoops_CSIAA '_hoops_PCPAR _hoops_HIH _hoops_HCIAA _hoops_ASIAA' */
						_hoops_RSAI (&_hoops_PCGS, _hoops_PIGRA, &_hoops_RGCAA);
						_hoops_HSIAA (&_hoops_RGCAA, &_hoops_CIIAA, sizeof (_hoops_PIGRA));
						break;
					}
				}
			} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

			if (_hoops_SRCP->_hoops_IPPGR) {
				if (BIT (_hoops_PIHRC, _hoops_SAGIC)) {
					node->_hoops_IPPGR = HI_Clone_Attributes (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCP->_hoops_IPPGR, node, true, null);
					node->_hoops_IPPGR->backlink = &node->_hoops_IPPGR;

					_hoops_ASGPR = node->_hoops_IPPGR;
					do {
						if (_hoops_ASGPR->type == HK_STYLE) {
							Style const *		s = (Style const *)_hoops_ASGPR;

							if (s->_hoops_IGRPR != null) {
								_hoops_ACHR			_hoops_RCGC = s->_hoops_IGRPR->_hoops_RCGC & _hoops_APHGP;

								if (!ALLBITS (node->_hoops_RCGC, _hoops_RCGC))
									HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, node, _hoops_RCGC);
							}
						}
						else
							break;
					} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
				}
				else {
					_hoops_IGRIC (_hoops_ARCAR, node, null, _hoops_SRCP->_hoops_IPPGR, &_hoops_RGCAA);

					_hoops_ASGPR = node->_hoops_IPPGR;

					if (_hoops_ASGPR != null) do {
						if (_hoops_ASGPR->type > HK_RENDERING_OPTIONS)
							break;
						if (_hoops_ASGPR->type == HK_RENDERING_OPTIONS) {
							_hoops_RHAIR const	*	_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_ASGPR;

							if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA)) {
								_hoops_ISIAA (&_hoops_PCGS, &_hoops_AHAIR->locks->normal.value, sizeof (_hoops_PIGRA));
								break;
							}
						}
					} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
				}
			}

			if (node->_hoops_IPPGR != null) {
				Attribute *		_hoops_ASGPR = node->_hoops_IPPGR;

				do {
					if (_hoops_ASGPR->type >= _hoops_CPPIR) {
						if (_hoops_ASGPR->type == _hoops_CPPIR) {
							if (conditions == null) {
								conditions = (_hoops_SPPIR *)_hoops_ASGPR;
								_hoops_PRRH (conditions);
							}
							else {
								_hoops_SPPIR const *		_hoops_RSSPH = (_hoops_SPPIR const *)_hoops_ASGPR;
								int						size = _hoops_RSSPH->count * sizeof (unsigned int);
								_hoops_SPPIR *			_hoops_CHSIC;
								int						_hoops_IRCAA;

								if ((_hoops_IRCAA = HOOPS_WORLD->_hoops_AGCAA / 32) == 0)
									_hoops_IRCAA = 1;

								ZALLOC (_hoops_CHSIC, _hoops_SPPIR);
								_hoops_CHSIC->type = _hoops_CPPIR;
								_hoops_CHSIC->_hoops_HIHI = 1;

								ZALLOC_ARRAY (_hoops_CHSIC->_hoops_SGCAA, _hoops_IRCAA, unsigned int);
								ZALLOC_ARRAY (_hoops_CHSIC->values, _hoops_IRCAA, unsigned int);

								_hoops_AIGA (conditions->_hoops_SGCAA, conditions->count, unsigned int, _hoops_CHSIC->_hoops_SGCAA);
								_hoops_AIGA (conditions->values, conditions->count, unsigned int, _hoops_CHSIC->values);

								_hoops_ISIAA (_hoops_CHSIC->_hoops_SGCAA, _hoops_RSSPH->_hoops_SGCAA, size);
								_hoops_HSIAA (_hoops_CHSIC->values, _hoops_RSSPH->_hoops_SGCAA, size);
								_hoops_ISIAA (_hoops_CHSIC->values, _hoops_RSSPH->values, size);

								for (int i=0; i<_hoops_CHSIC->count; i++) {
									unsigned int	mask = _hoops_CHSIC->_hoops_SGCAA[i];
									int				index = i * 32;

									while (mask != 0) {
										if ((mask & 1) != 0)
											_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[index]);

										mask >>= 1;
										++index;
									}
								}

								_hoops_HPRH (conditions);
								conditions = _hoops_CHSIC;
							}
						}
						break;
					}
				} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
			}

			/* _hoops_PHHIP _hoops_HRGR _hoops_RH _hoops_SRRPR _hoops_IIGR _hoops_IRS _hoops_CCAH _hoops_HHIS */
			_hoops_CPSIC(_hoops_ARCAR, node, _hoops_SRCP, &_hoops_PCGS, conditions);
			goto _hoops_APRIC;
		}

		if (direct) {
			_hoops_PARIC = null;
			direct = false;
		}

		if (BIT (_hoops_PIHRC, _hoops_IAGIC)) {
			if (!ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_IRHGP))
				goto _hoops_APRIC;

			if (_hoops_PARIC)
				_hoops_IGRIC(_hoops_ARCAR, node, _hoops_PARIC, null);

			_hoops_CRCP	*	where = node;

			_hoops_PGRPR *	include;
			ZALLOC (include, _hoops_PGRPR);
			include->_hoops_RRHH = _hoops_HPAPA;

			if (BIT (_hoops_PIHRC, _hoops_GPGIC)) {
				include->_hoops_RRHH |= _hoops_GPCHC;

				where = _hoops_HASHC(_hoops_ARCAR, node, "invisible include");

				_hoops_IGRIC(_hoops_ARCAR, where, _hoops_SRCP->_hoops_IPPGR, null);

				Attribute *	_hoops_ASGPR = where->_hoops_IPPGR;

				do {
					Attribute *	next = _hoops_ASGPR->next;

					if (_hoops_ASGPR->type != HK_VISIBILITY) {
						_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_ASGPR);
						_hoops_HPRH (_hoops_ASGPR);
					}

					_hoops_ASGPR = next;
				} while (_hoops_ASGPR != null);
			}

			include->type = _hoops_AGRPR;
			include->_hoops_HIHI = 1;
			include->owner = where;
			include->key = _hoops_AIRIR (include);
			include->_hoops_CPGPR = _hoops_HCHPA;

			_hoops_CPAPA (_hoops_ARCAR->_hoops_RIGC, include, where);

			include->_hoops_IGRPR = _hoops_SRCP;
			_hoops_PRRH (_hoops_SRCP);
			_hoops_SPAPA(_hoops_ARCAR->_hoops_RIGC, include, _hoops_SRCP);

			HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, where, _hoops_SRCP->_hoops_RCGC);

			goto _hoops_APRIC;
		}

		if (_hoops_SRCP->_hoops_IPPGR || _hoops_PARIC)
			_hoops_IGRIC(_hoops_ARCAR, node, _hoops_PARIC, _hoops_SRCP->_hoops_IPPGR, locks);

		if (_hoops_SRCP->geometry != null)
			_hoops_IGPIC (_hoops_ARCAR, node, _hoops_SRCP);
	}

	/* _hoops_SIGPA _hoops_SHSC _hoops_SICA _hoops_RPP _hoops_ISAP _hoops_SIGC */
	if (!ANYBIT(_hoops_PIHRC, _hoops_SAGIC)) {
		Attribute const *		_hoops_HPHCR = null;

		if (BIT(locks->_hoops_IPPGR, (1 << HK_VISIBILITY)) && !BIT (_hoops_SRCP->_hoops_RCGC, _hoops_RHHGP)) {
			_hoops_ACHR			_hoops_SHSIC = 0;

			_hoops_HPHCR = _hoops_RHSIC;

			while (_hoops_HPHCR && _hoops_HPHCR->type < HK_VISIBILITY)
				_hoops_HPHCR = _hoops_HPHCR->next;

			if (_hoops_HPHCR && _hoops_HPHCR->type == HK_VISIBILITY) {
				_hoops_RSAIR const *		vis = (_hoops_RSAIR const *)_hoops_HPHCR;

				_hoops_SHSIC = locks->_hoops_RGP & (vis->mask & ~vis->value);

				if (ALLBITS(_hoops_SHSIC, _hoops_SRCP->_hoops_RCGC & _hoops_IRHGP)) {
					_hoops_ARCAR->_hoops_CCCHC->LookupItem(node->owner, &_hoops_CCCHC);
					if (_hoops_CCCHC != null) {
						if (_hoops_CCCHC->_hoops_IICHC._hoops_AICHC == node)
							_hoops_CCCHC->_hoops_IICHC._hoops_AICHC = _hoops_CCCHC->_hoops_IICHC._hoops_AICHC->next;
					}

					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC, node);
					HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)node);
					_hoops_HPRH(node);

					node = tree;
					_hoops_PIHRC = 0;

					goto _hoops_APRIC;
				}
			}
		}

		_hoops_HPHCR = node->_hoops_IPPGR;

		while (_hoops_HPHCR && _hoops_HPHCR->type < HK_VISIBILITY)
			_hoops_HPHCR = _hoops_HPHCR->next;

		if (_hoops_HPHCR && _hoops_HPHCR->type == HK_VISIBILITY) {
			_hoops_RSAIR const *		vis = (_hoops_RSAIR const *)_hoops_HPHCR;

			if (!ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_APHGP|_hoops_HPHGP) &&
				(/*_hoops_SHAAA->_hoops_PISH == _hoops_GISIC && _hoops_SHAAA->_hoops_PIRA == 0 ||*/
				 !ANYBIT(vis->mask&vis->value|~vis->mask, _hoops_SRCP->_hoops_RCGC&_hoops_IRHGP) &&
				 (!BIT (_hoops_SRCP->_hoops_RCGC, T_EDGES) || !ANYBIT (vis->mask&vis->value, T_ANY_EDGE))) &&
				 (_hoops_SRCP->geometry != null || _hoops_SRCP->_hoops_RGRPR != null)) {

				// _hoops_RAARH _hoops_SR _hoops_RISIC _hoops_PPR _hoops_PGHPR _hoops_GIIS, _hoops_HIH _hoops_SR _hoops_PAH'_hoops_RA _hoops_SHH _hoops_RCRR _hoops_AHCA _hoops_HPRC _hoops_GHHS
				// _hoops_PCPAR _hoops_GPP _hoops_HPGR _hoops_IRS _hoops_PHPA _hoops_PAPA, _hoops_HIS _hoops_SR _hoops_PGHA _hoops_GAR _hoops_RPP _hoops_SR _hoops_RAARH _hoops_CIIHP _hoops_AISIC,
				// _hoops_AHSAR _hoops_SGS _hoops_SR _hoops_GRHP _hoops_RH _hoops_HPRC _hoops_IS _hoops_HPIHR _hoops_ICHRR-_hoops_AACC _hoops_RH _hoops_GSSR _hoops_PGSA _hoops_PAGIR

				if (node->_hoops_IPPGR) {
					Attribute *		_hoops_ASGPR = node->_hoops_IPPGR;

					do {
						Attribute *		next = _hoops_ASGPR->next;

						if (_hoops_ASGPR->type != HK_VISIBILITY) {
							_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,_hoops_ASGPR);
							_hoops_HPRH (_hoops_ASGPR);
						}

						_hoops_ASGPR = next;
					} while (_hoops_ASGPR != null);
				}

				Attribute *		_hoops_RGIIC = node->_hoops_IPPGR;

				if (_hoops_RGIIC != null)
					_hoops_CIGPR(_hoops_ARCAR->_hoops_RIGC, _hoops_RGIIC);

				_hoops_IGRIC(_hoops_ARCAR, node, _hoops_PARIC, _hoops_RGIIC);

				if (_hoops_RGIIC)
					_hoops_HPRH (_hoops_RGIIC);

				Geometry *		geometry;
				_hoops_PGRPR *		include;

				while ((geometry = node->geometry) != null) {
					_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC,geometry);
					_hoops_HPRH (geometry);
				}

				ZALLOC (include, _hoops_PGRPR);
				include->_hoops_RRHH = _hoops_HPAPA|_hoops_GPCHC;
				include->type = _hoops_AGRPR;
				include->_hoops_HIHI = 1;
				include->owner = node;
				include->key = _hoops_AIRIR (include);
				include->_hoops_CPGPR = _hoops_HCHPA;

				_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, include, node);

				include->_hoops_IGRPR = _hoops_SRCP;
				_hoops_PRRH (_hoops_SRCP);
				_hoops_SPAPA(_hoops_ARCAR->_hoops_RIGC, include, _hoops_SRCP);

				HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, node, _hoops_SRCP->_hoops_RCGC);

				_hoops_PIHRC |= _hoops_IAGIC;
				goto _hoops_APRIC;
			}
		}
	}

	if (node->_hoops_IPPGR != null) {
		Attribute *		_hoops_ASGPR = node->_hoops_IPPGR;

		do {
			if (_hoops_ASGPR->type >= _hoops_CPPIR) {
				if (_hoops_ASGPR->type == _hoops_CPPIR) {
					if (conditions == null) {
						conditions = (_hoops_SPPIR *)_hoops_ASGPR;
						_hoops_PRRH (conditions);
					}
					else {
						_hoops_SPPIR const *		_hoops_RSSPH = (_hoops_SPPIR const *)_hoops_ASGPR;
						int						size = _hoops_RSSPH->count * sizeof (unsigned int);
						_hoops_SPPIR *			_hoops_CHSIC;
						int						_hoops_IRCAA;

						if ((_hoops_IRCAA = HOOPS_WORLD->_hoops_AGCAA / 32) == 0)
							_hoops_IRCAA = 1;

						ZALLOC (_hoops_CHSIC, _hoops_SPPIR);
						_hoops_CHSIC->type = _hoops_CPPIR;
						_hoops_CHSIC->_hoops_HIHI = 1;

						ZALLOC_ARRAY (_hoops_CHSIC->_hoops_SGCAA, _hoops_IRCAA, unsigned int);
						ZALLOC_ARRAY (_hoops_CHSIC->values, _hoops_IRCAA, unsigned int);
						_hoops_CHSIC->count = _hoops_IRCAA;

						_hoops_AIGA (conditions->_hoops_SGCAA, conditions->count, unsigned int, _hoops_CHSIC->_hoops_SGCAA);
						_hoops_AIGA (conditions->values, conditions->count, unsigned int, _hoops_CHSIC->values);

						_hoops_ISIAA (_hoops_CHSIC->_hoops_SGCAA, _hoops_RSSPH->_hoops_SGCAA, size);
						_hoops_HSIAA (_hoops_CHSIC->values, _hoops_RSSPH->_hoops_SGCAA, size);
						_hoops_ISIAA (_hoops_CHSIC->values, _hoops_RSSPH->values, size);

						for (int i=0; i<_hoops_CHSIC->count; i++) {
							unsigned int	mask = _hoops_CHSIC->_hoops_SGCAA[i];
							int				index = i * 32;

							while (mask != 0) {
								if ((mask & 1) != 0)
									_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[index]);

								mask >>= 1;
								++index;
							}
						}

						_hoops_HPRH (conditions);
						conditions = _hoops_CHSIC;
					}
				}
				break;
			}
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
	}

	Subsegment const *	_hoops_GIPIA;
	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_GIPIA->type == _hoops_AGRPR) {
			_hoops_PGRPR const *		inc = (_hoops_PGRPR const *)_hoops_GIPIA;
			_hoops_HGGIC			t = _hoops_IRGIC (inc->condition, conditions);

			if (t == _hoops_CGGIC)
				_hoops_SRCP = inc->_hoops_IGRPR;
			else {
				if (t == _hoops_SGGIC) {
					_hoops_PGRPR *		include;

					ZALLOC (include, _hoops_PGRPR);
					include->_hoops_RRHH = _hoops_HPAPA;
					include->type = _hoops_AGRPR;
					include->_hoops_HIHI = 1;
					include->owner = node;
					include->key = _hoops_AIRIR (include);
					include->_hoops_CPGPR = _hoops_HCHPA;

					HI_Copy_Conditional (&inc->condition, &include->condition);

					include->priority = inc->priority;

					_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, include, node);

					include->_hoops_IGRPR = inc->_hoops_IGRPR;
					_hoops_PRRH (inc->_hoops_IGRPR);
					_hoops_SPAPA(_hoops_ARCAR->_hoops_RIGC, include, inc->_hoops_IGRPR);

					HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, node, inc->_hoops_IGRPR->_hoops_RCGC);

					_hoops_PIHRC |= _hoops_IAGIC;
				}
				continue;
			}
		}
		else
			_hoops_SRCP = (_hoops_CRCP const *)_hoops_GIPIA;

		if (_hoops_IARIC || _hoops_GIPIA->next == null) {
			if (!_hoops_IARIC) {
				_hoops_CHCHC *	_hoops_CCGIC;
				POOL_ZALLOC (_hoops_CCGIC, _hoops_CHCHC, _hoops_ARCAR->memory_pool);
				_hoops_CCGIC->segment = _hoops_GIPIA->owner;
				_hoops_CCGIC->node = node;
				_hoops_CCGIC->_hoops_PIHRC = _hoops_PIHRC;
				_hoops_CCGIC->next = _hoops_CARIC;
				_hoops_CARIC = _hoops_CCGIC;
				node->_hoops_PHSI |= _hoops_HIHIC;
			}

			if (_hoops_GIPIA->owner != root)
				direct = false;
			_hoops_PARIC = node->_hoops_IPPGR;
			_hoops_HRSSA = node;

			goto top;
		}
		else {
			node->_hoops_PHSI |= _hoops_HIHIC;
			_hoops_PIHRC |= _hoops_GHSIC (_hoops_ARCAR, tree, node, _hoops_SRCP, node->_hoops_IPPGR, root, direct, locks, conditions) & ~_hoops_SAGIC;
			node->_hoops_PHSI &= ~_hoops_HIHIC;
		}
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);


  _hoops_APRIC:;
	do {
		if (node != tree) {
			if (node->geometry == null &&
				node->_hoops_RGRPR == null &&
				!BIT (node->_hoops_RRHH, _hoops_CACHC) &&
				!ANYBIT (node->_hoops_PHSI, _hoops_SHSIR|_hoops_GIPSA)) {

				_hoops_ARCAR->_hoops_CCCHC->LookupItem(node->owner, &_hoops_CCCHC);
				if (_hoops_CCCHC != null) {
					if (_hoops_CCCHC->_hoops_IICHC._hoops_AICHC == node)
						_hoops_CCCHC->_hoops_IICHC._hoops_AICHC = _hoops_CCCHC->_hoops_IICHC._hoops_AICHC->next;
				}

				_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC, node);
				HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)node);
				_hoops_HPRH (node);
				node = null;
			}
			else {
				node->_hoops_PHSI &= ~_hoops_HIHIC;

				if (node->_hoops_IPPGR != null) {
					Attribute *		_hoops_ASGPR = node->_hoops_IPPGR;

					do {
						if (_hoops_ASGPR->type >= _hoops_CPPIR) {
							if (_hoops_ASGPR->type == _hoops_CPPIR) {
								if (!BIT (_hoops_PIHRC, _hoops_APGIC) ||
									!_hoops_RAGIC (node, (_hoops_SPPIR const *)_hoops_ASGPR)) {
									_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC, _hoops_ASGPR);
									HI_Disentangle (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_ASGPR);
									_hoops_HPRH (_hoops_ASGPR);
								}
							}
							break;
						}
					} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
				}
			}
		}

		if (_hoops_CARIC != null) {
			_hoops_CHCHC *	_hoops_CCGIC = _hoops_CARIC;
			_hoops_SRCP = _hoops_CCGIC->segment;
			node = _hoops_CCGIC->node;
			node->_hoops_PHSI &= ~_hoops_HIHIC;
			_hoops_PIHRC |= _hoops_CCGIC->_hoops_PIHRC;
			_hoops_CARIC = _hoops_CCGIC->next;
			FREE (_hoops_CCGIC, _hoops_CHCHC);
		}
		else
			_hoops_SRCP = null;
	} while (_hoops_SRCP != null);

	if (conditions != null)
		_hoops_HPRH (conditions);

	return _hoops_PIHRC;
}


local void _hoops_PISIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				tree,
	_hoops_PICHC *			_hoops_ASCIA)
{
	float _hoops_GICPA[_hoops_SICHC];
	int _hoops_HISIC = 0;

	for (int i=0; i<_hoops_SICHC; i++) {
		_hoops_HICHC *	_hoops_APSIC = _hoops_ASCIA->_hoops_HGASH[i];

		if (_hoops_APSIC != null) {
			ASSERT(_hoops_APSIC->_hoops_SRCP->_hoops_IPPGR == null);

			if (_hoops_APSIC->_hoops_ASCIA)
				_hoops_PISIC (_hoops_ARCAR, tree, _hoops_APSIC->_hoops_ASCIA);

			_hoops_HISIC++;

			if (_hoops_APSIC->_hoops_IICHC._hoops_RICHC > 0)
				_hoops_CIHIC (_hoops_ARCAR, _hoops_APSIC->_hoops_SRCP, 1, &_hoops_APSIC->_hoops_IICHC, false);

			_hoops_GICPA[i] = _hoops_PHHIC(_hoops_ARCAR, _hoops_APSIC->_hoops_SRCP, _hoops_RHHIC);
		}
		else
			_hoops_GICPA[i] = 0.0f;
	}

	// _hoops_HASC _hoops_PPR _hoops_HAIHR _hoops_IISIC

	for (int i=0; i<_hoops_SICHC; i++) {
		_hoops_HICHC *	_hoops_APSIC = _hoops_ASCIA->_hoops_HGASH[i];

		if (_hoops_APSIC != null) {
			if (_hoops_GICPA[i] < 1.0f)
				_hoops_APSIC->_hoops_SRCP->_hoops_RRHH &= ~_hoops_HACHC;
#if 1
			else if (_hoops_APSIC->_hoops_SRCP->owner != tree) {
				_hoops_CIGPR(_hoops_ARCAR->_hoops_RIGC, _hoops_APSIC->_hoops_SRCP);
				_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_APSIC->_hoops_SRCP, tree);
				_hoops_APSIC->_hoops_SRCP->owner = tree;
			}
#endif
			FREE(_hoops_APSIC, _hoops_HICHC);
		}
	}

	FREE(_hoops_ASCIA, _hoops_PICHC);
}

local void _hoops_CISIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP)
{
	Subsegment *			_hoops_GIPIA;
	Subsegment *			_hoops_HARIC;

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_HARIC = _hoops_GIPIA->next;

		if (_hoops_GIPIA->type == _hoops_IRCP &&
			!ANYBIT(_hoops_GIPIA->_hoops_RRHH, _hoops_PACHC|_hoops_CACHC)) {
			_hoops_CISIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA);
		}
	} while ((_hoops_GIPIA = _hoops_HARIC) != null);

	ASSERT(!BIT(_hoops_SRCP->_hoops_PHSI, _hoops_HIHIC));

	_hoops_ACCHC * _hoops_CCCHC;
	_hoops_ARCAR->_hoops_CCCHC->RemoveItem(_hoops_SRCP, &_hoops_CCCHC);

	if (_hoops_CCCHC != null) {
		if (_hoops_CCCHC->_hoops_ASCIA != null) {
			_hoops_PISIC (_hoops_ARCAR, _hoops_SRCP, _hoops_CCCHC->_hoops_ASCIA);
		}
		else {
			if (_hoops_CCCHC->_hoops_IICHC._hoops_RICHC > 0)
				_hoops_CIHIC (_hoops_ARCAR, _hoops_SRCP, 1, &_hoops_CCCHC->_hoops_IICHC, false);
		}

		delete _hoops_CCCHC;
	}

	_hoops_SRCP->bounding = null;
}


local bool _hoops_SISIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP,
	bool				_hoops_HCGIC,
	_hoops_GHAIR **		_hoops_GCSIC=null)
{
	Subsegment *		_hoops_GIPIA;
	Subsegment *		_hoops_HARIC;

	bool _hoops_RCSIC = false;
	bool _hoops_ACSIC = false;

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_GIPIA->type == _hoops_IRCP) {
			if ((_hoops_HCGIC || !BIT(_hoops_GIPIA->_hoops_RRHH, _hoops_PACHC))) {
				_hoops_GHAIR * current;

				if (_hoops_SISIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA, _hoops_HCGIC, &current))
					_hoops_ACSIC = true;

				if (current != null)
					_hoops_RCSIC = true;
			}
		}
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);


	_hoops_GHAIR *		_hoops_PCSIC = _hoops_RCGIC(_hoops_ARCAR, _hoops_SRCP->_hoops_IPPGR);

	if (_hoops_RCSIC && !BIT(_hoops_SRCP->_hoops_RRHH, _hoops_CACHC)) {
		_hoops_GHAIR *	_hoops_HCSIC = _hoops_GCGIC(_hoops_ARCAR, _hoops_SRCP->_hoops_IPPGR);

		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;
		do {
			_hoops_HARIC = _hoops_GIPIA->next;

			if (_hoops_GIPIA->type == _hoops_IRCP && _hoops_GIPIA->priority == 0) {
				_hoops_GHAIR *	h = _hoops_RCGIC(_hoops_ARCAR, ((_hoops_CRCP*)_hoops_GIPIA)->_hoops_IPPGR);

				if (h != null) {
					_hoops_ACSIC = true;

					_hoops_CRCP *	_hoops_ICSIC = _hoops_HASHC(_hoops_ARCAR, _hoops_SRCP->owner, "defer", 0, 0, &_hoops_SRCP->next);

					_hoops_CIGPR(_hoops_ARCAR->_hoops_RIGC, h);

					if (_hoops_HCSIC != null && _hoops_PCSIC == null) {
						if (!HI_Set_Heuristics (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_ICSIC, h)) {
							ASSERT(0); // _hoops_CGH _hoops_HAR _hoops_IHPS
							FREE (h, _hoops_GHAIR);
						}

						h = null;

						_hoops_ICSIC = _hoops_HASHC(_hoops_ARCAR, _hoops_ICSIC, "defer holder");
					}

					_hoops_ICSIC->_hoops_RRHH |= _hoops_SRCP->_hoops_RRHH & _hoops_PACHC;
					_hoops_ICSIC->priority = _hoops_SRCP->priority;

					_hoops_CIGPR(_hoops_ARCAR->_hoops_RIGC, _hoops_GIPIA);
					_hoops_GIPIA->owner = _hoops_ICSIC;
					_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_GIPIA, _hoops_ICSIC);

					if (_hoops_SRCP->_hoops_IPPGR != null) {
						_hoops_ICSIC->_hoops_IPPGR = HI_Clone_Attributes (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCP->_hoops_IPPGR, _hoops_ICSIC, true, null);
						_hoops_ICSIC->_hoops_IPPGR->backlink = &_hoops_ICSIC->_hoops_IPPGR;

						Attribute const *		_hoops_ASGPR = _hoops_ICSIC->_hoops_IPPGR;

						do switch (_hoops_ASGPR->type) {
							case HK_CAMERA: {
								HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, _hoops_ICSIC, _hoops_PSPCR);
							}	break;

							case HK_VISIBILITY: {
								_hoops_RSAIR const *	vis = (_hoops_RSAIR const *)_hoops_ASGPR;
								_hoops_ACHR			_hoops_RCGC = 0;

								if (ANYBIT (vis->value, _hoops_AAHGP) ||
									(ANYBIT (vis->value, T_CUT_GEOMETRY) &&
									 ANYBIT (vis->_hoops_PRIGA.value, T_FACES|T_LINES)))
									_hoops_RCGC |= _hoops_APHGP;

								if (BIT (vis->value, T_WINDOWS))
									_hoops_RCGC |= _hoops_HPHGP;

								if (!ALLBITS (_hoops_ICSIC->_hoops_RCGC, _hoops_RCGC))
									HI_Propagate_Maybes (_hoops_ARCAR->_hoops_RIGC, _hoops_ICSIC, _hoops_RCGC);
							}	break;
						} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
					}

					if (_hoops_PCSIC != null) {
						_hoops_GHAIR * _hoops_CIIIP = _hoops_RCGIC(_hoops_ARCAR, _hoops_ICSIC->_hoops_IPPGR);
						ASSERT(_hoops_CIIIP != null);

						if (_hoops_CIIIP->_hoops_RRCRP < h->_hoops_RRCRP)
							_hoops_CIIIP->_hoops_RRCRP = h->_hoops_RRCRP;

						if (_hoops_CIIIP->_hoops_ARCRP < h->_hoops_ARCRP)
							_hoops_CIIIP->_hoops_ARCRP = h->_hoops_ARCRP;

						_hoops_HPRH(h);
					}
					else if (h != null) {
						if (!HI_Set_Heuristics (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_ICSIC, h)) {
							ASSERT(0); // _hoops_CGH _hoops_HAR _hoops_IHPS
							FREE (h, _hoops_GHAIR);
						}
					}
				}
			}
		} while ((_hoops_GIPIA = _hoops_HARIC) != null);
	}

	if (_hoops_GCSIC != null)
		*_hoops_GCSIC = _hoops_PCSIC;

	return _hoops_ACSIC;
}

local void _hoops_IIHIC(
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP)
{
	int	_hoops_GSCHC[64];
	int	_hoops_RSCHC = 0;

	_hoops_SCAIC (_hoops_ARCAR, _hoops_SRCP, _hoops_GSCHC, &_hoops_RSCHC);

	/* _hoops_SPS, _hoops_GACHC _hoops_GII _hoops_SPSHI, _hoops_HAGC _hoops_CCAH _hoops_SPSHI _hoops_GAR _hoops_SIGR _hoops_HPGR _hoops_GRR _hoops_HHSPR */
	for (int _hoops_HSCIC=0; _hoops_HSCIC<_hoops_RSCHC; _hoops_HSCIC++) {
		_hoops_ISHIC (_hoops_ARCAR, _hoops_SRCP, 1, _hoops_GSCHC[_hoops_HSCIC], false);
		_hoops_PCGIC (_hoops_ARCAR, _hoops_SRCP, true, false);
	}
}

local void _hoops_CCSIC(
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP)
{
	Subsegment *			_hoops_SIIS;
	Subsegment *			next;

	if ((_hoops_SIIS = _hoops_SRCP->_hoops_RGRPR) != null) do {
		next = _hoops_SIIS->next;
		if (_hoops_SIIS->type == _hoops_IRCP)
			_hoops_CCSIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_SIIS);
	} while ((_hoops_SIIS = next) != null);

	if (BIT(_hoops_SRCP->_hoops_RRHH, _hoops_PACHC))
		_hoops_IIHIC(_hoops_ARCAR, _hoops_SRCP);
}

#if 0
local void _hoops_SCSIC(
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP)
{
	if (_hoops_SRCP->bounding._hoops_HICAR())
		return;

	Subsegment *			_hoops_SIIS;
	Subsegment *			next;

	int count = 0;

	if ((_hoops_SIIS = _hoops_SRCP->_hoops_RGRPR) != null) do {
		next = _hoops_SIIS->next;
		if (_hoops_SIIS->type == _hoops_IRCP) {
			_hoops_GHAIR * h = _hoops_RCGIC(_hoops_ARCAR, _hoops_SRCP->_hoops_IPPGR);
			// _hoops_SIGPA _hoops_GPRR _hoops_PPR _hoops_IGRI _hoops_PISI _hoops_ARAH-_hoops_HHIS
			if (h == null || h->_hoops_RRCRP < _hoops_CHPIC) {
				_hoops_SCSIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_SIIS);
				count++;
			}
		}
	} while ((_hoops_SIIS = next) != null);


	if (BIT(_hoops_SRCP->_hoops_RRHH, _hoops_PACHC) && count > 1) {
		_hoops_PICHC *	_hoops_ASCIA = _hoops_SRSIC(_hoops_ARCAR, &_hoops_SRCP->bounding->cuboid, true);

		_hoops_SIIS = _hoops_SRCP->_hoops_RGRPR;
		_hoops_SRCP->_hoops_RGRPR = null;
		_hoops_SIIS->backlink = &_hoops_SIIS;

		do {
			next = _hoops_SIIS->next;
			if (_hoops_SIIS->type == _hoops_IRCP) {
				_hoops_HICHC * _hoops_APSIC = _hoops_HASIC(_hoops_ARCAR, _hoops_ASCIA, (_hoops_CRCP *)_hoops_SIIS, _hoops_SRCP, 0, null, true);
				ASSERT(_hoops_APSIC->_hoops_SRCP != null);
				_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_SIIS, _hoops_APSIC->_hoops_SRCP);
				_hoops_SIIS->owner = _hoops_APSIC->_hoops_SRCP;
				// _hoops_IASC _hoops_PPR _hoops_SGHGP _hoops_GSSIC. _hoops_AHGGR?
				if (_hoops_APSIC->_hoops_SRCP->bounding._hoops_HICAR())
					_hoops_APSIC->_hoops_SRCP->bounding = ((_hoops_CRCP*)_hoops_SIIS)->bounding;
				else
					_hoops_APSIC->_hoops_SRCP->bounding->Merge(((_hoops_CRCP*)_hoops_SIIS)->bounding);
				_hoops_APSIC->_hoops_SRCP->_hoops_RCGC |= ((_hoops_CRCP*)_hoops_SIIS)->_hoops_RCGC;
			}
			else {
				_hoops_CIGPR(_hoops_ARCAR->_hoops_RIGC, _hoops_SIIS);
				_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_SIIS, _hoops_SRCP);
			}
		} while ((_hoops_SIIS = next) != null);

		_hoops_PISIC (_hoops_ARCAR, _hoops_SRCP, _hoops_ASCIA);
	}
}
#endif

local bool _hoops_RSSIC (
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP)
{
	Subsegment *			_hoops_GIPIA;
	Subsegment *			_hoops_HARIC;

	bool _hoops_ASSIC = false;

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_HARIC = _hoops_GIPIA->next;

		if (_hoops_GIPIA->type == _hoops_IRCP) {
			_hoops_GHAIR * h = _hoops_RCGIC(_hoops_ARCAR, ((_hoops_CRCP*)_hoops_GIPIA)->_hoops_IPPGR);

			// _hoops_SIGPA _hoops_GPRR _hoops_PPR _hoops_IGRI _hoops_PISI _hoops_ARAH-_hoops_HHIS
			if (h == null) {
				if (_hoops_RSSIC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_GIPIA))
					_hoops_ASSIC = true;
			}
		}
	} while ((_hoops_GIPIA = _hoops_HARIC) != null);

#if 0
	if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "-- 110951")) {
		_hoops_ARCAR=_hoops_ARCAR;
	}
#endif

	if (!_hoops_ASSIC &&
		!BIT(_hoops_SRCP->_hoops_RRHH, _hoops_CACHC)) {

		_hoops_SSGI * c = _hoops_ACGIC(_hoops_ARCAR, _hoops_SRCP->_hoops_IPPGR);

		if (c != null) {
			_hoops_ACSGA const *	colors = c->colors;

			while (colors != null) {
				if (colors->type == _hoops_GIGRA) {
					_hoops_HCSGA const *	_hoops_ICSGA = (_hoops_HCSGA const *)colors;

					if (_hoops_RIRGR(_hoops_ICSGA->_hoops_ISHIR)) {
						_hoops_CRCP *	_hoops_CSPIC = _hoops_HASHC(_hoops_ARCAR, _hoops_SRCP->owner, "defer trans");

						_hoops_GHAIR *	heuristics;
						ZALLOC (heuristics, _hoops_GHAIR);
						heuristics->mask |= _hoops_APIRP;
						heuristics->value |= _hoops_APIRP;
						heuristics->_hoops_RRCRP = _hoops_SHPIC;

						if (!HI_Set_Heuristics (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_CSPIC, heuristics)) {
							ASSERT(0); // _hoops_CGH _hoops_HAR _hoops_IHPS
							FREE (heuristics, _hoops_GHAIR);
						}

						_hoops_CIGPR (_hoops_ARCAR->_hoops_RIGC, _hoops_SRCP);
						_hoops_SRCP->owner = _hoops_CSPIC;
						_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, (Subsegment*)_hoops_SRCP, _hoops_CSPIC);
						return false;
					}
				}

				colors = colors->next;
			}
			_hoops_ASSIC = true;
		}
	}

	return _hoops_ASSIC;
}

#if 0
local bool _hoops_PSSIC(
	_hoops_ICCHC *		_hoops_ARCAR,
	_hoops_CRCP *				_hoops_SRCP)
{
	Subsegment *	_hoops_SIIS;
	Subsegment *	next;

	if ((_hoops_SIIS = _hoops_SRCP->_hoops_RGRPR) != null) do {
		next = _hoops_SIIS->next;

		if (_hoops_SIIS->type == _hoops_IRCP) {
			_hoops_CRCP *		_hoops_GIPIA = (_hoops_CRCP *)_hoops_SIIS;
			_hoops_GHAIR *	h = _hoops_RCGIC(_hoops_ARCAR, _hoops_GIPIA->_hoops_IPPGR);

			if (h == null && _hoops_PSSIC (_hoops_ARCAR, _hoops_GIPIA))
				_hoops_ARCAR->_hoops_GGRHH->InsertItem(_hoops_SRCP);
		}
	} while ((_hoops_SIIS = next) != null);

	if (!ANYBIT(_hoops_SRCP->_hoops_RRHH, _hoops_PACHC|_hoops_CACHC))
		return false;

	int count = 0;

	if ((_hoops_SIIS = _hoops_SRCP->_hoops_RGRPR) != null) do {
		next = _hoops_SIIS->next;
		if (_hoops_SIIS->type == _hoops_IRCP) {
			_hoops_CRCP *	_hoops_GIPIA = (_hoops_CRCP *)_hoops_SIIS;

			if (!_hoops_GIPIA->bounding._hoops_HICAR()) {
				_hoops_GHAIR * h = _hoops_RCGIC(_hoops_ARCAR, _hoops_GIPIA->_hoops_IPPGR);
				if (!BIT (_hoops_GIPIA->_hoops_RRHH, _hoops_PACHC) &&
					_hoops_ARCAR->_hoops_GGRHH->LookupItem(_hoops_GIPIA) != VHASH_STATUS_SUCCESS &&
					(/*_hoops_GGHR == _hoops_IRAP ||*/ h != null && h->_hoops_RRCRP < _hoops_CHPIC))
					count++;
			}
		}
	} while ((_hoops_SIIS = next) != null);


	if (count > 1/* && _hoops_HHGP > 0*/) {
		_hoops_CRCP * _hoops_HSSIC = _hoops_HASHC(_hoops_ARCAR, _hoops_SRCP, "weights", _hoops_PACHC);

		_hoops_HSSIC->bounding = _hoops_SRCP->bounding;
		_hoops_HSSIC->_hoops_RCGC = _hoops_SRCP->_hoops_RCGC;

		if ((_hoops_SIIS = _hoops_SRCP->_hoops_RGRPR) != null) do {
			next = _hoops_SIIS->next;
			if (_hoops_SIIS != _hoops_HSSIC) {
				_hoops_CRCP *	_hoops_GIPIA = (_hoops_CRCP *)_hoops_SIIS;

				if (!_hoops_GIPIA->bounding._hoops_HICAR()) {
					_hoops_GHAIR * h = _hoops_RCGIC(_hoops_ARCAR, _hoops_GIPIA->_hoops_IPPGR);
					if (!BIT (_hoops_GIPIA->_hoops_RRHH, _hoops_PACHC) &&
						_hoops_ARCAR->_hoops_GGRHH->LookupItem(_hoops_GIPIA) != VHASH_STATUS_SUCCESS &&
						(/*_hoops_GGHR == _hoops_IRAP ||*/ h != null && h->_hoops_RRCRP < _hoops_CHPIC)) {

						_hoops_CRCP *	_hoops_ISSIC = _hoops_HASHC(_hoops_ARCAR, _hoops_HSSIC, "subweights", _hoops_PACHC);

						_hoops_ISSIC->bounding = _hoops_GIPIA->bounding;
						_hoops_ISSIC->_hoops_RCGC = _hoops_GIPIA->_hoops_RCGC;

						_hoops_GHAIR *	heuristics;
						ZALLOC (heuristics, _hoops_GHAIR);
						heuristics->mask |= _hoops_IAIRP;
						heuristics->value |= _hoops_IAIRP;

						if (!HI_Set_Heuristics (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_ISSIC, heuristics)) {
							ASSERT(0); // _hoops_CGH _hoops_HAR _hoops_IHPS
							FREE (heuristics, _hoops_GHAIR);
						}

						_hoops_CIGPR(_hoops_ARCAR->_hoops_RIGC, _hoops_SIIS);
						_hoops_SIIS->owner = _hoops_ISSIC;
						_hoops_CPAPA(_hoops_ARCAR->_hoops_RIGC, _hoops_SIIS, _hoops_ISSIC);
					}
				}
			}
		} while ((_hoops_SIIS = next) != null);

		_hoops_GHAIR *	heuristics;
		ZALLOC (heuristics, _hoops_GHAIR);
		heuristics->mask |= _hoops_HAIRP|_hoops_CAIRP;
		heuristics->value |= _hoops_HAIRP|_hoops_CAIRP;

		heuristics->_hoops_CSIRP |= 1<<_hoops_RSIRP;
		heuristics->_hoops_SSIRP[_hoops_RSIRP] = 1.0f;

		//_hoops_SCSHP->_hoops_CSSIC |= 1<<_hoops_SSSIC;
		//_hoops_SCSHP->_hoops_GGGCC[_hoops_SSSIC] = 1.0f;

		heuristics->_hoops_RGCRP = 0;
		heuristics->_hoops_AGCRP = _hoops_CHPIC;

		heuristics->_hoops_GGCRP = 0;

		if (!HI_Set_Heuristics (_hoops_ARCAR->_hoops_RIGC, (_hoops_HPAH *)_hoops_HSSIC, heuristics)) {
			ASSERT(0); // _hoops_CGH _hoops_HAR _hoops_IHPS
			FREE (heuristics, _hoops_GHAIR);
		}
	}

	return true;
}
#endif

#if 0
local void _hoops_RGGCC(
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP)
{
	ASSERT(BIT(_hoops_ARCAR->flags, _hoops_PRCHC));
	ASSERT(BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HIRIR));

	Subsegment *	_hoops_SIIS;

	if ((_hoops_SIIS = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (_hoops_SIIS->type == _hoops_IRCP)
			_hoops_RGGCC (_hoops_ARCAR, (_hoops_CRCP *)_hoops_SIIS);
	} while ((_hoops_SIIS = _hoops_SIIS->next) != null);

	Geometry * geo = _hoops_SRCP->geometry;

	while (geo != null) {
		ASSERT(geo->type == _hoops_AHIP);
		_hoops_ISRSA(_hoops_ARCAR->_hoops_RIGC, (_hoops_PHIP *)geo);
		geo = geo->next;
	}
}
#endif

local void _hoops_CPSIC (
	_hoops_ICCHC *	_hoops_ARCAR,
	_hoops_CRCP *			_hoops_SRCP,
	_hoops_CRCP const *		root,
	_hoops_PIGRA *	locks,
	_hoops_SPPIR *		conditions)
{
	ASSERT(BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HIRIR));
	ASSERT(root);

	bool	_hoops_AGGCC = BIT(_hoops_ARCAR->flags, _hoops_HRCHC);

	if (_hoops_AGGCC) {
		_hoops_ARCAR->flags &= ~_hoops_HRCHC;
		_hoops_ARCAR->_hoops_CCCHC = POOL_NEW(_hoops_ARCAR->memory_pool, _hoops_PCCHC)(_hoops_ARCAR->memory_pool);
	}

	_hoops_PIGRA	_hoops_RGCAA;

	if (locks == null) {
		locks = &_hoops_RGCAA;
		ZERO_STRUCT(locks, _hoops_PIGRA);

		Attribute *	_hoops_ASGPR= _hoops_SRCP->_hoops_IPPGR;

		if (_hoops_ASGPR != null) do {
			if (_hoops_ASGPR->type > HK_RENDERING_OPTIONS)
				break;
			if (_hoops_ASGPR->type == HK_RENDERING_OPTIONS) {
				_hoops_RHAIR const	*	_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_ASGPR;

				if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA))
					_hoops_RSAI (&_hoops_AHAIR->locks->normal.value, _hoops_PIGRA, locks);

				break;
			}
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
	}

	_hoops_SRCP->bounding = root->bounding;
	_hoops_GHSIC (_hoops_ARCAR, _hoops_SRCP, _hoops_SRCP, root, null, root, true, locks, conditions);

	_hoops_CISIC (_hoops_ARCAR, _hoops_SRCP);
	_hoops_SSIIC (_hoops_ARCAR, _hoops_SRCP, false);
	_hoops_PCGIC (_hoops_ARCAR, _hoops_SRCP, true, false);

	if (BIT(_hoops_ARCAR->flags, _hoops_CGCHC)) {
		_hoops_CGPIC(_hoops_ARCAR, _hoops_SRCP, false);
		_hoops_PCGIC (_hoops_ARCAR, _hoops_SRCP, true, false);
	}

	_hoops_IPPIC (_hoops_ARCAR, _hoops_SRCP, false);
	_hoops_PCGIC (_hoops_ARCAR, _hoops_SRCP, true, false);

	_hoops_IIHIC(_hoops_ARCAR, _hoops_SRCP);

	if (_hoops_AGGCC) {
		_hoops_SSIIC (_hoops_ARCAR, _hoops_SRCP, true);

		if (BIT(_hoops_ARCAR->flags, _hoops_SGCHC)) {
			// _hoops_IRHH _hoops_IRS _hoops_CRCC _hoops_CAGH _hoops_IH _hoops_IRGH _hoops_CRPGI
			if (_hoops_SRCP->geometry != null) {
				_hoops_CRCP * _hoops_HRHIC = _hoops_HASHC(_hoops_ARCAR, _hoops_SRCP, "refs", _hoops_HACHC);
				_hoops_SPSHC(_hoops_ARCAR, _hoops_SRCP, _hoops_HRHIC);
			}

			_hoops_RSSIC (_hoops_ARCAR, _hoops_SRCP);
			_hoops_PCGIC (_hoops_ARCAR, _hoops_SRCP, true, true);

			_hoops_AHPIC (_hoops_ARCAR, _hoops_SRCP, null, null, null);
			_hoops_PCGIC (_hoops_ARCAR, _hoops_SRCP, true, true);

			_hoops_SISIC (_hoops_ARCAR, _hoops_SRCP, true);

			ASSERT(!_hoops_SISIC (_hoops_ARCAR, _hoops_SRCP, true));

			_hoops_PGRIC(_hoops_ARCAR, _hoops_SRCP);
			_hoops_CCSIC(_hoops_ARCAR, _hoops_SRCP);
		}

		_hoops_SSPIC (_hoops_ARCAR, _hoops_SRCP);

		_hoops_PCGIC (_hoops_ARCAR, _hoops_SRCP, true, true);

		_hoops_CIHIC (_hoops_ARCAR, _hoops_SRCP, 1, null, true);

		ASSERT(_hoops_SRCP->bounding._hoops_HICAR());

		_hoops_HPRIC (_hoops_SRCP);

		if (BIT(_hoops_ARCAR->flags, _hoops_SGCHC)) {
#if 0
			// _hoops_HAR _hoops_CPSA _hoops_CRSH _hoops_ASRAH _hoops_IH _hoops_HA
			if (BIT(_hoops_ARCAR->flags, _hoops_ARCHC)) {
				//_hoops_PGGCC(_hoops_SAHHH, _hoops_PHHIP);
				_hoops_CHHIC (_hoops_ARCAR, _hoops_SRCP, 1, _hoops_GHHIC|_hoops_AHHIC);
				_hoops_AAHIC (_hoops_ARCAR, _hoops_SRCP);
				ASSERT(_hoops_ARCAR->_hoops_GGRHH->Count() == 0);
				_hoops_PSSIC(_hoops_ARCAR, _hoops_SRCP);
				_hoops_ARCAR->_hoops_GGRHH->Flush();
			}
			else
#endif
			{
				_hoops_CHHIC (_hoops_ARCAR, _hoops_SRCP, 1, _hoops_SPHIC|_hoops_GHHIC);
				_hoops_PAHIC (_hoops_ARCAR, _hoops_SRCP);
			}

			_hoops_PCGIC (_hoops_ARCAR, _hoops_SRCP, false, true);
		}

		if (_hoops_ARCAR->_hoops_CCCHC->Count() > 0)
			_hoops_ARCAR->_hoops_CCCHC->DeleteItems();
		delete _hoops_ARCAR->_hoops_CCCHC;
		_hoops_ARCAR->_hoops_CCCHC = null;

		/* _hoops_HACH _hoops_PHARA _hoops_RIH _hoops_IH (_hoops_APGP) _hoops_RHPA _hoops_SGHC */
		_hoops_SSIIC (_hoops_ARCAR, _hoops_SRCP, true);
	}
}

GLOBAL_FUNCTION _hoops_GSPGR HI_Make_Static_Tree (
	Net_Rendition const &	nr,
	_hoops_CRCP const *			root) {
	_hoops_PGRPR *				include;
	_hoops_CRCP *				_hoops_SRCP;
	_hoops_ICCHC		_hoops_ARCAR;
	_hoops_GSPGR					_hoops_RSPGR, _hoops_ASPGR;
	int						_hoops_AICIP;

	_hoops_RSPGR = HI_What_Time();

	/* _hoops_HHSP _hoops_PAAP _hoops_RGSHA */
	_hoops_AICIP = nr->_hoops_SRA->_hoops_RIGC->flags;
	nr->_hoops_SRA->_hoops_RIGC->flags |= _hoops_RRSCA|_hoops_PGPSA;

	ZALLOC (include, _hoops_PGRPR);
	include->_hoops_HIHI = 1;
	include->type = _hoops_PIRIR;
	include->owner = _hoops_PGRCA(root);
	include->key = _hoops_AIRIR (include);
	include->_hoops_CPGPR = _hoops_HCHPA;

	{
		_hoops_SPAGR			_hoops_GHAGR (root->_hoops_RHAGR, nr->_hoops_SRA->_hoops_RIGC->thread_id);
		_hoops_AHAGR *	_hoops_CSC = HI_Find_Segment_Cache (root);	// _hoops_HASPH _hoops_ASAI _hoops_IIHA _hoops_GPP _hoops_CRAA
		_hoops_CSC->_hoops_RASGP (include);
	}

	ZALLOC (_hoops_SRCP, _hoops_CRCP);
	_hoops_SRCP->_hoops_HIHI = 1;
	_hoops_SRCP->type = _hoops_IRCP;
	_hoops_SRCP->owner = (_hoops_CRCP *)include;
	_hoops_SRCP->key = _hoops_AIRIR (_hoops_SRCP);
	_hoops_SRCP->_hoops_CPGPR = _hoops_HCHPA;
	_hoops_SRCP->_hoops_RRHH = _hoops_CACHC|_hoops_HIRIR;

	include->_hoops_IGRPR = _hoops_SRCP;
	_hoops_SRCP->backlink = (Subsegment **)&include->_hoops_IGRPR;

	{
		_hoops_CRCP const *		start_seg = root;

		if (start_seg->name.length > 0) {
			_hoops_PIRHH (nr->_hoops_SRA->_hoops_RIGC, _hoops_ARCAR._hoops_RGSHC, "%n :-internal static-:", &start_seg->name);
			HI_Copy_Chars_To_Name (_hoops_ARCAR._hoops_RGSHC, &_hoops_SRCP->name);
		}
		else
			HI_Copy_Chars_To_Name ("unnamed :-internal static-:", &_hoops_SRCP->name);
	}


	/* _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SIHGA */

	HOOPS_WORLD->_hoops_AGHGI = 1;//_hoops_IHPR;


	ZERO_STRUCT (&_hoops_ARCAR, _hoops_ICCHC);
	_hoops_ARCAR._hoops_RIGC = nr->_hoops_SRA->_hoops_RIGC;
	_hoops_ARCAR.memory_pool = HI_Create_Memory_Pool(MPF_NONE);
	_hoops_ARCAR.flags = _hoops_PRCHC|_hoops_HRCHC;

	if (BIT(nr->flags, _hoops_HRSHP)) {
		_hoops_ARCAR.flags |= _hoops_IRCHC;
		include->_hoops_RRHH |= _hoops_PSIGP;
	}

	_hoops_ARCAR._hoops_PSCHC = _hoops_RCIHC;
	_hoops_ARCAR._hoops_ASCHC = _hoops_ACIHC;
	_hoops_ARCAR._hoops_HSCHC = _hoops_PCIHC;
	_hoops_ARCAR._hoops_ISCHC = _hoops_HCIHC;
	_hoops_ARCAR._hoops_CSCHC = _hoops_ICIHC;
	_hoops_ARCAR._hoops_SSCHC = _hoops_CCIHC;
	_hoops_ARCAR._hoops_GGSHC = _hoops_SCIHC;
	_hoops_ARCAR._hoops_GGRHH = POOL_NEW(_hoops_ARCAR.memory_pool, _hoops_AAPHP)(_hoops_ARCAR.memory_pool, _hoops_PAPHP);


	if (nr->_hoops_IRR->_hoops_IRCRP == _hoops_HRCRP)
		_hoops_ARCAR.flags |= _hoops_CGCHC|_hoops_SGCHC|_hoops_ARCHC;

	_hoops_CPSIC(&_hoops_ARCAR, _hoops_SRCP, root);

	HOOPS_WORLD->_hoops_AGHGI = 0;//_hoops_RCPP;

	/* _hoops_HSHPC _hoops_SPSHI _hoops_IS _hoops_SGHC, _hoops_GHRHA _hoops_PICAA (_hoops_PSP _hoops_AIRC, _hoops_PSP _hoops_CPAP) _hoops_SGHC */
	_hoops_IGIIC (&_hoops_ARCAR, _hoops_SRCP, root->bounding);

	/* _hoops_PHIH _hoops_PAAP _hoops_RGSHA */
	nr->_hoops_SRA->_hoops_RIGC->flags = _hoops_AICIP;

	delete _hoops_ARCAR._hoops_GGRHH;

#ifdef VALIDATE_MEMORY
	size_t allocated = 0;
	HI_Relinquish_Memory_On_Pool (_hoops_ARCAR.memory_pool);
	HI_Memory_On_Pool(_hoops_ARCAR.memory_pool, &allocated);
	if (allocated > 0) {
		HE_WARNING (HEC_HOOPS_SYSTEM, HES_MEMORY_USAGE, "Memory leak detected in static tree memory pool.");
		HI_Dump_Allocation_Metadata (_hoops_ARCAR.memory_pool, "static tree memory pool");
	}
#endif

	HI_Destroy_Memory_Pool(_hoops_ARCAR.memory_pool);

	_hoops_ASPGR = HI_What_Time();
	return (_hoops_ASPGR - _hoops_RSPGR + 0.001) / _hoops_HSPGR;
}


GLOBAL_FUNCTION void HI_Clean_Static_Tree (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP) {
	_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
	_hoops_AHAGR *			_hoops_CSC = _hoops_SRCP->_hoops_CSC;

	if ((_hoops_CSC = _hoops_SRCP->_hoops_CSC) != null) do {
		_hoops_PGRPR *			st = _hoops_CSC->_hoops_CHICA();

		if (st != null) {
			HI_Disentangle(_hoops_RIGC, (_hoops_HPAH *)st->_hoops_IGRPR);
			_hoops_HPRH (st);
			_hoops_CSC->_hoops_RASGP (null);
		}
	} while ((_hoops_CSC = _hoops_CSC->next) != null);
}

