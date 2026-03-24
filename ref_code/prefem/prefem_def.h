#pragma once
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "prefem/prefem_global.h"
#include "prefem/bit_func.h"


//typedef wchar_t TCHAR;
#define _X86_32BIT
//#ifdef _X64_64BIT

#ifdef _X86_32BIT
#define DW_NONE 0xffffffff 
#endif
#ifdef _X64_64BIT
#define DW_NONE 0xffffffffffffffff
#endif



#define DELETE_ARRAY(x) {if((x)!=NULL){delete [] (x); (x)=NULL;}}
#define MAX2(x,y) ( ((x)>(y)) ? (x) : (y) )

// Node
typedef struct tagPP_NODE{
	DWORD		NID;				// Node ID 
	float		xyz[3];				// Position

	float x(){return xyz[0];}
	float y(){return xyz[1];}
	float z(){return xyz[2];}
} PP_NODE;


// Element Type definitions
#define	EL_NONE				0
#define EL_POINT			1
#define EL_LINE2			2	// 1D : Line
#define EL_LINE3			3	// 1D : Line having Middle Nodes
#define EL_TRI3				4	// 2D : Triangle ( Including Shell )
#define EL_TRI6				5	// 2D : Triangle having Middle Nodes ( Including Shell )
#define EL_QUAD4			6	// 2D : Rectangle ( Including Shell )
#define EL_QUAD8			7	// 2D : Rectangle having Middle Nodes ( Including Shell )
#define EL_TET4				8	// 3D : Tetragonal
#define EL_TET10			9	// 3D : Tetragonal having Middle Nodes
#define EL_HEX8				10	// 3D : Hexagonal
#define EL_HEX20			11	// 3D : Hexagonal having Middle Nodes
#define EL_PRISM6			12	// 3D : Prizm
#define EL_PRISM15			13	// 3D : Prism having Middle Nodes
#define EL_PYRAMID5			14	// 3D : Pyramid
#define EL_PYRAMID13		15	// 3D : Pyramid having Middle Nodes
#define EL_PLOT             16  //
#define EL_RBE2             17
#define EL_FAST             18
#define EL_ELAS             19
#define EL_CONM2            20
#define EL_RBE3             21
// To be added...
// Element
typedef struct tagPP_ELEMENT{
	DWORD	EID;			// Element ID
	unsigned short	TID;			// Type ID
	DWORD	NSI;			// Element Node Start Index
	DWORD	LSI;			// Link Start Index
	DWORD	MID;			// Material ID
	DWORD	PID;			// Property ID
	DWORD   GID;            // Group ID

} PP_ELEMENT;


#define MAX_ELEMENT_TYPE	256
#define ELEMENT_TYPE_CNT	16
#define MAX_ELEMENT_NODE	32
#define MAX_ELEMENT_EDGE	128
#define MAX_ELEMENT_FACE	32
#define MAX_ELEMENT_LINK	32
#define MAX_ELEMENT_GROUP	1024

////////////////////////////////////////////////////////
// Description about Element Type definition

// Node Sequence
// 1, 2, 3, 4, 5, 6, 7, 8
// ----------  ----------

// 1D : Link Count and Direction is same to Apex Node
// 2D : Link Count and Direction is same to Edge
// 3D : Link Count and Direction is same to Face

