
#if !defined(_HUIUTILITYMFC_H__20011029__1611__)
#define _HUIUTILITYMFC_H__20011029__1611__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// HOptionsDlg.h : header file
#include <afxtempl.h>
#include "resource.h"

class HOptionsPage : public CDialog  
{
public:
	DECLARE_DYNCREATE(HOptionsPage)

	HOptionsPage();
	HOptionsPage(UINT nID, CWnd *pParent = NULL);
	virtual ~HOptionsPage();

   UINT GetID()      {return m_id;}
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	virtual void OnButtonReset();
	virtual void OnButtonApply();
	virtual void OnCancel();

   DECLARE_MESSAGE_MAP()
   UINT     m_id;
};

class pageStruct
{
   public:
   HOptionsPage *pDlg;
   UINT id;
   HOptionsPage *pDlgParent;
   CString csCaption;
};

#define WM_CHANGE_PAGE (WM_APP + 100)

/////////////////////////////////////////////////////////////////////////////
// HOptionsDlg dialog

class HOptionsDlg : public CDialog
{
// Construction
public:
	HOptionsDlg(CWnd* pParent = NULL);   // standard constructor
   ~HOptionsDlg();

// Dialog Data
	//{{AFX_DATA(HOptionsDlg)
	enum { IDD = IDD_HOPTIONSDLG };
	CStatic	m_boundingFrame;
	//}}AFX_DATA

   // dialog title
   void SetTitle(CString t)   {m_csTitle = t;}

   // used in the pretty shaded static control
   void SetConstantText(CString t)   {m_csConstantText = t;}

   // add a page (page, page title, optional parent)
   bool AddPage(HOptionsPage &page, const char *pCaption, HOptionsPage *pDlgParent = NULL);

   //get a handle to a page
   HOptionsPage * GetPage(int iPage);

   int GetPageCount();

   // show a page
   bool ShowPage(int iPage);

   bool ShowPage(HOptionsPage * pPage);

   // end the dialog with a special return code
   void EndSpecial(UINT res, bool bOk = true);
	
	// set the first page
	void SetStartPage(HOptionsPage *pPage = NULL) {m_pStartPage = pPage;}


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HOptionsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
   
   bool EndOK();

	CStatic		m_captionBar;
	CTreeCtrl	m_pageTree;

   // check to see if this dlg has already been added to the tree
   HTREEITEM FindHTREEItemForDlg(HOptionsPage *pParent);

	// Generated message map functions
	//{{AFX_MSG(HOptionsDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangedPageTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfoPageTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPhelp();
	afx_msg void OnResetAll();
	//}}AFX_MSG
	afx_msg LRESULT OnChangePage(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

   CPtrArray   m_pages;
   int         m_iCurPage;
   CRect       m_frameRect;
   CString     m_csTitle, m_csConstantText;

	HOptionsPage	*m_pStartPage;

   // store info about *pDlgs that have been added to 
   // the tree - used for quick lookup of parent nodes
   // DWORDs are used because HTREEITEMs can't be... blame Microsoft
   CMap< HOptionsPage *, HOptionsPage *, DWORD, DWORD&  > m_dlgMap;

};

// In order to ease use, these values have been hard coded in colorbtn.rc
// This avoids the need for another header file.
#define IDD_COLORBTN                    (5100)
#define IDC_COLOR1                      (5101)
#define IDC_COLOR20                     (5120)
#define IDC_OTHER                       (5121)


/////////////////////////////////////////////////////////////////////////////
// CColorBtnDlg dialog

class CColorBtnDlg : public CDialog
{
// Construction
public:

	
	static COLORREF colors[20];
    static BYTE used[20];

    CButton *parent;
    int colorindex;
    bool m_bUndefine;

	CColorBtnDlg(CWnd* pParent = NULL);   // standard constructor

     
// Dialog Data
	//{{AFX_DATA(CColorBtnDlg)
	enum { IDD = IDD_COLORBTN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorBtnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CColorBtnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnOther();
	afx_msg void OnUndefine();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	void OnColor(UINT id);    
    void EndDialog( int nResult );

	DECLARE_MESSAGE_MAP()

};

class CStyleDialog;
class ClashDlg;


/////////////////////////////////////////////////////////////////////////////
// CColorBtn dialog

class CColorBtn : public CButton
{
// Construction
public:

    CColorBtn();

    void SetParentDialog(CStyleDialog *dialog) { m_pStyleDialog = dialog; }
    void SetParentClashDialog(ClashDlg *dialog) { m_pClashDialog = dialog; }
    CStyleDialog *m_pStyleDialog;
    ClashDlg *m_pClashDialog;
    // The selected color,set this variable to initialize the 
    // button's color and read to see the results

