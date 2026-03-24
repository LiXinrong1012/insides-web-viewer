//************************************************************************** 

//* Export.cpp	- Ascii File Exporter

//* 

//* By Christer Janson

//* Kinetix Development

//*

//* January 20, 1997 CCJ Initial coding

//*

//* This module contains the main export functions.

//*

//* Copyright (c) 1997, All Rights Reserved. 

//***************************************************************************



#include "hsftomaxexp.h"

#include "BStream.h"
#include "BOpcodeShell.h"








/****************************************************************************



  Global output [Scene info]

  

****************************************************************************/

// export the HSF object to a file

static void WriteObject(BBaseOpcodeHandler * handler, BStreamFileToolkit * tk, FILE * fp,
                        char * buffer, int size) 
{
    TK_Status status;

    // ask the toolkit to write out the object; the toolkit will write out as much as
    // the current buffer can hold
    status = handler->Write(*tk);

    // if there is still more data left to write; we have to loop through 
    // generating and writing buffers of data until we're done
    while (status == TK_Pending) 
    {
        // due to compression, preparing a new buffer might immediately fill that buffer
        // so we need an extra check to possibly export that buffer and prepare a new buffer
        while (status == TK_Pending) 
        {
            // ask the toolkit how much of the buffer is currently filled
            // this will normally be the same as the buffer size that we passed in
            int count = tk->CurrentBufferLength();

            // write the current out to our file since this example deals with 
            // exporting a file; however, instead of writing to a file, the buffer of
            // data could be sent to an application data-structure, or transmitted
            // over a network ('streamed'), etc...
            fwrite(buffer, sizeof (char), count, fp);

            // tell the toolkit where it can resume writing data; in this case, we
            // can reuse the same buffer once we're done with it
            status = tk->PrepareBuffer(buffer, size);
        }

        // ask the toolkit to continue trying to write out the object's data
        status = handler->Write(*tk);
    }
}


 // Dump some global animation information.

void HsfExp::ExportGlobalInfo()

{

	Interval range = ip->GetAnimRange();



	struct tm *newtime;

	time_t aclock;



	time( &aclock );

	newtime = localtime(&aclock);



	TSTR today = _tasctime(newtime);	// The date string has a \n appended.

	today.remove(today.length()-1);		// Remove the \n



	// Start with a file identifier and format version

	FPRINTF(pStream, "%s\t%d\n", ID_FILEID, VERSION);



	// Text token describing the above as a comment.

	FPRINTF(pStream, "%s \"%s  %1.2f - %s\"\n", ID_COMMENT, GetString(IDS_VERSIONSTRING), VERSION / 100.0f, today);



	FPRINTF(pStream, "%s {\n", ID_SCENE);

	FPRINTF(pStream, "\t%s \"%s\"\n", ID_FILENAME, FixupName(ip->GetCurFileName()));

	FPRINTF(pStream, "\t%s %d\n", ID_FIRSTFRAME, range.Start() / GetTicksPerFrame());

	FPRINTF(pStream, "\t%s %d\n", ID_LASTFRAME, range.End() / GetTicksPerFrame());

	FPRINTF(pStream, "\t%s %d\n", ID_FRAMESPEED, GetFrameRate());

	FPRINTF(pStream, "\t%s %d\n", ID_TICKSPERFRAME, GetTicksPerFrame());

	

	Texmap* env = ip->GetEnvironmentMap();



	Control* ambLightCont;

	Control* bgColCont;

	

	if (env) {

		// Output environment texture map

		DumpTexture(env, Class_ID(0,0), 0, 1.0f, 0);

	}

	else {

		// Output background color

		bgColCont = ip->GetBackGroundController();

		if (bgColCont && bgColCont->IsAnimated()) {

			// background color is animated.

			FPRINTF(pStream, "\t%s {\n", ID_ANIMBGCOLOR);

			

			DumpPoint3Keys(bgColCont, 0);

				

			FPRINTF(pStream, "\t}\n");

		}

		else {

			// Background color is not animated

			Color bgCol = ip->GetBackGround(GetStaticFrame(), FOREVER);

			FPRINTF(pStream, "\t%s %s\n", ID_STATICBGCOLOR, Format(bgCol));

		}

	}

	

	// Output ambient light

	ambLightCont = ip->GetAmbientController();

	if (ambLightCont && ambLightCont->IsAnimated()) {

		// Ambient light is animated.

		FPRINTF(pStream, "\t%s {\n", ID_ANIMAMBIENT);

		

		DumpPoint3Keys(ambLightCont, 0);

		

		FPRINTF(pStream, "\t}\n");

	}

	else {

		// Ambient light is not animated

		Color ambLight = ip->GetAmbient(GetStaticFrame(), FOREVER);

		FPRINTF(pStream, "\t%s %s\n", ID_STATICAMBIENT, Format(ambLight));

	}



	FPRINTF(pStream,"}\n");

}



void HsfExp::GetLocalMatrix(INode *node, Matrix3 &pivot)

{

	Matrix3 nodeTM = node->GetNodeTM(GetStaticFrame());

	INode *parent;



	Matrix3 parentTM,  localTM;



	parent = node->GetParentNode();

	parentTM = parent->GetNodeTM(GetStaticFrame());

	pivot = nodeTM*Inverse(parentTM);

}





/****************************************************************************



  GeomObject output

  

****************************************************************************/

void HsfExp::ExportHsfMatrix(INode *node)

{

	Matrix3 nodeTM = node->GetNodeTM(GetStaticFrame());

	INode *parent;



	Matrix3 parentTM,  localTM;



	parent = node->GetParentNode();

	parentTM = parent->GetNodeTM(GetStaticFrame());

	Matrix3 pivot = nodeTM*Inverse(parentTM);





	TimeValue t = GetStaticFrame();	

	    TK_Matrix *matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);

 	float matrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};



// 		pivot.Invert();

		Point3 row = pivot.GetRow(0);

		matrix[0] = row[0];

		matrix[1] = row[1];

		matrix[2] = row[2];

		matrix[3] = 0;

		row = pivot.GetRow(1);

		matrix[4] = row[0];

		matrix[5] = row[1];

		matrix[6] = row[2];

		matrix[7] = 0;

		row = pivot.GetRow(2);

		matrix[8] = row[0];

		matrix[9] = row[1];

		matrix[10] = row[2];

		matrix[11] = 0;

		row = pivot.GetRow(3);

		matrix[12] = row[0];

		matrix[13] = row[1];

		matrix[14] = row[2];

		matrix[15] = 1;		

		matrix_handler->SetMatrix(matrix);

	    WriteObject(matrix_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
		delete matrix_handler;	

}

 



void HsfExp::ExportGeomObject(INode* node, int indentLevel)

{

	ObjectState os = node->EvalWorldState(GetStaticFrame());

	if (!os.obj)

		return;



	 

	

	// Targets are actually geomobjects, but we will export them

	// from the camera and light objects, so we skip them here.

	if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID, 0))

		return;

	

	

	TSTR indent = GetIndent(indentLevel);

	

	ExportNodeHeader(node, ID_GEOMETRY, indentLevel);

	

	ExportNodeTM(node, indentLevel);

	ExportHsfMatrix(node);

	

	if (GetIncludeMesh()) {

		ExportMesh(node, GetStaticFrame(), indentLevel);

	}



	// Node properties (only for geomobjects)

	FPRINTF(pStream, "%s\t%s %d\n", indent.data(), ID_PROP_MOTIONBLUR, node->MotBlur());

	FPRINTF(pStream, "%s\t%s %d\n", indent.data(), ID_PROP_CASTSHADOW, node->CastShadows());

	FPRINTF(pStream, "%s\t%s %d\n", indent.data(), ID_PROP_RECVSHADOW, node->RcvShadows());



	if (GetIncludeAnim()) {

		ExportAnimKeys(node, indentLevel);

	}



	// Export the visibility track

	Control* visCont = node->GetVisController();

	if (visCont) {

		FPRINTF(pStream, "%s\t%s {\n", indent.data(), ID_VISIBILITY_TRACK);

		DumpFloatKeys(visCont, indentLevel);

		FPRINTF(pStream, "\t}\n");

	}



	if (GetIncludeMtl()) {

		ExportMaterial(node, indentLevel);

	}



	if (GetIncludeMeshAnim()) {

		ExportAnimMesh(node, indentLevel);

	}

	

	if (GetIncludeIKJoints()) {

		ExportIKJoints(node, indentLevel);

	}

	

	FPRINTF(pStream,"%s}\n", indent.data());

}



/****************************************************************************



  Shape output

  

****************************************************************************/



void HsfExp::ExportShapeObject(INode* node, int indentLevel)

{

	ExportNodeHeader(node, ID_SHAPE, indentLevel);

	ExportNodeTM(node, indentLevel);

	ExportHsfMatrix(node);



	TimeValue t = GetStaticFrame();

	Matrix3 tm = node->GetObjTMAfterWSM(t);



	TSTR indent = GetIndent(indentLevel);

	

	ObjectState os = node->EvalWorldState(t);

	if (!os.obj || os.obj->SuperClassID()!=SHAPE_CLASS_ID) {

		FPRINTF(pStream,"%s}\n", indent.data());

		return;

	}

	

	ShapeObject* shape = (ShapeObject*)os.obj;

	PolyShape pShape;

	int numLines;



	// We will output ahspes as a collection of polylines.

	// Each polyline contains collection of line segments.

	shape->MakePolyShape(t, pShape);

	numLines = pShape.numLines;

	

	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_SHAPE_LINECOUNT, numLines);

	

	for(int poly = 0; poly < numLines; poly++) {

		FPRINTF(pStream,"%s\t%s %d {\n", indent.data(), ID_SHAPE_LINE, poly);

		DumpPoly(&pShape.lines[poly], tm, indentLevel);

		DumpHsfPoly(&pShape.lines[poly], tm);

		FPRINTF(pStream, "%s\t}\n", indent.data());

	}

	if (GetIncludeMtl()) {

		ExportMaterial(node, indentLevel);

	}



	

	if (GetIncludeAnim()) {

		ExportAnimKeys(node, indentLevel);

	}

	

	FPRINTF(pStream,"%s}\n", indent.data());

}



void HsfExp::DumpPoly(PolyLine* line, Matrix3 tm, int indentLevel)

{

	int numVerts = line->numPts;

	

	TSTR indent = GetIndent(indentLevel);

	

	if(line->IsClosed()) {

		FPRINTF(pStream,"%s\t\t%s\n", indent.data(), ID_SHAPE_CLOSED);

	}

	

	FPRINTF(pStream,"%s\t\t%s %d\n", indent.data(), ID_SHAPE_VERTEXCOUNT, numVerts);

	

	// We differ between true and interpolated knots

	for (int i=0; i<numVerts; i++) {

		PolyPt* pt = &line->pts[i];

		if (pt->flags & POLYPT_KNOT) {

			FPRINTF(pStream,"%s\t\t%s\t%d\t%s\n", indent.data(), ID_SHAPE_VERTEX_KNOT, i,

				Format(tm * pt->p));

		}

		else {

			FPRINTF(pStream,"%s\t\t%s\t%d\t%s\n", indent.data(), ID_SHAPE_VERTEX_INTERP,

				i, Format(tm * pt->p));

		}

		

	}

}











void HsfExp::DumpHsfPoly(PolyLine* line, Matrix3 tm)

