// AdvancedMaterialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "HGlobals.h"
#include "vlist.h"
#include "vhash.h"
#include "HEventInfo.h"
#include "HBaseView.h"
#include "HModelInfo.h"
#include "HSelectionSet.h"
#include "HMaterialLibrary.h"
#include "HUtilityGeometryCreation.h"
#include "AdvancedMaterialDlg.h"
#include "AdvMtlTexturePage.h"
#include "AdvMtlTextureTransPage.h"
#include "AdvMtlMiscPage.h"
#include "AdvMaterialSheet.h"
#include "CAppSettings.h"
#include <map>
#include <string>

HMaterialLibrary * CAdvancedMaterialDlg::mpMaterialLibrary = 0;
int                CAdvancedMaterialDlg::mMaterialIndex = 0;
int                CAdvancedMaterialDlg::mPreviewIndex = 0;

#define HAM_STRING_LEN 1024
#define HAM_MATERIAL 0
#define HAM_TWEAKABLE 1
#define HAM_TYPE 2
#define HAM_VALUE 3
#define HAM_FOLDER 4

#define HAM_DRIVER "/driver/dx9/mainsphere"
//#define HAM_DRIVER "/driver/opengl2/mainsphere"
#define HAM_ENVIRONMENT "environment/civic_square"

//
// doubleToLogSlider
//
inline int doubleToLogSlider( double dvar )
{
   
    double lVal = log10( dvar ); 
    
    double e = ( lVal + 1 ) * 25;
    
    int sliderVal = (int) e;
    
    return sliderVal;
    
}


//
// AdvMtlTreeManager
//
//   Internal class to manage tree of materials.
//   It has two main functions:
//
//         1.  Groups materials by folder
//         2.  Tracks if materials have been fully loaded
//
//   Materials are not fully loaded until selected.
//

using namespace std;

class AdvMtlTreeManager
{
    // map for grouping materials by folder
    
    map< string, HTREEITEM > mNodeMap;  
    map< string, HTREEITEM > :: const_iterator  mFolderItr;
    typedef pair <string, HTREEITEM> Node_Pair;
    
    // map for tracking of materials have been fully loaded
    
    map< HTREEITEM, bool > mMaterialLoadMap;  
    map< HTREEITEM, bool > :: iterator  mMtlLoadItr;
    
    typedef pair <HTREEITEM, bool> MtlLoad_Pair;


   CTreeCtrl * mpTree;
   HMaterialLibrary *mpMaterialLibrary;
   
public:

   AdvMtlTreeManager( CTreeCtrl * pTree, HMaterialLibrary *pMaterialLibrary  )
   {
       mpTree = pTree;
       mpMaterialLibrary = pMaterialLibrary;
   }
 
   //
   //  Splits material name into folder and actual name.
   //
   void splitName( const char * fullnameIn, string &folderOut, string &nameOut )
   {
       int strMaxLen = strlen( fullnameIn );
       char drive[1]; // dummy
       char ext[1]; // dummy
       char * pFolder = new char[ strMaxLen + 1];
       char * pName  = new char[ strMaxLen + 1];
        _splitpath( fullnameIn, drive, pFolder, pName,ext );
        
        
        folderOut = string( pFolder );
        nameOut = string( pName );
        
        // /remove the '/' from the end of the folder
        
        folderOut.erase( folderOut.length() - 1, 1 );
        
        delete [] pFolder;
        delete [] pName;

   }
   
   //
   // searches for an existing tree node with the given name
   //
   HTREEITEM findFolder(  std::string folderName )
   {
       mFolderItr = mNodeMap.find(  folderName );
       
       if  ( mFolderItr == mNodeMap.end( ) )
          return 0;
          
       return  mFolderItr->second;
   }
   
   //
   //  adds a material to the tree
   //
   HTREEITEM addMaterial( const char * fullName )
   {
       string folderName, mtlName;
       splitName( fullName, folderName, mtlName );
       
       HTREEITEM hFolder = findFolder( folderName );
       if ( 0 == hFolder )
       {
            hFolder = mpTree->InsertItem(   H_UNICODE_TEXT( folderName.c_str()) );
            mpTree->SetItemData( hFolder, HAM_FOLDER );  
            mNodeMap.insert( Node_Pair( folderName, hFolder ) );
            
       }
       
       // create a material node, but don't fully load the material
       
       HTREEITEM hItem = mpTree->InsertItem( H_UNICODE_TEXT( mtlName.c_str()), hFolder );
       mpTree->SetItemData( hItem, HAM_MATERIAL );
       mMaterialLoadMap.insert( MtlLoad_Pair(  hItem, false ) ); // note that the material isn't fully loaded
       return hItem;

   }
   
