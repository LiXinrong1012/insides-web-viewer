//************************************************************************** 
//* HsfExp.h	- Ascii File Exporter
//* 
//* By Christer Janson
//* Kinetix Development
//*
//* January 20, 1997 CCJ Initial coding
//*
//* Class definition 
//*
//* Copyright (c) 1997, All Rights Reserved. 
//***************************************************************************

#ifndef __HsfExp__H
#define __HsfExp__H

#define BUFFERSIZE 4096

#include "Max.h"
#include "resource.h"
#include "istdplug.h"
#include "stdmat.h"
#include "decomp.h"
#include "shape.h"
#include "interpik.h"
#include "bmmlib.h"
#include "asciitok.h"
#include "vhash.h"

extern ClassDesc* GetHsfExpDesc();
extern TCHAR *GetString(int id);
extern HINSTANCE hInstance;


class HUtilityXMLGenerator;
class HUtilityXMLTag;

#define LEFT_HANDED 0
#define RIGHT_HANDED 1
#define DEFAULT_HANDED 2


#define VERSION			200			// Version number * 100
//#define FLOAT_OUTPUT	_T("%4.4f")	// Float precision for output
#define CFGFILENAME		_T("HSFEXP.CFG")	// Configuration file

//#define ASCIIOUTPUT



#ifdef ASCIIOUTPUT

#define FPRINTF fprintf

#else
#define FPRINTF fprintf2


static int  fprintf2(FILE *, const char *, ...)
{
 	;
	return 0;
}

#endif

class MtlKeeper {
public:
	BOOL	AddMtl(Mtl* mtl);
	int		GetMtlID(Mtl* mtl);
	int		Count();
	Mtl*	GetMtl(int id);

	Tab<Mtl*> mtlTab;
};

class BStreamFileToolkit;
// This is the main class for the exporter.

class HsfExp : public SceneExport {
public:
	HsfExp();
	~HsfExp();

