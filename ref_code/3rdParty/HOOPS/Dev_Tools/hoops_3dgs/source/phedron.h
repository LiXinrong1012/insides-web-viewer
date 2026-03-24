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
 * $Id: obf_tmp.txt 1.219.2.1 2011-01-25 07:43:08 heppe Exp $
 */

#ifndef _hoops_RCCCC

#ifndef _hoops_GRAGP
#include "database.h"
#endif

Begin_HOOPS_Namespace

/*
 * _hoops_ACCCC _hoops_CHR _hoops_SAHGA _hoops_IRS _hoops_IGRH _hoops_RRAR _hoops_HSAR _hoops_AHHA _hoops_PPR _hoops_CCGI,
 * _hoops_PGGA _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_SAPIA _hoops_IS _hoops_IGGHA _hoops_PII-_hoops_SHIC _hoops_SAIA _hoops_GIRP.
 * _hoops_HGI _hoops_GSH _hoops_RH _hoops_PCCCC _hoops_PPR _hoops_RH _hoops_CIGR _hoops_CAPP.
 */
typedef unsigned int Local_Vertex_Flags;
#define _hoops_PHIAA				(Local_Vertex_Flags)0x00000001
#define _hoops_HHIAA				(Local_Vertex_Flags)0x00000002
#define _hoops_CIICA			(_hoops_PHIAA | _hoops_HHIAA)

#define _hoops_GCICA					(Local_Vertex_Flags)0x00000004
#define _hoops_SIICA					(Local_Vertex_Flags)0x00000008


#define _hoops_HCRRA		(Local_Vertex_Flags)0x00000010
#define _hoops_SIRRA		(Local_Vertex_Flags)0x00000020
#define _hoops_CCRRA			(Local_Vertex_Flags)0x00000040
#define _hoops_APPRA				(_hoops_HCRRA | _hoops_SIRRA | _hoops_CCRRA)


#define _hoops_HCCCC					(_hoops_APPRA | _hoops_CIICA | \
											 _hoops_GCICA | _hoops_SIICA)


#define _hoops_PPHPR		(Local_Vertex_Flags)0x00000100
#define _hoops_RPHPR		(Local_Vertex_Flags)0x00000200
#define _hoops_PPPRA				(_hoops_PPHPR | _hoops_RPHPR)

#define _hoops_AARHR		(Local_Vertex_Flags)0x00000400
#define _hoops_HARHR		(Local_Vertex_Flags)0x00000800
#define _hoops_HPPRA				(_hoops_AARHR | _hoops_HARHR)


#define _hoops_ARSII		(_hoops_HCRRA | _hoops_PPHPR | _hoops_AARHR)
#define _hoops_GGSII	(_hoops_SIRRA | _hoops_RPHPR | _hoops_HARHR)
#define _hoops_ICCCC		(_hoops_CCRRA)
#define _hoops_CPPRA				(_hoops_APPRA | _hoops_PPPRA | _hoops_HPPRA)


#define LVA_EXPLICIT_NORMAL					(Local_Vertex_Flags)0x00001000
#define _hoops_ASAPA				(Local_Vertex_Flags)0x00002000
#define _hoops_CCCCC				(Local_Vertex_Flags)0x00004000

#define _hoops_SACCP				(Local_Vertex_Flags)0x00010000
#define _hoops_RPCCP							(Local_Vertex_Flags)0x00020000

#define _hoops_SCCCC			(Local_Vertex_Flags)0x00100000
#define _hoops_CICII			(Local_Vertex_Flags)0x00200000
#define _hoops_GSCCC		(Local_Vertex_Flags)0x00400000
#define _hoops_RSCCC			(Local_Vertex_Flags)0x01000000
#define _hoops_ASCCC			(Local_Vertex_Flags)0x02000000
#define _hoops_PSCCC		(Local_Vertex_Flags)0x04000000

struct _hoops_PSGHR {
	float					size;
	_hoops_GASC					glyph;
	unsigned char			glyph_symbol;
	Local_Vertex_Flags		flags;
};

struct _hoops_RPHIR {
	_hoops_RPHIR *			next;
	_hoops_PHASP			_hoops_HSAI;
	_hoops_HCRPR					name;
	Integer32				key;
	unsigned char			id;
};

struct _hoops_CPHIR {
	int						face;			/* _hoops_GPP _hoops_SRS _hoops_RARP _hoops_GACC _hoops_IGI _hoops_GAR _hoops_RPR */
	int						vertex;			/* _hoops_GPP _hoops_SRS _hoops_RARP _hoops_GACC _hoops_IGI _hoops_GAR '_hoops_HSCCC' _hoops_RPR */
};


struct Local_Vertex_Attributes {
	/* _hoops_PGII _hoops_SIRGR _hoops_IIGR _hoops_IGIR = _hoops_RSHS + _hoops_ISCCC, _hoops_AHSAR _hoops_SRRSA _hoops_HIIA */

	Local_Vertex_Flags *	flags;
	Local_Vertex_Flags		_hoops_SGRHR;
	_hoops_CPHIR **		_hoops_RCIHR;	/* _hoops_HSP-_hoops_GPHA _hoops_CSCCC */
	int *					_hoops_RHHIR;

	RGB *					_hoops_PAHIR;	/* _hoops_GPIA _hoops_PSHA _hoops_HPP _hoops_PIRA */
	RGB *					ecolors;	/* _hoops_ISHA _hoops_PSHA _hoops_HPP _hoops_PIRA */
	RGB *					fcolors;	/* _hoops_HSP _hoops_PSHA _hoops_HPP _hoops_PIRA */
	RGBAS32 *				_hoops_IAHIR;		/* _hoops_GPIA _hoops_PSHA _hoops_HPP _hoops_PIRAI */
	_hoops_ACGHR *		_hoops_HAHIR; 	/* _hoops_GPIA _hoops_PSHA _hoops_HPP _hoops_SIGRA */
	_hoops_ACGHR *		_hoops_HGHIR; 	/* _hoops_ISHA _hoops_PSHA _hoops_HPP _hoops_SIGRA */
	_hoops_ACGHR *		_hoops_IGHIR; 	/* _hoops_HSP _hoops_PSHA _hoops_HPP _hoops_SIGRA */
	float *					_hoops_CAHIR;
	unsigned char *			_hoops_SAHIR;
	_hoops_RPHIR *			_hoops_GPHIR;
	Vector *				normals;

	_hoops_RSSH *				params;
	Integer32				param_width;
	_hoops_RSSH *				_hoops_IPHIR;
	_hoops_RSSH *				_hoops_PPHIR;
	Integer32				_hoops_HPHIR;
	_hoops_SSIC			_hoops_SSCCC;

	int						_hoops_ICRRA;
	int						_hoops_PCRRA;
	int						_hoops_HIRRA;
	int						_hoops_SCHPR;
	int						_hoops_CCHPR;
	int						_hoops_RCRHR;
	int						_hoops_SIRHR;
	int						_hoops_CPIAA;
	int						_hoops_SIIPR;
	int						_hoops_SCHHC;
	int						_hoops_AHIIC;
	int						_hoops_RSAPA;
	int						explicit_normal_count;
	int						_hoops_CACCP;

