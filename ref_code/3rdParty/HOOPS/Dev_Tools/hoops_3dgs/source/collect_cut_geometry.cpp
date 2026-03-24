/*
 * Copyright (c) 2000-2003 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.133 2010-12-06 22:05:39 jason Exp $
 */

#include "hoops.h"

#ifndef DISABLE_CUT_GEOMETRY

#include "database.h"
#include "phedron.h"
#include "driver.h"
#include "hversion.h"
#include "adt.h"
#include "hpserror.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hd_proto.h"






struct _hoops_ARHGA {
	Point	points[2];
};

struct _hoops_PRHGA {
	Point *		points;
	int			count;
};

struct _hoops_HRHGA {
	int			point_count;
	Point *		points;
	int			face_list_length;
	int *		face_list;
};

typedef VList<_hoops_ARHGA *> _hoops_IRHGA;
typedef VList<_hoops_PRHGA *> _hoops_CRHGA;
typedef VList<_hoops_HRHGA *> _hoops_SRHGA;
typedef VList<_hoops_IRHGA *> _hoops_GAHGA;

/* _hoops_SPR _hoops_ARP _hoops_IIGR _hoops_CIPH _hoops_IS _hoops_HPPP _hoops_IH _hoops_GRR _hoops_HPPA _hoops_IPPA */
Begin_HOOPS_Namespace
	struct _hoops_RAHGA {
		_hoops_RAHGA *	next;
		int						_hoops_AAHGA;

		_hoops_IRHGA *				_hoops_PICHR;			/* _hoops_PAHGA _hoops_HAHGA _hoops_IAHGA _hoops_IIGR _hoops_APGR */
		_hoops_GAHGA *		_hoops_CAHGA;		/* _hoops_PAHGA _hoops_ISHPR _hoops_IIGR _hoops_SAHGA _hoops_APGR */
		_hoops_CRHGA *			_hoops_GPHGA;		/* _hoops_PAHGA _hoops_APGR _hoops_RPHGA _hoops_GIRP _hoops_CAS _hoops_SSRR */
		_hoops_SRHGA *				faces;			/* _hoops_PAHGA (_hoops_PAHH _hoops_CAHC) _hoops_RGHS _hoops_IS _hoops_SHH _hoops_IGI _hoops_GAR _hoops_RRCPR _hoops_RSSI */

		Net_Rendition			_hoops_APHGA;	/* _hoops_IPP _hoops_SGS _hoops_AIS _hoops_IRS _hoops_HGAGA, _hoops_IRAP _hoops_RPP _hoops_GGSR _hoops_IIGR _hoops_CPSRR */
	};
End_HOOPS_Namespace;



#define _hoops_PPHGA 0
#define _hoops_HPHGA 1
#define _hoops_IPHGA		2
#define _hoops_CPHGA	3
#define _hoops_SPHGA	4