    COLORREF currentcolor;

    // Use Serialize to store the color table in a file. Call at the document's Serialize()
    
	void Serialize( CArchive& ar );

    // If using Serialize, call Reset to reinitialize the color table at OnNewDocument()

	static void Reset();

    // Use Load and Store to save/restore the color table to/from the registry

	static BOOL Load();
    static BOOL Store();
	  


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorBtn)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorBtn();



	// Generated message map functions
protected:
	//{{AFX_MSG(CColorBtn)
	afx_msg void OnClicked();
	//}}AFX_MSG

    void DrawItem(LPDRAWITEMSTRUCT);

	DECLARE_MESSAGE_MAP()

private:

    // A number of pens and brushes needed to paint the button

    CPen *oldpen;
    CBrush *oldbrush;
    CPen blackpen;
    CPen dkgray;
    CPen whitepen;
    CBrush backbrush;
    CBrush nullbrush;
    CPen nullpen;
    


   CColorBtnDlg dlg;
};


// PathDialog.h : header file
//

class CPathDialog;

// CPathDialogSub - intercepts messages from child controls
class CPathDialogSub : public CWnd
{
	friend CPathDialog;
public:
	CPathDialog* m_pPathDialog;
protected:
    afx_msg void OnOK();              // OK button clicked
	afx_msg void OnChangeEditPath();
    DECLARE_MESSAGE_MAP()
private:
};

/////////////////////////////////////////////////////////////////////////////
// CPathDialog dialog

class CPathDialog
{
	friend CPathDialogSub;
// Construction
public:
	CPathDialog(LPCTSTR lpszCaption=NULL,
		LPCTSTR lpszTitle=NULL,
		LPCTSTR lpszInitialPath=NULL, 
		CWnd* pParent = NULL);

	CString GetPathName();
	virtual int DoModal();

	static int Touch(LPCTSTR lpPath, BOOL bValidate=TRUE);
	static int MakeSurePathExists(LPCTSTR lpPath);
	static BOOL IsFileNameValid(LPCTSTR lpFileName);
	static int ConcatPath(LPTSTR lpRoot, LPCTSTR lpMorePath);

private:
	static int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam, LPARAM pData);

	LPCTSTR m_lpszCaption;
	LPCTSTR m_lpszInitialPath;

	TCHAR m_szPathName[MAX_PATH];

	BROWSEINFO m_bi;
	HWND m_hWnd;
	CWnd*	m_pParentWnd;
	BOOL m_bParentDisabled;
	BOOL m_bGetSuccess;

	CPathDialogSub m_PathDialogSub;

};



/////////////////////////////////////////////////////////////////////////////
// CDockingDialogBar window

class CDockingDialogBar : public CControlBar
{
	const COLORREF	m_clrBtnHilight;
	const COLORREF	m_clrBtnShadow;

	// Construction / destruction
public:
    CDockingDialogBar();

// Attributes
public:
    BOOL IsHorz() const;
	void ChangeDialog(CDialog *pDialog, UINT nID);

// Operations
public:

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDockingDialogBar)
    public:
    virtual BOOL Create(CWnd* pParentWnd, CDialog *pDialog, CString &pTitle, UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_LEFT);
    virtual CSize CalcFixedLayout( BOOL bStretch, BOOL bHorz );
    virtual CSize CalcDynamicLayout( int nLength, DWORD dwMode );
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CDockingDialogBar();
    void StartTracking();
    void StopTracking(BOOL bAccept);
    void OnInvertTracker(const CRect& rect);
    
    // implementation helpers
    CPoint& ClientToWnd(CPoint& point);

protected:
	void		DrawGripper(CDC &dc);

    CSize       m_sizeMin;
    CSize       m_sizeHorz;
    CSize       m_sizeVert;
    CSize       m_sizeFloat;
    CRect       m_rectBorder;
    CRect       m_rectTracker;
    UINT        m_nDockBarID;
    CPoint      m_ptOld;
    BOOL        m_bTracking;
    BOOL        m_bInRecalcNC;
    int         m_cxEdge;
	CRect		m_rectUndock;
	CRect		m_rectClose;
	CRect		m_rectGripper;
	int			m_cxGripper;
	int			m_cxBorder;
	CDialog*	m_cDialog;
    CBrush		m_brushBkgd;

	// Rob Wolpov 10/15/98 Added support for diagonal resizing
	int  m_cyBorder;
	int  m_cMinWidth;
	int  m_cMinHeight;
	int  m_cCaptionSize;

