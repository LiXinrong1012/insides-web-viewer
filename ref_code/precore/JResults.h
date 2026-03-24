#pragma once

#include "precore/iresults.h"

namespace pp{
	class DataStreamReader;
}

namespace INSIDES
{

class JResults :
	public IResults
{
public:
	JResults(void);
	virtual ~JResults(void);

	/// 进行初始化，创建之后调用
	virtual bool init();

	/// 得到此帧的时候
	virtual double getTime(int index)const{return _timelist[index];}

	//virtual std::complex<double> getEigenFreq(int index)const{return std::complex<double>(0,0);}
	virtual QString getEigenFreq(int index)const{return _freqList[index];}

	void setTimeList(QList<double>& timelist){_timelist=timelist;}

	void setDataReader(QSharedPointer<pp::DataStreamReader> reader){_dataReader=reader;}
	QSharedPointer<pp::DataStreamReader> getDataReader(){return _dataReader;}

private:
	QList<double>		_timelist;
	QList<QString>		_freqList;
	QSharedPointer<pp::DataStreamReader>	_dataReader;


};

}