typedef struct tagPP_ELTYPE{
	// Basic Information
	DWORD	dwDim;

	// Node Count
	DWORD	dwNodeCnt;	
	DWORD	dwApexCnt;	
	DWORD	dwMidCnt;

	// Edge
	DWORD	dwEdgeCnt;	
	DWORD	dwEdgeType[MAX_ELEMENT_EDGE];		// Each Edge type
	DWORD	dwEdgeNodeCnt[MAX_ELEMENT_EDGE];	// Each Edge Node Cnt
	DWORD*	dwEdgeNode[MAX_ELEMENT_EDGE];		// Each Edge Node
	DWORD	dwEdgeNodeFlag[MAX_ELEMENT_EDGE]; 	// Each Edge Node Flag

	// Face 
	DWORD	dwFaceCnt;
	DWORD	dwFaceType[MAX_ELEMENT_FACE];		// Each Face type
	DWORD	dwFaceNodeCnt[MAX_ELEMENT_FACE];	// Each Face NodeCnt
	DWORD*	dwFaceNode[MAX_ELEMENT_FACE];		// Each Face Node
	DWORD	dwFaceNodeFlag[MAX_ELEMENT_FACE];	// Each Face Node Flag

	// for csharp. 2013.7.10.
	DWORD getFaceType(int index){return dwFaceType[index];}
	DWORD getFaceNodeCnt(int index){return dwFaceNodeCnt[index];}
	DWORD getFaceNode(int faceIndex,int index){return dwFaceNode[faceIndex][index];}


	// Link Count
	DWORD	dwLinkCnt;
	DWORD	dwLinkType[MAX_ELEMENT_LINK];
	DWORD	dwLinkNodeCnt[MAX_ELEMENT_LINK];
	DWORD*  dwLinkNode[MAX_ELEMENT_LINK];
	DWORD	dwLinkNodeFlag[MAX_ELEMENT_LINK];

} PP_ELTYPE;

// Surface
// Only 3D, (1D, 2D no need to make surface) - Only Triangle
typedef struct tagPP_SURFACE{
	unsigned short	TID;// Type ID
	DWORD	EID;		// Face Data Black ( EID + Face Dir ) BIT5 structure
	DWORD	ElNode[4];	// Node Number in Element
	float	Normal[3];	// Surface Normal 

	inline DWORD getEID()const{return getLowBit5(EID);}
	inline DWORD getFaceDir()const{return getUpBit5(EID);}
	inline void setEIDAndFaceDir(DWORD faceDir,DWORD eid){EID=makeBit5(faceDir,eid);}

} PP_SURFACE;

////////////////////////////////////////////////////////
// Hashing Table

#define HASH_TABLE_SIZE	1000000
typedef struct tagPP_HASHITEM {
	DWORD*	pData;
	unsigned short int	nCnt;
	unsigned short int	nSize;
} PP_HASHITEM;

// Macros
#define DELETE_ARRAY(x) {if((x)!=NULL){delete [] (x); (x)=NULL;}}
#define MAX2(x,y) ( ((x)>(y)) ? (x) : (y) )

/////////////////////////////////////////////////////////////
// Bit Operation Macros

/////////////////////////////////////////////////////////////
// DWORD for MARKING ( Upper 1 )
//
// TYPE 1: DWORD 32 bits : 0 0000000000000000000000000000000
//                         DIR(1)         INDEX(31)
// DIR   is limited 2    = 0 - 1 ( 0 or 1 )
// INDEX is limited 2^31 = 0 - 2147383647

#define GET_DW_UPBIT1(x) (((x)&0x80000000)>>31)
#define GET_DW_LOBIT1(x) ((x)&0x7fffffff)
#ifndef MAKE_DW_BIT1
#define MAKE_DW_BIT1(x,y) ((((DWORD)(x))<<31)|(DWORD)(y))
#endif

/////////////////////////////////////////////////////////////
// DWORD for HASHING ( Upper 4 )
//
// TYPE 4: DWORD 32 bits : 0000 0000000000000000000000000000
//                         DIR(4)         INDEX(28)
// DIR   is limited 2^4  = 0 - 15
// INDEX is limited 2^28 = 0 - 268435455

#define GET_DW_UPBIT4(x) (((x)&0xf0000000)>>28)
#define GET_DW_LOBIT4(x) ((x)&0x0fffffff)
#ifndef MAKE_DW_BIT4
#define MAKE_DW_BIT4(x,y) ((((DWORD)(x))<<28)|(DWORD)(y))
#endif



/////////////////////////////////////////////////////////////
// DWORD for HASHING ( Upper BYTE(8) )
//
// TYPE 2: DWORD 32 bits : 00000000 000000000000000000000000
//                         DIR(8)         INDEX(24)
// DIR   is limited 2^8  = 0 - 255
// INDEX is limited 2^24 = 0 - 16777215

#define GET_DW_UPBYTE(x) (((x)&0xff000000)>>24)
#define GET_DW_LOBYTE(x) ((x)&0x00ffffff)
#define MAKE_DW_BYTE(x,y) ((((DWORD)(x))<<24)|(DWORD)(y))

