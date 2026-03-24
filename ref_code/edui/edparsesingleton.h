#ifndef EDPARSESINGLETON_H
#define EDPARSESINGLETON_H


#include "edparse/EDParsePlugin.h"

/*!
	@brief   edparse插件工程加载实现单例类
	@date    2015.6.19
	@author  Jerry
*/
class EDParseSingleton
{
public:
	///获得本工程的唯一指针
	static EDParseSingleton* instance();

	///得到edparse插件
	EDParsePlugin* getPlugin(){return _plugin;}

private:
	EDParsePlugin*	_plugin;

	EDParseSingleton();
	~EDParseSingleton();
	Q_DISABLE_COPY(EDParseSingleton);

};

#endif // EDPARSESINGLETON_H
