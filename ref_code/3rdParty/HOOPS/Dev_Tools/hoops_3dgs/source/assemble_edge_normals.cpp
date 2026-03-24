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
 * $Id: obf_tmp.txt 1.37 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hi_proto.h"
#include "hpserror.h"


#define _hoops_GRAHR(src, _hoops_PCAP) \
	((void)((_hoops_PCAP)->x = (src)->x, (_hoops_PCAP)->y = (src)->y, (_hoops_PCAP)->z = (src)->z))

#define _hoops_RRAHR(add, _hoops_ARAHR) \
	((void)((_hoops_ARAHR)->x += (add)->x, (_hoops_ARAHR)->y += (add)->y, (_hoops_ARAHR)->z += (add)->z))


GLOBAL_FUNCTION void HI_Assemble_Edge_Normals (
	Polyhedron					*_hoops_IPRI) {
	_hoops_RPGHR		*lea;
	Local_Face_Attributes		*_hoops_CPRI;
	Vector						*_hoops_PRAHR;
	_hoops_ARPA						*_hoops_HRAHR;
	_hoops_GHHPR				*flags;

	lea = &_hoops_IPRI->_hoops_IHHPR;
	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

	if (lea->explicit_normal_count == _hoops_IPRI->_hoops_SPHA) {
		return; /* _hoops_IRAHR... */
	}

	if (lea->normals == null)
		HI_Initialize_Edge_Attributes (_hoops_IPRI, _hoops_CRAHR);

	if (_hoops_CPRI->normals == null)
		HI_Assemble_Face_Normals (_hoops_IPRI);

	flags		= lea->flags;
	_hoops_PRAHR = lea->normals;
	_hoops_HRAHR = _hoops_CPRI->normals;

	if (_hoops_IPRI->type == _hoops_GSIP) {
		_hoops_AIHPR *			_hoops_PIHPR = (_hoops_AIHPR *)_hoops_IPRI;
		int				_hoops_HIHPR;
		int				rows;
		int				_hoops_SSIPR;

		_hoops_SSIPR = 2 * (_hoops_PIHPR->columns - 1);

		if (lea->explicit_normal_count == 0) {
			/*
			 * _hoops_PRPC _hoops_RAAP _hoops_RPIA
			 */
			_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
			/* _hoops_AIAH _hoops_SCGA */
			++_hoops_PRAHR;

			_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
			/* _hoops_AIAH _hoops_SCGA */
			++_hoops_PRAHR;

			/* _hoops_AIAH _hoops_SRAHR */
			++_hoops_PRAHR;

			_hoops_HRAHR += 2;

			/*
			 * _hoops_PRPC _hoops_GAGHR
			 */
			_hoops_HIHPR = _hoops_PIHPR->columns - 2;
			_hoops_RGGA (--_hoops_HIHPR < 0) {
				_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				/* _hoops_AIAH _hoops_SCGA */
				++_hoops_PRAHR;

				_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				--_hoops_HRAHR;
				_hoops_RRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				(void)HI_Normalize (_hoops_PRAHR);
				++_hoops_PRAHR;

				_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				--_hoops_HRAHR;
				_hoops_RRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				(void)HI_Normalize (_hoops_PRAHR);
				++_hoops_PRAHR;

				_hoops_HRAHR += 4;
			}

			/*
			 * _hoops_PRPC _hoops_RPHR _hoops_RPIA
			 */
			/* _hoops_AIAH _hoops_SRAHR */
			++_hoops_PRAHR;

			--_hoops_HRAHR;
			_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
			/* _hoops_AIAH _hoops_SCGA */
			++_hoops_PRAHR;

			_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
			--_hoops_HRAHR;
			_hoops_RRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
			(void)HI_Normalize (_hoops_PRAHR);
			++_hoops_PRAHR;

			_hoops_HRAHR += 2;

			/*
			 * _hoops_GHCPR
			 */
			rows = _hoops_PIHPR->rows - 2;
			_hoops_RGGA (--rows < 0) {
				/*
				 * _hoops_RAAP _hoops_PIHP
				 */
				_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				_hoops_HRAHR -= _hoops_SSIPR - 1;
				_hoops_RRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				(void)HI_Normalize (_hoops_PRAHR);
				++_hoops_PRAHR;
				_hoops_HRAHR += _hoops_SSIPR - 1;

				_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				/* _hoops_AIAH _hoops_SCGA */
				++_hoops_PRAHR;

				/* _hoops_AIAH _hoops_SRAHR */
				++_hoops_PRAHR;

				_hoops_HRAHR += 2;

				/*
				 * _hoops_GHCPR
				 */
				_hoops_HIHPR = _hoops_PIHPR->columns - 2;
				_hoops_RGGA (--_hoops_HIHPR < 0) {
					_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
					_hoops_HRAHR -= _hoops_SSIPR - 1;
					_hoops_RRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
					(void)HI_Normalize (_hoops_PRAHR);
					++_hoops_PRAHR;
					_hoops_HRAHR += _hoops_SSIPR - 1;

					_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
					--_hoops_HRAHR;
					_hoops_RRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
					(void)HI_Normalize (_hoops_PRAHR);
					++_hoops_PRAHR;

					_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
					--_hoops_HRAHR;
					_hoops_RRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
					(void)HI_Normalize (_hoops_PRAHR);
					++_hoops_PRAHR;

					_hoops_HRAHR += 4;
				}

				/*
				 * _hoops_RPHR _hoops_PIHP
				 */
				/* _hoops_AIAH _hoops_SRAHR */
				++_hoops_PRAHR;

				--_hoops_HRAHR;
				_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				/* _hoops_AIAH _hoops_SCGA */
				++_hoops_PRAHR;

				_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				--_hoops_HRAHR;
				_hoops_RRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				(void)HI_Normalize (_hoops_PRAHR);
				++_hoops_PRAHR;

				_hoops_HRAHR += 2;
			}

			/*
			 * _hoops_SCIA _hoops_GAGHR
			 */
			_hoops_HRAHR -= _hoops_SSIPR - 1;
			_hoops_HIHPR = _hoops_PIHPR->columns - 1;
			_hoops_RGGA (--_hoops_HIHPR < 0) {
				_hoops_GRAHR ((Vector *)_hoops_HRAHR, _hoops_PRAHR);
				/* _hoops_AIAH _hoops_SCGA, _hoops_RII 2 _hoops_AIAH _hoops_SRAHR */
				_hoops_PRAHR += 3;
				_hoops_HRAHR += 2;
			}

			/*
			 * _hoops_SCIA _hoops_RPHR _hoops_RPIA
			 */
			/* _hoops_HCR 3 _hoops_AIAH _hoops_SRAHR */

			if (_hoops_PRAHR != (lea->normals + _hoops_IPRI->_hoops_SPHA - 3))
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Edge normals unsuccessfully counted");
		}
		else {
		}
	}
	else /* _hoops_HGCPR */ {
		Shell alter *		_hoops_SPHPR = (Shell alter *)_hoops_IPRI;
		_hoops_CGCPR *		_hoops_SGCPR;
		int					face;
		int					remaining = _hoops_IPRI->_hoops_SPHA;

		if (_hoops_SPHPR->_hoops_SGCPR == null ||
			_hoops_SPHPR->_hoops_GRCPR == null) {
			/* (_hoops_ASAR)_hoops_ARPR _hoops_RRCPR _hoops_SPPR _hoops_IS _hoops_GCIS _hoops_ISCP _hoops_IHH _hoops_IAS-_hoops_IS-_hoops_RCHP _hoops_SIHC */
			if (_hoops_SPHPR->_hoops_GRCPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_GRCPR,
							_hoops_SPHPR->_hoops_SPHA,
							_hoops_RHHPR);
				_hoops_SPHPR->_hoops_GRCPR = null;
			}

			if (_hoops_SPHPR->_hoops_HHHPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_HHHPR,
							_hoops_SPHPR->point_count + 1,
							_hoops_RHHPR const *);
				_hoops_SPHPR->_hoops_HHHPR = null;
			}

			if (_hoops_SPHPR->_hoops_SGCPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_SGCPR,
							_hoops_SPHPR->_hoops_SPHA,
							_hoops_CGCPR);
				_hoops_SPHPR->_hoops_SGCPR = null;
			}

			HI_Create_Shell_Edges (_hoops_SPHPR, true);
		}

		_hoops_SGCPR = _hoops_SPHPR->_hoops_SGCPR;

		if (lea->explicit_normal_count == 0) {
			do {
				if (_hoops_SGCPR->_hoops_AIIPR > 0) {
					face = _hoops_SGCPR->_hoops_AIIPR;
					_hoops_GRAHR ((Vector *)&_hoops_HRAHR[face], _hoops_PRAHR);

					if (_hoops_SGCPR->_hoops_HIIPR > 0) {
						face = _hoops_SGCPR->_hoops_HIIPR;
						_hoops_RRAHR ((Vector *)&_hoops_HRAHR[face], _hoops_PRAHR);
						(void)HI_Normalize (_hoops_PRAHR);
					}
				}
				else {
					if (_hoops_SGCPR->_hoops_HIIPR > 0) {
						face = _hoops_SGCPR->_hoops_HIIPR;
						_hoops_GRAHR ((Vector *)&_hoops_HRAHR[face], _hoops_PRAHR);
					}
					else {
						_hoops_PRAHR->x =
						_hoops_PRAHR->y =
						_hoops_PRAHR->z = 0.0f;
					}
				}

				++_hoops_PRAHR;
				++_hoops_SGCPR;
			} _hoops_RGGA (--remaining == 0);
		}
		else {
			do if (!BIT (*flags++, _hoops_CRAHR)) {
				if (_hoops_SGCPR->_hoops_AIIPR > 0) {
					face = _hoops_SGCPR->_hoops_AIIPR;
					_hoops_GRAHR ((Vector *)&_hoops_HRAHR[face], _hoops_PRAHR);

					if (_hoops_SGCPR->_hoops_HIIPR > 0) {
						face = _hoops_SGCPR->_hoops_HIIPR;
						_hoops_RRAHR ((Vector *)&_hoops_HRAHR[face], _hoops_PRAHR);
						(void)HI_Normalize (_hoops_PRAHR);
					}
				}
				else {
					if (_hoops_SGCPR->_hoops_HIIPR > 0) {
						face = _hoops_SGCPR->_hoops_HIIPR;
						_hoops_GRAHR ((Vector *)&_hoops_HRAHR[face], _hoops_PRAHR);
					}
					else {
						_hoops_PRAHR->x =
						_hoops_PRAHR->y =
						_hoops_PRAHR->z = 0.0f;
					}
				}

				++_hoops_PRAHR;
				++_hoops_SGCPR;
			} _hoops_RGGA (--remaining == 0);
		}
	}

	_hoops_IPRI->polyhedron_flags |= _hoops_GAAHR;
}
