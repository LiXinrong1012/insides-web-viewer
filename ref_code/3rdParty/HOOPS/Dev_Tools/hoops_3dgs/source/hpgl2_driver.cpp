/*
* Copyright (c) 2000 by Tech Soft 3D, LLC.
* The information contained herein is confidential and proprietary to
* Tech Soft 3D, LLC., and considered a trade secret as defined under
* civil and criminal statutes.	Tech Soft 3D shall pursue its civil
* and criminal remedies in the event of unauthorized use or misappropriation
* of its trade secrets.	 Use of this information by anyone other than
* authorized employees of Tech Soft 3D, LLC. is granted only under a
* written non-disclosure agreement, expressly prescribing the scope and
* manner of such use.
*
* $Id: obf_tmp.txt 1.73 2010-08-03 23:51:11 jason Exp $
*/

/*
 _hoops_CACRI _hoops_GARPH
 _hoops_HPPC 1.1 _hoops_SACRI _hoops_PHAA _hoops_PPGGR _hoops_GPCRI _hoops_HPP
	   _hoops_RPCRI _hoops_APCRI _hoops_PPCRI, _hoops_CHHRA._hoops_HPCRI._hoops_HIHRH
	   _hoops_IPCRI, _hoops_CPCRI, _hoops_SPCRI; _hoops_GHCRI: 310-326-2864
*/


#include "hoops.h"
#include "hd_proto.h"


/* _hoops_IPCP _hoops_HSPR _hoops_III _hoops_RCGPA _hoops_PSAP _hoops_RISRP _hoops_IIGR _hoops_PPSCP _hoops_CSCR _hoops_PIH.
*/
/* #_hoops_PPIP _hoops_RHCRI */


#ifndef HPGL2_DRIVER

extern "C"  bool HC_CDECL HD_HPGL2_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "hpgl2");
}

#else

#include "database.h"
#include "driver.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "searchh.h"
#include "hversion.h"
#include <stdio.h>

#if 0
#define _hoops_AHCRI(_hoops_PHCRI) printf("%s\n", _hoops_PHCRI)
#else
#define _hoops_AHCRI(_hoops_PHCRI)
#endif



/*_hoops_IISH _hoops_PISH _hoops_RHPP _hoops_HCSP _hoops_SIH
*/
#define _hoops_HHCRI		1
#define _hoops_IHCRI	2

/* _hoops_RRIA _hoops_CSIIR
*/
#define _hoops_CHCRI			1024
#define _hoops_SHCRI			1024

/* _hoops_GICRI _hoops_AGAH _hoops_RPPS _hoops_ASPA _hoops_HRGR 32767.
*  _hoops_SGPR _hoops_CRGP _hoops_ARI _hoops_IS _hoops_RICRI _hoops_HHH _hoops_SPGS.
*/
#define _hoops_AICRI			32000
#define _hoops_PICRI					256
#define _hoops_HICRI				(_hoops_PICRI + 1)


/* _hoops_IICRI _hoops_CSCR _hoops_CSSC
*/
#define _hoops_CICRI					0
#define _hoops_SICRI				1
#define _hoops_GCCRI				2

/* _hoops_IICRI _hoops_CGAS-_hoops_IHCRH _hoops_HSAGA
*/
#define _hoops_RCCRI			0
#define _hoops_ACCRI				1
#define _hoops_PCCRI				2

/* _hoops_IICRI _hoops_IHAH _hoops_GRPAR
* _hoops_AIHH _hoops_HCCRI()
*/
#define _hoops_ICCRI		 512000	 /* _hoops_GCSRR  */
#define _hoops_CCCRI 20		 /* _hoops_ASPA */

/* _hoops_SAPRR _hoops_PAPR _hoops_A
*/
#define _hoops_SCCRI					 2.54
#define MAX_COLORS 256
/*
 * _hoops_ISGSR _hoops_PAH _hoops_RSPC _hoops_CSGSR _hoops_PIH
 */
struct _hoops_SSGSR {
	unsigned char _hoops_GGRSR;
	struct {
            unsigned char r, g, b, number;
	} pen[MAX_COLORS];
};

/*
* _hoops_PIAP _hoops_PIH _hoops_SGS _hoops_RHGSR _hoops_HCPH _hoops_IS _hoops_RH _hoops_SRAC _hoops_SICAR
*/

struct _hoops_GSCRI {
	unsigned int r, g, b;
	bool defined; /* _hoops_IHPR _hoops_RPP _hoops_AIHSR _hoops_HSH _hoops_CHR _hoops_PAPR _hoops_GGR _hoops_SPSIR _hoops_HAIR _hoops_ARCR */
	bool set;		/* _hoops_IHPR _hoops_RPP _hoops_CSGSR _hoops_HAIR _hoops_SSCP _hoops_RPII _hoops_ARP _hoops_CCA _hoops_SACRI _hoops_RHASR */
};

struct _hoops_RSCRI {
	long left, right, top, bottom;
};

struct _hoops_ASCRI {
	FILE *				_hoops_PSCRI;

	bool				_hoops_HSCRI,
						_hoops_ISCRI,
						_hoops_CSCRI,
						_hoops_SSCRI,
						_hoops_GGSRI;

	long				_hoops_HAP,
						_hoops_RGSRI,
						_hoops_AGSRI,
						_hoops_PGSRI,
						_hoops_HGSRI,
						_hoops_IGSRI;

	Int_Rectangle	_hoops_CGSRI;

	float				_hoops_SGSRI,
						_hoops_GRSRI;

	struct _hoops_GSCRI		pen[(_hoops_PICRI + 1)];
        _hoops_SSGSR      const * _hoops_SARSR;

	_hoops_GARSR		_hoops_RRSRI;

	_hoops_ISC		_hoops_ARSRI;

	_hoops_GARRR		_hoops_PRSRI;

	int					_hoops_PIHSR,
						_hoops_HRSRI,
						_hoops_IRSRI,
						_hoops_CRSRI,
						_hoops_SRSRI,
						_hoops_GASRI,
						_hoops_RASRI,
						_hoops_AASRI,
						_hoops_PASRI,
						_hoops_HASRI,
						_hoops_IASRI;

	/* _hoops_PIAH _hoops_PPSCP _hoops_CASRI */
	char				*_hoops_SASRI;
	long				_hoops_GPSRI;
	int					_hoops_RPSRI,
						_hoops_APSRI,
						_hoops_PPSRI,
						_hoops_HPSRI;
	_hoops_GARRR		_hoops_IPSRI;
	Int_Rectangle	_hoops_CPSRI,
						_hoops_SPSRI,
						_hoops_GHSRI;
	unsigned char		*_hoops_RPHGH,
						*_hoops_RHSRI;
	long				_hoops_AHSRI;
};



/*
* _hoops_PHSRI _hoops_IS _hoops_ARP _hoops_GH _hoops_PIAP _hoops_CICRR
*/
#define _hoops_HHSRI(dc)	((_hoops_ASCRI alter *)(dc)->data)
#define _hoops_IHSRI(nr)	((_hoops_ASCRI alter *)(nr)->_hoops_SRA->data)







/*
* _hoops_PGAA
*/
local void _hoops_CHSRI(void) {
	HE_ERROR (HEC_HPGL2_DRIVER, HES_WRITE_FAILED,
	"Can't write data to file");
}


#if (0)	 /* _hoops_SGPR _hoops_RIGR _hoops_CSPP, _hoops_HSPR, _hoops_IH _hoops_ACHPR. */
/*
* _hoops_PGAA
*/
local void _hoops_SHSRI (
	_hoops_ASCRI alter	*state,
	char const			*data) {

	if ((fputs (data, state->_hoops_PSCRI) == -1))
		_hoops_CHSRI();
}

/*
* _hoops_PGAA
*/
local void _hoops_GISRI (
	_hoops_ASCRI alter	*state,
	char const			*data,
	long				count) {

	if (fwrite(data, sizeof(char),(size_t)count, state->_hoops_PSCRI) != count)
		_hoops_CHSRI();
}
#endif

/* _hoops_RISRI _hoops_IRSP _hoops_IIGR _hoops_AISRI _hoops_PSCH.
*/
#define _hoops_SHSRI(x,y) {if ((fputs ((y), (x)->_hoops_PSCRI) == -1))\
	{_hoops_CHSRI();}}

#define _hoops_GISRI(x,y,z) {if (fwrite((y), sizeof(char),\
	(size_t)(z), (x)->_hoops_PSCRI) != (size_t)(z)) {_hoops_CHSRI();}}


/*
* _hoops_PGAA
*/
local void _hoops_PISRI (
	_hoops_ASCRI alter	*state) {

	/* _hoops_HAIA _hoops_AGSHA _hoops_GA'_hoops_RA _hoops_ACRAA _hoops_HISRI _hoops_PRAR _hoops_GAPA
	* _hoops_IISRI _hoops_PPR _hoops_SACRI _hoops_CAPRR, _hoops_CCA _hoops_RH _hoops_GHPP _hoops_SGS _hoops_RH _hoops_PHI
	* _hoops_IIGR _hoops_CISRI _hoops_GGR _hoops_RH _hoops_IHCRH _hoops_PIHA _hoops_SHH _hoops_HIAP _hoops_RAS _hoops_SIGSP
	* _hoops_CAPRR. _hoops_HGI _hoops_API _hoops_ARH _hoops_RH _hoops_PHI _hoops_IIGR
	* _hoops_SACRI _hoops_CISRI _hoops_IS 256.
	*/
	_hoops_SHSRI(state,"NP256");
	state->_hoops_HRSRI = 256;

	/* _hoops_IPCP _hoops_ARRS _hoops_IRGAA _hoops_PAH _hoops_HIAP _hoops_CSGSR _hoops_SISRI.
	* _hoops_PHGP _hoops_ARI _hoops_SR _hoops_HHSA _hoops_IRS _hoops_HIAP _hoops_IIGR _hoops_III _hoops_HHRP _hoops_ARPP _hoops_HIRAA
	* _hoops_RH _hoops_SPS _hoops_RASIR. _hoops_HSRR _hoops_RGR _hoops_IS _hoops_IPHR, _hoops_SR _hoops_PIHA _hoops_ARP _hoops_HAIR,
	* _hoops_PGAP _hoops_SIAS _hoops_AASA _hoops_RGR _hoops_API, _hoops_ARPP _hoops_IPAC _hoops_PPR
	* _hoops_HIRAA _hoops_III _hoops_HHRP, _hoops_GGR _hoops_RH _hoops_RASIR _hoops_PGSA _hoops_PGSI.
	* _hoops_GCSRI() _hoops_GRS _hoops_RPGSA _hoops_HS _hoops_AIAH _hoops_HS
	* _hoops_ARP _hoops_RCSRI _hoops_IS -1, _hoops_HIH _hoops_RH _hoops_AGR _hoops_ACSRI
	* _hoops_ARI _hoops_HRGR _hoops_SAPIA.
	*/
	state->_hoops_IRSRI = -1;
}

local void _hoops_PCSRI(_hoops_ASCRI * state, int const pen, int & r, int & g, int & b)
{
    _hoops_SSGSR const * _hoops_SARSR = state->_hoops_SARSR;
    if(!_hoops_SARSR){
        return;
    }

    for(int i = 0; i < _hoops_SARSR->_hoops_GGRSR; ++i){
        if( pen == _hoops_SARSR->pen[i].number ){
            r = _hoops_SARSR->pen[i].r;
            g = _hoops_SARSR->pen[i].g;
            b = _hoops_SARSR->pen[i].b;
            return;
        }
    }
}

local int _hoops_HCSRI(_hoops_ASCRI * state, int const r, int const g, int const b)
{
    _hoops_SSGSR const * _hoops_SARSR = state->_hoops_SARSR;
    if(!_hoops_SARSR)
        return -1;

    float _hoops_PSIHA = 444; /* _hoops_ICSRI(_hoops_AGGIR(3*256^2)) _hoops_HAPCA _hoops_CCSRI(256*_hoops_AGGIR(3)) */
    int pen = 0;

    for(int i = 0; i < _hoops_SARSR->_hoops_GGRSR; ++i){

        int const _hoops_HIHHA = _hoops_SARSR->pen[i].r - r;
        int const _hoops_SCSRI = _hoops_SARSR->pen[i].g - g;
        int const _hoops_IHHI = _hoops_SARSR->pen[i].b - b;

        float const _hoops_CGSIR = _hoops_SGIHR((float)(_hoops_HIHHA*_hoops_HIHHA + _hoops_SCSRI*_hoops_SCSRI + _hoops_IHHI*_hoops_IHHI));
        if( _hoops_CGSIR < _hoops_PSIHA){
            pen = _hoops_SARSR->pen[i].number;
            _hoops_PSIHA = _hoops_CGSIR;
        }
    }
    return pen;
}

local int _hoops_HCSRI(_hoops_ASCRI * state, int const index)
{
    if(state->_hoops_SARSR){
        int const r = state->pen[index].r;
        int const g = state->pen[index].g;
        int const b = state->pen[index].b;
        return _hoops_HCSRI(state, r, g, b);
    }
    return index-1;
}

/*
* _hoops_PGAA
*/
local void _hoops_GSSRI (
	_hoops_ASCRI alter	*state,
	_hoops_GARSR		index,
	bool			_hoops_RSSRI) {

	char				string1[64];
	char				string2[64];
	char				_hoops_ASSRI[128];
	int r, g, b;

	r = state->pen[index].r;
	g = state->pen[index].g;
	b = state->pen[index].b;

        int const _hoops_PSSRI = _hoops_HCSRI(state, index);
        _hoops_PCSRI(state, _hoops_PSSRI, r, g, b);

	/* _hoops_SACRI _hoops_GRS _hoops_HSSRI _hoops_PGS (_hoops_PCCIR,_hoops_ISHI,_hoops_RCSR = 255,255,255) _hoops_GAR
	* _hoops_RRH _hoops_RPP _hoops_RH _hoops_IHSP _hoops_HRGR _hoops_ARP _hoops_GPP (_hoops_ISSRI _hoops_IRGAA)
	* _hoops_PAR _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_IGI _hoops_GAR _hoops_RH _hoops_CSSRI _hoops_GGR _hoops_HSP _hoops_PAIA.
	* _hoops_HGI _hoops_GRS _hoops_GGHC _hoops_PGS _hoops_SSSRI _hoops_IS _hoops_HAR _hoops_IIIAA _hoops_RH
	* _hoops_HSSSH _hoops_SSSRI. _hoops_PHGP, _hoops_SR _hoops_ISPR _hoops_IH _hoops_PGS _hoops_ARI,
	* _hoops_PPR _hoops_GGGAI _hoops_PGS _hoops_HIS _hoops_SGS _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_GPCPR _hoops_PGS,
	* _hoops_HIH _hoops_HHSH (1 _hoops_ARIP _hoops_RGGAI), _hoops_GGR _hoops_AGR _hoops_IS _hoops_AGGAI _hoops_SGS
	* _hoops_PGS _hoops_GRS _hoops_SHR _hoops_SHH _hoops_CIGC.
	*/
	if ((r == 255) && (g == 255) && (b == 255)) b = 254;

	if (_hoops_RSSRI) {
		/*
		* _hoops_IISRI _hoops_CCH
		*/

		/* _hoops_PAGA: _hoops_IH _hoops_IISRI _hoops_CCH, _hoops_SR _hoops_PGGAI _hoops_PHI _hoops_IIGR _hoops_CISRI _hoops_HRGR
		* _hoops_ARP _hoops_HPP _hoops_ACCRH _hoops_AARSP _hoops_HSCAR _hoops_IRGAA _hoops_GGR _hoops_HGGAI() _hoops_PAR
		* _hoops_GCIAA _hoops_CCA _hoops_IHCRH _hoops_HII _hoops_SACRI _hoops_CCH
		*/

		Sprintf_DD(string1, "\033*v%da%db", r, g);
		Sprintf_DD(string2, "%dc%dI", b, ((index > 0) ? index : 0));
		Sprintf_SS(_hoops_ASSRI, "%s%s", string1, string2);
		_hoops_SHSRI(state, _hoops_ASSRI);
		state->pen[index].set = true;
	}
	else {
		/*
		* _hoops_IGGAI _hoops_CCH
		*/
		if (state->_hoops_HSCRI) {
			_hoops_SHSRI(state, ";");
			state->_hoops_HSCRI = false;
		}

		if (state->_hoops_HRSRI != 256) _hoops_PISRI(state);

		Sprintf_DD(string1, "PC%d,%d,", _hoops_PSSRI, r);
		Sprintf_DD(string2, "%d,%d", g, b);
		Sprintf_SS(_hoops_ASSRI, "%s%s", string1, string2);
		_hoops_SHSRI(state, _hoops_ASSRI);
		state->pen[index].set = true;
	}
}




/*
* _hoops_PGAA
*/
local void _hoops_CGGAI (
	_hoops_ASCRI alter	*state,
	_hoops_GARSR		index) {

	char				string[64];

	/*
	* _hoops_RHCCP _hoops_SSCP _hoops_AIAH _hoops_SGGAI _hoops_SGS _hoops_HAIR _hoops_SSCP
	* _hoops_HGAS, _hoops_PPR _hoops_HIS _hoops_CCAH _hoops_HAIR _hoops_IRGAA _hoops_PIHA _hoops_SHH _hoops_AHSHH.
	*/

	if (state->_hoops_HSCRI) {
		_hoops_SHSRI(state, ";");
		state->_hoops_HSCRI = false;
	}

	/*
	* _hoops_ARGH _hoops_IH _hoops_APIP _hoops_PPR _hoops_PAPR _hoops_CIHA
	*/
	if ((index > _hoops_PICRI) ||
		(state->pen[index].defined != true)) {

		/* _hoops_ARP _hoops_IS _hoops_APRP _hoops_RPP _hoops_HAR _hoops_IRS _hoops_APIP _hoops_PAR _hoops_HAR _hoops_IRS _hoops_PAPR _hoops_CIHA */
		index = 0;

		/*
		* _hoops_CGP _hoops_CSGSR 0 _hoops_HRGR _hoops_HAR _hoops_APRP, _hoops_GGGAI _hoops_IS _hoops_APRP
		* _hoops_PPR _hoops_IPPRA _hoops_IS _hoops_HHSA _hoops_HIAP _hoops_CAPP.
		*/
		if ((state->pen[0].r != 0) ||
			(state->pen[0].g != 0) ||
			(state->pen[0].b != 0) ||
			!(state->pen[0].defined)) {

			state->pen[0].r = 0;
			state->pen[0].g = 0;
			state->pen[0].b = 0;
			state->pen[0].defined = true;
			state->pen[0].set = false;
		}
	}

	/*
	* _hoops_CGP _hoops_CSGSR _hoops_SSCP _hoops_HAR _hoops_RPII _hoops_ARP _hoops_HPGR _hoops_GRGAI _hoops_GGR _hoops_SACRI, _hoops_AA _hoops_HIS.
	*/
	if (state->pen[index].set != true) {
		_hoops_GSSRI(state, index, false);
	}

	/* _hoops_ISGP _hoops_RRGAI _hoops_GRP _hoops_RH _hoops_CCAH _hoops_CIHA.
	*/
        int const _hoops_PSSRI = _hoops_HCSRI(state, index);
	Sprintf_D(string, "SP%d", _hoops_PSSRI);
	_hoops_SHSRI(state, string);

	/*
	* _hoops_RSCS _hoops_SCGR _hoops_HAIR _hoops_RGSR _hoops_GGR _hoops_PIAP.
	*/
	state->_hoops_RRSRI = index;
	state->_hoops_ARSRI.r = state->pen[index].r;
	state->_hoops_ARSRI.g = state->pen[index].g;
	state->_hoops_ARSRI.b = state->pen[index].b;
}



/*
* _hoops_PGAA
*/
local void _hoops_ARGAI (
	_hoops_ASCRI alter	*state,
	_hoops_ISC const *color) {

	_hoops_GARSR		i, _hoops_PRGAI;


	/* _hoops_RHCCP _hoops_SSCP _hoops_AIAH _hoops_SGGAI _hoops_SGS _hoops_CCAH _hoops_AIHSR _hoops_HAIR _hoops_RHAP
	* _hoops_HAR _hoops_PSSP _hoops_CGHI _hoops_HAIR _hoops_AHSHH _hoops_IS _hoops_HRGAI.
	*/

	/*
	* _hoops_RAP _hoops_SHIR _hoops_ACHPP _hoops_CIHA.	_hoops_CGP _hoops_HAIR _hoops_ARCR _hoops_HRGR _hoops_IHIR, _hoops_PSCR _hoops_HCR
	* _hoops_CCAH _hoops_PSHA _hoops_RSGR _hoops_GH _hoops_HPGR _hoops_RH 0 _hoops_CIHA _hoops_GGR _hoops_RH _hoops_HAIR _hoops_ARCR.
	*/
	_hoops_PRGAI = 0;


	/* _hoops_ARGH _hoops_RPP _hoops_HAIR _hoops_SPASR _hoops_GII _hoops_IIGR _hoops_RH _hoops_PSHA _hoops_AIAH _hoops_PAPR
	* _hoops_GGR _hoops_RH _hoops_HAIR _hoops_ARCR
	*/
	for (i = 0; i <= _hoops_PICRI; i++) {
		if (state->pen[i].defined == true) {
			if ((state->pen[i].r == color->r) &&
				(state->pen[i].g == color->g) &&
				(state->pen[i].b == color->b)) break;
		}
		else {
			if (_hoops_PRGAI == 0) _hoops_PRGAI = i;
		}
	}

	if (i > _hoops_PICRI) {
		/*
		* _hoops_CSSGR _hoops_ASSP'_hoops_RA _hoops_PSSP _hoops_IRS _hoops_PAPR _hoops_CSGSR _hoops_HIS _hoops_PPIP _hoops_HA.
		*/
		i = _hoops_PRGAI;
		state->pen[i].r = color->r;
		state->pen[i].g = color->g;
		state->pen[i].b = color->b;
		state->pen[i].defined = true;
		state->pen[i].set = false;
	}

	/* _hoops_RHRPA _hoops_RGR _hoops_PPSR _hoops_SR _hoops_HS _hoops_GSGI _hoops_RH _hoops_AIHSR _hoops_HAIR _hoops_GGR _hoops_ISCP
	* _hoops_HAIR _hoops_ARCR, _hoops_PAR _hoops_SR _hoops_HS _hoops_IRGAI _hoops_HAIR 0 _hoops_IS _hoops_RH _hoops_CCAH
	* _hoops_AIHSR _hoops_HSH.
	*/

	_hoops_CGGAI(state, i);
}