{

  
	int numVerts = line->numPts;

	

 	

	if(line->IsClosed()) {

		;

 	}



	float *points = new float[numVerts * 3];

		

	

	// We differ between true and interpolated knots

	for (int i=0; i<numVerts; i++) {

		PolyPt* pt = &line->pts[i];

		points[i*3] = pt->p.x;

		points[i*3+1] = pt->p.y;

		points[i*3+2] = pt->p.z; 		

	}


	TK_Polypoint *polylinehandler= new TK_Polypoint(TKE_Polyline);

	polylinehandler->SetPoints(numVerts, points);

 	WriteObject(polylinehandler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	delete polylinehandler;



}



void HsfExp::ExportHsfLight(INode* node)

{





	TimeValue t = GetStaticFrame();

 

 	

	ObjectState os = node->EvalWorldState(t);

	if (!os.obj) {

 		return;

	}

	

	GenLight* light = (GenLight*)os.obj;

	struct LightState ls;

	Interval valid = FOREVER;

	Interval animRange = ip->GetAnimRange();



	light->EvalLightState(t, valid, &ls);

 

	if (ls.type == OMNI_LIGHT)

	{

	ExportHsfMatrix(node);
 
     TK_Point *light_handler = new TK_Point (TKE_Local_Light );
	 light_handler->SetPoint(0,0,0);
	WriteObject(light_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
     delete light_handler;  

	}

	else if (ls.type == TSPOT_LIGHT)

	{

 	Matrix3 matrix, targetmatrix;


		INode* target = node->GetTarget();

		if (target) {

			GetLocalMatrix(target, targetmatrix);

 	GetLocalMatrix(node, matrix);
	Point3 p(0,0,0);
	Point3 res = p * matrix;
	Point3 restarget = p * targetmatrix;
     TK_Spot_Light *light_handler = new TK_Spot_Light ();
	 light_handler->SetPosition(res.x, res.y, res.z);
	 light_handler->SetTarget(restarget.x, restarget.y, restarget.z);
	 light_handler->SetInner(light->GetHotspot(t));
	 light_handler->SetOuter(light->GetFallsize(t));
//	 light_handler->SetInner(ls.Ge);
	light_handler->SetOptions( TKO_Spot_Inner_Degrees | TKO_Spot_Outer_Degrees);


 
	WriteObject(light_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
     delete light_handler;  



		}

	}



    TK_Color *color_handler = new TK_Color();

    color_handler->SetGeometry( TKO_Geo_Extended | TKO_Geo_Light);

 	color_handler->SetChannels(1<<TKO_Channel_Diffuse);

	color_handler->SetDiffuse(ls.color);

	WriteObject(color_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
 

	

	 

}















/****************************************************************************



  Light output

  

****************************************************************************/



void HsfExp::ExportLightObject(INode* node, int indentLevel)

{



	ExportHsfLight(node);



	TimeValue t = GetStaticFrame();

	TSTR indent = GetIndent(indentLevel);



	ExportNodeHeader(node, ID_LIGHT, indentLevel);

	

	ObjectState os = node->EvalWorldState(t);

	if (!os.obj) {

		FPRINTF(pStream, "%s}\n", indent.data());

		return;

	}

	

	GenLight* light = (GenLight*)os.obj;

	struct LightState ls;

	Interval valid = FOREVER;

	Interval animRange = ip->GetAnimRange();



	light->EvalLightState(t, valid, &ls);



	// This is part os the lightState, but it doesn't

	// make sense to output as an animated setting so

	// we dump it outside of ExportLightSettings()



	FPRINTF(pStream, "%s\t%s ", indent.data(), ID_LIGHT_TYPE);

	switch(ls.type) {

	case OMNI_LIGHT:  FPRINTF(pStream, "%s\n", ID_LIGHT_TYPE_OMNI); break;

	case TSPOT_LIGHT: FPRINTF(pStream, "%s\n", ID_LIGHT_TYPE_TARG);  break;

	case DIR_LIGHT:   FPRINTF(pStream, "%s\n", ID_LIGHT_TYPE_DIR); break;

	case FSPOT_LIGHT: FPRINTF(pStream, "%s\n", ID_LIGHT_TYPE_FREE); break;

	}



	ExportNodeTM(node, indentLevel);

	// If we have a target object, export Node TM for the target too.

	INode* target = node->GetTarget();

	if (target) {

		ExportNodeTM(target, indentLevel);

	}



	int shadowMethod = light->GetShadowMethod();

	FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_LIGHT_SHADOWS,

			shadowMethod == LIGHTSHADOW_NONE ? ID_LIGHT_SHAD_OFF :

			shadowMethod == LIGHTSHADOW_MAPPED ? ID_LIGHT_SHAD_MAP :

			ID_LIGHT_SHAD_RAY);



	

	FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_LIGHT_USELIGHT, Format(light->GetUseLight()));

	

	FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_LIGHT_SPOTSHAPE, 

		light->GetSpotShape() == RECT_LIGHT ? ID_LIGHT_SHAPE_RECT : ID_LIGHT_SHAPE_CIRC);



	FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_LIGHT_USEGLOBAL, Format(light->GetUseGlobal()));

	FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_LIGHT_ABSMAPBIAS, Format(light->GetAbsMapBias()));

	FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_LIGHT_OVERSHOOT, Format(light->GetOvershoot()));



	ExclList* el = light->GetExclList();  // DS 8/31/00 . switched to NodeIDTab from NameTab

	if (el->Count()) {

		FPRINTF(pStream,"%s\t%s {\n", indent.data(), ID_LIGHT_EXCLUSIONLIST);

		FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_NUMEXCLUDED, Format(el->Count()));

		FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_EXCLINCLUDE, Format(el->TestFlag(NT_INCLUDE)));

		FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_EXCL_AFFECT_ILLUM, Format(el->TestFlag(NT_AFFECT_ILLUM)));

		FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_EXCL_AFFECT_SHAD, Format(el->TestFlag(NT_AFFECT_SHADOWCAST)));

		for (int nameid = 0; nameid < el->Count(); nameid++) {

			INode *n = (*el)[nameid];	// DS 8/31/00

			if (n)

				FPRINTF(pStream,"%s\t\t%s \"%s\"\n", indent.data(), ID_LIGHT_EXCLUDED, n->GetName());

			}

		FPRINTF(pStream,"%s\t}\n", indent.data());

	}



	// Export light settings for frame 0

	ExportLightSettings(&ls, light, t, indentLevel);



	// Export animated light settings

	if (!valid.InInterval(animRange) && GetIncludeCamLightAnim()) {

		FPRINTF(pStream,"%s\t%s {\n", indent.data(), ID_LIGHT_ANIMATION);



		TimeValue t = animRange.Start();

		

		while (1) {

			valid = FOREVER; // Extend the validity interval so the camera can shrink it.

			light->EvalLightState(t, valid, &ls);



			t = valid.Start() < animRange.Start() ? animRange.Start() : valid.Start();

			

			// Export the light settings at this frame

			ExportLightSettings(&ls, light, t, indentLevel+1);

			

			if (valid.End() >= animRange.End()) {

				break;

			}

			else {

				t = (valid.End()/GetTicksPerFrame()+GetMeshFrameStep()) * GetTicksPerFrame();

			}

		}



		FPRINTF(pStream,"%s\t}\n", indent.data());

	}



	// Export animation keys for the light node

	if (GetIncludeAnim()) {

		ExportAnimKeys(node, indentLevel);

		

		// If we have a target, export animation keys for the target too.

		if (target) {

			ExportAnimKeys(target, indentLevel);

		}

	}

	

	FPRINTF(pStream,"%s}\n", indent.data());

}



void HsfExp::ExportLightSettings(LightState* ls, GenLight* light, TimeValue t, int indentLevel)

{

	TSTR indent = GetIndent(indentLevel);



	FPRINTF(pStream,"%s\t%s {\n", indent.data(), ID_LIGHT_SETTINGS);



	// Frame #

	FPRINTF(pStream, "%s\t\t%s %d\n",indent.data(), ID_TIMEVALUE, t);



	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_COLOR, Format(ls->color));

	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_INTENS, Format(ls->intens));

	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_ASPECT, Format(ls->aspect));

	

	if (ls->type != OMNI_LIGHT) {

		FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_HOTSPOT, Format(ls->hotsize));

		FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_FALLOFF, Format(ls->fallsize));

	}

	if (ls->type != DIR_LIGHT && ls->useAtten) {

		FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_ATTNSTART, Format(ls->attenStart));

		FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_ATTNEND,	Format(ls->attenEnd));

	}



	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_TDIST, Format(light->GetTDist(t, FOREVER)));

	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_MAPBIAS, Format(light->GetMapBias(t, FOREVER)));

	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_MAPRANGE, Format(light->GetMapRange(t, FOREVER)));

	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_MAPSIZE, Format(light->GetMapSize(t, FOREVER)));

	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_LIGHT_RAYBIAS, Format(light->GetRayBias(t, FOREVER)));



	FPRINTF(pStream,"%s\t}\n", indent.data());

}





float HsfExp::GetCameraFov(INode *node)

{

	CameraState cs;

	TimeValue t = GetStaticFrame();

	Interval valid = FOREVER;

	// Get animation range

 	

	ObjectState os = node->EvalWorldState(t);

	CameraObject *cam = (CameraObject *)os.obj;

	

	cam->EvalCameraState(t,valid,&cs);



	return cs.fov;

}

	

 

void HsfExp::WriteHsfCamera(INode *node, INode *target, CameraState *cs, CameraObject *cam, int tt)

{		

	

	Point3 center;

	center.x = (m_max.x + m_min.x) /2.0f;

	center.y = (m_max.y + m_min.y) /2.0f;

	center.z = (m_max.z + m_min.z) /2.0f;

	Matrix3 pivot = node->GetNodeTM(GetStaticFrame());
	Matrix3 pivottarget;
	
	if (target)
		pivottarget = target->GetNodeTM(GetStaticFrame());

	Point3 p,t,u;
	p.x = 0;
	p.y = 0;
	p.z = 0;
	t.x = 0;
	t.y = 0;
	if (!target)
		t.z = -cam->GetTDist(tt);
	else
		t.z = 0;
	u.x = 0;
	u.y = 1;
	u.z = 0;

	p = p * pivot;
	if (!target)
		t = t * pivot;
	else
		t = t * pivottarget;

	u = u * pivot;

	u.x = u.x - p.x;
	u.y = u.y - p.y;
	u.z = u.z - p.z;
	u.Normalize();


	Point3 row0 = pivot.GetRow(0);

	Point3 row1 = pivot.GetRow(1);

	Point3 row2 = pivot.GetRow(2);

	Point3 row3 = pivot.GetRow(3);

 
	Point3 delta = t - p;
	float length = delta.Length();

//	Point3 targpos = t - p;
//	targpos.Normalize();
//	t = p + (targpos * length);




    // create a TK_Camera object to export a TKE_View opcode; this defines an initial
    // camera used to view the scene-graph contained in the file
     TK_Camera *view_handler = new TK_Camera (TKE_View);
	if (!m_bFirstCamera)
		view_handler->SetView("default");
	else
		view_handler->SetView(FixupName(node->GetName()));

    view_handler->SetProjection(TKO_Camera_Perspective);
    view_handler->SetPosition(p.x, p.y, p.z);
    view_handler->SetTarget(t.x, t.y, t.z);
    view_handler->SetUpVector(u.x, u.y, u.z);
    view_handler->SetField(cs->fov*cam->GetTDist(tt), cs->fov*cam->GetTDist(tt));  
	WriteObject(view_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	m_bFirstCamera = true;
     delete view_handler;  
}
 

/****************************************************************************



  Camera output

  

****************************************************************************/



void HsfExp::ExportCameraObject(INode* node, int indentLevel)

{

	TSTR indent = GetIndent(indentLevel);



	ExportNodeHeader(node, ID_CAMERA, indentLevel);

 

	INode* target = node->GetTarget();

	if (target) {

		FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_CAMERA_TYPE, ID_CAMERATYPE_TARGET);

	}

	else {

		FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_CAMERA_TYPE, ID_CAMERATYPE_FREE);

	}





	ExportNodeTM(node, indentLevel);

 	// If we have a target object, export animation keys for the target too.

	if (target) {

		ExportNodeTM(target, indentLevel); 	

	}

	

	CameraState cs;

	TimeValue t = GetStaticFrame();

	Interval valid = FOREVER;

	// Get animation range

	Interval animRange = ip->GetAnimRange();

	

	ObjectState os = node->EvalWorldState(t);

	CameraObject *cam = (CameraObject *)os.obj;

	

	cam->EvalCameraState(t,valid,&cs);

	

	ExportCameraSettings(&cs, cam, t, indentLevel);

 

	

	WriteHsfCamera(node, target, &cs, cam,t);

 	

	// Export animated camera settings

	if (!valid.InInterval(animRange) && GetIncludeCamLightAnim()) {



		FPRINTF(pStream,"%s\t%s {\n", indent.data(), ID_CAMERA_ANIMATION);



		TimeValue t = animRange.Start();

		

		while (1) {

			valid = FOREVER; // Extend the validity interval so the camera can shrink it.

			cam->EvalCameraState(t,valid,&cs);



			t = valid.Start() < animRange.Start() ? animRange.Start() : valid.Start();

			

			// Export the camera settings at this frame

			ExportCameraSettings(&cs, cam, t, indentLevel+1);

			

			if (valid.End() >= animRange.End()) {

				break;

			}

			else {

				t = (valid.End()/GetTicksPerFrame()+GetMeshFrameStep()) * GetTicksPerFrame();

			}

		}



		FPRINTF(pStream,"%s\t}\n", indent.data());

	}

	

	// Export animation keys for the light node

	if (GetIncludeAnim()) {

		ExportAnimKeys(node, indentLevel);

		

		// If we have a target, export animation keys for the target too.

		if (target) {

			ExportAnimKeys(target, indentLevel, true);

		}

	}

	

	FPRINTF(pStream,"%s}\n", indent.data());

}



void HsfExp::ExportCameraSettings(CameraState* cs, CameraObject* cam, TimeValue t, int indentLevel)

{

	TSTR indent = GetIndent(indentLevel);



	FPRINTF(pStream,"%s\t%s {\n", indent.data(), ID_CAMERA_SETTINGS);



	// Frame #

	FPRINTF(pStream, "%s\t\t%s %d\n", indent.data(), ID_TIMEVALUE, t);



	if (cs->manualClip) {

		FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_CAMERA_HITHER, Format(cs->hither));

		FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_CAMERA_YON, Format(cs->yon));

	}



	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_CAMERA_NEAR, Format(cs->nearRange));

	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_CAMERA_FAR, Format(cs->farRange));

	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_CAMERA_FOV, Format(cs->fov));

	FPRINTF(pStream,"%s\t\t%s %s\n", indent.data(), ID_CAMERA_TDIST, Format(cam->GetTDist(t)));



	FPRINTF(pStream,"%s\t}\n",indent.data());

}





