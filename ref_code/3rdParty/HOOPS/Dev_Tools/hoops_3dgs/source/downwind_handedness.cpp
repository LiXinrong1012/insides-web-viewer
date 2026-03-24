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
 * $Id: obf_tmp.txt 1.54 2010-09-22 02:29:38 trask Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"


GLOBAL_FUNCTION void HD_Downwind_Handedness (
	Net_Rendition alter &		nr,
	Attribute const *			_hoops_ASGPR) {
	_hoops_ARAIR const *			_hoops_HRACA = (_hoops_ARAIR const *)_hoops_ASGPR;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	if (_hoops_HRACA->which == _hoops_RAACA &&
		BIT (_hoops_IHCR->flags, _hoops_PGCH)) {}
	else if (_hoops_HRACA->which == _hoops_GIACA &&
			 !BIT (_hoops_IHCR->flags, _hoops_PGCH)) {}
	else {
		_hoops_HRPA					tmp;
		_hoops_HHCR			_hoops_GGCC;

		HD_Undo_Screen (nr, &tmp);
		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();
		_hoops_GGCC->flags ^= _hoops_PGCH;	/* _hoops_IHAA _hoops_RH _hoops_IGRH */
		HD_Redo_Screen (nr, &tmp);

		if (BIT (_hoops_GGCC->flags, _hoops_HHGGA))
			HD_Set_DC_Cutting_Planes (nr);

		if (_hoops_GGCC->_hoops_HCHH != null) {
			/* _hoops_IHAA _hoops_AHCA _hoops_RHCH _hoops_HRGR _hoops_CPHR _hoops_GAR	 _hoops_SISR = _hoops_GHHPA + (_hoops_GHHPA-_hoops_SISR), _hoops_PAR	_hoops_SISR = _hoops_PCIHP-_hoops_SISR, _hoops_CAS	_hoops_PCIHP = 2*_hoops_GHHPA */
			float							pivot = (float)(nr->_hoops_SAIR->_hoops_PHRA.left +
															nr->_hoops_SAIR->_hoops_PHRA.right);
			_hoops_HSRGA alter &		_hoops_HCIHP = _hoops_GGCC->_hoops_HCHH.Modify();
			_hoops_ASHH alter *		region;

			region = (_hoops_ASHH alter *)_hoops_HCIHP->_hoops_PSHH;

			do if (BIT (region->flags, _hoops_SPAGA)) {
				DC_Point *					point = region->points;
				int							count = region->count;

				while (count--) {
					point->x = pivot - point->x;
					++point;
				}
				// _hoops_SPPR _hoops_HAR _hoops_RIRRR _hoops_CGPR _hoops_ICIHP._hoops_CCIHP() _hoops_PCIAR _hoops_RH _hoops_ISPH _hoops_HIGR

				Swap (region->_hoops_RCHS.left, region->_hoops_RCHS.right);
				region->_hoops_RCHS.left = pivot - region->_hoops_RCHS.left;
				region->_hoops_RCHS.right = pivot - region->_hoops_RCHS.right;
			} while ((region = region->next) != null);

			// _hoops_CIHH _hoops_ARH _hoops_HAR _hoops_RIRRR _hoops_RHSP _hoops_ICIHP._hoops_CCIHP()
		}
	}
}