/*
* _hoops_PGAA
*/
local void _hoops_CRGAI (
	_hoops_ASCRI alter	*state) {

	int					i;

	/* _hoops_AHHRR _hoops_CCPAR _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_RH _hoops_CSIIR
	* _hoops_SGS _hoops_SACRI _hoops_HRGR _hoops_GRP _hoops_IS _hoops_SRGAI _hoops_AAGA _hoops_GAGAI.
	* _hoops_HGI _hoops_API _hoops_HRSCA _hoops_AGCR _hoops_PIAP _hoops_CCPAR,
	* _hoops_HIS _hoops_SGS _hoops_RH _hoops_RHPP _hoops_GRS _hoops_HSPAA _hoops_SACRI _hoops_RHASR
	* _hoops_IS _hoops_ARP _hoops_RH _hoops_CSIIR.
	*/

	/* _hoops_RAP _hoops_HCR _hoops_CISRI _hoops_IS _hoops_IPPRA */
	for (i=0; i<=_hoops_PICRI; i++) state->pen[i].set = false;

	/* _hoops_GHRAA _hoops_AIRC _hoops_IS _hoops_IPPRA _hoops_AAIP.
	*/
	state->_hoops_RRSRI			= _hoops_HICRI;
	state->_hoops_IRSRI			= -1;
	state->_hoops_CRSRI			= -1;
	state->_hoops_SRSRI			= -1;
	state->_hoops_GASRI		= -1;
	state->_hoops_RASRI	= -1;
	state->_hoops_PASRI	= -1;
	state->_hoops_HRSRI		= -1;

	/* _hoops_RAP _hoops_SACRI _hoops_CSGSR _hoops_IS _hoops_CISS _hoops_IS _hoops_HHSA _hoops_SPS _hoops_PCRR
	* _hoops_IS _hoops_SHH _hoops_IPPSR, _hoops_HAR _hoops_CSCHR, _hoops_PCRR. */
	state->_hoops_CSCRI = true;
}



/*
* _hoops_PGAA
*/
local void _hoops_ACPSR (
	_hoops_ASCRI alter	*state,
	int					weight) {

	char				string[64];
	float				_hoops_RAGAI;


	/* _hoops_SIGP: _hoops_SACRI _hoops_AGSHA _hoops_AAGAI _hoops_HS _hoops_SPGC _hoops_ISHHH _hoops_PAGAI _hoops_CGPR
	* _hoops_III _hoops_HHRP _hoops_CHR _hoops_RISA. _hoops_HAGAI _hoops_ISPR _hoops_IH _hoops_RISA _hoops_III _hoops_HHRP
	* _hoops_ARI _hoops_PPR _hoops_RIP _hoops_IH _hoops_IAGAI _hoops_PHSPR _hoops_IIGR _hoops_PAGAI _hoops_GGGGR. */

	if (state->_hoops_HSCRI) {
		_hoops_SHSRI(state, ";");
		state->_hoops_HSCRI = false;
	}

	_hoops_RAGAI = (float)weight * (float)25.4 / (float)state->_hoops_HAP;
	_hoops_RAGAI += (float)(0.005); /* _hoops_AIAP _hoops_IS _hoops_GIRR _hoops_GH. */

	Sprintf_F(string,"PW%.2f", _hoops_RAGAI);
	_hoops_SHSRI(state, string);

	state->_hoops_IRSRI = weight;
}



/*
* _hoops_PGAA
*/
local void _hoops_CAGAI (
	_hoops_ASCRI alter	*state,
	int					style) {

	char				string1[16];
	char				string2[16];
	int					cap;
	int					_hoops_SAGAI;


	if (state->_hoops_HSCRI) {
		_hoops_SHSRI(state, ";");
		state->_hoops_HSCRI = false;
	}

	if (style < 1) style = 0;

	cap	 = style & LCAP_MASK;
	_hoops_SAGAI = style & LJOIN_MASK;

	string1[0] = '\0';
	if (cap != (state->_hoops_CRSRI & LCAP_MASK)) {
		switch (cap) {

			case LCAP_SQUARE:
				Sprintf_S(string1,"LA%s","1,2");
				break;

			case LCAP_ROUND:
				Sprintf_S(string1,"LA%s","1,4");
				break;

			case LCAP_BUTT:
			default:
				Sprintf_S(string1,"LA%s","1,1");
				break;
		}
	}

	if (_hoops_SAGAI != (state->_hoops_CRSRI & LJOIN_MASK)) {
		if (_hoops_SSGR(string1)) {
			Sprintf_S(string2, "%s,", string1);
		}
		else {
			Sprintf_S(string2, "%s", "LA");
		}

		switch (_hoops_SAGAI) {

			case LJOIN_BEVEL:
				Sprintf_S(string1,"%s2,5", string2);
				break;

			case LJOIN_ROUND:
				Sprintf_S(string1,"%s2,4", string2);
				break;

			case LJOIN_MITER:
			default:
				Sprintf_S(string1,"%s2,1", string2);
				break;
		}
	}

	_hoops_SHSRI(state, string1);
	state->_hoops_CRSRI = style;
}


/*
* _hoops_PAGA: _hoops_HGI _hoops_RHPP _hoops_RHAP _hoops_HAR _hoops_ARP _hoops_III _hoops_CSSC (_hoops_PGAP _hoops_CHARP _hoops_HCPH
* _hoops_III _hoops_PAIA) _hoops_GRP _hoops_RH _hoops_SACRI "_hoops_GPGAI" _hoops_IRGAA.
* _hoops_RPGAI, _hoops_SR _hoops_CAH _hoops_GRAA-_hoops_RPHSR _hoops_III _hoops_CSSC _hoops_ISSC _hoops_IS _hoops_APGAI, _hoops_HIS _hoops_SGS
* _hoops_APGAI _hoops_PAH _hoops_RGSHA _hoops_RH _hoops_III _hoops_HSGP _hoops_CSRA _hoops_IS _hoops_PCCP _hoops_IRPR
* _hoops_SPCC. _hoops_HGI _hoops_AHSGH _hoops_PAHP _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_PIH _hoops_RGHR
* _hoops_GAHPR _hoops_HIH _hoops_GRS _hoops_GSRS _hoops_RRI _hoops_PPGAI _hoops_ACPP.
*/


/*
* _hoops_PGAA
*/
local void _hoops_HPGAI (
	_hoops_ASCRI alter		*state,
	int						type) {

	char					string[64];

	/* _hoops_HGI _hoops_HICRR _hoops_ARH _hoops_SACRI _hoops_III _hoops_CSSC. _hoops_HHIGR _hoops_IIAH
	* _hoops_GGR _hoops_ISPAH _hoops_CCA _hoops_IPGAI() _hoops_PGGA _hoops_HHH
	* _hoops_HSP _hoops_PAIA _hoops_HGAP _hoops_SGS _hoops_SR _hoops_GACC _hoops_ARP _hoops_IRS _hoops_SASI _hoops_III _hoops_GPRR.
	*/



	if (state->_hoops_HSCRI) {
		_hoops_SHSRI(state, ";");
		state->_hoops_HSCRI = false;
	}

	switch (type) {
		case FP_SQUARE_DOTS:
			/* _hoops_III _hoops_GPRR _hoops_IGI _hoops_CCA _hoops_CPGAI _hoops_HSP _hoops_HSGP */
			/* _hoops_ARP _hoops_SPGAI _hoops_HSGP #1 _hoops_SPCC _hoops_GGR _hoops_GHGAI */
			Sprintf_D(string, "LT1,%d,1",
				state->_hoops_IASRI);
			_hoops_SHSRI(state, string);

		   break;

		case FP_CHECKERBOARD:
			/* _hoops_III _hoops_GPRR _hoops_IGI _hoops_CCA _hoops_RHGAI _hoops_HSP _hoops_HSGP */
			/* _hoops_ARP _hoops_AHGAI _hoops_HSGP #2 _hoops_SPCC _hoops_GGR _hoops_GHGAI */
			Sprintf_D(string, "LT2,%d,1",
				state->_hoops_IASRI);
			_hoops_SHSRI(state, string);

			break;

		case FP_SOLID:	/* 0 */
		default:
			_hoops_SHSRI(state, "LT");
			type = 0;
			break;
	}

	state->_hoops_SRSRI = type;
}


/*
* _hoops_PGAA
*/
local void _hoops_AHPSR (
	_hoops_ASCRI alter		*state,
	int						pattern) {

	char					string[64];
	long					_hoops_HHPCP;


	/*
	* _hoops_PHGAI _hoops_HSGP _hoops_HRGR _hoops_HAR _hoops_GPCPR _hoops_PII _hoops_PCPA _hoops_RH _hoops_IRISR _hoops_HHGAI
	* _hoops_CPPHR, _hoops_HIH _hoops_HRGR _hoops_HHASH _hoops_HII _hoops_HCR _hoops_HIASR.
	*/

	/* _hoops_PS _hoops_ARP _hoops_RH _hoops_HSP _hoops_III _hoops_GPRR _hoops_IS _hoops_PCPA _hoops_HRGR _hoops_SIGR _hoops_IH _hoops_RH
	* _hoops_PIASR _hoops_HSP _hoops_HSGP.	 _hoops_AIHH _hoops_IHGAI _hoops_IH _hoops_IPPHR
	* _hoops_IIGR _hoops_III _hoops_CSSC.
	*/

	if (state->_hoops_HSCRI) {
		_hoops_SHSRI(state, ";");
		state->_hoops_HSCRI = false;
	}

	/*
	* _hoops_RAP _hoops_SHIR _hoops_III _hoops_GPRR, _hoops_IAHA, _hoops_PPR _hoops_SGCR,
	* _hoops_ASC _hoops_CHR _hoops_HGAS _hoops_IH _hoops_PCHC _hoops_PAIA _hoops_CAPP.
	*/
	state->_hoops_RASRI = FP_SOLID;	/* 0 */
	state->_hoops_PASRI = LCAP_BUTT + LJOIN_MITER;
	state->_hoops_AASRI = /* _hoops_GGR _hoops_ASPA, 1/6 _hoops_IIGR _hoops_SGGGH */
		(state->_hoops_HASRI + 3) / 6;


	switch (pattern) {

		case FP_CHECKERBOARD:
		case FP_WINDOW_CHECKERBOARD:
			_hoops_HHPCP = state->_hoops_HASRI / 2;
			Sprintf_D(string,"FT3,%d,0", _hoops_HHPCP);
			_hoops_SHSRI(state, string);


			/* _hoops_SGCR _hoops_PIHA _hoops_SHH _hoops_CRGP _hoops_HSAR _hoops_SGGGH, _hoops_IAII _hoops_RHAC'_hoops_GCPP
			_hoops_HGCR _hoops_IRS _hoops_RPHSR _hoops_HSGP */
			state->_hoops_AASRI =
				(int)(_hoops_HHPCP * (long)7 / (long)8);
			state->_hoops_RASRI =
				FP_CHECKERBOARD;  /* _hoops_CHGAI _hoops_III */
			state->_hoops_PASRI =
				LCAP_BUTT + LJOIN_MITER;
			break;

		case FP_CROSSHATCH:
		case FP_WINDOW_CROSSHATCH:
			Sprintf_D(string, "FT4,%d,0", state->_hoops_HASRI);
			_hoops_SHSRI(state, string);
			break;

		case FP_HORIZONTAL_BARS:
		case FP_WINDOW_HORIZONTAL_BARS:
			Sprintf_D(string, "FT3,%d,0", state->_hoops_HASRI);
			_hoops_SHSRI(state, string);
			break;

		case FP_VERTICAL_BARS:
		case FP_WINDOW_VERTICAL_BARS:
			Sprintf_D(string, "FT3,%d,90", state->_hoops_HASRI);
			_hoops_SHSRI(state, string);
			break;

		case FP_SLANT_LEFT:
		case FP_WINDOW_SLANT_LEFT:
			Sprintf_D(string, "FT3,%d,135", state->_hoops_HASRI);
			_hoops_SHSRI(state, string);
			break;

		case FP_SLANT_RIGHT:
		case FP_WINDOW_SLANT_RIGHT:
			Sprintf_D(string, "FT3,%d,45", state->_hoops_HASRI);
			_hoops_SHSRI(state, string);
			break;

		case FP_SQUARE_DOTS:
		case FP_WINDOW_SQUARE_DOTS:
			/* _hoops_ARP _hoops_SGGGH _hoops_IS 1/2 _hoops_IIGR _hoops_GSSR, _hoops_PPR _hoops_ARP _hoops_IS 45 _hoops_ASIPR */
			_hoops_HHPCP = state->_hoops_HASRI / 2;
			Sprintf_D(string, "FT3,%d,45", _hoops_HHPCP);
			_hoops_SHSRI(state, string);
			state->_hoops_RASRI = FP_SQUARE_DOTS; /* _hoops_SHGAI _hoops_III */
			state->_hoops_PASRI = LCAP_ROUND + LJOIN_ROUND;

			break;

		case FP_DIAMONDS:
		case FP_WINDOW_DIAMONDS:
			Sprintf_D(string, "FT4,%d,45", state->_hoops_HASRI);
			_hoops_SHSRI(state, string);
			break;

		case FP_USER_DEFINED:
		case FP_SOLID:
		default:
			_hoops_SHSRI(state,"FT");
			break;
	}

	state->_hoops_GASRI = pattern;
}




/*
* _hoops_PGAA
*/
local void _hoops_GIGAI(
	_hoops_ASCRI alter	*state,
	long				*x,
	long				*y,
	DC_Point const	*point) {

        *x = (long)point->x;
        *y = (long)point->y;

	*x += state->_hoops_PGSRI;
	*y += state->_hoops_HGSRI;
}


/*
* _hoops_PGAA
*/
local void _hoops_RIGAI(
	_hoops_ASCRI alter	*state,
	long				X,
	long				Y) {

		static	long				m, n;
		static	char				*_hoops_RPPA;
	static	char				string[100];

	/* _hoops_AIGAI _hoops_IS _hoops_HSPAA _hoops_PIGAI _hoops_SPCR,_hoops_GHCR _hoops_PSAI
	* _hoops_GRP _hoops_SACRI _hoops_HIGAI _hoops_IRGAA _hoops_SPAHR _hoops_CCA _hoops_AIRA _hoops_IIGR 64.
	* _hoops_IIGAI _hoops_CHR _hoops_GGR _hoops_SACRI _hoops_AIR _hoops_PCRR.
	*
	* _hoops_CGP _hoops_PIAP->_hoops_CIGAI _hoops_HRGR _hoops_IHPR, _hoops_PSCR _hoops_PHSP _hoops_IH
	* _hoops_IPPSR _hoops_IHIS _hoops_PSHS _hoops_IS (0,0).  _hoops_CGP _hoops_RCPP, _hoops_PSCR _hoops_PHSP
	* _hoops_IH _hoops_CSCHR _hoops_IHIS _hoops_HII (_hoops_SIGAI, _hoops_GCGAI).
	*/

	if (state->_hoops_CSCRI) {
		state->_hoops_RGSRI = 0;
		state->_hoops_AGSRI = 0;
		_hoops_SHSRI(state,"=");
		state->_hoops_CSCRI = false;
	}

	if (X < state->_hoops_RGSRI) { /* _hoops_PSCR _hoops_HHHR _hoops_SPCR _hoops_IHIS */
				n = (long)(state->_hoops_RGSRI - X);
				n = n + n + 1;
	}
		else {
				n = (long)(X - state->_hoops_RGSRI);
				n = n + n;
		}

		_hoops_RPPA = string;

	while (n >= 64) {
			*_hoops_RPPA++ = ((char) (63 + (n & 63)));
			m = n >> 6;
			n = m;
	}

	*_hoops_RPPA++ = ((char) (191 + n));

		if (Y < state->_hoops_AGSRI) { /* _hoops_PSCR _hoops_HHHR _hoops_GHCR _hoops_IHIS */
				n = (long)(state->_hoops_AGSRI - Y);
				n = n + n + 1;
	}
		else {
				n = (long)(Y - state->_hoops_AGSRI);
				n = n + n;
		}

	while (n >= 64) {
		*_hoops_RPPA++ = ((char) (63 + (n & 63)));
			m = n >> 6;
			n = m;
	}

	*_hoops_RPPA++ = ((char) (191 + n));
	*_hoops_RPPA = '\0';

	_hoops_SHSRI(state, string);

	/* _hoops_ASAC _hoops_CCAH _hoops_ACAGR _hoops_IH _hoops_SPS _hoops_GHIR */
		state->_hoops_RGSRI = X;
	state->_hoops_AGSRI = Y;
}



/*
* _hoops_PGAA
*/
local bool _hoops_RCGAI (
	_hoops_ASCRI alter	*state,
	_hoops_HCRPR const		*name,
	char const			*delimiter) {

	char				*source; /* _hoops_HCGP _hoops_HSPP */
	char				*start; /* _hoops_ACGAI _hoops_HSPP */
	char				*end;	/* _hoops_ACGAI _hoops_RSGR */
	int					_hoops_PCGAI;	/* _hoops_HAIHH _hoops_SPCC */
	int					_hoops_HCGAI;	/* _hoops_HCGP _hoops_SPCC */
	int					i, j;

	/* _hoops_GSAH _hoops_IS _hoops_HSPAA _hoops_CISPP _hoops_PPR _hoops_RCPHR _hoops_RHIPP.
	* _hoops_ICGAI _hoops_HPS _hoops_HII _hoops_HCGP _hoops_SGS _hoops_CHR _hoops_IHAIA _hoops_HPP _hoops_RH
	* _hoops_HPS _hoops_GGR _hoops_RH _hoops_IRAP _hoops_CCGAI _hoops_GSGR "_hoops_HAIHH".
	* _hoops_HIPR _hoops_SHPH _hoops_SCGAI _hoops_IS \033 _hoops_ARPP _hoops_HIRAA.
	* _hoops_GCAAA _hoops_IHPR _hoops_RPP _hoops_ACGAI _hoops_HRGR _hoops_GSGI, _hoops_PAR _hoops_RCPP _hoops_RPP _hoops_HAR.
	*/


	/* _hoops_RAP _hoops_GH _hoops_HCGP _hoops_GSGR.
	*/
	source = name->text;
	_hoops_HCGAI   = name->length;

	/* _hoops_ARGH _hoops_GSGAI
	*/
	if (_hoops_HCGAI <= 0) return false;
	if (source == NULL) return false;
	if (delimiter == NULL) return false;
	_hoops_PCGAI = (int) _hoops_SSGR (delimiter);
	if (_hoops_PCGAI <= 0) return false;


	/* _hoops_ACGR _hoops_SRS _hoops_HAGAR _hoops_IIGR _hoops_HAIHH
	*/
	start = NULL;
	for (i=0; i<_hoops_HCGAI; i++) {
		for (j=0; ((j<_hoops_PCGAI) && (j+i<_hoops_HCGAI)); j++) {
			if (source[i+j] != delimiter[j]) break;
		}
		if (j >= _hoops_PCGAI) {
			/* _hoops_PGII _hoops_HPS _hoops_PSSP */
			start = source + i;
			break;
		}
	}
	if (start == NULL) return false;


	/* _hoops_ACGR _hoops_CGHI _hoops_HAGAR _hoops_IIGR _hoops_HAIHH
	*/
	end = NULL;
	for (i=_hoops_HCGAI-1; i>=0; i--) {
		for (j=0; ((j<_hoops_PCGAI) && (j+i<_hoops_HCGAI)); j++) {
			if (source[i+j] != delimiter[j]) break;
		}
		if (j >= _hoops_PCGAI) {
			/* _hoops_PGII _hoops_HPS _hoops_PSSP */
			end = source + i;
			break;
		}
	}
	if (end == NULL) return false;

	/* _hoops_ARGH _hoops_RPP _hoops_RGAR _hoops_SPR _hoops_HAIHH
	*/
	if (end == start) return false;


	/*
	* _hoops_RSGAI _hoops_ACGAI
	*/
	start = start + _hoops_PCGAI;
	_hoops_HCGAI = (int)(end - start);
	if (_hoops_HCGAI <= 0) return false;


	/* _hoops_RHRPA _hoops_RGR _hoops_PPSR, _hoops_SR _hoops_RRP _hoops_IS _hoops_HSPAA _hoops_ASGAI _hoops_HPS
	* _hoops_SGSH _hoops_GAR _hoops_HSPP. _hoops_ASGR _hoops_SCGAI _hoops_CCA \033
	*/
	j = 0;	/* _hoops_HPS _hoops_AIAH _hoops_AHSHH */

	for (i=0; i<=(_hoops_HCGAI - 3); i++) {
			if (start[i] == 'E' && start[i+1] == 'S' && start[i+2] == 'C') {
			/* _hoops_RHGAR _hoops_HPS _hoops_HAR _hoops_GAPR _hoops_AHSHH _hoops_PPR \033 */
			_hoops_GISRI(state, &start[j], i-j);
			_hoops_SHSRI(state,"\033");
			j = i + 3;
		}
	}
	if (j<_hoops_HCGAI) _hoops_GISRI(state, &start[j], _hoops_HCGAI-j);

	return true;
}


/*
* _hoops_PGAA
*/
local void _hoops_PCPSR (
	_hoops_ASCRI alter				*state,
	Int_Rectangle const			*_hoops_PSGAI,
	_hoops_GARRR const			_hoops_CPA) {

	DC_Point						_hoops_HSGAI;
	long							left, right, bottom, top;
	char							string1[64];
	char							string2[64];
	char							_hoops_ASSRI[128];

	/*
	* _hoops_RHCCP _hoops_GRS _hoops_HS _hoops_SGGAI _hoops_SGS _hoops_ISGAI'_hoops_GRI
	* _hoops_HSHR _hoops_SSCP _hoops_HGAS. _hoops_PHGP _hoops_SR _hoops_RRP _hoops_IS _hoops_HIAP _hoops_HSPH _hoops_RPPS.
	* _hoops_PAGA _hoops_SR _hoops_GGCR _hoops_SPR _hoops_AIR _hoops_IS _hoops_CCAC _hoops_HPGR _hoops_GRR _hoops_HGPC.
	*/


	/*
	* _hoops_RHGAR _hoops_HSPH _hoops_CSGAI _hoops_IRGAA _hoops_RPP _hoops_HSPH _hoops_PCSRR _hoops_HS _hoops_HGAS.
	*/
	if ((state->_hoops_CGSRI.right  != _hoops_PSGAI->right) ||
		(state->_hoops_CGSRI.left	  != _hoops_PSGAI->left)  ||
		(state->_hoops_CGSRI.top	  != _hoops_PSGAI->top)	  ||
		(state->_hoops_CGSRI.bottom != _hoops_PSGAI->bottom)) {

		/*
		* _hoops_SSGAI _hoops_RAAP
		*/
		_hoops_HSGAI.x = (float) _hoops_PSGAI->left	- 1;
		_hoops_HSGAI.y = (float) _hoops_PSGAI->bottom - 1;
		_hoops_GIGAI(state, &left, &bottom, &_hoops_HSGAI);

		/*
		* _hoops_GGRAI _hoops_RPHR
		*/
		_hoops_HSGAI.x = (float) _hoops_PSGAI->right	+ 1;
		_hoops_HSGAI.y = (float) _hoops_PSGAI->top	+ 1;
		_hoops_GIGAI(state, &right, &top, &_hoops_HSGAI);

		if (state->_hoops_HSCRI) {
			_hoops_SHSRI(state, ";");
			state->_hoops_HSCRI = false;
		}

		Sprintf_DD(string1, "%d,%d", left, bottom);
		Sprintf_DD(string2, "%d,%d", right, top);
		Sprintf_SS(_hoops_ASSRI, "IW%s,%s", string1, string2);
		_hoops_SHSRI(state, _hoops_ASSRI);


		state->_hoops_CGSRI = *_hoops_PSGAI;
	}

	state->_hoops_PRSRI = _hoops_CPA;
}



