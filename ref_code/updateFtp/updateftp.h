#ifndef FTPWINDOW_H
#define FTPWINDOW_H

#include <QDialog>
#include <QDialog>
#include <QHash>
#include <QNetworkConfigurationManager>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFile;
class QFtp;
class QLabel;
class QLineEdit;
class QTreeWidget;
class QTreeWidgetItem;
class QProgressDialog;
class QPushButton;
class QUrlInfo;
class QNetworkSession;
QT_END_NAMESPACE

namespace Ui{
	class UpdateFtpClass;
}
class FtpWindow : public QDialog
{
	Q_OBJECT

public:
	FtpWindow(QWidget *parent = 0);

	//![0]
	private slots:
		void updateAll();
		void cancelDownload();
		void connectToFtp();
		void downloadFile();
		void ftpCommandFinished(int commandId, bool error);
		void addList(const QUrlInfo &urlInfo);
		void updateProgress(qint64 readBytes,
			qint64 totalBytes);

signals:
		void downloadNext();


private:
	QString _host;
	QString _user;
	QString _pass;
	QString _path;
	QString _localDir;

	QStringList _updateFiles;
	int _currentItem;
	QString _currentPath;
	QFtp *_ftp;
	QFile *_file;

	QNetworkSession *_networkSession;
	QNetworkConfigurationManager _manager;
	Ui::UpdateFtpClass *ui;
};

#endif