    //
    //  loadSelectedMaterial
    //
    //   Checks if a material has been fully loaded. If not the material is loaded
    //
    void loadSelectedMaterial( CString strMaterialName, HTREEITEM hItem )
    {
       mMtlLoadItr = mMaterialLoadMap.find(  hItem );
       
       if  ( mMtlLoadItr != mMaterialLoadMap.end() )
       {
          bool loaded = mMtlLoadItr->second;
          
          if ( !loaded )
          {
              addMaterialDetailsToTree(  H_ASCII_TEXT( strMaterialName.GetBuffer()), hItem );
              mMtlLoadItr->second = true;
          }
       }
    }
    
    
    //
    //  AddMaterialDetailsToTree
    //
    //    Add the tweakable parameter information to the tree.
    //    This can only be done currently by initializing the material and parsing the shader program.
    //    Therefore to avoid an initial hit loading the shader editor we delay adding details until the 
    //    user selects a material name in the tree.
    //
    void addMaterialDetailsToTree( const char * pMaterialName, HTREEITEM hItem  )
    {
        char strTweak[ HAM_STRING_LEN ];
        char strType[ HAM_STRING_LEN ];

        HTREEITEM childItem = 0;
        HTREEITEM typeItem = 0;
        HTREEITEM valItem = 0;
        int tCount = 0;
        if ( mpMaterialLibrary->GetTweakablesCount( pMaterialName, &tCount  ) )
        {
            
            for ( int i = 0; i < tCount; i++ )
            {
                mpMaterialLibrary->GetTweakableByIndex( pMaterialName, i, strTweak, strType );
                
                childItem = mpTree->InsertItem(  H_UNICODE_TEXT( strTweak ), hItem );
                mpTree->SetItemData( childItem, HAM_TWEAKABLE ); // mark tweakable 
                
                typeItem = mpTree->InsertItem(  H_UNICODE_TEXT( strType ), childItem ); 
                mpTree->SetItemData( typeItem, HAM_TYPE ); // mark tweakable type
                
                int nVals = mpMaterialLibrary->CountFromType( strType );
                
                float vals[4];
                mpMaterialLibrary->GetTweakableDefaults( pMaterialName, i, vals );
                for ( int j = 0; j < nVals; j++ )
                {
                    CString strVal;
                    strVal.Format( _T("%g"), vals[j] );
                    valItem = mpTree->InsertItem(  strVal, typeItem ); 
                    mpTree->SetItemData( valItem, HAM_VALUE ); // tweakable value
                }
                
            }
        }
    }
};



// CAdvancedMaterialDlg dialog

IMPLEMENT_DYNAMIC(CAdvancedMaterialDlg, CDialog)

CAdvancedMaterialDlg::CAdvancedMaterialDlg( HBaseView *pView, CWnd* pParent /*=NULL*/)
	: CDialog(CAdvancedMaterialDlg::IDD, pParent)
  
{
  
    mpHView = pView;
    mpEnumeratedMaterial = 0;
    mpCurrentMaterial = 0;
    mColorSelected = false;
    mFloatSelected = false;
    mSelectionCount = 0;
    mpPropertySheet = 0;
    mTextureScaleX = 1.0;
    mTextureScaleY = 1.0;
    mhBrush = 0;
    mStrFloatVal = "";
    mpAdvMtlsTreeManager = 0;
    mLibraryInitialized = true; 
    mEnvironmentInitialized = false;
    
}

CAdvancedMaterialDlg::~CAdvancedMaterialDlg()
{
    if ( 0 != mpAdvMtlsTreeManager )
       delete mpAdvMtlsTreeManager;
}

void CAdvancedMaterialDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_HAM_TREE, mMaterialsTree);
    DDX_Control(pDX, IDC_HAM_MATERIALS_EDT, mEdtMaterialsString);
    DDX_Control(pDX, IDC_WND_COLOR, mWndColor);
    DDX_Control(pDX, ID_PREVIEW_WIN, mWndPreview);
    DDX_Control(pDX, IDC_EDT_FLOAT, mEdtFloat);
    DDX_Control(pDX, IDC_BTN_TWEAK_COLOR, mBtnTweakColor);
    DDX_Control(pDX, IDC_GROUP_COLOR, mLabelColor);
    DDX_Control(pDX, IDC_GROUP_NUMBER, mLabelFloat);
    DDX_Control(pDX, IDC_BTN_TWEAK_FLOAT, mButtonApplyFloat);
    DDX_Control(pDX, IDC_SHEET_FRAME, mFramePropertySheet);
    DDX_Control(pDX, IDC_SEL_MTL_RELOAD, mBtnReloadMaterial);
    DDX_Control(pDX, IDC_HAM_ENV_EDT, mEdtEnvironment);
}



BEGIN_MESSAGE_MAP(CAdvancedMaterialDlg, CDialog)
    ON_NOTIFY(NM_CLICK, IDC_HAM_TREE, &CAdvancedMaterialDlg::OnNMClickHamTree)
    ON_NOTIFY(TVN_SELCHANGED, IDC_HAM_TREE, &CAdvancedMaterialDlg::OnTvnSelchangedHamTree)
    ON_BN_CLICKED(IDC_SEL_MTL_APPLY, &CAdvancedMaterialDlg::OnBnClickedSelMtlApply)
    ON_BN_CLICKED(IDC_SEL_MTL_CLONE, &CAdvancedMaterialDlg::OnBnClickedSelMtlClone)
    ON_BN_CLICKED(IDC_BTN_TWEAK_COLOR, &CAdvancedMaterialDlg::OnBnClickedBtnTweakColor)
    ON_WM_DRAWITEM()
    ON_BN_CLICKED(IDCANCEL, &CAdvancedMaterialDlg::OnBnClickedCancel)
    ON_WM_CTLCOLOR()
    ON_EN_UPDATE(IDC_EDT_FLOAT, &CAdvancedMaterialDlg::OnEnUpdateEdtFloat)
    ON_BN_CLICKED(IDC_BTN_TWEAK_FLOAT, &CAdvancedMaterialDlg::OnBnClickedBtnTweakFloat)
    ON_BN_CLICKED(IDC_SEL_MTL_RELOAD, &CAdvancedMaterialDlg::OnBnClickedSelMtlReload)
