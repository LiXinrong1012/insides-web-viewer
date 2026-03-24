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
 * $Id: obf_tmp.txt 1.64 2010-06-04 21:37:19 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"





GLOBAL_FUNCTION int HD_Transform_Not_At_All (
	_hoops_HHCR const &	_hoops_IHCR,
	int							point_count,
	Point const *				in,
	float const *				_hoops_CCIPA,
	_hoops_PACIR const *	_hoops_GPHH,
	DC_Point alter *			_hoops_PAGR,
	float alter *				ws,
	_hoops_GRCAR alter *			_hoops_ARCAR) {
	Point const *				_hoops_PPIPR = in + point_count;

	UNREFERENCED (_hoops_CCIPA);

	if (BIT (_hoops_IHCR->flags, _hoops_AIHS) ||
		!BIT (_hoops_IHCR->heuristics, _hoops_PICAR)) {
		if (BIT(_hoops_IHCR->flags, _hoops_PASP)) _hoops_PCCAR {
			_hoops_PAGR->x = in->x;
			_hoops_PAGR->y = in->y;
			_hoops_PAGR->z = in->z;
			if (_hoops_PAGR->z > _hoops_IHCR->_hoops_PCHH)
				_hoops_PAGR->z = _hoops_IHCR->_hoops_PCHH;
			else if (_hoops_PAGR->z < 0.0f)
				_hoops_PAGR->z = 0.0f;

			*ws = 1.0f;
			*_hoops_ARCAR = _hoops_HCRCP;

			if (++in == _hoops_PPIPR)
				return point_count;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
		else _hoops_PCCAR {
			_hoops_PAGR->x = in->x;
			_hoops_PAGR->y = in->y;
			_hoops_PAGR->z = in->z;

			*ws = 1.0f;
			*_hoops_ARCAR = _hoops_HCRCP;

			if (++in == _hoops_PPIPR)
				return point_count;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}
	else {
		int						_hoops_AHGPS = 0;

		_hoops_PCCAR {
			_hoops_PAGR->x = in->x;
			_hoops_PAGR->y = in->y;
			_hoops_PAGR->z = in->z;
			if (BIT(_hoops_IHCR->flags, _hoops_PASP)) {
				if (_hoops_PAGR->z > _hoops_IHCR->_hoops_PCHH)
					_hoops_PAGR->z = _hoops_IHCR->_hoops_PCHH;
				else if (_hoops_PAGR->z < 0.0f)
					_hoops_PAGR->z = 0.0f;
			}

			*ws = 1.0f;
			*_hoops_ARCAR = _hoops_HCRCP;
			if (_hoops_PAGR->x < _hoops_GPHH->left)   
				*_hoops_ARCAR |= _hoops_SCIIS;
			if (_hoops_PAGR->x > _hoops_GPHH->right)  
				*_hoops_ARCAR |= CC_OFF_TO_RIGHT;
			if (_hoops_PAGR->y < _hoops_GPHH->bottom) 
				*_hoops_ARCAR |= CC_OFF_TO_BOTTOM;
			if (_hoops_PAGR->y > _hoops_GPHH->top)	  
				*_hoops_ARCAR |= _hoops_GSIIS;
			if (*_hoops_ARCAR == _hoops_HCRCP)
				++_hoops_AHGPS;

			if (++in == _hoops_PPIPR)
				return _hoops_AHGPS;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}
}


GLOBAL_FUNCTION int HD_Transform_And_Test_XY_XY (
	_hoops_HHCR const &	_hoops_IHCR,
	int							point_count,
	Point const *				in,
	float const *				_hoops_CCIPA,
	_hoops_PACIR const *	_hoops_GPHH,
	DC_Point alter *			_hoops_PAGR,
	float alter *				ws,
	_hoops_GRCAR alter *			_hoops_ARCAR) {
	Point const *				_hoops_PPIPR = in + point_count;
	_hoops_RPRA const *			matrix = (_hoops_RPRA const *)_hoops_CCIPA;

	if (BIT (_hoops_IHCR->flags, _hoops_AIHS) ||
		!BIT (_hoops_IHCR->heuristics, _hoops_PICAR)) {
		_hoops_PCCAR {
			_hoops_PAGR->x = _hoops_PRPPI (matrix, *in);
			_hoops_PAGR->y = _hoops_HRPPI (matrix, *in);
			_hoops_PAGR->z = 0.0f;

			*ws = 1.0f;
			*_hoops_ARCAR = _hoops_HCRCP;

			if (++in == _hoops_PPIPR)
				return point_count;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}
	else {
		int						_hoops_AHGPS = 0;

		_hoops_PCCAR {
			_hoops_PAGR->x = _hoops_PRPPI (matrix, *in);
			_hoops_PAGR->y = _hoops_HRPPI (matrix, *in);
			_hoops_PAGR->z = 0.0f;

			*ws = 1.0f;
			*_hoops_ARCAR = _hoops_HCRCP;
			if (_hoops_PAGR->x < _hoops_GPHH->left)   
				*_hoops_ARCAR |= _hoops_SCIIS;
			if (_hoops_PAGR->x > _hoops_GPHH->right)  
				*_hoops_ARCAR |= CC_OFF_TO_RIGHT;
			if (_hoops_PAGR->y < _hoops_GPHH->bottom) 
				*_hoops_ARCAR |= CC_OFF_TO_BOTTOM;
			if (_hoops_PAGR->y > _hoops_GPHH->top)	   
				*_hoops_ARCAR |= _hoops_GSIIS;
			if (*_hoops_ARCAR == _hoops_HCRCP)
				++_hoops_AHGPS;

			if (++in == _hoops_PPIPR)
				return _hoops_AHGPS;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}
}


GLOBAL_FUNCTION int HD_Transform_And_Test_XYZ_XY (
	_hoops_HHCR const &	_hoops_IHCR,
	int							point_count,
	Point const *				in,
	float const *				_hoops_CCIPA,
	_hoops_PACIR const *	_hoops_GPHH,
	DC_Point alter *			_hoops_PAGR,
	float alter *				ws,
	_hoops_GRCAR alter *			_hoops_ARCAR) {
	Point const *				_hoops_PPIPR = in + point_count;
	_hoops_RPRA const *			matrix = (_hoops_RPRA const *)_hoops_CCIPA;

	if (BIT (_hoops_IHCR->flags, _hoops_AIHS) ||
		!BIT (_hoops_IHCR->heuristics, _hoops_PICAR)) {
		_hoops_PCCAR {
			_hoops_PAGR->x = _hoops_HPRA (matrix, *in);
			_hoops_PAGR->y = _hoops_IPRA (matrix, *in);
			_hoops_PAGR->z = 0.0f;

			*ws = 1.0f;
			*_hoops_ARCAR = _hoops_HCRCP;

			if (++in == _hoops_PPIPR)
				return point_count;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}
	else {
		int		_hoops_AHGPS = 0;

		_hoops_PCCAR {
			_hoops_PAGR->x = _hoops_HPRA (matrix, *in);
			_hoops_PAGR->y = _hoops_IPRA (matrix, *in);
			_hoops_PAGR->z = 0.0f;

			*ws = 1.0f;
			*_hoops_ARCAR = _hoops_HCRCP;
			if (_hoops_PAGR->x < _hoops_GPHH->left)   
				*_hoops_ARCAR |= _hoops_SCIIS;
			if (_hoops_PAGR->x > _hoops_GPHH->right)  
				*_hoops_ARCAR |= CC_OFF_TO_RIGHT;
			if (_hoops_PAGR->y < _hoops_GPHH->bottom) 
				*_hoops_ARCAR |= CC_OFF_TO_BOTTOM;
			if (_hoops_PAGR->y > _hoops_GPHH->top)	   
				*_hoops_ARCAR |= _hoops_GSIIS;
			if (*_hoops_ARCAR == _hoops_HCRCP)
				++_hoops_AHGPS;

			if (++in == _hoops_PPIPR)
				return _hoops_AHGPS;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}
}


GLOBAL_FUNCTION int HD_Transform_And_Test_XYZ_XYZ (
	_hoops_HHCR const &	_hoops_IHCR,
	int							point_count,
	Point const *				in,
	float const *				_hoops_CCIPA,
	_hoops_PACIR const *	_hoops_GPHH,
	DC_Point alter *			_hoops_PAGR,
	float alter *				ws,
	_hoops_GRCAR alter *			_hoops_ARCAR) {
	Point const *				_hoops_PPIPR = in + point_count;
	_hoops_RPRA const *			matrix = (_hoops_RPRA const *)_hoops_CCIPA;
	float						_hoops_PCHH = _hoops_IHCR->_hoops_PCHH;

	if (BIT (_hoops_IHCR->flags, _hoops_AIHS) ||
		!BIT (_hoops_IHCR->heuristics, _hoops_PICAR)) {
		if (BIT(_hoops_IHCR->flags, _hoops_PASP)) _hoops_PCCAR {
			_hoops_PAGR->x = _hoops_HPRA (matrix, *in);
			_hoops_PAGR->y = _hoops_IPRA (matrix, *in);
			_hoops_PAGR->z = _hoops_CPRA (matrix, *in);

			if (_hoops_PAGR->z > _hoops_PCHH)
				_hoops_PAGR->z = _hoops_PCHH;
			else if (_hoops_PAGR->z < 0.0f)
				_hoops_PAGR->z = 0.0f;

			*ws = 1.0f;
			*_hoops_ARCAR = _hoops_HCRCP;

			if (++in == _hoops_PPIPR)
				return point_count;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
		else _hoops_PCCAR {
			_hoops_PAGR->x = _hoops_HPRA (matrix, *in);
			_hoops_PAGR->y = _hoops_IPRA (matrix, *in);
			_hoops_PAGR->z = _hoops_CPRA (matrix, *in);

			*ws = 1.0f;
			*_hoops_ARCAR = _hoops_HCRCP;

			if (++in == _hoops_PPIPR)
				return point_count;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}
	else {
		int						_hoops_AHGPS = 0;

		if (BIT(_hoops_IHCR->flags, _hoops_PASP)) _hoops_PCCAR {
			_hoops_PAGR->x = _hoops_HPRA (matrix, *in);
			_hoops_PAGR->y = _hoops_IPRA (matrix, *in);
			_hoops_PAGR->z = _hoops_CPRA (matrix, *in);

			if (_hoops_PAGR->z > _hoops_PCHH)
				_hoops_PAGR->z = _hoops_PCHH;
			else if (_hoops_PAGR->z < 0.0f)
				_hoops_PAGR->z = 0.0f;

			*ws = 1.0f;
			*_hoops_ARCAR = _hoops_HCRCP;
			if (_hoops_PAGR->x < _hoops_GPHH->left)   
				*_hoops_ARCAR |= _hoops_SCIIS;
			if (_hoops_PAGR->x > _hoops_GPHH->right) 
				*_hoops_ARCAR |= CC_OFF_TO_RIGHT;
			if (_hoops_PAGR->y < _hoops_GPHH->bottom) 
				*_hoops_ARCAR |= CC_OFF_TO_BOTTOM;
			if (_hoops_PAGR->y > _hoops_GPHH->top)	  
				*_hoops_ARCAR |= _hoops_GSIIS;
			if (*_hoops_ARCAR == _hoops_HCRCP)
				++_hoops_AHGPS;

			if (++in == _hoops_PPIPR)
				return _hoops_AHGPS;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
		else _hoops_PCCAR {
			_hoops_PAGR->x = _hoops_HPRA (matrix, *in);
			_hoops_PAGR->y = _hoops_IPRA (matrix, *in);
			_hoops_PAGR->z = _hoops_CPRA (matrix, *in);

			*ws = 1.0f;
			*_hoops_ARCAR = _hoops_HCRCP;
			if (_hoops_PAGR->x < _hoops_GPHH->left)   
				*_hoops_ARCAR |= _hoops_SCIIS;
			if (_hoops_PAGR->x > _hoops_GPHH->right)  
				*_hoops_ARCAR |= CC_OFF_TO_RIGHT;
			if (_hoops_PAGR->y < _hoops_GPHH->bottom) 
				*_hoops_ARCAR |= CC_OFF_TO_BOTTOM;
			if (_hoops_PAGR->y > _hoops_GPHH->top)	   
				*_hoops_ARCAR |= _hoops_GSIIS;
			if (*_hoops_ARCAR == _hoops_HCRCP)
				++_hoops_AHGPS;

			if (++in == _hoops_PPIPR)
				return _hoops_AHGPS;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}

}


GLOBAL_FUNCTION int HD_Transform_And_Test_XYZ_XY_W (
	_hoops_HHCR const &	_hoops_IHCR,
	int							point_count,
	Point const *				in,
	float const *				_hoops_CCIPA,
	_hoops_PACIR const *	_hoops_GPHH,
	DC_Point alter *			_hoops_PAGR,
	float alter *				ws,
	_hoops_GRCAR alter *			_hoops_ARCAR) {
	Point const *				_hoops_PPIPR = in + point_count;
	_hoops_RPRA const *			matrix = (_hoops_RPRA const *)_hoops_CCIPA;

	if (BIT (_hoops_IHCR->flags, _hoops_AIHS) ||
		!BIT (_hoops_IHCR->heuristics, _hoops_PICAR)) {
		_hoops_PCCAR {
			*ws = _hoops_PHCP (matrix, *in);
			_hoops_PAGR->x = _hoops_HPRA (matrix, *in) / *ws;
			_hoops_PAGR->y = _hoops_IPRA (matrix, *in) / *ws;
			_hoops_PAGR->z = 0.0f;

			*_hoops_ARCAR = _hoops_HCRCP;

			if (++in == _hoops_PPIPR)
				return point_count;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}
	else {
		int						_hoops_AHGPS = 0;

		_hoops_PCCAR {
			*ws = _hoops_PHCP (matrix, *in);
			_hoops_PAGR->z = 0.0f;

			if (*ws <= _hoops_IHCR->_hoops_CHCR) {
				_hoops_PAGR->x = _hoops_HPRA (matrix, *in);
				_hoops_PAGR->y = _hoops_IPRA (matrix, *in);

				*_hoops_ARCAR = _hoops_IPCAR;
			}
			else {
				_hoops_PAGR->x = _hoops_HPRA (matrix, *in) / *ws;
				_hoops_PAGR->y = _hoops_IPRA (matrix, *in) / *ws;

				*_hoops_ARCAR = _hoops_HCRCP;
				if (_hoops_PAGR->x < _hoops_GPHH->left)   
					*_hoops_ARCAR |= _hoops_SCIIS;
				if (_hoops_PAGR->x > _hoops_GPHH->right)  
					*_hoops_ARCAR |= CC_OFF_TO_RIGHT;
				if (_hoops_PAGR->y < _hoops_GPHH->bottom) 
					*_hoops_ARCAR |= CC_OFF_TO_BOTTOM;
				if (_hoops_PAGR->y > _hoops_GPHH->top)	   
					*_hoops_ARCAR |= _hoops_GSIIS;
				if (*_hoops_ARCAR == _hoops_HCRCP)
					++_hoops_AHGPS;
			}

			if (++in == _hoops_PPIPR)
				return _hoops_AHGPS;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}
}

static const float _hoops_CIGRGR[64] = {
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1
};

GLOBAL_FUNCTION int HD_Transform_And_Test_XYZ_XYZ_W (
	_hoops_HHCR const &	_hoops_IHCR,
	int							point_count,
	Point const *				in,
	float const *				_hoops_CCIPA,
	_hoops_PACIR const *	_hoops_GPHH,
	DC_Point alter *			_hoops_PAGR,
	float alter *				ws,
	_hoops_GRCAR alter *			_hoops_ARCAR) {
#if 0
	Point const *				_hoops_PPIPR = in + point_count;
	_hoops_RPRA const *			matrix = (_hoops_RPRA const *)_hoops_CCIPA;

	if (BIT (_hoops_IHCR->flags, _hoops_AIHS) ||
		!BIT (_hoops_IHCR->heuristics, _hoops_PICAR)) {
		_hoops_PCCAR {
			*ws = _hoops_PHCP (matrix, *in);
			_hoops_PAGR->x = _hoops_HPRA (matrix, *in) / *ws;
			_hoops_PAGR->y = _hoops_IPRA (matrix, *in) / *ws;
			_hoops_PAGR->z = _hoops_CPRA (matrix, *in) / *ws;

			*_hoops_ARCAR = _hoops_HCRCP;

			if (++in == _hoops_PPIPR)
				return point_count;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}
	else {
		int						_hoops_AHGPS = 0;

		_hoops_PCCAR {
			*ws = _hoops_PHCP (matrix, *in);

			if (*ws <= _hoops_IHCR->_hoops_CHCR) {
				_hoops_PAGR->x = _hoops_HPRA (matrix, *in);
				_hoops_PAGR->y = _hoops_IPRA (matrix, *in);
				_hoops_PAGR->z = _hoops_CPRA (matrix, *in);

				*_hoops_ARCAR = _hoops_IPCAR;
			}
			else {
				_hoops_PAGR->x = _hoops_HPRA (matrix, *in) / *ws;
				_hoops_PAGR->y = _hoops_IPRA (matrix, *in) / *ws;
				_hoops_PAGR->z = _hoops_CPRA (matrix, *in) / *ws;

				*_hoops_ARCAR = _hoops_HCRCP;
				if (_hoops_PAGR->x < _hoops_GPHH->left)   
					*_hoops_ARCAR |= _hoops_SCIIS;
				if (_hoops_PAGR->x > _hoops_GPHH->right)  
					*_hoops_ARCAR |= CC_OFF_TO_RIGHT;
				if (_hoops_PAGR->y < _hoops_GPHH->bottom) 
					*_hoops_ARCAR |= CC_OFF_TO_BOTTOM;
				if (_hoops_PAGR->y > _hoops_GPHH->top)	  
					*_hoops_ARCAR |= _hoops_GSIIS;
				if (*_hoops_ARCAR == _hoops_HCRCP)
					++_hoops_AHGPS;
			}

			if (++in == _hoops_PPIPR)
				return _hoops_AHGPS;

			++_hoops_PAGR;
			++ws;
			++_hoops_ARCAR;
		}
	}
#else
	HI_Transform_Points_44 (point_count, in, _hoops_CCIPA, _hoops_IHCR->_hoops_CHCR, (Point *)_hoops_PAGR, ws);

	if (BIT (_hoops_IHCR->flags, _hoops_AIHS) || !BIT (_hoops_IHCR->heuristics, _hoops_PICAR)) {
		float const				*_hoops_SIGRGR = ws + point_count;
		int						_hoops_IGIC = 64;

		ASSERT (sizeof(_hoops_GRCAR) == sizeof (unsigned char));  //_hoops_IAII _hoops_RH _hoops_RCGHA _hoops_CAPP _hoops_PPPPR'_hoops_RA _hoops_IPHR
		SET_MEMORY (_hoops_ARCAR, point_count, _hoops_HCRCP);
		do {
			if (_hoops_SIGRGR - ws < _hoops_IGIC)
				_hoops_IGIC = _hoops_SIGRGR - ws;
			_hoops_AIGA (_hoops_CIGRGR, _hoops_IGIC, float, ws);
			ws += _hoops_IGIC;
		} while (ws < _hoops_SIGRGR);
		return point_count;
	}
	else {
		DC_Point const		*_hoops_GCGRGR = _hoops_PAGR + point_count;
		int						_hoops_AHGPS = 0;

		_hoops_PCCAR {
			if (*ws <= _hoops_IHCR->_hoops_CHCR)
				*_hoops_ARCAR = _hoops_IPCAR;
			else {
				*_hoops_ARCAR = _hoops_HCRCP;
				if (_hoops_PAGR->x < _hoops_GPHH->left)   
					*_hoops_ARCAR |= _hoops_SCIIS;
				if (_hoops_PAGR->x > _hoops_GPHH->right)  
					*_hoops_ARCAR |= CC_OFF_TO_RIGHT;
				if (_hoops_PAGR->y < _hoops_GPHH->bottom)
					*_hoops_ARCAR |= CC_OFF_TO_BOTTOM;
				if (_hoops_PAGR->y > _hoops_GPHH->top)	   
					*_hoops_ARCAR |= _hoops_GSIIS;
				if (*_hoops_ARCAR == _hoops_HCRCP)
					++_hoops_AHGPS;
			}

			if (++_hoops_PAGR == _hoops_GCGRGR)
				return _hoops_AHGPS;

			++ws;
			++_hoops_ARCAR;
		}
	}
#endif
}
