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
 * $Id: obf_tmp.txt 1.80 2010-06-04 21:37:19 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "patterns.h"
#include "hd_proto.h"
#include "hi_proto.h"

/* _hoops_CGAPR _hoops_SGH _hoops_IH _hoops_SACGP<=3 */
local void _hoops_RCICS(
	DC_Point alter	*pt,
	int alter			*sz,
	float				x, 
	float				y,
	float				z,
	int 				_hoops_ACICS, 
	int 				_hoops_PCICS,
	bool			_hoops_AGSSH) {
	int	alter			_hoops_HCICS=0;

	if (_hoops_ACICS == 3 && _hoops_PCICS == 3) {
		if(_hoops_AGSSH) {
			/* _hoops_PGSA _hoops_APGR _hoops_HII _hoops_SCIA _hoops_ISHP */
			pt[0].x = x - 1;		pt[0].y = y + 3;		pt[0].z = z ;
			pt[1].x = x + 1;		pt[1].y = y + 3;		pt[1].z = z ;
			pt[2].x = x - 2;		pt[2].y = y + 2;		pt[2].z = z ;
			pt[3].x = x + 2;		pt[3].y = y + 2;		pt[3].z = z ;
			pt[4].x = x - 3;		pt[4].y = y + 1;		pt[4].z = z ;
			pt[5].x = x + 3;		pt[5].y = y + 1;		pt[5].z = z ;
			pt[6].x = x - 3;		pt[6].y = y;			pt[6].z = z ;
			pt[7].x = x + 3;		pt[7].y = y;			pt[7].z = z ;
			pt[8].x = x - 3;		pt[8].y = y - 1;		pt[8].z = z ;
			pt[9].x = x + 3;		pt[9].y = y - 1;		pt[9].z = z ;
			pt[10].x = x - 2;		pt[10].y = y - 2;		pt[10].z = z ;
			pt[11].x = x + 2;		pt[11].y = y - 2;		pt[11].z = z ;
			pt[12].x = x - 1;		pt[12].y = y - 3;		pt[12].z = z ;
			pt[13].x = x + 1;		pt[13].y = y - 3;		pt[13].z = z ;

			_hoops_HCICS = -14 ;
		}
		else {
			/* _hoops_SRS _hoops_RCIH */
			pt[0].x = x + _hoops_ACICS	  ; pt[0].y = y           ;	pt[0].z = z ;
			pt[1].x = pt[0].x     ; pt[1].y = pt[0].y + 1 ; pt[1].z = z ;
			pt[2].x = pt[1].x - 1 ;	pt[2].y = pt[1].y + 1 ; pt[2].z = z ;
			pt[3].x = pt[2].x - 1 ; pt[3].y = pt[2].y + 1 ; pt[3].z = z ;
			pt[4].x = pt[3].x - 1 ;	pt[4].y = pt[3].y     ; pt[4].z = z ;

			/* _hoops_GIAP _hoops_RCIH */
			pt[5].x = pt[4].x - 1 ; pt[5].y = pt[4].y     ; pt[5].z = z ;
			pt[6].x = pt[5].x - 1 ;	pt[6].y = pt[5].y - 1 ; pt[6].z = z ;
			pt[7].x = pt[6].x - 1 ; pt[7].y = pt[6].y - 1 ; pt[7].z = z ;
			pt[8].x = pt[7].x     ;	pt[8].y = pt[7].y - 1 ; pt[8].z = z ;

			/* _hoops_HRSSR _hoops_RCIH */
			pt[9].x  = pt[8].x      ; pt[9].y  = pt[8].y  - 1 ; pt[9].z  = z ;
			pt[10].x = pt[9].x  + 1 ; pt[10].y = pt[9].y  - 1 ; pt[10].z = z ;
			pt[11].x = pt[10].x + 1 ; pt[11].y = pt[10].y - 1 ; pt[11].z = z ;
			pt[12].x = pt[11].x + 1 ; pt[12].y = pt[11].y     ; pt[12].z = z ;

			/* _hoops_SCHCR _hoops_RCIH */
			pt[13].x = pt[12].x + 1 ; pt[13].y = pt[12].y     ; pt[13].z = z ;
			pt[14].x = pt[13].x + 1 ; pt[14].y = pt[13].y + 1 ; pt[14].z = z ;
			pt[15].x = pt[14].x + 1 ; pt[15].y = pt[14].y + 1 ; pt[15].z = z ;
			
			pt[16]=pt[0];

			_hoops_HCICS = 17 ;
		}
	} 
	else if (_hoops_ACICS == 3 && _hoops_PCICS == 2) {
		if(_hoops_AGSSH) {
			/* _hoops_PGSA _hoops_APGR _hoops_HII _hoops_SCIA _hoops_ISHP */
			pt[0].x = x - 1;		pt[0].y = y + 2;		pt[0].z = z ;
			pt[1].x = x + 1;		pt[1].y = y + 2;		pt[1].z = z ;
			pt[2].x = x - 2;		pt[2].y = y + 1;		pt[2].z = z ;
			pt[3].x = x + 2;		pt[3].y = y + 1;		pt[3].z = z ;
			pt[4].x = x - 3;		pt[4].y = y;			pt[4].z = z ;
			pt[5].x = x + 3;		pt[5].y = y;			pt[5].z = z ;
			pt[6].x = x - 2;		pt[6].y = y - 1;		pt[6].z = z ;
			pt[7].x = x + 2;		pt[7].y = y - 1;		pt[7].z = z ;
			pt[8].x = x - 1;		pt[8].y = y - 2;		pt[8].z = z ;
			pt[9].x = x + 1;		pt[9].y = y - 2;		pt[9].z = z ;

			_hoops_HCICS = -10 ;
		}
		else {
			/* _hoops_SRS _hoops_RCIH */
			pt[0].x = x + _hoops_ACICS	  ; pt[0].y = y           ;	pt[0].z = z ;
			pt[1].x = pt[0].x - 1 ; pt[1].y = pt[0].y + 1 ; pt[1].z = z ;
			pt[2].x = pt[1].x - 1 ;	pt[2].y = pt[1].y + 1 ; pt[2].z = z ;
			pt[3].x = pt[2].x - 1 ; pt[3].y = pt[2].y     ; pt[3].z = z ;

			/* _hoops_GIAP _hoops_RCIH */
			pt[4].x = pt[3].x - 1 ; pt[4].y = pt[3].y     ; pt[4].z = z ;
			pt[5].x = pt[4].x - 1 ;	pt[5].y = pt[4].y - 1 ; pt[5].z = z ;
			pt[6].x = pt[5].x - 1 ; pt[6].y = pt[5].y - 1 ; pt[6].z = z ;

			/* _hoops_HRSSR _hoops_RCIH */
			pt[7].x = pt[6].x + 1 ; pt[7].y = pt[6].y - 1 ; pt[7].z = z ;
			pt[8].x = pt[7].x + 1 ; pt[8].y = pt[7].y - 1 ; pt[8].z = z ;
			pt[9].x = pt[8].x + 1 ; pt[9].y = pt[8].y     ; pt[9].z = z ;

			/* _hoops_SCHCR _hoops_RCIH */
			pt[10].x = pt[9].x  + 1 ; pt[10].y = pt[9].y      ; pt[10].z = z ;
			pt[11].x = pt[10].x + 1 ; pt[11].y = pt[10].y + 1 ; pt[11].z = z ;
			
			pt[12] = pt[0];

			_hoops_HCICS = 13;
		}
	}
	else if (_hoops_ACICS == 3 && _hoops_PCICS == 1) {
		if(_hoops_AGSSH) {
			/* _hoops_PGSA _hoops_APGR _hoops_HII _hoops_SCIA _hoops_ISHP */
			pt[0].x = x - 2;		pt[0].y = y + 1;		pt[0].z = z ;
			pt[1].x = x + 2;		pt[1].y = y + 1;		pt[1].z = z ;
			pt[2].x = x - 3;		pt[2].y = y;			pt[2].z = z ;
			pt[3].x = x + 3;		pt[3].y = y;			pt[3].z = z ;
			pt[4].x = x - 2;		pt[4].y = y - 1;		pt[4].z = z ;
			pt[5].x = x + 2;		pt[5].y = y - 1;		pt[5].z = z ;

			_hoops_HCICS = -6;
		}
		else {
			/* _hoops_SRS _hoops_RCIH */
			pt[0].x = x + _hoops_ACICS	  ; pt[0].y = y           ;	pt[0].z = z ;
			pt[1].x = pt[0].x - 1 ; pt[1].y = pt[0].y + 1 ; pt[1].z = z ;
			pt[2].x = pt[1].x - 1 ;	pt[2].y = pt[1].y     ; pt[2].z = z ;
			pt[3].x = pt[2].x - 1 ; pt[3].y = pt[2].y     ; pt[3].z = z ;

			/* _hoops_GIAP _hoops_RCIH */
			pt[4].x = pt[3].x - 1 ; pt[4].y = pt[3].y     ; pt[4].z = z ;
			pt[5].x = pt[4].x - 1 ;	pt[5].y = pt[4].y     ; pt[5].z = z ;
			pt[6].x = pt[5].x - 1 ; pt[6].y = pt[5].y - 1 ; pt[6].z = z ;

			/* _hoops_HRSSR _hoops_RCIH */
			pt[7].x = pt[6].x + 1 ; pt[7].y = pt[6].y - 1 ; pt[7].z = z ;
			pt[8].x = pt[7].x + 1 ; pt[8].y = pt[7].y     ; pt[8].z = z ;
			pt[9].x = pt[8].x + 1 ; pt[9].y = pt[8].y     ; pt[9].z = z ;

			/* _hoops_SCHCR _hoops_RCIH */
			pt[10].x = pt[9].x  + 1 ; pt[10].y = pt[9].y  ; pt[10].z = z ;
			pt[11].x = pt[10].x + 1 ; pt[11].y = pt[10].y ; pt[11].z = z ;

			pt[12] = pt[0];

			_hoops_HCICS = 13;
		}
	}
	else if (_hoops_ACICS == 2 && _hoops_PCICS == 3) {
		if(_hoops_AGSSH) {
			/* _hoops_PGSA _hoops_APGR _hoops_HII _hoops_RAAP _hoops_IS _hoops_RPHR */
			pt[0].x = x - 2;		pt[0].y = y + 1;		pt[0].z = z ;
			pt[1].x = x - 2;		pt[1].y = y - 1;		pt[1].z = z ;
			pt[2].x = x - 1;		pt[2].y = y + 2;		pt[2].z = z ;
			pt[3].x = x - 1;		pt[3].y = y - 2;		pt[3].z = z ;
			pt[4].x = x;			pt[4].y = y + 3;		pt[4].z = z ;
			pt[5].x = x;			pt[5].y = y - 3;		pt[5].z = z ;
			pt[6].x = x + 1;		pt[6].y = y + 2;		pt[6].z = z ;
			pt[7].x = x + 1;		pt[7].y = y - 2;		pt[7].z = z ;
			pt[8].x = x + 2;		pt[8].y = y + 1;		pt[8].z = z ;
			pt[9].x = x + 2;		pt[9].y = y - 1;		pt[9].z = z ;

			_hoops_HCICS = -10 ;
		}
		else {
			/* _hoops_SRS _hoops_RCIH */
			pt[0].x = x + _hoops_ACICS	  ; pt[0].y = y           ;	pt[0].z = z ;
			pt[1].x = pt[0].x     ; pt[1].y = pt[0].y + 1 ; pt[1].z = z ;
			pt[2].x = pt[1].x - 1 ;	pt[2].y = pt[1].y + 1 ; pt[2].z = z ;
			pt[3].x = pt[2].x - 1 ; pt[3].y = pt[2].y + 1 ; pt[3].z = z ;

			/* _hoops_GIAP _hoops_RCIH */
			pt[4].x = pt[3].x - 1 ;	pt[4].y = pt[3].y - 1 ; pt[4].z = z ;
			pt[5].x = pt[4].x - 1 ; pt[5].y = pt[4].y - 1 ; pt[5].z = z ;
			pt[6].x = pt[5].x     ;	pt[6].y = pt[5].y - 1 ; pt[6].z = z ;

			/* _hoops_HRSSR _hoops_RCIH */
			pt[7].x = pt[6].x     ; pt[7].y = pt[6].y - 1 ; pt[7].z = z ;
			pt[8].x = pt[7].x + 1 ; pt[8].y = pt[7].y - 1 ; pt[8].z = z ;
			pt[9].x = pt[8].x + 1 ; pt[9].y = pt[8].y - 1 ; pt[9].z = z ;

			/* _hoops_SCHCR _hoops_RCIH */
			pt[10].x = pt[9].x  + 1 ; pt[10].y = pt[9].y  + 1 ; pt[10].z = z ;
			pt[11].x = pt[10].x + 1 ; pt[11].y = pt[10].y + 1 ; pt[11].z = z ;

			pt[12] = pt[0];
			
			_hoops_HCICS = 13;
		}
	}
	else if (_hoops_ACICS == 1 && _hoops_PCICS == 3) {
		if(_hoops_AGSSH) {
			/* _hoops_PGSA _hoops_APGR _hoops_HII _hoops_RAAP _hoops_IS _hoops_RPHR */
			pt[0].x = x - 1;		pt[0].y = y + 2;		pt[0].z = z ;
			pt[1].x = x - 1;		pt[1].y = y - 2;		pt[1].z = z ;
			pt[2].x = x;			pt[2].y = y + 3;		pt[2].z = z ;
			pt[3].x = x;			pt[3].y = y - 3;		pt[3].z = z ;
			pt[4].x = x + 1;		pt[4].y = y + 2;		pt[4].z = z ;
			pt[5].x = x + 1;		pt[5].y = y - 2;		pt[5].z = z ;
			
			_hoops_HCICS = -6;
		}
		else {
			/* _hoops_SRS _hoops_RCIH */
			pt[0].x = x + _hoops_ACICS	  ; pt[0].y = y           ;	pt[0].z = z ;
			pt[1].x = pt[0].x     ; pt[1].y = pt[0].y + 1 ; pt[1].z = z ;
			pt[2].x = pt[1].x     ;	pt[2].y = pt[1].y + 1 ; pt[2].z = z ;
			pt[3].x = pt[2].x - 1 ; pt[3].y = pt[2].y + 1 ; pt[3].z = z ;

			/* _hoops_GIAP _hoops_RCIH */
			pt[4].x = pt[3].x - 1 ; pt[4].y = pt[3].y - 1 ; pt[4].z = z ;
			pt[5].x = pt[4].x     ;	pt[5].y = pt[4].y - 1 ; pt[5].z = z ;
			pt[6].x = pt[5].x     ; pt[6].y = pt[5].y - 1 ; pt[6].z = z ;

			/* _hoops_HRSSR _hoops_RCIH */
			pt[7].x = pt[6].x     ; pt[7].y = pt[6].y - 1 ; pt[7].z = z ;
			pt[8].x = pt[7].x     ; pt[8].y = pt[7].y - 1 ; pt[8].z = z ;
			pt[9].x = pt[8].x + 1 ; pt[9].y = pt[8].y - 1 ; pt[9].z = z ;

			/* _hoops_SCHCR _hoops_RCIH */
			pt[10].x = pt[9].x + 1 ; pt[10].y = pt[9].y  + 1 ; pt[10].z = z ;
			pt[11].x = pt[10].x    ; pt[11].y = pt[10].y + 1 ; pt[11].z = z ;

			pt[12] = pt[0];
			
			_hoops_HCICS = 13;
		}
	}
	else if (_hoops_ACICS == 2 && _hoops_PCICS == 2) {
		if(_hoops_AGSSH) {
			/* _hoops_PGSA _hoops_APGR _hoops_HII _hoops_SCIA _hoops_ISHP */
			pt[0].x = x - 1;		pt[0].y = y + 2;		pt[0].z = z ;
			pt[1].x = x + 1;		pt[1].y = y + 2;		pt[1].z = z ;
			pt[2].x = x - 2;		pt[2].y = y + 1;		pt[2].z = z ;
			pt[3].x = x + 2;		pt[3].y = y + 1;		pt[3].z = z ;
			pt[4].x = x - 2;		pt[4].y = y;			pt[4].z = z ;
			pt[5].x = x + 2;		pt[5].y = y;			pt[5].z = z ;
			pt[6].x = x - 2;		pt[6].y = y - 1;		pt[6].z = z ;
			pt[7].x = x + 2;		pt[7].y = y - 1;		pt[7].z = z ;
			pt[8].x = x - 1;		pt[8].y = y - 2;		pt[8].z = z ;
			pt[9].x = x + 1;		pt[9].y = y - 2;		pt[9].z = z ;

			_hoops_HCICS = -10;
		}
		else {
			/* _hoops_SRS _hoops_RCIH */
			pt[0].x = x + _hoops_ACICS	  ; pt[0].y = y           ;	pt[0].z = z ;
			pt[1].x = pt[0].x     ; pt[1].y = pt[0].y + 1 ; pt[1].z = z ;
			pt[2].x = pt[1].x - 1 ;	pt[2].y = pt[1].y + 1 ; pt[2].z = z ;
			pt[3].x = pt[2].x - 1 ; pt[3].y = pt[2].y     ; pt[3].z = z ;

			/* _hoops_GIAP _hoops_RCIH */
			pt[4].x = pt[3].x - 1 ; pt[4].y = pt[3].y     ; pt[4].z = z ;
			pt[5].x = pt[4].x - 1 ;	pt[5].y = pt[4].y - 1 ; pt[5].z = z ;
			pt[6].x = pt[5].x     ; pt[6].y = pt[5].y - 1 ; pt[6].z = z ;

			/* _hoops_HRSSR _hoops_RCIH */
			pt[7].x = pt[6].x     ; pt[7].y = pt[6].y - 1 ; pt[7].z = z ;
			pt[8].x = pt[7].x + 1 ; pt[8].y = pt[7].y - 1 ; pt[8].z = z ;
			pt[9].x = pt[8].x + 1 ; pt[9].y = pt[8].y     ; pt[9].z = z ;

			/* _hoops_SCHCR _hoops_RCIH */
			pt[10].x = pt[9].x  + 1 ; pt[10].y = pt[9].y      ; pt[10].z = z ;
			pt[11].x = pt[10].x + 1 ; pt[11].y = pt[10].y + 1 ; pt[11].z = z ;

			pt[12] = pt[0];
			
			_hoops_HCICS = 13;
		}
	}
	else if (_hoops_ACICS == 2 && _hoops_PCICS == 1) {
		if(_hoops_AGSSH) {
			/* _hoops_PGSA _hoops_APGR _hoops_HII _hoops_SCIA _hoops_ISHP */
			pt[0].x = x - 1;		pt[0].y = y + 1;		pt[0].z = z ;
			pt[1].x = x + 1;		pt[1].y = y + 1;		pt[1].z = z ;
			pt[2].x = x - 2;		pt[2].y = y;			pt[2].z = z ;
			pt[3].x = x + 2;		pt[3].y = y;			pt[3].z = z ;
			pt[4].x = x - 1;		pt[4].y = y - 1;		pt[4].z = z ;
			pt[5].x = x + 1;		pt[5].y = y - 1;		pt[5].z = z ;

			_hoops_HCICS = -6;
		}
		else {
			/* _hoops_SRS _hoops_RCIH */
			pt[0].x = x + _hoops_ACICS	  ; pt[0].y = y           ;	pt[0].z = z ;
			pt[1].x = pt[0].x - 1 ; pt[1].y = pt[0].y + 1 ; pt[1].z = z ;
			pt[2].x = pt[1].x - 1 ;	pt[2].y = pt[1].y     ; pt[2].z = z ;

			/* _hoops_GIAP _hoops_RCIH */
			pt[3].x = pt[2].x - 1 ; pt[3].y = pt[2].y     ; pt[3].z = z ;
			pt[4].x = pt[3].x - 1 ;	pt[4].y = pt[3].y - 1 ; pt[4].z = z ;

			/* _hoops_HRSSR _hoops_RCIH */
			pt[5].x = pt[4].x + 1 ; pt[5].y = pt[4].y - 1 ; pt[5].z = z ;
			pt[6].x = pt[5].x + 1 ; pt[6].y = pt[5].y     ; pt[6].z = z ;

			/* _hoops_SCHCR _hoops_RCIH */
			pt[7].x = pt[6].x + 1 ; pt[7].y = pt[6].y ; pt[7].z = z ;

			pt[8] = pt[0];
			
			_hoops_HCICS = 9;
		}
	}
	else if (_hoops_ACICS == 1 && _hoops_PCICS == 2) {
		if(_hoops_AGSSH) {
			/* _hoops_PGSA _hoops_APGR _hoops_HII _hoops_RAAP _hoops_IS _hoops_RPHR */
			pt[0].x = x - 1;		pt[0].y = y + 1;		pt[0].z = z ;
			pt[1].x = x - 1;		pt[1].y = y - 1;		pt[1].z = z ;
			pt[2].x = x;			pt[2].y = y + 2;		pt[2].z = z ;
			pt[3].x = x;			pt[3].y = y - 2;		pt[3].z = z ;
			pt[4].x = x + 1;		pt[4].y = y + 1;		pt[4].z = z ;
			pt[5].x = x + 1;		pt[5].y = y - 1;		pt[5].z = z ;

			_hoops_HCICS = -6;
		}
		else {
			/* _hoops_SRS _hoops_RCIH */
			pt[0].x = x + _hoops_ACICS	  ; pt[0].y = y           ;	pt[0].z = z ;
			pt[1].x = pt[0].x     ; pt[1].y = pt[0].y + 1 ; pt[1].z = z ;
			pt[2].x = pt[1].x - 1 ;	pt[2].y = pt[1].y + 1 ; pt[2].z = z ;

			/* _hoops_GIAP _hoops_RCIH */
			pt[3].x = pt[2].x - 1 ; pt[3].y = pt[2].y - 1 ; pt[3].z = z ;
			pt[4].x = pt[3].x     ;	pt[4].y = pt[3].y - 1 ; pt[4].z = z ;

			/* _hoops_HRSSR _hoops_RCIH */
			pt[5].x = pt[4].x     ; pt[5].y = pt[4].y - 1 ; pt[5].z = z ;
			pt[6].x = pt[5].x + 1 ; pt[6].y = pt[5].y - 1 ; pt[6].z = z ;

			/* _hoops_SCHCR _hoops_RCIH */
			pt[7].x = pt[6].x + 1 ; pt[7].y = pt[6].y + 1 ; pt[7].z = z ;

			pt[8] = pt[0];
			
			_hoops_HCICS = 9;
		}
	}
	else if (_hoops_ACICS == 1 && _hoops_PCICS == 1) {
		if(_hoops_AGSSH) {
			/* _hoops_PGSA _hoops_APGR _hoops_GAR _hoops_IRS _hoops_SHHP */
			pt[0].x = x - 1;		pt[0].y = y;			pt[0].z = z ;
			pt[1].x = x + 1;		pt[1].y = y;			pt[1].z = z ;
			pt[2].x = x;			pt[2].y = y + 1;		pt[2].z = z ;
			pt[3].x = x;			pt[3].y = y - 1;		pt[3].z = z ;

			_hoops_HCICS = -4;
		}
		else {
			/* _hoops_SRS _hoops_RCIH */
			pt[0].x = x + _hoops_ACICS	  ; pt[0].y = y           ;	pt[0].z = z ;

			/* _hoops_GIAP _hoops_RCIH */
			pt[1].x = pt[0].x - 1 ; pt[1].y = pt[0].y + 1 ; pt[1].z = z ;

			/* _hoops_HRSSR _hoops_RCIH */
			pt[2].x = pt[1].x - 1 ; pt[2].y = pt[1].y - 1 ; pt[2].z = z ;

			/* _hoops_SCHCR _hoops_RCIH */
			pt[3].x = pt[2].x + 1 ; pt[3].y = pt[2].y - 1 ; pt[3].z = z ;

			pt[4] = pt[0];
			
			_hoops_HCICS = 5;
		}
	}
	else if (_hoops_ACICS==0 && _hoops_PCICS==3) {
		/* _hoops_PGSA _hoops_IRS _hoops_III*/
		pt[0].x = x;		pt[0].y = y + 3;			pt[0].z = z ;
		pt[1].x = x;		pt[1].y = y - 3;			pt[1].z = z ;

		_hoops_HCICS = 2;
	}
	else if (_hoops_ACICS==0 && _hoops_PCICS==2) {
		/* _hoops_PGSA _hoops_IRS _hoops_III*/
		pt[0].x = x;		pt[0].y = y + 2;			pt[0].z = z ;
		pt[1].x = x;		pt[1].y = y - 2;			pt[1].z = z ;

		_hoops_HCICS = 2;
	}
	
	else if (_hoops_ACICS==0 && _hoops_PCICS==1) {
		/* _hoops_PGSA _hoops_IRS _hoops_III*/
		pt[0].x = x;		pt[0].y = y + 1;			pt[0].z = z ;
		pt[1].x = x;		pt[1].y = y - 1;			pt[1].z = z ;

		_hoops_HCICS = 2;
	}
	else if (_hoops_ACICS==3 && _hoops_PCICS==0) {
		/* _hoops_PGSA _hoops_IRS _hoops_III*/
		pt[0].x = x - 3;	pt[0].y = y;				pt[0].z = z ;
		pt[1].x = x + 3;	pt[1].y = y;				pt[1].z = z ;

		_hoops_HCICS = 2;
	}
	else if (_hoops_ACICS==2 && _hoops_PCICS==0) {
		/* _hoops_PGSA _hoops_IRS _hoops_III*/
		pt[0].x = x - 2;	pt[0].y = y;				pt[0].z = z ;
		pt[1].x = x + 2;	pt[1].y = y;				pt[1].z = z ;

		_hoops_HCICS = 2;
	}
	
	else if (_hoops_ACICS==1 && _hoops_PCICS==0) {
		/* _hoops_PGSA _hoops_IRS _hoops_III*/
		pt[0].x = x - 1;	pt[0].y = y;				pt[0].z = z ;
		pt[1].x = x + 1;	pt[1].y = y;				pt[1].z = z ;

		_hoops_HCICS = 2;
	}
	else {
		pt[0].x = x ; pt[0].y = y ; pt[0].z = z ;

		_hoops_HCICS = 1 ;
	}

	*sz=_hoops_HCICS;	
}

