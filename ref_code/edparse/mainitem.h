#pragma once

#include "edparse/edparse_global.h"
#include <vector>
#include <string>
#include <map>

#include <QList>
#include <QString>
#include <QSet>
#include <QStringList>

using namespace std ;



namespace Parse {

	struct EDPARSE_EXPORT SubItem
	{
		SubItem():rowIndex(0),columnIndex(0){}
		SubItem(const QString& name):keyname(name),rowIndex(0),columnIndex(0){}

		QString keyname;
		QStringList valueList;
		int	rowIndex;
		int columnIndex;
	};

	class EDPARSE_EXPORT Item
	{
	public:
		Item();
		Item(const QString& name);

		virtual ~Item(){qDeleteAll(itemList);itemList.clear();}

		void appendItem(Item* item);
		int childCount()const{return itemList.size();}
		Item* child(int index){return itemList[index];}
		const Item* child(int index)const{return itemList[index];}
		int row();

		Item* getParent(){return parent;}
		const Item* getParent()const{return parent;}

		QString toString()const;

		QString getFullName()const;

		/// 条目的父条目
		Item* parent;
		/// 条目的关键字
		QString		keyname;
		QString		mainID;
		QString		mainLabel;
		int			rowIndex;
		int			columnIndex;

		QStringList	properties;
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

	class EDPARSE_EXPORT FileItem : public Item
	{
	public:
		/// 主项属于的文件名
		QString		fileName;			

	};


	class EDPARSE_EXPORT ErrorItem
	{
	public:
		QString	fileName;
		int		lineIndex;
		int		columnIndex;
		QString errorInfo;
		QString possibleSolution;
	};

}