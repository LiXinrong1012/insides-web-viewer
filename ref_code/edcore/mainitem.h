#pragma once

#include "edcore/edcore_global.h"
#include <vector>
#include <string>
#include <map>

#include <QList>
#include <QString>
#include <QSet>
#include <QStringList>
#include <QMap>

using namespace std ;


namespace Parse {
	/*!
	*	代表一条像　QG=1,2,3　这样的子条目。
	*	@author	Jerry He
	*	@date	2014.8.31
	*/
	class EDCORE_EXPORT SubItem
	{
	public:
		SubItem():rowIndex(0),columnIndex(0){}
		SubItem(const QString& name):keyname(name),rowIndex(0),columnIndex(0){}

		QString keyname;
		QStringList valueList;
		int	rowIndex;
		int columnIndex;
	};

	/*!
	*	代表一条像 Box 这样的属性。
	*	@author	Jerry He
	*	@date	2014.8.31
	*/
	class EDCORE_EXPORT SubProperty
	{
	public:
		QString propertyName;
		int		rowIndex;
		int		columnIndex;

		SubProperty(const QString& name=QString()):propertyName(name),rowIndex(-1),columnIndex(-1)
		{
		}
	};

	/*!
	*	代表一条完整的条目，例如：
	*	Marker /1, QG=1,2,3
	*
	*	@author	Jerry He
	*	@date	2014.8.31
	*/
	class EDCORE_EXPORT Item
	{
	public:
		Item();
		Item(const QString& name);

		virtual ~Item();

		///为该条目添加子项
		void appendItem(Item* item);

		///返回子项数
		int childCount()const{return itemList.size();}

		///获得子项通过给定的index
		Item* child(int index){return itemList[index];}

		///获得子项通过给定的index
		const Item* child(int index)const{return itemList[index];}

		///返回当前条目所在行
		int row();

		///返回此条目的父条目
		Item* getParent(){return parent;}

		///返回此条目的父条目
		const Item* getParent()const{return parent;}

		///将条目信息转化为字符串
		QString toString()const;

		///获得该条目全名
		QString getFullName()const;

		/// 条目的父条目
		Item* parent;

		/// 条目的关键字
		QString		keyname;

		/// mainID
		QString		mainID;

		/// mainLabel
		QString		mainLabel;

		/// 所在行号
		int			rowIndex;

		/// 所在列号
		int			columnIndex;

		/// 属性
		QStringList	properties;

		/// 键值对
		QList<SubItem>	keyValues;

	private:
		/// 子条目
		QList<Item*> itemList;

		/*
		bool GetValue ( string subname, vector<string>*& val, const int num = 1, const bool bcheck = false ) ;

		bool GetValue ( int &num, string subname, vector<string>*& val ) ;

		void toLocation ( string& location ) ;	// 将location赋值为文件名+行号

		string toLocation() ;

		bool hasProperty ( string const& s )  ;

		map<string, string>* getProperties() {
			if ( properties.size() == 0 )
				return NULL ;
			else
				return &properties ;
		}

		int  PropertySize()  { return properties.size() ;} ;

		void write ( string prestr, ofstream& fout ) ;


		bool findSubs( vector<string> subnames, list<SubItem*>* subs ) ;

		bool confirmSubs( list<string>& subnames ) ;
		*/
	};

	class EDCORE_EXPORT FileItem : public Item
	{
	public:
		/// 主项属于的文件名
		QString		fileName;			

	};

}