END_MESSAGE_MAP()


// CAdvancedMaterialDlg message handlers

//
//  PreTranslateMessage
//
//   Override for tooltip support
//
BOOL CAdvancedMaterialDlg::PreTranslateMessage(MSG* pMsg)
{
     m_ToolTip.RelayEvent(pMsg);

     return CDialog::PreTranslateMessage(pMsg);
}


//
//  LayoutTweakableControls
//
void CAdvancedMaterialDlg::LayoutTweakableControls()
{
    //
    // Layout tweakable editors
    // 
    //    Places on top of the other. We only show one at a time. Use the color editor as the guide.
    //

     
    CRect tRect, cRect, dlgRect,lwRect, nlwRect, ncRect, cdlgRect;
    
    GetWindowRect( &dlgRect );
    GetClientRect( &cdlgRect );
    ClientToScreen(&cdlgRect);
    CPoint offset = cdlgRect.TopLeft();
    offset.x = -offset.x;
    offset.y = -offset.y;


    mLabelColor.GetWindowRect( &tRect );
    mLabelColor.GetClientRect( &cRect );
    ncRect = cRect;
    ClientToScreen(&ncRect );
    
    tRect.OffsetRect( offset );
    
    mLabelFloat.GetWindowRect( &lwRect );
    mLabelFloat.MoveWindow(  tRect);
    mLabelFloat.GetWindowRect( &nlwRect );

  
    mWndColor.GetWindowRect( &tRect );
    tRect.OffsetRect( offset );
    mEdtFloat.MoveWindow( &tRect );

    mBtnTweakColor.GetWindowRect( &tRect );
    tRect.OffsetRect( offset );
    mButtonApplyFloat.MoveWindow( &tRect );
 
}

//
// BuildMaterialsTree
//
void CAdvancedMaterialDlg::BuildMaterialsTree( bool EraseExisting )
{
    if ( EraseExisting )
    {
        mMaterialsTree.DeleteAllItems();
    }
    
    if ( !mLibraryInitialized  )
        return;
        
	//
	// enumerate the material names
	//
	const char * pName  = 0;
	
	BeginEnumerateMaterialNames();
	
	    while(  ( pName = GetNextMaterialName() ) != 0 )
	    {
	         mpAdvMtlsTreeManager->addMaterial( pName );
	    }
	    
	EndEnumerateMaterialNames();
	
	mMaterialsTree.SortChildren( NULL );
}

