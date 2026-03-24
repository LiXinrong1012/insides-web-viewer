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
 * $Id: obf_tmp.txt 1.94 2010-10-20 20:26:18 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "please.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local bool _hoops_RPRHH (
	_hoops_APRHH const *_hoops_PPRHH,
	char const						*p2) {
	char const						*p1 = _hoops_PPRHH->item.text;

	do if (*p1++ != *p2++) return false;
	_hoops_RGGA (*p2 == '\0');

	return true;
}


GLOBAL_FUNCTION bool HD_Gather_Device_Info (
	Display_Context const *			dc,
	_hoops_APRHH alter *		_hoops_PPRHH) {
	local		char const			_hoops_HPRHH[] = "yes";
	local		char const			no[] = "no";
	local		char const			_hoops_IPRHH = '\0';
	char const *					_hoops_CPRHH = &_hoops_IPRHH;
	char							buf[MAX_ERRMSG];
	float							x, y;
	float							_hoops_CSIH;

	switch (_hoops_PPRHH->item.length) {
		case 4: {
			if (_hoops_RPRHH (_hoops_PPRHH, "size")) {
				_hoops_CPRHH = !BIT(dc->flags, _hoops_SAISR) ? null :
						 _hoops_SPRHH (dc->_hoops_RIGC, buf, "%.1f,%.1f", dc->current.size.x, dc->current.size.y);
			}
		}	break;

		case 5: {
			if (_hoops_RPRHH (_hoops_PPRHH, "alive"))
				_hoops_CPRHH = _hoops_HPRHH;
		}	break;

		case 6: {
			if (_hoops_RPRHH (_hoops_PPRHH, "planes")) {
				if (!BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH) ||
					!_hoops_AGGR (dc->_hoops_PGCC._hoops_ICHSR,
					"frame buffer"))
					_hoops_CPRHH = null;
				else {
					if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR)
						_hoops_CPRHH = "24";	/*** _hoops_GHRHH! ***/
					else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
						int		planes = 1;

						_hoops_RGGA ((1<<planes) >= dc->_hoops_PGCC._hoops_AAPSR)
							++planes;
						_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", planes);
					}
					else /* _hoops_AIHHP */
						_hoops_CPRHH = "1";  /*** _hoops_GHRHH! ***/
				}
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "colors")) {
				if (!BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH)) 
					_hoops_CPRHH = null;
				else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
					if (_hoops_AGGR (dc->_hoops_PGCC._hoops_ICHSR,
						"frame buffer"))
						_hoops_CPRHH = "16777216";  /*** _hoops_GHRHH! ***/
					else
						_hoops_CPRHH = null;
				}
				else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_RIIHP)
					_hoops_CPRHH = "2";		/* !! */
				else /* _hoops_RPP (_hoops_CSPH->_hoops_CPHSR._hoops_AHRHH == _hoops_AIIHP) */
					_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d",
					dc->_hoops_PGCC._hoops_AAPSR);
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "pixels"))
				_hoops_CPRHH = !BIT(dc->flags, _hoops_SAISR) ? null :
				_hoops_PHRHH (dc->_hoops_RIGC, buf, "%d,%d",
					dc->current._hoops_PRPSR.x,
					dc->current._hoops_PRPSR.y);
			else if (_hoops_RPRHH (_hoops_PPRHH, "exists"))
				_hoops_CPRHH = _hoops_HPRHH;
			else if (_hoops_RPRHH (_hoops_PPRHH, "stereo"))
				_hoops_CPRHH = BIT(dc->_hoops_PGCC.flags, _hoops_IPPHP) ? _hoops_HPRHH : no;
		}	break;

		case 7: {
			if (_hoops_RPRHH (_hoops_PPRHH, "display"))
				_hoops_CPRHH = BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH) ? _hoops_HPRHH : no;
			else if (_hoops_RPRHH (_hoops_PPRHH, "locater"))
				_hoops_CPRHH = BIT(dc->_hoops_PGCC.flags, _hoops_RSHSR) ? _hoops_HPRHH : no;
			else if (_hoops_RPRHH (_hoops_PPRHH, "started"))
				_hoops_CPRHH = _hoops_HPRHH;
			else if (_hoops_RPRHH (_hoops_PPRHH, "dc dots"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_CCCA));
			else if (_hoops_RPRHH (_hoops_PPRHH, "3d dots"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_SCCA));
			else if (_hoops_RPRHH (_hoops_PPRHH, "rasters"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(rasters));
		}	break;

		case 8: {
			if (_hoops_RPRHH (_hoops_PPRHH, "keyboard"))
				_hoops_CPRHH = BIT(dc->_hoops_PGCC.flags, _hoops_PSHSR) ? _hoops_HPRHH : no;
			else if (_hoops_RPRHH (_hoops_PPRHH, "raw free")) 
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_CCRGH));
			else if (_hoops_RPRHH (_hoops_PPRHH, "max size")) {
				if (!BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH) && !BIT(dc->_hoops_PGCC.flags, _hoops_RSHSR))
					_hoops_CPRHH = null;
				else {
					if (!BIT(dc->flags, _hoops_SAISR) ||
						dc->options._hoops_SPHSR.x < 0.0f) {
							x = dc->_hoops_PGCC.size.x;
							y = dc->_hoops_PGCC.size.y;
					}
					else {
						x = dc->options._hoops_SPHSR.x;
						y = dc->options._hoops_SPHSR.y;
					}
					_hoops_CPRHH = _hoops_SPRHH (dc->_hoops_RIGC, buf, "%.1f,%.1f", x, y);
				}
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "dc lines"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_HCCA));
			else if (_hoops_RPRHH (_hoops_PPRHH, "3d lines"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_ICCA));
			else if (_hoops_RPRHH (_hoops_PPRHH, "segments"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_SISAA));
		}	break;

		case 9: {
			if (_hoops_RPRHH (_hoops_PPRHH, "analytics"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_HHRGH));
			else if (_hoops_RPRHH (_hoops_PPRHH, "tristrips"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(tristrips));
			else if (_hoops_RPRHH (_hoops_PPRHH, "occlusion")) {
				if (dc->_hoops_ACPGR->_hoops_GRSSP != null) 
					_hoops_CPRHH = _hoops_HPRHH;
				else
					_hoops_CPRHH = no;
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "dl strips"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_GGCAR));

		}	break;

		case 10: {
			if (_hoops_RPRHH (_hoops_PPRHH, "max colors")) {
				if (!BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH)) 
					_hoops_CPRHH = null;
				else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
					if (_hoops_AGGR (dc->_hoops_PGCC._hoops_ICHSR, "frame buffer"))
						_hoops_CPRHH = "16777216";  /*** _hoops_GHRHH! ***/
					else
						_hoops_CPRHH = null;
				}
				else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_RIIHP)
					_hoops_CPRHH = "2";		/* !! */
				else /* _hoops_RPP (_hoops_CSPH->_hoops_CPHSR._hoops_AHRHH == _hoops_AIIHP) */
					_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d",
					dc->_hoops_PGCC._hoops_HHPGH);
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "max pixels"))
				_hoops_CPRHH = (!BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH) && !BIT(dc->_hoops_PGCC.flags, _hoops_RSHSR))
						? null
						: _hoops_PHRHH (dc->_hoops_RIGC, buf, "%d,%d", dc->_hoops_PGCC._hoops_PRPSR.x,
													dc->_hoops_PGCC._hoops_PRPSR.y);
			else if (_hoops_RPRHH (_hoops_PPRHH, "resolution")) {
				if (!BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH) && !BIT(dc->_hoops_PGCC.flags, _hoops_RSHSR))
					_hoops_CPRHH = null;
				else {
					if (!BIT(dc->flags, _hoops_SAISR) ||
						dc->options._hoops_SPHSR.x < 0.0f) {
							x = dc->_hoops_PGCC._hoops_PRPSR.x/dc->_hoops_PGCC.size.x;
							y = dc->_hoops_PGCC._hoops_PRPSR.y/dc->_hoops_PGCC.size.y;
					}
					else {
						x = dc->_hoops_PGCC._hoops_PRPSR.x/
							dc->options._hoops_SPHSR.x;
						y = dc->_hoops_PGCC._hoops_PRPSR.y/
							dc->options._hoops_SPHSR.y;
					}
					_hoops_CPRHH = _hoops_SPRHH (dc->_hoops_RIGC, buf, "%.2f,%.2f", x, y);
				}
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "anti-alias") ||
				_hoops_RPRHH (_hoops_PPRHH, "anti alias"))
				_hoops_CPRHH = BIT(dc->_hoops_PGCC.flags, _hoops_CPPGH) ? _hoops_HPRHH : no;
			else if (_hoops_RPRHH (_hoops_PPRHH, "ndl strips"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_GRHAR));
			else if (_hoops_RPRHH (_hoops_PPRHH, "dl deletes"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_SGAGR));
			
		}	break;

		case 11: {
			if (_hoops_RPRHH (_hoops_PPRHH, "update time"))
				_hoops_CPRHH = _hoops_HHRHH (dc->_hoops_RIGC, buf, "%F", _hoops_RCCA(_hoops_IPRGH));
			if (_hoops_RPRHH (_hoops_PPRHH, "finish time"))
				_hoops_CPRHH = _hoops_HHRHH (dc->_hoops_RIGC, buf, "%F", _hoops_RCCA(_hoops_CPRGH));
			else if (_hoops_RPRHH (_hoops_PPRHH, "static time"))
				_hoops_CPRHH = _hoops_HHRHH (dc->_hoops_RIGC, buf, "%F", _hoops_RCCA(_hoops_SPRGH));
			else if (_hoops_RPRHH (_hoops_PPRHH, "shadow time"))
				_hoops_CPRHH = _hoops_HHRHH (dc->_hoops_RIGC, buf, "%F", _hoops_RCCA(_hoops_GHRGH));
			else if (_hoops_RPRHH (_hoops_PPRHH, "driver type"))
				_hoops_CPRHH = dc->_hoops_PGCC.driver_type;
			else if (_hoops_RPRHH (_hoops_PPRHH, "dc polygons"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_PHRGH));
			else if (_hoops_RPRHH (_hoops_PPRHH, "3d polygons"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_GRCS));
			else if (_hoops_RPRHH (_hoops_PPRHH, "polyhedrons"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_AIRGH));
		}	break;

		case 12: {
			if (_hoops_RPRHH (_hoops_PPRHH, "display type"))
				_hoops_CPRHH = !BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH) ? null : dc->_hoops_PGCC._hoops_ICHSR;
			else if (_hoops_RPRHH (_hoops_PPRHH, "locater type"))
				_hoops_CPRHH = !BIT(dc->_hoops_PGCC.flags, _hoops_RSHSR) ? null : dc->_hoops_PGCC._hoops_RCPGH;
			else if (_hoops_RPRHH (_hoops_PPRHH, "dc triangles"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_ACCA));
			else if (_hoops_RPRHH (_hoops_PPRHH, "3d triangles"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_PCCA));
			else if (_hoops_RPRHH (_hoops_PPRHH, "video memory")) {
				size_t _hoops_IHRHH =  HOOPS_WORLD->vram_size / (1<<20);
				_hoops_CPRHH = _hoops_CHRHH (dc->_hoops_RIGC, buf, "%P MB", _hoops_IHRHH);
			}
		}	break;

		case 13: {		
			if (_hoops_RPRHH (_hoops_PPRHH, "driver config")) {
				if (dc->_hoops_PGCC._hoops_PRARR != null)
					_hoops_CPRHH = dc->_hoops_PGCC._hoops_PRARR->_hoops_AAIPP.text;
				else
					_hoops_CPRHH = _hoops_IPRHH;
			} 
			else if (_hoops_RPRHH (_hoops_PPRHH, "assemble time"))
				_hoops_CPRHH = _hoops_HHRHH (dc->_hoops_RIGC, buf, "%F", _hoops_RCCA(_hoops_RHRGH));
			else if (_hoops_RPRHH (_hoops_PPRHH, "double buffer") ||
					 _hoops_RPRHH (_hoops_PPRHH, "double-buffer")) {
				switch (dc->_hoops_PGCC._hoops_CHHSR) {
					case _hoops_SHHSR:	_hoops_CPRHH = "none";		break;
					case _hoops_ACPGA:	_hoops_CPRHH = "copy";		break;
					case _hoops_RCPGA:	_hoops_CPRHH = "swap";		break;
				}
			}
		}	break;

		case 14: {
			if (_hoops_RPRHH (_hoops_PPRHH, "dl 3d vertices"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_RPAS));
			else if (_hoops_RPRHH (_hoops_PPRHH, "phong lighting"))
				_hoops_CPRHH = BIT(dc->_hoops_PGCC.flags, _hoops_RPPGH) ? _hoops_HPRHH : no;
			else if (_hoops_RPRHH (_hoops_PPRHH, "z buffer depth")) {
				if (!BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH))
					_hoops_CPRHH = null;
				else
					_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", dc->_hoops_PGCC._hoops_HASHP);
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "driver version")) {
				_hoops_CPRHH = null;	   /* _hoops_HPCAR _hoops_IRS _hoops_ARPC _hoops_CCGR _hoops_SCH _hoops_IIAH */
				if (BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH)) {
					char const		*version;
					int				_hoops_SHRHH;

					version = dc->_hoops_PGCC._hoops_SCHSR;
					_hoops_SHRHH = _hoops_SSGR (version);

					if (_hoops_GPPSA (version, 11, "$Revision: ") &&
						_hoops_AGGR (&version[_hoops_SHRHH-2], " $")) {
						_hoops_CPRHH = _hoops_GIRHH (dc->_hoops_RIGC, buf, "%s", &version[11]);
						buf[_hoops_SHRHH-13] = '\0';
					}
					else {
						_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, 
							_hoops_GIRHH (dc->_hoops_RIGC, null,
								"Unrecognised format in driver version '%s'",
								version));
					}
				}
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "resumed update"))
				_hoops_CPRHH = _hoops_RCCA(_hoops_ASRGH) ? _hoops_HPRHH : no;
		}	break;

		case 15: {
			if (_hoops_RPRHH (_hoops_PPRHH, "locater buttons")) {
				_hoops_CPRHH = !BIT(dc->_hoops_PGCC.flags, _hoops_RSHSR) ? null :
						 _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", dc->_hoops_PGCC._hoops_ASHSR);
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "hardware lights")) {
				if (!BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH))
					_hoops_CPRHH = null;
				else
					_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", dc->_hoops_PGCC._hoops_HGCC);
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "gouraud shading"))
				_hoops_CPRHH = BIT(dc->_hoops_PGCC.flags, _hoops_SGICP) ? _hoops_HPRHH : no;
			else if (_hoops_RPRHH (_hoops_PPRHH, "dl 3d triangles"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_AGCAR));
		}	break;

		case 16: {
			if (_hoops_RPRHH (_hoops_PPRHH, "max texture size"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", dc->_hoops_PGCC._hoops_PCPGH);
			else if (_hoops_RPRHH (_hoops_PPRHH, "memory oversized")) 
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_ICRGH));
			else if (_hoops_RPRHH (_hoops_PPRHH, "windowing system"))
				_hoops_CPRHH = BIT(dc->_hoops_PGCC.flags, _hoops_HSHSR) ? _hoops_HPRHH : no;
			else if (_hoops_RPRHH (_hoops_PPRHH, "gouraud lighting"))
				_hoops_CPRHH = BIT(dc->_hoops_PGCC.flags, _hoops_GPPGH) ? _hoops_HPRHH : no;
			else if (_hoops_RPRHH (_hoops_PPRHH, "driver config id"))
				_hoops_CPRHH = dc->_hoops_PGCC._hoops_GSPGH.text;

		}	break;

		case 17: {
			if (_hoops_RPRHH (_hoops_PPRHH, "current window id"))
				_hoops_CPRHH = !BIT(dc->_hoops_PGCC.flags, _hoops_HSHSR) ? null :
						 _hoops_RIRHH (dc->_hoops_RIGC, buf, "%D", dc->current._hoops_RAPGH);
			else if (_hoops_RPRHH (_hoops_PPRHH, "event interrupted"))
				_hoops_CPRHH = _hoops_RCCA(_hoops_RSRGH) ? _hoops_HPRHH : no;
			else if (_hoops_RPRHH (_hoops_PPRHH, "occlusion queries"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_IHRGH));
			else if (_hoops_RPRHH (_hoops_PPRHH, "video memory used")) {
				size_t used = (HOOPS_WORLD->display_list_vram_usage + HOOPS_WORLD->_hoops_SARH) / (1<<20);
				_hoops_CPRHH = _hoops_CHRHH (dc->_hoops_RIGC, buf, "%P MB", used);
			}
		}	break;

		case 18: {
			if (_hoops_RPRHH (_hoops_PPRHH, "quick moves method")) {
				/* _hoops_HRS _hoops_RH _hoops_SPAHR _hoops_SGS _hoops_CSAP _hoops_IGI _hoops_GGR _hoops_RH _hoops_PGHC _hoops_PAAP (_hoops_PGAP 
				 * _hoops_PAH _hoops_AGRP _hoops_GPGA _hoops_GPP _hoops_RH "_hoops_AIRHH _hoops_CIHCA" _hoops_RHPP _hoops_HCSP) */
				switch (dc->_hoops_SHPGR) {
					case QMoves_NONE:			_hoops_CPRHH = "none";		break;
					case QMoves_XOR:			_hoops_CPRHH = "xor";			break;
					case QMoves_Real_Overlay:	_hoops_CPRHH = "overlay";		break;
					case QMoves_Accumulation:	_hoops_CPRHH = "overlay";		break;
					case QMoves_Spriting:		_hoops_CPRHH = "spriting";	break;
				}
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "pixel aspect ratio"))
				_hoops_CPRHH = !BIT(dc->flags, _hoops_SAISR) ? null :
						 _hoops_HHRHH (dc->_hoops_RIGC, buf, "%.3f", dc->current._hoops_AGRS);
			else if (_hoops_RPRHH (_hoops_PPRHH, "video memory limit")) {
				size_t _hoops_IHRHH = HOOPS_WORLD->_hoops_PHARR / (1<<20);
				_hoops_CPRHH = _hoops_CHRHH (dc->_hoops_RIGC, buf, "%P MB", _hoops_IHRHH);
			}

		}	break;

		case 19: {
			if (_hoops_RPRHH (_hoops_PPRHH, "window aspect ratio")) {
				if (!BIT(dc->flags, _hoops_SAISR))
					_hoops_CPRHH = null;
				else {
					_hoops_CSIH = dc->current.size.x/dc->current.size.y;
					_hoops_CPRHH = _hoops_HHRHH (dc->_hoops_RIGC, buf, "%.3f", _hoops_CSIH);
				}
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "current window id 2"))
				_hoops_CPRHH = !BIT(dc->_hoops_PGCC.flags, _hoops_HSHSR) ? null :
						 _hoops_RIRHH (dc->_hoops_RIGC, buf, "%D", dc->current._hoops_PAPGH);

			else if (_hoops_RPRHH (_hoops_PPRHH, "current colormap id"))
				_hoops_CPRHH = !BIT(dc->_hoops_PGCC.flags, _hoops_HSHSR) ? null :
						 _hoops_RIRHH (dc->_hoops_RIGC, buf, "%D", dc->current._hoops_HAPGH);
		}	break;

		case 20: {
			if (_hoops_RPRHH (_hoops_PPRHH, "depth peeling layers"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", dc->_hoops_PGCC._hoops_AHAGH);
		}	break;
			
		case 21: {
			if (_hoops_RPRHH (_hoops_PPRHH, "driver config version"))
				_hoops_CPRHH = dc->_hoops_PGCC._hoops_RSPGH.text;
			else if (_hoops_RPRHH (_hoops_PPRHH, "hardware acceleration"))
				_hoops_CPRHH = BIT(dc->_hoops_PGCC.flags, _hoops_PHPGH) ? _hoops_HPRHH : no;
		}	break;

		case 22: {
			if (_hoops_RPRHH (_hoops_PPRHH, "segments extent culled"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_CHRGH));
			else if (_hoops_RPRHH (_hoops_PPRHH, "segments vector culled"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_GIRGH));
		}	break;

		case 23: {
			if (_hoops_RPRHH (_hoops_PPRHH, "hardware cutting planes")) {
				if (!BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH))
					_hoops_CPRHH = null;
				else
					_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", dc->_hoops_PGCC._hoops_ACPGH);
			}
			else if (_hoops_RPRHH (_hoops_PPRHH, "segments frustum culled"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_SHRGH));
		}	break;

		case 25: {
			if (_hoops_RPRHH (_hoops_PPRHH, "segments occlusion culled"))
				_hoops_CPRHH = _hoops_RHRHH (dc->_hoops_RIGC, buf, "%d", _hoops_RCCA(_hoops_RIRGH));
		}	break;
	}

	if (_hoops_CPRHH == &_hoops_IPRHH) {
		if (_hoops_RPRHH (_hoops_PPRHH, "anti-aliasing") ||
			_hoops_RPRHH (_hoops_PPRHH, "anti aliasing") ||
			_hoops_RPRHH (_hoops_PPRHH, "antialiasing") ||
			_hoops_RPRHH (_hoops_PPRHH, "anti-alias") ||
			_hoops_RPRHH (_hoops_PPRHH, "anti alias") ||
			_hoops_RPRHH (_hoops_PPRHH, "antialias"))
			_hoops_CPRHH = BIT(dc->_hoops_PGCC.flags, _hoops_CPPGH) ? _hoops_HPRHH : no;
	}

	if (_hoops_CPRHH == &_hoops_IPRHH) {
		HE_ERROR (HEC_SYSTEM, HES_INVALID_INPUT,
				_hoops_PIRHH (
					dc->_hoops_RIGC, null,
					"'%n' is not a recognized type of device information",
					&_hoops_PPRHH->item));
		return false;
	}
	else {

		if (_hoops_CPRHH == null) {
			_hoops_PPRHH->data.length = 0;
			_hoops_PPRHH->data.text = null;
		}
		else
			HI_Copy_Chars_To_Name (_hoops_CPRHH, &_hoops_PPRHH->data);

		return true;
	}
}

