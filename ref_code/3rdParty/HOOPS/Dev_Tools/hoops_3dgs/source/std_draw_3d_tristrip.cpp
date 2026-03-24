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
 * $Id: obf_tmp.txt 1.322 2011-01-12 03:23:14 covey Exp $
 */
#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "phdraw.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hpserror.h"


#include "hidden.h" /* _hoops_SRSA _hoops_HGCR _hoops_IGICS _hoops_GGSR _hoops_IIGR _hoops_RGR _hoops_RGHR _hoops_PPR _hoops_HSCI _hoops_CAPRC */


#define _hoops_HRIIS(_hoops_CGICS, _hoops_PAGR)	\
	do {						\
		(_hoops_PAGR).x = (_hoops_CGICS).x;	\
		(_hoops_PAGR).y = (_hoops_CGICS).y;	\
		(_hoops_PAGR).z = (_hoops_CGICS).z;	\
	} while (0)


#ifndef DISABLE_DRAW_3D

local void _hoops_GIACP (
	Net_Rendition const & nr,
	Tristrip alter				*ts) {
	_hoops_ARPA alter					*_hoops_RIACP;
	Display_Context				*dc = (Display_Context*)nr->_hoops_SRA;

	if (dc->_hoops_PIACP < ts->face_count) {
		if (dc->_hoops_AIACP && dc->_hoops_PIACP > 0)
			FREE_ARRAY_ALIGNED (dc->_hoops_AIACP, dc->_hoops_PIACP, _hoops_ARPA, 16);
		POOL_ALLOC_ARRAY_ALIGNED_CACHED (dc->_hoops_AIACP, ts->face_count, _hoops_ARPA, 16, dc->memory_pool);
		dc->_hoops_PIACP = ts->face_count;
	}
	_hoops_RIACP = dc->_hoops_AIACP;

	if (ts == null ||
		ts->_hoops_GSCP == null ||
		(ts->_hoops_GSCP && ts->_hoops_GSCP->type >= _hoops_PRCP) ||
		((Polyhedron*)ts->_hoops_GSCP)->local_face_attributes.normals == null ) {
		bool		*done;

		/*
		 * _hoops_CPGP _hoops_HIACP _hoops_HRGR _hoops_IIACP, _hoops_RIP _hoops_RH _hoops_RSSI _hoops_GAR '_hoops_HAR _hoops_CPHR'
		 * _hoops_PPR _hoops_ISPR _hoops_RH _hoops_RIP _hoops_SPHR.
		 */
		POOL_ZALLOC_ARRAY_CACHED (done, ts->face_count, bool, dc->memory_pool);
		ZERO_ARRAY (_hoops_RIACP, ts->face_count, _hoops_ARPA);

		{
			_hoops_SGCC const &	_hoops_HSGA = nr->transform_rendition->_hoops_IPH;
			int							_hoops_PHHA = ts->_hoops_PHHA;
			int const *					lengths = ts->lengths;
			int const *					vi = ts->_hoops_AIHA;
			int const *					fi = ts->face_indices;
			_hoops_ARPA const *				normals = ts->_hoops_PRHH;
			int							_hoops_SGICS = 0;
			int							_hoops_RHSGI = 0;

			/* _hoops_RCPA _hoops_SICR _hoops_RH _hoops_IRHP _hoops_HSP _hoops_ASGA _hoops_IS _hoops_GHC, _hoops_SR _hoops_RRP _hoops_IRS
			 * _hoops_ISAR _hoops_PPSR _hoops_IH _hoops_GRR. _hoops_PS _hoops_AA _hoops_RGR _hoops_HPP _hoops_SIACP _hoops_RH
			 * _hoops_RCAPR _hoops_CRHH. _hoops_GCACP.
			 */
			while (_hoops_PHHA-- > 0) {
				int						length = 3;
				int						_hoops_HSPI;
				int						_hoops_ISPI;
				int						_hoops_CSPI;
				int						face;
				bool					_hoops_ASSRR = false;

				if (BIT (nr->transform_rendition->heuristics, _hoops_SASA))
					_hoops_ASSRR = true;

				if (lengths != null)
					length = *lengths++;

				if (vi != null) {
					_hoops_HSPI = *vi++;
					_hoops_ISPI = *vi++;
				}
				else {
					_hoops_HSPI = _hoops_SGICS++;
					_hoops_ISPI = _hoops_SGICS++;
				}

				if (fi)
					fi += 2;

				length -= 2;

				while (length-- > 0) {
					if (vi != null)
						_hoops_CSPI = *vi++;
					else
						_hoops_CSPI = _hoops_SGICS++;

					if (fi != null)
						face = *fi++;
					else
						face = _hoops_RHSGI++;

					/* _hoops_RARIR _hoops_GII _hoops_HSP'_hoops_GRI _hoops_IPPA _hoops_HGGC _hoops_PPSPR _hoops_AIPH. */
					if (!done[face]) {
						Vector *		normal;
						Vector			vector;
						bool			valid;

						if (normals != null) {
							normal = (Vector *)&normals[face];
							valid = true;
						}
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

							valid = HI_Normalize (&vector);

							if (_hoops_ASSRR) {
								vector.x = -vector.x;
								vector.y = -vector.y;
								vector.z = -vector.z;
							}
							normal = &vector;
						}

						if (valid) {
							HD_Compute_One_World_Plane (_hoops_HSGA, normal,
														&ts->points[_hoops_CSPI],
														&_hoops_RIACP[face]);
							done[face] = true;
						}
					}

					_hoops_HSPI = _hoops_ISPI;
					_hoops_ISPI = _hoops_CSPI;
					_hoops_ASSRR = !_hoops_ASSRR;
				}
			}
		}
		FREE_ARRAY (done, ts->face_count, bool);
	}
	else
		HD_Compute_World_Face_Planes (nr, ((Polyhedron*)ts->_hoops_GSCP), _hoops_RIACP);
}

local void _hoops_GRICS (
	Net_Rendition const &	nr,
	Tristrip alter *		ts) {
	_hoops_ARPA*					_hoops_AARHH = nr->_hoops_SRA->_hoops_PGPCP;
	int						_hoops_PAHCP = nr->_hoops_SRA->_hoops_PAHCP;
	Display_Context *		dc = (Display_Context*)nr->_hoops_SRA;

	if (_hoops_PAHCP < ts->point_count) {
		if (_hoops_AARHH)
			FREE_ARRAY (_hoops_AARHH, _hoops_PAHCP, _hoops_ARPA);
		POOL_ALLOC_ARRAY_CACHED (_hoops_AARHH, ts->point_count, _hoops_ARPA, dc->memory_pool);
		dc->_hoops_PGPCP = _hoops_AARHH;
		dc->_hoops_PAHCP = ts->point_count;
	}


	if (ts->_hoops_ICHA == null)
		ZERO_ARRAY (_hoops_AARHH, ts->point_count, _hoops_ARPA);
	else if (ts->_hoops_GSCP == null)
		HD_Compute_World_Vertex_Planes (nr, ts->point_count,
										ts->points, ts->_hoops_ICHA, _hoops_AARHH);
	else {
		//_hoops_IHRCP _hoops_RCIC			*_hoops_CPHAR = _hoops_HSAGA->_hoops_CPHAR;

		/*_hoops_RRICS (_hoops_SCII,
										_hoops_HSAGA->_hoops_RSHS,
										_hoops_CPHAR->_hoops_RSSA,
										_hoops_CPHAR->_hoops_SPSSI._hoops_ASGA,
										_hoops_ARICS);
										*/
		HD_Compute_World_Vertex_Planes (nr, ts->point_count,
										ts->points, ts->_hoops_ICHA, _hoops_AARHH);
	}
}

GLOBAL_FUNCTION int alter * HD_Get_Screen_Facings (
	Net_Rendition const &		nr,
	Tristrip const *			ts,
	int							face_count) {
	Polyhedron const *			_hoops_IPRI = null;
	Display_Context*			dc = (Display_Context*)nr->_hoops_SRA;

	/* _hoops_CGP _hoops_IIH _hoops_CHR _hoops_PSP _hoops_RSSI, _hoops_PSCR _hoops_IIH _hoops_CHR _hoops_PSP _hoops_GSSIA. */
	if (!face_count)
		return null;

	if (ts->_hoops_GSCP && ts->_hoops_GSCP->type <= _hoops_PRCP)
		_hoops_IPRI = (Polyhedron*)ts->_hoops_GSCP;

#if 1
	if (dc->_hoops_AIACP != null && dc->_hoops_PIACP >= face_count) {
		/* _hoops_HCACP */

		_hoops_GIACP (nr, (Tristrip alter *)ts);

		return HD_Generate_DC_Screen_Facings (nr, face_count,
											  dc->_hoops_AIACP, false);
	}
	else
#endif
	if (_hoops_IPRI != null &&
			_hoops_IPRI->local_face_attributes.normals != null) {
		/* [_hoops_GCAS] _hoops_CGGGA _hoops_IRS _hoops_CCAH _hoops_RSGA & _hoops_GGRA _hoops_CGH _hoops_SHH _hoops_CCACP
		 * _hoops_HSAR _hoops_SCACP _hoops_RH _hoops_GHC _hoops_IS _hoops_GSSP _hoops_GC (_hoops_PPR _hoops_PSCR _hoops_GAAP
		 * _hoops_CGGGA _hoops_PCCP _hoops_GGRA _hoops_APIC)
		 */
		return HD_Generate_DC_Screen_Facings (nr, face_count,
						_hoops_IPRI->local_face_attributes.normals, true);
	}
	else {

		/* _hoops_RRP _hoops_IS _hoops_HGCR _hoops_RH _hoops_GHC _hoops_SRS */
		_hoops_GIACP (nr, (Tristrip alter *)ts);

		return HD_Generate_DC_Screen_Facings (nr, face_count,
											  dc->_hoops_AIACP, false);
	}
}


#define _hoops_CSACP(nr, mat, _hoops_SSACP, point, color, plane, _hoops_ASACP, _hoops_GGPCP) do {			\
		if (_hoops_SSACP && ANYBIT (nr->transform_rendition->_hoops_IPH->data._hoops_RAGR,	\
								  _hoops_CICH))									\
			_hoops_GSACP (nr, mat, point, color, plane, _hoops_ASACP, _hoops_GGPCP);			\
		else																					\
			_hoops_ISACP (nr,															\
								 nr->_hoops_IHA->_hoops_AGP,							\
								 mat, point, color, plane, _hoops_ASACP, null, 0, 0, _hoops_GGPCP, null);	\
	} while (0)

local void _hoops_GSACP (
	Net_Rendition const &		nr,
	_hoops_HHA const &	_hoops_ISHIR,
	Point const *				_hoops_RSACP,
	RGB const *					color,
	_hoops_ARPA const *				plane,
	Vector const *				_hoops_ASACP,
	RGBA alter *				total) {
	Point						_hoops_HSACP;
	_hoops_RPRA const *			elements = nr->transform_rendition->_hoops_IPH->data.elements;

	_hoops_HSACP.x = _hoops_HPRA (elements, *_hoops_RSACP);
	_hoops_HSACP.y = _hoops_IPRA (elements, *_hoops_RSACP);
	_hoops_HSACP.z = _hoops_CPRA (elements, *_hoops_RSACP);

	_hoops_ISACP (nr, nr->_hoops_IHA->_hoops_AGP,
						 _hoops_ISHIR, &_hoops_HSACP, color, plane, _hoops_ASACP, null, 0, 0, total, null);
}

