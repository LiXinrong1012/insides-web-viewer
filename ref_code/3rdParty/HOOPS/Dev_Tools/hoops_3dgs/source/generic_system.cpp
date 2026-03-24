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
 * $Id: obf_tmp.txt 1.20 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "filedata.h"
#include "hi_proto.h"
#include "hpserror.h"

#include <stdio.h>
#include <stdlib.h>



/*
 *	_hoops_CGP _hoops_RSIPR _hoops_RH _hoops_CIIA '_hoops_CHHR'/'_hoops_RGHR' _hoops_HCPA/_hoops_PAIHH _hoops_CCA
 *	_hoops_PCCP _hoops_IRPR _hoops_ICCIA _hoops_HAIHH _hoops_PSCR _hoops_PPSI _hoops_SPR _hoops_GPP _hoops_RH _hoops_RSGR _hoops_IIGR
 *	_hoops_RH '_hoops_CHHR'
 */

GLOBAL_FUNCTION void HI_Add_Path_Delimiter (
	_hoops_HCRPR alter	*_hoops_PSHAP,
	_hoops_HCRPR alter	*file) 
{
	char			*_hoops_CASCA, *_hoops_RRSAA;
	int				i;
	_hoops_HCRPR			newname;

	if (_hoops_PSHAP->length == 0) return;

	if (file->length == 0) return;

	if ((_hoops_PSHAP->text)[_hoops_PSHAP->length - 1] == PATH_DELIMITER ||
		*file->text == PATH_DELIMITER) return;

	if (PATH_DELIMITER_TWO != '\0') {
		if ((_hoops_PSHAP->text)[_hoops_PSHAP->length - 1] == PATH_DELIMITER_TWO ||
			*file->text == PATH_DELIMITER_TWO) return;
	}

	newname.length = _hoops_PSHAP->length+1;
	ALLOC_ARRAY (_hoops_CASCA, newname.length+1, char);
	newname.text = _hoops_CASCA;

	i = _hoops_PSHAP->length;
	_hoops_RRSAA = _hoops_PSHAP->text;

	do *_hoops_CASCA++ = *_hoops_RRSAA++;
	_hoops_RGGA (--i == 0);

	*_hoops_CASCA++ = PATH_DELIMITER;
	*_hoops_CASCA = '\0';

	_hoops_RGAIR (*_hoops_PSHAP);
	_hoops_PSHAP->length = newname.length;
	_hoops_PSHAP->text = newname.text;
}


/*
 * _hoops_AHGHR _hoops_RH _hoops_CIIA '_hoops_RSIRR', _hoops_RHAPA '_hoops_CHHR', '_hoops_RGHR', _hoops_PPR '_hoops_SAIHH'
 * _hoops_PAGA _hoops_SGS '_hoops_SAIHH' _hoops_CRRPR _hoops_GII _hoops_CGCPH _hoops_HAIHH (_hoops_PSHRR '.')
 */

GLOBAL_FUNCTION void HI_Parse_Filename (
	_hoops_HCRPR *name,
	_hoops_HCRPR *_hoops_PSHAP,
	_hoops_HCRPR *file,
	_hoops_HCRPR *_hoops_GPIHH) {
	int				i;
	char			*_hoops_ASAPR;
	char			*_hoops_RPIHH;
	char			*_hoops_AHSCA;

	_hoops_PSHAP->length = file->length = _hoops_GPIHH->length = 0;
	_hoops_RPIHH = name->text + name->length - 1;
	_hoops_ASAPR = _hoops_RPIHH + 1;

	do {
		--_hoops_ASAPR;

		if ((*_hoops_ASAPR == '.') && (_hoops_GPIHH->length == 0)) { 
			i = _hoops_GPIHH->length = _hoops_RPIHH - _hoops_ASAPR + 1;
			if (i != 0) {
				char	*_hoops_CSHPP = _hoops_ASAPR;
				ALLOC_ARRAY (_hoops_AHSCA, i+1, char);
				_hoops_GPIHH->text = _hoops_AHSCA;
				do *_hoops_AHSCA++ = *_hoops_CSHPP++; _hoops_RGGA (_hoops_CSHPP > _hoops_RPIHH);
				*_hoops_AHSCA = '\0';
				_hoops_RPIHH = _hoops_ASAPR - 1;
			}
		}

		if (*_hoops_ASAPR == PATH_DELIMITER || (*_hoops_ASAPR == PATH_DELIMITER_TWO && PATH_DELIMITER_TWO != '\0')) {
			char	*_hoops_CSHPP;
			_hoops_CSHPP = name->text;
			i = _hoops_PSHAP->length = _hoops_ASAPR - _hoops_CSHPP + 1;
			ALLOC_ARRAY (_hoops_AHSCA, i+1, char);
			_hoops_PSHAP->text = _hoops_AHSCA;
			do *_hoops_AHSCA++ = *_hoops_CSHPP++; _hoops_RGGA (--i == 0);
			*_hoops_AHSCA = '\0';
			++_hoops_ASAPR;
			break;
		}
	} _hoops_RGGA (_hoops_ASAPR == name->text);

	i = _hoops_RPIHH - _hoops_ASAPR + 1;
	if (i == 0) return;

	ALLOC_ARRAY (_hoops_AHSCA, i+1, char);
	file->text = _hoops_AHSCA;
	file->length = i;
	_hoops_RGGA (_hoops_ASAPR > _hoops_RPIHH) *_hoops_AHSCA++ = *_hoops_ASAPR++;
	*_hoops_AHSCA = '\0';

	return;
}


/*
 * _hoops_CGP _hoops_RH _hoops_AIRPR _hoops_GHARR _hoops_RHAP _hoops_HAR _hoops_GCGH _hoops_CSPP _hoops_RGGHR _hoops_PPR _hoops_RPP
 * _hoops_RH _hoops_RGHR '_hoops_RSIRR' _hoops_HICP, _hoops_CIPAA '_hoops_RSIRR' _hoops_RPPR _hoops_IS _hoops_IRHH _hoops_SCH _hoops_HSGS
 */
GLOBAL_FUNCTION void HI_Make_Unique_Filename (
	_hoops_HCRPR *name) {
	UNREFERENCED (name);

	/***** _hoops_ASAI _hoops_APIHH _hoops_PPIHH *****/
}


#ifdef UNIX_SYSTEM


#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


GLOBAL_FUNCTION void * HI_System_Alloc (size_t size)
{
	return malloc(size);
}

GLOBAL_FUNCTION void HI_System_Free (void *pntr)
{
	free(pntr);
}


//#_hoops_PPIP _hoops_AHIHH
#ifdef _hoops_PHIHH
#undef WIN32_LEAN_AND_MEAN
#define _hoops_HHIHH
#define _hoops_IHIHH 1
#include "dlmalloc.c"

GLOBAL_FUNCTION void HI_Set_System_Memory_Functions()
{
    HOOPS_WORLD->_hoops_RSSPP = _hoops_CHIHH;
    HOOPS_WORLD->_hoops_GSSPP = _hoops_SHIHH;
}

#else


GLOBAL_FUNCTION void HI_Set_System_Memory_Functions()
{
	HOOPS_WORLD->_hoops_RSSPP = free;
	HOOPS_WORLD->_hoops_GSSPP = malloc;
}

#endif

GLOBAL_FUNCTION void HI_System_Memory_Purge()
{
#ifdef _hoops_PHIHH
_hoops_GIIHH(0);
#endif
}


GLOBAL_FUNCTION void HI_Set_Thread_Name (int id, char const * name, bool _hoops_RIIHH) 
{
	UNREFERENCED(id);
	UNREFERENCED(name);
	UNREFERENCED(_hoops_RIIHH);
}

GLOBAL_FUNCTION void HI_Error_Exit (void) {
	exit(1);
}


GLOBAL_FUNCTION void HI_Normal_Exit (void) {
	exit(0);
}


/*
 * _hoops_AHGHR _hoops_IRS _hoops_RGHR _hoops_RCSSA _hoops_PPR _hoops_IRS _hoops_RGHR _hoops_CCH (_hoops_SSHHH _hoops_PAR _hoops_GGIHH)
 * _hoops_RGIHH _hoops_RH _hoops_RGHR _hoops_PPR _hoops_HRS _hoops_IRS "_hoops_PHIGR" _hoops_RGHR _hoops_RGHH (_hoops_SRPC *).
 * _hoops_CGP '_hoops_AGIHH' _hoops_HRGR _hoops_IHPR, _hoops_PSCR _hoops_SCH _hoops_HRGR _hoops_GPRS _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_RGHR _hoops_CSPP
 * (_hoops_PGIHH _hoops_IAHA).	 _hoops_HHPC, _hoops_GII _hoops_APRS _hoops_CSPP _hoops_CGH _hoops_SHH _hoops_PGHPR, _hoops_PAR
 * _hoops_HGIHH _hoops_IS _hoops_IRS _hoops_IGIHH _hoops_RGHR _hoops_SGS _hoops_RHAP _hoops_HAR _hoops_GGR _hoops_IIGR _hoops_ACAS _hoops_GGHC _hoops_IRS _hoops_CCAH
 * _hoops_CSPP _hoops_PHI.
 */
