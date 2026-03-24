#ifndef _VDS_STRUCTURES_H_
#define _VDS_STRUCTURES_H_
/*
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

enum MCONTROL_TYPE
{
	MCONTROL_TYPE_GLOBAL_SIZEPARAMS,
	MCONTROL_TYPE_LOCAL_SIZEPARAMS
};

enum MPATTERN_TYPE
{
	MPATTERN_TYPE_UNSTRUCTURED,
	MPATTERN_TYPE_STRUCTURED_ISO,
	MPATTERN_TYPE_STRUCTURED_EQU
};

enum VDS_ELEMENT_QUALITY
{
	VDS_ELEMENT_QUALITY_STRETCH,
	VDS_ELEMENT_QUALITY_ASPECTRATIO,
	VDS_ELEMENT_QUALITY_EDGELENGTH,
	VDS_ELEMENT_QUALITY_AREA,
	VDS_ELEMENT_QUALITY_WARP,
	VDS_ELEMENT_QUALITY_SKEW,
	VDS_ELEMENT_QUALITY_VDSSTRETCH,
	VDS_ELEMENT_QUALITY_NODEVALENCE
};

enum VDS_MESHER_PERFORMANCE_MODE
{
	VDS_MESHER_PERFORMANCE_MODE_FASTEST,
	VDS_MESHER_PERFORMANCE_MODE_GOODQUALITY,
	VDS_MESHER_PERFORMANCE_MODE_BESTQUALITY
};



struct MCONTROL_PARAM
{
	int entityId;
	int modelId;
	int entityType;	
	MCONTROL_TYPE controlType; 

	bool bEnableSizeParams;
	struct
	{
		double avgSize;
		double maxSize;
		double minSize;

		double dGeomQualityRatio;
		double dGeomCountRatio;
		
		bool bEnableTrimAngle;
		double trimAngle;
		double dGradingFactor;

		double minQuality;
		double maxEdgeDistRatio;
		bool bOutputQuadMesh;
	} sizeParams;

	bool bEnableKeepEntity;
	struct
	{
		bool bShape;
		bool bFeatures;
	} keepEntity;

	bool bEnableMeshPattern;
	struct
	{
		MPATTERN_TYPE nType;
	} meshPattern;

	bool bEnableMeshCount;
	struct
	{
		long nNodes;
	} meshCount;

	struct
	{
		VDS_MESHER_PERFORMANCE_MODE	 mode;
	} performance;

	struct
	{
		bool bEnableMergeEdges;
		bool bEnableMergeFaces;
		double dMeshPatternMinElemAngle;
	} autoSettings;

	struct
	{
		double ptXYZ[3];
	} fixedPoint;


	MCONTROL_PARAM()
	{
		initDefaults();
	}

	void initDefaults()
	{
		entityId =0;
		modelId =0;
		entityType = 0;	
		controlType = MCONTROL_TYPE_LOCAL_SIZEPARAMS; 

		sizeParams.avgSize = 5;
		sizeParams.maxSize = 10;
		sizeParams.minSize = .5;

		sizeParams.dGeomQualityRatio = .7;
		sizeParams.dGeomCountRatio = .5;
		
		sizeParams.trimAngle = 45;

		sizeParams.minQuality = .1;
		sizeParams.maxEdgeDistRatio = .1;
		sizeParams.bOutputQuadMesh = false;

		sizeParams.bEnableTrimAngle = false;
		sizeParams.dGradingFactor = 1.25;

		keepEntity.bShape = false;
		keepEntity.bFeatures = false;

		meshPattern.nType = MPATTERN_TYPE_UNSTRUCTURED;

		bEnableMeshCount = false;
		bEnableMeshPattern = false;
		bEnableKeepEntity = false;
		bEnableSizeParams = false;

		fixedPoint.ptXYZ[0] = fixedPoint.ptXYZ[1] = fixedPoint.ptXYZ[2] = 0;

		performance.mode = VDS_MESHER_PERFORMANCE_MODE_GOODQUALITY;
		autoSettings.bEnableMergeEdges = false;
		autoSettings.bEnableMergeFaces = false;
		autoSettings.dMeshPatternMinElemAngle = 30;
	}


};

struct MQUADNODE_DATA
{
	double nAngle;
	bool bInFrontEdge;
};



struct VDS_PROGRESS_SHMEM
{
	long progressPos;//0 to 100
	char progressMessage[256];
};

enum UEI_TYPE
{
	UEI_TYPE_MODEL=1,
	UEI_TYPE_BODY,
	UEI_TYPE_FACE,
	UEI_TYPE_EDGE,
	UEI_TYPE_VERTEX,
	UEI_TYPE_ELEM,
	UEI_TYPE_NODE,
	UEI_TYPE_FACEPOINT,
	UEI_TYPE_EDGEPOINT
};

// Unique entity identifier info
struct UEI_INFO
{
	UEI_TYPE nUeiType;
	long nParId;
	long nEntityId;
	long nSubId;
	void *pAddData;

	UEI_INFO::UEI_INFO()
	{
		nParId = 0;
		nEntityId = 0;
		nSubId = 0;
		pAddData = 0;

	}
};
*/
#endif