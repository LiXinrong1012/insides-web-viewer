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
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/DataLoader.cpp,v 1.67 2008-10-11 00:33:44 evan Exp $
//

#include "stdafx.h"

#include "HCtrlView.h"
#include "Hoops3dStream.h"

#include "HBaseView.h"
#include "HBaseModel.h"
#include "HEventInfo.h"
#include "HBaseOperator.h"
#include "HOpCameraOrbit.h"
#include "HOpCameraPan.h"
#include "HOpCameraZoom.h"
#include "HOpCameraZoomBox.h"
#include "HOpObjectAnnotate.h"
#include "HOpMarkupFreehand.h"
#include "HMySelectionSet.h"
#include "HConstantFramerate.h"
#include "HStream.h"
#include "HBhvUtility.h"
#include "hc.h"
#include "Hdb.h"
#include <atlctl.h>
#include <Wininet.h>
#include "Hoops3dStreamCtrl.h"
#include "DataLoader.h"
#include "HUtilityXMLParser.h"
#include "vlist.h"
#include "HDispatchXML.h"
#include "HUtilityLocaleString.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BUFFERSIZE 728000
#define BUFFERSIZE2 500000

	     
#define BOOL2bool(TRUE_Or_FALSE)	\
	(( TRUE_Or_FALSE == TRUE ) ? true : false)
	
CDataLoader::CDataLoader(CHoops3dStreamCtrl *ctrl)
{
    m_pTreeControlXML = 0;
    m_pModelStructureObjectTree = 0;
    m_pStreamControl = ctrl;
    m_ParsingThread = 0;
	m_ModelStructureTypesList = 0;
}

CDataLoader::~CDataLoader()
{
    delete [] m_pTreeControlXML;
    ResetModelStructureTypes();
    delete_vlist(m_ModelStructureTypesList);
    delete m_pModelStructureObjectTree;

}
void CDataLoader::ResetModelStructureTypes()
{	
    START_LIST_ITERATION(ModelStructureType, m_ModelStructureTypesList)
    	delete temp;
    END_LIST_ITERATION(m_ModelStructureTypesList);;
    vlist_flush(m_ModelStructureTypesList);

    delete m_pModelStructureObjectTree;
    m_pModelStructureObjectTree = new ModelStructureObject;

}

void CDataLoader::Init(HCtrlView *view)
{	
	m_pView = view;
	m_bDownloadInProgress = false;
	m_bDataProcessingComplete = true;
	m_bAbortDownload = false;
	HStreamFileToolkit *tk = view->GetModel()->GetStreamFileTK();
 	tk->SetOpcodeHandler(TKE_View, new TK_ATL_Initial_View(m_pView, this));
	m_bRestoreCamera = true;
	HBhvUtility::SetupAnimationReadFromHSF(tk, view->GetModel());
	view->GetModel()->GetDispatchXML()->AddHandler(new TK_ModelStructure_XML (this, tk));
	tk->SetOpcodeHandler (TKE_XML, view->GetModel()->GetDispatchXML()->MakeCopy());
	if(m_ModelStructureTypesList)
		delete_vlist(m_ModelStructureTypesList);
	m_ModelStructureTypesList = new_vlist(malloc, free);
}

bool  CDataLoader::StartDownload(BSTR bfilename, bool isStreamable)
{	
 	TCHAR extension[256];
	TCHAR stemp[4096];
	while (1)
	{
	    if (!m_ParsingThread)
		break;
		Sleep(100);
	}
	if (!m_bDownloadInProgress)
	{
//		m_pView->CreateProgressWindow();
		m_pView->SetHasCamera(false);
		m_DataReceived = 0;
		ClearCachedDataList();		
		m_bDownloadInProgress = true;
		m_bDataProcessingComplete = false;
		m_bAbortDownload = false;
		HUtility::FindFileNameExtension(bfilename, extension, 256);
		ResetModelStructureTypes();
		SetTreeControlXML(0);
		if (_tcscmp(extension, _T("hsf")) ==0 )
			m_bDataIsStreamable = isStreamable;
		else
			m_bDataIsStreamable = false;
		
		if (m_bDataIsStreamable)
		{
			HStreamFileToolkit *tk = m_pView->GetModel()->GetStreamFileTK(); 			
			tk->Restart();
		}
		else
		{
			// Create a tempfile that will act as the cache file.
			TCHAR   szTempPath[MAX_PATH];
			GetTempPath (MAX_PATH, szTempPath);		
			GetTempFileName (szTempPath, _T("hc"), 0, stemp); 
			_tcscpy(m_tempfilename, stemp);
 			_tcscat(m_tempfilename, L".");
			_tcscat(m_tempfilename, extension);
			if(sizeof(TCHAR) > 1)
				m_temphandle = _wfopen((wchar_t const*)&m_tempfilename[0], L"wb");
			else
				m_temphandle = fopen((char const*)&m_tempfilename[0], "wb");
		}		
		
		return true;
	}
	return false;
}



