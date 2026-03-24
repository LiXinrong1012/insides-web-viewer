#ifndef XYITEMTITLE_H
#define XYITEMTITLE_H

#include <QObject>
#include <QVector>
#include "qcustomplot/qcustomplot.h"

/*!
	@brief   代表xy条目信息数据结构类
	@date    2015.7.3
	@author  Jerry
*/
class XYItemTitle 
{
public:
	XYItemTitle():type(Normal),yType(Normal),relatedPlotable(NULL){};

	enum Type{Normal=0,Custom,IsImported};

	/// 曲线类型
	Type type;			

	/// 曲线的名字
	QString name;		

	///曲线定义条目或者内容
	QString itemContent;	

	///x行第一条目索引
	int secIndex;

	///x行第二条目索引
	int subsecIndex;

	///x行第三条目索引
	int subsubsecIndex;

	///x行节点选择框索引
	int nodeElemIndex;

	///全部x值
	QVector<double>	xs;

	///全部y值
	QVector<double> ys;

	///　此曲线的指针
	QCPCurve* relatedPlotable; 

	///曲线定义条目或者内容
	QString itemYContent;	

	///y行第一条目索引
	int secYIndex;

	///y行第二条目索引
	int subsecYIndex;

	///y行第三条目索引
	int subsubsecYIndex;

	///y行节点选择框索引
	int nodeElemYIndex;

	///y值类别
	Type yType;

	///重定输入符
	friend QDataStream& operator << (QDataStream& fout,const XYItemTitle& item);

	///重定输出符
	friend QDataStream& operator >> (QDataStream& fin, XYItemTitle& item);
};

QDataStream& operator << (QDataStream& fout,const XYItemTitle& path);
QDataStream& operator >> (QDataStream& fin, XYItemTitle& path);

#endif // XYITEMTITLE_H