#pragma once

#include "precore/baseitem.h"
#include "prefem/JFEMPart.h"

#include <QVector>

namespace INSIDES
{

struct SNode
{
	QString typeName;
	int		id;
	QString QG;
};

struct SElement
{
	QString typeName;
	int		id;
	int		groupId;
	QString nodeList;

	SElement():groupId(0){}
};

/*!
*	代表一个柔性体。
*	@author Jerry He
*	@date	2014.4.4
*/
class PRECORE_EXPORT FEMPartBaseItem :
	public BaseItem
{
public:
	FEMPartBaseItem(void);
	~FEMPartBaseItem(void);

	virtual void copyTo(BaseItem* item)const;//复制到别一个条目，不包含子对象,不包含父子关系

	JFEMPart* getFEMPart(){return &_FEMPart;}

	QVector<SNode>& getSNodeList(){return _sNodeList;}
	QVector<SElement>& getSElementList(){return _sElementList;}

	/// 根据String值更新内部值。
	void updateInteralMesh();

private:
	JFEMPart	_FEMPart;
	QVector<SNode>	_sNodeList;
	QVector<SElement>	_sElementList;
};


} // end namespace INSIDES