/*!
	Processes new chunk of HSF data

*/ 
TK_Status CDataLoader::ProcessData( BYTE* pBytes, DWORD dwSize)
{
	TK_Status status = TK_Normal;
	int per = (int)((float)m_DataReceived/(float)m_DataReceiveSize * 100.0f);
	if ((per % 5) == 0)
	{
	    HCtrlView::StreamProgressCallback(m_DataReceived, m_DataReceiveSize, m_pView);
		//m_pView->SetProgressWindow(per);
	}

	if (!m_bDataIsStreamable) {
		int result = fwrite (pBytes, dwSize, 1, m_temphandle);
		if(result != 1){
			status = TK_Error;
		}
	}
	else
	{

		HStreamFileToolkit *tk = m_pView->GetModel()->GetStreamFileTK();
		HC_Open_Segment_By_Key(m_pView->GetModel()->GetModelKey());
			status = tk->ParseBuffer ((const char *)pBytes,dwSize, TK_Normal);
			m_pView->EmitHSFData( ".", (const char*)pBytes, dwSize);
		HC_Close_Segment();
		if (!m_pView->OperatorStarted())
			m_pView->Update();
	}

	return status;
}	



bool CDataLoader::OnData (BYTE* pBytes, DWORD dwSize)
{

	if (m_bDownloadInProgress)
	{

		if (m_bAbortDownload || dwSize == 0 || pBytes == (BYTE*)0)
		{
			if (m_bAbortDownload)
			    m_bDataProcessingComplete = true;
			m_bAbortDownload = false;
			m_bDownloadInProgress = false;
  			return false;
		}			

		for (unsigned int i=0;i<dwSize;i+=BUFFERSIZE)
		{
			databuffer *databuf = new databuffer;
			
			if (i+BUFFERSIZE>dwSize)
				databuf->length = dwSize - i;
			else
				databuf->length = BUFFERSIZE;

 			databuf->data = new unsigned char[databuf->length];
			memcpy(databuf->data, pBytes+i, databuf->length);
		 	m_CachedDataList.insert(m_CachedDataList.end(), databuf);		
		} 
	}

	return true;
}


void CDataLoader::SetTreeControlXML(char *data)
{
    if (m_pTreeControlXML)
		delete [] m_pTreeControlXML;

    m_pTreeControlXML = 0;
    
	if (data){    
		m_pTreeControlXML = new char[strlen(data)+1];
		strcpy(m_pTreeControlXML, data);
    }
}
void CDataLoader::ClearCachedDataList()
{
	vector<databuffer *>::iterator iter = m_CachedDataList.begin();

	while (iter!=m_CachedDataList.end())
	{
		delete [] (*iter)->data;
		delete *iter;
		++iter;
	}
	m_CachedDataList.clear();
}


ModelStructureObject * CDataLoader::FindModelStructureObject(ModelStructureObject *mso, int identifier)
{
    if (mso->m_Identifier == identifier)
	return mso;
    if (mso->m_IdentifierList)    
    {
        START_LIST_ITERATION(char, mso->m_IdentifierList)
	    if (atoi(temp) == identifier)
		return mso;
		END_LIST_ITERATION(mso->m_IdentifierList);
    }

    ModelStructureObject *found = 0;
    START_LIST_ITERATION(ModelStructureObject, mso->m_Children)
	found = FindModelStructureObject(temp, identifier);
	if (found)
	    break;
    END_LIST_ITERATION(mso->m_Children);
    return found; 
}


static bool ExtractString(char *orig, char *extr)
{
    if (!strstr(orig,"/"))
    {    
		strcpy(extr, orig);
		return true;
    }
    HC_Parse_String(orig, "/",0,extr);
	
	return false;
}


