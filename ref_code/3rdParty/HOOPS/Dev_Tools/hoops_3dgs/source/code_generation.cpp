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
 * $Id: obf_tmp.txt 1.47 2010-10-06 19:16:21 jason Exp $
 */

#include "hoops.h"
#include "filedata.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HI_Dump_Code (
	char const		*string) {
#ifndef DISABLE_CODE_GENERATION
	_hoops_HCRPR			_hoops_GGHGA;
	_hoops_HCRPR			_hoops_RGHGA;

	if (HOOPS_WORLD->_hoops_AGHGA != null) {
		int				length;

		length = _hoops_SSGR (string);

		if (HOOPS_WORLD->_hoops_PGHGA) {
			int		_hoops_HGHGA = HOOPS_WORLD->_hoops_ISPPR;

			while (_hoops_HGHGA > 0) {
				int		_hoops_IGIC = _hoops_AHIA (32, _hoops_HGHGA);

				if (!HI_Write_File_Buffer (HOOPS_WORLD->_hoops_AGHGA,
										   "                                ",
										   _hoops_IGIC,
										   &_hoops_GGHGA, &_hoops_RGHGA)) {
					HE_ERROR (HEC_FILE_IO, HES_FILE_IO,
							  Sprintf_NN (null, "%n %n", &_hoops_GGHGA, &_hoops_RGHGA));
					HI_Close_File (HOOPS_WORLD->_hoops_AGHGA, &_hoops_GGHGA, &_hoops_RGHGA);
					HOOPS_WORLD->_hoops_AGHGA = null;
					HOOPS_WORLD->system_flags &= ~_hoops_IGHGA;
					return;
				}
				_hoops_HGHGA -= _hoops_IGIC;
			}
		}

		if (!HI_Write_File_Buffer (HOOPS_WORLD->_hoops_AGHGA,
								   string, length,
								   &_hoops_GGHGA, &_hoops_RGHGA)) {
			HE_ERROR (HEC_FILE_IO, HES_FILE_IO,
					  Sprintf_NN (null, "%n %n", &_hoops_GGHGA, &_hoops_RGHGA));
			HI_Close_File (HOOPS_WORLD->_hoops_AGHGA, &_hoops_GGHGA, &_hoops_RGHGA);
			HOOPS_WORLD->_hoops_AGHGA = null;
			HOOPS_WORLD->system_flags &= ~_hoops_IGHGA;
			return;
		}

		if (string[length-1] == '\n') {
			HOOPS_WORLD->_hoops_PGHGA = true;
			++HOOPS_WORLD->_hoops_CGHGA;
		}
		else
			HOOPS_WORLD->_hoops_PGHGA = false;
	}
	else
		HOOPS_WORLD->system_flags &= ~_hoops_IGHGA;
#endif
}

local void _hoops_SGHGA (void) 
{
	_hoops_HCRPR			name;
	_hoops_HCRPR			_hoops_GGHGA;
	_hoops_HCRPR			_hoops_RGHGA;

	if (HOOPS_WORLD->_hoops_GRHGA.length != 0)
		HI_Copy_Chars_To_Name (Sprintf_ND (null, "%n/code%d.c", 
			&HOOPS_WORLD->_hoops_GRHGA, HOOPS_WORLD->_hoops_RRHGA), &name);
	else
		HI_Copy_Chars_To_Name (Sprintf_D (null, "code%d.c", HOOPS_WORLD->_hoops_RRHGA), &name);

	if (!HI_Open_File (&name, FILE_For_Writing, &HOOPS_WORLD->_hoops_AGHGA, true, &_hoops_GGHGA, &_hoops_RGHGA)) {
		HE_ERROR (HEC_FILE_IO, HES_FILE_IO,
				  Sprintf_NN (null, "%n %n", &_hoops_GGHGA, &_hoops_RGHGA));
		_hoops_RGAIR (_hoops_GGHGA);
		_hoops_RGAIR (_hoops_RGHGA);
		_hoops_RGAIR (name);

		HOOPS_WORLD->_hoops_AGHGA = null;
		HOOPS_WORLD->system_flags &= ~_hoops_IGHGA;
		return;
	}
	_hoops_RGAIR (name);

	HOOPS_WORLD->_hoops_ISPPR = 0;
	HI_Dump_Code ("typedef struct {float x, y, z;} Point;\n");
	HI_Dump_Code ("#define HC_POINT Point\n");
	HI_Dump_Code ("typedef struct {float x, y, z;} Vector;\n");
	HI_Dump_Code ("#define HC_VECTOR Vector\n");
	HI_Dump_Code ("typedef struct {float a, b, c, d;} Plane;\n");
	HI_Dump_Code ("#define HC_PLANE Plane\n");
	HI_Dump_Code ("typedef struct {float red, green, blue;} RGB;\n");
	HI_Dump_Code ("#define HC_RGB RGB\n");
	HI_Dump_Code ("typedef struct {float red, green, blue, alpha;} RGBA;\n");
	HI_Dump_Code ("#define HC_RGBA RGBA\n");

	HI_Dump_Code ("#include \"hc.h\"\n\n");
	HI_Dump_Code ("#include <stdlib.h>\n\n");
	HI_Dump_Code ("extern HC_KEY hx_associate (HC_KEY key, HC_POINTER_SIZED_INT tag, int insert);\n");
	HI_Dump_Code (Sprintf_D (null, "extern int code_chain_%d (void);\n", HOOPS_WORLD->_hoops_RRHGA+1));
	HI_Dump_Code ("#define DEFINE(key, tag) hx_associate (key, tag, 1)\n");
	HI_Dump_Code ("#define LOOKUP(tag) hx_associate (0, tag, 0)\n\n");
	HI_Dump_Code (Sprintf_D (null, "int code_chain_%d (void) {\n", HOOPS_WORLD->_hoops_RRHGA));
	HI_Dump_Code ("	 char	string_buffer[256];\n");
	HI_Dump_Code ("	 float	ff;\n");
	HI_Dump_Code ("	 int	ii;\n");
	HI_Dump_Code ("	 long	ll;\n");
	HI_Dump_Code ("	 HC_KEY key;\n");
	HI_Dump_Code ("	 float	matrix[16];\n\n");
	HOOPS_WORLD->_hoops_CGHGA = 20;
	HOOPS_WORLD->_hoops_ISPPR = 2;
}


