#ifndef PP_SHAPE_INPUT_LIB_H_
#define  PP_SHAPE_INPUT_LIB_H_

/***************************************************************************
 * Description:
 *          
 *          This header is a interface to load all build-in shapes.
 * Author  : Jerry He (hejw06@gmail.com) 
 * Language: C++
 * Date    : 2011-10-27
 ***************************************************************************/

#include "coresps/coresps_global.h"

class ShapeManager;


/// These shapes are made by LiDa. Sep. 2011.
CORESPS_EXPORT void importSimpleShapesDef();


/// These shapes are created by Jerry. 
/// Oct. 2011
CORESPS_EXPORT void importHoopsShapesDef();


#endif