void CDataLoader::GetPathFromIdentifier(int identifier, char *path)
{
    ModelStructureObject *mso = FindModelStructureObject(m_pModelStructureObjectTree, identifier);
    if (!mso)
    {    
		strcpy(path, "");
		return;
    }
    ModelStructureObject *opath[512];
    int i=0;
    while (1)
    {
		opath[i++] = mso;
		mso = mso->m_pParent;
		if (mso == m_pModelStructureObjectTree)
			break;
    }

    strcpy(path,"");
    for (int j=0; j<i; ++j)
    {
		strcat(path,"/");
		strcat(path, opath[i-1-j]->m_pName);
    }
}



     


ModelStructureObject * CDataLoader::FindModelStructureObject(ModelStructureObject *mso, char *path)
{
    char name[4096];
    char newpath[4096];
    strcpy(newpath, path);

    bool lastone = ExtractString(newpath,name);
     
    ModelStructureObject *found = 0;
    START_LIST_ITERATION(ModelStructureObject, mso->m_Children)
	if (strcmp(name, temp->m_pName) == 0)
	{
	    char extrapath[4096];
 	    if (!lastone)
	    {	    
		strcpy(extrapath, newpath+strlen(name)+1);
		found = FindModelStructureObject(temp, extrapath);
	    }
	    else
	     	found = temp;	    
 	    if (found)
		break;
	}
    END_LIST_ITERATION(mso->m_Children);
    return found; 
}


int CDataLoader::FilterIdentifier(int identifier, char *type)
{
    ModelStructureObject *startobject  =   FindModelStructureObject(m_pModelStructureObjectTree, identifier);
    if (!startobject)
	return identifier;
    ModelStructureObject *currentobject = startobject;
    if (strcmp(type,"") == 0)
	return identifier;
    
    while(1)
    {
	if (currentobject == m_pModelStructureObjectTree)
	    return startobject->m_Identifier;
	if (strcmp(currentobject->m_pType, type) == 0)
	    return currentobject->m_Identifier;
	if (!currentobject->m_pParent)
	    return startobject->m_Identifier;
	currentobject = currentobject->m_pParent;
    }

}
void CDataLoader::GetXMLForItemChildren(int identifier, char *(&text))
{
    ModelStructureObject *mso;
    if (identifier == -1)
	mso = m_pModelStructureObjectTree;
    else
	mso = FindModelStructureObject(m_pModelStructureObjectTree, identifier);
    GetXMLForItemChildren(mso, text);
}

void CDataLoader::GetXMLForItemChildren(char *path, char *(&text))
{
    ModelStructureObject *mso;
    if (strcmp(path,"/") != 0)
	mso = FindModelStructureObject(m_pModelStructureObjectTree, path+1);
    else
	mso = m_pModelStructureObjectTree;
    GetXMLForItemChildren(mso, text);
}



void CDataLoader::GetXMLForItemChildren(ModelStructureObject *mso, char *(&text))
{
     
    HUtilityXMLGenerator xmlgen;
    xmlgen.Reset();

    HUtilityXMLTag xmlt_toplevel;
    xmlt_toplevel.SetTagname("tree");
    xmlt_toplevel.SetOpen(true);
    xmlgen.AddTag(&xmlt_toplevel);	      
    
    START_LIST_ITERATION(ModelStructureObject, mso->m_Children)
		HUtilityXMLTag xmlt;
		xmlt.SetTagname("tree");
		char name[4096];
		char tagid[4096];
		char type[4096];
		int ident;
		strcpy(name,temp->m_pName);
		ident = temp->m_Identifier;
		strcpy(type,temp->m_pType);
 		itoa(ident, tagid,10);
		if (strcmp(name,"") == 0)		
		    xmlt.AddProperty("text", tagid, true);		
		else
		    xmlt.AddProperty("text", name, true);

		xmlt.AddProperty("userData", tagid, true);

		bool found = false;
		vlist_t *childrenlist = temp->m_Children;    
		START_LIST_ITERATION(ModelStructureObject, childrenlist)
		    found = true;
		    break;
 		END_LIST_ITERATION(childrenlist);

		if (found)
		    xmlt.AddProperty("src", "children.xml", true);

		vlist_t * typelist = GetModelStructureTypeList();
		
		START_LIST_ITERATION(ModelStructureType, typelist)
		    if (strcmp(temp->GetName(), type) == 0)
			xmlt.AddProperty("icon", temp->GetImage(), true);
		END_LIST_ITERATION(typelist);

 		xmlt.SetOpen(false);
		xmlgen.AddTag(&xmlt);	      	    	
	    END_LIST_ITERATION(mso->m_Children);
	   
	    xmlgen.CloseTag(&xmlt_toplevel);

	    char *temp = new char [xmlgen.GetBufferSize()+1];	    
	    memcpy(temp, xmlgen.GetBuffer(), xmlgen.GetBufferSize());
	    temp[xmlgen.GetBufferSize()] = 0;
	    text = temp;     
            
}

