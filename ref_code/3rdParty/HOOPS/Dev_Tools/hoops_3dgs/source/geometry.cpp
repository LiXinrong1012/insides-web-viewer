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
 * $Id: obf_tmp.txt 1.37 2010-09-29 17:37:43 reuben Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#define _hoops_IRCHH		0x0001
#define _hoops_CRCHH		0x0002
#define _hoops_SRCHH		0x0004
#define _hoops_GACHH		0x0008
#define _hoops_RACHH		0x0010
#define _hoops_AACHH		0x0020
#define _hoops_PACHH		0x0040
#define _hoops_HACHH		0x0100
#define _hoops_IACHH	0x0200
#define _hoops_CACHH	0x0400


local const _hoops_IGRCR _hoops_SACHH[] = {
	{_hoops_IRCHH,			_hoops_GRRCR ("points"),			_hoops_RRRCR, 0, false},
	{_hoops_CRCHH,		_hoops_GRRCR ("face list"),			_hoops_RRRCR, 0, false},
	{_hoops_SRCHH,	_hoops_GRRCR ("face planes"),		_hoops_RRRCR, 0, false},
	{_hoops_GACHH,	_hoops_GRRCR ("face colors"),		_hoops_RRRCR, 0, false},
	{_hoops_RACHH,		_hoops_GRRCR ("face flags"),		_hoops_RRRCR, 0, false},
	{_hoops_AACHH,	_hoops_GRRCR ("rgb rasters"),		_hoops_RRRCR, 0, false},
	{_hoops_PACHH,	_hoops_GRRCR ("rgba rasters"),		_hoops_RRRCR, 0, false},
	{_hoops_HACHH,	_hoops_GRRCR ("mapped 8 rasters"),	_hoops_RRRCR, 0, false},
	{_hoops_IACHH,	_hoops_GRRCR ("mapped 16 rasters"),	_hoops_RRRCR, 0, false},
	{_hoops_CACHH,	_hoops_GRRCR ("grayscale rasters"),	_hoops_RRRCR, 0, false},
};

#define _hoops_GPCHH	0x00000001	// _hoops_SIH _hoops_IH _hoops_RPCHH _hoops_AAP
#define _hoops_APCHH				0x00000002
#define _hoops_PPCHH			-1			// _hoops_HHHR _hoops_HSH _hoops_IH _hoops_HGAI _hoops_PGPP
#define _hoops_HPCHH			-2

local const _hoops_IGRCR _hoops_IPCHH[] = {
	{_hoops_GPCHH,	_hoops_GRRCR ("camera relative"),		_hoops_RRRCR, 0, true},
	{_hoops_GPCHH,	_hoops_GRRCR ("camera-relative"),		_hoops_RRRCR, 0, true},
	{_hoops_APCHH,			_hoops_GRRCR ("orientation"),			_hoops_SPPCR, -6, true},

	{_hoops_PPCHH,		_hoops_GRRCR ("bounding cuboid"),		_hoops_SPPCR, 6, false},
	{_hoops_HPCHH,		_hoops_GRRCR ("bounding sphere"),		_hoops_SPPCR, 4, false},
};




