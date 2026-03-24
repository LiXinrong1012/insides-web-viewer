// HVisualizeView.cpp : implementation of the HVisualizeView class
// 

// Standard includes
#include <assert.h>
#include <math.h>
#include "hc.h"

#include "HVisualizeView.h"
#include "HVisualizeModel.h"
#include "HVisualizeSelectionSet.h"

#include "HSharedKey.h"

#include "HConstantFrameRate.h"


HVisualizeView::HVisualizeView(HBaseModel *model,
    const char * 		alias,	
    const char *		driver_type,
    const char *		instance_name,
    void *				window_handle,
    void *				colormap,
    void *				clip_override) : HBaseView(model, alias, driver_type, instance_name, window_handle, colormap, clip_override)

{
}

HVisualizeView::~HVisualizeView()
{
	H_SAFE_DELETE(m_pSelection);
}


// app-specific init function
void HVisualizeView::Init()
{
	// call base's init function first to get the default HOOPS hierarchy for the view
	HBaseView::Init();

	// create our app-specific Selection object and initialize
	m_pSelection = new HVisualizeSelectionSet(this);
    m_pSelection->Init();

	// TODO: Add your initialization here
	HC_Open_Segment_By_Key(m_SceneKey);
	  HC_Set_Visibility("edges = off, lines = off");
    HC_Close_Segment();
}

void HVisualizeView::OnBuildLODS()
{
	int i, count;
	char type[256];

	HC_Open_Segment_By_Key(GetModelKey());
	  HC_Begin_Contents_Search("...", "shells");		
	  HC_Show_Contents_Count(&count);
	  HC_KEY *keyarray = new HC_KEY[count];

	  for (i=0;i<count;i++)
		HC_Find_Contents(type, &keyarray[i]);

	  HC_End_Contents_Search();
	HC_Close_Segment();

	for (int shellnum = 0; shellnum < count; shellnum++)
	{    
		int plen, flen, plen_optimized, flen_optimized;
		HC_KEY	shellkey = keyarray[shellnum];
		HC_Show_Shell_Size(shellkey, &plen, &flen);	  
		HPoint *plist = new HPoint[plen];
		int *flist = new int[flen];
		HPoint *plist_optimized = new HPoint[plen];
		int *flist_optimized = new int[flen];

		HC_Show_Shell(shellkey, &plen, plist, &flen, flist);

		HC_Open_Geometry(shellkey);
		  for (int j=1; j<=2; j++)
		  {  
			HC_Open_LOD(j);
			HC_Flush_Contents(".", "everything");

			switch(j)
			{
			case 1:
				if (plen > 50)
				{
					HC_Compute_Optimized_Shell(plen, plist, 0, flen, flist, "lod = 10%, lod algorithm = nice", 
						&plen_optimized, plist_optimized, &flen_optimized, flist_optimized, 0, 0);
					HC_Insert_Shell(plen_optimized, plist_optimized, flen_optimized, flist_optimized);
				}
				break;
			case 2:
				if (plen > 50)
				{
					HC_Compute_Optimized_Shell(plen, plist, 0, flen, flist, "lod = 5%, lod algorithm = nice", 
						&plen_optimized, plist_optimized, &flen_optimized, flist_optimized, 0, 0);
					HC_Insert_Shell(plen_optimized, plist_optimized, flen_optimized, flist_optimized);
				}
				break;
			}

			HC_Close_LOD();
		  }
		HC_Close_Geometry();

		delete [] plist;
		delete [] plist_optimized;
		delete [] flist;
		delete [] flist_optimized;
	}    

	delete [] keyarray;

	Update();
}



void HVisualizeView::OnLODOriginal()
{
	// render gouraud shaded mode for original LOD level
	RenderGouraud();

	HC_Open_Segment_By_Key(GetSceneKey());
		HC_Set_Rendering_Options("lighting interpolation = on, lod = off");
	HC_Close_Segment();

	Update();
}

void HVisualizeView::OnLOD1()
{
	// render in flat shaded mode for lods
	RenderFlat();

	HC_Open_Segment_By_Key(GetSceneKey());
		HC_Set_Rendering_Options("no lighting interpolation, lod = on, lodo = (clamp = 1, fallback = coarsest)");
	HC_Close_Segment();

	Update();
}

void HVisualizeView::OnLOD2()
{
	// render in flat shaded mode for lods
	RenderFlat();

	HC_Open_Segment_By_Key(GetSceneKey());
		HC_Set_Rendering_Options("no lighting interpolation, lod = on, lodo = (clamp = 2, fallback = coarsest)");
	HC_Close_Segment();

	Update();
}

void HVisualizeView::OnEnableFramerate()
{
	HConstantFrameRate *cframerate = GetConstantFrameRateObject();

	//set up a default simplification list
	HConstFRSimpType	**SimpList;
 		    
	SimpList = new HConstFRSimpType *[3];
	SimpList[0] = new HFrNoSimp;
	SimpList[1] = new HFrLodThreshold(0,6);
	SimpList[2] = new HFrSolidBBox();
 	
	cframerate->Init(30.0, SimpList, 3);  

 	cframerate->Start();  
}

void HVisualizeView::OnDisableFramerate()
{
	HConstantFrameRate *cframerate = GetConstantFrameRateObject();
	HConstFRSimpType	**SimpList;
	int length = 0;

	//Delete list created in OnEnableFramerate
	if( cframerate->GetMode(&SimpList, 0, &length)  )
	{
		for (int x = 0; x < length; x++)
		{
			delete SimpList[x];
		}
		delete [] SimpList;
	}

	cframerate->Stop();	
	cframerate->Shutdown();   

	Update();
}