//
// OnInitDialog
//
//   Initialize the material library and treeview
//
BOOL CAdvancedMaterialDlg::OnInitDialog()
{

    CDialog::OnInitDialog();
    
    
    //Create the ToolTip control
	if( !m_ToolTip.Create(this))
	{
	   TRACE0("Unable to create the ToolTip!");
	}
	else
	{
	  // Add tool tips to the controls, either by hard coded string 
	  // or using the string table resource
	  m_ToolTip.AddTool( &mBtnTweakColor, _T("Modifies color tweakable of current material"));
	  m_ToolTip.Activate(TRUE);
	}
	
    LayoutTweakableControls();

    //
    //  Set Up property sheets
    //
    if ( NULL == mpPropertySheet )
    {
 
        CString  strCap = "hello";
        LPCTSTR  pCap = strCap;
        CWnd * pPlaceHolder = GetDlgItem( IDC_SHEET_FRAME );

        mpPropertySheet = new CAdvMaterialSheet( pCap, pPlaceHolder  );
      
        CRect crect,wrect;
        pPlaceHolder->GetClientRect( &crect );
        pPlaceHolder->GetWindowRect( &wrect );
        ScreenToClient( &wrect );
        

        CAdvMtlTextureTransPage * pTexTrans = new CAdvMtlTextureTransPage();
        CAdvMtlTexturePage  * pTex   = new CAdvMtlTexturePage();
        CAdvMtlMiscPage     * pMisc  = new CAdvMtlMiscPage();
        
        pTexTrans->SetDialog( this );
        pTex->SetDialog( this );
        pMisc->SetDialog( this );
       
        mpPropertySheet->AddPage( pTexTrans );
        mpPropertySheet->AddPage( pTex );
        mpPropertySheet->AddPage( pMisc );
        
        mpPropertySheet->Create( this ,  WS_CHILD | WS_VISIBLE | WS_EX_CONTROLPARENT | DS_3DLOOK | WS_TABSTOP );

        mpPropertySheet->SetWindowPos( 0, wrect.TopLeft().x, wrect.TopLeft().y, wrect.Width(), wrect.Height(), SWP_NOZORDER  | SWP_NOREDRAW | SWP_NOACTIVATE  );

	 
    }    

    
	if ( CAdvancedMaterialDlg::mpMaterialLibrary == NULL) 
	{
	    if (  HDB::GetMaterialLibrary() == NULL ) 
	        HDB::SetMaterialLibrary (new HMaterialLibrary());
	     
	    CAdvancedMaterialDlg::mpMaterialLibrary = HDB::GetMaterialLibrary();
	    
	    HC_Open_Segment_By_Key (mpHView->GetSceneKey()); {
		    mLibraryInitialized = HDB::GetMaterialLibrary()->RegisterMaterials (CAppSettings::MaterialLibraryDirectory);
		    //HDB::GetMaterialLibrary()->RegisterMaterials (H_FORMAT_TEXT ("%s\\%s", getenv("HMF_MASTER"), "materials"));
	    } HC_Close_Segment ();
		mEnvironmentInitialized = HDB::GetMaterialLibrary()->SetEnvironment (HAM_ENVIRONMENT);
	  
	}
	
	mEdtEnvironment.SetWindowText( _T(HAM_ENVIRONMENT ) );
	
	HC_Open_Segment_By_Key (mpHView->GetSceneKey()); {
		HC_Style_Segment( HDB::GetMaterialLibrary()->GetContainerSegment() );
	} HC_Close_Segment ();

	HC_Open_Segment_By_Key (mpHView->GetLightsKey()); {
		HC_Flush_Contents ("...", "lights");
		HC_Set_Visibility ("images=off");
		HC_Include_Segment (HDB::GetMaterialLibrary()->GetContainerSegment());
	} HC_Close_Segment ();
	
	mEdtMaterialsString.SetWindowText(CAppSettings::MaterialLibraryDirectory);
	
	
	if ( NULL == mpAdvMtlsTreeManager ) 
         mpAdvMtlsTreeManager = new AdvMtlTreeManager( &mMaterialsTree, mpMaterialLibrary );
 
	BuildMaterialsTree( false );

	
	DisableTweakableControls();
	
    char dopt[MVO_BUFFER_SIZE];
	
	//
	// Create a unique segment name for this previe window
	//
	sprintf( mPreviewSegmentName, "%s_%d",HAM_DRIVER, CAdvancedMaterialDlg::mPreviewIndex++ );
	
 	mPreviewKey = HC_KOpen_Segment( mPreviewSegmentName );	
        HC_Set_Visibility("faces = on, edges = off, lines = off, markers = off,lights=on");
	    sprintf (dopt, "disable input = all, use window id = %s%p", H_EXTRA_POINTER_FORMAT, mWndPreview.m_hWnd);
	    HC_Set_Driver_Options(dopt);
	    HC_Set_Driver_Options("isolated=on");
 	    //HC_Set_Rendering_Options("hlro = (face displacement = 5, visibility = off, pattern = 1, dim factor = 0.6)");		
	    HC_Set_Rendering_Options( "hsra = hardware z-buffer, technology = standard" );
	    //HC_Set_Driver_Options("debug = 0x01000000, double-buffering, no gamma correction, no light scaling");
	    HC_Set_Driver_Options("double-buffering, no gamma correction, no light scaling");
	    //HC_Set_Heuristics("no partial erase");
	    //HC_Set_Rendering_Options("no display lists");
	    HC_Set_Rendering_Options("lighting interpolation = (faces=gouraud)") ;
	    HC_Set_Color("window=white");
	     HC_Set_Color("faces=blue");
	    HPoint center(0.0,0);
	    float radius = 10.0;
	    int numsides = 24;
	    HPoint axis( 0.0, 0.0, 1.0 );
	    HPoint ref( 0.0, 1.0, 0.0 );
	    float texture_matrix[16] = { 1, 0, 0, 0, 0 , 1, 0, 0 ,0 , 0, 1, 0 , 0, 0, 0, 1 };
     HC_Open_Segment("scene");
	        HC_Insert_Distant_Light( -1, -1, -1 ); 
	        HC_Insert_Distant_Light( 1, 1, 1 );
	        HC_Set_Camera_Position( -100.0, 0, 0 );
	        HC_Set_Camera_Target ( 0,0 ,0 );
	        HC_Set_Camera_Field( 20.0, 20.0 );
	        HC_Set_Texture_Matrix( texture_matrix );
			HC_Scale_Texture( 5, 5, 5 );

            HUtilityGeometryCreation::CreateSphere( center, radius, numsides,  axis, ref );
        HC_Close_Segment();
 	HC_Close_Segment();	

     return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}




//
//  Utility Functions 
//
//   May be added to material library
//
void  CAdvancedMaterialDlg::BeginEnumerateMaterialNames()
{
    mpCurrentMaterial = const_cast< char *> ( mpMaterialLibrary->GetMaterialList() );
    
}

//
//  GetNextMaterialName
//
//    Seaches for the next ; seperated name.
//    Returns the name in a new null terminated string.
//
const char * CAdvancedMaterialDlg::GetNextMaterialName()
{
    if ( mpCurrentMaterial == 0 ) 
        return 0;
        
    int nChars = 0;
    char * pEnd = mpCurrentMaterial;
    
    while ( ( *pEnd != 0 ) && ( *pEnd != ';' ) )
    {
        pEnd++;
        nChars++;
    }
         
    if ( nChars == 0 )
    {
        mpCurrentMaterial = 0;
        return 0;
    }
        
    if ( mpEnumeratedMaterial != 0 )
        delete []  mpEnumeratedMaterial;
  
    mpEnumeratedMaterial = new char[ nChars + 1 ];
    strncpy( mpEnumeratedMaterial, mpCurrentMaterial, nChars );
    mpEnumeratedMaterial[ nChars ] = 0;
    
 
     if ( *pEnd != 0 )
        mpCurrentMaterial = pEnd + 1;
     else
         mpCurrentMaterial = 0;
        
    return mpEnumeratedMaterial;
    
}


void  CAdvancedMaterialDlg:: EndEnumerateMaterialNames()
{
      if ( mpEnumeratedMaterial != 0 )
        delete []  mpEnumeratedMaterial;
        
      mpCurrentMaterial = 0;
      mpEnumeratedMaterial = 0;

}

