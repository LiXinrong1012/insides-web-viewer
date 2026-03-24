#pragma once

#include "precore/precore_global.h"
#include <QtCore/QMap>
#include <QtCore/QString>
#include <bitset>
#include "precore/appearance.h"


namespace Base{class ItemProperties;}
namespace osg
{
	class Matrixf;
}



namespace INSIDES
{

typedef osg::Matrixf Matrix;

class BaseItem;
class Assembly;

typedef QList<BaseItem*> BaseItemList;

/*!
	@breif This class is used as the base class of all items.
	支持属性、子条目、复制。
	@author	Jerry He
	@date	2013.12
*/
class PRECORE_EXPORT BaseItem
{
public:
	/// constructions, destructions, etc
	BaseItem(const QString& keyname=QString());
	virtual ~BaseItem(void);

	/// 克隆一个自己，不包含子对象，不包含父子关系
	BaseItem* clone()const;			

	/// 克隆一个自己，包含子对象等所有信息
	BaseItem* cloneAll()const;

	/// 复制到别一个条目，不包含子对象,不包含父子关系
	virtual void copyTo(BaseItem* item)const;

	/// 根据此条目生成一个实例，并更新。
	BaseItem* createInstance();	


	/// 是否是一个构件或者组件
	bool isPartOrAssembly();

	/// 设置名字
	void setKeyname(const QString& name ){_keyname=name;}
	/// 获得名字
	QString getKeyName()const{return _keyname;}

	/// 比较关键字
	bool compareKeyname(const QString& name);

	/// 获得全路径名字，例如：".instance.i1"
	QString getFullName()const;

	/// 获得类别
	int getCategory()const{return _category;}
	/// 设置类别
	void setCategory(int category){_category=category;}

	/// 获得ID号
	int getID()const {return _id;}

	/// 设置ID号
	void setID(int id){_id=id;}

	/// 获得类类型ID
	int getClassType()const{return _classType;}

	/// 是否被激活，没被激活的条目代表一个不起实际作用的条目
	bool getActive()const{return _flags[0];}

	/// 设置是否被激活
	void setActive(bool active){_flags[0]=active;}

	/// 获取是否是被包含的条目，一个包含的条目是指它是一个Instance的子条目
	bool getIncluded()const {return _flags[1];}

	/// 设置是否是被包含条目
	void setIncluded(bool b){_flags[1]=b;}

	/// 获取条目是否收缩子条目
	bool getCollapsed()const{return _flags[2];}

	/// 设置条目是否收缩子条目
	void setCollapsed(bool b){_flags[2]=b;}

	/// 是否是一个实例
	bool isInstance()const{return _flags[3];}

	/// 设置是否是一个实例
	void setIsInstance(bool b){_flags[3]=b;}

	/// 是否是一个
	bool isExternal()const{return _flags[4];}
	void setIsExternal(bool b){_flags[4]=b;}

	/// 获得总的设置标记
	unsigned long getFlags(){return _flags.to_ulong();}

	/// 设置总的设置标记
	void setFlags(unsigned long f);

	/// 设置此条目的矩阵
	void setMatrix(const Matrix* matrix);

	/// 返回此条目的矩阵
	const Matrix* getMatrix()const{return _matrix;}

	/// 获取此条目相对parentAssembly条目的变换矩阵		
	void getRelativeMatrix(Matrix& matrix,Assembly* parentAssembly=NULL);

	/// 获取模型的显示外观
	const AppearanceItem* getAppearance()const;

	/// 设置模型的显示外观
	AppearanceItem* getAppearance();

	void setAppearance(AppearanceItem* item);

	//// 获得父条目
	BaseItem* getParent()const{return _parent;}

	/// 设置父条目
	void setParent(BaseItem* parent){_parent=parent;}

	///　获得最近的Assembly指针
	Assembly* getParentAssembly();
	BaseItem* findItem( const QString& absoluteName,BaseItem* baseAssembly=NULL );
	BaseItem* findItemWithoutFolder( const QString& name,BaseItem* baseAssembly=NULL );

	virtual QString toString();
	virtual QString getDisplayText()const{return getKeyName();}

	// properties related functions
	typedef Base::ItemProperties Properties;
	QString& operator[] (const QString& nIndex);
	QString operator[](const QString& index)const;
	QString get(const QString& index)const;
	void set(const QString& key,const QString& value);
	bool hasKey(const QString& index)const;
	void removeKey(const QString& index);
	QMap<QString,QString>& getMap();
	Properties* getProperties(){return _properties;}
	void setProperties(Properties* p);
	QString getPropertiesString()const;
	void setPropertiesString(const QString& str);
	bool hasProperties()const;
	void printProperties();


	/// 子条目数目
	int count()const{return _itemList.size();}

	/// 返回第index个子条目
	BaseItem* child(int index){return _itemList[index];}
	const BaseItem* child(int index)const;

	/// 返回第一个名字是keyname的子条目
	BaseItem* child(const QString& keyname);

	/// 删除条目，deleteIt指数指示是否从内存中清除
	bool remove(BaseItem* item,bool deleteIt=true);

	/// 条目在父条目中的位置
	int row()const;

	/// 某子条目的位置
	int indexOf(BaseItem* const item)const;

	/// 在某位置插入条目，为０意味着插入第一个，为count()意味着append()
	bool insertChild(int pos,BaseItem* item);

	/// 在最后增加子条目
	bool appendChild(BaseItem* item);

	/// 删除所有条目
	void clearChildren();

	/// 返回id1<id2的结果，用来排序；
	static bool compareID(const BaseItem* i1,const BaseItem* i2);
	static bool compareKeyname(const BaseItem* i1,const BaseItem* i2);
	static long	currentMaxID();
	static long nextCurrentMaxID();
	static void getChildren(BaseItem* item,QList<BaseItem*>& children,bool recusive=false);

	static QString instanceKeyName;

protected:
	/// 更新一个实例。
	void updateInstance();

	/// 更新一个实例。
	static void updateInstance(const BaseItem* src,BaseItem* dst);

	BaseItem*	_parent;
	int			_category;
	int			_id;
	int			_classType;			//标明类类型
	AppearanceItem* _appearance; 

	/*!
	*	Various flags need supported by BaseItem
	*	Bit 0: Active
	*	Bit 1: Included
	*	Bit 2: Collapsed
	*	Bit 3: Is instance
	*/
	std::bitset<16>	_flags;

	QString		_keyname;
	BaseItemList _itemList;
	Properties*	_properties;
	Matrix*		_matrix;

	Properties* getOrCreateProperties();


	static long _currentMaxID;

private:
	Q_DISABLE_COPY(BaseItem);

	static void updateInstanceChildren(const BaseItem* src,BaseItem* dst);
	static void createInstanceChildren( const BaseItem* src,BaseItem* dst );

};

} //end namespace INSIDES