local bool _hoops_GHHGA (_hoops_IRHGA *_hoops_RHHGA, _hoops_GAHGA *_hoops_AHHGA, float tolerance, float _hoops_PHHGA)
{
	_hoops_IRHGA *_hoops_HHHGA;
	_hoops_ARHGA *_hoops_IHHGA, *_hoops_CHHGA, *_hoops_SHHGA, *_hoops_GIHGA, *line;
	float _hoops_RIHGA = tolerance * tolerance;
	float _hoops_AIHGA = _hoops_PHHGA * _hoops_PHHGA;
	float _hoops_ARGCR;
	int _hoops_PIHGA = -1;
	int _hoops_HIHGA, i;
	int _hoops_IIHGA = _hoops_PPHGA;

	_hoops_IHHGA = _hoops_RHHGA->PeekFirst();
	_hoops_CHHGA = _hoops_RHHGA->PeekLast();
	_hoops_HIHGA = _hoops_AHHGA->Count();
	_hoops_AHHGA->ResetCursor();

	int		_hoops_CIHGA = _hoops_RHHGA->Count();

	for (i = 0; i < _hoops_HIHGA; i++) {
		/* _hoops_HGCR _hoops_IRS _hoops_SIHGA */
		_hoops_HHHGA = _hoops_AHHGA->PeekCursor();

		/* _hoops_GCHGA _hoops_IS _hoops_RH _hoops_SPS _hoops_SIHGA */
		_hoops_AHHGA->AdvanceCursor();

		int		_hoops_RCHGA = _hoops_HHHGA->Count();

		if (_hoops_RCHGA == 0)
			continue;

		_hoops_SHHGA = _hoops_HHHGA->PeekFirst();
		_hoops_GIHGA = _hoops_HHHGA->PeekLast();

		int		_hoops_ACHGA = _hoops_AHIA (_hoops_CIHGA, _hoops_RCHGA);

		_hoops_ARGCR = (_hoops_IHHGA->points[0] - _hoops_SHHGA->points[0])._hoops_PPSSR();	/* _hoops_HSPP _hoops_HSPP */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			bool	_hoops_PCHGA = true;
			for (int j=0; j<_hoops_ACHGA; ++j) {
				_hoops_ARHGA const *		a = _hoops_RHHGA->NthItem (j);
				_hoops_ARHGA const *		b = _hoops_HHHGA->NthItem (j);
				if ((a->points[0] - b->points[0])._hoops_PPSSR() > _hoops_AIHGA ||
					(a->points[1] - b->points[1])._hoops_PPSSR() > _hoops_AIHGA) {
					_hoops_PCHGA = false;
					break;
				}
			}
			if (_hoops_PCHGA) {
				if (_hoops_CIHGA <= _hoops_RCHGA) {
					_hoops_ARHGA *			a;
					while ((a = _hoops_RHHGA->RemoveFirst()) != null)
						FREE (a, _hoops_ARHGA);
					delete _hoops_RHHGA;
					return true;
				}
				else {
					_hoops_ARHGA *			b;
					while ((b = _hoops_HHHGA->RemoveFirst()) != null)
						FREE (b, _hoops_ARHGA);
					continue;
				}
			}

			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_HPHGA;
		}

		_hoops_ARGCR = (_hoops_CHHGA->points[1] - _hoops_GIHGA->points[1])._hoops_PPSSR();		/* _hoops_RSGR _hoops_RSGR */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			bool	_hoops_PCHGA = true;
			for (int j=0; j<_hoops_ACHGA; ++j) {
				_hoops_ARHGA const *		a = _hoops_RHHGA->NthItem (_hoops_CIHGA-1-j);
				_hoops_ARHGA const *		b = _hoops_HHHGA->NthItem (_hoops_RCHGA-1-j);
				if ((a->points[0] - b->points[0])._hoops_PPSSR() > _hoops_AIHGA ||
					(a->points[1] - b->points[1])._hoops_PPSSR() > _hoops_AIHGA) {
					_hoops_PCHGA = false;
					break;
				}
			}
			if (_hoops_PCHGA) {
				if (_hoops_CIHGA <= _hoops_RCHGA) {
					_hoops_ARHGA *			a;
					while ((a = _hoops_RHHGA->RemoveFirst()) != null)
						FREE (a, _hoops_ARHGA);
					delete _hoops_RHHGA;
					return true;
				}
				else {
					_hoops_ARHGA *			b;
					while ((b = _hoops_HHHGA->RemoveFirst()) != null)
						FREE (b, _hoops_ARHGA);
					continue;
				}
			}

			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_IPHGA;
		}

		_hoops_ARGCR = (_hoops_CHHGA->points[1] - _hoops_SHHGA->points[0])._hoops_PPSSR();	/* _hoops_RSGR _hoops_HSPP */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			bool	_hoops_PCHGA = true;
			for (int j=0; j<_hoops_ACHGA; ++j) {
				_hoops_ARHGA const *		a = _hoops_RHHGA->NthItem (_hoops_CIHGA-1-j);
				_hoops_ARHGA const *		b = _hoops_HHHGA->NthItem (j);
				if ((a->points[1] - b->points[0])._hoops_PPSSR() > _hoops_AIHGA ||
					(a->points[0] - b->points[1])._hoops_PPSSR() > _hoops_AIHGA) {
					_hoops_PCHGA = false;
					break;
				}
			}
			if (_hoops_PCHGA) {
				if (_hoops_CIHGA <= _hoops_RCHGA) {
					_hoops_ARHGA *			a;
					while ((a = _hoops_RHHGA->RemoveFirst()) != null)
						FREE (a, _hoops_ARHGA);
					delete _hoops_RHHGA;
					return true;
				}
				else {
					_hoops_ARHGA *			b;
					while ((b = _hoops_HHHGA->RemoveFirst()) != null)
						FREE (b, _hoops_ARHGA);
					continue;
				}
			}

			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_CPHGA;
		}

		_hoops_ARGCR = (_hoops_IHHGA->points[0] - _hoops_GIHGA->points[1])._hoops_PPSSR();		/* _hoops_HSPP _hoops_RSGR */
		if (_hoops_ARGCR < _hoops_RIHGA) {
			bool	_hoops_PCHGA = true;
			for (int j=0; j<_hoops_ACHGA; ++j) {
				_hoops_ARHGA const *		a = _hoops_RHHGA->NthItem (j);
				_hoops_ARHGA const *		b = _hoops_HHHGA->NthItem (_hoops_RCHGA-1-j);
				if ((a->points[0] - b->points[1])._hoops_PPSSR() > _hoops_AIHGA ||
					(a->points[1] - b->points[0])._hoops_PPSSR() > _hoops_AIHGA) {
					_hoops_PCHGA = false;
					break;
				}
			}
			if (_hoops_PCHGA) {
				if (_hoops_CIHGA <= _hoops_RCHGA) {
					_hoops_ARHGA *			a;
					while ((a = _hoops_RHHGA->RemoveFirst()) != null)
						FREE (a, _hoops_ARHGA);
					delete _hoops_RHHGA;
					return true;
				}
				else {
					_hoops_ARHGA *			b;
					while ((b = _hoops_HHHGA->RemoveFirst()) != null)
						FREE (b, _hoops_ARHGA);
					continue;
				}
			}

			_hoops_PIHGA = i;
			_hoops_RIHGA = _hoops_ARGCR;
			_hoops_IIHGA = _hoops_SPHGA;
		}
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
				_hoops_HHHGA->AddFirst(line);
			}
		}	break;

		case _hoops_IPHGA: {
			_hoops_RHHGA->Reverse();
			while ((line = _hoops_RHHGA->RemoveFirst()) != null) {
				Swap (line->points[0], line->points[1]);
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


local _hoops_PRHGA *_hoops_GSHGA (_hoops_PRHGA const * in) {
	_hoops_PRHGA *_hoops_PAGR;

	ALLOC (_hoops_PAGR, _hoops_PRHGA);
	_hoops_PAGR->count = in->count;
	_hoops_APRGA(in->points, in->count, Point, _hoops_PAGR->points);
	return _hoops_PAGR;
}




local void _hoops_RSHGA (void) {}


local void _hoops_ASHGA (
	_hoops_ARPA const *						_hoops_SHPA,
	Point const *						_hoops_CARGA,
	Point const *						_hoops_PSHGA,
	Point alter *						result) {
	float									_hoops_HSHGA, _hoops_ISHGA, _hoops_CSHGA;
	float									t, _hoops_SSHGA;

	_hoops_HSHGA = _hoops_PSHGA->x - _hoops_CARGA->x;
	_hoops_ISHGA = _hoops_PSHGA->y - _hoops_CARGA->y;
	_hoops_CSHGA = _hoops_PSHGA->z - _hoops_CARGA->z;

	_hoops_SSHGA = _hoops_HSHGA * _hoops_SHPA->a + _hoops_ISHGA * _hoops_SHPA->b + _hoops_CSHGA * _hoops_SHPA->c;

	if (_hoops_SSHGA == 0.0f)
		t = 1.0f; /* (_hoops_CPPPR _hoops_SSHRR) */
	else
		t = -(_hoops_CARGA->x * _hoops_SHPA->a + _hoops_CARGA->y * _hoops_SHPA->b +
			  _hoops_CARGA->z * _hoops_SHPA->c + _hoops_SHPA->d) / _hoops_SSHGA;

	result->x = _hoops_CARGA->x + t*_hoops_HSHGA;
	result->y = _hoops_CARGA->y + t*_hoops_ISHGA;
	result->z = _hoops_CARGA->z + t*_hoops_CSHGA;
}




local void _hoops_GGIGA (
	Tristrip const *			ts,
	Point const *				points,
	_hoops_ARPA const *  				_hoops_SHPA,
	_hoops_RAHGA *		_hoops_RGIGA,
	float						tolerance,
	bool *						_hoops_AGIGA) {
 	int							_hoops_PHHA = ts->_hoops_PHHA;
	int const *					lengths = ts->lengths;
	int const *					vi = ts->_hoops_AIHA;
	float						_hoops_PGIGA = tolerance * tolerance;

	while (_hoops_PHHA-- > 0) {
		int						length = *lengths++;
		int						_hoops_SICPR = false;
		Point const *			_hoops_HSPI;
		Point const *			_hoops_ISPI;
		Point const *			_hoops_CSPI;
		int						_hoops_HGIGA;
		int						_hoops_IGIGA;
		int						_hoops_CGIGA;
		float					_hoops_SSRP;

		if (length < 0) {
			length = -length;
			_hoops_SICPR = true;
		}

		_hoops_HSPI = &points[*vi++];
		_hoops_SSRP = *_hoops_HSPI * *_hoops_SHPA;
		if (Abs (_hoops_SSRP) < tolerance)
			_hoops_SSRP = 0.0f;
		_hoops_HGIGA = Sign (_hoops_SSRP);
		_hoops_ISPI = &points[*vi++];
		_hoops_SSRP = *_hoops_ISPI * *_hoops_SHPA;
		if (Abs (_hoops_SSRP) < tolerance)
			_hoops_SSRP = 0.0f;
		_hoops_IGIGA = Sign (_hoops_SSRP);
		length -= 2;
		while (length-- > 0) {
			_hoops_CSPI = &points[*vi++];
			_hoops_SSRP = *_hoops_CSPI * *_hoops_SHPA;
			if (Abs (_hoops_SSRP) < tolerance)
				_hoops_SSRP = 0.0f;
			_hoops_CGIGA = Sign (_hoops_SSRP);

			/* _hoops_RPGP & _hoops_AACC _hoops_SCPH, _hoops_ASAC _hoops_AACC _hoops_RPP _hoops_IRPR */
			if (_hoops_HGIGA != _hoops_IGIGA || _hoops_IGIGA != _hoops_CGIGA) {
				Point					_hoops_SGIGA[3];
				int						_hoops_GRIGA = 0;

				if (_hoops_HGIGA != _hoops_IGIGA) {
					if (_hoops_HGIGA == 0)
						_hoops_SGIGA[_hoops_GRIGA++] = *_hoops_HSPI;
					else if (_hoops_IGIGA == 0)
						_hoops_SGIGA[_hoops_GRIGA++] = *_hoops_ISPI;
					else
						_hoops_ASHGA (_hoops_SHPA, _hoops_HSPI, _hoops_ISPI, &_hoops_SGIGA[_hoops_GRIGA++]);
				}
				if (_hoops_HGIGA != _hoops_CGIGA) {
					if (_hoops_HGIGA == 0)
						_hoops_SGIGA[_hoops_GRIGA++] = *_hoops_HSPI;
					else if (_hoops_CGIGA == 0)
						_hoops_SGIGA[_hoops_GRIGA++] = *_hoops_CSPI;
					else
						_hoops_ASHGA (_hoops_SHPA, _hoops_HSPI, _hoops_CSPI, &_hoops_SGIGA[_hoops_GRIGA++]);

					if (_hoops_GRIGA == 2 &&
						(_hoops_SGIGA[1] - _hoops_SGIGA[0])._hoops_PPSSR() < _hoops_PGIGA)
						--_hoops_GRIGA;
				}
				if (_hoops_IGIGA != _hoops_CGIGA) {
					if (_hoops_IGIGA == 0)
						_hoops_SGIGA[_hoops_GRIGA++] = *_hoops_ISPI;
					else if (_hoops_CGIGA == 0)
						_hoops_SGIGA[_hoops_GRIGA++] = *_hoops_CSPI;
					else
						_hoops_ASHGA (_hoops_SHPA, _hoops_ISPI, _hoops_CSPI, &_hoops_SGIGA[_hoops_GRIGA++]);

					if (_hoops_GRIGA == 2 &&
						(_hoops_SGIGA[1] - _hoops_SGIGA[0])._hoops_PPSSR() < _hoops_PGIGA ||
						_hoops_GRIGA == 3 &&
						((_hoops_SGIGA[2] - _hoops_SGIGA[0])._hoops_PPSSR() < _hoops_PGIGA ||
						 (_hoops_SGIGA[2] - _hoops_SGIGA[1])._hoops_PPSSR() < _hoops_PGIGA))
						--_hoops_GRIGA;
				}

				ASSERT (_hoops_GRIGA < 3);

				if (_hoops_GRIGA == 2) {
					/* _hoops_SSPC _hoops_RPP _hoops_SSRS */
					_hoops_RGIGA->_hoops_PICHR->ResetCursor();
					int _hoops_RRIGA = _hoops_RGIGA->_hoops_PICHR->Count();

					for (int i = 0; i < _hoops_RRIGA; i++) {
						_hoops_ARHGA		*test;

						test = _hoops_RGIGA->_hoops_PICHR->PeekCursor();

						if ((_hoops_SGIGA[0] - test->points[0])._hoops_PPSSR() < _hoops_PGIGA &&
							(_hoops_SGIGA[1] - test->points[1])._hoops_PPSSR() < _hoops_PGIGA ||
							(_hoops_SGIGA[0] - test->points[1])._hoops_PPSSR() < _hoops_PGIGA &&
							(_hoops_SGIGA[1] - test->points[0])._hoops_PPSSR() < _hoops_PGIGA) {
							_hoops_GRIGA = 0;
							break;
						}

						/* _hoops_GCHGA _hoops_IS _hoops_RH _hoops_SPS _hoops_SIHGA */
						_hoops_RGIGA->_hoops_PICHR->AdvanceCursor();
					}

					if (_hoops_GRIGA != 0) {
						_hoops_ARHGA *				line;
						ALLOC (line, _hoops_ARHGA);
						line->points[0] = _hoops_SGIGA[0];
						line->points[1] = _hoops_SGIGA[1];

						_hoops_RGIGA->_hoops_PICHR->AddFirst(line);
						*_hoops_AGIGA = true;
					}
				}
			}

			if (!_hoops_SICPR) {
				_hoops_HSPI = _hoops_ISPI;
				_hoops_HGIGA = _hoops_IGIGA;
			}
			_hoops_ISPI = _hoops_CSPI;
			_hoops_IGIGA = _hoops_CGIGA;
		}
	}
}

local void _hoops_ARIGA (
	Net_Rendition const & 			nr,
	Tristrip const *				ts) {
	Point const *					points = ts->points;
   	_hoops_SGCC const &		_hoops_HSGA = nr->transform_rendition->_hoops_IPH;
	float							tolerance = nr->_hoops_CPP->_hoops_PRIGA.tolerance * 1.0e-6f;
	_hoops_GPPA const *	_hoops_IRCAR;
	_hoops_RAHGA *			_hoops_RGIGA;
	Point							_hoops_HRIGA[1024];
	Point alter *					_hoops_IRIGA = _hoops_HRIGA;
	bool							_hoops_AGIGA = false;

	/* _hoops_RGAR _hoops_SPR _hoops_HPPA _hoops_IPPA _hoops_HRGR _hoops_CISI _hoops_CGPR _hoops_RGR _hoops_SAGGR _hoops_PIGS */
	_hoops_IRCAR = nr->transform_rendition->_hoops_RGH->_hoops_PHCA->_hoops_APPA;

	/* "_hoops_SCGR" _hoops_HPPA _hoops_IPPA _hoops_GRS _hoops_SHH _hoops_HPGR _hoops_RIPS _hoops_IIGR _hoops_HIGR */
	_hoops_RGIGA = (_hoops_RAHGA *)nr->_hoops_SRA->_hoops_CRIGA;

	/* _hoops_HIHP _hoops_IS _hoops_GSSP _hoops_GC _hoops_RPP _hoops_SIGR */
	if (ANYBIT (_hoops_HSGA->data._hoops_RAGR, _hoops_CICH)) {
		if (ts->point_count > _hoops_GGAPR(_hoops_HRIGA))
			ALLOC_ARRAY (_hoops_IRIGA, ts->point_count, Point);
		points = _hoops_IRIGA;

		HI_Compute_Transformed_Points (ts->point_count, ts->points, &_hoops_HSGA->data.elements[0][0], _hoops_IRIGA);
	}

	_hoops_GGIGA (ts, points, &_hoops_IRCAR->_hoops_SHPA, _hoops_RGIGA, tolerance, &_hoops_AGIGA);

	if (_hoops_AGIGA &&
		(nr->_hoops_CPP->_hoops_PRIGA._hoops_SRIGA == _hoops_GAIGA &&
		 !nr->_hoops_SRA->_hoops_RAIGA ||
		 nr->_hoops_CPP->_hoops_PRIGA._hoops_SRIGA == _hoops_AAIGA)) {
		Display_Context alter *		dc;

		dc = (Display_Context alter *)nr->_hoops_SRA;

		dc->_hoops_PAIGA = nr->_hoops_IHA->color;
		dc->_hoops_HAIGA = nr->_hoops_AHP->color;
		dc->_hoops_RAIGA = true;
	}

	if (_hoops_IRIGA != _hoops_HRIGA)
		FREE_ARRAY (_hoops_IRIGA, ts->point_count, Point);
}



local int _hoops_IAIGA[] = {0, 1, 2};

local void triangle_action (
	void alter *				_hoops_CAIGA,
	int							_hoops_HAPH,
	Point const *				p1,
	Point const *				p2,
	Point const *				_hoops_IAPH,
	Integer32					s1,
	Integer32					s2,
	Integer32					_hoops_CAPH,
	Intersection const *		i1,
	Intersection const *		i2,
	Intersection const *		_hoops_SAPH) {
	Net_Rendition const *		nr = (Net_Rendition const *)_hoops_CAIGA;
	Point						points[3];
	Tristrip					ts;
	int							length = 3;

	UNREFERENCED (_hoops_HAPH);
	UNREFERENCED (s1);	UNREFERENCED (s2);	UNREFERENCED (_hoops_CAPH);
	UNREFERENCED (i1);	UNREFERENCED (i2);	UNREFERENCED (_hoops_SAPH);

	points[0].x = p1->x;
	points[0].y = p1->y;
	points[0].z = p1->z;

	points[1].x = p2->x;
	points[1].y = p2->y;
	points[1].z = p2->z;

	points[2].x = _hoops_IAPH->x;
	points[2].y = _hoops_IAPH->y;
	points[2].z = _hoops_IAPH->z;

	/* _hoops_AASC _hoops_CRHH, _hoops_SAHR _hoops_PCPA'_hoops_GRI _hoops_SIGR _hoops_IH _hoops_RH _hoops_HPPA _hoops_API */
	ZERO_STRUCT (&ts, Tristrip);
	ts.points = points;
	ts.point_count = 3;
	ts._hoops_PHHA = 1;
	ts.lengths = &length;
	ts._hoops_AIHA = _hoops_IAIGA;

	_hoops_ARIGA (*nr, &ts);
}

#define _hoops_SAIGA 64

local void HC_CDECL _hoops_GPIGA (
	Net_Rendition const &	nr,
	Polygon const *			_hoops_RPIGA) {
	int						count = _hoops_RPIGA->count;
	int						_hoops_APIGA[_hoops_SAIGA + 1];
	int alter				*face_list = _hoops_APIGA;
	int						index;

	if (count < 3)
		return;

	if (count > _hoops_SAIGA)
		ALLOC_ARRAY (face_list, count + 1, int);

	face_list[0] = count;
	for (index = 0; index < count; ++index)
		face_list[index+1] = index;

	HI_Triangulate_Face_X (_hoops_RPIGA->points, null, face_list, face_list + count + 1,
						   triangle_action, (void alter *)&nr);

	if (count > _hoops_SAIGA)
		FREE_ARRAY (face_list, count + 1, int);
}



local Geometry const * _hoops_PPIGA (
	Net_Rendition const &		_hoops_GSAGR,
	Geometry const *			geometry,
	Action_Mask					mask,
	bool						_hoops_RSAGR) {
	_hoops_ACHR					_hoops_RGP;
	Display_Context alter *		dc = (Display_Context alter *)_hoops_GSAGR->_hoops_SRA;
	_hoops_CRCP const *				start;
	_hoops_HICS				path;
	bool						_hoops_HPIGA;

	UNREFERENCED (mask);

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_IPIGA))
		return;
#endif

	_hoops_RGP = _hoops_GSAGR->_hoops_RGP;

	dc->_hoops_RAI = geometry;
	dc->_hoops_CPIGA = false;

	/* _hoops_PAH'_hoops_RA _hoops_HPPP _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_CAS _hoops_IS _hoops_PPSI _hoops_RH _hoops_GHPP (_hoops_HGPP _hoops_GAR
	 * _hoops_PHSPR _hoops_IRS _hoops_SPIGA).  _hoops_GACC _hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_HPPP _hoops_RPP _hoops_HAR _hoops_GHIGA _hoops_PAPA
	 */
	start = dc->_hoops_RHIGA;
	if (dc->_hoops_AHSI != null)
		path = dc->_hoops_AHSI->path;
	_hoops_HPIGA =	(_hoops_GSAGR->_hoops_CPP->_hoops_PRIGA.level == _hoops_AHIGA);

	do {
		Net_Rendition				nr = _hoops_GSAGR;
		bool						single = _hoops_RSAGR;

		if (dc->_hoops_SPA != dc->_hoops_ISAGR) {
			if ((geometry = dc->_hoops_SPA->geometry) == null)
				geometry = dc->_hoops_SPA->_hoops_CSAGR;	// _hoops_IHIS _hoops_GPP _hoops_IS _hoops_GGAS
			nr = dc->_hoops_SPA->nr;
			single = dc->_hoops_SPA->single;
		}

		dc->_hoops_RAI = geometry;

	_hoops_PCCAR {
		if (_hoops_GGPGR(nr)) {
			geometry = dc->_hoops_RAI;
			if (dc->_hoops_SPA != dc->_hoops_ISAGR &&
				geometry != dc->_hoops_SPA->_hoops_CSAGR)
				dc->_hoops_SPA->geometry = geometry;
			dc->_hoops_RAI = null;
			return geometry;
		}
		else switch (dc->_hoops_RAI->type) {
			/*
			 * _hoops_PHIGA _hoops_GGR _hoops_ARI _hoops_HA _hoops_IHSA _hoops_RGAR _hoops_RH _hoops_CICA,
			 * _hoops_HAR _hoops_RH _hoops_HAPR.  _hoops_PHGP _hoops_RH _hoops_RGAR _hoops_PPRRR _hoops_GGSR _hoops_HRGR _hoops_AIH
			 * _hoops_IRS _hoops_ASRC.  _hoops_HHIGA _hoops_ASRC _hoops_SIHH _hoops_RGSR
			 * _hoops_CSPH->_hoops_IHIGA = _hoops_IRAP.
			 */

			case _hoops_SCIP: 
			case _hoops_GSIP: {
				Type type = dc->_hoops_RAI->type;
#ifndef DISABLE_CALLBACKS
				_hoops_CRCP *	_hoops_ARPGR;
				if ((_hoops_ARPGR = dc->_hoops_RAI->owner) != null)
					_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(dc->_hoops_RIGC->thread_id);

				if (nr->_hoops_RSGC->action.draw_3d_polyhedron != null ||
					nr->_hoops_RSGC->action.draw_3d_geometry != null) {
					_hoops_CHIGA	draw;

					if (nr->_hoops_RSGC->action.draw_3d_polyhedron != null)
						draw = nr->_hoops_RSGC->action.draw_3d_polyhedron;
					else
						draw = (_hoops_CHIGA)nr->_hoops_RSGC->action.draw_3d_geometry;

					do {
						(*draw) (&nr, (Polyhedron const *)dc->_hoops_RAI);
						if (start != null)
							HD_Process_Cut_Geometry (_hoops_GSAGR, start, path, _hoops_HPIGA, false);

						if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
							if (_hoops_ARPGR != null)
								_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
							goto Done;
						}
					} while (dc->_hoops_RAI->type == type);
				}
				else
#endif
				{
					_hoops_SHIGA	draw = dc->_hoops_IPCI->draw_3d_polyhedron;

					do {
						(*draw) (nr, (Polyhedron const *)dc->_hoops_RAI);
						if (start != null)
							HD_Process_Cut_Geometry (_hoops_GSAGR, start, path, _hoops_HPIGA, false);

						if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null) {
							if (_hoops_ARPGR != null)
								_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
							goto Done;
						}
					} while (dc->_hoops_RAI->type == type);
				}

				if (_hoops_ARPGR != null)
					_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();

			}	break;

			case _hoops_PRCP: {
#ifndef _hoops_GSPIR
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
#ifndef DISABLE_CALLBACKS
					if (nr->_hoops_RSGC->action.draw_3d_nurbs_surface != null ||
						nr->_hoops_RSGC->action.draw_3d_geometry != null) {
						_hoops_GIIGA draw;

						if (nr->_hoops_RSGC->action.draw_3d_nurbs_surface != null)
							draw = nr->_hoops_RSGC->action.draw_3d_nurbs_surface;
						else
							draw = (_hoops_GIIGA)nr->_hoops_RSGC->action.draw_3d_geometry;

						do {
							(*draw) (&nr, (_hoops_APPGR *)dc->_hoops_RAI);
							if (start != null)
								HD_Process_Cut_Geometry (_hoops_GSAGR, start, path, _hoops_HPIGA, false);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_PRCP);
					}
					else
#endif
					{
						_hoops_RIIGA	draw = dc->_hoops_IPCI->draw_3d_nurbs_surface;

						do {
							(*draw) (nr, (_hoops_APPGR *)dc->_hoops_RAI);
							if (start != null)
								HD_Process_Cut_Geometry (_hoops_GSAGR, start, path, _hoops_HPIGA, false);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_PRCP);
					}
				}
				else
#endif
					_hoops_CSHI (dc->_hoops_RAI, _hoops_PRCP);
			}	break;

			case _hoops_ASIP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE)) {
#ifndef DISABLE_CALLBACKS
					if (nr->_hoops_RSGC->action.draw_3d_cylinder != null ||
						nr->_hoops_RSGC->action.draw_3d_geometry != null) {
						_hoops_AIIGA		draw;

						if (nr->_hoops_RSGC->action.draw_3d_cylinder != null)
							draw = nr->_hoops_RSGC->action.draw_3d_cylinder;
						else
							draw = (_hoops_AIIGA)nr->_hoops_RSGC->action.draw_3d_geometry;

						do {
							(*draw) (&nr, (Cylinder const *)dc->_hoops_RAI);
							if (start != null)
								HD_Process_Cut_Geometry (_hoops_GSAGR, start, path, _hoops_HPIGA, false);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_ASIP);
					}
					else
#endif
					{
						_hoops_PIIGA		draw = dc->_hoops_IPCI->draw_3d_cylinder;

						do {
							(*draw) (nr, (Cylinder const *)dc->_hoops_RAI);
							if (start != null)
								HD_Process_Cut_Geometry (_hoops_GSAGR, start, path, _hoops_HPIGA, false);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_ASIP);
					}
				}
				else
					_hoops_CSHI (dc->_hoops_RAI, _hoops_ASIP);
			}	break;

			case _hoops_CSIP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE)) {
#ifndef DISABLE_CALLBACKS
					if (nr->_hoops_RSGC->action.draw_3d_polycylinder != null ||
						nr->_hoops_RSGC->action.draw_3d_geometry != null) {
						_hoops_HIIGA	draw;

						if (nr->_hoops_RSGC->action.draw_3d_polycylinder != null)
							draw = nr->_hoops_RSGC->action.draw_3d_polycylinder;
						else
							draw = (_hoops_HIIGA)nr->_hoops_RSGC->action.draw_3d_geometry;

						do {
							(*draw) (&nr, (PolyCylinder const *)dc->_hoops_RAI);
							if (start != null)
								HD_Process_Cut_Geometry (_hoops_GSAGR, start, path, _hoops_HPIGA, false);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_CSIP);
					}
					else
#endif
					{
						_hoops_IIIGA	draw = dc->_hoops_IPCI->draw_3d_polycylinder;

						do {
							(*draw) (nr, (PolyCylinder const *)dc->_hoops_RAI);
							if (start != null)
								HD_Process_Cut_Geometry (_hoops_GSAGR, start, path, _hoops_HPIGA, false);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_CSIP);
					}
				}
				else
					_hoops_CSHI (dc->_hoops_RAI, _hoops_CSIP);
			}	break;


			case _hoops_HSIP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE)) {
#ifndef DISABLE_CALLBACKS
					if (nr->_hoops_RSGC->action.draw_3d_sphere != null ||
						nr->_hoops_RSGC->action.draw_3d_geometry != null) {
						_hoops_CIIGA		draw;

						if (nr->_hoops_RSGC->action.draw_3d_polycylinder != null)
							draw = nr->_hoops_RSGC->action.draw_3d_sphere;
						else
							draw = (_hoops_CIIGA)nr->_hoops_RSGC->action.draw_3d_geometry;

						do {
							(*draw) (&nr, (Sphere const *)dc->_hoops_RAI);
							if (start != null)
								HD_Process_Cut_Geometry (_hoops_GSAGR, start, path, _hoops_HPIGA, false);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_HSIP);
					}
					else
#endif
					{
						_hoops_SIIGA	draw = dc->_hoops_IPCI->draw_3d_sphere;

						do {
							(*draw) (nr, (Sphere const *)dc->_hoops_RAI);
							if (start != null)
								HD_Process_Cut_Geometry (_hoops_GSAGR, start, path, _hoops_HPIGA, false);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_HSIP);
					}
				}
				else
					_hoops_CSHI (dc->_hoops_RAI, _hoops_HSIP);
			}	break;

			case _hoops_SGCP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
