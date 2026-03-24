#ifndef INSSOLVERMANAGER_H
#define INSSOLVERMANAGER_H

#include <string>

/*!
	@brief   用来记录更新信息的结构体
	@date    2015.6.23
	@author  Jerry
*/
struct SolverUpdateInfo
{
	/// 起始物理仿真时间
	double startTime ;

	/// 终了物理仿真时间
	double endTime ;

	/// 积分精度
	double error ;

	/// 当前计算到的时间
	double	calTime;

	/// 当前物理积分步长
	double stepTime ;	

	/// 其它信息
	std::string message;

	SolverUpdateInfo()
		:startTime(0)
		,endTime(0)
		,error(0)
		,calTime(0)
		,stepTime(0)
		,message("")
	{}
};


/*!
	@breif 求解器管理的回调方法虚基类。
	为求解器回调界面方法提供入口。

	@author	Jerry He
	@date	2014.10.3
*/
class INSSolverManager
{
public:
	enum LogType{LT_MESSAGE=0,LT_LOG,LT_WARNING,LT_ERROR};

	///当求解器启动后回调
	virtual void started()=0;

	///当求解器暂停后回调
	virtual void paused()=0;

	///当求解器重新开始后回调
	virtual void restarted()=0;

	///当求解器求解完成后回调
	virtual void finished()=0;

	///显示 log
	virtual void log(int logType,const std::string& message)=0;

	///显示信息
	virtual void information(const SolverUpdateInfo* info)=0;
};

#endif // INSSOLVERMANAGER_H