#define _hoops_ICICS		-1
#define _hoops_CCICS	0
#define _hoops_SCICS	1

local void draw_dc_ellipse (
	Net_Rendition const &		in_nr,
	DC_Point const *			where,
	DC_Point const *			radii,
	bool						_hoops_AGSSH) {
	DC_Point					pt[4 * 100 + 1];
	float						x, y, z;
	int							_hoops_GSICS;
	int							_hoops_HCICS;
	Net_Rendition				nr = in_nr;
	Net_Rendition				_hoops_RSICS = nr;
	int							i;
	int							_hoops_ASICS;
	int							a;
	int							b;
	int							cx;
	int							cy;
	int							_hoops_PSICS;
	int							_hoops_HSICS;
	double						err;
	double						_hoops_ISICS;
	double						_hoops_CSICS;
	DC_Point alter *			_hoops_SSICS;
	DC_Point alter *			_hoops_GGCCS, *_hoops_RGCCS;
	int							_hoops_AGCCS, _hoops_PGCCS;
	int							_hoops_HGRCR;

	_hoops_GSICS = (int)(0.5f + _hoops_SGIHR (_hoops_IAAA (radii->x, radii->y)));

	if (_hoops_GSICS == 0) {
		if (!_hoops_AGSSH)
			_hoops_HAPIP(nr, where);
		return;
	}

	if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP))
		nr.Modify()->_hoops_IRR.Modify()->_hoops_CHP &= ~_hoops_SHP;

	if (!BIT(nr->_hoops_AHP->flags, _hoops_HGRIP) &&
		BIT(nr->_hoops_AHP->line_style->flags, LSF_MIDDLE_GLYPH|LSF_JOIN))
		nr.Modify()->_hoops_AHP.Modify()->flags |= _hoops_AGRIP;


	if (BIT (nr->transform_rendition->flags, _hoops_AIHS))
		nr.Modify()->transform_rendition.Modify()->flags &= ~_hoops_AIHS;

	if (nr->_hoops_AHP->color != nr->_hoops_IHA->color)
		nr.Modify()->_hoops_AHP.Modify()->color = nr->_hoops_IHA->color;

	if (nr->_hoops_AHP->weight > 1) {
		nr.Modify()->_hoops_AHP.Modify()->weight = 1;
	}

	if (!_hoops_AGSSH) {
		Line_Rendition alter &		_hoops_HGCCS = _hoops_RSICS.Modify()->_hoops_AHP.Modify();

		_hoops_HGCCS->style = LCAP_BUTT|LJOIN_BEVEL;
	}

	x = (float)(int)(where->x + 0.5f);
	y = (float)(int)(where->y + 0.5f);
	z = where->z;

	/* _hoops_PGSA _hoops_RISS _hoops_CHPI */
	if (radii->x < 4.0f && radii->y < 4.0f) {
		int _hoops_IGCCS,	_hoops_CGCCS;
		int _hoops_ACICS, _hoops_PCICS;

		_hoops_IGCCS = int (2 * radii->x + 0.5f);
		_hoops_CGCCS = int (2 * radii->y + 0.5f);

		if (_hoops_IGCCS % 2 == 0)
			_hoops_IGCCS-- ;
		if (_hoops_CGCCS % 2 == 0)
			_hoops_CGCCS-- ;

		_hoops_ACICS = (int)(_hoops_IGCCS / 2);
		_hoops_PCICS = (int)(_hoops_CGCCS / 2);
		_hoops_HCICS=0;
		
		_hoops_RCICS(pt, &_hoops_HCICS, x, y, z, _hoops_ACICS, _hoops_PCICS, 
							_hoops_AGSSH && (nr->_hoops_IHA->pattern == FP_SOLID));

		/* _hoops_SR _hoops_ARPR _hoops_IRS _hoops_GC-_hoops_SHRAA _hoops_AGIS _hoops_IS _hoops_PGSA _hoops_CPPPR _hoops_RISA _hoops_CHPI, _hoops_HIS _hoops_RH 
		 * _hoops_SGCCS _hoops_HSP _hoops_HSGP _hoops_CGH _hoops_SHH _hoops_CHCC _hoops_GAR _hoops_IRS _hoops_ISII */
		if (_hoops_AGSSH) {	
			if (_hoops_HCICS == 1)
				_hoops_AIGGA (nr, _hoops_HCICS, pt);
			else {
				if (nr->_hoops_SRA->_hoops_APHHP == null &&
						nr->_hoops_IHA->pattern == FP_SOLID) {
					nr.Modify()->transform_rendition.Modify()->_hoops_SHIH +=
						nr->transform_rendition->_hoops_CHIH;
					_hoops_SCGGA (nr, _hoops_HCICS, pt); // _hoops_GC _hoops_SHRAA _hoops_AGIS
				}
				else
					_hoops_RSGCP (nr, _hoops_HCICS>0?_hoops_HCICS:-_hoops_HCICS, pt);
			}
		}
		else {
			if (_hoops_HCICS == 1)
				_hoops_AIGGA (nr, _hoops_HCICS, pt);
			else
				_hoops_SCGGA (_hoops_RSICS, _hoops_HCICS, pt);
		}
	}
	/*_hoops_PGSA _hoops_SGRIR _hoops_CHPI */
	else  {
		
		a = (int)(radii->x + 0.5f);
		b = (int)(radii->y + 0.5f); 
		cx = (int)(where->x + 0.5f); 
		cy = (int)(where->y + 0.5f);

		ALLOC_ARRAY_CACHED(_hoops_GGCCS, a+b, DC_Point);
		ALLOC_ARRAY_CACHED(_hoops_SSICS, (b<<2)+2, DC_Point);
		_hoops_PSICS = 0;
		_hoops_HSICS = b;
		_hoops_ISICS = a*a;
		_hoops_CSICS = b*b;
		err = (_hoops_CSICS*4) - ((_hoops_ISICS*b)*4) + _hoops_ISICS;
		_hoops_ASICS = 0;
		_hoops_HGRCR = _hoops_ICICS;
		_hoops_AGCCS = 0;

		while (_hoops_ISICS*((_hoops_HSICS<<1)-1) > (_hoops_CSICS*2)*(_hoops_PSICS+1)) {
			if (err<0) {
				err += (_hoops_CSICS*4)*((_hoops_PSICS<<1)+3);
				if (_hoops_HGRCR != _hoops_ICICS)
				{
					_hoops_GGCCS[_hoops_AGCCS].x = (float)(_hoops_PSICS+cx);
					_hoops_GGCCS[_hoops_AGCCS].y = (float)(_hoops_HSICS+cy);
					_hoops_GGCCS[_hoops_AGCCS++].z = where->z;
					_hoops_HGRCR = _hoops_ICICS;
				}
				++_hoops_PSICS;
			}
			else {
				
				_hoops_SSICS[_hoops_ASICS].x = (float)(_hoops_PSICS+cx);
				_hoops_SSICS[_hoops_ASICS].y = (float)(_hoops_HSICS+cy);
				_hoops_SSICS[_hoops_ASICS++].z = where->z;

				_hoops_SSICS[_hoops_ASICS].x = -(float)(_hoops_PSICS+cx)+(float)(cx<<1);
				_hoops_SSICS[_hoops_ASICS].y = (float)(_hoops_HSICS+cy);
				_hoops_SSICS[_hoops_ASICS++].z = where->z;	
	
				if (_hoops_HGRCR!=_hoops_CCICS)
				{
					_hoops_GGCCS[_hoops_AGCCS].x = (float)(_hoops_PSICS+cx);
					_hoops_GGCCS[_hoops_AGCCS].y = (float)(_hoops_HSICS+cy);
					_hoops_GGCCS[_hoops_AGCCS++].z = where->z;
					_hoops_HGRCR=_hoops_CCICS;
				}

				err += (_hoops_CSICS*4)*((_hoops_PSICS<<1)+3)+(_hoops_ISICS*4)*(-(_hoops_HSICS<<1)+2);
				--_hoops_HSICS;
				++_hoops_PSICS;
			}
		}
		err = _hoops_CSICS*((_hoops_PSICS<<1)+1)*((_hoops_PSICS<<1)+1) + (_hoops_ISICS*4)*(_hoops_HSICS-1)*(_hoops_HSICS-1) - (_hoops_ISICS*4)*_hoops_CSICS;
		while (_hoops_HSICS>0) {
			
			_hoops_SSICS[_hoops_ASICS].x = (float)(_hoops_PSICS+cx);
			_hoops_SSICS[_hoops_ASICS].y = (float)(_hoops_HSICS+cy);
			_hoops_SSICS[_hoops_ASICS++].z = where->z;

			_hoops_SSICS[_hoops_ASICS].x = -(float)(_hoops_PSICS+cx)+(float)(cx<<1);
			_hoops_SSICS[_hoops_ASICS].y = (float)(_hoops_HSICS+cy);
			_hoops_SSICS[_hoops_ASICS++].z = where->z;

			if (err<0) {
				if (_hoops_HGRCR != _hoops_CCICS) {
					_hoops_GGCCS[_hoops_AGCCS].x = (float)(_hoops_PSICS+cx);
					_hoops_GGCCS[_hoops_AGCCS].y = (float)(_hoops_HSICS+cy);
					_hoops_GGCCS[_hoops_AGCCS++].z = where->z;
					_hoops_HGRCR=_hoops_CCICS;
				}

				err += (_hoops_CSICS*8)*(_hoops_PSICS+1) + (_hoops_ISICS*4)*(-(_hoops_HSICS<<1)+3);
				++_hoops_PSICS;
				--_hoops_HSICS;
			}
			else{

				if (_hoops_HGRCR != _hoops_SCICS) {
					_hoops_GGCCS[_hoops_AGCCS].x = (float)(_hoops_PSICS+cx);
					_hoops_GGCCS[_hoops_AGCCS].y = (float)(_hoops_HSICS+cy);
					_hoops_GGCCS[_hoops_AGCCS++].z = where->z;
					_hoops_HGRCR=_hoops_SCICS;
				}

				err += (_hoops_ISICS*4)*(-(_hoops_HSICS<<1)+3);
				--_hoops_HSICS;
			}
		}

		if (_hoops_GGCCS[_hoops_AGCCS-1].x!=(float)(_hoops_PSICS+cx)) {
			_hoops_GGCCS[_hoops_AGCCS].x = (float)(_hoops_PSICS+cx);
			_hoops_GGCCS[_hoops_AGCCS].y = (float)(_hoops_HSICS+cy);
			_hoops_GGCCS[_hoops_AGCCS++].z = where->z;
		}

		_hoops_SSICS[_hoops_ASICS].x = (float)(_hoops_PSICS+cx);
		_hoops_SSICS[_hoops_ASICS].y = (float)(_hoops_HSICS+cy);
		_hoops_SSICS[_hoops_ASICS++].z = where->z;

		_hoops_SSICS[_hoops_ASICS].x = -(float)(_hoops_PSICS+cx)+(float)(cx<<1);
		_hoops_SSICS[_hoops_ASICS].y = (float)(_hoops_HSICS+cy);
		_hoops_SSICS[_hoops_ASICS++].z = where->z;

		/*_hoops_HPIRA _hoops_CISA _hoops_RSSA */
		for (i=0; i<=_hoops_ASICS-3; ++i) {
			_hoops_SSICS[_hoops_ASICS+i].x = _hoops_SSICS[_hoops_ASICS-3-i].x;
			_hoops_SSICS[_hoops_ASICS+i].y = -_hoops_SSICS[_hoops_ASICS-3-i].y+(float)(cy<<1);
			_hoops_SSICS[_hoops_ASICS+i].z = _hoops_SSICS[_hoops_ASICS-3-i].z;
		}
		_hoops_ASICS+=_hoops_ASICS-2;

		
		/*_hoops_HPIRA _hoops_RH _hoops_ISHA _hoops_III */
		_hoops_PGCCS=4*_hoops_AGCCS+1;
		ALLOC_ARRAY_CACHED(_hoops_RGCCS, _hoops_PGCCS, DC_Point);

		for (i=0; i<_hoops_AGCCS; ++i) {
			/* _hoops_SRS _hoops_RCIH */
			_hoops_RGCCS[i] = _hoops_GGCCS[i];

			/*_hoops_SCHCR _hoops_RCIH*/
			_hoops_RGCCS[_hoops_AGCCS+i].x =  _hoops_GGCCS[_hoops_AGCCS-1-i].x;
			_hoops_RGCCS[_hoops_AGCCS+i].y = -_hoops_GGCCS[_hoops_AGCCS-1-i].y+(float)(cy<<1);
			_hoops_RGCCS[_hoops_AGCCS+i].z =  _hoops_GGCCS[_hoops_AGCCS-1-i].z;
		
			/*_hoops_HRSSR _hoops_RCIH*/
			_hoops_RGCCS[2*_hoops_AGCCS+i].x = -_hoops_GGCCS[i].x+(float)(cx<<1);
			_hoops_RGCCS[2*_hoops_AGCCS+i].y = -_hoops_GGCCS[i].y+(float)(cy<<1);
			_hoops_RGCCS[2*_hoops_AGCCS+i].z =  _hoops_GGCCS[i].z;
		
			/*_hoops_GIAP _hoops_RCIH*/
			_hoops_RGCCS[3*_hoops_AGCCS+i].x = -_hoops_GGCCS[_hoops_AGCCS-1-i].x+(float)(cx<<1);
			_hoops_RGCCS[3*_hoops_AGCCS+i].y =  _hoops_GGCCS[_hoops_AGCCS-1-i].y;
			_hoops_RGCCS[3*_hoops_AGCCS+i].z =  _hoops_GGCCS[_hoops_AGCCS-1-i].z;
		}

		_hoops_RGCCS[_hoops_PGCCS-1] = _hoops_GGCCS[0];
		FREE_ARRAY(_hoops_GGCCS, a+b, DC_Point);
		
		/*_hoops_PGSA _hoops_SCH*/		
		if (_hoops_AGSSH) {
			if (nr->_hoops_IHA->pattern!=FP_SOLID)
				_hoops_RSGCP(nr, _hoops_PGCCS, _hoops_RGCCS);
			else {
				nr.Modify()->transform_rendition.Modify()->_hoops_SHIH +=
					nr->transform_rendition->_hoops_CHIH;
				_hoops_SCGGA(nr, -_hoops_ASICS, _hoops_SSICS);	// _hoops_GC _hoops_SHRAA _hoops_AGIS
			}
		}
		else
			_hoops_SCGGA(_hoops_RSICS, _hoops_PGCCS, _hoops_RGCCS);

		FREE_ARRAY(_hoops_SSICS, _hoops_ASICS, DC_Point);
		FREE_ARRAY(_hoops_RGCCS, _hoops_PGCCS, DC_Point);
	}
}



GLOBAL_FUNCTION void HD_Std_DC_Ellipse (
	Net_Rendition const &		nr,
	DC_Point const *			where,
	DC_Point const *			radii) {

	draw_dc_ellipse (nr, where, radii, true);
}



GLOBAL_FUNCTION void HD_Std_DC_Outline_Ellipse (
	Net_Rendition const &		nr,
	DC_Point const *			where,
	DC_Point const *			radii) {

	draw_dc_ellipse (nr, where, radii, false);
}