#endif



#define _hoops_RGACP	64
#define _hoops_AGACP		(3*_hoops_RGACP)
#define _hoops_PGACP		(_hoops_AGACP+3) /* _hoops_ASSS _hoops_IH _hoops_SPR _hoops_RRI _hoops_SCPH _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_GHIPR-_hoops_RH-_hoops_RHC _hoops_HHGP */
#define _hoops_HGACP 4

struct _hoops_SGACP {
	DC_Point					_hoops_HRIGA[_hoops_PGACP];
	RGBAS32						_hoops_HIAI[_hoops_PGACP];
	_hoops_ARPA						_hoops_IHRGA[_hoops_PGACP];
	RGBA						_hoops_IGACP[_hoops_PGACP];
	_hoops_RSSH					_hoops_CGACP[_hoops_PGACP*_hoops_HGACP];
	_hoops_RSSH alter *			_hoops_SHRGA;
	DC_Point alter *			points;
	RGBAS32 alter *				colors;
	_hoops_ARPA alter *				planes;
	_hoops_RSSH alter *			params;
	RGBA alter *				_hoops_HPHSA;
	int							param_width;
};

local void _hoops_ARPCP (
	_hoops_SGACP *		_hoops_IGIC) {

	_hoops_IGIC->points = _hoops_IGIC->_hoops_HRIGA;
	_hoops_IGIC->colors = _hoops_IGIC->_hoops_HIAI;
	_hoops_IGIC->planes = _hoops_IGIC->_hoops_IHRGA;
	_hoops_IGIC->params = _hoops_IGIC->_hoops_SHRGA;
	_hoops_IGIC->_hoops_HPHSA = _hoops_IGIC->_hoops_IGACP;
}

local void _hoops_PRPCP (
	_hoops_SGACP *		_hoops_IGIC,
	int				param_width) {

	_hoops_IGIC->param_width = param_width;
	if (param_width > _hoops_HGACP)
		ALLOC_ARRAY_CACHED (_hoops_IGIC->_hoops_SHRGA, _hoops_PGACP * param_width, _hoops_RSSH);
	else
		_hoops_IGIC->_hoops_SHRGA = _hoops_IGIC->_hoops_CGACP;
	_hoops_ARPCP(_hoops_IGIC);
}

local void _hoops_HRPCP (
	_hoops_SGACP *		_hoops_IGIC) {

	if (_hoops_IGIC->param_width > _hoops_HGACP)
		FREE_ARRAY (_hoops_IGIC->_hoops_SHRGA, _hoops_PGACP * _hoops_IGIC->param_width, _hoops_RSSH);
}


local void _hoops_IRPCP (
	Net_Rendition const &	_hoops_PPHIS,
	_hoops_SGACP *				_hoops_IGIC,
	Tristrip const *		ts,
	bool 					_hoops_HAACP,
	bool 					_hoops_HIGSI) {
	int						count = -(_hoops_IGIC->points-_hoops_IGIC->_hoops_HRIGA);

#ifndef DISABLE_TEXTURING
	if (_hoops_IGIC->params != _hoops_IGIC->_hoops_SHRGA)
		_hoops_HSHGH (_hoops_PPHIS, count, _hoops_IGIC->_hoops_HRIGA,
										   (_hoops_IGIC->_hoops_HPHSA != _hoops_IGIC->_hoops_IGACP) ? _hoops_IGIC->_hoops_IGACP : (RGBA*)null,
										   (_hoops_IGIC->planes != _hoops_IGIC->_hoops_IHRGA) ? _hoops_IGIC->_hoops_IHRGA : (_hoops_ARPA*)null,
										   _hoops_IGIC->_hoops_SHRGA, ts->_hoops_GSSH->_hoops_GSHA, ts->_hoops_GSSH->_hoops_SCAI);
	else
#endif
#ifndef DISABLE_PHONG
	if (_hoops_HAACP)
		_hoops_CRPCP (_hoops_PPHIS, count, _hoops_IGIC->_hoops_HRIGA,
										(_hoops_IGIC->_hoops_HPHSA != _hoops_IGIC->_hoops_IGACP) ? _hoops_IGIC->_hoops_IGACP: (RGBA*)null,
										_hoops_IGIC->_hoops_IHRGA);
	else
#endif
	if (_hoops_IGIC->colors != _hoops_IGIC->_hoops_HIAI) {
		if (!_hoops_HIGSI)
			_hoops_SRPCP (_hoops_PPHIS, count, _hoops_IGIC->_hoops_HRIGA, _hoops_IGIC->_hoops_HIAI);
		else
			_hoops_GAPCP (_hoops_PPHIS, count, _hoops_IGIC->_hoops_HRIGA, _hoops_IGIC->_hoops_HIAI, false);
	}
	else
		_hoops_RAPCP (_hoops_PPHIS, count, _hoops_IGIC->_hoops_HRIGA);

	_hoops_ARPCP (_hoops_IGIC);
}


GLOBAL_FUNCTION void HD_Std_3D_Tristrip (
	Net_Rendition const & 		nr,
	Tristrip const *			ts) {
#ifndef DISABLE_DRAW_3D
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	int							point_count = ts->point_count;
	int							face_count = ts->face_count;
	int							_hoops_PHHA = ts->_hoops_PHHA;
	int const *					lengths = ts->lengths;
	int const *					_hoops_AIHA = ts->_hoops_AIHA;
	int const *					face_indices = ts->face_indices;
	RGB const *					_hoops_PCHA = ts->_hoops_PCHA;
	RGB const *					_hoops_PAGI = ts->_hoops_PAGI;
	Vector const *				_hoops_ICHA = ts->_hoops_ICHA;
	_hoops_ARPA const *				_hoops_RIIIA = ts->_hoops_PRHH;
	_hoops_RSSH const *			_hoops_CCHA = ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_CCHA : 0;
	int							param_width = ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_GSHA : 0;
	int							_hoops_SGICS = 0;
	int							_hoops_RHSGI = 0;
	int							_hoops_HSPI, _hoops_ISPI, _hoops_CSPI;
	int							_hoops_PGRSH, _hoops_AGSIR, _hoops_PGSIR;
	RGB const					*_hoops_SRIIS, *_hoops_GAIIS, *_hoops_PRICS;
	_hoops_ARPA const					*_hoops_RAIIS, *_hoops_AIAIA, *_hoops_PIHHA;
	Net_Rendition		 		_hoops_AIRSH;
	Net_Rendition		 		_hoops_PPHIS;
	Net_Rendition		 		_hoops_HRICS;
	int alter *					_hoops_AGHAR = null;
	_hoops_PC const &		_hoops_CGR = nr->_hoops_IHA->_hoops_AGP;
	unsigned char				_hoops_IRIR;
	unsigned char				_hoops_IRICS;
	bool						_hoops_APH = false, _hoops_CRICS = false, _hoops_SSIGC = false;
	bool						_hoops_HIGSI = false, _hoops_AAIIS = false;
	bool						_hoops_HAACP = false, _hoops_IAACP = false, _hoops_CRIR = false;
	bool						_hoops_CAACP = false;
	unsigned char				_hoops_SRICS = 0;
	int							_hoops_GAICS = 0;
	RGBAS32						_hoops_RAICS[2048];
	RGBAS32						*_hoops_AAICS = _hoops_RAICS, *_hoops_PAICS = null, *_hoops_GHGCP = null;
	int							_hoops_AGH = 0;
	DC_Point  *					_hoops_GHPCP;
	float *						ws;
	_hoops_GRCAR *					_hoops_ARCAR;
	_hoops_ARPA const *				_hoops_PAIIS = null;
	_hoops_SGACP						_hoops_IGIC;
	int							_hoops_CRCAR;
	Bounding					bounding;
	bool						_hoops_HAICS=false, _hoops_IAICS=false;
	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;

	dc->_hoops_GSGC |= _hoops_GCGI;
	if (BIT(dc->flags, _hoops_CHSI))
		return;

	if (ts->_hoops_PHHA == 0)
		return;

	_hoops_PRPCP (&_hoops_IGIC, param_width);


	if (point_count == 0 || face_count == 0) {
		if (lengths == null || _hoops_AIHA == null) {
			// _hoops_CGH _hoops_HS 3 _hoops_GIAH _hoops_ARAR, _hoops_IH _hoops_HA _hoops_SAHR _hoops_HPCAR _hoops_RH "_hoops_GIPR _hoops_IRAP" _hoops_AGIR
			if (ts->point_count == 0)
				_hoops_PGRCA(ts)->point_count = point_count = 3 * _hoops_PHHA;
			if (ts->face_count == 0)
				_hoops_PGRCA(ts)->face_count = face_count = _hoops_PHHA;
		}
		else {
			int				index;
			/* _hoops_PPPA _hoops_HIGR _hoops_IS _hoops_CGIC _hoops_RH _hoops_CIAS _hoops_PSHS _hoops_HSH _hoops_IH _hoops_GPHA _hoops_PPR _hoops_HSP _hoops_PSPI. */

			while (_hoops_PHHA-- > 0) {
				int			length = *lengths++;

				while (length-- > 0) {
					if ((index = *_hoops_AIHA++) > point_count)
						point_count = index;
					if (face_indices) {
						if ((index = *face_indices++) > face_count)
							face_count = index;
					}
				}
			}
			_hoops_PHHA = ts->_hoops_PHHA;
			lengths = ts->lengths;
			_hoops_AIHA = ts->_hoops_AIHA;
			face_indices = ts->face_indices;

			if (face_count == 0 && !face_indices)
					face_count = ts->total - 2*ts->_hoops_PHHA;

			/* _hoops_AGRP _hoops_CCAH _hoops_HSH _hoops_HII "_hoops_CIAS _hoops_CIHA" _hoops_IS "_hoops_PHI _hoops_IIGR _hoops_PSPI" */
			if (ts->point_count == 0)
				_hoops_PGRCA(ts)->point_count = ++point_count;
			if (ts->face_count == 0)
				_hoops_PGRCA(ts)->face_count = ++face_count;
		}
	}

	bounding = ts->bounding;
	POOL_ALLOC_ARRAY_ALIGNED_CACHED (_hoops_GHPCP, point_count, DC_Point, 16, dc->memory_pool);
	POOL_ALLOC_ARRAY_ALIGNED_CACHED (ws, point_count, float, 16, dc->memory_pool);
	POOL_ALLOC_ARRAY_CACHED (_hoops_ARCAR, point_count, _hoops_GRCAR, dc->memory_pool);

	_hoops_CRCAR = HD_Acquire_Clip_Points (nr, bounding, point_count, ts->points, _hoops_GHPCP, ws, _hoops_ARCAR);

	if (_hoops_CRCAR == 0)
		goto _hoops_HPAGR;

	_hoops_IRICS = (unsigned char)(255.99f * nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR);

	/* _hoops_CGP _hoops_SR _hoops_CAHP _hoops_SHPR _hoops_IPPA _hoops_GSSIA _hoops_PAR _hoops_GSSP _hoops_HSP _hoops_GHC, _hoops_SR _hoops_RRP _hoops_IS _hoops_CASI _hoops_CAPR _hoops_GH.
		_hoops_HGI _hoops_IGIPR _hoops_SGS _hoops_CAICS _hoops_PPR _hoops_SAICS _hoops_GRS
		_hoops_SHH _hoops_PIGS _hoops_HAAI _hoops_PPR _hoops_GRS _hoops_GAGAR _hoops_AGAP _hoops_HSH.
	*/
	if (dc->_hoops_PIACP < ts->face_count)
		_hoops_HAICS=true;
	if (dc->_hoops_ICACP < ts->face_count)
		_hoops_IAICS=true;

	if (dc->_hoops_APHHP == null) {
		_hoops_APH = BIT (nr->transform_rendition->flags, _hoops_IGSP);

		if (!_hoops_APH &&
			ANYBIT (nr->transform_rendition->heuristics,
					_hoops_SASA | _hoops_GPSA) &&
			nr->_hoops_IHA->_hoops_CHA != nr->_hoops_IHA->_hoops_GIA) {
			_hoops_AIRSH = nr.Copy();
			_hoops_CIGA alter &		_hoops_SIGA = _hoops_AIRSH->_hoops_IHA.Modify();

			Swap (_hoops_SIGA->color, _hoops_SIGA->_hoops_RGIR);
			Swap (_hoops_SIGA->_hoops_CHA, _hoops_SIGA->_hoops_GIA);

			_hoops_SRICS = (unsigned char)(255.99f * _hoops_SIGA->_hoops_CHA->_hoops_IRIR);
			_hoops_CRICS = true;
		}
		else if (BIT (nr->transform_rendition->flags, _hoops_SPP))
			_hoops_GAICS = ~0;

		_hoops_SSIGC = _hoops_APH || _hoops_CRICS;

		_hoops_CRIR = BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH);

		_hoops_HAACP = BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA);
		_hoops_IAACP = BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GSRC) &&
				   nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR;

		/* _hoops_RHI _hoops_GCA _hoops_RAHCP */
		if (_hoops_IAACP && nr->_hoops_IHA->_hoops_CHA->texture[_hoops_RIA])
			_hoops_HAACP = true;

		if (_hoops_ICHA != null || _hoops_HAACP || (_hoops_CCHA || _hoops_IAACP) && !_hoops_RIIIA) {
			_hoops_GRICS (nr, (Tristrip alter *)ts);
			_hoops_PAIIS = dc->_hoops_PGPCP;
		}
		else if (_hoops_RIIIA) {
			//_hoops_RPP (_hoops_CSPH->_hoops_IAHCP == _hoops_IRAP) {
				_hoops_GIACP (nr, (Tristrip alter *)ts);
				_hoops_RIIIA = dc->_hoops_AIACP;
			//}
		}

		if (_hoops_ICHA != null || _hoops_RIIIA != null) {
			if (_hoops_CGR)
				_hoops_CAACP = _hoops_CGR->_hoops_ISPHP ||
								BIT (nr->_hoops_IRR->_hoops_PPH, Rendo_LOCAL_VIEWER) ||
								BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH);
		}
	}

	if (_hoops_SSIGC /* && _hoops_ASGA */) {
		if ((_hoops_AGHAR = dc->_hoops_CGHAR) == null || face_count != dc->_hoops_ICACP) {
			_hoops_AGHAR = HD_Get_Screen_Facings (nr, ts, face_count);
			//_hoops_CSPH->_hoops_APSCC = _hoops_GSSIA;
			//_hoops_CSPH->_hoops_GPICS = _hoops_ACHAA;
		}
		//((_hoops_AASGR _hoops_RAPC *)_hoops_GARI)->_hoops_APSCC = _hoops_GSSIA;
	}

	_hoops_SRIIS = _hoops_GAIIS = _hoops_PRICS = null;
	_hoops_RAIIS = _hoops_AIAIA = _hoops_PIHHA = null;

	_hoops_HIGSI = (_hoops_CCHA == null) && (_hoops_ICHA == null) &&
				(_hoops_PCHA == null) && !_hoops_CRIR;
	_hoops_AAIIS = (_hoops_ICHA && _hoops_PAGI) || (_hoops_PCHA && _hoops_RIIIA);



