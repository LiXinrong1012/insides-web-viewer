#ifndef _INCLUDE_PROGRESSDLG_H
#define _INCLUDE_PROGRESSDLG_H


/////////////////////////////////////////////////////////////////////////////
// CProgressDlg window

class CProgressDlg : public CWnd
{
// Construction/Destruction
public:
    CProgressDlg();
    CProgressDlg(CWnd* pParent, LPCTSTR pszTitle, BOOL bSmooth = FALSE);
    virtual ~CProgressDlg();

    virtual BOOL Create(CWnd* pParent, LPCTSTR pszTitle, BOOL bSmooth = FALSE);
    BOOL GoModal(LPCTSTR pszTitle =_T("Progress"), BOOL bSmooth = FALSE);

protected:
    void CommonConstruct();

// Operations
public:
    void SetRange(int nLower, int nUpper, int nStep = 1);
                                                    // Set range and step size
    int OffsetPos(int nPos);                        // Same as CProgressCtrl
    int StepIt();                                   //    "
    int SetStep(int nStep);                         //    "
    int SetPos(int nPos);                           //    "

    void SetText(LPCTSTR fmt, ...);                 // Set text in text area

    void Clear();                                   // Clear text, reset bar
    void Hide();                                    // Hide window
    void Show();                                    // Show window

    BOOL Cancelled() { return m_bCancelled; }       // Was "Cancel" hit?

	void SetWindowSize(int nNumTextLines, int nWindowWidth = 390);

    void PeekAndPump(BOOL bCancelOnESCkey = TRUE);  // Message pumping for modal operation   
    
// Implementation
protected:
    void GetPreviousSettings();
    void SaveCurrentSettings();

protected:
    BOOL m_bCancelled;
    BOOL m_bModal;
    BOOL m_bPersistantPosition;
    int  m_nPrevPos, m_nPrevPercent;
    int  m_nStep;
    int  m_nMaxValue, m_nMinValue;
    int  m_nNumTextLines;

    CStatic       m_Text;
    CProgressCtrl m_wndProgress;
    CButton       m_CancelButton;
    CString       m_strTitle,
                  m_strCancelLabel;
    CFont         m_font;


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CProgressDlg)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
    //{{AFX_MSG(CProgressDlg)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
    afx_msg void OnCancel();
    DECLARE_MESSAGE_MAP()
};


class HStreamFileToolkit;

enum ProgressMode
{
	HStreamRead,
	HStreamWrite
};

class HStreamProgressDlg : public CProgressDlg
{
// Construction/Destruction
public:
    HStreamProgressDlg(HStreamFileToolkit* tk, ProgressMode readOrWrite);
    virtual ~HStreamProgressDlg();

    virtual BOOL Create(CWnd* pParent, LPCTSTR pszTitle, BOOL bSmooth = FALSE);

	ProgressMode GetProgressMode() { return m_ProgressMode; }
	void SetProgressMode(ProgressMode readOrWrite) { m_ProgressMode = readOrWrite; }

	bool SetCurrentProgress(unsigned long so_far, unsigned long expected, void * user_data);


protected:
	HStreamFileToolkit* m_tk;
	ProgressMode m_ProgressMode;
};


#endif
/////////////////////////////////////////////////////////////////////////////