/*
* _hoops_PGAA
*/
local void _hoops_RGRAI(
	_hoops_ASCRI alter			*state,
	Int_Rectangle const		*_hoops_AGRAI) {

	DC_Point			_hoops_PGRAI;
	long				x, y;
	_hoops_ISC		_hoops_APRRA;

        /* _hoops_HSRR _hoops_IGGAI _hoops_CCPHR _hoops_PPSCP _hoops_CCH: */
        /* _hoops_AIAP _hoops_IRS _hoops_IHIS _hoops_IRGAA _hoops_IS _hoops_CGGGH _hoops_AAPA _hoops_RAAP _hoops_RPIA _hoops_IIGR _hoops_PPSCP */
        /* _hoops_GGR _hoops_IISRI _hoops_PCRR _hoops_HIS _hoops_SGS _hoops_SR _hoops_CHR _hoops_HRPP _hoops_IH _hoops_PPSCP _hoops_CCH. */
        /* _hoops_HIPR _hoops_ICHGA _hoops_HIGAI _hoops_IRGAA */

        /* _hoops_SGH _hoops_AGAH _hoops_GSSC _hoops_RPHR _hoops_RPIA */
		_hoops_PGRAI.x = (float) _hoops_AGRAI->left;
		_hoops_PGRAI.y = (float) _hoops_AGRAI->bottom;

        /*
	* _hoops_RAH _hoops_IRS _hoops_CSGSR _hoops_GH _hoops_IHIS _hoops_CCA _hoops_HIGAI _hoops_IRGAA _hoops_RPP _hoops_HAHH.
	*/
	if (state-> _hoops_HSCRI) {
		_hoops_SHSRI(state, "<");
	}
	else {
		_hoops_SHSRI(state, "PE<");
	}

	_hoops_GIGAI(state, &x, &y, &_hoops_PGRAI);
		_hoops_RIGAI(state, x,y);

		_hoops_SHSRI(state, ";");			/* _hoops_RSGR _hoops_HIGAI _hoops_IRGAA */
		state->_hoops_HSCRI = false;

	/* _hoops_HAIA _hoops_SACRI _hoops_AGSHA _hoops_RRP _hoops_IS _hoops_HGRAI _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_AHGAI
	* _hoops_AAGA _hoops_CARA _hoops_ARPP _hoops_GII _hoops_PPSCP _hoops_IS _hoops_HHSA _hoops_GRGAI _hoops_IS _hoops_ASH _hoops_AHRH
	* _hoops_RIIA _hoops_IIGR _hoops_IGRAI _hoops_GPP _hoops_RH _hoops_CGRAI. _hoops_PHGP _hoops_RPP _hoops_HAHH,
	* _hoops_SR _hoops_SGRAI _hoops_IRS _hoops_RGGAI _hoops_PSCHR _hoops_HPGR _hoops_RH _hoops_IICAA _hoops_PPSR.
        */
        if (state->_hoops_SSCRI != true) {
            /* _hoops_RAP _hoops_IS _hoops_RGGAI _hoops_HIS _hoops_PSCHR _hoops_GRS _hoops_HAR _hoops_CRGH.
            */
            _hoops_APRRA.r = 255;
            _hoops_APRRA.g = 255;
            _hoops_APRRA.b = 0;
            _hoops_ARGAI(state, &_hoops_APRRA);
            if ((int)1 != state->_hoops_IRSRI)
                    _hoops_ACPSR(state, (int)1);

            /* _hoops_RAIGR _hoops_CSGSR _hoops_ISHP _hoops_HRGR _hoops_RAPR.
            */
            _hoops_SHSRI(state, "PD;PU;");
            state->_hoops_SSCRI = true;
        }
}


/*
* _hoops_PGAA
*/
static void _hoops_GRRAI(
	_hoops_ASCRI alter	*state,
	long				_hoops_RRRAI,
	long				_hoops_ARRAI,
	int					_hoops_RPSRI) {

	char				string[64];
	_hoops_GARSR		i;
	long				width, height;

	/* _hoops_PRRAI _hoops_IS _hoops_IISRI _hoops_CCH, _hoops_HASRH _hoops_HPGR _hoops_SCGR _hoops_IGGAI _hoops_CSGSR _hoops_AHC.
	*/
	_hoops_SHSRI(state, "\033%1A");

	/* _hoops_RHGAR _hoops_RHAAR _hoops_CSCR _hoops_PIH _hoops_IRGAA _hoops_RPP _hoops_ICRP
	* _hoops_RPAI _hoops_CSCR _hoops_IRGAA _hoops_RHAP _hoops_HAR _hoops_PSSP _hoops_RH _hoops_PPSCP _hoops_GPRR.
	*/
	if (state->_hoops_PPSRI != _hoops_RPSRI) {

		if (_hoops_RPSRI == _hoops_SICRI) {
			/* _hoops_ACCRH _hoops_CSCR _hoops_PIH:
			* _hoops_CSSGR _hoops_GC = 0
			* _hoops_SSHI _hoops_IPISR _hoops_HRRAI = 1,	_hoops_IRRAI _hoops_HPP _hoops_AIR
			*	  (_hoops_CGAS _hoops_HAIR _hoops_GHSHA, _hoops_PIGAI _hoops_HPP _hoops_AIR
			* _hoops_CRRAI _hoops_RIR _hoops_CIHA = 8
			* _hoops_CRRAI _hoops_RIR _hoops_AHGPH, _hoops_PHGPH, _hoops_IHAC _hoops_PRRPA = 8, 8, 8
			* _hoops_SGPR _hoops_SRRAI _hoops_PGGA _hoops_IIGR _hoops_GARAI 0
			*/
			_hoops_GISRI(state,
				"\033*v6W\0\1\010\010\010\010", 11); /*11 _hoops_ICCGI */

			/*
			* _hoops_IPCP _hoops_HSPP _hoops_IISRI _hoops_CCH _hoops_IRGAA _hoops_GRS _hoops_GGHC _hoops_IISRI _hoops_IS _hoops_CAPGP
			* _hoops_RH _hoops_SCGR _hoops_SACRI _hoops_IHCRH. _hoops_HSHCR, _hoops_RH _hoops_RHAAR
			* _hoops_CSCR _hoops_PIH _hoops_IRGAA _hoops_GRS _hoops_HIAP _hoops_RH _hoops_IHCRH.
			* _hoops_RARAI _hoops_PPR _hoops_AARAI _hoops_RH _hoops_IHCRH _hoops_HRGR _hoops_HAR _hoops_PARAI _hoops_CCGR _hoops_RAS
			* _hoops_RH _hoops_RHAAR _hoops_CSCR _hoops_IRGAA _hoops_SSCP _hoops_RPII _hoops_AHSHH _hoops_HPGR _hoops_CHGC _hoops_ARR
			* _hoops_IS _hoops_ARP _hoops_RH _hoops_ARCR _hoops_IGIR _hoops_PPR _hoops_SIH _hoops_RIR _hoops_CIHA.
			* _hoops_PHGP _hoops_SR _hoops_RRP _hoops_IS _hoops_ARP _hoops_GH _hoops_RH _hoops_IHIR _hoops_IHCRH _hoops_GGR _hoops_IISRI _hoops_IS _hoops_SHH _hoops_HRPP
			* _hoops_IH _hoops_RH _hoops_SCGH-_hoops_CIHA _hoops_CSCR.
			*/

			if (state->_hoops_HPSRI != _hoops_ACCRI) {
				if (state->_hoops_HPSRI == _hoops_PCCRI) {
					/* _hoops_HARAI _hoops_CSAP _hoops_SHIS _hoops_HIS _hoops_CIHPA _hoops_PSAP _hoops_RH _hoops_IHCRH _hoops_RRGC
					*/
					_hoops_SHSRI(state,"\033*p1P");
				}
				else {
					for (i=1; i<=_hoops_PICRI; i++) {
						if (state->pen[i].defined) {
							_hoops_GSSRI(state, i, true);
						}
						else {
							Sprintf_D(string,"\033*v255a255b255c%dI",i);
							_hoops_SHSRI(state, string);
						}
					}
				}
				state->_hoops_HPSRI = _hoops_ACCRI;
			}

			/* _hoops_ICSS _hoops_CIHA 0 _hoops_HIS _hoops_SGS _hoops_SR _hoops_HIAP _hoops_IS _hoops_PGS _hoops_CAPP.
			*/
			state->pen[0].set = false;
			state->_hoops_PPSRI = _hoops_SICRI;
		}
		else {
			/* _hoops_IARAI
			*/

			/* _hoops_CARAI _hoops_IPISR _hoops_ASSP'_hoops_RA _hoops_SGH _hoops_PCCP _hoops_CGAS _hoops_IHCRH.
			* _hoops_HSHCR _hoops_RPP _hoops_SR _hoops_HS _hoops_SPR _hoops_PAPR _hoops_IH _hoops_CGAS _hoops_AHRH,
			* _hoops_AISI _hoops_SCH _hoops_HA _hoops_GGR _hoops_AGIR _hoops_SR _hoops_RRP _hoops_SCH _hoops_SPHR.
			*/
			if (state->_hoops_HPSRI == _hoops_ACCRI) {
					_hoops_SHSRI(state,"\033*p0P");
					state->_hoops_HPSRI = _hoops_PCCRI;
			}

			/* _hoops_ACCRH _hoops_CSCR _hoops_PIH:
			* _hoops_CSSGR _hoops_GC = 0
			* _hoops_SSHI _hoops_IPISR _hoops_HRRAI = 3,	_hoops_CARAI _hoops_HPP _hoops_AIR
			*	   (_hoops_PPPSR _hoops_HAIR _hoops_GHSHA, _hoops_PIGAI _hoops_HPP _hoops_AIR
			* _hoops_CRRAI _hoops_RIR _hoops_CIHA = 8
			* _hoops_CRRAI _hoops_RIR _hoops_AHGPH, _hoops_PHGPH, _hoops_IHAC _hoops_PRRPA = 8, 8, 8
			* _hoops_SGPR _hoops_SRRAI _hoops_PGGA _hoops_IIGR _hoops_GARAI 0
			*/
			_hoops_GISRI(state,
				"\033*v6W\0\3\010\010\010\010", 11); /*11 _hoops_ICCGI */

			state->_hoops_PPSRI = _hoops_GCCRI;
		}

		/*
		* _hoops_RAP _hoops_PPSCP _hoops_RAAA
		*/
		Sprintf_D(string,"\033*t%dR",state->_hoops_HAP);
		_hoops_SHSRI(state, string);
	}

	/* _hoops_HSRR _hoops_CGAS _hoops_HAIR, _hoops_SR _hoops_SHR _hoops_ISPR _hoops_IS _hoops_SHH _hoops_RCRR _hoops_CIHA 0
	* _hoops_HRGR _hoops_ARP _hoops_IS _hoops_PGS, _hoops_HIS _hoops_SGS _hoops_SCH _hoops_GRS _hoops_SHH _hoops_RRH.
	*/
	if (_hoops_RPSRI == _hoops_SICRI) {
		if ((state->pen[0].defined != true) ||
			(state->pen[0].set != true) ||
			(state->pen[0].r != 255) ||
			(state->pen[0].g != 255) ||
			(state->pen[0].b != 255)) {

			_hoops_SHSRI(state,"\033*v255a255b255c0I");
			state->pen[0].defined = true;
			state->pen[0].set = true;
			state->pen[0].r = 255;
			state->pen[0].g = 255;
			state->pen[0].b = 255;
		}
	}

		/*
	* _hoops_ARP _hoops_APPS, _hoops_IGAA
	* _hoops_HSPP _hoops_PPSCP _hoops_HCISR _hoops_HPGR _hoops_SCGR _hoops_HASRH _hoops_AHC
	* _hoops_ARP _hoops_RISRP
	*/
		width  = _hoops_ARRAI;
		height = _hoops_RRRAI;

#ifdef _hoops_SARAI
	Sprintf_DD(string,"\033*r%dt%dS\033*r1A\033*b0M", height, width);
#else
	Sprintf_DD(string,"\033*r%dt%dS\033*r1A\033*b2M", height, width);
#endif

	_hoops_SHSRI(state, string);
}


/*
* _hoops_PGAA
*/
local bool _hoops_GPRAI(
	_hoops_HHCR const	&_hoops_IHCR,
	_hoops_ASCRI alter				*state,
	Int_Rectangle const			*_hoops_AGRAI,
	int								type) {

	long					_hoops_RPRAI,
										_hoops_APRAI,
										_hoops_PPRAI,
										_hoops_HPRAI,
										_hoops_IPRAI,
										_hoops_CPRAI,
										_hoops_SAIRI,
										_hoops_SPRAI,
										_hoops_GHRAI;
	Int_Rectangle		_hoops_RHRAI;
	long					_hoops_AHRAI;
	int						increment;


	/* _hoops_CSH _hoops_PIAH _hoops_PPSCP _hoops_PHRAI _hoops_PPR _hoops_SR _hoops_RRP _hoops_IS _hoops_ARP _hoops_GH
	* _hoops_IH _hoops_IRS _hoops_CCAH _hoops_PPSCP. _hoops_SGPR _hoops_HHRAI _hoops_IPP'_hoops_GRI
	* _hoops_ACIPR _hoops_HSPH _hoops_ARRGR, _hoops_PGAP _hoops_HRGR _hoops_CGI _hoops_GGR _hoops_GAR _hoops_HSPH,
	* _hoops_IS _hoops_ARP _hoops_RH _hoops_IGIR _hoops_PPR _hoops_RIRPA _hoops_IIGR _hoops_RH _hoops_PPSCP _hoops_SRHR.
	* _hoops_CGP _hoops_RGR _hoops_HRGR _hoops_HAH _hoops_AHSC, _hoops_SR _hoops_SGH _hoops_IRS _hoops_HRHC _hoops_IGIR _hoops_SGS
	* _hoops_GRS _hoops_HGGC _hoops_HHSHH _hoops_RH _hoops_SCGR _hoops_AHRH _hoops_PHGSP.
	*/

	if (state->_hoops_SASRI != NULL) {
		/* _hoops_PPSCP _hoops_IHAH _hoops_HRGR _hoops_HAR _hoops_IRAP _hoops_HIS _hoops_AIAH _hoops_PHRAI.
		*/
		HE_ERROR (HEC_HPGL2_DRIVER, HES_CREATE_MEMORY_RASTER_FAILED,
			"Error opening raster cache that is already open.");
		return false;
	}

	/* _hoops_RAP _hoops_IHAH _hoops_IGIR _hoops_SAIPR _hoops_ARI.
	*/
	_hoops_AHRAI = _hoops_ICCRI;

	/* _hoops_CGP _hoops_AIAA _hoops_GCSRR/_hoops_AIR, _hoops_IRHH _hoops_CGRIR _hoops_SAIPR _hoops_SPR _hoops_SCHCR _hoops_RH _hoops_IGIR.
	*/
	if (type == _hoops_GCCRI) _hoops_AHRAI /= 4;


	/* _hoops_RHCCP _hoops_GRS _hoops_HS _hoops_IHRAI _hoops_SGS _hoops_SISRI _hoops_PPR _hoops_CHRAI
	*  _hoops_CHR > 0, _hoops_PPR _hoops_SGS _hoops_PHGSP _hoops_ARRGR _hoops_GRS _hoops_SHH
	*  _hoops_GIAA _hoops_PAR _hoops_SASPR _hoops_IS _hoops_HSPH _hoops_ARRGR.
	*/
	_hoops_RPRAI = _hoops_IHCR->_hoops_AGAA.right - _hoops_IHCR->_hoops_AGAA.left   + 1;
	_hoops_APRAI = _hoops_IHCR->_hoops_AGAA.top	- _hoops_IHCR->_hoops_AGAA.bottom + 1;
	_hoops_PPRAI = _hoops_RPRAI * _hoops_APRAI;

	if (_hoops_PPRAI <= _hoops_AHRAI) {
		/* _hoops_SGPR _hoops_HSPH _hoops_ARRGR _hoops_IS _hoops_ARP _hoops_PPSCP _hoops_IHAH */
		_hoops_SPRAI	= _hoops_RPRAI;
		_hoops_GHRAI	= _hoops_APRAI;
		_hoops_SAIRI = _hoops_PPRAI;
		state->_hoops_SPSRI = _hoops_IHCR->_hoops_AGAA;
	}
	else {
		_hoops_HPRAI = _hoops_AGRAI->right - _hoops_AGRAI->left	+ 1;
		_hoops_IPRAI  = _hoops_AGRAI->top  - _hoops_AGRAI->bottom + 1;
		_hoops_CPRAI = _hoops_HPRAI * _hoops_IPRAI;

		if (_hoops_CPRAI > _hoops_AHRAI) {
			/* _hoops_IICRI _hoops_HRGR _hoops_HAH _hoops_AHSC _hoops_IS _hoops_IHAH */
			return false;
		}
		/* _hoops_CGP _hoops_ARI, _hoops_SHRAI _hoops_GCSRR _hoops_HRGR _hoops_GAPA _hoops_PHGSP _hoops_PPR _hoops_HSPH _hoops_PGRR.
		* _hoops_PS'_hoops_GCPP _hoops_SGH _hoops_PCCP _hoops_GIRAI _hoops_PIRPR _hoops_IS _hoops_CSRA _hoops_RH _hoops_IHAH _hoops_IGIR.
		* _hoops_HHIGR _hoops_HRGR _hoops_IHGP, _hoops_PPR _hoops_RIRAI _hoops_RH _hoops_IHAH _hoops_IS _hoops_AIRAI _hoops_HSPH _hoops_HGPC.
		* _hoops_PS _hoops_HSRS _hoops_GPISR _hoops_IS _hoops_SGS _hoops_SR _hoops_HGCR _hoops_GHPP _hoops_GGR _hoops_CRGP _hoops_HSAR
		* _hoops_AHCA 10 _hoops_HRRAR _hoops_HPGR _hoops_HRGI.
		*/

		_hoops_RHRAI = *_hoops_AGRAI;
		increment	= _hoops_CCCRI;	 /* _hoops_ASPA */

		while (_hoops_CPRAI < _hoops_AHRAI) {
			state->_hoops_SPSRI = _hoops_RHRAI;
			_hoops_RHRAI.top	   += increment;
			_hoops_RHRAI.right  += increment;
			_hoops_RHRAI.bottom -= increment;
			_hoops_RHRAI.left   -= increment;

			if (_hoops_RHRAI.top	   > _hoops_IHCR->_hoops_AGAA.top)
				_hoops_RHRAI.top	   = _hoops_IHCR->_hoops_AGAA.top;
			if (_hoops_RHRAI.right  > _hoops_IHCR->_hoops_AGAA.right)
				_hoops_RHRAI.right  = _hoops_IHCR->_hoops_AGAA.right;
			if (_hoops_RHRAI.bottom < _hoops_IHCR->_hoops_AGAA.bottom)
				_hoops_RHRAI.bottom = _hoops_IHCR->_hoops_AGAA.bottom;
			if (_hoops_RHRAI.left   < _hoops_IHCR->_hoops_AGAA.left)
				_hoops_RHRAI.left   = _hoops_IHCR->_hoops_AGAA.left;

			_hoops_HPRAI = _hoops_RHRAI.right - _hoops_RHRAI.left	  + 1;
			_hoops_IPRAI  = _hoops_RHRAI.top	 - _hoops_RHRAI.bottom + 1;
			_hoops_CPRAI = _hoops_HPRAI * _hoops_IPRAI;
		}

		_hoops_SPRAI = state->_hoops_SPSRI.right
			- state->_hoops_SPSRI.left   + 1;
		_hoops_GHRAI  = state->_hoops_SPSRI.top
			- state->_hoops_SPSRI.bottom + 1;
		_hoops_SAIRI = _hoops_SPRAI * _hoops_GHRAI;
	}

	/* _hoops_AGGA _hoops_SR _hoops_SGH _hoops_RH _hoops_IHIR 4 _hoops_GCSRR _hoops_RIR _hoops_AIR _hoops_RPP _hoops_HAHH.
	*/
	if (type == _hoops_GCCRI) {
		_hoops_SPRAI	*= 4;
		_hoops_SAIRI *= 4;
	}

	TRY_ALLOC_ARRAY(state->_hoops_SASRI, _hoops_SAIRI, char);

	if (!state->_hoops_SASRI) {
		/* _hoops_ARPC _hoops_IGGAR _hoops_SRHR*/
		HE_ERROR (HEC_HPGL2_DRIVER, HES_CREATE_MEMORY_RASTER_FAILED, "Could not open raster buffer.");
		return false;
	}

	state->_hoops_GPSRI = _hoops_SAIRI;

	/* _hoops_GHRAA _hoops_GCSRR _hoops_GGR _hoops_IHAH _hoops_IS 0.
	* _hoops_HSRR _hoops_SCGH _hoops_PPSCP, _hoops_CIHA 0 _hoops_HRGR _hoops_HCR _hoops_PGS (_hoops_RRH);
	* _hoops_HSRR _hoops_CHPGH _hoops_HGGPA,  _hoops_PIRAI = (0,0,0,0) _hoops_HRGR _hoops_APRP, _hoops_HIH
	* _hoops_CCA _hoops_IHIR _hoops_IHSP (_hoops_IRS=0), _hoops_PGAP _hoops_SR'_hoops_GCPP _hoops_HIRAI _hoops_CGPR _hoops_SR _hoops_HSPAA
	* _hoops_RH _hoops_PPSCP _hoops_PPR _hoops_AGRP _hoops_IS _hoops_SACRI'_hoops_GRI _hoops_RRH _hoops_PGS (255,255,255)
	*/
	/*	_hoops_IIRAI((_hoops_SRPC *)(_hoops_PIAP->_hoops_CIRAI), (_hoops_SCSH)0, _hoops_SIRAI); */
	{
		char *			_hoops_RPPA = state->_hoops_SASRI;
		int				count = _hoops_SAIRI;

		while (count-- > 0)
			*_hoops_RPPA++ = 0;
	}

	state->_hoops_RPSRI		= type;
	state->_hoops_APSRI = _hoops_SPRAI;

	/* _hoops_RSCS _hoops_SCGR _hoops_GCRAI _hoops_ARRGR _hoops_PPR _hoops_HSHR _hoops_IS _hoops_SGH
	* _hoops_SPHR _hoops_IS _hoops_HSPAA _hoops_IS _hoops_SISS _hoops_CGPR _hoops_SR _hoops_HSPAA _hoops_PPSCP. _hoops_HGI _hoops_ARRGR
	* _hoops_HRGR _hoops_SASPR _hoops_IS _hoops_PAR _hoops_APPR _hoops_HSAR _hoops_RH _hoops_RCRAI _hoops_ARRGR
	* _hoops_SGS _hoops_SR _hoops_GACC _hoops_ARP _hoops_ARI.
	*/
	state->_hoops_CPSRI			   = _hoops_IHCR->_hoops_AGAA;
	state->_hoops_IPSRI = _hoops_IHCR->_hoops_CPA;

	/* _hoops_GHRAA _hoops_RIHRR _hoops_PHGSP _hoops_IS _hoops_IRAP */
	state->_hoops_GHSRI.bottom = state->_hoops_SPSRI.top;
	state->_hoops_GHSRI.top	 = state->_hoops_SPSRI.bottom;
	state->_hoops_GHSRI.left	 = state->_hoops_SPSRI.right;
	state->_hoops_GHSRI.right	 = state->_hoops_SPSRI.left;


	return true;
}