#define _hoops_APIIS(_hoops_PPIIS, _hoops_HPIIS) do if (BIT(_hoops_PPIIS.options, _hoops_CHRH)) {	\
			RGBAS32 alter &	_hoops_HAPCR = _hoops_HPIIS;											\
			RGB				tmp = _hoops_HAPCR;											\
			tmp = HD_Apply_Color_Effects (tmp, _hoops_PPIIS);							\
			_hoops_HAPCR = RGBAS32 (tmp, _hoops_HAPCR.a);											\
		} while (0)

#define _hoops_IPIIS(_hoops_PPIIS, _hoops_HPIIS) do if (BIT(_hoops_PPIIS.options, _hoops_CHRH)) {		\
			RGBA alter &	_hoops_HAPCR = _hoops_HPIIS;											\
			RGB				tmp = _hoops_HAPCR;											\
			tmp = HD_Apply_Color_Effects (tmp, _hoops_PPIIS);							\
			_hoops_HAPCR = RGBA (tmp, _hoops_HAPCR.alpha);											\
		} while (0)


#if 1
	if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH &&
		!BIT(dc->flags, _hoops_GPHHP) &&
		!BIT (ts->_hoops_SRHA, DL_DO_NOT_DEFER) &&
		!BIT (ts->_hoops_SRHA, DL_3D_TRANSPARENCY) &&
		BIT (nr->_hoops_CPP->_hoops_PRH._hoops_SRI, _hoops_HSSS) &&
		nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI) {
		int 		flags = 0;
		int 		_hoops_AGPCS = 0;

		if (point_count != _hoops_CRCAR) {
			for (int i = 0; i < point_count; i++)
				_hoops_AGPCS |= _hoops_ARCAR[i];
		}

		if (!BIT(_hoops_AGPCS, _hoops_IPCAR)) {
			if (_hoops_CAACP)
				flags |= _hoops_CCGSH;
			if (nr->_hoops_IHA->_hoops_CHA->texture[_hoops_RIA])
				flags |= _hoops_GSGSH;
			if (_hoops_AAIIS)
				flags |= _hoops_SCGSH;

			/* _hoops_PSCPR _hoops_RH _hoops_CRHH _hoops_RPICS.  _hoops_PS'_hoops_GCPP _hoops_AGGHA _hoops_HIPH _hoops_HII _hoops_SCH _hoops_SPHR _hoops_GAR _hoops_SIGR */
			HD_Hide_3D_Tristrip (nr, _hoops_AIRSH, ts, flags, _hoops_GHPCP);

			/*_hoops_RPP (_hoops_HSAGA->_hoops_AAGGR > 1)
				_hoops_PGPCS (_hoops_HSAGA);*/	/* _hoops_SHI _hoops_HHHA _hoops_HGPCS _hoops_ARRS */

			goto _hoops_HPAGR;
		}
	}
