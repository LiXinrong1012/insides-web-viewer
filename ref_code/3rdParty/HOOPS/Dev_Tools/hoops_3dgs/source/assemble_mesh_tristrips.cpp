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
 * $Id: obf_tmp.txt 1.100 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hi_proto.h"
#include "hpserror.h"


typedef struct _hoops_PSAHR {
	struct _hoops_PSAHR		*_hoops_CGHPR,
								*_hoops_SGHPR,
								*up;
	struct _hoops_PSAHR		*_hoops_GRHPR;
	int							_hoops_IICPR,
								_hoops_HSAHR,
								*_hoops_ISAHR,
								_hoops_CSAHR;

	One_Face_Attributes		face_attributes; /*(_hoops_CGHI _hoops_GGR _hoops_AGIR _hoops_PISC _hoops_SPCC)*/
}		_hoops_SSAHR;



GLOBAL_FUNCTION void HI_Assemble_Mesh_Vertex_Normals (
	_hoops_AIHPR					*_hoops_PIHPR) 
{
	Vector				*_hoops_GGPHR;
	_hoops_ARPA				*_hoops_HRAHR;
	Local_Vertex_Flags	*flags;
	int						_hoops_HIHPR;
	int						rows;
	int						_hoops_SSIPR = (_hoops_PIHPR->columns - 1) * 2;

	if (_hoops_PIHPR->local_vertex_attributes.explicit_normal_count ==
		_hoops_PIHPR->point_count + _hoops_PIHPR->_hoops_GCRHR)
		/* _hoops_IRAHR */
		return;

	if (_hoops_PIHPR->local_vertex_attributes.normals == null)
		HI_Initialize_Vertex_Attributes ((Polyhedron *)_hoops_PIHPR, LVA_EXPLICIT_NORMAL, 0);

	_hoops_GGPHR = _hoops_PIHPR->local_vertex_attributes.normals;

	if (!BIT (_hoops_PIHPR->polyhedron_flags, PHF_FACE_NORMALS_VALID))
		HI_Assemble_Face_Normals ((Polyhedron *)_hoops_PIHPR);
	_hoops_HRAHR = _hoops_PIHPR->local_face_attributes.normals;

#define _hoops_GRAHR(_hoops_PCAP,src) ((void)((_hoops_PCAP)->x = (src)->x, (_hoops_PCAP)->y = (src)->y, (_hoops_PCAP)->z = (src)->z))
#define _hoops_RRAHR(_hoops_ARAHR,add)   ((void)((_hoops_ARAHR)->x += (add)->x, (_hoops_ARAHR)->y += (add)->y, (_hoops_ARAHR)->z += (add)->z))

	if (_hoops_PIHPR->local_vertex_attributes.explicit_normal_count == 0) {
		/* _hoops_PRPC _hoops_RAAP _hoops_RPIA */
		_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
		/* _hoops_AIAH _hoops_SCGA */
		++_hoops_GGPHR;

		/* _hoops_PRPC _hoops_GAGHR */
		_hoops_HIHPR = _hoops_PIHPR->columns - 2;
		_hoops_RGGA (--_hoops_HIHPR < 0) {
			_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			++_hoops_HRAHR;
			_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			++_hoops_HRAHR;
			_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			(void)HI_Normalize (_hoops_GGPHR);
			++_hoops_GGPHR;
		}

		/* _hoops_PRPC _hoops_RPHR _hoops_RPIA */
		_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
		++_hoops_HRAHR;
		_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
		(void)HI_Normalize (_hoops_GGPHR);
		_hoops_HRAHR += 1 - _hoops_SSIPR;
		++_hoops_GGPHR;

		rows = _hoops_PIHPR->rows - 2;
		_hoops_RGGA (--rows < 0) {
			/* _hoops_RAAP _hoops_PIHP */
			_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			++_hoops_HRAHR;
			_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			_hoops_HRAHR += _hoops_SSIPR - 1;
			_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			(void)HI_Normalize (_hoops_GGPHR);
			_hoops_HRAHR -= _hoops_SSIPR - 1;
			++_hoops_GGPHR;

			/* _hoops_GHCPR */
			_hoops_HIHPR = _hoops_PIHPR->columns - 2;
			_hoops_RGGA (--_hoops_HIHPR < 0) {
				_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				++_hoops_HRAHR;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				++_hoops_HRAHR;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				_hoops_HRAHR += _hoops_SSIPR - 3;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				++_hoops_HRAHR;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				++_hoops_HRAHR;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				(void)HI_Normalize (_hoops_GGPHR);
				_hoops_HRAHR -= _hoops_SSIPR - 1;
				++_hoops_GGPHR;
			}

			/* _hoops_RPHR _hoops_PIHP */
			_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			_hoops_HRAHR += _hoops_SSIPR - 1;
			_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			++_hoops_HRAHR;
			_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			(void)HI_Normalize (_hoops_GGPHR);
			_hoops_HRAHR -= _hoops_SSIPR - 1;
			++_hoops_GGPHR;
		}

		/* _hoops_SCIA _hoops_RAAP _hoops_RPIA */
		_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
		++_hoops_HRAHR;
		_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
		(void)HI_Normalize (_hoops_GGPHR);
		++_hoops_GGPHR;

		/* _hoops_SCIA _hoops_GAGHR */
		_hoops_HIHPR = _hoops_PIHPR->columns - 2;
		_hoops_RGGA (--_hoops_HIHPR < 0) {
			_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			++_hoops_HRAHR;
			_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			++_hoops_HRAHR;
			_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			(void)HI_Normalize (_hoops_GGPHR);
			++_hoops_GGPHR;
		}

		/* _hoops_SCIA _hoops_RPHR _hoops_RPIA */
		_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
		/* _hoops_AIAH _hoops_SCGA */
	}
	else {
		flags = _hoops_PIHPR->local_vertex_attributes.flags;

		/* _hoops_PRPC _hoops_RAAP _hoops_RPIA */
		if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
			_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			/* _hoops_AIAH _hoops_SCGA */
		}
		++_hoops_GGPHR;
		++flags;

		/* _hoops_PRPC _hoops_GAGHR */
		_hoops_HIHPR = _hoops_PIHPR->columns - 2;
		_hoops_RGGA (--_hoops_HIHPR < 0) {
			if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
				_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				++_hoops_HRAHR;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				++_hoops_HRAHR;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				(void)HI_Normalize (_hoops_GGPHR);
			}
			else
				_hoops_HRAHR += 2;
			++_hoops_GGPHR;
			++flags;
		}

		/* _hoops_PRPC _hoops_RPHR _hoops_RPIA */
		if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
			_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			++_hoops_HRAHR;
			_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			(void)HI_Normalize (_hoops_GGPHR);
			_hoops_HRAHR += 1 - _hoops_SSIPR;
		}
		else
			_hoops_HRAHR += 2 - _hoops_SSIPR;
		++_hoops_GGPHR;
		++flags;

		rows = _hoops_PIHPR->rows - 2;
		_hoops_RGGA (--rows < 0) {
			/* _hoops_RAAP _hoops_PIHP */
			if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
				_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				++_hoops_HRAHR;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				_hoops_HRAHR += _hoops_SSIPR - 1;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				(void)HI_Normalize (_hoops_GGPHR);
				_hoops_HRAHR -= _hoops_SSIPR - 1;
			}
			else
				++_hoops_HRAHR;
			++_hoops_GGPHR;
			++flags;

			/* _hoops_GHCPR */
			_hoops_HIHPR = _hoops_PIHPR->columns - 2;
			_hoops_RGGA (--_hoops_HIHPR < 0) {
				if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
					_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
					++_hoops_HRAHR;
					_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
					++_hoops_HRAHR;
					_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
					_hoops_HRAHR += _hoops_SSIPR - 3;
					_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
					++_hoops_HRAHR;
					_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
					++_hoops_HRAHR;
					_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
					(void)HI_Normalize (_hoops_GGPHR);
					_hoops_HRAHR -= _hoops_SSIPR - 1;
				}
				else
					_hoops_HRAHR += 2;
				++_hoops_GGPHR;
				++flags;
			}

			/* _hoops_RPHR _hoops_PIHP */
			if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
				_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				_hoops_HRAHR += _hoops_SSIPR - 1;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				++_hoops_HRAHR;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				(void)HI_Normalize (_hoops_GGPHR);
				_hoops_HRAHR -= _hoops_SSIPR - 1;
			}
			else
				++_hoops_HRAHR;
			++_hoops_GGPHR;
			++flags;
		}

		/* _hoops_SCIA _hoops_RAAP _hoops_RPIA */
		if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
			_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			++_hoops_HRAHR;
			_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			(void)HI_Normalize (_hoops_GGPHR);
		}
		else
			++_hoops_HRAHR;
		++_hoops_GGPHR;
		++flags;

		/* _hoops_SCIA _hoops_GAGHR */
		_hoops_HIHPR = _hoops_PIHPR->columns - 2;
		_hoops_RGGA (--_hoops_HIHPR < 0) {
			if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
				_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				++_hoops_HRAHR;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				++_hoops_HRAHR;
				_hoops_RRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
				(void)HI_Normalize (_hoops_GGPHR);
			}
			else
				_hoops_HRAHR += 2;
			++_hoops_GGPHR;
			++flags;
		}

		/* _hoops_SCIA _hoops_RPHR _hoops_RPIA */
		if (!BIT (*flags, LVA_EXPLICIT_NORMAL)) {
			_hoops_GRAHR (_hoops_GGPHR, (Vector *)_hoops_HRAHR);
			/* _hoops_AIAH _hoops_SCGA */
		}
	}
}




