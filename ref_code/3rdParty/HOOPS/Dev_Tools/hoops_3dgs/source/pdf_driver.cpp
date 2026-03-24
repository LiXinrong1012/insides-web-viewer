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
 * $Id: obf_tmp.txt 1.299 2011-01-20 01:16:46 reuben Exp $
 */

#include "hoops.h"
#include "hd_proto.h"

#ifndef PDF_DRIVER

extern "C" bool HC_CDECL
HD_PDF_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI, 
	int						request, 
	void *					request_info)
{
	UNREFERENCED (request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "pdf");
}

#else


#include "database.h"
#include "driver.h"

#include "filedata.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "patterns.h"
#include "please.h"
#include "searchh.h"
#include "tandt.h"
#include "span.h"
#include "hversion.h"
#include "adt.h"

#include <stdio.h>
#include <stdarg.h>
#include <locale.h>
#include <limits.h>

#if 0
#define _hoops_AHCRI(_hoops_PHCRI) printf("%s\n", _hoops_PHCRI)
#else
#define _hoops_AHCRI(_hoops_PHCRI)
#endif

#include <Zlib/zlib.h>

#define _hoops_PAACC 1024

/*******************************************************************************
 * _hoops_HAACC _hoops_HSCAR _hoops_PPR _hoops_GPCA
 ******************************************************************************/


/*****************************
 * _hoops_HAACC _hoops_GRIRH _hoops_RHASR
 ****************************

 * _hoops_IHAC - _hoops_PHIR _hoops_PPR _hoops_RGISR _hoops_RH _hoops_CRAA _hoops_GRP _hoops_RRAIA _hoops_CRARH _hoops_PHI _hoops_GRGPH
 * _hoops_IHAC* - _hoops_PHIR _hoops_PPR _hoops_RGISR _hoops_RH _hoops_CRAA _hoops_GRP _hoops_PRGI-_hoops_PISC _hoops_GRGPH
 * _hoops_RCSR - _hoops_IAACC, _hoops_CISA _hoops_PPR _hoops_RGISR _hoops_RH _hoops_CRAA _hoops_GRP _hoops_RRAIA _hoops_CRARH _hoops_PHI _hoops_GRGPH
 * _hoops_RCSR* - _hoops_IAACC, _hoops_CISA _hoops_PPR _hoops_RGISR _hoops_RH _hoops_CRAA _hoops_GRP _hoops_PRGI-_hoops_PISC _hoops_GRGPH
 * _hoops_GSGGR - _hoops_AGIS
 * _hoops_CAACC - _hoops_HAIR _hoops_GC
 * _hoops_GHGP - _hoops_GIPSR _hoops_HSGP
 * _hoops_RCHP - _hoops_CISA _hoops_CRAA _hoops_GRP _hoops_RRAIA _hoops_CRARH _hoops_PHI _hoops_GRGPH
 * _hoops_RCHP* - _hoops_CISA _hoops_CRAA _hoops_GRP _hoops_PRGI-_hoops_PISC _hoops_GRGPH
 * _hoops_GGHR - _hoops_SPGCA _hoops_CGHI _hoops_PPSR _hoops_IS _hoops_SRS _hoops_PPSR _hoops_GGR _hoops_CRAA (_hoops_APRAR _hoops_CRAA)
 * _hoops_SAACC - _hoops_RGAIA _hoops_GPACC
 * _hoops_PPHR - _hoops_RGAIA _hoops_RPACC
 * _hoops_GSSAA - _hoops_III _hoops_IS (_hoops_HII _hoops_CGHI _hoops_PPSR _hoops_GGR _hoops_CRAA)
 * _hoops_SPHAI - _hoops_IHIS _hoops_IS (_hoops_RPGH _hoops_CCAH _hoops_CRAA)
 * _hoops_ACHP - _hoops_RSGR _hoops_RH _hoops_CRAA _hoops_SIHH _hoops_SHRAA _hoops_PAR _hoops_APACC
 * _hoops_GAIHI - _hoops_CIHPA _hoops_HAIR _hoops_GC/_hoops_CIHH _hoops_PIAP _hoops_GPP _hoops_HAIR _hoops_GC _hoops_RRGC
 * _hoops_ARHHI - _hoops_AISI _hoops_HAIR _hoops_GC/_hoops_CIHH _hoops_PIAP _hoops_GPP _hoops_HAIR _hoops_GC _hoops_RRGC
 * _hoops_ASAR - _hoops_ARRGR
 * _hoops_PPACC - _hoops_ARP _hoops_RGISR _hoops_HAIR
 * _hoops_HPACC _hoops_GPHHC _hoops_ARP _hoops_CISA _hoops_HAIR
 * _hoops_IISGA - _hoops_IPACC _hoops_CRAA
 * _hoops_GRI - _hoops_IAACC _hoops_PPR _hoops_RGISR _hoops_IRS _hoops_CRAA (_hoops_PSHR _hoops_HRGR "_hoops_GGHR _hoops_IISGA")
 * _hoops_ARSIC - _hoops_CPHP _hoops_IS _hoops_AA _hoops_CCA _hoops_HSP _hoops_PAIA
 * _hoops_CPACC - _hoops_HRCSR _hoops_IGIR (_hoops_GGR _hoops_RSSA)
 * _hoops_SRSCI - _hoops_IACSH _hoops_GRP _hoops_RH _hoops_RRAIA _hoops_CRARH _hoops_PHI _hoops_GRGPH _hoops_IS _hoops_CGIC _hoops_PGAP _hoops_PGHH _hoops_PRCS _hoops_ASSA _hoops_RH _hoops_CIHH _hoops_CRAA
 * _hoops_SRSCI* - _hoops_IACSH _hoops_GRP _hoops_RH _hoops_PRGI-_hoops_PISC _hoops_GRGPH _hoops_IS _hoops_CGIC _hoops_PGAP _hoops_PGHH _hoops_PRCS _hoops_ASSA _hoops_RH _hoops_CIHH _hoops_CRAA
 * _hoops_SSCHA - _hoops_III _hoops_SGCR

 *****************************
 * _hoops_HAACC _hoops_GRIRH _hoops_RHASR
 ****************************/

struct _hoops_SPACC;
struct _hoops_GHACC;
struct _hoops_RHACC;
struct _hoops_AHACC;
struct _hoops_PHACC;
struct _hoops_HHACC;

typedef VList < _hoops_SPACC * >_hoops_IHACC;
typedef VList < _hoops_RHACC * >_hoops_CHACC;
typedef VList < _hoops_AHACC * >_hoops_SHACC;
typedef VList < _hoops_PHACC * >_hoops_GIACC;
typedef VList < _hoops_HHACC * >_hoops_RIACC;



struct _hoops_GHACC
{
	FILE *_hoops_PAGR;
	struct _hoops_AHACC *_hoops_AIACC;
	_hoops_CHACC *_hoops_PIACC;
	_hoops_SHACC *_hoops_HIACC;
	_hoops_GIACC *font_list;
	bool error;
	int _hoops_IIACC;
	int _hoops_CIACC;
	int _hoops_SIACC, _hoops_GCACC;
	int _hoops_RCACC;
};

/* _hoops_RPP _hoops_ACACC _hoops_PAH'_hoops_RA _hoops_SHH _hoops_PSPP,
 * _hoops_PCACC _hoops_GRS _hoops_SHH _hoops_RH _hoops_HSSC _hoops_ISSC _hoops_IGIR. */
#define _hoops_HCACC (32000)
#define _hoops_ICACC (4000)
#define _hoops_CCACC (1000)

struct _hoops_SPACC
{
	unsigned char *buffer;
	int _hoops_RSIGR;
	int _hoops_SCACC;
};

struct _hoops_GSACC
{
	unsigned char r, g, b;
};

/*	_hoops_RSACC _hoops_AIGHH _hoops_PIH _hoops_HRPR _hoops_PPR _hoops_SGSS _hoops_API _hoops_IS _hoops_ARPR, _hoops_HSPC
 *	_hoops_PPR _hoops_HAGGR _hoops_IRS _hoops_AIGHH.
 */

#define _hoops_ASACC 0x1
#define _hoops_PSACC 0x2

enum
{
	PDF_ZLIB = 1,
	_hoops_HSACC = 0
};

struct _hoops_ISACC
{
	int id;
	_hoops_IHACC *_hoops_CSACC;
	_hoops_SPACC *_hoops_SSACC;
	int _hoops_GGPCC;
	int _hoops_RGPCC;
	struct z_stream_s zstream;
};

local _hoops_ISACC *
_hoops_AGPCC (_hoops_GHACC * _hoops_PGPCC, int id)
{
	_hoops_ISACC *_hoops_CIPAH;

	ALLOC (_hoops_CIPAH, _hoops_ISACC);
	_hoops_CIPAH->id = id;
	_hoops_CIPAH->_hoops_RGPCC = _hoops_CIPAH->_hoops_GGPCC = 0;
	_hoops_CIPAH->_hoops_SSACC = 0;
	_hoops_CIPAH->_hoops_CSACC = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_IHACC)(HOOPS_WORLD->memory_pool);

	_hoops_CIPAH->zstream.zalloc = Z_NULL;
	_hoops_CIPAH->zstream.zfree = Z_NULL;
	_hoops_CIPAH->zstream.data_type = Z_ASCII;
	_hoops_CIPAH->zstream.next_out = 0;
	_hoops_CIPAH->zstream.avail_out = 0;
	_hoops_CIPAH->zstream.next_in = 0;
	_hoops_CIPAH->zstream.avail_in = 0;

	if (deflateInit (&_hoops_CIPAH->zstream, Z_DEFAULT_COMPRESSION) != Z_OK) {
		HE_ERROR (HEC_PDF_DRIVER, HES_DISK_FULL,
			  "Error writing PDF file - zlib stream initialization failed.");
		_hoops_PGPCC->error = true;
	}

	return (_hoops_CIPAH);
}

local void
_hoops_HGPCC(_hoops_ISACC * _hoops_CIPAH, int length)
{
	/* _hoops_CGP _hoops_IIH _hoops_HRGR _hoops_PSP _hoops_SCGR _hoops_ASIRR _hoops_SRHR _hoops_PAR _hoops_RH _hoops_CGHI _hoops_SPR _hoops_HRGR _hoops_IHIR _hoops_IGPCC... */
	if (!_hoops_CIPAH->_hoops_SSACC ||
	    _hoops_CIPAH->_hoops_SSACC->_hoops_SCACC == _hoops_CIPAH->_hoops_SSACC->_hoops_RSIGR) {
		_hoops_SPACC *_hoops_CGPCC = 0;

		ALLOC (_hoops_CGPCC, _hoops_SPACC);

		/* _hoops_IIPP _hoops_IRS _hoops_PSGR _hoops_IGIR _hoops_SRHR _hoops_ARI _hoops_IH _hoops_ACHPR _hoops_PPR _hoops_HICIP. */
		if (length <= _hoops_CCACC) {
			_hoops_CGPCC->_hoops_RSIGR = _hoops_CCACC;
		}
		else if (length >= _hoops_HCACC) {
			_hoops_CGPCC->_hoops_RSIGR = _hoops_HCACC;
		}
		else {
			_hoops_CGPCC->_hoops_RSIGR = length;
		}
		/* _hoops_IIPP _hoops_HPIH _hoops_SRHR _hoops_IS _hoops_CRCC _hoops_ISCP _hoops_AIGHH _hoops_PIH */
		TRY_ALLOC_ARRAY (_hoops_CGPCC->buffer, _hoops_CGPCC->_hoops_RSIGR, unsigned char);
		if (!_hoops_CGPCC->buffer) {
			_hoops_CGPCC->_hoops_RSIGR = _hoops_ICACC;
			ALLOC_ARRAY (_hoops_CGPCC->buffer, _hoops_CGPCC->_hoops_RSIGR, unsigned char);
		}
		_hoops_CGPCC->_hoops_SCACC = 0;

		/* _hoops_RGPA _hoops_RGR _hoops_SGPCC _hoops_IIGR _hoops_PIH _hoops_IS _hoops_RH _hoops_AIGHH'_hoops_GRI _hoops_ASIRR _hoops_HIGR. */
		_hoops_CIPAH->_hoops_CSACC->AddLast (_hoops_CGPCC);
		_hoops_CIPAH->_hoops_SSACC = _hoops_CGPCC;
	}
}

local void
_hoops_GRPCC (_hoops_GHACC * _hoops_PGPCC, _hoops_ISACC * _hoops_CIPAH)
{
	_hoops_SPACC *_hoops_CGPCC;
	int _hoops_IA;

	if (_hoops_PGPCC->_hoops_RCACC == PDF_ZLIB) {
		_hoops_HGPCC(_hoops_CIPAH, 0);
		_hoops_CGPCC = _hoops_CIPAH->_hoops_SSACC;
		/* _hoops_CGP _hoops_IIH'_hoops_GRI _hoops_PSP _hoops_RRI _hoops_IIPR _hoops_SRHR _hoops_IS _hoops_PPSI _hoops_SGRH _hoops_PIH... */
		if (_hoops_CIPAH->zstream.avail_out == 0) {
			_hoops_CIPAH->zstream.next_out = _hoops_CGPCC->buffer + _hoops_CGPCC->_hoops_SCACC;
			_hoops_CIPAH->zstream.avail_out = _hoops_CGPCC->_hoops_RSIGR - _hoops_CGPCC->_hoops_SCACC;
		}
		_hoops_IA = deflate (&_hoops_CIPAH->zstream, Z_FINISH);
		ASSERT(_hoops_IA == Z_OK || _hoops_IA == Z_STREAM_END);
		int _hoops_RRPCC =
			_hoops_CGPCC->_hoops_RSIGR - _hoops_CGPCC->_hoops_SCACC - _hoops_CIPAH->zstream.avail_out;
		_hoops_CGPCC->_hoops_SCACC += _hoops_RRPCC;
		_hoops_CIPAH->_hoops_RGPCC += _hoops_RRPCC;
		while (_hoops_IA == Z_OK) {

			int length = _hoops_CIPAH->zstream.avail_in;

			_hoops_HGPCC(_hoops_CIPAH, length);
			_hoops_CGPCC = _hoops_CIPAH->_hoops_SSACC;

			/* _hoops_CGP _hoops_IIH'_hoops_GRI _hoops_PSP _hoops_RRI _hoops_IIPR _hoops_SRHR _hoops_IS _hoops_PPSI _hoops_SGRH _hoops_PIH... */
			if (_hoops_CIPAH->zstream.avail_out == 0) {
				_hoops_CIPAH->zstream.next_out = _hoops_CGPCC->buffer + _hoops_CGPCC->_hoops_SCACC;
				_hoops_CIPAH->zstream.avail_out = _hoops_CGPCC->_hoops_RSIGR - _hoops_CGPCC->_hoops_SCACC;
			}

			/* _hoops_IAAH _hoops_RH _hoops_SRHR */
			_hoops_IA = deflate (&_hoops_CIPAH->zstream, Z_FINISH);

			_hoops_RRPCC = _hoops_CGPCC->_hoops_RSIGR - _hoops_CIPAH->zstream.avail_out;
			_hoops_CGPCC->_hoops_SCACC = _hoops_RRPCC;
			_hoops_CIPAH->_hoops_RGPCC += _hoops_RRPCC;
		}
	}

	_hoops_IA = deflateEnd (&_hoops_CIPAH->zstream);
	ASSERT(_hoops_IA == Z_OK);
}

local void
_hoops_ARPCC (_hoops_ISACC * _hoops_CIPAH)
{
	_hoops_SPACC *_hoops_CGPCC;

	while ((_hoops_CGPCC = _hoops_CIPAH->_hoops_CSACC->RemoveFirst ()) != null) {
		FREE_ARRAY (_hoops_CGPCC->buffer, _hoops_CGPCC->_hoops_RSIGR, unsigned char);
		FREE (_hoops_CGPCC, _hoops_SPACC);
	}
	delete _hoops_CIPAH->_hoops_CSACC;
	FREE (_hoops_CIPAH, _hoops_ISACC);
	return;
}

#define _hoops_PRPCC(_hoops_CIPAH) do{_hoops_ARPCC((_hoops_CIPAH)); _hoops_CIPAH = 0;}while (0)

/* _hoops_HCSH _hoops_IIGR _hoops_RH _hoops_RSACC _hoops_AIGHH _hoops_CIPH... */

struct _hoops_HHACC
{
	int id;
	_hoops_ISACC *_hoops_CIPAH;
	int width, height, _hoops_RCHA;
};

struct _hoops_AHACC
{
	int id;
	/* _hoops_IGAA _hoops_PPR _hoops_APPS _hoops_CHR _hoops_GGR _hoops_RSSA (1/72.0 * _hoops_IPIHH) _hoops_ARI. */
	int width, height;
	_hoops_ISACC *_hoops_CIPAH;
	_hoops_RIACC *_hoops_HRPCC;
	_hoops_GIACC *font_list;
};

struct _hoops_IRPCC
{
	int id;
	int _hoops_CRPCC;
	_hoops_ISACC *_hoops_CIPAH;
	char *filename;
};

struct _hoops_SRPCC
{
	int id;
	char *_hoops_GAPCC;
	int Flags;
	_hoops_IRPCC *_hoops_RAPCC;
	int xmin, xmax, ymin, ymax;
};

struct _hoops_PHACC
{
	int id;
	char *_hoops_AAPCC;
	char *_hoops_PAPCC;
	int _hoops_HAPCC;
	int _hoops_IAPCC;
	unsigned char const *_hoops_HSISR;
	_hoops_SRPCC *_hoops_CAPCC;
};

/*	_hoops_HSIGP _hoops_SAPCC _hoops_IH _hoops_RHHP _hoops_AIAAH.  _hoops_IPCP _hoops_SHHP _hoops_CGRPR _hoops_GASR _hoops_HRGR
 *	_hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_RSACC _hoops_RGHR _hoops_PPR _hoops_ICGI _hoops_RH _hoops_CARA _hoops_SHI (_hoops_GGR _hoops_GCSRR)
 *	_hoops_CRGR _hoops_RH _hoops_RGHR.  _hoops_IPCP 3_hoops_IAPPA _hoops_CARRA _hoops_GGR _hoops_RH _hoops_GASR _hoops_AGCCA _hoops_IS _hoops_CARA 3 _hoops_PPR
 *	_hoops_HIS _hoops_GPP...
 */
struct _hoops_RHACC
{
	long offset;
	int id;
};

static _hoops_RHACC *
_hoops_GPPCC (int id, long offset)
{
	_hoops_RHACC *_hoops_RPPCC;
	ALLOC (_hoops_RPPCC, _hoops_RHACC);
	_hoops_RPPCC->id = id;
	_hoops_RPPCC->offset = offset;
	return (_hoops_RPPCC);
}

enum
{
	_hoops_APPCC = 0,
	_hoops_PPPCC,
	_hoops_HPPCC,
	_hoops_IPPCC,
	_hoops_CPPCC,
	_hoops_SPPCC,
	_hoops_GHPCC,
	_hoops_RHPCC,
	_hoops_AHPCC,
	_hoops_PHPCC,
	_hoops_HHPCC,
	_hoops_IHPCC,
	_hoops_CHPCC,
	_hoops_SHPCC
};

local int
_hoops_GIPCC (_hoops_GHACC * _hoops_PGPCC)
{
	int retval = _hoops_PGPCC->_hoops_IIACC++;
	return (retval);
}

local bool
_hoops_RIPCC (_hoops_GHACC * _hoops_PGPCC)
{
	bool retval = false;
	if (ferror (_hoops_PGPCC->_hoops_PAGR)) {
		HE_ERROR (HEC_PDF_DRIVER, HES_DISK_FULL,
			  "Error writing PDF file - the disk may be full");
		_hoops_PGPCC->error = retval = true;
	}
	return (retval);
}

local size_t
_hoops_AIPCC (void *ptr, size_t size, size_t _hoops_PIPCC, _hoops_GHACC * _hoops_PGPCC)
{
	size_t retval = 0;
	if (!_hoops_PGPCC->error && !_hoops_RIPCC (_hoops_PGPCC))
		retval = fwrite (ptr, size, _hoops_PIPCC, _hoops_PGPCC->_hoops_PAGR);
	return (retval);
}

