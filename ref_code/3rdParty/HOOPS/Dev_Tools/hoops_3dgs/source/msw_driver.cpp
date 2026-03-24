/*
 * Copyright (c) 1998-2001, 2002 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.790 2011-01-07 22:05:47 reuben Exp $
 */

#ifdef _hoops_GAACI
#undef _hoops_GAACI
#endif
#define _hoops_GAACI 0x0501

#include "windows_wrapper.h"	// _hoops_CGRI <_hoops_SPHGR._hoops_GGHR>, _hoops_PIHA _hoops_RCPS _hoops_SRS :(


#include "hoops.h"
#include "hd_proto.h"


#ifndef MSW_DRIVER


/*
 * _hoops_APICR _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_MSW_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED(request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "msw");
}

#else

#include "database.h"
#include "driver.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "please.h"
#include "searchh.h"
#include "hversion.h"
#include "msw.h"
#include "hi_proto.h"
#ifndef _WIN32_WCE
#include <mbstring.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#undef CONST

/*
 * _hoops_RAACI _hoops_IS _hoops_AAACI _hoops_PAACI _hoops_IH _hoops_IHAGH _hoops_AGAH _hoops_HAACI
 */
#define IDM_ABOUT		104

/*
 * _hoops_RACRR _hoops_SGI _hoops_GGR _hoops_CSPH->_hoops_AAP._hoops_HISRA
 * _hoops_ASC _hoops_CHR _hoops_IGI _hoops_HPP _hoops_IAACI ("_hoops_HISRA = _hoops_PGGIR");
 */

/* _hoops_CAACI _hoops_HRGR _hoops_IGI _hoops_IS _hoops_GGHC _hoops_AGAH _hoops_SPHGR _hoops_RHPP
 * _hoops_IS _hoops_IIPR _hoops_RHASR _hoops_GAR _hoops_RPP _hoops_RH _hoops_SISS _hoops_HRGR _hoops_IHIR _hoops_HAIR - _hoops_CSGRH
 * _hoops_GRS _hoops_HAR _hoops_GPHCR - _hoops_SISS _hoops_GRS _hoops_RPGAH _hoops_IS _hoops_HS _hoops_PSP _hoops_IHCRH _hoops_PPR
 * 16777216 _hoops_PSHA - _hoops_RGR _hoops_GRS _hoops_IHSH _hoops_CPPPR _hoops_AHCI _hoops_GPP _hoops_IRS _hoops_SAACI _hoops_SISS _hoops_PPR _hoops_HRGR
 * _hoops_SCGAH _hoops_RSARA _hoops_IH _hoops_GPACI _hoops_IH _hoops_ISHHH _hoops_PPR _hoops_IRIRR - _hoops_RPACI
 */
#define _hoops_APACI							0x00000010

/*
 * _hoops_PPACI _hoops_CHR _hoops_IGI _hoops_HIS _hoops_SGS _hoops_RH _hoops_IPSP _hoops_GHCA _hoops_HSPAA _hoops_PAII _hoops_HAII
 * _hoops_GRGAI _hoops_PGPCR _hoops_GCPPI _hoops_PPR _hoops_GSRS _hoops_PAII _hoops_HAII _hoops_RIHH _hoops_PRCA _hoops_GGR _hoops_SGH _hoops_RPPS _hoops_RCC
 * _hoops_HAACI
 */
#define _hoops_HPACI						0x00000020

/*
 * _hoops_IPACI _hoops_HRGR _hoops_ARSAR _hoops_HIS _hoops_SGS _hoops_SSHSR _hoops_PAH _hoops_CRGS _hoops_IHHH _hoops_HAR _hoops_IS _hoops_PSSRH _hoops_CRGR
 * _hoops_RH _hoops_GPSRR _hoops_GSSHR _hoops_IH _hoops_IRS _hoops_RPPS - _hoops_RGR _hoops_AGSR _hoops_SGS _hoops_RH _hoops_IPSP _hoops_PIHA _hoops_HPPP
 * _hoops_HCSRH _hoops_SSHRH _hoops_PPR _hoops_AASA _hoops_CPACI _hoops_CGPR _hoops_SSIA _hoops_HHGC _hoops_CHARP _hoops_IS _hoops_PGSA
 * _hoops_CRGR _hoops_RH _hoops_ARSAR _hoops_RPPS
 */
#define _hoops_GCCRH							0x00000040

/*
 * _hoops_IPCP _hoops_SPACI _hoops_HIRGR _hoops_IHHH _hoops_IS _hoops_PGSA _hoops_RH _hoops_SPPR _hoops_IIGR _hoops_PCHC _hoops_RPHSR _hoops_AGSAR
 * (_hoops_HGPP _hoops_GAR _hoops_SAIA) _hoops_CCA _hoops_IRS _hoops_RPHSR _hoops_CSGSR - _hoops_RGR _hoops_APPP _hoops_PICP _hoops_IIGR _hoops_IRS _hoops_ARPC
 * _hoops_SR _hoops_HS _hoops_GHACI _hoops_CAS _hoops_SPHGR _hoops_GRS _hoops_HAR _hoops_PGSA _hoops_ASPA _hoops_PGAP _hoops_HSSC _hoops_GPP _hoops_IRS
 * _hoops_CAPS _hoops_III
 */
#define _hoops_RHACI								0x00000080

/*
 * _hoops_AHACI _hoops_RIP _hoops_HIRGR _hoops_RH _hoops_RHPP _hoops_IS _hoops_CICA _hoops_RH _hoops_HCGR _hoops_PPR
 * _hoops_IGHP _hoops_PSHA _hoops_GPP _hoops_PCHC _hoops_PGSA _hoops_RHASR - _hoops_RGR _hoops_HRGR _hoops_IS _hoops_PPGR
 * _hoops_IH _hoops_PRRIR _hoops_GRRII _hoops_GGR _hoops_HHH _hoops_SPHGR _hoops_SISS _hoops_SPSIR (_hoops_SCRPR. _hoops_HHH _hoops_PHACI)
 */
#define _hoops_HHACI						0x00000100

/*
 * _hoops_IHACI	_hoops_ARCSA _hoops_AGAH _hoops_HAR _hoops_IS _hoops_SGH _hoops_RGCI _hoops_SHPP _hoops_HSPH _hoops_HGRH
 * _hoops_IH _hoops_GPACI - _hoops_RGR _hoops_GRS _hoops_GGHC _hoops_PCHC _hoops_IAGH _hoops_IIGR _hoops_RH _hoops_CSCR _hoops_IS _hoops_IHCC
 * _hoops_RH _hoops_SSSHR _hoops_IIRRH _hoops_GPP _hoops_RH _hoops_CHACI _hoops_CSCR _hoops_CR _hoops_RH _hoops_SPHGR _hoops_SHACI
 * _hoops_SGS _hoops_SR _hoops_GIACI _hoops_GPP _hoops_RH _hoops_CHACI _hoops_AA _hoops_HAR _hoops_GCGH _hoops_CIHH.	_hoops_IGHS _hoops_RH _hoops_SHPP
 * _hoops_CIHH _hoops_HGRH _hoops_PAH _hoops_GGHC _hoops_HHH _hoops_ISHA _hoops_CARA (_hoops_SHPCA. _hoops_SAIA _hoops_GRPAA _hoops_RHCH _hoops_CHR
 * _hoops_PSAP _hoops_SHPR) _hoops_HAR _hoops_IS _hoops_SHH _hoops_CHCC.	 _hoops_GPGP _hoops_PGI _hoops_AGIR _hoops_PSP _hoops_RIACI _hoops_RHASR _hoops_CHR _hoops_AGCA
 * _hoops_GGR _hoops_RH _hoops_SCRII _hoops_CR _hoops_SPHGR _hoops_SAHR _hoops_AIACI _hoops_GH
 */
#define _hoops_PIACI					0x00000200

/*
 * _hoops_HIACI - _hoops_RGR _hoops_HCSP _hoops_GRS _hoops_IGRC _hoops_GGHC _hoops_PPSCP _hoops_GPRR
 * _hoops_CSCR _hoops_IS _hoops_AIRI _hoops_RRI _hoops_PCACR _hoops_HIH _hoops_GRS _hoops_HASIR _hoops_RAHRH _hoops_IIACI _hoops_SGS
 * _hoops_RH _hoops_IPSP _hoops_CIACI _hoops_GAR _hoops_SPAC - _hoops_SIACI _hoops_HAR _hoops_IS _hoops_SHH _hoops_ARP
 */
#define _hoops_GCACI								0x00000800

/*
 * _hoops_RCACI
 */
#define _hoops_ACACI									0x00000400

/*
 * _hoops_PCACI - _hoops_HCAGR _hoops_HAR _hoops_IGI _hoops_HIH _hoops_PSIGA _hoops_CGPR
 * _hoops_HCACI _hoops_HPIC _hoops_PAII _hoops_HAII _hoops_IHCRH
 */
#define _hoops_ICACI						0x00002000


/*
 * _hoops_CCACI - _hoops_IGI _hoops_IS _hoops_CRGS _hoops_AGAH _hoops_SGS _hoops_SCACI _hoops_HRGR _hoops_CISI _hoops_PPR
 * _hoops_SR _hoops_CHR _hoops_CCCH _hoops_IS _hoops_IRS _hoops_GSACI.	 _hoops_RSACI _hoops_HIS _hoops_SGS _hoops_SR _hoops_ACPA _hoops_IS _hoops_SAIPR _hoops_RH _hoops_SCACI
 * _hoops_CSCR _hoops_IGIR _hoops_IS 64_hoops_ARGI _hoops_PPR _hoops_ASACI
 */
#define _hoops_PSACI							0x00004000

/*
 * _hoops_HSACI - _hoops_HGI _hoops_HRGR _hoops_IGI _hoops_RPP _hoops_RH _hoops_IPSP _hoops_APSI
 * _hoops_PPGS _hoops_GGAPH _hoops_HPP _hoops_AGAH - _hoops_IPIH _hoops_IGI _hoops_HPP _hoops_ISACI
 *
 * _hoops_HGI _hoops_HRGR _hoops_HA _hoops_ARP _hoops_GGR _hoops_RH _hoops_RHPP _hoops_RPP _hoops_SR _hoops_CHR _hoops_ISHHH
 * _hoops_PGGA _hoops_CSACI _hoops_SSACI _hoops_IIGR _hoops_SRHR _hoops_PPGS _hoops_CSAP _hoops_GGPCI
 * _hoops_GPP _hoops_ISHHH _hoops_ARPP
 */
#define _hoops_RGPCI					0x00008000

/*
 * _hoops_AGPCI - _hoops_AA _hoops_HAR _hoops_CAHP
 * _hoops_IRS _hoops_PGPCI _hoops_GPP _hoops_IRS _hoops_IHCRH _hoops_AGRP, _hoops_RGR _hoops_HGPCI _hoops_RH _hoops_PHI _hoops_IIGR
 * _hoops_IGPCI _hoops_HIH _hoops_CICAA _hoops_GCGP _hoops_IGHP _hoops_RPPS _hoops_CGPCI (_hoops_PSIGA _hoops_RPP
 * _hoops_IGPCI _hoops_CHR _hoops_CPPPR _hoops_IHPH--_hoops_SGPCI/_hoops_RCPGP)
 */
#define _hoops_GRPCI				0x00010000

/*
 * _hoops_RRPCI _hoops_ARPCI _hoops_HAR _hoops_GGSP _hoops_HA
 * _hoops_PRPCI - _hoops_HRPCI _hoops_IHHH _hoops_SGS _hoops_IIH
 * _hoops_GRS _hoops_SHH _hoops_PSP _hoops_AHRH _hoops_ICPAA _hoops_ISHP _hoops_IS _hoops_RH _hoops_RHPP _hoops_IH _hoops_ISHHH.
 * _hoops_CGP _hoops_RGR _hoops_HRGR _hoops_HAR _hoops_ARP, _hoops_RHPP _hoops_GRS _hoops_APCS _hoops_HHPR _hoops_ICCGR
 * _hoops_HCHSR _hoops_SRHR _hoops_IS _hoops_HGCR _hoops_RH _hoops_CSCR _hoops_PPR _hoops_IRPCI-_hoops_CRPCI _hoops_SCH _hoops_IS _hoops_RH
 * _hoops_GRGAI.	 _hoops_HGI _hoops_SRPCI _hoops_GH _hoops_ISHHH _hoops_GAPCI _hoops_CGPR _hoops_IIH
 * _hoops_CHR _hoops_AHRH.
 *
 * _hoops_RAPCI _hoops_ARPCI
 * _hoops_RPP _hoops_AAPCI _hoops_HRGR _hoops_HAR _hoops_ARP _hoops_SR _hoops_SGH _hoops_IRS _hoops_RSRA
 * _hoops_PAPCI _hoops_CRPCI _hoops_IS _hoops_IPS _hoops_IRS _hoops_ICCGR _hoops_AGPGI _hoops_IS
 * _hoops_RH _hoops_GRGAI _hoops_SISS _hoops_RH _hoops_RHGS _hoops_HAPCI
 * _hoops_HRGR _hoops_IAPCI _hoops_PPR _hoops_CGH _hoops_SHH _hoops_PSP _hoops_RPIP _hoops_SHH _hoops_IGI
 * _hoops_PGGA _hoops_SR _hoops_SGH _hoops_AHRH _hoops_GGR _hoops_RII _hoops_ARAR _hoops_GACC
 */
#define _hoops_CAPCI			0x00020000
#define _hoops_SAPCI		0x00020000

/*
 * _hoops_GPPCI - _hoops_HRPCI _hoops_IHHH _hoops_SGS _hoops_SR _hoops_CHR _hoops_IRCC
 * _hoops_IS _hoops_SRGAI.  _hoops_PS _hoops_RRP _hoops_IS _hoops_ACPA _hoops_PCPA _hoops_ISCP _hoops_PASPR _hoops_HRGR.
 * _hoops_HAS._hoops_IAS, _hoops_IRS _hoops_RPPCI, _hoops_IRS _hoops_APPCI _hoops_PAR _hoops_IRS _hoops_HGGSP. _hoops_PS _hoops_IGI _hoops_IS _hoops_AA _hoops_RGR
 * _hoops_CCA _hoops_PPPCI.  _hoops_PPPCI _hoops_HRS _hoops_HAGH
 * _hoops_ACPP _hoops_IH _hoops_HPPCI, _hoops_IPPCI & _hoops_CPPCI _hoops_PPR _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_APP _hoops_IH _hoops_SPPCI.
 */
#define _hoops_GHPCI								0x00040000

/* _hoops_RHPCI - _hoops_GRS _hoops_SGH _hoops_RRIC _hoops_PAIA _hoops_IH _hoops_RSSI
 * _hoops_RIIA _hoops_IIGR _hoops_HRRPI _hoops_ASRCI.	_hoops_HGI _hoops_AHPCI _hoops_GGR _hoops_RRI _hoops_CCCI _hoops_ISHHH
 * _hoops_IIGR _hoops_HSP _hoops_PAIA _hoops_HIH _hoops_GHCA _hoops_ASRHA _hoops_SRGAI _hoops_RGHR _hoops_IGIR
 */
#define _hoops_PHPCI						0x00100000

/* _hoops_HHPCI - _hoops_SSCP _hoops_IHPCI _hoops_III _hoops_HHRP _hoops_CHPCI
 * _hoops_IS _hoops_HCPPR _hoops_RH _hoops_SRAA _hoops_SGCR _hoops_GPP _hoops_RH _hoops_SHPR.
 */
#define _hoops_SHPCI						0x00400000


#define _hoops_GIPCI					0x00000001
#define _hoops_RIPCI					0x00000002
#define _hoops_AIPCI					0x00000004
#define _hoops_PIPCI					0x00000008
#define _hoops_HIPCI					0x00000010
#define _hoops_IIPCI					0x00000020
#define _hoops_CIPCI					0x00000040
#define _hoops_SIPCI					0x00000080
#define _hoops_GCPCI					0x00000100
#define _hoops_RCPCI					0x00000200
#define _hoops_ACPCI					0x00000400
#define _hoops_PCPCI					0x00000800
#define _hoops_HCPCI					0x00001000
#define _hoops_ICPCI					0x00002000
#define _hoops_CCPCI					0x00004000
#define _hoops_SCPCI					0x00008000


typedef int _hoops_RPSGR;
#define _hoops_PPSGR			(_hoops_RPSGR)0x11
#define _hoops_GSPCI			(_hoops_RPSGR)0x12
#define _hoops_RSPCI		(_hoops_RPSGR)0x14
#define _hoops_HPSGR		(_hoops_RPSGR)0x21
#define _hoops_ASPCI		(_hoops_RPSGR)0x22
#define _hoops_PSPCI		(_hoops_RPSGR)0x24
#define _hoops_HSPCI		(_hoops_RPSGR)0x01
#define _hoops_ISPCI		(_hoops_RPSGR)0x02
#define _hoops_CSPCI	(_hoops_RPSGR)0x04
#define _hoops_SSPCI			(_hoops_RPSGR)0x10
#define _hoops_GGHCI		(_hoops_RPSGR)0x20



struct _hoops_RGHCI {
	HDC					dc;
	HBITMAP				bitmap;
	HBITMAP				_hoops_AGHCI;
	void far			*_hoops_RCHA;
#ifdef _WIN32_WCE
	void far			*_hoops_PGHCI;
#endif
	_hoops_RGHCI			*_hoops_HGHCI;
};


typedef enum {
	_hoops_IGHCI,
	_hoops_SCASA,
	_hoops_CGHCI
} _hoops_SGHCI;



struct MSW_Driver_State {
	bool					_hoops_GRHCI;
	bool					_hoops_RRHCI;
	bool					_hoops_ARHCI;
	char						_hoops_PRHCI[2];
	DC_Point					_hoops_HRHCI;
	bool					_hoops_IRHCI;
	_hoops_RGHCI					*_hoops_CRHCI;
	bool					_hoops_SRHCI;
	bool					_hoops_GAHCI;
	LPPALETTEENTRY				_hoops_RAHCI;
	LPRGBQUAD					_hoops_AAHCI;

	Display_Context const	*dc;

	Int_XY					_hoops_GCGRR;
	Int_XY					_hoops_SIGRR;
	Int_XY					_hoops_CIGRR;
	Int_XY					_hoops_PAHCI;
	Int_XY					_hoops_HAHCI;

	char						_hoops_IAHCI;
	char						_hoops_CAHCI;
	char						_hoops_SAHCI;
	char						_hoops_GPHCI;
	char						_hoops_RPHCI;
	char						_hoops_APHCI;
	char						_hoops_PPHCI;
	char						_hoops_HPHCI;
	int							_hoops_GCGSH;

	_hoops_SGRRR				*_hoops_GRRRR;

	/*
	 * _hoops_PS _hoops_RRP _hoops_IS _hoops_GRHP _hoops_IRS _hoops_CRS _hoops_IS _hoops_PGAP _hoops_SGIPR _hoops_CSPP _hoops_IIGR _hoops_RH
	 * _hoops_CSGSR _hoops_PPR _hoops_IPHCI _hoops_RIAH _hoops_SR _hoops_CHR _hoops_GRP _hoops_GGR _hoops_RGR _hoops_HAGAR _hoops_IIGR _hoops_RH _hoops_RHPP
	 */
	_hoops_PGRCI					*_hoops_CPHCI;
	_hoops_ARRCI					*_hoops_SPHCI;
	_hoops_HPRCI					*_hoops_GHHCI;
	int							*_hoops_RHHCI;
	int							*_hoops_AHHCI;
	int							*_hoops_PHHCI;
	int							*_hoops_HHHCI;
	int							*_hoops_IHHCI;
	int							*_hoops_CHHCI;

	int							_hoops_SHHCI;
	int							_hoops_GIHCI;
	int							_hoops_RIHCI;
	int							_hoops_AIHCI;
	_hoops_PGRCI					_hoops_PIHCI;
	_hoops_PGRCI					_hoops_HIHCI;
	int							_hoops_IIHCI;
	int							_hoops_CIHCI;
	int							_hoops_SIHCI;
	int							_hoops_GCHCI;
	_hoops_ARRCI					_hoops_RCHCI;
	_hoops_ARRCI					_hoops_ACHCI;
	bool					_hoops_PCHCI;
	HDC							_hoops_PHCIH;

	int							_hoops_HCHCI;
	int							_hoops_ICHCI;
	int							_hoops_CCHCI;
	int							_hoops_SCHCI;
	_hoops_HPRCI					_hoops_GSHCI;
	_hoops_HPRCI					_hoops_RSHCI;

	/*
	 * _hoops_RPP _hoops_IHPR, _hoops_SR _hoops_CHR _hoops_SGGHA _hoops_SPHGR _hoops_HPPCI, _hoops_HAR _hoops_SPPCI _hoops_PAR
	 * _hoops_PSCSR _hoops_GPP _hoops_ASHCI.
	 */
	_hoops_RIRCI					_hoops_SSRRI;

	/*
	 * _hoops_HHHSP _hoops_IS _hoops_SHH _hoops_PSHCI _hoops_GPP _hoops_RIARR
	 */
	int							_hoops_HSHCI;
	HPALETTE					_hoops_ISHCI;
	HBITMAP						_hoops_CSHCI;
	WNDPROC						_hoops_GIGRR;
	int							_hoops_SSHCI;

	HWND						_hoops_GGICI;
	HWND						_hoops_RGICI;

	int							_hoops_RCRAP;
	Image						*_hoops_IHGRR;
	_hoops_RPSGR						_hoops_PIGRR;
	HDC							_hoops_AGICI;
	HDC							_hoops_PGICI;
	_hoops_SGHCI				_hoops_HGICI;
	HDC							_hoops_IGICI;
	HDC							_hoops_CGICI;
	HDC							_hoops_SGICI;
	HBITMAP						_hoops_GRICI;

	/*
	 * _hoops_HSRR _hoops_RRICI _hoops_GCGC _hoops_RGAR.
	 * _hoops_ARICI _hoops_IS _hoops_ACHPR _hoops_GH _hoops_ISHHH.
	 */
	HDC							_hoops_PRICI;
	HDC							_hoops_HRICI;

	bool					_hoops_IRICI;
	bool					_hoops_CRICI;
	bool					_hoops_SRICI;
	bool					_hoops_GAICI;

	FARPROC						_hoops_RAICI;

	RECT						_hoops_IIGRR;
	HRGN						_hoops_AAICI;
	RECT						_hoops_HIGRR;

	HRGN						_hoops_PAICI;
	_hoops_GARRR				_hoops_HAICI;

	HBITMAP						_hoops_IAICI;
	bool					_hoops_SRRRR;
	bool					_hoops_CAICI;
	bool					_hoops_SAICI;

	bool					_hoops_GPICI;
	int							_hoops_RPICI;

	LPBITMAPINFO				_hoops_APICI;
	int							_hoops_PPICI;
	unsigned char				*_hoops_HPICI;
	HANDLE						_hoops_IPICI;
	LPBITMAPINFO				_hoops_CPICI;
	int							_hoops_SPICI;
	unsigned char				*_hoops_GHICI;
	int							_hoops_RHICI;

	bool					pending_resize;

	bool					_hoops_AHICI;

	/* _hoops_HARAI _hoops_IPSCP */
	bool					_hoops_PHICI;
	int							_hoops_HHICI;
	int							planes;
	int							_hoops_IHICI;
	LPLOGPALETTE				_hoops_CHICI;
	bool					*_hoops_SHICI;
	HPALETTE					_hoops_GIICI;

	HPEN						_hoops_RIICI;

	bool					_hoops_AIICI;

	/*
	 * _hoops_PGGRR
	 */
	int							_hoops_PIICI;
	int							_hoops_HIICI;

	int							_hoops_RCGRR;
	int							_hoops_ACGRR;
	int							_hoops_PCGRR;
	int							_hoops_HCGRR;

	int							yfudge;
	int							_hoops_CCGRR;

	/*
	 * _hoops_IPCP _hoops_IIICI
	 */
	int							_hoops_SCGRR;
	int							mouse_y;
#	define		_hoops_RRRRR		0x01
#	define		_hoops_PRRRR	0x04
#	define		_hoops_ARRRR		0x02
	int							_hoops_HRRRR;
	bool						_hoops_IRRRR;

	bool						_hoops_CIICI;

	/*
	 * _hoops_CSIGP _hoops_IHAH
	 */
	struct {
#define _hoops_CCC		(_hoops_GARRR)-1
		_hoops_GARRR			_hoops_RPCI;
		_hoops_GARRR			_hoops_SIICI;
		_hoops_GARRR			_hoops_GCICI;

		Driver_Color		_hoops_RCICI;
		Driver_Color		_hoops_ACICI;

		Int_Rectangle		_hoops_AGAA;

#define _hoops_PCICI			(int)(-1)
		int						_hoops_HCICI;
		int						_hoops_ICICI;

#define _hoops_CCICI			(HFONT)0
		HFONT					font;
	} _hoops_CSC;

	/*
	 * _hoops_SCSA _hoops_ACPH _hoops_GASR
	 */
	COLORREF (*_hoops_SCICI)
		(MSW_Driver_State alter *state,
				Driver_Color const *target,
				Driver_Color const *window,
				bool alter *_hoops_GSICI);

	void (*_hoops_RSICI)
		(MSW_Driver_State alter *state,
				Driver_Color const *color);

	void (*_hoops_ASICI)
		(MSW_Driver_State alter *state,
				Driver_Color const *color);

	void (*_hoops_PSICI)
		(MSW_Driver_State alter *state,
				_hoops_PGRCI alter *_hoops_CPHCI,
				_hoops_PGRCI alter *_hoops_HSICI);

	void (*_hoops_ISICI)
		(MSW_Driver_State alter *state,
				_hoops_ARRCI alter *_hoops_SPHCI,
				_hoops_ARRCI alter *_hoops_HSICI);

	/* _hoops_SGI _hoops_IS _hoops_RPGP _hoops_GGSR _hoops_HAGH _hoops_CSICI _hoops_SSICI */
	bool					_hoops_GGCCI;
	bool					_hoops_RGCCI;
	HBITMAP						_hoops_AGCCI;
	HDC							_hoops_PGCCI;

	/* _hoops_GRSCP _hoops_SRSRR _hoops_CICRR _hoops_PPR _hoops_CIPH */

#define _hoops_HGCCI				0
#define _hoops_IGCCI		1
#define _hoops_CGCCI			2
#define _hoops_SGCCI				3
#define _hoops_GRCCI		4
#define _hoops_RRCCI	_hoops_GRCCI

	int							_hoops_ARCCI;
	int							_hoops_PRCCI;
	int							_hoops_HRCCI[1+_hoops_RRCCI];

	int							point_count;
	POINT						*points;

	int							_hoops_IRCCI;
	int							*_hoops_CRCCI;

	char						_hoops_SRCCI;

	/* _hoops_GACCI _hoops_RACCI */
	bool					_hoops_AACCI;
	int							_hoops_PACCI;
	int							_hoops_HACCI[64];
	int							_hoops_IACCI;
	bool					_hoops_CACCI;
	bool					_hoops_SACCI;
	bool					_hoops_GPCCI;
	int							_hoops_PIHSR;

#define _hoops_RPCCI sizeof(BITMAPINFO)+(sizeof(RGBQUAD)*1024)
	unsigned char				_hoops_APCCI[_hoops_RPCCI];
	/*_hoops_CGPR _hoops_RII _hoops_SAGGR _hoops_RHSI _hoops_PPCCI _hoops_RGR*/
	unsigned char				*_hoops_HPCCI;
	unsigned long				_hoops_IPCCI;

	HFONT						_hoops_CPCCI;
	HBRUSH						_hoops_SPCCI;
	HPEN						_hoops_GHCCI;
	HPALETTE					_hoops_RHCCI;

	int							_hoops_AHCCI; /* _hoops_PHCCI _hoops_RGAR */
};


local void stop_device (Display_Context alter *dc);
local void free_outer_window (Display_Context const *dc);

local HFONT _hoops_HHCCI (Display_Context const *dc,
						 _hoops_HPRCI alter *_hoops_IHCCI, int alter *_hoops_CHHCI, int alter *_hoops_PHHCI, 
						 LOGFONT const *_hoops_CHCCI, long _hoops_SHCCI, long _hoops_GICCI, float width, float _hoops_PRPHA);

/*
 * _hoops_RICCI _hoops_CIGR _hoops_IS _hoops_AICCI _hoops_CICRR _hoops_IS _hoops_PICCI _hoops_RHPP
 * _hoops_PIAP _hoops_PIH _hoops_HII _hoops_PPHHH _hoops_AGAH _hoops_CICRR
 */
#define _hoops_HICCI() ((MSW_Driver_State alter *)((dc)->data))
#define _hoops_IICCI() ((MSW_Driver_State alter *)((nr->_hoops_SRA)->data))


typedef int (FAR WINAPI *_hoops_CICCI) (HWND, unsigned int, unsigned int, long);
typedef int (APIENTRY _hoops_SICCI)(LOGFONT *, const TEXTMETRIC *,
										unsigned long, long);

struct _hoops_GCCCI {
	HDC					_hoops_AGICI;
	bool				_hoops_RCCCI;
	_hoops_SGRRR *		list;
};





local __inline void _hoops_ACCCI(
	MSW_Driver_State alter *state) {
	state->_hoops_ARCCI = _hoops_HGCCI;

	state->point_count = 0;
	state->_hoops_IRCCI = 0;
}

local __inline void draw_and_reset_poly_cache (
	MSW_Driver_State alter *state,
	bool reset) {

	switch (state->_hoops_ARCCI) {
#ifndef _WIN32_WCE
		case _hoops_IGCCI: {

			PolyPolyline (state->_hoops_AGICI,
						  state->points,
						  (DWORD*)state->_hoops_CRCCI,
						  state->_hoops_IRCCI);
		}	break;

		case _hoops_CGCCI: {
			PolyPolygon (state->_hoops_AGICI,
						 state->points,
						 state->_hoops_CRCCI,
						 state->_hoops_IRCCI);
		}	break;

		case _hoops_SGCCI: {
			PolyTextOut (state->_hoops_AGICI,
						 (POLYTEXT *) state->points,
						 state->_hoops_IRCCI);
		}	break;
#endif
		case _hoops_HGCCI: return;
		default:break;
	}

	if (reset)
		_hoops_ACCCI(state);
}


local __inline void _hoops_PCCCI(
	Net_Rendition const & nr,
	int						count,
	int						type) {
	MSW_Driver_State alter		*state = _hoops_IICCI ();

	if (state->_hoops_ARCCI == _hoops_HGCCI) return;

	if ((nr->transform_rendition->_hoops_CPA != state->_hoops_CSC._hoops_GCICI) ||
		(state->_hoops_ARCCI != type) ||
		(state->point_count + count > state->_hoops_HRCCI[type]))
				draw_and_reset_poly_cache (state, true);
}

#define _hoops_HCCCI(coord) ((int)((coord) + 0.005f))

#define _hoops_ICCCI(points, count)										\
   (count == 4 &&														\
	((points[0].x == points[1].x && points[2].x == points[3].x &&		\
	  points[0].y == points[3].y && points[1].y == points[2].y) ||		\
	 (points[0].x == points[3].x && points[1].x == points[2].x &&		\
	  points[0].y == points[1].y && points[2].y == points[3].y)))

#define _hoops_CCCCI(points) { \
	int			left, right, bottom, top; \
	if (points[0].x < points[2].x) { \
		left = points[0].x; \
		right = points[2].x + 1; \
	} \
	else { \
		left = points[2].x; \
		right = points[0].x + 1; \
	} \
	if (points[0].y > points[2].y) { \
		bottom = points[0].y + 1; \
		top = points[2].y; \
	} \
	else { \
		bottom = points[2].y + 1; \
		top = points[0].y; \
	} \
	GDI_Rectangle (state->_hoops_AGICI, left, top, right, bottom); \
}



/*
 * _hoops_HAIA _hoops_RPGP _hoops_SICAR _hoops_IH _hoops_CRPCI _hoops_HPIHR
 */
struct FAKE_LOGPALETTE {
	WORD				_hoops_SCCCI;
	WORD				_hoops_GSCCI;
	PALETTEENTRY		aEntries[256];
};


/*
 * _hoops_PGAA
 */
local void _hoops_RSCCI (
	MSW_Driver_State			*state) {
	FAKE_LOGPALETTE			Palette = {0x300,256,0};
	HPALETTE				ScreenPalette = 0;
	HDC						ScreenDC;
	int						_hoops_ASCCI;

	/* _hoops_IIPI _hoops_CPS _hoops_GGR _hoops_RH _hoops_GHARR _hoops_IHCRH _hoops_IS _hoops_APRP */
	for (_hoops_ASCCI = 0; _hoops_ASCCI < 256; _hoops_ASCCI++) {
		Palette.aEntries[_hoops_ASCCI].peRed = 0;
		Palette.aEntries[_hoops_ASCCI].peGreen = 0;
		Palette.aEntries[_hoops_ASCCI].peBlue = 0;
#ifndef _WIN32_WCE
		Palette.aEntries[_hoops_ASCCI].peFlags = PC_NOCOLLAPSE;
#endif
	}

	/* _hoops_GISA, _hoops_HAIHR, _hoops_CHCRH, _hoops_PSCCI, _hoops_PPR _hoops_HSCI _hoops_RH _hoops_IHCRH */
	ScreenDC = GetDC (NULL);
	ScreenPalette = CreatePalette ((LOGPALETTE *)&Palette);
	ScreenPalette = SelectPalette (ScreenDC, ScreenPalette, !state->_hoops_SRCCI);
#ifndef _WIN32_WCE
	if (state->_hoops_GIICI != (HPALETTE)NULL)
		UnrealizeObject (state->_hoops_GIICI);
#endif
	RealizePalette (ScreenDC);
	ScreenPalette = SelectPalette (ScreenDC, ScreenPalette, !state->_hoops_SRCCI);
	DeleteObject (ScreenPalette);
	ReleaseDC (NULL, ScreenDC);
}


/*
 * _hoops_PGAA
 */
local HPALETTE _hoops_HSCCI (
	LPLOGPALETTE			_hoops_ISCCI,
	int						_hoops_CSCCI,
	MSW_Driver_State			*state) {
	int						i;
	FAKE_LOGPALETTE			Palette = {0x300, 256, 0};
	PALETTEENTRY			*_hoops_SSCCI = &_hoops_ISCCI->palPalEntry[0];

	/*
	 * _hoops_HGI _hoops_PCPH _hoops_SSCP _hoops_RPII _hoops_HRII _hoops_GGSCI _hoops_SRSS _hoops_PPR _hoops_GRS
	 * _hoops_IRAA _hoops_HHH _hoops_RGSCI _hoops_IH _hoops_RH _hoops_SPS _hoops_IRPPI _hoops_AGSCI _hoops_IRCC _hoops_IS
	 * _hoops_CAHA _hoops_RGR _hoops_GGSR - _hoops_SCH _hoops_AIS _hoops_GGSR _hoops_GAR _hoops_IRS _hoops_APACA _hoops_PIHRH _hoops_GPSPR
	 * _hoops_IIGR _hoops_RRGR (_hoops_IGI _hoops_CCA _hoops_PGSCI) _hoops_HIH _hoops_RIAGR _hoops_IRS _hoops_PHI _hoops_IIGR _hoops_HHGS
	 * _hoops_PPR/_hoops_PAR _hoops_HGSCI _hoops_SGS _hoops_RRP _hoops_IGSCI - _hoops_SR _hoops_SSAS _hoops_HAR _hoops_CIPAA
	 * _hoops_RH _hoops_CGSCI _hoops_AGIR _hoops_HIS _hoops_IHSH _hoops_HPGR _hoops_RH _hoops_SHS
	 */

#ifndef _WIN32_WCE
	if (GetSystemPaletteUse (state->_hoops_PGICI) == SYSPAL_NOSTATIC) {
		/*
		 * _hoops_HSRR _hoops_CGSCI, _hoops_SAHR _hoops_IPS _hoops_RH _hoops_HAIR _hoops_GASR _hoops_CRGR
		 * _hoops_IRS _hoops_SGSCI _hoops_CRPR _hoops_PPR _hoops_GCGRA _hoops_RH _hoops_SRS _hoops_PPR _hoops_CGHI _hoops_AIRP
		 * _hoops_CCA _hoops_APRP _hoops_PPR _hoops_PGS
		 * _hoops_PHIR _hoops_GGR _hoops_RH _hoops_IHCRH _hoops_CCA _hoops_RH _hoops_RAGA _hoops_HSH, _hoops_ISCPR _hoops_GRR
		 * _hoops_GAR _hoops_GRSCI
		 */
		for (i = 0; i < 256; i++) {
			Palette.aEntries[i].peRed = _hoops_SSCCI[i].peRed;
			Palette.aEntries[i].peGreen = _hoops_SSCCI[i].peGreen;
			Palette.aEntries[i].peBlue = _hoops_SSCCI[i].peBlue;
			Palette.aEntries[i].peFlags = PC_NOCOLLAPSE;
		}

		/*
		 * _hoops_GCRR _hoops_RCRR _hoops_RH _hoops_CGHI _hoops_RARP _hoops_HRGR _hoops_PGS
		 * _hoops_HGI _hoops_GHCA _hoops_GCGRA _hoops_PCCP _hoops_RARP _hoops_GGR _hoops_RH _hoops_CRPR!
		 */
		_hoops_SSCCI[255].peRed	  = Palette.aEntries[255].peRed = 255;
		_hoops_SSCCI[255].peGreen = Palette.aEntries[255].peGreen = 255;
		_hoops_SSCCI[255].peBlue  = Palette.aEntries[255].peBlue = 255;
		Palette.aEntries[255].peFlags = 0;

		/*
		 * _hoops_CHSR _hoops_RH _hoops_SRS _hoops_HRGR _hoops_APRP
		 * _hoops_HGI _hoops_GHCA _hoops_GCGRA _hoops_PCCP _hoops_RARP _hoops_GGR _hoops_RH _hoops_CRPR!
		 */
		_hoops_SSCCI[0].peRed	= Palette.aEntries[0].peRed = 0;
		_hoops_SSCCI[0].peGreen = Palette.aEntries[0].peGreen = 0;
		_hoops_SSCCI[0].peBlue	= Palette.aEntries[0].peBlue = 0;
		Palette.aEntries[0].peFlags = 0;
	}
	else
#endif
		{
		/*
		 * _hoops_HSRR _hoops_RRSCI, _hoops_HGCR _hoops_RH _hoops_ARSCI _hoops_RSPHR _hoops_PSHA _hoops_CRGR
		 * _hoops_RH _hoops_CRPR, _hoops_PSCR _hoops_CISA _hoops_GGR _hoops_RH _hoops_RHPA _hoops_HGS _hoops_CCA _hoops_RH
		 * _hoops_RAGA _hoops_HAIR _hoops_GASR
		 */
		int				_hoops_PRSCI;
		int				_hoops_HRSCI;
		DWORD			*_hoops_IRSCI;

		/* _hoops_SIPR _hoops_RH _hoops_RSPHR _hoops_PSHA _hoops_HII _hoops_RH _hoops_GHARR _hoops_IHCRH */
		_hoops_PRSCI = GetDeviceCaps (state->_hoops_PGICI, NUMCOLORS);
		_hoops_CSCCI = min ((int) GetSystemPaletteEntries (state->_hoops_PGICI, 0, 256,
								Palette.aEntries), _hoops_CSCCI);

		/*
		 * _hoops_RAP _hoops_RH _hoops_CRSCI _hoops_IIGR _hoops_RH _hoops_GSSC _hoops_RSPHR _hoops_PSHA _hoops_IS _hoops_HPAP _hoops_PPR _hoops_RH
		 * _hoops_SICHR _hoops_HAIR _hoops_CRPR _hoops_IS _hoops_RH _hoops_GHARR _hoops_PSHA
		 */
		_hoops_PRSCI = _hoops_PRSCI / 2;
		for (i = 0; i < _hoops_PRSCI; i++) {
			_hoops_IRSCI = (DWORD *)&Palette.aEntries[i];
			*_hoops_IRSCI = i;
			Palette.aEntries[i].peFlags = PC_EXPLICIT;
		}

		/* _hoops_PHIR _hoops_GGR _hoops_RH _hoops_AIRP _hoops_HII _hoops_RH _hoops_RAGA _hoops_HAIR _hoops_GASR */
		_hoops_HRSCI = _hoops_CSCCI - _hoops_PRSCI;
		for (; i < _hoops_HRSCI; i++) {
			Palette.aEntries[i].peRed = _hoops_SSCCI[i].peRed;
			Palette.aEntries[i].peGreen = _hoops_SSCCI[i].peGreen;
			Palette.aEntries[i].peBlue = _hoops_SSCCI[i].peBlue;
			Palette.aEntries[i].peFlags = 0;
		}

#ifndef _WIN32_WCE
		/* _hoops_GHGHR _hoops_GII _hoops_RHPA _hoops_AIRP _hoops_GAR _hoops_GRSCI */
		for (; i < 256 - _hoops_PRSCI; i++) {
			Palette.aEntries[i].peFlags = PC_NOCOLLAPSE;
		}
#endif
		/* _hoops_RAP _hoops_RH _hoops_CRSCI _hoops_IIGR _hoops_RH _hoops_AAPA _hoops_RSPHR _hoops_PSHA _hoops_IS _hoops_HPAP */
		for (i = 256 - _hoops_PRSCI; i < 256; i++) {
			/* _hoops_PS _hoops_CHR _hoops_CPIC _hoops_IS _hoops_SGH _hoops_IRS _hoops_HRII _hoops_CGRRA _hoops_SIA _hoops_HGRH _hoops_ARI */
			_hoops_IRSCI = (DWORD *)&Palette.aEntries[i];
			*_hoops_IRSCI = i;
			Palette.aEntries[i].peFlags = PC_EXPLICIT;
		}
	}

	/* _hoops_HCGAR _hoops_RH _hoops_IHCRH */
	return CreatePalette ((LOGPALETTE *)&Palette);
}



/*****************************************************************************
 *****************************************************************************
								_hoops_CPIRH _hoops_SPIRH
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_PGAA
 */
local void consume_key (
	MSW_Driver_State alter	*state,
	UINT				word_parameter,
	LONG				_hoops_GHIRH) {
	int					key;
	BYTE				_hoops_RHIRH[256];
	int					status = 0;

	/* _hoops_ASC _hoops_CPPC _hoops_CHR _hoops_AHIRH _hoops_GPP _hoops_RH _hoops_PHIRH _hoops_CPPC */

#	define B_SHIFT				0x00000100
#	define B_CONTROL			0x00000200
#	define B_NUM_LOCK			0x00000400
#	define B_ALT				0x00000800

	/* _hoops_ASC _hoops_CHR _hoops_HSGS _hoops_IS _hoops_RH _hoops_AAGIP _hoops_PPR _hoops_ACGP _hoops_HHIRH */

#	define B_CAPS_LOCK			0x00001000
#	define B_SCROLL_LOCK		0x00002000
#	define B_LEFT_SHIFT			0x00004000
#	define B_RIGB_SHIFT			0x00008000
#	define B_RIGB_CONTROL		0x00010000
#	define B_LEFT_CONTROL		0x00020000
#	define B_RIGB_ALT			0x00040000
#	define B_LEFT_ALT			0x00080000


#ifndef _WIN32_WCE
	GetKeyboardState (_hoops_RHIRH);

	if ((_hoops_RHIRH[VK_SHIFT] & 0x80) != 0)
		status |= B_SHIFT;
	if ((_hoops_RHIRH[VK_CONTROL] & 0x80) != 0)
		status |= B_CONTROL;
	if ((_hoops_RHIRH[VK_NUMLOCK] & 0x01) != 0)
		status |= B_NUM_LOCK;
	if ((_hoops_RHIRH[VK_MENU] & 0x80) != 0)
		status |= B_ALT;
	if ((_hoops_RHIRH[VK_CAPITAL] & 0x01) != 0)
		status |= B_CAPS_LOCK;
	if ((_hoops_RHIRH[VK_SCROLL] & 0x01) != 0)
		status |= B_SCROLL_LOCK;
	if ((_hoops_RHIRH[VK_LSHIFT] & 0x80) != 0)
		status |= B_LEFT_SHIFT;
	if ((_hoops_RHIRH[VK_RSHIFT] & 0x80) != 0)
		status |= B_RIGB_SHIFT;
	if ((_hoops_RHIRH[VK_LCONTROL] & 0x80) != 0)
		status |= B_LEFT_CONTROL;
	if ((_hoops_RHIRH[VK_RCONTROL] & 0x80) != 0)
		status |= B_RIGB_CONTROL;
	if ((_hoops_RHIRH[VK_LMENU] & 0x80) != 0)
		status |= B_LEFT_ALT;
	if ((_hoops_RHIRH[VK_RMENU] & 0x80) != 0)
		status |= B_RIGB_ALT;
#endif
	/* _hoops_SCH'_hoops_GRI _hoops_PCCP _hoops_ICIGP _hoops_SIC _hoops_IIGR _hoops_HHH _hoops_CGGAR */
	switch (word_parameter) {
		case VK_NUMPAD0:
		case VK_NUMPAD1:
		case VK_NUMPAD2:
		case VK_NUMPAD3:
		case VK_NUMPAD4:
		case VK_NUMPAD5:
		case VK_NUMPAD6:
		case VK_NUMPAD7:
		case VK_NUMPAD8:
		case VK_NUMPAD9: {
			if (status & B_NUM_LOCK)
				key = '0' + word_parameter - VK_NUMPAD0;
			else
				key = FIRST_KEYPAD_KEY + word_parameter - VK_NUMPAD0;
		}	break;

		case VK_INSERT: {
			key = INSERT_KEY;
		}	break;

		case VK_END: {
			key = END_KEY;
		}	break;

		case VK_HOME: {
			key = HOME_KEY;
		}	break;

		case VK_PRIOR: {
			key = PAGE_UP_KEY;
		}	break;

		case VK_NEXT: {
			key = PAGE_DOWN_KEY;
		}	break;

		case VK_F1:
		case VK_F2:
		case VK_F3:
		case VK_F4:
		case VK_F5:
		case VK_F6:
		case VK_F7:
		case VK_F8:
		case VK_F9:
		case VK_F10:
		case VK_F11:
		case VK_F12:
		case VK_F13:
		case VK_F14:
		case VK_F15:
		case VK_F16: {
			key = FIRST_FUNCTION_KEY + word_parameter - VK_F1 + 1;
		}	break;

		case VK_TAB: {
			key = 9;
		}	break;

		case VK_RETURN: {
			key = 13;
		}	break;

		case VK_ESCAPE: {
			key = 27;
		}	break;

		case VK_SPACE: {
			key = 32;
		}	break;

		case VK_DELETE: {
			key = RUBOUT_KEY;
		}	break;

		case VK_UP: {
			key = UP_ARROW_KEY;
		}	break;

		case VK_DOWN: {
			key = DOWN_ARROW_KEY;
		}	break;

		case VK_LEFT: {
			key = LEFT_ARROW_KEY;
		}	break;

		case VK_RIGHT: {
			key = RIGHT_ARROW_KEY;
		}	break;

		default: {
#ifndef _WIN32_WCE
			UINT	_hoops_IHIRH;
			WORD	_hoops_CHIRH;
			char	_hoops_SHIRH[256];

			_hoops_IHIRH = (WORD) LOBYTE (HIWORD (_hoops_GHIRH));
			GetKeyboardState ((LPBYTE)_hoops_SHIRH);

			if (ToAsciiEx (word_parameter, _hoops_IHIRH, (PBYTE)_hoops_SHIRH,
				(LPWORD)&_hoops_CHIRH, (UINT)0,GetKeyboardLayout(0)) == 1)
				key = (unsigned int) (0xFFL & _hoops_CHIRH);
			else
#endif
				key = 0;
		} _hoops_HHHI;
	}

	if (key != 0)
		HI_Queue_Keyboard_Event ((_hoops_GGAGR alter *)state->dc->_hoops_GHRI,
								 key, status);
}


/*
 * _hoops_PGAA
 */
local void consume_mouse (
	MSW_Driver_State alter	*state,
	UINT				event,
	UINT				word_parameter,
	LONG				_hoops_GHIRH) {

	UNREFERENCED(word_parameter);

	switch (event) {
		case WM_RBUTTONDOWN: {
			state->_hoops_HRRRR |= _hoops_ARRRR;
		}	break;
		case WM_MBUTTONDOWN: {
			state->_hoops_HRRRR |= _hoops_PRRRR;
		}	break;
		case WM_LBUTTONDOWN: {
			state->_hoops_HRRRR |= _hoops_RRRRR;
		}	break;

		case WM_RBUTTONUP: {
			state->_hoops_HRRRR &= ~_hoops_ARRRR;
		}	break;
		case WM_MBUTTONUP: {
			state->_hoops_HRRRR &= ~_hoops_PRRRR;
		}	break;
		case WM_LBUTTONUP: {
			state->_hoops_HRRRR &= ~_hoops_RRRRR;
		}
	}

	state->_hoops_SCGRR = LOWORD (_hoops_GHIRH);
	state->mouse_y = state->yfudge - HIWORD (_hoops_GHIRH);

	HD_Queue_Pixel_Location_Event (state->dc, state->_hoops_HRRRR,
								   state->_hoops_SCGRR, state->mouse_y);
	state->_hoops_IRRRR = true;
}


/*
 * _hoops_PGAA
 */
local void check_events (
	MSW_Driver_State alter	*state) {
	MSG					_hoops_SSACR;


	if (state->_hoops_CIICI) {
		state->_hoops_IRRRR = false;

		while (PeekMessage (&_hoops_SSACR, state->_hoops_GGICI, 0, 0, PM_NOREMOVE) &&
			GetMessage (&_hoops_SSACR, state->_hoops_GGICI, 0, 0)) {
				TranslateMessage (&_hoops_SSACR);
				DispatchMessage (&_hoops_SSACR);
		}
	}
}


/*
 * _hoops_SRAC
 */
local bool _hoops_HSCSP (
	Display_Context const	*dc,
	int alter					*button,
	int alter					*x,
	int alter					*y) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();


	if (state != null) {
		check_events (state);

		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		state = _hoops_HICCI ();

		/*
		 * _hoops_HGI _hoops_API _hoops_PIHA _hoops_SHR _hoops_RHRRH _hoops_IRS _hoops_GISAP "_hoops_PIAP",
		 * _hoops_HIS _hoops_RPP _hoops_RIIRH _hoops_SSAS _hoops_HAR _hoops_RHRRH _hoops_PCCP _hoops_CPGGR _hoops_AIH
		 * _hoops_AIIRH, _hoops_SR _hoops_PIHA _hoops_RHRRH _hoops_SPR _hoops_ARI.
		 * _hoops_PS _hoops_GRS _hoops_SAHR _hoops_ASAR-_hoops_RHRRH _hoops_RH _hoops_CGHI _hoops_GISAP _hoops_PIAP _hoops_SGS
		 * _hoops_SR _hoops_HARRA.
		 */
		if (state == NULL || state->_hoops_IRRRR)
			return false;
		else {
			*button = state->_hoops_HRRRR;
			*x = state->_hoops_SCGRR;
			*y = state->mouse_y;
			return true;
		}
	}


	return false;
}


/*
 * _hoops_SRAC
 */
local bool _hoops_ISCSP (
	Display_Context const	*dc,
	int alter					*button,
	int alter					*status) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();

	UNREFERENCED (status);
	UNREFERENCED (button);


	if (state != null) {
		check_events (state);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		state = _hoops_HICCI ();

		/*
		* _hoops_RIIRH _hoops_GRS _hoops_SHR _hoops_HS _hoops_PIIRH _hoops_GII _hoops_HIIRH
		* _hoops_IS _hoops_AGAH _hoops_AIH _hoops_IIIRH.  _hoops_CPGP _hoops_AGAH _hoops_ASSP'_hoops_RA
		* _hoops_RRP _hoops_IS _hoops_ACPA _hoops_RH "_hoops_PIAP" _hoops_IIGR _hoops_RH _hoops_CIIRH, _hoops_RGR _hoops_API
		* _hoops_PAH _hoops_IGIRR _hoops_ASRC _hoops_RCPP.
		*/
	}

	return false;
}


/*
 * _hoops_SRAC
 */
local void _hoops_ASCSP (
	Display_Context const	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();

#ifndef _WIN32_WCE
	SetWindowText (state->_hoops_GGICI, dc->options._hoops_IAPIR.text);
#endif
}



/*****************************************************************************
 *****************************************************************************
	  _hoops_HAICR _hoops_PCCIR _hoops_HAS _hoops_ACHP _hoops_RA _hoops_IAS _hoops_PCCIR ,  _hoops_IHRPR _hoops_GSSAA _hoops_HAS _hoops_CCAHR _hoops_RCSR _hoops_GCSR _hoops_IRS _hoops_PCCIR _hoops_GHGP,  _hoops_IRS _hoops_ACHP _hoops_GHGP   _hoops_SRSCI _hoops_HAS _hoops_ACHP _hoops_GHGP _hoops_GCSR _hoops_SSCHA	 _hoops_HAICR _hoops_PCCIR _hoops_GCSR _hoops_GSGGR _hoops_GRI
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_PGAA
 *
 * _hoops_IHCRA: _hoops_GASCI
 *
 * _hoops_RASCI : _hoops_AASCI _hoops_IS _hoops_SGH _hoops_RH _hoops_PASCI() _hoops_API _hoops_GGR _hoops_RH _hoops_RAGA
 *			 _hoops_GRGAI _hoops_RHPP _hoops_IS _hoops_AGRP _hoops_ARPR _hoops_IRS _hoops_IHIR _hoops_HASCI _hoops_HRPR
 *			 _hoops_IH _hoops_PGI _hoops_IASCI _hoops_PAR _hoops_CASCI _hoops_CCH.	 _hoops_IPCP _hoops_IHIR _hoops_HASCI
 *			 _hoops_HRPR _hoops_HHS _hoops_SASCI _hoops_SHH _hoops_CGI _hoops_IS _hoops_GPSCI() _hoops_IS
 *			 _hoops_HGCR _hoops_IRS _hoops_SHCA _hoops_IS _hoops_IRS _hoops_SISS _hoops_GGR _hoops_RH _hoops_AGSRH _hoops_HSCHR.
 *
 * _hoops_RPSCI   : _hoops_APSCI	== _hoops_GSCA _hoops_IS _hoops_RH _hoops_GRGAI _hoops_RHPP (_hoops_HII _hoops_PPSCI).
 *			 _hoops_RCAAI	== _hoops_IHPR == _hoops_IASCI _hoops_CCH, _hoops_RCPP == _hoops_CASCI _hoops_CCH.
 *			 _hoops_HPSCI == _hoops_RCSSA _hoops_IIGR _hoops_GRGAI _hoops_SISS (_hoops_IAS._hoops_ISHI. "_hoops_CSAAI _hoops_IPSCI _hoops_GRISH")
 *			 _hoops_CPSCI == _hoops_SPSCI _hoops_IIGR _hoops_GRGAI _hoops_SISS (_hoops_IAS._hoops_ISHI. "_hoops_GHSCI:")
 *
 * _hoops_GCAAA : _hoops_SCSA _hoops_PPGS _hoops_RGHH _hoops_IS _hoops_PPGS _hoops_CCA _hoops_IRS _hoops_IHIR _hoops_HASCI _hoops_HRPR.
 *			 _hoops_IHHAH _hoops_RPP _hoops_RHPP _hoops_ASSP'_hoops_RA _hoops_GCGH _hoops_PASCI() _hoops_PAR _hoops_IRPSR'_hoops_RA
 *			 _hoops_CCPP _hoops_PPGS _hoops_IH _hoops_RH _hoops_IHIR _hoops_HASCI _hoops_HRPR.
 */
#ifndef _WIN32_WCE
local HANDLE _hoops_RHSCI (
	HINSTANCE		_hoops_AHSCI,
	int				_hoops_PHSCI,
	LPSTR			device_string,
	LPSTR			output_string) {
	LPFNDEVMODE		extended_device_mode;
	int				_hoops_HHSCI;
	HANDLE			_hoops_IHSCI;
	PDEVMODE		_hoops_CHSCI;
	DEVMODE			_hoops_SHSCI;


	extended_device_mode =
		(LPFNDEVMODE)GetProcAddress (_hoops_AHSCI, "ExtDeviceMode");
	if (extended_device_mode) {
		_hoops_HHSCI = extended_device_mode ((HWND)NULL,
										_hoops_AHSCI, NULL,
			device_string, output_string, NULL, NULL, 0);

		if (_hoops_HHSCI < 0 || (_hoops_IHSCI =
			LocalAlloc (LHND, _hoops_HHSCI)) != 0)
			return NULL;

		_hoops_CHSCI = (PDEVMODE) LocalLock (_hoops_IHSCI);

		_hoops_AAHR (device_string, (char alter *)_hoops_SHSCI.dmDeviceName);
		_hoops_SHSCI.dmSpecVersion		= 0x300;
		_hoops_SHSCI.dmDriverVersion		= 0;
		_hoops_SHSCI.dmSize				= sizeof (_hoops_SHSCI);
		_hoops_SHSCI.dmDriverExtra		= 0;
		_hoops_SHSCI.dmFields			= DM_ORIENTATION;
		_hoops_SHSCI.dmOrientation		= (_hoops_PHSCI == Drivo_Landscape_ON ?
												DMORIENT_LANDSCAPE :
												DMORIENT_PORTRAIT);
		_hoops_SHSCI.dmPaperSize			= 0;
		_hoops_SHSCI.dmPaperLength		= 0;
		_hoops_SHSCI.dmPaperWidth		= 0;
		_hoops_SHSCI.dmScale				= 0;
		_hoops_SHSCI.dmCopies			= 0;
		_hoops_SHSCI.dmDefaultSource		= 0;
		_hoops_SHSCI.dmPrintQuality		= 0;
		_hoops_SHSCI.dmColor				= 0;
		_hoops_SHSCI.dmDuplex			= 0;

		extended_device_mode ((HWND) NULL, _hoops_AHSCI,
						(LPDEVMODE) _hoops_CHSCI,
						device_string, output_string, &_hoops_SHSCI, NULL,
						DM_MODIFY | DM_COPY);

		LocalUnlock (_hoops_IHSCI);
	}
	else
		return NULL;


	return _hoops_IHSCI;
}
#endif

/*
 * _hoops_PGAA
 */
local HANDLE _hoops_GISCI (
	int				_hoops_PHSCI,
	LPSTR			device_string,
	LPSTR			_hoops_RISCI,
	LPSTR			output_string) {
								/* _hoops_SCSA _hoops_RGHH _hoops_IS _hoops_HASCI _hoops_PPARR */
	HANDLE			_hoops_IHSCI = NULL;
								/* _hoops_AISCI _hoops_RHPP _hoops_RSIRR (_hoops_CRRPR ._hoops_PISCI) */
	char			_hoops_HSS[64];
								/* _hoops_HISCI _hoops_IIGR _hoops_RHPP _hoops_ASCSR */
	HINSTANCE		handle_driver;

#ifndef _WIN32_WCE
	_hoops_AAHR (_hoops_RISCI, _hoops_HSS);
	_hoops_HPRPR (".DRV", _hoops_HSS);

	handle_driver = LoadLibrary (_hoops_HSS);

	if (handle_driver < (HINSTANCE) 32)
		return NULL;

	_hoops_IHSCI = _hoops_RHSCI (handle_driver, _hoops_PHSCI,
		 device_string, output_string);
	if (_hoops_IHSCI == NULL)
		_hoops_ARGIP (HEC_MSW_DRIVER, HES_EXTDEVICEMODE_NOT_SUPPORTED,
					 "Driver doesn't support ExtDeviceMode",
					 "Couldn't change orientation",
					 "Printer will use default orientation");

	FreeLibrary (handle_driver);

#endif
	return _hoops_IHSCI;
}


/*
 * _hoops_PGAA
 *
 * _hoops_IHCRA: _hoops_IISCI
 *
 * _hoops_RASCI : _hoops_SIPR _hoops_IRS _hoops_GRGAI _hoops_SHCA.
 *			 _hoops_CISCI _hoops_RH _hoops_SHIR _hoops_GRGAI'_hoops_GRI _hoops_SIHC _hoops_GGSR _hoops_IIGR _hoops_SISCI._hoops_GCSCI, _hoops_RCSCI
 *			 _hoops_SCH, _hoops_RSSAR _hoops_IRS _hoops_HASCI _hoops_HRPR (_hoops_IIHA _hoops_GPP _hoops_RCAAI),
 *			 _hoops_PPR _hoops_HCPH _hoops_GPSCI.  _hoops_ACSCI _hoops_GH _hoops_RH _hoops_HASCI _hoops_HRPR
 *			 _hoops_SGS _hoops_CSAP _hoops_SPIP, _hoops_HAH.
 *
 * _hoops_RPSCI   : _hoops_RCAAI == _hoops_IHPR _hoops_RPP _hoops_HHGC _hoops_IS _hoops_SRGAI _hoops_GGR _hoops_IASCI _hoops_CCH.
 *						 _hoops_RCPP _hoops_RPP _hoops_HHGC _hoops_IS _hoops_SRGAI _hoops_GGR _hoops_CASCI _hoops_CCH.
 *
 * _hoops_GCAAA : _hoops_SHCA _hoops_IS _hoops_RH _hoops_SHIR _hoops_GRGAI _hoops_GGR _hoops_RH _hoops_IRPR _hoops_IASCI/
 *			 _hoops_CASCI _hoops_CCH (_hoops_GPGA _hoops_GPP _hoops_RCAAI).  _hoops_IHHAH _hoops_GPP _hoops_RIHH.
 */
local HDC get_printer_DC (
	int				_hoops_PHSCI) {
								/* _hoops_RPPCI _hoops_SHCA _hoops_SR'_hoops_GCPP _hoops_ASRC. */
	HDC				_hoops_PRICI = NULL;
								/* _hoops_SGAA _hoops_PCSCI _hoops_SIHC _hoops_HII _hoops_SISCI._hoops_GCSCI */
	char			printer_name[64];
								/* _hoops_HCSCI _hoops_RSIRR(_hoops_IAS._hoops_ISHI. "_hoops_CSAAI _hoops_IPSCI _hoops_GRISH") */
	char			device_name[64];
								/* _hoops_SCHGR _hoops_RSIRR (_hoops_IAS._hoops_ISHI. "_hoops_ICSCI") */
	char			_hoops_HSS[64];
								/* _hoops_CCSCI _hoops_SCSCI (_hoops_IAS._hoops_ISHI. "_hoops_GHSCI:") */
	char			output_port_name[64];
								/* _hoops_GSSCI _hoops_RSSCI _hoops_ASSCI _hoops_IS _hoops_HASCI _hoops_PPARR. */
	HANDLE			_hoops_IHSCI;
								/* _hoops_CRS _hoops_IS _hoops_HASCI _hoops_HRPR. */
	PDEVMODE		_hoops_CHSCI;

#ifndef _WIN32_WCE
	GetProfileString ("windows", "device", "", printer_name, 64);

	if (!(HI_Parse_String (printer_name, ",", 0, device_name, -1) &&
		  HI_Parse_String (printer_name, ",", 1, _hoops_HSS, -1) &&
		  HI_Parse_String (printer_name, ",", 2, output_port_name, -1))) {
		return NULL;
	}

	if (_hoops_PHSCI == _hoops_HGHRP)
		_hoops_IHSCI = NULL;
	else
		_hoops_IHSCI = _hoops_GISCI (_hoops_PHSCI, device_name,
										   _hoops_HSS, output_port_name);

	/*
	 * _hoops_PS _hoops_RRP _hoops_IS _hoops_SSS _hoops_GGSR _hoops_PCPA _hoops_RH _hoops_GRGAI _hoops_HSCHR _hoops_HRGR _hoops_IS _hoops_IRSHR
	 * _hoops_RH _hoops_CSCR _hoops_GGR _hoops_RH _hoops_RCPH _hoops_PCPH
	 */

	if (_hoops_IHSCI)
		_hoops_CHSCI = (PDEVMODE) LocalLock (_hoops_IHSCI);
	else
		_hoops_CHSCI = NULL;

	_hoops_PRICI = CreateDC (_hoops_HSS, device_name, output_port_name,
								  (DEVMODE const *)_hoops_CHSCI);


	if (_hoops_IHSCI) {
		LocalUnlock (_hoops_IHSCI);
		LocalFree (_hoops_IHSCI);
	}

#endif
	return _hoops_PRICI;
}


/*
 * _hoops_PGAA
 */
short APIENTRY printer_abort_proc (
	HDC					_hoops_PRICI,
	short				code) {
	MSG					_hoops_SSACR;
	_hoops_RRPRH alter	*_hoops_IRSRA = _hoops_ARPRH ();

	UNREFERENCED (_hoops_PRICI);
	UNREFERENCED (code);


	while (!_hoops_IRSRA->_hoops_CCRCI && PeekMessage (&_hoops_SSACR, NULL, 0, 0, PM_REMOVE)) {
		if (!_hoops_IRSRA->_hoops_SCRCI ||
			IsDialogMessage (_hoops_IRSRA->_hoops_SCRCI, &_hoops_SSACR)) {
			TranslateMessage (&_hoops_SSACR);
			DispatchMessage (&_hoops_SSACR);
		}
	}


	return !_hoops_IRSRA->_hoops_CCRCI;
}


/*
 * _hoops_PGAA
 */
BOOL APIENTRY print_dialog_proc (
	HWND				handle_dialog,
	UINT				message,
	UINT				word_parameter,
	LONG				_hoops_GHIRH) {
	_hoops_RRPRH alter	*_hoops_IRSRA = _hoops_ARPRH ();

	UNREFERENCED (_hoops_GHIRH);
	UNREFERENCED (word_parameter);


	switch (message) {
		case WM_INITDIALOG: {
#ifndef _WIN32_WCE
			SetWindowText (handle_dialog, _hoops_IRSRA->_hoops_GSRCI);
#endif
		}	break;

		case WM_COMMAND: {
			_hoops_IRSRA->_hoops_CCRCI = true;
			DestroyWindow (handle_dialog);
			_hoops_IRSRA->_hoops_SCRCI = 0;
		}	break;

		default: {
			return FALSE;
		}
	}


	return TRUE;
}


/*
 * _hoops_PGAA
 */
BOOL APIENTRY clipboard_dialog_proc (
	HWND				handle_dialog,
	UINT				message,
	UINT				word_parameter,
	LONG				_hoops_GHIRH) {
	_hoops_RRPRH alter	*_hoops_IRSRA = _hoops_ARPRH ();

	UNREFERENCED (_hoops_GHIRH);
	UNREFERENCED (word_parameter);


	switch (message) {
		case WM_INITDIALOG: {
#ifndef _WIN32_WCE
			SetWindowText (handle_dialog, _hoops_IRSRA->_hoops_GSRCI);
#endif
		}	break;

		default: {
			return FALSE;
		}
	}


	return TRUE;
}


/*
 * _hoops_PGAA
 */
local void _hoops_SGCRH (
	MSW_Driver_State alter	*state,
	HWND				_hoops_GGICI,
	bool			_hoops_RRCRH,
	bool			_hoops_ARCRH) {
	PAINTSTRUCT			ps;
	HDC					_hoops_AGICI;
	RECT				_hoops_PRCRH;


	_hoops_AGICI = BeginPaint (state->_hoops_GGICI, (LPPAINTSTRUCT)&ps);
	EndPaint (state->_hoops_GGICI, &ps);

	if (state->pending_resize) {
		state->pending_resize = false;
		if (!IsIconic (_hoops_GGICI) &&
			(_hoops_RRCRH || IsWindowVisible (_hoops_GGICI)))
		{
			GetClientRect (state->_hoops_GGICI, &state->_hoops_IIGRR);
			HD_Force_Refresh (state->dc);
			return;
		}
	}

	CopyRect (&_hoops_PRCRH, &ps.rcPaint);

	if (state->_hoops_SRRRR) {
		if (BIT(state->dc->flags, _hoops_GIRIP)) {
			/*
			 * _hoops_PS _hoops_CHR _hoops_IPIH _hoops_IGSIP _hoops_RH _hoops_PSSCI
			 * _hoops_SAHR _hoops_GGCR _hoops_IS _hoops_RH _hoops_HGRC _hoops_CCAC
			 */
			IntersectRect (&_hoops_PRCRH,
						   &state->_hoops_IIGRR,
						   &ps.rcPaint);

			if (EqualRect (&_hoops_PRCRH, &ps.rcPaint)) {
				/*
				 * _hoops_HSSCI _hoops_CCAC _hoops_HRGR _hoops_GIHRR _hoops_AGIRH _hoops_GIAA
				 * _hoops_RH _hoops_CCAC _hoops_SR _hoops_CHR _hoops_AIAH _hoops_ASCA
				 * _hoops_PS _hoops_GA'_hoops_RA _hoops_HS _hoops_IS _hoops_AA _hoops_PA _hoops_CR _hoops_RH _hoops_HPHS
				 * _hoops_AIAH _hoops_GPP _hoops_RH _hoops_PSSCI _hoops_SSSCP _hoops_SHH _hoops_CPCGP
				 * _hoops_HPP _hoops_SHPR _hoops_CPGGR
				 */
			}
			else {
				/*
				 * _hoops_IPCP _hoops_PSSCI _hoops_ISSCI _hoops_SIPP _hoops_RH _hoops_CCAC _hoops_SR'_hoops_ASAR _hoops_ASCA
				 * _hoops_HACSR _hoops_CHARP _hoops_AHCA _hoops_RH _hoops_GSHRH _hoops_CCAC
				 */

				UnionRect (&state->_hoops_IIGRR,
						   &state->_hoops_IIGRR,
						   &ps.rcPaint);
				HD_Force_Partial_Refresh (state->dc,
										  ps.rcPaint.left - 25,
										  ps.rcPaint.right - 1 + 25,
										  state->yfudge - ps.rcPaint.bottom - 25,
										  state->yfudge - ps.rcPaint.top + 25);
			}
		}
		else {
			if (!state->_hoops_CAICI) {
				/* _hoops_PS _hoops_HS _hoops_IS _hoops_HSPP _hoops_PCCP _hoops_PAAP - _hoops_PRIA _hoops_RH _hoops_RPPS _hoops_IGIR */
				GetClientRect (state->_hoops_GGICI, &state->_hoops_IIGRR);
				HD_Force_Refresh (state->dc);
			}
			else {
				if (!state->_hoops_GAHCI) {

					if (state->_hoops_AGICI) 
						ReleaseDC(state->_hoops_GGICI, state->_hoops_AGICI);

					/* _hoops_PS _hoops_RRP _hoops_IS _hoops_HGCR _hoops_RH _hoops_CSPH _hoops_PPR _hoops_HPAC _hoops_SCH _hoops_GAR _hoops_SR _hoops_ACRR */
					state->_hoops_AGICI = GetDC (state->_hoops_GGICI);

					/* _hoops_AGGA _hoops_SR _hoops_RRP _hoops_IS _hoops_CSSCI _hoops_CPRAH _hoops_SSSCI _hoops_RPP _hoops_IRPR */
					state->_hoops_IGICI = state->_hoops_AGICI;
					state->_hoops_AGICI = state->_hoops_CGICI;
				}
				
				/*
				 * _hoops_IPCP _hoops_PSSCI _hoops_HRGR _hoops_APIP
				 * _hoops_CICR _hoops_IPS _hoops_RH _hoops_HGRC _hoops_ARRGR _hoops_IS _hoops_RH _hoops_AIRI
				 */
				BitBlt (state->_hoops_IGICI, ps.rcPaint.left,
						ps.rcPaint.top,
						ps.rcPaint.right-ps.rcPaint.left,
						ps.rcPaint.bottom-ps.rcPaint.top,
						state->_hoops_AGICI,
						ps.rcPaint.left, ps.rcPaint.top,
						SRCCOPY);
				
				if (!state->_hoops_GAHCI) {

					state->_hoops_AGICI = state->_hoops_IGICI;

					ReleaseDC (state->_hoops_GGICI, state->_hoops_AGICI);
					state->_hoops_AGICI = null;
				}
			}
		}
	}
	else {
		/* _hoops_AGAR _hoops_GRAA-_hoops_ACHGR _hoops_CCH */
		if (ps.rcPaint.bottom + ps.rcPaint.top +
			ps.rcPaint.right + ps.rcPaint.left == 0)
			HD_Force_Refresh (state->dc);
		else
			HD_Force_Partial_Refresh (state->dc,
									  ps.rcPaint.left - 25,
									  ps.rcPaint.right - 1 + 25,
									  state->yfudge - ps.rcPaint.bottom	 - 25,
									  state->yfudge - ps.rcPaint.top + 25);
	}

	/* _hoops_IPCP _hoops_SHIR _hoops_ACPH _hoops_IH _hoops_RGR _hoops_HRGR _hoops_PCSH/_hoops_HCSH _hoops_GGGSI */
	if (_hoops_ARCRH)
		InvalidateRect (_hoops_GGICI, (LPRECT) &ps.rcPaint, 0);
}


/*
 * _hoops_PGAA
 */
local int _hoops_RGGSI (
	MSW_Driver_State alter	*state,
	bool			_hoops_SRCCI,
	bool			_hoops_AGGSI,
	bool			_hoops_PGGSI) {


	if (state->_hoops_GIICI != NULL) {
		/* _hoops_CGP _hoops_SR _hoops_HS _hoops_CPHR _hoops_RGR _hoops_ARI _hoops_SR _hoops_AA _hoops_HAR _hoops_RRP _hoops_IS _hoops_AA _hoops_SCH _hoops_GICS */
		state->_hoops_SAICI = false;
		SelectPalette (state->_hoops_AGICI, state->_hoops_GIICI, _hoops_SRCCI);
#ifndef _WIN32_WCE
		if (_hoops_PGGSI)
			UnrealizeObject (state->_hoops_GIICI);
#endif
		if (RealizePalette (state->_hoops_AGICI) && _hoops_AGGSI &&
			!BIT (state->dc->options._hoops_IRARR,
				  _hoops_GRPCI)) {
			PostMessage (state->_hoops_GGICI, WM_PAINT, 0, 0);
		}
		if (state->_hoops_SRRRR) {
			SelectPalette (state->_hoops_IGICI,
						   state->_hoops_GIICI,
						   _hoops_SRCCI);
#ifndef _WIN32_WCE
			UnrealizeObject (state->_hoops_GIICI);
#endif
			RealizePalette (state->_hoops_IGICI);
		}
		return TRUE;
	}
	else
		return FALSE;
}


/*
 * _hoops_PGAA
 * _hoops_GRAA-_hoops_SGH _hoops_RPPS _hoops_RCC _hoops_RPPS _hoops_AACRH
 */
LRESULT APIENTRY _hoops_HGGSI (
	HWND					_hoops_GGICI,
	UINT					message,
	WPARAM					word_parameter,
	LPARAM					_hoops_GHIRH) {
	Display_Context *	dc;
	static		bool				_hoops_IGGSI = false;
	MSW_Driver_State alter *	state;



	if ((dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT)_hoops_GGICI)) != null &&
			(state = _hoops_HICCI ()) != null) {

		state->_hoops_CIICI = false;

		switch (message) {
			case WM_SYSCOMMAND: {
				switch (word_parameter & 0xFFF0) {
					case SC_KEYMENU: {
						/*
						 * _hoops_CGGSI _hoops_RHHR _hoops_RH _hoops_SGGSI _hoops_SIC
						 * _hoops_HPPP _hoops_RGAR _hoops_RPP _hoops_PSP _hoops_RGSHA _hoops_CCAC
						 */
						if (!dc->options._hoops_HRSSP)
							consume_key (state, VK_F10, 0);
					}	break;
					case IDM_ABOUT: {
						/* _hoops_HGI _hoops_GRGSI _hoops_HCAII _hoops_CCA _hoops_RRGSI */
						_hoops_RGIIR	*_hoops_ARSAH;
						int					_hoops_PPIHA = false;

						PUSHNAME(dc->_hoops_RIGC);
						if ((_hoops_ARSAH = HOOPS_WORLD->_hoops_RASAH) != null) do {
							if (_hoops_ARSAH->_hoops_APRPR == HC_Report_Error) {
								_hoops_PPIHA = true;
								break;
							}
						} _hoops_RGGA ((_hoops_ARSAH = _hoops_ARSAH->next) == null);
						if (!_hoops_PPIHA) {
							HC_Define_Error_Handler ((_hoops_IRPCR)HC_Report_Error);
							HC_Print_Version ();
							HC_UnDefine_Error_Handler ((_hoops_IRPCR)HC_Report_Error);
						}
						else {
							HC_Print_Version ();
						}
						POPNAME(dc->_hoops_RIGC);
						state->_hoops_CIICI = true;
						return (LONG)0;
					} _hoops_HHHI;
				}
			}	break;

		case WM_ERASEBKGND:
				state->_hoops_CIICI = true;
			/* _hoops_IRISR _hoops_GRS _hoops_RGHH _hoops_RGR */
			return TRUE;
			_hoops_HHHI;

		case WM_CLOSE: {
			/*
			 * _hoops_HPIRA _hoops_RPISR _hoops_GRS _hoops_ISPR _hoops_RGR _hoops_RIP _hoops_PPR _hoops_PCHIA _hoops_RHPP
			 * _hoops_ISCCP _hoops_SCH _hoops_ARI _hoops_CHH _hoops_HS _hoops_RPII _hoops_HACRH _hoops_IACRH
			 */
			char	event_string[255];

			if (dc->options._hoops_GASSP && !dc->options._hoops_IRSSP)
				HI_Queue_Special_Event (dc->_hoops_RIGC, "MSW:DeleteWindow",
					HI_Build_Special_Event_String (event_string, "MSW", dc->_hoops_AAHSR,
					(POINTER_SIZED_INT)state->_hoops_GGICI, -1));

			HI_Queue_Actor_Shutdown(dc->_hoops_GHRI, false);

			state = 0;

		}	break;

		case WM_SIZE: {
			state->pending_resize = true;
		}	break;


		case WM_KEYDOWN: {
			consume_key (state, word_parameter, _hoops_GHIRH);
		}	break;

#		ifndef WM_ENTERSIZEMOVE
			/* _hoops_PRCSR _hoops_GGR _hoops_ARGSI 2.2 _hoops_PPR _hoops_PHPA */
#			define WM_ENTERSIZEMOVE 0x231
#			define WM_EXITSIZEMOVE	0x232
#		endif

		case WM_ENTERSIZEMOVE: {
			state->_hoops_IRHCI = true;
		}	break;

		case WM_EXITSIZEMOVE: {
			state->_hoops_IRHCI = false;
			state->_hoops_CIGRR.x = state->_hoops_HAHCI.x;
			state->_hoops_CIGRR.y = state->_hoops_HAHCI.y;
			state->_hoops_SIGRR.x = state->_hoops_PAHCI.x;
			state->_hoops_SIGRR.y = state->_hoops_PAHCI.y;
		}	break;

		case WM_WINDOWPOSCHANGED: {
			LPWINDOWPOS _hoops_CACRH;

			_hoops_CACRH = (LPWINDOWPOS) _hoops_GHIRH;

			if (state->_hoops_IRHCI) {
				state->_hoops_HAHCI.x = _hoops_CACRH->cx;
				state->_hoops_HAHCI.y = _hoops_CACRH->cy;
				state->_hoops_PAHCI.x = _hoops_CACRH->x;
				state->_hoops_PAHCI.y = _hoops_CACRH->y;
			}
			else {
				state->_hoops_CIGRR.x = _hoops_CACRH->cx;
				state->_hoops_CIGRR.y = _hoops_CACRH->cy;
				state->_hoops_SIGRR.x = _hoops_CACRH->x;
				state->_hoops_SIGRR.y = _hoops_CACRH->y;
			}
		}	break;

		case WM_MOUSEMOVE:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_LBUTTONUP: {
			consume_mouse (state, message, word_parameter, _hoops_GHIRH);
		}	break;

#ifndef _WIN32_WCE
		case WM_WINDOWPOSCHANGING: {

			LPWINDOWPOS _hoops_CACRH;
			char			_hoops_SACRH = false;

			_hoops_CACRH = (LPWINDOWPOS) _hoops_GHIRH;
			if (IsIconic (_hoops_GGICI) || IsZoomed (_hoops_GGICI))
				break;

			if (!dc->options._hoops_RASSP) {
				if (state->_hoops_CIGRR.x == _hoops_CACRH->cx &&
					state->_hoops_CIGRR.y == _hoops_CACRH->cy) {
					/* _hoops_RPCRH */
					_hoops_CACRH->flags |= (SWP_NOMOVE | SWP_NOREPOSITION);
					_hoops_SACRH = true;
				}
			}

			if (!_hoops_SACRH &&
				!dc->options._hoops_PASSP &&
				_hoops_CACRH->cx > 0 &&
				(state->_hoops_CIGRR.x != _hoops_CACRH->cx ||
				 state->_hoops_CIGRR.y != _hoops_CACRH->cy)) {
				/*
				 * _hoops_PS _hoops_HS _hoops_IS _hoops_APCRH _hoops_RGR _hoops_RPPS _hoops_IS _hoops_RH _hoops_PSHR
				 * _hoops_AHHSR _hoops_SCH _hoops_RIAGR _hoops_CGPR _hoops_SR _hoops_SPIP _hoops_SCH
				 */
				float			cx, cy;
				int				_hoops_PPCRH, _hoops_HPCRH, _hoops_IPCRH, _hoops_CPCRH;
				bool		_hoops_IRACA;

				_hoops_IPCRH = _hoops_CACRH->x;
				_hoops_CPCRH = _hoops_CACRH->y;
				_hoops_HPCRH = _hoops_CACRH->cx;
				_hoops_PPCRH = _hoops_CACRH->cy;

				_hoops_IRACA = false;

				_hoops_SACRH = true;
				/* _hoops_PRGSI _hoops_RH _hoops_GHGPR _hoops_SRHR _hoops_SRHR */
				state->_hoops_CAICI = false;

				cx = _hoops_HPCRH - state->_hoops_CIGRR.x;
				cy = _hoops_PPCRH - state->_hoops_CIGRR.y;

				if (Abs(cx)>Abs(cy)) {
					if (Abs(cy) == 0.0f) {
						_hoops_PPCRH = (int)((float) _hoops_HPCRH *
							(float)state->_hoops_GCGRR.y /
							(float)state->_hoops_GCGRR.x);

						if (_hoops_CPCRH != state->_hoops_SIGRR.y)
							_hoops_CPCRH += (_hoops_CACRH->cy - _hoops_PPCRH);

					}
					else {
						_hoops_HPCRH = (int)((float) _hoops_PPCRH *
							(float)state->_hoops_GCGRR.x /
							(float)state->_hoops_GCGRR.y);

						if (_hoops_IPCRH != state->_hoops_SIGRR.x)
							_hoops_IPCRH += (_hoops_CACRH->cx - _hoops_HPCRH);
					}
				}
				else {
					if (Abs(cx) == 0.0f) {
						_hoops_HPCRH = (int)((float) _hoops_PPCRH *
							(float)state->_hoops_GCGRR.x /
							(float)state->_hoops_GCGRR.y);

						if (_hoops_IPCRH != state->_hoops_SIGRR.x)
							_hoops_IPCRH += (_hoops_CACRH->cx - _hoops_HPCRH);

					}
					else {
						_hoops_PPCRH = (int)((float) _hoops_HPCRH *
							(float)state->_hoops_GCGRR.y /
							(float)state->_hoops_GCGRR.x);

						if (_hoops_CPCRH != state->_hoops_SIGRR.y)
							_hoops_CPCRH += (_hoops_CACRH->cy - _hoops_PPCRH);
					}
				}

				state->_hoops_CIGRR.x = _hoops_HPCRH;
				state->_hoops_CIGRR.y = _hoops_PPCRH;

				if (!_hoops_IRACA) {
				   _hoops_CACRH->x = _hoops_IPCRH;
				   _hoops_CACRH->y = _hoops_CPCRH;
				   _hoops_CACRH->cx = _hoops_HPCRH;
				   _hoops_CACRH->cy = _hoops_PPCRH;
				   _hoops_SACRH = true;
				}
			}

			_hoops_IGGSI = false;
			if (_hoops_SACRH) {
				state->_hoops_CIICI = true;
				return 0;
			}
			state->_hoops_CIICI = true;
			}	break;

#endif
			case WM_PALETTECHANGED: {
				if (word_parameter != (WPARAM) state->_hoops_GGICI &&
					!BIT (state->dc->options._hoops_IRARR,
						  _hoops_GRPCI)) {
					_hoops_RGGSI (state, TRUE, TRUE, TRUE);
					InvalidateRect (state->_hoops_GGICI, NULL, FALSE);
				}
			}	break;


			case WM_QUERYNEWPALETTE: {
				state->_hoops_CIICI = true;
				if (state->_hoops_SRCCI)
					return TRUE;
				return _hoops_RGGSI (state, FALSE, TRUE, TRUE);
			}	_hoops_HHHI;


			case WM_PAINT: {
				_hoops_RGGSI (state, !state->_hoops_SRCCI, FALSE, FALSE);
				_hoops_SGCRH (state, _hoops_GGICI, true, false);
			}	break;


			case WM_SETFOCUS: {
				state->_hoops_SRCCI = true;
			}	break;

			case WM_KILLFOCUS: {

				state->_hoops_SRCCI = false;
			}	break;
		}

		if (state)
				state->_hoops_CIICI = true;
	}


	return DefWindowProc (_hoops_GGICI, message,
						  word_parameter, _hoops_GHIRH);
}


/*
 * _hoops_PGAA
 * _hoops_GICRH _hoops_HGGSP _hoops_SIIRH: _hoops_RICRH _hoops_IRS _hoops_CIAGR _hoops_PGCPR _hoops_SSHRH
 */
LRESULT APIENTRY _hoops_AICRH (
	HWND						_hoops_GGICI,
	UINT						message,
	WPARAM						word_parameter,
	LPARAM						_hoops_GHIRH) {
	Display_Context			*dc;
	LONG						result;
	MSW_Driver_State alter		*state;

	result = 0L;

	if ((dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT)_hoops_GGICI)) != null &&
			(state = _hoops_HICCI ()) != null) {

		state->_hoops_CIICI = false;

		switch (message) {
#ifndef _WIN32_WCE
			case WM_MDICREATE: {
			  _hoops_ARGIP (HEC_MSW_DRIVER, HES_MDI_SUPPORTED_BY_NOWINDOWSHOOK,
					   "MDI Applications are only supported by the NO_WINDOWS_HOOK",
					   "debug option",
					   "HOOPS does not handle MDI messages");
			}	break;
#endif
			case WM_ERASEBKGND:
				/* _hoops_IRISR _hoops_GRS _hoops_RGHH _hoops_RGR */
				return TRUE;
				_hoops_HHHI;

			case WM_SIZE: {
				state->pending_resize = true;
			}	break;

			case WM_PAINT: {
				_hoops_SGCRH (state, _hoops_GGICI, false, true);
			}	break;

			case WM_SETFOCUS: {
				state->_hoops_SRCCI = true;
			}	break;

			case WM_KILLFOCUS: {
				state->_hoops_SRCCI = false;
			}	break;

			case WM_PALETTECHANGED: {
				if (word_parameter != (WPARAM) state->_hoops_GGICI &&
					!BIT (state->dc->options._hoops_IRARR,
						  _hoops_GRPCI)) {
					_hoops_RGGSI (state, false, TRUE, TRUE);
					InvalidateRect (state->_hoops_GGICI, NULL, TRUE);
				}
			}	break;

			case WM_QUERYNEWPALETTE: {
				state->_hoops_CIICI = false;
				result = _hoops_RGGSI (state, FALSE, TRUE, TRUE);
			}	break;

			default:
				break;
		}

		if (result == 0)
			result = CallWindowProc (state->_hoops_GIGRR,
									 _hoops_GGICI, message,
									 word_parameter, _hoops_GHIRH);

		/* _hoops_PIAP _hoops_GHCA _hoops_SHH _hoops_ACSS _hoops_RHSP _hoops_RCPGR _hoops_RPPS _hoops_AACRH _hoops_AASA */
		if ((state = _hoops_HICCI ()) != null)
			state->_hoops_CIICI = true;
	}
	else {
		result = DefWindowProc (_hoops_GGICI, message,
								word_parameter, _hoops_GHIRH);
	}

	return result;
}


/*****************************************************************************
 *****************************************************************************
								_hoops_HRGSI _hoops_IPSCP
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_PGAA
 */
local void _hoops_IRGSI (
	MSW_Driver_State alter *		state,
	_hoops_HHCR const &		_hoops_IHCR) {
	float							_hoops_PIIH = 1.0f;
	float							_hoops_HIIH = 1.0f;
	int								xoffset = 0;
	int								yoffset = 0;

#ifndef _WIN32_WCE


	if (state->_hoops_PIGRR == _hoops_PSPCI &&
		!state->_hoops_GPHCI)
		return;

	if (state->_hoops_GAICI) {
		SIZE	   _hoops_CRGSI;
		SIZE	   printer_win_rect;
		SIZE	   preview_vp_rect;
		SIZE	   _hoops_SRGSI;
		POINT   preview_vp_origin;

		GetViewportExtEx (state->_hoops_PGICI, &_hoops_CRGSI);
		GetViewportExtEx (state->_hoops_AGICI,		 &preview_vp_rect);
		GetWindowExtEx	 (state->_hoops_PGICI, &printer_win_rect);
		GetWindowExtEx	 (state->_hoops_AGICI,		 &_hoops_SRGSI);

		_hoops_PIIH = (float)(printer_win_rect.cx * preview_vp_rect.cx)/(float)(_hoops_SRGSI.cx * _hoops_CRGSI.cx);
		_hoops_HIIH = (float)(printer_win_rect.cy * preview_vp_rect.cy)/(float)(_hoops_SRGSI.cy * _hoops_CRGSI.cy);

		GetViewportOrgEx (state->_hoops_AGICI, &preview_vp_origin);

		xoffset = preview_vp_origin.x;
		yoffset = preview_vp_origin.y;
	}

	SetRectRgn (state->_hoops_AAICI,
				(int)(_hoops_IHCR->_hoops_AGAA.left * _hoops_PIIH) + xoffset,
				(int)((state->yfudge - _hoops_IHCR->_hoops_AGAA.top) * _hoops_HIIH) + yoffset,
				(int)(_hoops_IHCR->_hoops_AGAA.right * _hoops_PIIH) + 1 + xoffset,
				(int)((state->yfudge - _hoops_IHCR->_hoops_AGAA.bottom) * _hoops_HIIH) + 1 + yoffset);

	SelectClipRgn (state->_hoops_AGICI, state->_hoops_AAICI);
	if (state->_hoops_SRRRR)
		SelectClipRgn (state->_hoops_IGICI, state->_hoops_AAICI);


	if (_hoops_IHCR->_hoops_HCHH != null) {
		if (state->_hoops_HAICI != _hoops_IHCR->_hoops_HCHH->_hoops_CPA) {
			_hoops_ASHH const *		_hoops_CRAIR = _hoops_IHCR->_hoops_HCHH->_hoops_PSHH;
			POINT							_hoops_HRIGA[256];
			POINT *							points = _hoops_HRIGA;
			int								i;

			if (_hoops_CRAIR->count > _hoops_GGAPR(_hoops_HRIGA))
				POOL_ALLOC_ARRAY_CACHED (points, _hoops_CRAIR->count, POINT, _hoops_IHCR->_hoops_SRA->memory_pool);

			for (i=0; i<_hoops_CRAIR->count; ++i) {
				points[i].x = (int)(_hoops_CRAIR->points[i].x * _hoops_PIIH) + xoffset;
				points[i].y = (int)((state->yfudge - _hoops_CRAIR->points[i].y) * _hoops_HIIH) + yoffset;
			}

			DeleteObject (state->_hoops_PAICI);
			state->_hoops_PAICI = CreatePolygonRgn (points, _hoops_CRAIR->count, WINDING);
			state->_hoops_HAICI = _hoops_IHCR->_hoops_HCHH->_hoops_CPA;

			if (_hoops_CRAIR->count > _hoops_GGAPR(_hoops_HRIGA))
				FREE_ARRAY (points, _hoops_CRAIR->count, POINT);
		}

		ExtSelectClipRgn (state->_hoops_AGICI, state->_hoops_PAICI, RGN_AND);
		if (state->_hoops_SRRRR)
			ExtSelectClipRgn (state->_hoops_IGICI, state->_hoops_PAICI, RGN_AND);
	}
#endif
}

/*
 * _hoops_SRAC
 */
local void draw_dc_text (
	Net_Rendition const &		nr,
	DC_Point const *			where,
	int							count,
	Karacter const *			kstring) {
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	//_hoops_GAGSI _hoops_RCIC *	_hoops_CSPH = _hoops_SCII->_hoops_GHCSR;
	DC_Point const *			_hoops_RAGSI = where;


	/*_hoops_SIGP _hoops_AAGSI*/
	draw_and_reset_poly_cache(state, true);

	if (nr->transform_rendition->_hoops_CPA != state->_hoops_CSC._hoops_GCICI) {
		_hoops_IRGSI (state,nr->transform_rendition);
		state->_hoops_CSC._hoops_GCICI = nr->transform_rendition->_hoops_CPA;
	}


	if (_hoops_HRCIR->_hoops_CPA != state->_hoops_CSC._hoops_RPCI) {
		_hoops_SARCI alter			*sizedfont;
		HFONT						_hoops_HCGCI;
		long						_hoops_GICCI;
#ifndef _WIN32_WCE
#ifdef MINITAB
	UINT _hoops_PAGSI = TA_BOTTOM | TA_LEFT | TA_NOUPDATECP;
#else
	UINT _hoops_PAGSI = TA_BASELINE | TA_LEFT | TA_NOUPDATECP;
#endif
#endif

		sizedfont = (_hoops_SARCI *)_hoops_HRCIR->font->_hoops_GAASR;
		_hoops_GICCI = (long)(_hoops_HRCIR->rotation * 10.0f);

#ifndef _WIN32_WCE
		/* _hoops_GHAII 2005 _hoops_GHGA _hoops_RGR _hoops_RRPC _hoops_CSAP _hoops_PCCP _hoops_HAGSI _hoops_CAGRH _hoops_IPHR _hoops_AARI _hoops_HII _hoops_IAGSI _hoops_CAGSI*/
		SetTextAlign  (state->_hoops_AGICI, _hoops_PAGSI);
		_hoops_HCGCI = _hoops_HHCCI (state->dc, 
			state->_hoops_GHHCI, state->_hoops_CHHCI, state->_hoops_PHHCI, 
			sizedfont->_hoops_GPRCI, 
			_hoops_HRCIR->font->_hoops_RACSR*_hoops_HRCIR->font->_hoops_GRGGH, 
			_hoops_GICCI, _hoops_HRCIR->width_scale, sizedfont->_hoops_PRPHA);
		SetTextAlign  (state->_hoops_AGICI, _hoops_PAGSI);
#endif

		if (state->_hoops_CSC._hoops_RCICI != _hoops_HRCIR->color)
			(*state->_hoops_RSICI)(state, &_hoops_HRCIR->color);

		if (nr->_hoops_SRA->_hoops_CPIGA) {
			if (state->_hoops_CSC._hoops_ACICI != _hoops_HRCIR->color)
				(*state->_hoops_ASICI)(state, &_hoops_HRCIR->color);

			if (state->_hoops_CSC._hoops_HCICI != OPAQUE)
				SetBkMode (state->_hoops_AGICI, state->_hoops_CSC._hoops_HCICI = OPAQUE);
		}
		else {
			if (state->_hoops_CSC._hoops_HCICI != TRANSPARENT)
				SetBkMode (state->_hoops_AGICI, state->_hoops_CSC._hoops_HCICI = TRANSPARENT);
		}

		if (_hoops_HCGCI) {
			SelectObject (state->_hoops_AGICI, _hoops_HCGCI);
			state->_hoops_CSC.font = _hoops_CCICI;
		}

		state->_hoops_CSC._hoops_RPCI = _hoops_HRCIR->_hoops_CPA;
		state->_hoops_CSC._hoops_SIICI = _hoops_CCC;
	}

#ifndef _WIN32_WCE

	if (state->_hoops_PPHCI) {

		state->_hoops_ARCCI = _hoops_SGCCI;
	}
	else {
		(void) TextOutW (state->_hoops_AGICI,
			_hoops_HCCCI (_hoops_RAGSI->x),
			state->yfudge - _hoops_HCCCI (_hoops_RAGSI->y),
			(LPCWSTR)kstring, count);
	}
#endif
}


/*
 * _hoops_SRAC
 */
local bool measure_char(
	Net_Rendition const & nr,
	Font_Instance const * instance,
	Karacter _hoops_IPCSR,
	float alter *_hoops_GGGS,
	bool alter *_hoops_CPCSR,
	void ** _hoops_HPSRH) {
/*_hoops_ASIGA _hoops_RGR _hoops_RRP _hoops_HHH _hoops_HPIHR _hoops_GPP _hoops_SAGSI */
#ifndef _WIN32_WCE
	MSW_Driver_State alter *state = _hoops_IICCI ();
	_hoops_SARCI *sizedfont = (_hoops_SARCI*)instance->_hoops_GAASR;
	HFONT	_hoops_HCGCI = 0;

	*_hoops_CPCSR = true;
	*_hoops_GGGS = 0;

	if (instance->_hoops_RRGGH) {

		bool result;

		/*_hoops_RSAIP _hoops_RSAIP _hoops_RSAIP*/
		((Font_Instance alter*)instance)->_hoops_GAASR = (void*)sizedfont->_hoops_RPRCI;

		result = HI_W32_measure_char_stenciled(nr, instance, _hoops_IPCSR, _hoops_GGGS, _hoops_CPCSR, _hoops_HPSRH);    

		/*_hoops_RSAIP _hoops_RSAIP _hoops_RSAIP*/
		((Font_Instance alter*)instance)->_hoops_GAASR = (void*)sizedfont;

		return result;
	}

	_hoops_HCGCI = _hoops_HHCCI (state->dc,
		state->_hoops_GHHCI, state->_hoops_CHHCI, state->_hoops_PHHCI,
	sizedfont->_hoops_GPRCI, 
	instance->_hoops_RACSR * instance->_hoops_GRGGH, 
	0, 1.0f, 1.0f);

	if (_hoops_HCGCI) {
		int _hoops_GPGSI=0;
		ABC _hoops_HPCSA;
		int _hoops_RPGSI = 0;
		int _hoops_APGSI = 0;

		if (state->_hoops_CSC.font != _hoops_HCGCI) {
			SelectObject (state->_hoops_AGICI, (state->_hoops_CSC.font = _hoops_HCGCI));
			state->_hoops_CSC._hoops_RPCI = _hoops_CCC;
		}

		if ((_hoops_RPGSI = GetCharABCWidthsW (state->_hoops_AGICI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_HPCSA)) == 0 &&
				!GetCharWidth32W (state->_hoops_AGICI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_GPGSI)) {

			/* _hoops_HSPC _hoops_IS _hoops_HSSPR _hoops_RCAPI _hoops_SAHR _hoops_IH _hoops_IGAAI */
			_hoops_GPGSI = -1;

			if ((_hoops_RPGSI = GetCharABCWidths (state->_hoops_AGICI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_HPCSA)) == 0 &&
				!GetCharWidth (state->_hoops_AGICI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_GPGSI)) {

				HDC _hoops_PPGSI = GetDC(state->_hoops_GGICI);
				SelectObject (_hoops_PPGSI, (state->_hoops_CSC.font = _hoops_HCGCI));
				state->_hoops_CSC._hoops_RPCI = _hoops_CCC;
				_hoops_APGSI = true;

				if ((_hoops_RPGSI = GetCharABCWidthsW (_hoops_PPGSI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_HPCSA)) == 0 &&
					!(GetCharWidth32W (_hoops_PPGSI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_GPGSI)) &&
					(_hoops_RPGSI = GetCharABCWidths (_hoops_PPGSI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_HPCSA)) == 0 &&
					!GetCharWidth (_hoops_PPGSI, _hoops_IPCSR, _hoops_IPCSR, &_hoops_GPGSI)) {
					/* _hoops_SGPR _hoops_RH _hoops_HPGSI _hoops_GAR _hoops_IRS _hoops_IIPGA _hoops_AHC. _hoops_HHIGR _hoops_PPPPR'_hoops_RA _hoops_IHSH _hoops_PPGC _hoops_RPHR,
					 * _hoops_HIH _hoops_SCH _hoops_GRS _hoops_HPGR _hoops_CHGC _hoops_SHH _hoops_GGGR. */
					_hoops_GPGSI = sizedfont->_hoops_ACGCI;
				}
			}
		}

		if (_hoops_RPGSI) {

			GCP_RESULTSW _hoops_IPGSI;
			DWORD _hoops_PSRGA = 0;
			DWORD result;
			unsigned short glyph;
			_hoops_IPGSI.lStructSize=sizeof(GCP_RESULTSW);
			_hoops_IPGSI.lpOutString=0;
			_hoops_IPGSI.lpOrder=0;
			_hoops_IPGSI.lpDx=0;
			_hoops_IPGSI.lpCaretPos=0;
			_hoops_IPGSI.lpClass=0;
			_hoops_IPGSI.lpGlyphs=(LPWSTR)&glyph;
			_hoops_IPGSI.nGlyphs=1;
			_hoops_IPGSI.nMaxFit=0;

			if ((result = GetCharacterPlacementW(state->_hoops_AGICI, (LPCWSTR)&_hoops_IPCSR, 1, 0, &_hoops_IPGSI, _hoops_PSRGA)) != 0) {

				if (glyph == 0x0000) {
					*_hoops_GGGS = 0.0f;
					*_hoops_CPCSR = true;
					*_hoops_HPSRH = (void*)0;
					return true;
				}
			}

			// _hoops_RPP (_hoops_RAHII._hoops_CPGSI<0) _hoops_RAHII._hoops_CPGSI = 0;
			// _hoops_RPP (_hoops_RAHII._hoops_SPGSI<0) _hoops_RAHII._hoops_SPGSI = 0;
			_hoops_GPGSI = _hoops_HPCSA.abcA + _hoops_HPCSA.abcB + _hoops_HPCSA.abcC;
		}

		*_hoops_GGGS = (float)_hoops_GPGSI;
		*_hoops_CPCSR = false;
		*_hoops_HPSRH = (void*)1;
	}

#endif
	return true;
}


/*
 * _hoops_SRAC
 */
local void unload_font (
	Display_Context const	*dc,
	Font_Instance alter		*instance) {

	_hoops_SARCI *sizedfont = (_hoops_SARCI *) instance->_hoops_GAASR;

	UNREFERENCED(dc);

	if (sizedfont->_hoops_RPRCI != null) {
		/* _hoops_RSAIP _hoops_RSAIP _hoops_RSAIP */
		instance->_hoops_GAASR = (void*)sizedfont->_hoops_RPRCI;
		HI_W32_unload_font_stenciled(dc, instance);
	}

	FREE (sizedfont, _hoops_SARCI);
}


/*
 * _hoops_PGAA
 */
local _hoops_SARCI * _hoops_GHGSI (
	Display_Context const *dc,
	char const				*_hoops_HPRRI,
	Font_Instance alter	*instance,
	MSW_Driver_State alter		*state) {

#ifndef _WIN32_WCE
	_hoops_RRPRH alter	  *_hoops_IRSRA = _hoops_ARPRH ();
	HFONT					_hoops_HCGCI = 0;
	HFONT					_hoops_RHGSI;
	_hoops_SGRRR		*_hoops_HSSRH;
	_hoops_SARCI *			sizedfont = 0;
	TEXTMETRIC				tm;
	unsigned int			_hoops_AHGSI = 0;
	char					error[4096];
	_hoops_GCGCI alter *_hoops_RHCSR = 0;

	_hoops_HSSRH = HI_W32_find_font (_hoops_IRSRA->font_list, _hoops_HPRRI);

	if (!_hoops_HSSRH)			
		_hoops_HSSRH = HI_W32_find_font (state->_hoops_GRRRR, _hoops_HPRRI);
	

	if (!_hoops_HSSRH) {
		_hoops_ARGIP (HEC_MSW_DRIVER, HES_LOAD_FONT_FAILED,
					   "Unable to find font in internally recorded font list",
					   _hoops_HPRRI, "");
		return 0;
	}

	_hoops_RHCSR = (_hoops_GCGCI alter *)
		HI_W32_load_font_stenciled(dc, _hoops_HPRRI, instance, state->_hoops_PGICI, 
			&state->_hoops_GRRRR, &_hoops_IRSRA->font_list);

	if(_hoops_RHCSR){
		_hoops_HCGCI = _hoops_HHCCI (state->dc,
			state->_hoops_GHHCI, state->_hoops_CHHCI, state->_hoops_PHHCI, 
			&_hoops_HSSRH->_hoops_PCGCI, _hoops_RHCSR->_hoops_RCGCI, 0, 1.0f, 1.0f);
	}

	if (!_hoops_HCGCI) {
		sprintf (error, "Create Font Indirect failed with return code %ld on font", _hoops_AHGSI);
		_hoops_ARGIP (HEC_MSW_DRIVER, HES_LOAD_FONT_FAILED, error, _hoops_HPRRI, "");

		if (_hoops_RHCSR)
			HI_W32_unload_font_stenciled(dc, (Font_Instance alter *)_hoops_RHCSR);

		return 0;
	}

	ZALLOC (sizedfont, _hoops_SARCI);

	sizedfont->_hoops_RPRCI = _hoops_RHCSR;

	_hoops_RHGSI = (HFONT) SelectObject (state->_hoops_PGICI, _hoops_HCGCI);

	if (!GetTextMetrics (state->_hoops_PGICI, &tm)) {

		/* _hoops_PHGSI _hoops_HRCSR _hoops_PPR _hoops_PHIS */
		_hoops_AHGSI = GetLastError ();

		sprintf (error, "GetTextMetrics failed with return code %ld on font", _hoops_AHGSI);
		_hoops_ARGIP (HEC_MSW_DRIVER, HES_LOAD_FONT_FAILED, error, _hoops_HPRRI, "");

		FREE (sizedfont, _hoops_SARCI);
		sizedfont=0;
	}
	else {
		sizedfont->_hoops_GPRCI = &_hoops_HSSRH->_hoops_PCGCI;
		sizedfont->_hoops_ACGCI = tm.tmMaxCharWidth;
		sizedfont->_hoops_PRPHA = _hoops_HSSRH->_hoops_PRPHA;
	}

	SelectObject (state->_hoops_PGICI, _hoops_RHGSI);

	/* _hoops_HHGSI _hoops_APSP _hoops_ARRGI _hoops_SAIP */
	instance->_hoops_HRGGH = false;

	return sizedfont;
#else
	return 0;
#endif
}


/*
 * _hoops_SRAC
 */
local void * load_font (
	Display_Context const *dc,
	char const *name,
	Font_Instance alter * instance) {

	MSW_Driver_State alter			*state = _hoops_HICCI ();
	_hoops_SARCI					*sizedfont;


	if (!state->_hoops_GAHCI) {
		switch (state->_hoops_HGICI) {
			case _hoops_IGHCI:
				state->_hoops_PGICI = GetDC (GetDesktopWindow ());
				break;
			case _hoops_CGHCI:
				state->_hoops_PGICI =
					get_printer_DC (dc->options._hoops_ARPSR);
				break;
			case _hoops_SCASA:
				 state->_hoops_PGICI = state->_hoops_AGICI =
						(HDC) dc->options._hoops_ISPRP;
				break;
		}
	}

	/* _hoops_HHCS _hoops_IS _hoops_GGARP _hoops_RGR _hoops_HRCSR _hoops_PPR _hoops_ISPR _hoops_IH _hoops_HPCS */
	sizedfont = _hoops_GHGSI (dc, name, instance, state);


	if (!sizedfont) {
		/* _hoops_AIRS - _hoops_HPPR _hoops_IHGSI */
		if (!_hoops_IGGPA ("Arial-GDI-VECTOR", name))
				sizedfont = _hoops_GHGSI (dc, "Arial-GDI-VECTOR", instance, state);

		if (!sizedfont) {
			/* _hoops_CHGSI _hoops_AHCI _hoops_ARPC - _hoops_SASRR _hoops_SRIGP */
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Arial Font could not be loaded");
		}
	}

	if (!state->_hoops_GAHCI) {
		switch (state->_hoops_HGICI) {
			case _hoops_IGHCI: {
				ReleaseDC (GetDesktopWindow (), state->_hoops_PGICI);
			}	break;
			case _hoops_CGHCI: {
				DeleteDC (state->_hoops_PGICI);
			}	break;
			case _hoops_SCASA: break;
		}
	}

	return (void*)sizedfont;
}

/*
 * _hoops_SRAC
 */
local bool _hoops_CSCSP(
	Net_Rendition const &	nr,
	_hoops_IGPIR const			*_hoops_RRCSP,
	_hoops_IGPIR alter			*_hoops_ARCSP) {
	
	return HI_W32_name_font(nr, _hoops_RRCSP, _hoops_ARCSP);
}

/*
 * _hoops_SRAC
 */
local  bool _hoops_GGSSP(
	Net_Rendition const &	nr,
	Font_Instance const		*specific) {

	UNREFERENCED(specific);

	if (nr->_hoops_SISI->transform == FT_FULL ||
		BIT(nr->_hoops_SRA->flags, _hoops_CRAGH))
		return true;

	return false;
}

/*
 * _hoops_SRAC
 */
local _hoops_RAARP * _hoops_RGSSP (
	Net_Rendition const & nr,
	Font_Instance const	*instance,
	unsigned short			_hoops_IPCSR,
	int						bitmap_height,
	int						bolding_level,
	float					xrslant,
	float					xrrotation,
	float					xrwidth_scale,
	bool				antialias) {

	_hoops_SARCI *sizedfont = (_hoops_SARCI *) instance->_hoops_GAASR;
	_hoops_RAARP *stencil=0;

	UNREFERENCED(nr);

	if (!sizedfont->_hoops_RPRCI)
		return 0;

	/*_hoops_RSAIP _hoops_RSAIP _hoops_RSAIP*/
	((Font_Instance alter*)instance)->_hoops_GAASR = (void*)sizedfont->_hoops_RPRCI;

	stencil = HI_W32_make_font_stencil (instance, _hoops_IPCSR, 
									bitmap_height, bolding_level,
									xrslant,xrrotation,xrwidth_scale,
									antialias); 

	/*_hoops_RSAIP _hoops_RSAIP _hoops_RSAIP*/
	((Font_Instance alter*)instance)->_hoops_GAASR = (void*)sizedfont;

	return stencil;
}


/*
 * _hoops_SRAC
 */
local void find_all_fonts (
	Display_Context alter *dc) {

	MSW_Driver_State alter *state = _hoops_HICCI ();
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	HI_W32_find_all_fonts (dc, &state->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}

/*
 * _hoops_SRAC
 */
local bool _hoops_AACSR (
	Display_Context alter	*dc,
	char const					 *_hoops_PACSR) {

	MSW_Driver_State alter *state = _hoops_HICCI ();
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	return HI_W32_find_one_font (dc, _hoops_PACSR, state->_hoops_PGICI, &state->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}

/*	
 * _hoops_SRAC
 */
local void _hoops_CACSR (
	Display_Context alter *dc) {

	MSW_Driver_State alter *state = _hoops_HICCI ();
	_hoops_RRPRH alter *_hoops_IRSRA = _hoops_ARPRH ();

	HI_W32_find_basic_fonts (dc, state->_hoops_PGICI, &state->_hoops_GRRRR, &_hoops_IRSRA->font_list);
}




/*****************************************************************************
 *****************************************************************************
							 _hoops_CSSGR _hoops_IPHH _hoops_PARPI
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_SRAC
 */
local void _hoops_SCCSR (
	Display_Context const	*dc,
	unsigned int				r,
	unsigned int				g,
	unsigned int				b,
	int							index) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();
	LPPALETTEENTRY				entry;


	state->_hoops_SAICI = true;

	entry = &state->_hoops_CHICI->palPalEntry[index];

	entry->peRed   = (BYTE)r;
	entry->peGreen = (BYTE)g;
	entry->peBlue  = (BYTE)b;
	entry->peFlags = 0;

	state->_hoops_SHICI[index] = true;
}


/*****************************************************************************
 *****************************************************************************
							  _hoops_CSIGP _hoops_PARPI
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_PGAA
 */
local void _hoops_SHGSI (
	MSW_Driver_State alter				*state) {
	Display_Context const		*dc = state->dc;

	state->_hoops_CSC._hoops_RPCI  = _hoops_CCC;
	state->_hoops_CSC._hoops_SIICI  = _hoops_CCC;
	state->_hoops_CSC._hoops_GCICI = _hoops_CCC;
	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		state->_hoops_CSC._hoops_RCICI	   = RGBAS32 (255,255,255,255);	// ~0
		state->_hoops_CSC._hoops_ACICI	   = RGBAS32 (255,255,255,255);
	}
	else {
		state->_hoops_CSC._hoops_RCICI	   = _hoops_IAASP;
		state->_hoops_CSC._hoops_ACICI	   = _hoops_IAASP;
	}
	state->_hoops_CSC._hoops_HCICI			   = _hoops_PCICI;
	state->_hoops_CSC.font			   = _hoops_CCICI;

	state->_hoops_CSC._hoops_AGAA.left = 0;
	state->_hoops_CSC._hoops_AGAA.right = 0;
	state->_hoops_CSC._hoops_AGAA.bottom = 0;
	state->_hoops_CSC._hoops_AGAA.top = 0;	
}


#define _hoops_GIGSI			(short) 1
#define _hoops_RIGSI				(short) 2
#define _hoops_AIGSI		(short) 3

#define _hoops_PIGSI(_hoops_HIGSI, _hoops_PHPSR, color, contrast_color) \
		_hoops_IIGSI (_hoops_GIGSI, _hoops_HIGSI, \
					  (void *) &(color), \
					  (void *) &(contrast_color), \
					  (void *) &(_hoops_PHPSR), 0, 0, 0, \
					  (MSW_Driver_State alter *)state, 0)

#define _hoops_CIGSI(_hoops_HIGSI, _hoops_SIGSI) \
		_hoops_IIGSI (_hoops_RIGSI, _hoops_HIGSI, \
					  (void *) &(_hoops_SIGSI), \
					  (void *) null, \
					  null, 0, 0, 0, \
					  (MSW_Driver_State alter *)state, 0)

#define _hoops_GCGSI(_hoops_HIGSI, _hoops_CPA, height, width, \
								  _hoops_RCGSI, _hoops_ACGSI, pattern, direction) \
		_hoops_IIGSI (_hoops_AIGSI, _hoops_HIGSI, \
					  (void *) &(_hoops_RCGSI), \
					  (void *) &(_hoops_ACGSI), \
					  (void *) pattern, _hoops_CPA, height, width, \
					  (MSW_Driver_State alter *)state, direction)


/*
 * _hoops_PGAA
 */
local void _hoops_PCGSI (
	Display_Context const	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_SGH _hoops_IRS _hoops_HCGSI _hoops_IPHCI */
	if (IsWindow (state->_hoops_GGICI))
		SelectObject (state->_hoops_AGICI, state->_hoops_SPCCI);
	/* _hoops_PS _hoops_ICGSI _hoops_PPPPR'_hoops_RA _hoops_AA _hoops_RGR _hoops_AAGAI */
	_hoops_SHGSI (state);
}


/*
 * _hoops_PGAA
 */
local void _hoops_ISICI (
	MSW_Driver_State alter	*state,
	_hoops_ARRCI alter	*_hoops_SPHCI,
	_hoops_ARRCI alter	*_hoops_CCGSI) {

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_SGH _hoops_IRS _hoops_HCGSI _hoops_IPHCI */
	SelectObject (state->_hoops_AGICI, state->_hoops_SPCCI);

	DeleteObject (_hoops_SPHCI->_hoops_HARCI);

	_hoops_CCGSI->_hoops_PRRCI = _hoops_SPHCI->_hoops_PRRCI;
	FREE (_hoops_SPHCI, _hoops_ARRCI);
	/* _hoops_PS _hoops_ICGSI _hoops_PPPPR'_hoops_RA _hoops_AA _hoops_RGR _hoops_AAGAI */
	_hoops_SHGSI (state);
}


/*
 * _hoops_PGAA
 */
local HBRUSH _hoops_IIGSI (
	short						_hoops_HRRCI,
	RGBAS32 const			*_hoops_HIGSI,
	void						*_hoops_SCGSI,
	void						*_hoops_GSGSI,
	void						*_hoops_RSGSI,
	Integer32				_hoops_ACHI,
	int							_hoops_ASGSI,
	int							_hoops_PSGSI,
	MSW_Driver_State alter			*state,
	int							direction) {
#ifndef _WIN32_WCE
	_hoops_ARRCI alter			*_hoops_SPHCI;
	_hoops_ARRCI alter			*_hoops_HSGSI;
	_hoops_RRRCI alter			*_hoops_ISGSI;
	int							_hoops_CSGSI;
	Display_Context const	*dc = state->dc;
	int							*_hoops_IRRCI =
												(int *)
													_hoops_RSGSI;
	unsigned char const			*_hoops_PGPH =
												(unsigned char *)
													_hoops_RSGSI;
	COLORREF					*_hoops_SSGSI =
												(COLORREF *)
													_hoops_SCGSI;
	/*_hoops_SPRS		_hoops_GGRSI _hoops_RCIC		*_hoops_RGRSI =
												(_hoops_GGRSI *)
													_hoops_AGRSI;*/
	Driver_Color	 const		*_hoops_RARCI =
												(Driver_Color *)
													_hoops_SCGSI;
	Driver_Color	 const		*_hoops_AARCI =
												(Driver_Color *)
													_hoops_GSGSI;
	int							_hoops_GCAIR = _hoops_ACHI;
	int							_hoops_CPA = _hoops_ACHI;


	_hoops_HSGSI = _hoops_SPHCI = state->_hoops_SPHCI;
	_hoops_CSGSI = false;

	while (_hoops_SPHCI->_hoops_PRRCI != NULL) {
		_hoops_HSGSI = _hoops_SPHCI;
		_hoops_SPHCI=_hoops_SPHCI->_hoops_PRRCI;
		if (_hoops_HRRCI == _hoops_SPHCI->_hoops_HRRCI) {
			if (*_hoops_HIGSI == _hoops_IAASP) {
				/* _hoops_GSSR _hoops_PGRSI _hoops_AGIR */
				switch (_hoops_HRRCI) {
					case _hoops_RIGSI: {
						if (*_hoops_SSGSI == _hoops_SPHCI->_hoops_RARCI._hoops_CRRCI) {
							_hoops_CSGSI = true;
						}
					}	break;

					case _hoops_GIGSI: {
						if (*_hoops_IRRCI == _hoops_SPHCI->_hoops_IRRCI &&
							*_hoops_AARCI == _hoops_SPHCI->_hoops_AARCI &&
							*_hoops_RARCI == _hoops_SPHCI->_hoops_RARCI._hoops_GARCI) {
							_hoops_CSGSI = true;
						}
					}	break;

				   case _hoops_AIGSI: {
						if (_hoops_SPHCI->_hoops_PARCI == _hoops_CPA &&
							*_hoops_AARCI == _hoops_SPHCI->_hoops_AARCI &&
							*_hoops_RARCI == _hoops_SPHCI->_hoops_RARCI._hoops_GARCI) {
							_hoops_CSGSI = true;
						}
					}	break;
				}
			}
			else {
				/* _hoops_PRISP _hoops_HSP _hoops_AGIR ! */
				switch (_hoops_HRRCI) {
					case _hoops_RIGSI: {
						if (_hoops_SPHCI->_hoops_RARCI._hoops_GARCI == *_hoops_HIGSI) {
							_hoops_CSGSI = true;
						}
					}	break;

					case _hoops_GIGSI: {
						if (_hoops_SPHCI->_hoops_IRRCI == *_hoops_IRRCI &&
							_hoops_SPHCI->_hoops_AARCI == *_hoops_AARCI &&
							_hoops_SPHCI->_hoops_RARCI._hoops_GARCI == *_hoops_HIGSI) {
							_hoops_CSGSI = true;
						}
					}	break;

				   case _hoops_AIGSI: {
						if (_hoops_SPHCI->_hoops_PARCI == _hoops_CPA &&
							_hoops_SPHCI->_hoops_AARCI == *_hoops_AARCI &&
							_hoops_SPHCI->_hoops_RARCI._hoops_GARCI == *_hoops_HIGSI) {
							_hoops_CSGSI = true;
						}
					}	break;
				}
			}
			if (_hoops_CSGSI) {
				/*
				* _hoops_PS _hoops_AIAH _hoops_HS _hoops_SPR - _hoops_GGCR _hoops_RGR _hoops_IPSP _hoops_IS _hoops_RH _hoops_HIGR
				* _hoops_IIGR _hoops_IPHCI _hoops_SSHSR _hoops_PPR _hoops_GPISR _hoops_RH _hoops_RPR _hoops_IIGR _hoops_SSHSR
				*/
				break;
			}
		}
	}

	if (!_hoops_CSGSI) {
		/* _hoops_IASHR ... _hoops_SR _hoops_IRPSR'_hoops_RA _hoops_SSS _hoops_IRS _hoops_PSSP */
		if (*state->_hoops_IHHCI == *state->_hoops_AHHCI) {
			/*
			 * _hoops_PS _hoops_HS _hoops_IS _hoops_RHGPA _hoops_SPR - _hoops_SHR _hoops_SGH _hoops_RH _hoops_HGRSI _hoops_SPR _hoops_GGR _hoops_RH _hoops_HIGR
			 * _hoops_CR _hoops_SR _hoops_RHHSR _hoops_SCH _hoops_GGR _hoops_IGRSI _hoops_AGR
			 */

			/* _hoops_AGGA _hoops_AASA _hoops_HCR _hoops_IIGR _hoops_RH _hoops_SSHSR _hoops_PPR _hoops_CRGS _hoops_PSCR _hoops_IS _hoops_CIH _hoops_RH _hoops_IPHCI */
			_hoops_ISGSI = _hoops_SPHCI->_hoops_AGRCI;
			while (_hoops_ISGSI != NULL) {
				_hoops_RRRCI alter *_hoops_CGRSI;

				_hoops_PCGSI (_hoops_ISGSI->dc);
				_hoops_CGRSI = _hoops_ISGSI;
				_hoops_ISGSI = _hoops_ISGSI->_hoops_AGRCI;
				FREE (_hoops_CGRSI, _hoops_RRRCI);
			}
			/* _hoops_CPGP _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_RPRS _hoops_RGR _hoops_RARP _hoops_SAHR _hoops_CPCS _hoops_SCH */
			DeleteObject (_hoops_SPHCI->_hoops_HARCI);
		}
		else {
			/* _hoops_CICR _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SPR */
			ALLOC (_hoops_SPHCI, _hoops_ARRCI);
			_hoops_SPHCI->_hoops_PRRCI =
				state->_hoops_SPHCI->_hoops_PRRCI;
			state->_hoops_SPHCI->_hoops_PRRCI =
				_hoops_SPHCI;
			(*state->_hoops_IHHCI)++;
		}

		/* _hoops_SGRSI: _hoops_GRRSI _hoops_RSSA _hoops_IS _hoops_RH _hoops_SRS _hoops_RRRSI _hoops_RARP */

		_hoops_SPHCI->_hoops_HRRCI		= _hoops_HRRCI;
		_hoops_SPHCI->_hoops_AGRCI			= NULL;

#			define _hoops_ARRSI \
					_hoops_GHIA (\
						bit = *layer++; \
						*_hoops_PAGR++ = BIT (bit, 0x01) ? _hoops_IPHHP : _hoops_SIPI; \
						*_hoops_PAGR++ = BIT (bit, 0x02) ? _hoops_IPHHP : _hoops_SIPI; \
						*_hoops_PAGR++ = BIT (bit, 0x04) ? _hoops_IPHHP : _hoops_SIPI; \
						*_hoops_PAGR++ = BIT (bit, 0x08) ? _hoops_IPHHP : _hoops_SIPI; \
						*_hoops_PAGR++ = BIT (bit, 0x10) ? _hoops_IPHHP : _hoops_SIPI; \
						*_hoops_PAGR++ = BIT (bit, 0x20) ? _hoops_IPHHP : _hoops_SIPI; \
						*_hoops_PAGR++ = BIT (bit, 0x40) ? _hoops_IPHHP : _hoops_SIPI; \
						*_hoops_PAGR++ = BIT (bit, 0x80) ? _hoops_IPHHP : _hoops_SIPI;)

#				define _hoops_PRRSI \
					_hoops_GHIA (\
						bit = *layer++; \
						if (BIT (bit, 0x01))  *_hoops_PAGR = _hoops_IPHHP; ++_hoops_PAGR; \
						if (BIT (bit, 0x02))  *_hoops_PAGR = _hoops_IPHHP; ++_hoops_PAGR; \
						if (BIT (bit, 0x04))  *_hoops_PAGR = _hoops_IPHHP; ++_hoops_PAGR; \
						if (BIT (bit, 0x08))  *_hoops_PAGR = _hoops_IPHHP; ++_hoops_PAGR; \
						if (BIT (bit, 0x10))  *_hoops_PAGR = _hoops_IPHHP; ++_hoops_PAGR; \
						if (BIT (bit, 0x20))  *_hoops_PAGR = _hoops_IPHHP; ++_hoops_PAGR; \
						if (BIT (bit, 0x40))  *_hoops_PAGR = _hoops_IPHHP; ++_hoops_PAGR; \
						if (BIT (bit, 0x80))  *_hoops_PAGR = _hoops_IPHHP; ++_hoops_PAGR;)

#				define _hoops_HRRSI \
					_hoops_GHIA (\
						bit = *layer++; \
						*_hoops_PAGR++ = BIT (bit, 0x01) ? _hoops_IPHHP.b : _hoops_SIPI.b; \
						*_hoops_PAGR++ = BIT (bit, 0x01) ? _hoops_IPHHP.g : _hoops_SIPI.g; \
						*_hoops_PAGR++ = BIT (bit, 0x01) ? _hoops_IPHHP.r : _hoops_SIPI.r; \
						*_hoops_PAGR++ = BIT (bit, 0x02) ? _hoops_IPHHP.b : _hoops_SIPI.b; \
						*_hoops_PAGR++ = BIT (bit, 0x02) ? _hoops_IPHHP.g : _hoops_SIPI.g; \
						*_hoops_PAGR++ = BIT (bit, 0x02) ? _hoops_IPHHP.r : _hoops_SIPI.r; \
						*_hoops_PAGR++ = BIT (bit, 0x04) ? _hoops_IPHHP.b : _hoops_SIPI.b; \
						*_hoops_PAGR++ = BIT (bit, 0x04) ? _hoops_IPHHP.g : _hoops_SIPI.g; \
						*_hoops_PAGR++ = BIT (bit, 0x04) ? _hoops_IPHHP.r : _hoops_SIPI.r; \
						*_hoops_PAGR++ = BIT (bit, 0x08) ? _hoops_IPHHP.b : _hoops_SIPI.b; \
						*_hoops_PAGR++ = BIT (bit, 0x08) ? _hoops_IPHHP.g : _hoops_SIPI.g; \
						*_hoops_PAGR++ = BIT (bit, 0x08) ? _hoops_IPHHP.r : _hoops_SIPI.r; \
						*_hoops_PAGR++ = BIT (bit, 0x10) ? _hoops_IPHHP.b : _hoops_SIPI.b; \
						*_hoops_PAGR++ = BIT (bit, 0x10) ? _hoops_IPHHP.g : _hoops_SIPI.g; \
						*_hoops_PAGR++ = BIT (bit, 0x10) ? _hoops_IPHHP.r : _hoops_SIPI.r; \
						*_hoops_PAGR++ = BIT (bit, 0x20) ? _hoops_IPHHP.b : _hoops_SIPI.b; \
						*_hoops_PAGR++ = BIT (bit, 0x20) ? _hoops_IPHHP.g : _hoops_SIPI.g; \
						*_hoops_PAGR++ = BIT (bit, 0x20) ? _hoops_IPHHP.r : _hoops_SIPI.r; \
						*_hoops_PAGR++ = BIT (bit, 0x40) ? _hoops_IPHHP.b : _hoops_SIPI.b; \
						*_hoops_PAGR++ = BIT (bit, 0x40) ? _hoops_IPHHP.g : _hoops_SIPI.g; \
						*_hoops_PAGR++ = BIT (bit, 0x40) ? _hoops_IPHHP.r : _hoops_SIPI.r; \
						*_hoops_PAGR++ = BIT (bit, 0x80) ? _hoops_IPHHP.b : _hoops_SIPI.b; \
						*_hoops_PAGR++ = BIT (bit, 0x80) ? _hoops_IPHHP.g : _hoops_SIPI.g; \
						*_hoops_PAGR++ = BIT (bit, 0x80) ? _hoops_IPHHP.r : _hoops_SIPI.r;)

#				define _hoops_IRRSI \
					_hoops_GHIA (\
						bit = *layer++; \
						if (BIT (bit, 0x01))  *_hoops_PAGR++ = _hoops_IPHHP.b, \
						*_hoops_PAGR++ = _hoops_IPHHP.g, *_hoops_PAGR++ = _hoops_IPHHP.r; \
						if (BIT (bit, 0x02))  *_hoops_PAGR++ = _hoops_IPHHP.b, \
						*_hoops_PAGR++ = _hoops_IPHHP.g, *_hoops_PAGR++ = _hoops_IPHHP.r; \
						if (BIT (bit, 0x04))  *_hoops_PAGR++ = _hoops_IPHHP.b, \
						*_hoops_PAGR++ = _hoops_IPHHP.g, *_hoops_PAGR++ = _hoops_IPHHP.r; \
						if (BIT (bit, 0x08))  *_hoops_PAGR++ = _hoops_IPHHP.b, \
						*_hoops_PAGR++ = _hoops_IPHHP.g, *_hoops_PAGR++ = _hoops_IPHHP.r; \
						if (BIT (bit, 0x10))  *_hoops_PAGR++ = _hoops_IPHHP.b, \
						*_hoops_PAGR++ = _hoops_IPHHP.g, *_hoops_PAGR++ = _hoops_IPHHP.r; \
						if (BIT (bit, 0x20))  *_hoops_PAGR++ = _hoops_IPHHP.b, \
						*_hoops_PAGR++ = _hoops_IPHHP.g, *_hoops_PAGR++ = _hoops_IPHHP.r; \
						if (BIT (bit, 0x40))  *_hoops_PAGR++ = _hoops_IPHHP.b, \
						*_hoops_PAGR++ = _hoops_IPHHP.g, *_hoops_PAGR++ = _hoops_IPHHP.r; \
						if (BIT (bit, 0x80))  *_hoops_PAGR++ = _hoops_IPHHP.b, \
						*_hoops_PAGR++ = _hoops_IPHHP.g, *_hoops_PAGR++ = _hoops_IPHHP.r;)


		if (*_hoops_HIGSI != _hoops_IAASP) {
			/* _hoops_CRRSI _hoops_IH _hoops_HCR _hoops_ASRCI _hoops_IIGR _hoops_HPGCR _hoops_GPRR _hoops_HRGR ... */
			int						_hoops_AAPSR;
			unsigned short			_hoops_SRRSI[5];
			int						_hoops_IRRCI[4];
			unsigned char			*_hoops_GARSI =
							state->_hoops_HPICI;
			LPBITMAPINFOHEADER		_hoops_GGHPR = &state->_hoops_APICI->bmiHeader;
			int						_hoops_RARSI=0;
			BYTE					_hoops_IPHHP;
			BYTE					_hoops_SIPI;
			unsigned char const		*layer;
			BYTE alter				*_hoops_PAGR;
			unsigned char			bit;
			int						plane;

			if (_hoops_PSGSI == 0) {
				/* _hoops_APPAI _hoops_ASRCI _hoops_HSPAA _hoops_ISHP _hoops_PSP _hoops_IGAA _hoops_PAR _hoops_APPS */
				_hoops_PSGSI = 8;
				_hoops_ASGSI = 8;
			}
			_hoops_GCAIR =
				HD_Find_Dither_Pattern (dc->_hoops_SHCIP, _hoops_HIGSI,
										_hoops_SRRSI,
										_hoops_IRRCI);

			if (_hoops_GCAIR == 1) {
				/*
				 * _hoops_HGI _hoops_HRGR _hoops_ICRP _hoops_AARSI - _hoops_SR _hoops_CGH _hoops_HS _hoops_IIP _hoops_PARSI _hoops_IS
				 *	_hoops_ARI _hoops_IH _hoops_IRS _hoops_RPHSR _hoops_HAIR - _hoops_AAPA _hoops_PAPA "_hoops_CAGRH" - _hoops_PPGR
				 *	_hoops_HPP _hoops_RGSR _hoops_RH _hoops_GIAP _hoops_HAIR _hoops_CIHA _hoops_IS _hoops_RH _hoops_PSHR _hoops_HAIR
				 *	_hoops_PPR _hoops_HAGC _hoops_GIPR _hoops_PAIA _hoops_RPHSR
				 */
				_hoops_SRRSI[1] = _hoops_SRRSI[0];
				_hoops_IRRCI[0] = FP_SOLID;
			}

			/*
			 * _hoops_PHAA _hoops_SR _hoops_HS _hoops_IS _hoops_ASH _hoops_RGR _hoops_HPHS _hoops_IH _hoops_SACS
			 * _hoops_HARSI
			 */
		   _hoops_SPHCI->_hoops_RARCI._hoops_GARCI = *_hoops_HIGSI;

			switch (dc->_hoops_PGCC._hoops_PIHSR) {
				case _hoops_RIIHP:
				case _hoops_SIHSR: {
					_hoops_RARSI =  ((_hoops_PSGSI + 3) & (~0x0003));
				}	break;
				case _hoops_HIHSR: {
					_hoops_RARSI = ((_hoops_PSGSI*3 + 3) & (~0x0003));
				}	break;
			}

			if (state->_hoops_PHICI)
				_hoops_AAPSR = state->_hoops_HHICI;
			else
				_hoops_AAPSR = dc->_hoops_PGCC._hoops_AAPSR;


			if (_hoops_RARSI*_hoops_ASGSI > state->_hoops_RHICI) {
				/*
				 * _hoops_PS _hoops_CHH _hoops_SAHR _hoops_IARSI _hoops_HIH _hoops_HRGR _hoops_AHPP _hoops_IS _hoops_PHIS
				 * _hoops_CCA _hoops_HHH _hoops_CIPRH
				 */
				GlobalUnlock (state->_hoops_IPICI);
				GlobalFree (state->_hoops_IPICI);
				state->_hoops_RHICI = _hoops_RARSI*_hoops_ASGSI;
				state->_hoops_SPICI = state->_hoops_PPICI +
						sizeof (BITMAPINFOHEADER) + state->_hoops_RHICI;
				state->_hoops_SPICI += _hoops_IAAA (8, _hoops_AAPSR) * 2;

				state->_hoops_IPICI =
					GlobalAlloc (GMEM_MOVEABLE|GMEM_NODISCARD,
						(DWORD) state->_hoops_SPICI);
				if (state->_hoops_IPICI == NULL) {
					char	_hoops_CARSI[128];

#ifndef _WIN32_WCE
					wsprintf (_hoops_CARSI,
							  "patterned brush requested %d memory",
							  state->_hoops_SPICI);
#endif
					_hoops_HRAIR (HEC_MEMORY, HES_OUT_OF_MEMORY, _hoops_CARSI);
				}
				state->_hoops_CPICI =
					(LPBITMAPINFO) GlobalLock (state->_hoops_IPICI);
				if (state->_hoops_CPICI == NULL) {
					char	_hoops_CARSI[128];
#ifndef _WIN32_WCE
					wsprintf (_hoops_CARSI,
							  "patterned brush requested GlobalLock failed",
							  state->_hoops_SPICI);
#endif
					_hoops_HRAIR (HEC_MEMORY, HES_OUT_OF_MEMORY, _hoops_CARSI);
				}
				COPY_MEMORY (state->_hoops_APICI,
									 state->_hoops_PPICI,
									 state->_hoops_CPICI);
			}

			_hoops_GGHPR = &state->_hoops_CPICI->bmiHeader;

		   _hoops_GARSI =
				(unsigned char *) state->_hoops_CPICI +
				sizeof (BITMAPINFOHEADER) +
				_hoops_IAAA (8, _hoops_AAPSR) * 2;

			state->_hoops_HPICI =  _hoops_GARSI;
			/* _hoops_AGGA _hoops_IGRC _hoops_AA _hoops_SCH ! */

			_hoops_SIPI = (BYTE) _hoops_SRRSI[0];
			_hoops_IPHHP = (BYTE) _hoops_SRRSI[1];

			layer = (unsigned char const *)
				dc->_hoops_GRPH[_hoops_IRRCI[0]];
			_hoops_PAGR = _hoops_GARSI;
			_hoops_ARRSI; _hoops_ARRSI;
			_hoops_ARRSI; _hoops_ARRSI;
			_hoops_ARRSI; _hoops_ARRSI;
			_hoops_ARRSI; _hoops_ARRSI;
			for (plane = 2; plane < _hoops_GCAIR; ++plane) {
				_hoops_IPHHP = (BYTE) _hoops_SRRSI[plane];
				layer = (unsigned char const *)
					dc->_hoops_GRPH[_hoops_IRRCI[plane - 1]];
				_hoops_PAGR = _hoops_GARSI;
				_hoops_PRRSI; _hoops_PRRSI;
				_hoops_PRRSI; _hoops_PRRSI;
				_hoops_PRRSI; _hoops_PRRSI;
				_hoops_PRRSI; _hoops_PRRSI;
			}
			/*
			 * _hoops_RHRPA _hoops_RGR _hoops_PPSR _hoops_SR _hoops_CGH _hoops_HS _hoops_CPS _hoops_GCSS _hoops_SGS _hoops_SR _hoops_RRP _hoops_IS
			 * _hoops_ARPR _hoops_RH _hoops_SARSI _hoops_PSSCI _hoops_IPHCI
			 */

			_hoops_GGHPR->biWidth		= _hoops_PSGSI;
			_hoops_GGHPR->biHeight	= _hoops_ASGSI;
			_hoops_GGHPR->biSizeImage = _hoops_RARSI * _hoops_GGHPR->biHeight;
		}

		switch (_hoops_HRRCI) {
			case _hoops_RIGSI: {
				/* _hoops_ACHSP _hoops_CPSA _hoops_SHH _hoops_IRS _hoops_GPRSI _hoops_IPHCI _hoops_HA */
				if (*_hoops_HIGSI == _hoops_IAASP) {
					_hoops_SPHCI->_hoops_RARCI._hoops_CRRCI = *_hoops_SSGSI;
					_hoops_SPHCI->_hoops_HARCI	=
						CreateSolidBrush (*_hoops_SSGSI);
				}
				else {
						if (state->_hoops_IAHCI &&
							state->_hoops_GPHCI) {
							_hoops_SPHCI->_hoops_HARCI =
								CreateDIBPatternBrushPt (state->_hoops_CPICI,
									DIB_PAL_COLORS);
						}
						else
					{
#ifndef _WIN32_WCE
						_hoops_SPHCI->_hoops_HARCI =
							CreateDIBPatternBrush (state->_hoops_IPICI,
												   DIB_PAL_COLORS);
#endif
					}
				}
			}	break;
			case _hoops_GIGSI: {
				unsigned char			bit;
				BYTE alter				*_hoops_PAGR;
				unsigned char const		*layer;
				unsigned char			*_hoops_GARSI = state->_hoops_HPICI;
				LPBITMAPINFOHEADER		_hoops_GGHPR = &state->_hoops_APICI->bmiHeader;
				int						_hoops_RARSI=0;
				int						_hoops_AAPSR;

				_hoops_SPHCI->_hoops_IRRCI = *_hoops_IRRCI;
				_hoops_SPHCI->_hoops_AARCI = *_hoops_AARCI;
				_hoops_SPHCI->_hoops_RARCI._hoops_GARCI = *_hoops_RARCI;

				/* _hoops_AGGA _hoops_IGRC _hoops_AA _hoops_SCH ! */
				if (state->_hoops_PHICI)
					_hoops_AAPSR = state->_hoops_HHICI;
				else
					_hoops_AAPSR = dc->_hoops_PGCC._hoops_AAPSR;

				switch (dc->_hoops_PGCC._hoops_PIHSR) {
					case _hoops_RIIHP:
					case _hoops_SIHSR: {
						_hoops_RARSI =  8;
					}	break;

					case _hoops_HIHSR: {
						_hoops_RARSI = 24;
					}	_hoops_HHHI;
				}
				_hoops_ASGSI = 8;
				/*
				 * _hoops_SR _hoops_HS _hoops_IS _hoops_RGIC _hoops_AHCA _hoops_RH _hoops_RGHP _hoops_GC _hoops_IS _hoops_ARPR
				 * _hoops_RH _hoops_IPHCI _hoops_IHGS _hoops_RRPAR _hoops_HSAR _hoops_SR _hoops_HS _hoops_AIAH _hoops_PSPP
				 */
				if (_hoops_RARSI*_hoops_ASGSI > state->_hoops_RHICI) {
					/*
					 * _hoops_PS _hoops_CHH _hoops_SAHR _hoops_IARSI _hoops_HIH _hoops_HRGR _hoops_AHPP _hoops_IS _hoops_PHIS
					 * _hoops_CCA _hoops_HHH _hoops_CIPRH
					 */
					GlobalUnlock (state->_hoops_IPICI);
					GlobalFree (state->_hoops_IPICI);
					state->_hoops_RHICI = _hoops_RARSI*_hoops_ASGSI;
					state->_hoops_SPICI = state->_hoops_PPICI +
						sizeof (BITMAPINFOHEADER) + state->_hoops_RHICI;

					switch (dc->_hoops_PGCC._hoops_PIHSR) {
						case _hoops_RIIHP:
						case _hoops_SIHSR: {
							state->_hoops_SPICI += _hoops_IAAA (8, _hoops_AAPSR) * 2;
						}	break;

						case _hoops_HIHSR: {
						}	_hoops_HHHI;
					}

					state->_hoops_IPICI =
						GlobalAlloc (GMEM_MOVEABLE|GMEM_NODISCARD,
							(DWORD) state->_hoops_SPICI);
					if (state->_hoops_IPICI == NULL) {
						char _hoops_CARSI[128];
#ifndef _WIN32_WCE
						wsprintf (_hoops_CARSI,
								  "patterned brush requested %d memory",
								  state->_hoops_SPICI);
#endif
						_hoops_HRAIR (HEC_MEMORY, HES_OUT_OF_MEMORY, _hoops_CARSI);
					}
					state->_hoops_CPICI =
						(LPBITMAPINFO) GlobalLock (state->_hoops_IPICI);
					if (state->_hoops_CPICI == NULL) {
						char _hoops_CARSI[128];
#ifndef _WIN32_WCE
						wsprintf (_hoops_CARSI,
								  "patterned brush requested GlobalLock failed",
								  state->_hoops_SPICI);
#endif
						_hoops_HRAIR (HEC_MEMORY, HES_OUT_OF_MEMORY, _hoops_CARSI);
					}
					COPY_MEMORY (state->_hoops_APICI,
								 state->_hoops_PPICI, state->_hoops_CPICI);
				}

				_hoops_GGHPR = &state->_hoops_CPICI->bmiHeader;

				switch (dc->_hoops_PGCC._hoops_PIHSR) {
					case _hoops_RIIHP:
					case _hoops_SIHSR: {
						BYTE	_hoops_IPHHP;
						BYTE	_hoops_SIPI;

						_hoops_GARSI =
							(unsigned char *) state->_hoops_CPICI +
							sizeof (BITMAPINFOHEADER) +
							_hoops_IAAA (8, _hoops_AAPSR) * 2;
						state->_hoops_HPICI = _hoops_GARSI;

						layer = (unsigned char const *)
							dc->_hoops_GRPH[*_hoops_IRRCI];
						_hoops_PAGR = _hoops_GARSI;

						if (*_hoops_HIGSI == _hoops_IAASP) {
							_hoops_SIPI = (BYTE) _hoops_AARCI->_hoops_PGGCR;
							_hoops_IPHHP = (BYTE) _hoops_RARCI->_hoops_PGGCR;
							_hoops_ARRSI; _hoops_ARRSI;
							_hoops_ARRSI; _hoops_ARRSI;
							_hoops_ARRSI; _hoops_ARRSI;
							_hoops_ARRSI; _hoops_ARRSI;
						}
						else {
							_hoops_IPHHP = (BYTE) _hoops_AARCI->_hoops_PGGCR;
							_hoops_PRRSI; _hoops_PRRSI;
							_hoops_PRRSI; _hoops_PRRSI;
							_hoops_PRRSI; _hoops_PRRSI;
							_hoops_PRRSI; _hoops_PRRSI;
						}
					}	break;
					case _hoops_HIHSR: {
						_hoops_ISC	_hoops_IPHHP;
						_hoops_ISC	_hoops_SIPI;

						_hoops_GARSI =
							(unsigned char *) state->_hoops_CPICI +
							_hoops_GGHPR->biSize;
						state->_hoops_HPICI = _hoops_GARSI;

						_hoops_GGHPR->biBitCount = 24;
						_hoops_GGHPR->biClrUsed = 0;

						layer = (unsigned char const *)
							dc->_hoops_GRPH[*_hoops_IRRCI];
						_hoops_PAGR = _hoops_GARSI;

						_hoops_SIPI = _hoops_AARCI->_hoops_HRIR;
						_hoops_IPHHP = _hoops_RARCI->_hoops_HRIR;
						_hoops_HRRSI; _hoops_HRRSI;
						_hoops_HRRSI; _hoops_HRRSI;
						_hoops_HRRSI; _hoops_HRRSI;
						_hoops_HRRSI; _hoops_HRRSI;
					}	break;
				}

				/*
				 * _hoops_RHRPA _hoops_RGR _hoops_PPSR _hoops_SR _hoops_CGH _hoops_HS _hoops_CPS _hoops_GCSS _hoops_SGS _hoops_SR _hoops_RRP
				 * _hoops_IS _hoops_ARPR _hoops_RH _hoops_SARSI _hoops_PSSCI _hoops_IPHCI
				 */

				_hoops_GGHPR->biWidth		= 8;
				_hoops_GGHPR->biHeight	= 8;
				_hoops_GGHPR->biSizeImage = _hoops_RARSI * _hoops_GGHPR->biHeight;
				if (state->_hoops_IAHCI) {
					_hoops_SPHCI->_hoops_HARCI =
						CreateDIBPatternBrushPt (state->_hoops_CPICI,
							DIB_PAL_COLORS);
				}
				else
				{
#ifndef _WIN32_WCE
					_hoops_SPHCI->_hoops_HARCI =
						CreateDIBPatternBrush (state->_hoops_IPICI,
											   DIB_PAL_COLORS);
#endif
				}
			}	break;

			case _hoops_AIGSI: {
				int					i,
													j;
				unsigned char		*_hoops_GARSI;
				unsigned char		*_hoops_RPRSI,
													*_hoops_APRSI;
				LPBITMAPINFOHEADER	_hoops_GGHPR;
				int					_hoops_RARSI=0;
				int					_hoops_AAPSR;
				/*_hoops_SPRS			_hoops_SCSH					_hoops_PPRSI =
													(_hoops_HPRSI+7)/8;*/

				_hoops_SPHCI->_hoops_IRRCI = *_hoops_IRRCI;
				_hoops_SPHCI->_hoops_AARCI = *_hoops_AARCI;
				_hoops_SPHCI->_hoops_RARCI._hoops_GARCI = *_hoops_RARCI;

				if (state->_hoops_PHICI)
					_hoops_AAPSR = state->_hoops_HHICI;
				else
					_hoops_AAPSR = dc->_hoops_PGCC._hoops_AAPSR;

				switch (dc->_hoops_PGCC._hoops_PIHSR) {
					case _hoops_RIIHP:
					case _hoops_SIHSR: {
						_hoops_RARSI =  ((_hoops_PSGSI + 3) & (~0x0003));
					}	break;

					case _hoops_HIHSR: {
						_hoops_RARSI = ((_hoops_PSGSI*3 + 3) & (~0x0003));
					}	break;
				}
				/*
				 * _hoops_PHAA _hoops_SR _hoops_HS _hoops_IS _hoops_ASH _hoops_RGR _hoops_HPHS _hoops_IH _hoops_SACS
				 * _hoops_HARSI
				 */
				_hoops_SPHCI->_hoops_PARCI =
					_hoops_CPA;

				if (_hoops_RARSI*_hoops_ASGSI > state->_hoops_RHICI) {
					/* _hoops_PS _hoops_CHH _hoops_SAHR _hoops_IARSI _hoops_HIH _hoops_HRGR _hoops_AHPP _hoops_IS _hoops_PHIS
						_hoops_CCA _hoops_HHH _hoops_CIPRH */
					GlobalUnlock (state->_hoops_IPICI);
					GlobalFree (state->_hoops_IPICI);
					state->_hoops_RHICI = _hoops_RARSI*_hoops_ASGSI;
					state->_hoops_SPICI = state->_hoops_PPICI +
						   sizeof (BITMAPINFOHEADER) + state->_hoops_RHICI;

					switch (dc->_hoops_PGCC._hoops_PIHSR) {
						case _hoops_SIHSR: {
							state->_hoops_SPICI +=
								_hoops_IAAA (8, _hoops_AAPSR) * 2;
						}	break;

						case _hoops_HIHSR: {
						}	_hoops_HHHI;
					}

					state->_hoops_IPICI =
						GlobalAlloc (GMEM_MOVEABLE|GMEM_NODISCARD,
							(DWORD) state->_hoops_SPICI);
					if (state->_hoops_IPICI == NULL) {
						char	_hoops_CARSI[128];
#ifndef _WIN32_WCE
						wsprintf (_hoops_CARSI,
								  "patterned brush requested %d memory",
								  state->_hoops_SPICI);
#endif
						_hoops_HRAIR (HEC_MEMORY, HES_OUT_OF_MEMORY, _hoops_CARSI);
					}
					state->_hoops_CPICI =
						(LPBITMAPINFO) GlobalLock (state->_hoops_IPICI);
					if (state->_hoops_CPICI == NULL) {
						char	_hoops_CARSI[128];
#ifndef _WIN32_WCE
						wsprintf (_hoops_CARSI,
								  "patterned brush requested GlobalLock failed",
								  state->_hoops_SPICI);
#endif
						_hoops_HRAIR (HEC_MEMORY, HES_OUT_OF_MEMORY, _hoops_CARSI);
					}
					COPY_MEMORY (state->_hoops_APICI,
										 state->_hoops_PPICI,
										 state->_hoops_CPICI);
				}

				_hoops_GGHPR = &state->_hoops_CPICI->bmiHeader;

				switch (dc->_hoops_PGCC._hoops_PIHSR) {
					case _hoops_RIIHP:
					case _hoops_SIHSR: {
						_hoops_GARSI =
							(unsigned char *) state->_hoops_CPICI +
							sizeof (BITMAPINFOHEADER) +
							_hoops_IAAA (8, _hoops_AAPSR) * 2;
						state->_hoops_HPICI = _hoops_GARSI;
						if (!direction) {
							_hoops_RPRSI = _hoops_GARSI;
							for (i = 0; i < _hoops_ASGSI; i++) {
								_hoops_APRSI = _hoops_RPRSI;
								for (j = 0; j < _hoops_PSGSI; j++) {
									if (*_hoops_HIGSI == _hoops_IAASP) {
										(*_hoops_APRSI++) = (*_hoops_PGPH++)?
											(unsigned char)_hoops_RARCI->_hoops_PGGCR:
											(unsigned char)_hoops_AARCI->_hoops_PGGCR;
									}
									else {
										if (!*_hoops_PGPH++) {
											*_hoops_APRSI = (unsigned char)
												_hoops_AARCI->_hoops_PGGCR;
										}
										_hoops_APRSI++;
									}
								}
								_hoops_RPRSI+=_hoops_RARSI;
							}
						}
						else {
							_hoops_RPRSI = _hoops_GARSI +
								(_hoops_ASGSI - 1) * _hoops_RARSI;
							for (i = 0; i < _hoops_ASGSI; i++) {
								_hoops_APRSI = _hoops_RPRSI;
								for (j = 0; j < _hoops_PSGSI; j++) {
									if (*_hoops_HIGSI == _hoops_IAASP) {
										(*_hoops_APRSI++) = (*_hoops_PGPH++)?
											(unsigned char)
											_hoops_RARCI->_hoops_PGGCR:
											(unsigned char)
											_hoops_AARCI->_hoops_PGGCR;
									}
									else {
										if (!*_hoops_PGPH++) {
											*_hoops_APRSI = (unsigned char)
												_hoops_AARCI->_hoops_PGGCR;
										}
										_hoops_APRSI++;
									}
								}
								_hoops_RPRSI -= _hoops_RARSI;
							}
						}
					}	break;
					case _hoops_HIHSR: {
						_hoops_ISC	_hoops_IPHHP;
						_hoops_ISC	_hoops_SIPI;
						_hoops_GARSI =
							(unsigned char *) state->_hoops_CPICI +
							_hoops_GGHPR->biSize;
						state->_hoops_HPICI = _hoops_GARSI;
						_hoops_GGHPR->biBitCount = 24;
						_hoops_GGHPR->biClrUsed = 0;
						_hoops_SIPI = _hoops_AARCI->_hoops_HRIR;
						_hoops_IPHHP = _hoops_RARCI->_hoops_HRIR;
						if (!direction) {
							_hoops_RPRSI = _hoops_GARSI;
							for (i = 0; i < _hoops_ASGSI; i++) {
								_hoops_APRSI = _hoops_RPRSI;
								for (j = 0; j < _hoops_PSGSI; j++) {
									(*_hoops_APRSI++) = (*_hoops_PGPH)?
										_hoops_IPHHP.b:
										_hoops_SIPI.b;
									(*_hoops_APRSI++) = (*_hoops_PGPH)?
										_hoops_IPHHP.g:
										_hoops_SIPI.g;
									(*_hoops_APRSI++) = (*_hoops_PGPH++)?
										_hoops_IPHHP.r:
										_hoops_SIPI.r;
								}
								_hoops_RPRSI+=_hoops_RARSI;
							}
						}
						else {
							_hoops_RPRSI = _hoops_GARSI +
								(_hoops_ASGSI - 1) * _hoops_RARSI;
							for (i = 0; i < _hoops_ASGSI; i++) {
								_hoops_APRSI = _hoops_RPRSI;
								for (j = 0; j < _hoops_PSGSI; j++) {
									(*_hoops_APRSI++) = (*_hoops_PGPH)?
										_hoops_IPHHP.b:
										_hoops_SIPI.b;
									(*_hoops_APRSI++) = (*_hoops_PGPH)?
										_hoops_IPHHP.g:
										_hoops_SIPI.g;
									(*_hoops_APRSI++) = (*_hoops_PGPH++)?
										_hoops_IPHHP.r:
										_hoops_SIPI.r;
								}
								_hoops_RPRSI -= _hoops_RARSI;
							}
						}
					}	break;
				}

				/*
				 * _hoops_RHRPA _hoops_RGR _hoops_PPSR _hoops_SR _hoops_HS _hoops_CPS _hoops_GCSS _hoops_SGS _hoops_SR _hoops_RRP _hoops_IS
				 * _hoops_ARPR _hoops_RH _hoops_SARSI _hoops_PSSCI _hoops_IPHCI
				 */

				_hoops_GGHPR->biWidth		= _hoops_PSGSI;
				_hoops_GGHPR->biHeight	= _hoops_ASGSI;
				_hoops_GGHPR->biSizeImage = _hoops_RARSI * _hoops_GGHPR->biHeight;


				if (state->_hoops_IAHCI) {
					_hoops_SPHCI->_hoops_HARCI =
						CreateDIBPatternBrushPt (state->_hoops_CPICI,
							DIB_PAL_COLORS);
				}
				else
				{
#ifndef _WIN32_WCE
					_hoops_SPHCI->_hoops_HARCI =
						CreateDIBPatternBrush (state->_hoops_IPICI,
											   DIB_PAL_COLORS);
#endif
				}
			}	break;
		}
	}

	_hoops_ISGSI = _hoops_SPHCI->_hoops_AGRCI;

	_hoops_RGGA (_hoops_ISGSI == NULL || _hoops_ISGSI->dc == dc)
		_hoops_ISGSI = _hoops_ISGSI->_hoops_AGRCI;

	if ((_hoops_ISGSI == NULL) && (_hoops_SPHCI->_hoops_AGRCI == NULL)) {
		ALLOC (_hoops_ISGSI, _hoops_RRRCI);
		_hoops_ISGSI->_hoops_AGRCI = NULL;
		_hoops_ISGSI->dc = dc;
		_hoops_SPHCI->_hoops_AGRCI = _hoops_ISGSI;
	}

	/* _hoops_PS _hoops_HHGC _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_ASRCI _hoops_IS _hoops_SHH _hoops_GGR _hoops_RGGGH _hoops_AGR _hoops_HIS _hoops_SR _hoops_HA _hoops_IHIS _hoops_RGR
		_hoops_IPHCI _hoops_RARP _hoops_IS _hoops_RH _hoops_SCIA _hoops_IIGR _hoops_RH _hoops_HIGR */
	if (state->_hoops_SPHCI->_hoops_PRRCI != _hoops_SPHCI) {
		_hoops_HSGSI->_hoops_PRRCI = _hoops_SPHCI->_hoops_PRRCI;
		_hoops_SPHCI->_hoops_PRRCI = state->_hoops_SPHCI->_hoops_PRRCI;
		state->_hoops_SPHCI->_hoops_PRRCI = _hoops_SPHCI;
	}


	return _hoops_SPHCI->_hoops_HARCI;
#else
	return 0;
#endif
}



/*
 * _hoops_PGAA
 */
local void _hoops_IPRSI (
	Display_Context const	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_SGH _hoops_IRS _hoops_HCGSI _hoops_CSGSR */
	if (IsWindow (state->_hoops_GGICI))
		SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);
	/* _hoops_PS _hoops_ICGSI _hoops_PPPPR'_hoops_RA _hoops_AA _hoops_RGR _hoops_AAGAI */
	_hoops_SHGSI (state);
}


/*
 * _hoops_PGAA
 */
local void _hoops_PSICI (
	MSW_Driver_State alter	*state,
	_hoops_PGRCI alter		*_hoops_CPHCI,
	_hoops_PGRCI alter		*_hoops_CPRSI) {

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_SGH _hoops_IRS _hoops_HCGSI _hoops_CSGSR */
	SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);

	DeleteObject (_hoops_CPHCI->_hoops_GRRCI);

	_hoops_CPHCI->line_style = null;

	_hoops_CPRSI->_hoops_HGRCI = _hoops_CPHCI->_hoops_HGRCI;
	FREE (_hoops_CPHCI, _hoops_PGRCI);
	/* _hoops_PS _hoops_ICGSI _hoops_PPPPR'_hoops_RA _hoops_AA _hoops_RGR _hoops_AAGAI */
	_hoops_SHGSI (state);
}


/*
* _hoops_PGAA
*/
local HPEN _hoops_SPRSI (
	MSW_Driver_State alter		*state,
	DWORD					_hoops_IGRCI,
	DWORD					_hoops_CGRCI,
	DWORD					_hoops_SGRCI,
	Line_Style const &		line_style) {
	_hoops_PGRCI alter			*_hoops_CPHCI;
	_hoops_PGRCI alter			*_hoops_GHRSI;
	_hoops_RGRCI alter			*_hoops_ISGSI;
	int						_hoops_RHRSI;
	Display_Context alter  *dc =
								(Display_Context alter *) state->dc;

	_hoops_GHRSI = _hoops_CPHCI = state->_hoops_CPHCI;
	_hoops_RHRSI = false;

	while (_hoops_CPHCI->_hoops_HGRCI != NULL) {
		_hoops_GHRSI = _hoops_CPHCI;
		_hoops_CPHCI = _hoops_CPHCI->_hoops_HGRCI;
		if (_hoops_IGRCI == _hoops_CPHCI->_hoops_IGRCI) {
#ifndef _WIN32_WCE
			switch (_hoops_IGRCI & PS_STYLE_MASK) {
#else
			switch (_hoops_IGRCI) {
#endif
				case PS_SOLID: {
					if (_hoops_CGRCI == _hoops_CPHCI->_hoops_CGRCI &&
						_hoops_SGRCI == _hoops_CPHCI->_hoops_SGRCI) {
						_hoops_RHRSI = true;
					}
				}	break;

				default: {
					/* _hoops_PPRII _hoops_SHH _hoops_IRS _hoops_ICIGP _hoops_IPHCI */
					if (_hoops_IGRCI == _hoops_CPHCI->_hoops_IGRCI &&
						_hoops_CGRCI == _hoops_CPHCI->_hoops_CGRCI &&
						_hoops_SGRCI == _hoops_CPHCI->_hoops_SGRCI &&
						line_style == _hoops_CPHCI->line_style) {
						_hoops_RHRSI = true;
					}
				}	break;
			}
		}
		if (_hoops_RHRSI) {
			/*
			 * _hoops_PS _hoops_AIAH _hoops_HS _hoops_SPR - _hoops_GGCR _hoops_RGR _hoops_IPSP _hoops_IS _hoops_RH _hoops_HIGR
			 * _hoops_IIGR _hoops_CSGSR _hoops_SSHSR _hoops_PPR _hoops_GPISR _hoops_RH _hoops_RPR _hoops_IIGR _hoops_SSHSR
			 */
			break;
		}
	}

	if (!_hoops_RHRSI) {
		/* _hoops_IASHR ... _hoops_SR _hoops_IRPSR'_hoops_RA _hoops_SSS _hoops_IRS _hoops_PSSP */
		if (*state->_hoops_HHHCI == *state->_hoops_RHHCI) {
			/*
			 * _hoops_PS _hoops_HS _hoops_IS _hoops_RHGPA _hoops_SPR - _hoops_SHR _hoops_SGH _hoops_RH _hoops_HGRSI _hoops_SPR _hoops_GGR _hoops_RH _hoops_HIGR
			 * _hoops_CR _hoops_SR _hoops_RHHSR _hoops_SCH _hoops_GGR _hoops_IGRSI _hoops_AGR
			 */

			/* _hoops_AGGA _hoops_AASA _hoops_HCR _hoops_IIGR _hoops_RH _hoops_SSHSR _hoops_PPR _hoops_CRGS _hoops_PSCR _hoops_IS _hoops_CIH _hoops_RH _hoops_CSGSR */
			_hoops_ISGSI = _hoops_CPHCI->_hoops_AGRCI;
			while (_hoops_ISGSI != NULL) {
				_hoops_RGRCI alter *_hoops_CGRSI;

				_hoops_IPRSI (_hoops_ISGSI->dc);
				_hoops_CGRSI = _hoops_ISGSI;
				_hoops_ISGSI = _hoops_ISGSI->_hoops_AGRCI;
				FREE (_hoops_CGRSI, _hoops_RGRCI);
			}

			_hoops_CPHCI->line_style = null;

			/* _hoops_CPGP _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_RPRS _hoops_RGR _hoops_RARP _hoops_SAHR _hoops_CPCS _hoops_SCH */
			DeleteObject (_hoops_CPHCI->_hoops_GRRCI);
		}
		else {
			/* _hoops_CICR _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SPR */
			ZALLOC (_hoops_CPHCI, _hoops_PGRCI);
			_hoops_CPHCI->_hoops_HGRCI = state->_hoops_CPHCI->_hoops_HGRCI;
			state->_hoops_CPHCI->_hoops_HGRCI = _hoops_CPHCI;
			(*state->_hoops_HHHCI)++;
		}

		/*
		 * _hoops_HGI _hoops_RRGR _hoops_HRGR _hoops_HGGC _hoops_ARI _hoops_IH _hoops_PGCR _hoops_SCPC - _hoops_SPR _hoops_HRGR _hoops_IH _hoops_GII _hoops_GHARR
		 * _hoops_SGS _hoops_ASSP'_hoops_RA _hoops_GCGH _hoops_AHRSI _hoops_HIH _hoops_SCGAH _hoops_PGGA _hoops_RGR
		 * _hoops_GPRR _hoops_IIGR _hoops_CSGSR _hoops_HRGR _hoops_SPAC
		 */
#ifdef _WIN32_WCE
		if (((_hoops_IGRCI) == PS_SOLID) && _hoops_CGRCI == 1) {
			 _hoops_CPHCI->_hoops_GRRCI = CreatePen (PS_SOLID, (int)_hoops_CGRCI, _hoops_SGRCI);
		}
#else
		if (((_hoops_IGRCI & PS_STYLE_MASK) == PS_SOLID) && _hoops_CGRCI == 1) {
			/* _hoops_RPHSR _hoops_PPR _hoops_IGAA==1 */
			_hoops_CPHCI->_hoops_GRRCI = CreatePen (PS_SOLID, (int)_hoops_CGRCI, _hoops_SGRCI);
		}
		else {
			LOGBRUSH		_hoops_PHRSI;

			memset(&_hoops_PHRSI,0,sizeof(LOGBRUSH));

			_hoops_PHRSI.lbStyle = BS_SOLID;
			_hoops_PHRSI.lbColor = _hoops_SGRCI;

			if ((_hoops_IGRCI & PS_STYLE_MASK) == PS_SOLID) {
				/* _hoops_RPHSR, _hoops_HIH _hoops_IGAA!=1 */

				_hoops_CPHCI->_hoops_GRRCI = ExtCreatePen (_hoops_IGRCI, _hoops_CGRCI,
													  &_hoops_PHRSI, 0, NULL);
			}
			else {

				int i, npat;
				DWORD* _hoops_HHRSI;
				int * pattern;
				float _hoops_ICPGH;

				if (BIT(line_style->_hoops_GHISR[0].flags, LSF_ABSOLUTE_LENGTH))
					_hoops_ICPGH = 1.0f;
				else
					_hoops_ICPGH = dc->_hoops_PGCC._hoops_ICPGH;

				pattern = line_style->_hoops_GHISR[0].pattern;
				npat = line_style->_hoops_GHISR[0]._hoops_RHISR;

				ALLOC_ARRAY(_hoops_HHRSI,npat, DWORD);
				for (i = 0; i < npat; i++)
					_hoops_HHRSI[i] = pattern[i] * _hoops_ICPGH;

				_hoops_CPHCI->_hoops_GRRCI = ExtCreatePen (_hoops_IGRCI,  _hoops_CGRCI, &_hoops_PHRSI, npat, _hoops_HHRSI);
				FREE_ARRAY(_hoops_HHRSI,npat, DWORD);
			}
		}
#endif
		_hoops_CPHCI->_hoops_IGRCI	= _hoops_IGRCI;
		_hoops_CPHCI->_hoops_CGRCI	= _hoops_CGRCI;
		_hoops_CPHCI->_hoops_SGRCI = _hoops_SGRCI;
		_hoops_CPHCI->line_style	= line_style;
		_hoops_CPHCI->_hoops_AGRCI	= NULL;
	}

	_hoops_ISGSI = _hoops_CPHCI->_hoops_AGRCI;

	_hoops_RGGA (_hoops_ISGSI == NULL || _hoops_ISGSI->dc == dc)
		_hoops_ISGSI = _hoops_ISGSI->_hoops_AGRCI;

	if ((_hoops_ISGSI == NULL) && (_hoops_CPHCI->_hoops_AGRCI == NULL)) {
		ALLOC (_hoops_ISGSI, _hoops_RGRCI);
		_hoops_ISGSI->_hoops_AGRCI = NULL;
		_hoops_ISGSI->dc = dc;
		_hoops_CPHCI->_hoops_AGRCI = _hoops_ISGSI;
	}

	/*
	 * _hoops_PS _hoops_HHGC _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_CISRI _hoops_IS _hoops_SHH _hoops_GGR _hoops_RGGGH _hoops_AGR _hoops_HIS _hoops_SR _hoops_HA _hoops_IHIS _hoops_RGR
	 * _hoops_CSGSR _hoops_RARP _hoops_IS _hoops_RH _hoops_SCIA _hoops_IIGR _hoops_RH _hoops_HIGR
	 */
	if (state->_hoops_CPHCI->_hoops_HGRCI != _hoops_CPHCI) {
		_hoops_GHRSI->_hoops_HGRCI = _hoops_CPHCI->_hoops_HGRCI;
		_hoops_CPHCI->_hoops_HGRCI = state->_hoops_CPHCI->_hoops_HGRCI;
		state->_hoops_CPHCI->_hoops_HGRCI = _hoops_CPHCI;
	}


	return _hoops_CPHCI->_hoops_GRRCI;
}


/*
 * _hoops_PGAA
 */
local void _hoops_IHRSI (
	Display_Context const	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();

	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_SGH _hoops_IRS _hoops_HCGSI _hoops_HRCSR */

	if (IsWindow (state->_hoops_GGICI)) {
		if (state->_hoops_AGICI == null) {
			HDC hDC = GetDC(state->_hoops_GGICI);
			SelectObject (hDC, state->_hoops_CPCCI);
			ReleaseDC(state->_hoops_GGICI, hDC);
		}
		else
			SelectObject (state->_hoops_AGICI, state->_hoops_CPCCI);
	}
	/* _hoops_PS _hoops_ICGSI _hoops_PPPPR'_hoops_RA _hoops_AA _hoops_RGR _hoops_AAGAI */
	_hoops_SHGSI (state);
}


/*
 * _hoops_PGAA
 */
local void _hoops_CHRSI (
	MSW_Driver_State alter	*state,
	_hoops_HPRCI alter	*_hoops_GHHCI,
	_hoops_HPRCI alter	*_hoops_SHRSI) {


	/* _hoops_PS _hoops_RRP _hoops_IS _hoops_SGH _hoops_IRS _hoops_HCGSI _hoops_HRCSR */
	SelectObject (state->_hoops_AGICI, state->_hoops_CPCCI);

	DeleteObject (_hoops_GHHCI->_hoops_CPRCI);
	_hoops_SHRSI->_hoops_IPRCI = _hoops_GHHCI->_hoops_IPRCI;
	FREE (_hoops_GHHCI, _hoops_HPRCI);
	/* _hoops_PS _hoops_ICGSI _hoops_PPPPR'_hoops_RA _hoops_AA _hoops_RGR _hoops_AAGAI */
	_hoops_SHGSI (state);
}


/*
 * _hoops_PGAA
 */


local HFONT _hoops_HHCCI (
	Display_Context const *dc,
	_hoops_HPRCI alter	*_hoops_IHCCI,
	int					*_hoops_CHHCI,
	int					*_hoops_PHHCI,
	LOGFONT const		*_hoops_CHCCI,
	long				_hoops_SHCCI,
	long				_hoops_GICCI,
	float				width_scale,
	float				_hoops_PRPHA) {
#ifndef _WIN32_WCE
	_hoops_HPRCI alter			*_hoops_GHHCI;
	_hoops_HPRCI alter			*_hoops_GIRSI;
	_hoops_PPRCI alter				*_hoops_ISGSI;
	int							_hoops_RIRSI;
	LOGFONT						_hoops_AIRSI;
	HFONT						_hoops_PIRSI;

	_hoops_GIRSI = _hoops_GHHCI = _hoops_IHCCI;
	_hoops_RIRSI = false;

	while (_hoops_GHHCI->_hoops_IPRCI != NULL) {
		_hoops_GIRSI = _hoops_GHHCI;
		_hoops_GHHCI = _hoops_GHHCI->_hoops_IPRCI;

		if (	(_hoops_CHCCI->lfWeight == _hoops_GHHCI->_hoops_GPRCI->lfWeight)	&&
				(_hoops_CHCCI->lfItalic == _hoops_GHHCI->_hoops_GPRCI->lfItalic)	&&
				(_hoops_CHCCI->lfUnderline == _hoops_GHHCI->_hoops_GPRCI->lfUnderline)  &&
				(_hoops_CHCCI->lfStrikeOut == _hoops_GHHCI->_hoops_GPRCI->lfStrikeOut)  &&
				(_hoops_CHCCI->lfCharSet == _hoops_GHHCI->_hoops_GPRCI->lfCharSet)  &&
				(_hoops_CHCCI->lfOutPrecision == _hoops_GHHCI->_hoops_GPRCI->lfOutPrecision)	&&
				(_hoops_CHCCI->lfClipPrecision == _hoops_GHHCI->_hoops_GPRCI->lfClipPrecision)  &&
				(_hoops_CHCCI->lfQuality == _hoops_GHHCI->_hoops_GPRCI->lfQuality)  &&
				(_hoops_CHCCI->lfPitchAndFamily == _hoops_GHHCI->_hoops_GPRCI->lfPitchAndFamily)	&&
				(!strcmp(_hoops_CHCCI->lfFaceName, _hoops_GHHCI->_hoops_GPRCI->lfFaceName))  &&
				(_hoops_SHCCI == _hoops_GHHCI->_hoops_CIRHH) &&
				(_hoops_GICCI == _hoops_GHHCI->_hoops_SPRCI) &&
				(width_scale == _hoops_GHHCI->width_scale)) {
			_hoops_RIRSI = true;
			break;
		}
	}

	if (!_hoops_RIRSI) {
		/* _hoops_IASHR ... _hoops_SR _hoops_IRPSR'_hoops_RA _hoops_SSS _hoops_IRS _hoops_PSSP */
		if (*_hoops_CHHCI == *_hoops_PHHCI) {
			/*
			 * _hoops_PS _hoops_HS _hoops_IS _hoops_RHGPA _hoops_SPR - _hoops_SHR _hoops_SGH _hoops_RH _hoops_HGRSI _hoops_SPR _hoops_GGR _hoops_RH _hoops_HIGR
			 * _hoops_CR _hoops_SR _hoops_RHHSR _hoops_SCH _hoops_GGR _hoops_IGRSI _hoops_AGR
			 */

			/* _hoops_AGGA _hoops_AASA _hoops_HCR _hoops_IIGR _hoops_RH _hoops_SSHSR _hoops_PPR _hoops_CRGS _hoops_PSCR _hoops_IS _hoops_CIH _hoops_RH _hoops_HRCSR */
			_hoops_ISGSI = _hoops_GHHCI->_hoops_AGRCI;
			while (_hoops_ISGSI != NULL) {
				_hoops_PPRCI alter *_hoops_CGRSI;

				_hoops_IHRSI (_hoops_ISGSI->dc);
				_hoops_CGRSI = _hoops_ISGSI;
				_hoops_ISGSI = _hoops_ISGSI->_hoops_AGRCI;
				FREE (_hoops_CGRSI, _hoops_PPRCI);
			}
			/* _hoops_CPGP _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_RPRS _hoops_RGR _hoops_RARP _hoops_SAHR _hoops_CPCS _hoops_SCH */
			DeleteObject (_hoops_GHHCI->_hoops_CPRCI);
		}
		else {
			/* _hoops_CICR _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SPR */
			ALLOC (_hoops_GHHCI, _hoops_HPRCI);
			_hoops_GHHCI->_hoops_IPRCI = _hoops_IHCCI->_hoops_IPRCI;
			_hoops_IHCCI->_hoops_IPRCI = _hoops_GHHCI;
			(*_hoops_CHHCI)++;
		}


		/* _hoops_SIGP: _hoops_GISA _hoops_HRCSR _hoops_RGHH _hoops_ARI */
		_hoops_RSAI (_hoops_CHCCI, LOGFONT, &_hoops_AIRSI);

		_hoops_AIRSI.lfOrientation = _hoops_AIRSI.lfEscapement = _hoops_GICCI;
		_hoops_AIRSI.lfHeight = -_hoops_SHCCI;

		if (width_scale == 1.0f) {
			_hoops_AIRSI.lfWidth = 0;
		}
		else {
			_hoops_AIRSI.lfWidth	= (long)((_hoops_SHCCI * width_scale * _hoops_PRPHA)+0.5f);
		}

		/*
		 * _hoops_HIHP _hoops_IS _hoops_HIRSI _hoops_CPHH (_hoops_SPHGR _hoops_SSPII)
		 * _hoops_HGI _hoops_HRGR _hoops_AP _hoops_ARPP _hoops_PPR _hoops_IIRSI _hoops_CR _hoops_SPR _hoops_IIAH _hoops_GPP _hoops_HPPCI _hoops_PPR
		 * _hoops_RH _hoops_RII _hoops_IIAH _hoops_GPP _hoops_CIRSI _hoops_SIRSI
		 * _hoops_RAH _hoops_ASAI _hoops_GCRSI _hoops_RCRSI _hoops_HCCHA
		 */

		_hoops_PIRSI = CreateFontIndirect(&_hoops_AIRSI);

		if (_hoops_PIRSI == NULL) {
			HE_ERROR (HEC_MSW_DRIVER, HES_WINDOWS_FONT, "Couldn't request Windows font");
			/*_hoops_PIAP->_hoops_IHAH._hoops_ACRSI = _hoops_PCRSI;*/
		}

		_hoops_GHHCI->_hoops_CIRHH			= _hoops_SHCCI;
		_hoops_GHHCI->_hoops_CPRCI			= _hoops_PIRSI;
		_hoops_GHHCI->_hoops_GPRCI			= _hoops_CHCCI;
		_hoops_GHHCI->_hoops_SPRCI		= _hoops_GICCI;
		_hoops_GHHCI->width_scale			= width_scale;
		_hoops_GHHCI->_hoops_AGRCI			= NULL;
	}

	_hoops_ISGSI = _hoops_GHHCI->_hoops_AGRCI;

	_hoops_RGGA (_hoops_ISGSI == NULL || _hoops_ISGSI->dc == dc)
		_hoops_ISGSI = _hoops_ISGSI->_hoops_AGRCI;

	if ((_hoops_ISGSI == NULL) && (_hoops_GHHCI->_hoops_AGRCI == NULL)) {
		ALLOC (_hoops_ISGSI, _hoops_PPRCI);
		_hoops_ISGSI->_hoops_AGRCI = NULL;
		_hoops_ISGSI->dc = dc;
		_hoops_GHHCI->_hoops_AGRCI = _hoops_ISGSI;
	}

	/*
	 * _hoops_PS _hoops_HHGC _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_GSPIP _hoops_IS _hoops_SHH _hoops_GGR _hoops_RGGGH _hoops_AGR _hoops_HIS _hoops_SR _hoops_HA _hoops_IHIS _hoops_RGR
	 * _hoops_HRCSR _hoops_RARP _hoops_IS _hoops_RH _hoops_SCIA _hoops_IIGR _hoops_RH _hoops_HIGR
	 */
	if (_hoops_IHCCI->_hoops_IPRCI != _hoops_GHHCI) {
		_hoops_GIRSI->_hoops_IPRCI = _hoops_GHHCI->_hoops_IPRCI;
		_hoops_GHHCI->_hoops_IPRCI = _hoops_IHCCI->_hoops_IPRCI;
		_hoops_IHCCI->_hoops_IPRCI = _hoops_GHHCI;
	}

	return _hoops_GHHCI->_hoops_CPRCI;
#else
	HE_ERROR (HEC_MSW_DRIVER, HES_WINDOWS_FONT, "Couldn't request Windows font");
	return NULL;
#endif /* _hoops_HCRSI */
}


/*
 * _hoops_PGAA
 */
local void _hoops_ICRSI (
	MSW_Driver_State alter			*state) {
	HRGN						_hoops_CCRSI;
	Display_Context const	*dc = state->dc;


	if (state->_hoops_PIGRR == _hoops_PSPCI)
		return;

   /*
   _hoops_CHSR _hoops_RPGGI _hoops_ASSP'_hoops_RA _hoops_IPHR _hoops_GGR _hoops_SPHGR _hoops_SCRSI _hoops_GSRSI _hoops_PGI	 ....

   _hoops_HGASR: _hoops_RSRSI _hoops_AISS _hoops_SRPR _hoops_HRHI _hoops_ASRSI _hoops_GPP _hoops_RPPCI
		_hoops_PSRSI _hoops_RCC _hoops_SPCAR: _hoops_HSRSI
		_hoops_ISRSI _hoops_CGHI _hoops_SRSS _hoops_GPP 10-19-1993
		_hoops_CSRSI
		========
		_hoops_GPGP _hoops_IRS _hoops_PSCSR 3.1 _hoops_ISHHH _hoops_CCRPR, _hoops_RCPH _hoops_RSRSI _hoops_CCA _hoops_RH
		_hoops_GIAP _hoops_RHPC _hoops_ARP _hoops_IS _hoops_IHHAH _hoops_IS _hoops_HIAP _hoops_RH _hoops_CIHH _hoops_ISPH _hoops_IS _hoops_HSPH
		_hoops_IIPR _hoops_IS _hoops_RH _hoops_GRGAI _hoops_HSHIA _hoops_RHAP _hoops_HAR _hoops_HIAP _hoops_RH _hoops_CIHH _hoops_ISPH.
		_hoops_SSRSI _hoops_GPP _hoops_RH _hoops_GRGAI _hoops_SISS _hoops_GGSC _hoops_HRGR _hoops_HGGC _hoops_ARP _hoops_IS _hoops_RH _hoops_CIHH
		_hoops_ISPH _hoops_CHIA _hoops_GGR _hoops_RH _hoops_PGHC _hoops_AASA _hoops_IS _hoops_RSRSI.

		_hoops_GGASI
		=====
		_hoops_IPCP _hoops_CSAAI _hoops_IPSCI _hoops_CCPII _hoops_PPR _hoops_CSAAI _hoops_IPSCI _hoops_GRISH _hoops_GRGAI _hoops_SPSIR _hoops_AA _hoops_HAR _hoops_RGHH
		_hoops_RH _hoops_AASA _hoops_IS _hoops_RSRSI _hoops_PRRP _hoops_CGPR _hoops_RH _hoops_RGASI _hoops_RHPC _hoops_HRGR _hoops_ARP _hoops_IS
		_hoops_IHHAH. _hoops_RPGAI _hoops_IIGR _hoops_RGSR _hoops_RH _hoops_CIHH _hoops_ISPH _hoops_IS _hoops_SHH _hoops_RH _hoops_RSIR
		_hoops_GPAAI _hoops_HSHIA (_hoops_GAR _hoops_SCH _hoops_CGH), _hoops_RH _hoops_AASA _hoops_SSCP _hoops_PSP _hoops_GIRRR _hoops_PPR _hoops_RH _hoops_PGHC
		_hoops_CIHH _hoops_ISPH _hoops_HRGR _hoops_HGGC _hoops_RH _hoops_SISS _hoops_GGSC'_hoops_GRI _hoops_CIHH _hoops_ISPH.

		_hoops_AGASI
		==========
		_hoops_RPGAI _hoops_IIGR _hoops_HIRAA _hoops_IHHAH _hoops_GAR _hoops_RH _hoops_RGASI _hoops_RHPC _hoops_IS _hoops_RSRSI, _hoops_ARPR
		_hoops_IRS _hoops_ISPH _hoops_IIGR _hoops_RH _hoops_GPAAI _hoops_CCAC _hoops_IIGR _hoops_RH _hoops_HSHIA _hoops_PPR _hoops_HSPAA _hoops_SGS _hoops_ISPH _hoops_GAR _hoops_RH
		_hoops_RGASI _hoops_RHPC. _hoops_HGI _hoops_GRS _hoops_RCRP _hoops_RH _hoops_PIASR _hoops_GIRRR _hoops_IIGR _hoops_RCPH
		_hoops_RSRSI (_hoops_PGASI, _hoops_IHHAH). _hoops_IPCP _hoops_HSPR _hoops_HRGR _hoops_PCCP _hoops_PCAI _hoops_IIGR _hoops_RSH _hoops_RGR
		_hoops_HGASI _hoops_HHS _hoops_SHH _hoops_HGPS:

   */

	_hoops_CCRSI = CreateRectRgn (0, 0, dc->_hoops_PGCC._hoops_PRPSR.x,
						 dc->_hoops_PGCC._hoops_PRPSR.y);
	SelectClipRgn (state->_hoops_AGICI, _hoops_CCRSI);
	if (state->_hoops_SRRRR)
		SelectClipRgn (state->_hoops_IGICI, _hoops_CCRSI);
	DeleteObject (_hoops_CCRSI);
	state->_hoops_CSC._hoops_GCICI = _hoops_CCC;
}



/*
 * _hoops_PGAA
 */
local void _hoops_IGASI (
	MSW_Driver_State alter *		state,
	_hoops_HHCR const &		_hoops_IHCR) {
	POINT							_hoops_PSRSR;
	float							_hoops_PIIH = 1.0f;
	float							_hoops_HIIH = 1.0f;
	int								xoffset = 0;
	int								yoffset = 0;

#ifndef _WIN32_WCE

	if (state->_hoops_PIGRR == _hoops_PSPCI &&
		!state->_hoops_GPHCI)
		return;

	/*
	 * _hoops_HSRR _hoops_SIRSI _hoops_SGS _hoops_GCGH _hoops_HCISR _hoops_HPGR _hoops_IRS _hoops_GSSC _hoops_RAAA
	 * _hoops_HSAR _hoops_HCGR, _hoops_SR _hoops_RRP _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_RH _hoops_CSRA _hoops_AAACA _hoops_IH
	 * _hoops_RH _hoops_SPCR _hoops_PPR _hoops_GHCR _hoops_SSGAR.
	 * _hoops_GIGHR: _hoops_RGR _hoops_PGPCR _hoops_AASA _hoops_HRGR _hoops_HAR _hoops_AGSI _hoops_HPP _hoops_RH
	 *		 _hoops_PPACI _hoops_RIP
	 */
	if ((state->_hoops_PIGRR == _hoops_GSPCI ||
		 state->_hoops_PIGRR == _hoops_ASPCI) &&
		(Escape (state->_hoops_PGICI, GETSCALINGFACTOR, 0, NULL, (LPSTR)&_hoops_PSRSR) > 0 ||
		state->_hoops_GAICI)) {
		float			_hoops_CGASI		= 1.0f;
		float			_hoops_SGASI		= 1.0f;

		/* _hoops_SSCR _hoops_GGSR _hoops_RH _hoops_AGSRH _hoops_CSRA _hoops_AAACA (_hoops_IAARR _hoops_IIGR 2) */
		if (Escape (state->_hoops_PGICI, GETSCALINGFACTOR, 0, NULL, (LPSTR)&_hoops_PSRSR) > 0) {
			_hoops_PIIH = 1.0f / (1L << _hoops_PSRSR.x);
			_hoops_HIIH = 1.0f / (1L << _hoops_PSRSR.y);
		}

		if (state->_hoops_GAICI) {
			SIZE	   _hoops_CRGSI;
			SIZE	   printer_win_rect;
			SIZE	   preview_vp_rect;
			SIZE	   _hoops_SRGSI;
			POINT   preview_vp_origin;

			GetViewportExtEx (state->_hoops_PGICI, &_hoops_CRGSI);
			GetViewportExtEx (state->_hoops_AGICI,		 &preview_vp_rect);
			GetWindowExtEx	 (state->_hoops_PGICI, &printer_win_rect);
			GetWindowExtEx	 (state->_hoops_AGICI,		 &_hoops_SRGSI);

			_hoops_CGASI = (float)(printer_win_rect.cx * preview_vp_rect.cx)/(float)(_hoops_SRGSI.cx * _hoops_CRGSI.cx);
			_hoops_SGASI = (float)(printer_win_rect.cy * preview_vp_rect.cy)/(float)(_hoops_SRGSI.cy * _hoops_CRGSI.cy);

			_hoops_PIIH *= _hoops_CGASI;
			_hoops_HIIH *= _hoops_SGASI;

			GetViewportOrgEx (state->_hoops_AGICI, &preview_vp_origin);

			xoffset = preview_vp_origin.x;
			yoffset = preview_vp_origin.y;
		}
	}
#endif

	state->_hoops_CSC._hoops_AGAA = _hoops_IHCR->_hoops_AGAA;

	int _hoops_AGRSH = (int)(_hoops_IHCR->_hoops_AGAA.left * _hoops_PIIH) + xoffset;
	int _hoops_AGSIR = (int)((state->yfudge - _hoops_IHCR->_hoops_AGAA.top) * _hoops_HIIH) + yoffset;
	int x1 = (int)(_hoops_IHCR->_hoops_AGAA.right * _hoops_PIIH) + 1 + xoffset;
	int _hoops_PGRSH = (int)((state->yfudge - _hoops_IHCR->_hoops_AGAA.bottom) * _hoops_HIIH) + 1 + yoffset;

	SetRectRgn (state->_hoops_AAICI, _hoops_AGRSH, _hoops_AGSIR, x1, _hoops_PGRSH);

	SelectClipRgn (state->_hoops_AGICI, state->_hoops_AAICI);
	if (state->_hoops_SRRRR)
		SelectClipRgn (state->_hoops_IGICI, state->_hoops_AAICI);

#ifndef _WIN32_WCE
	if (_hoops_IHCR->_hoops_HCHH != null) {
		if (state->_hoops_HAICI != _hoops_IHCR->_hoops_HCHH->_hoops_CPA) {
			_hoops_ASHH const *		_hoops_CRAIR = _hoops_IHCR->_hoops_HCHH->_hoops_PSHH;
			POINT							_hoops_HRIGA[1024];
			POINT *							points = _hoops_HRIGA;
			int								i;

			if (_hoops_CRAIR->count > _hoops_GGAPR(_hoops_HRIGA))
				POOL_ALLOC_ARRAY_CACHED (points, _hoops_CRAIR->count, POINT, _hoops_IHCR->_hoops_SRA->memory_pool);

			for (i=0; i<_hoops_CRAIR->count; ++i) {
				points[i].x = (int)(_hoops_CRAIR->points[i].x * _hoops_PIIH) + xoffset;
				points[i].y = (int)((state->yfudge - _hoops_CRAIR->points[i].y) * _hoops_HIIH) + yoffset;
			}

			DeleteObject (state->_hoops_PAICI);
			state->_hoops_PAICI = CreatePolygonRgn (points, _hoops_CRAIR->count, WINDING);
			state->_hoops_HAICI = _hoops_IHCR->_hoops_HCHH->_hoops_CPA;

			if (_hoops_CRAIR->count > _hoops_GGAPR(_hoops_HRIGA))
				FREE_ARRAY (points, _hoops_CRAIR->count, POINT);
		}

		ExtSelectClipRgn (state->_hoops_AGICI, state->_hoops_PAICI, RGN_AND);
		if (state->_hoops_SRRRR)
			ExtSelectClipRgn (state->_hoops_IGICI, state->_hoops_PAICI, RGN_AND);
	}

	else
		state->_hoops_HAICI = _hoops_CCC;

#endif
}


#define _hoops_GRASI(_hoops_RRASI,_hoops_ARASI) (_hoops_RRASI.left == _hoops_ARASI.left && \
	_hoops_RRASI.right == _hoops_ARASI.right && \
	_hoops_RRASI.top == _hoops_ARASI.top && \
	_hoops_RRASI.bottom == _hoops_ARASI.bottom)


INLINE void _hoops_PRASI(Net_Rendition const & nr) 
{ 
	MSW_Driver_State alter *_hoops_HRASI = _hoops_IICCI();
	_hoops_HHCR const & _hoops_IRASI = nr->transform_rendition;
	if (_hoops_HRASI->_hoops_CSC._hoops_GCICI != _hoops_IRASI->_hoops_CPA) {
		if ((_hoops_IRASI->_hoops_HCHH && _hoops_HRASI->_hoops_HAICI != _hoops_IRASI->_hoops_HCHH->_hoops_CPA) ||
			(!_hoops_IRASI->_hoops_HCHH && _hoops_HRASI->_hoops_HAICI != _hoops_CCC) ||
			!_hoops_GRASI(_hoops_HRASI->_hoops_CSC._hoops_AGAA,_hoops_IRASI->_hoops_AGAA)) {
				_hoops_IGASI (_hoops_HRASI, _hoops_IRASI);
		} 
		_hoops_HRASI->_hoops_CSC._hoops_GCICI = _hoops_IRASI->_hoops_CPA; 
	} 
}


/*
 ****************************
 * _hoops_IHRPR _hoops_GCSR _hoops_GSSAA _hoops_GCSR _hoops_PCCIR	_hoops_IHRPR _hoops_GGHR _hoops_GCSR _hoops_HAS _hoops_GSGGR _hoops_IAS *
 ****************************
 */

/*
 * _hoops_PGAA
 */
local void _hoops_CRASI (
	MSW_Driver_State alter		*state,
	Driver_Color const	*color) {


	SetTextColor (state->_hoops_AGICI, _hoops_SRASI (color->_hoops_HRIR.r,
								   color->_hoops_HRIR.g,
								   color->_hoops_HRIR.b));
	state->_hoops_CSC._hoops_RCICI = *color;
}


/*
 * _hoops_PGAA
 */
local void _hoops_GAASI (
	MSW_Driver_State alter		*state,
	Driver_Color const	*color) {

#ifndef _WIN32_WCE
	SetTextColor (state->_hoops_AGICI, PALETTEINDEX (color->_hoops_PGGCR));
	state->_hoops_CSC._hoops_RCICI = *color;
#endif
}


/*
 * _hoops_PGAA
 */
local void _hoops_RAASI (
	MSW_Driver_State alter		*state,
	Driver_Color const	*color) {
	short const				*_hoops_AAASI;


	_hoops_AAASI = (short const *)state->_hoops_APICI->bmiColors;

#ifndef _WIN32_WCE
	SetTextColor (state->_hoops_AGICI,
				  PALETTEINDEX (_hoops_AAASI[color->_hoops_PIHHP]));
	state->_hoops_CSC._hoops_RCICI = *color;
#endif
}


/*
 * _hoops_PGAA
 */
local void _hoops_PAASI (
	MSW_Driver_State alter		*state,
	Driver_Color const	*color) {


	SetBkColor (state->_hoops_AGICI, _hoops_SRASI (color->_hoops_HRIR.r,
								 color->_hoops_HRIR.g,
								 color->_hoops_HRIR.b));
	state->_hoops_CSC._hoops_ACICI = *color;
}


/*
 * _hoops_PGAA
 */
local void _hoops_HAASI (
	MSW_Driver_State alter		*state,
	Driver_Color const	*color) {

#ifndef _WIN32_WCE
	SetBkColor (state->_hoops_AGICI, PALETTEINDEX (color->_hoops_PGGCR));
	state->_hoops_CSC._hoops_ACICI = *color;
#endif
}


/*
 * _hoops_PGAA
 */
local void _hoops_IAASI (
	MSW_Driver_State alter		*state,
	Driver_Color const	*color) {
	short const				*_hoops_AAASI;


	_hoops_AAASI = (short const *)state->_hoops_APICI->bmiColors;

#ifndef _WIN32_WCE
	SetBkColor (state->_hoops_AGICI,
				PALETTEINDEX (_hoops_AAASI[color->_hoops_PIHHP]));
#endif
	state->_hoops_CSC._hoops_ACICI = *color;
}


/*
 * _hoops_PGAA
 */
local COLORREF _hoops_CAASI (
	MSW_Driver_State alter		*state,
	Driver_Color const	*target,
	Driver_Color const	*window,
	bool alter		*_hoops_GSICI) {
	COLORREF				color;


	color = _hoops_SRASI (target->_hoops_HRIR.r,
				 target->_hoops_HRIR.g,
				 target->_hoops_HRIR.b);

	if (state->_hoops_CSC._hoops_ICICI == R2_XORPEN)
		color ^= _hoops_SRASI (window->_hoops_HRIR.r,
					  window->_hoops_HRIR.g,
					  window->_hoops_HRIR.b);

	*_hoops_GSICI = false;

	return color;
}


/*
 * _hoops_PGAA
 */
local COLORREF _hoops_SAASI (
	MSW_Driver_State alter		*state,
	Driver_Color const	*target,
	Driver_Color const	*window,
	bool alter		*_hoops_GSICI) {

#ifndef _WIN32_WCE
	if (state->_hoops_CSC._hoops_ICICI == R2_XORPEN && !*_hoops_GSICI) {
		LPPALETTEENTRY	_hoops_GPASI;
		LPPALETTEENTRY	_hoops_RPASI;
		LPPALETTEENTRY	_hoops_APASI;
		COLORREF		color;

		_hoops_GPASI = &state->_hoops_CHICI->palPalEntry[0];
		_hoops_RPASI = &_hoops_GPASI[target->_hoops_PGGCR];
		_hoops_APASI = &_hoops_GPASI[window->_hoops_PGGCR];

		color = _hoops_SRASI (_hoops_RPASI->peRed,
					 _hoops_RPASI->peGreen,
					 _hoops_RPASI->peBlue) ^
				_hoops_SRASI (_hoops_APASI->peRed,
					 _hoops_APASI->peGreen,
					 _hoops_APASI->peBlue);

		/*
		 * _hoops_CPGP _hoops_RH _hoops_PIHHR _hoops_HAIR _hoops_HRGR _hoops_HAR _hoops_HHPA _hoops_GGR _hoops_RH _hoops_IHCRH _hoops_SR _hoops_GRS
		 * _hoops_HS _hoops_IS _hoops_PIHHR _hoops_CCA _hoops_RH _hoops_IGHP _hoops_HAIR _hoops_PPR _hoops_PSCR _hoops_PIHHR _hoops_CCA _hoops_RH
		 * _hoops_PIASR _hoops_HAIR
		 */
		*_hoops_GSICI = true;
		return PALETTEINDEX (window->_hoops_PGGCR);
	}
	else {
		*_hoops_GSICI = false;
		return PALETTEINDEX (target->_hoops_PGGCR);
	}
#else
		return 0;
#endif
}


/*
 * _hoops_PGAA
 */
local COLORREF _hoops_PPASI (
	MSW_Driver_State alter		*state,
	Driver_Color const	*target,
	Driver_Color const	*window,
	bool alter		*_hoops_GSICI) {
	short const				*_hoops_AAASI;
	short					_hoops_RPASI;
	short					_hoops_APASI;

#ifndef _WIN32_WCE
	_hoops_AAASI = (short const *)state->_hoops_APICI->bmiColors;
	_hoops_RPASI = _hoops_AAASI[target->_hoops_PIHHP];
	_hoops_APASI = _hoops_AAASI[window->_hoops_PIHHP];

	if (state->_hoops_CSC._hoops_ICICI == R2_XORPEN && !*_hoops_GSICI) {
		COLORREF		color;

		color = PALETTEINDEX (_hoops_RPASI ^ _hoops_APASI);

		if (color == GetNearestColor (state->_hoops_PGICI, color)) {
			/* _hoops_HPASI _hoops_AGIR */
			*_hoops_GSICI = false;
			return color;
		}
		else {
			/*
			 * _hoops_CPGP _hoops_RH _hoops_PIHHR _hoops_HAIR _hoops_HRGR _hoops_HAR _hoops_HHPA _hoops_GGR _hoops_RH _hoops_IHCRH _hoops_SR _hoops_GRS
			 * _hoops_HS _hoops_IS _hoops_PIHHR _hoops_CCA _hoops_RH _hoops_IGHP _hoops_HAIR _hoops_PPR _hoops_PSCR _hoops_PIHHR _hoops_CCA _hoops_RH
			 * _hoops_PIASR _hoops_HAIR
			 */
			*_hoops_GSICI = true;
			return PALETTEINDEX (_hoops_APASI);
		}
	}
	else {
		*_hoops_GSICI = false;
		return PALETTEINDEX (_hoops_RPASI);
	}
#else
		return 0;
#endif
}


/*
 **********************************
 * _hoops_ISAII _hoops_HAS _hoops_ACHP _hoops_IAS	  _hoops_RAIGR _hoops_RA _hoops_RA _hoops_PCCIR _hoops_HAS _hoops_RCSR _hoops_IARGR _hoops_RA _hoops_IAS _hoops_GRI *
 **********************************
 */

/*
 * _hoops_PGAA
 */
local bool _hoops_IPASI (
	MSW_Driver_State alter		*state,
	Net_Rendition const & nr,
	bool alter		*_hoops_GSICI) {
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	HPEN _hoops_CPASI;
	COLORREF color;

	_hoops_CPASI = 0;
	color = (*state->_hoops_SCICI) (state,
									&_hoops_HC->color,
									&nr->_hoops_SAIR->_hoops_GPIR,
									_hoops_GSICI);
	if (state->_hoops_SAHCI) {

		DWORD width = 0;
		if(_hoops_HC->weight < 0)
			width = HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true);
		else if(_hoops_HC->weight == 0)
			width = 1;
		else
			width = _hoops_HC->weight;

		if (!BIT(nr->_hoops_AHP->flags, _hoops_SSGIP) &&
			!state->dc->options._hoops_HHHSR &&
			!BIT(nr->_hoops_AHP->line_style->flags, LSF_ABSOLUTE_WEIGHT)) {
			width *= state->dc->_hoops_PGCC._hoops_CCPGH;
		}

#ifdef _WIN32_WCE
		DWORD _hoops_IGRCI = 0;
#endif
#ifndef _WIN32_WCE
		DWORD _hoops_IGRCI = PS_GEOMETRIC;

		switch (_hoops_HC->style & LCAP_MASK) {
			case LCAP_BUTT:		_hoops_IGRCI |= PS_ENDCAP_FLAT;  break;
			case LCAP_ROUND:	_hoops_IGRCI |= PS_ENDCAP_ROUND; break;
			case LCAP_SQUARE:	_hoops_IGRCI |= PS_ENDCAP_SQUARE; break;
		}

		switch (_hoops_HC->style & LJOIN_MASK) {
			case LJOIN_MITER:	_hoops_IGRCI |= PS_JOIN_MITER; break;
			case LJOIN_ROUND:	_hoops_IGRCI |= PS_JOIN_ROUND; break;
			case LJOIN_BEVEL:	_hoops_IGRCI |= PS_JOIN_BEVEL; break;
		}
#endif
		if (BIT(_hoops_HC->line_style->flags, LSF_SOLID))
			_hoops_CPASI = _hoops_SPRSI (state, _hoops_IGRCI | PS_SOLID, width, color, _hoops_HC->line_style);
#ifndef _WIN32_WCE
		else
			_hoops_CPASI = _hoops_SPRSI (state, _hoops_IGRCI | PS_USERSTYLE, width, color, _hoops_HC->line_style);
#endif
	}

	/* _hoops_SR _hoops_HS _hoops_IRS _hoops_GRAA-_hoops_RPHSR _hoops_HIH _hoops_IAII _hoops_IHGP _hoops_CSGSR, _hoops_PAR _hoops_RPP _hoops_RH _hoops_PGHC _hoops_RPGAR _hoops_SRSH,
	 * _hoops_HPPR _hoops_SGP _hoops_IRS "_hoops_IPSP _hoops_PAPR" (_hoops_HII _hoops_PICCI'_hoops_GRI _hoops_AIHP) _hoops_CSGSR */
#ifndef _WIN32_WCE
		if (_hoops_CPASI == 0)
		_hoops_CPASI = _hoops_SPRSI (state, PS_COSMETIC | PS_USERSTYLE, 1, color, _hoops_HC->line_style);
#endif
	if (_hoops_CPASI == 0)
		return false;

	SelectObject (state->_hoops_AGICI, _hoops_CPASI);

	if (state->_hoops_CSC._hoops_HCICI != TRANSPARENT)
		SetBkMode (state->_hoops_AGICI, state->_hoops_CSC._hoops_HCICI = TRANSPARENT);

	return true;
}

/*
 **********************************
 * _hoops_RCCH _hoops_IRS _hoops_GSGGR _hoops_IAS	  _hoops_RAIGR _hoops_RA _hoops_RA _hoops_PCCIR _hoops_HAS _hoops_RCSR _hoops_IARGR _hoops_RA _hoops_IAS _hoops_GRI *
 **********************************
 */

/*
 * _hoops_PGAA
 */
local void _hoops_SPASI (
	MSW_Driver_State alter *	state,
	Net_Rendition const &		nr,
	bool alter *				_hoops_GSICI,
	bool						_hoops_GHASI,
	RGBAS32 alter *				_hoops_HIGSI,
	_hoops_CIGA const &		_hoops_RHASI) {
	_hoops_CIGA				_hoops_SIGA = _hoops_RHASI;
	HBRUSH						_hoops_AHASI;
	HPEN						_hoops_CPASI;
	COLORREF					_hoops_PHASI;
	COLORREF					_hoops_HHASI;
	int							_hoops_IHASI;
	Display_Context const *		dc = state->dc;
	Driver_Color				_hoops_RSISR;
	bool alter					temp;

	_hoops_SIGA.Modify();
	_hoops_PHASI = 0;

	_hoops_IHASI = _hoops_SIGA->pattern;
	_hoops_RSISR = _hoops_SIGA->color;

	/* _hoops_CHASI _hoops_SGS _hoops_CHASA _hoops_RH _hoops_IPHCI _hoops_GPRR */

	if (state->_hoops_CSC._hoops_ICICI == R2_XORPEN) {
		if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR
			&& *_hoops_HIGSI != _hoops_IAASP) {
			/* _hoops_SHASI .... _hoops_SR _hoops_SAHR _hoops_HGCR _hoops_RH _hoops_PHRHA _hoops_HAIR */
			_hoops_SIGA->color._hoops_PGGCR =
				GetNearestPaletteIndex (state->_hoops_GIICI,
										_hoops_SRASI (_hoops_HIGSI->r,
												 _hoops_HIGSI->g,
												 _hoops_HIGSI->b));
		}
	}

	if (state->_hoops_RCRAP == DT_PLOTTER && _hoops_GHASI) {
		_hoops_AHASI = state->_hoops_SPCCI;
	}
	else {
		if (*_hoops_HIGSI != _hoops_IAASP	&&
			dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR &&
			state->_hoops_IHICI != 4) {
			/* _hoops_HGI _hoops_CGH _hoops_HRGR _hoops_HRII _hoops_RHRH - _hoops_GIASI _hoops_IHPR _hoops_PHRI */
			_hoops_RSISR._hoops_HRIR.r = _hoops_HIGSI->r;
			_hoops_RSISR._hoops_HRIR.g = _hoops_HIGSI->g;
			_hoops_RSISR._hoops_HRIR.b = _hoops_HIGSI->b;
			*_hoops_HIGSI = _hoops_IAASP;
		}

		if (state->_hoops_CSC._hoops_ICICI == R2_XORPEN) {
			if (*_hoops_HIGSI == _hoops_IAASP) {
				/* _hoops_RIASI _hoops_HPGCR _hoops_HSP _hoops_AGIR */
				if (*_hoops_GSICI && _hoops_IHASI != FP_SOLID) {
					temp = *_hoops_GSICI;
					_hoops_HHASI = (*state->_hoops_SCICI) (state,
											&_hoops_RSISR,
											&nr->_hoops_SAIR->_hoops_GPIR,
											&temp);
					_hoops_PHASI = (*state->_hoops_SCICI) (state,
											&_hoops_SIGA->contrast_color,
											&nr->_hoops_SAIR->_hoops_GPIR,
											_hoops_GSICI);
				}
				else {
					temp = *_hoops_GSICI;
					_hoops_PHASI = (*state->_hoops_SCICI) (state,
											&_hoops_RSISR,
											&nr->_hoops_SAIR->_hoops_GPIR,
											&temp);
					_hoops_HHASI = (*state->_hoops_SCICI) (state,
											&_hoops_SIGA->contrast_color,
											&nr->_hoops_SAIR->_hoops_GPIR,
											_hoops_GSICI);
				}


				switch (dc->_hoops_PGCC._hoops_PIHSR) {
					case _hoops_HIHSR: {
						_hoops_SIGA->contrast_color._hoops_HRIR.r = GetRValue (_hoops_PHASI);
						_hoops_SIGA->contrast_color._hoops_HRIR.g = GetGValue (_hoops_PHASI);
						_hoops_SIGA->contrast_color._hoops_HRIR.b = GetBValue (_hoops_PHASI);
					}	break;
					case _hoops_SIHSR: {
						_hoops_SIGA->contrast_color._hoops_PGGCR = (_hoops_GARSR) _hoops_PHASI;
					}	break;
					case _hoops_RIIHP: {
						_hoops_SIGA->contrast_color._hoops_PIHHP = (_hoops_HIHHP) _hoops_PHASI;
					}	break;
				}

				switch (dc->_hoops_PGCC._hoops_PIHSR) {
					case _hoops_HIHSR: {
						_hoops_RSISR._hoops_HRIR.r = GetRValue (_hoops_HHASI);
						_hoops_RSISR._hoops_HRIR.g = GetGValue (_hoops_HHASI);
						_hoops_RSISR._hoops_HRIR.b = GetBValue (_hoops_HHASI);
					}	break;
					case _hoops_SIHSR: {
						_hoops_RSISR._hoops_PGGCR = (_hoops_GARSR) _hoops_HHASI;
					}	break;
					case _hoops_RIIHP: {
						_hoops_RSISR._hoops_PIHHP = (_hoops_HIHHP) _hoops_HHASI;
					}	break;
				}
			}
		}
		else {
			/* _hoops_RIASI _hoops_PIHHR _hoops_AIASI */
			if (*_hoops_HIGSI == _hoops_IAASP) {
				/* _hoops_RIASI _hoops_HPGCR _hoops_HSP _hoops_AGIR */
				_hoops_PHASI = (*state->_hoops_SCICI) (state,
											&_hoops_RSISR,
											&nr->_hoops_SAIR->_hoops_GPIR,
											_hoops_GSICI);
				switch (dc->_hoops_PGCC._hoops_PIHSR) {
					case _hoops_HIHSR: {
						_hoops_RSISR._hoops_HRIR.r = GetRValue (_hoops_PHASI);
						_hoops_RSISR._hoops_HRIR.g = GetGValue (_hoops_PHASI);
						_hoops_RSISR._hoops_HRIR.b = GetBValue (_hoops_PHASI);
					}	break;
					case _hoops_SIHSR: {
						_hoops_RSISR._hoops_PGGCR = (_hoops_GARSR) _hoops_PHASI;
					}	break;
					case _hoops_RIIHP: {
						_hoops_RSISR._hoops_PIHHP = (_hoops_HIHHP) _hoops_PHASI;
					}	break;
				}
			}
		}

		/*
		 * _hoops_PS _hoops_GRS _hoops_RSGR _hoops_GH _hoops_CCA _hoops_IRS _hoops_IRAP _hoops_IPHCI,  _hoops_IRS _hoops_RPHSR _hoops_IPHCI,  _hoops_IRS _hoops_IIPH
		 * _hoops_IPHCI _hoops_PAR _hoops_IRS _hoops_IPSP _hoops_PAPR _hoops_IPHCI _hoops_GPGA _hoops_GPP _hoops_GRRRA _hoops_CGSI -
		 * _hoops_PIAP->_hoops_PIASI,  _hoops_HIASI,	_hoops_RSHAR->_hoops_HSGP _hoops_PPR _hoops_PIAP->_hoops_IHAH._hoops_IIASI.
		 * _hoops_RCPA _hoops_IRHH _hoops_RGR _hoops_IRS _hoops_RSCA _hoops_CIASI (_hoops_RHGRH _hoops_GCAS _hoops_SIASI _hoops_GCASI)
		 * _hoops_SR _hoops_IRHH _hoops_IRS _hoops_IRGH _hoops_PSGR _hoops_PPR _hoops_AA _hoops_HHH _hoops_GHAR _hoops_HHCPR
		 */

	   switch (_hoops_IHASI) {
			case FP_USER_DEFINED: {
				_hoops_AHASI = _hoops_GCGSI (
										   _hoops_HIGSI,
										   _hoops_SIGA->_hoops_PGPH->_hoops_CPA,
										   _hoops_SIGA->_hoops_PGPH->height,
										   _hoops_SIGA->_hoops_PGPH->width,
										   _hoops_SIGA->contrast_color,
										   _hoops_RSISR,
										   _hoops_SIGA->_hoops_PGPH->pattern,
										   _hoops_SIGA->_hoops_PGPH->_hoops_RCHHP);
			}	break;
			case FP_SOLID: {
				/* _hoops_GPGP _hoops_RGR _hoops_AGIR _hoops_SR _hoops_ACRR _hoops_IRS _hoops_RCASI _hoops_ARI */
				_hoops_AHASI = _hoops_CIGSI (_hoops_HIGSI, _hoops_PHASI);
			}	break;
			default: {
				/* _hoops_HGI _hoops_CGH _hoops_SHH _hoops_CPS _hoops_AHSAR _hoops_RASRR _hoops_PRCSR _hoops_PAIA */
				if (BIT (nr->_hoops_SRA->options._hoops_IRARR,
				   _hoops_HHACI)) {
						_hoops_AHASI = _hoops_PIGSI (_hoops_HIGSI,
											_hoops_SIGA->pattern,
											_hoops_RSISR,
											_hoops_SIGA->contrast_color);
				}
				else {
					_hoops_AHASI =	 _hoops_PIGSI (
											_hoops_HIGSI,
											_hoops_SIGA->pattern,
											_hoops_SIGA->contrast_color,
											_hoops_RSISR);
				}
			}	break;
		}
	}

	SelectObject (state->_hoops_AGICI, _hoops_AHASI);
	/*
	 * _hoops_ISGP _hoops_PCCP _hoops_IRPR _hoops_CSGSR
	 */
	if (!state->_hoops_AHICI &&
		!BIT (nr->_hoops_SRA->options._hoops_IRARR, _hoops_RHACI) &&
		(state->_hoops_RCRAP != DT_PLOTTER ||
		(state->_hoops_RCRAP == DT_PLOTTER && !_hoops_GHASI))) {
		SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);
	}
	else {
		_hoops_CPASI = _hoops_SPRSI (state, PS_SOLID, 1, _hoops_PHASI, null);
		SelectObject (state->_hoops_AGICI, _hoops_CPASI);
	}


	if (state->_hoops_CSC._hoops_HCICI != OPAQUE)
		SetBkMode (state->_hoops_AGICI, state->_hoops_CSC._hoops_HCICI = OPAQUE);
}


/*****************************************************************************
 *****************************************************************************
							 _hoops_ACASI _hoops_ICSH _hoops_PCASI
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_SRAC
 */
local void _hoops_HCASI (
	Net_Rendition const & nr,
	Draw_Overlay_List_Action action) 
{
	MSW_Driver_State alter		*state = _hoops_IICCI ();

	if (nr->_hoops_SRA->_hoops_SHPGR != QMoves_XOR)
		return;

	if (BIT (state->_hoops_PIGRR, _hoops_HSPCI)) {
		/* _hoops_ACIPA _hoops_GGSR _hoops_RH _hoops_IHAH _hoops_SRHR _hoops_PPR _hoops_SAS */
		draw_and_reset_poly_cache(state, true);
		_hoops_SHGSI (state);
		SetROP2 (state->_hoops_AGICI, R2_XORPEN);
		state->_hoops_CSC._hoops_ICICI = R2_XORPEN;
		action (nr);
		draw_and_reset_poly_cache(state, true);
		SetROP2 (state->_hoops_AGICI, R2_COPYPEN);
		state->_hoops_CSC._hoops_ICICI = R2_COPYPEN;
		_hoops_SHGSI (state);
	}
}


/*
 * _hoops_SRAC
 */
local void draw_overlay_list (
	Net_Rendition const & nr) 
{
	_hoops_HCASI (nr, HD_Standard_Draw_Overlay_List);
}


/*
 * _hoops_SRAC
 */
local void _hoops_SCPGR (
	Net_Rendition const & nr) 
{
	_hoops_HCASI (nr, HD_Standard_UnDraw_Overlay_List);
}


/*****************************************************************************
 *****************************************************************************
						  _hoops_IPSRH _hoops_SRRPI _hoops_GRIRH
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_PGAA
 */
local INLINE void _hoops_ICASI (
	MSW_Driver_State alter *	state,
	int							count,
	DC_Point const *			points,
	bool						_hoops_CCASI,
	bool						_hoops_SCASI,
	bool						_hoops_GSASI) 
{
	LONG				yfudge = (LONG) state->yfudge;
	int					_hoops_PCCIH = (int)_hoops_CCASI;
	int					close = (int)_hoops_SCASI;
	POINT alter *		outp;
	DC_Point const *	_hoops_RSASI;
	int					_hoops_ASASI;
	DC_Point const *	_hoops_PSASI;

	if (_hoops_PCCIH || close)
		_hoops_ASASI = count+1;
	else
		_hoops_ASASI = count;

	outp = (POINT*) (state->points + state->point_count);

	state->point_count += _hoops_ASASI;
	state->_hoops_CRCCI[state->_hoops_IRCCI++] = _hoops_ASASI;

	_hoops_PSASI = points;

	_hoops_RSASI = points+count;
	while (points < _hoops_RSASI) {
		/*
		 * _hoops_PS _hoops_SGH 0.005 _hoops_PGGA _hoops_RGGHR _hoops_CRHS _hoops_HSASI _hoops_GGR _hoops_RH
		 * _hoops_ISASI _hoops_AHC _hoops_PPR 0.005 _hoops_AHPP _hoops_IS _hoops_GIRR _hoops_GH
		 * _hoops_CIAH
		 */
		outp->x = _hoops_PSCSH(points->x + 0.005);
		outp->y = yfudge - _hoops_PSCSH(points->y + 0.005);
		++outp;
		++points;
	}

	/*
	 * _hoops_PS _hoops_HS _hoops_IRS _hoops_ARPC _hoops_CGPR _hoops_ASCA _hoops_APGR _hoops_SGS _hoops_RH _hoops_ISII _hoops_PCPH
	 * _hoops_GRS _hoops_PGSA _hoops_GH _hoops_IS _hoops_HIH _hoops_HAR _hoops_RHGGP _hoops_RH _hoops_CGHI _hoops_PPSR _hoops_GGR _hoops_RH _hoops_ISII
	 * _hoops_CSASI - _hoops_GGR _hoops_AGR _hoops_IS _hoops_GGSP _hoops_RGR _hoops_SR _hoops_GCIS _hoops_RH _hoops_CGHI _hoops_PPSR
	 * _hoops_RRPC _hoops_SHI _hoops_HPP _hoops_SPR _hoops_AIR _hoops_GGR _hoops_SISR _hoops_HIS _hoops_SGS _hoops_SR _hoops_GRS _hoops_IIHCA _hoops_RH _hoops_CGHI _hoops_AIR
	 * _hoops_GIGHR: _hoops_GAGPR _hoops_ASCA _hoops_ISSC _hoops_IS _hoops_RH _hoops_ACHP-1 _hoops_PPSR _hoops_GHCA _hoops_HAR _hoops_IPHR
	 *		 _hoops_CR _hoops_RH _hoops_SSASI _hoops_RIIRA _hoops_GRS _hoops_HAR _hoops_SSCC
	 *		 _hoops_IAGS _hoops_RH _hoops_PSHR _hoops_III _hoops_GRR _hoops_PPRRR
	 */
	if (_hoops_PCCIH) {
		outp->x = outp[-1].x + 1;
		outp->y = outp[-1].y + 1;
		++outp;
	}

	if (close) {
		points = _hoops_PSASI;
		outp->x = _hoops_PSCSH(points->x + 0.005);
		outp->y = yfudge - _hoops_PSCSH(points->y + 0.005);
	}

	UNREFERENCED(_hoops_GSASI);
}

/*
 * _hoops_SRAC
 */
local void draw_dc_rectangle (
	Net_Rendition const &		nr,
	int							left,
	int							right,
	int							bottom,
	int							top) {
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	Display_Context const *		dc = nr->_hoops_SRA;
	bool						_hoops_GSICI = false;

	if (_hoops_SIGA->pattern != FP_SOLID) {
		HD_Std_DC_Rectangle (nr, left, right+1, bottom-1, top);
		return;
	}

	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	if (_hoops_SIGA->_hoops_CPA != state->_hoops_CSC._hoops_RPCI ||
		state->_hoops_CSC._hoops_SIICI != _hoops_CCC) {
		RGBAS32					_hoops_GGPSI;

		_hoops_GGPSI = _hoops_IAASP;
		_hoops_SPASI (state, nr, &_hoops_GSICI, true, &_hoops_GGPSI, _hoops_SIGA);
		state->_hoops_CSC._hoops_RPCI = _hoops_SIGA->_hoops_CPA;
		state->_hoops_CSC._hoops_SIICI = _hoops_CCC;
	}

	if (BIT (dc->options._hoops_IRARR, _hoops_RHACI) ||
		state->_hoops_PIGRR == _hoops_ASPCI)
		GDI_Rectangle (state->_hoops_AGICI,
				   left, state->yfudge - top,
				   right + 1, state->yfudge - bottom + 1);
	else if (state->_hoops_RCRAP == DT_PLOTTER) /* _hoops_CASGI _hoops_SISS */
		GDI_Rectangle (state->_hoops_AGICI,
				   left - 1, state->yfudge - top - 1,
				   right + 1, state->yfudge - bottom + 1);
	else
		GDI_Rectangle (state->_hoops_AGICI,
				   left, state->yfudge - top,
				   right+2, state->yfudge - bottom+2);
}

local bool _hoops_CPISR (Net_Rendition const & nr)
{
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	MSW_Driver_State *state = _hoops_IICCI ();

	if (_hoops_HC->weight > 1) {

		if (_hoops_HC->weight >= 3) {
			if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
				return true;
			}

			if (BIT(_hoops_HC->flags, _hoops_SRPI) || 
				ANYBIT(_hoops_HC->line_style->flags, (LSF_COMPLEX_ANYBITS & ~(LSF_ABSOLUTE_LENGTH|LSF_ABSOLUTE_WEIGHT))) ||
				ANYBIT((_hoops_HC->style&LCAP_MASK), LCAP_COMPLEX_BITS)) {
				return true;
			}

			if (!BIT(_hoops_HC->line_style->flags, LSF_SOLID) &&
				((_hoops_HC->style & LPAT_MASK) >> LPAT_SHIFT != (_hoops_HC->style & LCAP_MASK) >> LCAP_SHIFT)) {
				return true;
			}	
		}

		if (state->_hoops_SSRRI == _hoops_GGARI || state->_hoops_SSRRI == _hoops_RGARI) {
			if (!BIT(_hoops_HC->line_style->flags, LSF_SOLID)) {
				return true;
			}
			if (_hoops_HC->weight > 3) {
				return true;
			}
		}
	}
	if (BIT(_hoops_HC->flags, _hoops_SRPI) || 
		ANYBIT(_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS&(~LSF_ABSOLUTE_LENGTH))) {
		return true;
	}

	if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) &&
		!(nr->_hoops_SRA->_hoops_SHPGR == QMoves_XOR && BIT (nr->current, _hoops_CRSI))) {
		return true;
	}
	
	return false;
}

local bool _hoops_RGPSI (
	int							count,
	DC_Point const			*points) {

	if (count < 0)
		count = -count;

	while (count-- > 0) {
		if (points->x < -32000.0f || points->x > 32000.0f ||
			points->y < -32000.0f || points->y > 32000.0f)
			return false;
		++points;
	}

	return true;
}

/*
 * _hoops_SRAC
 */
local void draw_dc_polyline (
	Net_Rendition const & nr,
	int							in_count,
	DC_Point const			*points) {
	MSW_Driver_State alter			*state = _hoops_IICCI ();
	Line_Rendition const		&_hoops_HC = nr->_hoops_AHP;
	Display_Context const	*dc = state->dc;
	bool					_hoops_GSICI;
	_hoops_GARRR				_hoops_AGPSI = _hoops_HC->_hoops_CPA;
	int							_hoops_ASASI;
	int							count, chunk;
	int							_hoops_RRC;

	if (_hoops_CPISR (nr)) {
		HD_Std_DC_Polyline (nr, in_count, points);
		return;
	}

	if(!_hoops_RGPSI(in_count, points)){
		if(_hoops_HC->weight > 1 || !BIT(_hoops_HC->line_style->flags, LSF_SOLID)){
			HD_Std_DC_Polyline (nr, in_count, points);
			return;
		}
		if (!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
			HD_Clip_DC_Polyline (nr, in_count, points, 0, 0, 0, 0, 0, 0, _hoops_PHGGA);
			return;
		}
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, in_count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}

	_hoops_PCCCI(nr,2,_hoops_IGCCI);
	_hoops_PRASI(nr);


	if (_hoops_HC->_hoops_CPA != state->_hoops_CSC._hoops_RPCI ||
		state->_hoops_CSC._hoops_ICICI == R2_XORPEN &&
		dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {

		draw_and_reset_poly_cache(state, true);
		state->_hoops_CSC._hoops_RPCI = _hoops_CCC;
	}

	_hoops_RRC = 0;
	if (in_count > 0) {
		chunk = in_count;
	}
	else {
		_hoops_ICHC (in_count, _hoops_RRC, 2);
		chunk = 2;
	}

_hoops_PGPSI:

	if (chunk>state->_hoops_HRCCI[_hoops_IGCCI])
		count = state->_hoops_HRCCI[_hoops_IGCCI] - 2;
	else
		count = chunk;

	chunk -= count;

	if (_hoops_HC->weight < 2) {
		/* _hoops_GSRGR _hoops_IRS _hoops_RSPH _hoops_ICHRR _hoops_III _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_RH _hoops_HACH _hoops_AIR _hoops_SAGGR _hoops_RHIAA, 
		    _hoops_HIH _hoops_RGAR _hoops_IH _hoops_GGSIA _hoops_APGR */
		_hoops_ASASI = count+1;
		_hoops_PCCCI(nr,_hoops_ASASI,_hoops_IGCCI);
		_hoops_ICASI (state, count, points, true, false, false);
	}
	else {
		_hoops_ASASI = count;
		_hoops_PCCCI(nr,_hoops_ASASI,_hoops_IGCCI);
		_hoops_ICASI (state, count, points, false, false, false);
	}

	state->_hoops_ARCCI = _hoops_IGCCI;
	_hoops_GSICI = false; /* _hoops_GASA: _hoops_RGR _hoops_AHPP _hoops_IS _hoops_SHH _hoops_IGI _hoops_IH _hoops_HGPSI _hoops_PCCP _hoops_PIHHR _hoops_CSGSR _hoops_GPP _hoops_IRS _hoops_SCGH _hoops_AIRI */
	do {
		if (_hoops_HC->_hoops_CPA != state->_hoops_CSC._hoops_RPCI) {
			_hoops_IPASI (state, nr, &_hoops_GSICI);
			if (_hoops_GSICI)
				_hoops_AGPSI = _hoops_CCC;
		}
		if (!state->_hoops_RPHCI || _hoops_HC->weight >= 2 || _hoops_GSICI) {
			GDI_Polyline(state->_hoops_AGICI, state->points, _hoops_ASASI);
			if (!_hoops_GSICI)
				_hoops_ACCCI(state);
		}
	} while (_hoops_GSICI);

	state->_hoops_CSC._hoops_RPCI = _hoops_AGPSI;
	state->_hoops_CSC._hoops_SIICI = _hoops_CCC;

	if (chunk > 0) {
		draw_and_reset_poly_cache(state, true);
		points += count-1;
		in_count++;
		goto _hoops_PGPSI;
	}
	if (_hoops_RRC) {
		if (--in_count > 0) {
			points += _hoops_RRC;
			chunk = 2;
			goto _hoops_PGPSI;
		}
	}
}

/*
 * _hoops_SRAC
 */
local void _hoops_IGPSI (
	Net_Rendition const & nr,
	int							in_count,
	DC_Point const			*points) {
	MSW_Driver_State alter			*state = _hoops_IICCI ();
	Line_Rendition const		&_hoops_HC = nr->_hoops_AHP;
	Display_Context const	*dc = state->dc;
	int							_hoops_ASASI;
	int							count;
	HPEN						_hoops_CGPSI;
	
	if (_hoops_CPISR (nr)) {
		HD_Std_DC_Polyline (nr, in_count, points);
		return;
	}

	if(!_hoops_RGPSI(in_count, points)){
		if(_hoops_HC->weight > 1 || !BIT(_hoops_HC->line_style->flags, LSF_SOLID)){
			HD_Std_DC_Polyline (nr, in_count, points);
			return;
		}
		if (!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
			HD_Clip_DC_Polyline (nr, in_count, points, 0, 0, 0, 0, 0, 0, _hoops_PHGGA);
			return;
		}
	}
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, in_count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}

	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);


_hoops_PGPSI:

	/*-1 _hoops_HRGR _hoops_IH _hoops_SSRS _hoops_RSGR _hoops_PPSR*/
	if (in_count>state->_hoops_HRCCI[_hoops_IGCCI])
		count = state->_hoops_HRCCI[_hoops_IGCCI];
	else
		count = in_count;

	in_count -= count;

	_hoops_ASASI = count;
	_hoops_ICASI (state, count, points, false, false, false);
	state->_hoops_ARCCI = _hoops_IGCCI;

	switch (dc->_hoops_PGCC._hoops_PIHSR)
	{
		case _hoops_SIHSR: {
			/* _hoops_CICR _hoops_ARPR _hoops_IRS _hoops_CSGSR _hoops_PPR _hoops_PHHR ... */
#ifndef _WIN32_WCE
			_hoops_CGPSI = CreatePen (PS_SOLID, 1, PALETTEINDEX (_hoops_HC->color._hoops_PGGCR));
#endif
			SelectObject (state->_hoops_AGICI, _hoops_CGPSI);
			GDI_Polyline (state->_hoops_AGICI, state->points, _hoops_ASASI);
			SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);
			DeleteObject (_hoops_CGPSI);
		}	break;

		case _hoops_HIHSR: {
			/* _hoops_CICR _hoops_ARPR _hoops_IRS _hoops_CSGSR _hoops_PPR _hoops_PHHR ... */
			_hoops_CGPSI = CreatePen (PS_SOLID, 1,
				_hoops_SRASI (_hoops_HC->color._hoops_HRIR.r,
					 _hoops_HC->color._hoops_HRIR.g,
					 _hoops_HC->color._hoops_HRIR.b));
			SelectObject (state->_hoops_AGICI, _hoops_CGPSI);
			GDI_Polyline (state->_hoops_AGICI, state->points, _hoops_ASASI);
			SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);
			DeleteObject (_hoops_CGPSI);
		}	break;

		case _hoops_RIIHP: {
			/* _hoops_SRPR _hoops_GIR _hoops_ARI */
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Gray Scale Not handled for WMF");
			return;
		} _hoops_HHHI;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Unknown color system");
			return;
		} _hoops_HHHI
	}

	if (in_count > 0) {
		draw_and_reset_poly_cache(state, true);
		points += count-1;
		in_count++;
		goto _hoops_PGPSI;
	}

	/* _hoops_CPGP _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_HPHR _hoops_GGSR _hoops_IIGR _hoops_III _hoops_SGPSI - _hoops_SHH _hoops_ICIC */
	_hoops_SHGSI (state);
	_hoops_ACCCI(state);
}

/*
 * _hoops_SRAC
 */
local void draw_dc_colorized_face (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				color) {
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	//_hoops_GAGSI _hoops_RCIC	*	_hoops_CSPH = _hoops_SCII->_hoops_GHCSR;
	bool						_hoops_GSICI;


	if (state->_hoops_IHICI == 4 ||
		((state->_hoops_PIGRR&0x0F) == _hoops_CSPCI &&
		!state->_hoops_GPHCI &&
		_hoops_SIGA->pattern != FP_SOLID) ||
		_hoops_SIGA->pattern == FP_USER_DEFINED &&
		(_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP != 0 ||
		((!state->_hoops_IAHCI ||
		  state->_hoops_SSRRI == _hoops_GGARI || state->_hoops_SSRRI == _hoops_RGARI) &&
		(_hoops_SIGA->_hoops_PGPH->height > 8 ||
		  _hoops_SIGA->_hoops_PGPH->width > 8)))) {
		HD_Std_DC_Colorized_Face (nr, count, points, color);
		return;
	}
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Face (nr, count, points, color, _hoops_GPHC);
		return;
	}

	draw_and_reset_poly_cache (state, true);
	_hoops_PRASI(nr);

	_hoops_ICASI (state, count, points, false, true, true);
	state->_hoops_ARCCI = _hoops_CGCCI;

	_hoops_GSICI = false;

	do {
		RGBAS32			_hoops_GGPSI = *color;

		_hoops_SPASI (state, nr, &_hoops_GSICI, false, &_hoops_GGPSI, _hoops_SIGA);

		if (state->_hoops_APHCI) {
			if (_hoops_GSICI)
				draw_and_reset_poly_cache(state, false);
		}
		else {
			GDI_Polygon (state->_hoops_AGICI, (POINT *)state->points, count);
			if (!_hoops_GSICI)
				_hoops_ACCCI(state);
		}
	} while (_hoops_GSICI);

	state->_hoops_CSC._hoops_RPCI = _hoops_CCC;
}


/*
 * _hoops_SRAC
 */
local void _hoops_RPCGA (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Line_Rendition const &		_hoops_HC = nr->_hoops_RHP;
	Display_Context const *		dc = nr->_hoops_SRA;
	bool						_hoops_GRPSI;
	bool						_hoops_RRPSI;
	bool						_hoops_GSICI;
	_hoops_GARRR					_hoops_ARPSI = _hoops_SIGA->_hoops_CPA;
	_hoops_GARRR					_hoops_PRPSI = _hoops_HC->_hoops_CPA;

	if (count+1 > state->_hoops_HRCCI[_hoops_CGCCI]) {
		HD_Std_DC_Polygon (nr, count, points);
		return;
	}

	if (_hoops_HC->weight > 1 &&
		(dc->_hoops_PGCC._hoops_CCPGH != 1.0f &&
		!BIT(nr->_hoops_AHP->flags, _hoops_SSGIP) &&
		!dc->options._hoops_HHHSR &&
		!BIT(nr->_hoops_AHP->line_style->flags, LSF_ABSOLUTE_WEIGHT))) {
		HD_Std_DC_Polygon (nr, count, points);
		return;
	}

	if (!BIT(_hoops_HC->line_style->flags, LSF_SOLID)) {
		if (state->_hoops_SSRRI < _hoops_SHRCI) {
			HD_Std_DC_Polygon (nr, count, points);
			return;
		}
		if (_hoops_HC->weight > 1) {
			HD_Std_DC_Polygon (nr, count, points);
			return;
		}
	}
	if (BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS)) {
		HD_Std_DC_Polygon (nr, count, points);
		return;
	}
	if (state->_hoops_SSRRI == _hoops_GGARI || state->_hoops_SSRRI == _hoops_RGARI) {
		if (_hoops_HC->weight > 3) {
			if (!(_hoops_HC->style & LJOIN_ROUND)) {
				HD_Std_DC_Polygon (nr, count, points);
				return;
			}
		}
	}


	if (((state->_hoops_PIGRR&0x0F) == _hoops_CSPCI &&
		!state->_hoops_GPHCI &&
		_hoops_SIGA->pattern != FP_SOLID) ||
		_hoops_SIGA->pattern == FP_USER_DEFINED &&
		(_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP != 0 ||
		((!state->_hoops_IAHCI ||
		  state->_hoops_SSRRI == _hoops_GGARI || state->_hoops_SSRRI == _hoops_RGARI) &&
		(_hoops_SIGA->_hoops_PGPH->height > 8 ||
		  _hoops_SIGA->_hoops_PGPH->width > 8)))) {
			HD_Std_DC_Polygon (nr, count, points);
			return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Std_DC_Polygon (nr, count, points);
		return;
	}

	_hoops_PCCCI(nr,count,_hoops_CGCCI);
	_hoops_PRASI(nr);

	if (_hoops_SIGA->_hoops_CPA != state->_hoops_CSC._hoops_RPCI ||
		_hoops_HC->_hoops_CPA != state->_hoops_CSC._hoops_SIICI ||
		state->_hoops_CSC._hoops_ICICI == R2_XORPEN &&
		dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {

		draw_and_reset_poly_cache(state, true);

		state->_hoops_CSC._hoops_RPCI = _hoops_CCC;
		state->_hoops_CSC._hoops_SIICI = _hoops_CCC;
	}

	_hoops_ICASI (state, count, points, false, true, true);
	state->_hoops_ARCCI = _hoops_CGCCI;

	_hoops_RRPSI = false;
	_hoops_GRPSI = false;
	_hoops_GSICI		= false;

	do {
		if (_hoops_SIGA->_hoops_CPA != state->_hoops_CSC._hoops_RPCI ||
			_hoops_HC->_hoops_CPA != state->_hoops_CSC._hoops_SIICI) {
			RGBAS32				_hoops_GGPSI;

			_hoops_GGPSI = _hoops_IAASP;
			_hoops_SPASI (state, nr, &_hoops_RRPSI, false, &_hoops_GGPSI, _hoops_SIGA);

			_hoops_IPASI (state, nr, &_hoops_GRPSI);

			_hoops_GSICI = _hoops_GRPSI && _hoops_RRPSI;

			if (_hoops_GSICI) {
				_hoops_ARPSI = _hoops_CCC;
				_hoops_PRPSI = _hoops_CCC;
			}
		}

		if (_hoops_ICCCI(state->points, count)) {
			_hoops_CCCCI(state->points);
			if (!_hoops_GSICI)
				_hoops_ACCCI(state);
		}
		else {
			if (state->_hoops_APHCI) {
				if (_hoops_GSICI)
					draw_and_reset_poly_cache(state, false);
			}
			else {
				GDI_Polygon (state->_hoops_AGICI, (POINT *)state->points, count);
				if (!_hoops_GSICI)
					_hoops_ACCCI(state);
			}
		}
	} while (_hoops_GSICI);

	state->_hoops_CSC._hoops_RPCI = _hoops_ARPSI;
	state->_hoops_CSC._hoops_SIICI = _hoops_PRPSI;
}


/*
 * _hoops_SRAC
 */
local void draw_dc_face (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Display_Context const *		dc = nr->_hoops_SRA;
	bool						_hoops_GSICI;
	_hoops_GARRR					_hoops_AGPSI = _hoops_SIGA->_hoops_CPA;

	if (count+1 > state->_hoops_HRCCI[_hoops_CGCCI]) {
		HD_Std_DC_Face (nr, count, points);
		return;
	}

	if (((state->_hoops_PIGRR&0x0F) == _hoops_CSPCI &&
		!state->_hoops_GPHCI &&
		_hoops_SIGA->pattern != FP_SOLID) ||
		_hoops_SIGA->pattern == FP_USER_DEFINED &&
		(_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP != 0 ||
		((!state->_hoops_IAHCI ||
		  state->_hoops_SSRRI == _hoops_GGARI || state->_hoops_SSRRI == _hoops_RGARI) &&
		(_hoops_SIGA->_hoops_PGPH->height > 8 ||
		  _hoops_SIGA->_hoops_PGPH->width > 8)))) {
		HD_Std_DC_Face (nr, count, points);
		return;
	}
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Face (nr, count, points, 0, _hoops_GPHC);
		return;
	}

	_hoops_PCCCI(nr,count,_hoops_CGCCI);
	_hoops_PRASI(nr);

	if (_hoops_SIGA->_hoops_CPA != state->_hoops_CSC._hoops_RPCI ||
		state->_hoops_CSC._hoops_SIICI != _hoops_CCC ||
		state->_hoops_CSC._hoops_ICICI == R2_XORPEN &&
		dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {

		draw_and_reset_poly_cache(state, true);

		state->_hoops_CSC._hoops_RPCI = _hoops_CCC;
	}

	_hoops_ICASI (state, count, points, false, true, true);
	state->_hoops_ARCCI = _hoops_CGCCI;

	_hoops_GSICI = false;

	do {
		if (_hoops_SIGA->_hoops_CPA != state->_hoops_CSC._hoops_RPCI ||
			state->_hoops_CSC._hoops_SIICI != _hoops_CCC) {
			RGBAS32				_hoops_GGPSI;

			_hoops_GGPSI = _hoops_IAASP;
			_hoops_SPASI (state, nr, &_hoops_GSICI, false, &_hoops_GGPSI, _hoops_SIGA);
			if (_hoops_GSICI)
				_hoops_AGPSI = _hoops_CCC;
		}


		if (_hoops_ICCCI(state->points, count)) {
			_hoops_CCCCI(state->points);
			if (!_hoops_GSICI)
				_hoops_ACCCI(state);
		}
		else {
			if (state->_hoops_APHCI) {
				if (_hoops_GSICI)
					draw_and_reset_poly_cache(state, false);
			}
			else {
				GDI_Polygon (state->_hoops_AGICI, (POINT *)state->points, count);
				if (!_hoops_GSICI)
					_hoops_ACCCI(state);
			}
		}
	} while (_hoops_GSICI);

	state->_hoops_CSC._hoops_RPCI = _hoops_AGPSI;
	state->_hoops_CSC._hoops_SIICI = _hoops_CCC;
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
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	bool						_hoops_GSICI = false;
	int							_hoops_RRC;

	if (state->_hoops_IHICI == 4 ||
		((state->_hoops_PIGRR&0x0F) == _hoops_CSPCI &&
		!state->_hoops_GPHCI &&
		_hoops_SIGA->pattern != FP_SOLID) ||
		_hoops_SIGA->pattern == FP_USER_DEFINED &&
		(_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP != 0 ||
		((!state->_hoops_IAHCI ||
		  state->_hoops_SSRRI == _hoops_GGARI || state->_hoops_SSRRI == _hoops_RGARI) &&
		(_hoops_SIGA->_hoops_PGPH->height > 8 ||
		  _hoops_SIGA->_hoops_PGPH->width > 8)))) {
			HD_Span_DC_Colorized_Polytris (nr, count, points, colors, single);
			return;
	}
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 0, 0, 0, 0, _hoops_GPHC|
																	(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}

	draw_and_reset_poly_cache (state, true);
	_hoops_PRASI(nr);

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_ICASI (state, 3, points, false, true, true);
		state->_hoops_ARCCI = _hoops_CGCCI;
		_hoops_GSICI = false;

		do {
			RGBAS32				_hoops_GGPSI = *colors;

			_hoops_SPASI (state, nr, &_hoops_GSICI, false, &_hoops_GGPSI, _hoops_SIGA);

			if (state->_hoops_APHCI) {
				if (_hoops_GSICI)
					draw_and_reset_poly_cache(state, false);
			}
			else {
				GDI_Polygon (state->_hoops_AGICI, (POINT *)state->points, 3);
				if (!_hoops_GSICI)
					_hoops_ACCCI(state);
			}
		} while (_hoops_GSICI);

		points += _hoops_RRC;
		if (!single)
			colors++;
	}

	state->_hoops_CSC._hoops_RPCI  = _hoops_CCC;
}


/*
 * _hoops_SRAC
 */
local void draw_dc_polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Display_Context const *		dc = nr->_hoops_SRA;
	bool						_hoops_GSICI;
	_hoops_GARRR					_hoops_AGPSI = _hoops_SIGA->_hoops_CPA;
	int							_hoops_RRC;

	if (
		((state->_hoops_PIGRR&0x0F) == _hoops_CSPCI &&
		!state->_hoops_GPHCI &&
		_hoops_SIGA->pattern != FP_SOLID) ||
		_hoops_SIGA->pattern == FP_USER_DEFINED &&
		(_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP != 0 ||
		((!state->_hoops_IAHCI ||
		  state->_hoops_SSRRI == _hoops_GGARI || state->_hoops_SSRRI == _hoops_RGARI) &&
		(_hoops_SIGA->_hoops_PGPH->height > 8 ||
		  _hoops_SIGA->_hoops_PGPH->width > 8)))) {
		HD_Span_DC_Polytriangle (nr, count, points);
		return;
	}
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}

	_hoops_PCCCI(nr,3,_hoops_CGCCI);
	_hoops_PRASI(nr);

	if (_hoops_SIGA->_hoops_CPA != state->_hoops_CSC._hoops_RPCI ||
		state->_hoops_CSC._hoops_SIICI != _hoops_CCC ||
		state->_hoops_CSC._hoops_ICICI == R2_XORPEN &&
		dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {

		draw_and_reset_poly_cache(state, true);
		state->_hoops_CSC._hoops_RPCI  = _hoops_CCC;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_PCCCI(nr,count,_hoops_CGCCI);
		_hoops_ICASI (state, 3, points, false, true, true);
		state->_hoops_ARCCI = _hoops_CGCCI;

		_hoops_GSICI = false;

		do {
			if (_hoops_SIGA->_hoops_CPA != state->_hoops_CSC._hoops_RPCI) {
				RGBAS32				_hoops_GGPSI;

				_hoops_GGPSI = _hoops_IAASP;
				_hoops_SPASI (state, nr, &_hoops_GSICI, false, &_hoops_GGPSI, _hoops_SIGA);
				if (_hoops_GSICI)
					_hoops_AGPSI = _hoops_CCC;
			}

			if (state->_hoops_APHCI) {
				if (_hoops_GSICI)
					draw_and_reset_poly_cache(state, false);
			}
			else {
			   GDI_Polygon (state->_hoops_AGICI, (POINT *)state->points, 3);
				if (!_hoops_GSICI)
					_hoops_ACCCI(state);
			}
		} while (_hoops_GSICI);

		points += _hoops_RRC;
	}

	state->_hoops_CSC._hoops_RPCI = _hoops_AGPSI;
}



/*
 * _hoops_SRAC
 */
local void _hoops_HRPSI (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_RRPRH *				_hoops_IRSRA = _hoops_ARPRH ();
	Display_Context const *		dc = nr->_hoops_SRA;
	HBRUSH						_hoops_IRPSI;
	int							_hoops_RRC;


	if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
		HD_Span_DC_Polytriangle (nr, count, points);
		return;
	}
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}

	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_ICASI (state, 3, points, false, true, true);
		state->_hoops_ARCCI = _hoops_CGCCI;

		SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);

		/* _hoops_CICR _hoops_RGHH _hoops_RPHSR _hoops_RSSI _hoops_HPGR _hoops_SRS */
		switch (dc->_hoops_PGCC._hoops_PIHSR)
		{
			case _hoops_SIHSR: {
				/* _hoops_CICR _hoops_ARPR _hoops_IRS _hoops_IPHCI _hoops_PPR _hoops_PHHR ... */
#ifndef _WIN32_WCE
				if (_hoops_SIGA->pattern == FP_SOLID)
					/* _hoops_HHRRH _hoops_RPHSR _hoops_ASRCI _hoops_ARPR _hoops_IRS _hoops_CRPSI _hoops_HRHC _hoops_SRPSI */
					_hoops_IRPSI = CreateSolidBrush (PALETTEINDEX (_hoops_SIGA->color._hoops_PGGCR));
				else
#endif
					{
					_hoops_IRPSI = CreatePatternBrush (_hoops_IRSRA->bit_patterns[_hoops_SIGA->pattern]);
#ifndef _WIN32_WCE
					SetBkColor (state->_hoops_AGICI, PALETTEINDEX (_hoops_SIGA->contrast_color._hoops_PGGCR));
					SetTextColor (state->_hoops_AGICI, PALETTEINDEX (_hoops_SIGA->color._hoops_PGGCR));
#endif
				}
				SelectObject (state->_hoops_AGICI, _hoops_IRPSI);

				GDI_Polygon (state->_hoops_AGICI, (POINT *)state->points, 3);
				SelectObject (state->_hoops_AGICI, state->_hoops_SPCCI);
				DeleteObject (_hoops_IRPSI);
			}	break;

			case _hoops_HIHSR: {
				/* _hoops_CICR _hoops_ARPR _hoops_IRS _hoops_IPHCI _hoops_PPR _hoops_PHHR ... */
				if (_hoops_SIGA->pattern == FP_SOLID)
					/* _hoops_HHRRH _hoops_RPHSR _hoops_ASRCI _hoops_ARPR _hoops_IRS _hoops_CRPSI _hoops_HRHC _hoops_SRPSI */
					_hoops_IRPSI = CreateSolidBrush (_hoops_SRASI (_hoops_SIGA->color._hoops_HRIR.r,
									   _hoops_SIGA->color._hoops_HRIR.g, _hoops_SIGA->color._hoops_HRIR.b));
				else {
					_hoops_IRPSI = CreatePatternBrush (_hoops_IRSRA->bit_patterns[_hoops_SIGA->pattern]);

					SetBkColor (state->_hoops_AGICI,
								_hoops_SRASI (_hoops_SIGA->contrast_color._hoops_HRIR.r,
									 _hoops_SIGA->contrast_color._hoops_HRIR.g,
									 _hoops_SIGA->contrast_color._hoops_HRIR.b));
					SetTextColor (state->_hoops_AGICI,
								  _hoops_SRASI (_hoops_SIGA->color._hoops_HRIR.r,
									   _hoops_SIGA->color._hoops_HRIR.g,
									   _hoops_SIGA->color._hoops_HRIR.b));
				}

				SelectObject (state->_hoops_AGICI, _hoops_IRPSI);
				GDI_Polygon (state->_hoops_AGICI, (POINT *)state->points, 3);
				SelectObject (state->_hoops_AGICI, state->_hoops_SPCCI);
				DeleteObject (_hoops_IRPSI);
			}	break;

			case _hoops_RIIHP: {
				/* _hoops_SRPR _hoops_GIR _hoops_ARI */
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "Gray Scale Not handled for WMF");
				return;
			} _hoops_HHHI;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "Unknown color system");
				return;
			} _hoops_HHHI
		}

		points += _hoops_RRC;
	}

	_hoops_SHGSI (state);
	_hoops_ACCCI(state);
}

/*
 * _hoops_SRAC
 */
local void _hoops_GAPSI (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Display_Context const *		dc = nr->_hoops_SRA;
	HBRUSH						_hoops_IRPSI;
	HPEN						_hoops_CGPSI;
	HRGN						_hoops_RAPSI;
	RECT						_hoops_AAPSI;
	int							_hoops_CGRCI;
	int							i, j;
	POINT						point;
	int							spacing;


	if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
		HD_Std_DC_Face (nr, count, points);
		return;
	}
	
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Face (nr, count, points, 0, _hoops_GPHC);
		return;
	}
	
	if(!_hoops_RGPSI(count, points) && !BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
		HD_Clip_DC_Face (nr, count, points, 0, _hoops_PHGGA);
		return;
	}

	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	_hoops_ICASI (state, count, points, false, true, true);
	state->_hoops_ARCCI = _hoops_CGCCI;


	/*
	 * _hoops_CPGP _hoops_RH _hoops_GSSR _hoops_SHPR _hoops_HRGR 72 _hoops_CGSGI (36 _hoops_PAGAI _hoops_RIR _hoops_SRPGH)
	 * _hoops_SR _hoops_AIRA _hoops_ISCP _hoops_HGRC _hoops_III _hoops_SGCR _hoops_GPP _hoops_CPHSR _hoops_RAAA
	 * _hoops_RIR _hoops_CPIHH	 (_hoops_SRPGH _hoops_IGRC)
	 */

	_hoops_CGRCI = (int) ((float) (dc->_hoops_PGCC._hoops_PRPSR.x /
								dc->_hoops_PGCC.size.x) / 36.0f);

	if (_hoops_CGRCI < 1)
			_hoops_CGRCI = 1;

	/* _hoops_CICR _hoops_RGHH _hoops_RPHSR _hoops_RSSI _hoops_HPGR _hoops_SRS */
	switch (dc->_hoops_PGCC._hoops_PIHSR)
	{
		case _hoops_SIHSR: {
#ifndef _WIN32_WCE
			_hoops_IRPSI = CreateSolidBrush (PALETTEINDEX (_hoops_SIGA->color._hoops_PGGCR));

			_hoops_CGPSI = CreatePen (PS_SOLID, _hoops_CGRCI,
				PALETTEINDEX (_hoops_SIGA->contrast_color._hoops_PGGCR));
#endif
		}	break;

		case _hoops_HIHSR: {
			_hoops_IRPSI = CreateSolidBrush (_hoops_SRASI (_hoops_SIGA->color._hoops_HRIR.r,
								   _hoops_SIGA->color._hoops_HRIR.g,
								   _hoops_SIGA->color._hoops_HRIR.b));

			_hoops_CGPSI = CreatePen (PS_SOLID, _hoops_CGRCI,
				_hoops_SRASI (_hoops_SIGA->contrast_color._hoops_HRIR.r,
								 _hoops_SIGA->contrast_color._hoops_HRIR.g,
								 _hoops_SIGA->contrast_color._hoops_HRIR.b));
		}	break;

		case _hoops_RIIHP: {
			short const				*_hoops_AAASI;

			_hoops_AAASI = (short const *)state->_hoops_APICI->bmiColors;
#ifndef _WIN32_WCE
			_hoops_IRPSI = CreateSolidBrush (PALETTEINDEX (_hoops_AAASI[_hoops_SIGA->color._hoops_PIHHP]));

			_hoops_CGPSI = CreatePen (PS_SOLID, _hoops_CGRCI,
				PALETTEINDEX (_hoops_AAASI[_hoops_SIGA->contrast_color._hoops_PIHHP]));
#endif
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Unknown color system");
			return;
		} _hoops_HHHI
	}

	SelectObject (state->_hoops_AGICI, _hoops_IRPSI);
	SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);

	GDI_Polygon (state->_hoops_AGICI, state->points, count);

	state->_hoops_CSC._hoops_RPCI = _hoops_SIGA->_hoops_CPA;

#ifndef _WIN32_WCE
	if (_hoops_SIGA->pattern != FP_SOLID) {
	    SelectObject (state->_hoops_AGICI, _hoops_CGPSI);
    
	    BeginPath (state->_hoops_AGICI);
		    GDI_Polyline (state->_hoops_AGICI, (POINT *)state->points, count);
	    EndPath (state->_hoops_AGICI);
    
	    _hoops_RAPSI = PathToRegion (state->_hoops_AGICI);
    
	    /* _hoops_AGGA _hoops_GRAS _hoops_RH _hoops_IASC _hoops_AHCRR */
	    GetRgnBox (_hoops_RAPSI, &_hoops_AAPSI);
	    ExtSelectClipRgn (state->_hoops_AGICI, _hoops_RAPSI, RGN_AND);

	    DeleteObject (_hoops_RAPSI);
    
	    _hoops_AAPSI.left = 65536;
	    _hoops_AAPSI.right = 0;
	    _hoops_AAPSI.top = 65536;
	    _hoops_AAPSI.bottom = 0;
    
	    for (i = 0; i < count; i++) {
		    POINT	*	_hoops_GAPPA;
    
		    _hoops_GAPPA = &state->points[i];
    
		    if (_hoops_GAPPA->x < _hoops_AAPSI.left) _hoops_AAPSI.left = _hoops_GAPPA->x;
		    if (_hoops_GAPPA->y < _hoops_AAPSI.top) _hoops_AAPSI.top = _hoops_GAPPA->y;
		    if (_hoops_GAPPA->x > _hoops_AAPSI.right) _hoops_AAPSI.right = _hoops_GAPPA->x;
		    if (_hoops_GAPPA->y > _hoops_AAPSI.bottom) _hoops_AAPSI.bottom = _hoops_GAPPA->y;
	    }
    
    
    
	    /*
	     * _hoops_PS _hoops_PIHA _hoops_SHR _hoops_PAPSI _hoops_HPGR 0,0 _hoops_IH _hoops_CISRI
	     * _hoops_CPGP _hoops_PAIA _hoops_CHR _hoops_SHR 8 _hoops_SIH _hoops_AAIA
	     * _hoops_AGGA _hoops_SR _hoops_CHR _hoops_HCR _hoops_ARP _hoops_IS _hoops_CISA _hoops_RH _hoops_HAPSI _hoops_CCA _hoops_RH _hoops_HSGP
	     */
    
	    spacing = 8 * _hoops_CGRCI;
    

	    switch (_hoops_SIGA->pattern) {
		    case FP_SLANT_RIGHT:
		    case FP_WINDOW_SLANT_RIGHT: {
			    /* _hoops_IAPSI _hoops_CCA _hoops_SCIA _hoops_RAAP _hoops_RPIA _hoops_IIGR _hoops_RPPS */
    
			    /* _hoops_GCRR _hoops_AHCRR _hoops_AHSC _hoops_RAPR _hoops_IH _hoops_CAPSI _hoops_IS _hoops_RHHR _hoops_HCR _hoops_RGCRA */
			    _hoops_AAPSI.right	+= (_hoops_AAPSI.bottom - _hoops_AAPSI.top);
    
			    /* _hoops_AGGA _hoops_SRPA _hoops_IS 8 _hoops_IGRH _hoops_HIICP _hoops_GAR _hoops_RPP _hoops_III 0 */
			    _hoops_AAPSI.left -= _hoops_AAPSI.left % spacing;
    
			    /* _hoops_AGGA _hoops_IS _hoops_GRHP _hoops_HSGP _hoops_RGCGA _hoops_SRPA _hoops_IS _hoops_HSPP _hoops_HPGR 8 _hoops_IGRH _hoops_HIICP _hoops_IIHA _hoops_GPP _hoops_HAPC */
			    _hoops_AAPSI.left += (spacing - (_hoops_AAPSI.top % spacing));
    
			    for (i = _hoops_AAPSI.left; i < _hoops_AAPSI.right; i += spacing) {
				    MoveToEx (state->_hoops_AGICI, i, _hoops_AAPSI.top, &point);
				    /* _hoops_SAPSI _hoops_RPHR _hoops_SPR _hoops_AIR _hoops_GRR _hoops_AIR _hoops_ISHP */
				    LineTo (state->_hoops_AGICI, i - _hoops_AAPSI.bottom + _hoops_AAPSI.top, _hoops_AAPSI.bottom);
			    }
		    }	break;
		    case FP_SLANT_LEFT:
		    case FP_WINDOW_SLANT_LEFT: {
			    /* _hoops_IAPSI _hoops_CCA 0,0 _hoops_IIGR _hoops_RPPS */
    
			    /* _hoops_GCRR _hoops_AHCRR _hoops_AHSC _hoops_RAPR _hoops_IH _hoops_CAPSI _hoops_IS _hoops_RHHR _hoops_HCR _hoops_RGCRA */
			    _hoops_AAPSI.left  -= (_hoops_AAPSI.bottom - _hoops_AAPSI.top);
    
			    /* _hoops_AGGA _hoops_SRPA _hoops_IS 8 _hoops_IGRH _hoops_GPPSI _hoops_GAR _hoops_RPP _hoops_III 0 */
			    _hoops_AAPSI.left -= _hoops_AAPSI.left % spacing;
    
			    /* _hoops_AGGA _hoops_IS _hoops_GRHP _hoops_HSGP _hoops_RGCGA _hoops_SRPA _hoops_IS _hoops_HSPP _hoops_HPGR 8 _hoops_IGRH _hoops_HIICP _hoops_IIHA _hoops_GPP _hoops_HAPC */
			    _hoops_AAPSI.left -= (spacing - (_hoops_AAPSI.top % spacing));
    
			    /* _hoops_IPCP _hoops_HGGAR _hoops_IH _hoops_RGR _hoops_HSPP _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_RRI _hoops_SIRAR */
			    for (i = _hoops_AAPSI.left; i < _hoops_AAPSI.right; i += spacing) {
				    MoveToEx (state->_hoops_AGICI, i, _hoops_AAPSI.top, &point);
				    /* _hoops_SAPSI _hoops_RPHR _hoops_SPR _hoops_AIR _hoops_GRR _hoops_AIR _hoops_ISHP */
				    LineTo (state->_hoops_AGICI, i + _hoops_AAPSI.bottom - _hoops_AAPSI.top, _hoops_AAPSI.bottom);
			    }
		    }	break;
		    case FP_VERTICAL_BARS:
		    case FP_WINDOW_VERTICAL_BARS: {
			    for (i = _hoops_AAPSI.left / spacing * spacing; i < _hoops_AAPSI.right; i += spacing) {
				    MoveToEx (state->_hoops_AGICI, i, _hoops_AAPSI.top, &point);
				    LineTo (state->_hoops_AGICI, i, _hoops_AAPSI.bottom);
			    }
		    }	break;
		    case FP_HORIZONTAL_BARS:
		    case FP_WINDOW_HORIZONTAL_BARS: {
			    _hoops_AAPSI.left -= spacing;
			    for (i = _hoops_AAPSI.top / spacing * spacing; i < _hoops_AAPSI.bottom; i += spacing) {
				    MoveToEx (state->_hoops_AGICI, _hoops_AAPSI.right, i, &point);
				    LineTo (state->_hoops_AGICI, _hoops_AAPSI.left, i);
			    }
		    }	break;
		    case FP_CROSSHATCH:
		    case FP_WINDOW_CROSSHATCH: {
			    for (i = _hoops_AAPSI.left / spacing * spacing; i < _hoops_AAPSI.right; i += spacing) {
				    MoveToEx (state->_hoops_AGICI, i, _hoops_AAPSI.top, &point);
				    LineTo (state->_hoops_AGICI, i, _hoops_AAPSI.bottom);
			    }
			    _hoops_AAPSI.left -= spacing;
			    for (i = _hoops_AAPSI.top / spacing * spacing; i < _hoops_AAPSI.bottom; i += spacing) {
				    MoveToEx (state->_hoops_AGICI, _hoops_AAPSI.right, i, &point);
				    LineTo (state->_hoops_AGICI, _hoops_AAPSI.left, i);
			    }
		    }	break;
		    case FP_DIAMONDS:
		    case FP_WINDOW_DIAMONDS: {
			    /* _hoops_IAPSI _hoops_CCA _hoops_SCIA _hoops_RAAP _hoops_RPIA _hoops_IIGR _hoops_RPPS */
    
			    /* _hoops_GCRR _hoops_AHCRR _hoops_AHSC _hoops_RAPR _hoops_IH _hoops_CAPSI _hoops_IS _hoops_RHHR _hoops_HCR _hoops_RGCRA */
			    _hoops_AAPSI.right	+= (_hoops_AAPSI.bottom - _hoops_AAPSI.top);
    
			    /* _hoops_AGGA _hoops_SRPA _hoops_IS 8 _hoops_IGRH _hoops_GPPSI _hoops_GAR _hoops_RPP _hoops_III 0 */
			    _hoops_AAPSI.left -= _hoops_AAPSI.left % spacing;
    
			    /* _hoops_AGGA _hoops_IS _hoops_GRHP _hoops_HSGP _hoops_RGCGA _hoops_SRPA _hoops_IS _hoops_HSPP _hoops_HPGR 8 _hoops_IGRH _hoops_HIICP _hoops_IIHA _hoops_GPP _hoops_HAPC */
			    _hoops_AAPSI.left += (spacing - (_hoops_AAPSI.top % spacing));
    
			    for (i = _hoops_AAPSI.left; i < _hoops_AAPSI.right; i += spacing) {
				    MoveToEx (state->_hoops_AGICI, i, _hoops_AAPSI.top, &point);
				    /* _hoops_SAPSI _hoops_RPHR _hoops_SPR _hoops_AIR _hoops_GRR _hoops_AIR _hoops_ISHP */
				    LineTo (state->_hoops_AGICI, i - _hoops_AAPSI.bottom + _hoops_AAPSI.top, _hoops_AAPSI.bottom);
			    }
			    /* _hoops_IAPSI _hoops_CCA 0,0 _hoops_IIGR _hoops_RPPS */
    
			    /* _hoops_GCRR _hoops_AHCRR _hoops_AHSC _hoops_RAPR _hoops_IH _hoops_CAPSI _hoops_IS _hoops_RHHR _hoops_HCR _hoops_RGCRA */
			    _hoops_AAPSI.left  -= (_hoops_AAPSI.bottom - _hoops_AAPSI.top);
    
			    /* _hoops_AGGA _hoops_SRPA _hoops_IS 8 _hoops_IGRH _hoops_GPPSI _hoops_GAR _hoops_RPP _hoops_III 0 */
			    _hoops_AAPSI.left -= _hoops_AAPSI.left % spacing;
    
			    /* _hoops_AGGA _hoops_IS _hoops_GRHP _hoops_HSGP _hoops_RGCGA _hoops_SRPA _hoops_IS _hoops_HSPP _hoops_HPGR 8 _hoops_IGRH _hoops_HIICP _hoops_IIHA _hoops_GPP _hoops_HAPC */
			    _hoops_AAPSI.left -= (spacing - (_hoops_AAPSI.top % spacing));
    
			    /* _hoops_IPCP _hoops_HGGAR _hoops_IH _hoops_RGR _hoops_HSPP _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_RRI _hoops_SIRAR */
			    for (i = _hoops_AAPSI.left; i < _hoops_AAPSI.right; i += spacing) {
				    MoveToEx (state->_hoops_AGICI, i, _hoops_AAPSI.top, &point);
				    /* _hoops_SAPSI _hoops_RPHR _hoops_SPR _hoops_AIR _hoops_GRR _hoops_AIR _hoops_ISHP */
				    LineTo (state->_hoops_AGICI, i + _hoops_AAPSI.bottom - _hoops_AAPSI.top, _hoops_AAPSI.bottom);
			    }
		    }	break;
		    case FP_SQUARE_DOTS:
		    case FP_WINDOW_SQUARE_DOTS: {
			    /*
			     * _hoops_ASC _hoops_CHR _hoops_IRS _hoops_RSCA _hoops_HAGH _hoops_PPR _hoops_GHAP _hoops_RRAPH _hoops_CPIC _hoops_IS _hoops_HPCAR _hoops_CGH _hoops_CSRA
			     * _hoops_GAR _hoops_RPHSR _hoops_RPPSI _hoops_HRII _hoops_HSAR _hoops_APGR
			     */
			    for (i = _hoops_AAPSI.left / spacing * spacing; i < _hoops_AAPSI.right; i += spacing) {
				    for (j = _hoops_AAPSI.top / spacing * spacing; j < _hoops_AAPSI.bottom; j += spacing) {
					    GDI_Rectangle (state->_hoops_AGICI, i, j, i + _hoops_CGRCI*2, j + _hoops_CGRCI*2);
				    }
			    }
		    }	break;
		    case FP_CHECKERBOARD:
		    case FP_WINDOW_CHECKERBOARD: {
			    _hoops_AAPSI.left -= spacing;
			    for (i = _hoops_AAPSI.left / spacing * spacing; i < _hoops_AAPSI.right; i += spacing) {
				    for (j = _hoops_AAPSI.top / spacing * spacing; j < _hoops_AAPSI.bottom; j += spacing) {
					    MoveToEx (state->_hoops_AGICI, i + 4 * _hoops_CGRCI, j, &point);
					    LineTo (state->_hoops_AGICI, i + spacing, j);
					    LineTo (state->_hoops_AGICI, i + spacing, j + 4 * _hoops_CGRCI);
					    LineTo (state->_hoops_AGICI, i + 4 * _hoops_CGRCI, j + 4 * _hoops_CGRCI);
					    LineTo (state->_hoops_AGICI, i + 4 * _hoops_CGRCI, j);
				    }
			    }
		    }	break;
	    }

		_hoops_SHGSI (state);
	}
#endif

	SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);
	SelectObject (state->_hoops_AGICI, state->_hoops_SPCCI);
	DeleteObject (_hoops_CGPSI);
	DeleteObject (_hoops_IRPSI);


	_hoops_ACCCI(state);
}



/*
 * _hoops_SRAC
 */
local void _hoops_APPSI (
	Net_Rendition const & nr,
	int							count,
	DC_Point const			*points) {
	int							_hoops_RRC;

	if (nr->_hoops_IHA->pattern == FP_USER_DEFINED) {
		HD_Span_DC_Polytriangle (nr, count, points);
		return;
	}
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}

	if(!_hoops_RGPSI(count, points) && !BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_PHGGA);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_GAPSI (nr, 3, points);
		points += _hoops_RRC;
	}
}


local void draw_3d_nurbs_curve (
	Net_Rendition const &		nr,
	_hoops_PIRGR const			*curve)
{
#ifndef _hoops_CCPIR
#ifndef _WIN32_WCE    /* _hoops_PPPSI _hoops_ASSP'_hoops_RA _hoops_PII _hoops_HPPSI */
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	_hoops_GARRR _hoops_AGPSI = _hoops_HC->_hoops_CPA;
	MSW_Driver_State *state = _hoops_IICCI ();
	bool _hoops_GSICI;
	int count, _hoops_PHISR, i;
	Point *_hoops_HHISR;
	DC_Point *_hoops_IHISR;
	float const *mat;
	Polyline polyline;

	if (!curve->control_point_count)
		return;

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_NURBS_Curve (nr, curve);
		return;
	}

	if (nr->_hoops_ARA->_hoops_APPI._hoops_SAR ||
		_hoops_CPISR (nr)) {
		HD_Std_3D_NURBS_Curve (nr, curve);
		return;
	}

	if (curve->polyline.points == null) {
		HI_Generate_NURBS_Polyline (curve, 
			&nr->_hoops_ARA->_hoops_APPI, 
			&nr->transform_rendition->matrix->data, 
			&polyline, 0);
		if (!polyline.points)
			return; /* _hoops_CHISR? */

		_hoops_PIRGR alter *_hoops_IPPSI = (_hoops_PIRGR alter *)curve;
		/* _hoops_CHPR _hoops_SAII _hoops_IIGR _hoops_RH _hoops_PIH _hoops_IS _hoops_RH _hoops_AGIS */
		_hoops_IPPSI->polyline.points    = polyline.points;		
		_hoops_IPPSI->polyline.count 	  = polyline.count;		
		_hoops_IPPSI->polyline.allocated = polyline.allocated;
	}
	else {
		polyline.points    = curve->polyline.points;
		polyline.count     = curve->polyline.count;
		polyline.allocated = curve->polyline.allocated;
	}
	if (curve->polyline.count*4 > state->_hoops_HRCCI[_hoops_GRCCI]) {
		HD_Std_3D_NURBS_Curve (nr, curve);
		return;
	}
	count = polyline.count;
	_hoops_PHISR = count*3-2;
	ALLOC_ARRAY_ALIGNED (_hoops_HHISR, _hoops_PHISR, Point, 16);
	ALLOC_ARRAY_ALIGNED (_hoops_IHISR, _hoops_PHISR, DC_Point, 16);
	HI_Generate_Polyline_Bezier (count, polyline.points, _hoops_HHISR);

	mat = &nr->transform_rendition->matrix->data.elements[0][0];
	HI_Compute_Transformed_Points (_hoops_PHISR, _hoops_HHISR, mat, (Point *)_hoops_IHISR);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0 ; i < _hoops_PHISR ; i++) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition, 
					_hoops_IHISR[i].x, _hoops_IHISR[i].y, _hoops_IHISR[i].z)) {
				HD_Std_3D_NURBS_Curve (nr, curve);
				goto done;
			}
		}
		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}

	_hoops_PRASI(nr);
	draw_and_reset_poly_cache(state, true);
	_hoops_ICASI (state, _hoops_PHISR, _hoops_IHISR, true, false, false);
	state->_hoops_ARCCI = _hoops_GRCCI;
	_hoops_GSICI = false;

	do {
		if (_hoops_HC->_hoops_CPA != state->_hoops_CSC._hoops_RPCI) {
			_hoops_IPASI (state, nr, &_hoops_GSICI);
			if (_hoops_GSICI)
				_hoops_AGPSI = _hoops_CCC;
		}
		PolyBezier(state->_hoops_AGICI, state->points, _hoops_PHISR);
		if (!_hoops_GSICI)
			_hoops_ACCCI(state);
	} while (_hoops_GSICI);

	state->_hoops_CSC._hoops_RPCI = _hoops_AGPSI;
	state->_hoops_CSC._hoops_SIICI = _hoops_CCC;

done:
	FREE_ARRAY_ALIGNED (_hoops_HHISR, _hoops_PHISR, Point, 16);
	FREE_ARRAY_ALIGNED (_hoops_IHISR, _hoops_PHISR, DC_Point, 16);
#endif
#endif
}

local void draw_3d_elliptical_arc (
		Net_Rendition const & nr,
		Elliptical_Arc const *arc) 
{
#ifndef _WIN32_WCE    /* _hoops_PPPSI _hoops_ASSP'_hoops_RA _hoops_PII _hoops_HPPSI */
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	MSW_Driver_State *state = _hoops_IICCI ();
	int i, count;
	DC_Point buffer[16];
	bool _hoops_GSICI;
	_hoops_GARRR _hoops_AGPSI = _hoops_HC->_hoops_CPA;

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_Elliptical_Arc (nr, arc);
		return;
	}

	if (arc->type == _hoops_GRCP || arc->type == _hoops_RRCP) {
		/* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RSH _hoops_IS _hoops_PGSA _hoops_PIISR _hoops_AGSAR _hoops_ARI, _hoops_PPR 
			_hoops_CHH _hoops_HRII _hoops_HAR _hoops_HIISR _hoops_CCA _hoops_SCII->_hoops_CSIS */
		HD_Std_3D_Elliptical_Arc (nr, arc);
		return;
	}
	if (_hoops_CPISR (nr)) {
		HD_Std_3D_Elliptical_Arc (nr, arc);
		return;
	}

	HD_Generate_Elliptical_Bezier (nr, (_hoops_GHHI const *)arc, &count, buffer);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0 ; i < count ; i++) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition, 
					buffer[i].x, buffer[i].y, buffer[i].z)) {
				HD_Std_3D_Elliptical_Arc (nr, arc);
				return;
			}
		}
		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}

	_hoops_PRASI(nr);
	draw_and_reset_poly_cache(state, true);
	_hoops_ICASI (state, count, buffer, true, false, false);
	state->_hoops_ARCCI = _hoops_GRCCI;
	_hoops_GSICI = false;
	
	do {
		if (_hoops_HC->_hoops_CPA != state->_hoops_CSC._hoops_RPCI) {
			_hoops_IPASI (state, nr, &_hoops_GSICI);
			if (_hoops_GSICI)
				_hoops_AGPSI = _hoops_CCC;
		}
		PolyBezier(state->_hoops_AGICI, state->points, count);
		if (!_hoops_GSICI)
			_hoops_ACCCI(state);
	} while (_hoops_GSICI);

	state->_hoops_CSC._hoops_RPCI = _hoops_AGPSI;
	state->_hoops_CSC._hoops_SIICI = _hoops_CCC;

	return;
#endif
} /* _hoops_RSGR _hoops_API _hoops_PGSA 3d _hoops_ICISR _hoops_PGIS */


/*
 * _hoops_SRAC
 */
local void draw_3d_ellipse (
	Net_Rendition const &	nr,
	Ellipse const *			ellipse) {
	Net_Rendition			_hoops_IICS = nr;
	Line_Rendition			_hoops_CPPSI = _hoops_IICS->_hoops_AHP;

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_Ellipse (nr, ellipse);
		return;
	}

	if (BIT (nr->_hoops_RGP, T_FACES)) {
		HD_Std_3D_Ellipse (nr, ellipse);
		return;
	}
	/* _hoops_RPP _hoops_IIH _hoops_AAPR _hoops_GII _hoops_CGGC _hoops_SGS _hoops_RGR _hoops_CPAP _hoops_SIAS _hoops_SHH _hoops_PISI, 
	   _hoops_RGR _hoops_GHIS _hoops_IIGR _hoops_ASAC _hoops_PPR _hoops_PHIH _hoops_CHH _hoops_SHH _hoops_IRS _hoops_CAGRH.  _hoops_HAPI, _hoops_PHRI, _hoops_SR 
	   _hoops_PAH _hoops_HGCR _hoops_SGGR _hoops_CCA _hoops_SCH.  */
	_hoops_IICS->_hoops_AHP = nr->_hoops_RHP;
	draw_3d_elliptical_arc (nr, (Elliptical_Arc *)ellipse);
	_hoops_IICS->_hoops_AHP = _hoops_CPPSI;
}


/*
 * _hoops_SRAC
 */
local void _hoops_CCISR (
	Net_Rendition const &	nr,
	DC_Point const *		center,
	DC_Point const *		radii,
	float 					start,
	float 					end) {
#ifndef _WIN32_WCE    /* _hoops_PPPSI _hoops_ASSP'_hoops_RA _hoops_PII _hoops_HPPSI */
	MSW_Driver_State *		state = _hoops_IICCI ();
	bool					_hoops_GSICI;
	int						i, count;
	DC_Point 				buffer[16];
	DC_Point 				_hoops_SPPSI[2];
	_hoops_GARRR				_hoops_AGPSI = nr->_hoops_AHP->_hoops_CPA;

	if (_hoops_CPISR (nr)) {
		HD_Std_DC_Elliptical_Arc (nr, center, radii, start, end);
		return;
	}
	_hoops_SPPSI[0].x = radii->x;
	_hoops_SPPSI[0].y = 0;
	_hoops_SPPSI[0].z = 0;
	_hoops_SPPSI[1].x = 0;
	_hoops_SPPSI[1].y = -radii->y;
	_hoops_SPPSI[1].z = 0;
	HD_DC_Generate_Elliptical_Bezier (nr, center, &_hoops_SPPSI[0], &_hoops_SPPSI[1], start, end, &count, buffer);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0 ; i < count ; i++) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition, 
					buffer[i].x, buffer[i].y, buffer[i].z)) {
				HD_Std_DC_Elliptical_Arc (nr, center, radii, start, end);
				return;
			}
		}
		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}
	_hoops_PRASI (nr);
	draw_and_reset_poly_cache (state, true);
	for (i = 0 ; i < count ; i++) {
		buffer[i].x = _hoops_HCCCI(buffer[i].x);
		buffer[i].y = state->yfudge -  _hoops_HCCCI(buffer[i].y);
	}
	_hoops_ICASI (state, count, buffer, true, false, false);
	state->_hoops_ARCCI = _hoops_GRCCI;
	_hoops_GSICI = false;
	do {
		if (nr->_hoops_AHP->_hoops_CPA != state->_hoops_CSC._hoops_RPCI) {
			_hoops_IPASI (state, nr, &_hoops_GSICI);
			if (_hoops_GSICI)
				_hoops_AGPSI = _hoops_CCC;
		}
		PolyBezier(state->_hoops_AGICI, state->points, count);
		if (!_hoops_GSICI)
			_hoops_ACCCI(state);
	} while (_hoops_GSICI);
	state->_hoops_CSC._hoops_RPCI = _hoops_AGPSI;
	state->_hoops_CSC._hoops_SIICI = _hoops_CCC;
#endif
}


/*
 * _hoops_SRAC
 */
local void draw_dc_ellipse (
	Net_Rendition const &		nr,
	DC_Point const *			center,
	DC_Point const *			size) {
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	bool						_hoops_GSICI = false;


	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	state->_hoops_AHICI = true;

	if (_hoops_SIGA->_hoops_CPA != state->_hoops_CSC._hoops_RPCI ||
		state->_hoops_CSC._hoops_SIICI != _hoops_CCC) {
		RGBAS32			_hoops_GGPSI;

		_hoops_GGPSI = _hoops_IAASP;
		_hoops_SPASI (state, nr, &_hoops_GSICI, false, &_hoops_GGPSI, _hoops_SIGA);

		state->_hoops_CSC._hoops_RPCI = _hoops_SIGA->_hoops_CPA;
		state->_hoops_CSC._hoops_SIICI = _hoops_CCC;
	}
	state->_hoops_AHICI = false;

	GDI_Ellipse (state->_hoops_AGICI,
			 _hoops_HCCCI (center->x) - _hoops_HCCCI (size->x),
			 state->yfudge - _hoops_HCCCI (center->y) - _hoops_HCCCI (size->y),
			 _hoops_HCCCI (center->x) + _hoops_HCCCI (size->x) + 1,
			 state->yfudge - _hoops_HCCCI (center->y) + _hoops_HCCCI (size->y) + 1);
}


/*
 * _hoops_SRAC
 */
local void _hoops_SCISR (
		Net_Rendition const & nr,
		DC_Point const			*center,
		DC_Point const			*size) 
{
	Line_Rendition const		&_hoops_HC = nr->_hoops_AHP;
	MSW_Driver_State alter			*state = _hoops_IICCI ();
	bool					_hoops_GSICI = false;
	Display_Context const	*dc = nr->_hoops_SRA;

	if (_hoops_HC->weight > 1 &&
		(dc->_hoops_PGCC._hoops_CCPGH != 1.0f &&
		!BIT(nr->_hoops_AHP->flags, _hoops_SSGIP) &&
		!dc->options._hoops_HHHSR && 
		!BIT(nr->_hoops_AHP->line_style->flags, LSF_ABSOLUTE_WEIGHT))) {
		HD_Std_DC_Outline_Ellipse (nr, center, size);
		return;
	}

	if (!BIT(_hoops_HC->line_style->flags, LSF_SOLID)) {
		if (state->_hoops_SSRRI < _hoops_SHRCI) {
			HD_Std_DC_Outline_Ellipse (nr, center, size);
			return;
		}
		if (_hoops_HC->weight > 1) {
			HD_Std_DC_Outline_Ellipse (nr, center, size);
			return;
		}
	}
	if (BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS)) {
		HD_Std_DC_Outline_Ellipse (nr, center, size);
		return;
	}

	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	if (_hoops_HC->_hoops_CPA != state->_hoops_CSC._hoops_RPCI) {
		_hoops_IPASI (state, nr, &_hoops_GSICI);
		state->_hoops_CSC._hoops_RPCI = _hoops_HC->_hoops_CPA;
		state->_hoops_CSC._hoops_SIICI = _hoops_CCC;
	}
	SelectObject (state->_hoops_AGICI, state->_hoops_SPCCI);
	GDI_Ellipse (state->_hoops_AGICI,
			 _hoops_HCCCI (center->x) - _hoops_HCCCI (size->x),
			 state->yfudge - _hoops_HCCCI (center->y) - _hoops_HCCCI (size->y),
			 _hoops_HCCCI (center->x) + _hoops_HCCCI (size->x) + 1,
			 state->yfudge - _hoops_HCCCI (center->y) + _hoops_HCCCI (size->y) + 1);
}


/*
 * _hoops_SRAC
 */
local void _hoops_GHPSI (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			where) {
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	/*_hoops_SPRS		_hoops_GAGSI _hoops_RCIC *_hoops_CSPH = _hoops_SCII->_hoops_GHCSR;*/


	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	if (state->_hoops_CAHCI) {
#ifndef _WIN32_WCE
		while (count-- > 0) {
			SetPixelV (
			  state->_hoops_AGICI,
			  _hoops_HCCCI (where->x),
			  state->yfudge - _hoops_HCCCI (where->y),
			  _hoops_SRASI (_hoops_HC->color._hoops_HRIR.r,
				   _hoops_HC->color._hoops_HRIR.g,
				   _hoops_HC->color._hoops_HRIR.b));
			where++;
		}
#endif
	}
	else
	{
		while (count-- > 0) {
			SetPixel (
			  state->_hoops_AGICI,
			  _hoops_HCCCI (where->x),
			  state->yfudge - _hoops_HCCCI (where->y),
			  _hoops_SRASI (_hoops_HC->color._hoops_HRIR.r,
				   _hoops_HC->color._hoops_HRIR.g,
				   _hoops_HC->color._hoops_HRIR.b));
			where++;
		}
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_RHPSI (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const				*where) {
	MSW_Driver_State alter				*state = _hoops_IICCI ();
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	/*_hoops_SPRS		_hoops_GAGSI _hoops_RCIC		*_hoops_CSPH = _hoops_SCII->_hoops_GHCSR;*/


	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	if (state->_hoops_CAHCI) {
#ifndef _WIN32_WCE
		while (count-- > 0) {
			SetPixelV (state->_hoops_AGICI,
					   _hoops_HCCCI (where->x),
					   state->yfudge - _hoops_HCCCI (where->y),
					   PALETTEINDEX (_hoops_HC->color._hoops_PGGCR));
			where++;
		}
#endif
	}
	else {
#ifndef _WIN32_WCE
		while (count-- > 0) {
			SetPixel (state->_hoops_AGICI,
					  _hoops_HCCCI (where->x),
					  state->yfudge - _hoops_HCCCI (where->y),
					  PALETTEINDEX (_hoops_HC->color._hoops_PGGCR));
			where++;
		}
#endif
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_AHPSI (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*where) {
	MSW_Driver_State alter				*state = _hoops_IICCI ();
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	short int const					*_hoops_PHPSI = (short int const *)state->_hoops_APICI->bmiColors;
	/*_hoops_SPRS		_hoops_GAGSI _hoops_RCIC		*_hoops_CSPH = _hoops_SCII->_hoops_GHCSR;*/


	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

#ifndef _WIN32_WCE
	if (state->_hoops_CAHCI) {
		while (count-- > 0) {
			SetPixelV (
				state->_hoops_AGICI,
					_hoops_HCCCI (where->x),
					state->yfudge - _hoops_HCCCI (where->y),
					PALETTEINDEX (_hoops_PHPSI[_hoops_HC->color._hoops_PIHHP]));
			where++;
		}
	}
	else
	{
		while (count-- > 0) {
			SetPixel (
				state->_hoops_AGICI,
					_hoops_HCCCI (where->x),
					state->yfudge - _hoops_HCCCI (where->y),
					PALETTEINDEX (_hoops_PHPSI[_hoops_HC->color._hoops_PIHHP]));
			where++;
		}
	}
#endif
}


/*
 * _hoops_SRAC
 */
local void draw_dc_polymarker (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*where,
	float const						*rotations,
	float const						*size_fixups) {
	MSW_Driver_State alter				*state = _hoops_IICCI ();

	state->_hoops_AHICI = true;
	HD_Std_DC_Polymarker (nr, count, where, rotations, size_fixups);
	state->_hoops_AHICI = false;
}


/*
 * _hoops_SRAC
 */
local void draw_dc_rgb32_rasters (
	Net_Rendition const & nr,
	DC_Point const				*start,
	DC_Point const				*end,
	int								row_bytes,
	RGBAS32 const				*rasters) {

	MSW_Driver_State alter		*state = _hoops_IICCI ();
	int						width = (int)(end->x - start->x) + 1;
	int						height = (int)(start->y - end->y) + 1;
	int						_hoops_HHPSI = (int)start->x;
	int						_hoops_IHPSI = state->yfudge - (int)start->y;

	unsigned int			_hoops_CHPSI;
	unsigned int			_hoops_SHPSI;

	unsigned char			*_hoops_GIPSI = null;
	BITMAPINFO * _hoops_RIPSI;



	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	_hoops_CHPSI = ((width*3) + 3) & ~0x3;
	_hoops_SHPSI  = _hoops_CHPSI * height;

	if (height == 1) {
		if (_hoops_SHPSI > state->_hoops_IPCCI) {
			FREE_ARRAY(state->_hoops_HPCCI,state->_hoops_IPCCI,unsigned char);
			state->_hoops_IPCCI=_hoops_SHPSI;
			ALLOC_ARRAY(state->_hoops_HPCCI,state->_hoops_IPCCI,unsigned char);
		}
		_hoops_GIPSI = state->_hoops_HPCCI;
	}
	else {
		ALLOC_ARRAY(_hoops_GIPSI, _hoops_SHPSI, unsigned char);
	}

	if (!_hoops_GIPSI) return;

	_hoops_RIPSI = (BITMAPINFO*) state->_hoops_APCCI;

	_hoops_RIPSI->bmiHeader.biSize				= sizeof (BITMAPINFOHEADER);
	_hoops_RIPSI->bmiHeader.biWidth				= width;
	_hoops_RIPSI->bmiHeader.biHeight				= -height;
	_hoops_RIPSI->bmiHeader.biPlanes				= 1;
	_hoops_RIPSI->bmiHeader.biBitCount			= 24;
	_hoops_RIPSI->bmiHeader.biCompression			= BI_RGB;
	_hoops_RIPSI->bmiHeader.biSizeImage			= _hoops_SHPSI;
	_hoops_RIPSI->bmiHeader.biXPelsPerMeter		= state->_hoops_PIICI;
	_hoops_RIPSI->bmiHeader.biYPelsPerMeter		= state->_hoops_HIICI;
	_hoops_RIPSI->bmiHeader.biClrUsed				= 0;
	_hoops_RIPSI->bmiHeader.biClrImportant		= 0;

	{
		Driver_Color const *		window = &nr->_hoops_SAIR->_hoops_GPIR;
		unsigned char *_hoops_AIPSI;
		RGBAS32 const *_hoops_PIPSI;
		unsigned char const *_hoops_HIPSI;
		int row;
		unsigned char alter *pp;
		unsigned char const *pe;

		_hoops_HIPSI = (unsigned char const*) rasters;
		_hoops_AIPSI = _hoops_GIPSI;
		row=0;

#define XOR_IMAGES_AS_RECT	/* _hoops_AHAC _hoops_GGSR _hoops_RPP _hoops_IRCC _hoops_IS _hoops_AGIRA _hoops_RH _hoops_HPHR _hoops_CSCR _hoops_CIPCA */

#ifdef	XOR_IMAGES_AS_RECT	/* _hoops_GA'_hoops_RA _hoops_RRP _hoops_RH _hoops_IPS _hoops_HPGR _hoops_HCR _hoops_RPP _hoops_GHGA _hoops_IIPSI */
		if (state->_hoops_CSC._hoops_ICICI != R2_XORPEN)
#endif
		while (row<height) {

			_hoops_PIPSI = (RGBAS32 const*) _hoops_HIPSI;

			pp = _hoops_AIPSI;
			pe = _hoops_AIPSI + (width*3);

			while (pp<pe) {
				if (state->_hoops_CSC._hoops_ICICI != R2_XORPEN) {
					*pp++ = _hoops_PIPSI->b;
					*pp++ = _hoops_PIPSI->g;
					*pp++ = _hoops_PIPSI->r;
				}
				else {
					*pp++ = _hoops_PIPSI->b ^ window->_hoops_HRIR.b;
					*pp++ = _hoops_PIPSI->g ^ window->_hoops_HRIR.g;
					*pp++ = _hoops_PIPSI->r ^ window->_hoops_HRIR.r;
				}
				_hoops_PIPSI++;
			}

			_hoops_HIPSI += row_bytes;
			_hoops_AIPSI += _hoops_CHPSI;
			row++;
		}
	}

	if ((state->_hoops_PIGRR != _hoops_PSPCI) &&
		!state->_hoops_SRICI) {

		/*_hoops_RGR _hoops_HRGR _hoops_RH "_hoops_GSSR" _hoops_AGIR*/
#ifndef _WIN32_WCE
		if (state->_hoops_CSC._hoops_ICICI != R2_XORPEN) {
			SetDIBitsToDevice (state->_hoops_AGICI, _hoops_HHPSI, _hoops_IHPSI,
							width, height, 0, 0, 0, height,
							(LPVOID)_hoops_GIPSI,
							_hoops_RIPSI, DIB_RGB_COLORS);
		}
		else {
#ifdef	XOR_IMAGES_AS_RECT
			/* _hoops_RGR _hoops_HPGR _hoops_CHGC _hoops_SHR _hoops_AHPP _hoops_IS _hoops_PGSA _hoops_CPHP */
			_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
			bool						_hoops_GSICI = false;

			draw_and_reset_poly_cache(state, true);
			_hoops_PRASI(nr);

			if (_hoops_SIGA->_hoops_CPA != state->_hoops_CSC._hoops_RPCI ||
				state->_hoops_CSC._hoops_SIICI != _hoops_CCC) {
				RGBAS32					_hoops_GGPSI;

				_hoops_GGPSI = _hoops_IAASP;
				_hoops_SPASI (state, nr, &_hoops_GSICI, true, &_hoops_GGPSI, _hoops_SIGA);
				state->_hoops_CSC._hoops_RPCI = _hoops_SIGA->_hoops_CPA;
				state->_hoops_CSC._hoops_SIICI = _hoops_CCC;
			}

			GDI_Rectangle (state->_hoops_AGICI,
					   _hoops_HHPSI, _hoops_IHPSI,
					   _hoops_HHPSI+width+1, _hoops_IHPSI+height+1);
#else
			/* _hoops_RGR *_hoops_CGH* _hoops_IPHR, _hoops_HIH _hoops_AHPP _hoops_IS _hoops_SAHR _hoops_IRHH _hoops_CIPSI *_hoops_PAR _hoops_ISAP* */
			StretchDIBits (state->_hoops_AGICI, _hoops_HHPSI, _hoops_IHPSI,
							width, height, 0, 0, width, height,
							(LPVOID)_hoops_GIPSI, _hoops_RIPSI,
							DIB_RGB_COLORS, _hoops_SIPSI);
#endif
		}
#endif
	}
	else if (state->_hoops_IRICI) {
		int			_hoops_GCPSI, _hoops_RCPSI;
		int			_hoops_ACPSI, _hoops_PCPSI;
		int			_hoops_HCPSI, _hoops_ICPSI;
		int				_hoops_CCPSI, _hoops_SCPSI;
		float	scale;

		/* _hoops_HAPI _hoops_HRGR _hoops_RH _hoops_CRPCI _hoops_RH _hoops_SHSC _hoops_ICCGR _hoops_HCHSR*/
		/* _hoops_SRHR _hoops_IS _hoops_RH _hoops_SHPR _hoops_AGIR _hoops_RGR _hoops_HGRH _hoops_GACC*/
		/* _hoops_IIAH _hoops_IH _hoops_RHAR _hoops_AGIR _hoops_PPSCP _hoops_IRPCI _hoops_GSPSI*/
		/* _hoops_HIH _hoops_HRGR _hoops_HAR _hoops_SCGR _hoops_IHGS _hoops_IGI*/

		_hoops_HCPSI = GetDeviceCaps (state->_hoops_PRICI, HORZRES);
		_hoops_ICPSI = GetDeviceCaps (state->_hoops_PRICI, VERTRES);

		_hoops_CCPSI = nr->_hoops_SRA->_hoops_PGCC._hoops_PRPSR.x;
		_hoops_SCPSI = nr->_hoops_SRA->_hoops_PGCC._hoops_PRPSR.y;

		scale=_hoops_AHIA((float)_hoops_HCPSI/_hoops_CCPSI,(float)_hoops_ICPSI/_hoops_SCPSI);

		if (_hoops_HCPSI > _hoops_ICPSI) {
			_hoops_PCPSI = _hoops_ICPSI;
			_hoops_ACPSI = (int)(((double)(_hoops_CCPSI*_hoops_PCPSI))/(double)_hoops_SCPSI);
		}
		else {
			_hoops_ACPSI = _hoops_HCPSI;
			_hoops_PCPSI = (int)(((double)(_hoops_SCPSI*_hoops_ACPSI))/(double)_hoops_CCPSI);
		}

		_hoops_GCPSI = (int)(((float)(_hoops_HCPSI - _hoops_ACPSI)/2.0f)+0.5f);
		_hoops_RCPSI = (int)(((float)(_hoops_ICPSI - _hoops_PCPSI)/2.0f)+0.5f);

		/*_hoops_RH _hoops_RSPSI _hoops_HRGR _hoops_IRS _hoops_RSCA*/
		/*_hoops_CPHS _hoops_GHAAI _hoops_SCH _hoops_HHS _hoops_SAHR _hoops_SHH _hoops_RH _hoops_ASPSI _hoops_SRGAI _hoops_RHPP*/
#ifndef _WIN32_WCE
		StretchDIBits (state->_hoops_HRICI,
					_hoops_GCPSI+(int)((float)scale*(float)_hoops_HHPSI),
					_hoops_RCPSI+(int)((float)scale*(float)_hoops_IHPSI),
						(int)((float)scale*(float)width+0.5f),
						(int)((float)scale*(float)height+0.5f),
						 0, 0, width, height,
						(LPVOID)_hoops_GIPSI, _hoops_RIPSI,
						DIB_RGB_COLORS, SRCCOPY);
#endif
	}
	else {
		/* _hoops_ARI _hoops_SR _hoops_RRP _hoops_IS _hoops_IRPCI _hoops_CRPCI _hoops_IH _hoops_SRGAI _hoops_PSPSI _hoops_IS _hoops_IPHR*/
		/* _hoops_PPR _hoops_IH _hoops_RH _hoops_CHACI */
#ifndef _WIN32_WCE
			StretchDIBits (state->_hoops_AGICI, _hoops_HHPSI, _hoops_IHPSI,
							width, height, 0, 0, width, height,
							(LPVOID)_hoops_GIPSI, _hoops_RIPSI,
							DIB_RGB_COLORS, SRCCOPY);
#endif
	}

	if (state->_hoops_HPCCI != _hoops_GIPSI)
		FREE_ARRAY(_hoops_GIPSI, _hoops_SHPSI, unsigned char);
}


/*
 * _hoops_PGAA
 */
local int _hoops_HSPSI (
	int		x,
	int		y,
	int		size) {
	int		d;

	d = 0;
	while (size-- > 0) {
		d = (d<<1 | (x&1 ^ y&1))<<1 | y&1;
		x >>= 1;
		y >>= 1;
	}
	return d;
}


/*
 * _hoops_PGAA
 */
local void _hoops_ISPSI (
	Net_Rendition const & nr) {
	MSW_Driver_State alter				*state =
					_hoops_IICCI ();
	int								size;
	int								_hoops_RPIS;
	int								l, i;

	size  = 3;
	state->_hoops_PACCI  = 8; /* 2 _hoops_IS _hoops_RH _hoops_RIIR _hoops_IIGR "_hoops_IGIR" */
	_hoops_RPIS = state->_hoops_IACCI = 256;

	l = (1 << size);
	_hoops_RPIS = _hoops_RPIS / (l * l);
	for (i = 0; i < l * l; i++) {
		state->_hoops_HACCI[i] = _hoops_RPIS * _hoops_HSPSI (i/l, i % l, size);
	}
}


/*
 * _hoops_PGAA
 */
local int _hoops_CSPSI (
	Net_Rendition const & nr,
	int								x,
	int								y,
	int								level) {
	MSW_Driver_State alter				*state =
					_hoops_IICCI ();
	int								size;

	if (!state->_hoops_AACCI) {
		_hoops_ISPSI (nr);
		state->_hoops_AACCI = true;
	}

	size = state->_hoops_PACCI;
	if (level > state->_hoops_HACCI[(x % size) + size*(y % size)])
		return 0;
	else
		return 1;
}

/*
 * _hoops_SRAC
 */
local void _hoops_SSPSI (
	Net_Rendition const & nr,
	DC_Point const				*start,
	DC_Point const				*end,
	int								row_bytes,
	RGBAS32 const				*rasters) {
	MSW_Driver_State alter				*state =
					_hoops_IICCI ();
	int								width = (int) (end->x - start->x) + 1;
	int								height = (int) (start->y - end->y) + 1;
	int								x = (int)start->x;
	int								y = state->yfudge - (int)start->y;
	HBITMAP							_hoops_GGHSI;
	HBITMAP							_hoops_CSHCI;
	/*_hoops_SPRS		_hoops_RGRRR							_hoops_RGHSI = _hoops_IGAA * _hoops_APPS;*/
	BITMAPINFO						*_hoops_AGHSI;
	unsigned char					*_hoops_GIPSI = null;
	int								_hoops_CHPSI;
	int								_hoops_PGHSI;
	int								_hoops_SHPSI;
	int								_hoops_HGHSI;
	int								_hoops_HPAIP = x;
	int								_hoops_IPAIP = y;
	char							*_hoops_IGHSI;


	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	ALLOC_ARRAY(_hoops_IGHSI, (sizeof (BITMAPINFO) + sizeof (RGBQUAD)), char);
	_hoops_AGHSI=(BITMAPINFO*) _hoops_IGHSI;

	_hoops_AGHSI->bmiHeader.biSize			= sizeof (BITMAPINFOHEADER);
	_hoops_AGHSI->bmiHeader.biWidth			= width;
	_hoops_AGHSI->bmiHeader.biHeight			= height;
	_hoops_AGHSI->bmiHeader.biPlanes			= 1;
	_hoops_AGHSI->bmiHeader.biBitCount		= 1;
	_hoops_AGHSI->bmiHeader.biCompression		= 0;
	_hoops_AGHSI->bmiHeader.biSizeImage		= 0;
	_hoops_AGHSI->bmiHeader.biXPelsPerMeter	= state->_hoops_PIICI;
	_hoops_AGHSI->bmiHeader.biYPelsPerMeter	= state->_hoops_HIICI;
	_hoops_AGHSI->bmiHeader.biClrUsed			= 0;
	_hoops_AGHSI->bmiHeader.biClrImportant	= 0;
	(_hoops_AGHSI->bmiColors)->rgbBlue		= 1;
	(_hoops_AGHSI->bmiColors)->rgbGreen		= 1;
	(_hoops_AGHSI->bmiColors)->rgbRed			= 1;
	(_hoops_AGHSI->bmiColors)->rgbReserved	= 0;
	(_hoops_AGHSI->bmiColors+1)->rgbBlue		= 0;
	(_hoops_AGHSI->bmiColors+1)->rgbGreen		= 0;
	(_hoops_AGHSI->bmiColors+1)->rgbRed		= 0;
	(_hoops_AGHSI->bmiColors+1)->rgbReserved	= 0;


	/*
	 * _hoops_CGP _hoops_IIH _hoops_HRGR _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_CGHSI _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_IIH _hoops_HRGR _hoops_IRS
	 * _hoops_GGHS _hoops_ARPC.  _hoops_PGPR _hoops_HPPCI _hoops_PAH _hoops_PIIA _hoops_RH _hoops_AGR _hoops_IIGR _hoops_ASCA.
	 * _hoops_CSH _hoops_CSPP _hoops_IIGR _hoops_PSCSR _hoops_GAHGH _hoops_GRAA-_hoops_PGHGI _hoops_RGCGA _hoops_GSRSA.
	 */
	_hoops_HGHSI = (width + 7)/8;
	_hoops_CHPSI  = (_hoops_HGHSI + 3) & (~0x0003);
	_hoops_PGHSI = _hoops_CHPSI;
	_hoops_SHPSI  = _hoops_PGHSI * height;

	/* _hoops_HHCS _hoops_IGGAR _hoops_RAPR _hoops_IH _hoops_RH _hoops_RSIR _hoops_CSCR _hoops_HPGR _hoops_ARR */
	TRY_ALLOC_ARRAY(_hoops_GIPSI, _hoops_SHPSI, unsigned char);

	if (_hoops_GIPSI != null) {
		/* _hoops_PS _hoops_PAH _hoops_AA _hoops_RH _hoops_RSIR _hoops_CSCR _hoops_HPGR _hoops_ARR */
		unsigned char	*_hoops_AIPSI = _hoops_GIPSI;
		int				_hoops_SGHSI = height;

		_hoops_AGHSI->bmiHeader.biWidth	  = width;
		_hoops_AGHSI->bmiHeader.biHeight	  = height;
		_hoops_AGHSI->bmiHeader.biSizeImage = 0;

		_hoops_AIPSI = _hoops_GIPSI + _hoops_SHPSI;
		_hoops_RGGA (_hoops_SGHSI-- == 0) {
			unsigned char alter *pp;
			unsigned char const *pe;
			RGBAS32	  const *_hoops_PIPSI;
			int					level;
			int					_hoops_GRHSI = 0;

			_hoops_AIPSI -= _hoops_PGHSI;
			pp = (unsigned char alter *) _hoops_AIPSI;
			pe = (unsigned char const *)(_hoops_AIPSI + _hoops_CHPSI);
			_hoops_PIPSI = rasters;
			do {
				unsigned char	byte;
				int				k;
				byte = 0;
				k = 0;
				while ((k < 8) && (_hoops_GRHSI++ < width)) {
					level = (int) (0.299f*_hoops_PIPSI->r +
								   0.587f*_hoops_PIPSI->g +
								   0.114f*_hoops_PIPSI->b);
					byte |= _hoops_CSPSI (nr, _hoops_HPAIP++, _hoops_IPAIP, level) << (7 - k++);
					_hoops_PIPSI++;
				}
				*pp++ = byte;
			} _hoops_RGGA (pp == pe);
			rasters = (RGBAS32 *)((unsigned char alter *)rasters + row_bytes);
			_hoops_IPAIP++;
			_hoops_HPAIP = x;
		}

		if (state->_hoops_SRRRR) {
			_hoops_GGHSI =
				CreateCompatibleBitmap (state->_hoops_AGICI, width, height);
#ifndef _WIN32_WCE
			SetDIBits (state->_hoops_AGICI, _hoops_GGHSI, 0, height,
				(LPVOID)_hoops_GIPSI, _hoops_AGHSI,
				DIB_PAL_COLORS);
#endif
			_hoops_CSHCI = (HBITMAP) SelectObject (state->_hoops_SGICI,
				_hoops_GGHSI);
			BitBlt (state->_hoops_AGICI, x, y, width, height,
				state->_hoops_SGICI, 0, 0, SRCCOPY);
			SelectObject (state->_hoops_SGICI, _hoops_CSHCI);

			DeleteObject (_hoops_GGHSI);
		}
		else {
#ifndef _WIN32_WCE
			SetDIBitsToDevice (state->_hoops_AGICI, x, y,
				width, height, 0, 0, 0, height,
				(LPVOID)_hoops_GIPSI, _hoops_AGHSI,
				DIB_PAL_COLORS);
#endif
		}
		FREE_ARRAY(_hoops_GIPSI, _hoops_SHPSI, char);
	}
	else {
		/* _hoops_PS _hoops_HS _hoops_IS _hoops_IIPR _hoops_SCH _hoops_SPR _hoops_III _hoops_HPGR _hoops_IRS _hoops_GHIR */
		_hoops_SHPSI = _hoops_PGHSI;
		TRY_ALLOC_ARRAY(_hoops_GIPSI, _hoops_SHPSI, unsigned char);
		if (_hoops_GIPSI == null) {
			HE_ERROR (HEC_MEMORY, HES_ALLOCATE_MEMORY_FAILED,
					  "Unable to allocate memory for a single scan line");
		}
		_hoops_AGHSI->bmiHeader.biWidth	  = width;
		_hoops_AGHSI->bmiHeader.biHeight	  = 1;
		_hoops_AGHSI->bmiHeader.biSizeImage = 0;

		if (_hoops_GIPSI != null) {
			int						_hoops_SGHSI = height;
			unsigned char			*_hoops_AIPSI = _hoops_GIPSI;
			unsigned char alter		*pp;
			unsigned char const		*pe;
			RGBAS32	  const		*_hoops_PIPSI;

			if (state->_hoops_SRRRR) {
				_hoops_GGHSI =
					CreateCompatibleBitmap (state->_hoops_AGICI, width, 1);

				_hoops_RGGA (_hoops_SGHSI-- == 0) {
					int						level;
					int						_hoops_GRHSI = 0;

					pp = (unsigned char alter *) _hoops_AIPSI;
					pe = (unsigned char const *)(_hoops_AIPSI + _hoops_CHPSI);
					_hoops_PIPSI = rasters;
					do {
						unsigned char	byte;
						int				k;
						byte = k = 0;
						while ((k < 8) && (_hoops_GRHSI++ < width)) {
							level = (int) (0.299f*_hoops_PIPSI->r +
										   0.587f*_hoops_PIPSI->g +
										   0.114f*_hoops_PIPSI->b);
							byte |= _hoops_CSPSI (nr, _hoops_HPAIP++, _hoops_IPAIP, level) << (7 - k++);
							_hoops_PIPSI++;
						}
						*pp++ = byte;
					} _hoops_RGGA (pp == pe);
					rasters = (RGBAS32 *)((unsigned char alter *)rasters +
										   row_bytes);
					_hoops_HPAIP = x;
					_hoops_IPAIP++;
#ifndef _WIN32_WCE
					SetDIBits (state->_hoops_AGICI, _hoops_GGHSI, 0, 1,
							 (LPVOID)_hoops_GIPSI, state->_hoops_APICI, DIB_PAL_COLORS);
#endif
					_hoops_CSHCI =
						(HBITMAP) SelectObject (state->_hoops_SGICI,
												_hoops_GGHSI);
					BitBlt (state->_hoops_AGICI, x, y, width, 1,
							state->_hoops_SGICI, 0, 0, SRCCOPY);
					SelectObject (state->_hoops_SGICI, _hoops_CSHCI);
					++y;
				}

				DeleteObject (_hoops_GGHSI);
			}
			else {
				_hoops_RGGA (_hoops_SGHSI-- == 0) {
					int						level;
					int						_hoops_GRHSI = 0;

					pp = (unsigned char alter *) _hoops_AIPSI;
					pe = (unsigned char const *)(_hoops_AIPSI + _hoops_CHPSI);
					_hoops_PIPSI = rasters;
					do {
						unsigned char	byte;
						int				k;

						byte = k = 0;
						while ((k < 8) && (_hoops_GRHSI++ < width)) {
							level = (int) (0.299f*_hoops_PIPSI->r +
										   0.587f*_hoops_PIPSI->g +
										   0.114f*_hoops_PIPSI->b);
							byte |= _hoops_CSPSI (nr, _hoops_HPAIP++, _hoops_IPAIP, level) << (7 - k++);
							_hoops_PIPSI++;
						}
						*pp++ = byte;
					} _hoops_RGGA (pp == pe);
					rasters = (RGBAS32 *)((unsigned char alter *)rasters +
										   row_bytes);
					_hoops_HPAIP = x;
					_hoops_IPAIP++;
#ifndef _WIN32_WCE
					SetDIBitsToDevice (state->_hoops_AGICI, x, y,
									width, 1, 0, 0, 0, 1,
									(LPVOID)_hoops_GIPSI,
									_hoops_AGHSI,
									DIB_PAL_COLORS);
#endif
					++y;
				}
			}
		}
		FREE_ARRAY(_hoops_GIPSI, _hoops_SHPSI, char);
	}
	FREE_ARRAY(_hoops_AGHSI,(sizeof(BITMAPINFO)+sizeof(RGBQUAD)), char);
}


/*
 * _hoops_SRAC
 */
local void _hoops_RRHSI (
	Net_Rendition const & nr,
	DC_Point const		*start,
	DC_Point const		*end,
	Image const			*image,
	int						hoffset,
	int						voffset,
	void const				*_hoops_PISCP) {
	MSW_Driver_State alter		*state = _hoops_IICCI ();
	int						width = (int) (end->x - start->x) + 1;
	int						height = (int) (start->y - end->y) + 1;
	int						x = (int) start->x;
	int						y = state->yfudge - (int)(start->y);
	_hoops_RGHCI				*_hoops_ARHSI = (_hoops_RGHCI *) _hoops_PISCP;
#ifdef _WIN32_WCE
		unsigned char *_hoops_PRHSI;
		unsigned char *src;
		unsigned char *_hoops_HRGSP;
		int i,_hoops_HRHSI;
		int xx,yy;
#endif


	if (_hoops_PISCP == null)
		/* _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_CARS */
		HD_Std_Display_Frame_Buffer (nr, start, end, image, hoffset,
			voffset, _hoops_PISCP);
	else {

		draw_and_reset_poly_cache(state, true);

		SelectClipRgn (state->_hoops_AGICI, NULL);
		_hoops_SHGSI (state);

#ifdef _WIN32_WCE
		_hoops_HRHSI = state->_hoops_APICI->bmiHeader.biWidth * state->_hoops_APICI->bmiHeader.biHeight;
		src = _hoops_ARHSI->_hoops_RCHA;
		_hoops_HRGSP = _hoops_ARHSI->_hoops_PGHCI;

		for (yy=0;yy<state->_hoops_APICI->bmiHeader.biHeight;yy++)
		{
				_hoops_PRHSI = &src[(state->_hoops_APICI->bmiHeader.biWidth*(state->_hoops_APICI->bmiHeader.biHeight-yy-1))*4];
		for (xx=0;xx<state->_hoops_APICI->bmiHeader.biWidth;xx++)
		{
				*_hoops_HRGSP = *_hoops_PRHSI;
				_hoops_PRHSI++;
				_hoops_HRGSP++;
				*_hoops_HRGSP = *_hoops_PRHSI;
				_hoops_PRHSI++;
				_hoops_HRGSP++;
				*_hoops_HRGSP = *_hoops_PRHSI;
				_hoops_PRHSI++;
				_hoops_HRGSP++;
				_hoops_PRHSI++;
		}
		}

		BitBlt (state->_hoops_AGICI,										//_hoops_IRHSI
				x,
				y,
				width,
				height,
				_hoops_ARHSI->dc,
				hoffset,
				voffset,
				SRCCOPY);
	}

#else
		/* _hoops_AGGA _hoops_IPS _hoops_RH _hoops_CRHSI _hoops_IS _hoops_RH _hoops_SHPR */
		BitBlt (state->_hoops_AGICI,
				x,
				y,
				width,
				height,
				_hoops_ARHSI->dc,
				hoffset,
				voffset,
				SRCCOPY);
	}
#endif

	/*
	 * _hoops_HAIA _hoops_SRHSI _hoops_APAC _hoops_AA _hoops_AHGCI _hoops_ACRAA _hoops_IIGR _hoops_RGR _hoops_SRHR -
	 * _hoops_SR _hoops_GRS _hoops_SHH _hoops_RIGRP _hoops_SCH _hoops_ARPP _hoops_HHH _hoops_APAC _hoops_GRS _hoops_ACRAA
	 * _hoops_HIS _hoops_HHSA _hoops_IRS _hoops_RGAS _hoops_ACRAA
	 */
#ifndef _WIN32_WCE
	GdiFlush ();
#endif

}


/*
 * _hoops_SRAC
 */
local void _hoops_GAHSI (
	Net_Rendition const & nr,
	DC_Point const			*start,
	DC_Point const			*end,
	int							row_bytes,
	unsigned char const			*rasters) {
	MSW_Driver_State alter			*state = _hoops_IICCI ();
	int							width = (int) (end->x - start->x) + 1;
	int							height = (int) (start->y - end->y) + 1;
	int							x = (int) start->x;
	int							y = state->yfudge - (int)(start->y);
	LPBITMAPINFOHEADER			_hoops_GGHPR = &state->_hoops_APICI->bmiHeader;
	HBITMAP						_hoops_GGHSI;
	HBITMAP						_hoops_CSHCI;
	unsigned char alter			*_hoops_GIPSI = null;
	int							_hoops_CHPSI;

	if (row_bytes == 0)
		row_bytes = width;


	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	_hoops_GGHPR->biBitCount = 8;
	/*
	 * _hoops_CGP _hoops_IIH _hoops_HRGR _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_CGHSI _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_IIH _hoops_HRGR _hoops_IRS
	 * _hoops_GGHS _hoops_ARPC.  _hoops_PGPR _hoops_HPPCI _hoops_PAH _hoops_PIIA _hoops_RH _hoops_AGR _hoops_IIGR _hoops_ASCA.
	 * _hoops_CSH _hoops_CSPP _hoops_IIGR _hoops_PSCSR _hoops_GAHGH _hoops_GRAA-_hoops_PGHGI _hoops_RGCGA _hoops_GSRSA.
	 */
	if (height > 1) {
		/*
		 * _hoops_IPCP _hoops_AASSA _hoops_IIGR _hoops_RH _hoops_AHRH _hoops_RHAP _hoops_HAR _hoops_AHGS _hoops_IS _hoops_SHH _hoops_CRSH
		 * _hoops_IH _hoops_CHACI.  _hoops_RAHSI _hoops_SCH _hoops_IS _hoops_PHHR _hoops_RHIR _hoops_RH _hoops_RRGR _hoops_SGS
		 * _hoops_AAHSI _hoops_RH _hoops_AHRH _hoops_IH _hoops_CHACI & _hoops_ISHHH.
		 */
		if (ANYBIT (row_bytes, 0x03) || state->_hoops_SSRRI < _hoops_SHRCI ||
				   (state->_hoops_PIGRR != _hoops_HSPCI)) {

			_hoops_CHPSI = ((width + 3) & (~0x0003));

			TRY_ALLOC_ARRAY(_hoops_GIPSI, _hoops_CHPSI * height, unsigned char);

			if (_hoops_GIPSI != null) {
				unsigned char alter		*_hoops_AIPSI = _hoops_GIPSI;
				int						_hoops_SGHSI = height;

				_hoops_GGHPR->biWidth		= _hoops_CHPSI;
				_hoops_GGHPR->biHeight	= height;
				_hoops_GGHPR->biSizeImage = _hoops_CHPSI * height;

				_hoops_AIPSI = _hoops_GIPSI + _hoops_GGHPR->biSizeImage;
				_hoops_RGGA (_hoops_SGHSI-- == 0) {
					_hoops_AIPSI -= _hoops_CHPSI;
					COPY_MEMORY (rasters, width, _hoops_AIPSI);
					rasters += row_bytes;
				}
			}
			else {
				_hoops_GGHPR->biWidth		= row_bytes;
				_hoops_GGHPR->biHeight	= 1;
				_hoops_GGHPR->biSizeImage = width;
			}
		}
		else {
			/*
			 * _hoops_HGI _hoops_RIS _hoops_CGH _hoops_SHH _hoops_AIARR _hoops_RGAR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_SGGHA _hoops_HPPCI
			 */

			_hoops_GGHPR->biWidth		=  row_bytes;
			_hoops_GGHPR->biHeight	= -height;
			_hoops_GGHPR->biSizeImage =  width * height;

			_hoops_CHPSI = width;
			_hoops_GIPSI = (unsigned char alter *)rasters;
		}
	}
	else {
		_hoops_GGHPR->biWidth		= width;
		_hoops_GGHPR->biHeight	= height; /* 1 */
		_hoops_GGHPR->biSizeImage = width;

		_hoops_CHPSI = width;
		_hoops_GIPSI = (unsigned char alter *)rasters;
	}

	if (_hoops_GIPSI != null) {
		if (state->_hoops_SRRRR) {
			_hoops_GGHSI =
				CreateCompatibleBitmap (state->_hoops_AGICI, _hoops_CHPSI, height);
#ifndef _WIN32_WCE
			SetDIBits (state->_hoops_AGICI, _hoops_GGHSI, 0, height,
					   (LPVOID)_hoops_GIPSI, state->_hoops_APICI, DIB_PAL_COLORS);
#endif
			_hoops_CSHCI = (HBITMAP)
				SelectObject (state->_hoops_SGICI, _hoops_GGHSI);
			BitBlt (state->_hoops_AGICI, x, y, _hoops_CHPSI, height,
					state->_hoops_SGICI, 0, 0, SRCCOPY);
			SelectObject (state->_hoops_SGICI, _hoops_CSHCI);

			DeleteObject (_hoops_GGHSI);
		}
		else {
#ifndef _WIN32_WCE
			SetDIBitsToDevice (state->_hoops_AGICI, x, y,
							   _hoops_CHPSI, height, 0, 0, 0, height,
							   (LPVOID)_hoops_GIPSI,
							   state->_hoops_APICI,
							   DIB_PAL_COLORS);
#endif
		}

		if (_hoops_GIPSI != (unsigned char alter *)rasters)
			FREE_ARRAY(_hoops_GIPSI, _hoops_CHPSI*height, char);
	}
	else {
		if (state->_hoops_SRRRR) {
			_hoops_GGHSI =
				CreateCompatibleBitmap (state->_hoops_AGICI, width, 1);

			_hoops_RGGA (height-- == 0) {
#ifndef _WIN32_WCE
				SetDIBits (state->_hoops_AGICI, _hoops_GGHSI, 0, 1,
						   (LPVOID)rasters, state->_hoops_APICI, DIB_PAL_COLORS);
#endif
				_hoops_CSHCI = (HBITMAP) SelectObject (state->_hoops_SGICI,
													   _hoops_GGHSI);
				BitBlt (state->_hoops_AGICI, x, y, width, 1,
						state->_hoops_SGICI, 0, 0, SRCCOPY);
				SelectObject (state->_hoops_SGICI, _hoops_CSHCI);
				++y;
				rasters += width;
			}

			DeleteObject (_hoops_GGHSI);
		}
		else {
			_hoops_RGGA (height-- == 0) {
#ifndef _WIN32_WCE
				SetDIBitsToDevice (state->_hoops_AGICI, x, y,
								   width, 1, 0, 0, 0, 1,
								   (LPVOID)rasters, state->_hoops_APICI,
								   DIB_PAL_COLORS);
#endif
				++y;
				rasters += width;
			}
		}
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_PAHSI (
	Net_Rendition const & nr,
	DC_Point const			*start,
	DC_Point const			*end,
	int							row_bytes,
	unsigned char const			*rasters) {
	MSW_Driver_State alter			*state = _hoops_IICCI ();
	int							width = (int) (end->x - start->x) + 1;
	int							height = (int) (start->y - end->y) + 1;
	int							x = (int) start->x;
	int							y = state->yfudge - (int)(start->y);
	LPBITMAPINFOHEADER			_hoops_GGHPR = &state->_hoops_APICI->bmiHeader;
	HBITMAP						_hoops_GGHSI;
	HBITMAP						_hoops_CSHCI;
	unsigned char alter			*_hoops_GIPSI = null;
	int							_hoops_CHPSI;

	if (row_bytes == 0)
	   row_bytes = width;

	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	_hoops_GGHPR->biBitCount = 8;
	/*
	 * _hoops_CGP _hoops_IIH _hoops_HRGR _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_CGHSI _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_IIH _hoops_HRGR _hoops_IRS
	 * _hoops_GGHS _hoops_ARPC.  _hoops_PGPR _hoops_HPPCI _hoops_PAH _hoops_PIIA _hoops_RH _hoops_AGR _hoops_IIGR _hoops_ASCA.
	 * _hoops_CSH _hoops_CSPP _hoops_IIGR _hoops_PSCSR _hoops_GAHGH _hoops_GRAA-_hoops_PGHGI _hoops_RGCGA _hoops_GSRSA.
	 */
	if (height > 1) {
		/*
		 * _hoops_IPCP _hoops_AASSA _hoops_IIGR _hoops_RH _hoops_AHRH _hoops_RHAP _hoops_HAR _hoops_AHGS _hoops_IS _hoops_SHH _hoops_CRSH
		 * _hoops_IH _hoops_CHACI.  _hoops_RAHSI _hoops_SCH _hoops_IS _hoops_PHHR _hoops_RHIR _hoops_RH _hoops_RRGR _hoops_SGS
		 * _hoops_AAHSI _hoops_RH _hoops_AHRH _hoops_IH _hoops_CHACI & _hoops_ISHHH.
		 */
		if (ANYBIT (row_bytes, 0x03) || state->_hoops_SSRRI < _hoops_SHRCI ||
				   (state->_hoops_PIGRR != _hoops_HSPCI)) {

			_hoops_CHPSI = ((width + 3) & (~0x0003));

			TRY_ALLOC_ARRAY(_hoops_GIPSI, _hoops_CHPSI * height, unsigned char);

			if (_hoops_GIPSI != null) {
				unsigned char alter		*_hoops_AIPSI = _hoops_GIPSI;
				int						_hoops_SGHSI = height;

				_hoops_GGHPR->biWidth		= _hoops_CHPSI;
				_hoops_GGHPR->biHeight	= height;
				_hoops_GGHPR->biSizeImage = _hoops_CHPSI * height;

				_hoops_AIPSI = _hoops_GIPSI + _hoops_GGHPR->biSizeImage;
				_hoops_RGGA (_hoops_SGHSI-- == 0) {
					_hoops_AIPSI -= _hoops_CHPSI;
					COPY_MEMORY (rasters, width, _hoops_AIPSI);
					rasters += row_bytes;
				}
			}
			else {
				_hoops_GGHPR->biWidth		= row_bytes;
				_hoops_GGHPR->biHeight	= 1;
				_hoops_GGHPR->biSizeImage = width;
			}
		}
		else {
			/*
			 * _hoops_HGI _hoops_RIS _hoops_CGH _hoops_SHH _hoops_AIARR _hoops_RGAR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_SGGHA _hoops_HPPCI
			 */

			_hoops_GGHPR->biWidth		=  row_bytes;
			_hoops_GGHPR->biHeight	= -height;
			_hoops_GGHPR->biSizeImage =  width * height;

			_hoops_CHPSI = width;
			_hoops_GIPSI = (unsigned char alter *)rasters;
		}
	}
	else {
		_hoops_GGHPR->biWidth		= width;
		_hoops_GGHPR->biHeight	= height; /* 1 */
		_hoops_GGHPR->biSizeImage = width;

		_hoops_CHPSI = width;
		_hoops_GIPSI = (unsigned char alter *)rasters;
	}

	if (_hoops_GIPSI != null) {
		if (state->_hoops_SRRRR) {
			_hoops_GGHSI =
				CreateCompatibleBitmap (state->_hoops_AGICI, _hoops_CHPSI, height);
#ifndef _WIN32_WCE
			SetDIBits (state->_hoops_AGICI, _hoops_GGHSI, 0, height,
					   (LPVOID)_hoops_GIPSI, state->_hoops_APICI, DIB_PAL_COLORS);
#endif
			_hoops_CSHCI = (HBITMAP)
				SelectObject (state->_hoops_SGICI, _hoops_GGHSI);
			BitBlt (state->_hoops_AGICI, x, y, _hoops_CHPSI, height,
					state->_hoops_SGICI, 0, 0, SRCCOPY);
			SelectObject (state->_hoops_SGICI, _hoops_CSHCI);

			DeleteObject (_hoops_GGHSI);
		}
		else {
			if (state->_hoops_IRICI) {
				int			_hoops_GCPSI, _hoops_RCPSI;
				int			_hoops_ACPSI, _hoops_PCPSI;
				int			_hoops_HCPSI, _hoops_ICPSI;

				_hoops_HCPSI = GetDeviceCaps (state->_hoops_PRICI, HORZRES);
				_hoops_ICPSI = GetDeviceCaps (state->_hoops_PRICI, VERTRES);

				if (_hoops_HCPSI > _hoops_ICPSI) {
					_hoops_PCPSI = _hoops_ICPSI;
					_hoops_ACPSI = (int)(((double)(_hoops_CHPSI*_hoops_PCPSI))/(double)height);
				}
				else {
					_hoops_ACPSI = _hoops_HCPSI;
					_hoops_PCPSI = (int)(((double)(height*_hoops_ACPSI))/(double)_hoops_CHPSI);
				}

				_hoops_GCPSI = (_hoops_HCPSI - _hoops_ACPSI)/2;
				_hoops_RCPSI = (_hoops_ICPSI - _hoops_PCPSI)/2;
#ifndef _WIN32_WCE
				SetStretchBltMode (state->_hoops_HRICI, COLORONCOLOR);

				StretchDIBits (state->_hoops_HRICI, _hoops_GCPSI, _hoops_RCPSI,
								_hoops_ACPSI, _hoops_PCPSI, 0, 0, _hoops_CHPSI, height,
								(LPVOID)_hoops_GIPSI, state->_hoops_APICI, DIB_PAL_COLORS,
								SRCCOPY);
#endif
			}
			else if (state->_hoops_PIGRR == _hoops_PSPCI) {

#ifndef _WIN32_WCE
				SetStretchBltMode (state->_hoops_AGICI, COLORONCOLOR);

				StretchDIBits (state->_hoops_AGICI, x, y,
					_hoops_CHPSI, height, 0, 0, _hoops_CHPSI, height,
					(LPVOID)_hoops_GIPSI, state->_hoops_APICI, DIB_PAL_COLORS,
					SRCCOPY);
#endif
			}
			else {
#ifndef _WIN32_WCE
				SetDIBitsToDevice (state->_hoops_AGICI, x, y,
					_hoops_CHPSI, height, 0, 0, 0, height,
					(LPVOID)_hoops_GIPSI,
					state->_hoops_APICI,
					DIB_PAL_COLORS);
#endif
			}
		}

		if (_hoops_GIPSI != (unsigned char alter *)rasters)
			FREE_ARRAY(_hoops_GIPSI, _hoops_CHPSI*height, char);
	}
	else {
		if (state->_hoops_SRRRR) {
			_hoops_GGHSI =
				CreateCompatibleBitmap (state->_hoops_AGICI, width, 1);

			_hoops_RGGA (height-- == 0) {
#ifndef _WIN32_WCE
				SetDIBits (state->_hoops_AGICI, _hoops_GGHSI, 0, 1,
						   (LPVOID)rasters, state->_hoops_APICI,
						   DIB_PAL_COLORS);
#endif
				_hoops_CSHCI = (HBITMAP) SelectObject (state->_hoops_SGICI,
											 _hoops_GGHSI);
				BitBlt (state->_hoops_AGICI, x, y, width, 1,
						state->_hoops_SGICI, 0, 0, SRCCOPY);
				SelectObject (state->_hoops_SGICI, _hoops_CSHCI);
				++y;
				rasters += width;
			}

			DeleteObject (_hoops_GGHSI);
		}
		else {
			_hoops_RGGA (height-- == 0) {
				/*
				 * _hoops_HAHSI _hoops_IH _hoops_RSRA _hoops_AHRH _hoops_ASSP'_hoops_RA _hoops_IRHH
				 * _hoops_GSGS _hoops_CSSP.
				 */
#ifndef _WIN32_WCE
				if (state->_hoops_IRICI) {
					SetDIBitsToDevice (state->_hoops_HRICI, x, y,
									   width, 1, 0, 0, 0, 1,
									   (LPVOID)rasters, state->_hoops_APICI,
									   DIB_PAL_COLORS);
				}
				else {
					SetDIBitsToDevice (state->_hoops_AGICI, x, y,
									   width, 1, 0, 0, 0, 1,
									   (LPVOID)rasters, state->_hoops_APICI,
									   DIB_PAL_COLORS);
				}
#endif
				++y;
				rasters += width;
			}
		}
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_IAHSI (
	Net_Rendition const & nr,
	DC_Point const			*start,
	DC_Point const			*end,
	int							row_bytes,
	unsigned char const			*rasters) {
	MSW_Driver_State alter			*state = _hoops_IICCI ();
	int							width = (int) (end->x - start->x) + 1;
	int							height = (int) (start->y - end->y) + 1;
	int							x = (int) start->x;
	int							y = state->yfudge - (int)(start->y);
	LPBITMAPINFOHEADER			_hoops_GGHPR = &state->_hoops_APICI->bmiHeader;
	HBITMAP						_hoops_GGHSI;
	HBITMAP						_hoops_CSHCI;
	unsigned char alter			*_hoops_GIPSI = null;
	int							_hoops_CHPSI;

	if (row_bytes == 0)
		row_bytes = width;


	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);


	_hoops_GGHPR->biBitCount = 8;
	/*
	 * _hoops_CGP _hoops_IIH _hoops_HRGR _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_CGHSI _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_IIH _hoops_HRGR _hoops_IRS
	 * _hoops_GGHS _hoops_ARPC.  _hoops_PGPR _hoops_HPPCI _hoops_PAH _hoops_PIIA _hoops_RH _hoops_AGR _hoops_IIGR _hoops_ASCA.
	 * _hoops_CSH _hoops_CSPP _hoops_IIGR _hoops_PSCSR _hoops_GAHGH _hoops_GRAA-_hoops_PGHGI _hoops_RGCGA _hoops_GSRSA.
	 */
	if (height > 1) {

		/*
		 * _hoops_IPCP _hoops_AASSA _hoops_IIGR _hoops_RH _hoops_AHRH _hoops_RHAP _hoops_HAR _hoops_AHGS _hoops_IS _hoops_SHH _hoops_CRSH
		 * _hoops_IH _hoops_CHACI.  _hoops_RAHSI _hoops_SCH _hoops_IS _hoops_PHHR _hoops_RHIR _hoops_RH _hoops_RRGR _hoops_SGS
		 * _hoops_AAHSI _hoops_RH _hoops_AHRH _hoops_IH _hoops_CHACI & _hoops_ISHHH.
		 */
		if (ANYBIT (row_bytes, 0x03) || state->_hoops_SSRRI < _hoops_SHRCI ||
				   (state->_hoops_PIGRR != _hoops_HSPCI)) {

			_hoops_CHPSI = ((width + 3) & (~0x0003));

			TRY_ALLOC_ARRAY(_hoops_GIPSI, _hoops_CHPSI * height, unsigned char);

			if (_hoops_GIPSI != null) {
				unsigned char alter		*_hoops_AIPSI = _hoops_GIPSI;
				int						_hoops_SGHSI = height;

				_hoops_GGHPR->biWidth		= _hoops_CHPSI;
				_hoops_GGHPR->biHeight	= height;
				_hoops_GGHPR->biSizeImage = _hoops_CHPSI * height;

				_hoops_AIPSI = _hoops_GIPSI + _hoops_GGHPR->biSizeImage;
				_hoops_RGGA (_hoops_SGHSI-- == 0) {
					_hoops_AIPSI -= _hoops_CHPSI;
					COPY_MEMORY (rasters, width, _hoops_AIPSI);
					rasters += row_bytes;
				}
			}
			else {
				_hoops_GGHPR->biWidth		= row_bytes;
				_hoops_GGHPR->biHeight	= 1;
				_hoops_GGHPR->biSizeImage = width;
			}
		}
		else {
			/*
			 * _hoops_HGI _hoops_RIS _hoops_CGH _hoops_SHH _hoops_AIARR _hoops_RGAR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_SGGHA _hoops_HPPCI
			 */

			_hoops_GGHPR->biWidth		=  row_bytes;
			_hoops_GGHPR->biHeight	= -height;
			_hoops_GGHPR->biSizeImage =  row_bytes * height;

			_hoops_CHPSI = width;
			_hoops_GIPSI = (unsigned char alter *)rasters;
		}
	}
	else {
		_hoops_GGHPR->biWidth		= width;
		_hoops_GGHPR->biHeight	= height; /* 1 */
		_hoops_GGHPR->biSizeImage = width;

		_hoops_CHPSI = width;
		_hoops_GIPSI = (unsigned char alter *)rasters;
	}

	if (_hoops_GIPSI != null) {
		if (state->_hoops_SRRRR) {
			_hoops_GGHSI =
				CreateCompatibleBitmap (state->_hoops_AGICI, _hoops_CHPSI, height);
#ifndef _WIN32_WCE
			SetDIBits (state->_hoops_AGICI, _hoops_GGHSI, 0, height,
					   (LPVOID)_hoops_GIPSI, state->_hoops_APICI, DIB_PAL_COLORS);
#endif
			_hoops_CSHCI = (HBITMAP)
				SelectObject (state->_hoops_SGICI, _hoops_GGHSI);
			BitBlt (state->_hoops_AGICI, x, y, _hoops_CHPSI, height,
					state->_hoops_SGICI, 0, 0, SRCCOPY);
			SelectObject (state->_hoops_SGICI, _hoops_CSHCI);

			DeleteObject (_hoops_GGHSI);
		}
		else {
			char _hoops_IA = false;
			Display_Context const		*dc = nr->_hoops_SRA;
			_hoops_APARR alter &		_hoops_RRCI = (_hoops_APARR alter &) dc->_hoops_ACPGR;

			if (state->_hoops_GGCCI) {
#ifndef _WIN32_WCE
				if (SetDIBitsToDevice (state->_hoops_AGICI, x, y,
								   _hoops_CHPSI, height, 0, 0, 0, height,
								   (LPVOID)_hoops_GIPSI,
								   state->_hoops_APICI,
								   DIB_PAL_COLORS) != 0) {
					_hoops_IA = true;
					_hoops_RRCI->_hoops_CCCSR = _hoops_GAHSI;
				}
#endif
			}
			if (!_hoops_IA) {
#ifndef _WIN32_WCE
				SetDIBitsToDevice (state->_hoops_AGICI, x, y,
								   _hoops_CHPSI, height, 0, 0, 0, height,
								   (LPVOID)_hoops_GIPSI,
								   state->_hoops_APICI,
								   DIB_PAL_COLORS);
#endif

				_hoops_RRCI->_hoops_CCCSR = _hoops_PAHSI;
			}
		}

		if (_hoops_GIPSI != (unsigned char alter *)rasters)
			FREE_ARRAY(_hoops_GIPSI, _hoops_CHPSI*height, char);
	}
	else {
		if (state->_hoops_SRRRR) {
			_hoops_GGHSI =
				CreateCompatibleBitmap (state->_hoops_AGICI, width, 1);

			_hoops_RGGA (height-- == 0) {
#ifndef _WIN32_WCE
				SetDIBits (state->_hoops_AGICI, _hoops_GGHSI, 0, 1,
						   (LPVOID)rasters, state->_hoops_APICI,
						   DIB_PAL_COLORS);
#endif
				_hoops_CSHCI = (HBITMAP) SelectObject (state->_hoops_SGICI,
											 _hoops_GGHSI);
				BitBlt (state->_hoops_AGICI, x, y, width, 1,
						state->_hoops_SGICI, 0, 0, SRCCOPY);
				SelectObject (state->_hoops_SGICI, _hoops_CSHCI);
				++y;
				rasters += row_bytes;
			}

			DeleteObject (_hoops_GGHSI);
		}
		else {
			_hoops_RGGA (height-- == 0) {
#ifndef _WIN32_WCE
				SetDIBitsToDevice (state->_hoops_AGICI, x, y,
								   width, 1, 0, 0, 0, 1,
								   (LPVOID)rasters, state->_hoops_APICI,
								   DIB_PAL_COLORS);
#endif
				++y;
				rasters += row_bytes;
			}
		}
	}
}



/*
 * _hoops_SRAC
 */
local void _hoops_GSCGA (
	Net_Rendition const & nr,
	DC_Point const				*start,
	DC_Point const				*end,
	int								row_bytes,
	unsigned char const				*rasters) {
	MSW_Driver_State alter				*state =
					_hoops_IICCI ();
	int								width = (int) (end->x - start->x) + 1;
	int								height = (int) (start->y - end->y) + 1;
	int								x = (int) start->x;
	int								y = state->yfudge - (int)(start->y);
	LPBITMAPINFOHEADER				_hoops_GGHPR = &state->_hoops_APICI->bmiHeader;
	HBITMAP							_hoops_GGHSI;
	HBITMAP							_hoops_CSHCI;
	/*_hoops_SPRS		_hoops_GAGSI _hoops_RCIC		*_hoops_CSPH = _hoops_SCII->_hoops_GHCSR;*/

	UNREFERENCED(row_bytes);

	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	_hoops_GGHPR->biWidth		= width;
	_hoops_GGHPR->biHeight	= 1;
	_hoops_GGHPR->biSizeImage = width;

	if (state->_hoops_SRRRR) {
		_hoops_GGHSI =
			CreateCompatibleBitmap (state->_hoops_AGICI, width, 1);

		_hoops_RGGA (height-- == 0) {
#ifndef _WIN32_WCE
			SetDIBits (state->_hoops_AGICI, _hoops_GGHSI, 0, 1,
					   (LPVOID)rasters, state->_hoops_APICI,
					   DIB_PAL_COLORS);
#endif
			_hoops_CSHCI = (HBITMAP)
				SelectObject (state->_hoops_SGICI, _hoops_GGHSI);
			BitBlt (state->_hoops_AGICI, x, y, width, 1,
					state->_hoops_SGICI, 0, 0, SRCCOPY);
			SelectObject (state->_hoops_SGICI, _hoops_CSHCI);
			++y;
			rasters += width;
		}

		DeleteObject (_hoops_GGHSI);
	}
	else {
		_hoops_RGGA (height-- == 0) {
#ifndef _WIN32_WCE
			SetDIBitsToDevice (state->_hoops_AGICI, x, y, width, 1, 0, 0, 0, 1,
							   (LPVOID)rasters,
							   state->_hoops_APICI,
							   DIB_PAL_COLORS);
#endif
			rasters += width;
			++y;
		}
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_CCCGA (
	Net_Rendition const & nr,
	DC_Point const				*start,
	DC_Point const				*end,
	int								row_bytes,
	unsigned char const				*_hoops_GAAC) {
	MSW_Driver_State alter				*state = _hoops_IICCI ();
	int								width = (int) (end->x - start->x) + 1;
	int								x = (int) start->x;
	int								y = state->yfudge - (int)(start->y);
	LPBITMAPINFOHEADER				_hoops_GGHPR = &state->_hoops_APICI->bmiHeader;
	HBITMAP							_hoops_GGHSI;
	HBITMAP							_hoops_CSHCI;
	/*_hoops_SPRS		_hoops_GAGSI _hoops_RCIC		*_hoops_CSPH = _hoops_SCII->_hoops_GHCSR;*/

	UNREFERENCED(row_bytes);

	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	_hoops_GGHPR->biWidth		= width;
	_hoops_GGHPR->biHeight	= 1;
	_hoops_GGHPR->biSizeImage = (width+7)/8;
	_hoops_GGHPR->biBitCount	= 1;

	if (state->_hoops_SRRRR) {
		_hoops_GGHSI = CreateCompatibleBitmap (state->_hoops_AGICI, width, 1);
#ifndef _WIN32_WCE
		SetDIBits (state->_hoops_AGICI, _hoops_GGHSI, 0, 1,
				   (LPVOID)_hoops_GAAC, state->_hoops_APICI,
				   DIB_PAL_COLORS);
#endif
		_hoops_CSHCI = (HBITMAP)
			SelectObject (state->_hoops_SGICI, _hoops_GGHSI);
		BitBlt (state->_hoops_AGICI, x, y, width, 1,
				state->_hoops_SGICI, 0, 0, SRCCOPY);
		SelectObject (state->_hoops_SGICI, _hoops_CSHCI);

		DeleteObject (_hoops_GGHSI);
	}
	else {
#ifndef _WIN32_WCE
		SetDIBitsToDevice (state->_hoops_AGICI,
						   x, y, width, 1, 0, 0, 0, 1,
						   (LPVOID)_hoops_GAAC, state->_hoops_APICI,
						   DIB_PAL_COLORS);
#endif
	}
}

#if !defined(DISABLE_TEXTURING) && !defined(_WIN32_WCE)
local bool _hoops_CAHSI(_hoops_AIGH const * img, int width, int height, int _hoops_SAHSI, _hoops_AIGH const & _hoops_GPHSI)
{
	while(height--){
		if(
			img[ (width * height) + _hoops_SAHSI ].r != _hoops_GPHSI.r ||
			img[ (width * height) + _hoops_SAHSI ].g != _hoops_GPHSI.g ||
			img[ (width * height) + _hoops_SAHSI ].b != _hoops_GPHSI.b
		){
			return false;
		}
	}
	return true;
}

local void _hoops_RPHSI(
	Net_Rendition const & nr,
	Int_Rectangle const * _hoops_GAHIP,
	_hoops_RCR	const * _hoops_IICSR)
{
	MSW_Driver_State alter *	state = _hoops_IICCI ();
	_hoops_SAHAP _hoops_HGIIR = *((_hoops_SAHAP)_hoops_IICSR->_hoops_HGIIR->address);
	void * _hoops_HRARP = _hoops_IICSR->_hoops_HRARP;
	RGBTRIPLE * _hoops_APHSI = 0;
	_hoops_AIGH * rasters = 0;
	_hoops_AIGH * row = 0;
	int width = 0;
	int height = 0;
	int const _hoops_PPHSI = _hoops_GAHIP->left;
	int const _hoops_HPHSI = _hoops_GAHIP->right - _hoops_PPHSI +2;
	int const _hoops_IPHSI = _hoops_GAHIP->bottom;
	int const _hoops_CPHSI = _hoops_GAHIP->top - _hoops_GAHIP->bottom +2;
	HDC	_hoops_AGICI;

	if (state->_hoops_IRICI)
		_hoops_AGICI = state->_hoops_HRICI;
	else
		_hoops_AGICI = state->_hoops_AGICI;
	
	_hoops_HGIIR (
		_hoops_HPHSI, 
		_hoops_CPHSI,
		0, 
		&width, 
		&height,
		0,
		0,
		0,
		_hoops_HRARP);

	int const _hoops_CHPSI = ((width + 3) & (~0x0003));
	int const _hoops_SPHSI = 80;
	POOL_ALLOC_ARRAY_CACHED(_hoops_APHSI, _hoops_SPHSI * _hoops_CHPSI, RGBTRIPLE, nr->_hoops_SRA->memory_pool);
	POOL_ALLOC_ARRAY_CACHED(rasters, _hoops_SPHSI * width, _hoops_AIGH, nr->_hoops_SRA->memory_pool);

	BITMAPINFO _hoops_AGHSI;
	SET_MEMORY(&_hoops_AGHSI, sizeof(_hoops_AGHSI), 0);

	_hoops_AGHSI.bmiHeader.biSize				= sizeof (BITMAPINFOHEADER);
	_hoops_AGHSI.bmiHeader.biWidth			= _hoops_CHPSI;
	_hoops_AGHSI.bmiHeader.biHeight			= _hoops_SPHSI;
	_hoops_AGHSI.bmiHeader.biPlanes			= 1;
	_hoops_AGHSI.bmiHeader.biBitCount			= 24;
	_hoops_AGHSI.bmiHeader.biCompression		= BI_RGB; /* _hoops_GHHSI */
	_hoops_AGHSI.bmiHeader.biXPelsPerMeter	= state->_hoops_PIICI;
	_hoops_AGHSI.bmiHeader.biYPelsPerMeter	= state->_hoops_HIICI;
	_hoops_AGHSI.bmiHeader.biSizeImage		= _hoops_SPHSI * _hoops_CHPSI * sizeof(RGBTRIPLE);

	int _hoops_RPHAP = 0;
	while (_hoops_RPHAP < height) {
		int _hoops_RHHSI = _hoops_SPHSI;
		if(_hoops_RHHSI > height - _hoops_RPHAP){
			_hoops_RHHSI = height - _hoops_RPHAP;
		}

		int _hoops_AHHSI = 0;
		int _hoops_PHHSI = width < _hoops_HPHSI ? width -1 : _hoops_HPHSI -1;
		for(int i = 0; i < _hoops_RHHSI; ++i){
			_hoops_HGIIR (
				_hoops_HPHSI,
				_hoops_CPHSI,
				_hoops_RPHAP +i,
				&width,
				&height,
				0,
				(char**)&row,
				0,
				_hoops_HRARP);

			/* _hoops_HHHSI _hoops_RH _hoops_CSCR _hoops_HPGP _hoops_CCCH.  _hoops_IGGPH _hoops_AGAH _hoops_RRRH _hoops_CHR _hoops_GSSC _hoops_GRGPR _hoops_HRGR
			 * _hoops_SCIA, _hoops_HIH _hoops_HRRPI _hoops_HRGR _hoops_GSSC _hoops_GRGPR _hoops_HRGR _hoops_PRPC. */
			if(row)
				COPY_MEMORY(row, (_hoops_PHHSI +1) * sizeof(_hoops_AIGH), rasters + (_hoops_RHHSI - i -1) * width);
			else
				ZERO_ARRAY(rasters + (_hoops_RHHSI - i -1) * width, _hoops_PHHSI+1, _hoops_AIGH);
		}

		/* _hoops_IHHSI _hoops_SGGR _hoops_RH _hoops_PGS _hoops_ASPA _hoops_HII _hoops_RH _hoops_RAAP... */
		while (_hoops_AHHSI < (_hoops_PHHSI+1) && _hoops_CAHSI(rasters, width, _hoops_RHHSI, _hoops_AHHSI, _hoops_AIGH(255, 255, 255))){
			++_hoops_AHHSI;
		}
		/* _hoops_CGP _hoops_IIH'_hoops_GRI _hoops_PA _hoops_RAAP _hoops_RAS _hoops_CHHSI _hoops_SGGR _hoops_RH _hoops_RAAP _hoops_ICRP _hoops_PGS _hoops_ASPA... */
		if (_hoops_AHHSI < (_hoops_PHHSI+1)) {

			/* _hoops_IHHSI _hoops_SGGR _hoops_RH _hoops_PGS _hoops_ASPA _hoops_HII _hoops_RH _hoops_RPHR... */
			while (_hoops_PHHSI >= _hoops_AHHSI && _hoops_CAHSI(rasters, width, _hoops_RHHSI, _hoops_PHHSI, _hoops_AIGH(255, 255, 255))){
				--_hoops_PHHSI;
			}
			int const _hoops_SHHSI = _hoops_PHHSI - _hoops_AHHSI +1;

			if(_hoops_SHHSI > 0){

				float _hoops_AGRSH = _hoops_PPHSI + _hoops_AHHSI * _hoops_HPHSI / (double) width;
				float x1 = _hoops_AGRSH + _hoops_SHHSI * _hoops_HPHSI / (double) width -1;
				float _hoops_PGRSH = _hoops_IPHSI + _hoops_RPHAP * _hoops_CPHSI / (double) height;
				float _hoops_AGSIR = _hoops_PGRSH + _hoops_RHHSI * _hoops_CPHSI / (double) height;

				DC_Point start(_hoops_AGRSH, _hoops_PGRSH, 0);
				DC_Point end(x1, _hoops_AGSIR, 0);
				
				for(int r = 0; r < _hoops_RHHSI; ++r){
					for(int c = 0; c < _hoops_SHHSI; ++c){
						int const _hoops_AHPCP = r * _hoops_CHPSI + c;
						int const _hoops_GIHSI = r * width + c;
						_hoops_APHSI[_hoops_AHPCP].rgbtRed = rasters[_hoops_GIHSI + _hoops_AHHSI].r;
						_hoops_APHSI[_hoops_AHPCP].rgbtGreen = rasters[_hoops_GIHSI + _hoops_AHHSI].g;
						_hoops_APHSI[_hoops_AHPCP].rgbtBlue = rasters[_hoops_GIHSI + _hoops_AHHSI].b;
					}
				}

				StretchDIBits (
					_hoops_AGICI,
					start.x,
					start.y,
					end.x - start.x,
					end.y - start.y,
					0,
					0,
					_hoops_SHHSI,
					_hoops_RHHSI,
					(LPVOID)_hoops_APHSI,
					&_hoops_AGHSI,
					DIB_RGB_COLORS,
					SRCCOPY);
			}
		}
		_hoops_RPHAP += _hoops_RHHSI;
	}
	FREE_ARRAY(_hoops_APHSI, _hoops_SPHSI * _hoops_CHPSI, RGBTRIPLE);
	FREE_ARRAY(rasters, _hoops_SPHSI * width, _hoops_AIGH);
}
#endif

/*
 * _hoops_SRAC
 */
local void draw_window (
	Net_Rendition const &		nr,
	Int_Rectangle const			*extent) {
	_hoops_CGRA const		_hoops_SGRA = nr->_hoops_SAIR;
	MSW_Driver_State alter *	state = _hoops_IICCI ();

	Image const					*image = null;
	_hoops_RCR						*_hoops_IICSR = null;
	_hoops_HCHIR				*_hoops_HGIIR	= 0;
	_hoops_CPAIR				_hoops_CICSR;


#if defined(_WIN32_WCE) || defined(DISABLE_TEXTURING)
	HD_Standard_Draw_Window(nr, extent);
	return;
#else

	
	if (_hoops_SGRA->_hoops_PGPH != null || _hoops_SGRA->_hoops_SICSR == null) {
		HD_Standard_Draw_Window(nr, extent);
		return;
	}

	if (nr->_hoops_GCCSR->count > 0) {
		_hoops_CICSR.textures = nr->_hoops_GCCSR->textures;
		_hoops_CICSR.keys = nr->_hoops_GCCSR->keys;
		_hoops_CICSR.count = nr->_hoops_GCCSR->count;
	}
	else {
		_hoops_CICSR.textures = 0;
		_hoops_CICSR.keys = 0;
		_hoops_CICSR.count = 0;
	}

	if ((_hoops_IICSR = HI_Activate_Texture((_hoops_RCR alter *)_hoops_SGRA->_hoops_SICSR, &_hoops_CICSR, false)) != null) {
		_hoops_HGIIR = _hoops_IICSR->_hoops_HGIIR;
		image = _hoops_IICSR->image;
	}
	
	if (_hoops_IICSR == null || BIT(_hoops_IICSR->flags, _hoops_AIA)) {
		HD_Standard_Draw_Window (nr, extent);
		return;
	}

	if (image == null && _hoops_IICSR->_hoops_HGIIR == null) {
		_hoops_HPRH(_hoops_IICSR);
		HD_Standard_Draw_Window(nr, extent);
		return;
	}
	if (image != null && 
		image->format != Image_RGBA32) {

		_hoops_HPRH(_hoops_IICSR);
		HD_Standard_Draw_Window(nr, extent);
		return;
	}

	draw_and_reset_poly_cache(state, true);
	_hoops_PRASI(nr);

	if (_hoops_IICSR->_hoops_HGIIR != null) {
		_hoops_RPHSI(nr, extent, _hoops_IICSR);
	}
	else {
		Int_Rectangle const			*_hoops_GAHIP = &_hoops_SGRA->_hoops_GAHIP;

		int width = 0;
		int height = 0;

		int								_hoops_RAAC, _hoops_RIHSI, _hoops_CAAIP;
		int								left, _hoops_IIIH, _hoops_SIIH;


		unsigned char					*_hoops_GIPSI = null;
		int								_hoops_CHPSI;
		int								_hoops_PGHSI;
		int								_hoops_SHPSI = 0;

		int								_hoops_SGHSI;

		unsigned char alter				*pp;
		unsigned char const				*pe;
		BITMAPINFO					_hoops_AGHSI;
		_hoops_AIGH const * const *		rasters;
		_hoops_AIGH const *				_hoops_PIPSI;
		HDC	_hoops_AGICI;	

		if (state->_hoops_IRICI)
			_hoops_AGICI = state->_hoops_HRICI;
		else
			_hoops_AGICI = state->_hoops_AGICI;

		width = image->width;
		height = image->height;

		rasters = (_hoops_AIGH const * const *) image->rasters;
		rasters += height-1;

		_hoops_SGHSI = height;

		_hoops_CHPSI = ((width + 3) & (~0x0003));
		_hoops_PGHSI = _hoops_CHPSI * 3;
		_hoops_SHPSI = _hoops_PGHSI;

		TRY_ALLOC_ARRAY(_hoops_GIPSI, _hoops_SHPSI, unsigned char);

		if (_hoops_GIPSI == null) {
			HE_ERROR (HEC_MEMORY, HES_ALLOCATE_MEMORY_FAILED,
					  "Unable to allocate memory for a single scan line");
			_hoops_HPRH(_hoops_IICSR);
			return;
		}

		_hoops_AGHSI.bmiHeader.biSize				= sizeof (BITMAPINFOHEADER);
		_hoops_AGHSI.bmiHeader.biWidth			= _hoops_CHPSI;
		_hoops_AGHSI.bmiHeader.biHeight			= 1;
		_hoops_AGHSI.bmiHeader.biPlanes			= 1;
		_hoops_AGHSI.bmiHeader.biBitCount			= 24;
		_hoops_AGHSI.bmiHeader.biCompression		= BI_RGB; /* _hoops_GHHSI */
		_hoops_AGHSI.bmiHeader.biSizeImage		= width;
		_hoops_AGHSI.bmiHeader.biXPelsPerMeter	= state->_hoops_PIICI;
		_hoops_AGHSI.bmiHeader.biYPelsPerMeter	= state->_hoops_HIICI;
		_hoops_AGHSI.bmiHeader.biClrUsed			= 0;
		_hoops_AGHSI.bmiHeader.biClrImportant		= 0;
		_hoops_AGHSI.bmiHeader.biSizeImage		= _hoops_PGHSI;

		unsigned char * _hoops_AIPSI = _hoops_GIPSI;

		_hoops_IIIH = _hoops_GAHIP->right - _hoops_GAHIP->left +1;
		_hoops_SIIH = _hoops_GAHIP->top - _hoops_GAHIP->bottom +1;
		left = _hoops_GAHIP->left;


		_hoops_CAAIP = _hoops_GAHIP->bottom;

		_hoops_RAAC = state->yfudge;

		_hoops_RGGA (_hoops_SGHSI-- == 0) {
			_hoops_RIHSI = state->yfudge - (height - _hoops_SGHSI) * _hoops_SIIH / height;

			pp = (unsigned char alter *) _hoops_AIPSI;
			pe = (unsigned char const *)(_hoops_AIPSI + width * 3);
			_hoops_PIPSI = *rasters--;

			do {
				*pp++ = _hoops_PIPSI->b;
				*pp++ = _hoops_PIPSI->g;
				*pp++ = _hoops_PIPSI->r;

				_hoops_PIPSI++;
			} _hoops_RGGA (pp == pe);

			if (state->_hoops_SSRRI == _hoops_GGARI || state->_hoops_SSRRI == _hoops_RGARI || 
					(state->_hoops_PIGRR != _hoops_GSPCI && state->_hoops_PIGRR != _hoops_ASPCI)) {
				StretchDIBits (
					_hoops_AGICI,
					left, _hoops_RIHSI - _hoops_CAAIP, _hoops_IIIH, _hoops_RAAC-_hoops_RIHSI+1,
					0, 0, width, 1,
					(LPVOID)_hoops_GIPSI, &_hoops_AGHSI, DIB_RGB_COLORS, SRCCOPY);

			}
			else {
				int offset=0, _hoops_AIHSI=width, i;
				int _hoops_PIHSI, _hoops_HIHSI;

				pp -= width*3;

				for (i=0; i<width * 3;i+=3) {
					if (pp[i]==255 && pp[i+1]==255 && pp[i+2]==255)
						offset++;
					else 
						break;
				}

				_hoops_AIHSI -= offset;

				if (_hoops_AIHSI > 0) {
					for (i=width*3-3; i>=0;i-=3) {

						if (pp[i]==255 && pp[i+1]==255 && pp[i+2]==255)
							_hoops_AIHSI--;
						else 
							break;
					}

					_hoops_PIHSI = left + (offset*_hoops_IIIH/width);
					_hoops_HIHSI = (_hoops_AIHSI*_hoops_IIIH/width)+1;

					StretchDIBits (
						_hoops_AGICI,
						_hoops_PIHSI, _hoops_RIHSI - _hoops_CAAIP, _hoops_HIHSI, _hoops_RAAC-_hoops_RIHSI+1,
						offset, 0, _hoops_AIHSI, 1,
						(LPVOID)_hoops_GIPSI, &_hoops_AGHSI, DIB_RGB_COLORS, SRCCOPY);
				}
			}

			_hoops_RAAC = _hoops_RIHSI;
		}

		if(_hoops_GIPSI)
			FREE_ARRAY(_hoops_GIPSI, _hoops_SHPSI, char);
	}

	_hoops_HPRH(_hoops_IICSR);

#endif
}


/*****************************************************************************
 *****************************************************************************
							  _hoops_IPSRH _hoops_PARPI
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_PGAA
 */
local void _hoops_IIHSI (
	MSW_Driver_State alter	*state) {
	HBRUSH				_hoops_CIHSI;
	RECT				_hoops_SIHSI;


	state->_hoops_IGICI = state->_hoops_AGICI;
	state->_hoops_CGICI = CreateCompatibleDC (state->_hoops_AGICI);

	/* _hoops_SHSP _hoops_RH _hoops_CIHH _hoops_PSAP */ _hoops_ICRSI (state);

	/* _hoops_GISA _hoops_SCH _hoops_IH _hoops_RH _hoops_CIAS _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_SHPR */
	{
		GetClientRect (GetDesktopWindow (), &_hoops_SIHSI);
		state->_hoops_IAICI =
			CreateCompatibleBitmap (state->_hoops_AGICI,
									_hoops_SIHSI.right,
									_hoops_SIHSI.bottom);
	}

	if (state->_hoops_IAICI == NULL) {
		/*
		 * _hoops_IPGRH _hoops_PRAR, _hoops_SGS _hoops_SARS'_hoops_RA _hoops_IPHR.
		 */
		ReleaseDC (state->_hoops_GGICI, state->_hoops_CGICI);
		state->_hoops_SRRRR = false;
	}
	else {
		/*
		 * _hoops_GCHSI - _hoops_SR _hoops_GGHP _hoops_PCCP _hoops_CPRAH _hoops_CCAC
		 */

		/*
		 * _hoops_RPP _hoops_SR _hoops_HS _hoops_SPIP _hoops_PPR _hoops_RCHSI _hoops_IRS _hoops_CSGSR _hoops_PAR _hoops_IPHCI,
		 * _hoops_ACHSI _hoops_SCH _hoops_PPR _hoops_HSCI _hoops_SCH
		 */
		if (state->_hoops_RIICI != NULL) {
			SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);
		}

		SelectObject (state->_hoops_AGICI, state->_hoops_SPCCI);

		/* _hoops_AGGA _hoops_HAIHR _hoops_RGR _hoops_PSSCI _hoops_CRGR _hoops_ISCP _hoops_PPGS _hoops_SHCA */
		state->_hoops_CSHCI = (HBITMAP) SelectObject (state->_hoops_CGICI,
											state->_hoops_IAICI);
		state->_hoops_AGICI = state->_hoops_CGICI;

		/* _hoops_GISA _hoops_IRS _hoops_SHCA _hoops_IH _hoops_HIRAA _hoops_AHRH _hoops_HPGP _hoops_GHGPR _hoops_RHGPR */
		state->_hoops_SGICI = CreateCompatibleDC (state->_hoops_CGICI);


		if (state->_hoops_GIICI != NULL &&
			state->_hoops_PIGRR != _hoops_PSPCI) {
			SelectPalette (state->_hoops_CGICI,
						   state->_hoops_GIICI,
						   !state->_hoops_SRCCI);
#ifndef _WIN32_WCE
			UnrealizeObject (state->_hoops_GIICI);
#endif
			RealizePalette (state->_hoops_CGICI);
		}

		/* _hoops_PCHSI _hoops_RAPR _hoops_RGR _hoops_PSSCI _hoops_AHPP _hoops_IS _hoops_SCIR _hoops_PISA _hoops_RCAPI _hoops_HIS
			_hoops_IIS _hoops_IHHH _hoops_PGSA _hoops_IRS _hoops_ARRGR _hoops_GGR _hoops_PGS _hoops_IS _hoops_SCH */

		_hoops_CIHSI = (HBRUSH) GetStockObject (WHITE_BRUSH);
		SelectObject (state->_hoops_AGICI, _hoops_CIHSI);
		GDI_Rectangle (state->_hoops_AGICI, 0, 0,
				   _hoops_SIHSI.right, _hoops_SIHSI.bottom);
		SelectObject (state->_hoops_AGICI, state->_hoops_SPCCI);
		DeleteObject (_hoops_CIHSI);
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_HCHSI (
	Display_Context const	*dc) {
	_hoops_RRPRH alter			*_hoops_IRSRA = _hoops_ARPRH ();
	int							ii;


	HD_Get_Bit_Patterns_8 ((Display_Context alter *)dc, false);

	if (_hoops_IRSRA->bit_patterns == null) {
		ALLOC_ARRAY (_hoops_IRSRA->bit_patterns, TOTAL_BIT_PATTERNS, HBITMAP);

		for (ii = 0; ii < TOTAL_BIT_PATTERNS; ii++) {
			unsigned short			_hoops_ICHSI[8];
			unsigned char const		*_hoops_APHCP;
			unsigned short alter	*_hoops_CCHSI;

			_hoops_CCHSI = _hoops_ICHSI;
			_hoops_APHCP = (unsigned char const *)dc->_hoops_GRPH[ii];

			*_hoops_CCHSI++ = (unsigned short)*_hoops_APHCP++;
			*_hoops_CCHSI++ = (unsigned short)*_hoops_APHCP++;
			*_hoops_CCHSI++ = (unsigned short)*_hoops_APHCP++;
			*_hoops_CCHSI++ = (unsigned short)*_hoops_APHCP++;
			*_hoops_CCHSI++ = (unsigned short)*_hoops_APHCP++;
			*_hoops_CCHSI++ = (unsigned short)*_hoops_APHCP++;
			*_hoops_CCHSI++ = (unsigned short)*_hoops_APHCP++;
			*_hoops_CCHSI++ = (unsigned short)*_hoops_APHCP++;

			/* _hoops_ASAC _hoops_IRS _hoops_RGHH _hoops_HSSPP */
			_hoops_IRSRA->bit_patterns[ii] = CreateBitmap (8, 8, 1, 1,
												 (LPSTR)_hoops_ICHSI);
		}
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_SCHSI (
	Display_Context alter	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();
	LOGBRUSH					_hoops_PHRSI;
	HENHMETAFILE				_hoops_GSHSI;
	HPEN						_hoops_CGPSI;
	int							_hoops_SSHCI;

	/* _hoops_CPGP _hoops_HAR _hoops_HCR _hoops_PSCH _hoops_ARP _hoops_RH _hoops_CGHI _hoops_RIHH _hoops_SCAC _hoops_SCH _hoops_ARPP _hoops_HCR _hoops_HCPH */
	memset(&_hoops_PHRSI,0,sizeof(LOGBRUSH));

	SetLastError (ERROR_SUCCESS);
	CreateDIBPatternBrushPt (NULL, DIB_PAL_COLORS);
	if (GetLastError () == ERROR_CALL_NOT_IMPLEMENTED)
		state->_hoops_IAHCI = false;
	else
		state->_hoops_IAHCI = true;
	SetLastError (ERROR_SUCCESS);
#ifndef _WIN32_WCE
	SetPixelV (state->_hoops_PGICI, 0, 0, 0);
#endif
	if (GetLastError () == ERROR_CALL_NOT_IMPLEMENTED)
		state->_hoops_CAHCI = false;
	else
		state->_hoops_CAHCI = true;

	SetLastError (ERROR_SUCCESS);
	_hoops_PHRSI.lbColor = 1;
	_hoops_PHRSI.lbStyle = BS_SOLID;
#ifndef _WIN32_WCE
	_hoops_CGPSI = ExtCreatePen (PS_COSMETIC|PS_SOLID, 1, &_hoops_PHRSI, 0, NULL);
#endif
	if (GetLastError () == ERROR_CALL_NOT_IMPLEMENTED)
		state->_hoops_SAHCI = false;
	else {
		state->_hoops_SAHCI = true;
	}
	if (_hoops_CGPSI != NULL)
		DeleteObject (_hoops_CGPSI);

	SetLastError (ERROR_SUCCESS);
#ifndef _WIN32_WCE
	PolyPolyline (state->_hoops_PGICI, NULL, NULL, 0);

	if (GetLastError () == ERROR_CALL_NOT_IMPLEMENTED)
		state->_hoops_RPHCI = false;
	else
		state->_hoops_RPHCI = true;
#else
		state->_hoops_RPHCI = false;
#endif
	/* _hoops_RAHP _hoops_SGIP _hoops_GAR _hoops_GHAP _hoops_ACPA _hoops_AGCR _hoops_CHR _hoops_PSP _hoops_RSHSI _hoops_HIH ... */
	SetLastError (ERROR_SUCCESS);
#ifndef _WIN32_WCE
	PolyPolygon (state->_hoops_PGICI, NULL, NULL, 0);
	if (GetLastError () == ERROR_CALL_NOT_IMPLEMENTED)
		state->_hoops_APHCI = false;
	else
		state->_hoops_APHCI = true;
#else
		state->_hoops_APHCI = false;
#endif


	SetLastError (ERROR_SUCCESS);
#ifndef _WIN32_WCE
	PolyTextOut (state->_hoops_PGICI, NULL, 0);
	if (GetLastError () == ERROR_CALL_NOT_IMPLEMENTED)
		state->_hoops_PPHCI = false;
	else
		state->_hoops_PPHCI = true;
#else
		state->_hoops_PPHCI = false;
#endif

	if (state->_hoops_AGICI != null) {
		/* _hoops_RAH _hoops_HAR _hoops_RRP _hoops_IS _hoops_RPGP - _hoops_GPACI _hoops_GRS _hoops_HAR _hoops_GCGH */

		state->_hoops_GPCCI = false;
#ifndef _WIN32_WCE
		if (GetObjectType ((HGDIOBJ) state->_hoops_AGICI) == OBJ_METADC) {
			/* _hoops_RASRR _hoops_SSCP _hoops_CGI _hoops_IHHH _hoops_PCCP _hoops_RHGS _hoops_IAHA _hoops_SCRII _hoops_RGHH */
			state->_hoops_GPHCI = false;
			state->_hoops_PPHCI = false;
			state->_hoops_APHCI = false;
			state->_hoops_RPHCI = false;
			state->_hoops_SAHCI = false;
			state->_hoops_CAHCI = false;
			state->_hoops_IAHCI = false;
			/*_hoops_ASIGA _hoops_RGR _hoops_IRHS _hoops_IS _hoops_ASHSI _hoops_HCR _hoops_PGSI
			 _hoops_PIAP->_hoops_PSHSI=_hoops_IHPR;
			_hoops_CSPH->_hoops_CPHSR._hoops_HSHSI = _hoops_RCPP;
			*/
		}
		else {
			HDC	_hoops_AGICI;
			SetLastError (ERROR_SUCCESS);
			_hoops_AGICI = CreateEnhMetaFile (state->_hoops_PGICI, NULL, NULL, NULL);
			if (GetLastError () == ERROR_CALL_NOT_IMPLEMENTED) {
				state->_hoops_GPHCI = false;
			}
			else {
				state->_hoops_GPHCI = true;
				_hoops_GSHSI = CloseEnhMetaFile (_hoops_AGICI);
				DeleteEnhMetaFile (_hoops_GSHSI);
			}
		}
#endif
	}
	else {
	   SetLastError (ERROR_SUCCESS);
	   /* _hoops_HGI _hoops_RPGP _hoops_PIHA _hoops_SHH _hoops_CPHR _hoops_GPP _hoops_RH _hoops_RIHRR _hoops_SHCA _hoops_PPR _hoops_HAR _hoops_RH _hoops_SIHC _hoops_SHCA */

	   {
		   HDC	_hoops_AGICI;
		   if (state->_hoops_AGICI == NULL)
			   _hoops_AGICI = state->_hoops_PGICI;
		   else
			   _hoops_AGICI = state->_hoops_AGICI;

		   _hoops_SSHCI = SetROP2 (_hoops_AGICI, R2_XORPEN);
		   if (_hoops_SSHCI == 0)
			   state->_hoops_GPCCI = false;
		   else {
			   state->_hoops_GPCCI = true;
			   SetROP2 (_hoops_AGICI, _hoops_SSHCI);
		   }
	   }
	}
#ifndef _WIN32_WCE
	if (BeginPath (state->_hoops_PGICI)) {
		EndPath (state->_hoops_PGICI);
		state->_hoops_HPHCI = true;
	}
	else
#endif
		{
		state->_hoops_HPHCI = false;
	}

	{
#ifndef _WIN32_WCE
		WORD		   _hoops_ISHSI;
		char		   _hoops_CSHSI[255];
		_hoops_ISHSI = GETTECHNOLOGY;
		if (Escape(state->_hoops_PGICI, QUERYESCSUPPORT, sizeof(WORD), (LPSTR)&_hoops_ISHSI, NULL)) {
			Escape(state->_hoops_PGICI, GETTECHNOLOGY, 0, NULL, &_hoops_CSHSI);
		}
		_hoops_ISHSI = EPSPRINTING;
		if (Escape(state->_hoops_PGICI, QUERYESCSUPPORT, sizeof(WORD), (LPSTR)&_hoops_ISHSI, NULL)) {
			Escape(state->_hoops_PGICI, EPSPRINTING, 0, NULL, NULL);
		}
#endif
	}
}


/*
 * _hoops_SRAC
 */
local bool start_device (
	Display_Context alter	*dc) {
	MSW_Driver_State alter			*state;
	_hoops_RRPRH alter			*_hoops_IRSRA = _hoops_ARPRH ();


	ZALLOC(state, MSW_Driver_State);
	state->_hoops_IPCCI = 1024;
	ALLOC_ARRAY(state->_hoops_HPCCI,state->_hoops_IPCCI,unsigned char);
	state->points = 0;
	state->_hoops_CRCCI = 0;
	state->_hoops_HAICI = _hoops_CCC;


	dc->data = (void alter *) state;

	state->dc = dc;

#ifndef _WIN32_WCE
	state->_hoops_CPCCI = (HFONT) GetStockObject(DEVICE_DEFAULT_FONT);
#endif
	state->_hoops_SPCCI = (HBRUSH) GetStockObject(NULL_BRUSH);
	state->_hoops_GHCCI = (HPEN) GetStockObject(NULL_PEN);
	state->_hoops_RHCCI = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	/* _hoops_ARPR _hoops_IRS _hoops_SPCS _hoops_ISPH _hoops_IH _hoops_RH _hoops_HSPH _hoops_PRCH */
	state->_hoops_AAICI = CreateRectRgn (0, 0, 1, 1);
	SetRectEmpty (&state->_hoops_HIGRR);
	/* _hoops_PPR _hoops_IRS _hoops_SPCS _hoops_SGCS _hoops_ISPH _hoops_HIS _hoops_SR _hoops_PAH _hoops_SHR _hoops_HSCI _hoops_IGIRR */
	state->_hoops_PAICI = CreateRectRgn (0, 0, 1, 1);

	/* _hoops_GHRAA _hoops_HHH _hoops_IIGR _hoops_RH _hoops_PIAP _hoops_CCPAR _hoops_IS _hoops_SHIR _hoops_HSH */
	state->_hoops_CIICI = true;
	state->_hoops_CSC._hoops_ICICI = R2_COPYPEN;
	state->_hoops_PIHSR = dc->_hoops_PGCC._hoops_PIHSR;

	_hoops_ACCCI (state);

	state->_hoops_SSRRI = _hoops_IRSRA->_hoops_SSRRI;

	state->_hoops_RGCCI =  true;

	if (state->_hoops_RGCCI)
		state->_hoops_GGCCI = true;

	/* _hoops_SIIR _hoops_PAIA _hoops_IH _hoops_APGR _hoops_PPR _hoops_SSSCI */
	_hoops_HCHSI (dc);

	/* _hoops_HGH _hoops_GPRR _hoops_RRGR _hoops_SSHSI _hoops_GGR _hoops_SGH _hoops_IH _hoops_GSPIP */
	{
		CPINFO _hoops_GGISI;
		GetCPInfo (CP_ACP, &_hoops_GGISI);
		if (_hoops_GGISI.MaxCharSize == 1)
			state->_hoops_RRHCI = false;
		else
			state->_hoops_RRHCI = true;

		GetCPInfo (CP_OEMCP, &_hoops_GGISI);
		if (_hoops_GGISI.MaxCharSize == 1)
			state->_hoops_GRHCI = false;
		else
			state->_hoops_GRHCI = true;
	}

	/*
	 * _hoops_AGGA _hoops_CGIC _hoops_PCPA _hoops_CGGAR _hoops_IIGR _hoops_SPHGR _hoops_SISS _hoops_SR _hoops_CHR _hoops_SRHPH _hoops_IS
	 * _hoops_HGI _hoops_HSPR _hoops_HGRH _hoops_HRGR _hoops_IGI _hoops_IH _hoops_IRRIR _hoops_PPCIP ....
	 */
	if (!dc->options._hoops_GCHSR) {
		   if (!dc->options._hoops_ISPRP) {
				/* _hoops_PS _hoops_RRP _hoops_IS _hoops_ISPR _hoops_RH _hoops_PCSHA _hoops_RSIRR */
				char * _hoops_GHRI;
				int i;
				ALLOC_ARRAY(_hoops_GHRI, dc->_hoops_HCRSR+1, char);
				strcpy(_hoops_GHRI, dc->_hoops_PCRSR);
				for (i=0; i<dc->_hoops_HCRSR; ++i) {
					_hoops_GHRI[i] = tolower(_hoops_GHRI[i]);
				}

				if (!strcmp(dc->_hoops_PCRSR, "clipboard")) {
					/* _hoops_HASRR _hoops_RGISI (_hoops_APPCI) */
					state->_hoops_PIGRR = _hoops_RSPCI;
					state->_hoops_GAHCI = true;
					state->_hoops_PCHCI = false;
				} else if (!strcmp(dc->_hoops_PCRSR + dc->_hoops_HCRSR - 5, ".emf")) {
					/* _hoops_HASRR _hoops_RGISI (_hoops_AGISI _hoops_RGHR) */
					state->_hoops_PIGRR = _hoops_RSPCI;
					state->_hoops_GAHCI = true;
					state->_hoops_PCHCI = true;
				} else if (!strcmp(dc->_hoops_PCRSR, "printer")) {
					/* _hoops_HASRR _hoops_RPPCI */
					state->_hoops_PIGRR = _hoops_GSPCI;
					state->_hoops_HGICI = _hoops_CGHCI;
					state->_hoops_AGICI = state->_hoops_PGICI = get_printer_DC (dc->options._hoops_ARPSR);
					state->_hoops_CRICI = true;
					state->_hoops_SRICI = true;
				} else {
					/* _hoops_HASRR _hoops_PGISI */
					state->_hoops_PIGRR = _hoops_PPSGR;
					state->_hoops_HGICI = _hoops_IGHCI;
					state->_hoops_PGICI = GetDC (GetDesktopWindow ());
				}
				FREE_ARRAY(_hoops_GHRI, dc->_hoops_HCRSR+1, char);
		   } else {
				/* _hoops_HGISI _hoops_RPPCI */
				state->_hoops_PIGRR = _hoops_ASPCI;
				state->_hoops_HGICI = _hoops_SCASA;
				state->_hoops_PRICI = state->_hoops_PGICI = 
							state->_hoops_AGICI = (HDC) dc->options._hoops_ISPRP;
				state->_hoops_IRICI = false;
				state->_hoops_CRICI = true;
				state->_hoops_SRICI = true;
				state->_hoops_GGICI = 0;
			}
	} else if (dc->options._hoops_RGHRP == _hoops_GGHRP) {
		Image *image;

		image = (Image alter *)_hoops_RCSSR (dc->_hoops_RIGC, dc->options._hoops_GCHSR);
		if (image == null) {
			HE_ERROR (HEC_MSW_DRIVER, HES_INVALID_KEY,
					"An invalid key was passed to the msw driver with use window id."); 
			return false;
		}
		if (image->_hoops_PHGH == 0 ||
			!(image->format == Image_RGBA32 || 
			 image->format == _hoops_HRSRH || 
			 image->format == _hoops_CSGSP || 
			 image->format == _hoops_HHGH)) {
			HE_ERROR (HEC_MSW_DRIVER, HES_INVALID_KEY,
					"msw output image unsupported format."); 
			return false;
		}
		state->_hoops_IHGRR = image;
		_hoops_PRRH (state->_hoops_IHGRR);
		state->_hoops_PIGRR = _hoops_RSPCI;
		state->_hoops_GAHCI = true;
		if (!strcmp(dc->_hoops_PCRSR + dc->_hoops_HCRSR - 5, ".emf")) {
					/* _hoops_HASRR _hoops_RGISI (_hoops_AGISI _hoops_RGHR) */
					state->_hoops_PIGRR = _hoops_RSPCI;
					state->_hoops_PCHCI = true;
		}
		else{
			state->_hoops_PCHCI = false;
		}
	} else {
		if (!dc->options._hoops_ISPRP) {
			/* _hoops_HGISI _hoops_HGGSP */
			long style;
			state->_hoops_GGICI = (HWND) dc->options._hoops_GCHSR;
			state->_hoops_PIGRR = _hoops_HPSGR;
			state->_hoops_HGICI = _hoops_IGHCI;
			state->_hoops_PGICI = GetDC (GetDesktopWindow ());
			/* _hoops_HGH _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_IGISI _hoops_CGISI _hoops_SGISI _hoops_GRISI _hoops_RPPS */
			style = GetWindowLong (state->_hoops_GGICI, GWL_STYLE);
			if (style & WS_CHILD)
				state->_hoops_SACCI = true;
		} else {
			/*
			 * _hoops_RRISI _hoops_RH _hoops_RCC _hoops_SSCP _hoops_RPII _hoops_IRS _hoops_ARISI _hoops_SGS _hoops_SR _hoops_IGI _hoops_IS _hoops_ARPR
			 * _hoops_RH _hoops_PRISI
			 * _hoops_HRISI _hoops_HGRC _hoops_SGS _hoops_SR _hoops_IRHH _hoops_SCH _hoops_PGI _hoops_IRS _hoops_SHCA _hoops_PAR _hoops_IRS _hoops_ARISI _hoops_HIS _hoops_SGS
			 * _hoops_IRS _hoops_HCACI _hoops_HHS _hoops_HS _hoops_RH _hoops_HPHS _hoops_GPGAR _hoops_HII _hoops_IRS _hoops_GRGAI
			 * _hoops_SHCA (_hoops_SIRSI _hoops_AA _hoops_HAR _hoops_HS _hoops_SPHGR _hoops_RIR _hoops_IRISI)
			 *
			 * _hoops_PS _hoops_CRISI _hoops_AA _hoops_HAR _hoops_RPGP _hoops_IH _hoops_SRISI _hoops_PAR _hoops_GAISI _hoops_CR _hoops_AGCR
			 * _hoops_CSSC _hoops_IIGR _hoops_SHCA _hoops_PAH _hoops_HAR _hoops_SHH _hoops_GPGAR _hoops_IH _hoops_HPHS
			 */
			if (BIT(dc->options._hoops_IRARR, _hoops_GHPCI)) {
				bool			_hoops_RAISI = false;

				state->_hoops_SRICI=true;

				/*
				 * _hoops_IIPR _hoops_RPCC _hoops_HRGR _hoops_IGI _hoops_IS _hoops_RIH _hoops_RH _hoops_SRGAI _hoops_PSPSI _hoops_CSPH _hoops_IS _hoops_AGAH.
				 * _hoops_PS _hoops_HHS _hoops_HS _hoops_SPIP _hoops_IRS _hoops_CCAH _hoops_HCSP _hoops_SGH _hoops_RPPS _hoops_AAISI _hoops_PAR _hoops_CPHP
				 * _hoops_RPP _hoops_SR _hoops_RIAGR _hoops_RAPR _hoops_SIH.
				 */
				if (dc->options._hoops_HAPIR) {

					if (dc->options._hoops_HAPIR->name.text[0] == '0' &&
						dc->options._hoops_HAPIR->name.text[1] == 'x')
						sscanf(dc->options._hoops_HAPIR->name.text, "%lx", &state->_hoops_AGICI);
					else
						sscanf(dc->options._hoops_HAPIR->name.text, "%ld", &state->_hoops_AGICI);

					/*_hoops_SR _hoops_GRHHR _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_SRGAI _hoops_PSPSI _hoops_IH _hoops_RCRR*/
					_hoops_RAISI = true;
				} else {
					state->_hoops_AGICI = (HDC)dc->options._hoops_ISPRP;

					/*_hoops_HPPR _hoops_PPR _hoops_SSS _hoops_GGSR _hoops_IH _hoops_HPHR _hoops_AGSHA*/
					if (GetDeviceCaps(state->_hoops_AGICI, RASTERCAPS)
							& RC_STRETCHBLT)
						_hoops_RAISI = true;
				}

				if ((BIT (dc->options._hoops_IRARR, _hoops_SAPCI)) ||
					(!_hoops_RAISI)) {

					/*_hoops_HHSA _hoops_IHIR _hoops_HAIR _hoops_HIS _hoops_APGR _hoops_HGCR _hoops_HSCH*/
					state->_hoops_CRICI = true;

					/* _hoops_AA _hoops_HAR _hoops_SGH _hoops_PAISI. _hoops_IH _hoops_ISHHH */
					/* _hoops_HIS _hoops_SR _hoops_GRHHR _hoops_SSIA _hoops_HS _hoops_ARP _hoops_HAR _hoops_ARP _hoops_HIPIP*/
					state->_hoops_IRICI = false;
					state->_hoops_GAICI = true;
					state->_hoops_PIGRR = _hoops_ASPCI;
					state->_hoops_GGICI = 0;
					state->_hoops_HGICI = _hoops_SCASA;
					state->_hoops_PGICI = (HDC) dc->options._hoops_ISPRP;

					if (state->_hoops_AGICI == state->_hoops_PGICI)
							state->_hoops_GAICI = false;
				} else {
					long		style;

					/* _hoops_PCSS _hoops_IS _hoops_PAISI _hoops_PPR _hoops_HAISI _hoops_IAISI. */
					state->_hoops_IRICI = true;
					state->_hoops_GAICI = true;
					state->_hoops_PIGRR = _hoops_HPSGR;
					/* _hoops_GSCA _hoops_IIGR _hoops_IRISR _hoops_RPPS */
					state->_hoops_GGICI = (HWND) dc->options._hoops_GCHSR;
					state->_hoops_HGICI = _hoops_IGHCI;
					/* _hoops_SIPR _hoops_SIHC _hoops_HII _hoops_SCGR _hoops_RPPS */
					state->_hoops_PGICI = GetDC (GetDesktopWindow ());
					/* _hoops_RPPCI _hoops_SHCA */
					state->_hoops_PRICI = (HDC) dc->options._hoops_ISPRP;

					style = GetWindowLong (state->_hoops_GGICI, GWL_STYLE);
					if (style & WS_CHILD)
						state->_hoops_SACCI = true;

						state->_hoops_HRICI = state->_hoops_AGICI;

					if (state->_hoops_HRICI == state->_hoops_PRICI)
							state->_hoops_GAICI = false;
				}
			} else {
				/* _hoops_HGI _hoops_HGGC _hoops_HICP _hoops_IS _hoops_GCGH _hoops_PGHC _hoops_IRSP, _hoops_GHAP _hoops_AHGC */
				state->_hoops_PIGRR = _hoops_PSPCI;
				state->_hoops_AGICI = (HDC) dc->options._hoops_ISPRP;
				state->_hoops_HGICI = _hoops_SCASA;
				state->_hoops_GGICI = (HWND) dc->options._hoops_GCHSR;
				state->_hoops_PGICI = GetDC (state->_hoops_GGICI);
			}
		}
	}

	state->_hoops_GAHCI = true;

	if (state->_hoops_SSRRI == _hoops_PHRCI && (state->_hoops_PIGRR&0x0F) == _hoops_HSPCI)
		/* _hoops_SRPR _hoops_RAPR _hoops_SHCA'_hoops_GRI - _hoops_SGH _hoops_GRAA _hoops_HAII _hoops_CSPH */
		state->_hoops_GAHCI = false;

	if (state->_hoops_PIGRR == _hoops_HPSGR) {
		char			_hoops_CAISI[80];
		WNDCLASS		_hoops_SAISI;

#ifndef _WIN32_WCE
		GetClassName (state->_hoops_GGICI, _hoops_CAISI, sizeof (_hoops_CAISI));
#endif
#ifdef _hoops_GPISI
	_hoops_RCSRH(_hoops_ACSRH) =
			(HINSTANCE) GetWindowLong (state->_hoops_GGICI, GWL_HINSTANCE);
#endif
#ifndef _WIN32_WCE
		GetClassInfo (_hoops_RCSRH (_hoops_ACSRH), _hoops_CAISI, &_hoops_SAISI);

		if (!BIT (_hoops_SAISI.style, CS_OWNDC))
#endif
			state->_hoops_GAHCI =	false;
	}

	/*
	 * _hoops_PS _hoops_RRP _hoops_IS _hoops_ACPA _hoops_PGAP _hoops_CSGSR _hoops_PPR _hoops_IPHCI _hoops_RIAH _hoops_IS _hoops_SGH _hoops_IH _hoops_RGR
	 * _hoops_HAGAR _hoops_IIGR _hoops_RH _hoops_RHPP
	 */
	switch (state->_hoops_PIGRR&0x0F) {
		case _hoops_HSPCI: {
			state->_hoops_CPHCI		 = &_hoops_IRSRA->_hoops_SSRCI;
			state->_hoops_HHHCI		 = &_hoops_IRSRA->_hoops_CSRCI;
			state->_hoops_RHHCI		 = &_hoops_IRSRA->_hoops_ISRCI;
			state->_hoops_SPHCI		 = &_hoops_IRSRA->_hoops_AGACI;
			state->_hoops_IHHCI	 = &_hoops_IRSRA->_hoops_RGACI;
			state->_hoops_AHHCI		 = &_hoops_IRSRA->_hoops_GGACI;
			state->_hoops_GHHCI		 = &_hoops_IRSRA->_hoops_IGACI;
			state->_hoops_CHHCI		 = &_hoops_IRSRA->_hoops_HGACI;
			state->_hoops_PHHCI		 = &_hoops_IRSRA->_hoops_PGACI;
		}	break;

		case _hoops_ISPCI: {
			state->_hoops_GSHCI._hoops_CPRCI		= NULL;
			state->_hoops_GSHCI._hoops_GPRCI			= NULL;
			state->_hoops_GSHCI._hoops_CIRHH			= 0;
			state->_hoops_GSHCI._hoops_SPRCI	= 0;

			state->_hoops_GSHCI._hoops_IPRCI	= NULL;
			state->_hoops_GSHCI._hoops_AGRCI			= NULL;
			state->_hoops_HCHCI =
				GetDeviceCaps (state->_hoops_AGICI, NUMFONTS);
			if (state->_hoops_HCHCI < 1) {
				/* _hoops_IPSRH _hoops_PGI _hoops_CPPHR _hoops_SCH _hoops_SSCP _hoops_PSP _hoops_GSPIP (_hoops_GGR _hoops_PGAP _hoops_AGIR _hoops_SR
				   _hoops_SSIA _hoops_GRS _hoops_SGH _hoops_HRRPI),	-1 _hoops_PGAP _hoops_SIGH _hoops_PCCP _hoops_PGGS
				   _hoops_PHI _hoops_IIGR _hoops_ASRCI */
				state->_hoops_HCHCI =
					65535 / sizeof (_hoops_HPRCI) - 1;
			}

			if (_hoops_IRSRA->_hoops_SSRRI < _hoops_IHRCI && state->_hoops_HCHCI > 8) {
				/* _hoops_PS _hoops_RPGAH _hoops_IS _hoops_SHH _hoops_RRGI _hoops_IRS _hoops_RPISI _hoops_HRRPI _hoops_PPAC _hoops_GHARR - _hoops_SHH _hoops_APISI
				_hoops_IIGR _hoops_RH _hoops_CIPP */
				state->_hoops_HCHCI = 8;
			}
			state->_hoops_CCHCI = 0;


			state->_hoops_RCHCI._hoops_HRRCI			= -1;
			state->_hoops_RCHCI._hoops_PRRCI		= NULL;
			state->_hoops_RCHCI._hoops_AGRCI			= NULL;

			state->_hoops_IIHCI =
				GetDeviceCaps (state->_hoops_AGICI, NUMBRUSHES);
			if (state->_hoops_IIHCI < 1) {
				/* _hoops_IPSRH _hoops_PGI _hoops_CPPHR _hoops_SCH _hoops_SSCP _hoops_PSP _hoops_ASRCI (_hoops_GGR _hoops_PGAP _hoops_AGIR _hoops_SR
				   _hoops_SSIA _hoops_GRS _hoops_SGH _hoops_HRRPI),	-1 _hoops_PGAP _hoops_SIGH _hoops_PCCP _hoops_PGGS
				   _hoops_PHI _hoops_IIGR _hoops_ASRCI */
				state->_hoops_IIHCI =
					65535 / sizeof (_hoops_ARRCI) - 1;
			}

			if (_hoops_IRSRA->_hoops_SSRRI < _hoops_IHRCI && state->_hoops_IIHCI > 8) {
				/* _hoops_PS _hoops_RPGAH _hoops_IS _hoops_SHH _hoops_RRGI _hoops_IRS _hoops_RPISI _hoops_HRRPI _hoops_PPAC _hoops_GHARR - _hoops_SHH _hoops_APISI
				_hoops_IIGR _hoops_RH _hoops_CIPP */
				state->_hoops_IIHCI = 8;
			}
			state->_hoops_SIHCI = 0;


			state->_hoops_PIHCI._hoops_IGRCI				= MAXDWORD;
			state->_hoops_PIHCI._hoops_HGRCI			= NULL;
			state->_hoops_PIHCI._hoops_AGRCI				= NULL;
			state->_hoops_SHHCI = GetDeviceCaps (state->_hoops_AGICI,
													  NUMPENS);
			if (state->_hoops_SHHCI < 1) {
				/*
				 * _hoops_IPSRH _hoops_PGI _hoops_CPPHR _hoops_SCH _hoops_SSCP _hoops_PSP _hoops_CISRI (_hoops_GGR _hoops_PGAP _hoops_AGIR _hoops_SR
				 * _hoops_SSIA _hoops_GRS _hoops_SGH _hoops_HRRPI),	-1 _hoops_PGAP _hoops_SIGH _hoops_PCCP _hoops_PGGS
				 * _hoops_PHI _hoops_IIGR _hoops_CISRI
				 */
				state->_hoops_SHHCI = 65535 / sizeof (_hoops_PGRCI) - 1;
			}

			if (_hoops_IRSRA->_hoops_SSRRI < _hoops_IHRCI && state->_hoops_SHHCI > 8) {
				/*
				 * _hoops_PS _hoops_RPGAH _hoops_IS _hoops_SHH _hoops_RRGI _hoops_IRS _hoops_RPISI _hoops_HRRPI _hoops_PPAC _hoops_GHARR - _hoops_SHH
				 * _hoops_APISI _hoops_IIGR _hoops_RH _hoops_CIPP
				 */
				state->_hoops_SHHCI = 8;
			}
			state->_hoops_RIHCI = 0;

			state->_hoops_CPHCI		= &state->_hoops_PIHCI;
			state->_hoops_HHHCI		= &state->_hoops_RIHCI;
			state->_hoops_RHHCI		= &state->_hoops_SHHCI;
			state->_hoops_SPHCI		= &state->_hoops_RCHCI;
			state->_hoops_IHHCI	= &state->_hoops_SIHCI;
			state->_hoops_AHHCI		= &state->_hoops_IIHCI;
			state->_hoops_GHHCI		= &state->_hoops_GSHCI;
			state->_hoops_CHHCI		= &state->_hoops_CCHCI;
			state->_hoops_PHHCI		= &state->_hoops_HCHCI;
		}	break;

		case _hoops_CSPCI: {
			state->_hoops_RSHCI._hoops_CPRCI		 = NULL;
			state->_hoops_RSHCI._hoops_GPRCI		 = NULL;
			state->_hoops_RSHCI._hoops_CIRHH		 = 0;
			state->_hoops_RSHCI._hoops_SPRCI	 = 0;

			state->_hoops_RSHCI._hoops_IPRCI	 = NULL;
			state->_hoops_RSHCI._hoops_AGRCI				= NULL;
			state->_hoops_ICHCI =
				GetDeviceCaps (state->_hoops_AGICI, NUMFONTS);
			if (state->_hoops_ICHCI < 1) {
				/* _hoops_IPSRH _hoops_PGI _hoops_CPPHR _hoops_SCH _hoops_SSCP _hoops_PSP _hoops_GSPIP (_hoops_GGR _hoops_PGAP _hoops_AGIR _hoops_SR
				   _hoops_SSIA _hoops_GRS _hoops_SGH _hoops_HRRPI),	-1 _hoops_PGAP _hoops_SIGH _hoops_PCCP _hoops_PGGS
				   _hoops_PHI _hoops_IIGR _hoops_ASRCI */
				state->_hoops_ICHCI =
					65535 / sizeof (_hoops_HPRCI) - 1;
			}

			if (_hoops_IRSRA->_hoops_SSRRI < _hoops_IHRCI && state->_hoops_ICHCI > 8) {
				/* _hoops_PS _hoops_RPGAH _hoops_IS _hoops_SHH _hoops_RRGI _hoops_IRS _hoops_RPISI _hoops_HRRPI _hoops_PPAC _hoops_GHARR - _hoops_SHH _hoops_APISI
				_hoops_IIGR _hoops_RH _hoops_CIPP */
				state->_hoops_ICHCI = 8;
			}
			state->_hoops_SCHCI = 0;


			state->_hoops_ACHCI._hoops_HRRCI			= -1;
			state->_hoops_ACHCI._hoops_PRRCI	= NULL;
			state->_hoops_ACHCI._hoops_AGRCI			= NULL;
			state->_hoops_CIHCI =
				GetDeviceCaps (state->_hoops_PGICI, NUMBRUSHES);
			if (state->_hoops_CIHCI < 1) {
				/* _hoops_IPSRH _hoops_PGI _hoops_CPPHR _hoops_SCH _hoops_SSCP _hoops_PSP _hoops_ASRCI (_hoops_GGR _hoops_PGAP _hoops_AGIR _hoops_SR
				   _hoops_SSIA _hoops_GRS _hoops_SGH _hoops_HRRPI),	-1 _hoops_PGAP _hoops_SIGH _hoops_PCCP _hoops_PGGS
				   _hoops_PHI _hoops_IIGR _hoops_ASRCI */
				state->_hoops_CIHCI =
					65535 / sizeof (_hoops_ARRCI) - 1;
			}

			if (_hoops_IRSRA->_hoops_SSRRI < _hoops_IHRCI && state->_hoops_CIHCI > 8) {
				/* _hoops_PS _hoops_RPGAH _hoops_IS _hoops_SHH _hoops_RRGI _hoops_IRS _hoops_RPISI _hoops_HRRPI _hoops_PPAC _hoops_GHARR - _hoops_SHH _hoops_APISI
				_hoops_IIGR _hoops_RH _hoops_CIPP */
				state->_hoops_CIHCI = 8;
			}
			state->_hoops_GCHCI = 0;
			state->_hoops_HIHCI._hoops_IGRCI				= MAXDWORD;
			state->_hoops_HIHCI._hoops_HGRCI		= NULL;
			state->_hoops_HIHCI._hoops_AGRCI				= NULL;
			state->_hoops_GIHCI = GetDeviceCaps (state->_hoops_PGICI,
													   NUMPENS);
			if (state->_hoops_GIHCI < 1) {
				state->_hoops_GIHCI = 65535 / sizeof (_hoops_PGRCI) - 1;
			}

			if (_hoops_IRSRA->_hoops_SSRRI < _hoops_IHRCI && state->_hoops_GIHCI > 8) {
				state->_hoops_GIHCI = 8;
			}
			state->_hoops_AIHCI = 0;

			state->_hoops_CPHCI		= &state->_hoops_HIHCI;
			state->_hoops_HHHCI		= &state->_hoops_AIHCI;
			state->_hoops_RHHCI		= &state->_hoops_GIHCI;
			state->_hoops_SPHCI		= &state->_hoops_ACHCI;
			state->_hoops_IHHCI	= &state->_hoops_GCHCI;
			state->_hoops_AHHCI		= &state->_hoops_CIHCI;
			state->_hoops_GHHCI		= &state->_hoops_RSHCI;
			state->_hoops_CHHCI		= &state->_hoops_SCHCI;
			state->_hoops_PHHCI		= &state->_hoops_ICHCI;
		}	break;
	}

	if (!state->_hoops_GAHCI)
		switch (state->_hoops_HGICI) {
			case _hoops_IGHCI: {
				ReleaseDC (GetDesktopWindow (), state->_hoops_PGICI);
			}	break;

			case _hoops_CGHCI: {
				DeleteDC (state->_hoops_PGICI);
			}	break;

			case _hoops_SCASA: {
				/* _hoops_ARRP _hoops_IS _hoops_AA */
			}	break;
		}


	return true;
}


/*
 * _hoops_PGAA
 */
local void _hoops_HGGAH (
	Display_Context alter	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();
	RECT						_hoops_PCRSP;
	RECT						_hoops_IGGAH;
	POINT						_hoops_CGGAH;
	HWND						_hoops_SGGAH;
	bool					_hoops_PPISI = false;


	/*
	 * _hoops_PS _hoops_RRP _hoops_IS _hoops_GRAS _hoops_RH _hoops_RPPS _hoops_PHGSP _hoops_PPR _hoops_GPAA - _hoops_SR _hoops_HS _hoops_IS
	 * _hoops_RGIC _hoops_AHCA _hoops_PPGC _hoops_IRS _hoops_CIAGR _hoops_CCPAR - _hoops_HIS _hoops_IS _hoops_IRHH _hoops_SCH _hoops_RCAC _hoops_SR
	 * _hoops_CHR _hoops_CPIC _hoops_IS _hoops_HGCR _hoops_RH _hoops_RPPS _hoops_ARRGR (_hoops_CRRPR _hoops_HCR _hoops_RGSHA _hoops_HIAHR
	 * _hoops_PPR _hoops_GPAA) _hoops_PPR _hoops_RH _hoops_RPRGR _hoops_CCAC (_hoops_SAHR _hoops_RH _hoops_HAICP _hoops_CCAC _hoops_IIGR _hoops_RH
	 * _hoops_SHPR) - _hoops_SR _hoops_GRS _hoops_GACC _hoops_SGHHR _hoops_IS _hoops_HGCR _hoops_RH _hoops_SRGAH _hoops_HCGR _hoops_SPCC _hoops_PPR
	 * _hoops_RH _hoops_ARGAH _hoops_PRGAH _hoops_HPHS
	 * _hoops_IRSC _hoops_AGCR _hoops_HRGAH _hoops_HSH _hoops_GHAP _hoops_CGH _hoops_SHH _hoops_SHSS _hoops_IS _hoops_CAHA _hoops_CPS
	 * _hoops_GGSR
	 */

	_hoops_SGGAH = state->_hoops_GGICI;

	if (_hoops_SGGAH == NULL || !IsWindow(_hoops_SGGAH)) {
		/* _hoops_AGAH _hoops_IPAC _hoops_GGSR _hoops_RH _hoops_GHARR _hoops_ARPP _hoops_SGP _hoops_RPPS */
		_hoops_SGGAH = GetDesktopWindow ();
		_hoops_PPISI = true;
	}

	GetWindowRect (_hoops_SGGAH, &_hoops_PCRSP);
	GetClientRect (_hoops_SGGAH, &_hoops_IGGAH);

	_hoops_CGGAH.x = _hoops_IGGAH.left;
	_hoops_CGGAH.y = _hoops_IGGAH.bottom;
	ClientToScreen (_hoops_SGGAH, &_hoops_CGGAH);
	_hoops_IGGAH.left = _hoops_CGGAH.x;
	_hoops_IGGAH.bottom = _hoops_CGGAH.y;

	_hoops_CGGAH.x = _hoops_IGGAH.right;
	_hoops_CGGAH.y = _hoops_IGGAH.top;
	ClientToScreen (_hoops_SGGAH, &_hoops_CGGAH);
	_hoops_IGGAH.right = _hoops_CGGAH.x;
	_hoops_IGGAH.top = _hoops_CGGAH.y;

	/*
	 * _hoops_IPCP _hoops_IRGAH _hoops_PAH _hoops_HS _hoops_ARGAH _hoops_CRGAH, _hoops_IRS _hoops_SRGAH, _hoops_IRS _hoops_IRGAH, _hoops_PPR _hoops_SPR _hoops_IIGR
	 * _hoops_HRSP _hoops_CSSC _hoops_IIGR _hoops_GPAA
	 */

	state->_hoops_HCGRR =
	state->_hoops_RCGRR =
	state->_hoops_ACGRR =
	state->_hoops_PCGRR = 0;

	if (_hoops_PPISI) {
		/* _hoops_PSRAR _hoops_PGRR _hoops_HPP _hoops_SPR _hoops_CR _hoops_SPHGR _hoops_HRGR _hoops_SPR _hoops_HAH _hoops_CASH _hoops_CCA _hoops_PSP _hoops_RPPS */
		_hoops_PCRSP.bottom--;
		_hoops_PCRSP.right--;
		_hoops_IGGAH.bottom--;
		_hoops_IGGAH.right--;
	}

	if (dc->options.border || dc->options._hoops_HRSSP) {
		if (state->_hoops_GGICI == NULL) {
			/*
			 * _hoops_AGAH _hoops_GRS _hoops_SHH _hoops_GRP _hoops_RGR _hoops_HPHS _hoops_IS _hoops_ARPR _hoops_RH _hoops_SHIR
			 *	_hoops_RPPS _hoops_HIS _hoops_SR _hoops_PIHA _hoops_PSIIR _hoops_SCH _hoops_IS _hoops_ASSS _hoops_IH _hoops_RH _hoops_HPRGR _hoops_GPAA
			 * _hoops_GAGAH _hoops_RAGAH _hoops_PPR _hoops_GPAA
			 */
#ifndef _WIN32_WCE
			if (dc->options._hoops_AASSP) {
				state->_hoops_ACGRR	 =
				state->_hoops_PCGRR	 = GetSystemMetrics (SM_CXFRAME);
				state->_hoops_RCGRR = GetSystemMetrics (SM_CYFRAME);
			}
			else {
				state->_hoops_ACGRR	 =
				state->_hoops_PCGRR		 = GetSystemMetrics (SM_CXBORDER);
				state->_hoops_RCGRR = GetSystemMetrics (SM_CYBORDER);
			}
#endif
			state->_hoops_HCGRR = state->_hoops_RCGRR +
				GetSystemMetrics (SM_CYCAPTION) - 1;
		}
		else {
			/* _hoops_PSIH _hoops_GPAA _hoops_IIGR _hoops_APRS _hoops_RPPS */
			state->_hoops_ACGRR = _hoops_PCRSP.right - _hoops_IGGAH.right;
			state->_hoops_PCGRR = _hoops_IGGAH.left - _hoops_PCRSP.left;
			state->_hoops_HCGRR = _hoops_IGGAH.top - _hoops_PCRSP.top;
			state->_hoops_RCGRR = _hoops_PCRSP.bottom - _hoops_IGGAH.bottom;
		}
	}

	if (_hoops_PPISI) {
		dc->current.extent.left = (float) _hoops_PCRSP.left;
		dc->current.extent.right = (float) _hoops_PCRSP.right;
		dc->current.extent.bottom =
			(float)(state->_hoops_CCGRR - _hoops_PCRSP.bottom);
		dc->current.extent.top = (float)(state->_hoops_CCGRR - _hoops_PCRSP.top);
	}
	else {
#if 1
		dc->current.extent.left = (float) _hoops_IGGAH.left;
		dc->current.extent.right = (float) _hoops_IGGAH.right +
			state->_hoops_ACGRR + state->_hoops_PCGRR - 1;
		dc->current.extent.bottom =
			(float)(state->_hoops_CCGRR - _hoops_IGGAH.bottom);
		dc->current.extent.top = (float)(state->_hoops_CCGRR - _hoops_IGGAH.top +
			state->_hoops_HCGRR + state->_hoops_RCGRR - 1);
#else
		dc->current.extent.left = 0.0f;
		dc->current.extent.right = (float) _hoops_PCRSP.right - 1;
		dc->current.extent.bottom = 0.0f;
		dc->current.extent.top = (float) _hoops_PCRSP.bottom - 1;
#endif
	}
}


/*
 * _hoops_PGAA
 */
local _hoops_RGHCI *_hoops_HPISI (
	int							*x,
	int							y,
	MSW_Driver_State alter			*state) {
	_hoops_RGHCI					*_hoops_ARHSI;
	LPBITMAPINFOHEADER			_hoops_GGHPR = &state->_hoops_APICI->bmiHeader;
	Display_Context const	*dc = state->dc;


	ALLOC (_hoops_ARHSI, _hoops_RGHCI);
	_hoops_ARHSI->dc = CreateCompatibleDC (state->_hoops_AGICI);
#ifndef _WIN32_WCE
	*x = ((*x + 7) & (~0x0007));

	_hoops_GGHPR->biWidth		= *x;
	_hoops_GGHPR->biHeight	= y * -1;

	*x *= _hoops_GGHPR->biBitCount / 8;
	_hoops_GGHPR->biSizeImage = *x * y;

	/* _hoops_IPISI _hoops_RH _hoops_HRASR */
	_hoops_ARHSI->bitmap = CreateDIBSection(_hoops_ARHSI->dc,
								  state->_hoops_APICI,
								  dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR ?
									  DIB_PAL_COLORS : DIB_RGB_COLORS,
								  &_hoops_ARHSI->_hoops_RCHA,
								  NULL,
								  0);

#else
	*x = ((*x + 7) & (~0x0007));

	_hoops_GGHPR->biWidth		= abs(*x);
		_hoops_GGHPR->biHeight	= abs(y+22);				//_hoops_GRHII _hoops_IH _hoops_AIGGP _hoops_AIRI

	*x *= _hoops_GGHPR->biBitCount / 8;
	_hoops_GGHPR->biSizeImage = *x * y;

	/* _hoops_IPISI _hoops_RH _hoops_HRASR */
	_hoops_GGHPR->biSize = sizeof(BITMAPINFOHEADER);
	_hoops_GGHPR->biBitCount	= 24;

	_hoops_ARHSI->_hoops_RCHA = malloc(_hoops_GGHPR->biWidth*_hoops_GGHPR->biHeight * 4 *4);

	/* _hoops_IPISI _hoops_RH _hoops_HRASR */
	_hoops_ARHSI->bitmap = CreateDIBSection(_hoops_ARHSI->dc,
								  state->_hoops_APICI,
								  DIB_RGB_COLORS,
								  &_hoops_ARHSI->_hoops_PGHCI,
								  NULL,
								  0);
	_hoops_GGHPR->biBitCount	= 32;
#endif

	_hoops_ARHSI->_hoops_AGHCI =
		(HBITMAP) SelectObject (_hoops_ARHSI->dc,
								_hoops_ARHSI->bitmap);

#ifndef _WIN32_WCE
	SetStretchBltMode (_hoops_ARHSI->dc, COLORONCOLOR);
#endif
	_hoops_ARHSI->_hoops_HGHCI=state->_hoops_CRHCI;
	state->_hoops_CRHCI = _hoops_ARHSI;


	return _hoops_ARHSI;
}


/*
 * _hoops_PGAA
 */
local void _hoops_CPISI (
	_hoops_RGHCI				*_hoops_ARHSI,
	MSW_Driver_State alter		*state) {
	_hoops_RGHCI				*_hoops_SPISI,
										*_hoops_GHISI;

	if (state->_hoops_CRHCI != NULL) {
		_hoops_SPISI = null;
		_hoops_GHISI = state->_hoops_CRHCI;
		while (_hoops_GHISI != _hoops_ARHSI) {
			_hoops_SPISI = _hoops_GHISI;
			_hoops_GHISI = _hoops_GHISI->_hoops_HGHCI;
		}
		if (_hoops_SPISI == null) {
			state->_hoops_CRHCI = _hoops_ARHSI->_hoops_HGHCI;
		}
		else {
			_hoops_SPISI->_hoops_HGHCI = _hoops_ARHSI->_hoops_HGHCI;
		}

		DeleteObject (SelectObject (_hoops_ARHSI->dc,
					  _hoops_ARHSI->_hoops_AGHCI));
		DeleteDC (_hoops_ARHSI->dc);
		FREE (_hoops_ARHSI, _hoops_RGHCI);
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_RHISI (
	Net_Rendition const & nr,
	int								width,
	int								height,
	Image_Format					format,
	Image alter * alter			*image,
	void alter * alter				*_hoops_PISCP) {
	_hoops_RGHCI alter				*_hoops_ARHSI;
	int								row_bytes;
	MSW_Driver_State alter			*state = _hoops_IICCI ();
	Display_Context const		*dc = state->dc;

	if ((format == Image_MAPPED_8 &&
		 dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) ||
		(format == _hoops_CSGSP &&
		 dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) &&
		(state->_hoops_PIGRR&0x0F) != _hoops_CSPCI) {
		row_bytes = width;
		_hoops_ARHSI = _hoops_HPISI (&row_bytes, height, state);

		/*
		 * _hoops_HSRR _hoops_RH _hoops_IHSP _hoops_HGRH _hoops_IS _hoops_IPHR _hoops_CIAH _hoops_RH _hoops_RSIR _hoops_SRHR
		 * _hoops_PPRII _hoops_SHH _hoops_PIISR _hoops_CCA 0x00'_hoops_GRI
		 */
		SET_MEMORY(_hoops_ARHSI->_hoops_RCHA, row_bytes * height, 0);

		HI_Create_Image (image,
						 null,
						 width, height,
						 format, row_bytes,
						 _hoops_SGPGI,
						 (unsigned char *) _hoops_ARHSI->_hoops_RCHA);
		HI_Validate_Inverted_Rasters (*image);

		if (format == Image_MAPPED_8) {
			int		i;
			int		_hoops_AHISI;
			_hoops_RGHCI   *_hoops_ARHSI = state->_hoops_CRHCI;

			/*
			 * _hoops_GSSRH _hoops_PHISI, _hoops_PSSP _hoops_RH _hoops_SARSI _hoops_HAIR _hoops_GASR _hoops_IS _hoops_RH
			 * _hoops_SCGR _hoops_IHCRH _hoops_IS _hoops_PSSP _hoops_RH _hoops_HHISI _hoops_IHCRH
			 */
			_hoops_AHISI = min (GetPaletteEntries (state->_hoops_GIICI, 0,
												 256, state->_hoops_RAHCI),
							  256);
			/* _hoops_IHISI, _hoops_IHCRH _hoops_AIRP _hoops_CHR _hoops_PCCIR-_hoops_ISHI-_hoops_RCSR, _hoops_CHISI _hoops_CHR _hoops_RCSR-_hoops_ISHI-_hoops_PCCIR */
			for (i = 0; i < _hoops_AHISI; ++i) {
				state->_hoops_AAHCI[i].rgbRed = state->_hoops_RAHCI[i].peRed;
				state->_hoops_AAHCI[i].rgbGreen = state->_hoops_RAHCI[i].peGreen;
				state->_hoops_AAHCI[i].rgbBlue = state->_hoops_RAHCI[i].peBlue;

				state->_hoops_AAHCI[i].rgbReserved = 0;
			}
			while (_hoops_ARHSI != null) {
#ifndef _WIN32_WCE
				SetDIBColorTable(_hoops_ARHSI->dc, 0, 256,
					state->_hoops_AAHCI);
#endif
				_hoops_ARHSI = _hoops_ARHSI->_hoops_HGHCI;
			}
		}
		*_hoops_PISCP = (void *)_hoops_ARHSI;
	}
	else {
		HD_Std_Create_Frame_Buffer (nr, width, height, format, image,
									_hoops_PISCP);
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_SHISI (
	Net_Rendition const &	nr,
	Image alter		  *image,
	void alter		  *_hoops_PISCP) {
	MSW_Driver_State alter	  *state = _hoops_IICCI ();

	if (_hoops_PISCP == null) {
	/* _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_CARS */
		HD_Std_Destroy_Frame_Buffer (nr, image, _hoops_PISCP);
	}
	else if (state != null) {
		_hoops_CPISI ((_hoops_RGHCI *)_hoops_PISCP, state);
		_hoops_HPRH (image);
	}
}


/*
 * _hoops_PGAA
 */
local void _hoops_GIISI (
	Display_Context const	*dc) {

	_hoops_APARR alter &	_hoops_RRCI = (_hoops_APARR alter &) dc->_hoops_ACPGR;


	_hoops_RRCI->_hoops_IGSSP				= _hoops_RHISI;
	_hoops_RRCI->_hoops_CGSSP			= _hoops_RRHSI;
	_hoops_RRCI->_hoops_SGSSP			= _hoops_SHISI;
}

local HDC _hoops_RIISI(char const * filename, float _hoops_AIISI, float _hoops_PIISI, int _hoops_HAP) {
	HDC retval = NULL;

	int width = _hoops_AIISI * _hoops_HAP;
	int height = _hoops_PIISI * _hoops_HAP;

	HDC _hoops_HIISI = CreateCompatibleDC(0);

	BITMAPINFOHEADER _hoops_GGHPR;
	BYTE* _hoops_IIISI = 0;
	memset(&_hoops_GGHPR, 0, sizeof(BITMAPINFOHEADER));
	_hoops_GGHPR.biWidth = width;
	_hoops_GGHPR.biHeight = height;
	_hoops_GGHPR.biSizeImage = width * height * 3;
	_hoops_GGHPR.biSize = sizeof (BITMAPINFOHEADER);
	_hoops_GGHPR.biPlanes = 1;
	_hoops_GGHPR.biBitCount = 24;
	_hoops_GGHPR.biCompression = BI_RGB;	/* _hoops_GHHSI */
	_hoops_GGHPR.biClrUsed = 8;
	HBITMAP hBitmap = CreateDIBSection(_hoops_HIISI, (BITMAPINFO*)&_hoops_GGHPR, DIB_RGB_COLORS, (void**)&_hoops_IIISI, 0, 0);

	SelectObject(_hoops_HIISI, hBitmap);
	DeleteObject(hBitmap);

#ifndef _WIN32_WCE
	retval = CreateEnhMetaFile(_hoops_HIISI, filename, NULL, NULL);
#endif

	DeleteDC(_hoops_HIISI);

	return retval;
}

local bool _hoops_CIISI(HDC _hoops_PHCIH, bool _hoops_SIISI) {
	bool result = false;
	HENHMETAFILE _hoops_GCISI;
	_hoops_GCISI = CloseEnhMetaFile(_hoops_PHCIH);

#ifndef _WIN32_WCE
	if (_hoops_SIISI) {
		if (OpenClipboard(NULL)) {
			EmptyClipboard();
			SetClipboardData (CF_ENHMETAFILE, _hoops_GCISI);
			CloseClipboard();
		} else {
			result = false;
		}
	}
#endif

	DeleteEnhMetaFile(_hoops_GCISI);
	return result;
}

/*
 * _hoops_SRAC
 */
local void get_physical_info (
	Display_Context alter	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();
	int							_hoops_AAPSR;
	bool					_hoops_RCISI;
	HDC							_hoops_AGICI;

	dc->_hoops_PGCC.flags |= _hoops_PPPGH;

	if (!state->_hoops_GAHCI)
		switch (state->_hoops_HGICI)
		{
			case _hoops_IGHCI: {
				state->_hoops_PGICI = GetDC (GetDesktopWindow ());
			}	break;

			case _hoops_CGHCI: {
				state->_hoops_PGICI =
					get_printer_DC (dc->options._hoops_ARPSR);
			}	break;

			case _hoops_SCASA: {
				 state->_hoops_PGICI = state->_hoops_AGICI =
					(HDC) dc->options._hoops_ISPRP;
			}	break;
		}


	if (state->_hoops_PIGRR == _hoops_RSPCI) {
		float width, height;

		if (dc->options._hoops_SPHSR.x != -1) {	/* _hoops_IPSP _hoops_CARSR _hoops_IGIR */
			width = dc->options._hoops_SPHSR.x/2.54f;
			height = dc->options._hoops_SPHSR.y/2.54f;
		}
		else {
			width = 8.5f;
			height = 11.0f;
		}
		dc->_hoops_PGCC.size.x = width * 2.54f;
		dc->_hoops_PGCC.size.y = height * 2.54f;
		dc->_hoops_PGCC._hoops_PRPSR.x = width * dc->options._hoops_GHHSR;
		dc->_hoops_PGCC._hoops_PRPSR.y = height * dc->options._hoops_GHHSR;
		dc->_hoops_PGCC._hoops_ARISR.x = 0;
		dc->_hoops_PGCC._hoops_ARISR.y = 0;

		state->_hoops_PHCIH = _hoops_RIISI((char*)0, width, height, dc->options._hoops_GHHSR);
		state->_hoops_IGICI = 
		state->_hoops_PGICI = 
		state->_hoops_SGICI = 
		state->_hoops_AGICI = 
		_hoops_AGICI = 
		state->_hoops_PHCIH;
	}

	_hoops_AGICI = state->_hoops_PGICI;

	if (state->_hoops_SSRRI == _hoops_PHRCI &&
		(state->_hoops_PIGRR & 0x0F) == _hoops_ISPCI) {

		state->_hoops_GPHCI = false;
		state->_hoops_PPHCI = false;
		state->_hoops_APHCI = false;
		state->_hoops_RPHCI = false;
		state->_hoops_SAHCI = false;
		state->_hoops_CAHCI = false;
		state->_hoops_IAHCI = false;
		state->_hoops_HPHCI = false;
		state->_hoops_GPCCI = false;
	}
	else
		_hoops_SCHSI (dc);


	dc->_hoops_PGCC._hoops_PIPGH = false;

	{
		int		_hoops_ACISI;

		_hoops_ACISI = GetDeviceCaps (_hoops_AGICI, TEXTCAPS);

		state->_hoops_RPICI = _hoops_CRGGH;
		if (BIT (_hoops_ACISI, TC_CR_ANY))
			state->_hoops_RPICI = _hoops_GPCSR;
		else if (BIT (_hoops_ACISI, TC_CR_90))
			state->_hoops_RPICI = _hoops_SRGGH;
	}

	{
		int		_hoops_PCISI;

		_hoops_PCISI = GetDeviceCaps (_hoops_AGICI, RASTERCAPS);

		state->_hoops_GPICI = BIT (_hoops_PCISI, RC_BITBLT);
	}

	/* _hoops_PS _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RSH _hoops_IS _hoops_HGCR _hoops_HCGR _hoops_IS _hoops_PGSA _hoops_CIPCA _hoops_SIHH _hoops_HCISI _hoops_ICISI,
	 * _hoops_HGPP _hoops_GAR _hoops_GPS _hoops_RH _hoops_SSSCI _hoops_PPR _hoops_CCISI _hoops_CAPR _hoops_GGR _hoops_CIPCA _hoops_RRI
	 */
	dc->_hoops_PGCC.flags |= _hoops_APPGH;
	dc->_hoops_PGCC._hoops_IIPGH[0] = QMoves_XOR;

	state->_hoops_AACCI = false;

	state->_hoops_PIICI = GetDeviceCaps (_hoops_AGICI, LOGPIXELSX);
	state->_hoops_HIICI = GetDeviceCaps (_hoops_AGICI, LOGPIXELSY);
	state->_hoops_RCRAP = GetDeviceCaps (_hoops_AGICI, TECHNOLOGY);
	state->planes = GetDeviceCaps (_hoops_AGICI, PLANES);
	state->_hoops_IHICI = GetDeviceCaps (_hoops_AGICI, BITSPIXEL);

	if (state->_hoops_RCRAP == DT_PLOTTER)
		state->_hoops_SRHCI = false;
	else
		state->_hoops_SRHCI = true;

	_hoops_AAPSR = GetDeviceCaps (_hoops_AGICI, NUMCOLORS);
	if (_hoops_AAPSR < 0)
		_hoops_AAPSR = _hoops_GPARA;
	state->_hoops_PHICI = BIT (GetDeviceCaps (_hoops_AGICI, RASTERCAPS), RC_PALETTE);

	if (state->_hoops_CRICI) {
		state->_hoops_PHICI = false;
		_hoops_AAPSR = 1<<24;
	}

	/* _hoops_SCISI _hoops_HCR _hoops_HISRA _hoops_SIH _hoops_CRGR _hoops_IRGH _hoops_PIAP _hoops_HRPR */
	state->_hoops_GGCCI = !BIT (dc->options._hoops_IRARR, _hoops_ICACI);

	/*
	 * _hoops_CGP _hoops_RH _hoops_GHARR _hoops_HRGR _hoops_GRP _hoops_SRGH _hoops_IHCRH _hoops_PSCR _hoops_SR _hoops_RRP _hoops_IS _hoops_IRHH _hoops_RCRR
	 * _hoops_RH _hoops_SRS 10 _hoops_CHR _hoops_CIH _hoops_HPP _hoops_PRPRA _hoops_AGAH _hoops_HAR _hoops_IS _hoops_SGH _hoops_CAPR
	 */
#ifndef _WIN32_WCE
	if (state->_hoops_PHICI && state->_hoops_GGCCI &&
		dc->options._hoops_APASR == 0 &&
		GetSystemPaletteUse (_hoops_AGICI) != SYSPAL_NOSTATIC) {
		/* _hoops_PS _hoops_RRP _hoops_IS _hoops_PARRH _hoops_CHARP _hoops_HAIR _hoops_IPI _hoops_IRS _hoops_RSCA */
		dc->_hoops_PGCC._hoops_APASR = 10;
		dc->_hoops_PGCC._hoops_AAPSR = 236;
	}
#else
   state->_hoops_PHICI = false;
#endif
		
	/*
	 * _hoops_RHCS _hoops_IH _hoops_PIHRH _hoops_CAGRH - _hoops_IHPR _hoops_HAIR _hoops_SIRSI _hoops_RRGI _hoops_HPPCI _hoops_CHR _hoops_RCCAR
	 * 1 _hoops_IGRH _hoops_IPPA,	 1 _hoops_AIR _hoops_RIR _hoops_IPPA,	 8 _hoops_PSHA _hoops_PPR _hoops_PSP _hoops_IHCRH - _hoops_SR _hoops_GRS _hoops_SAHR
	 * _hoops_HHSA _hoops_RGR _hoops_AARRA _hoops_IS _hoops_SHH _hoops_IHPR _hoops_HAIR
	 */

	if (state->_hoops_SSRRI == _hoops_IHRCI &&
		state->planes == 1 &&
		state->_hoops_IHICI == 1 &&
		_hoops_AAPSR == 8 &&
		!state->_hoops_PHICI) {
		/* _hoops_AIAP _hoops_IHPR _hoops_HAIR _hoops_CCH */
		_hoops_AAPSR = 1<<24;
	}

	if (state->_hoops_PHICI) {
		/* _hoops_GSISI _hoops_HPHS _hoops_SR _hoops_GRS _hoops_RRP _hoops_GGR _hoops_RH _hoops_IIHSR _hoops_HCPC _hoops_CHPGH _hoops_PCGC */
		state->_hoops_HHICI = GetDeviceCaps (_hoops_AGICI, SIZEPALETTE);
		dc->_hoops_PGCC._hoops_AAPSR = state->_hoops_HHICI -
										GetDeviceCaps (_hoops_AGICI, NUMRESERVED);
	}
	else {
		/* _hoops_PS _hoops_PAH _hoops_HGGC _hoops_ARPR _hoops_IRS _hoops_SICHR _hoops_IHCRH _hoops_IH _hoops_RH _hoops_SISS */
		dc->_hoops_PGCC._hoops_AAPSR = _hoops_AAPSR;
	}

	if (dc->options._hoops_AAPSR != 0) {
		state->_hoops_HHICI = _hoops_AHIA (state->_hoops_HHICI,
								   dc->options._hoops_APASR +
									   dc->options._hoops_AAPSR);
	}

	/*
	 * _hoops_HGH _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_IIGRP _hoops_CSRA _hoops_SISS
	 */
	{
		DWORD	_hoops_RSISI;
		BYTE	r;
		BYTE	g;
		BYTE	b;

		_hoops_RSISI = GetNearestColor (_hoops_AGICI, _hoops_SRASI(255, 0, 0));
		r = GetRValue (_hoops_RSISI);
		g = GetBValue (_hoops_RSISI);
		b = GetGValue (_hoops_RSISI);

		_hoops_RCISI = (r==g && r==b && dc->_hoops_PGCC._hoops_AAPSR > 2);
	}

	/*
	 *	_hoops_AIHHP _hoops_RPP
	 *	1) _hoops_ASISI
	 *
	 *	_hoops_CHPGH _hoops_RPP
	 *	1) _hoops_CSH _hoops_IHCRH
	 *	2) _hoops_HAH _hoops_CIAGR _hoops_HHPA _hoops_IHCRH _hoops_AIRP
	 *
	 *	_hoops_IIHSR _hoops_RPP
	 *	1) _hoops_SSCP _hoops_IHCRH
	 *	2) _hoops_SSCP _hoops_IRS _hoops_GHACA _hoops_PHI _hoops_IIGR _hoops_AIRP _hoops_HHPA _hoops_GGR _hoops_IHCRH (>4096)
	 *
	 */
	if (_hoops_RCISI && !state->_hoops_CRICI) {
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_RIIHP;

		state->_hoops_SCICI		   = _hoops_PPASI;
		state->_hoops_RSICI	   = _hoops_RAASI;
		state->_hoops_ASICI		   = _hoops_IAASI;
		dc->_hoops_ACPGR->draw_dc_polydot= _hoops_AHPSI;

		dc->_hoops_PGCC._hoops_PCHSR = _hoops_AHIA (_hoops_AAPSR, 256);
	}
	else if (state->_hoops_PHICI && !state->_hoops_CRICI &&
			 ((state->_hoops_PIGRR & 0x0F) != _hoops_ISPCI)) {
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_SIHSR;

		state->_hoops_SCICI		   = _hoops_SAASI;
		state->_hoops_RSICI	   = _hoops_GAASI;
		state->_hoops_ASICI		   = _hoops_HAASI;
		dc->_hoops_ACPGR->draw_dc_polydot= _hoops_RHPSI;
	}
	else {
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;

		state->_hoops_SCICI		   = _hoops_CAASI;
		state->_hoops_RSICI	   = _hoops_CRASI;
		state->_hoops_ASICI		   = _hoops_PAASI;
		dc->_hoops_ACPGR->draw_dc_polydot= _hoops_GHPSI;

		/*
		 * _hoops_AGGA _hoops_SR _hoops_HS _hoops_SPR _hoops_GASAR _hoops_SGGHR _hoops_IS _hoops_RGIC _hoops_AHCA - _hoops_RPP _hoops_RH
		 * _hoops_ACRSP _hoops_SISS _hoops_HRGR _hoops_CPSA _hoops_HAR _hoops_IRS _hoops_PSISI _hoops_SISS, _hoops_SR _hoops_RRP
		 * _hoops_IS _hoops_CRGS _hoops_AGAH _hoops_IS _hoops_HSPAA _hoops_IHHH _hoops_AHRH _hoops_GAR _hoops_HSISI _hoops_HIS _hoops_SGS
		 * _hoops_SR _hoops_PAH _hoops_SRCH _hoops_GHHS _hoops_ISISI _hoops_GGR _hoops_ISCP _hoops_IIPR
		 */
		if ((long) dc->_hoops_PGCC._hoops_AAPSR < 4096 &&
			(state->_hoops_PIGRR & 0x0F) != _hoops_ISPCI) {
			dc->_hoops_PGCC.flags |= _hoops_IAPGH;
			dc->_hoops_PGCC._hoops_CIPGH.r =
				dc->_hoops_PGCC._hoops_CIPGH.g =
				dc->_hoops_PGCC._hoops_CIPGH.b = 2;
			dc->_hoops_PGCC._hoops_SIPGH = 0;
		}

		/*
		 * _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_RSAIP.	_hoops_RHRPA _hoops_GPRI, _hoops_ISHHH _hoops_AHRH _hoops_GPP _hoops_CSISI
		 * _hoops_SIRSI _hoops_RHAP _hoops_HAR _hoops_IPHR.	_hoops_HGI _hoops_HCPH _hoops_GGSR _hoops_IS
		 * _hoops_SSISI _hoops_IS _hoops_SPSHH _hoops_PPR _hoops_SRGAI _hoops_GGCSI _hoops_AHRH.
		 */
		if (((state->_hoops_PIGRR == _hoops_ASPCI) ||
			 (state->_hoops_PIGRR == _hoops_GSPCI))  &&
			 (dc->_hoops_PGCC._hoops_AAPSR < 3)) {
			dc->_hoops_ACPGR->draw_dc_rgb32_rasters = _hoops_SSPSI;
		}
	}

	/*
	 * _hoops_PIAP->_hoops_RGCSI _hoops_CGH _hoops_SHH _hoops_IHPR _hoops_RGAR _hoops_IH _hoops_ISHHH.
	 * _hoops_AIAP _hoops_IHPR _hoops_HAIR _hoops_HIS _hoops_HRRPI _hoops_GRS _hoops_SPSHH _hoops_IH _hoops_IHHH _hoops_CGPR _hoops_SCH _hoops_GIHII _hoops_IS
	 * _hoops_IRS _hoops_APRP & _hoops_PGS _hoops_PAR _hoops_IIGRP _hoops_CSRA _hoops_GRGAI.
	 */
	if (state->_hoops_IRICI) {
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	}

	if ((state->_hoops_IRICI) && (state->_hoops_GAICI) && (state->_hoops_PHICI)) {
		dc->_hoops_PGCC._hoops_PIHSR = _hoops_SIHSR;
		dc->_hoops_ACPGR->_hoops_CCCSR = _hoops_PAHSI;
	}



	/*
	 * _hoops_AGCSI _hoops_AAPA _hoops_PAPA _hoops_IIGR _hoops_RH _hoops_HAICP _hoops_CCAC _hoops_IIGR _hoops_RH _hoops_SISS -
	 * _hoops_RACRR _hoops_HGRH _hoops_HRGR _hoops_GCIS _hoops_IS _hoops_ASSS _hoops_PGCSI _hoops_CCA _hoops_RH _hoops_PSP _hoops_HGPC _hoops_HCSP
	 * _hoops_IS _hoops_SHH _hoops_ARP _hoops_IS _hoops_RH _hoops_IHIR _hoops_CPHSR _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_RPAAI, _hoops_HAR _hoops_SAHR _hoops_RH
	 * _hoops_GPAAI _hoops_CCAC
	 */

	if (state->_hoops_PIGRR != _hoops_RSPCI) {
		/* _hoops_SIPR _hoops_RH _hoops_CCAC _hoops_SGS _hoops_SPHGR _hoops_CPPHR _hoops_HRGR _hoops_GPAAI */
		dc->_hoops_PGCC._hoops_PRPSR.x = GetDeviceCaps (_hoops_AGICI, HORZRES);
		dc->_hoops_PGCC._hoops_PRPSR.y = GetDeviceCaps (_hoops_AGICI, VERTRES);

		dc->_hoops_PGCC.size.x = GetDeviceCaps (_hoops_AGICI, HORZSIZE) / 10.0f;
		
		/* _hoops_HR _hoops_IGAA _hoops_GGSP _hoops_PPR _hoops_AIR _hoops_CHR _hoops_RRAA */
		dc->_hoops_PGCC.size.y = (float) dc->_hoops_PGCC._hoops_PRPSR.y /
			(float) dc->_hoops_PGCC._hoops_PRPSR.x * dc->_hoops_PGCC.size.x;
	}
#if 0
	/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_CCIH _hoops_IH _hoops_HGCSI _hoops_GIAIA _hoops_SGS _hoops_IHSA _hoops_ISHHH */
	if (dc->_hoops_PGCC._hoops_PRPSR.x<dc->_hoops_PGCC._hoops_PRPSR.y) {
		float size = dc->_hoops_PGCC.size.x ;
		dc->_hoops_PGCC.size.x = dc->_hoops_PGCC.size.y;
		dc->_hoops_PGCC.size.y = size;
	}
#endif

	if (!state->_hoops_SRICI) {
		dc->_hoops_PGCC._hoops_CHHSR = _hoops_ACPGA;
		state->_hoops_SRRRR = dc->options._hoops_SRRRR;
	}
	else {
		dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
		state->_hoops_SRRRR = false;
	}

#ifndef _WIN32_WCE
	{
		if (!dc->options.border && (state->_hoops_PIGRR == _hoops_GSPCI || state->_hoops_PIGRR == _hoops_ASPCI)){
			POINT _hoops_IGCSI, _hoops_CGCSI;
			Escape (_hoops_AGICI, GETPHYSPAGESIZE, 0, (LPSTR)NULL, &_hoops_IGCSI);
			Escape (_hoops_AGICI, GETPRINTINGOFFSET, 0, (LPSTR)NULL, &_hoops_CGCSI);

			dc->_hoops_PGCC._hoops_PRPSR.x = _hoops_IGCSI.x - 2*_hoops_CGCSI.x;
			dc->_hoops_PGCC._hoops_PRPSR.y = _hoops_IGCSI.y - 2*_hoops_CGCSI.y;
		}
	}
#endif

	/*
	 * _hoops_HSRR _hoops_SIRSI, _hoops_SR _hoops_RRP _hoops_IS _hoops_SRPA _hoops_RH _hoops_HSGP _hoops_SAAA _hoops_HIS
	 * _hoops_SGS _hoops_APGR _hoops_CHCC _hoops_HPP _hoops_AAPA _hoops_PAPA _hoops_PAH _hoops_SHH _hoops_SGCSI
	 */
	if (state->_hoops_PIGRR == _hoops_GSPCI ||
		state->_hoops_PIGRR == _hoops_ASPCI) {
		dc->_hoops_PGCC._hoops_ICPGH = (float)dc->_hoops_PGCC._hoops_PRPSR.x / 1024.0f;
		dc->_hoops_PGCC._hoops_CCPGH = ((float)(GetDeviceCaps(state->_hoops_AGICI, HORZRES)+GetDeviceCaps(state->_hoops_AGICI, VERTRES)))/3000.0f;
		dc->_hoops_PGCC._hoops_PIPGH = true;
		dc->_hoops_PGCC.flags |= _hoops_GGISR;
		if (state->_hoops_GAICI)
			dc->_hoops_PGCC._hoops_CCPGH *= 5;
	}
	if (dc->_hoops_PGCC._hoops_CCPGH == 0.0f)
		dc->_hoops_PGCC._hoops_CCPGH = 1.0f;
	if (dc->_hoops_PGCC._hoops_ICPGH == 0.0f)
		dc->_hoops_PGCC._hoops_ICPGH = 1.0f;

	if (state->_hoops_PIGRR == _hoops_PSPCI ||
		state->_hoops_PIGRR == _hoops_RSPCI) {
		dc->_hoops_PGCC.flags &= ~_hoops_CCHSR;
		dc->_hoops_PGCC.flags |= _hoops_IPPGH;
	}

	if (state->_hoops_PIGRR == _hoops_GSPCI	 ||
		state->_hoops_PIGRR == _hoops_ASPCI) {
		dc->_hoops_PGCC.flags |= _hoops_CCHSR;
		dc->_hoops_PGCC.flags |= _hoops_IPPGH;
	}


	/* _hoops_GRCSI _hoops_HRGR _hoops_IGI _hoops_IH _hoops_RH _hoops_ASGH _hoops_ISRR-_hoops_RRCSI _hoops_HAISR */
	state->_hoops_CCGRR =
	state->yfudge = max (0, dc->_hoops_PGCC._hoops_PRPSR.y - 1);

	/*
	 * _hoops_RAGAH _hoops_PPR _hoops_GPAA _hoops_CHR _hoops_HGAS _hoops_GGR _hoops_ARI
	 */
	if (state->_hoops_PIGRR == _hoops_PSPCI ||
		state->_hoops_PIGRR == _hoops_RSPCI	 ||
		state->_hoops_PIGRR == _hoops_GSPCI	 ||
		state->_hoops_PIGRR == _hoops_ASPCI) {
		state->_hoops_ACGRR	 =
		state->_hoops_PCGRR	 =
		state->_hoops_HCGRR	 =
		state->_hoops_RCGRR = 0;
	}
	else
		_hoops_HGGAH (dc);

	state->_hoops_PRCCI = 4096+1;

	/*_hoops_ARCSI!!! _hoops_AA _hoops_HAR _hoops_HASIR _hoops_PAR _hoops_SHS*/
	state->_hoops_HRCCI[_hoops_HGCCI] = 666;
	state->_hoops_HRCCI[_hoops_IGCCI]	= state->_hoops_PRCCI - 1;
	state->_hoops_HRCCI[_hoops_CGCCI]		= state->_hoops_PRCCI - 1;
	state->_hoops_HRCCI[_hoops_SGCCI]			= state->_hoops_PRCCI - 1;
	state->_hoops_HRCCI[_hoops_GRCCI]	= state->_hoops_PRCCI - 1;

	/*_hoops_SIGP _hoops_CCRSA _hoops_SRHR _hoops_PPR _hoops_RPGP*/
	state->_hoops_APHCI = false;
	state->_hoops_PPHCI = false;


	ALLOC_ARRAY(state->points, state->_hoops_PRCCI, POINT);
	ALLOC_ARRAY(state->_hoops_CRCCI, state->_hoops_PRCCI/2, int);

	dc->_hoops_PGCC._hoops_ICHSR = "frame buffer";
	dc->_hoops_PGCC.driver_type  = "MSWindows";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.790 $";
	dc->_hoops_PGCC.flags |= _hoops_HSHSR;
	dc->_hoops_PGCC.flags |= _hoops_SAPGH;
	dc->_hoops_PGCC.flags |= _hoops_PSHSR;

	if (GetSystemMetrics (SM_MOUSEPRESENT) != 0)
		dc->_hoops_PGCC.flags |= _hoops_RSHSR;
	else
		dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;

	dc->_hoops_PGCC.flags |= _hoops_GIHSR;
#ifndef _WIN32_WCE
	dc->_hoops_PGCC._hoops_ASHSR = GetSystemMetrics (SM_CMOUSEBUTTONS);
#endif

	if (!state->_hoops_GAHCI)
		switch (state->_hoops_HGICI) {
			case _hoops_IGHCI: {
				ReleaseDC (GetDesktopWindow (), state->_hoops_PGICI);
			}	break;

			case _hoops_CGHCI: {
				DeleteDC (state->_hoops_PGICI);
			}	break;

			case _hoops_SCASA: {
				/* _hoops_ARRP _hoops_IS _hoops_AA */
			}	break;
		}

	state->_hoops_PIHSR = dc->_hoops_PGCC._hoops_PIHSR;

	if (state->_hoops_PIGRR == _hoops_RSPCI) {
		_hoops_CIISI(state->_hoops_PHCIH, false);
		state->_hoops_IGICI = state->_hoops_PGICI = state->_hoops_SGICI = 
		state->_hoops_AGICI = state->_hoops_PHCIH = 0;
	}

}

local void _hoops_PRCSI (Display_Context const * dc){

	MSW_Driver_State alter			*state = _hoops_HICCI ();
	int const width = state->_hoops_IHGRR->width;
	int const height = state->_hoops_IHGRR->height;
	HENHMETAFILE _hoops_GCISI = CloseEnhMetaFile(state->_hoops_PHCIH);
	HDC _hoops_HIISI = CreateCompatibleDC(0);

	int _hoops_HRCSI = 0;
	switch(state->_hoops_IHGRR->format){
		case _hoops_HHGH:
			_hoops_HRCSI = 3;
			break;

		case _hoops_HRSRH:
		case Image_RGBA32:
			_hoops_HRCSI = 4;
		break;

		default:
			ASSERT(0 && "Image in unexpected format");
	}

	BITMAPINFOHEADER _hoops_GGHPR;
	BYTE* _hoops_IIISI = 0;
	memset(&_hoops_GGHPR, 0, sizeof(BITMAPINFOHEADER));
	_hoops_GGHPR.biWidth = width;
	_hoops_GGHPR.biHeight = height;
	_hoops_GGHPR.biSizeImage = width * height * _hoops_HRCSI;
	_hoops_GGHPR.biSize = sizeof (BITMAPINFOHEADER);
	_hoops_GGHPR.biPlanes = 1;
	_hoops_GGHPR.biBitCount = 8 * _hoops_HRCSI;
	_hoops_GGHPR.biCompression = BI_RGB;	/* _hoops_GHHSI */
	_hoops_GGHPR.biClrUsed = 8;
	HBITMAP hBitmap = CreateDIBSection(_hoops_HIISI, (BITMAPINFO*)&_hoops_GGHPR, DIB_RGB_COLORS, (void**)&_hoops_IIISI, 0, 0);

	SelectObject(_hoops_HIISI, hBitmap);
	DeleteObject(hBitmap);

	RECT rect;
	rect.bottom = height;
	rect.right = width;
	rect.top =
	rect.left = 0;

	HI_Clear_Image_Cache(state->_hoops_IHGRR);
	HI_Set_Delayed_Activity (state->_hoops_IHGRR->owner, _hoops_IHSSR,
							 state->_hoops_IHGRR, _hoops_HHSSR);

	PlayEnhMetaFile(_hoops_HIISI, _hoops_GCISI, &rect);

	unsigned char * _hoops_PHGH = (unsigned char*)state->_hoops_IHGRR->_hoops_PHGH;

	for(int row = 0; row < height; ++row){
		int const _hoops_AHPCP = state->_hoops_IHGRR->format * width * row;
		int const _hoops_GIHSI = state->_hoops_IHGRR->format * width * (height - row - 1);
		for(int col = 0; col < width; ++col){
			_hoops_PHGH[_hoops_AHPCP + 3 * col + 0] = _hoops_IIISI[_hoops_GIHSI + 3 * col + 2];
			_hoops_PHGH[_hoops_AHPCP + 3 * col + 1] = _hoops_IIISI[_hoops_GIHSI + 3 * col + 1];
			_hoops_PHGH[_hoops_AHPCP + 3 * col + 2] = _hoops_IIISI[_hoops_GIHSI + 3 * col + 0];
		}
	}

	DeleteDC(_hoops_HIISI);
}


/*
 * _hoops_SRAC
 */
local void stop_device (
	Display_Context alter	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();

	/*_hoops_ASIGA _hoops_PCPA?*/
	if (!state) return;

#ifndef _WIN32_WCE
	if (state->_hoops_AGICI !=null &&
		GetObjectType ((HGDIOBJ) state->_hoops_AGICI) == OBJ_METADC)
		ReleaseDC (state->_hoops_GGICI, state->_hoops_PGICI);
#endif
	/* _hoops_RCSH _hoops_GII _hoops_ASSRH _hoops_SHCA'_hoops_GRI _hoops_SR _hoops_SPIP */
	if (state->_hoops_GAHCI)
		switch (state->_hoops_PIGRR) {
			case _hoops_RSPCI:
				/* _hoops_RPP !_hoops_IRCSI _hoops_PSCR _hoops_IPS _hoops_IS _hoops_CHACI */
				_hoops_CIISI(state->_hoops_PHCIH, !state->_hoops_PCHCI);
				if(state->_hoops_IHGRR)
					_hoops_HPRH (state->_hoops_IHGRR);
			case _hoops_PPSGR:
			case _hoops_GSPCI:
			case _hoops_HPSGR:
			case _hoops_PSPCI: {
				ReleaseDC (GetDesktopWindow (), state->_hoops_PGICI);
			}	break;

			default: {
				/* _hoops_AA _hoops_ISAP _hoops_IH _hoops_HIASR? */
			}
	}

	DeleteObject (state->_hoops_AAICI);
	DeleteObject (state->_hoops_PAICI);


	if (BIT (state->_hoops_PIGRR, _hoops_HSPCI)) {
		/*
		 * _hoops_PS _hoops_RGAR _hoops_RCSH _hoops_CISRI, _hoops_ASRCI _hoops_PPR _hoops_GSPIP _hoops_SGS _hoops_SR _hoops_HS _hoops_PACIA
		 * _hoops_CRGR _hoops_ISCP _hoops_SHCA'_hoops_GRI _hoops_ARI _hoops_PPR _hoops_GGAS _hoops_ISCP "_hoops_IPI" _hoops_AIRP _hoops_GGR
		 * _hoops_RH _hoops_IPSP _hoops_CPCI - _hoops_HCR _hoops_SPHGR _hoops_RRGI _hoops_SPR _hoops_GHARR _hoops_CISPP
		 * _hoops_HSSRR _hoops_RH _hoops_PSHR _hoops_ASRCI _hoops_PPR _hoops_CISRI
		 */
		{
			_hoops_HPRCI alter	*_hoops_GHHCI;
			_hoops_HPRCI alter	*_hoops_HSICI;
			_hoops_PPRCI alter		*_hoops_ISGSI;
			_hoops_PPRCI			*_hoops_AGRCI;

			_hoops_HSICI = state->_hoops_GHHCI;
			_hoops_GHHCI = _hoops_HSICI->_hoops_IPRCI;

			while (_hoops_GHHCI != NULL) {
				_hoops_ISGSI = _hoops_GHHCI->_hoops_AGRCI;

				while (_hoops_ISGSI != NULL) {
					/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_GPHHR */
					if (_hoops_ISGSI->dc == dc) {
						/*
						 * _hoops_CRCSI _hoops_SR _hoops_CHR _hoops_GRP _hoops_SCH, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_RCSH _hoops_SCH
						 */
						if (state->_hoops_GAHCI)
							_hoops_IHRSI (dc);
					}

					/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_AGGAR */
					_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					_hoops_GHHCI->_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					if (_hoops_ISGSI->_hoops_AGRCI != NULL)
							_hoops_ISGSI->_hoops_AGRCI->_hoops_AGRCI =
								_hoops_ISGSI->_hoops_AGRCI;
					FREE (_hoops_ISGSI, _hoops_PPRCI);
					_hoops_ISGSI = _hoops_AGRCI;
				}

				if (_hoops_GHHCI == null) {
					_hoops_GHHCI = _hoops_HSICI->_hoops_IPRCI;
				}
				_hoops_HSICI = _hoops_GHHCI;
				_hoops_GHHCI = _hoops_GHHCI->_hoops_IPRCI;
			}
		}
		{
			_hoops_ARRCI alter	*_hoops_SPHCI;
			_hoops_ARRCI alter	*_hoops_HSICI;
			_hoops_RRRCI alter	*_hoops_ISGSI;
			_hoops_RRRCI			*_hoops_AGRCI;

			_hoops_HSICI = state->_hoops_SPHCI;
			_hoops_SPHCI = _hoops_HSICI->_hoops_PRRCI;

			while (_hoops_SPHCI != NULL) {
				_hoops_ISGSI = _hoops_SPHCI->_hoops_AGRCI;

				while (_hoops_ISGSI != NULL) {
					/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_GPHHR */
					if (_hoops_ISGSI->dc == dc) {
						/*
						 * _hoops_CRCSI _hoops_SR _hoops_CHR _hoops_GRP _hoops_SCH, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_RCSH _hoops_SCH
						 */
						if (state->_hoops_GAHCI)
							_hoops_PCGSI (dc);
					}

					/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_AGGAR */
					_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					_hoops_SPHCI->_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					if (_hoops_ISGSI->_hoops_AGRCI != NULL)
							_hoops_ISGSI->_hoops_AGRCI->_hoops_AGRCI =
								_hoops_ISGSI->_hoops_AGRCI;
					FREE (_hoops_ISGSI, _hoops_RRRCI);
					_hoops_ISGSI = _hoops_AGRCI;
				}

				if (_hoops_SPHCI == null) {
					_hoops_SPHCI = _hoops_HSICI->_hoops_PRRCI;
				}
				_hoops_HSICI = _hoops_SPHCI;
				_hoops_SPHCI = _hoops_SPHCI->_hoops_PRRCI;
			}
		}
		{
			_hoops_PGRCI alter	  *_hoops_CPHCI;
			_hoops_PGRCI alter	  *_hoops_HSICI;
			_hoops_RGRCI alter	  *_hoops_ISGSI;
			_hoops_RGRCI		  *_hoops_AGRCI;

			_hoops_HSICI = state->_hoops_CPHCI;
			_hoops_CPHCI = _hoops_HSICI->_hoops_HGRCI;

			while (_hoops_CPHCI != NULL) {
				_hoops_ISGSI = _hoops_CPHCI->_hoops_AGRCI;

				while (_hoops_ISGSI != NULL) {
					/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_GPHHR */
					_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					if (_hoops_ISGSI->dc == dc) {
						/*
						* _hoops_CRCSI _hoops_SR _hoops_CHR _hoops_GRP _hoops_SCH, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_RCSH _hoops_SCH
						*/
						if (state->_hoops_GAHCI)
							_hoops_IPRSI (dc);
					}

					/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_AGGAR */
					_hoops_CPHCI->_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					if (_hoops_ISGSI->_hoops_AGRCI != NULL)
							_hoops_ISGSI->_hoops_AGRCI->_hoops_AGRCI =
								_hoops_ISGSI->_hoops_AGRCI;
					FREE (_hoops_ISGSI, _hoops_RGRCI);
					_hoops_ISGSI = _hoops_AGRCI;
				}

				if (_hoops_CPHCI == null) {
					_hoops_CPHCI = _hoops_HSICI->_hoops_HGRCI;
				}
				_hoops_HSICI = _hoops_CPHCI;
				_hoops_CPHCI = _hoops_CPHCI->_hoops_HGRCI;
			}
		}
	}
	else {
		/*
		 * _hoops_CPGP _hoops_RGR _hoops_HRGR _hoops_PGI _hoops_IRS _hoops_SRCSI _hoops_PAR _hoops_IRS _hoops_SRPSR _hoops_SR _hoops_AA _hoops_HAR _hoops_HSSRR
		 * _hoops_PAR _hoops_HPPR _hoops_IS _hoops_HRSPA _hoops_GACSI/_hoops_ASRCI _hoops_GAPA _hoops_HCPH _hoops_CR _hoops_SSIA _hoops_CHR
		 * _hoops_RHPP _hoops_SASI
		 */
		{
			/* _hoops_CIH _hoops_HCR _hoops_RH _hoops_GSPIP */
			_hoops_HPRCI alter	*_hoops_GHHCI;
			_hoops_HPRCI alter	*_hoops_HSICI;
			_hoops_PPRCI alter		*_hoops_ISGSI;
			_hoops_PPRCI			*_hoops_AGRCI;

			_hoops_HSICI = state->_hoops_GHHCI;
			_hoops_GHHCI = _hoops_HSICI->_hoops_IPRCI;

			while (_hoops_GHHCI != NULL) {
				_hoops_ISGSI = _hoops_GHHCI->_hoops_AGRCI;

				while (_hoops_ISGSI != NULL) {
					/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_GPHHR */
					_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					_hoops_GHHCI->_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					if (_hoops_ISGSI->_hoops_AGRCI != NULL)
							_hoops_ISGSI->_hoops_AGRCI->_hoops_AGRCI =
								_hoops_ISGSI->_hoops_AGRCI;
					FREE (_hoops_ISGSI, _hoops_PPRCI);
					_hoops_ISGSI = _hoops_AGRCI;
				}
				_hoops_CHRSI (state, _hoops_GHHCI, _hoops_HSICI);
				_hoops_GHHCI = _hoops_HSICI->_hoops_IPRCI;
			}
		}
		{
			/* _hoops_CIH _hoops_HCR _hoops_RH _hoops_ASRCI */
			_hoops_ARRCI alter	*_hoops_SPHCI;
			_hoops_ARRCI alter	*_hoops_HSICI;
			_hoops_RRRCI alter	*_hoops_ISGSI;
			_hoops_RRRCI			*_hoops_AGRCI;

			_hoops_HSICI = state->_hoops_SPHCI;
			_hoops_SPHCI = _hoops_HSICI->_hoops_PRRCI;

			while (_hoops_SPHCI != NULL) {
				_hoops_ISGSI = _hoops_SPHCI->_hoops_AGRCI;

				while (_hoops_ISGSI != NULL) {
					/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_GPHHR */
					_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					_hoops_SPHCI->_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					if (_hoops_ISGSI->_hoops_AGRCI != NULL)
							_hoops_ISGSI->_hoops_AGRCI->_hoops_AGRCI =
								_hoops_ISGSI->_hoops_AGRCI;
					FREE (_hoops_ISGSI, _hoops_RRRCI);
					_hoops_ISGSI = _hoops_AGRCI;
				}
				_hoops_ISICI (state, _hoops_SPHCI, _hoops_HSICI);
				_hoops_SPHCI = _hoops_HSICI->_hoops_PRRCI;
			}
		}
		{
			_hoops_PGRCI alter	  *_hoops_CPHCI;
			_hoops_PGRCI alter	  *_hoops_HSICI;
			_hoops_RGRCI alter	  *_hoops_ISGSI;
			_hoops_RGRCI			*_hoops_AGRCI;
			_hoops_HSICI = state->_hoops_CPHCI;
			_hoops_CPHCI = _hoops_HSICI->_hoops_HGRCI;

			while (_hoops_CPHCI != NULL) {
				_hoops_ISGSI = _hoops_CPHCI->_hoops_AGRCI;

				while (_hoops_ISGSI != NULL) {
					/* _hoops_AGGA _hoops_HASIR _hoops_RH _hoops_GPHHR */
					_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					_hoops_CPHCI->_hoops_AGRCI = _hoops_ISGSI->_hoops_AGRCI;
					if (_hoops_ISGSI->_hoops_AGRCI != NULL)
							_hoops_ISGSI->_hoops_AGRCI->_hoops_AGRCI =
								_hoops_ISGSI->_hoops_AGRCI;
					FREE (_hoops_ISGSI, _hoops_RGRCI);
					_hoops_ISGSI = _hoops_AGRCI;
				}
				_hoops_PSICI (state, _hoops_CPHCI, _hoops_HSICI);
				_hoops_CPHCI = _hoops_HSICI->_hoops_HGRCI;
			}
		}
	}

	/* _hoops_IPPRA _hoops_RPPS _hoops_PSSRH _hoops_RPP _hoops_RGCI _hoops_ARP */
	if (state->_hoops_PIGRR == _hoops_HPSGR &&
		state->_hoops_GIGRR != NULL) {

#ifdef _WIN64
		SetWindowLongPtr (state->_hoops_GGICI, GWLP_WNDPROC,
					   (LONG_PTR)state->_hoops_GIGRR);
#else
		SetWindowLong (state->_hoops_GGICI, GWL_WNDPROC,
					   (unsigned long)state->_hoops_GIGRR);
#endif
		state->_hoops_GIGRR = NULL;
	}


	/*_hoops_RGR _hoops_CRRHP _hoops_RH _hoops_IRGH _hoops_HRCSR _hoops_HIGR*/
	{
		_hoops_SGRRR * _hoops_HSSRH = state->_hoops_GRRRR;
		_hoops_SGRRR * _hoops_ISSRH;

		while (_hoops_HSSRH) {

			_hoops_ISSRH = _hoops_HSSRH->next;

			FREE_ARRAY (_hoops_HSSRH->name, _hoops_SSGR(_hoops_HSSRH->name) + 1, char);

			if (_hoops_HSSRH->specific)
				FREE_ARRAY (_hoops_HSSRH->specific, _hoops_SSGR(_hoops_HSSRH->specific) + 1, char);

			FREE (_hoops_HSSRH, _hoops_SGRRR);

			_hoops_HSSRH = _hoops_ISSRH;
		}

		state->_hoops_GRRRR = 0;
	}


	if (state->points)
		FREE_ARRAY(state->points, state->_hoops_PRCCI, POINT);

	if (state->_hoops_CRCCI)
		FREE_ARRAY(state->_hoops_CRCCI, state->_hoops_PRCCI/2, DWORD);

	if (state->_hoops_HPCCI)
		FREE_ARRAY(state->_hoops_HPCCI,state->_hoops_IPCCI,unsigned char);

	FREE (state, MSW_Driver_State);
	state = null;
	((Display_Context alter *)dc)->data = null;
}


/*****************************************************************************
 *****************************************************************************
						   _hoops_HCHRH _hoops_HGGSP _hoops_PARPI
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_SRAC
 */
local POINTER_SIZED_INT get_outer_window (
	Display_Context const	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();
	POINTER_SIZED_INT			retval = 0L;
	_hoops_RRPRH					*_hoops_IRSRA = _hoops_ARPRH ();
	bool					_hoops_RACSI = false;


	_hoops_SHGSI (state);

	if (state->_hoops_PIGRR == _hoops_ASPCI ||
		state->_hoops_PIGRR == _hoops_GSPCI) {
		Display_Context alter	*ldc = (Display_Context alter *) dc;

		if (state->_hoops_HPHCI) {
			ldc->_hoops_ACPGR->draw_dc_rectangle				= HD_Std_DC_Rectangle;
			ldc->_hoops_ACPGR->draw_dc_face					= _hoops_GAPSI;
			ldc->_hoops_ACPGR->_hoops_RPCGA				= _hoops_GAPSI; 
			ldc->_hoops_ACPGR->draw_dc_polytriangle			= _hoops_APPSI;
		}
	}

	if (state->_hoops_PIGRR == _hoops_PSPCI ||
		state->_hoops_PIGRR == _hoops_RSPCI) {
		Display_Context alter	*ldc = (Display_Context alter *) dc;

		if (state->_hoops_PIGRR == _hoops_RSPCI) {
			float width, height;
			if (dc->options._hoops_SPHSR.x == -1) {
				width = dc->_hoops_PGCC.size.x ;
				height = dc->_hoops_PGCC.size.y ;
			} else {
				width = dc->options._hoops_SPHSR.x;
				height = dc->options._hoops_SPHSR.y;
			}
			if (state->_hoops_PCHCI) {
				state->_hoops_PHCIH = _hoops_RIISI(
					dc->_hoops_PCRSR,
					width,
					height,
					dc->options._hoops_GHHSR);
				if (state->_hoops_HPHCI) {
					ldc->_hoops_ACPGR->draw_dc_rectangle				= HD_Std_DC_Rectangle;
					ldc->_hoops_ACPGR->draw_dc_face					= _hoops_GAPSI;
					ldc->_hoops_ACPGR->_hoops_RPCGA				= _hoops_GAPSI; 
					ldc->_hoops_ACPGR->draw_dc_polytriangle			= _hoops_APPSI;
				}
			} else {
				state->_hoops_PHCIH = _hoops_RIISI(
					(char*)0,
					width,
					height,
					dc->options._hoops_GHHSR);
			}

			state->_hoops_IGICI = state->_hoops_PGICI = state->_hoops_SGICI = state->_hoops_AGICI = state->_hoops_PHCIH;
		}		/*
		 * _hoops_CPGP _hoops_SSSCI _hoops_AA _hoops_HAR _hoops_CSRA _hoops_GPP _hoops_GII _hoops_GPRR _hoops_IIGR _hoops_SPHGR _hoops_CHACI
		 * _hoops_ASC _hoops_SICAR _hoops_IGRC _hoops_PGSA _hoops_RISA _hoops_CIPSI _hoops_RIIA _hoops_HIS _hoops_SGS
		 * _hoops_SSIA _hoops_PAH _hoops_CSRA
		 */
		ldc->_hoops_ACPGR->_hoops_CCCSR			= _hoops_PAHSI;

		if (dc->_hoops_SHCIP->_hoops_IRR->_hoops_RCRAP == _hoops_ICRAP) {
			ldc->_hoops_ACPGR->_hoops_IGSSP			= HD_Std_Create_Frame_Buffer;
			ldc->_hoops_ACPGR->_hoops_CGSSP			= HD_Std_Display_Frame_Buffer;
			ldc->_hoops_ACPGR->_hoops_SGSSP			= HD_Std_Destroy_Frame_Buffer;
		}
		if (!state->_hoops_GPHCI) {

			/*
			 * _hoops_AACSI _hoops_IAHA _hoops_GSACI _hoops_AA _hoops_HAR _hoops_GCGH _hoops_IRS _hoops_SGPHA _hoops_IIGR _hoops_RH _hoops_HCPH _hoops_SR _hoops_SGH _hoops_GGR
			 * _hoops_PACSI _hoops_RRGR - _hoops_HRII _hoops_HSAR _hoops_HACSI _hoops_HCR _hoops_IAPR _hoops_RH _hoops_HGHC _hoops_SR _hoops_HS _hoops_SAHR
			 * _hoops_PHPH _hoops_PGCR _hoops_CCAH _hoops_SICAR _hoops_IS _hoops_RGHH _hoops_RH _hoops_RHGS _hoops_IAHA _hoops_GACSI _hoops_PPR _hoops_CISRI
			 */
			ldc->_hoops_ACPGR->draw_dc_polyline				= _hoops_IGPSI;
			ldc->_hoops_ACPGR->draw_dc_polytriangle			= _hoops_HRPSI;


			/*
			 * _hoops_RAP _hoops_HCR _hoops_RII _hoops_PGSI _hoops_IS _hoops_HSSHH (_hoops_HII _hoops_IACSI._hoops_GSGGR)
			 * _hoops_IPCP _hoops_GCHRR _hoops_GIRRR _hoops_IIGR _hoops_RGR _hoops_GRS _hoops_SHH _hoops_IS _hoops_HS _hoops_AAPA _hoops_PAPA _hoops_CHARP _hoops_IHSA
			 * _hoops_AGCR _hoops_CSSC _hoops_ISHP _hoops_CRGR _hoops_CACSI _hoops_CSSC - _hoops_ARGR _hoops_GGR _hoops_HIPH,
			 * _hoops_PGRC _hoops_PAR _hoops_AHRH
			 */

			ldc->_hoops_ACPGR->draw_dc_polymarker				= HD_Std_DC_Polymarker;
			ldc->_hoops_ACPGR->draw_dc_rectangle				= HD_Std_DC_Rectangle;
			ldc->_hoops_ACPGR->draw_dc_face					= HD_Std_DC_Face;
			ldc->_hoops_ACPGR->_hoops_RPCGA				= HD_Std_DC_Polygon;
			ldc->_hoops_ACPGR->draw_dc_colorized_face			= HD_Std_DC_Colorized_Face;
			ldc->_hoops_ACPGR->draw_dc_colorized_polytriangle = HD_Span_DC_Colorized_Polytris;
			ldc->_hoops_ACPGR->draw_dc_polydot				= HD_Std_DC_Polydot;
		}
		else {
			ldc->_hoops_ACPGR->draw_dc_rectangle				= HD_Std_DC_Rectangle;
			ldc->_hoops_ACPGR->draw_dc_face					= _hoops_GAPSI;
			ldc->_hoops_ACPGR->_hoops_RPCGA				= HD_Std_DC_Polygon;
			ldc->_hoops_ACPGR->draw_dc_colorized_face			= HD_Std_DC_Colorized_Face;
			ldc->_hoops_ACPGR->draw_dc_colorized_polytriangle = HD_Span_DC_Colorized_Polytris;
			ldc->_hoops_ACPGR->draw_dc_polytriangle			= _hoops_APPSI;
		}
	}

	state->_hoops_IPICI = NULL;

	state->_hoops_SRRRR = dc->options._hoops_SRRRR;

	state->_hoops_RIICI			= NULL;
	state->_hoops_GIICI		= NULL;

	if (state->_hoops_IHICI == 4) {
		/* _hoops_AGAH _hoops_HCHSR _hoops_SRHR _hoops_HGRH _hoops_PAH _hoops_HAR _hoops_RGHH _hoops_SACSI 4 _hoops_IGRH _hoops_RPCC */
		state->_hoops_RGCCI = false;
	}

	switch (state->_hoops_PIGRR) {
		case _hoops_PPSGR: {
				DWORD			window_style;
				char			_hoops_IAPIR[256];
				HMONITOR		_hoops_IGRAH;
				MONITORINFO		_hoops_CGRAH = { sizeof(_hoops_CGRAH) };
				const	POINT			_hoops_SGRAH = { 0, 0 };

				if (!_hoops_IRSRA->_hoops_SGACI) {
					WNDCLASS		window_class;

					window_class.style =
						CS_HREDRAW|CS_VREDRAW|CS_GLOBALCLASS;
#ifndef _WIN32_WCE
					if (state->_hoops_SSRRI != _hoops_PHRCI)
						window_class.style |= CS_OWNDC;

					window_class.hIcon			= LoadIcon (_hoops_RCSRH (_hoops_HGRAH), "HoopsIcon");
					window_class.lpszClassName	= "HoopsWClassMSW";
#endif
					window_class.lpfnWndProc	= _hoops_HGGSI;
					window_class.cbClsExtra		= 0;
					window_class.cbWndExtra		= 0;
					window_class.hInstance		= _hoops_RCSRH (_hoops_ACSRH);

					window_class.hCursor		= LoadCursor (NULL, IDC_ARROW);
					window_class.hbrBackground	= (HBRUSH) COLOR_CAPTIONTEXT;
					window_class.lpszMenuName	= NULL;

					RegisterClass (&window_class);
					_hoops_IRSRA->_hoops_SGACI = true;
				}
#ifndef _WIN32_WCE

				/* _hoops_GAGAH _hoops_RAGAH _hoops_PPR _hoops_GPAA */
				if (dc->options.border || dc->options._hoops_HRSSP) {
					if (dc->options._hoops_AASSP) {
						state->_hoops_ACGRR	 =
						state->_hoops_PCGRR	 = GetSystemMetrics (SM_CXFRAME);
						state->_hoops_RCGRR = GetSystemMetrics (SM_CYFRAME);
					}
					else {
						state->_hoops_ACGRR	 =
						state->_hoops_PCGRR		 = GetSystemMetrics (SM_CXBORDER);
						state->_hoops_RCGRR = GetSystemMetrics (SM_CYBORDER);
					}
					state->_hoops_HCGRR = state->_hoops_RCGRR +
						GetSystemMetrics (SM_CYCAPTION) - 1;
				}
#endif
				/* _hoops_CAHA _hoops_GGSR _hoops_RH _hoops_RPPS _hoops_IAHA */
				window_style = WS_OVERLAPPED;

				if (dc->options._hoops_HRSSP) {
#ifndef _WIN32_WCE
					 window_style |= WS_SYSMENU | WS_CAPTION |
									 WS_MINIMIZEBOX | WS_MAXIMIZEBOX |
									 WS_CAPTION | WS_THICKFRAME;
#else
					 window_style |= WS_SYSMENU | WS_CAPTION |
									 WS_MINIMIZEBOX | WS_MAXIMIZEBOX |
									 WS_CAPTION;
#endif
				}
				else {
					window_style |= WS_POPUP;
					if (dc->options.border)
						window_style |= WS_DLGFRAME;
				}

				if (!dc->options._hoops_AASSP) {
#ifndef _WIN32_WCE
					 window_style &= !(WS_MINIMIZEBOX | WS_MAXIMIZEBOX |
									   WS_MAXIMIZE | WS_MINIMIZE |
									   WS_THICKFRAME);
#else
					 window_style &= !(WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
#endif
				}

				HI_Copy_Name_To_Chars (&dc->options._hoops_IAPIR, _hoops_IAPIR);
				_hoops_IAPIR[79] = '\0';

				state->_hoops_SIGRR.x = dc->_hoops_RHPGA.left
					- state->_hoops_PCGRR;
				state->_hoops_SIGRR.y = state->_hoops_CCGRR -
							dc->_hoops_RHPGA.top - state->_hoops_HCGRR;
				state->_hoops_CIGRR.x = state->_hoops_GCGRR.x = dc->_hoops_RHPGA.right -
							dc->_hoops_RHPGA.left +
							state->_hoops_ACGRR + state->_hoops_PCGRR;
				state->_hoops_CIGRR.y = state->_hoops_GCGRR.y = dc->_hoops_RHPGA.top -
							dc->_hoops_RHPGA.bottom +
							state->_hoops_HCGRR + state->_hoops_RCGRR;

#ifndef _WIN32_WCE
				
				
				if (BIT(dc->options.flags, _hoops_GIPRP)) {
					_hoops_IGRAH = MonitorFromPoint(_hoops_SGRAH, MONITOR_DEFAULTTOPRIMARY);
					GetMonitorInfo(_hoops_IGRAH, &_hoops_CGRAH);

					state->_hoops_GGICI =
						CreateWindow ("HoopsWClassMSW", _hoops_IAPIR, WS_POPUP | WS_VISIBLE,
								_hoops_CGRAH.rcMonitor.left,
								_hoops_CGRAH.rcMonitor.top,
								_hoops_CGRAH.rcMonitor.right - _hoops_CGRAH.rcMonitor.left,
								_hoops_CGRAH.rcMonitor.bottom - _hoops_CGRAH.rcMonitor.top,
								NULL, NULL, _hoops_RCSRH (_hoops_ACSRH), (LPSTR)dc);
				} else{
					state->_hoops_GGICI =
						CreateWindow ("HoopsWClassMSW", _hoops_IAPIR, window_style,
								dc->_hoops_RHPGA.left - state->_hoops_PCGRR,
								state->_hoops_CCGRR -
								dc->_hoops_RHPGA.top - state->_hoops_HCGRR,
								dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left +
								state->_hoops_ACGRR + state->_hoops_PCGRR + 1,
								dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom +
								state->_hoops_HCGRR + state->_hoops_RCGRR + 1,
								NULL, NULL, _hoops_RCSRH (_hoops_ACSRH), (LPSTR)dc);
				}


#endif
				if (state->_hoops_GGICI == NULL) {
					 HE_ERROR (HEC_MSW_DRIVER, HES_CANNOT_CREATE_WINDOW,
							   "Unable to Create a Window");
					 HD_Kill_Driver (dc);
				}
#ifndef _WIN32_WCE
				GdiSetBatchLimit (MAXDWORD);
#endif
				if (state->_hoops_GAHCI && state->_hoops_AGICI == null) {
					_hoops_RACSI = true;
					state->_hoops_AGICI = GetDC (state->_hoops_GGICI);
				}

#ifndef _WIN32_WCE
				if (dc->options._hoops_HRSSP) {
					HMENU			_hoops_GRRAH;

					_hoops_GRRAH = GetSystemMenu (state->_hoops_GGICI, FALSE);
					 AppendMenu (_hoops_GRRAH, MF_SEPARATOR, 0, NULL);
					 AppendMenu (_hoops_GRRAH, MF_STRING, IDM_ABOUT, "&About...");
				}
#endif
				if (state->_hoops_RGCCI)
					_hoops_GIISI (dc);

				if (!dc->options._hoops_IASSP)
					ShowWindow (state->_hoops_GGICI, SW_SHOWNORMAL);

				UpdateWindow (state->_hoops_GGICI);

				retval = (POINTER_SIZED_INT) state->_hoops_GGICI;
		}	break;

		case _hoops_HPSGR: {
#ifndef _WIN32_WCE
#ifdef _WIN64
			_hoops_RCSRH (_hoops_ACSRH) =
				(HINSTANCE) GetWindowLongPtr (state->_hoops_GGICI, GWLP_HINSTANCE);
#else
			_hoops_RCSRH (_hoops_ACSRH) =
				(HINSTANCE) GetWindowLong (state->_hoops_GGICI, GWL_HINSTANCE);
#endif
#endif
			/* _hoops_GRPHA _hoops_RH _hoops_CSPH _hoops_HIS _hoops_SGS _hoops_PCSRH _hoops_GRS _hoops_IPHR */
			((Display_Context alter *)dc)->current._hoops_RAPGH =
				(POINTER_SIZED_INT) state->_hoops_GGICI;

			state->_hoops_GGICI = (HWND) dc->options._hoops_GCHSR;

			if (!dc->options._hoops_CRSSP &&
				!BIT (dc->options._hoops_IRARR, _hoops_GCCRH)) {
#ifdef _WIN64
				state->_hoops_GIGRR = (WNDPROC)
					 GetWindowLongPtr (state->_hoops_GGICI,
						GWLP_WNDPROC);

				SetWindowLongPtr (state->_hoops_GGICI, GWLP_WNDPROC,
								(__int64) _hoops_AICRH);
#else
				state->_hoops_GIGRR = (WNDPROC)
					 GetWindowLong (state->_hoops_GGICI,
						GWL_WNDPROC);

				SetWindowLong (state->_hoops_GGICI, GWL_WNDPROC,
								(LONG) _hoops_AICRH);
#endif
			}
			else {
				state->_hoops_GIGRR = NULL;
				if (dc->options._hoops_RCHSR == 0 && state->_hoops_PHICI != 0)
					_hoops_ARGIP (HEC_MSW_DRIVER,
						HES_NOWINDOWHOOK_COLORMAPID_REQUIRED_TOGETHER,
						"When using NO WINDOWS HOOK, HOOPS requires you to use the",
						"USE COLORMAP ID option and handle the palette messages yourself",
						"as outlined in the 'USE WINDOW ID' demos");
			}

			if (state->_hoops_AGICI == null) {
				_hoops_RACSI = true;
				state->_hoops_AGICI = GetDC (state->_hoops_GGICI);
			}

			if (state->_hoops_RGCCI)
				_hoops_GIISI (dc);


			retval = (POINTER_SIZED_INT) state->_hoops_GGICI;
		}	break;

		case _hoops_PSPCI: {
			RECT	_hoops_IGGAH;
#ifndef _WIN32_WCE
#ifdef _WIN64
			_hoops_RCSRH (_hoops_ACSRH)=
				 (HINSTANCE) GetWindowLongPtr (state->_hoops_GGICI, GWLP_HINSTANCE);
#else
			_hoops_RCSRH (_hoops_ACSRH)=
				 (HINSTANCE) GetWindowLong (state->_hoops_GGICI, GWL_HINSTANCE);
#endif
			GetClientRect (state->_hoops_GGICI, &_hoops_IGGAH);

			SetWindowExtEx (state->_hoops_AGICI, _hoops_IGGAH.right, _hoops_IGGAH.bottom, NULL);
			SetWindowOrgEx (state->_hoops_AGICI, 0, 0, NULL);
#endif
			retval = (POINTER_SIZED_INT) state->_hoops_AGICI;
		}	break;

		case _hoops_ASPCI: {
			/* _hoops_IH _hoops_RAGIP _hoops_IIGR _hoops_PA _hoops_RRI _hoops_PGCPR _hoops_IS _hoops_ASRC */
#ifndef _WIN32_WCE
#ifdef _WIN64
			_hoops_RCSRH (_hoops_ACSRH)=
				(HINSTANCE) GetWindowLongPtr (state->_hoops_GGICI, GWLP_HINSTANCE);
#else
			_hoops_RCSRH (_hoops_ACSRH)=
				(HINSTANCE) GetWindowLong (state->_hoops_GGICI, GWL_HINSTANCE);
#endif
#endif
			retval = (POINTER_SIZED_INT)state->_hoops_AGICI;
		}	break;
	}

#ifndef _WIN32_WCE
	if (!IsWindowVisible (state->_hoops_GGICI) ||
		(IsWindowVisible (state->_hoops_GGICI) && GetFocus() == state->_hoops_GGICI) ||
	(IsWindowVisible (state->_hoops_GGICI) && GetTopWindow(GetFocus()) == state->_hoops_GGICI))
		state->_hoops_SRCCI = true;
	else
		state->_hoops_SRCCI = false;

	SetPolyFillMode (state->_hoops_AGICI, WINDING);
#endif

	/*
	 * _hoops_RAP _hoops_GH _hoops_IRS _hoops_HAIR _hoops_AGIAI _hoops_GASR _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_SCGH _hoops_SISS _hoops_PAR
	 * _hoops_RPP _hoops_SR _hoops_HS _hoops_HGRC _hoops_GGCSI _hoops_IS _hoops_HSISI _hoops_GPCSI
	 */
	if (state->_hoops_SRHCI  && 
		(BIT(dc->_hoops_PGCC.flags , _hoops_IAPGH) ||
		 dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR ||
		 dc->_hoops_PGCC._hoops_PIHSR == _hoops_RIIHP)) {
		int				index;
		int				_hoops_AAPSR;
		short alter		*_hoops_RPCSI;
		HPALETTE		_hoops_APCSI;
		HDC				_hoops_AGICI = state->_hoops_AGICI;

		if (state->_hoops_PHICI)
			_hoops_AAPSR = state->_hoops_HHICI;
		else
			_hoops_AAPSR = dc->_hoops_PGCC._hoops_AAPSR;

		{
			char const	*tmp;
			int			ii;


			ALLOC_ARRAY (tmp,
						 sizeof (LOGPALETTE) +
						 _hoops_AAPSR * sizeof (PALETTEENTRY),
						 char);
			state->_hoops_CHICI = (LPLOGPALETTE)tmp;
			if (state->_hoops_RGCCI) {
				ALLOC_ARRAY (tmp, 256 * sizeof (PALETTEENTRY), char);
				state->_hoops_RAHCI = (LPPALETTEENTRY) tmp;
				ALLOC_ARRAY (tmp, 256 * sizeof (RGBQUAD), char);
				state->_hoops_AAHCI = (LPRGBQUAD)	tmp;
			}

			ALLOC_ARRAY (state->_hoops_SHICI,
						 _hoops_AAPSR,
						 bool);

			for (ii =0; ii < _hoops_AAPSR; ii++)
				state->_hoops_SHICI[ii] = false;
		}

		state->_hoops_CHICI->palNumEntries = _hoops_AAPSR;
		state->_hoops_CHICI->palVersion = 0x300;

		if (state->_hoops_PHICI) {
			GetSystemPaletteEntries (_hoops_AGICI, 0,
									 state->_hoops_HHICI,
									 &state->_hoops_CHICI->palPalEntry[0]);

#ifndef _WIN32_WCE
			for (index = 0; index < state->_hoops_HHICI; index++)
				state->_hoops_CHICI->palPalEntry[index].peFlags = PC_NOCOLLAPSE;
#endif
		}
		else {
			for (index = 0; index < _hoops_AAPSR; index++) {
				state->_hoops_CHICI->palPalEntry[index].peRed = index;
				state->_hoops_CHICI->palPalEntry[index].peFlags = PC_EXPLICIT;
			}
		}

		if (dc->options._hoops_RCHSR == 0 &&
				state->_hoops_PIGRR != _hoops_PSPCI) {
			if (state->_hoops_GGCCI) {
				_hoops_RSCCI (state);
				state->_hoops_GIICI =
					_hoops_HSCCI (state->_hoops_CHICI, 256, state);
			}
			else
				state->_hoops_GIICI = CreatePalette (state->_hoops_CHICI);

			state->_hoops_ISHCI = SelectPalette (state->_hoops_AGICI,
											  state->_hoops_GIICI,
											  !state->_hoops_SRCCI);
		}

		if (state->_hoops_PHICI) {
			for (index = 0; index < state->_hoops_HHICI; index++)
				state->_hoops_CHICI->palPalEntry[index].peFlags = 0;
		}

		if (state->_hoops_ISHCI == (HPALETTE) 1)
			state->_hoops_ISHCI = state->_hoops_RHCCI;

		if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
			if (state->_hoops_PIGRR != _hoops_PSPCI) {
				/* _hoops_HGI _hoops_HRGR _hoops_CAS _hoops_RH _hoops_SGH _hoops_RPPS _hoops_HGIR _hoops_CRSRR _hoops_IISA _hoops_CRGR _hoops_HPSI */
				if (dc->options._hoops_RCHSR != 0) {
					/*
					 * _hoops_PS _hoops_HS _hoops_IRS _hoops_HGIR _hoops_CARSR - _hoops_RCSH _hoops_CARS _hoops_PPR _hoops_SGH
					 * _hoops_PPCSI
					 */
					state->_hoops_GIICI =
						(HPALETTE) dc->options._hoops_RCHSR;
					state->_hoops_ISHCI =
						SelectPalette (state->_hoops_AGICI,
									   state->_hoops_GIICI,
									   !state->_hoops_SRCCI);
				}
				if (state->_hoops_RGICI == 0 ||
					state->_hoops_RGICI ==
					state->_hoops_GGICI) {
#ifndef _WIN32_WCE
					UnrealizeObject (state->_hoops_GIICI);
#endif
					RealizePalette (state->_hoops_AGICI);
				}
				}
			_hoops_APCSI = state->_hoops_GIICI;
		}
		else {
			SelectPalette (state->_hoops_AGICI,
						   state->_hoops_ISHCI,
						   !state->_hoops_SRCCI);
			DeleteObject (state->_hoops_GIICI);

			{
				char alter	*tmp;

				tmp = (char alter *)state->_hoops_CHICI;
				FREE_ARRAY (tmp,
							sizeof (LOGPALETTE) +
							_hoops_AAPSR * sizeof (PALETTEENTRY),
							char);
				FREE_ARRAY (state->_hoops_SHICI,
					_hoops_AAPSR,
					bool);
			}
			state->_hoops_GIICI = NULL;
			_hoops_APCSI = state->_hoops_ISHCI;
		}

		{
			unsigned char alter	 *tmp;
			LPBITMAPINFOHEADER		_hoops_HPCSI;


			state->_hoops_PPICI = sizeof (BITMAPINFOHEADER) +
						 _hoops_IAAA (8, _hoops_AAPSR) * 2;

			ALLOC_ARRAY (tmp, state->_hoops_PPICI, unsigned char);
			memset(tmp,0,state->_hoops_PPICI);

			state->_hoops_APICI = (LPBITMAPINFO)tmp;

			_hoops_HPCSI = &state->_hoops_APICI->bmiHeader;
			_hoops_HPCSI->biSize			 = sizeof (BITMAPINFOHEADER);
			_hoops_HPCSI->biPlanes		 = 1;
			_hoops_HPCSI->biBitCount		 = 8;
			_hoops_HPCSI->biCompression	 = BI_RGB;	/* _hoops_GHHSI */
			_hoops_HPCSI->biXPelsPerMeter = state->_hoops_PIICI;
			_hoops_HPCSI->biYPelsPerMeter = state->_hoops_HIICI;
			_hoops_HPCSI->biClrUsed		 = 8;
			_hoops_HPCSI->biClrImportant	 = 0;


			/*
			 * _hoops_PS _hoops_ARPR _hoops_IRS _hoops_GIAP _hoops_IPS _hoops_IIGR _hoops_RGR _hoops_HPHS _hoops_CR _hoops_SR
			 * _hoops_RRP _hoops_IS _hoops_PCCS _hoops_SCH _hoops_PPR _hoops_SGH _hoops_HAGH _hoops_AII (_hoops_IPCSI
			 * _hoops_RH _hoops_IHCRH _hoops_HPHS) _hoops_GGR _hoops_RH _hoops_AGIR _hoops_IIGR 16 _hoops_HAIR _hoops_AGSHA
			 */
			state->_hoops_SPICI = state->_hoops_PPICI +
				sizeof (BITMAPINFOHEADER) + _hoops_IAAA (8, _hoops_AAPSR) * 2;

#ifndef _WIN32_WCE
			state->_hoops_IPICI =
				GlobalAlloc (GMEM_MOVEABLE|GMEM_NODISCARD, (DWORD) state->_hoops_SPICI);
			state->_hoops_CPICI = (LPBITMAPINFO)GlobalLock (state->_hoops_IPICI);
#endif
			state->_hoops_RHICI = 0;
			COPY_MEMORY (state->_hoops_APICI,
								 state->_hoops_PPICI,
								 state->_hoops_CPICI);

			if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR ||
				dc->_hoops_PGCC._hoops_PIHSR == _hoops_RIIHP ||
				BIT(dc->_hoops_PGCC.flags , _hoops_IAPGH)) {
					state->_hoops_HPICI = (unsigned char *)state->_hoops_CPICI +
								sizeof (BITMAPINFOHEADER) +
								_hoops_IAAA (8, _hoops_AAPSR) * 2;
			}
			else {
				state->_hoops_HPICI = (unsigned char *)state->_hoops_CPICI +
						state->_hoops_CPICI->bmiHeader.biSize;
			}
		}

		_hoops_RPCSI = (short int alter *)state->_hoops_APICI->bmiColors;
		if (BIT(dc->_hoops_PGCC.flags , _hoops_IAPGH)) {
			*_hoops_RPCSI++ = GetNearestPaletteIndex (_hoops_APCSI, _hoops_SRASI(0,	 0,	  0));
			*_hoops_RPCSI++ = GetNearestPaletteIndex (_hoops_APCSI, _hoops_SRASI(0,	 0,	  255));
			*_hoops_RPCSI++ = GetNearestPaletteIndex (_hoops_APCSI, _hoops_SRASI(0,	 255, 0));
			*_hoops_RPCSI++ = GetNearestPaletteIndex (_hoops_APCSI, _hoops_SRASI(0,	 255, 255));
			*_hoops_RPCSI++ = GetNearestPaletteIndex (_hoops_APCSI, _hoops_SRASI(255, 0,	  0));
			*_hoops_RPCSI++ = GetNearestPaletteIndex (_hoops_APCSI, _hoops_SRASI(255, 0,	  255));
			*_hoops_RPCSI++ = GetNearestPaletteIndex (_hoops_APCSI, _hoops_SRASI(255, 255, 0));
			*_hoops_RPCSI++ = GetNearestPaletteIndex (_hoops_APCSI, _hoops_SRASI(255, 255, 255));
		}
		else {
			state->_hoops_APICI->bmiHeader.biClrUsed = _hoops_AAPSR;

			if (_hoops_AAPSR > 256)
				_hoops_AAPSR = 256;

			if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_RIIHP ||
				dc->options._hoops_RAHHP) {
				int		_hoops_PIHHP;

				for (index = 0; index < _hoops_AAPSR; index++) {
					_hoops_PIHHP = (int) (255.0 * ((float)index/
						((float)_hoops_AAPSR - 1.0)));
					*_hoops_RPCSI++ = GetNearestPaletteIndex (_hoops_APCSI,
													  _hoops_SRASI (_hoops_PIHHP,
														   _hoops_PIHHP,
														   _hoops_PIHHP));
				}
			}
			else {
				for (index = 0; index < _hoops_AAPSR; index++)
					*_hoops_RPCSI++ = index;
			}
		}
	}
	else {
		unsigned char alter	 *tmp;
		LPBITMAPINFOHEADER		_hoops_HPCSI;


		state->_hoops_PPICI = sizeof (BITMAPINFOHEADER);

		ALLOC_ARRAY (tmp, state->_hoops_PPICI, unsigned char);
		memset(tmp,0,state->_hoops_PPICI);

		state->_hoops_APICI = (LPBITMAPINFO)tmp;

		_hoops_HPCSI = &state->_hoops_APICI->bmiHeader;
		_hoops_HPCSI->biSize		 = sizeof (BITMAPINFOHEADER);
		_hoops_HPCSI->biPlanes	 = 1;
		_hoops_HPCSI->biBitCount	 = 32;
		_hoops_HPCSI->biCompression = BI_RGB;  /* _hoops_GHHSI */
		_hoops_HPCSI->biXPelsPerMeter = state->_hoops_PIICI;
		_hoops_HPCSI->biYPelsPerMeter = state->_hoops_HIICI;
		_hoops_HPCSI->biClrUsed = 0;
		_hoops_HPCSI->biClrImportant = 0;
	}


	if ((state->_hoops_PIGRR == _hoops_PPSGR ||
		 state->_hoops_PIGRR == _hoops_HPSGR)) {

		if (state->_hoops_GGICI) {
			/* _hoops_RAP _hoops_RH _hoops_GAPGH _hoops_IS _hoops_RH _hoops_SCGR _hoops_RPPS _hoops_IGIR */
			GetClientRect (state->_hoops_GGICI, &state->_hoops_IIGRR);

			HD_Resize_Subscreen (dc, true,
								 0, state->_hoops_IIGRR.right - 1,
								 0, state->_hoops_IIGRR.bottom - 1);
		}

		if (state->_hoops_SRRRR)
			_hoops_IIHSI (state);
	}

#if 0
#ifndef _WIN32_WCE
#ifdef MINITAB
	SetTextAlign (state->_hoops_AGICI, TA_BOTTOM | TA_LEFT | TA_NOUPDATECP);
#else
	SetTextAlign (state->_hoops_AGICI, TA_BASELINE | TA_LEFT | TA_NOUPDATECP);
#endif
#endif
#endif

	if (!state->_hoops_GAHCI && _hoops_RACSI) {
		ReleaseDC(state->_hoops_GGICI, state->_hoops_AGICI);
		state->_hoops_AGICI = 0;
	} else {
		/* _hoops_ASAC _hoops_ISCP _hoops_GGSC _hoops_IH _hoops_SPHR */
		if (state->_hoops_PIGRR == _hoops_HPSGR)
			state->_hoops_HSHCI = SaveDC (state->_hoops_AGICI);
	}

	/*
	 * _hoops_ACAC _hoops_CPCSI: _hoops_ICAH _hoops_IS _hoops_CPSA _hoops_HHSA _hoops_ICCGR _hoops_HCHSR _hoops_SRHR.
	 *		   _hoops_RCIAH _hoops_HA, _hoops_SCH _hoops_IRHAP _hoops_GPP _hoops_RH _hoops_IPSP _hoops_RGSR
	 *		   _hoops_PIASI = _hoops_ICCGR _hoops_HCHSR _hoops_SRHR.
	 */
	if (state->_hoops_IRICI) {
		Display_Context alter	*ldc = (Display_Context alter *) dc;

		if (dc->_hoops_SHCIP->_hoops_IRR->_hoops_RCRAP == _hoops_ICRAP) {
			ldc->_hoops_ACPGR->_hoops_IGSSP			= HD_Std_Create_Frame_Buffer;
			ldc->_hoops_ACPGR->_hoops_CGSSP			= HD_Std_Display_Frame_Buffer;
			ldc->_hoops_ACPGR->_hoops_SGSSP			= HD_Std_Destroy_Frame_Buffer;
		}
	}

	return retval;
}

/*
 * _hoops_SRAC
 */
local void free_outer_window (
	Display_Context const	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();

	/*_hoops_ASIGA _hoops_PCPA? */
	if (!state) return;

	/* _hoops_SPCSI _hoops_IRS _hoops_SPCS _hoops_GISAP _hoops_PGRRR _hoops_HIS _hoops_SGS _hoops_APGAI _hoops_CGISR _hoops_RH _hoops_GISAP _hoops_HRGR _hoops_GH */
	state->_hoops_HRRRR &= ~_hoops_ARRRR;
	state->_hoops_HRRRR &= ~_hoops_PRRRR;
	state->_hoops_HRRRR &= ~_hoops_RRRRR;

	state->_hoops_SCGRR = 1;
	state->mouse_y = 1;

	if (!dc->options._hoops_CRSSP) {
		HD_Queue_Pixel_Location_Event (state->dc, state->_hoops_HRRRR,
								   state->_hoops_SCGRR, state->mouse_y);
		state->_hoops_IRRRR = true;
	}

	state->_hoops_CPICI = NULL;
	state->_hoops_SPICI = 0;
	state->_hoops_RHICI = 0;

	if (state->_hoops_PIGRR == _hoops_HPSGR) {
		/* _hoops_PHIH *_hoops_ISCP* _hoops_PIAP */
		if (state->_hoops_GAHCI)
			RestoreDC (state->_hoops_AGICI, state->_hoops_HSHCI);

		if (!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH)) {

#ifdef _WIN64
			SetWindowLongPtr (state->_hoops_GGICI, GWLP_WNDPROC,
				(POINTER_SIZED_INT) state->_hoops_GIGRR);
#else
			SetWindowLong (state->_hoops_GGICI, GWL_WNDPROC,
				(LONG) state->_hoops_GIGRR);
#endif
		}
	}
	else if (state->_hoops_PIGRR == _hoops_ASPCI &&
		!BIT (dc->options._hoops_IRARR, _hoops_HPACI)) {
#ifndef _WIN32_WCE
		Escape (state->_hoops_AGICI, ENDDOC, 0, NULL, NULL);
#endif
	}

	SelectObject (state->_hoops_AGICI, state->_hoops_CPCCI);
	state->_hoops_CSC.font = _hoops_CCICI;

	if (state->_hoops_RIICI != NULL)
		SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);

	SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);

	if (state->_hoops_SRHCI &&
		(dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR ||
		 dc->_hoops_PGCC._hoops_PIHSR == _hoops_RIIHP ||
		 BIT(dc->_hoops_PGCC.flags , _hoops_IAPGH))) {
		int		_hoops_AAPSR;

		if (state->_hoops_PHICI)
			_hoops_AAPSR = state->_hoops_HHICI;
		else
			_hoops_AAPSR = dc->_hoops_PGCC._hoops_AAPSR;

		if (state->_hoops_GIICI != NULL) {
			if (state->_hoops_PIGRR != _hoops_PSPCI) {
				SelectPalette (state->_hoops_AGICI,
							   state->_hoops_ISHCI,
							   !state->_hoops_SRCCI);
			}
			if (dc->options._hoops_RCHSR == 0) {
				DeleteObject (state->_hoops_GIICI);
			}

			FREE_ARRAY (state->_hoops_CHICI,
						sizeof (LOGPALETTE) +
						_hoops_AAPSR * sizeof (PALETTEENTRY),
						char);

			if (state->_hoops_RGCCI) {
				FREE_ARRAY (state->_hoops_RAHCI,
							256 * sizeof (PALETTEENTRY), char);
				FREE_ARRAY (state->_hoops_AAHCI,
							256 * sizeof (RGBQUAD), char);
			}

			state->_hoops_GIICI	= NULL;
			state->_hoops_ISHCI	= NULL;
		}
	}
	FREE_ARRAY (state->_hoops_APICI, state->_hoops_PPICI, unsigned char);

	if (state->_hoops_IPICI != NULL) {
#ifndef _WIN32_WCE
		GlobalUnlock (state->_hoops_IPICI);
		GlobalFree (state->_hoops_IPICI);
#endif
	}

	/*
	 * _hoops_CPCS _hoops_PSAP-_hoops_SHPR _hoops_SRHR
	 */
	if (state->_hoops_SRRRR) {
		SelectObject (state->_hoops_CGICI, state->_hoops_CSHCI);
		DeleteObject (state->_hoops_IAICI);
		DeleteDC (state->_hoops_CGICI);
		DeleteDC (state->_hoops_SGICI);
		state->_hoops_AGICI = state->_hoops_IGICI;
	}

	/*
	 * _hoops_RASRR _hoops_HRGR _hoops_HGSAR _hoops_IH _hoops_PSAR _hoops_PICP _hoops_IIGR _hoops_HPASR _hoops_HAII _hoops_SHCA,
	 * _hoops_HIH _hoops_SR _hoops_HAGGR _hoops_CARS _hoops_ARI
	 */
	if (state->_hoops_GAHCI &&
		state->_hoops_PIGRR != _hoops_ASPCI &&
		state->_hoops_PIGRR != _hoops_PSPCI &&
		state->_hoops_PIGRR != _hoops_RSPCI) {
		ReleaseDC (state->_hoops_GGICI, state->_hoops_AGICI);
		state->_hoops_AGICI = null;
	}
	if (BIT (state->_hoops_PIGRR, _hoops_SSPCI)) {
		/* _hoops_PS _hoops_RGAR _hoops_HAGGR _hoops_GGSR _hoops_HAII _hoops_SPHGR */
		DestroyWindow (state->_hoops_GGICI);
	}
}


/*
 * _hoops_SRAC
 */
local void _hoops_RSCSP (
	Display_Context const	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();


	if (state->_hoops_PIGRR == _hoops_PSPCI ||
		state->_hoops_PIGRR == _hoops_ASPCI) {
		/* _hoops_AGCR _hoops_PSGC _hoops_CGH _hoops_IIP _hoops_GPHCR _hoops_IH _hoops_SIRSI _hoops_PAR _hoops_GPACI */
		return;
	}
#ifndef _WIN32_WCE
	if ((state->_hoops_PIGRR == _hoops_PPSGR ||
		 state->_hoops_PIGRR == _hoops_HPSGR) &&
		IsWindow (state->_hoops_GGICI) &&
		(IsIconic (state->_hoops_GGICI))) {
		/* _hoops_CGP _hoops_RH _hoops_RPPS _hoops_HRGR _hoops_PRRAH _hoops_SR _hoops_SSPC _hoops_HCR _hoops_PCCS _hoops_SSHRH */
		return;
	}
#endif
	/* _hoops_SPCSI _hoops_IRS _hoops_SPCS _hoops_GISAP _hoops_PGRRR _hoops_HIS _hoops_SGS _hoops_APGAI _hoops_CGISR _hoops_RH _hoops_GISAP _hoops_HRGR _hoops_GH */
	state->_hoops_HRRRR &= ~_hoops_ARRRR;
	state->_hoops_HRRRR &= ~_hoops_PRRRR;
	state->_hoops_HRRRR &= ~_hoops_RRRRR;

	state->_hoops_SCGRR = 1;
	state->mouse_y = 1;

	if (!dc->options._hoops_CRSSP) {
		HD_Queue_Pixel_Location_Event (state->dc, state->_hoops_HRRRR,
								   state->_hoops_SCGRR, state->mouse_y);
		state->_hoops_IRRRR = true;
	}

#ifndef _WIN32_WCE
	if ((state->_hoops_PIGRR == _hoops_PPSGR ||
		 state->_hoops_PIGRR == _hoops_HPSGR) &&
		IsWindow (state->_hoops_GGICI) &&
		IsZoomed (state->_hoops_GGICI)) {
		/* _hoops_PS _hoops_HS _hoops_IS _hoops_IIS _hoops_SPHGR _hoops_CPAII _hoops_GHCSI _hoops_SRS */
		SendMessage (state->_hoops_GGICI, WM_SYSCOMMAND, SC_RESTORE, 0);
	}
#endif
	state->_hoops_SIGRR.x = dc->_hoops_RHPGA.left
		- state->_hoops_PCGRR;
	state->_hoops_SIGRR.y = state->_hoops_CCGRR -
				dc->_hoops_RHPGA.top - state->_hoops_HCGRR;
	state->_hoops_CIGRR.x = state->_hoops_GCGRR.x = dc->_hoops_RHPGA.right -
				dc->_hoops_RHPGA.left +
				state->_hoops_ACGRR + state->_hoops_PCGRR;
	state->_hoops_CIGRR.y = state->_hoops_GCGRR.y = dc->_hoops_RHPGA.top -
				dc->_hoops_RHPGA.bottom +
				state->_hoops_HCGRR + state->_hoops_RCGRR;

	MoveWindow (state->_hoops_GGICI,
				dc->_hoops_RHPGA.left - state->_hoops_PCGRR,
				state->_hoops_CCGRR -
				dc->_hoops_RHPGA.top - state->_hoops_HCGRR,
				dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left +
				state->_hoops_ACGRR + state->_hoops_PCGRR,
				dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom +
				state->_hoops_HCGRR + state->_hoops_RCGRR,
				true);
}


/*****************************************************************************
 *****************************************************************************
						   _hoops_HRHI _hoops_PPR _hoops_SICRH _hoops_CRRPI
 *****************************************************************************
 *****************************************************************************/


/* _hoops_IPCP _hoops_HSPR _hoops_PGCR _hoops_CIGR, _hoops_RHCSI _hoops_HPP _hoops_SPR _hoops_IIGR _hoops_ISCP _hoops_AHCSI, _hoops_HRGR _hoops_HAHH
 * _hoops_IS _hoops_IPHR _hoops_AARI _hoops_IRS _hoops_CAGRH _hoops_GGR _hoops_SRGAI _hoops_PSPSI _hoops_GGR _hoops_PHCSI _hoops_PPR _hoops_CPCSI.  _hoops_HHCSI, _hoops_SCH _hoops_AHPP
 * _hoops_CSAP _hoops_PHGHR _hoops_RH _hoops_SAPS _hoops_PPSR _hoops_HPI _hoops_GGR _hoops_IRS _hoops_AHCI _hoops_PIAP _hoops_RAS _hoops_RGCI _hoops_IHCSI.  _hoops_PHGP
 * _hoops_RGR _hoops_RSAIP _hoops_HRGR _hoops_SIGR _hoops_GGR _hoops_PGCR _hoops_IIHP... 1) _hoops_GGR _hoops_CHCSI, _hoops_ARPP _hoops_PPR _hoops_RAS _hoops_SHCSI; _hoops_PPR
 * 2) _hoops_ARI, _hoops_HPGR _hoops_IHPI/_hoops_HPIRA _hoops_PAAP.	_hoops_IPCP _hoops_GIAP _hoops_HRGR _hoops_HAHH _hoops_PGGA _hoops_RH _hoops_SRGAI
 * _hoops_PSPSI _hoops_ACAS _hoops_ICGI _hoops_IRS _hoops_SRGS _hoops_SGS _hoops_SSCP _hoops_RH _hoops_GGHS _hoops_IS _hoops_RGRIR _hoops_SAPS _hoops_PPSR
 * _hoops_SPHS. */

#ifdef _hoops_IIIPA
#	 define X86_MASK_EXCEPTIONS(dwOldMode) \
		__asm fnstcw WORD PTR dwOldMode \
		__asm mov eax, dwOldMode \
		__asm or eax, 0x3f \
		__asm mov WORD PTR dwOldMode+2, ax \
		__asm fldcw WORD PTR dwOldMode+2

#	 define X86_RESTORE_MASK(dwOldMode) \
		__asm fnclex \
		__asm fldcw WORD PTR dwOldMode
#else
#	 define X86_MASK_EXCEPTIONS(x)
#	 define X86_RESTORE_MASK(x)
#endif

/*
 * _hoops_SRAC
 */
local void init_update (
	Display_Context const	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();
	RECT						_hoops_IGGAH;
#ifndef _WIN32_WCE
#ifdef _hoops_IIIPA
	if (state->_hoops_SSRRI == _hoops_RGARI) {
				int mode;
				X86_MASK_EXCEPTIONS(mode);
				state->_hoops_AHCCI = mode;
	}
#endif
#endif

	if (!state->_hoops_GAHCI) {
		/* _hoops_PS _hoops_GRS _hoops_AA _hoops_RGR _hoops_SPHR _hoops_GGR _hoops_GGSRH - _hoops_RGAR _hoops_AA _hoops_ARR */
		state->_hoops_CACCI = true;

		if (state->_hoops_AGICI) 
			ReleaseDC(state->_hoops_GGICI, state->_hoops_AGICI);

		/* _hoops_PS _hoops_RRP _hoops_IS _hoops_HGCR _hoops_RH _hoops_CSPH _hoops_PPR _hoops_HPAC _hoops_SCH _hoops_GAR _hoops_SR _hoops_ACRR */
		state->_hoops_AGICI = GetDC (state->_hoops_GGICI);
		/*
		 * _hoops_PS _hoops_RRP _hoops_IS _hoops_HGSR _hoops_HCR _hoops_RPPS _hoops_AAP -
		 * _hoops_GICSI/_hoops_PHIH _hoops_CSPH _hoops_GRS _hoops_HAR _hoops_IPHR _hoops_ARHI
		 * _hoops_RICSI/_hoops_AICSI _hoops_HCPH - _hoops_RH _hoops_SPRS _hoops_HRGR _hoops_SHPHP _hoops_GACC
		 */
#if 0
#ifndef _WIN32_WCE
#ifdef MINITAB
	SetTextAlign (state->_hoops_AGICI, TA_BOTTOM | TA_LEFT | TA_NOUPDATECP);
#else
	SetTextAlign (state->_hoops_AGICI, TA_BASELINE | TA_LEFT | TA_NOUPDATECP);
#endif
#endif
#endif

	_hoops_SHGSI (state);
	/* _hoops_AGGA _hoops_SR _hoops_RRP _hoops_IS _hoops_CSSCI _hoops_CPRAH _hoops_SSSCI _hoops_RPP _hoops_IRPR */
	if ((state->_hoops_PIGRR == _hoops_PPSGR ||
			state->_hoops_PIGRR == _hoops_HPSGR) &&
			state->_hoops_SRRRR) {
				state->_hoops_IGICI = state->_hoops_AGICI;
				state->_hoops_AGICI = state->_hoops_CGICI;
		}
	}

	if (state->_hoops_PIGRR == _hoops_PPSGR) {
		if (BIT(dc->flags, _hoops_SAISR) &&
			!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH))
			check_events (state);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		state = _hoops_HICCI ();
	}

	if (state != NULL) {
#ifndef _WIN32_WCE
		if (state->_hoops_PIGRR != _hoops_PSPCI &&
			(!IsWindow (state->_hoops_GGICI) ||
			IsIconic (state->_hoops_GGICI) ||
			!IsWindowVisible (state->_hoops_GGICI)))
			return;

		if (IsZoomed (state->_hoops_GGICI))
			((Display_Context alter *)dc)->options._hoops_PASSP = true;
#endif
		GetClientRect (state->_hoops_GGICI, &_hoops_IGGAH);

		if (!EqualRect (&_hoops_IGGAH, &state->_hoops_HIGRR)) {
			RECT	_hoops_PCRSP;

			CopyRect (&state->_hoops_HIGRR, &_hoops_IGGAH);
			GetWindowRect (state->_hoops_GGICI, &_hoops_PCRSP);

			state->yfudge = max (0, _hoops_IGGAH.bottom - 1);

			HD_Resize_Subscreen (dc, true,
								 0, _hoops_IGGAH.right - 1,
								 0, _hoops_IGGAH.bottom - 1);
		}
	}
}


/*
 * _hoops_SRAC
 */
local void get_current_info (
	Display_Context alter	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();
	HDC							_hoops_AGICI;


	if (!state->_hoops_GAHCI)
		switch (state->_hoops_HGICI) {
			case _hoops_IGHCI: {
				state->_hoops_PGICI = GetDC (GetDesktopWindow ());
			}	break;

			case _hoops_CGHCI: {
				state->_hoops_PGICI =
					get_printer_DC (dc->options._hoops_ARPSR);
			}	break;

			case _hoops_SCASA: {
				 state->_hoops_PGICI = state->_hoops_AGICI =
					(HDC) dc->options._hoops_ISPRP;
			}	break;
		}


	if (state->_hoops_AGICI == 0)
		_hoops_AGICI = state->_hoops_PGICI;
	else
		_hoops_AGICI = state->_hoops_AGICI;

	if (state->_hoops_PIGRR == _hoops_RSPCI) {
		  dc->current.border.right	=
		  dc->current.border.left	= (int)(0.015625f *
									  (float)GetDeviceCaps (_hoops_AGICI,
				LOGPIXELSX));
		  dc->current.border.bottom =
		  dc->current.border.top	= (int)(0.015625f *
									  (float)GetDeviceCaps (_hoops_AGICI,
				LOGPIXELSY));
		  dc->current.size.x = GetDeviceCaps(_hoops_AGICI, HORZSIZE) / 10.0f;
		  dc->current.size.y = GetDeviceCaps(_hoops_AGICI, VERTSIZE) / 10.0f;
		  return;
	}

	if (state->_hoops_PIGRR == _hoops_PSPCI)
	   return;

	if (state->_hoops_PIGRR == _hoops_ASPCI) {
	   if (dc->options.border) {
		  /*
		   * _hoops_PS _hoops_CHR _hoops_PPGP _hoops_IS _hoops_PSRAR _hoops_RH _hoops_ASCA _hoops_CCAC _hoops_HPP 1/64" _hoops_IIGR _hoops_PCCP
		   * _hoops_CPIHH _hoops_HCR _hoops_AARI _hoops_PGGA _hoops_IIGR _hoops_SIRCP _hoops_SPHS _hoops_PICSI _hoops_HPP
		   * _hoops_RH _hoops_HICSI _hoops_IICSI.  _hoops_HGI _hoops_HIRGR _hoops_RH _hoops_SPHGR _hoops_HCHSR
		   * _hoops_IS _hoops_CICSI _hoops_CRGH _hoops_GH _hoops_GPP _hoops_RH _hoops_SICSI _hoops_HIH _hoops_HRGR _hoops_HAR _hoops_IRS _hoops_RRHP
		   * _hoops_CGCHI.	_hoops_GCCSI _hoops_RH _hoops_RCCSI _hoops_CCPCR _hoops_CHH _hoops_SHH _hoops_AAH _hoops_HIH
		   * _hoops_AHCSI _hoops_GARIR _hoops_GPP _hoops_PCHC _hoops_PPAP _hoops_AGI (_hoops_HGPP _hoops_GAR _hoops_ACCSI
		   * _hoops_SAIA _hoops_PCCSI _hoops_GH _hoops_GPP 16 _hoops_IGRH _hoops_AGSHA _hoops_PGGA _hoops_RH _hoops_CCPCR
		   * _hoops_HIRGR _hoops_IRS _hoops_RPHSR _hoops_III _hoops_IS _hoops_SHH _hoops_PGSA _hoops_AARI _hoops_RH _hoops_GPIA)
		   */
		  dc->current.border.right	=
		  dc->current.border.left	= (int)(0.015625f *
									  (float)GetDeviceCaps (_hoops_AGICI,
				LOGPIXELSX));
		  dc->current.border.bottom =
		  dc->current.border.top	= (int)(0.015625f *
									  (float)GetDeviceCaps (_hoops_AGICI,
				LOGPIXELSY));
	   }
	   return;
	}

	_hoops_HGGAH (dc);

	if (dc->options.border) {
		HD_Allow_For_Border (dc,
				state->_hoops_ACGRR, state->_hoops_PCGRR,
				state->_hoops_RCGRR, state->_hoops_HCGRR);
	}

	if (!state->_hoops_GAHCI)
		switch (state->_hoops_HGICI)
		{
			case _hoops_IGHCI: {
				ReleaseDC (GetDesktopWindow (), state->_hoops_PGICI);
			}	break;

			case _hoops_CGHCI: {
				DeleteDC (state->_hoops_PGICI);
			}	break;

			case _hoops_SCASA: {
				/* _hoops_ARRP _hoops_IS _hoops_AA */
			}	break;
		}
}


/*
 * _hoops_SRAC
 */
local void init_picture (
	Net_Rendition const & nr) {
	MSW_Driver_State alter			*state = _hoops_IICCI ();
	Display_Context const	*dc = nr->_hoops_SRA;
	bool					_hoops_HCCSI;


	draw_and_reset_poly_cache(state, true);

	if (state->_hoops_GAHCI)
	switch (state->_hoops_PIGRR) {
		case _hoops_HPSGR: {
#ifndef _WIN32_WCE
			state->_hoops_SSHCI = GetROP2 (state->_hoops_AGICI);
#endif
			/* _hoops_PHIH _hoops_ISCP _hoops_PIAP */
			RestoreDC (state->_hoops_AGICI, state->_hoops_HSHCI);
		}	break;

		case _hoops_PSPCI: {
			if (state->_hoops_SAICI) {
				state->_hoops_GIICI = CreatePalette
						(state->_hoops_CHICI);

				SetPaletteEntries (state->_hoops_GIICI, 0,
								   state->_hoops_CHICI->palNumEntries,
								   &state->_hoops_CHICI->palPalEntry[0]);
				SelectPalette (state->_hoops_AGICI,
							   state->_hoops_GIICI,
							   FALSE);
				RealizePalette (state->_hoops_AGICI);

				OpenClipboard (NULL);
				SetClipboardData (CF_PALETTE,
						state->_hoops_GIICI);
				CloseClipboard ();

				state->_hoops_SAICI = false;
			}
		}	break;
	}
	else
		if (state->_hoops_CACCI) {
			/*
			 * _hoops_CPGP _hoops_SR _hoops_GHCA _hoops_HS _hoops_SAHR _hoops_ICCSI _hoops_RGR _hoops_CSPH _hoops_PPR _hoops_SR _hoops_AA _hoops_HAR _hoops_HHGC _hoops_IS _hoops_AA _hoops_RGR
			 * _hoops_CAIH _hoops_GGR _hoops_CCCSI (_hoops_CR _hoops_SCH _hoops_HRGR _hoops_AGIA _hoops_IS _hoops_ASRC _hoops_GAR _hoops_ICSI _hoops_GAR
			 * _hoops_SSRR
			 */
			SelectPalette (state->_hoops_AGICI, state->_hoops_GIICI, !state->_hoops_SRCCI);
			state->_hoops_CACCI = false;
		}

	/*
	 * _hoops_CGP _hoops_RH _hoops_RCPH _hoops_SPPPR _hoops_HRGR _hoops_SCCSI _hoops_SCH _hoops_HRGR _hoops_SSSHR _hoops_IS _hoops_PAAP _hoops_RH
	 * _hoops_IHCRH _hoops_RPP _hoops_SR _hoops_HS _hoops_GCAP _hoops_SHPH _hoops_PAR _hoops_RPP _hoops_SCH _hoops_SHPH _hoops_RGCI _hoops_PRGGR (_hoops_RPP _hoops_GII)
	 * _hoops_IIGR _hoops_RH _hoops_IHCRH - _hoops_RPP _hoops_AGAH _hoops_SSCP _hoops_GPGGR _hoops_RH _hoops_IHCRH _hoops_SCH _hoops_GRS _hoops_PAAP _hoops_RH _hoops_GHARR
	 * _hoops_IHCRH _hoops_ARI	 - _hoops_PIP _hoops_SGS _hoops_RGR _hoops_HRGR _hoops_RGAR _hoops_CPHR _hoops_RPP _hoops_CHARP _hoops_SSCP _hoops_HGAS _hoops_RH _hoops_IHCRH
	 */
#ifndef _WIN32_WCE
	if (!IsWindowVisible (state->_hoops_GGICI) ||
		(IsWindowVisible (state->_hoops_GGICI) && GetFocus () == state->_hoops_GGICI) ||
	(IsWindowVisible (state->_hoops_GGICI) && GetTopWindow(GetFocus()) == state->_hoops_GGICI))
		_hoops_HCCSI = true;
	else
		_hoops_HCCSI = false;
#endif
#if 0
	if (state->_hoops_CHICI != null && _hoops_HCCSI != state->_hoops_SRCCI) {
		state->_hoops_SAICI = true;
		if (state->_hoops_SRCCI) {
			/* _hoops_RAP _hoops_HCR _hoops_AIRP _hoops_SGS _hoops_CHR _hoops_IGI _hoops_IS _hoops_GSCSI */
			int i;
			for (i = 0; i < state->_hoops_CHICI->palNumEntries; i++)
				if (state->_hoops_SHICI[i])
					state->_hoops_CHICI->palPalEntry[i].peFlags = PC_NOCOLLAPSE;
		}
		else {
			/* _hoops_RAP _hoops_HCR _hoops_AIRP _hoops_SGS _hoops_CHR _hoops_IGI _hoops_IS _hoops_AHHR */
			int i;
			for (i = 0; i < state->_hoops_CHICI->palNumEntries; i++)
				if (state->_hoops_SHICI[i])
					state->_hoops_CHICI->palPalEntry[i].peFlags = 0;
		}
	}
#endif

	state->_hoops_SRCCI = _hoops_HCCSI;

#ifdef _hoops_GPISI
	/* _hoops_HGI _hoops_AGRP _hoops_IHIGR _hoops_RSCSI _hoops_CSPP _hoops_IS _hoops_IPHR - _hoops_ASCSI _hoops_PSCSI */
	/* !_hoops_HSCSI _hoops_PPR _hoops_ISCSI _hoops_CHR _hoops_IIP _hoops_IHPR			*/
	if (state->_hoops_SAICI ||
		 (state->_hoops_GAICI && state->_hoops_IRICI && state->_hoops_PHICI)) {
#else
	if ((state->_hoops_SAICI && (!state->_hoops_SACCI || state->_hoops_SRCCI)) ||
		 (state->_hoops_GAICI && state->_hoops_IRICI && state->_hoops_PHICI)) {
#endif

		/*
		 * _hoops_PS _hoops_HS _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_RH _hoops_SSRS _hoops_IPS _hoops_IIGR _hoops_RH _hoops_CSCSI
		 * _hoops_IGI _hoops_IH _hoops_GPRSI/_hoops_IPSP _hoops_PAPR _hoops_ASRCI _hoops_HRGR _hoops_GH _hoops_IS _hoops_ICGIP
		 * _hoops_HGCR _hoops_PCCP _hoops_PGGS _hoops_HAPR _hoops_ARI
		 */
		HDC	   _hoops_AGICI;

#ifdef _hoops_GPISI
		/* _hoops_HGI _hoops_AGRP _hoops_HRGR _hoops_SIGR _hoops_IH _hoops_SSCSI - _hoops_ASCSI _hoops_PSCSI */
		state->_hoops_SRCCI = true;
#endif

		if (state->_hoops_GAICI)
			_hoops_AGICI = state->_hoops_HRICI;
		else
			_hoops_AGICI = state->_hoops_AGICI;

		if (state->_hoops_PIGRR != _hoops_PSPCI)
				_hoops_RSCCI (state);

		COPY_MEMORY (state->_hoops_APICI,
							 state->_hoops_PPICI,
							 state->_hoops_CPICI);

		if (state->_hoops_PIGRR != _hoops_PSPCI) {
			if (state->_hoops_GGCCI && dc->options._hoops_RCHSR == 0) {
				HPALETTE		_hoops_GGSSI;

				_hoops_GGSSI = _hoops_HSCCI (state->_hoops_CHICI,
													256, state);

				SelectPalette (_hoops_AGICI, _hoops_GGSSI, !state->_hoops_SRCCI);

				DeleteObject (state->_hoops_GIICI);

				state->_hoops_GIICI = _hoops_GGSSI;

				RealizePalette (_hoops_AGICI);

				if (state->_hoops_SRRRR) {
					SelectPalette (state->_hoops_IGICI,
								   state->_hoops_GIICI,
								   !state->_hoops_SRCCI);
#ifndef _WIN32_WCE
					UnrealizeObject (state->_hoops_GIICI);
#endif
					RealizePalette (state->_hoops_IGICI);
				}
			}
			else {
				int		start, _hoops_RGSSI;

				start = _hoops_RGSSI = 0;
				while (_hoops_RGSSI < state->_hoops_CHICI->palNumEntries) {
					while (start < state->_hoops_CHICI->palNumEntries &&
						!state->_hoops_SHICI[start]) {
						start++;
					}
					_hoops_RGSSI = start;
					if (start < state->_hoops_CHICI->palNumEntries) {
						while (_hoops_RGSSI < state->_hoops_CHICI->palNumEntries &&
							state->_hoops_SHICI[_hoops_RGSSI]) {
							_hoops_RGSSI++;
						}
						SetPaletteEntries (state->_hoops_GIICI, start,
										   _hoops_RGSSI-start,
										   &state->_hoops_CHICI->palPalEntry[start]);
						start = _hoops_RGSSI;
					}
				}
				SelectPalette (_hoops_AGICI,
							   state->_hoops_GIICI,
							   !state->_hoops_SRCCI);
				if (state->_hoops_RGICI == 0 ||
					state->_hoops_RGICI == state->_hoops_GGICI) {
#ifndef _WIN32_WCE
					UnrealizeObject (state->_hoops_GIICI);
#endif
					RealizePalette (_hoops_AGICI);
				}
				else {
					SendMessage (state->_hoops_RGICI,
								 WM_QUERYNEWPALETTE, 0, 0L);
				}
				if (state->_hoops_SRRRR) {
					SelectPalette (state->_hoops_IGICI,
								   state->_hoops_GIICI,
								   !state->_hoops_SRCCI);
					if (state->_hoops_RGICI == 0 ||
						state->_hoops_RGICI == state->_hoops_GGICI) {
#ifndef _WIN32_WCE
						UnrealizeObject (state->_hoops_GIICI);
#endif
						RealizePalette (state->_hoops_IGICI);
					}
					else {
						SendMessage (state->_hoops_RGICI,
									 WM_QUERYNEWPALETTE, 0, 0L);
					}
				}
#ifdef _hoops_GPISI
			/* _hoops_AGSSI _hoops_AHCI _hoops_ACAGR _hoops_CAPP. */
			state->_hoops_SAICI = false;
#endif
			}

			if ((state->_hoops_RGCCI) &&
				state->_hoops_CRHCI != null) {
				int			i;
				_hoops_RGHCI   *_hoops_ARHSI = state->_hoops_CRHCI;

				/*
				 * _hoops_GSSRH _hoops_PHISI, _hoops_PSSP _hoops_RH _hoops_SARSI _hoops_HAIR _hoops_GASR _hoops_IS _hoops_RH
				 * _hoops_SCGR _hoops_IHCRH _hoops_IS _hoops_PSSP _hoops_RH _hoops_HHISI _hoops_IHCRH
				 */
				GetPaletteEntries (state->_hoops_GIICI, 0,
								   256, state->_hoops_RAHCI);
				/* _hoops_IHISI, _hoops_IHCRH _hoops_AIRP _hoops_CHR _hoops_PCCIR-_hoops_ISHI-_hoops_RCSR, _hoops_CHISI _hoops_CHR _hoops_RCSR-_hoops_ISHI-_hoops_PCCIR */
				for (i = 0; i < 256; ++i) {
					state->_hoops_AAHCI[i].rgbRed =
						state->_hoops_RAHCI[i].peRed;
					state->_hoops_AAHCI[i].rgbGreen =
						state->_hoops_RAHCI[i].peGreen;
					state->_hoops_AAHCI[i].rgbBlue =
						state->_hoops_RAHCI[i].peBlue;
					state->_hoops_AAHCI[i].rgbReserved = 0;
				}
				while (_hoops_ARHSI != null) {
#ifndef _WIN32_WCE
				   SetDIBColorTable (_hoops_ARHSI->dc, 0, 256, state->_hoops_AAHCI);
					_hoops_ARHSI = _hoops_ARHSI->_hoops_HGHCI;
#endif
				}
			}
		}
	}

#ifndef _hoops_GPISI
	/* _hoops_PGSSI - _hoops_RGR _hoops_GRS _hoops_SCAC _hoops_SCH _hoops_PRGI _hoops_RPP _hoops_IHCRH _hoops_HAR _hoops_ARP */
	state->_hoops_SAICI = false;
#endif

		GetClientRect (state->_hoops_GGICI, &state->_hoops_IIGRR);

	if (state->_hoops_SRRRR)
		state->_hoops_CAICI = false;
}


/*
 * _hoops_SRAC
 */
local void finish_picture (
	Net_Rendition const & nr,
	bool						swap_buffers) {
	Display_Context const		*dc = nr->_hoops_SRA;
	MSW_Driver_State alter				*state = _hoops_HICCI ();

	UNREFERENCED (swap_buffers);


	draw_and_reset_poly_cache(state, true);

	_hoops_ICRSI (state);

	if (state->_hoops_PIGRR == _hoops_ASPCI &&
		!BIT (dc->options._hoops_IRARR, _hoops_HPACI) &&
		state->_hoops_RCRAP == DT_PLOTTER) {
#ifndef _WIN32_WCE
		Escape (state->_hoops_AGICI, NEWFRAME, 0, NULL, NULL);
#endif
	}

	if (state->_hoops_SRRRR) {
		if (!_hoops_IACI(dc)) {
			/* _hoops_AIAP _hoops_PAAP */
			state->_hoops_CAICI = true;
			BitBlt (state->_hoops_IGICI, state->_hoops_IIGRR.left,
					state->_hoops_IIGRR.top,
					state->_hoops_IIGRR.right-state->_hoops_IIGRR.left,
					state->_hoops_IIGRR.bottom-state->_hoops_IIGRR.top,
					state->_hoops_AGICI,
					state->_hoops_IIGRR.left, state->_hoops_IIGRR.top,
					SRCCOPY);
		}
	}
	else {
		/*
		 * _hoops_HGSSI: _hoops_ACGPA _hoops_ASAI _hoops_IGSSI _hoops_RAIGR _hoops_IHHAH _hoops_CGSSI!  _hoops_HGAPR _hoops_ISCC _hoops_RCSPR _hoops_SGSSI!
		 * _hoops_GRSSI: _hoops_ACGPA _hoops_ASAI _hoops_IGSSI _hoops_RGGCI _hoops_RCSPR _hoops_RRSSI _hoops_ARSSI _hoops_IPACI _hoops_PCASR
		 */
		if (state->_hoops_GGICI &&
			!dc->options._hoops_CRSSP &&
			!BIT (nr->_hoops_SRA->options._hoops_IRARR, _hoops_GCCRH))
			ValidateRect (state->_hoops_GGICI, &state->_hoops_IIGRR);

		SetRectEmpty (&state->_hoops_IIGRR);
	}
#ifndef _WIN32_WCE
	GdiFlush ();
#endif

	if (state->_hoops_PIGRR == _hoops_HPSGR) {
		/*
		 * _hoops_CPCS _hoops_IRS _hoops_CSGSR _hoops_PAR _hoops_CSGSR _hoops_SR _hoops_SPIP
		 */
		SelectObject (state->_hoops_AGICI, state->_hoops_GHCCI);

		state->_hoops_CSC._hoops_RPCI = _hoops_CCC;
		state->_hoops_CSC._hoops_GCICI = _hoops_CCC;

		SelectObject (state->_hoops_AGICI, state->_hoops_CPCCI);
		state->_hoops_CSC.font = _hoops_CCICI;

		if (state->_hoops_GAHCI) {
			state->_hoops_HSHCI = SaveDC (state->_hoops_AGICI);
			SetROP2 (state->_hoops_AGICI, state->_hoops_SSHCI);
		}
	}
	if (state->_hoops_GAHCI)
		switch (state->_hoops_PIGRR) {
			case _hoops_RSPCI:{
				/* _hoops_RPP !_hoops_IRCSI _hoops_PSCR _hoops_IPS _hoops_IS _hoops_CHACI */
				if (dc->options._hoops_GCHSR && dc->options._hoops_RGHRP == _hoops_GGHRP && state->_hoops_IHGRR) {
					_hoops_PRCSI(dc);
				} 
			}	break;

			default: {
				/* _hoops_AA _hoops_ISAP _hoops_IH _hoops_HIASR? */
			}
	}

}


/*
 * _hoops_SRAC
 */
local void finish_update (
	Display_Context const	*dc) {
	MSW_Driver_State alter			*state = _hoops_HICCI ();

#ifndef _WIN32_WCE
	if (state->_hoops_SSRRI == _hoops_RGARI) {
		int mode = state->_hoops_AHCCI;
		X86_RESTORE_MASK(mode);
		UNREFERENCED(mode);
	}
#endif

	if (!state->_hoops_GAHCI) {
		/* _hoops_PS _hoops_RRP _hoops_IS _hoops_HGCR _hoops_RH _hoops_CSPH _hoops_PPR _hoops_HPAC _hoops_SCH _hoops_GAR _hoops_SR _hoops_ACRR */
		if ((state->_hoops_PIGRR == _hoops_PPSGR ||
			state->_hoops_PIGRR == _hoops_HPSGR) &&
			state->_hoops_SRRRR) {
				state->_hoops_AGICI = state->_hoops_IGICI;
		}
		ReleaseDC (state->_hoops_GGICI, state->_hoops_AGICI);
		state->_hoops_AGICI = null;
	}

	if (state->_hoops_SSRRI == _hoops_PHRCI && state->_hoops_PIGRR == _hoops_HPSGR) {
		char event_string[255];

		HI_Queue_Special_Event (dc->_hoops_RIGC, "MSW:FinishUpdate",
			HI_Build_Special_Event_String (event_string,"MSW",dc->_hoops_AAHSR,
				(POINTER_SIZED_INT)state->_hoops_GGICI, -1));
	}


	if (state->_hoops_PIGRR == _hoops_PPSGR) {
		if (BIT(dc->flags, _hoops_SAISR) &&
			!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH))
			check_events (state);
	}
}



/*
 * _hoops_SRAC
 * _hoops_RPP _hoops_GHGPR _hoops_RHGPR, _hoops_RGR _hoops_PIHA _hoops_SHH _hoops_PIGS _hoops_ARPP _hoops_RH _hoops_GGSHR _hoops_PSCA
 */
local bool
snapshot(
	Net_Rendition const &  nr,
	int width,
	int height,
	unsigned char * data) {

	MSW_Driver_State alter *state = _hoops_IICCI ();

	if(!state->_hoops_IHGRR){
		Int_Rectangle const * area = &nr->_hoops_SAIR->_hoops_SCIH; 
		int w,h;
		int x,y; 
		COLORREF color;

		w = area->right - area->left + 1;
		h = area->top - area->bottom + 1;

		if (w*h > width*height) return false;
				
		draw_and_reset_poly_cache(state, true);
		_hoops_ICRSI (state);

	#ifndef _WIN32_WCE
		GdiFlush ();
	#endif

		/*0x00bb_hoops_PRSSI*/ 
		for (y=0;y<h;y++) {
			for (x=0;x<w;x++) {
			
				color = GetPixel(state->_hoops_AGICI, x, y);
	 
				*data++ = (unsigned char)(0x000000FF&(color));
				*data++ = (unsigned char)(0x000000FF&(color>>8));
				*data++ = (unsigned char)(0x000000FF&(color>>16));
			}
		}
	}
	else {
		int _hoops_HRCSI = 0;
		switch(state->_hoops_IHGRR->format){
			case _hoops_HHGH:
				_hoops_HRCSI = 3;
				break;

			case _hoops_HRSRH:
			case Image_RGBA32:
				_hoops_HRCSI = 4;
			break;

			default:
				return false;
		}

		unsigned char * _hoops_PHGH = (unsigned char*)state->_hoops_IHGRR->_hoops_PHGH;
		int _hoops_HRSSI = state->_hoops_IHGRR->width;
		int _hoops_IRSSI = width < _hoops_HRSSI ? width : _hoops_HRSSI;
		if(state->_hoops_IHGRR->format == _hoops_HHGH){
			for(int row = 0; row < height; ++row){
				int const _hoops_AHPCP = 3 * _hoops_HRSSI * row;
				int const _hoops_GIHSI = 3 * width * row;
				COPY_MEMORY(&_hoops_PHGH[_hoops_AHPCP], _hoops_IRSSI * 3, &data[_hoops_GIHSI]);
			}
		}
		else {
			for(int row = 0; row < height; ++row){
				int const _hoops_AHPCP = _hoops_HRCSI * _hoops_HRSSI * row;
				int const _hoops_GIHSI = 3 * width * row;
				for(int col = 0; col < _hoops_IRSSI; ++col)
					COPY_MEMORY(&_hoops_PHGH[_hoops_AHPCP + _hoops_HRCSI * col], 3, &data[_hoops_GIHSI + 3 * col]);
			}
		}
	}
	return true;
}



/*****************************************************************************
 *****************************************************************************
					  _hoops_PHRPI _hoops_HHRPI _hoops_PPR _hoops_SCHGR _hoops_CRSSI
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_SRAC
 */
local void _hoops_RSCSR (
	_hoops_APARR alter &		_hoops_RRCI) {

	_hoops_RRCI->start_device					= start_device;
	_hoops_RRCI->stop_device						= stop_device;

	_hoops_RRCI->get_physical_info				= get_physical_info;
	_hoops_RRCI->get_current_info				= get_current_info;

	_hoops_RRCI->init_update						= init_update;
	_hoops_RRCI->finish_update					= finish_update;

	_hoops_RRCI->init_picture					= init_picture;
	_hoops_RRCI->finish_picture					= finish_picture;

	_hoops_RRCI->get_outer_window				= get_outer_window;
	_hoops_RRCI->free_outer_window				= free_outer_window;
	_hoops_RRCI->_hoops_RSCSP				= _hoops_RSCSP;
	_hoops_RRCI->_hoops_ASCSP			= _hoops_ASCSP;

	_hoops_RRCI->draw_overlay_list				= draw_overlay_list;
	_hoops_RRCI->_hoops_SCPGR				= _hoops_SCPGR;

	_hoops_RRCI->draw_dc_polymarker				= draw_dc_polymarker;
	_hoops_RRCI->draw_dc_rectangle				= draw_dc_rectangle;
	_hoops_RRCI->draw_dc_polyline				= draw_dc_polyline;
	_hoops_RRCI->draw_dc_face					= draw_dc_face;
	_hoops_RRCI->_hoops_RPCGA					= _hoops_RPCGA;
	_hoops_RRCI->draw_dc_colorized_face			= draw_dc_colorized_face;
	_hoops_RRCI->draw_dc_polytriangle			= draw_dc_polytriangle;
	_hoops_RRCI->draw_dc_colorized_polytriangle	= draw_dc_colorized_polytriangle;
	_hoops_RRCI->_hoops_CCCGA				= _hoops_CCCGA;
	_hoops_RRCI->_hoops_GSCGA			= _hoops_GSCGA;
	_hoops_RRCI->_hoops_CCCSR			= _hoops_IAHSI;
	_hoops_RRCI->draw_dc_rgb32_rasters			= draw_dc_rgb32_rasters;

	_hoops_RRCI->draw_3d_nurbs_curve				= draw_3d_nurbs_curve;
	_hoops_RRCI->draw_3d_elliptical_arc			= draw_3d_elliptical_arc;
	_hoops_RRCI->draw_3d_ellipse					= draw_3d_ellipse;
	_hoops_RRCI->_hoops_CCISR			= _hoops_CCISR;
	_hoops_RRCI->draw_dc_ellipse					= draw_dc_ellipse;
	_hoops_RRCI->_hoops_SCISR			= _hoops_SCISR;

	_hoops_RRCI->_hoops_SCCSR			= _hoops_SCCSR;
	_hoops_RRCI->_hoops_ISCSP				= _hoops_ISCSP;
	_hoops_RRCI->_hoops_HSCSP				= _hoops_HSCSP;

	_hoops_RRCI->load_font						= load_font;
	_hoops_RRCI->unload_font						= unload_font;
	_hoops_RRCI->measure_char					= measure_char;
	_hoops_RRCI->draw_dc_text					= draw_dc_text;
	_hoops_RRCI->_hoops_AACSR					= _hoops_AACSR;
	_hoops_RRCI->_hoops_CACSR				= _hoops_CACSR;
	_hoops_RRCI->find_all_fonts					= find_all_fonts;
	_hoops_RRCI->_hoops_CSCSP						= _hoops_CSCSP;
	_hoops_RRCI->_hoops_RGSSP				= _hoops_RGSSP;
	_hoops_RRCI->_hoops_GGSSP				= _hoops_GGSSP;

	_hoops_RRCI->draw_window						= draw_window;

	_hoops_RRCI->snapshot = snapshot;
} /* _hoops_RSGR _hoops_API _hoops_SRAAH */



/*
 * _hoops_IAAAH _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_MSW_Driver (
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

#endif /* _hoops_SRSSI */
