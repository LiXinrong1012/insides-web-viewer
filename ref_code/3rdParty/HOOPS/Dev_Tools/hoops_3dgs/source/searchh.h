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
 * Search Hoops (searchh) - named changed from search.h to avoid
 * conflict with an existing search.h on sun systems
 *
 * $Id: obf_tmp.txt 1.46 2010-10-12 23:43:41 covey Exp $
 */

#ifndef _hoops_HCSRS

Begin_HOOPS_Namespace

struct _hoops_AGHPR {
	_hoops_AGHPR *			next;
	_hoops_HPAH *				item;
	Key						key;
	Type					type;
	bool					_hoops_AGRI;
};

struct _hoops_SSPPR {
	_hoops_SSPPR *			prev;
	_hoops_AGHPR *			list;
	int						count;

	/* _hoops_IGI _hoops_HPP _hoops_HRCSR _hoops_ICSRS... */
	_hoops_HCRPR *					_hoops_HGPIR;
	int						_hoops_IASRS;
	int						next;
	_hoops_GGAGR *					_hoops_HASRS;
};


/* _hoops_IGI _hoops_HPP _hoops_GRCCA, _hoops_CCSRS, _hoops_PPR _hoops_IPPAR _hoops_SICAR... */
#define _hoops_HHPPP				_hoops_GHAGP
#define _hoops_SCSRS		((int)_hoops_HHPPP + 1)

#define _hoops_RCICA						(_hoops_RHAGP+0)
#define _hoops_PCICA					(_hoops_RHAGP+1)
#define _hoops_GSICA							(_hoops_RHAGP+2)
#define _hoops_HCICA							(_hoops_RHAGP+3)
#define _hoops_PIICA						(_hoops_RHAGP+4)

#define _hoops_RHAPP					(_hoops_RHAGP+5)
#define _hoops_AHAPP						(_hoops_RHAGP+6)
#define _hoops_PHAPP					(_hoops_RHAGP+7)
#define _hoops_HHAPP						(_hoops_RHAGP+8)
#define _hoops_IHAPP					(_hoops_RHAGP+9)
#define _hoops_CHAPP							(_hoops_RHAGP+10)
#define _hoops_SHAPP					(_hoops_RHAGP+11)
#define _hoops_GIAPP					(_hoops_RHAGP+12)
#define _hoops_GHAPP					(_hoops_RHAGP+13)

#define _hoops_RIAPP				(_hoops_RHAGP+14)
#define _hoops_AIAPP					(_hoops_RHAGP+15)
#define _hoops_PIAPP					(_hoops_RHAGP+16)
#define _hoops_HIAPP					(_hoops_RHAGP+17)

#define _hoops_IIAPP					(_hoops_RHAGP+18)
#define _hoops_CIAPP						(_hoops_RHAGP+19)
#define _hoops_SIAPP					(_hoops_RHAGP+20)

#define _hoops_RCAPP				(_hoops_RHAGP+21)
#define _hoops_ACAPP					(_hoops_RHAGP+22)
#define _hoops_PCAPP					(_hoops_RHAGP+23)
#define _hoops_HCAPP				(_hoops_RHAGP+24)
#define _hoops_ICAPP			(_hoops_RHAGP+25)
#define _hoops_CCAPP				(_hoops_RHAGP+26)
#define _hoops_SCAPP					(_hoops_RHAGP+27)
#define _hoops_GSAPP					(_hoops_RHAGP+28)
#define _hoops_RSAPP				(_hoops_RHAGP+29)
#define _hoops_ASAPP					(_hoops_RHAGP+30)
#define _hoops_PSAPP			(_hoops_RHAGP+31)
#define _hoops_HSAPP			(_hoops_RHAGP+32)
#define _hoops_ISAPP				(_hoops_RHAGP+33)
#define _hoops_CSAPP			(_hoops_RHAGP+34)
#define _hoops_SSAPP			(_hoops_RHAGP+35)
#define _hoops_GGPPP			(_hoops_RHAGP+36)
#define _hoops_RGPPP			(_hoops_RHAGP+37)
#define _hoops_AGPPP				(_hoops_RHAGP+38)
#define _hoops_PGPPP			(_hoops_RHAGP+39)
#define _hoops_HGPPP				(_hoops_RHAGP+40)
#define _hoops_IGPPP					(_hoops_RHAGP+41)
#define _hoops_CGPPP			(_hoops_RHAGP+42)