#if defined WIN32_SYSTEM && !defined NUTCRACKER
# define vsnprintf(a, sa, f, va) _vsnprintf(a, sa, f, va)
#endif

class _hoops_HIPCC
{
      private:
	char _hoops_IIPCC[4096];

      public:
	  _hoops_HIPCC ()
	{
		strcpy (_hoops_IIPCC, "");
		char const *_hoops_CIPCC = setlocale (LC_ALL, 0);
		if (_hoops_CIPCC != 0)
			  strcpy (_hoops_IIPCC, _hoops_CIPCC);
		  setlocale (LC_ALL, "C");
		  setlocale (LC_CTYPE, "");
	}

	 ~_hoops_HIPCC ()
	{
		setlocale (LC_ALL, _hoops_IIPCC);
	}
};

local int
_hoops_SIPCC (char *str, size_t size, char const *format, va_list _hoops_CAARA)
{
	int _hoops_GCPCC = 0;

	_hoops_GCPCC = vsnprintf (str, size, format, _hoops_CAARA);

	return (_hoops_GCPCC);
}

local int
_hoops_RCPCC (_hoops_GHACC * _hoops_PGPCC, char const *format, ...)
{
	char *buffer = 0;
	int _hoops_ACPCC = 0, _hoops_GCPCC = -1;
	va_list _hoops_CAARA;

	if (_hoops_PGPCC->error)
		return (0);

	_hoops_ACPCC = (int) _hoops_SSGR (format) + 128;

	ALLOC_ARRAY (buffer, _hoops_ACPCC, char);
	va_start (_hoops_CAARA, format);
	_hoops_GCPCC = _hoops_SIPCC (buffer, _hoops_ACPCC, format, _hoops_CAARA);
	va_end (_hoops_CAARA);
	while (_hoops_GCPCC < 0 || _hoops_GCPCC > _hoops_ACPCC) {
		FREE_ARRAY (buffer, _hoops_ACPCC, char);
		_hoops_ACPCC *= 2;
		ALLOC_ARRAY (buffer, _hoops_ACPCC, char);
		va_start (_hoops_CAARA, format);
		_hoops_GCPCC = _hoops_SIPCC (buffer, _hoops_ACPCC, format, _hoops_CAARA);
		va_end (_hoops_CAARA);
	}

	_hoops_AIPCC (buffer, sizeof (char), _hoops_GCPCC, _hoops_PGPCC);
	FREE_ARRAY (buffer, _hoops_ACPCC, char);

	return (_hoops_GCPCC);
}

local int
_hoops_PCPCC (_hoops_GHACC * _hoops_PGPCC)
{
	return (ftell (_hoops_PGPCC->_hoops_PAGR));
}

local void
_hoops_HCPCC (_hoops_GHACC * _hoops_PGPCC)
{
	fclose (_hoops_PGPCC->_hoops_PAGR);
	return;
}

local void
_hoops_ICPCC (_hoops_GHACC * _hoops_PGPCC, _hoops_ISACC * _hoops_CIPAH)
{
	_hoops_SPACC *_hoops_CGPCC = 0;

	_hoops_CIPAH->_hoops_CSACC->ResetCursor ();

	while ((_hoops_CGPCC = _hoops_CIPAH->_hoops_CSACC->PeekCursor ()) != null) {
		_hoops_AIPCC (_hoops_CGPCC->buffer, _hoops_CGPCC->_hoops_SCACC, 1, _hoops_PGPCC);
		_hoops_CIPAH->_hoops_CSACC->AdvanceCursor ();
	}
}

local void
_hoops_CCPCC (_hoops_GHACC * _hoops_PGPCC, _hoops_HHACC * image)
{
	_hoops_RHACC *_hoops_RPPCC;


	_hoops_RPPCC = _hoops_GPPCC (image->id, _hoops_PCPCC (_hoops_PGPCC));
	_hoops_PGPCC->_hoops_PIACC->AddLast (_hoops_RPPCC);
	_hoops_GRPCC (_hoops_PGPCC, image->_hoops_CIPAH);
	_hoops_RCPCC (_hoops_PGPCC,
		   "%d 0 obj\n"
		   "<< "
		   "/Type /XObject "
		   "/Subtype /Image "
		   "/Width %d "
		   "/Height %d "
		   "/ColorSpace /DeviceRGB "
		   "/BitsPerComponent %d "
		   "/Length %d "
		   "%s "
		   ">>\n"
		   "stream\n",
		   image->id,
		   image->width, image->height,
		   image->_hoops_RCHA,
		   image->_hoops_CIPAH->_hoops_RGPCC,
		   (_hoops_PGPCC->_hoops_RCACC == PDF_ZLIB) ? "/Filter [/FlateDecode]" : "");
	_hoops_ICPCC (_hoops_PGPCC, image->_hoops_CIPAH);
	_hoops_PRPCC (image->_hoops_CIPAH);
	_hoops_RCPCC (_hoops_PGPCC, "\nendstream\n" "endobj\n\n");
	return;
}

/* _hoops_HGI _hoops_API _hoops_HRGR _hoops_PIGS _hoops_HII _hoops_SCPCC. _hoops_HSRR _hoops_GRR _hoops_HSHIA _hoops_GGR _hoops_RH _hoops_GSPCC, _hoops_RGR _hoops_API _hoops_CIGCP _hoops_GGSR _hoops_RH _hoops_HSHIA
 * _hoops_CARA, _hoops_RH _hoops_HSHIA'_hoops_GRI _hoops_ASIRR _hoops_AIGHH _hoops_CARA. _hoops_SHHP _hoops_CGRPR _hoops_PCAPA _hoops_CHR _hoops_RPIAH
 * _hoops_IS _hoops_RH _hoops_HSIGP _hoops_GASR _hoops_IH _hoops_GRR _hoops_CARA _hoops_RGR _hoops_API _hoops_CIGCP. */
local void
_hoops_RSPCC (_hoops_GHACC * _hoops_PGPCC, _hoops_AHACC * _hoops_ASPCC)
{
	_hoops_RHACC *_hoops_RPPCC;
	_hoops_HHACC *image;
	_hoops_PHACC *font;


	/* _hoops_GGI _hoops_GGSR _hoops_RH _hoops_HSHIA _hoops_CARA */
	_hoops_RPPCC = _hoops_GPPCC (_hoops_ASPCC->id, _hoops_PCPCC (_hoops_PGPCC));
	_hoops_PGPCC->_hoops_PIACC->AddLast (_hoops_RPPCC);
	_hoops_RCPCC (_hoops_PGPCC,
		   "%d 0 obj\n"
		   "<< "
		   "/Type /Page "
		   "/Parent %d 0 R "
		   "/MediaBox [0 0 %d %d] ", _hoops_ASPCC->id, _hoops_PGPCC->_hoops_GCACC, _hoops_ASPCC->width, _hoops_ASPCC->height);
	if (_hoops_ASPCC->_hoops_CIPAH->_hoops_RGPCC > 0) {
		_hoops_RCPCC (_hoops_PGPCC, "/Contents %d 0 R ", _hoops_ASPCC->_hoops_CIPAH->id);
	}
	_hoops_RCPCC (_hoops_PGPCC, "/Resources " "<< " "/ProcSet [/PDF /Text /ImageA /ImageB /ImageC] ");

	if (_hoops_ASPCC->_hoops_HRPCC->Count () > 0) {
		_hoops_RCPCC (_hoops_PGPCC, "/XObject << ");
		_hoops_ASPCC->_hoops_HRPCC->ResetCursor ();
		while ((image = _hoops_ASPCC->_hoops_HRPCC->PeekCursor ()) != null) {
			_hoops_RCPCC (_hoops_PGPCC, "/I%x %d 0 R ", image->id, image->id);
			_hoops_ASPCC->_hoops_HRPCC->AdvanceCursor ();
		}
		_hoops_RCPCC (_hoops_PGPCC, ">> ");
	}
	if (_hoops_ASPCC->font_list->Count () > 0) {
		_hoops_RCPCC (_hoops_PGPCC, "/Font << ");
		_hoops_ASPCC->font_list->ResetCursor ();
		while ((font = _hoops_ASPCC->font_list->PeekCursor ()) != null) {
			_hoops_RCPCC (_hoops_PGPCC, "/F%x %d 0 R ", font->id, font->id);
			_hoops_ASPCC->font_list->AdvanceCursor ();
		}
		_hoops_RCPCC (_hoops_PGPCC, ">> ");
	}
	_hoops_RCPCC (_hoops_PGPCC, ">> "	/* _hoops_RSGR _hoops_ASPP */
		   ">>\n"	/* _hoops_RSGR _hoops_AGPAI _hoops_PSPCC */
		   "endobj\n\n");

	/* _hoops_GGI _hoops_GGSR _hoops_RGR _hoops_HSHIA'_hoops_GRI _hoops_ASIRR _hoops_CARA.  _hoops_IPCP _hoops_ASIRR _hoops_CARA _hoops_ICGI _hoops_CAGA-_hoops_PII _hoops_RGCAI _hoops_IS _hoops_PGSA _hoops_CIPH _hoops_GPP _hoops_RH _hoops_HSHIA. */
	_hoops_RPPCC = _hoops_GPPCC (_hoops_ASPCC->_hoops_CIPAH->id, _hoops_PCPCC (_hoops_PGPCC));
	_hoops_PGPCC->_hoops_PIACC->AddLast (_hoops_RPPCC);
	_hoops_GRPCC (_hoops_PGPCC, _hoops_ASPCC->_hoops_CIPAH);
	_hoops_RCPCC (_hoops_PGPCC,
		   "%d 0 obj\n"
		   "<< /Length %d "
		   "%s "
		   ">>\n"
		   "stream\n",
		   _hoops_ASPCC->_hoops_CIPAH->id,
		   _hoops_ASPCC->_hoops_CIPAH->_hoops_RGPCC,
		   (_hoops_PGPCC->_hoops_RCACC == PDF_ZLIB) ? "/Filter [/FlateDecode]" : "");
	_hoops_ICPCC (_hoops_PGPCC, _hoops_ASPCC->_hoops_CIPAH);
	_hoops_PRPCC (_hoops_ASPCC->_hoops_CIPAH);

	_hoops_RCPCC (_hoops_PGPCC, "\nendstream\n" "endobj\n\n");

	/* _hoops_APSHR _hoops_GH _hoops_RH _hoops_CSCR _hoops_HSPCC.  _hoops_IPCP _hoops_ISPCC _hoops_GGR _hoops_AGCR _hoops_CARA _hoops_CHR _hoops_AIAH _hoops_HGGPR (_hoops_ICGSI). */
	while ((image = _hoops_ASPCC->_hoops_HRPCC->RemoveFirst ()) != null) {
		FREE (image, _hoops_HHACC);
	}
	delete _hoops_ASPCC->_hoops_HRPCC;
	delete _hoops_ASPCC->font_list;
	return;
}

local void
_hoops_CSPCC (_hoops_GHACC * _hoops_PGPCC, _hoops_PHACC * font)
{
	_hoops_RHACC *_hoops_RPPCC;
	_hoops_SRPCC *_hoops_CAPCC = font->_hoops_CAPCC;
	int i, width;


	/* _hoops_CGP _hoops_RGR _hoops_HRGR _hoops_PCCP _hoops_GARAI _hoops_HRCSR... */
	if (_hoops_CAPCC) {
		_hoops_IRPCC *_hoops_RAPCC = _hoops_CAPCC->_hoops_RAPCC;
		_hoops_RPPCC = _hoops_GPPCC (font->id, _hoops_PCPCC (_hoops_PGPCC));
		_hoops_PGPCC->_hoops_PIACC->AddLast (_hoops_RPPCC);
		_hoops_RCPCC (_hoops_PGPCC,
			   "%d 0 obj\n"
			   "<<\n"
			   "/Type /Font\n"
			   "/Subtype /%s\n"
			   "/BaseFont /%s\n"
			   "/FirstChar %d\n"
			   "/LastChar %d\n"
			   "/FontDescriptor %d 0 R\n"
			   "/Widths [ ", font->id,
			   font->_hoops_AAPCC,
			   font->_hoops_PAPCC, font->_hoops_HAPCC, font->_hoops_IAPCC, _hoops_CAPCC->id);
		for (i = 0; i < font->_hoops_IAPCC - font->_hoops_HAPCC + 1; ++i) {
			width = (int) (1000 / 255.0 * font->_hoops_HSISR[i]);
			_hoops_RCPCC (_hoops_PGPCC, "%d ", width);
		}
		_hoops_RCPCC (_hoops_PGPCC, "]\n" ">>\n" "endobj\n\n");

		_hoops_RPPCC = _hoops_GPPCC (_hoops_CAPCC->id, _hoops_PCPCC (_hoops_PGPCC));
		_hoops_PGPCC->_hoops_PIACC->AddLast (_hoops_RPPCC);
		_hoops_RCPCC (_hoops_PGPCC,
			   "%d 0 obj\n"
			   "<<\n"
			   "/Type /FontDescriptor\n"
			   "/FontName /%s\n"
			   "/Flags %d\n"
			   "/FontFile2 %d 0 R\n"
			   "/FontBBox [%d %d %d %d]\n"
			   ">>\n"
			   "endobj\n\n", _hoops_CAPCC->id,
			   _hoops_CAPCC->_hoops_GAPCC,
			   _hoops_CAPCC->Flags,
			   _hoops_RAPCC->id,
			   _hoops_CAPCC->xmin,
			   _hoops_CAPCC->ymin, _hoops_CAPCC->xmax, _hoops_CAPCC->ymax);

		/* _hoops_IISH _hoops_GGSR _hoops_RH _hoops_SSPCC _hoops_CARA. */
		_hoops_RPPCC = _hoops_GPPCC (_hoops_RAPCC->id, _hoops_PCPCC (_hoops_PGPCC));
		_hoops_PGPCC->_hoops_PIACC->AddLast (_hoops_RPPCC);
		_hoops_GRPCC (_hoops_PGPCC, _hoops_RAPCC->_hoops_CIPAH);
		_hoops_RCPCC (_hoops_PGPCC,
			   "%d 0 obj\n"
			   "<<\n"
			   "/Length %d\n"
			   "/Length1 %d\n"
			   "%s"
			   ">>\n"
			   "stream\n", _hoops_RAPCC->id,
			   _hoops_RAPCC->_hoops_CIPAH->_hoops_RGPCC,
			   _hoops_RAPCC->_hoops_CIPAH->_hoops_RGPCC,
			   (_hoops_PGPCC->_hoops_RCACC == PDF_ZLIB) ? "/Filter [/FlateDecode]" : "");
		_hoops_ICPCC (_hoops_PGPCC, _hoops_RAPCC->_hoops_CIPAH);
		_hoops_RCPCC (_hoops_PGPCC, "\nendstream\n" "endobj\n\n");

		FREE_ARRAY (_hoops_RAPCC->filename, _hoops_SSGR (_hoops_RAPCC->filename) + 1, char);
		_hoops_PRPCC (_hoops_RAPCC->_hoops_CIPAH);
		FREE (_hoops_RAPCC, _hoops_IRPCC);

		FREE_ARRAY (_hoops_CAPCC->_hoops_GAPCC, _hoops_SSGR (_hoops_CAPCC->_hoops_GAPCC) + 1,
			    char);
		FREE (_hoops_CAPCC, _hoops_SRPCC);
	}
	else {
		_hoops_RPPCC = _hoops_GPPCC (font->id, _hoops_PCPCC (_hoops_PGPCC));
		_hoops_PGPCC->_hoops_PIACC->AddLast (_hoops_RPPCC);
		_hoops_RCPCC (_hoops_PGPCC,
			   "%d 0 obj\n"
			   "<<\n"
			   "/Type /Font\n"
			   "/Subtype /%s\n"
			   "/BaseFont /%s\n"
			   ">>\n" "endobj\n\n", font->id, font->_hoops_AAPCC, font->_hoops_PAPCC);
	}
	return;
}

/* _hoops_APGRR _hoops_RGR _hoops_IS _hoops_GGI _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_RSACC _hoops_GGSR _hoops_IS _hoops_RH _hoops_RGHR.  _hoops_HGI _hoops_ISPCC _hoops_GGSR _hoops_RH _hoops_HSHIA _hoops_ASIRR
 * _hoops_SGP _hoops_GGHCC _hoops_IH _hoops_GRR _hoops_CARA _hoops_GAR _hoops_SCH _hoops_HRGR _hoops_PHPH.  _hoops_PGII _hoops_AAHAR _hoops_PPGS _hoops_CGH _hoops_SHH _hoops_HGGPR _hoops_ARI. */
