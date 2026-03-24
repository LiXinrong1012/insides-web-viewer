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
 * $Id: obf_tmp.txt 1.102 2010-06-16 22:04:10 covey Exp $
 */

#ifndef _hoops_PRHHS
#define _hoops_PRHHS


Begin_HOOPS_Namespace

#ifdef DISABLE_TABLE_LOOKUPS
#	 define _hoops_PHGCR(a, b) ((a) * (b))
#else
	GLOBAL_DATA const unsigned short _hoops_HRHHS[256][256];
#	 define _hoops_PHGCR(a, b) (_hoops_HRHHS[a][b])
#endif

/*
 * _hoops_RAIGR _hoops_RPIHR _hoops_PPSR _hoops_PHI _hoops_HRGR _hoops_IGI _hoops_IS _hoops_HCAAA _hoops_IRS 32 _hoops_IGRH _hoops_PHI, _hoops_CCA
 * 16 _hoops_SIH _hoops_IIGR _hoops_GRASP _hoops_PPR 16 _hoops_IGRH _hoops_PSHII _hoops_GPPS.
 * _hoops_IRHHS _hoops_HRGR _hoops_CRHHS _hoops_HPP _hoops_PGICR _hoops_PCPHS _hoops_RH _hoops_HHIPR _hoops_ARIP.
 * _hoops_SRHHS _hoops_PGPP _hoops_PAH _hoops_SHH _hoops_CRHHS _hoops_HPP _hoops_PCPHS _hoops_RH _hoops_RSIR
 * _hoops_HRPR _hoops_GAR _hoops_IRS _hoops_RSRA _hoops_HPI (_hoops_RH "_hoops_PHI" _hoops_PAIP).
 */
struct _hoops_GAHHS {
#	 if HOOPS_BIGENDIAN
		unsigned char	_hoops_GPCIC;
		unsigned char	_hoops_CHHI;
		unsigned char	_hoops_IHHI;
		unsigned char	_hoops_SACIC;
#	 else
		unsigned char	_hoops_SACIC;
		unsigned char	_hoops_IHHI;
		unsigned char	_hoops_CHHI;
		unsigned char	_hoops_GPCIC;
#	 endif
};

struct _hoops_RAHHS {
#	if HOOPS_BIGENDIAN
		short				_hoops_SAGCR;		/* _hoops_GRASP _hoops_ARIP, 16b.0b   */
		unsigned short		_hoops_RCGCR;		/* _hoops_PSHII _hoops_ARIP, 0b.16b */
#	else
		unsigned short		_hoops_RCGCR;		/* _hoops_PSHII _hoops_ARIP, 0b.16b */
		short				_hoops_SAGCR;		/* _hoops_GRASP _hoops_ARIP, 16b.0b   */
#	endif
};


union _hoops_CRRRH {
	Integer32						number;			/* _hoops_RSIR _hoops_PHI, 16b.16b  */
	struct _hoops_GAHHS _hoops_SHGGR;
	struct _hoops_RAHHS _hoops_CAGCR;
};


struct _hoops_GHGCR{
	_hoops_CRRRH		r;
	_hoops_CRRRH		g;
	_hoops_CRRRH		b;
};


#define LOAD_ARGUMENT(arg)	(void)(arg)
#define TRUNCATE_POINT(src, _hoops_AAHHS, _hoops_HRGSP, _hoops_PAHHS, _hoops_PSHRS)		\
		_hoops_HRGSP[_hoops_PAHHS]._hoops_PSHRS = _hoops_ISCSH(src[_hoops_AAHHS]._hoops_PSHRS)
#define _hoops_HAHHS(src, _hoops_HRGSP) \
		_hoops_HRGSP = _hoops_ISCSH(src)


#define TRUNCATE_3_POINTS(src, _hoops_HRGSP, _hoops_ICIPR, _hoops_CCIPR, _hoops_GCGCR, _hoops_PSHRS)	\
		TRUNCATE_POINT (src, _hoops_ICIPR, _hoops_HRGSP, 0, _hoops_PSHRS);				\
		TRUNCATE_POINT (src, _hoops_CCIPR, _hoops_HRGSP, 1, _hoops_PSHRS);				\
		TRUNCATE_POINT (src, _hoops_GCGCR, _hoops_HRGSP, 2, _hoops_PSHRS); 