#endif

	if ((ts->_hoops_GSSH && !ts->_hoops_GSSH->_hoops_CCHA) && !_hoops_HAACP &&
		(_hoops_ICHA || _hoops_RIIIA || _hoops_CRIR)) {

		_hoops_AGH = _hoops_IAAA (point_count, face_count);
		if (_hoops_AGH > _hoops_GGAPR (_hoops_RAICS)/2)
			ALLOC_ARRAY_CACHED (_hoops_AAICS, 2*_hoops_AGH, RGBAS32);
		ZERO_ARRAY (_hoops_AAICS, 2*_hoops_AGH, RGBAS32);
		_hoops_PAICS = _hoops_AAICS + _hoops_AGH;
	}

	while (_hoops_PHHA-- > 0) {
		int							length = 3;
		bool						_hoops_AGRCA = false;

		if (lengths != null)
			length = *lengths++;

		if (_hoops_AIHA != null) {
			_hoops_HSPI = *_hoops_AIHA++;
			_hoops_ISPI = *_hoops_AIHA++;
		}
		else {
			_hoops_HSPI = _hoops_SGICS++;
			_hoops_ISPI = _hoops_SGICS++;
		}

		_hoops_PGRSH = _hoops_ISCSH(_hoops_GHPCP[_hoops_HSPI].y);
		_hoops_AGSIR = _hoops_ISCSH(_hoops_GHPCP[_hoops_ISPI].y);

		if (face_indices != null)
			face_indices += 2;

		length -= 2;

		while (length-- > 0) {
			int						face;

			if (_hoops_AIHA != null)
				_hoops_CSPI = *_hoops_AIHA++;
			else
				_hoops_CSPI = _hoops_SGICS++;

			_hoops_PGSIR = _hoops_ISCSH(_hoops_GHPCP[_hoops_CSPI].y);

			if (face_indices != null)
				face = *face_indices++;
			else
				face = _hoops_RHSGI++;

			if (_hoops_PGRSH != _hoops_AGSIR || _hoops_AGSIR != _hoops_PGSIR) {
				/* _hoops_HPPP _hoops_RGR _hoops_SCPH */
				_hoops_PPHIS = nr;
				_hoops_IRIR = _hoops_IRICS;
				_hoops_GHGCP = _hoops_AAICS;
				if (_hoops_SSIGC && _hoops_AGHAR[face] == _hoops_GAICS) {
					if (_hoops_CRICS) {
						_hoops_PPHIS = _hoops_AIRSH;
						_hoops_IRIR = _hoops_SRICS;
						_hoops_GHGCP = _hoops_PAICS;
					}
					else
						_hoops_PPHIS = null;  /* _hoops_HPPHR _hoops_RGSP */
				}
				if (_hoops_PPHIS && _hoops_HRICS && _hoops_PPHIS != _hoops_HRICS &&
					_hoops_IGIC.points != _hoops_IGIC._hoops_HRIGA)
					_hoops_IRPCP (_hoops_HRICS, &_hoops_IGIC, ts, _hoops_HAACP, _hoops_HIGSI);
				_hoops_HRICS = _hoops_PPHIS;

				if (!ANYBIT (_hoops_ARCAR[_hoops_HSPI] & _hoops_ARCAR[_hoops_ISPI] & _hoops_ARCAR[_hoops_CSPI], ~_hoops_RPCAR) &&
					_hoops_PPHIS != null) {
					/* _hoops_HAR _hoops_RHGCP _hoops_PAR _hoops_CPIIS _hoops_SACH _hoops_SGGR _hoops_GGR _hoops_SPR _hoops_HAGA */
					_hoops_RSAI (&_hoops_GHPCP[_hoops_HSPI], DC_Point, &_hoops_IGIC.points[0]);
					_hoops_RSAI (&_hoops_GHPCP[_hoops_ISPI], DC_Point, &_hoops_IGIC.points[1]);
					_hoops_RSAI (&_hoops_GHPCP[_hoops_CSPI], DC_Point, &_hoops_IGIC.points[2]);
					_hoops_IGIC.points += 3;

					if ((ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_CCHA) || _hoops_HAACP) {
						float		_hoops_SPIIS = _hoops_PPHIS->_hoops_IHA->_hoops_CHA->_hoops_IRIR;

#ifndef DISABLE_TEXTURING
						if (_hoops_CCHA) {
							int			i;

							if (ts->_hoops_GSSH && BIT (ts->_hoops_GSSH->_hoops_SCAI, _hoops_HPPAR)) {			
								_hoops_RSSH alter *	_hoops_APICS = _hoops_IGIC.params;

								_hoops_APICS = _hoops_IGIC.params;
								for (i=0; i<param_width; i++) *_hoops_IGIC.params++ = _hoops_CCHA[_hoops_HSPI*param_width+i];
								for (i=0; i<param_width; i++) *_hoops_IGIC.params++ = _hoops_CCHA[_hoops_ISPI*param_width+i];
								for (i=0; i<param_width; i++) *_hoops_IGIC.params++ = _hoops_CCHA[_hoops_CSPI*param_width+i];

								if (_hoops_APICS[param_width*0] == 0.0f)
									_hoops_APICS[param_width*0] = 0.5f * (_hoops_APICS[param_width*1]+_hoops_APICS[param_width*2]);
								if (_hoops_APICS[param_width*1] == 0.0f)
									_hoops_APICS[param_width*1] = 0.5f * (_hoops_APICS[param_width*0]+_hoops_APICS[param_width*2]);
								if (_hoops_APICS[param_width*2] == 0.0f)
									_hoops_APICS[param_width*2] = 0.5f * (_hoops_APICS[param_width*0]+_hoops_APICS[param_width*1]);
#define _hoops_PRPAR 0.7f
								while (_hoops_APICS[param_width*0]-_hoops_APICS[param_width*1] > _hoops_PRPAR) _hoops_APICS[param_width*1] += 1.0f;
								while (_hoops_APICS[param_width*0]-_hoops_APICS[param_width*2] > _hoops_PRPAR) _hoops_APICS[param_width*2] += 1.0f;
								while (_hoops_APICS[param_width*1]-_hoops_APICS[param_width*0] > _hoops_PRPAR) _hoops_APICS[param_width*0] += 1.0f;
								while (_hoops_APICS[param_width*1]-_hoops_APICS[param_width*2] > _hoops_PRPAR) _hoops_APICS[param_width*2] += 1.0f;
								while (_hoops_APICS[param_width*2]-_hoops_APICS[param_width*0] > _hoops_PRPAR) _hoops_APICS[param_width*0] += 1.0f;
								while (_hoops_APICS[param_width*2]-_hoops_APICS[param_width*1] > _hoops_PRPAR) _hoops_APICS[param_width*1] += 1.0f;
#undef _hoops_PRPAR
							}
							else {
								if (param_width == 2) {
									*_hoops_IGIC.params++ = _hoops_CCHA[_hoops_HSPI*param_width];
									*_hoops_IGIC.params++ = _hoops_CCHA[_hoops_HSPI*param_width+1];
									*_hoops_IGIC.params++ = _hoops_CCHA[_hoops_ISPI*param_width];
									*_hoops_IGIC.params++ = _hoops_CCHA[_hoops_ISPI*param_width+1];
									*_hoops_IGIC.params++ = _hoops_CCHA[_hoops_CSPI*param_width];
									*_hoops_IGIC.params++ = _hoops_CCHA[_hoops_CSPI*param_width+1];
								}
								else {
									for (i=0; i<param_width; i++) *_hoops_IGIC.params++ = _hoops_CCHA[_hoops_HSPI*param_width+i];
									for (i=0; i<param_width; i++) *_hoops_IGIC.params++ = _hoops_CCHA[_hoops_ISPI*param_width+i];
									for (i=0; i<param_width; i++) *_hoops_IGIC.params++ = _hoops_CCHA[_hoops_CSPI*param_width+i];
								}
							}

						}
#endif
						if (_hoops_PAIIS) {
							_hoops_IGIC.planes[0] = _hoops_PAIIS[_hoops_HSPI];
							_hoops_IGIC.planes[1] = _hoops_PAIIS[_hoops_ISPI];
							_hoops_IGIC.planes[2] = _hoops_PAIIS[_hoops_CSPI];
							_hoops_IGIC.planes += 3;
						}
						else if (_hoops_RIIIA) {
							_hoops_IGIC.planes[0] = _hoops_RIIIA[face];
							_hoops_IGIC.planes[1] = _hoops_RIIIA[face];
							_hoops_IGIC.planes[2] = _hoops_RIIIA[face];
							_hoops_IGIC.planes += 3;
						}

						if (_hoops_PCHA) {
							_hoops_IGIC._hoops_HPHSA[0] = RGBA (_hoops_PCHA[_hoops_HSPI], _hoops_SPIIS);
							_hoops_IGIC._hoops_HPHSA[1] = RGBA (_hoops_PCHA[_hoops_ISPI], _hoops_SPIIS);
							_hoops_IGIC._hoops_HPHSA[2] = RGBA (_hoops_PCHA[_hoops_CSPI], _hoops_SPIIS);
							_hoops_IPIIS (_hoops_PHAH, _hoops_IGIC._hoops_HPHSA[0]);
							_hoops_IPIIS (_hoops_PHAH, _hoops_IGIC._hoops_HPHSA[1]);
							_hoops_IPIIS (_hoops_PHAH, _hoops_IGIC._hoops_HPHSA[2]);
							_hoops_IGIC._hoops_HPHSA += 3;
						}
						else if (_hoops_PAGI) {
							_hoops_IGIC._hoops_HPHSA[0] = RGBA (_hoops_PAGI[face], _hoops_SPIIS);
							_hoops_IPIIS (_hoops_PHAH, _hoops_IGIC._hoops_HPHSA[0]);
							_hoops_IGIC._hoops_HPHSA[1] = _hoops_IGIC._hoops_HPHSA[2] = _hoops_IGIC._hoops_HPHSA[0];
							_hoops_IGIC._hoops_HPHSA += 3;
						}
						else {
							_hoops_IGIC._hoops_HPHSA[0] = RGBA (_hoops_PPHIS->_hoops_IHA->_hoops_CHA->_hoops_CSHR,
												   _hoops_SPIIS);
							_hoops_IPIIS (_hoops_PHAH, _hoops_IGIC._hoops_HPHSA[0]);
							_hoops_IGIC._hoops_HPHSA[1] = _hoops_IGIC._hoops_HPHSA[2] = _hoops_IGIC._hoops_HPHSA[0];
							_hoops_IGIC._hoops_HPHSA += 3;
						}
					}
					else if (_hoops_ICHA || _hoops_RIIIA || _hoops_CRIR) {
						_hoops_HHA const &		_hoops_ISHIR = _hoops_PPHIS->_hoops_IHA->_hoops_CHA;
						RGBA							tmp;

						if (_hoops_PCHA) {
							_hoops_SRIIS = &_hoops_PCHA[_hoops_HSPI];
							_hoops_GAIIS = &_hoops_PCHA[_hoops_ISPI];
							_hoops_PRICS = &_hoops_PCHA[_hoops_CSPI];
						}
						else if (_hoops_PAGI)
							_hoops_SRIIS = _hoops_GAIIS = _hoops_PRICS = &_hoops_PAGI[face];

						if (_hoops_ICHA) {
							_hoops_RAIIS = &_hoops_PAIIS[_hoops_HSPI];
							_hoops_AIAIA = &_hoops_PAIIS[_hoops_ISPI];
							_hoops_PIHHA = &_hoops_PAIIS[_hoops_CSPI];
						}
						else if (_hoops_RIIIA)
							_hoops_RAIIS = _hoops_AIAIA = _hoops_PIHHA = &_hoops_RIIIA[face];

						if (!_hoops_HIGSI) {
							if (_hoops_GHGCP[_hoops_HSPI] == _hoops_CAHSR::_hoops_SAHSR || _hoops_AAIIS) {
								_hoops_CSACP (nr, _hoops_ISHIR, _hoops_CAACP, &ts->points[_hoops_HSPI], _hoops_SRIIS, _hoops_RAIIS, null, &tmp);
								_hoops_GHGCP[_hoops_HSPI] = RGBAS32 (tmp, _hoops_IRIR);
								_hoops_APIIS (_hoops_PHAH, _hoops_GHGCP[_hoops_HSPI]);
								_hoops_SIPCP (dc, _hoops_GHGCP[_hoops_HSPI]);
							}
							*_hoops_IGIC.colors++ = _hoops_GHGCP[_hoops_HSPI];

							if (_hoops_GHGCP[_hoops_ISPI] == _hoops_CAHSR::_hoops_SAHSR || _hoops_AAIIS) {
								_hoops_CSACP (nr, _hoops_ISHIR, _hoops_CAACP, &ts->points[_hoops_ISPI], _hoops_GAIIS, _hoops_AIAIA, null, &tmp);
								_hoops_GHGCP[_hoops_ISPI] = RGBAS32 (tmp, _hoops_IRIR);
								_hoops_APIIS (_hoops_PHAH, _hoops_GHGCP[_hoops_ISPI]);
								_hoops_SIPCP (dc, _hoops_GHGCP[_hoops_ISPI]);
							}
							*_hoops_IGIC.colors++ = _hoops_GHGCP[_hoops_ISPI];

							if (_hoops_GHGCP[_hoops_CSPI] == _hoops_CAHSR::_hoops_SAHSR || _hoops_AAIIS) {
								_hoops_CSACP (nr, _hoops_ISHIR, _hoops_CAACP, &ts->points[_hoops_CSPI], _hoops_PRICS, _hoops_PIHHA, null, &tmp);
								_hoops_GHGCP[_hoops_CSPI] = RGBAS32 (tmp, _hoops_IRIR);
								_hoops_APIIS (_hoops_PHAH, _hoops_GHGCP[_hoops_CSPI]);
								_hoops_SIPCP (dc, _hoops_GHGCP[_hoops_CSPI]);
							}
							*_hoops_IGIC.colors++ = _hoops_GHGCP[_hoops_CSPI];
						}
						else {
							if (_hoops_GHGCP[face] == _hoops_CAHSR::_hoops_SAHSR) {
								_hoops_CSACP (nr, _hoops_ISHIR, _hoops_CAACP, &ts->points[_hoops_CSPI], _hoops_PRICS, _hoops_PIHHA, null, &tmp);
								_hoops_GHGCP[face] = RGBAS32 (tmp, _hoops_IRIR);
								_hoops_APIIS (_hoops_PHAH, _hoops_GHGCP[face]);
								_hoops_SIPCP (dc, _hoops_GHGCP[face]);
							}
							*_hoops_IGIC.colors++ = _hoops_GHGCP[face];
						}
					}
					else {
						if (_hoops_PCHA) {
							*_hoops_IGIC.colors = RGBAS32 (_hoops_PCHA[_hoops_HSPI], _hoops_IRIR);
							_hoops_APIIS (_hoops_PHAH, *_hoops_IGIC.colors);
							_hoops_SIPCP (dc, *_hoops_IGIC.colors);
							_hoops_IGIC.colors++;

							*_hoops_IGIC.colors = RGBAS32 (_hoops_PCHA[_hoops_ISPI], _hoops_IRIR);
							_hoops_APIIS (_hoops_PHAH, *_hoops_IGIC.colors);
							_hoops_SIPCP (dc, *_hoops_IGIC.colors);
							_hoops_IGIC.colors++;

							*_hoops_IGIC.colors = RGBAS32 (_hoops_PCHA[_hoops_CSPI], _hoops_IRIR);
							_hoops_APIIS (_hoops_PHAH, *_hoops_IGIC.colors);
							_hoops_SIPCP (dc, *_hoops_IGIC.colors);
							_hoops_IGIC.colors++;
						}
						else if (_hoops_PAGI) {
							RGBAS32		result = RGBAS32 (_hoops_PAGI[face], _hoops_IRIR);
							_hoops_APIIS (_hoops_PHAH, result);
							_hoops_SIPCP (dc, result);
							*_hoops_IGIC.colors++ = result;

							if (!_hoops_HIGSI) {
								*_hoops_IGIC.colors++ = result;
								*_hoops_IGIC.colors++ = result;
							}
						}
						else if (_hoops_CRICS)
							*_hoops_IGIC.colors++ = _hoops_PPHIS->_hoops_IHA->color;
					}

					/* _hoops_GII _hoops_GHIPR-_hoops_RH-_hoops_RHC (_hoops_ARSHA) _hoops_CIHH _hoops_IRHS _hoops_IS _hoops_SHH _hoops_GIR _hoops_ARI */
					if (BIT (_hoops_ARCAR[_hoops_HSPI] | _hoops_ARCAR[_hoops_ISPI] | _hoops_ARCAR[_hoops_CSPI], _hoops_IPCAR)) {
						_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
						int								a, b, c;
						float							_hoops_PRSAS, _hoops_HRSAS, _hoops_GPGSI;
						float							_hoops_IRSAS, _hoops_CRSAS;
						float							_hoops_SRSAS = _hoops_IHCR->_hoops_GSCH[0] * dc->_hoops_PGCC._hoops_PASHP;

						/* "_hoops_IRSHR" _hoops_SSAI._hoops_RSSA _hoops_HIS _hoops_SGS _hoops_PPSR _hoops_RAIGR _hoops_HRGR _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_RHC
						 * _hoops_PPR _hoops_PPSR _hoops_IHRPR _hoops_HRGR _hoops_GHIPR.  _hoops_ACAGR _hoops_IIGR _hoops_IHAC _hoops_GRS _hoops_CGIC _hoops_RPP
						 * _hoops_RH _hoops_AACC _hoops_RSSAR _hoops_SPR _hoops_PAR _hoops_PGCR _hoops_HIPH.
						 */
						if (ws[_hoops_HSPI] >= _hoops_IHCR->_hoops_CHCR) {
							if (ws[_hoops_CSPI] < _hoops_IHCR->_hoops_CHCR) {
								a = 0;	_hoops_PRSAS = ws[_hoops_HSPI];
								b = 1;	_hoops_HRSAS = ws[_hoops_ISPI];
								c = 2;	_hoops_GPGSI = ws[_hoops_CSPI];
							}
							else {	/* _hoops_RASAS _hoops_PIHA _hoops_SHH _hoops_GHIPR */
								a = 2;	_hoops_PRSAS = ws[_hoops_CSPI];
								b = 0;	_hoops_HRSAS = ws[_hoops_HSPI];
								c = 1;	_hoops_GPGSI = ws[_hoops_ISPI];
							}
						}
						else {
							if (ws[_hoops_ISPI] >= _hoops_IHCR->_hoops_CHCR) {
								a = 1;	_hoops_PRSAS = ws[_hoops_ISPI];
								b = 2;	_hoops_HRSAS = ws[_hoops_CSPI];
								c = 0;	_hoops_GPGSI = ws[_hoops_HSPI];
							}
							else {	/* _hoops_AASAS _hoops_PIHA _hoops_SHH _hoops_RGAR _hoops_SPR _hoops_GGR _hoops_RIPS */
								a = 2;	_hoops_PRSAS = ws[_hoops_CSPI];
								b = 0;	_hoops_HRSAS = ws[_hoops_HSPI];
								c = 1;	_hoops_GPGSI = ws[_hoops_ISPI];
							}
						}

						a -= 3; b -= 3; c -= 3; /* _hoops_AGCR _hoops_CGRPR _hoops_RH _hoops_PGGPS _hoops_GSSRH _hoops_RH _hoops_CICRR */

						if (_hoops_HRSAS < _hoops_IHCR->_hoops_CHCR) {
							/* _hoops_IHAC & _hoops_IHRPR _hoops_GIPR _hoops_GHIPR, _hoops_GAGPR _hoops_HSPH _hoops_CAPR _hoops_GGR _hoops_HGHC */
							float					_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

							_hoops_IRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_HRSAS - _hoops_PRSAS);
							_hoops_CRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_GPGSI - _hoops_PRSAS);

							_hoops_IGIC.points[b].x = (_hoops_PRSAS*_hoops_IGIC.points[a].x + (_hoops_IGIC.points[b].x - _hoops_PRSAS*_hoops_IGIC.points[a].x) * _hoops_IRSAS) * _hoops_PASAS;
							_hoops_IGIC.points[b].y = (_hoops_PRSAS*_hoops_IGIC.points[a].y + (_hoops_IGIC.points[b].y - _hoops_PRSAS*_hoops_IGIC.points[a].y) * _hoops_IRSAS) * _hoops_PASAS;
							_hoops_IGIC.points[b].z = _hoops_SRSAS;
							_hoops_IGIC.points[c].x = (_hoops_PRSAS*_hoops_IGIC.points[a].x + (_hoops_IGIC.points[c].x - _hoops_PRSAS*_hoops_IGIC.points[a].x) * _hoops_CRSAS) * _hoops_PASAS;
							_hoops_IGIC.points[c].y = (_hoops_PRSAS*_hoops_IGIC.points[a].y + (_hoops_IGIC.points[c].y - _hoops_PRSAS*_hoops_IGIC.points[a].y) * _hoops_CRSAS) * _hoops_PASAS;
							_hoops_IGIC.points[c].z = _hoops_SRSAS;

							if (_hoops_IGIC.colors != _hoops_IGIC._hoops_HIAI) {
								if (!_hoops_HIGSI) {
									_hoops_PCRGA (_hoops_IGIC.colors[a], _hoops_IGIC.colors[b], _hoops_IRSAS, _hoops_IGIC.colors[b]);
									_hoops_PCRGA (_hoops_IGIC.colors[a], _hoops_IGIC.colors[c], _hoops_CRSAS, _hoops_IGIC.colors[c]);
								}
							}
							else if (_hoops_IGIC._hoops_HPHSA != _hoops_IGIC._hoops_IGACP) {
								_hoops_ACRGA (_hoops_IGIC._hoops_HPHSA[a], _hoops_IGIC._hoops_HPHSA[b], _hoops_IRSAS, _hoops_IGIC._hoops_HPHSA[b]);
								_hoops_ACRGA (_hoops_IGIC._hoops_HPHSA[a], _hoops_IGIC._hoops_HPHSA[c], _hoops_CRSAS, _hoops_IGIC._hoops_HPHSA[c]);
							}
							if (_hoops_IGIC.planes != _hoops_IGIC._hoops_IHRGA) {
								_hoops_RGRGA (_hoops_IGIC.planes[a], _hoops_IGIC.planes[b], _hoops_IRSAS, _hoops_IGIC.planes[b]);
								_hoops_RGRGA (_hoops_IGIC.planes[a], _hoops_IGIC.planes[c], _hoops_CRSAS, _hoops_IGIC.planes[c]);
							}
#ifndef DISABLE_TEXTURING
							if (_hoops_IGIC.params != _hoops_IGIC._hoops_SHRGA) {
								_hoops_GGRGA (nr, &_hoops_IGIC.params[param_width*a], &_hoops_IGIC.params[param_width*b], _hoops_IRSAS,
													   &_hoops_IGIC.params[param_width*b], 1.0f, param_width);
								_hoops_GGRGA (nr, &_hoops_IGIC.params[param_width*a], &_hoops_IGIC.params[param_width*c], _hoops_CRSAS,
													   &_hoops_IGIC.params[param_width*c], 1.0f, param_width);
							}
#endif
						}
						else {
							/* _hoops_SAHR _hoops_IHRPR _hoops_SACH, _hoops_IRHH _hoops_PGCR _hoops_HIPH _hoops_RAIGR-_hoops_IHAC-_hoops_IHRPR', _hoops_IHAC-_hoops_IHAC'-_hoops_IHRPR' */
							float					_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

							/* _hoops_IHAC' (_hoops_GIAP _hoops_PPSR _hoops_IIGR _hoops_GIAP _hoops_HASAS) _hoops_GAPA _hoops_IHAC _hoops_PPR _hoops_IHRPR */
							_hoops_IRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_HRSAS) / (_hoops_GPGSI - _hoops_HRSAS);
							/* _hoops_IHRPR' (_hoops_HRSSR _hoops_PPSR _hoops_IIGR _hoops_GIAP _hoops_HASAS) _hoops_GAPA _hoops_RAIGR _hoops_PPR _hoops_IHRPR */
							_hoops_CRSAS = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_GPGSI - _hoops_PRSAS);

							_hoops_IGIC.points[0].x = _hoops_IGIC.points[b].x;
							_hoops_IGIC.points[0].y = _hoops_IGIC.points[b].y;
							_hoops_IGIC.points[0].z = _hoops_IGIC.points[b].z;
							_hoops_IGIC.points[1].x = (_hoops_HRSAS*_hoops_IGIC.points[b].x + (_hoops_IGIC.points[c].x - _hoops_HRSAS*_hoops_IGIC.points[b].x) * _hoops_IRSAS) * _hoops_PASAS;
							_hoops_IGIC.points[1].y = (_hoops_HRSAS*_hoops_IGIC.points[b].y + (_hoops_IGIC.points[c].y - _hoops_HRSAS*_hoops_IGIC.points[b].y) * _hoops_IRSAS) * _hoops_PASAS;
							_hoops_IGIC.points[1].z = _hoops_SRSAS;
							_hoops_IGIC.points[2].x = (_hoops_PRSAS*_hoops_IGIC.points[a].x + (_hoops_IGIC.points[c].x - _hoops_PRSAS*_hoops_IGIC.points[a].x) * _hoops_CRSAS) * _hoops_PASAS;
							_hoops_IGIC.points[2].y = (_hoops_PRSAS*_hoops_IGIC.points[a].y + (_hoops_IGIC.points[c].y - _hoops_PRSAS*_hoops_IGIC.points[a].y) * _hoops_CRSAS) * _hoops_PASAS;
							_hoops_IGIC.points[2].z = _hoops_SRSAS;
							_hoops_IGIC.points[c].x = _hoops_IGIC.points[2].x;
							_hoops_IGIC.points[c].y = _hoops_IGIC.points[2].y;
							_hoops_IGIC.points[c].z = _hoops_IGIC.points[2].z;
							_hoops_IGIC.points += 3;

							if (_hoops_IGIC.colors != _hoops_IGIC._hoops_HIAI) {
								if (!_hoops_HIGSI) {
									_hoops_IGIC.colors[0] = _hoops_IGIC.colors[b];
									_hoops_PCRGA (_hoops_IGIC.colors[b], _hoops_IGIC.colors[c], _hoops_IRSAS, _hoops_IGIC.colors[1]);
									_hoops_PCRGA (_hoops_IGIC.colors[a], _hoops_IGIC.colors[c], _hoops_CRSAS, _hoops_IGIC.colors[2]);
									_hoops_IGIC.colors[c] = _hoops_IGIC.colors[2];
									_hoops_IGIC.colors += 3;
								}
								else {
									_hoops_IGIC.colors[0] = _hoops_IGIC.colors[-1];
									_hoops_IGIC.colors++;
								}
							}
							else if (_hoops_IGIC._hoops_HPHSA != _hoops_IGIC._hoops_IGACP) {
								_hoops_IGIC._hoops_HPHSA[0] = _hoops_IGIC._hoops_HPHSA[b];
								_hoops_ACRGA (_hoops_IGIC._hoops_HPHSA[b], _hoops_IGIC._hoops_HPHSA[c], _hoops_IRSAS, _hoops_IGIC._hoops_HPHSA[1]);
								_hoops_ACRGA (_hoops_IGIC._hoops_HPHSA[a], _hoops_IGIC._hoops_HPHSA[c], _hoops_CRSAS, _hoops_IGIC._hoops_HPHSA[2]);
								_hoops_IGIC._hoops_HPHSA[c] = _hoops_IGIC._hoops_HPHSA[2];
								_hoops_IGIC._hoops_HPHSA += 3;
							}
							if (_hoops_IGIC.planes != _hoops_IGIC._hoops_IHRGA) {
								_hoops_IGIC.planes[0] = _hoops_IGIC.planes[b];
								_hoops_RGRGA (_hoops_IGIC.planes[b], _hoops_IGIC.planes[c], _hoops_IRSAS, _hoops_IGIC.planes[1]);
								_hoops_RGRGA (_hoops_IGIC.planes[a], _hoops_IGIC.planes[c], _hoops_CRSAS, _hoops_IGIC.planes[2]);
								_hoops_IGIC.planes[c] = _hoops_IGIC.planes[2];
								_hoops_IGIC.planes += 3;
							}
#ifndef DISABLE_TEXTURING
							if (_hoops_IGIC.params != _hoops_IGIC._hoops_SHRGA) {
								COPY_PARAMETER (&_hoops_IGIC.params[param_width*b], &_hoops_IGIC.params[param_width*0], param_width);
								_hoops_GGRGA (nr, &_hoops_IGIC.params[param_width*b], &_hoops_IGIC.params[param_width*c], _hoops_IRSAS,
													   &_hoops_IGIC.params[param_width*1], 1.0f, param_width);
								_hoops_GGRGA (nr, &_hoops_IGIC.params[param_width*a], &_hoops_IGIC.params[param_width*c], _hoops_CRSAS,
													   &_hoops_IGIC.params[param_width*2], 1.0f, param_width);
								COPY_PARAMETER (&_hoops_IGIC.params[param_width*2], &_hoops_IGIC.params[param_width*c], param_width);
								_hoops_IGIC.params += 3*param_width;
							}
#endif
						}
					}
				}
			}

			if (_hoops_IGIC.points != _hoops_IGIC._hoops_HRIGA &&
				((_hoops_IGIC.points-_hoops_IGIC._hoops_HRIGA) >= _hoops_AGACP || _hoops_PHHA == 0 && length == 0)) {
				if (_hoops_PPHIS == null)
					_hoops_PPHIS = nr;
				_hoops_IRPCP (_hoops_PPHIS, &_hoops_IGIC, ts, _hoops_HAACP, _hoops_HIGSI);
				_hoops_HRICS = null;
			}

			_hoops_HSPI = _hoops_ISPI;
			_hoops_ISPI = _hoops_CSPI;
			_hoops_PGRSH = _hoops_AGSIR;
			_hoops_AGSIR = _hoops_PGSIR;
			_hoops_AGRCA = !_hoops_AGRCA;
		}
	}

	if (_hoops_AAICS != _hoops_RAICS)
		FREE_ARRAY (_hoops_AAICS, 2*_hoops_AGH, RGBAS32);