local int
_hoops_RGHCC (_hoops_GHACC * _hoops_PGPCC)
{
	long _hoops_AGHCC;
	_hoops_RHACC *_hoops_RPPCC;
	_hoops_AHACC *_hoops_ASPCC;
	_hoops_PHACC *font;
	int i;


	/* _hoops_GGI _hoops_GGSR _hoops_RH _hoops_PGHCC (_hoops_ICGI _hoops_IRS _hoops_CGRPR _hoops_IS _hoops_RH _hoops_SSHSI _hoops_CARA) */
	_hoops_RPPCC = _hoops_GPPCC (_hoops_PGPCC->_hoops_SIACC, _hoops_PCPCC (_hoops_PGPCC));
	_hoops_PGPCC->_hoops_PIACC->AddLast (_hoops_RPPCC);
	_hoops_RCPCC (_hoops_PGPCC,
		   "%d 0 obj\n"
		   "<< "
		   "/Type /Catalog "
		   "/Pages %d 0 R " ">>\n" "endobj\n\n", _hoops_PGPCC->_hoops_SIACC, _hoops_PGPCC->_hoops_GCACC);

	/* _hoops_GGI _hoops_GGSR _hoops_RH _hoops_SSHSI _hoops_CARA (_hoops_ICGI _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_HCR _hoops_HSHIA _hoops_AGSAR) */
	_hoops_RPPCC = _hoops_GPPCC (_hoops_PGPCC->_hoops_GCACC, _hoops_PCPCC (_hoops_PGPCC));
	_hoops_PGPCC->_hoops_PIACC->AddLast (_hoops_RPPCC);
	_hoops_RCPCC (_hoops_PGPCC,
		   "%d 0 obj\n"
		   "<< " "/Type /Pages " "/Count %d " "/Kids [ ", _hoops_PGPCC->_hoops_GCACC, _hoops_PGPCC->_hoops_CIACC);

	_hoops_PGPCC->_hoops_HIACC->ResetCursor ();
	while ((_hoops_ASPCC = _hoops_PGPCC->_hoops_HIACC->PeekCursor ()) != null) {
		_hoops_RCPCC (_hoops_PGPCC, "%d 0 R ", _hoops_ASPCC->id);
		_hoops_PGPCC->_hoops_HIACC->AdvanceCursor ();
	}

	_hoops_RCPCC (_hoops_PGPCC, "] " ">>\n" "endobj\n\n");


	/* _hoops_CASI _hoops_GH _hoops_RH _hoops_HSHIA _hoops_AGSAR */
	_hoops_PGPCC->_hoops_HIACC->ResetCursor ();
	while ((_hoops_ASPCC = _hoops_PGPCC->_hoops_HIACC->PeekCursor ()) != null) {
		FREE (_hoops_ASPCC, _hoops_AHACC);
		_hoops_PGPCC->_hoops_HIACC->AdvanceCursor ();
	}
	delete _hoops_PGPCC->_hoops_HIACC;

	/* _hoops_CASI _hoops_GH _hoops_RH _hoops_HRCSR _hoops_AGSAR */
	_hoops_PGPCC->font_list->ResetCursor ();
	while ((font = _hoops_PGPCC->font_list->PeekCursor ()) != null) {
		FREE_ARRAY (font->_hoops_PAPCC, _hoops_SSGR (font->_hoops_PAPCC) + 1, char);
		FREE (font, _hoops_PHACC);
		_hoops_PGPCC->font_list->AdvanceCursor ();
	}
	delete _hoops_PGPCC->font_list;

	/* _hoops_GGI _hoops_RH _hoops_HSIGP (_hoops_SHHP _hoops_CGRPR) _hoops_ICSHR.  _hoops_HGI _hoops_ICSHR _hoops_HIGR _hoops_AII _hoops_IH _hoops_HCR _hoops_RH _hoops_AGSAR. */
	_hoops_AGHCC = _hoops_PCPCC (_hoops_PGPCC);
	_hoops_RCPCC (_hoops_PGPCC, "xref\n" "0 %d\n", _hoops_PGPCC->_hoops_IIACC);
	{
		_hoops_RHACC **_hoops_HGHCC;
		float *priorities;
		int _hoops_IGHCC, id;

		_hoops_IGHCC = (int) _hoops_PGPCC->_hoops_PIACC->Count ();
		ALLOC_ARRAY (_hoops_HGHCC, _hoops_IGHCC, _hoops_RHACC *);
		ALLOC_ARRAY (priorities, _hoops_IGHCC, float);

		_hoops_PGPCC->_hoops_PIACC->ResetCursor ();
		for (i = 0; i < _hoops_IGHCC; ++i) {
			_hoops_HGHCC[i] = _hoops_PGPCC->_hoops_PIACC->PeekCursor ();
			priorities[i] = (float) _hoops_HGHCC[i]->id;
			_hoops_PGPCC->_hoops_PIACC->AdvanceCursor ();
		}

		HI_Sort_Array (_hoops_IGHCC, priorities, (void **) _hoops_HGHCC,
			       sizeof (_hoops_RHACC *), true);

		for (id = i = 0; i < _hoops_IGHCC; ++i, ++id) {
			while (_hoops_HGHCC[i]->id > id) {
				_hoops_RCPCC (_hoops_PGPCC, "0000000000 65535 f \n");
				++id;
			}
			_hoops_RCPCC (_hoops_PGPCC, "%010ld 00000 n \n", _hoops_HGHCC[i]->offset);
		}

		FREE_ARRAY (priorities, _hoops_IGHCC, float);
		FREE_ARRAY (_hoops_HGHCC, _hoops_IGHCC, _hoops_RHACC *);
	}
	_hoops_RCPCC (_hoops_PGPCC, "\n\n");

	while ((_hoops_RPPCC = _hoops_PGPCC->_hoops_PIACC->RemoveFirst ()) != null)
		FREE (_hoops_RPPCC, _hoops_RHACC);

	delete _hoops_PGPCC->_hoops_PIACC;

	/* _hoops_RH _hoops_CGHCC _hoops_HRGR _hoops_SHR _hoops_RH _hoops_CGHI _hoops_IGCI _hoops_GGR _hoops_IRS _hoops_RSACC _hoops_RGHR.  _hoops_HHIGR _hoops_SSCP _hoops_RH _hoops_SHI _hoops_IIGR _hoops_RH _hoops_HSIGP _hoops_PPR _hoops_CRSRR _hoops_IIGR _hoops_RH _hoops_PGHCC */
	_hoops_RCPCC (_hoops_PGPCC,
		   "trailer\n"
		   "<< "
		   "/Size %d "
		   "/Root %d 0 R " "/Info 1 0 R " ">>\n", _hoops_PGPCC->_hoops_IIACC, _hoops_PGPCC->_hoops_SIACC);
	_hoops_RCPCC (_hoops_PGPCC, "startxref\n" "%ld\n" "%%%%EOF", _hoops_AGHCC);
	_hoops_HCPCC (_hoops_PGPCC);

	FREE (_hoops_PGPCC, _hoops_GHACC);

	return (0);
}

local void
_hoops_SGHCC (_hoops_GHACC * _hoops_PGPCC,
			       _hoops_ISACC * _hoops_CIPAH,
			       int const length, void const *const _hoops_GRHCC)
{
	_hoops_SPACC *_hoops_CGPCC;

	if (length == 0)
		return;

	_hoops_HGPCC(_hoops_CIPAH, length);
	_hoops_CGPCC = _hoops_CIPAH->_hoops_SSACC;

	if (_hoops_PGPCC->_hoops_RCACC == PDF_ZLIB) {

		int _hoops_RRPCC = 0;

		/* _hoops_CGP _hoops_IIH'_hoops_GRI _hoops_PSP _hoops_RRI _hoops_IIPR _hoops_SRHR _hoops_IS _hoops_PPSI _hoops_SGRH _hoops_PIH... */
		if (_hoops_CIPAH->zstream.avail_out == 0) {
			_hoops_CIPAH->zstream.next_out = _hoops_CGPCC->buffer + _hoops_CGPCC->_hoops_SCACC;
			_hoops_CIPAH->zstream.avail_out = _hoops_CGPCC->_hoops_RSIGR - _hoops_CGPCC->_hoops_SCACC;
		}

		/* _hoops_CGP _hoops_IIH'_hoops_GRI _hoops_PSP _hoops_RRI _hoops_CIIA _hoops_SRHR _hoops_PIH _hoops_IS _hoops_SAGR... */
		if (_hoops_CIPAH->zstream.avail_in == 0) {
			_hoops_CIPAH->zstream.next_in = (Bytef *) _hoops_GRHCC;
			_hoops_CIPAH->zstream.avail_in = length;
			_hoops_CIPAH->_hoops_GGPCC += length;
		}

		/* _hoops_IAAH _hoops_RH _hoops_SRHR */
		if (deflate (&_hoops_CIPAH->zstream, Z_NO_FLUSH) != Z_OK) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					   "Data Compression Failure. Set bit 1 in debug bits to disable compression");
		}

		_hoops_RRPCC = _hoops_CGPCC->_hoops_RSIGR - _hoops_CGPCC->_hoops_SCACC - _hoops_CIPAH->zstream.avail_out;
		_hoops_CGPCC->_hoops_SCACC += _hoops_RRPCC;
		_hoops_CIPAH->_hoops_RGPCC += _hoops_RRPCC;
		if (_hoops_CIPAH->zstream.avail_in > 0) {
			_hoops_SGHCC (_hoops_PGPCC, _hoops_CIPAH,
						       _hoops_CIPAH->zstream.avail_in,
						       (unsigned char *) _hoops_GRHCC + length -
						       _hoops_CIPAH->zstream.avail_in);
		}

	}
	else {

		/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_CPIC _hoops_IS _hoops_PGSAH _hoops_RH _hoops_SRHR... */
		if (_hoops_CGPCC->_hoops_SCACC + length < _hoops_CGPCC->_hoops_RSIGR) {
			/* _hoops_IGPP _hoops_HCR _hoops_RH _hoops_CCAH _hoops_ASIRR _hoops_APHR _hoops_HPGR _hoops_RH _hoops_SRS _hoops_RRHCC _hoops_HIH _hoops_GGR _hoops_RH _hoops_SRHR. */
			COPY_MEMORY (_hoops_GRHCC, length, _hoops_CGPCC->buffer + _hoops_CGPCC->_hoops_SCACC);
			_hoops_CGPCC->_hoops_SCACC += length;
			_hoops_CIPAH->_hoops_GGPCC += length;
			_hoops_CIPAH->_hoops_RGPCC = _hoops_CIPAH->_hoops_GGPCC;
		}
		else {
			/* _hoops_PGPR _hoops_IPS _hoops_RAPR _hoops_IS _hoops_CISA _hoops_RH _hoops_SCGR _hoops_ASIRR _hoops_SRHR _hoops_PPR _hoops_GHHA. */
			int _hoops_ARHCC = _hoops_CGPCC->_hoops_RSIGR - _hoops_CGPCC->_hoops_SCACC;

			COPY_MEMORY (_hoops_GRHCC, _hoops_ARHCC,
				     _hoops_CGPCC->buffer + _hoops_CGPCC->_hoops_SCACC);
			_hoops_CGPCC->_hoops_SCACC += _hoops_ARHCC;
			_hoops_CIPAH->_hoops_GGPCC += _hoops_ARHCC;
			_hoops_CIPAH->_hoops_RGPCC = _hoops_CIPAH->_hoops_GGPCC;
			_hoops_SGHCC (_hoops_PGPCC, _hoops_CIPAH,
						       length - _hoops_ARHCC,
						       (unsigned char *) _hoops_GRHCC + _hoops_ARHCC);
		}
	}

	return;
}

/* _hoops_APGRR _hoops_RGR _hoops_IS _hoops_CIGAA _hoops_PIH _hoops_IS _hoops_RH _hoops_SCGR _hoops_HSHIA'_hoops_GRI _hoops_ASIRR _hoops_AIGHH.  _hoops_IPCP _hoops_ASIRR _hoops_AIGHH
 * _hoops_HRGR _hoops_SAHR _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_CAGA-_hoops_PII _hoops_RGCAI _hoops_SGS _hoops_PGSA _hoops_HCGR, _hoops_AAGA _hoops_HCISR _hoops_PPR _hoops_RISA _hoops_RRRH.
 * _hoops_PRHCC _hoops_HRGR _hoops_HRHCC _hoops_PSHPR _hoops_PIH _hoops_IS _hoops_RH _hoops_AIGHH.  */
local void
_hoops_IRHCC (_hoops_GHACC * _hoops_PGPCC, int const length, void const *const _hoops_GRHCC)
{
	_hoops_SGHCC (_hoops_PGPCC, _hoops_PGPCC->_hoops_AIACC->_hoops_CIPAH, length, _hoops_GRHCC);
	return;
}

/* _hoops_APGRR _hoops_RGR _hoops_IS _hoops_CIGAA _hoops_PIH _hoops_IS _hoops_RH _hoops_SCGR _hoops_HSHIA'_hoops_GRI _hoops_ASIRR _hoops_AIGHH.  _hoops_IPCP _hoops_ASIRR _hoops_AIGHH
 * _hoops_HRGR _hoops_SAHR _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_CAGA-_hoops_PII _hoops_RGCAI _hoops_SGS _hoops_PGSA _hoops_HCGR, _hoops_AAGA _hoops_HCISR _hoops_PPR _hoops_RISA _hoops_RRRH. */
local void
_hoops_CRHCC (_hoops_GHACC * _hoops_PGPCC, char const *const _hoops_SRHCC, ...)
{
	char *_hoops_GAHCC;
	int _hoops_RAHCC, _hoops_GCPCC;
	va_list _hoops_CAARA;


	if (_hoops_SSGR (_hoops_SRHCC) == 0)
		return;

	_hoops_RAHCC = (int) _hoops_SSGR (_hoops_SRHCC) + 128;

	ALLOC_ARRAY (_hoops_GAHCC, _hoops_RAHCC, char);
	va_start (_hoops_CAARA, _hoops_SRHCC);
	_hoops_GCPCC = _hoops_SIPCC (_hoops_GAHCC, _hoops_RAHCC, _hoops_SRHCC, _hoops_CAARA);
	va_end (_hoops_CAARA);
	while (_hoops_GCPCC < 0 || _hoops_GCPCC > _hoops_RAHCC) {
		FREE_ARRAY (_hoops_GAHCC, _hoops_RAHCC, char);
		_hoops_RAHCC *= 2;
		ALLOC_ARRAY (_hoops_GAHCC, _hoops_RAHCC, char);
		va_start (_hoops_CAARA, _hoops_SRHCC);
		_hoops_GCPCC = _hoops_SIPCC (_hoops_GAHCC, _hoops_RAHCC, _hoops_SRHCC, _hoops_CAARA);
		va_end (_hoops_CAARA);
	}

	if (_hoops_GAHCC[_hoops_GCPCC - 1] == '\n')
		--_hoops_GCPCC;
	else
		_hoops_GAHCC[_hoops_GCPCC] = ' ';

	_hoops_SGHCC (_hoops_PGPCC, _hoops_PGPCC->_hoops_AIACC->_hoops_CIPAH,
				       _hoops_GCPCC + 1, (unsigned char const *) _hoops_GAHCC);
	FREE_ARRAY (_hoops_GAHCC, _hoops_RAHCC, char);
	return;
}

local void
_hoops_AAHCC (_hoops_GHACC * _hoops_PGPCC,
			float left, float right,
			float bottom, float top,
			int _hoops_PAHCC, int _hoops_HAHCC, int _hoops_PRGRA, unsigned char const *data)
{
	_hoops_CRHCC (_hoops_PGPCC, "q %g 0 0 %g %g %g cm", right - left, top - bottom, left,
			       bottom);
	_hoops_CRHCC (_hoops_PGPCC, "BI /W %d /H %d /CS /RGB /BPC 8 ID", _hoops_PAHCC, _hoops_HAHCC);
	switch (_hoops_PRGRA) {
	case 3:
		_hoops_IRHCC (_hoops_PGPCC, 3 * _hoops_PAHCC * _hoops_HAHCC, data);
		break;
	default:
		{
			int row, col;
			for (row = 0; row < _hoops_HAHCC; ++row) {
				for (col = 0; col < _hoops_PAHCC; ++col) {
					_hoops_IRHCC (_hoops_PGPCC, 3,
								      &data[_hoops_PRGRA *
									    (col +
									     _hoops_PAHCC * row)]);
				}
			}
		}
	}
	_hoops_CRHCC (_hoops_PGPCC, "EI Q\n");
	return;
}

local void
_hoops_IAHCC (_hoops_GHACC * _hoops_PGPCC,
			 float left, float right,
			 float bottom, float top,
			 int _hoops_PAHCC, int _hoops_HAHCC,
			 int _hoops_PRGRA, unsigned char const *data)
{
	_hoops_HHACC *image;


	/* _hoops_HGI _hoops_CGH _hoops_SHH _hoops_HGGPR _hoops_CGPR _hoops_SCH _hoops_HRGR _hoops_PHPH. */
	ALLOC (image, _hoops_HHACC);
	image->_hoops_CIPAH = _hoops_AGPCC (_hoops_PGPCC, 0);

	image->id = _hoops_GIPCC (_hoops_PGPCC);
	image->width = _hoops_PAHCC;
	image->height = _hoops_HAHCC;
	image->_hoops_RCHA = 8;

	switch (_hoops_PRGRA) {
	case 3:
		_hoops_SGHCC (_hoops_PGPCC, image->_hoops_CIPAH, 3 * _hoops_PAHCC * _hoops_HAHCC,
					       data);
		break;
	default:
		{
			int row, col;
			for (row = 0; row < _hoops_HAHCC; ++row) {
				for (col = 0; col < _hoops_PAHCC; ++col) {
					_hoops_SGHCC (_hoops_PGPCC, image->_hoops_CIPAH, 3,
								       &data[_hoops_PRGRA *
									     (col +
									      _hoops_PAHCC * row)]);
				}
			}
		}
	}

	/* _hoops_CAHCC _hoops_PHHR _hoops_IAISR _hoops_PPR _hoops_GGI _hoops_RGR _hoops_GGSR _hoops_IS _hoops_RH _hoops_GSPCC. */
	_hoops_CCPCC (_hoops_PGPCC, image);

	/* _hoops_PS _hoops_HGGC _hoops_RRP _hoops_IS _hoops_GGCR _hoops_RGR _hoops_IS _hoops_RH _hoops_HSHIA _hoops_HIS _hoops_SR'_hoops_GCPP _hoops_ACPA _hoops_SCH'_hoops_GRI _hoops_CRSRR _hoops_PPR _hoops_CIPH _hoops_CGPR _hoops_SR
	 * _hoops_GCSH _hoops_GGI _hoops_GGSR _hoops_RH _hoops_HSHIA _hoops_CARA. */
	_hoops_PGPCC->_hoops_AIACC->_hoops_HRPCC->AddLast (image);

	_hoops_CRHCC (_hoops_PGPCC,
			       "q %g 0 0 %g %g %g cm /I%x Do Q\n",
			       right - left, top - bottom, left, bottom, image->id);
	return;
}

/********  _hoops_CHCPI  **********/
local _hoops_GHACC *_hoops_SAHCC (char *filename);
local int _hoops_RGHCC (_hoops_GHACC * _hoops_PGPCC);
local void _hoops_GPHCC (_hoops_GHACC * _hoops_PGPCC, float width, float height, float dpi);
local void _hoops_RPHCC (_hoops_GHACC * _hoops_PGPCC);
local void _hoops_APHCC (_hoops_GHACC * _hoops_PGPCC);
local void _hoops_PPHCC (_hoops_GHACC * _hoops_PGPCC);
local void _hoops_HPHCC (_hoops_GHACC * _hoops_PGPCC, float x, float y);
local void _hoops_IPHCC (_hoops_GHACC * _hoops_PGPCC, float red, float green, float blue);
local void _hoops_CPHCC (_hoops_GHACC * _hoops_PGPCC, float red, float green, float blue);
local void _hoops_SPHCC (_hoops_GHACC * _hoops_PGPCC, int _hoops_SAGAI);
local void _hoops_GHHCC (_hoops_GHACC * _hoops_PGPCC, int cap);
local void _hoops_RHHCC (_hoops_GHACC * _hoops_PGPCC, int count, int const *pattern, float scale);
local void _hoops_AHHCC (_hoops_GHACC * _hoops_PGPCC, float weight);
local int _hoops_PHHCC (_hoops_GHACC * _hoops_PGPCC, char const *_hoops_SSISR);
local int _hoops_HHHCC (_hoops_GHACC * _hoops_PGPCC, char const *_hoops_SSISR, char const *filename,
			  int xmin, int xmax, int ymin, int ymax, unsigned char const *_hoops_HSISR);
local int _hoops_IHHCC (_hoops_GHACC * _hoops_PGPCC, float size, char const *_hoops_SSISR);
local void _hoops_CHHCC (_hoops_GHACC * _hoops_PGPCC, int const mode);
local void _hoops_SHHCC (_hoops_GHACC * _hoops_PGPCC, int _hoops_RCACC);
local void _hoops_GIHCC (_hoops_GHACC * _hoops_PGPCC, int mask, int count, int _hoops_IGHCP,
				     float const *points);
local void _hoops_RIHCC (_hoops_GHACC * _hoops_PGPCC, float x, float y, float rotation,
			    float width_scale, int count, unsigned short const *text);
local void _hoops_AIHCC (_hoops_GHACC * _hoops_PGPCC, float left, float right, float bottom, float top,
			     int width, int height, int _hoops_PRGRA, unsigned char const *data);
local void _hoops_PIHCC (_hoops_GHACC * _hoops_PGPCC, int point_count, int _hoops_IGHCP, float const *points,
			      bool _hoops_HIHCC);
local void _hoops_IIHCC (_hoops_GHACC * _hoops_PGPCC, int point_count, int _hoops_IGHCP,
			       float const *points);
local void _hoops_CIHCC (_hoops_GHACC * _hoops_PGPCC, int point_count, int _hoops_IGHCP,
				float const *points);
local void _hoops_SIHCC (_hoops_GHACC * _hoops_PGPCC, int point_count, int _hoops_IGHCP,
			       float const *points);
/*****************************************/

local void
_hoops_RPHCC (_hoops_GHACC * _hoops_PGPCC)
{
	if (_hoops_PGPCC->_hoops_AIACC) {
		_hoops_PPHCC (_hoops_PGPCC);
		_hoops_RSPCC (_hoops_PGPCC, _hoops_PGPCC->_hoops_AIACC);
		_hoops_PGPCC->_hoops_AIACC = 0;
	}
	return;
}


local void
_hoops_APHCC (_hoops_GHACC * _hoops_PGPCC)
{
	_hoops_CRHCC (_hoops_PGPCC, "q\n");
	return;
}

local void
_hoops_PPHCC (_hoops_GHACC * _hoops_PGPCC)
{
	_hoops_CRHCC (_hoops_PGPCC, "Q\n");
	return;
}

local void
_hoops_HPHCC (_hoops_GHACC * _hoops_PGPCC, float x, float y)
{
	_hoops_CRHCC (_hoops_PGPCC, "%g 0 0 %g 0 0 cm\n", x, y);
	return;
}