#define	_hoops_SGPPP					(_hoops_RHAGP+43)
#define	_hoops_GRPPP			(_hoops_RHAGP+44)

#define _hoops_GCAPP					(_hoops_RHAGP+45)
#define _hoops_RRPPP				(_hoops_RHAGP+46)

#define _hoops_ARPPP						(_hoops_RHAGP+47)

#define _hoops_PRPPP						(_hoops_RHAGP+48)

#define _hoops_HRPPP			(_hoops_RHAGP+49)
#define _hoops_IRPPP					(_hoops_RHAGP+50)


struct _hoops_RRHCA {
	union {
		_hoops_AGHPR **			_hoops_ASRGR;
		int						count;
	}							item;

	bool						_hoops_CHHCA[_hoops_SCSRS];
	bool						_hoops_AHHCA,
								_hoops_GHPPP,
								_hoops_CPICA,
								_hoops_SPICA,
								_hoops_IPICA,
								_hoops_GHICA,
								_hoops_RHICA,
								_hoops_PHICA,
								_hoops_IHICA,
								_hoops_HGCCA,
								_hoops_SSICA,
								_hoops_RCHCA,
								_hoops_SCPPP,
								_hoops_RIPPP,
								_hoops_PIPPP,
								any_vertex_attributes,
								_hoops_SIPPP,
								_hoops_SHHCA,
								geometry_options,
								bounding;

#	define		_hoops_RIHCA		(-1)
#	define		_hoops_GIHCA	0
#	define		_hoops_AIHCA		1
	int							_hoops_RAIHR,
								_hoops_PIHCA;

	struct {
		bool						_hoops_PHHCA,
									point,
									_hoops_HHHCA,
									area;
	}							_hoops_CGR;
	struct {
		bool						_hoops_PAGI,
									_hoops_PRHH,
									face_patterns,
									_hoops_AIPPP,
									_hoops_ASHA,
									_hoops_RSHA,
									_hoops_HIPPP,
									_hoops_IIPPP,
									_hoops_CIPPP,
									_hoops_GCPPP,
									_hoops_RCPPP,
									_hoops_ACPPP,
									_hoops_PCPPP,
									_hoops_ICHA,
									_hoops_ACICA,
									_hoops_HCPPP,
									_hoops_ICPPP,
									_hoops_CCPPP;
	}							_hoops_RGHIR;

	struct {
		_hoops_ACHR					_hoops_AAICA;
		_hoops_ACHR					_hoops_RGP;
#	define		_hoops_HPICA	0x1
#	define		_hoops_GPHCA		0x2
#	define		_hoops_RHPPP			0x3
		int							_hoops_RAHCA;
#	define		_hoops_PPHCA		0x1
#	define		_hoops_HPHCA		0x2
#	define		_hoops_AHPPP			0x3
		int							_hoops_APHCA;
#	define		_hoops_CPHCA			0x1
#	define		_hoops_SPHCA			0x2
#	define		_hoops_PHPPP			0x3
		int							_hoops_IPHCA;
		struct {
			_hoops_PCARP					flags;
			_hoops_PCARP					values;
		}							_hoops_PAICA;
		struct {
			_hoops_CGSP			mask;
			short						_hoops_APH;
		}								heuristics;
		_hoops_SAPAP					_hoops_CAICA;
		struct {
			Color_Object				mask;
			_hoops_ARGRA			_hoops_HAA[_hoops_IIGRA];
			int							_hoops_GSHCA[_hoops_IIGRA];
		}							color;
		struct {
			_hoops_GHGI					_hoops_ASHCA;
			_hoops_GHGI					simple;
			_hoops_GHGI					_hoops_HSHCA;
			_hoops_PIGRA				locks;
			short						_hoops_SSHCA;
			_hoops_PPAAP				_hoops_RGICA;
			_hoops_GPCRP			_hoops_CGICA;
			_hoops_RRPHA					_hoops_GRICA;
			int							geometry;
			_hoops_GICRP		_hoops_IIAIR;
			_hoops_IHGAP			_hoops_APPI;
			_hoops_HIGAP			_hoops_PSRIR;
			_hoops_CCGAP			_hoops_GAICA;
			_hoops_ASSRP			_hoops_PRIGA;
			_hoops_HGGAP			_hoops_GHSS;
			int							_hoops_PGICA;
		}							_hoops_RSHCA;
		struct {
			int							count;
			int *						_hoops_GPICA;
		}							user_options;
		struct {
			int							count;
			int *						_hoops_GPICA;
		}							conditions;
		struct {
			int							count;
			int *						_hoops_GPICA;
		}							_hoops_PPICA;
		struct {
			int							count;
			int *						_hoops_GPICA;
		}							callbacks;
	}							_hoops_GAHCA;

