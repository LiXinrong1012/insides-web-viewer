/*
* Copyright (c) 2009 by Tech Soft 3D, LLC.
* The information contained herein is confidential and proprietary to
* Tech Soft 3D, LLC., and considered a trade secret as defined under
* civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
* and criminal remedies in the event of unauthorized use or misappropriation
* of its trade secrets.  Use of this information by anyone other than
* authorized employees of Tech Soft 3D, LLC. is granted only under a
* written non-disclosure agreement, expressly prescribing the scope and
* manner of such use.
*
* $Id: H3DXHelper.h,v 1.4 2011-01-14 19:06:01 guido Exp $
*/

#ifndef _H3DXHELPER_H
#define _H3DXHELPER_H


#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include <tchar.h>
#include <wchar.h>
#include <map>

#include "hc.h"
#include "HTools.h"
#include "HUtilityPMI.h"


class HInputHandlerOptions;
class HOutputHandlerOptions;
class HIOConnector3DX;
class HIOUtility3DX;
class BREP_Edge_Matcher;
class BREP_Topology;
class HIOConnector;
class HBaseView;
typedef int  BOOL;



class BREP_Edge_Matcher
{
public:

	BREP_Edge_Matcher();
	~BREP_Edge_Matcher();
	struct vlist_s *		m_edgelist;
	struct vlist_s *		m_edgeidlist;
	struct vhash_s *		m_edgehash;
	HC_KEY * m_edgekeys;

	void AddModellerEdge(void *edgeid);
	void Restart();
	void StartEdgeIteration();
	bool NextEdge(HC_KEY edgekey, HC_KEY &origkey, void **origid);
 	long m_edgenum;
 };





class H3DXExporter
{
public:
	bool Export(wchar_t const * file_name, HC_KEY model_key, HOutputHandlerOptions * options);

	A3DAsmModelFile * createModelFile();
	A3DAsmProductOccurrence * createOccurrence();
	A3DAsmPartDefinition* createPart(HC_KEY segmentkey, bool hasColor, bool lineVisibility, bool faceVisibility, bool isInclude);
	A3DRiRepresentationItem * createRI(HC_KEY key, bool hasColor, bool lineVisibility, bool faceVisibility, bool isInclude);
	A3DTess3D* createShellTesselation(HC_KEY shellkey, bool &needsColorMap);
	A3DTess3D* createLineTesselation(HC_KEY polylinekey);
	void AddTexture(HC_KEY imagekey);
	void gatherTextures(HC_KEY segmentkey);
	A3DAsmProductOccurrence * createInclude(HC_KEY key, bool hasColor);
	bool IsEnvironmentTexture(char *texturename);
	bool	FindTexture(char *texturename, char *definition);
	void FindCorrespondingColormap(HC_KEY segmentkey, char *textout);
 	
	A3DAsmProductOccurrence * createOccurrenceRecursive(HC_KEY segmentkey, bool hasColor, bool lineVisibility, bool faceVisibility, bool isInclude);


	void SetColor(A3DRootBaseWithGraphics* pBase, HC_KEY segmentkey, bool needsColorMap, bool hasColor,  bool isVisible,bool faceColor = true);

	A3DMkpAnnotationEntity *createPMI(HC_KEY segmentkey);
	A3DTessMarkup * createTesselation(HC_KEY segmentkey);
	A3DMkpView * createView(HC_KEY segmentkey);


	bool m_VertexColorFound;
	HC_KEY	m_modelKey;
	HBaseView *m_pView;
	struct vlist_s *m_RI_list;
	struct vhash_s *m_texturehash;
	int m_ColorMapCount;
	struct vhash_s *m_instancehash;
};

class HUtilityXMLTag;

#include "vhash.h"
#include "varray.h"

#include <vector>

typedef VHash<A3DAsmProductOccurrence *, HC_KEY> POccurrenceKeyHash;
typedef VArray<char const *> StringArray;