local void
_hoops_IPHCC (_hoops_GHACC * _hoops_PGPCC, float red, float green, float blue)
{
	_hoops_CRHCC (_hoops_PGPCC, "%g %g %g rg\n", red, green, blue);
	return;
}

local void
_hoops_CPHCC (_hoops_GHACC * _hoops_PGPCC, float red, float green, float blue)
{
	_hoops_CRHCC (_hoops_PGPCC, "%g %g %g RG\n", red, green, blue);
	return;
}

local void
_hoops_SPHCC (_hoops_GHACC * _hoops_PGPCC, int _hoops_SAGAI)
{
	_hoops_CRHCC (_hoops_PGPCC, "%d j\n", _hoops_SAGAI);
	return;
}

local void
_hoops_GHHCC (_hoops_GHACC * _hoops_PGPCC, int cap)
{
	_hoops_CRHCC (_hoops_PGPCC, "%d J\n", cap);
	return;
}

local void
_hoops_RHHCC (_hoops_GHACC * _hoops_PGPCC, int count, int const *pattern, float scale)
{
	int i;
	_hoops_CRHCC (_hoops_PGPCC, "[");
	for (i = 0; i < count; ++i)
		_hoops_CRHCC (_hoops_PGPCC, "%g", scale * pattern[i]);
	_hoops_CRHCC (_hoops_PGPCC, "] 0 d\n");
	return;
}

local void
_hoops_SHHCC (_hoops_GHACC * _hoops_PGPCC, int _hoops_RCACC)
{
	_hoops_PGPCC->_hoops_RCACC = _hoops_RCACC;
	return;
}

local void
_hoops_AHHCC (_hoops_GHACC * _hoops_PGPCC, float weight)
{
	/* _hoops_HAACC _hoops_CPPC _hoops_IRS _hoops_SGCR _hoops_SPR _hoops_III _hoops_GAR _hoops_SPR _hoops_GRAA-_hoops_SAAA _hoops_ASPA.  _hoops_PGII
	   _hoops_RII _hoops_APGR _hoops_CHR _hoops_GCHCC. */
	_hoops_CRHCC (_hoops_PGPCC, "%g w\n", weight);
	return;
}

local void
_hoops_GPHCC (_hoops_GHACC * _hoops_PGPCC, float width, float height, float dpi)
{
	_hoops_AHACC alter *_hoops_ASPCC;


	if (_hoops_PGPCC->_hoops_AIACC)
		_hoops_RPHCC (_hoops_PGPCC);

	ALLOC (_hoops_ASPCC, _hoops_AHACC);

	_hoops_ASPCC->id = _hoops_GIPCC (_hoops_PGPCC);
	++_hoops_PGPCC->_hoops_CIACC;
	_hoops_ASPCC->_hoops_CIPAH = _hoops_AGPCC (_hoops_PGPCC, _hoops_GIPCC (_hoops_PGPCC));

	_hoops_ASPCC->_hoops_HRPCC = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_RIACC)(HOOPS_WORLD->memory_pool);
	_hoops_ASPCC->font_list = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_GIACC)(HOOPS_WORLD->memory_pool);

	_hoops_PGPCC->_hoops_AIACC = _hoops_ASPCC;

	_hoops_ASPCC->width = (int) width;
	_hoops_ASPCC->height = (int) height;

	_hoops_SPHCC (_hoops_PGPCC, 1);
	_hoops_GHHCC (_hoops_PGPCC, 0);
	_hoops_AHHCC (_hoops_PGPCC, 0);
	_hoops_HPHCC (_hoops_PGPCC, 72 / dpi, 72 / dpi);
	_hoops_APHCC (_hoops_PGPCC);

	_hoops_PGPCC->_hoops_HIACC->AddLast (_hoops_ASPCC);
	return;
}

/* _hoops_HGI _hoops_API _hoops_RGIHH _hoops_RH _hoops_RGHR (_hoops_GGR _hoops_PSHPR _hoops_CCH) _hoops_IH _hoops_RH _hoops_RSACC.  _hoops_HHIGR _hoops_CIGCP _hoops_GGSR _hoops_HHH _hoops_RGSPR _hoops_SIHC _hoops_PPR _hoops_HHH _hoops_PPCAR
 * _hoops_RSACC _hoops_AGSAR.  _hoops_RAPAR _hoops_CARA _hoops_SGS _hoops_HRGR _hoops_PHPH _hoops_GGR _hoops_RH _hoops_RGHR _hoops_IRHS _hoops_IS _hoops_HS _hoops_PCCP _hoops_RCHCC (_hoops_SHHP _hoops_CGRPR _hoops_ICSHR).
 * _hoops_IPCP _hoops_SHHP _hoops_CGRPR _hoops_GASR _hoops_HRGR _hoops_IRS _hoops_GASR _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_RSACC _hoops_RGHR _hoops_IIAAR _hoops_RAPSR _hoops_AII _hoops_IS _hoops_HCR _hoops_RH _hoops_AGSAR
 * _hoops_GGR _hoops_RH _hoops_RSACC.  _hoops_HGI _hoops_RCRP _hoops_RSACC _hoops_ACHCC _hoops_HPHAI _hoops_RH _hoops_RRCPH _hoops_IS _hoops_PCHCC  _hoops_HCHCC _hoops_AGSAR _hoops_GGR _hoops_RH _hoops_RGHR. */

local _hoops_GHACC *
_hoops_SAHCC (char *filename)
{
	_hoops_RHACC alter *_hoops_RPPCC;
	_hoops_GHACC alter *_hoops_PGPCC;

	ALLOC (_hoops_PGPCC, _hoops_GHACC);
	ZERO_STRUCT (_hoops_PGPCC, _hoops_GHACC);

	_hoops_PGPCC->_hoops_PAGR = fopen (filename, "wb");
	if (!_hoops_PGPCC->_hoops_PAGR)
		return (0);

	_hoops_PGPCC->_hoops_SIACC = 2;	/* _hoops_RH _hoops_PGHCC _hoops_CARA _hoops_HRGR _hoops_CPIC _hoops_IS _hoops_SHH _hoops_RH _hoops_SPS _hoops_RAS _hoops_RH _hoops_RSPHR _hoops_ICHCC */
	_hoops_PGPCC->_hoops_GCACC = 3;	/* _hoops_SSHSI _hoops_CARA _hoops_HRGR _hoops_SPS _hoops_RAS _hoops_PGHCC */
	_hoops_PGPCC->_hoops_HIACC = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_SHACC)(HOOPS_WORLD->memory_pool);
	_hoops_PGPCC->_hoops_PIACC = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_CHACC)(HOOPS_WORLD->memory_pool);
	_hoops_PGPCC->font_list = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_GIACC)(HOOPS_WORLD->memory_pool);
	_hoops_PGPCC->error = false;

	/* _hoops_IPCP _hoops_SPS _hoops_CIAGR _hoops_AGSAR _hoops_CHR _hoops_PPCAR _hoops_IS _hoops_HCR _hoops_RSACC _hoops_RGHR (_hoops_IH _hoops_IHHH _hoops_APIC) _hoops_HIS _hoops_GGI _hoops_CAPR _hoops_GGSR _hoops_ARI */
	_hoops_RCPCC (_hoops_PGPCC, "%%PDF-1.4\n%%");
	{
		long _hoops_CCHCC = -1;
		_hoops_AIPCC (&_hoops_CCHCC, sizeof (long), 1, _hoops_PGPCC);
	}
	_hoops_RCPCC (_hoops_PGPCC, "\n\n");

	_hoops_RPPCC = _hoops_GPPCC (1, ftell (_hoops_PGPCC->_hoops_PAGR));
	_hoops_PGPCC->_hoops_PIACC->AddLast (_hoops_RPPCC);
	_hoops_RCPCC (_hoops_PGPCC, "1 0 obj\n" "<< " "/Producer (HOOPS 3D PDF) " ">>\n" "endobj\n\n");

	_hoops_PGPCC->_hoops_IIACC = 4;

	return (_hoops_PGPCC);

}

local void
_hoops_CIHCC (_hoops_GHACC * _hoops_PGPCC, int point_count, int _hoops_IGHCP, float const *points)
{

	/* _hoops_SPHAI - _hoops_IHIS _hoops_IS. */
	_hoops_CRHCC (_hoops_PGPCC, "%g %g m", points[0], points[1]);

	/* _hoops_CGP _hoops_RH _hoops_SCHCC _hoops_PPR _hoops_CGHI _hoops_PPSR _hoops_CHR _hoops_RH _hoops_PSHR... */
	if (points[0] == points[(point_count - 1) * _hoops_IGHCP]
	    && points[1] == points[(point_count - 1) * _hoops_IGHCP + 1]) {

		while (point_count-- > 1) {
			points += _hoops_IGHCP;
			/* _hoops_GSSAA - _hoops_III _hoops_IS */
			_hoops_CRHCC (_hoops_PGPCC, "%g %g l", points[0], points[1]);
		}
		/* _hoops_GSHCC _hoops_RH _hoops_SCHCC _hoops_PPR _hoops_CGHI _hoops_PPSR _hoops_PPR _hoops_RGISR _hoops_RH _hoops_III. */
		_hoops_CRHCC (_hoops_PGPCC, "s\n");

	}
	else {

		while (point_count-- > 1) {
			points += _hoops_IGHCP;
			/* _hoops_GSSAA - _hoops_III _hoops_IS */
			_hoops_CRHCC (_hoops_PGPCC, "%g %g l", points[0], points[1]);
		}
		/* _hoops_IPACC _hoops_RH _hoops_III. */
		_hoops_CRHCC (_hoops_PGPCC, "S\n");
	}
	return;
}

local void
_hoops_SIHCC (_hoops_GHACC * _hoops_PGPCC, int point_count, int _hoops_IGHCP, float const *points)
{
	while (point_count-- > 1) {
		points += _hoops_IGHCP;
		/* _hoops_SPHAI - _hoops_III _hoops_IS, _hoops_IISGA - _hoops_RGISR _hoops_RH _hoops_III (_hoops_PAR _hoops_PSCHR) */
		_hoops_CRHCC (_hoops_PGPCC, "%g %g 1 1 re f", points[0], points[1]);
	}
	_hoops_CRHCC (_hoops_PGPCC, "\n");
}

local void
_hoops_IIHCC (_hoops_GHACC * _hoops_PGPCC, int point_count, int _hoops_IGHCP, float const *points)
{
	int i;


	_hoops_CRHCC (_hoops_PGPCC, "%g %g m", points[0], points[1]);
	for (i = 1; i < point_count; ++i) {
		points += _hoops_IGHCP;
		_hoops_CRHCC (_hoops_PGPCC, "%g %g l", points[0], points[1]);
	}
	_hoops_CRHCC (_hoops_PGPCC, "f\n");
	return;
}

local void
_hoops_PIHCC (_hoops_GHACC * _hoops_PGPCC, int point_count, int _hoops_IGHCP, float const *points, bool _hoops_HIHCC)
{
	int i;


	_hoops_CRHCC (_hoops_PGPCC, "%g %g m", (points[0]), (points[1]));
	for (i = 1; i < point_count; i += 3) {
		_hoops_CRHCC (_hoops_PGPCC, "%g %g %g %g %g %g c",
				       (points[_hoops_IGHCP * (i + 0) + 0]), (points[_hoops_IGHCP * (i + 0) + 1]),
				       (points[_hoops_IGHCP * (i + 1) + 0]), (points[_hoops_IGHCP * (i + 1) + 1]),
				       (points[_hoops_IGHCP * (i + 2) + 0]), (points[_hoops_IGHCP * (i + 2) + 1]));
	}

	/* _hoops_ISPR _hoops_IH _hoops_CAHC _hoops_CRAA */
	if (points[0] == points[_hoops_IGHCP * (point_count - 1) + 0] &&
	    points[1] == points[_hoops_IGHCP * (point_count - 1) + 1] && _hoops_HIHCC)
		_hoops_CRHCC (_hoops_PGPCC, "f\n");
	_hoops_CRHCC (_hoops_PGPCC, "S\n");
	return;
}

local void
_hoops_AIHCC (_hoops_GHACC * _hoops_PGPCC,
		  float left, float right,
		  float bottom, float top,
		  int width, int height, int _hoops_PRGRA, unsigned char const *data)
{
	/*      _hoops_HAACC _hoops_RSHCC _hoops_CPPHR _hoops_RRRH _hoops_APPR _hoops_HSAR 1_hoops_ARGI _hoops_CGH _hoops_SHH
	 *      _hoops_HSPCC (_hoops_HAR _hoops_SGS _hoops_SSIA _hoops_HS _hoops_IS _hoops_SHH...).
	 */
	if (width * height * 3 <= _hoops_PAACC) {
		_hoops_AAHCC (_hoops_PGPCC, left, right, bottom, top, width, height, _hoops_PRGRA,
					data);
	}
	else {
		_hoops_IAHCC (_hoops_PGPCC, left, right, bottom, top, width, height, _hoops_PRGRA,
					 data);
	}
	return;
}

local int
_hoops_ASHCC (char const *const _hoops_SSISR)
{
	int retval;

	if (!strcmp (_hoops_SSISR, "Times-Roman")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Times-Italic")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Times-Bold")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Times-BoldItalic")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Helvetica")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Helvetica-Oblique")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Helvetica-Bold")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Helvetica-BoldOblique")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Courier")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Courier-Oblique")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Courier-Bold")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Courier-BoldOblique")) {
		retval = 1;
	}
	else if (!strcmp (_hoops_SSISR, "Symbol")) {
		retval = 1;
	}
	else {
		retval = 0;
	}

	return (retval);
}

local int
_hoops_PHHCC (_hoops_GHACC * _hoops_PGPCC, char const *_hoops_SSISR)
{
	_hoops_GIACC *font_list = 0;
	_hoops_PHACC *font = 0;
	int _hoops_PSHCC = 1;
	int _hoops_HSHCC = 1;

	if (_hoops_PGPCC && _hoops_PGPCC->_hoops_AIACC) {
		font_list = _hoops_PGPCC->_hoops_AIACC->font_list;

		/* _hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_RGR _hoops_HRCSR _hoops_HRGR _hoops_GGR _hoops_RH _hoops_HSHIA _hoops_HRCSR
		 * _hoops_HIGR.  _hoops_CGP _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_PSCR _hoops_SR _hoops_RRP _hoops_IS _hoops_GGCR _hoops_SCH. */
		font_list->ResetCursor ();
		while ((font = font_list->PeekCursor ()) != null) {
			if (strcmp (font->_hoops_PAPCC, _hoops_SSISR) == 0) {
				/* _hoops_HRGSI _hoops_SSCP _hoops_AIAH _hoops_RPII _hoops_GARAI */
				_hoops_PSHCC = 0;
				break;
			}
			font_list->AdvanceCursor ();
		}
	}

	if (_hoops_PGPCC && _hoops_PGPCC->font_list) {
		font_list = _hoops_PGPCC->font_list;

		/* _hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_RGR _hoops_HRCSR _hoops_HRGR _hoops_AIAH _hoops_GGR _hoops_RH
		 * _hoops_ISHCC _hoops_HRCSR _hoops_HIGR. */
		font_list->ResetCursor ();
		while ((font = font_list->PeekCursor ()) != null) {
			if (strcmp (font->_hoops_PAPCC, _hoops_SSISR) == 0) {
				/* _hoops_HRGSI _hoops_SSCP _hoops_AIAH _hoops_RPII _hoops_GARAI */
				_hoops_HSHCC = 0;
				break;
			}
			font_list->AdvanceCursor ();
		}
	}

	if (_hoops_PGPCC && _hoops_PGPCC->font_list && _hoops_HSHCC) {
		font_list = _hoops_PGPCC->font_list;

		/* _hoops_IIPP _hoops_PPR _hoops_HGSR _hoops_RH _hoops_HRCSR _hoops_HRPR. */
		ALLOC (font, _hoops_PHACC);
		font->id = _hoops_GIPCC (_hoops_PGPCC);
		ALLOC_ARRAY (font->_hoops_PAPCC, _hoops_SSGR (_hoops_SSISR) + 1, char);
		COPY_MEMORY (_hoops_SSISR, _hoops_SSGR (_hoops_SSISR) + 1, font->_hoops_PAPCC);
		font->_hoops_HAPCC = 0;
		font->_hoops_IAPCC = 255;
		font->_hoops_AAPCC = (char *) ("TrueType");
		font->_hoops_CAPCC = 0;

		font_list->AddFirst (font);
		_hoops_CSPCC (_hoops_PGPCC, font);
	}

	if (_hoops_PGPCC && _hoops_PGPCC->_hoops_AIACC && _hoops_PSHCC) {
		_hoops_PGPCC->_hoops_AIACC->font_list->AddFirst (font);
	}

	return (0);
}

local int
_hoops_HHHCC (_hoops_GHACC * _hoops_PGPCC,
		char const *_hoops_SSISR,
		char const *filename, int xmin, int xmax, int ymin, int ymax,
		unsigned char const *_hoops_HSISR)
{
	_hoops_GIACC *font_list = 0;
	_hoops_PHACC *font = 0;
	bool _hoops_PSHCC = true;
	bool _hoops_HSHCC = true;


	if (_hoops_PGPCC && _hoops_PGPCC->_hoops_AIACC) {
		font_list = _hoops_PGPCC->_hoops_AIACC->font_list;

		/* _hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_RGR _hoops_HRCSR _hoops_HRGR _hoops_GGR _hoops_RH _hoops_HSHIA _hoops_HRCSR
		 * _hoops_HIGR.  _hoops_CGP _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_PSCR _hoops_SR _hoops_RRP _hoops_IS _hoops_GGCR _hoops_SCH. */
		font_list->ResetCursor ();
		while ((font = font_list->PeekCursor ()) != null) {
			if (strcmp (font->_hoops_PAPCC, _hoops_SSISR) == 0) {
				/* _hoops_HRGSI _hoops_SSCP _hoops_AIAH _hoops_RPII _hoops_GARAI */
				_hoops_PSHCC = false;
				break;
			}
			font_list->AdvanceCursor ();
		}
	}

	if (_hoops_PGPCC && _hoops_PGPCC->font_list) {
		font_list = _hoops_PGPCC->font_list;

		/* _hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_RGR _hoops_HRCSR _hoops_HRGR _hoops_AIAH _hoops_GGR _hoops_RH
		 * _hoops_GSPCC'_hoops_GRI _hoops_HRCSR _hoops_HIGR. */
		font_list->ResetCursor ();
		while ((font = font_list->PeekCursor ()) != null) {
			if (strcmp (font->_hoops_PAPCC, _hoops_SSISR) == 0) {
				/* _hoops_HRGSI _hoops_SSCP _hoops_AIAH _hoops_RPII _hoops_GARAI */
				_hoops_HSHCC = false;
				break;
			}
			font_list->AdvanceCursor ();
		}
	}

	if (_hoops_PGPCC && _hoops_PGPCC->font_list && _hoops_HSHCC) {
		_hoops_SRPCC *_hoops_CAPCC = 0;

		/* _hoops_CGP _hoops_RGR _hoops_HRGR _hoops_ASAI _hoops_IRS _hoops_CSHCC _hoops_HRCSR, _hoops_SR _hoops_RRP _hoops_IS _hoops_GIACI _hoops_RH _hoops_HRCSR _hoops_RGHR. */
		if (!_hoops_ASHCC (_hoops_SSISR)) {
			FILE *_hoops_SSHCC = 0;
			_hoops_ISACC *_hoops_CIPAH = 0;
			char *buffer = 0;
			_hoops_IRPCC *_hoops_RAPCC = 0;
			_hoops_CIPAH = _hoops_AGPCC (_hoops_PGPCC, 0);

			ALLOC_ARRAY (buffer, 16000, char);
			_hoops_SSHCC = fopen (filename, "rb");
			if (!_hoops_SSHCC) {
				return (-1);
			}
			while (!feof (_hoops_SSHCC)) {
				int count;
				count = (int) fread (buffer, 1, 16000, _hoops_SSHCC);
				if (count > 0)
					_hoops_SGHCC (_hoops_PGPCC, _hoops_CIPAH, count, buffer);
			}
			fclose (_hoops_SSHCC);
			FREE_ARRAY (buffer, 16000, char);

			ALLOC (_hoops_RAPCC, _hoops_IRPCC);
			_hoops_RAPCC->id = _hoops_GIPCC (_hoops_PGPCC);
			_hoops_RAPCC->_hoops_CRPCC = 0;
			_hoops_RAPCC->_hoops_CIPAH = _hoops_CIPAH;
			ALLOC_ARRAY (_hoops_RAPCC->filename, _hoops_SSGR (filename) + 1, char);
			COPY_MEMORY (filename, _hoops_SSGR (filename) + 1, _hoops_RAPCC->filename);

			ALLOC (_hoops_CAPCC, _hoops_SRPCC);
			_hoops_CAPCC->id = _hoops_GIPCC (_hoops_PGPCC);
			_hoops_CAPCC->_hoops_RAPCC = _hoops_RAPCC;
			_hoops_CAPCC->Flags = (1 << 2) | (1 << 6);
			_hoops_CAPCC->xmin = xmin;
			_hoops_CAPCC->ymin = ymin;
			_hoops_CAPCC->xmax = xmax;
			_hoops_CAPCC->ymax = ymax;
			ALLOC_ARRAY (_hoops_CAPCC->_hoops_GAPCC, _hoops_SSGR (_hoops_SSISR) + 1,
				     char);
			COPY_MEMORY (_hoops_SSISR, _hoops_SSGR (_hoops_SSISR) + 1,
				     _hoops_CAPCC->_hoops_GAPCC);
		}

		/* _hoops_IIPP _hoops_PPR _hoops_HGSR _hoops_RH _hoops_HRCSR _hoops_HRPR. */
		ALLOC (font, _hoops_PHACC);
		font->id = _hoops_GIPCC (_hoops_PGPCC);
		ALLOC_ARRAY (font->_hoops_PAPCC, _hoops_SSGR (_hoops_SSISR) + 1, char);
		COPY_MEMORY (_hoops_SSISR, _hoops_SSGR (_hoops_SSISR) + 1, font->_hoops_PAPCC);
		font->_hoops_HAPCC = 32;
		font->_hoops_IAPCC = 255;
		font->_hoops_HSISR = _hoops_HSISR;
		font->_hoops_AAPCC = (char *) ("TrueType");
		font->_hoops_CAPCC = _hoops_CAPCC;

		font_list->AddFirst (font);
		_hoops_CSPCC (_hoops_PGPCC, font);
	}

	if (_hoops_PGPCC && _hoops_PGPCC->_hoops_AIACC && _hoops_PSHCC) {
		_hoops_PGPCC->_hoops_AIACC->font_list->AddFirst (font);
	}

	return (0);
}