	Local_Vertex_Flags alter *	_hoops_CHHPR (int index = 0) alter {
		if (flags)
			return &flags[index];
		else
			return &_hoops_SGRHR;
	}
	Local_Vertex_Flags const *	_hoops_CHHPR (int index = 0) const {
		if (flags)
			return &flags[index];
		else
			return &_hoops_SGRHR;
	}

	bool lvf_uniform (int point_count) {
		if (_hoops_CPIAA != 0 && _hoops_CPIAA != point_count)
			return false;
		if (_hoops_SIIPR != 0 && _hoops_SIIPR != point_count)
			return false;
		if (_hoops_ICRRA != 0 && _hoops_ICRRA != point_count)
			return false;
		if (_hoops_PCRRA != 0 && _hoops_PCRRA != point_count)
			return false;
		if (_hoops_HIRRA != 0 && _hoops_HIRRA != point_count)
			return false;
		if (_hoops_SCHPR != 0 && _hoops_SCHPR != point_count)
			return false;
		if (_hoops_CCHPR != 0 && _hoops_CCHPR != point_count)
			return false;
		if (_hoops_RCRHR != 0 && _hoops_RCRHR != point_count)
			return false;
		if (_hoops_SIRHR != 0 && _hoops_SIRHR != point_count)
			return false;
		if (_hoops_SCHHC != 0 && _hoops_SCHHC != point_count)
			return false;
		if (_hoops_AHIIC != 0 && _hoops_AHIIC != point_count)
			return false;
		if (_hoops_RSAPA != 0 && _hoops_RSAPA != point_count)
			return false;
		if (explicit_normal_count != 0 && explicit_normal_count != point_count)
			return false;
		if (_hoops_CACCP != 0 && _hoops_CACCP != point_count)
			return false;

		return true;
	}
};

#define _hoops_GRRHR(va)	ZERO_STRUCT(&(va), _hoops_PSGHR)

#define COPY_ONE_VERTEX_ATTRIBUTES(_hoops_GGSCC, _hoops_RGSCC) do {	\
			(_hoops_RGSCC).size = (_hoops_GGSCC).size;					\
			(_hoops_RGSCC).glyph = (_hoops_GGSCC).glyph;				\
			(_hoops_RGSCC).glyph_symbol = (_hoops_GGSCC).glyph_symbol;	\
			(_hoops_RGSCC).flags = (_hoops_GGSCC).flags;				\
		} while (0)

#define _hoops_ARRHR(_hoops_AGSCC, index, va) do {				\
			(va).flags = *((_hoops_AGSCC)->_hoops_CHHPR(index)) & _hoops_HCCCC;	\
			if ((_hoops_AGSCC)->_hoops_CAHIR != null)								\
				(va).size = (_hoops_AGSCC)->_hoops_CAHIR[index];					\
			if ((_hoops_AGSCC)->_hoops_SAHIR != null)								\
				(va).glyph_symbol = (_hoops_AGSCC)->_hoops_SAHIR[index];			\
		} while (0)

#define _hoops_PRRHR(_hoops_AGSCC, index, va)										\
		(((va).flags & _hoops_HCCCC) == (*((_hoops_AGSCC)->_hoops_CHHPR(index)) & _hoops_HCCCC) &&	\
		 ((_hoops_AGSCC)->_hoops_CAHIR == null || (va).size == (_hoops_AGSCC)->_hoops_CAHIR[index]) &&							\
		 ((_hoops_AGSCC)->_hoops_SAHIR == null ||	(va).glyph_symbol == (_hoops_AGSCC)->_hoops_SAHIR[index]))

#define _hoops_HSGHR(_hoops_PGSCC, _hoops_HGSCC)														\
		(((_hoops_PGSCC).flags & _hoops_HCCCC) == ((_hoops_HGSCC).flags & _hoops_HCCCC) &&				\
		 (!BIT ((_hoops_PGSCC).flags, _hoops_GCICA) || (_hoops_PGSCC).size == (_hoops_HGSCC).size) &&						\
		 (!BIT ((_hoops_PGSCC).flags, _hoops_SIICA) || (_hoops_PGSCC).glyph_symbol == (_hoops_HGSCC).glyph_symbol))



#define _hoops_SSGHR(_hoops_PGSCC, _hoops_HGSCC)		\
		(((_hoops_PGSCC).flags & _hoops_HCCCC) <		\
		 ((_hoops_HGSCC).flags & _hoops_HCCCC) ||		\
		 (_hoops_PGSCC).flags == (_hoops_HGSCC).flags &&				\
		 ((_hoops_PGSCC).size < (_hoops_HGSCC).size ||				\
		  (_hoops_PGSCC).size == (_hoops_HGSCC).size &&				\
		  (_hoops_PGSCC).glyph_symbol < (_hoops_HGSCC).glyph_symbol))

////////////////////////////////////////////////////////////////////////////////

typedef unsigned short _hoops_GHHPR;
#define _hoops_HPHPR			(_hoops_GHHPR)0x0001
#define _hoops_APHPR		(_hoops_GHHPR)0x0002
#define _hoops_IPHPR		(_hoops_GHHPR)0x0004
#define _hoops_AGSII			(_hoops_HPHPR | _hoops_APHPR)
#define _hoops_SHHPR		(_hoops_HPHPR | _hoops_APHPR | _hoops_IPHPR)

#define _hoops_SSRRA		(_hoops_GHHPR)0x0010
#define _hoops_RPGI	(_hoops_GHHPR)0x0020
#define _hoops_CCICA			(_hoops_SSRRA | _hoops_RPGI)

#define _hoops_APGI			(_hoops_GHHPR)0x0040
#define _hoops_AHIAA			(_hoops_GHHPR)0x0080
#define _hoops_ICICA		(_hoops_APGI | _hoops_AHIAA)

#define _hoops_AACPR					(_hoops_GHHPR)0x0100
#define _hoops_AGSPR					(_hoops_GHHPR)0x0200
#define _hoops_HGCCP			(_hoops_GHHPR)0x0200 //_hoops_PCHCP _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_HSHRR _hoops_PCPI
#define _hoops_CIIPR						(_hoops_GHHPR)0x0400
#define _hoops_CCCPR					(_hoops_GHHPR)0x0800

#define _hoops_GPGI			(_hoops_GHHPR)0x1000
#define _hoops_SCICA				(_hoops_GHHPR)0x2000
#define _hoops_CRAHR				(_hoops_GHHPR)0x4000
#define _hoops_IPACP			(_hoops_GHHPR)0x8000
															 

struct _hoops_IAHPR {
	RGB						color;			/* _hoops_ISHA _hoops_HAIR, _hoops_SGS _hoops_HRGR */
	_hoops_ACGHR		findex;			/* _hoops_ISHA _hoops_HAIR, _hoops_SGS _hoops_HRGR */
	float					weight;
	unsigned char			pattern;
	Line_Style				line_style;
	_hoops_GHHPR		flags;
	int						_hoops_CPACP;
};

