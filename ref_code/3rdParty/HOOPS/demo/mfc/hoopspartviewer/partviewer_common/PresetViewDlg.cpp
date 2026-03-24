
#include "stdafx.h"
#include "HMarkupManager.h"
#include "string.h"
#include "utf_utils.h"
#include "PresetViewDlg.h"

IMPLEMENT_DYNAMIC(PresetViewEditDlg, CDialog)

PresetViewEditDlg::PresetViewEditDlg(HMarkupManager * markup, CWnd* pParent)
	: CDialog(PresetViewEditDlg::IDD, pParent), m_markup(markup)
{
}

PresetViewEditDlg::~PresetViewEditDlg()
{
}

static
H_FORMAT_TEXT GetCurrentSelection(CComboBox const & cb)
{
	TCHAR buffer[MVO_BUFFER_SIZE] = {_T("trash")};
	int cs = cb.GetCurSel();
	if(cs == -1)
		return "";
	cb.GetLBText(cs, buffer);
	return H_FORMAT_TEXT(H_ASCII_TEXT(buffer));
}

#define	GDI_RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define	GDI_RGBA(r,g,b,a) ((COLORREF) (r & 0xff) | ((g & 0xff) << 8) | ((b & 0xff) << 16) | ((a & 0xff) << 24) )

static
HBITMAP GetBmp(HMarkupManager * m, char const * layer)
{
	HDC hDC = GetDC (NULL);
	HDC hDCMem = CreateCompatibleDC (hDC);
	HBITMAP hBitmap;

	unsigned char const * image_data = 0;
	int x = 255, y = 255;
	bool exists = m->GetPreviewImage(layer, &x, &y, 0, &image_data);

	hBitmap = CreateCompatibleBitmap (hDC, x, y);
	SelectObject(hDCMem, hBitmap);

	if(exists){
		for(int row = 0; row < y; ++row){
			for(int col = 0; col < x; ++col){
				unsigned char r;
				unsigned char g;
				unsigned char b;
				unsigned char a = 0; 
				r = *image_data++;
				g = *image_data++;
				b = *image_data++;
				image_data++;
				SetPixel(hDCMem, col, row, GDI_RGBA(r, g, b, a));
			}
		}
	}

	DeleteDC (hDCMem);
	DeleteDC (hDC);
	return hBitmap;
}

BOOL PresetViewEditDlg::OnInitDialog()
{
	UpdateData(FALSE);
	char * allviews = strdup(m_markup->GetLayerNames());
	char const * tok = strtok(allviews, ";");
	for(; tok; tok = strtok(0, ";")){
		m_viewCombo.AddString(H_TEXT(tok));
	}
	free(allviews);
	m_viewCombo.SetCurSel(0);
	HBITMAP bmp = GetBmp(m_markup, GetCurrentSelection(m_viewCombo));
	m_img.SetBitmap(bmp);
	return TRUE;
}


void PresetViewEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIEWCOMBO, m_viewCombo);
	DDX_Control(pDX, IDC_VIEWIMG, m_img);
}


BEGIN_MESSAGE_MAP(PresetViewEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, &PresetViewEditDlg::OnApply)
	ON_BN_CLICKED(IDC_DELETEVIEW, &PresetViewEditDlg::OnDelete)
	ON_CBN_SELCHANGE(IDC_VIEWCOMBO, &PresetViewEditDlg::OnCbnSelchangeViewcombo)
END_MESSAGE_MAP()


void PresetViewEditDlg::OnApply()
{
	std::list<std::string>::iterator iter = m_delete.begin();
	std::list<std::string>::const_iterator const end = m_delete.end();
	for(; iter != end; ++iter){
		m_markup->DeleteLayer(iter->c_str());
	}
	m_view = GetCurrentSelection(m_viewCombo);
	PresetViewEditDlg::OnOK();
}

void PresetViewEditDlg::OnDelete()
{
	H_FORMAT_TEXT v = GetCurrentSelection(m_viewCombo);
	if(strlen(v) > 0){
		m_delete.push_back((char*)v);
		int sel = m_viewCombo.GetCurSel();
		m_viewCombo.DeleteString(sel);
		int max = m_viewCombo.GetCount();
		m_viewCombo.SetCurSel(sel < max ? sel : max -1);
		OnCbnSelchangeViewcombo();
	}
}
void PresetViewEditDlg::OnCbnSelchangeViewcombo()
{
	HBITMAP bmp = GetBmp(m_markup, GetCurrentSelection(m_viewCombo));
	m_img.SetBitmap(bmp);
}



IMPLEMENT_DYNAMIC(PresetViewNameDlg, CDialog)

PresetViewNameDlg::PresetViewNameDlg(CWnd* pParent)
	: CDialog(PresetViewNameDlg::IDD, pParent)
{

}

PresetViewNameDlg::~PresetViewNameDlg()
{
}

BEGIN_MESSAGE_MAP(PresetViewNameDlg, CDialog)
	ON_BN_CLICKED(IDOK, &PresetViewNameDlg::OnOK)
END_MESSAGE_MAP()

void PresetViewNameDlg::OnOK()
{
	m_edit.GetWindowText(m_name);
	CDialog::OnOK();
}

BOOL PresetViewNameDlg::OnInitDialog()
{
	UpdateData(FALSE);
	return TRUE;
}

void PresetViewNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIEWNAME, m_edit);
}