// Generated message map functions
protected:
   //{{AFX_MSG(CDockingDialogBar)
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
    afx_msg void OnNcPaint();
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
#if (_MSC_VER < 1400)
    afx_msg UINT OnNcHitTest(CPoint point);
#else
	afx_msg LRESULT OnNcHitTest(CPoint point);
#endif
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnCaptureChanged(CWnd *pWnd);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};




class wcSliderPopup : public CWnd
{
// Construction
public:
    wcSliderPopup			( void );
    wcSliderPopup			( CPoint p, int Pos, int nMin, int nMax, CWnd* pParentWnd );
                 
// Operations
public:
    BOOL	Create				( CPoint p, int Pos, int nMin, int nMax, CWnd* pParentWnd );
	void	SetPos				( int Pos, BOOL bInvalidate = TRUE );
	int		GetPos				( void )				{ return m_Pos; };
	void	SetRange			( int nMin, int nMax )	{ m_Min = nMin; m_Max = nMax; };
	void	SetDelta			( int Dlt )				{ m_Delta = Dlt; };

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(wcSliderPopup)
    //}}AFX_VIRTUAL

protected:
    void	PositionChange		( void );
    void	EndSliderPopup		( int nMessage );
	void	DrawTriAt			( int Pos, BOOL Clear, BOOL DrawTrack = FALSE );
	int		GetTriPos			( int Pos );
	int		TriToPos			( void );

// protected attributes
protected:
    CRect          m_WindowRect;
    CWnd*          m_pParent;
	int			   m_Pos;
	int			   m_OldPos;
	int			   m_TriPos;

	int			   m_Min;
	int			   m_Max;
	int			   m_Delta;

    // Generated message map functions
protected:
    //{{AFX_MSG(wcSliderPopup)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnNcDestroy();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnActivateApp(BOOL bActive, DWORD hTask);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};



// CColourPopup messages
#define CSP_DELTAPOS         WM_USER + 1201        // Colour Picker Selection change
#define CSP_CLOSEUP          WM_USER + 1202        // Colour Picker close up

class wcSliderButton : public CEdit
{
	DECLARE_DYNAMIC (wcSliderButton)
// Construction
public:
	wcSliderButton(void);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(wcSliderButton)
	public:
	//}}AFX_VIRTUAL
	virtual BOOL Create(BOOL LeftBut, DWORD dwExStyle, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Implementation
public:
	virtual ~wcSliderButton();
	void	SetLeftButton			( BOOL Left );
	void	SetPos					( int Pos );
	int		GetPos					( void )				{ return m_Pos; };
	void	SetRange				( int nMin, int nMax )	{ m_Min = nMin; m_Max = nMax; };
	void	SetRange				( int Pos, int nMin, int nMax )	{ SetRange (nMin, nMax); SetPos (Pos); };

	// Generated message map functions
protected:
	enum 
	{
		VALID			= 0x00, 
		OUT_OF_RANGE	= 0x01, 
		INVALID_CHAR	= 0x02, 
		MINUS_PLUS		= 0x03
	};

	void			ButtonClicked			( void );					// handles a mouse click on the button
	void			DrawButton				( int nButtonState = 0 );	// draws the button
	BOOL			ScreenPointInButtonRect	( CPoint point );			// checks if the given point is in the browse button
	void			CheckPosRange			( void );
	int				GetPosPerc				( void );
	void			OnBadInput				( void );
	virtual int		IsValid			( void ) const; 
	

	//{{AFX_MSG(wcSliderButton)
	afx_msg void OnUpdate();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
#if (_MSC_VER < 1400)
    afx_msg UINT OnNcHitTest(CPoint point);
#else
	afx_msg LRESULT OnNcHitTest(CPoint point);
#endif
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
    afx_msg LRESULT OnSliderDelta(WPARAM lParam, LPARAM wParam);
    afx_msg LRESULT OnSliderClose(WPARAM lParam, LPARAM wParam);
	DECLARE_MESSAGE_MAP()

private:
	BOOL			m_bButtonLeft;			// browse button on left side of control?
	BOOL			m_bMouseCaptured;		// button has captured the mouse?
	int				m_nButtonState;			// current button state (up, down, or disabled)
	CRect			m_rcButtonRect;			// window coordinates of the button
	int				m_Pos;
	int				m_Min;
	int				m_Max;
};

/////////////////////////////////////////////////////////////////////////////
// DDV_/DDX_FileEditCtrl functions

void DDX_SliderButtonCtrl (CDataExchange *pDX, int nIDC, wcSliderButton &rCFEC, BOOL LeftBut);



//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_HUIUTILITYMFC_H__20011029__1611__)
