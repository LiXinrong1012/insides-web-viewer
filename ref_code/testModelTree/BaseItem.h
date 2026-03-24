#pragma once

#include <QString>
#include <QList>


class BaseItem
{
public:
	BaseItem(void);
	~BaseItem(void);

	enum VisibilityType{Visual,Unvisual,Inherit};

	QString getKeyname(){return _name;}
	void setKeyname(const QString& name){_name=name;}

	BaseItem* getParent(){return _parent;}
	void setParent(BaseItem* parent){_parent=parent;}

	VisibilityType getVisibilityType(){return _visibilityType;}
	void setVisibilityType(VisibilityType v){_visibilityType=v;}

	/// to support children
	virtual int count()const{return _itemlist.size();}
	virtual BaseItem* child(int index){return _itemlist[index];}
	virtual bool remove(BaseItem* item);
	int row()const;
	virtual int indexOf(BaseItem* const item)const;
	virtual bool insertChild(int pos,BaseItem* item);
	virtual bool appendChild(BaseItem* item);
	virtual bool clearChildren();


private:
	QList<BaseItem*> _itemlist;
	BaseItem*	_parent;
	QString		_name;
	VisibilityType	_visibilityType;

	friend class ModelDocument;
	
};