struct _hoops_HHHIR {
	_hoops_HHHIR *		next;
	_hoops_PHASP		_hoops_HSAI;
	_hoops_HCRPR				name;
	Integer32			key;
	unsigned char		id;
};

struct _hoops_RPGHR {
	/* _hoops_PGII _hoops_SIRGR _hoops_IIGR _hoops_IGIR = _hoops_ASHS	_hoops_AHSAR _hoops_HSGP _hoops_HIGR */

	_hoops_GHHPR *		flags;

	RGB *					colors;
	_hoops_ACGHR *		findices;
	unsigned char *			_hoops_AHHIR; 
	_hoops_HHHIR *			_hoops_PHHIR;
	float *					weights;
	Vector *				normals;

	int						_hoops_HSRRA;
	int						_hoops_PSRRA;
	int						_hoops_CPIAA;
	int						_hoops_SIIPR;
	int						_hoops_SRAPA;
	int						_hoops_CCHHC;
	int						explicit_normal_count;

	_hoops_GHHPR alter *	_hoops_CHHPR (int index = 0) alter {
		return &flags[index];
	}
	_hoops_GHHPR const *	_hoops_CHHPR (int index = 0) const {
		return &flags[index];
	}
};

#define _hoops_SHSPR(_hoops_ACAIP)	ZERO_STRUCT(&(_hoops_ACAIP), _hoops_IAHPR)

#define _hoops_AAIPR(_hoops_IGSCC, _hoops_CGSCC) do {		\
			(_hoops_CGSCC).color	  = (_hoops_IGSCC).color;				\
			(_hoops_CGSCC).findex  = (_hoops_IGSCC).findex;			\
			(_hoops_CGSCC).weight  = (_hoops_IGSCC).weight;			\
			(_hoops_CGSCC).pattern = (_hoops_IGSCC).pattern;			\
			(_hoops_CGSCC).line_style = (_hoops_IGSCC).line_style;		\
			(_hoops_CGSCC).flags	  = (_hoops_IGSCC).flags;				\
		} while (0)

#define _hoops_GISPR(_hoops_SGSCC, index, _hoops_ACAIP) do {					\
			(_hoops_ACAIP).flags = (_hoops_SGSCC)->flags[index] & ~_hoops_CRAHR;	\
			if ((_hoops_SGSCC)->colors != null)									\
				(_hoops_ACAIP).color = (_hoops_SGSCC)->colors[index];						\
			if ((_hoops_SGSCC)->findices != null)								\
				(_hoops_ACAIP).findex = (_hoops_SGSCC)->findices[index];					\
			if ((_hoops_SGSCC)->weights != null)									\
				(_hoops_ACAIP).weight = (_hoops_SGSCC)->weights[index];					\
			if ((_hoops_SGSCC)->_hoops_AHHIR != null)								\
				(_hoops_ACAIP).pattern = (_hoops_SGSCC)->_hoops_AHHIR[index];					\
		} while (0)

#define _hoops_GSSPR(_hoops_SGSCC, index, _hoops_ACAIP)										\
		(((_hoops_ACAIP).flags & ~_hoops_CRAHR) == ((_hoops_SGSCC)->flags[index] & ~_hoops_CRAHR) &&	\
		 ((_hoops_SGSCC)->colors == null || (_hoops_ACAIP).color == (_hoops_SGSCC)->colors[index]) &&					\
		 ((_hoops_SGSCC)->weights == null ||	(_hoops_ACAIP).weight == (_hoops_SGSCC)->weights[index]) &&				\
		 ((_hoops_SGSCC)->findices == null || (_hoops_ACAIP).findex == (_hoops_SGSCC)->findices[index]) &&				\
		 ((_hoops_SGSCC)->_hoops_AHHIR == null || (_hoops_ACAIP).pattern == (_hoops_SGSCC)->_hoops_AHHIR[index]))

#define _hoops_HPGI(_hoops_GRSCC, _hoops_RRSCC, mask)													\
	(((_hoops_GRSCC).flags & (mask)) == ((_hoops_RRSCC).flags & (mask)) &&											\
	 (!BIT ((_hoops_GRSCC).flags&(mask), _hoops_GPGI) || (_hoops_GRSCC).pattern == (_hoops_RRSCC).pattern) &&			\
	 (!BIT ((_hoops_GRSCC).flags&(mask), _hoops_SCICA) || (_hoops_GRSCC).weight == (_hoops_RRSCC).weight) &&			\
	 (!BIT ((_hoops_GRSCC).flags&(mask), _hoops_RPGI) || (_hoops_GRSCC).findex == (_hoops_RRSCC).findex) &&	\
	 (!BIT ((_hoops_GRSCC).flags&(mask), _hoops_SSRRA) ||										\
		(_hoops_GRSCC).color.red	  == (_hoops_RRSCC).color.red   &&													\
		(_hoops_GRSCC).color.green == (_hoops_RRSCC).color.green &&													\
		(_hoops_GRSCC).color.blue  == (_hoops_RRSCC).color.blue))

#define _hoops_AGIPR(_hoops_GRSCC, _hoops_RRSCC)				\
		((_hoops_GRSCC).flags < (_hoops_RRSCC).flags ||					\
		 (_hoops_GRSCC).flags == (_hoops_RRSCC).flags &&					\
		 ((_hoops_GRSCC).weight < (_hoops_RRSCC).weight ||				\
		  (_hoops_GRSCC).weight == (_hoops_RRSCC).weight &&				\
		  ((_hoops_GRSCC).pattern < (_hoops_RRSCC).pattern ||				\
		   (_hoops_GRSCC).pattern == (_hoops_RRSCC).pattern &&			\
		   ((_hoops_GRSCC).findex < (_hoops_RRSCC).findex ||				\
		    (_hoops_GRSCC).findex == (_hoops_RRSCC).findex &&				\
		    ((_hoops_GRSCC).color.red  <  (_hoops_RRSCC).color.red    ||	\
			 (_hoops_GRSCC).color.red  == (_hoops_RRSCC).color.red    &&	\
			 ((_hoops_GRSCC).color.green < (_hoops_RRSCC).color.green  ||	\
			  (_hoops_GRSCC).color.green == (_hoops_RRSCC).color.green &&	\
			  (_hoops_GRSCC).color.blue  <  (_hoops_RRSCC).color.blue))))))

////////////////////////////////////////////////////////////////////////////////

typedef unsigned char _hoops_SRRHR;
#define _hoops_PARHR			(_hoops_SRRHR)0x01
#define _hoops_IARHR		(_hoops_SRRHR)0x02
#define _hoops_CARHR		(_hoops_SRRHR)0x04
#define _hoops_PGSII			(_hoops_PARHR | _hoops_IARHR)
#define _hoops_PPRHR		(_hoops_PARHR | _hoops_IARHR | _hoops_CARHR)


typedef unsigned short _hoops_GIIPR;
#define	_hoops_ARSCC		(_hoops_GIIPR)0x000F