GLOBAL_FUNCTION void HI_Show_Geometry_Options (
	Geometry const *		geo,
	char alter *			list,
	int						_hoops_GGCIR) 
{
	_hoops_CSPPR();
	if (geo == null || BIT (geo->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY,
			"Provided key does not refer to a valid geometry");
		goto done;
	}
	switch (geo->type) {
		case _hoops_ICIP: {
			Light const	*light = (Light const *) geo;
			if (BIT (light->flags, _hoops_RISGP))
				HI_Return_Chars (list, _hoops_GGCIR, "camera relative,", 15);
			else
				HI_Return_Chars (list, _hoops_GGCIR, "", 0);
		} break;

		case _hoops_IIIP: {
			Polyline const	*polyline = (Polyline const *) geo;

			if (polyline->orientation) {
				char buf[128];
				char *_hoops_ASAPR = buf;
				char *_hoops_PSAPR = _hoops_ASAPR + _hoops_GGAPR(buf);
				_hoops_ASAPR = HI_Copy_Chars ("orientation=(", _hoops_ASAPR);
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &polyline->orientation[0].x);
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &polyline->orientation[0].y);
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &polyline->orientation[0].z);

				if (BIT(polyline->_hoops_RRHH,_hoops_HCPIR)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &polyline->orientation[1].x);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &polyline->orientation[1].y);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &polyline->orientation[1].z);
				}

				_hoops_ASAPR[-1] = ')';

				HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
			}
			else
				HI_Return_Chars (list, _hoops_GGCIR, "", 0);
		} break;

		case _hoops_PCIP: {
			Marker const	*marker = (Marker const *) geo;

			if (marker->orientation) {
				char buf[128];
				char *_hoops_ASAPR = buf;
				char *_hoops_PSAPR = _hoops_ASAPR + _hoops_GGAPR(buf);
				_hoops_ASAPR = HI_Copy_Chars ("orientation=(", _hoops_ASAPR);
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &marker->orientation[0].x);
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &marker->orientation[0].y);
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &marker->orientation[0].z);

				if (BIT(marker->_hoops_RRHH,_hoops_IHPIR)) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &marker->orientation[1].x);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &marker->orientation[1].y);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", &marker->orientation[1].z);
				}

				_hoops_ASAPR[-1] = ')';

				HI_Return_Chars (list, _hoops_GGCIR, buf, (int)(_hoops_ASAPR - buf));
			}
			else
				HI_Return_Chars (list, _hoops_GGCIR, "", 0);
		} break;

		default: {
			HI_Return_Chars (list, _hoops_GGCIR, "", 0);
		} break;
	}

done:
	_hoops_IRRPR();
}


HC_INTERFACE void HC_CDECL HC_Show_Geometry_Options (
	Key			key,
	char *		list)
{
	_hoops_PAPPR context("Show_Geometry_Options");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Geometry_Options () */\n");
	);
	
	_hoops_CSPPR();

	Geometry const * geo = (Geometry const *) _hoops_RCSSR (context, key);

	HI_Show_Geometry_Options(geo, list, -1);

	_hoops_IRRPR();

#endif
}



