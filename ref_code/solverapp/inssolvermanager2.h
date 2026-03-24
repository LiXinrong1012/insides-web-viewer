#ifndef INSSOLVERMANAGER2_H
#define INSSOLVERMANAGER2_H

#include <QString>
#include "inssolver/inssolvermanager.h"


class SolverUpdateInfo2 : public SolverUpdateInfo
{
public:
	double cpuTime;
	double process;
	double remainTime;
};

/*!
	@brief 针对INSSolverManager的一个扩充。
	INSSolverManager是针对求解器的一个回调类，基于纯C++定义。
	INSSolverManager针对SolverApp内部，转换接口为Qt接口。

	@author	Jerry He
	@date	2015.1.13
*/
class INSSolverManager2 : public INSSolverManager
{
public:
	INSSolverManager2():_connector(NULL){}
	virtual void log(int logType,const std::string& message){}
	virtual void log2(int logType,const QString& mes)=0;

	virtual void information(const SolverUpdateInfo* info){}
	virtual void information2(SolverUpdateInfo2& info)=0;

	INSSolverManager2* getConnector(){return _connector;}
	void setConnector(INSSolverManager2* m){_connector=m;}

private:
	INSSolverManager2* _connector;
	
};

#endif // INSSOLVERMANAGER2_H