GLOBAL_FUNCTION void HI_Start_Code_Generation (void) {
	_hoops_HCRPR			name;
	_hoops_HCRPR			_hoops_GGHGA;
	_hoops_HCRPR			_hoops_RGHGA;

#ifdef DISABLE_CODE_GENERATION
	_hoops_IRPPR ("Code Generation");
#else
	if (HOOPS_WORLD->_hoops_RRHGA == 0) {

		if (HOOPS_WORLD->_hoops_GRHGA.length != 0)
			HI_Copy_Chars_To_Name (Sprintf_N (null, "%n/code.c", &HOOPS_WORLD->_hoops_GRHGA), &name);
		else
	 		HI_Copy_Chars_To_Name ("code.c", &name);

		if (!HI_Open_File (&name, FILE_For_Writing, &HOOPS_WORLD->_hoops_AGHGA, true, &_hoops_GGHGA, &_hoops_RGHGA)) {
			HE_ERROR (HEC_FILE_IO, HES_FILE_IO, Sprintf_NN (null, "%n %n", &_hoops_GGHGA, &_hoops_RGHGA));
			_hoops_RGAIR (_hoops_GGHGA);
			_hoops_RGAIR (_hoops_RGHGA);
			_hoops_RGAIR (name);

			HOOPS_WORLD->_hoops_AGHGA = null;
			HOOPS_WORLD->system_flags &= ~_hoops_IGHGA;
			return;
		}
		_hoops_RGAIR (name);

		HI_Dump_Code ("/* HOOPS Codegen Compile Hints: \n");
		HI_Dump_Code (" * Check end of files for missing lines containing return 0 and closing curly brace. \n");
		HI_Dump_Code (" * Make sure each generated code*.c file is available.  Make this easier by grouping the files \n");
		HI_Dump_Code (" * using the System Option \"code generation directory=c:/mycodegendir/\" or by storing the ");
		HI_Dump_Code (" * path in the environment variable HOOPS_CODE_GENERATION_DIRECTORY.\n");
		HI_Dump_Code (" * If your files are extremely long, you may not be able to debug into the program.  Usually \n");
		HI_Dump_Code (" * this is due to very large allocations for shell points and facelists.  A quick solution \n");
		HI_Dump_Code (" * is to separate these into functions in yet other included files. \n");

		HI_Dump_Code ("typedef struct {float x, y, z;} Point;\n");
		HI_Dump_Code ("#define HC_POINT Point\n");
		HI_Dump_Code ("typedef struct {float x, y, z;} Vector;\n");
		HI_Dump_Code ("#define HC_VECTOR Vector\n");
		HI_Dump_Code ("typedef struct {float a, b, c, d;} Plane;\n");
		HI_Dump_Code ("#define HC_PLANE Plane\n");
		HI_Dump_Code ("typedef struct {float red, green, blue;} RGB;\n");
		HI_Dump_Code ("#define HC_RGB RGB\n");
		HI_Dump_Code ("typedef struct {float red, green, blue, alpha;} RGBA;\n");
		HI_Dump_Code ("#define HC_RGBA RGBA\n");

		HI_Dump_Code ("#include \"hc.h\"\n");
		HI_Dump_Code ("#include <stdlib.h>\n\n");
		HI_Dump_Code ("extern int code_chain_1 (void);\n");
		HI_Dump_Code ("typedef struct key_node {\n");
		HI_Dump_Code ("	 struct key_node *left, *right;\n");
		HI_Dump_Code ("	 HC_KEY					key;\n");
		HI_Dump_Code ("	 HC_POINTER_SIZED_INT	tag;\n");
		HI_Dump_Code ("} Key_Node;\n\n");
		HI_Dump_Code ("static Key_Node *key_table = (Key_Node *)0;\n\n");
		HI_Dump_Code ("HC_KEY hx_associate (HC_KEY key, HC_POINTER_SIZED_INT tag, int insert) {\n");
		HI_Dump_Code ("	 Key_Node **linker = &key_table;\n");
		HI_Dump_Code ("	 if (tag>=0)\n");
		HI_Dump_Code ("	   return (HC_KEY)tag;\n");
		HI_Dump_Code ("	 while (1) {\n");
		HI_Dump_Code ("	   if (*linker == (Key_Node *)0) {\n");
		HI_Dump_Code ("		 if (!insert) return (HC_KEY)-1;\n");
		HI_Dump_Code ("		 *linker = (Key_Node *)malloc (sizeof (Key_Node));\n");
		HI_Dump_Code ("		 (*linker)->key = key;\n");
		HI_Dump_Code ("		 (*linker)->tag = tag;\n");
		HI_Dump_Code ("		 (*linker)->left = (*linker)->right = (Key_Node *)0;\n");
		HI_Dump_Code ("		 return key;\n");
		HI_Dump_Code ("	   }\n");
		HI_Dump_Code ("	   else {\n");
		HI_Dump_Code ("		 Key_Node *node = *linker;\n");
		HI_Dump_Code ("		 if (node->tag == tag) {\n");
		HI_Dump_Code ("		   if (insert) node->key = key;\n");
		HI_Dump_Code ("		   return node->key;\n");
		HI_Dump_Code ("		 } else\n");
		HI_Dump_Code ("		   linker = (node->tag > tag) ? &node->right : &node->left;\n");
		HI_Dump_Code ("	   }\n");
		HI_Dump_Code ("	 }\n");
		HI_Dump_Code ("}\n\n");
		HI_Dump_Code ("#define DEFINE(key, tag) hx_associate (key, tag, 1)\n");
		HI_Dump_Code ("#define LOOKUP(tag) hx_associate (0, tag, 0)\n\n");
		HI_Dump_Code ("#ifndef NULL\n");
		HI_Dump_Code ("# define NULL ((void *) 0)\n");
		HI_Dump_Code ("#endif\n");
		HI_Dump_Code ("int main (int argc, char **argv) {\n");
		HI_Dump_Code ("	 char	string_buffer[256];\n");
		HI_Dump_Code ("	 float	ff;\n");
		HI_Dump_Code ("	 int	ii;\n");
		HI_Dump_Code ("	 long	ll;\n");
		HI_Dump_Code ("	 HC_KEY key;\n");
		HI_Dump_Code ("	 float	matrix[16];\n\n");
		HOOPS_WORLD->_hoops_CGHGA = 20;
		HOOPS_WORLD->_hoops_ISPPR = 2;
		HOOPS_WORLD->_hoops_PGHGA = true;
	}
	else {
		_hoops_SGHGA();
	}
#endif
}