/*
* _hoops_PGAA
*/
local void _hoops_ACRAI(
	_hoops_ASCRI alter		*state,
	DC_Point const		*start,
	DC_Point const		*end,
	int						row_bytes,
	void const				*rasters,
	int						type,
	Int_Rectangle const *_hoops_AGRAI) {

	char					*_hoops_GIHPR;
	char					*source;
	long					top, bottom, right, left;
	long					_hoops_APARP,
										_hoops_GCPIR;

	UNREFERENCED (end);

	/* _hoops_HGI _hoops_PSCH _hoops_IGRIR _hoops_PPSCP _hoops_PIH _hoops_IS _hoops_RH _hoops_PPSCP _hoops_IHAH.
	* _hoops_IPCP _hoops_CIS _hoops_GRS _hoops_HS _hoops_RAICR _hoops_SGS _hoops_RH _hoops_IHAH _hoops_HICP,
	* _hoops_PPR _hoops_SGS _hoops_RH _hoops_CCAH _hoops_PHGSP _hoops_CHR
	* _hoops_GIAA _hoops_RH _hoops_IHAH'_hoops_GRI _hoops_AHPA _hoops_PHGSP, _hoops_PAR _hoops_SHS _hoops_RH _hoops_CIS
	* _hoops_GRS _hoops_HS _hoops_AHSHH _hoops_RH _hoops_PGHC _hoops_PPSCP _hoops_PPR
	* _hoops_SPIP _hoops_IRS _hoops_CCAH _hoops_IHAH _hoops_IS _hoops_SIHRR _hoops_RH _hoops_CCAH _hoops_PPSCP.
	*
	* _hoops_IPCP _hoops_CIS _hoops_GRS _hoops_HS _hoops_PCRAI _hoops_HCRAI _hoops_AHRH
	* _hoops_SGS _hoops_HS <= 0 _hoops_PHGSP.
	*/


	top		= (long)_hoops_AGRAI->top;
	bottom	= (long)_hoops_AGRAI->bottom;
	left	= (long)_hoops_AGRAI->left;
	right	= (long)_hoops_AGRAI->right;

	_hoops_GCPIR = (type==_hoops_SICRI) ? (long)1 : (long)4;
	_hoops_APARP	= (right - left + 1) * _hoops_GCPIR;

	_hoops_GIHPR = (char *)(state->_hoops_SASRI)
		+ (((long)(state->_hoops_SPSRI.top) - top) *
		  (long)(state->_hoops_APSRI))
		+ ((left - (long)state->_hoops_SPSRI.left) *
		  _hoops_GCPIR);
	source = (char*)rasters
		+ (((long)(start->y) - top) * row_bytes)
		+ ((left - (long)(start->x)) * _hoops_GCPIR);



	/* _hoops_HRHI _hoops_RIHRR _hoops_PPSCP _hoops_PHGSP
	*/
	if (top	   > state->_hoops_GHSRI.top)
		state->_hoops_GHSRI.top	 = top;
	if (bottom < state->_hoops_GHSRI.bottom)
		state->_hoops_GHSRI.bottom = bottom;
	if (left   < state->_hoops_GHSRI.left)
		state->_hoops_GHSRI.left	 = left;
	if (right  > state->_hoops_GHSRI.right)
		state->_hoops_GHSRI.right	 = right;

	/*
	* _hoops_PAGA _hoops_SR _hoops_CHR _hoops_HPIAA _hoops_IRHSA _hoops_PIH _hoops_HRGR _hoops_GCSS _hoops_GGR
	* 4 _hoops_RAPSR _hoops_SGHC _hoops_SGS _hoops_CHR _hoops_GCRCP.
	*/

	while (top-- >= bottom) {
		COPY_MEMORY (source, _hoops_APARP, _hoops_GIHPR);
		source += row_bytes;
		_hoops_GIHPR += state->_hoops_APSRI;
	}
}


/*
* _hoops_PGAA
*/
local long _hoops_ICRAI(
	_hoops_ASCRI alter		*state,
	long alter				_hoops_GPIGR) {

		unsigned char	*in;				/* _hoops_CRS _hoops_IS _hoops_SPS _hoops_CIIA _hoops_RAPSR */
		unsigned char	*_hoops_PAGR;				/* _hoops_CRS _hoops_IS _hoops_SPS _hoops_IIPR _hoops_RAPSR */
		unsigned char	*_hoops_IPHAP;	/* _hoops_CRS _hoops_IS _hoops_CRAPH _hoops_RAPSR */
		unsigned char	b;				/* _hoops_SCGR _hoops_RAPSR _hoops_PIRA */
		long			_hoops_CCRAI;			/* _hoops_SCRAI */
	unsigned char	*_hoops_GSRAI;

	/* _hoops_RSRAI _hoops_CIAAR _hoops_GCSRR _hoops_APHR _hoops_HPGR _hoops_GGR _hoops_IS _hoops_GGSR
	* _hoops_GRP _hoops_SACRI _hoops_ASRAI 2: _hoops_PSRAI _hoops_HSRAI. 4.0 "_hoops_ISRAI" _hoops_IPISR.
	* _hoops_GCAAA _hoops_PHI _hoops_IIGR _hoops_GCSRR _hoops_GGR _hoops_SGRH _hoops_III.
	*/

	in	= state->_hoops_RPHGH;
	_hoops_PAGR = state->_hoops_RHSRI;
		_hoops_GSRAI = _hoops_PAGR;

		_hoops_IPHAP = _hoops_PAGR;			/* _hoops_HSPC _hoops_RPGR _hoops_CRAPH _hoops_CCA 255 (=-1) */
		_hoops_PAGR++;
		*_hoops_IPHAP = 255;

		while (_hoops_GPIGR) {			/* _hoops_CIAAR = _hoops_GCSRR _hoops_HHRPA _hoops_IH _hoops_RISRP */

				/* _hoops_CSGA _hoops_SCRAI _hoops_IIGR _hoops_SPS _hoops_CIIA _hoops_RAPSR */
				_hoops_CCRAI = _hoops_GPIGR;						/* _hoops_AHPA _hoops_SSRR _hoops_CSRAI */
				b = *in;						/* _hoops_PIRA _hoops_IIGR _hoops_SPS _hoops_RAPSR */
				in++;
				_hoops_GPIGR--;

				while (_hoops_GPIGR) {
						if (b!=*in) break;
						in++;
						_hoops_GPIGR--;
				}
				_hoops_CCRAI-=_hoops_GPIGR;

				if (_hoops_CCRAI<3) {	/* _hoops_RPP 1 _hoops_PAR 2 _hoops_CSRAI, _hoops_GGCR _hoops_IS _hoops_PIH _hoops_HIGR */
						if (*_hoops_IPHAP==127) {	/* _hoops_PSCR _hoops_PIH _hoops_CRAPH _hoops_HRGR _hoops_IHIR */
								_hoops_IPHAP = _hoops_PAGR;
								_hoops_PAGR++;
								*_hoops_IPHAP = 255; /* _hoops_HSPC _hoops_CRAPH
								  _hoops_GAR _hoops_RPGR _hoops_CCA 255 (=-1) */
						}

						*_hoops_PAGR = b;
						_hoops_PAGR++;

						if (*_hoops_IPHAP==255) {
								*_hoops_IPHAP= 0;
						}
						else (*_hoops_IPHAP)++;				/* _hoops_GPISR _hoops_PIH _hoops_CRAPH */

						if (_hoops_CCRAI==2) { /* _hoops_AA _hoops_GICS */
								if (*_hoops_IPHAP==127) {	/* _hoops_PSCR _hoops_PIH _hoops_CRAPH _hoops_HRGR _hoops_IHIR */
										_hoops_IPHAP = _hoops_PAGR;
										_hoops_PAGR++;
										*_hoops_IPHAP = 255; /* _hoops_HSPC _hoops_CRAPH _hoops_GAR
									   _hoops_RPGR _hoops_CCA 255 (=-1) */
								}

								*_hoops_PAGR = b;
								_hoops_PAGR++;

								if (*_hoops_IPHAP==255) {
										*_hoops_IPHAP= 0;
								}
								else (*_hoops_IPHAP)++;		/* _hoops_GPISR _hoops_PIH _hoops_CRAPH */
						}
				}
				else {							/* 3 _hoops_PAR _hoops_RRI _hoops_CSRAI */

			/* _hoops_RH _hoops_HSPR _hoops_III _hoops_HIRGR _hoops_GPGR
			_hoops_RPGR _hoops_GCSRR _hoops_HPGR _hoops_RSGR _hoops_IS _hoops_SHH _hoops_PCRAI */
						if (b==0) if (_hoops_GPIGR==0) break;

						if (*_hoops_IPHAP==255) {
								_hoops_PAGR--;			/* _hoops_RPGR _hoops_CRAPH, _hoops_HIS _hoops_GGI _hoops_IAPR _hoops_SCH */
						}

						while (_hoops_CCRAI>128) {
								*_hoops_PAGR = 129;		/* 81_hoops_GGHR = -127 */
								_hoops_PAGR++;
								*_hoops_PAGR = b;
								_hoops_PAGR++;
								_hoops_CCRAI-=128;
						}

						if (_hoops_CCRAI>1) {
								*_hoops_PAGR = (unsigned char)(257 - _hoops_CCRAI);
								_hoops_PAGR++;
								*_hoops_PAGR = b;
								_hoops_PAGR++;

								_hoops_IPHAP = _hoops_PAGR;	/* _hoops_ARP _hoops_GH _hoops_CCAH _hoops_RPGR _hoops_CRAPH */
								_hoops_PAGR++;
								*_hoops_IPHAP = 255;
						}
						else {			/* _hoops_RGAR _hoops_SPR _hoops_SSRAI, _hoops_ASAC _hoops_GAR _hoops_PIH _hoops_HIGR */
								_hoops_IPHAP = _hoops_PAGR;
								_hoops_PAGR++;
								*_hoops_IPHAP = 0;
								*_hoops_PAGR = b;
								_hoops_PAGR++;
						}
				}
		}

		if (*_hoops_IPHAP==255) {
				_hoops_PAGR--;					/* _hoops_RPGR _hoops_CRAPH, _hoops_HIS _hoops_GGI _hoops_IAPR _hoops_SCH */
		}

		return (long)(_hoops_PAGR-_hoops_GSRAI);	/* _hoops_ASRC _hoops_PHI _hoops_IIGR _hoops_IIPR _hoops_GCSRR */
}





/*
* _hoops_PGAA
*/
local void _hoops_GGAAI(
	_hoops_ASCRI alter		*state,
	long					length) {

	char					string[16];


#ifdef _hoops_SARAI
	Sprintf_D(string, "\033*b%dW", length);
	_hoops_SHSRI(state, string);
	_hoops_GISRI(state, state->_hoops_RPHGH, length);
#else
	/* _hoops_IAAH _hoops_III
	*/
	length = _hoops_ICRAI(state, length);
	Sprintf_D(string, "\033*b%dW", length);
	_hoops_SHSRI(state, string);
	_hoops_GISRI(state, state->_hoops_RHSRI, length);

#endif
}


/*
* _hoops_PGAA
*/
local bool _hoops_RGAAI(
	_hoops_ASCRI alter		*state,
	long					size) { /* _hoops_IGIR _hoops_GGR _hoops_GCSRR */

	/* _hoops_HGI _hoops_API _hoops_HRGR _hoops_PIGS _hoops_CGPR
	* _hoops_SR _hoops_HS _hoops_IRS _hoops_PPSCP _hoops_CSCR _hoops_IS _hoops_HSPAA _hoops_IS _hoops_SISS,
	* _hoops_PPR _hoops_SR _hoops_RRP _hoops_IS _hoops_IGS _hoops_IRS _hoops_SRHR _hoops_IS _hoops_SGH _hoops_IS
	* _hoops_IRSHR _hoops_RH _hoops_PPSCP _hoops_PIH _hoops_PPR _hoops_SAGR _hoops_RH _hoops_PIH.
	* _hoops_IIPP _hoops_IRS _hoops_SRHR _hoops_IS _hoops_CRCC 2 _hoops_IACH _hoops_RH _hoops_AIR _hoops_IGAA
	* _hoops_IIGR _hoops_RH _hoops_PPSCP.  _hoops_PS _hoops_ASAC _hoops_PGCR _hoops_PIAP _hoops_CICRR _hoops_IS _hoops_RH
	* _hoops_SRHR, _hoops_RH _hoops_AIRA _hoops_CRS _hoops_IS _hoops_RH _hoops_SRS _hoops_ARIP _hoops_GRS
	* _hoops_CGRPR _hoops_RH _hoops_ARIP _hoops_IGI _hoops_IS _hoops_CRCC _hoops_RH _hoops_SGRH _hoops_PIH.
	* _hoops_IPCP _hoops_GIAP _hoops_CRS _hoops_GRS _hoops_PPSR _hoops_IS _hoops_RH _hoops_IRGP, _hoops_PGAP
	* _hoops_SR _hoops_SRS _hoops_CISA _hoops_GGR _hoops_CCA _hoops_PIH _hoops_PRRP _hoops_HGRAR.
	* _hoops_CGP _hoops_HGRC _hoops_IGIR == 0, _hoops_PSCR _hoops_SR _hoops_RGAR _hoops_CIH _hoops_GII _hoops_APRS _hoops_SRHR.
	*/

	/* _hoops_APSHR _hoops_GII _hoops_APRS _hoops_SRHR.
	*/
	if (state->_hoops_RHSRI != NULL) {
		/* _hoops_RHSIR _hoops_IGIR _hoops_HRGR _hoops_RGAR _hoops_HHAA */
		FREE_ARRAY(state->_hoops_RHSRI, 2*state->_hoops_AHSRI, char);
		state->_hoops_RHSRI = NULL;
		state->_hoops_RPHGH = NULL;
		state->_hoops_AHSRI = 0;
	}
	if (size <= 0) return true;

	/* _hoops_IIPP _hoops_CCAH _hoops_SRHR.
	* _hoops_GRSCP _hoops_IGIR _hoops_HRGR _hoops_RRPC _hoops_RH _hoops_PHI _hoops_IIGR _hoops_PIH _hoops_GCSRR.
	* _hoops_AGAAI() _hoops_SRS _hoops_IGISR _hoops_GIAP _hoops_HS _hoops_CCA _hoops_PIH _hoops_GGR
	* _hoops_RH _hoops_GGSP _hoops_ICSA. _hoops_SPAA _hoops_PGAAI() _hoops_HGAAI
	* _hoops_PIH _hoops_IS _hoops_RH _hoops_SRS _hoops_HHAA _hoops_IIGR _hoops_RH _hoops_SRHR _hoops_ARPP _hoops_HIRAA
	* _hoops_IS _hoops_RH _hoops_SISS.
	*/
	size += 128;  /* _hoops_GGCR _hoops_IGAAI _hoops_SPGS */

	TRY_ALLOC_ARRAY(state->_hoops_RHSRI, 2*size, unsigned char);

	if (!state->_hoops_RHSRI) {
		/* _hoops_ARPC _hoops_IGGAR _hoops_SRHR*/
		HE_ERROR (HEC_HPGL2_DRIVER, HES_CREATE_MEMORY_RASTER_FAILED, "Could not open raster buffer.");
		return false;
	}
	/* _hoops_RHSIR _hoops_IGIR _hoops_HRGR _hoops_IH _hoops_RH _hoops_HHAA _hoops_SSPP _hoops_IGI */
	state->_hoops_AHSRI = size;
	state->_hoops_RPHGH = state->_hoops_RHSRI + size;

	return true;
}



