#ifndef INSTEMPLATE_H
#define INSTEMPLATE_H


#include <QString>
#include <QList>
#include <string>
#include <QStringList>
#include <QMap>


namespace INSEditor
{

namespace Parse{

/*!
*	The \class INSItemTemplate is used as a type of item in the .ins file.
*	@example:
*	<ITEM KEYWORD="RIGID" PROPERTIES="" 
*	SUBITEMNAMES="MASS,IP,QG,THETAG,PHIG,XG,YG,ZG
*	,EULER321G,EULER323G,EULER313G,EULER312G
*	,EULER212G,EULER213G,EULER231G,EULER232G
*	,EULER123G,EULER121G,EULER131G,EULER132G,VG,VR,OG,OR"        
*	SHORTHELP="" LONGHELP="" />
*	@todo:	support function call tip. Example: IP=x,y,z
*	@author	Jerry He
*	@date	2014.8.14
*/
class ItemTemplate
{
public:
	///获得关键字名字
	const QString& getKeyName()const{return _keyName;}
	
	///设置关键字名字
	void setKeyName(const QString& keyName){_keyName=keyName;}

	///获得所有子项胡列表
	const QStringList& getSubItems()const{return _subItems;}

	///设置所有子项为subItems
	void setSubItems(const QStringList& subItems){_subItems=subItems;}

	///获得所有子属性
	const QStringList& getSubProperties()const{return _subProperties;}

	///设置子属性为subProperties
	void setSubProperties(const QStringList& subProperties){_subProperties=subProperties;}

	///条目中是否含有属性p
	bool hasProperty(const QString& p)const;

	///条目中时候含有子项p
	bool hasSubItem(const QString& p)const;

private:
	///关键名
	QString		_keyName;

	///所有子项
	QStringList _subItems;

	///所有子属性
	QStringList _subProperties;
};


/*!
*	The \class INSTemplate is used to manage all INS file defined item type.
*	It contains a list of \class INSItemTemplate instances.
*	@author	Jerry He
*	@date	2014.8.14
*/
class ItemTemplateManagerSinleton
{
public:
	typedef QMap<QString,ItemTemplate> MapType;

	///获取insmodee唯一指针
	static ItemTemplateManagerSinleton* instance();
	
	///加载默认的instemplate文件 
	bool loadDefault();
	
	///加载instemplate文件fileName
	bool loadTemplateFile(const QString& fileName);

	///获得关键字集1
	const char* getKeywordSet1();

	///获得关键字集2
	const char* getKeywordSet2();

	///通过key找到对应的 itemTemplate
	const ItemTemplate* getItem(const QString& key);

private:
	///已废弃
	void reset();

private:
	ItemTemplateManagerSinleton();
	~ItemTemplateManagerSinleton();
	Q_DISABLE_COPY(ItemTemplateManagerSinleton);

	MapType			_items;
	QString			_keywordSet1;
	QString			_keywordSet2;
	std::string		_keywordSet1Array;
	std::string		_keywordSet2Array;
};

inline ItemTemplateManagerSinleton* ItemTemplateManager(){
	return ItemTemplateManagerSinleton::instance();
}

} // end namespace Parse
} // end namespace INSEditor


#endif // INSTEMPLATE_H