//
// Apply Material
//
//   Applies material to currently selection set
//
void CAdvancedMaterialDlg::ApplyMaterial(  const char *name ) 
{
    HSelectionSet *selection = mpHView->GetSelection();
    char key_type[MVO_BUFFER_SIZE];

	if ( selection )
	{
		const unsigned int max = sizeof(mSelectedKeys)/sizeof(mSelectedKeys[0]);
		mSelectionCount = MIN(selection->GetSize(), max);

		// Save selection
		for (  int i = 0; i != mSelectionCount; ++i )
			mSelectedKeys[i] = selection->GetAt(i);

		// Deselect first so we see the material change.
		selection->DeSelectAll();

		// Refresh the material
		//mpMaterialLibrary->ReloadMaterial( name );

		// Restyle after deselection so selection styles don't conflict.
		
		float texture_matrix[16] = { 1, 0, 0, 0, 
		                             0 , 1, 0, 0 ,0 , 0, 1, 0 , 0, 0, 0, 1 };
		for ( int i = 0; i != mSelectionCount; ++i )
		{
		    HC_Show_Key_Type( mSelectedKeys[i], key_type );
		    
		    if ( streq(key_type, "segment") ) {
			    HC_Open_Segment_By_Key( mSelectedKeys[i] );
    			
    			
			        HC_Set_Texture_Matrix( texture_matrix );
			        HC_Scale_Texture( mTextureScaleX, mTextureScaleY, 1.0 );
				    mpMaterialLibrary->ApplyMaterial( name );
    				
			    HC_Close_Segment();
		    }
		}
	}
	
	mpHView->SetCameraChanged();
	mpHView->Update();
}


// Apply ApplyTextureParameters
//
//   Applies texture scaling to currently selection set
//
void CAdvancedMaterialDlg::ApplyTextureParameters( double scaleX, double scaleY ) 
{
    char key_type[MVO_BUFFER_SIZE];
    
    mTextureScaleX = scaleX;
    mTextureScaleY = scaleY;
    float texture_matrix[16] = { 1, 0, 0, 0, 0 , 1, 0, 0 ,0 , 0, 1, 0 , 0, 0, 0, 1 };
    
	if ( mSelectionCount )
	{

		for (  int i = 0; i != mSelectionCount; ++i )
		{
			HC_Show_Key_Type( mSelectedKeys[i], key_type );
		    
		    if ( streq(key_type, "segment") ) {

			    HC_Open_Segment_By_Key( mSelectedKeys[i] );
    			
			        HC_Set_Texture_Matrix( texture_matrix );
			        HC_Scale_Texture( scaleX, scaleY, 1.0 );
    				
			    HC_Close_Segment();
			    
	

			}
		}
		
		mpHView->Update();
	}
	else if ( 0 ) 
	{

        HC_Open_Segment_By_Key( mPreviewKey );	
            HC_Open_Segment("scene");
                HC_Set_Texture_Matrix( texture_matrix );
                HC_Scale_Texture( scaleX, scaleY, 1.0 );
            HC_Close_Segment();
        HC_Close_Segment();

        HC_Update_One_Display( mPreviewSegmentName );

        mWndPreview.RedrawWindow();
   }

	
}

//
//  GetSelectedMaterial
//
//    Gets the selected material from the tree. Moves up the tree from a selected item until it founds a material node
//
bool CAdvancedMaterialDlg::GetSelectedMaterial(  CString &cstrMaterialName  )
{
    HTREEITEM hItem = mMaterialsTree.GetSelectedItem();
    bool gotMaterial = false;
    
    while ( hItem  ) 
    {
        int iData = mMaterialsTree.GetItemData( hItem );
        
        if ( iData == HAM_MATERIAL ) // a material node gets its full name
        {
            gotMaterial = true;
            CString strName = mMaterialsTree.GetItemText( hItem );
            
            HTREEITEM hFolderItem = mMaterialsTree.GetParentItem( hItem );
            CString strFolder = mMaterialsTree.GetItemText( hFolderItem );
        
            cstrMaterialName =  strFolder + "/" + strName;
 
            break;
        }
        
        hItem = mMaterialsTree.GetParentItem(  hItem );
    }
     
    return gotMaterial;
}

//
//  GetSelectedTweakable
//
//     Gets information about the selected tweakable.
//
bool CAdvancedMaterialDlg::GetSelectedTweakable( CString &tweakableName, int &tweakIndex )
{
    HTREEITEM hItem = mMaterialsTree.GetSelectedItem();
    bool gotTweakable = false;
    
    while ( hItem  ) 
    {
        int iData = mMaterialsTree.GetItemData( hItem );
        
        if ( iData == HAM_TWEAKABLE ) // a tweakable node
        {
            gotTweakable = true;
            tweakableName = mMaterialsTree.GetItemText( hItem );
            break;
        }
        
        hItem = mMaterialsTree.GetParentItem(  hItem );
    }
     
    tweakIndex = 0;
    
    if ( gotTweakable ) // find the child index of the selected tweakable
    {
       HTREEITEM hItemParent = mMaterialsTree.GetParentItem(  hItem );  // the parent material
       
       HTREEITEM hChildItem = mMaterialsTree.GetChildItem( hItemParent );

       while ( hChildItem != hItem )
       {
          hChildItem = mMaterialsTree.GetNextItem( hChildItem, TVGN_NEXT );
          tweakIndex++;
       }
       
    }
    return gotTweakable;
    
}


