#include <QApplication>
#include "updateftp.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	FtpWindow ftpWin;
	ftpWin.show();
	return app.exec();
}
