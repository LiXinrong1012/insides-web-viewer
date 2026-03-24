#pragma once

#include <QScopedPointer>
#include <QString>
#include <QDataStream>

class TDYParameterItem
{
public:
	QString keyname;
	QString strPara;
	QString description;
};


class TDYParametersPrivate;

class TDYParameters
{
public:
	TDYParameters(void);
	~TDYParameters(void);

	TDYParameters* clone()const;

	int count()const;
	const TDYParameterItem* getAt(int index)const;
	QList<TDYParameterItem> getAll()const;
	bool add(const TDYParameterItem& item);
	bool add(const TDYParameterItem& item,QString& errMessage);
	bool add(const QString& key,const QString& para);
	bool add(const QString& key,const QString& para,const QString& des);
	bool add(const QString& key,const QString& para,const QString& des,QString& errmess);
	void clear();

	bool hasKey(const QString& key)const;
	bool addOrReplace(const QString& key,const QString& para);
	bool addOrReplace( const TDYParameterItem& item);

	// calculate values
	double getValue(const QString& str,bool* result=NULL)const;

private:
	QScopedPointer<TDYParametersPrivate> _ptr;
	TDYParameters(TDYParameters&);
	
	friend QDataStream &	operator<< ( QDataStream & out, const TDYParameters& paras );

	friend QDataStream &	operator>> ( QDataStream & in, TDYParameters& paras );
};

QDataStream &	operator<< ( QDataStream & out, const TDYParameterItem& paras );
QDataStream &	operator>> ( QDataStream & in, TDYParameterItem& paras );

QDataStream &	operator<< ( QDataStream & out, const TDYParameters& paras );
QDataStream &	operator>> ( QDataStream & in, TDYParameters& paras );