#ifndef HELPENGINESINGLETON_H
#define HELPENGINESINGLETON_H

class QHelpEngine;

class HelpEngineSingleton
{

public:
	HelpEngineSingleton();
	~HelpEngineSingleton();

	static QHelpEngine* instance();
	static void setHelpEngine(QHelpEngine* e){_engine=e;}

private:
	static QHelpEngine*	_engine;
	
};

#endif // HELPENGINESINGLETON_H
