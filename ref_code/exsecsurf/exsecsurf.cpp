#include "exsecsurf.h"
#include "precore/FlexResultItem.h"
#include "precore/FEMPartBaseItem.h"

#include "prefem/MeshGlobal.h"

#include "TDYSectionSurface.h"

Q_EXPORT_PLUGIN2(iexchangesectionsurface, ExSecSurf);


ExSecSurf::ExSecSurf()
{
	/// 柔性体单元的初始化
	static MeshGlobal meshGlobal;
	JMesh::SetElemType(meshGlobal.getType());
}

QString ExSecSurf::getKeyname()
{
	return "TDY_EX_SEC_SURF";
}


ExSecSurf::~ExSecSurf()
{

}

ISectionSurface* ExSecSurf::createSectionSurface( FlexResultItem* flexResultItem )
{
	TDYSectionSurface* secSurf=new TDYSectionSurface(flexResultItem);
	return secSurf;
}