/* When this returns false, all data in the download has been processed. */
bool CDataLoader::ProcessNextChunk()
{
	vector<databuffer *>::iterator iter = m_CachedDataList.begin();
	int tempdatareceived = 0;
	/* If there is data in the list... */
	if (iter!=m_CachedDataList.end())
	{
		while (1)
		{
			tempdatareceived+=((*iter)->length);
			m_DataReceived+=((*iter)->length);
			TK_Status status = ProcessData((*iter)->data, (*iter)->length);		
			delete [] (*iter)->data;
			delete *iter;
			m_CachedDataList.erase(iter);

			switch(status){
				case TK_Normal:
				case TK_Pending:
				case TK_Complete:
					{
					}break;
				default:
					{
						iter = m_CachedDataList.begin();
						while(iter!=m_CachedDataList.end())
						{
							m_DataReceived+=((*iter)->length);	
							delete [] (*iter)->data;
							delete *iter;
							m_CachedDataList.erase(iter);
							iter = m_CachedDataList.begin();
						}
						::MessageBox(NULL, _T("ERROR! File is wrong version or corrupted."), _T("File read error"), MB_OK);
						return false;
					}break;
					
			}
			iter = m_CachedDataList.begin();
			if (iter == m_CachedDataList.end() || status == TK_Complete)
				return true;
			if (tempdatareceived > BUFFERSIZE2)
				return true;
		}
		return true;
	}

	/* If the list has no data in it AND the download is NOT in progress... */
	else if (iter==m_CachedDataList.end() && !m_bDownloadInProgress)
	{
		HC_Control_Update_By_Key (m_pView->GetViewKey(), "redraw everything");
		
		if (!m_bDataIsStreamable)
		{
			fclose(m_temphandle);
			HFileInputResult result = m_pView->GetModel()->Read(H_ASCII_TEXT(m_tempfilename));
			wchar_t error_msg[256] = {_T("")};
			wchar_t error_fmt[] = {_T("An error occured reading stream.\nThe error code was %s.")};
			switch(result){
				case InputOK:
					{
					HC_Open_Segment_By_Key(m_pView->GetModelKey());		

					HC_POINTER_SIZED_INT    value = 0;

					if (HC_Show_Existence("user value"))
						HC_Show_User_Value(&value);

					HC_Close_Segment();

					if (value == 1)
						m_pView->GetModel()->SetBRepGeometry(true);
					else if (value == 2)
						m_pView->GetModel()->SetFEAGeometry(true);
					else if (value == 3)
						m_pView->GetModel()->SetVectorGeometry(true);

					if (!m_pView->GetHasCamera())
						m_pView->FitWorld();
					
					m_pView->GetModel()->CleanIncludes();
					m_pView->Update();
					}break;
				case InputVersionMismatch:
					wsprintf(error_msg, error_fmt, _T("InputVersionMismatch"));
					break;
				case InputFail:
					wsprintf(error_msg, error_fmt, _T("InputFail"));
					break;
				case InputNotHandled:
					wsprintf(error_msg, error_fmt, _T("InputNotHandled"));
					break;
				case InputBadFileName:
					wsprintf(error_msg, error_fmt, _T("InputBadFileName"));
					break;
				case InputBadOptions:
					wsprintf(error_msg, error_fmt, _T("InputBadOptions"));
					break;
				default:
					wsprintf(error_msg, error_fmt, _T("Unknown error"));
					break;
			}

			if(result != InputOK){
				::MessageBox(NULL, error_msg, _T("ERROR!"), MB_OK);
			}
			if(sizeof(TCHAR) > 0)
				_wremove((wchar_t const *)&m_tempfilename[0]);
			else
				remove((char const *)&m_tempfilename[0]);
		}
		HC_Open_Segment_By_Key(m_pView->GetModel()->GetModelKey());		
		
		HC_POINTER_SIZED_INT    value = 0;
		
		if (HC_Show_Existence("user value"))
			HC_Show_User_Value(&value);
		
		HC_Close_Segment();
		
		if (value == 1)
			m_pView->GetModel()->SetBRepGeometry(true);
		else if (value == 2)
			m_pView->GetModel()->SetFEAGeometry(true);
		else if (value == 3)
			m_pView->GetModel()->SetVectorGeometry(true);

		if(!m_bDownloadInProgress)
			m_bDataProcessingComplete = true;

		m_pView->GetModel()->CleanIncludes();
		return false;
	}

	return true;
}


