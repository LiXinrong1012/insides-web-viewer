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
 * $Id: obf_tmp.txt 1.158 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "hversion.h"
#include "database.h"
#include "filedata.h"
#include "adt.h"
#include "hpserror.h"
#include "task_queue.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"



local bool _hoops_RACHS (
	char const *		in,
	_hoops_HCRPR *				_hoops_PAGR) {

	if (!HI_Show_Environment (in, _hoops_PAGR))
		return false;
	else
		return _hoops_PAGR->length > 0;
}

local _hoops_SRHSR		picture = _hoops_GRRCR ("picture");
local _hoops_SRHSR		locater = _hoops_GRRCR ("locater");
local _hoops_SRHSR		keyboard = _hoops_GRRCR ("keyboard");
local _hoops_SRHSR		_hoops_AACHS = _hoops_GRRCR ("hardcopy");

									

GLOBAL_FUNCTION void HI_Interpret_Environment (
	_hoops_AIGPR *	_hoops_RIGC,
	bool					_hoops_GICIH) {
	_hoops_HCRPR					name;
	char *					buf;
	_hoops_CRCP *				_hoops_SRCP;

	if (BIT (HOOPS_WORLD->system_flags, _hoops_CSCPP))
		return;

	if (*HI_Look_Up_Alias (_hoops_RIGC, (char *)picture.text, picture.length) != null) {
		/* _hoops_AIAH _hoops_PAPR -- _hoops_PIHA _hoops_SHH _hoops_IHCHC _hoops_RAS _hoops_IRS _hoops_AASA _hoops_IS _hoops_IPPPR
		 *	 _hoops_PGAP _hoops_ARP ?_hoops_SICRH _hoops_GAR _hoops_RH _hoops_CPPPR _hoops_SRS _hoops_AHAP.
		 * _hoops_PRRAR _hoops_RRP _hoops_IS _hoops_ARPR _hoops_SCH & _hoops_HPPR _hoops_PACHS _hoops_HA.
		 */
		PUSHNAME(_hoops_RIGC);
		HC_Create_Segment ("?picture");
		POPNAME(_hoops_RIGC);

		if (_hoops_RACHS ("HOOPS_PICTURE_OPTIONS", &name)) {
			_hoops_SRCP = HI_One_Segment_Search (_hoops_RIGC, "?picture", true);
			if (_hoops_SRCP != null && _hoops_SRCP->owner->type == _hoops_IRCP) {
				PUSHNAME(_hoops_RIGC);
				ALLOC_ARRAY(buf, name.length+1, char);
				HC_Open_Segment("?picture/^");
				HC_Set_Driver_Options (Sprintf_N (buf, "%n", &name));
				HC_Close_Segment();
				FREE_ARRAY(buf, name.length+1, char);
				POPNAME(_hoops_RIGC);
			}
			_hoops_RGAIR (name);
		}
	}
	else if (!_hoops_RACHS ("HOOPS_PICTURE", &name)) {
		if (BIT (HOOPS_WORLD->_hoops_SAPPR, _hoops_GPPPR)) {
			/* _hoops_GRH _hoops_AGIR -- _hoops_RGR _hoops_PIHA _hoops_SHH _hoops_PIGS _hoops_GAR _hoops_IRS _hoops_GCIH _hoops_HII _hoops_ASSA _hoops_IRS
			 *	 _hoops_IPPPR.	_hoops_PS _hoops_HHGC _hoops_IS _hoops_ASSS _hoops_RH _hoops_AGIR _hoops_CAS ?_hoops_SICRH _hoops_HRGR
			 *	 _hoops_IHGS _hoops_PAPR _hoops_GAR _hoops_RH _hoops_SRS _hoops_AASA _hoops_CRGR _hoops_IRISR, _hoops_HIS _hoops_ARI _hoops_SR _hoops_GRS
			 *	 _hoops_HSGR _hoops_SCH _hoops_PPR _hoops_IPPPR _hoops_GRS _hoops_ISPR _hoops_ISSC _hoops_SPHR.
			 */
		}
		else {
#if 0
			ALLOC_ARRAY(buf, 4096, char);
			Sprintf_S (buf,
					   "'?Picture' will have a default value of %s",
					   HK_DEFAULT_PICTURE);
		
			_hoops_PHPGR (HEC_DRIVER, HES_HOOPS_PICTURE_UNDEFINED,
				"No translation for environment variable 'HOOPS_PICTURE' -",
				buf);	
			FREE_ARRAY(buf, 4096, char);
#endif
			HOOPS_WORLD->_hoops_SAPPR |= _hoops_GPPPR;

			PUSHNAME(_hoops_RIGC);
			HI_Copy_Chars_To_Name (HK_DEFAULT_PICTURE, &name);
			ALLOC_ARRAY(buf, name.length+256, char);
			HC_Define_Alias ("?picture", Sprintf_N (buf, "?driver/%n", &name));
			FREE_ARRAY(buf, name.length+256, char);
			HC_Create_Segment ("?picture");
			POPNAME(_hoops_RIGC);
			_hoops_RGAIR (name);
		}
	}
	else {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Define_Alias ("?picture", Sprintf_N (buf, "?driver/%n", &name));
		FREE_ARRAY(buf, name.length+256, char);
		HC_Create_Segment ("?picture");
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);

		if (_hoops_RACHS ("HOOPS_PICTURE_OPTIONS", &name)) {
			_hoops_SRCP = HI_One_Segment_Search (_hoops_RIGC, "?picture", true);
			if (_hoops_SRCP != null && _hoops_SRCP->owner->type == _hoops_IRCP) {
				PUSHNAME(_hoops_RIGC);
				ALLOC_ARRAY(buf, name.length+256, char);
				HC_Open_Segment("?picture/^");
				HC_Set_Driver_Options (Sprintf_N (buf, "%n", &name));
				HC_Close_Segment();
				FREE_ARRAY(buf, name.length+256, char);
				POPNAME(_hoops_RIGC);
			}
			_hoops_RGAIR (name);
		}
	}
	HOOPS_WORLD->_hoops_SAPPR |= _hoops_GPPPR;

	if (_hoops_GICIH)
		return;


	if (HOOPS_WORLD->_hoops_GRGHP.length == 0 &&
		!HI_Show_Environment ("HOOPS_APPLICATION", &HOOPS_WORLD->_hoops_GRGHP)) {
		(void)HI_Find_Application_Name (&HOOPS_WORLD->_hoops_GRGHP);
	}

	if (* HI_Look_Up_Alias (_hoops_RIGC, (char *)locater.text, locater.length) == null) {
		if (!_hoops_RACHS ("HOOPS_LOCATER", &name)) {
			PUSHNAME(_hoops_RIGC);
			HC_Define_Alias ("?locater", "?picture");
			POPNAME(_hoops_RIGC);
		}
		else {
			PUSHNAME(_hoops_RIGC);
			ALLOC_ARRAY(buf, name.length+256, char);
			HC_Define_Alias ("?locater", Sprintf_N (buf, "?driver/%n", &name));
			FREE_ARRAY(buf, name.length+256, char);
			HC_Create_Segment ("?locater");
			POPNAME(_hoops_RIGC);
			_hoops_RGAIR (name);
		}
	}

	if (* HI_Look_Up_Alias (_hoops_RIGC, (char *)keyboard.text, keyboard.length) == null) {
		if (!_hoops_RACHS ("HOOPS_KEYBOARD", &name)) {
			PUSHNAME(_hoops_RIGC);
			HC_Define_Alias ("?keyboard", "?picture");
			POPNAME(_hoops_RIGC);
		}
		else {
			PUSHNAME(_hoops_RIGC);
			ALLOC_ARRAY(buf, name.length+256, char);
			HC_Define_Alias ("?keyboard", Sprintf_N (buf, "?driver/%n", &name));
			FREE_ARRAY(buf, name.length+256, char);
 			HC_Create_Segment ("?keyboard");
			POPNAME(_hoops_RIGC);
			_hoops_RGAIR (name);
		}
	}

	if (* HI_Look_Up_Alias (_hoops_RIGC, (char *)_hoops_AACHS.text, _hoops_AACHS.length) == null) {
		if (_hoops_RACHS ("HOOPS_HARDCOPY", &name)) {
			PUSHNAME(_hoops_RIGC);
			ALLOC_ARRAY(buf, name.length+256, char);
			HC_Define_Alias ("?hardcopy", Sprintf_N (buf, "?driver/%n", &name));
			FREE_ARRAY(buf, name.length+256, char);
			POPNAME(_hoops_RIGC);
			_hoops_RGAIR (name);

			if (_hoops_RACHS ("HOOPS_HARDCOPY_OPTIONS", &name)) {
				PUSHNAME(_hoops_RIGC);
				HC_Create_Segment ("?hardcopy");
				POPNAME(_hoops_RIGC);
				_hoops_SRCP = HI_One_Segment_Search (_hoops_RIGC, "?hardcopy", true);

				if (_hoops_SRCP != null && _hoops_SRCP->owner->type == _hoops_IRCP) {
					PUSHNAME(_hoops_RIGC);
					ALLOC_ARRAY(buf, name.length+256, char);
					HC_Open_Segment("?hardcopy/^");
					HC_Set_Driver_Options (Sprintf_N (buf, "%n", &name));
					HC_Close_Segment();
					FREE_ARRAY(buf, name.length+256, char);
					POPNAME(_hoops_RIGC);
				}

				PUSHNAME(_hoops_RIGC);
				HC_Delete_Segment ("?hardcopy");
				POPNAME(_hoops_RIGC);
				_hoops_RGAIR (name);
			}
		}
	}

	if (_hoops_RACHS ("HOOPS_SYSTEM_OPTIONS", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);		
		HC_Define_System_Options (Sprintf_N (buf, "%n", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	if (_hoops_RACHS ("HOOPS_LICENSE", &name)) {
#if 0
		int		_hoops_HACHS;

		_hoops_HACHS = HOOPS_WORLD->_hoops_HPSPP;
#endif

		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Define_System_Options (Sprintf_N (buf, "license=(%n)", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);

#if 0
#ifndef _hoops_IGSPR
		if (!ALLBITS (_hoops_HACHS, HOOPS_WORLD->_hoops_HPSPP) &&
			!HOOPS_WORLD->_hoops_IPSPP) {
			char const		*_hoops_SSACR[9];

			_hoops_SSACR[0]	= "Your HOOPS licensing option has been set through the use";
			_hoops_SSACR[1]	= "of the HOOPS_LICENSE environment variable.  This method for";
			_hoops_SSACR[2]	= "setting the licensing option is permitted ONLY for internal";
			_hoops_SSACR[3]	= "application development.	 For distribution of any application";
			_hoops_SSACR[4]	= "using HOOPS, you MUST set the licensing option using the";
			_hoops_SSACR[5]	= "Define_System_Options HOOPS function, and NOT with any";
			_hoops_SSACR[6]	= "environment variables.  Your HOOPS licensing agreement";
			_hoops_SSACR[7]	= "explicity prohibits you from revealing your HOOPS licensing";
			_hoops_SSACR[8]	= "keys to anyone outside the scope of the original agreement.";

			HI_Generate_Untrappable_Error (null, HEC_SYSTEM, HES_INVALID_LICENSE, 1, 9, _hoops_SSACR);
		}
#endif
#endif
	}

	HC_Open_Segment("/");

	if (_hoops_RACHS ("HOOPS_DRIVER_OPTIONS", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Set_Driver_Options (Sprintf_N (buf, "%n", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	if (_hoops_RACHS ("HOOPS_HEURISTICS", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Set_Heuristics (Sprintf_N (buf, "%n", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	if (_hoops_RACHS ("HOOPS_RENDERING_OPTIONS", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Set_Rendering_Options (Sprintf_N (buf, "%n", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	if (_hoops_RACHS ("HOOPS_COLORS", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Set_Color (Sprintf_N (buf, "%n", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	if (_hoops_RACHS ("HOOPS_VISIBILITY", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Set_Visibility (Sprintf_N (buf, "%n", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	if (_hoops_RACHS ("HOOPS_TEXT_FONT", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Set_Text_Font (Sprintf_N (buf, "%n", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	if (_hoops_RACHS ("HOOPS_FONT_DIRECTORY", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Define_System_Options (Sprintf_N (buf, "font directory=(%n)", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	if (_hoops_RACHS ("HOOPS_DRIVER_DIRECTORY", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Define_System_Options (Sprintf_N (buf, "driver directory=(%n)", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	if (_hoops_RACHS ("HOOPS_METAFILE_DIRECTORY", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Define_System_Options (Sprintf_N (buf, "metafile directory=(%n)", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}
	else if (_hoops_RACHS ("HOOPS_METAFILES", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);		
		HC_Define_System_Options (Sprintf_N (buf, "metafile directory=(%n)", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	if (_hoops_RACHS ("HOOPS_DRIVER_CONFIG_FILE", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Define_System_Options (Sprintf_N (buf, "driver config file=(%n)", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	if (_hoops_RACHS ("HOOPS_CODE_GENERATION_DIRECTORY", &name)) {
		PUSHNAME(_hoops_RIGC);
		ALLOC_ARRAY(buf, name.length+256, char);
		HC_Define_System_Options (Sprintf_N (buf, "code generation directory=(%n)", &name));
		FREE_ARRAY(buf, name.length+256, char);
		POPNAME(_hoops_RIGC);
		_hoops_RGAIR (name);
	}

	HC_Close_Segment();
}


local void _hoops_IACHS (
	int					severity,
	int					category,
	int					specific,
	int					_hoops_GHSPP) {
	_hoops_IGHGP *				_hoops_SSGGA = HOOPS_WORLD;
	_hoops_CPSPP *		control;

	ZALLOC (control, _hoops_CPSPP);
	control->category = category;
	control->specific = specific;
	control->_hoops_GHSPP = _hoops_GHSPP | _hoops_RHSPP;
	control->state = _hoops_GHSPP;

	control->next = _hoops_SSGGA->_hoops_PSSPP[severity];
	_hoops_SSGGA->_hoops_PSSPP[severity] = control;
}



local void _hoops_CACHS (void) {
	union _hoops_SACHS {
		struct {
			short			first,
							_hoops_IAGRA;
		}				_hoops_AGRIH;
		Integer32		_hoops_PCRSP;
	}				_hoops_GPCHS;

	_hoops_GPCHS._hoops_PCRSP = 1;

	if (HOOPS_BIGENDIAN && !(_hoops_GPCHS._hoops_AGRIH.first == 0 && _hoops_GPCHS._hoops_AGRIH._hoops_IAGRA == 1))
		HE_ERROR2 (HEC_INTERNAL_ERROR, HES_BIG_ENDIAN_SHOULD_BE_FALSE,
				"'HOOPS_BIGENDIAN' is TRUE -",
				   "should probably be set FALSE on this hardware");

	if (!HOOPS_BIGENDIAN && !(_hoops_GPCHS._hoops_AGRIH.first == 1 && _hoops_GPCHS._hoops_AGRIH._hoops_IAGRA == 0))
		HE_ERROR2 (HEC_INTERNAL_ERROR, HES_BIG_ENDIAN_SHOULD_BE_TRUE,
				"'HOOPS_BIGENDIAN' is FALSE -",
				   "should probably be set TRUE on this hardware");
}


#define _hoops_RPCHS(type1, _hoops_IASAR, _hoops_APCHS, _hoops_CASAR) \
		((char *)&type1._hoops_IASAR - (char *)&type1  !=  (char *)&_hoops_APCHS._hoops_CASAR - (char *)&_hoops_APCHS)

local void _hoops_PPCHS (void) {
	Subsegment		_hoops_SSGPR;
	_hoops_CRCP			segment;
	_hoops_PGRPR			include;
	Xref			_hoops_AHICA;
	Style			style;

	if (_hoops_RPCHS (_hoops_SSGPR, priority, segment, priority))
		ASSERT (0);
	else if (_hoops_RPCHS (_hoops_SSGPR, priority, include, priority))
		ASSERT (0);
	else if (_hoops_RPCHS (_hoops_AHICA, _hoops_IGRPR, include, _hoops_IGRPR))
		ASSERT (0);
	else if (_hoops_RPCHS (_hoops_AHICA, _hoops_IGRPR, style, _hoops_IGRPR))
		ASSERT (0);
	else if (_hoops_RPCHS (_hoops_AHICA, _hoops_GRRPR, include, _hoops_GRRPR))
		ASSERT (0);
	else if (_hoops_RPCHS (_hoops_AHICA, _hoops_GRRPR, style, _hoops_GRRPR))
		ASSERT (0);
	else if (_hoops_RPCHS (_hoops_AHICA, _hoops_SHAIR, include, _hoops_SHAIR))
		ASSERT (0);
	else if (_hoops_RPCHS (_hoops_AHICA, _hoops_SHAIR, style, _hoops_SHAIR))
		ASSERT (0);
	else 
		return;

	/* _hoops_ARARH */
	_hoops_HRAIR (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
			  "subsegment structure misalignment");

}


GLOBAL_FUNCTION void HI_Start_Hoops (
	char const *	_hoops_SCPGA) {
	int				_hoops_HPCHS;
	char			string[256];

	if (!HOOPS_WORLD) 
		HI_Init_Internal_Data ();		/* _hoops_ARP _hoops_GH _hoops_RH _hoops_HGSI _hoops_HRPR */

	HOOPS_WORLD->_hoops_GCSPP = true;
	HOOPS_WORLD->_hoops_PRRPH = true;
	HOOPS_WORLD->_hoops_PGSCA->thread_id = THREAD_ID();
	HOOPS_WORLD->_hoops_PGSCA->_hoops_RCSPP = _hoops_SCPGA;

	/* _hoops_PPGS _hoops_PAH _hoops_HA _hoops_SHH _hoops_PSPP... */

	// _hoops_IPCHS/_hoops_IPCHS _hoops_CGH _hoops_RGAR _hoops_SHH _hoops_HRCRA _hoops_HPP _hoops_CASRR-_hoops_GHIR _hoops_CPCHS _hoops_RRGR
	_hoops_IACHS (_hoops_HCSPP,		HEC_UNDEFINED,	HES_UNDEFINED,						_hoops_ACCPP);
	_hoops_IACHS (_hoops_ICSPP,	HEC_DRIVER,		HES_FORCEBW_WITH_SOFTWARE_Z_BUFFER,	_hoops_ACCPP);
	_hoops_IACHS (_hoops_ICSPP,	HEC_TRISTRIP,	HES_REQUIRES_COLOR_MAP,				_hoops_ACCPP);
	_hoops_IACHS (_hoops_ICSPP,	HEC_RENDERING,	HES_NONWINDOWED_HSR,				_hoops_ACCPP);


	HI_Ensure_Definition_Set(HOOPS_WORLD->_hoops_PGSCA);

	PUSHNAME(HOOPS_WORLD->_hoops_PGSCA);
	_hoops_AASAH (HOOPS_WORLD->_hoops_PGSCA, "Hoops Startup (internal)");
	PUSHNAME(HOOPS_WORLD->_hoops_PGSCA);		/* (_hoops_GRR _hoops_IIGR _hoops_RH _hoops_HSPR _hoops_GRS _hoops_AA _hoops_IRS _hoops_IISPP) */

	/* _hoops_ARP _hoops_RIARR _hoops_IASAH &_hoops_GSGGR. */
	_hoops_AASAH (HOOPS_WORLD->_hoops_PGSCA, "System-specific Start (internal)");
	HI_Start_System_Specific (HOOPS_WORLD->_hoops_PGSCA);
	HC_Define_Driver_Config("*", "*", "*", "reset");
	HOOPS_WORLD->_hoops_GAGHP = HOOPS_WORLD->_hoops_CIIPA;

	_hoops_AASAH (HOOPS_WORLD->_hoops_PGSCA, "Init Time (internal)");
	HI_Init_Time ();

	// _hoops_AISSA _hoops_GSSHR _hoops_PIHA _hoops_RCPS _hoops_RAS _hoops_IHPI _hoops_GHIR _hoops_PPR _hoops_PPGS
	HOOPS_WORLD->_hoops_ACARR = NEW(_hoops_SRIAP)(2);

	_hoops_AASAH (HOOPS_WORLD->_hoops_PGSCA, "Default Handlers (internal)");
	HC_Define_Error_Handler ((_hoops_IRPCR)HI_Make_It_Fatal);		/* _hoops_CGH _hoops_SHH _hoops_SRS! */
	HC_Define_Exit_Handler ((_hoops_IRPCR)HC_Reset_System);	/* _hoops_CGH _hoops_SHH _hoops_GIAP! */

#ifndef DISABLE_CALLBACKS
	HC_Define_Callback_Name ("null", nullroutine);
#endif

	_hoops_AASAH (HOOPS_WORLD->_hoops_PGSCA, "Consistency Checking (internal)");
	_hoops_CACHS ();
	_hoops_PPCHS ();
	HI_Show_Type_Name (_hoops_IRCP, string, -1);

	_hoops_AASAH (HOOPS_WORLD->_hoops_PGSCA, "Define Default Colors (internal)");
	HI_Define_Default_Colors (HOOPS_WORLD->_hoops_PGSCA);

	_hoops_AASAH (HOOPS_WORLD->_hoops_PGSCA, "Define Fonts (internal)");
	HI_Init_Stencil_Cache ();
	HI_Define_Internal_Fonts (HOOPS_WORLD->_hoops_PGSCA);

	HOOPS_WORLD->_hoops_PPAPA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_IGGGI)(HOOPS_WORLD->memory_pool, 1024);

	HC_Create_Segment ("/");
	HI_Set_Default_Attributes (HOOPS_WORLD->_hoops_PGSCA);		/* _hoops_GACC _hoops_RSSAR _hoops_CAGH "/" */

	HOOPS_WORLD->_hoops_SARHP[0]._hoops_RPGHP = HOOPS_WORLD->root;

	/* _hoops_AGCR _hoops_IRACC _hoops_CHR _hoops_GHSAR _hoops_ICIC, _hoops_HIS _hoops_HCPRA _hoops_HHSP _hoops_IPAC */
	_hoops_HPCHS = HOOPS_WORLD->_hoops_SAPPR;
	HOOPS_WORLD->_hoops_SAPPR |= _hoops_GPPPR;
		HC_Define_Alias ("?driver", "/driver");
		HC_Define_Alias ("?null", "?driver/null");

		HC_Define_Alias ("?home", "/");

		HC_Define_Alias ("?include library", "/include library");
		HC_Define_Alias ("?style library", "/style library");
	HOOPS_WORLD->_hoops_SAPPR = _hoops_HPCHS;

	HC_Create_Segment ("?include library");
	HC_Create_Segment ("?style library");

	_hoops_AASAH (HOOPS_WORLD->_hoops_PGSCA, "Drivers' Start (internal)");
	HD_Start_Drivers (HOOPS_WORLD->_hoops_PGSCA);

	/* _hoops_IPCA _hoops_IS _hoops_IRGH _hoops_CIPH */
	_hoops_AASAH (HOOPS_WORLD->_hoops_PGSCA, "Local Start (internal)");

	HC_Define_Error_Handler ((_hoops_IRPCR)HC_Report_Error); /* _hoops_CICA _hoops_IAPR */
	HC_UnDefine_Error_Handler ((_hoops_IRPCR)HI_Make_It_Fatal);

	POPNAME(HOOPS_WORLD->_hoops_PGSCA);	/* _hoops_PSP _hoops_RRI _hoops_SPCHS */

	HI_Interpret_Environment (HOOPS_WORLD->_hoops_PGSCA, false);

	// _hoops_PS _hoops_HA _hoops_GHCHS _hoops_SPRS-_hoops_PIGHH _hoops_GAR _hoops_HPHR _hoops_HAACI _hoops_RRP _hoops_IS _hoops_HIISR _hoops_CCA _hoops_SGHC _hoops_PPR _hoops_RHCHS _hoops_HAACI
	// _hoops_SPGA'_hoops_RA _hoops_SGS _hoops_PGCPR (_hoops_PPR _hoops_PAH _hoops_SAHR _hoops_AA _hoops_AHCHS("?_hoops_RPISR); _hoops_PHCHS(_hoops_GPP); _hoops_RPP _hoops_PIASR)
	// _hoops_IPPSA->_hoops_HHCHS = _hoops_RCPP;		/* _hoops_ARRS _hoops_RHASR (_hoops_IHCHS _hoops_HCPH) _hoops_IHPPP _hoops_SCH _hoops_GPP */

	if (BETA_TEST &&
		(HOOPS_WORLD->_hoops_PAHGI ||
		 BIT (HOOPS_WORLD->error_mask, 1 /* _hoops_SRRHS */))) {
		/* _hoops_RRP _hoops_IS _hoops_CHASA _hoops_CHCHS "_hoops_PSP _hoops_SIHC" _hoops_HRP _hoops_HAH */
		Error_Mask			_hoops_IRSAH = HOOPS_WORLD->error_mask;

		HOOPS_WORLD->error_mask = false;

		PUSHNAME(HOOPS_WORLD->_hoops_PGSCA);
		HC_Print_Version ();
		POPNAME(HOOPS_WORLD->_hoops_PGSCA);

		HOOPS_WORLD->error_mask = _hoops_IRSAH;
	}
	else if (BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_HGHGI) &&
			 HOOPS_WORLD->_hoops_PAHGI) {
		PUSHNAME(HOOPS_WORLD->_hoops_PGSCA);
		HC_Print_Version ();
		POPNAME(HOOPS_WORLD->_hoops_PGSCA);
	}

	POPNAME(HOOPS_WORLD->_hoops_PGSCA);	/* _hoops_PSP _hoops_RRI "_hoops_RHAR _hoops_GASCA" */

	HOOPS_WORLD->_hoops_PRRPH = false;
}


/*
 * _hoops_HGI _hoops_CSAP _hoops_RAARH _hoops_GAGCI _hoops_PGGA _hoops_IIGR _hoops_IRS _hoops_CAGRH _hoops_GGR _hoops_SHCHS _hoops_IHRPR.
 * _hoops_HHIGR _hoops_SSCP _hoops_RPII _hoops_RAAP _hoops_GAR _hoops_IRS _hoops_GAGCI _hoops_PGGA _hoops_SCH _hoops_PHPP _hoops_GGR _hoops_GICHS._hoops_RICHS,
 * _hoops_PPR _hoops_SR _hoops_HHGC _hoops_IS _hoops_GRHP _hoops_RH _hoops_AICHS _hoops_IH _hoops_RH _hoops_PSCSR _hoops_ASCSR _hoops_RH
 * _hoops_PSHR _hoops_ARHI _hoops_PICHS.
 */
GLOBAL_FUNCTION void HI_Make_It_Fatal (
	int							category,
	int							specific,
	int							severity,
	int							msgc,
	char const * const *		msgv,
	int							_hoops_HRSAH,
	char const * const *		_hoops_PRSAH) {
	UNREFERENCED (category);
	UNREFERENCED (specific);

	HC_Report_Error (HEC_DRIVER, HES_FATAL_ERROR,
					 severity == 0 ? 0 : 3, msgc, msgv, _hoops_HRSAH, _hoops_PRSAH);
	HI_Error_Exit ();
}


GLOBAL_FUNCTION void HI_Ensure_Definition_Set (
	_hoops_AIGPR *	_hoops_RIGC) {
	_hoops_CPPGI *		_hoops_HICHS = HOOPS_WORLD->_hoops_SARHP;
	int						_hoops_IICHS = HOOPS_WORLD->_hoops_CARHP;
	int						id;
	int						i;

	id = _hoops_RIGC->_hoops_IAPCR;

	if (id >= _hoops_IICHS) {
		HOOPS_WORLD->_hoops_CARHP = id + 1;

		ZALLOC_ARRAY(HOOPS_WORLD->_hoops_SARHP, HOOPS_WORLD->_hoops_CARHP, _hoops_CPPGI);

		if (_hoops_IICHS > 0) {
			_hoops_AIGA(_hoops_HICHS, _hoops_IICHS, _hoops_CPPGI, HOOPS_WORLD->_hoops_SARHP);
			FREE_ARRAY(_hoops_HICHS, _hoops_IICHS, _hoops_CPPGI);

			/* _hoops_GGCH _hoops_RHGS _hoops_CICHS */
			for (i=0; i<_hoops_IICHS; i++) {
				HOOPS_WORLD->_hoops_SARHP->_hoops_AIHPP->backlink = &HOOPS_WORLD->_hoops_SARHP->_hoops_AIHPP;
			}

			for (i=_hoops_IICHS; i<=id; i++) {
				_hoops_RIGC->_hoops_IAPCR = i;

				HOOPS_WORLD->_hoops_SARHP[i]._hoops_RPGHP = HOOPS_WORLD->root;

#ifndef DISABLE_CALLBACKS
				PUSHNAME(_hoops_RIGC);
				HC_Define_Callback_Name ("null", nullroutine);
				POPNAME(_hoops_RIGC);
#endif
				HI_Define_Default_Colors (_hoops_RIGC);

				HI_Define_Internal_Fonts (_hoops_RIGC);

				PUSHNAME(_hoops_RIGC);
				HC_Define_Alias ("?driver", "/driver");
				HC_Define_Alias ("?null", "?driver/null");
				HC_Define_Alias ("?home", "/");
				HC_Define_Alias ("?include library", "/include library");
				HC_Define_Alias ("?style library", "/style library");
				POPNAME(_hoops_RIGC);
			}

			_hoops_RIGC->_hoops_IAPCR = id;
		}
	}
}


#include "hc_standalone_proto.h"
#include "hc_legacy.c"