/*
* _hoops_PGAA
*/
local void _hoops_CGAAI(
	_hoops_ASCRI alter		*state,
	DC_Point const		*start,
	DC_Point const		*end,
	int						row_bytes,
	void const				*rasters,
	int						_hoops_RPSRI,
	Int_Rectangle const *_hoops_AGRAI,
	Int_Rectangle const *_hoops_GPHH,
	_hoops_GARRR			_hoops_SGAAI) {

	unsigned char			*source,
										*_hoops_PCAP;
	RGBAS32				*_hoops_GRAAI;
	long					rows, _hoops_RRAAI,
										_hoops_RSIGR, i,
										data_length, _hoops_ARAAI;
	char					*_hoops_RPHGH;
	char					*_hoops_PRAAI;

	UNREFERENCED (end);

	/* _hoops_SIGP: _hoops_PS _hoops_SIAS _hoops_HS _hoops_HRAAI _hoops_HHGS _hoops_IS _hoops_ISPR _hoops_GGSR _hoops_RPP
	* _hoops_APGAI _hoops_PIH _hoops_IISA _hoops_GGR _hoops_HAGH _hoops_IRAAI.
	*/

	/* _hoops_PAGA: _hoops_CRAAI _hoops_HRGR _hoops_RH _hoops_ISP _hoops_IS _hoops_RH _hoops_PIH _hoops_IH _hoops_RH
	 * _hoops_SPS _hoops_GAGHR. _hoops_SRAAI _hoops_HRGR _hoops_RH _hoops_PHI _hoops_IIGR _hoops_RIHRR _hoops_PIH _hoops_GCSRR.
	 * _hoops_SRAAI _hoops_PAH _hoops_SHH _hoops_CRGP _hoops_HSAR _hoops_CRAAI. */

	_hoops_RRAAI = _hoops_AGRAI->right - _hoops_AGRAI->left + 1;
	if (_hoops_RRAAI < 1) return;

	rows = _hoops_AGRAI->top - _hoops_AGRAI->bottom + 1;
	if (rows < 1) return;


	/* _hoops_PHAA, _hoops_ARP _hoops_GH _hoops_ACRAA _hoops_SRHR _hoops_IH _hoops_PPSCP _hoops_PIH.
	* _hoops_RGPP _hoops_AHRH _hoops_RRP 3 _hoops_GCSRR _hoops_RIR _hoops_AIR _hoops_PGGA _hoops_AIIR _hoops_RAPSR _hoops_HRGR _hoops_GIGRH.
	* _hoops_CGP _hoops_IGIR _hoops_IIGR _hoops_SCGR _hoops_SRHR _hoops_HRGR _hoops_HAH _hoops_RISA, _hoops_CCPP _hoops_IRS _hoops_CCAH _hoops_SPR.
	*/
	_hoops_RSIGR = rows;
	if (_hoops_RPSRI == _hoops_GCCRI) _hoops_RSIGR *= 3;
	if (state->_hoops_AHSRI < _hoops_RSIGR) {
		if (_hoops_RGAAI(state, _hoops_RSIGR) != true) {
			return;
		}
	}

	/* _hoops_RAP _hoops_HSPP _hoops_PPSR _hoops_IH _hoops_SRHR _hoops_IS _hoops_HCPRA _hoops_ASH _hoops_HGRAR _hoops_PIH.
	*/
	_hoops_RPHGH = (char *)state->_hoops_RPHGH;


	/* _hoops_ARGH _hoops_SACRI _hoops_HSPH _hoops_RPPS. _hoops_CPSGA _hoops_PHRI "_hoops_PHGSP" _hoops_GAAAI _hoops_PCCP
	* _hoops_AIAH _hoops_SACH _hoops_PPSCP, _hoops_SR _hoops_RRP _hoops_IS _hoops_SHH _hoops_RCRR _hoops_RH _hoops_SISS'_hoops_GRI _hoops_SCGR
	* _hoops_HSPH _hoops_RPPS _hoops_HRGR _hoops_ARP _hoops_CHPP _hoops_RAPR.
	*/
	if (_hoops_SGAAI != state->_hoops_PRSRI) {
		_hoops_PCPSR(state, _hoops_GPHH, _hoops_SGAAI);
	}

	/* _hoops_RAP _hoops_IICAA _hoops_PPSR _hoops_IH _hoops_PPSCP _hoops_GGR _hoops_SACRI. _hoops_HIPR _hoops_HCPA _hoops_HIGAI _hoops_CCH.
	*/
	_hoops_RGRAI(state, _hoops_AGRAI);

	/* _hoops_GCIH _hoops_IISRI _hoops_CCH.
	*/
	_hoops_GRRAI(state, _hoops_RRAAI, rows, _hoops_RPSRI);

	/* _hoops_PSIH _hoops_RAPSR _hoops_SHI _hoops_IS _hoops_SRS _hoops_AIR _hoops_IIGR _hoops_RIHRR _hoops_PHGSP
	* _hoops_IIGR _hoops_HCGP _hoops_PIH _hoops_PPSCP.
	*/
	_hoops_ARAAI = (long)_hoops_AGRAI->left - (long)start->x;
	if (state->_hoops_RPSRI == _hoops_GCCRI) _hoops_ARAAI *= 4;
	_hoops_ARAAI += (((long)start->y - (long)_hoops_AGRAI->top) * (long)row_bytes);
	_hoops_PRAAI = (char *)rasters + _hoops_ARAAI;

	/* _hoops_RAAAI _hoops_PPSCP _hoops_PIH, _hoops_PPR _hoops_HSPAA _hoops_III _hoops_HPP _hoops_III.
	*/
	if (_hoops_RPSRI == _hoops_SICRI) {

			data_length = rows;
			for (i= 0; i< _hoops_RRAAI; i++) {
				_hoops_PCAP   = (unsigned char *) _hoops_RPHGH + data_length - 1;
				source = (unsigned char *) _hoops_PRAAI + i;
				while (_hoops_PCAP >= (unsigned char *) _hoops_RPHGH) {
					*_hoops_PCAP-- = *source;
					source += row_bytes;
				}
				_hoops_GGAAI(state, data_length);
			}
	}
	else {
            /* _hoops_AAAAI _hoops_GPRR
            * _hoops_PAGA: _hoops_SR _hoops_ISPR _hoops_IHSP, _hoops_PPR _hoops_RPP _hoops_RRH (_hoops_AIIR = 0),
            * _hoops_PSCR _hoops_ARP _hoops_AIR _hoops_IS _hoops_APACA _hoops_PGS (255,255,255) _hoops_PGAP _hoops_SACRI _hoops_GRS _hoops_HSSRI
            * _hoops_GAR _hoops_RRH _hoops_SAPGP _hoops_IS _hoops_RH _hoops_PAAAI _hoops_SACRI _hoops_IRGAA.
            * _hoops_CGP _hoops_AIR _hoops_HRGR _hoops_HAR _hoops_RRH, _hoops_PPR _hoops_HAIR _hoops_HRGR _hoops_PGS
            * (255,255,255), _hoops_SR _hoops_AGRP _hoops_SCH _hoops_IS _hoops_HHSH _hoops_PGS
            * (254,254,254) _hoops_HIS _hoops_SGS _hoops_RH _hoops_SISS _hoops_GRS _hoops_IRHH _hoops_SCH _hoops_CIGC.
            * _hoops_SGPR _hoops_AGCR _hoops_HSH _hoops_HIS _hoops_SCH _hoops_HGAAI _hoops_PRAR _hoops_PGGA _hoops_HCR
            * _hoops_RGGHR _hoops_CHR _hoops_RH _hoops_PSHR.
            * _hoops_SIGP: _hoops_CGP _hoops_SR _hoops_IAIR _hoops_HISA _hoops_GAGHR _hoops_GPRR _hoops_RISRP _hoops_GGR _hoops_PIHRA
            * _hoops_IS _hoops_RH _hoops_SCGR _hoops_PSRAI _hoops_RISRP, _hoops_AGRP _hoops_CIGC _hoops_PGS _hoops_IS
            * (255,255,254).
            */
			/* _hoops_HAAAI = _hoops_IHPR, _hoops_HRSP _hoops_GSPR _hoops_RIR _hoops_AIR ->
			* 90 _hoops_CPSH _hoops_IRSHR: _hoops_PRPC _hoops_RAAP _hoops_RHCHR _hoops_SCIA _hoops_RAAP.
			*/
			data_length = rows * 3;
			for (i= 0; i< _hoops_RRAAI; i++) {
				_hoops_PCAP   = (unsigned char*)_hoops_RPHGH + data_length - 1;
				_hoops_GRAAI = (RGBAS32 *)_hoops_PRAAI + i;
				while (_hoops_PCAP > (unsigned char*) _hoops_RPHGH) {
					if (_hoops_GRAAI->a) {
						/* _hoops_HAR _hoops_RRH */
						if ((_hoops_GRAAI->r == 255) &&
							(_hoops_GRAAI->g == 255) &&
							(_hoops_GRAAI->b == 255)) {

							/* _hoops_IAAAI _hoops_PGS */
							*_hoops_PCAP-- = 254;
							*_hoops_PCAP-- = 254;
							*_hoops_PCAP-- = 254;
						}
						else {
							/* _hoops_PGII _hoops_RII _hoops_PSHA */
							*_hoops_PCAP-- = _hoops_GRAAI->b;
							*_hoops_PCAP-- = _hoops_GRAAI->g;
							*_hoops_PCAP-- = _hoops_GRAAI->r;
						}
					}
					else {
						/* _hoops_RAP _hoops_IS _hoops_RRH _hoops_PGS */
						*_hoops_PCAP-- = 255;
						*_hoops_PCAP-- = 255;
						*_hoops_PCAP-- = 255;
					}

					_hoops_GRAAI = (RGBAS32 *)((char *)_hoops_GRAAI + row_bytes);
				}
				_hoops_GGAAI(state, data_length);
			}
        }

	/* _hoops_HCSH _hoops_PPSCP _hoops_HCISR _hoops_CCH.
	* _hoops_PRRAI _hoops_ISSC _hoops_IS _hoops_SACRI _hoops_CCH _hoops_CCA _hoops_CSGSR _hoops_HPGR _hoops_SCGR _hoops_IISRI _hoops_CAAAI.
	*/
	_hoops_SHSRI(state, "\033*rC\033%1B");

	/* _hoops_GCSRI() _hoops_IS _hoops_HHSA _hoops_HIAP _hoops_IIGR _hoops_CISRI
	* _hoops_PPR _hoops_III _hoops_AIRC, _hoops_PPR _hoops_HHSA _hoops_SGH _hoops_IIGR _hoops_IPPSR _hoops_PCRR
	* _hoops_IH _hoops_SPS _hoops_RASIR.
	*/
	_hoops_CRGAI(state);
}



/*
* _hoops_PGAA
*/
local void _hoops_SAAAI(
	_hoops_ASCRI alter	*state) {

	DC_Point			start, end;


	/* _hoops_RAP _hoops_GH _hoops_GRPC _hoops_IIGR _hoops_PPSCP _hoops_IIHA _hoops_GPP _hoops_RIHRR _hoops_PHGSP. */
	start.x = (float) state->_hoops_SPSRI.left;
	start.y = (float) state->_hoops_SPSRI.top;
	end.x	= (float) state->_hoops_SPSRI.right;
	end.y	= (float) state->_hoops_SPSRI.bottom;


	/* _hoops_RHGAR _hoops_RH _hoops_PPSCP _hoops_CSCR. */
	_hoops_CGAAI(state,
				&start,
				&end,
				state->_hoops_APSRI,
				(void *)(state->_hoops_SASRI),
				state->_hoops_RPSRI,
				&(state->_hoops_GHSRI),
				&(state->_hoops_CPSRI),
				state->_hoops_IPSRI);

	/* _hoops_APSHR _hoops_RH _hoops_PPSCP _hoops_IHAH. */
	FREE_ARRAY(state->_hoops_SASRI, state->_hoops_GPSRI, char);
	state->_hoops_SASRI = NULL;
	state->_hoops_GPSRI = 0;
}





/*
* _hoops_SRAC
*/
local bool start_device (
	Display_Context alter	*dc) {

	_hoops_ASCRI alter			*state;

	_hoops_AHCRI("start_device");

	/* _hoops_CCPP _hoops_RHPP _hoops_PIAP _hoops_HRPR */
	ZALLOC (state, _hoops_ASCRI);
	dc->data = (void alter *) state;

	HD_Get_Bit_Patterns (dc, true);

	/* _hoops_RGHR _hoops_HAS/_hoops_GCSR _hoops_HGSR */
	state->_hoops_PSCRI = (FILE alter *)-1;


	return true;
}


/*
* _hoops_SRAC
*/
local void get_physical_info (
	Display_Context alter	*dc) {

	_hoops_ASCRI alter			*state = _hoops_HHSRI (dc);
	float						width, height, left,
											right, top, bottom, _hoops_HAHHH;
	long						_hoops_HHPCP;
	int							i;

	_hoops_AHCRI("get_physical_info");

	/*
	* _hoops_IGIR _hoops_GGR _hoops_SAPSR
	*
	* _hoops_HGI _hoops_PCPH _hoops_IIGS _hoops_HPHS _hoops_AHCA _hoops_RH _hoops_SISS _hoops_IS _hoops_AAPA _hoops_AGAH.
	* _hoops_HGI _hoops_PCPH _hoops_HRGR _hoops_HHASH _hoops_HII _hoops_RII _hoops_AGAH _hoops_SISS _hoops_SPSIR _hoops_GGR _hoops_SGS
	* _hoops_RGR _hoops_PCPH _hoops_PIHA _hoops_ACPA _hoops_RH _hoops_CPHSR _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_SISS _hoops_IS _hoops_IIS
	* _hoops_AGAH _hoops_ACPA _hoops_RSH _hoops_AHPH _hoops_ASPA _hoops_RH _hoops_SISS _hoops_SSCP. _hoops_HSRR _hoops_SGS _hoops_SCPC, _hoops_RH
	* _hoops_CPHSR _hoops_IGIR _hoops_RHPP _hoops_HCSP _hoops_HRGR _hoops_RAICR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_ARP. _hoops_CGP
	* _hoops_SCH _hoops_HRGR, _hoops_RH _hoops_CPHSR _hoops_IGIR _hoops_HRGR _hoops_ARP _hoops_IS _hoops_PSSP _hoops_RH _hoops_RHPP _hoops_HCSP _hoops_PIRA.
	* _hoops_CGP _hoops_RH _hoops_RHPP _hoops_HCSP _hoops_HRGR _hoops_HAR _hoops_ARP, _hoops_IRS _hoops_SHIR _hoops_PIRA _hoops_HRGR _hoops_IGI. _hoops_HPGHR _hoops_GHGA
	* _hoops_SCH _hoops_RGR _hoops_PPRRR, _hoops_RH _hoops_CPHSR _hoops_IGIR _hoops_SAGGR _hoops_ARP _hoops_IS _hoops_SHH _hoops_HISI _hoops_AGAH _hoops_HRGR
	* _hoops_IGRC _hoops_CPIC _hoops_IS _hoops_SGH _hoops_IGH _hoops_RH _hoops_CPHSR _hoops_IGIR _hoops_RHPP _hoops_HCSP
	* _hoops_SSCP _hoops_RPII _hoops_ARP _hoops_PAR _hoops_HAR.
	*/

	/*
	* _hoops_IPCP _hoops_CPHSR _hoops_IGIR _hoops_RGHP _hoops_ARI _hoops_HRGR _hoops_CPSA _hoops_RH "_hoops_GPAAI _hoops_CCAC"
	* _hoops_IIGR _hoops_RH _hoops_SISS _hoops_IH _hoops_IRS _hoops_SAGHR _hoops_IRS _hoops_RPAAI _hoops_IGIR. _hoops_HHIGR _hoops_HRGR _hoops_RH _hoops_CCAC
	* _hoops_ASSA _hoops_GII _hoops_GSIA _hoops_PASHA _hoops_GRAA-_hoops_ISHHH _hoops_APAAI.
	* _hoops_GPGP _hoops_SACRI _hoops_CSHCR, _hoops_SCH _hoops_HRGR _hoops_RH _hoops_CCAC _hoops_PAPR _hoops_HPP _hoops_RH _hoops_SISS'_hoops_GRI
	* _hoops_ACIPR-_hoops_HSPH-_hoops_SAIPR _hoops_SHIR _hoops_SAAA _hoops_RSSA _hoops_PPAAI _hoops_PPR _hoops_HPAAI.
	* _hoops_HHIGR _hoops_HRGR _hoops_ASAI _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_RPAAI.
	* _hoops_IPAAI _hoops_CHR _hoops_SAPSR.
	*/

	/*
	_hoops_GPGP _hoops_PIHRA, _hoops_SR _hoops_CPAAI _hoops_RH _hoops_SPAAI _hoops_GAPA
	_hoops_ICHRR-_hoops_ISHA _hoops_CS _hoops_PPR _hoops_RGRRR-_hoops_ISHA _hoops_CS.	 _hoops_IPCP _hoops_CS _hoops_ISHA _hoops_AGCCA
	_hoops_IS _hoops_RH _hoops_GHAAI _hoops_ISHA _hoops_IIGR _hoops_RH _hoops_GPAAI _hoops_CCAC _hoops_SGS _hoops_RHAAI
	_hoops_HII _hoops_RH _hoops_HRGAI. _hoops_AGAAH _hoops_HRGR _hoops_RH _hoops_SPCC _hoops_IIGR _hoops_RGR _hoops_GHAAI _hoops_ISHA.
	_hoops_PGAAH _hoops_HRGR _hoops_RH _hoops_SPCC _hoops_IIGR _hoops_RH _hoops_GPAAI _hoops_CCAC _hoops_GGR _hoops_RH
	_hoops_HAGA _hoops_SGS _hoops_RH _hoops_RPAAI _hoops_IHCI. _hoops_IPCP _hoops_RPAAI _hoops_IHCI _hoops_GGSR _hoops_IIGR _hoops_RH
	_hoops_SISS _hoops_HPP _hoops_RH _hoops_HCHC _hoops_IIGR _hoops_RH _hoops_APPS _hoops_IPSH _hoops_AHAAI _hoops_HHH
	_hoops_GRAA-_hoops_GPAAI _hoops_HGPC.
	_hoops_PCICP-_hoops_ISHA _hoops_CS (_hoops_PHAAI): _hoops_IGAA < _hoops_APPS
	_hoops_HHAAI-_hoops_ISHA _hoops_CS (_hoops_IHAAI): _hoops_IGAA > _hoops_APPS
	_hoops_SACRI _hoops_CHAAI _hoops_RH _hoops_SAAA _hoops_RSSA _hoops_PPAAI _hoops_PPR _hoops_HPAAI _hoops_PPR _hoops_SHIR
	_hoops_SPCH _hoops_GGR _hoops_HAGH _hoops_IIHP _hoops_IH _hoops_PHAAI _hoops_PPR _hoops_IHAAI _hoops_HIS _hoops_SR _hoops_RRP
	_hoops_IS _hoops_ACPA _hoops_PGAP _hoops_SCH _hoops_HRGR. _hoops_CHSR _hoops_HPP _hoops_PRCA _hoops_GIPR _hoops_SR _hoops_RCRP
	_hoops_RH _hoops_CCRPR _hoops_SHAAI _hoops_RGSHA.
	*/


	/* _hoops_SIPR _hoops_IGAA, _hoops_APPS _hoops_PPR _hoops_APAAI _hoops_SGS _hoops_CCRPR _hoops_SSCP
	* _hoops_GCSS _hoops_GGR _hoops_GIAAI _hoops_HCSP. _hoops_ASC _hoops_CHR _hoops_GGR _hoops_SRPGH.
	*/
	width  = dc->options._hoops_PCPRP[0][0];  /* _hoops_SHIR = 1.0 */
	left   = dc->options._hoops_PCPRP[0][1];  /* _hoops_SHIR = 0.0 */
	right  = dc->options._hoops_PCPRP[1][0];  /* _hoops_SHIR = 0.0 */
	height = dc->options._hoops_PCPRP[1][1];  /* _hoops_SHIR = 1.0 */
	bottom = dc->options._hoops_PCPRP[2][0];  /* _hoops_SHIR = 0.0 */
	top	   = dc->options._hoops_PCPRP[2][1];  /* _hoops_SHIR = 0.0 */

	/* _hoops_IIPI _hoops_SHIR _hoops_IGIR _hoops_ARI _hoops_RGAR _hoops_GGR _hoops_RH _hoops_AGIR _hoops_CGPR _hoops_RH _hoops_SR'_hoops_ASAR _hoops_GRP
	   _hoops_AAPA-_hoops_PAPA _hoops_SHIR _hoops_AAP */
   if ((width < 1.01) && (height < 1.01)) {
	 width = 17.5;
	 height = 22.0;
   }


	/* _hoops_RAP _hoops_AASC _hoops_SHRAI _hoops_PGRR _hoops_ARI _hoops_IIGR 1 _hoops_GHGAI = 0.1 _hoops_SRPGH */
	if (width  < 0.1) width	 = 0.1f;
	if (height < 0.1) height = 0.1f;

	/* _hoops_PHSH _hoops_HCGC */
	if (left   < 0) left   = 0;
	if (right  < 0) right  = 0;
	if (top	   < 0) top	   = 0;
	if (bottom < 0) bottom = 0;

	if (left   > width) left   = width;
	if (right  > width) right  = width;
	if (top	   > height) top	= height;
	if (bottom > height) bottom = height;

	if ((left + right) > width) {
		/* _hoops_RIAAI _hoops_RPHR _hoops_IH _hoops_RAAP.
		*/
		_hoops_HAHHH = right;
		right = width - left;
		left  = width - _hoops_HAHHH;
	}
	if ((bottom + top) > height) {
		/* _hoops_RIAAI _hoops_SCIA _hoops_IH _hoops_PRPC.
		*/
		_hoops_HAHHH  = top;
		top	   = height - bottom;
		bottom = height - _hoops_HAHHH;
	}

	/* _hoops_CGP _hoops_SRGAI _hoops_IGIR _hoops_HRGR < 1 _hoops_GHGAI, _hoops_SRPA _hoops_APAAI.
	*/
	while ((width - right - left) < 0.1f) {
		if (left > 0) {
			left -= 0.1f;
			if (left < 0) left = 0.0f;
		}
		else {
			right -= 0.1f;
			if (right < 0) right = 0.0f;
		}
		if ((left + right) <= 0) break;
	}
	while ((height - top - bottom) < 0.1f) {
		if (bottom > 0) {
			bottom -= 0.1f;
			if (bottom < 0) bottom = 0.0f;
		}
		else {
			top -= 0.1f;
			if (top < 0) top = 0.0f;
		}
		if ((top + bottom) <= 0) break;
	}

	/* _hoops_PSIH _hoops_RH _hoops_SRGAI _hoops_CCAC _hoops_SGS _hoops_HRGR _hoops_ASSA _hoops_RH _hoops_APAAI [_hoops_SRPGH].
	* _hoops_HIPR, _hoops_AGAH _hoops_IRHS _hoops_AGCR _hoops_IS _hoops_ARP _hoops_HSIH _hoops_AIAAI _hoops_IIGR _hoops_IAGH
	*/
	dc->_hoops_PGCC.size.x = width - right - left;
	dc->_hoops_PGCC.size.y = height - top	- bottom;

	/* _hoops_RAP _hoops_RAAA (_hoops_PIAAI) _hoops_IS _hoops_PSSP _hoops_RH
	* _hoops_CCRPR-_hoops_CARSR _hoops_HCSP _hoops_PIRA.
	*/
	state->_hoops_HAP = dc->options._hoops_GHHSR;

	if (dc->options._hoops_SPHSR.x != -1) {
		state->_hoops_GRSRI = dc->options._hoops_SPHSR.y;
		state->_hoops_SGSRI = dc->options._hoops_SPHSR.x;
	} else {
		state->_hoops_GRSRI = dc->_hoops_PGCC.size.y;
		state->_hoops_SGSRI = dc->_hoops_PGCC.size.x;
	}

	dc->current._hoops_HAP.x = state->_hoops_HAP / 2.54f;
	dc->current._hoops_HAP.y = state->_hoops_HAP / 2.54f;
	dc->current._hoops_PRPSR.x = (int) (state->_hoops_HAP * state->_hoops_SGSRI / 2.54f);
	dc->current._hoops_PRPSR.y = (int) (state->_hoops_HAP * state->_hoops_GRSRI / 2.54f);

        /* #11903 _hoops_RGAR _hoops_ARP _hoops_SHIR _hoops_III _hoops_SGCR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_PIP _hoops_IPPSR _hoops_III _hoops_SGCR. */
        if(!dc->options._hoops_HHHSR)
            dc->_hoops_PGCC._hoops_IHHSR = dc->options._hoops_GHHSR/150.0f;

	/* _hoops_APGAI _hoops_IHIGR _hoops_RGAR _hoops_GH _hoops_IS 32767 _hoops_AIR _hoops_PGRAR.
	* _hoops_PHGP _hoops_SR _hoops_PSRAR _hoops_RAAA _hoops_RPP _hoops_SR _hoops_GRS _hoops_IHCC _hoops_RGR.
	*/

	/* _hoops_ACGR _hoops_SGRIR _hoops_SPIS.
	*/
	_hoops_HAHHH = dc->_hoops_PGCC.size.y;
	if (dc->_hoops_PGCC.size.x > _hoops_HAHHH) _hoops_HAHHH = dc->_hoops_PGCC.size.x;
	_hoops_HAHHH /= (float) _hoops_SCCRI;  /* _hoops_AGRP _hoops_IS _hoops_IPIHH, _hoops_PGGA _hoops_RAAA _hoops_HRGR _hoops_PIAAI.*/

	/* _hoops_GPPR _hoops_ISHP _hoops_RAAA _hoops_CCGR _hoops_IGIR _hoops_HIAAI < 32,000  _hoops_ASPA.
	*/
	while (((float)(state->_hoops_HAP) * _hoops_HAHHH) > (float)_hoops_AICRI) {
				state->_hoops_HAP /= 2;
		}

	if (state->_hoops_HAP < 1) {
		/* _hoops_RHHGR _hoops_PIHA _hoops_SHH > 32,000 _hoops_IPIHH !
		*/
		state->_hoops_HAP = 1;
		HE_ERROR (HEC_HPGL2_DRIVER, HES_INVALID_SIZE,
			"Requested print area is too large.");
	}

	/* _hoops_PSIH _hoops_CPHSR _hoops_IGIR _hoops_IIGR _hoops_SISS _hoops_GGR _hoops_ASPA _hoops_IH _hoops_AAPA _hoops_AGAH.
	* _hoops_PAGA _hoops_SR _hoops_GGCR 1.5 _hoops_IS _hoops_GGHC _hoops_GIRR _hoops_PSAP _hoops_PPR _hoops_PIHRA _hoops_IIGR 1.
	*/
	dc->_hoops_PGCC._hoops_PRPSR.x = (int)((dc->_hoops_PGCC.size.x *
		(float)(state->_hoops_HAP) / _hoops_SCCRI) + 1.5);
	dc->_hoops_PGCC._hoops_PRPSR.y = (int)((dc->_hoops_PGCC.size.y *
		(float)(state->_hoops_HAP) / _hoops_SCCRI) + 1.5);

	/*
	* _hoops_ARGH _hoops_RPP _hoops_ISCP _hoops_SIRCP _hoops_SSCP _hoops_PPGP _hoops_SRGAI _hoops_CCAC
	* _hoops_CRGR _hoops_GRAA-_hoops_GPAAI _hoops_CCAC, _hoops_PGAP _hoops_HIRGR _hoops_IIAAI _hoops_CIHH
	* _hoops_PAGA _hoops_SR _hoops_RGAR _hoops_GGCR 0.001 _hoops_CAPP _hoops_IS _hoops_GGHC _hoops_SIRCP _hoops_ISHP, _hoops_HIH
	* _hoops_HGGC _hoops_RGHH _hoops_AIIC _hoops_SHRRR _hoops_SPHS.
	* _hoops_CGP _hoops_CIAAI _hoops_HRGR _hoops_SIGR _hoops_SR _hoops_PSRAR _hoops_RH _hoops_CGRS _hoops_HIS _hoops_SAAA
	* _hoops_SHSGH _hoops_CCCI. _hoops_CGP _hoops_GASAR _hoops_CIAAI _hoops_HRGR _hoops_SIGR, _hoops_SR _hoops_PSRAR
	* _hoops_AIR _hoops_CRRPA. _hoops_SIAAI _hoops_RGAR _hoops_SPR _hoops_AIR _hoops_CIAAI _hoops_HRGR _hoops_SIGR.
	*/
	while ((state->_hoops_PGSRI + (long)(dc->_hoops_PGCC._hoops_PRPSR.x)) >
		(long)((width *
		(float)(state->_hoops_HAP) / _hoops_SCCRI) + 0.001)) {
		if (state->_hoops_PGSRI >  0) {
			state->_hoops_PGSRI -= 1;
		}
		else {
			dc->_hoops_PGCC._hoops_PRPSR.x -= 1;
		}
	}
	while ((state->_hoops_HGSRI + (long)(dc->_hoops_PGCC._hoops_PRPSR.y)) >
		(long)((height *
		(float)(state->_hoops_HAP) / _hoops_SCCRI) + 0.001)) {
		if (state->_hoops_HGSRI >  0) {
			state->_hoops_HGSRI -= 1;
		}
		else {
			dc->_hoops_PGCC._hoops_PRPSR.y -= 1;
		}
	}

	/* _hoops_GCAAI _hoops_ISPR.
	*/
	if (dc->_hoops_PGCC._hoops_PRPSR.y < 1)
		dc->_hoops_PGCC._hoops_PRPSR.y = 1;
	if (dc->_hoops_PGCC._hoops_PRPSR.x < 1)
		dc->_hoops_PGCC._hoops_PRPSR.x = 1;

	/* _hoops_PGIRH _hoops_PGRR _hoops_IS _hoops_AGAH _hoops_GGR _hoops_RCAAI _hoops_HSCHR _hoops_SISR < _hoops_HAPC,
	* _hoops_PGGA _hoops_AGAH _hoops_GRS _hoops_GGSHR _hoops_RPP _hoops_SR _hoops_CHR _hoops_GHGA _hoops_HISGH.
	*/
	if (dc->_hoops_PGCC._hoops_PRPSR.x > dc->_hoops_PGCC._hoops_PRPSR.y) {

		/* _hoops_ACAAI _hoops_PHI _hoops_IIGR _hoops_ASPA.
		*/
		_hoops_HHPCP = dc->_hoops_PGCC._hoops_PRPSR.x;
		dc->_hoops_PGCC._hoops_PRPSR.x = dc->_hoops_PGCC._hoops_PRPSR.y;
		dc->_hoops_PGCC._hoops_PRPSR.y = _hoops_HHPCP;

		/* _hoops_GGSHR _hoops_IGIR */
		_hoops_HAHHH = dc->_hoops_PGCC.size.x;
		dc->_hoops_PGCC.size.x = dc->_hoops_PGCC.size.y;
		dc->_hoops_PGCC.size.y = _hoops_HAHHH;
	}



	/* _hoops_RGAIA _hoops_PAIA _hoops_CHR _hoops_ARP _hoops_GH _hoops_IH 1024 _hoops_HIS _hoops_SRPA _hoops_IIHA _hoops_GPP _hoops_HRGAI _hoops_PSPA.
	* _hoops_SIGP: _hoops_RAH _hoops_SR _hoops_RRP _hoops_IS _hoops_SRPA _hoops_HSGP _hoops_CSRA _hoops_IH _hoops_SISS _hoops_RAAA?
	*/
	dc->_hoops_PGCC._hoops_ICPGH =
		(float)dc->_hoops_PGCC._hoops_PRPSR.x / 1024.0f;

	/* _hoops_RAP _hoops_AAP _hoops_IIHA _hoops_GPP _hoops_PCAAI _hoops_SIH.
	* _hoops_SGAA _hoops_PCAAI _hoops_HII _hoops_AGAH _hoops_HRGR -1.
	*/
	i = dc->options._hoops_AGHRP;
	if (i < 0) i = 0;

	state->_hoops_GGSRI = (i & (int)(_hoops_HHCRI)) ? true : false;

	dc->_hoops_PGCC._hoops_PIHSR = _hoops_SIHSR;
	if (i & (int)(_hoops_IHCRI))
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;

	/* _hoops_RAP _hoops_RII _hoops_CPHSR _hoops_CCPAR
	*/
	dc->_hoops_PGCC._hoops_ARISR.x			= 0;
	dc->_hoops_PGCC._hoops_ARISR.y			= 0;
	dc->_hoops_PGCC._hoops_AAPSR			= 256;
	dc->_hoops_PGCC._hoops_APASR			= 1;
	dc->_hoops_PGCC._hoops_PCHSR	        = 256;
	dc->_hoops_PGCC.flags |= _hoops_GGISR;
	dc->_hoops_PGCC.flags |= _hoops_GIHSR;
	dc->_hoops_PGCC._hoops_CHHSR		= _hoops_SHHSR;
	dc->_hoops_PGCC.driver_type			= "HPGL2";
	dc->_hoops_PGCC._hoops_SCHSR			= "$Revision: 1.73 $";
	dc->_hoops_PGCC.flags &= ~_hoops_HSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;
	dc->_hoops_PGCC._hoops_ASHSR	        = 0;
	dc->_hoops_PGCC.flags &= ~_hoops_PSHSR;
	dc->_hoops_PGCC._hoops_ICHSR			= "HPGL2 device";
	dc->_hoops_PGCC.flags |= _hoops_ISHSR;
	dc->flags |= _hoops_CSHSR;
	dc->_hoops_PGCC.flags |= _hoops_CAPGH;
}