	// SceneExport methods
	int    ExtCount();     // Number of extensions supported 
	const TCHAR * Ext(int n);     // Extension #n (i.e. "ASC")
	const TCHAR * LongDesc();     // Long ASCII description (i.e. "Ascii Export") 
	const TCHAR * ShortDesc();    // Short ASCII description (i.e. "Ascii")
	const TCHAR * AuthorName();    // ASCII Author name
	const TCHAR * CopyrightMessage();   // ASCII Copyright message 
	const TCHAR * OtherMessage1();   // Other message #1
	const TCHAR * OtherMessage2();   // Other message #2
	unsigned int Version();     // Version number * 100 (i.e. v3.01 = 301) 
	void	ShowAbout(HWND hWnd);  // Show DLL's "About..." box
	int		DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0); // Export	file
	BOOL	SupportsOptions(int ext, DWORD options);
	void LoadUrl (char *url);
	// Other methods
	int subsegment;
	// Node enumeration
	BOOL	nodeEnum(INode* node, int indentLevel);
	BOOL	nodeEnumCamera(INode* node, int indentLevel);

	void	PreProcess(INode* node, int& nodeCount);

	// High level export
	void	ExportGlobalInfo();
	void	ExportMaterialList();
	void	ExportGeomObject(INode* node, int indentLevel); 
	void	ExportLightObject(INode* node, int indentLevel); 
	void	ExportCameraObject(INode* node, int indentLevel); 
	void	ExportShapeObject(INode* node, int indentLevel); 
	void	ExportHelperObject(INode* node, int indentLevel);

	// Mid level export
	void	ExportMesh(INode* node, TimeValue t, int indentLevel); 
	void	ExportAnimKeys(INode* node, int indentLevel, bool isTarget = false);
	void	ExportMaterial(INode* node, int indentLevel); 
	void	ExportAnimMesh(INode* node, int indentLevel); 
	void	ExportIKJoints(INode* node, int indentLevel);
	void	ExportNodeTM(INode* node, int indentLevel);
	void	ExportNodeHeader(INode* node, TCHAR* type, int indentLevel);
	void	ExportCameraSettings(CameraState* cs, CameraObject* cam, TimeValue t, int indentLevel);
	void	ExportLightSettings(LightState* ls, GenLight* light, TimeValue t, int indentLevel);

	// Low level export
	void	DumpPoly(PolyLine* line, Matrix3 tm, int indentLevel);
	void	DumpMatrix3(Matrix3* m, int indentLevel);
	void	DumpMaterial(Mtl* mtl, int mtlID, int subNo, int indentLevel);
	void	DumpTexture(Texmap* tex, Class_ID cid, int subNo, float amt, int	indentLevel);
	void	DumpJointParams(JointParams* joint, int indentLevel);
	void	DumpUVGen(StdUVGen* uvGen, int indentLevel); 
	void	DumpPosSample(INode* node, int indentLevel); 
	void	DumpRotSample(INode* node, int indentLevel); 
	void	DumpScaleSample(INode* node, int indentLevel); 
	void	DumpPoint3Keys(Control* cont, int indentLevel);
	void	DumpFloatKeys(Control* cont, int indentLevel);
	void	DumpPosKeys(Control* cont, int indentLevel);
	void	DumpRotKeys(Control* cont, int indentLevel);
	void	DumpScaleKeys(Control* cont, int indentLevel);

	// Misc methods
	TCHAR*	GetMapID(Class_ID cid, int subNo);
	Point3	GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv, bool &normalspecified);
	BOOL	CheckForAndExportFaceMap(Mtl* mtl, Mesh* mesh, int indentLevel); 
	void	make_face_uv(Face *f, Point3 *tv);
	BOOL	TMNegParity(Matrix3 &m);
	TSTR	GetIndent(int indentLevel);
	TCHAR*	FixupName(TCHAR* name);
	void	CommaScan(TCHAR* buf);
	BOOL	CheckForAnimation(INode* node, BOOL& pos, BOOL& rot, BOOL& scale);
	TriObject*	GetTriObjectFromNode(INode *node, TimeValue t, int &deleteIt);
	BOOL	IsKnownController(Control* cont);

	// A collection of overloaded value to string converters.
	TSTR	Format(int value);
	TSTR	Format(float value);
	TSTR	Format(Color value);
	TSTR	Format(Point3 value); 
	TSTR	Format(AngAxis value); 
	TSTR	Format(Quat value);
	TSTR	Format(ScaleValue value);

	// Configuration methods
	TSTR	GetCfgFilename();
	BOOL	ReadConfig();
	void	WriteConfig();
	
	// Interface to member variables
	inline BOOL	GetIncludeMesh()			{ return bIncludeMesh; }
	inline BOOL	GetIncludeAnim()			{ return bIncludeAnim; }
	inline BOOL	GetIncludeMtl()				{ return bIncludeMtl; }
	inline BOOL	GetIncludeMeshAnim()		{ return bIncludeMeshAnim; }
	inline BOOL	GetIncludeCamLightAnim()	{ return bIncludeCamLightAnim; }
	inline BOOL	GetIncludeIKJoints()		{ return bIncludeIKJoints; }
	inline BOOL	GetIncludeNormals()			{ return bIncludeNormals; }
	inline BOOL	GetIncludeTextureCoords()	{ return bIncludeTextureCoords; }
	inline BOOL	GetIncludeVertexColors()	{ return bIncludeVertexColors; }
	inline BOOL	GetIncludeObjGeom()			{ return bIncludeObjGeom; }
	inline BOOL	GetIncludeObjShape()		{ return bIncludeObjShape; }
	inline BOOL	GetIncludeObjCamera()		{ return bIncludeObjCamera; }
	inline BOOL	GetIncludeObjLight()		{ return bIncludeObjLight; }
	inline BOOL	GetIncludeObjTextures()		{ return bIncludeObjTextures; }	inline BOOL	GetFlipAxis()				{ return bFlipAxis; }
	inline BOOL	GetIncludeObjHelper()		{ return bIncludeObjHelper; }
	inline BOOL	GetAlwaysSample()			{ return bAlwaysSample; }
	inline int	GetMeshFrameStep()			{ return nMeshFrameStep; }
	inline int	GetKeyFrameStep()			{ return nKeyFrameStep; }
	inline int	GetPrecision()				{ return nPrecision; }
	inline TimeValue GetStaticFrame()		{ return nStaticFrame; }
	inline Interface*	GetInterface()		{ return ip; }



	inline void	SetIncludeMesh(BOOL val)			{ bIncludeMesh = val; }
	inline void	SetIncludeAnim(BOOL val)			{ bIncludeAnim = val; }
	inline void	SetIncludeMtl(BOOL val)				{ bIncludeMtl = val; }
	inline void	SetIncludeMeshAnim(BOOL val)		{ bIncludeMeshAnim = val; }
	inline void	SetIncludeCamLightAnim(BOOL val)	{ bIncludeCamLightAnim = val; }
	inline void	SetIncludeIKJoints(BOOL val)		{ bIncludeIKJoints = val; }
	inline void	SetIncludeNormals(BOOL val)			{ bIncludeNormals = val; }
	inline void	SetIncludeTextureCoords(BOOL val)	{ bIncludeTextureCoords = val; }
	inline void	SetIncludeVertexColors(BOOL val)	{ bIncludeVertexColors = val; }
	inline void	SetIncludeObjGeom(BOOL val)			{ bIncludeObjGeom = val; }
	inline void	SetIncludeObjShape(BOOL val)		{ bIncludeObjShape = val; }
	inline void	SetIncludeObjCamera(BOOL val)		{ bIncludeObjCamera = val; }
	inline void	SetIncludeObjLight(BOOL val)		{ bIncludeObjLight = val; }
	inline void	SetIncludeObjTextures(BOOL val)		{ bIncludeObjTextures = val; }	inline void	SetFlipAxis(BOOL val)				{ bFlipAxis = val; }

	inline void	SetIncludeObjHelper(BOOL val)		{ bIncludeObjHelper = val; }
	inline void	SetAlwaysSample(BOOL val)			{ bAlwaysSample = val; }
	inline void SetMeshFrameStep(int val)			{ nMeshFrameStep = val; }
	inline void SetKeyFrameStep(int val)			{ nKeyFrameStep = val; }
	inline void SetPrecision(int val)				{ nPrecision = val; }
	inline void SetStaticFrame(TimeValue val)		{ nStaticFrame = val; }


	inline int	GetVertexCompressionBits()			{ return m_VertexCompressionBits; }
	inline void	SetVertexCompressionBits(int val)			{ m_VertexCompressionBits = val; }
	inline int	GetNormalCompressionBits()			{ return m_NormalCompressionBits; }
	inline void	SetNormalCompressionBits(int val)			{ m_NormalCompressionBits = val; }
	inline int	GetImageCompressionValue()			{ return m_ImageCompressionValue; }
	inline void	SetImageCompressionValue(int val)			{ m_ImageCompressionValue = val; }
	inline int	GetHandedness()						{ return m_handedness; }
	inline void	SetHandedness(int val)				{ m_handedness = val; }

	inline BOOL	GetConnectivityCompression()			{ return bConnectivityCompression; }
	inline void	SetConnectivityCompression(BOOL val)			{ bConnectivityCompression = val; }
	inline BOOL	GetVertexCompression()			{ return bVertexCompression; }
	inline void	SetVertexCompression(BOOL val)			{ bVertexCompression = val; }
	inline BOOL	GetNormalCompression()			{ return bNormalCompression; }
	inline void	SetNormalCompression(BOOL val)			{ bNormalCompression = val; }
	inline BOOL	GetImageCompression()			{ return bImageCompression; }
	inline void	SetImageCompression(BOOL val)			{ bImageCompression = val; }

	inline BOOL	GetSpecForEnv()			{ return bSpecForEnv; }
	inline void	SetSpecForEnv(BOOL val)			{ bSpecForEnv = val; }

	inline BOOL	GetDisableEnv()					{ return bDisableEnv; }
	inline void	SetDisableEnv(BOOL val)			{ bDisableEnv = val; }

	inline BOOL	GetCameraAsAnimation()					{ return bCameraAsAnimation; }
	inline void	SetCameraAsAnimation(BOOL val)			{ bCameraAsAnimation = val; }
	inline BOOL	GetInactiveByDefault()					{ return bInactiveByDefault; }
	inline void	SetInactiveByDefault(BOOL val)			{ bInactiveByDefault = val; }

