#include "saveorreadclass.h"
#include <QStringList>
#include <QFile>

#include "CustomPlotViewSetting.h"

SaveOrReadClass::SaveOrReadClass(QObject *parent)
//	: QMimeData(parent)
{
	_magicValue = 0xa1a2a3a4;
}

SaveOrReadClass::~SaveOrReadClass()
{

}

void SaveOrReadClass::saveAllData()
{
	QFile saveData("savedata.dat");
	saveData.open(QFile::WriteOnly);
	QDataStream stream(&saveData);
	stream.setVersion(QDataStream::Qt_4_8);
	stream<< _magicValue;
	QStringList types = this->formats();
	stream<<types.count();
	for(int i=0;i<types.count();i++)
	{
		stream<<types[i];
		stream<<this->data(types[i]);
	}
	saveData.close();
}

bool SaveOrReadClass::readAllData()
{
	QFile openData("savedata.dat");
	openData.open(QFile::ReadOnly);
	QDataStream stream(&openData);
	stream.setVersion(QDataStream::Qt_4_8);
	qint32 magic;  
	stream >> magic;  
    if (magic != _magicValue)  
		return false;  

	int count ;
	stream>>count;
	for (int i=0;i<count;i++)
	{
		QString typeStr ;
		stream>>typeStr;
		QByteArray byte;
		stream>>byte;
		double d = byte.toDouble();
		int dd = byte.toInt();

		this->setData(typeStr,byte);
	}
	openData.close();
	return true;
}

void SaveOrReadClass::setSaveData(QString mimeType,QString value)
{
	QByteArray encodeData;
	QDataStream stream(&encodeData,QIODevice::WriteOnly);
	stream<<value;	
	this->setData(mimeType,encodeData);
}

QString SaveOrReadClass::getSaveQStringData( QString mimeType )
{
	QByteArray array = this->data(mimeType);
	QDataStream stream(&array,QIODevice::ReadOnly);
	QString str;
	stream>>str;
	return str;
}

void SaveOrReadClass::setSaveData( QString mimeType,double value )
{
	QByteArray encodeData;
	QDataStream stream(&encodeData,QIODevice::WriteOnly);
	stream<<value;	
	this->setData(mimeType,encodeData);
}

double SaveOrReadClass::getSaveDoubleData( QString mimeType )
{
	QByteArray encodeData=this->data(mimeType);
	QDataStream stream(&encodeData,QIODevice::ReadOnly);
	double temp;
	stream>>temp;
	return temp;
}

void SaveOrReadClass::setSaveData( QString mimeType,int value )
{
	QByteArray encodeData;
	QDataStream stream(&encodeData,QIODevice::WriteOnly);
	stream<<value;	
	this->setData(mimeType,encodeData);
}

int SaveOrReadClass::getSaveIntData( QString mimeType )
{
	QByteArray array=this->data(mimeType);
	QDataStream stream(&array,QIODevice::ReadOnly);
	int temp;
	stream>>temp;
	return temp;
}

void SaveOrReadClass::setSaveData( QString mimeType,QVector<double> value )
{
	QByteArray encodeData;
	QDataStream stream(&encodeData,QIODevice::WriteOnly);
	stream<<value.count();
	stream<<value;	
	this->setData(mimeType,encodeData);
}

QVector<double> SaveOrReadClass::getDoubleVectorData( QString mimeType )
{
	QByteArray array = this->data(mimeType);
	QDataStream stream(&array,QIODevice::ReadOnly);
	int count=0 ;
	double num=0;
	QVector<double> vect;
	stream>>count;
	stream>>vect;
	return vect;
	for (int i=0;i<count;i++)
	{
		stream>>num;
		vect.push_back(num);
	}
	return vect;
}

void SaveOrReadClass::setSaveData( QString mimeType,QByteArray array )
{
	this->setData(mimeType,array);
}