/*
* _hoops_SRAC
*/
local void get_current_info (
	Display_Context alter	*dc) {

	_hoops_ASCRI alter			*state = _hoops_HHSRI (dc);
	float						width, height, left,
											right, top, bottom, _hoops_HAHHH;
	long						_hoops_HHPCP;

	_hoops_AHCRI("get_current_info");

	/*
	* _hoops_RAP _hoops_GPAAI _hoops_IGAA _hoops_PPR _hoops_APPS (_hoops_ACIPR _hoops_HSPH _hoops_CCAC)
	* _hoops_HGI _hoops_HRGR _hoops_CCAC _hoops_IHAIA _hoops_HPP _hoops_SACRI _hoops_AGSHA _hoops_PPAAI _hoops_PPR _hoops_HPAAI
	* _hoops_SHIR _hoops_ACIPR-_hoops_HSPH _hoops_SAAA _hoops_RSSA .
	*/
	if (dc->options._hoops_SPHSR.x == -1) {

		/* _hoops_SIPR _hoops_IGAA, _hoops_APPS _hoops_PPR _hoops_APAAI _hoops_SGS _hoops_CCRPR _hoops_SSCP
		* _hoops_GCSS _hoops_GGR _hoops_GIAAI _hoops_HCSP. _hoops_ASC _hoops_CHR _hoops_GGR _hoops_SRPGH.
		*/
		width  = dc->options._hoops_PCPRP[0][0];  /* _hoops_SHIR = 1.0 */
		left   = dc->options._hoops_PCPRP[0][1];  /* _hoops_SHIR = 0.0 */
		right  = dc->options._hoops_PCPRP[1][0];  /* _hoops_SHIR = 0.0 */
		height = dc->options._hoops_PCPRP[1][1];  /* _hoops_SHIR = 1.0 */
		bottom = dc->options._hoops_PCPRP[2][0];  /* _hoops_SHIR = 0.0 */
		top	   = dc->options._hoops_PCPRP[2][1];  /* _hoops_SHIR = 0.0 */

		/* _hoops_IIPI _hoops_SHIR _hoops_IGIR _hoops_ARI _hoops_RGAR _hoops_GGR _hoops_RH _hoops_AGIR _hoops_CGPR _hoops_RH _hoops_SR'_hoops_ASAR _hoops_GRP
		   _hoops_AAPA-_hoops_PAPA _hoops_SHIR _hoops_AAP */
	   if ((width < 1.01) && (height < 1.01)) {
		 width = 17.5;
		 height = 22.0;
	   }
	}
	else {

		/* _hoops_SIPR _hoops_IGAA, _hoops_APPS _hoops_SGS _hoops_CCRPR _hoops_SSCP _hoops_GCSS _hoops_GGR
		* _hoops_RH _hoops_HCAAI _hoops_HCSP. _hoops_CPSGA _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_SGH _hoops_AGCR
		* _hoops_HSH _hoops_ARI, _hoops_AGAH _hoops_RAIA _hoops_CAPR _hoops_IS _hoops_ARP _hoops_RH _hoops_HSIH _hoops_AHHSR _hoops_IIGR _hoops_RH
		* _hoops_SGRAI _hoops_RPPS, _hoops_PPR _hoops_SCH _hoops_RGAR _hoops_RHAP _hoops_IS _hoops_CIAH _hoops_RPP _hoops_IGAA < _hoops_ICAAI.

		* _hoops_CGP _hoops_IGAA > _hoops_APPS, _hoops_PAR _hoops_SR _hoops_RRP _hoops_IS _hoops_CCAAI _hoops_APAAI, _hoops_PSCR _hoops_GA'_hoops_RA
		* _hoops_SGH _hoops_RH _hoops_HCAAI _hoops_HCSP, _hoops_PPR _hoops_SGH _hoops_GIAAI _hoops_RIIA.
		*/

		width  = dc->options._hoops_SPHSR.x;
		height = dc->options._hoops_SPHSR.y;

		if (width > height) {
			/* _hoops_GGSHR _hoops_IGAA _hoops_IH _hoops_APPS */
			top = width;
			width = height;
			height = top;
		}

		left   = 0.0;
		right  = 0.0;
		bottom = 0.0;
		top	   = 0.0;
	}

	state->_hoops_GRSRI = height;
	state->_hoops_SGSRI = width;

	/* _hoops_RAP _hoops_AASC _hoops_SHRAI _hoops_PGRR _hoops_ARI _hoops_IIGR 1 _hoops_GHGAI = 0.1 _hoops_SRPGH */
	if (width  < 0.1) width	 = 0.1f;
	if (height < 0.1) height = 0.1f;

	/* _hoops_PHSH _hoops_HCGC */
	if (left   < 0) left   = 0;
	if (right  < 0) right  = 0;
	if (top	   < 0) top	   = 0;
	if (bottom < 0) bottom = 0;

	if (left   > width) left   = width;
	if (right  > width) right  = width;
	if (top	   > height) top	= height;
	if (bottom > height) bottom = height;

	if ((left + right) > width) {
		/* _hoops_RIAAI _hoops_RPHR _hoops_IH _hoops_RAAP.
		*/
		_hoops_HAHHH = right;
		right = width - left;
		left  = width - _hoops_HAHHH;
	}
	if ((bottom + top) > height) {
		/* _hoops_RIAAI _hoops_SCIA _hoops_IH _hoops_PRPC.
		*/
		_hoops_HAHHH  = top;
		top	   = height - bottom;
		bottom = height - _hoops_HAHHH;
	}

	/* _hoops_CGP _hoops_SRGAI _hoops_IGIR _hoops_HRGR < 1 _hoops_GHGAI, _hoops_SRPA _hoops_APAAI.
	*/
	while ((width - right - left) < 0.1f) {
		if (left > 0) {
			left -= 0.1f;
			if (left < 0) left = 0.0f;
		}
		else {
			right -= 0.1f;
			if (right < 0) right = 0.0f;
		}
		if ((left + right) <= 0) break;
	}
	while ((height - top - bottom) < 0.1f) {
		if (bottom > 0) {
			bottom -= 0.1f;
			if (bottom < 0) bottom = 0.0f;
		}
		else {
			top -= 0.1f;
			if (top < 0) top = 0.0f;
		}
		if ((top + bottom) <= 0) break;
	}


	/* _hoops_PSIH _hoops_RH _hoops_SRGAI _hoops_CCAC _hoops_SGS _hoops_HRGR _hoops_ASSA _hoops_RH _hoops_APAAI [_hoops_SRPGH].
	* _hoops_HIPR, _hoops_AGAH _hoops_IRHS _hoops_AGCR _hoops_IS _hoops_ARP _hoops_HSIH _hoops_AIAAI _hoops_IIGR _hoops_IAGH
	*/
	dc->current.size.x = width - right - left;
	dc->current.size.y = height - top	- bottom;

	/* _hoops_ACGR _hoops_SGRIR _hoops_SPIS.
	*/
	_hoops_HAHHH = dc->current.size.y;
	if (dc->current.size.x > _hoops_HAHHH)
		_hoops_HAHHH = dc->current.size.x;
	_hoops_HAHHH /= (float) _hoops_SCCRI;  /* _hoops_AGRP _hoops_IS _hoops_IPIHH, _hoops_PGGA _hoops_RAAA _hoops_HRGR _hoops_PIAAI.*/

	/* _hoops_GPPR _hoops_ISHP _hoops_RAAA _hoops_CCGR _hoops_IGIR _hoops_HIAAI < 32,000  _hoops_ASPA.
	*/
	while (((float)(state->_hoops_HAP) * _hoops_HAHHH) > (float)_hoops_AICRI) {
				state->_hoops_HAP /= 2;
		}

	if (state->_hoops_HAP < 1) {
		/* _hoops_RHHGR _hoops_PIHA _hoops_SHH > 32,000 _hoops_IPIHH !
		*/
		state->_hoops_HAP = 1;
		HE_ERROR (HEC_HPGL2_DRIVER, HES_INVALID_SIZE,
			"Requested print area is too large.");
	}

	/* _hoops_PSIH _hoops_CPHSR _hoops_IGIR _hoops_IIGR _hoops_SISS _hoops_GGR _hoops_ASPA _hoops_IH _hoops_AAPA _hoops_AGAH.
	* _hoops_PAGA _hoops_SR _hoops_GGCR 1.5 _hoops_IS _hoops_GGHC _hoops_GIRR _hoops_PSAP _hoops_PPR _hoops_PIHRA _hoops_IIGR 1.
	*/
	dc->current._hoops_PRPSR.x = (int)((dc->current.size.x *
		(float)(state->_hoops_HAP) / _hoops_SCCRI) + 1.5);
	dc->current._hoops_PRPSR.y = (int)((dc->current.size.y *
		(float)(state->_hoops_HAP) / _hoops_SCCRI) + 1.5);


	/* _hoops_RSCS _hoops_CGRS _hoops_ACAGR _hoops_GGR _hoops_ASPA _hoops_IH _hoops_IRGH _hoops_ISRR _hoops_SCAAI.
	* _hoops_GSAAI _hoops_GARIR _hoops_GPP _hoops_PHAAI _hoops_PAR _hoops_IHAAI _hoops_PGGA _hoops_SACRI _hoops_CGRS _hoops_SHPH.
	*/
		state->_hoops_PGSRI = (long)((left *
			(float)(state->_hoops_HAP) / _hoops_SCCRI) + 0.5);
	state->_hoops_HGSRI = (long)((bottom *
		(float)(state->_hoops_HAP) / _hoops_SCCRI) + 0.5);

	/*
	* _hoops_ARGH _hoops_RPP _hoops_ISCP _hoops_SIRCP _hoops_SSCP _hoops_PPGP _hoops_SRGAI _hoops_CCAC
	* _hoops_CRGR _hoops_GRAA-_hoops_GPAAI _hoops_CCAC, _hoops_PGAP _hoops_HIRGR _hoops_IIAAI _hoops_CIHH
	* _hoops_PAGA _hoops_SR _hoops_RGAR _hoops_GGCR 0.001 _hoops_CAPP _hoops_IS _hoops_GGHC _hoops_SIRCP _hoops_ISHP, _hoops_HIH
	* _hoops_HGGC _hoops_RGHH _hoops_AIIC _hoops_SHRRR _hoops_SPHS.
	* _hoops_CGP _hoops_CIAAI _hoops_HRGR _hoops_SIGR _hoops_SR _hoops_PSRAR _hoops_RH _hoops_CGRS _hoops_HIS _hoops_SAAA
	* _hoops_SHSGH _hoops_CCCI. _hoops_CGP _hoops_GASAR _hoops_CIAAI _hoops_HRGR _hoops_SIGR, _hoops_SR _hoops_PSRAR
	* _hoops_AIR _hoops_CRRPA. _hoops_SIAAI _hoops_RGAR _hoops_SPR _hoops_AIR _hoops_CIAAI _hoops_HRGR _hoops_SIGR.
	*/
	while ((state->_hoops_PGSRI + (long)(dc->current._hoops_PRPSR.x)) >
		(long)((width *
		(float)(state->_hoops_HAP) / _hoops_SCCRI) + 0.001)) {
		if (state->_hoops_PGSRI >  0) {
			state->_hoops_PGSRI -= 1;
		}
		else {
			dc->current._hoops_PRPSR.x -= 1;
		}
	}
	while ((state->_hoops_HGSRI + (long)(dc->current._hoops_PRPSR.y)) >
		(long)((height *
		(float)(state->_hoops_HAP) / _hoops_SCCRI) + 0.001)) {
		if (state->_hoops_HGSRI >  0) {
			state->_hoops_HGSRI -= 1;
		}
		else {
			dc->current._hoops_PRPSR.y -= 1;
		}
	}


	/* _hoops_RSCS _hoops_SRGAI _hoops_IGAA _hoops_GGR _hoops_ASPA _hoops_IH _hoops_IRGH _hoops_ISRR _hoops_SCAAI.
	* _hoops_HGI _hoops_HRGR _hoops_IGI _hoops_IH _hoops_SPHR _hoops_ISRR _hoops_ICSA.
	*/
	state->_hoops_IGSRI = dc->current._hoops_PRPSR.x - 1;

	/* _hoops_PAGAR, _hoops_SACRI _hoops_PCRR _hoops_CHR _hoops_HGRAR _hoops_CSCHR _hoops_IS _hoops_APGAI
	* _hoops_PCRR _hoops_RPP _hoops_HSCHR _hoops_IIGR _hoops_CSCR _hoops_HRGR _hoops_RCAAI.
	*/
	state->_hoops_ISCRI =
		dc->options._hoops_ARPSR ? false : true;

	/* _hoops_PGIRH _hoops_PGRR _hoops_IS _hoops_AGAH _hoops_GGR _hoops_RCAAI _hoops_HSCHR _hoops_SISR < _hoops_HAPC,
	* _hoops_PGGA _hoops_AGAH _hoops_GRS _hoops_GGSHR _hoops_RPP _hoops_SR _hoops_CHR _hoops_GHGA _hoops_HISGH.
	*/
	if (dc->current._hoops_PRPSR.x > dc->current._hoops_PRPSR.y) {

		/* _hoops_ACAAI _hoops_PHI _hoops_IIGR _hoops_ASPA.
		*/
		_hoops_HHPCP = dc->current._hoops_PRPSR.x;
		dc->current._hoops_PRPSR.x = dc->current._hoops_PRPSR.y;
		dc->current._hoops_PRPSR.y = _hoops_HHPCP;

		/* _hoops_GGSHR _hoops_IGIR */
		_hoops_HAHHH = dc->current.size.x;
		dc->current.size.x = dc->current.size.y;
		dc->current.size.y = _hoops_HAHHH;
	}
}

/*
* _hoops_SRAC
*/
local POINTER_SIZED_INT get_outer_window (
	Display_Context const	*_hoops_RSAAI) {

	_hoops_ASCRI alter			*state = _hoops_HHSRI (_hoops_RSAAI);
	Display_Context alter	*dc = (Display_Context alter*) _hoops_RSAAI;

	int							i;

	_hoops_AHCRI("get_outer_window");

	/* _hoops_GHRAA _hoops_HCR _hoops_CISRI _hoops_IS _hoops_ACHPP. _hoops_RAH _hoops_RGR _hoops_ARPP _hoops_SR
	*  _hoops_HGRAI _hoops_HCPH _hoops_IS _hoops_RIPGH().
	*/
	for (i=0; i<=_hoops_PICRI; i++) state->pen[i].defined = false;

	/* _hoops_IGS _hoops_IIPR _hoops_RGHR */
	if (!BIT(dc->flags, _hoops_SAISR)) {
		if ((state->_hoops_PSCRI = fopen (dc->_hoops_PCRSR, "wb")) == null) {
			HE_ERROR (HEC_HPGL2_DRIVER, HES_FILE_OPEN,
				"Error opening a file for plotting");
		}
	}

	if (dc->options._hoops_SPHSR.x != -1) {
		dc->_hoops_PGCC.extent.right = state->_hoops_HAP * dc->options._hoops_SPHSR.x / 2.54f;
		dc->_hoops_PGCC.extent.top = state->_hoops_HAP * dc->options._hoops_SPHSR.y / 2.54f;
	} else {
		dc->_hoops_PGCC.extent.right = state->_hoops_HAP * dc->_hoops_PGCC.size.x / 2.54f;
		dc->_hoops_PGCC.extent.top = state->_hoops_HAP * dc->_hoops_PGCC.size.y / 2.54f;
	}
	dc->_hoops_PGCC.extent.left = 0;
	dc->_hoops_PGCC.extent.bottom = 0;

	dc->_hoops_PGCC._hoops_PRPSR.x = (int) (dc->_hoops_PGCC.extent.right);
	dc->_hoops_PGCC._hoops_PRPSR.y = (int) (dc->_hoops_PGCC.extent.top);


	/* _hoops_AGAH _hoops_HRGR _hoops_ASAAI _hoops_RH _hoops_RHPP _hoops_IS _hoops_ASGGR _hoops_RH _hoops_IIPR _hoops_RPPS */
	/* _hoops_IH _hoops_ASCA.	 _hoops_PS _hoops_AA _hoops_ISAP _hoops_ARI. */
	/* _hoops_PSAAI _hoops_RGHR _hoops_CSAP _hoops_AIAH _hoops_HSAAI _hoops_GGR _hoops_APISR() */

	/* _hoops_ASRC _hoops_HSAGA _hoops_IIGR _hoops_SGRAI _hoops_RGHR */
	return ((POINTER_SIZED_INT) state->_hoops_PSCRI);
}