enum
{
	_hoops_GGICC = 0,
	_hoops_RGICC = 1,
	_hoops_AGICC = 2,
	_hoops_PGICC = 3,
	_hoops_HGICC = 4,
	_hoops_IGICC = 5,
	_hoops_CGICC = 6,
	_hoops_SGICC = 7
};

local void
_hoops_CHHCC (_hoops_GHACC * _hoops_PGPCC, int const mode)
{
	_hoops_CRHCC (_hoops_PGPCC, "%d Tr\n", mode);
}

local int
_hoops_IHHCC (_hoops_GHACC * _hoops_PGPCC, float size, char const *_hoops_SSISR)
{
	_hoops_GIACC *font_list = _hoops_PGPCC->font_list;
	_hoops_PHACC *font;

	/* _hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_RGR _hoops_HRCSR _hoops_HRGR _hoops_GGR _hoops_RH
	 * _hoops_ISHCC _hoops_HRCSR _hoops_HIGR. */
	font_list->ResetCursor ();
	while ((font = font_list->PeekCursor ()) != null) {
		if (strcmp (font->_hoops_PAPCC, _hoops_SSISR) == 0) {
			/* _hoops_IPCP _hoops_HRCSR _hoops_HRGR _hoops_GSGI, _hoops_ARP _hoops_RGR _hoops_HRCSR. */
			_hoops_CRHCC (_hoops_PGPCC, "/F%x %g Tf\n", font->id, size);
			return (0);
		}
		font_list->AdvanceCursor ();
	}

	return (-1);
}

local void
_hoops_RIHCC (_hoops_GHACC * _hoops_PGPCC,
		 float x, float y,
		 float rotation, float width_scale, int count, unsigned short const *text)
{
	if (count <= 0)
		return;

	_hoops_CRHCC (_hoops_PGPCC, "BT");

	if (rotation != 0.0f) {
		_hoops_CRHCC (_hoops_PGPCC,
				       "%.4f %.4f %.4f %.4f %.4f %.4f Tm",
				       cos (rotation * HK_Pi / 180.0),
				       sin (rotation * HK_Pi / 180.0),
				       -sin (rotation * HK_Pi / 180.0),
				       cos (rotation * HK_Pi / 180.0), x, y);
	}
	else {
		_hoops_CRHCC (_hoops_PGPCC, "%g %g Td", x, y);
	}

	if (width_scale) {
		_hoops_CRHCC (_hoops_PGPCC, "%g Tz", width_scale * 100);
	}

	do {
		_hoops_CRHCC (_hoops_PGPCC, "<%2x> Tj", (char) *text++);
	} while (--count > 0);

	_hoops_CRHCC (_hoops_PGPCC, "ET\n");

	return;
}

local void
_hoops_GIHCC (_hoops_GHACC * _hoops_PGPCC, int mask, int count, int _hoops_IGHCP, float const *points)
{

	/* _hoops_ARHHI - _hoops_AISI _hoops_CIHH/_hoops_GRICC _hoops_PIAP, _hoops_SPHAI - _hoops_IHIS _hoops_IS. */
	_hoops_CRHCC (_hoops_PGPCC, "%g %g m", points[0], points[1]);
	--count;
	points += _hoops_IGHCP;

	while (count-- > 0) {
		/* _hoops_GSSAA - _hoops_III _hoops_IS */
		_hoops_CRHCC (_hoops_PGPCC, "%g %g l", points[0], points[1]);
		points += _hoops_IGHCP;
	}

	/* _hoops_GGHR - _hoops_SPGCA _hoops_CGHI _hoops_PPSR _hoops_IS _hoops_SRS _hoops_PPSR, _hoops_SRSCI - _hoops_CIHH _hoops_CRAA, _hoops_ACHP - _hoops_GA'_hoops_RA _hoops_RGISR */
	if (mask)
		_hoops_CRHCC (_hoops_PGPCC, "h W n\n");
	else
		_hoops_CRHCC (_hoops_PGPCC, "h W* n\n");
	return;
}

/*******************************************************************************
 * _hoops_HIGGR _hoops_HAACC _hoops_HSCAR _hoops_PPR _hoops_GPCA
 ******************************************************************************/

/*******************************************************************************
 * _hoops_PCSH _hoops_AGAH _hoops_ASGC _hoops_SGS _hoops_AASA _hoops_CRGR _hoops_HAACC _hoops_GPCA
 ******************************************************************************/

local const unsigned char _hoops_RPCSR[256 - 32] =
	{ 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149,
149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 149, 149, 149, 149, 149, 0,
149, 149, 0, 149, 149, 0, 149, 0, 149, 149, 0, 0, 0, 149, 0, 149, 149, 149, 0, 149, 149, 0, 0, 0, 149, 149, 149, 149, 149, 149,
149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 0, 149, 149, 149, 149, 149, 149, 0, 149, 149, 149, 149, 149, 0, 0, 149,
149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 0, 149, 149, 149, 149, 149, 149, 0, 149, 149,
149, 149, 149, 0, 0, 149, };
local const unsigned char _hoops_RRICC[256 - 32] =
	{ 70, 78, 89, 138, 138, 220, 165, 56, 83, 83, 97, 145, 70, 83, 70, 70, 138, 138, 138, 138,
138, 138, 138, 138, 138, 138, 70, 70, 145, 145, 145, 138, 250, 165, 165, 179, 179, 165, 152, 192, 179, 70, 124, 165, 138, 206, 179,
192, 165, 192, 179, 165, 152, 179, 165, 233, 165, 165, 152, 70, 70, 70, 117, 138, 56, 138, 138, 124, 138, 138, 70, 138, 138, 56,
56, 124, 56, 206, 138, 138, 138, 138, 83, 124, 70, 138, 124, 179, 124, 124, 124, 84, 66, 84, 145, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 138, 138, 138, 138, 0, 138, 83, 0, 93, 138, 0, 138, 0,
247, 83, 0, 0, 0, 83, 0, 133, 70, 83, 0, 91, 138, 0, 0, 0, 152, 165, 165, 165, 165, 165, 165, 247, 179, 165, 165, 165, 165, 70, 70,
70, 70, 0, 179, 192, 192, 192, 192, 192, 0, 192, 179, 179, 179, 179, 0, 0, 152, 138, 138, 138, 138, 138, 138, 220, 124, 138, 138,
138, 138, 70, 70, 70, 70, 0, 138, 138, 138, 138, 138, 138, 0, 152, 138, 138, 138, 138, 0, 0, 124, };
local const unsigned char _hoops_ARICC[256 - 32] =
	{ 70, 83, 118, 138, 138, 220, 179, 70, 83, 83, 97, 145, 70, 83, 70, 70, 138, 138, 138, 138,
138, 138, 138, 138, 138, 138, 83, 83, 145, 145, 145, 152, 241, 179, 179, 179, 179, 165, 152, 192, 179, 70, 138, 179, 152, 206, 179, 192,
165, 192, 179, 165, 152, 179, 165, 233, 165, 165, 152, 83, 70, 83, 145, 138, 70, 138, 152, 138, 152, 138, 83, 152, 152, 70, 70, 138, 70,
220, 152, 152, 152, 152, 97, 138, 83, 152, 138, 192, 138, 138, 124, 97, 71, 97, 145, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 138, 138, 138, 138, 0, 138, 83, 0, 93, 138, 0, 138, 0, 247, 83, 0, 0, 0, 83, 0,
138, 70, 83, 0, 91, 138, 0, 0, 0, 152, 179, 179, 179, 179, 179, 179, 247, 179, 165, 165, 165, 165, 70, 70, 70, 70, 0, 179, 192, 192,
192, 192, 192, 0, 192, 179, 179, 179, 179, 0, 0, 152, 138, 138, 138, 138, 138, 138, 220, 138, 138, 138, 138, 138, 70, 70, 70, 70, 0,
152, 152, 152, 152, 152, 152, 0, 152, 152, 152, 152, 152, 0, 0, 138, };
local const unsigned char _hoops_PPCSR[256 - 32] =
	{ 63, 83, 102, 124, 124, 206, 192, 83, 83, 83, 124, 140, 63, 83, 63, 70, 124, 124, 124, 124,
124, 124, 124, 124, 124, 124, 70, 70, 140, 140, 140, 111, 227, 179, 165, 165, 179, 152, 138, 179, 179, 83, 97, 179, 152, 220,
179, 179, 138, 179, 165, 138, 152, 179, 179, 233, 179, 179, 152, 83, 70, 83, 117, 124, 83, 111, 124, 111, 124, 111, 83, 124,
124, 70, 70, 124, 70, 192, 124, 124, 124, 124, 83, 97, 70, 124, 124, 179, 124, 124, 111, 119, 51, 119, 134, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 124, 124, 124, 124, 0, 124, 83, 0, 70,
124, 0, 124, 0, 247, 83, 0, 0, 0, 83, 0, 113, 63, 83, 0, 78, 124, 0, 0, 0, 111, 179, 179, 179, 179, 179, 179, 220, 165, 152,
152, 152, 152, 83, 83, 83, 83, 0, 179, 179, 179, 179, 179, 179, 0, 179, 179, 179, 179, 179, 0, 0, 124, 111, 111, 111, 111, 111,
111, 165, 111, 111, 111, 111, 111, 70, 70, 70, 70, 0, 124, 124, 124, 124, 124, 124, 0, 124, 124, 124, 124, 124, 0, 0, 124, };
local const unsigned char _hoops_PRICC[256 - 32] =
	{ 63, 83, 105, 124, 124, 206, 192, 83, 83, 83, 124, 167, 63, 83, 63, 70, 124, 124, 124, 124,
124, 124, 124, 124, 124, 124, 83, 83, 167, 167, 167, 124, 227, 152, 152, 165, 179, 152, 152, 179, 179, 83, 111, 165, 138, 206, 165,
179, 152, 179, 152, 124, 138, 179, 152, 206, 152, 138, 138, 97, 70, 97, 105, 124, 83, 124, 124, 111, 124, 111, 70, 124, 124, 70, 70,
111, 70, 179, 124, 124, 124, 124, 97, 97, 70, 124, 111, 165, 111, 111, 97, 100, 69, 100, 134, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 97, 124, 124, 124, 124, 0, 124, 83, 0, 70, 124, 0, 124, 0, 220, 83, 0,
0, 0, 83, 0, 130, 63, 83, 0, 78, 124, 0, 0, 0, 124, 152, 152, 152, 152, 152, 152, 220, 165, 152, 152, 152, 152, 83, 83, 83, 83, 0,
165, 179, 179, 179, 179, 179, 0, 179, 179, 179, 179, 179, 0, 0, 124, 124, 124, 124, 124, 124, 124, 165, 111, 111, 111, 111, 111, 70,
70, 70, 70, 0, 124, 124, 124, 124, 124, 124, 0, 124, 124, 124, 124, 124, 0, 0, 111, };
local const unsigned char _hoops_HRICC[256 - 32] =
	{ 63, 83, 138, 124, 124, 247, 206, 83, 83, 83, 124, 141, 63, 83, 63, 70, 124, 124, 124, 124,
124, 124, 124, 124, 124, 124, 83, 83, 141, 141, 141, 124, 230, 179, 165, 179, 179, 165, 152, 192, 192, 97, 124, 192, 165, 233, 179,
192, 152, 192, 179, 138, 165, 179, 179, 247, 179, 179, 165, 83, 70, 83, 144, 124, 83, 124, 138, 111, 138, 111, 83, 124, 138, 70, 83,
138, 70, 206, 138, 124, 138, 138, 111, 97, 83, 138, 124, 179, 124, 124, 111, 98, 56, 98, 129, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 124, 124, 124, 124, 0, 124, 83, 0, 75, 124, 0, 124, 0, 247, 83,
0, 0, 0, 83, 0, 134, 63, 83, 0, 83, 124, 0, 0, 0, 124, 179, 179, 179, 179, 179, 179, 247, 179, 165, 165, 165, 165, 97, 97, 97, 97,
0, 179, 192, 192, 192, 192, 192, 0, 192, 179, 179, 179, 179, 0, 0, 138, 124, 124, 124, 124, 124, 124, 179, 111, 111, 111, 111, 111,
70, 70, 70, 70, 0, 138, 124, 124, 124, 124, 124, 0, 124, 138, 138, 138, 138, 0, 0, 124, };
local const unsigned char _hoops_IRICC[256 - 32] =
	{ 63, 97, 138, 124, 124, 206, 192, 83, 83, 83, 124, 141, 63, 83, 63, 70, 124, 124, 124, 124,
124, 124, 124, 124, 124, 124, 83, 83, 141, 141, 141, 124, 206, 165, 165, 165, 179, 165, 165, 179, 192, 97, 124, 165, 152, 220, 179, 179,
152, 179, 165, 138, 152, 179, 165, 220, 165, 152, 152, 83, 70, 83, 141, 124, 83, 124, 124, 111, 124, 111, 83, 124, 138, 70, 70, 124, 70,
192, 138, 124, 124, 124, 97, 97, 70, 138, 111, 165, 124, 111, 97, 87, 56, 87, 141, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 97, 124, 124, 124, 124, 0, 124, 83, 0, 67, 124, 0, 124, 0, 247, 83, 0, 0, 0, 83, 0, 124,
63, 83, 0, 75, 124, 0, 0, 0, 124, 165, 165, 165, 165, 165, 165, 233, 165, 165, 165, 165, 165, 97, 97, 97, 97, 0, 179, 179, 179, 179, 179,
179, 0, 179, 179, 179, 179, 179, 0, 0, 124, 124, 124, 124, 124, 124, 124, 179, 111, 111, 111, 111, 111, 70, 70, 70, 70, 0, 138, 124, 124,
124, 124, 124, 0, 124, 138, 138, 138, 138, 0, 0, 111, };
local const unsigned char _hoops_HPCSR[256 - 32] =
	{ 63, 83, 176, 124, 136, 206, 192, 109, 83, 83, 124, 136, 63, 136, 63, 70, 124, 124, 124,
124, 124, 124, 124, 124, 124, 124, 70, 70, 136, 136, 136, 111, 136, 179, 165, 179, 152, 152, 189, 150, 179, 83, 156, 179, 170,
220, 179, 179, 190, 183, 138, 147, 152, 171, 109, 190, 160, 197, 152, 83, 213, 83, 163, 124, 124, 156, 136, 136, 123, 109, 130,
103, 150, 83, 150, 136, 136, 143, 130, 136, 136, 130, 136, 150, 109, 143, 176, 170, 123, 170, 123, 119, 51, 119, 136, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 154, 62, 136, 43, 176, 124, 186,
186, 186, 186, 255, 244, 150, 244, 150, 100, 136, 103, 136, 136, 176, 123, 115, 136, 136, 136, 136, 247, 150, 247, 163, 203,
170, 197, 244, 190, 190, 203, 190, 190, 176, 176, 176, 176, 176, 176, 176, 190, 176, 195, 195, 220, 203, 136, 63, 176, 150, 150,
255, 244, 150, 244, 150, 123, 83, 195, 195, 194, 176, 96, 96, 96, 96, 96, 96, 123, 123, 123, 123, 0, 83, 69, 170, 170, 170, 96,
96, 96, 96, 96, 96, 123, 123, 123, 0, };

/*
 * _hoops_HSCAR _hoops_SGS _hoops_RHGSR _hoops_HCPH _hoops_IS _hoops_SRAC _hoops_SICAR
 */
struct _hoops_CRICC
{
	_hoops_GHACC *_hoops_PGPCC;
	/*! _hoops_SRICC _hoops_PPR _hoops_APPS _hoops_CHR _hoops_GGR _hoops_IPIHH _hoops_ARI. */
	int width, height;
	/*! _hoops_GAICC _hoops_GGR _hoops_PAGAI _hoops_RIR _hoops_CPIHH. */
	int _hoops_HAP;

	/* _hoops_HCISR _hoops_PIAP */
	int _hoops_RAICC;
	int _hoops_AAICC;
	int _hoops_IRSRI;
	float _hoops_RACSR;
	float _hoops_PAICC;
	float _hoops_HAICC;
	char *_hoops_IAICC;
	int _hoops_CAICC;
	int _hoops_SAICC;
	int _hoops_GPICC;
	_hoops_GARRR _hoops_RPICC;
	Driver_Color _hoops_APICC;
	Driver_Color _hoops_AARSR;
	bool _hoops_PPICC;
	bool _hoops_PRGGH;
	_hoops_HIPCC *locale;
};

struct _hoops_PSISR
{
	unsigned char const *_hoops_HSISR;
	float _hoops_ISISR;
	int _hoops_CSISR;
	char *_hoops_SSISR;
};

#define _hoops_HPICC(dc) ((_hoops_CRICC alter *)(dc->data))

local bool
_hoops_IPICC (Display_Context alter * dc)
{
	_hoops_CRICC alter *state;

	_hoops_AHCRI ("pdf_start_device");

	ZALLOC (state, _hoops_CRICC);

	dc->data = (void alter *) state;
	/* _hoops_SIGP: _hoops_HAR _hoops_RCRR _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_SIGR _hoops_CPRIR. */
	HD_Get_Bit_Patterns (dc, false);

	return (true);
}



