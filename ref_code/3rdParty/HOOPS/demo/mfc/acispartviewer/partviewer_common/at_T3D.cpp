#include "stdafx.h"
#include <stdio.h>
#include "acis.hxx"
#include "dcl_kern.h"
#include "datamsc.hxx"
#include "at_t3d.h"

// Define macros for this attribute and its parent, to provide
// the information to the definition macro.
#define THIS() ATTRIB_T3D
#define THIS_LIB NONE
#define PARENT() ATTRIB
#define PARENT_LIB KERN
// Identifier used externally to identify a particular entity type. This is only used 
// within the save/restore system for translating to/from external file format, but must 
// be unique amongst attributes derived directly from ATTRIB, across all application developers.
#define ATTRIB_T3D_NAME "t3d"
MASTER_ATTRIB_DEFN( "t3d master attribute" )