/*
* _hoops_SRAC
*/
local void _hoops_SCCSR (
	Display_Context const	*dc,
	unsigned int				r,
	unsigned int				g,
	unsigned int				b,
	int							index) {

	_hoops_ASCRI alter			*state = _hoops_HHSRI (dc);

	_hoops_AHCRI("set_device_color_map");

	state->pen[index].r = r;
	state->pen[index].g = g;
	state->pen[index].b = b;
	state->pen[index].defined = true;
	state->pen[index].set = false;
}




/*
* _hoops_SRAC
*/
local void init_picture (
	Net_Rendition const &		nr) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_ASCRI alter *	state = _hoops_HHSRI (dc);

	char						string1[64];
	char						string2[64];
	char						_hoops_ASSRI[64];
	float						_hoops_HAHHH;
	long						w, h;

	_hoops_AHCRI("init_picture");

	if (!BIT(dc->flags, _hoops_SAISR)) return;

	/* _hoops_ISAAI: _hoops_IGGAI/2 _hoops_PPR _hoops_CSAAI _hoops_IISRI _hoops_AIAAH _hoops_SSAAI, 3_hoops_IAPPA _hoops_GGPAI, _hoops_RGPAI. 462 */

        state->_hoops_SARSR = (_hoops_SSGSR const *) dc->options._hoops_RCHSR;

	/* _hoops_RHGAR _hoops_CISPP _hoops_GSGR */
	if (dc->options._hoops_HAPIR && _hoops_RCGAI(state, &(dc->options._hoops_HAPIR->name), "INIT")
		!= true) {
		/* _hoops_HSPAA _hoops_SHIR _hoops_CISPP _hoops_GSGR */
		_hoops_SHSRI(state, "\033E");
	}

	/* _hoops_IIPI */
	/* _hoops_PRRAI _hoops_IS _hoops_SACRI (_hoops_RPP _hoops_HAR _hoops_IIH _hoops_AIAH) */
	/* _hoops_PCSH _hoops_AGPAI, _hoops_CCA _hoops_PGPAI _hoops_PSAP (_hoops_HIS _hoops_ICCGR _hoops_PAH _hoops_RGSHA) */
	_hoops_SHSRI(state, "\033%0BBP5,1");

	/* _hoops_HGPAI _hoops_IGPAI _hoops_GGR _hoops_SACRI _hoops_PSPA _hoops_IIGR 1016 _hoops_RIR _hoops_CPIHH _hoops_PAR 400 _hoops_RIR _hoops_SRPGH */
	/* _hoops_IGI _hoops_IH _hoops_CAGA _hoops_IRGAA,	 _hoops_IIAC _hoops_RGR _hoops_RRI _hoops_CGCH _hoops_PPR _hoops_SGGI */
        if(state->_hoops_ISCRI){
	    w = (long)((state->_hoops_GRSRI * 400.0) + 0.9999);
	    h = (long)((state->_hoops_SGSRI  * 400.0) + 0.9999);
        }
        else {
	    h = (long)((state->_hoops_GRSRI * 400.0) + 0.9999);
	    w = (long)((state->_hoops_SGSRI  * 400.0) + 0.9999);
        }
        /*_hoops_HISGH _hoops_HCSP _hoops_ASSP'_hoops_RA _hoops_IPHR.  _hoops_CGPAI _hoops_CIGCP _hoops_GGSR _hoops_HPAGI _hoops_ARI _hoops_PPR _hoops_SGS _hoops_AHPP _hoops_IS _hoops_IPHR _hoops_IH _hoops_SGPAI.. _hoops_HAGC _hoops_RGR _hoops_AA _hoops_RH _hoops_PSHR. */
        w = h = 0;
	Sprintf_LD (string1, "PS%D,", h);
	Sprintf_LD (string2, "%D", w);
	Sprintf_SS (_hoops_ASSRI, "%s%s", string1, string2);
	_hoops_SHSRI(state, _hoops_ASSRI);

	/*_hoops_ICSA _hoops_PSAP */
	/* _hoops_SHIR _hoops_PPAAI, _hoops_HPAAI */
	/* _hoops_IHSP _hoops_GPP (_hoops_HIS _hoops_HSP _hoops_PSHA _hoops_CRGH _hoops_CGPR
	   _hoops_SR _hoops_IIIAA _hoops_AAPI _hoops_CCA _hoops_PAIA) */
	/* _hoops_HASC _hoops_PSAP */
	/* _hoops_IGAA _hoops_PSPA _hoops_IS _hoops_GHGAI */
	_hoops_SHSRI(state,"RO0IPTR1MC0WU0");

	/* _hoops_ARP _hoops_SAAA: _hoops_ARP _hoops_IPSP _hoops_PSPA _hoops_IS _hoops_PSSP _hoops_APGAI _hoops_ASPA
	 * _hoops_PPR _hoops_RAAA */
	_hoops_HAHHH = 1016.0f/(float)state->_hoops_HAP;
	Sprintf_F(string1, "%.6f", _hoops_HAHHH);
	Sprintf_SS(string2, "SC0,%s,0,%s,2;", string1, string1);
	_hoops_SHSRI(state, string2);

	/* _hoops_ARP _hoops_HGGPA _hoops_HAIR _hoops_CCIR. _hoops_HGI _hoops_CGH _hoops_SHH _hoops_SACRI'_hoops_GRI _hoops_SHIR. */
	_hoops_SHSRI(state, "CR0,255,0,255,0,255");

	/* _hoops_PAGA: _hoops_PS _hoops_CRGS _hoops_AGAH _hoops_IS _hoops_SGH _hoops_CISRI 1-255 _hoops_GGR _hoops_GRPAI()
	* _hoops_ASC _hoops_CHR _hoops_PAPR _hoops_IS _hoops_RHPP _hoops_GGR _hoops_RIPGH().
	* _hoops_SPAA _hoops_SR _hoops_ARP _hoops_GGR _hoops_SACRI _hoops_GAR _hoops_SIGR _hoops_GGR _hoops_RRPAI().
	*
	* _hoops_PS _hoops_SGH _hoops_CSGSR 0 _hoops_GAR _hoops_IRS _hoops_IRRHH _hoops_CSGSR, _hoops_ARSSR _hoops_SCH _hoops_GAR _hoops_SIGR
	* _hoops_IH _hoops_PPPSR _hoops_HGGPA _hoops_CHIA _hoops_PSHA.
	*/

	/* _hoops_RAP _hoops_HCR _hoops_CISRI _hoops_IS _hoops_IPPRA _hoops_PPR _hoops_HSPC _hoops_AAGA
	* _hoops_CSIIR _hoops_IS _hoops_ACHPP.
	*/
	_hoops_CRGAI(state);

	/* _hoops_GHRAA _hoops_CGHI _hoops_HSHR _hoops_PIRA _hoops_IS _hoops_IPPRA _hoops_PIAP.
	*/
	state->_hoops_PRSRI = (_hoops_GARRR)0;

	/* _hoops_GHRAA _hoops_HSPH _hoops_CSGAI _hoops_IS _hoops_ACHPP _hoops_PIAP.
	*/
	state->_hoops_CGSRI.right	 = -1;
	state->_hoops_CGSRI.left	 = -1;
	state->_hoops_CGSRI.top	 = -1;
	state->_hoops_CGSRI.bottom = -1;

	/* _hoops_RAP _hoops_PPSCP _hoops_ARPAI _hoops_IS _hoops_ACHPP.
	*/
	state->_hoops_SPSRI	 = state->_hoops_CGSRI;
	state->_hoops_GHSRI		 = state->_hoops_CGSRI;
	state->_hoops_SASRI			 = NULL;
	state->_hoops_GPSRI	 = 0;
	state->_hoops_RPSRI			 = _hoops_CICRI;
	state->_hoops_RPHGH		 = NULL;
	state->_hoops_RHSRI	 = NULL;
	state->_hoops_AHSRI	 = 0;
	state->_hoops_HPSRI = _hoops_RCCRI;
	state->_hoops_PPSRI = _hoops_CICRI;

	/* _hoops_GCIH _hoops_GGSR _hoops_HAR _hoops_GGR _hoops_HIGAI (_hoops_ISII _hoops_PIGAI) _hoops_CCH.
	*/
	state->_hoops_HSCRI = false;

	/* _hoops_HAIA _hoops_AGSHA _hoops_RRP _hoops_IS _hoops_HGRAI _hoops_HPGR _hoops_CHGC _hoops_SPR
	* _hoops_AAGA _hoops_RASIR _hoops_ARPP _hoops_IRS _hoops_PPSCP _hoops_HIS _hoops_PPSI _hoops_SISS _hoops_GGR
	* _hoops_CCPHR _hoops_AAGA/_hoops_PPSCP _hoops_CCH (_hoops_RIIA _hoops_IIGR _hoops_IRS _hoops_HGAI
	* _hoops_PPSCP _hoops_IGRAI _hoops_CCH). _hoops_CGP _hoops_IRS _hoops_AAGA _hoops_IGCI _hoops_SSCP _hoops_RPII
	* _hoops_ARP, _hoops_PSCR _hoops_PRPAI _hoops_GRS _hoops_SHH _hoops_ARP _hoops_IHPR.
	* _hoops_GHRAA _hoops_IS _hoops_RCPP _hoops_ARI.
	*/
	state->_hoops_SSCRI = false;

	/* _hoops_GHRAA _hoops_HSP _hoops_HSGP _hoops_CSIIR.
	* _hoops_RAP _hoops_SGGGH _hoops_IS _hoops_APPR _hoops_IIGR 2 _hoops_GHGAI _hoops_PAR 8 _hoops_ASPA
	* _hoops_RGAIA _hoops_SGCR _hoops_HRGR _hoops_HCAGR 1/6 _hoops_IIGR _hoops_SGGGH.
	*/
	state->_hoops_IASRI =  2; /* _hoops_GGR _hoops_GHGAI */

	while (
		(state->_hoops_HASRI = /* _hoops_GGR _hoops_ASPA _hoops_HRPAI */
		state->_hoops_HAP * state->_hoops_IASRI / 25)
		< 8) {
		state->_hoops_IASRI += 1;
	}

	/* _hoops_AIHH _hoops_IPGAI() _hoops_IH _hoops_IRPAI.
	*/
	state->_hoops_AASRI = /* _hoops_GGR _hoops_ASPA */
		(state->_hoops_HASRI + 3) / 6;
}



/*
* _hoops_SRAC
*/
local void finish_picture (
	Net_Rendition const &		nr,
	bool						swap_buffers) {

	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_ASCRI alter *	state = _hoops_IHSRI (nr);
	UNREFERENCED (swap_buffers);

	_hoops_AHCRI("finish_picture");

	if (!BIT(dc->flags, _hoops_SAISR)) return;

	/* _hoops_RHGAR _hoops_GII _hoops_PPSCP _hoops_SGS _hoops_HRGR _hoops_GGR _hoops_IHAH.
	*/
	if (state->_hoops_SASRI) _hoops_SAAAI(state);



	/* _hoops_APSHR _hoops_RH _hoops_PPSCP _hoops_IHAH _hoops_PPR _hoops_PPSCP _hoops_ACRAA _hoops_SRHR.
	*/
	if (state->_hoops_SASRI != NULL) {
		FREE_ARRAY(state->_hoops_SASRI, state->_hoops_GPSRI, char);
		state->_hoops_SASRI = NULL;
		state->_hoops_GPSRI = 0;
	}
	_hoops_RGAAI(state, (long)0);

	/* _hoops_RSGR _hoops_PPR _hoops_HIAP */
		_hoops_SHSRI(state, ";PUSP0PG;");

		/* _hoops_RHGAR _hoops_RCPHR _hoops_GSGR */
	if (dc->options._hoops_HAPIR && _hoops_RCGAI(state, &(dc->options._hoops_HAPIR->name), "TERM")
		!= true) {
		/* _hoops_HSPAA _hoops_SHIR _hoops_RCPHR _hoops_GSGR */
		_hoops_SHSRI(state, "\033E");
	}
}


/*
* _hoops_SRAC
*/
local void stop_device (
	Display_Context alter *		dc) {
	_hoops_ASCRI alter *	state = _hoops_HHSRI (dc);

	_hoops_AHCRI("stop_device");
	fclose (state->_hoops_PSCRI);
	state->_hoops_PSCRI = null;

	FREE (state, _hoops_ASCRI);
	dc->data = null;
}



/*
* _hoops_PGAA
*/
local void _hoops_CRPAI(
	_hoops_ASCRI alter		*state,
	int						count,
	DC_Point const		*points) {

	long					x, y;

	_hoops_AHCRI("draw_dc_hpgl2_polyline");
	/* _hoops_RIGS _hoops_SACRI _hoops_PGRC */

	/* _hoops_GCIH _hoops_HIGAI _hoops_ISII _hoops_PIGAI _hoops_IRGAA _hoops_RPP
	* _hoops_HAR _hoops_AIAH _hoops_GGR _hoops_HIGAI _hoops_IRGAA _hoops_PIAP.
	*/
	if (!(state->_hoops_HSCRI)) {
			_hoops_SHSRI(state, "PE");
			state->_hoops_HSCRI = true;
	}

	/* _hoops_GAGA _hoops_SRS _hoops_PPSR _hoops_HII _hoops_AGAH _hoops_IS _hoops_SACRI _hoops_PCRR.
	* _hoops_SPAA _hoops_IHIS _hoops_IIH _hoops_RPP _hoops_HAR _hoops_IIH _hoops_AIAH.
	*/
	_hoops_GIGAI(state, &x, &y, points++);
	if ((x != state->_hoops_RGSRI) ||
		(y != state->_hoops_AGSRI)) {
		   _hoops_SHSRI(state, "<");
		   _hoops_RIGAI(state, x, y);
		}
	count--;

	/* _hoops_GISP _hoops_SGHC.
	*/
	while (count--) {
		_hoops_GIGAI(state, &x, &y, points++);
		_hoops_RIGAI(state, x, y);
	}

	state->_hoops_SSCRI = true;
}


/*
* _hoops_SRAC
*/
local void draw_dc_polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	_hoops_ASCRI alter *	state = _hoops_IHSRI (nr);

	_hoops_AHCRI("draw_dc_polyline");

	/* _hoops_SIGP: _hoops_HAGAI _hoops_GGCR _hoops_GRH _hoops_PRCA _hoops_IH _hoops_PAGAI
	* _hoops_PGGA _hoops_SACRI _hoops_SSCP _hoops_SPGC _hoops_CCA _hoops_PAGAI _hoops_IIAC _hoops_IIGR _hoops_APGR
	* _hoops_CCA _hoops_RISA _hoops_III _hoops_HHRP.	_hoops_SRPAI _hoops_IAIR _hoops_GAPAI().
	*/

	/* _hoops_AARS _hoops_RPP _hoops_HAR _hoops_RPHSR _hoops_III _hoops_HSGP */
	if (nr->transform_rendition->_hoops_HCHH != null ||
		!BIT(_hoops_HC->line_style->flags, LSF_SOLID) ||
		ANYBIT((_hoops_HC->style&LCAP_MASK), LCAP_COMPLEX_BITS)) {
		HD_Std_DC_Polyline (nr, count, points);
		return;
	}

	if (state->_hoops_SASRI) _hoops_SAAAI(state);


	if (_hoops_IHCR->_hoops_CPA != state->_hoops_PRSRI) {
		_hoops_PCPSR(state, &(_hoops_IHCR->_hoops_AGAA), _hoops_IHCR->_hoops_CPA);
	}


	/* _hoops_RAP _hoops_HAIR.
	*/
	if (nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		/* _hoops_AIIHP */
		if (_hoops_HC->color._hoops_PGGCR != state->_hoops_RRSRI) {
			_hoops_CGGAI(state, _hoops_HC->color._hoops_PGGCR);
		}
	}
	else {
		/* _hoops_ACRSP */
		if ((state->_hoops_RRSRI == _hoops_HICRI) ||
			(_hoops_HC->color._hoops_HRIR.r != state->_hoops_ARSRI.r) ||
			(_hoops_HC->color._hoops_HRIR.g != state->_hoops_ARSRI.g) ||
			(_hoops_HC->color._hoops_HRIR.b != state->_hoops_ARSRI.b)) {

			_hoops_ARGAI(state, &(_hoops_HC->color._hoops_HRIR));
		}
	}

	/*
	* _hoops_ARGH _hoops_III _hoops_AIRC _hoops_PPR _hoops_ARP _hoops_RPP _hoops_GII _hoops_SHPH.
	*/

	if ((int)0 != state->_hoops_SRSRI) {
		/* _hoops_GGR _hoops_AGIR _hoops_RAPAI _hoops_SSCP _hoops_HGAS _hoops_RGR */
		_hoops_HPGAI(state, 0);
	}

	if (_hoops_HC->weight != state->_hoops_IRSRI) {
		_hoops_ACPSR(state, _hoops_HC->weight);
	}

	if (_hoops_HC->style != state->_hoops_CRSRI) {
		_hoops_CAGAI(state, _hoops_HC->style);
	}


	if (count > 0)
		_hoops_CRPAI(state, count, points);
	else {
		int			_hoops_RRC;

		_hoops_ICHC (count, _hoops_RRC, 2);
		while (count-- > 0) {
			_hoops_CRPAI(state, 2, points);

			points += _hoops_RRC;
		}
	}
}



/*
* _hoops_SRAC
*/
local void draw_dc_colorized_polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						single) {
	_hoops_ASCRI alter *	state = _hoops_IHSRI (nr);
	_hoops_ISC					_hoops_APRRA;
	Net_Rendition				_hoops_AAPAI;
	Line_Rendition				_hoops_PAPAI;
	int							_hoops_RRC;

	_hoops_AHCRI("draw_dc_colorized_polyline");

	if (state->_hoops_SASRI) _hoops_SAAAI(state);

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Colorized_Polyline (nr, count, points, colors, single);
		return;
	}

	/*
	* _hoops_RAP _hoops_HAIR
	*/
	_hoops_APRRA.r = colors->r;
	_hoops_APRRA.g = colors->g;
	_hoops_APRRA.b = colors->b;
	if ((state->_hoops_RRSRI == _hoops_HICRI) ||
		(_hoops_APRRA.r != state->_hoops_ARSRI.r) ||
		(_hoops_APRRA.g != state->_hoops_ARSRI.g) ||
		(_hoops_APRRA.b != state->_hoops_ARSRI.b)) {

		_hoops_ARGAI(state, &_hoops_APRRA);
	}

	/* _hoops_RHRPA _hoops_RGR _hoops_PPSR, _hoops_RH _hoops_CCAH _hoops_HAIR _hoops_SSCP _hoops_RPII _hoops_ARP _hoops_GGR _hoops_SACRI
	* _hoops_HPGR _hoops_RH _hoops_CSGSR _hoops_CIHA _hoops_RCRP _hoops_HPP _hoops_PIAP->_hoops_HAPAI.
	* _hoops_CPR _hoops_SR _hoops_PAH _hoops_AGRP _hoops_RH _hoops_IPP _hoops_IS _hoops_RGR _hoops_SCGH _hoops_HAIR,
	* _hoops_PPR _hoops_PSCR _hoops_AASA _hoops_RH _hoops_GSSR _hoops_IAPAI.
	*/

	/* _hoops_RAP _hoops_GH _hoops_IRGH _hoops_PCIAR _hoops_IIGR _hoops_GCHRR _hoops_IPP _hoops_PPR _hoops_III _hoops_IPP,
	* _hoops_SGS _hoops_CHR _hoops_RH _hoops_PSHR _hoops_GAR _hoops_RH _hoops_CIIA _hoops_HGIIP, _hoops_AHSAR _hoops_SGS
	* _hoops_RH _hoops_III _hoops_IPP _hoops_HAIR _hoops_HRGR _hoops_HGAS _hoops_IS _hoops_RH _hoops_HAPAI
	* _hoops_PAR _hoops_HAIR _hoops_IGPC _hoops_SGS _hoops_CSAP _hoops_ARP _hoops_ARRS.
	*/
	_hoops_AAPAI = nr;
	_hoops_PAPAI = _hoops_AAPAI.Modify()->_hoops_AHP.Modify();

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		_hoops_APRRA.r = colors->r;
		_hoops_APRRA.g = colors->g;
		_hoops_APRRA.b = colors->b;
		if ((_hoops_APRRA.r != state->_hoops_ARSRI.r) ||
			(_hoops_APRRA.g != state->_hoops_ARSRI.g) ||
			(_hoops_APRRA.b != state->_hoops_ARSRI.b)) {

			_hoops_ARGAI(state, &_hoops_APRRA);

			if (nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
				_hoops_PAPAI->color._hoops_PGGCR = state->_hoops_RRSRI;
			}
			else {
				/* _hoops_IH _hoops_ACRSP */
				_hoops_PAPAI->color._hoops_HRIR.r = state->_hoops_ARSRI.r;
				_hoops_PAPAI->color._hoops_HRIR.g = state->_hoops_ARSRI.g;
				_hoops_PAPAI->color._hoops_HRIR.b = state->_hoops_ARSRI.b;
			}
		}

		draw_dc_polyline(_hoops_AAPAI, 2, points);

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
}






/*
* _hoops_PGAA
*/
local void _hoops_CAPAI(
	_hoops_ASCRI alter		*state,
	int						count,
	DC_Point const		*points) {

	long					x, y, _hoops_SAPAI, _hoops_GPPAI;

	_hoops_AHCRI("draw_dc_hpgl2_face");

	/* _hoops_PARAR _hoops_IS _hoops_SRS _hoops_PPSR */
	if (state->_hoops_HSCRI) {
		_hoops_SHSRI(state, "<");
	}
	else {
			_hoops_SHSRI(state, "PE<");
	}

	_hoops_GIGAI(state, &_hoops_SAPAI, &_hoops_GPPAI, points++);
		_hoops_RIGAI(state, _hoops_SAPAI, _hoops_GPPAI);
	count--;

	/* _hoops_GCIH _hoops_HSSP _hoops_CCH */
	_hoops_SHSRI(state, ";PMPE");

	/* _hoops_GISP _hoops_SGHC */
	while (count--) {
		_hoops_GIGAI(state, &x, &y, points++);
		_hoops_RIGAI(state, x, y);
	}

	/* _hoops_HCRS _hoops_ISSC _hoops_IS _hoops_HSPP */
		_hoops_RIGAI(state, _hoops_SAPAI, _hoops_GPPAI);

	/* _hoops_HCSH _hoops_HSSP _hoops_CCH _hoops_PPR _hoops_AA _hoops_RH _hoops_CISA */
		_hoops_SHSRI(state, ";PM2FP");
	state->_hoops_HSCRI = false;

	state->_hoops_SSCRI = true;
}



