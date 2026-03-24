#if !defined(AFX_EDITLIGHTSDLG_H__D724FA41_626A_436B_9153_017EE83012EF__INCLUDED_)
#define AFX_EDITLIGHTSDLG_H__D724FA41_626A_436B_9153_017EE83012EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditLightsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditLightsDlg dialog
class HSolidView;

class CEditLightsDlg : public CDialog
{
// Construction
public:
	CEditLightsDlg(HBaseView* pHSolidView, CWnd* pParent = NULL);   // standard constructor

	static void RepositionLights( HBaseView* pBaseView );


// Dialog Data
	//{{AFX_DATA(CEditLightsDlg)
	enum { IDD = IDD_EDIT_LIGHTS };
	CComboBox	m_LightsCombo;
	int		m_LightStatus;
	BOOL	m_bFollowCamera;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditLightsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HBaseView* m_pHView;

	// Generated message map functions
	//{{AFX_MSG(CEditLightsDlg)
	afx_msg void OnButtonLightColor();
	afx_msg void OnButtonAddLight();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRemoveLight();
	afx_msg void OnEditlightsOn();
	afx_msg void OnEditlightsOff();
	afx_msg void OnSelchangeComboLightNames();
	afx_msg void OnLightFollowCamera();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void get_default_color(char* retColorStr);
	void get_default_visibility(char* retVisibilityStr);
	void get_new_name(char* retNewName);
	void switch_light(bool bIsOn);
	void update_switch();
	void update_follow_camera_ctrl();
	int insert_light_in_combo( HC_KEY lightSegmentKey, char* lightName = NULL );

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLIGHTSDLG_H__D724FA41_626A_436B_9153_017EE83012EF__INCLUDED_)
