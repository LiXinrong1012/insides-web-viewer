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
 * $Id: obf_tmp.txt 1.110 2010-04-06 01:51:25 covey Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "hidden.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "database.h" /* _hoops_RGAR _hoops_IH _hoops_HCGR->_hoops_SGSS */
#include "hpserror.h"
#include "phedron.h"
#include "phdraw.h"


GLOBAL_FUNCTION void HD_Free_Hidden_Tristrip (
	Hidden_Tristrip alter *		_hoops_ACSIP)
{
	Tristrip alter *_hoops_IPIAR = (Tristrip alter *)_hoops_ACSIP->tristrips;

	if (_hoops_ACSIP->_hoops_AGHAR)
		FREE_ARRAY_ALIGNED (_hoops_ACSIP->_hoops_AGHAR, _hoops_ACSIP->tristrips->face_count, int, 16);
	if (_hoops_ACSIP->_hoops_SPGCP)
		FREE_ARRAY (_hoops_ACSIP->_hoops_SPGCP, _hoops_ACSIP->_hoops_APPH, float);
	if (_hoops_ACSIP->_hoops_CPGCP)
		FREE_ARRAY (_hoops_ACSIP->_hoops_CPGCP, _hoops_ACSIP->_hoops_APPH, _hoops_GPGCP);
	if (_hoops_ACSIP->_hoops_GHGCP)
		FREE_ARRAY (_hoops_ACSIP->_hoops_GHGCP, 2*_hoops_ACSIP->_hoops_AGH, RGBAS32);

	if (_hoops_ACSIP->_hoops_GHPCP != null)
		FREE_ARRAY (_hoops_ACSIP->_hoops_GHPCP, _hoops_IPIAR->point_count, DC_Point);
	if (_hoops_ACSIP->_hoops_AARHH != null)
		FREE_ARRAY (_hoops_ACSIP->_hoops_AARHH, _hoops_IPIAR->point_count, _hoops_ARPA);
	if (_hoops_ACSIP->_hoops_RIACP != null)
		FREE_ARRAY (_hoops_ACSIP->_hoops_RIACP, _hoops_IPIAR->face_count, _hoops_ARPA);

	_hoops_ACSIP->_hoops_APHGA.release();
	_hoops_ACSIP->_hoops_PARHH.release();

	if (_hoops_ISAI (_hoops_IPIAR) == 0)
		HI_Free_Tristrip (_hoops_IPIAR);
	FREE (_hoops_ACSIP, Hidden_Tristrip);
}

GLOBAL_FUNCTION void HD_Free_Hidden_Polymarker (
	_hoops_PGRCP alter * _hoops_HGRCP)
{
	if (_hoops_HGRCP->_hoops_GHGCP)
		FREE_ARRAY (_hoops_HGRCP->_hoops_GHGCP, _hoops_HGRCP->_hoops_GIGPR->point_count, RGBAS32);
	if (_hoops_HGRCP->_hoops_GHPCP != null)
		FREE_ARRAY (_hoops_HGRCP->_hoops_GHPCP, _hoops_HGRCP->_hoops_GIGPR->point_count, DC_Point);
	if (_hoops_HGRCP->_hoops_AARHH != null)
		FREE_ARRAY (_hoops_HGRCP->_hoops_AARHH, _hoops_HGRCP->_hoops_GIGPR->point_count, _hoops_ARPA);
	if (_hoops_HGRCP->_hoops_RIACP != null)
		FREE_ARRAY (_hoops_HGRCP->_hoops_RIACP, _hoops_HGRCP->_hoops_GIGPR->point_count, _hoops_ARPA);

	_hoops_HGRCP->_hoops_APHGA.release();
	_hoops_HGRCP->_hoops_PARHH.release();
	if (_hoops_ISAI (_hoops_HGRCP->_hoops_GIGPR) == 0)
		HI_Free_Polymarker ((Polymarker alter *)_hoops_HGRCP->_hoops_GIGPR); 
	FREE (_hoops_HGRCP, _hoops_PGRCP);
}