#define _hoops_PRSCC	(_hoops_GIIPR)0x0010
#define _hoops_HRSCC	(_hoops_GIIPR)0x0020
#define _hoops_IRSCC	(_hoops_GIIPR)0x0040
#define _hoops_CRSCC	(_hoops_GIIPR)0x0080
#define LFA_EXPLICIT_COLOR_BY_VALUE			(_hoops_PRSCC | _hoops_HRSCC)
#define LFA_EXPLICIT_COLOR_BY_FINDEX		(_hoops_IRSCC | _hoops_CRSCC)
#define _hoops_IACHR				(LFA_EXPLICIT_COLOR_BY_VALUE | LFA_EXPLICIT_COLOR_BY_FINDEX)

#define _hoops_IAGI				(_hoops_GIIPR)0x0100
#define _hoops_HSIPR				(_hoops_GIIPR)0x0200
#define _hoops_HRAPA			(_hoops_IAGI | _hoops_HSIPR)

#define _hoops_HAGI				(_hoops_GIIPR)0x0400
#define LFA_EXPLICIT_NORMAL					(_hoops_GIIPR)0x0800

#define _hoops_ACSII					(_hoops_IACHR | _hoops_HRAPA | \
											 _hoops_HAGI | LFA_EXPLICIT_NORMAL)

#define _hoops_RGIHR				(_hoops_GIIPR)0x1000
#define _hoops_IGAHR					(_hoops_GIIPR)0x8000

typedef unsigned short _hoops_SARHR;
#define	_hoops_PHGPR				(_hoops_SARHR)(_hoops_ACSII | _hoops_PGSII)
#define _hoops_SRSCC				(_hoops_SARHR)(_hoops_ACSII | _hoops_PPRHR)


struct One_Face_Attributes {
	RGB						color;			/* _hoops_HSP _hoops_HAIR, _hoops_SGS _hoops_HRGR */
	_hoops_ACGHR		findex;			/* _hoops_HSP _hoops_HAIR, _hoops_SGS _hoops_HRGR */
	unsigned char			pattern;		/* _hoops_GAR _hoops_GGR _hoops_PAIA._hoops_GGHR */
	int						region;
	_hoops_SARHR	flags;
};

struct Local_Face_Attributes {
	/* _hoops_PGII _hoops_SIRGR _hoops_IIGR _hoops_IGIR = _hoops_ACHAA */

	_hoops_GIIPR *			flags;
	_hoops_SRRHR *	_hoops_GARHR;
	_hoops_GIIPR			_hoops_SGRHR;

	RGB *						colors;
	_hoops_ACGHR *			findices;
	unsigned char *				_hoops_AHHIR; /* _hoops_GAR _hoops_GGR _hoops_PAIA._hoops_GGHR */
	_hoops_ARPA *						normals;

	int *						regions;

	int							_hoops_CPIAA;
	int							_hoops_SIIPR;
	int							_hoops_HSRRA;
	int							_hoops_PSRRA;
	int							_hoops_SRAPA;
	int							explicit_normal_count;
	int							_hoops_IHAHR;
	int							_hoops_HCRHR;

	_hoops_GIIPR alter *	_hoops_CHHPR (int index = 0) alter {
		if (flags)
			return &flags[index];
		else
			return &_hoops_SGRHR;
	}
	_hoops_GIIPR const *	_hoops_CHHPR (int index = 0) const {
		if (flags)
			return &flags[index];
		else
			return &_hoops_SGRHR;
	}

	bool	lff_uniform (int face_count, _hoops_GIIPR _hoops_GASCC = _hoops_ACSII) {
		if (BIT(_hoops_GASCC, _hoops_IAGI) &&
			_hoops_CPIAA != 0 && _hoops_CPIAA != face_count)									
			return false;
		if (BIT(_hoops_GASCC, _hoops_HSIPR) &&
			_hoops_SIIPR != 0 && _hoops_SIIPR != face_count)
			return false;
		if (BIT(_hoops_GASCC, LFA_EXPLICIT_COLOR_BY_VALUE) &&
			_hoops_HSRRA != 0 && _hoops_HSRRA != face_count)
			return false;
		if (BIT(_hoops_GASCC, LFA_EXPLICIT_COLOR_BY_FINDEX) &&
			_hoops_PSRRA != 0 && _hoops_PSRRA != face_count)
			return false;
		if (BIT(_hoops_GASCC, _hoops_HAGI) &&
			_hoops_SRAPA != 0 && _hoops_SRAPA != face_count)
			return false;
		if (BIT(_hoops_GASCC, LFA_EXPLICIT_NORMAL) &&
			explicit_normal_count != 0 && explicit_normal_count != face_count)
			return false;

		return true;
	}
};

#define _hoops_AAPHR(_hoops_RASCC) ZERO_STRUCT(&(_hoops_RASCC), One_Face_Attributes)

#define _hoops_PIPHR(_hoops_AASCC, index, _hoops_RASCC) do {					\
			(_hoops_RASCC).flags = *(_hoops_AASCC)->_hoops_CHHPR(index) & _hoops_SRSCC;	\
			if (_hoops_AASCC->_hoops_GARHR)										\
				(_hoops_RASCC).flags |= (_hoops_AASCC)->_hoops_GARHR[index];				\
			if ((_hoops_AASCC)->colors != null)									\
				(_hoops_RASCC).color = (_hoops_AASCC)->colors[index];						\
			if ((_hoops_AASCC)->findices != null)								\
				(_hoops_RASCC).findex = (_hoops_AASCC)->findices[index];					\
			if ((_hoops_AASCC)->_hoops_AHHIR != null)								\
				(_hoops_RASCC).pattern = (_hoops_AASCC)->_hoops_AHHIR[index];					\
			if ((_hoops_AASCC)->regions != null)									\
				(_hoops_RASCC).region = (_hoops_AASCC)->regions[index];					\
		} while (0)

#define _hoops_IIPHR(_hoops_AASCC, index, _hoops_RASCC)								\
		((_hoops_RASCC).flags == (*(_hoops_AASCC)->_hoops_CHHPR(index) & _hoops_SRSCC |					\
						((_hoops_AASCC->_hoops_GARHR) ? (_hoops_AASCC)->_hoops_GARHR[index] : 0)) &&	\
		 ((_hoops_AASCC)->colors == null || (_hoops_RASCC).color == (_hoops_AASCC)->colors[index]) &&			\
		 ((_hoops_AASCC)->findices == null || (_hoops_RASCC).findex == (_hoops_AASCC)->findices[index]) &&		\
		 ((_hoops_AASCC)->_hoops_AHHIR == null || (_hoops_RASCC).pattern == (_hoops_AASCC)->_hoops_AHHIR[index]) &&		\
		 ((_hoops_AASCC)->regions == null || (_hoops_RASCC).region == (_hoops_AASCC)->regions[index]))