local void
_hoops_CPICC (Display_Context alter * dc)
{
	_hoops_CRICC alter *state = _hoops_HPICC (dc);

	_hoops_AHCRI ("pdf_stop_device");

	if (state->_hoops_PGPCC) {
		_hoops_RGHCC (state->_hoops_PGPCC);
		state->_hoops_PGPCC = 0;
	}

	if (state->_hoops_IAICC) {
		FREE_ARRAY (state->_hoops_IAICC, _hoops_SSGR (state->_hoops_IAICC) + 1, char);
	}
	FREE (state, _hoops_CRICC);
	dc->data = null;

	return;
}

/* _hoops_HGI _hoops_API _hoops_RGAR _hoops_CRGS _hoops_AGAH _hoops_RH _hoops_SHIR _hoops_IGIR _hoops_IH _hoops_RH _hoops_HAACC _hoops_RHPP. */
local void
_hoops_SPICC (Display_Context alter * dc)
{
	_hoops_AHCRI ("pdf_get_default_size");

	float const width = 8.5f;
	float const height = 11.0f;
	float const _hoops_HGII = 150;

	dc->_hoops_PGCC._hoops_ARISR.x = 0;
	dc->_hoops_PGCC._hoops_ARISR.y = 0;
	dc->_hoops_PGCC._hoops_PRPSR.x = (int) (_hoops_HGII * width);
	dc->_hoops_PGCC._hoops_PRPSR.y = (int) (_hoops_HGII * height);
	dc->_hoops_PGCC.size.x = width * 2.54;
	dc->_hoops_PGCC.size.y = height * 2.54;

	return;
}


/* _hoops_HGI _hoops_API _hoops_SAGGR _hoops_RH _hoops_AAP _hoops_HII _hoops_AGAH _hoops_IH _hoops_IGIR, _hoops_HGISR _hoops_RH _hoops_RSACC _hoops_RHPP'_hoops_GRI _hoops_IGIR
 * _hoops_PPR _hoops_IGISR _hoops_GGR _hoops_RH _hoops_HSH _hoops_GGR _hoops_SCGR _hoops_HIS _hoops_AGAH _hoops_CGISR _hoops_PCPA _hoops_IGIR _hoops_SR _hoops_IGRC _hoops_ARP. */
local void
_hoops_GHICC (Display_Context alter * dc)
{
	_hoops_AHCRI ("pdf_set_size");

	_hoops_CRICC alter *state = _hoops_HPICC (dc);

	state->_hoops_HAP = dc->options._hoops_GHHSR;

	/* #11903 _hoops_RGAR _hoops_ARP _hoops_SHIR _hoops_III _hoops_SGCR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_PIP _hoops_IPPSR _hoops_III _hoops_SGCR. */
	if (!dc->options._hoops_HHHSR)
		dc->_hoops_PGCC._hoops_IHHSR = dc->options._hoops_GHHSR / 150.0f;

	if (dc->options._hoops_SPHSR.x != -1) {
		state->width = (int) (72 * dc->options._hoops_SPHSR.x / 2.54f);
		state->height = (int) (72 * dc->options._hoops_SPHSR.y / 2.54f);
	}
	else {
		state->width = (int) (72 * dc->_hoops_PGCC.size.x / 2.54f);
		state->height = (int) (72 * dc->_hoops_PGCC.size.y / 2.54f);
	}

	dc->current._hoops_HAP.x = state->_hoops_HAP / 2.54f;
	dc->current._hoops_HAP.y = state->_hoops_HAP / 2.54f;
	dc->current._hoops_PRPSR.x = (int) (state->_hoops_HAP * state->width / 72.0f);
	dc->current._hoops_PRPSR.y = (int) (state->_hoops_HAP * state->height / 72.0f);

	return;
}


local void
_hoops_RHICC (Display_Context alter * dc)
{
	_hoops_AHCRI ("pdf_get_physical_info");

	_hoops_SPICC (dc);

	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
	dc->_hoops_PGCC._hoops_PCHSR = 256;
	dc->_hoops_PGCC.flags |= _hoops_CAPGH;
	dc->_hoops_PGCC.flags &= ~_hoops_RSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_PSHSR;
	dc->_hoops_PGCC.flags &= ~_hoops_HSHSR;
	dc->_hoops_PGCC.flags |= _hoops_ISHSR;
	dc->_hoops_PGCC.flags |= _hoops_HPPGH;
	dc->_hoops_PGCC.flags |= _hoops_GIHSR;
	dc->_hoops_PGCC.flags |= _hoops_IPPGH;
	dc->_hoops_PGCC.flags |= _hoops_CCHSR;
	dc->_hoops_PGCC.flags |= _hoops_ISRIP;
	dc->flags |= _hoops_CSHSR;
	dc->_hoops_PGCC.driver_type = "PDF";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.299 $";
	dc->_hoops_PGCC._hoops_ICHSR = "laser printer";


	return;
}


local void
_hoops_AHICC (Display_Context alter * dc)
{
	_hoops_AHCRI ("pdf_current_info");

	_hoops_GHICC (dc);

	return;
}


local POINTER_SIZED_INT
_hoops_PHICC (Display_Context const *_hoops_RSAAI)
{
	Display_Context alter *dc = (Display_Context alter *) _hoops_RSAAI;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);

	_hoops_AHCRI ("pdf_get_outer_window");

	if (!BIT (dc->flags, _hoops_SAISR) && !state->_hoops_PGPCC) {
		if ((state->_hoops_PGPCC = _hoops_SAHCC ((char *) dc->_hoops_PCRSR)) != null) {
			/* _hoops_RPP _hoops_RH _hoops_HHICC _hoops_IGRH _hoops_HRGR *_hoops_HAR* _hoops_ARP, _hoops_SAGR _hoops_RH _hoops_RGHR. */
			if (BIT (dc->options._hoops_IRARR, _hoops_ASACC)) {
				_hoops_SHHCC (state->_hoops_PGPCC, _hoops_HSACC);
			}
			else {
				_hoops_SHHCC (state->_hoops_PGPCC, PDF_ZLIB);
			}
		}
		else {
			HE_ERROR (HEC_PDF_DRIVER,
				  HES_FILE_OPEN,
				  Sprintf_S (null,
					     "Cannot open PDF output file - %s", dc->_hoops_PCRSR)
				);
			state->_hoops_PRGGH = true;
		}
	}

	if (dc->options._hoops_SPHSR.x != -1) {
		dc->_hoops_PGCC.extent.right = state->_hoops_HAP * dc->options._hoops_SPHSR.x / 2.54f;
		dc->_hoops_PGCC.extent.top = state->_hoops_HAP * dc->options._hoops_SPHSR.y / 2.54f;
	}
	else {
		dc->_hoops_PGCC.extent.right = state->_hoops_HAP * 8.5f;
		dc->_hoops_PGCC.extent.top = state->_hoops_HAP * 11.0f;
	}
	dc->_hoops_PGCC.extent.left = 0;
	dc->_hoops_PGCC.extent.bottom = 0;

	dc->_hoops_PGCC._hoops_PRPSR.x = (int) (dc->_hoops_PGCC.extent.right);
	dc->_hoops_PGCC._hoops_PRPSR.y = (int) (dc->_hoops_PGCC.extent.top);

	return ((POINTER_SIZED_INT) state->_hoops_PGPCC);
}


local void
_hoops_IHICC (Display_Context const *dc)
{
	_hoops_CRICC alter *state = _hoops_HPICC (dc);

	_hoops_AHCRI ("pdf_free_outer_window");

	if (state->_hoops_PRGGH)
		return;

	if (BIT (dc->flags, _hoops_SAISR)) {
		_hoops_RPHCC (state->_hoops_PGPCC);
		state->_hoops_PPICC = false;
	}
	return;
}


local void
_hoops_CHICC (Net_Rendition const &nr)
{
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);

	_hoops_AHCRI ("pdf_init_picture");

	if(state->locale == 0)
		state->locale = new _hoops_HIPCC;

	if (state->_hoops_PRGGH)
		return;

	if (!state->_hoops_PPICC && BIT (dc->flags, _hoops_SAISR)) {
		if (dc->options._hoops_ARPSR) {
			_hoops_GPHCC (state->_hoops_PGPCC, state->height, state->width, state->_hoops_HAP);
		}
		else {
			_hoops_GPHCC (state->_hoops_PGPCC, state->width, state->height, state->_hoops_HAP);
		}
		state->_hoops_PPICC = true;
	}
	/* _hoops_HIAP _hoops_RH _hoops_HCISR _hoops_PIAP      */
	state->_hoops_RPICC = -1;

	return;
}


local void
_hoops_SHICC (Net_Rendition const &nr, bool swap_buffers)
{
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);

	_hoops_AHCRI ("pdf_finish_picture");

	ASSERT (state->locale != 0);
	delete state->locale;
	state->locale = 0;

	UNREFERENCED (swap_buffers);

	if (state->_hoops_PRGGH)
		return;

	if (state->_hoops_PPICC && BIT (dc->flags, _hoops_SAISR)) {
		_hoops_RPHCC (state->_hoops_PGPCC);
		state->_hoops_PPICC = false;
	}
	return;
}


enum
{
	_hoops_GIICC = 1 << 0,

	_hoops_RIICC = 1 << 2,
	_hoops_AIICC = 1 << 3,
	_hoops_PIICC = 1 << 4,
	_hoops_HIICC = 1 << 5,
	_hoops_IIICC =
		_hoops_RIICC | _hoops_AIICC | _hoops_PIICC | _hoops_HIICC,

	_hoops_CIICC = 1 << 6,
	_hoops_SIICC = 1 << 7,
	_hoops_GCICC = _hoops_CIICC | _hoops_SIICC,

	_hoops_RCICC = 1 << 8,
	_hoops_ACICC = 1 << 9,
	_hoops_PCICC = 1 << 10,
	_hoops_HCICC = _hoops_RCICC | _hoops_ACICC | _hoops_PCICC
};

local void
_hoops_ICICC (Net_Rendition const &nr, long flags)
{
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	_hoops_IGCSR const &_hoops_HRCIR = nr->_hoops_SISI;
	RGBAS32 color;


	if ((flags & _hoops_GIICC) && state->_hoops_RPICC != _hoops_IHCR->_hoops_CPA) {

		/* _hoops_ARRC _hoops_RH _hoops_CGHI _hoops_CIHH _hoops_CRAA _hoops_GAR _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_AISI _hoops_IRS _hoops_CCAH _hoops_SPR. */
		_hoops_PPHCC (state->_hoops_PGPCC);
		_hoops_APHCC (state->_hoops_PGPCC);
		if (_hoops_IHCR->_hoops_HCHH) {
			_hoops_ASHH const *_hoops_CRAIR = _hoops_IHCR->_hoops_HCHH->_hoops_PSHH;
			do {
				if (!BIT (_hoops_CRAIR->flags, _hoops_RHIH)) {
					
					float _hoops_CCICC[4][2];

					_hoops_PACIR _hoops_RCHS = _hoops_IHCR->_hoops_AGAA;
					/* _hoops_GCRR _hoops_RH _hoops_CIHH _hoops_SPR _hoops_HPI _hoops_SCICC _hoops_HIS _hoops_SSIA _hoops_CHR _hoops_GSICC. */
					_hoops_RCHS._hoops_IACHA(0.5f);

					_hoops_CCICC[0][0] = _hoops_RCHS.left;
					_hoops_CCICC[0][1] = _hoops_RCHS.bottom;
					_hoops_CCICC[1][0] = _hoops_RCHS.right;
					_hoops_CCICC[1][1] = _hoops_RCHS.bottom;
					_hoops_CCICC[2][0] = _hoops_RCHS.right;
					_hoops_CCICC[2][1] = _hoops_RCHS.top;
					_hoops_CCICC[3][0] = _hoops_RCHS.left;
					_hoops_CCICC[3][1] = _hoops_RCHS.top;
					_hoops_GIHCC (state->_hoops_PGPCC, 0, 4, 2,
								  (float *) _hoops_CCICC);
				}
				_hoops_GIHCC (state->_hoops_PGPCC,
							  BIT (_hoops_CRAIR->flags, _hoops_RHIH),
							  _hoops_CRAIR->count, 3, (float *) _hoops_CRAIR->points);
			} while ((_hoops_CRAIR = _hoops_CRAIR->next) != null);
		}
		else {
			
			float _hoops_CCICC[4][2];

			_hoops_PACIR _hoops_RCHS = _hoops_IHCR->_hoops_AGAA;
			/* _hoops_GCRR _hoops_RH _hoops_CIHH _hoops_SPR _hoops_HPI _hoops_SCICC _hoops_HIS _hoops_SSIA _hoops_CHR _hoops_GSICC. */
			_hoops_RCHS._hoops_IACHA(0.5f);

			_hoops_CCICC[0][0] = _hoops_RCHS.left;
			_hoops_CCICC[0][1] = _hoops_RCHS.bottom;
			_hoops_CCICC[1][0] = _hoops_RCHS.right;
			_hoops_CCICC[1][1] = _hoops_RCHS.bottom;
			_hoops_CCICC[2][0] = _hoops_RCHS.right;
			_hoops_CCICC[2][1] = _hoops_RCHS.top;
			_hoops_CCICC[3][0] = _hoops_RCHS.left;
			_hoops_CCICC[3][1] = _hoops_RCHS.top;

			_hoops_GIHCC (state->_hoops_PGPCC, 0, 4, 2, (float *) _hoops_CCICC);
		}

		/* _hoops_HIAP _hoops_RH _hoops_HCISR _hoops_PIAP      */
		state->_hoops_RPICC = _hoops_IHCR->_hoops_CPA;
		state->_hoops_RAICC = 0;
		state->_hoops_AAICC = 1;
		state->_hoops_IRSRI = 1;
		state->_hoops_AARSR = _hoops_CAHSR::_hoops_SAHSR;
		state->_hoops_APICC = _hoops_CAHSR::_hoops_SAHSR;
		state->_hoops_RACSR = -1;
		state->_hoops_SAICC = -1;
		state->_hoops_GPICC = 0;
		state->_hoops_CAICC = -1;
		state->_hoops_PAICC = 0;
		state->_hoops_HAICC = 1;
		if (state->_hoops_IAICC) {
			FREE_ARRAY (state->_hoops_IAICC,
				    _hoops_SSGR (state->_hoops_IAICC) + 1, char);
			state->_hoops_IAICC = 0;
		}

	}

	if (_hoops_HC) {
		if ((flags & _hoops_RIICC)
		    && state->_hoops_RAICC != (_hoops_HC->style & LCAP_MASK) >> LCAP_SHIFT) {
			_hoops_GHHCC (state->_hoops_PGPCC, (_hoops_HC->style & LCAP_MASK) >> LCAP_SHIFT);
			state->_hoops_RAICC = (_hoops_HC->style & LCAP_MASK) >> LCAP_SHIFT;
		}

		if ((flags & _hoops_AIICC)
		    && state->_hoops_AAICC != (_hoops_HC->style & LJOIN_MASK) >> LJOIN_SHIFT) {
			_hoops_SPHCC (state->_hoops_PGPCC, (_hoops_HC->style & LJOIN_MASK) >> LJOIN_SHIFT);
			state->_hoops_AAICC = (_hoops_HC->style & LJOIN_MASK) >> LJOIN_SHIFT;
		}

		if ((flags & _hoops_PIICC) && state->_hoops_IRSRI != _hoops_HC->weight) {
			_hoops_AHHCC (state->_hoops_PGPCC, _hoops_HC->weight);
			state->_hoops_IRSRI = _hoops_HC->weight;
		}

		if ((flags & _hoops_HIICC) && state->_hoops_SAICC != _hoops_HC->_hoops_CPA) {
			int *pattern, _hoops_RHISR;
			float scale;

			if (BIT (_hoops_HC->line_style->_hoops_GHISR[0].flags, LSF_ABSOLUTE_LENGTH))
				scale = 1.0f;
			else
				scale = dc->_hoops_PGCC._hoops_ICPGH;

			pattern = _hoops_HC->line_style->_hoops_GHISR[0].pattern;
			_hoops_RHISR = _hoops_HC->line_style->_hoops_GHISR[0]._hoops_RHISR;

			if (!(state->_hoops_GPICC == 0 && _hoops_RHISR == 0)) {
				_hoops_RHHCC (state->_hoops_PGPCC, _hoops_RHISR, pattern, scale);

				state->_hoops_GPICC = _hoops_RHISR;
			}
			state->_hoops_SAICC = _hoops_HC->_hoops_CPA;
		}

		if (flags & _hoops_CIICC) {
			_hoops_AAASP (dc, _hoops_HC->color, dc->_hoops_PGCC._hoops_PIHSR, color);
			if (state->_hoops_APICC != color) {
				_hoops_CPHCC (state->_hoops_PGPCC, color.r / 255.0f,
						      color.g / 255.0f, color.b / 255.0f);
				state->_hoops_APICC = color;
			}
		}
	}

	if (_hoops_SIGA) {
		if (flags & _hoops_SIICC) {
			_hoops_AAASP (dc, _hoops_SIGA->color, dc->_hoops_PGCC._hoops_PIHSR, color);
			if (state->_hoops_AARSR != color) {
				_hoops_IPHCC (state->_hoops_PGPCC, color.r / 255.0f, color.g / 255.0f,
						    color.b / 255.0f);
				state->_hoops_AARSR = color;
			}
		}
	}

	if (_hoops_HRCIR && _hoops_HRCIR->font) {
		if ((flags & _hoops_RCICC)) {
			int _hoops_GSHIH = _hoops_HRCIR->font->family->_hoops_RRCSR;
			char const *_hoops_SSISR = 0;

			switch (_hoops_GSHIH) {

#ifdef FREETYPE
			case _hoops_SISSP:
				/* _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_CIH _hoops_GPRR _hoops_HRCSR. */
				{
					_hoops_GPGGH const *_hoops_RSCGI =
						(_hoops_GPGGH const *) _hoops_HRCIR->font->_hoops_GAASR;
					_hoops_SSISR = _hoops_RSCGI->_hoops_SSISR.text;
				} break;
#endif
			default:
				/* _hoops_HGI _hoops_HRGR _hoops_IRS _hoops_CSHCC _hoops_HRCSR (_hoops_GAR _hoops_SR _hoops_RGAR _hoops_RGHH _hoops_SGRRI _hoops_PPR _hoops_CSHCC _hoops_GSPIP). */
				{
					_hoops_PSISR const *_hoops_GACSR =
						(_hoops_PSISR const *) _hoops_HRCIR->font->_hoops_GAASR;
					_hoops_SSISR = _hoops_GACSR->_hoops_SSISR;
				}
			}

			if (state->_hoops_IAICC
			    && strcmp (state->_hoops_IAICC, _hoops_SSISR) != 0
			    || state->_hoops_RACSR != _hoops_HRCIR->font->_hoops_RACSR) {

#ifdef FREETYPE
				if (_hoops_GSHIH == _hoops_SISSP) {
					_hoops_GPGGH const *_hoops_RSCGI =
						(_hoops_GPGGH const *) _hoops_HRCIR->font->_hoops_GAASR;
					if (!BIT (dc->options._hoops_IRARR, _hoops_PSACC)) {
						_hoops_SASC _hoops_RSHIH;
						float _hoops_RSICC = 0;

						HD_Get_Freetype_Font_Bounding (_hoops_HRCIR->font, _hoops_RSHIH);
						/* _hoops_CIA _hoops_GH _hoops_RH _hoops_APSR _hoops_APPS 20% _hoops_IH _hoops_IRS _hoops_ASICC _hoops_IASC. */
						_hoops_RSICC = 1.2f * (_hoops_RSHIH.max.y - _hoops_RSHIH.min.y);

						/* _hoops_PSICC _hoops_GC _hoops_IS _hoops_IPSP _hoops_GC _hoops_PHCSH = 1/72 * 1/1000 = 1/7200 */
						_hoops_RSHIH.min.x *= _hoops_RSICC / 7200.0f;
						_hoops_RSHIH.max.x *= _hoops_RSICC / 7200.0f;
						_hoops_RSHIH.min.y *= _hoops_RSICC / 7200.0f;
						_hoops_RSHIH.max.y *= _hoops_RSICC / 7200.0f;
						_hoops_HHHCC (state->_hoops_PGPCC, _hoops_SSISR,
								_hoops_RSCGI->_hoops_APGGH.text,
								(int) _hoops_RSHIH.min.x,
								(int) _hoops_RSHIH.max.x,
								(int) _hoops_RSHIH.min.y,
								(int) _hoops_RSHIH.max.y,
								_hoops_RRICC);
					}
				}
				else {
					_hoops_PHHCC (state->_hoops_PGPCC, _hoops_SSISR);
				}
#endif
				_hoops_IHHCC (state->_hoops_PGPCC, _hoops_HRCIR->font->_hoops_RACSR,
					      _hoops_SSISR);
				if (state->_hoops_IAICC) {
					FREE_ARRAY (state->_hoops_IAICC,
						    _hoops_SSGR (state->_hoops_IAICC) + 1,
						    char);
				}
				ALLOC_ARRAY (state->_hoops_IAICC,
					     _hoops_SSGR (_hoops_SSISR) + 1, char);
				COPY_MEMORY (_hoops_SSISR, _hoops_SSGR (_hoops_SSISR) + 1,
					     state->_hoops_IAICC);
				state->_hoops_RACSR = _hoops_HRCIR->font->_hoops_RACSR;
			}
		}
		if (flags & _hoops_ACICC) {
			_hoops_AAASP (dc, _hoops_HRCIR->color, dc->_hoops_PGCC._hoops_PIHSR, color);
			if (state->_hoops_AARSR != color) {
				_hoops_IPHCC (state->_hoops_PGPCC, color.r / 255.0f, color.g / 255.0f,
						    color.b / 255.0f);
				state->_hoops_AARSR = color;
			}
			if (state->_hoops_APICC != color) {
				_hoops_CPHCC (state->_hoops_PGPCC, color.r / 255.0f,
						      color.g / 255.0f, color.b / 255.0f);
				state->_hoops_APICC = color;
			}
		}
		if (flags & _hoops_PCICC) {
			if (state->_hoops_CAICC != _hoops_RGICC && _hoops_HRCIR->outline) {
				_hoops_CHHCC (state->_hoops_PGPCC, _hoops_RGICC);
				state->_hoops_CAICC = _hoops_RGICC;
			}
			else if (state->_hoops_CAICC != _hoops_GGICC && !_hoops_HRCIR->outline) {
				_hoops_CHHCC (state->_hoops_PGPCC, _hoops_GGICC);
				state->_hoops_CAICC = _hoops_GGICC;
			}
		}
	}
	return;
}

