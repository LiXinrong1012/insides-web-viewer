//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HIOManager.h,v 1.146.2.1 2011-01-11 22:35:59 guido Exp $
//

/*! 
    \file HIOManager.h
    \brief A header file containing the HIO classes for passing to 
		HBaseView::FileInput and HBaseView::FileOutput 
*/

#ifndef _HIOMANAGER_H
#define _HIOMANAGER_H

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include "HTools.h"


// forwards
enum HFileOutputResult;
class HPDFOptions;
class HBaseView;
class HCamera;
class HBaseModel;
struct vlist_s;
class HStreamFileToolkit;
class HBhvBehaviorManager;
class BREP_Topology;

enum H_OUTPUT_TYPE
{
	H_OUTPUT_TYPE_DEFAULT = 0,
	H_PDF_OUTPUT_PORTFOLIO,
	H_PDF_OUTPUT_3D,
	H_PDF_OUTPUT_2D,
	H_SINGLE_PASS_ZSORT,
	H_SINGLE_PASS_NO_HIDDEN_SURFACES
};


/*! \def HInputOpNone
	\brief This HInputHandler supports no input
*/
#define HInputOpNone					(1UL<<0)

/*! \def HInputOpFileInputByKey
	\brief This HInputHandler supports input to a segment key 	
*/
#define HInputOpFileInputByKey			(1UL<<1)

/*! \def HInputOpFileInputToImageKey
	\brief This HInputHandler supports input to an image key 	
*/
#define HInputOpFileInputToImageKey		(1UL<<2)

/*! \def HOutputOpNone
	\brief This HOutputHandler supports no output
*/
#define HOutputOpNone					(1UL<<0)

/*! \def HOutputOpFileOutputByKey
	\brief This HOutputHandler supports output from a segment key 	
*/
#define HOutputOpFileOutputByKey		(1UL<<1)

/*! \def HOutputOpFileOutputFromImageKey
	\brief This HOutputHandler supports output from an image key 	
*/
#define HOutputOpFileOutputFromImageKey	(1UL<<2)


/*! 
    \def HIORegisterInputType(type,input_object)
	Used by a HInputHandler to set extension types that it handles
*/
#define HIORegisterInputType(type,input_object) do {HIOManager::GetCurrentHIOManager()->RegisterInputHandler(type, input_object); }while(0);



//! HIORegisterOutputType(type,output_object)  Used by a HOutputHandler to set extension types that it handler.
#define HIORegisterOutputType(type,output_object) do { HIOManager::GetCurrentHIOManager()->RegisterOutputHandler(type, output_object); }while(0); 




/*!
HIONoticeCallback must be sub-classed if the input or output ProgressNoticeCallback 
or InformationNoticeCallback are used.
*/	
class MVO_API HIONoticeCallback
{
public:

	virtual ~HIONoticeCallback() {;};
	/*! 
	This abstract function will receive any notices from its callback. 
	The notice data is only valid during the function call.
	*/
	virtual void Notice(const char * notice) =0;
	virtual void Notice(const __wchar_t * notice){
	};
#ifdef H_USHORT_OVERLOAD
	virtual void Notice(const unsigned short * notice){
		Notice((__wchar_t const *) notice);
	};
#endif
};

/*!
HIOPercentNoticeCallback must be sub-classed if the input or output ProgressPercentNoticeCallback.
*/	
class MVO_API HIOPercentNoticeCallback
{
public:
	virtual ~HIOPercentNoticeCallback();
	/*! 
	This abstract function will receive any notices from its callback. 
	The value will be between 0.0 and 1.0.
	*/
	virtual void Notice(float notice) =0;
};



/*! Function prototype for the Create/Free methods of the loadable HIO modules.
*/
typedef void * (*HIO_CREATE_FREE_FUNCTION)(void *);

/*! Function prototype for the FreeConnector methods of the HIOConnector class.
*/
typedef void (*HIO_FREE_CONNECTOR_FUNCTION)(void *);

/*!
HIOConnector manages the associativity between the HOOPS entity and the imported/exported 
entity. Each file import/export will result into on HIOConnector object if requested which 
can be used to query the mapping.  In future, it is planned that this will replace the modeler bridges
*/
class MVO_API HIOConnector
{
public:

	/*Constructs an HIOConnector object.*/
	HIOConnector();
	virtual ~HIOConnector();

	/*! 
	This method gets the HOOPS entity or key associated with the given kernel entity. If there are 
	multiple HOOPS entities associated the given kernel entity, this method will return the first one. In such case,
	it is recommended that you use #GetHoopsEntities.
	\param pKernelEntity A void* to the kernel entity.
	\returns The HC_KEY of the associated HOOPS entity.
	*/
	virtual HC_KEY GetHoopsEntity(void * pKernelEntity);

	/*! 
	This method gets the kernel entity associated with the given HOOPS entity. If there are 
	multiple kernel entities associated the given key, this method will return the first one. In such case,
	it is recommended that you use #GetKernelEntities.
	\param key The HC_KEY to the HOOPS entity associated with the kernel entity to search for.
	\returns A void* to the associated kernel entity.
	*/
	virtual void * GetKernelEntity(HC_KEY key);

	/*! 
	This method returns a list of all HOOPS entities (keys) associated with the given kernel entity. 
	\param pKernelEntity A void* to the kernel entity.
	\param ret_HoopsKeysList Returns a list of HOOPS HC_KEYS. Please pass a valid vlist pointer.
	\returns True if ret_HoopsKeysList could be populated.
	*/
	virtual bool GetHoopsEntities(void * pKernelEntity, vlist_s *ret_HoopsKeysList);

	/*! 
	This method returns a list of all the kernel entities associated with the given HOOPS entity. 
	\param key The HC_KEY to the HOOPS entity.
	\param ret_KernelEntitiesList Returns a list of kernel entities as void*. Please pass a valid vlist pointer.
	\returns True if ret_KernelEntitiesList could be populated.
	*/
	virtual bool GetKernelEntities(HC_KEY key, vlist_s *ret_KernelEntitiesList);

	/*! 
	This method adds an association between a HOOPS key and a kernel entity.
	\param key The HC_KEY object to the HOOPS entity.
	\param pKernalEntity A void* to the associated kernel entity to be mapped to the the HOOPS key.
	*/
	virtual void AddConnection(HC_KEY key, void* pKernelEntity);


	/*! 
	This method calls #HC_Optimize_Segment_Tree on the given segment and updates the connections 
	using #HC_Show_Optimized_Mapping. 
	\param segname The segment on which the optimization is to be performed.
	\param option_string A comma separated list of the desired settings as described in #HC_Optimize_Segment_Tree.
	*/
	virtual void OptimizeTree(const char * segname, const char * option_string);

protected:

