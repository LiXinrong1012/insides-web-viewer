
#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include "edui/edui_global.h"

/*!
	@brief   主程序类，main函数调用
	@date    2015.6.19
	@author  Jerry
*/
class EDUI_EXPORT MainApplication
{
public:
	MainApplication();
	~MainApplication();
	
	///初始化并启动主程序
	int run(int argc,char* argv[]);

private:

};

#endif // MAINAPPLICATION_H