local void
_hoops_HSICC (Net_Rendition const &nr, int count, DC_Point const *points)
{
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	int _hoops_RRC;

	_hoops_AHCRI ("pdf_draw_dc_polyline");

	if (state->_hoops_PRGGH)
		return;

	if (count == 0)
		return;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}

	if (BIT (nr->_hoops_AHP->flags, _hoops_SRPI) ||
	    ANYBIT (_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS) ||
	    ANYBIT ((_hoops_HC->style & LCAP_MASK), LCAP_COMPLEX_BITS)) {
		HD_Std_DC_Polyline (nr, count, points);
		return;
	}

	/* _hoops_GHAP'_hoops_SPHAI _hoops_GIPHC _hoops_RGR _hoops_GGSR _hoops_GAR _hoops_GHAP _hoops_RHCA _hoops_AGGCI _hoops_GRS _hoops_PHPS _hoops_PPR _hoops_SCH _hoops_CRHPR
	   _hoops_GPHGC _hoops_HCGR _hoops_IHSH _hoops_HIS _hoops_GSGS _hoops_GIH! */
	//_hoops_SCSH _hoops_ISICC = (_hoops_HGICP->_hoops_IAHA & _hoops_CSICC) >> _hoops_SSICC;
	//_hoops_SCSH _hoops_ACPC = (_hoops_HGICP->_hoops_IAHA & _hoops_GGCCC) >> _hoops_RGCCC;
	//_hoops_RPP (_hoops_ISICC != _hoops_ACPC) {
	//      _hoops_AGCCC (_hoops_SCII, _hoops_RPR, _hoops_RSSA);
	//      _hoops_ASRC;
	//}

	_hoops_ICICC (nr, _hoops_GIICC | _hoops_IIICC | _hoops_CIICC);

	if (count < 0) {
		_hoops_ICHC (count, _hoops_RRC, 2);
		while (count-- > 0) {
			_hoops_CIHCC (state->_hoops_PGPCC, 2, 3, (float *) points);
			points += _hoops_RRC;
		}
	}
	else {
		_hoops_CIHCC (state->_hoops_PGPCC, count, 3, (float *) points);
	}
	return;
}


local void
_hoops_PGCCC (Net_Rendition const &nr, int left, int right, int bottom, int top)
{
	_hoops_CRICC alter *state = _hoops_HPICC (nr->_hoops_SRA);
	float points[4][2];

	_hoops_AHCRI ("pdf_draw_dc_rectangle");

	if (state->_hoops_PRGGH)
		return;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Rectangle (nr, left, right, bottom, top);
		return;
	}

	_hoops_ICICC (nr, _hoops_GIICC | _hoops_SIICC);

	points[0][0] = left;
	points[0][1] = bottom;
	points[1][0] = right;
	points[1][1] = bottom;
	points[2][0] = right;
	points[2][1] = top;
	points[3][0] = left;
	points[3][1] = top;

	_hoops_IIHCC (state->_hoops_PGPCC, 4, 2, (float *) points);
	return;
}

local void
_hoops_HGCCC (Net_Rendition const &nr, int count, DC_Point const *points)
{
	_hoops_CRICC alter *state = _hoops_HPICC (nr->_hoops_SRA);

	_hoops_AHCRI ("pdf_draw_dc_face");

	if (state->_hoops_PRGGH)
		return;

	if (count == 0)
		return;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Face (nr, count, points);
		return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Face (nr, count, points, 0, _hoops_GPHC);
		return;
	}

	_hoops_ICICC (nr, _hoops_GIICC | _hoops_SIICC);

	_hoops_IIHCC (state->_hoops_PGPCC, count, 3, (float *) points);

	return;
}


local void
_hoops_IGCCC (Net_Rendition const &nr,
			    int count, DC_Point const *points, RGBAS32 const *color)
{
	_hoops_CRICC alter *state = _hoops_HPICC (nr->_hoops_SRA);

	_hoops_AHCRI ("pdf_draw_dc_colorized_face");

	if (state->_hoops_PRGGH)
		return;

	if (count == 0)
		return;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Colorized_Face (nr, count, points, color);
		return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Face (nr, count, points, color, _hoops_GPHC | _hoops_PAIC);
		return;
	}

	_hoops_ICICC (nr, _hoops_GIICC);

	if (state->_hoops_AARSR != *color) {
		_hoops_IPHCC (state->_hoops_PGPCC, color->r / 255.0f, color->g / 255.0f,
				    color->b / 255.0f);
		state->_hoops_AARSR = *color;
	}

	_hoops_IIHCC (state->_hoops_PGPCC, count, 3, (float *) points);
	return;
}


local void
_hoops_CGCCC (Net_Rendition const &nr, int count, DC_Point const *points)
{
	_hoops_CRICC alter *state = _hoops_HPICC (nr->_hoops_SRA);
	
	int _hoops_RRC;

	_hoops_AHCRI ("pdf_draw_dc_polytriangle");

	if (state->_hoops_PRGGH)
		return;

	if (count == 0)
		return;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Polytriangle (nr, count, points);
		return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}

	_hoops_ICICC (nr, _hoops_GIICC | _hoops_SIICC);

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_IIHCC (state->_hoops_PGPCC, 3, 3, (float *) points);
		points += _hoops_RRC;
	}

	return;
}

local void
_hoops_SGCCC (Net_Rendition const &nr,
				    int count,
				    DC_Point const *points,
				    RGBAS32 const *colors, bool _hoops_AIPSP)
{
	_hoops_CRICC alter *state = _hoops_HPICC (nr->_hoops_SRA);
	int _hoops_RRC;
	bool _hoops_GRCCC = false;

	_hoops_AHCRI ("pdf_draw_dc_colorized_polytriangle");

	if (state->_hoops_PRGGH)
		return;

	if (count == 0)
		return;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Colorized_Polytris (nr, count, points, colors, _hoops_AIPSP);
		return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 0, 0, 0, 0,
					 _hoops_GPHC | (_hoops_AIPSP ? _hoops_RAIC :
								_hoops_PAIC));
		return;
	}

	_hoops_ICICC (nr, _hoops_GIICC);

	_hoops_ICHC (count, _hoops_RRC, 3);

	while (count-- > 0) {
		if (_hoops_AIPSP && !_hoops_GRCCC) {
			if (state->_hoops_AARSR != *colors) {
				_hoops_IPHCC (state->_hoops_PGPCC, colors->r / 255.0f,
						    colors->g / 255.0f, colors->b / 255.0f);
				state->_hoops_AARSR = *colors;
			}
			_hoops_GRCCC = true;
		}
		if (!_hoops_AIPSP) {
			if (state->_hoops_AARSR != *colors) {
				_hoops_IPHCC (state->_hoops_PGPCC, colors->r / 255.0f,
						    colors->g / 255.0f, colors->b / 255.0f);
				state->_hoops_AARSR = *colors;
			}
		}

		_hoops_IIHCC (state->_hoops_PGPCC, 3, 3, (float *) points);

		points += _hoops_RRC;
		if (!_hoops_AIPSP)
			++colors;
	}
	return;
}



local void
_hoops_RRCCC (Net_Rendition const &nr, Ellipse const *ellipse)
{
	_hoops_CIGA _hoops_SIGA;
	Line_Rendition _hoops_HC = nr->_hoops_RHP;
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	int i, count;
	DC_Point buffer[16];

	_hoops_AHCRI ("pdf_draw_3d_ellipse");

	if (state->_hoops_PRGGH)
		return;

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_Ellipse (nr, ellipse);
		return;
	}

	if (ellipse->type == _hoops_SGCP ||
	    ellipse->type == _hoops_CGCP ||
	    ellipse->type == _hoops_GRCP || ellipse->type == _hoops_RRCP) {

		if (BIT (nr->_hoops_RGP, T_FACES))
			_hoops_SIGA = nr->_hoops_IHA;
		else
			_hoops_SIGA = null;

		if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE))
			_hoops_HC = nr->_hoops_RHP;
		else
			_hoops_HC = null;

	}

	if (_hoops_HC && BIT (_hoops_HC->flags, _hoops_SRPI) ||
	    (ANYBIT (_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS)
	     || ANYBIT ((_hoops_HC->style & LCAP_MASK), LCAP_COMPLEX_BITS))) {
		HD_Std_3D_Ellipse (nr, ellipse);
		return;
	}

	if (_hoops_SIGA && _hoops_SIGA->pattern != FP_SOLID) {
		HD_Std_3D_Ellipse (nr, ellipse);
		return;
	}

	HD_Generate_Elliptical_Bezier (nr, (_hoops_GHHI const *) ellipse, &count, buffer);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0; i < count; i++) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition,
							     buffer[i].x, buffer[i].y,
							     buffer[i].z)) {
				HD_Std_3D_Ellipse (nr, ellipse);
				return;
			}
		}
		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}

	if (_hoops_SIGA || _hoops_HC)
		_hoops_ICICC (nr, _hoops_GIICC);

	if (_hoops_SIGA) {
		_hoops_ICICC (nr, _hoops_SIICC);
		_hoops_PIHCC (state->_hoops_PGPCC, count, 3, (float *) buffer, true);

	}

	if (_hoops_HC) {
		Net_Rendition _hoops_CRAI = nr;

		_hoops_CRAI.Modify ()->_hoops_AHP = _hoops_CRAI->_hoops_RHP;

		_hoops_ICICC (_hoops_CRAI, _hoops_IIICC | _hoops_CIICC);
		_hoops_PIHCC (state->_hoops_PGPCC, count, 3, (float *) buffer, false);
	}

	return;
}


local void
_hoops_ARCCC (Net_Rendition const &nr, Elliptical_Arc const *arc)
{
	_hoops_CIGA _hoops_SIGA = null;
	Line_Rendition _hoops_HC = nr->_hoops_AHP;
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	DC_Point buffer[16];
	int i, count;

	_hoops_AHCRI ("pdf_draw_3d_elliptical_arc");

	if (state->_hoops_PRGGH)
		return;

	/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HAR _hoops_GGR _hoops_CIHP _hoops_PHCR... */
	if (nr->transform_rendition->_hoops_SPH->projection != _hoops_CPPCR) {
		HD_Std_3D_Elliptical_Arc (nr, arc);
		return;
	}

	if (arc->type == _hoops_GRCP || arc->type == _hoops_RRCP) {
		HD_Std_3D_Elliptical_Arc (nr, arc);
		return;
	}

	if (arc->type == _hoops_SGCP || arc->type == _hoops_CGCP) {

		if (BIT (nr->_hoops_RGP, T_FACES))
			_hoops_SIGA = nr->_hoops_IHA;
		else
			_hoops_SIGA = null;

		if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE))
			_hoops_HC = nr->_hoops_RHP;
		else
			_hoops_HC = null;
	}

	if (_hoops_HC &&
	    BIT (_hoops_HC->flags, _hoops_SRPI) ||
	    (ANYBIT (_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS)
	     || ANYBIT ((_hoops_HC->style & LCAP_MASK), LCAP_COMPLEX_BITS))) {
		HD_Std_3D_Elliptical_Arc (nr, arc);
		return;
	}

	if (_hoops_SIGA && _hoops_SIGA->pattern != FP_SOLID) {
		HD_Std_3D_Elliptical_Arc (nr, arc);
		return;
	}

	HD_Generate_Elliptical_Bezier (nr, (_hoops_GHHI const *) arc, &count, buffer);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0; i < count; i++) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition,
							     buffer[i].x, buffer[i].y,
							     buffer[i].z)) {
				HD_Std_3D_Elliptical_Arc (nr, arc);
				return;
			}
		}
		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}

	if (_hoops_SIGA || _hoops_HC)
		_hoops_ICICC (nr, _hoops_GIICC);

	if (_hoops_SIGA) {
		_hoops_ICICC (nr, _hoops_SIICC);
		_hoops_PIHCC (state->_hoops_PGPCC, count, 3, (float *) buffer, true);

	}

	if (_hoops_HC) {
		_hoops_ICICC (nr, _hoops_IIICC | _hoops_CIICC);
		_hoops_PIHCC (state->_hoops_PGPCC, count, 3, (float *) buffer, false);
	}

	return;
}


local void
_hoops_PRCCC (Net_Rendition const &nr,
			    DC_Point const *center, DC_Point const *radii, float start, float end)
{
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	int i, count;
	DC_Point _hoops_SPPSI[2];
	DC_Point buffer[16];

	_hoops_AHCRI ("pdf_draw_dc_elliptical_arc");

	if (state->_hoops_PRGGH)
		return;

	if (BIT (_hoops_HC->flags, _hoops_SRPI) ||
	    ANYBIT (_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS) ||
	    ANYBIT ((_hoops_HC->style & LCAP_MASK), LCAP_COMPLEX_BITS)) {
		HD_Std_DC_Elliptical_Arc (nr, center, radii, start, end);
		return;
	}

	_hoops_SPPSI[0].x = radii->x;
	_hoops_SPPSI[1].y = radii->y;
	_hoops_SPPSI[0].y = _hoops_SPPSI[0].z = _hoops_SPPSI[1].x = _hoops_SPPSI[1].z = 0;
	HD_DC_Generate_Elliptical_Bezier (nr, center, &_hoops_SPPSI[0], &_hoops_SPPSI[1], start, end,
					  &count, buffer);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0; i < count; i++) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition,
							     buffer[i].x, buffer[i].y,
							     buffer[i].z)) {
				HD_Std_DC_Elliptical_Arc (nr, center, radii, start, end);
				return;
			}
		}
		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}

	_hoops_ICICC (nr, _hoops_GIICC | _hoops_IIICC | _hoops_CIICC);
	_hoops_PIHCC (state->_hoops_PGPCC, count, 3, (float *) buffer, false);

	return;
}

local void
_hoops_HRCCC (Net_Rendition const &nr, DC_Point const *center, DC_Point const *radii)
{
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	int i, count;
	DC_Point _hoops_SPPSI[2];
	DC_Point buffer[16];

	_hoops_AHCRI ("pdf_draw_dc_ellipse");

	if (state->_hoops_PRGGH)
		return;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Std_DC_Ellipse (nr, center, radii);
		return;
	}

	_hoops_SPPSI[0].x = radii->x;
	_hoops_SPPSI[1].y = radii->y;
	_hoops_SPPSI[0].y = _hoops_SPPSI[0].z = _hoops_SPPSI[1].x = _hoops_SPPSI[1].z = 0;

	HD_DC_Generate_Elliptical_Bezier (nr, center, &_hoops_SPPSI[0], &_hoops_SPPSI[1], 0, 1, &count,
					  buffer);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0; i < count; i++) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition,
							     buffer[i].x, buffer[i].y,
							     buffer[i].z)) {
				HD_Std_DC_Ellipse (nr, center, radii);
				return;
			}
		}
		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}

	_hoops_ICICC (nr, _hoops_GIICC | _hoops_SIICC);

	_hoops_PIHCC (state->_hoops_PGPCC, count, 3, (float *) buffer, true);

	return;
}

local void
_hoops_IRCCC (Net_Rendition const &nr, DC_Point const *center, DC_Point const *radii)
{
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	int i, count;
	DC_Point _hoops_SPPSI[2];
	DC_Point buffer[16];

	_hoops_AHCRI ("pdf_draw_dc_outline_ellipse");

	if (state->_hoops_PRGGH)
		return;

	if (BIT (_hoops_HC->flags, _hoops_SRPI) ||
	    ANYBIT (_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS) ||
	    ANYBIT ((_hoops_HC->style & LCAP_MASK), LCAP_COMPLEX_BITS)) {
		HD_Std_DC_Elliptical_Arc (nr, center, radii, 0, 1);
		return;
	}

	_hoops_SPPSI[0].x = radii->x;
	_hoops_SPPSI[1].y = radii->y;
	_hoops_SPPSI[0].y = _hoops_SPPSI[0].z = _hoops_SPPSI[1].x = _hoops_SPPSI[1].z = 0;

	HD_DC_Generate_Elliptical_Bezier (nr, center, &_hoops_SPPSI[0], &_hoops_SPPSI[1], 0, 1, &count,
					  buffer);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		for (i = 0; i < count; ++i) {
			if (!HD_Point_Within_Cutting_Planes (nr->transform_rendition,
							     buffer[i].x, buffer[i].y,
							     buffer[i].z)) {
				HD_Std_DC_Elliptical_Arc (nr, center, radii, 0, 1);
				return;
			}
		}
		/* _hoops_SHS _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_SHISR _hoops_AGIR _hoops_CAPP */
	}

	_hoops_ICICC (nr, _hoops_GIICC | _hoops_IIICC | _hoops_CIICC);

	_hoops_PIHCC (state->_hoops_PGPCC, count, 3, (float *) buffer, false);

	return;
}

local void
_hoops_CRCCC (Net_Rendition const &inr, int count, DC_Point const *points)
{
	Net_Rendition nr = inr;
	_hoops_CRICC alter *state = _hoops_HPICC (nr->_hoops_SRA);

	_hoops_AHCRI ("pdf_draw_dc_polydot");

	if (state->_hoops_PRGGH)
		return;

	if (count <= 0) {
		_hoops_AHCRI ("count <= 0");
		return;
	}

	nr.Modify ()->_hoops_IHA.Modify ()->color = nr->_hoops_AHP->color;

	_hoops_ICICC (nr, _hoops_GIICC | _hoops_SIICC);
	_hoops_SIHCC (state->_hoops_PGPCC, count, 3, (float *) points);

	return;
}