void SaveOrReadClass::setSaveData( QString mimeType,CurveSetting settings )
{
	QByteArray encodeData;
	QDataStream stream(&encodeData,QIODevice::WriteOnly);
	stream<<settings.colorCurve;
	stream<<(int)(settings.nCurveWidth);
	stream<<(int)(settings.axisType);
	stream<<(int)(settings.penStyle);
	stream<<(int)(settings.curveLineStyle);
	stream<<(int)(settings.scatterShape);
	stream<<settings.shapeSize;
	this->setData(mimeType,encodeData);
}

CurveSetting SaveOrReadClass::getCurveSetting( QString mimeType )
{
	CurveSetting settings;
	QByteArray encodeData;
	int axisType,penStyle,curveLineStyle,scatterShape;
	encodeData = this->data(mimeType);
	QDataStream stream(&encodeData,QIODevice::ReadOnly);

	stream>>settings.colorCurve;
	stream>>settings.nCurveWidth;
	stream>>axisType;
	settings.axisType = (AxisType)axisType;
	stream>>penStyle;
	settings.penStyle = (Qt::PenStyle)penStyle;
	stream>>curveLineStyle;
	settings.curveLineStyle = (QCPCurve::LineStyle)curveLineStyle;
	stream>>scatterShape;
	settings.scatterShape = (QCPScatterStyle::ScatterShape)scatterShape;
	stream>>settings.shapeSize;
	
	return settings;
}

void SaveOrReadClass::setSaveData( QString mimeType,AxisSetting settings )
{
	QByteArray encodeData;
	QDataStream stream(&encodeData,QIODevice::WriteOnly);
	stream<<settings.bShowGrid;
	stream<<settings.bShowAxis;
	stream<<settings.colorGrid;
	stream<<settings.colorAxis;
	stream<<settings.strAxisTitle;

	stream<<settings.fontAxisTitle;
	stream<<settings.colorAxisTitle;
	stream<<settings.fontAxisLabels;
	stream<<settings.colorAxisLabels;

	stream<<settings.nPrecision;
	stream<<settings.bUseLogarithmic;
	this->setData(mimeType,encodeData);
}

AxisSetting SaveOrReadClass::getAxisSetting( QString mimeType )
{
	AxisSetting settings;
	QByteArray encodeData;
	encodeData = this->data(mimeType);
	QDataStream stream(&encodeData,QIODevice::ReadOnly);
	stream>>settings.bShowGrid;
	stream>>settings.bShowAxis;
	stream>>settings.colorGrid;
	stream>>settings.colorAxis;
	stream>>settings.strAxisTitle;

	stream>>settings.fontAxisTitle;
	stream>>settings.colorAxisTitle;
	stream>>settings.fontAxisLabels;
	stream>>settings.colorAxisLabels;

	stream>>settings.nPrecision;
	stream>>settings.bUseLogarithmic;

	return settings;
}

void SaveOrReadClass::setSaveData( QString mimeType,AxisGeneralSetting settings )
{
	QByteArray encodeData;
	QDataStream stream(&encodeData,QIODevice::WriteOnly);
	stream<<settings.strChartTitle;
	stream<<settings.fontChartTitle;
	stream<<settings.colorChartTitle;

	stream<<settings.bShowLegend;
	stream<<settings.bShowMotion;
	stream<<settings.AlignLegendhorizontal;
	stream<<settings.AlignLegendvertical;
	this->setData(mimeType,encodeData);
}

AxisGeneralSetting SaveOrReadClass::getAxisGeneralSetting( QString mimeType )
{
	AxisGeneralSetting settings;
	QByteArray encodeData;
	encodeData = this->data(mimeType);
	QDataStream stream(&encodeData,QIODevice::ReadOnly);
	int alignLegendhorizontal,alignLengendvertical;

	stream>>settings.strChartTitle;
	stream>>settings.fontChartTitle;
	stream>>settings.colorChartTitle;

	stream>>settings.bShowLegend;
	stream>>settings.bShowMotion;
	stream>>alignLegendhorizontal;
	settings.AlignLegendhorizontal = (Qt::Alignment)alignLegendhorizontal;
	stream>>alignLengendvertical;
	settings.AlignLegendvertical=(Qt::Alignment)alignLengendvertical;
	return settings;
}

int SaveOrReadClass::getTypeCount()
{
	return this->formats().count();
}