	//! A hash map between HOOPS Keys and kernel entities.
	struct vhash_s *mhash_Hoops2Kernel;

	//! A hash map between kernel entities and HOOPS Keys.
	struct vhash_s *mhash_Kernel2Hoops;

};

/*! 
	\enum HInputHandlerStyle
	Specifies input styles.
*/
enum HInputHandlerStyle {
	HInputHandlerStyleModel, //!< Specifies an #HInputHandler for model data.
	HInputHandlerStyleImage  //!< Specifies an #HInputHandler for image data.
};

/*! 
	HInputHandlerOptions is used to pass data to the HInputHandler.
	All options are used based on the handler's needs. 
	Specific HInputHandler subclassed instances should document their own usage of options.
*/
class MVO_API HInputHandlerOptions 
{
public:

	/*! Construct an HInputHandlerOptions object. */
	HInputHandlerOptions() {
		m_pHBaseView=0;
		m_pImageName=0;
		m_pImageFormat=0;
		m_pConnector=0;
		m_pExtendedData=0;
		m_bLocal = false;
		m_tk = 0;
		m_bLogging = false;

	
		// Generic options used in DGN, SKP and DWG importer
		m_bIgnoreOffEntities = false;

		//DWG/SKP option
		m_bImportMetadata = false;

		// DWG import options (try and move them somewhere else)
		m_bInputViaHSF = false;
		m_Deviation = 10.0;
		m_bImportWireframeForBrep = false;
		m_numIsolines = 0;
		m_listRegAppNames = 0;
		m_listEntityType=0;
		m_bForceReimport = false;
		m_listDWGLayouts = 0;
		m_bAttachDWGHandles = false;
		m_bImportAllLayouts = false;
		m_bDWGInsertMeshesAsShells = false;
		m_bDisableDWGDrawOrder = false;

		// DGN import Options
		m_iDGNCellHeaderOption = SINGLE_ENTITY_CELLHEADER;
		m_coneFactor = 10.0;
		m_factorForSmartSolids = 45.0;
		m_bDGNRebaselineModel = true;
		m_bDGNImportAllModels = false;

		// PRC options
		m_pPRCPMIConnector = 0;
		m_pPRCTopologyManager = 0;
		m_bPRCMergeFaces = false;
		m_bPRCCreatePRCFileOnly = false;
		m_pPRCMultiModelSelectionCallback = 0;
		m_bPRCWrongVersion = false;
		m_pPRCAsmModelFile = 0;

		// DWF import options
		m_bDisableDWFDrawOrder = false;
		m_bDWFRebaselineModel = true;
		m_bImportThumbnail    = false;

		//SKP optimization option
		m_bOptimizeSegmentTree = false;

	};

	/*! Construct an HInputHandlerOptions object from another HInputHandlerOptions object. 
	\param o A pointer to an HInputHandlerOptions object that you want to copy. */
	HInputHandlerOptions(HInputHandlerOptions const *o) {
		m_pHBaseView = o->m_pHBaseView;
		m_pImageName = o->m_pImageName;
		m_pImageFormat = o->m_pImageFormat;
		m_pConnector = o->m_pConnector;
		m_pExtendedData = o->m_pExtendedData;
		m_bLocal = o->m_bLocal;
		
		
		//DWG/DGN/SKP option
		m_bIgnoreOffEntities = o->m_bIgnoreOffEntities;

		//DWG/SKP option
		m_bImportMetadata = o->m_bImportMetadata;


		//DWG Options
		m_bInputViaHSF = o->m_bInputViaHSF;
		m_Deviation = o->m_Deviation;
		m_bImportWireframeForBrep = o->m_bImportWireframeForBrep;
		m_numIsolines = o->m_numIsolines;
		m_listRegAppNames = o->m_listRegAppNames;
		m_listEntityType=o->m_listEntityType;	
		m_bForceReimport = o->m_bForceReimport;
		m_listDWGLayouts = o->m_listDWGLayouts;
		m_bAttachDWGHandles = o->m_bAttachDWGHandles;
		m_bImportAllLayouts = o->m_bImportAllLayouts;
		m_bDWGInsertMeshesAsShells = o->m_bDWGInsertMeshesAsShells;
		m_bDisableDWGDrawOrder = o->m_bDisableDWGDrawOrder;

		//DGN Options
		m_iDGNCellHeaderOption = o->m_iDGNCellHeaderOption;
		m_bDGNRebaselineModel = o->m_bDGNRebaselineModel;
		m_coneFactor = o->m_coneFactor;
		m_factorForSmartSolids = o->m_factorForSmartSolids;
		m_bDGNImportAllModels = o->m_bDGNImportAllModels;

		// PRC options
		m_pPRCPMIConnector = o->m_pPRCPMIConnector;
		m_pPRCTopologyManager = o->m_pPRCTopologyManager;
		m_bPRCMergeFaces = o->m_bPRCMergeFaces;
		m_bPRCCreatePRCFileOnly = o->m_bPRCCreatePRCFileOnly;
		m_pPRCMultiModelSelectionCallback = o->m_pPRCMultiModelSelectionCallback;
		m_bPRCWrongVersion = o->m_bPRCWrongVersion;
		m_pPRCAsmModelFile = o->m_pPRCAsmModelFile;

		// DWF import options
		m_bDisableDWFDrawOrder = o->m_bDisableDWFDrawOrder;
		m_bDWFRebaselineModel = o->m_bDWFRebaselineModel;
		m_bImportThumbnail = o->m_bImportThumbnail;
		

		//SKP import option
		m_bOptimizeSegmentTree = o->m_bOptimizeSegmentTree;

	};