/****************************************************************************



  Helper object output

  

****************************************************************************/



void HsfExp::ExportHelperObject(INode* node, int indentLevel)

{

	TSTR indent = GetIndent(indentLevel);

	ExportNodeHeader(node, ID_HELPER, indentLevel);

	 



	// We don't really know what kind of helper this is, but by exporting

	// the Classname of the helper object, the importer has a chance to

	// identify it.

	Object* helperObj = node->EvalWorldState(0).obj;

	if (helperObj) {

		TSTR className;

		helperObj->GetClassName(className);

		FPRINTF(pStream,"%s\t%s \"%s\"\n", indent.data(), ID_HELPER_CLASS, className);

	}



	ExportNodeTM(node, indentLevel);

	ExportHsfMatrix(node);

	

	if (helperObj) {

		TimeValue	t = GetStaticFrame();

		Matrix3		oTM = node->GetObjectTM(t);

		Box3		bbox;



		helperObj->GetDeformBBox(t, bbox, &oTM);



		FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_BOUNDINGBOX_MIN, Format(bbox.pmin));

		FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_BOUNDINGBOX_MAX, Format(bbox.pmax));

	}



	if (GetIncludeAnim()) {

		ExportAnimKeys(node, indentLevel);

	}

	

	FPRINTF(pStream,"%s}\n", indent.data());

}





/****************************************************************************



  Node Header

  

****************************************************************************/



// The Node Header consists of node type (geometry, helper, camera etc.)

// node name and parent node

void HsfExp::ExportNodeHeader(INode* node, TCHAR* type, int indentLevel)

{

	TSTR indent = GetIndent(indentLevel);

	

	// Output node header and object type 

	FPRINTF(pStream,"%s%s {\n", indent.data(), type);

	

	// Node name

	FPRINTF(pStream,"%s\t%s \"%s\"\n", indent.data(), ID_NODE_NAME, FixupName(node->GetName()));

	

	//  If the node is linked, export parent node name

	INode* parent = node->GetParentNode();

	if (parent && !parent->IsRootNode()) {

		FPRINTF(pStream,"%s\t%s \"%s\"\n", indent.data(), ID_NODE_PARENT, FixupName(parent->GetName()));

	}

}





/****************************************************************************



  Node Transformation

  

****************************************************************************/



void HsfExp::ExportNodeTM(INode* node, int indentLevel)

{

	Matrix3 pivot = node->GetNodeTM(GetStaticFrame());

	TSTR indent = GetIndent(indentLevel);

	

	FPRINTF(pStream,"%s\t%s {\n", indent.data(), ID_NODE_TM);

	

	// Node name

	// We export the node name together with the nodeTM, because some objects

	// (like a camera or a spotlight) has an additional node (the target).

	// In that case the nodeTM and the targetTM is exported after eachother

	// and the nodeName is how you can tell them apart.

	FPRINTF(pStream,"%s\t\t%s \"%s\"\n", indent.data(), ID_NODE_NAME, FixupName(node->GetName()));



	// Export TM inheritance flags

	DWORD iFlags = node->GetTMController()->GetInheritanceFlags();

	FPRINTF(pStream,"%s\t\t%s %d %d %d\n", indent.data(), ID_INHERIT_POS,

		INHERIT_POS_X & iFlags ? 1 : 0,

		INHERIT_POS_Y & iFlags ? 1 : 0,

		INHERIT_POS_Z & iFlags ? 1 : 0);



	FPRINTF(pStream,"%s\t\t%s %d %d %d\n", indent.data(), ID_INHERIT_ROT,

		INHERIT_ROT_X & iFlags ? 1 : 0,

		INHERIT_ROT_Y & iFlags ? 1 : 0,

		INHERIT_ROT_Z & iFlags ? 1 : 0);



	FPRINTF(pStream,"%s\t\t%s %d %d %d\n", indent.data(), ID_INHERIT_SCL,

		INHERIT_SCL_X & iFlags ? 1 : 0,

		INHERIT_SCL_Y & iFlags ? 1 : 0,

		INHERIT_SCL_Z & iFlags ? 1 : 0);



	// Dump the full matrix

	DumpMatrix3(&pivot, indentLevel+2);

	

	FPRINTF(pStream,"%s\t}\n", indent.data());

}



/****************************************************************************



  Animation output

  

****************************************************************************/



// If the object is animated, then we will output the entire mesh definition

// for every specified frame. This can result in, dare I say, rather large files.

//

// Many target systems (including MAX itself!) cannot always read back this

// information. If the objects maintains the same number of verices it can be

// imported as a morph target, but if the number of vertices are animated it

// could not be read back in withou special tricks.

// Since the target system for this exporter is unknown, it is up to the

// user (or developer) to make sure that the data conforms with the target system.



void HsfExp::ExportAnimMesh(INode* node, int indentLevel)

{

	ObjectState os = node->EvalWorldState(GetStaticFrame());

	if (!os.obj)

		return;

	

	TSTR indent = GetIndent(indentLevel);

	

	// Get animation range

	Interval animRange = ip->GetAnimRange();

	// Get validity of the object

	Interval objRange = os.obj->ObjectValidity(GetStaticFrame());

	

	// If the animation range is not fully included in the validity

	// interval of the object, then we're animated.

	if (!objRange.InInterval(animRange)) {

		

		FPRINTF(pStream,"%s\t%s {\n", indent.data(), ID_MESH_ANIMATION);

		

		TimeValue t = animRange.Start();

		

		while (1) {

			// This may seem strange, but the object in the pipeline

			// might not be valid anymore.

			os = node->EvalWorldState(t);

			objRange = os.obj->ObjectValidity(t);

			t = objRange.Start() < animRange.Start() ? animRange.Start() : objRange.Start();

			

			// Export the mesh definition at this frame

			ExportMesh(node, t, indentLevel+1);

			

			if (objRange.End() >= animRange.End()) {

				break;

			}

			else {

				t = (objRange.End()/GetTicksPerFrame()+GetMeshFrameStep()) * GetTicksPerFrame();

			}

		}

		FPRINTF(pStream,"%s\t}\n", indent.data());

	}

}






class TK_My_Shell: public TK_Shell
{
public:
    TK_My_Shell():TK_Shell() { };
    ~TK_My_Shell(){ Reset(); };

    TK_Status Interpret (BStreamFileToolkit & tk, long key, int lod) alter 
    {
        TK_Status status = TK_Normal;
	    int flags = tk.GetWriteFlags();

  
         InitSubop( tk, lod, true );
    // set flags in mp_subop specific to lodlevel 0

        if(!( flags & TK_Full_Resolution_Vertices ) )

            mp_subop |= TKSH_COMPRESSED_POINTS;
 
 
//		 SetSubop(GetSubop() | TKSH_CONNECTIVITY_COMPRESSION);
  //      SetSubop( GetSubop() & ~TKSH_TRISTRIPS );

        /* Uncomment the following line if your database has good tristrips that you'd like 
         * to use as the face list */
        //SetSubop( TKSH_TRISTRIPS | GetSubop() );
        SetLodLevel( 0 );
       // SetKey( tk, key );
        
        return status;
    }

    /* Here we clean up the mess we might have made with non-shell LODs. */
    void Reset() {
        BBaseOpcodeHandler *handler;
        while((handler = PopObject()) != NULL) {
            delete handler;
        }
        TK_Shell::Reset();
    }
	void SetShellFaces(int flen, int *faces)
	{
		SetFaces(flen, faces);
	}

};


void HsfExp::OptimizeAndWrite(Mesh *mesh, int origpnum, int pnum, int facenum, float *points, int *pmap, int *faces,  float *normals, bool *normalspecified,float *texcoords)