GLOBAL_FUNCTION void HD_Free_Hidden_Payload (
	Display_Context const *		dc,
	_hoops_SRHSA alter *		_hoops_ASHSA) {

	if (_hoops_ISAI(_hoops_ASHSA) == 0) {
		if (_hoops_ASHSA->next)
			HD_Free_Hidden_Payload(dc, _hoops_ASHSA->next);

		_hoops_ASHSA->_hoops_APHGA.release();

		if (_hoops_ASHSA->_hoops_CHCSA) {
			_hoops_HARHH* _hoops_CHCSA = _hoops_ASHSA->_hoops_CHCSA;

			if (_hoops_ISAI(_hoops_CHCSA) == 0)
				FREE_ARRAY(_hoops_CHCSA, _hoops_CHCSA->size, unsigned char);

		}
		else {
			/*
			 * _hoops_SRS, _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_GII _hoops_PPSR _hoops_HIGR
			 */
			if (_hoops_IARHH (_hoops_ASHSA->type) || _hoops_ASHSA->type == _hoops_RCHSA)
				FREE_ARRAY (_hoops_ASHSA->points, _hoops_ASHSA->count, DC_Point);

			/*
			 * _hoops_HA _hoops_CASI _hoops_GH _hoops_RH _hoops_CARHH _hoops_PPR _hoops_HCPA
			 */
			switch (_hoops_ASHSA->type) {
			  case _hoops_HCHSA: {
				  _hoops_ICHSA alter	*info;

				  if ((info = (_hoops_ICHSA alter *)_hoops_ASHSA->_hoops_GPHSA) != null) {
					  FREE_ARRAY (info->_hoops_CCHSA, _hoops_ASHSA->count, bool);
					  FREE (info, _hoops_ICHSA);
				  }
			  }	  break;

			  case _hoops_IAHSA: {
				  _hoops_CAHSA alter		*info;

				  if ((info = (_hoops_CAHSA alter *)_hoops_ASHSA->_hoops_GPHSA) != null) {
					  if (info->_hoops_RAGR) {
						  if (BIT (info->_hoops_RAGR, _hoops_PPHSA))
							  FREE_ARRAY (info->_hoops_HPHSA, 1, RGBAS32);
					  }
					  FREE (info, _hoops_CAHSA);
				  }
			  }	  break;

			  case _hoops_IPHSA: {
				  _hoops_CAHSA alter		*info;

				  if ((info = (_hoops_CAHSA alter *)_hoops_ASHSA->_hoops_GPHSA) != null) {
					  if (info->_hoops_RAGR) {
						  if (BIT (info->_hoops_RAGR, _hoops_PPHSA))
							  FREE_ARRAY (info->_hoops_HPHSA, 1, RGBAS32);
						  else if (BIT (info->_hoops_RAGR, _hoops_CPHSA))
							  FREE_ARRAY (info->_hoops_HPHSA, 3, RGBAS32);
						  else if (BIT (info->_hoops_RAGR, _hoops_SPHSA))
							  FREE_ARRAY (info->rgba_colors, 3, RGBA);
						  if (BIT (info->_hoops_RAGR, _hoops_GHHSA))
							  FREE_ARRAY (info->planes, 3, _hoops_ARPA);
						  if (BIT (info->_hoops_RAGR, _hoops_RHHSA)) {
							  FREE_ARRAY (info->params, info->param_width*3, _hoops_RSSH);
						  }
					  }
					  FREE (info, _hoops_CAHSA);
				  }
			  }	  break;

			  case _hoops_AHHSA: {
				  _hoops_CAHSA alter		*info;

				  if ((info = (_hoops_CAHSA alter *)_hoops_ASHSA->_hoops_GPHSA) != null) {
					  if (info->_hoops_RAGR) {
						  if (BIT (info->_hoops_RAGR, _hoops_PPHSA))
							  FREE_ARRAY (info->_hoops_HPHSA, 1, RGBAS32);
						  else if (BIT (info->_hoops_RAGR, _hoops_CPHSA))
							  FREE_ARRAY (info->_hoops_HPHSA, 2, RGBAS32);
						  else if (BIT (info->_hoops_RAGR, _hoops_SPHSA))
							  FREE_ARRAY (info->rgba_colors, 2, RGBA);
						  if (BIT (info->_hoops_RAGR, _hoops_GHHSA))
							  FREE_ARRAY (info->planes, 2, _hoops_ARPA);
						  if (BIT (info->_hoops_RAGR, _hoops_RHHSA)) {
							  FREE_ARRAY (info->params, info->param_width*2, _hoops_RSSH);
						  }
					  }
					  FREE (info, _hoops_CAHSA);
				  }
			  }	  break;

			  case _hoops_PHHSA: {
				  _hoops_HHHSA alter				*info;

				  info = &_hoops_ASHSA->_hoops_GPHSA->_hoops_CHHSA;
				  if (--info->_hoops_HIHI == 0) {
					  if (info->db_image)
						  _hoops_HPRH (info->db_image);
					  else {
						  int								height;

						  height = (int)(_hoops_ASHSA->ymax - _hoops_ASHSA->ymin) + 1;
						  FREE_ARRAY (*info->rasters, info->row_bytes * height, char);
						  FREE_ARRAY (info->rasters, height, void *);
					  }
					  FREE (info, _hoops_HHHSA);
				  }
			  }	  break;

			  case _hoops_SHHSA: {
				  _hoops_GIHSA alter			*info;

				  info = &_hoops_ASHSA->_hoops_GPHSA->_hoops_AIHSA;
				  if (--info->_hoops_HIHI == 0) {
					  HI_Cleanup_Stencil(info->stencil, true);
					  FREE (info, _hoops_GIHSA);
				  }
			  }	  break;

			  case _hoops_PIHSA: {
				  _hoops_HIHSA alter		*info;

				  info = (_hoops_HIHSA alter *)_hoops_ASHSA->_hoops_GPHSA;
				  _hoops_PRPIR (info->_hoops_SIHSA);
				  if (info->text != null) 
					  _hoops_HPRH (info->text);
				  FREE_ARRAY (_hoops_ASHSA->points, 1, DC_Point);
				  FREE (info, _hoops_HIHSA);
			  }	  break;

			  case _hoops_RCHSA:
			  case _hoops_ACHSA:
			  case _hoops_PCHSA: {
			  }	  break;

			  default: {
				  _hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									 "Unknown type of hidden object");
			  }	  break;
			}
			
			FREE (_hoops_ASHSA, _hoops_SRHSA);
		}
		
	}

}