TK_Status TK_ATL_Initial_View::Interpret(BStreamFileToolkit &tk, ID_Key key, int variant)
{
	HPoint pos, tar, up;
	float fieldx=0, fieldy=0;
	char proj[16];

	m_pView->GetCamera(&pos,&tar,&up,fieldx,fieldy,proj);

	m_settings[0] = pos.x; m_settings[1] = pos.y; m_settings[2] = pos.z;
	m_settings[3] = tar.x; m_settings[4] = tar.y; m_settings[5] = tar.z;
	m_settings[6] = up.x ; m_settings[7] = up.y ; m_settings[8] = up.z;
	m_settings[9] = fieldx ; m_settings[10] = fieldy;

	if(proj[0] == 'p')
		m_projection = TKO_Camera_Perspective;
	else
		m_projection = TKO_Camera_Orthographic;

	SetView("default");

	return TK_Normal;
}


TK_Status TK_ATL_Initial_View::Execute(BStreamFileToolkit &tk) 
{
	
	TK_Status status=TK_Normal;
	
	if (m_pDataLoader->GetRestoreCamera())
	{
		HPoint pos, tar, up;
		float fieldx, fieldy;
		
		pos.Set(m_settings[0],m_settings[1],m_settings[2]);
		tar.Set(m_settings[3],m_settings[4],m_settings[5]);
		up.Set(m_settings[6],m_settings[7],m_settings[8]);
		fieldx = m_settings[9];
		fieldy = m_settings[10];
		
		char proj[16];
		
		if (m_projection == TKO_Camera_Perspective)
			strcpy(proj,"p");
		else if (m_projection == TKO_Camera_Orthographic)
			strcpy(proj,"o");
		else
			strcpy(proj,"s");
		
		if (!strcmp(GetView(),"default"))
		{
			m_pView->SetInitialCamera(pos,tar,up,fieldx,fieldy,proj);
			m_pView->SetCamera(pos,tar,up,fieldx,fieldy,proj);
			
			m_pView->CameraPositionChanged();
		}
	}
	else
		m_pDataLoader->SetRestoreCamera(true);

	m_pView->SetHasCamera(true);

	return (status);
}

#include "Hoops3dStreamCtrl.h"
static DWORD WINAPI  XMLParsingThread(LPVOID pParam)
{
    XML_Parsing_Object *pob = (XML_Parsing_Object *)pParam;
#ifdef SAVE_XML
    FILE *fp;
    fp=fopen("c:\\modelstructure.xml", "w");
    fwrite(buffer, 1, strlen(buffer), fp);
    fclose(fp);
#endif
    HUtilityXMLParser xp;
    pob->m_pDataLoader->GetView()->GetModel()->GetDispatchXML()->StopIteration();	    
    xp.SetupParseBuffer(pob->buffer);
    xp.SetTagCallback("Type", TK_ModelStructure_XML::XMLCallback, pob);
    xp.SetTagCallback("Object", TK_ModelStructure_XML::XMLCallback, pob);
    xp.SetTagCallback("ModelStructure", TK_ModelStructure_XML::XMLCallback, pob);
    xp.SetTagCallback("Hierachy", TK_ModelStructure_XML::XMLCallback, pob);
    xp.SetTagCallback("IdentifierList", TK_ModelStructure_XML::XMLCallback, pob);
    
    pob->m_TempObjects = new_vlist(malloc,free);
    pob->m_pXmlgen = new HUtilityXMLGenerator;
    pob->m_pXmlgen->Reset();
    
    xp.ProcessXMLData();
    char *temp = new char [pob->m_pXmlgen->GetBufferSize()+1];	    
    memcpy(temp, pob->m_pXmlgen->GetBuffer(), pob->m_pXmlgen->GetBufferSize());
    temp[pob->m_pXmlgen->GetBufferSize()] = 0;
    pob->m_pDataLoader->SetTreeControlXML(temp);
    delete [] temp;
    delete pob->m_pXmlgen;
    delete_vlist(pob->m_TempObjects);
    SendMessage(pob->m_pDataLoader->GetControl()->m_hWnd, WM_XML_PARSING_COMPLETE,0,0);
    
    delete [] pob->buffer;
    delete pob;
     return 0;
}



