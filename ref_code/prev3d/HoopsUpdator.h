#pragma once

#include "prev3d/prev3d_global.h"
#include <QHash>

namespace INSIDES{
	class AppearanceItem;
	class IResultItem;
}

using namespace INSIDES;

class ViewManager;

struct ResultUpdatePara
{
	ViewManager*	viewManager;
};

typedef void (*HoopsModelUpdatingFunc)(AppearanceItem* item);
typedef void (*HoopsResultUpdatingFunc)(ResultUpdatePara* para,IResultItem* resultItem,AppearanceItem* item);
typedef void (*HoopsEigenUpdatingFunc)(IResultItem* resultItem,AppearanceItem* item,float scale);


class PREV3D_EXPORT HoopsUpdatorSingleton
{
public:
	static HoopsUpdatorSingleton* instance();

	// 获得模型条目更新函数
	HoopsModelUpdatingFunc getItemUpdatingFunc(int typeID);
	// 注册模型条目更新函数
	void registerItemUpdating(int typeID,HoopsModelUpdatingFunc func);
	void onItemUpdating(AppearanceItem* item);
	
	/// 结果动画
	HoopsResultUpdatingFunc getResultUpdatingFunc(int typeId);
	void registerResultUpdating(int typeId,HoopsResultUpdatingFunc func);
	void onResultItemUpdating(ResultUpdatePara* para,IResultItem* resultItem, AppearanceItem* item);

	/// 模态动画
	HoopsEigenUpdatingFunc getEigenUpdatingFunc(int typeId);
	void registerEigenUpdating(int typeId,HoopsEigenUpdatingFunc func);
	void onEigenItemUpdating(IResultItem* resultItem,AppearanceItem* item,float scale);


private:
	typedef QHash<int,HoopsModelUpdatingFunc> ModelUpdatingFuncMap;
	typedef QHash<int,HoopsResultUpdatingFunc> ResultUpdatingFuncMap;
	typedef QHash<int,HoopsEigenUpdatingFunc>	EigenUpdatingFuncMap;

	ModelUpdatingFuncMap _modelUpdatingFuncMap;
	ResultUpdatingFuncMap _resultUpdatingFuncMap;
	EigenUpdatingFuncMap	_eigenUpdatingFuncMap;

	HoopsUpdatorSingleton(void);
	~HoopsUpdatorSingleton(void);

};


inline HoopsUpdatorSingleton* HoopsUpdator(){
	return HoopsUpdatorSingleton::instance();
}

// 注册模型更新的函数
void PREV3D_EXPORT registerModelUpdatingFunctions();	
void PREV3D_EXPORT registerResultUpdatingFunctions();
void PREV3D_EXPORT registerEigenUpdatingFunctions();