GLOBAL_FUNCTION void HD_Free_Hidden_List (
	Display_Context const *		dc,
	_hoops_CASS alter *				hidden) {
#ifndef DISABLE_SORTING_HSR
	_hoops_CASS alter *				next;
	_hoops_SRHSA alter *		_hoops_ASHSA;

	_hoops_PCCAR {
		int _hoops_SARHH = 0;
		_hoops_ASHSA = hidden->_hoops_ASHSA;
		next = hidden->next;

		if (!BIT(hidden->flags, HF_SLABBED)) { 
			_hoops_SARHH = 1;	
		}

		if (_hoops_ASHSA->type == _hoops_RIGCP) {
			Hidden_Tristrip alter * _hoops_ACSIP = (Hidden_Tristrip alter *)hidden->_hoops_ASHSA->_hoops_GPHSA;
			if (_hoops_ISAI (hidden->_hoops_ASHSA) == 0) {
				HD_Free_Hidden_Tristrip (_hoops_ACSIP); 
				hidden->_hoops_ASHSA->_hoops_APHGA.release();
				FREE (hidden->_hoops_ASHSA, _hoops_SRHSA);
			}
			FREE (hidden, _hoops_CASS);
			_hoops_SARHH = 0;
		}
		else if (_hoops_ASHSA->type == _hoops_HIGCP){
			_hoops_PGRCP* _hoops_GPRHH = (_hoops_PGRCP*)_hoops_ASHSA->_hoops_GPHSA;
			if (_hoops_ISAI (hidden->_hoops_ASHSA) == 0) {
				HD_Free_Hidden_Polymarker(_hoops_GPRHH);
				hidden->_hoops_ASHSA->_hoops_APHGA.release();
				FREE (hidden->_hoops_ASHSA, _hoops_SRHSA);
			}
			FREE (hidden, _hoops_CASS);
			_hoops_SARHH = 0;
		}
		else 
			HD_Free_Hidden_Payload(dc, _hoops_ASHSA);

		if (_hoops_SARHH)
			FREE(hidden, _hoops_CASS);

		if ((hidden = next) == null) break;
	}
#endif
}