#define INTERPOLATE_LINE(x,y,r)  ((x)*(r) + (y)*(1.0f-(r)))


#define MAX_RESULT_CNT			4096
#define	MAX_RESULT_SUB_CNT		12
#define MAX_RESULT_STEP_CNT		4096
#define MAX_SPEC_INT_VALUE		50
#define MAX_SPEC_REAL_VALUE		50
#define MAX_PATH_LENGTH			1024

typedef struct PP_RID{	
	DWORD	index;	// Result Index	 (0-65535)
	int	year;	// Month
	int	month;	// Year
	int	day;	// Day
	int	hour;	// Hour
	int	min;	// Minute
	int	random;	// Random number
} PP_RID;


// Integer Value Type ( Basic Define )
#define FV_SIT_UNKNOWN				0
#define FV_SIT_ITERATION			1
#define FV_SIT_TIMESTEP				2
#define FV_SIT_FREQUENCY			3
// Secondary ( for ADVC )
#define FV_SIT_SEQUENCE				4
#define FV_SIT_MODENUM              5
#define FV_SIT_CASENUM              6
#define FV_SIT_STEPNUM              7
// To be added...

// Real Value Type ( Basic Define )
#define FV_SRT_UNKNOWN				0
#define FV_SRT_TIME					1
#define FV_SRT_FREQUENCY			2
#define FV_SRT_EIGENVALUE			3
#define FV_SRT_SOLID_FRACTION		4	// Solidification Fraction
#define FV_SRT_FILLING_FRACTION		5	// Filling Fraction
// To be added...

#define FV_VIEW_GENERAL            0
#define FV_VIEW_MAPPING            1
#define FV_VIEW_ROUGHPICK          2    // Haribote view
#define FV_VIEW_SHOWPICKM          3    // Minomushi view
#define FV_VIEW_SHOWBDPPLAYER      5    // Minomushi view

// Dynamic Load Type
#define HYP_LOAD_RLOAD               0
#define HYP_LOAD_SPECTRUM            1
#define HYP_LOAD_RANDOM              2
#define HYP_LOAD_TLOAD1              3
#define HYP_LOAD_TLOAD2              4

// Dynamic Response Type
#define HYP_RESPONSE_UNKNOWN         0
#define HYP_RESPONSE_DISPLACEMENT	1
#define HYP_RESPONSE_VELOCITY		2
#define HYP_RESPONSE_ACCELERATION	3
#define HYP_RESPONSE_STRESS			4
#define HYP_RESPONSE_STRAIN			5
#define HYP_RESPONSE_ACTRAN_PLTDOMAIN	6
#define HYP_RESPONSE_ACTRAN_PLTSURFACE	7
#define HYP_RESPONSE_ACTRAN_PLTPOINT		8
#define HYP_RESPONSE_FMBD_MDF		9
#define HYP_RESPONSE_FMBD_THERMALSTRESS		10
#define HYP_RESPONSE_FMBD_FATIGUEPROP		11
#define HYP_RESPONSE_FMBD_FATIGUECOND		12

// Frequency Analysis LBC

////////////////////////////////////////////
// Type Definition

// Result Analysis Type
#define FV_RAT_UNKNOWN			0	// UnKnown
#define FV_RAT_STATIC			1	// Static Liner Analysis
#define FV_RAT_TRANSIENT		2	// Transient Analysis
#define FV_RAT_NORMALMODE		3	// Normal Mode Analysis
#define FV_RAT_FREQUENCY		4	// Frequency Response
// $FROVI$ - 2005/05/20
#define FV_RAT_STATIC_NONLINER	5	// Static Non Liner
#define FV_RAT_BUCKLING			6	// Buckling		
#define FV_RAT_STEADY_HEAT_CONDUCTION	7	// Steady heat conduction
// To be added...

/* Ideas - case - analysis types
0:   Unknown	O
1:   Static		O
2:   Normal mode	O
3:   Complex eigenvalue first order	-- X
4:   Transient	O
5:   Frequency response	O
6:   Buckling
7:   Complex eigenvalue second order
9:   Static non-linear
10:   Craig-Bampton constraint modes
11:   Equivalent attachment modes
12:   Effective mass modes
13:   Effective mass matrix
14:   Effective mass matrix
*/



