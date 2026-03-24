#include "precore_global.h"

#include "prefem/JMesh.h"
#include "prefem/MeshGlobal.h"

#include "category_register.h"

bool init_precore_module()
{
	/// 柔性体单元的初始化
	static MeshGlobal meshGlobal;
	JMesh::SetElemType(meshGlobal.getType());

	/// 类型信息初始化
	registerAllCategories();
	
	return true;
}