#define TRUNCATE_2_POINTS(src, _hoops_HRGSP, _hoops_ICIPR, _hoops_CCIPR, _hoops_PSHRS)				\
		TRUNCATE_POINT (src, _hoops_ICIPR, _hoops_HRGSP, 0, _hoops_PSHRS);				\
		TRUNCATE_POINT (src, _hoops_CCIPR, _hoops_HRGSP, 1, _hoops_PSHRS); 

#define _hoops_IAHHS(src, _hoops_HRGSP, _hoops_ICIPR, _hoops_CCIPR, _hoops_GCGCR)	\
		_hoops_HRGSP[0] = &src[_hoops_ICIPR]; _hoops_HRGSP[1] = &src[_hoops_CCIPR]; _hoops_HRGSP[2] = &src[_hoops_GCGCR];

#define _hoops_AGRCR(src, _hoops_HRGSP, _hoops_ICIPR, _hoops_CCIPR, _hoops_GCGCR) \
		_hoops_HRGSP[0].r = _hoops_IRGCR(src[_hoops_ICIPR].r);	\
		_hoops_HRGSP[0].g = _hoops_IRGCR(src[_hoops_ICIPR].g);	\
		_hoops_HRGSP[0].b = _hoops_IRGCR(src[_hoops_ICIPR].b);	\
		_hoops_HRGSP[1].r = _hoops_IRGCR(src[_hoops_CCIPR].r);	\
		_hoops_HRGSP[1].g = _hoops_IRGCR(src[_hoops_CCIPR].g);	\
		_hoops_HRGSP[1].b = _hoops_IRGCR(src[_hoops_CCIPR].b);	\
		_hoops_HRGSP[2].r = _hoops_IRGCR(src[_hoops_GCGCR].r);	\
		_hoops_HRGSP[2].g = _hoops_IRGCR(src[_hoops_GCGCR].g);	\
		_hoops_HRGSP[2].b = _hoops_IRGCR(src[_hoops_GCGCR].b);

	
#define _hoops_CAHHS 4
#define _hoops_PRGCR(a,b,which) \
				((_hoops_ARGCR = a.which - b.which) < _hoops_CAHHS && _hoops_ARGCR > -_hoops_CAHHS)


#define _hoops_CRGCR(a, b) {register int _hoops_SAHHS = (a); (a) = (b); (b) = _hoops_SAHHS;}

#define _hoops_ACGCR(_hoops_CPGCR, _hoops_AGCII, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR) \
	(((_hoops_GIGCR) <= (_hoops_CPGCR)) ? ((_hoops_RIGCR) <= (_hoops_CPGCR)) ? ((d3) <= (_hoops_CPGCR)) ? (_hoops_HIGCR) : (_hoops_PIGCR) : (_hoops_AIGCR) : (_hoops_AGCII))

#define _hoops_GPHHS(_hoops_IRPHS, _hoops_SSHGA, _hoops_RPHHS, remainder) \
	_hoops_RPHHS = _hoops_IRPHS / _hoops_SSHGA; \
	remainder = _hoops_IRPHS % _hoops_SSHGA;


struct _hoops_GHISP {
	_hoops_PC				_hoops_AGP;		// _hoops_IH _hoops_APHHS _hoops_RGAR
	_hoops_HHA			_hoops_CHA;		// _hoops_IH _hoops_APHHS _hoops_RGAR
	Driver_Color				color;
	int							_hoops_PIHSR;	// _hoops_CPPC _hoops_GPRR _hoops_IIGR "_hoops_HAIR" _hoops_PAIP
	int							pattern;
	Driver_Color				contrast_color; // _hoops_SPASR _hoops_CSPH->_hoops_CPHSR._hoops_AHRHH
	Integer32					z;
};



/*
 * _hoops_PPHHS _hoops_CSSC
 */
 
struct _hoops_HPHHS {
#	if HOOPS_BIGENDIAN
		unsigned char	_hoops_GPCIC;
		unsigned char	_hoops_CHHI;
		unsigned char	_hoops_IHHI;
		unsigned char	_hoops_SACIC;
#	else
		unsigned char	_hoops_SACIC;
		unsigned char	_hoops_IHHI;
		unsigned char	_hoops_CHHI;
		unsigned char	_hoops_GPCIC;
#	endif
};

