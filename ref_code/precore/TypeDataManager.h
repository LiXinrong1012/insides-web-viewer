#pragma once

#include "precore/precore_global.h"
#include <map>
#include <string>
#include <vector>
#include <QString>
#include <QScopedPointer>

struct TypeDataSingleItem
{
	QString keyname;
	QString displayText;
	QString description;
};


struct TypeDataGroup
{
	QString groupName;
	std::vector<TypeDataSingleItem> items;
};

/*!
*	单个条目类型的信息。
*	@author Jerry He
*	@date 2014.2.7
*/
class TypeData
{
public:
	int		typeID;
	QString	icon;
	QString insIcon;	//实例的图标
	QString	typeDiscription;
	QString name;
	QString TDYName;
	std::vector<TypeDataGroup> groups;
};


class TypeDataManagerPrivate;

class PRECORE_EXPORT TypeDataManager
{
public:
	static TypeDataManager* instance();
	bool init(const QString& fileName);
	void clear();

	TypeData* getTypeData(int typeID);

private:
	QScopedPointer<TypeDataManagerPrivate> _ptr;

	// singleton pattern.
	static TypeDataManager* _instance;
	TypeDataManager(void);
	~TypeDataManager(void);
};