#if 0
		/* _hoops_GHCA _hoops_RRP _hoops_IS _hoops_CASI _hoops_GH _hoops_SASI _hoops_AHAP _hoops_IAIAR _hoops_HII _hoops_RH _hoops_HIGR
		 * _hoops_RIIA _hoops_IIGR _hoops_GAR _hoops_SIRGR, _hoops_GAR _hoops_RGAR _hoops_HHH _hoops_CHH _hoops_HS _hoops_RPII _hoops_SHRAC
		 * _hoops_RGR _hoops_GHIR _hoops_AARI, _hoops_PPR _hoops_RH _hoops_ACSP _hoops_IIP _hoops_HHS _hoops_SHH _hoops_RPP _hoops_SR _hoops_GRHP _hoops_CAPR
		 */

		if (status->_hoops_PGPCP != null) {
			_hoops_ARPA const			*tmp = status->_hoops_PGPCP;

			FREE_ARRAY (tmp, status->point_count, _hoops_ARPA);
			status->_hoops_PGPCP = null;
		}
		if (ts->_hoops_AIACP != null) {
			_hoops_ARPA const			*tmp = ts->_hoops_AIACP;

			FREE_ARRAY_ALIGNED (tmp, ts->face_count, _hoops_ARPA, 16);
			((Tristrip alter*)ts)->_hoops_AIACP = null;
		}
	}