// Result DOF Type
#define FV_RDT_UNKNOWN			0
#define FV_RDT_SCALAR			1
#define FV_RDT_VECTOR			2
#define FV_RDT_VECROT			3
#define FV_RDT_TENSOR			4
// To be added...

// Result Type Definition
#define FV_RT_UNKNOWN			0
#define FV_RT_TEMPERATURE		1
#define FV_RT_STRESS			2
#define FV_RT_STRAIN			4
#define FV_RT_STRAIN_ENERGY		5
#define FV_RT_APPLY_LOAD		6
#define FV_RT_SPC_MPC			7
#define FV_RT_PRESSURE			8
#define FV_RT_GAP_THICKNESS		9
#define FV_RT_DISTANCE			10
#define FV_RT_HEAT_FLUX			11	// $FROVI$ - 2005/05/16
#define FV_RT_ELEMENT_FORCE		12  // Tiger 2005/06/20
#define FV_RT_NODE_COORD		13

#define FV_RT_EQUIVALENT_STRESS 14
#define FV_RT_EQUIVALENT_STRAIN 15
#define FV_RT_DAMAGE_FRACTION 16
#define FV_RT_PLASTIC_WORK 17
#define FV_RT_INTERNAL_ENERGY 18
#define FV_RT_LOG10_STRAIN_RATE 19
#define FV_RT_NET_XR_STRESS 20
#define FV_RT_NET_YT_STRESS 21
#define FV_RT_NET_Z_STRESS 22
#define FV_RT_Z_VELOCITY 23
#define FV_RT_VOLUMETRIC_STRAIN 25
#define FV_RT_CRACK_DAMAGE 26
#define FV_RT_CRACK_SIZE 27
#define FV_RT_EFF_BULK_MOD 28
#define FV_RT_EFF_SHEAR_MOD 29
#define FV_RT_MAX_VON_MISES 30
#define FV_RT_MAX_PRESSURE 31
#define FV_RT_DENSITY 32
#define FV_RT_PARTICLE_COORD	33
#define FV_RT_ELEMENT_CHECK		34

// Secondary Results
#define FV_RT_VON_MISES			101
#define FV_RT_MAX_PRINCIPAL		102
#define FV_RT_MID_PRINCIPAL		103
#define FV_RT_MIN_PRINCIPAL		104
#define FV_RT_STRESS_TOP		105
#define FV_RT_STRESS_CENTER		106
// To be added...
#define FV_RT_STRESS_CENTER_TOP 107
#define FV_RT_STRAIN_CENTER     108
#define FV_RT_STRAIN_TOP        109
#define FV_RT_STRAIN_CENTER_TOP 110
#define FV_RT_VELOCITY          111
#define FV_RT_ACCELERATION      112
#define FV_RT_STRESS_BOT        113 
#define FV_RT_STRAIN_BOT        114
#define FV_MOD_COMPOSITE        115
#define FV_RT_DISPLACEMENT		3
#define FV_RT_DISPLACEMENT_ROTATE 116
#define FV_RT_DISPLACEMENT_REAL_TRANS   117
#define FV_RT_DISPLACEMENT_REAL_ROTATE   118
#define FV_RT_DISPLACEMENT_IMAG_TRANS   119
#define FV_RT_DISPLACEMENT_IMAG_ROTATE   120
#define FV_RT_DISPLACEMENT_AMPL_TRANS   121
#define FV_RT_DISPLACEMENT_AMPL_ROTATE   122
#define FV_RT_DISPLACEMENT_PHASE_TRANS  123
#define FV_RT_DISPLACEMENT_PHASE_ROTATE  124
#define FV_RT_ACCELERATION_ROTATE        125
#define FV_RT_ACCELERATION_REAL_TRANS    126
#define FV_RT_ACCELERATION_REAL_ROTATE   127
#define FV_RT_ACCELERATION_IMAG_TRANS    128
#define FV_RT_ACCELERATION_IMAG_ROTATE   129
#define FV_RT_ACCELERATION_AMPL_TRANS    130
#define FV_RT_ACCELERATION_AMPL_ROTATE   131
#define FV_RT_ACCELERATION_PHASE_TRANS    132
#define FV_RT_ACCELERATION_PHASE_ROTATE   133
#define FV_RT_VELOCITY_ROTATE        134
#define FV_RT_VELOCITY_REAL_TRANS    135
#define FV_RT_VELOCITY_REAL_ROTATE   136
#define FV_RT_VELOCITY_IMAG_TRANS    137
#define FV_RT_VELOCITY_IMAG_ROTATE   138
#define FV_RT_VELOCITY_AMPL_TRANS    139
#define FV_RT_VELOCITY_AMPL_ROTATE   140
#define FV_RT_VELOCITY_PHASE_TRANS    141
#define FV_RT_VELOCITY_PHASE_ROTATE   142