//
//  OnNMClickHamTree
//
void CAdvancedMaterialDlg::OnNMClickHamTree(NMHDR *pNMHDR, LRESULT *pResult)
{
  
    HTREEITEM hParentItem;

    hParentItem = mMaterialsTree.GetSelectedItem();
  
    *pResult = 0;
}


//
//  OnTvnSelchangedHamTree
//
//    User selects another item in the tree
//
void CAdvancedMaterialDlg::OnTvnSelchangedHamTree(NMHDR *pNMHDR, LRESULT *pResult)
{
     
    HTREEITEM hItem = mMaterialsTree.GetSelectedItem();
    CString strName = mMaterialsTree.GetItemText( hItem );
   
    int nodeType = mMaterialsTree.GetItemData( hItem );
    
    if ( nodeType == HAM_FOLDER ) 
    {
        // no nothing
    }
    else 
    {
        if ( nodeType == HAM_MATERIAL ) 
        {
            DisableTweakableControls();
           
            
            HTREEITEM hFolderItem = mMaterialsTree.GetParentItem( hItem );
            CString strFolder = mMaterialsTree.GetItemText( hFolderItem );
            
            mStrMaterialName = strFolder + "/" + strName;
            
            mEdtMaterialsString.SetWindowText(   mStrMaterialName  );
            
            mpAdvMtlsTreeManager->loadSelectedMaterial( mStrMaterialName,  hItem );

        } 
        else // its a tweakable node of some kind
        {
            //
            //  Its either a value or type
            //
            int TweakIndex;
            CString TweakableName, strFormat;
            
            GetSelectedMaterial( mStrMaterialName );
            GetSelectedTweakable( TweakableName, TweakIndex );
            
            strFormat.Format( _T("%s: %s ( %d )"), mStrMaterialName,  TweakableName, TweakIndex );
            
            mEdtMaterialsString.SetWindowText(   strFormat  );

            
            EnableTweakableControls(  TweakableName, TweakIndex );
            
            
        }

        int len = mStrMaterialName.GetLength() + 1;
         char * pChars = new char [ len ];
           
        wcstombs( pChars, mStrMaterialName.GetBuffer(), len );	
           
       UpdatePreviewWindow( false, pChars );
           
       delete [] pChars;
    }

    *pResult = 0;
}


//
//  OnBnClickedSelMtlApply
//
//   User has pressed apply material button. Apply the current material to the selected segments
//
void CAdvancedMaterialDlg::OnBnClickedSelMtlApply()
{
    
    if ( mStrMaterialName.GetLength() > 0 )
        ApplyMaterial( H_ASCII_TEXT (mStrMaterialName.GetBuffer()) );

}

//
//  OnBnClickedSelMtlClone
//
//     Clone an existing material and add it to the tree
//
void CAdvancedMaterialDlg::OnBnClickedSelMtlClone()
{
    CString strName;
    
    if ( GetSelectedMaterial( strName ) )
    {
         char  new_name[ HAM_STRING_LEN];
         
         CAdvancedMaterialDlg::mMaterialIndex++;
         
         if (mpMaterialLibrary->CloneMaterial( H_ASCII_TEXT( strName.GetBuffer()), new_name ) )
         {
            mpAdvMtlsTreeManager->addMaterial( new_name );
         }
    }
    
}


//
//  DisableFloatControl
//
void CAdvancedMaterialDlg::DisableFloatControl( bool bHide )
{
    CString strFloat = _T("Edit - ");

    mEdtFloat.EnableWindow( FALSE );
    mLabelFloat.EnableWindow( FALSE );
    mLabelFloat.SetWindowText( strFloat );
    mButtonApplyFloat.EnableWindow( FALSE );
    
    if ( bHide ) 
    {
        mEdtFloat.ShowWindow( SW_HIDE );
        mLabelFloat.ShowWindow( SW_HIDE );
        mButtonApplyFloat.ShowWindow( SW_HIDE );
    }
 
}

//
//  DisableColorColor
//
void CAdvancedMaterialDlg::DisableColorControl( bool bHide )
{
    CString strColor = _T("Edit - ");
    
    mWndColor.EnableWindow( FALSE );
    mLabelColor.EnableWindow( FALSE );
    mLabelColor.SetWindowText( strColor );
    mBtnTweakColor.EnableWindow( FALSE );
    mWndColor.Invalidate( TRUE );
    
    if ( bHide ) 
    {
        mWndColor.ShowWindow( SW_HIDE );
        mLabelColor.ShowWindow( SW_HIDE );
        mBtnTweakColor.ShowWindow( SW_HIDE );
    }

}

//
// DisableTweakableControls
//
//   Disable tweable editor controls
//
void CAdvancedMaterialDlg::DisableTweakableControls()
{
    DisableFloatControl( false );
    DisableColorControl( false );
}