struct _hoops_IPHHS {
#	if HOOPS_BIGENDIAN
		unsigned short		_hoops_SAGCR;		/* _hoops_GRASP _hoops_ARIP, 16b.0b   */
		unsigned short		_hoops_RCGCR;		/* _hoops_PSHII _hoops_ARIP, 0b.16b */
#	else
		unsigned short		_hoops_RCGCR;		/* _hoops_PSHII _hoops_ARIP, 0b.16b */
		unsigned short		_hoops_SAGCR;		/* _hoops_GRASP _hoops_ARIP, 16b.0b   */
#	endif
};

union _hoops_CPHHS{
	unsigned Integer32				 number;		 /* _hoops_RSIR _hoops_PHI, 16b.16b	*/
	_hoops_HPHHS _hoops_SHGGR;
	_hoops_IPHHS _hoops_CAGCR;
};


struct _hoops_SPHHS {
	_hoops_CRRRH		_hoops_HAGR;
	_hoops_CRRRH		_hoops_HGRCR;
};

struct _hoops_GRGCR {
	_hoops_CPHHS		_hoops_HAGR;
	_hoops_CRRRH		_hoops_HGRCR;
};

INLINE void _hoops_HAGCR(_hoops_SPHHS alter &f, int _hoops_CPPCP, int _hoops_HCPSR, int _hoops_CRRAR)
{
	f._hoops_HAGR.number = 0;							
	f._hoops_HAGR._hoops_CAGCR._hoops_RCGCR = 0x8000;				
	f._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = _hoops_CPPCP;					
	f._hoops_HGRCR.number = 0;							
	f._hoops_HGRCR._hoops_CAGCR._hoops_RCGCR = 0;					
	f._hoops_HGRCR._hoops_CAGCR._hoops_SAGCR = (_hoops_HCPSR) - (_hoops_CPPCP);		
	switch (_hoops_CRRAR) {								
		case 0: break;							
		case 1: break;							
		case 2: f._hoops_HGRCR.number >>= 1; break;	
		case 3: f._hoops_HGRCR.number /=  3; break;	
		case 4: f._hoops_HGRCR.number >>= 2; break;	
		case 5: f._hoops_HGRCR.number /=  5; break;	
		case 6: f._hoops_HGRCR.number /=  6; break;	
		case 7: f._hoops_HGRCR.number /=  7; break;	
		case 8: f._hoops_HGRCR.number >>= 3; break;	
		default: f._hoops_HGRCR.number /= (int)_hoops_CRRAR;
	}
} 

INLINE void _hoops_HAGCR(_hoops_GRGCR alter &f, int _hoops_CPPCP, int _hoops_HCPSR, int _hoops_CRRAR)
{
	f._hoops_HAGR.number = 0;							
	f._hoops_HAGR._hoops_CAGCR._hoops_RCGCR = 0x8000;				
	f._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = _hoops_CPPCP;					
	f._hoops_HGRCR.number = 0;							
	f._hoops_HGRCR._hoops_CAGCR._hoops_RCGCR = 0;					
	f._hoops_HGRCR._hoops_CAGCR._hoops_SAGCR = (_hoops_HCPSR) - (_hoops_CPPCP);		
	switch (_hoops_CRRAR) {								
		case 0: break;							
		case 1: break;							
		case 2: f._hoops_HGRCR.number >>= 1; break;	
		case 3: f._hoops_HGRCR.number /=  3; break;	
		case 4: f._hoops_HGRCR.number >>= 2; break;	
		case 5: f._hoops_HGRCR.number /=  5; break;	
		case 6: f._hoops_HGRCR.number /=  6; break;	
		case 7: f._hoops_HGRCR.number /=  7; break;	
		case 8: f._hoops_HGRCR.number >>= 3; break;	
		default: f._hoops_HGRCR.number /= (int)_hoops_CRRAR;
	}
} 

#define _hoops_GHHHS(s, d)						\
	(d)._hoops_HAGR.number		   = (s)._hoops_HAGR.number;	\
	(d)._hoops_HGRCR.number	   = (s)._hoops_HGRCR.number;

#define _hoops_RPGCR(f)							\
	f._hoops_HAGR.number += f._hoops_HGRCR.number

#define _hoops_RHHHS(f,n)							\
	f._hoops_HAGR.number += f._hoops_HGRCR.number * (n)

#define _hoops_PPGCR(f)				\
	f._hoops_HAGR.number += f._hoops_HGRCR.number / 2




