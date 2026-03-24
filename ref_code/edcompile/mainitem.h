#pragma once

#include <vector>
#include <string>
#include <map>

#include <QList>
#include <QString>
#include <QSet>
#include <QStringList>

using namespace std ;

namespace INSEditor {
namespace Parse{

	enum Type{BASEITEM,KEYVALUEITEM,PROPERTYITEM,COMMENT,LINEITEM,ASSEMBLYITEM,COMPILEERRORITEM};

	/*!
		@brief   lineItem等的基类
		@date    2015.6.15
		@author  Jerry
	*/	
	class BaseItem
	{
	public:
		BaseItem():type(BASEITEM),rowIndex(0),columnIndex(0){}
		BaseItem(int t):type(t),rowIndex(0),columnIndex(0){}
		virtual ~BaseItem(){}

		bool operator < (const BaseItem& i2){
			if(rowIndex==i2.rowIndex)
				return columnIndex<i2.columnIndex;
			return rowIndex<i2.rowIndex;
		}

		int type;				///类类型
		int	rowIndex;			///在文件中的行号，从0开始
		int columnIndex;		///在文件中的列号，从0开始
	};

	/*!
		@brief 代表一个键－值项。
		@author	Jerry He
		@date	2014.9
	*/
	class KeyValueItem : public BaseItem
	{
	public:
		KeyValueItem():BaseItem(KEYVALUEITEM){}
		KeyValueItem(const QString& name):BaseItem(KEYVALUEITEM),keyname(name){}

		QString keyname;		///键名
		QStringList valueList;	///键值数组
	};

	/// 代表一个属性值
	class PropertyItem : public BaseItem
	{
	public:
		PropertyItem(const QString& nameV):BaseItem(PROPERTYITEM),name(nameV){}
		QString name;
	};

	/// 代表一个注释条目
	class CommentItem : public BaseItem
	{
	public:
		CommentItem(const QString& c):BaseItem(COMMENT),comment(c){}
		QString comment;
	};

	class AssemblyItem;

	/*!
		@brief 代表一个条目项。
		@author	Jerry He
		@date	2014.9
		*/
	class LineItem : public BaseItem
	{
	public:
		///构造函数
		LineItem();
		LineItem(const QString& name);
		LineItem(const LineItem& item);
		LineItem& operator = (const LineItem& item);

		virtual ~LineItem();

		///清空本条LineItem
		void clear();

		///添加一个子item
		BaseItem* addItem(const BaseItem& item);

		///获得本条目的的父条目
		AssemblyItem* getParent(){return parent;}
		const AssemblyItem* getParent()const{return parent;}

		///将本lineItem内容转为字符串并返回
		QString toString()const;

#ifdef _DEBUG
		/// 打开整个AssemblyItem验证
		virtual void print(const QString& pre);
#endif
		/// 获得全名
		QString getFullName()const;

		///移除属性item
		void removeProperty(PropertyItem* item);

		///是否有属性 property
		bool hasProperty(const QString& property)const;

		///通过name获得属性PropertyItem
		PropertyItem* getProperty(const QString& name);

		///通过name获得键值对KeyvalueItem
		KeyValueItem* getKeyvalue(const QString& name);

	public:
		/// 条目的父条目
		AssemblyItem* parent;

		/// 条目的关键字
		QString		keyname;

		/// 条目的名字
		QString		mainID;

		/// 条目的名字
		QString		mainLabel;

		///所有键值对
		QList<KeyValueItem*>	keyValues;

		///所有属性
		QList<PropertyItem*>	properties;

		///所有注释
		QList<CommentItem*>		comments;

		///所有item
		QList<BaseItem*>		allItems;

	private:
		///深拷贝lineItem
		void deepCopy(LineItem* dst,const LineItem* src);
	};

	/*!
		@brief   代表一个符合项
		@date    2015.6.15
		@author  Jerry
	*/
	class AssemblyItem : public LineItem
	{
	public:
		AssemblyItem();
		AssemblyItem(const LineItem& lineItem);
		virtual ~AssemblyItem();

		///添加子项item
		void addChild(LineItem* item);

		///添加注释
		CommentItem* addComment(const CommentItem& item);

		///返回子项总数
		int childCount()const{return itemList.size();}

		///获得第index个子项
		LineItem* child(int index){return itemList[index];}
		const LineItem* child(int index)const{return itemList[index];}

		///获得所有子项(不包含注释)
		const QList<LineItem*>& getItemList(){return itemList;}

		///获得所有子项(包含注释)
		const QList<BaseItem*>& getAllItemList(){return allItemList;}

		///移除子项item
		void removeChild(LineItem* item);

		///所在行号
		int row();

#ifdef _DEBUG
		///调试用打印信息函数
		virtual void print(const QString& pre);
#endif

	private:
		/// 子条目
		QList<LineItem*> itemList;

		/// 含注释的子条目列表
		QList<BaseItem*> allItemList;

		///禁止拷贝
		Q_DISABLE_COPY(AssemblyItem);
	};
	
	///编译信息类型
	enum CompileInfoType{
		Message,
		Log,
		Warning,
		Error
	};

	/*! 编译时产生的错误的信息内容。*/
	class CompileInfoItem : public BaseItem
	{
	public:
		CompileInfoItem(const QString& fileName_,const QString& errorInfo_,CompileInfoType type_=Warning)
			:BaseItem(COMPILEERRORITEM)
			,infoType(type_)
			,fileName(fileName_)
			,errorInfo(errorInfo_)
		{
		}

		CompileInfoType infoType;

		/// 文件名
		QString	fileName;	

		/// 错误信息
		QString errorInfo;		
	};

}	// end namespace Parse
} // end namespace INSEditor