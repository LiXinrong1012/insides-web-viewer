#ifndef SAVEORREADCLASS_H
#define SAVEORREADCLASS_H

#include <QMimeData>
#include <QVector>
#include <QMessageBox>

class CurveSetting;
class AxisSetting;
class CutsomPlotAxisSetting;
class AxisGeneralSetting;
class SaveOrReadClass : public QMimeData
{
	Q_OBJECT

public:
	SaveOrReadClass(QObject *parent);
	~SaveOrReadClass();

	void saveAllData();
	bool readAllData();

	void setSaveData(QString mimeType,QByteArray array);

	void setSaveData(QString mimeType,QString value);
	QString getSaveQStringData(QString mimeType);

	void setSaveData(QString mimeType,double value);
	double getSaveDoubleData(QString mimeType);

	void setSaveData(QString mimeType,int value);
	int getSaveIntData(QString mimeType);

	void setSaveData(QString mimeType,QVector<double> value);
	QVector<double> getDoubleVectorData(QString mimeType);

	///CurveParasSerialize.cpp 42ÐÐ
	void setSaveData(QString mimeType,CurveSetting settings);
	CurveSetting getCurveSetting(QString mimeType);
	///CurveParasSerialize.cpp 120ÐÐ
	void setSaveData(QString mimeType,AxisSetting settings);
	AxisSetting getAxisSetting(QString mimeType);
	///CurveParaSerialize.cpp 22ÐÐ
	void setSaveData(QString mimeType,AxisGeneralSetting settings);
	AxisGeneralSetting getAxisGeneralSetting(QString mimeType);

	
	int getTypeCount();
	
private:
	qint32 _magicValue;
};

#endif // SAVEORREADCLASS_H
