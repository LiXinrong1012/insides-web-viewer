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
 * $Id: obf_tmp.txt 1.18 2010-10-06 19:16:35 jason Exp $
 */

#ifndef _hoops_CHRGGR

Begin_HOOPS_Namespace

enum _hoops_ICARR{
	_hoops_PAIRI = 1,
	_hoops_CCARR,
	_hoops_CIARC,
	_hoops_ICIHA,
	_hoops_CGCSS,
	_hoops_GRCSS,
	_hoops_IRCSS,
	_hoops_SRCSS,
	_hoops_HPPAH,
	_hoops_IPPAH
};

class HOOPS_API _hoops_GCARR : public CMO {

public:

	_hoops_GCARR() {_hoops_SHRGGR=false;};
	virtual ~_hoops_GCARR() {;};

	virtual void _hoops_HCARR(bool _hoops_SCARR)=0;

	virtual _hoops_ICARR Type()=0;

	virtual bool _hoops_GCIRI(_hoops_GCARR const * _hoops_ARCSS) {UNREFERENCED(_hoops_ARCSS);return false;}

	INLINE _hoops_GSPGR _hoops_IPIRI() {return time_stamp;};
	INLINE void _hoops_CIIRI(_hoops_GSPGR _hoops_GIRGGR) {time_stamp = _hoops_GIRGGR;};

private:

	bool			_hoops_SHRGGR;
	volatile _hoops_GSPGR	time_stamp;
	_hoops_GCARR *			_hoops_PIIRI;
	friend class _hoops_SRIAP;
};


class HOOPS_API _hoops_SRIAP : public CMO {

public:

	_hoops_SRIAP(int _hoops_PHCHA=1, bool _hoops_GCSIH=false);

	~_hoops_SRIAP();

	void _hoops_PCARR(_hoops_GCARR * _hoops_HPIRI, int _hoops_HIIRI=0);
	
	_hoops_GCARR * _hoops_IAIRI(_hoops_GCARR * _hoops_SIIRI = null);

	bool _hoops_APIRI() {return _hoops_HHIRI > 0;};

	void _hoops_RHIRI() {
		LOCK_MUTEX (HOOPS_WORLD->_hoops_PIPSA);
		_hoops_HHIRI--;
		UNLOCK_MUTEX (HOOPS_WORLD->_hoops_PIPSA);
	};

	bool _hoops_PPIRI() {return _hoops_GCSIH;};

	

private:
	_hoops_GCARR *					_hoops_PHIRI;
	_hoops_CPGRR					_hoops_IHIRI;
	HM_Semaphore			_hoops_CHIRI;

	int						_hoops_PHCHA;
	HThreadHandle *			_hoops_SHIRI;

	bool					_hoops_GCSIH;

	volatile int			_hoops_HHIRI;
};

End_HOOPS_Namespace;

#define _hoops_CHRGGR
#endif