TK_Status   TK_ModelStructure_XML::Execute (BStreamFileToolkit & tk) 
{
    
	char *buffer = new char[GetSize() + 1];
	memcpy(buffer, GetXML(), GetSize());
	buffer[GetSize()] = 0;
	
#ifdef SAVE_XML
	FILE *fp;
	fp=fopen("c:\\modelstructure.xml", "w");
	fwrite(buffer, 1, strlen(buffer), fp);
	fclose(fp);
#endif
	//	xp.FindDocType(doctype, buffer);
	if (strstr(buffer,"<ModelStructure") != 0)
	{
 	    XML_Parsing_Object *pob = new XML_Parsing_Object();
	    pob->m_pDataLoader = m_pDataLoader;
	    pob->buffer = buffer;	    
 	    CreateThread(0,0,XMLParsingThread, pob,  0, & m_pDataLoader->m_ParsingThread);
	    ::SetThreadPriority((HANDLE) m_pDataLoader->m_ParsingThread, THREAD_PRIORITY_LOWEST);
	}
	else
	    delete [] buffer;


    return TK_Normal;
}

void *TK_ModelStructure_XML::XMLCallback(HUtilityXMLTag *xt, bool open, void *m_pExtraData)
{

   
	XML_Parsing_Object *msxml = (XML_Parsing_Object *)m_pExtraData;
	HUtilityXMLGenerator * xmlgen = msxml->m_pXmlgen;

	if (!open)
	{
	    if (strcmp(xt->GetTagname(), "Object") == 0 || strcmp(xt->GetTagname(), "Hierachy") == 0)
	    {	    
		HUtilityXMLTag * xmlt = (HUtilityXMLTag *)vlist_remove_first(msxml->m_TempObjects);
		xmlgen->CloseTag(xmlt);
		delete xmlt;
	    }
	    return 0;
	}
	    
 	if (strcmp(xt->GetTagname(), "Hierachy") == 0)
	{
		HUtilityXMLTag *xmlt = new HUtilityXMLTag;
		xmlt->SetTagname("tree");
		xmlt->SetOpen(true);
		xmlgen->AddTag(xmlt);	      
		vlist_add_first(msxml->m_TempObjects, xmlt);
	}
 	if (strcmp(xt->GetTagname(), "IdentifierList") == 0)
	{
	    ModelStructureObject *msobject = (ModelStructureObject *)xt->GetXMLParser()->GetStackData();
	    xt->StartListItemsQuery();
	    msobject->m_IdentifierList = new_vlist(malloc,free);
	    while(1)
	    {	    
		char *litem;
		if (!xt->GetNextListItem(&litem))
			break;
		char *newitem = new char[strlen(litem)+1];
		strcpy(newitem, litem);
		vlist_add_last(msobject->m_IdentifierList, newitem);
	    }
			
	}

 	if (strcmp(xt->GetTagname(), "Object") == 0)
	{
		HUtilityXMLTag *xmlt = new HUtilityXMLTag;
		xmlt->SetTagname("tree");
		char name[4096];
		char tagid[4096];
		char type[4096];
		int ident;
		xt->GetProperty("Name", name);
		xt->GetProperty("Identifier", ident);
		xt->GetProperty("Type", type);
		itoa(ident, tagid,10);
		if (strcmp(name,"") == 0)		
		    xmlt->AddProperty("text", tagid, true);		
		else
		    xmlt->AddProperty("text", name, true);

		xmlt->AddProperty("userData", tagid, true);

		vlist_t * typelist = msxml->m_pDataLoader->GetModelStructureTypeList();

		ModelStructureType *objecttype = 0;
		START_LIST_ITERATION(ModelStructureType, typelist)
		    if (strcmp(temp->GetName(), type) == 0)
		    {		    
			xmlt->AddProperty("icon", temp->GetImage(), true);
			objecttype = temp;
		    }
		END_LIST_ITERATION(typelist);

 		xmlt->SetOpen(true);

	    

		xmlgen->AddTag(xmlt);	      
		vlist_add_first(msxml->m_TempObjects, xmlt);

		ModelStructureObject *msobject = (ModelStructureObject *)xt->GetXMLParser()->GetStackData();
		   
		if (!msobject)
		    msobject = msxml->m_pDataLoader->GetModelStructureObjectTree();
		ModelStructureObject *newmsobject = new ModelStructureObject;
		newmsobject->SetType(type);
		newmsobject->SetIdentifier(ident);
		newmsobject->SetParent(msobject);
		newmsobject->SetName(name);
		newmsobject->SetType(objecttype);
		msobject->AddChild(newmsobject); 
		return newmsobject;
	    
	}
	
 	if (strcmp(xt->GetTagname(), "Type") == 0)
	{

		ModelStructureType *mst = new ModelStructureType;
	
 		char name[4096];
		char image[4096];
		int selectable;
 		xt->GetProperty("Name", name);
		xt->GetProperty("Image", image);
		xt->GetProperty("Selectable", selectable);

		mst->SetName(name);
		mst->SetImage(image);
		mst->SetSelectable(BOOL2bool(selectable));
		vlist_t * typelist = msxml->m_pDataLoader->GetModelStructureTypeList();
		vlist_add_last(typelist, mst);
		
 	    
	}
	return 0;

}