typedef std::vector<PMI::Polyline> PmiPolylineArray;
typedef std::vector<PMI::String> PmiStringArray;
typedef std::vector<PMI::TextAttributes> PmiTextAttributesArray;
typedef std::vector<PMI::Entity> PmiEntityArray;

class H3DXImporter
{
public:
	H3DXImporter(HIOUtility3DX* p3DXInputHandler);
	virtual ~H3DXImporter();
	virtual bool Import(const wchar_t * FileName, HC_KEY modelKey, HInputHandlerOptions * pInputOptions = 0);

protected:
	bool WriteConfigFile ( wchar_t const * filename, int config_selection = 0 );


	A3DInt32 CreateAndPushCascadedAttributesFace(const A3DRiRepresentationItem* pRepItem,
											const A3DTessBase* pTessBase,
											const A3DTessFaceData* psTessFaceData,
											A3DUns32 uiFaceIndex,
											const A3DMiscCascadedAttributes* pFatherAttr,
											A3DMiscCascadedAttributes** ppAttr,
											A3DMiscCascadedAttributesData* psAttrData);

	A3DInt32 CreateAndPushCascadedAttributes(const A3DRootBaseWithGraphics* pBase,
										const A3DMiscCascadedAttributes* pFatherAttr,
										A3DMiscCascadedAttributes** ppAttr,
										A3DMiscCascadedAttributesData* psAttrData);

	void parseRiSet(A3DRiSet* p, A3DMiscCascadedAttributes* pFatherAttr, double modelscale);

	void parseAttributes(const A3DEntity* pEntity);

 
	void BuildShell(A3DTess3D* p, A3DRiRepresentationItem* pRepItem, A3DMiscCascadedAttributes* pFatherAttr, A3DTessBaseData *tessbasedata, double modelscale);
	void BuildWires(A3DTess3D* p, A3DRiRepresentationItem* pRepItem, A3DMiscCascadedAttributes* pFatherAttr, A3DTessBaseData *tessbasedata);
	void BuildMarkup(A3DTess3D* p, A3DRiRepresentationItem* pRepItem, A3DMiscCascadedAttributes* pFatherAttr, A3DTessBaseData *tessbasedata);

	void getMarkupTesselation(const A3DTessBaseData *psTessBaseData, const A3DTessMarkupData *psTessMarkupData,
			PmiPolylineArray & out_polylines, PmiStringArray & out_strings, PmiTextAttributesArray & out_text_attributes);


	void parseTess(A3DTessBase* p, A3DRiRepresentationItem* pRepItem, 
				  A3DMiscCascadedAttributes* pFatherAttr, double modelscale);

	void parseBrepData(A3DTopoBrepData* p);
	void parseConnex(A3DTopoConnex* p,A3DTopoBrepData* p2);
	void parseShell(A3DTopoShell* p, bool invert = false);
	void parseFace(A3DTopoFace* p);
	void parseLoop(A3DTopoLoop* p);
	void parseCoEdge(A3DTopoCoEdge* p);
	void parseEdge(A3DTopoEdge* p);
	void parseVertex(A3DTopoVertex* p);
	void parseMultipleVertex(A3DTopoMultipleVertex* p);
	void parseUniqueVertex(A3DTopoUniqueVertex* p);
	void parseBody(A3DTopoBody* p);
	void parseContext(A3DTopoContext* p);

	void SetMaterial(A3DMiscCascadedAttributesData *attr);

	void parseRiBrepModel(A3DRiBrepModel* p);
	void parseRiCSys(A3DRiCoordinateSystem* p);
	void parseRiCurve(A3DRiCurve* p);
	void parseRiPointSet(A3DRiPointSet* p);

	void parseRI(A3DRiRepresentationItem* p, A3DMiscCascadedAttributes* pFatherAttr, double modelscale);
	void parsePart(A3DAsmPartDefinition* p, A3DMiscCascadedAttributes* pFatherAttr, double modelscale);