struct _hoops_AHHHS {
	float				_hoops_HAGR;
	float				_hoops_HGRCR;
};

#define _hoops_PHHHS(f, _hoops_CPPCP, _hoops_HCPSR, _hoops_CRRAR)				\
	f._hoops_HAGR = _hoops_CPPCP;									\
	f._hoops_HGRCR = (_hoops_HCPSR) - (_hoops_CPPCP);						\
	if (_hoops_CRRAR != 0 && _hoops_CRRAR != 1)						\
		f._hoops_HGRCR /= (float)_hoops_CRRAR;

#define _hoops_HHHHS(s, d)						\
	(d)._hoops_HAGR				   = (s)._hoops_HAGR;			\
	(d)._hoops_HGRCR			   = (s)._hoops_HGRCR;

#define _hoops_IHHHS(f)							\
	f._hoops_HAGR += f._hoops_HGRCR

#define _hoops_CHHHS(f,n)							\
	f._hoops_HAGR += f._hoops_HGRCR * (n)

#define _hoops_SHHHS(f)				\
	f._hoops_HAGR += 0.5f * f._hoops_HGRCR




struct _hoops_RSGCR {
	struct {
		Integer32	_hoops_SAGCR;
		Integer32	_hoops_RCGCR;
		float			simple;
	} _hoops_HAGR;
	struct {
		struct {
			Integer32		_hoops_SAGCR;
			Integer32		_hoops_RCGCR;
		} _hoops_RSHPH, _hoops_GIHHS; /* _hoops_AAHRP, _hoops_SIISR */
		float			simple;
	} _hoops_HGRCR;
};

INLINE void _hoops_IAGCR(_hoops_RSGCR alter &b, int _hoops_CPPCP, int _hoops_HCPSR, int _hoops_CRRAR)									
{	
	int _hoops_HGGRH = _hoops_HCPSR - _hoops_CPPCP;
	int	delta = _hoops_CRRAR ? _hoops_CRRAR : 1;					
	b._hoops_HAGR.simple = _hoops_CPPCP + 0.5f;											
	b._hoops_HGRCR.simple = (float)_hoops_HGGRH / (float)delta;						
	//_hoops_RIHHS (_hoops_AIHHS, _hoops_ISGSP, _hoops_RCSR._hoops_PIHHS._hoops_HIHHS._hoops_HHIPR, _hoops_RCSR._hoops_PIHHS._hoops_HIHHS._hoops_IRASR);
	b._hoops_HGRCR._hoops_RSHPH._hoops_SAGCR = _hoops_HGGRH / delta;
	b._hoops_HGRCR._hoops_RSHPH._hoops_RCGCR = _hoops_HGGRH % delta;
	if (_hoops_HGGRH < 0) {														
		b._hoops_HGRCR._hoops_RSHPH._hoops_RCGCR = -(b._hoops_HGRCR._hoops_RSHPH._hoops_RCGCR << 1);			
		b._hoops_HGRCR._hoops_GIHHS._hoops_SAGCR	 = b._hoops_HGRCR._hoops_RSHPH._hoops_SAGCR - 1;					
	}																	
	else {																
		b._hoops_HGRCR._hoops_RSHPH._hoops_RCGCR = b._hoops_HGRCR._hoops_RSHPH._hoops_RCGCR << 1;				
		b._hoops_HGRCR._hoops_GIHHS._hoops_SAGCR	 = b._hoops_HGRCR._hoops_RSHPH._hoops_SAGCR + 1;					
	}																	
	b._hoops_HGRCR._hoops_GIHHS._hoops_RCGCR = b._hoops_HGRCR._hoops_RSHPH._hoops_RCGCR - (delta << 1);		
	b._hoops_HAGR._hoops_SAGCR = _hoops_CPPCP;													
	b._hoops_HAGR._hoops_RCGCR = b._hoops_HGRCR._hoops_RSHPH._hoops_RCGCR - delta; 
}