	/*! Construct an HInputHandlerOptions object from another HInputHandlerOptions object. 
	\param o Pass by reference an HInputHandlerOptions object that you want to copy. */
	HInputHandlerOptions(const HInputHandlerOptions &o) {
		m_pHBaseView = o.m_pHBaseView;
		m_pImageName = o.m_pImageName;
		m_pImageFormat = o.m_pImageFormat;
		m_pConnector = o.m_pConnector;
		m_pExtendedData = o.m_pExtendedData;
		m_bLocal = o.m_bLocal;

		//DWG/DGN/SKP option
		m_bIgnoreOffEntities = o.m_bIgnoreOffEntities;

		//DWG/SKP option
		m_bImportMetadata = o.m_bImportMetadata;

		//DWG options
		m_bInputViaHSF = o.m_bInputViaHSF;
		m_Deviation = o.m_Deviation;
		m_bImportWireframeForBrep = o.m_bImportWireframeForBrep;
		m_numIsolines = o.m_numIsolines;
		m_listRegAppNames = o.m_listRegAppNames;
		m_listEntityType = o.m_listEntityType;
		m_bForceReimport = o.m_bForceReimport;
		m_listDWGLayouts = o.m_listDWGLayouts;
		m_bAttachDWGHandles = o.m_bAttachDWGHandles;
		m_bImportAllLayouts = o.m_bImportAllLayouts;
		m_bDWGInsertMeshesAsShells = o.m_bDWGInsertMeshesAsShells;
		m_bDisableDWGDrawOrder = o.m_bDisableDWGDrawOrder;

		//DGN options
		m_iDGNCellHeaderOption = o.m_iDGNCellHeaderOption;
		m_bDGNRebaselineModel = o.m_bDGNRebaselineModel;
		m_coneFactor = o.m_coneFactor;
		m_factorForSmartSolids = o.m_factorForSmartSolids;
		m_bDGNImportAllModels = o.m_bDGNImportAllModels;

		// PRC options
		m_pPRCPMIConnector = o.m_pPRCPMIConnector;
		m_pPRCTopologyManager = o.m_pPRCTopologyManager;
		m_bPRCMergeFaces = o.m_bPRCMergeFaces;
		m_bPRCCreatePRCFileOnly = o.m_bPRCCreatePRCFileOnly;
		m_pPRCMultiModelSelectionCallback = o.m_pPRCMultiModelSelectionCallback;
		m_bPRCWrongVersion = o.m_bPRCWrongVersion;
		m_pPRCAsmModelFile = o.m_pPRCAsmModelFile;

		// DWF import options
		m_bDisableDWFDrawOrder = o.m_bDisableDWFDrawOrder;
		m_bDWFRebaselineModel = o.m_bDWFRebaselineModel;
		m_bImportThumbnail = o.m_bImportThumbnail;
		

		//SKP import option
		m_bOptimizeSegmentTree = o.m_bOptimizeSegmentTree;

	};

	virtual ~HInputHandlerOptions();

	//! A pointer to the HBaseView object for this input. 
	HBaseView * m_pHBaseView;

	//! The HOOPS image name to use for a newly loaded image. 
	const char * m_pImageName;

	//! The HOOPS omage format to use for loading an image if not using filename .ext for format. 
	const char * m_pImageFormat;

	//! The value is true if the image will have the local attribute.
	bool m_bLocal;

	//! The streamfile toolkit to be used.
	HStreamFileToolkit * m_tk;

	//! If true, logging will be enabled in those plugins that support it.
	bool m_bLogging;

	//! A pointer to HIOConnector object. The connectivity between HOOPS and kernel will be stored in this. 
	HIOConnector * m_pConnector;

	//! A pointer to extra data needed by a HInputHandler subclass 
	void * m_pExtendedData;

	//! DWG file import option: Set to true if you want to import the DWG file using BStream Toolkit. Use this option for very large DWG models.
	bool m_bInputViaHSF;

	//! DWG file import option: The allowable maximum difference in world space between a true mathematical surface and the tessellated surface.
	double m_Deviation;

	//! DWG and SKP import option: Set to true if you want to import the metadata (xdata) along with the geometry.
	bool m_bImportMetadata;

	/*! DWG file import option: List of strings (char*) which is name of registered application names. The DWG importer will import metadata (xdata)
		for these applications only. Pass NULL if you want import of all xData. This option will only be used if m_bImportMetadata is true.
	 */
	struct vlist_s * m_listRegAppNames;

	/*! DWG file import option: List of AcDb entities which user want to import(e.g. AcDb3dSolid, AcDbBlockReference). Pass NULL if you want to import all supported AcDb entities.*/
	struct vlist_s * m_listEntityType;

	//! DWG file import option: Set to true if you want to import the wireframe representation for BRep solids. For e.g. wireframe edges of a cube
	bool m_bImportWireframeForBrep;

	//! DWG file import option: Set the number of isolines you want for surfaces (cylindrical/spherical/toroidal). Set to 0 for suppressing isolines .
	double m_numIsolines;

	//! DWG file import option: If true, re-imports DWG files (master and all xrefs) even if their corresponding HSF files are found with a later date-timestamp. Valid only when m_bInputViaHSF is true.
	bool m_bForceReimport;

	/*!
	DWG file import option: If true, Draw order will be ignored, depth range setting 
	will not be added in entity segments. Segment optimization works better this way.
	*/
	bool m_bDisableDWGDrawOrder;

	/*! DWG file import option: List of DWG Layouts to be imported. If list is not provided, default Model_Space is imported */
	struct vlist_s * m_listDWGLayouts;

	/*!  DGN,DWG and SketchUp file import option: If true, ignores import of entities whose visibilty is off. */
	bool m_bIgnoreOffEntities;

	/*! DGN file import option: This is for elements inserted as meshes in HOOPS. Increasing value of this factor increases
	    the number of rows/columns in mesh elements.
	*/
	double m_coneFactor;

	/*! DGN file import option: This is for smarts/feature solids. This is angle in degree with range from 0 to 360
	    Increasing the value decreases the tessellation
	*/
	double m_factorForSmartSolids;

	/*! DWG file import option: If true, DWG entity handles will be imported and put it as UserOptions. Default value is false.*/
	bool m_bAttachDWGHandles;

	//! DGN file import option: has three option about how cell header should be imported
	int m_iDGNCellHeaderOption;


	
	/*! 
	Specifies how cell header should be imported
	*/
	enum {
		SINGLE_ENTITY_CELLHEADER, //!< indicates that cell header entity will be imported as single segment
		BREAK_CELLHEADER,         //!< indicates that cell header will have as many segments as its childs
		OPT_CELLHEADER            //!< same as BREAK_CELLHEADER, but segment structure will be optimized for color
	};


	// PRC options - these really shouldn't be here, and yet, they are.
	
	//! PRC import option: Returned to user. Indicates if there is a mismatch between the PRC import dlls and the header files
	bool m_bPRCWrongVersion;		

	//! PRC import option: Returned to user. Contains Pointer to A3DAsmModelFile entity
	void *m_pPRCAsmModelFile;