//
//  Enable tweakable controls and update the parameters
//
void CAdvancedMaterialDlg::EnableTweakableControls( CString TweakableName, int TweakIndex  )
{

      CString strFloat = _T("Edit - Float");
      CString strColor = _T("Edit - Color");

      mIdxTweakable    = TweakIndex;
      mStrTweakableName = TweakableName;
      
      char strType[ HAM_STRING_LEN ];
      char strTweak[ HAM_STRING_LEN ];
      char strName[ HAM_STRING_LEN ];

      strcpy( strName, H_ASCII_TEXT( mStrMaterialName.GetBuffer()));
      
      //
      //  Get the current values
      
      mpMaterialLibrary->GetTweakableByIndex( strName, mIdxTweakable, strTweak, strType );
      mNumVals = mpMaterialLibrary->CountFromType( strType );
      mpMaterialLibrary->GetTweakableDefaults( strName, mIdxTweakable, mVals );
      
      mColorSelected = mNumVals == 3;
      mFloatSelected = mNumVals == 1;
      
      
 
    if ( mColorSelected )
    {
         DisableFloatControl( true );
            
        //
        // grab color for color pane
        //
        int r = (int) ( mVals[0] * 255.0 + 0.5 );
        int g = (int) ( mVals[1] * 255.0 + 0.5 );
        int b = (int) ( mVals[2] * 255.0 + 0.5 );
        mColorRef = RGB(  r,g,b  );          

        
        mWndColor.ShowWindow( SW_SHOW );
        mLabelColor.ShowWindow( SW_SHOW );
        mBtnTweakColor.ShowWindow( SW_SHOW );

        mWndColor.EnableWindow( TRUE );
        mLabelColor.EnableWindow( TRUE );
        mBtnTweakColor.EnableWindow( TRUE );
 
        mLabelColor.SetWindowText( strColor + " - " + mStrTweakableName );
 
    }
    else if ( mFloatSelected )
    {
        //
        // disable color window 
        //
        
        DisableColorControl( true );
        
        mEdtFloat.ShowWindow( SW_SHOW );
        mLabelFloat.ShowWindow( SW_SHOW );
        mButtonApplyFloat.ShowWindow( SW_SHOW );
        
        mEdtFloat.EnableWindow( TRUE );
        mLabelFloat.EnableWindow( TRUE );
        mButtonApplyFloat.EnableWindow( TRUE );

        
        CString strFloatVal;
        strFloatVal.Format( _T("%g"), mVals[0] ); 
        mLabelFloat.SetWindowText( strFloat + " - " + mStrTweakableName );
        mEdtFloat.SetWindowText(  strFloatVal );
  
    }
    else
    {   
        CString strWarning;
        strWarning.Format(_T("Tweakable - %d (%s) type (%s) is neither color nor float, mNumVals = %d"), mIdxTweakable, strTweak, strType, mNumVals );
        mEdtMaterialsString.SetWindowText( strWarning );
    }

   
}


//
//  OnBnClickedBtnTweakColor
//
//    Apply change in color tweakable
//
void CAdvancedMaterialDlg::OnBnClickedBtnTweakColor()
{


    CColorDialog dlg( mColorRef, CC_ANYCOLOR | CC_RGBINIT | CC_FULLOPEN );
     if ( dlg.DoModal() == IDOK )
     {
        mColorRef = dlg.GetColor();
        mVals[0] = (float) GetRValue( mColorRef ) / 255.0;
        mVals[1] = (float) GetGValue( mColorRef ) / 255.0;
        mVals[2] = (float) GetBValue( mColorRef ) / 255.0;
        
        mpMaterialLibrary->Tweak( H_ASCII_TEXT( mStrMaterialName.GetBuffer()), mIdxTweakable, mVals );
 
 
        UpdateSelectedTweakableItem( 3 );
        
   	    mpHView->SetCameraChanged();
	    mpHView->ForceUpdate();
	    
	   mWndColor.InvalidateRect(NULL, TRUE);
       mWndColor.UpdateWindow();


    }
}

//
//  OnDrawItem
//
//    Override for custom color
//
void CAdvancedMaterialDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   
    CWnd *pWnd = GetDlgItem( nIDCtl );
    
    if ( nIDCtl == IDC_WND_COLOR  )
    {   
        CDC dc;
        dc.Attach(lpDrawItemStruct->hDC);
        dc.DrawEdge( &lpDrawItemStruct->rcItem, EDGE_SUNKEN, BF_RECT );
        
        if ( mColorSelected &&  pWnd->IsWindowEnabled() )
        {
             CBrush clr( mColorRef );
             dc.FillRect( &lpDrawItemStruct->rcItem, &clr );
        }    
        else
        {
             COLORREF bk = RGB(240,240,240);
             CBrush clr( bk );
             dc.FillRect( &lpDrawItemStruct->rcItem, &clr );
        }     
        dc.Detach();
    }
    else if ( nIDCtl == ID_PREVIEW_WIN  )
    {
        	HC_Control_Update_By_Key (mPreviewKey, "redraw everything");

	        HC_Update_One_Display( mPreviewSegmentName );

    }
    else
    {
        CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
    }
}



//
//  UpdatePreviewWindow
//
//    Chnages preview material after chnage to material parameters
//
void CAdvancedMaterialDlg::UpdatePreviewWindow( bool isColor, char * name )
{
       HC_Control_Update_By_Key (mPreviewKey, "redraw everything");

        HC_Open_Segment( mPreviewSegmentName );
             HC_Open_Segment("scene");
             
                if ( isColor )
                     HC_Set_Color( name );
                else {
                     mpMaterialLibrary->ApplyStyles();
                     mpMaterialLibrary->ApplyMaterial( name );
                }
                     
             HC_Close_Segment();
 
        HC_Close_Segment();
        
        
       HC_Update_One_Display( mPreviewSegmentName );
        
	   mWndPreview.RedrawWindow();

}