#ifndef DISABLE_CALLBACKS
					if (nr->_hoops_RSGC->action.draw_3d_geometry != null) {
						_hoops_GCIGA		draw;

						draw = (_hoops_GCIGA)nr->_hoops_RSGC->action.draw_3d_geometry;

						do {
							(*draw) (&nr, (Ellipse const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_SGCP);
					}
					else
#endif
					{
						_hoops_RCIGA		draw = dc->_hoops_IPCI->draw_3d_ellipse;

						do {
							(*draw) (nr, (Ellipse const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_SGCP);
					}
				}
				else
					_hoops_CSHI (dc->_hoops_RAI, _hoops_SGCP);
			}	break;

			case _hoops_CGCP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
#ifndef DISABLE_CALLBACKS
					if (nr->_hoops_RSGC->action.draw_3d_ellipse != null ||
						nr->_hoops_RSGC->action.draw_3d_geometry != null) {
						_hoops_GCIGA		draw;

						if (nr->_hoops_RSGC->action.draw_3d_ellipse)
							draw = nr->_hoops_RSGC->action.draw_3d_ellipse;
						else
							draw = (_hoops_GCIGA)nr->_hoops_RSGC->action.draw_3d_geometry;

						do {
							(*draw) (&nr, (Ellipse const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_CGCP);
					}
					else
#endif
					{
						_hoops_RCIGA		draw = dc->_hoops_IPCI->draw_3d_ellipse;

						do {
							(*draw) (nr, (Ellipse const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_CGCP);
					}
				}
				else
					_hoops_CSHI (dc->_hoops_RAI, _hoops_CGCP);
			}	break;

			case _hoops_GRCP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
#ifndef DISABLE_CALLBACKS
					if (nr->_hoops_RSGC->action.draw_3d_geometry != null) {
						_hoops_ACIGA		draw;

						draw = (_hoops_ACIGA)nr->_hoops_RSGC->action.draw_3d_geometry;

						do {
							(*draw) (&nr, (Elliptical_Arc const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_GRCP);
					}
					else
#endif
					{
						_hoops_PCIGA		draw = dc->_hoops_IPCI->draw_3d_elliptical_arc;

						do {
							(*draw) (nr, (Elliptical_Arc const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_GRCP);
					}
				}
				else
					_hoops_CSHI (dc->_hoops_RAI, _hoops_GRCP);
			}	break;

			case _hoops_RRCP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
#ifndef DISABLE_CALLBACKS
					if (nr->_hoops_RSGC->action.draw_3d_geometry != null) {
						
						_hoops_ACIGA	draw = (_hoops_ACIGA)nr->_hoops_RSGC->action.draw_3d_geometry;

						do {
							(*draw) (&nr, (Elliptical_Arc const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_RRCP);
					}
					else
#endif
					{
						_hoops_PCIGA	draw = dc->_hoops_IPCI->draw_3d_elliptical_arc;

						do {
							(*draw) (nr, (Elliptical_Arc const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_RRCP);
					}
				}
				else
					_hoops_CSHI (dc->_hoops_RAI, _hoops_RRCP);
			}	break;

			case _hoops_RCIP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
#ifndef DISABLE_CALLBACKS
					if (nr->_hoops_RSGC->action.draw_3d_polygon != null ||
						nr->_hoops_RSGC->action.draw_3d_geometry != null) {
						_hoops_HCIGA		draw;

						if (nr->_hoops_RSGC->action.draw_3d_polygon != null)
							draw = nr->_hoops_RSGC->action.draw_3d_polygon;
						else
							draw = (_hoops_HCIGA)(nr->_hoops_RSGC->action.draw_3d_geometry);

						do {
							(*draw) (&nr, (Polygon const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_RCIP);
					}
					else
#endif
					{
						_hoops_ICIGA		draw = dc->_hoops_IPCI->draw_3d_polygon;

						do {
							(*draw) (nr, (Polygon const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_RCIP);
					}
				}
				else
					_hoops_CSHI (dc->_hoops_RAI, _hoops_RCIP);
			}	break;

			case _hoops_GGCP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_GRID_EDGE|T_VERTICES)) {
#ifndef DISABLE_CALLBACKS
					if (nr->_hoops_RSGC->action.draw_3d_geometry != null) {

						_hoops_CCIGA	draw = (_hoops_CCIGA)nr->_hoops_RSGC->action.draw_3d_geometry;

						do {
							(*draw) (&nr, (Grid const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_GGCP);
					}
					else
#endif
					{
						_hoops_SCIGA	draw = dc->_hoops_IPCI->draw_3d_grid;

						do {
							(*draw) (nr, (Grid const *)dc->_hoops_RAI);

							if (single || (dc->_hoops_RAI = dc->_hoops_RAI->next) == null)
								goto Done;
						} while (dc->_hoops_RAI->type == _hoops_GGCP);
					}
				}
				else
					_hoops_CSHI (dc->_hoops_RAI, _hoops_GGCP);
			}	break;

			case _hoops_HGPGR:
			case _hoops_PIIP:
			case _hoops_HIIP:
			case _hoops_IIIP:
			case _hoops_CHIP:
			case _hoops_RIIP:
			case _hoops_GIIP:
			case _hoops_ICIP:
			case _hoops_PCIP:
			case _hoops_PIRS:
			case _hoops_AGCP:
			case _hoops_HGCP: {
				if (single)
					goto Done;
				else
					_hoops_CSHI (dc->_hoops_RAI, dc->_hoops_RAI->type);
			}	break;

			case _hoops_GHPGR: {
				/* _hoops_ASRHR _hoops_CGH _hoops_AIAH _hoops_HS _hoops_RPII _hoops_CRPPR _hoops_HPP _hoops_GSSR _hoops_SRGS */
				_hoops_CSHI (dc->_hoops_RAI, _hoops_GHPGR);
			}	break;

			case _hoops_AHIP: {
				_hoops_PHIP const *		_hoops_RRA = (_hoops_PHIP const *)dc->_hoops_RAI;
				Geometry const *				_hoops_PPPGR = _hoops_RRA->next;

				if ((dc->_hoops_RAI = HD_Process_Geometry_Reference (nr, _hoops_RRA)) != null)
					goto _hoops_SPPGR;
				nr = _hoops_GSAGR;
				single = _hoops_RSAGR;

				if (single || (dc->_hoops_RAI = _hoops_PPPGR) == null)
					goto Done;
			}	break;

			default: {
				_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, 
					Sprintf_D (null, "Unknown type '%d' in render", geometry->type));
				dc->_hoops_RAI = null;
				return null;
			}	  _hoops_HHHI;
		}

		if (dc->_hoops_RAI == null)
			break;
	}


  Done:;
//		_hoops_CSPH->_hoops_IHIGA = _hoops_IRAP;
		if (dc->_hoops_SPA != dc->_hoops_ISAGR)
			dc->_hoops_SPA->geometry = null;

  _hoops_SPPGR:;
	} while (dc->_hoops_SPA != dc->_hoops_ISAGR);


	//_hoops_RPP (_hoops_HSPP != _hoops_IRAP && _hoops_CAHP)
	//	_hoops_GSIGA (_hoops_RSIGA, _hoops_HSPP, _hoops_CRAA, _hoops_RCPP, _hoops_IHPR);

	dc->_hoops_RAI = null;

	return null;
}


GLOBAL_FUNCTION void HD_Generate_Cut_Geometry (
	Net_Rendition const & 		in_nr,
	_hoops_CRCP const *				_hoops_SRCP,
	Geometry const *			geometry) {
	Display_Context alter *		dc = (Display_Context alter *)in_nr->_hoops_SRA;
	_hoops_SGCC const &	_hoops_HSGA = in_nr->transform_rendition->_hoops_IPH;
	Net_Rendition				nr = in_nr;
	_hoops_RAHGA *		_hoops_RGIGA;
	_hoops_IAPA const *	_hoops_HRCAR;

	if (geometry == null)
		return;		/* _hoops_CGH _hoops_HS _hoops_RPII _hoops_RAICR... */

	/* _hoops_ASIGA _hoops_CASI _hoops_PPR _hoops_RIARR _hoops_RPP _hoops_AGRRR */

	Bounding	bounding;

	if (_hoops_SRCP->bounding != null) {
		if (_hoops_SRCP->bounding._hoops_HICAR())
			return;		/* _hoops_PSP _hoops_PSIGA _hoops_CPAP */

		bounding = _hoops_SRCP->bounding;
	}
	else {
		Geometry const *		g = geometry;

		bounding = Bounding::Create();

		do {
			Bounding		_hoops_HSIGA;

			if (HI_Figure_Geometry_Bounding (g, _hoops_HSIGA))
				bounding.Merge (_hoops_HSIGA);
		} while ((g = g->next) != null);

		if (bounding._hoops_HICAR())
			return;		/* _hoops_PSP _hoops_PSIGA _hoops_CPAP */
	}

	if (bounding->sphere.radius == 0.0f)
		return;			/* _hoops_PAH'_hoops_RA _hoops_HGCR _hoops_PA _hoops_IRCC _hoops_IS _hoops_AACC _hoops_IRS _hoops_PPSR */

	if (_hoops_HSGA->data._hoops_RAGR != 0)
		bounding = bounding._hoops_SCIS (&_hoops_HSGA->data.elements[0][0]);

	_hoops_HRCAR = in_nr->transform_rendition->_hoops_RGH->_hoops_ISIGA;
	if (_hoops_HRCAR) do {
		_hoops_GPPA const *	_hoops_IRCAR;

		_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA;
		do if (!_hoops_IRCAR->internal) {
			_hoops_RAHGA **		_hoops_ASRGR = &dc->_hoops_CRIGA;
			_hoops_HHRA *					_hoops_SPH;
			_hoops_APARR				_hoops_RRCI;

			if ((_hoops_RGIGA = dc->_hoops_CRIGA) != null) do {
				if (_hoops_IRCAR->id == _hoops_RGIGA->_hoops_AAHGA)
					break;
				_hoops_ASRGR = &_hoops_RGIGA->next;
			} while ((_hoops_RGIGA = _hoops_RGIGA->next) != null);

			if (_hoops_RGIGA == null) {
				ZALLOC (_hoops_RGIGA, _hoops_RAHGA);
				_hoops_RGIGA->next = dc->_hoops_CRIGA;
				dc->_hoops_CRIGA = _hoops_RGIGA;
				_hoops_RGIGA->_hoops_AAHGA = _hoops_IRCAR->id;
				_hoops_RGIGA->_hoops_PICHR = POOL_NEW(dc->memory_pool, _hoops_IRHGA)(dc->memory_pool);
				_hoops_RGIGA->_hoops_CAHGA = POOL_NEW(dc->memory_pool, _hoops_GAHGA)(dc->memory_pool);
				_hoops_RGIGA->_hoops_GPHGA = POOL_NEW(dc->memory_pool, _hoops_CRHGA)(dc->memory_pool);
				_hoops_RGIGA->faces = POOL_NEW(dc->memory_pool, _hoops_SRHGA)(dc->memory_pool);
			}
			else if (_hoops_RGIGA != dc->_hoops_CRIGA) {
				/* _hoops_IHIS _hoops_IS _hoops_RIPS */
				*_hoops_ASRGR = _hoops_RGIGA->next;
				_hoops_RGIGA->next = dc->_hoops_CRIGA;
				dc->_hoops_CRIGA = _hoops_RGIGA;
			}

			_hoops_RGIGA->_hoops_APHGA = in_nr;

			ZALLOC(_hoops_SPH, _hoops_HHRA);
			HI_Default_Camera(_hoops_SPH);
			_hoops_PRRH (_hoops_SPH);

			_hoops_SPH->_hoops_RRHH = _hoops_RSPCR;
			_hoops_SPH->position = bounding->sphere.center + bounding->sphere.radius * _hoops_IRCAR->_hoops_SHPA;
			_hoops_SPH->target = bounding->sphere.center;
			_hoops_SPH->up_vector = _hoops_IRGA::_hoops_RCPCR;
			_hoops_SPH->_hoops_ISPA = 2.0f * bounding->sphere.radius;
			_hoops_SPH->_hoops_SSPA = _hoops_SPH->_hoops_ISPA;
			_hoops_SPH->projection = _hoops_CPPCR;
			_hoops_SPH->_hoops_HHCH = 0.0f;
			_hoops_SPH->_hoops_IHCH = 0.0f;

			_hoops_SPH->_hoops_IIPCR = -_hoops_IRCAR->_hoops_SHPA;
			_hoops_SPH->_hoops_CRSS = _hoops_IRGA::X_Axis;
			_hoops_SPH->_hoops_SRIR = bounding->sphere.radius;
			_hoops_SPH->_hoops_ARSS = 2.0f;
			_hoops_SPH->_hoops_PRSS = 2.0f;
			_hoops_SPH->_hoops_CSIH = 1.0f;
			_hoops_SPH->_hoops_CIPCR = *in_nr->transform_rendition->_hoops_SPH->_hoops_SIPCR;
			_hoops_SPH->_hoops_SIPCR = &_hoops_SPH->_hoops_CIPCR;

			/* _hoops_IRHH _hoops_RCRR _hoops_PSPAR _hoops_SRSGR _hoops_PCCP _hoops_CSIGA _hoops_HARGR */
			/*	_hoops_AHGC, _hoops_RRP _hoops_HAR _hoops_SHH _hoops_AARGR, _hoops_SAHR _hoops_HAR _hoops_GPP _hoops_CRAA */
			HI_Cross_Product (&_hoops_SPH->up_vector, &_hoops_SPH->_hoops_IIPCR, &_hoops_SPH->_hoops_CRSS);

			if (_hoops_SPH->_hoops_CRSS.x == 0 &&
				  _hoops_SPH->_hoops_CRSS.y == 0 &&
					_hoops_SPH->_hoops_CRSS.z == 0) {
				/* _hoops_AHCI _hoops_AHGC -- _hoops_RHC _hoops_HAGA _hoops_PIHA _hoops_SHH _hoops_IGIAR _hoops_GHCR _hoops_IRSS, _hoops_SPCR _hoops_HRGR _hoops_IHRI _hoops_IH _hoops_SSIGA _hoops_PSCR */
				_hoops_SPH->up_vector = _hoops_IRGA::X_Axis;

				HI_Cross_Product (&_hoops_SPH->up_vector, &_hoops_SPH->_hoops_IIPCR, &_hoops_SPH->_hoops_CRSS);
			}

			/* _hoops_GGCGA _hoops_HA _hoops_RGCGA _hoops_CIAH, _hoops_AGCGA _hoops_SSIGA */
			HI_Cross_Product (&_hoops_SPH->_hoops_IIPCR, &_hoops_SPH->_hoops_CRSS, &_hoops_SPH->up_vector);

			/* _hoops_PPR _hoops_HPGIR */
			HI_Normalize (&_hoops_SPH->up_vector);
			HI_Normalize (&_hoops_SPH->_hoops_CRSS);


			HD_Downwind_Camera (nr, (Attribute *)_hoops_SPH);

			_hoops_HPRH (_hoops_SPH);

			nr.Modify();
			nr->current |= _hoops_PGCGA;

			HD_Remove_Cutting_Planes (nr);
			HD_Add_Cutting_Plane (nr, &_hoops_IRCAR->_hoops_SHPA);

			_hoops_RRCI = _hoops_HGCGA (dc, "cut geometry", nr);

			/* _hoops_PGSI _hoops_IS _hoops_PGSA _hoops_ISSGR _hoops_IGCGA _hoops_PPR _hoops_PGGC _hoops_GII _hoops_HPPA _hoops_APGR */

			_hoops_RRCI->_hoops_CHCI						= _hoops_PPIGA;

			_hoops_RRCI->draw_3d_polyhedron			= HD_Std_3D_Polyhedron;
			_hoops_RRCI->draw_3d_nurbs_surface		= HD_Std_3D_NURBS_Surface;
			_hoops_RRCI->draw_3d_cylinder			= HD_Std_3D_Cylinder;
			_hoops_RRCI->draw_3d_polycylinder		= HD_Std_3D_PolyCylinder;
			_hoops_RRCI->draw_3d_sphere				= HD_Std_3D_Sphere;

			_hoops_RRCI->draw_3d_ellipse				= HD_Std_3D_Ellipse;
			_hoops_RRCI->draw_3d_grid				= HD_Std_3D_Grid;

			_hoops_RRCI->draw_3d_polygon				= _hoops_GPIGA;
			_hoops_RRCI->draw_3d_tristrip			= _hoops_ARIGA;

			/*
			 * _hoops_HCR _hoops_RII _hoops_CPAP _hoops_PGSA _hoops_PSCH _hoops_PAH _hoops_SHH _hoops_HPSH	 -- _hoops_ISCP _hoops_GRH
			 * _hoops_SRGS _hoops_CGH _hoops_SRCH _hoops_CGCGA _hoops_ICRP _hoops_IIGR _hoops_AGCR, _hoops_HIH _hoops_HHH _hoops_CHH
			 * _hoops_HCAGR _hoops_SHH _hoops_CPHR _hoops_GAR _hoops_ARIP _hoops_IIGR "_hoops_ASCA" _hoops_RH _hoops_PIASR _hoops_APSAR, _hoops_PPR _hoops_SR
			 * _hoops_IIP _hoops_ACPA _hoops_PCPA _hoops_PISC _hoops_GPAC _hoops_HHH _hoops_CPAP _hoops_SIAS _hoops_RSGR _hoops_GH _hoops_PSAR
			 */
			_hoops_RRCI->draw_3d_elliptical_arc		= (_hoops_PCIGA)_hoops_RSHGA;
			_hoops_RRCI->draw_3d_marker				= (_hoops_SGCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_3d_polyline			= (_hoops_GRCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_3d_nurbs_curve			= (_hoops_RRCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_3d_image				= (_hoops_ARCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_3d_text				= (_hoops_PRCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_HRCGA				= (_hoops_IRCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_CRCGA		= (_hoops_SRCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_3d_polyedge			= (_hoops_GACGA)_hoops_RSHGA;
			_hoops_RRCI->draw_3d_polyedge_from_tristrip = (_hoops_RACGA)_hoops_RSHGA;
			_hoops_RRCI->draw_3d_polymarker			= (_hoops_AACGA)_hoops_RSHGA;

			_hoops_RRCI->_hoops_PPAS		= (_hoops_GACGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_ARCI		= (_hoops_PACGA)_hoops_RSHGA;

			_hoops_RRCI->draw_dc_ellipse				= (_hoops_HACGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_SCISR		= (_hoops_IACGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_CCISR		= (_hoops_CACGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_face				= (_hoops_SACGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_colorized_face		= (_hoops_GPCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_RPCGA				= (_hoops_APCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_rectangle			= (_hoops_PPCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_HPCGA				= (_hoops_IPCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_text				= (_hoops_CPCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_SPCGA		= (_hoops_GHCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_polytriangle		   = (_hoops_RHCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_colorized_polytriangle = (_hoops_AHCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_gouraud_polytriangle   = (_hoops_PHCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_phong_polytriangle	= (_hoops_HHCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_textured_polytriangle  = (_hoops_IHCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_polyline			= (_hoops_CHCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_colorized_polyline	= (_hoops_SHCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_gouraud_polyline	= (_hoops_GICGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_phong_polyline		= (_hoops_RICGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_textured_polyline	= (_hoops_AICGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_polymarker			= (_hoops_PICGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_colorized_polymarker = (_hoops_HICGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_polydot				= (_hoops_IICGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_CICGA				= (_hoops_SICGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_GCCGA		= (_hoops_RCCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_ACCGA		= (_hoops_PCCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_HCCGA		= (_hoops_ICCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_CCCGA			= (_hoops_SCCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_GSCGA		= (_hoops_RSCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_CCCSR		= (_hoops_ASCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_PSCGA	= (_hoops_HSCGA)_hoops_RSHGA;
			_hoops_RRCI->draw_dc_rgb32_rasters		= (_hoops_ISCGA)_hoops_RSHGA;

			_hoops_RRCI->_hoops_CSCGA				= (_hoops_SSCGA)_hoops_RSHGA;
			_hoops_RRCI->_hoops_AGCSR				= (_hoops_GGSGA)_hoops_RSHGA;

			dc->flags |= _hoops_RGSGA;

			_hoops_AGSGA	_hoops_PGSGA (dc);
			(*dc->_hoops_IPCI->_hoops_CHCI) (nr, geometry, _hoops_RAPI, false);

			dc->flags &= ~_hoops_RGSGA;

			_hoops_HGSGA (dc, "cut geometry");
			_hoops_RGIGA->_hoops_APHGA = null;
		} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);
	} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);
}

local float _hoops_IGSGA[] = {0.001f, 0.01f, 0.1f, 1.0f};

local Key _hoops_CGSGA (
	Display_Context *			dc,
	_hoops_AIGPR *		_hoops_RIGC,
 	bool						_hoops_HPIGA,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path,
	bool						_hoops_SGSGA,
	_hoops_RAHGA *		_hoops_RGIGA,
	float const *				_hoops_GRSGA,
	float						tolerance) 
{
	_hoops_RRSGA *				_hoops_RPGGA = 0;
 	_hoops_GAHGA *			_hoops_AHHGA;
	_hoops_IRHGA *					_hoops_HHHGA;
	_hoops_IRHGA *					_hoops_RHHGA;
	_hoops_CRHGA *				_hoops_ARSGA;
	_hoops_ARHGA *					line;
	_hoops_PRHGA *				polyline;
	_hoops_HRHGA *					face;
	int							i, count, _hoops_ASPS, point_count, face_list_length;
	int *						_hoops_PRSGA;
	Point *						_hoops_HRSGA;
	bool						_hoops_IRSGA;
	Key							_hoops_CRSGA = _hoops_SHSSR;

	if (_hoops_RGIGA != null) do {
 		/* _hoops_CCPP _hoops_HHH _hoops_AH _hoops_CPCI.  _hoops_ASC _hoops_CHR _hoops_HCR _hoops_SRSGA _hoops_GH _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_API, _hoops_HIS _hoops_GASGA _hoops_IIGR
		 * _hoops_GII _hoops_RSIH _hoops_RASGA _hoops_SGS _hoops_AASGA _hoops_SGS _hoops_GGAS. */
		_hoops_AHHGA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_GAHGA)(_hoops_RIGC->memory_pool);
		_hoops_ARSGA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_CRHGA)(_hoops_RIGC->memory_pool);

		/* _hoops_PASGA _hoops_HII _hoops_III _hoops_IS _hoops_ISII */
		while ((line = _hoops_RGIGA->_hoops_PICHR->RemoveFirst()) != null) {
			_hoops_HHHGA = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_IRHGA)(_hoops_RIGC->memory_pool);
			_hoops_HHHGA->AddFirst(line);
			_hoops_AHHGA->AddLast(_hoops_HHHGA);
		}

		// _hoops_RCHRR _hoops_HII _hoops_PCCP _hoops_IGGA _hoops_CPAP, _hoops_SGH _hoops_IRS _hoops_CPPPR _hoops_HASGA _hoops_AAHP
		{
			float			_hoops_IASGA = tolerance * 1.0e-5f;

			while ((_hoops_RHHGA = _hoops_AHHGA->RemoveFirst()) != null) {
				if (_hoops_RHHGA->Count() == 0) {
					delete _hoops_RHHGA;
					continue;
				}
				if (_hoops_GHHGA (_hoops_RHHGA, _hoops_AHHGA, _hoops_IASGA, tolerance * 1.0e-6f))
					continue;

				_hoops_RGIGA->_hoops_CAHGA->AddFirst(_hoops_RHHGA);
			}
		}
		if (!_hoops_HPIGA)
			goto _hoops_HPAGR;

		// _hoops_GPGR _hoops_HHHH _hoops_HPGR _hoops_HASGA _hoops_HIH _hoops_CASGA _hoops_SASGA _hoops_GPSGA, _hoops_ACPP _hoops_RPSGA
		for (i=0; i<_hoops_GGAPR(_hoops_IGSGA); i++) {
			float			_hoops_IASGA = tolerance * _hoops_IGSGA[i];

			Swap (_hoops_RGIGA->_hoops_CAHGA, _hoops_AHHGA);

			while ((_hoops_RHHGA = _hoops_AHHGA->RemoveFirst()) != null) {
				if (_hoops_RHHGA->Count() == 0) {
					delete _hoops_RHHGA;
					continue;
				}
				if (_hoops_GHHGA (_hoops_RHHGA, _hoops_AHHGA, _hoops_IASGA, tolerance * 1.0e-6f))
					continue;

				_hoops_RGIGA->_hoops_CAHGA->AddFirst(_hoops_RHHGA);
			}
		}


		while ((_hoops_RHHGA = _hoops_RGIGA->_hoops_CAHGA->RemoveFirst()) != null) {
			/* _hoops_APSGA _hoops_HII _hoops_IRS _hoops_CCHHR _hoops_HIGR _hoops_SCCI _hoops_CRGR _hoops_PCCP _hoops_CRPR.	 _hoops_PS _hoops_PHHR _hoops_HII _hoops_IRS _hoops_PPSGA _hoops_IIGR "_hoops_HPSGA"'_hoops_GRI
			 * _hoops_IS _hoops_IRS _hoops_RSRA "_hoops_IPSGA" */
			if (_hoops_RHHGA->Count() != 0) {
				ALLOC (polyline, _hoops_PRHGA);
				count = _hoops_RHHGA->Count();
				polyline->count = count + 1;
				ALLOC_ARRAY (polyline->points, polyline->count, Point);
				for (i = 0; i < count; i++) {
					line = _hoops_RHHGA->RemoveFirst();
					memcpy (&polyline->points[i], &line->points[0], sizeof (Point));
					if (i == count - 1)
						memcpy (&polyline->points[i+1], &line->points[1], sizeof (Point));
					FREE (line, _hoops_ARHGA);
				}

				_hoops_ARSGA->AddFirst(polyline);
			}
			delete _hoops_RHHGA;
			_hoops_RHHGA = NULL;
		}

		/* _hoops_IPS _hoops_IS _hoops_HRSAR _hoops_PGRC _hoops_HIGR */
		_hoops_ARSGA->ResetCursor();
		while ((polyline = _hoops_ARSGA->PeekCursor()) != null) {
			_hoops_RGIGA->_hoops_GPHGA->AddFirst(_hoops_GSHGA (polyline));
			_hoops_ARSGA->AdvanceCursor();
		}

		/* _hoops_PASGA _hoops_HII _hoops_ISII _hoops_IS _hoops_HSP */
		point_count = 0;
		face_list_length = 0;
		_hoops_ASPS = 0;
		_hoops_ARSGA->ResetCursor();

		/* _hoops_GRAS _hoops_PCCP _hoops_AAPA _hoops_ASCR _hoops_GPP _hoops_PPSR _hoops_RPR _hoops_PPR _hoops_HSP _hoops_HIGR _hoops_SPCC */
		count = _hoops_ARSGA->Count();
		for (i = 0; i < count; i++) {
			polyline = _hoops_ARSGA->PeekCursor();
			point_count += polyline->count;
			face_list_length += polyline->count + 1;
			_hoops_ARSGA->AdvanceCursor();
		}
		if (point_count != 0) {
			ALLOC (face, _hoops_HRHGA);
			ALLOC_ARRAY (face->points, point_count, Point);
			ALLOC_ARRAY (face->face_list, face_list_length, int);

			_hoops_HRSGA = face->points;
			_hoops_PRSGA = face->face_list;
			_hoops_IRSGA = true;
			while ((polyline = _hoops_ARSGA->RemoveFirst()) != null) {
				/* _hoops_RPP _hoops_RH _hoops_ISII _hoops_HRGR _hoops_RRI _hoops_HSAR _hoops_IRS _hoops_RSRA _hoops_III _hoops_PPR _hoops_HRGR _hoops_IRS _hoops_CAHC _hoops_ISPH (_hoops_SRS _hoops_PPR _hoops_CGHI _hoops_RSSA
				 * _hoops_CHR _hoops_SASPR), _hoops_SR _hoops_PAH _hoops_GGCR _hoops_SCH _hoops_IS _hoops_RH _hoops_HSP _hoops_HIGR */
				if (polyline->count >= 3 &&
					(polyline->points[0] - polyline->points[polyline->count - 1])._hoops_PPSSR() < tolerance) {
					if (_hoops_IRSGA)
						*_hoops_PRSGA = polyline->count - 1;
					else
						/* _hoops_CAHAR _hoops_HCR _hoops_RSSI _hoops_RAS _hoops_RH _hoops_SRS _hoops_CHR _hoops_PCCPR.	 _hoops_CPSGA _hoops_RPP _hoops_SSIA'_hoops_ASAR _hoops_IPHC, _hoops_RH
						 * _hoops_AGAH _hoops_SPSGA _hoops_GRS _hoops_ACPA _hoops_PCPA _hoops_IS _hoops_AA */
						*_hoops_PRSGA = - (polyline->count - 1);
					_hoops_PRSGA++;

					for (i = 0; i < polyline->count - 1; i++) {
						*_hoops_PRSGA++ = _hoops_ASPS++;
						memcpy (_hoops_HRSGA, &polyline->points[i], sizeof (Point));
						_hoops_HRSGA++;
					}
					_hoops_IRSGA = false;
				}
				FREE_ARRAY (polyline->points, polyline->count, Point);
				FREE (polyline, _hoops_PRHGA);
			}
			face->point_count = _hoops_HRSGA - face->points;
			face->face_list_length = _hoops_PRSGA - face->face_list;

			if (face->point_count != 0) {
				/* _hoops_GRHP _hoops_SCH _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_RIRA (_hoops_HIH _hoops_PCCS _hoops_SIRGR _hoops_RPP _hoops_SIGR) */
				if (face->point_count != point_count) {
					_hoops_HRSGA = face->points;
					_hoops_APRGA(_hoops_HRSGA, face->point_count, Point, face->points);
					FREE_ARRAY (_hoops_HRSGA, point_count, Point);
				}
				if (face->face_list_length != face_list_length) {
					_hoops_PRSGA = face->face_list;
					_hoops_APRGA(_hoops_PRSGA, face->face_list_length, int, face->face_list);
					FREE_ARRAY (_hoops_PRSGA, face_list_length, int);
				}
				_hoops_RGIGA->faces->AddFirst(face);
			}
			else {
				/* _hoops_PPRI _hoops_SCH _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_AHCI (_hoops_IAS._hoops_ISHI. _hoops_HCR _hoops_RSSI _hoops_ARHAR) */
				FREE_ARRAY (face->points, point_count, Point);
				FREE_ARRAY (face->face_list, face_list_length, int);
				FREE (face, _hoops_HRHGA);
			}
		}

		if (_hoops_RGIGA->_hoops_PICHR->Count() == 0 &&
			_hoops_RGIGA->_hoops_GPHGA->Count() == 0 &&
			_hoops_RGIGA->faces->Count() == 0)
			goto _hoops_HPAGR;



		if (_hoops_SRCP != null) {
			_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
			_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);

			if ((_hoops_RPGGA = _hoops_CSC->_hoops_GHSGA()->_hoops_RHSGA) != null) do {
				if (_hoops_RPGGA->_hoops_AAHGA == _hoops_RGIGA->_hoops_AAHGA)
					break;
			} while ((_hoops_RPGGA = _hoops_RPGGA->next) != null);

			if (_hoops_RPGGA == null) {
				ALLOC (_hoops_RPGGA, _hoops_RRSGA);
				_hoops_RPGGA->next = _hoops_CSC->_hoops_GHSGA()->_hoops_RHSGA;
				_hoops_CSC->_hoops_GHSGA()->_hoops_RHSGA = _hoops_RPGGA;
				_hoops_RPGGA->_hoops_AAHGA = _hoops_RGIGA->_hoops_AAHGA;
				_hoops_RPGGA->geometry = null;
			}
		}


		while ((line = _hoops_RGIGA->_hoops_PICHR->RemoveFirst()) != null) {
			Line *			geometry;

			if (_hoops_SRCP != null) {
				ZALLOC (geometry, Line);
				geometry->type = _hoops_PIIP;
				geometry->_hoops_RRHH = _hoops_RSPCR;
				geometry->_hoops_CPGPR = _hoops_PHSSR;
				geometry->_hoops_HIHI = 1;
				geometry->key = _hoops_AIRIR (geometry);

				if (_hoops_GRSGA != null)
					HI_Compute_Transformed_Points (2, line->points, _hoops_GRSGA, geometry->points);
				else
					_hoops_AIGA (line->points, 2, Point, geometry->points);

				if ((geometry->next = _hoops_RPGGA->geometry) != null)
					_hoops_RPGGA->geometry->backlink = &geometry->next;
				geometry->backlink = &_hoops_RPGGA->geometry;
				_hoops_RPGGA->geometry = (Geometry *)geometry;
			}

			FREE (line, _hoops_ARHGA);
		}
		while ((polyline = _hoops_RGIGA->_hoops_GPHGA->RemoveFirst()) != null) {
			if (_hoops_SRCP != null) {
				Geometry **			_hoops_ASRGR;
				Polyline *			geometry;
				Point *				points;

				ZALLOC (geometry, Polyline);
				geometry->type = _hoops_IIIP;
				geometry->_hoops_RRHH = _hoops_RSPCR;
				geometry->_hoops_CPGPR = _hoops_PHSSR;
				geometry->_hoops_HIHI = 1;
				geometry->key = _hoops_AIRIR (geometry);
				geometry->count = polyline->count;

				ALLOC_ARRAY (points, polyline->count, Point);
				geometry->points = points;
				geometry->allocated = polyline->count;
				if (_hoops_GRSGA != null)
					HI_Compute_Transformed_Points (polyline->count, polyline->points, _hoops_GRSGA, points);
				else
					_hoops_AIGA (polyline->points, polyline->count, Point, points);

				/* _hoops_HGHC _hoops_RAS _hoops_GII _hoops_SCHS */
				_hoops_ASRGR = &_hoops_RPGGA->geometry;
				while (*_hoops_ASRGR != null && (*_hoops_ASRGR)->type < _hoops_IIIP)
					_hoops_ASRGR = &(*_hoops_ASRGR)->next;

				if ((geometry->next = *_hoops_ASRGR) != null)
					(*_hoops_ASRGR)->backlink = &geometry->next;
				geometry->backlink = _hoops_ASRGR;
				*_hoops_ASRGR = (Geometry *)geometry;
			}

			FREE_ARRAY (polyline->points, polyline->count, Point);
			FREE (polyline, _hoops_PRHGA);
		}

		while ((face = _hoops_RGIGA->faces->RemoveFirst()) != null) {
			if (_hoops_SRCP != null) {
				Shell *				geometry;
				Point *				points;

				ZALLOC (geometry, Shell);

				geometry->type = _hoops_SCIP;
				geometry->_hoops_RRHH = _hoops_RSPCR;
				geometry->_hoops_HIHI = 1;
				geometry->key = _hoops_AIRIR (geometry);

				geometry->point_count = face->point_count;
				geometry->_hoops_SPHA = -1;			/* _hoops_HAR _hoops_AISP _hoops_GAPR */
				geometry->face_count = 1;

				ALLOC_ARRAY_ALIGNED (points, face->point_count, Point, 16);
				geometry->points = points;
				if (_hoops_GRSGA != null)
					HI_Compute_Transformed_Points (face->point_count, face->points, _hoops_GRSGA, points);
				else
					_hoops_AIGA (face->points, face->point_count, Point, points);

				geometry->face_list_length = face->face_list_length;
				geometry->face_list = (int *)
				HI_Clone_Anything ((void *)face->face_list, face->face_list_length * (long)sizeof(int));

				geometry->_hoops_CPGPR = _hoops_AHSGA;
				HI_Figure_Geometry_Bounding ((Geometry *)geometry, geometry->bounding);	// _hoops_IRAP);
				geometry->_hoops_CPGPR = _hoops_PHSSR;

				if ((geometry->next = _hoops_RPGGA->geometry) != null)
					_hoops_RPGGA->geometry->backlink = &geometry->next;
				geometry->backlink = &_hoops_RPGGA->geometry;
				_hoops_RPGGA->geometry = (Geometry *)geometry;
			}
			else {
				PUSHNAME(_hoops_RIGC);
				_hoops_CRSGA = HC_Insert_Shell (face->point_count, face->points,
													 face->face_list_length, face->face_list);
				POPNAME(_hoops_RIGC);
			}
 			FREE_ARRAY (face->points, face->point_count, Point);
			FREE_ARRAY (face->face_list, face->face_list_length, int);
			FREE (face, _hoops_HRHGA);
		}

	  _hoops_HPAGR:
		delete _hoops_AHHGA;
		delete _hoops_ARSGA;

		if (_hoops_SGSGA) {	/* _hoops_HCR _hoops_CPHR _hoops_CCA _hoops_SCH */
			dc->_hoops_CRIGA = _hoops_RGIGA->next;

			delete _hoops_RGIGA->_hoops_PICHR;
			delete _hoops_RGIGA->_hoops_CAHGA;
			delete _hoops_RGIGA->_hoops_GPHGA;
			delete _hoops_RGIGA->faces;
			FREE (_hoops_RGIGA, _hoops_RAHGA);

			_hoops_RGIGA = dc->_hoops_CRIGA;
		}
		else
			_hoops_RGIGA = _hoops_RGIGA->next;
	} while (_hoops_RGIGA != null);

	return _hoops_CRSGA;
}



GLOBAL_FUNCTION void HD_Process_Cut_Geometry (
	Net_Rendition const & 		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path,
	bool						_hoops_HPIGA,
	bool						_hoops_SGSGA) {
	_hoops_SGCC const &	matrix = nr->transform_rendition->_hoops_IPH;
 	_hoops_RAHGA *		_hoops_RGIGA;

	_hoops_RGIGA = (_hoops_RAHGA *)nr->_hoops_SRA->_hoops_CRIGA;

	_hoops_CGSGA ((Display_Context *)nr->_hoops_SRA,
									nr->_hoops_SRA->_hoops_RIGC, _hoops_HPIGA, _hoops_SRCP, path,
									_hoops_SGSGA, _hoops_RGIGA,
									&matrix->_hoops_PPRA()->data.elements[0][0],
									nr->_hoops_CPP->_hoops_PRIGA.tolerance);


	if (_hoops_HPIGA) {
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, nr->_hoops_SRA->_hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);
		_hoops_PHSGA *		_hoops_HHSGA = _hoops_CSC->_hoops_GHSGA();

		_hoops_HHSGA->_hoops_RSISR = nr->_hoops_SRA->_hoops_PAIGA;
		_hoops_HHSGA->_hoops_IHSGA = nr->_hoops_SRA->_hoops_HAIGA;

		((Display_Context alter *)nr->_hoops_SRA)->_hoops_RAIGA = false;
	}
}


GLOBAL_FUNCTION void HD_Delete_Cut_Geometry_Pieces (
	Display_Context alter *		dc) {
	_hoops_RAHGA *		_hoops_RGIGA;

	while ((_hoops_RGIGA = dc->_hoops_CRIGA) != null) {
		if (_hoops_RGIGA->_hoops_PICHR)
			delete _hoops_RGIGA->_hoops_PICHR;
		if (_hoops_RGIGA->_hoops_GPHGA)
			delete _hoops_RGIGA->_hoops_GPHGA;
		if (_hoops_RGIGA->faces)
			delete _hoops_RGIGA->faces;
		if (_hoops_RGIGA->_hoops_CAHGA)
			delete _hoops_RGIGA->_hoops_CAHGA;

		dc->_hoops_CRIGA = _hoops_RGIGA->next;
		FREE (_hoops_RGIGA, _hoops_RAHGA);
	}
}


HC_INTERFACE Key HC_Compute_Capping_Shell (
	int						key_count,
	Key const *				_hoops_CHSGA,
	float const *			_hoops_SHSGA)
{
	_hoops_PAPPR context("Compute_Capping_Shell");

	// _hoops_ASIGA _hoops_SIGP
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Capping_Shell () */\n");
		//_hoops_GISGA (_hoops_RISGA (_hoops_IRAP, "_hoops_AISGA (_hoops_PISGA (%_hoops_APCAR), ", _hoops_SIC));
		//_hoops_GISGA (_hoops_HISGA (_hoops_IRAP, "%_hoops_IISGA);\_hoops_ACHP", _hoops_CISGA));
	);


	_hoops_ARPA const *			_hoops_SHPA = (_hoops_ARPA const *)_hoops_SHSGA;
	bool					_hoops_AGIGA = false;
	int						_hoops_SISGA = 0;
	Key						_hoops_CRSGA;

	_hoops_RAHGA *	_hoops_RGIGA;
	ZALLOC (_hoops_RGIGA, _hoops_RAHGA);
 	_hoops_RGIGA->_hoops_AAHGA = 0;
	_hoops_RGIGA->_hoops_PICHR = POOL_NEW(context->memory_pool, _hoops_IRHGA)(context->memory_pool);
	_hoops_RGIGA->_hoops_CAHGA = POOL_NEW(context->memory_pool, _hoops_GAHGA)(context->memory_pool);
	_hoops_RGIGA->_hoops_GPHGA = POOL_NEW(context->memory_pool, _hoops_CRHGA)(context->memory_pool);
	_hoops_RGIGA->faces = POOL_NEW(context->memory_pool, _hoops_SRHGA)(context->memory_pool);


	while (key_count-- > 0) {
		Key		key = *_hoops_CHSGA++;	/* _hoops_HAR _hoops_ICIC _hoops_IS _hoops_SGH *_hoops_SISR++ _hoops_SSPP _hoops_GGR _hoops_GCSGA */

		_hoops_CSPPR();
		Polyhedron *	_hoops_SPHPR = (Polyhedron *)_hoops_RCSSR (context, key);

		if (_hoops_SPHPR != null) {
			if (_hoops_SPHPR->type == _hoops_SCIP || _hoops_SPHPR->type == _hoops_GSIP) {
				
				_hoops_CRCP *	_hoops_ARPGR;
				if ((_hoops_ARPGR = _hoops_SPHPR->owner) != null)
					_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(context->thread_id);

				Tristrip const *	tristrip;

				if (_hoops_SPHPR->tristrips == null)
					HI_Assemble_3D_Tristrips  (_hoops_SPHPR, (_hoops_SARHR)~0, false);

				if ((tristrip = _hoops_SPHPR->tristrips) != null) do {
					if (!BIT (tristrip->face_attributes.flags, _hoops_HSIPR))
						_hoops_GGIGA (tristrip, _hoops_SPHPR->points, _hoops_SHPA, _hoops_RGIGA, 1.0e-10f, &_hoops_AGIGA);
				} while ((tristrip = tristrip->next) != null);

				if (_hoops_ARPGR != null)
					_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
			}
			else
				/* _hoops_CGH _hoops_SHH _hoops_SHSS _hoops_IS _hoops_RGHH _hoops_RRI _hoops_RRCPR-_hoops_PII _hoops_ARAR, _hoops_HIH _hoops_IH _hoops_HA */
				++_hoops_SISGA;
		}
		else
			++_hoops_SISGA;

		_hoops_IRRPR();
	}

	if (_hoops_SISGA > 0) {
		/* _hoops_CGH _hoops_CAHP _hoops_IRS _hoops_ASRHR _hoops_GPSRR */
	}

	_hoops_CRSGA = _hoops_CGSGA (0, context, true, 0, _hoops_HICS(), false, _hoops_RGIGA, null, 0.001f);

	while (_hoops_RGIGA != 0) {
 		_hoops_RAHGA *	temp = _hoops_RGIGA;

		_hoops_RGIGA = temp->next;

		delete temp->_hoops_PICHR;
		delete temp->_hoops_CAHGA;
		delete temp->_hoops_GPHGA;
		delete temp->faces;
		FREE (temp, _hoops_RAHGA);
	}

	return _hoops_CRSGA;
}

#endif


