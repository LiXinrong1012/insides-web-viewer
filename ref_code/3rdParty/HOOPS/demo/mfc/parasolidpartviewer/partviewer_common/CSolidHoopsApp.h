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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CSolidHoopsApp.h,v 1.75 2010-05-12 18:07:39 nathan Exp $
//

// CSolidHoopsApp.h : interface of the CSolidHoopsApp class, derived from CHoopsApp
// This is the main header for the application

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifndef solidhoops_app
#define solidhoops_app

#include "hc.h"
#include "CHoopsApp.h"
class HDB;
class HOptionsDlg;
#ifdef HOOPS_LEAD_TOOLS
class HIOUtilityLeadTools;
#endif
#ifdef HOOPS_DWG_IO
class HIOUtilityDWG;
#endif

#ifdef HOOPS_IV_IO
class HIOUtilityIV;
#endif

class CCommandLineOutputDlg;
class CSolidHoopsView;

/////////////////////////////////////////////////////////////////////////////
// CSolidHoopsApp:
// See CSolidHoopsApp.cpp for the implementation of this class
//

class CSolidHoopsApp : public CHoopsApp
{

private:
	bool	m_bConstantSpin;
	bool	m_bShuttingDown;
	BOOL	m_bSelectionFadeWasEnabled;

	CCommandLineOutputDlg *		m_pCmdLineDlg;
	H_WCS *						m_pCmdLineOutputFile;
	bool						m_bSavedHsfStreaming;

protected:

#ifdef HOOPS_LEAD_TOOLS
	HIOUtilityLeadTools* m_pIOUtilityLeadTools;
#endif
#ifdef HOOPS_DWG_IO
	HIOUtilityDWG* m_pIOUtilityDwg;
#endif

#ifdef HOOPS_IV_IO
	HIOUtilityIV* m_pIOUtilityIV;
#endif

	HOptionsDlg * m_opt_dlg;

public:
	void ReadSettingsFromRegistry();
	void WriteSettingsToRegistry();
	void CommitAllOptions();
	void RefreshAllOptions();
	void ImportOptions(CString const & fname);
	void ExportOptions(CString const & fname);
	void LoadFileOptions(CString const & fname);

	CSolidHoopsApp();
	~CSolidHoopsApp();
 	
	
	bool GetConstantSpin(){ return m_bConstantSpin; };
	bool ShuttingDown() {return m_bShuttingDown;};

	void    LoadUrl (CString & url);

	static void CreateAllFileTypesString(CString * filters, const char * file_types); 
	static void ProcessFilters(CString * filters, const char * file_types); 
	char m_AppDirectory[MVO_BUFFER_SIZE];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSolidHoopsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	#ifdef HOOPS_QA
	#ifndef _DEBUG
	virtual int Run();
	#endif
	#endif
	//}}AFX_VIRTUAL

	void CompleteCommandLineProcessing ( CSolidHoopsView * view );

// Implementation

	//{{AFX_MSG(CSolidHoopsApp)
	afx_msg void OnAppAbout();
	afx_msg void OnDDBAbout();
	afx_msg void OnVisitHoops3d();
	afx_msg void OnLoadHelp();
	afx_msg void OnConstantspin();
	afx_msg void OnUpdateConstantspin(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnToolsOptions();
	afx_msg void OnFilePrintOptions();
	afx_msg void OnPerformanceDefault();
	afx_msg void OnUpdatePerformanceDefault(CCmdUI *pCmdUI);
	afx_msg void OnPerformanceHigh();
	afx_msg void OnUpdatePerformanceHigh(CCmdUI *pCmdUI);
	afx_msg void OnPerformanceStaticModel();
	afx_msg void OnUpdatePerformanceStaticModel(CCmdUI *pCmdUI);
	afx_msg void OnPerformanceSegmentDisplayLists();
	afx_msg void OnUpdatePerformanceSegmentDisplayLists(CCmdUI *pCmdUI);
	afx_msg void OnPerformanceGeometryDisplayLists();
	afx_msg void OnUpdatePerformanceGeometryDisplayLists(CCmdUI *pCmdUI);
	afx_msg void OnPerformanceFixedFramerate();
	afx_msg void OnUpdatePerformanceFixedFramerate(CCmdUI *pCmdUI);
	afx_msg void OnPerformanceTargetFramerate();
	afx_msg void OnUpdatePerformanceTargetFramerate(CCmdUI *pCmdUI);
	afx_msg void OnEffectsNone();
	afx_msg void OnUpdateEffectsNone(CCmdUI *pCmdUI);
	afx_msg void OnEffectsFancy();
	afx_msg void OnUpdateEffectsFancy(CCmdUI *pCmdUI);
	afx_msg void OnEffectsAmbientOcclusion();
	afx_msg void OnUpdateEffectsAmbientOcclusion(CCmdUI *pCmdUI);
	afx_msg void OnEffectsBloom();
	afx_msg void OnUpdateEffectsBloom(CCmdUI *pCmdUI);
	afx_msg void OnEffectsFastSilhouetteEdges();
	afx_msg void OnUpdateEffectsFastSilhouetteEdges(CCmdUI *pCmdUI);
	afx_msg void OnEffectsReflectionPlane();
	afx_msg void OnUpdateEffectsReflectionPlane(CCmdUI *pCmdUI);
	afx_msg void OnEffectsShadowMaps();
	afx_msg void OnUpdateShadowMaps(CCmdUI *pCmdUI);
	afx_msg void OnEffectsSimpleShadows();
	afx_msg void OnUpdateEffectsSimpleShadows(CCmdUI *pCmdUI);

	//}}AFX_MSG
#ifdef PARASOLID
	afx_msg void OnVisitParasolid();
#endif // PARASOLID
#ifdef ACIS
	afx_msg void OnVisitSpatial();
#endif // ACIS
#ifdef GRANITE
	afx_msg void OnVisitPtc();
#endif // GRANITE


	DECLARE_MESSAGE_MAP()
};

#endif