	//! PRC import option:  Pointer to connector class. If not null prc PMI entities will be associated to HOOPS keys
	HIOConnector *		m_pPRCPMIConnector;
	//! PRC import option:  Pointer to connector class. If not null prc topology entities will be associated to HOOPS keys
	BREP_Topology *		m_pPRCTopologyManager;
	//! PRC import option:  If true individual faces will be merged into one shell
	bool				m_bPRCMergeFaces;
	//! PRC import option:  If true temporary prc file will be created but no parsing and creation of HOOPS entities occurs
	bool				m_bPRCCreatePRCFileOnly;
	//! PRC import option:  Function pointer for interactive multi-model loading
	void (*m_pPRCMultiModelSelectionCallback) (char const * in_container, int in_num_configs, char const ** in_configs, 
											   int & out_config_selection);
	

	/*! DWG file import option: If true, All Paper_Space Layouts will get imported. 
	Model Space will have Visiblity=ON, while all others Layouts with visiblity=OFF.*/
	bool  m_bImportAllLayouts;

	//! DGN file import option: if true then whole model is rebased with use of model extents to compensate for the floating point precison loss
	bool m_bDGNRebaselineModel;
	
	//! DGN file import option: if true then all the models are imported in the DGN file else only current model is imported.
	bool m_bDGNImportAllModels;

	/*!
	DWG file import option: If true, All meshes will be converted as shells.
	*/
	bool m_bDWGInsertMeshesAsShells;

	// DWF import options
	/*!
	DWF file import option: If true, Draw order will be ignored, depth range setting 
	will not be added in entity segments. Segment optimization works better this way.
	*/
	bool m_bDisableDWFDrawOrder;

	//! DWF file import option: if true then Thumbnail are imported in the DWF file.
	bool m_bImportThumbnail;

	//! DWF file import option: if true then whole model is rebased with use of model extents to compensate for the floating point precison loss
	bool m_bDWFRebaselineModel;

	//! SKP file import option: if true then model is optimized using Optimize_Segment_Tree api. Can be set to true if scene graph structure is not importfant
	bool m_bOptimizeSegmentTree;
	

};



//! HInputHandler an abstract base class for model and image input.
/*! 
	HInputHandler is an abstract base class that performs model and image file input. 
	HIOManager::RegisterInputHandler is used to register an input handler for a 
	file extension type with the HIOManager.  To make a new input handler, create a 
	child class that inherits from this class and implements the abstract interfaces.
*/
class MVO_API HInputHandler 
{

public:
	/*! 
		For the constructor in any child class, note it must class must call SetInputOps() with the 
		subclassed HInputHandler instance type.

		For example, the following line of code can be used to specify a class supporting the image input:
		<pre>\code {SetInputOps(HInputOpFileInputToImageKey);};\endcode</pre>
	*/
	HInputHandler();
	virtual ~HInputHandler();

	/*! 
		\return The HInputOp which can be one of the following: #HInputOpNone, #HInputOpFileInputByKey or 
		#HInputOpFileInputToImageKey.
	*/ 
	unsigned long GetInputOps() {return m_InputOps;};


	/*! \return A character pointer denoting the name of the input handler. 
	*/
	virtual const char * GetInputName() = 0;  


	/*! 
		This abstract function must register extension types to be handled by subclassed HInputHandler instance.

		For example, the following line of code can be used to specify a class that will handle files with "stl" extensions:
		<pre>\code {HIORegisterInputType("stl",this);};\endcode</pre>
	*/
	virtual void RegisterInputHandlerTypes() = 0;

	/*! 
		This abstract method returns the #HInputHandlerStyle the HInputHandler.

		For example, the following line of code can be used for an HInputHandler that handles models: 
		<pre>\code {return HInputHandlerStyleModel;}\endcode</pre>
	*/
	virtual HInputHandlerStyle GetInputStyle() = 0;

#ifdef SWIG
	%typemap(ctype) HC_KEY * image_key "MVO_POINTER_SIZED_INT *"
	%typemap(imtype,out="MVO_POINTER_SIZED_INT") HC_KEY * image_key "out MVO_POINTER_SIZED_INT"
	%typemap(cstype,out="MVO_POINTER_SIZED_INT") HC_KEY * image_key "out MVO_POINTER_SIZED_INT"
	%typemap(csin) HC_KEY * image_key "out $csinput"
#endif

	/*! This method loads model data from a given file to a given HOOPS segment key.  Note that this <i>must</i> be 
	implemented in a subclassed HInputHandler instance handling models.
		\param filename The name of the file to load.
		\param key The HOOPS segment key to load model data into.
		\param options An options class containing any needed extra information for the operation.
		\return The #HFileInputResult result of the input operation.
	*/
	virtual	HFileInputResult FileInputByKey(const char * filename, HC_KEY key, HInputHandlerOptions * options);
	virtual	HFileInputResult FileInputByKey(const __wchar_t * filename, HC_KEY key, HInputHandlerOptions * options);


	/*! 
		This method loads model data from a given file to a given HOOPS segment key.  Note that this <i>must</i> be 
		implemented in a subclassed HInputHandler instance handling models.
		\param filename The UNICODE name of the file to load.
		\param key The HOOPS segment key to load model data into.
		\param options An options class containing any needed extra information for the operation.
		\return The #HFileInputResult result of the input operation.
	*/
	virtual	HFileInputResult FileInputByKey(const unsigned short * filename, HC_KEY key, HInputHandlerOptions * options);

	/*! 
		This method loads image data from a given file to a given HOOPS image key.  Note that this <i>must</i> be 
		implemented in a sub-classed HInputHandler instance handling Images.
		\param filename The name of the file to load.
		\param image_key The pointer to a HOOPS key that will be filled in with a HOOPS image key.
		\param segment_key The HOOPS segment key to create the image_key in ie. the working segment.
		\param options An options class containing any needed extra infromation for operation.
		\return The HFileInputResult result of the input operation.
	*/

	virtual HFileInputResult FileInputToImageKey(const char * filename, HC_KEY  *image_key, HC_KEY segment_key, HInputHandlerOptions * options);
	virtual HFileInputResult FileInputToImageKey(const __wchar_t * filename, HC_KEY  *image_key, HC_KEY segment_key, HInputHandlerOptions * options);


	/*! 
		This method loads image data from a given file to a given HOOPS image key.  Note that this <i>must</i> be 
		implemented in a sub-classed HInputHandler instance handling Images.
		\param filename The UNICODE name of the file to load.
		\param image_key The pointer to a HOOPS key that will be filled in with a HOOPS image key.
		\param segment_key The HOOPS segment key to create the image_key in ie. the working segment.
		\param options An options class containing any needed extra infromation for operation.
		\return The HFileInputResult result of the input operation.
	*/
	virtual HFileInputResult FileInputToImageKey(const unsigned short * filename, HC_KEY  *image_key, HC_KEY segment_key, HInputHandlerOptions * options);

#ifdef SWIG
	%clear HC_KEY * image_key;
#endif