GLOBAL_FUNCTION bool HI_Open_File (
	_hoops_HCRPR alter *	name,
	int				_hoops_CCHHH,
	void alter **	_hoops_CRIPH,
	bool			_hoops_SCHHH,
	_hoops_HCRPR alter *	_hoops_GGHGA,
	_hoops_HCRPR alter *	_hoops_RGHGA) {
	char			buf[4096], *_hoops_ASAPR;
	int				f;
	int *			_hoops_CGIHH;

	UNREFERENCED (_hoops_SCHHH);

	HI_Copy_Chars_To_Name ("", _hoops_RGHGA);

	if (name->length == 0) {
		HI_Copy_Chars_To_Name ("Internal error: File name is blank at Open File", _hoops_GGHGA);
		return false;
	}

	switch (_hoops_CCHHH) {
		case FILE_For_Reading: {
			f = open (name->text, 0);

			if (f == -1) {
				_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf) - 1,
								  "Unable to open file '%s' for reading",
								  (void *)name->text);
				if (_hoops_ASAPR != null)
					*_hoops_ASAPR = '\0';
				else
					buf[0] = '\0';
				HI_Copy_Chars_To_Name (buf, _hoops_GGHGA);
				return false;
			}
		}	break;

		case FILE_For_Writing: {
			f = creat (name->text, 0666);

			if (f == -1) {
				_hoops_ASAPR = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf) - 1,
								  "Unable to open file '%s' for writing",
								  (void *)name->text);
				if (_hoops_ASAPR != null)
					*_hoops_ASAPR = '\0';
				else
					buf[0] = '\0';
				HI_Copy_Chars_To_Name (buf, _hoops_GGHGA);
				return false;
			}
		}	break;

		default:
			HI_Copy_Chars_To_Name ("Internal error - Illegal access mode at Open File", _hoops_GGHGA);
			return false;
	}

	ALLOC (_hoops_CGIHH, int);
	*_hoops_CGIHH = f;
	*_hoops_CRIPH = _hoops_CGIHH;
	return true;
}


/*
 * _hoops_SGIHH _hoops_RH _hoops_RGHR _hoops_PSHS _hoops_HPP '_hoops_GRIHH'.	 _hoops_GCAAA _hoops_RCPP _hoops_RPP _hoops_IIH _hoops_CSAP
 * _hoops_GII _hoops_RIHH.
 */
GLOBAL_FUNCTION bool HI_Close_File (
	void alter		*_hoops_CRIPH,
	_hoops_HCRPR alter	*_hoops_GGHGA,
	_hoops_HCRPR alter	*_hoops_RGHGA) {
	int				i;
	
	if (!_hoops_CRIPH) return false;
   
	i = *((int *)_hoops_CRIPH);

	UNREFERENCED (_hoops_RGHGA);

	FREE (_hoops_CRIPH, int);
	if (close (i) != -1)
		return true;
	HI_Copy_Chars_To_Name ("Error closing file", _hoops_GGHGA);
	return false;
}


/*
 * _hoops_RRIHH _hoops_GH _hoops_IS '_hoops_ARIHH' _hoops_CRGR '_hoops_SRHR' _hoops_GRP '_hoops_GRIHH' _hoops_GAR _hoops_RH _hoops_RGHR
 * _hoops_RGHH.	_hoops_GCAAA # _hoops_IIGR _hoops_GCSRR _hoops_IRIGR _hoops_GGR '_hoops_PRIHH'.
 * _hoops_HRIHH _hoops_HSAR '_hoops_ARIHH' _hoops_GHCA _hoops_SHH _hoops_IRIGR _hoops_HIH _hoops_RPP '_hoops_PRIHH' _hoops_HRGR 0, _hoops_RSGR _hoops_IIGR
 * _hoops_RGHR _hoops_HRGR _hoops_SHHA.
 * _hoops_RRPP _hoops_GHCA _hoops_SHH _hoops_IRIHH.  _hoops_CGP _hoops_RH _hoops_SRHR _hoops_HRGR _hoops_HAR _hoops_GAPR _hoops_APIP, _hoops_RH _hoops_API
 * _hoops_HRS '_hoops_IHPR' _hoops_HIH '_hoops_PRIHH' _hoops_HRGR '-1'.
 */