#define _hoops_IIHHS(s, d)							\
	(d)._hoops_HAGR._hoops_SAGCR		   	= (s)._hoops_HAGR._hoops_SAGCR;			\
	(d)._hoops_HAGR._hoops_RCGCR	   	= (s)._hoops_HAGR._hoops_RCGCR;			\
	(d)._hoops_HAGR.simple		   	= (s)._hoops_HAGR.simple;			\
	(d)._hoops_HGRCR._hoops_RSHPH._hoops_SAGCR  	= (s)._hoops_HGRCR._hoops_RSHPH._hoops_SAGCR;	\
	(d)._hoops_HGRCR._hoops_RSHPH._hoops_RCGCR 	= (s)._hoops_HGRCR._hoops_RSHPH._hoops_RCGCR;	\
	(d)._hoops_HGRCR._hoops_GIHHS._hoops_SAGCR  	= (s)._hoops_HGRCR._hoops_GIHHS._hoops_SAGCR;	\
	(d)._hoops_HGRCR._hoops_GIHHS._hoops_RCGCR 	= (s)._hoops_HGRCR._hoops_GIHHS._hoops_RCGCR;	\
	(d)._hoops_HGRCR.simple		= (s)._hoops_HGRCR.simple;

#define _hoops_APGCR(b)												\
	b._hoops_HAGR.simple += b._hoops_HGRCR.simple;										\
	if (b._hoops_HAGR._hoops_RCGCR >= 0) {b._hoops_HAGR._hoops_SAGCR	 += b._hoops_HGRCR._hoops_GIHHS._hoops_SAGCR;	\
							  b._hoops_HAGR._hoops_RCGCR += b._hoops_HGRCR._hoops_GIHHS._hoops_RCGCR;}	\
	else					 {b._hoops_HAGR._hoops_SAGCR	 += b._hoops_HGRCR._hoops_RSHPH._hoops_SAGCR;	\
							  b._hoops_HAGR._hoops_RCGCR += b._hoops_HGRCR._hoops_RSHPH._hoops_RCGCR;}

#define _hoops_CIHHS(b,n) do {	\
		int _n_ = (n);		\
		while (_n_-- > 0) {			\
			_hoops_APGCR (b);	\
		}							\
	} while (0)

#define _hoops_SIHHS(b)											\
	b._hoops_HAGR.simple += 0.5f * b._hoops_HGRCR.simple;							\
	if (b._hoops_HAGR._hoops_RCGCR >= 0) {b._hoops_HAGR._hoops_SAGCR	 += b._hoops_HGRCR._hoops_GIHHS._hoops_SAGCR/2;	\
							  b._hoops_HAGR._hoops_RCGCR += b._hoops_HGRCR._hoops_GIHHS._hoops_RCGCR/2;}\
	else					 {b._hoops_HAGR._hoops_SAGCR	 += b._hoops_HGRCR._hoops_RSHPH._hoops_SAGCR/2;	\
							  b._hoops_HAGR._hoops_RCGCR += b._hoops_HGRCR._hoops_RSHPH._hoops_RCGCR/2;}



/*
 * _hoops_IRS _hoops_PRCGH _hoops_IICAA _hoops_HRGR _hoops_PCCP _hoops_ISHA _hoops_IIGR _hoops_HSPRA,
 * _hoops_PPR _hoops_SPHCP _hoops_ICGI _hoops_HCR _hoops_IHIA _hoops_GCHHS
 */
#define _hoops_GSPGS 64

struct _hoops_ISGCR {
	int							_hoops_CRRAR;				/* _hoops_APPS _hoops_IIGR _hoops_RH _hoops_PPAP, _hoops_GGR _hoops_ASPA, _hoops_ACCHA 1 */

	_hoops_SPHHS		x;				/* _hoops_IRGGA _hoops_AHC */
	_hoops_SPHHS		y;				/* _hoops_IRPHR _hoops_AHC */

	_hoops_RSGCR	bx;				/* _hoops_PAH _hoops_HIISR _hoops_CCA _hoops_RCHHS _hoops_PCRR */
	_hoops_RSGCR	bz;				/* _hoops_HCH (32 _hoops_SIH _hoops_PAR _hoops_CRGP) */

	_hoops_SPHHS		r;				/* _hoops_HAIR _hoops_PRRRA */
	_hoops_SPHHS		g;				/* _hoops_HAIR _hoops_ASSAA */
	_hoops_SPHHS		b;				/* _hoops_HAIR _hoops_HRRRA */

