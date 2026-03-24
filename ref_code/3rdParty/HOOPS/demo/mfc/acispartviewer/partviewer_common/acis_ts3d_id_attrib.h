#if !defined( ATTRIB_T3D_ID_CLASS )
#define ATTRIB_T3D_ID_CLASS
#include "at_T3D.h"
extern int ATTRIB_T3D_ID_TYPE;
#define ATTRIB_T3D_ID_LEVEL    ( ATTRIB_T3D_LEVEL + 1 )

class ATTRIB_T3D_ID : public ATTRIB_T3D {
	int entity_id;
public:
	ATTRIB_T3D_ID( ENTITY * = NULL, int = 0 );
	int get_ID() const { return entity_id; }

	void set_ID( int );
	ATTRIB_FUNCTIONS( ATTRIB_T3D_ID, NONE );
	void merge_owner( ENTITY *, logical );
	void replace_owner( ENTITY *, logical );
};
#endif