{

 	int *pmap2 = new int[pnum];

	int *pmap3 = new int[pnum];

	for (int i=0;i<pnum;i++)

	{

		pmap2[i] = -2;

  	}





	for (int i=0;i<facenum;i+=4)

	{

		for (int j=0;j<3;j++)

		{

			pmap2[faces[i+j+1]] = -1;

		}

	}



	int merged = 0;

	int totalpnum = pnum;
	if (totalpnum>100000)
		totalpnum = 0;

	for (int p=0;p<totalpnum;p++)

	{

		if (pmap2[p] == -1)

		{		

 			int comparepoint = p;

			int currentpoint;

			if (p<origpnum)

				currentpoint = origpnum;

			else

				currentpoint = p+1;

  		while (currentpoint<pnum)
		{

			if (pmap[currentpoint] == comparepoint && pmap2[currentpoint] == -1)

			{

				if ((!normals || (!normalspecified[currentpoint])) &&

					(!texcoords || (texcoords[currentpoint*3] == texcoords[comparepoint*3] && texcoords[currentpoint*3 + 1] == texcoords[comparepoint*3 + 1] &&

					texcoords[currentpoint*3 + 2] == texcoords[comparepoint*3 + 2])))

				{
					pmap2[currentpoint] = comparepoint;
					merged++;

				}

			}

			currentpoint++;

		}

		}

	}

	float *newpoints = new float[pnum*3];

	float *newnormals = 0;
	bool *newnormalspecified = 0;

	if (normals)
	{
		newnormals = new float[pnum*3];
		newnormalspecified = new bool[pnum];
	}
	float *newtexcoords = 0;

	if (texcoords)

		newtexcoords = new float[pnum*3];

	int newpnum = 0;

	for (int i=0;i<pnum;i++)

	{

		if (pmap2[i] == -1)

		{

			pmap3[i] = newpnum;

			newpoints[newpnum*3] = points[i *3];

			newpoints[newpnum*3 + 1] = points[i *3 + 1];

			newpoints[newpnum*3 + 2] = points[i *3 + 2];

			if (normals)

			{
				newnormalspecified[newpnum] = normalspecified[i];
				if (newnormalspecified[newpnum])
				{
					newnormals[newpnum*3] = normals[i *3];
					newnormals[newpnum*3 + 1] = normals[i *3 + 1];
					newnormals[newpnum*3 + 2] = normals[i *3 + 2];
				}
				else
				{
					newnormals[newpnum*3] = 0.0f;
					newnormals[newpnum*3+1] = 0.0f;
					newnormals[newpnum*3+2] = 0.0f;
				}

				


			}

			if (texcoords)

			{

				newtexcoords[newpnum*3] = texcoords[i *3];

				newtexcoords[newpnum*3 + 1] = texcoords[i *3 + 1];

				newtexcoords[newpnum*3 + 2] = texcoords[i *3 + 2];

			}

			newpnum++;			

		}

		else

		{

			if (pmap2[i] != -2)

				pmap3[i] = pmap3[pmap2[i]];

		}

	}
	int i;



	for (i=0;i<facenum;i+=4)

	{

		for (int j=0;j<3;j++)
		{
			faces[i+j+1] = pmap3[faces[i+j+1]];
		}

	}
	
	for (i=0;i<facenum;i+=4)
	{
		Point3 vertexNormal = mesh->getFaceNormal(i/4);
		for (int j=0;j<3;j++)
		{
			int index = faces[i+j+1];
			if (!newnormalspecified[index])
			{
				newnormals[index *3]+=vertexNormal.x;
				newnormals[index *3+1]+=vertexNormal.y;
				newnormals[index *3+2]+=vertexNormal.z;
			}
		}
	}

	for (i=0;i<newpnum;i++)
	{
		Point3 normal;
		normal.x = newnormals[i*3];
		normal.y = newnormals[i*3+1];
		normal.z = newnormals[i*3+2];
		normal.Normalize();
		newnormals[i*3] = normal.x;
		newnormals[i*3+1] = normal.y;
		newnormals[i*3+2] = normal.z;
	}
	delete [] newnormalspecified;

		



	TK_My_Shell *shell_handler= new TK_My_Shell;

	shell_handler->SetPoints(newpnum, newpoints);

	if (normals && 	GetIncludeNormals())

		shell_handler->SetVertexNormals(newnormals);

	if (texcoords)

		shell_handler->SetVertexParameters(newtexcoords);

	shell_handler->SetShellFaces(facenum, faces);

 	shell_handler->Interpret(*m_pStreamFileToolkit,-1,0);

	WriteObject(shell_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	delete shell_handler;




	delete [] newpoints;

	delete [] newnormals;

	delete [] newtexcoords;

	delete [] pmap3;

	delete [] pmap2;	 



}



			

















 void HsfExp::WriteShell(INode *node, TimeValue t)

{

  
	int i;

	Mtl* nodeMtl = node->GetMtl();

	Matrix3 tm = node->GetObjTMAfterWSM(t);

	BOOL negScale = TMNegParity(tm);

	int vx1, vx2, vx3;

	TSTR indent;

	Matrix3 pivot = node->GetNodeTM(GetStaticFrame());

	pivot.Invert();	

	ObjectState os = node->EvalWorldState(t);

	if (!os.obj || os.obj->SuperClassID()!=GEOMOBJECT_CLASS_ID) {

		return; // Safety net. This shouldn't happen.

	}

	

	// Order of the vertices. Get 'em counter clockwise if the objects is

	// negatively scaled.

	if (0) {

		vx1 = 2;

		vx2 = 1;

		vx3 = 0;

	}

	else {

		vx1 = 0;

		vx2 = 1;

		vx3 = 2;

	}

	

	BOOL needDel;

	TriObject* tri = GetTriObjectFromNode(node, t, needDel);

	if (!tri) {

		return;

	}

	

	Mesh* mesh = &tri->GetMesh();

	

	mesh->buildNormals();



	int maxpoints = mesh->getNumVerts();

	maxpoints += mesh->getNumFaces() * 3;

 	

	float *points = new float[maxpoints * 3];

	int *pmap = new int[maxpoints];

	for (i=0; i<mesh->getNumVerts(); i++) {



		Point3 v = tm * mesh->verts[i];

 		v = pivot * v;

		points[i*3] = v.x;

		points[i*3 + 1] = v.y;

		points[i*3 + 2] = v.z;

		pmap[i] = -1;

 	}



 	int pnum = mesh->getNumVerts();

	// To determine visibility of a face, get the vertices in clockwise order.

	// If the objects has a negative scaling, we must compensate for that by

	// taking the vertices counter clockwise

	int *faces = new int[mesh->getNumFaces() * 4];

	int flen = 0;

	int *facematerials = new int[mesh->getNumFaces()];

	int *facemap = new int[mesh->getNumFaces()];

	int numsubfaces = 0;



 	for (i=0; i<mesh->getNumFaces(); i++) {



 		if (nodeMtl && nodeMtl->ClassID() == Class_ID(MULTI_CLASS_ID, 0)) 

		  facematerials[i] = mesh->faces[i].getMatID() % nodeMtl->NumSubMtls();

		else

			facematerials[i] = 0;

		if (facematerials[i] > numsubfaces)

			numsubfaces = facematerials[i];

		facemap[i] = flen + 1;

		faces[flen++] = 3;

		for (int j=0;j<3;j++)

		{

			int vx;

			switch(j)

			{

			case 0: 

				vx = vx1;

				break;

			case 1:

				vx = vx2;

					break;

			case 2:

				vx = vx3;

				break;

			}

				

  			if (pmap[mesh->faces[i].v[vx]] == -1)

			{

				faces[flen++] = 	mesh->faces[i].v[vx];
				pmap[mesh->faces[i].v[vx]] = mesh->faces[i].v[vx];

			}

			else

			{

				faces[flen++] = pnum;

				pmap[pnum] = mesh->faces[i].v[vx];

				points[pnum*3] = points[pmap[pnum]*3];

				points[pnum*3+1] = points[pmap[pnum]*3+1];

				points[pnum*3+2] = points[pmap[pnum]*3+2];

				pnum++;

			}				

		}

	}	



 	



	float *normals =0;

	bool *normalspecified;

	if (1) { 		

	normals = new float[pnum*3];
	normalspecified = new bool[pnum];



		Point3 fn;  // Face normal

		Point3 vn;  // Vertex normal

		int  vert;

		Face* f;		

		// Face and vertex normals.

		// In MAX a vertex can have more than one normal (but doesn't always have it).

		// This is depending on the face you are accessing the vertex through.

		// To get all information we need to export all three vertex normals

		// for every face.


		for (i=0; i<mesh->getNumFaces(); i++) {

			f = &mesh->faces[i];			

			vert = f->getVert(vx1);

			vn = GetVertexNormal(mesh, i, mesh->getRVertPtr(vert), normalspecified[faces[facemap[i]+vx1]]);

			normals[faces[facemap[i]+vx1]*3] = vn.x;

			normals[faces[facemap[i]+vx1]*3+1] = vn.y;

			normals[faces[facemap[i]+vx1]*3+2] = vn.z;



 			vert = f->getVert(vx2);

			vn = GetVertexNormal(mesh, i, mesh->getRVertPtr(vert),normalspecified[faces[facemap[i]+vx2]]);

			normals[faces[facemap[i]+vx2]*3] = vn.x;

			normals[faces[facemap[i]+vx2]*3+1] = vn.y;

			normals[faces[facemap[i]+vx2]*3+2] = vn.z;



 			vert = f->getVert(vx3);

			vn = GetVertexNormal(mesh, i, mesh->getRVertPtr(vert),normalspecified[faces[facemap[i]+vx3]]);

			normals[faces[facemap[i]+vx3]*3] = vn.x;

			normals[faces[facemap[i]+vx3]*3+1] = vn.y;

			normals[faces[facemap[i]+vx3]*3+2] = vn.z;

		}

  	}

	

	float *texcoords = 0;



	// Export face map texcoords if we have them...

	if (GetIncludeTextureCoords() && !CheckForFaceMap(nodeMtl, mesh)) {

		// If not, export standard tverts

	texcoords = new float[pnum*3];



		int numTVx = mesh->getNumTVerts();



		if (numTVx) {

 



	for (i=0; i<mesh->getNumFaces(); i++) {

			TVFace* f;	

			int  vert;

			f = &mesh->tvFace[i];			

			vert = f->t[vx1];

			int vnum;

			vnum = faces[facemap[i]+vx1];

			texcoords[vnum*3] = mesh->tVerts[vert].x;

			texcoords[vnum*3+1] = mesh->tVerts[vert].y;

			texcoords[vnum*3+2] = mesh->tVerts[vert].z;



			vert = f->t[vx2];			

			vnum = faces[facemap[i]+vx2];

			texcoords[vnum*3] = mesh->tVerts[vert].x;

			texcoords[vnum*3+1] = mesh->tVerts[vert].y;

			texcoords[vnum*3+2] = mesh->tVerts[vert].z;



			vert = f->t[vx3];			

			vnum = faces[facemap[i]+vx3];

			texcoords[vnum*3] = mesh->tVerts[vert].x;

			texcoords[vnum*3+1] = mesh->tVerts[vert].y;

			texcoords[vnum*3+2] = mesh->tVerts[vert].z;





			}

 

		}

		}

 		for (i=0;i<=numsubfaces;i++)

		{

			int newfacelen = 0;

			int *breakfaces = new int[mesh->getNumFaces() * 4];

			for (int j=0;j<mesh->getNumFaces();j++)

			{

				if (facematerials[j] == i)

				{

					breakfaces[newfacelen++] = 3;

					breakfaces[newfacelen++] = faces[facemap[j]];

					breakfaces[newfacelen++] = faces[facemap[j]+1];

					breakfaces[newfacelen++] = faces[facemap[j]+2];

				}

			}

				bool hasTexture;

 				if (nodeMtl && nodeMtl->ClassID() == Class_ID(MULTI_CLASS_ID, 0)) 

				{

					WriteOpenSegment("");

					hasTexture = MaterialHasTexture(nodeMtl->GetSubMtl(i));

				}

				else

					hasTexture = MaterialHasTexture(nodeMtl);



				 if (hasTexture)
 					OptimizeAndWrite(mesh, mesh->getNumVerts(), pnum, newfacelen, points, pmap, breakfaces, normals,normalspecified,texcoords);

				 else

 					OptimizeAndWrite(mesh, mesh->getNumVerts(), pnum, newfacelen, points, pmap, breakfaces, normals,normalspecified,0);



//				TK_My_Shell *shell_handler= new TK_My_Shell;

//				shell_handler->SetPoints(pnum, points);

//				shell_handler->SetVertexNormals(normals);

//				shell_handler->SetVertexParameters(texcoords);

//				shell_handler->SetShellFaces(newfacelen, breakfaces);

//			    WriteObject(shell_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
//				delete shell_handler;
				delete [] breakfaces;
  				

		 		if (nodeMtl && nodeMtl->ClassID() == Class_ID(MULTI_CLASS_ID, 0)) 

				{



				int mtlID = mtlList.GetMtlID(nodeMtl);

				ReferenceSubMaterial(mtlID, i);
 				WriteCloseSegment();
				}
		}


	 

 	delete [] points;

	delete [] normals;

	delete [] normalspecified;

	delete [] texcoords;

	delete [] pmap;

	delete [] faces;

	delete [] facematerials;

	delete [] facemap;

	if (needDel) {

		delete tri;

	}

 //	delete shell_handler;
}




bool HsfExp::MaterialHasTexture(Mtl *mtl)

{

int i;

if (mtl)

{

for (i=0; i<mtl->NumSubTexmaps(); i++) {

		if (strcmp(GetMapID( mtl->ClassID(),i), ID_MAP_DIFFUSE) == 0 || strcmp(GetMapID( mtl->ClassID(),i), ID_MAP_BUMP) == 0 || (strcmp(GetMapID( mtl->ClassID(),i), ID_MAP_REFLECT) == 0) && !GetDisableEnv())

		{

			Texmap* subTex = mtl->GetSubTexmap(i);

			if (subTex) 

				return true;

		}

	}

}

return false;

}





/****************************************************************************



  Mesh output

  

****************************************************************************/



void HsfExp::ExportMesh(INode* node, TimeValue t, int indentLevel)

{



	WriteShell(node,t);



	int i;

	Mtl* nodeMtl = node->GetMtl();

	Matrix3 tm = node->GetObjTMAfterWSM(t);

	BOOL negScale = TMNegParity(tm);

	int vx1, vx2, vx3;

	TSTR indent;

	

	indent = GetIndent(indentLevel+1);

	

	ObjectState os = node->EvalWorldState(t);

	if (!os.obj || os.obj->SuperClassID()!=GEOMOBJECT_CLASS_ID) {

		return; // Safety net. This shouldn't happen.

	}

	

	// Order of the vertices. Get 'em counter clockwise if the objects is

	// negatively scaled.

	if (negScale) {

		vx1 = 2;

		vx2 = 1;

		vx3 = 0;

	}

	else {

		vx1 = 0;

		vx2 = 1;

		vx3 = 2;

	}

	

	BOOL needDel;

	TriObject* tri = GetTriObjectFromNode(node, t, needDel);

	if (!tri) {

		return;

	}

	

	Mesh* mesh = &tri->GetMesh();

	

	mesh->buildNormals();

	

	FPRINTF(pStream, "%s%s {\n",indent.data(),  ID_MESH);

	FPRINTF(pStream, "%s\t%s %d\n",indent.data(), ID_TIMEVALUE, t);

	FPRINTF(pStream, "%s\t%s %d\n",indent.data(), ID_MESH_NUMVERTEX, mesh->getNumVerts());

    FPRINTF(pStream, "%s\t%s %d\n",indent.data(), ID_MESH_NUMFACES, mesh->getNumFaces());

	

	// Export the vertices

	FPRINTF(pStream,"%s\t%s {\n",indent.data(), ID_MESH_VERTEX_LIST);

	for (i=0; i<mesh->getNumVerts(); i++) {

		Point3 v = tm * mesh->verts[i];

		FPRINTF(pStream, "%s\t\t%s %4d\t%s\n",indent.data(), ID_MESH_VERTEX, i, Format(v));

	}

	FPRINTF(pStream,"%s\t}\n",indent.data()); // End vertex list

	

	// To determine visibility of a face, get the vertices in clockwise order.

	// If the objects has a negative scaling, we must compensate for that by

	// taking the vertices counter clockwise

	FPRINTF(pStream, "%s\t%s {\n",indent.data(), ID_MESH_FACE_LIST);

	for (i=0; i<mesh->getNumFaces(); i++) {

		FPRINTF(pStream,"%s\t\t%s %4d:    A: %4d B: %4d C: %4d AB: %4d BC: %4d CA: %4d",

			indent.data(),

			ID_MESH_FACE, i,

			mesh->faces[i].v[vx1],

			mesh->faces[i].v[vx2],

			mesh->faces[i].v[vx3],

			mesh->faces[i].getEdgeVis(vx1) ? 1 : 0,

			mesh->faces[i].getEdgeVis(vx2) ? 1 : 0,

			mesh->faces[i].getEdgeVis(vx3) ? 1 : 0);

		FPRINTF(pStream,"\t %s ", ID_MESH_SMOOTHING);

		for (int j=0; j<32; j++) {

			if (mesh->faces[i].smGroup & (1<<j)) {

				if (mesh->faces[i].smGroup>>(j+1)) {

					FPRINTF(pStream,"%d,",j+1); // Add extra comma

				} else {

					FPRINTF(pStream,"%d ",j+1);

				}

			}

		}

		

		// This is the material ID for the face.

		// Note: If you use this you should make sure that the material ID

		// is not larger than the number of sub materials in the material.

		// The standard approach is to use a modulus function to bring down

		// the material ID.

		int num;

		if (nodeMtl && nodeMtl->ClassID() == Class_ID(MULTI_CLASS_ID, 0)) 

		  num = mesh->faces[i].getMatID() % nodeMtl->NumSubMtls();

		else

			num = 0;





		FPRINTF(pStream,"\t%s %d", ID_MESH_MTLID, num);

		

		FPRINTF(pStream,"\n");

	}

	FPRINTF(pStream,"%s\t}\n", indent.data()); // End face list

	

	// Export face map texcoords if we have them...

	if (GetIncludeTextureCoords() && !CheckForAndExportFaceMap(nodeMtl, mesh, indentLevel+1)) {

		// If not, export standard tverts

		int numTVx = mesh->getNumTVerts();



		FPRINTF(pStream, "%s\t%s %d\n",indent.data(), ID_MESH_NUMTVERTEX, numTVx);



		if (numTVx) {

			FPRINTF(pStream,"%s\t%s {\n",indent.data(), ID_MESH_TVERTLIST);

			for (i=0; i<numTVx; i++) {

				UVVert tv = mesh->tVerts[i];

				FPRINTF(pStream, "%s\t\t%s %d\t%s\n",indent.data(), ID_MESH_TVERT, i, Format(tv));

			}

			FPRINTF(pStream,"%s\t}\n",indent.data());

			

			FPRINTF(pStream, "%s\t%s %d\n",indent.data(), ID_MESH_NUMTVFACES, mesh->getNumFaces());



			FPRINTF(pStream, "%s\t%s {\n",indent.data(), ID_MESH_TFACELIST);

			for (i=0; i<mesh->getNumFaces(); i++) {

				FPRINTF(pStream,"%s\t\t%s %d\t%d\t%d\t%d\n",

					indent.data(),

					ID_MESH_TFACE, i,

					mesh->tvFace[i].t[vx1],

					mesh->tvFace[i].t[vx2],

					mesh->tvFace[i].t[vx3]);

			}

			FPRINTF(pStream, "%s\t}\n",indent.data());

		}



		// CCJ 3/9/99

		// New for R3 - Additional mapping channels

		for (int mp = 2; mp < MAX_MESHMAPS-1; mp++) {

			if (mesh->mapSupport(mp)) {



				FPRINTF(pStream, "%s\t%s %d {\n",indent.data(), ID_MESH_MAPPINGCHANNEL, mp);





				int numTVx = mesh->getNumMapVerts(mp);

				FPRINTF(pStream, "%s\t\t%s %d\n",indent.data(), ID_MESH_NUMTVERTEX, numTVx);



				if (numTVx) {

					FPRINTF(pStream,"%s\t\t%s {\n",indent.data(), ID_MESH_TVERTLIST);

					for (i=0; i<numTVx; i++) {

						UVVert tv = mesh->mapVerts(mp)[i];

						FPRINTF(pStream, "%s\t\t\t%s %d\t%s\n",indent.data(), ID_MESH_TVERT, i, Format(tv));

					}

					FPRINTF(pStream,"%s\t\t}\n",indent.data());

					

					FPRINTF(pStream, "%s\t\t%s %d\n",indent.data(), ID_MESH_NUMTVFACES, mesh->getNumFaces());



					FPRINTF(pStream, "%s\t\t%s {\n",indent.data(), ID_MESH_TFACELIST);

					for (i=0; i<mesh->getNumFaces(); i++) {

						FPRINTF(pStream,"%s\t\t\t%s %d\t%d\t%d\t%d\n",

							indent.data(),

							ID_MESH_TFACE, i,

							mesh->mapFaces(mp)[i].t[vx1],

							mesh->mapFaces(mp)[i].t[vx2],

							mesh->mapFaces(mp)[i].t[vx3]);

					}

					FPRINTF(pStream, "%s\t\t}\n",indent.data());

				}

				FPRINTF(pStream, "%s\t}\n",indent.data());

			}

		}

	}



	// Export color per vertex info

	if (GetIncludeVertexColors()) {

		int numCVx = mesh->numCVerts;



		FPRINTF(pStream, "%s\t%s %d\n",indent.data(), ID_MESH_NUMCVERTEX, numCVx);

		if (numCVx) {

			FPRINTF(pStream,"%s\t%s {\n",indent.data(), ID_MESH_CVERTLIST);

			for (i=0; i<numCVx; i++) {

				Point3 vc = mesh->vertCol[i];

				FPRINTF(pStream, "%s\t\t%s %d\t%s\n",indent.data(), ID_MESH_VERTCOL, i, Format(vc));

			}

			FPRINTF(pStream,"%s\t}\n",indent.data());

			

			FPRINTF(pStream, "%s\t%s %d\n",indent.data(), ID_MESH_NUMCVFACES, mesh->getNumFaces());



			FPRINTF(pStream, "%s\t%s {\n",indent.data(), ID_MESH_CFACELIST);

			for (i=0; i<mesh->getNumFaces(); i++) {

				FPRINTF(pStream,"%s\t\t%s %d\t%d\t%d\t%d\n",

					indent.data(),

					ID_MESH_CFACE, i,

					mesh->vcFace[i].t[vx1],

					mesh->vcFace[i].t[vx2],

					mesh->vcFace[i].t[vx3]);

			}

			FPRINTF(pStream, "%s\t}\n",indent.data());

		}

	}

	

	if (GetIncludeNormals()) {

		// Export mesh (face + vertex) normals

		FPRINTF(pStream, "%s\t%s {\n",indent.data(), ID_MESH_NORMALS);

		

		Point3 fn;  // Face normal

		Point3 vn;  // Vertex normal

		int  vert;

		Face* f;

		

		// Face and vertex normals.

		// In MAX a vertex can have more than one normal (but doesn't always have it).

		// This is depending on the face you are accessing the vertex through.

		// To get all information we need to export all three vertex normals

		// for every face.

		for (i=0; i<mesh->getNumFaces(); i++) {

			f = &mesh->faces[i];

			fn = mesh->getFaceNormal(i);

			FPRINTF(pStream,"%s\t\t%s %d\t%s\n", indent.data(), ID_MESH_FACENORMAL, i, Format(fn));

			
			bool spec;
			vert = f->getVert(vx1);

			vn = GetVertexNormal(mesh, i, mesh->getRVertPtr(vert), spec);

			FPRINTF(pStream,"%s\t\t\t%s %d\t%s\n",indent.data(), ID_MESH_VERTEXNORMAL, vert, Format(vn));

			

			vert = f->getVert(vx2);

			vn = GetVertexNormal(mesh, i, mesh->getRVertPtr(vert), spec);

			FPRINTF(pStream,"%s\t\t\t%s %d\t%s\n",indent.data(), ID_MESH_VERTEXNORMAL, vert, Format(vn));

			

			vert = f->getVert(vx3);

			vn = GetVertexNormal(mesh, i, mesh->getRVertPtr(vert), spec);

			FPRINTF(pStream,"%s\t\t\t%s %d\t%s\n",indent.data(), ID_MESH_VERTEXNORMAL, vert, Format(vn));

		}

		

		FPRINTF(pStream, "%s\t}\n",indent.data());

	}

	

	FPRINTF(pStream, "%s}\n",indent.data());

	

	if (needDel) {

		delete tri;

	}

}



Point3 HsfExp::GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv, bool &normalspecified)

