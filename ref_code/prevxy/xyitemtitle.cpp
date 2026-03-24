#include "xyitemtitle.h"

QDataStream& operator << (QDataStream& out,const XYItemTitle& item)
{
	out<<item.itemContent
		<<item.secIndex
		<<item.subsecIndex
		<<item.subsubsecIndex
		<<item.nodeElemIndex
		<<item.name
		<<(qint32)(item.type)
		<<item.xs
		<<item.ys

		<<item.itemYContent
		<<item.secYIndex
		<<item.subsecYIndex
		<<item.subsubsecYIndex
		<<item.nodeElemYIndex
		<<item.yType;
	return out;
}
QDataStream& operator >> (QDataStream& in, XYItemTitle& item)
{
	qint32 tmpType,yTmpType;
	in>>item.itemContent
		>>item.secIndex
		>>item.subsecIndex
		>>item.subsubsecIndex
		>>item.nodeElemIndex
		>>item.name
		>>tmpType;
	in
		>>item.xs
		>>item.ys
		
		>>item.itemContent
		>>item.secIndex
		>>item.subsecIndex
		>>item.subsubsecIndex
		>>item.nodeElemIndex
		>>yTmpType;
	item.type=(XYItemTitle::Type)tmpType;
	item.yType=(XYItemTitle::Type)yTmpType;

	return in;
}