private:
	BOOL	bIncludeMesh;
	BOOL	bIncludeAnim;
	BOOL	bIncludeMtl;
	BOOL	bIncludeMeshAnim;
	BOOL	bIncludeCamLightAnim;
	BOOL	bIncludeIKJoints;
	BOOL	bIncludeNormals;
	BOOL	bIncludeTextureCoords;
	BOOL	bIncludeObjGeom;
	BOOL	bIncludeObjShape;
	BOOL	bIncludeObjCamera;
	BOOL	bIncludeObjLight;
	BOOL	bIncludeObjTextures;	BOOL	bFlipAxis;
	BOOL	bIncludeObjHelper;
	BOOL	bAlwaysSample;
	BOOL	bIncludeVertexColors;
	int		nMeshFrameStep;
	int		nKeyFrameStep;
	int		nPrecision;
 	TimeValue	nStaticFrame;

	Interface*	ip;
	FILE*		pStream;
	int			nTotalNodeCount;
	int			nCurNode;
	TCHAR		szFmtStr[16];

	MtlKeeper	mtlList;

private:
	void InitializeHSFWrite(HUtilityXMLTag *bhvtag, const TCHAR *name);
	void WriteOpenSegment(TCHAR *name);
	void WriteCloseSegment();	void WriteVisibilityOff();
	void EndHSFWrite(HUtilityXMLTag *bhvtag);
	void WriteShell(INode *node, TimeValue t);
	void WriteColor(Mtl *mtl, const char *texnamedef, const char *texnameref, const char *texnamebump);	void WriteSimpleColor(Color d);
	void DumpHSFMaterial(Mtl* mtl, int mtlID, int subNo);
	void ReferenceMaterial(INode *node);
	void DumpHsfTexture(int mtlID,int subMat, Texmap* tex, Class_ID cid, int subNo,float amt, TCHAR *texturetype, bool &dumped);
	void WriteTextureImage(Texmap *tex, Class_ID cid, int subNo, const char *name, int width, int height, unsigned char *buffer);
	BOOL CheckForFaceMap(Mtl* mtl, Mesh* mesh);
	void ReferenceSubMaterial(int mat, int submat);
	void WriteTexture(Texmap *tex, Class_ID cid, int subNo,const char *name, StdUVGen *uvGen, int imagenum);
	void WriteUserOptions(const char *text);
 	void OptimizeAndWrite(Mesh *mesh, int origpnum, int pnum, int facenum, float *points, int *pmap, int *faces,  float *normals, bool *normalspecified,float *texcoords);
	void ExportHsfMatrix(INode *node);
	void WriteHsfCamera(INode *node, INode *target, CameraState *cs, CameraObject *cam, int t);
	bool MaterialHasTexture(Mtl *mtl);

	void MakeFullPath(INode *startnode, char *text);
	void OpenAnimationInterpolator(HUtilityXMLTag *animtag, INode *node, bool isTarget, char *type);
	void CloseAnimationInterpolator(HUtilityXMLTag *animtag);
	void WriteTimeline(INode* node);
	void WriteTimelineRot(INode* node);

	void WritePosInterpolator(INode* node);
	void WriteRotInterpolator(INode* node);
	bool IsCamera(INode *node);
	void DumpHsfPoly(PolyLine* line, Matrix3 tm);
	float GetCameraFov(INode *node);
	void WriteTimelineFov(INode* node);
	void WriteFovInterpolator(INode* node);
	void ExportHsfLight(INode* node);
	void GetLocalMatrix(INode *node, Matrix3 &pivot);
	void CreateRelativePath(char *text, char *text2);




 

	BOOL bConnectivityCompression;
	BOOL bVertexCompression;
	BOOL bNormalCompression;
	BOOL bImageCompression;
	BOOL bSpecForEnv;
	BOOL bDisableEnv;
	BOOL bCameraAsAnimation;
	int mcounter;
	int m_imagecounter;
	BStreamFileToolkit *m_pStreamFileToolkit;
	char m_Buffer[4097];
	FILE *m_Stream;
	Point3 m_min, m_max;

	vhash_t *m_imagehash;
	HUtilityXMLGenerator *m_pXML;
	int m_animcounter;
	int m_VertexCompressionBits;
	int m_NormalCompressionBits;
	int m_ImageCompressionValue;
	int m_handedness;
	BOOL m_bFirstCamera;
	BOOL bInactiveByDefault;
	BOOL bSaveImages;
	BOOL bSaveColors;

};

#endif // __HsfExp__H

