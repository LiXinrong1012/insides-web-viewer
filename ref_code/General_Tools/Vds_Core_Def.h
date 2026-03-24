#ifndef PP_VDS_CORE_DEF_H_
#define PP_VDS_CORE_DEF_H_

#include <cstring>

#ifndef DWORD
typedef unsigned long DWORD;
#endif

struct V_LINK
{
	void *pData;
	struct V_LINK *pNext;
};

struct V_DLINK
{
	void *pData ;
	struct V_DLINK *pPrevious ;
	struct V_DLINK *pNext ;

	V_DLINK() 
	{
		pData = 0 ;
		pPrevious = pNext = 0 ;
	}
};


typedef struct tagLOC_COORD {
	// tiger 2005.3.14 add coordinate ID NO.
	DWORD CoodID;
	// input
	char name[132], refName[132];
	int iType, iMethod, iFirstType, iSecondType;
	//	COLORREF colLocal;
	double fOrigin[3], fPoint1[3], fPoint2[3];
	// output
	double fLocOrigin[3], fLoc2Global3[9], fGlobal2Loc3[9], fGlobal2Loc6[6][6];
	
	tagLOC_COORD()
	{
		CoodID = 1;
		strcpy(name, "Global");
		strcpy(refName, "");
		iType = 1;
		iMethod = 1;
		iFirstType = 1;
		iSecondType = 1;
		int i, j;
		for(i=0; i<3; i++)
		{
			fOrigin[i] = 0;
			fPoint1[i] = 0;
			fPoint2[i] = 0;
			fLocOrigin[i] = 0;
		}
		for(i=0; i<9; i++)
		{
			fLoc2Global3[i] = 0; 
			fGlobal2Loc3[i] = 0; 
		}
		for( i=0; i<6; i++ )
			for( j=0; j<6; j++ )
			{
				fGlobal2Loc6[i][j] = 0;
			}
	}
	
	void copy(tagLOC_COORD coord)
	{
		CoodID = coord.CoodID;
		strcpy(name, coord.name);
		strcpy(refName, coord.refName);
		iType = coord.iType;
		iMethod = coord.iMethod;
		iFirstType = coord.iFirstType;
		iSecondType = coord.iSecondType;
		int i, j;
		for(i=0; i<3; i++)
		{
			fOrigin[i] = coord.fOrigin[i];
			fPoint1[i] = coord.fPoint1[i];
			fPoint2[i] = coord.fPoint2[i];
			fLocOrigin[i] = coord.fLocOrigin[i];
		}
		for(i=0; i<9; i++)
		{
			fLoc2Global3[i] = coord.fLoc2Global3[i]; 
			fGlobal2Loc3[i] = coord.fGlobal2Loc3[i]; 
		}
		for( i=0; i<6; i++ )
			for( j=0; j<6; j++ )
			{
				fGlobal2Loc6[i][j] = coord.fGlobal2Loc6[i][j];
			}
	}
} LOC_COORD;


#endif 