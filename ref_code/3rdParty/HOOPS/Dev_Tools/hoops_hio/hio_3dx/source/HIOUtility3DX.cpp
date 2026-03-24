//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hio_3dx/source/HIOUtility3DX.cpp,v 1.3 2011-01-14 19:06:01 guido Exp $
//


// standard includes
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include <A3DSDKIncludes.h>

// Hoops Include
#include "HIOUtility3DX.h"
#include "hc.h"
#include "H3DXHelper.h"
#include "HUtilityLocaleString.h"

HIOUtility3DX::HIOUtility3DX() 
{
	SetInputOps(HInputOpFileInputByKey);
}

HFileInputResult HIOUtility3DX::FileInputByKey(const wchar_t * FileName, HC_KEY key, HInputHandlerOptions * options)
{
	bool free_options = false;

	if (!FileName)
		return InputBadFileName;
	if (!key)
		return InputFail;
	if (!options)
	{
		free_options = true;
		options = new HInputHandlerOptions;
	}
	


	SetStartingInput(FileName);

	H3DXImporter importer(this);
	bool result = importer.Import(FileName, key, options);

	SetFinishedInput();

	if (!options->m_bPRCCreatePRCFileOnly)
		HC_Optimize_Segment_Tree_By_Key(key, "instance shells, preserve user options=on");

	if (free_options)
		delete options;

	if (result)
		return InputOK;
	else
		return InputFail;
}

HFileOutputResult HIOUtility3DX::FileOutputByKey(const wchar_t * FileName, HC_KEY key, HOutputHandlerOptions * options)
{
	if (!FileName)
		return OutputBadFileName;
	if (!key)
		return OutputFail;

	H3DXExporter exporter;

	return (exporter.Export(FileName, key, options) ? OutputOK : OutputFail);
}


void HIOUtility3DX::RegisterInputHandlerTypes() {
 	HIORegisterInputType("prc",this); // Acrobat's Internal 3D Representation
	HIORegisterInputType("prd",this); // Acrobat's Internal 3D Representation
	HIORegisterInputType("x_t",this); // Parasolid ASCII
	HIORegisterInputType("xmt_txt",this);  // Parasolid ASCII
	HIORegisterInputType("x_b",this); // Parasolid Binary
	HIORegisterInputType("step",this); // STEP
	HIORegisterInputType("stp",this); // STEP
	HIORegisterInputType("igs",this); // IGES
	HIORegisterInputType("iges",this); // IGES
	HIORegisterInputType("CATPart",this);  // Catia V5 Part
	HIORegisterInputType("CATProduct",this); // Catia V5 Assembly
	HIORegisterInputType("cgr",this); // Catia Graphics File
	HIORegisterInputType("session",this); // Catia V4
	HIORegisterInputType("model",this);  // Catia V4 
	HIORegisterInputType("3dxml",this); // Dassault Interchange Format
	HIORegisterInputType("CADDS",this); // CADDS5
	HIORegisterInputType("PD",this); // CADDS5
	HIORegisterInputType("XV3",this); // Lattice XVL
	HIORegisterInputType("XV0",this); // Lattice XVL
	HIORegisterInputType("prt",this); // Siemens NX and Pro/E
	HIORegisterInputType("asm",this); //Pro/E
	HIORegisterInputType("xpr",this); //Pro/E
	HIORegisterInputType("xas",this); //Pro/E
	HIORegisterInputType("neu",this); //Pro/E
	HIORegisterInputType("asm.1",this); //Pro/E
	HIORegisterInputType("prt.1",this); //Pro/E
	HIORegisterInputType("jt",this); // JT
 	HIORegisterInputType("SLDPRT",this);  //SolidWorks Part
 	HIORegisterInputType("SLDASM",this);  // SolidWorks Assembly
	HIORegisterInputType("mf1",this);  // IDEAS	
	HIORegisterInputType("arc",this);  // IDEAS
	HIORegisterInputType("unv",this);  // IDEAS
 	HIORegisterInputType("pkg",this);  // IDEAS and OneSpace Designer
	HIORegisterInputType("sdp",this);  // OneSpace Designer
	HIORegisterInputType("sdpc",this);  // OneSpace Designer
	HIORegisterInputType("sdw",this);  // OneSpace Designer
	HIORegisterInputType("sdwc",this);  // OneSpace Designer
	HIORegisterInputType("sda",this);  // OneSpace Designer
	HIORegisterInputType("sdac",this);  // OneSpace Designer
	HIORegisterInputType("sds",this);  // OneSpace Designer
	HIORegisterInputType("sdsc",this);  // OneSpace Designer
	HIORegisterInputType("ses",this);  // OneSpace Designer
	HIORegisterInputType("bdl",this);  // OneSpace Designer
 	HIORegisterInputType("psm",this);  // SolidEdge
	HIORegisterInputType("pwd",this);  // SolidEdge
	HIORegisterInputType("par",this);  // SolidEdge Part
	HIORegisterInputType("asm",this);  // SolidEdge Assembly
	HIORegisterInputType("sat",this); // ACIS ASCII
	HIORegisterInputType("sab",this); // ACIS Binary
	HIORegisterInputType("ipt",this);  // Autodesk Inventor
	HIORegisterInputType("iam",this);  // Autodesk Inventor
	HIORegisterInputType("ifc",this);  // Industry Foundation Classes
	HIORegisterInputType("dae",this);  // COLLADA
	HIORegisterInputType("u3d",this); // U3D


	// These formats are supported through HIO that are included with HOOPS
	// without licensing third party libraries.  Uncomment if you want to
	// read these formats through Acrobat

	// 	HIORegisterInputType("vrml",this); // VRML
	// 	HIORegisterInputType("wrl",this); // VRML
 		HIORegisterInputType("u3d",this); // U3D
	//	HIORegisterInputType("stl",this); // Stereo Lithography
	//	HIORegisterInputType("obj",this); //Wavefront OBJ
	//	HIORegisterInputType("3ds",this); // Autodesk's 3DS Format

 }

void HIOUtility3DX::RegisterOutputHandlerTypes() {
	HIORegisterOutputType("prc", this);
	HIORegisterOutputType("iges", this);
	HIORegisterOutputType("step", this);
	HIORegisterOutputType("x_t", this);
	HIORegisterOutputType("stl", this);
}



#ifdef HIO_3DX
void * CreateInput(HIOManager *manager)
{

	//TODO, Handle CADDS Files.  They have no extension and start with _pd

	HIOUtility3DX *handler = new HIOUtility3DX();
	handler->RegisterInputHandlerTypes();

  	return handler;
};

void * CreateOutput(HIOManager *manager)
{
	HIOUtility3DX *handler = new HIOUtility3DX();
	handler->RegisterOutputHandlerTypes();

  	return handler;
};

void * CreateConnector(void * unused)
{
	return NULL;
};

void Free(HIOUtility3DX *handler)
{ 
	if(handler) 
	{
		delete handler; 
	}
};


#endif


