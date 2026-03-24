#pragma once

#include <QString>
#include <QScopedPointer>

class ExportTDYPrivate;
/*!
*	This class to used to export .tdy file.
*	@author Jerry He
*	@date 2014.3.19
*/
class ExportTDY
{
public:
	ExportTDY(void);
	~ExportTDY(void);

	bool doJob(const QString& fileName );

private:
	QScopedPointer<ExportTDYPrivate> _ptr;
};