	A3DInt32 productOccurrenceGetExternalData(A3DAsmProductOccurrenceData const * psPOccData,
											 A3DAsmProductOccurrence *& pExternalData);
	A3DInt32 productOccurrenceGetLocation(A3DAsmProductOccurrenceData const * psPOccData,
										 A3DMiscCartesianTransformation *& pLocation);
	bool prototypeGetPartRecursive(A3DAsmProductOccurrence * prototype, 
								   A3DMiscCascadedAttributes * pAttr, 
								   double modelscale,
								   bool use_external_data);
	void productOccurrenceGetPart(A3DAsmProductOccurrenceData const * psPOccData, 
								  A3DMiscCascadedAttributes * pAttr, 
								  double modelscale);
	bool prototypeGetOccurrencesRecursive(A3DAsmProductOccurrence * prototype,
										  A3DMiscCascadedAttributes * pAttr,
										  double modelscale);
	void productOccurrenceGetChildren(A3DAsmProductOccurrenceData const * psPOccData,
									  A3DMiscCascadedAttributes * pAttr,
									  double modelscale);

	void parsePOccurrence(A3DAsmProductOccurrence * p, 
						  A3DMiscCascadedAttributes * pFatherAttr, 
						  double modelscale);						

	void traverseAnnotationReference(const A3DMkpAnnotationReference *pAnnot);
	void SetMatrix(A3DMiscCartesianTransformation *trans);
	void SetMatrix2(A3DMiscCartesianTransformationData trans);
	void traverseAnnotation(const A3DMkpAnnotationEntity *pAnnot);
	void traverseAnnotationItem(const A3DMkpAnnotationItem *pAnnot);
	void traverseAnnotationSet(const A3DMkpAnnotationSet *pAnnot);
	void getLeaderLines(const A3DMkpLeader *pMarkup, PmiPolylineArray & out_leader_lines);
	void traverseMarkup(const A3DMkpMarkup *pMarkup);
	void PopulateTextures();
	void AddVertexColor(HPoint *face, A3DUns8 *vertexarray, int &vcpos, bool invert, bool decrement);

	void traverseView(const A3DMkpView *pView);
	void treatReference(A3DEntity* pEntity, const A3DMkpMarkup *pMarkup);
	void treatReferenceOnTopology(A3DEntity* pEntity,const A3DMkpMarkup *pMarkup);
	int GetDLLVersion() { return m_iMajorVersion * 100 + m_iMinorVersion; }

	HIOConnector *			m_pConnector;
	HIOConnector *			m_pPMIConnector;
	HIOUtility3DX *			m_p3DXInputHandler;
	HIOConnector3DX	*		m_pConnectivityInfo;
	HC_KEY					m_modelKey;
	HC_KEY					m_markup_segment;
	wchar_t *				m_fileName;
	POccurrenceKeyHash		m_part_key_hash;
	POccurrenceKeyHash		m_dead_part_hash;
	POccurrenceKeyHash		m_external_part_key_hash;
	POccurrenceKeyHash		m_dead_external_part_hash;
	POccurrenceKeyHash		m_poccurrence_key_hash;
	POccurrenceKeyHash		m_dead_poccurrence_hash;
	PmiEntityArray			m_pmi_entities;
	struct vhash_s *		m_annotationhash;
	struct vlist_s *		m_brepfacelist;
	BREP_Edge_Matcher *		m_edgematcher;
	BREP_Topology *			m_TopologyManager;
	bool					m_bMergeFaces;
	int						m_AnnotationCounter;
	bool					m_bHasBrepStructure;
	A3DTopoFace **			m_PartFaces;
	int						m_PartFaceNum;
	double					m_body_scale;
 	StringArray				m_name_array;
	StringArray				m_type_array;
	int						m_default_entry_index;
	A3DInt32				m_iMajorVersion;
	A3DInt32				m_iMinorVersion;
};

#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif
