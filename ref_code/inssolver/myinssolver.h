#ifndef MYINSSOLVER_H
#define MYINSSOLVER_H


#include "inssolver/inssolver_global.h"
#include "inssolver/inssolver.h"

class INSSolverManager;


/*!
	@brief   充当求解器的测试程序
	@date    2015.6.23
	@author  Jerry
*/
class INSSOLVER_EXPORT MyINSSolver : public INSSolver
{
public:
	MyINSSolver();

	///实现虚方法
	virtual void setPara(const INSSolverPara& para);
	virtual void start();
	virtual void pause();
	virtual void restart();
	virtual void stop();

	virtual void compile(const char* fileName);

private:
	///存储求解器启动相关设置参数
	INSSolverPara _solverPara;

	///是否是暂停的
	bool		_isPaused;

	///需要暂停
	bool		_needPause;

	///需要停止
	bool		_needStop;
	
};

#endif // MYINSSOLVER_H
