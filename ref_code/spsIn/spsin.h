
namespace pp
{
	class ShapeManager;
}

#ifndef SPSIN_EXPORTS
#define SPSIN_EXPORT __declspec(dllimport) 
#else
#define SPSIN_EXPORT __declspec(dllexport) 
#endif


/*extern "C"*/
SPSIN_EXPORT void setShapeManager(ShapeManager* shapeManager);

/*extern "C"*/
SPSIN_EXPORT void importShapesCollection();