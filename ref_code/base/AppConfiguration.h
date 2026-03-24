#pragma once

#include "Base/base_global.h"
#include <QString>

namespace Base{

class ParametersManager;

/*!
*	This class is used to store some global various, e.g,
*	startup directory, working directory, app status, etc.
*	@author Jerry He
*	@date	2014.3.29
*/
class BASE_EXPORT AppConfiguration
{
public:
	static AppConfiguration* instance();

	/// get/set startup directory
	QString startupDirectory()const;
	void setStartupDirectory(const QString& str);

	/// get/set working directory
	QString workingDirectory()const;
	void setWorkingDirectory(const QString& str);

	QString projectFullName()const;
	void setProjectFullName(const QString& str);

	/// get/set solver directory
	QString getSolverDirectory()const;
	void setSolverDirectory(const QString& str);

	ParametersManager* getParametersManager();
	const ParametersManager* getParametersManager()const;


private:
	AppConfiguration(void);
	~AppConfiguration(void);

	class Internals;

	Internals* _internals;
};


}	//end namespace Base