#define _hoops_SAGI(_hoops_PASCC, _hoops_HASCC, mask)														\
		(((_hoops_PASCC).flags & (mask)) == ((_hoops_HASCC).flags & (mask)) &&											\
		 ((_hoops_PASCC).region == (_hoops_HASCC).region ||																\
			((_hoops_PASCC).flags & _hoops_PHGPR) == 0 &&													\
			!BIT (HOOPS_WORLD->system_flags, _hoops_CSRRA)) &&								\
		 (!BIT ((_hoops_PASCC).flags&(mask), _hoops_HAGI) || (_hoops_PASCC).pattern == (_hoops_HASCC).pattern) &&			\
		 (!BIT ((_hoops_PASCC).flags&(mask), LFA_EXPLICIT_COLOR_BY_FINDEX) || (_hoops_PASCC).findex == (_hoops_HASCC).findex) &&	\
		 (!BIT ((_hoops_PASCC).flags&(mask), LFA_EXPLICIT_COLOR_BY_VALUE) || (_hoops_PASCC).color == (_hoops_HASCC).color))

#define _hoops_HGPHR(_hoops_PASCC, _hoops_HASCC)				\
		((_hoops_PASCC).flags < (_hoops_HASCC).flags ||					\
		 (_hoops_PASCC).flags == (_hoops_HASCC).flags &&					\
		 ((_hoops_PASCC).region < (_hoops_HASCC).region ||				\
		  (_hoops_PASCC).region == (_hoops_HASCC).region &&				\
		  ((_hoops_PASCC).pattern < (_hoops_HASCC).pattern ||				\
		   (_hoops_PASCC).pattern == (_hoops_HASCC).pattern &&			\
		   ((_hoops_PASCC).findex < (_hoops_HASCC).findex ||				\
			(_hoops_PASCC).findex == (_hoops_HASCC).findex &&				\
			((_hoops_PASCC).color.red   <  (_hoops_HASCC).color.red   ||	\
			 (_hoops_PASCC).color.red   == (_hoops_HASCC).color.red   &&	\
			 ((_hoops_PASCC).color.green <  (_hoops_HASCC).color.green ||	\
			  (_hoops_PASCC).color.green == (_hoops_HASCC).color.green &&	\
			  (_hoops_PASCC).color.blue  <  (_hoops_HASCC).color.blue))))))

////////////////////////////////////////////////////////////////////////////////


#define			_hoops_PAIPR				0x00
#define			_hoops_IASCC		0x01
#define			_hoops_ICCII		0x02
#define			_hoops_CASCC		0x04

struct _hoops_RRCC {
	_hoops_RRCC *	next;

	_hoops_RSSH *				_hoops_CCHA;
	int						_hoops_CGAHR;
	int						_hoops_GSHA;
	_hoops_SSIC			_hoops_SCAI;

	bool					_hoops_SASCC;
	bool					_hoops_SPGRC;

	_hoops_PHASP			_hoops_HSAI;
};


/* _hoops_PAGA: _hoops_GPSCC _hoops_HRGR _hoops_RPSCC _hoops_CCA 2 _hoops_SPCS _hoops_HSH _hoops_HPGR _hoops_RH _hoops_HSPP _hoops_IIGR _hoops_RCSAR _hoops_CGGR 
 * _hoops_HIS _hoops_SGS _hoops_ACHAR _hoops_PPR _hoops_GPSCC _hoops_CCHRC _hoops_GGR _hoops_CAPRH. */
struct Tristrip {
	Tristrip *				next;
	Geometry *				_hoops_GSCP;
	Bounding				bounding;

	_hoops_PHASP			_hoops_HSAI;

	_hoops_IGCGP	_hoops_RAHH;
	Activity				_hoops_CPGPR;
	Activity				_hoops_SPGPR;
	_hoops_GHGI				_hoops_GSAI;
	_hoops_ARCGP				_hoops_SRHA;
	_hoops_ARCGP				_hoops_CARI;

	int						_hoops_PHHA;
	int						total;
	int *					lengths;
	int *					_hoops_AIHA;
	int *					face_indices;

	int						point_count;
	int						face_count;

	Point *					points;
	RGB *					_hoops_PCHA;
	float *					_hoops_HCHA;
	Vector *				_hoops_ICHA;
	_hoops_RRCC *	_hoops_GSSH;
	float *					_hoops_CCCP;

	RGB *					_hoops_PAGI;
	_hoops_ARPA *					_hoops_PRHH;

	/*_hoops_SPGGR					*_hoops_IAHCP;*/
	/*_hoops_SCSH					*_hoops_APSCC;*/
	Tristrip const *		_hoops_SCGHR;
	_hoops_GACR *			_hoops_GAHA;
#	ifdef _hoops_SCIGI
	int						*list;
#	endif

	int						lengths_allocated;
	int						_hoops_IPII;
	int						_hoops_SGAHR;

	bool					_hoops_RPRCP;
	bool					_hoops_GPPPI;

	int						same_colors;

	One_Face_Attributes		face_attributes;
};

/* _hoops_ISHA _hoops_PSPI _hoops_SAGGR 1 _hoops_SPCS _hoops_CRPSR _hoops_PIRA _hoops_RIR _hoops_CGGR */
struct Polyedge {
	Polyedge *				next;
	Geometry *				_hoops_GSCP; 
	Bounding				bounding;

	_hoops_PHASP			_hoops_HSAI;

	_hoops_IGCGP	_hoops_RAHH;
	Activity				_hoops_CPGPR;
	Activity				_hoops_SPGPR;
	_hoops_GHGI				_hoops_GSAI;
	_hoops_ARCGP				_hoops_SRHA;
	_hoops_ARCGP				_hoops_CARI;

	int						_hoops_PHHA;
	int						total;
	int *					lengths;
	int *					_hoops_AIHA;
	int *					_hoops_SPII;

	int						point_count;
	int						_hoops_SPHA;

	Point *					points;
	RGB *					_hoops_PCHA;
	float *					_hoops_HCHA;
	Vector *				_hoops_ICHA;
	_hoops_RSSH *				_hoops_CCHA;
	Integer32				_hoops_GSHA;
	_hoops_SSIC			_hoops_SCAI;
	float *					_hoops_CCCP;

	RGB *					_hoops_ASHA;
	Vector *				_hoops_RSHA;

	Polyedge const *		_hoops_SCGHR;  
	_hoops_GACR *			_hoops_GAHA;

#	ifdef _hoops_SCIGI
	int						*list;
#	endif

	int						lengths_allocated;
	int						_hoops_IPII;
	int						_hoops_CPII;

	bool					_hoops_RPRCP;
	bool					_hoops_GPPPI;
	int						same_colors;

	_hoops_IAHPR		_hoops_PPGI;
};

struct Polymarker {
	Polymarker *			next;
	Geometry *				_hoops_GSCP;
	Bounding				bounding;

	_hoops_PHASP			_hoops_HSAI;

	_hoops_IGCGP	_hoops_RAHH;
	Activity				_hoops_CPGPR;
	Activity				_hoops_SPGPR;
	_hoops_GHGI				_hoops_GSAI;
	_hoops_ARCGP				_hoops_SRHA;
	_hoops_ARCGP				_hoops_CARI;

	int *					_hoops_AIHA;
	int						length;
	int						point_count;

	Point *					points;
	RGB *					_hoops_PCHA;
	RGBAS32 *				_hoops_RGIA;
	float *					_hoops_HCHA;
	Vector *				_hoops_ICHA;
	_hoops_RSSH *				_hoops_CCHA;
	Integer32				_hoops_GSHA;
	_hoops_SSIC			_hoops_SCAI;
	float *					_hoops_CCCP;