GLOBAL_FUNCTION bool HI_Read_File_Buffer (
	void alter				*_hoops_CRIPH,
	char alter				*buffer,
	int alter				*_hoops_GSHHH,
	int						_hoops_RSHHH,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	int						f = *((int *)_hoops_CRIPH);

	UNREFERENCED (_hoops_RGHGA);

	*_hoops_GSHHH = read (f, buffer, _hoops_RSHHH);

	if (*_hoops_GSHHH != -1)
		return true;
	else {
		HI_Copy_Chars_To_Name ("I/O Error occured while reading file buffer",
				_hoops_GGHGA);
		return false;
	}
}


/*
 * _hoops_CRIHH '_hoops_GCSRR' _hoops_HII '_hoops_SRHR' _hoops_GRP '_hoops_GRIHH' _hoops_GAR _hoops_RH _hoops_RGHR _hoops_RGHH.
 * _hoops_IISH _hoops_GHCA _hoops_SHH _hoops_IRIHH.
 */
GLOBAL_FUNCTION bool HI_Write_File_Buffer (
	void alter				*_hoops_CRIPH,
	char const				*buffer,
	int						_hoops_SHGGR,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	int				f = *((int *)_hoops_CRIPH);

	UNREFERENCED (_hoops_RGHGA);

	if (_hoops_SHGGR == write (f, (void *)buffer, _hoops_SHGGR))
		return true;
	else {
		HI_Copy_Chars_To_Name ("I/O Error occured while writing file buffer",
				_hoops_GGHGA);
		return false;
	}
}


/*
 * _hoops_SRIHH _hoops_SGS _hoops_GII _hoops_PSCA _hoops_IHGS _hoops_IRIGR _hoops_CHR _hoops_IHIR _hoops_PPR _hoops_GII _hoops_IHGS
 * _hoops_PHPH _hoops_CHR _hoops_RHPA (_hoops_IH '_hoops_GRIHH')
 * _hoops_HPSHR _hoops_IRS _hoops_IRIGR _hoops_CAIH, _hoops_RPP _hoops_GCSRR _hoops_HRGR _hoops_GIIA _hoops_GAR -1, _hoops_RH _hoops_PGHC '_hoops_IRIGR'
 * _hoops_CAIH _hoops_CSAP _hoops_GAIHH _hoops_PPR _hoops_RH _hoops_SRHR _hoops_CSAP _hoops_APIP _hoops_HPGR _hoops_SGS _hoops_GHIR.	 _hoops_HHPC,
 * '_hoops_GCSRR' _hoops_HRS _hoops_RH _hoops_PHI _hoops_IIGR _hoops_GCSRR _hoops_IRIGR.
 * _hoops_IPCP _hoops_API _hoops_GGR _hoops_RGR _hoops_RPHRA _hoops_CHR _hoops_HGSAR _hoops_IH _hoops_ASRAH _hoops_IHGC _hoops_IIGR _hoops_GII
 * _hoops_PIH _hoops_SIGR _hoops_GAPA _hoops_IRIGR/_hoops_GGI _hoops_PPR _hoops_CAPRH _hoops_HCPH.	'_hoops_GRIHH' _hoops_PAH _hoops_SHH
 * _hoops_IRS _hoops_CRS _hoops_IS _hoops_IRS _hoops_HRPR _hoops_PGAP _hoops_ICGI _hoops_GII _hoops_HAHH _hoops_HPHS,
 * _hoops_PSPP _hoops_RHSP _hoops_RH '_hoops_IGS' _hoops_AASA.
 */
