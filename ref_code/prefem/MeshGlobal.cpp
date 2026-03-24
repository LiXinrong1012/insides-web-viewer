#include "MeshGlobal.h"



void DefineElementTypes(PP_ELTYPE* ElType);

MeshGlobal::MeshGlobal(void)
{
	DefineElementTypes(_elemTypes);
}


MeshGlobal::~MeshGlobal(void)
{
}



// Element Type Definition
static void DefineElementTypes(PP_ELTYPE* ElType)
{
	// Clean Data Area
	ZeroMemory( ElType, MAX_ELEMENT_TYPE * sizeof(PP_ELTYPE) );

	/////////////////////
	// Type 1 : EL_POINT
	ElType[EL_POINT].dwDim = 1;

	// Count
	ElType[EL_POINT].dwNodeCnt = 1;	
	ElType[EL_POINT].dwApexCnt = 1;	
	ElType[EL_POINT].dwMidCnt  = 0;	 
	ElType[EL_POINT].dwEdgeCnt = 0; 
	ElType[EL_POINT].dwFaceCnt = 0;
	ElType[EL_POINT].dwLinkCnt = 0;	

	/////////////////////
	// Type 2 : EL_LINE2

	// Basic Information
	ElType[EL_LINE2].dwDim = 1;

	// Count
	ElType[EL_LINE2].dwNodeCnt = 2;	
	ElType[EL_LINE2].dwApexCnt = 2;	
	ElType[EL_LINE2].dwMidCnt  = 0;	 
	ElType[EL_LINE2].dwEdgeCnt = 1; 
	ElType[EL_LINE2].dwFaceCnt = 0;
	ElType[EL_LINE2].dwLinkCnt = 2;	

	// Edge
	ElType[EL_LINE2].dwEdgeType[0] = EL_LINE2;

	ElType[EL_LINE2].dwEdgeNode[0] = new DWORD[2];		// Each Edge Node
	ElType[EL_LINE2].dwEdgeNode[0][0] = 0;
	ElType[EL_LINE2].dwEdgeNode[0][1] = 1;

	ElType[EL_LINE2].dwEdgeNodeFlag[0] = 0x00000003; 	// Each Edge Node Flag

	ElType[EL_LINE2].dwLinkType[0] = EL_POINT;
	ElType[EL_LINE2].dwLinkType[1] = EL_POINT;
	ElType[EL_LINE2].dwLinkNodeCnt[0] = 1;
	ElType[EL_LINE2].dwLinkNodeCnt[1] = 1;
	ElType[EL_LINE2].dwLinkNode[0] = new DWORD[1];
	ElType[EL_LINE2].dwLinkNode[1] = new DWORD[1];
	ElType[EL_LINE2].dwLinkNode[0][0] = 0;
	ElType[EL_LINE2].dwLinkNode[1][0] = 1;
	ElType[EL_LINE2].dwLinkNodeFlag[0] = 0x00000001;
	ElType[EL_LINE2].dwLinkNodeFlag[1] = 0x00000002;

	/////////////////////
	// Type 3 : EL_LINE3

	// Basic Information
	ElType[EL_LINE3].dwDim = 1;

	// Count
	ElType[EL_LINE3].dwNodeCnt = 3;	
	ElType[EL_LINE3].dwApexCnt = 2;	
	ElType[EL_LINE3].dwMidCnt  = 1;	 
	ElType[EL_LINE3].dwEdgeCnt = 1; 
	ElType[EL_LINE3].dwFaceCnt = 0;
	ElType[EL_LINE3].dwLinkCnt = 2;	

	// Edge
	ElType[EL_LINE3].dwEdgeType[0] = EL_LINE3;

	ElType[EL_LINE3].dwEdgeNode[0] = new DWORD[3];		// Each Edge Node
	ElType[EL_LINE3].dwEdgeNode[0][0] = 0;
	ElType[EL_LINE3].dwEdgeNode[0][1] = 1;
	ElType[EL_LINE3].dwEdgeNode[0][2] = 2;

	ElType[EL_LINE3].dwEdgeNodeFlag[0] = 0x00000007; 	// Each Edge Node Flag

	// Link
	ElType[EL_LINE3].dwLinkType[0] = EL_POINT;
	ElType[EL_LINE3].dwLinkType[1] = EL_POINT;
	ElType[EL_LINE3].dwLinkNodeCnt[0] = 1;
	ElType[EL_LINE3].dwLinkNodeCnt[1] = 1;
	ElType[EL_LINE3].dwLinkNode[0] = new DWORD[1];
	ElType[EL_LINE3].dwLinkNode[1] = new DWORD[1];
	ElType[EL_LINE3].dwLinkNode[0][0] = 0;
	ElType[EL_LINE3].dwLinkNode[1][0] = 1;
	ElType[EL_LINE3].dwLinkNodeFlag[0] = 0x00000001;
	ElType[EL_LINE3].dwLinkNodeFlag[1] = 0x00000002;

	/////////////////////
	// Type 4 : EL_TRI3

	// Basic Information
	ElType[EL_TRI3].dwDim = 2;

	// Count
	ElType[EL_TRI3].dwNodeCnt = 3;	
	ElType[EL_TRI3].dwApexCnt = 3;	
	ElType[EL_TRI3].dwMidCnt  = 0;	 
	ElType[EL_TRI3].dwEdgeCnt = 3; 
	ElType[EL_TRI3].dwFaceCnt = 1;
	ElType[EL_TRI3].dwLinkCnt = 3;	

	// Edge
	ElType[EL_TRI3].dwEdgeType[0] = EL_LINE2;
	ElType[EL_TRI3].dwEdgeType[1] = EL_LINE2;
	ElType[EL_TRI3].dwEdgeType[2] = EL_LINE2;

	ElType[EL_TRI3].dwEdgeNode[0] = new DWORD[2];		// Each Edge Node
	ElType[EL_TRI3].dwEdgeNode[1] = new DWORD[2];
	ElType[EL_TRI3].dwEdgeNode[2] = new DWORD[2];

	ElType[EL_TRI3].dwEdgeNode[0][0] = 0;
	ElType[EL_TRI3].dwEdgeNode[0][1] = 1;

	ElType[EL_TRI3].dwEdgeNode[1][0] = 1;
	ElType[EL_TRI3].dwEdgeNode[1][1] = 2;

	ElType[EL_TRI3].dwEdgeNode[2][0] = 2;
	ElType[EL_TRI3].dwEdgeNode[2][1] = 0;

	ElType[EL_TRI3].dwEdgeNodeFlag[0] = 0x00000003; 	// Each Edge Node Flag
	ElType[EL_TRI3].dwEdgeNodeFlag[1] = 0x00000006;
	ElType[EL_TRI3].dwEdgeNodeFlag[2] = 0x00000005;

	// Face 
	ElType[EL_TRI3].dwFaceType[0] = EL_TRI3;	// Each Face type

	ElType[EL_TRI3].dwFaceNode[0] = new DWORD[3];	// Each Face Node

	ElType[EL_TRI3].dwFaceNode[0][0] = 0;
	ElType[EL_TRI3].dwFaceNode[0][1] = 1;
	ElType[EL_TRI3].dwFaceNode[0][2] = 2;

	ElType[EL_TRI3].dwFaceNodeFlag[0] = 0x00000007;	// Each Face Node Flag

	// Link
	ElType[EL_TRI3].dwLinkType[0] = EL_LINE2;
	ElType[EL_TRI3].dwLinkType[1] = EL_LINE2;
	ElType[EL_TRI3].dwLinkType[2] = EL_LINE2;

	ElType[EL_TRI3].dwLinkNodeCnt[0] = 2;
	ElType[EL_TRI3].dwLinkNodeCnt[1] = 2;
	ElType[EL_TRI3].dwLinkNodeCnt[2] = 2;

	ElType[EL_TRI3].dwLinkNode[0] = new DWORD[2];		// Each Link Node
	ElType[EL_TRI3].dwLinkNode[1] = new DWORD[2];
	ElType[EL_TRI3].dwLinkNode[2] = new DWORD[2];

	ElType[EL_TRI3].dwLinkNode[0][0] = 0;
	ElType[EL_TRI3].dwLinkNode[0][1] = 1;

	ElType[EL_TRI3].dwLinkNode[1][0] = 1;
	ElType[EL_TRI3].dwLinkNode[1][1] = 2;

	ElType[EL_TRI3].dwLinkNode[2][0] = 2;
	ElType[EL_TRI3].dwLinkNode[2][1] = 0;

	ElType[EL_TRI3].dwLinkNodeFlag[0] = 0x00000003; 	// Each Link Node Flag
	ElType[EL_TRI3].dwLinkNodeFlag[1] = 0x00000006;
	ElType[EL_TRI3].dwLinkNodeFlag[2] = 0x00000005;


	/////////////////////
	// Type 4 : EL_TRI6

	// Basic Information
	ElType[EL_TRI6].dwDim = 2;

	// Count
	ElType[EL_TRI6].dwNodeCnt = 6;	
	ElType[EL_TRI6].dwApexCnt = 3;	
	ElType[EL_TRI6].dwMidCnt  = 3;	 
	ElType[EL_TRI6].dwEdgeCnt = 3; 
	ElType[EL_TRI6].dwFaceCnt = 1;
	ElType[EL_TRI6].dwLinkCnt = 3;	

	// Edge
	ElType[EL_TRI6].dwEdgeType[0] = EL_LINE3;
	ElType[EL_TRI6].dwEdgeType[1] = EL_LINE3;
	ElType[EL_TRI6].dwEdgeType[2] = EL_LINE3;

	ElType[EL_TRI6].dwEdgeNode[0] = new DWORD[3];		// Each Edge Node
	ElType[EL_TRI6].dwEdgeNode[1] = new DWORD[3];
	ElType[EL_TRI6].dwEdgeNode[2] = new DWORD[3];

	ElType[EL_TRI6].dwEdgeNode[0][0] = 0;
	ElType[EL_TRI6].dwEdgeNode[0][1] = 1;
	ElType[EL_TRI6].dwEdgeNode[0][2] = 3;

	ElType[EL_TRI6].dwEdgeNode[1][0] = 1;
	ElType[EL_TRI6].dwEdgeNode[1][1] = 2;
	ElType[EL_TRI6].dwEdgeNode[1][2] = 4;

	ElType[EL_TRI6].dwEdgeNode[2][0] = 2;
	ElType[EL_TRI6].dwEdgeNode[2][1] = 0;
	ElType[EL_TRI6].dwEdgeNode[2][2] = 5;

	ElType[EL_TRI6].dwEdgeNodeFlag[0] = 0x0000000b; 	// Each Edge Node Flag
	ElType[EL_TRI6].dwEdgeNodeFlag[1] = 0x00000016;
	ElType[EL_TRI6].dwEdgeNodeFlag[2] = 0x00000025;

	// Face 
	ElType[EL_TRI6].dwFaceType[0] = EL_TRI6;	// Each Face type

	ElType[EL_TRI6].dwFaceNode[0] = new DWORD[6];	// Each Face Node

	ElType[EL_TRI6].dwFaceNode[0][0] = 0;
	ElType[EL_TRI6].dwFaceNode[0][1] = 1;
	ElType[EL_TRI6].dwFaceNode[0][2] = 2;
	ElType[EL_TRI6].dwFaceNode[0][3] = 3;
	ElType[EL_TRI6].dwFaceNode[0][4] = 4;
	ElType[EL_TRI6].dwFaceNode[0][5] = 5;

	ElType[EL_TRI6].dwFaceNodeFlag[0] = 0x0000003f;	// Each Face Node Flag

	// Link
	ElType[EL_TRI6].dwLinkType[0] = EL_LINE2;
	ElType[EL_TRI6].dwLinkType[1] = EL_LINE2;
	ElType[EL_TRI6].dwLinkType[2] = EL_LINE2;

	ElType[EL_TRI6].dwLinkNodeCnt[0] = 2;
	ElType[EL_TRI6].dwLinkNodeCnt[1] = 2;
	ElType[EL_TRI6].dwLinkNodeCnt[2] = 2;

	ElType[EL_TRI6].dwLinkNode[0] = new DWORD[2];		// Each Link Node
	ElType[EL_TRI6].dwLinkNode[1] = new DWORD[2];
	ElType[EL_TRI6].dwLinkNode[2] = new DWORD[2];

	ElType[EL_TRI6].dwLinkNode[0][0] = 0;
	ElType[EL_TRI6].dwLinkNode[0][1] = 1;

	ElType[EL_TRI6].dwLinkNode[1][0] = 1;
	ElType[EL_TRI6].dwLinkNode[1][1] = 2;

	ElType[EL_TRI6].dwLinkNode[2][0] = 2;
	ElType[EL_TRI6].dwLinkNode[2][1] = 0;

	ElType[EL_TRI6].dwLinkNodeFlag[0] = 0x00000003; 	// Each Link Node Flag
	ElType[EL_TRI6].dwLinkNodeFlag[1] = 0x00000006;
	ElType[EL_TRI6].dwLinkNodeFlag[2] = 0x00000005;

	/////////////////////
	// Type 6 : EL_QUAD4

	// Basic Information
	ElType[EL_QUAD4].dwDim = 2;

	// Count
	ElType[EL_QUAD4].dwNodeCnt = 4;	
	ElType[EL_QUAD4].dwApexCnt = 4;	
	ElType[EL_QUAD4].dwMidCnt  = 0;	 
	ElType[EL_QUAD4].dwEdgeCnt = 4; 
	ElType[EL_QUAD4].dwFaceCnt = 1;
	ElType[EL_QUAD4].dwLinkCnt = 4;	

	// Edge
	ElType[EL_QUAD4].dwEdgeType[0] = EL_LINE2;
	ElType[EL_QUAD4].dwEdgeType[1] = EL_LINE2;
	ElType[EL_QUAD4].dwEdgeType[2] = EL_LINE2;
	ElType[EL_QUAD4].dwEdgeType[3] = EL_LINE2;

	ElType[EL_QUAD4].dwEdgeNode[0] = new DWORD[2];		// Each Edge Node
	ElType[EL_QUAD4].dwEdgeNode[1] = new DWORD[2];
	ElType[EL_QUAD4].dwEdgeNode[2] = new DWORD[2];
	ElType[EL_QUAD4].dwEdgeNode[3] = new DWORD[2];

	ElType[EL_QUAD4].dwEdgeNode[0][0] = 0;
	ElType[EL_QUAD4].dwEdgeNode[0][1] = 1;

	ElType[EL_QUAD4].dwEdgeNode[1][0] = 1;
	ElType[EL_QUAD4].dwEdgeNode[1][1] = 2;

	ElType[EL_QUAD4].dwEdgeNode[2][0] = 2;
	ElType[EL_QUAD4].dwEdgeNode[2][1] = 3;

	ElType[EL_QUAD4].dwEdgeNode[3][0] = 3;
	ElType[EL_QUAD4].dwEdgeNode[3][1] = 0;

	ElType[EL_QUAD4].dwEdgeNodeFlag[0] = 0x00000003; 	// Each Edge Node Flag
	ElType[EL_QUAD4].dwEdgeNodeFlag[1] = 0x00000006;
	ElType[EL_QUAD4].dwEdgeNodeFlag[2] = 0x0000000c;
	ElType[EL_QUAD4].dwEdgeNodeFlag[3] = 0x00000009;

	// Face 
	ElType[EL_QUAD4].dwFaceType[0] = EL_QUAD4;	// Each Face type

	ElType[EL_QUAD4].dwFaceNode[0] = new DWORD[4];	// Each Face Node

	ElType[EL_QUAD4].dwFaceNode[0][0] = 0;
	ElType[EL_QUAD4].dwFaceNode[0][1] = 1;
	ElType[EL_QUAD4].dwFaceNode[0][2] = 2;
	ElType[EL_QUAD4].dwFaceNode[0][3] = 3;

	ElType[EL_QUAD4].dwFaceNodeFlag[0] = 0x0000000f;	// Each Face Node Flag

	// Link
	ElType[EL_QUAD4].dwLinkType[0] = EL_LINE2;
	ElType[EL_QUAD4].dwLinkType[1] = EL_LINE2;
	ElType[EL_QUAD4].dwLinkType[2] = EL_LINE2;
	ElType[EL_QUAD4].dwLinkType[3] = EL_LINE2;

	ElType[EL_QUAD4].dwLinkNodeCnt[0] = 2;
	ElType[EL_QUAD4].dwLinkNodeCnt[1] = 2;
	ElType[EL_QUAD4].dwLinkNodeCnt[2] = 2;
	ElType[EL_QUAD4].dwLinkNodeCnt[3] = 2;

	ElType[EL_QUAD4].dwLinkNode[0] = new DWORD[2];		// Each Link Node
	ElType[EL_QUAD4].dwLinkNode[1] = new DWORD[2];
	ElType[EL_QUAD4].dwLinkNode[2] = new DWORD[2];
	ElType[EL_QUAD4].dwLinkNode[3] = new DWORD[2];

	ElType[EL_QUAD4].dwLinkNode[0][0] = 0;
	ElType[EL_QUAD4].dwLinkNode[0][1] = 1;

	ElType[EL_QUAD4].dwLinkNode[1][0] = 1;
	ElType[EL_QUAD4].dwLinkNode[1][1] = 2;

	ElType[EL_QUAD4].dwLinkNode[2][0] = 2;
	ElType[EL_QUAD4].dwLinkNode[2][1] = 3;

	ElType[EL_QUAD4].dwLinkNode[3][0] = 3;
	ElType[EL_QUAD4].dwLinkNode[3][1] = 0;

	ElType[EL_QUAD4].dwLinkNodeFlag[0] = 0x00000003; 	// Each Link Node Flag
	ElType[EL_QUAD4].dwLinkNodeFlag[1] = 0x00000006;
	ElType[EL_QUAD4].dwLinkNodeFlag[2] = 0x0000000c;
	ElType[EL_QUAD4].dwLinkNodeFlag[3] = 0x00000009;

	/////////////////////
	// Type 6 : EL_QUAD8

	// Basic Information
	ElType[EL_QUAD8].dwDim = 2;

	// Count
	ElType[EL_QUAD8].dwNodeCnt = 8;	
	ElType[EL_QUAD8].dwApexCnt = 4;	
	ElType[EL_QUAD8].dwMidCnt  = 4;	 
	ElType[EL_QUAD8].dwEdgeCnt = 4; 
	ElType[EL_QUAD8].dwFaceCnt = 1;
	ElType[EL_QUAD8].dwLinkCnt = 4;	

	// Edge
	ElType[EL_QUAD8].dwEdgeType[0] = EL_LINE3;
	ElType[EL_QUAD8].dwEdgeType[1] = EL_LINE3;
	ElType[EL_QUAD8].dwEdgeType[2] = EL_LINE3;
	ElType[EL_QUAD8].dwEdgeType[3] = EL_LINE3;

	ElType[EL_QUAD8].dwEdgeNode[0] = new DWORD[3];		// Each Edge Node
	ElType[EL_QUAD8].dwEdgeNode[1] = new DWORD[3];
	ElType[EL_QUAD8].dwEdgeNode[2] = new DWORD[3];
	ElType[EL_QUAD8].dwEdgeNode[3] = new DWORD[3];

	ElType[EL_QUAD8].dwEdgeNode[0][0] = 0;
	ElType[EL_QUAD8].dwEdgeNode[0][1] = 1;
	ElType[EL_QUAD8].dwEdgeNode[0][2] = 4;

	ElType[EL_QUAD8].dwEdgeNode[1][0] = 1;
	ElType[EL_QUAD8].dwEdgeNode[1][1] = 2;
	ElType[EL_QUAD8].dwEdgeNode[1][2] = 5;

	ElType[EL_QUAD8].dwEdgeNode[2][0] = 2;
	ElType[EL_QUAD8].dwEdgeNode[2][1] = 3;
	ElType[EL_QUAD8].dwEdgeNode[2][2] = 6;

	ElType[EL_QUAD8].dwEdgeNode[3][0] = 3;
	ElType[EL_QUAD8].dwEdgeNode[3][1] = 0;
	ElType[EL_QUAD8].dwEdgeNode[3][2] = 7;

	ElType[EL_QUAD8].dwEdgeNodeFlag[0] = 0x00000013; 	// Each Edge Node Flag
	ElType[EL_QUAD8].dwEdgeNodeFlag[1] = 0x00000026;
	ElType[EL_QUAD8].dwEdgeNodeFlag[2] = 0x0000004c;
	ElType[EL_QUAD8].dwEdgeNodeFlag[3] = 0x00000089;

	// Face 
	ElType[EL_QUAD8].dwFaceType[0] = EL_QUAD8;	// Each Face type

	ElType[EL_QUAD8].dwFaceNode[0] = new DWORD[8];	// Each Face Node

	ElType[EL_QUAD8].dwFaceNode[0][0] = 0;
	ElType[EL_QUAD8].dwFaceNode[0][1] = 1;
	ElType[EL_QUAD8].dwFaceNode[0][2] = 2;
	ElType[EL_QUAD8].dwFaceNode[0][3] = 3;
	ElType[EL_QUAD8].dwFaceNode[0][4] = 4;
	ElType[EL_QUAD8].dwFaceNode[0][5] = 5;
	ElType[EL_QUAD8].dwFaceNode[0][6] = 6;
	ElType[EL_QUAD8].dwFaceNode[0][7] = 7;

	ElType[EL_QUAD8].dwFaceNodeFlag[0] = 0x000000ff;	// Each Face Node Flag	

	// Link
	ElType[EL_QUAD8].dwLinkType[0] = EL_LINE2;
	ElType[EL_QUAD8].dwLinkType[1] = EL_LINE2;
	ElType[EL_QUAD8].dwLinkType[2] = EL_LINE2;
	ElType[EL_QUAD8].dwLinkType[3] = EL_LINE2;

	ElType[EL_QUAD8].dwLinkNodeCnt[0] = 2;
	ElType[EL_QUAD8].dwLinkNodeCnt[1] = 2;
	ElType[EL_QUAD8].dwLinkNodeCnt[2] = 2;
	ElType[EL_QUAD8].dwLinkNodeCnt[3] = 2;

	ElType[EL_QUAD8].dwLinkNode[0] = new DWORD[2];		// Each Link Node
	ElType[EL_QUAD8].dwLinkNode[1] = new DWORD[2];
	ElType[EL_QUAD8].dwLinkNode[2] = new DWORD[2];
	ElType[EL_QUAD8].dwLinkNode[3] = new DWORD[2];

	ElType[EL_QUAD8].dwLinkNode[0][0] = 0;
	ElType[EL_QUAD8].dwLinkNode[0][1] = 1;

	ElType[EL_QUAD8].dwLinkNode[1][0] = 1;
	ElType[EL_QUAD8].dwLinkNode[1][1] = 2;

	ElType[EL_QUAD8].dwLinkNode[2][0] = 2;
	ElType[EL_QUAD8].dwLinkNode[2][1] = 3;

	ElType[EL_QUAD8].dwLinkNode[3][0] = 3;
	ElType[EL_QUAD8].dwLinkNode[3][1] = 0;

	ElType[EL_QUAD8].dwLinkNodeFlag[0] = 0x00000003; 	// Each Link Node Flag
	ElType[EL_QUAD8].dwLinkNodeFlag[1] = 0x00000006;
	ElType[EL_QUAD8].dwLinkNodeFlag[2] = 0x0000000c;
	ElType[EL_QUAD8].dwLinkNodeFlag[3] = 0x00000009;

	/////////////////////
	// Type 8 : EL_TET4

	// Basic Information
	ElType[EL_TET4].dwDim = 3;

	// Count
	ElType[EL_TET4].dwNodeCnt = 4;	
	ElType[EL_TET4].dwApexCnt = 4;	
	ElType[EL_TET4].dwMidCnt  = 0;	 
	ElType[EL_TET4].dwEdgeCnt = 6; 
	ElType[EL_TET4].dwFaceCnt = 4;
	ElType[EL_TET4].dwLinkCnt = 4;	

	// Edge
	ElType[EL_TET4].dwEdgeType[0] = EL_LINE2;
	ElType[EL_TET4].dwEdgeType[1] = EL_LINE2;
	ElType[EL_TET4].dwEdgeType[2] = EL_LINE2;
	ElType[EL_TET4].dwEdgeType[3] = EL_LINE2;
	ElType[EL_TET4].dwEdgeType[4] = EL_LINE2;
	ElType[EL_TET4].dwEdgeType[5] = EL_LINE2;

	ElType[EL_TET4].dwEdgeNode[0] = new DWORD[2];		// Each Edge Node
	ElType[EL_TET4].dwEdgeNode[1] = new DWORD[2];
	ElType[EL_TET4].dwEdgeNode[2] = new DWORD[2];
	ElType[EL_TET4].dwEdgeNode[3] = new DWORD[2];
	ElType[EL_TET4].dwEdgeNode[4] = new DWORD[2];
	ElType[EL_TET4].dwEdgeNode[5] = new DWORD[2];

	ElType[EL_TET4].dwEdgeNode[0][0] = 0;
	ElType[EL_TET4].dwEdgeNode[0][1] = 1;

	ElType[EL_TET4].dwEdgeNode[1][0] = 1;
	ElType[EL_TET4].dwEdgeNode[1][1] = 2;

	ElType[EL_TET4].dwEdgeNode[2][0] = 2;
	ElType[EL_TET4].dwEdgeNode[2][1] = 0;

	ElType[EL_TET4].dwEdgeNode[3][0] = 0;
	ElType[EL_TET4].dwEdgeNode[3][1] = 3;

	ElType[EL_TET4].dwEdgeNode[4][0] = 1;
	ElType[EL_TET4].dwEdgeNode[4][1] = 3;

	ElType[EL_TET4].dwEdgeNode[5][0] = 2;
	ElType[EL_TET4].dwEdgeNode[5][1] = 3;

	ElType[EL_TET4].dwEdgeNodeFlag[0] = 0x00000003; 	// Each Edge Node Flag
	ElType[EL_TET4].dwEdgeNodeFlag[1] = 0x00000006;
	ElType[EL_TET4].dwEdgeNodeFlag[2] = 0x00000005;
	ElType[EL_TET4].dwEdgeNodeFlag[3] = 0x00000009;
	ElType[EL_TET4].dwEdgeNodeFlag[4] = 0x0000000a;
	ElType[EL_TET4].dwEdgeNodeFlag[5] = 0x0000000c;

	// Face 
	ElType[EL_TET4].dwFaceType[0] = EL_TRI3;	// Each Face type
	ElType[EL_TET4].dwFaceType[1] = EL_TRI3;
	ElType[EL_TET4].dwFaceType[2] = EL_TRI3;
	ElType[EL_TET4].dwFaceType[3] = EL_TRI3;

	ElType[EL_TET4].dwFaceNode[0] = new DWORD[3];	// Each Face Node
	ElType[EL_TET4].dwFaceNode[1] = new DWORD[3];
	ElType[EL_TET4].dwFaceNode[2] = new DWORD[3];
	ElType[EL_TET4].dwFaceNode[3] = new DWORD[3];

	ElType[EL_TET4].dwFaceNode[0][0] = 0;
	ElType[EL_TET4].dwFaceNode[0][1] = 2;
	ElType[EL_TET4].dwFaceNode[0][2] = 1;

	ElType[EL_TET4].dwFaceNode[1][0] = 0;
	ElType[EL_TET4].dwFaceNode[1][1] = 1;
	ElType[EL_TET4].dwFaceNode[1][2] = 3;

	ElType[EL_TET4].dwFaceNode[2][0] = 1;
	ElType[EL_TET4].dwFaceNode[2][1] = 2;
	ElType[EL_TET4].dwFaceNode[2][2] = 3;

	ElType[EL_TET4].dwFaceNode[3][0] = 2;
	ElType[EL_TET4].dwFaceNode[3][1] = 0;
	ElType[EL_TET4].dwFaceNode[3][2] = 3;

	ElType[EL_TET4].dwFaceNodeFlag[0] = 0x00000007;	// Each Face Node Flag
	ElType[EL_TET4].dwFaceNodeFlag[1] = 0x0000000b;
	ElType[EL_TET4].dwFaceNodeFlag[2] = 0x0000000e;
	ElType[EL_TET4].dwFaceNodeFlag[3] = 0x0000000d;

	// Link 
	ElType[EL_TET4].dwLinkType[0] = EL_TRI3;	// Each Link type
	ElType[EL_TET4].dwLinkType[1] = EL_TRI3;
	ElType[EL_TET4].dwLinkType[2] = EL_TRI3;
	ElType[EL_TET4].dwLinkType[3] = EL_TRI3;

	ElType[EL_TET4].dwLinkNodeCnt[0] = 3;
	ElType[EL_TET4].dwLinkNodeCnt[1] = 3;
	ElType[EL_TET4].dwLinkNodeCnt[2] = 3;
	ElType[EL_TET4].dwLinkNodeCnt[3] = 3;

	ElType[EL_TET4].dwLinkNode[0] = new DWORD[3];	// Each Link Node
	ElType[EL_TET4].dwLinkNode[1] = new DWORD[3];
	ElType[EL_TET4].dwLinkNode[2] = new DWORD[3];
	ElType[EL_TET4].dwLinkNode[3] = new DWORD[3];

	ElType[EL_TET4].dwLinkNode[0][0] = 0;
	ElType[EL_TET4].dwLinkNode[0][1] = 2;
	ElType[EL_TET4].dwLinkNode[0][2] = 1;

	ElType[EL_TET4].dwLinkNode[1][0] = 0;
	ElType[EL_TET4].dwLinkNode[1][1] = 1;
	ElType[EL_TET4].dwLinkNode[1][2] = 3;

	ElType[EL_TET4].dwLinkNode[2][0] = 1;
	ElType[EL_TET4].dwLinkNode[2][1] = 2;
	ElType[EL_TET4].dwLinkNode[2][2] = 3;

	ElType[EL_TET4].dwLinkNode[3][0] = 2;
	ElType[EL_TET4].dwLinkNode[3][1] = 0;
	ElType[EL_TET4].dwLinkNode[3][2] = 3;

	ElType[EL_TET4].dwLinkNodeFlag[0] = 0x00000007;	// Each Link Node Flag
	ElType[EL_TET4].dwLinkNodeFlag[1] = 0x0000000b;
	ElType[EL_TET4].dwLinkNodeFlag[2] = 0x0000000e;
	ElType[EL_TET4].dwLinkNodeFlag[3] = 0x0000000d;

	/////////////////////
	// Type 8 : EL_TET10

	// Basic Information
	ElType[EL_TET10].dwDim = 3;

	// Count
	ElType[EL_TET10].dwNodeCnt = 10;	
	ElType[EL_TET10].dwApexCnt = 4;	
	ElType[EL_TET10].dwMidCnt  = 6;	 
	ElType[EL_TET10].dwEdgeCnt = 6; 
	ElType[EL_TET10].dwFaceCnt = 4;
	ElType[EL_TET10].dwLinkCnt = 4;	

	// Edge
	ElType[EL_TET10].dwEdgeType[0] = EL_LINE3;
	ElType[EL_TET10].dwEdgeType[1] = EL_LINE3;
	ElType[EL_TET10].dwEdgeType[2] = EL_LINE3;
	ElType[EL_TET10].dwEdgeType[3] = EL_LINE3;
	ElType[EL_TET10].dwEdgeType[4] = EL_LINE3;
	ElType[EL_TET10].dwEdgeType[5] = EL_LINE3;

	ElType[EL_TET10].dwEdgeNode[0] = new DWORD[3];		// Each Edge Node
	ElType[EL_TET10].dwEdgeNode[1] = new DWORD[3];
	ElType[EL_TET10].dwEdgeNode[2] = new DWORD[3];
	ElType[EL_TET10].dwEdgeNode[3] = new DWORD[3];
	ElType[EL_TET10].dwEdgeNode[4] = new DWORD[3];
	ElType[EL_TET10].dwEdgeNode[5] = new DWORD[3];

	ElType[EL_TET10].dwEdgeNode[0][0] = 0;
	ElType[EL_TET10].dwEdgeNode[0][1] = 1;
	ElType[EL_TET10].dwEdgeNode[0][2] = 4;

	ElType[EL_TET10].dwEdgeNode[1][0] = 1;
	ElType[EL_TET10].dwEdgeNode[1][1] = 2;
	ElType[EL_TET10].dwEdgeNode[1][2] = 5;

	ElType[EL_TET10].dwEdgeNode[2][0] = 2;
	ElType[EL_TET10].dwEdgeNode[2][1] = 0;
	ElType[EL_TET10].dwEdgeNode[2][2] = 6;

	ElType[EL_TET10].dwEdgeNode[3][0] = 0;
	ElType[EL_TET10].dwEdgeNode[3][1] = 3;
	ElType[EL_TET10].dwEdgeNode[3][2] = 7;

	ElType[EL_TET10].dwEdgeNode[4][0] = 1;
	ElType[EL_TET10].dwEdgeNode[4][1] = 3;
	ElType[EL_TET10].dwEdgeNode[4][2] = 8;

	ElType[EL_TET10].dwEdgeNode[5][0] = 2;
	ElType[EL_TET10].dwEdgeNode[5][1] = 3;
	ElType[EL_TET10].dwEdgeNode[5][2] = 9;

	ElType[EL_TET10].dwEdgeNodeFlag[0] = 0x00000013; 	// Each Edge Node Flag
	ElType[EL_TET10].dwEdgeNodeFlag[1] = 0x00000026;
	ElType[EL_TET10].dwEdgeNodeFlag[2] = 0x00000045;
	ElType[EL_TET10].dwEdgeNodeFlag[3] = 0x00000089;
	ElType[EL_TET10].dwEdgeNodeFlag[4] = 0x0000010a;
	ElType[EL_TET10].dwEdgeNodeFlag[5] = 0x0000020c;

	// Face 
	ElType[EL_TET10].dwFaceType[0] = EL_TRI6;	// Each Face type
	ElType[EL_TET10].dwFaceType[1] = EL_TRI6;
	ElType[EL_TET10].dwFaceType[2] = EL_TRI6;
	ElType[EL_TET10].dwFaceType[3] = EL_TRI6;

	ElType[EL_TET10].dwFaceNode[0] = new DWORD[6];	// Each Face Node
	ElType[EL_TET10].dwFaceNode[1] = new DWORD[6];
	ElType[EL_TET10].dwFaceNode[2] = new DWORD[6];
	ElType[EL_TET10].dwFaceNode[3] = new DWORD[6];

	ElType[EL_TET10].dwFaceNode[0][0] = 0;
	ElType[EL_TET10].dwFaceNode[0][1] = 2;
	ElType[EL_TET10].dwFaceNode[0][2] = 1;
	ElType[EL_TET10].dwFaceNode[0][3] = 6;
	ElType[EL_TET10].dwFaceNode[0][4] = 5;
	ElType[EL_TET10].dwFaceNode[0][5] = 4;

	ElType[EL_TET10].dwFaceNode[1][0] = 0;
	ElType[EL_TET10].dwFaceNode[1][1] = 1;
	ElType[EL_TET10].dwFaceNode[1][2] = 3;
	ElType[EL_TET10].dwFaceNode[1][3] = 4;
	ElType[EL_TET10].dwFaceNode[1][4] = 8;
	ElType[EL_TET10].dwFaceNode[1][5] = 7;

	ElType[EL_TET10].dwFaceNode[2][0] = 1;
	ElType[EL_TET10].dwFaceNode[2][1] = 2;
	ElType[EL_TET10].dwFaceNode[2][2] = 3;
	ElType[EL_TET10].dwFaceNode[2][3] = 5;
	ElType[EL_TET10].dwFaceNode[2][4] = 9;
	ElType[EL_TET10].dwFaceNode[2][5] = 8;

	ElType[EL_TET10].dwFaceNode[3][0] = 2;
	ElType[EL_TET10].dwFaceNode[3][1] = 0;
	ElType[EL_TET10].dwFaceNode[3][2] = 3;
	ElType[EL_TET10].dwFaceNode[3][3] = 6;
	ElType[EL_TET10].dwFaceNode[3][4] = 7;
	ElType[EL_TET10].dwFaceNode[3][5] = 9;

	ElType[EL_TET10].dwFaceNodeFlag[0] = 0x00000077;	// Each Face Node Flag
	ElType[EL_TET10].dwFaceNodeFlag[1] = 0x0000019b;
	ElType[EL_TET10].dwFaceNodeFlag[2] = 0x0000032e;
	ElType[EL_TET10].dwFaceNodeFlag[3] = 0x000002cd;

	// Link 
	ElType[EL_TET10].dwLinkType[0] = EL_TRI3;	// Each Link type
	ElType[EL_TET10].dwLinkType[1] = EL_TRI3;
	ElType[EL_TET10].dwLinkType[2] = EL_TRI3;
	ElType[EL_TET10].dwLinkType[3] = EL_TRI3;

	ElType[EL_TET10].dwLinkNodeCnt[0] = 3;
	ElType[EL_TET10].dwLinkNodeCnt[1] = 3;
	ElType[EL_TET10].dwLinkNodeCnt[2] = 3;
	ElType[EL_TET10].dwLinkNodeCnt[3] = 3;

	ElType[EL_TET10].dwLinkNode[0] = new DWORD[3];	// Each Link Node
	ElType[EL_TET10].dwLinkNode[1] = new DWORD[3];
	ElType[EL_TET10].dwLinkNode[2] = new DWORD[3];
	ElType[EL_TET10].dwLinkNode[3] = new DWORD[3];

	ElType[EL_TET10].dwLinkNode[0][0] = 0;
	ElType[EL_TET10].dwLinkNode[0][1] = 2;
	ElType[EL_TET10].dwLinkNode[0][2] = 1;

	ElType[EL_TET10].dwLinkNode[1][0] = 0;
	ElType[EL_TET10].dwLinkNode[1][1] = 1;
	ElType[EL_TET10].dwLinkNode[1][2] = 3;

	ElType[EL_TET10].dwLinkNode[2][0] = 1;
	ElType[EL_TET10].dwLinkNode[2][1] = 2;
	ElType[EL_TET10].dwLinkNode[2][2] = 3;

	ElType[EL_TET10].dwLinkNode[3][0] = 2;
	ElType[EL_TET10].dwLinkNode[3][1] = 0;
	ElType[EL_TET10].dwLinkNode[3][2] = 3;

	ElType[EL_TET10].dwLinkNodeFlag[0] = 0x00000007;	// Each Link Node Flag
	ElType[EL_TET10].dwLinkNodeFlag[1] = 0x0000000b;
	ElType[EL_TET10].dwLinkNodeFlag[2] = 0x0000000e;
	ElType[EL_TET10].dwLinkNodeFlag[3] = 0x0000000d;

	/////////////////////
	// Type 10 : EL_HEX8

	// Basic Information
	ElType[EL_HEX8].dwDim = 3;

	// Count
	ElType[EL_HEX8].dwNodeCnt = 8;	
	ElType[EL_HEX8].dwApexCnt = 8;	
	ElType[EL_HEX8].dwMidCnt  = 0;	 
	ElType[EL_HEX8].dwEdgeCnt = 12; 
	ElType[EL_HEX8].dwFaceCnt = 6;
	ElType[EL_HEX8].dwLinkCnt = 6;	

	// Edge
	ElType[EL_HEX8].dwEdgeType[0] = EL_LINE2;
	ElType[EL_HEX8].dwEdgeType[1] = EL_LINE2;
	ElType[EL_HEX8].dwEdgeType[2] = EL_LINE2;
	ElType[EL_HEX8].dwEdgeType[3] = EL_LINE2;
	ElType[EL_HEX8].dwEdgeType[4] = EL_LINE2;
	ElType[EL_HEX8].dwEdgeType[5] = EL_LINE2;
	ElType[EL_HEX8].dwEdgeType[6] = EL_LINE2;
	ElType[EL_HEX8].dwEdgeType[7] = EL_LINE2;
	ElType[EL_HEX8].dwEdgeType[8] = EL_LINE2;
	ElType[EL_HEX8].dwEdgeType[9] = EL_LINE2;
	ElType[EL_HEX8].dwEdgeType[10] = EL_LINE2;
	ElType[EL_HEX8].dwEdgeType[11] = EL_LINE2;

	ElType[EL_HEX8].dwEdgeNode[0] = new DWORD[2];		// Each Edge Node
	ElType[EL_HEX8].dwEdgeNode[1] = new DWORD[2];
	ElType[EL_HEX8].dwEdgeNode[2] = new DWORD[2];
	ElType[EL_HEX8].dwEdgeNode[3] = new DWORD[2];
	ElType[EL_HEX8].dwEdgeNode[4] = new DWORD[2];
	ElType[EL_HEX8].dwEdgeNode[5] = new DWORD[2];
	ElType[EL_HEX8].dwEdgeNode[6] = new DWORD[2];
	ElType[EL_HEX8].dwEdgeNode[7] = new DWORD[2];
	ElType[EL_HEX8].dwEdgeNode[8] = new DWORD[2];
	ElType[EL_HEX8].dwEdgeNode[9] = new DWORD[2];
	ElType[EL_HEX8].dwEdgeNode[10] = new DWORD[2];
	ElType[EL_HEX8].dwEdgeNode[11] = new DWORD[2];

	ElType[EL_HEX8].dwEdgeNode[0][0] = 0;
	ElType[EL_HEX8].dwEdgeNode[0][1] = 1;

	ElType[EL_HEX8].dwEdgeNode[1][0] = 1;
	ElType[EL_HEX8].dwEdgeNode[1][1] = 2;

	ElType[EL_HEX8].dwEdgeNode[2][0] = 2;
	ElType[EL_HEX8].dwEdgeNode[2][1] = 3;

	ElType[EL_HEX8].dwEdgeNode[3][0] = 3;
	ElType[EL_HEX8].dwEdgeNode[3][1] = 0;

	ElType[EL_HEX8].dwEdgeNode[4][0] = 0;
	ElType[EL_HEX8].dwEdgeNode[4][1] = 4;

	ElType[EL_HEX8].dwEdgeNode[5][0] = 1;
	ElType[EL_HEX8].dwEdgeNode[5][1] = 5;

	ElType[EL_HEX8].dwEdgeNode[6][0] = 2;
	ElType[EL_HEX8].dwEdgeNode[6][1] = 6;

	ElType[EL_HEX8].dwEdgeNode[7][0] = 3;
	ElType[EL_HEX8].dwEdgeNode[7][1] = 7;

	ElType[EL_HEX8].dwEdgeNode[8][0] = 4;
	ElType[EL_HEX8].dwEdgeNode[8][1] = 5;

	ElType[EL_HEX8].dwEdgeNode[9][0] = 5;
	ElType[EL_HEX8].dwEdgeNode[9][1] = 6;

	ElType[EL_HEX8].dwEdgeNode[10][0] = 6;
	ElType[EL_HEX8].dwEdgeNode[10][1] = 7;

	ElType[EL_HEX8].dwEdgeNode[11][0] = 7;
	ElType[EL_HEX8].dwEdgeNode[11][1] = 4;

	ElType[EL_HEX8].dwEdgeNodeFlag[0] = 0x00000003; 	// Each Edge Node Flag
	ElType[EL_HEX8].dwEdgeNodeFlag[1] = 0x00000006;
	ElType[EL_HEX8].dwEdgeNodeFlag[2] = 0x0000000c;
	ElType[EL_HEX8].dwEdgeNodeFlag[3] = 0x00000009;
	ElType[EL_HEX8].dwEdgeNodeFlag[4] = 0x00000011;
	ElType[EL_HEX8].dwEdgeNodeFlag[5] = 0x00000022;
	ElType[EL_HEX8].dwEdgeNodeFlag[6] = 0x00000044;
	ElType[EL_HEX8].dwEdgeNodeFlag[7] = 0x00000088;
	ElType[EL_HEX8].dwEdgeNodeFlag[8] = 0x00000030;
	ElType[EL_HEX8].dwEdgeNodeFlag[9] = 0x00000060;
	ElType[EL_HEX8].dwEdgeNodeFlag[10] = 0x000000c0;
	ElType[EL_HEX8].dwEdgeNodeFlag[11] = 0x00000090;

	// Face 
	ElType[EL_HEX8].dwFaceType[0] = EL_QUAD4;	// Each Face type
	ElType[EL_HEX8].dwFaceType[1] = EL_QUAD4;
	ElType[EL_HEX8].dwFaceType[2] = EL_QUAD4;
	ElType[EL_HEX8].dwFaceType[3] = EL_QUAD4;
	ElType[EL_HEX8].dwFaceType[4] = EL_QUAD4;
	ElType[EL_HEX8].dwFaceType[5] = EL_QUAD4;

	ElType[EL_HEX8].dwFaceNode[0] = new DWORD[4];	// Each Face Node
	ElType[EL_HEX8].dwFaceNode[1] = new DWORD[4];
	ElType[EL_HEX8].dwFaceNode[2] = new DWORD[4];
	ElType[EL_HEX8].dwFaceNode[3] = new DWORD[4];
	ElType[EL_HEX8].dwFaceNode[4] = new DWORD[4];
	ElType[EL_HEX8].dwFaceNode[5] = new DWORD[4];

	ElType[EL_HEX8].dwFaceNode[0][0] = 0;
	ElType[EL_HEX8].dwFaceNode[0][1] = 3;
	ElType[EL_HEX8].dwFaceNode[0][2] = 2;
	ElType[EL_HEX8].dwFaceNode[0][3] = 1;

	ElType[EL_HEX8].dwFaceNode[1][0] = 4;
	ElType[EL_HEX8].dwFaceNode[1][1] = 5;
	ElType[EL_HEX8].dwFaceNode[1][2] = 6;
	ElType[EL_HEX8].dwFaceNode[1][3] = 7;

	ElType[EL_HEX8].dwFaceNode[2][0] = 0;
	ElType[EL_HEX8].dwFaceNode[2][1] = 1;
	ElType[EL_HEX8].dwFaceNode[2][2] = 5;
	ElType[EL_HEX8].dwFaceNode[2][3] = 4;

	ElType[EL_HEX8].dwFaceNode[3][0] = 2;
	ElType[EL_HEX8].dwFaceNode[3][1] = 3;
	ElType[EL_HEX8].dwFaceNode[3][2] = 7;
	ElType[EL_HEX8].dwFaceNode[3][3] = 6;

	ElType[EL_HEX8].dwFaceNode[4][0] = 1;
	ElType[EL_HEX8].dwFaceNode[4][1] = 2;
	ElType[EL_HEX8].dwFaceNode[4][2] = 6;
	ElType[EL_HEX8].dwFaceNode[4][3] = 5;

	ElType[EL_HEX8].dwFaceNode[5][0] = 0;
	ElType[EL_HEX8].dwFaceNode[5][1] = 4;
	ElType[EL_HEX8].dwFaceNode[5][2] = 7;
	ElType[EL_HEX8].dwFaceNode[5][3] = 3;

	ElType[EL_HEX8].dwFaceNodeFlag[0] = 0x0000000f;	// Each Face Node Flag
	ElType[EL_HEX8].dwFaceNodeFlag[1] = 0x000000f0;
	ElType[EL_HEX8].dwFaceNodeFlag[2] = 0x00000033;
	ElType[EL_HEX8].dwFaceNodeFlag[3] = 0x000000cc;
	ElType[EL_HEX8].dwFaceNodeFlag[4] = 0x00000066;
	ElType[EL_HEX8].dwFaceNodeFlag[5] = 0x00000099;

	// Link 
	ElType[EL_HEX8].dwLinkType[0] = EL_QUAD4;	// Each Link type
	ElType[EL_HEX8].dwLinkType[1] = EL_QUAD4;
	ElType[EL_HEX8].dwLinkType[2] = EL_QUAD4;
	ElType[EL_HEX8].dwLinkType[3] = EL_QUAD4;
	ElType[EL_HEX8].dwLinkType[4] = EL_QUAD4;
	ElType[EL_HEX8].dwLinkType[5] = EL_QUAD4;

	ElType[EL_HEX8].dwLinkNodeCnt[0] = 4;	// Each Link type
	ElType[EL_HEX8].dwLinkNodeCnt[1] = 4;
	ElType[EL_HEX8].dwLinkNodeCnt[2] = 4;
	ElType[EL_HEX8].dwLinkNodeCnt[3] = 4;
	ElType[EL_HEX8].dwLinkNodeCnt[4] = 4;
	ElType[EL_HEX8].dwLinkNodeCnt[5] = 4;

	ElType[EL_HEX8].dwLinkNode[0] = new DWORD[4];	// Each Link Node
	ElType[EL_HEX8].dwLinkNode[1] = new DWORD[4];
	ElType[EL_HEX8].dwLinkNode[2] = new DWORD[4];
	ElType[EL_HEX8].dwLinkNode[3] = new DWORD[4];
	ElType[EL_HEX8].dwLinkNode[4] = new DWORD[4];
	ElType[EL_HEX8].dwLinkNode[5] = new DWORD[4];

	ElType[EL_HEX8].dwLinkNode[0][0] = 0;
	ElType[EL_HEX8].dwLinkNode[0][1] = 3;
	ElType[EL_HEX8].dwLinkNode[0][2] = 2;
	ElType[EL_HEX8].dwLinkNode[0][3] = 1;

	ElType[EL_HEX8].dwLinkNode[1][0] = 4;
	ElType[EL_HEX8].dwLinkNode[1][1] = 5;
	ElType[EL_HEX8].dwLinkNode[1][2] = 6;
	ElType[EL_HEX8].dwLinkNode[1][3] = 7;

	ElType[EL_HEX8].dwLinkNode[2][0] = 0;
	ElType[EL_HEX8].dwLinkNode[2][1] = 1;
	ElType[EL_HEX8].dwLinkNode[2][2] = 5;
	ElType[EL_HEX8].dwLinkNode[2][3] = 4;

	ElType[EL_HEX8].dwLinkNode[3][0] = 2;
	ElType[EL_HEX8].dwLinkNode[3][1] = 3;
	ElType[EL_HEX8].dwLinkNode[3][2] = 7;
	ElType[EL_HEX8].dwLinkNode[3][3] = 6;

	ElType[EL_HEX8].dwLinkNode[4][0] = 1;
	ElType[EL_HEX8].dwLinkNode[4][1] = 2;
	ElType[EL_HEX8].dwLinkNode[4][2] = 6;
	ElType[EL_HEX8].dwLinkNode[4][3] = 5;

	ElType[EL_HEX8].dwLinkNode[5][0] = 0;
	ElType[EL_HEX8].dwLinkNode[5][1] = 4;
	ElType[EL_HEX8].dwLinkNode[5][2] = 7;
	ElType[EL_HEX8].dwLinkNode[5][3] = 3;

	ElType[EL_HEX8].dwLinkNodeFlag[0] = 0x0000000f;	// Each Link Node Flag
	ElType[EL_HEX8].dwLinkNodeFlag[1] = 0x000000f0;
	ElType[EL_HEX8].dwLinkNodeFlag[2] = 0x00000033;
	ElType[EL_HEX8].dwLinkNodeFlag[3] = 0x000000cc;
	ElType[EL_HEX8].dwLinkNodeFlag[4] = 0x00000066;
	ElType[EL_HEX8].dwLinkNodeFlag[5] = 0x00000099;

	/////////////////////
	// Type 10 : EL_HEX20

	// Basic Information
	ElType[EL_HEX20].dwDim = 3;

	// Count
	ElType[EL_HEX20].dwNodeCnt = 20;	
	ElType[EL_HEX20].dwApexCnt = 8;	
	ElType[EL_HEX20].dwMidCnt  = 12;	 
	ElType[EL_HEX20].dwEdgeCnt = 12; 
	ElType[EL_HEX20].dwFaceCnt = 6;
	ElType[EL_HEX20].dwLinkCnt = 6;	

	// Edge
	ElType[EL_HEX20].dwEdgeType[0] = EL_LINE3;
	ElType[EL_HEX20].dwEdgeType[1] = EL_LINE3;
	ElType[EL_HEX20].dwEdgeType[2] = EL_LINE3;
	ElType[EL_HEX20].dwEdgeType[3] = EL_LINE3;
	ElType[EL_HEX20].dwEdgeType[4] = EL_LINE3;
	ElType[EL_HEX20].dwEdgeType[5] = EL_LINE3;
	ElType[EL_HEX20].dwEdgeType[6] = EL_LINE3;
	ElType[EL_HEX20].dwEdgeType[7] = EL_LINE3;
	ElType[EL_HEX20].dwEdgeType[8] = EL_LINE3;
	ElType[EL_HEX20].dwEdgeType[9] = EL_LINE3;
	ElType[EL_HEX20].dwEdgeType[10] = EL_LINE3;
	ElType[EL_HEX20].dwEdgeType[11] = EL_LINE3;

	ElType[EL_HEX20].dwEdgeNode[0] = new DWORD[3];		// Each Edge Node
	ElType[EL_HEX20].dwEdgeNode[1] = new DWORD[3];
	ElType[EL_HEX20].dwEdgeNode[2] = new DWORD[3];
	ElType[EL_HEX20].dwEdgeNode[3] = new DWORD[3];
	ElType[EL_HEX20].dwEdgeNode[4] = new DWORD[3];
	ElType[EL_HEX20].dwEdgeNode[5] = new DWORD[3];
	ElType[EL_HEX20].dwEdgeNode[6] = new DWORD[3];
	ElType[EL_HEX20].dwEdgeNode[7] = new DWORD[3];
	ElType[EL_HEX20].dwEdgeNode[8] = new DWORD[3];
	ElType[EL_HEX20].dwEdgeNode[9] = new DWORD[3];
	ElType[EL_HEX20].dwEdgeNode[10] = new DWORD[3];
	ElType[EL_HEX20].dwEdgeNode[11] = new DWORD[3];

	ElType[EL_HEX20].dwEdgeNode[0][0] = 0;
	ElType[EL_HEX20].dwEdgeNode[0][1] = 1;
	ElType[EL_HEX20].dwEdgeNode[0][2] = 8;

	ElType[EL_HEX20].dwEdgeNode[1][0] = 1;
	ElType[EL_HEX20].dwEdgeNode[1][1] = 2;
	ElType[EL_HEX20].dwEdgeNode[1][2] = 9;

	ElType[EL_HEX20].dwEdgeNode[2][0] = 2;
	ElType[EL_HEX20].dwEdgeNode[2][1] = 3;
	ElType[EL_HEX20].dwEdgeNode[2][2] = 10;

	ElType[EL_HEX20].dwEdgeNode[3][0] = 3;
	ElType[EL_HEX20].dwEdgeNode[3][1] = 0;
	ElType[EL_HEX20].dwEdgeNode[3][2] = 11;

	ElType[EL_HEX20].dwEdgeNode[4][0] = 0;
	ElType[EL_HEX20].dwEdgeNode[4][1] = 4;
	ElType[EL_HEX20].dwEdgeNode[4][2] = 12;

	ElType[EL_HEX20].dwEdgeNode[5][0] = 1;
	ElType[EL_HEX20].dwEdgeNode[5][1] = 5;
	ElType[EL_HEX20].dwEdgeNode[5][2] = 13;

	ElType[EL_HEX20].dwEdgeNode[6][0] = 2;
	ElType[EL_HEX20].dwEdgeNode[6][1] = 6;
	ElType[EL_HEX20].dwEdgeNode[6][2] = 14;

	ElType[EL_HEX20].dwEdgeNode[7][0] = 3;
	ElType[EL_HEX20].dwEdgeNode[7][1] = 7;
	ElType[EL_HEX20].dwEdgeNode[7][2] = 15;

	ElType[EL_HEX20].dwEdgeNode[8][0] = 4;
	ElType[EL_HEX20].dwEdgeNode[8][1] = 5;
	ElType[EL_HEX20].dwEdgeNode[8][2] = 16;

	ElType[EL_HEX20].dwEdgeNode[9][0] = 5;
	ElType[EL_HEX20].dwEdgeNode[9][1] = 6;
	ElType[EL_HEX20].dwEdgeNode[9][2] = 17;

	ElType[EL_HEX20].dwEdgeNode[10][0] = 6;
	ElType[EL_HEX20].dwEdgeNode[10][1] = 7;
	ElType[EL_HEX20].dwEdgeNode[10][2] = 18;

	ElType[EL_HEX20].dwEdgeNode[11][0] = 7;
	ElType[EL_HEX20].dwEdgeNode[11][1] = 4;
	ElType[EL_HEX20].dwEdgeNode[11][2] = 19;

	ElType[EL_HEX20].dwEdgeNodeFlag[0] = 0x00000103; 	// Each Edge Node Flag
	ElType[EL_HEX20].dwEdgeNodeFlag[1] = 0x00000206;
	ElType[EL_HEX20].dwEdgeNodeFlag[2] = 0x0000040c;
	ElType[EL_HEX20].dwEdgeNodeFlag[3] = 0x00000809;
	ElType[EL_HEX20].dwEdgeNodeFlag[4] = 0x00001011;
	ElType[EL_HEX20].dwEdgeNodeFlag[5] = 0x00002022;
	ElType[EL_HEX20].dwEdgeNodeFlag[6] = 0x00004044;
	ElType[EL_HEX20].dwEdgeNodeFlag[7] = 0x00008088;
	ElType[EL_HEX20].dwEdgeNodeFlag[8] = 0x00010030;
	ElType[EL_HEX20].dwEdgeNodeFlag[9] = 0x00020060;
	ElType[EL_HEX20].dwEdgeNodeFlag[10] = 0x000400c0;
	ElType[EL_HEX20].dwEdgeNodeFlag[11] = 0x00080090;

	// Face 
	ElType[EL_HEX20].dwFaceType[0] = EL_QUAD8;	// Each Face type
	ElType[EL_HEX20].dwFaceType[1] = EL_QUAD8;
	ElType[EL_HEX20].dwFaceType[2] = EL_QUAD8;
	ElType[EL_HEX20].dwFaceType[3] = EL_QUAD8;
	ElType[EL_HEX20].dwFaceType[4] = EL_QUAD8;
	ElType[EL_HEX20].dwFaceType[5] = EL_QUAD8;

	ElType[EL_HEX20].dwFaceNode[0] = new DWORD[8];	// Each Face Node
	ElType[EL_HEX20].dwFaceNode[1] = new DWORD[8];
	ElType[EL_HEX20].dwFaceNode[2] = new DWORD[8];
	ElType[EL_HEX20].dwFaceNode[3] = new DWORD[8];
	ElType[EL_HEX20].dwFaceNode[4] = new DWORD[8];
	ElType[EL_HEX20].dwFaceNode[5] = new DWORD[8];

	ElType[EL_HEX20].dwFaceNode[0][0] = 0;
	ElType[EL_HEX20].dwFaceNode[0][1] = 3;
	ElType[EL_HEX20].dwFaceNode[0][2] = 2;
	ElType[EL_HEX20].dwFaceNode[0][3] = 1;
	ElType[EL_HEX20].dwFaceNode[0][4] = 11;
	ElType[EL_HEX20].dwFaceNode[0][5] = 10;
	ElType[EL_HEX20].dwFaceNode[0][6] = 9;
	ElType[EL_HEX20].dwFaceNode[0][7] = 8;

	ElType[EL_HEX20].dwFaceNode[1][0] = 4;
	ElType[EL_HEX20].dwFaceNode[1][1] = 5;
	ElType[EL_HEX20].dwFaceNode[1][2] = 6;
	ElType[EL_HEX20].dwFaceNode[1][3] = 7;
	ElType[EL_HEX20].dwFaceNode[1][4] = 16;
	ElType[EL_HEX20].dwFaceNode[1][5] = 17;
	ElType[EL_HEX20].dwFaceNode[1][6] = 18;
	ElType[EL_HEX20].dwFaceNode[1][7] = 19;

	ElType[EL_HEX20].dwFaceNode[2][0] = 0;
	ElType[EL_HEX20].dwFaceNode[2][1] = 1;
	ElType[EL_HEX20].dwFaceNode[2][2] = 5;
	ElType[EL_HEX20].dwFaceNode[2][3] = 4;
	ElType[EL_HEX20].dwFaceNode[2][4] = 8;
	ElType[EL_HEX20].dwFaceNode[2][5] = 13;
	ElType[EL_HEX20].dwFaceNode[2][6] = 16;
	ElType[EL_HEX20].dwFaceNode[2][7] = 12;

	ElType[EL_HEX20].dwFaceNode[3][0] = 2;
	ElType[EL_HEX20].dwFaceNode[3][1] = 3;
	ElType[EL_HEX20].dwFaceNode[3][2] = 7;
	ElType[EL_HEX20].dwFaceNode[3][3] = 6;
	ElType[EL_HEX20].dwFaceNode[3][4] = 10;
	ElType[EL_HEX20].dwFaceNode[3][5] = 15;
	ElType[EL_HEX20].dwFaceNode[3][6] = 18;
	ElType[EL_HEX20].dwFaceNode[3][7] = 14;

	ElType[EL_HEX20].dwFaceNode[4][0] = 1;
	ElType[EL_HEX20].dwFaceNode[4][1] = 2;
	ElType[EL_HEX20].dwFaceNode[4][2] = 6;
	ElType[EL_HEX20].dwFaceNode[4][3] = 5;
	ElType[EL_HEX20].dwFaceNode[4][4] = 9;
	ElType[EL_HEX20].dwFaceNode[4][5] = 14;
	ElType[EL_HEX20].dwFaceNode[4][6] = 17;
	ElType[EL_HEX20].dwFaceNode[4][7] = 13;

	ElType[EL_HEX20].dwFaceNode[5][0] = 0;
	ElType[EL_HEX20].dwFaceNode[5][1] = 4;
	ElType[EL_HEX20].dwFaceNode[5][2] = 7;
	ElType[EL_HEX20].dwFaceNode[5][3] = 3;
	ElType[EL_HEX20].dwFaceNode[5][4] = 12;
	ElType[EL_HEX20].dwFaceNode[5][5] = 19;
	ElType[EL_HEX20].dwFaceNode[5][6] = 15;
	ElType[EL_HEX20].dwFaceNode[5][7] = 11;

	ElType[EL_HEX20].dwFaceNodeFlag[0] = 0x00000f0f;	// Each Face Node Flag
	ElType[EL_HEX20].dwFaceNodeFlag[1] = 0x000f00f0;
	ElType[EL_HEX20].dwFaceNodeFlag[2] = 0x00013133;
	ElType[EL_HEX20].dwFaceNodeFlag[3] = 0x0004c4cc;
	ElType[EL_HEX20].dwFaceNodeFlag[4] = 0x00026266;
	ElType[EL_HEX20].dwFaceNodeFlag[5] = 0x00089899;

	// Link 
	ElType[EL_HEX20].dwLinkType[0] = EL_QUAD4;	// Each Link type
	ElType[EL_HEX20].dwLinkType[1] = EL_QUAD4;
	ElType[EL_HEX20].dwLinkType[2] = EL_QUAD4;
	ElType[EL_HEX20].dwLinkType[3] = EL_QUAD4;
	ElType[EL_HEX20].dwLinkType[4] = EL_QUAD4;
	ElType[EL_HEX20].dwLinkType[5] = EL_QUAD4;

	ElType[EL_HEX20].dwLinkNodeCnt[0] = 4;	// Each Link type
	ElType[EL_HEX20].dwLinkNodeCnt[1] = 4;
	ElType[EL_HEX20].dwLinkNodeCnt[2] = 4;
	ElType[EL_HEX20].dwLinkNodeCnt[3] = 4;
	ElType[EL_HEX20].dwLinkNodeCnt[4] = 4;
	ElType[EL_HEX20].dwLinkNodeCnt[5] = 4;

	ElType[EL_HEX20].dwLinkNode[0] = new DWORD[4];	// Each Link Node
	ElType[EL_HEX20].dwLinkNode[1] = new DWORD[4];
	ElType[EL_HEX20].dwLinkNode[2] = new DWORD[4];
	ElType[EL_HEX20].dwLinkNode[3] = new DWORD[4];
	ElType[EL_HEX20].dwLinkNode[4] = new DWORD[4];
	ElType[EL_HEX20].dwLinkNode[5] = new DWORD[4];

	ElType[EL_HEX20].dwLinkNode[0][0] = 0;
	ElType[EL_HEX20].dwLinkNode[0][1] = 3;
	ElType[EL_HEX20].dwLinkNode[0][2] = 2;
	ElType[EL_HEX20].dwLinkNode[0][3] = 1;

	ElType[EL_HEX20].dwLinkNode[1][0] = 4;
	ElType[EL_HEX20].dwLinkNode[1][1] = 5;
	ElType[EL_HEX20].dwLinkNode[1][2] = 6;
	ElType[EL_HEX20].dwLinkNode[1][3] = 7;

	ElType[EL_HEX20].dwLinkNode[2][0] = 0;
	ElType[EL_HEX20].dwLinkNode[2][1] = 1;
	ElType[EL_HEX20].dwLinkNode[2][2] = 5;
	ElType[EL_HEX20].dwLinkNode[2][3] = 4;

	ElType[EL_HEX20].dwLinkNode[3][0] = 2;
	ElType[EL_HEX20].dwLinkNode[3][1] = 3;
	ElType[EL_HEX20].dwLinkNode[3][2] = 7;
	ElType[EL_HEX20].dwLinkNode[3][3] = 6;

	ElType[EL_HEX20].dwLinkNode[4][0] = 1;
	ElType[EL_HEX20].dwLinkNode[4][1] = 2;
	ElType[EL_HEX20].dwLinkNode[4][2] = 6;
	ElType[EL_HEX20].dwLinkNode[4][3] = 5;

	ElType[EL_HEX20].dwLinkNode[5][0] = 0;
	ElType[EL_HEX20].dwLinkNode[5][1] = 4;
	ElType[EL_HEX20].dwLinkNode[5][2] = 7;
	ElType[EL_HEX20].dwLinkNode[5][3] = 3;

	ElType[EL_HEX20].dwLinkNodeFlag[0] = 0x0000000f;	// Each Link Node Flag
	ElType[EL_HEX20].dwLinkNodeFlag[1] = 0x000000f0;
	ElType[EL_HEX20].dwLinkNodeFlag[2] = 0x00000033;
	ElType[EL_HEX20].dwLinkNodeFlag[3] = 0x000000cc;
	ElType[EL_HEX20].dwLinkNodeFlag[4] = 0x00000066;
	ElType[EL_HEX20].dwLinkNodeFlag[5] = 0x00000099;

	/////////////////////
	// Type 12 : EL_PRISM6

	// Basic Information
	ElType[EL_PRISM6].dwDim = 3;

	// Count
	ElType[EL_PRISM6].dwNodeCnt = 6;	
	ElType[EL_PRISM6].dwApexCnt = 6;	
	ElType[EL_PRISM6].dwMidCnt  = 0;	 
	ElType[EL_PRISM6].dwEdgeCnt = 9; 
	ElType[EL_PRISM6].dwFaceCnt = 5;
	ElType[EL_PRISM6].dwLinkCnt = 5;	

	// Edge
	ElType[EL_PRISM6].dwEdgeType[0] = EL_LINE2;
	ElType[EL_PRISM6].dwEdgeType[1] = EL_LINE2;
	ElType[EL_PRISM6].dwEdgeType[2] = EL_LINE2;
	ElType[EL_PRISM6].dwEdgeType[3] = EL_LINE2;
	ElType[EL_PRISM6].dwEdgeType[4] = EL_LINE2;
	ElType[EL_PRISM6].dwEdgeType[5] = EL_LINE2;
	ElType[EL_PRISM6].dwEdgeType[6] = EL_LINE2;
	ElType[EL_PRISM6].dwEdgeType[7] = EL_LINE2;
	ElType[EL_PRISM6].dwEdgeType[8] = EL_LINE2;

	ElType[EL_PRISM6].dwEdgeNode[0] = new DWORD[2];		// Each Edge Node
	ElType[EL_PRISM6].dwEdgeNode[1] = new DWORD[2];
	ElType[EL_PRISM6].dwEdgeNode[2] = new DWORD[2];
	ElType[EL_PRISM6].dwEdgeNode[3] = new DWORD[2];
	ElType[EL_PRISM6].dwEdgeNode[4] = new DWORD[2];
	ElType[EL_PRISM6].dwEdgeNode[5] = new DWORD[2];
	ElType[EL_PRISM6].dwEdgeNode[6] = new DWORD[2];
	ElType[EL_PRISM6].dwEdgeNode[7] = new DWORD[2];
	ElType[EL_PRISM6].dwEdgeNode[8] = new DWORD[2];

	ElType[EL_PRISM6].dwEdgeNode[0][0] = 0;
	ElType[EL_PRISM6].dwEdgeNode[0][1] = 1;

	ElType[EL_PRISM6].dwEdgeNode[1][0] = 1;
	ElType[EL_PRISM6].dwEdgeNode[1][1] = 2;

	ElType[EL_PRISM6].dwEdgeNode[2][0] = 2;
	ElType[EL_PRISM6].dwEdgeNode[2][1] = 0;

	ElType[EL_PRISM6].dwEdgeNode[3][0] = 0;
	ElType[EL_PRISM6].dwEdgeNode[3][1] = 3;

	ElType[EL_PRISM6].dwEdgeNode[4][0] = 1;
	ElType[EL_PRISM6].dwEdgeNode[4][1] = 4;

	ElType[EL_PRISM6].dwEdgeNode[5][0] = 2;
	ElType[EL_PRISM6].dwEdgeNode[5][1] = 5;

	ElType[EL_PRISM6].dwEdgeNode[6][0] = 3;
	ElType[EL_PRISM6].dwEdgeNode[6][1] = 4;

	ElType[EL_PRISM6].dwEdgeNode[7][0] = 4;
	ElType[EL_PRISM6].dwEdgeNode[7][1] = 5;

	ElType[EL_PRISM6].dwEdgeNode[8][0] = 5;
	ElType[EL_PRISM6].dwEdgeNode[8][1] = 3;

	ElType[EL_PRISM6].dwEdgeNodeFlag[0] = 0x00000003; 	// Each Edge Node Flag
	ElType[EL_PRISM6].dwEdgeNodeFlag[1] = 0x00000006;
	ElType[EL_PRISM6].dwEdgeNodeFlag[2] = 0x00000005;
	ElType[EL_PRISM6].dwEdgeNodeFlag[3] = 0x00000009;
	ElType[EL_PRISM6].dwEdgeNodeFlag[4] = 0x00000012;
	ElType[EL_PRISM6].dwEdgeNodeFlag[5] = 0x00000024;
	ElType[EL_PRISM6].dwEdgeNodeFlag[6] = 0x00000018;
	ElType[EL_PRISM6].dwEdgeNodeFlag[7] = 0x00000030;
	ElType[EL_PRISM6].dwEdgeNodeFlag[8] = 0x00000028;

	// Face 
	ElType[EL_PRISM6].dwFaceType[0] = EL_TRI3;	// Each Face type
	ElType[EL_PRISM6].dwFaceType[1] = EL_TRI3;
	ElType[EL_PRISM6].dwFaceType[2] = EL_QUAD4;
	ElType[EL_PRISM6].dwFaceType[3] = EL_QUAD4;
	ElType[EL_PRISM6].dwFaceType[4] = EL_QUAD4;

	ElType[EL_PRISM6].dwFaceNode[0] = new DWORD[3];	// Each Face Node
	ElType[EL_PRISM6].dwFaceNode[1] = new DWORD[3];
	ElType[EL_PRISM6].dwFaceNode[2] = new DWORD[4];
	ElType[EL_PRISM6].dwFaceNode[3] = new DWORD[4];
	ElType[EL_PRISM6].dwFaceNode[4] = new DWORD[4];

	ElType[EL_PRISM6].dwFaceNode[0][0] = 0;
	ElType[EL_PRISM6].dwFaceNode[0][1] = 2;
	ElType[EL_PRISM6].dwFaceNode[0][2] = 1;

	ElType[EL_PRISM6].dwFaceNode[1][0] = 3;
	ElType[EL_PRISM6].dwFaceNode[1][1] = 4;
	ElType[EL_PRISM6].dwFaceNode[1][2] = 5;

	ElType[EL_PRISM6].dwFaceNode[2][0] = 0;
	ElType[EL_PRISM6].dwFaceNode[2][1] = 1;
	ElType[EL_PRISM6].dwFaceNode[2][2] = 4;
	ElType[EL_PRISM6].dwFaceNode[2][3] = 3;

	ElType[EL_PRISM6].dwFaceNode[3][0] = 1;
	ElType[EL_PRISM6].dwFaceNode[3][1] = 2;
	ElType[EL_PRISM6].dwFaceNode[3][2] = 5;
	ElType[EL_PRISM6].dwFaceNode[3][3] = 4;

	ElType[EL_PRISM6].dwFaceNode[4][0] = 2;
	ElType[EL_PRISM6].dwFaceNode[4][1] = 0;
	ElType[EL_PRISM6].dwFaceNode[4][2] = 3;
	ElType[EL_PRISM6].dwFaceNode[4][3] = 5;

	ElType[EL_PRISM6].dwFaceNodeFlag[0] = 0x00000007;	// Each Face Node Flag
	ElType[EL_PRISM6].dwFaceNodeFlag[1] = 0x00000038;
	ElType[EL_PRISM6].dwFaceNodeFlag[2] = 0x0000001b;
	ElType[EL_PRISM6].dwFaceNodeFlag[3] = 0x00000036;
	ElType[EL_PRISM6].dwFaceNodeFlag[4] = 0x0000002d;

	// Link 
	ElType[EL_PRISM6].dwLinkType[0] = EL_TRI3;	// Each Link type
	ElType[EL_PRISM6].dwLinkType[1] = EL_TRI3;
	ElType[EL_PRISM6].dwLinkType[2] = EL_QUAD4;
	ElType[EL_PRISM6].dwLinkType[3] = EL_QUAD4;
	ElType[EL_PRISM6].dwLinkType[4] = EL_QUAD4;

	ElType[EL_PRISM6].dwLinkNodeCnt[0] = 3;	// Each Link type
	ElType[EL_PRISM6].dwLinkNodeCnt[1] = 3;
	ElType[EL_PRISM6].dwLinkNodeCnt[2] = 4;
	ElType[EL_PRISM6].dwLinkNodeCnt[3] = 4;
	ElType[EL_PRISM6].dwLinkNodeCnt[4] = 4;

	ElType[EL_PRISM6].dwLinkNode[0] = new DWORD[3];	// Each Link Node
	ElType[EL_PRISM6].dwLinkNode[1] = new DWORD[3];
	ElType[EL_PRISM6].dwLinkNode[2] = new DWORD[4];
	ElType[EL_PRISM6].dwLinkNode[3] = new DWORD[4];
	ElType[EL_PRISM6].dwLinkNode[4] = new DWORD[4];

	ElType[EL_PRISM6].dwLinkNode[0][0] = 0;
	ElType[EL_PRISM6].dwLinkNode[0][1] = 2;
	ElType[EL_PRISM6].dwLinkNode[0][2] = 1;

	ElType[EL_PRISM6].dwLinkNode[1][0] = 3;
	ElType[EL_PRISM6].dwLinkNode[1][1] = 4;
	ElType[EL_PRISM6].dwLinkNode[1][2] = 5;

	ElType[EL_PRISM6].dwLinkNode[2][0] = 0;
	ElType[EL_PRISM6].dwLinkNode[2][1] = 1;
	ElType[EL_PRISM6].dwLinkNode[2][2] = 4;
	ElType[EL_PRISM6].dwLinkNode[2][3] = 3;

	ElType[EL_PRISM6].dwLinkNode[3][0] = 1;
	ElType[EL_PRISM6].dwLinkNode[3][1] = 2;
	ElType[EL_PRISM6].dwLinkNode[3][2] = 5;
	ElType[EL_PRISM6].dwLinkNode[3][3] = 4;

	ElType[EL_PRISM6].dwLinkNode[4][0] = 2;
	ElType[EL_PRISM6].dwLinkNode[4][1] = 0;
	ElType[EL_PRISM6].dwLinkNode[4][2] = 3;
	ElType[EL_PRISM6].dwLinkNode[4][3] = 5;

	ElType[EL_PRISM6].dwLinkNodeFlag[0] = 0x00000007;	// Each Link Node Flag
	ElType[EL_PRISM6].dwLinkNodeFlag[1] = 0x00000038;
	ElType[EL_PRISM6].dwLinkNodeFlag[2] = 0x0000001b;
	ElType[EL_PRISM6].dwLinkNodeFlag[3] = 0x00000036;
	ElType[EL_PRISM6].dwLinkNodeFlag[4] = 0x0000002d;

	/////////////////////
	// Type 13 : EL_PRISM15

	// Basic Information
	ElType[EL_PRISM15].dwDim = 3;

	// Count
	ElType[EL_PRISM15].dwNodeCnt = 15;	
	ElType[EL_PRISM15].dwApexCnt = 6;	
	ElType[EL_PRISM15].dwMidCnt  = 9;	 
	ElType[EL_PRISM15].dwEdgeCnt = 9; 
	ElType[EL_PRISM15].dwFaceCnt = 5;
	ElType[EL_PRISM15].dwLinkCnt = 5;	

	// Edge
	ElType[EL_PRISM15].dwEdgeType[0] = EL_LINE3;
	ElType[EL_PRISM15].dwEdgeType[1] = EL_LINE3;
	ElType[EL_PRISM15].dwEdgeType[2] = EL_LINE3;
	ElType[EL_PRISM15].dwEdgeType[3] = EL_LINE3;
	ElType[EL_PRISM15].dwEdgeType[4] = EL_LINE3;
	ElType[EL_PRISM15].dwEdgeType[5] = EL_LINE3;
	ElType[EL_PRISM15].dwEdgeType[6] = EL_LINE3;
	ElType[EL_PRISM15].dwEdgeType[7] = EL_LINE3;
	ElType[EL_PRISM15].dwEdgeType[8] = EL_LINE3;

	ElType[EL_PRISM15].dwEdgeNode[0] = new DWORD[3];		// Each Edge Node
	ElType[EL_PRISM15].dwEdgeNode[1] = new DWORD[3];
	ElType[EL_PRISM15].dwEdgeNode[2] = new DWORD[3];
	ElType[EL_PRISM15].dwEdgeNode[3] = new DWORD[3];
	ElType[EL_PRISM15].dwEdgeNode[4] = new DWORD[3];
	ElType[EL_PRISM15].dwEdgeNode[5] = new DWORD[3];
	ElType[EL_PRISM15].dwEdgeNode[6] = new DWORD[3];
	ElType[EL_PRISM15].dwEdgeNode[7] = new DWORD[3];
	ElType[EL_PRISM15].dwEdgeNode[8] = new DWORD[3];

	ElType[EL_PRISM15].dwEdgeNode[0][0] = 0;
	ElType[EL_PRISM15].dwEdgeNode[0][1] = 1;
	ElType[EL_PRISM15].dwEdgeNode[0][2] = 6;

	ElType[EL_PRISM15].dwEdgeNode[1][0] = 1;
	ElType[EL_PRISM15].dwEdgeNode[1][1] = 2;
	ElType[EL_PRISM15].dwEdgeNode[1][2] = 7;

	ElType[EL_PRISM15].dwEdgeNode[2][0] = 2;
	ElType[EL_PRISM15].dwEdgeNode[2][1] = 0;
	ElType[EL_PRISM15].dwEdgeNode[2][2] = 8;

	ElType[EL_PRISM15].dwEdgeNode[3][0] = 0;
	ElType[EL_PRISM15].dwEdgeNode[3][1] = 3;
	ElType[EL_PRISM15].dwEdgeNode[3][2] = 9;

	ElType[EL_PRISM15].dwEdgeNode[4][0] = 1;
	ElType[EL_PRISM15].dwEdgeNode[4][1] = 4;
	ElType[EL_PRISM15].dwEdgeNode[4][2] = 10;

	ElType[EL_PRISM15].dwEdgeNode[5][0] = 2;
	ElType[EL_PRISM15].dwEdgeNode[5][1] = 5;
	ElType[EL_PRISM15].dwEdgeNode[5][2] = 11;

	ElType[EL_PRISM15].dwEdgeNode[6][0] = 3;
	ElType[EL_PRISM15].dwEdgeNode[6][1] = 4;
	ElType[EL_PRISM15].dwEdgeNode[6][2] = 12;

	ElType[EL_PRISM15].dwEdgeNode[7][0] = 4;
	ElType[EL_PRISM15].dwEdgeNode[7][1] = 5;
	ElType[EL_PRISM15].dwEdgeNode[7][2] = 13;

	ElType[EL_PRISM15].dwEdgeNode[8][0] = 5;
	ElType[EL_PRISM15].dwEdgeNode[8][1] = 3;
	ElType[EL_PRISM15].dwEdgeNode[8][2] = 14;

	ElType[EL_PRISM15].dwEdgeNodeFlag[0] = 0x00000043; 	// Each Edge Node Flag
	ElType[EL_PRISM15].dwEdgeNodeFlag[1] = 0x00000086;
	ElType[EL_PRISM15].dwEdgeNodeFlag[2] = 0x00000105;
	ElType[EL_PRISM15].dwEdgeNodeFlag[3] = 0x00000209;
	ElType[EL_PRISM15].dwEdgeNodeFlag[4] = 0x00000412;
	ElType[EL_PRISM15].dwEdgeNodeFlag[5] = 0x00000824;
	ElType[EL_PRISM15].dwEdgeNodeFlag[6] = 0x00001018;
	ElType[EL_PRISM15].dwEdgeNodeFlag[7] = 0x00002030;
	ElType[EL_PRISM15].dwEdgeNodeFlag[8] = 0x00004028;

	// Face 
	ElType[EL_PRISM15].dwFaceType[0] = EL_TRI6;	// Each Face type
	ElType[EL_PRISM15].dwFaceType[1] = EL_TRI6;
	ElType[EL_PRISM15].dwFaceType[2] = EL_QUAD8;
	ElType[EL_PRISM15].dwFaceType[3] = EL_QUAD8;
	ElType[EL_PRISM15].dwFaceType[4] = EL_QUAD8;

	ElType[EL_PRISM15].dwFaceNode[0] = new DWORD[6];	// Each Face Node
	ElType[EL_PRISM15].dwFaceNode[1] = new DWORD[6];
	ElType[EL_PRISM15].dwFaceNode[2] = new DWORD[8];
	ElType[EL_PRISM15].dwFaceNode[3] = new DWORD[8];
	ElType[EL_PRISM15].dwFaceNode[4] = new DWORD[8];

	ElType[EL_PRISM15].dwFaceNode[0][0] = 0;
	ElType[EL_PRISM15].dwFaceNode[0][1] = 2;
	ElType[EL_PRISM15].dwFaceNode[0][2] = 1;
	ElType[EL_PRISM15].dwFaceNode[0][3] = 8;
	ElType[EL_PRISM15].dwFaceNode[0][4] = 7;
	ElType[EL_PRISM15].dwFaceNode[0][5] = 6;

	ElType[EL_PRISM15].dwFaceNode[1][0] = 3;
	ElType[EL_PRISM15].dwFaceNode[1][1] = 4;
	ElType[EL_PRISM15].dwFaceNode[1][2] = 5;
	ElType[EL_PRISM15].dwFaceNode[1][3] = 12;
	ElType[EL_PRISM15].dwFaceNode[1][4] = 13;
	ElType[EL_PRISM15].dwFaceNode[1][5] = 14;

	ElType[EL_PRISM15].dwFaceNode[2][0] = 0;
	ElType[EL_PRISM15].dwFaceNode[2][1] = 1;
	ElType[EL_PRISM15].dwFaceNode[2][2] = 4;
	ElType[EL_PRISM15].dwFaceNode[2][3] = 3;
	ElType[EL_PRISM15].dwFaceNode[2][4] = 6;
	ElType[EL_PRISM15].dwFaceNode[2][5] = 10;
	ElType[EL_PRISM15].dwFaceNode[2][6] = 12;
	ElType[EL_PRISM15].dwFaceNode[2][7] = 9;

	ElType[EL_PRISM15].dwFaceNode[3][0] = 1;
	ElType[EL_PRISM15].dwFaceNode[3][1] = 2;
	ElType[EL_PRISM15].dwFaceNode[3][2] = 5;
	ElType[EL_PRISM15].dwFaceNode[3][3] = 4;
	ElType[EL_PRISM15].dwFaceNode[3][4] = 7;
	ElType[EL_PRISM15].dwFaceNode[3][5] = 11;
	ElType[EL_PRISM15].dwFaceNode[3][6] = 13;
	ElType[EL_PRISM15].dwFaceNode[3][7] = 10;

	ElType[EL_PRISM15].dwFaceNode[4][0] = 2;
	ElType[EL_PRISM15].dwFaceNode[4][1] = 0;
	ElType[EL_PRISM15].dwFaceNode[4][2] = 3;
	ElType[EL_PRISM15].dwFaceNode[4][3] = 5;
	ElType[EL_PRISM15].dwFaceNode[4][4] = 8;
	ElType[EL_PRISM15].dwFaceNode[4][5] = 9;
	ElType[EL_PRISM15].dwFaceNode[4][6] = 14;
	ElType[EL_PRISM15].dwFaceNode[4][7] = 11;

	ElType[EL_PRISM15].dwFaceNodeFlag[0] = 0x000001c7;	// Each Face Node Flag
	ElType[EL_PRISM15].dwFaceNodeFlag[1] = 0x00007038;
	ElType[EL_PRISM15].dwFaceNodeFlag[2] = 0x0000165b;
	ElType[EL_PRISM15].dwFaceNodeFlag[3] = 0x00002cb6;
	ElType[EL_PRISM15].dwFaceNodeFlag[4] = 0x00004b2d;

	// Link 
	ElType[EL_PRISM15].dwLinkType[0] = EL_TRI3;	// Each Link type
	ElType[EL_PRISM15].dwLinkType[1] = EL_TRI3;
	ElType[EL_PRISM15].dwLinkType[2] = EL_QUAD4;
	ElType[EL_PRISM15].dwLinkType[3] = EL_QUAD4;
	ElType[EL_PRISM15].dwLinkType[4] = EL_QUAD4;

	ElType[EL_PRISM15].dwLinkNodeCnt[0] = 3;	// Each Link type
	ElType[EL_PRISM15].dwLinkNodeCnt[1] = 3;
	ElType[EL_PRISM15].dwLinkNodeCnt[2] = 4;
	ElType[EL_PRISM15].dwLinkNodeCnt[3] = 4;
	ElType[EL_PRISM15].dwLinkNodeCnt[4] = 4;

	ElType[EL_PRISM15].dwLinkNode[0] = new DWORD[3];	// Each Link Node
	ElType[EL_PRISM15].dwLinkNode[1] = new DWORD[3];
	ElType[EL_PRISM15].dwLinkNode[2] = new DWORD[4];
	ElType[EL_PRISM15].dwLinkNode[3] = new DWORD[4];
	ElType[EL_PRISM15].dwLinkNode[4] = new DWORD[4];

	ElType[EL_PRISM15].dwLinkNode[0][0] = 0;
	ElType[EL_PRISM15].dwLinkNode[0][1] = 2;
	ElType[EL_PRISM15].dwLinkNode[0][2] = 1;

	ElType[EL_PRISM15].dwLinkNode[1][0] = 3;
	ElType[EL_PRISM15].dwLinkNode[1][1] = 4;
	ElType[EL_PRISM15].dwLinkNode[1][2] = 5;

	ElType[EL_PRISM15].dwLinkNode[2][0] = 0;
	ElType[EL_PRISM15].dwLinkNode[2][1] = 1;
	ElType[EL_PRISM15].dwLinkNode[2][2] = 4;
	ElType[EL_PRISM15].dwLinkNode[2][3] = 3;

	ElType[EL_PRISM15].dwLinkNode[3][0] = 1;
	ElType[EL_PRISM15].dwLinkNode[3][1] = 2;
	ElType[EL_PRISM15].dwLinkNode[3][2] = 5;
	ElType[EL_PRISM15].dwLinkNode[3][3] = 4;

	ElType[EL_PRISM15].dwLinkNode[4][0] = 2;
	ElType[EL_PRISM15].dwLinkNode[4][1] = 0;
	ElType[EL_PRISM15].dwLinkNode[4][2] = 3;
	ElType[EL_PRISM15].dwLinkNode[4][3] = 5;

	ElType[EL_PRISM15].dwLinkNodeFlag[0] = 0x00000007;	// Each Link Node Flag
	ElType[EL_PRISM15].dwLinkNodeFlag[1] = 0x00000038;
	ElType[EL_PRISM15].dwLinkNodeFlag[2] = 0x0000001b;
	ElType[EL_PRISM15].dwLinkNodeFlag[3] = 0x00000036;
	ElType[EL_PRISM15].dwLinkNodeFlag[4] = 0x0000002d;

	/////////////////////
	// Type 14 : EL_PYRAMID5

	// Basic Information
	ElType[EL_PYRAMID5].dwDim = 3;

	// Count
	ElType[EL_PYRAMID5].dwNodeCnt = 5;	
	ElType[EL_PYRAMID5].dwApexCnt = 5;	
	ElType[EL_PYRAMID5].dwMidCnt  = 0;	 
	ElType[EL_PYRAMID5].dwEdgeCnt = 8; 
	ElType[EL_PYRAMID5].dwFaceCnt = 5;
	ElType[EL_PYRAMID5].dwLinkCnt = 5;	

	// Edge
	ElType[EL_PYRAMID5].dwEdgeType[0] = EL_LINE2;
	ElType[EL_PYRAMID5].dwEdgeType[1] = EL_LINE2;
	ElType[EL_PYRAMID5].dwEdgeType[2] = EL_LINE2;
	ElType[EL_PYRAMID5].dwEdgeType[3] = EL_LINE2;
	ElType[EL_PYRAMID5].dwEdgeType[4] = EL_LINE2;
	ElType[EL_PYRAMID5].dwEdgeType[5] = EL_LINE2;
	ElType[EL_PYRAMID5].dwEdgeType[6] = EL_LINE2;
	ElType[EL_PYRAMID5].dwEdgeType[7] = EL_LINE2;

	ElType[EL_PYRAMID5].dwEdgeNode[0] = new DWORD[2];		// Each Edge Node
	ElType[EL_PYRAMID5].dwEdgeNode[1] = new DWORD[2];
	ElType[EL_PYRAMID5].dwEdgeNode[2] = new DWORD[2];
	ElType[EL_PYRAMID5].dwEdgeNode[3] = new DWORD[2];
	ElType[EL_PYRAMID5].dwEdgeNode[4] = new DWORD[2];
	ElType[EL_PYRAMID5].dwEdgeNode[5] = new DWORD[2];
	ElType[EL_PYRAMID5].dwEdgeNode[6] = new DWORD[2];
	ElType[EL_PYRAMID5].dwEdgeNode[7] = new DWORD[2];

	ElType[EL_PYRAMID5].dwEdgeNode[0][0] = 0;
	ElType[EL_PYRAMID5].dwEdgeNode[0][1] = 1;

	ElType[EL_PYRAMID5].dwEdgeNode[1][0] = 1;
	ElType[EL_PYRAMID5].dwEdgeNode[1][1] = 2;

	ElType[EL_PYRAMID5].dwEdgeNode[2][0] = 2;
	ElType[EL_PYRAMID5].dwEdgeNode[2][1] = 3;

	ElType[EL_PYRAMID5].dwEdgeNode[3][0] = 3;
	ElType[EL_PYRAMID5].dwEdgeNode[3][1] = 0;

	ElType[EL_PYRAMID5].dwEdgeNode[4][0] = 0;
	ElType[EL_PYRAMID5].dwEdgeNode[4][1] = 4;

	ElType[EL_PYRAMID5].dwEdgeNode[5][0] = 1;
	ElType[EL_PYRAMID5].dwEdgeNode[5][1] = 4;

	ElType[EL_PYRAMID5].dwEdgeNode[6][0] = 2;
	ElType[EL_PYRAMID5].dwEdgeNode[6][1] = 4;

	ElType[EL_PYRAMID5].dwEdgeNode[7][0] = 3;
	ElType[EL_PYRAMID5].dwEdgeNode[7][1] = 4;

	ElType[EL_PYRAMID5].dwEdgeNodeFlag[0] = 0x00000003; 	// Each Edge Node Flag
	ElType[EL_PYRAMID5].dwEdgeNodeFlag[1] = 0x00000006;
	ElType[EL_PYRAMID5].dwEdgeNodeFlag[2] = 0x0000000c;
	ElType[EL_PYRAMID5].dwEdgeNodeFlag[3] = 0x00000009;
	ElType[EL_PYRAMID5].dwEdgeNodeFlag[4] = 0x00000011;
	ElType[EL_PYRAMID5].dwEdgeNodeFlag[5] = 0x00000012;
	ElType[EL_PYRAMID5].dwEdgeNodeFlag[6] = 0x00000014;
	ElType[EL_PYRAMID5].dwEdgeNodeFlag[7] = 0x00000018;

	// Face 
	ElType[EL_PYRAMID5].dwFaceType[0] = EL_QUAD4;	// Each Face type
	ElType[EL_PYRAMID5].dwFaceType[1] = EL_TRI3;
	ElType[EL_PYRAMID5].dwFaceType[2] = EL_TRI3;
	ElType[EL_PYRAMID5].dwFaceType[3] = EL_TRI3;
	ElType[EL_PYRAMID5].dwFaceType[4] = EL_TRI3;

	ElType[EL_PYRAMID5].dwFaceNode[0] = new DWORD[4];	// Each Face Node
	ElType[EL_PYRAMID5].dwFaceNode[1] = new DWORD[3];
	ElType[EL_PYRAMID5].dwFaceNode[2] = new DWORD[3];
	ElType[EL_PYRAMID5].dwFaceNode[3] = new DWORD[3];
	ElType[EL_PYRAMID5].dwFaceNode[4] = new DWORD[3];

	ElType[EL_PYRAMID5].dwFaceNode[0][0] = 0;
	ElType[EL_PYRAMID5].dwFaceNode[0][1] = 3;
	ElType[EL_PYRAMID5].dwFaceNode[0][2] = 2;
	ElType[EL_PYRAMID5].dwFaceNode[0][3] = 1;

	ElType[EL_PYRAMID5].dwFaceNode[1][0] = 0;
	ElType[EL_PYRAMID5].dwFaceNode[1][1] = 1;
	ElType[EL_PYRAMID5].dwFaceNode[1][2] = 4;

	ElType[EL_PYRAMID5].dwFaceNode[2][0] = 1;
	ElType[EL_PYRAMID5].dwFaceNode[2][1] = 2;
	ElType[EL_PYRAMID5].dwFaceNode[2][2] = 4;

	ElType[EL_PYRAMID5].dwFaceNode[3][0] = 2;
	ElType[EL_PYRAMID5].dwFaceNode[3][1] = 3;
	ElType[EL_PYRAMID5].dwFaceNode[3][2] = 4;

	ElType[EL_PYRAMID5].dwFaceNode[4][0] = 3;
	ElType[EL_PYRAMID5].dwFaceNode[4][1] = 0;
	ElType[EL_PYRAMID5].dwFaceNode[4][2] = 4;

	ElType[EL_PYRAMID5].dwFaceNodeFlag[0] = 0x0000000f;	// Each Face Node Flag
	ElType[EL_PYRAMID5].dwFaceNodeFlag[1] = 0x00000013;
	ElType[EL_PYRAMID5].dwFaceNodeFlag[2] = 0x00000016;
	ElType[EL_PYRAMID5].dwFaceNodeFlag[3] = 0x0000001c;
	ElType[EL_PYRAMID5].dwFaceNodeFlag[4] = 0x00000019;

	// Link 
	ElType[EL_PYRAMID5].dwLinkType[0] = EL_QUAD4;	// Each Link type
	ElType[EL_PYRAMID5].dwLinkType[1] = EL_TRI3;
	ElType[EL_PYRAMID5].dwLinkType[2] = EL_TRI3;
	ElType[EL_PYRAMID5].dwLinkType[3] = EL_TRI3;
	ElType[EL_PYRAMID5].dwLinkType[4] = EL_TRI3;

	ElType[EL_PYRAMID5].dwLinkNodeCnt[0] = 4;
	ElType[EL_PYRAMID5].dwLinkNodeCnt[1] = 3;
	ElType[EL_PYRAMID5].dwLinkNodeCnt[2] = 3;
	ElType[EL_PYRAMID5].dwLinkNodeCnt[3] = 3;
	ElType[EL_PYRAMID5].dwLinkNodeCnt[4] = 3;

	ElType[EL_PYRAMID5].dwLinkNode[0] = new DWORD[4];	// Each Link Node
	ElType[EL_PYRAMID5].dwLinkNode[1] = new DWORD[3];
	ElType[EL_PYRAMID5].dwLinkNode[2] = new DWORD[3];
	ElType[EL_PYRAMID5].dwLinkNode[3] = new DWORD[3];
	ElType[EL_PYRAMID5].dwLinkNode[4] = new DWORD[3];

	ElType[EL_PYRAMID5].dwLinkNode[0][0] = 0;
	ElType[EL_PYRAMID5].dwLinkNode[0][1] = 3;
	ElType[EL_PYRAMID5].dwLinkNode[0][2] = 2;
	ElType[EL_PYRAMID5].dwLinkNode[0][3] = 1;

	ElType[EL_PYRAMID5].dwLinkNode[1][0] = 0;
	ElType[EL_PYRAMID5].dwLinkNode[1][1] = 1;
	ElType[EL_PYRAMID5].dwLinkNode[1][2] = 4;

	ElType[EL_PYRAMID5].dwLinkNode[2][0] = 1;
	ElType[EL_PYRAMID5].dwLinkNode[2][1] = 2;
	ElType[EL_PYRAMID5].dwLinkNode[2][2] = 4;

	ElType[EL_PYRAMID5].dwLinkNode[3][0] = 2;
	ElType[EL_PYRAMID5].dwLinkNode[3][1] = 3;
	ElType[EL_PYRAMID5].dwLinkNode[3][2] = 4;

	ElType[EL_PYRAMID5].dwLinkNode[4][0] = 3;
	ElType[EL_PYRAMID5].dwLinkNode[4][1] = 0;
	ElType[EL_PYRAMID5].dwLinkNode[4][2] = 4;

	ElType[EL_PYRAMID5].dwLinkNodeFlag[0] = 0x0000000f;	// Each Link Node Flag
	ElType[EL_PYRAMID5].dwLinkNodeFlag[1] = 0x00000013;
	ElType[EL_PYRAMID5].dwLinkNodeFlag[2] = 0x00000016;
	ElType[EL_PYRAMID5].dwLinkNodeFlag[3] = 0x0000001c;
	ElType[EL_PYRAMID5].dwLinkNodeFlag[4] = 0x00000019;

	/////////////////////
	// Type 15 : EL_PYRAMID13

	// Basic Information
	ElType[EL_PYRAMID13].dwDim = 3;

	// Count
	ElType[EL_PYRAMID13].dwNodeCnt = 13;	
	ElType[EL_PYRAMID13].dwApexCnt = 5;	
	ElType[EL_PYRAMID13].dwMidCnt  = 8;	 
	ElType[EL_PYRAMID13].dwEdgeCnt = 8; 
	ElType[EL_PYRAMID13].dwFaceCnt = 5;
	ElType[EL_PYRAMID13].dwLinkCnt = 5;	

	// Edge
	ElType[EL_PYRAMID13].dwEdgeType[0] = EL_LINE3;
	ElType[EL_PYRAMID13].dwEdgeType[1] = EL_LINE3;
	ElType[EL_PYRAMID13].dwEdgeType[2] = EL_LINE3;
	ElType[EL_PYRAMID13].dwEdgeType[3] = EL_LINE3;
	ElType[EL_PYRAMID13].dwEdgeType[4] = EL_LINE3;
	ElType[EL_PYRAMID13].dwEdgeType[5] = EL_LINE3;
	ElType[EL_PYRAMID13].dwEdgeType[6] = EL_LINE3;
	ElType[EL_PYRAMID13].dwEdgeType[7] = EL_LINE3;

	ElType[EL_PYRAMID13].dwEdgeNode[0] = new DWORD[3];		// Each Edge Node
	ElType[EL_PYRAMID13].dwEdgeNode[1] = new DWORD[3];
	ElType[EL_PYRAMID13].dwEdgeNode[2] = new DWORD[3];
	ElType[EL_PYRAMID13].dwEdgeNode[3] = new DWORD[3];
	ElType[EL_PYRAMID13].dwEdgeNode[4] = new DWORD[3];
	ElType[EL_PYRAMID13].dwEdgeNode[5] = new DWORD[3];
	ElType[EL_PYRAMID13].dwEdgeNode[6] = new DWORD[3];
	ElType[EL_PYRAMID13].dwEdgeNode[7] = new DWORD[3];

	ElType[EL_PYRAMID13].dwEdgeNode[0][0] = 0;
	ElType[EL_PYRAMID13].dwEdgeNode[0][1] = 1;
	ElType[EL_PYRAMID13].dwEdgeNode[0][2] = 5;

	ElType[EL_PYRAMID13].dwEdgeNode[1][0] = 1;
	ElType[EL_PYRAMID13].dwEdgeNode[1][1] = 2;
	ElType[EL_PYRAMID13].dwEdgeNode[1][2] = 6;

	ElType[EL_PYRAMID13].dwEdgeNode[2][0] = 2;
	ElType[EL_PYRAMID13].dwEdgeNode[2][1] = 3;
	ElType[EL_PYRAMID13].dwEdgeNode[2][2] = 7;

	ElType[EL_PYRAMID13].dwEdgeNode[3][0] = 3;
	ElType[EL_PYRAMID13].dwEdgeNode[3][1] = 0;
	ElType[EL_PYRAMID13].dwEdgeNode[3][2] = 8;

	ElType[EL_PYRAMID13].dwEdgeNode[4][0] = 0;
	ElType[EL_PYRAMID13].dwEdgeNode[4][1] = 4;
	ElType[EL_PYRAMID13].dwEdgeNode[4][2] = 9;

	ElType[EL_PYRAMID13].dwEdgeNode[5][0] = 1;
	ElType[EL_PYRAMID13].dwEdgeNode[5][1] = 4;
	ElType[EL_PYRAMID13].dwEdgeNode[5][2] = 10;

	ElType[EL_PYRAMID13].dwEdgeNode[6][0] = 2;
	ElType[EL_PYRAMID13].dwEdgeNode[6][1] = 4;
	ElType[EL_PYRAMID13].dwEdgeNode[6][2] = 11;

	ElType[EL_PYRAMID13].dwEdgeNode[7][0] = 3;
	ElType[EL_PYRAMID13].dwEdgeNode[7][1] = 4;
	ElType[EL_PYRAMID13].dwEdgeNode[7][2] = 12;

	ElType[EL_PYRAMID13].dwEdgeNodeFlag[0] = 0x00000023; 	// Each Edge Node Flag
	ElType[EL_PYRAMID13].dwEdgeNodeFlag[1] = 0x00000046;
	ElType[EL_PYRAMID13].dwEdgeNodeFlag[2] = 0x0000008c;
	ElType[EL_PYRAMID13].dwEdgeNodeFlag[3] = 0x00000109;
	ElType[EL_PYRAMID13].dwEdgeNodeFlag[4] = 0x00000211;
	ElType[EL_PYRAMID13].dwEdgeNodeFlag[5] = 0x00000412;
	ElType[EL_PYRAMID13].dwEdgeNodeFlag[6] = 0x00000814;
	ElType[EL_PYRAMID13].dwEdgeNodeFlag[7] = 0x00001018;

	// Face 
	ElType[EL_PYRAMID13].dwFaceType[0] = EL_QUAD8;	// Each Face type
	ElType[EL_PYRAMID13].dwFaceType[1] = EL_TRI6;
	ElType[EL_PYRAMID13].dwFaceType[2] = EL_TRI6;
	ElType[EL_PYRAMID13].dwFaceType[3] = EL_TRI6;
	ElType[EL_PYRAMID13].dwFaceType[4] = EL_TRI6;

	ElType[EL_PYRAMID13].dwFaceNode[0] = new DWORD[8];	// Each Face Node
	ElType[EL_PYRAMID13].dwFaceNode[1] = new DWORD[6];
	ElType[EL_PYRAMID13].dwFaceNode[2] = new DWORD[6];
	ElType[EL_PYRAMID13].dwFaceNode[3] = new DWORD[6];
	ElType[EL_PYRAMID13].dwFaceNode[4] = new DWORD[6];

	ElType[EL_PYRAMID13].dwFaceNode[0][0] = 0;
	ElType[EL_PYRAMID13].dwFaceNode[0][1] = 3;
	ElType[EL_PYRAMID13].dwFaceNode[0][2] = 2;
	ElType[EL_PYRAMID13].dwFaceNode[0][3] = 1;
	ElType[EL_PYRAMID13].dwFaceNode[0][4] = 8;
	ElType[EL_PYRAMID13].dwFaceNode[0][5] = 7;
	ElType[EL_PYRAMID13].dwFaceNode[0][6] = 6;
	ElType[EL_PYRAMID13].dwFaceNode[0][7] = 5;

	ElType[EL_PYRAMID13].dwFaceNode[1][0] = 0;
	ElType[EL_PYRAMID13].dwFaceNode[1][1] = 1;
	ElType[EL_PYRAMID13].dwFaceNode[1][2] = 4;
	ElType[EL_PYRAMID13].dwFaceNode[1][3] = 5;
	ElType[EL_PYRAMID13].dwFaceNode[1][4] = 10;
	ElType[EL_PYRAMID13].dwFaceNode[1][5] = 9;

	ElType[EL_PYRAMID13].dwFaceNode[2][0] = 1;
	ElType[EL_PYRAMID13].dwFaceNode[2][1] = 2;
	ElType[EL_PYRAMID13].dwFaceNode[2][2] = 4;
	ElType[EL_PYRAMID13].dwFaceNode[2][3] = 6;
	ElType[EL_PYRAMID13].dwFaceNode[2][4] = 11;
	ElType[EL_PYRAMID13].dwFaceNode[2][5] = 10;

	ElType[EL_PYRAMID13].dwFaceNode[3][0] = 2;
	ElType[EL_PYRAMID13].dwFaceNode[3][1] = 3;
	ElType[EL_PYRAMID13].dwFaceNode[3][2] = 4;
	ElType[EL_PYRAMID13].dwFaceNode[3][3] = 7;
	ElType[EL_PYRAMID13].dwFaceNode[3][4] = 12;
	ElType[EL_PYRAMID13].dwFaceNode[3][5] = 11;

	ElType[EL_PYRAMID13].dwFaceNode[4][0] = 3;
	ElType[EL_PYRAMID13].dwFaceNode[4][1] = 0;
	ElType[EL_PYRAMID13].dwFaceNode[4][2] = 4;
	ElType[EL_PYRAMID13].dwFaceNode[4][3] = 8;
	ElType[EL_PYRAMID13].dwFaceNode[4][4] = 9;
	ElType[EL_PYRAMID13].dwFaceNode[4][5] = 12;

	ElType[EL_PYRAMID13].dwFaceNodeFlag[0] = 0x000001ef;	// Each Face Node Flag
	ElType[EL_PYRAMID13].dwFaceNodeFlag[1] = 0x00000633;
	ElType[EL_PYRAMID13].dwFaceNodeFlag[2] = 0x00000c56;
	ElType[EL_PYRAMID13].dwFaceNodeFlag[3] = 0x0000189c;
	ElType[EL_PYRAMID13].dwFaceNodeFlag[4] = 0x00001319;

	// Link 
	ElType[EL_PYRAMID13].dwLinkType[0] = EL_QUAD4;	// Each Link type
	ElType[EL_PYRAMID13].dwLinkType[1] = EL_TRI3;
	ElType[EL_PYRAMID13].dwLinkType[2] = EL_TRI3;
	ElType[EL_PYRAMID13].dwLinkType[3] = EL_TRI3;
	ElType[EL_PYRAMID13].dwLinkType[4] = EL_TRI3;

	ElType[EL_PYRAMID13].dwLinkNodeCnt[0] = 4;	// Each Link type
	ElType[EL_PYRAMID13].dwLinkNodeCnt[1] = 3;
	ElType[EL_PYRAMID13].dwLinkNodeCnt[2] = 3;
	ElType[EL_PYRAMID13].dwLinkNodeCnt[3] = 3;
	ElType[EL_PYRAMID13].dwLinkNodeCnt[4] = 3;

	ElType[EL_PYRAMID13].dwLinkNode[0] = new DWORD[4];	// Each Link Node
	ElType[EL_PYRAMID13].dwLinkNode[1] = new DWORD[3];
	ElType[EL_PYRAMID13].dwLinkNode[2] = new DWORD[3];
	ElType[EL_PYRAMID13].dwLinkNode[3] = new DWORD[3];
	ElType[EL_PYRAMID13].dwLinkNode[4] = new DWORD[3];

	ElType[EL_PYRAMID13].dwLinkNode[0][0] = 0;
	ElType[EL_PYRAMID13].dwLinkNode[0][1] = 3;
	ElType[EL_PYRAMID13].dwLinkNode[0][2] = 2;
	ElType[EL_PYRAMID13].dwLinkNode[0][3] = 1;

	ElType[EL_PYRAMID13].dwLinkNode[1][0] = 0;
	ElType[EL_PYRAMID13].dwLinkNode[1][1] = 1;
	ElType[EL_PYRAMID13].dwLinkNode[1][2] = 4;

	ElType[EL_PYRAMID13].dwLinkNode[2][0] = 1;
	ElType[EL_PYRAMID13].dwLinkNode[2][1] = 2;
	ElType[EL_PYRAMID13].dwLinkNode[2][2] = 4;

	ElType[EL_PYRAMID13].dwLinkNode[3][0] = 2;
	ElType[EL_PYRAMID13].dwLinkNode[3][1] = 3;
	ElType[EL_PYRAMID13].dwLinkNode[3][2] = 4;

	ElType[EL_PYRAMID13].dwLinkNode[4][0] = 3;
	ElType[EL_PYRAMID13].dwLinkNode[4][1] = 0;
	ElType[EL_PYRAMID13].dwLinkNode[4][2] = 4;

	ElType[EL_PYRAMID13].dwLinkNodeFlag[0] = 0x0000000f;	// Each Link Node Flag
	ElType[EL_PYRAMID13].dwLinkNodeFlag[1] = 0x00000013;
	ElType[EL_PYRAMID13].dwLinkNodeFlag[2] = 0x00000016;
	ElType[EL_PYRAMID13].dwLinkNodeFlag[3] = 0x0000001c;
	ElType[EL_PYRAMID13].dwLinkNodeFlag[4] = 0x00000019;
}