	/*! 
	 	This method must be implemented in a subclassed HInputHandler.
		\returns The extension type or types that are handled by this HInputHandler.

		Examples:
		
		The following line of code can be used to specify the stl extension: 
		<pre>\code {return "stl";};\endcode</pre>

		The following line of code can be used to specify that the jpg, bmp and gif extension are handled:
		<pre>\code {return "jpg;bmp;gif";};\endcode</pre>
	*/
	virtual const char * GetInputTypesString() = 0;

	/*! If used this will return the last progress messages posted
		\returns The last progress posted and 0 if none is available.
	*/
	const __wchar_t * GetInputProgress();

	/*! If used this will return the last progress percent posted
		\returns The last progress posted or 0.0 if none is available.
	*/
	float GetInputPercentProgress();

	/*! If used this will return the oldest information messages posted
		\returns The oldest information posted and 0 if none is available.
	*/
	const __wchar_t * GetInputInformation();

	/*! If used this will call the notice function when progress is posted
		It is the duty of the caller to delete the notice_callback object
		passing 0 to this function will unset the callback.

		\returns The last callback object set
	*/
	HIONoticeCallback * SetInputProgressNoticeCallback(HIONoticeCallback *notice_callback);
	
	
	/*! If used this will call the notice function when percent progress is posted
		It is the duty of the caller to delete the notice_callback object
		passing 0 to this function will unset the callback.

		\returns The last callback object set
	*/
	HIOPercentNoticeCallback * SetInputPercentProgressNoticeCallback(HIOPercentNoticeCallback *percent_notice_callback);
	
	/*! If used this will call the notice function when information is posted
		It is the duty of the caller to delete the notice_callback object
		passing 0 to this function will unset the callback.

		\returns The last callback object set
	*/
	HIONoticeCallback * SetInputInformationNoticeCallback(HIONoticeCallback *notice_callback);

	//! This posts the current progress message 
	void ReportInputProgress(const char * progress);
	void ReportInputProgress(const __wchar_t * progress);

	//! This posts the current percent progress should be between 0.0 and 1.0
	void ReportInputPercentProgress(float percent_progress);

	//! This posts information to the information queue
	void ReportInputInformation(const char * information);
	void ReportInputInformation(const __wchar_t * information);

	void SetModuleDirectory(const char *module_directory);
	void SetModuleDirectory(const __wchar_t *module_directory);
protected:

	/*! The three FileInput methods must call this before loading data
		It restarts the information logging and sets the progress to "starting"
	*/
	void SetStartingInput(const char *filename);
	void SetStartingInput(const __wchar_t *filename = 0);

	/*! The three FileInput methods must call this after loading data if they work
		It sets the progress to "finished"
	*/
	void SetFinishedInput();

	//! This sets the HInputOp
	void SetInputOps(unsigned long ops) {m_InputOps=ops;};

	//! This is the HInputOp set for a subclassed instance
	unsigned long m_InputOps;

	__wchar_t *m_module_directory;

private:

	__wchar_t *m_progress;
	float m_percent_progress;
	__wchar_t *m_information;
	struct vlist_s *m_information_list;
	HIONoticeCallback *m_progress_callback;
	HIONoticeCallback *m_information_callback;
	HIOPercentNoticeCallback *m_percent_progress_callback;
};

/*! \enum HOutputHandlerStyle
	Specifies the output styles.
*/
enum HOutputHandlerStyle 
{
	HOutputHandlerStyleModel, //! Specifies an #HOutputHandler for geometry data.
	HOutputHandlerStyleImage, //! Specifies an #HOutputHandler for an image. 
	HOutputHandlerStyleHardcopy, //! Specifies an #HOutputHandler for a hardcopy output type.
	HOutputHandlerStyleHTML, //! Specifies an #HOutputHandler for a MVO style html file.
	HOutputHandlerStyleDontCare
};

/*!
	ExportedNameMap maps HC_KEYs to names in an exported file.  As of now, this is only needed by PDF.
	PDF exports a U3D file which names segments and shells using some undefined rules.  This makes it
	impossible to reference names in the U3D file from JavaScripts in the PDF file.  This map defines
	an interface to find out those names.
*/
class MVO_API ExportNameMap
{
private:
	void * _imp;
public:
	ExportNameMap();
	~ExportNameMap();

	H_FORMAT_TEXT lookup(HC_KEY) const;
	void tag(HC_KEY, H_FORMAT_TEXT const &);
};

/*! 
	HOutputHandlerOptions is used to pass data to HOutputHandler. 
	All options are used based on the handler's needs.
	Specific HOutputHandler subclassed instances should document their own usage of options.
*/
class MVO_API HOutputHandlerOptions 
{
public:
	/*! Constructs an HOutputHandlerOptions object. */
	HOutputHandlerOptions();

	virtual char const * GetType() const;

	/*! Any application wishing to customize how the options are populated should derive from this class
	and overload this function.  */
	virtual bool PopulateOptions();
	
	/*! Constructs an HOutputHandlerOptions object from another HOutputHandlerOptions object. 
		\param o A pointer to the HOutputHandlerOptions object you want to copy.
	*/
	HOutputHandlerOptions(HOutputHandlerOptions const *o) {
		 Init(o);
	};

	/*! Constructs an HOutputHandlerOptions object from another HOutputHandlerOptions object. 
		\param o A reference to the HOutputHandlerOptions object you want to copy.
	*/
	HOutputHandlerOptions(const HOutputHandlerOptions &o) {
		Init(&o);
	};


	virtual ~HOutputHandlerOptions();

	/*! This method initializes this HOutputHandlerOptions object from using the properties of another HOutputHandlerOptions object. 
		\param o A pointer to the HOutputHandlerOptions object you want to copy.
	*/
	void Init(HOutputHandlerOptions const *o);

	//! A pointer to the HBaseView object for this output.
	HBaseView * m_pHBaseView;
	//! A pointer to the HBaseView object for this output.
	HBaseView * const View() const {return m_pHBaseView;};
	//! A pointer to the HBaseView object for this output.
	void View(HBaseView * const v) {m_pHBaseView = v;};

	//! A pointer to the HBaseModel object for this output.
	HBaseModel * m_pHBaseModel;
	//! A pointer to the HBaseModel object for this output.
	HBaseModel * const Model() const {return m_pHBaseModel;};
	//! A pointer to the HBaseModel object for this output.
	void Model(HBaseModel * const m) {m_pHBaseModel = m;};