//
// Saves the contents of the current selection in an internal list.
// If clear is true, then the current selection set is clear.
//
// Often we want to clear the selection after applying materials changes,
// but keep the selected entities for further use e.g.
//
void   CAdvancedMaterialDlg::UpdateSelection( bool clear )
{
   
    HSelectionSet *selection = mpHView->GetSelection();

	if ( selection  )
	{
		const unsigned int max = sizeof(mSelectedKeys)/sizeof(mSelectedKeys[0]);
		mSelectionCount = MIN(selection->GetSize(), max);

		// Save selection
		for (  int i = 0; i != mSelectionCount; ++i )
			mSelectedKeys[i] = selection->GetAt(i);

		// Deselect first so we see the material change.
		if ( clear  )
		    selection->DeSelectAll();
    }

}

//
// UpdateSelectedTweakable
//
//   Updates the value of a tweakable in the tree. First get the value noe, then update the items
//
//
void CAdvancedMaterialDlg::UpdateSelectedTweakableItem( int nVals )
{
    HTREEITEM hItem = mMaterialsTree.GetSelectedItem();
    CString strName = mMaterialsTree.GetItemText( hItem );
   
    int nodeType = mMaterialsTree.GetItemData( hItem );
    
    
    if ( nodeType == HAM_MATERIAL ) 
    {
        // no tweakable is selected
        return;
    } 
    
    HTREEITEM hItemTweakable = 0;
    HTREEITEM hItemType = 0;
    HTREEITEM hItemValue = 0;
    
    //
    // get the type node
    //
    if ( nodeType == HAM_TWEAKABLE )
    {
       hItemTweakable = hItem;
       hItemType =  mMaterialsTree.GetChildItem( hItemTweakable );
    }
    else if ( nodeType == HAM_TYPE  )
    {
       hItemType  =  hItem;
    }
    else if ( nodeType == HAM_VALUE )
    {
        hItemValue = hItem;
        hItemType = mMaterialsTree.GetParentItem( hItemValue );
    } 

    //
    // update the values from the mVals array
    //
    if ( hItemType )
    {
        int j = 0;
        hItemValue =  mMaterialsTree.GetChildItem( hItemType );
        while( hItemValue )
        {
            if ( j == nVals ) // its a bug if this happens as it means there are more child items than values
                break;
            CString strVal;
            strVal.Format( _T("%g"), mVals[j] );
            mMaterialsTree.SetItemData( hItemValue, HAM_VALUE ); // tweakable value
            mMaterialsTree.SetItemText( hItemValue, strVal );
            hItemValue =  mMaterialsTree.GetNextItem( hItemValue, TVGN_NEXT);
            j++;
        }
            
    }
 

  
}

HBRUSH CAdvancedMaterialDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{

  HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
  
  if ( nCtlColor = CTLCOLOR_DLG )
  {
     mhBrush = hbr;
  }
  return (HBRUSH ) hbr;
}

void CAdvancedMaterialDlg::OnBnClickedCancel()
{
    // TODO: Add your control notification handler code here
    OnCancel();
}

//
//  OnEnUpdateEdtFloat
//
//    Used to check user has input a valid number as they type
//
void CAdvancedMaterialDlg::OnEnUpdateEdtFloat()
{
    CString newText;
    mEdtFloat.GetWindowText( newText );
    
    int nChar = newText.GetLength();
    
    //
    // check element types
    //
    bool oops = false;
    bool foundDecimal = false;
    
    for ( int i = 0; i < nChar; i++)
    {
        TCHAR tChar = newText.GetAt( i );
        if ( tChar == '.' || tChar == ',' )
        {
            if ( foundDecimal )
            {
               oops = true;
               break;
            }
            foundDecimal = true;
        }
        else if ( !isdigit( tChar ) )
        {
           oops = true;
           break;
        }
    }
    
    if ( oops ) // revert to previous value
    {
        int selStart, selFinish;
        mEdtFloat.GetSel( selStart, selFinish );
        mEdtFloat.SetWindowText( mStrFloatVal );
        mEdtFloat.SetSel( selStart, selFinish );
    }
    else
    {
        mStrFloatVal = newText;
    }
    
}

//
//  OnBnClickedBtnTweakFloat
//
//    Applies current float value to active tweakable
//
void CAdvancedMaterialDlg::OnBnClickedBtnTweakFloat()
{
 
        mVals[0] = _tstof(  mStrFloatVal.GetBuffer() );
        mVals[1] = mVals[0];
        mVals[2] = mVals[0];
        
        mpMaterialLibrary->Tweak( H_ASCII_TEXT( mStrMaterialName.GetBuffer()), mIdxTweakable, mVals );
        UpdateSelectedTweakableItem( 1 );
 
   	    mpHView->SetCameraChanged();
	    mpHView->ForceUpdate();
	    mpHView->Update();

}

// 
//   OnBnClickedSelMtlReload
//
//     Reload the selected material e.g. after the material source has been updated.
//     Note:  The code does not updated the tweakable in the tree for now.
//
void CAdvancedMaterialDlg::OnBnClickedSelMtlReload()
{
    CString strName;
    
    if ( GetSelectedMaterial( strName ) )
    {
           
         if ( mpMaterialLibrary->ReloadMaterial( H_ASCII_TEXT( strName.GetBuffer() ) ) )
         {
           
         }
    }
    
}   

