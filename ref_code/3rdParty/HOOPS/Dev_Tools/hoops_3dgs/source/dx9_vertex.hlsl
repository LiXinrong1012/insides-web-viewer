// Copyright (c) 2007 by Tech Soft 3D, LLC.
// all rights reserved
// $Id: dx9_vertex.hlsl,v 1.58 2010-04-19 23:42:10 trask Exp $
 
/* IO Types ******************************************************************/


vertex_results main( const vertex_input vertex )
{
        // test 1 2 3 trask  -- attempt 2
	vertex_results vresult = vertex_common(vertex);
	return vresult;
} 