HC_INTERFACE void HC_CDECL HC_Set_Geometry_Options (
	Key				key,
	char const *	list) 
{
	_hoops_PAPPR context("Set_Geometry_Options");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Set_Geometry_Options () */ \n");
	);

	_hoops_CSPPR();
	int				offset;
	Geometry *	geometry = (Geometry *)_hoops_SISIR (context, key, &offset);

	if (geometry == null || BIT (geometry->_hoops_RRHH, _hoops_HGAGR) ||
		geometry->type < _hoops_AHRIR ||
		 geometry->type > _hoops_PHRIR) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "Provided key does not refer to a valid geometry");
		_hoops_IRRPR();
		return;
	}

	_hoops_HIACR (_hoops_CPCHH, _hoops_IPCHH);

	Option_Value *	option_list;
	Option_Value *	option;

	if (!HI_Parse_Options (context, list, _hoops_CIACR (_hoops_CPCHH),
							&option_list, _hoops_SIACR)) {
		_hoops_IRRPR();
		return;
	}

	if ((option = option_list) != null) {
		_hoops_RPPPR();
		do {
			switch (option->type->id) {
				case _hoops_GPCHH: {
					if (geometry->type == _hoops_ICIP) {
						Light *		light = (Light *)geometry;

						if (option->_hoops_GCACR)
							light->flags &= ~_hoops_RISGP;
						else
							light->flags |= _hoops_RISGP;
					}
					else {
						HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY, "'camera relative' can only be applied to lights");
					}
				}	break;

				case _hoops_APCHH: {
					if (geometry->type == _hoops_PIRS)
						geometry = HI_Isolate_Marker_From_Multimarker (context, (_hoops_GRPGR *)geometry, offset);


					if (geometry->type == _hoops_IIIP) {
						Polyline *		polyline = (Polyline *)geometry;

						/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_HGCR _hoops_IRS _hoops_SPCHH _hoops_PHI _hoops_IIGR _hoops_PSPAR */
						if (!option->_hoops_GCACR && 
							option->_hoops_AIPCR != 3 &&
							option->_hoops_AIPCR != 6) {
							HE_ERROR(HEC_GEOMETRY, HES_INVALID_COUNT,
								"line pattern orientation must be either one or two vectors");
							break;
						}

						/* _hoops_CASI _hoops_GGSR _hoops_GII _hoops_RHGS _hoops_PSPAR _hoops_SHR */
						if (polyline->orientation)
							if (BIT(geometry->_hoops_RRHH, _hoops_HCPIR))
								FREE_ARRAY(polyline->orientation, 2, Vector);
							else
								FREE_ARRAY(polyline->orientation, 1, Vector);
						polyline->orientation = null;
						polyline->_hoops_RRHH &= ~_hoops_HCPIR;

						if (!option->_hoops_GCACR) {
							/* _hoops_RGHH _hoops_ARAR _hoops_IH _hoops_GSSR _hoops_RGAR _hoops_PPR _hoops_HARGR _hoops_PSAI */
							if (option->_hoops_AIPCR == 6) {
								polyline->_hoops_RRHH |= _hoops_HCPIR;
								ALLOC_ARRAY(polyline->orientation, 2, Vector);
								_hoops_AIGA(option->value._hoops_PIPCR, 2, Vector, polyline->orientation);

								if (!HI_Normalize (&polyline->orientation[0]) ||
									!HI_Normalize (&polyline->orientation[1])) {
									HE_WARNING (HEC_GEOMETRY, HES_ZERO_LENGTH, "Vector of zero length.");
								}
							}
							else {
								ALLOC_ARRAY(polyline->orientation,1,Vector);
								_hoops_AIGA(option->value._hoops_PIPCR, 1, Vector, polyline->orientation);

								if (!HI_Normalize (&polyline->orientation[0])) {
									HE_WARNING (HEC_GEOMETRY, HES_ZERO_LENGTH, "Vector of zero length.");
								}
							}
						}
					}
					else if (geometry->type == _hoops_PCIP) {
						Marker *		marker = (Marker *)geometry;

						/* _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_HGCR _hoops_IRS _hoops_SPCHH _hoops_PHI _hoops_IIGR _hoops_PSPAR */
						if (!option->_hoops_GCACR && 
							option->_hoops_AIPCR != 3 &&
							option->_hoops_AIPCR != 6) {
							HE_ERROR(HEC_GEOMETRY, HES_INVALID_COUNT,"marker orientation must be either one or two vectors");
							break;
						}

						/* _hoops_CASI _hoops_GGSR _hoops_GII _hoops_RHGS _hoops_PSPAR _hoops_SHR */
						if (marker->orientation)
							if (BIT(geometry->_hoops_RRHH, _hoops_IHPIR))
								FREE_ARRAY(marker->orientation, 2, Vector);
							else
								FREE_ARRAY(marker->orientation, 1, Vector);
						marker->orientation = null;
						marker->_hoops_RRHH &= ~_hoops_IHPIR;

						if (!option->_hoops_GCACR) {
							/* _hoops_RGHH _hoops_ARAR _hoops_IH _hoops_GSSR _hoops_RGAR _hoops_PPR _hoops_HARGR _hoops_PSAI */
							if (option->_hoops_AIPCR == 6) {
								marker->_hoops_RRHH |= _hoops_IHPIR;
								ALLOC_ARRAY(marker->orientation, 2, Vector);
								_hoops_AIGA(option->value._hoops_PIPCR, 2, Vector, marker->orientation);

								if (!HI_Normalize (&marker->orientation[0]) ||
									!HI_Normalize (&marker->orientation[1])) {
									HE_WARNING (HEC_GEOMETRY, HES_ZERO_LENGTH,
										"Vector of zero length.");
								}
							}
							else {
								ALLOC_ARRAY(marker->orientation,1,Vector);
								_hoops_AIGA(option->value._hoops_PIPCR, 1, Vector, marker->orientation);

								if (!HI_Normalize (&marker->orientation[0])) {
									HE_WARNING (HEC_GEOMETRY, HES_ZERO_LENGTH,"Vector of zero length.");
								}
							}
						}
					}
					else {
						HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY,"'orientation' cannot be applied to this geometry");
					}
				}	break;

				case _hoops_PPCHH:
				case _hoops_HPCHH: {
					Bounding		bounding;

					if (option->type->id == _hoops_PPCHH)
						bounding = Bounding::Create(_hoops_SASC(*(Point const *)&option->value._hoops_PIPCR[0],
																  *(Point const *)&option->value._hoops_PIPCR[3]));
					else
						bounding = Bounding::Create(_hoops_CAIS(*(Point const *)&option->value._hoops_PIPCR[0],
																  option->value._hoops_PIPCR[3]));

					// _hoops_ARP _hoops_SGI _hoops_PPR _hoops_SRPA _hoops_GHCHH _hoops_GPP _hoops_PCHC _hoops_AGSAR
					switch (geometry->type) {
						case _hoops_ICIP: {
							bounding->_hoops_CGCIR = 0.1f;
						}	break;

						// _hoops_GSHRH _hoops_CGRPR _hoops_IS _hoops_IASC
						case _hoops_SCIP:
						case _hoops_GSIP: {
							Polyhedron alter *			_hoops_HPGPR = (Polyhedron alter *)geometry;
							_hoops_HPGPR->bounding = bounding;
						}	break;

						case _hoops_GGCP: {
							Grid const *				grid = (Grid const *)geometry;
							if (grid->count1 == 0 ||
								grid->_hoops_APIAA == _hoops_PPIAA && grid->count2 == 0)
								bounding->flags |= Bounding_TRANSFORM_DEPENDENT;
							bounding->_hoops_CGCIR = 0.1f;
						}	break;

						// _hoops_GRH _hoops_SGI
						case _hoops_SIIP: {
							bounding->flags = Bounding_TRANSFORM_DEPENDENT;
							bounding->_hoops_CGCIR = 0.02f;
						}	break;
						case _hoops_HGCP: {
							bounding->flags = _hoops_IGCIR;
							bounding->_hoops_CGCIR = 0.1f;
						}	break;
						case _hoops_AGCP: {
							bounding->flags = _hoops_HGCIR;
							bounding->_hoops_CGCIR = 0.05f;
						}	break;

						// _hoops_IHGP _hoops_SICIR _hoops_RHCHH (_hoops_PIP: _hoops_GSGS _hoops_RPGS _hoops_HSAR _hoops_GSSR _hoops_AGGPR _hoops_AHCHH)
						case _hoops_ASIP:
						case _hoops_RCIP:
						case _hoops_SGCP:
						case _hoops_CGCP:
						case _hoops_GRCP:
						case _hoops_RRCP: {
							bounding->_hoops_CGCIR = 0.5f;
						}	break;

						case _hoops_PIIP:
						case _hoops_HIIP:
						case _hoops_IIIP:
						case _hoops_CHIP:
						case _hoops_RIIP:
						case _hoops_GIIP: {
							bounding->_hoops_CGCIR = 0.1f;
						}	break;

						case _hoops_PCIP: {
							bounding->_hoops_CGCIR = 0.01f;
						}	break;
						case _hoops_PIRS: {
							bounding->_hoops_CGCIR = 0.1f;
						}	break;
					}

					if (geometry->owner != null) {
						_hoops_CRCP alter *		_hoops_SRCP = geometry->owner;

						if (_hoops_SRCP->_hoops_HSRIR == null)
							_hoops_SRCP->_hoops_HSRIR = bounding;
						else /* _hoops_GSSR _hoops_HASC */
							_hoops_SRCP->_hoops_HSRIR.Merge (bounding);

						HI_Propagate_Bounding (context, _hoops_SRCP, bounding, null);
					}
				}	break;

				default: {} break;
			}
		}
		_hoops_RGGA ((option = option->next) == null);

		_hoops_IRRPR(); // _hoops_PHCHH
	}

	_hoops_IRRPR();

	HI_Free_Option_List (context, option_list);
}


