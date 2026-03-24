#pragma once

#include "precore/BaseItem.h"


namespace INSIDES
{

typedef BaseItem Folder;

/*!
	@breif 代表一个子结构。
	代表一个子结构，提供默认的文件夹支持。
	
	@author	Jerry He
	@date	2014.3
*/
class PRECORE_EXPORT Assembly : public BaseItem
{
public:
	Assembly(const QString& keyName=QString());
	~Assembly(void);

	void createDefault();

	BaseItem* getParameters();
	BaseItem* getOrCreateParameters();

	/// 返回Parts文件夹，Parts文件夹里储存如RigidPart,FEMPart等组件
	BaseItem* getParts();

	/// 返回Assemblies文件夹，用来放置子结构
	BaseItem* getAssemblies();

	/// 返回Constraints文件夹，用来放置约束
	BaseItem* getConstraints();

	/// 返回Loads文件夹，用来放置力等。
	BaseItem* getLoads();

	/// 返回碰撞文件夹，用来放置碰撞力等。
	BaseItem* getContacts();

	/// 返回Instances文件夹，用来放置所有实例。
	BaseItem* getInstances();

	/// 返回Request文件夹，用来放置自定义输出数据。
	BaseItem* getRequests();

	/// 返回Set文件夹，用来放置集合
	BaseItem* getSets();

	BaseItem* getMarkers();

	/// 返回地条目。
	BaseItem* getGround();

private:
	Assembly(const Assembly& C);
	Assembly & operator = (const Assembly &);


protected:
	void Assembly::initFolders();
	Folder* Assembly::getOrCreateFolder( const QString& key );

};


} // end namespace INSDIES