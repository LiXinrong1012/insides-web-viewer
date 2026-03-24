#ifndef TDYTYPEINFOMANAGER_H
#define TDYTYPEINFOMANAGER_H

#include <QObject>
#include <QMap>
#include <QSharedPointer>
#include <QtXml/QDomElement>
#include <QStringList>


namespace INSEditor
{
namespace Parse
{
class AssemblyItem;
class LineItem;
class ModelParser;

/*!
	@brief   代表一个属性
	@date    2015.6.15
	@author  Jerry
*/
class TDYTypeProperty
{
public:
	///属性名称
	QString keyName;
};

/*!
	@brief   代表一个属性组,组内的属性是互斥的
	@date    2015.6.15
	@author  Jerry
*/
class TDYTypePropertyGroup
{
public:
	///属性组的名称
	QString					keyName;
	
	///是否是可选参数,默认为可选参数
	bool					isOptimal;

	///默认值
	QString					defaultValue;
	
	///所有属性
	QList<TDYTypeProperty>	properties;

	///是否可选默认为真
	TDYTypePropertyGroup():isOptimal(true){}
};

class TDYTypeKeyValue;
typedef QSharedPointer<TDYTypeKeyValue> TDYTypeKeyValuePtr;

/*!
	@brief   代表一个键值对
	@date    2015.6.15
	@author  Jerry
*/
class TDYTypeKeyValue
{
public:
	/// 关键字名字
	QString keyName;

	///分量数目，当分量数据<=0时，表示长度不固定
	int	componentCount;

	///单个分量的类型
	QString componentType;

	///是否是可选参数,
	bool isOptimal;

	///是否是引用
	bool isReference;

	///值的个数 0为不限制，大于0为强制几个
	int valueCount;

	///是否是只设置其一，还是可设置多个
	///仅仅在有子属性值时才有意义
	bool isMultipleKeyvalue;

	///可以设置几个，当isMultipleKeyvalue = true时，有子属性时生效，默认为1
	int selectCount;

	///如果是引用，可引用的条目类型集合
	QStringList validReferenceTypes;

	///是否只在特定属性值下起作用，如果为空，表明都起作用
	QStringList validUnderProperties;

	///保存帮助内容
	QString	helpString;

	///该键值对的子项键值对
	QList<TDYTypeKeyValuePtr> subKeyValueGroup;

	///构造函数及变量的默认值初始化
	TDYTypeKeyValue():componentCount(0)
		,isReference(false)
		,isOptimal(true)
		,isMultipleKeyvalue(true)
		,valueCount(0)
		,selectCount(1)
	{
	}

	///是否为动态的
	bool isDynanic()const{return componentCount<=0;}
};


/*!
	@brief 单个类型的定义信息。
	@author	Jerry He
	@date	2014.12.8
*/
class TDYTypeInfo
{
public:
	///tdyTypeInfo名称
	QString						keyName;

	///对应的后处理中的类别,默认为-1
	int							viewerCategory; 

	///属性组
	QList<TDYTypePropertyGroup> propertyGroups;

	///键值对组
	TDYTypeKeyValuePtr			keyvalueGroups;

	///是否支持未知属性
	bool						supportUnknownProperty;

	///是否支持未知键值对
	bool						supportUnknownKeyValue;

	///帮助内容
	QString						helpString;

	///性属列表 
	QList<QString>				propertyList;

	///键值对列表
	QList<TDYTypeKeyValuePtr>	keyvalueList;

	///是否存在属性P
	bool hasProperty(const QString& p){return propertyList.contains(p.toUpper());}

	/// 将propertyGroups中的所有属性更新到propertyList中
	/// 将keyvalueGroups中所有键值更新到keyvalueList中
	void update();

	TDYTypeInfo():viewerCategory(-1){}
};

typedef QSharedPointer<TDYTypeInfo>   TDYTypeInfoPtr;


/*!
	@brief 管理INSIDES-Solver支持的所有条目信息
	@author	Jerry He
	@date	2014.12.7
*/
class TDYTypeInfoManager 
{
public:
	TDYTypeInfoManager();
	~TDYTypeInfoManager();

	/// 是否完成导入数据
	bool isLoaded()const{return _isLoaded;}

	/// 从原来的tdy_template.xml中导入条目定义信息
	void loadFromTDYTemplate(const QString& fileName);

	/// 从文件中导入
	void load(const QString& fileName);

	/// 保存到文件
	void save(const QString& fileName);

	/// 从某个节点中导入
	void load(QDomElement rootElement);

	/// 保存到某个节点
	void save(QDomElement rootElement);

	///获得所有信息
	const QMap<QString,TDYTypeInfoPtr>& getAllInfos()const{return _tdyTypeInfos;}
	QMap<QString,TDYTypeInfoPtr>& getAllInfos(){return _tdyTypeInfos;}

	/// 增加一个条目信息
	void addTDYInfos(QString keyName,TDYTypeInfoPtr ptr);

	///获得所有键
	const char* getAllKeynames();

	///获得所有属性
	const char* getAllProperties();

private:
	///添加键值对项
	void addKeyValueElement(TDYTypeKeyValuePtr kvPtr,QDomDocument& doc, QDomElement& element);

	///读取键值对内容
	TDYTypeKeyValuePtr readKeyValueElement(QDomElement& element);

private:
	QMap<QString,TDYTypeInfoPtr>	_tdyTypeInfos;

	///是否加载完成
	bool							_isLoaded;

	///所有键
	std::string						_allKeynames;

	///所有属性
	std::string						_allProperties;

};

} // end namespace Parse
} // end namespace INSEditor

#endif // TDYTYPEINFOMANAGER_H
