#pragma once

#include "coresps/coresps_global.h"
#include <QScopedPointer>


class HoopsStyleManagerPrivate;

/*!
\breif This class is used to manage HOOPS styles.
*/
class CORESPS_EXPORT HoopsStyleManager
{
public:
	static HoopsStyleManager* instance();
	static void destruct();

	HC_KEY getStyle(const char* keyName);
	bool removeStyle(const char* keyName);
	void clear();
	void startDefineStyle(const char* keyName);
	void endDefineStyle();

	bool includeStyleSegment(const char* keyName);

private:
	static HoopsStyleManager* _instance;
	QScopedPointer<HoopsStyleManagerPrivate> _ptr;
	HoopsStyleManager(void);
	~HoopsStyleManager(void);
};