	bool						_hoops_SIHCA;
};


/*
 * _hoops_SCHGR _hoops_GSSRS (_hoops_IGI _hoops_IH _hoops_RSSRS _hoops_GIPHR)
 */
struct _hoops_ASSRS {
	/* _hoops_ARP _hoops_RRGCC _hoops_GRP _hoops_RGR */
#define _hoops_PSSRS		256
	char		_hoops_HSSRS[_hoops_PSSRS];

	/* _hoops_RHPP _hoops_RCSP _hoops_IRGAH _hoops_RSIRR */
#define _hoops_ISSRS			5
#define _hoops_CSSRS		256
	char		_hoops_SSSRS[_hoops_ISSRS][_hoops_CSSRS+1];

	/* _hoops_RCRAH _hoops_RARP _hoops_PPSR */
	bool	(HC_CDECL * _hoops_GGGAS) (_hoops_GGAGR alter *_hoops_GHRI, int request);

	/* _hoops_RGGAS _hoops_RARP _hoops_PPSR */
	bool	(HC_CDECL * _hoops_AGGAS) (_hoops_GGAGR alter *_hoops_GHRI, int request);

	/* _hoops_SRHSI, _hoops_PGGAS, _hoops_PAR _hoops_HRGAI */
#define _hoops_HGGAS			0x400
	short		_hoops_IGGAS;

	/* _hoops_CGGAS _hoops_SGGAS _hoops_PAPA */
	unsigned char		_hoops_GRGAS;
	unsigned char		_hoops_RRGAS;

	/* _hoops_ACIPR _hoops_HIISC _hoops_GIPHR _hoops_GSGR */
#define _hoops_ARGAS		15
#define _hoops_PRGAS	"$HDIRCNAME$"
	char		_hoops_HRGAS[_hoops_ARGAS];

	/* _hoops_PCPA _hoops_IPAHR _hoops_PPR _hoops_RGGIR/_hoops_IISGA _hoops_AA _hoops_SR _hoops_ARAS _hoops_GPP? */
	char		_hoops_IRGAS[HK_PLATFORM_LEN];

	/* _hoops_RHPP _hoops_AAP */
#define _hoops_CRGAS		0
	short		options;

	/* _hoops_RRGR _hoops_AIGHH _hoops_PAR _hoops_CSPP */
#ifndef _hoops_SRGAS
#	define _hoops_SRGAS				"unknown"
#endif
	char		_hoops_CIPAH[_hoops_ARGAS];

	/* _hoops_RHPP _hoops_GCPGH _hoops_CRSRR */
#define _hoops_GAGAS			24
	char		_hoops_RAGAS[_hoops_GAGAS];
};

#define IDENTIFY_HDI_DRIVER(name,_hoops_APRPR,_hoops_RHSRR,_hoops_AAGAS) \
local _hoops_ASSRS const  _hoops_PAGAS = { \
							name, \
							{_hoops_RHSRR, "", "", "", ""}, \
							_hoops_APRPR, \
							_hoops_APRPR, \
							_hoops_HGGAS, \
							HOOPS_VERSION - 256, \
							HOOPS_SUBVERSION, \
							_hoops_PRGAS, \
							HK_PLATFORM, \
							_hoops_CRGAS, \
							_hoops_SRGAS, \
							_hoops_AAGAS \
						}

End_HOOPS_Namespace;

#define _hoops_HCSRS
#endif