	//! A pointer to the HCamera object for this output.
	HCamera * m_pCamera;
	//! A pointer to the HCamera object for this output.
	HCamera * const Camera() const {return m_pCamera;};
	//! A pointer to the HCamera object for this output.
	void Camera(HCamera * const c) {m_pCamera = c;};

	//! The HC_Key for this output.
	HC_KEY m_Key;
	//! The HC_Key for this output.
	HC_KEY const Key() const {return m_Key;};
	//! The HC_Key for this output.
	void Key(HC_KEY const k) {m_Key = k;};

	//! HOOPS HSRAOption string . 
	char const * m_pHSRAOptions;
	//! HOOPS HSRAOption string . 
	char const * const HSRAOptions() const {return m_pHSRAOptions;};
	//! HOOPS HSRAOption string . 
	void HSRAOptions(char const * const tf) {m_pHSRAOptions = tf;};

	//! RGB color stored in xyz.  
	HPoint const * m_pWindowColor;
	//! Set the color of the window.  The RGB color stored in xyz of HPoint.  
	HPoint const * const WindowColor() const {return m_pWindowColor;};
	//! Set the color of the window.  The RGB color stored in xyz of HPoint.  
	void WindowColor(HPoint const * const tf) {m_pWindowColor = tf;};

	//! If set to true, the background color of the view is used.
	bool m_bUseWindowColor;
	//! If set to true, the background color of the view is used.
	bool const UseWindowColor() const {return m_bUseWindowColor;};
	//! If set to true, the background color of the view is used.
	void UseWindowColor(bool const tf) {m_bUseWindowColor = tf;};

	//! Width for output sizing in inches.
	float m_Window_Width;
	//! Width for output sizing in inches.
	float const WindowWidth() const {return m_Window_Width;};
	//! Width for output sizing in inches.
	void WindowWidth(float const f) {m_Window_Width = f;};

	//! Height for output sizing in inches.
	float m_Window_Height;
	//! Height for output sizing in inches.
	float const WindowHeight() const {return m_Window_Height;};
	//! Height for output sizing in inches.
	void WindowHeight(float const f) {m_Window_Height = f;};

	//! Width for output sizing in inches.
	float m_Paper_Width;
	//! Width for output sizing in inches.
	float const PaperWidth() const {return m_Paper_Width;};
	//! Width for output sizing in inches.
	void PaperWidth(float const f) {m_Paper_Width = f;};

	//! Height for output sizing in inches.
	float m_Paper_Height;
	//! Height for output sizing in inches.
	float const PaperHeight() const {return m_Paper_Height;};
	//! Height for output sizing in inches.
	void PaperHeight(float const f) {m_Paper_Height = f;};

	//! Specifies black and white output. 
	bool m_ForceGrayscale;
	//! Specifies black and white output. 
	bool const ForceGrayscale() const {return m_ForceGrayscale;};
	//! Specifies black and white output. 
	void ForceGrayscale(bool const tf) {m_ForceGrayscale = tf;};

	//! This option has been deprecated. Specifies printing method.
	bool m_bFastPrint;
	//! This option has been deprecated. Specifies printing method.
	bool const FastPrint() const {return m_bFastPrint;};
	//! This option has been deprecated. Specifies printing method.
	void FastPrint(bool const tf) {m_bFastPrint = tf;};

	//! This option has been deprecated and has no effect.
	bool m_bConserveMemory;
	//! This option has been deprecated and has no effect.
	bool const ConserveMemory() const {return m_bConserveMemory;};
	//! This option has been deprecated and has no effect.
	void ConserveMemory(bool const tf) {m_bConserveMemory = tf;};

 	bool m_bWriteAnimations;
	bool const WriteAnimations() const {return m_bWriteAnimations;};
	void WriteAnimations(bool const tf) {m_bWriteAnimations = tf;};

	//! Determines if a window frame is drawn or not.
	bool m_bWindowFrame;
	//! Determines if a window frame is drawn or not.
	bool const WindowFrame() const {return m_bWindowFrame;};
	//! Determines if a window frame is drawn or not.
	void WindowFrame(bool const tf) {m_bWindowFrame = tf;};

	//! Determines if HOOPS is calculating a subscreen to match the output to the size of the view window.
	bool m_bUseSubscreen;
	//! Determines if HOOPS is calculating a subscreen to match the output to the size of the view window.
	bool const UseSubscreen() const {return m_bUseSubscreen;};
	//! Determines if HOOPS is calculating a subscreen to match the output to the size of the view window.
	void UseSubscreen(bool const tf) {m_bUseSubscreen = tf;};

	//! Indicates the DPI used for images.  This is calculated with info from HC_Show_Device_Info.
	int m_Image_Dpi;
	//! Indicates the DPI used for images.  This is calculated with info from HC_Show_Device_Info.
	int const ImageDpi() const {return m_Image_Dpi;};
	//! Indicates the DPI used for images.  This is calculated with info from HC_Show_Device_Info.
	void ImageDpi(int const dpi) {m_Image_Dpi = dpi;};

	//! Indicates the DPI used for paper.  This is set from the options dialog.
	int m_Paper_Dpi;
	//! Indicates the DPI used for paper.  This is set from the options dialog.
	int const PaperDpi() const {return m_Paper_Dpi;};
	//! Indicates the DPI used for paper.  This is set from the options dialog.
	void PaperDpi(int const dpi) {m_Paper_Dpi = dpi;};

	//! A pointer to extra data needed by a HOutputHandler subclass .
	void * m_pExtendedData;
	void * const ExtendedData() const {return m_pExtendedData;};
	void ExtendedData(void * const vp) {m_pExtendedData = vp;};
	void ExtendedData(HPDFOptions * const vp) {m_pExtendedData = (void*)vp;};


	//! The file format version desired for writing.
	int m_Version;
	int const Version() const {return m_Version;};
	void Version(int const v) {m_Version = v;};

	//! The output type.
	H_OUTPUT_TYPE m_OutputType;
	//! The output type.
	H_OUTPUT_TYPE OutputType() const {return m_OutputType;};
	//! The output type.
	void OutputType(H_OUTPUT_TYPE ot) {m_OutputType = ot;};

	//! Some file formats, such as pdf and dwf,  support 2d and/or 3d output.  Set this to true for 3d output.
	bool m_b3dOutput;
	//! Some file formats, such as pdf and dwf,  support 2d and/or 3d output.  Set this to true for 3d output.
	bool const Output3d() const {return m_b3dOutput;};
	//! Some file formats, such as pdf and dwf,  support 2d and/or 3d output.  Set this to true for 3d output.
	void Output3d(bool const tf) {m_b3dOutput = tf;};

