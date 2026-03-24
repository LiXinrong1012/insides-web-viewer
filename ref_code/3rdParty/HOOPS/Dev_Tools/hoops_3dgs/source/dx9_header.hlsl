#define reg(a) :register(a)

#define DRIVER_SPECIFIC_FLIP 1
#define BAD_VARIABLE_INDEX
#define DX9

#define semantic(a) : a

#define samplerCube sampler
#define sampler2D sampler


#define STATIC_ARRAY_BEGIN(name,type,size) static const type name[size] = {
#define STATIC_ARRAY_END }

#define OUT_TEXCOORD0	TEXCOORD0	
#define OUT_TEXCOORD1	TEXCOORD1	
#define OUT_TEXCOORD2	TEXCOORD2	
#define OUT_TEXCOORD3	TEXCOORD3	
#define OUT_TEXCOORD4	TEXCOORD4	
#define OUT_TEXCOORD5	TEXCOORD5	
#define OUT_TEXCOORD6	TEXCOORD6	
#define OUT_TEXCOORD7	TEXCOORD7	
#define OUT_FOG			FOG			