#define _hoops_RGPHR(x) ((x)->_hoops_CSAHR)


local void _hoops_CSHPR (
	_hoops_SSAHR			*_hoops_AGPHR,
	_hoops_SSAHR			**_hoops_SSHPR) {
	_hoops_SSAHR			*node;

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
		if (_hoops_SAGI (_hoops_AGPHR->face_attributes, node->face_attributes, ~0)) {
			_hoops_AGPHR->up = node->up;
			_hoops_AGPHR->_hoops_GRHPR = node->_hoops_GRHPR;
			node->_hoops_GRHPR = _hoops_AGPHR;
			return;
		}
#ifndef _hoops_PGPHR
		else if (_hoops_HGPHR (_hoops_AGPHR->face_attributes, node->face_attributes)) {
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



GLOBAL_FUNCTION void HI_Assemble_Mesh_Tristrips (
	_hoops_AIHPR *					_hoops_PIHPR,
	_hoops_SARHR	_hoops_HGSPR,
	bool					_hoops_PCRHR) {

	/* _hoops_RH _hoops_HGRH _hoops_ARI _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_IGPHR - _hoops_CGPHR _hoops_GA'_hoops_RA _hoops_PICP _hoops_AHCA
	 * _hoops_GHGA _hoops_PAII _hoops_GPHA _hoops_ASGA _hoops_PPR _hoops_PAII _hoops_SGPHR _hoops_GIRP,
	 * _hoops_HIH _hoops_GRPHR *_hoops_AA* _hoops_PICP - _hoops_HIS _hoops_RH _hoops_PSCH _hoops_HS _hoops_RPII _hoops_RRPHR
	 * _hoops_ARPHR _hoops_GIRP.
	 */

	if (_hoops_PCRHR)
		HI_Assemble_Mesh_Vertex_Normals (_hoops_PIHPR);

	if (!_hoops_HGSPR)
		return;


#	define _hoops_PRPHR		10 /* _hoops_HRPHR _hoops_IIGR _hoops_GHGA _hoops_IRPHR _hoops_CRPHR -
									* _hoops_CACH _hoops_SRPHR _hoops_CAPP _hoops_GAPHR "_hoops_RAPHR."
									*/

	if (_hoops_PIHPR->local_face_attributes._hoops_SGRHR == 0 &&
		!ANYBIT(_hoops_PIHPR->polyhedron_flags, _hoops_APRHR|_hoops_CGRHR)) {
		Tristrip *		ts;

		ZALLOC (ts, Tristrip);
		_hoops_ICAI (ts);
		ts->next = null;
		_hoops_PIHPR->tristrips = ts;

		_hoops_AAPHR (ts->face_attributes);
		ts->face_attributes.flags |= _hoops_PIHPR->local_face_attributes._hoops_GARHR[0];
		ts->same_colors = _hoops_PAIPR;

		if (_hoops_PIHPR->rows <= _hoops_PIHPR->columns + _hoops_PRPHR) {
			/* _hoops_ARAS _hoops_RHIR _hoops_GAGHR _hoops_HPP _hoops_GAGHR */

			int				*_hoops_RPIPR, *_hoops_PAPHR, *_hoops_AAGR,
										face,
										_hoops_ISPI,
										_hoops_CSPI,
										_hoops_IHRHR;

			/* _hoops_AIRP =
						_hoops_PHI _hoops_IIGR _hoops_RSSI (_hoops_HAPHR _hoops_IIGR _hoops_GIHA-1 * _hoops_IAPHR _hoops_IIGR _hoops_GIHA-1 * 2)
						_hoops_IPSH _hoops_PHI _hoops_IIGR _hoops_GCHRR _hoops_GAGHR _hoops_RRGPR (_hoops_HAPHR _hoops_IIGR _hoops_GIHA - 1) _hoops_SISR 2 _hoops_CAIPR _hoops_GRR (_hoops_GPHA 1 _hoops_PPR 2)
			 */

			ts->_hoops_PHHA = _hoops_PIHPR->rows - 1;
			ts->total = ((_hoops_PIHPR->columns - 1) * 2 + 2) * (_hoops_PIHPR->rows - 1);

			ALLOC_ARRAY (ts->lengths, ts->_hoops_PHHA, int);
			ALLOC_ARRAY (ts->_hoops_AIHA, ts->total, int);
			ALLOC_ARRAY (ts->face_indices, ts->total, int);
			ts->lengths_allocated = ts->_hoops_PHHA;
			ts->_hoops_IPII = ts->_hoops_SGAHR = ts->total;
			ts->_hoops_RAHH |= _hoops_AAHH;

			_hoops_AAGR = ts->lengths;
			_hoops_RPIPR = ts->_hoops_AIHA;
			_hoops_PAPHR = ts->face_indices;

			face = -1;
			_hoops_ISPI = 0;
			_hoops_CSPI = _hoops_PIHPR->columns;
			_hoops_IHRHR = _hoops_PIHPR->rows - 1;

			do {
				int				_hoops_APCPR = _hoops_PIHPR->columns - 1;

				*_hoops_AAGR++ = 2 * _hoops_PIHPR->columns;

				*_hoops_RPIPR++ = _hoops_ISPI;
				*_hoops_RPIPR++ = _hoops_CSPI;
				*_hoops_PAPHR++ = 0;
				*_hoops_PAPHR++ = 0;

				do {
					*_hoops_RPIPR++ = ++_hoops_ISPI;
					*_hoops_PAPHR++ = ++face;
					*_hoops_RPIPR++ = ++_hoops_CSPI;
					*_hoops_PAPHR++ = ++face;
				} _hoops_RGGA (--_hoops_APCPR == 0);

				++_hoops_ISPI; ++_hoops_CSPI;						/* _hoops_ARGAR _hoops_IS _hoops_RH _hoops_SPS _hoops_GAGHR */
			} _hoops_RGGA (--_hoops_IHRHR == 0);
		}
		else {
			/* _hoops_ARAS _hoops_RHIR _hoops_PIHP _hoops_HPP _hoops_PIHP */

			/* _hoops_PAGA: _hoops_HGI _hoops_CAPHR _hoops_HIGR _hoops_HRGR _hoops_GGR _hoops_IRS _hoops_SAGHR _hoops_AGR. */
			int				*_hoops_RPIPR, *_hoops_PAPHR, *_hoops_AAGR,
										face,
										_hoops_SAPHR,
										_hoops_GPPHR,
										_hoops_SSIPR,
										_hoops_RPPHR,
										column,
										_hoops_APPHR = _hoops_PIHPR->columns - 1;

			/* _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_PPPHR. _hoops_HASRR _hoops_HSSP-_hoops_RSSP/_hoops_HPPHR-
			 * _hoops_RGSP _hoops_IPPHR _hoops_CPPHR _hoops_SGS _hoops_HSP _hoops_AHHR _hoops_SPPHR _hoops_SHH _hoops_GHSAR _hoops_IS
			 * _hoops_ARAS _hoops_HII _hoops_GPHA 1 _hoops_IS _hoops_GPHA 0 _hoops_IS _hoops_GPHA "0+_hoops_IAPHR". _hoops_PS _hoops_PAH'_hoops_RA
			 * _hoops_GHPHR _hoops_IRS _hoops_IRPHR _hoops_CRHH _hoops_APHR _hoops_HII _hoops_HGPP _hoops_IRS _hoops_HSP. _hoops_PHGP
			 * _hoops_SR _hoops_CCPH _hoops_PSAP _hoops_IRS _hoops_SCPH _hoops_HII _hoops_GRR _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_IRPHR _hoops_PIHP
			 * _hoops_PPR _hoops_PPSI _hoops_CAPR _hoops_GGR _hoops_PAII _hoops_HAII _hoops_RHSAR _hoops_CRPHR. _hoops_RAPHR.
			 */

			/* _hoops_PSHR _hoops_HIGR-_hoops_SPCC _hoops_RHPHR _hoops_GAR _hoops_ARRS, _hoops_AHSAR _hoops_HAPHR _hoops_PPR
			 * _hoops_IAPHR _hoops_CHR _hoops_AHPHR, _hoops_PPR _hoops_SR _hoops_RRP 1 _hoops_IHH _hoops_GPHA _hoops_PSAI _hoops_IS
			 * _hoops_SIAPR _hoops_RAS _hoops_RH _hoops_PHPHR _hoops_SCPH _hoops_APHR _hoops_GRR _hoops_PIHP.
			 */
			ts->_hoops_PHHA = 2 * (_hoops_PIHPR->columns - 1);
			ts->total = ((_hoops_PIHPR->rows - 1) * 2 + 2 + 2) * _hoops_APPHR;

			ALLOC_ARRAY (ts->lengths, ts->_hoops_PHHA, int);
			ALLOC_ARRAY (ts->_hoops_AIHA, ts->total, int);
			ALLOC_ARRAY (ts->face_indices, ts->total, int);
			ts->lengths_allocated = ts->_hoops_PHHA;
			ts->_hoops_IPII = ts->_hoops_SGAHR = ts->total;
			ts->_hoops_RAHH |= _hoops_AAHH;

			_hoops_AAGR = ts->lengths;
			_hoops_RPIPR = ts->_hoops_AIHA;
			_hoops_PAPHR = ts->face_indices;

			_hoops_GPPHR = _hoops_PIHPR->columns;
			_hoops_SSIPR = 2*_hoops_APPHR;
			_hoops_RPPHR = (_hoops_PIHPR->face_count - 1) - _hoops_SSIPR;

#			ifdef _hoops_CGSPR
				if (_hoops_PIHPR->rows < 3)
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									   "This can't be happening");
#			endif

			/* _hoops_SRS, _hoops_AA _hoops_GRR _hoops_PIHP *_hoops_HHPHR* _hoops_RH _hoops_SRS _hoops_SCPH */
			column = 0;
			do {
				_hoops_SAPHR = column + _hoops_GPPHR;
				face = 2*column;

				*_hoops_AAGR++ = 2 * _hoops_PIHPR->rows - 1;
				*_hoops_RPIPR++ = column + 1;
				*_hoops_RPIPR++ = _hoops_SAPHR;
				*_hoops_PAPHR++ = 0;
				*_hoops_PAPHR++ = 0;

				_hoops_PCCAR {
					*_hoops_RPIPR++ = _hoops_SAPHR + 1;
					*_hoops_PAPHR++ = face + 1;
					face += _hoops_SSIPR;
					_hoops_SAPHR += _hoops_GPPHR;
					*_hoops_RPIPR++ = _hoops_SAPHR;
					*_hoops_PAPHR++ = face;

					if (face > _hoops_RPPHR)
						break;
				}
				*_hoops_RPIPR++ = _hoops_SAPHR + 1;
				*_hoops_PAPHR++ = face + 1;
			}
			_hoops_RGGA (++column == _hoops_APPHR);

			/* _hoops_HA _hoops_GGCR _hoops_RH _hoops_SRS _hoops_SCPH _hoops_HII _hoops_GRR _hoops_PIHP */
			column = 0;
			do {
				_hoops_SAPHR = column + _hoops_GPPHR;
				face = 2*column;

				*_hoops_AAGR++ = 3;
				*_hoops_RPIPR++ = column + 1;
				*_hoops_RPIPR++ = column;
				*_hoops_RPIPR++ = _hoops_SAPHR;
				*_hoops_PAPHR++ = 0;
				*_hoops_PAPHR++ = 0;
				*_hoops_PAPHR++ = face;
			}
			_hoops_RGGA (++column == _hoops_APPHR);
		}
	}
	else {		/* _hoops_IIH *_hoops_CHR* _hoops_HSP _hoops_AIRC _hoops_AARI - _hoops_IHPHR _hoops_HRGR _hoops_ICCAR _hoops_HIS _hoops_ACIPR */
		int				*list;
		int				*_hoops_CHPHR;
		int				_hoops_SHPHR;
		_hoops_SSAHR	*temps = null;

		_hoops_SHPHR = _hoops_PIHPR->face_count * 2;
		ALLOC_ARRAY_CACHED (list, _hoops_SHPHR, int);
		_hoops_CHPHR = list;

		if (_hoops_PIHPR->rows <= _hoops_PIHPR->columns + _hoops_PRPHR) {
			/* _hoops_GIPHR _hoops_PPR _hoops_RIPHR _hoops_GAGHR _hoops_HPP _hoops_GAGHR */

			/* _hoops_IPCP _hoops_HSPR _hoops_IGCPR _hoops_CHR _hoops_GGR _hoops_IRS _hoops_SAGHR _hoops_AGR. */
			_hoops_SSAHR					*_hoops_AGPHR;
			Local_Face_Attributes		*_hoops_CPRI;
			int								_hoops_SSPI,
														_hoops_CSPI,
														_hoops_ISPI,
														_hoops_IIRHR,
														_hoops_AIPHR,
														_hoops_HPCPR,
														_hoops_SSIPR;

			_hoops_ISPI = 0;
			_hoops_CSPI = _hoops_PIHPR->columns;
			_hoops_SSPI = 1;
			_hoops_AIPHR = 0;

			_hoops_CPRI = &_hoops_PIHPR->local_face_attributes;
			_hoops_HPCPR = _hoops_PIHPR->rows - 1;
			_hoops_IIRHR = _hoops_SSIPR = 2*_hoops_CSPI - 2;

			_hoops_PCCAR {
				ALLOC (_hoops_AGPHR, _hoops_SSAHR);
				_hoops_AAPHR (_hoops_AGPHR->face_attributes);
				_hoops_PIPHR (_hoops_CPRI, _hoops_AIPHR, _hoops_AGPHR->face_attributes);

				/*
				 * _hoops_CISA _hoops_GGR _hoops_RH _hoops_CGGR _hoops_GPHA _hoops_HIGR
				 */
				_hoops_AGPHR->_hoops_ISAHR = list;
				*list++ = _hoops_SSPI;
				*list++ = _hoops_AIPHR;
				_hoops_AGPHR->_hoops_CSAHR = 2;

				if (_hoops_AIPHR & 1) {
					/* _hoops_HGI _hoops_HRGR _hoops_IRS '_hoops_HPIPR' _hoops_HSP, _hoops_HII _hoops_RH _hoops_PPSR _hoops_IIGR _hoops_RAR
					 * _hoops_IIGR _hoops_HSSP-_hoops_RSSP. _hoops_PISPR _hoops_SCH _hoops_GGR _hoops_IRS _hoops_CGGR _hoops_HPIPR,
					 * _hoops_HIH _hoops_GA'_hoops_RA _hoops_SAS _hoops_SCH. _hoops_RAPHR.
					 */
					_hoops_AGPHR->_hoops_IICPR = _hoops_CSPI;
					_hoops_AGPHR->_hoops_HSAHR = _hoops_ISPI;

					/* _hoops_PH _hoops_CPS _hoops_IS _hoops_RH _hoops_SPS _hoops_HSP */
					_hoops_ISPI = _hoops_CSPI; _hoops_CSPI = _hoops_SSPI; _hoops_SSPI = _hoops_ISPI + 1;
					++_hoops_AIPHR;

					if (--_hoops_IIRHR == 0) {
						/* _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_GAGHR */
						if (--_hoops_HPCPR == 0) {
							_hoops_CSHPR (_hoops_AGPHR, &temps);
							goto _hoops_HIPHR;
						}

						++_hoops_ISPI; ++_hoops_CSPI; _hoops_SSPI = _hoops_ISPI + 1;
						_hoops_IIRHR = _hoops_SSIPR;
					}
				}
				else {
					/* _hoops_SIHA _hoops_IRS _hoops_GSSR _hoops_CGGR */
					_hoops_AGPHR->_hoops_IICPR = _hoops_ISPI;
					_hoops_AGPHR->_hoops_HSAHR = _hoops_CSPI;

					_hoops_PCCAR {
						/* _hoops_PH _hoops_CPS _hoops_IS _hoops_RH _hoops_SPS _hoops_HSP */
						_hoops_ISPI = _hoops_CSPI; _hoops_CSPI = _hoops_SSPI; _hoops_SSPI = _hoops_ISPI + 1;
						++_hoops_AIPHR;

						if (--_hoops_IIRHR == 0) {
							/* _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_GAGHR */
							if (--_hoops_HPCPR == 0) {
								_hoops_CSHPR (_hoops_AGPHR, &temps);
								goto _hoops_HIPHR;
							}

							++_hoops_ISPI; ++_hoops_CSPI; _hoops_SSPI = _hoops_ISPI + 1;
							_hoops_IIRHR = _hoops_SSIPR;
							break;
						}

						if (!_hoops_IIPHR (_hoops_CPRI, _hoops_AIPHR,
																  _hoops_AGPHR->face_attributes))
							break;

						*list++ = _hoops_SSPI;
						*list++ = _hoops_AIPHR;
						_hoops_AGPHR->_hoops_CSAHR += 2;
					}
				}

				_hoops_CSHPR (_hoops_AGPHR, &temps);
			}
			_hoops_HIPHR:;
		}
		else {
			/* _hoops_GIPHR _hoops_PPR _hoops_RIPHR _hoops_PIHP _hoops_HPP _hoops_PIHP */

			/* _hoops_IPCP _hoops_HSPR _hoops_IGCPR _hoops_CHR _hoops_GGR _hoops_IRS _hoops_SAGHR _hoops_AGR. */
			_hoops_SSAHR					*_hoops_AGPHR;
			Local_Face_Attributes		*_hoops_CPRI;
			int								_hoops_SSPI,
														_hoops_CSPI,
														_hoops_ISPI,
														_hoops_CIPHR,
														_hoops_AIPHR,
														column,
														_hoops_SIPHR,
														_hoops_GCPHR,
														columns;

			columns = _hoops_PIHPR->columns;
			_hoops_GCPHR = 2*(columns - 1) - 1;
			/* (_hoops_SR _hoops_PHHR _hoops_RPHR _hoops_IS _hoops_RAAP _hoops_IS _hoops_ASSS _hoops_RCPHR _hoops_RPGP _hoops_ACSRR _hoops_AHHR) */
			column = columns - 2;
			_hoops_ISPI = column;
			_hoops_CSPI = _hoops_ISPI + 1;
			_hoops_SSPI = _hoops_ISPI + columns;
			_hoops_AIPHR = 2*column;
			_hoops_CPRI = &_hoops_PIHPR->local_face_attributes;
			_hoops_CIPHR = _hoops_SIPHR = 2*(_hoops_PIHPR->rows - 1);

			_hoops_PCCAR {
				ALLOC (_hoops_AGPHR, _hoops_SSAHR);
				_hoops_AAPHR (_hoops_AGPHR->face_attributes);
				_hoops_PIPHR (_hoops_CPRI, _hoops_AIPHR, _hoops_AGPHR->face_attributes);

				/* _hoops_CISA _hoops_GGR _hoops_RH _hoops_CGGR _hoops_GIHA */
				_hoops_AGPHR->_hoops_ISAHR = list;
				*list++ = _hoops_SSPI;
				*list++ = _hoops_AIPHR;
				_hoops_AGPHR->_hoops_CSAHR = 2;

				if (!(_hoops_AIPHR & 1)) {
					/* _hoops_HGI _hoops_HRGR _hoops_IRS '_hoops_HPIPR' _hoops_HSP, _hoops_HII _hoops_RH _hoops_PPSR _hoops_IIGR _hoops_RAR
					 * _hoops_IIGR _hoops_HSSP-_hoops_RSSP. _hoops_PISPR _hoops_SCH _hoops_GGR _hoops_IRS _hoops_CGGR _hoops_HPIPR,
					 * _hoops_HIH _hoops_GA'_hoops_RA _hoops_SAS _hoops_SCH. _hoops_RAPHR.
					 */
					_hoops_AGPHR->_hoops_IICPR = _hoops_CSPI;
					_hoops_AGPHR->_hoops_HSAHR = _hoops_ISPI;

					/* _hoops_PH _hoops_CPS _hoops_IS _hoops_RH _hoops_SPS _hoops_HSP */
					_hoops_ISPI = _hoops_CSPI; _hoops_CSPI = _hoops_SSPI; _hoops_SSPI = _hoops_ISPI + columns;
					++_hoops_AIPHR;

					if (--_hoops_CIPHR == 0) {
						/* _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_PIHP */
						if (--column < 0) {
							_hoops_CSHPR (_hoops_AGPHR, &temps);
							goto _hoops_ACPHR;
						}

						_hoops_ISPI = column;
						_hoops_CSPI = _hoops_ISPI + 1;
						_hoops_SSPI = _hoops_ISPI + columns;
						_hoops_AIPHR = 2*column;
						_hoops_CIPHR = _hoops_SIPHR;
					}
				}
				else {
					/* _hoops_SIHA _hoops_IRS _hoops_GSSR _hoops_CGGR */
					_hoops_AGPHR->_hoops_IICPR = _hoops_ISPI;
					_hoops_AGPHR->_hoops_HSAHR = _hoops_CSPI;

					_hoops_PCCAR {
						/* _hoops_PH _hoops_CPS _hoops_IS _hoops_RH _hoops_SPS _hoops_HSP */
						_hoops_ISPI = _hoops_CSPI; _hoops_CSPI = _hoops_SSPI; _hoops_SSPI = _hoops_ISPI + columns;

						if (_hoops_ISPI + 1 == _hoops_CSPI) {		/* _hoops_CCAH _hoops_SPR _hoops_HRGR _hoops_IRS _hoops_GSSC-_hoops_RAAP _hoops_HSP */
							_hoops_AIPHR += _hoops_GCPHR;
						}
						else
							++_hoops_AIPHR;

						if (--_hoops_CIPHR == 0) {
							/* _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_PIHP */
							if (--column < 0) {
								_hoops_CSHPR (_hoops_AGPHR, &temps);
								goto _hoops_ACPHR;
							}

							_hoops_ISPI = column;
							_hoops_CSPI = _hoops_ISPI + 1;
							_hoops_SSPI = _hoops_ISPI + columns;
							_hoops_AIPHR = 2*column;
							_hoops_CIPHR = _hoops_SIPHR;
							break;
						}

						if (!_hoops_IIPHR (_hoops_CPRI,
																  _hoops_AIPHR,
																  _hoops_AGPHR->face_attributes))
							break;

						*list++ = _hoops_SSPI;
						*list++ = _hoops_AIPHR;
						_hoops_AGPHR->_hoops_CSAHR += 2;
					}
				}

				_hoops_CSHPR (_hoops_AGPHR, &temps);
			}
			_hoops_ACPHR:;
		}

		/* _hoops_ARAS _hoops_RHIR _hoops_RH _hoops_IRHP-_hoops_HHIS _hoops_PSCS _hoops_RH _hoops_HPHR _hoops_CCGI */

		if (temps != null) {
			_hoops_SSAHR	*_hoops_AGPHR = temps;
			_hoops_SSAHR	*_hoops_PCPHR;

			do {
				Tristrip		*ts;
				_hoops_SSAHR	*_hoops_HCPHR;

				/* _hoops_SSS _hoops_IRS _hoops_RIIS */
				_hoops_PCCAR {
					if (_hoops_AGPHR->_hoops_CGHPR != null)
						_hoops_AGPHR = _hoops_AGPHR->_hoops_CGHPR;
					else if (_hoops_AGPHR->_hoops_SGHPR != null)
						_hoops_AGPHR = _hoops_AGPHR->_hoops_SGHPR;
					else
						break;
				}

				if ((_hoops_PCPHR = _hoops_AGPHR->up) != null) {
					if (_hoops_PCPHR->_hoops_CGHPR == _hoops_AGPHR)
						_hoops_PCPHR->_hoops_CGHPR = null;
					else
						_hoops_PCPHR->_hoops_SGHPR = null;
				}

				_hoops_HCPHR = _hoops_AGPHR;

				ZALLOC (ts, Tristrip);
				_hoops_ICAI (ts);
				ts->next = _hoops_PIHPR->tristrips;
				_hoops_PIHPR->tristrips = ts;
				ts->face_attributes = _hoops_AGPHR->face_attributes; 
				ts->same_colors = _hoops_PAIPR;

				/* _hoops_RPR _hoops_GH _hoops_RH _hoops_PHI _hoops_IIGR _hoops_IIRGR */
				{
					int		_hoops_PHHA = 0;

					do ++_hoops_PHHA;
					while ((_hoops_AGPHR = _hoops_AGPHR->_hoops_GRHPR) != null);
					ts->_hoops_PHHA = _hoops_PHHA;
				}
				_hoops_AGPHR = _hoops_HCPHR;

				ZALLOC_ARRAY (ts->lengths, ts->_hoops_PHHA, int);
				ts->lengths_allocated = ts->_hoops_PHHA;

				/* _hoops_HGCR _hoops_RH _hoops_IHHA _hoops_PPR _hoops_APSR _hoops_SPCC */
				{
					int		total = 0;
					int *	_hoops_IAIPR = ts->lengths;

					/*
					 * (1 _hoops_CAIPR _hoops_IH _hoops_GRR _hoops_RCHAR _hoops_GPHA;
					 *	2 _hoops_CAIPR _hoops_IH _hoops_RH _hoops_PGCR _hoops_APHR _hoops_GIHA)
					 */
					do {
						*_hoops_IAIPR = _hoops_AGPHR->_hoops_CSAHR/2 + 2;
						total += *_hoops_IAIPR++;
					} while ((_hoops_AGPHR = _hoops_AGPHR->_hoops_GRHPR) != null);
					ts->total = total;
				}
				_hoops_AGPHR = _hoops_HCPHR;

				ZALLOC_ARRAY (ts->_hoops_AIHA, ts->total, int);
				ZALLOC_ARRAY (ts->face_indices, ts->total, int);
				ts->_hoops_IPII = ts->_hoops_SGAHR = ts->total;
				ts->_hoops_RAHH |= _hoops_AAHH;

				{
					int *					_hoops_RPIPR = ts->_hoops_AIHA;
					int *					_hoops_PAPHR = ts->face_indices;
					_hoops_SSAHR *	_hoops_ICPHR = _hoops_AGPHR->_hoops_GRHPR;

					do {
						int *				in = _hoops_AGPHR->_hoops_ISAHR;

						*_hoops_RPIPR++ = _hoops_AGPHR->_hoops_IICPR;
						*_hoops_RPIPR++ = _hoops_AGPHR->_hoops_HSAHR;
						*_hoops_PAPHR++ = 0;
						*_hoops_PAPHR++ = 0;

						do {
							*_hoops_RPIPR++ = *in++;
							*_hoops_PAPHR++ = *in++;
						} while ((_hoops_AGPHR->_hoops_CSAHR -= 2) > 0);

						if (_hoops_AGPHR->face_attributes.region != ts->face_attributes.region)
							ts->face_attributes.region = -1;	/* _hoops_CCPHR */

						_hoops_ICPHR = _hoops_AGPHR->_hoops_GRHPR;
						FREE (_hoops_AGPHR, _hoops_SSAHR);
					} while ((_hoops_AGPHR = _hoops_ICPHR) != null);
				}
			} while ((_hoops_AGPHR = _hoops_PCPHR) != null);
		}

		FREE_ARRAY (_hoops_CHPHR, _hoops_SHPHR, int);
	}
}
