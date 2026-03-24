#include "stdafx.h"
#include <stdio.h>
#include <memory.h>
#include "acis.hxx"
#include "datamsc.hxx"
#include "acis_ts3d_id_attrib.h"


// Implementation of hoops attribute. This is attached to body,
// face or edge objects, and is used to tag entities uniquely
#define THIS()      ATTRIB_T3D_ID
#define THIS_LIB    NONE
#define PARENT()    ATTRIB_T3D
#define PARENT_LIB  NONE

// Identifier used externally to identify a particular entity type. This is used in the 
// save/restore system for translating to/from external file format.
#define ATTRIB_T3D_ID_NAME "T3D_ID"

// Implement the standard attribute functions.
ATTRIB_DEF( "acis_ts3d_id" )

debug_int( "TS3D_ID" , get_ID(), fp);

SAVE_DEF 
write_int( entity_id ); // Save specific data
RESTORE_DEF 
set_ID( read_int() );

COPY_DEF 
set_ID( from->get_ID() );

SCAN_DEF
// (no specific pointer data)
FIX_POINTER_DEF
// (no specific pointer data)
TERMINATE_DEF

// make a color attribute
ATTRIB_T3D_ID::ATTRIB_T3D_ID ( ENTITY *owner,
						int id ) : ATTRIB_T3D( owner )

{
	// Initialize members.
	entity_id = id;
}

// If my owner is split, create a new instance of myself on the copy.
int set_split_owner_action( SplitCopy );

// If my owner is copied, create a new instance of myself on the copy.
int set_copy_owner_action( CopyCopy );


// Set the member data.
void
ATTRIB_T3D_ID::set_ID ( int new_id )
{
	backup();
	entity_id = new_id;
}

// Virtual function called when two entities are to be merged.
void
ATTRIB_T3D_ID::merge_owner ( ENTITY *other_ent,
						 logical delete_owner )
{
	// If the owner of this attribute is going to be deleted, and there is no attribute attached 
	// to the other entity, then we transfer to that other entity.
	if ( delete_owner )
	{
		ATTRIB *other_att = find_attrib( other_ent, ATTRIB_T3D_TYPE, ATTRIB_T3D_ID_TYPE );
		if ( other_att == NULL )
		{
			move( other_ent );
		}
	}
}

// Virtual function called during replacement.
void
ATTRIB_T3D_ID::replace_owner ( ENTITY *other_ent,
						   logical replace_owner )
{
	if ( replace_owner )
	{
		ATTRIB *other_att = find_attrib( other_ent, ATTRIB_T3D_TYPE, ATTRIB_T3D_ID_TYPE );
		if ( other_att == NULL ) {         
			move(other_ent);         
		}     
	} 
}


