//
// Copyright (c) 2002 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/DataLoader.h,v 1.28 2008-07-25 20:20:08 reuben Exp $
//


#if !defined(AFX_DATALOADER_H__A606F2DA_B9BD_487F_93F8_A22F5BAD1DA5__INCLUDED_)
#define AFX_DATALOADER_H__A606F2DA_B9BD_487F_93F8_A22F5BAD1DA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "HUtility.h"

#include "HStream.h"
#include "HOpcodeHandler.h"
struct IWebBrowserApp;


#include "Vector"
using namespace std;

 
class HBaseModel;
class HCtrlView;
class HCtrlDB;
class HBaseOperator;
class CHoops3dStreamCtrl;
class HUtilityXMLTag;
class HUtilityXMLGenerator;
class ModelStructureObject;



///! databuffer holds chunks of stream data
struct databuffer
{
	unsigned char *data;	    	/*!<Pointer to stream buffer */
	unsigned int length;	    	/*!<length of stream buffer */
};


//! The CDataLoader class provides support for loading a file in a piecwise fashion (streaming)
/*!
	By chopping up data into smaller chunks the CDataLoader class allows the streaming of HSF data while
	not interrupting any user interaction
    
*/
class CDataLoader  
{
public:
	/*! 
	  Class Constructor
	  \param ctrl Pointer to Control Class
 	*/
	CDataLoader(CHoops3dStreamCtrl *ctrl);
	virtual ~CDataLoader();

	/*! 
	  Class Initialization
	  \param view Pointer to Hoops View Object
 	*/
	void Init(HCtrlView *view);
	/*! 
	  Start file download
	  \param filename name of file to download
	  \param isStreamable true = allow streaming for this file, false = do not allow streaming for this file
	  \return success
	*/
	bool StartDownload(BSTR filename, bool isStreamable = true);
	/*! 
	   Put new data chunk in cache list
	  \param pBytes Pointer to data chunk
	  \param dwSize Size of data chunk
	  \return true = more data is pending, false = no more data is pending
	*/
	bool OnData (BYTE* pBytes, DWORD dwSize);

	/*! 
	  Process next data chunk. This function is typically called ín regular intervals from the main application
 	  \return true = more data is pending, false = no more data is pending
	*/
	bool ProcessNextChunk();	

	/*! 
	   \return Indicates if download is currently in progress
	*/	
	bool GetDownloadInProgress() { return m_bDownloadInProgress; }

	/*! 
	   \return Indicates if download is currently in progress
	*/	
	bool GetDownloadComplete() { return m_bDataProcessingComplete; }

	/*! 
	   \return Size of already received data
	*/	
	long GetDownloadDataReceived() { return m_DataReceived; }
	
	/*! 
	   \return Total size of downloaded file
	*/	
	long GetDownloadDataTotalSize() { return m_DataReceiveSize; }
	/*! 
	  Abort current download

	*/	
	void AbortDownload() { 
	    if (!m_bDataProcessingComplete || m_bDownloadInProgress) { 
	    m_bAbortDownload = true; 
	    if (!m_bDownloadInProgress) 
		m_bDataProcessingComplete = true;
	    }
	    
	    }
	/*! 
	  Set download status
 	  \param ulProgressMax Size of total data
 	*/
	void SetDownloadStatus(int ulProgressMax) { m_DataReceiveSize = ulProgressMax; }

	/*! 
 	  \return Restore camera to scene default
 	*/
	bool GetRestoreCamera() { return m_bRestoreCamera; }

	/*! 
 	    Restore camera to scene default
	    \param restorecamera TRUE: Restore Camera
 	*/
	void SetRestoreCamera(bool restorecamera) { m_bRestoreCamera = restorecamera; }

	
	/*! 
 	    Sets Text String containing xml model structure information
	    \param data Pointer to Text String
 	*/
	void SetTreeControlXML(char *data);
    
	/*! 
 	    Returns Model Structure XML
	    \return pointer to text string
 	*/
	char *GetTreeControlXML() { return m_pTreeControlXML; }


	/*! 
 	    Returns Pointer to a list of Model Structure Types (body, shell, face,etc.)
	    \return Pointer to vlist
 	*/
	struct vlist_s* GetModelStructureTypeList() { return m_ModelStructureTypesList; }    
	/*! 
 	    Returns Pointer to the Model Structure Tree describing the model structure of the currently loaded hsf file
	    \return Pointer to ModelStructureObject
 	*/
	ModelStructureObject *GetModelStructureObjectTree() { return m_pModelStructureObjectTree; }