	//! Some file formats, support binary and ascii such as STL.  Set this to true for ascii output.
	bool m_bAscii;
	//! Some file formats, support binary and ascii such as STL.  Set this to true for ascii output.
	bool const Ascii() const {return m_bAscii;};
	//! Some file formats, support binary and ascii such as STL.  Set this to true for ascii output.
	void Ascii(bool const tf) {m_bAscii = tf;};

	/*! Sets the page margin in inches.
		m_PageMargins[0] is the left margine
		m_PageMargins[1] is the right margine
		m_PageMargins[2] is the bottom margine
		m_PageMargins[3] is the top margine
		*/
	float m_PageMargins[4];

	//! A pointer to the behavior manager.
	HBhvBehaviorManager * m_pBehaviorManager;

	/*! DWF Model name */
	char const* m_pDWFModelName;

	/*! available for output handlers to map HC_KEYS to names in the output file. */
	ExportNameMap m_names;
};


//! HOutputHandler an abstract base class for model and image output.
/*! 
	HInputHandler is an abstract base class that performs model, image, hardcopy and html file output. 
	HIOManager::RegisterOutputHandler is used to register an output handler for a file extension type 
	with the HIOManager.  To make a new output handler, create a child class that inherits from this 
	class and implements the abstract interfaces.
*/
class MVO_API HOutputHandler 
{

public:
	/*! 
		For the constructor in any child class, note it must class must call SetOutputOps() with the 
		subclassed HOutputHandler instance type.

		For example, the following line of code can be used to specify a class supporting the image output:
		<pre>\code {SetOutputOps(HOutputOpFileOutputFromImageKey);};\endcode</pre>
	*/
	HOutputHandler();
	virtual ~HOutputHandler();


	/*! \return A character pointer denoting the name of the output handler. 
	*/
	virtual const char * GetOutputName() = 0;  

	/*! 
		\return The HOutputOp which specifies what kind of output this handlers works with.  It can be #HOutputOpNone, 
		#HOutputOpFileOutputByKey or #HOutputOpFileOutputFromImageKey.
	*/ 
	unsigned long GetOutputOps() {return m_OutputOps;};
	
	/*! 
		This abstract function must register extension types to be handled by subclassed HOutputHandler instance.

		For example, the following lines of code can be used to specify a class that will handle files with "tiff" 
		and "tif" extensions:
		<pre>\code 
		{HIORegisterOutputType("tif",this);
		HIORegisterOutputType("tiff",this);};
		\endcode</pre>
	*/
	virtual void RegisterOutputHandlerTypes() = 0;


	/*! This method writes model data from a given HOOPS key to a given output file. Note that this <i>must</i> 
	be implimented in a subclassed HOutputHandler instance handling models.
		\param filename The name of the file to output.
		\param key The HOOPS segment key to output model data from.
		\param options The options class containing any needed extra information for the operation.
		\return The #HFileOutputResult result of the output operation.
	*/
	virtual	HFileOutputResult FileOutputByKey(const char * filename, HC_KEY key, HOutputHandlerOptions * options);
	virtual	HFileOutputResult FileOutputByKey(const __wchar_t * filename, HC_KEY key, HOutputHandlerOptions * options);

	/*! This method writes model data from a given HOOPS key to a given output file. Note that this <i>must</i> 
	be implimented in a subclassed HOutputHandler instance handling models.
		\param filename The wide character name of the file to output.
		\param key The HOOPS segment key to get output model data from.
		\param options The options class containing any needed extra information for the operation.
		\return The #HFileOutputResult result of the output operation.
	*/
	virtual	HFileOutputResult FileOutputByKey(const unsigned short * filename, HC_KEY key, HOutputHandlerOptions * options);


	/*! This method writes image data from a given HOOPS key to a given output file. Note that this <i>must</i> 
	be implimented in a subclassed HOutputHandler instance handling images.
		This must be implemented in a subclassed HOutputHandler instance handling images.
		\param filename The name of the file to output.
		\param image_key The HOOPS image key to get output image data from.
		\param options The options class containing any needed extra information for the operation.
		\return The #HFileOutputResult result of the output operation.
	*/
	virtual HFileOutputResult FileOutputFromImageKey(const char * filename, HC_KEY image_key, HOutputHandlerOptions * options);
	virtual HFileOutputResult FileOutputFromImageKey(const __wchar_t * filename, HC_KEY image_key, HOutputHandlerOptions * options);

	/*! 
	 	This must be implemented in a subclassed HOutputHandler 
		\return The extension type or types that can be handled by this HOutputHandler. 

		For example: the following line of code can be use to specify the stl extenstion:
		<pre>\code {return "stl";};\endcode</pre>

		The following line of code can be used to specify that jpg, bmp and gif extension are handled: 
		<pre>\code {return "jpg;bmp;gif";};\endcode</pre>
	*/
	virtual const char * GetOutputTypesString() = 0;

	/*! 
		\return The #HOutputHandlerStyle that this instance will use. It can be HOutputHandlerStyleModel for geometry data, 
		#HOutputHandlerStyleImage for images, #HOutputHandlerStyleHardcopy for hardcopy or #HOutputHandlerStyleHTML 
		for MVO style html page.

		For example: the following code can be used for an HOutputHandler that outputs model:
		<pre>\code {return HOutputHandlerStyleModel;}\endcode</pre>
	*/
	virtual HOutputHandlerStyle GetOutputStyle() = 0;
	
	/*! 
	 	\return A default HSRA for HOutputHandler instance if needed.

		For example: the following line of code might be used for an output handler needing painters:
		<pre>\code {return "painters";};\endcode</pre>
	*/
	virtual const char * GetOutputDefaultHSRA();

	/*! If used this will return the last progress messages posted
		\returns The last progress posted and 0 if none is available.
	*/
	const char * GetOutputProgress();

	/*! If used this will return the last progress percent posted
		\returns The last progress posted or 0.0 if none is available.
	*/
	float GetOutputPercentProgress();

	/*! If used this will return the oldest information messages posted
		\returns The oldest information posted and 0 if none is available.
	*/
	const __wchar_t * GetOutputInformation();

	/*! If used this will call the notice function when progress is posted
		It is the duty of the caller to delete the notice_callback object
		passing 0 to this function will unset the callback.

		\returns The last callback object set
	*/
	HIONoticeCallback * SetOutputProgressNoticeCallback(HIONoticeCallback *notice_callback);

	
	/*! If used this will call the notice function when progress is posted
		It is the duty of the caller to delete the notice_callback object
		passing 0 to this function will unset the callback.

		\returns The last callback object set
	*/
	HIOPercentNoticeCallback * SetOutputPercentProgressNoticeCallback(HIOPercentNoticeCallback *percent_notice_callback);
	