	Polymarker *			_hoops_SCGHR;  
	_hoops_GACR *			_hoops_GAHA;
#	ifdef _hoops_SCIGI
	int						*list;
#	endif

	int						_hoops_IPII;

	bool					_hoops_RPRCP;
	bool					_hoops_GPPPI;

	int						same_colors;

	_hoops_PSGHR	_hoops_SACI;
};



/* _hoops_PPSCC */
struct _hoops_GAHS {
	_hoops_GAHS *			next;
	Geometry *				_hoops_GSCP;
	Bounding				bounding;
};


////////////////////////////////////////////////////////////////////////////////


typedef unsigned int	_hoops_IICHH;
#define _hoops_HACPR								(_hoops_IICHH)0x00000001
#define _hoops_PACPR						(_hoops_IICHH)0x00000002
#define _hoops_PGAHR					(_hoops_IICHH)0x00000004

#define PHF_VERTEX_NORMALS_VALID				(_hoops_IICHH)0x00000008
#define PHF_FACE_NORMALS_VALID					(_hoops_IICHH)0x00000010
#define _hoops_GAAHR					(_hoops_IICHH)0x00000020

#define _hoops_HPSCC							(_hoops_IICHH)0x00000040
#define _hoops_IPSCC						(_hoops_IICHH)0x00000080

#define PHF_POINTS_BY_REFERENCE					(_hoops_IICHH)0x00000100
#define PHF_VERTEX_NORMALS_BY_REFERENCE			(_hoops_IICHH)0x00000200
#define PHF_SHELL_FACE_LIST_BY_REFERENCE		(_hoops_IICHH)0x00000400

#define PHF_IMPLICIT_NORMALS_REVERSED			(_hoops_IICHH)0x00000800
#define _hoops_ASAHR					(_hoops_IICHH)0x00001000

#define _hoops_CCRHR			(_hoops_IICHH)0x00002000
#define _hoops_APCCP			(_hoops_IICHH)0x00004000
#define _hoops_APRHR				(_hoops_IICHH)0x00008000
#define _hoops_CGRHR			(_hoops_IICHH)0x00010000

#define _hoops_SCRRA						(_hoops_IICHH)0x00020000

#define _hoops_PGCCP					(_hoops_IICHH)0x00040000


typedef char			_hoops_CSSHA;
#define _hoops_AARCA		(_hoops_CSSHA)0x1
#define _hoops_HARCA	(_hoops_CSSHA)0x2
#define _hoops_PARCA		(_hoops_CSSHA)0x4
#define _hoops_CCICP		(_hoops_CSSHA)0x8


struct Polyhedron : public Geometry {

	Bounding					bounding;

	/* _hoops_CPSCC _hoops_PIH */
	Point *						points;

	/* _hoops_SPSCC & _hoops_GSPPA _hoops_HSCAR */
	_hoops_IICHH			polyhedron_flags;	  /* (_hoops_SHHA _hoops_IS _hoops_SHH 2 _hoops_GCSRR) */

	/*
	 * _hoops_CGP _hoops_RH _hoops_IGRH _hoops_HRGR _hoops_GPP _hoops_PSCR _hoops_RH _hoops_RSHCR _hoops_IGRH (_hoops_PAR _hoops_IGRI)
	 * _hoops_GGR _hoops_GRR _hoops_HIGR _hoops_RGSPR _hoops_PAH _hoops_SHH _hoops_GHSCC _hoops_IS _hoops_SHH _hoops_IPIH _hoops_CCCI.
	 */
	Local_Vertex_Flags			_hoops_AGRHR;
	_hoops_GHHPR			_hoops_RSHPR;
	_hoops_SARHR		_hoops_ACRHR;
	struct _hoops_RHSCC {
		float						scale;
		float						translate;
		int							_hoops_RSCRP;
		int							_hoops_CIAIR;
		float  *					_hoops_SIAIR;
	}							_hoops_GIHIR;
	int							_hoops_AHSCC;


	int							point_count;
	int							face_count;
	int							_hoops_SPHA;		/* -1 _hoops_RPP _hoops_HAR _hoops_HSSPR */

	int							_hoops_GCRHR;

	/*
	 * _hoops_IPCP _hoops_HSPR _hoops_GSRS _hoops_GPHA/_hoops_HSP/_hoops_ISHA _hoops_IRGH _hoops_AIRC. _hoops_HGISI _hoops_GHCS
	 * _hoops_HRGR _hoops_PISI _hoops_CCGR _hoops_RH _hoops_SRS _hoops_GHIR _hoops_SSIA _hoops_CHR _hoops_IGRC _hoops_SIGR - _hoops_CCGR
	 * _hoops_RH _hoops_SRS _hoops_AIRC _hoops_CHR _hoops_ARP _hoops_HPP _hoops_RH _hoops_IPSP, _hoops_PAR _hoops_AICRR _hoops_IRHS _hoops_IS _hoops_RARIR _hoops_CAPR
	 */
	Local_Vertex_Attributes		local_vertex_attributes;
	_hoops_RPGHR		_hoops_IHHPR;
	Local_Face_Attributes		local_face_attributes;

	
	
	_hoops_ARPA alter *				_hoops_PGPCP;

	/* _hoops_RCSA _hoops_IGI _hoops_HPP _hoops_RH _hoops_SCGR _hoops_ACIPR-_hoops_ISHA _hoops_AHHA */

	float						_hoops_GCIPR;

	/*
	 * _hoops_GSPHA _hoops_IH _hoops_IGRC _hoops_ASCA
	 */

	/*
	 * '_hoops_PSSI' _hoops_CHR _hoops_RH _hoops_SSAAA _hoops_GPIA _hoops_CPCI.  _hoops_HGI _hoops_HIGR _hoops_GRS
	 * _hoops_SHH _hoops_PSPP _hoops_RH _hoops_SRS _hoops_GHIR _hoops_SAIA _hoops_IGRC _hoops_RRP _hoops_IS _hoops_SHH _hoops_PHSCC.
	 */
	Polymarker *				_hoops_GIGPR;

	/*
	 * '_hoops_AHHA' _hoops_CHR _hoops_RH _hoops_SSAAA _hoops_ISHA _hoops_CPCI. _hoops_HGI _hoops_HIGR _hoops_GRS
	 * _hoops_SHH _hoops_PSPP _hoops_RH _hoops_SRS _hoops_GHIR _hoops_SPPR _hoops_IGRC _hoops_RRP _hoops_IS _hoops_SHH _hoops_PHSCC.
	 */
	Polyedge *					_hoops_SHGPR;

	/*
	 * '_hoops_CCGI' _hoops_CHR _hoops_RH _hoops_SSAAA _hoops_HSP _hoops_CPCI. _hoops_HGI _hoops_HIGR _hoops_GRS
	 * _hoops_SHH _hoops_PSPP _hoops_RH _hoops_SRS _hoops_GHIR _hoops_RSSI _hoops_IGRC _hoops_RRP _hoops_IS _hoops_SHH _hoops_PHSCC.
	 */
	Tristrip *					tristrips;

	/*
	 * '_hoops_ACGC' _hoops_CHR _hoops_RH _hoops_GGSRA _hoops_CPRC _hoops_APGR. _hoops_HGI _hoops_HIGR _hoops_GRS
	 * _hoops_SHH _hoops_PSPP _hoops_RH _hoops_SRS _hoops_GHIR _hoops_ACGC _hoops_IGRC _hoops_RRP _hoops_IS _hoops_SHH _hoops_PHSCC.
	 */
	Polyedge *					_hoops_CHGPR;

	/* _hoops_CCHHR _hoops_HIGR _hoops_IIGR _hoops_IAGAI _hoops_SHCPI */
	_hoops_PGAIR *					_hoops_HGAIR;
};


struct _hoops_AIHPR : public Polyhedron {
	/* _hoops_SAPRR _hoops_GIGR [_hoops_IPSP _hoops_CHIA, _hoops_HHSCC] _hoops_PIH */
	int							rows;
	int							columns;

	/* _hoops_SAPRR _hoops_GRAHA _hoops_PPR _hoops_PHPHA _hoops_PIH */

	/*
	 * _hoops_IPCP _hoops_ISHA _hoops_AIRC _hoops_CHR _hoops_GCSS, _hoops_IH _hoops_GRR _hoops_HSHRR _hoops_GPHA, _hoops_GAR _hoops_RH _hoops_ISHA
	 * _hoops_IS _hoops_RH _hoops_RPHR, _hoops_AGCPR, _hoops_PPR _hoops_IHSCC _hoops_GH _hoops_PPR _hoops_IS _hoops_RH _hoops_RAAP. _hoops_HSRR
	 * _hoops_GSGAR, _hoops_GC _hoops_HRGR _hoops_ARSAR _hoops_IH _hoops_RH _hoops_AIRC _hoops_PRGI _hoops_CGPR _hoops_RH
	 * _hoops_ISHA _hoops_ACAS _hoops_HRGR _hoops_PSAP _hoops_RH _hoops_HSHRR.
	 */
};


/*
 * _hoops_SPR _hoops_PASPR _hoops_GPHA _hoops_PAH _hoops_PPIP _hoops_GRR _hoops_ISHA;
 * _hoops_IGI _hoops_HPP _hoops_ISHA _hoops_AIRC, _hoops_AHI.
 */
struct _hoops_RHHPR {
	int					_hoops_GIHPR;	  /* _hoops_SHI _hoops_GIAA '_hoops_RSSA' */
};


/*
 * _hoops_PGCR _hoops_RSSI _hoops_PAH _hoops_PPIP _hoops_GRR _hoops_ISHA;
 * _hoops_IGI _hoops_HPP _hoops_ASSIA _hoops_RRGR.
 */
struct _hoops_CGCPR {
	int					_hoops_AIIPR; /* _hoops_PSRPA _hoops_SHR _hoops_SIGH _hoops_IRS _hoops_HPHR _hoops_HSP */
	int					_hoops_HIIPR;
#	define				_hoops_PIIPR	(-1)
#	define				_hoops_IAGPA	(-2)	/* _hoops_RPP _hoops_RRI _hoops_HSAR 2 _hoops_RSSI */
};

#define _hoops_CHSCC			0
#define _hoops_SHSCC		1
#define _hoops_GISCC	2
#define _hoops_SHHIR			3 /* 1 _hoops_IH _hoops_RH _hoops_HISAR _hoops_CIHA, 2 _hoops_IH _hoops_RH _hoops_CASH _hoops_CIHA, 3 _hoops_IH _hoops_IRS _hoops_RISCC _hoops_RIP. */

struct Shell : public Polyhedron {
	/* _hoops_SAPRR _hoops_GIGR [_hoops_IPSP _hoops_CHIA, _hoops_HHSCC] _hoops_PIH */
	bool						_hoops_GSAPA;
	int							face_list_length;
	int *						face_list;

	/* _hoops_SAPRR _hoops_GRAHA _hoops_PPR _hoops_PHPHA _hoops_PIH */

	/*
	 * _hoops_ASCGR _hoops_AISCC _hoops_SIHC _hoops_HRGR _hoops_RCPGR _hoops_IPGPA _hoops_PGGA, _hoops_ISGHR _hoops_RSSI _hoops_PPR _hoops_RSSA,
	 * _hoops_RH _hoops_SIA _hoops_HII _hoops_RH "_hoops_PISCC" _hoops_SIHC _hoops_IS _hoops_RH _hoops_GGSP _hoops_HISCC
	 * _hoops_RIS _hoops_HRGR _hoops_HAR _hoops_IHGP.
	 *
	 * '_hoops_PRCPR' _hoops_HRGR _hoops_IRS _hoops_HIGR, _hoops_GSHHR _hoops_HPP _hoops_HCGP _hoops_GPHA, _hoops_IIGR _hoops_PASPR _hoops_GIHA.
	 * _hoops_IPCP _hoops_HCGP _hoops_GPHA _hoops_HRGR _hoops_CIAII _hoops_HII _hoops_RH _hoops_SIHC _hoops_GGR _hoops_IISCC.
	 *
	 * '_hoops_CISCC' _hoops_ACAR _hoops_GRR _hoops_HCGP _hoops_GPHA _hoops_IS _hoops_RH _hoops_RSGI _hoops_IIGR
	 * _hoops_RGCI _hoops_HGAGA _hoops_IIGR _hoops_PASPR _hoops_GIHA _hoops_GIAA _hoops_RH '_hoops_SPPR'
	 * _hoops_CRPR. _hoops_IPCP _hoops_PHI _hoops_IIGR _hoops_HGPP _hoops_GIHA _hoops_HRGR "_hoops_RPGPA[_hoops_GHAP+1] -
	 * _hoops_RPGPA[_hoops_GHAP]", _hoops_HIS _hoops_RGR _hoops_CRPR _hoops_HRGR _hoops_SISCC _hoops_PPR
	 * _hoops_IGCGI _hoops_RHIR "_hoops_CGHI"+1 _hoops_IH _hoops_GSGAR.
	 *
	 * _hoops_IPCP _hoops_PPARR _hoops_HRGR _hoops_IGI _hoops_GGR _hoops_RH _hoops_GCSCC _hoops_IIGR _hoops_CPRAA _hoops_HHH _hoops_RCSCC.
	 *
	 * _hoops_IPCP _hoops_PRCR _hoops_IIGR _hoops_AGCR _hoops_SIRGR _hoops_HRGR _hoops_PISI _hoops_CCGR _hoops_PGI 
	 *  _hoops_IRS) _hoops_RH _hoops_SRS _hoops_PISCC
	 *  _hoops_RCSR) _hoops_RH _hoops_SRS _hoops_GHIR _hoops_SAHP _hoops_CHR _hoops_IIAC _hoops_SIGC.
	 * 
	 * _hoops_PAGA _hoops_SGS _hoops_IIH _hoops_HRGR _hoops_RGAR _hoops_SPR _hoops_PRIA _hoops_IH _hoops_GRR _hoops_ACSCC.  _hoops_HSRR _hoops_GII _hoops_RAGA
	 * _hoops_GPHA '_hoops_HAS', _hoops_RHAC _hoops_PAH _hoops_IHSH _hoops_GH _hoops_GIHA _hoops_CCA _hoops_CIHA > _hoops_HAS.  _hoops_PHGP _hoops_RPP _hoops_PPHR>_hoops_HAS _hoops_PPR _hoops_HAS->_hoops_PPHR 
	 * _hoops_HRGR _hoops_IRS _hoops_APIP _hoops_ACSCC, _hoops_HAS->_hoops_PPHR _hoops_GRS _hoops_GGCA _hoops_GAPA _hoops_RPGPA[_hoops_HAS] _hoops_PPR _hoops_RPGPA[_hoops_HAS+1]
	 * _hoops_HIH _hoops_PPHR->_hoops_HAS _hoops_GRS _hoops_HAR _hoops_SHH _hoops_GGR _hoops_RH _hoops_CCIR _hoops_RPGPA[_hoops_PPHR] _hoops_PPR _hoops_RPGPA[_hoops_PPHR+1]
	 */
	_hoops_RHHPR *		_hoops_GRCPR;			  /* _hoops_IGIR = _hoops_ASHS */
	_hoops_RHHPR **		_hoops_HHHPR; /* _hoops_GIAA '_hoops_SPPR', _hoops_IGIR=_hoops_RSHS+1 */

	/*
	 * _hoops_IPCP _hoops_HIGR _hoops_IIGR _hoops_RSSI _hoops_IHIA _hoops_CCA _hoops_GRR _hoops_ISHA _hoops_CHR _hoops_IGI _hoops_RHSP
	 * _hoops_ASSIA-_hoops_ISHA _hoops_SHRRR.
	 */
	_hoops_CGCPR *				_hoops_SGCPR;	  /* _hoops_IGIR = _hoops_ASHS */
};


////////////////////////////////////////////////////////////////////////////////

enum _hoops_PCSCC {
	Polyhedron_Progress_Setup,
	Polyhedron_Progress_Tristrips,
	_hoops_HCSCC,
	Polyhedron_Progress_Polyedges,
	Polyhedron_Progress_Polymarkers,
	Polyhedron_Progress_Cleanup
};

enum _hoops_ICSCC {
	Tristrip_Cut_Edges				= 0x0001,
	Tristrip_Resort					= 0x0002,
	Tristrip_Specials				= 0x0003,

	Polyedge_View_Dependent_Pass	= 0x0010,

	Polymarker_Diffuse_Locked		= 0x0100
};




struct _hoops_SGRGH : public CMO_Pooled {
	public:
		int							stage;		// _hoops_CCSCC

		Polyhedron const *			_hoops_IPRI;
		Tristrip *					tristrip;
		Polyedge *					_hoops_ACP;
		Polyedge *					polyedge;
		Polymarker *				_hoops_RGRHR;

		bool						_hoops_ARRGH;
		bool						_hoops_SCSCC;
		Color_Object				_hoops_GSSCC;

		_hoops_SGRGH (Polyhedron const * _hoops_HPGPR) : _hoops_IPRI (_hoops_HPGPR) {_hoops_PRRH (_hoops_IPRI);}
		~_hoops_SGRGH ();
};



////////////////////////////////////////////////////////////////////////////////


struct UV_Point {
	float				u, v;
};


struct UV_Edge {
	UV_Edge *			next;
	UV_Edge *			_hoops_RSSCC;

	int					index;
	float				priority;
	UV_Region *			region;
	struct {
		float				a, b, c;
	}					line;
};


struct UV_Region {
	UV_Region *			next;
	UV_Edge *			_hoops_GRCPR;

	struct {
		UV_Point		min, max;
	} _hoops_RCHS;			

	bool				_hoops_IHRRH;
};


struct UV_Region_Set {
	UV_Region *			regions;
	UV_Point *			points;		
	int					point_count;
	int					_hoops_CAHI;
};

#define _hoops_RSSSI (char)0x1
struct UV_Trim {
	Type				type;
	char				flags;
	UV_Trim *			next;
};

struct UV_Trim_Poly : public UV_Trim {
	UV_Point *			points;		
	int					count;	  
};

struct UV_Trim_Curve : public UV_Trim {
	int					degree;
	int					control_point_count;
	UV_Point *			control_points;
	float *				weights;
	float *				knots;
};


struct UV_Trim_Collection : public UV_Trim {
	UV_Trim *			_hoops_GPRIR;
};



#define _hoops_GIIAA		(_hoops_HIGAP)0x01
#define _hoops_CCSSI		(_hoops_HIGAP)0x02

struct _hoops_APPGR : public Geometry {
	_hoops_CCAGP					_hoops_RHAGR;		// _hoops_SAPGP _hoops_IS _hoops_PIAH _hoops_CPHAR

	_hoops_HIGAP			_hoops_SHIAA;
	int							n_u_vertices, n_v_vertices;
	int							u_degree, v_degree;
	Point *						control_points;	// _hoops_IGIR _hoops_HRGR (_hoops_ASSCC * _hoops_PSSCC). _hoops_HSSCC _hoops_SPAC _hoops_GGR _hoops_HPPC
	float *						weights; 		// _hoops_IGIR _hoops_HRGR (_hoops_ASSCC * _hoops_PSSCC)
	float *						u_knots; 		// _hoops_IGIR _hoops_HRGR (_hoops_ISSCC + _hoops_ASSCC + 1)
	float *						v_knots; 		// _hoops_IGIR _hoops_HRGR (_hoops_CSSCC + _hoops_PSSCC + 1)

	UV_Trim *					_hoops_GPRIR;

	// _hoops_ARRS _hoops_PIH _hoops_CHR _hoops_IPSP-_hoops_CHIA, _hoops_CAPP _hoops_CHR _hoops_PHPHA
	Polyhedron *				_hoops_IPRI;
	int							_hoops_GRPPA;		// _hoops_ICRRP _hoops_RPP _hoops_GII _hoops_IIGR _hoops_RH _hoops_HRP _hoops_SSCP _hoops_HGAS _hoops_CR _hoops_CPHAR _hoops_RGAP
};


#define _hoops_SSSCC	128 /* _hoops_RH _hoops_RGAR _hoops_HIAGR _hoops_PSGR _hoops_ARI */
#define _hoops_GGGSC	(_hoops_SSSCC + 1)
#define _hoops_RGGSC		(_hoops_GGGSC + \
										 _hoops_SSSCC)

#define _hoops_AGGSC	64 /* _hoops_RH _hoops_RGAR _hoops_HIAGR _hoops_PSGR _hoops_ARI */
#define _hoops_PGGSC		(2 * _hoops_AGGSC)
#define _hoops_HGGSC			(_hoops_PGGSC + 2)
#define _hoops_IGGSC				(_hoops_HGGSC + \
												 _hoops_PGGSC)
End_HOOPS_Namespace;

#define _hoops_RCCCC TRUE
#endif /* _hoops_CGGSC */
