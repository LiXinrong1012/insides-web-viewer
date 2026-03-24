// partviewer_common\AdvMtlTexturePage.cpp : implementation file
//

#include "stdafx.h"
#include "HGlobals.h"
#include "vlist.h"
#include "vhash.h"
#include "HEventInfo.h"
#include "HBaseView.h"
#include "HModelInfo.h"
#include "HSelectionSet.h"
#
#include "AdvancedMaterialDlg.h"
#include "partviewer_common\AdvMtlTexturePage.h"


// CAdvMtlTexturePage dialog

IMPLEMENT_DYNAMIC(CAdvMtlTexturePage, CPropertyPage)

CAdvMtlTexturePage::CAdvMtlTexturePage()
	: CPropertyPage(CAdvMtlTexturePage::IDD)
{
    mpDialog = 0;
}

CAdvMtlTexturePage::~CAdvMtlTexturePage()
{
}

void CAdvMtlTexturePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RB_UV_PLANE_X_Y,    mRB_PLANE_X_Y  );
    DDX_Control(pDX, IDC_RB_UV_PLANE_Y_Z,    mRB_PLANE_Y_Z  );
    DDX_Control(pDX, IDC_RB_UV_PLANE_Z_X,    mRB_PLANE_Z_X  );
    DDX_Control(pDX, IDC_RB_UV_SPHERE,       mRB_SPHERE     );
    DDX_Control(pDX, IDC_RB_UV_SPHERE_Y_Z,   mRB_SPHERE_Y_Z );
    DDX_Control(pDX, IDC_RB_UV_SPHERE_Z_X,   mRB_SPHERE_Z_X );


}


BEGIN_MESSAGE_MAP(CAdvMtlTexturePage, CPropertyPage)
    ON_BN_CLICKED(IDC_GEN_TEX, &CAdvMtlTexturePage::OnBnClickedGenTex)
    ON_WM_CTLCOLOR()

END_MESSAGE_MAP()


// CAdvMtlTexturePage message handlers



void CAdvMtlTexturePage::SetDialog( CAdvancedMaterialDlg *  pDlg )
{
    mpDialog = pDlg;
} 
	
CAdvancedMaterialDlg * CAdvMtlTexturePage::GetDialog()
{
    return mpDialog;
}

void CAdvMtlTexturePage::OnBnClickedGenTex()
{
    
    char key_type[MVO_BUFFER_SIZE];

    mpDialog->UpdateSelection( true );
    
    int nSelectionCount = mpDialog->GetSelectionCount();
    
    if ( nSelectionCount > 0 )
    {
        for ( int i = 0; i != nSelectionCount; ++i )
        {
        	  HC_Show_Key_Type( mpDialog->GetSelectedKeys()[i], key_type );
	    
	          if ( streq(key_type, "shell") ) {
	          
	                HShellWrapper shell( mpDialog->GetSelectedKeys()[i] );
	                HPoint center, min, max;
	                shell.FindExtents( center, min, max );
	                
	                float dx = fabs( max.x - min.x );
	                float dy = fabs( max.y - min.y );
	                float dz = fabs( max.z - min.z );
	                int nPoints = shell.m_plen;
	                float * uv = new float [ nPoints * 2 ];
	                float * pUV = uv;


                    if ( mRB_PLANE_X_Y.GetCheck() == BST_CHECKED ) 
                    {
                        for ( int iv = 0; iv< nPoints; iv++ )
	                    {
	                        float u = ( shell.m_Points[iv].x - min.x ) / dx;
	                        float v = ( shell.m_Points[iv].y - min.y ) / dy;
		                    
	                        *pUV++ = u;
	                        *pUV++ = v;
	                    }

                    }
                    else if ( mRB_PLANE_Y_Z.GetCheck() == BST_CHECKED )
                    {
                        for ( int iv = 0; iv< nPoints; iv++ )
	                    {
	                        float u = ( shell.m_Points[iv].y - min.y ) / dy;
	                        float v = ( shell.m_Points[iv].z - min.z ) / dz;
		                    
	                        *pUV++ = u;
	                        *pUV++ = v;
	                    }

                    }
                    else if ( mRB_PLANE_Z_X.GetCheck() == BST_CHECKED )
                    {
                        for ( int iv = 0; iv< nPoints; iv++ )
	                    {
	                        float u = ( shell.m_Points[iv].x - min.x ) / dx;
	                        float v = ( shell.m_Points[iv].z - min.z ) / dz;
		                    
	                        *pUV++ = u;
	                        *pUV++ = v;
	                    }
	
                    }
                    else if ( mRB_SPHERE.GetCheck() == BST_CHECKED ) // Z Axis
                    {
                        for ( int iv = 0; iv< nPoints; iv++ )
	                    {

                             double xd = shell.m_Points[iv].x - center.x;
                             double yd = shell.m_Points[iv].y - center.y;
                             double zd = shell.m_Points[iv].z - center.z;
                             
                             double radius = sqrt(xd * xd  + yd * yd  +  zd * zd );
                             double theta =  acos( zd / radius);
                             double phi    = atan2( yd, xd );
                             
                             *pUV++ = (float) theta;
	                         *pUV++ = (float)  phi;
                         }
                    }  
                    else if ( mRB_SPHERE_Y_Z.GetCheck() == BST_CHECKED ) // X Axis
                    {
                        for ( int iv = 0; iv< nPoints; iv++ )
	                    {

                             double xd = shell.m_Points[iv].x - center.x;
                             double yd = shell.m_Points[iv].y - center.y;
                             double zd = shell.m_Points[iv].z - center.z;
                             
                             double radius = sqrt(xd * xd  + yd * yd  +  zd * zd );
                             double theta =  acos( xd / radius);
                             double phi    = atan2( yd, zd );
                             
                             *pUV++ = (float) theta;
	                         *pUV++ = (float)  phi;
                         }
                    }  
                    else if ( mRB_SPHERE_Z_X.GetCheck() == BST_CHECKED ) // Y Axis
                    {
                        for ( int iv = 0; iv< nPoints; iv++ )
	                    {

                             double xd = shell.m_Points[iv].x - center.x;
                             double yd = shell.m_Points[iv].y - center.y;
                             double zd = shell.m_Points[iv].z - center.z;
                             
                             double radius = sqrt(xd * xd  + yd * yd  +  zd * zd );
                             double theta =  acos( yd / radius);
                             double phi    = atan2( zd, xd );
                             
                             *pUV++ = (float) theta;
	                         *pUV++ = (float)  phi;
                         }
                  
	                }
	                HC_MSet_Vertex_Parameters( mpDialog->GetSelectedKeys()[i], 0, nPoints, 2, uv );
	                delete [] uv;
	          }

	    }
	}
	
	HBaseView * pView = mpDialog->GetBaseView();
	pView->SetCameraChanged();
	pView->Update();
}

HBRUSH CAdvMtlTexturePage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
 HBRUSH hbr;
   
    if( nCtlColor == CTLCOLOR_DLG )
    {
          if ( mpDialog->GetDialogBrush() > 0 )
              return mpDialog->GetDialogBrush();
    }
    
        
   hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

  return hbr;
}