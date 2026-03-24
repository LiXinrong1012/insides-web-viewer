/***************************************************************************
*   Copyright (c) 2010-2011 Jerry He                                      *
*                                                                         *
*   This file is part of the QtMudyPlot development system.               *
*                                                                         *
*   All this libraries can be used freely,  with any purpose,             * 
*   including commercial applications, and to alter it or                 * 
*   redistribute it.                                                      *
*                                                                         *
*   But the following restrictions must be obeyed.                        *
*                                                                         *
*   1. The origin of this software must not be misrepresented;            *
*   you must not claim that you wrote the original software.              * 
*   If you use this software in a product, an acknowledgment in the       * 
*   product documentation would be appreciated but is not required.       *
*                                                                         * 
*   2. Altered source versions must be plainly marked as such, and        *
*   must not be misrepresented as being the original software.            *
*                                                                         *
*   3. This notice may not be removed or altered from any source          * 
*   distribution.                                                         *
*                                                                         *
*   If you have any problems or advices, you can contact me.              *
*   E-mail: hejw06@gmail.com                                              *
*                                                                         *
***************************************************************************/


#pragma once

#include "base/base_global.h"
#include <QPixmap>
#include <QString>
#include <QMap>


namespace Base
{

class BASE_EXPORT PixmapManagerSingleton
{
public:
	bool exist(const QString& keyName);
	QPixmap* get(const QString& keyName);

	static PixmapManagerSingleton* instance();

protected:
	static PixmapManagerSingleton* _instance;

	PixmapManagerSingleton(void);
	~PixmapManagerSingleton(void);

	QPixmap* add(const QString& keyName);

	typedef std::map<QString,QPixmap*> KeyMap;
	KeyMap _dataMap;
};

inline BASE_EXPORT PixmapManagerSingleton* PixmapManager(){
	return PixmapManagerSingleton::instance();
}



} // end namespace Base
