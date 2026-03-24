
#pragma once

#include "Resource.h"
#include <list>
#include <string>

class HMarkupManager;

class PresetViewEditDlg : public CDialog
{
	DECLARE_DYNAMIC(PresetViewEditDlg)
	CString m_view;

public:
	PresetViewEditDlg(HMarkupManager * markup, CWnd* pParent = NULL);
	virtual ~PresetViewEditDlg();


	enum { IDD = IDD_VIEWSEDITDLG };
	afx_msg void OnApply();
	afx_msg void OnDelete();
	afx_msg void OnCbnSelchangeViewcombo();
	CString getViewName() const {return m_view;};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	CComboBox m_viewCombo;
	CStatic m_img;
	HMarkupManager * m_markup;
	std::list<std::string> m_delete;

	DECLARE_MESSAGE_MAP()
};

class PresetViewNameDlg : public CDialog
{
	DECLARE_DYNAMIC(PresetViewNameDlg)

public:
	PresetViewNameDlg(CWnd* pParent = NULL);
	virtual ~PresetViewNameDlg();

	enum { IDD = IDD_VIEWSNAMEDLG };

	CString getViewName() {return m_name;};
	afx_msg void OnOK();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	CEdit m_edit;
	CString m_name;
	DECLARE_MESSAGE_MAP()
};
