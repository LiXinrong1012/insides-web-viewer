#pragma once

#include <math.h>
#include <memory.h>


// General Functions

__forceinline float GetAngle(float *v1, float *v2)
{
	register double fAngle = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	fAngle /= sqrt( v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2] );
	fAngle /= sqrt( v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2] );
	
	if ( fAngle > 1.0 )	fAngle = 1.0;
	else if ( fAngle < -1.0 ) fAngle = -1.0;
	
	return (float)fAngle;
}

inline void GetTriNormal(float* normal, float* v1, float* v2, float* v3)
{
	register float a[3], b[3], v[3];
	register float norm;

	a[0] = v2[0] - v1[0];
	a[1] = v2[1] - v1[1];
	a[2] = v2[2] - v1[2];

	b[0] = v3[0] - v1[0];
	b[1] = v3[1] - v1[1];
	b[2] = v3[2] - v1[2];

	v[0] = a[1]*b[2] - a[2]*b[1];
	v[1] = a[2]*b[0] - a[0]*b[2];
	v[2] = a[0]*b[1] - a[1]*b[0];

	norm = (float)sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
	if( norm != 0.0f ){
		normal[0] =  v[0] / norm;
		normal[1] =  v[1] / norm;
		normal[2] =  v[2] / norm;			
	}
	else{
		normal[0] =  1.0f;
		normal[1] =  1.0f;
		normal[2] =  1.0f;
	}	
}

//////////////////////////////////////////////////////////////////////
// Hashing Related Functions
//////////////////////////////////////////////////////////////////////

inline void AddHashItem(PP_HASHITEM* arHashTable, DWORD nHashCnt, DWORD dwData)
{
	register DWORD nHashItemCnt = arHashTable[nHashCnt].nCnt;
//	if( nHashItemCnt > 15)
//		int a=0;
	//if( arHashTable[nHashCnt].nCnt == 0 ){
	if( nHashItemCnt == 0 ){
		arHashTable[nHashCnt].nSize = 16;
		arHashTable[nHashCnt].pData = new DWORD[16];
		arHashTable[nHashCnt].pData[0] = dwData;
		arHashTable[nHashCnt].nCnt++;
	}
	else{

		if( nHashItemCnt == arHashTable[nHashCnt].nSize) {
			DWORD* temp = new DWORD[nHashItemCnt+16];
			memcpy( temp, arHashTable[nHashCnt].pData, nHashItemCnt * sizeof(DWORD) );
			delete [] arHashTable[nHashCnt].pData;
			arHashTable[nHashCnt].pData = temp;
			arHashTable[nHashCnt].nSize += 16;
		}
/*		DWORD* temp = new DWORD[nHashItemCnt+1];
		//for(DWORD ia=0; ia<nHashItemCnt; ia++)
		//	temp[ia] = arHashTable[nHashCnt].pData[ia];
		memcpy( temp, arHashTable[nHashCnt].pData, nHashItemCnt * sizeof(DWORD) );
		temp[nHashItemCnt] = dwData;
		delete [] arHashTable[nHashCnt].pData;
		arHashTable[nHashCnt].pData = temp;
*/
		arHashTable[nHashCnt].pData[nHashItemCnt] = dwData;
		arHashTable[nHashCnt].nCnt++;
	}
}

inline void DeleteHashItem(PP_HASHITEM* arHashTable, DWORD nHashCnt, DWORD iCnt)
{
	register DWORD nHashItemCnt = arHashTable[nHashCnt].nCnt;

	if( nHashItemCnt == 0 ) return;
	else if( nHashItemCnt == 1 ){
		delete [] arHashTable[nHashCnt].pData;
		arHashTable[nHashCnt].nCnt = 0;
	}
	else{
		DWORD* temp = new DWORD[nHashItemCnt-1];
		register int ib = 0;
		for(DWORD ia=0; ia<nHashItemCnt; ia++){
			if( iCnt != ia ){
				temp[ib] = arHashTable[nHashCnt].pData[ia];
				ib++;
			}
		}		
		delete [] arHashTable[nHashCnt].pData;
		arHashTable[nHashCnt].pData = temp;
		arHashTable[nHashCnt].nCnt = ib;
	}
}

inline void DeleteHashTable(PP_HASHITEM* arHashTable)
{
	// Delete Hash Table
	for(DWORD i=0; i<HASH_TABLE_SIZE; i++){		
		if( arHashTable[i].nCnt > 0 ) {
//#ifndef _DEBUG
			delete [] arHashTable[i].pData;
//#endif
		}
	}
//#ifndef _DEBUG
	delete [] arHashTable;
//#endif
	arHashTable = 0;
}


