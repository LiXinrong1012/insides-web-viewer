// CMultiModelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"

#include "CMultiModelDlg.h"

// CMultiModelDlg dialog

IMPLEMENT_DYNAMIC(CMultiModelDlg, CDialog)

CMultiModelDlg::CMultiModelDlg(CWnd * pParent, char const * in_container, int in_num_configs, char const ** in_configs)
	: CDialog(CMultiModelDlg::IDD, pParent)
{
	m_container = in_container;
	m_num_configs = in_num_configs;
	m_configs = in_configs;
	m_config_selection = -1;

	m_wchar_strings = new wchar_t * [m_num_configs + 1];
}

CMultiModelDlg::~CMultiModelDlg()
{
	for (int i = 0; i < m_num_configs + 1; i++)
		delete [] m_wchar_strings[i];

	delete [] m_wchar_strings;
}

BOOL CMultiModelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	H_UTF8 utf8;
	utf8.encodedText(m_container);
	H_WCS wcs(utf8);

	m_wchar_strings[0] = new wchar_t [wcslen(wcs.encodedText()) + 1];
	wcscpy(m_wchar_strings[0], wcs.encodedText());

	TVINSERTSTRUCT is;
	is.hParent = TVI_ROOT;
	is.hInsertAfter = TVI_LAST;
	is.item.mask = TVIF_TEXT;
	is.item.pszText = m_wchar_strings[0];
	HTREEITEM parent = MultiModelTree.InsertItem(&is);
	MultiModelTree.SetItemData(parent, (DWORD)-1);

	for (int i = 0; i < m_num_configs; i++)
	{
		H_UTF8 utf8;
		utf8.encodedText(m_configs[i]);
		H_WCS wcs(utf8);

		m_wchar_strings[i + 1] = new wchar_t [wcslen(wcs.encodedText()) + 1];
		wcscpy(m_wchar_strings[i + 1], wcs.encodedText());

		TVINSERTSTRUCT is;
		is.hParent = parent;
		is.hInsertAfter = TVI_LAST;
		is.item.mask = TVIF_TEXT;
		is.item.pszText = m_wchar_strings[i + 1];
		HTREEITEM item = MultiModelTree.InsertItem(&is);
		MultiModelTree.SetItemImage(item, 0, 0);
		MultiModelTree.SetItemData(item, (DWORD)i);
	}

	MultiModelTree.Expand(parent, TVE_EXPAND);
	MultiModelTree.GetSelectedItem();
	return 0;
}

void CMultiModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MULTIMODELTREE, MultiModelTree);
}


BEGIN_MESSAGE_MAP(CMultiModelDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CMultiModelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMultiModelDlg message handlers

void CMultiModelDlg::OnBnClickedOk()
{
	HTREEITEM item = MultiModelTree.GetSelectedItem();
	if (item)
		m_config_selection = (int)MultiModelTree.GetItemData(item);

	OnOK();
}