#endif

  _hoops_HPAGR:
	FREE_ARRAY_ALIGNED (_hoops_GHPCP, point_count, DC_Point, 16);
	FREE_ARRAY_ALIGNED (ws, point_count, float, 16);
	FREE_ARRAY (_hoops_ARCAR, point_count, _hoops_GRCAR);

	_hoops_HRPCP (&_hoops_IGIC);

	if (_hoops_IAICS && dc->_hoops_CGHAR) {
		FREE_ARRAY_ALIGNED(dc->_hoops_CGHAR, dc->_hoops_ICACP, int, 16);
		dc->_hoops_ICACP = 0;
		dc->_hoops_CGHAR = null;
	}

	if (_hoops_HAICS && dc->_hoops_AIACP != null) {
		FREE_ARRAY_ALIGNED (dc->_hoops_AIACP, dc->_hoops_PIACP, _hoops_ARPA, 16);
		dc->_hoops_AIACP = null;
		dc->_hoops_PIACP = 0;
	}

#endif
}


local void _hoops_PPICS (_hoops_CPSIP alter *_hoops_CSC, int flags)
{
	switch (_hoops_CSC->_hoops_IISIP) {
		case _hoops_PSSIP:
		case _hoops_SAGHC:
		case _hoops_ISSIP:
			_hoops_CSC->_hoops_PHSIP = _hoops_RHHSA|_hoops_GHHSA;
			break;
		case _hoops_SSSIP:
			_hoops_CSC->_hoops_PHSIP = _hoops_RHHSA;
			break;
		case _hoops_RGGCP:
		case _hoops_PGGCP:
		case _hoops_IGGCP:
		case _hoops_SGGCP:
		case _hoops_IRGCP:
			_hoops_CSC->_hoops_PHSIP = _hoops_CPHSA;
			break;
		case _hoops_PRGCP:
		case _hoops_RRGCP:
		case _hoops_SRGCP:
		case _hoops_RAGCP:
			_hoops_CSC->_hoops_PHSIP = _hoops_PPHSA;
			break;
	}
	if (BIT (flags, _hoops_GSGSH))
		_hoops_CSC->_hoops_PHSIP |= _hoops_GHHSA;
}