{

	Face* f = &mesh->faces[faceNo];

	DWORD smGroup = f->smGroup;

	int numNormals;

	Point3 vertexNormal;

	normalspecified = false;

	// Is normal specified

	// SPCIFIED is not currently used, but may be used in future versions.

	if (rv->rFlags & SPECIFIED_NORMAL) {
		vertexNormal = rv->rn.getNormal();
		normalspecified = true;

	}

	// If normal is not specified it's only available if the face belongs

	// to a smoothing group

 	else if ((numNormals = (rv->rFlags & NORCT_MASK)) != 0 && smGroup) {

		// If there is only one vertex is found in the rn member.

		if (numNormals == 1) {

			vertexNormal = rv->rn.getNormal();
			normalspecified = true;
		}

		else {

			// If two or more vertices are there you need to step through them

			// and find the vertex with the same smoothing group as the current face.

			// You will find multiple normals in the ern member.

			vertexNormal.Set(0,0,0);
			for (int i = 0; i < numNormals; i++) {

				if (rv->ern[i].getSmGroup() & smGroup) {

					Point3 temp = rv->ern[i].getNormal();
					vertexNormal.x+=temp.x;
					vertexNormal.y+=temp.y;
					vertexNormal.z+=temp.z;
					normalspecified = true;
					break;
				}

			}

		}

	}

	else {

		// Get the normal from the Face if no smoothing groups are there	
		vertexNormal = mesh->getFaceNormal(faceNo);

	}

	vertexNormal.FNormalize();

	return vertexNormal;

}



/****************************************************************************



  Inverse Kinematics (IK) Joint information

  

****************************************************************************/



void HsfExp::ExportIKJoints(INode* node, int indentLevel)

{

	Control* cont;

	TSTR indent = GetIndent(indentLevel);



	if (node->TestAFlag(A_INODE_IK_TERMINATOR)) 

		FPRINTF(pStream,"%s\t%s\n", indent.data(), ID_IKTERMINATOR);



	if(node->TestAFlag(A_INODE_IK_POS_PINNED))

		FPRINTF(pStream,"%s\t%s\n", indent.data(), ID_IKPOS_PINNED);



	if(node->TestAFlag(A_INODE_IK_ROT_PINNED))

		FPRINTF(pStream,"%s\t%s\n", indent.data(), ID_IKROT_PINNED);



	// Position joint

	cont = node->GetTMController()->GetPositionController();

	if (cont) {

		JointParams* joint = (JointParams*)cont->GetProperty(PROPID_JOINTPARAMS);

		if (joint && !joint->IsDefault()) {

			// Has IK Joints!!!

			FPRINTF(pStream,"%s\t%s {\n", indent.data(), ID_IKJOINT);

			DumpJointParams(joint, indentLevel+1);

			FPRINTF(pStream,"%s\t}\n", indent.data());

		}

	}



	// Rotational joint

	cont = node->GetTMController()->GetRotationController();

	if (cont) {

		JointParams* joint = (JointParams*)cont->GetProperty(PROPID_JOINTPARAMS);

		if (joint && !joint->IsDefault()) {

			// Has IK Joints!!!

			FPRINTF(pStream,"%s\t%s {\n", indent.data(), ID_IKJOINT);

			DumpJointParams(joint, indentLevel+1);

			FPRINTF(pStream,"%s\t}\n", indent.data());

		}

	}

}



void HsfExp::DumpJointParams(JointParams* joint, int indentLevel)

{

	TSTR indent = GetIndent(indentLevel);

	float scale = joint->scale;



	FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_IKTYPE,   joint->Type() == JNT_POS ? ID_IKTYPEPOS : ID_IKTYPEROT);

	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_IKDOF,    joint->dofs);



	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_IKXACTIVE,  joint->flags & JNT_XACTIVE  ? 1 : 0);

	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_IKYACTIVE,  joint->flags & JNT_YACTIVE  ? 1 : 0);

	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_IKZACTIVE,  joint->flags & JNT_ZACTIVE  ? 1 : 0);



	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_IKXLIMITED, joint->flags & JNT_XLIMITED ? 1 : 0);

	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_IKYLIMITED, joint->flags & JNT_YLIMITED ? 1 : 0);

	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_IKZLIMITED, joint->flags & JNT_ZLIMITED ? 1 : 0);



	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_IKXEASE,    joint->flags & JNT_XEASE    ? 1 : 0);

	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_IKYEASE,    joint->flags & JNT_YEASE    ? 1 : 0);

	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_IKZEASE,    joint->flags & JNT_ZEASE    ? 1 : 0);



	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_IKLIMITEXACT, joint->flags & JNT_LIMITEXACT ? 1 : 0);



	for (int i=0; i<joint->dofs; i++) {

		FPRINTF(pStream,"%s\t%s %d %s %s %s\n", indent.data(), ID_IKJOINTINFO, i, Format(joint->min[i]), Format(joint->max[i]), Format(joint->damping[i]));

	}



}



/****************************************************************************



  Material and Texture Export

  

****************************************************************************/



void HsfExp::ExportMaterialList()

{

	if (!GetIncludeMtl()) {

		return;

	}



	FPRINTF(pStream, "%s {\n", ID_MATERIAL_LIST);



	int numMtls = mtlList.Count();

	FPRINTF(pStream, "\t%s %d\n", ID_MATERIAL_COUNT, numMtls);

	WriteOpenSegment("styles");

	for (int i=0; i<numMtls; i++) {

		if (!bSaveImages || (bSaveImages == bSaveColors))
			DumpMaterial(mtlList.GetMtl(i), i, -1, 0);
		DumpHSFMaterial(mtlList.GetMtl(i), i, -1);

	}

	WriteCloseSegment();



	FPRINTF(pStream, "}\n");

}



void HsfExp::ReferenceSubMaterial(int mat, int submat)