HC_INTERFACE void HC_CDECL HC_Show_Geometry_Pointer (
	Key				key,
	char const *	list,
	void *			address) 
{
	_hoops_PAPPR context("Show_Geometry_Pointer");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Geometry_Pointer () */\n");
	);

	
	void **	_hoops_HHCHH = (void **)address;
	*_hoops_HHCHH = null;

	_hoops_CSPPR();

	Geometry *	geometry = (Geometry*)_hoops_RCSSR (context, key);

	if (geometry == null || BIT (geometry->_hoops_RRHH, _hoops_HGAGR) ||
		geometry->type < _hoops_AHRIR ||
		 geometry->type > _hoops_PHRIR) {
		HE_ERROR (HEC_GEOMETRY, HES_INVALID_KEY,"Provided key does not refer to a valid geometry");
		_hoops_IRRPR();
		return;
	}

	_hoops_HIACR (_hoops_IHCHH, _hoops_SACHH);

	Option_Value *	option_list;
	Option_Value *	option;

	if (HI_Parse_Options (context, list, _hoops_CIACR (_hoops_IHCHH),
		&option_list, _hoops_SIACR)) {

		char	type[80];
						  
		if ((option = option_list) != null) {
			switch (option->type->id) {
				case _hoops_IRCHH: {
					Point **ptr = (Point **) address;

					switch (geometry->type) {
						case _hoops_GSIP:
						case _hoops_SCIP:		
							*ptr = ((Polyhedron *)geometry)->points;	
						break;
			
						case _hoops_IIIP:	
							*ptr = ((Polyline *)geometry)->points;		
						break;
						case _hoops_PIIP:		
							*ptr = ((Line *)geometry)->points;			
							break;

						case _hoops_RCIP:	
							*ptr = ((Polygon *)geometry)->points;		
							break;

						case _hoops_PCIP:		
							*ptr = &((Marker *)geometry)->_hoops_CSAI;	
							break;

						default: {
							
							PUSHNAME(context);
							HC_Show_Key_Type (key, type);
							POPNAME(context);

							HE_ERROR (HEC_GEOMETRY, HES_INVALID_TYPE, 
								Sprintf_S (null, "cannot show 'points' on a '%s'", type));
						}	break;
					}
				}	break;

				case _hoops_CRCHH: {
					int **ptr = (int **) address;

					switch (geometry->type) {
						case _hoops_SCIP: 
							*ptr = ((Shell *)geometry)->face_list; 
							break;
						
						default: {
							PUSHNAME(context);
							HC_Show_Key_Type (key, type);
							POPNAME(context);
							HE_ERROR (HEC_GEOMETRY, HES_INVALID_TYPE, 
								Sprintf_S (null, "cannot show 'face list' on a '%s'", type));
						}	break;
					}
				}	break;

				case _hoops_SRCHH: {
					_hoops_ARPA **ptr = (_hoops_ARPA **) address;

					switch (geometry->type) {
						case _hoops_GSIP:
						case _hoops_SCIP: {
							Polyhedron *phon = (Polyhedron *)geometry;
							if (!ALLBITS (phon->polyhedron_flags, PHF_FACE_NORMALS_VALID|_hoops_ASAHR))
								HI_Assemble_Face_Normals (phon);
							*ptr = phon->local_face_attributes.normals;
						} break;
						
						default: {
							PUSHNAME(context);
							HC_Show_Key_Type (key, type);
							POPNAME(context);
							HE_ERROR (HEC_GEOMETRY, HES_INVALID_TYPE, 
								Sprintf_S (null, "cannot show 'face planes' on a '%s'", type));
						}	break;
					}
				}	break;

				case _hoops_GACHH: {
					RGB **ptr = (RGB **) address;

					switch (geometry->type) {
						case _hoops_GSIP:
						case _hoops_SCIP: {
							Polyhedron *phon = (Polyhedron *)geometry;
							*ptr = phon->local_face_attributes.colors;
						} break;
						
						default: {
							PUSHNAME(context);
							HC_Show_Key_Type (key, type);
							POPNAME(context);
							HE_ERROR (HEC_GEOMETRY, HES_INVALID_TYPE,
									  Sprintf_S (null, "cannot show 'face colors' on a '%s'", type));
						}	break;
					}
				}	break;

				case _hoops_RACHH: {
					_hoops_GIIPR **ptr = (_hoops_GIIPR **) address;

					switch (geometry->type) {
						case _hoops_GSIP:
						case _hoops_SCIP: {
							Polyhedron *phon = (Polyhedron *)geometry;
							*ptr = phon->local_face_attributes._hoops_CHHPR();
						} break;
						
						default: {
							PUSHNAME(context);
							HC_Show_Key_Type (key, type);
							POPNAME(context);
							HE_ERROR (HEC_GEOMETRY, HES_INVALID_TYPE,
								Sprintf_S (null, "cannot show 'face flags' on a '%s'", type));
						}	break;
					}
				}	break;

				case _hoops_CACHH:
				case _hoops_AACHH:
				case _hoops_PACHH:
				case _hoops_HACHH:
				case _hoops_IACHH: {
					void **ptr = (void **) address;

					switch (geometry->type) {

						case _hoops_HGCP: {
							
							Image *image = (Image *)geometry;
							Image_Format _hoops_CHCHH = _hoops_CAHPA;

							switch (option->type->id) {
								case _hoops_CACHH:
									_hoops_CHCHH = _hoops_AHGH;
									break;
								case _hoops_AACHH:
									_hoops_CHCHH = _hoops_HHGH;
									break;
								case _hoops_PACHH:
									_hoops_CHCHH = Image_RGBA32;
									break;
								case _hoops_HACHH:
									_hoops_CHCHH = Image_MAPPED_8;
									break;
								case _hoops_IACHH: 
									_hoops_CHCHH = Image_MAPPED_16;
									break;
							}

							*ptr = 0;

							if (_hoops_CHCHH != image->format) {
								if (image->format == _hoops_HHGH && 
									_hoops_CHCHH == Image_RGBA32)
									HE_WARNING (HEC_GEOMETRY, HES_INVALID_TYPE,
										"Requested raster type doesn't match internal "
										"raster type, please show using 'rgb rasters', not 'rgba rasters'");
								else{
									HE_WARNING (HEC_GEOMETRY, HES_INVALID_TYPE, Sprintf_DD(null,
										"Requested raster type %d doesn't match internal raster type %d",
										_hoops_CHCHH, image->format));
								}
							}
							else
								*ptr = (void *)(image->_hoops_PHGH);

						} break;
						
						default: {
							PUSHNAME(context);
							HC_Show_Key_Type (key, type);
							POPNAME(context);
							HE_ERROR (HEC_GEOMETRY, HES_INVALID_TYPE,
								Sprintf_S (null, "cannot show 'rasters' on a '%s'", type));
						}	break;
					}
				}	break;

				default: {
					HE_ERROR (HEC_GEOMETRY, HES_INVALID_TYPE, "invalid type specified");
				}
			}
		}
		HI_Free_Option_List (context, option_list);
	}
	_hoops_IRRPR();
#endif
}


