#ifndef INSSOLVER_H
#define INSSOLVER_H


#include <string>
#include <map>

class INSSolverManager;

/*!
*	@breif  求解器启动相关参数。
	@date   2015.6.23
	@author Jerry
*/
struct INSSolverPara
{
	/// 求解器管理实例指针
	INSSolverManager* manager;

	/// 求解文件名，全路径
	std::string fileName;
	std::map<std::string,std::string> settings;
};

/*!
*	@breif 代表一个求解器实例
*	定义求解器对外的管理方法,供前处理与求解器交互。
*	@author	Jerry He
*	@date	2014.10.3
*/
class INSSolver
{
public:
	virtual ~INSSolver(){};

	///设置求解器启动相关参数
	virtual void setPara(const INSSolverPara& para)=0;

	///求解器开始求解
	virtual void start()=0;

	///求解器暂停求解
	virtual void pause()=0;

	///求解器重新开始求解
	virtual void restart()=0;

	///求解器停止求解
	virtual void stop()=0;

	///编译模型文件fileName
	virtual void compile(const char* fileName)=0;
private:

};

#endif // INSSOLVER_H