	/* _hoops_CPS _hoops_CAPP _hoops_IH _hoops_RAHCP _hoops_PPR/_hoops_PAR _hoops_AI, _hoops_IGGA _hoops_ISPAA _hoops_GHCA _hoops_SHH _hoops_GPRI _hoops_PAR _hoops_HAR */
	_hoops_AHHHS		_hoops_SIGA;				/* _hoops_SAPS _hoops_PPSR _hoops_PRRRA */
	_hoops_AHHHS		_hoops_SHRIC;				/* _hoops_SAPS _hoops_PPSR _hoops_ASSAA */
	_hoops_AHHHS		_hoops_PPGGS;				/* _hoops_SAPS _hoops_PPSR _hoops_HRRRA */

	_hoops_AHHHS		_hoops_IPAIA;				/* _hoops_IPPA _hoops_IRS */
	_hoops_AHHHS		_hoops_CPAIA;				/* _hoops_IPPA _hoops_RCSR */
	_hoops_AHHHS		_hoops_HSPIR;				/* _hoops_IPPA _hoops_GSGGR */
	_hoops_AHHHS		_hoops_RGHGS;				/* _hoops_IPPA _hoops_GHGP */


	_hoops_SPHHS		_hoops_ISAHH;
	_hoops_SPHHS		_hoops_APCGH;


	_hoops_AHHHS		_hoops_PGHGS;				/* _hoops_GSSP _hoops_SISR */
	_hoops_AHHHS		_hoops_HGHGS;				/* _hoops_GSSP _hoops_HAPC */
	_hoops_AHHHS		_hoops_IGHGS;				/* _hoops_GSSP _hoops_SSH */

	_hoops_AHHHS		_hoops_ACHHS;			/* _hoops_AIHP _hoops_GGSP _hoops_PCHHS _hoops_SISR */
	_hoops_AHHHS		_hoops_HCHHS;			/* _hoops_AIHP _hoops_GGSP _hoops_PCHHS _hoops_HAPC */
	_hoops_AHHHS		_hoops_ICHHS;			/* _hoops_AIHP _hoops_GGSP _hoops_PCHHS _hoops_SSH */
	float						_hoops_CCHHS, _hoops_SCHHS, _hoops_GSHHS;	/* _hoops_AIHP _hoops_GGSP _hoops_HSPP _hoops_HSH */

	int							param_width;
	_hoops_AHHHS		param[_hoops_GSPGS];			/* _hoops_RHPC */
	_hoops_AHHHS		_hoops_RSHHS[_hoops_GSPGS];		/* _hoops_AIHP _hoops_GGSP _hoops_ASHHS */
	float						_hoops_PSHHS[_hoops_GSPGS];		/* _hoops_AIHP _hoops_GGSP _hoops_HSPP _hoops_HSH */

	_hoops_AHHHS		_hoops_HSHHS;	/* _hoops_ISHHS _hoops_GIGGR */
	_hoops_AHHHS		_hoops_CSHHS;	/* _hoops_AIHP _hoops_GGSP _hoops_PCHAS */
};


struct _hoops_IPGCR {
	int							_hoops_CRRAR;
	_hoops_SPHHS		x;				/* _hoops_IRGGA _hoops_AHC */
};

struct _hoops_SRGCR {
	int							_hoops_CRRAR;
	_hoops_SPHHS		x;				/* _hoops_IRGGA _hoops_AHC */
	_hoops_RSGCR	bz;				/* _hoops_HCH (32 _hoops_SIH _hoops_PAR _hoops_CRGP) */
};


/*
 * _hoops_SSHHS *_hoops_PIHA* _hoops_SHH _hoops_HPGR _hoops_CHGC 2
 */

#define _hoops_GGIHS 64


struct _hoops_AHISP {
	_hoops_ISGCR						left, right;

#define	_hoops_SSPGS		0x01
#define	_hoops_GGHGS		0x02
#define	_hoops_RGIHS	0x04	/* _hoops_PPR _hoops_HCR _hoops_IHIA _hoops_CIPH _hoops_PII _hoops_AGIHS & _hoops_CIAAR/_hoops_PGIHS */
#define	_hoops_AGHGS		0x08	/* _hoops_PPR _hoops_HGIHS _hoops_RPP _hoops_IRPR */
	int							valid;
};


#define _hoops_HGGCR	unsigned char alter * alter *
#define _hoops_CSSIR	RGBAS32 alter * alter *
#define _hoops_SSSIR	_hoops_RAAH alter * alter *

End_HOOPS_Namespace;

#endif /* _hoops_IGIHS */
