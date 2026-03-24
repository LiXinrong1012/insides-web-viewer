#pragma once



#include "resource.h"
#include "afxcmn.h"

// CMultiModelDlg dialog

class MultiModel;
class CMultiModelDlg : public CDialog
{
	DECLARE_DYNAMIC(CMultiModelDlg)

public:
	CMultiModelDlg(CWnd* pParent = NULL, char const * in_container = 0, int in_num_configs = 0, char const ** in_configs = 0);
	virtual ~CMultiModelDlg();

// Dialog Data
	enum { IDD = IDD_MULTIMODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	
	char const *	m_container;
	int				m_num_configs;
	char const **	m_configs;
	int				m_config_selection;
	wchar_t **		m_wchar_strings;
 
	DECLARE_MESSAGE_MAP()
public:
	int GetConfigSelection () { return m_config_selection; };

	CTreeCtrl MultiModelTree;
	afx_msg void OnBnClickedOk();
};
