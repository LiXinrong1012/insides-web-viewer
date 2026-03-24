#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"


class HMaterialLibrary;
class HBaseView;
class CAdvMaterialSheet;
class AdvMtlTreeManager;



//
// CAdvancedMaterialDlg dialog
//
class CAdvancedMaterialDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdvancedMaterialDlg)

public:
	CAdvancedMaterialDlg( HBaseView *pHView,  CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdvancedMaterialDlg();

// Dialog Data
	enum { IDD = IDD_ADVANCED_MATERIAL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
//	virtual BOOL OnInitDialog( );

	DECLARE_MESSAGE_MAP()
	
	CToolTipCtrl m_ToolTip; // tooltips for  dialog controls
	
	BOOL PreTranslateMessage(MSG* pMsg);
	
private:
    
    //
    // Controls
    //
    CTreeCtrl          mMaterialsTree;
    CEdit              mEdtMaterialsString;
    CAdvMaterialSheet  *mpPropertySheet;
    HBRUSH              mhBrush;
    
    //
    //   Utility Variables
    //
    HBaseView *               mpHView;
    static HMaterialLibrary * mpMaterialLibrary;
    static int                mMaterialIndex;
    static int                mPreviewIndex;
    char *                    mpEnumeratedMaterial;
    char *                    mpCurrentMaterial;
    char                      mPreviewSegmentName[MVO_BUFFER_SIZE];
    AdvMtlTreeManager         *mpAdvMtlsTreeManager;

   
    
    //
    // Tweakable Editing
    // 
    CString                   mStrMaterialName;
    CString                   mStrTweakableName;
    CString                   mStrFloatVal;
    int                       mIdxTweakable;
    int                       mNumVals;
    bool                      mColorSelected;
    bool                      mFloatSelected;
    float                     mVals[4];
    COLORREF                  mColorRef;
    
  
    HC_KEY                    mSelectedKeys[256];
    int                       mSelectionCount;
     
    //
    // texture scaling
    //
    double                    mTextureScaleX;
    double                    mTextureScaleY;
    
    bool                      mLibraryInitialized;
    bool                      mEnvironmentInitialized;
   
public:

    virtual BOOL OnInitDialog();
    
    
    //
    //  Utility Functions 
    //
    
 
    bool GetSelectedMaterial( CString &StrMaterialName );
    void DisableFloatControl( bool Hide );
    void DisableColorControl( bool Hide );
    void DisableTweakableControls();
    bool GetSelectedTweakable( CString &TweakableName, int &tweakIndex );
    void EnableTweakableControls( CString TweakableName, int TweakIndex );
    void ApplyTextureParameters( double scaleX, double scaleY );
    void LayoutTweakableControls();
    void BuildMaterialsTree( bool EraseExisting );
    void UpdateSelectedTweakableItem( int nVals );
    void LoadSelectedMaterial( CString strMaterialName, HTREEITEM hItem );
    

    
    //
    //   May be added to material library
    //
    void         BeginEnumerateMaterialNames();
    const char * GetNextMaterialName(); 
    void         EndEnumerateMaterialNames();
    
    void         ApplyMaterial(  const char *name );
    
    void UpdatePreviewWindow( bool isColor, char * name );
    
  
         
    //
    // Message Handlers
    //
    afx_msg void OnNMClickHamTree(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnTvnSelchangedHamTree(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedSelMtlApply();
    afx_msg void OnBnClickedSelMtlClone();
    afx_msg void OnBnClickedBtnTweakColor();
    CStatic mWndColor;
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    CWnd mWndPreview;
    long mPreviewKey;
     afx_msg void OnBnClickedCancel();
    
    //
    //  Accessor Functions used by Property Pages to interact with view and selection
    //
    
    HC_KEY     *              GetSelectedKeys()     { return  mSelectedKeys; }
    int                       GetSelectionCount()   { return  mSelectionCount; }
    HBaseView *               GetBaseView()         { return  mpHView; }
    HBRUSH                    GetDialogBrush()      { return  mhBrush; }
    
    //
    // Saves the contents of the current selection in an internal list.
    // If clear is true, then the current selection set is clear.
    //
    // Often we want to clear the selection after applying materials changes,
    // but keep the selected entities for further use e.g.
    //
    void   UpdateSelection( bool clear );
    
    HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

    CEdit mEdtFloat;
    CButton mBtnTweakColor;
    afx_msg void OnEnUpdateEdtFloat();
    CStatic mLabelColor;
    CStatic mLabelFloat;
    CButton mButtonApplyFloat;
    afx_msg void OnBnClickedBtnTweakFloat();
    CStatic mFramePropertySheet;
    afx_msg void OnBnClickedSelMtlReload();
    CButton mBtnReloadMaterial;
    CEdit mEdtEnvironment;
};
