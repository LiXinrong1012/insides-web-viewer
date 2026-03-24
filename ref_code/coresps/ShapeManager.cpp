#include "ShapeManager.h"
#include "HoopsShapeManager.h"

#include "coresps/shapeinputlib.h"
#include "coresps/spsin.h"


ShapeManager* ShapeManager::instance()
{
	return HoopsShapeManager::instance();
}

void register_all_buildin_shapes()
{
	importSimpleShapesDef();
	importHoopsShapesDef();
	importShapesCollection();
	//ShapeManager::instance()->setGlobalScale(0.3);
}