#define VN_IMPORT_OP2  0

// Result Location Type Definition
#define	FV_RLT_NODAL			0
#define FV_RLT_ELEMENTNODAL		1
#define FV_RLT_ELEMENTAL		2
// To be added... ( I Think it's enough )

// Result Data variable allocation type
#define FV_RVT_FLOAT				0
#define FV_RVT_DOUBLE				1	// Not support yet!
#define FV_RVT_SHORT_INT			2	// Not support yet!
#define FV_RVT_LONG_INT				3	// Not support yet!

////////////////////////////////////////////
// Special Value Definition

// Integer Value Type ( Basic Define )
#define FV_SIT_UNKNOWN				0
#define FV_SIT_ITERATION			1
#define FV_SIT_TIMESTEP				2
#define FV_SIT_FREQUENCY			3
// To be added...

// Real Value Type ( Basic Define )
#define FV_SR_UNKNOWN				0
#define FV_SR_TIME					1
#define FV_SR_FREQUENCY				2
// To be added...

typedef struct tagPP_RAWRESULT{

	// Index
	PP_RID	RID;					// Result ID
	PP_RID	ParentRID;				// Parent Result Index ( Single : DW_NONE )

	// Geometry Infomation
	DWORD	dwElementCnt;			// Element Number
	DWORD	dwNodeCnt;				// Node Number

	// Title and Description
	TCHAR	lpszName[256];			// Result Name
	TCHAR	lpszDesc[1024];			// Result Discription

	// Type Information
	DWORD	dwAnlType;				// Analysis Type
	DWORD	dwDofType;				// Data Charateristic Type
	DWORD	dwRltType;				// Result Type

	BYTE	ubLocType;				// Result Location Type	( Node, Element, Element Node )
	BYTE	ubAlcType;				// Data Allocation type ( float, double, long int, short int )

	// Subset Information
	BYTE	ubSubItemCnt;			// Result Sub-Item Number
	DWORD	dwSubDataCnt;			// Result Sub-Item Data Number
	DWORD	dwSubDataSize;			// Result Sub-Item DataSize in byte

	// Intiger Value
	DWORD	dwIntValType[MAX_SPEC_INT_VALUE];			// Intiger Value type
	long	lIntValue[MAX_SPEC_INT_VALUE];				// Intiger Value

	// Real Value
	DWORD	dwRealValType[MAX_SPEC_REAL_VALUE];			// RealValue Type
	double	dRealValue[MAX_SPEC_REAL_VALUE];			// Special Value

} PP_RAWRESULT;

// Result Item Status Flags
#define FV_RIS_FORCEMEMORY		0x00000001

typedef struct tagPP_RESULTITEM{
	DWORD	dwVersion;			// Result Version
	TCHAR	lpszFilePath[1024];		// Result File Path
	PP_RAWRESULT	fvInfo;
	fpos_t	fposDataStart;		// Data Main Start File Position
	fpos_t	fposSubsetStart[MAX_RESULT_SUB_CNT];	// Subset Start Position
	float*	afData[MAX_RESULT_SUB_CNT];	// float type data pointer
	//double* adData[MAX_RESULT_SUB_CNT]; // double type data pointer
	//DWORD	dwRefCnt;
	//DWORD	dwStatus;
} PP_RESULTITEM;

