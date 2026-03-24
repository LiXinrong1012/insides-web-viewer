// HAnalysisModel.cpp : implementation of the HAnalysisModel class
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "hc.h"
#include "HStream.h"
#include "HOpcodeShell.h"
#include "HUtility.h"
#include "HIOManager.h"

#include "HAnalysisModel.h"
#include "HTools.h"



HAnalysisModel::HAnalysisModel()
{
	m_DataCycles = 10;

	m_bSolidModel = false;
	SetBRepGeometry(false);
}

HAnalysisModel::~HAnalysisModel()
{
}


float colors[39] = { 0,0,1,   0, 0.333333f, 1,   0, 0.666667f, 1,
					 0,1,1,   0, 1,  0.666667f,  0, 1, 0.333333f,
					 0,1,0,   0.333333f, 1, 0,   0.666667f, 1, 0,
					 1,1,0,   1, 0.666667f, 0,   1, 0.333333f, 0,
					 1,0,0 };


void HAnalysisModel::Init()
{
	HBaseModel::Init();

	//set up legend segment
    HC_Open_Segment_By_Key(m_ModelKey);	
		
		HC_Set_Color_Map_By_Value( "RGB", 13, colors);

		HC_Open_Segment("legendbar");
			HPoint pos(0.5, 0.0, 1.0), target(0.5, 0.0, -1.0), up(0.0, 1.0, 0.0);
			HC_Set_Camera( &pos, &target, &up, 5.0, 3.0, "orthographic" );

		    HC_Set_Handedness("left");
			HC_Set_Selectability("geometry=off");
			HC_Set_Visibility("cutting planes = off");
			HC_Set_Rendering_Options("depth range = (0,1e-4), simple shadow=off, anti-alias = text");
			HC_Set_Heuristics("no backplane culls");
			HC_Set_Color("edge=line=text=R=0 G=0 B=0");



			HC_Set_Text_Font("size=.07 oru, size tolerance=0 points, no transforms, line spacing=1");
			HC_Set_Text_Alignment("<*");

			HC_Insert_Text( 0.5f, 14.0f, 0.0f, "von Mises (psi)");
			HC_Insert_Text( -.5f, 0.0f, 0.0f, "9.155e+001");
			HC_Insert_Text( -.5f, 1.0f, 0.0f, "9.208e+003");
			HC_Insert_Text( -.5f, 2.0f, 0.0f, "1.833e+004");
			HC_Insert_Text( -.5f, 3.0f, 0.0f, "2.744e+004");
			HC_Insert_Text( -.5f, 4.0f, 0.0f, "3.656e+004");
			HC_Insert_Text( -.5f, 5.0f, 0.0f, "4.568e+004");
			HC_Insert_Text( -.5f, 6.0f, 0.0f, "5.479e+004");
			HC_Insert_Text( -.5f, 7.0f, 0.0f, "6.391e+004");
			HC_Insert_Text( -.5f, 8.0f, 0.0f, "7.303e+004");
			HC_Insert_Text( -.5f, 9.0f, 0.0f, "8.214e+004");
			HC_Insert_Text( -.5f, 10.0f, 0.0f, "9.126e+004");
			HC_Insert_Text( -.5f, 11.0f, 0.0f, "1.004e+005");
			HC_Insert_Text( -.5f, 12.0f, 0.0f, "1.095e+005");

			float mm[] = { 0.1, 0.0, 0.0, 0.0,
						   0.0, 0.1, 0.0, 0.0,
						   0.0, 0.0, 0.1, 0.0,
						   -1.00, -.75, 0.0, 1.0};

			HC_Set_Modelling_Matrix( mm );

			HC_Open_Segment("chart");

				float const points[3*26] = 
				{	0,0,0,  1,0,0,  0,1,0,  1,1,0,
					0,2,0,  1,2,0,  0,3,0,  1,3,0,
					0,4,0,  1,4,0,  0,5,0,  1,5,0,
					0,6,0,  1,6,0,  0,7,0,  1,7,0,
					0,8,0,  1,8,0,  0,9,0,  1,9,0,
					0,10,0,  1,10,0,  0,11,0,  1,11,0,
					0,12,0,  1,12,0
				};

				int const chart_flist[5*12] = 
				{ 4, 0,1,3,2,
				  4, 2,3,5,4,
				  4, 4,5,7,6,
				  4, 6,7,9,8,
				  4, 8,9,11,10,
				  4, 10,11,13,12,
				  4, 12,13,15,14,
				  4, 14,15,17,16,
				  4, 16,17,19,18,
				  4, 18,19,21,20,
				  4, 20,21,23,22,
				  4, 22,23,25,24
				};

				HC_Set_Visibility("faces=on,edges=on,lights=off");
				HC_KEY shell_key = HC_KInsert_Shell( 26, points, 60, chart_flist);

				int i, flist_length=12;
				float *indices; 

				// set a default face color
				int f_count = flist_length;
				indices = new float[ f_count ];
				for ( i = 0 ; i < f_count ; i++ ) {
					indices[i] = (float)i;
				}
				HC_MSet_Face_Colors_By_FIndex( shell_key, "faces", 0, f_count, indices);

				delete [] indices;

			HC_Close_Segment();
		HC_Close_Segment();
	HC_Close_Segment();

}


// our application-specific read function
HFileInputResult HAnalysisModel::Read(const char * FileName) 
{   

	HFileInputResult success = InputOK;

	// get the file extension
	char extension[120]; 
	HUtility::FindFileNameExtension(FileName, extension);

	// read the file into the model object's model segment
    HC_Open_Segment_By_Key(m_ModelKey);	
		HC_Open_Segment("main");
			{
				// No special read - let the base class handle
				m_bSolidModel = false;
				success = HBaseModel::Read(FileName);
			}
 		HC_Close_Segment();
    HC_Close_Segment();

    return success;
}

// our application-specific write function
bool HAnalysisModel::Write(const char * FileName, HBaseView * view, 
									int version, int width, int height) 
{   

	bool success = true;
 
	// get the file extension
	char extension[120]; 
	HUtility::FindFileNameExtension(FileName, extension);

	{
		if(!HBaseModel::Write(FileName, view, width, height))
			success = false;
	}
 
    return success;
}
