// HVisualizeModel.cpp : implementation of the HVisualizeModel class
//


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "hc.h"
#include "HStream.h"
#include "HOpcodeShell.h"
#include "HUtility.h"

#include "HVisualizeModel.h"
#include "HTools.h"


HVisualizeModel::HVisualizeModel()
{
	m_bSolidModel = false;
	SetBRepGeometry(false);
}

HVisualizeModel::~HVisualizeModel()
{
	// Model cleanup : delete all the entities from the 
	// partition associated with this model
	DeleteAllEntities();
}

// Delete all the entities in the current model from the 
// modeller and associated HOOPS geometry
void HVisualizeModel::DeleteAllEntities()
{
}



// our application-specific read function
HFileInputResult HVisualizeModel::Read(const char * FileName) 
{   
//	CWaitCursor show_hourglass_cursor_through_this_function;

	HFileInputResult success = InputOK;

	// get the file extension
	char extension[120]; 
	HUtility::FindFileNameExtension(FileName, extension);

	// read the file into the model object's model segment
    HC_Open_Segment_By_Key(m_ModelKey);	

		HC_Open_Segment("main");
			// No special read - let the base class handle
			m_bSolidModel = false;
			success = HBaseModel::Read(FileName);
 		HC_Close_Segment();
    HC_Close_Segment();

    return success;
}

// our application-specific write function
bool HVisualizeModel::Write(const char * FileName, HBaseView * view, 
									int version, int width, int height) 
{   
//	CWaitCursor show_hourglass_cursor_through_this_function;

	bool success = true;
 
	// get the file extension
	char extension[120]; 
	HUtility::FindFileNameExtension(FileName, extension);

	if(!HBaseModel::Write(FileName, view, width, height))
		success = false;

    return success;
}