/*
* _hoops_SRAC
*/
local void draw_dc_face (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_ASCRI alter *	state = _hoops_IHSRI (nr);

	_hoops_AHCRI("draw_dc_face");

	if (state->_hoops_SASRI) _hoops_SAAAI(state);

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Face (nr, count, points);
		return;
	}

	if (_hoops_IHCR->_hoops_CPA != state->_hoops_PRSRI) {
		_hoops_PCPSR(state, &(_hoops_IHCR->_hoops_AGAA), _hoops_IHCR->_hoops_CPA);
	}

	/* _hoops_RAP _hoops_HAIR.
	*/
	if (nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		/* _hoops_AIIHP */
		if (_hoops_SIGA->color._hoops_PGGCR != state->_hoops_RRSRI) {
			_hoops_CGGAI(state, _hoops_SIGA->color._hoops_PGGCR);
		}
	}
	else {
		/* _hoops_ACRSP */
		if ((state->_hoops_RRSRI == _hoops_HICRI) ||
			(_hoops_SIGA->color._hoops_HRIR.r != state->_hoops_ARSRI.r) ||
			(_hoops_SIGA->color._hoops_HRIR.g != state->_hoops_ARSRI.g) ||
			(_hoops_SIGA->color._hoops_HRIR.b != state->_hoops_ARSRI.b)) {

			_hoops_ARGAI(state, &(_hoops_SIGA->color._hoops_HRIR));
		}
	}


	/* _hoops_PHAA, _hoops_ARP _hoops_HSP _hoops_HSGP _hoops_IS _hoops_RPHSR.
	*/
	if (FP_SOLID != state->_hoops_GASRI) {
		/* _hoops_HGI _hoops_GHCA _hoops_AGRP _hoops_RPPAI */
		_hoops_AHPSR (state, FP_SOLID);
	}

	/* _hoops_PAGA: _hoops_APPAI _hoops_HSGP _hoops_HRGR _hoops_HAR _hoops_RGISH _hoops_HPP _hoops_SACRI _hoops_III
	* _hoops_AIRC. _hoops_PHGP _hoops_SR _hoops_AA _hoops_HAR _hoops_RRP _hoops_IS _hoops_ISPR _hoops_PPR _hoops_HIAP _hoops_AGCR _hoops_ARI.
	*/

	/* _hoops_PSAAI _hoops_RH _hoops_RPHSR _hoops_HSP.
	*/
	_hoops_CAPAI(state, count, points);

	/* _hoops_AGGA _hoops_SGRAI _hoops_RH _hoops_HSGP _hoops_IAPR _hoops_RH _hoops_HSP _hoops_RPP _hoops_GII.
	*/
	if (_hoops_SIGA->pattern != FP_SOLID) {
		/* _hoops_RAP _hoops_CGARA _hoops_HAIR.
		*/
		if (nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
			/* _hoops_AIIHP */
			if (_hoops_SIGA->contrast_color._hoops_PGGCR != state->_hoops_RRSRI) {
				_hoops_CGGAI(state, _hoops_SIGA->contrast_color._hoops_PGGCR);
			}
		}
		else {
			/* _hoops_ACRSP */
			if ((state->_hoops_RRSRI == _hoops_HICRI) ||
				(_hoops_SIGA->contrast_color._hoops_HRIR.r != state->_hoops_ARSRI.r) ||
				(_hoops_SIGA->contrast_color._hoops_HRIR.g != state->_hoops_ARSRI.g) ||
				(_hoops_SIGA->contrast_color._hoops_HRIR.b != state->_hoops_ARSRI.b)) {

				_hoops_ARGAI(state, &(_hoops_SIGA->contrast_color._hoops_HRIR));
			}
		}

		/* _hoops_SGGGR _hoops_HSP _hoops_PPPAI _hoops_GHCA _hoops_AGRP _hoops_RPPAI
		*  _hoops_HPPAI, _hoops_PPR _hoops_PGRIP
		*/
		_hoops_AHPSR (state, _hoops_SIGA->pattern);

		if (state->_hoops_RASRI != state->_hoops_SRSRI) {
			_hoops_HPGAI(state, state->_hoops_RASRI);
		}

		if (state->_hoops_AASRI != state->_hoops_IRSRI) {
			_hoops_ACPSR(state, state->_hoops_AASRI);
		}

		if (state->_hoops_PASRI != state->_hoops_CRSRI) {
			_hoops_CAGAI(state, state->_hoops_PASRI);
		}

		/* _hoops_PSAAI _hoops_RH _hoops_PIISR _hoops_HSSP _hoops_CCA _hoops_RH _hoops_HSGP */
		_hoops_SHSRI(state, "FP");
	}
}



/*
* _hoops_SRAC
*/
local void draw_dc_polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	int							_hoops_RRC;

	_hoops_AHCRI("draw_dc_polytriangle");

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Polytriangle (nr, count, points);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		draw_dc_face (nr, 3, points);

		points += _hoops_RRC;
	}
}



/*
* _hoops_SRAC
*/
local void draw_dc_colorized_face (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				color) {

	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_ASCRI alter *	state = _hoops_IHSRI (nr);
	_hoops_ISC					_hoops_APRRA;

	_hoops_AHCRI("draw_dc_colorized_face");

	if (state->_hoops_SASRI) _hoops_SAAAI(state);

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Colorized_Face (nr, count, points, color);
		return;
	}

	if (color != NULL) {
		_hoops_APRRA.r = color->r;
		_hoops_APRRA.g = color->g;
		_hoops_APRRA.b = color->b;
	}
	else {
		/* _hoops_CGP _hoops_ARI, _hoops_SR _hoops_HPCAR _hoops_SR _hoops_CHR _hoops_HGGC _hoops_GHHS _hoops_AIHSR _hoops_HAIR
		_hoops_HII _hoops_HSP _hoops_IPP _hoops_PPR _hoops_HAR _hoops_CGAS _hoops_HAIR. */
		_hoops_APRRA = _hoops_SIGA->color._hoops_HRIR;
	}

	if ((state->_hoops_RRSRI == _hoops_HICRI) ||
		(_hoops_APRRA.r != state->_hoops_ARSRI.r) ||
		(_hoops_APRRA.g != state->_hoops_ARSRI.g) ||
		(_hoops_APRRA.b != state->_hoops_ARSRI.b)) {
		_hoops_ARGAI(state, &_hoops_APRRA);
	}

	if (_hoops_IHCR->_hoops_CPA != state->_hoops_PRSRI) {
		_hoops_PCPSR(state, &(_hoops_IHCR->_hoops_AGAA), _hoops_IHCR->_hoops_CPA);
	}

	/* _hoops_PHAA, _hoops_ARP _hoops_HSP _hoops_HSGP _hoops_IS _hoops_RPHSR.
	*/
	if (FP_SOLID != state->_hoops_GASRI) {
		/* _hoops_HGI _hoops_GHCA _hoops_AGRP _hoops_RPPAI */
		_hoops_AHPSR (state, FP_SOLID);
	}

	/* _hoops_PAGA: _hoops_APPAI _hoops_HSGP _hoops_HRGR _hoops_HAR _hoops_RGISH _hoops_HPP _hoops_SACRI _hoops_III
	* _hoops_AIRC. _hoops_PHGP _hoops_SR _hoops_AA _hoops_HAR _hoops_RRP _hoops_IS _hoops_ISPR _hoops_PPR _hoops_HIAP _hoops_AGCR _hoops_ARI.
	*/

	/* _hoops_PSAAI _hoops_RH _hoops_RPHSR _hoops_HSP.
	*/
	_hoops_CAPAI(state, count, points);

	/* _hoops_AGGA _hoops_SGRAI _hoops_RH _hoops_HSGP _hoops_IAPR _hoops_RH _hoops_HSP _hoops_RPP _hoops_GII.
	*/
	if (_hoops_SIGA->pattern != FP_SOLID) {
	   /* _hoops_RAP _hoops_CGARA _hoops_HAIR.
		* _hoops_HR _hoops_SGS _hoops_RH _hoops_CGARA _hoops_HAIR _hoops_IISA _hoops_GAR _hoops_PCCP _hoops_CIHA _hoops_PAR
		* _hoops_PPPSR _hoops_AIHSR _hoops_GPGA _hoops_GPP _hoops_RH _hoops_HAIR _hoops_GHARR, _hoops_PRGI _hoops_PHRI
		* _hoops_RH _hoops_HSP _hoops_HAIR _hoops_SHR _hoops_IISA _hoops_GAR _hoops_AIHSR _hoops_GGR "_hoops_HAIR".
		*/
		if (nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
			/* _hoops_AIIHP */
			if (_hoops_SIGA->contrast_color._hoops_PGGCR != state->_hoops_RRSRI) {
				_hoops_CGGAI(state, _hoops_SIGA->contrast_color._hoops_PGGCR);
			}
		}
		else {
			/* _hoops_ACRSP */
			if ((state->_hoops_RRSRI == _hoops_HICRI) ||
				(_hoops_SIGA->contrast_color._hoops_HRIR.r != state->_hoops_ARSRI.r) ||
				(_hoops_SIGA->contrast_color._hoops_HRIR.g != state->_hoops_ARSRI.g) ||
				(_hoops_SIGA->contrast_color._hoops_HRIR.b != state->_hoops_ARSRI.b)) {

				_hoops_ARGAI(state, &(_hoops_SIGA->contrast_color._hoops_HRIR));
			}
		}

		/* _hoops_SGGGR _hoops_HSP _hoops_PPPAI _hoops_GHCA _hoops_AGRP _hoops_RPPAI
		*  _hoops_HPPAI, _hoops_PPR _hoops_PGRIP
		*/
		_hoops_AHPSR (state, _hoops_SIGA->pattern);

		if (state->_hoops_RASRI != state->_hoops_SRSRI) {
			_hoops_HPGAI(state, state->_hoops_RASRI);
		}

		if (state->_hoops_AASRI != state->_hoops_IRSRI) {
			_hoops_ACPSR(state, state->_hoops_AASRI);
		}

		if (state->_hoops_PASRI != state->_hoops_CRSRI) {
			_hoops_CAGAI(state, state->_hoops_PASRI);
		}

		/* _hoops_PSAAI _hoops_RH _hoops_PIISR _hoops_HSSP _hoops_CCA _hoops_RH _hoops_HSGP */
		_hoops_SHSRI(state, "FP");
	}
}





/*
* _hoops_SRAC
*/
local void draw_dc_colorized_polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						single) {
	int							_hoops_RRC;

	_hoops_AHCRI("draw_dc_colorized_polytriangle");

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Colorized_Polytris (nr, count, points, colors, single);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		draw_dc_colorized_face (nr, 3, points, colors);

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
}




/*
* _hoops_SRAC
*/
local void _hoops_CCCSR (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	unsigned char const *		rasters) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ASCRI alter *	state = _hoops_IHSRI (nr);
	Int_Rectangle				_hoops_AGRAI;

	_hoops_AHCRI("draw_dc_mapped8_rasters");

	/* _hoops_IICRI _hoops_IPPAI:
	* _hoops_AGAH _hoops_AAGAI _hoops_CSPAA _hoops_CPPPR _hoops_RISA _hoops_AHRH _hoops_PGAP, _hoops_RPP _hoops_CHHHP
	* _hoops_RSRGR, _hoops_ARPR _hoops_IRS _hoops_AHCPR _hoops_IIGR _hoops_ACCGI _hoops_IH _hoops_RH _hoops_SACRI _hoops_SISS.
	* _hoops_PHGP, _hoops_SR _hoops_IHAH _hoops_AHRH _hoops_CRGR _hoops_SPR _hoops_SGRIR _hoops_PPSCP _hoops_CCGR:
	*	_hoops_PHGSP _hoops_IIGR _hoops_CCAH _hoops_PPSCP _hoops_IRIRA _hoops_RH _hoops_AHPA _hoops_PHGSP _hoops_IH
	*	 _hoops_RH _hoops_PIAH _hoops_PPSCP, _hoops_PAR
	*	_hoops_APGAI _hoops_HCPH _hoops_IH _hoops_HPIH _hoops_PGSA _hoops_ACPH _hoops_PAR _hoops_GPRR _hoops_IIGR _hoops_PPSCP, _hoops_PAR
	*	_hoops_SR _hoops_PAH'_hoops_RA _hoops_CCPP _hoops_PPGS _hoops_IS _hoops_IHAH _hoops_RH _hoops_PPSCP.
	*/

	if (state->_hoops_GGSRI) return;
   /* _hoops_PSIH _hoops_SACH _hoops_PHGSP _hoops_IIGR _hoops_RH _hoops_PPSCP
	*/
	_hoops_AGRAI.top	   = (int) start->y;
	_hoops_AGRAI.left   = (int) start->x;
	_hoops_AGRAI.bottom = (int) end->y;
	_hoops_AGRAI.right  = (int) end->x;
	if (_hoops_AGRAI.bottom < _hoops_IHCR->_hoops_AGAA.bottom)
		_hoops_AGRAI.bottom = _hoops_IHCR->_hoops_AGAA.bottom;
	if (_hoops_AGRAI.top	   > _hoops_IHCR->_hoops_AGAA.top)
		_hoops_AGRAI.top	   = _hoops_IHCR->_hoops_AGAA.top;
	if (_hoops_AGRAI.left   < _hoops_IHCR->_hoops_AGAA.left)
		_hoops_AGRAI.left   = _hoops_IHCR->_hoops_AGAA.left;
	if (_hoops_AGRAI.right  > _hoops_IHCR->_hoops_AGAA.right)
		_hoops_AGRAI.right  = _hoops_IHCR->_hoops_AGAA.right;

	/* _hoops_HRHP _hoops_HCRAI _hoops_AHRH.
	*/
	if (_hoops_AGRAI.top	  < _hoops_AGRAI.bottom) return;
	if (_hoops_AGRAI.right < _hoops_AGRAI.left)	return;

	/* _hoops_ARGH _hoops_RPP _hoops_SR _hoops_RRP _hoops_SR _hoops_RRP _hoops_IRS _hoops_CCAH _hoops_IHAH _hoops_IS _hoops_ASH _hoops_RGR _hoops_PPSCP.
	*/
	if ((state->_hoops_SASRI == NULL) ||
		(state->_hoops_RPSRI != _hoops_SICRI) ||
		(state->_hoops_SPSRI.right  < _hoops_AGRAI.right) ||
		(state->_hoops_SPSRI.left	  > _hoops_AGRAI.left)  ||
		(state->_hoops_SPSRI.top	  < _hoops_AGRAI.top)   ||
		(state->_hoops_SPSRI.bottom > _hoops_AGRAI.bottom)) {

		/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IGS _hoops_IRS _hoops_CCAH _hoops_PPSCP _hoops_IHAH.
		*/
		if (state->_hoops_SASRI != NULL) _hoops_SAAAI(state);

		if (_hoops_GPRAI(_hoops_IHCR, state, &_hoops_AGRAI, _hoops_SICRI) != true) {
			_hoops_CGAAI(state, start, end, row_bytes, rasters,
						_hoops_SICRI, &_hoops_AGRAI,
						&(_hoops_IHCR->_hoops_AGAA), _hoops_IHCR->_hoops_CPA);
			return;
		}
	}

	/* _hoops_RGPA _hoops_PPSCP _hoops_IS _hoops_RH _hoops_IHAH.
	*/
	_hoops_ACRAI(state, start, end, row_bytes, rasters,
		_hoops_SICRI, &_hoops_AGRAI);
}



/*
* _hoops_SRAC
*/
local void draw_dc_rgb32_rasters (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	RGBAS32 const *				rasters) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ASCRI alter *	state = _hoops_IHSRI (nr);
	Int_Rectangle				_hoops_AGRAI;

	_hoops_AHCRI("draw_dc_rgb32_rasters");

	/* _hoops_IICRI _hoops_IPPAI:
	* _hoops_AGAH _hoops_AAGAI _hoops_CSPAA _hoops_CPPPR _hoops_RISA _hoops_AHRH _hoops_PGAP, _hoops_RPP _hoops_CHHHP
	* _hoops_RSRGR, _hoops_ARPR _hoops_IRS _hoops_AHCPR _hoops_IIGR _hoops_ACCGI _hoops_IH _hoops_RH _hoops_SACRI _hoops_SISS.
	* _hoops_PHGP, _hoops_SR _hoops_IHAH _hoops_AHRH _hoops_CRGR _hoops_SPR _hoops_SGRIR _hoops_PPSCP _hoops_CCGR:
	*	_hoops_PHGSP _hoops_IIGR _hoops_CCAH _hoops_PPSCP _hoops_IRIRA _hoops_RH _hoops_AHPA _hoops_PHGSP _hoops_IH
	*	 _hoops_RH _hoops_PIAH _hoops_PPSCP, _hoops_PAR
	*	_hoops_APGAI _hoops_HCPH _hoops_IH _hoops_HPIH _hoops_PGSA _hoops_ACPH _hoops_PAR _hoops_GPRR _hoops_IIGR _hoops_PPSCP, _hoops_PAR
	*	_hoops_SR _hoops_PAH'_hoops_RA _hoops_CCPP _hoops_PPGS _hoops_IS _hoops_IHAH _hoops_RH _hoops_PPSCP.
	*/

	if (state->_hoops_GGSRI) return;

	/* _hoops_PSIH _hoops_SACH _hoops_PHGSP _hoops_IIGR _hoops_RH _hoops_PPSCP
	*/
	_hoops_AGRAI.top	   = (int) start->y;
	_hoops_AGRAI.left   = (int) start->x;
	_hoops_AGRAI.bottom = (int) end->y;
	_hoops_AGRAI.right  = (int) end->x;
	if (_hoops_AGRAI.bottom < _hoops_IHCR->_hoops_AGAA.bottom)
		_hoops_AGRAI.bottom = _hoops_IHCR->_hoops_AGAA.bottom;
	if (_hoops_AGRAI.top	   > _hoops_IHCR->_hoops_AGAA.top)
		_hoops_AGRAI.top	   = _hoops_IHCR->_hoops_AGAA.top;
	if (_hoops_AGRAI.left   < _hoops_IHCR->_hoops_AGAA.left)
		_hoops_AGRAI.left   = _hoops_IHCR->_hoops_AGAA.left;
	if (_hoops_AGRAI.right  > _hoops_IHCR->_hoops_AGAA.right)
		_hoops_AGRAI.right  = _hoops_IHCR->_hoops_AGAA.right;

	/* _hoops_HRHP _hoops_HCRAI _hoops_AHRH.
	*/
	if (_hoops_AGRAI.top	  < _hoops_AGRAI.bottom) return;
	if (_hoops_AGRAI.right < _hoops_AGRAI.left)	return;

	/* _hoops_ARGH _hoops_RPP _hoops_SR _hoops_RRP _hoops_SR _hoops_RRP _hoops_IRS _hoops_CCAH _hoops_IHAH _hoops_IS _hoops_ASH _hoops_RGR _hoops_PPSCP.
	*/
	if ((state->_hoops_SASRI == NULL) ||
		(state->_hoops_RPSRI != _hoops_GCCRI) ||
		(state->_hoops_SPSRI.right  < _hoops_AGRAI.right) ||
		(state->_hoops_SPSRI.left	  > _hoops_AGRAI.left)  ||
		(state->_hoops_SPSRI.top	  < _hoops_AGRAI.top)   ||
		(state->_hoops_SPSRI.bottom > _hoops_AGRAI.bottom)) {

		/* _hoops_PS _hoops_RRP _hoops_IS _hoops_IGS _hoops_IRS _hoops_CCAH _hoops_PPSCP _hoops_IHAH.
		*/
		if (state->_hoops_SASRI != NULL) _hoops_SAAAI(state);

		if (_hoops_GPRAI(_hoops_IHCR, state, &_hoops_AGRAI, _hoops_GCCRI) != true) {
			_hoops_CGAAI(state, start, end, row_bytes, rasters,
						_hoops_GCCRI, &_hoops_AGRAI,
						&(_hoops_IHCR->_hoops_AGAA), _hoops_IHCR->_hoops_CPA);
			return;
		}
	}

	/* _hoops_RGPA _hoops_PPSCP _hoops_IS _hoops_RH _hoops_IHAH.
	*/
	_hoops_ACRAI(state, start, end, row_bytes, rasters,
				_hoops_GCCRI, &_hoops_AGRAI);
}

/*
* _hoops_SRAC
*/
local void _hoops_RSCSR (
	_hoops_APARR alter &		_hoops_RRCI) {

	_hoops_RRCI->start_device			= start_device;
	_hoops_RRCI->get_physical_info			= get_physical_info;
	_hoops_RRCI->get_outer_window			= get_outer_window;
	_hoops_RRCI->get_current_info			= get_current_info;
	_hoops_RRCI->init_picture			= init_picture;
	_hoops_RRCI->finish_picture			= finish_picture;
	_hoops_RRCI->stop_device				= stop_device;

	_hoops_RRCI->draw_dc_polyline			= draw_dc_polyline;
	_hoops_RRCI->draw_dc_colorized_polyline          = draw_dc_colorized_polyline;
	_hoops_RRCI->draw_dc_face			= draw_dc_face;
	_hoops_RRCI->draw_dc_colorized_face		= draw_dc_colorized_face;
	_hoops_RRCI->draw_dc_polytriangle		= draw_dc_polytriangle;
	_hoops_RRCI->draw_dc_colorized_polytriangle      = draw_dc_colorized_polytriangle;
	_hoops_RRCI->_hoops_CCCSR		= _hoops_CCCSR;
	_hoops_RRCI->draw_dc_rgb32_rasters		= draw_dc_rgb32_rasters;
	_hoops_RRCI->_hoops_SCCSR		= _hoops_SCCSR;
}

extern "C"  bool HC_CDECL HD_HPGL2_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR);
}

/*
* _hoops_ASCSR _hoops_RARP _hoops_PPSR (_hoops_IGI _hoops_GPP _hoops_PSCSR)
*/
_hoops_HSCSR (_hoops_RSCSR)

#endif /* _hoops_CPPAI */
