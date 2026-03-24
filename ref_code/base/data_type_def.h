////////////////////////////////////////////////////////
//  
//  Bottle Post Structure Global Header file
//
//  Generated : 2003. 2. 12   by Frovi
//  
////////////////////////////////////////////////////////


#ifndef __GLOBAL_BASE_DATA_DEF_H__
#define __GLOBAL_BASE_DATA_DEF_H__

//////////////////////////////////////////////////////
// General Difinitions

#define DW_NONE		0xffffffff	// Double-word variable none parameter
#define SW_NONE		0xffff		// Single-word variable none parameter

//#define  fQNAN	-1.0e-20f	// single precision quiet NaN value 0xffffffff
#define FINITBYTE	0xf0		// Single-byte variable for plot initialization
#define fQNAN	(-5.9654142337428973e+029f)	// single precision quiet NaN value 0xf0f0f0f0
#define dQNAN	-1.0e-20	// double precision quiet NaN value 0xffffffffffffffff

#define PI 3.1415926

// $FROVI$ - 2005/05/21
// Now many problem happen when fQNAN Value is applied,
// When the data is transform, the fQNAN is changed and also it's difficult check everytime,
// Then we can set cutoff value like below for calculate data range
#define fCutOffMax	1.0e20f
#define fCutOffMin	-1.0e20f
#define IsSafeFloat(x)	( (x)>fCutOffMin && (x)<fCutOffMax )

#define W_NONE		0xffff		// Single-word variable none parameter

//#define getMax(a,b)    (((a) > (b)) ? (a) : (b))
//#define getMin(a,b)    (((a) < (b)) ? (a) : (b))
//#ifndef PI
//#define PI			3.14159265f	// PI value
//#endif

#define DEGRAD		0.01745329	

#define SEL_PICK	1

#define DIR_XM		0
#define DIR_XP		1
#define DIR_YM		2
#define DIR_YP		3
#define DIR_ZM		4
#define DIR_ZP		5
#define DIR_YM2		6
// Tiger 2005/06/21
#define DIR_QU1		10
#define DIR_QU2		11
#define DIR_QU3		12
#define DIR_QU4		13
#define DIR_QU5		14
#define DIR_QU6		15
#define DIR_QU7		16
#define DIR_QU8		17
// Tiger End


/* API declaration data types */
typedef unsigned char		PGUBYTE;
typedef unsigned short int	PGSWORD;
typedef unsigned long int	PGDWORD;
typedef float				PGSREAL;
typedef double				PGDREAL;
typedef unsigned long int	DWORD;
typedef DWORD				COLORREF;
typedef int					BOOL;
typedef unsigned short int	VUWORD;
typedef unsigned long		VUDWORD;
typedef signed short int	VWORD;
typedef signed long			VDWORD;

typedef unsigned char		VUBYTE;
typedef char				VBYTE;

typedef unsigned int		VUINT;
typedef int					VINT;

typedef float 				VFLOAT;
typedef double				VDOUBLE;






#endif // __GLOBAL_DEF_H__