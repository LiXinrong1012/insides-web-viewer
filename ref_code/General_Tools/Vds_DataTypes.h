#ifndef _VDS_TOOLS_DATA_TYPES_H_
#define  _VDS_TOOLS_DATA_TYPES_H_

#include "stdio.h"
#include "memory.h"

//#include "Version.h"
#if _MSC_VER > 1200
#include "basetsd.h" 
#else
typedef unsigned long		DWORD_PTR;
#endif

//#define _GLOBAL_DEBUG_FOR_ONEFACE_
//#define _GLOBAL_DEBUG_ONEFACE_ID_ 27408



typedef unsigned short int	VUWORD;
typedef unsigned long		VUDWORD;
typedef signed short int	VWORD;
typedef signed long			VDWORD;

typedef unsigned char		VUBYTE;
typedef char				VBYTE;

typedef float 				VFLOAT;
typedef double				VDOUBLE;


#endif 