GLOBAL_FUNCTION void HI_Chain_Code_Files (void) {
#ifndef DISABLE_CODE_GENERATION
	_hoops_HCRPR			_hoops_GGHGA;
	_hoops_HCRPR			_hoops_RGHGA;

	HI_Dump_Code ("\n");
	++HOOPS_WORLD->_hoops_RRHGA;
	HOOPS_WORLD->_hoops_ISPPR = 2;
	HI_Dump_Code (Sprintf_D (null, "code_chain_%d ();\n", HOOPS_WORLD->_hoops_RRHGA));
	HI_Dump_Code ("return 0;\n}\n");

	if (!HI_Close_File (HOOPS_WORLD->_hoops_AGHGA, &_hoops_GGHGA, &_hoops_RGHGA)) {
		HE_ERROR (HEC_FILE_IO, HES_FILE_IO,
				  Sprintf_NN (null, "%n %n", &_hoops_GGHGA, &_hoops_RGHGA));
		_hoops_RGAIR (_hoops_GGHGA);
		_hoops_RGAIR (_hoops_RGHGA);

		HOOPS_WORLD->_hoops_AGHGA = null;
		HOOPS_WORLD->system_flags &= ~_hoops_IGHGA;
		return;
	}
	_hoops_SGHGA();
#endif
}

GLOBAL_FUNCTION void HI_Finish_Code_Generation (void) {
#ifndef DISABLE_CODE_GENERATION
	_hoops_HCRPR			_hoops_GGHGA;
	_hoops_HCRPR			_hoops_RGHGA;

	HOOPS_WORLD->_hoops_ISPPR = 0;
	if (!HI_Close_File (HOOPS_WORLD->_hoops_AGHGA, &_hoops_GGHGA, &_hoops_RGHGA)) {
		HE_ERROR (HEC_FILE_IO, HES_FILE_IO,
				  Sprintf_NN (null, "%n %n", &_hoops_GGHGA, &_hoops_RGHGA));
		_hoops_RGAIR (_hoops_GGHGA);
		_hoops_RGAIR (_hoops_RGHGA);
	}
	HOOPS_WORLD->_hoops_AGHGA = null;
#endif
}
