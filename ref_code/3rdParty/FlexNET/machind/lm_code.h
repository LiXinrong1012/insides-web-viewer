/******************************************************************************
 *

 *
 *          Copyright (c) 1990-2009 Flexera Software, Inc. All Rights Reserved.
 *      This software has been provided pursuant to a License Agreement
 *      containing restrictions on its use.  This software contains
 *      valuable trade secrets and proprietary information of
 *      Flexera Software, Inc. and is protected by law.  It may
 *      not be copied or distributed in any form or medium, disclosed
 *      to third parties, reverse engineered or used in any manner not
 *      provided for in said License Agreement except with the prior
 *      written authorization from Flexera Software, Inc.
 ******************************************************************************
 *
 *      Description:    Used to generate lm_new.o/.obj and by license-
 *                      generators.
 *
 *      Once the kit is "built" (using make or nmake) this file is no longer
 *	needed, but should be stored somewhere safe.
 *
 *	Set the following values:
 *      VENDOR_KEY1-5 		Provided by Flexera Software, Inc.
 *      VENDOR_NAME 		If not evaluating, set to vendor name.
 *      LM_SEED1-3 			Make up 3 32-bit numbers, (or use
 *				'lmrand1 -seed' to make up), keep secret, safe,
 *				and never change.
 *	TRL_KEY1-2 		Provided by Flexera Software, Inc. if TRL used.
 *      LM_STRENGTH: 		If using TRL, set to desired length
 *
 *	Upgrading: 		from version older than 8.1: Copy your
 *				ENCRYPTION_SEEDs from the old lm_code.h file.
 *				Make sure LM_STRENGTH matches, if you were
 *				using LM_STRENGTH
 */

#ifndef LM_CODE_H
#define LM_CODE_H
#include "lm_trl.h"
/*
 * 	Vendor keys:   		Enter keys received from Flexera Software, Inc.
 *				Changing keys has NO impact on license files
 *				(unlike LM_SEEDs).
 */
#define VENDOR_KEY1 0x74ca7b07
#define VENDOR_KEY2 0xefc2f260
#define VENDOR_KEY3 0xd27fb81f
#define VENDOR_KEY4 0x04479306
#define VENDOR_KEY5 0x460155c4
#define TRL_KEY1 0x3f1a5603
#define TRL_KEY2 0x52cf96aa

/*
 * 	Vendor name.  		Leave "demo" if evaluating.  Otherwise,
 *			 	set to your vendor daemon name.
 */
#define VENDOR_NAME "Dream"
/*
 * 	Private SEEDs: 		Make up 3, 8-hex-char numbers, replace and
 *				guard securely.  You can also use the command
 *				'lmrand1 -seed' to make these numbers up.
 */
#define LM_SEED1 0x495bc2f0
#define LM_SEED2 0xcbb8bfd0
#define LM_SEED3 0x83612c57
/*
 *	Pick an LM_STRENGTH:
 */
#define LM_STRENGTH LM_STRENGTH_113BIT
/*
 *			       	LM_STRENGTH Options are
 *			       	LM_STRENGTH_DEFAULT:
 *			      	 Public key protection unused. Use SIGN=
 *			      	 attribute. sign length = 12
 *			       	TRL:
 *			       	LM_STRENGTH_113BIT, LOW:   sign length= 60 chars
 *			       	LM_STRENGTH_163BIT, MEDIUM:sign length= 84 chars
 *			       	LM_STRENGTH_239BIT, HIGH:  sign length=120 chars
 *				Pre-v7.1:
 *			       	LM_STRENGTH_LICENSE_KEY:   Use old license-key.
 *			       	If you're upgrading from
 *			       	pre-v7.1, and want no changes, set this to
 *			       	LM_STRENGTH_LICENSE_KEY.
*/
/*
 *	TRL Keys:		Provided by Flexera Software, Inc., if TRL is used.
 * 				Be sure to set LM_STRENGTH to
 * 				LM_STRENGTH_DEFAULT, above, if TRL_KEYs are zero.
 */


#include "lm_code2.h"
#endif /* LM_CODE_H */