GLOBAL_FUNCTION void HD_Cache_From_Hidden_Tristrip (
	Hidden_Tristrip alter *		_hoops_ACSIP,
	float						_hoops_GCSIP) {
	Display_Context alter *		dc = (Display_Context alter *) _hoops_ACSIP->_hoops_APHGA->_hoops_SRA;
	_hoops_CPSIP alter *		_hoops_CSC = dc->_hoops_SPSIP;
	int							_hoops_HPICS, _hoops_GGIAR, p1, p2, _hoops_SSPAR, param_width;
	_hoops_GPGCP *	_hoops_IPICS;
	Net_Rendition			 	_hoops_PPHIS;
	_hoops_HHA			_hoops_CPICS;
	RGBAS32 *					_hoops_HPHSA = null;
	Tristrip const *			tristrip = _hoops_ACSIP->tristrips;
	bool						_hoops_CAACP = BIT (_hoops_ACSIP->flags, _hoops_CCGSH);
	bool						_hoops_AAIIS = BIT (_hoops_ACSIP->flags, _hoops_SCGSH);
	RGBA						tmp;
	DC_Point const *			_hoops_CGCAR = _hoops_ACSIP->_hoops_GHPCP;
	int							_hoops_SPICS;
	unsigned char				_hoops_IRIR;
	_hoops_ARPA const *				plane = null;
	RGB const *					rgb = null;
	_hoops_AHAH const &				_hoops_PHAH = _hoops_ACSIP->_hoops_APHGA->_hoops_ARA->_hoops_IHRH;

	_hoops_HPICS = _hoops_CSC->used / 3;
	while (_hoops_ACSIP->_hoops_GCSIP >= _hoops_GCSIP &&
		   _hoops_ACSIP->_hoops_GSSIP < _hoops_ACSIP->_hoops_APPH) {
		_hoops_IPICS = &_hoops_ACSIP->_hoops_CPGCP[_hoops_ACSIP->_hoops_GSSIP];
		_hoops_SPICS = _hoops_IPICS->_hoops_PPGCP + _hoops_IPICS->_hoops_IPGCP;
		param_width = tristrip->_hoops_GSSH ? tristrip->_hoops_GSSH->_hoops_GSHA : 0;
		if (tristrip->face_indices) {
			/* _hoops_HHHA _hoops_HSP _hoops_PSPI.  _hoops_HSP _hoops_CIHA _hoops_CRPR _hoops_HRGR _hoops_GGAIA _hoops_IS _hoops_GPHA _hoops_CIHA _hoops_CRPR */
			_hoops_SSPAR = tristrip->face_indices[_hoops_SPICS + 2];
#ifdef _hoops_IIIPA
			if (_hoops_ACSIP->_hoops_GSSIP < _hoops_ACSIP->_hoops_APPH - 1) {
				int _hoops_GHICS = _hoops_IPICS[1]._hoops_PPGCP + _hoops_IPICS[1]._hoops_IPGCP;
				int *next_fi = &tristrip->face_indices[_hoops_GHICS + 2];
				_hoops_SSAGR(next_fi);
			}
#endif
		}
		else
			/* _hoops_CHHA _hoops_HSP _hoops_PSPI.  _hoops_GRR _hoops_GHPAH _hoops_ARPP _hoops_RGR _hoops_RGHP 2 _hoops_GIHA _hoops_IS _hoops_HSPP */
			_hoops_SSPAR = _hoops_SPICS - 2*_hoops_IPICS->_hoops_HPGCP;
		if (!_hoops_ACSIP->_hoops_AGHAR || _hoops_ACSIP->_hoops_AGHAR[_hoops_SSPAR]) {
			_hoops_PPHIS = _hoops_ACSIP->_hoops_APHGA; /* _hoops_RIPS _hoops_PPAP _hoops_RHICS */
			_hoops_HPHSA = _hoops_ACSIP->_hoops_GHGCP;
		}
		else {
			if (!_hoops_ACSIP->_hoops_PARHH) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								 "Internal mismatch detected in backplane culling of transparent triangles.");
				goto _hoops_RCAI;
			}
			_hoops_PPHIS = _hoops_ACSIP->_hoops_PARHH; /* _hoops_ISSC _hoops_PPAP _hoops_RHICS */
			if (_hoops_ACSIP->_hoops_GHGCP)
				_hoops_HPHSA = _hoops_ACSIP->_hoops_GHGCP + _hoops_ACSIP->_hoops_AGH;
		}
		_hoops_CPICS = _hoops_PPHIS->_hoops_IHA->_hoops_CHA;
		_hoops_IRIR = (unsigned char)(255.99f * _hoops_CPICS->_hoops_IRIR);

		if (_hoops_CSC->used == 0) {
			if (param_width > _hoops_CSC->_hoops_RHSIP) {
				FREE_ARRAY (_hoops_CSC->params,
							_hoops_CSC->_hoops_RHSIP*_hoops_GHSIP,
							_hoops_RSSH);
				_hoops_CSC->_hoops_RHSIP = param_width;
				ALLOC_ARRAY_CACHED (_hoops_CSC->params,
							 _hoops_CSC->_hoops_RHSIP*_hoops_GHSIP,
							 _hoops_RSSH);
			}
			_hoops_CSC->param_flags = tristrip->_hoops_GSSH ? tristrip->_hoops_GSSH->_hoops_SCAI : 0;
			_hoops_CSC->param_width = param_width;
			_hoops_CSC->_hoops_IISIP = _hoops_ACSIP->_hoops_IISIP;
			_hoops_PPICS (_hoops_CSC, _hoops_ACSIP->flags);
			if (_hoops_CSC->_hoops_PHSIP == _hoops_PPHSA)
				_hoops_CSC->_hoops_HPHSA[0] = _hoops_HPHSA[_hoops_SSPAR];
			_hoops_CSC->nr = _hoops_PPHIS;
		}
		else {
			if (_hoops_PPHIS->_hoops_CPA != _hoops_CSC->nr->_hoops_CPA ||
				_hoops_ACSIP->_hoops_IISIP != _hoops_CSC->_hoops_IISIP ||
				param_width != _hoops_CSC->param_width) {

				HD_Flush_Hidden_Item_Cache(dc);
				_hoops_HPICS = 0;

				if (param_width > _hoops_CSC->_hoops_RHSIP) {
					FREE_ARRAY (_hoops_CSC->params,
								_hoops_CSC->_hoops_RHSIP*_hoops_GHSIP,
								_hoops_RSSH);
					_hoops_CSC->_hoops_RHSIP = param_width;
					ALLOC_ARRAY_CACHED (_hoops_CSC->params,
								 _hoops_CSC->_hoops_RHSIP*_hoops_GHSIP,
								 _hoops_RSSH);
				}
				_hoops_CSC->param_flags = tristrip->_hoops_GSSH ? tristrip->_hoops_GSSH->_hoops_SCAI : 0;
				_hoops_CSC->param_width = param_width;
				_hoops_CSC->_hoops_IISIP = _hoops_ACSIP->_hoops_IISIP;
				_hoops_PPICS (_hoops_CSC, _hoops_ACSIP->flags);
				if (_hoops_CSC->_hoops_PHSIP == _hoops_PPHSA)
					_hoops_CSC->_hoops_HPHSA[0] = _hoops_HPHSA[_hoops_SSPAR];
				_hoops_CSC->nr = _hoops_PPHIS;
			}
			else if (_hoops_CSC->used > _hoops_GHSIP - 3) {
				HD_Flush_Hidden_Item_Cache(dc);
				_hoops_HPICS = 0;
				_hoops_CSC->nr = _hoops_PPHIS;
				_hoops_CSC->_hoops_IISIP = _hoops_ACSIP->_hoops_IISIP;
			}
		}
		if (tristrip->lengths[_hoops_IPICS->_hoops_HPGCP] > 0) {
			/* _hoops_SCPH _hoops_CGGR */
			_hoops_GGIAR = tristrip->_hoops_AIHA[_hoops_SPICS];
			if (_hoops_IPICS->_hoops_IPGCP & 0x1) {
				p1 = tristrip->_hoops_AIHA[_hoops_SPICS + 1];
				p2 = tristrip->_hoops_AIHA[_hoops_SPICS + 2];
			}
			else {
				p2 = tristrip->_hoops_AIHA[_hoops_SPICS + 1];
				p1 = tristrip->_hoops_AIHA[_hoops_SPICS + 2];
			}
		}
		else {
			/* _hoops_SCPH _hoops_PRII */
			_hoops_GGIAR = tristrip->_hoops_AIHA[_hoops_IPICS->_hoops_PPGCP];
			p1 = tristrip->_hoops_AIHA[_hoops_SPICS + 1];
			p2 = tristrip->_hoops_AIHA[_hoops_SPICS + 2];
		}
		_hoops_CSC->points[_hoops_CSC->used+0] = _hoops_CGCAR[_hoops_GGIAR];
		_hoops_CSC->points[_hoops_CSC->used+1] = _hoops_CGCAR[p1];
		_hoops_CSC->points[_hoops_CSC->used+2] = _hoops_CGCAR[p2];

		switch (_hoops_ACSIP->_hoops_IISIP) {
			case _hoops_ISSIP: /* _hoops_GPIC _hoops_RCIAR, _hoops_GAGS */
				_hoops_AIGA (&tristrip->_hoops_GSSH->_hoops_CCHA[_hoops_GGIAR * tristrip->_hoops_GSSH->_hoops_GSHA],
							 tristrip->_hoops_GSSH->_hoops_GSHA, _hoops_RSSH, 
							 &_hoops_CSC->params[_hoops_CSC->used * tristrip->_hoops_GSSH->_hoops_GSHA]);			
				_hoops_AIGA (&tristrip->_hoops_GSSH->_hoops_CCHA[p1 * tristrip->_hoops_GSSH->_hoops_GSHA],
							 tristrip->_hoops_GSSH->_hoops_GSHA, _hoops_RSSH, 
							 &_hoops_CSC->params[(_hoops_CSC->used+1) * tristrip->_hoops_GSSH->_hoops_GSHA]);			
				_hoops_AIGA (&tristrip->_hoops_GSSH->_hoops_CCHA[p2 * tristrip->_hoops_GSSH->_hoops_GSHA],
							 tristrip->_hoops_GSSH->_hoops_GSHA, _hoops_RSSH, 
							 &_hoops_CSC->params[(_hoops_CSC->used+2) * tristrip->_hoops_GSSH->_hoops_GSHA]);			
				

				_hoops_CSC->planes[_hoops_CSC->used+0] = tristrip->_hoops_PRHH[_hoops_SSPAR];
				_hoops_CSC->planes[_hoops_CSC->used+1] = tristrip->_hoops_PRHH[_hoops_SSPAR];
				_hoops_CSC->planes[_hoops_CSC->used+2] = tristrip->_hoops_PRHH[_hoops_SSPAR];

				if (_hoops_ACSIP->_hoops_RIACP) {
					/*_hoops_IHAH->_hoops_GHC[_hoops_IHAH->_hoops_IGI+0] = _hoops_CRHH->_hoops_HPPIS[_hoops_AHICS];
					_hoops_IHAH->_hoops_GHC[_hoops_IHAH->_hoops_IGI+1] = _hoops_CRHH->_hoops_HPPIS[_hoops_AHICS];
					_hoops_IHAH->_hoops_GHC[_hoops_IHAH->_hoops_IGI+2] = _hoops_CRHH->_hoops_HPPIS[_hoops_AHICS];*/
					_hoops_CSC->planes[_hoops_CSC->used+0] = _hoops_ACSIP->_hoops_RIACP[_hoops_SSPAR];
					_hoops_CSC->planes[_hoops_CSC->used+1] = _hoops_ACSIP->_hoops_RIACP[_hoops_SSPAR];
					_hoops_CSC->planes[_hoops_CSC->used+2] = _hoops_ACSIP->_hoops_RIACP[_hoops_SSPAR];
				}

				_hoops_HHHI;
			case _hoops_RRGCP:	/* _hoops_GPIC _hoops_RCIAR, _hoops_RIR _hoops_HSP _hoops_HAIR */
				if (_hoops_ACSIP->_hoops_IISIP == _hoops_RRGCP)	/* _hoops_GA'_hoops_RA _hoops_RPP _hoops_HRRHH _hoops_HII _hoops_ARRS */
					_hoops_CSC->flags |= _hoops_HHSIP;
				_hoops_HHHI;
			case _hoops_SRGCP: /* _hoops_GPIC _hoops_RCIAR */
				if (_hoops_HPHSA[_hoops_SSPAR] == _hoops_CAHSR::_hoops_SAHSR || _hoops_AAIIS) {
					if (tristrip->_hoops_PAGI)
						rgb = &tristrip->_hoops_PAGI[_hoops_SSPAR];
					_hoops_CSACP (_hoops_PPHIS, _hoops_CPICS, _hoops_CAACP, &tristrip->points[_hoops_GGIAR], rgb, &tristrip->_hoops_PRHH[_hoops_SSPAR], null, &tmp);
					//_hoops_PHICS (_hoops_HHICS, _hoops_IHICS, _hoops_CHICS, &_hoops_CRHH->_hoops_RSSA[_hoops_CPGAS], _hoops_AIHSR, &_hoops_SHICS->_hoops_GIICS[_hoops_AHICS], _hoops_IRAP, &_hoops_AIPSH);

					_hoops_HPHSA[_hoops_SSPAR] = RGBAS32 (tmp, _hoops_IRIR);
					_hoops_APIIS (_hoops_PHAH, _hoops_HPHSA[_hoops_SSPAR]);
					_hoops_SIPCP (dc, _hoops_HPHSA[_hoops_SSPAR]);
				}
				if (_hoops_CSC->_hoops_HPHSA[0] != _hoops_HPHSA[_hoops_SSPAR])
					_hoops_CSC->flags |= _hoops_HHSIP;
				_hoops_CSC->_hoops_HPHSA[_hoops_HPICS] = _hoops_HPHSA[_hoops_SSPAR];
				break;

			case _hoops_SAGHC: /* _hoops_IRIC _hoops_RCIAR, _hoops_GAGS */
			case _hoops_PSSIP: /* _hoops_IRIC _hoops_RCIAR, _hoops_GAGS */
				//_hoops_RPP (_hoops_CSPH->_hoops_RIICS) {
				if (_hoops_ACSIP->_hoops_AARHH) {
					/*_hoops_IHAH->_hoops_GHC[_hoops_IHAH->_hoops_IGI+0] = _hoops_CSPH->_hoops_RIICS[_hoops_CPGAS];
					_hoops_IHAH->_hoops_GHC[_hoops_IHAH->_hoops_IGI+1] = _hoops_CSPH->_hoops_RIICS[_hoops_PARAA];
					_hoops_IHAH->_hoops_GHC[_hoops_IHAH->_hoops_IGI+2] = _hoops_CSPH->_hoops_RIICS[_hoops_AARAA];*/
					_hoops_CSC->planes[_hoops_CSC->used+0] = _hoops_ACSIP->_hoops_AARHH[_hoops_GGIAR];
					_hoops_CSC->planes[_hoops_CSC->used+1] = _hoops_ACSIP->_hoops_AARHH[p1];
					_hoops_CSC->planes[_hoops_CSC->used+2] = _hoops_ACSIP->_hoops_AARHH[p2];
				}
				_hoops_HHHI;
			case _hoops_SSSIP:	/* _hoops_GAACP, _hoops_GAGS */
				_hoops_AIGA (&tristrip->_hoops_GSSH->_hoops_CCHA[_hoops_GGIAR * tristrip->_hoops_GSSH->_hoops_GSHA],
							 tristrip->_hoops_GSSH->_hoops_GSHA, _hoops_RSSH, 
							 &_hoops_CSC->params[_hoops_CSC->used * tristrip->_hoops_GSSH->_hoops_GSHA]);			
				_hoops_AIGA (&tristrip->_hoops_GSSH->_hoops_CCHA[p1 * tristrip->_hoops_GSSH->_hoops_GSHA],
							 tristrip->_hoops_GSSH->_hoops_GSHA, _hoops_RSSH, 
							 &_hoops_CSC->params[(_hoops_CSC->used+1) * tristrip->_hoops_GSSH->_hoops_GSHA]);			
				_hoops_AIGA (&tristrip->_hoops_GSSH->_hoops_CCHA[p2 * tristrip->_hoops_GSSH->_hoops_GSHA],
							 tristrip->_hoops_GSSH->_hoops_GSHA, _hoops_RSSH, 
							 &_hoops_CSC->params[(_hoops_CSC->used+2) * tristrip->_hoops_GSSH->_hoops_GSHA]);			

				_hoops_CSC->rgba_colors[_hoops_CSC->used] = _hoops_IGISA::_hoops_IAHHP;
				_hoops_CSC->rgba_colors[_hoops_CSC->used+1] = _hoops_CSC->rgba_colors[_hoops_CSC->used];
				_hoops_CSC->rgba_colors[_hoops_CSC->used+2] = _hoops_CSC->rgba_colors[_hoops_CSC->used];
				break;

			case _hoops_SGGCP:	/* _hoops_IRIC _hoops_RCIAR, _hoops_RIR _hoops_HSP _hoops_PSHA */
			case _hoops_PGGCP:	/* _hoops_GPIC _hoops_RCIAR, _hoops_RIR _hoops_GPHA _hoops_PSHA */
				_hoops_CSC->flags |= _hoops_HHSIP;
				_hoops_HHHI;
			case _hoops_RGGCP:	/* _hoops_IRIC _hoops_RCIAR, _hoops_RIR _hoops_GPHA _hoops_PSHA */
			case _hoops_IRGCP:	/* _hoops_IRIC _hoops_RCIAR */
				if (_hoops_HPHSA[_hoops_GGIAR] == _hoops_CAHSR::_hoops_SAHSR || _hoops_AAIIS) {
					/*_hoops_RPP (_hoops_CSPH->_hoops_RIICS)
						_hoops_IPPA = &_hoops_CSPH->_hoops_RIICS[_hoops_CPGAS];*/
					if (_hoops_ACSIP->_hoops_AARHH && _hoops_ACSIP->_hoops_IISIP != _hoops_PGGCP)
						plane = &_hoops_ACSIP->_hoops_AARHH[_hoops_GGIAR];
					if (tristrip->_hoops_PCHA)
						rgb = &tristrip->_hoops_PCHA[_hoops_GGIAR];
					else if (tristrip->_hoops_PAGI)
						rgb = &tristrip->_hoops_PAGI[_hoops_SSPAR];
					_hoops_CSACP (_hoops_PPHIS, _hoops_CPICS, _hoops_CAACP, &tristrip->points[_hoops_GGIAR], rgb, plane, null, &tmp);
					_hoops_HPHSA[_hoops_GGIAR] = RGBAS32 (tmp, _hoops_IRIR);
					_hoops_APIIS (_hoops_PHAH, _hoops_HPHSA[_hoops_GGIAR]);
					_hoops_SIPCP (dc, _hoops_HPHSA[_hoops_GGIAR]);
				}
				_hoops_CSC->_hoops_HPHSA[_hoops_CSC->used] = _hoops_HPHSA[_hoops_GGIAR];
				if (_hoops_HPHSA[p1] == _hoops_CAHSR::_hoops_SAHSR || _hoops_AAIIS) {
					/*_hoops_RPP (_hoops_CSPH->_hoops_RIICS)
						_hoops_IPPA = &_hoops_CSPH->_hoops_RIICS[_hoops_PARAA];*/
					if (_hoops_ACSIP->_hoops_AARHH && _hoops_ACSIP->_hoops_IISIP != _hoops_PGGCP)
						plane = &_hoops_ACSIP->_hoops_AARHH[p1];
					if (tristrip->_hoops_PCHA)
						rgb = &tristrip->_hoops_PCHA[p1];
					else if (tristrip->_hoops_PAGI)
						rgb = &tristrip->_hoops_PAGI[_hoops_SSPAR];
					_hoops_CSACP (_hoops_PPHIS, _hoops_CPICS, _hoops_CAACP, &tristrip->points[p1], rgb, plane, null, &tmp);
					_hoops_HPHSA[p1] = RGBAS32 (tmp, _hoops_IRIR);
					_hoops_APIIS (_hoops_PHAH, _hoops_HPHSA[p1]);
					_hoops_SIPCP (dc, _hoops_HPHSA[p1]);
				}
				_hoops_CSC->_hoops_HPHSA[_hoops_CSC->used+1] = _hoops_HPHSA[p1];
				if (_hoops_HPHSA[p2] == _hoops_CAHSR::_hoops_SAHSR || _hoops_AAIIS) {
					/*_hoops_RPP (_hoops_CSPH->_hoops_RIICS)
						_hoops_IPPA = &_hoops_CSPH->_hoops_RIICS[_hoops_AARAA];*/
					if (_hoops_ACSIP->_hoops_AARHH && _hoops_ACSIP->_hoops_IISIP != _hoops_PGGCP)
						plane = &_hoops_ACSIP->_hoops_AARHH[p2];
					if (tristrip->_hoops_PCHA)
						rgb = &tristrip->_hoops_PCHA[p2];
					else if (tristrip->_hoops_PAGI)
						rgb = &tristrip->_hoops_PAGI[_hoops_SSPAR];
					_hoops_CSACP (_hoops_PPHIS, _hoops_CPICS, _hoops_CAACP, &tristrip->points[p2], rgb, plane, null, &tmp);
					_hoops_HPHSA[p2] = RGBAS32 (tmp, _hoops_IRIR);
					_hoops_APIIS (_hoops_PHAH, _hoops_HPHSA[p2]);
					_hoops_SIPCP (dc, _hoops_HPHSA[p2]);
				}
				_hoops_CSC->_hoops_HPHSA[_hoops_CSC->used+2] = _hoops_HPHSA[p2];
				break;

			case _hoops_IGGCP:	/* _hoops_RIR _hoops_GPHA _hoops_PSHA */
				_hoops_CSC->_hoops_HPHSA[_hoops_CSC->used] = RGBAS32 (tristrip->_hoops_PCHA[_hoops_GGIAR], _hoops_IRIR);
				_hoops_APIIS (_hoops_PHAH, _hoops_CSC->_hoops_HPHSA[_hoops_CSC->used]);
				_hoops_SIPCP (dc, _hoops_CSC->_hoops_HPHSA[_hoops_CSC->used]);
				_hoops_CSC->_hoops_HPHSA[_hoops_CSC->used+1] = RGBAS32 (tristrip->_hoops_PCHA[p1], _hoops_IRIR);
				_hoops_APIIS (_hoops_PHAH, _hoops_CSC->_hoops_HPHSA[_hoops_CSC->used+1]);
				_hoops_SIPCP (dc, _hoops_CSC->_hoops_HPHSA[_hoops_CSC->used+1]);
				_hoops_CSC->_hoops_HPHSA[_hoops_CSC->used+2] = RGBAS32 (tristrip->_hoops_PCHA[p2], _hoops_IRIR);
				_hoops_APIIS (_hoops_PHAH, _hoops_CSC->_hoops_HPHSA[_hoops_CSC->used+2]);
				_hoops_SIPCP (dc, _hoops_CSC->_hoops_HPHSA[_hoops_CSC->used+2]);
				break;

			case _hoops_PRGCP:	/* _hoops_RIR _hoops_HSP _hoops_HAIR */
				_hoops_CSC->flags |= _hoops_HHSIP;
				_hoops_CSC->_hoops_HPHSA[_hoops_HPICS] = RGBAS32 (tristrip->_hoops_PAGI[_hoops_SSPAR], _hoops_IRIR);
				_hoops_APIIS (_hoops_PHAH, _hoops_CSC->_hoops_HPHSA[_hoops_HPICS]);
				_hoops_SIPCP (dc, _hoops_CSC->_hoops_HPHSA[_hoops_HPICS]);
				break;

			case _hoops_RAGCP:
				if (_hoops_CSC->used == 0) {
					_hoops_AAASP (dc, _hoops_PPHIS->_hoops_IHA->color, dc->_hoops_PGCC._hoops_PIHSR, _hoops_CSC->_hoops_HPHSA[_hoops_CSC->used]);
					_hoops_CSC->_hoops_HPHSA[_hoops_CSC->used].a = (unsigned char)(255.99f * _hoops_PPHIS->_hoops_IHA->_hoops_CHA->_hoops_IRIR);
				}
				else
					_hoops_CSC->_hoops_HPHSA[_hoops_CSC->used] = _hoops_CSC->_hoops_HPHSA[_hoops_CSC->used-1];
				_hoops_CSC->_hoops_HPHSA[_hoops_CSC->used+1] = _hoops_CSC->_hoops_HPHSA[_hoops_CSC->used];
				_hoops_CSC->_hoops_HPHSA[_hoops_CSC->used+2] = _hoops_CSC->_hoops_HPHSA[_hoops_CSC->used];
				break;

			default:
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								 "Hidden tristrip has undecipherable attributes");
				break;
		}
		if (BIT(_hoops_ACSIP->flags, _hoops_GSGSH)) {
			_hoops_CSC->planes[_hoops_CSC->used+0] = _hoops_ACSIP->_hoops_AARHH[_hoops_GGIAR];
			_hoops_CSC->planes[_hoops_CSC->used+1] = _hoops_ACSIP->_hoops_AARHH[p1];
			_hoops_CSC->planes[_hoops_CSC->used+2] = _hoops_ACSIP->_hoops_AARHH[p2];
		}
		_hoops_CSC->used += 3;
		_hoops_HPICS++;
  _hoops_RCAI:
		_hoops_ACSIP->_hoops_GSSIP++;
		if (_hoops_ACSIP->_hoops_GSSIP < _hoops_ACSIP->_hoops_APPH)
			_hoops_ACSIP->_hoops_GCSIP = _hoops_ACSIP->_hoops_SPGCP[_hoops_ACSIP->_hoops_GSSIP];
	}
}