	/*! If used this will call the notice function when information is posted
		It is the duty of the caller to delete the notice_callback object
		passing 0 to this function will unset the callback.

		\returns The last callback object set
	*/
	HIONoticeCallback * SetOutputInformationNoticeCallback(HIONoticeCallback *notice_callback);

	//! This posts the current progress message 
	void ReportOutputProgress(const char * progress);

	//! This posts the current percent progress message should be between 0.0 and 1.0 
	void ReportOutputPercentProgress(float percent_progress);

	//! This posts information to the information queue
	void ReportOutputInformation(const char * information);


	void SetModuleDirectory(const char *module_directory);
	void SetModuleDirectory(const __wchar_t *module_directory);

protected:

	/*! The three FileOutput methods must call this before loading data
		It restarts the information logging and sets the progress to "starting"
	*/
	void SetStartingOutput();

	/*! The three FileOutput methods must call this after loading data if they work
		It sets the progress to "finished"
	*/
	void SetFinishedOutput();

	//! This sets the HOutputOp.
	void SetOutputOps(unsigned long ops) {m_OutputOps=ops;};
	//! This is the HOutputOp set for a subclassed instance
	unsigned long m_OutputOps;

	char *m_module_directory;
private:

	char *m_progress;
	float m_percent_progress;
	__wchar_t *m_information;
	struct vlist_s *m_information_list;
	HIONoticeCallback *m_progress_callback;
	HIOPercentNoticeCallback *m_percent_progress_callback;
	HIONoticeCallback *m_information_callback;
};

/*!
	HIOManger manages subclassed instances of HInputHandler and HOutputHandler.
	It maps handlers to operations based on registered assocations and/or requested file extensions.
	It is created on demand by HDB.
*/
class MVO_API HIOManager
{

public:

	HIOManager();
	virtual ~HIOManager();
	
	/*!  
		This method associates a specified file type with an input handler.  If another
		input handler already exists for the file type, this method replaces it with the 
		given <i>handler</i>.
		
		\param file_type The file extension this to associate with the given <i>handler</i>.
		\param handler The handler for specified extension <i>file_type</i>. This may be 0 to clear extension handler.
		\return A pointer to old handler for the file extension.
	*/
	virtual HInputHandler * RegisterInputHandler(const char * file_type, HInputHandler * handler);

	/*!  
		This method associates a specified file type with an output handler.  If another 
		output handler already exists for the file type, this method replaces it with the 
		given handler. 
		\param file_type The file extension this to associate with the given <i>handler</i>.
		\param handler The handler for specified extension <i>file_type</i>. This may be 0 to clear extension handler.
		\return A pointer to old handler for the file extension.
	*/
	virtual HOutputHandler * RegisterOutputHandler(const char * file_type, HOutputHandler * handler);

	/*!  
		This method associates a specified file type with an HIOConnector.  If another 
		another connector already exists for the file type, this method replaces it with the 
		given connector. 

		\param file_type The file extension this connector is for.
		\param Create A pointer to the desired Create method.
		\param Free A pointer to the desired Free method
		\return A pointer to old connector for the file extension.
	*/
	virtual HIOConnector * RegisterConnector(const char * file_type, HIO_CREATE_FREE_FUNCTION Create, HIO_FREE_CONNECTOR_FUNCTION Free);

	/*! 
		\param file_type The extentsion to lookup handler for example: "jpg"
		\return The HInputHandler registered for specifed file type or 0 if none is registered.
	*/
	virtual HInputHandler * GetInputHandler(const char * file_type);
	HInputHandler * GetInputHandler(const __wchar_t * file_type);
#ifdef _MSC_VER
	HInputHandler * GetInputHandler(const unsigned short * file_type);
#endif

	/*! 
		\param file_type The extention to lookup handler for example: "jpg"
		\return The HOutputHandler registered for specifed file type or 0 if none is registered.
	*/
	virtual HOutputHandler * GetOutputHandler(const char * file_type);
	virtual HOutputHandler * GetOutputHandler(const __wchar_t * file_type);

	/*!
		This method registers default file handlers.  This called by HDB when it creates a HIOManager.
		To avoid the default handlers being set, pass your own HIOManager by calling HDB::SetHIOManager().
	*/
	virtual void RegisterHandlers();

	/*! 
		\return The list of all extensions registered with input handlers.  You can part this string to create a file type 
		list for input file dialogs.  The string's format looks like "jpg;gif;tiff".
	*/
	virtual const char * GetInputHandlerTypes();

	/*! 
		\return The list of all extensions registered with output handlers.  You can parse this string to create a file 
		type list for output file dialogs.  The string's format looks like "jpg;gif;tiff".
	*/
	virtual const char * GetOutputHandlerTypes();


	/*! 
		This method creates a new connector for the given type and returns a pointer to it.

		\param file_type The extension to lookup handler for example: "jpg".
		\return An HIOConnector registered for specifed file type or 0 if none.
	*/
	virtual HIOConnector * CreateConnector(const char * file_type);

	/*! 
		This method frees a connector for the file type associated with it.
		\param old_connector A pointer to the HIOConnector object you wan to free from a given type.
	*/
	virtual void FreeConnector(HIOConnector * old_connector);


	/*! 
	 	This method gets the current HIOManager. It will create on if none exists.	
		\return	The current manager from HDB.
	*/
	static HIOManager *GetCurrentHIOManager();

	/*!
		This method gets a string representation of the HFileOutputResults.
		\param result The HFileOutputResult that you want to get a string representation of.
		\param result_str Returns the string representation of the result.
	*/
	static void GetFileOutputResultString(HFileOutputResult result, char *result_str);

protected:

	//! A hash of HInputHandlers.
	struct vhash_s * input_handlers;

	//! A hash of HOutputHandlers.
	struct vhash_s * output_handlers;

	//! A hash of HIOConnector Create/Free functions.
	struct vhash_s * connector_procs;

	//! A list of default HInputHandlers created by the manager.
	struct vlist_s * owned_input_handlers;

	//! A list of default HOutputHandlers created by the manager.
	struct vlist_s * owned_output_handlers;

	//! A list of dynamically loaded HInputHandlers libraries.
	struct vlist_s * loaded_input_handlers;

	//! A list of dynamically loaded HOutputHandlers libraries.
	struct vlist_s * loaded_output_handlers;

	//! A list of created HIOConnectors.
	struct vhash_s * created_connectors;

	char * m_input_types;
	int m_input_types_allocated;

	char * m_output_types;
	int m_output_types_allocated;
};

#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif

