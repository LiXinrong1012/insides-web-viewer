#ifndef TDY_PRE_PREFEM_BIT_FUNC_H
#define TDY_PRE_PREFEM_BIT_FUNC_H


/////////////////////////////////////////////////////////////
// DWORD for HASHING ( Upper 5 )
//
// TYPE 2: DWORD 32 bits : 00000 000000000000000000000000000
//                         DIR(5)         INDEX(27)
// DIR   is limited 2^5  = 0 - 31
// INDEX is limited 2^27 = 0 - 134217727

inline DWORD getUpBit5(DWORD x){ return (((x)&0xf8000000)>>27); }
inline DWORD getLowBit5(DWORD x){ return ((x)&0x07ffffff); }
inline DWORD makeBit5(DWORD up,DWORD low){return ((((DWORD)(up))<<27)|(DWORD)(low)); }



#endif