ModelStructureObject::ModelStructureObject()
{
	m_pType = 0;
	m_pTypePointer = 0;
	m_pParent = 0;
	m_pName = 0;
 	m_Children = new_vlist(malloc, free);
 	m_IdentifierList = 0;
 	
}

ModelStructureObject::~ModelStructureObject()
{
	delete [] m_pType;
	delete [] m_pName;
        START_LIST_ITERATION(ModelStructureObject, m_Children)
		delete temp;
	END_LIST_ITERATION(m_Children);
	delete_vlist(m_Children);

	if (m_IdentifierList)
	{
	    START_LIST_ITERATION(char, m_IdentifierList)
		delete [] temp;
	    END_LIST_ITERATION(m_IdentifierList);
	    delete_vlist(m_IdentifierList);
	}
	
}


void ModelStructureObject::AddChild(ModelStructureObject *child)
{ 
    vlist_add_last(m_Children, child); 
}



void ModelStructureObject::Select(HBaseView *view)
{
    if (GetTypePointer() && GetTypePointer()->GetSelectable())
    {
	if (m_Identifier != -1 || m_IdentifierList)
	{		
	    if (m_Identifier != -1)
	    {		    
		HC_KEY sel_key;
		if (view->GetModel()->GetStreamFileTK()->IndexToKey(m_Identifier, sel_key) != TK_NotFound)
		{
		    if (sel_key != -1)
		    {	    
			
			HMySelectionSet* sel_set = (HMySelectionSet *)view->GetSelection();
		 	sel_set->SelectDirect(sel_key,0,0);
		    }		    
		}
	    }
	    else
	    {
		vlist_t *childrenlist = m_IdentifierList;	
		//HSelectionSet* sel_set = (HSelectionSet *)view->GetSelection();
 		START_LIST_ITERATION(char, childrenlist)
		    HC_KEY sel_key;
		
		int identifier = atoi(temp);
		if (view->GetModel()->GetStreamFileTK()->IndexToKey(identifier, sel_key) != TK_NotFound)
		{
		    if (sel_key != -1)
		    {	    
			
			HMySelectionSet* sel_set = (HMySelectionSet *)view->GetSelection();
			sel_set->SelectDirect(sel_key,0,0);
		    }
		    
		}
		END_LIST_ITERATION(childrenlist);			
		
	    }
	    
	    
	    
	}
    }
}
static int xxx = 0;
void ModelStructureObject::SelectAllChildItemsRecursive(HBaseView *view)
{
 	Select(view);
  	START_LIST_ITERATION(ModelStructureObject, m_Children)
	    temp->SelectAllChildItemsRecursive(view);
 	END_LIST_ITERATION(m_Children);			
}
		    

     

 