local void
_hoops_SRCCC (Net_Rendition const &nr,
		  DC_Point const *where, int count, Karacter const *kstring)
{
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	_hoops_IGCSR const &_hoops_HRCIR = nr->_hoops_SISI;

	_hoops_AHCRI ("pdf_draw_dc_text");

	if (state->_hoops_PRGGH)
		return;

	/* _hoops_ISPR _hoops_CIHH */
	_hoops_ICICC (nr, _hoops_GIICC | _hoops_HCICC);
	_hoops_RIHCC (state->_hoops_PGPCC, where->x, where->y, _hoops_HRCIR->rotation, _hoops_HRCIR->width_scale, count,
			 (unsigned short *) kstring);
	return;
}


local bool
_hoops_GACCC (Net_Rendition const &nr,
		  Font_Instance const *instance,
		  Karacter _hoops_IPCSR,
		  float alter * _hoops_GGGS, bool alter * _hoops_CPCSR, void **_hoops_SPCSR)
{
	_hoops_CRICC alter *state = _hoops_HPICC (nr->_hoops_SRA);
	_hoops_PSISR *_hoops_RHCSR = (_hoops_PSISR *) instance->_hoops_GAASR;
	int index = _hoops_IPCSR & 0x00FF;

	_hoops_AHCRI ("pdf_measure_char");

	if (state->_hoops_PRGGH)
		return (false);

	if (index >= 32 && _hoops_RHCSR->_hoops_HSISR[index - 32] > 0) {
		*_hoops_GGGS = ((float) _hoops_RHCSR->_hoops_HSISR[index - 32] * (_hoops_RHCSR->_hoops_ISISR) / 255.0);
		*_hoops_CPCSR = false;
	}
	else {
		*_hoops_GGGS = 0.0f;
		*_hoops_CPCSR = true;
	}

	*_hoops_SPCSR = (void *) 1;

	return (true);
}


local _hoops_PSISR *
_hoops_AHCSR (int const _hoops_CSISR,
		char const *const font_name, unsigned char const *const _hoops_HSISR, float const _hoops_ISISR)
{
	_hoops_PSISR *retval;

	ALLOC (retval, _hoops_PSISR);
	retval->_hoops_CSISR = _hoops_CSISR;
	ALLOC_ARRAY (retval->_hoops_SSISR, _hoops_SSGR (font_name) + 1, char);
	COPY_MEMORY (font_name, _hoops_SSGR (font_name) + 1, retval->_hoops_SSISR);
	retval->_hoops_HSISR = _hoops_HSISR;
	retval->_hoops_ISISR = _hoops_ISISR;

	return (retval);
}

local void
_hoops_PHCSR (_hoops_PSISR * const _hoops_RHCSR)
{
	FREE_ARRAY (_hoops_RHCSR->_hoops_SSISR, _hoops_SSGR (_hoops_RHCSR->_hoops_SSISR) + 1, char);
	FREE (_hoops_RHCSR, _hoops_PSISR);
	return;
}


local void *
_hoops_RACCC (Display_Context const *dc, char const *name, Font_Instance alter * instance)
{
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	_hoops_PSISR *_hoops_RHCSR = (_hoops_PSISR *) 0;
	int _hoops_ISISR = (int) instance->_hoops_RACSR;

	_hoops_AHCRI ("pdf_load_font");

	if (state->_hoops_PRGGH)
		return ((void *) 0);

	switch (name[0]) {

	default:
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				   "unexpected character table");
		_hoops_RHCSR = _hoops_AHCSR (_hoops_CPPCC, "Courier", _hoops_RPCSR, _hoops_ISISR);
		break;		/* _hoops_SHIR */

	case 'C':
		if (name[7] == '-') {
			switch (name[8]) {
			default:
				_hoops_RHCSR =
					_hoops_AHCSR (_hoops_GHPCC, "Courier-Oblique",
							_hoops_RPCSR, _hoops_ISISR);
				break;	/* _hoops_SHIR */
			case 'B':
				switch (name[12]) {
				case '\0':
					_hoops_RHCSR =
						_hoops_AHCSR (_hoops_SPPCC, "Courier-Bold",
								_hoops_RPCSR, _hoops_ISISR);
					break;	/* _hoops_AGIR '\0' */
				case 'O':
					_hoops_RHCSR =
						_hoops_AHCSR (_hoops_RHPCC,
								"Courier-BoldOblique",
								_hoops_RPCSR, _hoops_ISISR);
					break;	/* _hoops_AGIR '_hoops_RGGIR' */
				}
				break;	/* _hoops_AGIR '_hoops_IHAC' */
			}
		}
		else {
			_hoops_RHCSR = _hoops_AHCSR (_hoops_CPPCC, "Courier", _hoops_RPCSR, _hoops_ISISR);
		}
		break;		/* _hoops_AGIR '_hoops_IHRPR' */

	case 'S':
		_hoops_RHCSR = _hoops_AHCSR (_hoops_CHPCC, "Symbol", _hoops_HPCSR, _hoops_ISISR);
		break;		/* _hoops_AGIR '_hoops_IISGA' */

	case 'H':
		switch (name[9]) {
		case '-':
			switch (name[10]) {
			default:
				_hoops_RHCSR =
					_hoops_AHCSR (_hoops_HPPCC, "Helvetica-Oblique",
							_hoops_RRICC, _hoops_ISISR);
				break;	/* _hoops_SHIR */
			case 'B':
				switch (name[14]) {
				case '\0':
					_hoops_RHCSR =
						_hoops_AHCSR (_hoops_PPPCC,
								"Helvetica-Bold",
								_hoops_ARICC, _hoops_ISISR);
					break;	/* _hoops_AGIR '\0' */
				case 'O':
					_hoops_RHCSR =
						_hoops_AHCSR (_hoops_IPPCC,
								"Helvetica-BoldOblique",
								_hoops_ARICC, _hoops_ISISR);
					break;	/* _hoops_AGIR '_hoops_RGGIR' */
				}
				break;	/* _hoops_AGIR '_hoops_IHAC' */
			}
			break;	/* _hoops_AGIR '-' */
		default:
			_hoops_RHCSR =
				_hoops_AHCSR (_hoops_APPCC, "Helvetica", _hoops_RRICC,
						_hoops_ISISR);
			break;	/* _hoops_SHIR */
		}
		break;		/* _hoops_AGIR '_hoops_CIPII' */

	case 'T':
		switch (name[6]) {

		case 'R':
			_hoops_RHCSR =
				_hoops_AHCSR (_hoops_AHPCC, "Times-Roman", _hoops_PPCSR,
						_hoops_ISISR);
			break;	/* _hoops_AGIR '_hoops_SAAAR' */

		case 'I':
			_hoops_RHCSR =
				_hoops_AHCSR (_hoops_HHPCC, "Times-Italic",
						_hoops_PRICC, _hoops_ISISR);
			break;	/* _hoops_AGIR '_hoops_SAAAR' */

		default:
			if (name[10] == '\0') {
				_hoops_RHCSR =
					_hoops_AHCSR (_hoops_PHPCC, "Times-Bold",
							_hoops_HRICC, _hoops_ISISR);
			}
			else {
				_hoops_RHCSR =
					_hoops_AHCSR (_hoops_IHPCC, "Times-BoldItalic",
							_hoops_IRICC, _hoops_ISISR);
			}
			break;	/* _hoops_SHIR */
		}
		break;		/* _hoops_AGIR '_hoops_SAAAR' */
	}

	if (!_hoops_RHCSR) {
		/* _hoops_CGP _hoops_SR _hoops_HGCR _hoops_ARI _hoops_HSAR _hoops_RH _hoops_CICA _hoops_AACCC _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_CRSH _hoops_CIAH. */
		char error[512];
		sprintf (error, "load_font in pdf_driver.c failed to find the font %s.", name);
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, error);
	}

	return ((void *) _hoops_RHCSR);
}


local void
_hoops_PACCC (Display_Context const *dc, Font_Instance alter * instance)
{
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	_hoops_PSISR *_hoops_RHCSR = (_hoops_PSISR *) instance->_hoops_GAASR;

	_hoops_AHCRI ("pdf_unload_font");

	UNREFERENCED (dc);

	if (state->_hoops_PRGGH)
		return;

	_hoops_PHCSR (_hoops_RHCSR);

	return;
}


local void
_hoops_HACCC (Net_Rendition const &nr,
	       Font_Instance const *specific,
	       Point const *where, int count, Karacter const *string, Vector const *scale)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	_hoops_IGCSR const &_hoops_HRCIR = nr->_hoops_SISI;

	_hoops_AHCRI ("pdf_draw_font");

	UNREFERENCED (scale);

	if (state->_hoops_PRGGH)
		return;

	if (_hoops_HRCIR->transform == FT_FULL) {
		if ((specific->_hoops_HRGGH || specific->_hoops_RRGGH)
		    && (specific->family->_hoops_RRCSR == _hoops_SISSP)) {

			dc->_hoops_PGCC.flags &= ~_hoops_HPPGH;
			(*specific->_hoops_SRCSR) (nr, specific, where, count, string, scale);
			dc->_hoops_PGCC.flags |= _hoops_HPPGH;
		}
		else {
			HD_Standard_Draw_Font (nr, specific, where, count, string, scale);
		}
		return;
	}

	switch (specific->family->_hoops_RRCSR) {

#ifndef DISABLE_DEFINED_FONTS
	case _hoops_ARCSR:
		specific->_hoops_SRCSR (nr, specific, where, count, string, scale);
		break;
#endif
#ifdef FREETYPE
	case _hoops_SISSP:
		{
			/* _hoops_AGGA _hoops_SGS _hoops_RH _hoops_HRCSR _hoops_SSCP _hoops_RPII _hoops_RRAI _hoops_IS _hoops_RH _hoops_GSPCC, _hoops_SR'_hoops_ASAR _hoops_HRPP _hoops_IS _hoops_ISPR _hoops_RH _hoops_HCISR _hoops_PIAP. */
			_hoops_ICICC (nr, _hoops_GIICC | _hoops_HCICC);

			_hoops_RIHCC (state->_hoops_PGPCC, where->x, where->y, _hoops_HRCIR->rotation,
					 _hoops_HRCIR->width_scale, count, (unsigned short *) string);
		} break;

#endif
	default:
		HD_Standard_Draw_Font (nr, specific, where, count, string, scale);
		break;
	}
	return;
}



#define _hoops_IACSR(x) (float)(1.0f/(x))

local void
_hoops_IACCC (Display_Context alter * dc)
{
	_hoops_CRICC alter *state = _hoops_HPICC (dc);

	_hoops_AHCRI ("pdf_find_basic_fonts");

	if (state->_hoops_PRGGH)
		return;

	HD_Record_Font_With_Encoding (dc, "Times-Roman", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.6759));
	HD_Record_Font_With_Encoding (dc, "Times-Italic", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.6720));
	HD_Record_Font_With_Encoding (dc, "Times-Bold", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.6809));
	HD_Record_Font_With_Encoding (dc, "Times-BoldItalic", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.6759));
	HD_Record_Font_With_Encoding (dc, "Helvetica", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.7290));
	HD_Record_Font_With_Encoding (dc, "Helvetica-Oblique", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.7290));
	HD_Record_Font_With_Encoding (dc, "Helvetica-Bold", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.7290));
	HD_Record_Font_With_Encoding (dc, "Helvetica-BoldOblique", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.7290));
	HD_Record_Font_With_Encoding (dc, "Courier", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.7290));
	HD_Record_Font_With_Encoding (dc, "Courier-Oblique", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.7290));
	HD_Record_Font_With_Encoding (dc, "Courier-Bold", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.7290));
	HD_Record_Font_With_Encoding (dc, "Courier-BoldOblique", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.7290));
	HD_Record_Font_With_Encoding (dc, "Symbol", "", _hoops_SACSR, 0.0f,
				      _hoops_IACSR (0.6729));

	HD_Mark_Font_As_Generic (dc, "Times-Roman", GFN_ROMAN);
	HD_Mark_Font_As_Generic (dc, "Helvetica", GFN_SANS_SERIF);
	HD_Mark_Font_As_Generic (dc, "Courier", GFN_TYPEWRITER);

	HD_Mark_Font_As_Transformable (dc, "Times-Roman", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Times-Italic", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Times-Bold", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Times-BoldItalic", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Helvetica", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Helvetica-Oblique", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Helvetica-Bold", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Helvetica-BoldOblique", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Courier", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Courier-Oblique", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Courier-Bold", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Courier-BoldOblique", _hoops_GPCSR);
	HD_Mark_Font_As_Transformable (dc, "Symbol", _hoops_GPCSR);

	return;
}


local void
_hoops_CACCC (Net_Rendition const &nr,
			   DC_Point const *start,
			   DC_Point const *end, int row_bytes, RGBAS32 const *_hoops_SACCC)
{
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	int _hoops_GPCCC, _hoops_RPCCC, _hoops_APCCC, _hoops_PPCCC;
	int _hoops_HPCCC, _hoops_IPCCC;
	int _hoops_CPCCC;
	int width, height;
	float left, right, bottom, top;
	struct _hoops_GSACC *data;
	int row, col;

	/* _hoops_GGI _hoops_IRS _hoops_RIS _hoops_IIGR _hoops_AIHSR _hoops_AHRH */

	_hoops_AHCRI ("pdf_draw_dc_rgb32_rasters");

	if (state->_hoops_PRGGH)
		return;

	_hoops_ICICC (nr, _hoops_GIICC);

	if (row_bytes == 0)
		row_bytes = (int) ((end->x - start->x + 1.0f) * (int) sizeof (RGBAS32));

	_hoops_HPCCC = _hoops_IAAA (0, (int) start->y - (int) _hoops_IHCR->_hoops_AGAA.top);
	_hoops_IPCCC = _hoops_IAAA (0, (int) _hoops_IHCR->_hoops_AGAA.left - (int) start->x);
	_hoops_CPCCC = _hoops_IAAA (0, row_bytes +
				  ((int) start->x - 1 -
				   (int) _hoops_IHCR->_hoops_AGAA.right) * (int) sizeof (RGBAS32));

	_hoops_GPCCC = (int) start->x + _hoops_IPCCC;
	_hoops_RPCCC = (int) start->y - _hoops_HPCCC;
	_hoops_APCCC = (int) end->x + _hoops_IPCCC;
	_hoops_PPCCC = (int) end->y - _hoops_HPCCC;

	height = _hoops_RPCCC - _hoops_PPCCC +1;
	width = _hoops_APCCC - _hoops_GPCCC +1;

	if (width * height <= 0)
		return;

	left = _hoops_GPCCC - 0.5f;
	right = _hoops_APCCC + 0.5f;
	bottom = _hoops_RPCCC + 0.5f;
	top = _hoops_PPCCC - 0.5f;

	/* _hoops_ACRAR _hoops_RH _hoops_AIIR _hoops_GAR _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_IGI _hoops_GGR _hoops_HAACC. */
	/* _hoops_RAH _hoops_SR _hoops_RRP _hoops_IS _hoops_GGSHR _hoops_PCCIR _hoops_PPR _hoops_RCSR? */
	POOL_ALLOC_ARRAY_CACHED (data, width * height, struct _hoops_GSACC, nr->_hoops_SRA->memory_pool);

		for (row = 0; row < height; ++row) {
			for (col = 0; col < width; ++col) {
				data[row * width + col].r = _hoops_SACCC[row * width + col].r;
				data[row * width + col].g = _hoops_SACCC[row * width + col].g;
				data[row * width + col].b = _hoops_SACCC[row * width + col].b;
			}
		}

	_hoops_AIHCC (state->_hoops_PGPCC,
			  left, right, top, bottom, width, height, sizeof(_hoops_GSACC), (unsigned char const *) data);
	FREE_ARRAY (data, width * height, struct _hoops_GSACC);

	return;
}



local void
_hoops_SPCCC (Net_Rendition const &nr, Int_Rectangle const *extent)
{
	_hoops_CGRA const &_hoops_SGRA = nr->_hoops_SAIR;
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_CRICC alter *state = _hoops_HPICC (dc);
	Image const *image = null;
	_hoops_RCR *_hoops_IICSR = null;
	_hoops_AIGH *rasters;
	_hoops_CPAIR _hoops_CICSR;

	_hoops_AHCRI ("pdf_draw_window");

	if (state->_hoops_PRGGH)
		return;

	if (_hoops_SGRA->_hoops_PGPH != null || _hoops_SGRA->_hoops_SICSR == null) {
		HD_Standard_Draw_Window (nr, extent);
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

	if ((_hoops_IICSR = HI_Activate_Texture ((_hoops_RCR alter *) _hoops_SGRA->_hoops_SICSR, &_hoops_CICSR, false)) != null) {
		image = _hoops_IICSR->image;
	}

	if(image == null){
		HD_Standard_Draw_Window (nr, extent);
		goto _hoops_RCCSR;
	}

	if (_hoops_IICSR == null || BIT (_hoops_IICSR->flags, _hoops_AIA)) {
		HD_Standard_Draw_Window (nr, extent);
		goto _hoops_RCCSR;
	}

	/* _hoops_HSCGR _hoops_GGSR _hoops_RH _hoops_AIIR _hoops_HSH... */
	rasters = *(_hoops_AIGH **) image->rasters;

	_hoops_AIHCC (state->_hoops_PGPCC,
			  extent->left, extent->right,
			  extent->bottom, extent->top,
			  image->width, image->height, 4, (unsigned char const *) rasters);

_hoops_RCCSR:
	if(_hoops_IICSR)
		_hoops_HPRH (_hoops_IICSR);
	return;
}


/************************************/


local void
_hoops_RSCSR (_hoops_APARR alter & _hoops_RRCI)
{
	_hoops_RRCI->start_device = _hoops_IPICC;
	_hoops_RRCI->get_physical_info = _hoops_RHICC;
	_hoops_RRCI->get_outer_window = _hoops_PHICC;
	_hoops_RRCI->get_current_info = _hoops_AHICC;
	_hoops_RRCI->init_picture = _hoops_CHICC;
	_hoops_RRCI->finish_picture = _hoops_SHICC;
	_hoops_RRCI->free_outer_window = _hoops_IHICC;
	_hoops_RRCI->stop_device = _hoops_CPICC;

	_hoops_RRCI->draw_3d_elliptical_arc = _hoops_ARCCC;
	_hoops_RRCI->draw_3d_ellipse = _hoops_RRCCC;
	_hoops_RRCI->_hoops_CCISR = _hoops_PRCCC;
	_hoops_RRCI->draw_dc_ellipse = _hoops_HRCCC;
	_hoops_RRCI->_hoops_SCISR = _hoops_IRCCC;
	_hoops_RRCI->draw_dc_colorized_face = _hoops_IGCCC;
	_hoops_RRCI->draw_dc_colorized_polytriangle = _hoops_SGCCC;
	_hoops_RRCI->draw_dc_face = _hoops_HGCCC;
	_hoops_RRCI->draw_dc_polydot = _hoops_CRCCC;
	_hoops_RRCI->draw_dc_polyline = _hoops_HSICC;
	_hoops_RRCI->draw_dc_polytriangle = _hoops_CGCCC;
	_hoops_RRCI->draw_dc_rectangle = _hoops_PGCCC;
	_hoops_RRCI->draw_dc_rgb32_rasters = _hoops_CACCC;
	_hoops_RRCI->draw_window = _hoops_SPCCC;

	_hoops_RRCI->_hoops_CACSR = _hoops_IACCC;
	_hoops_RRCI->_hoops_SRCSR = _hoops_HACCC;
	_hoops_RRCI->load_font = _hoops_RACCC;
	_hoops_RRCI->unload_font = _hoops_PACCC;

	_hoops_RRCI->draw_dc_text = _hoops_SRCCC;
	_hoops_RRCI->measure_char = _hoops_GACCC;

	return;
}



extern "C" bool HC_CDECL
HD_PDF_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI, 
	int						request, 
	void *					request_info)
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR);
}


_hoops_HSCSR (_hoops_RSCSR)
#endif /* _hoops_GHCCC */