{

	char name[4096];

	char subname[4096];

	





  	Mtl *temp = mtlList.GetMtl(mat);
	strcpy(name, FixupName(temp->GetName()));

	if (temp->GetSubMtl(submat))

	{

	strcpy(subname, FixupName(temp->GetSubMtl(submat)->GetName()));


	char text[4096];
 	char text2[4096];
 
	sprintf(text2, "styles/%s/%s", name,subname);
	CreateRelativePath(text, text2);

 //	WriteUserOptions(text);
   

     TK_Referenced_Segment *style_handler = new TK_Referenced_Segment(TKE_Style_Segment);

 //	sprintf(text, "/Material/%d/%d", mat, submat);

	style_handler->SetSegment(text);

    WriteObject(style_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
     TK_Referenced_Segment *style_handler2 = new TK_Referenced_Segment(TKE_Style_Segment);
	
	CreateRelativePath(text, "styles/textures");
 
 	style_handler2->SetSegment(text);

    WriteObject(style_handler2, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);

//	WriteUserOptions(text);

	delete style_handler;
	delete style_handler2;
	}
}



void HsfExp::ReferenceMaterial(INode *node)

{



 	Mtl* temp = node->GetMtl();

 	char text[4096];
 	char text2[4096];
 
	sprintf(text2, "styles/%s", FixupName(temp->GetName()));
	CreateRelativePath(text, text2);

 //	WriteUserOptions(text);
	Mtl* mtl = node->GetMtl();

	int mtlID = mtlList.GetMtlID(mtl);



     TK_Referenced_Segment *style_handler = new TK_Referenced_Segment(TKE_Style_Segment);

 //	sprintf(text, "/Material/%d", mtlID);

	style_handler->SetSegment(text);

    WriteObject(style_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	delete style_handler;



}



void HsfExp::ExportMaterial(INode* node, int indentLevel)

{

	Mtl* mtl = node->GetMtl();

	

	TSTR indent = GetIndent(indentLevel);

	

	// If the node does not have a material, export the wireframe color

	if (mtl) {

		int mtlID = mtlList.GetMtlID(mtl);

		if (mtlID >= 0) {

			FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_MATERIAL_REF, mtlID);

			ReferenceMaterial(node);

		}

	}

	else {

		DWORD c = node->GetWireColor();
		
		Color x(GetRValue(c)/255.0f, GetGValue(c)/255.0f, GetBValue(c)/255.0f);
		WriteSimpleColor(x);

		FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_WIRECOLOR,

			Format(Color(GetRValue(c)/255.0f, GetGValue(c)/255.0f, GetBValue(c)/255.0f)));

	}

}





void HsfExp::WriteSimpleColor(Color d)
{
	TimeValue t = GetStaticFrame();


 
    TK_Color *color_handler = new TK_Color();

    color_handler->SetGeometry(TKO_Geo_Face | TKO_Geo_Line);

 	color_handler->SetDiffuse(d);
	color_handler->SetChannels((1<<TKO_Channel_Diffuse));

     WriteObject(color_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	delete color_handler;
}

void HsfExp::WriteColor(Mtl *mtl, const char *texnamediffuse, const char *texnamereflection, const char *texnamebump)

{
	long channels = (1<<TKO_Channel_Diffuse) | (1<<TKO_Channel_Transmission) | (1<<TKO_Channel_Specular);
 
	TimeValue t = GetStaticFrame();



	Color d,e,s;

	d = mtl->GetDiffuse(t);

	s = mtl->GetSpecular(t);

    TK_Color *color_handler = new TK_Color();

    color_handler->SetGeometry(TKO_Geo_Face | TKO_Geo_Line);

	float transparency = mtl->GetXParency();
 


	if (texnamereflection && strcmp(texnamereflection, "") != 0)

	{
 

 		color_handler->SetEnvironmentName(texnamereflection);

	//	if (GetSpecForEnv())
//
//			color_handler->SetMirror(s);
//
//		else

			color_handler->SetMirrorName("(r = 0.3 g = 0.3 b = 0.3)");

	}

	if (texnamebump && strcmp(texnamebump, "") != 0)

	{
	 	
 		color_handler->SetBumpName(texnamebump);
		channels |= (1<<TKO_Channel_Bump);
	}



	if (texnamediffuse && strcmp(texnamediffuse, "") != 0)

	{

 

		char text[4096];

		if (transparency>0.0)

			sprintf(text,"faces = (diffuse = %s (r=%f g=%f b=%f, transmission = (r = %f g = %f b = %f))", texnamediffuse,d.r,d.g,d.b, transparency, transparency, transparency);

		else

			sprintf(text,"faces = %s", texnamediffuse);


		color_handler->SetDiffuseName(texnamediffuse);

	}

	else

	{
 
 		color_handler->SetDiffuse(d);

	}

	

 	color_handler->SetSpecular(s);



 	Color tr;

	tr.r = tr.g = tr.b = transparency;

	color_handler->SetTransmission(tr);

 	

	if (texnamereflection && strcmp(texnamereflection, "") != 0)

	{
 
		if (1)

			color_handler->SetChannels((1<<TKO_Channel_Mirror) | (1<<TKO_Channel_Environment) | (1<<TKO_Channel_Diffuse) | (1<<TKO_Channel_Transmission) | (1<<TKO_Channel_Specular) | (1 << TKO_Channel_Extended));

		else

			color_handler->SetChannels((1<<TKO_Channel_Mirror) | (1<<TKO_Channel_Environment) | (1<<TKO_Channel_Diffuse) | (1<<TKO_Channel_Specular) | (1 << TKO_Channel_Extended));

	}

	else

	{
 
			color_handler->SetChannels(channels);			

	}

    WriteObject(color_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	delete color_handler;
}

void HsfExp::WriteUserOptions(const char *text)

{

    TK_User_Options *user_options_handler = new TK_User_Options();

	user_options_handler->SetOptions(text);

    WriteObject(user_options_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	delete user_options_handler;
}





void HsfExp::DumpHSFMaterial(Mtl* mtl, int mtlID, int subNo)

{

	int i;

	TimeValue t = GetStaticFrame();

	

	if (!mtl) return;

		

	TSTR className;

	mtl->GetClassName(className);

		

	char name[4096];	



	if (subNo == -1) {

		sprintf(name,"%d", mtlID);

	}

	else {

		sprintf(name,"%d", subNo);

	}



	WriteOpenSegment(FixupName(mtl->GetName()));

	WriteUserOptions(FixupName(mtl->GetName()));

	char textname[4096];

	strcpy(textname, FixupName(mtl->GetName()));

	if (!bSaveImages)
	{
	char stext[4096];
   TK_Referenced_Segment *style_handler = new TK_Referenced_Segment(TKE_Style_Segment);
	CreateRelativePath(stext, "styles/textures");
 
 	style_handler->SetSegment(stext);

     WriteObject(style_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
	}
  	

	char texnamedif[4096];

	strcpy(texnamedif, "");

	char texnameref[4096];

	strcpy(texnameref, "");

	char texnamebump[4096];

	strcpy(texnamebump, "");
	

	bool do_one_only = false;

	for (i=0; i<mtl->NumSubTexmaps(); i++) {

		if (strcmp(GetMapID( mtl->ClassID(),i), ID_MAP_DIFFUSE) == 0 || strcmp(GetMapID( mtl->ClassID(),i), ID_MAP_BUMP) == 0 || ((strcmp(GetMapID( mtl->ClassID(),i), ID_MAP_REFLECT) == 0 || strcmp(GetMapID( mtl->ClassID(),i), ID_MAP_REFRACT) == 0) && !GetDisableEnv()))

		{

		Texmap* subTex = mtl->GetSubTexmap(i);

		float amt = 1.0f;

		if (subTex && !do_one_only) {

//			do_one_only = true;

			// If it is a standard material we can see if the map is enabled.

			if (mtl->ClassID() == Class_ID(DMTL_CLASS_ID, 0)) {

				if (!((StdMat*)mtl)->MapEnabled(i))

					continue;

				amt = ((StdMat*)mtl)->GetTexmapAmt(i, 0);

				

			}			

			if (GetIncludeObjTextures())

			{

// 			MessageBox(0,"start",0,0);
			bool dumped = false;
			if (bSaveImages)
					DumpHsfTexture(mtlID, subNo, subTex, mtl->ClassID(), i,amt, GetMapID( mtl->ClassID(),i), dumped);

			if (strcmp(GetMapID( mtl->ClassID(),i), ID_MAP_DIFFUSE) == 0)
				sprintf(texnamedif, "texdif%d",mcounter);
			else if (strcmp(GetMapID( mtl->ClassID(),i), ID_MAP_BUMP) == 0)
			{
				sprintf(texnamebump, "texbump%d", mcounter);
//							MessageBox(0,"Bump2",0,0);
			}

			else if (dumped)
				sprintf(texnameref, "texref%d", mcounter);

			}
// 			MessageBox(0,"end",0,0);



  		}

		}

	}



// We know the Standard material, so we can get some extra info

	if (bSaveColors)

	{

	if (mtl->ClassID() == Class_ID(DMTL_CLASS_ID, 0)) {

		StdMat* std = (StdMat*)mtl;

		WriteColor(std, texnamedif, texnameref, texnamebump);  		

 	}

	else {

		WriteColor(mtl, texnamedif, texnameref, texnamebump);  		

	}

	}

	mcounter++;

	if (mtl->NumSubMtls() > 0)  {	 	

		for (i=0; i<mtl->NumSubMtls(); i++) {

			Mtl* subMtl = mtl->GetSubMtl(i);

			if (subMtl) {

				DumpHSFMaterial(subMtl, 0, i);

			}

		}

	}

	

	WriteCloseSegment();





}





void HsfExp::DumpMaterial(Mtl* mtl, int mtlID, int subNo, int indentLevel)

{

	



	int i;

	TimeValue t = GetStaticFrame();

	

	if (!mtl) return;

	

	TSTR indent = GetIndent(indentLevel+1);

	

	TSTR className;

	mtl->GetClassName(className);

	

	

	if (subNo == -1) {

		// Top level material

		FPRINTF(pStream,"%s%s %d {\n",indent.data(), ID_MATERIAL, mtlID);

	}

	else {

		FPRINTF(pStream,"%s%s %d {\n",indent.data(), ID_SUBMATERIAL, subNo);

	}

	FPRINTF(pStream,"%s\t%s \"%s\"\n",indent.data(), ID_MATNAME, FixupName(mtl->GetName()));

	FPRINTF(pStream,"%s\t%s \"%s\"\n",indent.data(), ID_MATCLASS, FixupName(className));

	

	// We know the Standard material, so we can get some extra info

	if (mtl->ClassID() == Class_ID(DMTL_CLASS_ID, 0)) {

		StdMat* std = (StdMat*)mtl;



		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_AMBIENT, Format(std->GetAmbient(t)));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_DIFFUSE, Format(std->GetDiffuse(t)));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_SPECULAR, Format(std->GetSpecular(t)));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_SHINE, Format(std->GetShininess(t)));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_SHINE_STRENGTH, Format(std->GetShinStr(t)));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_TRANSPARENCY, Format(std->GetXParency(t)));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_WIRESIZE, Format(std->WireSize(t)));



		FPRINTF(pStream,"%s\t%s ", indent.data(), ID_SHADING);

		switch(std->GetShading()) {

		case SHADE_CONST: FPRINTF(pStream,"%s\n", ID_MAT_SHADE_CONST); break;

		case SHADE_PHONG: FPRINTF(pStream,"%s\n", ID_MAT_SHADE_PHONG); break;

		case SHADE_METAL: FPRINTF(pStream,"%s\n", ID_MAT_SHADE_METAL); break;

		case SHADE_BLINN: FPRINTF(pStream,"%s\n", ID_MAT_SHADE_BLINN); break;

		default: FPRINTF(pStream,"%s\n", ID_MAT_SHADE_OTHER); break;

		}

		

		FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_XP_FALLOFF, Format(std->GetOpacFalloff(t)));

		FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_SELFILLUM, Format(std->GetSelfIllum(t)));

		

		if (std->GetTwoSided()) {

			FPRINTF(pStream,"%s\t%s\n", indent.data(), ID_TWOSIDED);

		}

		

		if (std->GetWire()) {

			FPRINTF(pStream,"%s\t%s\n", indent.data(), ID_WIRE);

		}

		

		if (std->GetWireUnits()) {

			FPRINTF(pStream,"%s\t%s\n", indent.data(), ID_WIREUNITS);

		}

		

		FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_FALLOFF, std->GetFalloffOut() ? ID_FALLOFF_OUT : ID_FALLOFF_IN);

		

		if (std->GetFaceMap()) {

			FPRINTF(pStream,"%s\t%s\n", indent.data(), ID_FACEMAP);

		}

		

		if (std->GetSoften()) {

			FPRINTF(pStream,"%s\t%s\n", indent.data(), ID_SOFTEN);

		}

		

		FPRINTF(pStream,"%s\t%s ", indent.data(), ID_XP_TYPE);

		switch (std->GetTransparencyType()) {

		case TRANSP_FILTER: FPRINTF(pStream,"%s\n", ID_MAP_XPTYPE_FLT); break;

		case TRANSP_SUBTRACTIVE: FPRINTF(pStream,"%s\n", ID_MAP_XPTYPE_SUB); break;

		case TRANSP_ADDITIVE: FPRINTF(pStream,"%s\n", ID_MAP_XPTYPE_ADD); break;

		default: FPRINTF(pStream,"%s\n", ID_MAP_XPTYPE_OTH); break;

		}

	}

	else {

		// Note about material colors:

		// This is only the color used by the interactive renderer in MAX.

		// To get the color used by the scanline renderer, we need to evaluate

		// the material using the mtl->Shade() method.

		// Since the materials are procedural there is no real "diffuse" color for a MAX material

		// but we can at least take the interactive color.

		

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_AMBIENT, Format(mtl->GetAmbient()));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_DIFFUSE, Format(mtl->GetDiffuse()));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_SPECULAR, Format(mtl->GetSpecular()));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_SHINE, Format(mtl->GetShininess()));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_SHINE_STRENGTH, Format(mtl->GetShinStr()));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_TRANSPARENCY, Format(mtl->GetXParency()));

		FPRINTF(pStream,"%s\t%s %s\n",indent.data(), ID_WIRESIZE, Format(mtl->WireSize()));

	}



	for (i=0; i<mtl->NumSubTexmaps(); i++) {

		Texmap* subTex = mtl->GetSubTexmap(i);

		float amt = 1.0f;

		if (subTex) {

			// If it is a standard material we can see if the map is enabled.

			if (mtl->ClassID() == Class_ID(DMTL_CLASS_ID, 0)) {

				if (!((StdMat*)mtl)->MapEnabled(i))

					continue;

				amt = ((StdMat*)mtl)->GetTexmapAmt(i, 0);

				

			}

			DumpTexture(subTex, mtl->ClassID(), i, amt, indentLevel+1);

		}

	}

	

	if (mtl->NumSubMtls() > 0)  {

		FPRINTF(pStream,"%s\t%s %d\n",indent.data(), ID_NUMSUBMTLS, mtl->NumSubMtls());

		

		for (i=0; i<mtl->NumSubMtls(); i++) {

			Mtl* subMtl = mtl->GetSubMtl(i);

			if (subMtl) {

				DumpMaterial(subMtl, 0, i, indentLevel+1);

			}

		}

	}

	FPRINTF(pStream,"%s}\n", indent.data());

}





// For a standard material, this will give us the meaning of a map

// givien its submap id.

TCHAR* HsfExp::GetMapID(Class_ID cid, int subNo)

{

	static TCHAR buf[50];

	strcpy(buf,"");

	if (cid == Class_ID(0,0)) {

		strcpy(buf, ID_ENVMAP);

	}

	else if (cid == Class_ID(DMTL_CLASS_ID, 0)) {

 
		switch (subNo) {

		case ID_AM: strcpy(buf, ID_MAP_AMBIENT); break;

		case ID_DI: strcpy(buf, ID_MAP_DIFFUSE); break;

		case ID_SP: strcpy(buf, ID_MAP_SPECULAR); break;

		case ID_SH: strcpy(buf, ID_MAP_SHINE); break;

		case ID_SS: strcpy(buf, ID_MAP_SHINESTRENGTH); break;

		case ID_SI: strcpy(buf, ID_MAP_SELFILLUM); break;

		case ID_OP: strcpy(buf, ID_MAP_OPACITY); break;

		case ID_FI: strcpy(buf, ID_MAP_FILTERCOLOR); break;

		case ID_BU: strcpy(buf, ID_MAP_BUMP); break;

		case ID_RL: strcpy(buf, ID_MAP_REFLECT); break;

		case 12: strcpy(buf, ID_MAP_REFLECT); break;

		case ID_RR: strcpy(buf, ID_MAP_REFRACT); break;

		}

	}

	else {

		strcpy(buf, ID_MAP_GENERIC);

	}

	

	return buf;

}



void HsfExp::DumpTexture(Texmap* tex, Class_ID cid, int subNo, float amt, int indentLevel)

{

	if (!tex) return;

	

	TSTR indent = GetIndent(indentLevel+1);

	

	TSTR className;

	tex->GetClassName(className);

	

	FPRINTF(pStream,"%s%s {\n", indent.data(), GetMapID(cid, subNo));

	

	FPRINTF(pStream,"%s\t%s \"%s\"\n", indent.data(), ID_TEXNAME, FixupName(tex->GetName()));

	FPRINTF(pStream,"%s\t%s \"%s\"\n", indent.data(), ID_TEXCLASS, FixupName(className));

	

	// If we include the subtexture ID, a parser could be smart enough to get

	// the class name of the parent texture/material and make it mean something.

	FPRINTF(pStream,"%s\t%s %d\n", indent.data(), ID_TEXSUBNO, subNo);

	

	FPRINTF(pStream,"%s\t%s %s\n", indent.data(), ID_TEXAMOUNT, Format(amt));

	

	// Is this a bitma ptexture?

	// We know some extra bits 'n pieces about the bitmap texture

	if (tex->ClassID() == Class_ID(BMTEX_CLASS_ID, 0x00)) {

		TSTR mapName = ((BitmapTex *)tex)->GetMapName();

		FPRINTF(pStream,"%s\t%s \"%s\"\n", indent.data(), ID_BITMAP, FixupName(mapName));

		

		StdUVGen* uvGen = ((BitmapTex *)tex)->GetUVGen();

		if (uvGen) {

			DumpUVGen(uvGen, indentLevel+1);

		}

		

		TextureOutput* texout = ((BitmapTex*)tex)->GetTexout();

		if (texout->GetInvert()) {

			FPRINTF(pStream,"%s\t%s\n", indent.data(), ID_TEX_INVERT);

		}

		

		FPRINTF(pStream,"%s\t%s ", indent.data(), ID_BMP_FILTER);

		switch(((BitmapTex*)tex)->GetFilterType()) {

		case FILTER_PYR:  FPRINTF(pStream,"%s\n", ID_BMP_FILT_PYR); break;

		case FILTER_SAT: FPRINTF(pStream,"%s\n", ID_BMP_FILT_SAT); break;

		default: FPRINTF(pStream,"%s\n", ID_BMP_FILT_NONE); break;

		}

	}

	

	for (int i=0; i<tex->NumSubTexmaps(); i++) {

		DumpTexture(tex->GetSubTexmap(i), tex->ClassID(), i, 1.0f, indentLevel+1);

	}

	

	FPRINTF(pStream, "%s}\n", indent.data());

}





void HsfExp::WriteTextureImage(Texmap *tex, Class_ID cid, int subNo, const char *name, int width, int height, unsigned char *buffer)

{

 

		char mapName[4096];

		int imagenum;

		strcpy(mapName,((BitmapTex *)tex)->GetMapName());

		if (vhash_lookup_string_key_item(m_imagehash, mapName, (void **)&imagenum) != VHASH_STATUS_SUCCESS)

		{

			vhash_insert_string_key_item(m_imagehash, mapName, (void *)m_imagecounter);

			imagenum = m_imagecounter;

			m_imagecounter++;			

 

	char imagename[4096];

	sprintf(imagename, "image-%d", imagenum);

	char text[4096];
 	char text2[4096];
	CreateRelativePath(text, "styles/textures");

	WriteOpenSegment(text);

    TK_Image *image_handler = new TK_Image();

	image_handler->SetBytes(width * height * 3, (char *)buffer);

	image_handler->SetSize(width, height);

	char newname[4096];

	sprintf(newname, "%s-image", name);

	image_handler->SetName(imagename);

	image_handler->SetFormat(TKO_Image_RGB);
	image_handler->SetOptions(TKO_Image_Local_Texture);
	if (GetImageCompression())

		image_handler->SetCompression(TKO_Compression_JPEG);

	else

		image_handler->SetCompression(TKO_Compression_RLE);



    WriteObject(image_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
WriteCloseSegment();	
	
	delete image_handler;
	}

	StdUVGen* uvGen = ((BitmapTex *)tex)->GetUVGen();
	char text[4096];
 	CreateRelativePath(text, "styles/textures");

	WriteOpenSegment(text);
	WriteTexture(tex,cid, subNo, name, uvGen, imagenum);
	WriteCloseSegment();
 
}

typedef float HT_Row_Vector[4];



#define F(x)		((float)(x)) /* please don't use for casting - use as modifier on consts */





static void  HC_Compute_Scale_Matrix (

     	double			x,

     	double			y,

     	double			z,

     	float  		*matp) {

     	HT_Row_Vector 	*m = (HT_Row_Vector  *)matp;



     



    



    m[0][0] = (float)x; m[0][1] = F(0);     m[0][2] = F(0);     m[0][3] = F(0);

    m[1][0] = F(0);     m[1][1] = (float)y; m[1][2] = F(0);     m[1][3] = F(0);

    m[2][0] = F(0);     m[2][1] = F(0);     m[2][2] = (float)z; m[2][3] = F(0);

    m[3][0] = F(0);     m[3][1] = F(0);     m[3][2] = F(0);     m[3][3] = F(1);

}





void HsfExp::WriteTexture(Texmap *tex, Class_ID cid, int subNo,const char *name, StdUVGen *uvGen, int imagenum)

{

 

    TK_Texture *texture_handler = new TK_Texture();

 	texture_handler->SetName(name);

	char newname[4096];

	sprintf(newname, "image-%d", imagenum);

	texture_handler->SetImage(newname);



	if (uvGen)

	{

		TimeValue t = GetStaticFrame();

	

		float matrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};



	    TK_Matrix *matrix_handler = new TK_Matrix(TKE_Texture_Matrix);

		HC_Compute_Scale_Matrix(1.0f/uvGen->GetUScl(t), 1.0f/uvGen->GetVScl(t),1,matrix);

		Matrix3 uvtrans;

		uvGen->GetUVTransform(uvtrans);

		uvtrans.Invert();

		Point3 row = uvtrans.GetRow(0);

		matrix[0] = row[0];

		matrix[1] = row[1];

		matrix[2] = row[2];

		matrix[3] = 0;

		row = uvtrans.GetRow(1);

		matrix[4] = row[0];

		matrix[5] = row[1];

		matrix[6] = row[2];

		matrix[7] = 0;

		row = uvtrans.GetRow(2);

		matrix[8] = row[0];

		matrix[9] = row[1];

		matrix[10] = row[2];

		matrix[11] = 0;

		row = uvtrans.GetRow(3);

		matrix[12] = row[0];

		matrix[13] = row[1];

		matrix[14] = row[2];

		matrix[15] = 1;

		

		matrix_handler->SetMatrix(matrix);

	    WriteObject(matrix_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);
		delete matrix_handler;
	}

	 



	if (strcmp(GetMapID(cid, subNo), ID_MAP_DIFFUSE) == 0 || strcmp(GetMapID(cid, subNo), ID_MAP_BUMP) == 0)

	{

		texture_handler->SetTiling(TKO_Texture_Tiling_Repeat);

		texture_handler->SetFlags(TKO_Texture_Tiling);

	}

	else

	{

		texture_handler->SetTiling(TKO_Texture_Tiling_Clamp);

		texture_handler->SetParameterSource(TKO_Texture_Param_Source_Reflection_Vector);

		texture_handler->SetFlags(TKO_Texture_Param_Source | TKO_Texture_Tiling);

	}


    WriteObject(texture_handler, m_pStreamFileToolkit, m_Stream, m_Buffer, BUFFERSIZE);




	delete texture_handler;
}







void HsfExp::DumpHsfTexture(int mtlID, int subMat, Texmap* tex, Class_ID cid, int subNo, float amt, TCHAR *texturetype, bool &dumped)
{

 	if (!tex) return; 	

	TSTR className;

	tex->GetClassName(className);

	TimeValue t = GetStaticFrame();
	 

  	if (tex->ClassID() == Class_ID(BMTEX_CLASS_ID, 0x00)) {


		char text[4096];
//		MessageBox(0,text,0,0);
 

		if (strcmp(GetMapID(cid, subNo), ID_MAP_GENERIC) == 0 || strcmp(GetMapID(cid, subNo), ID_MAP_DIFFUSE) == 0 || strcmp(GetMapID(cid, subNo), ID_MAP_BUMP) == 0 ((strcmp(GetMapID(cid, subNo), ID_MAP_REFLECT) == 0 || strcmp(GetMapID(cid,subNo), ID_MAP_REFRACT) == 0) && !GetDisableEnv())) 
		{




		Bitmap *bitmap = ((BitmapTex *)tex)->GetBitmap(t);

		if (bitmap)

		{


		int width = bitmap->Width();

		int height = bitmap->Height();

		unsigned char *image = new unsigned char[width * height *3];

		BMM_Color_fl *orig_image = new BMM_Color_fl[width];

		for (int i=0;i<height;i++)

		{



			char mapName[4096];

			int imagenum;

			strcpy(mapName,((BitmapTex *)tex)->GetMapName());

			if (vhash_lookup_string_key_item(m_imagehash, mapName, (void **)&imagenum) != VHASH_STATUS_SUCCESS)

			{

			int res =  bitmap->GetPixels(0,i,width, orig_image);

			for (int j=0;j<width;j++)

			{

				float x = BMM_Color_fl::clipColor(orig_image[j].r);

				image[(i*width + j)*3] = (float)BMM_Color_fl::clipColor(orig_image[j].r)/65536.0f * 256.0f;

				image[(i*width + j)*3 + 1] = (float)BMM_Color_fl::clipColor(orig_image[j].g)/65536.0f * 256.0f;

				image[(i*width + j)*3 + 2] = (float)BMM_Color_fl::clipColor(orig_image[j].b)/65536.0f * 256.0f;

			}

			}

		}

		char name[4096];

		if (strcmp(texturetype, ID_MAP_DIFFUSE) == 0)
			sprintf(name, "texdif%d", mcounter);

		else if (strcmp(texturetype, ID_MAP_BUMP) == 0 || strcmp(GetMapID(cid, subNo), ID_MAP_GENERIC) == 0)
		{
			sprintf(name, "texbump%d", mcounter);
 
		}
		else
			sprintf(name, "texref%d", mcounter);





		WriteTextureImage(tex, cid, subNo, name,width,height,image);
		dumped = true;

		}

		}



	}
	

	for (int i=0; i<tex->NumSubTexmaps(); i++) {

		DumpHsfTexture(mtlID, subMat, tex->GetSubTexmap(i), tex->ClassID(), i, 1.0f,texturetype, dumped);

	}

	

}







void HsfExp::DumpUVGen(StdUVGen* uvGen, int indentLevel)

{

	int mapType = uvGen->GetCoordMapping(0);

	TimeValue t = GetStaticFrame();

	TSTR indent = GetIndent(indentLevel+1);

	

	FPRINTF(pStream,"%s%s ", indent.data(), ID_MAPTYPE);

	

	switch (mapType) {

	case UVMAP_EXPLICIT: FPRINTF(pStream,"%s\n", ID_MAPTYPE_EXP); break;

	case UVMAP_SPHERE_ENV: FPRINTF(pStream,"%s\n", ID_MAPTYPE_SPH); break;

	case UVMAP_CYL_ENV:  FPRINTF(pStream,"%s\n", ID_MAPTYPE_CYL); break;

	case UVMAP_SHRINK_ENV: FPRINTF(pStream,"%s\n", ID_MAPTYPE_SHR); break;

	case UVMAP_SCREEN_ENV: FPRINTF(pStream,"%s\n", ID_MAPTYPE_SCR); break;

	}

	

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_U_OFFSET, Format(uvGen->GetUOffs(t)));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_V_OFFSET, Format(uvGen->GetVOffs(t)));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_U_TILING, Format(uvGen->GetUScl(t)));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_V_TILING, Format(uvGen->GetVScl(t)));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_ANGLE, Format(uvGen->GetAng(t)));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_BLUR, Format(uvGen->GetBlur(t)));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_BLUR_OFFSET, Format(uvGen->GetBlurOffs(t)));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_NOISE_AMT, Format(uvGen->GetNoiseAmt(t)));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_NOISE_SIZE, Format(uvGen->GetNoiseSize(t)));

	FPRINTF(pStream,"%s%s %d\n", indent.data(), ID_NOISE_LEVEL, uvGen->GetNoiseLev(t));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_NOISE_PHASE, Format(uvGen->GetNoisePhs(t)));

}





/****************************************************************************



  Face Mapped Material functions

  

****************************************************************************/



BOOL HsfExp::CheckForFaceMap(Mtl* mtl, Mesh* mesh)

{

	if (!mtl || !mesh) {

		return FALSE;

	}

	

	ULONG matreq = mtl->Requirements(-1);

	

	// Are we using face mapping?

	if (!(matreq & MTLREQ_FACEMAP)) {

		return FALSE;

	}

		

	

	

	return TRUE;

}







/****************************************************************************



  Face Mapped Material functions

  

****************************************************************************/



BOOL HsfExp::CheckForAndExportFaceMap(Mtl* mtl, Mesh* mesh, int indentLevel)

{

	if (!mtl || !mesh) {

		return FALSE;

	}

	

	ULONG matreq = mtl->Requirements(-1);

	

	// Are we using face mapping?

	if (!(matreq & MTLREQ_FACEMAP)) {

		return FALSE;

	}

	

	TSTR indent = GetIndent(indentLevel+1);

	

	// OK, we have a FaceMap situation here...

	

	FPRINTF(pStream, "%s%s {\n", indent.data(), ID_MESH_FACEMAPLIST);

	for (int i=0; i<mesh->getNumFaces(); i++) {

		Point3 tv[3];

		Face* f = &mesh->faces[i];

		make_face_uv(f, tv);

		FPRINTF(pStream, "%s\t%s %d {\n", indent.data(), ID_MESH_FACEMAP, i);

		FPRINTF(pStream, "%s\t\t%s\t%d\t%d\t%d\n", indent.data(), ID_MESH_FACEVERT, (int)tv[0].x, (int)tv[0].y, (int)tv[0].z);

		FPRINTF(pStream, "%s\t\t%s\t%d\t%d\t%d\n", indent.data(), ID_MESH_FACEVERT, (int)tv[1].x, (int)tv[1].y, (int)tv[1].z);

		FPRINTF(pStream, "%s\t\t%s\t%d\t%d\t%d\n", indent.data(), ID_MESH_FACEVERT, (int)tv[2].x, (int)tv[2].y, (int)tv[2].z);

		FPRINTF(pStream, "%s\t}\n", indent.data());

	}

	FPRINTF(pStream, "%s}\n", indent.data());

	

	return TRUE;

}





/****************************************************************************



  Misc Utility functions

  

****************************************************************************/



// Return an indentation string

TSTR HsfExp::GetIndent(int indentLevel)

{

	TSTR indentString = "";

	for (int i=0; i<indentLevel; i++) {

		indentString += "\t";

	}

	

	return indentString;

}



// Determine is the node has negative scaling.

// This is used for mirrored objects for example. They have a negative scale factor

// so when calculating the normal we should take the vertices counter clockwise.

// If we don't compensate for this the objects will be 'inverted'.

BOOL HsfExp::TMNegParity(Matrix3 &m)

{

	return (DotProd(CrossProd(m.GetRow(0),m.GetRow(1)),m.GetRow(2))<0.0)?1:0;

}



// Return a pointer to a TriObject given an INode or return NULL

// if the node cannot be converted to a TriObject

TriObject* HsfExp::GetTriObjectFromNode(INode *node, TimeValue t, int &deleteIt)

{

	deleteIt = FALSE;

	Object *obj = node->EvalWorldState(t).obj;

	if (obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0))) { 

		TriObject *tri = (TriObject *) obj->ConvertToType(t, 

			Class_ID(TRIOBJ_CLASS_ID, 0));

		// Note that the TriObject should only be deleted

		// if the pointer to it is not equal to the object

		// pointer that called ConvertToType()

		if (obj != tri) deleteIt = TRUE;

		return tri;

	}

	else {

		return NULL;

	}

}



// Print out a transformation matrix in different ways.

// Apart from exporting the full matrix we also decompose

// the matrix and export the components.

void HsfExp::DumpMatrix3(Matrix3* m, int indentLevel)

{

	Point3 row;

	TSTR indent = GetIndent(indentLevel);

	

	// Dump the whole Matrix

	row = m->GetRow(0);

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_TM_ROW0, Format(row));

	row = m->GetRow(1);

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_TM_ROW1, Format(row));

	row = m->GetRow(2);

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_TM_ROW2, Format(row));

	row = m->GetRow(3);

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_TM_ROW3, Format(row));

	

	// Decompose the matrix and dump the contents

	AffineParts ap;

	float rotAngle;

	Point3 rotAxis;

	float scaleAxAngle;

	Point3 scaleAxis;

	

	decomp_affine(*m, &ap);



	// Quaternions are dumped as angle axis.

	AngAxisFromQ(ap.q, &rotAngle, rotAxis);

	AngAxisFromQ(ap.u, &scaleAxAngle, scaleAxis);



	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_TM_POS, Format(ap.t));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_TM_ROTAXIS, Format(rotAxis));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_TM_ROTANGLE, Format(rotAngle));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_TM_SCALE, Format(ap.k));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_TM_SCALEAXIS, Format(scaleAxis));

	FPRINTF(pStream,"%s%s %s\n", indent.data(), ID_TM_SCALEAXISANG, Format(scaleAxAngle));

}



// From the SDK

// How to calculate UV's for face mapped materials.

static Point3 basic_tva[3] = { 

	Point3(0.0,0.0,0.0),Point3(1.0,0.0,0.0),Point3(1.0,1.0,0.0)

};

static Point3 basic_tvb[3] = { 

	Point3(1.0,1.0,0.0),Point3(0.0,1.0,0.0),Point3(0.0,0.0,0.0)

};

static int nextpt[3] = {1,2,0};

static int prevpt[3] = {2,0,1};



void HsfExp::make_face_uv(Face *f, Point3 *tv)

{

	int na,nhid,i;

	Point3 *basetv;

	/* make the invisible edge be 2->0 */

	nhid = 2;

	if (!(f->flags&EDGE_A))  nhid=0;

	else if (!(f->flags&EDGE_B)) nhid = 1;

	else if (!(f->flags&EDGE_C)) nhid = 2;

	na = 2-nhid;

	basetv = (f->v[prevpt[nhid]]<f->v[nhid]) ? basic_tva : basic_tvb; 

	for (i=0; i<3; i++) {  

		tv[i] = basetv[na];

		na = nextpt[na];

	}

}





/****************************************************************************



  String manipulation functions

  

****************************************************************************/



#define CTL_CHARS  31

#define SINGLE_QUOTE 39

// protected characters: a--z, A--Z, 0--9, *_-.@
// blank is converted into +
// rest of non-protected char becomes %hex
static void URIencode(const char * in, unsigned long n, char * out)
{
    unsigned int i, j=0;

    for(i=0;i<n;i++) {

	    char c= (char)in[i];

	    if( c == ' ') {
		    out[j] = '+';
		    j++;

	    }
	    else if(c=='_' || c=='-' || c=='*' || c=='.' || c=='@'
		    || c>='a' && c<='z' || c>='A' && c<='Z' || c>='0' && c<='9' ){

		    out[j] = c;
		    j++;

	    }
	    else
	    {
			const char * HEX = "0123456789ABCDEF";

			out[j++] = 'H';
			out[j++] = 'E';
			out[j++] = 'X';
 			out[j]=HEX[(((unsigned char)c)>>4)];
			j++;
			out[j]=HEX[(((unsigned char)c)&0x000F)];
			j++;
	    }
    }
    out[j] = '\0';
}


// Replace some characters we don't care for.

TCHAR* HsfExp::FixupName(TCHAR* name)

{

	static char buffer[256];
	static char buffer2[256];

	TCHAR* cPtr;

	

    _tcscpy(buffer, name);

    cPtr = buffer;

	

    while(*cPtr) {

		if (*cPtr == '"')

			*cPtr = SINGLE_QUOTE;

//        else if (*cPtr <= CTL_CHARS)
//
//			*cPtr = _T('_');

        else if (*cPtr == '(' || *cPtr == ')')

			*cPtr = _T('_');

        cPtr++;

    }



	URIencode(buffer, strlen(buffer), buffer2);

	

	return buffer2;

}



// International settings in Windows could cause a number to be written

// with a "," instead of a ".".

// To compensate for this we need to convert all , to . in order to make the

// format consistent.

void HsfExp::CommaScan(TCHAR* buf)

{

    for(; *buf; buf++) if (*buf == ',') *buf = '.';

}



TSTR HsfExp::Format(int value)

{

	TCHAR buf[50];

	

	sprintf(buf, _T("%d"), value);

	return buf;

}





TSTR HsfExp::Format(float value)

{

	TCHAR buf[40];

	

	sprintf(buf, szFmtStr, value);

	CommaScan(buf);

	return TSTR(buf);

}



TSTR HsfExp::Format(Point3 value)

{

	TCHAR buf[120];

	TCHAR fmt[120];

	

	sprintf(fmt, "%s\t%s\t%s", szFmtStr, szFmtStr, szFmtStr);

	sprintf(buf, fmt, value.x, value.y, value.z);



	CommaScan(buf);

	return buf;

}



TSTR HsfExp::Format(Color value)

{

	TCHAR buf[120];

	TCHAR fmt[120];

	

	sprintf(fmt, "%s\t%s\t%s", szFmtStr, szFmtStr, szFmtStr);

	sprintf(buf, fmt, value.r, value.g, value.b);



	CommaScan(buf);

	return buf;

}



TSTR HsfExp::Format(AngAxis value)

{

	TCHAR buf[160];

	TCHAR fmt[160];

	

	sprintf(fmt, "%s\t%s\t%s\t%s", szFmtStr, szFmtStr, szFmtStr, szFmtStr);

	sprintf(buf, fmt, value.axis.x, value.axis.y, value.axis.z, value.angle);



	CommaScan(buf);

	return buf;

}





TSTR HsfExp::Format(Quat value)

{

	// A Quat is converted to an AngAxis before output.

	

	Point3 axis;

	float angle;

	AngAxisFromQ(value, &angle, axis);

	

	return Format(AngAxis(axis, angle));

}



TSTR HsfExp::Format(ScaleValue value)

{

	TCHAR buf[280];

	

	sprintf(buf, "%s %s", Format(value.s), Format(value.q));

	CommaScan(buf);

	return buf;

}