GLOBAL_FUNCTION bool HI_Synch_File_Buffer (
	void alter				*_hoops_CRIPH,
	int alter				*_hoops_SHGGR,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {

	UNREFERENCED (_hoops_CRIPH);
	UNREFERENCED (_hoops_GGHGA);
	UNREFERENCED (_hoops_RGHGA);

	*_hoops_SHGGR = -1;
	return true;
}



#define _hoops_AIIHH 1024
#define _hoops_PIIHH 1024

typedef struct _hoops_HIIHH {
	int			_hoops_IIIHH;
	int			_hoops_CIIHH;
	DIR			*_hoops_CCSAR;
	_hoops_HCRPR		name;
	_hoops_HCRPR		filter;
} _hoops_SIIHH;


/*
 * _hoops_GCIHH _hoops_RH _hoops_CHHR "_hoops_RSIRR" _hoops_PPR _hoops_ISHCR _hoops_RRGSP _hoops_GGR _hoops_HCR
 * _hoops_RH _hoops_AIRP _hoops_SGS _hoops_PSSP _hoops_RH _hoops_HSGP _hoops_GGR "_hoops_RGRR".	"_hoops_RCIHH"
 * _hoops_PPR "_hoops_ACIHH" _hoops_GASAR _hoops_GGSIA _hoops_RH _hoops_GIPHR _hoops_IS _hoops_SAGHR
 * _hoops_RGHR _hoops_AIRC. _hoops_PCIHH _hoops_GGR "_hoops_HCIHH", _hoops_PGAP _hoops_ICGI _hoops_IRS _hoops_CRS
 * _hoops_IS _hoops_RHSAR _hoops_SIHC. _hoops_CGP _hoops_HCR _hoops_IAGA _hoops_PRAR, _hoops_IHPR _hoops_HRGR _hoops_GIIA. _hoops_CGP
 * _hoops_PA _hoops_IAGA _hoops_RHPH, _hoops_RCPP _hoops_HRGR _hoops_GIIA _hoops_PPR _hoops_RH _hoops_PSHHH _hoops_PPR
 * _hoops_GCAS _hoops_HSHHH _hoops_RHIPP _hoops_CHR _hoops_PIISR _hoops_GGR _hoops_CCA _hoops_ICIHH _hoops_GAR
 * _hoops_IS _hoops_PCPA _hoops_CCIHH _hoops_RHPH. _hoops_AGAH _hoops_RAIA _hoops_SCIHH _hoops_CGPR _hoops_HCHAR
 * _hoops_IH _hoops_HRCSR _hoops_GSIHH, _hoops_IAS._hoops_ISHI. _hoops_RSIHH _hoops_PPR _hoops_HRCSR _hoops_ASIHH.
 */
GLOBAL_FUNCTION bool HI_Open_Directory (
	_hoops_HCRPR alter	*name,
	_hoops_HCRPR const	*filter,
	int				_hoops_IIIHH,
	int				_hoops_CIIHH,
	void alter		**_hoops_PSIHH,
	_hoops_HCRPR alter	*_hoops_GGHGA,
	_hoops_HCRPR alter	*_hoops_RGHGA) {
	DIR				*_hoops_CCSAR;
	char			_hoops_HSIHH[_hoops_AIIHH];
	_hoops_SIIHH	*_hoops_HIIHH;
	char			buf1[MAX_ERRMSG], *_hoops_ISIHH;
	char const		*_hoops_CSIHH;

	if (name->length >= _hoops_GGAPR (_hoops_HSIHH)) {
		_hoops_ISIHH = HI_Sprintf1 (buf1, buf1+_hoops_GGAPR(buf1) - 1,
						   "Unable to open directory '%n' because",
						   (void *)name);
		if (_hoops_ISIHH != null)
			*_hoops_ISIHH = '\0';
		else
			buf1[0] = '\0';

		*_hoops_PSIHH = null;
		HI_Copy_Chars_To_Name (buf1, _hoops_GGHGA);
		HI_Copy_Chars_To_Name ("the name is too long.", _hoops_RGHGA);
		return false;
	}

	HI_Copy_Name_To_Chars (name, _hoops_HSIHH);

	if ((_hoops_CCSAR = opendir (_hoops_HSIHH)) != null) {
		ALLOC (_hoops_HIIHH, _hoops_SIIHH);

		_hoops_HIIHH->_hoops_IIIHH = _hoops_IIIHH;
		_hoops_HIIHH->_hoops_CIIHH = _hoops_CIIHH;
		_hoops_HIIHH->_hoops_CCSAR = _hoops_CCSAR;
		HI_Copy_Name (name, &_hoops_HIIHH->name);
		HI_Copy_Name (filter, &_hoops_HIIHH->filter);

		*_hoops_PSIHH = (void *)_hoops_HIIHH;
		HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
		HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
		return true;
	}
	else {
		switch (errno) {
			case ENOTDIR:
				_hoops_CSIHH = "a component of the filename is not a directory.";
				break;

			case EACCES:
				_hoops_CSIHH = "a component of the filename denies search permission.";
				break;

			case ENAMETOOLONG:
				_hoops_CSIHH = "the length of the filename argument exceeds {PATH_MAX}.";
				break;

			case ENOENT:
				_hoops_CSIHH = "the named directory does not exist.";
				break;

			case EMFILE:
				_hoops_CSIHH = "the maximum number of file descriptors are currently open.";
				break;

			case EFAULT:
				_hoops_CSIHH = "the filename points outside the allocated address space.";
				break;

			case EAGAIN:
				_hoops_CSIHH = "a call to malloc failed.";
				break;

			case ENOMEM:
				_hoops_CSIHH = "a call to malloc failed.";
				break;

			default:
				_hoops_CSIHH = "an unknown error occurred.";
				break;
		}

		_hoops_ISIHH = HI_Sprintf1 (buf1, buf1+_hoops_GGAPR(buf1) - 1,
						   "Unable to open directory '%n' because",
						   (void *)name);
		if (_hoops_ISIHH != null)
			*_hoops_ISIHH = '\0';
		else
			buf1[0] = '\0';

		*_hoops_PSIHH = null;
		HI_Copy_Chars_To_Name (buf1, _hoops_GGHGA);
		HI_Copy_Chars_To_Name (_hoops_CSIHH, _hoops_RGHGA);
		return false;
	}
}


/*
 * _hoops_SGIHH _hoops_RH _hoops_CHHR _hoops_GRPAA _hoops_RHSAR _hoops_SIHC _hoops_HRGR _hoops_SSIHH _hoops_IS _hoops_HPP _hoops_HCIHH.
 * _hoops_GGCHH _hoops_RH _hoops_RHSAR _hoops_SIHC. _hoops_GCAAA _hoops_IHPR _hoops_RPP _hoops_HCR _hoops_IAGA _hoops_PRAR _hoops_PPR
 * _hoops_RCPP (_hoops_CCA _hoops_PSHHH _hoops_PPR _hoops_GCAS _hoops_HSHHH _hoops_IIAAR
 * _hoops_ICIHH _hoops_GAR _hoops_IS _hoops_PCPA _hoops_CCIHH _hoops_RHPH) _hoops_IAII.
 */
GLOBAL_FUNCTION bool HI_Close_Directory (
	void alter				*_hoops_PSIHH,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	_hoops_SIIHH alter	*_hoops_HIIHH = (_hoops_SIIHH *)_hoops_PSIHH;
	char					buf1[MAX_ERRMSG], *_hoops_ISIHH;

	if (_hoops_HIIHH == (_hoops_SIIHH *)null) {
		/* _hoops_ISAP _hoops_IS _hoops_AA _hoops_CR _hoops_IGS _hoops_SRSH */
		HI_Copy_Chars_To_Name ("no need to close", _hoops_GGHGA);
		HI_Copy_Chars_To_Name ("directory not open", _hoops_RGHGA);
		return false;
	}
	else if (closedir (_hoops_HIIHH->_hoops_CCSAR) != 0) {
		/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_CPS _hoops_PPR _hoops_RGCHH _hoops_CIS _hoops_IIGR _hoops_RIHH */
		_hoops_ISIHH = HI_Sprintf1 (buf1, buf1+_hoops_GGAPR(buf1) - 1,
						   "Unable to close directory '%n' because",
						   (void *)&_hoops_HIIHH->name);
		if (_hoops_ISIHH != null)
			*_hoops_ISIHH = '\0';
		else
			buf1[0] = '\0';
		HI_Copy_Chars_To_Name (buf1, _hoops_GGHGA);

		if (errno == EBADF)
			HI_Copy_Chars_To_Name ("the file descriptor is no longer valid.",
								   _hoops_RGHGA);
		else
			HI_Copy_Chars_To_Name ("an unknown error occurred.", _hoops_RGHGA);

		_hoops_RGAIR (_hoops_HIIHH->filter);
		_hoops_RGAIR (_hoops_HIIHH->name);
		FREE (_hoops_HIIHH, _hoops_SIIHH);
		return false;
	}
	else {
		/* _hoops_GSSR _hoops_GGGR _hoops_IIGR _hoops_PCCP _hoops_IGS _hoops_CHHR */
		_hoops_RGAIR (_hoops_HIIHH->filter);
		_hoops_RGAIR (_hoops_HIIHH->name);
		FREE (_hoops_HIIHH, _hoops_SIIHH);
		HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
		HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
		return true;
	}
}


/*
 * _hoops_AGCHH _hoops_RH _hoops_SPS _hoops_RARP _hoops_GGR _hoops_RH _hoops_CHHR _hoops_SGS _hoops_SPASR _hoops_RH _hoops_AAGPR
 * _hoops_RAGA _hoops_RHSP _hoops_SCIHH.	_hoops_CGP _hoops_IIH _hoops_CHR _hoops_PSP _hoops_RRI _hoops_HGPP _hoops_AIRP, _hoops_SCH
 * _hoops_HRS "_hoops_IHPR" (_hoops_IR), _hoops_HIH "_hoops_CAIAH" _hoops_GRS _hoops_SHH _hoops_HS _hoops_IRS _hoops_SPCC _hoops_IIGR 0.
 * _hoops_HHIGR _hoops_HRGR _hoops_RH _hoops_CIS'_hoops_GRI _hoops_CSSAR _hoops_IS _hoops_PCARA _hoops_CAIAH _hoops_RAS _hoops_RCPH
 * _hoops_RGR _hoops_PCPH.
 */
GLOBAL_FUNCTION bool HI_Read_Directory (
	void alter				*_hoops_PSIHH,
	_hoops_HCRPR alter			*filename,
	_hoops_HCRPR alter			*_hoops_GGHGA,
	_hoops_HCRPR alter			*_hoops_RGHGA) {
	_hoops_SIIHH alter	*_hoops_HIIHH = (_hoops_SIIHH *)_hoops_PSIHH;
	struct dirent			*entry;
	char					buf1[MAX_ERRMSG], *_hoops_ISIHH;
	char const				*_hoops_CSIHH;

	if (_hoops_HIIHH == (_hoops_SIIHH *)null) {
		/* _hoops_PAH'_hoops_RA _hoops_AA _hoops_PA _hoops_CR _hoops_IGS _hoops_SRSH */
		HI_Copy_Chars_To_Name ("", filename);
		HI_Copy_Chars_To_Name ("cannot read", _hoops_GGHGA);
		HI_Copy_Chars_To_Name ("directory not open", _hoops_RGHGA);
		return false;
	}

	entry = null;
	filename->length = 0;
	_hoops_RGGA (entry != null) {
		if ((entry = readdir (_hoops_HIIHH->_hoops_CCSAR)) != null) {
			if (_hoops_HIIHH->filter.length != 0) {
				char	_hoops_PGCHH[256];

				HI_Copy_Name_To_Chars (&_hoops_HIIHH->filter, _hoops_PGCHH);
				if (!HI_Wild_Equal_Strings (entry->d_name, _hoops_PGCHH)) {
					entry = null;
					continue;
				}
			}

			/*
			 * _hoops_HGCHH _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_IRS _hoops_IGCHH _hoops_HPGR _hoops_HCR.
			 * _hoops_CGCHH _hoops_HRGR _hoops_PCCP _hoops_IHPH _hoops_CAIH _hoops_SR'_hoops_GHGP _hoops_PII _hoops_IS _hoops_SIPIP.
			 */
			if (_hoops_HIIHH->_hoops_IIIHH != 0) {
				char			path[_hoops_PIIHH];
				struct stat		status;
				int				mode = 0;

				if ((_hoops_HIIHH->name.length + strlen (entry->d_name) + 1) >
					_hoops_GGAPR (path)) {
					/* _hoops_SIGS _hoops_SGCHH */
					entry = null;
					continue;
				}

				HI_Copy_Name_To_Chars (&_hoops_HIIHH->name, path);
				if (path[_hoops_HIIHH->name.length-1] != '/') {
					path[_hoops_HIIHH->name.length] = '/';
					_hoops_AAHR (entry->d_name,
									&path[_hoops_HIIHH->name.length+1]);
				}
				else
					_hoops_AAHR (entry->d_name,
									&path[_hoops_HIIHH->name.length]);

				if (stat (path, &status) == 0) {
					if (BIT (status.st_mode, 0400))
						mode |= DIR_Select_Readable;
					if (BIT (status.st_mode, 0200))
						mode |= DIR_Select_Writeable;
					if (BIT (status.st_mode, 0100))
						mode |= DIR_Select_Executable;
					if (S_ISREG (status.st_mode))
						mode |= DIR_Select_File;
					if (S_ISDIR (status.st_mode))
						mode |= DIR_Select_Directory;

					if ((mode & _hoops_HIIHH->_hoops_IIIHH) !=
						(_hoops_HIIHH->_hoops_CIIHH & _hoops_HIIHH->_hoops_IIIHH)) {
						entry = null;
						continue;
					}
				}
				else {
					entry = null;
					continue;
				}
			}
		}
		else {
			switch (errno) {
			  case EBADF:
				_hoops_CSIHH = "the file descriptor is no longer valid.";
				break;

			  case ENOENT:
				/*
				 * _hoops_RRGI _hoops_GRCHH _hoops_HPGR _hoops_CHGC, _hoops_RGR _hoops_HRGR _hoops_HAR _hoops_PCCP _hoops_RIHH _hoops_RIR _hoops_HCPPH, _hoops_CR
				 * _hoops_SCH _hoops_HRGR _hoops_RH _hoops_GHPP _hoops_RRGR _hoops_RAGA _hoops_CGPR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_CHHR
				 * _hoops_HRGR _hoops_GCSPR
				 _hoops_RRCHH = "_hoops_RH _hoops_SCGR _hoops_RGHR _hoops_CRS _hoops_IH _hoops_RH _hoops_CHHR _hoops_HRGR _hoops_HAR _hoops_GAAPH _hoops_HPGR _hoops_IRS _hoops_APIP _hoops_RARP.";
				 */
				return true;
				break;

			  default:
				return true;
				break;
			}

			_hoops_ISIHH = HI_Sprintf1 (buf1, buf1+_hoops_GGAPR(buf1) - 1,
							   "Unable to read directory '%n' because",
							   (void *)&_hoops_HIIHH->name);
			if (_hoops_ISIHH != null)
				*_hoops_ISIHH = '\0';
			else
				buf1[0] = '\0';

			HI_Copy_Chars_To_Name ("", filename);
			HI_Copy_Chars_To_Name (buf1, _hoops_GGHGA);
			HI_Copy_Chars_To_Name (_hoops_CSIHH, _hoops_RGHGA);
			return false;
		}
	}

	HI_Copy_Chars_To_Name (entry->d_name, filename);
	HI_Copy_Chars_To_Name ("", _hoops_GGHGA);
	HI_Copy_Chars_To_Name ("", _hoops_RGHGA);
	return true;
}


HC_INTERFACE void HC_CDECL HC_Report_Error (
	int					category,
	int					specific,
	int					severity,
	int					msgc,
	char const * const	*msgv,
	int					_hoops_HRSAH,
	char const * const	*_hoops_PRSAH) 
{
	local		char const * const	type[4] = {
										"Informational message",
										"Warning",
										"Error",
										"Fatal error"};

	if (_hoops_HRSAH) {
		_hoops_PRSAH += _hoops_HRSAH;

		fprintf (stderr, "\n\n%s (%d/%d) from HOOPS routine '%s' -\n",
			 	type [severity], category, specific, *--_hoops_PRSAH);

		_hoops_RGGA (--_hoops_HRSAH == 0)
			fprintf (stderr, "	  which was called from '%s' -\n", *--_hoops_PRSAH);
	} else {
		fprintf (stderr, "\n\n%s (%d/%d) from unknown HOOPS routine -\n",
			type [severity], category, specific);
	}

	if (msgc > 0) {
		fprintf (stderr, "\n");
		do fprintf (stderr, "	 %s\n", *msgv++);
		_hoops_RGGA (--msgc == 0);
	}
	fprintf (stderr, "\n");
	fflush (stderr);
}

#if !defined(AIX_SYSTEM) && !defined(OSX_SYSTEM)

GLOBAL_FUNCTION bool HI_Show_Environment (
	char const		*which,
	_hoops_HCRPR			*result) {

	if ((which = getenv (which)) == null)
		return false;
	else {
		HI_Copy_Chars_To_Name (which, result);
		return true;
	}
}
#endif /* !_hoops_PAPR(_hoops_ICAPR) && !_hoops_PAPR(_hoops_ARCHH) */


HC_INTERFACE void HC_CDECL HC_Record_Profile_Source (
	char const *		section,
	char const *		filename) {

	UNREFERENCED (section);
	UNREFERENCED (filename);

	_hoops_PAPPR context("Record_Profile_Source (MSW specific)");

	HE_WARNING (HEC_MISC, HES_GENERAL_ERROR, "This routine is necessary only under Microsoft Windows");
}

HC_INTERFACE void HC_CDECL HC_Record_Instance_Handle (
	void alter *	_hoops_PRCHH) 
{
	UNREFERENCED (_hoops_PRCHH);

	_hoops_PAPPR context("Record_Instance_Handle (MSW specific)");

	HE_WARNING (HEC_MISC, HES_GENERAL_ERROR,
		"This routine is necessary only under Microsoft Windows");
}


#endif /* _hoops_HRCHH */