	/*! 
 	    Filters Identifier based on model structure type. (example: an identifier pointing to an edge with a face as a filter
		will return the identifier of its parent face
	    \return Pointer to identifier
 	*/
	int FilterIdentifier(int identifier, char *type);
	/*! 
		Given the model structure object to start the search from this function will return the model structure object associated to 
		a given identifier
		\param mso Model Structure Object
		\param identifier Identifier to search for
 	    \return Model Structure Object with given identifier
 	*/
	ModelStructureObject * FindModelStructureObject(ModelStructureObject *mso, int identifier);
	
	/*! 
 	    Returns Model Structure XML for children of the object with the given identifier
	    \param identifier Identifier to start returning XML description from
		\param text XML description of children for given identifier (returned)

 	*/
	void GetXMLForItemChildren(int identifier, char *(&text));
	
	/*! 
		Given the model structure object to start the search from this function will return the model structure object associated to 
		a given path
		\param mso Model Structure Object
		\param path Path to search for
 	    \return Model Structure Object with given path
 	*/
	ModelStructureObject * FindModelStructureObject(ModelStructureObject *mso, char *path);
	/*! 
 	    Returns Model Structure XML for children of the given model structure object
	    \param mso Model Structure Object to start returning XML description from
		\param text XML description of children for given identifier (returned)

 	*/
	void GetXMLForItemChildren(ModelStructureObject *mso, char *(&text));
	/*! 
 	    Returns Model Structure XML for children of the object with the given path
	    \param path Path of model structure object to start returning XML description from
		\param text XML description of children for given identifier (returned)

 	*/
	void GetXMLForItemChildren(char *path, char *(&text));
	/*! 
 	    Returns full path for given identifier
	    \param identifier Identifier to start returning path for
		\param path path for given identifier (returned)

 	*/
	void GetPathFromIdentifier(int identifier, char *path);

	
	/*! 
 	    \return HCtrlView Object

 	*/
	HCtrlView * GetView() { return m_pView; }
	/*! 
 	    \return Control Class Object

 	*/
	CHoops3dStreamCtrl *GetControl() { return m_pStreamControl; }


	DWORD				m_ParsingThread;		/*!< parsing thread ID*/
protected:
	/*! 
	  Process new data chunk (either store or hand to streaming toolkit)
	  \param pBytes Pointer to data chunk
	  \param dwSize Size of data chunk
	  \return true = more data is pending, false = no more data is pending
	*/
	TK_Status			ProcessData( BYTE* pBytes, DWORD dwSize);
	/*! 
	   Free data cache
	*/
	void ClearCachedDataList();


	
	vector <databuffer *> m_CachedDataList;			/*!< vector of data chunks*/

	HCtrlView*			m_pView;					/*!< Pointer to HOOPS view object*/
	bool				m_bDataIsStreamable;		/*!< true = file is streamable, false = file is not streamable*/

	bool				m_bDownloadInProgress;		/*!< true = download currently in progress, false = no download in progress*/
	long				m_DataReceived;				/*!< amount of already received data*/
	long				m_DataReceiveSize;			/*!< total size of downloaded file*/
	bool				m_bAbortDownload;			/*!< true = abort download as soon as possible, false = no abortion*/

	bool				m_bDataProcessingComplete;  /*!< true = all data chunks have been processed, false = data processing in progress*/

	bool				m_bRestoreCamera;	     /*!< true = restore camera, false = do not restore camera*/

private:
	void				ResetModelStructureTypes();

	FILE *				m_temphandle;
	TCHAR				m_tempfilename[MAX_PATH];
	char *				m_pTreeControlXML;
	struct vlist_s*			m_ModelStructureTypesList;				/*!< Pointer to list of child animations */
	ModelStructureObject		*m_pModelStructureObjectTree;		
	CHoops3dStreamCtrl		*m_pStreamControl;


};


#ifndef DOXYGEN_SHOULD_SKIP_THIS

template <class T>
class CBindStatusCallback2 : public CBindStatusCallback<T>
{
	typedef void (T::*ATL_PDATAAVAILABLE2)(CBindStatusCallback<T>* pbsc, BYTE* pBytes, DWORD dwSize);

public:
	STDMETHOD(OnProgress)(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
	{
//		ATLTRACE(_T("CBindStatusCallback2::OnProgress"));
//		return m_pT->OnProgress ( ulProgress, ulProgressMax, ulStatusCode, szStatusText );
		m_pT->GetDataLoader()->SetDownloadStatus(ulProgressMax);
		return S_OK;
	}

	static HRESULT Download(T* pT, ATL_PDATAAVAILABLE2 pFunc, BSTR bstrURL, IUnknown* pUnkContainer = NULL, BOOL bRelative = FALSE)
	{
		CComObject<CBindStatusCallback2<T> > *pbsc;
		HRESULT hRes = CComObject<CBindStatusCallback2<T> >::CreateInstance(&pbsc);
		if (FAILED(hRes))
			return hRes;
 		return pbsc->StartAsyncDownload(pT, pFunc, bstrURL, pUnkContainer, bRelative);
	}
};

class ModelStructureType
{
public:

    ModelStructureType()
    {
	m_pName = 0;
	m_pImage = 0;
	m_bSelectable = false;
	
    }
    ~ModelStructureType()
    {
	delete [] m_pName;
	delete [] m_pImage;
    }

    void SetName(char *name)
    {
	m_pName = new char[strlen(name)+1];
	strcpy(m_pName, name);
    }

    void SetImage(char *image)
    {
	m_pImage = new char[strlen(image)+1];
	strcpy(m_pImage, image);
    }

    char *GetName() { return m_pName; }
    char *GetImage() { return m_pImage; }
    bool GetSelectable() { return m_bSelectable; }
    void SetSelectable( bool selectable ) { m_bSelectable = selectable; }

    char *m_pName;
    char *m_pImage;
    bool m_bSelectable;

};

class ModelStructureObject
{
public:

    ModelStructureObject();
     ~ModelStructureObject();
    void SetType(char *name)
    {
	m_pType = new char[strlen(name)+1];
	strcpy(m_pType, name);
    }
    void SetType(ModelStructureType *type)
    {
	m_pTypePointer = type;
    }

    void SetIdentifier(int identifier) 
    { 
	m_Identifier = identifier;
    }
    void SetParent(ModelStructureObject *parent)
    {
	m_pParent = parent;
    }
    void SetName(char *name)
    {
	m_pName = new char[strlen(name)+1];
	strcpy(m_pName, name);
    }

    char *GetType() { return m_pType; }
    ModelStructureType *GetTypePointer() { return m_pTypePointer; }
    void SelectAllChildItemsRecursive(HBaseView *view);
    void Select(HBaseView *view);


    void AddChild(ModelStructureObject *child);
 
    char *m_pType;
    char *m_pName;
    struct vlist_s*			m_Children;		
    struct vlist_s*			m_IdentifierList;		
    ModelStructureObject *m_pParent;
    ModelStructureType *m_pTypePointer;
    int m_Identifier;

};


class TK_ATL_Initial_View : public HTK_Camera 
{
private:
	HCtrlView * m_pView;
	int				my_stage;
	HTK_Camera		*my_camera; 
	CDataLoader		*m_pDataLoader;

public:
	TK_ATL_Initial_View(HCtrlView * view, CDataLoader *dataloader) : HTK_Camera(TKE_View) 
	{ 
		m_pView = view;
		m_pDataLoader = dataloader;
	}

	TK_Status	Interpret(BStreamFileToolkit &tk, ID_Key key, int variant) alter;
	TK_Status   Execute (BStreamFileToolkit & tk) alter;	
};




//! The TK_Bhv_XML subclasses writes and reads behaviour related XML data
class TK_ModelStructure_XML : public TK_XML
{

 
public:

	/*!
	Constructs a TK_Bhv_XML Object
	\param model Pointer to HBaseModel object
 	*/
	TK_ModelStructure_XML(CDataLoader * model, HStreamFileToolkit*toolkit) : TK_XML() 
	{ 
		m_pDataLoader = model;
		m_pStreamFileToolkit = toolkit;
	}


	/*! customized for this class to populate MVO 'behavior' data structures with information */
	TK_Status   Execute (BStreamFileToolkit & tk) alter;

	static void *XMLCallback(HUtilityXMLTag *xt, bool open, void *m_pExtraData);
	
private:
	CDataLoader *	m_pDataLoader;	
	HStreamFileToolkit * m_pStreamFileToolkit;
	struct vlist_s*			m_TempObjects;				/*!< Pointer to list of child animations */


};

class XML_Parsing_Object
{
public:
	CDataLoader *	m_pDataLoader;	
	char *buffer;
	static unsigned long XMLParsingThread(LPVOID pParam);
	struct vlist_s*			m_TempObjects;				/*!< Pointer to list of child animations */
	HUtilityXMLGenerator	    * m_pXmlgen;
 
};


#endif

#endif // !defined(AFX_DATALOADER_H__A606F2DA_B9BD_487F_93F8_A22F5BAD1DA5__INCLUDED_)


