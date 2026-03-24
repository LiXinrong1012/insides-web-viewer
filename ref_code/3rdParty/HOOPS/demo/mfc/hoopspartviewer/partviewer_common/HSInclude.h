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

// This file contains all the kernel specific include files and #defs

#ifndef HSINCLUDE_RAJESH_B__20010301__1038__
#define HSINCLUDE_RAJESH_B__20010301__1038__


//-- BEGIN: INCLUDE FILES----------------------------
#ifdef PARASOLID
// Parasolid kernel includes
#include "parasolid_kernel.h"
#include "kernel_interface.h"
#include "frustrum_ifails.h"

// HOOPS-Parasolid bridge includes
#include "hp_bridge.h"

#endif // PARASOLID

#ifdef ACIS

// Acis kernel includes
#include "base.hxx"  
#include "logical.h"  
#include "box.hxx"
#include "position.hxx"
#include "transf.hxx"
#include "unitvec.hxx"

#include "boolapi.hxx"

#include "raytest.hxx"
#include "intrapi.hxx" 
#include "rnd_api.hxx"  
#include "rgbcolor.hxx"  

#include "kernapi.hxx"
#include "kernopts.hxx"
#include "acis.hxx"  
#include "acistype.hxx"  
#include "attrib.hxx"
#include "entity.hxx"

#include "curve.hxx"
#include "surface.hxx"
#include "point.hxx"
#include "transfrm.hxx"
#include "body.hxx"
#include "shell.hxx"
#include "face.hxx"
#include "edge.hxx"
#include "vertex.hxx"
#include "surdef.hxx"

#include "rgbcolor.hxx"

#include "ckoutcom.hxx" 
#include "fileinfo.hxx"
#include "bulletin.hxx" 

// ACIS includes for assembly support
#include "asm_api.hxx"
#include "asm_assembly.hxx"
#include "asm_model_ref.hxx"
#include "comp_ent_handle.hxx"
#include "eelists.hxx"
#include "entity_handle.hxx"
#include "entity_handle_list.hxx"
#include "ga_asm_api.hxx"
#include "ha_bridge_asm.h"

// HOOPS-Acis bridge includes
#include "ha_bridge.h"
#include "ha_rend_options.h"

// acispartviewer specific includes
#endif // ACIS

#ifdef GRANITE
// Granite kernel includes
#include "KGlobal.h"
#include "KWSession.h"
#include "KWModel.h"

// HOOPS-Granite bridge includes
#include "hg_bridge.h"

// partviewer includes
#endif // GRANITE

//-- END: INCLUDE FILES----------------------------

//-- BEGIN: #ifdefs---------------------------
#ifdef PARASOLID
#define		KERN_ATTDEF			PK_ATTDEF_t
#define		KERN_ENTITY			PK_ENTITY_t
#define		KERN_BODY			PK_BODY_t
#define		KERN_FACE			PK_FACE_t
#define		KERN_EDGE			PK_EDGE_t
#define		KERN_BOX			PK_BOX_t
#define		KERN_ENTITY_LIST	PK_ENTITY_t*

#define		KERN_CLASS_TYPEDEF	PK_CLASS_t
#define		KERN_INSTANCE_TYPE	PK_CLASS_instance
#define		KERN_BODY_TYPE		PK_CLASS_body
#define		KERN_FACE_TYPE		PK_CLASS_face
#define		KERN_EDGE_TYPE		PK_CLASS_edge
#define		KERN_VERTEX_TYPE	PK_CLASS_vertex
#define		KERN_ENTITY_TYPE	PK_CLASS_entity

#define		KERN_ERROR			PK_ERROR_t

#define		KERN_STREAM_FILE	"psf"

#endif // PARASOLID

#ifdef ACIS
#define		KERN_ATTDEF			ATTRIB*
#define		KERN_ENTITY			ENTITY*
#define		KERN_BODY			BODY*
#define		KERN_FACE			FACE*
#define		KERN_EDGE			EDGE*
#define		KERN_BOX			box*
#define		KERN_ENTITY_LIST	ENTITY_LIST


#define		KERN_CLASS_TYPEDEF	int
#define		KERN_INSTANCE_TYPE	ASM_MODEL_REF_TYPE
#define		KERN_BODY_TYPE		BODY_TYPE
#define		KERN_FACE_TYPE		FACE_TYPE
#define		KERN_EDGE_TYPE		EDGE_TYPE
#define		KERN_VERTEX_TYPE	VERTEX_TYPE
#define		KERN_ENTITY_TYPE	ENTITY_TYPE

#define		KERN_ERROR			outcome

#define		KERN_STREAM_FILE	"asf"

extern void CHECK_OUTCOME( const outcome& result );

#endif	// ACIS

#ifdef HOOPS_ONLY
#define		KERN_CLASS_TYPEDEF	int
#define		SEGMENT_TYPE		1
#define		ENTITY_TYPE			2
#define		SUBENTITY_TYPE		3
#endif // HOOPS_ONLY


#ifdef GRANITE

#define		KERN_ATTDEF			
#define		KERN_ENTITY			KObj_ptr
#define		KERN_BODY			KBody_ptr
#define		KERN_FACE			KFace_ptr
#define		KERN_EDGE			KEdge_ptr
#define		KERN_BOX			KBox3D_ptr
#define		KERN_ENTITY_LIST	KObjList_ptr

#define		KERN_CLASS_TYPEDEF	xrttiobject*
#define		KERN_INSTANCE_TYPE	0
#define		KERN_BODY_TYPE		KBody::getClassRtti()
#define		KERN_FACE_TYPE		KFace::getClassRtti()
#define		KERN_EDGE_TYPE		KEdge::getClassRtti()
#define		KERN_VERTEX_TYPE	0
#define		KERN_ENTITY_TYPE	KObj::getClassRtti()

#define		KERN_ERROR			0

#define		KERN_STREAM_FILE	"gsf"

#endif // GRANITE

#ifndef KERN_STREAM_FILE
#define		KERN_STREAM_FILE	"hsf"
#endif

//-- END: #ifdefs----------------------------


#endif	// HSINCLUDE_RAJESH_B__20010301__1038__
